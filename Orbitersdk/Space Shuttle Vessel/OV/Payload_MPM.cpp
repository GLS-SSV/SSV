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
2022/10/29   GLS
2022/10/30   GLS
2022/11/01   GLS
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

	SetSearchForAttachments( true );// search for attachments to feed RTL
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
		oapiWriteLog( "(SSV_OV) [INFO] Hiding Payload MPM shoulder pedestal" );
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_SHOULDER_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_SHOULDER_MPM_Port, &grpSpec );
	}
	if (!plmpm.Forward.IsUsed)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding Payload MPM forward pedestal" );
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_FORWARD_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_FORWARD_MPM_Port, &grpSpec );
	}
	if (!plmpm.Mid.IsUsed)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding Payload MPM mid pedestal" );
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_MID_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_MID_MPM_Port, &grpSpec );
	}
	if (!plmpm.Aft.IsUsed)
	{
		oapiWriteLog( "(SSV_OV) [INFO] Hiding Payload MPM aft pedestal" );
		oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_AFT_MPM_Port, &grpSpec );
		oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_AFT_MPM_Port, &grpSpec );
	}
	return;
}

void Payload_MPM::CreateAttachment( void )
{
	if (!hAttach) hAttach = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + ATTACHMENT_POS, ATTACHMENT_DIR, ATTACHMENT_ROT, "SSV_MPM" );
	return;
}

void Payload_MPM::UpdateAttachment( void )
{
	if (hAttach) STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + attach_point[0], attach_point[1] - attach_point[0], ATTACHMENT_ROT );
	return;
}

void Payload_MPM::OnPreStep(double simt, double simdt, double mjd)
{
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

void Payload_MPM::OnMRLLatched( void )
{
	AttachPayload();
	return;
}

void Payload_MPM::OnMRLReleased( void )
{
	DetachPayload();
	return;
}

bool Payload_MPM::CheckRTL() const
{
	// if PL is latched, RTL switches should be set
	if (IsLatched()) return true;

	return (FindAttachment() != -1);
}
