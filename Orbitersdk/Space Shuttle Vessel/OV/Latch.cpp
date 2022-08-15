/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/06   GLS
2020/05/10   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/06/18   GLS
2021/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/05/07   GLS
2022/08/05   GLS
********************************************/
#include "Latch.h"
#include "ActiveLatchGroup.h"
#include "MPM.h"
#include "Atlantis.h"
#include <MathSSV.h>
//#include <Stopwatch.h>

LatchSystem::LatchSystem( AtlantisSubsystemDirector *_director, const std::string &_ident, const std::string &_attachID, double latchmaxdistance, double latchmaxangle )
	: AtlantisSubsystem(_director, _ident), attachedPayload(NULL), hPayloadAttachment(NULL), hAttach(NULL), AttachID(_attachID),
	latchmaxdistance(latchmaxdistance), latchmaxangle(latchmaxangle), firstStep(true), payloadName(""), attachmentIndex(-1)
{
}

LatchSystem::~LatchSystem()
{
}

void LatchSystem::OnPreStep(double simt, double simdt, double mjd)
{
	//oapiWriteLog((char*)(GetIdentifier().c_str()));
	if(firstStep) {
		//oapiWriteLog("First step");
		CheckForAttachedObjects();
		firstStep=false;
	}

	if(attachedPayload!=NULL && !STS()->GetAttachmentStatus(hAttach)) {
		if(PayloadIsFree()) {
			/*STS()->AttachChild(attachedPayload->GetHandle(), hAttach, hPayloadAttachment);
			double mass=STS()->GetEmptyMass()+attachedPayload->GetMass();
			STS()->SetEmptyMass(mass);*/
			STS()->AttachChildAndUpdateMass(attachedPayload->GetHandle(), hAttach, hPayloadAttachment);
		}
	}
}

bool LatchSystem::OnParseLine(const char* line)
{
	const std::string label = "ATTACHED_PAYLOAD ";
	if(!_strnicmp(line, label.c_str(), label.length())) {
		std::string temp=line+label.length();
		int index=temp.find(' ');
		payloadName=temp.substr(0, index);
		std::string num=temp.substr(index+1);
		attachmentIndex=atoi(num.c_str());

		oapiWriteLogV( "%s payload: %s %d", GetIdentifier().c_str(), payloadName.c_str(), attachmentIndex );
		return true;
	}
	return false;
}

void LatchSystem::OnSaveState(FILEHANDLE scn) const
{
	if(hPayloadAttachment) {
		char pData[55];
		sprintf_s(pData, 55, "%s %d", attachedPayload->GetName(), attachedPayload->GetAttachmentIndex(hPayloadAttachment));
		oapiWriteScenario_string(scn, "ATTACHED_PAYLOAD", pData);
	}
}

void LatchSystem::AttachPayload(VESSEL* vessel, ATTACHMENTHANDLE attachment)
{
	//for the moment, assume attachment passed is completely valid
	hPayloadAttachment=attachment;
	attachedPayload=vessel;

	// needed to prevent RMS and MPMs from moving when payload they are attached to is latched to something else
	if(STS()->GetPortMPM() && (STS()->GetPortMPM() != this)) STS()->GetPortMPM()->CheckDoubleAttach(vessel, true);
	if(STS()->GetStarboardMPM() && (STS()->GetStarboardMPM() != this)) STS()->GetStarboardMPM()->CheckDoubleAttach(vessel, true);
	//detached=false;

	OnAttach();
}

void LatchSystem::DetachPayload()
{
	if(attachedPayload) {
		// remove mass of released payload
		//double mass=STS()->GetEmptyMass()-attachedPayload->GetMass();
		//STS()->SetEmptyMass(mass);

		// signal to RMS and MPMs that payload they are attached to has been unlatched
		if(STS()->GetPortMPM() && (STS()->GetPortMPM() != this)) STS()->GetPortMPM()->CheckDoubleAttach(attachedPayload, false);
		if(STS()->GetStarboardMPM() && (STS()->GetStarboardMPM() != this)) STS()->GetStarboardMPM()->CheckDoubleAttach(attachedPayload, false);
	}
	hPayloadAttachment=NULL;
	attachedPayload=NULL;
	//STS()->DetachChild(hAttach);
	STS()->DetachChildAndUpdateMass(hAttach);

	OnDetach();
}

/*void LatchSystem::Detach(VESSEL* vessel)
{
	if(vessel==NULL || vessel==attachedPayload) {
		STS()->DetachChild(hAttach);
		detached=true;
	}
}*/

