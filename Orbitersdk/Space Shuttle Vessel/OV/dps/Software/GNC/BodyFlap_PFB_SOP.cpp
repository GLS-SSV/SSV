/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/10/21   GLS
2022/12/01   indy91
2026/09/18   GLS
********************************************/
#include "BodyFlap_PFB_SOP.h"


namespace dps
{
	BodyFlap_PFB_SOP::BodyFlap_PFB_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "BodyFlap_PFB_SOP" )
	{
		{// TODO fix IO
			DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
			dipPositionFeedback.Connect( pBundle, 6 );
		}
		return;
	}

	BodyFlap_PFB_SOP::~BodyFlap_PFB_SOP( void )
	{
		return;
	}

	void BodyFlap_PFB_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		WriteCOMPOOL_SS( SCP_DBFOFB, static_cast<float>(((dipPositionFeedback.GetVoltage() * (27.5 + 16.6)) / 5.0) - 16.6) );// (-16.6;+27.5) [deg]
		return;
	}
}
