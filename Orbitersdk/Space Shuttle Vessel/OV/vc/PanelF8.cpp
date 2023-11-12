/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
2022/10/04   GLS
2023/05/12   GLS
2023/06/03   GLS
2023/11/11   GLS
********************************************/
#include "PanelF8.h"
#include "MDU.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "PushButtonIndicator.h"
#include "StandardSwitchCover.h"
#include "RotarySwitchPotentiometer.h"
#include "../Atlantis.h"
#include "../meshres_vc.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_f8.h"


namespace vc {

	PanelF8::PanelF8( Atlantis* _sts, BusManager* pBusManager )
		: AtlantisPanel(_sts, "F8")
	{
		DefineMesh( MESHNAME_PANELF8 );

		Add( pPLT1 = new MDU( _sts, "PLT1", MDUID_PLT1, pBusManager) );
		Add( pPLT2 = new MDU( _sts, "PLT2", MDUID_PLT2, pBusManager) );

		Add( pFltCntlrPower = new LockableLever2( _sts, "FLT CNTLR POWER" ) );
		pFltCntlrPower->SetLabel( 0, "OFF" );
		pFltCntlrPower->SetLabel( 1, "ON" );

		Add( pHSISelectMode = new StdSwitch3( _sts, "HSI SELECT MODE" ) );
		pHSISelectMode->SetLabel( 0, "APPROACH" );
		pHSISelectMode->SetLabel( 1, "TAEM" );
		pHSISelectMode->SetLabel( 2, "ENTRY" );

		Add( pHSISelectSource = new StdSwitch3( _sts, "HSI SELECT SOURCE" ) );
		pHSISelectSource->SetLabel( 0, "MLS" );
		pHSISelectSource->SetLabel( 1, "NAV" );
		pHSISelectSource->SetLabel( 2, "GPS" );

		Add( pHSISelectChannel = new StdSwitch3( _sts, "HSI SELECT CHANNEL" ) );
		pHSISelectChannel->SetLabel( 0, "3" );
		pHSISelectChannel->SetLabel( 1, "2" );
		pHSISelectChannel->SetLabel( 2, "1" );

		Add( pADIAttitude = new StdSwitch3( _sts, "ADI ATTITUDE" ) );
		pADIAttitude->SetLabel( 0, "REF" );
		pADIAttitude->SetLabel( 1, "LVLH" );
		pADIAttitude->SetLabel( 2, "INRTL" );

		Add( pADIError = new StdSwitch3( _sts, "ADI ERROR" ) );
		pADIError->SetLabel( 0, "LOW" );
		pADIError->SetLabel( 1, "MED" );
		pADIError->SetLabel( 2, "HIGH" );

		Add( pADIRate = new StdSwitch3( _sts, "ADI RATE" ) );
		pADIRate->SetLabel( 0, "LOW" );
		pADIRate->SetLabel( 1, "MED" );
		pADIRate->SetLabel( 2, "HIGH" );

		Add( pAttRef = new PushButton( _sts, "ATT REF" ) );

		Add( pLandingGearTB[0] = new StandardTalkback3( _sts, "LANDING GEAR NOSE" ) );
		Add( pLandingGearTB[1] = new StandardTalkback3( _sts, "LANDING GEAR LEFT" ) );
		Add( pLandingGearTB[2] = new StandardTalkback3( _sts, "LANDING GEAR RIGHT" ) );

		Add( pLandingGearArmDeployCover[0] = new StandardSwitchCover( _sts, "LANDING GEAR ARM COVER" ) );
		Add( pLandingGearArmDeployCover[1] = new StandardSwitchCover( _sts, "LANDING GEAR DN COVER" ) );

		Add( pLandingGearArmDeploy[0] = new PushButtonIndicatorSingleLight( _sts, "LANDING GEAR ARM" ) );
		Add( pLandingGearArmDeploy[1] = new PushButtonIndicatorSingleLight( _sts, "LANDING GEAR DN" ) );

		Add( pHUDMode = new StdSwitch3( _sts, "HUD MODE" ) );
		pHUDMode->SetLabel( 0, "DCLT" );
		pHUDMode->SetLabel( 1, "NORM" );
		pHUDMode->SetLabel( 2, "TEST" );
		pHUDMode->SetSpringLoaded( true, 0 );

		Add( pHUDBrightness = new RotarySwitchPotentiometer( _sts, "HUD BRIGHTNESS" ) );

		Add( pHUDBright = new StdSwitch3( _sts, "HUD BRIGHT" ) );
		pHUDBright->SetLabel( 0, "MAN NIGHT" );
		pHUDBright->SetLabel( 1, "AUTO" );
		pHUDBright->SetLabel( 2, "MAN DAY" );

		Add( pRDRALTM = new StdSwitch2( _sts, "RDR ALTM" ) );
		pRDRALTM->SetLabel( 0, "2" );
		pRDRALTM->SetLabel( 1, "1" );
		pRDRALTM->SetInitialPosition( 0 );
	}

