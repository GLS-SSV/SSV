#include "CCTVCameraPTU.h"
#include "ParameterValues.h"
#include <MathSSV.h>


const static char* MESHNAME = "TODO";


CCTVCameraPTU::CCTVCameraPTU( Atlantis* const sts, const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top ):CameraPTU( pos, dir, top, MAX_CAM_ZOOM, MIN_CAM_ZOOM, PLB_CAM_ZOOM_RATE, PLB_CAM_PAN_MAX, PLB_CAM_PAN_MIN, PLB_CAM_TILT_MAX, PLB_CAM_TILT_MIN, PTU_LOWRATE_SPEED, PTU_HIGHRATE_SPEED ),
	sts(sts)
{
	//ABCD, Elbow;
	return;
}

CCTVCameraPTU::~CCTVCameraPTU()
{
	return;
}

void CCTVCameraPTU::TimeStep( const double dt )
{
	CameraPTU::TimeStep( dt );

	sts->SetAnimation( anim_Pan, linterp( PLB_CAM_PAN_MIN, 0.0, PLB_CAM_PAN_MAX, 1.0, pan ) );
	sts->SetAnimation( anim_Tilt, linterp( PLB_CAM_TILT_MIN, 0.0, PLB_CAM_TILT_MAX, 1.0, tilt ) );
	return;
}

void CCTVCameraPTU::AddMesh( void )
{
	hMesh = oapiLoadMeshGlobal( MESHNAME );
	VECTOR3 ofs = sts->GetOrbiterCoGOffset() + pos;
	mesh_idx = sts->AddMesh( hMesh, &ofs );
	sts->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void CCTVCameraPTU::DefineAnimations( const double rotZo, const double rotXo, const ANIMATIONCOMPONENT_HANDLE baseparent, const UINT pan_grp, const UINT tilt_grp )
{
	// base orientation
	MGROUP_ROTATE* CAMERAZO = new MGROUP_ROTATE( mesh_idx, NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(rotZo * RAD) );
	anim_Zo = sts->CreateAnimation( 0.0 );
	ANIMATIONCOMPONENT_HANDLE parent = sts->AddAnimationComponent( anim_Zo, 0.0, 1.0, CAMERAZO, baseparent );
	sts->SetAnimation( anim_Zo, 1.0 );

	MGROUP_ROTATE* CAMERAYO = new MGROUP_ROTATE( mesh_idx, NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), static_cast<float>(rotXo * RAD) );
	anim_Xo = sts->CreateAnimation( 0.0 );
	parent = sts->AddAnimationComponent( anim_Xo, 0.0, 1.0, CAMERAYO, parent );
	sts->SetAnimation( anim_Xo, 1.0 );

	// PTU
	static UINT PanGrp[1] = {pan_grp};
	MGROUP_ROTATE* CAMERAPAN = new MGROUP_ROTATE( mesh_idx, PanGrp, 1, pos, _V( 0.0, 1.0, 0.0 ), static_cast<float>((PLB_CAM_PAN_MAX - PLB_CAM_PAN_MIN) * RAD) );
	anim_Pan = sts->CreateAnimation( 0.5 );
	parent = sts->AddAnimationComponent( anim_Pan, 0.0, 1.0, CAMERAPAN, parent );

	static UINT TiltGrp[1] = {tilt_grp};
	MGROUP_ROTATE* CAMERATILT = new MGROUP_ROTATE( mesh_idx, TiltGrp, 1, pos, _V( -1.0, 0.0, 0.0 ), static_cast<float>((PLB_CAM_TILT_MAX - PLB_CAM_TILT_MIN) * RAD) );
	anim_Tilt = sts->CreateAnimation( PLB_CAM_TILT_MIN / (PLB_CAM_TILT_MIN - PLB_CAM_TILT_MAX) );
	sts->AddAnimationComponent( anim_Tilt, 0.0, 1.0, CAMERATILT, parent );
	return;
}
