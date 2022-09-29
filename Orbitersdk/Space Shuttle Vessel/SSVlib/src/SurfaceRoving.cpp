/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/06/16   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "SurfaceRoving.h"
#include <MathSSV.h>


SurfaceRoving::SurfaceRoving( VESSEL* v, double wheelbase, double track, double height ):
	v(v),
	wheelbase(wheelbase),
	track(track),
	height(height)
{
}

SurfaceRoving::~SurfaceRoving( void )
{
}

void SurfaceRoving::SetHeight( double height )
{
	this->height = height;
	return;
}

void SurfaceRoving::Move( double dt, double speed, double forward_steering, double rear_steering )
{
	//if (speed == 0.0) return;// stopped

	double lat_cur = 0.0;
	double lon_cur = 0.0;
	double hdg_cur = 0.0;
	double rad_cur = 0.0;
	double lat_new = 0.0;
	double lon_new = 0.0;
	double hdg_new = 0.0;
	double rad_new = 0.0;
	VESSELSTATUS2 vs;
	OBJHANDLE gravref = v->GetSurfaceRef();

	// get state
	vs.version = 2;
	v->GetStatusEx( &vs );
	lat_cur = vs.surf_lat;
	lon_cur = vs.surf_lng;
	hdg_cur = vs.surf_hdg;

	// convert steering to RAD and limit to +/-90º
	forward_steering = range( -PI05, forward_steering * RAD, PI05 );
	rear_steering = range( -PI05, rear_steering * RAD, PI05 );

	// get current radius
	rad_cur = oapiGetSize( gravref ) + oapiSurfaceElevation( gravref, lon_cur, lat_cur );

	// calc new vehicle heading and position
	if (forward_steering == rear_steering)
	{
		// wheels turned in same direction, vehicle direction doesn't change (also for oblique steer)
		// calc direction of motion
		VECTOR3 dir = Normalize( _V( sin( forward_steering + hdg_cur ), cos( lat_cur ) * cos( forward_steering + hdg_cur ), 0.0 ) );

		lat_new = lat_cur + ((dir.y * speed * dt) / rad_cur);
		lon_new = lon_cur + ((dir.x * speed * dt) / rad_cur);
		hdg_new = hdg_cur;
	}
	else
	{
		// wheels turned in different directions, vehicle turns
		// intercept point
		double x = wheelbase / (tan( forward_steering ) - tan( rear_steering ));
		double y = (tan( -rear_steering ) * x) + (wheelbase * 0.5);
		// calc radius
		double r = sqrt( (x * x) + (y * y) );
		// circle turn angle
		double theta = (speed * dt) / r;
		// calc direction of motion
		VECTOR3 dir = Normalize( _V( sin( (sign( x ) * theta) + hdg_cur ), cos( lat_cur ) * cos( (sign( x ) * theta) + hdg_cur ), 0.0 ) );

		hdg_new = hdg_cur + (sign( x ) * theta);
		lat_new = lat_cur + ((dir.y * 2.0 * r * sin( theta * 0.5 )) / rad_cur);
		lon_new = lon_cur + ((dir.x * 2.0 * r * sin( theta * 0.5 )) / rad_cur);
	}

	// bound heading
	while (hdg_new > PI2) hdg_new -= PI2;
	while (hdg_new < 0.0) hdg_new += PI2;

	// get new radius
	rad_new = oapiGetSize( gravref ) + oapiSurfaceElevation( gravref, lon_new, lat_new );

	// calc new vehicle attitude
	double pitch = 0.0;
	double roll = 0.0;

	double FL_lat = lat_new + ((wheelbase * 0.5 * cos( hdg_new )) + (track * 0.5 * sin( hdg_new ))) / rad_new;
	double FL_lon = lon_new + ((wheelbase * 0.5 * sin( hdg_new )) + (-track * 0.5 * cos( hdg_new ))) / rad_new;
	double FL_elev = oapiSurfaceElevation( gravref, FL_lon, FL_lat );

	double FR_lat = lat_new + ((wheelbase * 0.5 * cos( hdg_new )) + (-track * 0.5 * sin( hdg_new ))) / rad_new;
	double FR_lon = lon_new + ((wheelbase * 0.5 * sin( hdg_new )) + (track * 0.5 * cos( hdg_new ))) / rad_new;
	double FR_elev = oapiSurfaceElevation( gravref, FR_lon, FR_lat );

	double RL_lat = lat_new + ((-wheelbase * 0.5 * cos( hdg_new )) + (track * 0.5 * sin( hdg_new ))) / rad_new;
	double RL_lon = lon_new + ((-wheelbase * 0.5 * sin( hdg_new )) + (-track * 0.5 * cos( hdg_new ))) / rad_new;
	double RL_elev = oapiSurfaceElevation( gravref, RL_lon, RL_lat );

	double RR_lat = lat_new + ((-wheelbase * 0.5 * cos( hdg_new )) + (-track * 0.5 * sin( hdg_new ))) / rad_new;
	double RR_lon = lon_new + ((-wheelbase * 0.5 * sin( hdg_new )) + (track * 0.5 * cos( hdg_new ))) / rad_new;
	double RR_elev = oapiSurfaceElevation( gravref, RR_lon, RR_lat );

	pitch = atan2( (FL_elev + FR_elev - RL_elev - RR_elev) * 0.5, wheelbase );
	roll = atan2( (FR_elev + RR_elev - FL_elev - RL_elev) * 0.5, track );

	// change in attitude due to position and heading change
	MATRIX3 rot1 = rotm( _V( 0.0, 1.0, 0.0 ), (90.0 * RAD) - lon_new );
	MATRIX3 rot2 = rotm( _V( 1.0, 0.0, 0.0 ), -lat_new );
	MATRIX3 rot3 = rotm( _V( 0.0, 0.0, 1.0 ), (180.0 * RAD) + hdg_new );

	// change in attitude due to terrain
	MATRIX3 rot4 = rotm( _V( 1.0, 0.0, 0.0 ), (90.0 * RAD) - pitch );
	MATRIX3 rot5 = rotm( _V( 0.0, 0.0, 1.0 ), roll );

	MATRIX3 RotMatrix_Def = mul( rot1, mul( rot2, mul( rot3, mul( rot4, rot5 ) ) ) );
	vs.arot.x = atan2( RotMatrix_Def.m23, RotMatrix_Def.m33 );
	vs.arot.y = -asin( RotMatrix_Def.m13 );
	vs.arot.z = atan2( RotMatrix_Def.m12, RotMatrix_Def.m11 );

	vs.vrot.x = height;


	// set state
	vs.surf_lng = lon_new;
	vs.surf_lat = lat_new;
	vs.surf_hdg = hdg_new;
	vs.status = 1;
	v->DefSetStateEx( &vs );
	return;
}

