/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2021/05/26   GLS
2021/06/02   GLS
2021/06/28   GLS
2021/08/22   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/01   GLS
2022/01/07   GLS
2022/01/10   GLS
2022/02/08   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/04/27   GLS
2022/04/28   GLS
2022/05/21   GLS
2022/05/29   GLS
2022/06/04   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/09/06   GLS
2022/09/07   GLS
2022/09/09   GLS
2022/09/10   GLS
2022/09/29   GLS
2023/07/25   GLS
********************************************/
#include "PanelA6U.h"
#include "StandardSwitch.h"
#include "StandardRotarySwitch.h"
#include "Talkback.h"
#include "PushButtonIndicator.h"
#include "ThumbWheel.h"
#include "PushWheel.h"
#include "../Atlantis.h"
#include "../meshres_vc_a6u.h"
#include "../ParameterValues.h"
#include "vc_defs.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelA6U";
	constexpr VECTOR3 OFFSET_PANEL = {0.262478, 2.51095, 12.3974};


	PanelA6U::PanelA6U( Atlantis* _sts, const std::string &orbiter ):AtlantisPanel(_sts, "A6U")
	{
		char cbuf[255];

		if ((orbiter == "Discovery") || (orbiter == "Endeavour")) thumbwheels = false;
		else thumbwheels = true;

		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add(pSense=new StdSwitch2(_sts, "SENSE"));
		Add(pFltCntlrPower = new LockableLever2(_sts, "FLT CNTLR POWER"));
		Add(pPayloadRetentionLogicPowerSys[0] = new StdSwitch2( _sts, "PAYLOAD RETENTION LOGIC POWER SYS 1" ) );
		Add(pPayloadRetentionLogicPowerSys[1] = new StdSwitch2( _sts, "PAYLOAD RETENTION LOGIC POWER SYS 2" ) );
		Add(pPayloadRetentionLatches[0] = new StdSwitch3(_sts, "PAYLOAD RETENTION LATCHES 1"));
		Add(pPayloadRetentionLatches[1] = new StdSwitch3(_sts, "PAYLOAD RETENTION LATCHES 2"));
		Add(pPayloadRetentionLatches[2] = new StdSwitch3(_sts, "PAYLOAD RETENTION LATCHES 3"));
		Add(pPayloadRetentionLatches[3] = new StdSwitch3(_sts, "PAYLOAD RETENTION LATCHES 4"));
		Add(pPayloadRetentionLatches[4] = new StdSwitch3(_sts, "PAYLOAD RETENTION LATCHES 5"));
		Add(pPayloadSelect = new RotaryDemuxSwitch(_sts, "PAYLOAD SELECT", 5));
		Add( pLatchState[0] = new StandardTalkback3( _sts, "PAYLOAD RETENTION LATCHES 1 TB" ) );
		Add( pLatchState[1] = new StandardTalkback3( _sts, "PAYLOAD RETENTION LATCHES 2 TB" ) );
		Add( pLatchState[2] = new StandardTalkback3( _sts, "PAYLOAD RETENTION LATCHES 3 TB" ) );
		Add( pLatchState[3] = new StandardTalkback3( _sts, "PAYLOAD RETENTION LATCHES 4 TB" ) );
		Add( pLatchState[4] = new StandardTalkback3( _sts, "PAYLOAD RETENTION LATCHES 5 TB" ) );
		Add( pLatchRTL[0] = new StandardTalkback2( _sts, "PAYLOAD RETENTION LATCHES READY TO LATCH 1" ) );
		Add( pLatchRTL[1] = new StandardTalkback2( _sts, "PAYLOAD RETENTION LATCHES READY TO LATCH 2" ) );
		Add( pLatchRTL[2] = new StandardTalkback2( _sts, "PAYLOAD RETENTION LATCHES READY TO LATCH 3" ) );
		Add( pLatchRTL[3] = new StandardTalkback2( _sts, "PAYLOAD RETENTION LATCHES READY TO LATCH 4" ) );
		Add( pLatchRTL[4] = new StandardTalkback2( _sts, "PAYLOAD RETENTION LATCHES READY TO LATCH 5" ) );
		Add( pADIAttitude = new StdSwitch3( _sts, "ADI ATTITUDE" ) );
		Add( pADIError = new StdSwitch3( _sts, "ADI ERROR" ) );
		Add( pADIRate = new StdSwitch3( _sts, "ADI RATE" ) );

		Add( pAnnunciatorBusSelect = new StdSwitch3( _sts, "ANNUNCIATOR BUS SELECT" ) );
		pAnnunciatorBusSelect->SetLabel( 0, "MN C" );
		pAnnunciatorBusSelect->SetLabel( 1, "OFF" );
		pAnnunciatorBusSelect->SetLabel( 2, "MN B" );
		pAnnunciatorBusSelect->SetInitialPosition( 0 );

		Add( pAnnunciatorLampTest = new StdSwitch3( _sts, "ANNUNCIATOR LAMP TEST" ) );

		Add( pEventTimerMode = new StdSwitch3( _sts, "EVENT TIMER MODE" ) );
		Add( pEventTimerControl = new StdSwitch3( _sts, "EVENT TIMER CONTROL" ) );
		Add( pEventTimerTimer = new StdSwitch3( _sts, "EVENT TIMER TIMER" ) );

		for(int i=0;i<24;i++) {
			sprintf_s(cbuf, 255, "%d", i+1);
			std::string name="A6U_PBI";
			name+=cbuf;
			Add(pPBIs[i]=new PushButtonIndicatorSingleLight(_sts, name));
		}

		pSense->SetLabel(0, "-X");
		pSense->SetLabel(1, "-Z");
		pFltCntlrPower->SetLabel(0, "OFF");
		pFltCntlrPower->SetLabel(1, "ON");

		pPayloadRetentionLogicPowerSys[0]->SetLabel( 0, "OFF" );
		pPayloadRetentionLogicPowerSys[0]->SetLabel( 1, "ON" );
		pPayloadRetentionLogicPowerSys[1]->SetLabel( 0, "OFF" );
		pPayloadRetentionLogicPowerSys[1]->SetLabel( 1, "ON" );

		for(int i=0;i<5;i++) {
			pPayloadRetentionLatches[i]->SetLabel(0, "LATCH");
			pPayloadRetentionLatches[i]->SetLabel(1, "OFF");
			pPayloadRetentionLatches[i]->SetLabel(2, "RELEASE");
		}
		pPayloadSelect->SetLabel(0, "1");
		pPayloadSelect->SetLabel(1, "MON1");
		pPayloadSelect->SetLabel(2, "2");
		pPayloadSelect->SetLabel(3, "MON3");
		pPayloadSelect->SetLabel(4, "3");

		pADIAttitude->SetLabel( 0, "REF" );
		pADIAttitude->SetLabel( 1, "LVLH" );
		pADIAttitude->SetLabel( 2, "INRTL" );
		pADIError->SetLabel( 0, "LOW" );
		pADIError->SetLabel( 1, "MED" );
		pADIError->SetLabel( 2, "HIGH" );
		pADIRate->SetLabel( 0, "LOW" );
		pADIRate->SetLabel( 1, "MED" );
		pADIRate->SetLabel( 2, "HIGH" );

		pEventTimerMode->SetLabel( 1, "DOWN" );
		pEventTimerMode->SetLabel( 2, "UP" );

		if (thumbwheels)
		{
			Add( pEventTimerMin10 = new ThumbWheel( _sts, "EVENT TIMER MIN 10" ) );
			Add( pEventTimerMin1 = new ThumbWheel( _sts, "EVENT TIMER MIN 1" ) );
			Add( pEventTimerSec10 = new ThumbWheel( _sts, "EVENT TIMER SEC 10" ) );
			Add( pEventTimerSec1 = new ThumbWheel( _sts, "EVENT TIMER SEC 1" ) );
		}
		else
		{
			Add( pEventTimerMin10 = new PushWheel( _sts, "EVENT TIMER MIN 10" ) );
			Add( pEventTimerMin1 = new PushWheel( _sts, "EVENT TIMER MIN 1" ) );
			Add( pEventTimerSec10 = new PushWheel( _sts, "EVENT TIMER SEC 10" ) );
			Add( pEventTimerSec1 = new PushWheel( _sts, "EVENT TIMER SEC 1" ) );
		}
	}

	PanelA6U::~PanelA6U()
	{
	}

	void PanelA6U::DefineVC()
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 switch_pull = _V( 0.0, 0.3126, 0.9499 );
		const VECTOR3 push_dir = -switch_pull;
		oapiWriteLog( "PanelA6U: DefineVC called" );

		AddAIDToMouseEventList( AID_A6U );

		pSense->DefineGroup( GRP_S1_A6U_VC );
		pSense->SetInitialAnimState( 0.5 );
		pSense->SetReference( _V( 0.0, 0.269135, -0.08385 ), switch_rot );
		pSense->SetMouseRegion( AID_A6U, 0.098628f, 0.270893f, 0.138880f, 0.323253f );

		pFltCntlrPower->DefineGroup( GRP_S2_A6U_VC );
		pFltCntlrPower->SetInitialAnimState( 0.5 );
		pFltCntlrPower->SetReference( _V( 0.0, 0.269135, -0.08385 ), switch_rot );
		pFltCntlrPower->SetPullDirection( switch_pull );
		pFltCntlrPower->SetMouseRegion( AID_A6U, 0.177025f, 0.270893f, 0.218820f, 0.323253f );

		pPayloadRetentionLogicPowerSys[0]->DefineGroup( GRP_S46_A6U_VC );
		pPayloadRetentionLogicPowerSys[0]->SetInitialAnimState( 0.5f );
		pPayloadRetentionLogicPowerSys[0]->SetReference( _V( 0.0, 0.09605, -0.02995 ), switch_rot );
		pPayloadRetentionLogicPowerSys[0]->SetMouseRegion( AID_A6U, 0.084953f, 0.722369f, 0.125479f, 0.774586f );

		pPayloadRetentionLogicPowerSys[1]->DefineGroup( GRP_S47_A6U_VC );
		pPayloadRetentionLogicPowerSys[1]->SetInitialAnimState( 0.5f );
		pPayloadRetentionLogicPowerSys[1]->SetReference( _V( 0.0, 0.09605, -0.02995 ), switch_rot );
		pPayloadRetentionLogicPowerSys[1]->SetMouseRegion( AID_A6U, 0.188237f, 0.722369f, 0.229873f, 0.774586f );

		pPayloadRetentionLatches[0]->DefineGroup( GRP_S36_A6U_VC );
		pPayloadRetentionLatches[0]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[0]->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pPayloadRetentionLatches[0]->SetMouseRegion( AID_A6U, 0.305503f, 0.857711f, 0.347077f, 0.910700f );

		pPayloadRetentionLatches[1]->DefineGroup( GRP_S42_A6U_VC );
		pPayloadRetentionLatches[1]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[1]->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pPayloadRetentionLatches[1]->SetMouseRegion( AID_A6U, 0.375593f, 0.857711f, 0.417842f, 0.910700f );

		pPayloadRetentionLatches[2]->DefineGroup( GRP_S43_A6U_VC );
		pPayloadRetentionLatches[2]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[2]->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pPayloadRetentionLatches[2]->SetMouseRegion( AID_A6U, 0.448760f, 0.857711f, 0.489752f, 0.910700f );

		pPayloadRetentionLatches[3]->DefineGroup( GRP_S44_A6U_VC );
		pPayloadRetentionLatches[3]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[3]->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pPayloadRetentionLatches[3]->SetMouseRegion( AID_A6U, 0.520025f, 0.857711f, 0.561029f, 0.910700f );

		pPayloadRetentionLatches[4]->DefineGroup( GRP_S45_A6U_VC );
		pPayloadRetentionLatches[4]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[4]->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pPayloadRetentionLatches[4]->SetMouseRegion( AID_A6U, 0.591158f, 0.857711f, 0.632382f, 0.910700f );

		pPayloadSelect->DefineGroup( GRP_S37_A6U_VC );
		pPayloadSelect->SetInitialAnimState( 0.0f );
		pPayloadSelect->SetReference( _V( 0.445512, 0.039925, -0.01395 ), switch_pull );
		pPayloadSelect->DefineRotationAngle( 120.0f );
		pPayloadSelect->SetOffset( -60.0f );
		pPayloadSelect->SetMouseRegion( AID_A6U, 0.120618f, 0.849379f, 0.190510f, 0.940452f );

		pADIAttitude->DefineGroup( GRP_S5_A6U_VC );
		pADIAttitude->SetInitialAnimState( 0.5 );
		pADIAttitude->SetReference( _V( 0.0, 0.160115, -0.04995 ), switch_rot );
		pADIAttitude->SetMouseRegion( AID_A6U, 0.074821f, 0.544949f, 0.116603f, 0.607548f );

		pADIError->DefineGroup( GRP_S6_A6U_VC );
		pADIError->SetInitialAnimState( 0.5 );
		pADIError->SetReference( _V( 0.0, 0.160115, -0.04995 ), switch_rot );
		pADIError->SetMouseRegion( AID_A6U, 0.159342f, 0.544949f, 0.200350f, 0.607548f );

		pADIRate->DefineGroup( GRP_S7_A6U_VC );
		pADIRate->SetInitialAnimState( 0.5 );
		pADIRate->SetReference( _V( 0.0, 0.160115, -0.04995 ), switch_rot );
		pADIRate->SetMouseRegion( AID_A6U, 0.216830f, 0.544949f, 0.257883f, 0.607548f );

		for (int i = 0; i < 24; i++)
		{
			pPBIs[i]->SetStateOffset( 1, 0.0f, 0.488281f );
			pPBIs[i]->SetDirection( push_dir );
		}

		// switch number: original name (current name)
		pPBIs[0]->SetMouseRegion( AID_A6U, 0.302380f, 0.112640f, 0.343902f, 0.167037f );// S8: SELECT - A (SELECT - A)
		pPBIs[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_S8_A6U_VC );

		pPBIs[1]->SetMouseRegion( AID_A6U, 0.355619f, 0.112640f, 0.397401f, 0.167037f );// S9: SELECT - B (SELECT - B)
		pPBIs[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_S9_A6U_VC );

		pPBIs[2]->SetMouseRegion( AID_A6U, 0.408885f, 0.112640f, 0.450712f, 0.167037f );// S10: CONTROL - AUTO (CONTROL - AUTO)
		pPBIs[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_S10_A6U_VC );

		pPBIs[3]->SetMouseRegion( AID_A6U, 0.480867f, 0.112640f, 0.522217f, 0.167037f );// S11: CONTROL - MAN (CONTROL - INRTL)
		pPBIs[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_S11_A6U_VC );

		pPBIs[4]->SetMouseRegion( AID_A6U, 0.534342f, 0.112640f, 0.575704f, 0.167037f );// S12: RCS JETS - NORM (CONTROL - LVLH)
		pPBIs[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_S12_A6U_VC );

		pPBIs[5]->SetMouseRegion( AID_A6U, 0.587557f, 0.112640f, 0.629127f, 0.167037f );// S13: RCS JETS - VERN (CONTROL - FREE)
		pPBIs[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_S13_A6U_VC );

		pPBIs[6]->SetMouseRegion( AID_A6U, 0.302481f, 0.270600f, 0.344202f, 0.328560f );// S14: TRANSLATION X - HIGH ()
		pPBIs[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_S14_A6U_VC );

		pPBIs[7]->SetMouseRegion( AID_A6U, 0.355781f, 0.270600f, 0.397528f, 0.328560f );// S15: TRANSLATION Y - HIGH (TRANSLATION Y - LOW Z)
		pPBIs[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_S15_A6U_VC );

		pPBIs[8]->SetMouseRegion( AID_A6U, 0.409371f, 0.270600f, 0.450875f, 0.328560f );// S16: TRANSLATION Z - HIGH (TRANSLATION Z - HIGH Z)
		pPBIs[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_S16_A6U_VC );

		pPBIs[9]->SetMouseRegion( AID_A6U, 0.480845f, 0.270600f, 0.522355f, 0.328560f );// S17: ROTATION ROLL - DISC RATE (ROTATION ROLL - PRI)
		pPBIs[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_S17_A6U_VC );

		pPBIs[10]->SetMouseRegion( AID_A6U, 0.534236f, 0.270600f, 0.575915f, 0.328560f );// S18: ROTATION PITCH - DISC RATE (ROTATION PITCH - ALT)
		pPBIs[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_S18_A6U_VC );

		pPBIs[11]->SetMouseRegion( AID_A6U, 0.587621f, 0.270600f, 0.629426f, 0.328560f );// S19: ROTATION YAW - DISC RATE (ROTATION YAW - VERN)
		pPBIs[11]->DefineMeshGroup( GetVCMeshIndex(), GRP_S19_A6U_VC );

		pPBIs[12]->SetMouseRegion( AID_A6U, 0.302481f, 0.356250f, 0.344202f, 0.410405f );// S20: TRANSLATION X - NORM (TRANSLATION X - NORM)
		pPBIs[12]->DefineMeshGroup( GetVCMeshIndex(), GRP_S20_A6U_VC );

		pPBIs[13]->SetMouseRegion( AID_A6U, 0.355781f, 0.356250f, 0.397528f, 0.410405f );// S21: TRANSLATION Y - NORM (TRANSLATION Y - NORM)
		pPBIs[13]->DefineMeshGroup( GetVCMeshIndex(), GRP_S21_A6U_VC );

		pPBIs[14]->SetMouseRegion( AID_A6U, 0.409371f, 0.356250f, 0.450875f, 0.410405f );// S22: TRANSLATION Z - NORM (TRANSLATION Z - NORM)
		pPBIs[14]->DefineMeshGroup( GetVCMeshIndex(), GRP_S22_A6U_VC );

		pPBIs[15]->SetMouseRegion( AID_A6U, 0.480845f, 0.356250f, 0.522355f, 0.410405f );// S23: ROTATION ROLL - ACCEL (ROTATION ROLL - DISC RATE)
		pPBIs[15]->DefineMeshGroup( GetVCMeshIndex(), GRP_S23_A6U_VC );

		pPBIs[16]->SetMouseRegion( AID_A6U, 0.534236f, 0.356250f, 0.575915f, 0.410405f );// S24: ROTATION PITCH - ACCEL (ROTATION PITCH - DISC RATE)
		pPBIs[16]->DefineMeshGroup( GetVCMeshIndex(), GRP_S24_A6U_VC );

		pPBIs[17]->SetMouseRegion( AID_A6U, 0.587621f, 0.356250f, 0.629426f, 0.410405f );// S25: ROTATION YAW - ACCEL (ROTATION YAW - DISC RATE)
		pPBIs[17]->DefineMeshGroup( GetVCMeshIndex(), GRP_S25_A6U_VC );

		pPBIs[18]->SetMouseRegion( AID_A6U, 0.302481f, 0.432998f, 0.344202f, 0.487530f );// S26: TRANSLATION X - PULSE (TRANSLATION X - PULSE)
		pPBIs[18]->DefineMeshGroup( GetVCMeshIndex(), GRP_S26_A6U_VC );

		pPBIs[19]->SetMouseRegion( AID_A6U, 0.355781f, 0.432998f, 0.397528f, 0.487530f );// S27: TRANSLATION Y - PULSE (TRANSLATION Y - PULSE)
		pPBIs[19]->DefineMeshGroup( GetVCMeshIndex(), GRP_S27_A6U_VC );

		pPBIs[20]->SetMouseRegion( AID_A6U, 0.409371f, 0.432998f, 0.450875f, 0.487530f );// S28: TRANSLATION Z - PULSE (TRANSLATION Z - PULSE)
		pPBIs[20]->DefineMeshGroup( GetVCMeshIndex(), GRP_S28_A6U_VC );

		pPBIs[21]->SetMouseRegion( AID_A6U, 0.480845f, 0.432998f, 0.522355f, 0.487530f );// S29: ROTATION ROLL - PULSE (ROTATION ROLL - PULSE)
		pPBIs[21]->DefineMeshGroup( GetVCMeshIndex(), GRP_S29_A6U_VC );

		pPBIs[22]->SetMouseRegion( AID_A6U, 0.534236f, 0.432998f, 0.575915f, 0.487530f );// S30: ROTATION PITCH - PULSE (ROTATION PITCH - PULSE)
		pPBIs[22]->DefineMeshGroup( GetVCMeshIndex(), GRP_S30_A6U_VC );

		pPBIs[23]->SetMouseRegion( AID_A6U, 0.587621f, 0.432998f, 0.629426f, 0.487530f );// S31: ROTATION YAW - PULSE (ROTATION YAW - PULSE)
		pPBIs[23]->DefineMeshGroup( GetVCMeshIndex(), GRP_S31_A6U_VC );

		pLatchRTL[0]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS2_U_A6U_VC, GRP_DS2_L_A6U_VC );
		pLatchRTL[1]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS3_U_A6U_VC, GRP_DS3_L_A6U_VC );
		pLatchRTL[2]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS4_U_A6U_VC, GRP_DS4_L_A6U_VC );
		pLatchRTL[3]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS12_U_A6U_VC, GRP_DS12_L_A6U_VC );
		pLatchRTL[4]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS13_U_A6U_VC, GRP_DS13_L_A6U_VC );

		pLatchState[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_A6U_VC );
		pLatchState[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_A6U_VC );
		pLatchState[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS9_A6U_VC );
		pLatchState[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS10_A6U_VC );
		pLatchState[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS11_A6U_VC );

		pAnnunciatorBusSelect->SetInitialAnimState( 0.5f );
		pAnnunciatorBusSelect->DefineGroup( GRP_S33_A6U_VC );
		pAnnunciatorBusSelect->SetReference( _V( 0.0, 0.21381, -0.06665 ), switch_rot );
		pAnnunciatorBusSelect->SetMouseRegion( AID_A6U, 0.693455f, 0.415364f, 0.734311f, 0.466886f );

		pAnnunciatorLampTest->SetInitialAnimState( 0.5f );
		pAnnunciatorLampTest->DefineGroup( GRP_S34_A6U_VC );
		pAnnunciatorLampTest->SetReference( _V( 0.0, 0.21381, -0.06665 ), switch_rot );
		pAnnunciatorLampTest->SetMouseRegion( AID_A6U, 0.743841f, 0.415364f, 0.790502f, 0.466886f );
		pAnnunciatorLampTest->SetSpringLoaded( true, 0 );
		pAnnunciatorLampTest->SetSpringLoaded( true, 2 );

		pEventTimerMode->SetInitialAnimState( 0.5f );
		pEventTimerMode->DefineGroup( GRP_S39_A6U_VC );
		pEventTimerMode->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pEventTimerMode->SetMouseRegion( AID_A6U, 0.718267f, 0.857566f, 0.758678f, 0.909669f );
		pEventTimerMode->SetSpringLoaded( true, 0 );

		pEventTimerControl->SetInitialAnimState( 0.5f );
		pEventTimerControl->DefineGroup( GRP_S40_A6U_VC );
		pEventTimerControl->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pEventTimerControl->SetMouseRegion( AID_A6U, 0.768547f, 0.857566f, 0.816827f, 0.909669f );
		pEventTimerControl->SetSpringLoaded( true, 0 );
		pEventTimerControl->SetSpringLoaded( true, 2 );

		pEventTimerTimer->SetInitialAnimState( 0.5f );
		pEventTimerTimer->DefineGroup( GRP_S41_A6U_VC );
		pEventTimerTimer->SetReference( _V( 0.0, 0.04393, -0.01375 ), switch_rot );
		pEventTimerTimer->SetMouseRegion( AID_A6U, 0.825988f, 0.857566f, 0.866415f, 0.909669f );
		pEventTimerTimer->SetSpringLoaded( true, 0 );
		pEventTimerTimer->SetSpringLoaded( true, 2 );

		pEventTimerMin10->SetBounds( 0, 5 );
		pEventTimerSec10->SetBounds( 0, 5 );
		if (thumbwheels)
		{
			const VECTOR3 pos = _V( 0.0, 0.098502, -0.054399 );

			pEventTimerMin10->DefineWheelGroup( GRP_S38_THUMBWHEEL_10M_A6U_VC );
			pEventTimerMin10->SetReference( pos, switch_rot );
			pEventTimerMin10->SetMouseRegion( AID_A6U, 0.744716f, 0.691278f, 0.754887f, 0.761120f );

			pEventTimerMin1->DefineWheelGroup( GRP_S38_THUMBWHEEL_1M_A6U_VC );
			pEventTimerMin1->SetReference( pos, switch_rot );
			pEventTimerMin1->SetMouseRegion( AID_A6U, 0.780951f, 0.691278f, 0.791016f, 0.761120f );

			pEventTimerSec10->DefineWheelGroup( GRP_S38_THUMBWHEEL_10S_A6U_VC );
			pEventTimerSec10->SetReference( pos, switch_rot );
			pEventTimerSec10->SetMouseRegion( AID_A6U, 0.816347f, 0.691278f, 0.826765f, 0.761120f );

			pEventTimerSec1->DefineWheelGroup( GRP_S38_THUMBWHEEL_1S_A6U_VC );
			pEventTimerSec1->SetReference( pos, switch_rot );
			pEventTimerSec1->SetMouseRegion( AID_A6U, 0.852202f, 0.691278f, 0.862676f, 0.761120f );
		}
		else
		{
			const VECTOR3 pushbutton_dir = _V( 0.0, -0.298517, -0.9544 );
			const VECTOR3 pos = _V( 0.0, 0.099482, -0.051277 );

			pEventTimerMin10->DefineWheelGroup( GRP_S38_PUSHWHEEL_10M_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin10)->DefinePushButtonGroups( GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_10M_A6U_VC, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_10M_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin10)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerMin10->SetReference( pos, switch_rot );
			pEventTimerMin10->SetMouseRegion( AID_A6U, 0.727924f, 0.677331f, 0.748643f, 0.772438f );

			pEventTimerMin1->DefineWheelGroup( GRP_S38_PUSHWHEEL_1M_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin1)->DefinePushButtonGroups( GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_1M_A6U_VC, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_1M_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin1)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerMin1->SetReference( pos, switch_rot );
			pEventTimerMin1->SetMouseRegion( AID_A6U, 0.763386f, 0.677331f, 0.784841f, 0.772438f );

			pEventTimerSec10->DefineWheelGroup( GRP_S38_PUSHWHEEL_10S_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec10)->DefinePushButtonGroups( GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_10S_A6U_VC, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_10S_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec10)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerSec10->SetReference( pos, switch_rot );
			pEventTimerSec10->SetMouseRegion( AID_A6U, 0.799334f, 0.677331f, 0.821040f, 0.772438f );

			pEventTimerSec1->DefineWheelGroup( GRP_S38_PUSHWHEEL_1S_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec1)->DefinePushButtonGroups( GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_1S_A6U_VC, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_1S_A6U_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec1)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerSec1->SetReference( pos, switch_rot );
			pEventTimerSec1->SetMouseRegion( AID_A6U, 0.835869f, 0.677331f, 0.857234f, 0.772438f );
		}
		return;
	}

	void PanelA6U::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		//oapiWriteLog("PanelA6U: RegisterVC called");

		VECTOR3 ofs=STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A6U, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A6U,
			_V( 0.527516, 0.38211, -0.1199 ) + ofs, _V( 0.0, 0.38211, -0.1199 ) + ofs,
			_V( 0.527516, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.0 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA6U::Realize()
	{
		DiscreteBundle* pBundle=STS()->BundleManager()->CreateBundle( "DDU_POWER", 16 );
		pFltCntlrPower->ConnectPort( 1, pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "DAP_PBI_AFT_1", 16 );
		for (int i = 0; i < 16; i++) pPBIs[i]->ConnectPushButton( pBundle, i );
		pBundle = STS()->BundleManager()->CreateBundle( "DAP_PBI_AFT_2", 16 );
		for (int i = 16; i < 24; i++) pPBIs[i]->ConnectPushButton( pBundle, i - 16 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_1", 16 );
		pPBIs[0]->ConnectLight( 0, pBundle, 1 );
		pPBIs[1]->ConnectLight( 0, pBundle, 5 );
		pPBIs[2]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_2", 16 );
		pPBIs[6]->ConnectLight( 0, pBundle, 1 );
		pPBIs[7]->ConnectLight( 0, pBundle, 5 );
		pPBIs[8]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_3", 16 );
		pPBIs[12]->ConnectLight( 0, pBundle, 1 );
		pPBIs[13]->ConnectLight( 0, pBundle, 5 );
		pPBIs[14]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_4", 16 );
		pPBIs[18]->ConnectLight( 0, pBundle, 1 );
		pPBIs[19]->ConnectLight( 0, pBundle, 5 );
		pPBIs[20]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_1", 16 );
		pPBIs[3]->ConnectLight( 0, pBundle, 1 );
		pPBIs[4]->ConnectLight( 0, pBundle, 5 );
		pPBIs[5]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_2", 16 );
		pPBIs[9]->ConnectLight( 0, pBundle, 1 );
		pPBIs[10]->ConnectLight( 0, pBundle, 5 );
		pPBIs[11]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_3", 16 );
		pPBIs[15]->ConnectLight( 0, pBundle, 1 );
		pPBIs[16]->ConnectLight( 0, pBundle, 5 );
		pPBIs[17]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_4", 16 );
		pPBIs[21]->ConnectLight( 0, pBundle, 1 );
		pPBIs[22]->ConnectLight( 0, pBundle, 5 );
		pPBIs[23]->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_RETENTION_A6U_MMC", 16 );
		pPayloadRetentionLatches[0]->ConnectPort( 2, pBundle, 0 );
		pPayloadRetentionLatches[0]->ConnectPort( 0, pBundle, 1 );
		pPayloadRetentionLatches[1]->ConnectPort( 2, pBundle, 2 );
		pPayloadRetentionLatches[1]->ConnectPort( 0, pBundle, 3 );
		pPayloadRetentionLatches[2]->ConnectPort( 2, pBundle, 4 );
		pPayloadRetentionLatches[2]->ConnectPort( 0, pBundle, 5 );
		pPayloadRetentionLatches[3]->ConnectPort( 2, pBundle, 6 );
		pPayloadRetentionLatches[3]->ConnectPort( 0, pBundle, 7 );
		pPayloadRetentionLatches[4]->ConnectPort( 2, pBundle, 8 );
		pPayloadRetentionLatches[4]->ConnectPort( 0, pBundle, 9 );
		LOGIC_POWER_SYS_1A.Connect( pBundle, 10 );
		LOGIC_POWER_SYS_2A.Connect( pBundle, 11 );
		LOGIC_POWER_SYS_3A.Connect( pBundle, 12 );
		LOGIC_POWER_SYS_1B.Connect( pBundle, 13 );
		LOGIC_POWER_SYS_2B.Connect( pBundle, 14 );
		LOGIC_POWER_SYS_3B.Connect( pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 16 );
		//PL_1_SEL_1A_LAT.Connect( pBundle, 0 );
		//PL_1_SEL_1A_REL.Connect( pBundle, 1 );
		//PL_1_SEL_1_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_1A_1.Connect( pBundle, 3 );
		//PL_1_SEL_1B_LAT.Connect( pBundle, 4 );
		//PL_1_SEL_1B_REL.Connect( pBundle, 5 );
		//PL_1_SEL_1_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_1B_1.Connect( pBundle, 7 );
		PL_1_SEL_1A_LAT_TB.Connect( pBundle, 8 );
		PL_1_SEL_1A_REL_TB.Connect( pBundle, 9 );
		PL_1_RDY_1A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 16 );
		//PL_1_SEL_2A_LAT.Connect( pBundle, 0 );
		//PL_1_SEL_2A_REL.Connect( pBundle, 1 );
		//PL_1_SEL_2_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_1A_2.Connect( pBundle, 3 );
		//PL_1_SEL_2B_LAT.Connect( pBundle, 4 );
		//PL_1_SEL_2B_REL.Connect( pBundle, 5 );
		//PL_1_SEL_2_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_1B_2.Connect( pBundle, 7 );
		PL_1_SEL_2A_LAT_TB.Connect( pBundle, 8 );
		PL_1_SEL_2A_REL_TB.Connect( pBundle, 9 );
		PL_1_RDY_2A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 16 );
		//PL_1_SEL_3A_LAT.Connect( pBundle, 0 );
		//PL_1_SEL_3A_REL.Connect( pBundle, 1 );
		//PL_1_SEL_3_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_1A_3.Connect( pBundle, 3 );
		//PL_1_SEL_3B_LAT.Connect( pBundle, 4 );
		//PL_1_SEL_3B_REL.Connect( pBundle, 5 );
		//PL_1_SEL_3_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_1B_3.Connect( pBundle, 7 );
		PL_1_SEL_3A_LAT_TB.Connect( pBundle, 8 );
		PL_1_SEL_3A_REL_TB.Connect( pBundle, 9 );
		PL_1_RDY_3A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 16 );
		//PL_1_SEL_4A_LAT.Connect( pBundle, 0 );
		//PL_1_SEL_4A_REL.Connect( pBundle, 1 );
		//PL_1_SEL_4_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_1A_4.Connect( pBundle, 3 );
		//PL_1_SEL_4B_LAT.Connect( pBundle, 4 );
		//PL_1_SEL_4B_REL.Connect( pBundle, 5 );
		//PL_1_SEL_4_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_1B_4.Connect( pBundle, 7 );
		PL_1_SEL_4A_LAT_TB.Connect( pBundle, 8 );
		PL_1_SEL_4A_REL_TB.Connect( pBundle, 9 );
		PL_1_RDY_4A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 16 );
		//PL_1_SEL_5A_LAT.Connect( pBundle, 0 );
		//PL_1_SEL_5A_REL.Connect( pBundle, 1 );
		//PL_1_SEL_5_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_1A_5.Connect( pBundle, 3 );
		//PL_1_SEL_5B_LAT.Connect( pBundle, 4 );
		//PL_1_SEL_5B_REL.Connect( pBundle, 5 );
		//PL_1_SEL_5_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_1B_5.Connect( pBundle, 7 );
		PL_1_SEL_5A_LAT_TB.Connect( pBundle, 8 );
		PL_1_SEL_5A_REL_TB.Connect( pBundle, 9 );
		PL_1_RDY_5A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 16 );
		//PL_2_SEL_1A_LAT.Connect( pBundle, 0 );
		//PL_2_SEL_1A_REL.Connect( pBundle, 1 );
		//PL_2_SEL_1_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_2A_1.Connect( pBundle, 3 );
		//PL_2_SEL_1B_LAT.Connect( pBundle, 4 );
		//PL_2_SEL_1B_REL.Connect( pBundle, 5 );
		//PL_2_SEL_1_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_2B_1.Connect( pBundle, 7 );
		PL_2_SEL_1A_LAT_TB.Connect( pBundle, 8 );
		PL_2_SEL_1A_REL_TB.Connect( pBundle, 9 );
		PL_2_RDY_1A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 16 );
		//PL_2_SEL_2A_LAT.Connect( pBundle, 0 );
		//PL_2_SEL_2A_REL.Connect( pBundle, 1 );
		//PL_2_SEL_2_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_2A_2.Connect( pBundle, 3 );
		//PL_2_SEL_2B_LAT.Connect( pBundle, 4 );
		//PL_2_SEL_2B_REL.Connect( pBundle, 5 );
		//PL_2_SEL_2_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_2B_2.Connect( pBundle, 7 );
		PL_2_SEL_2A_LAT_TB.Connect( pBundle, 8 );
		PL_2_SEL_2A_REL_TB.Connect( pBundle, 9 );
		PL_2_RDY_2A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 16 );
		//PL_2_SEL_3A_LAT.Connect( pBundle, 0 );
		//PL_2_SEL_3A_REL.Connect( pBundle, 1 );
		//PL_2_SEL_3_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_2A_3.Connect( pBundle, 3 );
		//PL_2_SEL_3B_LAT.Connect( pBundle, 4 );
		//PL_2_SEL_3B_REL.Connect( pBundle, 5 );
		//PL_2_SEL_3_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_2B_3.Connect( pBundle, 7 );
		PL_2_SEL_3A_LAT_TB.Connect( pBundle, 8 );
		PL_2_SEL_3A_REL_TB.Connect( pBundle, 9 );
		PL_2_RDY_3A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 16 );
		//PL_2_SEL_4A_LAT.Connect( pBundle, 0 );
		//PL_2_SEL_4A_REL.Connect( pBundle, 1 );
		//PL_2_SEL_4_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_2A_4.Connect( pBundle, 3 );
		//PL_2_SEL_4B_LAT.Connect( pBundle, 4 );
		//PL_2_SEL_4B_REL.Connect( pBundle, 5 );
		//PL_2_SEL_4_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_2B_4.Connect( pBundle, 7 );
		PL_2_SEL_4A_LAT_TB.Connect( pBundle, 8 );
		PL_2_SEL_4A_REL_TB.Connect( pBundle, 9 );
		PL_2_RDY_4A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 16 );
		//PL_2_SEL_5A_LAT.Connect( pBundle, 0 );
		//PL_2_SEL_5A_REL.Connect( pBundle, 1 );
		//PL_2_SEL_5_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_2A_5.Connect( pBundle, 3 );
		//PL_2_SEL_5B_LAT.Connect( pBundle, 4 );
		//PL_2_SEL_5B_REL.Connect( pBundle, 5 );
		//PL_2_SEL_5_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_2B_5.Connect( pBundle, 7 );
		PL_2_SEL_5A_LAT_TB.Connect( pBundle, 8 );
		PL_2_SEL_5A_REL_TB.Connect( pBundle, 9 );
		PL_2_RDY_5A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 16 );
		//PL_3_SEL_1A_LAT.Connect( pBundle, 0 );
		//PL_3_SEL_1A_REL.Connect( pBundle, 1 );
		//PL_3_SEL_1_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_3A_1.Connect( pBundle, 3 );
		//PL_3_SEL_1B_LAT.Connect( pBundle, 4 );
		//PL_3_SEL_1B_REL.Connect( pBundle, 5 );
		//PL_3_SEL_1_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_3B_1.Connect( pBundle, 7 );
		PL_3_SEL_1A_LAT_TB.Connect( pBundle, 8 );
		PL_3_SEL_1A_REL_TB.Connect( pBundle, 9 );
		PL_3_RDY_1A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 16 );
		//PL_3_SEL_2A_LAT.Connect( pBundle, 0 );
		//PL_3_SEL_2A_REL.Connect( pBundle, 1 );
		//PL_3_SEL_2_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_3A_2.Connect( pBundle, 3 );
		//PL_3_SEL_2B_LAT.Connect( pBundle, 4 );
		//PL_3_SEL_2B_REL.Connect( pBundle, 5 );
		//PL_3_SEL_2_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_3B_2.Connect( pBundle, 7 );
		PL_3_SEL_2A_LAT_TB.Connect( pBundle, 8 );
		PL_3_SEL_2A_REL_TB.Connect( pBundle, 9 );
		PL_3_RDY_2A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 16 );
		//PL_3_SEL_3A_LAT.Connect( pBundle, 0 );
		//PL_3_SEL_3A_REL.Connect( pBundle, 1 );
		//PL_3_SEL_3_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_3A_3.Connect( pBundle, 3 );
		//PL_3_SEL_3B_LAT.Connect( pBundle, 4 );
		//PL_3_SEL_3B_REL.Connect( pBundle, 5 );
		//PL_3_SEL_3_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_3B_3.Connect( pBundle, 7 );
		PL_3_SEL_3A_LAT_TB.Connect( pBundle, 8 );
		PL_3_SEL_3A_REL_TB.Connect( pBundle, 9 );
		PL_3_RDY_3A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 16 );
		//PL_3_SEL_4A_LAT.Connect( pBundle, 0 );
		//PL_3_SEL_4A_REL.Connect( pBundle, 1 );
		//PL_3_SEL_4_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_3A_4.Connect( pBundle, 3 );
		//PL_3_SEL_4B_LAT.Connect( pBundle, 4 );
		//PL_3_SEL_4B_REL.Connect( pBundle, 5 );
		//PL_3_SEL_4_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_3B_4.Connect( pBundle, 7 );
		PL_3_SEL_4A_LAT_TB.Connect( pBundle, 8 );
		PL_3_SEL_4A_REL_TB.Connect( pBundle, 9 );
		PL_3_RDY_4A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 16 );
		//PL_3_SEL_5A_LAT.Connect( pBundle, 0 );
		//PL_3_SEL_5A_REL.Connect( pBundle, 1 );
		//PL_3_SEL_5_MOTOR_1_PWR.Connect( pBundle, 2 );
		IND_3A_5.Connect( pBundle, 3 );
		//PL_3_SEL_5B_LAT.Connect( pBundle, 4 );
		//PL_3_SEL_5B_REL.Connect( pBundle, 5 );
		//PL_3_SEL_5_MOTOR_2_PWR.Connect( pBundle, 6 );
		IND_3B_5.Connect( pBundle, 7 );
		PL_3_SEL_5A_LAT_TB.Connect( pBundle, 8 );
		PL_3_SEL_5A_REL_TB.Connect( pBundle, 9 );
		PL_3_RDY_5A_TB.Connect( pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle( "A6U_INTERNAL_LATCH_SWITCHES", 16 );
		// connect ports for payload select rotary
		PayloadSelect[0].Connect( pBundle, 0 );
		pPayloadSelect->ConnectOutputSignal( 0, pBundle, 0 );
		PayloadSelect[1].Connect( pBundle, 1 );
		pPayloadSelect->ConnectOutputSignal( 2, pBundle, 1 );
		PayloadSelect[2].Connect( pBundle, 2 );
		pPayloadSelect->ConnectOutputSignal( 4, pBundle, 2 );
		// connect 2 MON ports
		pPayloadSelect->ConnectOutputSignal( 1, pBundle, 3 );
		pPayloadSelect->ConnectOutputSignal( 3, pBundle, 4 );

		pPayloadRetentionLogicPowerSys[0]->ConnectPort( 1, pBundle, 5 );
		PLRetLogicPwrSysSwitch[0].Connect( pBundle, 5 );

		pPayloadRetentionLogicPowerSys[1]->ConnectPort( 1, pBundle, 6 );
		PLRetLogicPwrSysSwitch[1].Connect( pBundle, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "A6U_INTERNAL_LATCH_TKBKS", 16 );
		for (int i = 0; i < 5; i++)
		{
			Latch_LatchedTkbk[i].Connect( pBundle, i );
			Latch_ReleasedTkbk[i].Connect( pBundle, i + 5 );
			Latch_RTLTkbk[i].Connect( pBundle, i + 10 );

			pLatchState[i]->SetInput( 0, pBundle, i, TB_LAT );
			pLatchState[i]->SetInput( 1, pBundle, i + 5, TB_REL );
			pLatchRTL[i]->SetInput( pBundle, i + 10, TB_GRAY );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH0", 16 );
		PLD_SEL_POS_1.Connect( pBundle, 9 );
		pBundle = STS()->BundleManager()->CreateBundle( "MDM_OF4_IOM13_CH1", 16 );
		PLD_SEL_POS_2.Connect( pBundle, 0 );
		pBundle = STS()->BundleManager()->CreateBundle( "MDM_OF4_IOM13_CH0", 16 );
		PLD_SEL_POS_3.Connect( pBundle, 0 );
		pBundle = STS()->BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH0", 16 );
		PLD_SEL_MONITOR.Connect( pBundle, 0 );

		pBundle = STS()->BundleManager()->CreateBundle( "ADI_Switches_A6U", 16 );
		pADIAttitude->ConnectPort( 0, pBundle, 0 );// REF
		pADIAttitude->ConnectPort( 2, pBundle, 1 );// INRTL
		pADIError->ConnectPort( 0, pBundle, 2 );// LOW
		pADIError->ConnectPort( 2, pBundle, 3 );// HIGH
		pADIRate->ConnectPort( 0, pBundle, 4 );// LOW
		pADIRate->ConnectPort( 2, pBundle, 5 );// HIGH
		pSense->ConnectPort( 0, pBundle, 6 );// -X
		pSense->ConnectPort( 1, pBundle, 7 );// -Z

		pBundle = STS()->BundleManager()->CreateBundle( "AftEventTimer_A", 16 );
		pEventTimerMode->ConnectPort( 0, pBundle, 0 );
		pEventTimerMode->ConnectPort( 2, pBundle, 1 );
		pEventTimerControl->ConnectPort( 0, pBundle, 2 );
		pEventTimerControl->ConnectPort( 2, pBundle, 3 );
		pEventTimerTimer->ConnectPort( 0, pBundle, 4 );
		pEventTimerTimer->ConnectPort( 2, pBundle, 5 );

		pBundle = STS()->BundleManager()->CreateBundle( "AftEventTimer_B", 16 );
		pEventTimerSec1->Connect( pBundle, 0, 0 );
		pEventTimerSec1->Connect( pBundle, 1, 1 );
		pEventTimerSec1->Connect( pBundle, 2, 2 );
		pEventTimerSec1->Connect( pBundle, 3, 3 );
		pEventTimerSec10->Connect( pBundle, 4, 0 );
		pEventTimerSec10->Connect( pBundle, 5, 1 );
		pEventTimerSec10->Connect( pBundle, 6, 2 );
		pEventTimerMin1->Connect( pBundle, 7, 0 );
		pEventTimerMin1->Connect( pBundle, 8, 1 );
		pEventTimerMin1->Connect( pBundle, 9, 2 );
		pEventTimerMin1->Connect( pBundle, 10, 3 );
		pEventTimerMin10->Connect( pBundle, 11, 0 );
		pEventTimerMin10->Connect( pBundle, 12, 1 );
		pEventTimerMin10->Connect( pBundle, 13, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA", 16 );
		pAnnunciatorBusSelect->ConnectPort( 0, pBundle, 4 );
		pAnnunciatorBusSelect->ConnectPort( 2, pBundle, 5 );
		pAnnunciatorLampTest->ConnectPort( 2, pBundle, 10 );
		pAnnunciatorLampTest->ConnectPort( 0, pBundle, 11 );

		AtlantisPanel::Realize();
	}

	void PanelA6U::OnPreStep(double simt, double simdt, double mjd)
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		PanelA6U::PAYLOAD Payload = GetSelectedPayload();

		// panel output
		switch (Payload)
		{
			case PL1:
				if (PLRetLogicPwrSysSwitch[0]) LOGIC_POWER_SYS_1A.SetLine();
				else LOGIC_POWER_SYS_1A.ResetLine();
				LOGIC_POWER_SYS_2A.ResetLine();
				LOGIC_POWER_SYS_3A.ResetLine();

				if (PLRetLogicPwrSysSwitch[1]) LOGIC_POWER_SYS_1B.SetLine();
				else LOGIC_POWER_SYS_1B.ResetLine();
				LOGIC_POWER_SYS_2B.ResetLine();
				LOGIC_POWER_SYS_3B.ResetLine();


				IND_1A_1.SetLine();
				IND_1A_2.SetLine();
				IND_1A_3.SetLine();
				IND_1A_4.SetLine();
				IND_1A_5.SetLine();

				IND_2A_1.ResetLine();
				IND_2A_2.ResetLine();
				IND_2A_3.ResetLine();
				IND_2A_4.ResetLine();
				IND_2A_5.ResetLine();

				IND_3A_1.ResetLine();
				IND_3A_2.ResetLine();
				IND_3A_3.ResetLine();
				IND_3A_4.ResetLine();
				IND_3A_5.ResetLine();

				IND_1B_1.SetLine();
				IND_1B_2.SetLine();
				IND_1B_3.SetLine();
				IND_1B_4.SetLine();
				IND_1B_5.SetLine();

				IND_2B_1.ResetLine();
				IND_2B_2.ResetLine();
				IND_2B_3.ResetLine();
				IND_2B_4.ResetLine();
				IND_2B_5.ResetLine();

				IND_3B_1.ResetLine();
				IND_3B_2.ResetLine();
				IND_3B_3.ResetLine();
				IND_3B_4.ResetLine();
				IND_3B_5.ResetLine();

				PLD_SEL_POS_1.SetLine();
				PLD_SEL_POS_2.ResetLine();
				PLD_SEL_POS_3.ResetLine();
				PLD_SEL_MONITOR.ResetLine();
				break;
			case PL2:
				LOGIC_POWER_SYS_1A.ResetLine();
				if (PLRetLogicPwrSysSwitch[0]) LOGIC_POWER_SYS_2A.SetLine();
				else LOGIC_POWER_SYS_2A.ResetLine();
				LOGIC_POWER_SYS_3A.ResetLine();

				LOGIC_POWER_SYS_1B.ResetLine();
				if (PLRetLogicPwrSysSwitch[1]) LOGIC_POWER_SYS_2B.SetLine();
				else LOGIC_POWER_SYS_2B.ResetLine();
				LOGIC_POWER_SYS_3B.ResetLine();


				IND_1A_1.ResetLine();
				IND_1A_2.ResetLine();
				IND_1A_3.ResetLine();
				IND_1A_4.ResetLine();
				IND_1A_5.ResetLine();

				IND_2A_1.SetLine();
				IND_2A_2.SetLine();
				IND_2A_3.SetLine();
				IND_2A_4.SetLine();
				IND_2A_5.SetLine();

				IND_3A_1.ResetLine();
				IND_3A_2.ResetLine();
				IND_3A_3.ResetLine();
				IND_3A_4.ResetLine();
				IND_3A_5.ResetLine();

				IND_1B_1.ResetLine();
				IND_1B_2.ResetLine();
				IND_1B_3.ResetLine();
				IND_1B_4.ResetLine();
				IND_1B_5.ResetLine();

				IND_2B_1.SetLine();
				IND_2B_2.SetLine();
				IND_2B_3.SetLine();
				IND_2B_4.SetLine();
				IND_2B_5.SetLine();

				IND_3B_1.ResetLine();
				IND_3B_2.ResetLine();
				IND_3B_3.ResetLine();
				IND_3B_4.ResetLine();
				IND_3B_5.ResetLine();

				PLD_SEL_POS_1.ResetLine();
				PLD_SEL_POS_2.SetLine();
				PLD_SEL_POS_3.ResetLine();
				PLD_SEL_MONITOR.ResetLine();
				break;
			case PL3:
				LOGIC_POWER_SYS_1A.ResetLine();
				LOGIC_POWER_SYS_2A.ResetLine();
				if (PLRetLogicPwrSysSwitch[0]) LOGIC_POWER_SYS_3A.SetLine();
				else LOGIC_POWER_SYS_3A.ResetLine();

				LOGIC_POWER_SYS_1B.ResetLine();
				LOGIC_POWER_SYS_2B.ResetLine();
				if (PLRetLogicPwrSysSwitch[1]) LOGIC_POWER_SYS_3B.SetLine();
				else LOGIC_POWER_SYS_3B.ResetLine();


				IND_1A_1.ResetLine();
				IND_1A_2.ResetLine();
				IND_1A_3.ResetLine();
				IND_1A_4.ResetLine();
				IND_1A_5.ResetLine();

				IND_2A_1.ResetLine();
				IND_2A_2.ResetLine();
				IND_2A_3.ResetLine();
				IND_2A_4.ResetLine();
				IND_2A_5.ResetLine();

				IND_3A_1.SetLine();
				IND_3A_2.SetLine();
				IND_3A_3.SetLine();
				IND_3A_4.SetLine();
				IND_3A_5.SetLine();

				IND_1B_1.ResetLine();
				IND_1B_2.ResetLine();
				IND_1B_3.ResetLine();
				IND_1B_4.ResetLine();
				IND_1B_5.ResetLine();

				IND_2B_1.ResetLine();
				IND_2B_2.ResetLine();
				IND_2B_3.ResetLine();
				IND_2B_4.ResetLine();
				IND_2B_5.ResetLine();

				IND_3B_1.SetLine();
				IND_3B_2.SetLine();
				IND_3B_3.SetLine();
				IND_3B_4.SetLine();
				IND_3B_5.SetLine();

				PLD_SEL_POS_1.ResetLine();
				PLD_SEL_POS_2.ResetLine();
				PLD_SEL_POS_3.SetLine();
				PLD_SEL_MONITOR.ResetLine();
				break;
			default:// MON
				LOGIC_POWER_SYS_1A.ResetLine();
				LOGIC_POWER_SYS_2A.ResetLine();
				LOGIC_POWER_SYS_3A.ResetLine();

				LOGIC_POWER_SYS_1B.ResetLine();
				LOGIC_POWER_SYS_2B.ResetLine();
				LOGIC_POWER_SYS_3B.ResetLine();

				IND_1A_1.SetLine();
				IND_1A_2.SetLine();
				IND_1A_3.SetLine();
				IND_1A_4.SetLine();
				IND_1A_5.SetLine();

				IND_2A_1.SetLine();
				IND_2A_2.SetLine();
				IND_2A_3.SetLine();
				IND_2A_4.SetLine();
				IND_2A_5.SetLine();

				IND_3A_1.SetLine();
				IND_3A_2.SetLine();
				IND_3A_3.SetLine();
				IND_3A_4.SetLine();
				IND_3A_5.SetLine();

				IND_1B_1.SetLine();
				IND_1B_2.SetLine();
				IND_1B_3.SetLine();
				IND_1B_4.SetLine();
				IND_1B_5.SetLine();

				IND_2B_1.SetLine();
				IND_2B_2.SetLine();
				IND_2B_3.SetLine();
				IND_2B_4.SetLine();
				IND_2B_5.SetLine();

				IND_3B_1.SetLine();
				IND_3B_2.SetLine();
				IND_3B_3.SetLine();
				IND_3B_4.SetLine();
				IND_3B_5.SetLine();

				PLD_SEL_POS_1.ResetLine();
				PLD_SEL_POS_2.ResetLine();
				PLD_SEL_POS_3.ResetLine();
				PLD_SEL_MONITOR.SetLine();
				break;
		}

		// panel input
		if (PL_1_SEL_1A_LAT_TB || PL_2_SEL_1A_LAT_TB || PL_3_SEL_1A_LAT_TB) Latch_LatchedTkbk[0].SetLine();
		else Latch_LatchedTkbk[0].ResetLine();

		if (PL_1_SEL_2A_LAT_TB || PL_2_SEL_2A_LAT_TB || PL_3_SEL_2A_LAT_TB) Latch_LatchedTkbk[1].SetLine();
		else Latch_LatchedTkbk[1].ResetLine();

		if (PL_1_SEL_3A_LAT_TB || PL_2_SEL_3A_LAT_TB || PL_3_SEL_3A_LAT_TB) Latch_LatchedTkbk[2].SetLine();
		else Latch_LatchedTkbk[2].ResetLine();

		if (PL_1_SEL_4A_LAT_TB || PL_2_SEL_4A_LAT_TB || PL_3_SEL_4A_LAT_TB) Latch_LatchedTkbk[3].SetLine();
		else Latch_LatchedTkbk[3].ResetLine();

		if (PL_1_SEL_5A_LAT_TB || PL_2_SEL_5A_LAT_TB || PL_3_SEL_5A_LAT_TB) Latch_LatchedTkbk[4].SetLine();
		else Latch_LatchedTkbk[4].ResetLine();

		if (PL_1_SEL_1A_REL_TB || PL_2_SEL_1A_REL_TB || PL_3_SEL_1A_REL_TB) Latch_ReleasedTkbk[0].SetLine();
		else Latch_ReleasedTkbk[0].ResetLine();

		if (PL_1_SEL_2A_REL_TB || PL_2_SEL_2A_REL_TB || PL_3_SEL_2A_REL_TB) Latch_ReleasedTkbk[1].SetLine();
		else Latch_ReleasedTkbk[1].ResetLine();

		if (PL_1_SEL_3A_REL_TB || PL_2_SEL_3A_REL_TB || PL_3_SEL_3A_REL_TB) Latch_ReleasedTkbk[2].SetLine();
		else Latch_ReleasedTkbk[2].ResetLine();

		if (PL_1_SEL_4A_REL_TB || PL_2_SEL_4A_REL_TB || PL_3_SEL_4A_REL_TB) Latch_ReleasedTkbk[3].SetLine();
		else Latch_ReleasedTkbk[3].ResetLine();

		if (PL_1_SEL_5A_REL_TB || PL_2_SEL_5A_REL_TB || PL_3_SEL_5A_REL_TB) Latch_ReleasedTkbk[4].SetLine();
		else Latch_ReleasedTkbk[4].ResetLine();

		if (PL_1_RDY_1A_TB || PL_2_RDY_1A_TB || PL_3_RDY_1A_TB) Latch_RTLTkbk[0].SetLine();
		else Latch_RTLTkbk[0].ResetLine();

		if (PL_1_RDY_2A_TB || PL_2_RDY_2A_TB || PL_3_RDY_2A_TB) Latch_RTLTkbk[1].SetLine();
		else Latch_RTLTkbk[1].ResetLine();

		if (PL_1_RDY_3A_TB || PL_2_RDY_3A_TB || PL_3_RDY_3A_TB) Latch_RTLTkbk[2].SetLine();
		else Latch_RTLTkbk[2].ResetLine();

		if (PL_1_RDY_4A_TB || PL_2_RDY_4A_TB || PL_3_RDY_4A_TB) Latch_RTLTkbk[3].SetLine();
		else Latch_RTLTkbk[3].ResetLine();

		if (PL_1_RDY_5A_TB || PL_2_RDY_5A_TB || PL_3_RDY_5A_TB) Latch_RTLTkbk[4].SetLine();
		else Latch_RTLTkbk[4].ResetLine();
		return;
	}

	PanelA6U::PAYLOAD PanelA6U::GetSelectedPayload() const
	{
		if(PayloadSelect[0]) return PL1;
		if(PayloadSelect[1]) return PL2;
		if(PayloadSelect[2]) return PL3;
		else return MON;
	}

	void PanelA6U::VisualCreated( void )
	{
		// hide thumbwheels or pushwheels
		DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
		if (hDevMesh != NULL)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;// hide group and shadow
			if (thumbwheels)
			{
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_10M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_10S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_1M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_1S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_CASE_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_10M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_10S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_1M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_DOWN_1S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_10M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_10S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_1M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_PUSHWHEEL_PUSHBUTTON_UP_1S_A6U_VC, &grpSpec );
			}
			else
			{
				oapiEditMeshGroup( hDevMesh, GRP_S38_THUMBWHEEL_10M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_THUMBWHEEL_10S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_THUMBWHEEL_1M_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_THUMBWHEEL_1S_A6U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S38_THUMBWHEEL_CASE_A6U_VC, &grpSpec );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}
