#include "MEDSFCGNCXFER.h"
#include <MathSSV.h>


namespace dps
{
	MEDSFCGNCXFER::MEDSFCGNCXFER( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "MEDSFCGNCXFER" ),
		LAST_ROLL_SW(0), LAST_CDI_SCALE(0), LAST_D_AZ(0), LAST_D_INCL(0), LAST_MEDS_XTRK(0), LAST_XTRK_DEV(0), LAST_TGT_INCL(0)
	{
		return;
	}

	MEDSFCGNCXFER::~MEDSFCGNCXFER( void )
	{
		return;
	}

	void MEDSFCGNCXFER::Realize( void )
	{
		return;
	}

	void MEDSFCGNCXFER::OnPostStep( double simt, double simdt, double mjd )
	{
		// TODO gather = 6.25Hz, output = 25Hz

		// inputs
		unsigned short MEDS_FC_XFER_IS_PFS = 1;

		unsigned short GLIDE_RTLS_INHIBIT = 0;// TODO
		unsigned short RTLS_ABORT_DECLARED = 0;// TODO
		unsigned short S_AOA = 0;// TODO
		unsigned short S_ATO = 0;// TODO
		unsigned short TAL_ABORT_DECLARED = 0;// TODO
		unsigned short ROLL_SW = ReadCOMPOOL_IS( SCP_ROLL_SW );
		unsigned short S_RTLS_TURN = 0;// TODO
		unsigned short ENGINE_OUT_YAW_STEERING = 0;// TODO
		unsigned short IPHASE = ReadCOMPOOL_IS( SCP_IPHASE );
		unsigned short ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );
		unsigned short TG_END = ReadCOMPOOL_IS( SCP_TG_END );
		unsigned short WOWLON_IND = ReadCOMPOOL_IS( SCP_WOWLON );
		unsigned short HSI_MODE_LEFT = ReadCOMPOOL_IS( SCP_HSI_MODE_LEFT );
		unsigned short HSI_MODE_RIGHT = ReadCOMPOOL_IS( SCP_HSI_MODE_RIGHT );
		float THETA_MAX = 0.0f;// TODO
		float THETA_MIN = 0.0f;// TODO
		float THETA = ReadCOMPOOL_SS( SCP_THETA );
		unsigned short MEDS_LADIPR_SCALE = ReadCOMPOOL_IS( SCP_MEDS_LADIPR_SCALE );
		unsigned short MEDS_RADIPR_SCALE = ReadCOMPOOL_IS( SCP_MEDS_RADIPR_SCALE );
		unsigned short MEDS_LADIYR_SCALE = ReadCOMPOOL_IS( SCP_MEDS_LADIYR_SCALE );
		unsigned short MEDS_RADIYR_SCALE = ReadCOMPOOL_IS( SCP_MEDS_RADIYR_SCALE );
		unsigned short MEDS_LADIRR_SCALE = ReadCOMPOOL_IS( SCP_MEDS_LADIRR_SCALE );
		unsigned short MEDS_RADIRR_SCALE = ReadCOMPOOL_IS( SCP_MEDS_RADIRR_SCALE );
		unsigned short MEDS_LH_TGOSC_FLAG = ReadCOMPOOL_IS( SCP_MEDS_LH_TGOSC_FLAG );
		unsigned short MEDS_RH_TGOSC_FLAG = ReadCOMPOOL_IS( SCP_MEDS_RH_TGOSC_FLAG );
		float YSGNP = ReadCOMPOOL_SS( SCP_YSGNP );
		unsigned short MEDS_LADIPE_SCALE = ReadCOMPOOL_IS( SCP_MEDS_LADIPE_SCALE );
		unsigned short MEDS_RADIPE_SCALE = ReadCOMPOOL_IS( SCP_MEDS_RADIPE_SCALE );
		unsigned short ME_ZERO = 0;// TODO
		unsigned short S_MAN_THROT = ReadCOMPOOL_IS( SCP_S_MAN_THROT );
		unsigned short AUTO_MODE = 0;// TODO
		unsigned short AUTOP_IND_AUTOP_LAMP = ReadCOMPOOL_IS( SCP_AUTOP_IND );
		unsigned short AUTORY_IND_AUTORY_LAMP = ReadCOMPOOL_IS( SCP_AUTORY_IND );
		unsigned short AUTOSB_IND = ReadCOMPOOL_IS( SCP_AUTOSB_IND );
		unsigned short ATT_SEL_SW[2];
		ATT_SEL_SW[0] = ReadCOMPOOL_AIS( SCP_ATT_SEL_SW, 1, 3 );
		ATT_SEL_SW[1] = ReadCOMPOOL_AIS( SCP_ATT_SEL_SW, 2, 3 );
		unsigned short CDI_SCALE =  ReadCOMPOOL_IS( SCP_CDI_SCALE );
		float MEDS_D_AZ = ReadCOMPOOL_SS( SCP_MEDS_D_AZ );
		float MEDS_DELAZ = ReadCOMPOOL_SS( SCP_MEDS_DELAZ );
		float MEDS_DPSAC = ReadCOMPOOL_SS( SCP_MEDS_DPSAC );
		float ROLLC1 = ReadCOMPOOL_SS( SCP_ROLLCMD );
		unsigned short BANK_FLAG = 0;// TODO
		float DGRNZT = 0.0f;// TODO
		float MEDS_BETA = ReadCOMPOOL_SS( SCP_MEDS_BETA );
		float MEDS_D_INCL = ReadCOMPOOL_SS( SCP_MEDS_D_INCL );
		float XTRK = ReadCOMPOOL_SS( SCP_XTRK );
		float XTRK_CDI = ReadCOMPOOL_SS( SCP_XTRK_CDI );
		float INCL_TARGET = ReadCOMPOOL_SS( SCP_INCL_TARGET );
		unsigned short MEDS_AREA_NAV_FIRST_PASS = ReadCOMPOOL_IS( SCP_MEDS_AREA_NAV_FIRST_PASS );
		float MACH = ReadCOMPOOL_SS( SCP_M );
		unsigned short GC_AIF_FB = 0;// TODO
		unsigned short D_DILEMMA = 0;// TODO
		unsigned short NAV_INIT_FLAG = 0;// TODO
		unsigned short MEDS_BETAHVR_VALID = ReadCOMPOOL_IS( SCP_MEDS_BETAHVR_VALID );
		unsigned short MEDS_H_VR = ReadCOMPOOL_IS( SCP_MEDS_H_VR );


