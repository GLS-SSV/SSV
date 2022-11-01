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
2022/10/30   GLS
2022/11/01   GLS
********************************************/
#include "Latch.h"
#include "ActiveLatchGroup.h"
#include "MPM.h"
#include "Atlantis.h"
#include <MathSSV.h>
//#include <Stopwatch.h>

LatchSystem::LatchSystem( AtlantisSubsystemDirector *_director, const std::string &_ident, const std::string &_attachID, double latchmaxdistance, double latchmaxangle )
	: AtlantisSubsystem(_director, _ident), attachedPayload(NULL), hPayloadAttachment(NULL), hAttach(NULL), AttachID(_attachID),
	latchmaxdistance(latchmaxdistance), latchmaxangle(latchmaxangle), firstStep(true), payloadName(""), attachmentIndex(-1), lastUpdateTime(-100.0), SearchForAttachments(false)
{
}

LatchSystem::~LatchSystem()
{
}

void LatchSystem::OnPreStep(double simt, double simdt, double mjd)
{
	// handle attachment setup
	if (firstStep)
	{
		CheckForAttachedObjects();
		firstStep=false;
	}

	// if active, update list of nearby attachments
	if (SearchForAttachments)
	{
		// every 100 seconds, update list of nearby payloads
		double Update = simt - lastUpdateTime;
		if ((Update >= 100.0) || (Update < 0.0))
		{
			UpdateAttachmentList();
			lastUpdateTime = simt;
		}
	}

	if(attachedPayload!=NULL && !STS()->GetAttachmentStatus(hAttach))
	{
		if(PayloadIsFree())
		{
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

bool LatchSystem::AttachPayload( void )
{
	// find vessel and attachment
	UpdateAttachmentList();
	int idx = FindAttachment();
	if (idx == -1) return false;

	hPayloadAttachment = vctAttachments[idx];
	attachedPayload = vctVessels[idx];

	// needed to prevent RMS and MPMs from moving when payload they are attached to is latched to something else
	if (STS()->GetPortMPM() && (STS()->GetPortMPM() != this)) STS()->GetPortMPM()->CheckDoubleAttach( attachedPayload, true );
	if (STS()->GetStarboardMPM() && (STS()->GetStarboardMPM() != this)) STS()->GetStarboardMPM()->CheckDoubleAttach( attachedPayload, true );

	OnAttach();
	return true;
}

void LatchSystem::DetachPayload()
{
	if (attachedPayload)
	{
		// signal to RMS and MPMs that payload they are attached to has been unlatched
		if (STS()->GetPortMPM() && (STS()->GetPortMPM() != this)) STS()->GetPortMPM()->CheckDoubleAttach( attachedPayload, false );
		if (STS()->GetStarboardMPM() && (STS()->GetStarboardMPM() != this)) STS()->GetStarboardMPM()->CheckDoubleAttach( attachedPayload, false );
	}
	hPayloadAttachment = NULL;
	attachedPayload = NULL;

	STS()->DetachChildAndUpdateMass( hAttach );

	OnDetach();
	return;
}

bool LatchSystem::PayloadIsFree() const
{
	if (attachedPayload)
	{
		// if we are attached to payload, it must be 'free'
		if (STS()->GetAttachmentStatus( hAttach )) return true;
		// otherwise, loop through all attachment points on payload and check if any of them are in use
		DWORD count = attachedPayload->AttachmentCount( true );
		for (DWORD i = 0; i < count; i++)
		{
			ATTACHMENTHANDLE att = attachedPayload->GetAttachmentHandle( true, i );
			if (attachedPayload->GetAttachmentStatus( att )) return false;
		}
	}
	return true;
}

void LatchSystem::CheckForAttachedObjects()
{
	if (hAttach)
	{
		OBJHANDLE hV = STS()->GetAttachmentStatus( hAttach );
		if (hV)
		{
			// payload is attached to this Latch, set internal attachement info from attachment and ignore scenario parameters
			attachedPayload = oapiGetVesselInterface( hV );

			// find handle of attachment point on payload
			for (DWORD i = 0; i < attachedPayload->AttachmentCount( true ); i++)
			{
				ATTACHMENTHANDLE hAtt = attachedPayload->GetAttachmentHandle( true, i );
				if (attachedPayload->GetAttachmentStatus( hAtt ) == STS()->GetHandle())
				{
					hPayloadAttachment = hAtt;

					// indicate payload latched to derived classes
					OnAttach();
					break;
				}
			}
		}
		else
		{
			// payload is attached to this Latch but not exclusivly (e.g. RMS and PLB), so set internal attachment info from scenario parameters
			if ((attachmentIndex != -1) && !payloadName.empty())
			{
				hV = oapiGetVesselByName( (char*)payloadName.c_str() );
				if (hV)
				{
					attachedPayload = oapiGetVesselInterface( hV );
					hPayloadAttachment = attachedPayload->GetAttachmentHandle( true, attachmentIndex );
					
					// needed to prevent RMS and MPMs from moving when payload they are attached to is latched to something else
					if (STS()->GetPortMPM() && (STS()->GetPortMPM() != this)) STS()->GetPortMPM()->CheckDoubleAttach( attachedPayload, true );
					if (STS()->GetStarboardMPM() && (STS()->GetStarboardMPM() != this)) STS()->GetStarboardMPM()->CheckDoubleAttach( attachedPayload, true );

					// indicate payload latched to derived classes
					OnAttach();
				}
			}
		}
	}
	return;
}

void LatchSystem::UpdateAttachmentList( void )
{
	vctVessels.clear();
	vctAttachments.clear();

	VECTOR3 pos;
	VECTOR3 dir;
	VECTOR3 rot;
	VECTOR3 gposAttach;// global position of (local) attachment
	STS()->GetAttachmentParams( hAttach, pos, dir, rot );
	STS()->Local2Global( pos, gposAttach );

	DWORD vesselCount = oapiGetVesselCount();
	for (DWORD i = 0; i < vesselCount; i++)
	{
		OBJHANDLE hV = oapiGetVesselByIndex( i );
		if (hV != STS()->GetHandle())// exclude OV
		{
			VECTOR3 gpos;
			oapiGetGlobalPos( hV, &gpos );
			if (dist( gpos, gposAttach ) < oapiGetSize( hV ))// only keep vessels that are close enough to have the local attachment inside their size radius
			{
				VESSEL* v = oapiGetVesselInterface( hV );
				DWORD nAttach = v->AttachmentCount( true );
				for (DWORD j = 0; j < nAttach; j++)
				{
					ATTACHMENTHANDLE hAtt = v->GetAttachmentHandle( true, j );
					const char* id = v->GetAttachmentId( hAtt );
					if (!strncmp( id, AttachID.c_str(), AttachID.length() + 1 ))// only allow attachments with compatible attachment id
					{
						vctVessels.push_back( v );
						vctAttachments.push_back( hAtt );
					}
				}
			}
		}
	}
	return;
}

int LatchSystem::FindAttachment( void ) const
{
	VECTOR3 pos;
	VECTOR3 dir;
	VECTOR3 rot;
	VECTOR3 gposAttach;// global position of (local) attachment
	VECTOR3 gdirAttach;// global direction of (local) attachment
	STS()->GetAttachmentParams( hAttach, pos, dir, rot );
	STS()->Local2Global( pos, gposAttach );
	STS()->GlobalRot( dir, gdirAttach );

	for (unsigned int i = 0; i < vctVessels.size(); i++)
	{
		VECTOR3 gpos;// global direction of target attachment
		vctVessels[i]->GetAttachmentParams( vctAttachments[i], pos, dir, rot );
		vctVessels[i]->Local2Global( pos, gpos );

		double attachdistance = dist( gpos, gposAttach );
		if (attachdistance < latchmaxdistance)
		{
			VECTOR3 gdir;// global direction of target attachment
			vctVessels[i]->GlobalRot( dir, gdir );

			double attachangle = fabs( PI - acos( range( -1.0, dotp( gdir, gdirAttach ), 1.0 ) ) );
			if (attachangle < latchmaxangle)
			{
				// passed all checks, return index
				return i;
			}
		}
	}
	return -1;
}
