/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/05/24   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/05/26   GLS
2021/06/02   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/01   GLS
2022/01/07   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
#include "PanelC2.h"
#include "StandardSwitch.h"
#include "Keyboard.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_c2.h"


extern GDIParams g_Param;


namespace vc
{
	PanelC2::PanelC2( Atlantis* psts ):AtlantisPanel( psts, "C2" )
	{
		DefineMesh( MESHNAME_PANELC2 );

		Add( pKeyboardCDR = new Keyboard( psts, "LH KEYBOARD", 1 ) );
		Add( pKeyboardPLT = new Keyboard( psts, "RH KEYBOARD", 2 ) );

		Add( pIDPCRTPower[0] = new StdSwitch2( psts, "IDP/CRT 1 POWER" ) );
		pIDPCRTPower[0]->SetLabel( 0, "OFF" );
		pIDPCRTPower[0]->SetLabel( 1, "ON" );
		pIDPCRTPower[0]->SetInitialPosition( 1 );
		Add( pIDPCRTPower[1] = new StdSwitch2( psts, "IDP/CRT 2 POWER" ) );
		pIDPCRTPower[1]->SetLabel( 0, "OFF" );
		pIDPCRTPower[1]->SetLabel( 1, "ON" );
		pIDPCRTPower[1]->SetInitialPosition( 1 );
		Add( pIDPCRTPower[2] = new StdSwitch2( psts, "IDP/CRT 3 POWER" ) );
		pIDPCRTPower[2]->SetLabel( 0, "OFF" );
		pIDPCRTPower[2]->SetLabel( 1, "ON" );
		pIDPCRTPower[2]->SetInitialPosition( 1 );

		Add( pIDPCRTMajFunc[0] = new StdSwitch3( psts, "IDP/CRT 1 MAJ FUNC" ) );
		pIDPCRTMajFunc[0]->SetLabel( 0, "PL" );
		pIDPCRTMajFunc[0]->SetLabel( 1, "SM" );
		pIDPCRTMajFunc[0]->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc[0]->SetInitialPosition( 2 );
		Add( pIDPCRTMajFunc[1] = new StdSwitch3( psts, "IDP/CRT 2 MAJ FUNC" ) );
		pIDPCRTMajFunc[1]->SetLabel( 0, "PL" );
		pIDPCRTMajFunc[1]->SetLabel( 1, "SM" );
		pIDPCRTMajFunc[1]->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc[1]->SetInitialPosition( 2 );
		Add( pIDPCRTMajFunc[2] = new StdSwitch3( psts, "IDP/CRT 3 MAJ FUNC" ) );
		pIDPCRTMajFunc[2]->SetLabel( 0, "PL" );
		pIDPCRTMajFunc[2]->SetLabel( 1, "SM" );
		pIDPCRTMajFunc[2]->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc[2]->SetInitialPosition( 2 );

		Add( pCRTSEL[0] = new StdSwitch2( psts, "LEFT IDP/CRT SEL" ) );
		pCRTSEL[0]->SetLabel( 0, "3" );
		pCRTSEL[0]->SetLabel( 1, "1" );
		pCRTSEL[0]->SetInitialPosition( 1 );
		Add( pCRTSEL[1] = new StdSwitch2( psts, "RIGHT IDP/CRT SEL" ) );
		pCRTSEL[1]->SetLabel( 0, "2" );
		pCRTSEL[1]->SetLabel( 1, "3" );

		Add( pEventTimerMode = new StdSwitch3( psts, "EVENT TIMER MODE" ) );
		pEventTimerMode->SetLabel( 0, "TEST" );
		pEventTimerMode->SetLabel( 1, "DOWN" );
		pEventTimerMode->SetLabel( 2, "UP" );

		Add( pEventTimerControl = new StdSwitch3( psts, "EVENT TIMER CONTROL" ) );
		pEventTimerControl->SetLabel( 0, "STOP" );
		pEventTimerControl->SetLabel( 1, "-" );
		pEventTimerControl->SetLabel( 2, "START" );

		Add( pTimer = new StdSwitch3( psts, "EVENT TIMER TIMER" ) );
		pTimer->SetLabel( 0, "RESET" );
		pTimer->SetLabel( 1, "-" );
		pTimer->SetLabel( 2, "SET" );

		for (int i = 0; i < 4; i++)
		{
			tgtwheel_state[i] = 0;
			wheelState[i] = 0.0;
			wheelnumber[i] = 0;
			oldwheelnumber[i] = 9;
		}
	}

