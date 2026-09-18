/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/10/18   GLS
2021/01/20   GLS
2021/05/08   GLS
2021/06/18   GLS
2021/08/07   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/08/20   GLS
2022/08/25   GLS
2022/09/29   GLS
2022/10/12   GLS
2022/10/26   GLS
2022/12/16   indy91
2022/12/23   GLS
2024/12/29   GLS
2025/07/20   GLS
2026/09/18   GLS
********************************************/
#include "RSLS.h"
#include "../DGO_LDB_COORD.h"
#include "../../../Atlantis.h"
#include "../../MasterTimingUnit.h"


namespace dps
{
	RSLS::RSLS( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RSLS" )
	{
		T0UmbilicalReleased = false;
		EngStartCmdIssued = false;
		ShtdnEnableCmdsIssued = false;
		FlagA = false;
		CounterA = 0;
		Eng1StartCmdIssued = false;
		Eng2StartCmdIssued = false;
		Eng3StartCmdIssued = false;
		ME1PrevalvesCmddClosed = false;
		ME2PrevalvesCmddClosed = false;
		ME3PrevalvesCmddClosed = false;
		ENG_1_SHUTDOWN_TOGGLE_FLAG = false;
		ENG_2_SHUTDOWN_TOGGLE_FLAG = false;
		ENG_3_SHUTDOWN_TOGGLE_FLAG = false;

		ME1LOXPrevalveCloseDelayTimer = -1.0;
		ME2LOXPrevalveCloseDelayTimer = -1.0;
		ME3LOXPrevalveCloseDelayTimer = -1.0;
		ME1LH2PrevalveCloseDelayTimer = -1.0;
		ME2LH2PrevalveCloseDelayTimer = -1.0;
		ME3LH2PrevalveCloseDelayTimer = -1.0;

		EngStartTimer = -1.0;
		EngTimerThrustOK = -1.0;
		EngShutdownTimer = -1.0;
		AllEngShutdownTimer = -1.0;
		SRBIgnitionTimer = -1.0;

		FRFCutOffTimer = -1.0;
		FltCntlTVCInitTimer = -1.0;
		FRFThrottleTo92Timer = -1.0;
		FRFThrottleTo100Timer = -1.0;

		CountdownClockCounting = false;
		firstpass_step1c = true;
		firstpass_step5 = true;
		firstpass_step16a = true;
		firstpass_step19a = true;
		firstpass_step34 = true;
		firstpass_step41h = true;

		CountdownTime = -540.;
		LaunchSequenceAbort = false;
		EngineShutdownVerificationHold = false;
		MPSLOXAccRecircVlvHold = false;
		LPSGoForAutoSeqStartHold = false;
		LPSGoForEngineStartHold = false;
		RSSeqSSMEGoForLaunchHold = false;
		MPSE1LH2PrevlvOpenHold = false;
		MPSE2LH2PrevlvOpenHold = false;
		MPSE3LH2PrevlvOpenHold = false;
		MPSLO2OvbdBVCloseHold = false;
		RSCountdownHold = false;
		ME1PadDataPathFailHold = false;
		ME2PadDataPathFailHold = false;
		ME3PadDataPathFailHold = false;
		ME1ControlFailHold = false;
		ME2ControlFailHold = false;
		ME3ControlFailHold = false;
		VentDoorPositionHold = false;
		ME1LowChamberPressureAbort = false;
		ME2LowChamberPressureAbort = false;
		ME3LowChamberPressureAbort = false;
		UncommandedEngineShutdownAbort = false;
		FlightCriticalMDMHoldAbort = false;

		{// TODO fix IO
			discsignals::DiscreteBundle* bundle = BundleManager()->CreateBundle( "MPS_CLInd_A", 16 );
			PV19_CLInd[0].Connect( bundle, 8 );
			PV19_CLInd[1].Connect( bundle, 9 );

			bundle = BundleManager()->CreateBundle( "MPS_OPInd_A", 16 );
			PV4_OPInd[0].Connect( bundle, 3 );
			PV4_OPInd[1].Connect( bundle, 4 );
			PV5_OPInd[0].Connect( bundle, 5 );
			PV5_OPInd[1].Connect( bundle, 6 );
			PV6_OPInd[0].Connect( bundle, 7 );
			PV6_OPInd[1].Connect( bundle, 8 );

			PV20_OPInd.Connect( bundle, 15 );

			bundle = BundleManager()->CreateBundle( "MPS_OPInd_B", 16 );
			PV21_OPInd.Connect( bundle, 0 );
		}
	}

	RSLS::~RSLS()
	{
	}


	void RSLS::OnPostStep( double simT, double dT, double mjd )
	{
		/*
		Steps from JSC-16936.
		Changes from diagram:
			- updated I-LOAD times
			- added 0.5s to the ENG_TIMER_FOR_THRUST_OK I-LOAD, to allow for low frame rates
			- updated PIC Arm and Fire commands: added Fire 1 to SSME > 90%, and Fire 2 and Fire 3 commands to PIC fire instant
			- changed step1 to handle sim start
			- "nulled" steps 14 (GLS command/checks), retained goto step15
			- "nulled" steps 17a (GLS command/checks), added goto step18
			- "nulled" steps 18 (GLS command/checks), added goto step19
			- added SSME start timer init in step 28, as it isn't indicated where it is initiated
			- added SRB ignition timer init in step 28, as it isn't indicated where it is initiated
			- added LOX PV timer init in step 30, 31 and 32, as it isn't indicated where it is initiated
		*/

	//step1:
		/*if (1st)
		{
			RSCountdownHold = true;
			goto step9;
		}
		else*/ if (CountdownClockCounting) goto step1a;
		else goto step9;

	step1a:
		if (T0UmbilicalReleased)
		{
			// TODO terminate:
			// t0 umb release fire 1&2&3 flags
			// srm ign arm flag
			// t0 umb release arm
			WriteCOMPOOL_IS( SCP_M_RSET_USER, 1 );
			oapiWriteLog( "RSLS: MEC RESET" );
			CANCEL( "RSLS" );
			return;
		}
		else goto step1b;

	step1b:
		if (ReadCOMPOOL_IS( SCP_SRB_IGNITION_CMD ) == 1)
		{
			// TODO terminate:
			// srm ign fire 1&2&3 flags

			WriteCOMPOOL_IS( SCP_T0_UMB_FIRE1, 1 );
			WriteCOMPOOL_IS( SCP_T0_UMB_FIRE23, 1 );
			T0UmbilicalReleased = true;
			oapiWriteLog( "RSLS: T0 UMB FIRE" );
			return;
		}
		else goto step1c;

	step1c:
		if (LaunchSequenceAbort)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag

			if (firstpass_step1c)
			{
				firstpass_step1c = false;
				// TODO issue (one time only)
				// srb rss safe flag
				WriteCOMPOOL_IS( SCP_M_RSET_USER, 1 );
				oapiWriteLog( "RSLS: MEC RESET" );
			}
			goto step30;
		}
		else goto step1d;

	step1d:
		if (ENG_1_SHUTDOWN_TOGGLE_FLAG == true)// TODO fix
		{
			ENG_1_SHUTDOWN_TOGGLE_FLAG = false;
			WriteCOMPOOL_AIS( SCP_MESHDNCMD, 1, 1, 3 );
			LaunchSequenceAbort = true;
			goto step30;
		}
		else goto step1e;

	step1e:
		if (ENG_2_SHUTDOWN_TOGGLE_FLAG == true)// TODO fix
		{
			ENG_2_SHUTDOWN_TOGGLE_FLAG = false;
			WriteCOMPOOL_AIS( SCP_MESHDNCMD, 2, 1, 3 );
			LaunchSequenceAbort = true;
			goto step30;
		}
		else goto step1f;

	step1f:
		if (ENG_3_SHUTDOWN_TOGGLE_FLAG == true)// TODO fix
		{
			ENG_3_SHUTDOWN_TOGGLE_FLAG = false;
			WriteCOMPOOL_AIS( SCP_MESHDNCMD, 3, 1, 3 );
			LaunchSequenceAbort = true;
			goto step30;
		}
		else goto step2;

	step2:
		if (ReadCOMPOOL_AIS( SCP_ME_PAD_DATA_PATH_FAIL, 1, 3 ) == 1)
		{
			ME1PadDataPathFailHold = true;
			oapiWriteLog( "ME1PadDataPathFailHold" );
			goto step2d;
		}
		else goto step2a;

	step2a:
		if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_MAJOR_COMPONENT_FAIL, 1, 3 ) == 1))
		{
			ME1ControlFailHold = true;
			oapiWriteLog( "ME1ControlFailHold 2a" );
			goto step2d;
		}
		else goto step2c;

	step2c:
		if (ReadCOMPOOL_AIS( SCP_ME_CHANNEL_FAIL, 1, 3 ) == 1)
		{
			ME1ControlFailHold = true;
			oapiWriteLog( "ME1ControlFailHold 2c" );
			goto step2d;
		}
		else goto step3;

	step2d:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step3:
		if (ReadCOMPOOL_AIS( SCP_ME_PAD_DATA_PATH_FAIL, 2, 3 ) == 1)
		{
			ME2PadDataPathFailHold = true;
			oapiWriteLog( "ME2PadDataPathFailHold" );
			goto step3d;
		}
		else goto step3a;

	step3a:
		if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_MAJOR_COMPONENT_FAIL, 2, 3 ) == 1))
		{
			ME2ControlFailHold = true;
			oapiWriteLog( "ME2ControlFailHold 3a" );
			goto step3d;
		}
		else goto step3c;

	step3c:
		if (ReadCOMPOOL_AIS( SCP_ME_CHANNEL_FAIL, 2, 3 ) == 1)
		{
			ME2ControlFailHold = true;
			oapiWriteLog( "ME2ControlFailHold 3c" );
			goto step3d;
		}
		else goto step4;

	step3d:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 2, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step4:
		if (ReadCOMPOOL_AIS( SCP_ME_PAD_DATA_PATH_FAIL, 3, 3 ) == 1)
		{
			ME3PadDataPathFailHold = true;
			oapiWriteLog( "ME3PadDataPathFailHold" );
			goto step4d;
		}
		else goto step4a;

	step4a:
		if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 3, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 3, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_MAJOR_COMPONENT_FAIL, 3, 3 ) == 1))
		{
			ME3ControlFailHold = true;
			oapiWriteLog( "ME3ControlFailHold 4a" );
			goto step4d;
		}
		else goto step4c;

	step4c:
		if (ReadCOMPOOL_AIS( SCP_ME_CHANNEL_FAIL, 3, 3 ) == 1)
		{
			ME3ControlFailHold = true;
			oapiWriteLog( "ME3ControlFailHold 4c" );
			goto step4d;
		}
		else goto step5;

	step4d:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 3, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step5:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_SRB_IGN_ARM_T ))
		{
			if (firstpass_step5)
			{
				firstpass_step5 = false;

				WriteCOMPOOL_IS( SCP_SRM_IGN_ARM, 1 );
				oapiWriteLog( "RSLS: SRM IGNITION ARM" );
				WriteCOMPOOL_IS( SCP_T0_UMB_ARM, 1 );
				oapiWriteLog( "RSLS: T0 UMB ARM" );
			}
			goto step6;
		}
		else goto step9;

	step6:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_SRB_PIC_VOLTS_CHK_T ))
		{
			if (0)// TODO any srb ign pic volt low or comm fault
			{
				if (0)// TODO 1st pass flag false
				{
					if (0)// TODO lh srb ign pic cap a volt low or comm fault
					{
						// TODO issue lh srb ign pic cap a hold
					}
					else if (0)// TODO lh srb ign pic cap b volt low or comm fault
					{
						// TODO issue lh srb ign pic cap b hold
					}
					else if (0)// TODO rh srb ign pic cap a volt low or comm fault
					{
						// TODO issue rh srb ign pic cap a hold
					}
					else
					{
						// TODO issue rh srb ign pic cap b hold
					}
					goto step7;
				}
				else
				{
					// TODO set 1st pass flag false
					goto step6a;
				}
			}
			else
			{
				// TODO set 1st pass flag true
				goto step6a;
			}
		}
		else goto step9;

	step6a:
		if (((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000001) != 0) ||// FF1
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000002) != 0) ||// FF2
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000004) != 0) ||// FF3
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00000008) != 0) ||// FF4
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00001000) != 0) ||// FA1
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00002000) != 0) ||// FA2
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00004000) != 0) ||// FA3
			((ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) & 0x00008000) != 0))// FA4
		{
			FlightCriticalMDMHoldAbort = true;
			RSCountdownHold = true;
			oapiWriteLog( "FlightCriticalMDMHoldAbort" );
			SendtoLDB();
			goto step7;
		}
		else goto step8;

	step7:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// srm ign arm flag
			// to umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step8:
		if (EngStartCmdIssued)
		{
			if (Eng1StartCmdIssued) goto step29;
			else goto step28a;
		}
		else goto step9;

	step9:
		if ((ReadCOMPOOL_IS( SCP_LPS_COUNTDOWN_HOLD ) == 1) || RSCountdownHold)
		{
			if (CountdownTime >= ReadCOMPOOL_SS( SCP_AUTO_RECYCLE_T )) goto step11_true;
			else
			{
				CountdownClockCounting = false;
				goto step10;
			}
		}
		else goto step12;

	step10:
		if (ReadCOMPOOL_IS( SCP_RESUME_COUNT ) == 1)
		{
			// TODO clear all rs launch sequence downlist items
			EngineShutdownVerificationHold = false;
			MPSLOXAccRecircVlvHold = false;
			LPSGoForAutoSeqStartHold = false;
			LPSGoForEngineStartHold = false;
			RSSeqSSMEGoForLaunchHold = false;
			MPSE1LH2PrevlvOpenHold = false;
			MPSE2LH2PrevlvOpenHold = false;
			MPSE3LH2PrevlvOpenHold = false;
			MPSLO2OvbdBVCloseHold = false;
			ME1PadDataPathFailHold = false;
			ME2PadDataPathFailHold = false;
			ME3PadDataPathFailHold = false;
			ME1ControlFailHold = false;
			ME2ControlFailHold = false;
			ME3ControlFailHold = false;

			// TODO reset srb rss safe flag
			WriteCOMPOOL_IS( SCP_LPS_COUNTDOWN_HOLD, 0 );
			RSCountdownHold = false;
			WriteCOMPOOL_IS( SCP_RESUME_COUNT, 0 );
			goto step12;
		}
		else goto step11;

	step11:
		if (ReadCOMPOOL_IS( SCP_RECYCLE_COUNT ) == 1) goto step11_true;
		else return;

	step11_true:
		// TODO terminate:
		// srm ign arm flag
		// t0 umb release arm flag

		// TODO issue:
		// srb rss safe flag
		WriteCOMPOOL_IS( SCP_M_RSET_USER, 1 );

		CountdownTime = -540.0;
		CountdownClockCounting = false;
		// TODO re-init rsls
		return;

	step12:
		if (ReadCOMPOOL_IS( SCP_GMTLO_SET ) == 1)
		{
			// TODO read GMTLO (LPS currently writes it in var GMTLO)
			CountdownTime = (mjd - ReadCOMPOOL_SD( SCP_PRED_GMT_LO )) * 86400.0;
			WriteCOMPOOL_IS( SCP_GMTLO_SET, 0 );
			CountdownClockCounting = true;
		}
		else CountdownTime = (mjd - ReadCOMPOOL_SD( SCP_PRED_GMT_LO )) * 86400.0;
		goto step16b;

	step13:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_LPS_GO_FOR_AUTO_SEQ_T ))
		{
			if (ReadCOMPOOL_IS( SCP_RS_AUTO_SEQ_START ) == 1)
			{
				// TODO set indicator event 6 rs auto seq start
				WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
				goto step14;
			}
			else
			{
				LPSGoForAutoSeqStartHold = true;
				RSCountdownHold = true;
				oapiWriteLog( "LPSGoForAutoSeqStartHold" );
				return;
			}
		}
		else return;

	step14:
		/*if (CountdownTime >= OUTBD_FILL_VALVES_CLOSE_TIME)
		{
			// TODO issue:
			// mps lo2 otbd fill vlv cl cmd
			// mps lh2 otbd fill vlv cl cmd

			// TODO terminate:
			// mps lo2 outboard fill valve open cmd
			// mps lh2 outboard fill valve open cmd
		}*/
		goto step15;

	step15:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_IMU_TO_INERTIAL_T ))
		{
			// TODO issue cmd imu to inertial flag
		}
		goto step16;

	step16:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_OPN_LO2_POGO_RECRC_VLV_T ))
		{
			// open POGO vlvs
			WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x8000 );// 1 A
			WriteCOMPOOL_IS( SCP_FA3_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM12_CH0_DATA ) & ~0x8000 );// 1 B
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x8000 );// 2 A
			WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x8000 );// 2 B
		}
		goto step16a;

	step16a:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_NAV_INIT_T ))
		{
			if (firstpass_step16a)
			{
				firstpass_step16a = false;
				// TODO issue init nav flag
				WriteCOMPOOL_IS( SCP_K_CMD, 100 );
				oapiWriteLog( "RSLS: Initialize MEs throttle to 100%" );
			}
		}
		goto step17;

	step16b:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_CONFIG_VNT_DRS_FOR_LCH_T ))
		{
			WriteCOMPOOL_IS( SCP_CONF_VENT_DOORS, 1 );
		}
		goto step13;

	step17:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_CHK_MPS_VLVS_POS_T ))
		{
			if (FlagA) goto step20;
			else
			{
				if (0)// TODO any comm faults
				{
					CounterA++;
					if (CounterA < 2) return;
					else
					{
						RSCountdownHold = true;
						return;
					}
				}
				else goto step17a;
			}
		}
		else goto step20;

	step17a:
		/*if (0) goto step18;// TODO mps lh2 outboard fill vlv closed
		else if (0) goto step18;// TODO lps bypass of lh2 otbd vlv closed
		else
		{
			CounterA++;
			if (CounterA < 2) return;
			else
			{
				// TODO issue mps lh2 outboard fill vlv hold
				RSCountdownHold = true;
				return;
			}
		}*/
		goto step18;

	step18:
		/*if (0) goto step19;// TODO mps lox outboard fill vlv closed
		else if (0) goto step19;// TODO lps bypass of lo2 otbd vlv closed
		else
		{
			CounterA++;
			if (CounterA < 2) return;
			else
			{
				// TODO issue mps lo2 otbd fill vlv hold
				RSCountdownHold = true;
				return;
			}
		}*/
		goto step19;

	step19:
		if (PV20_OPInd.IsSet() && PV21_OPInd.IsSet()) goto step19a;
		else if (0) goto step19a;// TODO lps bypass of lo2 accum recirc vlv open
		else
		{
			CounterA++;
			if (CounterA < 2) return;
			else
			{
				MPSLOXAccRecircVlvHold = true;
				RSCountdownHold = true;
				oapiWriteLog( "MPSLOXAccRecircVlvHold" );
				return;
			}
		}

	step19a:
		if ((ReadCOMPOOL_AIS( SCP_ME_READY, 1, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_READY, 2, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_READY, 3, 3 ) == 1))
		{
			// set LH2 prevalves op
			WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) | 0x0040 );// C LH2 OP A
			WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) | 0x0040 );// C LH2 OP B
			WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) | 0x0040 );// C LH2 OP C
			WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) | 0x0040 );// L LH2 OP A
			WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) | 0x0040 );// L LH2 OP B
			WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) | 0x0040 );// L LH2 OP C
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0040 );// R LH2 OP A
			WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) | 0x0040 );// R LH2 OP B
			WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) | 0x0040 );// R LH2 OP C

			if (firstpass_step19a)
			{
				firstpass_step19a = false;
				WriteCOMPOOL_IS( SCP_MESTRTENA, 1 );
			}

			// reset LH2 prevalves cl
			WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0020 );// C LH2 CL A
			WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0020 );// C LH2 CL B
			WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0020 );// C LH2 CL C
			WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0020 );// L LH2 CL A
			WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0020 );// L LH2 CL B
			WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) & ~0x0020 );// L LH2 CL C
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0020 );// R LH2 CL A
			WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0020 );// R LH2 CL B
			WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0020 );// R LH2 CL C

			FlagA = true;
			goto step20;
		}
		else
		{
			RSSeqSSMEGoForLaunchHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "RSSeqSSMEGoForLaunchHold" );
			return;
		}

	step20:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_CLSE_LO2_OVBD_BV_T ))
		{
			// close LO2 overboard b/v
			WriteCOMPOOL_IS( SCP_FA3_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM12_CH0_DATA ) | 0x4000 );// A
			WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) | 0x4000 );// B
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x4000 );// C
		}
		goto step21;

	step21:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_CHK_PREVLVS_OPN_T ))
		{
			if (PV19_CLInd[0].IsSet() || PV19_CLInd[1].IsSet())
			{
				if (0)// TODO close ind comm fault
				{
					MPSLO2OvbdBVCloseHold = true;
					RSCountdownHold = true;
					oapiWriteLog( "MPSLO2OvbdBVCloseHold" );
					return;
				}
				else goto step22;
			}
			else
			{
				MPSLO2OvbdBVCloseHold = true;
				RSCountdownHold = true;
				oapiWriteLog( "MPSLO2OvbdBVCloseHold" );
				return;
			}
		}
		else return;

	step22:
		if (PV4_OPInd[0].IsSet() || PV4_OPInd[1].IsSet())
		{
			if (0)// TODO open ind comm fault
			{
				MPSE1LH2PrevlvOpenHold = true;
				RSCountdownHold = true;
				oapiWriteLog( "MPSE1LH2PrevlvOpenHold" );
				return;
			}
			else goto step23;
		}
		else
		{
			MPSE1LH2PrevlvOpenHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "MPSE1LH2PrevlvOpenHold" );
			return;
		}

	step23:
		if (PV5_OPInd[0].IsSet() || PV5_OPInd[1].IsSet())
		{
			if (0)// TODO open ind comm fault
			{
				MPSE2LH2PrevlvOpenHold = true;
				RSCountdownHold = true;
				oapiWriteLog( "MPSE2LH2PrevlvOpenHold" );
				return;
			}
			else goto step24;
		}
		else
		{
			MPSE2LH2PrevlvOpenHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "MPSE2LH2PrevlvOpenHold" );
			return;
		}

	step24:
		if (PV6_OPInd[0].IsSet() || PV6_OPInd[1].IsSet())
		{
			if (0) // TODO open ind comm fault
			{
				MPSE3LH2PrevlvOpenHold = true;
				RSCountdownHold = true;
				oapiWriteLog( "MPSE3LH2PrevlvOpenHold" );
				return;
			}
			else goto step25;
		}
		else
		{
			MPSE3LH2PrevlvOpenHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "MPSE3LH2PrevlvOpenHold" );
			return;
		}

	step25:
		{
			unsigned short stwd = ReadCOMPOOL_IS( SCP_ORBITER_VENT_DOORS_STATUS_WORD );
			if (stwd != 0x0FFF)
			{
				if (0) goto step26;// TODO lps override set for each fail flag
				else
				{
					VentDoorPositionHold = true;
					RSCountdownHold = true;
					oapiWriteLog( "VentDoorPositionHold" );
					return;
				}
			}
			else goto step26;
		}

	step26:
		if ((ReadCOMPOOL_AIS( SCP_ME_READY, 1, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_READY, 2, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_READY, 3, 3 ) == 1)) goto step27;
		else
		{
			RSSeqSSMEGoForLaunchHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "RSSeqSSMEGoForLaunchHold" );
			return;
		}

	step27:
		if (ReadCOMPOOL_IS( SCP_LPS_GO_FOR_ENGINE_START ) == 1) goto step28;
		else
		{
			LPSGoForEngineStartHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "LPSGoForEngineStartHold" );
			return;
		}

	step28:
		if (CountdownTime >= ReadCOMPOOL_SS( SCP_START_SSMES_T ))
		{
			// TODO issue:
			// mps tvc servo ovrd cmd
			EngStartCmdIssued = true;
			Eng3StartCmdIssued = true;
			WriteCOMPOOL_AIS( SCP_MESTRTCMD, 3, 1, 3 );
			oapiWriteLog( "RSLS: ME-3 Ignition Command" );

			EngStartTimer = simT;
			SRBIgnitionTimer = simT + ReadCOMPOOL_SS( SCP_SRB_IGN_TIME_DELAY );

			// start:
			FRFCutOffTimer = simT + ReadCOMPOOL_SS( SCP_FRF_CUTOFF_TIME_DELAY );
			FltCntlTVCInitTimer = simT + ReadCOMPOOL_SS( SCP_FLT_CNTL_TVC_INIT_TIME_DELAY );
			FRFThrottleTo92Timer = simT + ReadCOMPOOL_SS( SCP_FRF_THROTTLE_TO_92_TIME_DELAY );
			FRFThrottleTo100Timer = simT + ReadCOMPOOL_SS( SCP_FRF_THROTTLE_TO_100_TIME_DELAY );
			EngTimerThrustOK = simT + ReadCOMPOOL_SS( SCP_ENG_TIMER_FOR_THRUST_OK );
		}
		return;

	step28a:
		if ((simT - EngStartTimer) >= 0.12)
		{
			if (!Eng2StartCmdIssued)
			{
				WriteCOMPOOL_AIS( SCP_MESTRTCMD, 2, 1, 3 );
				Eng2StartCmdIssued = true;
				oapiWriteLog( "RSLS: ME-2 Ignition Command" );
			}

			if ((simT - EngStartTimer) >= 0.24)
			{
				if (!Eng1StartCmdIssued)
				{
					WriteCOMPOOL_AIS( SCP_MESTRTCMD, 1, 1, 3 );
					Eng1StartCmdIssued = true;
					oapiWriteLog( "RSLS: ME-1 Ignition Command" );
				}
			}
		}
		goto step29;

	step29:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MESHDN, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MESHDN, 3, 3 ) == 1) ||
			(ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 3, 3 ) == 1))
		{
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			UncommandedEngineShutdownAbort = true;
			LaunchSequenceAbort = true;
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			goto step30;
		}
		else goto step37;

	step30:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 1, 3 ) == 1))
		{
			if (ME1LOXPrevalveCloseDelayTimer == -1.0) ME1LOXPrevalveCloseDelayTimer = simT + ReadCOMPOOL_SS( SCP_ME1_LOX_PREVLV_CLSE_DELAY );

			if (simT >= ME1LOXPrevalveCloseDelayTimer) goto step30a;
			else goto step31;
		}
		else goto step31;

	step30a:
		// set engine 1 LO2 prevalves cl
		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) | 0x0080 );// C LO2 CL A
		WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) | 0x0080 );// C LO2 CL B
		WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) | 0x0080 );// C LO2 CL C
		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) | 0x0040 );// C LO2 CL D
		// reset engine 1 LO2 prevalves op
		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0100 );// C LO2 OP A
		WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0100 );// C LO2 OP B
		WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0100 );// C LO2 OP C
		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) & ~0x0080 );// C LO2 OP D

		if (ME1LH2PrevalveCloseDelayTimer == -1.0) ME1LH2PrevalveCloseDelayTimer = simT + ReadCOMPOOL_SD( SCP_ME1_LH2_PREVLV_CLSE_T_DELAY );

		if (simT >= ME1LH2PrevalveCloseDelayTimer)
		{
			// set engine 1 LH2 prevalves cl
			WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) | 0x0020 );// C LH2 CL A
			WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) | 0x0020 );// C LH2 CL B
			WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) | 0x0020 );// C LH2 CL C
			// reset engine 1 LH2 prevalves op
			WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0040 );// C LH2 OP A
			WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0040 );// C LH2 OP B
			WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0040 );// C LH2 OP C

			ME1PrevalvesCmddClosed = true;
		}
		goto step31;

	step31:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 2, 3 ) == 1))
		{
			if (ME2LOXPrevalveCloseDelayTimer == -1.0) ME2LOXPrevalveCloseDelayTimer = simT + ReadCOMPOOL_SS( SCP_ME2_LOX_PREVLV_CLSE_DELAY );

			if (simT >= ME2LOXPrevalveCloseDelayTimer) goto step31a;
			else goto step32;
		}
		else goto step32;

	step31a:
		// set engine 2 LO2 prevalves cl
		WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) | 0x0080 );// L LO2 CL A
		WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) | 0x0080 );// L LO2 CL B
		WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) | 0x0080 );// L LO2 CL C
		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) | 0x0008 );// L LO2 CL D
		// reset engine 2 LO2 prevalves op
		WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0100 );// L LO2 OP A
		WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0100 );// L LO2 OP B
		WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) & ~0x0100 );// L LO2 OP C
		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) & ~0x0010 );// L LO2 OP D

		if (ME2LH2PrevalveCloseDelayTimer == -1.0) ME2LH2PrevalveCloseDelayTimer = simT + ReadCOMPOOL_SD( SCP_ME2_LH2_PREVLV_CLSE_T_DELAY );

		if (simT >= ME2LH2PrevalveCloseDelayTimer)
		{
			// set engine 2 LH2 prevalves cl
			WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) | 0x0020 );// L LH2 CL A
			WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) | 0x0020 );// L LH2 CL B
			WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) | 0x0020 );// L LH2 CL C
			// reset engine 2 LH2 prevalves op
			WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0040 );// L LH2 OP A
			WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0040 );// L LH2 OP B
			WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) & ~0x0040 );// L LH2 OP C

			ME2PrevalvesCmddClosed = true;
		}
		goto step32;

	step32:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 3, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 3, 3 ) == 1))
		{
			if (ME3LOXPrevalveCloseDelayTimer == -1.0) ME3LOXPrevalveCloseDelayTimer = simT + ReadCOMPOOL_SS( SCP_ME3_LOX_PREVLV_CLSE_DELAY );

			if (simT >= ME3LOXPrevalveCloseDelayTimer) goto step32a;
			else goto step33;
		}
		else goto step33;

	step32a:
		// set engine 3 LO2 prevalves cl
		WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0080 );// R LO2 CL A
		WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) | 0x0080 );// R LO2 CL B
		WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) | 0x0080 );// R LO2 CL C
		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA ) | 0x0040 );// R LO2 CL D
		// reset engine 3 LO2 prevalves op
		WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0100 );// R LO2 OP A
		WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0100 );// R LO2 OP B
		WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0100 );// R LO2 OP C
		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA ) & ~0x0080 );// R LO2 OP D

		if (ME3LH2PrevalveCloseDelayTimer == -1.0) ME3LH2PrevalveCloseDelayTimer = simT + ReadCOMPOOL_SD( SCP_ME3_LH2_PREVLV_CLSE_T_DELAY );

		if (simT >= ME3LH2PrevalveCloseDelayTimer)
		{
			// set engine 3 LH2 prevalves cl
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0020 );// R LH2 CL A
			WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) | 0x0020 );// R LH2 CL B
			WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) | 0x0020 );// R LH2 CL C
			// reset engine 3 LH2 prevalves op
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0040 );// R LH2 OP A
			WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0040 );// R LH2 OP B
			WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0040 );// R LH2 OP C

			ME3PrevalvesCmddClosed = true;
		}
		goto step33;

	step33:
		if (LaunchSequenceAbort)
		{
			if (EngShutdownTimer == -1.0) EngShutdownTimer = simT;

			if ((simT - EngShutdownTimer) >= 1.8)
			{
				if (ShtdnEnableCmdsIssued)
				{
					ShtdnEnableCmdsIssued = false;
					WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 0, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNENA, 2, 0, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNENA, 3, 0, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNCMD, 1, 1, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNCMD, 2, 1, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNCMD, 3, 1, 3 );
				}
				else
				{
					ShtdnEnableCmdsIssued = true;
					WriteCOMPOOL_AIS( SCP_MESHDNCMD, 1, 0, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNCMD, 2, 0, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNCMD, 3, 0, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNENA, 2, 1, 3 );
					WriteCOMPOOL_AIS( SCP_MESHDNENA, 3, 1, 3 );
				}
				goto step34;
			}
			else return;
		}
		else return;

	step34:
		if (firstpass_step34)
		{
			firstpass_step34 = false;
			AllEngShutdownTimer = simT + ReadCOMPOOL_SS( SCP_VERIFY_ALL_ENG_SHTDN_TIMER );
			return;
		}
		else goto step35;

	step35:
		if (((ReadCOMPOOL_AIS( SCP_MESHDN, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 1, 3 ) == 1)) &&
			((ReadCOMPOOL_AIS( SCP_MESHDN, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 2, 3 ) == 1)) &&
			((ReadCOMPOOL_AIS( SCP_MESHDN, 3, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 3, 3 ) == 1))) goto step36;
		else if (simT >= AllEngShutdownTimer)
		{
			EngineShutdownVerificationHold = true;
			RSCountdownHold = true;
			oapiWriteLog( "EngineShutdownVerificationHold" );
			CANCEL( "RSLS" );
			return;
		}
		else return;

	step36:
		if (ME1PrevalvesCmddClosed && ME2PrevalvesCmddClosed && ME3PrevalvesCmddClosed)
		{
			CANCEL( "RSLS" );
			return;
		}
		else return;

	step37:
		if (ReadCOMPOOL_IS( SCP_LPS_COUNTDOWN_HOLD ) == 1)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}
		else goto step37a;

	step37a:
		if ((ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) > ReadCOMPOOL_SS( SCP_ALL_ENG_PERCENT_CHB_PRS_CHK )) && (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) > ReadCOMPOOL_SS( SCP_ALL_ENG_PERCENT_CHB_PRS_CHK )) && (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) > ReadCOMPOOL_SS( SCP_ALL_ENG_PERCENT_CHB_PRS_CHK )))
		{
			// TODO terminate mps tvc servo ovrd cmd

			WriteCOMPOOL_IS( SCP_PREP_SSMES, 1 );

			goto step37b;
		}
		else goto step38;

	step37b:
		if (0)// TODO any comm faults
		{
			if (0)// TODO comm fault first pass flag E true
			{
				// TODO set comm fault first pass flag E false
				goto step38;
			}
			else
			{
				// TODO terminate:
				// srm ign arm flag
				// t0 umb release arm flag
				WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

				// TODO issue:
				// mps tvc servo ovrd cmd
				WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
				WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
				WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
				return;
			}
		}
		else
		{
			// TODO set comm fault first pass flag E true
			goto step42;
		}

	step38:
		if (ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) > ReadCOMPOOL_SS( SCP_ENG_PERCENT_CHB_PRS_FOR_GO )) goto step39;
		else if (simT >= EngTimerThrustOK)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			ME1LowChamberPressureAbort = true;
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
		}
		return;

	step39:
		if (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) > ReadCOMPOOL_SS( SCP_ENG_PERCENT_CHB_PRS_FOR_GO )) goto step40;
		else if (simT >= EngTimerThrustOK)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			ME2LowChamberPressureAbort = true;
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 2, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
		}
		return;

	step40:
		if (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) > ReadCOMPOOL_SS( SCP_ENG_PERCENT_CHB_PRS_FOR_GO )) goto step41c;
		else if (simT >= EngTimerThrustOK)
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			ME3LowChamberPressureAbort = true;
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 3, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
		}
		return;

	step41:
		oapiWriteLogV( "RSLS: SRBIgnitionTimer=%lf", SRBIgnitionTimer - simT );
		if (simT >= SRBIgnitionTimer) goto step41a;
		else return;

	step41a:
		if (ReadCOMPOOL_IS( SCP_FRF_TEST_FLAG ) == 1)
		{
			if (simT >= FRFCutOffTimer)
			{
				oapiWriteLog( "RSLS: FRF Shutdown Command" );

				// TODO terminate:
				// srm ign arm flag
				// t0 umb release arm flag
				WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

				// TODO issue:
				WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
				WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
				WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
				return;
			}
			else goto step41f;
		}
		else goto step41b;

	step41b:
		// TODO issue:
		// mode control met reset cmd
		// mps tvc servo ovrd cmd

		// HACK terminate LPS polling
		{
			CANCEL( "DGI_LDB_IO" );
			WriteCOMPOOL_IS( SCP_CZ2B_DPS_STATUS, 0 );
			//ASB_GSE_ICC_MSG = 0
		}

		WriteCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA ) | 0x8000 );// start event timer
		WriteCOMPOOL_IS( SCP_SRM_IGN_FIRE1, 1 );
		WriteCOMPOOL_IS( SCP_SRM_IGN_FIRE23, 1 );
		WriteCOMPOOL_IS( SCP_SRB_IGNITION_CMD, 1 );
		oapiWriteLog( "RSLS: SRM IGNITION FIRE" );
		STS()->MTU()->StartMET();
		WriteCOMPOOL_IS(SCP_STORE_MET_REF, 1); //Cause time of liftoff to be stored in the GPC
		return;

	step41c:
		if (0) goto step41;// TODO fascos inh
		else if (0)// TODO me-1 fascos lim exceeded
		{
			if (0)// TODO counter1 < 3
			{
				// TODO set counter2 and counter3 to 0, and counter1++
				goto step41d;
			}
			else
			{
				// TODO terminate:
				// srm ign arm flag
				// t0 umb release arm flag
				WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

				// TODO issue:
				// mps tvc servo ovrd cmd
				WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
				WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
				WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
				return;
			}
		}
		else
		{
			// TODO set counter1 to 0
			goto step41d;
		}

	step41d:
		if (0)// TODO me-2 fascos lim exceeded
		{
			if (0)// TODO counter2 < 3
			{
				// TODO set counter1 and counter3 to 0, and counter2++
				goto step41e;
			}
			else
			{
				// TODO terminate:
				// srm ign arm flag
				// t0 umb release arm flag
				WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

				// TODO issue:
				// mps tvc servo ovrd cmd
				WriteCOMPOOL_AIS( SCP_MESHDNENA, 2, 1, 3 );
				WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
				WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
				return;
			}
		}
		else
		{
			// TODO set counter2 to 0
			goto step41e;
		}

	step41e:
		if (0)// TODO me-3 fascos lim exceeded
		{
			if (0)// TODO counter3 < 3
			{
				// TODO set counter1 and counter2 to 0, and counter3++
				goto step41;
			}
			else
			{
				// TODO terminate:
				// srm ign arm flag
				// t0 umb release arm flag
				WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

				// TODO issue:
				// mps tvc servo ovrd cmd
				WriteCOMPOOL_AIS( SCP_MESHDNENA, 3, 1, 3 );
				WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
				WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
				return;
			}
		}
		else
		{
			// TODO set counter3 to 0
			goto step41;
		}

	step41f:
		if (0)// TODO 1st pass
		{
			// TODO issue srm ign fire 1 & 2 flags
			return;
		}

		if (0)// TODO 1st pass
		{
			// TODO terminate srn ign fire 1 & 2 flags
			// TODO issue t0 umb release fire 1 & 2 flags
			return;
		}
		else goto step41g;

	step41g:
		if (simT >= FltCntlTVCInitTimer)
		{
			if (0)// TODO 1st pass
			{
				// TODO issue mps gimbal slew check indicator
				return;
			}
			else goto step41h;
		}
		else goto step41h;

	step41h:
		if (simT >= FRFThrottleTo92Timer)
		{
			if (firstpass_step41h)
			{
				firstpass_step41h = false;

				oapiWriteLog( "RSLS: FRF Throttle to 92% Command" );

				WriteCOMPOOL_IS( SCP_K_CMD, 92 );
				// TODO issue:
				// mps gimbal slew check indicator
				return;
			}
			else goto step41i;
		}
		else goto step41i;

	step41i:
		if (simT >= FRFThrottleTo100Timer)
		{
			WriteCOMPOOL_IS( SCP_K_CMD, 100 );
		}
		return;

	step42:
		if (1)// TODO me-1 actuator ports ok
		{
			// TODO set me-1 act port first pass flag X true
			goto step43;
		}
		else if (0)// TODO me-1 act port fail first pass flag X true
		{
			// TODO set me-1 act port fail first pass flag X false
			goto step43;
		}
		else
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 1, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}

	step43:
		if (1)// TODO me-2 actuator ports ok
		{
			// TODO set me-2 act port first pass flag X true
			goto step44;
		}
		else if (0)// TODO me-2 act port fail first pass flag X true
		{
			// TODO set me-2 act port fail first pass flag X false
			goto step44;
		}
		else
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 2, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}

	step44:
		if (1)// TODO me-3 actuator ports ok
		{
			// TODO set me-3 act port first pass flag X true
			goto step38;
		}
		else if (0)// TODO me-3 act port fail first pass flag X true
		{
			// TODO set me-3 act port fail first pass flag X false
			goto step38;
		}
		else
		{
			// TODO terminate:
			// srm ign arm flag
			// t0 umb release arm flag
			WriteCOMPOOL_IS( SCP_PREP_SSMES, 0 );

			// TODO issue:
			// mps tvc servo ovrd cmd
			WriteCOMPOOL_AIS( SCP_MESHDNENA, 3, 1, 3 );
			WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
			WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, 1 );
			return;
		}

		return;
	}

	void RSLS::SendtoLDB( void )
	{
		// HACK send data to LDB (should all be telemetry?)
		DGO_LDB_COORD* pDGO_LDB_COORD = dynamic_cast<DGO_LDB_COORD*>(GetCOMSUB( "DGO_LDB_COORD" ));


		WriteCOMPOOL_AIS( SCP_CVAV_RESPONSE_DATA, 1, RSCountdownHold, 7 );
		WriteCOMPOOL_AIS( SCP_CVAV_RESPONSE_DATA, 2, LaunchSequenceAbort, 7 );

		unsigned int tmp = 0;
		// add more here
		tmp = (tmp << 1) | (unsigned int)FlightCriticalMDMHoldAbort;
		tmp = (tmp << 1) | (unsigned int)VentDoorPositionHold;
		tmp = (tmp << 1) | (unsigned int)UncommandedEngineShutdownAbort;
		tmp = (tmp << 1) | (unsigned int)ME3LowChamberPressureAbort;
		tmp = (tmp << 1) | (unsigned int)ME2LowChamberPressureAbort;
		tmp = (tmp << 1) | (unsigned int)ME1LowChamberPressureAbort;
		tmp = (tmp << 1) | (unsigned int)ME3ControlFailHold;
		tmp = (tmp << 1) | (unsigned int)ME2ControlFailHold;
		tmp = (tmp << 1) | (unsigned int)ME1ControlFailHold;
		tmp = (tmp << 1) | (unsigned int)ME3PadDataPathFailHold;
		tmp = (tmp << 1) | (unsigned int)ME2PadDataPathFailHold;
		tmp = (tmp << 1) | (unsigned int)ME1PadDataPathFailHold;
		tmp = (tmp << 1) | (unsigned int)MPSLO2OvbdBVCloseHold;
		tmp = (tmp << 1) | (unsigned int)MPSE3LH2PrevlvOpenHold;
		tmp = (tmp << 1) | (unsigned int)MPSE2LH2PrevlvOpenHold;
		tmp = (tmp << 1) | (unsigned int)MPSE1LH2PrevlvOpenHold;
		tmp = (tmp << 1) | (unsigned int)RSSeqSSMEGoForLaunchHold;
		tmp = (tmp << 1) | (unsigned int)LPSGoForEngineStartHold;
		tmp = (tmp << 1) | (unsigned int)LPSGoForAutoSeqStartHold;
		tmp = (tmp << 1) | (unsigned int)MPSLOXAccRecircVlvHold;
		tmp = (tmp << 1) | (unsigned int)EngineShutdownVerificationHold;
		WriteCOMPOOL_AIS( SCP_CVAV_RESPONSE_DATA, 3, tmp >> 16, 7 );
		WriteCOMPOOL_AIS( SCP_CVAV_RESPONSE_DATA, 4, tmp & 0xFFFF, 7 );

		pDGO_LDB_COORD->Call( 3, 4 );
		return;
	}
}