	PanelF8::~PanelF8()
	{
	}

	void PanelF8::DefineVC()
	{
		VECTOR3 switch_rot = _V(1, 0, 0);
		VECTOR3 push_dir = _V( 0.0, -0.258681, 0.965963 );
		VECTOR3 pull_dir = -push_dir;

		AddAIDToMouseEventList( AID_F8 );
		AddAIDToMouseEventList( AID_F8_MDU );
		AddAIDToMouseEventList( AID_F8_HUD );

		pPLT1->DefineVCGroup( GRP_PLT1_F8_VC );
		pPLT1->DefineMaterial( MAT_MDU_PLT1_F8_VC );
		pPLT1->SetMouseRegion( AID_F8_MDU, 0.0f, 0.0f, 0.489801f, 1.0f );

		pPLT2->DefineVCGroup( GRP_PLT2_F8_VC );
		pPLT2->DefineMaterial( MAT_MDU_PLT2_F8_VC );
		pPLT2->SetMouseRegion( AID_F8_MDU, 0.509333f, 0.0f, 1.0f, 1.0f );

		pFltCntlrPower->DefineGroup(GRP_SWITCH5_F8_VC);
		pFltCntlrPower->SetInitialAnimState(0.5);
		pFltCntlrPower->SetReference(_V(-0.734, 1.99, 14.685), switch_rot);
		pFltCntlrPower->SetMouseRegion( AID_F8, 0.379877f, 0.609586f, 0.422314f, 0.793425f );
		pFltCntlrPower->SetPullDirection( pull_dir );

		pHSISelectMode->DefineGroup( GRP_SWITCH1_F8_VC );
		pHSISelectMode->SetInitialAnimState( 0.5 );
		pHSISelectMode->SetReference( _V( 0.0, 2.04708, 14.700552 ), switch_rot );
		pHSISelectMode->SetMouseRegion( AID_F8, 0.263435f, 0.179901f, 0.306003f, 0.352800f );

		pHSISelectSource->DefineGroup( GRP_SWITCH2_F8_VC );
		pHSISelectSource->SetInitialAnimState( 0.5 );
		pHSISelectSource->SetReference( _V( 0.0, 2.04708, 14.700552 ), switch_rot );
		pHSISelectSource->SetMouseRegion( AID_F8, 0.342672f, 0.179901f, 0.389420f, 0.352800f );

		pHSISelectChannel->DefineGroup( GRP_SWITCH3_F8_VC );
		pHSISelectChannel->SetInitialAnimState( 0.5 );
		pHSISelectChannel->SetReference( _V( 0.0, 2.04708, 14.700552 ), switch_rot );
		pHSISelectChannel->SetMouseRegion( AID_F8, 0.398481f, 0.179901f, 0.439808f, 0.352800f );

		pADIAttitude->DefineGroup( GRP_SWITCH6_F8_VC );
		pADIAttitude->SetInitialAnimState( 0.5 );
		pADIAttitude->SetReference( _V( -0.633, 2.045, 14.7004 ), switch_rot );
		pADIAttitude->SetMouseRegion( AID_F8, 0.573540f, 0.180482f, 0.616687f, 0.353228f );

		pADIError->DefineGroup( GRP_SWITCH7_F8_VC );
		pADIError->SetInitialAnimState( 0.5 );
		pADIError->SetReference( _V( -0.5921, 2.0469, 14.7009 ), switch_rot );
		pADIError->SetMouseRegion( AID_F8, 0.652143f, 0.174853f, 0.699142f, 0.359075f );

		pADIRate->DefineGroup( GRP_SWITCH8_F8_VC );
		pADIRate->SetInitialAnimState( 0.5 );
		pADIRate->SetReference( _V( -0.5627, 2.0463, 14.7008 ), switch_rot );
		pADIRate->SetMouseRegion( AID_F8, 0.708632f, 0.178725f, 0.750834f, 0.350277f );

		pAttRef->SetMouseRegion( AID_F8, 0.571036f, 0.624760f, 0.618915f, 0.818711f );
		pAttRef->SetDirection( push_dir );
		pAttRef->DefineGroup( GRP_BUTTON3_F8_VC );

		pLandingGearTB[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_F8_VC );

		pLandingGearTB[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_F8_VC );

		pLandingGearTB[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS3_F8_VC );

		pLandingGearArmDeployCover[0]->SetMouseRegion( AID_F8, 0, 0.052979f, 0.513634f, 0.120368f, 0.740271f );
		pLandingGearArmDeployCover[0]->SetMouseRegion( AID_F8, 1, 0.049178f, 0.511376f, 0.065602f, 0.734235f );
		pLandingGearArmDeployCover[0]->SetReference( _V( 0.444, 1.99996, 14.68735 ), _V( 0, 0.965408, 0.260745 ) );
		pLandingGearArmDeployCover[0]->DefineGroup( GRP_A5_COVER1_F8_VC );

		pLandingGearArmDeployCover[1]->SetMouseRegion( AID_F8, 0, 0.142077f, 0.513883f, 0.210356f, 0.740062f );
		pLandingGearArmDeployCover[1]->SetMouseRegion( AID_F8, 1, 0.139839f, 0.516023f, 0.154470f, 0.733397f );
		pLandingGearArmDeployCover[1]->SetReference( _V( 0.4913, 1.99996, 14.68735 ), _V( 0, 0.965408, 0.260745 ) );
		pLandingGearArmDeployCover[1]->DefineGroup( GRP_A5_COVER2_F8_VC );

		pLandingGearArmDeploy[0]->SetStateOffset( 1, 0.0f, 0.488281f );
		pLandingGearArmDeploy[0]->SetDirection( push_dir );
		pLandingGearArmDeploy[0]->SetMouseRegion( AID_F8, 0.072426f, 0.551969f, 0.114127f, 0.720267f );
		pLandingGearArmDeploy[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_A5_S1_F8_VC );

		pLandingGearArmDeploy[1]->SetStateOffset( 1, 0.0f, 0.488281f );
		pLandingGearArmDeploy[1]->SetDirection( push_dir );
		pLandingGearArmDeploy[1]->SetMouseRegion( AID_F8, 0.160673f, 0.552534f, 0.201274f, 0.716342f );
		pLandingGearArmDeploy[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_A5_S2_F8_VC );

		pHUDMode->DefineGroup( GRP_HUDTEST_F8_VC );
		pHUDMode->SetInitialAnimState( 0.5 );
		pHUDMode->SetReference( _V( -0.5996, 2.4685, 14.5712 ), _V( 1, 0, 0 ) );
		pHUDMode->SetMouseRegion( AID_F8_HUD, 0.042951f, 0.399852f, 0.177495f, 0.643278f );

		pHUDBrightness->DefineGroup( GRP_HUDDIM_F8_VC );
		pHUDBrightness->SetInitialAnimState( 0.5 );
		pHUDBrightness->SetReference( _V( 0.6496, 2.4697, 14.5635 ), _V( 0, 0.275637, -0.961262 ) );
		pHUDBrightness->SetAngleRange( 180.0 );
		pHUDBrightness->SetMouseRegion( AID_F8_HUD, 0.390848f, 0.343682f, 0.605650f, 0.723217f );

		pHUDBright->DefineGroup( GRP_HUDBRT_F8_VC );
		pHUDBright->SetInitialAnimState( 0.5 );
		pHUDBright->SetReference( _V( -0.7070, 2.4680, 14.5712 ), _V( 1, 0, 0 ) );
		pHUDBright->SetMouseRegion( AID_F8_HUD, 0.810735f, 0.390512f, 0.943742f, 0.641940f );

		pRDRALTM->DefineGroup( GRP_SWITCH4_F8_VC );
		pRDRALTM->SetInitialAnimState( 0.5 );
		pRDRALTM->SetReference( _V( 0.59147, 1.99117, 14.6857 ), _V( 1, 0, 0 ) );
		pRDRALTM->SetMouseRegion( AID_F8, 0.322341f, 0.613130f, 0.370220f, 0.787155f );
	}

