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
2022/12/23   GLS
********************************************/
#include "RSLS.h"
#include "../../../Atlantis.h"
#include "SSME_SOP.h"
#include "IO_Control.h"
#include "MPS_ATVC_CMD_SOP.h"
#include "MEC_SOP.h"
#include "../../MasterTimingUnit.h"
#include <cassert>


namespace dps
{
	RSLS::RSLS( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RSLS" )
	{
		Active = false;

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
		firstpass_step16a = true;
		firstpass_step19a = true;
		firstpass_step34 = true;
		firstpass_step41h = true;

		SRBIgnitionCommand = false;
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
		GMTLO = -1.0;
		LPSGoForAutoSequenceStart = false;
		LPSGoForEngineStart = false;
		GMTLOSetCommand = false;
		ResumeCountCommand = false;
		LPSCountdownHold = false;
		RecycleCountCmd = false;

		// I-LOADs init
		LPS_GO_FOR_AUTO_SEQ_T = -27.0;// TODO confirm
		SRB_IGN_ARM_T = -18.0;
		SRB_PIC_VOLTS_CHK_T = -15.0;
		IMU_TO_INERTIAL_T = -15.0;
		AUTO_RECYCLE_T = -23.0;
		OPN_LO2_ACC_RECIRC_VLV_T = -12.5;
		NAV_INIT_T = -11.0;
		CONFIG_VNT_DRS_FOR_LCH_T = -27.92;
		CHK_MPS_VLVS_POS_T = -9.5;
		CLSE_LO2_OVBD_BV_T = -9.4;
		CHK_PREVLVS_OPN_T = -7.0;
		START_SSMES_T = -6.6;
		ALL_ENG_PERCENT_CHB_PRS_CHK = 90;
		ENG_PERCENT_CHB_PRS_FOR_GO = 90;
		ENG_TIMER_FOR_THRUST_OK = 4.6;// 5.5 for low fps
		VERIFY_ALL_ENG_SHTDN_TIMER = 8.0;
		ME1_LOX_PREVLV_CLSE_DELAY = 4.5;
		ME2_LOX_PREVLV_CLSE_DELAY = 4.5;
		ME3_LOX_PREVLV_CLSE_DELAY = 4.5;
		SRB_IGN_TIME_DELAY = 6.6;
		ME1_LH2_PREVLV_CLSE_T_DELAY = 0.8;
		ME2_LH2_PREVLV_CLSE_T_DELAY = 0.8;
		ME3_LH2_PREVLV_CLSE_T_DELAY = 0.8;
		SRB_IGN_PIC_LEVEL = 438;
		FRF_CUTOFF_TIME_DELAY = 22.0;
		FLT_CNTL_TVC_INIT_TIME_DELAY = 8.0;
		FRF_THROTTLE_TO_92_TIME_DELAY = 18.4;
		FRF_THROTTLE_TO_100_TIME_DELAY = 20.2;
		FRF_TEST_FLAG = 0;
	}

	RSLS::~RSLS()
	{
	}

	void RSLS::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "LPS_GO_FOR_AUTO_SEQ_T", ILOADs, LPS_GO_FOR_AUTO_SEQ_T );
		GetValILOAD( "SRB_IGN_ARM_T", ILOADs, SRB_IGN_ARM_T );
		GetValILOAD( "SRB_PIC_VOLTS_CHK_T", ILOADs, SRB_PIC_VOLTS_CHK_T );
		GetValILOAD( "IMU_TO_INERTIAL_T", ILOADs, IMU_TO_INERTIAL_T );
		GetValILOAD( "AUTO_RECYCLE_T", ILOADs, AUTO_RECYCLE_T );
		GetValILOAD( "OPN_LO2_ACC_RECIRC_VLV_T", ILOADs, OPN_LO2_ACC_RECIRC_VLV_T );
		GetValILOAD( "NAV_INIT_T", ILOADs, NAV_INIT_T );
		GetValILOAD( "CONFIG_VNT_DRS_FOR_LCH_T", ILOADs, CONFIG_VNT_DRS_FOR_LCH_T );
		GetValILOAD( "CHK_MPS_VLVS_POS_T", ILOADs, CHK_MPS_VLVS_POS_T );
		GetValILOAD( "CLSE_LO2_OVBD_BV_T", ILOADs, CLSE_LO2_OVBD_BV_T );
		GetValILOAD( "CHK_PREVLVS_OPN_T", ILOADs, CHK_PREVLVS_OPN_T );
		GetValILOAD( "START_SSMES_T", ILOADs, START_SSMES_T );
		GetValILOAD( "ALL_ENG_PERCENT_CHB_PRS_CHK", ILOADs, ALL_ENG_PERCENT_CHB_PRS_CHK );
		GetValILOAD( "ENG_PERCENT_CHB_PRS_FOR_GO", ILOADs, ENG_PERCENT_CHB_PRS_FOR_GO );
		GetValILOAD( "ENG_TIMER_FOR_THRUST_OK", ILOADs, ENG_TIMER_FOR_THRUST_OK );
		GetValILOAD( "VERIFY_ALL_ENG_SHTDN_TIMER", ILOADs, VERIFY_ALL_ENG_SHTDN_TIMER );
		GetValILOAD( "ME1_LOX_PREVLV_CLSE_DELAY", ILOADs, ME1_LOX_PREVLV_CLSE_DELAY );
		GetValILOAD( "ME2_LOX_PREVLV_CLSE_DELAY", ILOADs, ME2_LOX_PREVLV_CLSE_DELAY );
		GetValILOAD( "ME3_LOX_PREVLV_CLSE_DELAY", ILOADs, ME3_LOX_PREVLV_CLSE_DELAY );
		GetValILOAD( "SRB_IGN_TIME_DELAY", ILOADs, SRB_IGN_TIME_DELAY );
		GetValILOAD( "ME1_LH2_PREVLV_CLSE_T_DELAY", ILOADs, ME1_LH2_PREVLV_CLSE_T_DELAY );
		GetValILOAD( "ME2_LH2_PREVLV_CLSE_T_DELAY", ILOADs, ME2_LH2_PREVLV_CLSE_T_DELAY );
		GetValILOAD( "ME3_LH2_PREVLV_CLSE_T_DELAY", ILOADs, ME3_LH2_PREVLV_CLSE_T_DELAY );
		GetValILOAD( "SRB_IGN_PIC_LEVEL", ILOADs, SRB_IGN_PIC_LEVEL );
		GetValILOAD( "FRF_CUTOFF_TIME_DELAY", ILOADs, FRF_CUTOFF_TIME_DELAY );
		GetValILOAD( "FLT_CNTL_TVC_INIT_TIME_DELAY", ILOADs, FLT_CNTL_TVC_INIT_TIME_DELAY );
		GetValILOAD( "FRF_THROTTLE_TO_92_TIME_DELAY", ILOADs, FRF_THROTTLE_TO_92_TIME_DELAY );
		GetValILOAD( "FRF_THROTTLE_TO_100_TIME_DELAY", ILOADs, FRF_THROTTLE_TO_100_TIME_DELAY );
		GetValILOAD( "FRF_TEST_FLAG", ILOADs, FRF_TEST_FLAG );
		return;
	}


	void RSLS::OnPostStep( double simT, double dT, double mjd )
	{
		if (!Active) return;

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
			pMEC_SOP->SetMECMasterResetFlag();
			oapiWriteLog( "RSLS: MEC RESET" );
			Active = false;
			return;
		}
		else goto step1b;

	step1b:
		if (SRBIgnitionCommand)
		{
			// TODO terminate:
			// srm ign fire 1&2&3 flags

			// TODO issue:
			// t0 umb release fire 3 flag
			pMEC_SOP->SetLaunchSequencerFlag( MECSOP_LAUNCH_T0_UMB_RELEASE_FIRE_2 );
			T0UmbilicalReleased = true;
			oapiWriteLog( "RSLS: T0 UMB FIRE 2" );
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
				pMEC_SOP->SetMECMasterResetFlag();
				oapiWriteLog( "RSLS: MEC RESET" );
			}
			goto step30;
		}
		else goto step1d;

	step1d:
		if (pSSME_SOP->GetShutdownEnableCommandIssuedFlag( 1 ))
		{
			pSSME_SOP->SetShutdownCommandFlag( 1 );
			LaunchSequenceAbort = true;
			goto step30;
		}
		else goto step1e;

	step1e:
		if (pSSME_SOP->GetShutdownEnableCommandIssuedFlag( 2 ))
		{
			pSSME_SOP->SetShutdownCommandFlag( 2 );
			LaunchSequenceAbort = true;
			goto step30;
		}
		else goto step1f;

	step1f:
		if (pSSME_SOP->GetShutdownEnableCommandIssuedFlag( 3 ))
		{
			pSSME_SOP->SetShutdownCommandFlag( 3 );
			LaunchSequenceAbort = true;
			goto step30;
		}
		else goto step2;

	step2:
		if (pSSME_SOP->GetPadDataPathFailureFlag( 1 ))
		{
			ME1PadDataPathFailHold = true;
			goto step2d;
		}
		else goto step2a;

	step2a:
		if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 1, 3 ) == 1) || pSSME_SOP->GetMajorComponentFailureFlag( 1 ))
		{
			ME1ControlFailHold = true;
			goto step2d;
		}
		else goto step2c;

	step2c:
		if (pSSME_SOP->GetChannelFailureFlag( 1 ))
		{
			ME1ControlFailHold = true;
			goto step2d;
		}
		else goto step3;

	step2d:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to prestart pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step3:
		if (pSSME_SOP->GetPadDataPathFailureFlag( 2 ))
		{
			ME2PadDataPathFailHold = true;
			goto step3d;
		}
		else goto step3a;

	step3a:
		if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 2, 3 ) == 1) || pSSME_SOP->GetMajorComponentFailureFlag( 2 ))
		{
			ME2ControlFailHold = true;
			goto step3d;
		}
		else goto step3c;

	step3c:
		if (pSSME_SOP->GetChannelFailureFlag( 2 ))
		{
			ME2ControlFailHold = true;
			goto step3d;
		}
		else goto step4;

	step3d:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to prestart pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 2 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step4:
		if (pSSME_SOP->GetPadDataPathFailureFlag( 3 ))
		{
			ME3PadDataPathFailHold = true;
			goto step4d;
		}
		else goto step4a;

	step4a:
		if ((ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 3, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 3, 3 ) == 1) || pSSME_SOP->GetMajorComponentFailureFlag( 3 ))
		{
			ME3ControlFailHold = true;
			goto step4d;
		}
		else goto step4c;

	step4c:
		if (pSSME_SOP->GetChannelFailureFlag( 3 ))
		{
			ME3ControlFailHold = true;
			goto step4d;
		}
		else goto step5;

	step4d:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to prestart pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 3 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
			return;
		}
		else
		{
			RSCountdownHold = true;
			goto step9;
		}

	step5:
		if (CountdownTime >= SRB_IGN_ARM_T)
		{
			pMEC_SOP->SetLaunchSequencerFlag( MECSOP_LAUNCH_SRM_IGNITION_ARM );
			//oapiWriteLog( "RSLS: SRM IGNITION ARM" );
			pMEC_SOP->SetLaunchSequencerFlag( MECSOP_LAUNCH_T0_UMB_RELEASE_ARM );
			//oapiWriteLog( "RSLS: T0 UMB ARM" );
			goto step6;
		}
		else goto step9;

	step6:
		if (CountdownTime >= SRB_PIC_VOLTS_CHK_T)
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
			goto step7;
		}
		else goto step8;

	step7:
		if (EngStartCmdIssued)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// to umb release arm flag

			// TODO issue:
			// cmd ssme's to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
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
		if (LPSCountdownHold || RSCountdownHold)
		{
			if (CountdownTime >= AUTO_RECYCLE_T) goto step11_true;
			else
			{
				CountdownClockCounting = false;
				goto step10;
			}
		}
		else goto step12;

	step10:
		if (ResumeCountCommand)
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
			LPSCountdownHold = false;
			RSCountdownHold = false;
			ResumeCountCommand = false;
			goto step12;
		}
		else goto step11;

	step11:
		if (RecycleCountCmd) goto step11_true;
		else return;

	step11_true:
		// TODO terminate:
		// srm ign arm flag
		// t0 umb release arm flag

		// TODO issue:
		pMEC_SOP->SetMECMasterResetFlag();
		// srb rss safe flag

		CountdownTime = -540.0;
		CountdownClockCounting = false;
		// TODO re-init rsls
		return;

	step12:
		if (GMTLOSetCommand)
		{
			// TODO read GMTLO (LPS currently writes it in var GMTLO)
			CountdownTime = (mjd - GMTLO) * 86400.0;
			GMTLOSetCommand = false;
			CountdownClockCounting = true;
		}
		else CountdownTime = (mjd - GMTLO) * 86400.0;
		goto step16b;

	step13:
		if (CountdownTime >= LPS_GO_FOR_AUTO_SEQ_T)
		{
			if (LPSGoForAutoSequenceStart)
			{
				// TODO set indicator event 6 rs auto seq start
				// TODO set SSMEs to start position
				goto step14;
			}
			else
			{
				LPSGoForAutoSeqStartHold = true;
				RSCountdownHold = true;
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
		if (CountdownTime >= IMU_TO_INERTIAL_T)
		{
			// TODO issue cmd imu to inertial flag
		}
		goto step16;

	step16:
		if (CountdownTime >= OPN_LO2_ACC_RECIRC_VLV_T)
		{
			// TODO terminate mps lo2 acc recirc vlv 1 cl cmd b
			pIO_Control->SetCommand( LOX_POGO_RECIRC_1, false );
			// TODO terminate mps lo2 acc recirc vlv 2 cl cmd b
			pIO_Control->SetCommand( LOX_POGO_RECIRC_2, false );
		}
		goto step16a;

	step16a:
		if (CountdownTime >= NAV_INIT_T)
		{
			if (firstpass_step16a)
			{
				firstpass_step16a = false;
				// TODO issue init nav flag
				pSSME_SOP->SetThrottlePercent( 100 );
				oapiWriteLog( "RSLS: Initialize MEs throttle to 100%" );
			}
		}
		goto step17;

	step16b:
		if (CountdownTime >= CONFIG_VNT_DRS_FOR_LCH_T)
		{
			WriteCOMPOOL_IS( SCP_CONF_VENT_DOORS, 1 );
		}
		goto step13;

	step17:
		if (CountdownTime >= CHK_MPS_VLVS_POS_T)
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
				return;
			}
		}

	step19a:
		if ((ReadCOMPOOL_AIS( SCP_ME_READY, 1, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_READY, 2, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_READY, 3, 3 ) == 1))
		{
			// TODO op cmds b & c
			pIO_Control->SetCommand( ME1_LH2_PVLV_OP, true );
			pIO_Control->SetCommand( ME2_LH2_PVLV_OP, true );
			pIO_Control->SetCommand( ME3_LH2_PVLV_OP, true );

			if (firstpass_step19a)
			{
				firstpass_step19a = false;
				pSSME_SOP->SetStartEnableCommandFlag();
			}

			// TODO cl cmds b & c
			pIO_Control->SetCommand( ME1_LH2_PVLV_CL, false );
			pIO_Control->SetCommand( ME2_LH2_PVLV_CL, false );
			pIO_Control->SetCommand( ME3_LH2_PVLV_CL, false );

			FlagA = true;
			goto step20;
		}
		else
		{
			RSSeqSSMEGoForLaunchHold = true;
			RSCountdownHold = true;
			return;
		}

	step20:
		if (CountdownTime >= CLSE_LO2_OVBD_BV_T)
		{
			// TODO issue mps lo2 overboard b/v close cmds b & c
			pIO_Control->SetCommand( LOX_OVBD_BV, true );
		}
		goto step21;

	step21:
		if (CountdownTime >= CHK_PREVLVS_OPN_T)
		{
			if (PV19_CLInd[0].IsSet() || PV19_CLInd[1].IsSet())
			{
				if (0)// TODO close ind comm fault
				{
					MPSLO2OvbdBVCloseHold = true;
					RSCountdownHold = true;
					return;
				}
				else goto step22;
			}
			else
			{
				MPSLO2OvbdBVCloseHold = true;
				RSCountdownHold = true;
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
				return;
			}
			else goto step23;
		}
		else
		{
			MPSE1LH2PrevlvOpenHold = true;
			RSCountdownHold = true;
			return;
		}

	step23:
		if (PV5_OPInd[0].IsSet() || PV5_OPInd[1].IsSet())
		{
			if (0)// TODO open ind comm fault
			{
				MPSE2LH2PrevlvOpenHold = true;
				RSCountdownHold = true;
				return;
			}
			else goto step24;
		}
		else
		{
			MPSE2LH2PrevlvOpenHold = true;
			RSCountdownHold = true;
			return;
		}

	step24:
		if (PV6_OPInd[0].IsSet() || PV6_OPInd[1].IsSet())
		{
			if (0) // TODO open ind comm fault
			{
				MPSE3LH2PrevlvOpenHold = true;
				RSCountdownHold = true;
				return;
			}
			else goto step25;
		}
		else
		{
			MPSE3LH2PrevlvOpenHold = true;
			RSCountdownHold = true;
			return;
		}

	step25:
		{
			unsigned int stwd = ReadCOMPOOL_ID( SCP_ORBITER_VENT_DOORS_STATUS_WORD );
			if (stwd != 0x00FFFFFF)
			{
				if (0) goto step26;// TODO lps override set for each fail flag
				else
				{
					VentDoorPositionHold = true;
					RSCountdownHold = true;
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
			return;
		}

	step27:
		if (LPSGoForEngineStart) goto step28;
		else
		{
			LPSGoForEngineStartHold = true;
			RSCountdownHold = true;
			return;
		}

	step28:
		if (CountdownTime >= START_SSMES_T)
		{
			// TODO issue:
			// mps tvc servo ovrd cmd
			EngStartCmdIssued = true;
			Eng3StartCmdIssued = true;
			pSSME_SOP->SetEngineStartCommandFlag( 3 );
			oapiWriteLog( "RSLS: ME-3 Ignition Command" );

			EngStartTimer = simT;
			SRBIgnitionTimer = simT + SRB_IGN_TIME_DELAY;

			// start:
			FRFCutOffTimer = simT + FRF_CUTOFF_TIME_DELAY;
			FltCntlTVCInitTimer = simT + FLT_CNTL_TVC_INIT_TIME_DELAY;
			FRFThrottleTo92Timer = simT + FRF_THROTTLE_TO_92_TIME_DELAY;
			FRFThrottleTo100Timer = simT + FRF_THROTTLE_TO_100_TIME_DELAY;
			EngTimerThrustOK = simT + ENG_TIMER_FOR_THRUST_OK;
		}
		return;

	step28a:
		if ((simT - EngStartTimer) >= 0.12)
		{
			if (!Eng2StartCmdIssued)
			{
				pSSME_SOP->SetEngineStartCommandFlag( 2 );
				Eng2StartCmdIssued = true;
				oapiWriteLog( "RSLS: ME-2 Ignition Command" );
			}

			if ((simT - EngStartTimer) >= 0.24)
			{
				if (!Eng1StartCmdIssued)
				{
					pSSME_SOP->SetEngineStartCommandFlag( 1 );
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
			// TODO terminate prep ssmes for liftoff flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			UncommandedEngineShutdownAbort = true;
			LaunchSequenceAbort = true;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
			goto step30;
		}
		else goto step37;

	step30:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 1, 3 ) == 1))
		{
			if (ME1LOXPrevalveCloseDelayTimer == -1.0) ME1LOXPrevalveCloseDelayTimer = simT + ME1_LOX_PREVLV_CLSE_DELAY;

			if (simT >= ME1LOXPrevalveCloseDelayTimer) goto step30a;
			else goto step31;
		}
		else goto step31;

	step30a:
		// TODO issue mps e-1 lo2 prevalve cl cmd c
		pIO_Control->SetCommand( ME1_LOX_PVLV_CL_A, true );
		pIO_Control->SetCommand( ME1_LOX_PVLV_CL_B, true );
		// TODO terminate mps e-1 lo2 prevalve op cmd c
		pIO_Control->SetCommand( ME1_LOX_PVLV_OP_A, false );
		pIO_Control->SetCommand( ME1_LOX_PVLV_OP_B, false );

		if (ME1LH2PrevalveCloseDelayTimer == -1.0) ME1LH2PrevalveCloseDelayTimer = simT + ME1_LH2_PREVLV_CLSE_T_DELAY;

		if (simT >= ME1LH2PrevalveCloseDelayTimer)
		{
			// TODO issue mps e-1 lh2 prevalve cl cmds b & c
			pIO_Control->SetCommand( ME1_LH2_PVLV_CL, true );
			// TODO terminate mps e-1 lh2 prevalve op cmds b & c
			pIO_Control->SetCommand( ME1_LH2_PVLV_OP, false );
			ME1PrevalvesCmddClosed = true;
		}
		goto step31;

	step31:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 2, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 2, 3 ) == 1))
		{
			if (ME2LOXPrevalveCloseDelayTimer == -1.0) ME2LOXPrevalveCloseDelayTimer = simT + ME2_LOX_PREVLV_CLSE_DELAY;

			if (simT >= ME2LOXPrevalveCloseDelayTimer) goto step31a;
			else goto step32;
		}
		else goto step32;

	step31a:
		// TODO issue mps e-2 lo2 prevalve cl cmd c
		pIO_Control->SetCommand( ME2_LOX_PVLV_CL_A, true );
		pIO_Control->SetCommand( ME2_LOX_PVLV_CL_B, true );
		// TODO terminate mps e-2 lo2 prevalve op cmd c
		pIO_Control->SetCommand( ME2_LOX_PVLV_OP_A, false );
		pIO_Control->SetCommand( ME2_LOX_PVLV_OP_B, false );

		if (ME2LH2PrevalveCloseDelayTimer == -1.0) ME2LH2PrevalveCloseDelayTimer = simT + ME2_LH2_PREVLV_CLSE_T_DELAY;

		if (simT >= ME2LH2PrevalveCloseDelayTimer)
		{
			// TODO issue mps e-2 lh2 prevalve cl cmds b c
			pIO_Control->SetCommand( ME2_LH2_PVLV_CL, true );
			// TODO terminate mps e-2 lh2 prevalve op cmds b & c
			pIO_Control->SetCommand( ME2_LH2_PVLV_OP, false );
			ME2PrevalvesCmddClosed = true;
		}
		goto step32;

	step32:
		if ((ReadCOMPOOL_AIS( SCP_MESHDN, 3, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 3, 3 ) == 1))
		{
			if (ME3LOXPrevalveCloseDelayTimer == -1.0) ME3LOXPrevalveCloseDelayTimer = simT + ME3_LOX_PREVLV_CLSE_DELAY;

			if (simT >= ME3LOXPrevalveCloseDelayTimer) goto step32a;
			else goto step33;
		}
		else goto step33;

	step32a:
		// TODO issue mps e-3 lo2 prevalve cl cmd c
		pIO_Control->SetCommand( ME3_LOX_PVLV_CL_A, true );
		pIO_Control->SetCommand( ME3_LOX_PVLV_CL_B, true );
		// TODO terminate mps e-3 lo2 prevalve op cmd c
		pIO_Control->SetCommand( ME3_LOX_PVLV_OP_A, false );
		pIO_Control->SetCommand( ME3_LOX_PVLV_OP_B, false );

		if (ME3LH2PrevalveCloseDelayTimer == -1.0) ME3LH2PrevalveCloseDelayTimer = simT + ME3_LH2_PREVLV_CLSE_T_DELAY;

		if (simT >= ME3LH2PrevalveCloseDelayTimer)
		{
			// TODO issue mps e-3 lh2 prevalve cl cmds b & c
			pIO_Control->SetCommand( ME3_LH2_PVLV_CL, true );
			// TODO terminate mps e-3 lh2 prevalve op cmds b & c
			pIO_Control->SetCommand( ME3_LH2_PVLV_OP, false );
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
					pSSME_SOP->ResetShutdownEnableCommandFlag( 1 );
					pSSME_SOP->ResetShutdownEnableCommandFlag( 2 );
					pSSME_SOP->ResetShutdownEnableCommandFlag( 3 );
					pSSME_SOP->SetShutdownCommandFlag( 1 );
					pSSME_SOP->SetShutdownCommandFlag( 2 );
					pSSME_SOP->SetShutdownCommandFlag( 3 );
				}
				else
				{
					ShtdnEnableCmdsIssued = true;
					pSSME_SOP->ResetShutdownCommandFlag( 1 );
					pSSME_SOP->ResetShutdownCommandFlag( 2 );
					pSSME_SOP->ResetShutdownCommandFlag( 3 );
					pSSME_SOP->SetShutdownEnableCommandFlag( 1 );
					pSSME_SOP->SetShutdownEnableCommandFlag( 2 );
					pSSME_SOP->SetShutdownEnableCommandFlag( 3 );
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
			AllEngShutdownTimer = simT + VERIFY_ALL_ENG_SHTDN_TIMER;
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
			Active = false;
			return;
		}
		else return;

	step36:
		if (ME1PrevalvesCmddClosed && ME2PrevalvesCmddClosed && ME3PrevalvesCmddClosed)
		{
			Active = false;
			return;
		}
		else return;

	step37:
		if (LPSCountdownHold)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
			return;
		}
		else goto step37a;

	step37a:
		if ((ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) > ALL_ENG_PERCENT_CHB_PRS_CHK) && (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) > ALL_ENG_PERCENT_CHB_PRS_CHK) && (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) > ALL_ENG_PERCENT_CHB_PRS_CHK))
		{
			// TODO terminate mps tvc servo ovrd cmd
			// TODO issue prep ssmes for liftoff flag

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, LAUNCHCONFIG_2P, LAUNCHCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, LAUNCHCONFIG_3P, LAUNCHCONFIG_3Y );

			pMEC_SOP->SetLaunchSequencerFlag( MECSOP_LAUNCH_SRM_IGNITION_FIRE_1 );
			//oapiWriteLog( "RSLS: SRM IGNITION FIRE 1" );
			pMEC_SOP->SetLaunchSequencerFlag( MECSOP_LAUNCH_T0_UMB_RELEASE_FIRE_1 );
			//oapiWriteLog( "RSLS: T0 UMB FIRE 1" );
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
				// prep ssmes for liftoff flag
				// srm ign arm flag
				// t0 umb release arm flag

				// TODO issue:
				// cmd ssmes to pre-start pos flag
				// mps slew comp flag
				// mps tvc servo ovrd cmd
				pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
				return;
			}
		}
		else
		{
			// TODO set comm fault first pass flag E true
			goto step42;
		}

	step38:
		if (ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) > ENG_PERCENT_CHB_PRS_FOR_GO) goto step39;
		else if (simT >= EngTimerThrustOK)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			ME1LowChamberPressureAbort = true;
			pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
		}
		return;

	step39:
		if (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) > ENG_PERCENT_CHB_PRS_FOR_GO) goto step40;
		else if (simT >= EngTimerThrustOK)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			ME2LowChamberPressureAbort = true;
			pSSME_SOP->SetShutdownEnableCommandFlag( 2 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
		}
		return;

	step40:
		if (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) > ENG_PERCENT_CHB_PRS_FOR_GO) goto step41c;
		else if (simT >= EngTimerThrustOK)
		{
			// TODO terminate:
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			ME3LowChamberPressureAbort = true;
			pSSME_SOP->SetShutdownEnableCommandFlag( 3 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
		}
		return;

	step41:
		if (simT >= SRBIgnitionTimer) goto step41a;
		else return;

	step41a:
		if (FRF_TEST_FLAG == 1)
		{
			if (simT >= FRFCutOffTimer)
			{
				oapiWriteLog( "RSLS: FRF Shutdown Command" );

				// TODO terminate:
				// prep ssmes for liftoff flag
				// srm ign arm flag
				// t0 umb release arm flag

				// TODO issue:
				// cmd ssmes to pre-start pos flag
				// mps slew comp flag
				pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
				return;
			}
			else goto step41f;
		}
		else goto step41b;

	step41b:
		// TODO issue:
		// srm ign fire 3 flag
		// terminate lps polling flag
		// mode control met reset cmd
		// read gmt & store flag
		// mps tvc servo ovrd cmd
		WriteCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA ) | 0x0001 );// start event timer
		pMEC_SOP->SetLaunchSequencerFlag( MECSOP_LAUNCH_SRM_IGNITION_FIRE_2 );
		SRBIgnitionCommand = true;
		oapiWriteLog( "RSLS: SRM IGNITION FIRE 2" );
		SetMajorMode( 102 );// here?
		STS()->MTU()->StartMET();
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
				// prep ssmes for liftoff flag
				// srm ign arm flag
				// t0 umb release arm flag

				// TODO issue:
				// cmd ssmes to pre-start pos flag
				// mps slew comp flag
				// mps tvc servo ovrd cmd
				pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
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
				// prep ssmes for liftoff flag
				// srm ign arm flag
				// t0 umb release arm flag

				// TODO issue:
				// cmd ssmes to pre-start pos flag
				// mps slew comp flag
				// mps tvc servo ovrd cmd
				pSSME_SOP->SetShutdownEnableCommandFlag( 2 );

				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
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
				// prep ssmes for liftoff flag
				// srm ign arm flag
				// t0 umb release arm flag

				// TODO issue:
				// cmd ssmes to pre-start pos flag
				// mps slew comp flag
				// mps tvc servo ovrd cmd
				pSSME_SOP->SetShutdownEnableCommandFlag( 3 );

				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
				pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
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

				pSSME_SOP->SetThrottlePercent( 92 );
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
			pSSME_SOP->SetThrottlePercent( 100 );
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
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 1 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
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
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 2 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
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
			// prep ssmes for liftoff flag
			// srm ign arm flag
			// t0 umb release arm flag

			// TODO issue:
			// cmd ssmes to pre-start pos flag
			// mps slew comp flag
			// mps tvc servo ovrd cmd
			pSSME_SOP->SetShutdownEnableCommandFlag( 3 );

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, STARTCONFIG_2P, STARTCONFIG_2Y );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, STARTCONFIG_3P, STARTCONFIG_3Y );
			return;
		}

		return;
	}

	void RSLS::Realize()
	{
		pSSME_SOP = dynamic_cast<SSME_SOP*> (FindSoftware( "SSME_SOP" ));
		assert( (pSSME_SOP != NULL) && "RSLS::Realize.pSSME_SOP" );
		pIO_Control = dynamic_cast<IO_Control*> (FindSoftware( "IO_Control" ));
		assert( (pIO_Control != NULL) && "RSLS::Realize.pIO_Control" );
		pMPS_ATVC_CMD_SOP = dynamic_cast<MPS_ATVC_CMD_SOP*> (FindSoftware( "MPS_ATVC_CMD_SOP" ));
		assert( (pMPS_ATVC_CMD_SOP != NULL) && "RSLS::Realize.pMPS_ATVC_CMD_SOP" );
		pMEC_SOP = dynamic_cast<MEC_SOP*> (FindSoftware( "MEC_SOP" ));
		assert( (pMEC_SOP != NULL) && "RSLS::Realize.pMEC_SOP" );

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
		return;
	}

	bool RSLS::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
				Active = true;
			case 102:
				return true;
		}
		return false;
	}

	void RSLS::SetGMTLO( double GMTLO )
	{
		this->GMTLO = GMTLO;
		return;
	}

	void RSLS::SetGMTLOSetCommandFlag( bool val )
	{
		GMTLOSetCommand = val;
		return;
	}

	void RSLS::SetLPSCountdownHoldFlag( bool val )
	{
		LPSCountdownHold = val;
		return;
	}

	void RSLS::SetLPSGoForAutoSequenceStartFlag( bool val )
	{
		LPSGoForAutoSequenceStart = val;
		return;
	}

	void RSLS::SetLPSGoForEngineStartFlag( bool val )
	{
		LPSGoForEngineStart = val;
		return;
	}

	void RSLS::SetResumeCountCommandFlag( bool val )
	{
		ResumeCountCommand = val;
		if (val) RSCountdownHold = false;// HACK reset IMMEDIATELY after resume cmd, so hold isn't called again
		return;
	}

	bool RSLS::GetRSCountdownHoldFlag( void ) const
	{
		return RSCountdownHold;
	}

	bool RSLS::GetLaunchSequenceAbortFlag( void ) const
	{
		return LaunchSequenceAbort;
	}

	unsigned int RSLS::GetHoldFlags( void ) const
	{
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
		return tmp;
	}
}
