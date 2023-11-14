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
2023/04/26   GLS
2023/05/12   GLS
2023/06/03   GLS
2023/09/03   GLS
2023/11/11   GLS
********************************************/
#include "PanelF6.h"
#include "MDU.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "PushButtonIndicator.h"
#include "StandardSwitchCover.h"
#include "StandardLight.h"
#include "RotarySwitchPotentiometer.h"
#include "../Atlantis.h"
#include "../meshres_vc.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_f6.h"


namespace vc {

	PanelF6::PanelF6( Atlantis* _sts, BusManager* pBusManager )
		: AtlantisPanel(_sts, "F6")
	{
		DefineMesh( MESHNAME_PANELF6 );

		Add( pCDR1 = new MDU( _sts, "CDR1", MDUID_CDR1, pBusManager ) );
		Add( pCDR2 = new MDU( _sts, "CDR2", MDUID_CDR2, pBusManager ) );

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

		Add( pRCSCommand[0] = new StandardDoubleLight( _sts, "RCS COMMAND ROLL" ) );
		Add( pRCSCommand[1] = new StandardDoubleLight( _sts, "RCS COMMAND PITCH" ) );
		Add( pRCSCommand[2] = new StandardDoubleLight( _sts, "RCS COMMAND YAW" ) );

		Add( pRangeSafeArm = new StandardDoubleLight( _sts, "RANGE SAFE ARM" ) );// using double light because of 4 inputs

		Add( pAbort = new PushButtonIndicatorSingleLight( _sts, "ABORT" ) );

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
		pRDRALTM->SetInitialPosition( 1 );
	}

	PanelF6::~PanelF6()
	{
	}

