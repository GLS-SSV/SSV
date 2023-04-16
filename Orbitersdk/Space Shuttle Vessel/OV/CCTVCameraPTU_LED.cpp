#include "CCTVCameraPTU_LED.h"
#include "ExternalLight.h"


constexpr double LIGHT_RANGE = 90.0;// [m]
constexpr double LIGHT_OFFSET = 0.226378;// offset between camera position and LED position [m]
constexpr float LIGHT_UV_OFFSET = 143.0 / 512;// [1]

const double LIGHT_UMBRA_ANGLE = 20.0 * RAD;// [rad]
const double LIGHT_PENUMBRA_ANGLE = LIGHT_UMBRA_ANGLE + (15.0 * RAD);// [rad]

constexpr double LIGHT_ATT0 = 1.0;// [1]
constexpr double LIGHT_ATT1 = 0.1;// [1]
constexpr double LIGHT_ATT2 = 0.00001;// [1]


CCTVCameraPTU_LED::CCTVCameraPTU_LED( Atlantis* sts, const VECTOR3& pos ) : CCTVCameraPTU( sts, pos )
{
	light = new ExternalLight( sts, this->pos + (dir * LIGHT_OFFSET), dir, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, LED );
	return;
}

CCTVCameraPTU_LED::~CCTVCameraPTU_LED( void )
{
	delete light;
	return;
}

void CCTVCameraPTU_LED::TimeStep( const double dt )
{
	CCTVCameraPTU::TimeStep( dt );

	light->UpdateLightPosition( dynamic_cast<Atlantis*>(v)->GetOrbiterCoGOffset() + pos + (dir * LIGHT_OFFSET) );
	light->UpdateLightDirection( dir );
	light->TimeStep( dt );
	return;
}

void CCTVCameraPTU_LED::VisualCreated( void )
{
	light->VisualCreated();
	return;
}

void CCTVCameraPTU_LED::ConnectLEDPower( discsignals::DiscreteBundle* Bundle, const unsigned short Line )
{
	light->DefineState( 1, LIGHT_UV_OFFSET, 0.0f, 1.0f, Bundle, Line );
	return;
}

void CCTVCameraPTU_LED::DefineMeshGroup( UINT _mesh, UINT _grpIndex )
{
	light->DefineMeshGroup( _mesh, _grpIndex );
	return;
}
