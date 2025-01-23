#include "ABT_CNTL_SEQ.h"


namespace dps
{
	// TODO I-Loads
	constexpr float ASSIST_OMS_DT = 123.0f;// TODO (V97U1248C) [s]
	constexpr unsigned short ATO_ICNCT_SEL = 1;// (V99U9993C) [1]
	constexpr float ATO_OMS_DT = 123.0f;// TODO (V97U9798C) [s]
	constexpr float CONTINGENCY_NZ_LIM = 123.0f;// TODO (V97U9837C) [g]
	constexpr float CONT_OMS_RCS_ICNCT_TERM_FU_TIME = 123.0f;// TODO (V99U9718C) [s]
	constexpr float ENTRY_OMS_FUEL_BURN_TIME = 123.0f;// TODO (V99U9571C) [s]
	constexpr float ICNCT_DELAY = 123.0f;// TODO (V99U9786C) [s]
	constexpr float MANUAL_OMS_DT = 123.0f;// TODO (V99U9717C) [s]
	constexpr float OMS_NZ_LIM = 123.0f;// TODO (V99U9697C) [g]
	constexpr float OMS_RCS_INTERCON_INIT_FU_TIME = 123.0f;// TODO (V99U9716C) [s]
	constexpr float OMS_RCS_INTERCON_TERM_FU_TIME = 123.0f;// TODO (V99U9952C) [s]
	constexpr float RCS_10_JET_FU_BIAS = 123.0f;// TODO (V99U9775C) [s]
	constexpr float RCS_10_JET_FU_SCALE = 123.0f;// TODO (V99U9776C) [1]
	constexpr float RCS_24_JET_FU_BIAS = 123.0f;// TODO (V99U9772C) [s]
	constexpr float RCS_24_JET_FU_SCALE = 123.0f;// TODO (V99U9773C) [1]
	constexpr unsigned short RTLS_ICNCT_SEL = 1;// (V99U9991C) [1]
	constexpr float RTLS_OMS_DT = 123.0f;// TODO (V97U9780C) [s]
	constexpr float SERC_INCNT_DEL = 123.0f;// TODO (V99U9787C) [s]
	constexpr float START_DUMP_VELOCITY = 123.0f;// TODO (V99U9573C) [fps]
	constexpr unsigned short TAL_ICNCT_SEL = 1;// (V99U9992C) [1]
	constexpr float TAL_OMS_DT = 123.0f;// TODO (V97U9786C) [s]
	constexpr float T_RCS_REF = 123.0f;// TODO (V97U9828C) [s]


	// K-Loads
	constexpr float CG_TRIM_DELAY = 4.5f;// (V97U9836C) [s]
	constexpr float IGN_PRESS_DELAY = 2.0f;// (V97U9838C) [s]


	ABT_CNTL_SEQ::ABT_CNTL_SEQ( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ABT_CNTL_SEQ" ),
		PRE_MECO_ICNCT_COMPLETE_FLAG(0), SERC_IC_DEL_TIMER(0.0), BURN_TIME_SEL_COMPLETE_FLAG(0), DUMP_CUTOFF_FLAG(0), ATO_ABORT_SELECTED(0), OMS_DELAY_TIMER(0.0), OMS_CUTOFF_DELAY(30.0),
		ICNCT_DELAY_TIMER(0.0), MM_602_DUMP_INIT_FLAG(0), CG_TRIM_DELAY_TIMER(0.0), OMS_NZ_DUMP_INHIBIT_FLAG(0), IGN_PRESS_DELAY_INIT_FLAG(0), IGN_PRESS_DELAY_TIMER(0.0), DUMP_ENA_INIT_FLAG(0),
		TWO_OME_DUMP_FLAG(0), RCS_4X_ON_TIME(0.0),
		firstpass_step1a_1(false), firstpass_step1a_2(false), firstpass_step1a_3(false), firstpass_step1b_1(false), firstpass_step1b_2(false), firstpass_step6a(false),
		firstpass_step10(false), firstpass_step12_1(false), firstpass_step12_2(false), firstpass_step12_3(false), firstpass_step13(false), firstpass_step14_1(false),
		firstpass_step14_2(false), firstpass_step16a(false), firstpass_step22(false), firstpass_step24_1(false), firstpass_step24_2(false), firstpass_step25_1(false),
		firstpass_step25_2(false),
		ena_SERC_IC_DEL_TIMER(false), ena_OMS_DELAY_TIMER(false), ena_ICNCT_DELAY_TIMER(false), ena_CG_TRIM_DELAY_TIMER(false), ena_IGN_PRESS_DELAY_TIMER(false), ena_RCS_4X_ON_TIME(false),
		nzcheck_step18_1(0), nzcheck_step18_2(0), mm602check_step23(0.0), nzcheck_step26(0.0), nzcheck_step28(0.0),
		step(0.08)
	{
		return;
	}

	ABT_CNTL_SEQ::~ABT_CNTL_SEQ( void )
	{
		return;
	}

	void ABT_CNTL_SEQ::OnPostStep( double simt, double simdt, double mjd )
	{
		// HACK run at 80ms
		step += simdt;
		if (step < 0.08) return;

		// handle timers
		if (ena_SERC_IC_DEL_TIMER) SERC_IC_DEL_TIMER += step;
		if (ena_OMS_DELAY_TIMER) OMS_DELAY_TIMER += step;
		if (ena_ICNCT_DELAY_TIMER) ICNCT_DELAY_TIMER += step;
		if (ena_CG_TRIM_DELAY_TIMER) CG_TRIM_DELAY_TIMER += step;
		if (ena_IGN_PRESS_DELAY_TIMER) IGN_PRESS_DELAY_TIMER += step;
		if (ena_RCS_4X_ON_TIME) RCS_4X_ON_TIME += step;


		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );

	// step1:
		WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, 1.0f );

