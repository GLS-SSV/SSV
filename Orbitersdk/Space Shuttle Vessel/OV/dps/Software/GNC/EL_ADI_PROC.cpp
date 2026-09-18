#include "EL_ADI_PROC.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr float GPITCH = 1.0f;// (V99U7577C) [1]
	constexpr float GROLL = 0.1f;// (V99U7576C) [1]


	EL_ADI_PROC::EL_ADI_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "EL_ADI_PROC" ),
		firstpass304602(true), firstpass305603r(true), firstpass305603e(true),
		DO_ADI_TGO_DISPLAY(true), DISPLAY_RATE_MED(false), STOW_MED(false), HAC_TIME_SNAPPED(false), ALT_TIME_SNAPPED(false), HAC_TIME(0.0f), ALT_TIME(0.0f),
		IPHASE_PREV(0), RW_ID_PREV(0), YSGN_PREV(0.0f), NEP_FB_PREV(0), CSSRY_IND_PREV(0), CSSP_IND_PREV(0), ZERO_PR_INT(false), ZERO_R_INT(false), ZERO_P_INT(false), ZERO_5_INT(false),
		RERR_INTP(0.0f), RERR_INTN(0.0f), NZ_INTP(0.0f), NZ_INTN(0.0f)
	{
		return;
	}

	EL_ADI_PROC::~EL_ADI_PROC( void )
	{
		return;
	}

	void EL_ADI_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO FOH

		// inputs
		unsigned short MM_CODE_301 = ReadCOMPOOL_IS( SCP_MM_CODE_301 );
		unsigned short MM_CODE_302 = ReadCOMPOOL_IS( SCP_MM_CODE_302 );
		unsigned short MM_CODE_303 = ReadCOMPOOL_IS( SCP_MM_CODE_303 );
		unsigned short MM_CODE_304 = ReadCOMPOOL_IS( SCP_MM_CODE_304 );
		unsigned short MM_CODE_305 = ReadCOMPOOL_IS( SCP_MM_CODE_305 );
		unsigned short MM_CODE_602 = ReadCOMPOOL_IS( SCP_MM_CODE_602 );
		unsigned short MM_CODE_603 = ReadCOMPOOL_IS( SCP_MM_CODE_603 );
		float ROLLSINE1 = ReadCOMPOOL_ASS( SCP_ROLLSINE, 1, 3 );
		float ROLLSINE2 = ReadCOMPOOL_ASS( SCP_ROLLSINE, 2, 3 );
		float ROLLCOS1 = ReadCOMPOOL_ASS( SCP_ROLLCOS, 1, 3 );
		float ROLLCOS2 = ReadCOMPOOL_ASS( SCP_ROLLCOS, 2, 3 );
		float PTCHSINE1 = ReadCOMPOOL_ASS( SCP_PTCHSINE, 1, 3 );
		float PTCHSINE2 = ReadCOMPOOL_ASS( SCP_PTCHSINE, 2, 3 );
		float PTCHCOS1 = ReadCOMPOOL_ASS( SCP_PTCHCOS, 1, 3 );
		float PTCHCOS2 = ReadCOMPOOL_ASS( SCP_PTCHCOS, 2, 3 );
		float YAWSINE1 = ReadCOMPOOL_ASS( SCP_YAWSINE, 1, 3 );
		float YAWSINE2 = ReadCOMPOOL_ASS( SCP_YAWSINE, 2, 3 );
		float YAWCOS1 = ReadCOMPOOL_ASS( SCP_YAWCOS, 1, 3 );
		float YAWCOS2 = ReadCOMPOOL_ASS( SCP_YAWCOS, 2, 3 );
		float P_ORB = ReadCOMPOOL_SS( SCP_P_ORB );
		float Q_ORB = ReadCOMPOOL_SS( SCP_Q_ORB );
		float R_ORB = ReadCOMPOOL_SS( SCP_R_ORB );
		float P_STAB = ReadCOMPOOL_SS( SCP_P_STAB );
		float R_STAB = ReadCOMPOOL_SS( SCP_R_STAB );
		unsigned short LADIRSW = ReadCOMPOOL_IS( SCP_LADIRSW );
		unsigned short RADIRSW = ReadCOMPOOL_IS( SCP_RADIRSW );
		unsigned short LADIESW = ReadCOMPOOL_IS( SCP_LADIESW );
		unsigned short RADIESW = ReadCOMPOOL_IS( SCP_RADIESW );
		unsigned short IPHASE = ReadCOMPOOL_IS( SCP_IPHASE );
		// HACK convert xADIRSW from [1,2,3] (output from GNC SW RM) to [-1,0,+1] (usage here)
		{
			if (LADIRSW == 1) LADIRSW = -1;
			else if (LADIRSW == 3) LADIRSW = 1;
			else /*if (LADIRSW == 2)*/ LADIRSW = 0;

			if (RADIRSW == 1) RADIRSW = -1;
			else if (RADIRSW == 3) RADIRSW = 1;
			else /*if (RADIRSW == 2)*/ RADIRSW = 0;

			if (LADIESW == 1) LADIESW = -1;
			else if (LADIESW == 3) LADIESW = 1;
			else /*if (LADIESW == 2)*/ LADIESW = 0;

			if (RADIESW == 1) RADIESW = -1;
			else if (RADIESW == 3) RADIESW = 1;
			else /*if (RADIESW == 2)*/ RADIESW = 0;
		}
		float T_STATE = static_cast<float>(simt);
		double ALT_WHEELS = ReadCOMPOOL_SD( SCP_ALT_WHEELS );
		unsigned short WOWLON = ReadCOMPOOL_IS( SCP_WOWLON_IND );
		float RTAN = ReadCOMPOOL_SS( SCP_RTAN );
		float RTURN = ReadCOMPOOL_SS( SCP_RTURN );
		float V_GROUNDSPEED = ReadCOMPOOL_SS( SCP_V_GROUNDSPEED );
		float YSGNP = ReadCOMPOOL_SS( SCP_YSGNP );
		float HERROR = ReadCOMPOOL_SS( SCP_HERROR );
		float H_ERROR = ReadCOMPOOL_SS( SCP_H_ERROR );
		unsigned short TG_END = ReadCOMPOOL_IS( SCP_TG_END );
		float DPSAC = ReadCOMPOOL_SS( SCP_DPSAC );
		float RERRC = ReadCOMPOOL_SS( SCP_RERRC );
		float Y = ReadCOMPOOL_VS( SCP_POSN_WRT_RW, 2, 3 );
		unsigned short RW_ID = ReadCOMPOOL_IS( SCP_RW_ID );
		unsigned short NEP_FB = ReadCOMPOOL_IS( SCP_NEP_FB );
		unsigned short CSSRY_IND = ReadCOMPOOL_IS( SCP_CSSRY_IND );
		unsigned short CSSP_IND = ReadCOMPOOL_IS( SCP_CSSP_IND );
		float BODY_ERR_ANG[3];
		BODY_ERR_ANG[0] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 1, 3 );
		BODY_ERR_ANG[1] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 2, 3 );
		BODY_ERR_ANG[2] = ReadCOMPOOL_VS( SCP_BODY_ERR_ANG, 3, 3 );
		float PHI = ReadCOMPOOL_SS( SCP_PHI );
		float ROLLC1 = ReadCOMPOOL_SS( SCP_ROLLCMD );
		float PHIC_AT = ReadCOMPOOL_SS( SCP_PHIC_AT );
		float PHIC_AL = ReadCOMPOOL_SS( SCP_PHIC_AL );
		float ALFERR_FDC = ReadCOMPOOL_SS( SCP_ALPHA_N ) - ReadCOMPOOL_SS( SCP_ALPCMD );
		float NZERRFD = ReadCOMPOOL_SS( SCP_NZERR );// TODO
		float QFFDC = 0.0;// TODO
		float BETA_FDC = ReadCOMPOOL_SS( SCP_BETA_N );// TODO
		float PSI_HSIMV = ReadCOMPOOL_SS( SCP_PSI_HSIMV );

		// outputs
		unsigned short LADIRS = 0;
		unsigned short RADIRS = 0;
		unsigned short LADIRC = 0;
		unsigned short RADIRC = 0;
		unsigned short LADIPS = 0;
		unsigned short RADIPS = 0;
		unsigned short LADIPC = 0;
		unsigned short RADIPC = 0;
		unsigned short LADIYS = 0;
		unsigned short RADIYS = 0;
		unsigned short LADIYC = 0;
		unsigned short RADIYC = 0;
		unsigned short LADIRR = 0;
		unsigned short RADIRR = 0;
		unsigned short LADIPR = 0;
		unsigned short RADIPR = 0;
		unsigned short LADIYR = 0;
		unsigned short RADIYR = 0;
		unsigned short MEDS_LH_TGOSC_FLAG = 0;
		unsigned short MEDS_RH_TGOSC_FLAG = 0;
		unsigned short MEDS_LADIRR_SCALE = 0;
		unsigned short MEDS_RADIRR_SCALE = 0;
		unsigned short MEDS_LADIPR_SCALE = 0;
		unsigned short MEDS_RADIPR_SCALE = 0;
		unsigned short MEDS_LADIYR_SCALE = 0;
		unsigned short MEDS_RADIYR_SCALE = 0;
		unsigned short MEDS_LADIPE_SCALE = 0;
		unsigned short MEDS_RADIPE_SCALE = 0;
		unsigned short LADIRE = 0;
		unsigned short RADIRE = 0;
		unsigned short LADIPE = 0;
		unsigned short RADIPE = 0;
		unsigned short LADIYE = 0;
		unsigned short RADIYE = 0;
		unsigned short HUD_ROLLERR = 0;
		unsigned short HUD_PITCHERR = 0;
		unsigned short HUD_HEADING = 0;


		// Left ADI Control Word (LADIWORD1) 160 ms
		unsigned short LADI_C2 = 1;
		unsigned short LADI_C3 = 1;
		unsigned short LADI_C4 = 1;
		unsigned short LADI_C5 = 1;
		unsigned short LADI_C6 = 1;
		unsigned short LADI_C7 = 1;
		unsigned short LADI_C8 = 1;
		unsigned short LADI_C9 = 1;
		unsigned short LADI_C10 = 1;
		unsigned short LADI_C11 = 1;
		unsigned short LADI_C12 = 1;
		unsigned short LADI_C13 = 1;
		unsigned short LADI_C14 = 1;
		unsigned short LADIWORD1 = (LADI_C2 << 15) | (LADI_C3 << 14) | (LADI_C4 << 13) | (LADI_C5 << 12) | (LADI_C6 << 11) | (LADI_C7 << 10) |
			(LADI_C8 << 9) | (LADI_C9 << 8) | (LADI_C10 << 7) | (LADI_C11 << 6) | (LADI_C12 << 5) | (LADI_C13 << 4) | (LADI_C14 << 3);

		// Right ADI Control Word (RADIWORD1) 160 ms
		unsigned short RADI_C2 = 1;
		unsigned short RADI_C3 = 1;
		unsigned short RADI_C4 = 1;
		unsigned short RADI_C5 = 1;
		unsigned short RADI_C6 = 1;
		unsigned short RADI_C7 = 1;
		unsigned short RADI_C8 = 1;
		unsigned short RADI_C9 = 1;
		unsigned short RADI_C10 = 1;
		unsigned short RADI_C11 = 1;
		unsigned short RADI_C12 = 1;
		unsigned short RADI_C13 = 1;
		unsigned short RADI_C14 = 1;
		unsigned short RADIWORD1 = (RADI_C2 << 15) | (RADI_C3 << 14) | (RADI_C4 << 13) | (RADI_C5 << 12) | (RADI_C6 << 11) | (RADI_C7 << 10) |
			(RADI_C8 << 9) | (RADI_C9 << 8) | (RADI_C10 << 7) | (RADI_C11 << 6) | (RADI_C12 << 5) | (RADI_C13 << 4) | (RADI_C14 << 3);

		// Left ADI Test Word (LADIWORD2)
		unsigned short LADIWORD2 = 0b0111111111111000;

		// Right ADI Test Word (RADIWORD2)
		unsigned short RADIWORD2 = 0b0111111111111000;

		// Left ADI Roll Sine(LADIRS) 80 ms
		LADIRS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLSINE1, 1.0 )));

		// Right ADI Roll Sine(RADIRS) 80 ms
		RADIRS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLSINE2, 1.0 )));

		// Left ADI Roll Cosine(LADIRC) 80 ms
		LADIRC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLCOS1, 1.0 )));

		// Right ADI Roll Cosine(RADIRC) 80 ms
		RADIRC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, ROLLCOS2, 1.0 )));

		// Left ADI Pitch Sine(LADIPS) 80 ms
		LADIPS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHSINE1, 1.0 )));

		// Right ADI Pitch Sine(RADIPS) 80 ms
		RADIPS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHSINE2, 1.0 )));

		// Left ADI Pitch Cosine(LADIPC) 80 ms
		LADIPC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHCOS1, 1.0 )));

		// Right ADI Pitch Cosine(RADIPC) 80 ms
		RADIPC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, PTCHCOS2, 1.0 )));

		// Left ADI Yaw Sine(LADIYS) 80 ms
		LADIYS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWSINE1, 1.0 )));

		// Right ADI Yaw Sine(RADIYS) 80 ms
		RADIYS = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWSINE2, 1.0 )));

		// Left ADI Yaw Cosine(LADIYC) 80 ms
		LADIYC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWCOS1, 1.0 )));

		// Right ADI Yaw Cosine(RADIYC) 80 ms
		RADIYC = 8 * static_cast<unsigned short>(4095 * (range( -1.0, YAWCOS2, 1.0 )));

		// Attitude Rate Data
		if ((MM_CODE_301 == 1) || (MM_CODE_302 == 1) || (MM_CODE_303 == 1))
		{
			MEDS_LH_TGOSC_FLAG = 0;
			MEDS_RH_TGOSC_FLAG = 0;

			// Left ADI Roll Rate (LADIRR) 160 ms
			if (LADIRSW == 1)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * P_ORB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(10);
			}
			else if (LADIRSW == 0)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * P_ORB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(5);
			}
			else //if (LADIRSW == -1)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * P_ORB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(1);
			}

			// Right ADI Roll Rate (RADIRR) 160 ms
			if (RADIRSW == 1)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * P_ORB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(10);
			}
			else if (RADIRSW == 0)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * P_ORB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(5);
			}
			else //if (RADIRSW == -1)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * P_ORB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(1);
			}

			// Left ADI Pitch Rate (LADIPR) 160 ms
			if (LADIRSW == 1)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(10);
			}
			else if (LADIRSW == 0)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(5);
			}
			else //if (LADIRSW == -1)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(1);
			}

			// Right ADI Pitch Rate (RADIPR) 160 ms
			if (RADIRSW == 1)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(10);
			}
			else if (RADIRSW == 0)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(5);
			}
			else //if (RADIRSW == -1)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(1);
			}

			// Left ADI Yaw Rate (LADIYR) 160 ms
			if (LADIRSW == 1)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * R_ORB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(10);
			}
			else if (LADIRSW == 0)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * R_ORB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(5);
			}
			else //if (LADIRSW == -1)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * R_ORB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(1);
			}

			// Right ADI Yaw Rate (RADIYR) 160 ms
			if (RADIRSW == 1)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 10.0) * R_ORB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(10);
			}
			else if (RADIRSW == 0)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 5.0) * R_ORB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(5);
			}
			else //if (RADIRSW == -1)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / 1.0) * R_ORB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(1);
			}
		}
		else if (((ReadCOMPOOL_IS( SCP_DISPLAY_OPTION ) == 0) && ((MM_CODE_305 == 1) || (MM_CODE_603 == 1))) || ((MM_CODE_304 == 1) || (MM_CODE_602 == 1)))
		{
			MEDS_LH_TGOSC_FLAG = 0;
			MEDS_RH_TGOSC_FLAG = 0;

			// Left ADI Roll Rate (LADIRR) 160 ms
			if (LADIRSW == 1)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE )) * P_STAB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE ));
			}
			else if (LADIRSW == 0)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * P_STAB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
			}
			else //if (LADIRSW == -1)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE )) * P_STAB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE ));
			}

			// Right ADI Roll Rate (RADIRR) 160 ms
			if (RADIRSW == 1)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE )) * P_STAB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE ));
			}
			else if (RADIRSW == 0)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * P_STAB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
			}
			else //if (RADIRSW == -1)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE )) * P_STAB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE ));
			}

			// Left ADI Pitch Rate (LADIPR) 160 ms
			if (LADIRSW == 1)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE )) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE ));
			}
			else if (LADIRSW == 0)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
			}
			else //if (LADIRSW == -1)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE )) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE ));
			}

			// Right ADI Pitch Rate (RADIPR) 160 ms
			if (RADIRSW == 1)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE )) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE ));
			}
			else if (RADIRSW == 0)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
			}
			else //if (RADIRSW == -1)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE )) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE ));
			}

			// Left ADI Yaw Rate (LADIYR) 160 ms
			if (LADIRSW == 1)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE )) * R_STAB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE ));
			}
			else if (LADIRSW == 0)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * R_STAB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
			}
			else //if (LADIRSW == -1)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE )) * R_STAB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE ));
			}

			// Right ADI Yaw Rate (RADIYR) 160 ms
			if (RADIRSW == 1)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE )) * R_STAB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE ));
			}
			else if (RADIRSW == 0)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * R_STAB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
			}
			else //if (RADIRSW == -1)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE )) * R_STAB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE ));
			}
		}
		else if ((ReadCOMPOOL_IS( SCP_DISPLAY_OPTION ) == 1) && ((MM_CODE_305 == 1) || ((MM_CODE_603 == 1) && (IPHASE < 4))))
		{
			if (firstpass305603r)
			{
				firstpass305603r = false;

				DO_ADI_TGO_DISPLAY = true;
				DISPLAY_RATE_MED = false;
				STOW_MED = false;
				HAC_TIME_SNAPPED = false;
				ALT_TIME_SNAPPED = false;
			}

			MEDS_LH_TGOSC_FLAG = 0;
			MEDS_RH_TGOSC_FLAG = 0;

			// Determine Status of ADI Rate Pointers
			if ((IPHASE == 2) && (DO_ADI_TGO_DISPLAY == true))
			{
				if (HAC_TIME_SNAPPED == false)
				{
					HAC_TIME = T_STATE;
					HAC_TIME_SNAPPED = true;
				}
				if (T_STATE > (HAC_TIME + ReadCOMPOOL_IS( SCP_ROLL_STOW_DELAY_TIME )))
				{
					DO_ADI_TGO_DISPLAY = false;
				}
			}

			if (ALT_WHEELS < ReadCOMPOOL_SS( SCP_H_BLANK ))
			{
				if (ALT_TIME_SNAPPED == false)
				{
					ALT_TIME = T_STATE;
					ALT_TIME_SNAPPED = true;
				}

				if (T_STATE < (ALT_TIME + ReadCOMPOOL_IS( SCP_UNSTOW_DELAY_TIME )))
				{
					STOW_MED = true;
				}
				else
				{
					DISPLAY_RATE_MED = true;
					STOW_MED = false;
				}

				if (WOWLON == 1)
				{
					DISPLAY_RATE_MED = true;
					STOW_MED = false;
				}
			}

			// Left MM 305/603 ADI Roll Rate (LADIRR) 160 ms
			if (LADIRSW == 1)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 )) * P_STAB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 ));
			}
			else if (LADIRSW == 0)
			{
				if (DO_ADI_TGO_DISPLAY == true)
				{
					double TGO_HAC = (RTAN - (RTURN * sqrt( ReadCOMPOOL_SS( SCP_P2TRNC1 ) * (ReadCOMPOOL_SS( SCP_P2TRNC1 ) - 1.0) ))) / V_GROUNDSPEED;
					LADIRR = 8 * static_cast<unsigned short>(range( -4096, -4095 * ((2.0 * (TGO_HAC / ReadCOMPOOL_SS( SCP_TGOSC ))) - 1.0) * YSGNP, 4095 ));// HACK moved - sign from 8 to inside expression
					MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_TGOSC ));
					MEDS_LH_TGOSC_FLAG = 1;
				}
				else
				{
					if (DISPLAY_RATE_MED == true)
					{
						LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * P_STAB, 4095 ));
						MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
					}
					else
					{
						LADIRR = 0;
						MEDS_LADIRR_SCALE = 0;// off
					}
				}
			}
			else //if (LADIRSW == -1)
			{
				LADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE_305603 )) * P_STAB, 4095 ));
				MEDS_LADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE_305603 ));
			}

			// Right MM 305/603 ADI Roll Rate (RADIRR) 160 ms
			if (RADIRSW == 1)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 )) * P_STAB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 ));
			}
			else if (RADIRSW == 0)
			{
				if (DO_ADI_TGO_DISPLAY == true)
				{
					double TGO_HAC = (RTAN - (RTURN * sqrt( ReadCOMPOOL_SS( SCP_P2TRNC1 ) * (ReadCOMPOOL_SS( SCP_P2TRNC1 ) - 1.0) ))) / V_GROUNDSPEED;
					RADIRR = 8 * static_cast<unsigned short>(range( -4096, -4095 * ((2.0 * (TGO_HAC / ReadCOMPOOL_SS( SCP_TGOSC ))) - 1.0) * YSGNP, 4095 ));// HACK moved - sign from 8 to inside expression
					MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_TGOSC ));
					MEDS_RH_TGOSC_FLAG = 1;
				}
				else
				{
					if (DISPLAY_RATE_MED == true)
					{
						RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * P_STAB, 4095 ));
						MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
					}
					else
					{
						RADIRR = 0;
						MEDS_RADIRR_SCALE = 0;// off
					}
				}
			}
			else //if (RADIRSW == -1)
			{
				RADIRR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE_305603 )) * P_STAB, 4095 ));
				MEDS_RADIRR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE_305603 ));
			}

			// Left MM 305/603 ADI Pitch Rate (LADIPR) 160 ms
			if (LADIRSW == 1)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 )) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 ));
			}
			else if (LADIRSW == 0)
			{
				if ((DISPLAY_RATE_MED == false) && (STOW_MED == false))
				{
					float HERR_GUID;
					if (TG_END == 0)
					{
						HERR_GUID = HERROR;
					}
					else
					{
						HERR_GUID = H_ERROR;
					}

					float HERROR_MAX;
					if ((IPHASE == 3) || (TG_END == 1))
					{
						HERROR_MAX = ReadCOMPOOL_SS( SCP_HERRSC2 );
					}
					else
					{
						HERROR_MAX = ReadCOMPOOL_SS( SCP_HERRSC1 );
					}

					LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / HERROR_MAX) * HERR_GUID, 4095 ));
					MEDS_LADIPR_SCALE = static_cast<unsigned short>(HERROR_MAX);
				}
				else
				{
					if (STOW_MED == true)
					{
						LADIPR = 0;
						MEDS_LADIPR_SCALE = 0;// stow
					}
					else// if (DISPLAY_RATE_MED == true)
					{
						LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * Q_ORB, 4095 ));
						MEDS_LADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
					}
				}
			}
			else //if (LADIRSW == -1)
			{
				LADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE_305603 )) * Q_ORB, 4095 ));
				MEDS_LADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE_305603 ));
			}

			// Right MM 305/603 ADI Pitch Rate (RADIPR) 160 ms
			if (RADIRSW == 1)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 )) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 ));
			}
			else if (RADIRSW == 0)
			{
				if ((DISPLAY_RATE_MED == false) && (STOW_MED == false))
				{
					float HERR_GUID;
					if (TG_END == 0)
					{
						HERR_GUID = HERROR;
					}
					else
					{
						HERR_GUID = H_ERROR;
					}

					float HERROR_MAX;
					if ((IPHASE == 3) || (TG_END == 1))
					{
						HERROR_MAX = ReadCOMPOOL_SS( SCP_HERRSC2 );
					}
					else
					{
						HERROR_MAX = ReadCOMPOOL_SS( SCP_HERRSC1 );
					}

					RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / HERROR_MAX) * HERR_GUID, 4095 ));
					MEDS_RADIPR_SCALE = static_cast<unsigned short>(HERROR_MAX);
				}
				else
				{
					if (STOW_MED == true)
					{
						RADIPR = 0;
						MEDS_RADIPR_SCALE = 0;// stow
					}
					else// if (DISPLAY_RATE_MED == true)
					{
						RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * Q_ORB, 4095 ));
						MEDS_RADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
					}
				}
			}
			else //if (RADIRSW == -1)
			{
				RADIPR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE_305603 )) * Q_ORB, 4095 ));
				MEDS_RADIPR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE_305603 ));
			}

			// Left MM305/603 ADI Yaw Rate (LADIYR) 160 ms
			if (LADIRSW == 1)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 )) * R_STAB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 ));
			}
			else if (LADIRSW == 0)
			{
				if ((DISPLAY_RATE_MED == false) && (STOW_MED == false))
				{
					float LATERR;
					float LATSC;
					if ((IPHASE == 0) || (IPHASE == 1))
					{
						LATERR = DPSAC;
						LATSC = ReadCOMPOOL_SS( SCP_DPSACSC );
					}
					else if (IPHASE == 2)
					{
						LATERR = RERRC * YSGNP;
						LATSC = ReadCOMPOOL_SS( SCP_RERRCSC );
					}
					else// if ((IPHASE == 3) || (TG_END == 1))
					{
						LATERR = -Y;
						LATSC = ReadCOMPOOL_SS( SCP_YSC );
					}

					LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / LATSC) * LATERR, 4095 ));
					MEDS_LADIYR_SCALE = static_cast<unsigned short>(LATSC);
				}
				else
				{
					if (STOW_MED == true)
					{
						LADIYR = 0;
						MEDS_LADIYR_SCALE = 0;// stow
					}
					else// if (DISPLAY_RATE_MED == true)
					{
						LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * R_STAB, 4095 ));
						MEDS_LADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
					}
				}
			}
			else //if (LADIRSW == -1)
			{
				LADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE_305603 )) * R_STAB, 4095 ));
				MEDS_LADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE_305603 ));
			}

			// Right MM305/603 ADI Yaw Rate (RADIYR) 160 ms
			if (RADIRSW == 1)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 )) * R_STAB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_HIGH_RATE_305603 ));
			}
			else if (RADIRSW == 0)
			{
				if ((DISPLAY_RATE_MED == false) && (STOW_MED == false))
				{
					float LATERR;
					float LATSC;
					if ((IPHASE == 0) || (IPHASE == 1))
					{
						LATERR = DPSAC;
						LATSC = ReadCOMPOOL_SS( SCP_DPSACSC );
					}
					else if (IPHASE == 2)
					{
						LATERR = RERRC * YSGNP;
						LATSC = ReadCOMPOOL_SS( SCP_RERRCSC );
					}
					else// if ((IPHASE == 3) || (TG_END == 1))
					{
						LATERR = -Y;
						LATSC = ReadCOMPOOL_SS( SCP_YSC );
					}

					RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / LATSC) * LATERR, 4095 ));
					MEDS_RADIYR_SCALE = static_cast<unsigned short>(LATSC);
				}
				else
				{
					if (STOW_MED == true)
					{
						RADIYR = 0;
						MEDS_RADIYR_SCALE = 0;// stow
					}
					else// if (DISPLAY_RATE_MED == true)
					{
						RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_MED_RATE )) * R_STAB, 4095 ));
						MEDS_RADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_MED_RATE ));
					}
				}
			}
			else //if (RADIRSW == -1)
			{
				RADIYR = 8 * static_cast<unsigned short>(range( -4096, (4095 / ReadCOMPOOL_SS( SCP_LOW_RATE_305603 )) * R_STAB, 4095 ));
				MEDS_RADIYR_SCALE = static_cast<unsigned short>(ReadCOMPOOL_SS( SCP_LOW_RATE_305603 ));
			}
		}

		// Attitude Error Data
		// Left/Right ADI Roll/Pitch Error Integrator Monitoring - 160 ms
		if ((MM_CODE_304 == 1) || (MM_CODE_602 == 1))
		{
			if (firstpass304602 == true)
			{
				firstpass304602 = false;

				IPHASE_PREV = IPHASE;
				RW_ID_PREV = RW_ID;
				YSGN_PREV = YSGNP;
				NEP_FB_PREV = NEP_FB;
				CSSRY_IND_PREV = CSSRY_IND;
				CSSP_IND_PREV = CSSP_IND;
				ZERO_PR_INT = false;
				ZERO_R_INT = false;
				ZERO_P_INT = false;
				ZERO_5_INT = false;
			}
		}

		if ((firstpass305603e == true) || (IPHASE != IPHASE_PREV) || (RW_ID != RW_ID_PREV) || (YSGNP != YSGN_PREV) || (NEP_FB != NEP_FB_PREV))
		{
			firstpass305603e = false;

			ZERO_PR_INT = true;
			ZERO_PR_INT_COUNT = ReadCOMPOOL_IS( SCP_TIDELAY );
		}

		if ((CSSRY_IND == 1) && (CSSRY_IND_PREV == 0))
		{
			ZERO_R_INT = true;
			ZERO_R_INT_COUNT = ReadCOMPOOL_IS( SCP_TIDELAYC );
		}

		if ((CSSP_IND == 1) && (CSSP_IND_PREV == 0))
		{
			ZERO_P_INT = true;
			ZERO_P_INT_COUNT = ReadCOMPOOL_IS( SCP_TIDELAYC );
		}

		if ((IPHASE == 5) && (IPHASE != IPHASE_PREV))
		{
			ZERO_5_INT = true;
			ZERO_5_INT_COUNT = ReadCOMPOOL_IS( SCP_TIDELAY5 );
		}

		if (ZERO_PR_INT_COUNT != 0)
		{
			ZERO_PR_INT_COUNT--;
			if (ZERO_PR_INT_COUNT == 0) ZERO_PR_INT = false;
		}

		if (ZERO_R_INT_COUNT != 0)
		{
			ZERO_R_INT_COUNT--;
			if (ZERO_R_INT_COUNT == 0) ZERO_R_INT = false;
		}

		if (ZERO_P_INT_COUNT != 0)
		{
			ZERO_P_INT_COUNT--;
			if (ZERO_P_INT_COUNT == 0) ZERO_P_INT = false;
		}

		if (ZERO_5_INT_COUNT != 0)
		{
			ZERO_5_INT_COUNT--;
			if (ZERO_5_INT_COUNT == 0) ZERO_5_INT = false;
		}

		IPHASE_PREV = IPHASE;
		RW_ID_PREV = RW_ID;
		YSGN_PREV = YSGNP;
		NEP_FB_PREV = NEP_FB;
		CSSRY_IND_PREV = CSSRY_IND;
		CSSP_IND_PREV = CSSP_IND;


		double RECC1_L;
		double RECC1_R;
		double RECC2_L;
		double RECC2_R;
		double RECC3_L;
		double RECC3_R;
		double PSFE_L;
		double PSFE_R;
		double PSFC_L;
		double PSFC_R;
		double PSFD_L;
		double PSFD_R;
		if (LADIESW == 1)
		{
			RECC1_L = 4095 / 10.0;
			RECC2_L = 4095 / 25.0;
			RECC3_L = 4095 / 20.0;
			PSFE_L = 4095 / 5.0;
			PSFC_L = 4095 / 1.25;
			PSFD_L = 4095 / 10.0;
		}
		else if (LADIESW == 0)
		{
			RECC1_L = 4095 / 5.0;
			RECC2_L = 4095 / 25.0;
			RECC3_L = 4095 / 5.0;
			PSFE_L = 4095 / 2.0;
			PSFC_L = 4095 / 1.25;
			PSFD_L = 4095 / 5.0;
		}
		else //if (LADIESW == -1)
		{
			RECC1_L = 4095;
			RECC2_L = 4095 / 10.0;
			RECC3_L = 4095;
			PSFE_L = 4095;
			PSFC_L = 4095 / 0.5;
			PSFD_L = 4095;
		}
		if (RADIESW == 1)
		{
			RECC1_R = 4095 / 10.0;
			RECC2_R = 4095 / 25.0;
			RECC3_R = 4095 / 20.0;
			PSFE_R = 4095 / 5.0;
			PSFC_R = 4095 / 1.25;
			PSFD_R = 4095 / 10.0;
		}
		else if (RADIESW == 0)
		{
			RECC1_R = 4095 / 5.0;
			RECC2_R = 4095 / 25.0;
			RECC3_R = 4095 / 5.0;
			PSFE_R = 4095 / 2.0;
			PSFC_R = 4095 / 1.25;
			PSFD_R = 4095 / 5.0;
		}
		else //if (RADIESW == -1)
		{
			RECC1_R = 4095;
			RECC2_R = 4095 / 10.0;
			RECC3_R = 4095;
			PSFE_R = 4095;
			PSFC_R = 4095 / 0.5;
			PSFD_R = 4095;
		}

		// Left/Right ADI Roll Error (LADIRE/RADIRE) 160 ms
		if ((MM_CODE_301 == 1) || (MM_CODE_302 == 1) || (MM_CODE_303 == 1))
		{
			LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC1_L * BODY_ERR_ANG[0], 4095 ));
			RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC1_R * BODY_ERR_ANG[0], 4095 ));
		}
		else if (MM_CODE_304 == 1)
		{
			LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_L * (PHI - ROLLC1), 4095 ));
			RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_R * (PHI - ROLLC1), 4095 ));
			HUD_ROLLERR = 0;
		}
		else if ((MM_CODE_602 == 1) || (IPHASE == 0))
		{
			LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_L * (PHI - PHIC_AT), 4095 ));
			RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_R * (PHI - PHIC_AT), 4095 ));
			HUD_ROLLERR = static_cast<unsigned short>((100 * (PHI - PHIC_AT)) * GROLL);
		}
		else if (((MM_CODE_305 == 1) || (MM_CODE_603 == 1)) && (TG_END == 0) /*&& (IPHASE != 0)*/)
		{
			if (CSSRY_IND == 0)
			{
				LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_L * (PHI - PHIC_AT), 4095 ));
				RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_R * (PHI - PHIC_AT), 4095 ));
				HUD_ROLLERR = static_cast<unsigned short>((100 * (PHI - PHIC_AT)) * GROLL);
			}
			else
			{
				float RERR_SLOPEP;
				float RERR_SLOPEN;
				float RERR_INTT;
				float RERR_TOTAL;
				float ROLL_IERR = PHI - PHIC_AT;
				if ((ZERO_PR_INT == true) || (ZERO_R_INT == true))
				{
					ROLL_IERR = 0.0;
				}

				if (ROLL_IERR >= ReadCOMPOOL_SS( SCP_RERR_DB ))
				{
					RERR_SLOPEP = (ROLL_IERR - ReadCOMPOOL_SS( SCP_RERR_DB )) * ReadCOMPOOL_SS( SCP_GR_INTUP );
				}
				else
				{
					RERR_SLOPEP = (ROLL_IERR - ReadCOMPOOL_SS( SCP_RERR_DB )) * ReadCOMPOOL_SS( SCP_GR_INTDN );
				}
				RERR_INTP = RERR_INTP + 0.16f * RERR_SLOPEP;
				RERR_INTP = static_cast<float>(midval( 0.0, RERR_INTP, ReadCOMPOOL_SS( SCP_RINT_LIM ) ));

				if (ROLL_IERR <= -ReadCOMPOOL_SS( SCP_RERR_DB ))
				{
					RERR_SLOPEN = (ROLL_IERR + ReadCOMPOOL_SS( SCP_RERR_DB )) * ReadCOMPOOL_SS( SCP_GR_INTUP );
				}
				else
				{
					RERR_SLOPEN = (ROLL_IERR + ReadCOMPOOL_SS( SCP_RERR_DB )) * ReadCOMPOOL_SS( SCP_GR_INTDN );
				}
				RERR_INTN = RERR_INTN + 0.16f * RERR_SLOPEN;
				RERR_INTN = static_cast<float>(midval( 0.0, RERR_INTN, -ReadCOMPOOL_SS( SCP_RINT_LIM ) ));

				RERR_INTT = RERR_INTP + RERR_INTN;

				RERR_TOTAL = (PHI - PHIC_AT) + RERR_INTT;
				LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_L * RERR_TOTAL, 4095 ));
				RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC2_R * RERR_TOTAL, 4095 ));
				HUD_ROLLERR = static_cast<unsigned short>(RERR_TOTAL * 100 * GROLL);
			}
		}
		else //if (TG_END == 1)
		{
			if (WOWLON != 1)
			{
				RECC3_L = RECC2_L;
				RECC3_R = RECC2_R;
			}
			LADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC3_L * (PHI - PHIC_AL), 4095 ));
			RADIRE = 8 * static_cast<unsigned short>(range( -4096, RECC3_R * (PHI - PHIC_AL), 4095 ));
			HUD_ROLLERR = static_cast<unsigned short>((100 * (PHI - PHIC_AL)) * GROLL);
		}

		// Left/Right ADI Pitch Error (LADIPE/RADIPE) 160 ms
		if ((MM_CODE_301 == 1) || (MM_CODE_302 == 1) || (MM_CODE_303 == 1))
		{
			LADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC1_L * BODY_ERR_ANG[1], 4095 ));
			RADIPE = 8 * static_cast<unsigned short>(range( -4096, RECC1_R * BODY_ERR_ANG[1], 4095 ));
			MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / RECC1_L) * 4);// LSB 0.25º
			MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / RECC1_R) * 4);// LSB 0.25º
		}
		else if ((MM_CODE_304 == 1) || (((MM_CODE_602 == 1) || (MM_CODE_603 == 1)) && ((IPHASE == 6) || (IPHASE == 4))))
		{
			LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFE_L * ALFERR_FDC, 4095 ));
			RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFE_R * ALFERR_FDC, 4095 ));
			HUD_PITCHERR = 0;
			MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFE_L) * 4);// LSB 0.25º
			MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFE_R) * 4);// LSB 0.25º
		}
		else if (((MM_CODE_602 == 1) || (MM_CODE_603 == 1)) && (IPHASE == 5))
		{
			if (CSSP_IND == 0)
			{
				LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_L * NZERRFD, 4095 ));
				RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_R * NZERRFD, 4095 ));
				HUD_PITCHERR = static_cast<unsigned short>((100 * NZERRFD) * GPITCH);
				MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_L) * 4);// LSB 0.25º
				MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_R) * 4);// LSB 0.25º
			}
			else
			{
				float NZ_SLOPEP;
				float NZ_SLOPEN;
				float NZ_INTT;
				float NZERR_TOTAL;
				float NZ_IERR = NZERRFD;
				if ((ZERO_5_INT == true) || (ZERO_P_INT == true))
				{
					NZ_IERR = 0.0f;
				}

				if (NZ_IERR >= ReadCOMPOOL_SS( SCP_PERR_DB5 ))
				{
					NZ_SLOPEP = (NZ_IERR - ReadCOMPOOL_SS( SCP_PERR_DB5 )) * ReadCOMPOOL_SS( SCP_GP_INTUP5 );
				}
				else
				{
					NZ_SLOPEP = (NZ_IERR - ReadCOMPOOL_SS( SCP_PERR_DB5 )) * ReadCOMPOOL_SS( SCP_GP_INTDN5 );
				}
				NZ_INTP = NZ_INTP + 0.16f * NZ_SLOPEP;
				NZ_INTP = static_cast<float>(midval( 0.0, NZ_INTP, ReadCOMPOOL_SS( SCP_PINT_LIM5 ) ));

				if (NZ_IERR <= -ReadCOMPOOL_SS( SCP_PERR_DB5 ))
				{
					NZ_SLOPEN = (NZ_IERR + ReadCOMPOOL_SS( SCP_PERR_DB5 )) * ReadCOMPOOL_SS( SCP_GP_INTUP5 );
				}
				else
				{
					NZ_SLOPEN = (NZ_IERR + ReadCOMPOOL_SS( SCP_PERR_DB5 )) * ReadCOMPOOL_SS( SCP_GP_INTDN5 );
				}
				NZ_INTN = NZ_INTN + 0.16f * NZ_SLOPEN;
				NZ_INTN = static_cast<float>(midval( 0.0, NZ_INTN, -ReadCOMPOOL_SS( SCP_PINT_LIM5 ) ));

				NZ_INTT = NZ_INTP + NZ_INTN;

				NZERR_TOTAL = NZERRFD + NZ_INTT;
				LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_L * NZERR_TOTAL, 4095 ));
				RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_R * NZERR_TOTAL, 4095 ));
				HUD_PITCHERR = static_cast<unsigned short>(NZERR_TOTAL * 100 * GPITCH);
				MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_L) * 4);// LSB 0.25º
				MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_R) * 4);// LSB 0.25º
			}
		}
		else if (((MM_CODE_305 == 1) || (MM_CODE_603 == 1)) && (TG_END == 0) && ((IPHASE == 1) || (IPHASE == 2) || (IPHASE == 3)))
		{
			if (CSSP_IND == 0)
			{
				LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_L * NZERRFD, 4095 ));
				RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_R * NZERRFD, 4095 ));
				HUD_PITCHERR = static_cast<unsigned short>((100 * NZERRFD) * GPITCH);
				MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_L) * 4);// LSB 0.25º
				MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_R) * 4);// LSB 0.25º
			}
			else
			{
				float NZ_SLOPEP;
				float NZ_SLOPEN;
				float NZ_INTT;
				float NZERR_TOTAL;
				float NZ_IERR = NZERRFD;

				if ((ZERO_PR_INT == true) || (ZERO_P_INT == true))
				{
					NZ_IERR = 0.0f;
				}

				if (NZ_IERR >= ReadCOMPOOL_SS( SCP_PERR_DB ))
				{
					NZ_SLOPEP = (NZ_IERR - ReadCOMPOOL_SS( SCP_PERR_DB )) * ReadCOMPOOL_SS( SCP_GP_INTUP );
				}
				else
				{
					NZ_SLOPEP = (NZ_IERR - ReadCOMPOOL_SS( SCP_PERR_DB )) * ReadCOMPOOL_SS( SCP_GP_INTDN );
				}
				NZ_INTP = NZ_INTP + 0.16f * NZ_SLOPEP;
				NZ_INTP = static_cast<float>(midval( 0.0, NZ_INTP, ReadCOMPOOL_SS( SCP_PINT_LIM ) ));

				if (NZ_IERR <= -ReadCOMPOOL_SS( SCP_PERR_DB ))
				{
					NZ_SLOPEN = (NZ_IERR + ReadCOMPOOL_SS( SCP_PERR_DB )) * ReadCOMPOOL_SS( SCP_GP_INTUP );
				}
				else
				{
					NZ_SLOPEN = (NZ_IERR + ReadCOMPOOL_SS( SCP_PERR_DB )) * ReadCOMPOOL_SS( SCP_GP_INTDN );
				}
				NZ_INTN = NZ_INTN + 0.16f * NZ_SLOPEN;
				NZ_INTN = static_cast<float>(midval( 0.0, NZ_INTN, -ReadCOMPOOL_SS( SCP_PINT_LIM ) ));

				NZ_INTT = NZ_INTP + NZ_INTN;

				NZERR_TOTAL = NZERRFD + NZ_INTT;

				LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_L * NZERR_TOTAL, 4095 ));
				RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_R * NZERR_TOTAL, 4095 ));
				HUD_PITCHERR = static_cast<unsigned short>(NZERR_TOTAL * 100 * GPITCH);
				MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_L) * 4);// LSB 0.25º
				MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_R) * 4);// LSB 0.25º
			}
		}
		else if (((TG_END == 1) && (WOWLON == 0)) || (IPHASE == 0))
		{
			LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_L * NZERRFD, 4095 ));
			RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFC_R * NZERRFD, 4095 ));
			HUD_PITCHERR = static_cast<unsigned short>((100 * NZERRFD) * GPITCH);
			MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_L) * 4);// LSB 0.25º
			MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFC_R) * 4);// LSB 0.25º
		}
		else //if (WOWLON == 1)
		{
			LADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFD_L * QFFDC, 4095 ));
			RADIPE = 8 * static_cast<unsigned short>(range( -4096, PSFD_R * QFFDC, 4095 ));
			MEDS_LADIPE_SCALE = static_cast<unsigned short>((4095 / PSFD_L) * 4);// LSB 0.25º
			MEDS_RADIPE_SCALE = static_cast<unsigned short>((4095 / PSFD_R) * 4);// LSB 0.25º
		}

		// Left/Right ADI Yaw Error (LADIYE/RADIYE) 160 ms
		if ((MM_CODE_301 == 1) || (MM_CODE_302 == 1) || (MM_CODE_303 == 1))
		{
			LADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC1_L * BODY_ERR_ANG[2], 4095 ));
			RADIYE = 8 * static_cast<unsigned short>(range( -4096, RECC1_R * BODY_ERR_ANG[2], 4095 ));
		}
		else
		{
			LADIYE = 8 * static_cast<unsigned short>(range( -4096, -1638 * BETA_FDC, 4095 ));
			RADIYE = 8 * static_cast<unsigned short>(range( -4096, -1638 * BETA_FDC, 4095 ));
		}

		// Left/Right HUD HEADING
		if ((MM_CODE_602 == 1) || (MM_CODE_603 == 1) || (MM_CODE_304 == 1) || (MM_CODE_305 == 1))
		{
			HUD_HEADING = static_cast<unsigned short>(PSI_HSIMV * DEG * 50);
		}


		// output
		// Word 1 ADI Contl Word
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 1, LADIWORD1, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 1, RADIWORD1, 14 );
		// Word 2 Test Word
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 2, LADIWORD2, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 2, RADIWORD2, 14 );
		// Word 3 Roll Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 3, LADIRS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 3, RADIRS, 14 );
		// Word 4 Roll Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 4, LADIRC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 4, RADIRC, 14 );
		// Word 5 Pitch Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 5, LADIPS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 5, RADIPS, 14 );
		// Word 6 Pitch Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 6, LADIPC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 6, RADIPC, 14 );
		// Word 7 Yaw Sine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 7, LADIYS, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 7, RADIYS, 14 );
		// Word 8 Yaw Cosine
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 8, LADIYC, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 8, RADIYC, 14 );
		// Word 9 Roll Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 9, LADIRR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 9, RADIRR, 14 );
		// Word 10 Pitch Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 10, LADIPR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 10, RADIPR, 14 );
		// Word 11 Yaw Rate
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 11, LADIYR, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 11, RADIYR, 14 );
		// Word 12 Roll Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 12, LADIRE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 12, RADIRE, 14 );
		// Word 13 Pitch Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 13, LADIPE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 13, RADIPE, 14 );
		// Word 14 Yaw Error
		WriteCOMPOOL_AIS( SCP_DDU1_ADI, 14, LADIYE, 14 );
		WriteCOMPOOL_AIS( SCP_DDU2_ADI, 14, RADIYE, 14 );

		// HUD
		WriteCOMPOOL_IS( SCP_HUD_ROLLERR, HUD_ROLLERR );
		WriteCOMPOOL_IS( SCP_HUD_PITCHERR, HUD_PITCHERR );
		WriteCOMPOOL_IS( SCP_HUD_HEADING, HUD_HEADING );

		// MEDS
		WriteCOMPOOL_IS( SCP_MEDS_LH_TGOSC_FLAG, MEDS_LH_TGOSC_FLAG );
		WriteCOMPOOL_IS( SCP_MEDS_RH_TGOSC_FLAG, MEDS_RH_TGOSC_FLAG );
		WriteCOMPOOL_IS( SCP_MEDS_LADIRR_SCALE, MEDS_LADIRR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIRR_SCALE, MEDS_RADIRR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_LADIPR_SCALE, MEDS_LADIPR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIPR_SCALE, MEDS_RADIPR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_LADIYR_SCALE, MEDS_LADIYR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIYR_SCALE, MEDS_RADIYR_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_LADIPE_SCALE, MEDS_LADIPE_SCALE );
		WriteCOMPOOL_IS( SCP_MEDS_RADIPE_SCALE, MEDS_RADIPE_SCALE );
		return;
	}

	bool EL_ADI_PROC::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short ustmp = 0;

		if (!_strnicmp( keyword, "DO_ADI_TGO_DISPLAY", 19 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			DO_ADI_TGO_DISPLAY = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "DISPLAY_RATE_MED", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			DISPLAY_RATE_MED = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "STOW_MED", 9 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			STOW_MED = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "HAC_TIME_SNAPPED", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			HAC_TIME_SNAPPED = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "ALT_TIME_SNAPPED", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			ALT_TIME_SNAPPED = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "HAC_TIME", 9 ))
		{
			sscanf_s( value, "%f", &HAC_TIME );
		}
		else if (!_strnicmp( keyword, "ALT_TIME", 9 ))
		{
			sscanf_s( value, "%f", &ALT_TIME );
		}
		else if (!_strnicmp( keyword, "IPHASE_PREV", 12 ))
		{
			sscanf_s( value, "%hu", &IPHASE_PREV );
		}
		else if (!_strnicmp( keyword, "RW_ID_PREV", 11 ))
		{
			sscanf_s( value, "%hu", &RW_ID_PREV );
		}
		else if (!_strnicmp( keyword, "YSGN_PREV", 10 ))
		{
			sscanf_s( value, "%f", &YSGN_PREV );
		}
		else if (!_strnicmp( keyword, "NEP_FB_PREV", 12 ))
		{
			sscanf_s( value, "%hu", &NEP_FB_PREV );
		}
		else if (!_strnicmp( keyword, "CSSRY_IND_PREV", 15 ))
		{
			sscanf_s( value, "%hu", &CSSRY_IND_PREV );
		}
		else if (!_strnicmp( keyword, "CSSP_IND_PREV", 14 ))
		{
			sscanf_s( value, "%hu", &CSSP_IND_PREV );
		}
		else if (!_strnicmp( keyword, "ZERO_PR_INT", 12 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			ZERO_PR_INT = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "ZERO_R_INT", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			ZERO_R_INT = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "ZERO_P_INT", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			ZERO_P_INT = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "ZERO_5_INT", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			ZERO_5_INT = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "ZERO_PR_INT_COUNT", 18 ))
		{
			sscanf_s( value, "%hu", &ZERO_PR_INT_COUNT );
		}
		else if (!_strnicmp( keyword, "ZERO_R_INT_COUNT", 17 ))
		{
			sscanf_s( value, "%hu", &ZERO_R_INT_COUNT );
		}
		else if (!_strnicmp( keyword, "ZERO_P_INT_COUNT", 17 ))
		{
			sscanf_s( value, "%hu", &ZERO_P_INT_COUNT );
		}
		else if (!_strnicmp( keyword, "ZERO_5_INT_COUNT", 17 ))
		{
			sscanf_s( value, "%hu", &ZERO_5_INT_COUNT );
		}
		else if (!_strnicmp( keyword, "RERR_INTP", 10 ))
		{
			sscanf_s( value, "%f", &RERR_INTP );
		}
		else if (!_strnicmp( keyword, "RERR_INTN", 10 ))
		{
			sscanf_s( value, "%f", &RERR_INTN );
		}
		else if (!_strnicmp( keyword, "NZ_INTP", 8 ))
		{
			sscanf_s( value, "%f", &NZ_INTP );
		}
		else if (!_strnicmp( keyword, "NZ_INTN", 8 ))
		{
			sscanf_s( value, "%f", &NZ_INTN );
		}
		else if (!_strnicmp( keyword, "firstpass304602", 16 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			firstpass304602 = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "firstpass305603r", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			firstpass305603r = (ustmp == 1);
		}
		else if (!_strnicmp( keyword, "firstpass305603e", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			firstpass305603e = (ustmp == 1);
		}
		else return false;

		return true;
	}

	void EL_ADI_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "DO_ADI_TGO_DISPLAY", DO_ADI_TGO_DISPLAY );
		oapiWriteScenario_int( scn, "DISPLAY_RATE_MED", DISPLAY_RATE_MED );
		oapiWriteScenario_int( scn, "STOW_MED", STOW_MED );
		oapiWriteScenario_int( scn, "HAC_TIME_SNAPPED", HAC_TIME_SNAPPED );
		oapiWriteScenario_int( scn, "ALT_TIME_SNAPPED", ALT_TIME_SNAPPED );
		oapiWriteScenario_float( scn, "HAC_TIME", HAC_TIME );
		oapiWriteScenario_float( scn, "ALT_TIME", ALT_TIME );
		oapiWriteScenario_int( scn, "IPHASE_PREV", IPHASE_PREV );
		oapiWriteScenario_int( scn, "RW_ID_PREV", RW_ID_PREV );
		oapiWriteScenario_float( scn, "YSGN_PREV", YSGN_PREV );
		oapiWriteScenario_int( scn, "NEP_FB_PREV", NEP_FB_PREV );
		oapiWriteScenario_int( scn, "CSSRY_IND_PREV", CSSRY_IND_PREV );
		oapiWriteScenario_int( scn, "CSSP_IND_PREV", CSSP_IND_PREV );
		oapiWriteScenario_int( scn, "ZERO_PR_INT", ZERO_PR_INT );
		oapiWriteScenario_int( scn, "ZERO_R_INT", ZERO_R_INT );
		oapiWriteScenario_int( scn, "ZERO_P_INT", ZERO_P_INT );
		oapiWriteScenario_int( scn, "ZERO_5_INT", ZERO_5_INT );
		oapiWriteScenario_int( scn, "ZERO_PR_INT_COUNT", ZERO_PR_INT_COUNT );
		oapiWriteScenario_int( scn, "ZERO_R_INT_COUNT", ZERO_R_INT_COUNT );
		oapiWriteScenario_int( scn, "ZERO_P_INT_COUNT", ZERO_P_INT_COUNT );
		oapiWriteScenario_int( scn, "ZERO_5_INT_COUNT", ZERO_5_INT_COUNT );
		oapiWriteScenario_float( scn, "RERR_INTP", RERR_INTP );
		oapiWriteScenario_float( scn, "RERR_INTN", RERR_INTN );
		oapiWriteScenario_float( scn, "NZ_INTP", NZ_INTP );
		oapiWriteScenario_float( scn, "NZ_INTN", NZ_INTN );
		oapiWriteScenario_int( scn, "firstpass304602", firstpass304602 );
		oapiWriteScenario_int( scn, "firstpass305603r", firstpass305603r );
		oapiWriteScenario_int( scn, "firstpass305603e", firstpass305603e );
		return;
	}
}
