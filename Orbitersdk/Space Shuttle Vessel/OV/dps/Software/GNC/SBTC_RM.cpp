/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
********************************************/
#include "SBTC_RM.h"
#include <MathSSV.h>


namespace dps
{
	SBTC_RM::SBTC_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SBTC_RM" )
	{
		SBTC_L = 0.0;
		SBTC_L_DG = true;
		SBTC_TO_L = true;

		SBTC_R = 0.0;
		SBTC_R_DG = true;
		SBTC_TO_R = true;
		return;
	}

	SBTC_RM::~SBTC_RM( void )
	{
		return;
	}

	void SBTC_RM::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "LeftSBTC", 16 );
		for (int i = 0; i < 3; i++) LeftSBTC[i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "RightSBTC", 16 );
		for (int i = 0; i < 3; i++) RightSBTC[i].Connect( pBundle, i );
		return;
	}

	void SBTC_RM::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );
		unsigned short FF4_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF4_IOM15_CH0_DATA );

		bool LH_SBTC_TAKEOVER_A = ((FF1_IOM6_CH0 & 0x2000) != 0);
		bool LH_SBTC_TAKEOVER_B = ((FF2_IOM6_CH0 & 0x2000) != 0);
		bool LH_SBTC_TAKEOVER_C = ((FF3_IOM6_CH0 & 0x2000) != 0);
		bool RH_SBTC_TAKEOVER_A = ((FF2_IOM15_CH0 & 0x2000) != 0);
		bool RH_SBTC_TAKEOVER_B = ((FF3_IOM15_CH0 & 0x2000) != 0);
		bool RH_SBTC_TAKEOVER_C = ((FF4_IOM15_CH0 & 0x2000) != 0);

		SBTC_L = midval( LeftSBTC[0].GetVoltage(), LeftSBTC[1].GetVoltage(), LeftSBTC[2].GetVoltage() );
		SBTC_L_DG = true;
		SBTC_TO_L = (LH_SBTC_TAKEOVER_A && LH_SBTC_TAKEOVER_B) || (LH_SBTC_TAKEOVER_A && LH_SBTC_TAKEOVER_C) || (LH_SBTC_TAKEOVER_B && LH_SBTC_TAKEOVER_C);

		SBTC_R = midval( RightSBTC[0].GetVoltage(), RightSBTC[1].GetVoltage(), RightSBTC[2].GetVoltage() );
		SBTC_R_DG = true;
		SBTC_TO_R = (RH_SBTC_TAKEOVER_A && RH_SBTC_TAKEOVER_B) || (RH_SBTC_TAKEOVER_A && RH_SBTC_TAKEOVER_C) || (RH_SBTC_TAKEOVER_B && RH_SBTC_TAKEOVER_C);
		return;
	}

	bool SBTC_RM::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void SBTC_RM::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool SBTC_RM::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	void SBTC_RM::GetSBTCData_L( double &sbtc, bool &DG, bool &to ) const
	{
		sbtc = SBTC_L;
		DG = SBTC_L_DG;
		to = SBTC_TO_L;
		return;
	}

	void SBTC_RM::GetSBTCData_R( double &sbtc, bool &DG, bool &to ) const
	{
		sbtc = SBTC_R;
		DG = SBTC_R_DG;
		to = SBTC_TO_R;
		return;
	}
}