ATTACHMENTHANDLE LatchSystem::FindPayload(VESSEL** pVessel) const
{
	VECTOR3 grms, pos, dir, rot, grmsdir;
	ATTACHMENTHANDLE hAtt;
	STS()->GetAttachmentParams(hAttach, pos, dir, rot);
	STS()->Local2Global (pos, grms);  // global position of attachment point
	STS()->GlobalRot(dir, grmsdir);

	// Search the complete vessel list for a grappling candidate.
	// Not very scalable ...
	for (DWORD i = 0; i < oapiGetVesselCount(); i++) {
		OBJHANDLE hV = oapiGetVesselByIndex (i);
		hAtt = CanAttach(hV, grms, grmsdir);
		if(hAtt) {
			if(pVessel) *pVessel = oapiGetVesselInterface(hV);
			return hAtt;
		}
	}
	if(pVessel) *pVessel=NULL;
	return NULL;
}

ATTACHMENTHANDLE LatchSystem::CanAttach(OBJHANDLE hV, const VECTOR3& glatchpos, const VECTOR3& glatchdir) const
{
	if (hV == STS()->GetHandle()) return NULL; // we don't want to grapple ourselves ...

	VECTOR3 gpos, gdir, pos, dir, rot;
	oapiGetGlobalPos (hV, &gpos);
	if (dist (gpos, glatchpos) < oapiGetSize (hV)) { // in range
		VESSEL *v = oapiGetVesselInterface (hV);
		DWORD nAttach = v->AttachmentCount (true);
		for (DWORD j = 0; j < nAttach; j++) { // now scan all attachment points of the candidate
			ATTACHMENTHANDLE hAtt = v->GetAttachmentHandle (true, j);
			const char *id = v->GetAttachmentId (hAtt);
			if (strncmp (id, AttachID.c_str(), AttachID.length()))
				continue; // attachment point not compatible

			v->GetAttachmentParams (hAtt, pos, dir, rot);
			v->Local2Global (pos, gpos);
			//sprintf_s(oapiDebugString(), 256, "%s %s Dist: %f", v->GetName(), id, dist(gpos, glatchpos));
			//oapiWriteLog(oapiDebugString());
			if (dist (gpos, glatchpos) < latchmaxdistance) {
				v->GlobalRot(dir, gdir);
				double dot_product = range(-1, dotp(gdir, glatchdir), 1);
				if(fabs(PI-acos(dot_product)) < latchmaxangle) {
					return hAtt;
				}
			}
		}
	}

	return NULL;
}

bool LatchSystem::PayloadIsFree() const
{
	if(attachedPayload) {
		//if we are attached to payload, it must be 'free'
		if(STS()->GetAttachmentStatus(hAttach)) return true;
		//otherwise, loop through all attachment points on payload and check if any of them are in use
		DWORD count=attachedPayload->AttachmentCount(true);
		for(DWORD i=0;i<count;i++) {
			ATTACHMENTHANDLE att=attachedPayload->GetAttachmentHandle(true, i);
			if(attachedPayload->GetAttachmentStatus(att)) return false;
		}
	}
	return true;
}

void LatchSystem::CheckForAttachedObjects()
{
	if(hAttach) {
		OBJHANDLE hV=STS()->GetAttachmentStatus(hAttach);
		if(hV) {
			attachedPayload=oapiGetVesselInterface(hV);
			//double mass=STS()->GetEmptyMass()+attachedPayload->GetMass();
			//STS()->SetEmptyMass(mass);
			// find handle of attachment point on payload
			for(DWORD i=0;i<attachedPayload->AttachmentCount(true);i++) {
				ATTACHMENTHANDLE hAtt=attachedPayload->GetAttachmentHandle(true, i);
				if(attachedPayload->GetAttachmentStatus(hAtt)==STS()->GetHandle()) {
					hPayloadAttachment=hAtt;
					OnAttach();
					return;
				}
			}
		}
		else { // check data loaded from scenario
			if(attachmentIndex!=-1 && !payloadName.empty()) {
				hV=oapiGetVesselByName((char*)payloadName.c_str());
				if(hV) {
					VESSEL* v=oapiGetVesselInterface(hV);
					ATTACHMENTHANDLE attach=v->GetAttachmentHandle(true, attachmentIndex);
					AttachPayload(v, attach);
				}
			}
		}
	}
}
