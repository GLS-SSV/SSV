/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/10/21   GLS
2022/12/01   indy91
2023/11/26   GLS
2026/09/18   GLS
********************************************/
#include "Speedbrake_PFB_SOP.h"


namespace dps
{
	Speedbrake_PFB_SOP::Speedbrake_PFB_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Speedbrake_PFB_SOP" )
	{
		{// TODO fix IO
			DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
			dipPositionFeedback.Connect( pBundle, 5 );
		}
		return;
	}

	Speedbrake_PFB_SOP::~Speedbrake_PFB_SOP( void )
	{
		return;
	}

	void Speedbrake_PFB_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		double DSBFB = ((dipPositionFeedback.GetVoltage() * (98.6 + 9.9)) / 5.0) - 9.9;// (-9.9,+98.6) [deg]
		DSBFB = max(0.0, DSBFB);// HACK? limit min to 0.0
		WriteCOMPOOL_SS( SCP_DSBOFB, static_cast<float>(DSBFB) );
		WriteCOMPOOL_SS( SCP_DSBFBP, static_cast<float>(DSBFB / 0.986) );
		return;
	}
}
