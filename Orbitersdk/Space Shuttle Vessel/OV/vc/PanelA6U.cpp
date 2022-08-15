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
2022/05/29   GLS
2022/06/04   GLS
2022/06/23   GLS
2022/08/05   GLS
********************************************/
#include "PanelA6U.h"
#include "StandardSwitch.h"
#include "StandardRotarySwitch.h"
#include "Talkback.h"
#include "PushButtonIndicator.h"
#include "..\Atlantis.h"
#include "..\meshres_vc_a6u.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"


extern GDIParams g_Param;


namespace vc
{
	PanelA6U::PanelA6U( Atlantis* _sts ):AtlantisPanel(_sts, "A6U")
	{
		char cbuf[255];

		DefineMesh( MESHNAME_PANELA6U );

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

		for (int i = 0; i < 4; i++)
		{
			tgtwheel_state[i] = 0;
			wheelState[i] = 0.0;
			wheelnumber[i] = 0;
			oldwheelnumber[i] = 9;
		}
	}

	PanelA6U::~PanelA6U()
	{
		delete VC_A6Evt10MW;
		delete VC_A6Evt1MW;
		delete VC_A6Evt10SW;
		delete VC_A6Evt1SW;
	}

	bool PanelA6U::OnVCMouseEvent( int id, int _event, VECTOR3 &p )
	{
		if (id != AID_A6U) return false;

		if (_event & PANEL_MOUSE_LBDOWN)
		{
			if(p.x> 0.742159 && p.x < 0.752623)
			{
				if(p.y > 0.700371 && p.y < 0.726227)
				{
					if (wheelnumber[0] < 5) tgtwheel_state[0] += 0.25;
					return true;
				}
				else if(p.y > 0.750358 && p.y < 0.775435)
				{
					if (wheelnumber[0] > 0) tgtwheel_state[0] -= 0.25;
					if(tgtwheel_state[0] < 0) tgtwheel_state[0] +=EVTTMR_WHEELMAX_A6[0];
					return true;
				}
			}
			else if(p.x> 0.780784 && p.x < 0.791980)
			{
				if(p.y > 0.700371 && p.y < 0.726227)
				{
					tgtwheel_state[1] += 0.25;
					return true;
				}
				else if(p.y > 0.750358 && p.y < 0.775435)
				{
					tgtwheel_state[1] -= 0.25;
					if(tgtwheel_state[1] < 0) tgtwheel_state[1] +=EVTTMR_WHEELMAX_A6[1];
					return true;
				}
			}
			else if(p.x> 0.820791 && p.x < 0.830950)
			{
				if(p.y > 0.700371 && p.y < 0.726227)
				{
					if (wheelnumber[2] < 5) tgtwheel_state[2] += 0.25;
					return true;
				}
				else if(p.y > 0.750358 && p.y < 0.775435)
				{
					if (wheelnumber[2] > 0) tgtwheel_state[2] -= 0.25;
					if(tgtwheel_state[2] < 0) tgtwheel_state[2] +=EVTTMR_WHEELMAX_A6[2];
					return true;
				}
			}
			else if(p.x> 0.861106 && p.x < 0.871223)
			{
				if(p.y > 0.700371 && p.y < 0.726227)
				{
					tgtwheel_state[3] += 0.25;
					return true;
				}
				else if(p.y > 0.750358 && p.y < 0.775435)
				{
					tgtwheel_state[3] -= 0.25;
					if(tgtwheel_state[3] < 0) tgtwheel_state[3] +=EVTTMR_WHEELMAX_A6[3];
					return true;
				}
			}
		}
		return AtlantisPanel::OnVCMouseEvent( id, _event, p );
	}

