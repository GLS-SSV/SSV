/******* SSV File Modification Notice *******
Date         Developer
2020/04/23   GLS
2020/05/06   GLS
2020/05/13   GLS
2020/05/14   GLS
2020/05/20   GLS
2020/05/21   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/24   GLS
2020/10/10   GLS
2021/01/19   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/03/06   GLS
2022/05/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "Payload_MPM.h"
#include "../CommonDefs.h"
#include "meshres_MPM_Port.h"
#include "Atlantis.h"
#include <MathSSV.h>


const double MAX_ATTACHMENT_DIST = 0.1;// [m]
const double MAX_ATTACHMENT_ANGLE = 5.0 * RAD;// [rad]

const VECTOR3 ATTACHMENT_POS = _V( 2.6618946, 0.480061, 1.09833 );// Xo+911.05, Yo-104.799, Zo+435.715
const VECTOR3 ATTACHMENT_DIR = _V( 0.333478, 0.942758, 0.0 );
const VECTOR3 ATTACHMENT_ROT = _V(  0.0, 0.0, 1.0 );


Payload_MPM::Payload_MPM( AtlantisSubsystemDirector *_director, const mission::PayloadMPM& plmpm, bool portside )
	: MPM( _director, "STBD_MPM_PL", "MPM", portside, MAX_ATTACHMENT_DIST, MAX_ATTACHMENT_ANGLE ), plmpm(plmpm)
{
	// TODO pedestal configuration validity checks
	// TODO custom attachment location
	// TODO custom MRL connections

	attach_point[0] = ATTACHMENT_POS;
	attach_point[1] = ATTACHMENT_POS + ATTACHMENT_DIR;

	mesh_index_pedestal_shoulder = MESH_UNDEFINED;
	mesh_index_pedestal_forward = MESH_UNDEFINED;
	mesh_index_pedestal_mid = MESH_UNDEFINED;
	mesh_index_pedestal_aft = MESH_UNDEFINED;

	hMesh_Pedestal_Shoulder = plmpm.Shoulder.IsUsed ? oapiLoadMeshGlobal( plmpm.Shoulder.mesh.c_str() ) : NULL;
	hMesh_Pedestal_Forward = plmpm.Forward.IsUsed ? oapiLoadMeshGlobal( plmpm.Forward.mesh.c_str() ) : NULL;
	hMesh_Pedestal_Mid = plmpm.Mid.IsUsed ? oapiLoadMeshGlobal( plmpm.Mid.mesh.c_str() ) : NULL;
	hMesh_Pedestal_Aft = plmpm.Aft.IsUsed ? oapiLoadMeshGlobal( plmpm.Aft.mesh.c_str() ) : NULL;
}

Payload_MPM::~Payload_MPM()
{
}

void Payload_MPM::Realize()
{
	MPM::Realize();

	AddMesh();
	DefineAnimations();
	return;
}

void Payload_MPM::AddMesh( void )
{
	VECTOR3 ofs;

	if (plmpm.Shoulder.IsUsed)
	{
		ofs = STS()->GetOrbiterCoGOffset() + (portside ? PEDESTAL_OFFSET_PORT_SHOULDER : PEDESTAL_OFFSET_STBD_SHOULDER);
		mesh_index_pedestal_shoulder = STS()->AddMesh( hMesh_Pedestal_Shoulder, &ofs );
		STS()->SetMeshVisibilityMode( mesh_index_pedestal_shoulder, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}

	if (plmpm.Forward.IsUsed)
	{
		ofs = STS()->GetOrbiterCoGOffset() + (portside ? PEDESTAL_OFFSET_PORT_FORWARD : PEDESTAL_OFFSET_STBD_FORWARD);
		mesh_index_pedestal_forward = STS()->AddMesh( hMesh_Pedestal_Forward, &ofs );
		STS()->SetMeshVisibilityMode( mesh_index_pedestal_forward, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}

	if (plmpm.Mid.IsUsed)
	{
		ofs = STS()->GetOrbiterCoGOffset() + (portside ? PEDESTAL_OFFSET_PORT_MID : PEDESTAL_OFFSET_STBD_MID);
		mesh_index_pedestal_mid = STS()->AddMesh( hMesh_Pedestal_Mid, &ofs );
		STS()->SetMeshVisibilityMode( mesh_index_pedestal_mid, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}

	if (plmpm.Aft.IsUsed)
	{
		ofs = STS()->GetOrbiterCoGOffset() + (portside ? PEDESTAL_OFFSET_PORT_AFT : PEDESTAL_OFFSET_STBD_AFT);
		mesh_index_pedestal_aft = STS()->AddMesh( hMesh_Pedestal_Aft, &ofs );
		STS()->SetMeshVisibilityMode( mesh_index_pedestal_aft, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}
	return;
}

void Payload_MPM::DefineAnimations( void )
{
	// upper pedestals
	if (plmpm.Shoulder.IsUsed)
	{
		MGROUP_TRANSFORM* pUpperPedestal = new MGROUP_TRANSFORM( mesh_index_pedestal_shoulder, NULL, 0 );
		STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestal, mpmparent );
		SaveAnimation( pUpperPedestal );
	}
	if (plmpm.Forward.IsUsed)
	{
		MGROUP_TRANSFORM* pUpperPedestal = new MGROUP_TRANSFORM( mesh_index_pedestal_forward, NULL, 0 );
		STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestal, mpmparent );
		SaveAnimation( pUpperPedestal );
	}
	if (plmpm.Mid.IsUsed)
	{
		MGROUP_TRANSFORM* pUpperPedestal = new MGROUP_TRANSFORM( mesh_index_pedestal_mid, NULL, 0 );
		STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestal, mpmparent );
		SaveAnimation( pUpperPedestal );
	}
	if (plmpm.Aft.IsUsed)
	{
		MGROUP_TRANSFORM* pUpperPedestal = new MGROUP_TRANSFORM( mesh_index_pedestal_aft, NULL, 0 );
		STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestal, mpmparent );
		SaveAnimation( pUpperPedestal );
	}

	// attachment
	MGROUP_TRANSFORM* pMPMAttachment = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(attach_point), 2 );
	STS()->AddAnimationComponent( anim_mpm, 0, 1, pMPMAttachment, mpmparent );
	SaveAnimation( pMPMAttachment );
	return;
}

void Payload_MPM::VisualCreated( VISHANDLE vis )
{
	DEVMESHHANDLE hMPMDevMesh = STS()->GetDevMesh( vis, mesh_index_MPM );
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 3;

	// hide unused pedestal bases
	if (!plmpm.Shoulder.IsUsed)
	{
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_SHOULDER_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_SHOULDER_MPM_Port, &grpSpec );
	}
	if (!plmpm.Forward.IsUsed)
	{
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_FORWARD_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_FORWARD_MPM_Port, &grpSpec );
	}
	if (!plmpm.Mid.IsUsed)
	{
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_MID_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_MID_MPM_Port, &grpSpec );
	}
	if (!plmpm.Aft.IsUsed)
	{
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_AFT_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_AFT_MPM_Port, &grpSpec );
	}
	return;
}

void Payload_MPM::CreateAttachment( void )
{
	if (!hAttach) hAttach = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + ATTACHMENT_POS, ATTACHMENT_DIR, ATTACHMENT_ROT, "OBSS" );
	return;
}

void Payload_MPM::UpdateAttachment( void )
{
	if (hAttach) STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + attach_point[0], attach_point[1] - attach_point[0], ATTACHMENT_ROT );
	return;
}

void Payload_MPM::OnPreStep(double simt, double simdt, double mjd)
{
	// if we haven't found the PL yet, check for any new vessels added
	if(vhPLAttach.empty()) FindPLAttachments();

	if (CheckRTL()) SetRFL( true, true, true );
	else SetRFL( false, false, false );

	MPM::OnPreStep(simt, simdt, mjd);
	return;
}

void Payload_MPM::OnPostStep(double simt, double simdt, double mjd)
{
	// check for SimT is needed to ensure PL attachment point is positioned correctly
	if(mpm_moved)
	{
		UpdateAttachment();
		mpm_moved=false;
	}
}

void Payload_MPM::OnSaveState(FILEHANDLE scn) const
{
	MPM::OnSaveState(scn);
}

void Payload_MPM::OnMRLLatched()
{
	if(!hPayloadAttachment) AttachPL();
}

void Payload_MPM::OnMRLReleased()
{
	if(hPayloadAttachment) DetachPayload();
}

void Payload_MPM::AttachPL()
{
	if(!hPayloadAttachment) {
		int index=FindPL();
		if(index!=-1) {
			// if PL is attached to RMS, detach it so it can be attached to MPM
			//STS()->pRMS->Detach(vpPL[index]);
			AttachPayload(oapiGetVesselInterface(vhPL[index]), vhPLAttach[index]);
		}
	}
	//if(index!=-1) STS()->AttachChild(vpPL[index]->GetHandle(), hAttach, vhPLAttach[index]);
}

void Payload_MPM::FindPLAttachments()
{
	//iterate through all vessels and search for attachments with 'OS' string
	DWORD vesselCount=oapiGetVesselCount();
	for (DWORD i = 0; i < vesselCount; i++) {
		OBJHANDLE hV = oapiGetVesselByIndex (i);
		if (hV != STS()->GetHandle()) // we don't want to grapple ourselves ...
		{
			VESSEL* v=oapiGetVesselInterface(hV);
			DWORD attachCount = v->AttachmentCount (true);
			for (DWORD j = 0; j < attachCount; j++) { // now scan all attachment points of the candidate
				ATTACHMENTHANDLE hAtt = v->GetAttachmentHandle (true, j);
				const char *id = v->GetAttachmentId (hAtt);
				if(!_strnicmp(id, "MPM", 3)) {
					vhPL.push_back(hV);
					vhPLAttach.push_back(hAtt);
				}
			}
		}
	}
}

int Payload_MPM::FindPL() const
{
	VECTOR3 gpos, gdir, gattach, pos, dir, rot, gattachdir;
	STS()->Local2Global (STS()->GetOrbiterCoGOffset()+attach_point[0], gattach);  // global position of attachment point
	STS()->GlobalRot(attach_point[1]-attach_point[0], gattachdir);
	//loop through PL attachments and check each one
	for(unsigned int i=0;i<vhPLAttach.size();i++) {
		//VESSEL* v=vpPL[i];
		VESSEL* v=oapiGetVesselInterface(vhPL[i]);
		v->GetAttachmentParams (vhPLAttach[i], pos, dir, rot);
		v->Local2Global (pos, gpos);
		//sprintf_s(oapiDebugString(), 256, "%s Dist: %f", v->GetName(), dist(gpos, gattach));
		if (dist (gpos, gattach) < MAX_ATTACHMENT_DIST) {
			v->GlobalRot(dir, gdir);
			//sprintf_s(oapiDebugString(), 256, "Attitude difference: %f", fabs(180-DEG*acos(dotp(gdir, gattachdir))));
			if(fabs(PI-acos(range(-1.0, dotp(gdir, gattachdir), 1.0))) < MAX_ATTACHMENT_ANGLE) {  // found one!
				return i;
			}
		}
	}

	return -1;
}

bool Payload_MPM::CheckRTL() const
{
	//if PL is latched to MPMs, RTL switches should be set
	if(STS()->GetAttachmentStatus(hAttach)) return true;

	return (FindPL()!=-1);
}
