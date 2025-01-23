#include "RCS_RCS_XFEED.h"


namespace dps
{
	RCS_RCS_XFEED::RCS_RCS_XFEED( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RCS_RCS_XFEED" ),
		POST_SEQ_CMD_TERM_FLAG(0),
		firstpass_subseqa(true), firstpass_subseqb(true), firstpass_subseqc(true),
		firstpass_stepa1(true), firstpass_stepa3(true), firstpass_stepa4(true), firstpass_stepa5(true), firstpass_stepa6(true), firstpass_stepb1(true), firstpass_stepb2(true),
		firstpass_stepb3(true), firstpass_stepc1(true), firstpass_stepc3(true), firstpass_stepc4(true), firstpass_stepc5(true), firstpass_stepc6(true),
		timer_stepa3(0.0), timer_stepa4(0.0), timer_stepa5(0.0), timer_stepa6(0.0), timer_stepb1(0.0), timer_stepb2(0.0),
		timer_stepb3(0.0), timer_stepc3(0.0), timer_stepc4(0.0), timer_stepc5(0.0), timer_stepc6(0.0),
		timerena_stepa3(false), timerena_stepa4(false), timerena_stepa5(false), timerena_stepa6(false), timerena_stepb1(false), timerena_stepb2(false),
		timerena_stepb3(false), timerena_stepc3(false), timerena_stepc4(false), timerena_stepc5(false), timerena_stepc6(false)
	{
		return;
	}

	RCS_RCS_XFEED::~RCS_RCS_XFEED( void )
	{
		return;
	}

	void RCS_RCS_XFEED::OnPostStep( double simt, double simdt, double mjd )
	{
		// handle timers
		if (timerena_stepa3) timer_stepa3 += simdt;
		if (timerena_stepa4) timer_stepa4 += simdt;
		if (timerena_stepa5) timer_stepa5 += simdt;
		if (timerena_stepa6) timer_stepa6 += simdt;
		if (timerena_stepb1) timer_stepb1 += simdt;
		if (timerena_stepb2) timer_stepb2 += simdt;
		if (timerena_stepb3) timer_stepb3 += simdt;
		if (timerena_stepc3) timer_stepc3 += simdt;
		if (timerena_stepc4) timer_stepc4 += simdt;
		if (timerena_stepc5) timer_stepc5 += simdt;
		if (timerena_stepc6) timer_stepc6 += simdt;

	//step1:
		if ((ReadCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD ) == 1) || (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1))
		{
			firstpass_subseqa = true;
			firstpass_subseqb = true;
			firstpass_subseqc = true;
			WriteCOMPOOL_IS( SCP_RECONFIG_CMPL, 1 );
			WriteCOMPOOL_IS( SCP_CROSSFEED_OPEN, 0 );
			POST_SEQ_CMD_TERM_FLAG = 0;

			goto terminatesequence;
		}
		else
		{
			goto step2;
		}


	step2:
		if ((ReadCOMPOOL_IS( SCP_SEL_RCS_MASTER_CROSSFEED_FROM_LEFT ) == 1) || (ReadCOMPOOL_IS( SCP_SEL_RCS_MASTER_CROSSFEED_FROM_RT ) == 1))
		{
			WriteCOMPOOL_IS( SCP_FEED_FROM_LEFT_RCS, 0 );
			WriteCOMPOOL_IS( SCP_FEED_FROM_RIGHT_RCS, 0 );
		}
		goto step3;


	step3:
		if ((ReadCOMPOOL_IS( SCP_SEL_RCS_MASTER_CROSSFEED_FROM_LEFT ) == 1) || (ReadCOMPOOL_IS( SCP_FEED_FROM_LEFT_RCS ) == 1))
		{
			if (firstpass_subseqa)
			{
				firstpass_subseqb = true;
				firstpass_subseqc = true;
				WriteCOMPOOL_IS( SCP_CROSSFEED_OPEN, 0 );
				WriteCOMPOOL_IS( SCP_RECONFIG_CMPL, 0 );

				firstpass_subseqa = false;
			}

			SubsequenceA();
		}
		else
		{
			goto step4;
		}

		goto terminatesequence;


	step4:
		if ((ReadCOMPOOL_IS( SCP_SEL_RCS_MASTER_CROSSFEED_FROM_RT ) == 1) || (ReadCOMPOOL_IS( SCP_FEED_FROM_RIGHT_RCS ) == 1))
		{
			if (firstpass_subseqc)
			{
				firstpass_subseqa = true;
				firstpass_subseqb = true;
				WriteCOMPOOL_IS( SCP_CROSSFEED_OPEN, 0 );
				WriteCOMPOOL_IS( SCP_RECONFIG_CMPL, 0 );

				firstpass_subseqc = false;
			}

			SubsequenceC();
		}
		else
		{
			goto step5;
		}

		goto terminatesequence;


	step5:
		if ((ReadCOMPOOL_IS( SCP_SEL_RCS_MASTER_CROSSFEED_FROM_LEFT ) == 0) && (ReadCOMPOOL_IS( SCP_SEL_RCS_MASTER_CROSSFEED_FROM_RT ) == 0) &&
			(ReadCOMPOOL_IS( SCP_FEED_FROM_LEFT_RCS ) == 0) && (ReadCOMPOOL_IS( SCP_FEED_FROM_RIGHT_RCS ) == 0))
		{
			if (firstpass_subseqb)
			{
				firstpass_subseqa = true;
				firstpass_subseqc = true;
				WriteCOMPOOL_IS( SCP_CROSSFEED_OPEN, 0 );
				WriteCOMPOOL_IS( SCP_RECONFIG_CMPL, 0 );

				firstpass_subseqb = false;
			}

			SubsequenceB();

		}

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

		FA2_IOM7_CH1 |= (OMS_L_POD_XFD_VLVS_A_CMD_1_OP & 0b1) << 11;
		FA2_IOM7_CH1 |= (OMS_L_POD_XFD_VLVS_A_CMD_1_CL & 0b1) << 12;
		FA1_IOM7_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP & 0b1) << 11;
		FA1_IOM7_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL & 0b1) << 12;
		FA1_IOM15_CH1 |= (OMS_L_POD_XFD_VLVS_B_CMD_1_OP & 0b1) << 11;
		FA1_IOM15_CH1 |= (OMS_L_POD_XFD_VLVS_B_CMD_1_CL & 0b1) << 12;
		FA2_IOM15_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP & 0b1) << 11;
		FA2_IOM15_CH1 |= (OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL & 0b1) << 12;
		FA1_IOM7_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP & 0b1) << 7;
		FA1_IOM7_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL & 0b1) << 8;
		FA2_IOM15_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP & 0b1) << 7;
		FA2_IOM15_CH1 |= (OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL & 0b1) << 8;

		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_A_CMD_1_OP & 0b1) << 13;
		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_A_CMD_1_CL & 0b1) << 14;
		FA1_IOM7_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP & 0b1) << 13;
		FA1_IOM7_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL & 0b1) << 14;
		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_B_CMD_1_OP & 0b1) << 13;
		FA1_IOM15_CH1 |= (OMS_R_POD_XFD_VLVS_B_CMD_1_CL & 0b1) << 14;
		FA2_IOM15_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP & 0b1) << 13;
		FA2_IOM15_CH1 |= (OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL & 0b1) << 14;
		FA1_IOM7_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP & 0b1) << 9;
		FA1_IOM7_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL & 0b1) << 10;
		FA2_IOM15_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP & 0b1) << 9;
		FA2_IOM15_CH1 |= (OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL & 0b1) << 10;

		FA4_IOM7_CH2 |= (RCS_L_AFT_XFD_VLV_12_GPC_OP_A & 0b1) << 1;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_V_12_GPC_OP_B & 0b1) << 1;
		FA3_IOM15_CH2 |= (RCS_L_AFT_FU_XFD_V_12_GPC_OP_B & 0b1) << 10;
		FA1_IOM7_CH2 |= (RCS_L_AFT_XFD_VLV_345_GPC_OP_A & 0b1) << 1;
		FA2_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_V_345_GPC_OP_B & 0b1) << 1;
		FA2_IOM7_CH2 |= (RCS_L_AFT_FU_XFD_V_345_GPC_OP_B & 0b1) << 3;

		FA4_IOM7_CH2 |= (RCS_L_AFT_XFD_V_12_GPC_CL_A & 0b1) << 0;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_V_12_GPC_CL_B & 0b1) << 0;
		FA3_IOM15_CH2 |= (RCS_L_AFT_FU_XFD_V_12_GPC_CL_B & 0b1) << 9;
		FA1_IOM7_CH2 |= (RCS_L_AFT_XFD_V_345_GPC_CL_A & 0b1) << 0;
		FA2_IOM7_CH2 |= (RCS_L_AFT_OX_XFD_V_345_GPC_CL_B & 0b1) << 0;
		FA2_IOM7_CH2 |= (RCS_L_AFT_FU_XFD_V_345_GPC_CL_B & 0b1) << 2;

		FA3_IOM15_CH2 |= (RCS_R_AFT_XFD_VLV_12_GPC_OP_A & 0b1) << 1;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_12_GPC_OP_B & 0b1) << 1;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_12_GPC_OP_B & 0b1) << 10;
		FA2_IOM15_CH2 |= (RCS_R_AFT_XFD_VLV_345_GPC_OP_A & 0b1) << 1;
		FA1_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_345_GPC_OP_B & 0b1) << 1;
		FA1_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_345_GPC_OP_B & 0b1) << 3;

		FA3_IOM15_CH2 |= (RCS_R_AFT_XFD_V_12_GPC_CL_A & 0b1) << 0;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_12_GPC_CL_B & 0b1) << 0;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_12_GPC_CL_B & 0b1) << 9;
		FA2_IOM15_CH2 |= (RCS_R_AFT_XFD_V_345_GPC_CL_A & 0b1) << 0;
		FA1_IOM15_CH2 |= (RCS_R_AFT_OX_XFD_V_345_GPC_CL_B & 0b1) << 0;
		FA1_IOM15_CH2 |= (RCS_R_AFT_FU_XFD_V_345_GPC_CL_B & 0b1) << 2;

		FA2_IOM7_CH2 |= (RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A & 0b1) << 5;
		FA1_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B & 0b1) << 5;
		FA1_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B & 0b1) << 3;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_OP & 0b1) << 5;
		FA3_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_OP & 0b1) << 3;
		FA4_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_OP & 0b1) << 5;
		FA4_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_OP & 0b1) << 3;

		FA2_IOM7_CH2 |= (RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A & 0b1) << 4;
		FA1_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_12_GPC_CL_B & 0b1) << 4;
		FA1_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_12_GPC_CL_B & 0b1) << 2;
		FA3_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_CL & 0b1) << 4;
		FA3_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_CL & 0b1) << 2;
		FA4_IOM7_CH2 |= (RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_CL & 0b1) << 4;
		FA4_IOM7_CH2 |= (RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_CL & 0b1) << 2;

		FA1_IOM15_CH2 |= (RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A & 0b1) << 5;
		FA2_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B & 0b1) << 5;
		FA2_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B & 0b1) << 3;
		FA3_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_OP & 0b1) << 5;
		FA3_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_OP & 0b1) << 3;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_OP & 0b1) << 5;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_OP & 0b1) << 3;

		FA1_IOM15_CH2 |= (RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A & 0b1) << 4;
		FA2_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B & 0b1) << 4;
		FA2_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B & 0b1) << 2;
		FA3_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_CL & 0b1) << 4;
		FA3_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_CL & 0b1) << 2;
		FA4_IOM15_CH2 |= (RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_CL & 0b1) << 4;
		FA4_IOM15_CH2 |= (RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_CL & 0b1) << 2;

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

	void RCS_RCS_XFEED::SubsequenceA( void )
	{
		//// left to right RCS crossfeed sequence

		// step a1
		if (ReadCOMPOOL_IS( SCP_CROSSFEED_OPEN ) == 1)
		{
			if (POST_SEQ_CMD_TERM_FLAG == 1)
			{
				SubsequenceE();
			}
		}
		else
		{
			if (firstpass_stepa1)
			{
				SubsequenceE();

				firstpass_stepa1 = false;
			}
			else
			{
				// step a3
				if (firstpass_stepa3)
				{
					OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 1;
					OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
					OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 1;
					OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
					OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
					OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;
					OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 1;
					OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
					OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 1;
					OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
					OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
					OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

					WriteCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK, 0 );
					WriteCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK, 0 );
					WriteCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK, 0 );
					WriteCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK, 0 );

					firstpass_stepa3 = false;
					timer_stepa3 = 0.0;
					timerena_stepa3 = true;
				}

				if (timer_stepa3 >= 1.5)
				{
					timerena_stepa3 = false;

					// step a4
					if (firstpass_stepa4)
					{
						RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 1;
						RCS_L_AFT_OX_XFD_V_12_GPC_OP_B = 1;
						RCS_L_AFT_FU_XFD_V_12_GPC_OP_B = 1;
						RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 1;
						RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 1;
						RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 1;
						RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 1;
						RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 1;
						RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 1;
						RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 1;
						RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 1;
						RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 1;

						firstpass_stepa4 = false;
						timer_stepa4 = 0.0;
						timerena_stepa4 = true;
					}

					if (timer_stepa4 >= 1.5)
					{
						timerena_stepa4 = false;

						// step a5
						if (firstpass_stepa5)
						{
							RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
							RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
							RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;
							RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_OP = 1;
							RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_OP = 1;
							RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_OP = 1;
							RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_OP = 1;

							firstpass_stepa5 = false;
							timer_stepa5 = 0.0;
							timerena_stepa5 = true;
						}

						if (timer_stepa5 >= 1.5)
						{
							timerena_stepa5 = false;

							// step a6
							if (firstpass_stepa6)
							{
								RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 1;
								RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 1;
								RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 1;
								RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_CL = 1;
								RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_CL = 1;
								RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_CL = 1;
								RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_CL = 1;

								firstpass_stepa6 = false;
								timer_stepa6 = 0.0;
								timerena_stepa6 = true;
							}

							if (timer_stepa6 >= 1.5)
							{
								timerena_stepa6 = false;

								WriteCOMPOOL_IS( SCP_CROSSFEED_OPEN, 1 );
								POST_SEQ_CMD_TERM_FLAG = 1;
							}
						}
					}
				}
			}
		}
		return;
	}

	void RCS_RCS_XFEED::SubsequenceB( void )
	{
		//// reconfiguration sequence

		// step b1
		if (ReadCOMPOOL_IS( SCP_RECONFIG_CMPL ) == 1)
		{
			if (POST_SEQ_CMD_TERM_FLAG == 1)
			{
				SubsequenceE();
			}
		}
		else
		{
			if (firstpass_stepb1)
			{
				SubsequenceE();

				firstpass_stepb1 = false;
			}
			else
			{
				// step b2
				if (firstpass_stepb2)
				{
					RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
					RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
					RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;
					RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_OP = 1;
					RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_OP = 1;
					RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_OP = 1;
					RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_OP = 1;
					RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
					RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
					RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;
					RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_OP = 1;
					RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_OP = 1;
					RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_OP = 1;
					RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_OP = 1;

					firstpass_stepb2 = false;
					timer_stepb2 = 0.0;
					timerena_stepb2 = true;
				}

				if (timer_stepb2 >= 1.5)
				{
					timerena_stepb2 = false;

					// step b3
					if (firstpass_stepb3)
					{
						RCS_L_AFT_XFD_V_12_GPC_CL_A = 1;
						RCS_L_AFT_OX_XFD_V_12_GPC_CL_B = 1;
						RCS_L_AFT_FU_XFD_V_12_GPC_CL_B = 1;
						RCS_L_AFT_XFD_V_345_GPC_CL_A = 1;
						RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 1;
						RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 1;
						RCS_R_AFT_XFD_V_12_GPC_CL_A = 1;
						RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 1;
						RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 1;
						RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 1;
						RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 1;
						RCS_R_AFT_XFD_V_345_GPC_CL_A = 1;

						firstpass_stepb3 = false;
						timer_stepb3 = 0.0;
						timerena_stepb3 = true;
					}

					if (timer_stepb3 >= 1.5)
					{
						timerena_stepb3 = false;

						POST_SEQ_CMD_TERM_FLAG = 1;
						WriteCOMPOOL_IS( SCP_RECONFIG_CMPL, 1 );
					}
				}
			}
		}
		return;
	}

	void RCS_RCS_XFEED::SubsequenceC( void )
	{
		//// right to left RCS crossfeed sequence

		// step c1
		if (ReadCOMPOOL_IS( SCP_CROSSFEED_OPEN ) == 1)
		{
			if (POST_SEQ_CMD_TERM_FLAG == 1)
			{
				SubsequenceE();
			}
		}
		else
		{
			if (firstpass_stepc1)
			{
				SubsequenceE();

				firstpass_stepc1 = false;
			}
			else
			{
				// step c3
				if (firstpass_stepc3)
				{
					OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 1;
					OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
					OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 1;
					OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
					OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
					OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;
					OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 1;
					OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 1;
					OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 1;
					OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 1;
					OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 1;
					OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 1;

					WriteCOMPOOL_IS( SCP_OMS_L_POD_OX_XFD_B_MASK, 0 );
					WriteCOMPOOL_IS( SCP_OMS_L_POD_FU_XFD_B_MASK, 0 );
					WriteCOMPOOL_IS( SCP_OMS_R_POD_OX_XFD_B_MASK, 0 );
					WriteCOMPOOL_IS( SCP_OMS_R_POD_FU_XFD_B_MASK, 0 );

					firstpass_stepc3 = false;
					timer_stepc3 = 0.0;
					timerena_stepc3 = true;
				}

				if (timer_stepc3 >= 1.5)
				{
					timerena_stepc3 = false;

					// step c4
					if (firstpass_stepc4)
					{
						RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 1;
						RCS_L_AFT_OX_XFD_V_12_GPC_OP_B = 1;
						RCS_L_AFT_FU_XFD_V_12_GPC_OP_B = 1;
						RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 1;
						RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 1;
						RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 1;
						RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 1;
						RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 1;
						RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 1;
						RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 1;
						RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 1;
						RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 1;

						firstpass_stepc4 = false;
						timer_stepc4 = 0.0;
						timerena_stepc4 = true;
					}

					if (timer_stepc4 >= 1.5)
					{
						timerena_stepc4 = false;

						// step c5
						if (firstpass_stepc5)
						{
							RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 1;
							RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 1;
							RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 1;
							RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_OP = 1;
							RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_OP = 1;
							RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_OP = 1;
							RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_OP = 1;

							firstpass_stepc5 = false;
							timer_stepc5 = 0.0;
							timerena_stepc5 = true;
						}

						if (timer_stepc5 >= 1.5)
						{
							timerena_stepc5 = false;

							// step c6
							if (firstpass_stepc6)
							{
								RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 1;
								RCS_L_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 1;
								RCS_L_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 1;
								RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_CL = 1;
								RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_CL = 1;
								RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_CL = 1;
								RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_CL = 1;

								firstpass_stepc6 = false;
								timer_stepc6 = 0.0;
								timerena_stepc6 = true;
							}

							if (timer_stepc6 >= 1.5)
							{
								timerena_stepc6 = false;

								WriteCOMPOOL_IS( SCP_CROSSFEED_OPEN, 1 );
								POST_SEQ_CMD_TERM_FLAG = 1;
							}
						}
					}
				}
			}
		}
		return;
	}

	void RCS_RCS_XFEED::SubsequenceE( void )
	{
		RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A = 0;
		RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 0;
		RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 0;
		RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_OP = 0;
		RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_OP = 0;
		RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_OP = 0;
		RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_OP = 0;
		RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
		RCS_L_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 0;
		RCS_L_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 0;
		RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_CL = 0;
		RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_CL = 0;
		RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_CL = 0;
		RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_CL = 0;
		RCS_L_AFT_XFD_VLV_12_GPC_OP_A = 0;
		RCS_L_AFT_OX_XFD_V_12_GPC_OP_B = 0;
		RCS_L_AFT_FU_XFD_V_12_GPC_OP_B = 0;
		RCS_L_AFT_XFD_VLV_345_GPC_OP_A = 0;
		RCS_L_AFT_OX_XFD_V_345_GPC_OP_B = 0;
		RCS_L_AFT_FU_XFD_V_345_GPC_OP_B = 0;
		RCS_L_AFT_XFD_V_12_GPC_CL_A = 0;
		RCS_L_AFT_OX_XFD_V_12_GPC_CL_B = 0;
		RCS_L_AFT_FU_XFD_V_12_GPC_CL_B = 0;
		RCS_L_AFT_XFD_V_345_GPC_CL_A = 0;
		RCS_L_AFT_OX_XFD_V_345_GPC_CL_B = 0;
		RCS_L_AFT_FU_XFD_V_345_GPC_CL_B = 0;
		RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A = 0;
		RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B = 0;
		RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B = 0;
		RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_OP = 0;
		RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_OP = 0;
		RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_OP = 0;
		RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_OP = 0;
		RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A = 0;
		RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B = 0;
		RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B = 0;
		RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_CL = 0;
		RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_CL = 0;
		RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_CL = 0;
		RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_CL = 0;
		RCS_R_AFT_XFD_VLV_12_GPC_OP_A = 0;
		RCS_R_AFT_OX_XFD_V_12_GPC_OP_B = 0;
		RCS_R_AFT_FU_XFD_V_12_GPC_OP_B = 0;
		RCS_R_AFT_XFD_VLV_345_GPC_OP_A = 0;
		RCS_R_AFT_OX_XFD_V_345_GPC_OP_B = 0;
		RCS_R_AFT_FU_XFD_V_345_GPC_OP_B = 0;
		RCS_R_AFT_XFD_V_12_GPC_CL_A = 0;
		RCS_R_AFT_OX_XFD_V_12_GPC_CL_B = 0;
		RCS_R_AFT_FU_XFD_V_12_GPC_CL_B = 0;
		RCS_R_AFT_XFD_V_345_GPC_CL_A = 0;
		RCS_R_AFT_OX_XFD_V_345_GPC_CL_B = 0;
		RCS_R_AFT_FU_XFD_V_345_GPC_CL_B = 0;
		OMS_L_POD_XFD_VLVS_A_CMD_1_OP = 0;
		OMS_L_POD_XFD_VLVS_A_CMD_1_CL = 0;
		OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 0;
		OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 0;
		OMS_L_POD_XFD_VLVS_B_CMD_1_OP = 0;
		OMS_L_POD_XFD_VLVS_B_CMD_1_CL = 0;
		OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
		OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 0;
		OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP = 0;
		OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL = 0;
		OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;
		OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL = 0;
		OMS_R_POD_XFD_VLVS_A_CMD_1_OP = 0;
		OMS_R_POD_XFD_VLVS_A_CMD_1_CL = 0;
		OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP = 0;
		OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL = 0;
		OMS_R_POD_XFD_VLVS_B_CMD_1_OP = 0;
		OMS_R_POD_XFD_VLVS_B_CMD_1_CL = 0;
		OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP = 0;
		OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL = 0;
		OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP = 0;
		OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL = 0;
		OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP = 0;
		OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL = 0;

		POST_SEQ_CMD_TERM_FLAG = 0;
		return;
	}

	bool RCS_RCS_XFEED::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void RCS_RCS_XFEED::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool RCS_RCS_XFEED::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 601:
			case 602:
			case 603:
				return true;
		}
		return false;
	}
}