	bool PanelA6U::OnVCRedrawEvent( int id, int _event, SURFHANDLE surf )
	{
		const int NUMX[10] = {0, 64, 128, 192, 0, 64, 128, 192, 0, 64};
		const int NUMY[10] = {0, 0, 0, 0, 64, 64, 64, 64, 128, 128};

		switch (id)
		{
			case AID_A6U_WND0:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[0]], NUMY[wheelnumber[0]], 63, 63);
				return true;
			case AID_A6U_WND1:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[1]], NUMY[wheelnumber[1]], 63, 63);
				return true;
			case AID_A6U_WND2:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[2]], NUMY[wheelnumber[2]], 63, 63);
				return true;
			case AID_A6U_WND3:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[3]], NUMY[wheelnumber[3]], 63, 63);
				return true;
		}
		return AtlantisPanel::OnVCRedrawEvent( id, _event, surf );
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
		pSense->SetReference( _V( 0.728, 2.780, 12.313 ), switch_rot );
		pSense->SetMouseRegion( AID_A6U, 0.098628f, 0.270893f, 0.138880f, 0.323253f );

		pFltCntlrPower->DefineGroup( GRP_S2_A6U_VC );
		pFltCntlrPower->SetInitialAnimState( 0.5 );
		pFltCntlrPower->SetReference( _V( 0.686, 2.781, 12.313 ), switch_rot );
		pFltCntlrPower->SetPullDirection( switch_pull );
		pFltCntlrPower->SetMouseRegion( AID_A6U, 0.177025f, 0.270893f, 0.218820f, 0.323253f );

		pPayloadRetentionLogicPowerSys[0]->DefineGroup( GRP_S46_A6U_VC );
		pPayloadRetentionLogicPowerSys[0]->SetInitialAnimState( 0.5f );
		pPayloadRetentionLogicPowerSys[0]->SetReference( _V( 0.7303, 2.6068, 12.3675 ), switch_rot );
		pPayloadRetentionLogicPowerSys[0]->SetMouseRegion( AID_A6U, 0.084953f, 0.722369f, 0.125479f, 0.774586f );

		pPayloadRetentionLogicPowerSys[1]->DefineGroup( GRP_S47_A6U_VC );
		pPayloadRetentionLogicPowerSys[1]->SetInitialAnimState( 0.5f );
		pPayloadRetentionLogicPowerSys[1]->SetReference( _V( 0.6757, 2.6068, 12.3675 ), switch_rot );
		pPayloadRetentionLogicPowerSys[1]->SetMouseRegion( AID_A6U, 0.188237f, 0.722369f, 0.229873f, 0.774586f );

		pPayloadRetentionLatches[0]->DefineGroup( GRP_S36_A6U_VC );
		pPayloadRetentionLatches[0]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[0]->SetReference( _V( 0.618, 2.555, 12.383 ), switch_rot );
		pPayloadRetentionLatches[0]->SetMouseRegion( AID_A6U, 0.305503f, 0.857711f, 0.347077f, 0.910700f );

		pPayloadRetentionLatches[1]->DefineGroup( GRP_S42_A6U_VC );
		pPayloadRetentionLatches[1]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[1]->SetReference( _V( 0.582, 2.555, 12.383 ), switch_rot );
		pPayloadRetentionLatches[1]->SetMouseRegion( AID_A6U, 0.375593f, 0.857711f, 0.417842f, 0.910700f );

		pPayloadRetentionLatches[2]->DefineGroup( GRP_S43_A6U_VC );
		pPayloadRetentionLatches[2]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[2]->SetReference( _V( 0.543, 2.555, 12.383 ), switch_rot );
		pPayloadRetentionLatches[2]->SetMouseRegion( AID_A6U, 0.448760f, 0.857711f, 0.489752f, 0.910700f );

		pPayloadRetentionLatches[3]->DefineGroup( GRP_S44_A6U_VC );
		pPayloadRetentionLatches[3]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[3]->SetReference( _V( 0.505, 2.554, 12.383 ), switch_rot );
		pPayloadRetentionLatches[3]->SetMouseRegion( AID_A6U, 0.520025f, 0.857711f, 0.561029f, 0.910700f );

		pPayloadRetentionLatches[4]->DefineGroup( GRP_S45_A6U_VC );
		pPayloadRetentionLatches[4]->SetInitialAnimState( 0.5 );
		pPayloadRetentionLatches[4]->SetReference( _V( 0.468, 2.554, 12.383), switch_rot );
		pPayloadRetentionLatches[4]->SetMouseRegion( AID_A6U, 0.591158f, 0.857711f, 0.632382f, 0.910700f );

		pPayloadSelect->DefineGroup( GRP_S37_A6U_VC );
		pPayloadSelect->SetInitialAnimState( 0.0f );
		pPayloadSelect->SetReference( _V( 0.7079, 2.5535, 12.3926 ), switch_pull );
		pPayloadSelect->DefineRotationAngle( 120.0f );
		pPayloadSelect->SetOffset( -60.0f );
		pPayloadSelect->SetMouseRegion( AID_A6U, 0.120618f, 0.849379f, 0.190510f, 0.940452f );

		pADIAttitude->DefineGroup( GRP_S5_A6U_VC );
		pADIAttitude->SetInitialAnimState( 0.5 );
		pADIAttitude->SetReference( _V( 0.6908, 2.6717, 12.3472 ), switch_rot );
		pADIAttitude->SetMouseRegion( AID_A6U, 0.074821f, 0.544949f, 0.116603f, 0.607548f );

		pADIError->DefineGroup( GRP_S6_A6U_VC );
		pADIError->SetInitialAnimState( 0.5 );
		pADIError->SetReference( _V( 0.6908, 2.6717, 12.3472 ), switch_rot );
		pADIError->SetMouseRegion( AID_A6U, 0.159342f, 0.544949f, 0.200350f, 0.607548f );

		pADIRate->DefineGroup( GRP_S7_A6U_VC );
		pADIRate->SetInitialAnimState( 0.5 );
		pADIRate->SetReference( _V( 0.6908, 2.6717, 12.3472 ), switch_rot );
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
		pAnnunciatorBusSelect->SetReference( _V( 0.4093, 2.7248, 12.3307 ), switch_rot );
		pAnnunciatorBusSelect->SetMouseRegion( AID_A6U, 0.693455f, 0.415364f, 0.734311f, 0.466886f );

		pAnnunciatorLampTest->SetInitialAnimState( 0.5f );
		pAnnunciatorLampTest->DefineGroup( GRP_S34_A6U_VC );
		pAnnunciatorLampTest->SetReference( _V( 0.4093, 2.7248, 12.3307 ), switch_rot );
		pAnnunciatorLampTest->SetMouseRegion( AID_A6U, 0.743841f, 0.415364f, 0.790502f, 0.466886f );
		pAnnunciatorLampTest->SetSpringLoaded( true, 0 );
		pAnnunciatorLampTest->SetSpringLoaded( true, 2 );

		pEventTimerMode->SetInitialAnimState( 0.5f );
		pEventTimerMode->DefineGroup( GRP_S39_A6U_VC );
		pEventTimerMode->SetReference( _V( 0.3962, 2.5547, 12.3837 ), switch_rot );
		pEventTimerMode->SetMouseRegion( AID_A6U, 0.718267f, 0.857566f, 0.758678f, 0.909669f );
		pEventTimerMode->SetSpringLoaded( true, 0 );

		pEventTimerControl->SetInitialAnimState( 0.5f );
		pEventTimerControl->DefineGroup( GRP_S40_A6U_VC );
		pEventTimerControl->SetReference( _V( 0.3667, 2.5549, 12.3836 ), switch_rot );
		pEventTimerControl->SetMouseRegion( AID_A6U, 0.768547f, 0.857566f, 0.816827f, 0.909669f );
		pEventTimerControl->SetSpringLoaded( true, 0 );
		pEventTimerControl->SetSpringLoaded( true, 2 );

		pEventTimerTimer->SetInitialAnimState( 0.5f );
		pEventTimerTimer->DefineGroup( GRP_S41_A6U_VC );
		pEventTimerTimer->SetReference( _V( 0.3392, 2.5549, 12.3837 ), switch_rot );
		pEventTimerTimer->SetMouseRegion( AID_A6U, 0.825988f, 0.857566f, 0.866415f, 0.909669f );
		pEventTimerTimer->SetSpringLoaded( true, 0 );
		pEventTimerTimer->SetSpringLoaded( true, 2 );
		return;
	}

	void PanelA6U::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		//oapiWriteLog("PanelA6U: RegisterVC called");

		VECTOR3 ofs=STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A6U, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A6U,
			_V( 0.789994, 2.89306, 12.2775 ) + ofs, _V( 0.262478, 2.89306, 12.2775 ) + ofs,
			_V( 0.789994, 2.51095, 12.3974 ) + ofs, _V( 0.262478, 2.51095, 12.3974 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		// event timer wheel numbers
		SURFHANDLE digittex = oapiGetTextureHandle( GetVCMeshHandle(), TEX_SSV_OV_CLOCKNUMS_A6U_VC );
		oapiVCRegisterArea( AID_A6U_WND0, _R( 0, 64, 63, 127 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		oapiVCRegisterArea( AID_A6U_WND1, _R( 64, 64, 127, 127 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		oapiVCRegisterArea( AID_A6U_WND2, _R( 128, 64, 191, 127 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		oapiVCRegisterArea( AID_A6U_WND3, _R( 192, 64, 255, 127 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
	}

	void PanelA6U::DefineVCAnimations( UINT vcidx )
	{
		static VECTOR3 wheel_rot = {-1.0, 0, 0};
		static VECTOR3 wheel_pos = _V( 0.0, 2.6080, 12.3532 );

		static UINT VC_A6Evt10MW_Grp = GRP_S38_THUMBWHEEL1_A6U_VC;

		VC_A6Evt10MW = new MGROUP_ROTATE(GetVCMeshIndex(), &VC_A6Evt10MW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_A6Wheel[0]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_A6Wheel[0], 0, 1, VC_A6Evt10MW);

		static UINT VC_A6Evt1MW_Grp = GRP_S38_THUMBWHEEL2_A6U_VC;

		VC_A6Evt1MW = new MGROUP_ROTATE(GetVCMeshIndex(), &VC_A6Evt1MW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_A6Wheel[1]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_A6Wheel[1], 0, 1, VC_A6Evt1MW);

		static UINT VC_A6Evt10SW_Grp = GRP_S38_THUMBWHEEL3_A6U_VC;

		VC_A6Evt10SW = new MGROUP_ROTATE(GetVCMeshIndex(), &VC_A6Evt10SW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_A6Wheel[2]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_A6Wheel[2], 0, 1, VC_A6Evt10SW);

		static UINT VC_A6Evt1SW_Grp = GRP_S38_THUMBWHEEL4_A6U_VC;

		VC_A6Evt1SW = new MGROUP_ROTATE(GetVCMeshIndex(), &VC_A6Evt1SW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_A6Wheel[3]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_A6Wheel[3], 0, 1, VC_A6Evt1SW);

		AtlantisPanel::DefineVCAnimations( vcidx );
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

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 10 );
		PL_1_SEL_1A_LAT.Connect( pBundle, 0 );
		PL_1_SEL_1A_REL.Connect( pBundle, 1 );
		PL_1_RDY_1A.Connect( pBundle, 2 );
		//PL_1_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_1A_1.Connect( pBundle, 4 );
		//PL_1_SEL_1B_LAT.Connect( pBundle, 5 );
		//PL_1_SEL_1B_REL.Connect( pBundle, 6 );
		//PL_1_RDY_1B.Connect( pBundle, 7 );
		//PL_1_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_1B_1.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 10 );
		PL_1_SEL_2A_LAT.Connect( pBundle, 0 );
		PL_1_SEL_2A_REL.Connect( pBundle, 1 );
		PL_1_RDY_2A.Connect( pBundle, 2 );
		//PL_1_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_1A_2.Connect( pBundle, 4 );
		//PL_1_SEL_2B_LAT.Connect( pBundle, 5 );
		//PL_1_SEL_2B_REL.Connect( pBundle, 6 );
		//PL_1_RDY_2B.Connect( pBundle, 7 );
		//PL_1_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_1B_2.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 10 );
		PL_1_SEL_3A_LAT.Connect( pBundle, 0 );
		PL_1_SEL_3A_REL.Connect( pBundle, 1 );
		PL_1_RDY_3A.Connect( pBundle, 2 );
		//PL_1_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_1A_3.Connect( pBundle, 4 );
		//PL_1_SEL_3B_LAT.Connect( pBundle, 5 );
		//PL_1_SEL_3B_REL.Connect( pBundle, 6 );
		//PL_1_RDY_3B.Connect( pBundle, 7 );
		//PL_1_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_1B_3.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 10 );
		PL_1_SEL_4A_LAT.Connect( pBundle, 0 );
		PL_1_SEL_4A_REL.Connect( pBundle, 1 );
		PL_1_RDY_4A.Connect( pBundle, 2 );
		//PL_1_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_1A_4.Connect( pBundle, 4 );
		//PL_1_SEL_4B_LAT.Connect( pBundle, 5 );
		//PL_1_SEL_4B_REL.Connect( pBundle, 6 );
		//PL_1_RDY_4B.Connect( pBundle, 7 );
		//PL_1_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_1B_4.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 10 );
		PL_1_SEL_5A_LAT.Connect( pBundle, 0 );
		PL_1_SEL_5A_REL.Connect( pBundle, 1 );
		PL_1_RDY_5A.Connect( pBundle, 2 );
		//PL_1_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_1A_5.Connect( pBundle, 4 );
		//PL_1_SEL_5B_LAT.Connect( pBundle, 5 );
		//PL_1_SEL_5B_REL.Connect( pBundle, 6 );
		//PL_1_RDY_5B.Connect( pBundle, 7 );
		//PL_1_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_1B_5.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
		PL_2_SEL_1A_LAT.Connect( pBundle, 0 );
		PL_2_SEL_1A_REL.Connect( pBundle, 1 );
		PL_2_RDY_1A.Connect( pBundle, 2 );
		//PL_2_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_2A_1.Connect( pBundle, 4 );
		//PL_2_SEL_1B_LAT.Connect( pBundle, 5 );
		//PL_2_SEL_1B_REL.Connect( pBundle, 6 );
		//PL_2_RDY_1B.Connect( pBundle, 7 );
		//PL_2_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_2B_1.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
		PL_2_SEL_2A_LAT.Connect( pBundle, 0 );
		PL_2_SEL_2A_REL.Connect( pBundle, 1 );
		PL_2_RDY_2A.Connect( pBundle, 2 );
		//PL_2_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_2A_2.Connect( pBundle, 4 );
		//PL_2_SEL_2B_LAT.Connect( pBundle, 5 );
		//PL_2_SEL_2B_REL.Connect( pBundle, 6 );
		//PL_2_RDY_2B.Connect( pBundle, 7 );
		//PL_2_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_2B_2.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
		PL_2_SEL_3A_LAT.Connect( pBundle, 0 );
		PL_2_SEL_3A_REL.Connect( pBundle, 1 );
		PL_2_RDY_3A.Connect( pBundle, 2 );
		//PL_2_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_2A_3.Connect( pBundle, 4 );
		//PL_2_SEL_3B_LAT.Connect( pBundle, 5 );
		//PL_2_SEL_3B_REL.Connect( pBundle, 6 );
		//PL_2_RDY_3B.Connect( pBundle, 7 );
		//PL_2_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_2B_3.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 10 );
		PL_2_SEL_4A_LAT.Connect( pBundle, 0 );
		PL_2_SEL_4A_REL.Connect( pBundle, 1 );
		PL_2_RDY_4A.Connect( pBundle, 2 );
		//PL_2_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_2A_4.Connect( pBundle, 4 );
		//PL_2_SEL_4B_LAT.Connect( pBundle, 5 );
		//PL_2_SEL_4B_REL.Connect( pBundle, 6 );
		//PL_2_RDY_4B.Connect( pBundle, 7 );
		//PL_2_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_2B_4.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 10 );
		PL_2_SEL_5A_LAT.Connect( pBundle, 0 );
		PL_2_SEL_5A_REL.Connect( pBundle, 1 );
		PL_2_RDY_5A.Connect( pBundle, 2 );
		//PL_2_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_2A_5.Connect( pBundle, 4 );
		//PL_2_SEL_5B_LAT.Connect( pBundle, 5 );
		//PL_2_SEL_5B_REL.Connect( pBundle, 6 );
		//PL_2_RDY_5B.Connect( pBundle, 7 );
		//PL_2_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_2B_5.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 10 );
		PL_3_SEL_1A_LAT.Connect( pBundle, 0 );
		PL_3_SEL_1A_REL.Connect( pBundle, 1 );
		PL_3_RDY_1A.Connect( pBundle, 2 );
		//PL_3_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_3A_1.Connect( pBundle, 4 );
		//PL_3_SEL_1B_LAT.Connect( pBundle, 5 );
		//PL_3_SEL_1B_REL.Connect( pBundle, 6 );
		//PL_3_RDY_1B.Connect( pBundle, 7 );
		//PL_3_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_3B_1.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 10 );
		PL_3_SEL_2A_LAT.Connect( pBundle, 0 );
		PL_3_SEL_2A_REL.Connect( pBundle, 1 );
		PL_3_RDY_2A.Connect( pBundle, 2 );
		//PL_3_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_3A_2.Connect( pBundle, 4 );
		//PL_3_SEL_2B_LAT.Connect( pBundle, 5 );
		//PL_3_SEL_2B_REL.Connect( pBundle, 6 );
		//PL_3_RDY_2B.Connect( pBundle, 7 );
		//PL_3_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_3B_2.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
		PL_3_SEL_3A_LAT.Connect( pBundle, 0 );
		PL_3_SEL_3A_REL.Connect( pBundle, 1 );
		PL_3_RDY_3A.Connect( pBundle, 2 );
		//PL_3_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_3A_3.Connect( pBundle, 4 );
		//PL_3_SEL_3B_LAT.Connect( pBundle, 5 );
		//PL_3_SEL_3B_REL.Connect( pBundle, 6 );
		//PL_3_RDY_3B.Connect( pBundle, 7 );
		//PL_3_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_3B_3.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
		PL_3_SEL_4A_LAT.Connect( pBundle, 0 );
		PL_3_SEL_4A_REL.Connect( pBundle, 1 );
		PL_3_RDY_4A.Connect( pBundle, 2 );
		//PL_3_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_3A_4.Connect( pBundle, 4 );
		//PL_3_SEL_4B_LAT.Connect( pBundle, 5 );
		//PL_3_SEL_4B_REL.Connect( pBundle, 6 );
		//PL_3_RDY_4B.Connect( pBundle, 7 );
		//PL_3_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_3B_4.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
		PL_3_SEL_5A_LAT.Connect( pBundle, 0 );
		PL_3_SEL_5A_REL.Connect( pBundle, 1 );
		PL_3_RDY_5A.Connect( pBundle, 2 );
		//PL_3_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
		IND_3A_5.Connect( pBundle, 4 );
		//PL_3_SEL_5B_LAT.Connect( pBundle, 5 );
		//PL_3_SEL_5B_REL.Connect( pBundle, 6 );
		//PL_3_RDY_5B.Connect( pBundle, 7 );
		//PL_3_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
		IND_3B_5.Connect( pBundle, 9 );

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
		Seconds_1.Connect( pBundle, 0 );
		Seconds_2.Connect( pBundle, 1 );
		Seconds_4.Connect( pBundle, 2 );
		Seconds_8.Connect( pBundle, 3 );
		Seconds_10.Connect( pBundle, 4 );
		Seconds_20.Connect( pBundle, 5 );
		Seconds_40.Connect( pBundle, 6 );
		Minutes_1.Connect( pBundle, 7 );
		Minutes_2.Connect( pBundle, 8 );
		Minutes_4.Connect( pBundle, 9 );
		Minutes_8.Connect( pBundle, 10 );
		Minutes_10.Connect( pBundle, 11 );
		Minutes_20.Connect( pBundle, 12 );
		Minutes_40.Connect( pBundle, 13 );

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
				break;
		}

		// panel input
		if (PL_1_SEL_1A_LAT || PL_2_SEL_1A_LAT || PL_3_SEL_1A_LAT) Latch_LatchedTkbk[0].SetLine();
		else Latch_LatchedTkbk[0].ResetLine();

		if (PL_1_SEL_2A_LAT || PL_2_SEL_2A_LAT || PL_3_SEL_2A_LAT) Latch_LatchedTkbk[1].SetLine();
		else Latch_LatchedTkbk[1].ResetLine();

		if (PL_1_SEL_3A_LAT || PL_2_SEL_3A_LAT || PL_3_SEL_3A_LAT) Latch_LatchedTkbk[2].SetLine();
		else Latch_LatchedTkbk[2].ResetLine();

		if (PL_1_SEL_4A_LAT || PL_2_SEL_4A_LAT || PL_3_SEL_4A_LAT) Latch_LatchedTkbk[3].SetLine();
		else Latch_LatchedTkbk[3].ResetLine();

		if (PL_1_SEL_5A_LAT || PL_2_SEL_5A_LAT || PL_3_SEL_5A_LAT) Latch_LatchedTkbk[4].SetLine();
		else Latch_LatchedTkbk[4].ResetLine();

		if (PL_1_SEL_1A_REL || PL_2_SEL_1A_REL || PL_3_SEL_1A_REL) Latch_ReleasedTkbk[0].SetLine();
		else Latch_ReleasedTkbk[0].ResetLine();

		if (PL_1_SEL_2A_REL || PL_2_SEL_2A_REL || PL_3_SEL_2A_REL) Latch_ReleasedTkbk[1].SetLine();
		else Latch_ReleasedTkbk[1].ResetLine();

		if (PL_1_SEL_3A_REL || PL_2_SEL_3A_REL || PL_3_SEL_3A_REL) Latch_ReleasedTkbk[2].SetLine();
		else Latch_ReleasedTkbk[2].ResetLine();

		if (PL_1_SEL_4A_REL || PL_2_SEL_4A_REL || PL_3_SEL_4A_REL) Latch_ReleasedTkbk[3].SetLine();
		else Latch_ReleasedTkbk[3].ResetLine();

		if (PL_1_SEL_5A_REL || PL_2_SEL_5A_REL || PL_3_SEL_5A_REL) Latch_ReleasedTkbk[4].SetLine();
		else Latch_ReleasedTkbk[4].ResetLine();

		if (PL_1_RDY_1A || PL_2_RDY_1A || PL_3_RDY_1A) Latch_RTLTkbk[0].SetLine();
		else Latch_RTLTkbk[0].ResetLine();

		if (PL_1_RDY_2A || PL_2_RDY_2A || PL_3_RDY_2A) Latch_RTLTkbk[1].SetLine();
		else Latch_RTLTkbk[1].ResetLine();

		if (PL_1_RDY_3A || PL_2_RDY_3A || PL_3_RDY_3A) Latch_RTLTkbk[2].SetLine();
		else Latch_RTLTkbk[2].ResetLine();

		if (PL_1_RDY_4A || PL_2_RDY_4A || PL_3_RDY_4A) Latch_RTLTkbk[3].SetLine();
		else Latch_RTLTkbk[3].ResetLine();

		if (PL_1_RDY_5A || PL_2_RDY_5A || PL_3_RDY_5A) Latch_RTLTkbk[4].SetLine();
		else Latch_RTLTkbk[4].ResetLine();



		//// event timer ////
		double fCurrState = 0.0;
		double fTgtState = 0.0;

		double fDeltaWheel = 0.5 * simdt;

		for(int i = 0; i<4; i++)
		{
			fCurrState = wheelState[i];
			fTgtState = tgtwheel_state[i];


			if(0.0 == fCurrState && fTgtState >= EVTTMR_WHEELMAX_A6[i] - 0.5)
			{
				fCurrState = EVTTMR_WHEELMAX_A6[i];
			}

			if(fCurrState <= 0.5 && fTgtState == EVTTMR_WHEELMAX_A6[i])
			{
				fTgtState = 0.0;
			}

			if(fCurrState == fTgtState)
			{
				if(tgtwheel_state[i] >= EVTTMR_WHEELMAX_A6[i])
				{
					tgtwheel_state[i] -= EVTTMR_WHEELMAX_A6[i];
				}
				continue;
			}
			else if(fCurrState > fTgtState)
			{
				if(fCurrState - fDeltaWheel < fTgtState)
					wheelState[i] = fTgtState;
				else
					wheelState[i] = fCurrState - fDeltaWheel;
			}
			else
			{
				if(fCurrState + fDeltaWheel > fTgtState)
					wheelState[i] = fTgtState;
				else
					wheelState[i] = fCurrState + fDeltaWheel;
			}

			if(wheelState[i] >= EVTTMR_WHEELMAX_A6[i])
			{
				wheelState[i] -= EVTTMR_WHEELMAX_A6[i];
				if(tgtwheel_state[i] > EVTTMR_WHEELMAX_A6[i])
					tgtwheel_state[i] -= EVTTMR_WHEELMAX_A6[i];
			}

			wheelnumber[i] = (int)(fmod(wheelState[i]/ 0.25, EVTTMR_WHEELMAX_A6[i] * 2.0) );

			STS()->SetAnimation(anim_VC_A6Wheel[i], fmod(wheelState[i], 1.0));
		}


		if(wheelnumber[0] != oldwheelnumber[0])
		{
			oapiVCTriggerRedrawArea(-1, AID_A6U_WND0);
			oldwheelnumber[0] = wheelnumber[0];
			Minutes_10.SetLine( (wheelnumber[0] & 1) * 5.0f );
			Minutes_20.SetLine( ((wheelnumber[0] >> 1) & 1) * 5.0f );
			Minutes_40.SetLine( ((wheelnumber[0] >> 2) & 1) * 5.0f );
		}

		if(wheelnumber[1] != oldwheelnumber[1])
		{
			oapiVCTriggerRedrawArea(-1, AID_A6U_WND1);
			oldwheelnumber[1] = wheelnumber[1];
			Minutes_1.SetLine( (wheelnumber[1] & 1) * 5.0f );
			Minutes_2.SetLine( ((wheelnumber[1] >> 1) & 1) * 5.0f );
			Minutes_4.SetLine( ((wheelnumber[1] >> 2) & 1) * 5.0f );
			Minutes_8.SetLine( ((wheelnumber[1] >> 3) & 1) * 5.0f );
		}

		if(wheelnumber[2] != oldwheelnumber[2])
		{
			oapiVCTriggerRedrawArea(-1, AID_A6U_WND2);
			oldwheelnumber[2] = wheelnumber[2];
			Seconds_10.SetLine( (wheelnumber[2] & 1) * 5.0f );
			Seconds_20.SetLine( ((wheelnumber[2] >> 1) & 1) * 5.0f );
			Seconds_40.SetLine( ((wheelnumber[2] >> 2) & 1) * 5.0f );
		}

		if(wheelnumber[3] != oldwheelnumber[3])
		{
			oapiVCTriggerRedrawArea(-1, AID_A6U_WND3);
			oldwheelnumber[3] = wheelnumber[3];
			Seconds_1.SetLine( (wheelnumber[3] & 1) * 5.0f );
			Seconds_2.SetLine( ((wheelnumber[3] >> 1) & 1) * 5.0f );
			Seconds_4.SetLine( ((wheelnumber[3] >> 2) & 1) * 5.0f );
			Seconds_8.SetLine( ((wheelnumber[3] >> 3) & 1) * 5.0f );
		}
	}

	PanelA6U::PAYLOAD PanelA6U::GetSelectedPayload() const
	{
		if(PayloadSelect[0]) return PL1;
		if(PayloadSelect[1]) return PL2;
		if(PayloadSelect[2]) return PL3;
		else return MON;
	}
};
