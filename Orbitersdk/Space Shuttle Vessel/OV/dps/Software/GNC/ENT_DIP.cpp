#include "ENT_DIP.h"
#include <EngConst.h>
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr double VSAT = 25766.2;// Local circular orbit velocity (V97U0439C) [fp]


	ENT_DIP::ENT_DIP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ENT_DIP" ),
		FIRST_PASS(1), I(1), TRAILER_NO(1), ELAPSED_TIME(0.0), SHUTTLE_X_PREV(-400), SHUTTLE_Y_PREV(-400), GUID_X_PREV(-400)
	{
		return;
	}

	ENT_DIP::~ENT_DIP( void )
	{
		return;
	}

	void ENT_DIP::OnPreStep( double simt, double simdt, double mjd )
	{
		// INFO logic and associated I-Loads using "flipped" Y axis, conversion to display coordinates done in ENTRY TRAJ
		// ENT DIP	display
		// Y = 0	Y = 731
		// Y = 731	Y = 0

		float REL_VEL_MAG = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );
		float DELAZ = ReadCOMPOOL_SS( SCP_DELAZ );
		float ACC_DRAG = ReadCOMPOOL_SS( SCP_ACC_DRAG );
		float ALPHA = ReadCOMPOOL_SS( SCP_ALPHA );
		float ACMD1 = ReadCOMPOOL_SS( SCP_ACMD1 );
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		float DREFP = ReadCOMPOOL_SS( SCP_DREFP );
		float YL = ReadCOMPOOL_SS( SCP_YL );
		float E_S_Y_MAX = ReadCOMPOOL_SS( SCP_E_S_Y_MAX );
		float E_S_Y_MIN = ReadCOMPOOL_SS( SCP_E_S_Y_MIN );
		float P_S_X_MAX = ReadCOMPOOL_SS( SCP_P_S_X_MAX );
		float P_S_X_MIN = ReadCOMPOOL_SS( SCP_P_S_X_MIN );

		//// Central Plot Symbols
		/// Computation of the Shuttle Character
		if (FIRST_PASS == 1)
		{
			I = 1;
			WriteCOMPOOL_IS( SCP_DISP_IND, 1 );
			FIRST_PASS = 0;

			// init outside of display
			WriteCOMPOOL_IS( SCP_GUID_X, -400 );
			WriteCOMPOOL_IS( SCP_GUID_Y, -400 );
			WriteCOMPOOL_IS( SCP_DRAG_REF_Y, -400 );
			for (int i = 1; i <= 6; i++)
			{
				WriteCOMPOOL_AIS( SCP_TRAILER_X, i, -400, 6 );
				WriteCOMPOOL_AIS( SCP_TRAILER_Y, i, -400, 6 );
				WriteCOMPOOL_AIS( SCP_GUID_TRAILER_X, i, -400, 6 );
			}

			SHUTTLE_X_PREV = -400;
			SHUTTLE_Y_PREV = -400;
			GUID_X_PREV = -400;
		}
		// Y-Coordinate
		short SHUTTLE_YN = static_cast<short>(ReadCOMPOOL_ASS( SCP_VC0, I, 5 ) + (ReadCOMPOOL_ASS( SCP_VC1, I, 5 ) * (ReadCOMPOOL_SD( SCP_ALT_WHEELS ) + pow( REL_VEL_MAG, 2 ) / (2 * G * MPS2FPS))) + (ReadCOMPOOL_ASS( SCP_VC2, I, 5 ) * REL_VEL_MAG));
		if ((SHUTTLE_YN < ReadCOMPOOL_SS( SCP_E_G_Y_MIN )) || ((I == ReadCOMPOOL_IS( SCP_I_TRAN )) && (ISLECT == 5)))
		{
			if (I < 5)// HACK added sanity check to prevent invalid value in I
			{
				I = I + 1;
				WriteCOMPOOL_IS( SCP_DISP_IND, I );

				// recalc
				SHUTTLE_YN = static_cast<unsigned short>(ReadCOMPOOL_ASS( SCP_VC0, I, 5 ) + (ReadCOMPOOL_ASS( SCP_VC1, I, 5 ) * (ReadCOMPOOL_SD( SCP_ALT_WHEELS ) + pow( REL_VEL_MAG, 2 ) / (2 * G * MPS2FPS))) + (ReadCOMPOOL_ASS( SCP_VC2, I, 5 ) * REL_VEL_MAG));

				for (int i = 1; i <= 6; i++)
				{
					WriteCOMPOOL_AIS( SCP_TRAILER_X, i, -400, 6 );
					WriteCOMPOOL_AIS( SCP_TRAILER_Y, i, -400, 6 );
					WriteCOMPOOL_AIS( SCP_GUID_TRAILER_X, i, -400, 6 );
				}

				SHUTTLE_X_PREV = -400;
				SHUTTLE_Y_PREV = -400;
				GUID_X_PREV = -400;
			}
		}

		// X-Coordinate
		double RNG_TO_WP2 = min(ReadCOMPOOL_SS( SCP_RNG_TO_RW_THRESH ), -ReadCOMPOOL_ASS( SCP_HC1, I, 5 ) / (2 * ReadCOMPOOL_ASS( SCP_HC2, I, 5 )));
		short SHUTTLE_XN = static_cast<short>(ReadCOMPOOL_ASS( SCP_HC0, I, 5 ) + (ReadCOMPOOL_ASS( SCP_HC1, I, 5 ) * RNG_TO_WP2) + (ReadCOMPOOL_ASS( SCP_HC2, I, 5 ) * pow( RNG_TO_WP2, 2 )));

		// Limit X-Coordinate
		SHUTTLE_XN = static_cast<short>(midval( ReadCOMPOOL_SS( SCP_E_G_X_MIN ), SHUTTLE_XN, ReadCOMPOOL_SS( SCP_E_G_X_MAX ) ));

		WriteCOMPOOL_IS( SCP_SHUTTLE_X, static_cast<unsigned short>(SHUTTLE_XN + ReadCOMPOOL_SS( SCP_DXS )) );
		WriteCOMPOOL_IS( SCP_SHUTTLE_Y, static_cast<unsigned short>(SHUTTLE_YN + ReadCOMPOOL_SS( SCP_DYS )) );

		/// Computation of Shuttle Trailers
		bool trailer_computed = false;
		if ((((I == 1) || (I == 2)) && (ELAPSED_TIME >= 28.8)) ||
			(((I == 3) || (I == 4) || (I == 5)) && (ELAPSED_TIME >= 15.36)))
		{
			WriteCOMPOOL_AIS( SCP_TRAILER_X, TRAILER_NO, SHUTTLE_X_PREV, 6 );
			WriteCOMPOOL_AIS( SCP_TRAILER_Y, TRAILER_NO, SHUTTLE_Y_PREV, 6 );
			ELAPSED_TIME = 0.0;
			trailer_computed = true;
		}

		ELAPSED_TIME += simdt;

		// hACK moved below to only update after guidance trailer calc
		/*if (TRAILER_NO == 6)
		{
			TRAILER_NO = 1;
		}
		else
		{
			TRAILER_NO = TRAILER_NO + 1;
		}*/

		SHUTTLE_X_PREV = SHUTTLE_XN;
		SHUTTLE_Y_PREV = SHUTTLE_YN;

		/// Computation of Guidance Character
		if (ISLECT > 1)
		{
			double REF_RANGE = RNG_TO_WP2 - (ReadCOMPOOL_SS( SCP_DRDD ) * (ACC_DRAG - DREFP));
			WriteCOMPOOL_IS( SCP_GUID_X, static_cast<unsigned short>(ReadCOMPOOL_ASS( SCP_HC0, I, 5 ) + (ReadCOMPOOL_ASS( SCP_HC1, I, 5 ) * REF_RANGE) + (ReadCOMPOOL_ASS( SCP_HC2, I, 5 ) * pow( REF_RANGE, 2 ))) );
			WriteCOMPOOL_IS( SCP_GUID_Y, SHUTTLE_YN );
		}

		/// Computation of Guidance Trailer
		if ((ISLECT > 1) && trailer_computed)
		{
			WriteCOMPOOL_AIS( SCP_GUID_TRAILER_X, TRAILER_NO, GUID_X_PREV, 6 );
		}

		// HACK moved from above to only update after guidance trailer calc
		if (trailer_computed)
		{
			if (TRAILER_NO == 6)
			{
				TRAILER_NO = 1;
			}
			else
			{
				TRAILER_NO = TRAILER_NO + 1;
			}
		}

		GUID_X_PREV = ReadCOMPOOL_IS( SCP_GUID_X );

		/// Computation of the Alternate Landing Site Characters 
		// TODO

		/// Computation of the Bank Angle Flash Flag
		if (((ReadCOMPOOL_SS( SCP_BANK ) * DELAZ) > 0) && (fabs( DELAZ ) > YL))
		{
			WriteCOMPOOL_IS( SCP_BANK_FLAG, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_BANK_FLAG, 0 );
		}


		//// Drag Scale Symbols
		/// Computation of Actual Drag Acceleration Symbol Position
		double DRAG_ACC_Y = E_S_Y_MIN + (ReadCOMPOOL_SS( SCP_D_SCALE_FACT ) * ACC_DRAG);

		if (DRAG_ACC_Y > E_S_Y_MAX)
		{
			DRAG_ACC_Y = E_S_Y_MAX;
			WriteCOMPOOL_IS( SCP_DRAG_ACC_FLAG, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_DRAG_ACC_FLAG, 0 );
		}
		WriteCOMPOOL_IS( SCP_DRAG_ACC_Y, static_cast<unsigned short>(DRAG_ACC_Y) );

		/// Computation of Reference Drag Symbol Position
		if (ISLECT > 1)
		{
			double DRAG_REF_Y = E_S_Y_MIN + (ReadCOMPOOL_SS( SCP_D_SCALE_FACT ) * DREFP);

			if (DRAG_REF_Y > E_S_Y_MAX)
			{
				DRAG_REF_Y = E_S_Y_MAX;
				WriteCOMPOOL_IS( SCP_DRAG_REF_FLAG, 1 );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_DRAG_REF_FLAG, 0 );
			}

			WriteCOMPOOL_IS( SCP_DRAG_REF_Y, static_cast<unsigned short>(DRAG_REF_Y) );
		}


		//// Alpha Scale Symbols
		/// Computation of Actual Angle of Attack Symbol Position
		double ACC_ALPHA_Y = E_S_Y_MIN + (ReadCOMPOOL_SS( SCP_AL_SCALE_FACT ) * (ALPHA - ReadCOMPOOL_ASS( SCP_INIT_AL_VAL, I, 5 )));

		if (ACC_ALPHA_Y < E_S_Y_MIN)
		{
			ACC_ALPHA_Y = E_S_Y_MIN;
			WriteCOMPOOL_IS( SCP_ACC_ALPHA_FLAG, 1 );
		}
		if (ACC_ALPHA_Y > E_S_Y_MAX)
		{
			ACC_ALPHA_Y = E_S_Y_MAX;
			WriteCOMPOOL_IS( SCP_ACC_ALPHA_FLAG, 1 );
		}
		if (fabs( ALPHA - ACMD1 ) > 2.0)
		{
			WriteCOMPOOL_IS( SCP_ACC_ALPHA_FLAG, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_ACC_ALPHA_FLAG, 0 );
		}

		WriteCOMPOOL_IS( SCP_ACC_ALPHA_Y, static_cast<unsigned short>(ACC_ALPHA_Y) );

		/// Computation of Nominal Alpha Command Reference Symbol Position
		double COM_ALPHA_Y = E_S_Y_MIN + (ReadCOMPOOL_SS( SCP_AL_SCALE_FACT ) * (ACMD1 - ReadCOMPOOL_ASS( SCP_INIT_AL_VAL, I, 5 )));

		if (COM_ALPHA_Y < E_S_Y_MIN)
		{
			COM_ALPHA_Y = E_S_Y_MIN;
			WriteCOMPOOL_IS( SCP_COM_ALPHA_FLAG, 1 );
		}
		if (COM_ALPHA_Y > E_S_Y_MAX)
		{
			COM_ALPHA_Y = E_S_Y_MAX;
			WriteCOMPOOL_IS( SCP_COM_ALPHA_FLAG, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_COM_ALPHA_FLAG, 0 );
		}

		WriteCOMPOOL_IS( SCP_COM_ALPHA_Y, static_cast<unsigned short>(COM_ALPHA_Y) );


		//// REF ROLL STATUS
		float ROLRFC = ReadCOMPOOL_SS( SCP_ROLRF1 ) + ReadCOMPOOL_SS( SCP_ROLRF2 ) * REL_VEL_MAG;

		if (REL_VEL_MAG > ReadCOMPOOL_SS( SCP_VROLF1 ))
		{
			ROLRFC = ReadCOMPOOL_SS( SCP_ROLRF3 ) + ReadCOMPOOL_SS( SCP_ROLRF4 ) * REL_VEL_MAG;
		}

		if (REL_VEL_MAG > ReadCOMPOOL_SS( SCP_VROLF2 ))
		{
			ROLRFC = ReadCOMPOOL_SS( SCP_ROLRF5 ) + ReadCOMPOOL_SS( SCP_ROLRF6 ) * REL_VEL_MAG;
		}

		if (REL_VEL_MAG > ReadCOMPOOL_SS( SCP_VROLF3 ))
		{
			ROLRFC = ReadCOMPOOL_SS( SCP_ROLRF7 ) + ReadCOMPOOL_SS( SCP_ROLRF8 ) * REL_VEL_MAG;
		}

		if (fabs( /*ROLLC(3)*/ReadCOMPOOL_SS( SCP_ROLLREF ) ) < ROLRFC)
		{
			WriteCOMPOOL_IS( SCP_REF_ROL_STAT, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_REF_ROL_STAT, 0 );
		}


		//// PHUGOID BANK Symbol
		if (REL_VEL_MAG < ReadCOMPOOL_SS( SCP_V_TEST ))
		{
			float BANK_ANGLE = ReadCOMPOOL_SS( SCP_BANK );
			double DIR_ROL = 1 * sign( BANK_ANGLE );
			double DLZRL = DELAZ * DIR_ROL;

			if (DLZRL >= YL)
			{
				DIR_ROL = -DIR_ROL;
			}
			float D_BASE = ReadCOMPOOL_SS( SCP_DC1 );
			if (REL_VEL_MAG >= ReadCOMPOOL_SS( SCP_VC1_PHU ))
			{
				D_BASE = ReadCOMPOOL_SS( SCP_DC2 ) + (ReadCOMPOOL_SS( SCP_DC3 ) * REL_VEL_MAG);
			}
			if (REL_VEL_MAG < ReadCOMPOOL_SS( SCP_VC2_PHU ))
			{
				D_BASE = ReadCOMPOOL_SS( SCP_DC4 ) + (ReadCOMPOOL_SS( SCP_DC5 ) * REL_VEL_MAG);
			}
			short BIAS_ITEM = ReadCOMPOOL_IS( SCP_BIAS_ITEM );
			float D_REF = D_BASE + BIAS_ITEM;
			float HDTREF = -2 * ReadCOMPOOL_SS( SCP_H_SCAL ) * D_REF / REL_VEL_MAG;
			double ALDRFD = (-(G * MPS2FPS) * ((pow( ReadCOMPOOL_SS( SCP_V_MAG ), 2 ) / pow( VSAT, 2 )) - 1) / D_REF) + (2 * HDTREF / REL_VEL_MAG);
			double LODVD = (ALDRFD + (ReadCOMPOOL_SS( SCP_K16 ) * (ACC_DRAG - D_REF)) + (ReadCOMPOOL_SS( SCP_K17 ) * (HDTREF - ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID )))) / ReadCOMPOOL_SS( SCP_LOD );
			if (fabs( LODVD ) >= 1)
			{
				LODVD = 1 * sign( LODVD );
				double BCD = DIR_ROL * acos( LODVD );
				double ALPHA_R = ALPHA * RAD/*RAD_PER_DEG*/;
				double RCD = atan2( sin( BCD ), cos( ALPHA_R ) * cos( BCD ) ) * DEG/*DEG_PER_RAD*/;
				double ROLERR = RCD - ReadCOMPOOL_SS( SCP_PHI );

				double X_PHUGOID_BK = P_S_X_MIN + ((P_S_X_MAX - P_S_X_MIN) / 2) + (ReadCOMPOOL_SS( SCP_PH_SCALE_FACT ) * ROLERR);

				if (X_PHUGOID_BK > P_S_X_MAX)
				{
					X_PHUGOID_BK = P_S_X_MAX;
					WriteCOMPOOL_IS( SCP_X_PHUGOID_FLAG, 1 );
				}
				else if (X_PHUGOID_BK < P_S_X_MIN)
				{
					X_PHUGOID_BK = P_S_X_MIN;
					WriteCOMPOOL_IS( SCP_X_PHUGOID_FLAG, 1 );
				}
				else
				{
					WriteCOMPOOL_IS( SCP_X_PHUGOID_FLAG, 0 );
				}

				WriteCOMPOOL_IS( SCP_X_PHUGOID_BK, static_cast<unsigned short>(X_PHUGOID_BK) );
			}

			WriteCOMPOOL_SS( SCP_D_REF, D_REF );
		}
		return;
	}
}
