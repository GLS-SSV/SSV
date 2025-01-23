#include "ABT_OMS_RCS_CONN.h"


namespace dps
{
	ABT_OMS_RCS_CONN::ABT_OMS_RCS_CONN( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ABT_OMS_RCS_CONN" ),
		INTERCONNECT_MONITOR_FLAG(0), OMSRCS_IC_IN_PROGRESS_FLAG(0), OMSRCS_RTRN_TO_NORM_IN_PROGRESS_FLAG(0),
		_12_XFDISO_FAIL_FLAG(0), IC_FAIL_COUNTER(0),
		RCS_L_OX_TK_POSN_CYC_COUNTER(0), RCS_L_FU_TK_POSN_CYC_COUNTER(0), RCS_R_OX_TK_POSN_CYC_COUNTER(0), RCS_R_FU_TK_POSN_CYC_COUNTER(0),
		RCS_L_A_OX_TK_POSN_CYC_COUNTER(0), RCS_L_B_OX_TK_POSN_CYC_COUNTER(0), RCS_L_A_FU_TK_POSN_CYC_COUNTER(0), RCS_L_B_FU_TK_POSN_CYC_COUNTER(0),
		RCS_R_A_OX_TK_POSN_CYC_COUNTER(0), RCS_R_B_OX_TK_POSN_CYC_COUNTER(0), RCS_R_A_FU_TK_POSN_CYC_COUNTER(0), RCS_R_B_FU_TK_POSN_CYC_COUNTER(0),
		LOCAL_OMS_L_POD_OX_XFD_VLV_B_POSN_OP(0), LOCAL_OMS_L_POD_FU_XFD_VLV_B_POSN_OP(0), LOCAL_OMS_R_POD_OX_XFD_VLV_B_POSN_OP(0), LOCAL_OMS_R_POD_FU_XFD_VLV_B_POSN_OP(0),
		FA1_COMMFAULT_CYC_COUNTER(0), FA2_COMMFAULT_CYC_COUNTER(0), FA3_COMMFAULT_CYC_COUNTER(0), FA4_COMMFAULT_CYC_COUNTER(0),
		firstpass_step2(false), firstpass_step3(false), firstpass_step5(false), firstpass_step6(false), firstpass_step9(false),
		firstpass_step10(false), firstpass_step11(false), firstpass_step12(false), firstpass_step14(false), firstpass_step15(false),
		timer_step2(0.0), timer_step3(0.0), timer_step5(0.0), timer_step6(0.0), timer_step9(0.0), timer_step10(0.0),
		timer_step11(0.0), timer_step12(0.0), timer_step14(0.0), timer_step15(0.0),
		timerena_step2(false), timerena_step3(false), timerena_step5(false), timerena_step6(false), timerena_step9(false),
		timerena_step10(false), timerena_step11(false), timerena_step12(false), timerena_step14(false), timerena_step15(false)
	{
		return;
	}

	ABT_OMS_RCS_CONN::~ABT_OMS_RCS_CONN( void )
	{
		return;
	}

	void ABT_OMS_RCS_CONN::OnPostStep( double simt, double simdt, double mjd )
	{
		// handle timers
		if (timerena_step2) timer_step2 += simdt;
		if (timerena_step3) timer_step3 += simdt;
		if (timerena_step5) timer_step5 += simdt;
		if (timerena_step6) timer_step6 += simdt;
		if (timerena_step9) timer_step9 += simdt;
		if (timerena_step10) timer_step10 += simdt;
		if (timerena_step11) timer_step11 += simdt;
		if (timerena_step12) timer_step12 += simdt;
		if (timerena_step14) timer_step14 += simdt;
		if (timerena_step15) timer_step15 += simdt;

		// inputs
		unsigned short FA1_IOM3_CH1 = ReadCOMPOOL_IS( SCP_FA1_IOM3_CH1_DATA );
		unsigned short FA1_IOM3_CH2 = ReadCOMPOOL_IS( SCP_FA1_IOM3_CH2_DATA );
		unsigned short FA1_IOM11_CH1 = ReadCOMPOOL_IS( SCP_FA1_IOM11_CH1_DATA );
		unsigned short FA1_IOM11_CH2 = ReadCOMPOOL_IS( SCP_FA1_IOM11_CH2_DATA );
		unsigned short FA2_IOM3_CH1 = ReadCOMPOOL_IS( SCP_FA2_IOM3_CH1_DATA );
		unsigned short FA2_IOM3_CH2 = ReadCOMPOOL_IS( SCP_FA2_IOM3_CH2_DATA );
		unsigned short FA2_IOM11_CH1 = ReadCOMPOOL_IS( SCP_FA2_IOM11_CH1_DATA );
		unsigned short FA2_IOM11_CH2 = ReadCOMPOOL_IS( SCP_FA2_IOM11_CH2_DATA );
		unsigned short FA3_IOM3_CH2 = ReadCOMPOOL_IS( SCP_FA3_IOM3_CH2_DATA );
		unsigned short FA3_IOM11_CH1 = ReadCOMPOOL_IS( SCP_FA3_IOM11_CH1_DATA );
		unsigned short FA3_IOM11_CH2 = ReadCOMPOOL_IS( SCP_FA3_IOM11_CH2_DATA );
		unsigned short FA4_IOM11_CH1 = ReadCOMPOOL_IS( SCP_FA4_IOM11_CH1_DATA );
		unsigned short FA4_IOM11_CH2 = ReadCOMPOOL_IS( SCP_FA4_IOM11_CH2_DATA );
		unsigned short FA4_IOM3_CH2 = ReadCOMPOOL_IS( SCP_FA4_IOM3_CH2_DATA );

		unsigned short RCS_L_AFT_OX_XFD_VLV_12_OP = (FA3_IOM3_CH2 & 0x0100) >> 8;// V42X2236X
		unsigned short RCS_L_AFT_FU_XFD_VLV_12_OP = (FA3_IOM3_CH2 & 0x0400) >> 10;// V42X2336X
		unsigned short RCS_R_AFT_OX_XFD_VLV_12_OP = (FA4_IOM11_CH2 & 0x0100) >> 8;// V42X3236X
		unsigned short RCS_R_AFT_FU_XFD_VLV_12_OP = (FA4_IOM11_CH2 & 0x0400) >> 10;// V42X3336X

		unsigned short RCS_L_OXFU_XFD_VLV_12_OP = (FA3_IOM11_CH1 & 0x4000) >> 14;// V42X2251X
		unsigned short RCS_R_OXFU_XFD_VLV_12_OP = (FA4_IOM11_CH1 & 0x4000) >> 14;// V42X2252X

		unsigned short RCS_L_AFT_OX_XFD_VLV_345_OP = (FA2_IOM11_CH2 & 0x0010) >> 4;// V42X2238X
		unsigned short RCS_L_AFT_FU_XFD_VLV_345_OP = (FA2_IOM11_CH2 & 0x0040) >> 6;// V42X2338X
		unsigned short RCS_R_AFT_OX_XFD_VLV_345_OP = (FA1_IOM3_CH2 & 0x0010) >> 4;// V42X3238X
		unsigned short RCS_R_AFT_FU_XFD_VLV_345_OP = (FA1_IOM3_CH2 & 0x0040) >> 6;// V42X3338X

		unsigned short RCS_L_OXFU_XFD_VLV_345_OP = (FA4_IOM11_CH1 & 0x8000) >> 15;// V42X2253X
		unsigned short RCS_R_OXFU_XFD_VLV_345_OP = (FA4_IOM11_CH1 & 0x8000) >> 15;// V42X2254X

		unsigned short RCS_L_AFT_OX_TANK_ISLN_VLV_12_CL = (FA1_IOM11_CH2 & 0x0020) >> 5;// V42X2221X
		unsigned short RCS_L_AFT_FU_TANK_ISLN_VLV_12_CL = (FA1_IOM11_CH2 & 0x0080) >> 7;// V42X2321X

		unsigned short RCS_R_AFT_OX_TANK_ISLN_VLV_12_CL = (FA2_IOM3_CH2 & 0x0020) >> 5;// V42X3221X
		unsigned short RCS_R_AFT_FU_TANK_ISLN_VLV_12_CL = (FA2_IOM3_CH2 & 0x0080) >> 7;// V42X3321X

		unsigned short RCS_L_AFT_OX_TANK_ISLN_VLV_12_OP = (FA1_IOM11_CH2 & 0x0010) >> 4;// V42X2220X
		unsigned short RCS_L_AFT_FU_TANK_ISLN_VLV_12_OP = (FA1_IOM11_CH2 & 0x0040) >> 6;// V42X2320X

		unsigned short RCS_R_AFT_OX_TANK_ISLN_VLV_12_OP = (FA2_IOM3_CH2 & 0x0010) >> 4;// V42X3220X
		unsigned short RCS_R_AFT_FU_TANK_ISLN_VLV_12_OP = (FA2_IOM3_CH2 & 0x0040) >> 6;// V42X3320X

		unsigned short RCS_L_AFT_OX_TANK_ISLN_VLV_345_A_CL = (FA3_IOM11_CH2 & 0x0020) >> 5;// V42X2223X
		unsigned short RCS_L_AFT_OX_TANK_ISLN_VLV_345_B_CL = (FA4_IOM11_CH2 & 0x0020) >> 5;// V42X2225X
		unsigned short RCS_L_AFT_FU_TANK_ISLN_VLV_345_A_CL = (FA3_IOM11_CH2 & 0x0080) >> 7;// V42X2323X
		unsigned short RCS_L_AFT_FU_TANK_ISLN_VLV_345_B_CL = (FA4_IOM11_CH2 & 0x0080) >> 7;// V42X2325X

		unsigned short RCS_R_AFT_OX_TANK_ISLN_VLV_345_A_CL = (FA3_IOM3_CH2 & 0x0020) >> 5;// V42X3223X
		unsigned short RCS_R_AFT_OX_TANK_ISLN_VLV_345_B_CL = (FA4_IOM3_CH2 & 0x0020) >> 5;// V42X3225X
		unsigned short RCS_R_AFT_FU_TANK_ISLN_VLV_345_A_CL = (FA3_IOM3_CH2 & 0x0080) >> 7;// V42X3323X
		unsigned short RCS_R_AFT_FU_TANK_ISLN_VLV_345_B_CL = (FA4_IOM3_CH2 & 0x0080) >> 7;// V42X3325X

		unsigned short OMS_L_POD_OX_XFD_VLV_A_POSN_OP = (FA1_IOM11_CH1 & 0x0000) >> 6;// V43X4256X
		unsigned short OMS_L_POD_FU_XFD_VLV_A_POSN_OP = (FA1_IOM11_CH1 & 0x0000) >> 8;// V43X4356X
		unsigned short OMS_R_POD_OX_XFD_VLV_A_POSN_OP = (FA1_IOM3_CH1 & 0x0000) >> 8;// V43X5256X
		unsigned short OMS_R_POD_FU_XFD_VLV_A_POSN_OP = (FA1_IOM3_CH1 & 0x0000) >> 10;// V43X5356X
		//unsigned short OMS_L_POD_OX_XFD_VLV_B_POSN_OP = (FA2_IOM11_CH1 & 0x0000) >> 6;// V43X4258X
		//unsigned short OMS_L_POD_FU_XFD_VLV_B_POSN_OP = (FA2_IOM11_CH1 & 0x0000) >> 8;// V43X4358X
		//unsigned short OMS_R_POD_OX_XFD_VLV_B_POSN_OP = (FA2_IOM3_CH1 & 0x0000) >> 8;// V43X5258X
		//unsigned short OMS_R_POD_FU_XFD_VLV_B_POSN_OP = (FA2_IOM3_CH1 & 0x0000) >> 10;// V43X5358X

		// INFO FAx checks don't match several signal sources... typos or did signals switch FAx?
		unsigned short FA_1_INPUT_PROM_SEG_3_10_STATUS = 0;// TODO V91X2845X
		unsigned short FA_2_INPUT_PROM_SEG_3_10_STATUS = 0;// TODO V91X2846X
		unsigned short FA_3_INPUT_PROM_SEG_3_10_STATUS = 0;// TODO V91X2847X
		unsigned short FA_4_INPUT_PROM_SEG_3_10_STATUS = 0;// TODO V91X2848X


		//// initialization / termination
	// step1:
		if (OMSRCS_IC_IN_PROGRESS_FLAG == 1)
		{
			goto step2;
		}

		if (OMSRCS_RTRN_TO_NORM_IN_PROGRESS_FLAG == 1)
		{
			goto step6;
		}

		if ((ReadCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD ) == 1) && (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 0))
		{
			OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 0;
			OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 0;
			OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 0;
			OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 0;
			OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 0;
			OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 0;

			OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 0;
			OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 0;
			OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 0;
			OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 0;
			OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 0;
			OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 0;

			RCS_L_AFT_XFD_VLV_12_GPC_CL_A = 0;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B = 0;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B = 0;
			RCS_L_AFT_XFD_VLV_345_GPC_CL_A = 0;
			RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 0;
			RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 0;

			RCS_R_AFT_XFD_VLV_12_GPC_CL_A = 0;
			RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 0;
			RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 0;
			RCS_R_AFT_XFD_VLV_345_GPC_CL_A = 0;
			RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 0;
			RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 0;

			RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
			RCS_L_AFT_OX_TK_ISLN_V12_GPC_CL_B = 0;
			RCS_L_AFT_FU_TK_ISLN_V12_GPC_CL_B = 0;
			RCS_L_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_L_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_L_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
			RCS_L_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

			RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
			RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 0;
			RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 0;
			RCS_R_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_R_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_R_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
			RCS_R_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

			OMS_L_POD_XFD_VLVS_A_CMD_1_OP = 0;
			OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 0;
			OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP = 0;
			OMS_L_POD_XFD_VLVS_B_CMD_1_OP = 0;
			OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
			OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;

			OMS_R_POD_XFD_VLVS_A_CMD_1_OP = 0;
			OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 0;
			OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP = 0;
			OMS_R_POD_XFD_VLVS_B_CMD_1_OP = 0;
			OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
			OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;

			RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 0;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 0;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 0;
			RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 0;
			RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 0;
			RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 0;

			RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 0;
			RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 0;
			RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 0;
			RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 0;
			RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 0;
			RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 0;

			RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 0;
			RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 0;
			RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 0;

			RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 0;
			RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 0;
			RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 0;

			WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG, 0 );
			WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG, 0 );
			INTERCONNECT_MONITOR_FLAG = 0;
			_12_XFDISO_FAIL_FLAG = 0;

			WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 1 );
			WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
			OMSRCS_IC_IN_PROGRESS_FLAG = 1;

			IC_FAIL_COUNTER = 0;
			FA1_COMMFAULT_CYC_COUNTER = 0;
			RCS_L_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_FU_TK_POSN_CYC_COUNTER = 0;
			FA3_COMMFAULT_CYC_COUNTER = 0;
			RCS_R_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_R_FU_TK_POSN_CYC_COUNTER = 0;
			FA2_COMMFAULT_CYC_COUNTER = 0;
			RCS_L_A_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_B_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_A_FU_TK_POSN_CYC_COUNTER = 0;
			RCS_L_B_FU_TK_POSN_CYC_COUNTER = 0;
			FA4_COMMFAULT_CYC_COUNTER = 0;
			RCS_R_A_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_R_B_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_R_A_FU_TK_POSN_CYC_COUNTER = 0;
			RCS_R_B_FU_TK_POSN_CYC_COUNTER = 0;

			goto step2;
		}

		if ((ReadCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD ) == 1) && (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1))
		{
			OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 0;
			OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 0;
			OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 0;
			OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 0;
			OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 0;
			OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 0;

			OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 0;
			OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 0;
			OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 0;
			OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 0;
			OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 0;
			OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 0;

			RCS_L_AFT_XFD_VLV_12_GPC_CL_A = 0;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B = 0;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B = 0;
			RCS_L_AFT_XFD_VLV_345_GPC_CL_A = 0;
			RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 0;
			RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 0;

			RCS_R_AFT_XFD_VLV_12_GPC_CL_A = 0;
			RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 0;
			RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 0;
			RCS_R_AFT_XFD_VLV_345_GPC_CL_A = 0;
			RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 0;
			RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 0;

			RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
			RCS_L_AFT_OX_TK_ISLN_V12_GPC_CL_B = 0;
			RCS_L_AFT_FU_TK_ISLN_V12_GPC_CL_B = 0;
			RCS_L_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_L_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_L_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
			RCS_L_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

			RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
			RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 0;
			RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 0;
			RCS_R_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_R_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;
			RCS_R_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
			RCS_R_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

			OMS_L_POD_XFD_VLVS_A_CMD_1_OP = 0;
			OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 0;
			OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP = 0;
			OMS_L_POD_XFD_VLVS_B_CMD_1_OP = 0;
			OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
			OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;

			OMS_R_POD_XFD_VLVS_A_CMD_1_OP = 0;
			OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 0;
			OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP = 0;
			OMS_R_POD_XFD_VLVS_B_CMD_1_OP = 0;
			OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
			OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;

			RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 0;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 0;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 0;
			RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 0;
			RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 0;
			RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 0;

			RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 0;
			RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 0;
			RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 0;
			RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 0;
			RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 0;
			RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 0;

			RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 0;
			RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 0;
			RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 0;

			RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 0;
			RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 0;
			RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 0;
			RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 0;
			RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 0;

			INTERCONNECT_MONITOR_FLAG = 0;
			_12_XFDISO_FAIL_FLAG = 0;
			WriteCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK, 0 );

			OMSRCS_RTRN_TO_NORM_IN_PROGRESS_FLAG = 1;

			if (ReadCOMPOOL_IS( SCP_MODE_2_INDICATOR ) == 0)
			{
				WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 1 );
				WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
				goto step9;
			}
			else
			{
				goto step12;
			}
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1) && (INTERCONNECT_MONITOR_FLAG == 1))
			{
				goto step7;
			}
		}

		goto terminatesequence;


		//// oms to rcs interconnect
	step2:
		if (firstpass_step2)
		{
			RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 1;
			RCS_L_AFT_OX_TK_ISLN_V12_GPC_CL_B = 1;
			RCS_L_AFT_FU_TK_ISLN_V12_GPC_CL_B = 1;
			RCS_L_AFT_OX_TK_ISLN_V345_A_GPC_CL = 1;
			RCS_L_AFT_FU_TK_ISLN_V345_A_GPC_CL = 1;
			RCS_L_AFT_OX_TK_ISLN_V345_B_GPC_CL = 1;
			RCS_L_AFT_FU_TK_ISLN_V345_B_GPC_CL = 1;

			RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 1;
			RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 1;
			RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 1;
			RCS_R_AFT_OX_TK_ISLN_V345_A_GPC_CL = 1;
			RCS_R_AFT_FU_TK_ISLN_V345_A_GPC_CL = 1;
			RCS_R_AFT_OX_TK_ISLN_V345_B_GPC_CL = 1;
			RCS_R_AFT_FU_TK_ISLN_V345_B_GPC_CL = 1;

			firstpass_step2 = false;
			timer_step2 = 0.0;
			timerena_step2 = true;
		}

		if (timer_step2 >= 1.5)
		{
			timerena_step2 = false;
			goto step3;
		}

		goto terminatesequence;


	step3:
		if ((RCS_L_AFT_OX_TANK_ISLN_VLV_12_CL != 1) || (RCS_L_AFT_FU_TANK_ISLN_VLV_12_CL != 1) || (RCS_R_AFT_OX_TANK_ISLN_VLV_12_CL != 1) || (RCS_R_AFT_FU_TANK_ISLN_VLV_12_CL != 1) ||
			(RCS_L_AFT_OX_TANK_ISLN_VLV_12_OP != 0) || (RCS_L_AFT_FU_TANK_ISLN_VLV_12_OP != 0) || (RCS_R_AFT_OX_TANK_ISLN_VLV_12_OP != 0) || (RCS_R_AFT_FU_TANK_ISLN_VLV_12_OP != 0) ||
			(FA_1_INPUT_PROM_SEG_3_10_STATUS == 1) || (FA_3_INPUT_PROM_SEG_3_10_STATUS == 1))
		{
			WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG, 1 );
			IC_FAIL_COUNTER++;
		}
		else
		{
			RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 1;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 1;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 1;
			RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 1;
			RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 1;
			RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 1;
		}

		if ((RCS_L_AFT_OX_TANK_ISLN_VLV_345_A_CL != 1) || (RCS_L_AFT_OX_TANK_ISLN_VLV_345_B_CL != 1) || (RCS_L_AFT_FU_TANK_ISLN_VLV_345_A_CL != 1) || (RCS_L_AFT_FU_TANK_ISLN_VLV_345_B_CL != 1) ||
			(RCS_R_AFT_OX_TANK_ISLN_VLV_345_A_CL != 1) || (RCS_R_AFT_OX_TANK_ISLN_VLV_345_B_CL != 1) || (RCS_R_AFT_FU_TANK_ISLN_VLV_345_A_CL != 1) || (RCS_R_AFT_FU_TANK_ISLN_VLV_345_B_CL != 1) ||
			(FA_2_INPUT_PROM_SEG_3_10_STATUS == 1) || (FA_4_INPUT_PROM_SEG_3_10_STATUS == 1))
		{
			WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG, 1 );
			IC_FAIL_COUNTER++;
		}
		else
		{
			RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 1;
			RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 1;
			RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 1;
			RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 1;
			RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 1;
			RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 1;
		}

		if (IC_FAIL_COUNTER > 1)
		{
			goto step6;
		}
		else
		{
			if (firstpass_step3)
			{
				OMS_L_POD_XFD_VLVS_B_CMD_1_OP = 1;
				OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 1;
				OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP = 1;
				OMS_R_POD_XFD_VLVS_B_CMD_1_OP = 1;
				OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 1;
				OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP = 1;

				firstpass_step3 = false;
				timer_step3 = 0.0;
				timerena_step3 = true;
			}

			if (timer_step3 >= 1.5)
			{
				timerena_step3 = false;

				goto step4;
			}
		}

		goto terminatesequence;


	step4:
		if (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG ) == 0)
		{
			if (((RCS_L_AFT_OX_XFD_VLV_12_OP == 0) || (RCS_L_AFT_FU_XFD_VLV_12_OP == 0) || (RCS_R_OXFU_XFD_VLV_12_OP == 0) || (FA_3_INPUT_PROM_SEG_3_10_STATUS == 1)) &&
				((RCS_R_AFT_OX_XFD_VLV_12_OP == 0) || (RCS_R_AFT_FU_XFD_VLV_12_OP == 0) || (RCS_L_OXFU_XFD_VLV_12_OP == 0) || (FA_4_INPUT_PROM_SEG_3_10_STATUS == 1)))
			{
				_12_XFDISO_FAIL_FLAG = 1;
				IC_FAIL_COUNTER++;
			}
		}

		if (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG ) == 0)
		{
			if (((RCS_L_AFT_OX_XFD_VLV_345_OP == 0) || (RCS_L_AFT_FU_XFD_VLV_345_OP == 0) || (RCS_R_OXFU_XFD_VLV_345_OP == 0) || (FA_4_INPUT_PROM_SEG_3_10_STATUS == 1)) &&
				((RCS_R_AFT_OX_XFD_VLV_345_OP == 0) || (RCS_R_AFT_FU_XFD_VLV_345_OP == 0) || (RCS_L_OXFU_XFD_VLV_345_OP == 0) || (FA_3_INPUT_PROM_SEG_3_10_STATUS == 1)))
			{
				IC_FAIL_COUNTER++;
			}
		}

		if (IC_FAIL_COUNTER == 0)
		{
			goto step11;
		}
		else
		{
			goto step5;
		}


		//// failure processing
	step5:
		if (IC_FAIL_COUNTER > 1)
		{
			if (firstpass_step5)
			{
				RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 0;
				RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 0;
				RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 0;

				RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 0;
				RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 0;
				RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 0;

				RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 0;
				RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 0;
				RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 0;

				RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 0;
				RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 0;
				RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 0;

				OMS_L_POD_XFD_VLVS_B_CMD_1_OP = 0;
				OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
				OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;

				OMS_R_POD_XFD_VLVS_B_CMD_1_OP = 0;
				OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
				OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;

				RCS_L_AFT_XFD_VLV_12_GPC_CL_A = 1;
				RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B = 1;
				RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B = 1;

				RCS_R_AFT_XFD_VLV_12_GPC_CL_A = 1;
				RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 1;
				RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 1;

				RCS_L_AFT_XFD_VLV_345_GPC_CL_A = 1;
				RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 1;
				RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 1;

				RCS_R_AFT_XFD_VLV_345_GPC_CL_A = 1;
				RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 1;
				RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 1;

				OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 1;
				OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
				OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

				OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 1;
				OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
				OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

				firstpass_step5 = false;
				timer_step5 = 0.0;
				timerena_step5 = true;
			}

			if (timer_step5 >= 1.5)
			{
				timerena_step5 = false;

				goto step6;
			}
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG ) == 1) || (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG ) == 1))
			{
				goto step6;
			}
			else
			{
				if (_12_XFDISO_FAIL_FLAG == 1)
				{
					if (firstpass_step5)
					{
						RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 0;
						RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 0;
						RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 0;

						RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 0;
						RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 0;
						RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 0;

						RCS_L_AFT_XFD_VLV_12_GPC_CL_A = 1;
						RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B = 1;
						RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B = 1;

						RCS_R_AFT_XFD_VLV_12_GPC_CL_A = 1;
						RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 1;
						RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 1;

						WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG, 1 );

						firstpass_step5 = false;
						timer_step5 = 0.0;
						timerena_step5 = true;
					}

					if (timer_step5 >= 1.5)
					{
						timerena_step5 = false;

						goto step6;
					}
				}
				else
				{
					if (firstpass_step5)
					{
						RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 0;
						RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 0;
						RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 0;

						RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 0;
						RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 0;
						RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 0;

						RCS_L_AFT_XFD_VLV_345_GPC_CL_A = 1;
						RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 1;
						RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 1;

						RCS_R_AFT_XFD_VLV_345_GPC_CL_A = 1;
						RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 1;
						RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 1;

						WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG, 1 );

						firstpass_step5 = false;
						timer_step5 = 0.0;
						timerena_step5 = true;
					}

					if (timer_step5 >= 1.5)
					{
						timerena_step5 = false;

						goto step6;
					}
				}
			}
		}

		goto terminatesequence;


		//// monitor mode
	step7:
		if (FA_1_INPUT_PROM_SEG_3_10_STATUS == 1)
		{
			FA1_COMMFAULT_CYC_COUNTER++;
			RCS_L_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_FU_TK_POSN_CYC_COUNTER = 0;

			if (FA1_COMMFAULT_CYC_COUNTER == 3)
			{
				WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG, 1 );
				INTERCONNECT_MONITOR_FLAG = 0;

				goto terminatesequence;
			}
		}
		else
		{
			FA1_COMMFAULT_CYC_COUNTER = 0;

			if (RCS_L_AFT_OX_TANK_ISLN_VLV_12_CL == 0)
			{
				RCS_L_OX_TK_POSN_CYC_COUNTER++;

				if (RCS_L_OX_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					_12_XFDISO_FAIL_FLAG = 1;
					WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_L_OX_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_L_AFT_FU_TANK_ISLN_VLV_12_CL == 0)
			{
				RCS_L_FU_TK_POSN_CYC_COUNTER++;

				if (RCS_L_FU_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					_12_XFDISO_FAIL_FLAG = 1;
					WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_L_FU_TK_POSN_CYC_COUNTER = 0;
			}
		}
		goto step7a;


	step7a:
		if (FA_3_INPUT_PROM_SEG_3_10_STATUS == 1)
		{
			FA3_COMMFAULT_CYC_COUNTER++;
			RCS_L_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_FU_TK_POSN_CYC_COUNTER = 0;

			if (FA3_COMMFAULT_CYC_COUNTER == 3)
			{
				WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG, 1 );
				INTERCONNECT_MONITOR_FLAG = 0;

				goto terminatesequence;
			}
		}
		else
		{
			FA3_COMMFAULT_CYC_COUNTER = 0;

			if (RCS_R_AFT_OX_TANK_ISLN_VLV_12_CL == 0)
			{
				RCS_R_OX_TK_POSN_CYC_COUNTER++;

				if (RCS_R_OX_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					_12_XFDISO_FAIL_FLAG = 1;
					WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_R_OX_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_R_AFT_FU_TANK_ISLN_VLV_12_CL == 0)
			{
				RCS_R_FU_TK_POSN_CYC_COUNTER++;

				if (RCS_R_FU_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					_12_XFDISO_FAIL_FLAG = 1;
					WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_R_FU_TK_POSN_CYC_COUNTER = 0;
			}
		}
		goto step8;


	step8:
		if (FA_2_INPUT_PROM_SEG_3_10_STATUS == 1)
		{
			FA2_COMMFAULT_CYC_COUNTER++;
			RCS_L_A_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_R_A_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_A_FU_TK_POSN_CYC_COUNTER = 0;
			RCS_R_A_FU_TK_POSN_CYC_COUNTER = 0;

			if (FA2_COMMFAULT_CYC_COUNTER == 3)
			{
				WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG, 1 );
				INTERCONNECT_MONITOR_FLAG = 0;

				goto terminatesequence;
			}
		}
		else
		{
			FA2_COMMFAULT_CYC_COUNTER = 0;

			if (RCS_L_AFT_OX_TANK_ISLN_VLV_345_A_CL == 0)
			{
				RCS_L_A_OX_TK_POSN_CYC_COUNTER++;

				if (RCS_L_A_OX_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_L_A_OX_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_R_AFT_OX_TANK_ISLN_VLV_345_A_CL == 0)
			{
				RCS_R_A_OX_TK_POSN_CYC_COUNTER++;

				if (RCS_R_A_OX_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_R_A_OX_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_L_AFT_FU_TANK_ISLN_VLV_345_A_CL == 0)
			{
				RCS_L_A_FU_TK_POSN_CYC_COUNTER++;

				if (RCS_L_A_FU_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_L_A_FU_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_R_AFT_FU_TANK_ISLN_VLV_345_A_CL == 0)
			{
				RCS_R_A_FU_TK_POSN_CYC_COUNTER++;

				if (RCS_R_A_FU_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_R_A_FU_TK_POSN_CYC_COUNTER = 0;
			}
		}
		goto step8a;


	step8a:
		if (FA_4_INPUT_PROM_SEG_3_10_STATUS == 1)
		{
			FA4_COMMFAULT_CYC_COUNTER++;
			RCS_L_B_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_R_B_OX_TK_POSN_CYC_COUNTER = 0;
			RCS_L_B_FU_TK_POSN_CYC_COUNTER = 0;
			RCS_R_B_FU_TK_POSN_CYC_COUNTER = 0;

			if (FA4_COMMFAULT_CYC_COUNTER == 3)
			{
				WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG, 1 );
				INTERCONNECT_MONITOR_FLAG = 0;

				goto terminatesequence;
			}
		}
		else
		{
			FA4_COMMFAULT_CYC_COUNTER = 0;

			if (RCS_L_AFT_OX_TANK_ISLN_VLV_345_B_CL == 0)
			{
				RCS_L_B_OX_TK_POSN_CYC_COUNTER++;

				if (RCS_L_B_OX_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_L_B_OX_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_R_AFT_OX_TANK_ISLN_VLV_345_B_CL == 0)
			{
				RCS_R_B_OX_TK_POSN_CYC_COUNTER++;

				if (RCS_R_B_OX_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_R_B_OX_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_L_AFT_FU_TANK_ISLN_VLV_345_B_CL == 0)
			{
				RCS_L_B_FU_TK_POSN_CYC_COUNTER++;

				if (RCS_L_B_FU_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_L_B_FU_TK_POSN_CYC_COUNTER = 0;
			}

			if (RCS_R_AFT_FU_TANK_ISLN_VLV_345_B_CL == 0)
			{
				RCS_R_B_FU_TK_POSN_CYC_COUNTER++;

				if (RCS_R_B_FU_TK_POSN_CYC_COUNTER == 3)
				{
					INTERCONNECT_MONITOR_FLAG = 0;
					WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 1 );
					OMSRCS_IC_IN_PROGRESS_FLAG = 1;

					IC_FAIL_COUNTER++;

					goto step5;
				}
			}
			else
			{
				RCS_R_B_FU_TK_POSN_CYC_COUNTER = 0;
			}
		}

		goto terminatesequence;


		//// nominal return to normal
	step6:
		if (OMSRCS_RTRN_TO_NORM_IN_PROGRESS_FLAG == 1)
		{
			if (firstpass_step6)
			{
				RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
				RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
				RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

				RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
				RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
				RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

				RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
				RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

				RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
				RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

				RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
				RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

				RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
				RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

				firstpass_step6 = false;
				timer_step6 = 0.0;
				timerena_step6 = true;
			}

			if (timer_step6 >= 1.5)
			{
				timerena_step6 = false;

				goto step10;
			}
		}
		else
		{
			if (IC_FAIL_COUNTER > 1)
			{
				if (firstpass_step6)
				{
					RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
					RCS_L_AFT_OX_TK_ISLN_V12_GPC_CL_B = 0;
					RCS_L_AFT_FU_TK_ISLN_V12_GPC_CL_B = 0;

					RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
					RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 0;
					RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 0;

					RCS_L_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
					RCS_L_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;

					RCS_R_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
					RCS_R_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;

					RCS_L_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
					RCS_L_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

					RCS_R_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
					RCS_R_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

					RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
					RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
					RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

					RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
					RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
					RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

					RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
					RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

					RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
					RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

					RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
					RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

					RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
					RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

					firstpass_step6 = false;
					timer_step6 = 0.0;
					timerena_step6 = true;
				}

				if (timer_step6 >= 1.5)
				{
					timerena_step6 = false;

					goto step11;
				}
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG ) == 1)
				{
					if (firstpass_step6)
					{
						RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
						RCS_L_AFT_OX_TK_ISLN_V12_GPC_CL_B = 0;
						RCS_L_AFT_FU_TK_ISLN_V12_GPC_CL_B = 0;

						RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
						RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 0;
						RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 0;

						RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
						RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
						RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

						RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
						RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
						RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

						firstpass_step6 = false;
						timer_step6 = 0.0;
						timerena_step6 = true;
					}

					if (timer_step6 >= 1.5)
					{
						timerena_step6 = false;

						goto step11;
					}
				}
				else
				{
					if (firstpass_step6)
					{
						RCS_L_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
						RCS_L_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;

						RCS_R_AFT_OX_TK_ISLN_V345_A_GPC_CL = 0;
						RCS_R_AFT_FU_TK_ISLN_V345_A_GPC_CL = 0;

						RCS_L_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
						RCS_L_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

						RCS_R_AFT_OX_TK_ISLN_V345_B_GPC_CL = 0;
						RCS_R_AFT_FU_TK_ISLN_V345_B_GPC_CL = 0;

						RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
						RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

						RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
						RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

						RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
						RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

						RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
						RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

						firstpass_step6 = false;
						timer_step6 = 0.0;
						timerena_step6 = true;
					}

					if (timer_step6 >= 1.5)
					{
						timerena_step6 = false;
						goto step11;
					}
				}
			}
		}

		goto terminatesequence;


	step9:
		if (firstpass_step9)
		{
			OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 1;
			OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
			OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
			OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 1;
			OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
			OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

			OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 1;
			OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
			OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
			OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 1;
			OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
			OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

			firstpass_step9 = false;
			timer_step9 = 0.0;
			timerena_step9 = true;
		}

		if (timer_step9 >= 1.5)
		{
			timerena_step9 = false;

			WriteCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK, 0 );

			goto step6;
		}

		goto terminatesequence;


	step10:
		if (firstpass_step10)
		{
			if ((RCS_L_AFT_OX_TANK_ISLN_VLV_12_OP == 1) && (RCS_L_AFT_FU_TANK_ISLN_VLV_12_OP == 1) &&
				(RCS_L_AFT_OX_TANK_ISLN_VLV_12_CL == 0) && (RCS_L_AFT_FU_TANK_ISLN_VLV_12_CL == 0) && (FA_1_INPUT_PROM_SEG_3_10_STATUS == 0))
			{
				RCS_L_AFT_XFD_VLV_12_GPC_CL_A = 1;
				RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B = 1;
				RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B = 1;
				RCS_L_AFT_XFD_VLV_345_GPC_CL_A = 1;
				RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 1;
				RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 1;
			}
			else
			{
				RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 1;
				RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 1;
				RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 1;
				RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 1;
				RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 1;
				RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 1;
			}

			if ((RCS_R_AFT_OX_TANK_ISLN_VLV_12_OP == 1) && (RCS_R_AFT_FU_TANK_ISLN_VLV_12_OP == 1) &&
				(RCS_R_AFT_OX_TANK_ISLN_VLV_12_CL == 0) && (RCS_R_AFT_FU_TANK_ISLN_VLV_12_CL == 0) && (FA_3_INPUT_PROM_SEG_3_10_STATUS == 0))
			{
				RCS_R_AFT_XFD_VLV_12_GPC_CL_A = 1;
				RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 1;
				RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 1;
				RCS_R_AFT_XFD_VLV_345_GPC_CL_A = 1;
				RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 1;
				RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 1;
			}
			else
			{
				RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 1;
				RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 1;
				RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 1;
				RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 1;
				RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 1;
				RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 1;
			}

			WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 0 );
			WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 0 );

			firstpass_step10 = false;
			timer_step10 = 0.0;
			timerena_step10 = true;
		}

		if (timer_step10 >= 1.5)
		{
			timerena_step10 = false;

			goto step16;
		}

		goto terminatesequence;


		//// finish interconnect
	step11:
		if (ReadCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK ) == 1)
		{
			LOCAL_OMS_L_POD_OX_XFD_VLV_B_POSN_OP = 1;
		}
		else if (ReadCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK ) == 1)
		{
			LOCAL_OMS_L_POD_FU_XFD_VLV_B_POSN_OP = 1;
		}
		else if (ReadCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK ) == 1)
		{
			LOCAL_OMS_R_POD_OX_XFD_VLV_B_POSN_OP = 1;
		}
		else if (ReadCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK ) == 1)
		{
			LOCAL_OMS_R_POD_FU_XFD_VLV_B_POSN_OP = 1;
		}

		if (IC_FAIL_COUNTER > 1)
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
			OMSRCS_IC_IN_PROGRESS_FLAG = 0;
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
			WriteCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK, 0 );
			WriteCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK, 0 );

			goto step16;
		}
		else
		{
			if ((OMSRCS_IC_IN_PROGRESS_FLAG == 1) && (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 0) &&
				((LOCAL_OMS_L_POD_OX_XFD_VLV_B_POSN_OP == 0) || (LOCAL_OMS_L_POD_FU_XFD_VLV_B_POSN_OP == 0) ||
				(LOCAL_OMS_R_POD_OX_XFD_VLV_B_POSN_OP == 0) || (LOCAL_OMS_R_POD_FU_XFD_VLV_B_POSN_OP == 0) || (FA_2_INPUT_PROM_SEG_3_10_STATUS == 1)))
			{
				if (firstpass_step11)
				{
					OMS_L_POD_XFD_VLVS_A_CMD_1_OP = 1;
					OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 1;
					OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP = 1;

					OMS_R_POD_XFD_VLVS_A_CMD_1_OP = 1;
					OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 1;
					OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP = 1;

					firstpass_step11 = false;
					timer_step11 = 0.0;
					timerena_step11 = true;
				}

				if (timer_step11 >= 1.5)
				{
					timerena_step11 = false;

					if ((OMS_L_POD_OX_XFD_VLV_A_POSN_OP == 0) || (OMS_L_POD_FU_XFD_VLV_A_POSN_OP == 0) ||
						(OMS_R_POD_OX_XFD_VLV_A_POSN_OP == 0) || (OMS_R_POD_FU_XFD_VLV_A_POSN_OP == 0) || (FA_1_INPUT_PROM_SEG_3_10_STATUS == 1))
					{
						WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
						OMSRCS_IC_IN_PROGRESS_FLAG = 0;
						WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
						WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG, 1 );
						WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
						WriteCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK, 0 );
						WriteCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK, 0 );
						WriteCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK, 0 );
						WriteCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK, 0 );

						goto terminatesequence;
					}
				}
				else
				{
					goto terminatesequence;
				}
			}

			if ((IC_FAIL_COUNTER == 0) || (OMSRCS_IC_IN_PROGRESS_FLAG == 1))
			{
				WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG, 1 );
				INTERCONNECT_MONITOR_FLAG = 1;
				OMSRCS_IC_IN_PROGRESS_FLAG = 0;
				WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 0 );
				WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 0 );

				goto step7;
			}
			else
			{
				WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG, 1 );
				OMSRCS_IC_IN_PROGRESS_FLAG = 0;
				WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 0 );
				WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 0 );

				goto terminatesequence;
			}
		}


		//// mode 2 return to normal
	step12:
		if (firstpass_step12)
		{
			RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
			RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
			RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

			RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
			RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
			RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;

			RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
			RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

			RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP = 1;
			RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP = 1;

			RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
			RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

			RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP = 1;
			RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP = 1;

			firstpass_step12 = false;
			timer_step12 = 0.0;
			timerena_step12 = true;
		}

		if (timer_step12 >= 1.5)
		{
			timerena_step12 = false;

			goto step13;
		}

		goto terminatesequence;


	step13:
		if ((RCS_L_AFT_OX_TANK_ISLN_VLV_12_OP == 1) && (RCS_L_AFT_FU_TANK_ISLN_VLV_12_OP == 1) &&
			(RCS_L_AFT_OX_TANK_ISLN_VLV_12_CL == 0) && (RCS_L_AFT_FU_TANK_ISLN_VLV_12_CL == 0) && (FA_1_INPUT_PROM_SEG_3_10_STATUS == 0))
		{
			RCS_L_AFT_XFD_VLV_12_GPC_CL_A = 1;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B = 1;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B = 1;

			RCS_L_AFT_XFD_VLV_345_GPC_CL_A = 1;
			RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 1;
			RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 1;
		}
		else
		{
			RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 1;
			RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B = 1;
			RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B = 1;

			RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 1;
			RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 1;
			RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 1;
		}
		goto step14;


	step14:
		if (firstpass_step14)
		{
			if ((RCS_R_AFT_OX_TANK_ISLN_VLV_12_OP == 1) && (RCS_R_AFT_FU_TANK_ISLN_VLV_12_OP == 1) &&
				(RCS_R_AFT_OX_TANK_ISLN_VLV_12_CL == 0) && (RCS_R_AFT_FU_TANK_ISLN_VLV_12_CL == 0) && (FA_3_INPUT_PROM_SEG_3_10_STATUS == 0))
			{
				RCS_R_AFT_XFD_VLV_12_GPC_CL_A = 1;
				RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 1;
				RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 1;

				RCS_R_AFT_XFD_VLV_345_GPC_CL_A = 1;
				RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 1;
				RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 1;
			}
			else
			{
				RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 1;
				RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 1;
				RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 1;

				RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 1;
				RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 1;
				RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 1;
			}

			firstpass_step14 = false;
			timer_step14 = 0.0;
			timerena_step14 = true;
		}

		if (timer_step14 >= 1.5)
		{
			timerena_step14 = false;

			goto step15;
		}

		goto terminatesequence;


	step15:
		if (firstpass_step15)
		{
			OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 1;
			OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
			OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
			OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 1;
			OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
			OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

			OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 1;
			OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
			OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
			OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 1;
			OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
			OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

			firstpass_step15 = false;
			timer_step15 = 0.0;
			timerena_step15 = true;
		}

		if (timer_step15 >= 1.5)
		{
			timerena_step15 = false;

			goto step16;
		}

		goto terminatesequence;


	step16:
		WriteCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG, 0 );
		WriteCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG, 0 );
		WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG, 0 );
		WriteCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG, 0 );
		WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG, 0 );
		OMSRCS_RTRN_TO_NORM_IN_PROGRESS_FLAG = 0;

		goto terminatesequence;



	terminatesequence:
		// outputs
		unsigned short FA1_IOM7_CH1 = 0;
		unsigned short FA1_IOM7_CH2 = 0;
		unsigned short FA1_IOM15_CH1 = 0;
		unsigned short FA1_IOM15_CH2 = 0;
		unsigned short FA2_IOM7_CH1 = 0;
		unsigned short FA2_IOM7_CH2 = 0;
		unsigned short FA2_IOM15_CH1 = 0;
		unsigned short FA2_IOM15_CH2 = 0;
		unsigned short FA3_IOM7_CH2 = 0;
		unsigned short FA3_IOM15_CH2 = 0;
		unsigned short FA4_IOM7_CH2 = 0;
		unsigned short FA4_IOM15_CH2 = 0;

		FA2_IOM7_CH1 |= (OMS_L_POD_XFD_VLVS_A_CMD_1_CL & 0b1) << 12;
		FA1_IOM7_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL & 0b1) << 12;
		FA1_IOM7_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL & 0b1) << 8;
		FA1_IOM15_CH1 |= (OMS_L_POD_XFD_VLVS_B_CMD_1_CL & 0b1) << 12;
		FA2_IOM15_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL & 0b1) << 12;
		FA2_IOM15_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL & 0b1) << 8;

		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_A_CMD_1_CL & 0b1) << 14;
		FA1_IOM7_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL & 0b1) << 14;
		FA1_IOM7_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL & 0b1) << 10;
		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_B_CMD_1_CL & 0b1) << 14;
		FA2_IOM15_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL & 0b1) << 14;
		FA2_IOM15_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL & 0b1) << 10;

		FA4_IOM7_CH2 |= (RCS_L_AFT_XFD_VLV_12_GPC_CL_A & 0b1) << 0;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_VLV_12_GPC_CL_B & 0b1) << 0;
		FA3_IOM15_CH2 |= (RCS_L_AFT_FU_XFD_VLV_12_GPC_CL_B & 0b1) << 9;
		FA1_IOM7_CH2 |= (RCS_L_AFT_XFD_VLV_345_GPC_CL_A & 0b1) << 0;
		FA2_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_V_345_GPC_CL_B & 0b1) << 0;
		FA2_IOM7_CH2 |= (RCS_L_AFT_FU_XFD_V_345_GPC_CL_B & 0b1) << 2;

		FA3_IOM15_CH2 |= (RCS_R_AFT_XFD_VLV_12_GPC_CL_A & 0b1) << 0;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_12_GPC_CL_B & 0b1) << 0;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_12_GPC_CL_B & 0b1) << 9;
		FA2_IOM15_CH2 |= (RCS_R_AFT_XFD_VLV_345_GPC_CL_A & 0b1) << 0;
		FA1_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_345_GPC_CL_B & 0b1) << 0;
		FA1_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_345_GPC_CL_B & 0b1) << 2;

		FA2_IOM7_CH2 |= (RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A & 0b1) << 4;
		FA1_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V12_GPC_CL_B & 0b1) << 4;
		FA1_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V12_GPC_CL_B & 0b1) << 2;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V345_A_GPC_CL & 0b1) << 4;
		FA3_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V345_A_GPC_CL & 0b1) << 2;
		FA4_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V345_B_GPC_CL & 0b1) << 4;
		FA4_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V345_B_GPC_CL & 0b1) << 2;

		FA1_IOM15_CH2 |= (RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A & 0b1) << 4;
		FA2_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B & 0b1) << 4;
		FA2_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B & 0b1) << 2;
		FA3_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V345_A_GPC_CL & 0b1) << 4;
		FA3_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V345_A_GPC_CL & 0b1) << 2;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V345_B_GPC_CL & 0b1) << 4;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V345_B_GPC_CL & 0b1) << 2;

		FA2_IOM7_CH1 |= (OMS_L_POD_XFD_VLVS_A_CMD_1_OP & 0b1) << 11;
		FA1_IOM7_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP & 0b1) << 11;
		FA1_IOM7_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP & 0b1) << 7;
		FA1_IOM15_CH1 |= (OMS_L_POD_XFD_VLVS_B_CMD_1_OP & 0b1) << 11;
		FA2_IOM15_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP & 0b1) << 11;
		FA2_IOM15_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP & 0b1) << 7;

		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_A_CMD_1_OP & 0b1) << 13;
		FA1_IOM7_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP & 0b1) << 13;
		FA1_IOM7_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP & 0b1) << 9;
		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_B_CMD_1_OP & 0b1) << 13;
		FA2_IOM15_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP & 0b1) << 13;
		FA2_IOM15_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP & 0b1) << 9;

		FA4_IOM7_CH2 |= (RCS_L_AFT_XFD_VLV_12_GPC_OP_A & 0b1) << 1;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_VLV_12_GPC_OP_B & 0b1) << 1;
		FA3_IOM15_CH2 |= (RCS_L_AFT_FU_XFD_VLV_12_GPC_OP_B & 0b1) << 10;
		FA1_IOM7_CH2 |= (RCS_L_AFT_XFD_VLV_345_GPC_OP_A & 0b1) << 1;
		FA2_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_V_345_GPC_OP_B & 0b1) << 1;
		FA2_IOM7_CH2 |= (RCS_L_AFT_FU_XFD_V_345_GPC_OP_B & 0b1) << 3;

		FA3_IOM15_CH2 |= (RCS_R_AFT_XFD_VLV_12_GPC_OP_A & 0b1) << 1;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_12_GPC_OP_B & 0b1) << 1;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_12_GPC_OP_B & 0b1) << 10;
		FA2_IOM15_CH2 |= (RCS_R_AFT_XFD_VLV_345_GPC_OP_A & 0b1) << 1;
		FA1_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_345_GPC_OP_B & 0b1) << 1;
		FA1_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_345_GPC_OP_B & 0b1) << 3;

		FA2_IOM7_CH2 |= (RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A & 0b1) << 5;
		FA1_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B & 0b1) << 5;
		FA1_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B & 0b1) << 3;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_345_A_GPC_OP & 0b1) << 5;
		FA3_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_345_A_GPC_OP & 0b1) << 3;
		FA4_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_345_B_GPC_OP & 0b1) << 5;
		FA4_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_345_B_GPC_OP & 0b1) << 3;

		FA1_IOM15_CH2 |= (RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A & 0b1) << 5;
		FA2_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B & 0b1) << 5;
		FA2_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B & 0b1) << 3;
		FA3_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_345_A_GPC_OP & 0b1) << 5;
		FA3_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_345_A_GPC_OP & 0b1) << 3;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_345_B_GPC_OP & 0b1) << 5;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_345_B_GPC_OP & 0b1) << 3;


		unsigned short tmp = ReadCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, tmp | FA1_IOM7_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA1_IOM7_CH2_DATA, tmp | FA1_IOM7_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, tmp | FA1_IOM15_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA1_IOM15_CH2_DATA, tmp | FA1_IOM15_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, tmp | FA2_IOM7_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA2_IOM7_CH2_DATA, tmp | FA2_IOM7_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, tmp | FA2_IOM15_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA2_IOM15_CH2_DATA, tmp | FA2_IOM15_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH2_DATA, tmp | FA3_IOM7_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA3_IOM15_CH2_DATA, tmp | FA3_IOM15_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH2_DATA, tmp | FA4_IOM7_CH2 );

		tmp = ReadCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA );
		WriteCOMPOOL_IS( SCP_FA4_IOM15_CH2_DATA, tmp | FA4_IOM15_CH2 );
		return;
	}

	bool ABT_OMS_RCS_CONN::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ABT_OMS_RCS_CONN::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool ABT_OMS_RCS_CONN::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 301:
			case 302:
			case 303:
			case 304:
			case 601:
			case 602:
				return true;
		}
		return false;
	}
}