		// outputs
		unsigned short MEDS_CA_ABORT_DECLARED = 0;
		unsigned short MEDS_RTLS_ABORT_DECLARED = 0;
		unsigned short MEDS_AOA_ABORT_DECLARED = 0;
		unsigned short MEDS_ATO_ABORT_DECLARED = 0;
		unsigned short MEDS_TAL_ABORT_DECLARED = 0;
		unsigned short MEDS_ROLL_SW = 0;// HSI Heads-down Flag (1 = heads-down)
		unsigned short MEDS_PPA = 0;
		unsigned short MEDS_EO_YAW_STEERING_ON = 0;
		unsigned short MEDS_IPHASE = 6;
		unsigned short MEDS_ISLECT = 1;
		unsigned short MEDS_TAEM_GUIDANCE_END = 0;
		unsigned short MEDS_WOWLON = 0;
		unsigned short MEDS_HSI_MODE_LEFT = 1;
		unsigned short MEDS_HSI_MODE_RIGHT = 1;
		unsigned short MEDS_THETA_MAX_DELTA = 0;
		unsigned short MEDS_THETA_MIN_DELTA = 0;
		unsigned short MEDS_L_LADIPR_SCALE = 0;
		unsigned short MEDS_L_RADIPR_SCALE = 0;
		unsigned short MEDS_L_LADIYR_SCALE = 0;
		unsigned short MEDS_L_RADIYR_SCALE = 0;
		unsigned short MEDS_L_LADIRR_SCALE = 0;
		unsigned short MEDS_L_RADIRR_SCALE = 0;
		unsigned short MEDS_LADIRR_TGOSEC = 0;
		unsigned short MEDS_RADIRR_TGOSEC = 0;
		unsigned short MEDS_ADIRR_0_ON_R = 0;
		unsigned short MEDS_L_LADIPE_SCALE = 0;
		unsigned short MEDS_L_RADIPE_SCALE = 0;
		unsigned short MEDS_SB_AUTO = 0;
		unsigned short MEDS_DAP_PITCH_AUTO = 0;
		unsigned short MEDS_THROT_RY_AUTO = 0;
		unsigned short MEDS_THROT_RY_AUTO_BLANK = 0;
		unsigned short MEDS_L_ATT_SEL_SW = 0;
		unsigned short MEDS_R_ATT_SEL_SW = 0;
		unsigned short MEDS_CDI_SCALE = 0;
		unsigned short MEDS_D_AZ_OUT = 0;
		unsigned short MEDS_D_AZ_WARN = 0;
		unsigned short MEDS_P_RANGE_LABEL_CHAR1 = 0;
		unsigned short MEDS_P_RANGE_LABEL_CHAR2 = 0;
		unsigned short MEDS_P_RANGE_LABEL_CHAR3 = 0;
		unsigned short MEDS_P_RANGE_LABEL_CHAR4 = 0;
		unsigned short MEDS_P_RANGE_LABEL_CHAR5 = 0;
		unsigned short MEDS_T_NZ = 0;
		unsigned short MEDS_BETA_OUT = 0;
		unsigned short MEDS_D_INCL_OUT = 0;
		unsigned short MEDS_XTRK = 0;
		unsigned short MEDS_XTRK_DEV = 0;
		unsigned short MEDS_TGT_INCL = 0;

		unsigned short MEDS_FC_WORD_7_VAL = 1;
		unsigned short MEDS_FC_WORD_8_VAL = 0;
		unsigned short MEDS_FC_WORD_9_VAL = 0;
		unsigned short MEDS_FC_WORD_10_VAL = 0;
		unsigned short MEDS_FC_WORD_11_VAL = 0;
		unsigned short MEDS_FC_WORD_12_VAL = 0;
		unsigned short MEDS_FC_WORD_13_VAL = 0;
		unsigned short MEDS_FC_WORD_14_VAL = 0;
		unsigned short MEDS_FC_WORD_15_VAL = 0;
		unsigned short MEDS_FC_WORD_16_VAL = 0;
		unsigned short MEDS_FC_WORD_17_VAL = 0;
		unsigned short MEDS_FC_WORD_18_VAL = 0;
		unsigned short MEDS_FC_WORD_19_VAL = 0;
		unsigned short MEDS_FC_WORD_20_VAL = 0;
		unsigned short MEDS_FC_WORD_21_VAL = 0;
		unsigned short MEDS_FC_WORD_22_VAL = 0;
		unsigned short MEDS_FC_WORD_23_VAL = 0;
		unsigned short MEDS_FC_WORD_24_VAL = 0;
		unsigned short MEDS_FC_WORD_25_VAL = 0;
		unsigned short MEDS_FC_WORD_26_VAL = 0;
		unsigned short MEDS_FC_WORD_27_VAL = 0;
		unsigned short MEDS_FC_WORD_28_VAL = 0;
		unsigned short MEDS_FC_WORD_29_VAL = 0;
		unsigned short MEDS_FC_WORD_30_VAL = 0;
		unsigned short MEDS_FC_MSG2_WORD_1_VAL = 0;
		unsigned short MEDS_FC_MSG2_WORD_2_VAL = 0;
		unsigned short MEDS_FC_MSG2_WORD_3_VAL = 0;

