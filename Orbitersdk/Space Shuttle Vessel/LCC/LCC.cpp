/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/05/07   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/10/18   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/08/05   GLS
2022/08/10   GLS
********************************************/
#include "LCC.h"
#include "LCC_MFD.h"
#include "../LC39/LC39.h"
#include "../SLC6/SLC6.h"


#define ORBITER_MODULE


// all times in seconds
constexpr double MPS_HE_SUPPLY_START_TIME = -21600.0;// HACK T-6h, not sure
constexpr double ORBITER_ACCESS_ARM_RETRACT_TIME = -450.0;
constexpr double PSN4_TIME = -239.0;
constexpr double MPS_TVC_ACTR_PROFILE_TIME = -210.0;
constexpr double GOX_VENT_ARM_RETRACT_TIME = -150.0;
constexpr double GO_FOR_AUTO_SEQUENCE_START_TIME = -31.0;
constexpr double PRE_LO_SS_WATER_ACTIVATION_TIME = -16.0;
constexpr double MPS_HE_SUPPLY_END_TIME = -12.5;
constexpr double GO_FOR_ENGINE_START_TIME = -10.0;

constexpr double FIREX_ACTIVATION_DELAY = 6.0;// timed from several videos
constexpr double OAA_EXTEND_DELAY = 20.0;// timed from several videos


LCC::LCC(OBJHANDLE hVessel, int flightmodel)
	: VESSEL4(hVessel, flightmodel)
{
	launch_mjd = -1.0;
	CountdownTime = -1.0;
	lastCT = -1.0;

	clockholding = false;
	requestautohold = false;
	resumecmd = false;
	resuming = false;
	resumetimer = 0.0;
	cutoff = false;
	safingcomplete = false;
	liftoff = false;
	cutofftimer = -1.0;
	OAAemergencyextend = false;
	Firexactivated = false;
	hold0730 = false;
	hold0500 = false;
	hold0400 = false;
	hold0255 = false;
	hold0157 = false;
	hold0031 = false;

	_firstrun = true;

	MPSHeSupply = true;
	MPSHeSupplyPressure1 = 2000;
	MPSHeSupplyPressure2 = 4150 + (300 * oapiRand());// 4150 - 4450 (give 50 psi leeway to LCC redlines)

	MPSTVCProfile = false;

	LPSCountdownHold = false;

	pPad = NULL;

	sprintf_s(PadName, 256, "");

	static char *name = "SSV_LCC";
	MFDMODESPECEX spec;
	spec.name = name;
	spec.key = OAPI_KEY_T;
	spec.context = NULL;
	spec.msgproc = LCC_MFD::MsgProc;
	mfdID = RegisterMFDMode( spec );
}

LCC::~LCC()
{
	UnregisterMFDMode( mfdID );
}

