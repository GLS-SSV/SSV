/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
2023/06/14   GLS
********************************************/
#include "SBTC_RM.h"
#include <MathSSV.h>


namespace dps
{
	SBTC_RM::SBTC_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SBTC_RM" )
	{
		return;
	}

	SBTC_RM::~SBTC_RM( void )
	{
		return;
	}

	void SBTC_RM::OnPostStep( double simt, double simdt, double mjd )
	{
		// read and convert to vdc
		double FF1_IOM1_CH4 = ReadCOMPOOL_IS( SCP_FF1_IOM1_CH4_DATA ) * 0.01;
		double FF2_IOM1_CH4 = ReadCOMPOOL_IS( SCP_FF2_IOM1_CH4_DATA ) * 0.01;
		double FF2_IOM14_CH4 = ReadCOMPOOL_IS( SCP_FF2_IOM14_CH4_DATA ) * 0.01;
		double FF3_IOM1_CH4 = ReadCOMPOOL_IS( SCP_FF3_IOM1_CH4_DATA ) * 0.01;
		double FF3_IOM14_CH4 = ReadCOMPOOL_IS( SCP_FF3_IOM14_CH4_DATA ) * 0.01;
		double FF4_IOM14_CH4 = ReadCOMPOOL_IS( SCP_FF4_IOM14_CH4_DATA ) * 0.01;

		WriteCOMPOOL_SS( SCP_DSBTCC, static_cast<float>(midval( FF1_IOM1_CH4, FF2_IOM1_CH4, FF3_IOM1_CH4 )) );
		WriteCOMPOOL_IS( SCP_L_SBTC_DG, 1 );

		WriteCOMPOOL_SS( SCP_DSBTCP, static_cast<float>(midval( FF2_IOM14_CH4, FF3_IOM14_CH4, FF4_IOM14_CH4 )) );
		WriteCOMPOOL_IS( SCP_R_SBTC_DG, 1 );
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
}