		//// Major Mode processing
		unsigned short MEDS_MM = ReadCOMPOOL_IS( SCP_MM );


		//// Abort Mode, PPA, Roll Switch and EO Yaw Steering Flags Processing
		MEDS_CA_ABORT_DECLARED = GLIDE_RTLS_INHIBIT;
		MEDS_RTLS_ABORT_DECLARED = RTLS_ABORT_DECLARED;
		MEDS_AOA_ABORT_DECLARED = S_AOA;
		MEDS_ATO_ABORT_DECLARED = S_ATO;
		MEDS_TAL_ABORT_DECLARED = TAL_ABORT_DECLARED;

		if ((MEDS_MM == 101) || (MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 601))
		{
			if (ROLL_SW == -1)
			{
				MEDS_ROLL_SW = 1;
			}
			else
			{
				MEDS_ROLL_SW = 0;
			}
			LAST_ROLL_SW = MEDS_ROLL_SW;
		}
		else if (MEDS_MM == 104)
		{
			MEDS_ROLL_SW = LAST_ROLL_SW;
		}
		else
		{
			MEDS_ROLL_SW = 0;
		}

		if (MEDS_MM == 601)
		{
			MEDS_PPA = S_RTLS_TURN;
		}
		else
		{
			MEDS_PPA = 0;
		}

		if (((MEDS_MM == 102) || (MEDS_MM == 103)) && ((RTLS_ABORT_DECLARED == 0) && (S_ATO == 0) && (TAL_ABORT_DECLARED == 0)))
		{
			MEDS_EO_YAW_STEERING_ON = ENGINE_OUT_YAW_STEERING;
		}
		else
		{
			MEDS_EO_YAW_STEERING_ON = 0;
		}

		//// PFS Guidance Phase Processing
		if (MEDS_MM == 304)
		{
			MEDS_IPHASE = 1;
		}
		else
		{
			MEDS_IPHASE = IPHASE;
		}
		MEDS_ISLECT = ISLECT;

		//// TAEM Guidance End and WOWLON Processing
		MEDS_TAEM_GUIDANCE_END = TG_END;
		MEDS_WOWLON = WOWLON_IND;

		//// HSI Mode Indicator Processing
		MEDS_HSI_MODE_LEFT = HSI_MODE_LEFT;
		MEDS_HSI_MODE_RIGHT = HSI_MODE_RIGHT;

		//// Theta Max/Min Delta Processing
		double THETA_MAX_DELTA_SIN = sin( RAD * (THETA_MAX - THETA) );
		double THETA_MIN_DELTA_SIN = sin( RAD * (THETA - THETA_MIN) );
		MEDS_THETA_MAX_DELTA = 8 * static_cast<unsigned short>(4095 * THETA_MAX_DELTA_SIN);
		MEDS_THETA_MIN_DELTA = 8 * static_cast<unsigned short>(4095 * THETA_MIN_DELTA_SIN);

		//// ADI Error Scale Labels & Status Indicators (ADI Attitude Sel, Auto/Man Indicators) Processing
		// Left/Right ADI Pitch/Yaw Rate Scale Labels
		MEDS_L_LADIPR_SCALE = rangeint( 0, MEDS_LADIPR_SCALE, 8191 );
		MEDS_L_RADIPR_SCALE = rangeint( 0, MEDS_RADIPR_SCALE, 8191 );
		MEDS_L_LADIYR_SCALE = rangeint( 0, MEDS_LADIYR_SCALE, 8191 );
		MEDS_L_RADIYR_SCALE = rangeint( 0, MEDS_RADIYR_SCALE, 8191 );

		// Left/Right ADI Roll Rate Scale Labels
		MEDS_L_LADIRR_SCALE = rangeint( 0, MEDS_LADIRR_SCALE, 15 );
		MEDS_L_RADIRR_SCALE = rangeint( 0, MEDS_RADIRR_SCALE, 15 );

		if ((MEDS_MM == 305) || (MEDS_MM == 603))
		{
			MEDS_LADIRR_TGOSEC = MEDS_LH_TGOSC_FLAG;
			MEDS_RADIRR_TGOSEC = MEDS_RH_TGOSC_FLAG;
			if (YSGNP > 0.0)
			{
				MEDS_ADIRR_0_ON_R = 1;
			}
			else
			{
				MEDS_ADIRR_0_ON_R = 0;
			}
		}
		else
		{
			MEDS_LADIRR_TGOSEC = 0;
			MEDS_RADIRR_TGOSEC = 0;
			MEDS_ADIRR_0_ON_R = 0;
		}

		// Left/Right ADI Pitch Error Scale Labels
		MEDS_L_LADIPE_SCALE = rangeint( 0, MEDS_LADIPE_SCALE, 255 );
		MEDS_L_RADIPE_SCALE = rangeint( 0, MEDS_RADIPE_SCALE, 255 );