	void PanelF6::DefineVC()
	{
		VECTOR3 switch_rot = _V(1, 0, 0);
		VECTOR3 push_dir = _V( 0.0, -0.258681, 0.965963 );
		VECTOR3 pull_dir = -push_dir;

		AddAIDToMouseEventList( AID_F6 );
		AddAIDToMouseEventList( AID_F6_MDU );
		AddAIDToMouseEventList( AID_F6_HUD );

		pCDR1->DefineVCGroup( GRP_CDR1_F6_VC );
		pCDR1->DefineMaterial( MAT_MDU_CDR1_F6_VC );
		pCDR1->SetMouseRegion( AID_F6_MDU, 0.0f, 0.0f, 0.490755f, 1.0f );
		pCDR1->DefinePowerButtonGroup( GRP_CDR1_ONOFF_F6_VC );
		pCDR1->SetPowerButtonReference( _V( -0.930388, 2.130294, 14.682689 ), pull_dir );

		pCDR2->DefineVCGroup( GRP_CDR2_F6_VC );
		pCDR2->DefineMaterial( MAT_MDU_CDR2_F6_VC );
		pCDR2->SetMouseRegion( AID_F6_MDU, 0.514292f, 0.0f, 1.0f, 1.0f );
		pCDR2->DefinePowerButtonGroup( GRP_CDR2_ONOFF_F6_VC );
		pCDR2->SetPowerButtonReference( _V( -0.667332, 2.130294, 14.682689 ), pull_dir );

		pFltCntlrPower->DefineGroup(GRP_SWITCH_5_F6_VC);
		pFltCntlrPower->SetInitialAnimState(0.5);
		pFltCntlrPower->SetReference(_V(-0.734, 1.99, 14.685), switch_rot);
		pFltCntlrPower->SetMouseRegion( AID_F6, 0.383447f, 0.622820f, 0.424394f, 0.795206f );
		pFltCntlrPower->SetPullDirection( pull_dir );

		pHSISelectMode->DefineGroup( GRP_SWITCH_1_F6_VC );
		pHSISelectMode->SetInitialAnimState( 0.5 );
		pHSISelectMode->SetReference( _V( 0.0, 2.04624, 14.700701 ), switch_rot );
		pHSISelectMode->SetMouseRegion( AID_F6, 0.266822f, 0.198847f, 0.307091f, 0.357838f );

		pHSISelectSource->DefineGroup( GRP_SWITCH_2_F6_VC );
		pHSISelectSource->SetInitialAnimState( 0.5 );
		pHSISelectSource->SetReference( _V( 0.0, 2.04624, 14.700701 ), switch_rot );
		pHSISelectSource->SetMouseRegion( AID_F6, 0.343734f, 0.198847f, 0.389980f, 0.357838f );

		pHSISelectChannel->DefineGroup( GRP_SWITCH_3_F6_VC );
		pHSISelectChannel->SetInitialAnimState( 0.5 );
		pHSISelectChannel->SetReference( _V( 0.0, 2.04624, 14.700701 ), switch_rot );
		pHSISelectChannel->SetMouseRegion( AID_F6, 0.399537f, 0.198847f, 0.442460f, 0.357838f );

		pADIAttitude->DefineGroup( GRP_SWITCH_6_F6_VC );
		pADIAttitude->SetInitialAnimState( 0.5 );
		pADIAttitude->SetReference( _V( 0.633, 2.045, 14.7004 ), switch_rot );
		pADIAttitude->SetMouseRegion( AID_F6, 0.576813f, 0.195323f, 0.617059f, 0.362889f );

		pADIError->DefineGroup( GRP_SWITCH_7_F6_VC );
		pADIError->SetInitialAnimState( 0.5 );
		pADIError->SetReference( _V( 0.5921, 2.0469, 14.7009 ), switch_rot );
		pADIError->SetMouseRegion( AID_F6, 0.653861f, 0.186497f, 0.699455f, 0.366683f );

		pADIRate->DefineGroup( GRP_SWITCH_8_F6_VC );
		pADIRate->SetInitialAnimState( 0.5 );
		pADIRate->SetReference( _V( 0.5627, 2.0463, 14.7008 ), switch_rot );
		pADIRate->SetMouseRegion( AID_F6, 0.709568f, 0.184330f, 0.752249f, 0.356840f );

		pAttRef->SetMouseRegion( AID_F6, 0.546105f, 0.634219f, 0.593604f, 0.831280f  );
		pAttRef->SetDirection( push_dir );
		pAttRef->DefineGroup( GRP_BUTTON3_F6_VC );

		pLandingGearTB[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_F6_VC );

		pLandingGearTB[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_F6_VC );

		pLandingGearTB[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS3_F6_VC );

		pLandingGearArmDeployCover[0]->SetMouseRegion( AID_F6, 0, 0.054526f, 0.528985f, 0.125257f, 0.754980f );
		pLandingGearArmDeployCover[0]->SetMouseRegion( AID_F6, 1, 0.054526f, 0.528985f, 0.070585f, 0.754980f );
		pLandingGearArmDeployCover[0]->SetReference( _V( -0.92, 1.99996, 14.68735 ), _V( 0, 0.965408, 0.260745 ) );
		pLandingGearArmDeployCover[0]->DefineGroup( GRP_A5_COVER1_F6_VC );

		pLandingGearArmDeployCover[1]->SetMouseRegion( AID_F6, 0, 0.145214f, 0.527563f, 0.213629f, 0.753547f );
		pLandingGearArmDeployCover[1]->SetMouseRegion( AID_F6, 1, 0.145214f, 0.527563f, 0.159221f, 0.652332f );
		pLandingGearArmDeployCover[1]->SetReference( _V( -0.87370, 1.99996, 14.68735 ), _V( 0, 0.965408, 0.260745 ) );
		pLandingGearArmDeployCover[1]->DefineGroup( GRP_A5_COVER2_F6_VC );

		pLandingGearArmDeploy[0]->SetStateOffset( 1, 0.0f, 0.488281f );
		pLandingGearArmDeploy[0]->SetDirection( push_dir );
		pLandingGearArmDeploy[0]->SetMouseRegion( AID_F6, 0.075215f, 0.560928f, 0.116564f, 0.730217f );
		pLandingGearArmDeploy[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_A5_S1_F6_VC );

		pLandingGearArmDeploy[1]->SetStateOffset( 1, 0.0f, 0.488281f );
		pLandingGearArmDeploy[1]->SetDirection( push_dir );
		pLandingGearArmDeploy[1]->SetMouseRegion( AID_F6, 0.162630f, 0.559619f, 0.204250f, 0.726978f );
		pLandingGearArmDeploy[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_A5_S2_F6_VC );

		pRCSCommand[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_R_F6_VC );
		pRCSCommand[0]->SetStateOffset( 1, 0.0f, 0.126953f );// L
		pRCSCommand[0]->SetStateOffset( 2, 0.139648f, 0.126953f );// R
		pRCSCommand[0]->SetStateOffset( 3, 0.139648f, 0.0f );// LR

		pRCSCommand[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_P_F6_VC );
		pRCSCommand[1]->SetStateOffset( 1, 0.0f, 0.126953f );// U
		pRCSCommand[1]->SetStateOffset( 2, 0.139648f, 0.126953f );// D
		pRCSCommand[1]->SetStateOffset( 3, 0.139648f, 0.0f );// UD

		pRCSCommand[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_Y_F6_VC );
		pRCSCommand[2]->SetStateOffset( 1, 0.0f, 0.126953f );// L
		pRCSCommand[2]->SetStateOffset( 2, 0.139648f, 0.126953f );// R
		pRCSCommand[2]->SetStateOffset( 3, 0.139648f, 0.0f );// LR

		pRangeSafeArm->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS3_F6_VC );
		pRangeSafeArm->SetStateOffset( 1, 0.139648f, 0.0f );
		pRangeSafeArm->SetStateOffset( 2, 0.139648f, 0.0f );
		pRangeSafeArm->SetStateOffset( 3, 0.139648f, 0.0f );

