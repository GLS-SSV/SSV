/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/06/18   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/07/31   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/02/14   GLS
2022/03/24   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/08/23   GLS
2022/08/27   GLS
2022/09/14   GLS
2022/10/28   GLS
2022/11/09   GLS
2022/11/15   GLS
2022/11/16   GLS
2022/12/01   indy91
2022/12/23   GLS
2023/01/02   GLS
2023/06/14   GLS
2024/07/06   GLS
2026/09/18   GLS
********************************************/
#include "GNCDisplays.h"
#include "../CRT_Interface.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	GNCDisplays::GNCDisplays( SimpleGPCSystem* _gpc ):GeneralDisplays( _gpc, "GNCDisplays" )
	{
		return;
	}

	GNCDisplays::~GNCDisplays()
	{
		return;
	}

	void GNCDisplays::Paint( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 18:// GNC SYS SUMM 1
				OnPaint_DISP18( crt );
				break;
			case 19:// GNC SYS SUMM 2
				OnPaint_DISP19( crt );
				break;
			case 20:// DAP CONFIG
				OnPaint_DAPCONFIG( crt );
				break;
			case 21:// IMU ALIGN
				OnPaint_SPEC21( crt );
				break;
			case 22:// S TRK/COAS_CNTL
				OnPaint_SPEC22( crt );
				break;
			case 23:// RCS
				OnPaint_SPEC23( crt );
				break;
			case 25:// RM ORBIT
				OnPaint_SPEC25( crt );
				break;
			case 33:// REL NAV
				OnPaint_RELNAV( crt );
				break;
			case 34:// ORBIT TGT
				OnPaint_ORBITTGT( crt );
				break;
			case 40:// SENSOR TEST
				OnPaint_SPEC40( crt );
				break;
			case 41:// RGA/ADTA/RCS
				OnPaint_SPEC41( crt );
				break;
			case 42:// SWITCH/SURF
				OnPaint_SPEC42( crt );
				break;
			case 43:// CONTROLLERS
				OnPaint_SPEC43( crt );
				break;
			case 44:// SWITCHES
				OnPaint_SPEC44( crt );
				break;
			case 45:// NWS CHECK
				OnPaint_SPEC45( crt );
				break;
			case 50:// HORIZ SIT
				OnPaint_SPEC50( crt );
				break;
			case 51:// OVERRIDE
				OnPaint_SPEC51( crt );
				break;
			case 53:// CONTROLS
				OnPaint_SPEC53( crt );
				break;
			case 55:// GPS STATUS
				OnPaint_SPEC55( crt );
				break;
			case 112:// GPC/BTU I/F
				OnPaint_SPEC112( crt );
				break;
			case 113:// ACTUATOR CONTROL
				OnPaint_SPEC113( crt );
				break;
			////
			case 1011:// XXXXXX TRAJ 1
			case 1021:
				OnPaint_XXXXXXTRAJ1( crt );
				break;
			case 1031:// XXXXXX TRAJ 2
				OnPaint_XXXXXXTRAJ2( crt );
				break;
			case 1041:// XXXXX MNVR YYYYY
			case 1051:
			case 1061:
			case 2021:
			case 3011:
			case 3021:
			case 3031:
				OnPaint_XXXXXMNVRYYYYY( crt );
				break;
			case 2011:// UNIV PTG
				OnPaint_UNIVPTG( crt );
				break;
			case 3041:// ENTRY TRAJ
				OnPaint_ENTRYTRAJ( crt );
				break;
			case 3051:// VERT SIT
			case 6021:
			case 6031:
				OnPaint_VERTSIT( crt );
				break;
			case 6011:// RTLS TRAJ 2
				OnPaint_RTLSTRAJ2( crt );
				break;
			case 8011:// FCS/DED DIS C/O
				OnPaint_FCSDEDDISCO( crt );
				break;
			default:
				break;
		}
		return;
	}

	void GNCDisplays::PaintBackground( CRT_Interface* crt, unsigned short page ) const
	{
		switch (page)
		{
			case 18:// GNC SYS SUMM 1
				BackgroundData_DISP18( crt );
				break;
			case 19:// GNC SYS SUMM 2
				BackgroundData_DISP19( crt );
				break;
			case 20:// DAP CONFIG
				BackgroundData_DAPCONFIG( crt );
				break;
			case 21:// IMU ALIGN
				BackgroundData_SPEC21( crt );
				break;
			case 22:// S TRK/COAS_CNTL
				BackgroundData_SPEC22( crt );
				break;
			case 23:// RCS
				BackgroundData_SPEC23( crt );
				break;
			case 25:// RM ORBIT
				BackgroundData_SPEC25( crt );
				break;
			case 33:// REL NAV
				BackgroundData_RELNAV( crt );
				break;
			case 34:// ORBIT TGT
				BackgroundData_ORBITTGT( crt );
				break;
			case 40:// SENSOR TEST
				BackgroundData_SPEC40( crt );
				break;
			case 41:// RGA/ADTA/RCS
				BackgroundData_SPEC41( crt );
				break;
			case 42:// SWITCH/SURF
				BackgroundData_SPEC42( crt );
				break;
			case 43:// CONTROLLERS
				BackgroundData_SPEC43( crt );
				break;
			case 44:// SWITCHES
				BackgroundData_SPEC44( crt );
				break;
			case 45:// NWS CHECK
				BackgroundData_SPEC45( crt );
				break;
			case 50:// HORIZ SIT
				BackgroundData_SPEC50( crt );
				break;
			case 51:// OVERRIDE
				BackgroundData_SPEC51( crt );
				break;
			case 53:// CONTROLS
				BackgroundData_SPEC53( crt );
				break;
			case 55:// GPS STATUS
				BackgroundData_SPEC55( crt );
				break;
			case 112:// GPC/BTU I/F
				BackgroundData_SPEC112( crt );
				break;
			case 113:// ACTUATOR CONTROL
				BackgroundData_SPEC113( crt );
				break;
			////
			case 1011:// XXXXXX TRAJ 1
			case 1021:
				BackgroundData_XXXXXXTRAJ1( crt );
				break;
			case 1031:// XXXXXX TRAJ 2
				BackgroundData_XXXXXXTRAJ2( crt );
				break;
			case 1041:// XXXXX MNVR YYYYY
			case 1051:
			case 1061:
			case 2021:
			case 3011:
			case 3021:
			case 3031:
				BackgroundData_XXXXXMNVRYYYYY( crt );
				break;
			case 2011:// UNIV PTG
				BackgroundData_UNIVPTG( crt );
				break;
			case 3041:// ENTRY TRAJ
				BackgroundData_ENTRYTRAJ( crt );
				break;
			case 3051:// VERT SIT
			case 6021:
			case 6031:
				BackgroundData_VERTSIT( crt );
				break;
			case 6011:// RTLS TRAJ 2
				BackgroundData_RTLSTRAJ2( crt );
				break;
			case 8011:// FCS/DED DIS C/O
				BackgroundData_FCSDEDDISCO( crt );
				break;
			default:
				break;
		}
		return;
	}

	void GNCDisplays::OnPaint_DISP18( CRT_Interface* crt ) const
	{
		char cbuf[64];

		// TODO RCS

		// SURF
		if ((ReadCOMPOOL_IS( SCP_OPS3_INDICATOR ) == 1) || (ReadCOMPOOL_IS( SCP_OPS_6_INDICATOR ) == 1))
		{
			double tmp = 0;
			char pos;

			double LOB = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
			double LIB = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
			double RIB = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
			double ROB = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
			double DAILERON = ReadCOMPOOL_SS( SCP_DAILERON );
			double DRFB = ReadCOMPOOL_SS( SCP_DRFB );
			double DSBFB = ReadCOMPOOL_SS( SCP_DSBOFB );
			double BFP_CRT = ReadCOMPOOL_SS( SCP_BFP_CRT );

			if (LOB > 0.0) pos = 'D';
			else if (LOB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( LOB ), tmp );
			crt->TextGrid( 23, 5, cbuf );
			ReadCOMPOOL_C( SCP_LOB_HI_LO_SATURATION_STATUS, cbuf, 1 );
			cbuf[1] = 0;
			crt->TextGrid( 28, 5, cbuf, crt->DEUATT_OVERBRIGHT );

			if (LIB > 0.0) pos = 'D';
			else if (LIB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( LIB ), tmp );
			crt->TextGrid( 23, 6, cbuf );
			ReadCOMPOOL_C( SCP_LIB_HI_LO_SATURATION_STATUS, cbuf, 1 );
			cbuf[1] = 0;
			crt->TextGrid( 28, 6, cbuf, crt->DEUATT_OVERBRIGHT );

			if (RIB > 0.0) pos = 'D';
			else if (RIB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( RIB ), tmp );
			crt->TextGrid( 23, 7, cbuf );
			ReadCOMPOOL_C( SCP_RIB_HI_LO_SATURATION_STATUS, cbuf, 1 );
			cbuf[1] = 0;
			crt->TextGrid( 28, 7, cbuf, crt->DEUATT_OVERBRIGHT );

			if (ROB > 0.0) pos = 'D';
			else if (ROB < 0.0) pos = 'U';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f  %2.0f", pos, fabs( ROB ), tmp );
			crt->TextGrid( 23, 8, cbuf );
			ReadCOMPOOL_C( SCP_ROB_HI_LO_SATURATION_STATUS, cbuf, 1 );
			cbuf[1] = 0;
			crt->TextGrid( 28, 8, cbuf, crt->DEUATT_OVERBRIGHT );

			if (DAILERON > 0.0) pos = 'R';
			else if (DAILERON < 0.0) pos = 'L';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f", pos, fabs( DAILERON ) );
			crt->TextGrid( 23, 9, cbuf );

			if (DRFB > 0.0) pos = 'L';
			else if (DRFB < 0.0) pos = 'R';
			else pos = ' ';
			sprintf_s( cbuf, 64, "%c%4.1f", pos, fabs( DRFB ) );
			crt->TextGrid( 23, 10, cbuf );

			sprintf_s( cbuf, 64, "%5.1f", fabs( DSBFB ) );
			crt->TextGrid( 23, 11, cbuf );

			sprintf_s( cbuf, 64, "%5.1f", range( 0.0, BFP_CRT, 100.0 ) );
			crt->TextGrid( 23, 12, cbuf );
		}

		// DPS
		unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
		bool commfaultFF1 = (COMMFAULT_WORD_1 & 0x00000001) != 0;
		bool commfaultFF2 = (COMMFAULT_WORD_1 & 0x00000002) != 0;
		bool commfaultFF3 = (COMMFAULT_WORD_1 & 0x00000004) != 0;
		bool commfaultFF4 = (COMMFAULT_WORD_1 & 0x00000008) != 0;
		bool commfaultFA1 = (COMMFAULT_WORD_1 & 0x00001000) != 0;
		bool commfaultFA2 = (COMMFAULT_WORD_1 & 0x00002000) != 0;
		bool commfaultFA3 = (COMMFAULT_WORD_1 & 0x00004000) != 0;
		bool commfaultFA4 = (COMMFAULT_WORD_1 & 0x00008000) != 0;
		if (commfaultFF1) crt->TextGrid( 42, 6, "\x1D", crt->DEUATT_OVERBRIGHT );// FF1
		if (commfaultFF2) crt->TextGrid( 44, 6, "\x1D", crt->DEUATT_OVERBRIGHT );// FF2
		if (commfaultFF3) crt->TextGrid( 46, 6, "\x1D", crt->DEUATT_OVERBRIGHT );// FF3
		if (commfaultFF4) crt->TextGrid( 48, 6, "\x1D", crt->DEUATT_OVERBRIGHT );// FF4
		if (commfaultFA1) crt->TextGrid( 42, 7, "\x1D", crt->DEUATT_OVERBRIGHT );// FA1
		if (commfaultFA2) crt->TextGrid( 44, 7, "\x1D", crt->DEUATT_OVERBRIGHT );// FA2
		if (commfaultFA3) crt->TextGrid( 46, 7, "\x1D", crt->DEUATT_OVERBRIGHT );// FA3
		if (commfaultFA4) crt->TextGrid( 48, 7, "\x1D", crt->DEUATT_OVERBRIGHT );// FA4

		// TODO FCS

		// TODO NAV

		// CNTLR
		cbuf[1] = 0;
		ReadCOMPOOL_C( SCP_L_RHC_CH_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 17, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_L_RHC_CH_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 17, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_L_RHC_CH_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 17, cbuf, crt->DEUATT_OVERBRIGHT );


		ReadCOMPOOL_C( SCP_R_RHC_CH_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 18, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_R_RHC_CH_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 18, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_R_RHC_CH_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 18, cbuf, crt->DEUATT_OVERBRIGHT );


		ReadCOMPOOL_C( SCP_AFT_RHC_CH_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 19, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_AFT_RHC_CH_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 19, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_AFT_RHC_CH_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 19, cbuf, crt->DEUATT_OVERBRIGHT );


		ReadCOMPOOL_C( SCP_FWD_THC_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 20, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_FWD_THC_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 20, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_FWD_THC_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 20, cbuf, crt->DEUATT_OVERBRIGHT );


		ReadCOMPOOL_C( SCP_AFT_THC_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 21, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_AFT_THC_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 21, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_AFT_THC_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 21, cbuf, crt->DEUATT_OVERBRIGHT );


		ReadCOMPOOL_C( SCP_L_SBTC_CH_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 22, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_L_SBTC_CH_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 22, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_L_SBTC_CH_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 22, cbuf, crt->DEUATT_OVERBRIGHT );


		ReadCOMPOOL_C( SCP_R_SBTC_CH_1_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 24, 23, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_R_SBTC_CH_2_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 26, 23, cbuf, crt->DEUATT_OVERBRIGHT );

		ReadCOMPOOL_C( SCP_R_SBTC_CH_3_IO_FAIL_STATUS, cbuf, 1 );
		crt->TextGrid( 28, 23, cbuf, crt->DEUATT_OVERBRIGHT );
		return;
	}

	void GNCDisplays::OnPaint_DISP19( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void GNCDisplays::OnPaint_DAPCONFIG( CRT_Interface* crt ) const
	{
		char *strings[3] = {" ALL", "NOSE", "TAIL"};
		char cbuf[255];

		crt->TextGrid( 12, 3, "DAP A" );
		crt->TextGrid( 23, 3, "DAP B" );

		crt->TextGrid( 5, 3, "PRI" );
		crt->TextGrid( 5, 12, "ALT" );
		crt->TextGrid( 5, 18, "VERN" );

		crt->TextGrid( 17, 3, "01" );
		crt->TextGrid( 28, 3, "02" );

		/*int lim[3] = {3, 5, 5};
		int i, n;
		int edit = 2;// temporary
		for (n = 1, i = 0; n <= lim[edit]; n += 2, i++)
		{
			sprintf_s( cbuf, 255, "%.4f", DAPConfiguration[i].PRI_ROT_RATE );
			crt->TextGrid( 13 + (11 * i), 4, cbuf );
			sprintf_s( cbuf, 255, "%05.2f", DAPConfiguration[i].PRI_ATT_DB );
			crt->TextGrid( 14 + (11 * i), 5, cbuf );
			sprintf_s( cbuf, 255, "%.2f", DAPConfiguration[i].PRI_RATE_DB );
			crt->TextGrid( 15 + (11 * i), 6, cbuf );
			sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].PRI_ROT_PLS );
			crt->TextGrid( 14 + (11 * i), 7, cbuf );
			sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].PRI_COMP );
			crt->TextGrid( 14 + (11 * i), 8, cbuf );
			crt->TextGrid( 14 + (11 * i), 8, " " );// HACK
			crt->TextGrid( 15 + (11 * i), 9, strings[DAPConfiguration[i].PRI_P_OPTION] );
			crt->TextGrid( 15 + (11 * i), 10, strings[DAPConfiguration[i].PRI_Y_OPTION] );
			sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].PRI_TRAN_PLS );
			crt->TextGrid( 14 + (11 * i), 11, cbuf );

			sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].ALT_RATE_DB );
			crt->TextGrid( 14 + (11 * i), 13, cbuf );
			crt->TextGrid( 15 + (11 * i), 14, strings[DAPConfiguration[i].ALT_JET_OPT] );
			sprintf_s( cbuf, 255, "%d", DAPConfiguration[i].ALT_JETS );
			crt->TextGrid( 18 + (11 * i), 15, cbuf );
			sprintf_s( cbuf, 255, "%.2f", DAPConfiguration[i].ALT_ON_TIME );
			crt->TextGrid( 15 + (11 * i), 16, cbuf );
			sprintf_s( cbuf, 255, "%05.2f", DAPConfiguration[i].ALT_DELAY );
			crt->TextGrid( 14 + (11 * i), 17, cbuf );

			sprintf_s( cbuf, 255, "%.4f", DAPConfiguration[i].VERN_ROT_RATE );
			crt->TextGrid( 13 + (11 * i), 19, cbuf );
			sprintf_s( cbuf, 255, "%06.3f", DAPConfiguration[i].VERN_ATT_DB );
			crt->TextGrid( 13 + (11 * i), 20, cbuf );
			sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].VERN_RATE_DB );
			crt->TextGrid( 14 + (11 * i), 21, cbuf );
			crt->TextGrid( 14 + (11 * i), 21, " " );// HACK
			sprintf_s( cbuf, 255, "%05.3f", DAPConfiguration[i].VERN_ROT_PLS );
			crt->TextGrid( 14 + (11 * i), 22, cbuf );
			sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].VERN_COMP );
			crt->TextGrid( 14 + (11 * i), 23, cbuf );
			crt->TextGrid( 14 + (11 * i), 23, " " );// HACK
			sprintf_s( cbuf, 255, "%d", DAPConfiguration[i].VERN_CNTL_ACC );
			crt->TextGrid( 18 + (11 * i), 24, cbuf );
		}*/
		return;
	}

	void GNCDisplays::OnPaint_SPEC21( CRT_Interface* crt ) const
	{
		return;
	}

	void GNCDisplays::OnPaint_SPEC22( CRT_Interface* crt ) const
	{
		return;
	}

	void GNCDisplays::OnPaint_SPEC23( CRT_Interface* crt ) const
	{
		return;
	}

	void GNCDisplays::OnPaint_SPEC25( CRT_Interface* crt ) const
	{
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF1_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM15_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );

		bool FWD_THC_POS_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_X_OUTPUT_A, FWD_THC_NEG_X_OUTPUT_A, 8, 9 );
		bool FWD_THC_POS_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_X_OUTPUT_B, FWD_THC_NEG_X_OUTPUT_B, 8, 10 );
		bool FWD_THC_POS_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0080) != 0);
		bool FWD_THC_NEG_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_X_OUTPUT_C, FWD_THC_NEG_X_OUTPUT_C, 8, 11 );
		bool FWD_THC_POS_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Y_OUTPUT_A, FWD_THC_NEG_Y_OUTPUT_A, 11, 9 );
		bool FWD_THC_POS_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Y_OUTPUT_B, FWD_THC_NEG_Y_OUTPUT_B, 11, 10 );
		bool FWD_THC_POS_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0200) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Y_OUTPUT_C, FWD_THC_NEG_Y_OUTPUT_C, 11, 11 );
		bool FWD_THC_POS_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Z_OUTPUT_A, FWD_THC_NEG_Z_OUTPUT_A, 14, 9 );
		bool FWD_THC_POS_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Z_OUTPUT_B, FWD_THC_NEG_Z_OUTPUT_B, 14, 10 );
		bool FWD_THC_POS_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0800) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Z_OUTPUT_C, FWD_THC_NEG_Z_OUTPUT_C, 14, 11 );

		bool AFT_THC_POS_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_X_OUTPUT_A, AFT_THC_NEG_X_OUTPUT_A, 8, 13 );
		bool AFT_THC_POS_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_X_OUTPUT_B, AFT_THC_NEG_X_OUTPUT_B, 8, 14 );
		bool AFT_THC_POS_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0080) != 0);
		bool AFT_THC_NEG_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0100) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_X_OUTPUT_C, AFT_THC_NEG_X_OUTPUT_C, 8, 15 );
		bool AFT_THC_POS_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Y_OUTPUT_A, AFT_THC_NEG_Y_OUTPUT_A, 11, 13 );
		bool AFT_THC_POS_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Y_OUTPUT_B, AFT_THC_NEG_Y_OUTPUT_B, 11, 14 );
		bool AFT_THC_POS_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0200) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0400) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Y_OUTPUT_C, AFT_THC_NEG_Y_OUTPUT_C, 11, 15 );
		bool AFT_THC_POS_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Z_OUTPUT_A, AFT_THC_NEG_Z_OUTPUT_A, 14, 13 );
		bool AFT_THC_POS_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Z_OUTPUT_B, AFT_THC_NEG_Z_OUTPUT_B, 14, 14 );
		bool AFT_THC_POS_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0800) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x1000) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Z_OUTPUT_C, AFT_THC_NEG_Z_OUTPUT_C, 14, 15 );


		/*SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[3].GetVoltage(), 28, 9 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[4].GetVoltage(), 28, 10 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[5].GetVoltage(), 28, 11 );
		SPEC25_SPEC43_printRHC_P( crt, LeftRHC[0].GetVoltage(), 33, 9 );
		SPEC25_SPEC43_printRHC_P( crt, LeftRHC[1].GetVoltage(), 33, 10 );
		SPEC25_SPEC43_printRHC_P( crt, LeftRHC[2].GetVoltage(), 33, 11 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[6].GetVoltage(), 38, 9 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[7].GetVoltage(), 38, 10 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[8].GetVoltage(), 38, 11 );

		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[3].GetVoltage(), 28, 13 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[4].GetVoltage(), 28, 14 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[5].GetVoltage(), 28, 15 );
		SPEC25_SPEC43_printRHC_P( crt, RightRHC[0].GetVoltage(), 33, 13 );
		SPEC25_SPEC43_printRHC_P( crt, RightRHC[1].GetVoltage(), 33, 14 );
		SPEC25_SPEC43_printRHC_P( crt, RightRHC[2].GetVoltage(), 33, 15 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[6].GetVoltage(), 38, 13 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[7].GetVoltage(), 38, 14 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[8].GetVoltage(), 38, 15 );

		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[3].GetVoltage(), 28, 17 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[4].GetVoltage(), 28, 18 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[5].GetVoltage(), 28, 19 );
		SPEC25_SPEC43_printRHC_P( crt, AftRHC[0].GetVoltage(), 33, 17 );
		SPEC25_SPEC43_printRHC_P( crt, AftRHC[1].GetVoltage(), 33, 18 );
		SPEC25_SPEC43_printRHC_P( crt, AftRHC[2].GetVoltage(), 33, 19 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[6].GetVoltage(), 38, 17 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[7].GetVoltage(), 38, 18 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[8].GetVoltage(), 38, 19 );*/

		unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
		bool commfaultFF1 = (COMMFAULT_WORD_1 & 0x00000001) != 0;
		bool commfaultFF2 = (COMMFAULT_WORD_1 & 0x00000002) != 0;
		bool commfaultFF3 = (COMMFAULT_WORD_1 & 0x00000004) != 0;
		if (commfaultFF1) crt->TextGrid( 9, 9, "M", crt->DEUATT_OVERBRIGHT );// THC L 1 X
		if (commfaultFF1) crt->TextGrid( 12, 9, "M", crt->DEUATT_OVERBRIGHT );// THC L 1 Y
		if (commfaultFF1) crt->TextGrid( 15, 9, "M", crt->DEUATT_OVERBRIGHT );// THC L 1 Z
		if (commfaultFF2) crt->TextGrid( 9, 10, "M", crt->DEUATT_OVERBRIGHT );// THC L 2 X
		if (commfaultFF2) crt->TextGrid( 12, 10, "M", crt->DEUATT_OVERBRIGHT );// THC L 2 Y
		if (commfaultFF2) crt->TextGrid( 15, 10, "M", crt->DEUATT_OVERBRIGHT );// THC L 2 Z
		if (commfaultFF3) crt->TextGrid( 9, 11, "M", crt->DEUATT_OVERBRIGHT );// THC L 3 X
		if (commfaultFF3) crt->TextGrid( 12, 11, "M", crt->DEUATT_OVERBRIGHT );// THC L 3 Y
		if (commfaultFF3) crt->TextGrid( 15, 11, "M", crt->DEUATT_OVERBRIGHT );// THC L 3 Z
		if (commfaultFF1) crt->TextGrid( 9, 13, "M", crt->DEUATT_OVERBRIGHT );// THC A 1 X
		if (commfaultFF1) crt->TextGrid( 12, 13, "M", crt->DEUATT_OVERBRIGHT );// THC A 1 Y
		if (commfaultFF1) crt->TextGrid( 15, 13, "M", crt->DEUATT_OVERBRIGHT );// THC A 1 Z
		if (commfaultFF2) crt->TextGrid( 9, 14, "M", crt->DEUATT_OVERBRIGHT );// THC A 2 X
		if (commfaultFF2) crt->TextGrid( 12, 14, "M", crt->DEUATT_OVERBRIGHT );// THC A 2 Y
		if (commfaultFF2) crt->TextGrid( 15, 14, "M", crt->DEUATT_OVERBRIGHT );// THC A 2 Z
		if (commfaultFF3) crt->TextGrid( 9, 15, "M", crt->DEUATT_OVERBRIGHT );// THC A 3 X
		if (commfaultFF3) crt->TextGrid( 12, 15, "M", crt->DEUATT_OVERBRIGHT );// THC A 3 Y
		if (commfaultFF3) crt->TextGrid( 15, 15, "M", crt->DEUATT_OVERBRIGHT );// THC A 3 Z
		return;
	}

	void GNCDisplays::OnPaint_RELNAV( CRT_Interface* crt ) const
	{
		if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1)
		{
			crt->TextGrid( 17, 2, "*" );

			/*char cbuf[255];

			//TBD: Anything that is blank with rendezvous navigation off
			crt->NumberGrid( 8, 7, RNG_CUR_DISP, 4, 3 );

			crt->NumberSignGrid( 8, 8, RD_CUR, 4, 2, '+', '-' );

			crt->NumberGrid( 10, 9, THETA_CUR, 3, 2 );

			crt->NumberSignGrid( 10, 10, Y_CUR_DISP, 2, 2, '+', '-' );

			crt->NumberSignGrid( 10, 11, YD_CUR, 3, 1, '+', '-' );

			int TIMER[3];
			int T_NODE_SEC_INT;

			T_NODE_SEC_INT = static_cast<int>(T_NODE_SEC);
			TIMER[0] = T_NODE_SEC_INT / 3600;
			TIMER[1] = (T_NODE_SEC_INT - TIMER[0] * 3600) / 60;
			TIMER[2] = T_NODE_SEC_INT - TIMER[0] * 3600 - TIMER[1] * 60;
			sprintf_s(cbuf, 51, "%02d:%02d:%02d", abs(TIMER[0]), abs(TIMER[1]), abs(TIMER[2]));
			crt->TextGrid( 8, 12, cbuf );*/
		}
		return;
	}

	void GNCDisplays::OnPaint_ORBITTGT( CRT_Interface* crt ) const
	{
		/*char cbuf[51];

		if (PROX_PAST_STATUS == false && T_MAN > 0.0)
		{
			int timeDiff = max(0, static_cast<int>(DISP_TMAN_TIME - STS()->GetMET() + 1));
			int TIMER[4];

			TIMER[0] = timeDiff / 86400;
			TIMER[1] = (timeDiff - TIMER[0] * 86400) / 3600;
			TIMER[2] = (timeDiff - TIMER[0] * 86400 - TIMER[1] * 3600) / 60;
			TIMER[3] = timeDiff - TIMER[0] * 86400 - TIMER[1] * 3600 - TIMER[2] * 60;
			sprintf_s(cbuf, 51, "%03d/%02d:%02d:%02d", abs(TIMER[0]), abs(TIMER[1]), abs(TIMER[2]), abs(TIMER[3]));
			crt->TextGrid(39, 2, cbuf);
		}

		sprintf_s(cbuf, 51, "%02d", MAN_TGT);
		crt->TextGrid( 2, 4, cbuf );

		if (PROX_PAST_STATUS) crt->TextGrid( 5, 4, "*" );
		sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_TMAN[0], DISP_TMAN[1], DISP_TMAN[2], DISP_TMAN[3]);
		crt->TextGrid( 7, 4, cbuf );

		crt->NumberSignGrid( 21, 4, DISP_DV.x, 3, 1, '+', '-' );
		crt->NumberSignGrid( 29, 4, DISP_DV.y, 2, 1, '+', '-' );
		crt->NumberSignGrid( 36, 4, DISP_DV.z, 2, 1, '+', '-' );
		crt->NumberSignGrid( 43, 4, DISP_DV_MAG, 3, 1, '+', '-' );

		crt->NumberGrid( 39, 5, DSP_MISS, 7, 0 );

		sprintf_s(cbuf, 51, "%02d", PROX_TGT_SET_NO);
		crt->TextGrid( 24, 8, cbuf );

		sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_T1_TIG[0], DISP_T1_TIG[1], DISP_T1_TIG[2], DISP_T1_TIG[3]);
		crt->TextGrid( 14, 9, cbuf );

		crt->NumberGrid( 20, 10, DISP_EL_ANG, 3, 2 );

		crt->NumberSignGrid( 19, 11, DISP_T1_X.x, 3, 2, '+', '-' );
		crt->NumberSignGrid( 19, 12, DISP_T1_X.y, 3, 2, '+', '-' );
		crt->NumberSignGrid( 19, 13, DISP_T1_X.z, 3, 2, '+', '-' );

		crt->NumberSignGrid( 19, 14, DISP_T1_XD.x, 3, 2, '+', '-' );
		crt->NumberSignGrid( 19, 15, DISP_T1_XD.y, 3, 2, '+', '-' );
		crt->NumberSignGrid( 19, 16, DISP_T1_XD.z, 3, 2, '+', '-' );

		sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_T2_TIG[0], DISP_T2_TIG[1], DISP_T2_TIG[2], DISP_T2_TIG[3]);
		crt->TextGrid( 14, 17, cbuf );

		crt->NumberSignGrid( 19, 18, DISP_PROX_DT, 3, 1, '+', '-' );
		crt->NumberSignGrid( 19, 19, DISP_T2_OFF.x, 3, 2, '+', '-' );
		crt->NumberSignGrid( 19, 20, DISP_T2_OFF.y, 3, 2, '+', '-' );
		crt->NumberSignGrid( 19, 21, DISP_T2_OFF.z, 3, 2, '+', '-' );

		sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", PROX_BASE[0], PROX_BASE[1], PROX_BASE[2], PROX_BASE[3]);
		crt->TextGrid( 14, 22, cbuf );


		if (PROX_LOAD_FLASH)
		{
			crt->TextGrid( 38, 9, "LOAD", crt->DEUATT_FLASHING );
		}
		else
		{
			crt->TextGrid( 38, 9, "LOAD" );
		}

		if (PROX_T1_STAR_STATUS) crt->TextGrid( 51, 10, "*" );

		if (PROX_T2_STAR_STATUS) crt->TextGrid( 51, 11, "*" );*/
		return;
	}

	void GNCDisplays::OnPaint_SPEC40( CRT_Interface* crt ) const
	{
		return;
	}

	void GNCDisplays::OnPaint_SPEC41( CRT_Interface* crt ) const
	{
		return;
	}

	void GNCDisplays::OnPaint_SPEC42( CRT_Interface* crt ) const
	{
		unsigned short FF1_IOM4_CH1 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH1_DATA );
		unsigned short FF2_IOM4_CH1 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH1_DATA );
		unsigned short FF3_IOM4_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM4_CH1_DATA );
		unsigned short FF1_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH2_DATA );
		unsigned short FF2_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH2_DATA );
		unsigned short FF3_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF3_IOM4_CH2_DATA );
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF2_IOM12_CH1 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH1_DATA );
		unsigned short FF3_IOM12_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH1_DATA );
		unsigned short FF4_IOM12_CH1 = ReadCOMPOOL_IS( SCP_FF4_IOM12_CH1_DATA );
		unsigned short FF2_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH2_DATA );
		unsigned short FF3_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH2_DATA );
		unsigned short FF4_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF4_IOM12_CH2_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );
		unsigned short FF4_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF4_IOM15_CH0_DATA );

		bool FCS_LH_PITCH_AUTO_MODE_A = (FF1_IOM4_CH1 & 0x0020) != 0;
		if (FCS_LH_PITCH_AUTO_MODE_A) crt->TextGrid( 11, 13, "*" );

		bool FCS_LH_PITCH_AUTO_MODE_B = (FF2_IOM4_CH1 & 0x0020) != 0;
		if (FCS_LH_PITCH_AUTO_MODE_B) crt->TextGrid( 11, 14, "*" );

		bool FCS_LH_PITCH_AUTO_MODE_C = (FF3_IOM4_CH1 & 0x0020) != 0;
		if (FCS_LH_PITCH_AUTO_MODE_C) crt->TextGrid( 11, 15, "*" );

		bool FCS_LH_PITCH_CSS_MODE_A = (FF1_IOM4_CH1 & 0x0010) != 0;
		if (FCS_LH_PITCH_CSS_MODE_A) crt->TextGrid( 15, 13, "*" );

		bool FCS_LH_PITCH_CSS_MODE_B = (FF2_IOM4_CH1 & 0x0010) != 0;
		if (FCS_LH_PITCH_CSS_MODE_B) crt->TextGrid( 15, 14, "*" );

		bool FCS_LH_PITCH_CSS_MODE_C = (FF3_IOM4_CH1 & 0x0010) != 0;
		if (FCS_LH_PITCH_CSS_MODE_C) crt->TextGrid( 15, 15, "*" );

		bool FCS_LH_RY_AUTO_MODE_A = (FF1_IOM4_CH1 & 0x0004) != 0;
		if (FCS_LH_RY_AUTO_MODE_A) crt->TextGrid( 23, 13, "*" );

		bool FCS_LH_RY_AUTO_MODE_B = (FF2_IOM4_CH1 & 0x0004) != 0;
		if (FCS_LH_RY_AUTO_MODE_B) crt->TextGrid( 23, 14, "*" );

		bool FCS_LH_RY_AUTO_MODE_C = (FF3_IOM4_CH1 & 0x0004) != 0;
		if (FCS_LH_RY_AUTO_MODE_C) crt->TextGrid( 23, 15, "*" );

		bool FCS_LH_RY_CSS_MODE_A = (FF1_IOM4_CH1 & 0x0002) != 0;
		if (FCS_LH_RY_CSS_MODE_A) crt->TextGrid( 27, 13, "*" );

		bool FCS_LH_RY_CSS_MODE_B = (FF2_IOM4_CH1 & 0x0002) != 0;
		if (FCS_LH_RY_CSS_MODE_B) crt->TextGrid( 27, 14, "*" );

		bool FCS_LH_RY_CSS_MODE_C = (FF3_IOM4_CH1 & 0x0002) != 0;
		if (FCS_LH_RY_CSS_MODE_C) crt->TextGrid( 27, 15, "*" );

		bool LH_SPD_BK_THROT_AUTO_MAN_A = (FF1_IOM4_CH2 & 0x8000) != 0;
		if (LH_SPD_BK_THROT_AUTO_MAN_A) crt->TextGrid( 36, 13, "*" );

		bool LH_SPD_BK_THROT_AUTO_MAN_B = (FF2_IOM4_CH2 & 0x8000) != 0;
		if (LH_SPD_BK_THROT_AUTO_MAN_B) crt->TextGrid( 36, 14, "*" );

		bool LH_SPD_BK_THROT_AUTO_MAN_C = (FF3_IOM4_CH2 & 0x8000) != 0;
		if (LH_SPD_BK_THROT_AUTO_MAN_C) crt->TextGrid( 36, 15, "*" );

		bool LH_SBTC_TAKEOVER_A = (FF1_IOM6_CH0 & 0x0004) != 0;
		if (LH_SBTC_TAKEOVER_A) crt->TextGrid( 40, 13, "*" );

		bool LH_SBTC_TAKEOVER_B = (FF2_IOM6_CH0 & 0x0004) != 0;
		if (LH_SBTC_TAKEOVER_B) crt->TextGrid( 40, 14, "*" );

		bool LH_SBTC_TAKEOVER_C = (FF3_IOM6_CH0 & 0x0004) != 0;
		if (LH_SBTC_TAKEOVER_C) crt->TextGrid( 40, 15, "*" );

		bool LH_BODY_FLAP_AUTO_MANUAL_A = (FF1_IOM4_CH1 & 0x0001) != 0;
		if (LH_BODY_FLAP_AUTO_MANUAL_A) crt->TextGrid( 45, 13, "*" );

		bool LH_BODY_FLAP_AUTO_MANUAL_B = (FF2_IOM4_CH1 & 0x0001) != 0;
		if (LH_BODY_FLAP_AUTO_MANUAL_B) crt->TextGrid( 45, 14, "*" );

		bool LH_BODY_FLAP_AUTO_MANUAL_C = (FF3_IOM4_CH1 & 0x0001)!= 0;
		if (LH_BODY_FLAP_AUTO_MANUAL_C) crt->TextGrid( 45, 15, "*" );

		bool FCS_RH_PITCH_AUTO_MODE_A = (FF2_IOM12_CH1 & 0x0020) != 0;
		if (FCS_RH_PITCH_AUTO_MODE_A) crt->TextGrid( 11, 16, "*" );

		bool FCS_RH_PITCH_AUTO_MODE_B = (FF3_IOM12_CH1 & 0x0020) != 0;
		if (FCS_RH_PITCH_AUTO_MODE_B) crt->TextGrid( 11, 17, "*" );

		bool FCS_RH_PITCH_AUTO_MODE_C = (FF4_IOM12_CH1 & 0x0020) != 0;
		if (FCS_RH_PITCH_AUTO_MODE_C) crt->TextGrid( 11, 18, "*" );

		bool FCS_RH_PITCH_CSS_MODE_A = (FF2_IOM12_CH1 & 0x0010) != 0;;
		if (FCS_RH_PITCH_CSS_MODE_A) crt->TextGrid( 15, 16, "*" );

		bool FCS_RH_PITCH_CSS_MODE_B = (FF3_IOM12_CH1 & 0x0010) != 0;
		if (FCS_RH_PITCH_CSS_MODE_B) crt->TextGrid( 15, 17, "*" );

		bool FCS_RH_PITCH_CSS_MODE_C = (FF4_IOM12_CH1 & 0x0010) != 0;
		if (FCS_RH_PITCH_CSS_MODE_C) crt->TextGrid( 15, 18, "*" );

		bool FCS_RH_RY_AUTO_MODE_A = (FF2_IOM12_CH1 & 0x0004) != 0;
		if (FCS_RH_RY_AUTO_MODE_A) crt->TextGrid( 23, 16, "*" );

		bool FCS_RH_RY_AUTO_MODE_B = (FF3_IOM12_CH1 & 0x0004) != 0;
		if (FCS_RH_RY_AUTO_MODE_B) crt->TextGrid( 23, 17, "*" );

		bool FCS_RH_RY_AUTO_MODE_C = (FF4_IOM12_CH1 & 0x0004) != 0;
		if (FCS_RH_RY_AUTO_MODE_C) crt->TextGrid( 23, 18, "*" );

		bool FCS_RH_RY_CSS_MODE_A = (FF2_IOM12_CH1 & 0x0002) != 0;
		if (FCS_RH_RY_CSS_MODE_A) crt->TextGrid( 27, 16, "*" );

		bool FCS_RH_RY_CSS_MODE_B = (FF3_IOM12_CH1 & 0x0002) != 0;
		if (FCS_RH_RY_CSS_MODE_B) crt->TextGrid( 27, 17, "*" );

		bool FCS_RH_RY_CSS_MODE_C = (FF4_IOM12_CH1 & 0x0002) != 0;
		if (FCS_RH_RY_CSS_MODE_C) crt->TextGrid( 27, 18, "*" );

		bool RH_SPD_BK_THROT_AUTO_MAN_A = (FF2_IOM12_CH2 & 0x8000) != 0;
		if (RH_SPD_BK_THROT_AUTO_MAN_A) crt->TextGrid( 36, 16, "*" );

		bool RH_SPD_BK_THROT_AUTO_MAN_B = (FF3_IOM12_CH2 & 0x8000) != 0;
		if (RH_SPD_BK_THROT_AUTO_MAN_B) crt->TextGrid( 36, 17, "*" );

		bool RH_SPD_BK_THROT_AUTO_MAN_C = (FF4_IOM12_CH2 & 0x8000) != 0;
		if (RH_SPD_BK_THROT_AUTO_MAN_C) crt->TextGrid( 36, 18, "*" );

		bool RH_SBTC_TAKEOVER_A = (FF2_IOM15_CH0 & 0x0004) != 0;
		if (RH_SBTC_TAKEOVER_A) crt->TextGrid( 40, 16, "*" );

		bool RH_SBTC_TAKEOVER_B = (FF3_IOM15_CH0 & 0x0004) != 0;
		if (RH_SBTC_TAKEOVER_B) crt->TextGrid( 40, 17, "*" );

		bool RH_SBTC_TAKEOVER_C = (FF4_IOM15_CH0 & 0x0004) != 0;
		if (RH_SBTC_TAKEOVER_C) crt->TextGrid( 40, 18, "*" );

		bool RH_BODY_FLAP_AUTO_MANUAL_A = (FF2_IOM12_CH1 & 0x0001) != 0;
		if (RH_BODY_FLAP_AUTO_MANUAL_A) crt->TextGrid( 45, 16, "*" );

		bool RH_BODY_FLAP_AUTO_MANUAL_B = (FF3_IOM12_CH1 & 0x0001) != 0;
		if (RH_BODY_FLAP_AUTO_MANUAL_B) crt->TextGrid( 45, 17, "*" );

		bool RH_BODY_FLAP_AUTO_MANUAL_C = (FF4_IOM12_CH1 & 0x0001) != 0;
		if (RH_BODY_FLAP_AUTO_MANUAL_C) crt->TextGrid( 45, 18, "*" );


		unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
		bool commfaultFF1 = (COMMFAULT_WORD_1 & 0x00000001) != 0;
		bool commfaultFF2 = (COMMFAULT_WORD_1 & 0x00000002) != 0;
		bool commfaultFF3 = (COMMFAULT_WORD_1 & 0x00000004) != 0;
		bool commfaultFF4 = (COMMFAULT_WORD_1 & 0x00000008) != 0;
		if (commfaultFF1) crt->TextGrid( 12, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 P AUT
		if (commfaultFF2) crt->TextGrid( 12, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 P AUT
		if (commfaultFF3) crt->TextGrid( 12, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 P AUT
		if (commfaultFF1) crt->TextGrid( 16, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 P CSS
		if (commfaultFF2) crt->TextGrid( 16, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 P CSS
		if (commfaultFF3) crt->TextGrid( 16, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 P CSS
		if (commfaultFF1) crt->TextGrid( 24, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 R/Y AUT
		if (commfaultFF2) crt->TextGrid( 24, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 R/Y AUT
		if (commfaultFF3) crt->TextGrid( 24, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 R/Y AUT
		if (commfaultFF1) crt->TextGrid( 28, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 R/Y CSS
		if (commfaultFF2) crt->TextGrid( 28, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 R/Y CSS
		if (commfaultFF3) crt->TextGrid( 28, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 R/Y CSS
		if (commfaultFF1) crt->TextGrid( 37, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 SPD BRK AUT
		if (commfaultFF2) crt->TextGrid( 37, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 SPD BRK AUT
		if (commfaultFF3) crt->TextGrid( 37, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 SPD BRK AUT
		if (commfaultFF1) crt->TextGrid( 41, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 SPD BRK MAN
		if (commfaultFF2) crt->TextGrid( 41, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 SPD BRK MAN
		if (commfaultFF3) crt->TextGrid( 41, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 SPD BRK MAN
		if (commfaultFF1) crt->TextGrid( 46, 13, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 1 BDY FLP AUT
		if (commfaultFF2) crt->TextGrid( 46, 14, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 2 BDY FLP AUT
		if (commfaultFF3) crt->TextGrid( 46, 15, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE L 3 BDY FLP AUT

		if (commfaultFF2) crt->TextGrid( 12, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 P AUT
		if (commfaultFF3) crt->TextGrid( 12, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 P AUT
		if (commfaultFF4) crt->TextGrid( 12, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 P AUT
		if (commfaultFF2) crt->TextGrid( 16, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 P CSS
		if (commfaultFF3) crt->TextGrid( 16, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 P CSS
		if (commfaultFF4) crt->TextGrid( 16, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 P CSS
		if (commfaultFF2) crt->TextGrid( 24, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 R/Y AUT
		if (commfaultFF3) crt->TextGrid( 24, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 R/Y AUT
		if (commfaultFF4) crt->TextGrid( 24, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 R/Y AUT
		if (commfaultFF2) crt->TextGrid( 28, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 R/Y CSS
		if (commfaultFF3) crt->TextGrid( 28, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 R/Y CSS
		if (commfaultFF4) crt->TextGrid( 28, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 R/Y CSS
		if (commfaultFF2) crt->TextGrid( 37, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 SPD BRK AUT
		if (commfaultFF3) crt->TextGrid( 37, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 SPD BRK AUT
		if (commfaultFF4) crt->TextGrid( 37, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 SPD BRK AUT
		if (commfaultFF2) crt->TextGrid( 41, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 SPD BRK MAN
		if (commfaultFF3) crt->TextGrid( 41, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 SPD BRK MAN
		if (commfaultFF4) crt->TextGrid( 41, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 SPD BRK MAN
		if (commfaultFF2) crt->TextGrid( 46, 16, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 1 BDY FLP AUT
		if (commfaultFF3) crt->TextGrid( 46, 17, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 2 BDY FLP AUT
		if (commfaultFF4) crt->TextGrid( 46, 18, "M", crt->DEUATT_OVERBRIGHT );// FCS MODE R 3 BDY FLP AUT
		return;
	}

	void GNCDisplays::SPEC25_SPEC43_printTHC( CRT_Interface* crt, bool axis_plus, bool axis_minus, int x, int y ) const
	{
		char ctmp[2];
		ctmp[0] = ' ';
		ctmp[1] = 0;
		if (axis_plus && !axis_minus) ctmp[0] = '+';
		else if (!axis_plus && axis_minus) ctmp[0] = '-';
		crt->TextGrid( x, y, ctmp );
		return;
	}

	void GNCDisplays::SPEC25_SPEC43_printRHC_P( CRT_Interface* crt, double val, int x, int y ) const
	{
		char cbuf[16];
		int itmp = 0;
		char ctmp = 0;

		itmp = min( (int)fabs( val * 100 ), 99 );
		if (val > 0) ctmp = 'U';
		else if (val < 0) ctmp = 'D';
		else ctmp = ' ';
		sprintf_s( cbuf, 16, "%c%02d", ctmp, itmp );
		crt->TextGrid( x, y, cbuf );
		return;
	}

	void GNCDisplays::SPEC25_SPEC43_printRHC_RY( CRT_Interface* crt, double val, int x, int y ) const
	{
		char cbuf[16];
		int itmp = 0;
		char ctmp = 0;

		itmp = min( (int)fabs( val * 100 ), 99 );
		if (val > 0) ctmp = 'R';
		else if (val < 0) ctmp = 'L';
		else ctmp = ' ';
		sprintf_s( cbuf, 16, "%c%02d", ctmp, itmp );
		crt->TextGrid( x, y, cbuf );
		return;
	}

	void GNCDisplays::OnPaint_SPEC43( CRT_Interface* crt ) const
	{
		unsigned short FF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH0_DATA );
		unsigned short FF1_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM15_CH0_DATA );
		unsigned short FF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH0_DATA );
		unsigned short FF2_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM15_CH0_DATA );
		unsigned short FF3_IOM6_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM6_CH0_DATA );
		unsigned short FF3_IOM15_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH0_DATA );

		bool FWD_THC_POS_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0100) != 0);
		bool FWD_THC_NEG_X_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0080) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_X_OUTPUT_A, FWD_THC_NEG_X_OUTPUT_A, 7, 5 );
		bool FWD_THC_POS_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0100) != 0);
		bool FWD_THC_NEG_X_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0080) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_X_OUTPUT_B, FWD_THC_NEG_X_OUTPUT_B, 7, 6 );
		bool FWD_THC_POS_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0100) != 0);
		bool FWD_THC_NEG_X_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0080) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_X_OUTPUT_C, FWD_THC_NEG_X_OUTPUT_C, 7, 7 );
		bool FWD_THC_POS_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0040) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0020) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Y_OUTPUT_A, FWD_THC_NEG_Y_OUTPUT_A, 9, 5 );
		bool FWD_THC_POS_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0040) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0020) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Y_OUTPUT_B, FWD_THC_NEG_Y_OUTPUT_B, 9, 6 );
		bool FWD_THC_POS_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0040) != 0);
		bool FWD_THC_NEG_Y_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0020) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Y_OUTPUT_C, FWD_THC_NEG_Y_OUTPUT_C, 9, 7 );
		bool FWD_THC_POS_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0010) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_A = ((FF1_IOM6_CH0 & 0x0008) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Z_OUTPUT_A, FWD_THC_NEG_Z_OUTPUT_A, 11, 5 );
		bool FWD_THC_POS_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0010) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_B = ((FF2_IOM6_CH0 & 0x0008) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Z_OUTPUT_B, FWD_THC_NEG_Z_OUTPUT_B, 11, 6 );
		bool FWD_THC_POS_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0010) != 0);
		bool FWD_THC_NEG_Z_OUTPUT_C = ((FF3_IOM6_CH0 & 0x0008) != 0);
		SPEC25_SPEC43_printTHC( crt, FWD_THC_POS_Z_OUTPUT_C, FWD_THC_NEG_Z_OUTPUT_C, 11, 7 );

		bool AFT_THC_POS_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0100) != 0);
		bool AFT_THC_NEG_X_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0080) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_X_OUTPUT_A, AFT_THC_NEG_X_OUTPUT_A, 7, 8 );
		bool AFT_THC_POS_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0100) != 0);
		bool AFT_THC_NEG_X_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0080) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_X_OUTPUT_B, AFT_THC_NEG_X_OUTPUT_B, 7, 9 );
		bool AFT_THC_POS_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0100) != 0);
		bool AFT_THC_NEG_X_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0080) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_X_OUTPUT_C, AFT_THC_NEG_X_OUTPUT_C, 7, 10 );
		bool AFT_THC_POS_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0040) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0020) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Y_OUTPUT_A, AFT_THC_NEG_Y_OUTPUT_A, 9, 8 );
		bool AFT_THC_POS_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0040) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0020) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Y_OUTPUT_B, AFT_THC_NEG_Y_OUTPUT_B, 9, 9 );
		bool AFT_THC_POS_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0040) != 0);
		bool AFT_THC_NEG_Y_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0020) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Y_OUTPUT_C, AFT_THC_NEG_Y_OUTPUT_C, 9, 10 );
		bool AFT_THC_POS_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0010) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_A = ((FF1_IOM15_CH0 & 0x0008) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Z_OUTPUT_A, AFT_THC_NEG_Z_OUTPUT_A, 11, 8 );
		bool AFT_THC_POS_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0010) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_B = ((FF2_IOM15_CH0 & 0x0008) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Z_OUTPUT_B, AFT_THC_NEG_Z_OUTPUT_B, 11, 9 );
		bool AFT_THC_POS_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0010) != 0);
		bool AFT_THC_NEG_Z_OUTPUT_C = ((FF3_IOM15_CH0 & 0x0008) != 0);
		SPEC25_SPEC43_printTHC( crt, AFT_THC_POS_Z_OUTPUT_C, AFT_THC_NEG_Z_OUTPUT_C, 11, 10 );

		/*SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[3].GetVoltage(), 37, 5 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[4].GetVoltage(), 37, 6 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[5].GetVoltage(), 37, 7 );
		SPEC25_SPEC43_printRHC_P( crt, LeftRHC[0].GetVoltage(), 41, 5 );
		SPEC25_SPEC43_printRHC_P( crt, LeftRHC[1].GetVoltage(), 41, 6 );
		SPEC25_SPEC43_printRHC_P( crt, LeftRHC[2].GetVoltage(), 41, 7 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[6].GetVoltage(), 45, 5 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[7].GetVoltage(), 45, 6 );
		SPEC25_SPEC43_printRHC_RY( crt, LeftRHC[8].GetVoltage(), 45, 7 );

		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[3].GetVoltage(), 37, 8 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[4].GetVoltage(), 37, 9 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[5].GetVoltage(), 37, 10 );
		SPEC25_SPEC43_printRHC_P( crt, RightRHC[0].GetVoltage(), 41, 8 );
		SPEC25_SPEC43_printRHC_P( crt, RightRHC[1].GetVoltage(), 41, 9 );
		SPEC25_SPEC43_printRHC_P( crt, RightRHC[2].GetVoltage(), 41, 10 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[6].GetVoltage(), 45, 8 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[7].GetVoltage(), 45, 9 );
		SPEC25_SPEC43_printRHC_RY( crt, RightRHC[8].GetVoltage(), 45, 10 );

		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[3].GetVoltage(), 37, 11 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[4].GetVoltage(), 37, 12 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[5].GetVoltage(), 37, 13 );
		SPEC25_SPEC43_printRHC_P( crt, AftRHC[0].GetVoltage(), 41, 11 );
		SPEC25_SPEC43_printRHC_P( crt, AftRHC[1].GetVoltage(), 41, 12 );
		SPEC25_SPEC43_printRHC_P( crt, AftRHC[2].GetVoltage(), 41, 13 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[6].GetVoltage(), 45, 11 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[7].GetVoltage(), 45, 12 );
		SPEC25_SPEC43_printRHC_RY( crt, AftRHC[8].GetVoltage(), 45, 13 );*/


		short LH_SBTC_CMD_A = static_cast<short>(ReadCOMPOOL_IS( SCP_FF1_IOM1_CH4_DATA ) * (1 / 5.11));
		short LH_SBTC_CMD_B = static_cast<short>(ReadCOMPOOL_IS( SCP_FF2_IOM1_CH4_DATA ) * (1 / 5.11));
		short RH_SBTC_CMD_A = static_cast<short>(ReadCOMPOOL_IS( SCP_FF2_IOM14_CH4_DATA ) * (1 / 5.11));
		short LH_SBTC_CMD_C = static_cast<short>(ReadCOMPOOL_IS( SCP_FF3_IOM1_CH4_DATA ) * (1 / 5.11));
		short RH_SBTC_CMD_B = static_cast<short>(ReadCOMPOOL_IS( SCP_FF3_IOM14_CH4_DATA ) * (1 / 5.11));
		short RH_SBTC_CMD_C = static_cast<short>(ReadCOMPOOL_IS( SCP_FF4_IOM14_CH4_DATA ) * (1 / 5.11));

		crt->NumberGrid( 8, 11, LH_SBTC_CMD_A, 3 );
		crt->NumberGrid( 8, 12, LH_SBTC_CMD_B, 3 );
		crt->NumberGrid( 8, 13, LH_SBTC_CMD_C, 3 );
		crt->NumberGrid( 8, 14, RH_SBTC_CMD_A, 3 );
		crt->NumberGrid( 8, 15, RH_SBTC_CMD_B, 3 );
		crt->NumberGrid( 8, 16, RH_SBTC_CMD_C, 3 );


		/*SPEC43_printRPTA( crt, LeftRPTA[0].GetVoltage(), 7, 17 );
		SPEC43_printRPTA( crt, LeftRPTA[1].GetVoltage(), 7, 18 );
		SPEC43_printRPTA( crt, LeftRPTA[2].GetVoltage(), 7, 19 );
		SPEC43_printRPTA( crt, RightRPTA[0].GetVoltage(), 7, 20 );
		SPEC43_printRPTA( crt, RightRPTA[1].GetVoltage(), 7, 21 );
		SPEC43_printRPTA( crt, RightRPTA[2].GetVoltage(), 7, 22 );*/


		unsigned short FF1_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH0_DATA );
		unsigned short FF2_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH0_DATA );
		unsigned short FF3_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM4_CH0_DATA );
		unsigned short FF4_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF4_IOM4_CH0_DATA );

		bool LH_BODY_FLAP_UP_A = (FF1_IOM4_CH0 & 0x1000) != 0;
		if (LH_BODY_FLAP_UP_A) crt->TextGrid( 22, 9, "*" );

		bool LH_BODY_FLAP_UP_B = (FF2_IOM4_CH0 & 0x1000) != 0;
		if (LH_BODY_FLAP_UP_B) crt->TextGrid( 22, 10, "*" );

		bool LH_BODY_FLAP_DOWN_A = (FF1_IOM4_CH0 & 0x0800) != 0;
		if (LH_BODY_FLAP_DOWN_A) crt->TextGrid( 24, 9, "*" );

		bool LH_BODY_FLAP_DOWN_B = (FF2_IOM4_CH0 & 0x0800) != 0;
		if (LH_BODY_FLAP_DOWN_B) crt->TextGrid( 24, 10, "*" );

		bool RH_BODY_FLAP_UP_A = (FF3_IOM4_CH0 & 0x1000) != 0;
		if (RH_BODY_FLAP_UP_A) crt->TextGrid( 22, 11, "*" );

		bool RH_BODY_FLAP_UP_B = (FF4_IOM4_CH0 & 0x1000) != 0;
		if (RH_BODY_FLAP_UP_B) crt->TextGrid( 22, 12, "*" );

		bool RH_BODY_FLAP_DOWN_A = (FF3_IOM4_CH0 & 0x0800) != 0;
		if (RH_BODY_FLAP_DOWN_A) crt->TextGrid( 24, 11, "*" );

		bool RH_BODY_FLAP_DOWN_B = (FF4_IOM4_CH0 & 0x0800) != 0;
		if (RH_BODY_FLAP_DOWN_B) crt->TextGrid( 24, 12, "*" );


		unsigned short FF1_IOM6_CH1 = ReadCOMPOOL_IS( SCP_FF1_IOM6_CH1_DATA );
		unsigned short FF2_IOM6_CH1 = ReadCOMPOOL_IS( SCP_FF2_IOM6_CH1_DATA );
		unsigned short FF3_IOM15_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM15_CH1_DATA );
		unsigned short FF4_IOM15_CH1 = ReadCOMPOOL_IS( SCP_FF4_IOM15_CH1_DATA );
		unsigned short FF1_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF1_IOM12_CH0_DATA );
		unsigned short FF2_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM12_CH0_DATA );
		unsigned short FF3_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH0_DATA );
		unsigned short FF4_IOM12_CH0 = ReadCOMPOOL_IS( SCP_FF4_IOM12_CH0_DATA );

		bool LH_RHC_PLUS_PITCH_TRIM_A = (FF1_IOM6_CH1 & 0x4000) != 0;
		bool LH_RHC_MINUS_PITCH_TRIM_A = (FF1_IOM6_CH1 & 0x2000) != 0;
		if (LH_RHC_PLUS_PITCH_TRIM_A && !LH_RHC_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 14, "U" );
		else if (!LH_RHC_PLUS_PITCH_TRIM_A && LH_RHC_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 14, "D" );

		bool LH_RHC_PLUS_PITCH_TRIM_B = (FF2_IOM6_CH1 & 0x4000) != 0;
		bool LH_RHC_MINUS_PITCH_TRIM_B = (FF2_IOM6_CH1 & 0x2000)  != 0;
		if (LH_RHC_PLUS_PITCH_TRIM_B && !LH_RHC_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 15, "U" );
		else if (!LH_RHC_PLUS_PITCH_TRIM_B && LH_RHC_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 15, "D" );

		bool LH_RHC_PLUS_ROLL_TRIM_A = (FF1_IOM6_CH1 & 0x1000) != 0;
		bool LH_RHC_MINUS_ROLL_TRIM_A = (FF1_IOM6_CH1 & 0x0800) != 0;
		if (LH_RHC_PLUS_ROLL_TRIM_A && !LH_RHC_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 14, "R" );
		else if (!LH_RHC_PLUS_ROLL_TRIM_A && LH_RHC_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 14, "L" );

		bool LH_RHC_PLUS_ROLL_TRIM_B = (FF2_IOM6_CH1 & 0x1000) != 0;
		bool LH_RHC_MINUS_ROLL_TRIM_B = (FF2_IOM6_CH1 & 0x0800) != 0;
		if (LH_RHC_PLUS_ROLL_TRIM_B && !LH_RHC_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 15, "R" );
		else if (!LH_RHC_PLUS_ROLL_TRIM_B && LH_RHC_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 15, "L" );

		bool RH_RHC_PLUS_PITCH_TRIM_A = (FF3_IOM15_CH1 & 0x4000) != 0;
		bool RH_RHC_MINUS_PITCH_TRIM_A = (FF3_IOM15_CH1 & 0x2000) != 0;
		if (RH_RHC_PLUS_PITCH_TRIM_A && !RH_RHC_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 16, "U" );
		else if (!RH_RHC_PLUS_PITCH_TRIM_A && RH_RHC_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 16, "D" );

		bool RH_RHC_PLUS_PITCH_TRIM_B = (FF4_IOM15_CH1 & 0x4000) != 0;
		bool RH_RHC_MINUS_PITCH_TRIM_B = (FF4_IOM15_CH1 & 0x2000) != 0;
		if (RH_RHC_PLUS_PITCH_TRIM_B && !RH_RHC_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 17, "U" );
		else if (!RH_RHC_PLUS_PITCH_TRIM_B && RH_RHC_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 17, "D" );

		bool RH_RHC_PLUS_ROLL_TRIM_A = (FF3_IOM15_CH1 & 0x1000) != 0;
		bool RH_RHC_MINUS_ROLL_TRIM_A = (FF3_IOM15_CH1 & 0x0800) != 0;
		if (RH_RHC_PLUS_ROLL_TRIM_A && !RH_RHC_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 16, "R" );
		else if (!RH_RHC_PLUS_ROLL_TRIM_A && RH_RHC_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 16, "L" );

		bool RH_RHC_PLUS_ROLL_TRIM_B = (FF4_IOM15_CH1 & 0x1000) != 0;
		bool RH_RHC_MINUS_ROLL_TRIM_B = (FF4_IOM15_CH1 & 0x0800) != 0;
		if (RH_RHC_PLUS_ROLL_TRIM_B && !RH_RHC_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 17, "R" );
		else if (!RH_RHC_PLUS_ROLL_TRIM_B && RH_RHC_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 17, "L" );


		bool LH_PLUS_ROLL_TRIM_A = (FF1_IOM12_CH0 & 0x1000) != 0;
		bool LH_MINUS_ROLL_TRIM_A = (FF1_IOM12_CH0 & 0x0800) != 0;
		if (LH_PLUS_ROLL_TRIM_A && !LH_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 18, "R" );
		else if (!LH_PLUS_ROLL_TRIM_A && LH_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 18, "L" );

		bool LH_PLUS_ROLL_TRIM_B = (FF2_IOM12_CH0 & 0x1000) != 0;
		bool LH_MINUS_ROLL_TRIM_B = (FF2_IOM12_CH0 & 0x0800) != 0;
		if (LH_PLUS_ROLL_TRIM_B && !LH_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 19, "R" );
		else if (!LH_PLUS_ROLL_TRIM_B && LH_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 19, "L" );

		bool LH_PLUS_PITCH_TRIM_A = (FF1_IOM12_CH0 & 0x4000) != 0;
		bool LH_MINUS_PITCH_TRIM_A = (FF1_IOM12_CH0 & 0x2000) != 0;
		if (LH_PLUS_PITCH_TRIM_A && !LH_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 18, "U" );
		else if (!LH_PLUS_PITCH_TRIM_A && LH_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 18, "D" );

		bool LH_PLUS_PITCH_TRIM_B = (FF2_IOM12_CH0 & 0x4000) != 0;
		bool LH_MINUS_PITCH_TRIM_B = (FF2_IOM12_CH0 & 0x2000) != 0;
		if (LH_PLUS_PITCH_TRIM_B && !LH_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 19, "U" );
		else if (!LH_PLUS_PITCH_TRIM_B && LH_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 19, "D" );

		bool LH_PLUS_YAW_TRIM_A = (FF1_IOM12_CH0 & 0x0400) != 0;
		bool LH_MINUS_YAW_TRIM_A = (FF1_IOM12_CH0 & 0x0200) != 0;
		if (LH_PLUS_YAW_TRIM_A && !LH_MINUS_YAW_TRIM_A) crt->TextGrid( 47, 18, "R" );
		else if (!LH_PLUS_YAW_TRIM_A && LH_MINUS_YAW_TRIM_A) crt->TextGrid( 47, 18, "L" );

		bool LH_PLUS_YAW_TRIM_B = (FF2_IOM12_CH0 & 0x0400) != 0;
		bool LH_MINUS_YAW_TRIM_B = (FF2_IOM12_CH0 & 0x0200) != 0;
		if (LH_PLUS_YAW_TRIM_B && !LH_MINUS_YAW_TRIM_B) crt->TextGrid( 47, 19, "R" );
		else if (!LH_PLUS_YAW_TRIM_B && LH_MINUS_YAW_TRIM_B) crt->TextGrid( 47, 19, "L" );

		bool RH_PLUS_ROLL_TRIM_A = (FF3_IOM12_CH0 & 0x1000) != 0;
		bool RH_MINUS_ROLL_TRIM_A = (FF3_IOM12_CH0 & 0x0800) != 0;
		if (RH_PLUS_ROLL_TRIM_A && !RH_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 20, "R" );
		else if (!RH_PLUS_ROLL_TRIM_A && RH_MINUS_ROLL_TRIM_A) crt->TextGrid( 39, 20, "L" );

		bool RH_PLUS_ROLL_TRIM_B = (FF4_IOM12_CH0 & 0x1000) != 0;
		bool RH_MINUS_ROLL_TRIM_B = (FF4_IOM12_CH0 & 0x0800) != 0;
		if (RH_PLUS_ROLL_TRIM_B && !RH_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 21, "R" );
		else if (!RH_PLUS_ROLL_TRIM_B && RH_MINUS_ROLL_TRIM_B) crt->TextGrid( 39, 21, "L" );

		bool RH_PLUS_PITCH_TRIM_A = (FF3_IOM12_CH0 & 0x4000) != 0;
		bool RH_MINUS_PITCH_TRIM_A = (FF3_IOM12_CH0 & 0x2000) != 0;
		if (RH_PLUS_PITCH_TRIM_A && !RH_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 20, "U" );
		else if (!RH_PLUS_PITCH_TRIM_A && RH_MINUS_PITCH_TRIM_A) crt->TextGrid( 43, 20, "D" );

		bool RH_PLUS_PITCH_TRIM_B = (FF4_IOM12_CH0 & 0x4000) != 0;
		bool RH_MINUS_PITCH_TRIM_B = (FF4_IOM12_CH0 & 0x2000) != 0;
		if (RH_PLUS_PITCH_TRIM_B && !RH_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 21, "U" );
		else if (!RH_PLUS_PITCH_TRIM_B && RH_MINUS_PITCH_TRIM_B) crt->TextGrid( 43, 21, "D" );

		bool RH_PLUS_YAW_TRIM_A = (FF3_IOM12_CH0 & 0x0400) != 0;
		bool RH_MINUS_YAW_TRIM_A = (FF3_IOM12_CH0 & 0x0200) != 0;
		if (RH_PLUS_YAW_TRIM_A && !RH_MINUS_YAW_TRIM_A) crt->TextGrid( 47, 20, "R" );
		else if (!RH_PLUS_YAW_TRIM_A && RH_MINUS_YAW_TRIM_A) crt->TextGrid( 47, 20, "L" );

		bool RH_PLUS_YAW_TRIM_B = (FF4_IOM12_CH0 & 0x0400) != 0;
		bool RH_MINUS_YAW_TRIM_B = (FF4_IOM12_CH0 & 0x0200) != 0;
		if (RH_PLUS_YAW_TRIM_B && !RH_MINUS_YAW_TRIM_B) crt->TextGrid( 47, 21, "R" );
		else if (!RH_PLUS_YAW_TRIM_B && RH_MINUS_YAW_TRIM_B) crt->TextGrid( 47, 21, "L" );

		unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
		bool commfaultFF1 = (COMMFAULT_WORD_1 & 0x00000001) != 0;
		bool commfaultFF2 = (COMMFAULT_WORD_1 & 0x00000002) != 0;
		bool commfaultFF3 = (COMMFAULT_WORD_1 & 0x00000004) != 0;
		bool commfaultFF4 = (COMMFAULT_WORD_1 & 0x00000008) != 0;
		if (commfaultFF1) crt->TextGrid( 8, 5, "M", crt->DEUATT_OVERBRIGHT );// THC L 1 X
		if (commfaultFF1) crt->TextGrid( 10, 5, "M", crt->DEUATT_OVERBRIGHT );// THC L 1 Y
		if (commfaultFF1) crt->TextGrid( 12, 5, "M", crt->DEUATT_OVERBRIGHT );// THC L 1 Z
		if (commfaultFF2) crt->TextGrid( 8, 6, "M", crt->DEUATT_OVERBRIGHT );// THC L 2 X
		if (commfaultFF2) crt->TextGrid( 10, 6, "M", crt->DEUATT_OVERBRIGHT );// THC L 2 Y
		if (commfaultFF2) crt->TextGrid( 12, 6, "M", crt->DEUATT_OVERBRIGHT );// THC L 2 Z
		if (commfaultFF3) crt->TextGrid( 8, 7, "M", crt->DEUATT_OVERBRIGHT );// THC L 3 X
		if (commfaultFF3) crt->TextGrid( 10, 7, "M", crt->DEUATT_OVERBRIGHT );// THC L 3 Y
		if (commfaultFF3) crt->TextGrid( 12, 7, "M", crt->DEUATT_OVERBRIGHT );// THC L 3 Z
		if (commfaultFF1) crt->TextGrid( 8, 8, "M", crt->DEUATT_OVERBRIGHT );// THC A 1 X
		if (commfaultFF1) crt->TextGrid( 10, 8, "M", crt->DEUATT_OVERBRIGHT );// THC A 1 Y
		if (commfaultFF1) crt->TextGrid( 12, 8, "M", crt->DEUATT_OVERBRIGHT );// THC A 1 Z
		if (commfaultFF2) crt->TextGrid( 8, 9, "M", crt->DEUATT_OVERBRIGHT );// THC A 2 X
		if (commfaultFF2) crt->TextGrid( 10, 9, "M", crt->DEUATT_OVERBRIGHT );// THC A 2 Y
		if (commfaultFF2) crt->TextGrid( 12, 9, "M", crt->DEUATT_OVERBRIGHT );// THC A 2 Z
		if (commfaultFF3) crt->TextGrid( 8, 10, "M", crt->DEUATT_OVERBRIGHT );// THC A 3 X
		if (commfaultFF3) crt->TextGrid( 10, 10, "M", crt->DEUATT_OVERBRIGHT );// THC A 3 Y
		if (commfaultFF3) crt->TextGrid( 12, 10, "M", crt->DEUATT_OVERBRIGHT );// THC A 3 Z

		if (commfaultFF1) crt->TextGrid( 23, 9, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW L 1 UP
		if (commfaultFF1) crt->TextGrid( 25, 9, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW L 1 DN
		if (commfaultFF2) crt->TextGrid( 23, 10, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW L 2 UP
		if (commfaultFF2) crt->TextGrid( 25, 10, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW L 2 DN
		if (commfaultFF3) crt->TextGrid( 23, 11, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW R 1 UP
		if (commfaultFF3) crt->TextGrid( 25, 11, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW R 1 DN
		if (commfaultFF4) crt->TextGrid( 23, 12, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW R 2 UP
		if (commfaultFF4) crt->TextGrid( 25, 12, "M", crt->DEUATT_OVERBRIGHT );// BDY FLP SW R 2 DN

		if (commfaultFF1) crt->TextGrid( 40, 14, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM L 1 R
		if (commfaultFF1) crt->TextGrid( 44, 14, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM L 1 P
		if (commfaultFF2) crt->TextGrid( 40, 15, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM L 2 R
		if (commfaultFF2) crt->TextGrid( 44, 15, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM L 2 P
		if (commfaultFF3) crt->TextGrid( 40, 16, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM R 1 R
		if (commfaultFF3) crt->TextGrid( 44, 16, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM R 1 P
		if (commfaultFF4) crt->TextGrid( 40, 17, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM R 2 R
		if (commfaultFF4) crt->TextGrid( 44, 17, "M", crt->DEUATT_OVERBRIGHT );// RHC TRIM R 2 P

		if (commfaultFF1) crt->TextGrid( 40, 18, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM L 1 R
		if (commfaultFF1) crt->TextGrid( 44, 18, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM L 1 P
		if (commfaultFF1) crt->TextGrid( 48, 18, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM L 1 Y
		if (commfaultFF2) crt->TextGrid( 40, 19, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM L 2 R
		if (commfaultFF2) crt->TextGrid( 44, 19, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM L 2 P
		if (commfaultFF2) crt->TextGrid( 48, 19, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM L 2 Y
		if (commfaultFF3) crt->TextGrid( 40, 20, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM R 1 R
		if (commfaultFF3) crt->TextGrid( 44, 20, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM R 1 P
		if (commfaultFF3) crt->TextGrid( 48, 20, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM R 1 Y
		if (commfaultFF4) crt->TextGrid( 40, 21, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM R 2 R
		if (commfaultFF4) crt->TextGrid( 44, 21, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM R 2 P
		if (commfaultFF4) crt->TextGrid( 48, 21, "M", crt->DEUATT_OVERBRIGHT );// PNL TRIM R 2 Y
		return;
	}

	void GNCDisplays::SPEC43_printRPTA( CRT_Interface* crt, double val, int x, int y ) const
	{
		char cbuf[16];
		int itmp = 0;
		char ctmp = 0;

		itmp = (int)fabs( val * 100 );
		if (val > 0) ctmp = 'R';
		else if (val < 0) ctmp = 'L';
		else ctmp = ' ';
		sprintf_s( cbuf, 16, "%c%03d", ctmp, itmp );
		crt->TextGrid( x, y, cbuf );
		return;
	}

	void GNCDisplays::OnPaint_SPEC44( CRT_Interface* crt ) const
	{
		unsigned short FF1_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH2_DATA );
		unsigned short FF1_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF1_IOM9_CH1_DATA );
		unsigned short FF2_IOM4_CH0 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH0_DATA );
		unsigned short FF2_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF2_IOM9_CH1_DATA );
		unsigned short FF3_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM9_CH1_DATA );
		unsigned short FF3_IOM12_CH1 = ReadCOMPOOL_IS( SCP_FF3_IOM12_CH1_DATA );
		unsigned short FF4_IOM9_CH1 = ReadCOMPOOL_IS( SCP_FF4_IOM9_CH1_DATA );
		unsigned short FF4_IOM12_CH2 = ReadCOMPOOL_IS( SCP_FF4_IOM12_CH2_DATA );

		bool ENTRY_ROLL_MODE_NO_Y_JET_A = ((FF1_IOM4_CH2 & 0x1000) != 0);
		bool ENTRY_ROLL_MODE_NO_Y_JET_B = ((FF2_IOM4_CH0 & 0x2000) != 0);
		bool ENTRY_ROLL_MODE_NO_Y_JET_C = ((FF3_IOM12_CH1 & 0x2000) != 0);
		bool ENTRY_ROLL_MODE_NO_Y_JET_D = ((FF4_IOM12_CH2 & 0x0001) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_A = ((FF1_IOM9_CH1 & 0x1000) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_B = ((FF2_IOM9_CH1 & 0x1000) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_C = ((FF3_IOM9_CH1 & 0x1000) != 0);
		bool ENTRY_ROLL_MODE_L_GAIN_D = ((FF4_IOM9_CH1 & 0x1000) != 0);
		if (ENTRY_ROLL_MODE_L_GAIN_A) crt->TextGrid( 33, 7, "*" );
		if (ENTRY_ROLL_MODE_L_GAIN_B) crt->TextGrid( 33, 8, "*" );
		if (ENTRY_ROLL_MODE_L_GAIN_C) crt->TextGrid( 33, 9, "*" );
		if (ENTRY_ROLL_MODE_L_GAIN_D) crt->TextGrid( 33, 10, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_A) crt->TextGrid( 37, 7, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_B) crt->TextGrid( 37, 8, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_C) crt->TextGrid( 37, 9, "*" );
		if (ENTRY_ROLL_MODE_NO_Y_JET_D) crt->TextGrid( 37, 10, "*" );

		unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
		bool commfaultFF1 = (COMMFAULT_WORD_1 & 0x00000001) != 0;
		bool commfaultFF2 = (COMMFAULT_WORD_1 & 0x00000002) != 0;
		bool commfaultFF3 = (COMMFAULT_WORD_1 & 0x00000004) != 0;
		bool commfaultFF4 = (COMMFAULT_WORD_1 & 0x00000008) != 0;
		if (commfaultFF1) crt->TextGrid( 34, 7, "M", crt->DEUATT_OVERBRIGHT );// LOW GAIN 1
		if (commfaultFF2) crt->TextGrid( 34, 8, "M", crt->DEUATT_OVERBRIGHT );// LOW GAIN 2
		if (commfaultFF3) crt->TextGrid( 34, 9, "M", crt->DEUATT_OVERBRIGHT );// LOW GAIN 3
		if (commfaultFF4) crt->TextGrid( 34, 10, "M", crt->DEUATT_OVERBRIGHT );// LOW GAIN 4
		if (commfaultFF1) crt->TextGrid( 38, 7, "M", crt->DEUATT_OVERBRIGHT );// NO Y/J 1
		if (commfaultFF2) crt->TextGrid( 38, 8, "M", crt->DEUATT_OVERBRIGHT );// NO Y/J 2
		if (commfaultFF3) crt->TextGrid( 38, 9, "M", crt->DEUATT_OVERBRIGHT );// NO Y/J 3
		if (commfaultFF4) crt->TextGrid( 38, 10, "M", crt->DEUATT_OVERBRIGHT );// NO Y/J 4
		return;
	}

	void GNCDisplays::OnPaint_SPEC45( CRT_Interface* crt ) const
	{
		return;
	}

	void GNCDisplays::OnPaint_SPEC50( CRT_Interface* crt ) const
	{
		char cbuf[51];

		if ((ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_105 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_106 ) == 1))
		{
			if ((ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 1) || (ReadCOMPOOL_IS( SCP_RTLS_ABORT_DECLARED ) == 1) ||
				(0/*TODO CONT_2EO_START*/ == 1) || (0/*TODO CONT_3EO_START*/ == 1))
			{
				crt->TextGrid( 1, 5, "40 TAL" );
				crt->TextGrid( 9, 5, "SITE" );
			}
		}

		if ((ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_105 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_106 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1))
		{
			if ((0/*TODO CONT_2EO_START*/ == 1) || (0/*TODO CONT_3EO_START*/ == 1)) crt->TextGrid( 4, 6, "CONT" );
			else if (ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 1) crt->TextGrid( 4, 6, "TAL" );
			else crt->TextGrid( 4, 6, "RTLS" );
		}
		else// OPS 3
		{
			crt->TextGrid( 4, 6, "LAND" );
		}
		sprintf_s( cbuf, 51, "%02d", ReadCOMPOOL_IS( SCP_AREA_SEL ) );
		crt->TextGrid( 14, 6, cbuf );

		ReadCOMPOOL_C( SCP_RUNWAY_NAME_PSL, cbuf, 5 );
		cbuf[5] = 0;
		crt->TextGrid( 5, 7, cbuf );

		ReadCOMPOOL_C( SCP_RUNWAY_NAME_SSL, cbuf, 5 );
		cbuf[5] = 0;
		crt->TextGrid( 5, 8, cbuf );

		if (ReadCOMPOOL_IS( SCP_RW_SELECT ) == 1) crt->TextGrid( 15, 7, "*" );
		else crt->TextGrid( 15, 8, "*" );

		if (ReadCOMPOOL_IS( SCP_OVHD ) == 1)
		{
			crt->TextGrid( 7, 13, "OVHD", (ReadCOMPOOL_IS( SCP_OHALERT ) == 1) ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL );
		}
		else crt->TextGrid( 7, 13, "STRT" );
		if ((ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1))
		{
			if (ReadCOMPOOL_SS( SCP_YSGNP ) < 0.0) crt->TextGrid( 5, 13, "L" );
			else crt->TextGrid( 5, 13, "R" );

			if (ReadCOMPOOL_SS( SCP_L_HSI_P ) < 0.0) crt->TextGrid( 5, 14, "L" );
			else crt->TextGrid( 5, 14, "R" );
		}
		if (ReadCOMPOOL_IS( SCP_ENT_PT_SW ) == 1) crt->TextGrid( 1, 15, "N" );
		else crt->TextGrid( 1, 15, "M" );

		if (ReadCOMPOOL_IS( SCP_GI_CHANGE ) == 1) crt->TextGrid( 7, 16, "CLSE" );
		else crt->TextGrid( 7, 16, "NOM" );

		unsigned short I_SHORT_RW = ReadCOMPOOL_IS( SCP_I_SHORT_RW );
		if (I_SHORT_RW == 0) crt->TextGrid( 8, 17, "NOM" );
		else if (I_SHORT_RW == 1) crt->TextGrid( 6, 17, "SHORT", crt->DEUATT_OVERBRIGHT );
		else /*if (I_SHORT_RW == 2)*/ crt->TextGrid( 8, 17, "ELS", crt->DEUATT_OVERBRIGHT );

		//if (ReadCOMPOOL_IS( SCP_PROCESSING_MLS ) == 1) crt->TextGrid( 30, 16, "MLS", crt->DEUATT_OVERBRIGHT );// TODO

		if (ReadCOMPOOL_IS( SCP_DO_HERROR_DISPLAY ) == 1)
		{
			short pos;

			for (int i = 1; i <= (ReadCOMPOOL_IS( SCP_HERROR_NO_DIV ) + 1); i++)
			{
				pos = ReadCOMPOOL_AIS( SCP_HERROR_TICK_LOC, i, 11 );

				crt->Text( 807, pos, "\x2D" );
			}

			crt->Line( 807, 419, 807, 175 );


			char label[5];
			memset( label, 0, 5 );
			ReadCOMPOOL_C( SCP_HERROR_LABEL, label, 4 );
			unsigned short len = static_cast<unsigned short>(strlen( label ));
			crt->Text( 770 + 19 - (len * 19), 419, label );
			crt->Text( 770 + 19 - (len * 19), 175, label );
			crt->Text( 770, 297, "0" );

			char att = 0;
			if (ReadCOMPOOL_IS( SCP_HERROR_FLASH ) == 1) att = crt->DEUATT_FLASHING;

			pos = ReadCOMPOOL_IS( SCP_HERROR_DISP );
			crt->Text( 807, pos, "\x1F", att );
		}


		if (ReadCOMPOOL_IS( SCP_DO_TGO_DISPLAY ) == 1)
		{
			short pos;
			cbuf[1] = 0;
			char lbl[6];
			ReadCOMPOOL_C( SCP_TGO_LABEL, lbl, 5 );
			for (int i = 1; i <= 5; i++)
			{
				pos = ReadCOMPOOL_AIS( SCP_TGO_TICK_LOC, i, 5 );

				crt->Text( pos, 100, "\x18" );

				cbuf[0] = lbl[i - 1];
				crt->Text( pos, 128, cbuf );
			}

			crt->Line( 450, 95, 770, 95 );


			char att = 0;
			if (ReadCOMPOOL_IS( SCP_TGO_XTRACK_FLASH ) == 1) att = crt->DEUATT_FLASHING;

			pos = ReadCOMPOOL_IS( SCP_TGO_XTRACK_DISP );

			crt->Text( pos, 95, "\x06", att );
		}
		else if ((ReadCOMPOOL_IS( SCP_DO_RERRC_DISPLAY ) == 1) || (ReadCOMPOOL_IS( SCP_DO_Y_DISPLAY ) == 1))
		{
			short pos;

			for (int i = 1; i <= (ReadCOMPOOL_IS( SCP_XTRACK_NO_DIV ) + 1); i++)
			{
				pos = ReadCOMPOOL_AIS( SCP_XTRACK_TICK_LOC, i, 11 );

				crt->Text( pos, 100, "\x18" );
			}
			//crt->Text( 610, 100, "\x18" );// TODO check if it should be displayed with logic above

			crt->Line( 450, 95, 770, 95 );


			char label[5];
			memset( label, 0, 5 );
			ReadCOMPOOL_C( SCP_XTRACK_LABEL, label, 4 );
			unsigned short len = static_cast<unsigned short>(strlen( label ));
			crt->Text( 450 - static_cast<unsigned short>(len * 19 * 0.5), 128, label );
			crt->Text( 770 - static_cast<unsigned short>(len * 19 * 0.5), 128, label );
			crt->Text( 610, 128, "0" );

			char att = 0;
			if (ReadCOMPOOL_IS( SCP_TGO_XTRACK_FLASH ) == 1) att = crt->DEUATT_FLASHING;

			pos = ReadCOMPOOL_IS( SCP_TGO_XTRACK_DISP );

			crt->Text( pos, 95, "\x0E", att );
		}


		{
			// TODO hide in A/L?
			short X_HAC = ReadCOMPOOL_IS( SCP_X_HAC );
			short Y_HAC = ReadCOMPOOL_IS( SCP_Y_HAC );
			short RAD_HAC = ReadCOMPOOL_IS( SCP_RAD_HAC );

			Y_HAC = 731 - Y_HAC;// convert Y coordinate

			crt->Circle( X_HAC, Y_HAC, RAD_HAC );
		}


		{
			short X_TAIL_COORD = ReadCOMPOOL_IS( SCP_X_TAIL_COORD );
			short Y_TAIL_COORD = ReadCOMPOOL_IS( SCP_Y_TAIL_COORD );
			short X_HEAD_COORD = ReadCOMPOOL_IS( SCP_X_HEAD_COORD );
			short Y_HEAD_COORD = ReadCOMPOOL_IS( SCP_Y_HEAD_COORD );
			
			Y_TAIL_COORD = 731 - Y_TAIL_COORD;// convert Y coordinate
			Y_HEAD_COORD = 731 - Y_HEAD_COORD;// convert Y coordinate

			crt->Circle( X_TAIL_COORD, Y_TAIL_COORD, 5 );
			crt->Line( X_HEAD_COORD, Y_HEAD_COORD, X_TAIL_COORD, Y_TAIL_COORD );
		}


		{
			short X_20PRED = ReadCOMPOOL_IS( SCP_X_20PRED );
			short Y_20PRED = ReadCOMPOOL_IS( SCP_Y_20PRED );
			short X_40PRED = ReadCOMPOOL_IS( SCP_X_40PRED );
			short Y_40PRED = ReadCOMPOOL_IS( SCP_Y_40PRED );
			short X_60PRED = ReadCOMPOOL_IS( SCP_X_60PRED );
			short Y_60PRED = ReadCOMPOOL_IS( SCP_Y_60PRED );

			Y_20PRED = 731 - Y_20PRED;// convert Y coordinate
			Y_40PRED = 731 - Y_40PRED;// convert Y coordinate
			Y_60PRED = 731 - Y_60PRED;// convert Y coordinate

			crt->Circle( X_20PRED, Y_20PRED, 5, crt->DEUATT_OVERBRIGHT );
			crt->Circle( X_40PRED, Y_40PRED, 5, crt->DEUATT_OVERBRIGHT );
			crt->Circle( X_60PRED, Y_60PRED, 5, crt->DEUATT_OVERBRIGHT );
		}

		{
			unsigned short HI_G = ReadCOMPOOL_IS( SCP_HI_G );// HACK not really sure this is the source (it's not used anywhere else)
			char att = crt->DEUATT_NORMAL;
			if (HI_G == 1) att |= crt->DEUATT_FLASHING;

			if ((ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1))
			{
				double DISPLAYED_NORMAL_ACCEL = ReadCOMPOOL_SS( SCP_DISPLAYED_NORMAL_ACCEL ) / (G * MPS2FPS);
				crt->NumberGrid( 21, 16, DISPLAYED_NORMAL_ACCEL, 1, 1, att );
			}

			const int BUG_POINT_X = 512;
			const int BUG_POINT_Y = 419;
			crt->Text( BUG_POINT_X, BUG_POINT_Y, "\x0E", att );
		}
		return;
	}

	void GNCDisplays::OnPaint_SPEC51( CRT_Interface* crt ) const
	{
		{
			if (ReadCOMPOOL_IS( SCP_ABT_THROT_CMD ) == 1) crt->TextGrid( 13, 8, "*" );
			else if (ReadCOMPOOL_IS( SCP_NOM_THROT_CMD ) == 1) crt->TextGrid( 13, 9, "*" );
			else if (ReadCOMPOOL_IS( SCP_MAX_THROT_CMD ) == 1) crt->TextGrid( 12, 7, "*" );
		}

		{
			if (ReadCOMPOOL_IS( SCP_NO_Y_JET ) == 0)
			{
				if (ReadCOMPOOL_IS( SCP_L_GAIN ) == 0)
				{
					crt->TextGrid( 45, 18, "AUTO" );
				}
				else
				{
					crt->TextGrid( 45, 18, "L GAIN" );
				}
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_L_GAIN ) == 0)
				{
					crt->TextGrid( 45, 18, "NO YJET" );
				}
			}
		}

		if ((ReadCOMPOOL_IS( SCP_MM_CODE_301 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_302 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_303 ) == 1) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1))
		{
			if (ReadCOMPOOL_IS( SCP_WRAP ) == 1)
			{
				crt->TextGrid( 49, 20, "ACT" );
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_WRAP_MODE ) == 1)
				{
					crt->TextGrid( 49, 20, "ENA" );
				}
				else
				{
					crt->TextGrid( 49, 20, "INH" );
				}
			}
		}

		if ((ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 1) && (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) == 0)) crt->TextGrid( 47, 22, "*" );
		else if (ReadCOMPOOL_IS( SCP_VENT_DOOR_POS_IND ) == 1) crt->TextGrid( 47, 22, "* OP" );

		if ((ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 1) && (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) == 1)) crt->TextGrid( 47, 23, "*" );
		else if (ReadCOMPOOL_IS( SCP_VENT_DOOR_POS_IND ) == 2) crt->TextGrid( 47, 23, "* CL" );
		return;
	}

	void GNCDisplays::OnPaint_SPEC53( CRT_Interface* crt ) const
	{
		// TODO
		return;
	}

	void GNCDisplays::OnPaint_SPEC55( CRT_Interface* crt ) const
	{
		if ((ReadCOMPOOL_IS( SCP_OPS1_INDICATOR ) == 0) && (ReadCOMPOOL_IS( SCP_MM_CODE_901 ) == 0) && (ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 0))
		{
			char cbuf[16];
			double lon = 0;
			double lat = 0;
			double rad = 0;
			STS()->GetEquPos( lon, lat, rad );

			lon *= DEG;
			lat *= DEG;
			rad -= 6371010;
			if ((ReadCOMPOOL_IS( SCP_MM_CODE_304 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_305 ) == 1) ||
				(ReadCOMPOOL_IS( SCP_MM_CODE_602 ) == 1) || (ReadCOMPOOL_IS( SCP_MM_CODE_603 ) == 1)) rad *= (MPS2FPS / 1000);// kft
			else rad /= NM2M;// nm

			if (lat >= 0) crt->TextGrid( 29, 9, "N" );
			else crt->TextGrid( 29, 9, "S" );

			sprintf_s( cbuf, 16, "%05.2f", fabs( lat ) );
			crt->TextGrid( 29, 10, cbuf );

			if (lon >= 0) crt->TextGrid( 37, 9, "E" );
			else crt->TextGrid( 37, 9, "W" );

			sprintf_s( cbuf, 16, "%06.2f", fabs( lon ) );
			crt->TextGrid( 36, 10, cbuf );

			sprintf_s( cbuf, 16, "%08.4f", rad );
			crt->TextGrid( 44, 10, cbuf );
		}
		return;
	}

	void GNCDisplays::OnPaint_SPEC112( CRT_Interface* crt ) const
	{
		// TODO
		// BTU SELECTION
		/*if (ITEM_STATE_SPEC112[0] == true) crt->TextGrid( 7, 4, "*" );
		if (ITEM_STATE_SPEC112[1] == true) crt->TextGrid( 7, 5, "*" );
		if (ITEM_STATE_SPEC112[2] == true) crt->TextGrid( 7, 6, "*" );
		if (ITEM_STATE_SPEC112[3] == true) crt->TextGrid( 7, 7, "*" );
		if (ITEM_STATE_SPEC112[4] == true) crt->TextGrid( 7, 8, "*" );
		if (ITEM_STATE_SPEC112[5] == true) crt->TextGrid( 7, 9, "*" );
		if (ITEM_STATE_SPEC112[6] == true) crt->TextGrid( 7, 10, "*" );
		if (ITEM_STATE_SPEC112[7] == true) crt->TextGrid( 7, 11, "*" );
		if (ITEM_STATE_SPEC112[8] == true) crt->TextGrid( 7, 12, "*" );
		if (ITEM_STATE_SPEC112[9] == true) crt->TextGrid( 8, 13, "*" );
		if (ITEM_STATE_SPEC112[10] == true) crt->TextGrid( 9, 17, "*" );
		if (ITEM_STATE_SPEC112[11] == true) crt->TextGrid( 18, 4, "*" );
		if (ITEM_STATE_SPEC112[12] == true) crt->TextGrid( 18, 5, "*" );
		if (ITEM_STATE_SPEC112[13] == true) crt->TextGrid( 18, 6, "*" );
		if (ITEM_STATE_SPEC112[14] == true) crt->TextGrid( 18, 7, "*" );
		if (ITEM_STATE_SPEC112[15] == true) crt->TextGrid( 18, 8, "*" );
		if (ITEM_STATE_SPEC112[16] == true) crt->TextGrid( 18, 9, "*" );
		if (ITEM_STATE_SPEC112[17] == true) crt->TextGrid( 18, 10, "*" );
		if (ITEM_STATE_SPEC112[18] == true) crt->TextGrid( 18, 11, "*" );
		if (ITEM_STATE_SPEC112[19] == true) crt->TextGrid( 18, 12, "*" );
		if (ITEM_STATE_SPEC112[20] == true) crt->TextGrid( 18, 13, "*" );
		if (ITEM_STATE_SPEC112[21] == true) crt->TextGrid( 18, 14, "*" );
		if (ITEM_STATE_SPEC112[22] == true) crt->TextGrid( 18, 15, "*" );
		if (ITEM_STATE_SPEC112[23] == true) crt->TextGrid( 19, 17, "*" );

		// PORT SEL
		if (ITEM_STATE_SPEC112[30] == true) crt->TextGrid( 33, 11, "*" );
		if (ITEM_STATE_SPEC112[31] == true) crt->TextGrid( 33, 12, "*" );

		// TEST
		if (ITEM_STATE_SPEC112[24] == true) crt->TextGrid( 23, 19, "*" );
		if (ITEM_STATE_SPEC112[25] == true) crt->TextGrid( 23, 20, "*" );
		if (ITEM_STATE_SPEC112[26] == true) crt->TextGrid( 23, 21, "*" );

		// BTU
		if (ITEM_STATE_SPEC112[29] == true) crt->TextGrid( 51, 23, "*" );*/
		return;
	}

	void GNCDisplays::OnPaint_SPEC113( CRT_Interface* crt ) const
	{
		// TODO
		/*char cbuf[64];

		// MONITOR
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 4, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 4, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 5, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 5, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 6, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 6, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 7, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 7, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 8, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 8, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 9, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 9, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 10, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 10, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 11, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 11, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 12, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 12, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 13, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 13, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 14, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 14, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 15, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 15, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 16, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 16, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 17, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 17, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 18, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 18, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 19, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 19, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 20, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 20, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 21, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 21, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 22, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 22, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 1, 23, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 23, cbuf );
		sprintf_s( cbuf, 64, "%02.0f", dtmp );
		crt->TextGrid( 2, 24, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 8, 24, cbuf );*/

		/*if (ITEM_STATE_SPEC113[0] == true) crt->TextGrid( 21, 4, "*" );
		if (ITEM_STATE_SPEC113[1] == true) crt->TextGrid( 21, 5, "*" );
		if (ITEM_STATE_SPEC113[2] == true) crt->TextGrid( 21, 6, "*" );
		if (ITEM_STATE_SPEC113[3] == true) crt->TextGrid( 21, 7, "*" );
		if (ITEM_STATE_SPEC113[4] == true) crt->TextGrid( 21, 8, "*" );
		if (ITEM_STATE_SPEC113[5] == true) crt->TextGrid( 21, 9, "*" );
		if (ITEM_STATE_SPEC113[6] == true) crt->TextGrid( 21, 10, "*" );
		if (ITEM_STATE_SPEC113[7] == true) crt->TextGrid( 21, 11, "*" );
		if (ITEM_STATE_SPEC113[8] == true) crt->TextGrid( 21, 12, "*" );
		if (ITEM_STATE_SPEC113[9] == true) crt->TextGrid( 21, 13, "*" );
		if (ITEM_STATE_SPEC113[10] == true) crt->TextGrid( 21, 14, "*" );
		if (ITEM_STATE_SPEC113[11] == true) crt->TextGrid( 21, 15, "*" );
		if (ITEM_STATE_SPEC113[12] == true) crt->TextGrid( 21, 16, "*" );
		if (ITEM_STATE_SPEC113[13] == true) crt->TextGrid( 21, 17, "*" );
		if (ITEM_STATE_SPEC113[14] == true) crt->TextGrid( 21, 18, "*" );
		if (ITEM_STATE_SPEC113[15] == true) crt->TextGrid( 21, 19, "*" );
		if (ITEM_STATE_SPEC113[16] == true) crt->TextGrid( 21, 20, "*" );
		if (ITEM_STATE_SPEC113[17] == true) crt->TextGrid( 21, 21, "*" );
		if (ITEM_STATE_SPEC113[18] == true) crt->TextGrid( 21, 22, "*" );
		if (ITEM_STATE_SPEC113[19] == true) crt->TextGrid( 21, 23, "*" );
		if (ITEM_STATE_SPEC113[20] == true) crt->TextGrid( 21, 24, "*" );*/

		// FAIL
		/*if (abc == true) crt->TextGrid( 23, 4, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 4, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 4, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 4, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 4, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 4, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 4, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 4, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 5, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 5, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 5, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 5, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 5, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 5, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 5, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 5, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 6, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 6, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 6, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 6, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 6, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 6, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 6, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 6, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 7, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 7, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 7, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 7, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 7, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 7, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 7, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 7, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 8, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 8, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 8, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 8, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 8, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 8, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 8, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 8, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 9, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 9, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 9, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 9, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 9, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 9, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 9, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 9, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 10, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 10, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 10, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 10, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 10, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 10, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 10, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 10, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 11, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 11, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 11, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 11, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 11, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 11, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 11, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 11, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 12, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 12, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 12, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 12, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 12, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 12, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 12, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 12, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 13, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 13, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 13, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 13, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 13, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 13, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 13, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 13, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 14, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 14, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 14, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 14, "M", crt->DEUATT_OVERBRIGHT );

		if (abc == true) crt->TextGrid( 23, 15, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 23, 15, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 25, 15, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 25, 15, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 27, 15, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 27, 15, "M", crt->DEUATT_OVERBRIGHT );
		if (abc == true) crt->TextGrid( 29, 15, "\x1D", crt->DEUATT_OVERBRIGHT );
		else if (abc == true) crt->TextGrid( 29, 15, "M", crt->DEUATT_OVERBRIGHT );*/

		// ACTUATOR GIMBALING
		/*sprintf_s( cbuf, 64, "%05.2f", dtmp );
		crt->TextGrid( 39, 4, cbuf );
		sprintf_s( cbuf, 64, "%+06.2f", dtmp );
		crt->TextGrid( 42, 5, cbuf );*/

		/*if (ITEM_STATE_SPEC113[30] == true)
		{
			if (abc == true)
			{
				// speedbrake
				if (abc == true)
				{
					pMDU->LeftArrow( 40, 6 );
					pMDU->RightArrow( 41, 6 );
				}
				else
				{
					pMDU->RightArrow( 40, 6 );
					pMDU->LeftArrow( 41, 6 );
				}
			}
			else if (abc == true)
			{
				// other actuators (vertical)
				if (abc == true) crt->TextGrid( 40, 6 "\x1D", );
				else crt->TextGrid( 40, 6 "\x1D", );
			}
			else
			{
				// other actuators (horizontal)
				if (abc == true) pMDU->LeftArrow( 40, 6 );
				else pMDU->RightArrow( 40, 6 );
			}
		}
		if (ITEM_STATE_SPEC113[31] == true) crt->TextGrid( 51, 6, "*" );
		if (ITEM_STATE_SPEC113[32] == true) crt->TextGrid( 51, 9, "*" );*/

		// HYD PR
		/*sprintf_s( cbuf, 64, "%4.0f", STS()->GetAPU( 1 )->GetHydraulicPressure() );
		crt->TextGrid( 35, 9, cbuf );
		sprintf_s( cbuf, 64, "%4.0f", STS()->GetAPU( 2 )->GetHydraulicPressure() );
		crt->TextGrid( 35, 10, cbuf );
		sprintf_s( cbuf, 64, "%4.0f", STS()->GetAPU( 3 )->GetHydraulicPressure() );
		crt->TextGrid( 35, 11, cbuf );*/

		// AI SRB/NW
		//if (ITEM_STATE_SPEC113[33] == true) crt->TextGrid( 51, 12, "*" );

		// ME ISO V
		/*if (abc == true) crt->TextGrid( 32, 14, "C" );
		if (abc == true) crt->TextGrid( 35, 14, "C" );
		if (abc == true) crt->TextGrid( 38, 14, "C" );*/

		// FC LIM CHNG
		/*if (ITEM_STATE_SPEC113[34] == true) crt->TextGrid( 51, 15, "*" );
		if (ITEM_STATE_SPEC113[35] == true) crt->TextGrid( 51, 16, "*" );
		if (ITEM_STATE_SPEC113[36] == true) crt->TextGrid( 51, 17, "*" );
		if (ITEM_STATE_SPEC113[37] == true) crt->TextGrid( 51, 18, "*" );
		if (ITEM_STATE_SPEC113[38] == true) crt->TextGrid( 51, 19, "*" );
		if (ITEM_STATE_SPEC113[39] == true) crt->TextGrid( 51, 20, "*" );
		if (ITEM_STATE_SPEC113[40] == true) crt->TextGrid( 51, 21, "*" );
		if (ITEM_STATE_SPEC113[41] == true) crt->TextGrid( 51, 22, "*" );
		if (ITEM_STATE_SPEC113[42] == true) crt->TextGrid( 51, 23, "*" );
		if (ITEM_STATE_SPEC113[43] == true) crt->TextGrid( 51, 24, "*" );

		// AI MODES
		if (ITEM_STATE_SPEC113[21] == true) crt->TextGrid( 33, 18, "*" );
		if (ITEM_STATE_SPEC113[22] == true) crt->TextGrid( 33, 19, "*" );
		if (ITEM_STATE_SPEC113[23] == true) crt->TextGrid( 33, 20, "*" );
		if (ITEM_STATE_SPEC113[24] == true) crt->TextGrid( 33, 21, "*" );
		if (ITEM_STATE_SPEC113[25] == true) crt->TextGrid( 33, 22, "*" );
		if (ITEM_STATE_SPEC113[26] == true) crt->TextGrid( 33, 23, "*" );
		if (ITEM_STATE_SPEC113[27] == true) crt->TextGrid( 33, 24, "*" );*/
		return;
	}

	void GNCDisplays::OnPaint_XXXXXXTRAJ1( CRT_Interface* crt ) const
	{
		// title
		unsigned short DISP_TITLE = ReadCOMPOOL_IS( SCP_DISP_TITLE );
		if (DISP_TITLE == 1) crt->TextGrid( 18, 1, "LAUNCH" );
		else if (DISP_TITLE == 2) crt->TextGrid( 18, 1, "ASCENT" );
		else if (DISP_TITLE == 3) crt->TextGrid( 20, 1, "RTLS" );
		else if (DISP_TITLE == 5) crt->TextGrid( 21, 1, "ATO" );

		// solid lines
		for (int i = 1; i <= 7; i++)
		{
			short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A1_SOLID_LINE, i, 1, 7, 4 ));
			short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A1_SOLID_LINE, i, 2, 7, 4 ));
			short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A1_SOLID_LINE, i, 3, 7, 4 ));
			short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A1_SOLID_LINE, i, 4, 7, 4 ));
			crt->Line( x1, y1, x2, y2 );
		}

		// character strings
		for (int i = 1; i <= 8; i++)
		{
			SCP_DISPCHAR dc;
			ReadCOMPOOL_ASTRUCT( SCP_A1_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 8 );
			char txt[5];
			memset( txt, 0, 5 );
			memcpy( txt, dc.TXT, 4 );
			crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
		}


		if (ReadCOMPOOL_IS( SCP_CONT_SERC ) == 1) crt->TextGrid( 3, 13, "*" );
		if (ReadCOMPOOL_IS( SCP_ENA_RCS_CNTL ) == 1) crt->TextGrid( 10, 13, "ON", crt->DEUATT_OVERBRIGHT );


		if (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1)
		{
			crt->NumberGrid( 45, 18, ReadCOMPOOL_IS( SCP_K_CMD ), 3 );

			if (ReadCOMPOOL_IS( SCP_LH_RH_SRB_PC_50_PSI_FLAG ) == 1) crt->TextGrid( 23, 10, "PC<50", crt->DEUATT_OVERBRIGHT | crt->DEUATT_FLASHING );

			if (ReadCOMPOOL_IS( SCP_SRB_AUTO_SEP_INHIBIT_CREW_ALERT ) == 1) crt->TextGrid( 20, 4, "SRB SEP INH", crt->DEUATT_OVERBRIGHT | crt->DEUATT_FLASHING );
			if (ReadCOMPOOL_IS( SCP_ET_AUTO_SEP_INHIBIT_CREW_ALERT ) == 1) crt->TextGrid( 21, 6, "ET SEP INH", crt->DEUATT_OVERBRIGHT );
			//if (ReadCOMPOOL_IS( SCP_SEL_ET_SEP_MNL_ENABLE ) == 1) crt->TextGrid( 21, 8, "ET SEP MAN", crt->DEUATT_OVERBRIGHT );

			if (ReadCOMPOOL_SS( SCP_FIRST_EO_VI ) != 0.0)
			{
				crt->TextGrid( 35, 23, "1ST EO VI" );
				crt->NumberGrid( 45, 23, ReadCOMPOOL_SS( SCP_FIRST_EO_VI ), 5, 0 );
			}
			if (ReadCOMPOOL_SS( SCP_SECOND_EO_VI ) != 0.0)
			{
				
				crt->TextGrid( 35, 24, "2ND EO VI", crt->DEUATT_OVERBRIGHT );
				crt->NumberGrid( 45, 24, ReadCOMPOOL_SS( SCP_SECOND_EO_VI ), 5, 0, crt->DEUATT_OVERBRIGHT );
			}
		}

		crt->Text( static_cast<short>(ReadCOMPOOL_IS( SCP_A1_STATE_X )) + 512, static_cast<short>(ReadCOMPOOL_IS( SCP_A1_STATE_Y )) + 366, "\x7F", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );
		crt->Circle( static_cast<short>(ReadCOMPOOL_IS( SCP_A1_PRED_X )) + 512, static_cast<short>(ReadCOMPOOL_IS( SCP_A1_PRED_Y )) + 366, 5, crt->DEUATT_OVERBRIGHT );
		return;
	}

	void GNCDisplays::OnPaint_XXXXXXTRAJ2( CRT_Interface* crt ) const
	{
		// title
		unsigned short DISP_TITLE = ReadCOMPOOL_IS( SCP_DISP_TITLE );
		if (DISP_TITLE == 6) crt->TextGrid( 18, 1, "ASCENT" );
		else if (DISP_TITLE == 7) crt->TextGrid( 21, 1, "TAL" );
		else if (DISP_TITLE == 8) crt->TextGrid( 21, 1, "ATO" );


		// solid lines
		for (int i = 1; i <= 13; i++)
		{
			short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A2_SOLID_LINE, i, 1, 13, 4 ));
			short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A2_SOLID_LINE, i, 2, 13, 4 ));
			short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A2_SOLID_LINE, i, 3, 13, 4 ));
			short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_A2_SOLID_LINE, i, 4, 13, 4 ));
			crt->Line( x1, y1, x2, y2 );
		}

		// character strings
		for (int i = 1; i <= 7; i++)
		{
			SCP_DISPCHAR dc;
			ReadCOMPOOL_ASTRUCT( SCP_A2_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 7 );
			char txt[5];
			memset( txt, 0, 5 );
			memcpy( txt, dc.TXT, 4 );
			crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
		}


		crt->NumberGrid( 45, 18, ReadCOMPOOL_IS( SCP_K_CMD ), 3 );


		crt->NumberGrid( 45, 19, ReadCOMPOOL_IS( SCP_PRPLT ), 2 );


		if (ReadCOMPOOL_IS( SCP_CONT_SERC ) == 1) crt->TextGrid( 3, 13, "*" );
		if (ReadCOMPOOL_IS( SCP_ENA_RCS_CNTL ) == 1) crt->TextGrid( 10, 13, "ON", crt->DEUATT_OVERBRIGHT );


		if (ReadCOMPOOL_IS( SCP_ET_AUTO_SEP_INHIBIT_CREW_ALERT ) == 1) crt->TextGrid( 21, 6, "ET SEP INH", crt->DEUATT_OVERBRIGHT );
		//if (ReadCOMPOOL_IS( SCP_SEL_ET_SEP_MNL_ENABLE ) == 1) crt->TextGrid( 21, 8, "ET SEP MAN", crt->DEUATT_OVERBRIGHT );


		if (ReadCOMPOOL_SS( SCP_FIRST_EO_VI ) != 0.0)
		{
			crt->TextGrid( 35, 23, "1ST EO VI" );
			crt->NumberGrid( 45, 23, ReadCOMPOOL_SS( SCP_FIRST_EO_VI ), 5, 0 );
		}
		if (ReadCOMPOOL_SS( SCP_SECOND_EO_VI ) != 0.0)
		{
				
			crt->TextGrid( 35, 24, "2ND EO VI", crt->DEUATT_OVERBRIGHT );
			crt->NumberGrid( 45, 24, ReadCOMPOOL_SS( SCP_SECOND_EO_VI ), 5, 0, crt->DEUATT_OVERBRIGHT );
		}


		if (0/*TODO ReadCOMPOOL_IS( SCP_CONT_2EO_START )*/ == 0)
		{
			if ((ReadCOMPOOL_IS( SCP_S_MECO ) == 1) && (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0)) crt->TextGrid( 19, 5, "FINE" );
		}
		else
		{
			//if (ReadCOMPOOL_IS( SCP_S_FCD ) == 1) crt->TextGrid( 19, 5, "FINE" );
		}


		if (ReadCOMPOOL_IS( SCP_S_BLANK_TMECO ) == 0)
		{
			char cbuf[16];

			float TGO = ReadCOMPOOL_SS( SCP_TGO );
			short VGO_min = static_cast<short>(TGO / 60);
			short VGO_sec = static_cast<short>(TGO) % 60;
			sprintf_s( cbuf, 16, "%2d", VGO_min );
			crt->TextGrid( 43, 6, cbuf );
			sprintf_s( cbuf, 16, "%02d", VGO_sec );
			crt->TextGrid( 46, 6, cbuf );

			float TMET_MECO = ReadCOMPOOL_SS( SCP_TMET_MECO );
			short TMET_MECO_min = static_cast<short>(TMET_MECO / 60);
			short TMET_MECO_sec = static_cast<short>(TMET_MECO) % 60;
			sprintf_s( cbuf, 16, "%2d", TMET_MECO_min );
			crt->TextGrid( 45, 21, cbuf );
			sprintf_s( cbuf, 16, "%02d", TMET_MECO_sec );
			crt->TextGrid( 48, 21, cbuf );
		}


		crt->Text( static_cast<short>(ReadCOMPOOL_IS( SCP_A2_VI_X )) + 512, 101, "\x06", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );


		crt->Text( static_cast<short>(ReadCOMPOOL_IS( SCP_A2_STATE_X )) + 512, static_cast<short>(ReadCOMPOOL_IS( SCP_A2_STATE_Y )) + 366, "\x7F", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );
		crt->Circle( static_cast<short>(ReadCOMPOOL_IS( SCP_A2_PRED_X_30 )) + 512, static_cast<short>(ReadCOMPOOL_IS( SCP_A2_PRED_Y_30 )) + 366, 5, crt->DEUATT_OVERBRIGHT );
		crt->Circle( static_cast<short>(ReadCOMPOOL_IS( SCP_A2_PRED_X_60 )) + 512, static_cast<short>(ReadCOMPOOL_IS( SCP_A2_PRED_Y_60 )) + 366, 5, crt->DEUATT_OVERBRIGHT );
		return;
	}

	void GNCDisplays::OnPaint_XXXXXMNVRYYYYY( CRT_Interface* crt ) const
	{
		/*int minutes, seconds;
		int TIMER[4];
		char cbuf[255];

		// title
		switch (MNVR_TITLE_IND)
		{
			case 1:
				crt->TextGrid( 16, 1, "OMS 1 MNVR EXEC" );
				break;
			case 2:
				crt->TextGrid( 16, 1, "ATO 1 MNVR EXEC" );
				break;
			case 3:
				crt->TextGrid( 16, 1, "AOA 1 MNVR EXEC" );
				break;
			case 4:
				crt->TextGrid( 16, 1, "OMS 2 MNVR EXEC" );
				break;
			case 5:
				crt->TextGrid( 16, 1, "ATO 2 MNVR EXEC" );
				break;
			case 6:
				crt->TextGrid( 18, 1, "AOA MNVR TRANS" );
				break;
			case 7:
				crt->TextGrid( 16, 1, "OMS 2 MNVR COAST" );
				break;
			case 8:
				crt->TextGrid( 16, 1, "ATO 2 MNVR COAST" );
				break;
			case 9:
				crt->TextGrid( 16, 1, "DEORB MNVR COAST" );
				break;
			case 10:
				crt->TextGrid( 16, 1, "DEORB MNVR EXEC" );
				break;
			case 11:
				crt->TextGrid( 16, 1, "ORBIT MNVR EXEC" );
				break;
			default:
				crt->TextGrid( 16, 1, "????? MNVR ?????" );
				break;
		}

		switch (TXX_FLAG)
		{
		case 0:
			sprintf_s( cbuf, 255, "FF" );
			break;
		case 1:
			sprintf_s( cbuf, 255, "TA" );
			break;
		case 2:
			sprintf_s( cbuf, 255, "TP" );
			break;
		case 3:
			sprintf_s( cbuf, 255, "TC   :" );
			break;
		default:
			sprintf_s( cbuf, 255, "??   :" );
			break;
		}
		crt->TextGrid( 22, 10, cbuf );

		if (TXX_FLAG >= 0 && TXX_FLAG <= 2)
		{ 
			//If TXX was reset to negative, then it is blanked
			if (TXX >= 0)
			{
				//Special MM 303 logic. This is how the BFS works, PFS would use the CRT timer
				double tempt;
				if (GetMajorMode() == 303)
				{
					tempt = TXX - ReadCOMPOOL_SD(SCP_CLOCK);
				}
				else
				{
					tempt = TXX;
				}

				minutes = (int)(abs(tempt) / 60);
				seconds = (int)(abs(tempt) - (60 * minutes));

				sprintf_s(cbuf, 255, "%.2d:%.2d", minutes, seconds);
				crt->TextGrid( 25, 10, cbuf );
			}
		}

		int timeDiff = max(0, static_cast<int>(tig - ReadCOMPOOL_SD(SCP_CLOCK) + 1.0));
		if(ST_CRT_TIMER) {
			TIMER[0]=timeDiff/86400;
			TIMER[1]=(timeDiff-TIMER[0]*86400)/3600;
			TIMER[2]=(timeDiff-TIMER[0]*86400-TIMER[1]*3600)/60;
			TIMER[3]=timeDiff-TIMER[0]*86400-TIMER[1]*3600-TIMER[2]*60;
			sprintf_s(cbuf, 255, "%03d/%02d:%02d:%02d", abs(TIMER[0]), abs(TIMER[1]), abs(TIMER[2]), abs(TIMER[3]));
			crt->TextGrid( 39, 2, cbuf );
		}

		crt->TextGrid(12, OMS+2, "*");

		crt->NumberGrid( 12, 6, static_cast<short>(ReadCOMPOOL_SS( SCP_TVR_ROLL )), 3 );

		crt->NumberSignGrid( 8, 8, Trim.data[0], 1, 1, '+', '-' );
		crt->NumberSignGrid( 8, 9, Trim.data[1], 1, 1, '+', '-' );
		crt->NumberSignGrid( 8, 10, Trim.data[2], 1, 1, '+', '-' );

		crt->NumberGrid( 7, 11, WT_DISP, 6, 0 );

		sprintf_s(cbuf, 255, "%03.0f/%02.0f:%02.0f:%04.1f", TIG[0], TIG[1], TIG[2], TIG[3]);
		crt->TextGrid( 4, 13, cbuf );

		if (PEG_MODE_4)
		{
			crt->NumberGrid( 13, 15, C1_DISP, 5, 0 );
			crt->NumberSignGrid( 11, 16, C2_DISP, 1, 4, '+', '-' );
			crt->NumberGrid( 11, 17, HTGT_DISP, 3, 3 );
			crt->NumberGrid( 11, 18, THETA_DISP, 3, 3 );
			crt->NumberSignGrid( 12, 19, PROP_DEP, 5, 0, '+', '-' );
		}

		if (PEG_MODE_4)
		{
			if (VGO_LVLH.x != 0.0 || VGO_LVLH.y != 0.0 || VGO_LVLH.z != 0.0)
			{
				crt->NumberSignGrid( 10, 21, VGO_LVLH.x, 4, 1, '+', '-' );
				crt->NumberSignGrid( 11, 22, VGO_LVLH.y, 3, 1, '+', '-' );
				crt->NumberSignGrid( 11, 23, VGO_LVLH.z, 3, 1, '+', '-' );
			}
		}
		else
		{
			crt->NumberSignGrid( 10, 21, EXT_DV_LVLH.x, 4, 1, '+', '-' );
			crt->NumberSignGrid( 11, 22, EXT_DV_LVLH.y, 3, 1, '+', '-' );
			crt->NumberSignGrid( 11, 23, EXT_DV_LVLH.z, 3, 1, '+', '-' );
		}

		if(MnvrLoad || GetMajorMode()==303) {
			double tmp = BurnAtt.data[ROLL];
			if (tmp < 0) tmp += 360;
			sprintf_s(cbuf, 255, "%03.0f", tmp);
			crt->TextGrid( 27, 4, cbuf );
			tmp = BurnAtt.data[PITCH];
			if (tmp < 0) tmp += 360;
			sprintf_s(cbuf, 255, "%03.0f", tmp);
			crt->TextGrid( 27, 5, cbuf );
			tmp = BurnAtt.data[YAW];
			if (tmp < 0) tmp += 360;
			sprintf_s(cbuf, 255, "%03.0f", tmp);
			crt->TextGrid( 27, 6, cbuf );
		}

		if(MnvrLoad) {
			crt->TextGrid( 2, 24, "LOAD" );

			if(bBurnMode)
			{
				if (!EXEC_CMD && timeDiff <= -BURN_ENABLE_WINDOW) crt->TextGrid( 47, 3, "EXEC", crt->DEUATT_FLASHING + crt->DEUATT_OVERBRIGHT );
			}
		}
		else crt->TextGrid( 2, 24, "LOAD", crt->DEUATT_FLASHING );

		OrbitDAP::DAP_CONTROL_MODE dapMode = pOrbitDAP->GetDAPMode();

		if (MnvrToBurnAtt)
		{
			crt->TextGrid( 28, 7, "*" );
			double ttg;
			if ((dapMode == OrbitDAP::AUTO) && (BurnInProg == false) && (BurnCompleted == false) && (pOrbitDAP->GetTimeToAttitude( ttg ) == true))
			{
				char att = 0;
				if ((ttg > (timeDiff - 30)) || (((GetMajorMode() / 100) == 2) && (ttg > 3599))) att = crt->DEUATT_OVERBRIGHT;

				sprintf_s( cbuf, 255, "%02d:%02d", (int)ttg / 60, (int)ttg % 60 );
				crt->TextGrid( 26, 8, cbuf, att );
			}
		}
		// display selected DAP mode
		std::string text;
		switch(dapMode) {
		case OrbitDAP::AUTO:
			text = "AUTO";
			break;
		case OrbitDAP::INRTL:
			text = "INRTL";
			break;
		case OrbitDAP::LVLH:
			text = "LVLH";
			break;
		case OrbitDAP::FREE:
			text = "FREE";
			break;
		}
		if(MnvrToBurnAtt && dapMode != OrbitDAP::AUTO) crt->TextGrid( 30, 7, text.c_str(), crt->DEUATT_OVERBRIGHT );
		else crt->TextGrid( 30, 7, text.c_str() );

		if (GetMajorMode() >= 301 && REI_LS != 0)
		{
			crt->NumberGrid( 26, 9, REI_LS, 4, 0 );
		}

		if (ReadCOMPOOL_IS( SCP_OMSL_PITCH_STATUS ) == 1) crt->TextGrid( 27, 13, "M", crt->DEUATT_OVERBRIGHT );
		else if (ReadCOMPOOL_IS( SCP_OMSL_PITCH_STATUS ) == 2) crt->TextGrid( 27, 13, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (ReadCOMPOOL_IS( SCP_OMSL_YAW_STATUS ) == 1) crt->TextGrid( 27, 14, "M", crt->DEUATT_OVERBRIGHT );
		else if (ReadCOMPOOL_IS( SCP_OMSL_YAW_STATUS ) == 2) crt->TextGrid( 27, 14, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (ReadCOMPOOL_IS( SCP_OMSR_PITCH_STATUS ) == 1) crt->TextGrid( 33, 13, "M", crt->DEUATT_OVERBRIGHT );
		else if (ReadCOMPOOL_IS( SCP_OMSR_PITCH_STATUS ) == 2) crt->TextGrid( 33, 13, "\x1D", crt->DEUATT_OVERBRIGHT );

		if (ReadCOMPOOL_IS( SCP_OMSR_YAW_STATUS ) == 1) crt->TextGrid( 33, 14, "M", crt->DEUATT_OVERBRIGHT );
		else if (ReadCOMPOOL_IS( SCP_OMSR_YAW_STATUS ) == 2) crt->TextGrid( 33, 14, "\x1D", crt->DEUATT_OVERBRIGHT );
	
		if (ReadCOMPOOL_IS( SCP_OMSL_PITCH_STATUS ) != 1)
		{
			crt->NumberSignGrid( 23, 13, ReadCOMPOOL_SS( SCP_SOMSLPFDBK ), 1, 1, '+', '-' );
		}
		if (ReadCOMPOOL_IS( SCP_OMSL_YAW_STATUS ) != 1)
		{
			crt->NumberSignGrid( 23, 14, ReadCOMPOOL_SS( SCP_SOMSLYFDBK ), 1, 1, '+', '-' );
		}
		if (ReadCOMPOOL_IS( SCP_OMSR_PITCH_STATUS ) != 1)
		{
			crt->NumberSignGrid( 29, 13, ReadCOMPOOL_SS( SCP_SOMSRPFDBK ), 1, 1, '+', '-' );
		}
		if (ReadCOMPOOL_IS( SCP_OMSR_YAW_STATUS ) != 1)
		{
			crt->NumberSignGrid( 29, 14, ReadCOMPOOL_SS( SCP_SOMSRYFDBK ), 1, 1, '+', '-' );
		}

		int y = 18;
		if (ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL ) == 0) y = 16;
		else if (ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL ) == 1) y = 17;
		crt->TextGrid( 27, y, "*");

		y = 18;
		if (ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL ) == 0) y = 16;
		else if (ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL ) == 1) y = 17;
		crt->TextGrid( 32, y, "*");

		if (ReadCOMPOOL_IS( SCP_DRIVE_OMS ) == 1) crt->TextGrid( 32, 20, "*" );

		if (MnvrLoad)
		{
			int BurnTime[2];
			crt->NumberGrid( 45, 4, DV_TOT, 4, 1 );

			BurnTime[0]=(int)(TGO /60);
			BurnTime[1]=(int)(TGO -(BurnTime[0]*60));

			sprintf_s(cbuf, 255, "%2d:%.2d", BurnTime[0], BurnTime[1]);
			crt->TextGrid( 46, 5, cbuf );

			crt->NumberSignGrid( 43, 7, VGO_DISP.x, 4, 2, '+', '-' );
			crt->NumberSignGrid( 44, 8, VGO_DISP.y, 3, 2, '+', '-' );
			crt->NumberSignGrid( 44, 9, VGO_DISP.z, 3, 2, '+', '-' );
		}

		if (MnvrLoad && !Eq(TGT_HA, 0.0))
		{
			crt->NumberGrid( 41, 12, TGT_HA, 3, 0 );
			crt->NumberSignGrid( 47, 12, TGT_HP, 3, 0, '+', '-' );
		}

		{
			crt->NumberGrid( 41, 13, CUR_HA, 3, 0 );
			crt->NumberSignGrid( 47, 13, CUR_HP, 3, 0, '+', '-' );
		}*/
		return;
	}

	void GNCDisplays::OnPaint_UNIVPTG( CRT_Interface* crt ) const
	{
		/*char cbuf[255];
		double CUR_MNVR_COMPL[4];
		if ((DAPControlMode == INRTL) || (DAPControlMode == FREE)) ConvertSecondsToDDHHMMSS( STS()->GetMET(), CUR_MNVR_COMPL );
		else ConvertSecondsToDDHHMMSS( mnvrCompletionMET, CUR_MNVR_COMPL );
		sprintf_s( cbuf, 255, "%.2d:%.2d:%.2d", static_cast<int>(CUR_MNVR_COMPL[1]), static_cast<int>(CUR_MNVR_COMPL[2]), static_cast<int>(CUR_MNVR_COMPL[3]) );
		crt->TextGrid( 19, 2, cbuf );

		sprintf_s( cbuf, 255, "%.3d/%.2d:%.2d:%.2d", START_TIME[0], START_TIME[1], START_TIME[2], START_TIME[3] );
		crt->TextGrid( 15, 3, cbuf );

		crt->NumberGrid( 6, 6, MNVR_OPTION.data[PITCH], 3, 2 );
		crt->NumberGrid( 6, 7, MNVR_OPTION.data[ROLL], 3, 2 );
		crt->NumberGrid( 6, 8, MNVR_OPTION.data[YAW], 3, 2 );

		crt->NumberGrid( 11, 11, TGT_ID, 3 );

		unsigned char att = RA_DEC_flash ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL;
		crt->NumberGrid( 10, 13, RA, 3, 3, att );
		crt->NumberSignGrid( 10, 14, DEC, 2, 3, '+', '-', att );

		att = LAT_LON_ALT_flash ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL;
		crt->NumberSignGrid( 10, 15, LAT, 2, 3, '+', '-', att );
		crt->NumberSignGrid( 9, 16, LON, 3, 3, '+', '-', att );
		crt->NumberSignGrid( 9, 17, _ALT, 5, 1, '+', '-', att );

		crt->NumberGrid( 15, 19, BODY_VECT, 1 );

		att = P_Y_flash ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL;
		crt->NumberGrid( 8, 21, P, 3, 2, att );
		crt->NumberGrid( 8, 22, Y, 3, 2, att );

		if (OM >= 0.0)
		{
			crt->NumberGrid( 8, 23, OM, 3, 2 );
		}

		if (CurManeuver.IsValid)
		{
			if (CurManeuver.Type == AttManeuver::MNVR)
			{
				crt->TextGrid( 30, 5, "*" );
			}
			else if (CurManeuver.Type == AttManeuver::TRK)
			{
				crt->TextGrid( 30, 6, "*" );
			}
			else
			{
				crt->TextGrid( 30, 7, "*" );
			}
		}
		if (FutManeuver.IsValid)
		{
			if (FutManeuver.Type == AttManeuver::MNVR)
			{
				crt->TextGrid( 34, 5, "*" );
			}
			else if (FutManeuver.Type == AttManeuver::TRK)
			{
				crt->TextGrid( 34, 6, "*" );
			}
			else
			{
				crt->TextGrid( 34, 7, "*" );
			}
		}

		if (ERRTOT == true) crt->TextGrid( 32, 12, "*" );// ERR TOT
		else crt->TextGrid( 32, 13, "*" );// ERR DAP

		crt->NumberGrid( 27, 16, CUR_ATT.data[ROLL], 3, 2 );
		crt->NumberGrid( 35, 16, CUR_ATT.data[PITCH], 3, 2 );
		crt->NumberGrid( 43, 16, CUR_ATT.data[YAW], 3, 2 );

		crt->NumberGrid( 27, 17, REQD_ATT.data[ROLL], 3, 2 );
		crt->NumberGrid( 35, 17, REQD_ATT.data[PITCH], 3, 2 );
		crt->NumberGrid( 43, 17, REQD_ATT.data[YAW], 3, 2 );

		crt->NumberSignGrid( 26, 18, ATT_ERR.data[ROLL], 3, 2, '+', '-' );
		crt->NumberSignGrid( 34, 18, ATT_ERR.data[PITCH], 3, 2, '+', '-' );
		crt->NumberSignGrid( 42, 18, ATT_ERR.data[YAW], 3, 2, '+', '-' );

		crt->NumberSignGrid( 26, 19, degAngularVelocity.data[ROLL], 2, 3, '+', '-' );
		crt->NumberSignGrid( 34, 19, degAngularVelocity.data[PITCH], 2, 3, '+', '-' );
		crt->NumberSignGrid( 42, 19, degAngularVelocity.data[YAW], 2, 3, '+', '-' );*/
		return;
	}

	void GNCDisplays::OnPaint_ENTRYTRAJ( CRT_Interface* crt ) const
	{
		bool BANK_FLAG = ReadCOMPOOL_IS( SCP_BANK_FLAG );
		char att = crt->DEUATT_NORMAL;
		unsigned int DISP_IND = ReadCOMPOOL_IS( SCP_DISP_IND );

		// title
		crt->NumberGrid( 29, 1, DISP_IND, 1 );

		if (DISP_IND == 1)
		{
			// solid lines
			for (int i = 1; i <= 12; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_SOLID_LINE, i, 1, 12, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_SOLID_LINE, i, 2, 12, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_SOLID_LINE, i, 3, 12, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_SOLID_LINE, i, 4, 12, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// dashed lines
			for (int i = 1; i <= 14; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_DASH_LINE, i, 1, 14, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_DASH_LINE, i, 2, 14, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_DASH_LINE, i, 3, 14, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E1_DASH_LINE, i, 4, 14, 4 ));
				crt->Line( x1, y1, x2, y2, crt->DEUATT_DASHED );
			}

			// character strings
			for (int i = 1; i <= 17; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_E1_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 17 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}
		else if (DISP_IND == 2)
		{
			// solid lines
			for (int i = 1; i <= 9; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_SOLID_LINE, i, 1, 9, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_SOLID_LINE, i, 2, 9, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_SOLID_LINE, i, 3, 9, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_SOLID_LINE, i, 4, 9, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// dashed lines
			for (int i = 1; i <= 6; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_DASH_LINE, i, 1, 6, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_DASH_LINE, i, 2, 6, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_DASH_LINE, i, 3, 6, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E2_DASH_LINE, i, 4, 6, 4 ));
				crt->Line( x1, y1, x2, y2, crt->DEUATT_DASHED );
			}

			// character strings
			for (int i = 1; i <= 15; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_E2_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 15 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}
		else if (DISP_IND == 3)
		{
			// solid lines
			for (int i = 1; i <= 9; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_SOLID_LINE, i, 1, 9, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_SOLID_LINE, i, 2, 9, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_SOLID_LINE, i, 3, 9, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_SOLID_LINE, i, 4, 9, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// dashed lines
			for (int i = 1; i <= 3; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_DASH_LINE, i, 1, 3, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_DASH_LINE, i, 2, 3, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_DASH_LINE, i, 3, 3, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E3_DASH_LINE, i, 4, 3, 4 ));
				crt->Line( x1, y1, x2, y2, crt->DEUATT_DASHED );
			}

			// character strings
			for (int i = 1; i <= 13; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_E3_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 13 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}
		else if (DISP_IND == 4)
		{
			// solid lines
			for (int i = 1; i <= 9; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_SOLID_LINE, i, 1, 9, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_SOLID_LINE, i, 2, 9, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_SOLID_LINE, i, 3, 9, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_SOLID_LINE, i, 4, 9, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// dashed lines
			for (int i = 1; i <= 10; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_DASH_LINE, i, 1, 10, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_DASH_LINE, i, 2, 10, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_DASH_LINE, i, 3, 10, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E4_DASH_LINE, i, 4, 10, 4 ));
				crt->Line( x1, y1, x2, y2, crt->DEUATT_DASHED );
			}

			// character strings
			for (int i = 1; i <= 13; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_E4_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 13 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}
		else //if (DISP_IND == 5)
		{
			// solid lines
			for (int i = 1; i <= 14; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_SOLID_LINE, i, 1, 14, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_SOLID_LINE, i, 2, 14, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_SOLID_LINE, i, 3, 14, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_SOLID_LINE, i, 4, 14, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// dashed lines
			for (int i = 1; i <= 10; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_DASH_LINE, i, 1, 10, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_DASH_LINE, i, 2, 10, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_DASH_LINE, i, 3, 10, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_E5_DASH_LINE, i, 4, 10, 4 ));
				crt->Line( x1, y1, x2, y2, crt->DEUATT_DASHED );
			}

			// character strings
			for (int i = 1; i <= 14; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_E5_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 14 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}

		// phugoid scale
		if (BANK_FLAG) att = crt->DEUATT_FLASHING;
		else att = crt->DEUATT_NORMAL;
		crt->Line( 170, 80, 490, 80, att );

		// TODO low-energy logic
		crt->TextGrid( 8, 10, "LO ENRGY" );
		crt->TextGrid( 10, 11, "INH" );

		// TODO alt sites
		//crt->TextGrid( 9, 12, "*" );

		// digital data
		crt->NumberSignGrid( 15, 5, static_cast<short>(ReadCOMPOOL_IS( SCP_BIAS_ITEM )), 2, '+', '-' );

		crt->NumberGrid( 14, 6, ReadCOMPOOL_SS( SCP_D_REF ), 2, 1 );

		crt->NumberGrid( 13, 7, ReadCOMPOOL_SS( SCP_QBAR ), 3, 1 );

		crt->NumberSignGrid( 13, 8, ReadCOMPOOL_SS( SCP_DELAZ ) * DEG, 2, 1, '+', '-' );


		crt->NumberSignGrid( 47, 16, ReadCOMPOOL_SS( SCP_NY ), 0, 3, 'R', 'L' );

		crt->NumberSignGrid( 47, 17, ReadCOMPOOL_SS( SCP_DRTI ), 0, 3, 'R', 'L' );

		crt->NumberSignGrid( 47, 18, ReadCOMPOOL_SS( SCP_DATRIM ), 1, 1, 'R', 'L' );

		crt->NumberSignGrid( 47, 19, -ReadCOMPOOL_SS( SCP_DRTRIM ), 1, 1, 'R', 'L' );

		crt->NumberSignGrid( 47, 21, ReadCOMPOOL_SS( SCP_DLRDOT ), 3, 0, '+', '-' );

		crt->NumberSignGrid( 47, 22, ReadCOMPOOL_SS( SCP_RDTREF ), 3, 0, '+', '-' );

		crt->NumberSignGrid( 47, 23, ReadCOMPOOL_SS( SCP_ROLLREF ), 3, 0, 'R', 'L' );

		if (ReadCOMPOOL_IS( SCP_REF_ROL_STAT ) == 1) crt->TextGrid( 51, 23, "\x1D", crt->DEUATT_OVERBRIGHT );

		crt->NumberSignGrid( 47, 24, ReadCOMPOOL_SS( SCP_ROLLCMD ), 3, 0, 'R', 'L' );

		// scale data
		{
			const short ACC_ALPHA_X = 82;
			short ACC_ALPHA_Y = ReadCOMPOOL_IS( SCP_ACC_ALPHA_Y );

			ACC_ALPHA_Y = 731 - ACC_ALPHA_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_ACC_ALPHA_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			crt->Text( ACC_ALPHA_X, ACC_ALPHA_Y, "\x0B", att );

			
			short COM_ALPHA_Y = ReadCOMPOOL_IS( SCP_COM_ALPHA_Y );

			COM_ALPHA_Y = 731 - COM_ALPHA_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_COM_ALPHA_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			crt->Text( ACC_ALPHA_X, COM_ALPHA_Y, "\x1E", att );
		}
		{
			const short DRAG_ACC_X = 98;
			short DRAG_ACC_Y = ReadCOMPOOL_IS( SCP_DRAG_ACC_Y );

			DRAG_ACC_Y = 731 - DRAG_ACC_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_DRAG_ACC_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			crt->Text( DRAG_ACC_X, DRAG_ACC_Y, "\x0C", att );


			short DRAG_REF_Y = ReadCOMPOOL_IS( SCP_DRAG_REF_Y );

			DRAG_REF_Y = 731 - DRAG_REF_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_DRAG_REF_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			crt->Text( DRAG_ACC_X, DRAG_REF_Y, "\x1F", att );
		}

		// phugoid scale
		{
			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_X_PHUGOID_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			crt->Text( ReadCOMPOOL_IS( SCP_X_PHUGOID_BK ), 80, "\x06", att );
		}

		// orbiter symbol
		{
			short SHUTTLE_X = ReadCOMPOOL_IS( SCP_SHUTTLE_X );
			short SHUTTLE_Y = ReadCOMPOOL_IS( SCP_SHUTTLE_Y );

			SHUTTLE_Y = 731 - SHUTTLE_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (BANK_FLAG) att |= crt->DEUATT_FLASHING;
			crt->Text( SHUTTLE_X, SHUTTLE_Y, "\x0F", att, 270.0 );
		}

		// drag symbol
		{
			short GUID_X = ReadCOMPOOL_IS( SCP_GUID_X );
			short GUID_Y = ReadCOMPOOL_IS( SCP_GUID_Y );

			GUID_Y = 731 - GUID_Y;// convert Y coordinate

			crt->Text( GUID_X, GUID_Y, "\x1A", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );
		}

		// orbiter and drag trailers
		for (int i = 1; i <= 6; i++)
		{
			short TRAILER_X = ReadCOMPOOL_AIS( SCP_TRAILER_X, i, 6 );
			short TRAILER_Y = ReadCOMPOOL_AIS( SCP_TRAILER_Y, i, 6 );

			TRAILER_Y = 731 - TRAILER_Y;// convert Y coordinate

			crt->Text( TRAILER_X, TRAILER_Y, "\x06", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );

			short GUID_TRAILER_X = ReadCOMPOOL_AIS( SCP_GUID_TRAILER_X, i, 6 );
			crt->Text( GUID_TRAILER_X, TRAILER_Y, "\x07", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );
		}
		return;
	}

	void GNCDisplays::OnPaint_VERTSIT( CRT_Interface* crt ) const
	{
		char att = crt->DEUATT_NORMAL;
		unsigned short disp = (ReadCOMPOOL_IS( SCP_ADV_FLAG ) == 0) ? 1 : 2;// HACK used to figure out display

		crt->NumberGrid( 27, 1, disp, 1 );

		if (disp == 1)
		{
			// solid lines
			for (int i = 1; i <= 10; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_SOLID_LINE, i, 1, 10, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_SOLID_LINE, i, 2, 10, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_SOLID_LINE, i, 3, 10, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_SOLID_LINE, i, 4, 10, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// dashed lines
			for (int i = 1; i <= 2; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_DASH_LINE, i, 1, 2, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_DASH_LINE, i, 2, 2, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_DASH_LINE, i, 3, 2, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V1_DASH_LINE, i, 4, 2, 4 ));
				crt->Line( x1, y1, x2, y2, crt->DEUATT_DASHED );
			}

			// character strings
			for (int i = 1; i <= 7; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_V1_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 7 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}
		else
		{
			crt->TextGrid( 19, 17, "ACCEL" );

			// solid lines
			for (int i = 1; i <= 6; i++)
			{
				short x1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V2_SOLID_LINE, i, 1, 6, 4 ));
				short y1 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V2_SOLID_LINE, i, 2, 6, 4 ));
				short x2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V2_SOLID_LINE, i, 3, 6, 4 ));
				short y2 = static_cast<short>(ReadCOMPOOL_A2SS( SCP_V2_SOLID_LINE, i, 4, 6, 4 ));
				crt->Line( x1, y1, x2, y2 );
			}

			// character strings
			for (int i = 1; i <= 7; i++)
			{
				SCP_DISPCHAR dc;
				ReadCOMPOOL_ASTRUCT( SCP_V2_CHAR_STRING, i, &dc, sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 7 );
				char txt[5];
				memset( txt, 0, 5 );
				memcpy( txt, dc.TXT, 4 );
				crt->Text( static_cast<short>(dc.X), static_cast<short>(dc.Y), txt );
			}
		}

		if (ReadCOMPOOL_IS( SCP_TG_END ) == 1) crt->TextGrid( 39, 18, "A/L", crt->DEUATT_FLASHING );

		// E/W scale
		{
			short SHUTTLE_ENER_Y = ReadCOMPOOL_IS( SCP_SHUTTLE_ENER_Y );
			const short ESYMCEN = 917;
			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_SHUTTLE_ENER_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			SHUTTLE_ENER_Y = 731 - SHUTTLE_ENER_Y;// convert Y coordinate

			crt->Text( ESYMCEN, SHUTTLE_ENER_Y, "\x0C", att );


			short NOM_ENERGY_Y = ReadCOMPOOL_IS( SCP_NOM_ENERGY_Y );
			const short ENOMX = 919;

			NOM_ENERGY_Y = 731 - NOM_ENERGY_Y;// convert Y coordinate

			crt->Text( ENOMX, NOM_ENERGY_Y, "-", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );


			short ENER_UL_Y = ReadCOMPOOL_IS( SCP_ENER_UL_Y );
			short ENER_LL_Y = ReadCOMPOOL_IS( SCP_ENER_LL_Y );
			const short ELIMX = 923;

			ENER_UL_Y = 731 - ENER_UL_Y;// convert Y coordinate
			ENER_LL_Y = 731 - ENER_LL_Y;// convert Y coordinate

			crt->Text( ELIMX, ENER_UL_Y, "\x7D", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );
			crt->Text( ELIMX, ENER_LL_Y, "\x7D", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE );


			short EMOH_ENER_Y = ReadCOMPOOL_IS( SCP_EMOH_ENER_Y );
			const short EMOH = 917;

			EMOH_ENER_Y = 731 - EMOH_ENER_Y;// convert Y coordinate

			crt->Text( EMOH, EMOH_ENER_Y, "\x1F" );
		}

		// theta scale
		{
			/*short THETA_Y = ReadCOMPOOL_IS( SCP_THETA_Y );
			const short TSYMCEN = 905;

			THETA_Y = 731 - THETA_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_SHUTTLE_THETA_FLAG ) == 1) att |= crt->DEUATT_FLASHING;
			crt->Text( TSYMCEN, THETA_Y, "\x0B", att );*/
		}

		// digital data
		crt->NumberGrid( 39, 15, ReadCOMPOOL_SS( SCP_DSBFBP ), 3, 0 );

		crt->NumberGrid( 39, 16, ReadCOMPOOL_IS( SCP_VS_SBC ), 3 );

		crt->NumberSignGrid( 30, 18, ReadCOMPOOL_SS( SCP_NY ), 0, 3, 'R', 'L' );

		crt->NumberSignGrid( 30, 19, ReadCOMPOOL_SS( SCP_DRTI ), 0, 3, 'R', 'L' );

		crt->NumberSignGrid( 30, 20, ReadCOMPOOL_SS( SCP_DATRIM ), 1, 1, 'R', 'L' );

		crt->NumberSignGrid( 30, 21, -ReadCOMPOOL_SS( SCP_DRTRIM ), 1, 1, 'R', 'L' );

		// orbiter symbol
		{
			short VSHUTTLE_X = ReadCOMPOOL_IS( SCP_VSHUTTLE_X );
			short VSHUTTLE_Y = ReadCOMPOOL_IS( SCP_VSHUTTLE_Y );

			VSHUTTLE_Y = 731 - VSHUTTLE_Y;// convert Y coordinate

			short DISP_ALT_DIS_ANGLE = ReadCOMPOOL_IS( SCP_DISP_ALT_DIS_ANGLE );
			crt->Text( VSHUTTLE_X, VSHUTTLE_Y, "\x0F", crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE, DISP_ALT_DIS_ANGLE );
		}

		// orbiter symbol (alpha/mach)
		{
			/*short RT1_SQUARE_X = ReadCOMPOOL_IS( SCP_RT1_SQUARE_X );
			short RT1_SQUARE_Y = ReadCOMPOOL_IS( SCP_RT1_SQUARE_Y );

			RT1_SQUARE_Y = 731 - RT1_SQUARE_Y;// convert Y coordinate

			att = crt->DEUATT_OVERBRIGHT | crt->DEUATT_LARGE;
			if (ReadCOMPOOL_IS( SCP_SHUTTLE_ALPHA_FLAG ) == 1) att |= crt->DEUATT_FLASHING;

			crt->Text( RT1_SQUARE_X, RT1_SQUARE_Y, "\x0F", att );*/
		}
		return;
	}

	void GNCDisplays::OnPaint_RTLSTRAJ2( CRT_Interface* crt ) const
	{
		// IO-32 version

		// TODO
		return;
	}

	void GNCDisplays::OnPaint_FCSDEDDISCO( CRT_Interface* crt ) const
	{
		// ACTIVE STRING HERE
		/*if(bFCSTestActive) {
			if(ElevonTargetIdx != FV3) crt->TextGrid( 39, 10, "*" );
			else crt->TextGrid( 49, 10, "*" );
		}


		// MODE LT
		if (ModeLT == true) crt->TextGrid( 27, 6, "*" );
		else crt->TextGrid( 27, 7, "*" );


		// FCS COMMAND
		char buff[16];
		PrintElevonPos( ElevonTarget, buff );
		crt->TextGrid( 29, 14, buff );
		crt->TextGrid( 29, 15, buff );
		crt->TextGrid( 29, 16, buff );
		crt->TextGrid( 29, 17, buff );
		PrintRudderPos( RudderTarget, buff );
		crt->TextGrid( 29, 18, buff );
		PrintSpeedbrakePos( SpeedbrakeTarget, buff );
		crt->TextGrid( 29, 19, buff );
		if (BodyflapDrive > 0.0) crt->TextGrid( 32, 20, "DN" );
		else if (BodyflapDrive < 0.0) crt->TextGrid( 32, 20, "UP" );

		// FCS ACTUAL POS
		double LOB = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
		double LIB = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
		double RIB = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
		double ROB = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
		double DRFB = ReadCOMPOOL_SS( SCP_DRFB );
		double DSBFB = ReadCOMPOOL_SS( SCP_DSBFBP );
		double DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );

		PrintElevonPos( LOB, buff );
		crt->TextGrid( 36, 14, buff );
		if (downarrow_ElevonLOB) crt->TextGrid( 41, 14, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintElevonPos( LIB, buff );
		crt->TextGrid( 36, 15, buff );
		if (downarrow_ElevonLIB) crt->TextGrid( 41, 15, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintElevonPos( RIB, buff );
		crt->TextGrid( 36, 16, buff );
		if (downarrow_ElevonRIB) crt->TextGrid( 41, 16, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintElevonPos( ROB, buff );
		crt->TextGrid( 36, 17, buff );
		if (downarrow_ElevonROB) crt->TextGrid( 41, 17, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintRudderPos( DRFB, buff );
		crt->TextGrid( 36, 18, buff );
		if (downarrow_Rudder) crt->TextGrid( 41, 18, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintSpeedbrakePos( DSBFB, buff );
		crt->TextGrid( 36, 19, buff );
		if (downarrow_Speedbrake) crt->TextGrid( 41, 19, "\x1D", crt->DEUATT_OVERBRIGHT );

		sprintf_s( buff, 6, "%05.1f", range( 0.0, fabs( (DBFOFB + 11.7) * 2.919708 ), 100.0 ) );
		crt->TextGrid( 36, 20, buff );*/
		return;
	}

	void GNCDisplays::BackgroundData_DISP18( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "GNC SYS SUMM 1" );

		// labels
		// RCS
		crt->TextGrid( 1, 3, "RCS  JETISOL" );
		crt->TextGrid( 1, 4, "MANFFAILVLV" );
		crt->TextGrid( 3, 5, "F1" );
		crt->TextGrid( 4, 6, "2" );
		crt->TextGrid( 4, 7, "3" );
		crt->TextGrid( 4, 8, "4" );
		crt->TextGrid( 4, 9, "5" );
		crt->TextGrid( 3, 10, "L1" );
		crt->TextGrid( 4, 11, "2" );
		crt->TextGrid( 4, 12, "3" );
		crt->TextGrid( 4, 13, "4" );
		crt->TextGrid( 4, 14, "5" );
		crt->TextGrid( 3, 15, "R1" );
		crt->TextGrid( 4, 16, "2" );
		crt->TextGrid( 4, 17, "3" );
		crt->TextGrid( 4, 18, "4" );
		crt->TextGrid( 4, 19, "5" );

		// SURF
		crt->TextGrid( 15, 4, "SURF" );
		crt->TextGrid( 24, 4, "POS" );
		crt->TextGrid( 30, 4, "MOM" );
		crt->TextGrid( 15, 5, "L OB" );
		crt->TextGrid( 17, 6, "IB" );
		crt->TextGrid( 15, 7, "R IB" );
		crt->TextGrid( 17, 8, "OB" );
		crt->TextGrid( 15, 9, "AIL" );
		crt->TextGrid( 15, 10, "RUD" );
		crt->TextGrid( 15, 11, "SPD BRK" );
		crt->TextGrid( 15, 12, "BDY FLP" );

		// DPS
		crt->TextGrid( 35, 4, "DPS" );
		crt->TextGrid( 42, 4, "1 2 3 4 5" );
		crt->TextGrid( 38, 5, "GPC" );
		crt->TextGrid( 35, 6, "MDM FF" );
		crt->TextGrid( 39, 7, "FA" );

		// FCS
		crt->TextGrid( 35, 10, "FCS" );
		crt->TextGrid( 39, 10, "CH 1 2 3 4" );

		// NAV
		crt->TextGrid( 35, 14, "NAV" );
		crt->TextGrid( 42, 14, "1 2 3 4" );
		crt->TextGrid( 37, 15, "IMU" );
		crt->TextGrid( 37, 16, "ACC" );
		crt->TextGrid( 37, 17, "RGA" );
		crt->TextGrid( 37, 18, "TAC" );
		crt->TextGrid( 37, 19, "MLS" );
		crt->TextGrid( 37, 20, "ADTA" );

		// CNTLR
		crt->TextGrid( 17, 16, "CNTLR  1 2 3" );
		crt->TextGrid( 17, 17, "RHC  L" );
		crt->TextGrid( 22, 18, "R" );
		crt->TextGrid( 22, 19, "A" );
		crt->TextGrid( 17, 20, "THC  L" );
		crt->TextGrid( 22, 21, "A" );
		crt->TextGrid( 17, 22, "SBTC L" );
		crt->TextGrid( 22, 23, "R" );


		// lines
		// RCS
		crt->Line( 28, 122, 256, 122 );
		crt->Line( 28, 257, 256, 257 );
		crt->Line( 28, 392, 256, 392 );

		// SURF
		crt->Line( 294, 122, 636, 122 );

		// DPS
		crt->Line( 674, 122, 978, 122 );

		// FCS
		crt->Line( 674, 284, 940, 284 );

		// NAV
		crt->Line( 674, 392, 940, 392 );

		// CNTRL
		crt->Line( 332, 446, 560, 446 );
		return;
	}

	void GNCDisplays::BackgroundData_DISP19( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "GNC SYS SUMM 2" );

		// labels
		// OMS
		crt->TextGrid( 1, 3, "OMS AFT QTY" );
		crt->TextGrid( 16, 3, "L" );
		crt->TextGrid( 22, 3, "R" );
		crt->TextGrid( 9, 4, "OXID" );
		crt->TextGrid( 11, 5, "FU" );
		crt->TextGrid( 30, 3, "OMS" );
		crt->TextGrid( 43, 3, "L" );
		crt->TextGrid( 49, 3, "R" );
		crt->TextGrid( 31, 4, "TK P" );
		crt->TextGrid( 38, 4, "HE" );
		crt->TextGrid( 36, 5, "OXID" );
		crt->TextGrid( 38, 6, "FU" );
		crt->TextGrid( 31, 7, "N2 TK" );
		crt->TextGrid( 39, 7, "P" );
		crt->TextGrid( 34, 8, "REG  P" );
		crt->TextGrid( 34, 9, "P  VLV" );
		crt->TextGrid( 30, 10, "ENG IN" );
		crt->TextGrid( 39, 10, "P" );
		crt->TextGrid( 36, 11, "OXID" );
		crt->TextGrid( 38, 12, "FU" );
		crt->TextGrid( 35, 13, "VLV 1" );
		crt->TextGrid( 39, 14, "2" );

		// RCS
		crt->TextGrid( 21, 7, "JETISOL" );
		crt->TextGrid( 1, 8, "RCS" );
		crt->TextGrid( 11, 8, "OXID" );
		crt->TextGrid( 17, 8, "FU" );
		crt->TextGrid( 20, 8, "FAIL VLV" );
		crt->TextGrid( 1, 9, "FWD" );
		crt->TextGrid( 6, 9, "HE P" );
		crt->TextGrid( 6, 10, "TK P" );
		crt->TextGrid( 7, 11, "QTY" );
		crt->TextGrid( 1, 12, "MANF" );
		crt->TextGrid( 7, 12, "1 P" );
		crt->TextGrid( 7, 13, "2 P" );
		crt->TextGrid( 7, 14, "3 P" );
		crt->TextGrid( 7, 15, "4 P" );
		crt->TextGrid( 7, 16, "5" );
		crt->TextGrid( 1, 17, "AFT" );
		crt->TextGrid( 6, 17, "HE P" );
		crt->TextGrid( 1, 18, "L" );
		crt->TextGrid( 6, 18, "TK P" );
		crt->TextGrid( 7, 19, "QTY" );
		crt->TextGrid( 1, 20, "MANF" );
		crt->TextGrid( 7, 20, "1 P" );
		crt->TextGrid( 7, 21, "2 P" );
		crt->TextGrid( 7, 22, "3 P" );
		crt->TextGrid( 7, 23, "4 P" );
		crt->TextGrid( 7, 24, "5" );
		crt->TextGrid( 45, 15, "JETISOL" );
		crt->TextGrid( 35, 16, "OXID" );
		crt->TextGrid( 41, 16, "FU" );
		crt->TextGrid( 44, 16, "FAIL VLV" );
		crt->TextGrid( 30, 17, "HE P" );
		crt->TextGrid( 28, 18, "R TK P" );
		crt->TextGrid( 31, 19, "QTY" );
		crt->TextGrid( 31, 20, "1 P" );
		crt->TextGrid( 31, 21, "2 P" );
		crt->TextGrid( 31, 22, "3 P" );
		crt->TextGrid( 31, 23, "4 P" );
		crt->TextGrid( 31, 24, "5" );


		// lines
		crt->Line( 199, 176, 199, 662 );
		crt->Line( 294, 176, 294, 662 );
		crt->Line( 389, 176, 389, 662 );
		crt->Line( 465, 176, 465, 662 );
		crt->Line( 541, 176, 541, 662 );
		crt->Line( 655, 392, 655, 662 );
		crt->Line( 750, 392, 750, 662 );
		crt->Line( 845, 392, 845, 662 );
		crt->Line( 921, 392, 921, 662 );

		crt->Line( 28, 176, 541, 176 );
		crt->Line( 28, 230, 541, 230 );
		crt->Line( 142, 311, 389, 311 );
		crt->Line( 541, 392, 997, 392 );
		crt->Line( 28, 446, 997, 446 );
		crt->Line( 142, 527, 389, 527 );
		crt->Line( 598, 527, 845, 527 );
		return;
	}

	void GNCDisplays::BackgroundData_DAPCONFIG( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "DAP CONFIG" );

		crt->TextGrid( 1, 4, "ROT RATE" );
		crt->TextGrid( 1, 5, "ATT DB" );
		crt->TextGrid( 1, 6, "RATE" );
		crt->TextGrid( 6, 6, "DB" );
		crt->TextGrid( 1, 7, "ROT PLS" );
		crt->TextGrid( 1, 8, "COMP" );
		crt->TextGrid( 1, 9, "P OPTION" );
		crt->TextGrid( 1, 10, "Y OPTION" );
		crt->TextGrid( 1, 11, "TRAN PLS" );

		crt->TextGrid( 1, 13, "RATE" );
		crt->TextGrid( 6, 13, "DB" );
		crt->TextGrid( 1, 14, "JET OPT" );
		crt->TextGrid( 1, 15, "# JETS" );
		crt->TextGrid( 1, 16, "ON" );
		crt->TextGrid( 4, 16, "TIME" );
		crt->TextGrid( 1, 17, "DELAY" );

		crt->TextGrid( 1, 19, "ROT RATE" );
		crt->TextGrid( 1, 20, "ATT DB" );
		crt->TextGrid( 1, 21, "RATE" );
		crt->TextGrid( 6, 21, "DB" );
		crt->TextGrid( 1, 22, "ROT PLS" );
		crt->TextGrid( 1, 23, "COMP" );
		crt->TextGrid( 1, 24, "CNTL ACC" );

		crt->TextGrid( 10, 3, "1" );
		crt->TextGrid( 17, 3, "\x7D\x7D" );

		crt->TextGrid( 10, 4, "10" );
		crt->TextGrid( 13, 4, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 5, "11" );
		crt->TextGrid( 14, 5, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 6, "12" );
		crt->TextGrid( 15, 6, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 7, "13" );
		crt->TextGrid( 14, 7, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 8, "14" );
		crt->TextGrid( 15, 8, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 9, "15" );
		crt->TextGrid( 10, 10, "15" );
		crt->TextGrid( 10, 11, "17" );
		crt->TextGrid( 14, 11, "\x7D\x7D\x7D\x7D\x7D" );
	
		crt->TextGrid( 10, 13, "18" );
		crt->TextGrid( 14, 13, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 14, "19" );
		crt->TextGrid( 10, 15, "20" );
		crt->TextGrid( 18, 15, "\x7D" );
		crt->TextGrid( 10, 16, "21" );
		crt->TextGrid( 15, 16, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 17, "22" );
		crt->TextGrid( 14, 17, "\x7D\x7D\x7D\x7D\x7D" );
	
		crt->TextGrid( 10, 19, "23" );
		crt->TextGrid( 13, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 20, "24" );
		crt->TextGrid( 13, 20, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 21, "25" );
		crt->TextGrid( 15, 21, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 22, "26" );
		crt->TextGrid( 14, 22, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 23, "27" );
		crt->TextGrid( 15, 23, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 10, 24, "28" );
		crt->TextGrid( 18, 24, "\x7D" );

		crt->TextGrid( 21, 3, "2" );
		crt->TextGrid( 28, 3, "\x7D\x7D" );

		crt->TextGrid( 21, 4, "30" );
		crt->TextGrid( 24, 4, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 5, "31" );
		crt->TextGrid( 25, 5, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 6, "32" );
		crt->TextGrid( 26, 6, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 7, "33" );
		crt->TextGrid( 25, 7, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 8, "34" );
		crt->TextGrid( 26, 8, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 9, "35" );
		crt->TextGrid( 21, 10, "36" );
		crt->TextGrid( 21, 11, "37" );
		crt->TextGrid( 25, 11, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 21, 13, "38" );
		crt->TextGrid( 25, 13, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 14, "39" );
		crt->TextGrid( 21, 15, "40" );
		crt->TextGrid( 29, 15, "\x7D" );
		crt->TextGrid( 21, 16, "41" );
		crt->TextGrid( 26, 16, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 17, "42" );
		crt->TextGrid( 25, 17, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 21, 19, "43" );
		crt->TextGrid( 24, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 20, "44" );
		crt->TextGrid( 24, 20, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 21, "45" );
		crt->TextGrid( 26, 21, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 22, "46" );
		crt->TextGrid( 25, 22, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 23, "47" );
		crt->TextGrid( 26, 23, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 21, 24, "48" );
		crt->TextGrid( 29, 24, "\x7D" );

		crt->TextGrid( 34, 3, "PRI" );
		crt->TextGrid( 32, 4, "50" );
		crt->TextGrid( 35, 4, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 5, "51" );
		crt->TextGrid( 36, 5, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 6, "52" );
		crt->TextGrid( 37, 6, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 7, "53" );
		crt->TextGrid( 36, 7, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 8, "54" );
		crt->TextGrid( 37, 8, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 9, "55" );
		crt->TextGrid( 32, 10, "56" );
		crt->TextGrid( 32, 11, "57" );
		crt->TextGrid( 36, 11, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 34, 12, "ALT" );
		crt->TextGrid( 32, 13, "58" );
		crt->TextGrid( 36, 13, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 14, "59" );
		crt->TextGrid( 32, 15, "60" );
		crt->TextGrid( 40, 15, "\x7D" );
		crt->TextGrid( 32, 16, "61" );
		crt->TextGrid( 37, 16, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 17, "62" );
		crt->TextGrid( 36, 17, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 34, 18, "VERN" );
		crt->TextGrid( 32, 19, "63" );
		crt->TextGrid( 35, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 20, "64" );
		crt->TextGrid( 35, 20, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 21, "65" );
		crt->TextGrid( 37, 21, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 22, "66" );
		crt->TextGrid( 36, 22, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 23, "67" );
		crt->TextGrid( 37, 23, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 32, 24, "68" );
		crt->TextGrid( 40, 24, "\x7D" );

		crt->TextGrid( 42, 3, "DAP EDIT" );
		crt->TextGrid( 42, 4, "3 DAP A\x7D\x7D" );
		crt->TextGrid( 42, 5, "4 DAP B\x7D\x7D" );
		crt->TextGrid( 42, 6, "5" );

		crt->TextGrid( 42, 10, "NOTCH FLTR" );
		crt->TextGrid( 43, 11, "ENA 6" );

		crt->TextGrid( 42, 13, "XJETS ROT" );
		crt->TextGrid( 43, 14, "ENA 7" );

		crt->TextGrid( 42, 16, "REBOOST" );
		crt->TextGrid( 43, 17, "8 CFG" );
		crt->TextGrid( 43, 18, "9 INTVL" );
		crt->TextGrid( 45, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );

		// lines
		crt->Line( 380, 68, 380, 662 );
		crt->Line( 589, 68, 589, 662 );
		crt->Line( 798, 230, 798, 662 );

		crt->Line( 798, 230, 997, 230 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC21( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "IMU ALIGN" );

		// labels
		crt->TextGrid( 2, 2, "IMU" );
		crt->TextGrid( 8, 3, "1" );
		crt->TextGrid( 13, 3, "2" );
		crt->TextGrid( 18, 3, "3" );
		crt->TextGrid( 1, 4, "STAT" );
		crt->TextGrid( 1, 5, "TEMP" );
		crt->TextGrid( 1, 6, "STBY" );
		crt->TextGrid( 7, 6, "21" );
		crt->TextGrid( 12, 6, "22" );
		crt->TextGrid( 17, 6, "23" );
		crt->TextGrid( 1, 7, "OPER" );
		crt->TextGrid( 8, 7, "4" );
		crt->TextGrid( 13, 7, "5" );
		crt->TextGrid( 18, 7, "6" );
		crt->TextGrid( 1, 8, "DES" );
		crt->TextGrid( 8, 8, "7" );
		crt->TextGrid( 13, 8, "8" );
		crt->TextGrid( 18, 8, "9" );

		crt->TextGrid( 2, 11, "ACC" );
		crt->TextGrid( 6, 12, "1" );
		crt->TextGrid( 12, 12, "2" );
		crt->TextGrid( 18, 12, "3" );
		crt->TextGrid( 2, 13, "X" );
		crt->TextGrid( 2, 14, "Y" );
		crt->TextGrid( 2, 15, "Z" );

		crt->TextGrid( 2, 17, "ANG" );
		crt->TextGrid( 7, 18, "1" );
		crt->TextGrid( 15, 18, "2" );
		crt->TextGrid( 23, 18, "3" );
		crt->TextGrid( 2, 19, "X" );
		crt->TextGrid( 2, 20, "Y" );
		crt->TextGrid( 2, 21, "Z" );
		crt->TextGrid( 1, 22, "\x7F""X" );
		crt->TextGrid( 1, 23, "\x7F""Y" );
		crt->TextGrid( 1, 24, "\x7F""Z" );

		crt->TextGrid( 31, 4, "ALIGN" );
		crt->TextGrid( 25, 5, "IMU 1 10" );
		crt->TextGrid( 36, 5, "REF STAR" );
		crt->TextGrid( 45, 5, "13" );
		crt->TextGrid( 29, 6, "2 11" );
		crt->TextGrid( 40, 6, "IMU" );
		crt->TextGrid( 45, 6, "14" );
		crt->TextGrid( 48, 6, "\x7D" );
		crt->TextGrid( 29, 7, "3 12" );
		crt->TextGrid( 35, 7, "TYPE" );
		crt->TextGrid( 40, 7, "15" );

		crt->TextGrid( 41, 9, "EXEC" );
		crt->TextGrid( 46, 9, "16" );
		crt->TextGrid( 41, 10, "TERM" );
		crt->TextGrid( 46, 10, "17" );

		crt->TextGrid( 36, 12, "IMU BITE MASK" );
		crt->TextGrid( 37, 13, "1" );
		crt->TextGrid( 46, 13, "24" );
		crt->TextGrid( 37, 14, "2" );
		crt->TextGrid( 46, 14, "25" );
		crt->TextGrid( 37, 15, "3" );
		crt->TextGrid( 46, 15, "26" );

		crt->TextGrid( 36, 20, "NAV \x7F""V" );
		crt->TextGrid( 43, 20, "THRESH" );
		crt->TextGrid( 38, 21, "18" );
		crt->TextGrid( 41, 21, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 38, 23, "MM" );
		crt->TextGrid( 41, 23, "READ" );
		crt->TextGrid( 46, 23, "19" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC22( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "S TRK/COAS CNTL" );

		// labels
		crt->TextGrid( 2, 3, "S TRK CNTL" );
		crt->TextGrid( 13, 3, "-Y" );
		crt->TextGrid( 17, 3, "-Z" );
		crt->TextGrid( 1, 4, "SELF-TEST" );
		crt->TextGrid( 13, 4, "1" );
		crt->TextGrid( 17, 4, "2" );
		crt->TextGrid( 1, 5, "STAR TRK" );
		crt->TextGrid( 13, 5, "3" );
		crt->TextGrid( 17, 5, "4" );
		crt->TextGrid( 1, 6, "TGT TRK" );
		crt->TextGrid( 13, 6, "5" );
		crt->TextGrid( 17, 6, "6" );
		crt->TextGrid( 1, 7, "BREAK TRK" );
		crt->TextGrid( 13, 7, "7" );
		crt->TextGrid( 17, 7, "8" );
		crt->TextGrid( 1, 8, "TERM/IDLE" );
		crt->TextGrid( 13, 8, "9" );
		crt->TextGrid( 16, 8, "10" );

		crt->TextGrid( 2, 11, "S TRK" );
		crt->TextGrid( 13, 11, "-Y" );
		crt->TextGrid( 23, 11, "-Z" );
		crt->TextGrid( 1, 12, "REQD" );
		crt->TextGrid( 6, 12, "ID" );
		crt->TextGrid( 11, 12, "11" );
		crt->TextGrid( 14, 12, "\x7D\x7D\x7D" );
		crt->TextGrid( 21, 12, "12" );
		crt->TextGrid( 24, 12, "\x7D\x7D\x7D" );
		crt->TextGrid( 1, 13, "TRK ID" );
		crt->TextGrid( 1, 14, "S PRES" );
		crt->TextGrid( 1, 15, "\x7F""ANG" );
		crt->TextGrid( 1, 16, "THOLD" );
		crt->TextGrid( 11, 16, "13" );
		crt->TextGrid( 16, 16, "\x7D" );
		crt->TextGrid( 21, 16, "14" );
		crt->TextGrid( 26, 16, "\x7D" );
		crt->TextGrid( 1, 17, "SHUTTER" );
		crt->TextGrid( 4, 18, "MAN OP" );
		crt->TextGrid( 11, 18, "15" );
		crt->TextGrid( 21, 18, "16" );
		crt->TextGrid( 1, 19, "STATUS" );

		crt->TextGrid( 27, 3, "S TABLE" );
		crt->TextGrid( 38, 3, "1" );
		crt->TextGrid( 44, 3, "2" );
		crt->TextGrid( 50, 3, "3" );
		crt->TextGrid( 26, 4, "TRK ID" );
		crt->TextGrid( 26, 5, "\x7F MIN" );
		crt->TextGrid( 26, 6, "ANG DIF" );
		crt->TextGrid( 30, 7, "ERR" );
		crt->TextGrid( 26, 8, "SEL" );
		crt->TextGrid( 37, 8, "17" );
		crt->TextGrid( 43, 8, "18" );
		crt->TextGrid( 49, 8, "19" );
		crt->TextGrid( 26, 9, "S TABLE CLR 20" );

		crt->TextGrid( 33, 11, "COAS" );
		crt->TextGrid( 32, 12, "REQD" );
		crt->TextGrid( 37, 12, "ID" );
		crt->TextGrid( 45, 12, "21" );
		crt->TextGrid( 49, 12, "\x7D\x7D\x7D" );
		crt->TextGrid( 32, 13, "\x7F""DEG X" );
		crt->TextGrid( 37, 14, "Y" );
		crt->TextGrid( 32, 15, "SIGHT MODE" );
		crt->TextGrid( 45, 15, "22" );
		crt->TextGrid( 32, 16, "ACCEPT" );
		crt->TextGrid( 45, 16, "23" );
		crt->TextGrid( 32, 17, "CAL MODE" );
		crt->TextGrid( 45, 17, "24" );
		crt->TextGrid( 32, 18, "DES" );
		crt->TextGrid( 45, 18, "25" );
		crt->TextGrid( 32, 19, "POS" );
		crt->TextGrid( 38, 19, "+X" );
		crt->TextGrid( 41, 19, "26" );
		crt->TextGrid( 46, 19, "-Z" );
		crt->TextGrid( 49, 19, "27" );
		crt->TextGrid( 32, 20, "\x7F""BIAS" );
		crt->TextGrid( 32, 21, "UPDATE" );
		crt->TextGrid( 40, 21, "28" );
		crt->TextGrid( 48, 21, "29" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC23( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 23, 1, "RCS" );

		// labels
		// TODO
		return;
	}

	void GNCDisplays::BackgroundData_SPEC25( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "RM ORBIT" );

		// labels
		// THC
		crt->TextGrid( 4, 7, "THC" );
		crt->TextGrid( 8, 7, "TX" );
		crt->TextGrid( 11, 7, "TY" );
		crt->TextGrid( 14, 7, "TZ DES" );
		crt->TextGrid( 4, 9, "L 1" );
		crt->TextGrid( 18, 9, "1" );
		crt->TextGrid( 6, 10, "2" );
		crt->TextGrid( 18, 10, "2" );
		crt->TextGrid( 6, 11, "3" );
		crt->TextGrid( 18, 11, "3" );
		crt->TextGrid( 4, 13, "A 1" );
		crt->TextGrid( 18, 13, "4" );
		crt->TextGrid( 6, 14, "2" );
		crt->TextGrid( 18, 14, "5" );
		crt->TextGrid( 6, 15, "3" );
		crt->TextGrid( 18, 15, "6" );

		// RHC
		crt->TextGrid( 24, 7, "RHC" );
		crt->TextGrid( 29, 7, "R" );
		crt->TextGrid( 34, 7, "P" );
		crt->TextGrid( 39, 7, "Y" );
		crt->TextGrid( 43, 7, "DES" );
		crt->TextGrid( 24, 9, "L 1" );
		crt->TextGrid( 44, 9, "7" );
		crt->TextGrid( 26, 10, "2" );
		crt->TextGrid( 44, 10, "8" );
		crt->TextGrid( 26, 11, "3" );
		crt->TextGrid( 44, 11, "9" );
		crt->TextGrid( 24, 13, "R 1" );
		crt->TextGrid( 43, 13, "10" );
		crt->TextGrid( 26, 14, "2" );
		crt->TextGrid( 43, 14, "11" );
		crt->TextGrid( 26, 15, "3" );
		crt->TextGrid( 43, 15, "12" );
		crt->TextGrid( 24, 17, "A 1" );
		crt->TextGrid( 43, 17, "13" );
		crt->TextGrid( 26, 18, "2" );
		crt->TextGrid( 43, 18, "14" );
		crt->TextGrid( 26, 19, "3" );
		crt->TextGrid( 43, 19, "15" );

		crt->TextGrid( 24, 24, "SW" );
		crt->TextGrid( 27, 24, "RM" );
		crt->TextGrid( 30, 24, "INH 16" );
		return;
	}

	void GNCDisplays::BackgroundData_RELNAV( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "REL NAV" );

		crt->TextGrid( 3, 2, "RNDZ NAV ENA 1" );

		crt->TextGrid( 3, 3, "KU ANT" );
		crt->TextGrid( 12, 3, "ENA 2" );
		crt->TextGrid( 3, 4, "MEAS" );
		crt->TextGrid( 12, 4, "ENA 3" );

		crt->TextGrid( 10, 5, "NAV" );
		crt->TextGrid( 3, 6, "SV SEL 4" );
		crt->TextGrid( 3, 7, "RNG" );
		crt->TextGrid( 3, 8, "R" );
		crt->TextGrid( 3, 8, "\x04" );
		crt->TextGrid( 3, 9, "\x5C" );
		crt->TextGrid( 3, 10, "Y" );
		crt->TextGrid( 3, 11, "Y" );
		crt->TextGrid( 3, 11, "\x04" );
		crt->TextGrid( 3, 12, "NODE" );

		crt->TextGrid( 20, 2, "SV" );
		crt->TextGrid( 23, 2, "UPDATE" );
		crt->TextGrid( 21, 3, "POS" );
		crt->TextGrid( 21, 4, "VEL" );

		crt->TextGrid( 21, 6, "RR" );

		crt->TextGrid( 18, 7, "RNG" );
		crt->TextGrid( 18, 8, "R" );
		crt->TextGrid( 18, 8, "\x04" );
		crt->TextGrid( 18, 9, "EL" );
		crt->TextGrid( 18, 10, "AZ" );
		crt->TextGrid( 18, 11, "\x15P" );
		crt->TextGrid( 18, 12, "\x15R" );

		crt->TextGrid( 14, 13, "FILTER" );
		crt->TextGrid( 3, 14, "S TRK 12" );
		crt->TextGrid( 15, 14, "RR" );
		crt->TextGrid( 18, 14, "13" );
		crt->TextGrid( 24, 14, "COAS" );
		crt->TextGrid( 29, 14, "14" );
		crt->TextGrid( 26, 15, "X" );
		crt->TextGrid( 26, 16, "Y" );
		crt->TextGrid( 3, 15, "STAT" );
		crt->TextGrid( 3, 16, "FLTR" );
		crt->TextGrid( 8, 16, "UPDATE" );
		crt->TextGrid( 16, 16, "15" );
		crt->TextGrid( 3, 17, "COVAR REINIT" );
		crt->TextGrid( 16, 17, "16" );

		crt->TextGrid( 11, 18, "RESID" );
		crt->TextGrid( 18, 18, "RATIO" );
		crt->TextGrid( 24, 18, "ACPT" );
		crt->TextGrid( 30, 18, "REJ" );

		crt->TextGrid( 3, 19, "RNG" );
		crt->TextGrid( 3, 20, "R" );
		crt->TextGrid( 3, 20, "\x04" );
		crt->TextGrid( 3, 21, "V/EL/Y" );
		crt->TextGrid( 3, 22, "H/AZ/X" );
		crt->TextGrid( 3, 23, "GPS" );

		crt->TextGrid( 39, 17, "EDIT");
		crt->TextGrid( 44, 17, "OVRD");
		crt->TextGrid( 37, 18, "AUT" );
		crt->TextGrid( 42, 18, "INH" );
		crt->TextGrid( 47, 18, "FOR" );
		crt->TextGrid( 37, 19, "17" );
		crt->TextGrid( 42, 19, "18" );
		crt->TextGrid( 47, 19, "19" );
		crt->TextGrid( 37, 20, "20" );
		crt->TextGrid( 42, 20, "21" );
		crt->TextGrid( 47, 20, "22" );
		crt->TextGrid( 37, 21, "23" );
		crt->TextGrid( 42, 21, "24" );
		crt->TextGrid( 47, 21, "25" );
		crt->TextGrid( 37, 23, "42" );
		crt->TextGrid( 42, 23, "43" );
		crt->TextGrid( 47, 23, "44" );

		crt->TextGrid( 37, 3, "AVG G ON" );
		crt->TextGrid( 49, 3, "5" );

		crt->TextGrid( 42, 4, "GPS" );
		crt->TextGrid( 38, 5, "STAT" );
		crt->TextGrid( 44, 5, "P 1\x7B" );
		crt->TextGrid( 49, 5, "DES" );
		crt->TextGrid( 35, 6, "1" );
		crt->TextGrid( 49, 6, "31" );
		crt->TextGrid( 35, 7, "2" );
		crt->TextGrid( 49, 7, "32" );
		crt->TextGrid( 35, 8, "3" );
		crt->TextGrid( 49, 8, "33" );

		crt->TextGrid( 38, 9, "SV" );
		crt->TextGrid( 41, 9, "TRANSFER" );
		crt->TextGrid( 36, 10, "FLTR" );
		crt->TextGrid( 41, 10, "MINUS PROP" );
		crt->TextGrid( 37, 11, "POS" );
		crt->TextGrid( 37, 12, "VEL" );
		crt->TextGrid( 36, 13, "FLTR" );
		crt->TextGrid( 41, 13, "TO" );
		crt->TextGrid( 44, 13, "PROP" );
		crt->TextGrid( 50, 13, "8" );
		crt->TextGrid( 36, 14, "PROP" );
		crt->TextGrid( 41, 14, "TO" );
		crt->TextGrid( 44, 14, "FLTR" );
		crt->TextGrid( 50, 14, "9" );
		crt->TextGrid( 36, 15, "ORB" );
		crt->TextGrid( 41, 15, "TO TGT" );
		crt->TextGrid( 49, 15, "10" );
		crt->TextGrid( 36, 16, "TGT" );
		crt->TextGrid( 41, 16, "TO ORB" );
		crt->TextGrid( 49, 16, "11" );

		// lines
		crt->Line( 665, 95, 665, 446 );

		crt->Line( 665, 95, 988, 95 );
		crt->Line( 665, 230, 988, 230 );
		crt->Line( 28, 338, 665, 338 );
		crt->Line( 665, 446, 988, 446 );
		return;
	}

	void GNCDisplays::BackgroundData_ORBITTGT( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "ORBIT TGT" );

		crt->TextGrid( 2, 3, "MNVR" );
		crt->TextGrid( 12, 3, "TIG" );
		crt->TextGrid( 23, 3, "\x7FVX" );
		crt->TextGrid( 30, 3, "\x7FVY" );
		crt->TextGrid( 37, 3, "\x7FVZ" );
		crt->TextGrid( 45, 3, "\x7FVT" );
		crt->TextGrid( 27, 5, "PRED" );
		crt->TextGrid( 32, 5, "MATCH=" );

		crt->TextGrid( 2, 7, "INPUTS" );
		crt->TextGrid( 2, 8, "1 TGT NO" );
		crt->TextGrid( 2, 9, "2 T1 TIG" );
		crt->TextGrid( 24, 8, "\x7D\x7D" );

		crt->TextGrid( 14, 9, "\x7D\x7D\x7D" );
		crt->TextGrid( 18, 9, "\x7D\x7D" );
		crt->TextGrid( 21, 9, "\x7D\x7D" );
		crt->TextGrid( 24, 9, "\x7D\x7D" );

		crt->TextGrid( 2, 10, "6" );
		crt->TextGrid( 6, 10, "EL" );
		crt->TextGrid( 20, 10, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 11, "7" );
		crt->TextGrid( 6, 11, "\x7FX/DNRNG" );
		crt->TextGrid( 19, 11, "\x01" );
		crt->TextGrid( 19, 11, "\x02" );
		crt->TextGrid( 2, 12, "8" );
		crt->TextGrid( 6, 12, "\x7FY" );
		crt->TextGrid( 19, 12, "\x01" );
		crt->TextGrid( 19, 12, "\x02" );
		crt->TextGrid( 2, 13, "9" );
		crt->TextGrid( 6, 13, "\x7FZ/\x7FH" );
		crt->TextGrid( 19, 13, "\x01" );
		crt->TextGrid( 19, 13, "\x02" );
		for (int y = 14;y <= 16;y++) crt->TextGrid( 7, y, "\x04" );
		crt->TextGrid( 1, 14, "10" );
		crt->TextGrid( 6, 14, "\x7FX" );
		crt->TextGrid( 19, 14, "\x01" );
		crt->TextGrid( 19, 14, "\x02" );
		crt->TextGrid( 1, 15, "11" );
		crt->TextGrid( 6, 15, "\x7FY" );
		crt->TextGrid( 19, 15, "\x01" );
		crt->TextGrid( 19, 15, "\x02" );
		crt->TextGrid( 1, 16, "12" );
		crt->TextGrid( 6, 16, "\x7FZ" );
		crt->TextGrid( 19, 16, "\x01" );
		crt->TextGrid( 19, 16, "\x02" );

		crt->TextGrid( 1, 17, "13" );
		crt->TextGrid( 4, 17, "T2 TIG" );
		crt->TextGrid( 14, 17, "\x7D\x7D\x7D" );
		crt->TextGrid( 18, 17, "\x7D\x7D" );
		crt->TextGrid( 21, 17, "\x7D\x7D" );
		crt->TextGrid( 24, 17, "\x7D\x7D" );

		crt->TextGrid( 1, 18, "17" );
		crt->TextGrid( 6, 18, "\x7FT" );
		crt->TextGrid( 19, 18, "\x01" );
		crt->TextGrid( 19, 18, "\x02" );
		crt->TextGrid( 20, 18, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 1, 19, "18" );
		crt->TextGrid( 6, 19, "\x7FX" );
		crt->TextGrid( 19, 19, "\x01" );
		crt->TextGrid( 19, 19, "\x02" );
		crt->TextGrid( 20, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 1, 20, "19" );
		crt->TextGrid( 6, 20, "\x7FY" );
		crt->TextGrid( 19, 20, "\x01" );
		crt->TextGrid( 19, 20, "\x02" );
		crt->TextGrid( 1, 21, "20" );
		crt->TextGrid( 6, 21, "\x7FZ" );
		crt->TextGrid( 19, 21, "\x01" );
		crt->TextGrid( 19, 21, "\x02" );

		crt->TextGrid( 1, 22, "21" );
		crt->TextGrid( 4, 22, "BASE" );
		crt->TextGrid( 9, 22, "TIME" );
		crt->TextGrid( 14, 22, "\x7D\x7D\x7D" );
		crt->TextGrid( 18, 22, "\x7D\x7D" );
		crt->TextGrid( 21, 22, "\x7D\x7D" );
		crt->TextGrid( 24, 22, "\x7D\x7D" );

		crt->TextGrid( 38, 7, "CONTROLS" );
		crt->TextGrid( 38, 8, "T2" );
		crt->TextGrid( 41, 8, "TO" );
		crt->TextGrid( 44, 8, "T1" );
		crt->TextGrid( 49, 8, "25" );

		crt->TextGrid( 49, 9, "26" );
		crt->TextGrid( 38, 10, "COMPUTE T1" );
		crt->TextGrid( 49, 10, "28" );
		crt->TextGrid( 38, 11, "COMPUTE T2" );
		crt->TextGrid( 49, 11, "29" );

		crt->TextGrid( 36, 17, "ORBITER" );
		crt->TextGrid( 45, 17, "STATE" );
		crt->TextGrid( 39, 19, "X" );
		crt->TextGrid( 39, 20, "Y" );
		crt->TextGrid( 39, 21, "Z" );
		crt->TextGrid( 38, 22, "VX" );
		crt->TextGrid( 38, 23, "VY" );
		crt->TextGrid( 38, 24, "VZ" );

		crt->Line( 664, 662, 664, 446 );
		crt->Line( 664, 446, 997, 446 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC40( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "SENSOR TEST" );

		// labels
		crt->TextGrid( 12, 3, "DES STAT" );
		crt->TextGrid( 22, 3, "RNG" );
		crt->TextGrid( 30, 3, "AZ" );
		crt->TextGrid( 36, 3, "EL" );

		crt->TextGrid( 6, 4, "MLS" );
		crt->TextGrid( 10, 4, "1" );
		crt->TextGrid( 10, 5, "2" );
		crt->TextGrid( 10, 6, "3" );
		crt->TextGrid( 13, 4, "1" );
		crt->TextGrid( 13, 5, "2" );
		crt->TextGrid( 13, 6, "3" );

		crt->TextGrid( 12, 13, "DES STAT" );
		crt->TextGrid( 22, 13, "ALT" );

		crt->TextGrid( 6, 14, "RA" );
		crt->TextGrid( 10, 14, "1" );
		crt->TextGrid( 10, 15, "2" );
		crt->TextGrid( 13, 14, "7" );
		crt->TextGrid( 13, 15, "8" );

		crt->TextGrid( 12, 17, "DES" );
		crt->TextGrid( 23, 17, "X" );
		crt->TextGrid( 31, 17, "Y" );

		crt->TextGrid( 6, 18, "AA" );
		crt->TextGrid( 10, 18, "1" );
		crt->TextGrid( 10, 19, "2" );
		crt->TextGrid( 10, 20, "3" );
		crt->TextGrid( 10, 21, "3" );
		crt->TextGrid( 13, 18, "1" );
		crt->TextGrid( 13, 19, "2" );
		crt->TextGrid( 13, 20, "3" );
		crt->TextGrid( 13, 21, "3" );

		crt->TextGrid( 16, 23, "START 13" );
		crt->TextGrid( 27, 23, "STOP" );
		crt->TextGrid( 32, 23, "14" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC41( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "RGA/ADTA/RCS" );

		// labels
		crt->TextGrid( 4, 3, "DES STAT" );
		crt->TextGrid( 17, 3, "R" );
		crt->TextGrid( 25, 3, "P" );
		crt->TextGrid( 33, 3, "Y" );

		crt->TextGrid( 1, 4, "R1" );
		crt->TextGrid( 5, 4, "1" );
		crt->TextGrid( 1, 5, "G2" );
		crt->TextGrid( 5, 5, "2" );
		crt->TextGrid( 1, 6, "A3" );
		crt->TextGrid( 5, 6, "3" );
		crt->TextGrid( 2, 7, "4" );
		crt->TextGrid( 5, 7, "4" );

		crt->TextGrid( 4, 9, "DES STAT" );
		crt->TextGrid( 16, 9, "PS" );
		crt->TextGrid( 23, 9, "P\x10""C" );
		crt->TextGrid( 31, 9, "P\x10U" );
		crt->TextGrid( 39, 9, "P\x10L" );
		crt->TextGrid( 48, 9, "T" );

		crt->TextGrid( 1, 10, "A1" );
		crt->TextGrid( 5, 10, "5" );
		crt->TextGrid( 1, 11, "D3" );
		crt->TextGrid( 5, 11, "6" );
		crt->TextGrid( 1, 12, "T2" );
		crt->TextGrid( 5, 12, "7" );
		crt->TextGrid( 1, 13, "A4" );
		crt->TextGrid( 5, 13, "8" );

		crt->TextGrid( 1, 15, "TEST" );
		crt->TextGrid( 8, 15, "HI 9" );
		crt->TextGrid( 16, 15, "LOW 10" );
		crt->TextGrid( 26, 15, "STOP" );
		crt->TextGrid( 31, 15, "11" );

		crt->TextGrid( 21, 18, "RCS DRIVERS" );
		crt->TextGrid( 5, 20, "RJDF" );
		crt->TextGrid( 12, 20, "12" );
		crt->TextGrid( 5, 21, "RJDA-A" );
		crt->TextGrid( 12, 21, "13" );
		crt->TextGrid( 9, 22, "-B" );
		crt->TextGrid( 12, 22, "14" );

		crt->TextGrid( 20, 20, "TEST" );
		crt->TextGrid( 25, 20, "EXEC" );
		crt->TextGrid( 30, 20, "15" );
		crt->TextGrid( 20, 21, "CONTINUE" );
		crt->TextGrid( 30, 21, "16" );
		crt->TextGrid( 20, 22, "STOP" );
		crt->TextGrid( 30, 22, "17" );

		crt->TextGrid( 38, 20, "TEST" );
		crt->TextGrid( 38, 21, "JET" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC42( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "SWITCH/SURF" );

		// labels
		crt->TextGrid( 2, 6, "FCS" );
		crt->TextGrid( 2, 7, "CH" );
		crt->TextGrid( 10, 3, "ORIDE DES" );
		crt->TextGrid( 25, 3, "ORIDE DES" );
		crt->TextGrid( 7, 4, "1 1" );
		crt->TextGrid( 17, 4, "1" );
		crt->TextGrid( 22, 4, "3 1" );
		crt->TextGrid( 32, 4, "7" );
		crt->TextGrid( 9, 5, "2" );
		crt->TextGrid( 17, 5, "2" );
		crt->TextGrid( 24, 5, "2" );
		crt->TextGrid( 32, 5, "8" );
		crt->TextGrid( 9, 6, "3" );
		crt->TextGrid( 17, 6, "3" );
		crt->TextGrid( 24, 6, "3" );
		crt->TextGrid( 32, 6, "9" );
		crt->TextGrid( 7, 7, "2 1" );
		crt->TextGrid( 17, 7, "4" );
		crt->TextGrid( 22, 7, "4 1" );
		crt->TextGrid( 31, 7, "10" );
		crt->TextGrid( 9, 8, "2" );
		crt->TextGrid( 17, 8, "5" );
		crt->TextGrid( 24, 8, "2" );
		crt->TextGrid( 31, 8, "11" );
		crt->TextGrid( 9, 9, "3" );
		crt->TextGrid( 17, 9, "6" );
		crt->TextGrid( 24, 9, "3" );
		crt->TextGrid( 31, 9, "12" );

		crt->TextGrid( 2, 14, "FCS" );
		crt->TextGrid( 2, 15, "MODE" );
		crt->TextGrid( 15, 11, "P" );
		crt->TextGrid( 27, 11, "R/Y" );
		crt->TextGrid( 35, 11, "SPD BRKBDY FLP" );
		crt->TextGrid( 10, 12, "AUT CSS" );
		crt->TextGrid( 22, 12, "AUT CSS" );
		crt->TextGrid( 35, 12, "AUT MAN" );
		crt->TextGrid( 44, 12, "AUT  DES" );
		crt->TextGrid( 7, 13, "L 1" );
		crt->TextGrid( 49, 13, "13" );
		crt->TextGrid( 9, 14, "2" );
		crt->TextGrid( 49, 14, "14" );
		crt->TextGrid( 9, 15, "3" );
		crt->TextGrid( 49, 15, "15" );
		crt->TextGrid( 7, 16, "R 1" );
		crt->TextGrid( 49, 16, "16" );
		crt->TextGrid( 9, 17, "2" );
		crt->TextGrid( 49, 17, "17" );
		crt->TextGrid( 9, 18, "3" );
		crt->TextGrid( 49, 18, "18" );

		crt->TextGrid( 2, 22, "SURF" );
		crt->TextGrid( 11, 20, "L OB" );
		crt->TextGrid( 17, 20, "L IB" );
		crt->TextGrid( 24, 20, "R IB" );
		crt->TextGrid( 30, 20, "R OB" );
		crt->TextGrid( 37, 20, "RUD" );
		crt->TextGrid( 42, 19, "SPD BDY" );
		crt->TextGrid( 42, 20, "BRK FLP" );
		crt->TextGrid( 9, 21, "1" );
		crt->TextGrid( 49, 21, "19" );
		crt->TextGrid( 9, 22, "2" );
		crt->TextGrid( 49, 22, "20" );
		crt->TextGrid( 9, 23, "3" );
		crt->TextGrid( 49, 23, "21" );
		crt->TextGrid( 9, 24, "4" );
		crt->TextGrid( 49, 24, "22" );

		// lines
		crt->Line( 142, 176, 655, 176 );
		crt->Line( 38, 271, 997, 271 );
		crt->Line( 142, 338, 997, 338 );
		crt->Line( 142, 419, 997, 419 );
		crt->Line( 38, 500, 997, 500 );
		crt->Line( 142, 554, 997, 554 );

		crt->Line( 199, 68, 199, 662 );
		crt->Line( 266, 311, 266, 500 );
		crt->Line( 304, 68, 304, 271 );
		crt->Line( 313, 500, 313, 662 );
		crt->Line( 342, 311, 342, 500 );
		crt->Line( 427, 271, 427, 662 );
		crt->Line( 484, 68, 484, 271 );
		crt->Line( 494, 311, 494, 500 );
		crt->Line( 560, 500, 560, 662 );
		crt->Line( 570, 311, 570, 500 );
		crt->Line( 589, 68, 589, 271 );
		crt->Line( 674, 271, 674, 662 );
		crt->Line( 807, 271, 807, 662 );
		crt->Line( 940, 271, 940, 662 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC43( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "CONTROLLERS" );

		// labels
		crt->TextGrid( 7, 4, "TXTYTZDES" );
		crt->TextGrid( 6, 5, "1" );
		crt->TextGrid( 14, 5, "1" );
		crt->TextGrid( 5, 6, "L2" );
		crt->TextGrid( 14, 6, "2" );
		crt->TextGrid( 1, 7, "THC  3" );
		crt->TextGrid( 14, 7, "3" );
		crt->TextGrid( 6, 8, "1" );
		crt->TextGrid( 14, 8, "4" );
		crt->TextGrid( 5, 9, "A2" );
		crt->TextGrid( 14, 9, "5" );
		crt->TextGrid( 6, 10, "3" );
		crt->TextGrid( 14, 10, "6" );
		crt->TextGrid( 6, 11, "1" );
		crt->TextGrid( 14, 11, "7" );
		crt->TextGrid( 5, 12, "L2" );
		crt->TextGrid( 14, 12, "8" );
		crt->TextGrid( 6, 13, "3" );
		crt->TextGrid( 14, 13, "9" );
		crt->TextGrid( 1, 14, "SPD  1" );
		crt->TextGrid( 13, 14, "10" );
		crt->TextGrid( 1, 15, "BK" );
		crt->TextGrid( 5, 15, "R2" );
		crt->TextGrid( 13, 15, "11" );
		crt->TextGrid( 6, 16, "3" );
		crt->TextGrid( 13, 16, "12" );
		crt->TextGrid( 6, 17, "1" );
		crt->TextGrid( 13, 17, "13" );
		crt->TextGrid( 5, 18, "L2" );
		crt->TextGrid( 13, 18, "14" );
		crt->TextGrid( 1, 19, "RUD  3" );
		crt->TextGrid( 13, 19, "15" );
		crt->TextGrid( 1, 20, "PED  1" );
		crt->TextGrid( 13, 20, "16" );
		crt->TextGrid( 5, 21, "R2" );
		crt->TextGrid( 13, 21, "17" );
		crt->TextGrid( 6, 22, "3" );
		crt->TextGrid( 13, 22, "18" );

		crt->TextGrid( 20, 7, "BDY FLP" );
		crt->TextGrid( 22, 8, "UPDNDES" );
		crt->TextGrid( 20, 9, "L1" );
		crt->TextGrid( 26, 9, "19" );
		crt->TextGrid( 17, 10, "SW  2" );
		crt->TextGrid( 26, 10, "20" );
		crt->TextGrid( 20, 11, "R1" );
		crt->TextGrid( 26, 11, "21" );
		crt->TextGrid( 21, 12, "2" );
		crt->TextGrid( 26, 12, "22" );

		crt->TextGrid( 38, 4, "R" );
		crt->TextGrid( 42, 4, "P" );
		crt->TextGrid( 46, 4, "Y  DES" );
		crt->TextGrid( 36, 5, "1" );
		crt->TextGrid( 49, 5, "23" );
		crt->TextGrid( 35, 6, "L2" );
		crt->TextGrid( 49, 6, "24" );
		crt->TextGrid( 36, 7, "3" );
		crt->TextGrid( 49, 7, "25" );
		crt->TextGrid( 36, 8, "1" );
		crt->TextGrid( 49, 8, "26" );
		crt->TextGrid( 30, 9, "RHC" );
		crt->TextGrid( 35, 9, "R2" );
		crt->TextGrid( 49, 9, "27" );
		crt->TextGrid( 36, 10, "3" );
		crt->TextGrid( 49, 10, "28" );
		crt->TextGrid( 36, 11, "1" );
		crt->TextGrid( 49, 11, "29" );
		crt->TextGrid( 35, 12, "A2" );
		crt->TextGrid( 49, 12, "30" );
		crt->TextGrid( 36, 13, "3" );
		crt->TextGrid( 49, 13, "31" );
		crt->TextGrid( 35, 14, "L1" );
		crt->TextGrid( 49, 14, "32" );
		crt->TextGrid( 30, 15, "RHC" );
		crt->TextGrid( 36, 15, "2" );
		crt->TextGrid( 49, 15, "33" );
		crt->TextGrid( 30, 16, "TRIM" );
		crt->TextGrid( 35, 16, "R1" );
		crt->TextGrid( 49, 16, "34" );
		crt->TextGrid( 36, 17, "2" );
		crt->TextGrid( 49, 17, "35" );
		crt->TextGrid( 35, 18, "L1" );
		crt->TextGrid( 49, 18, "36" );
		crt->TextGrid( 30, 19, "PNL" );
		crt->TextGrid( 36, 19, "2" );
		crt->TextGrid( 49, 19, "37" );
		crt->TextGrid( 30, 20, "TRIM" );
		crt->TextGrid( 35, 20, "R1" );
		crt->TextGrid( 49, 20, "38" );
		crt->TextGrid( 36, 21, "2" );
		crt->TextGrid( 49, 21, "39" );

		// lines
		crt->Line( 28, 122, 313, 122 );
		crt->Line( 104, 203, 313, 203 );
		crt->Line( 28, 284, 313, 284 );
		crt->Line( 104, 365, 313, 365 );
		crt->Line( 28, 446, 313, 446 );
		crt->Line( 104, 527, 313, 527 );

		crt->Line( 142, 95, 142, 608 );
		crt->Line( 180, 95, 180, 284 );
		crt->Line( 218, 95, 218, 284 );
		crt->Line( 256, 95, 256, 608 );


		crt->Line( 332, 230, 560, 230 );
		crt->Line( 389, 284, 560, 284 );

		crt->Line( 427, 203, 427, 338 );
		crt->Line( 465, 203, 465, 338 );
		crt->Line( 503, 203, 503, 338 );


		crt->Line( 579, 122, 997, 122 );
		crt->Line( 674, 203, 997, 203 );
		crt->Line( 674, 284, 997, 284 );
		crt->Line( 579, 365, 997, 365 );
		crt->Line( 674, 419, 997, 419 );
		crt->Line( 579, 473, 997, 473 );
		crt->Line( 674, 527, 997, 527 );

		crt->Line( 712, 95, 712, 581 );
		crt->Line( 788, 95, 788, 581 );
		crt->Line( 864, 95, 864, 581 );
		crt->Line( 940, 95, 940, 581 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC44( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "SWITCHES" );

		// labels
		crt->TextGrid( 30, 4, "ENTRY ROLL" );
		crt->TextGrid( 41, 4, "MODE" );
		crt->TextGrid( 32, 5, "LOW" );
		crt->TextGrid( 37, 5, "NO" );
		crt->TextGrid( 32, 6, "GAIN" );
		crt->TextGrid( 37, 6, "Y/J DES" );
		crt->TextGrid( 30, 7, "1" );
		crt->TextGrid( 30, 8, "2" );
		crt->TextGrid( 30, 9, "3" );
		crt->TextGrid( 30, 10, "4" );
		crt->TextGrid( 42, 7, "1" );
		crt->TextGrid( 42, 8, "2" );
		crt->TextGrid( 42, 9, "3" );
		crt->TextGrid( 42, 10, "4" );

		crt->TextGrid( 11, 20, "9 RCO" );

		// lines
		crt->Line( 608, 122, 608, 284 );
		crt->Line( 703, 122, 703, 284 );
		crt->Line( 789, 122, 789, 284 );

		crt->Line( 579, 176, 845, 176 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC45( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 19, 1, "NWS CHECK" );

		// labels
		crt->TextGrid( 9, 4, "SYS" );
		crt->TextGrid( 9, 5, "SEL" );
		crt->TextGrid( 14, 3, "HYD" );
		crt->TextGrid( 14, 4, "PRESS" );
		crt->TextGrid( 14, 5, "HIGH" );

		crt->TextGrid( 21, 5, "ENABLE" );
		crt->TextGrid( 30, 5, "CURRENT" );
		crt->TextGrid( 41, 5, "POSITION" );

		crt->TextGrid( 4, 7, "NWS1" );
		crt->TextGrid( 4, 10, "NWS2" );

		crt->TextGrid( 22, 7, "A" );
		crt->TextGrid( 22, 8, "B" );

		crt->TextGrid( 22, 10, "A" );
		crt->TextGrid( 22, 11, "B" );

		crt->TextGrid( 41, 7, "A" );
		crt->TextGrid( 41, 8, "B" );
		crt->TextGrid( 41, 9, "C" );

		crt->TextGrid( 4, 14, "STIMULI" );
		crt->TextGrid( 4, 15, "ENABLE" );
		crt->TextGrid( 19, 15, "1" );
		crt->TextGrid( 4, 16, "RIGHT TURN (+) 2" );
		crt->TextGrid( 4, 17, "LEFT" );
		crt->TextGrid( 9, 17, "TURN" );
		crt->TextGrid( 15, 17, "(-) 3" );
		crt->TextGrid( 4, 18, "STOP" );
		crt->TextGrid( 19, 18, "4" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC50( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "HORIZ SIT" );

		// labels
		crt->TextGrid( 1, 2, "PTI" );
		crt->TextGrid( 11, 2, "1" );
		crt->TextGrid( 2, 3, "INDEX" );
		crt->TextGrid( 14, 2, "ALTM" );
		crt->TextGrid( 14, 3, "9" );
		crt->TextGrid( 17, 3, "\x7D\x7D" );
		crt->TextGrid( 20, 3, "\x7D\x7D" );

		crt->TextGrid( 1, 6, "41" );
		crt->TextGrid( 9, 6, "SITE" );
		crt->TextGrid( 14, 6, "\x7D\x7D" );

		crt->TextGrid( 1, 7, "PRI" );
		crt->TextGrid( 14, 7, "3" );

		crt->TextGrid( 1, 8, "SEC" );
		crt->TextGrid( 14, 8, "4" );

		crt->TextGrid( 1, 9, "TAC" );
		crt->TextGrid( 14, 9, "5" );

		crt->TextGrid( 1, 10, "GPS FOM" );
		crt->TextGrid( 14, 10, "RA" );
		crt->TextGrid( 13, 11, "46" );

		crt->TextGrid( 1, 12, "TAEM TGT" );
		crt->TextGrid( 1, 13, "G&N" );
		crt->TextGrid( 12, 13, "6" );

		crt->TextGrid( 1, 14, "HSI" );

		crt->TextGrid( 2, 15, "EP" );
		crt->TextGrid( 12, 15, "7" );

		crt->TextGrid( 1, 16, "AIM" );
		crt->TextGrid( 12, 16, "8" );

		crt->TextGrid( 1, 17, "S/B" );
		crt->TextGrid( 12, 17, "39" );

		crt->TextGrid( 43, 3, "NAV DELTA" );
		crt->TextGrid( 45, 4, "\x7FX" );
		crt->TextGrid( 48, 4, "10" );
		crt->TextGrid( 45, 5, "\x01" );
		crt->TextGrid( 45, 5, "\x02" );
		crt->TextGrid( 46, 5, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 45, 6, "\x7FY" );
		crt->TextGrid( 48, 6, "11" );
		crt->TextGrid( 45, 7, "\x01" );
		crt->TextGrid( 45, 7, "\x02" );
		crt->TextGrid( 45, 8, "\x7FZ" );
		crt->TextGrid( 48, 8, "12" );
		crt->TextGrid( 45, 9, "\x01" );
		crt->TextGrid( 45, 9, "\x02" );
		crt->TextGrid( 45, 10, "\x7FX" );
		crt->TextGrid( 46, 10, "\x04" );
		crt->TextGrid( 48, 10, "13" );
		crt->TextGrid( 45, 11, "\x01" );
		crt->TextGrid( 45, 11, "\x02" );
		crt->TextGrid( 46, 11, "\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 45, 12, "\x7FY" );
		crt->TextGrid( 46, 12, "\x04" );
		crt->TextGrid( 48, 12, "14" );
		crt->TextGrid( 45, 13, "\x01" );
		crt->TextGrid( 45, 13, "\x02" );
		crt->TextGrid( 45, 14, "\x7FZ" );
		crt->TextGrid( 46, 14, "\x04" );
		crt->TextGrid( 48, 14, "15" );
		crt->TextGrid( 45, 15, "\x01" );
		crt->TextGrid( 45, 15, "\x02" );
		crt->TextGrid( 45, 16, "LOAD" );
		crt->TextGrid( 50, 16, "16" );
		crt->TextGrid( 40, 17, "18" );
		crt->TextGrid( 43, 17, "\x7FT" );
		crt->TextGrid( 46, 17, "\x01" );
		crt->TextGrid( 46, 17, "\x02" );
		crt->TextGrid( 47, 17, "\x7D\x7D" );
		crt->TextGrid( 50, 17, "\x7D\x7D" );

		crt->TextGrid( 1, 18, "NAV" );
		crt->TextGrid( 1, 19, "TAC AZ" );
		crt->TextGrid( 4, 20, "RNG" );
		crt->TextGrid( 1, 21, "GPS" );
		crt->TextGrid( 1, 22, "DRAG H" );
		crt->TextGrid( 1, 23, "ADTA H" );
		crt->TextGrid( 7, 18, "RESID" );
		crt->TextGrid( 13, 18, "RATIO" );
		crt->TextGrid( 18, 18, "AUT" );
		crt->TextGrid( 18, 19, "19" );
		crt->TextGrid( 18, 21, "42" );
		crt->TextGrid( 18, 22, "22" );
		crt->TextGrid( 18, 23, "25" );
		crt->TextGrid( 21, 18, "INH" );
		crt->TextGrid( 21, 19, "20" );
		crt->TextGrid( 21, 21, "43" );
		crt->TextGrid( 21, 22, "23" );
		crt->TextGrid( 21, 23, "26" );
		crt->TextGrid( 24, 18, "FOR" );
		crt->TextGrid( 24, 19, "21" );
		crt->TextGrid( 24, 21, "44" );
		crt->TextGrid( 24, 22, "24" );
		crt->TextGrid( 24, 23, "27" );
		crt->TextGrid( 1, 24, "ADTA" );
		crt->TextGrid( 6, 24, "TO G&C" );
		crt->TextGrid( 18, 24, "28" );
		crt->TextGrid( 21, 24, "29" );
		crt->TextGrid( 24, 24, "30" );
		crt->TextGrid( 28, 18, "TAC 1" );
		crt->TextGrid( 29, 21, "DES 31" );
		crt->TextGrid( 36, 18, "TAC 2" );
		crt->TextGrid( 37, 21, "DES 32" );
		crt->TextGrid( 44, 18, "TAC 3" );
		crt->TextGrid( 45, 21, "DES 33" );
		crt->TextGrid( 29, 22, "ABS 34" );
		crt->TextGrid( 37, 22, "DELTA 35" );
		crt->TextGrid( 27, 23, "GPS S" );
		crt->TextGrid( 33, 23, "RN" );
		crt->TextGrid( 43, 23, "AZ" );
		crt->TextGrid( 27, 24, "AIF\x7DG S47" );
		crt->TextGrid( 38, 24, "48" );
		crt->TextGrid( 42, 24, "49" );

		// lines
		crt->Line( 28, 41, 247, 41 );
		crt->Line( 247, 41, 247, 122 );
		crt->Line( 28, 122, 247, 122 );

		crt->Line( 28, 311, 313, 311 );

		crt->Line( 28, 473, 997, 473 );
		crt->Line( 522, 581, 902, 581 );
		crt->Line( 522, 608, 997, 608 );
		crt->Line( 28, 635, 522, 635 );

		crt->Line( 142, 473, 142, 635 );
		crt->Line( 256, 473, 256, 635 );
		crt->Line( 351, 473, 351, 662 );
		crt->Line( 408, 473, 408, 662 );
		crt->Line( 465, 473, 465, 662 );
		crt->Line( 522, 473, 522, 662 );
		crt->Line( 693, 473, 693, 554 );
		crt->Line( 845, 473, 845, 554 );
		crt->Line( 893, 581, 893, 608 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC51( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "OVERRIDE" );

		// labels
		// ABORT MODE
		crt->TextGrid( 1, 3, "ABORT MODE" );
		crt->TextGrid( 2, 4, "TAL" );
		crt->TextGrid( 11, 4, "1" );
		crt->TextGrid( 2, 5, "ATO" );
		crt->TextGrid( 11, 5, "2" );
		crt->TextGrid( 1, 6, "ABORT" );
		crt->TextGrid( 11, 6, "3" );
		crt->TextGrid( 1, 7, "THROT MAX 4" );
		crt->TextGrid( 7, 8, "ABT 50" );
		crt->TextGrid( 7, 9, "NOM 51" );

		// ENTRY FCS
		crt->TextGrid( 30, 3, "ENTRY FCS" );
		crt->TextGrid( 19, 4, "ELEVON" );
		crt->TextGrid( 29, 4, "FILTER" );
		crt->TextGrid( 39, 4, "ATMOSPHERE" );
		crt->TextGrid( 17, 5, "AUTO" );
		crt->TextGrid( 23, 5, "17" );
		crt->TextGrid( 29, 5, "NOM 20" );
		crt->TextGrid( 39, 5, "NOM" );
		crt->TextGrid( 46, 5, "22" );
		crt->TextGrid( 17, 6, "FIXED 18" );
		crt->TextGrid( 29, 6, "ALT 21" );
		crt->TextGrid( 39, 6, "N POLE" );
		crt->TextGrid( 46, 6, "23" );
		crt->TextGrid( 19, 7, "SSME REPOS" );
		crt->TextGrid( 30, 7, "19" );
		crt->TextGrid( 39, 7, "S POLE" );
		crt->TextGrid( 46, 7, "24" );

		// IMU
		crt->TextGrid( 19, 8, "IMU STAT ATT DES" );
		crt->TextGrid( 20, 9, "1" );
		crt->TextGrid( 32, 9, "25" );
		crt->TextGrid( 20, 10, "2" );
		crt->TextGrid( 32, 10, "26" );
		crt->TextGrid( 20, 11, "3" );
		crt->TextGrid( 32, 11, "27" );

		// PRL
		crt->TextGrid( 44, 8, "PRL" );
		crt->TextGrid( 40, 9, "SYS AUT DES" );
		crt->TextGrid( 41, 10, "1" );
		crt->TextGrid( 44, 10, "28" );
		crt->TextGrid( 48, 10, "31" );
		crt->TextGrid( 41, 11, "2" );
		crt->TextGrid( 44, 11, "29" );
		crt->TextGrid( 48, 11, "32" );
		crt->TextGrid( 41, 12, "3" );
		crt->TextGrid( 44, 12, "30" );
		crt->TextGrid( 48, 12, "33" );

		// PRPLT DUMP
		crt->TextGrid( 4, 10, "PRPLT DUMP" );
		crt->TextGrid( 5, 11, "ICNCT 5" );
		crt->TextGrid( 1, 12, "OMS DUMP" );
		crt->TextGrid( 4, 13, "ARM" );
		crt->TextGrid( 11, 13, "6" );
		crt->TextGrid( 4, 14, "START  7" );
		crt->TextGrid( 4, 15, "STOP" );
		crt->TextGrid( 11, 15, "8" );
		crt->TextGrid( 2, 16, "9 QUAN/SIDE" );
		crt->TextGrid( 1, 17, "OMS DUMP TTG" );

		// ADTA
		crt->TextGrid( 19, 13, "ADTA" );
		crt->TextGrid( 29, 13, "H" );
		crt->TextGrid( 37, 13, "\x10" );
		crt->TextGrid( 43, 13, "M" );
		crt->TextGrid( 48, 13, "DES" );
		crt->TextGrid( 21, 14, "L 1" );
		crt->TextGrid( 48, 14, "34" );
		crt->TextGrid( 23, 15, "3" );
		crt->TextGrid( 48, 15, "35" );
		crt->TextGrid( 21, 16, "R 2" );
		crt->TextGrid( 48, 16, "36" );
		crt->TextGrid( 23, 17, "4" );
		crt->TextGrid( 48, 17, "37" );

		// ET SEP
		crt->TextGrid( 19, 18, "ET SEP" );
		crt->TextGrid( 21, 19, "AUTO" );
		crt->TextGrid( 29, 19, "38" );
		crt->TextGrid( 21, 20, "SEP" );
		crt->TextGrid( 29, 20, "39" );

		// ROLL MODE
		crt->TextGrid( 35, 18, "ROLL" );
		crt->TextGrid( 40, 18, "MODE" );
		crt->TextGrid( 36, 19, "AUTO SEL" );
		crt->TextGrid( 48, 19, "42" );
		crt->TextGrid( 36, 20, "WRAP" );
		crt->TextGrid( 41, 20, "MODE" );
		crt->TextGrid( 46, 20, "45" );

		// AFT RCS
		crt->TextGrid( 1, 20, "AFT RCS 13" );
		crt->TextGrid( 4, 21, "14" );
		crt->TextGrid( 7, 21, "TIME" );

		// ET UMB DR
		crt->TextGrid( 19, 21, "ET" );
		crt->TextGrid( 22, 21, "UMB DR" );
		crt->TextGrid( 21, 22, "CLOSE" );
		crt->TextGrid( 29, 22, "40" );

		// VENT DOOR CNTL
		crt->TextGrid( 35, 21, "VENT" );
		crt->TextGrid( 40, 21, "DOOR" );
		crt->TextGrid( 45, 21, "CNTL" );
		crt->TextGrid( 36, 22, "OPEN" );
		crt->TextGrid( 45, 22, "43" );
		crt->TextGrid( 36, 23, "CLOSE" );
		crt->TextGrid( 45, 23, "44" );

		// FWD RCS
		crt->TextGrid( 1, 23, "FWD RCS" );
		crt->TextGrid( 9, 23, "15" );
		crt->TextGrid( 4, 24, "16" );
		crt->TextGrid( 7, 24, "TIME" );

		// RCS RM MANIF
		crt->TextGrid( 19, 23, "RCS RM" );
		crt->TextGrid( 26, 23, "MANF" );
		crt->TextGrid( 21, 24, "CL" );
		crt->TextGrid( 24, 24, "OVRD" );
		crt->TextGrid( 29, 24, "41" );


		// lines
		crt->Line( 361, 203, 988, 203 );
		crt->Line( 28, 257, 361, 257 );
		crt->Line( 361, 338, 988, 338 );
		crt->Line( 361, 473, 988, 473 );

		crt->Line( 361, 203, 361, 676 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC53( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "CONTROLS" );

		// labels
		// SEC
		crt->TextGrid( 1, 4, "SEC ACT CK" );
		crt->TextGrid( 3, 6, "CH1 1" );
		crt->TextGrid( 5, 7, "2 2" );
		crt->TextGrid( 5, 8, "3 3" );
		crt->TextGrid( 5, 9, "4 4" );
		crt->TextGrid( 1, 10, "START 5" );
		crt->TextGrid( 2, 11, "STOP" );
		crt->TextGrid( 7, 11, "6" );
		crt->TextGrid( 2, 13, "NEG STIM" );
		crt->TextGrid( 3, 14, "ENA 7" );

		// AERO
		crt->TextGrid( 15, 4, "AERO" );
		crt->TextGrid( 20, 4, "PORT" );
		crt->TextGrid( 25, 4, "STAT" );
		crt->TextGrid( 22, 5, "1 2 3 4" );
		crt->TextGrid( 15, 6, "L OB" );
		crt->TextGrid( 17, 7, "IB" );
		crt->TextGrid( 15, 8, "R IB" );
		crt->TextGrid( 17, 9, "OB" );
		crt->TextGrid( 16, 10, "RUD" );
		crt->TextGrid( 12, 11, "SPD BRK" );

		// SSME
		crt->TextGrid( 35, 4, "SSME" );
		crt->TextGrid( 40, 4, "PORT" );
		crt->TextGrid( 45, 4, "STAT" );
		crt->TextGrid( 40, 5, "1 2 3 4" );
		crt->TextGrid( 36, 6, "L P" );
		crt->TextGrid( 38, 7, "Y" );
		crt->TextGrid( 36, 8, "C P" );
		crt->TextGrid( 38, 9, "Y" );
		crt->TextGrid( 36, 10, "R P" );
		crt->TextGrid( 38, 11, "Y" );

		// ACT
		crt->TextGrid( 23, 13, "ACT/CH" );
		crt->TextGrid( 14, 14, "8 BYPASS" );
		crt->TextGrid( 14, 15, "9  RESET" );

		// LRU
		crt->TextGrid( 2, 18, "LRU" );
		crt->TextGrid( 8, 18, "AA" );
		crt->TextGrid( 16, 18, "RGA" );
		crt->TextGrid( 22, 18, "SURF" );
		crt->TextGrid( 27, 18, "FDBK" );
		crt->TextGrid( 8, 19, "DES" );
		crt->TextGrid( 16, 19, "DES" );
		crt->TextGrid( 24, 19, "DES" );
		crt->TextGrid( 3, 20, "1" );
		crt->TextGrid( 7, 20, "10" );
		crt->TextGrid( 15, 20, "14" );
		crt->TextGrid( 23, 20, "18" );
		crt->TextGrid( 3, 21, "2" );
		crt->TextGrid( 7, 21, "11" );
		crt->TextGrid( 15, 21, "15" );
		crt->TextGrid( 23, 21, "19" );
		crt->TextGrid( 3, 22, "3" );
		crt->TextGrid( 7, 22, "12" );
		crt->TextGrid( 15, 22, "16" );
		crt->TextGrid( 23, 22, "20" );
		crt->TextGrid( 3, 23, "4" );
		crt->TextGrid( 7, 23, "13" );
		crt->TextGrid( 15, 23, "17" );
		crt->TextGrid( 23, 23, "21" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC55( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "GPS STATUS" );

		// labels
		crt->TextGrid( 1, 3, "I/O 10" );
		crt->TextGrid( 10, 3, "GPS1" );
		crt->TextGrid( 16, 3, "GPS2" );
		crt->TextGrid( 22, 3, "GPS3" );
		crt->TextGrid( 1, 4, "STAT" );
		crt->TextGrid( 1, 5, "MODE" );
		crt->TextGrid( 1, 6, "S/TEST" );
		crt->TextGrid( 11, 6, "11" );
		crt->TextGrid( 17, 6, "12" );
		crt->TextGrid( 23, 6, "13" );
		crt->TextGrid( 1, 7, "INIT" );
		crt->TextGrid( 11, 7, "14" );
		crt->TextGrid( 17, 7, "15" );
		crt->TextGrid( 23, 7, "16" );
		crt->TextGrid( 1, 8, "NAV" );
		crt->TextGrid( 11, 8, "17" );
		crt->TextGrid( 17, 8, "18" );
		crt->TextGrid( 23, 8, "19" );
		crt->TextGrid( 1, 9, "RESTART" );
		crt->TextGrid( 11, 9, "20" );
		crt->TextGrid( 17, 9, "21" );
		crt->TextGrid( 23, 9, "22" );
		crt->TextGrid( 1, 11, "GDOP" );

		crt->TextGrid( 34, 4, "GPS MINUS NAV" );
		crt->TextGrid( 29, 5, "\x7FH" );
		crt->TextGrid( 41, 5, "\x7FH" );
		crt->TextGrid( 42, 5, "\x04" );
		crt->TextGrid( 29, 6, "\x7F" );
		crt->TextGrid( 30, 6, "DR" );
		crt->TextGrid( 41, 6, "\x7F" );
		crt->TextGrid( 42, 6, "DR" );
		crt->TextGrid( 42, 6, "\x04" );
		crt->TextGrid( 29, 7, "\x7F" );
		crt->TextGrid( 30, 7, "CR" );
		crt->TextGrid( 41, 7, "\x7F" );
		crt->TextGrid( 42, 7, "CR" );
		crt->TextGrid( 42, 7, "\x04" );
		crt->TextGrid( 31, 9, "LAT" );
		crt->TextGrid( 39, 9, "LON" );
		crt->TextGrid( 47, 9, "ALT" );

		crt->TextGrid( 1, 12, "DG" );
		crt->TextGrid( 4, 12, "FAIL" );
		crt->TextGrid( 1, 13, "DES RCVR" );
		crt->TextGrid( 11, 13, "26" );
		crt->TextGrid( 17, 13, "27" );
		crt->TextGrid( 23, 13, "28" );
		crt->TextGrid( 1, 14, "QA" );
		crt->TextGrid( 4, 14, "OVRD" );
		crt->TextGrid( 11, 14, "29" );
		crt->TextGrid( 17, 14, "30" );
		crt->TextGrid( 23, 14, "31" );
		crt->TextGrid( 1, 15, "SF" );
		crt->TextGrid( 4, 15, "CAND" );
		crt->TextGrid( 1, 16, "QA1 P 1\x7B" );
		crt->TextGrid( 1, 17, "QA2 POS" );
		crt->TextGrid( 5, 18, "VEL" );
		crt->TextGrid( 1, 19, "QA3 POS" );
		crt->TextGrid( 5, 20, "VEL" );

		crt->TextGrid( 41, 12, "AUT INH FOR" );
		crt->TextGrid( 29, 13, "GPS TO G&C" );
		crt->TextGrid( 41, 13, "32" );
		crt->TextGrid( 45, 13, "33" );
		crt->TextGrid( 49, 13, "34" );
		crt->TextGrid( 29, 14, "GPS TO NAV" );
		crt->TextGrid( 41, 14, "35" );
		crt->TextGrid( 45, 14, "36" );
		crt->TextGrid( 49, 14, "37" );
		crt->TextGrid( 29, 15, "METERING" );
		crt->TextGrid( 38, 15, "OVERRIDE" );
		crt->TextGrid( 49, 15, "38" );
		crt->TextGrid( 29, 16, "GPS TIME" );
		crt->TextGrid( 38, 16, "ADJUST ENA" );
		crt->TextGrid( 49, 16, "39" );

		crt->TextGrid( 35, 17, "SATELLITES" );
		crt->TextGrid( 29, 18, "TRKD" );
		crt->TextGrid( 35, 18, "C1" );
		crt->TextGrid( 38, 18, "C2" );
		crt->TextGrid( 41, 18, "C3" );
		crt->TextGrid( 44, 18, "C4" );
		crt->TextGrid( 47, 18, "C5" );
		crt->TextGrid( 50, 18, "C6" );
		crt->TextGrid( 30, 19, "GPS1" );
		crt->TextGrid( 30, 20, "GPS2" );
		crt->TextGrid( 30, 21, "GPS3" );
		crt->TextGrid( 29, 23, "DES 43" );

		crt->TextGrid( 11, 21, "1-2" );
		crt->TextGrid( 17, 21, "2-3" );
		crt->TextGrid( 23, 21, "3-1" );
		crt->TextGrid( 1, 22, "QA4 POS" );
		crt->TextGrid( 5, 23, "VEL" );
		crt->TextGrid( 8, 24, "LAST" );
		crt->TextGrid( 13, 24, "SEL FIL UPDATE" );


		// lines
		crt->Line( 294, 68, 294, 635 );
		crt->Line( 408, 68, 408, 635 );
		crt->Line( 522, 68, 522, 635 );

		crt->Line( 28, 311, 997, 311 );
		crt->Line( 522, 446, 997, 446 );
		crt->Line( 28, 554, 522, 554 );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC112( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "GPC/BTU I/F" );

		// labels
		// BTU SELECTION
		crt->TextGrid( 4, 3, "BTU SELECTION" );
		crt->TextGrid( 2, 4, "FF1 1" );
		crt->TextGrid( 10, 4, "PCMMU 12" );
		crt->TextGrid( 4, 5, "2 2" );
		crt->TextGrid( 10, 5, "MMU1" );
		crt->TextGrid( 16, 5, "13" );
		crt->TextGrid( 4, 6, "3 3" );
		crt->TextGrid( 13, 6, "2" );
		crt->TextGrid( 16, 6, "14" );
		crt->TextGrid( 4, 7, "4 4" );
		crt->TextGrid( 10, 7, "MEC1" );
		crt->TextGrid( 16, 7, "15" );
		crt->TextGrid( 2, 8, "FA1 5" );
		crt->TextGrid( 13, 8, "2" );
		crt->TextGrid( 16, 8, "16" );
		crt->TextGrid( 4, 9, "2 6" );
		crt->TextGrid( 10, 9, "EIU1" );
		crt->TextGrid( 16, 9, "17" );
		crt->TextGrid( 4, 10, "3 7" );
		crt->TextGrid( 13, 10, "2" );
		crt->TextGrid( 16, 10, "18" );
		crt->TextGrid( 4, 11, "4 8" );
		crt->TextGrid( 13, 11, "3" );
		crt->TextGrid( 16, 11, "19" );
		crt->TextGrid( 2, 12, "PF1 9" );
		crt->TextGrid( 10, 12, "DDU" );
		crt->TextGrid( 16, 12, "20" );
		crt->TextGrid( 4, 13, "2 10" );
		crt->TextGrid( 10, 13, "MCIU" );
		crt->TextGrid( 16, 13, "21" );
		crt->TextGrid( 11, 14, "CMD" );
		crt->TextGrid( 16, 14, "22" );
		crt->TextGrid( 11, 15, "SRB" );
		crt->TextGrid( 16, 15, "23" );
		crt->TextGrid( 2, 16, "ALL" );
		crt->TextGrid( 2, 17, "MDMS" );
		crt->TextGrid( 7, 17, "11" );
		crt->TextGrid( 12, 16, "DES" );
		crt->TextGrid( 12, 17, "ALL" );
		crt->TextGrid( 17, 17, "24" );

		// TEST STATUS
		crt->TextGrid( 21, 3, "TEST" );
		crt->TextGrid( 26, 3, "STATUS" );
		crt->TextGrid( 21, 5, "BTU ITEM" );
		crt->TextGrid( 21, 6, "STEP" );
		crt->TextGrid( 21, 7, "RDW" );
		crt->TextGrid( 21, 8, "BCE STAT" );
		crt->TextGrid( 30, 8, "RG" );

		// MDM OUTPUT TEST
		crt->TextGrid( 34, 4, "MDM OUTPUT" );
		crt->TextGrid( 45, 4, "TEST" );
		crt->TextGrid( 38, 5, "MODULE" );

		crt->TextGrid( 34, 7, "ANALOG OUTPUTS" );
		crt->TextGrid( 35, 8, "0" );
		crt->TextGrid( 44, 8, "1" );
		crt->TextGrid( 35, 9, "2" );
		crt->TextGrid( 44, 9, "3" );
		crt->TextGrid( 35, 10, "4" );
		crt->TextGrid( 44, 10, "5" );
		crt->TextGrid( 35, 11, "6" );
		crt->TextGrid( 44, 11, "7" );
		crt->TextGrid( 35, 12, "8" );
		crt->TextGrid( 44, 12, "9" );
		crt->TextGrid( 34, 13, "10" );
		crt->TextGrid( 43, 13, "11" );
		crt->TextGrid( 34, 14, "12" );
		crt->TextGrid( 43, 14, "13" );
		crt->TextGrid( 34, 15, "14" );
		crt->TextGrid( 43, 15, "15" );

		crt->TextGrid( 34, 17, "DISCRETE OUTPUTS" );
		crt->TextGrid( 34, 18, "CHANNEL 0" );
		crt->TextGrid( 34, 19, "CHANNEL 1" );
		crt->TextGrid( 34, 20, "CHANNEL 2" );

		// PORT SEL
		crt->TextGrid( 20, 11, "PORT SEL 1" );
		crt->TextGrid( 31, 11, "31" );
		crt->TextGrid( 29, 12, "2 32" );

		// TEST
		crt->TextGrid( 10, 19, "LEVEL 1" );
		crt->TextGrid( 21, 19, "25" );
		crt->TextGrid( 2, 20, "TEST" );
		crt->TextGrid( 10, 20, "LEVEL 2" );
		crt->TextGrid( 21, 20, "26" );
		crt->TextGrid( 10, 21, "MDM OUTPUT" );
		crt->TextGrid( 21, 21, "27" );
		crt->TextGrid( 2, 22, "CONTROL TERMINATE" );
		crt->TextGrid( 21, 22, "28" );
		crt->TextGrid( 10, 23, "CONTINUE" );
		crt->TextGrid( 21, 23, "29" );

		// BTU
		crt->TextGrid( 32, 23, "BTU CYCLIC" );
		crt->TextGrid( 43, 23, "BITE" );
		crt->TextGrid( 49, 23, "30" );
		return;
	}

	void GNCDisplays::BackgroundData_SPEC113( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 16, 1, "ACTUATOR CONTROL" );

		// labels
		// MONITOR
		crt->TextGrid( 4, 2, "MONITOR" );
		crt->TextGrid( 2, 3, "CMD" );
		crt->TextGrid( 10, 3, "POS  ACT" );
		crt->TextGrid( 16, 4, "SB" );
		crt->TextGrid( 20, 4, "1" );
		crt->TextGrid( 15, 5, "RUD  2" );
		crt->TextGrid( 15, 6, "LIE  3" );
		crt->TextGrid( 15, 7, "RIE  4" );
		crt->TextGrid( 15, 8, "LOE  5" );
		crt->TextGrid( 15, 9, "ROE  6" );
		crt->TextGrid( 16, 10, "1P" );
		crt->TextGrid( 20, 10, "7" );
		crt->TextGrid( 16, 11, "1Y" );
		crt->TextGrid( 20, 11, "8" );
		crt->TextGrid( 16, 12, "2P" );
		crt->TextGrid( 20, 12, "9" );
		crt->TextGrid( 16, 13, "2Y" );
		crt->TextGrid( 19, 13, "10" );
		crt->TextGrid( 16, 14, "3P" );
		crt->TextGrid( 19, 14, "12" );
		crt->TextGrid( 16, 15, "3Y" );
		crt->TextGrid( 19, 15, "12" );
		crt->TextGrid( 15, 16, "RPA 13" );
		crt->TextGrid( 15, 17, "RPS 14" );
		crt->TextGrid( 15, 18, "RYA 15" );
		crt->TextGrid( 15, 19, "RYS 16" );
		crt->TextGrid( 15, 20, "LPA 17" );
		crt->TextGrid( 15, 21, "LPS 18" );
		crt->TextGrid( 15, 22, "LYA 19" );
		crt->TextGrid( 15, 23, "LYS 20" );
		crt->TextGrid( 16, 24, "BF" );
		crt->TextGrid( 19, 24, "21" );

		// FAIL
		crt->TextGrid( 24, 2, "FAIL" );
		crt->TextGrid( 23, 3, "A B C D" );

		// ACTUATOR GIMBALING
		crt->TextGrid( 33, 3, "ACTUATOR GIMBALING" );
		crt->TextGrid( 31, 4, "RATE" );
		crt->TextGrid( 36, 4, "29" );
		crt->TextGrid( 45, 4, "DEG/SEC" );
		crt->TextGrid( 31, 5, "FIN POS 30" );
		crt->TextGrid( 49, 5, "DEG" );
		crt->TextGrid( 31, 6, "START 31" );
		crt->TextGrid( 44, 6, "STOP" );
		crt->TextGrid( 49, 6, "32" );
		crt->TextGrid( 41, 7, "STATUS" );
		crt->TextGrid( 41, 8, "ECP ERR" );
		crt->TextGrid( 42, 9, "BF MON" );
		crt->TextGrid( 49, 9, "33" );

		// HYD PR
		crt->TextGrid( 33, 8, "HYD PR" );
		crt->TextGrid( 33, 9, "1" );
		crt->TextGrid( 33, 10, "2" );
		crt->TextGrid( 33, 11, "3" );

		// AI SRB/NW
		crt->TextGrid( 39, 12, "AI" );
		crt->TextGrid( 42, 12, "SRB/NW" );
		crt->TextGrid( 49, 12, "34" );

		// ME ISO V
		crt->TextGrid( 31, 13, "ME ISO V" );
		crt->TextGrid( 31, 14, "1  2" );
		crt->TextGrid( 37, 14, "3" );

		// FC LIM CHNG
		crt->TextGrid( 41, 14, "FC LIM" );
		crt->TextGrid( 48, 14, "CHNG" );
		crt->TextGrid( 40, 15, "R/SB MAT" );
		crt->TextGrid( 49, 15, "35" );
		crt->TextGrid( 36, 16, "R/SB RFG/FRT" );
		crt->TextGrid( 49, 16, "36" );
		crt->TextGrid( 38, 17, "MAT P 40MS" );
		crt->TextGrid( 49, 17, "37" );
		crt->TextGrid( 38, 18, "NOP CA RFG" );
		crt->TextGrid( 49, 18, "38" );
		crt->TextGrid( 38, 19, "NOP CA FRT" );
		crt->TextGrid( 49, 19, "39" );
		crt->TextGrid( 41, 20, "NOP OMS 40" );
		crt->TextGrid( 37, 21, "SRB S/S LIM 41" );
		crt->TextGrid( 38, 22, "EL POS LIM" );
		crt->TextGrid( 49, 22, "42" );
		crt->TextGrid( 37, 23, "S/B POS LIM 43" );
		crt->TextGrid( 35, 24, "R RATE" );
		crt->TextGrid( 42, 24, ".5 PCM" );
		crt->TextGrid( 49, 24, "44" );

		// AI MODES
		crt->TextGrid( 25, 17, "AI MODES" );
		crt->TextGrid( 23, 18, "0 SAFE" );
		crt->TextGrid( 30, 18, "22" );
		crt->TextGrid( 23, 19, "1 MDM" );
		crt->TextGrid( 30, 19, "23" );
		crt->TextGrid( 23, 20, "2 FERY" );
		crt->TextGrid( 30, 20, "24" );
		crt->TextGrid( 23, 21, "3 RAIN" );
		crt->TextGrid( 30, 21, "25" );
		crt->TextGrid( 23, 22, "4 GRAV" );
		crt->TextGrid( 30, 22, "26" );
		crt->TextGrid( 23, 23, "5 NULL" );
		crt->TextGrid( 30, 23, "27" );
		crt->TextGrid( 23, 24, "6 TURN" );
		crt->TextGrid( 30, 24, "28" );


		// lines
		// ACTUATOR GIMBALING
		crt->Line( 598, 95, 997, 95 );

		// HYD PR
		crt->Line( 636, 230, 750, 230 );

		// ME ISO V
		crt->Line( 598, 365, 750, 365 );

		// FC LIM CHNG
		crt->Line( 750, 392, 997, 392 );

		// AI MODES
		crt->Line( 446, 473, 655, 473 );
		return;
	}


	void GNCDisplays::BackgroundData_XXXXXXTRAJ1( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 25, 1, "TRAJ 1" );

		// labels
		crt->TextGrid( 8, 6, "CONT ABORT" );
		crt->TextGrid( 9, 7, "3EO" );
		crt->TextGrid( 2, 8, "2  ARM 2EO" );
		crt->TextGrid( 2, 9, "4  ABORT" );
		crt->TextGrid( 2, 11, "5" );
		crt->TextGrid( 8, 11, "YAW STEER" );
		crt->TextGrid( 2, 13, "6" );
		crt->TextGrid( 5, 13, "SERC" );
		crt->TextGrid( 39, 18, "THROT" );
		crt->TextGrid( 19, 23, "7" );
		crt->TextGrid( 25, 23, "DRP 1EO" );
		return;
	}

	void GNCDisplays::BackgroundData_XXXXXXTRAJ2( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 25, 1, "TRAJ 1" );

		// labels
		crt->TextGrid( 39, 6, "TGO" );
		crt->TextGrid( 45, 6, ":" );
		crt->TextGrid( 8, 6, "CONT ABORT" );
		crt->TextGrid( 9, 7, "3EO" );
		crt->TextGrid( 2, 8, "2  ARM 2EO" );
		crt->TextGrid( 2, 9, "4  ABORT" );
		crt->TextGrid( 2, 11, "5" );
		crt->TextGrid( 8, 11, "YAW STEER" );
		crt->TextGrid( 2, 13, "6" );
		crt->TextGrid( 5, 13, "SERC" );
		crt->TextGrid( 39, 18, "THROT" );
		crt->TextGrid( 39, 19, "PRPLT" );
		crt->TextGrid( 39, 21, "TMECO" );
		crt->TextGrid( 47, 21, ":" );
		crt->TextGrid( 19, 23, "7" );
		crt->TextGrid( 25, 23, "DRP 1EO" );

		// lines
		crt->Line( 213, 110, 963, 110 );

		crt->Text( 213, 119, "\x18" );
		crt->Text( 963, 119, "\x18" );
		return;
	}

	void GNCDisplays::BackgroundData_XXXXXMNVRYYYYY( CRT_Interface* crt ) const
	{
		crt->TextGrid( 2, 2, "OMS BOTH 1" );
		crt->TextGrid( 9, 3, "L 2" );
		crt->TextGrid( 9, 4, "R 3" );
		crt->TextGrid( 2, 5, "RCS SEL  4" );
		crt->TextGrid( 2, 6, "5 TV" );
		crt->TextGrid( 7, 6, "ROLL" );
		crt->TextGrid( 12, 6, "\x7D\x7D\x7D" );

		crt->TextGrid( 2, 7, "TRIM" );
		crt->TextGrid( 7, 7, "LOAD" );
		crt->TextGrid( 3, 8, "6 P" );
		crt->TextGrid( 8, 8, "\x01" );
		crt->TextGrid( 8, 8, "\x02" );
		crt->TextGrid( 9, 8, "\x7D\x7D\x7D" );
		crt->TextGrid( 3, 9, "7 LY" );
		crt->TextGrid( 8, 9, "\x01" );
		crt->TextGrid( 8, 9, "\x02" );
		crt->TextGrid( 3, 10, "8 RY" );
		crt->TextGrid( 8, 10, "\x01" );
		crt->TextGrid( 8, 10, "\x02" );

		crt->TextGrid( 2, 11, "9 WT" );
		crt->TextGrid( 7, 11, "\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 1, 12, "10 TIG" );
		crt->TextGrid( 4, 13, "\x7D\x7D\x7D" );
		crt->TextGrid( 8, 13, "\x7D\x7D" );
		crt->TextGrid( 11, 13, "\x7D\x7D" );
		crt->TextGrid( 14, 13, "\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 2, 14, "TGT PEG 4" );
		crt->TextGrid( 3, 15, "14" );
		crt->TextGrid( 6, 15, "C1" );
		crt->TextGrid( 13, 15, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 3, 16, "15" );
		crt->TextGrid( 6, 16, "C2" );
		crt->TextGrid( 11, 16, "\x01" );
		crt->TextGrid( 11, 16, "\x02" );
		crt->TextGrid( 12, 16, "\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 3, 17, "16" );
		crt->TextGrid( 6, 17, "HT" );
		crt->TextGrid( 11, 17, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 3, 18, "17 " );
		crt->TextGrid( 6, 18, "\x5CT" );
		crt->TextGrid( 11, 18, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 3, 19, "18 PRPLT" );
		crt->TextGrid( 12, 19, "\x01" );
		crt->TextGrid( 12, 19, "\x02" );
		crt->TextGrid( 13, 19, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 2, 20, "TGT PEG 7" );
		crt->TextGrid( 3, 21, "19 \x7FVX" );
		crt->TextGrid( 10, 21, "\x01" );
		crt->TextGrid( 10, 21, "\x02" );
		crt->TextGrid( 11, 21, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 3, 22, "20 \x7FVY" );
		crt->TextGrid( 11, 22, "\x01" );
		crt->TextGrid( 11, 22, "\x02" );
		crt->TextGrid( 12, 22, "\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 3, 23, "21 \x7FVZ" );
		crt->TextGrid( 11, 23, "\x01" );
		crt->TextGrid( 11, 23, "\x02" );
		crt->TextGrid( 12, 23, "\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 7, 24, "22/TIMER" );
		crt->TextGrid( 16, 24, "23" );

		crt->TextGrid( 22, 4, "24 R" );
		crt->TextGrid( 27, 4, "\x7D\x7D\x7D" );
		crt->TextGrid( 22, 5, "25 P" );
		crt->TextGrid( 22, 6, "26 Y" );

		crt->TextGrid( 21, 7, "MNVR" );
		crt->TextGrid( 26, 7, "27" );

		crt->TextGrid( 21, 3, "BURN ATT" );
		crt->TextGrid( 22, 8, "TTG" );

		crt->TextGrid( 21, 9, "REI" );
		crt->TextGrid( 21, 10, "T" );

		crt->TextGrid( 26, 11, "GMBL" );
		crt->TextGrid( 25, 12, "L" );
		crt->TextGrid( 31, 12, "R" );
		crt->TextGrid( 21, 13, "P" );
		crt->TextGrid( 21, 14, "Y" );

		crt->TextGrid( 21, 16, "PRI 28" );
		crt->TextGrid( 30, 16, "29" );
		crt->TextGrid( 21, 17, "SEC 30" );
		crt->TextGrid( 30, 17, "31" );
		crt->TextGrid( 21, 18, "OFF 32" );
		crt->TextGrid( 30, 18, "33" );
		crt->TextGrid( 21, 20, "GMBL" );
		crt->TextGrid( 26, 20, "CK" );
		crt->TextGrid( 30, 20, "34" );

		crt->TextGrid( 37, 4, "\x7FVTOT" );
		crt->TextGrid( 37, 5, "TGO" );
		crt->TextGrid( 37, 7, "VGO X" );
		crt->TextGrid( 41, 8, "Y" );
		crt->TextGrid( 41, 9, "Z" );

		crt->TextGrid( 42, 11, "HA" );
		crt->TextGrid( 48, 11, "HP" );

		crt->TextGrid( 37, 12, "TGT" );
		crt->TextGrid( 37, 13, "CUR" );

		crt->TextGrid( 36, 16, "35 ABORT TGT" );
		crt->TextGrid( 49, 16, "\x7D\x7D" );

		crt->TextGrid( 38, 18, "FWD RCS" );
		crt->TextGrid( 40, 19, "ARM" );
		crt->TextGrid( 46, 19, "36" );
		crt->TextGrid( 40, 20, "DUMP" );
		crt->TextGrid( 46, 20, "37" );
		crt->TextGrid( 40, 21, "OFF" );
		crt->TextGrid( 46, 21, "38" );

		crt->TextGrid( 38, 22, "SURF DRIVE" );
		crt->TextGrid( 40, 23, "ON" );
		crt->TextGrid( 46, 23, "39" );
		crt->TextGrid( 40, 24, "OFF" );
		crt->TextGrid( 46, 24, "40" );


		crt->Line( 370, 41, 370, 662 );
		crt->Line( 693, 82, 693, 392 );
		crt->Line( 693, 392, 988, 392 );
		return;
	}

	void GNCDisplays::BackgroundData_UNIVPTG( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 20, 1, "UNIV PTG" );

		crt->TextGrid( 4, 2, "CUR MNVR COMPL" );
		crt->TextGrid( 2, 3, "1 START TIME" );

		crt->TextGrid( 15, 3, "\x7D\x7D\x7D" );
		crt->TextGrid( 19, 3, "\x7D\x7D" );
		crt->TextGrid( 22, 3, "\x7D\x7D" );
		crt->TextGrid( 25, 3, "\x7D\x7D" );

		crt->TextGrid( 1, 5, "MNVR" );
		crt->TextGrid( 6, 5, "OPTION" );
		crt->TextGrid( 2, 6, "5 R \x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 7, "6 P" );
		crt->TextGrid( 2, 8, "7 Y" );

		crt->TextGrid( 1, 10, "TRK/ROT OPTIONS" );
		crt->TextGrid( 2, 11, "8 TGT ID \x7D\x7D\x7D" );

		crt->TextGrid( 2, 13, "9" );
		crt->TextGrid( 5, 13, "RA" );
		crt->TextGrid( 10, 13, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 14, "10 DEC" );
		crt->TextGrid( 10, 14, "\x01" );
		crt->TextGrid( 10, 14, "\x02" );
		crt->TextGrid( 11, 14, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 15, "11 LAT" );
		crt->TextGrid( 10, 15, "\x01" );
		crt->TextGrid( 10, 15, "\x02" );
		crt->TextGrid( 11, 15, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 16, "12 LON" );
		crt->TextGrid( 9, 16, "\x01" );
		crt->TextGrid( 9, 16, "\x02" );
		crt->TextGrid( 10, 16, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 17, "13 ALT" );
		crt->TextGrid( 9, 17, "\x01" );
		crt->TextGrid( 9, 17, "\x02" );
		crt->TextGrid( 10, 17, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

		crt->TextGrid( 2, 19, "14 BODY VECT" );
		crt->TextGrid( 15, 19, "\x7D" );

		crt->TextGrid( 2, 21, "15 P" );
		crt->TextGrid( 8, 21, "\x7D\x7D\x7D\x7D\x7D\x7D" );
		crt->TextGrid( 2, 22, "16 Y" );
		crt->TextGrid( 2, 23, "17 OM" );

		crt->TextGrid( 16, 5, "START MNVR" );
		crt->TextGrid( 27, 5, "18" );
		crt->TextGrid( 22, 6, "TRK" );
		crt->TextGrid( 27, 6, "19" );
		crt->TextGrid( 22, 7, "ROT" );
		crt->TextGrid( 27, 7, "20" );
		crt->TextGrid( 21, 8, "CNCL" );
		crt->TextGrid( 27, 8, "21" );
		crt->TextGrid( 29, 4, "CUR" );
		crt->TextGrid( 33, 4, "FUT" );

		crt->TextGrid( 21, 10, "ATT MON" );
		crt->TextGrid( 22, 11, "22" );
		crt->TextGrid( 25, 11, "MON AXIS" );
		crt->TextGrid( 34, 11, "\x7D" );
		crt->TextGrid( 22, 12, "ERR TOT 23" );
		crt->TextGrid( 22, 13, "ERR DAP 24" );

		crt->TextGrid( 21, 16, "CUR" );
		crt->TextGrid( 21, 17, "REQD" );
		crt->TextGrid( 21, 18, "ERR" );
		crt->TextGrid( 21, 19, "RATE" );

		crt->TextGrid( 28, 15, "ROLL" );
		crt->TextGrid( 35, 15, "PITCH" );
		crt->TextGrid( 44, 15, "YAW" );

		crt->TextGrid( 44, 4, "CUR" );
		crt->TextGrid( 48, 4, "FUT" );
		crt->TextGrid( 37, 5, "RBST" );
		crt->TextGrid( 42, 5, "25" );
		crt->TextGrid( 37, 6, "CNCL" );
		crt->TextGrid( 42, 6, "26" );
		crt->TextGrid( 37, 7, "DURATION" );
		crt->TextGrid( 46, 7, "27" );
		crt->TextGrid( 38, 8, "\x7D\x7D" );
		crt->TextGrid( 41, 8, "\x7D\x7D" );
		crt->TextGrid( 44, 8, "\x7D\x7D\x7D\x7D\x7D" );
		return;
	}

	void GNCDisplays::BackgroundData_ENTRYTRAJ( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "ENTRY TRAJ" );

		crt->TextGrid( 8, 5, "1 BIAS" );
		crt->TextGrid( 15, 5, "\x01" );
		crt->TextGrid( 15, 5, "\x02" );
		crt->TextGrid( 16, 5, "\x7D\x7D" );
		crt->TextGrid( 8, 6, "D REF" );
		crt->TextGrid( 8, 7, "q" );
		crt->TextGrid( 8, 7, "\x5D" );
		crt->TextGrid( 8, 8, "\x7F AZ" );
		crt->TextGrid( 8, 11, "3" );
		crt->TextGrid( 8, 12, "4  ALT" );
		crt->TextGrid( 11, 13, "SITES" );

		crt->TextGrid( 39, 16, "NY" );
		crt->TextGrid( 39, 17, "NY TRIM" );
		crt->TextGrid( 39, 18, "AIL" );
		crt->TextGrid( 39, 19, "RUD" );
		crt->TextGrid( 38, 20, "ZERO H BIAS 2" );
		crt->TextGrid( 43, 20, "\x04" );
		crt->TextGrid( 39, 21, "H BIAS" );
		crt->TextGrid( 39, 21, "\x04" );
		crt->TextGrid( 42, 22, "REF" );
		crt->TextGrid( 37, 23, "ROLL REF" );
		crt->TextGrid( 42, 24, "CMD" );

		crt->Text( 56, 55, "\x10" );
		crt->Text( 113, 55, "D" );
		crt->Text( 113, 89, "50" );
		crt->Text( 113, 189, "40" );
		crt->Text( 113, 289, "30" );
		crt->Text( 113, 389, "20" );
		crt->Text( 113, 489, "10" );
		crt->Text( 113, 589, "0" );

		// phugoid scale marks
		crt->Text( 170, 89, "\x18" );
		crt->Text( 330, 89, "\x18" );
		crt->Text( 490, 89, "\x18" );

		// alpha/D scale marks
		crt->Text( 90, 589, "-" );
		crt->Text( 90, 569, "-" );
		crt->Text( 90, 549, "-" );
		crt->Text( 90, 529, "-" );
		crt->Text( 90, 509, "-" );
		crt->Text( 90, 489, "-" );
		crt->Text( 90, 469, "-" );
		crt->Text( 90, 449, "-" );
		crt->Text( 90, 429, "-" );
		crt->Text( 90, 409, "-" );
		crt->Text( 90, 389, "-" );
		crt->Text( 90, 369, "-" );
		crt->Text( 90, 349, "-" );
		crt->Text( 90, 329, "-" );
		crt->Text( 90, 309, "-" );
		crt->Text( 90, 289, "-" );
		crt->Text( 90, 269, "-" );
		crt->Text( 90, 249, "-" );
		crt->Text( 90, 229, "-" );
		crt->Text( 90, 209, "-" );
		crt->Text( 90, 189, "-" );
		crt->Text( 90, 169, "-" );
		crt->Text( 90, 149, "-" );
		crt->Text( 90, 129, "-" );
		crt->Text( 90, 109, "-" );
		crt->Text( 90, 89, "-" );
		crt->Line( 90, 589, 90, 89 );
		return;
	}

	void GNCDisplays::BackgroundData_VERTSIT( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 18, 1, "VERT SIT" );

		crt->Text( 854, 217, "\x5C" );
		crt->Text( 949, 217, "E/W" );
		crt->Text( 949, 325, "STN" );
		crt->Text( 949, 406, "NOM" );
		crt->Text( 949, 541, "MEP" );
		crt->Text( 759, 325, "NOSE HI" );
		crt->Text( 759, 541, "NOSE LO" );

		crt->TextGrid( 30, 15, "SPD BK" );
		crt->TextGrid( 33, 16, "CMD" );

		crt->TextGrid( 21, 18, "NY" );
		crt->TextGrid( 21, 19, "NY" );
		crt->TextGrid( 24, 19, "TRIM" );
		crt->TextGrid( 21, 20, "AIL" );
		crt->TextGrid( 21, 21, "RUD" );
		crt->TextGrid( 21, 22, "TGT NZ" );

		// theta / E/W scale
		crt->Line( 911, 219, 911, 658 );
		crt->Text( 911, 328, "-" );
		crt->Text( 911, 548, "-" );
		return;
	}

	void GNCDisplays::BackgroundData_RTLSTRAJ2( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "RTLS TRAJ 2" );

		crt->TextGrid( 13, 6, "ABORT" );
		crt->TextGrid( 9, 7, "3EO" );
		crt->TextGrid( 2, 8, "2" );
		crt->TextGrid( 5, 8, "ARM 2EO" );
		crt->TextGrid( 2, 9, "4" );
		crt->TextGrid( 5, 9, "ABORT" );

		crt->TextGrid( 2, 11, "5" );
		crt->TextGrid( 8, 11, "YAW STEER" );

		crt->TextGrid( 2, 13, "6" );
		crt->TextGrid( 5, 13, "SERC" );

		crt->TextGrid( 39, 6, "TGO" );
		crt->TextGrid( 45, 6, ":" );

		crt->TextGrid( 38, 8, "GUID" );

		crt->TextGrid( 39, 18, "THROT" );
		crt->TextGrid( 39, 19, "PRPLT" );

		crt->TextGrid( 39, 21, "TMECO" );
		crt->TextGrid( 47, 21, ":" );

		crt->Text( 227, 118, "CO" );
		crt->Text( 236, 104, "\x18" );

		// dR scale
		crt->Line( 136, 95, 936, 95 );
		return;
	}

	void GNCDisplays::BackgroundData_FCSDEDDISCO( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "FCS/DED DIS C/O" );

		// DED DIS
		crt->TextGrid( 3, 5, "DED DIS" );
		crt->TextGrid( 2, 6, "FWD 1" );
		crt->TextGrid( 2, 7, "AFT 2" );
		crt->TextGrid( 10, 6, "HIGH 3" );
		crt->TextGrid( 10, 7, "LOW  4" );
		crt->TextGrid( 10, 8, "FLAG 5" );
		crt->TextGrid( 10, 9, "OFF  6" );

		// BODY FLP DES
		crt->TextGrid( 3, 11, "BODY FLP DES" );
		crt->TextGrid( 2, 12, "VLV" );
		crt->TextGrid( 6, 12, "1" );
		crt->TextGrid( 6, 13, "2" );
		crt->TextGrid( 6, 14, "3" );
		crt->TextGrid( 12, 12, "12" );
		crt->TextGrid( 12, 13, "13" );
		crt->TextGrid( 12, 14, "14" );

		// SEC ACT CK
		crt->TextGrid( 3, 16, "SEC ACT CK" );
		crt->TextGrid( 2, 17, "CH 1" );
		crt->TextGrid( 8, 17, "15" );
		crt->TextGrid( 2, 18, "CH 2" );
		crt->TextGrid( 8, 18, "16" );
		crt->TextGrid( 2, 19, "CH 3" );
		crt->TextGrid( 8, 19, "17" );
		crt->TextGrid( 2, 20, "CH 4" );
		crt->TextGrid( 8, 20, "18" );
		crt->TextGrid( 2, 21, "STOP" );
		crt->TextGrid( 8, 21, "19" );
		crt->TextGrid( 2, 22, "POS STIM" );
		crt->TextGrid( 4, 23, "ENA 20" );

		// MODE LT
		crt->TextGrid( 22, 5, "MODE" );
		crt->TextGrid( 27, 5, "LT" );
		crt->TextGrid( 21, 6, "ON" );
		crt->TextGrid( 26, 6, "7" );
		crt->TextGrid( 21, 7, "OFF  8" );

		// AVG G ON
		crt->TextGrid( 37, 5, "AVG G" );
		crt->TextGrid( 44, 5, "ON" );
		crt->TextGrid( 48, 5, "9" );

		// SURF DR
		crt->TextGrid( 22, 10, "SURF" );
		crt->TextGrid( 27, 10, "DR" );
		crt->TextGrid( 31, 10, "START 10" );
		crt->TextGrid( 42, 10, "STOP" );
		crt->TextGrid( 47, 10, "11" );

		crt->TextGrid( 19, 13, "SURF" );
		crt->TextGrid( 30, 13, "CMD" );
		crt->TextGrid( 37, 13, "POS" );
		crt->TextGrid( 43, 13, "1 2 3 4" );

		crt->TextGrid( 18, 14, "ELEV" );
		crt->TextGrid( 23, 14, "L OB" );
		crt->TextGrid( 25, 15, "IB" );
		crt->TextGrid( 23, 16, "R IB" );
		crt->TextGrid( 25, 17, "OB" );
		crt->TextGrid( 18, 18, "RUD" );
		crt->TextGrid( 18, 19, "SPD BRK" );
		crt->TextGrid( 18, 20, "BDY FLP" );

		// SEC ACT
		crt->TextGrid( 38, 22, "SEC ACT" );
		crt->TextGrid( 37, 23, "21" );
		crt->TextGrid( 48, 23, "\x7D\x7D" );
		crt->TextGrid( 40, 23, "BYPASS" );
		crt->TextGrid( 37, 24, "22 RESET" );
		crt->TextGrid( 48, 24, "\x7D\x7D" );
		return;
	}
};
