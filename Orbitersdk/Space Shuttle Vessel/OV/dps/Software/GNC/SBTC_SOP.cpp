/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/06/28   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/11/15   GLS
2023/06/14   GLS
2025/07/20   GLS
2026/09/18   GLS
********************************************/
#include "SBTC_SOP.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	SBTC_SOP::SBTC_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SBTC_SOP" ),
		SBTCOLDC(0.0f), SBTCOLDP(0.0f), SBEV_LH(0), SBEV_RH(0)
	{
		return;
	}

	SBTC_SOP::~SBTC_SOP( void )
	{
		return;
	}

	void SBTC_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		float DSBTCCC;
		float DSBTCPC;

		// in
		unsigned short MM_CODE_102 = ReadCOMPOOL_IS( SCP_MM_CODE_102 );
		unsigned short MM_CODE_103 = ReadCOMPOOL_IS( SCP_MM_CODE_103 );
		unsigned short MM_CODE_601 = ReadCOMPOOL_IS( SCP_MM_CODE_601 );
		float DSBTCC = ReadCOMPOOL_SS( SCP_DSBTCC );
		float DSBTCP = ReadCOMPOOL_SS( SCP_DSBTCP );
		unsigned short SBEV_LH_SEL = ReadCOMPOOL_IS( SCP_SBEV_LH_SEL );
		unsigned short SBEV_RH_SEL = ReadCOMPOOL_IS( SCP_SBEV_RH_SEL );
		unsigned short L_SBTC_DG = ReadCOMPOOL_IS( SCP_L_SBTC_DG );
		unsigned short R_SBTC_DG = ReadCOMPOOL_IS( SCP_R_SBTC_DG );

		SBTC_COMP( DSBTCC, DSBTCP, DSBTCCC, DSBTCPC );

		SBTC_STA_SEL( SBEV_RH_SEL, SBEV_LH_SEL, L_SBTC_DG, R_SBTC_DG, DSBTCCC, DSBTCPC );

		if ((MM_CODE_102 == 1) || (MM_CODE_103 == 1) || (MM_CODE_601 == 1)) SBTC_THROT_PROC( SBEV_RH_SEL, R_SBTC_DG, DSBTCPC );
		return;
	}

	bool SBTC_SOP::OnParseLine( const char* keyword, const char* value )
	{
		// TODO
		return false;
	}

	void SBTC_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		// TODO
		return;
	}

	void SBTC_SOP::SBTC_COMP( const float DSBTCC, const float DSBTCP, float& DSBTCCC, float& DSBTCPC )
	{
		// left SBTC
		DSBTCCC = (DSBTCC * ReadCOMPOOL_SS( SCP_CSBTCC )) + ReadCOMPOOL_SS( SCP_KSBTCC );

		// right SBTC
		DSBTCPC = (DSBTCP * ReadCOMPOOL_SS( SCP_CSBTCP )) + ReadCOMPOOL_SS( SCP_KSBTCP );
		return;
	}

	void SBTC_SOP::SBTC_STA_SEL( const unsigned short SBEV_RH_SEL, const unsigned short SBEV_LH_SEL, const unsigned short L_SBTC_DG, const unsigned short R_SBTC_DG, float& DSBTCCC, float& DSBTCPC )
	{
		// HACK reset takeover indications to AerojetDAP, and not using the internal values, which are latched for the DSBMAN output
		WriteCOMPOOL_IS( SCP_SBEV_LH, 0 );
		WriteCOMPOOL_IS( SCP_SBEV_RH, 0 );

		// PLT SBTC T/O
		if (SBEV_RH_SEL)
		{
			SBEV_LH = 0;
			SBEV_RH = 1;
			WriteCOMPOOL_IS( SCP_SBEV_LH, 0 );
			WriteCOMPOOL_IS( SCP_SBEV_RH, 1 );
		}

		// CMDR SBTC T/O
		if (SBEV_LH_SEL)
		{
			SBEV_LH = 1;
			SBEV_RH = 0;
			WriteCOMPOOL_IS( SCP_SBEV_LH, 1 );
			WriteCOMPOOL_IS( SCP_SBEV_RH, 0 );
		}

		// data good checks
		if (L_SBTC_DG)
		{
			SBTCOLDC = DSBTCCC;
		}
		else
		{
			DSBTCCC = SBTCOLDC;
		}
		if (R_SBTC_DG)
		{
			SBTCOLDP = DSBTCPC;
		}
		else
		{
			DSBTCPC = SBTCOLDP;
		}

		// station select
		WriteCOMPOOL_SS( SCP_DSBMAN, (SBEV_LH * DSBTCCC) + (SBEV_RH * DSBTCPC) );
		return;
	}

	void SBTC_SOP::SBTC_THROT_PROC( const unsigned short SBEV_RH_SEL, const unsigned short R_SBTC_DG, const float DSBTCPC )
	{
		unsigned short KMAX = ReadCOMPOOL_IS( SCP_KMAX );
		unsigned short KMIN = ReadCOMPOOL_IS( SCP_KMIN );
		unsigned short SBTHROT = KMAX;

		if ((SBEV_RH_SEL == 1) || (ReadCOMPOOL_IS( SCP_MNLSB_PLT_O ) == 1))
		{
			// compute SBTHROT and limit
			SBTHROT = static_cast<unsigned short>(midval( KMIN, Round( KMAX - ((DSBTCPC + 0.582) * ReadCOMPOOL_SS( SCP_DTHROT_PER_DEG )) ), KMAX ));
		}

		if (ReadCOMPOOL_IS( SCP_S_MAN_THROT ) == 0)
		{
			// reconfigure lamps for AUTO mode
			WriteCOMPOOL_IS( SCP_LAUTO_SBLAMP, 1 );
			WriteCOMPOOL_IS( SCP_RAUTO_SBLAMP, 1 );
			WriteCOMPOOL_IS( SCP_MNLSB_CMDR_O, 0 );
			WriteCOMPOOL_IS( SCP_MNLSB_PLT_O, 0 );
		}
		else
		{
			// reconfigure lamps for MANUAL mode
			WriteCOMPOOL_IS( SCP_LAUTO_SBLAMP, 0 );
			WriteCOMPOOL_IS( SCP_RAUTO_SBLAMP, 0 );
			WriteCOMPOOL_IS( SCP_MNLSB_CMDR_O, 0 );
			//WriteCOMPOOL_IS( SCP_MNLSB_PLT_O, 1 );// HACK don't turn on light or logic below will go "manual" before throttle match
		}

		if ((ReadCOMPOOL_IS( SCP_MNLSB_PLT_O ) == 1) && (R_SBTC_DG))
		{
			// update K_CMD
			WriteCOMPOOL_IS( SCP_K_CMD, SBTHROT );
		}

		if ((SBEV_RH_SEL == 1) && (ReadCOMPOOL_IS( SCP_MNLSB_PLT_O ) == 0))
		{
			// set all SBTC AUTO/MAN lamp discretes to OFF
			WriteCOMPOOL_IS( SCP_LAUTO_SBLAMP, 0 );
			WriteCOMPOOL_IS( SCP_RAUTO_SBLAMP, 0 );
			WriteCOMPOOL_IS( SCP_MNLSB_CMDR_O, 0 );
			WriteCOMPOOL_IS( SCP_MNLSB_PLT_O, 0 );

			WriteCOMPOOL_IS( SCP_S_MAN_THROT, 1 );

			unsigned short K_CMD = ReadCOMPOOL_IS( SCP_K_CMD );
			if ((SBEV_RH_SEL) && (fabs( SBTHROT - K_CMD ) < ReadCOMPOOL_IS( SCP_EPS_THROT )))
			{
				WriteCOMPOOL_IS( SCP_MNLSB_PLT_O, 1 );
			}
		}
		else if ((SBEV_RH_SEL == 0) && (ReadCOMPOOL_IS( SCP_MNLSB_PLT_O ) == 0))// HACK return to auto
		{
			WriteCOMPOOL_IS( SCP_S_MAN_THROT, 0 );
		}

		if ((ReadCOMPOOL_IS( SCP_AUTOSB ) == 1) && (SBEV_RH_SEL == 0))
		{
			// reconfigure lamps for AUTO mode
			WriteCOMPOOL_IS( SCP_LAUTO_SBLAMP, 1 );
			WriteCOMPOOL_IS( SCP_RAUTO_SBLAMP, 1 );
			WriteCOMPOOL_IS( SCP_MNLSB_CMDR_O, 0 );
			WriteCOMPOOL_IS( SCP_MNLSB_PLT_O, 0 );

			WriteCOMPOOL_IS( SCP_S_MAN_THROT, 0 );
		}

		// output
		if (ReadCOMPOOL_IS( SCP_LAUTO_SBLAMP ) == 1) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0400 );
		else WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) & ~0x0400 );
		if (ReadCOMPOOL_IS( SCP_RAUTO_SBLAMP ) == 1) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0400 );
		else WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) & ~0x0400 );
		if (ReadCOMPOOL_IS( SCP_MNLSB_PLT_O ) == 1) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0400 );
		else WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) & ~0x0400 );
		return;
	}
}