	void PanelF8::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_F8, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F8,
			_V( 0.4187, 2.0814, 14.7091 ) + ofs, _V( 0.9412, 2.0814, 14.7091 ) + ofs,
			_V( 0.4187, 1.9513, 14.6745 ) + ofs, _V( 0.9412, 1.9513, 14.6745 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCRegisterArea( AID_F8_MDU, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F8_MDU,
			_V( 0.4227, 2.3119, 14.7565 ) + ofs, _V( 0.9362, 2.3119, 14.7565 ) + ofs,
			_V( 0.4227, 2.0984, 14.6968 ) + ofs, _V( 0.9362, 2.0984, 14.6968 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCRegisterArea( AID_F8_HUD, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F8_HUD,
			_V( 0.5799, 2.5083, 14.5803 ) + ofs, _V( 0.7200, 2.5083, 14.5803 ) + ofs,
			_V( 0.5799, 2.4325, 14.5593 ) + ofs, _V( 0.7200, 2.4325, 14.5593 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelF8::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "DDU_POWER", 16 );
		pFltCntlrPower->ConnectPort( 1, pBundle, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF2_IOM4_CH1", 16 );
		pADIAttitude->ConnectPort( 2, pBundle, 0 );// INRTL
		pADIAttitude->ConnectPort( 1, pBundle, 1 );// LVLH
		pADIAttitude->ConnectPort( 0, pBundle, 2 );// REF
		pADIRate->ConnectPort( 2, pBundle, 3 );// HIGH
		pADIRate->ConnectPort( 1, pBundle, 4 );// MED
		pADIRate->ConnectPort( 0, pBundle, 5 );// LOW
		pADIError->ConnectPort( 2, pBundle, 6 );// HIGH
		pADIError->ConnectPort( 1, pBundle, 7 );// MED
		pADIError->ConnectPort( 0, pBundle, 8 );// LOW

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF2_IOM12_CH0", 16 );
		pRDRALTM->ConnectPort( 1, pBundle, 13 );// PLT RDR ALTM 1
		pRDRALTM->ConnectPort( 0, pBundle, 14 );// PLT RDR ALTM 2
		pHSISelectSource->ConnectPort( 0, pBundle, 15 );// MLS

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF2_IOM12_CH1", 16 );
		pHSISelectSource->ConnectPort( 1, pBundle, 0 );// NAV
		pHSISelectSource->ConnectPort( 2, pBundle, 1 );// GPS
		pHSISelectMode->ConnectPort( 0, pBundle, 2 );// APPROACH
		pHSISelectMode->ConnectPort( 1, pBundle, 3 );// TAEM
		pHSISelectMode->ConnectPort( 2, pBundle, 4 );// ENTRY
		pHSISelectChannel->ConnectPort( 0, pBundle, 5 );// 3
		pHSISelectChannel->ConnectPort( 1, pBundle, 6 );// 2
		pHSISelectChannel->ConnectPort( 2, pBundle, 7 );// 1

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF2_IOM12_CH2", 16 );
		pAttRef->Connect( 0, pBundle, 6 );// ATT REF A
		pAttRef->Connect( 1, pBundle, 7 );// ATT REF B

		pBundle = STS()->BundleManager()->CreateBundle( "LANDING_GEAR", 16 );
		pLandingGearArmDeploy[0]->ConnectPushButton( pBundle, 1 );// arm pb
		pLandingGearArmDeploy[1]->ConnectPushButton( pBundle, 3 );// dn pb
		pLandingGearTB[0]->SetInput( 0, pBundle, 5, TB_UP );
		pLandingGearTB[0]->SetInput( 1, pBundle, 6, TB_DN );
		pLandingGearTB[1]->SetInput( 0, pBundle, 7, TB_UP );
		pLandingGearTB[1]->SetInput( 1, pBundle, 8, TB_DN );
		pLandingGearTB[2]->SetInput( 0, pBundle, 9, TB_UP );
		pLandingGearTB[2]->SetInput( 1, pBundle, 10, TB_DN );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_5", 16 );
		pLandingGearArmDeploy[0]->ConnectLight( 0, pBundle, 7 );// arm light
		pLandingGearArmDeploy[1]->ConnectLight( 0, pBundle, 15 );// dn light

		pBundle = STS()->BundleManager()->CreateBundle( "HUD_SWITCHES", 16 );
		// power plt
		pHUDMode->ConnectPort( 0, pBundle, 9 );// mode dclt plt
		// TODO mode norm plt
		pHUDMode->ConnectPort( 2, pBundle, 11 );// mode test plt
		pHUDBrightness->Connect( pBundle, 12 );// brightness plt
		pHUDBright->ConnectPort( 0, pBundle, 13 );// bright man night plt
		// TODO bright auto plt
		pHUDBright->ConnectPort( 2, pBundle, 15 );// bright man day plt

		AtlantisPanel::Realize();
	}

}
