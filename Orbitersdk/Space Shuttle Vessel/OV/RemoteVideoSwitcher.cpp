#include "RemoteVideoSwitcher.h"


RemoteVideoSwitcher::RemoteVideoSwitcher( const  bool port, VideoSource* Elbow, VideoSource* Wrist, Atlantis* sts ) : VideoSource(), Elbow( Elbow ), Wrist( Wrist ), selWrist(false)
{
	discsignals::DiscreteBundle* pBundle = sts->BundleManager()->CreateBundle( port ? "VIDEOSWITCHER_PORT_INTERNAL" : "VIDEOSWITCHER_STBD_INTERNAL", 16 );

	Elbow->ConnectPowerOnOff( pBundle, 0 );
	Wrist->ConnectPowerOnOff( pBundle, 1 );
	return;
}

RemoteVideoSwitcher::~RemoteVideoSwitcher( void )
{
	return;
}

void RemoteVideoSwitcher::TimeStep( void )
{
	if (selWrist == dipWrist) return;

	// update
	selWrist = !selWrist;

	// update connections
	if (selWrist)
	{
		// TODO
	}
	else
	{
		// TODO
	}
	return;
}

void RemoteVideoSwitcher::SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout )
{
	if (selWrist)
	{
		Wrist->SetCommands( panleft, panright, tiltup, tiltdown, pantiltclk, zoomin, zoomout );
	}
	else
	{
		Elbow->SetCommands( panleft, panright, tiltup, tiltdown, pantiltclk, zoomin, zoomout );
	}
	return;
}

bool RemoteVideoSwitcher::GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom, double& pan, double& tilt ) const
{
	if (selWrist)
	{
		return Wrist->GetPhysicalData( pos, dir, top, zoom, pan, tilt );
	}
	else
	{
		return Elbow->GetPhysicalData( pos, dir, top, zoom, pan, tilt );
	}
}

void RemoteVideoSwitcher::ConnectSelSwitch( discsignals::DiscreteBundle* Bundle, const unsigned short portWrist )
{
	dipWrist.Connect( Bundle, portWrist );
	return;
}
