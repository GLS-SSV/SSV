#include "LAMP_PROC.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	// HACK correct values for BF_LL and BF_UL are -/+0.5, but changed to -/+1.0 as that is the deadband of the BF cmd hyteresis in the FCS
	constexpr float ADSM_LL = 1.0f;// BODY FLAP LOWER LIMIT - CONF LT (V97U6747C) [MACH]
	constexpr float ADSM_UL = 2.5f;// BODY FLAP UPPER LIMIT - CONF LT (V97U6748C) [MACH]
	constexpr float BF_LL = /*-0.5f*/-1.0f;// BODY FLAP LOWER LIMIT - CONF LT (V97U9092C) [deg]
	constexpr float BF_UL = /*0.5f*/1.0f;// BODY FLAP UPPER LIMIT -CONF LT (V97U9087C) [deg]
	constexpr float CONF_ALT_BF = 5000.0f;// MAX ALTITUDE LIMIT FOR HUD B/F WARNING MESSAGE (V99U7140C) [ft]
	constexpr float CONF_ALT_SB = -100.0f;// (V97U6749C) [ft]
	constexpr float DSB_MIN_U = 15.0f;// SP BK LOWER POSITION LIMIT (V97U0666C) [deg]
	constexpr float GEAR_DOWN_ALT = 300.0f;// ALTITUDE THRESHOLD FOR GEAR LIGHT (V97U6792C) [ft]
	constexpr float GEAR_EAS = 506.3f;// (V99U7141C) [ft/s]
	constexpr float LOAD_FLASH = 64.8f;// G-LOAD LIMIT TO TRIGGER HUD NZ SYMBOL FLASHING (V97U7024C) [ft/s^2]
	constexpr float LOAD_LITE = 72.9f;// (V97U7025C) [ft/s^2]
	constexpr float NAV_ALT = 20000.0f;// (V99U7142C) [ft]
	constexpr float SBM_LL = 0.95f;// SPEEDBRAKE LOWER LIMIT - CONF LT (V97U6924C) [MACH]
	constexpr float SBM_UL = 9.8f;// SPEEDBRAKE UPPER LIMIT - CONF LT (V97U6925C) [MACH]
	constexpr float SB_LIM = 20.0f;// (V97U7026C) [pct]
	constexpr float SB_LL = 14.0f;// SPEEDBRAKE LOWER LIMIT CONF LT (V97U9084C) [deg]
	constexpr float SB_UL = 18.0f;// SPEEDBRAKE UPPER LIMIT -CONF LT (V97U9085C) [deg]


	LAMP_PROC::LAMP_PROC( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "LAMP_PROC" )
	{
		return;
	}

	LAMP_PROC::~LAMP_PROC( void )
	{
		return;
	}

	void LAMP_PROC::OnPostStep( double simt, double simdt, double mjd )
	{
		// inputs
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
		unsigned short AUTOP_IND = ReadCOMPOOL_IS( SCP_AUTOP_IND );
		unsigned short CSSP_IND = ReadCOMPOOL_IS( SCP_CSSP_IND );
		unsigned short GEP_IND = 0;// TODO
		unsigned short AUTORY_IND = ReadCOMPOOL_IS( SCP_AUTORY_IND );
		unsigned short CSSRY_IND = ReadCOMPOOL_IS( SCP_CSSRY_IND );
		unsigned short GERY_IND = 0;// TODO
		unsigned short AUTOSB_IND = ReadCOMPOOL_IS( SCP_AUTOSB_IND );
		unsigned short MNLBF_IND = ReadCOMPOOL_IS( SCP_MNLBF_IND );
		unsigned short AUTOBF_IND = ReadCOMPOOL_IS( SCP_AUTOBF_IND );
		unsigned short MNLSB_CMDR_IND = ReadCOMPOOL_IS( SCP_MNLSB_CMD_IND );
		unsigned short MNLSB_PLT_IND = ReadCOMPOOL_IS( SCP_MNLSB_PLT_IND );
		float LOAD_TOTAL = ReadCOMPOOL_SS( SCP_LOAD_TOTAL );
		float NZ = ReadCOMPOOL_SS( SCP_NZ );
		float MACH = ReadCOMPOOL_SS( SCP_M );
		unsigned short L_PROBE_DEPLOY = 0;// TODO
		unsigned short R_PROBE_DEPLOY = 0;// TODO
		float DSB_ENT_SCHED = 0;// TODO
		float DSBC_AT = ReadCOMPOOL_SS( SCP_DSBC_AT );
		float DSBOFB = ReadCOMPOOL_SS( SCP_DSBFB_DEG );// TODO
		double ALT_WHEELS = ReadCOMPOOL_SD( SCP_ALT_WHEELS );
		unsigned short WOWLON_IND = ReadCOMPOOL_IS( SCP_WOWLON );
		float DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );
		float DDEASC = ReadCOMPOOL_SS( SCP_DDEASC );
		unsigned short MLY_GEAR_NOTUP = ReadCOMPOOL_IS( SCP_MLY_GEAR_NOTUP );
		unsigned short NAV_ALT_FLAG = 0;// TODO
		unsigned short NAV_TAC_FLAG = 0;// TODO
		unsigned short NUM_GPS_INSTALLED = 0;// TODO

		// outputs
		unsigned short LAUTO_PLAMP = 0;
		unsigned short RAUTO_PLAMP = 0;
		unsigned short LCSS_PLAMP = 0;
		unsigned short RCSS_PLAMP = 0;
		unsigned short LGAIN_ENA_PLAMP = 0;
		unsigned short RGAIN_ENA_PLAMP = 0;
		unsigned short LAUTO_RYLAMP = 0;
		unsigned short RAUTO_RYLAMP = 0;
		unsigned short LCSS_RYLAMP = 0;
		unsigned short RCSS_RYLAMP = 0;
		unsigned short LGAIN_ENA_RYLAMP = 0;
		unsigned short RGAIN_ENA_RYLAMP = 0;
		unsigned short LAUTO_SBLAMP = 0;
		unsigned short RAUTO_SBLAMP = 0;
		unsigned short MNLSB_CMDR_O = 0;
		unsigned short MNLSB_PLT_O = 0;
		unsigned short LMNL_BFLAMP = 0;
		unsigned short RMNL_BFLAMP = 0;
		unsigned short LAUTO_BFLAMP = 0;
		unsigned short RAUTO_BFLAMP = 0;
		unsigned short HUD_MODE_PITCH = 0;
		unsigned short HUD_MODE_BANK = 0;
		unsigned short HUD_MODE_SB = 0;
		unsigned short HI_G = 0;
		unsigned short HUD_HI_G = 0;
		unsigned short HI_G_GAX = 0;
		unsigned short PROBE_ALERT = 0;
		unsigned short SPD_BRK_ALERT = 0;
		unsigned short HUD_SPBRK = 0;
		unsigned short HUD_BF = 0;
		unsigned short HUD_GEAR_UP = 0;
		unsigned short NAV_ALT_ALERT = 0;
		unsigned short NAV_TAC_ALERT = 0;

		// Pitch and Roll/Yaw Lamps 320 ms
		if (AUTOP_IND == 1)
		{
			LAUTO_PLAMP = 1;
			RAUTO_PLAMP = 1;
			HUD_MODE_PITCH = 0;
		}
		else
		{
			LAUTO_PLAMP = 0;
			RAUTO_PLAMP = 0;
		}
		if (CSSP_IND == 1)
		{
			LCSS_PLAMP = 1;
			RCSS_PLAMP = 1;
			HUD_MODE_PITCH = 1;
		}
		else
		{
			LCSS_PLAMP = 0;
			RCSS_PLAMP = 0;
		}
		if (GEP_IND == 1)
		{
			LGAIN_ENA_PLAMP = 1;
			RGAIN_ENA_PLAMP = 1;
		}
		else
		{
			LGAIN_ENA_PLAMP = 0;
			RGAIN_ENA_PLAMP = 0;
		}

		if (AUTORY_IND == 1)
		{
			LAUTO_RYLAMP = 1;
			RAUTO_RYLAMP = 1;
			HUD_MODE_BANK = 0;
		}
		else
		{
			LAUTO_RYLAMP = 0;
			RAUTO_RYLAMP = 0;
		}
		if (CSSRY_IND == 1)
		{
			LCSS_RYLAMP = 1;
			RCSS_RYLAMP = 1;
			HUD_MODE_BANK = 1;
		}
		else
		{
			LCSS_RYLAMP = 0;
			RCSS_RYLAMP = 0;
		}
		if (GERY_IND == 1)
		{
			LGAIN_ENA_RYLAMP = 1;
			RGAIN_ENA_RYLAMP = 1;
		}
		else
		{
			LGAIN_ENA_RYLAMP = 0;
			RGAIN_ENA_RYLAMP = 0;
		}

		// Speedbrake Lamps 320 ms
		if (AUTOSB_IND == 1)
		{
			LAUTO_SBLAMP = 1;
			RAUTO_SBLAMP = 1;
			MNLSB_CMDR_O = 0;
			MNLSB_PLT_O = 0;
			HUD_MODE_SB = 0;
		}
		if ((AUTOSB_IND == 0) && (MNLSB_CMDR_IND == 0) && (MNLSB_PLT_IND == 1))
		{
			MNLSB_CMDR_O = 0;
			MNLSB_PLT_O = 1;
			LAUTO_SBLAMP = 0;
			RAUTO_SBLAMP = 0;
			HUD_MODE_SB = 1;
		}
		if ((AUTOSB_IND == 0) && (MNLSB_PLT_IND == 0) && (MNLSB_CMDR_IND == 1))
		{
			MNLSB_CMDR_O = 1;
			MNLSB_PLT_O = 0;
			LAUTO_SBLAMP = 0;
			RAUTO_SBLAMP = 0;
			HUD_MODE_SB = 1;
		}

		// Body Flap Lamps 320 ms
		if (MNLBF_IND == 1)
		{
			LMNL_BFLAMP = 1;
			RMNL_BFLAMP = 1;
		}
		else
		{
			LMNL_BFLAMP = 0;
			RMNL_BFLAMP = 0;
		}
		if (AUTOBF_IND == 1)
		{
			LAUTO_BFLAMP = 1;
			RAUTO_BFLAMP = 1;
		}
		else
		{
			LAUTO_BFLAMP = 0;
			RAUTO_BFLAMP = 0;
		}

		// ENTRY/LANDING EVENT ANNUNCIATION PROCESSING
		// G-LOAD
		if (((MM == 304) && (LOAD_TOTAL >= LOAD_FLASH)) || (((MM == 305) || (MM == 602) || (MM == 603)) && (NZ >= LOAD_FLASH)))
		{
			HI_G = 1;
			HUD_HI_G = 1;
		}
		else
		{
			HI_G = 0;
			HUD_HI_G = 0;
		}
		if (((MM == 304) && (LOAD_TOTAL >= LOAD_LITE)) || (((MM == 305) || (MM == 602) || (MM == 603)) && (NZ >= LOAD_LITE)))
		{
			HI_G_GAX = 1;
		}
		else
		{
			HI_G_GAX = 0;
		}

		// AIR DATA
		if (((ADSM_LL <= MACH) && (MACH <= ADSM_UL)) && ((L_PROBE_DEPLOY == 0) || (R_PROBE_DEPLOY == 0)))
		{
			PROBE_ALERT = 1;
		}
		else
		{
			PROBE_ALERT = 0;
		}

		// SPEED BRAKE
		double SB_COMP = 0.0;
		if ((MM == 304) || (MM == 305))
		{
			SB_COMP = midval( DSB_ENT_SCHED, DSB_MIN_U, 200 );
		}
		else// if ((MM == 602) || (MM == 603))
		{
			SB_COMP = midval( DSBC_AT, DSB_MIN_U, 200 );
		}
		if ((SBM_LL <= MACH) && (MACH <= SBM_UL) && ((DSBOFB - SB_COMP) >= SB_LIM))
		{
			HUD_SPBRK = 1;
			SPD_BRK_ALERT = 1;
		}
		else
		{
			HUD_SPBRK = 0;
			SPD_BRK_ALERT = 0;
		}
		if ((ALT_WHEELS <= CONF_ALT_SB) && (WOWLON_IND == 0))
		{
			if ((SB_LL <= DSBOFB) && (DSBOFB <= SB_UL))
			{
				HUD_SPBRK = 0;
			}
			else
			{
				HUD_SPBRK = 1;
			}
		}
		else
		{
			HUD_SPBRK = 0;
		}

		// BODY FLAP
		if ((ALT_WHEELS <= CONF_ALT_BF) && (WOWLON_IND == 0))
		{
			if ((BF_LL <= DBFOFB) && (DBFOFB <= BF_UL))
			{
				HUD_BF = 0;
			}
			else
			{
				HUD_BF = 1;
			}
		}
		else
		{
			HUD_BF = 0;
		}

		// LANDING GEAR
		if ((ALT_WHEELS <= GEAR_DOWN_ALT) && (DDEASC < GEAR_EAS))
		{
			if (MLY_GEAR_NOTUP == 0)
			{
				HUD_GEAR_UP = 1;
			}
			else
			{
				HUD_GEAR_UP = 0;
			}
		}
		else
		{
			HUD_GEAR_UP = 0;
		}

		// NAV
		if (NAV_ALT_FLAG == 1)
		{
			if (ALT_WHEELS > NAV_ALT)
			{
				NAV_ALT_ALERT = 1;
			}
			else
			{
				NAV_ALT_ALERT = 0;
			}
		}
		if (NAV_TAC_FLAG == 1)
		{
			if ((ALT_WHEELS > NAV_ALT) && (NUM_GPS_INSTALLED < 3))
			{
				NAV_TAC_ALERT = 1;
			}
			else
			{
				NAV_TAC_ALERT = 0;
			}
		}

		// output
		if (LAUTO_PLAMP == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0040 );
		if (RAUTO_PLAMP == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0040 );
		if (LCSS_PLAMP == 1) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0040 );
		if (RCSS_PLAMP == 1) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0040 );
		if (LGAIN_ENA_PLAMP == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0100 );
		if (RGAIN_ENA_PLAMP == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0100 );
		if (LAUTO_RYLAMP == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0080 );
		if (RAUTO_RYLAMP == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0080 );
		if (LCSS_RYLAMP == 1) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0080 );
		if (RCSS_RYLAMP == 1) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0080 );
		if (LGAIN_ENA_RYLAMP == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0200 );
		if (RGAIN_ENA_RYLAMP == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0200 );
		if (LAUTO_SBLAMP == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0020 );
		if (RAUTO_SBLAMP == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0020 );
		if (MNLSB_CMDR_O == 1) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0020 );
		if (MNLSB_PLT_O == 1) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0020 );
		if (LMNL_BFLAMP == 1) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0010 );
		if (RMNL_BFLAMP == 1) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0010 );
		if (LAUTO_BFLAMP == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0010 );
		if (RAUTO_BFLAMP == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0010 );

		// UI
		WriteCOMPOOL_IS( SCP_HI_G, HI_G );

		// GAX
		WriteCOMPOOL_IS( SCP_HI_G_GAX, HI_G_GAX );
		WriteCOMPOOL_IS( SCP_NAV_ALT_ALERT, NAV_ALT_ALERT );
		WriteCOMPOOL_IS( SCP_NAV_TAC_ALERT, NAV_TAC_ALERT );
		WriteCOMPOOL_IS( SCP_PROBE_ALERT, PROBE_ALERT );
		WriteCOMPOOL_IS( SCP_SPD_BRK_ALERT, SPD_BRK_ALERT );

		// HUD
		WriteCOMPOOL_IS( SCP_HUD_BF, HUD_BF );
		WriteCOMPOOL_IS( SCP_HUD_GEAR_UP, HUD_GEAR_UP );
		WriteCOMPOOL_IS( SCP_HUD_HI_G, HUD_HI_G );
		WriteCOMPOOL_IS( SCP_HUD_MODE_BANK, HUD_MODE_BANK );
		WriteCOMPOOL_IS( SCP_HUD_MODE_PITCH, HUD_MODE_PITCH );
		WriteCOMPOOL_IS( SCP_HUD_MODE_SB, HUD_MODE_SB );
		WriteCOMPOOL_IS( SCP_HUD_SPBRK, HUD_SPBRK );
		return;
	}

	bool LAMP_PROC::OnMajorModeChange( unsigned int newMajorMode )
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
}
