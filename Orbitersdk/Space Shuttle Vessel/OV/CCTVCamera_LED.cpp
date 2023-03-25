#include "CCTVCamera_LED.h"
#include "ExternalLight.h"


constexpr double LIGHT_RANGE = 20.0;// [m]
constexpr double LIGHT_OFFSET = 0.226378;// offset between camera position and LED position [m]
constexpr float LIGHT_UV_OFFSET = 143.0 / 512;// [1]

const double LIGHT_UMBRA_ANGLE = 85.0 * RAD;// [rad]
const double LIGHT_PENUMBRA_ANGLE = LIGHT_UMBRA_ANGLE + (25.0 * RAD);// [rad]

constexpr double LIGHT_ATT0 = 0.5;// [1]
constexpr double LIGHT_ATT1 = 0.0;// [1]
constexpr double LIGHT_ATT2 = 0.05;// [1]

constexpr double LED_OFFSET = 0.1;// distance from camera center to LEDs [m]


CCTVCamera_LED::CCTVCamera_LED( Atlantis* sts, const VECTOR3& pos ) : CCTVCamera( sts, pos )
{
	light = new ExternalLight( sts, this->pos + (dir * LED_OFFSET), dir, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, LED );
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

	light->UpdateLightPosition( dynamic_cast<Atlantis*>(v)->GetOrbiterCoGOffset() + pos + (dir * LIGHT_OFFSET) );
	light->UpdateLightDirection( dir );
	light->TimeStep( dt );
	return;
}

void CCTVCamera_LED::VisualCreated( void )
{
	light->VisualCreated();
	return;
}

void CCTVCamera_LED::ConnectLEDPower( discsignals::DiscreteBundle* Bundle, const unsigned short Line )
{
	light->DefineState( 1, LIGHT_UV_OFFSET, 0.0f, 1.0f, Bundle, Line );
	return;
}

void CCTVCamera_LED::DefineMeshGroup( UINT _mesh, UINT _grpIndex )
{
	light->DefineMeshGroup( _mesh, _grpIndex );
	return;
}
