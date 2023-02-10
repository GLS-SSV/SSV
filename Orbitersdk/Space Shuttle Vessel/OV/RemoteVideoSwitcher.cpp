#include "RemoteVideoSwitcher.h"
#include "CCTVCameraPTU.h"


RemoteVideoSwitcher::RemoteVideoSwitcher( const bool portside, VideoSource* Elbow, VideoSource* Wrist, Atlantis* sts ) : VideoSource(), Elbow(Elbow), Wrist(Wrist)
{
	discsignals::DiscreteBundle* pBundle = sts->BundleManager()->CreateBundle( portside ? "VIDEOSWITCHER_PORT_INTERNAL" : "VIDEOSWITCHER_STBD_INTERNAL", 16 );
	dynamic_cast<CCTVCameraPTU*>(Elbow)->ConnectPowerOnOff( pBundle, 0 );
	dynamic_cast<CCTVCamera*>(Wrist)->ConnectPowerOnOff( pBundle, 1 );
	dopPowerOnOffElbow.Connect( pBundle, 0 );
	dopPowerOnOffWrist.Connect( pBundle, 1 );
	return;
}

RemoteVideoSwitcher::~RemoteVideoSwitcher( void )
{
	return;
}

void RemoteVideoSwitcher::TimeStep( void )
{
	// route power on/off input to correct camera
	if (dipSelWrist)
	{
		dopPowerOnOffElbow.ResetLine();
		dopPowerOnOffWrist.SetLine( dipPowerOnOff.GetVoltage() );
	}
	else
	{
		dopPowerOnOffElbow.SetLine( dipPowerOnOff.GetVoltage() );
		dopPowerOnOffWrist.ResetLine();
	}
	return;
}

void RemoteVideoSwitcher::SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout )
{
	if (dipSelWrist)
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
	if (dipSelWrist)
	{
		return Wrist->GetPhysicalData( pos, dir, top, zoom, pan, tilt );
	}
	else
	{
		return Elbow->GetPhysicalData( pos, dir, top, zoom, pan, tilt );
	}
}

void RemoteVideoSwitcher::ConnectPowerOnOff( discsignals::DiscreteBundle* Bundle, const unsigned short OnOff )
{
	dipPowerOnOff.Connect( Bundle, OnOff );
	return;
}

void RemoteVideoSwitcher::ConnectSelSwitch( discsignals::DiscreteBundle* Bundle, const unsigned short portWrist )
{
	dipSelWrist.Connect( Bundle, portWrist );
	return;
}