	PanelC2::~PanelC2()
	{
		delete VC_C2Evt10MW;
		delete VC_C2Evt1MW;
		delete VC_C2Evt10SW;
		delete VC_C2Evt1SW;
	}

	void PanelC2::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		double fCurrState = 0.0;
		double fTgtState = 0.0;

		double fDeltaWheel = 0.5 * simdt;

		for(int i = 0; i<4; i++)
		{
			fCurrState = wheelState[i];
			fTgtState = tgtwheel_state[i];


			if(0.0 == fCurrState && fTgtState >= EVTTMR_WHEELMAX_C2[i] - 0.5)
			{
				fCurrState = EVTTMR_WHEELMAX_C2[i];
			}

			if(fCurrState <= 0.5 && fTgtState == EVTTMR_WHEELMAX_C2[i])
			{
				fTgtState = 0.0;
			}

			if(fCurrState == fTgtState)
			{
				if(tgtwheel_state[i] >= EVTTMR_WHEELMAX_C2[i])
				{
					tgtwheel_state[i] -= EVTTMR_WHEELMAX_C2[i];
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

			if(wheelState[i] >= EVTTMR_WHEELMAX_C2[i])
			{
				wheelState[i] -= EVTTMR_WHEELMAX_C2[i];
				if(tgtwheel_state[i] > EVTTMR_WHEELMAX_C2[i])
					tgtwheel_state[i] -= EVTTMR_WHEELMAX_C2[i];
			}

			wheelnumber[i] = (int)(fmod(wheelState[i]/ 0.25, EVTTMR_WHEELMAX_C2[i] * 2.0) );

			STS()->SetAnimation(anim_VC_C2Wheel[i], fmod(wheelState[i], 1.0));
		}


		if(wheelnumber[0] != oldwheelnumber[0])
		{
			oapiVCTriggerRedrawArea(-1, AID_C2_WND0);
			oldwheelnumber[0] = wheelnumber[0];
			Minutes_10.SetLine( (wheelnumber[0] & 1) * 5.0f );
			Minutes_20.SetLine( ((wheelnumber[0] >> 1) & 1) * 5.0f );
			Minutes_40.SetLine( ((wheelnumber[0] >> 2) & 1) * 5.0f );
		}

		if(wheelnumber[1] != oldwheelnumber[1])
		{
			oapiVCTriggerRedrawArea(-1, AID_C2_WND1);
			oldwheelnumber[1] = wheelnumber[1];
			Minutes_1.SetLine( (wheelnumber[1] & 1) * 5.0f );
			Minutes_2.SetLine( ((wheelnumber[1] >> 1) & 1) * 5.0f );
			Minutes_4.SetLine( ((wheelnumber[1] >> 2) & 1) * 5.0f );
			Minutes_8.SetLine( ((wheelnumber[1] >> 3) & 1) * 5.0f );
		}

		if(wheelnumber[2] != oldwheelnumber[2])
		{
			oapiVCTriggerRedrawArea(-1, AID_C2_WND2);
			oldwheelnumber[2] = wheelnumber[2];
			Seconds_10.SetLine( (wheelnumber[2] & 1) * 5.0f );
			Seconds_20.SetLine( ((wheelnumber[2] >> 1) & 1) * 5.0f );
			Seconds_40.SetLine( ((wheelnumber[2] >> 2) & 1) * 5.0f );
		}

		if(wheelnumber[3] != oldwheelnumber[3])
		{
			oapiVCTriggerRedrawArea(-1, AID_C2_WND3);
			oldwheelnumber[3] = wheelnumber[3];
			Seconds_1.SetLine( (wheelnumber[3] & 1) * 5.0f );
			Seconds_2.SetLine( ((wheelnumber[3] >> 1) & 1) * 5.0f );
			Seconds_4.SetLine( ((wheelnumber[3] >> 2) & 1) * 5.0f );
			Seconds_8.SetLine( ((wheelnumber[3] >> 3) & 1) * 5.0f );
		}
		return;
	}

	bool PanelC2::OnVCMouseEvent( int id, int _event, VECTOR3 &p )
	{
		if (id != AID_C2) return false;

		if (_event == PANEL_MOUSE_LBDOWN)
		{
			if (p.x > 0.495206 && p.x < 0.505833)
			{
				if (p.y > 0.614160 && p.y < 0.670943)
				{
					if (wheelnumber[0] < 5) tgtwheel_state[0] += 0.25;
					return true;
				}
				else if (p.y > 0.703429 && p.y < 0.756185)
				{
					if (wheelnumber[0] > 0) tgtwheel_state[0] -= 0.25;
					if (tgtwheel_state[0] < 0) tgtwheel_state[0] += EVTTMR_WHEELMAX_C2[0];
					return true;
				}
			}
			else if (p.x > 0.534728 && p.x < 0.545137)
			{
				if (p.y > 0.614160 && p.y < 0.670943)
				{
					tgtwheel_state[1] += 0.25;
					return true;
				}
				else if (p.y > 0.703429 && p.y < 0.756185)
				{
					tgtwheel_state[1] -= 0.25;
					if(tgtwheel_state[1] < 0) tgtwheel_state[1] += EVTTMR_WHEELMAX_C2[1];
					return true;
				}
			}
			else if (p.x > 0.574551 && p.x < 0.585762)
			{
				if (p.y > 0.614160 && p.y < 0.670943)
				{
					if (wheelnumber[2] < 5) tgtwheel_state[2] += 0.25;
					return true;
				}
				else if (p.y > 0.703429 && p.y < 0.756185)
				{
					if (wheelnumber[2] > 0) tgtwheel_state[2] -= 0.25;
					if(tgtwheel_state[2] < 0) tgtwheel_state[2] += EVTTMR_WHEELMAX_C2[2];
					return true;
				}
			}
			else if (p.x > 0.614937 && p.x < 0.626158)
			{
				if (p.y > 0.614160 && p.y < 0.670943)
				{
					tgtwheel_state[3] += 0.25;
					return true;
				}
				else if (p.y > 0.703429 && p.y < 0.756185)
				{
					tgtwheel_state[3] -= 0.25;
					if(tgtwheel_state[3] < 0) tgtwheel_state[3] += EVTTMR_WHEELMAX_C2[3];
					return true;
				}
			}
		}
		return AtlantisPanel::OnVCMouseEvent( id, _event, p );
	}

	bool PanelC2::OnVCRedrawEvent( int id, int _event, SURFHANDLE surf )
	{
		const int NUMX[10] = {0, 64, 128, 192, 0, 64, 128, 192, 0, 64};
		const int NUMY[10] = {0, 0, 0, 0, 64, 64, 64, 64, 128, 128};

		switch (id)
		{
			case AID_C2_WND0:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[0]], NUMY[wheelnumber[0]], 63, 63);
				return true;
			case AID_C2_WND1:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[1]], NUMY[wheelnumber[1]], 63, 63);
				return true;
			case AID_C2_WND2:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[2]], NUMY[wheelnumber[2]], 63, 63);
				return true;
			case AID_C2_WND3:
				oapiBlt(surf, g_Param.clock_digits, 0,0, NUMX[wheelnumber[3]], NUMY[wheelnumber[3]], 63, 63);
				return true;
		}
		return AtlantisPanel::OnVCRedrawEvent( id, _event, surf );
	}

	void PanelC2::DefineVC()
	{
		VECTOR3 switch_rot = _V( 1, 0, 0 );
		VECTOR3 switch_rotH = _V( 0, 0.707107, 0.707107 );
		VECTOR3 panel_normal = _V( 0.0, 0.723051, -0.690795 );

		AddAIDToMouseEventList( AID_C2 );

		UINT LeftKeyboardGrp[32] = {GRP_LEFT_KEYBOARD_FAULTSUMM_C2_VC, GRP_LEFT_KEYBOARD_SYSSUMM_C2_VC, GRP_LEFT_KEYBOARD_MSGRESET_C2_VC, GRP_LEFT_KEYBOARD_ACK_C2_VC,
					GRP_LEFT_KEYBOARD_GPCCRT_C2_VC, GRP_LEFT_KEYBOARD_A_C2_VC, GRP_LEFT_KEYBOARD_B_C2_VC, GRP_LEFT_KEYBOARD_C_C2_VC,
					GRP_LEFT_KEYBOARD_IORESET_C2_VC, GRP_LEFT_KEYBOARD_D_C2_VC, GRP_LEFT_KEYBOARD_E_C2_VC, GRP_LEFT_KEYBOARD_F_C2_VC,
					GRP_LEFT_KEYBOARD_ITEM_C2_VC, GRP_LEFT_KEYBOARD_1_C2_VC, GRP_LEFT_KEYBOARD_2_C2_VC, GRP_LEFT_KEYBOARD_3_C2_VC,
					GRP_LEFT_KEYBOARD_EXEC_C2_VC, GRP_LEFT_KEYBOARD_4_C2_VC, GRP_LEFT_KEYBOARD_5_C2_VC, GRP_LEFT_KEYBOARD_6_C2_VC,
					GRP_LEFT_KEYBOARD_OPS_C2_VC, GRP_LEFT_KEYBOARD_7_C2_VC, GRP_LEFT_KEYBOARD_8_C2_VC, GRP_LEFT_KEYBOARD_9_C2_VC,
					GRP_LEFT_KEYBOARD_SPEC_C2_VC, GRP_LEFT_KEYBOARD_MINUS_C2_VC, GRP_LEFT_KEYBOARD_0_C2_VC, GRP_LEFT_KEYBOARD_PLUS_C2_VC,
					GRP_LEFT_KEYBOARD_RESUME_C2_VC, GRP_LEFT_KEYBOARD_CLEAR_C2_VC, GRP_LEFT_KEYBOARD_DOT_C2_VC, GRP_LEFT_KEYBOARD_PRO_C2_VC};
		pKeyboardCDR->DefineGroup( LeftKeyboardGrp );
		pKeyboardCDR->SetDirection( -panel_normal );
		pKeyboardCDR->SetMouseRegion( AID_C2, 0.046853f, 0.112680f, 0.205339f, 0.887220f );

		UINT RightKeyboardGrp[32] = {GRP_RIGHT_KEYBOARD_FAULTSUMM_C2_VC, GRP_RIGHT_KEYBOARD_SYSSUMM_C2_VC, GRP_RIGHT_KEYBOARD_MSGRESET_C2_VC, GRP_RIGHT_KEYBOARD_ACK_C2_VC,
					GRP_RIGHT_KEYBOARD_GPCCRT_C2_VC, GRP_RIGHT_KEYBOARD_A_C2_VC, GRP_RIGHT_KEYBOARD_B_C2_VC, GRP_RIGHT_KEYBOARD_C_C2_VC,
					GRP_RIGHT_KEYBOARD_IORESET_C2_VC, GRP_RIGHT_KEYBOARD_D_C2_VC, GRP_RIGHT_KEYBOARD_E_C2_VC, GRP_RIGHT_KEYBOARD_F_C2_VC,
					GRP_RIGHT_KEYBOARD_ITEM_C2_VC, GRP_RIGHT_KEYBOARD_1_C2_VC, GRP_RIGHT_KEYBOARD_2_C2_VC, GRP_RIGHT_KEYBOARD_3_C2_VC,
					GRP_RIGHT_KEYBOARD_EXEC_C2_VC, GRP_RIGHT_KEYBOARD_4_C2_VC, GRP_RIGHT_KEYBOARD_5_C2_VC, GRP_RIGHT_KEYBOARD_6_C2_VC,
					GRP_RIGHT_KEYBOARD_OPS_C2_VC, GRP_RIGHT_KEYBOARD_7_C2_VC, GRP_RIGHT_KEYBOARD_8_C2_VC, GRP_RIGHT_KEYBOARD_9_C2_VC,
					GRP_RIGHT_KEYBOARD_SPEC_C2_VC, GRP_RIGHT_KEYBOARD_MINUS_C2_VC, GRP_RIGHT_KEYBOARD_0_C2_VC, GRP_RIGHT_KEYBOARD_PLUS_C2_VC,
					GRP_RIGHT_KEYBOARD_RESUME_C2_VC, GRP_RIGHT_KEYBOARD_CLEAR_C2_VC, GRP_RIGHT_KEYBOARD_DOT_C2_VC, GRP_RIGHT_KEYBOARD_PRO_C2_VC};
		pKeyboardPLT->DefineGroup( RightKeyboardGrp );
		pKeyboardPLT->SetDirection( -panel_normal );
		pKeyboardPLT->SetMouseRegion( AID_C2, 0.804448f, 0.112728f, 0.962729f, 0.886002f );


		pIDPCRTPower[0]->SetInitialAnimState( 0.5f );
		pIDPCRTPower[0]->DefineGroup( GRP_S1_C2_VC );
		pIDPCRTPower[0]->SetReference( _V( -0.108535, 1.89351, 14.4998 ), switch_rot );
		pIDPCRTPower[0]->SetMouseRegion( AID_C2, 0.296761f, 0.208225f, 0.334044f, 0.289804f );

		pIDPCRTPower[1]->SetInitialAnimState( 0.5f );
		pIDPCRTPower[1]->DefineGroup( GRP_S5_C2_VC );
		pIDPCRTPower[1]->SetReference( _V( 0.067066, 1.89351, 14.4998 ), switch_rot );
		pIDPCRTPower[1]->SetMouseRegion( AID_C2, 0.619269f, 0.206317f, 0.659321f, 0.292330f );

		pIDPCRTPower[2]->SetInitialAnimState( 0.5f );
		pIDPCRTPower[2]->DefineGroup( GRP_S3_C2_VC );
		pIDPCRTPower[2]->SetReference( _V( -0.020736, 1.89351, 14.4998 ), switch_rot );
		pIDPCRTPower[2]->SetMouseRegion( AID_C2, 0.458900f, 0.202660f, 0.497793f, 0.293795f );


		pIDPCRTMajFunc[0]->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc[0]->DefineGroup( GRP_S2_C2_VC );
		pIDPCRTMajFunc[0]->SetReference( _V( -0.07677, 1.89351, 14.4998 ), switch_rot );
		pIDPCRTMajFunc[0]->SetMouseRegion( AID_C2, 0.356281f, 0.207470f, 0.393134f, 0.289192f );

		pIDPCRTMajFunc[1]->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc[1]->DefineGroup( GRP_S6_C2_VC );
		pIDPCRTMajFunc[1]->SetReference( _V( 0.098475, 1.89351, 14.4998 ), switch_rot );
		pIDPCRTMajFunc[1]->SetMouseRegion( AID_C2, 0.676943f, 0.203528f, 0.718622f, 0.288572f );

		pIDPCRTMajFunc[2]->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc[2]->DefineGroup( GRP_S4_C2_VC );
		pIDPCRTMajFunc[2]->SetReference( _V( 0.011032, 1.89351, 14.4998 ), switch_rot );
		pIDPCRTMajFunc[2]->SetMouseRegion( AID_C2, 0.516817f, 0.204748f, 0.556571f, 0.293073f );


		pCRTSEL[0]->SetInitialAnimState( 0.5f );
		pCRTSEL[0]->DefineGroup( GRP_S7_C2_VC );
		pCRTSEL[0]->SetReference( _V( -0.09558, 1.85147, 14.4588 ), switch_rotH );
		pCRTSEL[0]->SetMouseRegion( AID_C2, 0.310240f, 0.434606f, 0.349249f, 0.536571f );
		pCRTSEL[0]->SetOrientation( true );


		pCRTSEL[1]->SetInitialAnimState( 0.5f );
		pCRTSEL[1]->DefineGroup( GRP_S8_C2_VC );
		pCRTSEL[1]->SetReference( _V( 0.104779, 1.85147, 14.4588 ), switch_rotH );
		pCRTSEL[1]->SetMouseRegion( AID_C2, 0.677758f, 0.439625f, 0.716074f, 0.535465f );
		pCRTSEL[1]->SetOrientation( true );


		pEventTimerMode->SetInitialAnimState( 0.5f );
		pEventTimerMode->DefineGroup( GRP_S9_C2_VC );
		pEventTimerMode->SetReference( _V( -0.102515, 1.81033, 14.4203 ), switch_rot );
		pEventTimerMode->SetMouseRegion( AID_C2, 0.306191f, 0.710797f, 0.346899f, 0.804266f );
		pEventTimerMode->SetSpringLoaded( true, 0 );

		pEventTimerControl->SetInitialAnimState( 0.5f );
		pEventTimerControl->DefineGroup( GRP_S10_C2_VC );
		pEventTimerControl->SetReference( _V( -0.072689, 1.81033, 14.4203 ), switch_rot );
		pEventTimerControl->SetMouseRegion( AID_C2, 0.362454f, 0.715464f, 0.402753f, 0.799829f );
		pEventTimerControl->SetSpringLoaded( true, 0 );
		pEventTimerControl->SetSpringLoaded( true, 2 );

		pTimer->SetInitialAnimState( 0.5f );
		pTimer->DefineGroup( GRP_S12_C2_VC );
		pTimer->SetReference( _V( 0.098572, 1.81033, 14.4203 ), switch_rot );
		pTimer->SetMouseRegion( AID_C2, 0.676663f, 0.714185f, 0.718559f, 0.801454f );
		pTimer->SetSpringLoaded( true, 0 );
		pTimer->SetSpringLoaded( true, 2 );
		return;
	}

	void PanelC2::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_C2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_C2,
			_V( -0.273643, 1.93304, 14.5383 ) + ofs, _V( 0.268635, 1.93304, 14.5383 ) + ofs,
			_V( -0.273643, 1.77029, 14.3829 ) + ofs, _V( 0.268635, 1.77029, 14.3829 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		SURFHANDLE digittex = oapiGetTextureHandle( GetVCMeshHandle(), TEX_SSV_OV_CLOCKNUMS_C2_VC );
		oapiVCRegisterArea( AID_C2_WND0, _R( 0, 0, 63, 63 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		oapiVCRegisterArea( AID_C2_WND1, _R( 64, 0, 127, 63 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		oapiVCRegisterArea( AID_C2_WND2, _R( 128, 0, 191, 63 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		oapiVCRegisterArea( AID_C2_WND3, _R( 192, 0, 255, 63 ), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_CURRENT, digittex );
		return;
	}

	void PanelC2::DefineVCAnimations( UINT vcidx )
	{
		static VECTOR3 wheel_rot = {1.0, 0, 0};
		static VECTOR3 wheel_pos = _V( 0.0, 1.815664, 14.438313 );

		static UINT VC_C2Evt10MW_Grp = GRP_S11_THUMBWHEEL1_C2_VC;

		VC_C2Evt10MW = new MGROUP_ROTATE( GetVCMeshIndex(), &VC_C2Evt10MW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_C2Wheel[0]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_C2Wheel[0], 0, 1, VC_C2Evt10MW);

		static UINT VC_C2Evt1MW_Grp = GRP_S11_THUMBWHEEL2_C2_VC;

		VC_C2Evt1MW = new MGROUP_ROTATE( GetVCMeshIndex(), &VC_C2Evt1MW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_C2Wheel[1]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_C2Wheel[1], 0, 1, VC_C2Evt1MW);

		static UINT VC_C2Evt10SW_Grp = GRP_S11_THUMBWHEEL3_C2_VC;

		VC_C2Evt10SW = new MGROUP_ROTATE( GetVCMeshIndex(), &VC_C2Evt10SW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_C2Wheel[2]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_C2Wheel[2], 0, 1, VC_C2Evt10SW);

		static UINT VC_C2Evt1SW_Grp = GRP_S11_THUMBWHEEL4_C2_VC;

		VC_C2Evt1SW = new MGROUP_ROTATE( GetVCMeshIndex(), &VC_C2Evt1SW_Grp, 1,
			wheel_pos, wheel_rot, (float)(360.0*RAD));
		anim_VC_C2Wheel[3]=STS()->CreateAnimation (0.0);
		STS()->AddAnimationComponent (anim_VC_C2Wheel[3], 0, 1, VC_C2Evt1SW);

		AtlantisPanel::DefineVCAnimations( vcidx );
		return;
	}

	void PanelC2::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "C2_A12A1_A12A2_IDP", 14 );
		pIDPCRTPower[0]->ConnectPort( 1, pBundle, 0 );
		pIDPCRTPower[1]->ConnectPort( 1, pBundle, 1 );
		pIDPCRTPower[2]->ConnectPort( 1, pBundle, 2 );

		pIDPCRTMajFunc[0]->ConnectPort( 0, pBundle, 4 );
		pIDPCRTMajFunc[1]->ConnectPort( 0, pBundle, 5 );
		pIDPCRTMajFunc[2]->ConnectPort( 0, pBundle, 6 );

		pIDPCRTMajFunc[0]->ConnectPort( 2, pBundle, 8 );
		pIDPCRTMajFunc[1]->ConnectPort( 2, pBundle, 9 );
		pIDPCRTMajFunc[2]->ConnectPort( 2, pBundle, 10 );

		pCRTSEL[0]->ConnectPort( 1, pBundle, 12 );
		pCRTSEL[1]->ConnectPort( 1, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdEventTimer_A", 16 );
		pEventTimerMode->ConnectPort( 0, pBundle, 0 );
		pEventTimerMode->ConnectPort( 2, pBundle, 1 );
		pEventTimerControl->ConnectPort( 0, pBundle, 2 );
		pEventTimerControl->ConnectPort( 2, pBundle, 3 );
		pTimer->ConnectPort( 0, pBundle, 4 );
		pTimer->ConnectPort( 2, pBundle, 5 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdEventTimer_B", 16 );
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

		pKeyboardCDR->ConnectIDP( 0, STS()->GetIDP( 1 ) );
		pKeyboardCDR->ConnectIDP( 1, STS()->GetIDP( 3 ) );

		pKeyboardPLT->ConnectIDP( 0, STS()->GetIDP( 3 ) );
		pKeyboardPLT->ConnectIDP( 1, STS()->GetIDP( 2 ) );

		AtlantisPanel::Realize();
		return;
	}
};