		pAbort->SetStateOffset( 1, -0.139648f, 0.0f );
		pAbort->SetDirection( push_dir );
		pAbort->SetMouseRegion( AID_F6, 0.908141f, 0.214696f, 0.939683f, 0.348886f );
		pAbort->DefineMeshGroup( GetVCMeshIndex(), GRP_A8_S2_F6_VC );

		pHUDMode->DefineGroup( GRP_HUDTEST_F6_VC );
		pHUDMode->SetInitialAnimState( 0.5 );
		pHUDMode->SetReference( _V( 0.7052, 2.4685, 14.5712 ), _V( 1, 0, 0 ) );
		pHUDMode->SetMouseRegion( AID_F6_HUD, 0.046968f, 0.392141f, 0.177257f, 0.644709f );

		pHUDBrightness->DefineGroup( GRP_HUDDIM_F6_VC );
		pHUDBrightness->SetInitialAnimState( 0.5 );
		pHUDBrightness->SetReference( _V( -0.6552, 2.4697, 14.5635 ), _V( 0.0, 0.275637, -0.961262 ) );
		pHUDBrightness->SetAngleRange( 180.0 );
		pHUDBrightness->SetMouseRegion( AID_F6_HUD, 0.401231f, 0.353931f, 0.605132f, 0.718589f );

		pHUDBright->DefineGroup( GRP_HUDBRT_F6_VC );
		pHUDBright->SetInitialAnimState( 0.5 );
		pHUDBright->SetReference( _V( 0.5978, 2.4679, 14.5712 ), _V( 1, 0, 0 ) );
		pHUDBright->SetMouseRegion( AID_F6_HUD, 0.814331f, 0.392763f, 0.946918f, 0.646512f );

