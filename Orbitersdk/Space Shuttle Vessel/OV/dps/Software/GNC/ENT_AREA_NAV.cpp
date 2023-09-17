#include "ENT_AREA_NAV.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	// I-Loads TODO
	constexpr float X_GSI_HI_WIND = -6500.0f;// TODO XA(2)?
	constexpr float X_GSI_NOMINAL = -7500.0f;// TODO XA(1)?
	constexpr float RADIUS_EP = 14000.0f;// TODO Radius of entry point HAC (V99U6873C) [ft]
	constexpr float RESELVE = 5000.0f;// TODO Overhead correction termination velocity (V99U7680C) [fps]

	// K-Loads
	constexpr float H_GSI_SHALLOW = 1500.0f;// (V97U9022C) [ft]

	// constants
	constexpr float NAUTMI_PER_FT = 0.00016457884f;// FEET TO NAUTICAL MILES CONVERSION FACTOR (V97U5423C) [NM/ft]


	ENT_AREA_NAV::ENT_AREA_NAV( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ENT_AREA_NAV" )
	{
		FIRST_PASS = 1;
		LEFT_SIDE = 1;
		IGS = 1;
		MASS_FLAG = 1;
		OVHD_LAST = 1;
		P = 0.0f;
		ARC_LEFT = 0.0f;
		ARC_RIGHT = 0.0f;
		RTURN_HSI_LEFT = 0.0f;
		RTURN_HSI_RIGHT = 0.0f;
		ALT_LAND = 0.0f;
		X_GSI = 0.0f;
		R_VEH_RW = _V( 0.0, 0.0, 0.0 );
		DELX_NEP = 0.0f;
		DELX_REF = 0.0f;
		DELX_MEP = 0.0f;
		X_EP = 0.0f;
		PSD_HSI = 0.0f;
		V_HSI = 0.0f;
		VH_HSI = 0.0f;
		H = 0.0f;

		N = 1;
		SOURCE = 1;
		MODE = 1;
		RCVR = 1;

		PRI_BEAR = 0.0f;
		PRI_RANGE = 0.0f;
		CDI = 0.0f;
		GSI = 0.0f;
		HEADING = 0.0f;
		HSI_MODE_INDICATOR = 1;
		BRG_FLAG = 0;
		GSI_FLAG = 0;
		CDI_FLAG = 0;
		SEC_BEAR = 0.0f;
		SEC_RANGE = 0.0f;

		FIRST_PASS_TAEM = 0;
		return;
	}

	ENT_AREA_NAV::~ENT_AREA_NAV( void )
	{
		return;
	}

	void ENT_AREA_NAV::OnPostStep( double simt, double simdt, double mjd )
	{
		// fill C0, C1, C2, C3, CUBRC, HCO, HMEP
		float HALI[2];
		HALI[0] = 0.0f;// TODO
		HALI[1] = 0.0f;// TODO
		float PBHC[2];
		PBHC[0] = 0.0f;// TODO
		PBHC[1] = 0.0f;// TODO
		float TGGS[2];
		TGGS[0] = 0.0f;// TODO
		TGGS[1] = 0.0f;// TODO
		float PBGC[2];
		PBGC[0] = 0.0f;// TODO
		PBGC[1] = 0.0f;// TODO
		float CUBIC_C3[2];
		CUBIC_C3[0] = 0.0f;// TODO
		CUBIC_C3[1] = 0.0f;// TODO
		float CUBIC_C4[2];
		CUBIC_C4[0] = 0.0f;// TODO
		CUBIC_C4[1] = 0.0f;// TODO
		float PBRC[2];
		PBRC[0] = 0.0f;// TODO
		PBRC[1] = 0.0f;// TODO
		float HFTC[2];
		HFTC[0] = 0.0f;// TODO
		HFTC[1] = 0.0f;// TODO
		float _HMEP[2];
		_HMEP[0] = 0.0f;// TODO
		_HMEP[1] = 0.0f;// TODO

		C0[0][0] = HALI[0];
		C0[1][0] = HALI[1];
		C0[0][1] = PBHC[0];
		C0[1][1] = PBHC[1];

		C1[0][0] = TGGS[0];
		C1[1][0] = TGGS[1];
		C1[0][1] = PBGC[0];
		C1[1][1] = PBGC[1];

		C2[0][0] = CUBIC_C3[0];
		C2[1][0] = CUBIC_C3[1];
		C2[0][1] = 0.0f;
		C2[1][1] = 0.0f;

		C3[0][0] = CUBIC_C4[0];
		C3[1][0] = CUBIC_C4[1];
		C3[0][1] = 0.0f;
		C3[1][1] = 0.0f;

		CUBRC[0] = PBRC[0];
		CUBRC[1] = PBRC[1];

		HCO[0] = HFTC[0];
		HCO[1] = HFTC[1];

		HMEP[0] = _HMEP[0];
		HMEP[1] = _HMEP[1];


		HSI_SEQUENCER();
		return;
	}

	void ENT_AREA_NAV::HSI_SEQUENCER( void )
	{
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short OVHD = ReadCOMPOOL_IS( SCP_OVHD );
		unsigned short NUM_GPS_INSTALLED = 0;// TODO
		unsigned short HI_WINDS = 0;// TODO

		if (FIRST_PASS == 1)
		{
			FIRST_PASS = 0;
			P = ReadCOMPOOL_SS( SCP_YSGN );// TODO YSGNP
			OVHD_LAST = OVHD;
			ARC_LEFT = ReadCOMPOOL_SS( SCP_PSHARS );
			ARC_RIGHT = ReadCOMPOOL_SS( SCP_PSHARS );

			MASS_FLAG = 1;
		}

		LEFT_SIDE = 1;

		for (int i = 1; i <= 2; i++)
		{
			if (LEFT_SIDE == 1)
			{
				SOURCE = ReadCOMPOOL_IS( SCP_SOURCE_LEFT );
				MODE = ReadCOMPOOL_IS( SCP_MODE_LEFT );
				RCVR = ReadCOMPOOL_IS( SCP_RCVR_LEFT );
			}
			else
			{
				SOURCE = ReadCOMPOOL_IS( SCP_SOURCE_RIGHT );
				MODE = ReadCOMPOOL_IS( SCP_MODE_RIGHT );
				RCVR = ReadCOMPOOL_IS( SCP_RCVR_RIGHT );
			}

			BRG_FLAG = 1;
			GSI_FLAG = 1;
			CDI_FLAG = 1;

			if (SOURCE == 2/*NAV*/)
			{
				NAV_STATE_TO_RW();
			}
			else
			{
				if (RCVR == 1)
				{
					N = 1;
				}
				else if (RCVR == 2)
				{
					N = 2;
				}
				else
				{
					N = 3;
				}

				if (SOURCE == 1/*TACAN/GPS*/)
				{
					if (NUM_GPS_INSTALLED < 3) TAC_BARO_TO_RW();
					else GPS_TO_RW();
				}
				else
				{
					MSBLS_TO_RW();
				}
			}


			if (OVHD != OVHD_LAST)
			{
				ARC_LEFT = ReadCOMPOOL_SS( SCP_PSHARS );
				ARC_RIGHT = ReadCOMPOOL_SS( SCP_PSHARS );
			}

			if ((OVHD == 0) || (length( ReadCOMPOOL_VD( SCP_V_RHO_EF ) ) > RESELVE) || ((OVHD != OVHD_LAST) && (BRG_FLAG == 0)))
			{
				// recompute P for overhead
				P = static_cast<float>(-sign( R_VEH_RW.data[1] ));
				OVHD_LAST = OVHD;

				if (OVHD == 0)
				{
					// recompute P for straight-in
					P = -P;
				}
			}


			if ((MODE == 3/*ENTRY*/) && ((MM == 602) || (MM == 304)))
			{
				ENTRY_HSI_COMP();
			}
			else
			{
				CDI = static_cast<float>(atan2( -R_VEH_RW.data[1], 16300 - R_VEH_RW.data[0] ) * DEG);
				HEADING = static_cast<float>(ReadCOMPOOL_SS( SCP_PSI_HSIMV ) * DEG);

				if (MASS_FLAG == 1)
				{
					float M_GSI = ReadCOMPOOL_SS( SCP_WT_GS1 );
					float M = ReadCOMPOOL_SS( SCP_WEIGHT );
					if ((M < M_GSI) || ((MM == 602) || (MM == 603)))
					{
						IGS = 1;
					}
					else
					{
						IGS = 2;
					}

					DELX_NEP = HCO[IGS - 1] / C1[IGS - 1][0];
					DELX_REF = C0[IGS - 1][0] / C1[IGS - 1][0];
					DELX_MEP = HMEP[IGS - 1] / C1[IGS - 1][0];
					MASS_FLAG = 0;
					ALT_LAND = HCO[IGS - 1];
				}

				if (HI_WINDS == 0)
				{
					X_GSI = X_GSI_NOMINAL;
				}
				else
				{
					X_GSI = X_GSI_HI_WIND;
				}

				if ((MODE == 1/*LAND*/) || ((MODE == 3/*ENTRY*/) && (H < ALT_LAND)) || ((MODE == 3/*ENTRY*/) && (H < (ALT_LAND + 6000)) && (fabs( CDI ) < (0.044 * DEG))))
				{
					LAND_HSI_COMP();
				}
				else
				{
					if (ReadCOMPOOL_IS( SCP_NEP_FB ) == 1)
					{
						X_EP = X_GSI + DELX_NEP;
						ALT_LAND = HCO[IGS - 1];
					}
					else
					{
						X_EP = X_GSI + DELX_MEP;
						ALT_LAND = HMEP[IGS - 1];
					}

					TAEM_HSI_COMP();
					GSI = 0.2f * GSI;
					CDI = 0.25f * CDI;
				}
			}

			if (LEFT_SIDE == 1)
			{
				WriteCOMPOOL_SS( SCP_PRIBEAR_LEFT, PRI_BEAR );
				WriteCOMPOOL_SS( SCP_PRIRANGE_LEFT, PRI_RANGE );
				WriteCOMPOOL_SS( SCP_CDI_LEFT, CDI );
				WriteCOMPOOL_SS( SCP_GSI_LEFT, GSI );
				WriteCOMPOOL_SS( SCP_HEADING_LEFT, HEADING );
				WriteCOMPOOL_IS( SCP_HSI_MODE_LEFT, HSI_MODE_INDICATOR );
				WriteCOMPOOL_IS( SCP_HDG_FLAG_LEFT, 1 );
				WriteCOMPOOL_IS( SCP_BRG_FLAG_LEFT, BRG_FLAG );
				WriteCOMPOOL_IS( SCP_GSI_FLAG_LEFT, GSI_FLAG );
				WriteCOMPOOL_IS( SCP_CDI_FLAG_LEFT, CDI_FLAG );
				WriteCOMPOOL_SS( SCP_SECBEAR_LEFT, SEC_BEAR );
				WriteCOMPOOL_SS( SCP_SECRANGE_LEFT, SEC_RANGE );
			}
			else
			{
				WriteCOMPOOL_SS( SCP_PRIBEAR_RIGHT, PRI_BEAR );
				WriteCOMPOOL_SS( SCP_PRIRANGE_RIGHT, PRI_RANGE );
				WriteCOMPOOL_SS( SCP_CDI_RIGHT, CDI );
				WriteCOMPOOL_SS( SCP_GSI_RIGHT, GSI );
				WriteCOMPOOL_SS( SCP_HEADING_RIGHT, HEADING );
				WriteCOMPOOL_IS( SCP_HSI_MODE_RIGHT, HSI_MODE_INDICATOR );
				WriteCOMPOOL_IS( SCP_HDG_FLAG_RIGHT, 1 );
				WriteCOMPOOL_IS( SCP_BRG_FLAG_RIGHT, BRG_FLAG );
				WriteCOMPOOL_IS( SCP_GSI_FLAG_RIGHT, GSI_FLAG );
				WriteCOMPOOL_IS( SCP_CDI_FLAG_RIGHT, CDI_FLAG );
				WriteCOMPOOL_SS( SCP_SECBEAR_RIGHT, SEC_BEAR );
				WriteCOMPOOL_SS( SCP_SECRANGE_RIGHT, SEC_RANGE );
			}

			LEFT_SIDE = 0;
		}

		WriteCOMPOOL_IS( SCP_MEDS_AREA_NAV_FIRST_PASS, 1 );
		return;
	}

	void ENT_AREA_NAV::NAV_STATE_TO_RW( void )
	{
		R_VEH_EF = ReadCOMPOOL_VD( SCP_R_EF );
		R_VEH_RW = {ReadCOMPOOL_SS( SCP_X ), ReadCOMPOOL_SS( SCP_Y ), ReadCOMPOOL_SS( SCP_Z )};// POSITION_WRT_RUNWAY;
		PSD_HSI = 0.0f;// COURSE_WRT_RW RAD_PER_DEG
		V_HSI = 0.0f;// REL_VEL_MAG
		VH_HSI = 0.0f;// V_GROUNDSPEED
		H = 0.0f;// ALT_WHEELS
		return;
	}

	void ENT_AREA_NAV::TAC_BARO_TO_RW( void )
	{
		NAV_STATE_TO_RW();
		// TODO
		return;
	}

	void ENT_AREA_NAV::TAC_BARO_TO_TOPODETIC( void )
	{
		// TODO
		return;
	}

	void ENT_AREA_NAV::GPS_TO_RW( void )
	{
		NAV_STATE_TO_RW();
		// TODO
		return;
	}

	void ENT_AREA_NAV::MSBLS_TO_RW( void )
	{
		NAV_STATE_TO_RW();
		// TODO
		return;
	}

	void ENT_AREA_NAV::ENTRY_HSI_COMP( void )
	{
		VECTOR3 R_EF = ReadCOMPOOL_VD( SCP_R_EF );
		VECTOR3 V_RHO_EF = ReadCOMPOOL_VD( SCP_V_RHO_EF );
		float ANGLE_CORR_TNTOMAG_RW = ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW );
		float AZIMUTH_RW = ReadCOMPOOL_SS( SCP_AZIMUTH_RW );
		float R_VEH_MAG_UPP = 0.0f;// TODO

		// VECTOR3 R_VEH_EF - position vector from the selected source
		VECTOR3 R_CC_R_PRI = ReadCOMPOOL_VS( SCP_R_CC_L_PRI );
		VECTOR3 R_CC_L_PRI = ReadCOMPOOL_VS( SCP_R_CC_L_PRI );
		float R_CC_RMAG_PRI = ReadCOMPOOL_SS( SCP_R_CC_RMAG_PRI );
		float R_CC_LMAG_PRI = ReadCOMPOOL_SS( SCP_R_CC_LMAG_PRI );
		VECTOR3 V_NORM = crossp( R_EF, V_RHO_EF );
		double PSI = atan2( V_NORM.data[2] * R_VEH_MAG_UPP, (R_EF.data[1] * V_NORM.data[0]) - (V_NORM.data[1] * R_EF.data[0]) );
		HEADING = static_cast<float>((PSI - ANGLE_CORR_TNTOMAG_RW) * DEG);

		if (HEADING < 0) HEADING += 360;

		float R_VEH_MAG = static_cast<float>(length( R_VEH_EF ));

		if (P > 0)
		{
			RANGE_BEAR_TO_HAC_ENTRY( R_CC_R_PRI, R_CC_RMAG_PRI, ReadCOMPOOL_IS( SCP_OVHD ), P, R_VEH_MAG, R_VEH_EF, AZIMUTH_RW, ANGLE_CORR_TNTOMAG_RW, PRI_RANGE, PRI_BEAR );
		}
		else
		{
			RANGE_BEAR_TO_HAC_ENTRY( R_CC_L_PRI, R_CC_LMAG_PRI, ReadCOMPOOL_IS( SCP_OVHD ), P, R_VEH_MAG, R_VEH_EF, AZIMUTH_RW, ANGLE_CORR_TNTOMAG_RW, PRI_RANGE, PRI_BEAR );
		}

		SEC_RANGE = PRI_RANGE;
		SEC_BEAR = PRI_BEAR;

		GSI = 0.0f;
		CDI = 0.0f;
		CDI_FLAG = 0;
		HSI_MODE_INDICATOR = 1;
		return;
	}

	void ENT_AREA_NAV::TAEM_HSI_COMP( void )
	{
		float ANGLE_CORR_TNTOMAG_RW = ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW );
		float AZIMUTH_RW = ReadCOMPOOL_SS( SCP_AZIMUTH_RW );
		unsigned short NUM_GPS_INSTALLED = 0;// TODO
		float R1 = ReadCOMPOOL_SS( SCP_R1 );
		float R2 = ReadCOMPOOL_SS( SCP_R2 );
		float X_WP2 = ReadCOMPOOL_SS( SCP_X_AIM );// TODO

		if (FIRST_PASS_TAEM == 1)
		{
			float PSHA = ReadCOMPOOL_SS( SCP_PSHA );
			float RTURN = ReadCOMPOOL_SS( SCP_RTURN );
			ARC_LEFT = PSHA;
			ARC_RIGHT = PSHA;
			RTURN_HSI_LEFT = RTURN;
			RTURN_HSI_RIGHT = RTURN;
			FIRST_PASS_TAEM = 0;
		}

		double SIGNY_HSI = sign( R_VEH_RW.data[1] );

		double R0;
		if (SOURCE == 2/*NAV*/)
		{
			R0 = ReadCOMPOOL_SS( SCP_RF );
		}
		else
		{
			R0 = ReadCOMPOOL_SS( SCP_RF0 );
		}

		double Y_CC = (P * R0) - R_VEH_RW.data[1];
		double X_CC = X_EP - R_VEH_RW.data[0];
		double R_CC = sqrt( (X_CC * X_CC) + (Y_CC * Y_CC) );
		double PHI = atan2( Y_CC, X_CC );

		if (PHI < 0)
		{
			PHI += PI2;
		}

		float RTURN_HSI;
		if (LEFT_SIDE == 1)
		{
			RTURN_HSI = RTURN_HSI_LEFT;
		}
		else
		{
			RTURN_HSI = RTURN_HSI_RIGHT;
		}

		double DIST_VEH_WP1;
		double BEAR_RW;
		if (R_CC < RTURN_HSI)
		{
			// on or inside HAC
			DIST_VEH_WP1 = 0;
			BEAR_RW = PHI - (P * PI05);
		}
		else
		{
			// outside HAC
			double THETA = asin( RTURN_HSI / R_CC );
			DIST_VEH_WP1 = sqrt( (R_CC * R_CC) - (RTURN_HSI * RTURN_HSI) );
			BEAR_RW = PHI - (P * THETA);
		}

		if (fabs( BEAR_RW ) > PI)
		{
			BEAR_RW -= sign( BEAR_RW ) * PI2;
		}

		float A3 = static_cast<float>(-P * BEAR_RW * DEG);

		if (BEAR_RW < 0)
		{
			BEAR_RW += PI2;
		}

		float ARC;// HAC turn angle
		if (LEFT_SIDE == 1)
		{
			ARC = ARC_LEFT;
		}
		else
		{
			ARC = ARC_RIGHT;
		}

		if (((ARC > (ReadCOMPOOL_SS( SCP_PSHARS ) + 1)) || (A3 < -1) || (P != SIGNY_HSI)) && (ARC > 90))
		{
			A3 += 360;
		}

		if (LEFT_SIDE == 1)
		{
			ARC_LEFT = A3;
		}
		else
		{
			ARC_RIGHT = A3;
		}

		ARC = A3;

		RTURN_HSI = static_cast<float>(R0 + ((R1 + (R2 * ARC)) * ARC));
		double D_ARC = ((R0 * ARC) + (0.5 * R1 * ARC * ARC) + (0.333333 * R2 * ARC * ARC)) * RAD;

		if (LEFT_SIDE == 1)
		{
			RTURN_HSI_LEFT = RTURN_HSI;
		}
		else
		{
			RTURN_HSI_RIGHT = RTURN_HSI;
		}

		if (((SOURCE == 2/*NAV*/) || ((SOURCE == 1/*TAC/GPS*/) && (NUM_GPS_INSTALLED == 3))) && (ReadCOMPOOL_IS( SCP_IPHASE ) < 2))
		{
			float PHAVGC = 0.0f;// TODO
			float PHAVGS = 0.0f;// TODO
			float PHAVGLL = 0.0f;// TODO
			float PHAVGUL = 0.0f;// TODO
			float MACH = ReadCOMPOOL_SS( SCP_VE ) * 0.001f;// TODO

			double DPSAC = BEAR_RW - PSD_HSI;
			
			if (fabs( DPSAC ) > PI)
			{
				DPSAC -= sign( DPSAC ) * PI2;
			}

			double PHAVG = PHAVGC - (PHAVGS * MACH);
			PHAVG = midval( PHAVG, PHAVGLL, PHAVGUL );
			double RTAC = VH_HSI * V_HSI / (G * MPS2FPS * tan( PHAVG * RAD ));
			double ARCAC = RTAC * fabs( DPSAC );

			double A = RTAC * (1.0 - cos( DPSAC ));
			double B = DIST_VEH_WP1 - (RTAC * fabs( sin( DPSAC ) ));
			double RC = sqrt( (A * A) + (B * B) );
			DIST_VEH_WP1 = ARCAC + RC;
		}

		double RANGE_FT = DIST_VEH_WP1 + D_ARC - X_EP + X_WP2;
		PRI_RANGE = static_cast<float>((RANGE_FT * NAUTMI_PER_FT) * 10);
		PRI_BEAR = static_cast<float>((BEAR_RW + (AZIMUTH_RW - ANGLE_CORR_TNTOMAG_RW)) * DEG);

		if (PRI_BEAR > 360)
		{
			PRI_BEAR -= 360;
		}

		SEC_BEAR = static_cast<float>((PHI + (AZIMUTH_RW - ANGLE_CORR_TNTOMAG_RW)) * DEG);
		SEC_RANGE = static_cast<float>(10 * R_CC * NAUTMI_PER_FT);

		if (SEC_BEAR > 360)
		{
			SEC_BEAR -= 360;
		}

		double R = RANGE_FT + X_GSI + DELX_REF - X_WP2;
		double DR = R - CUBRC[IGS - 1];

		double HREF;
		if (DR < 0)
		{
			HREF = C0[IGS - 1][0] + (C1[IGS - 1][0] * R) + (C2[IGS - 1][0] * R * R) + (C3[IGS - 1][0] * R * R * R);
		}
		else
		{
			HREF = C0[IGS - 1][1] + (C1[IGS - 1][1] * R) + (C2[IGS - 1][1] * R * R) + (C3[IGS - 1][1] * R * R * R);
		}

		GSI = static_cast<float>(H - HREF);
		HSI_MODE_INDICATOR = 2;
		return;
	}

	void ENT_AREA_NAV::LAND_HSI_COMP( void )
	{
		float ANGLE_CORR_TNTOMAG_RW = ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW );
		float AZIMUTH_RW = ReadCOMPOOL_SS( SCP_AZIMUTH_RW );
		float X_WP2 = ReadCOMPOOL_SS( SCP_X_AIM );// TODO

		double D = X_WP2 - R_VEH_RW.data[0];
		PRI_BEAR = static_cast<float>((atan2( -R_VEH_RW.data[1], D ) + AZIMUTH_RW - ANGLE_CORR_TNTOMAG_RW) * DEG);

		if (PRI_BEAR < 0)
		{
			PRI_BEAR += 360;
		}
		else
		{
			if (PRI_BEAR > 360)
			{
				PRI_BEAR -= 360;
			}
		}

		double DIST_WP2 = sqrt( (R_VEH_RW.data[1] * R_VEH_RW.data[1]) + (D * D) );
		PRI_RANGE = static_cast<float>((DIST_WP2 * NAUTMI_PER_FT) * 10);
		SEC_RANGE = PRI_RANGE;
		SEC_BEAR = PRI_BEAR;

		if (H > H_GSI_SHALLOW)
		{
			double R = DIST_WP2 + X_GSI + DELX_REF - X_WP2;
			double HREF = C0[IGS - 1][0] + (C1[IGS - 1][0] * R);
			GSI = static_cast<float>(H - HREF);
		}
		else
		{
			GSI_FLAG = 0;
		}

		HSI_MODE_INDICATOR = 3;
		return;
	}

	void ENT_AREA_NAV::RANGE_BEAR_TO_HAC_ENTRY( const VECTOR3& R_CC_EF, const float R_CC_MAG, const unsigned short OVHD, const float P, const float R_VEH_MAG, const VECTOR3& R_VEH_EF, const float AZIMUTH_RW, const float ANGLE_CORR_TNTOMAG_RW, float& RANGE, float& BEARING )
	{
		float X_WP2 = ReadCOMPOOL_SS( SCP_X_AIM );// TODO
		float X_NEP = ReadCOMPOOL_SS( SCP_XHAC );// TODO

		VECTOR3 V_NORM = crossp( R_VEH_EF, R_CC_EF );

		double BEAR_VEH = atan2( V_NORM.data[2] * R_VEH_MAG, V_NORM.data[0] * R_VEH_EF.data[1] - V_NORM.data[1] * R_VEH_EF.data[0] );
		double BEAR_CC = atan2( V_NORM.data[2] * R_CC_MAG, V_NORM.data[0] * R_CC_EF.data[1] - V_NORM.data[1] * R_CC_EF.data[0] );

		if (BEAR_CC < 0) BEAR_CC += PI2;

		double SIN_THET_VEH_CC = length( V_NORM ) / (R_VEH_MAG * R_CC_MAG);

		double DIST_VEH_WP1 = asin( SIN_THET_VEH_CC ) * R_CC_MAG;
		double A2 = RADIUS_EP / DIST_VEH_WP1;
		double BEAR_VEH_WP1 = BEAR_VEH - (P * A2);
		double A3 = A2 + (P * (AZIMUTH_RW - BEAR_CC));

		if (A3 < -0.003) A3 += PI2;
		if ((A3 < PI05) && (OVHD == 1)) A3 += PI2;

		double D_ARC = A3 * RADIUS_EP;

		RANGE = static_cast<float>((DIST_VEH_WP1 + D_ARC - X_NEP + X_WP2) * NAUTMI_PER_FT);
		BEARING = static_cast<float>((BEAR_VEH_WP1 - ANGLE_CORR_TNTOMAG_RW) * DEG);
		if (BEARING < 0) BEARING += 360;
		return;
	}

	bool ENT_AREA_NAV::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 602:// TODO check this
			case 603:
				return true;
			default:
				return false;
		}
	}

	bool ENT_AREA_NAV::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ENT_AREA_NAV::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}