		// Status Fields for DAP, Throttle (THROT), PITCH & ROLL/YAW (RY), Speed Brake (SB) and ADI Attitude (ATT) Modes
		MEDS_SB_AUTO = 1;
		if ((MEDS_MM == 101) || (MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 104) || (MEDS_MM == 105) || (MEDS_MM == 106) || (MEDS_MM == 601))
		{
			if (ME_ZERO == 0)
			{
				MEDS_DAP_PITCH_AUTO = 1;
				MEDS_THROT_RY_AUTO = (S_MAN_THROT == 0) ? 1 : 0;
				MEDS_THROT_RY_AUTO_BLANK = 0;
			}
			else if (/*(ME_ZERO == 1) &&*/ (MEDS_MM == 601))
			{
				MEDS_DAP_PITCH_AUTO = 1;
				MEDS_THROT_RY_AUTO_BLANK = 1;
			}
			else
			{
				MEDS_DAP_PITCH_AUTO = AUTO_MODE;
				MEDS_THROT_RY_AUTO_BLANK = 1;
			}
		}
		else if ((MEDS_MM == 301) || (MEDS_MM == 302) || (MEDS_MM == 303))
		{
			MEDS_DAP_PITCH_AUTO = AUTO_MODE;
			MEDS_THROT_RY_AUTO_BLANK = 1;
		}
		else if ((MEDS_MM == 602) || (MEDS_MM == 603) || (MEDS_MM == 304) || (MEDS_MM == 305))
		{
			MEDS_DAP_PITCH_AUTO = AUTOP_IND_AUTOP_LAMP;
			MEDS_THROT_RY_AUTO_BLANK = 0;
			MEDS_THROT_RY_AUTO = AUTORY_IND_AUTORY_LAMP;
			MEDS_SB_AUTO = AUTOSB_IND;
		}

		MEDS_L_ATT_SEL_SW = ATT_SEL_SW[0];
		MEDS_R_ATT_SEL_SW = ATT_SEL_SW[1];

		//// CDI Scale Processing
		unsigned short L_CDI_SCALE = rangeint( 0, CDI_SCALE, 511 );
		if ((MEDS_MM == 101) || (MEDS_MM == 102) || (MEDS_MM == 103))
		{
			MEDS_CDI_SCALE = L_CDI_SCALE;
			LAST_CDI_SCALE = MEDS_CDI_SCALE;
		}
		else if (MEDS_MM == 104)
		{
			MEDS_CDI_SCALE = LAST_CDI_SCALE;
		}

		//// Delta Azimuth Processing
		// Delta Azimuth Digital Readout (MEDS_D_AZ_OUT)
		if ((MEDS_MM == 601) || ((TAL_ABORT_DECLARED == 1) && (MEDS_MM == 103)))
		{
			MEDS_D_AZ_OUT = static_cast<unsigned short>(DEG * MEDS_D_AZ);// LSB = 1º
			LAST_D_AZ = MEDS_D_AZ_OUT;
		}
		else if ((TAL_ABORT_DECLARED == 1) && (MEDS_MM == 104))
		{
			MEDS_D_AZ_OUT = LAST_D_AZ;
		}
		else if (MEDS_MM == 304)
		{
			MEDS_D_AZ_OUT = static_cast<unsigned short>(DEG * MEDS_DELAZ);// LSB = 1º
		}
		else if (MEDS_MM == 602)
		{
			MEDS_D_AZ_OUT = static_cast<unsigned short>(MEDS_DPSAC);// LSB = 1º
		}
		else if (((MEDS_MM == 305) || (MEDS_MM == 603)) && (IPHASE < 2))
		{
			MEDS_D_AZ_OUT = static_cast<unsigned short>(MEDS_DPSAC);// LSB = 1º
		}

		// Delta Azimuth Warning Flag (MEDS_D_AZ_WARN)
		if ((MEDS_MM == 304) && (ISLECT >= 2) && (fabs( ROLLC1 ) > ReadCOMPOOL_SS( SCP_MIN_ROLL_AZ_WARN )))
		{
			MEDS_D_AZ_WARN = BANK_FLAG;
		}
		else
		{
			MEDS_D_AZ_WARN = 0;
		}

		//// HSI Runway Range Label Processing
		if (((TAL_ABORT_DECLARED == 1) && ((MEDS_MM == 103) || (MEDS_MM == 104))) || ((MEDS_MM == 601) || (MEDS_MM == 602) || (MEDS_MM == 603) || (MEDS_MM == 304) || (MEDS_MM == 305)))
		{
			char rw[5];
			ReadCOMPOOL_C( SCP_SEL_SITE_ID, rw, 5 );

			MEDS_P_RANGE_LABEL_CHAR1 = rw[0];
			MEDS_P_RANGE_LABEL_CHAR2 = rw[1];
			MEDS_P_RANGE_LABEL_CHAR3 = rw[2];
			MEDS_P_RANGE_LABEL_CHAR4 = rw[3];
			MEDS_P_RANGE_LABEL_CHAR5 = rw[4];
		}

		//// Target Nz Processing
		double LDGRNZT = range( -5.0, DGRNZT, 10.0 );
		if (/*(-5.0 <= LDGRNZT) &&*/ (LDGRNZT <= 0.0))
		{
			MEDS_T_NZ = 8 * static_cast<unsigned short>(-LDGRNZT / 0.00125);// LSB = 0.00015625 g's (INFO formula says 0.00125 g's)
			MEDS_T_NZ |= 0x8000;// sign
		}
		else //if ((0.0 < LDGRNZT) && (LDGRNZT < 10.0))
		{
			MEDS_T_NZ = 8 * static_cast<unsigned short>(LDGRNZT / 0.00250);// LSB = 0.0003125 g's (INFO formula says 0.00250 g's)
		}

		//// Beta Readout Processing
		double L_MEDS_BETA = range( -99.9, MEDS_BETA, 99.9 );
		MEDS_BETA_OUT = static_cast<unsigned short>(L_MEDS_BETA * 10);// LSB = 0.1º

		//// Delta Inclination Readout Processing
		double L_MEDS_D_INCL = range( -99.99 * RAD, MEDS_D_INCL, 99.99 * RAD );
		if (TAL_ABORT_DECLARED == 0)
		{
			if ((MEDS_MM == 102) || (MEDS_MM == 103))
			{
				MEDS_D_INCL_OUT = 2 * static_cast<unsigned short>(DEG * L_MEDS_D_INCL * 100);// LSB = 0.005º
				LAST_D_INCL = MEDS_D_INCL_OUT;
			}
			else if (MEDS_MM == 104)
			{
				MEDS_D_INCL_OUT = LAST_D_INCL;
			}
		}

