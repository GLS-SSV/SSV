#include "HUD_PROC.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr unsigned short DECEL_CMD_MAX = 16;// Maximum Deceleration Command (V99U7145C) [fps^2]
	constexpr unsigned short PITCH_ADJ = 32119;// Pitch Adjustment (V99U7590C) [1]
	constexpr unsigned short RW_REM_STP = 1000;// Runway Remaining to Stop (V99U7143C) [ft]
	constexpr unsigned short RW_TGO_MIN = 10;// Runway to go Minimum (V99U7168C) [ft]
	constexpr unsigned short VV_FILT_FREQ = 22861;// VV Filter Frequency (V99U7592C) [1]


	HUD_PROC::HUD_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "HUD_PROC" ),
		HUD_LH_ATT_PB_LAST(0), HUD_RH_ATT_PB_LAST(0), HUD_ATT_REF_LAST(0)
	{
		return;
	}

	HUD_PROC::~HUD_PROC( void )
	{
		return;
	}

	void HUD_PROC::Realize( void )
	{
		return;
	}

	void HUD_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		VECTOR3 POSN_WRT_RW = ReadCOMPOOL_VS( SCP_POSN_WRT_RW );
		VECTOR3 VEL_WRT_RW  = ReadCOMPOOL_VS( SCP_VEL_WRT_RW );
		float AZIMUTH_RW = ReadCOMPOOL_SS( SCP_AZIMUTH_RW );
		float ANGLE_CORR_TNTOMAG_RW = ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW );
		unsigned short IGS = ReadCOMPOOL_IS( SCP_IGS );
		unsigned short IGI = ReadCOMPOOL_IS( SCP_IGI );
		float V_REF[2];
		V_REF[0] = ReadCOMPOOL_VS( SCP_V_REF, 1, 2 );
		V_REF[1] = ReadCOMPOOL_VS( SCP_V_REF, 2, 2 );
		float X_ZERO[2];
		X_ZERO[0] = ReadCOMPOOL_VS( SCP_X_ZERO, 1, 2 );
		X_ZERO[1] = ReadCOMPOOL_VS( SCP_X_ZERO, 2, 2 );
		unsigned short NEP_FB = ReadCOMPOOL_IS( SCP_NEP_FB );
		double ALT_WHEELS = ReadCOMPOOL_SD( SCP_ALT_WHEELS );
		unsigned short P_MODE = ReadCOMPOOL_IS( SCP_P_MODE );
		unsigned short IPHASE = ReadCOMPOOL_IS( SCP_IPHASE );
		unsigned short NAV_ALT_FLAG = 0;// TODO
		unsigned short NAV_MLS_FLAG = 0;// TODO
		unsigned short RA_FLAG = 0;// TODO
		unsigned short NAV_TAC_FLAG = 0;// TODO
		unsigned short TG_END = ReadCOMPOOL_IS( SCP_TG_END );
		float H_DOT_ELLIPSOID = ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID );
		float ACC_DRAG = ReadCOMPOOL_SS( SCP_ACC_DRAG );
		float HERROR = ReadCOMPOOL_SS( SCP_HERROR );
		float H_ERROR = ReadCOMPOOL_SS( SCP_H_ERROR );
		float ENER_LL_Y = 0.0f;// TODO
		float SHUTTLE_ENER_Y = 0.0f;// TODO
		float ENER_UL_Y = 0.0f;// TODO
		float NOM_ENERGY_Y = 0.0f;// TODO
		float GAMMA_REF_2 = ReadCOMPOOL_SS( SCP_GAMMA_REF_2 );
		float SIGMA[2];
		SIGMA[0] = ReadCOMPOOL_VS( SCP_SIGMA, 1, 2 );
		SIGMA[1] = ReadCOMPOOL_VS( SCP_SIGMA, 2, 2 );
		unsigned short HUD_WOWLON = ReadCOMPOOL_IS( SCP_HUD_WOWLON );
		unsigned short SEL_LH_ADI_ATT_REF_PB = ReadCOMPOOL_IS( SCP_SEL_LH_ADI_ATT_REF_PB );
		unsigned short SEL_RH_ADI_ATT_REF_PB = ReadCOMPOOL_IS( SCP_SEL_RH_ADI_ATT_REF_PB );
		unsigned short HUD_GEAR_TRANS = ReadCOMPOOL_IS( SCP_HUD_GEAR_TRANS );
		unsigned short HUD_HYDSAT = ReadCOMPOOL_IS( SCP_HUD_HYDSAT );
		unsigned short HUD_SB_RETRACT = ReadCOMPOOL_IS( SCP_HUD_SB_RETRACT );
		unsigned short HUD_GEAR_UP = ReadCOMPOOL_IS( SCP_HUD_GEAR_UP );
		unsigned short HUD_BF = ReadCOMPOOL_IS( SCP_HUD_BF );
		unsigned short HUD_SPBRK = ReadCOMPOOL_IS( SCP_HUD_SPBRK );
		unsigned short HUD_HI_G = ReadCOMPOOL_IS( SCP_HUD_HI_G );
		unsigned short HUD_ROLLOUT = ReadCOMPOOL_IS( SCP_HUD_ROLLOUT );
		unsigned short HUD_MODE_BANK = ReadCOMPOOL_IS( SCP_HUD_MODE_BANK );
		unsigned short HUD_MODE_SB = ReadCOMPOOL_IS( SCP_HUD_MODE_SB );
		unsigned short HUD_MODE_PITCH = ReadCOMPOOL_IS( SCP_HUD_MODE_PITCH );
		unsigned short HUD_SPBRK_POS = ReadCOMPOOL_IS( SCP_HUD_SPBRK_POS );
		unsigned short HUD_SPBRK_CMD = ReadCOMPOOL_IS( SCP_HUD_SPBRK_CMD );
		unsigned short HUD_HEADING =  ReadCOMPOOL_IS( SCP_HUD_HEADING );
		unsigned short HUD_ROLLERR = ReadCOMPOOL_IS( SCP_HUD_ROLLERR );
		unsigned short HUD_PITCHERR = ReadCOMPOOL_IS( SCP_HUD_PITCHERR );
		unsigned short HUD_AIL_POS = ReadCOMPOOL_IS( SCP_HUD_AIL_POS );
		unsigned short HUD_AIL_CMD = 0;// TODO
		unsigned short HUD_L_FORMAT = 1;// TODO
		unsigned short HUD_R_FORMAT = 1;// TODO
		unsigned short HUD_L_HSI_SEL = ReadCOMPOOL_IS( SCP_HUD_L_HSI_SEL );
		unsigned short HUD_R_HSI_SEL = ReadCOMPOOL_IS( SCP_HUD_R_HSI_SEL );
		unsigned short HUD_L_ADI_SCL = ReadCOMPOOL_IS( SCP_HUD_L_ADI_SCL );
		unsigned short HUD_R_ADI_SCL = ReadCOMPOOL_IS( SCP_HUD_R_ADI_SCL );
		unsigned short HUD_RW_LENGTH = ReadCOMPOOL_IS( SCP_HUD_RW_LENGTH );

		// outputs
		unsigned short HUD_ALTNV = NAV_ALT_FLAG;
		unsigned short HUD_ATT_REF = HUD_ATT_REF_LAST;
		unsigned short HUD_BFS_IND = 0;
		unsigned short HUD_BFS_TGEND = 0;
		unsigned short HUD_CNTL1;
		unsigned short HUD_CNTL2_L;
		unsigned short HUD_CNTL2_R;
		unsigned short HUD_DCL_CMD_MAX = DECEL_CMD_MAX;
		unsigned short HUD_EAS_REF;
		unsigned short HUD_EMIN;
		unsigned short HUD_ENOM;
		unsigned short HUD_EOW;
		unsigned short HUD_ESTURN;
		unsigned short HUD_FLAG_1;
		unsigned short HUD_FLAG_2;
		unsigned short HUD_GAMMA_REF1 = 0;
		unsigned short HUD_GAMMA_REF2 = 0;
		unsigned short HUD_HERROR;
		unsigned short HUD_IPHASE;
		unsigned short HUD_MLSNV = NAV_MLS_FLAG;
		unsigned short HUD_PITCH_ADJ = PITCH_ADJ;
		unsigned short HUD_P_MODE = P_MODE;
		unsigned short HUD_RALNV = RA_FLAG;
		unsigned short HUD_RWY_HDG;
		unsigned short HUD_RW_REM_STP = RW_REM_STP;
		unsigned short HUD_RW_TGO_MIN = RW_TGO_MIN;
		unsigned short HUD_SPARE_CDW_06 = 0;
		unsigned short HUD_SPARE_CDW_07 = 0;
		unsigned short HUD_SPARE_CDW_08 = 0;
		unsigned short HUD_SPARE_CDW_09 = 0;
		unsigned short HUD_SPARE_CDW_10 = 0;
		unsigned short HUD_SPARE_CDW_11 = 0;
		unsigned short HUD_SPARE_CDW_12 = 0;
		unsigned short HUD_TACNV = NAV_TAC_FLAG;
		unsigned short HUD_TEST_WD = -68;
		unsigned short HUD_VV_FILT_FREQ = VV_FILT_FREQ;
		unsigned short HUD_X_RW_POS;
		unsigned short HUD_X_RW_SCL;
		unsigned short HUD_X_RW_VEL;
		unsigned short HUD_X_ZERO = 0;
		unsigned short HUD_Y_RW_POS;
		unsigned short HUD_Y_RW_SCL;
		unsigned short HUD_Y_RW_VEL;
		unsigned short HUD_Z_RW_POS;
		unsigned short HUD_Z_RW_SCL;
		unsigned short HUD_Z_RW_VEL;
		unsigned short HUD_VEL_SCL;
		unsigned short HUD_ACC_DRAG;
		unsigned short HUD_HDOT;


		unsigned short HUD_IGS;
		if ((MM == 602) || (MM == 603))
		{
			HUD_IGS = 1;
		}
		else
		{
			HUD_IGS = IGS;
		}

		// GAMMA REFERENCE CALCULATION
		double GREF1 = 0.0;// [deg]
		double GREF2 = -50.0;// [deg]
		if (((MM == 305) || (MM == 603)) && (HUD_WOWLON == 0))
		{
			if (HUD_P_MODE == 4)
			{
				// final flare
				double TEMP = fabs( ReadCOMPOOL_SS( SCP_H_NO_ACC ) - ALT_WHEELS ) / ReadCOMPOOL_SS( SCP_TAU_TD2F );
				double HDOT_REFF = ReadCOMPOOL_SS( SCP_H_TD2_DOT ) - TEMP;
				GREF2 = atan2( HDOT_REFF, VEL_WRT_RW.data[0] ) * DEG;
			}
			else
			{
				if ((ALT_WHEELS < ReadCOMPOOL_MS( SCP_HEXP, HUD_IGS, IGI, 2, 2 )) && (HUD_P_MODE == 3))
				{
					// exp decay
					double XEST1 = exp( (ALT_WHEELS - ReadCOMPOOL_MS( SCP_HEXP, HUD_IGS, IGI, 2, 2 )) / ReadCOMPOOL_VS( SCP_SIGMAH, HUD_IGS, 2 ) );
					double XEST2 = ReadCOMPOOL_SS( SCP_X_AIM_PT ) + ALT_WHEELS / tan( GAMMA_REF_2 * RAD );
					double XEST = XEST1 * ReadCOMPOOL_MS( SCP_XDECAY, HUD_IGS, IGI, 2, 2 ) + XEST2;
					double TEMP = exp( (ReadCOMPOOL_MS( SCP_X_EXP, HUD_IGS, IGI, 2, 2 ) - XEST) / SIGMA[HUD_IGS - 1] );
					double TEMP2 = atan2( (TEMP * ReadCOMPOOL_MS( SCP_HDECAY2, HUD_IGS, IGI, 2, 2 )), SIGMA[HUD_IGS - 1] ) * DEG;
					GREF2 = GAMMA_REF_2 - TEMP2;
				}
				else if ((ReadCOMPOOL_MS( SCP_HEXP, HUD_IGS, IGI, 2, 2 ) <= ALT_WHEELS) && (ALT_WHEELS <= ReadCOMPOOL_MS( SCP_HCLOOP2, HUD_IGS, IGI, 2, 2 )))
				{
					// pull-up circle
					double TEMP = (ReadCOMPOOL_MS( SCP_H_K2, HUD_IGS, IGI, 2, 2 ) - ALT_WHEELS) / ReadCOMPOOL_MS( SCP_RH, HUD_IGS, IGI, 2, 2 );
					GREF2 = (asin( TEMP ) * DEG) - 90;
				}
			}
			HUD_GAMMA_REF2 = static_cast<unsigned short>(100 * GREF2);

			GREF1 = ReadCOMPOOL_VS( SCP_GAMMA_REF_1, HUD_IGS, 2 );
			HUD_GAMMA_REF1 = static_cast<unsigned short>(100 * GREF1);
		}

		// HUD VELOCITY VECTOR CAGE/UNCAGE
		if (((SEL_LH_ADI_ATT_REF_PB == 1) && (HUD_LH_ATT_PB_LAST == 0)) || ((SEL_RH_ADI_ATT_REF_PB == 1) && (HUD_RH_ATT_PB_LAST == 0)))
		{
			HUD_ATT_REF = HUD_ATT_REF_LAST ? 0 : 1;
			HUD_ATT_REF_LAST = HUD_ATT_REF;
		}
		HUD_LH_ATT_PB_LAST = SEL_LH_ADI_ATT_REF_PB;
		HUD_RH_ATT_PB_LAST = SEL_RH_ADI_ATT_REF_PB;

		// TAEM processing
		HUD_EMIN = static_cast<unsigned short>(ENER_LL_Y);
		HUD_EOW = static_cast<unsigned short>(SHUTTLE_ENER_Y);
		HUD_ESTURN = static_cast<unsigned short>(ENER_UL_Y);
		HUD_ENOM = static_cast<unsigned short>(NOM_ENERGY_Y);

		// HUD_HERROR
		if (TG_END == 0)
		{
			HUD_HERROR = static_cast<unsigned short>(midval( HERROR, -32768, 32767 ));
		}
		else
		{
			HUD_HERROR = static_cast<unsigned short>(H_ERROR);
		}
		HUD_HERROR = -HUD_HERROR;

		// HUD_IPHASE
		if ((NEP_FB == 1) && (ALT_WHEELS <= ReadCOMPOOL_SS( SCP_HUD_NEP_PFNL_MIN_ALT )))
		{
			HUD_IPHASE = 3;
		}
		else
		{
			HUD_IPHASE = IPHASE;
		}

		// HUD_EAS_REF
		HUD_EAS_REF = static_cast<unsigned short>(V_REF[HUD_IGS - 1]);

		// HUD_X_ZERO
		if (((MM == 305) || (MM == 603)) && (HUD_WOWLON == 0))
		{
			HUD_X_ZERO = static_cast<unsigned short>(X_ZERO[IGI - 1]);
		}

		// HUD_RWY_HDG
		HUD_RWY_HDG = static_cast<unsigned short>((AZIMUTH_RW - ANGLE_CORR_TNTOMAG_RW) * DEG * 50);

		// HUD_X_RW_POS
		// HUD_X_RW_SCL
		if (fabs( POSN_WRT_RW.data[0] ) <= 32768)
		{
			HUD_X_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[0]);
			HUD_X_RW_SCL = 0;
		}
		else if (/*(32768 < fabs( POSN_WRT_RW.data[0] )) &&*/ (fabs( POSN_WRT_RW.data[0] ) <= 327680))
		{
			HUD_X_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[0] / 10.0);
			HUD_X_RW_SCL = 1;
		}
		else //if ((327680 < fabs( POSN_WRT_RW.data[0] )) && (fabs( POSN_WRT_RW.data[0] ) <= 3276800))
		{
			HUD_X_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[0] / 100.0);
			HUD_X_RW_SCL = 2;
		}

		// HUD_Y_RW_POS
		// HUD_Y_RW_SCL
		if (fabs( POSN_WRT_RW.data[1] ) <= 32768)
		{
			HUD_Y_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[1]);
			HUD_Y_RW_SCL = 0;
		}
		else if (/*(32768 < fabs( POSN_WRT_RW.data[1] )) &&*/ (fabs( POSN_WRT_RW.data[1] ) <= 327680))
		{
			HUD_Y_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[1] / 10.0);
			HUD_Y_RW_SCL = 1;
		}
		else //if ((327680 < fabs( POSN_WRT_RW.data[1] )) && (fabs( POSN_WRT_RW.data[1] ) <= 3276800))
		{
			HUD_Y_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[1] / 100.0);
			HUD_Y_RW_SCL = 2;
		}

		// HUD_Z_RW_POS
		// HUD_Z_RW_SCL
		if (fabs( POSN_WRT_RW.data[2] ) <= 32768)
		{
			HUD_Z_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[2]);
			HUD_Z_RW_SCL = 0;
		}
		else if (/*(32768 < fabs( POSN_WRT_RW.data[2] )) &&*/ (fabs( POSN_WRT_RW.data[2] ) <= 327680))
		{
			HUD_Z_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[2] / 10.0);
			HUD_Z_RW_SCL = 1;
		}
		else //if ((327680 < fabs( POSN_WRT_RW.data[2] )) && (fabs( POSN_WRT_RW.data[2] ) <= 3276800))
		{
			HUD_Z_RW_POS = static_cast<unsigned short>(POSN_WRT_RW.data[2] / 100.0);
			HUD_Z_RW_SCL = 2;
		}

		// HUD_ACC_DRAG
		HUD_ACC_DRAG = static_cast<unsigned short>(ACC_DRAG * 100);

		// HUD_HDOT
		HUD_HDOT = static_cast<unsigned short>(H_DOT_ELLIPSOID);

		// HUD_X_RW_VEL
		// HUD_Y_RW_VEL
		// HUD_Z_RW_VEL
		// HUD_VEL_SCL
		if ((MM == 304) || (MM == 602))
		{
			HUD_X_RW_VEL = static_cast<unsigned short>(VEL_WRT_RW.data[0]);
			HUD_Y_RW_VEL = static_cast<unsigned short>(VEL_WRT_RW.data[1]);
			HUD_Z_RW_VEL = static_cast<unsigned short>(VEL_WRT_RW.data[2]);
			HUD_VEL_SCL = 0;
		}
		else //if ((MM == 305) || (MM == 603))
		{
			HUD_X_RW_VEL = static_cast<unsigned short>(VEL_WRT_RW.data[0] * 10);
			HUD_Y_RW_VEL = static_cast<unsigned short>(VEL_WRT_RW.data[1] * 10);
			HUD_Z_RW_VEL = static_cast<unsigned short>(VEL_WRT_RW.data[2] * 10);
			HUD_VEL_SCL = 1;
		}

		// HUD_CNTL1
		HUD_CNTL1 = ((HUD_X_RW_SCL & 0b11) << 14) | ((HUD_Y_RW_SCL & 0b11) << 12) | ((HUD_Z_RW_SCL & 0b11) << 10) | ((HUD_VEL_SCL & 0b1) << 9) | ((HUD_BFS_IND & 0b1) << 7);

		// HUD_FLAG_1
		HUD_FLAG_1 = ((HUD_ATT_REF & 0b1) << 15) | ((HUD_WOWLON & 0b1) << 14) | ((HUD_ROLLOUT & 0b1) << 13) | ((HUD_HI_G & 0b1) << 12) | ((HUD_SPBRK & 0b1) << 11) |
			((HUD_BF & 0b1) << 10) | ((HUD_GEAR_UP & 0b1) << 9) | ((HUD_ALTNV & 0b1) << 8) | ((HUD_TACNV & 0b1) << 7) | ((HUD_MLSNV & 0b1) << 6) |
			((HUD_RALNV & 0b1) << 5) | ((HUD_SB_RETRACT & 0b1) << 4) | ((HUD_HYDSAT & 0b1) << 3) | ((HUD_GEAR_TRANS & 0b1) << 2) | ((HUD_BFS_TGEND & 0b1) << 1);

		// HUD_FLAG_2
		HUD_FLAG_2 = ((HUD_P_MODE & 0b111) << 10) | ((HUD_MODE_PITCH & 0b1) << 5) | ((HUD_MODE_SB & 0b1) << 4) | ((HUD_MODE_BANK & 0b1) << 3) | ((HUD_IPHASE & 0b111) << 0);

		// HUD_CNTL2_L
		HUD_CNTL2_L = ((HUD_L_ADI_SCL & 0b11) << 14) | ((HUD_L_HSI_SEL & 0b11) << 12) | ((HUD_L_FORMAT & 0b111) << 9);

		// HUD_CNTL2_R
		HUD_CNTL2_R = ((HUD_R_ADI_SCL & 0b11) << 14) | ((HUD_R_HSI_SEL & 0b11) << 12) | ((HUD_R_FORMAT & 0b111) << 9);


		// output
		// HUD Unique Message 1
		// HUD MSG1 CONTROL WORD
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 1, HUD_CNTL1, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 1, HUD_CNTL1, 31 );
		// TEST WORD
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 2, HUD_TEST_WD, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 2, HUD_TEST_WD, 31 );
		// GPC TO HUD FLAGS WORD 1
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 3, HUD_FLAG_1, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 3, HUD_FLAG_1, 31 );
		// GPC TO HUD FLAGS WORD 2
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 4, HUD_FLAG_2, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 4, HUD_FLAG_2, 31 );
		// SPEEDBRAKE POSITION
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 5, HUD_SPBRK_POS, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 5, HUD_SPBRK_POS, 31 );
		// SPEEDBRAKE COMMAND
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 6, HUD_SPBRK_CMD, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 6, HUD_SPBRK_CMD, 31 );
		// X POSITION WRT RUNWAY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 7, HUD_X_RW_POS, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 7, HUD_X_RW_POS, 31 );
		// Y POSITION WRT RUNWAY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 8, HUD_Y_RW_POS, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 8, HUD_Y_RW_POS, 31 );
		// Z POSITION WRT RUNWAY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 9, HUD_Z_RW_POS, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 9, HUD_Z_RW_POS, 31 );
		// X VELOCITY WRT RUNWAY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 10, HUD_X_RW_VEL, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 10, HUD_X_RW_VEL, 31 );
		// Y VELOCITY WRT RUNWAY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 11, HUD_Y_RW_VEL, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 11, HUD_Y_RW_VEL, 31 );
		// Z VELOCITY WRT RUNWAY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 12, HUD_Z_RW_VEL, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 12, HUD_Z_RW_VEL, 31 );
		// HEADING
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 13, HUD_HEADING, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 13, HUD_HEADING, 31 );
		// ACC DRAG
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 14, HUD_ACC_DRAG, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 14, HUD_ACC_DRAG, 31 );
		// H DOT ELLIPSOID
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 15, HUD_HDOT, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 15, HUD_HDOT, 31 );
		// FLIGHT PATH REFERENCE 2
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 16, HUD_GAMMA_REF2, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 16, HUD_GAMMA_REF2, 31 );
		// ROLL ERROR
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 17, HUD_ROLLERR, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 17, HUD_ROLLERR, 31 );
		// PITCH ERROR
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 18, HUD_PITCHERR, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 18, HUD_PITCHERR, 31 );
		// RUNWAY HEADING
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 19, HUD_RWY_HDG, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 19, HUD_RWY_HDG, 31 );
		// AIRSPEED REFERENCE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 20, HUD_EAS_REF, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 20, HUD_EAS_REF, 31 );
		// FLIGHT PATH REFERENCE 1
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 21, HUD_GAMMA_REF1, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 21, HUD_GAMMA_REF1, 31 );
		// X ZERO
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 22, HUD_X_ZERO, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 22, HUD_X_ZERO, 31 );
		// HERROR/H_ERROR
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 23, HUD_HERROR, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 23, HUD_HERROR, 31 );
		// ENERGY UPPER LIMIT
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 24, HUD_ESTURN, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 24, HUD_ESTURN, 31 );
		// ENERGY SHUTTLE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 25, HUD_EOW, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 25, HUD_EOW, 31 );
		// ENERGY LOWER LIMIT
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 26, HUD_EMIN, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 26, HUD_EMIN, 31 );
		// ENERGY NOMINAL
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 27, HUD_ENOM, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 27, HUD_ENOM, 31 );
		// AILERON POSITION
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 28, HUD_AIL_POS, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 28, HUD_AIL_POS, 31 );
		// AILERON LOAD BALANCE INCREMENT
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 29, HUD_AIL_CMD, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 29, HUD_AIL_CMD, 31 );
		// PITCH ADJUSTMENT
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 30, HUD_PITCH_ADJ, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 30, HUD_PITCH_ADJ, 31 );
		// VELOCITY VECTOR FILTER FREQUENCY
		WriteCOMPOOL_AIS( SCP_HUD1_MSG1, 31, HUD_VV_FILT_FREQ, 31 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG1, 31, HUD_VV_FILT_FREQ, 31 );

		// HUD Unique Message 2
		// HUD MSG2 CONTROL WORD
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 1, HUD_CNTL2_L, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 1, HUD_CNTL2_R, 12 );
		// RUNWAY REMAINING TO STOP
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 2, HUD_RW_REM_STP, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 2, HUD_RW_REM_STP, 12 );
		// MINIMUM RUNWAY TO GO
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 3, HUD_RW_TGO_MIN, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 3, HUD_RW_TGO_MIN, 12 );
		// MAXIMUM DECELERATION COMMAND
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 4, HUD_DCL_CMD_MAX, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 4, HUD_DCL_CMD_MAX, 12 );
		// RUNWAY LENGTH
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 5, HUD_RW_LENGTH, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 5, HUD_RW_LENGTH, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 6, HUD_SPARE_CDW_06, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 6, HUD_SPARE_CDW_06, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 7, HUD_SPARE_CDW_07, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 7, HUD_SPARE_CDW_07, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 8, HUD_SPARE_CDW_08, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 8, HUD_SPARE_CDW_08, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 9, HUD_SPARE_CDW_09, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 9, HUD_SPARE_CDW_09, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 10, HUD_SPARE_CDW_10, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 10, HUD_SPARE_CDW_10, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 11, HUD_SPARE_CDW_11, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 11, HUD_SPARE_CDW_11, 12 );
		// SPARE
		WriteCOMPOOL_AIS( SCP_HUD1_MSG2, 12, HUD_SPARE_CDW_12, 12 );
		WriteCOMPOOL_AIS( SCP_HUD2_MSG2, 12, HUD_SPARE_CDW_12, 12 );
		return;
	}

	bool HUD_PROC::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 304:
			case 305:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	bool HUD_PROC::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void HUD_PROC::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}