void LCC::clbkPostCreation()
{
	try
	{
		// get pointer to LCCPadInterface
		OBJHANDLE hPad = oapiGetVesselByName( PadName );
		if (hPad != NULL)
		{
			VESSEL* pVessel = oapiGetVesselInterface( hPad );
			if (pVessel != NULL)
			{
				if (!_strnicmp( pVessel->GetClassName(), "SSV_LC39", 7 ))
				{
					pPad = static_cast<LC39*>(pVessel);
					oapiWriteLog( "(SSV_LCC) [INFO] Connected to LCCPadInterface (LC39)" );
				}
				else if (!_strnicmp( pVessel->GetClassName(), "SSV_SLC6", 8 ))
				{
					pPad = static_cast<SLC6*>(pVessel);
					oapiWriteLog( "(SSV_LCC) [INFO] Connected to LCCPadInterface (SLC6)" );
				}
			}
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkPostCreation" );
		abort();
	}
}

void LCC::clbkPreStep(double simt, double simdt, double mjd)
{
	try
	{
		VESSEL4::clbkPreStep( simt, simdt, mjd );

		if (!pPad) return;

		if (_firstrun == true)
		{
			_firstrun = false;

			CountdownTime = (mjd - launch_mjd) * 86400.0;
			lastCT = CountdownTime;

			if (CountdownTime >= 0.0)
			{
				liftoff = true;
				return;
			}

			pPad->SetGMTLO( launch_mjd );
			pPad->SetGMTLOSetCommandFlag( true );

			// setup MPS He Supply initial status
			if ((CountdownTime < MPS_HE_SUPPLY_START_TIME) || (CountdownTime > MPS_HE_SUPPLY_END_TIME)) MPSHeSupply = false;

			if ((CountdownTime >= MPS_TVC_ACTR_PROFILE_TIME) && (CountdownTime < -135.0)) MPSTVCProfile = true;
		}

		/////////// MPS He Supply ///////////
		if (MPSHeSupply == true)
		{
			if (CountdownTime >= -12000.0)// T-3h20m
			{
				// eng
				for (int i = 1; i <= 3; i++)
				{
					if (pPad->GetHeTankPress( i ) < MPSHeSupplyPressure2) pPad->HeFillTank( i, 30 * oapiGetSimStep() );// add mass
				}

				// pneu
				if (pPad->GetHeTankPress( 0 ) < MPSHeSupplyPressure2) pPad->HeFillTank( 0, 2 * oapiGetSimStep() );// add mass
			}
			else
			{
				// eng
				for (int i = 1; i <= 3; i++)
				{
					if (pPad->GetHeTankPress( i ) < MPSHeSupplyPressure1) pPad->HeFillTank( i, 30 * oapiGetSimStep() );// add mass
				}

				// pneu
				if (pPad->GetHeTankPress( 0 ) < MPSHeSupplyPressure1) pPad->HeFillTank( 0, 2 * oapiGetSimStep() ); // add mass
			}
		}
		/////////// MPS He Supply ///////////

		if (liftoff)
		{
			// TODO
			return;
		}
		else if (cutoff)
		{
			if (safingcomplete)
			{
				// TODO recycle
			}
			else
			{
				// safing
				if (((cutofftimer + FIREX_ACTIVATION_DELAY) <= simt) && !Firexactivated && pPad->GetLaunchSequenceAbortFlag())
				{
					pPad->ActivateFirex( 1 );
					pPad->DeactivatePreLOSSWS();
					Firexactivated = true;
					oapiWriteLog( "(SSV_LCC) [INFO] Firex activated" );
				}

				if (((cutofftimer + OAA_EXTEND_DELAY) <= simt) && !OAAemergencyextend)
				{
					pPad->ExtendOrbiterAccessArm( true );
					OAAemergencyextend = true;
					oapiWriteLog( "(SSV_LCC) [INFO] Orbiter Access Arm emergency extend" );

					safingcomplete = true;
				}
			}
			return;
		}
		else if (clockholding)
		{
			if (resuming)
			{
				resumetimer -= simdt;

				if (resumetimer <= 0.0)
				{
					clockholding = false;
					resuming = false;
					resumetimer = 0.0;
					launch_mjd = mjd + (-CountdownTime / 86400.0);// re-synch so count resumes exactly at the hold time, to allow holding here again in case of failure
					pPad->SetResumeCountCommandFlag( true );
					pPad->SetGMTLO( launch_mjd );
					pPad->SetGMTLOSetCommandFlag( true );
					LPSCountdownHold = false;
					oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock has resumed" );
				}
				else return;

			}
			else if (resumecmd)
			{
				resumecmd = false;
				resuming = true;
				resumetimer = 3.0;
				launch_mjd = mjd + (-(CountdownTime - 3.0) / 86400.0);
				oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock will resume in 3 seconds" );
				return;
			}
			else
			{
				// TODO recycle
				return;
			}
		}

		// calc clock
		CountdownTime = (mjd - launch_mjd) * 86400.0;

		Checks();

		if (pPad->GetRSCountdownHoldFlag() || pPad->GetLaunchSequenceAbortFlag())
		{
			requestautohold = true;

			if (pPad->GetRSCountdownHoldFlag()) oapiWriteLog( "(SSV_LCC) [INFO] RS Countdown Hold Flag is on" );
			else oapiWriteLog( "(SSV_LCC) [INFO] Launch Sequence Abort Flag is on" );

			unsigned int holdflags = pPad->GetHoldFlags();
			if (holdflags & 0x00000001) oapiWriteLog( "(SSV_LCC) [INFO] Engine Shutdown Verification Hold" );
			else if (holdflags & 0x00000002) oapiWriteLog( "(SSV_LCC) [INFO] MPS LOX Acc Recirc Vlv Hold" );
			else if (holdflags & 0x00000004) oapiWriteLog( "(SSV_LCC) [INFO] LPS Go For Auto Seq Start Hold" );
			else if (holdflags & 0x00000008) oapiWriteLog( "(SSV_LCC) [INFO] LPS Go For Engine Start Hold" );
			else if (holdflags & 0x00000010) oapiWriteLog( "(SSV_LCC) [INFO] RS Seq SSME Go For Launch Hold" );
			else if (holdflags & 0x00000020) oapiWriteLog( "(SSV_LCC) [INFO] MPS E1 LH2 Prevlv Open Hold" );
			else if (holdflags & 0x00000040) oapiWriteLog( "(SSV_LCC) [INFO] MPS E2 LH2 Prevlv Open Hold" );
			else if (holdflags & 0x00000080) oapiWriteLog( "(SSV_LCC) [INFO] MPS E3 LH2 Prevlv Open Hold" );
			else if (holdflags & 0x00000100) oapiWriteLog( "(SSV_LCC) [INFO] MPS LO2 Ovbd BV Close Hold" );
			else if (holdflags & 0x00000200) oapiWriteLog( "(SSV_LCC) [INFO] ME1 Pad Data Path Fail Hold" );
			else if (holdflags & 0x00000400) oapiWriteLog( "(SSV_LCC) [INFO] ME2 Pad Data Path Fail Hold" );
			else if (holdflags & 0x00000800) oapiWriteLog( "(SSV_LCC) [INFO] ME3 Pad Data Path Fail Hold" );
			else if (holdflags & 0x00001000) oapiWriteLog( "(SSV_LCC) [INFO] ME1 Control Fail Hold" );
			else if (holdflags & 0x00002000) oapiWriteLog( "(SSV_LCC) [INFO] ME2 Control Fail Hold" );
			else if (holdflags & 0x00004000) oapiWriteLog( "(SSV_LCC) [INFO] ME3 Control Fail Hold" );
			else if (holdflags & 0x00008000) oapiWriteLog( "(SSV_LCC) [INFO] ME1 Low Chamber Pressure Abort" );
			else if (holdflags & 0x00010000) oapiWriteLog( "(SSV_LCC) [INFO] ME2 Low Chamber Pressure Abort" );
			else if (holdflags & 0x00020000) oapiWriteLog( "(SSV_LCC) [INFO] ME3 Low Chamber Pressure Abort" );
			else if (holdflags & 0x00040000) oapiWriteLog( "(SSV_LCC) [INFO] Uncommanded Engine Shutdown Abort" );
			else oapiWriteLogV( "(SSV_LCC) [INFO] Unknown Hold %d", holdflags );
		}

		if (requestautohold)
		{
			if ((CountdownTime > -540.0) && (CountdownTime <= -300.0))
			{
				if (!hold0500)
				{
					hold0500 = true;
					oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock will hold at T-5m due to a failure" );
				}
			}
			else if ((CountdownTime > -300.0) && (CountdownTime <= -240.0))
			{
				if (!hold0400 && !hold0500)
				{
					hold0400 = true;
					oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock will hold at T-4m due to a failure" );
				}
			}
			else if ((CountdownTime > -240.0) && (CountdownTime <= -31.0))
			{
				if (!hold0031 && !hold0400)
				{
					hold0031 = true;
					oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock will hold at T-31s due to a failure" );
				}
			}
			else if ((CountdownTime > -31.0) && !hold0031) cutoff = true;
		}

		if (cutoff) IssueCutoff();
		else if (hold0730 && (CountdownTime >= -450.0) && (lastCT < -450.0))
		{
			hold0730 = false;
			LPSCountdownHold = true;
			pPad->SetLPSCountdownHoldFlag( true );
			clockholding = true;
			CountdownTime = -450.0;
			oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock is holding at T-7m30s" );
		}
		else if (hold0500 && (CountdownTime >= -300.0) && (lastCT < -300.0))
		{
			requestautohold = false;
			hold0500 = false;
			LPSCountdownHold = true;
			pPad->SetLPSCountdownHoldFlag( true );
			clockholding = true;
			CountdownTime = -300.0;
			oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock is holding at T-5m" );
		}
		else if (hold0400 && (CountdownTime >= -240.0) && (lastCT < -240.0))
		{
			requestautohold = false;
			hold0400 = false;
			LPSCountdownHold = true;
			pPad->SetLPSCountdownHoldFlag( true );
			clockholding = true;
			CountdownTime = -240.0;
			oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock is holding at T-4m" );
		}
		else if (hold0255 && (CountdownTime >= -175.0) && (lastCT < -175.0))
		{
			hold0255 = false;
			LPSCountdownHold = true;
			pPad->SetLPSCountdownHoldFlag( true );
			clockholding = true;
			CountdownTime = -175.0;
			oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock is holding at T-2m55s" );
		}
		else if (hold0157 && (CountdownTime >= -117.0) && (lastCT < -117.0))
		{
			hold0157 = false;
			LPSCountdownHold = true;
			pPad->SetLPSCountdownHoldFlag( true );
			clockholding = true;
			CountdownTime = -117.0;
			oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock is holding at T-1m57s" );
		}
		else if (hold0031 && (CountdownTime >= -31.0) && (lastCT < -31.0))
		{
			requestautohold = false;
			hold0031 = false;
			LPSCountdownHold = true;
			pPad->SetLPSCountdownHoldFlag( true );
			clockholding = true;
			CountdownTime = -31.0;
			oapiWriteLog( "(SSV_LCC) [INFO] Countdown clock is holding at T-31s" );
		}
		else
		{
			Commands();
			lastCT = CountdownTime;
		}

		if (CountdownTime <= 0.0)
		{
			double ct = round( -CountdownTime * 10.0 ) / 10.0;// pre-round to 0.1s to avoid "60" seconds being displayed
			int hours = static_cast<int>(ct / 3600.0);
			int minutes = static_cast<int>((ct - (hours * 3600.0)) / 60.0);
			double seconds = ct - (hours*3600.0) - (minutes*60.0);
			sprintf_s( oapiDebugString(), 256, "T-%02i:%02i:%04.1f", hours, minutes, seconds );
		}
		else sprintf_s( oapiDebugString(), 256, "" );

		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkPreStep" );
		abort();
	}
}

void LCC::Checks( void )
{
	// HYD-02 - Hydraulic System Supply Pressures
	// TODO C&W param check
	// HACK using T-4m15s as start of check
	if (((CountdownTime >= -255.0) && (CountdownTime <= -235.0)) || ((CountdownTime >= -183.0) && (CountdownTime <= -10.0)))
	{
		if (((pPad->GetHydSysPress( 1 ) < 2850.0) || (pPad->GetHydSysPress( 1 ) > 3400.0)) ||
			((pPad->GetHydSysPress( 2 ) < 2850.0) || (pPad->GetHydSysPress( 2 ) > 3400.0)) ||
			((pPad->GetHydSysPress( 3 ) < 2850.0) || (pPad->GetHydSysPress( 3 ) > 3400.0)))
		{
			if (!requestautohold)
			{
				oapiWriteLog( "(SSV_LCC) [INFO] HYD-02 violation" );
				requestautohold = true;
			}
		}
	}

	// MPS-01 - MPS Helium Supply Pressure (E1,2,3, & Pneu)
	if ((CountdownTime >= (PSN4_TIME + 60.0)) && (CountdownTime <= MPS_HE_SUPPLY_END_TIME))
	{
		if (((pPad->GetHeTankPress( 1 ) < 4100.0) || (pPad->GetHeTankPress( 1 ) > 4500.0)) ||
			((pPad->GetHeTankPress( 2 ) < 4100.0) || (pPad->GetHeTankPress( 2 ) > 4500.0)) ||
			((pPad->GetHeTankPress( 3 ) < 4100.0) || (pPad->GetHeTankPress( 3 ) > 4500.0)) ||
			((pPad->GetHeTankPress( 0 ) < 4100.0) || (pPad->GetHeTankPress( 0 ) > 4500.0)))
		{
			if (!requestautohold)
			{
				oapiWriteLog( "(SSV_LCC) [INFO] MPS-01 violation" );
				requestautohold = true;
			}
		}
	}

	// MPS-03 - MPS Helium Regulator Outlet Pressure (E1,2,3 Pneu)
	if ((CountdownTime >= (PSN4_TIME + 60.0)) && (CountdownTime <= GO_FOR_ENGINE_START_TIME))
	{
		if (((pPad->GetHeRegPress( 1 ) < 730.0) || (pPad->GetHeRegPress( 1 ) > 788.0)) ||
			((pPad->GetHeRegPress( 2 ) < 730.0) || (pPad->GetHeRegPress( 2 ) > 788.0)) ||
			((pPad->GetHeRegPress( 3 ) < 730.0) || (pPad->GetHeRegPress( 3 ) > 788.0)))
		{
			if (!requestautohold)
			{
				oapiWriteLog( "(SSV_LCC) [INFO] MPS-03 violation" );
				requestautohold = true;
			}
		}
	}
	return;
}

void LCC::Commands( void )
{
	if ((CountdownTime >= MPS_HE_SUPPLY_START_TIME) && (lastCT < MPS_HE_SUPPLY_START_TIME))
	{
		MPSHeSupply = true;
		oapiWriteLog( "(SSV_LCC) [INFO] MPS He Supply started" );
	}
	else if ((CountdownTime >= ORBITER_ACCESS_ARM_RETRACT_TIME) && (lastCT < ORBITER_ACCESS_ARM_RETRACT_TIME))
	{
		pPad->RetractOrbiterAccessArm();
		oapiWriteLog( "(SSV_LCC) [INFO] Orbiter Access Arm retract" );
	}
	else if ((CountdownTime >= PSN4_TIME) && (lastCT < PSN4_TIME))
	{
		pPad->PSN4();
		oapiWriteLog( "(SSV_LCC) [INFO] Purge Sequence Number 4" );
	}
	else if ((CountdownTime >= MPS_TVC_ACTR_PROFILE_TIME) && (lastCT < MPS_TVC_ACTR_PROFILE_TIME))
	{
		MPSTVCProfile = true;
		// TODO remove override
		oapiWriteLog( "(SSV_LCC) [INFO] MPS Engine TVC Actuator Profile started" );
	}
	else if ((CountdownTime >= GOX_VENT_ARM_RETRACT_TIME) && (lastCT < GOX_VENT_ARM_RETRACT_TIME))
	{
		pPad->RetractGOXVentArm();
		oapiWriteLog( "(SSV_LCC) [INFO] GOX Vent Arm retract" );
	}
	else if ((CountdownTime >= GO_FOR_AUTO_SEQUENCE_START_TIME) && (lastCT < GO_FOR_AUTO_SEQUENCE_START_TIME))
	{
		pPad->SetLPSGoForAutoSequenceStartFlag( true );
		oapiWriteLog( "(SSV_LCC) [INFO] LPS Go For Auto Sequence Start" );
	}
	else if ((CountdownTime >= PRE_LO_SS_WATER_ACTIVATION_TIME) && (lastCT < PRE_LO_SS_WATER_ACTIVATION_TIME))
	{
		pPad->ActivatePreLOSSWS();
		oapiWriteLog( "(SSV_LCC) [INFO] Pre-Liftoff Sound Supression Water started" );
	}
	else if ((CountdownTime >= MPS_HE_SUPPLY_END_TIME) && (lastCT < MPS_HE_SUPPLY_END_TIME))
	{
		MPSHeSupply = false;
		oapiWriteLog( "(SSV_LCC) [INFO] MPS He Supply terminated" );
	}
	else if ((CountdownTime >= GO_FOR_ENGINE_START_TIME) && (lastCT < GO_FOR_ENGINE_START_TIME))
	{
		pPad->SetLPSGoForEngineStartFlag( true );
		oapiWriteLog( "(SSV_LCC) [INFO] LPS Go For Main Engine Start" );
		pPad->FireSSMEH2BurnPICs();
		oapiWriteLog( "(SSV_LCC) [INFO] Fire SSME H2 Burn PICs" );
	}
	else if ((CountdownTime >= 0.0) && (lastCT < 0.0))// TODO get liftoff indication
	{
		pPad->ActivatePostLOSSWS();
		liftoff = true;
		oapiWriteLog( "(SSV_LCC) [INFO] Post-Liftoff Sound Supression Water started" );
	}

	/////////// MPS TVC Profile ///////////
	if (MPSTVCProfile == true)
	{
		if (CountdownTime < -207.0)
		{
			// hold null
			pPad->SetSSMEActPos( 0, 0.0, 0.0 );
			pPad->SetSSMEActPos( 1, 0.0, 0.0 );
			pPad->SetSSMEActPos( 2, 0.0, 0.0 );
		}
		else if (CountdownTime < -205.0)
		{
			// move to "left-down" at 3º/s
			pPad->SetSSMEActPos( 0, (207.0 + CountdownTime) * (-3.0), (207.0 + CountdownTime) * 3.0 );
			pPad->SetSSMEActPos( 1, (207.0 + CountdownTime) * (-3.0), (207.0 + CountdownTime) * 3.0 );
			pPad->SetSSMEActPos( 2, (207.0 + CountdownTime) * (-3.0), (207.0 + CountdownTime) * 3.0 );
		}
		else if (CountdownTime < -200.0)
		{
			// hold 5s
			pPad->SetSSMEActPos( 0, -6.0, 6.0 );
			pPad->SetSSMEActPos( 1, -6.0, 6.0 );
			pPad->SetSSMEActPos( 2, -6.0, 6.0 );
		}
		else if (CountdownTime < -198.0)
		{
			// move to null at 3º/s
			pPad->SetSSMEActPos( 0, (-CountdownTime - 198.0) * (-3.0), (-CountdownTime - 198.0) * 3.0 );
			pPad->SetSSMEActPos( 1, (-CountdownTime - 198.0) * (-3.0), (-CountdownTime - 198.0) * 3.0 );
			pPad->SetSSMEActPos( 2, (-CountdownTime - 198.0) * (-3.0), (-CountdownTime - 198.0) * 3.0 );
		}
		else if (CountdownTime < -197.0)
		{
			// hold 1s
			pPad->SetSSMEActPos( 0, 0.0, 0.0 );
			pPad->SetSSMEActPos( 1, 0.0, 0.0 );
			pPad->SetSSMEActPos( 2, 0.0, 0.0 );
		}
		else if (CountdownTime < -195.0)
		{
			// move to "right-up" at 3º/s
			pPad->SetSSMEActPos( 0, (197.0 + CountdownTime) * 3.0, (197.0 + CountdownTime) * (-3.0) );
			pPad->SetSSMEActPos( 1, (197.0 + CountdownTime) * 3.0, (197.0 + CountdownTime) * (-3.0) );
			pPad->SetSSMEActPos( 2, (197.0 + CountdownTime) * 3.0, (197.0 + CountdownTime) * (-3.0) );
		}
		else if (CountdownTime < -190.0)
		{
			// hold 5s
			pPad->SetSSMEActPos( 0, 6.0, -6.0 );
			pPad->SetSSMEActPos( 1, 6.0, -6.0 );
			pPad->SetSSMEActPos( 2, 6.0, -6.0 );
		}
		else if (CountdownTime < -188.0)
		{
			// move to null at 3º/s
			pPad->SetSSMEActPos( 0, (-CountdownTime - 188.0) * 3.0, (-CountdownTime - 188.0) * (-3.0) );
			pPad->SetSSMEActPos( 1, (-CountdownTime - 188.0) * 3.0, (-CountdownTime - 188.0) * (-3.0) );
			pPad->SetSSMEActPos( 2, (-CountdownTime - 188.0) * 3.0, (-CountdownTime - 188.0) * (-3.0) );
		}
		else if (CountdownTime < -135.0)
		{
			// hold null
			pPad->SetSSMEActPos( 0, 0.0, 0.0 );
			pPad->SetSSMEActPos( 1, 0.0, 0.0 );
			pPad->SetSSMEActPos( 2, 0.0, 0.0 );
		}
		else
		{
			// move to start config
			pPad->SetSSMEActPos( 0, 0.0, 0.0 );
			pPad->SetSSMEActPos( 1, 0.0, 0.0 );
			pPad->SetSSMEActPos( 2, 0.0, 0.0 );
			MPSTVCProfile = false;
			oapiWriteLog( "(SSV_LCC) [INFO] MPS Engine TVC Actuator Profile terminated" );
		}
	}
	/////////// MPS TVC Profile ///////////
	return;
}

void LCC::IssueCutoff( void )
{
	cutoff = true;
	cutofftimer = oapiGetSimTime();
	LPSCountdownHold = true;
	pPad->SetLPSCountdownHoldFlag( true );
	pPad->SetLPSGoForEngineStartFlag( false );
	pPad->SetLPSGoForAutoSequenceStartFlag( false );
	oapiWriteLog( "(SSV_LCC) [INFO] Cutoff" );
	return;
}

void LCC::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		char cbuf[255];
		VESSEL4::clbkSaveState( scn );

		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );

		//oapiWriteScenario_float(scn, "LAUNCH_MJD", launch_mjd);
		//oapiWriteScenario_float cannot be used for launch mjd; too many decimals are lost
		sprintf_s(cbuf, 255, "%.10f", launch_mjd);
		oapiWriteScenario_string( scn, "LAUNCH_MJD", cbuf );
		oapiWriteScenario_string( scn, "PAD_NAME", PadName );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkSaveState" );
		abort();
	}
}

void LCC::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char* line;
		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				// TODO load mission file
			}
			else if (!_strnicmp( line, "LAUNCH_MJD", 10 ))
			{
				sscanf_s( line + 10, "%lf", &launch_mjd );
			}
			else if (!_strnicmp( line, "PAD_NAME", 8 ))
			{
				sscanf_s( line + 8, "%s", PadName, sizeof(PadName) );
			}
			else ParseScenarioLineEx( line, status );
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC) [FATAL ERROR] Exception in LCC::clbkLoadStateEx" );
		abort();
	}
}

DLLCLBK void InitModule(HINSTANCE hDLL)
{
}

DLLCLBK void ExitModule(HINSTANCE hDLL)
{
}

DLLCLBK VESSEL* ovcInit(OBJHANDLE hvessel, int flightmodel)
{
	try
	{
		return new LCC(hvessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	try
	{
		if (vessel) delete static_cast<LCC*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LCC) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LCC) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}