		if (MM == 304)
		{
			goto step24;
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_SEC_ME_FL_CNFM ) == 1) || (ReadCOMPOOL_IS( SCP_CONT_SERC ) == 1) || (ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 1))
			{
				WriteCOMPOOL_IS( SCP_SERC_FLAG, 1 );
				goto step1a;
			}
			else
			{
				goto step1b;
			}
		}


	step1a:
		if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 1)
		{
			PRE_MECO_ICNCT_COMPLETE_FLAG = 1;

			if (firstpass_step1a_1)
			{
				firstpass_step1a_1 = false;

				OMS_L_POD_HE_ISLN_VLV_A_OP = 1;
				OMS_L_POD_VAPOR_ISLN_VLV_1_OP = 1;
				OMS_R_POD_HE_ISLN_VLV_A_OP = 1;
				OMS_R_POD_VAPOR_ISLN_VLV_1_OP = 1;
				OMS_L_POD_HE_ISLN_VLV_B_OP = 1;
				OMS_L_POD_VAPOR_ISLN_VLV_2_OP = 1;
				OMS_R_POD_HE_ISLN_VLV_B_OP = 1;
				OMS_R_POD_VAPOR_ISLN_VLV_2_OP = 1;
			}
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD ) == 1)
			{
				OMS_L_POD_HE_ISLN_VLV_A_OP = 1;
				OMS_L_POD_VAPOR_ISLN_VLV_1_OP = 1;
				OMS_R_POD_HE_ISLN_VLV_A_OP = 1;
				OMS_R_POD_VAPOR_ISLN_VLV_1_OP = 1;
				OMS_L_POD_HE_ISLN_VLV_B_OP = 1;
				OMS_L_POD_VAPOR_ISLN_VLV_2_OP = 1;
				OMS_R_POD_HE_ISLN_VLV_B_OP = 1;
				OMS_R_POD_VAPOR_ISLN_VLV_2_OP = 1;
			}

			if ((ReadCOMPOOL_IS( SCP_GUID_MECO_PREP_FLAG ) == 1) || (ReadCOMPOOL_IS( SCP_CONT_MECO_PREP_FLAG ) == 1))
			{
				PRE_MECO_ICNCT_COMPLETE_FLAG = 1;
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_CONT_2EO_MODE ) == 5)
				{
					if (firstpass_step1a_2)
					{
						firstpass_step1a_2 = false;

						ena_SERC_IC_DEL_TIMER = true;
					}
				}

				if ((ReadCOMPOOL_IS( SCP_CONT_2EO_MODE ) != 5) || (SERC_IC_DEL_TIMER >= SERC_INCNT_DEL))
				{
					if (firstpass_step1a_3)
					{
						firstpass_step1a_3 = false;

						WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
						WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
						WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 0 );

						WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 1 );
						WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 1 );
					}
				}
			}
		}

		goto step1b;


	step1b:
		if (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_ENA ) == 1)
		{
			if (firstpass_step1b_1)
			{
				firstpass_step1b_1 = false;

				BURN_TIME_SEL_COMPLETE_FLAG = 1;
				WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, MANUAL_OMS_DT );
				DUMP_CUTOFF_FLAG = 0;
			}
		}
		else
		{
			if (ATO_ABORT_SELECTED == 1)
			{
				if (ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 1)
				{
					if (firstpass_step1b_2)
					{
						firstpass_step1b_2 = false;

						WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, TAL_OMS_DT );
					}
				}
			}
		}

		goto step2;


	step2:
		if ((BURN_TIME_SEL_COMPLETE_FLAG == 1) || (PRE_MECO_ICNCT_COMPLETE_FLAG == 1))
		{
			goto step7;
		}
		else
		{
			goto step3;
		}


	step3:
		if (ReadCOMPOOL_IS( SCP_RTLS_ABORT_DECLARED ) == 1)
		{
			goto step4;
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 1)
			{
				goto step5;
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_S_ABORT_CONTROL ) == 1)
				{
					goto step6;
				}
				else
				{
					goto step6a;
				}
			}
		}


	step4:
		WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, RTLS_OMS_DT );
		BURN_TIME_SEL_COMPLETE_FLAG = 1;

		if ((RTLS_ICNCT_SEL == 1) || (ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 1))
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
		}

		goto terminatesequence;


	step5:
		WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, TAL_OMS_DT );
		BURN_TIME_SEL_COMPLETE_FLAG = 1;

		if ((TAL_ICNCT_SEL == 1) || (ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 1))
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
		}

		goto terminatesequence;


	step6:
		WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, (ReadCOMPOOL_SS( SCP_K2 ) * ATO_OMS_DT) + ASSIST_OMS_DT );
		BURN_TIME_SEL_COMPLETE_FLAG = 1;
		ATO_ABORT_SELECTED = 1;

		if ((ATO_ICNCT_SEL == 1) || (ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 1))
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 1 );
		}
		else
		{
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
		}

		goto terminatesequence;


	step6a:
		if (ReadCOMPOOL_IS( SCP_AS29A ) == 1)
		{
			if (firstpass_step6a)
			{
				firstpass_step6a = false;

				WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, ASSIST_OMS_DT );

				if (ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 0)
				{
					WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
				}
			}

			goto step7;
		}

		goto terminatesequence;


	step7:
		if ((ReadCOMPOOL_IS( SCP_GUID_MECO_PREP_FLAG ) == 0) && (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0))
		{
			goto step8;
		}
		else
		{
			goto step12;
		}


	step8:
		if ((ReadCOMPOOL_IS( SCP_ORBITER_DUMP_INH ) == 0) && (ReadCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED ) > ReadCOMPOOL_SS( SCP_T1 )))
		{
			goto step9;
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) || (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1))
			{
				WriteCOMPOOL_IS( SCP_S_OMS_IGN, 0 );
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
				WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
				WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 0 );

				WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 1 );

				DUMP_CUTOFF_FLAG = 1;

				ena_OMS_DELAY_TIMER = true;
			}

			if (ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 0)
			{
				if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1)
				{
					WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
					WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );

					WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
				}
			}
		}

		goto terminatesequence;


	step9:
		if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) || (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1))
		{
			WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + step/*0.08*/) );
		}
		else
		{
			if ((DUMP_CUTOFF_FLAG == 0) || (OMS_DELAY_TIMER >= OMS_CUTOFF_DELAY))
			{
				WriteCOMPOOL_IS( SCP_S_OMS_IGN, 1 );

				WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 0 );
				DUMP_CUTOFF_FLAG = 0;

				ena_OMS_DELAY_TIMER = false;
				OMS_DELAY_TIMER = 0.0;
			}
		}

		if (((ReadCOMPOOL_IS( SCP_SERC_FLAG ) == 0) && (DUMP_CUTOFF_FLAG == 0)) || (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_ENA ) == 1))
		{
			if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 1)
			{
				goto step10;
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1)
				{
					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
					WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
					WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );

					WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
				}
			}
		}

		goto terminatesequence;


	step10:
		if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 1 );

			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 0 );
		}
		else
		{
			if (firstpass_step10)
			{
				firstpass_step10 = false;

				ena_ICNCT_DELAY_TIMER = true;
			}
			else
			{
				if (ICNCT_DELAY_TIMER >= ICNCT_DELAY)
				{
					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );
					WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 1 );

					goto step11;
				}
			}
			
		}

		goto terminatesequence;


	step11:
		if ((ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG ) == 0) && (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG ) == 0))
		{
			WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + (step * (RCS_24_JET_FU_BIAS / 0.08))/*RCS_24_JET_FU_BIAS*/) );
			WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, RCS_24_JET_FU_SCALE );
		}
		else
		{
			WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + (step * (RCS_10_JET_FU_BIAS / 0.08))/*RCS_10_JET_FU_BIAS*/) );
			WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, RCS_10_JET_FU_SCALE );
		}

		goto terminatesequence;


	step12:
		if (MM == 102)
		{
			if (firstpass_step12_1)
			{
				firstpass_step12_1 = false;

				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 0 );
				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 1 );
				WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 1 );
			}

			goto step13;
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_ARM_CONT_MPS_SETTLING_BURN ) == 1)
			{
				if (ReadCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED ) > ReadCOMPOOL_SS( SCP_T1 ))
				{
					if (firstpass_step12_2)
					{
						firstpass_step12_2 = false;

						WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
						WriteCOMPOOL_IS( SCP_MODE_2_INDICATOR, 1 );

						WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
						WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
						WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
						WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
					}
				}

				if (ReadCOMPOOL_IS( SCP_SETTLING_BURN_ENA ) == 1)
				{
					goto step9;
				}
				else
				{
					goto terminatesequence;
				}
			}
			else
			{
				if (firstpass_step12_3)
				{
					firstpass_step12_3 = false;

					WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 1 );
					WriteCOMPOOL_IS( SCP_S_OMS_IGN, 0 );
					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
					WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
				}

				goto step14;
			}
		}


	step13:
		if (ReadCOMPOOL_IS( SCP_FAST_SEP_FLAG ) == 1)
		{
			if (firstpass_step13)
			{
				firstpass_step13 = false;

				WriteCOMPOOL_IS( SCP_MODE_2_INDICATOR, 1 );
			}

			goto step20;
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_ORBITER_DUMP_INH ) == 1) || (ReadCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED ) <= ReadCOMPOOL_SS( SCP_T1 )))
			{
				goto step20;
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_ENA ) == 1)
				{
					goto step17;
				}
				else
				{
					goto terminatesequence;
				}
			}
		}


	step14:
		if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 1)
		{
			if (firstpass_step14_1)
			{
				firstpass_step14_1 = false;

				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
				WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 0 );
				WriteCOMPOOL_IS( SCP_ORBITER_DUMP_INH, 0 );
				WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );

				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
				WriteCOMPOOL_IS( SCP_MODE_2_INDICATOR, 1 );
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 0)
				{
					if (firstpass_step14_2)
					{
						firstpass_step14_2 = false;

						OMS_L_POD_HE_ISLN_VLV_A_OP = 0;
						OMS_L_POD_VAPOR_ISLN_VLV_1_OP = 0;
						OMS_R_POD_HE_ISLN_VLV_A_OP = 0;
						OMS_R_POD_VAPOR_ISLN_VLV_1_OP = 0;
						OMS_L_POD_HE_ISLN_VLV_B_OP = 0;
						OMS_L_POD_VAPOR_ISLN_VLV_2_OP = 0;
						OMS_R_POD_HE_ISLN_VLV_B_OP = 0;
						OMS_R_POD_VAPOR_ISLN_VLV_2_OP = 0;
						WriteCOMPOOL_IS( SCP_MODE_2_INDICATOR, 0 );
					}
				}
			}

			goto step15;
		}

		goto terminatesequence;


	step15:
		if (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_ENA ) == 1)
		{
			if (ReadCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED ) > ReadCOMPOOL_SS( SCP_T1 ))
			{
				goto step16;
			}
			else
			{
				goto step20;
			}
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_INH ) == 1)
			{
				goto step20;
			}
			else
			{
				goto step23;
			}
		}


	step16:
		if (MM_602_DUMP_INIT_FLAG == 1)
		{
			goto step16a;
		}
		else
		{
			if ((MM == 602) || (ReadCOMPOOL_IS( SCP_CONT_3EO_START ) == 1))
			{
				if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) <= OMS_NZ_LIM)
				{
					WriteCOMPOOL_IS( SCP_CG_TRIM, 1 );

					MM_602_DUMP_INIT_FLAG = 1;

					ena_CG_TRIM_DELAY_TIMER = true;

					if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 1)
					{
						if (ReadCOMPOOL_IS( SCP_FCS_ACCEPT_ICNCT ) == 1)
						{
							WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 1 );

							WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 0 );
							WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
						}
						else
						{
							WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );

							WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
						}
					}
					else
					{
						WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );
					}
				}
				else
				{
					WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 0 );
					WriteCOMPOOL_IS( SCP_ORBITER_DUMP_INH, 1 );
				}
			}

			goto terminatesequence;
		}


	step16a:
		if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 1)
		{
			if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1)
			{
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );
			}
			else
			{
				goto terminatesequence;
			}
		}
		else
		{
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );
		}

		if (CG_TRIM_DELAY <= CG_TRIM_DELAY_TIMER)
		{
			if (firstpass_step16a)
			{
				firstpass_step16a = false;

				if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) <= OMS_NZ_LIM)
				{
					goto step17;
				}
				else
				{
					OMS_NZ_DUMP_INHIBIT_FLAG = 1;

					goto step18;
				}
			}
			else
			{
				goto step17;
			}
		}

		goto terminatesequence;


	step17:
		if (IGN_PRESS_DELAY_INIT_FLAG == 0)
		{
			IGN_PRESS_DELAY_TIMER = 0.0;
			IGN_PRESS_DELAY_INIT_FLAG = 1;
		}

		if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) || (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1))
		{
			WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + step/*0.08*/) );

			if ((IGN_PRESS_DELAY <= IGN_PRESS_DELAY_TIMER) || (ReadCOMPOOL_IS( SCP_S_RCS_NULL20 ) == 1))
			{
				if (MM == 102)
				{
					goto step19;
				}
				else
				{
					goto step18;
				}
			}
		}
		else
		{
			WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 0 );

			WriteCOMPOOL_IS( SCP_S_OMS_IGN, 1 );
		}

		goto terminatesequence;


	step18:
		// HACK count consecutive time with "|NZ| > OMS_NZ_LIM"... not perfect
		if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) > ReadCOMPOOL_IS( SCP_OMS_NZ_LIM )) nzcheck_step18_1 += 1;
		else nzcheck_step18_1 = 0;

		// HACK count consecutive time with "|NZ| > CONTINGENCY_NZ_LIM"... not perfect
		if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) > CONTINGENCY_NZ_LIM) nzcheck_step18_2 += 1;
		else nzcheck_step18_2 = 0;
		
		if ((nzcheck_step18_1 >= 3) || (OMS_NZ_DUMP_INHIBIT_FLAG == 1))
		{
			WriteCOMPOOL_IS( SCP_S_OMS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
			WriteCOMPOOL_IS( SCP_CG_TRIM, 0 );
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
			WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 0 );

			WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 1 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
			WriteCOMPOOL_IS( SCP_ORBITER_DUMP_INH, 1 );
			WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );

			MM_602_DUMP_INIT_FLAG = 0;
			IGN_PRESS_DELAY_INIT_FLAG = 0;

			ena_IGN_PRESS_DELAY_TIMER = false;
			IGN_PRESS_DELAY_TIMER = 0.0;
			ena_CG_TRIM_DELAY_TIMER = false;
			CG_TRIM_DELAY_TIMER = 0.0;

			goto step22;
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_OME_ONLY_FLAG ) == 1) || (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 0) || (nzcheck_step18_2 >= 3) || (ReadCOMPOOL_SS( SCP_T1 ) >= CONT_OMS_RCS_ICNCT_TERM_FU_TIME))
			{
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
				WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
				WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );

				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
				WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );

				goto step22;
			}
			else
			{
				goto step19;
			}
		}


	step19:
		if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1)
		{
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );
			WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 1 );

			if ((ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG ) == 0) && (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG ) == 0))
			{
				WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + (step * (RCS_24_JET_FU_BIAS / 0.08))/*RCS_24_JET_FU_BIAS*/) );
				WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, RCS_24_JET_FU_SCALE );
			}
			else
			{
				WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + (step * (RCS_10_JET_FU_BIAS / 0.08))/*RCS_10_JET_FU_BIAS*/) );
				WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, RCS_10_JET_FU_SCALE );
			}
		}

		goto terminatesequence;


	step20:
		if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) || (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1))
		{
			WriteCOMPOOL_IS( SCP_CG_TRIM, 0 );
			WriteCOMPOOL_IS( SCP_S_OMS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
			WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 0 );
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
			MM_602_DUMP_INIT_FLAG = 0;
			IGN_PRESS_DELAY_INIT_FLAG = 0;

			WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 1 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
			WriteCOMPOOL_IS( SCP_ORBITER_DUMP_INH, 1 );

			ena_IGN_PRESS_DELAY_TIMER = false;
			IGN_PRESS_DELAY_TIMER = 0.0;
			ena_CG_TRIM_DELAY_TIMER = false;
			CG_TRIM_DELAY_TIMER = 0.0;
		}

		goto step21;


	step21:
		if (ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR ) > 0)
		{
			goto step23;
		}
		else
		{
			if ((MM == 602) || (MM == 603))
			{
				if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) > CONTINGENCY_NZ_LIM)
				{
					goto step22;
				}
			}
		}

		goto terminatesequence;


	step22:
		if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 0)
		{
			if (firstpass_step22)
			{
				firstpass_step22 = false;

				WriteCOMPOOL_SS( SCP_AFT_RCS_DUMP_DURATION, T_RCS_REF );
			}

			goto step23;
		}

		goto terminatesequence;


	step23:
		// HACK count time in MM602... not perfect
		if (MM == 602) mm602check_step23 += step;

		if ((mm602check_step23 >= 20.0) || (MM == 603))
		{
			if (ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_DURATION ) <= ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR ))
			{
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
				WriteCOMPOOL_IS( SCP_AFT_RCS_DUMP_ENABLE, 0 );
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_AFT_RCS_DUMP_ENABLE ) == 1)
				{
					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );

					WriteCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR, static_cast<float>(ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR ) + step/*0.08*/) );
				}
				else
				{
					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
				}
			}
		}

		goto terminatesequence;


	step24:
		if (START_DUMP_VELOCITY >= ReadCOMPOOL_SS( SCP_VE )/*TODO ReadCOMPOOL_SS( SCP_REL_VEL_MAG )*/)
		{
			goto step29;
		}
		else
		{
			if (firstpass_step24_1)
			{
				firstpass_step24_1 = false;

				WriteCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED, ENTRY_OMS_FUEL_BURN_TIME );

				if (OMS_RCS_INTERCON_INIT_FU_TIME > ReadCOMPOOL_SS( SCP_T1 ))
				{
					WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 1 );
				}
			}

			if ((ReadCOMPOOL_IS( SCP_FCS_ACCEPT_ICNCT ) == 1) && (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_INH ) == 0))
			{
				if (firstpass_step24_2)
				{
					firstpass_step24_2 = false;

					WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 1 );
				}
			}

			if (ReadCOMPOOL_IS( SCP_ORBITER_DUMP_ENA ) == 0)
			{
				goto step28;
			}

			if (DUMP_ENA_INIT_FLAG == 0)
			{
				WriteCOMPOOL_IS( SCP_CG_TRIM, 1 );
				OMS_L_POD_HE_ISLN_VLV_A_OP = 1;
				OMS_L_POD_VAPOR_ISLN_VLV_1_OP = 1;
				OMS_R_POD_HE_ISLN_VLV_A_OP = 1;
				OMS_R_POD_VAPOR_ISLN_VLV_1_OP = 1;
				OMS_L_POD_HE_ISLN_VLV_B_OP = 1;
				OMS_L_POD_VAPOR_ISLN_VLV_2_OP = 1;
				OMS_R_POD_HE_ISLN_VLV_B_OP = 1;
				OMS_R_POD_VAPOR_ISLN_VLV_2_OP = 1;
				DUMP_ENA_INIT_FLAG = 1;
			}
			else
			{
				goto step25;
			}

			if ((ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 1) && (ReadCOMPOOL_IS( SCP_FCS_ACCEPT_ICNCT ) == 1))
			{
				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 1 );

				WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 0 );

				ena_CG_TRIM_DELAY_TIMER = true;
			}
			else
			{
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );
				WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );

				TWO_OME_DUMP_FLAG = 1;

				WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );

				ena_RCS_4X_ON_TIME = true;
			}
			goto step28;
		}


	step25:
		if (TWO_OME_DUMP_FLAG == 0)
		{
			goto step26;
		}
		else
		{
			if (RCS_4X_ON_TIME >= 10)
			{
				if (firstpass_step25_1)
				{
					firstpass_step25_1 = false;

					WriteCOMPOOL_IS( SCP_S_OMS_IGN, 1 );

					WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 0 );
				}
			}

			if (RCS_4X_ON_TIME >= 20)
			{
				if (firstpass_step25_2)
				{
					firstpass_step25_2 = false;

					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
				}
			}

			goto step28;
		}


	step26:
		// HACK count consecutive time with "|NZ| > CONTINGENCY_NZ_LIM"... not perfect
		if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) > CONTINGENCY_NZ_LIM) nzcheck_step26 += step;
		else nzcheck_step26 = 0.0;

		if ((ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 0) || (nzcheck_step26 > 1.0) || (ReadCOMPOOL_SS( SCP_T1 ) >= OMS_RCS_INTERCON_TERM_FU_TIME))
		{
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );

			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );
			WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );

			goto step27;
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG ) == 1)
			{
				goto step27;
			}
			else
			{
				goto step28;
			}
		}


	step27:
		if (CG_TRIM_DELAY <= CG_TRIM_DELAY_TIMER)
		{
			if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 0) && (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 0))
			{
				WriteCOMPOOL_IS( SCP_S_OMS_IGN, 1 );
				
				WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 0 );

				ena_IGN_PRESS_DELAY_TIMER = true;
			}

			if (ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD ) == 1)
			{
				if (IGN_PRESS_DELAY <= IGN_PRESS_DELAY_TIMER)
				{
					WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );
					WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 1 );

					if ((ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG ) == 1) || (ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG ) == 1))
					{
						WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + (step * (RCS_10_JET_FU_BIAS / 0.08))/*RCS_10_JET_FU_BIAS*/) );
						WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, RCS_10_JET_FU_SCALE );
					}
					else
					{
						WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + (step * (RCS_24_JET_FU_BIAS / 0.08))/*RCS_24_JET_FU_BIAS*/) );
						WriteCOMPOOL_SS( SCP_OMS_TIME_SCALE_FACTOR, RCS_24_JET_FU_SCALE );
					}
				}
			}
		}

		goto step28;


	step28:
		// HACK count consecutive time with "|NZ| > OMS_NZ_LIM"... not perfect
		if (fabs( ReadCOMPOOL_SS( SCP_NZ ) ) > OMS_NZ_LIM) nzcheck_step28 += step;
		else nzcheck_step28 = 0.0;

		if ((ReadCOMPOOL_IS( SCP_ORBITER_DUMP_INH ) == 1) || (ReadCOMPOOL_SS( SCP_T1 ) >= ReadCOMPOOL_SS( SCP_OMS_DELTA_T_COMPUTED )) || (nzcheck_step28 > 1.0))
		{
			WriteCOMPOOL_IS( SCP_CG_TRIM, 0 );
			WriteCOMPOOL_IS( SCP_S_OMS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
			WriteCOMPOOL_IS( SCP_S_RCS_NULL20, 0 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_INTERCONNECT_CMD, 0 );
			OMS_L_POD_HE_ISLN_VLV_A_OP = 0;
			OMS_L_POD_VAPOR_ISLN_VLV_1_OP = 0;
			OMS_R_POD_HE_ISLN_VLV_A_OP = 0;
			OMS_R_POD_VAPOR_ISLN_VLV_1_OP = 0;
			OMS_L_POD_HE_ISLN_VLV_B_OP = 0;
			OMS_L_POD_VAPOR_ISLN_VLV_2_OP = 0;
			OMS_R_POD_HE_ISLN_VLV_B_OP = 0;
			OMS_R_POD_VAPOR_ISLN_VLV_2_OP = 0;
			WriteCOMPOOL_IS( SCP_ORBITER_DUMP_ENA, 0 );
			DUMP_ENA_INIT_FLAG = 0;
			WriteCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_INHENA_CMD, 0 );

			WriteCOMPOOL_IS( SCP_S_OMS_CUTOFF, 1 );
			WriteCOMPOOL_IS( SCP_OMS_TO_RCS_RTRN_TO_NORM_CONFIG_CMD, 1 );
			WriteCOMPOOL_IS( SCP_ORBITER_DUMP_INH, 1 );
			WriteCOMPOOL_IS( SCP_OME_ONLY_FLAG, 1 );

			ena_IGN_PRESS_DELAY_TIMER = false;
			IGN_PRESS_DELAY_TIMER = 0.0;
			ena_RCS_4X_ON_TIME = false;
			RCS_4X_ON_TIME = 0.0;
			ena_CG_TRIM_DELAY_TIMER = false;
			CG_TRIM_DELAY_TIMER = 0.0;
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_OMS_L_ON_CMD_IND ) == 1) || (ReadCOMPOOL_IS( SCP_OMS_R_ON_CMD_IND ) == 1))
			{
				WriteCOMPOOL_SS( SCP_T1, static_cast<float>(ReadCOMPOOL_SS( SCP_T1 ) + step/*0.08*/) );
			}
		}

		goto terminatesequence;


	step29:
		if (ReadCOMPOOL_IS( SCP_AFT_RCS_DUMP_ENABLE ) == 1)
		{
			if (ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_DURATION ) > ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR ))
			{
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 1 );

				WriteCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR, static_cast<float>(ReadCOMPOOL_SS( SCP_AFT_RCS_DUMP_CNTR ) + (ReadCOMPOOL_SS( SCP_AFT_RCS_TTG_SF ) * step/*0.08*/)) );
			}
			else
			{
				WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
				WriteCOMPOOL_IS( SCP_AFT_RCS_DUMP_ENABLE, 0 );
			}
		}
		else
		{
			WriteCOMPOOL_IS( SCP_S_RCS_IGN, 0 );
		}

		goto terminatesequence;


	terminatesequence:

		// output
		unsigned short FA1_IOM7_CH1 = 0;
		unsigned short FA1_IOM15_CH1 = 0;
		unsigned short FA2_IOM7_CH1 = 0;
		unsigned short FA2_IOM15_CH1 = 0;
		unsigned short FA3_IOM7_CH1 = 0;
		unsigned short FA3_IOM15_CH1 = 0;
		unsigned short FA4_IOM7_CH1 = 0;
		unsigned short FA4_IOM15_CH1 = 0;

		FA1_IOM15_CH1 |= (OMS_L_POD_HE_ISLN_VLV_A_OP & 0b1) << 2;
		FA2_IOM15_CH1 |= (OMS_L_POD_HE_ISLN_VLV_B_OP & 0b1) << 2;
		FA1_IOM7_CH1 |= (OMS_L_POD_VAPOR_ISLN_VLV_1_OP & 0b1) << 2;
		FA2_IOM7_CH1 |= (OMS_L_POD_VAPOR_ISLN_VLV_2_OP & 0b1) << 2;
		FA3_IOM15_CH1 |= (OMS_R_POD_HE_ISLN_VLV_A_OP & 0b1) << 2;
		FA4_IOM15_CH1 |= (OMS_R_POD_HE_ISLN_VLV_B_OP & 0b1) << 2;
		FA3_IOM7_CH1 |= (OMS_R_POD_VAPOR_ISLN_VLV_1_OP & 0b1) << 2;
		FA4_IOM7_CH1 |= (OMS_R_POD_VAPOR_ISLN_VLV_2_OP & 0b1) << 2;

		unsigned short tmp = ReadCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA1_IOM7_CH1_DATA, tmp | FA1_IOM7_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA1_IOM15_CH1_DATA, tmp | FA1_IOM15_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA2_IOM7_CH1_DATA, tmp | FA2_IOM7_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA2_IOM15_CH1_DATA, tmp | FA2_IOM15_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, tmp | FA3_IOM7_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA3_IOM15_CH1_DATA, tmp | FA3_IOM15_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, tmp | FA4_IOM7_CH1 );

		tmp = ReadCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA );
		WriteCOMPOOL_IS( SCP_FA4_IOM15_CH1_DATA, tmp | FA4_IOM15_CH1 );


		// reset
		step = 0.0;
		return;
	}

	bool ABT_CNTL_SEQ::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ABT_CNTL_SEQ::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool ABT_CNTL_SEQ::OnMajorModeChange( unsigned int newMajorMode )
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
