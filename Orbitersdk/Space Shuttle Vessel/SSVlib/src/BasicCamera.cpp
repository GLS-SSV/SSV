#include <BasicCamera.h>
#include <MathSSV.h>


BasicCamera::BasicCamera( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top, const double zoommax, const double zoommin, const double zoomrate ):
	pos(pos), dir(dir), top(top), zoom(zoommin), zoommax(zoommax), zoommin(zoommin), zoomrate(zoomrate), updated(true)
{
	return;
}

BasicCamera::~BasicCamera( void )
{
	return;
}

void BasicCamera::SetPhysicalParams( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top )
{
	this->pos = pos;
	this->dir = dir;
	this->top = top;
	updated = true;
	return;
}

void BasicCamera::Connect( discsignals::DiscreteBundle* bundle, const unsigned short power, const unsigned short poweronoff, const unsigned short heaterpower, const unsigned short zoomin, const unsigned short zoomout )
{
	Power.Connect( bundle, power );
	PowerOnOffCmd.Connect( bundle, poweronoff );
	HeaterPower.Connect( bundle, heaterpower );
	ZoomInCmd.Connect( bundle, zoomin );
	ZoomOutCmd.Connect( bundle, zoomout );
	return;
}

bool BasicCamera::GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom ) const
{
	pos = this->pos;
	dir = this->dir;
	top = this->top;
	zoom = this->zoom;
	return updated;
}

void BasicCamera::TimeStep( const double dt )
{
	updated = false;

	double motion = ZoomInCmd.IsSet() - ZoomOutCmd.IsSet();
	if ((motion != 0.0) && (zoom != zoommin) && (zoom != zoommax))
	{
		zoom = range( zoommin, zoom + (motion * zoomrate * dt), zoommax );
		updated = true;
	}
	return;
}
