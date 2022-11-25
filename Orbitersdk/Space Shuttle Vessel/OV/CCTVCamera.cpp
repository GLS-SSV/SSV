#include "CCTVCamera.h"
#include "ParameterValues.h"


const static char* MESHNAME = "TODO";


CCTVCamera::CCTVCamera( Atlantis* const sts, const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top ):BasicCamera( pos, dir, top, MAX_CAM_ZOOM, MIN_CAM_ZOOM, PLB_CAM_ZOOM_RATE ),
	sts(sts)
{
	//keel, ODS, EE;
	return;
}

CCTVCamera::~CCTVCamera()
{
	return;
}

void CCTVCamera::TimeStep( const double dt )
{
	BasicCamera::TimeStep( dt );
	return;
}

void CCTVCamera::AddMesh( void )
{
	hMesh = oapiLoadMeshGlobal( MESHNAME );
	VECTOR3 ofs = sts->GetOrbiterCoGOffset() + pos;
	mesh_idx = sts->AddMesh( hMesh, &ofs );
	sts->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void CCTVCamera::DefineAnimations( const double rotZo, const double rotYo, const ANIMATIONCOMPONENT_HANDLE baseparent )
{
	// base orientation
	MGROUP_ROTATE* CAMERAZO = new MGROUP_ROTATE( mesh_idx, NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(rotZo * RAD) );
	anim_Zo = sts->CreateAnimation( 0.0 );
	ANIMATIONCOMPONENT_HANDLE parent = sts->AddAnimationComponent( anim_Zo, 0.0, 1.0, CAMERAZO, baseparent );
	sts->SetAnimation( anim_Zo, 1.0 );

	MGROUP_ROTATE* CAMERAYO = new MGROUP_ROTATE( mesh_idx, NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(rotYo * RAD) );
	anim_Yo = sts->CreateAnimation( 0.0 );
	sts->AddAnimationComponent( anim_Yo, 0.0, 1.0, CAMERAYO, parent );
	sts->SetAnimation( anim_Yo, 1.0 );
	return;
}
