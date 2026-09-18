#include "XXXXXX_TRAJ_DIP.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	constexpr float DTC = 1.92f;// ALT/VEL UPDATE INTERVAL (V97U6762C) [s]


	XXXXXX_TRAJ_DIP::XXXXXX_TRAJ_DIP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "XXXXXX_TRAJ_DIP" ),
		step480ms(0.0), step960ms(0.0), step1920ms(0.0),
		firstpassA1(true), firstpassA2(true), firstpassR2(true),
		V0(0.0f), V1(0.0f), V2(0.0f), V3(0.0f),
		H0(0.0f), H1(0.0f), H2(0.0f), H3(0.0f),
		HDOT0(0.0f), HDOT1(0.0f), HDOT2(0.0f), HDOT3(0.0f),
		VI_FIRST_PASS_COMPL(0)
	{
		// HACK made coords really off screen
		WriteCOMPOOL_IS( SCP_A1_STATE_X, 800 );
		WriteCOMPOOL_IS( SCP_A1_STATE_Y, 400 );
		WriteCOMPOOL_IS( SCP_A1_PRED_X, 800 );
		WriteCOMPOOL_IS( SCP_A1_PRED_Y, 400 );
		WriteCOMPOOL_IS( SCP_A2_STATE_X, 800 );
		WriteCOMPOOL_IS( SCP_A2_STATE_Y, 400 );
		WriteCOMPOOL_IS( SCP_A2_PRED_X_30, 800 );
		WriteCOMPOOL_IS( SCP_A2_PRED_Y_30, 400 );
		WriteCOMPOOL_IS( SCP_A2_PRED_X_60, 800 );
		WriteCOMPOOL_IS( SCP_A2_PRED_Y_60, 400 );
		return;
	}

	XXXXXX_TRAJ_DIP::~XXXXXX_TRAJ_DIP( void )
	{
		return;
	}

	void XXXXXX_TRAJ_DIP::OnPreStep( double simt, double simdt, double mjd )
	{
		//bool run480ms = false;
		bool run960ms = false;
		bool run1920ms = false;

		step480ms += simdt;
		if (step480ms >= 0.48)
		{
			// enable 480ms/2.08Hz logic
			//run480ms = true;

			step960ms += step480ms;
			if (step960ms >= 0.96)
			{
				// enable 960ms/1.04Hz logic
				run960ms = true;

				step1920ms += step960ms;
				if (step1920ms >= 1.92)
				{
					// enable 1920ms/0.52Hz logic
					run1920ms = true;
				}
			}
		}
		else return;


		float ALT = ReadCOMPOOL_SS( SCP_ALT );

		if (run1920ms)
		{
			//// Computation of Ascent Display Dynamic Titles (.52 Hz)
			if (ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 1 );// LAUNCH TRAJ 1
			}
			else if ((ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) && 1/*TODO (ReadCOMPOOL_IS( SCP_RTLS_ABORT_DECLARED ) == 0)*/ && 1/*TODO (ReadCOMPOOL_IS( SCP_S_ATO ) == 0)*/)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 2 );// ASCENT TRAJ 1
			}
			else if ((ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) && 0/*TODO (ReadCOMPOOL_IS( SCP_RTLS_ABORT_DECLARED ) == 1)*/)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 3 );// RTLS TRAJ 1
			}
			else if ((ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) && 0/*TODO (ReadCOMPOOL_IS( SCP_S_ATO ) == 1)*/)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 5 );// ATO TRAJ 1
			}
			else if ((ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) && 1/*TODO (ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 0)*/ && 1/*TODO (ReadCOMPOOL_IS( SCP_S_ATO ) == 0)*/)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 6 );// ASCENT TRAJ 2
			}
			else if ((ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) && 0/*TODO (ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 1)*/)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 7 );// TAL TRAJ 2
			}
			else if ((ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) && 1/*TODO (ReadCOMPOOL_IS( SCP_S_ATO ) == 1)*/)
			{
				WriteCOMPOOL_IS( SCP_DISP_TITLE, 8 );// ATO TRAJ 2
			}
		}

		if (run960ms)
		{
			//// Computation of Remaining Propellant (MM 103 and MM 601) (1.04 Hz)
			if ((ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1))
			{
				/*unsigned short M = 123;// TODO
				double CURRENT_PRPLT = (32.174 * M) - ReadCOMPOOL_SS( SCP_R2_FINAL_WT );
				unsigned short PRPLT = static_cast<unsigned short>((CURRENT_PRPLT / ReadCOMPOOL_SS( SCP_TOTAL_PRPLT )) * 100);*/
				// HACK use existing logic for now, as needed mass properties are not yet defined
				short tmp = STS()->GetETPropellant();
				if (tmp < 0) tmp = 0;
	
				WriteCOMPOOL_IS( SCP_PRPLT, static_cast<unsigned short>(tmp) );
			}
		}

		//// Computation of Dynamic Symbols
		//// XXXXXX TRAJ 1 Display
		if (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1)
		{
			float H_DOT_ELLIPSOID = ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID );
			float REL_VEL_MAG = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );

			if (run960ms)
			{
				/// The Computation of the Altitude/Velocity Indicator (1.04 Hz)
				// X-COORDINATE
				double V_RHO_MAG = midval( ReadCOMPOOL_SS( SCP_A1_V_MIN ), REL_VEL_MAG, ReadCOMPOOL_SS( SCP_A1_V_MAX ) );
				unsigned short A1_STATE_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_A1_X_BIAS ) + (ReadCOMPOOL_SS( SCP_A1_X_SC_FACT ) * V_RHO_MAG));
				// Y-COORDINATE
				double H_ELLIPSOID = midval( ReadCOMPOOL_SS( SCP_A1_H_MIN ), ALT, ReadCOMPOOL_SS( SCP_A1_H_MAX ) );
				unsigned short A1_STATE_Y = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_A1_Y_BIAS ) + (ReadCOMPOOL_SS( SCP_A1_Y_SC_FACT ) * H_ELLIPSOID));

				WriteCOMPOOL_IS( SCP_A1_STATE_X, A1_STATE_X );
				WriteCOMPOOL_IS( SCP_A1_STATE_Y, A1_STATE_Y );

				/// The Computation of the Predicted Altitude/Velocity Indicator (1.04 Hz)
				// UPDATE PUSH-DOWN STACK AND COMPUTE DELTAS
				if (firstpassA1)
				{
					firstpassA1 = false;

					// init all with parameter
					V0 = REL_VEL_MAG;
					V1 = REL_VEL_MAG;
					V2 = REL_VEL_MAG;
					V3 = REL_VEL_MAG;
					H0 = ALT;
					H1 = ALT;
					H2 = ALT;
					H3 = ALT;
					HDOT0 = H_DOT_ELLIPSOID;
					HDOT1 = H_DOT_ELLIPSOID;
					HDOT2 = H_DOT_ELLIPSOID;
					HDOT3 = H_DOT_ELLIPSOID;
				}
				else
				{
					// shift and add parameter
					V0 = V1;
					V1 = V2;
					V2 = V3;
					V3 = REL_VEL_MAG;
					H0 = H1;
					H1 = H2;
					H2 = H3;
					H3 = ALT;
					HDOT0 = HDOT1;
					HDOT1 = HDOT2;
					HDOT2 = HDOT3;
					HDOT3 = H_DOT_ELLIPSOID;
				}
				double DELTA_V = midval( V3 - V2, V2 - V1, V1 - V0 );
				double DELTA_H = midval( H3 - H2, H2 - H1, H1 - H0 );
				double DELTA_HDOT = midval( HDOT3 - HDOT2, HDOT2 - HDOT1, HDOT1 - HDOT0 );

				// X-COORDINATE OF THE 20 SECOND PREDICTOR
				double VPRED_20 = V3 + ((DELTA_V / 0.96) * 20);
				double V_LIMIT_20 = midval( ReadCOMPOOL_SS( SCP_A1_V_MAX ), VPRED_20, ReadCOMPOOL_SS( SCP_A1_V_MIN ) );
				unsigned short A1_PRED_X = static_cast<unsigned short>((V_LIMIT_20 * ReadCOMPOOL_SS( SCP_A1_X_SC_FACT )) + ReadCOMPOOL_SS( SCP_A1_X_BIAS ));
				// Y-COORDINATE OF THE 20 SECOND PREDICTOR
				double HPRED_20 = H3 + ((DELTA_H / 0.96) * 20) + (0.5 * (DELTA_HDOT / 0.96) * pow( 20, 2 ));
				double H_LIMIT_20 = midval( ReadCOMPOOL_SS( SCP_A1_H_MAX ), HPRED_20, ReadCOMPOOL_SS( SCP_A1_H_MIN ) );
				unsigned short A1_PRED_Y = static_cast<unsigned short>((H_LIMIT_20 * ReadCOMPOOL_SS( SCP_A1_Y_SC_FACT )) + ReadCOMPOOL_SS( SCP_A1_Y_BIAS ));

				WriteCOMPOOL_IS( SCP_A1_PRED_X, A1_PRED_X );
				WriteCOMPOOL_IS( SCP_A1_PRED_Y, A1_PRED_Y );
			}
		}

		//// XXXXXX TRAJ 2 Display
		if (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1)
		{
			float H_DOT_ELLIPSOID = ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID );
			float V_INERTIAL_MAG = ReadCOMPOOL_SS( SCP_V_INERTIAL_MAG );

			if (run960ms)
			{
				/// The Computation of the Vehicle State Character (1.04 Hz)
				// X-COORDINATE
				double VI_PLOT = midval( ReadCOMPOOL_SS( SCP_A2_V_MIN ), V_INERTIAL_MAG, ReadCOMPOOL_SS( SCP_A2_V_MAX ) );
				unsigned short A2_STATE_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_A2_X_BIAS ) + (ReadCOMPOOL_SS( SCP_A2_X_SC_FACT ) * VI_PLOT));
				// Y-COORDINATE
				double H_ELLIPSOID = midval( ReadCOMPOOL_SS( SCP_A2_H_MIN ), ALT, ReadCOMPOOL_SS( SCP_A2_H_MAX ) );
				unsigned short A2_STATE_Y = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_A2_Y_BIAS ) + (ReadCOMPOOL_SS( SCP_A2_Y_SC_FACT ) * H_ELLIPSOID));

				WriteCOMPOOL_IS( SCP_A2_STATE_X, A2_STATE_X );
				WriteCOMPOOL_IS( SCP_A2_STATE_Y, A2_STATE_Y );

				/// The Computation of the Predicted Altitude/Velocity Indicators (1.04 Hz)
				// UPDATE PUSH-DOWN STACK AND COMPUTE DELTAS
				if (firstpassA2)
				{
					firstpassA2 = false;

					// init all with parameter
					V0 = V_INERTIAL_MAG;
					V1 = V_INERTIAL_MAG;
					V2 = V_INERTIAL_MAG;
					V3 = V_INERTIAL_MAG;
					H0 = ALT;
					H1 = ALT;
					H2 = ALT;
					H3 = ALT;
					HDOT0 = H_DOT_ELLIPSOID;
					HDOT1 = H_DOT_ELLIPSOID;
					HDOT2 = H_DOT_ELLIPSOID;
					HDOT3 = H_DOT_ELLIPSOID;
				}
				else
				{
					// shift and add parameter
					V0 = V1;
					V1 = V2;
					V2 = V3;
					V3 = V_INERTIAL_MAG;
					H0 = H1;
					H1 = H2;
					H2 = H3;
					H3 = ALT;
					HDOT0 = HDOT1;
					HDOT1 = HDOT2;
					HDOT2 = HDOT3;
					HDOT3 = H_DOT_ELLIPSOID;
				}
				double DELTA_V = midval( V3 - V2, V2 - V1, V1 - V0 );
				double DELTA_H = midval( H3 - H2, H2 - H1, H1 - H0 );
				double DELTA_HDOT = midval( HDOT3 - HDOT2, HDOT2 - HDOT1, HDOT1 - HDOT0 );

				// X-COORDINATE OF THE 30 SECOND PREDICTOR
				double VPRED_30 = V3 + ((DELTA_V / 0.96) * 30);
				double V_LIMIT_30 = midval( ReadCOMPOOL_SS( SCP_A2_V_MAX ), VPRED_30, ReadCOMPOOL_SS( SCP_A2_V_MIN ) );
				unsigned short A2_PRED_X_30 = static_cast<unsigned short>((V_LIMIT_30 * ReadCOMPOOL_SS( SCP_A2_X_SC_FACT )) + ReadCOMPOOL_SS( SCP_A2_X_BIAS ));
				// Y-COORDINATE OF THE 30 SECOND PREDICTOR
				double HPRED_30 = H3 + ((DELTA_H / 0.96) * 30) + (0.5 * (DELTA_HDOT / 0.96) * pow( 30, 2 ));
				double H_LIMIT_30 = midval( ReadCOMPOOL_SS( SCP_A2_H_MAX ), HPRED_30, ReadCOMPOOL_SS( SCP_A2_H_MIN ) );
				unsigned short A2_PRED_Y_30 = static_cast<unsigned short>((H_LIMIT_30 * ReadCOMPOOL_SS( SCP_A2_Y_SC_FACT )) + ReadCOMPOOL_SS( SCP_A2_Y_BIAS ));

				WriteCOMPOOL_IS( SCP_A2_PRED_X_30, A2_PRED_X_30 );
				WriteCOMPOOL_IS( SCP_A2_PRED_Y_30, A2_PRED_Y_30 );

				// X-COORDINATE OF THE 60 SECOND PREDICTOR
				double VPRED_60 = V3 + ((DELTA_V / 0.96) * 60);
				double V_LIMIT_60 = midval( ReadCOMPOOL_SS( SCP_A2_V_MAX ), VPRED_60, ReadCOMPOOL_SS( SCP_A2_V_MIN ) );
				unsigned short A2_PRED_X_60 = static_cast<unsigned short>((V_LIMIT_60 * ReadCOMPOOL_SS( SCP_A2_X_SC_FACT )) + ReadCOMPOOL_SS( SCP_A2_X_BIAS ));
				// Y-COORDINATE OF THE 60 SECOND PREDICTOR
				double HPRED_60 = H3 + ((DELTA_H / 0.96) * 60) + (0.5 * (DELTA_HDOT / 0.96) * pow( 60, 2 ));
				double H_LIMIT_60 = midval( ReadCOMPOOL_SS( SCP_A2_H_MAX ), HPRED_60, ReadCOMPOOL_SS( SCP_A2_H_MIN ) );
				unsigned short A2_PRED_Y_60 = static_cast<unsigned short>((H_LIMIT_60 * ReadCOMPOOL_SS( SCP_A2_Y_SC_FACT )) + ReadCOMPOOL_SS( SCP_A2_Y_BIAS ));

				WriteCOMPOOL_IS( SCP_A2_PRED_X_60, A2_PRED_X_60 );
				WriteCOMPOOL_IS( SCP_A2_PRED_Y_60, A2_PRED_Y_60 );
			}

			// The Computation of the Inertial Velocity Character (2.08 Hz)
			// X-COORDINATE
			if (0/*TODO ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED )*/ == 0)
			{
				double V2_PLOT = V_INERTIAL_MAG;
				V2_PLOT = midval( ReadCOMPOOL_SS( SCP_A2_VI_MIN ), V2_PLOT, ReadCOMPOOL_SS( SCP_A2_VI_MAX ) );
				unsigned short A2_VI_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_A2_X2_BIAS ) + (ReadCOMPOOL_SS( SCP_A2_X2_SC_FACT ) * V2_PLOT));
				WriteCOMPOOL_IS( SCP_A2_VI_X, A2_VI_X );
			}
			else
			{
				/*if (VI_FIRST_PASS_COMPL == 1)
				{
					double VDMAG = 0;// TODO
					double DEL_V_PLOT = VDMAG - V_INERTIAL_MAG;
					double V2_PLOT = ReadCOMPOOL_SS( SCP_A2_VI_MIN ) + ReadCOMPOOL_SS( SCP_DEL_V_MAX ) - DEL_V_PLOT;
					V2_PLOT = midval( ReadCOMPOOL_SS( SCP_A2_VI_MIN ), V2_PLOT, ReadCOMPOOL_SS( SCP_A2_VI_MAX ) );
					unsigned short A2_VI_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_A2_X2_BIAS ) + (ReadCOMPOOL_SS( SCP_A2_X2_SC_FACT ) * V2_PLOT));
					WriteCOMPOOL_IS( SCP_A2_VI_X, A2_VI_X );
				}
				else
				{
					VI_FIRST_PASS_COMPL = 1;
				}*/
			}
		}

		//// RTLS TRAJ 2 Display
		if (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1)
		{
			/*float REL_VEL_MAG = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );
			float V_HORIZ_DNRNG = 0.0f;// TODO

			if (run1920ms)
			{
				/// The Computation of the Altitude/Velocity Indicator (.52 Hz)
				// X-COORDINATE
				double REL_VEL_PLOT = midval( ReadCOMPOOL_SS( SCP_R2_V_MIN ), V_HORIZ_DNRNG, ReadCOMPOOL_SS( SCP_R2_V_MAX ) );
				unsigned short R2_STATE_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_X_BIAS ) + (ReadCOMPOOL_SS( SCP_R2_X_SC_FACT ) * REL_VEL_PLOT));
				// Y-COORDINATE
				double H_ELLIPSOID = midval( ReadCOMPOOL_SS( SCP_R2_H_MIN ), ALT, ReadCOMPOOL_SS( SCP_R2_H_MAX ) );
				unsigned short R2_STATE_Y = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_Y_BIAS_PASS ) + (ReadCOMPOOL_SS( SCP_R2_Y_SC_FACT ) * H_ELLIPSOID));

				WriteCOMPOOL_IS( SCP_R2_STATE_X, R2_STATE_X );
				WriteCOMPOOL_IS( SCP_R2_STATE_Y, R2_STATE_Y );

				/// The Computation of the Predicted Altitude/Velocity Indicator (.52 Hz)
				// X-COORDINATE
				// Update push-down stack
				if (firstpassR2)
				{
					firstpassR2 = false;

					// init all with parameter
					V1 = V_HORIZ_DNRNG;
					V2 = V_HORIZ_DNRNG;
					V3 = V_HORIZ_DNRNG;
					H1 = ALT;
					H2 = ALT;
					H3 = ALT;
				}
				else
				{
					// shift and add parameter
					V1 = V2;
					V2 = V3;
					V3 = V_HORIZ_DNRNG;
					H1 = H2;
					H2 = H3;
					H3 = ALT;
				}
				double VD1 = (V2 - V1) / DTC;
				double VD2 = (V3 - V2) / DTC;
				double VD = (VD1 + VD2) / 2;
				double V_PRED_2 = V2 + ((DTC + ReadCOMPOOL_SS( SCP_DT_4 )) * VD);
				double V_PRED_3 = V2 + ((DTC + ReadCOMPOOL_SS( SCP_DT5 )) * VD);
				V_PRED_2 = midval( ReadCOMPOOL_SS( SCP_R2_V_MIN ), V_PRED_2, ReadCOMPOOL_SS( SCP_R2_V_MAX ) );
				unsigned short R2_PRED_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_X_BIAS ) + (ReadCOMPOOL_SS( SCP_R2_X_SC_FACT ) * V_PRED_2));
				V_PRED_3 = midval( ReadCOMPOOL_SS( SCP_R2_V_MIN ), V_PRED_3, ReadCOMPOOL_SS( SCP_R2_V_MAX ) );
				unsigned short R2_PRED_X2 = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_X_BIAS ) + (ReadCOMPOOL_SS( SCP_R2_X_SC_FACT ) * V_PRED_3));
				// Y-COORDINATE
				double HD1 = (H2 - H1) / DTC;
				double HD2 = (H3 - H2) / DTC;
				double HD = (HD1 + HD2) / 2;
				double HDD = (HD2 - HD1) / DTC;
				double H_PRED_2 = H2 + ((ReadCOMPOOL_SS( SCP_DT_4 ) + DTC) * HD) + (pow( ReadCOMPOOL_SS( SCP_DT_4 ) + DTC, 2 ) * HDD / 2.0);
				double H_PRED_3 = H2 + ((ReadCOMPOOL_SS( SCP_DT5 ) + DTC) * HD) + (pow( ReadCOMPOOL_SS( SCP_DT5 ) + DTC, 2 ) * HDD / 2.0);
				H_PRED_2 = midval( ReadCOMPOOL_SS( SCP_R2_H_MIN ), H_PRED_2, ReadCOMPOOL_SS( SCP_R2_H_MAX ) );
				unsigned short R2_PRED_Y = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_Y_BIAS_PASS ) + (ReadCOMPOOL_SS( SCP_R2_Y_SC_FACT ) * H_PRED_2));
				H_PRED_3 = midval( ReadCOMPOOL_SS( SCP_R2_H_MIN ), H_PRED_3, ReadCOMPOOL_SS( SCP_R2_H_MAX ) );
				unsigned short R2_PRED_Y2 = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_Y_BIAS_PASS ) + (ReadCOMPOOL_SS( SCP_R2_Y_SC_FACT ) * H_PRED_3));

				WriteCOMPOOL_IS( SCP_R2_PRED_X, R2_PRED_X );
				WriteCOMPOOL_IS( SCP_R2_PRED_X2, R2_PRED_X2 );

				WriteCOMPOOL_IS( SCP_R2_PRED_Y, R2_PRED_Y );
				WriteCOMPOOL_IS( SCP_R2_PRED_Y2, R2_PRED_Y2 );
			}

			/// The Computation of the Delta Range Indicator (2.08 Hz)
			// COMPUTE DELTA R
			double REL_VEL_PLOT;
			if (V_HORIZ_DNRNG < 0)
			{
				REL_VEL_PLOT = -REL_VEL_MAG;
			}
			else
			{
				REL_VEL_PLOT = REL_VEL_MAG;
			}
			double RP = (ReadCOMPOOL_SS( SCP_R2_RP_1 ) * REL_VEL_PLOT) + ReadCOMPOOL_SS( SCP_R2_RP_2 ) + (ReadCOMPOOL_SS( SCP_R2_RP_3 ) * ReadCOMPOOL_SS( SCP_FLT_PATH_ANG ));
			float DELTA_R = static_cast<float>(RP - ReadCOMPOOL_IS( SCP_RNG_TO_RW_THRESH ));
			// X-COORDINATE
			double DEL_R = midval( ReadCOMPOOL_SS( SCP_R2_D_R_MIN ), DELTA_R, ReadCOMPOOL_SS( SCP_R2_D_R_MAX ) );
			unsigned short R2_D_R_X = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_R2_D_R_BIAS ) + (ReadCOMPOOL_SS( SCP_R2_D_R_SC_FACT ) * DEL_R));

			WriteCOMPOOL_IS( SCP_R2_D_R_X, R2_D_R_X );
			WriteCOMPOOL_SS( SCP_DELTA_R, DELTA_R );

			if (run1920ms)
			{
				/// Computation of the RTLS Guidance Status Parameter (GUID) (.52 Hz)
				// TODO
				// MF_DISPLAY
				// S_UNCONV
				// GUID_XXXX_CHAR
				// GUID_XXXX_DEC
			}*/
		}

		// reset
		step480ms = 0.0;
		if (run960ms)
		{
			step960ms = 0.0;

			if (run1920ms)
			{
				step1920ms = 0.0;
			}
		}
		return;
	}

	bool XXXXXX_TRAJ_DIP::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short ustmp = 0;

		if (!_strnicmp( keyword, "V0", 2 ))
		{
			sscanf_s( value, "%f", &V0 );
		}
		else if (!_strnicmp( keyword, "V1", 2 ))
		{
			sscanf_s( value, "%f", &V1 );
		}
		else if (!_strnicmp( keyword, "V2", 2 ))
		{
			sscanf_s( value, "%f", &V2 );
		}
		else if (!_strnicmp( keyword, "V3", 2 ))
		{
			sscanf_s( value, "%f", &V3 );
		}
		else if (!_strnicmp( keyword, "H0", 2 ))
		{
			sscanf_s( value, "%f", &H0 );
		}
		else if (!_strnicmp( keyword, "H1", 2 ))
		{
			sscanf_s( value, "%f", &H1 );
		}
		else if (!_strnicmp( keyword, "H2", 2 ))
		{
			sscanf_s( value, "%f", &H2 );
		}
		else if (!_strnicmp( keyword, "H3", 2 ))
		{
			sscanf_s( value, "%f", &H3 );
		}
		else if (!_strnicmp( keyword, "HDOT0", 6 ))
		{
			sscanf_s( value, "%f", &HDOT0 );
		}
		else if (!_strnicmp( keyword, "HDOT1", 6 ))
		{
			sscanf_s( value, "%f", &HDOT1 );
		}
		else if (!_strnicmp( keyword, "HDOT2", 6 ))
		{
			sscanf_s( value, "%f", &HDOT2 );
		}
		else if (!_strnicmp( keyword, "HDOT3", 6 ))
		{
			sscanf_s( value, "%f", &HDOT3 );
		}
		else if (!_strnicmp( keyword, "step480ms", 10 ))
		{
			sscanf_s( value, "%lf", &step480ms );
		}
		else if (!_strnicmp( keyword, "step960ms", 10 ))
		{
			sscanf_s( value, "%lf", &step960ms );
		}
		else if (!_strnicmp( keyword, "step1920ms", 11 ))
		{
			sscanf_s( value, "%lf", &step1920ms );
		}
		else if (!_strnicmp( keyword, "firstpassA1", 15 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			firstpassA1 = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "firstpassA2", 15 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			firstpassA2 = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "firstpassR2", 12 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			firstpassR2 = (ustmp == 1);
		}
		else return false;

		return true;
	}

	void XXXXXX_TRAJ_DIP::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "V0", V0 );
		oapiWriteScenario_float( scn, "V1", V1 );
		oapiWriteScenario_float( scn, "V2", V2 );
		oapiWriteScenario_float( scn, "V3", V3 );
		oapiWriteScenario_float( scn, "H0", H0 );
		oapiWriteScenario_float( scn, "H1", H1 );
		oapiWriteScenario_float( scn, "H2", H2 );
		oapiWriteScenario_float( scn, "H3", H3 );
		oapiWriteScenario_float( scn, "HDOT0", HDOT0 );
		oapiWriteScenario_float( scn, "HDOT1", HDOT1 );
		oapiWriteScenario_float( scn, "HDOT2", HDOT2 );
		oapiWriteScenario_float( scn, "HDOT3", HDOT3 );

		oapiWriteScenario_float( scn, "step480ms", step480ms );
		oapiWriteScenario_float( scn, "step960ms", step960ms );
		oapiWriteScenario_float( scn, "step1920ms", step1920ms );

		oapiWriteScenario_int( scn, "firstpassA1", firstpassA1 );
		oapiWriteScenario_int( scn, "firstpassA2", firstpassA2 );
		oapiWriteScenario_int( scn, "firstpassR2", firstpassR2 );
		return;
	}
}