		//// Cross Track Readout Processing
		if ((MEDS_MM == 102) || (MEDS_MM == 103))
		{
			MEDS_XTRK = static_cast<unsigned short>(XTRK * 10);// LSB = 0.1 NM
			LAST_MEDS_XTRK = MEDS_XTRK;
		}
		else if (MEDS_MM == 104)
		{
			MEDS_XTRK = LAST_MEDS_XTRK;
		}

		//// Cross Track Deviation Readout Processing
		double L_XTRK_CDI = range( -2048, XTRK_CDI, 2047 );
		if (TAL_ABORT_DECLARED == 1)
		{
			if (MEDS_MM == 103)
			{
				MEDS_XTRK_DEV = static_cast<unsigned short>(L_XTRK_CDI);// LSB = 1 NM
				LAST_XTRK_DEV = MEDS_XTRK_DEV;
			}
			else if (MEDS_MM == 104)
			{
				MEDS_XTRK_DEV = LAST_XTRK_DEV;
			}
		}

		//// Target Inclination Readout Processing
		if (S_ATO == 1)
		{
			if (MEDS_MM == 103)
			{
				MEDS_TGT_INCL = static_cast<unsigned short>(DEG * INCL_TARGET * 10);// LSB = 0.1º
				LAST_TGT_INCL = MEDS_TGT_INCL;
			}
			else if (MEDS_MM == 104)
			{
				MEDS_TGT_INCL = LAST_TGT_INCL;
			}
		}


