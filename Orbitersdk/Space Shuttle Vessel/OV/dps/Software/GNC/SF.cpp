#include "SF.h"
#include <MathSSV.h>
#include "../../../Atlantis.h"


namespace dps
{
	static double counts2volts( const short counts )
	{
		double volts = (counts / 64) * 0.01;
		return volts;
	}

	SF::SF( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SF" )
	{
		return;
	}

	SF::~SF( void )
	{
		return;
	}

	void SF::OnPreStep( double simt, double simdt, double mjd )
	{
		// HACK NY, NZ
		VECTOR3 gravity;
		STS()->GetWeightVector( gravity );
		VECTOR3 f;
		STS()->GetForceVector( f );

		WriteCOMPOOL_SS( SCP_NY, static_cast<float>((f.x - (STS()->GroundContact() ? 0.0 : gravity.x)) / length( gravity )) );

		double NZ = (f.y - (STS()->GroundContact() ? 0.0 : gravity.y)) / length( gravity );
		WriteCOMPOOL_SS( SCP_NZ, static_cast<float>(NZ) );

		if (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1) WriteCOMPOOL_SS( SCP_DISPLAYED_NORMAL_ACCEL, static_cast<float>(NZ * (G * MPS2FPS)) );

		// HACK rates
		VECTOR3 rates;
		STS()->GetAngularVel( rates );
		WriteCOMPOOL_SS( SCP_Q_ORB, static_cast<float>(rates.x * DEG) );
		WriteCOMPOOL_SS( SCP_P_ORB, static_cast<float>(rates.z * DEG) );
		WriteCOMPOOL_SS( SCP_R_ORB, static_cast<float>(-rates.y * DEG) );


		// SBTC
		if ((ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1))
		{
			// read and convert to vdc
			double FF1_IOM1_CH4 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH4_DATA ) );
			double FF2_IOM1_CH4 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH4_DATA ) );
			double FF2_IOM14_CH4 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM14_CH4_DATA ) );
			double FF3_IOM1_CH4 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH4_DATA ) );
			double FF3_IOM14_CH4 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM14_CH4_DATA ) );
			double FF4_IOM14_CH4 = counts2volts( ReadCOMPOOL_IS( SCP_FF4_IOM14_CH4_DATA ) );

			WriteCOMPOOL_SS( SCP_DSBTCC, static_cast<float>(midval( FF1_IOM1_CH4, FF2_IOM1_CH4, FF3_IOM1_CH4 )) );
			WriteCOMPOOL_IS( SCP_L_SBTC_DG, 1 );

			WriteCOMPOOL_SS( SCP_DSBTCP, static_cast<float>(midval( FF2_IOM14_CH4, FF3_IOM14_CH4, FF4_IOM14_CH4 )) );
			WriteCOMPOOL_IS( SCP_R_SBTC_DG, 1 );
		}

		// RPTA
		if ((ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1))
		{
			double FF1_IOM1_CH3 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH3_DATA ) );
			double FF2_IOM1_CH3 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH3_DATA ) );
			double FF2_IOM14_CH3 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM14_CH3_DATA ) );
			double FF3_IOM1_CH3 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH3_DATA ) );
			double FF3_IOM14_CH3 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM14_CH3_DATA ) );
			double FF4_IOM14_CH3 = counts2volts( ReadCOMPOOL_IS( SCP_FF4_IOM14_CH3_DATA ) );

			WriteCOMPOOL_SS( SCP_DRCMDR, static_cast<float>(midval( FF1_IOM1_CH3, FF2_IOM1_CH3, FF3_IOM1_CH3 )) );
			WriteCOMPOOL_IS( SCP_L_RPTA_DG, 1 );

			WriteCOMPOOL_SS( SCP_DRPLT, static_cast<float>(midval( FF2_IOM14_CH3, FF3_IOM14_CH3, FF4_IOM14_CH3 )) );
			WriteCOMPOOL_IS( SCP_R_RPTA_DG, 1 );
		}

		// RHC
		if ((ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_105 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_106 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_201 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_202_FROM_MM_201_FLAG ) == 1) || (ReadCOMPOOL_IS( SCP_MM_801_FROM_MM_201 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_301 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_302 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_303 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1))
		{
			double FF1_IOM1_CH0 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH0_DATA ) );
			double FF1_IOM1_CH1 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH1_DATA ) );
			double FF1_IOM1_CH2 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH2_DATA ) );

			double FF2_IOM1_CH0 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH0_DATA ) );
			double FF2_IOM1_CH1 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH1_DATA ) );
			double FF2_IOM1_CH2 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH2_DATA ) );

			double FF3_IOM1_CH0 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH0_DATA ) );
			double FF3_IOM1_CH1 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH1_DATA ) );
			double FF3_IOM1_CH2 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH2_DATA ) );

			WriteCOMPOOL_SS( SCP_DEC, static_cast<float>(midval( FF1_IOM1_CH1, FF2_IOM1_CH1, FF3_IOM1_CH1 )) );
			WriteCOMPOOL_SS( SCP_DAC, static_cast<float>(midval( FF1_IOM1_CH0, FF2_IOM1_CH0, FF3_IOM1_CH0 )) );
			WriteCOMPOOL_SS( SCP_DYC, static_cast<float>(midval( FF1_IOM1_CH2, FF2_IOM1_CH2, FF3_IOM1_CH2 )) );
			WriteCOMPOOL_IS( SCP_L_PIT_DG, 1 );
			WriteCOMPOOL_IS( SCP_L_ROL_DG, 1 );
			WriteCOMPOOL_IS( SCP_L_YAW_DG, 1 );


			double FF2_IOM14_CH0 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM14_CH0_DATA ) );
			double FF2_IOM14_CH1 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM14_CH1_DATA ) );
			double FF2_IOM14_CH2 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM14_CH2_DATA ) );

			double FF3_IOM14_CH0 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM14_CH0_DATA ) );
			double FF3_IOM14_CH1 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM14_CH1_DATA ) );
			double FF3_IOM14_CH2 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM14_CH2_DATA ) );

			double FF4_IOM14_CH0 = counts2volts( ReadCOMPOOL_IS( SCP_FF4_IOM14_CH0_DATA ) );
			double FF4_IOM14_CH1 = counts2volts( ReadCOMPOOL_IS( SCP_FF4_IOM14_CH1_DATA ) );
			double FF4_IOM14_CH2 = counts2volts( ReadCOMPOOL_IS( SCP_FF4_IOM14_CH2_DATA ) );

			WriteCOMPOOL_SS( SCP_DEP, static_cast<float>(midval( FF2_IOM14_CH1, FF3_IOM14_CH1, FF4_IOM14_CH1 )) );
			WriteCOMPOOL_SS( SCP_DAP, static_cast<float>(midval( FF2_IOM14_CH0, FF3_IOM14_CH0, FF4_IOM14_CH0 )) );
			WriteCOMPOOL_SS( SCP_DYP, static_cast<float>(midval( FF2_IOM14_CH2, FF3_IOM14_CH2, FF4_IOM14_CH2 )) );
			WriteCOMPOOL_IS( SCP_R_PIT_DG, 1 );
			WriteCOMPOOL_IS( SCP_R_ROL_DG, 1 );
			WriteCOMPOOL_IS( SCP_R_YAW_DG, 1 );


			double FF1_IOM1_CH5 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH5_DATA ) );
			double FF1_IOM1_CH6 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH6_DATA ) );
			double FF1_IOM1_CH7 = counts2volts( ReadCOMPOOL_IS( SCP_FF1_IOM1_CH7_DATA ) );

			double FF2_IOM1_CH5 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH5_DATA ) );
			double FF2_IOM1_CH6 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH6_DATA ) );
			double FF2_IOM1_CH7 = counts2volts( ReadCOMPOOL_IS( SCP_FF2_IOM1_CH7_DATA ) );

			double FF3_IOM1_CH5 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH5_DATA ) );
			double FF3_IOM1_CH6 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH6_DATA ) );
			double FF3_IOM1_CH7 = counts2volts( ReadCOMPOOL_IS( SCP_FF3_IOM1_CH7_DATA ) );

			WriteCOMPOOL_SS( SCP_DEA, static_cast<float>(midval( FF1_IOM1_CH6, FF2_IOM1_CH6, FF3_IOM1_CH6 )) );
			WriteCOMPOOL_SS( SCP_DAA, static_cast<float>(midval( FF1_IOM1_CH5, FF2_IOM1_CH5, FF3_IOM1_CH5 )) );
			WriteCOMPOOL_SS( SCP_DYA, static_cast<float>(midval( FF1_IOM1_CH7, FF2_IOM1_CH7, FF3_IOM1_CH7 )) );
			WriteCOMPOOL_IS( SCP_A_PIT_DG, 1 );
			WriteCOMPOOL_IS( SCP_A_ROL_DG, 1 );
			WriteCOMPOOL_IS( SCP_A_YAW_DG, 1 );
		}
		return;
	}
}
