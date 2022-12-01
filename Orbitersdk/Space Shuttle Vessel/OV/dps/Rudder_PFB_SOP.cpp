/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/10/21   GLS
********************************************/
#include "Rudder_PFB_SOP.h"


namespace dps
{
	Rudder_PFB_SOP::Rudder_PFB_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Rudder_PFB_SOP" )
	{
		return;
	}

	Rudder_PFB_SOP::~Rudder_PFB_SOP( void )
	{
		return;
	}

	void Rudder_PFB_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
		dipPositionFeedback.Connect( pBundle, 4 );
		return;
	}

	void Rudder_PFB_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		WriteCOMPOOL_SS( SCP_DRFB, static_cast<float>(((dipPositionFeedback.GetVoltage() * (27.6 + 27.6)) / 5.0) - 27.6) );// (-27.6;+27.6) [deg]
		return;
	}

	bool Rudder_PFB_SOP::OnMajorModeChange( unsigned int newMajorMode )
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