		//// validity bit determination
		unsigned short TAL_DECLARED_IN_103 = 0;
		unsigned short ATO_DECLARED_IN_103 = 0;
		// Major Mode Validity
		switch (MEDS_MM)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 801:
			case 601:
			case 602:
			case 603:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
				MEDS_FC_WORD_8_VAL = 1;
				break;
			default:
				MEDS_FC_WORD_8_VAL = 0;
		}

		// Abort Mode, PPA and Roll Switch Flags Validity
		if (MEDS_FC_WORD_8_VAL == 1)
		{
			switch (MEDS_MM)
			{
				case 101:
				case 102:
				case 103:
				case 104:
				case 105:
				case 106:
				case 301:
				case 302:
				case 303:
				case 304:
				case 305:
				case 601:
				case 602:
				case 603:
					MEDS_FC_WORD_9_VAL = 1;
					break;
				default:
					MEDS_FC_WORD_9_VAL = 0;
			}
		}
		if ((MEDS_FC_WORD_8_VAL == 1) && (MEDS_MM == 103))
		{
			if (TAL_ABORT_DECLARED == 1)
			{
				TAL_DECLARED_IN_103 = 1;
			}
			else
			{
				TAL_DECLARED_IN_103 = 0;
			}
		}
		if ((MEDS_FC_WORD_8_VAL == 1) && (MEDS_MM == 103))
		{
			if (S_ATO == 1)
			{
				ATO_DECLARED_IN_103 = 1;
			}
			else
			{
				ATO_DECLARED_IN_103 = 0;
			}
		}

		// Guidance Phase Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 305) || (MEDS_MM == 602) || (MEDS_MM == 603)))
		{
			MEDS_FC_WORD_10_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_10_VAL = 0;
		}
		if ((MEDS_FC_WORD_8_VAL == 1) && (MEDS_MM == 304))
		{
			MEDS_FC_WORD_11_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_11_VAL = 0;
		}

		// TAEM Guidance End and WOWLON Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 305) || (MEDS_MM == 603)))
		{
			MEDS_FC_WORD_12_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_12_VAL = 0;
		}

		// HSI Mode Indicator Validity
		if (MEDS_AREA_NAV_FIRST_PASS == 1)
		{
			MEDS_FC_WORD_13_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_13_VAL = 0;
		}

		// Theta Max/Min Delta Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 305) || (MEDS_MM == 602) || (MEDS_MM == 603)))
		{
			if ((MACH <= 2.0) && ((GC_AIF_FB == 0/*TODO INH*/) || D_DILEMMA))
			{
				MEDS_FC_WORD_14_VAL = 1;
				MEDS_FC_WORD_15_VAL = 1;
			}
			else
			{
				MEDS_FC_WORD_14_VAL = 1;
				MEDS_FC_WORD_15_VAL = 1;
			}
		}
		else
		{
			MEDS_FC_WORD_14_VAL = 0;
			MEDS_FC_WORD_15_VAL = 0;
		}

		// ADI Error Scale Labels & Status Indicators (ADI Attitude Sel, Auto/Man Indicators) Validity
		if (MEDS_FC_WORD_8_VAL == 1)
		{
			switch (MEDS_MM)
			{
				case 101:
				case 102:
				case 103:
				case 104:
				case 105:
				case 106:
				case 301:
				case 302:
				case 303:
				case 304:
				case 305:
				case 601:
				case 602:
				case 603:
					MEDS_FC_WORD_16_VAL = 1;
					MEDS_FC_WORD_17_VAL = 1;
					MEDS_FC_WORD_18_VAL = 1;
					MEDS_FC_WORD_19_VAL = 1;
					MEDS_FC_WORD_20_VAL = 1;
					MEDS_FC_WORD_21_VAL = 1;
					break;
				default:
					MEDS_FC_WORD_16_VAL = 0;
					MEDS_FC_WORD_17_VAL = 0;
					MEDS_FC_WORD_18_VAL = 0;
					MEDS_FC_WORD_19_VAL = 0;
					MEDS_FC_WORD_20_VAL = 0;
					MEDS_FC_WORD_21_VAL = 0;
			}
		}

		// CDI Scale Validity
		if ((NAV_INIT_FLAG == 1) && (MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 101) || (MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 104)))
		{
			MEDS_FC_WORD_22_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_22_VAL = 0;
		}

		// Delta Azimuth Validity
		if (MEDS_FC_WORD_8_VAL == 1)
		{
			if ((TAL_ABORT_DECLARED == 1) && (MEDS_MM == 103))
			{
				MEDS_FC_WORD_23_VAL = 1;
			}
			else if ((TAL_DECLARED_IN_103 == 1) && (MEDS_MM == 104) && (TAL_ABORT_DECLARED == 1))
			{
				MEDS_FC_WORD_23_VAL = 1;
			}
			else if ((MEDS_MM == 601) || (MEDS_MM == 602) || (MEDS_MM == 304))
			{
				MEDS_FC_WORD_23_VAL = 1;
			}
			else if ((IPHASE == 1) && ((MEDS_MM == 101) || (MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 104)))
			{
				MEDS_FC_WORD_23_VAL = 1;
			}
			else
			{
				MEDS_FC_WORD_23_VAL = 0;
			}
		}
		else
		{
			MEDS_FC_WORD_23_VAL = 0;
		}

		// HSI Relative Velocity Heading Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 601)))
		{
			MEDS_FC_WORD_24_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_24_VAL = 0;
		}

		// HSI Runway Range Label Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && (((TAL_ABORT_DECLARED == 1) && ((MEDS_MM == 103) || (MEDS_MM == 104))) || ((MEDS_MM == 601) || (MEDS_MM == 602) || (MEDS_MM == 603) || (MEDS_MM == 304) || (MEDS_MM == 305))))
		{
			MEDS_FC_WORD_25_VAL = 1;
			MEDS_FC_WORD_26_VAL = 1;
			MEDS_FC_WORD_27_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_25_VAL = 0;
			MEDS_FC_WORD_26_VAL = 0;
			MEDS_FC_WORD_27_VAL = 0;
		}

		// Target Nz Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && (MEDS_MM == 602) && (IPHASE >= 5) && (DGRNZT != 0))
		{
			MEDS_FC_WORD_28_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_28_VAL = 0;
		}

		// Beta Readout Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 601)) && (MEDS_BETAHVR_VALID == 1))
		{
			MEDS_FC_WORD_29_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_29_VAL = 0;
		}

		// Delta Inclination Readout Validity
		if ((TAL_ABORT_DECLARED == 0) && (MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 102) || (MEDS_MM == 103) || (MEDS_MM == 104)))
		{
			MEDS_FC_WORD_30_VAL = 1;
		}
		else
		{
			MEDS_FC_WORD_30_VAL = 0;
		}

		// Cross Track Readout Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && ((MEDS_MM == 102) || (MEDS_MM == 103) || ((MEDS_MM == 104) && ((TAL_ABORT_DECLARED == 0) || (TAL_DECLARED_IN_103 == 1)))))
		{
			MEDS_FC_MSG2_WORD_1_VAL = 1;
		}
		else
		{
			MEDS_FC_MSG2_WORD_1_VAL = 0;
		}

		// Cross Track Deviation Readout Validity
		if ((MEDS_FC_WORD_8_VAL == 1) && (TAL_ABORT_DECLARED == 1) && (MEDS_MM == 103))
		{
			MEDS_FC_MSG2_WORD_2_VAL = 1;
		}
		else if ((TAL_DECLARED_IN_103 == 1) && (MEDS_MM == 104) && (TAL_ABORT_DECLARED == 1) && (MEDS_FC_WORD_8_VAL == 1))
		{
			MEDS_FC_MSG2_WORD_2_VAL = 1;
		}
		else
		{
			MEDS_FC_MSG2_WORD_2_VAL = 0;
		}

		// Target Inclination Readout Validity
		if ((S_ATO == 1) && (MEDS_FC_WORD_8_VAL == 1) && (MEDS_MM == 103))
		{
			MEDS_FC_MSG2_WORD_3_VAL = 1;
		}
		else if ((MEDS_FC_WORD_8_VAL == 1) && (ATO_DECLARED_IN_103 == 1) && (MEDS_MM == 104) && (S_ATO == 1))
		{
			MEDS_FC_MSG2_WORD_3_VAL = 1;
		}
		else
		{
			MEDS_FC_MSG2_WORD_3_VAL = 0;
		}

		unsigned short MEDS_FC_XFER_VAL_WD1 = ((MEDS_FC_WORD_7_VAL & 0b1) << 15) | ((MEDS_FC_WORD_8_VAL & 0b1) << 14) | ((MEDS_FC_WORD_9_VAL & 0b1) << 13) | ((MEDS_FC_WORD_10_VAL & 0b1) << 12) |
			((MEDS_FC_WORD_11_VAL & 0b1) << 11) | ((MEDS_FC_WORD_12_VAL & 0b1) << 10) | ((MEDS_FC_WORD_13_VAL & 0b1) << 9) | ((MEDS_FC_WORD_14_VAL & 0b1) << 8) |
			((MEDS_FC_WORD_15_VAL & 0b1) << 7) | ((MEDS_FC_WORD_16_VAL & 0b1) << 6) | ((MEDS_FC_WORD_17_VAL & 0b1) << 5) | ((MEDS_FC_WORD_18_VAL & 0b1) << 4) |
			((MEDS_FC_WORD_19_VAL & 0b1) << 3) | ((MEDS_FC_WORD_20_VAL & 0b1) << 2) | ((MEDS_FC_WORD_21_VAL & 0b1) << 1) | ((MEDS_FC_WORD_22_VAL & 0b1) << 0);

		unsigned short MEDS_FC_XFER_VAL_WD2 = ((MEDS_FC_WORD_23_VAL & 0b1) << 15) | ((MEDS_FC_WORD_24_VAL & 0b1) << 14) | ((MEDS_FC_WORD_25_VAL & 0b1) << 13) | ((MEDS_FC_WORD_26_VAL & 0b1) << 12) |
			((MEDS_FC_WORD_27_VAL & 0b1) << 11) | ((MEDS_FC_WORD_28_VAL & 0b1) << 10) | ((MEDS_FC_WORD_29_VAL & 0b1) << 9) | ((MEDS_FC_WORD_30_VAL & 0b1) << 8) |
			((MEDS_FC_MSG2_WORD_1_VAL & 0b1) << 7) | ((MEDS_FC_MSG2_WORD_2_VAL & 0b1) << 6) | ((MEDS_FC_MSG2_WORD_3_VAL & 0b1) << 5);

		unsigned short MEDS_FC_XFER_VAL_WD3 = 0;
		unsigned short MEDS_FC_XFER_VAL_WD4 = 0;
		unsigned short MEDS_FC_XFER_VAL_WD5 = 0;
		unsigned short MEDS_FC_XFER_VAL_WD6 = 0;
		unsigned short MEDS_FC_XFER_FLAGS_1 = ((MEDS_FC_XFER_IS_PFS & 0b1) << 0);


		// output
		unsigned short tmp;
		//// MEDS FC TRANSFER MESSAGE 1
		// word 1 (MEDS_FC_XFER_VAL_WD1)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 1, MEDS_FC_XFER_VAL_WD1, 30 );
		// word 2 (MEDS_FC_XFER_VAL_WD2)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 2, MEDS_FC_XFER_VAL_WD2, 30 );
		// word 3 (MEDS_FC_XFER_VAL_WD3)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 3, MEDS_FC_XFER_VAL_WD3, 30 );
		// word 4 (MEDS_FC_XFER_VAL_WD4)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 4, MEDS_FC_XFER_VAL_WD4, 30 );
		// word 5 (MEDS_FC_XFER_VAL_WD5)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 5, MEDS_FC_XFER_VAL_WD5, 30 );
		// word 6 (MEDS_FC_XFER_VAL_WD6)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 6, MEDS_FC_XFER_VAL_WD6, 30 );
		// word 7 (MEDS_FC_XFER_FLAGS_1)
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 7, MEDS_FC_XFER_FLAGS_1, 30 );
		// word 8
		tmp = ((MEDS_MM & 0x03FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 8, tmp, 30 );
		// word 9
		tmp = ((MEDS_EO_YAW_STEERING_ON & 0b1) << 7) | ((MEDS_ROLL_SW & 0b1) << 6) | ((MEDS_PPA & 0b1) << 5) | ((MEDS_CA_ABORT_DECLARED & 0b1) << 4) |
			((MEDS_RTLS_ABORT_DECLARED & 0b1) << 3) | ((MEDS_AOA_ABORT_DECLARED & 0b1) << 2) | ((MEDS_ATO_ABORT_DECLARED & 0b1) << 1) | ((MEDS_TAL_ABORT_DECLARED & 0b1) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 9, tmp, 30 );
		// word 10
		tmp = ((MEDS_IPHASE & 0b111) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 10, tmp, 30 );
		// word 11
		tmp = ((MEDS_ISLECT & 0b1111) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 11, tmp, 30 );
		// word 12
		tmp = ((MEDS_TAEM_GUIDANCE_END & 0b1) << 1) | ((MEDS_WOWLON & 0b1) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 12, tmp, 30 );
		// word 13
		tmp = ((MEDS_HSI_MODE_LEFT & 0b11) << 2) | ((MEDS_HSI_MODE_RIGHT & 0b11) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 13, tmp, 30 );
		// word 14
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 14, MEDS_THETA_MAX_DELTA, 30 );
		// word 15
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 15, MEDS_THETA_MIN_DELTA, 30 );
		// word 16
		tmp = ((MEDS_LADIRR_TGOSEC & 0b1) << 15) | ((MEDS_ADIRR_0_ON_R & 0b1) << 14) | ((MEDS_L_LADIPR_SCALE & 0x1FFF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 16, tmp, 30 );
		// word 17
		tmp = ((MEDS_RADIRR_TGOSEC & 0b1) << 15) | ((MEDS_L_RADIPR_SCALE & 0x1FFF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 17, tmp, 30 );
		// word 18
		tmp = ((MEDS_L_LADIYR_SCALE & 0x1FFF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 18, tmp, 30 );
		// word 19
		tmp = ((MEDS_L_RADIYR_SCALE & 0x1FFF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 19, tmp, 30 );
		// word 20
		tmp = ((MEDS_L_ATT_SEL_SW & 0b11) << 14) | ((MEDS_R_ATT_SEL_SW & 0b11) << 12) | ((MEDS_SB_AUTO & 0b1) << 11) | ((MEDS_THROT_RY_AUTO_BLANK & 0b1) << 10) |
			((MEDS_THROT_RY_AUTO & 0b1) << 9) | ((MEDS_DAP_PITCH_AUTO & 0b1) << 8) | ((MEDS_L_LADIRR_SCALE & 0b1111) << 4) | ((MEDS_L_RADIRR_SCALE & 0b1111) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 20, tmp, 30 );
		// word 21
		tmp = ((MEDS_L_LADIPE_SCALE & 0x00FF) << 8) | ((MEDS_L_RADIPE_SCALE & 0x00FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 21, tmp, 30 );
		// word 22
		tmp = ((MEDS_CDI_SCALE & 0x01FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 22, tmp, 30 );
		// word 23
		tmp = ((MEDS_D_AZ_WARN & 0b1) << 9) | ((MEDS_D_AZ_OUT & 0x01FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 23, tmp, 30 );
		// word 24
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 24, MEDS_H_VR, 30 );
		// word 25
		tmp = ((MEDS_P_RANGE_LABEL_CHAR2 & 0x00FF) << 8) | ((MEDS_P_RANGE_LABEL_CHAR1 & 0x00FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 25, tmp, 30 );
		// word 26
		tmp = ((MEDS_P_RANGE_LABEL_CHAR4 & 0x00FF) << 8) | ((MEDS_P_RANGE_LABEL_CHAR3 & 0x00FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 26, tmp, 30 );
		// word 27
		tmp = ((MEDS_P_RANGE_LABEL_CHAR5 & 0x00FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 27, tmp, 30 );
		// word 28
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 28, MEDS_T_NZ, 30 );
		// word 29
		tmp = ((MEDS_BETA_OUT & 0x07FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 29, tmp, 30 );
		// word 30
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_1, 30, MEDS_D_INCL_OUT, 30 );

		//// MEDS FC TRANSFER MESSAGE 2
		// word 1
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 1, MEDS_XTRK, 30 );
		// word 2
		tmp = ((MEDS_XTRK_DEV & 0x0FFF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 2, tmp, 30 );
		// word 3
		tmp = ((MEDS_TGT_INCL & 0x03FF) << 0);
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 3, tmp, 30 );
		// word 4
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 4, 0, 30 );
		// word 5
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 5, 0, 30 );
		// word 6
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 6, 0, 30 );
		// word 7
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 7, 0, 30 );
		// word 8
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 8, 0, 30 );
		// word 9
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 9, 0, 30 );
		// word 10
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 10, 0, 30 );
		// word 11
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 11, 0, 30 );
		// word 12
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 12, 0, 30 );
		// word 13
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 13, 0, 30 );
		// word 14
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 14, 0, 30 );
		// word 15
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 15, 0, 30 );
		// word 16
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 16, 0, 30 );
		// word 17
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 17, 0, 30 );
		// word 18
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 18, 0, 30 );
		// word 19
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 19, 0, 30 );
		// word 20
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 20, 0, 30 );
		// word 21
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 21, 0, 30 );
		// word 22
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 22, 0, 30 );
		// word 23
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 23, 0, 30 );
		// word 24
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 24, 0, 30 );
		// word 25
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 25, 0, 30 );
		// word 26
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 26, 0, 30 );
		// word 27
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 27, 0, 30 );
		// word 28
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 28, 0, 30 );
		// word 29
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 29, 0, 30 );
		// word 30
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_2, 30, 0, 30 );

		//// MEDS FC TRANSFER MESSAGE 3
		// word 1
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 1, 0, 30 );
		// word 2
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 2, 0, 30 );
		// word 3
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 3, 0, 30 );
		// word 4
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 4, 0, 30 );
		// word 5
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 5, 0, 30 );
		// word 6
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 6, 0, 30 );
		// word 7
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 7, 0, 30 );
		// word 8
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 8, 0, 30 );
		// word 9
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 9, 0, 30 );
		// word 10
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 10, 0, 30 );
		// word 11
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 11, 0, 30 );
		// word 12
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 12, 0, 30 );
		// word 13
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 13, 0, 30 );
		// word 14
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 14, 0, 30 );
		// word 15
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 15, 0, 30 );
		// word 16
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 16, 0, 30 );
		// word 17
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 17, 0, 30 );
		// word 18
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 18, 0, 30 );
		// word 19
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 19, 0, 30 );
		// word 20
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 20, 0, 30 );
		// word 21
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 21, 0, 30 );
		// word 22
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 22, 0, 30 );
		// word 23
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 23, 0, 30 );
		// word 24
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 24, 0, 30 );
		// word 25
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 25, 0, 30 );
		// word 26
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 26, 0, 30 );
		// word 27
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 27, 0, 30 );
		// word 28
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 28, 0, 30 );
		// word 29
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 29, 0, 30 );
		// word 30
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_3, 30, 0, 30 );

		//// MEDS FC TRANSFER MESSAGE 4
		// word 1
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 1, 0, 30 );
		// word 2
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 2, 0, 30 );
		// word 3
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 3, 0, 30 );
		// word 4
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 4, 0, 30 );
		// word 5
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 5, 0, 30 );
		// word 6
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 6, 0, 30 );
		// word 7
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 7, 0, 30 );
		// word 8
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 8, 0, 30 );
		// word 9
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 9, 0, 30 );
		// word 10
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 10, 0, 30 );
		// word 11
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 11, 0, 30 );
		// word 12
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 12, 0, 30 );
		// word 13
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 13, 0, 30 );
		// word 14
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 14, 0, 30 );
		// word 15
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 15, 0, 30 );
		// word 16
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 16, 0, 30 );
		// word 17
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 17, 0, 30 );
		// word 18
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 18, 0, 30 );
		// word 19
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 19, 0, 30 );
		// word 20
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 20, 0, 30 );
		// word 21
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 21, 0, 30 );
		// word 22
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 22, 0, 30 );
		// word 23
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 23, 0, 30 );
		// word 24
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 24, 0, 30 );
		// word 25
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 25, 0, 30 );
		// word 26
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 26, 0, 30 );
		// word 27
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 27, 0, 30 );
		// word 28
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 28, 0, 30 );
		// word 29
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 29, 0, 30 );
		// word 30
		WriteCOMPOOL_AIS( SCP_MEDS_FC_TRANSFER_MESSAGE_4, 30, 0, 30 );
		return;
	}

	bool MEDSFCGNCXFER::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 801:
			case 901:
				return true;
			default:
				return false;
		}
	}

	bool MEDSFCGNCXFER::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void MEDSFCGNCXFER::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}