		pRDRALTM->DefineGroup( GRP_SWITCH_4_F6_VC );
		pRDRALTM->SetInitialAnimState( 0.5 );
		pRDRALTM->SetReference( _V( -0.771385, 1.99079, 14.6858 ), _V( 1, 0, 0 ) );
		pRDRALTM->SetMouseRegion( AID_F6, 0.324223f, 0.622842f, 0.371621f, 0.797419f );
		return;
	}

	void PanelF6::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_F6, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F6,
			_V( -0.9453, 2.0815, 14.7095 ) + ofs, _V( -0.4221, 2.0815, 14.7095 ) + ofs,
			_V( -0.9453, 1.9531, 14.6751 ) + ofs, _V( -0.4221, 1.9531, 14.6751 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCRegisterArea( AID_F6_MDU, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F6_MDU,
			_V( -0.9395, 2.3122, 14.7566 ) + ofs, _V( -0.4259, 2.3122, 14.7566 ) + ofs,
			_V( -0.9395, 2.0986, 14.6968 ) + ofs, _V( -0.4259, 2.0986, 14.6968 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCRegisterArea( AID_F6_HUD, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F6_HUD,
			_V( -0.7256, 2.5085, 14.5803 ) + ofs, _V( -0.5853, 2.5085, 14.5803 ) + ofs,
			_V( -0.7256, 2.4326, 14.5593 ) + ofs, _V( -0.5853, 2.4326, 14.5593 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelF6::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "MDU_ADC_Power", 16 );
		pCDR1->ConnectPower( pBundle, 0 );
		pCDR2->ConnectPower( pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "DDU_POWER", 16 );
		pFltCntlrPower->ConnectPort( 1, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM4_CH1", 16 );
		pADIAttitude->ConnectPort( 2, pBundle, 0 );// INRTL
		pADIAttitude->ConnectPort( 1, pBundle, 1 );// LVLH
		pADIAttitude->ConnectPort( 0, pBundle, 2 );// REF
		pADIRate->ConnectPort( 2, pBundle, 3 );// HIGH
		pADIRate->ConnectPort( 1, pBundle, 4 );// MED
		pADIRate->ConnectPort( 0, pBundle, 5 );// LOW
		pADIError->ConnectPort( 2, pBundle, 6 );// HIGH
		pADIError->ConnectPort( 1, pBundle, 7 );// MED
		pADIError->ConnectPort( 0, pBundle, 8 );// LOW

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM12_CH0", 16 );
		pRDRALTM->ConnectPort( 1, pBundle, 13 );// CDR RDR ALTM 1
		pRDRALTM->ConnectPort( 0, pBundle, 14 );// CDR RDR ALTM 2
		pHSISelectSource->ConnectPort( 0, pBundle, 15 );// MLS

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM12_CH1", 16 );
		pHSISelectSource->ConnectPort( 1, pBundle, 0 );// NAV
		pHSISelectSource->ConnectPort( 2, pBundle, 1 );// GPS
		pHSISelectMode->ConnectPort( 0, pBundle, 2 );// APPROACH
		pHSISelectMode->ConnectPort( 1, pBundle, 3 );// TAEM
		pHSISelectMode->ConnectPort( 2, pBundle, 4 );// ENTRY
		pHSISelectChannel->ConnectPort( 0, pBundle, 5 );// 3
		pHSISelectChannel->ConnectPort( 1, pBundle, 6 );// 2
		pHSISelectChannel->ConnectPort( 2, pBundle, 7 );// 1

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM12_CH2", 16 );
		pAttRef->Connect( 0, pBundle, 6 );// ATT REF A
		pAttRef->Connect( 1, pBundle, 7 );// ATT REF B

		pBundle = STS()->BundleManager()->CreateBundle( "LANDING_GEAR", 16 );
		pLandingGearArmDeploy[0]->ConnectPushButton( pBundle, 0 );// arm pb
		pLandingGearArmDeploy[1]->ConnectPushButton( pBundle, 2 );// dn pb
		pLandingGearTB[0]->SetInput( 0, pBundle, 5, TB_UP );
		pLandingGearTB[0]->SetInput( 1, pBundle, 6, TB_DN );
		pLandingGearTB[1]->SetInput( 0, pBundle, 7, TB_UP );
		pLandingGearTB[1]->SetInput( 1, pBundle, 8, TB_DN );
		pLandingGearTB[2]->SetInput( 0, pBundle, 9, TB_UP );
		pLandingGearTB[2]->SetInput( 1, pBundle, 10, TB_DN );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_4", 16 );
		pAbort->ConnectLight( 0, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_5", 16 );
		pRangeSafeArm->ConnectLight( 0, pBundle, 5 );
		pRangeSafeArm->ConnectLight( 1, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_3", 16 );
		pRCSCommand[0]->ConnectLight( 0, pBundle, 1 );
		pRCSCommand[0]->ConnectLight( 2, pBundle, 5 );
		pRCSCommand[1]->ConnectLight( 0, pBundle, 9 );
		pRCSCommand[1]->ConnectLight( 2, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_4", 16 );
		pRCSCommand[2]->ConnectLight( 0, pBundle, 1 );
		pRCSCommand[2]->ConnectLight( 2, pBundle, 5 );
		pAbort->ConnectLight( 1, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_5", 16 );
		pRangeSafeArm->ConnectLight( 2, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_3", 16 );
		pRCSCommand[0]->ConnectLight( 1, pBundle, 1 );
		pRCSCommand[0]->ConnectLight( 3, pBundle, 5 );
		pRCSCommand[1]->ConnectLight( 1, pBundle, 9 );
		pRCSCommand[1]->ConnectLight( 3, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_4", 16 );
		pRCSCommand[2]->ConnectLight( 1, pBundle, 1 );
		pRCSCommand[2]->ConnectLight( 3, pBundle, 5 );
		pLandingGearArmDeploy[0]->ConnectLight( 0, pBundle, 13 );// arm light

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_5", 16 );
		pLandingGearArmDeploy[1]->ConnectLight( 0, pBundle, 1 );// dn light
		pRangeSafeArm->ConnectLight( 1, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "HUD_SWITCHES", 16 );
		// power cdr
		pHUDMode->ConnectPort( 0, pBundle, 1 );// mode dclt cdr
		// TODO mode norm cdr
		pHUDMode->ConnectPort( 2, pBundle, 3 );// mode test cdr
		pHUDBrightness->Connect( pBundle, 4 );// brightness cdr
		pHUDBright->ConnectPort( 0, pBundle, 5 );// bright man night cdr
		// TODO bright auto cdr
		pHUDBright->ConnectPort( 2, pBundle, 7 );// bright man day cdr

		AtlantisPanel::Realize();
	}

}
