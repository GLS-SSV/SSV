#include "VERT_SIT_DIP.h"
#include <MathSSV.h>


namespace dps
{
	constexpr double EXEC_RATE_DT_OPS16 = 0.48;// 2.083Hz
	constexpr double EXEC_RATE_DT_OPS3 = 0.96;// 1.04Hz


	VERT_SIT_DIP::VERT_SIT_DIP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "VERT_SIT_DIP" ),
		step(EXEC_RATE_DT_OPS3)
	{
		return;
	}

	VERT_SIT_DIP::~VERT_SIT_DIP( void )
	{
		return;
	}

	void VERT_SIT_DIP::OnPreStep( double simt, double simdt, double mjd )
	{
		// INFO logic and associated I-Loads using "flipped" Y axis, conversion to display coordinates done in VERT SIT
		// VERT SIT	display
		// Y = 0	Y = 731
		// Y = 731	Y = 0

		step += simdt;
		if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 3)
		{
			if (step < EXEC_RATE_DT_OPS3) return;
		}
		else
		{
			if (step < EXEC_RATE_DT_OPS16) return;
		}

		// TODO init
		double ALT_WHEELS = ReadCOMPOOL_SD( SCP_ALT_WHEELS );
		float REL_VEL_MAG = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );
		float YMIN = ReadCOMPOOL_SS( SCP_YMIN );
		float YMAX = ReadCOMPOOL_SS( SCP_YMAX );
		float YMEP = ReadCOMPOOL_SS( SCP_YMEP );

		unsigned short IGSD = 1;// TODO OPS3: IGSD = IGS

		float PRED_R;
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 1)
		{
			PRED_R = ReadCOMPOOL_SS( SCP_R_GND_AP );
		}
		else
		{
			PRED_R = ReadCOMPOOL_SS( SCP_RPRED ) + ReadCOMPOOL_SS( SCP_X_AIM_PT );
		}

		if (((PRED_R < ReadCOMPOOL_SS( SCP_RT1_RNG_VS1 )) && (ALT_WHEELS < ReadCOMPOOL_SS( SCP_RT1_ALT_VS1 ))) || (/*TODO ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1*/ReadCOMPOOL_IS( SCP_MM ) == 603))
		{
			// 603/305
			int I;
			if (ALT_WHEELS >= ReadCOMPOOL_SS( SCP_HSWITCH ))
			{
				I = 1;// VERTICAL SITUATION 1
			}
			else
			{
				I = 2;// VERTICAL SITUATION 2
				WriteCOMPOOL_IS( SCP_ADV_FLAG, 1 );
			}

			/// Computation of Orbiter Symbol Nose
			double VSHUTTLE_X;
			double VSHUTTLE_Y;
			if ((ALT_WHEELS <= ReadCOMPOOL_VS( SCP_HBIAS, 2, 2 )) || (PRED_R <= ReadCOMPOOL_VS( SCP_RBIAS, 2, 2 )))
			{
				VSHUTTLE_Y = ReadCOMPOOL_SS( SCP_VS_Y_MIN );
				VSHUTTLE_X = ReadCOMPOOL_SS( SCP_VS_X_MIN );
			}
			else
			{
				// X-Coordinate
				double VSHUTTLE_XN = ReadCOMPOOL_VS( SCP_XSCALE, I, 2 ) * (PRED_R - ReadCOMPOOL_VS( SCP_RBIAS, I, 2 )) + ReadCOMPOOL_SS( SCP_VS_X_MIN );

				// Y-Coordinate
				double VSHUTTLE_YN = ReadCOMPOOL_VS( SCP_YSCALE, I, 2 ) * (ALT_WHEELS - ReadCOMPOOL_VS( SCP_HBIAS, I, 2 )) + ReadCOMPOOL_SS( SCP_VS_Y_MIN );

				// Altitude dissipation rate
				double ALT_DIS_ANGLE = atan2( -ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID ) * ReadCOMPOOL_VS( SCP_YSCALE, I, 2 ), ReadCOMPOOL_SS( SCP_V_GROUNDSPEED ) * ReadCOMPOOL_VS( SCP_XSCALE, I, 2 ) );
				short DISP_ALT_DIS_ANGLE = static_cast<short>(-90 - (ALT_DIS_ANGLE * /*(180 / PI)*/DEG));
				if (DISP_ALT_DIS_ANGLE < 0) DISP_ALT_DIS_ANGLE += 360;
				WriteCOMPOOL_IS( SCP_DISP_ALT_DIS_ANGLE, DISP_ALT_DIS_ANGLE );

				/// Computation of Orbiter Symbol Center
				// X-Coordinate
				VSHUTTLE_X = VSHUTTLE_XN + (ReadCOMPOOL_SS( SCP_DXS ) * cos( ALT_DIS_ANGLE )) - (ReadCOMPOOL_SS( SCP_DYS ) * sin( ALT_DIS_ANGLE ));

				// Y-Coordinate
				VSHUTTLE_Y = VSHUTTLE_YN + (ReadCOMPOOL_SS( SCP_DXS ) * sin( ALT_DIS_ANGLE )) + (ReadCOMPOOL_SS( SCP_DYS ) * cos( ALT_DIS_ANGLE ));
			}

			WriteCOMPOOL_IS( SCP_VSHUTTLE_X, static_cast<unsigned short>(VSHUTTLE_X) );
			WriteCOMPOOL_IS( SCP_VSHUTTLE_Y, static_cast<unsigned short>(VSHUTTLE_Y) );


			/// Computation of Current Theta Symbol Position
			unsigned short IV = 1;
			if (REL_VEL_MAG <= ReadCOMPOOL_SS( SCP_V_DEFAULT ))
			{
				IV = 1;
			}
			if (REL_VEL_MAG > ReadCOMPOOL_SS( SCP_V1 ))
			{
				IV = 2;
			}
			if (REL_VEL_MAG > ReadCOMPOOL_SS( SCP_V2 ))
			{
				IV = 3;
			}
			if (REL_VEL_MAG > ReadCOMPOOL_SS( SCP_V3 ))
			{
				IV = 4;
			}

			// COMPUTE THETA MAX VALUE FOR SCALING
			double THETA_MAX = ReadCOMPOOL_MS( SCP_A, IV, 1, 4, 5 ) + (ReadCOMPOOL_MS( SCP_A, IV, 2, 4, 5 ) * REL_VEL_MAG) + (ReadCOMPOOL_MS( SCP_A, IV, 3, 4, 5 ) * ((1.0 / ReadCOMPOOL_SS( SCP_COSPHI )) - 1.0)) + ((ReadCOMPOOL_MS( SCP_A, IV, 4, 4, 5 ) + (ReadCOMPOOL_MS( SCP_A, IV, 5, 4, 5 ) * REL_VEL_MAG)) * ReadCOMPOOL_SS( SCP_DSBFBP ));

			// COMPUTE THETA MIN VALUE FOR SCALING
			double M = 123;// TODO
			double THETA_MIN = ReadCOMPOOL_MS( SCP_B, IV, 1, 4, 5 ) + (ReadCOMPOOL_MS( SCP_B, IV, 2, 4, 5 ) * REL_VEL_MAG) + (ReadCOMPOOL_MS( SCP_B, IV, 3, 4, 5 ) * ((1.0 / ReadCOMPOOL_SS( SCP_COSPHI )) - 1.0)) + ((ReadCOMPOOL_MS( SCP_B, IV, 4, 4, 5 ) + (ReadCOMPOOL_MS( SCP_B, IV, 5, 4, 5 ) * REL_VEL_MAG)) * ReadCOMPOOL_SS( SCP_DSBFBP )) + (midval( ReadCOMPOOL_SS( SCP_PITCH_MAX ) - (ReadCOMPOOL_SS( SCP_DPDV ) * (REL_VEL_MAG - ReadCOMPOOL_SS( SCP_VB )) / ReadCOMPOOL_SS( SCP_VD )), ReadCOMPOOL_SS( SCP_PITCH_MAX ), ReadCOMPOOL_SS( SCP_PITCH_MIN ) ) * ((M - ReadCOMPOOL_SS( SCP_WT_NOM )) / ReadCOMPOOL_SS( SCP_WT_DENOM )));

			// LIMIT THETA SCALE SENSITIVITY
			if (THETA_MAX < (THETA_MIN + ReadCOMPOOL_SS( SCP_DTHT )))
			{
				THETA_MAX = THETA_MIN + ReadCOMPOOL_SS( SCP_DTHT );
			}

			WriteCOMPOOL_SS( SCP_THETA_MAX, static_cast<float>(THETA_MAX) );
			WriteCOMPOOL_SS( SCP_THETA_MIN, static_cast<float>(THETA_MIN) );

			// COMPUTE THETA SCALE FACTOR
			double THETA_SCALE = ReadCOMPOOL_SS( SCP_SCALE_LEN ) / (THETA_MIN - THETA_MAX);

			// COMPUTE THETA SYMBOL Y-POSITION
			double THETA_Y = YMEP - (THETA_SCALE * (ReadCOMPOOL_SS( SCP_THETA ) - THETA_MIN));
			
			// LIMIT THETA SYMBOL Y POSITION
			if (THETA_Y > YMAX)
			{
				THETA_Y = YMAX;
			}
			if (THETA_Y < YMIN)
			{
				THETA_Y = YMIN;
			}
			if ((THETA_Y == YMIN) || (THETA_Y == YMAX))
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_THETA_FLAG, 1 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_THETA_FLAG, 0 );
			}

			WriteCOMPOOL_IS( SCP_THETA_Y, static_cast<unsigned short>(THETA_Y) );
		}
		else
		{
			// 602
			/// Computation of the Mach-Alpha Indicator
			float ALPHA_N = ReadCOMPOOL_SS( SCP_ALPHA_N );

			// Y-Coordinate
			double ALPHA_PLOT = midval( ReadCOMPOOL_SS( SCP_RT2_ALPHA_MIN ), ALPHA_N, ReadCOMPOOL_SS( SCP_RT2_ALPHA_MAX ) );
			if (ALPHA_N > ReadCOMPOOL_SS( SCP_RT2_ALPHA_MAX ))
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_ALPHA_FLAG, 1 );
			}
			else if (ALPHA_N < ReadCOMPOOL_SS( SCP_RT2_ALPHA_MIN ))
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_ALPHA_FLAG, 1 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_ALPHA_FLAG, 0 );
			}
			unsigned short RT1_SQUARE_Y = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_RT1_ALPHA_BIAS ) + (ReadCOMPOOL_SS( SCP_RT1_ALPHA_SC_FACT ) * ALPHA_PLOT));

			// X-Coordinate
			double MACH_PLOT = midval( ReadCOMPOOL_SS( SCP_RT1_MACH_MIN ), ReadCOMPOOL_SS( SCP_M ), ReadCOMPOOL_SS( SCP_RT1_MACH_MAX ) );
			unsigned short RT1_SQUARE_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_RT1_MACH_BIAS ) + (ReadCOMPOOL_SS( SCP_RT1_MACH_SC_FACT ) * MACH_PLOT));

			WriteCOMPOOL_IS( SCP_RT1_SQUARE_Y, RT1_SQUARE_Y );
			WriteCOMPOOL_IS( SCP_RT1_SQUARE_X, RT1_SQUARE_X );
		}

		//// Conversion of Digital Data
		double SBC;
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 0)
		{
			SBC = ReadCOMPOOL_SS( SCP_DSBC_AT );
		}
		else// if (TG_END == 1)
		{
			SBC = ReadCOMPOOL_SS( SCP_DSBC_AL );
		}

		if (SBC < 0) SBC = 0.0;
		else if (SBC > 98.6) SBC = 98.6;

		double VS_SBC = 100 * SBC / 98.6;
		WriteCOMPOOL_IS( SCP_VS_SBC, static_cast<unsigned short>(VS_SBC) );

		//// Energy Scale Symbols
		unsigned short NOM_ENERGY_Y;
		unsigned short SHUTTLE_ENER_Y;
		unsigned short EMOH_ENER_Y;
		unsigned short ENER_UL_Y;
		unsigned short ENER_LL_Y;
		if (ALT_WHEELS > ReadCOMPOOL_SS( SCP_HSWITCH2 ))
		{
			/// Perform Energy Scale Symbol Computations
			float ES = ReadCOMPOOL_SS( SCP_ES );
			float EN = ReadCOMPOOL_SS( SCP_EN );
			float EMEP = ReadCOMPOOL_SS( SCP_EMEP );
			float EOW = ReadCOMPOOL_SS( SCP_EOW );
			float EMOH = ReadCOMPOOL_SS( SCP_EMOH );
			float EMAX = ReadCOMPOOL_SS( SCP_EMAX );
			float EMIN = ReadCOMPOOL_SS( SCP_EMIN );
			float RMINST = ReadCOMPOOL_SS( SCP_RMINST_DIP );

			// Compute S-TURN level
			float ENERGY_STURN;
			if (PRED_R > RMINST)
			{
				ENERGY_STURN = ES;
			}
			else
			{
				ENERGY_STURN = ReadCOMPOOL_VS( SCP_ES_C12, IGSD, 2 ) + (ReadCOMPOOL_VS( SCP_EDRS2, IGSD, 2 ) * (PRED_R - RMINST));
			}

			// Compute required scale factor
			float ENERGY_SCALE = ReadCOMPOOL_SS( SCP_SCALE_LEN ) / (ENERGY_STURN - EMEP);

			// Y-Coordinate
			NOM_ENERGY_Y = static_cast<unsigned short>(YMEP + (ENERGY_SCALE * (EN - EMEP)));

			/// Computation of Current Energy Symbol Position
			// Y-Coordinate
			SHUTTLE_ENER_Y = static_cast<unsigned short>(YMEP + (ENERGY_SCALE * (EOW - EMEP)));

			// Limit symbol and determine flash requirement
			if (EOW >= EN)
			{
				if (EOW > ENERGY_STURN)
				{
					if (PRED_R >= RMINST)
					{
						WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG, 1 );
					}
					else
					{
						WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG, 0 );
					}
				}
			}
			if (SHUTTLE_ENER_Y > YMAX)
			{
				SHUTTLE_ENER_Y = static_cast<unsigned short>(YMAX);
			}
			else
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG, 0 );
			}

			if (EOW <= EMEP)
			{
				if (PRED_R >= ReadCOMPOOL_SS( SCP_RMEPMIN ))
				{
					WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG, 1 );
				}
				else
				{
					WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG, 0 );
				}
			}
			if (SHUTTLE_ENER_Y < YMIN)
			{
				SHUTTLE_ENER_Y = static_cast<unsigned short>(YMIN);
			}
			else
			{
				WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG, 0 );
			}

			/// Computation of Energy Symbol Limit Position
			// Compute upper energy limit symbol position
			ENER_UL_Y = static_cast<unsigned short>(YMEP + (ENERGY_SCALE * (EMAX - EMEP))) + 11;// +11 AU offset as '_' is used instead of '-'

			// Compute lower energy limit symbol position
			ENER_LL_Y = static_cast<unsigned short>(YMEP + (ENERGY_SCALE * (EMIN - EMEP))) + 11;

			/// Computation of OTT Downmode Energy Symbol Position
			// Compute OTT Downmode Energy Symbol position
			if (PRED_R < ReadCOMPOOL_SS( SCP_RMOH ))
			{
				EMOH_ENER_Y = -400;
			}
			else
			{
				EMOH_ENER_Y = static_cast<unsigned short>(YMEP + (ENERGY_SCALE * (EMOH - EMEP)));
			}
		}
		else
		{
			NOM_ENERGY_Y = -400;
			SHUTTLE_ENER_Y = -400;
			EMOH_ENER_Y = -400;
			ENER_UL_Y = -400;
			ENER_LL_Y = -400;
		}
		WriteCOMPOOL_IS( SCP_NOM_ENERGY_Y, NOM_ENERGY_Y );
		WriteCOMPOOL_IS( SCP_SHUTTLE_ENER_Y, static_cast<unsigned short>(SHUTTLE_ENER_Y) );
		WriteCOMPOOL_IS( SCP_EMOH_ENER_Y, EMOH_ENER_Y );
		WriteCOMPOOL_IS( SCP_ENER_UL_Y, ENER_UL_Y );
		WriteCOMPOOL_IS( SCP_ENER_LL_Y, ENER_LL_Y );

		step = 0.0;
		return;
	}

	bool VERT_SIT_DIP::OnMajorModeChange( unsigned int newMajorMode )
	{
		return (newMajorMode == 305);
	}
}
