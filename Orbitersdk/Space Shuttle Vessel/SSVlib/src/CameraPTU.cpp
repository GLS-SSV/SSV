#include <CameraPTU.h>
#include <MathSSV.h>


CameraPTU::CameraPTU( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top, const double zoommax, const double zoommin, const double zoomrate, const double panmax, const double panmin, const double tiltrate, const double tiltmax, const double pantiltlowrate, const double pantilthighrate ):BasicCamera( pos, dir, top, zoommax, zoommin, zoomrate ),
	pan(panmin), panmax(panmax), panmin(panmin), tilt(tiltmin), tiltmax(tiltmax), tiltmin(tiltmin), pantiltlowrate(pantiltlowrate), pantilthighrate(pantilthighrate)
{
	return;
}

CameraPTU::~CameraPTU()
{
	return;
}

void CameraPTU::Connect( discsignals::DiscreteBundle* bundle, const unsigned short panleft, const unsigned short panright, const unsigned short tiltup, const unsigned short tiltdown, const unsigned short pantiltctr )
{
	PanLeftCmd.Connect( bundle, panleft );
	PanRightCmd.Connect( bundle, panright );
	TiltUpCmd.Connect( bundle, tiltup );
	TiltDownCmd.Connect( bundle, tiltdown );
	PanTiltCtrlClk.Connect( bundle, pantiltctr );
	return;
}

void CameraPTU::TimeStep( const double dt )
{
	BasicCamera::TimeStep( dt );

	double motion = PanLeftCmd.IsSet() - PanRightCmd.IsSet();
	if ((motion != 0.0) && (pan != panmin) && (pan != panmax))
	{
		double rt = PanTiltCtrlClk.IsSet() ? pantilthighrate : pantiltlowrate;
		pan = range( panmin, pan + (motion * rt * dt), panmax );
		updated = true;
	}

	motion = TiltUpCmd.IsSet() - TiltDownCmd.IsSet();
	if ((motion != 0.0) && (tilt != tiltmin) && (tilt != tiltmax))
	{
		double rt = PanTiltCtrlClk.IsSet() ? pantilthighrate : pantiltlowrate;
		tilt = range( tiltmin, tilt + (motion * rt * dt), tiltmax );
		updated = true;
	}
	return;
}
