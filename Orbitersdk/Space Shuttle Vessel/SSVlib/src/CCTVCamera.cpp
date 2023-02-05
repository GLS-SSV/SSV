#include "CCTVCamera.h"
#include "MathSSV.h"
#include "EngConst.h"


constexpr double MIN_CAM_ZOOM = 9.0;// horizontal FOV (approx) [deg]
constexpr double MAX_CAM_ZOOM = 77.0;// horizontal FOV (approx) [deg]
constexpr double PLB_CAM_ZOOM_RATE = (MAX_CAM_ZOOM - MIN_CAM_ZOOM) / 8.0;// 8s end-to-end [deg/s]
constexpr double CAM_LENS_OFFSET = 7.0 * IN2M;// [m] lens have ~7'' offset from axis
const VECTOR3 BASE_DIR = _V( 0.0, 0.0, -1.0 );
const VECTOR3 BASE_TOP = _V( 0.0, 1.0, 0.0 );
const VECTOR3 ZoDIR = _V( 0.0, 1.0, 0.0 );
const VECTOR3 YoDIR = _V( 1.0, 0.0, 0.0 );



CCTVCamera::CCTVCamera( VESSEL* const v, const VECTOR3& pos, const std::string& meshname ):
	CAMERAZO(NULL), CAMERAYO(NULL), anim_Zo(-1), anim_Yo(-1), v(v), PanLeftCmd(false), PanRightCmd(false),
	TiltUpCmd(false), TiltDownCmd(false), PanTiltCtrlClk(false), ZoomInCmd(false), ZoomOutCmd(false), dir0(BASE_DIR), top0(BASE_TOP), pos(pos), dir(BASE_DIR),
	top(BASE_TOP), zoom(MIN_CAM_ZOOM), pan(0.0), tilt(0.0), zoommax(MAX_CAM_ZOOM), zoommin(MIN_CAM_ZOOM), zoomrate(PLB_CAM_ZOOM_RATE)
{
	//keel, ODS, EE;

	// load mesh
	mesh_idx = v->AddMesh( oapiLoadMeshGlobal( meshname.c_str() ), &pos );
	v->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

CCTVCamera::~CCTVCamera()
{
	if (CAMERAZO) delete CAMERAZO;
	if (CAMERAYO) delete CAMERAYO;
	return;
}

void CCTVCamera::LoadState( const char* line )
{
	sscanf_s( line, "%lf", &zoom );
	zoom = range( zoommin, zoom, zoommax );
	return;
}

void CCTVCamera::SaveState( char* line ) const
{
	sprintf_s( line, 256, "%.6f", zoom );
	return;
}

void CCTVCamera::SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout )
{
	PanLeftCmd = panleft;
	PanRightCmd = panright;
	TiltUpCmd = tiltup;
	TiltDownCmd = tiltdown;
	PanTiltCtrlClk = pantiltclk;
	ZoomInCmd = zoomin;
	ZoomOutCmd = zoomout;
	return;
}

bool CCTVCamera::GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom, double& pan, double& tilt ) const
{
	pos = this->pos + this->dir * CAM_LENS_OFFSET;// add lens offset
	dir = this->dir;
	top = this->top;
	zoom = this->zoom;
	pan = this->pan;
	tilt = this->tilt;
	return dipPower && dipPowerOnOff;
}

void CCTVCamera::SetPhysicalParams( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top )
{
	this->pos = pos;
	dir0 = dir;
	top0 = top;
	return;
}

void CCTVCamera::ConnectPowerOnOff( discsignals::DiscreteBundle* Bundle, const unsigned short OnOff )
{
	dipPowerOnOff.Connect( Bundle, OnOff );
	return;
}

void CCTVCamera::ConnectPowerCameraPTU( discsignals::DiscreteBundle* Bundle, const unsigned short Camera_PTU )
{
	dipPower.Connect( Bundle, Camera_PTU );
	return;
}

void CCTVCamera::ConnectPowerHeater( discsignals::DiscreteBundle* Bundle, const unsigned short Heater )
{
	dipHeater.Connect( Bundle, Heater );
	return;
}

void CCTVCamera::TimeStep( const double dt )
{
	if (!(dipPower && dipPowerOnOff)) return;

	int motion = ZoomOutCmd - ZoomInCmd;
	if (motion != 0)
	{
		zoom = range( zoommin, zoom + (motion * zoomrate * dt), zoommax );
	}

	dir = dir0;
	top = top0;

	ZoomOutCmd = false;
	ZoomInCmd = false;
	return;
}

void CCTVCamera::DefineAnimations( const double rotZo, const double rotYo, const ANIMATIONCOMPONENT_HANDLE baseparent )
{
	ANIMATIONCOMPONENT_HANDLE parent = baseparent;
	VECTOR3 tmpYoDIR = YoDIR;

	// base orientation
	if (rotZo != 0.0)
	{
		CAMERAZO = new MGROUP_ROTATE( mesh_idx, NULL, 0, _V( 0.0, 0.0, 0.0 ), ZoDIR, static_cast<float>(rotZo * RAD) );
		anim_Zo = v->CreateAnimation( 0.0 );
		parent = v->AddAnimationComponent( anim_Zo, 0.0, 1.0, CAMERAZO, baseparent );
		v->SetAnimation( anim_Zo, 1.0 );

		// update base direction and top
		MATRIX3 rmat = rotm( ZoDIR, rotZo * RAD );
		dir0 = mul( rmat, dir0 );
		dir = dir0;
		top0 = mul( rmat, top0 );
		top = top0;
		tmpYoDIR = mul( rmat, tmpYoDIR );
	}

	if (rotYo != 0.0)
	{
		CAMERAYO = new MGROUP_ROTATE( mesh_idx, NULL, 0, _V( 0.0, 0.0, 0.0 ), YoDIR, static_cast<float>(rotYo * RAD) );
		anim_Yo = v->CreateAnimation( 0.0 );
		v->AddAnimationComponent( anim_Yo, 0.0, 1.0, CAMERAYO, parent );
		v->SetAnimation( anim_Yo, 1.0 );

		// update base direction and top
		MATRIX3 rmat = rotm( tmpYoDIR, rotYo * RAD );
		dir0 = mul( rmat, dir0 );
		dir = dir0;
		top0 = mul( rmat, top0 );
		top = top0;
	}
	return;
}
