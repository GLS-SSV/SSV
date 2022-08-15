/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#include "OMS_TVC_Feedback_SOP.h"
#include "OMSBurnSoftware.h"
#include <cassert>


namespace dps
{
	OMSTVCFDBK_SOP::OMSTVCFDBK_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "OMS_TVC_Feedback_SOP" )
	{
		return;
	}

	OMSTVCFDBK_SOP::~OMSTVCFDBK_SOP( void )
	{
		return;
	}

	void OMSTVCFDBK_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "OMS_TVC_FDBK", 8 );
		L_OMS_PRI_P_ACTR_POS.Connect( pBundle, 0 );
		L_OMS_PRI_Y_ACTR_POS.Connect( pBundle, 1 );
		L_OMS_SEC_P_ACTR_POS.Connect( pBundle, 2 );
		L_OMS_SEC_Y_ACTR_POS.Connect( pBundle, 3 );
		R_OMS_PRI_P_ACTR_POS.Connect( pBundle, 4 );
		R_OMS_PRI_Y_ACTR_POS.Connect( pBundle, 5 );
		R_OMS_SEC_P_ACTR_POS.Connect( pBundle, 6 );
		R_OMS_SEC_Y_ACTR_POS.Connect( pBundle, 7 );

		pOMSBurnSoftware = dynamic_cast<OMSBurnSoftware*>(FindSoftware( "OMSBurnSoftware" ));
		assert( (pOMSBurnSoftware != NULL) && "OMSTVCFDBK_SOP::Realize.pOMSBurnSoftware" );
		return;
	}

	void OMSTVCFDBK_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		return;
	}

	bool OMSTVCFDBK_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void OMSTVCFDBK_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool OMSTVCFDBK_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 104:
			case 105:
			case 106:
			case 202:
			case 301:
			case 302:
			case 303:
			case 601:
			case 801:
			case 901:
				return true;
			default:
				return false;
		}
	}

	bool OMSTVCFDBK_SOP::GetActrPos( unsigned int eng, double& p, double& y ) const
	{
		unsigned int actr = pOMSBurnSoftware->GetOMSGimbalActrSel( eng );

		if (actr == 0) return false;

		if (eng == 0)
		{
			if (actr == 1)
			{
				// L PRI
				p = L_OMS_PRI_P_ACTR_POS.GetVoltage();
				y = L_OMS_PRI_Y_ACTR_POS.GetVoltage();
			}
			else
			{
				// L SEC
				p = L_OMS_SEC_P_ACTR_POS.GetVoltage();
				y = L_OMS_SEC_Y_ACTR_POS.GetVoltage();
			}
		}
		else
		{
			if (actr == 1)
			{
				// R PRI
				p = R_OMS_PRI_P_ACTR_POS.GetVoltage();
				y = R_OMS_PRI_Y_ACTR_POS.GetVoltage();
			}
			else
			{
				// R SEC
				p = R_OMS_SEC_P_ACTR_POS.GetVoltage();
				y = R_OMS_SEC_Y_ACTR_POS.GetVoltage();
			}
		}
		return true;
	}
}