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
2022/04/27   GLS
2022/04/28   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/06   GLS
2022/09/08   GLS
2022/09/10   GLS
2022/09/29   GLS
********************************************/
#include "PanelC2.h"
#include "StandardSwitch.h"
#include "Keyboard.h"
#include "ThumbWheel.h"
#include "PushWheel.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_c2.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelC2";
	constexpr VECTOR3 OFFSET_PANEL = {-0.273686, 1.77029, 14.3829};


	PanelC2::PanelC2( Atlantis* _sts, const std::string &orbiter ):AtlantisPanel( _sts, "C2" )
	{
		if ((orbiter == "Discovery") || (orbiter == "Endeavour")) thumbwheels = false;
		else thumbwheels = true;

		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pKeyboardCDR = new Keyboard( _sts, "LH KEYBOARD", 1 ) );
		Add( pKeyboardPLT = new Keyboard( _sts, "RH KEYBOARD", 2 ) );

		Add( pIDPCRTPower[0] = new StdSwitch2( _sts, "IDP/CRT 1 POWER" ) );
		pIDPCRTPower[0]->SetLabel( 0, "OFF" );
		pIDPCRTPower[0]->SetLabel( 1, "ON" );
		pIDPCRTPower[0]->SetInitialPosition( 1 );
		Add( pIDPCRTPower[1] = new StdSwitch2( _sts, "IDP/CRT 2 POWER" ) );
		pIDPCRTPower[1]->SetLabel( 0, "OFF" );
		pIDPCRTPower[1]->SetLabel( 1, "ON" );
		pIDPCRTPower[1]->SetInitialPosition( 1 );
		Add( pIDPCRTPower[2] = new StdSwitch2( _sts, "IDP/CRT 3 POWER" ) );
		pIDPCRTPower[2]->SetLabel( 0, "OFF" );
		pIDPCRTPower[2]->SetLabel( 1, "ON" );
		pIDPCRTPower[2]->SetInitialPosition( 1 );

		Add( pIDPCRTMajFunc[0] = new StdSwitch3( _sts, "IDP/CRT 1 MAJ FUNC" ) );
		pIDPCRTMajFunc[0]->SetLabel( 0, "PL" );
		pIDPCRTMajFunc[0]->SetLabel( 1, "SM" );
		pIDPCRTMajFunc[0]->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc[0]->SetInitialPosition( 2 );
		Add( pIDPCRTMajFunc[1] = new StdSwitch3( _sts, "IDP/CRT 2 MAJ FUNC" ) );
		pIDPCRTMajFunc[1]->SetLabel( 0, "PL" );
		pIDPCRTMajFunc[1]->SetLabel( 1, "SM" );
		pIDPCRTMajFunc[1]->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc[1]->SetInitialPosition( 2 );
		Add( pIDPCRTMajFunc[2] = new StdSwitch3( _sts, "IDP/CRT 3 MAJ FUNC" ) );
		pIDPCRTMajFunc[2]->SetLabel( 0, "PL" );
		pIDPCRTMajFunc[2]->SetLabel( 1, "SM" );
		pIDPCRTMajFunc[2]->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc[2]->SetInitialPosition( 2 );

		Add( pCRTSEL[0] = new StdSwitch2( _sts, "LEFT IDP/CRT SEL" ) );
		pCRTSEL[0]->SetLabel( 0, "3" );
		pCRTSEL[0]->SetLabel( 1, "1" );
		pCRTSEL[0]->SetInitialPosition( 1 );
		Add( pCRTSEL[1] = new StdSwitch2( _sts, "RIGHT IDP/CRT SEL" ) );
		pCRTSEL[1]->SetLabel( 0, "2" );
		pCRTSEL[1]->SetLabel( 1, "3" );

		Add( pEventTimerMode = new StdSwitch3( _sts, "EVENT TIMER MODE" ) );
		pEventTimerMode->SetLabel( 0, "TEST" );
		pEventTimerMode->SetLabel( 1, "DOWN" );
		pEventTimerMode->SetLabel( 2, "UP" );

		Add( pEventTimerControl = new StdSwitch3( _sts, "EVENT TIMER CONTROL" ) );
		pEventTimerControl->SetLabel( 0, "STOP" );
		pEventTimerControl->SetLabel( 1, "-" );
		pEventTimerControl->SetLabel( 2, "START" );

		Add( pTimer = new StdSwitch3( _sts, "EVENT TIMER TIMER" ) );
		pTimer->SetLabel( 0, "RESET" );
		pTimer->SetLabel( 1, "-" );
		pTimer->SetLabel( 2, "SET" );

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

	PanelC2::~PanelC2()
	{
	}

	void PanelC2::DefineVC()
	{
		const VECTOR3 switch_rot = _V( 1.0, 0.0, 0.0 );
		const VECTOR3 switch_rotH = _V( 0.0, 0.707107, 0.707107 );
		const VECTOR3 panel_normal = _V( 0.0, 0.723051, -0.690795 );

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
		pIDPCRTPower[0]->SetReference( _V( 0.0, 0.12322, 0.1169 ), switch_rot );
		pIDPCRTPower[0]->SetMouseRegion( AID_C2, 0.296761f, 0.208225f, 0.334044f, 0.289804f );

		pIDPCRTPower[1]->SetInitialAnimState( 0.5f );
		pIDPCRTPower[1]->DefineGroup( GRP_S5_C2_VC );
		pIDPCRTPower[1]->SetReference( _V( 0.0, 0.12322, 0.1169 ), switch_rot );
		pIDPCRTPower[1]->SetMouseRegion( AID_C2, 0.619269f, 0.206317f, 0.659321f, 0.292330f );

		pIDPCRTPower[2]->SetInitialAnimState( 0.5f );
		pIDPCRTPower[2]->DefineGroup( GRP_S3_C2_VC );
		pIDPCRTPower[2]->SetReference( _V( 0.0, 0.12322, 0.1169 ), switch_rot );
		pIDPCRTPower[2]->SetMouseRegion( AID_C2, 0.458900f, 0.202660f, 0.497793f, 0.293795f );


		pIDPCRTMajFunc[0]->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc[0]->DefineGroup( GRP_S2_C2_VC );
		pIDPCRTMajFunc[0]->SetReference( _V( 0.0, 0.12322, 0.1169 ), switch_rot );
		pIDPCRTMajFunc[0]->SetMouseRegion( AID_C2, 0.356281f, 0.207470f, 0.393134f, 0.289192f );

		pIDPCRTMajFunc[1]->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc[1]->DefineGroup( GRP_S6_C2_VC );
		pIDPCRTMajFunc[1]->SetReference( _V( 0.0, 0.12322, 0.1169 ), switch_rot );
		pIDPCRTMajFunc[1]->SetMouseRegion( AID_C2, 0.676943f, 0.203528f, 0.718622f, 0.288572f );

		pIDPCRTMajFunc[2]->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc[2]->DefineGroup( GRP_S4_C2_VC );
		pIDPCRTMajFunc[2]->SetReference( _V( 0.0, 0.12322, 0.1169 ), switch_rot );
		pIDPCRTMajFunc[2]->SetMouseRegion( AID_C2, 0.516817f, 0.204748f, 0.556571f, 0.293073f );


		pCRTSEL[0]->SetInitialAnimState( 0.5f );
		pCRTSEL[0]->DefineGroup( GRP_S7_C2_VC );
		pCRTSEL[0]->SetReference( _V( 0.178106, 0.08118, 0.0759 ), switch_rotH );
		pCRTSEL[0]->SetMouseRegion( AID_C2, 0.310240f, 0.434606f, 0.349249f, 0.536571f );
		pCRTSEL[0]->SetOrientation( true );


		pCRTSEL[1]->SetInitialAnimState( 0.5f );
		pCRTSEL[1]->DefineGroup( GRP_S8_C2_VC );
		pCRTSEL[1]->SetReference( _V( 0.378465, 0.08118, 0.0759 ), switch_rotH );
		pCRTSEL[1]->SetMouseRegion( AID_C2, 0.677758f, 0.439625f, 0.716074f, 0.535465f );
		pCRTSEL[1]->SetOrientation( true );


		pEventTimerMode->SetInitialAnimState( 0.5f );
		pEventTimerMode->DefineGroup( GRP_S9_C2_VC );
		pEventTimerMode->SetReference( _V( 0.0, 0.04004, 0.0374 ), switch_rot );
		pEventTimerMode->SetMouseRegion( AID_C2, 0.306191f, 0.710797f, 0.346899f, 0.804266f );
		pEventTimerMode->SetSpringLoaded( true, 0 );

		pEventTimerControl->SetInitialAnimState( 0.5f );
		pEventTimerControl->DefineGroup( GRP_S10_C2_VC );
		pEventTimerControl->SetReference( _V( 0.0, 0.04004, 0.0374 ), switch_rot );
		pEventTimerControl->SetMouseRegion( AID_C2, 0.362454f, 0.715464f, 0.402753f, 0.799829f );
		pEventTimerControl->SetSpringLoaded( true, 0 );
		pEventTimerControl->SetSpringLoaded( true, 2 );

		pTimer->SetInitialAnimState( 0.5f );
		pTimer->DefineGroup( GRP_S12_C2_VC );
		pTimer->SetReference( _V( 0.0, 0.04004, 0.0374 ), switch_rot );
		pTimer->SetMouseRegion( AID_C2, 0.676663f, 0.714185f, 0.718559f, 0.801454f );
		pTimer->SetSpringLoaded( true, 0 );
		pTimer->SetSpringLoaded( true, 2 );

		pEventTimerMin10->SetBounds( 0, 5 );
		pEventTimerSec10->SetBounds( 0, 5 );
		if (thumbwheels)
		{
			const VECTOR3 pos = _V( 0.0, 0.03628, 0.064811 );

			pEventTimerMin10->DefineWheelGroup( GRP_S11_THUMBWHEEL_10M_C2_VC );
			pEventTimerMin10->SetReference( pos, switch_rot );
			pEventTimerMin10->SetMouseRegion( AID_C2, 0.494937f, 0.616959f, 0.503886f, 0.740783f );

			pEventTimerMin1->DefineWheelGroup( GRP_S11_THUMBWHEEL_1M_C2_VC );
			pEventTimerMin1->SetReference( pos, switch_rot );
			pEventTimerMin1->SetMouseRegion( AID_C2, 0.529472f, 0.618170f, 0.538711f, 0.739843f );

			pEventTimerSec10->DefineWheelGroup( GRP_S11_THUMBWHEEL_10S_C2_VC );
			pEventTimerSec10->SetReference( pos, switch_rot );
			pEventTimerSec10->SetMouseRegion( AID_C2, 0.564201f, 0.617049f, 0.574192f, 0.739046f );

			pEventTimerSec1->DefineWheelGroup( GRP_S11_THUMBWHEEL_1S_C2_VC );
			pEventTimerSec1->SetReference( pos, switch_rot );
			pEventTimerSec1->SetMouseRegion( AID_C2, 0.599850f, 0.616031f, 0.609458f, 0.739695f );
		}
		else
		{
			const VECTOR3 pushbutton_dir = _V( 0.0, -0.6907, 0.72314 );
			const VECTOR3 pos = _V( 0.0, 0.03854, 0.062445 );

			pEventTimerMin10->DefineWheelGroup( GRP_S11_PUSHWHEEL_10M_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin10)->DefinePushButtonGroups( GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_10M_C2_VC, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_10M_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin10)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerMin10->SetReference( pos, switch_rot );
			pEventTimerMin10->SetMouseRegion( AID_C2, 0.483671f, 0.604034f, 0.502917f, 0.770712f );

			pEventTimerMin1->DefineWheelGroup( GRP_S11_PUSHWHEEL_1M_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin1)->DefinePushButtonGroups( GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_1M_C2_VC, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_1M_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerMin1)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerMin1->SetReference( pos, switch_rot );
			pEventTimerMin1->SetMouseRegion( AID_C2, 0.515711f, 0.604034f, 0.536077f, 0.770712f );

			pEventTimerSec10->DefineWheelGroup( GRP_S11_PUSHWHEEL_10S_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec10)->DefinePushButtonGroups( GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_10S_C2_VC, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_10S_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec10)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerSec10->SetReference( pos, switch_rot );
			pEventTimerSec10->SetMouseRegion( AID_C2, 0.552291f, 0.604034f, 0.572616f, 0.770712f );

			pEventTimerSec1->DefineWheelGroup( GRP_S11_PUSHWHEEL_1S_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec1)->DefinePushButtonGroups( GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_1S_C2_VC, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_1S_C2_VC );
			dynamic_cast<PushWheel*>(pEventTimerSec1)->DefinePushButtonDirection( pushbutton_dir );
			pEventTimerSec1->SetReference( pos, switch_rot );
			pEventTimerSec1->SetMouseRegion( AID_C2, 0.587631f, 0.604034f, 0.607934f, 0.770712f );
		}
		return;
	}

	void PanelC2::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_C2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_C2,
			_V( 0.000043, 0.16275, 0.155399 ) + ofs, _V( 0.542334, 0.16275, 0.155399 ) + ofs,
			_V( 0.0, 0.0, 0.0 ) + ofs, _V( 0.542321, 0.0, 0.0 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
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

		pKeyboardCDR->ConnectIDP( 0, STS()->GetIDP( 1 ) );
		pKeyboardCDR->ConnectIDP( 1, STS()->GetIDP( 3 ) );

		pKeyboardPLT->ConnectIDP( 0, STS()->GetIDP( 3 ) );
		pKeyboardPLT->ConnectIDP( 1, STS()->GetIDP( 2 ) );

		AtlantisPanel::Realize();
		return;
	}

	void PanelC2::VisualCreated( void )
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
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_10M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_10S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_1M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_1S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_CASE_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_10M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_10S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_1M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_1S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_10M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_10S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_1M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_1S_C2_VC, &grpSpec );
			}
			else
			{
				oapiEditMeshGroup( hDevMesh, GRP_S11_THUMBWHEEL_10M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_THUMBWHEEL_10S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_THUMBWHEEL_1M_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_THUMBWHEEL_1S_C2_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_THUMBWHEEL_CASE_C2_VC, &grpSpec );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
};