void SurfaceRoving::Move_Crab( double dt, double speed )
{
	//if (speed == 0.0) return;// stopped

	double hdg_cur = 0.0;
	double hdg_new = 0.0;
	double rad_new = 0.0;
	VESSELSTATUS2 vs;
	OBJHANDLE gravref = v->GetSurfaceRef();

	// get state
	vs.version = 2;
	v->GetStatusEx( &vs );
	hdg_cur = vs.surf_hdg;

	// calc new vehicle heading
	// calc radius
	double r = sqrt( (wheelbase * wheelbase) + (track * track) );
	// circle turn angle
	double theta = (speed * dt) / r;

	hdg_new = hdg_cur + theta;

	// bound heading
	while (hdg_new > PI2) hdg_new -= PI2;
	while (hdg_new < 0.0) hdg_new += PI2;

	// get new radius
	rad_new = oapiGetSize( gravref ) + oapiSurfaceElevation( gravref, vs.surf_lng, vs.surf_lat );

	// calc new vehicle attitude
	double pitch = 0.0;
	double roll = 0.0;

	double FL_lat = vs.surf_lat + ((wheelbase * 0.5 * cos( hdg_new )) + (track * 0.5 * sin( hdg_new ))) / rad_new;
	double FL_lon = vs.surf_lng + ((wheelbase * 0.5 * sin( hdg_new )) + (-track * 0.5 * cos( hdg_new ))) / rad_new;
	double FL_elev = oapiSurfaceElevation( gravref, FL_lon, FL_lat );

	double FR_lat = vs.surf_lat + ((wheelbase * 0.5 * cos( hdg_new )) + (-track * 0.5 * sin( hdg_new ))) / rad_new;
	double FR_lon = vs.surf_lng + ((wheelbase * 0.5 * sin( hdg_new )) + (track * 0.5 * cos( hdg_new ))) / rad_new;
	double FR_elev = oapiSurfaceElevation( gravref, FR_lon, FR_lat );

	double RL_lat = vs.surf_lat + ((-wheelbase * 0.5 * cos( hdg_new )) + (track * 0.5 * sin( hdg_new ))) / rad_new;
	double RL_lon = vs.surf_lng + ((-wheelbase * 0.5 * sin( hdg_new )) + (-track * 0.5 * cos( hdg_new ))) / rad_new;
	double RL_elev = oapiSurfaceElevation( gravref, RL_lon, RL_lat );

	double RR_lat = vs.surf_lat + ((-wheelbase * 0.5 * cos( hdg_new )) + (-track * 0.5 * sin( hdg_new ))) / rad_new;
	double RR_lon = vs.surf_lng + ((-wheelbase * 0.5 * sin( hdg_new )) + (track * 0.5 * cos( hdg_new ))) / rad_new;
	double RR_elev = oapiSurfaceElevation( gravref, RR_lon, RR_lat );

	pitch = atan2( (FL_elev + FR_elev - RL_elev - RR_elev) * 0.5, wheelbase );
	roll = atan2( (FR_elev + RR_elev - FL_elev - RL_elev) * 0.5, track );

	// change in attitude due to position and heading change
	MATRIX3 rot1 = rotm( _V( 0.0, 1.0, 0.0 ), (90.0 * RAD) - vs.surf_lng );
	MATRIX3 rot2 = rotm( _V( 1.0, 0.0, 0.0 ), -vs.surf_lat );
	MATRIX3 rot3 = rotm( _V( 0.0, 0.0, 1.0 ), (180.0 * RAD) + hdg_new );

	// change in attitude due to terrain
	MATRIX3 rot4 = rotm( _V( 1.0, 0.0, 0.0 ), (90.0 * RAD) - pitch );
	MATRIX3 rot5 = rotm( _V( 0.0, 0.0, 1.0 ), roll );

	MATRIX3 RotMatrix_Def = mul( rot1, mul( rot2, mul( rot3, mul( rot4, rot5 ) ) ) );
	vs.arot.x = atan2( RotMatrix_Def.m23, RotMatrix_Def.m33 );
	vs.arot.y = -asin( RotMatrix_Def.m13 );
	vs.arot.z = atan2( RotMatrix_Def.m12, RotMatrix_Def.m11 );

	vs.vrot.x = height;


	// set state
	vs.surf_hdg = hdg_new;
	vs.status = 1;
	v->DefSetStateEx( &vs );
}
