#include "HORIZ_SIT_SPEC.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	// constants
	constexpr float HERROR_SCALE_Y1 = 419.0f;// (V97U6312C) [AU]
	constexpr float HERROR_SCALE_Y2 = 175.0f;// (V97U6313C) [AU]
	constexpr float HORIZ_SCALE_X1 = 450.0f;// (V97U6314C) [AU]
	constexpr float HORIZ_SCALE_X2 = 770.0f;// (V97U6315C) [AU]


	HORIZ_SIT_SPEC::HORIZ_SIT_SPEC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "HORIZ_SIT_SPEC" ),
		init(false), HAC_TIME(99999999.9f)
	{
		return;
	}

	HORIZ_SIT_SPEC::~HORIZ_SIT_SPEC( void )
	{
		return;
	}

	void HORIZ_SIT_SPEC::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short TG_END = ReadCOMPOOL_IS( SCP_TG_END );
		unsigned short IPHASE = ReadCOMPOOL_IS( SCP_IPHASE );
		VECTOR3 POSN_WRT_RW = ReadCOMPOOL_VS( SCP_POSN_WRT_RW );
		float RF = ReadCOMPOOL_SS( SCP_RF );
		float YSGNP = ReadCOMPOOL_SS( SCP_YSGNP );
		float V_GROUND_SPEED = ReadCOMPOOL_SS( SCP_V_GROUNDSPEED );
		float R_GND_AP = ReadCOMPOOL_SS( SCP_R_GND_AP );
		float PHI = ReadCOMPOOL_SS( SCP_PHI );
		float BETA_N = ReadCOMPOOL_SS( SCP_BETA_N );
		char tmpstr[8];

		if (ReadCOMPOOL_SD( SCP_ALT_WHEELS ) <= ReadCOMPOOL_SS( SCP_HS_ALT ))
		{
			float XHACD;// X distance of HAC
			if ((MM == 305) && (TG_END == 0))
			{
				XHACD = -ReadCOMPOOL_SS( SCP_XHAC );
			}
			else
			{
				XHACD = -ReadCOMPOOL_SS( SCP_X_NEP );
			}

			float PRED_R;// predicted range
			if (MM == 304)
			{
				PRED_R = static_cast<float>(ReadCOMPOOL_SS( SCP_RNG_TO_RW_THRESH ) * /*FT_PER_NMI*/(1.0 / FT2NM));
			}
			else if (TG_END == 0)
			{
				PRED_R = ReadCOMPOOL_SS( SCP_RPRED );
			}
			else
			{
				PRED_R = R_GND_AP - ReadCOMPOOL_SS( SCP_X_AIM_PT );
			}

			float SCALE_FACTOR;// scale factor
			if (PRED_R < XHACD)
			{
				SCALE_FACTOR = ReadCOMPOOL_SS( SCP_HS_Y_RANGE ) / (XHACD + ReadCOMPOOL_SS( SCP_X_AIM_PT ));
			}
			else
			{
			
				SCALE_FACTOR = ReadCOMPOOL_SS( SCP_HS_Y_RANGE ) / (PRED_R + ReadCOMPOOL_SS( SCP_X_AIM_PT ));
			}

			// wind correction
			float DELAZ = static_cast<float>((-BETA_N * cos( PHI * (PI / 180.0) )) * (PI / 180.0));// [rad]

			// rotation angle
			double TC = (ReadCOMPOOL_SS( SCP_COURSE_WRT_RW ) * (PI / 180.0)) + DELAZ;// [rad]

			float X_TAIL_COORD = static_cast<float>(SCALE_FACTOR * ((POSN_WRT_RW.data[0] - ReadCOMPOOL_SS( SCP_X_AIM_PT )) * sin( TC ) - POSN_WRT_RW.data[1] * cos( TC )) + ReadCOMPOOL_SS( SCP_HS_N_X ));
			float Y_TAIL_COORD = static_cast<float>(-SCALE_FACTOR * ((POSN_WRT_RW.data[0] - ReadCOMPOOL_SS( SCP_X_AIM_PT )) * cos( TC ) + POSN_WRT_RW.data[1] * sin( TC )) + ReadCOMPOOL_SS( SCP_HS_N_Y ));

			float X_HEAD_COORD = static_cast<float>(SCALE_FACTOR * ((POSN_WRT_RW.data[0] + XHACD) * sin( TC ) - POSN_WRT_RW.data[1] * cos( TC )) + ReadCOMPOOL_SS( SCP_HS_N_X ));
			float Y_HEAD_COORD = static_cast<float>(-SCALE_FACTOR * ((POSN_WRT_RW.data[0] + XHACD) * cos( TC ) + POSN_WRT_RW.data[1] * sin( TC )) + ReadCOMPOOL_SS( SCP_HS_N_Y ));

			WriteCOMPOOL_IS( SCP_X_TAIL_COORD, static_cast<unsigned short>(X_TAIL_COORD) );
			WriteCOMPOOL_IS( SCP_Y_TAIL_COORD, static_cast<unsigned short>(Y_TAIL_COORD) );
			WriteCOMPOOL_IS( SCP_X_HEAD_COORD, static_cast<unsigned short>(X_HEAD_COORD) );
			WriteCOMPOOL_IS( SCP_Y_HEAD_COORD, static_cast<unsigned short>(Y_HEAD_COORD) );

			// not output, same as tail coord above
			//X_RW_WP2 = X_TAIL_COORD;
			//Y_RW_WP2 = Y_TAIL_COORD;

			// The Computation of the Selected Heading Alignment Cones (RW Coordinates)
			// Selected Heading alignment cone
			// X-Coordinate
			double X_HACC = SCALE_FACTOR * ((POSN_WRT_RW.data[0] + XHACD) * sin( TC ) - (POSN_WRT_RW.data[1] - RF * YSGNP) * cos( TC )) + ReadCOMPOOL_SS( SCP_HS_N_X );
			WriteCOMPOOL_IS( SCP_X_HAC, static_cast<unsigned short>(X_HACC) );

			// Y-Coordinate
			double Y_HACC = -SCALE_FACTOR * ((POSN_WRT_RW.data[0] + XHACD) * cos( TC ) + (POSN_WRT_RW.data[1] - RF * YSGNP) * sin( TC )) + ReadCOMPOOL_SS( SCP_HS_N_Y );
			WriteCOMPOOL_IS( SCP_Y_HAC, static_cast<unsigned short>(Y_HACC) );

			// Circle radius
			double RAD_HACC = SCALE_FACTOR * ReadCOMPOOL_SS( SCP_RTURN );
			WriteCOMPOOL_IS( SCP_RAD_HAC, static_cast<unsigned short>(RAD_HACC) );


			// The Computation of the Three Orbiter Position Predictor Symbols
			// Predictor drives
			float Y_PRED1;
			float X_PRED1;
			float Y_PRED2;
			float X_PRED2;
			float Y_PRED3;
			float X_PRED3;
			if ((PHI == 0) || (V_GROUND_SPEED == 0))
			{
				Y_PRED1 = V_GROUND_SPEED * ReadCOMPOOL_SS( SCP_HDT1 );
				X_PRED1 = -Y_PRED1 * DELAZ;

				Y_PRED2 = V_GROUND_SPEED * ReadCOMPOOL_SS( SCP_HDT2 );
				X_PRED2 = -Y_PRED2 * DELAZ;

				Y_PRED3 = V_GROUND_SPEED * ReadCOMPOOL_SS( SCP_HDT3 );
				X_PRED3 = -Y_PRED3 * DELAZ;
			}
			else
			{
				float G_TAN_PHI = static_cast<float>(MPS2FPS * G * tan( PHI * (PI / 180.0) ));
				float RTURNP = (V_GROUND_SPEED * V_GROUND_SPEED) / G_TAN_PHI;
				float TURNRAT = G_TAN_PHI / V_GROUND_SPEED;

				Y_PRED1 = static_cast<float>((RTURNP * sin( TURNRAT * ReadCOMPOOL_SS( SCP_HDT1 ) )) + DELAZ * (RTURNP * (1.0 - cos( TURNRAT * ReadCOMPOOL_SS( SCP_HDT1 ) ))));
				X_PRED1 = static_cast<float>((RTURNP * (1.0 - cos( TURNRAT * ReadCOMPOOL_SS( SCP_HDT1 ) ))) - DELAZ * (RTURNP * sin( TURNRAT * ReadCOMPOOL_SS( SCP_HDT1 ) )));

				Y_PRED2 = static_cast<float>((RTURNP * sin( TURNRAT * ReadCOMPOOL_SS( SCP_HDT2 ) )) + DELAZ * (RTURNP * (1.0 - cos( TURNRAT * ReadCOMPOOL_SS( SCP_HDT2 ) ))));
				X_PRED2 = static_cast<float>((RTURNP * (1.0 - cos( TURNRAT * ReadCOMPOOL_SS( SCP_HDT2 ) ))) - DELAZ * (RTURNP * sin( TURNRAT * ReadCOMPOOL_SS( SCP_HDT2 ) )));
			
				Y_PRED3 = static_cast<float>((RTURNP * sin( TURNRAT * ReadCOMPOOL_SS( SCP_HDT3 ) )) + DELAZ * (RTURNP * (1.0 - cos( TURNRAT * ReadCOMPOOL_SS( SCP_HDT3 ) ))));
				X_PRED3 = static_cast<float>((RTURNP * (1.0 - cos( TURNRAT * ReadCOMPOOL_SS( SCP_HDT3 ) ))) - DELAZ * (RTURNP * sin( TURNRAT * ReadCOMPOOL_SS( SCP_HDT3 ) )));
			}

			// 20 Sec Position Predictor
			float X_20PRED = SCALE_FACTOR * X_PRED1 + ReadCOMPOOL_SS( SCP_HS_N_X );
			float Y_20PRED = SCALE_FACTOR * Y_PRED1 + ReadCOMPOOL_SS( SCP_HS_N_Y );
			WriteCOMPOOL_IS( SCP_X_20PRED, static_cast<unsigned short>(X_20PRED) );
			WriteCOMPOOL_IS( SCP_Y_20PRED, static_cast<unsigned short>(Y_20PRED) );

			// 40 Sec Position Predictor
			float X_40PRED = SCALE_FACTOR * X_PRED2 + ReadCOMPOOL_SS( SCP_HS_N_X );
			float Y_40PRED = SCALE_FACTOR * Y_PRED2 + ReadCOMPOOL_SS( SCP_HS_N_Y );
			WriteCOMPOOL_IS( SCP_X_40PRED, static_cast<unsigned short>(X_40PRED) );
			WriteCOMPOOL_IS( SCP_Y_40PRED, static_cast<unsigned short>(Y_40PRED) );

			// 60 Sec Position Predictor
			float X_60PRED = SCALE_FACTOR * X_PRED3 + ReadCOMPOOL_SS( SCP_HS_N_X );
			float Y_60PRED = SCALE_FACTOR * Y_PRED3 + ReadCOMPOOL_SS( SCP_HS_N_Y );
			WriteCOMPOOL_IS( SCP_X_60PRED, static_cast<unsigned short>(X_60PRED) );
			WriteCOMPOOL_IS( SCP_Y_60PRED, static_cast<unsigned short>(Y_60PRED) );



			// Horizontal and Vertical Scale Initialization
			if (((MM == 305) || ((MM == 603) && (IPHASE < 4))) && (init == false))
			{
				init = true;

				WriteCOMPOOL_IS( SCP_TGO_XTRACK_DISP, 9999 );
				WriteCOMPOOL_IS( SCP_HERROR_DISP, 9999 );

				WriteCOMPOOL_IS( SCP_DO_TGO_DISPLAY, 1 );
				WriteCOMPOOL_IS( SCP_DO_RERRC_DISPLAY, 0 );
				WriteCOMPOOL_IS( SCP_DO_Y_DISPLAY, 0 );
				WriteCOMPOOL_IS( SCP_DO_HERROR_DISPLAY, 1 );
				// TODO off in OPS1, etc

				YSGNPO = YSGNP;
				HAC_TIME_SNAPPED = 0;

				if (YSGNP > 0)
				{
					TGO_MIN = ReadCOMPOOL_SS( SCP_TGOSC );
				}
				else
				{
					TGO_MIN = 0;
				}

				TGO_SCALE_FACTOR = YSGNP * (HORIZ_SCALE_X1 - HORIZ_SCALE_X2) / ReadCOMPOOL_SS( SCP_TGOSC );

				for (int i = 1; i <= 5; i++)
				{
					WriteCOMPOOL_AIS( SCP_TGO_TICK_LOC, i, static_cast<unsigned short>(HORIZ_SCALE_X1 + (ReadCOMPOOL_VS( SCP_TGO_TICK_MARK, i, 5 ) - TGO_MIN) * TGO_SCALE_FACTOR), 5 );
				}

				for (int i = 1; i <= (ReadCOMPOOL_IS( SCP_HERROR_NO_DIV ) + 1); i++)
				{
					WriteCOMPOOL_AIS( SCP_HERROR_TICK_LOC, i, static_cast<unsigned short>(HERROR_SCALE_Y2 + ((i - 1) * ((HERROR_SCALE_Y1 - HERROR_SCALE_Y2) / ReadCOMPOOL_IS( SCP_HERROR_NO_DIV )))), 11 );
				}

				ReadCOMPOOL_C( SCP_HERROR_SC1_LABEL, tmpstr, 4 );
				WriteCOMPOOL_C( SCP_HERROR_LABEL, tmpstr, 4 );
				HERROR_MAX = ReadCOMPOOL_SS( SCP_HERRSC1 );
				HERROR_SCALE_FACTOR = (HERROR_SCALE_Y2 - HERROR_SCALE_Y1) / (2 * HERROR_MAX);
			}

			// Horizontal and Vertical Scale Reinitialization when YSGNP changes value
			if ((YSGNPO != YSGNP) && (ReadCOMPOOL_IS( SCP_DO_TGO_DISPLAY ) == 1))
			{
				if (YSGNP > 0)
				{
					TGO_MIN = ReadCOMPOOL_SS( SCP_TGOSC );
				}
				else
				{
					TGO_MIN = 0;
				}

				TGO_SCALE_FACTOR = YSGNP * (HORIZ_SCALE_X1 - HORIZ_SCALE_X2) / ReadCOMPOOL_SS( SCP_TGOSC );

				for (int i = 1; i <= 5; i++)
				{
					WriteCOMPOOL_AIS( SCP_TGO_TICK_LOC, i, static_cast<unsigned short>(HORIZ_SCALE_X1 + (ReadCOMPOOL_VS( SCP_TGO_TICK_MARK, i, 5 ) - TGO_MIN) * TGO_SCALE_FACTOR), 5 );
				}

				YSGNPO = YSGNP;
			}

			// Horizontal and Vertical Scale Computations
			if ((MM == 305) && (((TG_END == 0) && (IPHASE < 4)) || (TG_END == 1)))
			{
				if (ReadCOMPOOL_SD( SCP_ALT_WHEELS ) < ReadCOMPOOL_SS( SCP_H_BLANK ))
				{
					WriteCOMPOOL_IS( SCP_DO_TGO_DISPLAY, 0 );
					WriteCOMPOOL_IS( SCP_DO_RERRC_DISPLAY, 0 );
					WriteCOMPOOL_IS( SCP_DO_Y_DISPLAY, 0 );
					WriteCOMPOOL_IS( SCP_DO_HERROR_DISPLAY, 0 );
				}
				else
				{
					if ((ReadCOMPOOL_IS( SCP_DO_TGO_DISPLAY ) == 1) && (IPHASE == 2))
					{
						if (HAC_TIME_SNAPPED == 0)
						{
							HAC_TIME = static_cast<float>(simt)/*T_STATE*/;
							HAC_TIME_SNAPPED = 1;
						}
					}

					if (simt/*T_STATE*/ > (HAC_TIME + ReadCOMPOOL_IS( SCP_ROLL_STOW_DELAY_TIME )))
					{
						WriteCOMPOOL_IS( SCP_DO_TGO_DISPLAY, 0 );
						WriteCOMPOOL_IS( SCP_DO_RERRC_DISPLAY, 1 );
						RERRC_SCALE_FACTOR = (HORIZ_SCALE_X2 - HORIZ_SCALE_X1) / (2 * ReadCOMPOOL_SS( SCP_RERRCSC ));
						ReadCOMPOOL_C( SCP_RERRC_LABEL, tmpstr, 4 );
						WriteCOMPOOL_C( SCP_XTRACK_LABEL, tmpstr, 4 );

						for (int i = 1; i <= (ReadCOMPOOL_IS( SCP_XTRACK_NO_DIV ) + 1); i++)
						{
							WriteCOMPOOL_AIS( SCP_XTRACK_TICK_LOC, i, static_cast<unsigned short>(HORIZ_SCALE_X1 + ((i - 1) * ((HORIZ_SCALE_X2 - HORIZ_SCALE_X1) / ReadCOMPOOL_IS( SCP_XTRACK_NO_DIV )))), 11 );
						}
					}

					if (((ReadCOMPOOL_IS( SCP_DO_TGO_DISPLAY ) == 1) || (ReadCOMPOOL_IS( SCP_DO_RERRC_DISPLAY ) == 1)) && (IPHASE == 3))
					{
						WriteCOMPOOL_IS( SCP_DO_TGO_DISPLAY, 0 );
						WriteCOMPOOL_IS( SCP_DO_RERRC_DISPLAY, 0 );
						WriteCOMPOOL_IS( SCP_DO_Y_DISPLAY, 1 );
						Y_SCALE_FACTOR = (HORIZ_SCALE_X2 - HORIZ_SCALE_X1) / (2 * ReadCOMPOOL_SS( SCP_YSC ));
						ReadCOMPOOL_C( SCP_YSC_LABEL, tmpstr, 4 );
						WriteCOMPOOL_C( SCP_XTRACK_LABEL, tmpstr, 4 );

						for (int i = 1; i <= (ReadCOMPOOL_IS( SCP_XTRACK_NO_DIV ) + 1); i++)
						{
							WriteCOMPOOL_AIS( SCP_XTRACK_TICK_LOC, i, static_cast<unsigned short>(HORIZ_SCALE_X1 + ((i - 1) * ((HORIZ_SCALE_X2 - HORIZ_SCALE_X1) / ReadCOMPOOL_IS( SCP_XTRACK_NO_DIV )))), 11 );
						}
					}
				}
			}

			// Computation of the Time to HAC Intercept Predictor
			if (ReadCOMPOOL_IS( SCP_DO_TGO_DISPLAY ) == 1)
			{
				float TGO_XTRACK_DISP;

				float TGO_HAC = (ReadCOMPOOL_SS( SCP_RTAN ) - ReadCOMPOOL_SS( SCP_RTURN ) * sqrt( (ReadCOMPOOL_SS( SCP_P2TRNC1 ) * ReadCOMPOOL_SS( SCP_P2TRNC1 )) - 1 )) / V_GROUND_SPEED;

				if (TGO_HAC <= ReadCOMPOOL_SS( SCP_TGO_DISPLAY_CHAR ))
				{
					TGO_XTRACK_DISP = HORIZ_SCALE_X1 + (TGO_HAC - TGO_MIN) * TGO_SCALE_FACTOR;

					WriteCOMPOOL_IS( SCP_TGO_XTRACK_FLASH, 0 );

					if ((TGO_XTRACK_DISP < HORIZ_SCALE_X1) || (TGO_XTRACK_DISP > HORIZ_SCALE_X2))
					{
						WriteCOMPOOL_IS( SCP_TGO_XTRACK_FLASH, 1 );
					}

					TGO_XTRACK_DISP = static_cast<float>(midval( HORIZ_SCALE_X1, TGO_XTRACK_DISP, HORIZ_SCALE_X2 ));
				}
				else
				{
					TGO_XTRACK_DISP = 9999;// off-screen
				}

				WriteCOMPOOL_IS( SCP_TGO_XTRACK_DISP, static_cast<unsigned short>(TGO_XTRACK_DISP) );
			}

			// Computation of the HAC Radial Error Indicator
			if (ReadCOMPOOL_IS( SCP_DO_RERRC_DISPLAY ) == 1)
			{
				float TGO_XTRACK_DISP = HORIZ_SCALE_X1 + (ReadCOMPOOL_SS( SCP_RERRCSC ) - YSGNP * ReadCOMPOOL_SS( SCP_RERRC )) * RERRC_SCALE_FACTOR;

				WriteCOMPOOL_IS( SCP_TGO_XTRACK_FLASH, 0 );

				if ((TGO_XTRACK_DISP < HORIZ_SCALE_X1) || (TGO_XTRACK_DISP > HORIZ_SCALE_X2))
				{
					WriteCOMPOOL_IS( SCP_TGO_XTRACK_FLASH, 1 );
				}

				TGO_XTRACK_DISP = static_cast<float>(midval( HORIZ_SCALE_X1, TGO_XTRACK_DISP, HORIZ_SCALE_X2 ));

				WriteCOMPOOL_IS( SCP_TGO_XTRACK_DISP, static_cast<unsigned short>(TGO_XTRACK_DISP) );
			}

			// Computation of the Y Position Indicator
			if (ReadCOMPOOL_IS( SCP_DO_Y_DISPLAY ) == 1)
			{
				float Y = ReadCOMPOOL_VS( SCP_POSN_WRT_RW, 2, 3 );

				float TGO_XTRACK_DISP = HORIZ_SCALE_X1 + (Y + ReadCOMPOOL_SS( SCP_YSC )) * Y_SCALE_FACTOR;

				WriteCOMPOOL_IS( SCP_TGO_XTRACK_FLASH, 0 );

				if ((TGO_XTRACK_DISP < HORIZ_SCALE_X1) || (TGO_XTRACK_DISP > HORIZ_SCALE_X2))
				{
					WriteCOMPOOL_IS( SCP_TGO_XTRACK_FLASH, 1 );
				}

				TGO_XTRACK_DISP = static_cast<float>(midval( HORIZ_SCALE_X1, TGO_XTRACK_DISP, HORIZ_SCALE_X2 ));

				WriteCOMPOOL_IS( SCP_TGO_XTRACK_DISP, static_cast<unsigned short>(TGO_XTRACK_DISP) );
			}

			// Computation of the Altitude Error Indicator
			if (ReadCOMPOOL_IS( SCP_DO_HERROR_DISPLAY ) == 1)
			{
				if ((IPHASE == 3) || (TG_END == 1))
				{
					HERROR_MAX = ReadCOMPOOL_SS( SCP_HERRSC2 );
					ReadCOMPOOL_C( SCP_HERROR_SC2_LABEL, tmpstr, 4 );
					WriteCOMPOOL_C( SCP_HERROR_LABEL, tmpstr, 4 );
					HERROR_SCALE_FACTOR = (HERROR_SCALE_Y2 - HERROR_SCALE_Y1) / (2 * HERROR_MAX);
				}

				float HERR_GUID;
				if (TG_END == 0)
				{
					HERR_GUID = ReadCOMPOOL_SS( SCP_HERROR );
				}
				else
				{
					HERR_GUID = ReadCOMPOOL_SS( SCP_H_ERROR );
				}

				float HERROR_DISP = HERROR_SCALE_Y1 + (HERR_GUID + HERROR_MAX) * HERROR_SCALE_FACTOR;

				WriteCOMPOOL_IS( SCP_HERROR_FLASH, 0 );

				if ((HERROR_DISP > HERROR_SCALE_Y1) || (HERROR_DISP < HERROR_SCALE_Y2))
				{
					WriteCOMPOOL_IS( SCP_HERROR_FLASH, 1 );
				}

				HERROR_DISP = static_cast<float>(midval( HERROR_SCALE_Y1, HERROR_DISP, HERROR_SCALE_Y2 ));

				WriteCOMPOOL_IS( SCP_HERROR_DISP, static_cast<unsigned short>(HERROR_DISP) );
			}
		}
		else
		{
			// TODO off screen
			WriteCOMPOOL_IS( SCP_X_TAIL_COORD, 9999 );
			WriteCOMPOOL_IS( SCP_Y_TAIL_COORD, 9999 );
			WriteCOMPOOL_IS( SCP_X_HEAD_COORD, 9999 );
			WriteCOMPOOL_IS( SCP_Y_HEAD_COORD, 9999 );
			WriteCOMPOOL_IS( SCP_X_HAC, 9999 );
			WriteCOMPOOL_IS( SCP_Y_HAC, 9999 );
			WriteCOMPOOL_IS( SCP_RAD_HAC, 9999 );
			WriteCOMPOOL_IS( SCP_X_20PRED, 9999 );
			WriteCOMPOOL_IS( SCP_Y_20PRED, 9999 );
			WriteCOMPOOL_IS( SCP_X_40PRED, 9999 );
			WriteCOMPOOL_IS( SCP_Y_40PRED, 9999 );
			WriteCOMPOOL_IS( SCP_X_60PRED, 9999 );
			WriteCOMPOOL_IS( SCP_Y_60PRED, 9999 );
		}
		return;
	}

	bool HORIZ_SIT_SPEC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
				return true;
			default:
				return false;
		}
	}

	bool HORIZ_SIT_SPEC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void HORIZ_SIT_SPEC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}
