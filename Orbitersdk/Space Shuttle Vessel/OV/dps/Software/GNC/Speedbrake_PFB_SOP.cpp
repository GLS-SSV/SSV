/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/10/21   GLS
2022/12/01   indy91
********************************************/
#include "Speedbrake_PFB_SOP.h"


namespace dps
{
	Speedbrake_PFB_SOP::Speedbrake_PFB_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Speedbrake_PFB_SOP" )
	{
		return;
	}

	Speedbrake_PFB_SOP::~Speedbrake_PFB_SOP( void )
	{
		return;
	}

	void Speedbrake_PFB_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
		dipPositionFeedback.Connect( pBundle, 5 );
		return;
	}

	void Speedbrake_PFB_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		double DSBFB = ((dipPositionFeedback.GetVoltage() * (98.6 + 9.9)) / 5.0) - 9.9;// (-9.9,+98.6) [deg]
		DSBFB = max(0.0, DSBFB);// HACK? limit min to 0.0
		WriteCOMPOOL_SS( SCP_DSBFB_DEG, static_cast<float>(DSBFB) );
		WriteCOMPOOL_SS( SCP_DSBFB_PCT, static_cast<float>(DSBFB / 0.986) );
		return;
	}

	bool Speedbrake_PFB_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}
}
