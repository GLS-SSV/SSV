#include "CCTVCamera_LED.h"
#include "ExternalLight.h"


constexpr double LIGHT_RANGE = 20.0;// [m]

const double LIGHT_UMBRA_ANGLE = 90.0 * RAD;// [rad]
const double LIGHT_PENUMBRA_ANGLE = LIGHT_UMBRA_ANGLE + (25.0 * RAD);// [rad]

constexpr double LIGHT_ATT0 = 0.5;// [1]
constexpr double LIGHT_ATT1 = 0.0;// [1]
constexpr double LIGHT_ATT2 = 0.05;// [1]

constexpr double LED_OFFSET = 0.1;// distance from camera center to LEDs [m]


CCTVCamera_LED::CCTVCamera_LED( Atlantis* sts, const VECTOR3& pos ) : CCTVCamera( sts, pos )
{
	light = new ExternalLight( sts, pos + (dir * LED_OFFSET), dir, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, LED );
	return;
}

CCTVCamera_LED::~CCTVCamera_LED( void )
{
	delete light;
	return;
}

void CCTVCamera_LED::TimeStep( const double dt )
{
	CCTVCamera::TimeStep( dt );

	light->TimeStep( dt );
	return;
}

void CCTVCamera_LED::DefineAnimations( const UINT mesh_idx, const double rotZo, const double rotYo )
{
	CCTVCamera::DefineAnimations( mesh_idx, rotZo, rotYo );

	light->UpdateLightPosition( pos + (dir * LED_OFFSET) );
	light->UpdateLightDirection( dir );
	return;
}

void CCTVCamera_LED::SetPhysicalParams( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top )
{
	CCTVCamera::SetPhysicalParams( pos, dir, top );

	light->UpdateLightPosition( pos + (dir * LED_OFFSET) );
	light->UpdateLightDirection( dir );
	return;
}

void CCTVCamera_LED::VisualCreated( void )
{
	light->VisualCreated();
	return;
}

void CCTVCamera_LED::DefineLightMeshGroup( UINT _mesh, UINT _grpIndex )
{
	light->DefineMeshGroup( _mesh, _grpIndex );
	return;
}
