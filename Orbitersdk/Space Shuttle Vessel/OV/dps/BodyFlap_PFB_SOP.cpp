/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/10/21   GLS
********************************************/
#include "BodyFlap_PFB_SOP.h"


namespace dps
{
	BodyFlap_PFB_SOP::BodyFlap_PFB_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "BodyFlap_PFB_SOP" )
	{
		return;
	}

	BodyFlap_PFB_SOP::~BodyFlap_PFB_SOP( void )
	{
		return;
	}

	void BodyFlap_PFB_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
		dipPositionFeedback.Connect( pBundle, 6 );
		return;
	}

	void BodyFlap_PFB_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		WriteCOMPOOL_SD( SCP_DBFOFB, static_cast<float>(((dipPositionFeedback.GetVoltage() * (27.5 + 16.6)) / 5.0) - 16.6) );// (-16.6;+27.5) [deg]
		return;
	}

	bool BodyFlap_PFB_SOP::OnMajorModeChange( unsigned int newMajorMode )
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
