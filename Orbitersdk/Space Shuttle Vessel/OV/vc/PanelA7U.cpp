/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/01   GLS
2021/06/03   GLS
2021/06/06   GLS
2021/06/28   GLS
2021/07/02   GLS
2021/08/22   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2022/01/07   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelA7U.h"
#include "StandardSwitch.h"
#include "PushButtonIndicator.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a7u.h"


namespace vc
{
	PanelA7U::PanelA7U(Atlantis* _sts)
		: AtlantisPanel(_sts, "A7U")
	{
		DefineMesh( MESHNAME_PANELA7U );

		Add( pMasterAlarm = new PushButtonIndicatorSingleLight( _sts, "MASTER ALARM" ) );

		Add( pPLBFloodAftStbd = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD AFT STBD" ) );
		pPLBFloodAftStbd->SetLabel( 0, "OFF" );
		pPLBFloodAftStbd->SetLabel( 1, "ON" );
		pPLBFloodAftStbd->SetInitialPosition( 0 );

		Add( pPLBFloodAftPort = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD AFT PORT" ) );
		pPLBFloodAftPort->SetLabel( 0, "OFF" );
		pPLBFloodAftPort->SetLabel( 1, "ON" );
		pPLBFloodAftPort->SetInitialPosition( 0 );

		Add( pPLBFloodMidStbd = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD MID STBD" ) );
		pPLBFloodMidStbd->SetLabel( 0, "OFF" );
		pPLBFloodMidStbd->SetLabel( 1, "ON" );
		pPLBFloodMidStbd->SetInitialPosition( 0 );

		Add( pPLBFloodMidPort = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD MID PORT" ) );
		pPLBFloodMidPort->SetLabel( 0, "OFF" );
		pPLBFloodMidPort->SetLabel( 1, "ON" );
		pPLBFloodMidPort->SetInitialPosition( 0 );

		Add( pPLBFloodFwdStbd = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD FWD STBD" ) );
		pPLBFloodFwdStbd->SetLabel( 0, "OFF" );
		pPLBFloodFwdStbd->SetLabel( 1, "ON" );
		pPLBFloodFwdStbd->SetInitialPosition( 0 );

		Add( pPLBFloodFwdPort = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD FWD PORT" ) );
		pPLBFloodFwdPort->SetLabel( 0, "OFF" );
		pPLBFloodFwdPort->SetLabel( 1, "ON" );
		pPLBFloodFwdPort->SetInitialPosition( 0 );

		Add( pPLBFloodDocking = new StdSwitch3( _sts, "PAYLOAD BAY FLOOD DOCKING" ) );
		pPLBFloodDocking->SetLabel( 0, "OFF" );
		pPLBFloodDocking->SetLabel( 1, "DIM" );
		pPLBFloodDocking->SetLabel( 2, "BRIGHT" );
		pPLBFloodDocking->SetInitialPosition( 0 );

		Add( pPLBFloodFwdBhd = new StdSwitch2( _sts, "PAYLOAD BAY FLOOD FWD BHD" ) );
		pPLBFloodFwdBhd->SetLabel( 0, "OFF" );
		pPLBFloodFwdBhd->SetLabel( 1, "ON" );
		pPLBFloodFwdBhd->SetInitialPosition( 0 );

		Add( pPortRMSLight = new StdSwitch2( _sts, "RMS SPOTLIGHT PORT" ) );
		pPortRMSLight->SetLabel( 0, "OFF" );
		pPortRMSLight->SetLabel( 1, "ON" );
		pPortRMSLight->SetInitialPosition( 0 );

		Add( pPortRMSCamera = new StdSwitch2( _sts, "RMS CAMERA PORT" ) );
		pPortRMSCamera->SetLabel( 0, "ELBOW" );
		pPortRMSCamera->SetLabel( 1, "WRIST" );

		Add( pCameraPowerA_TB = new StandardTalkback2( _sts, "CAMERA POWER A TB" ) );
		Add( pCameraPowerB_TB = new StandardTalkback2( _sts, "CAMERA POWER B TB" ) );
		Add( pCameraPowerC_TB = new StandardTalkback2( _sts, "CAMERA POWER C TB" ) );
		Add( pCameraPowerD_TB = new StandardTalkback2( _sts, "CAMERA POWER D TB" ) );
		Add( pCameraPowerRMS_TB = new StandardTalkback2( _sts, "CAMERA POWER RMS TB" ) );

		Add( pCameraPowerA = new StdSwitch3( _sts, "CAMERA POWER A" ) );
		Add( pCameraPowerB = new StdSwitch3( _sts, "CAMERA POWER B" ) );
		Add( pCameraPowerC = new StdSwitch3( _sts, "CAMERA POWER C" ) );
		Add( pCameraPowerD = new StdSwitch3( _sts, "CAMERA POWER D" ) );
		Add( pCameraPowerRMS = new StdSwitch3( _sts, "CAMERA POWER RMS" ) );

		Add( pVideoInputA = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT A" ) );
		Add( pVideoInputB = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT B" ) );
		Add( pVideoInputC = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT C" ) );
		Add( pVideoInputD = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT D" ) );
		Add( pVideoInputRMS = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT RMS" ) );
		Add( pVideoInputFltDeck = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT FLT DECK" ) );
		Add( pVideoInputMidDeck = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT MID DECK" ) );
		Add( pVideoInputPL1 = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT PL 1" ) );
		Add( pVideoInputPL2 = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT PL 2" ) );
		Add( pVideoInputPL3 = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT PL 3" ) );
		Add( pVideoInputMUX1 = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT MUX 1" ) );
		Add( pVideoInputMUX2 = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT MUX 2" ) );
		Add( pVideoInputTest = new PushButtonIndicatorSingleLight( _sts, "VIDEO INPUT TEST" ) );

		Add( pVideoOutputMon1 = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT MON 1" ) );
		Add( pVideoOutputMon2 = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT MON 2" ) );
		Add( pVideoOutputDownLink = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT DOWN LINK" ) );
		Add( pVideoOutputDTV = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT DTV" ) );
		Add( pVideoOutputMUX1L = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT MUX 1L" ) );
		Add( pVideoOutputMUX1R = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT MUX 1R" ) );
		Add( pVideoOutputMUX2L = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT MUX 2L" ) );
		Add( pVideoOutputMUX2R = new PushButtonIndicatorSingleLight( _sts, "VIDEO OUTPUT MUX 2R" ) );

		Add( pPanTiltRate= new StdSwitch3( _sts, "CAMERA COMMAND PAN/TILT" ) );
		pPanTiltRate->SetLabel( 0, "LOW RATE" );
		pPanTiltRate->SetLabel( 1, "HIGH RATE" );

		Add( pCameraZoom = new StdSwitch3( _sts, "CAMERA COMMAND ZOOM" ) );
		Add( pCameraTilt = new StdSwitch3( _sts, "CAMERA COMMAND TILT" ) );
		Add( pCameraPan = new StdSwitch3( _sts, "CAMERA COMMAND PAN" ) );

		Add( pMenuALC = new PushButtonIndicatorSingleLight( _sts, "MENU ALC" ) );
		Add( pMenuManGain = new PushButtonIndicatorSingleLight( _sts, "MENU MAN GAIN" ) );
		Add( pMenuColorBalLTLevel = new PushButtonIndicatorSingleLight( _sts, "MENU COLOR BAL/LT LEVEL" ) );
		Add( pMode1 = new PushButtonIndicatorSingleLight( _sts, "MODE 1" ) );
		Add( pMode2 = new PushButtonIndicatorSingleLight( _sts, "MODE 2" ) );
		Add( pMode3 = new PushButtonIndicatorSingleLight( _sts, "MODE 3" ) );
	}

	PanelA7U::~PanelA7U()
	{
	}

	void PanelA7U::DefineVC()
	{
		const VECTOR3 switch_rot_vert =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 switch_rot_horz = _V( 0.0, 0.9499, -0.3126 );
		VECTOR3 switch_pull = _V( 0.0, 0.3126, 0.9499 );
		VECTOR3 push_dir = -switch_pull;

		AddAIDToMouseEventList(AID_A7U);

		pMasterAlarm->SetStateOffset( 1, 0.139648f, 0.0f );
		pMasterAlarm->SetDirection( push_dir );
		pMasterAlarm->SetMouseRegion( AID_A7U, 0.083136f, 0.079706f, 0.138636f, 0.132303f );
		pMasterAlarm->DefineMeshGroup( GetVCMeshIndex(), GRP_S51_A7U_VC );

		pPLBFloodAftStbd->DefineGroup( GRP_S1_A7U_VC );
		pPLBFloodAftStbd->SetInitialAnimState( 0.5 );
		pPLBFloodAftStbd->SetMouseRegion( AID_A7U, 0.073511f, 0.2643898f, 0.113731f, 0.320099f );
		pPLBFloodAftStbd->SetReference( _V( 0.207, 2.7795, 12.311 ), switch_rot_vert );

		pPLBFloodAftPort->DefineGroup( GRP_S2_A7U_VC );
		pPLBFloodAftPort->SetInitialAnimState( 0.5 );
		pPLBFloodAftPort->SetMouseRegion( AID_A7U, 0.158763f, 0.2643898f, 0.197284f, 0.320099f );
		pPLBFloodAftPort->SetReference( _V( 0.1635, 2.7795, 12.311 ), switch_rot_vert );

		pPLBFloodMidStbd->DefineGroup( GRP_S3_A7U_VC );
		pPLBFloodMidStbd->SetInitialAnimState( 0.5 );
		pPLBFloodMidStbd->SetMouseRegion( AID_A7U, 0.073511f, 0.407877f, 0.113731f, 0.460654f );
		pPLBFloodMidStbd->SetReference( _V( 0.207, 2.725, 12.3285 ), switch_rot_vert );

		pPLBFloodMidPort->DefineGroup( GRP_S4_A7U_VC );
		pPLBFloodMidPort->SetInitialAnimState( 0.5 );
		pPLBFloodMidPort->SetMouseRegion( AID_A7U, 0.158763f, 0.407877f, 0.197284f, 0.460654f );
		pPLBFloodMidPort->SetReference( _V( 0.1635, 2.725, 12.3285 ), switch_rot_vert );

		pPLBFloodFwdStbd->DefineGroup( GRP_S5_A7U_VC );
		pPLBFloodFwdStbd->SetInitialAnimState( 0.5 );
		pPLBFloodFwdStbd->SetMouseRegion( AID_A7U, 0.073511f, 0.563212f, 0.113731f, 0.612821f );
		pPLBFloodFwdStbd->SetReference( _V( 0.207, 2.666, 12.347 ), switch_rot_vert );

		pPLBFloodFwdPort->DefineGroup( GRP_S6_A7U_VC );
		pPLBFloodFwdPort->SetInitialAnimState( 0.5 );
		pPLBFloodFwdPort->SetMouseRegion( AID_A7U, 0.158763f, 0.563212f, 0.197284f, 0.612821f );
		pPLBFloodFwdPort->SetReference(_V( 0.1635, 2.666, 12.347 ), switch_rot_vert );

		pPLBFloodDocking->DefineGroup( GRP_S7_A7U_VC );
		pPLBFloodDocking->SetInitialAnimState( 0.5 );
		pPLBFloodDocking->SetMouseRegion( AID_A7U, 0.073511f, 0.691983f, 0.113731f, 0.744320f );
		pPLBFloodDocking->SetReference( _V( 0.207, 2.6155, 12.363 ), switch_rot_vert );

		pPLBFloodFwdBhd->DefineGroup( GRP_S8_A7U_VC );
		pPLBFloodFwdBhd->SetInitialAnimState( 0.5 );
		pPLBFloodFwdBhd->SetMouseRegion( AID_A7U, 0.158763f, 0.691983f, 0.197284f, 0.744320f );
		pPLBFloodFwdBhd->SetReference( _V( 0.1635, 2.6155, 12.363 ), switch_rot_vert );

		pPortRMSLight->SetInitialAnimState( 0.5 );
		pPortRMSLight->DefineGroup( GRP_S9_A7U_VC );
		pPortRMSLight->SetMouseRegion( AID_A7U, 0.073511f, 0.839128f, 0.113731f, 0.890425f );
		pPortRMSLight->SetReference( _V( 0.1635, 2.5595, 12.3805 ), switch_rot_vert );

		pPortRMSCamera->SetInitialAnimState( 0.5 );
		pPortRMSCamera->DefineGroup( GRP_S10_A7U_VC );
		pPortRMSCamera->SetMouseRegion( AID_A7U, 0.158763f, 0.839128f, 0.197284f, 0.890425f );
		pPortRMSCamera->SetReference( _V( 0.1635, 2.5595, 12.3805 ), switch_rot_vert );

		pCameraPowerA_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS4_U_A7U_VC, GRP_DS4_L_A7U_VC );
		pCameraPowerA_TB->SetInactiveSegment( TB_OFF );

		pCameraPowerB_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS5_U_A7U_VC, GRP_DS5_L_A7U_VC );
		pCameraPowerB_TB->SetInactiveSegment( TB_OFF );

		pCameraPowerC_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS6_U_A7U_VC, GRP_DS6_L_A7U_VC );
		pCameraPowerC_TB->SetInactiveSegment( TB_OFF );

		pCameraPowerD_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS7_U_A7U_VC, GRP_DS7_L_A7U_VC );
		pCameraPowerD_TB->SetInactiveSegment( TB_OFF );

		pCameraPowerRMS_TB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS8_U_A7U_VC, GRP_DS8_L_A7U_VC );
		pCameraPowerRMS_TB->SetInactiveSegment( TB_OFF );

		pCameraPowerA->DefineGroup( GRP_S13_A7U_VC );
		pCameraPowerA->SetInitialAnimState( 0.5f );
		pCameraPowerA->SetMouseRegion( AID_A7U, 0.511296f, 0.222131f, 0.549592f, 0.272522f );
		pCameraPowerA->SetReference( _V( -0.0244, 2.7983, 12.3060 ), switch_rot_vert );
		pCameraPowerA->SetSpringLoaded( true );

		pCameraPowerB->DefineGroup( GRP_S14_A7U_VC );
		pCameraPowerB->SetInitialAnimState( 0.5f );
		pCameraPowerB->SetMouseRegion( AID_A7U, 0.566371f, 0.222131f, 0.608776f, 0.272522f );
		pCameraPowerB->SetReference( _V( -0.0244, 2.7983, 12.3060 ), switch_rot_vert );
		pCameraPowerB->SetSpringLoaded( true );

		pCameraPowerC->DefineGroup( GRP_S15_A7U_VC );
		pCameraPowerC->SetInitialAnimState( 0.5f );
		pCameraPowerC->SetMouseRegion( AID_A7U, 0.618547f, 0.222131f, 0.665237f, 0.272522f );
		pCameraPowerC->SetReference( _V( -0.0244, 2.7983, 12.3060 ), switch_rot_vert );
		pCameraPowerC->SetSpringLoaded( true );

		pCameraPowerD->DefineGroup( GRP_S16_A7U_VC );
		pCameraPowerD->SetInitialAnimState( 0.5f );
		pCameraPowerD->SetMouseRegion( AID_A7U, 0.677654f, 0.222131f, 0.716847f, 0.272522f );
		pCameraPowerD->SetReference( _V( -0.0244, 2.7983, 12.3060 ), switch_rot_vert );
		pCameraPowerD->SetSpringLoaded( true );

		pCameraPowerRMS->DefineGroup( GRP_S17_A7U_VC );
		pCameraPowerRMS->SetInitialAnimState( 0.5f );
		pCameraPowerRMS->SetMouseRegion( AID_A7U, 0.727239f, 0.222131f, 0.775512f, 0.272522f );
		pCameraPowerRMS->SetReference( _V( -0.0244, 2.7983, 12.3060 ), switch_rot_vert );
		pCameraPowerRMS->SetSpringLoaded( true );

		pVideoInputA->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputA->SetDirection( push_dir );
		pVideoInputA->SetMouseRegion( AID_A7U, 0.510289f, 0.396140f, 0.551662f, 0.450443f );
		pVideoInputA->DefineMeshGroup( GetVCMeshIndex(), GRP_S27_A7U_VC );

		pVideoInputB->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputB->SetDirection( push_dir );
		pVideoInputB->SetMouseRegion( AID_A7U, 0.566371f, 0.396140f, 0.607709f, 0.450443f );
		pVideoInputB->DefineMeshGroup( GetVCMeshIndex(), GRP_S28_A7U_VC );

		pVideoInputC->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputC->SetDirection( push_dir );
		pVideoInputC->SetMouseRegion( AID_A7U, 0.620470f, 0.396140f, 0.662608f, 0.450443f );
		pVideoInputC->DefineMeshGroup( GetVCMeshIndex(), GRP_S29_A7U_VC );

		pVideoInputD->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputD->SetDirection( push_dir );
		pVideoInputD->SetMouseRegion( AID_A7U, 0.510289f, 0.474687f, 0.551662f, 0.528498f );
		pVideoInputD->DefineMeshGroup( GetVCMeshIndex(), GRP_S30_A7U_VC );

		pVideoInputRMS->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputRMS->SetDirection( push_dir );
		pVideoInputRMS->SetMouseRegion( AID_A7U, 0.566371f, 0.474687f, 0.607709f, 0.528498f );
		pVideoInputRMS->DefineMeshGroup( GetVCMeshIndex(), GRP_S31_A7U_VC );

		pVideoInputFltDeck->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputFltDeck->SetDirection( push_dir );
		pVideoInputFltDeck->SetMouseRegion( AID_A7U, 0.620470f, 0.474687f, 0.662608f, 0.528498f );
		pVideoInputFltDeck->DefineMeshGroup( GetVCMeshIndex(), GRP_S32_A7U_VC );

		pVideoInputMidDeck->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputMidDeck->SetDirection( push_dir );
		pVideoInputMidDeck->SetMouseRegion( AID_A7U, 0.676772f, 0.474687f, 0.718276f, 0.528498f );
		pVideoInputMidDeck->DefineMeshGroup( GetVCMeshIndex(), GRP_S55_A7U_VC );

		pVideoInputPL1->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputPL1->SetDirection( push_dir );
		pVideoInputPL1->SetMouseRegion( AID_A7U, 0.510289f, 0.565888f, 0.551662f, 0.619647f );
		pVideoInputPL1->DefineMeshGroup( GetVCMeshIndex(), GRP_S33_A7U_VC );

		pVideoInputPL2->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputPL2->SetDirection( push_dir );
		pVideoInputPL2->SetMouseRegion( AID_A7U, 0.566371f, 0.565888f, 0.607709f, 0.619647f );
		pVideoInputPL2->DefineMeshGroup( GetVCMeshIndex(), GRP_S34_A7U_VC );

		pVideoInputPL3->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputPL3->SetDirection( push_dir );
		pVideoInputPL3->SetMouseRegion( AID_A7U, 0.620470f, 0.565888f, 0.662608f, 0.619647f );
		pVideoInputPL3->DefineMeshGroup( GetVCMeshIndex(), GRP_S35_A7U_VC );

		pVideoInputMUX1->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputMUX1->SetDirection( push_dir );
		pVideoInputMUX1->SetMouseRegion( AID_A7U, 0.510289f, 0.643987f, 0.551662f, 0.697785f );
		pVideoInputMUX1->DefineMeshGroup( GetVCMeshIndex(), GRP_S36_A7U_VC );

		pVideoInputMUX2->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputMUX2->SetDirection( push_dir );
		pVideoInputMUX2->SetMouseRegion( AID_A7U, 0.566371f, 0.643987f, 0.607709f, 0.697785f );
		pVideoInputMUX2->DefineMeshGroup( GetVCMeshIndex(), GRP_S37_A7U_VC );

		pVideoInputTest->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoInputTest->SetDirection( push_dir );
		pVideoInputTest->SetMouseRegion( AID_A7U, 0.620470f, 0.643987f, 0.662608f, 0.697785f );
		pVideoInputTest->DefineMeshGroup( GetVCMeshIndex(), GRP_S38_A7U_VC );

		pVideoOutputMon1->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputMon1->SetDirection( push_dir );
		pVideoOutputMon1->SetMouseRegion( AID_A7U, 0.804372f, 0.396140f, 0.845838f, 0.450443f );
		pVideoOutputMon1->DefineMeshGroup( GetVCMeshIndex(), GRP_S19_A7U_VC );

		pVideoOutputMon2->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputMon2->SetDirection( push_dir );
		pVideoOutputMon2->SetMouseRegion( AID_A7U, 0.804372f, 0.474687f, 0.845838f, 0.528498f );
		pVideoOutputMon2->DefineMeshGroup( GetVCMeshIndex(), GRP_S23_A7U_VC );

		pVideoOutputDownLink->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputDownLink->SetDirection( push_dir );
		pVideoOutputDownLink->SetMouseRegion( AID_A7U, 0.859510f, 0.396140f, 0.901360f, 0.450443f );
		pVideoOutputDownLink->DefineMeshGroup( GetVCMeshIndex(), GRP_S22_A7U_VC );

		pVideoOutputDTV->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputDTV->SetDirection( push_dir );
		pVideoOutputDTV->SetMouseRegion( AID_A7U, 0.859510f, 0.474687f, 0.901360f, 0.528498f );
		pVideoOutputDTV->DefineMeshGroup( GetVCMeshIndex(), GRP_S26_A7U_VC );

		pVideoOutputMUX1L->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputMUX1L->SetDirection( push_dir );
		pVideoOutputMUX1L->SetMouseRegion( AID_A7U, 0.804372f, 0.565888f, 0.845838f, 0.619647f );
		pVideoOutputMUX1L->DefineMeshGroup( GetVCMeshIndex(), GRP_S20_A7U_VC );

		pVideoOutputMUX1R->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputMUX1R->SetDirection( push_dir );
		pVideoOutputMUX1R->SetMouseRegion( AID_A7U, 0.859510f, 0.565888f, 0.901360f, 0.619647f );
		pVideoOutputMUX1R->DefineMeshGroup( GetVCMeshIndex(), GRP_S21_A7U_VC );

		pVideoOutputMUX2L->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputMUX2L->SetDirection( push_dir );
		pVideoOutputMUX2L->SetMouseRegion( AID_A7U, 0.804372f, 0.643987f, 0.845838f, 0.697785f );
		pVideoOutputMUX2L->DefineMeshGroup( GetVCMeshIndex(), GRP_S24_A7U_VC );

		pVideoOutputMUX2R->SetStateOffset( 1, 0.0f, 0.488281f );
		pVideoOutputMUX2R->SetDirection( push_dir );
		pVideoOutputMUX2R->SetMouseRegion( AID_A7U, 0.859510f, 0.643987f, 0.901360f, 0.697785f );
		pVideoOutputMUX2R->DefineMeshGroup( GetVCMeshIndex(), GRP_S25_A7U_VC );

		pPanTiltRate->DefineGroup( GRP_S56_A7U_VC );
		pPanTiltRate->SetInitialAnimState( 0.5 );
		pPanTiltRate->SetMouseRegion( AID_A7U, 0.556938f, 0.779399f, 0.597005f, 0.830112f );
		pPanTiltRate->SetReference( _V( -0.043, 2.583, 12.373 ), switch_rot_vert );
		pPanTiltRate->SetSpringLoaded( true, 2 );

		pCameraZoom->DefineGroup( GRP_S41_A7U_VC );
		pCameraZoom->SetInitialAnimState( 0.5 );
		pCameraZoom->SetMouseRegion( AID_A7U, 0.668528f, 0.779399f, 0.709543f, 0.830112f );
		pCameraZoom->SetReference( _V( -0.158, 2.583, 12.373 ), switch_rot_vert );
		pCameraZoom->SetSpringLoaded( true );

		pCameraTilt->DefineGroup( GRP_S43_A7U_VC );
		pCameraTilt->SetInitialAnimState( 0.5 );
		pCameraTilt->SetMouseRegion( AID_A7U, 0.777975f, 0.779399f, 0.818993f, 0.830112f );
		pCameraTilt->SetReference( _V( -0.158, 2.583, 12.373 ), switch_rot_vert );
		pCameraTilt->SetSpringLoaded( true );

		pCameraPan->DefineGroup( GRP_S44_A7U_VC );
		pCameraPan->SetInitialAnimState( 0.5 );
		pCameraPan->SetMouseRegion( AID_A7U, 0.858388f, 0.777995f, 0.894921f, 0.828333f );
		pCameraPan->SetReference( _V( -0.2, 2.584, 12.373 ), switch_rot_horz );
		pCameraPan->SetOrientation( true );
		pCameraPan->SetSpringLoaded( true );

		pMenuALC->SetStateOffset( 1, 0.0f, 0.488281f );
		pMenuALC->SetDirection( push_dir );
		pMenuALC->SetMouseRegion( AID_A7U, 0.593901f, 0.909915f, 0.636076f, 0.964254f );
		pMenuALC->DefineMeshGroup( GetVCMeshIndex(), GRP_S45_A7U_VC );

		pMenuManGain->SetStateOffset( 1, 0.0f, 0.488281f );
		pMenuManGain->SetDirection( push_dir );
		pMenuManGain->SetMouseRegion( AID_A7U, 0.647890f, 0.909915f, 0.690042f, 0.964254f );
		pMenuManGain->DefineMeshGroup( GetVCMeshIndex(), GRP_S46_A7U_VC );

		pMenuColorBalLTLevel->SetStateOffset( 1, 0.0f, 0.488281f );
		pMenuColorBalLTLevel->SetDirection( push_dir );
		pMenuColorBalLTLevel->SetMouseRegion( AID_A7U, 0.701415f, 0.909915f, 0.743015f, 0.964254f );
		pMenuColorBalLTLevel->DefineMeshGroup( GetVCMeshIndex(), GRP_S47_A7U_VC );

		pMode1->SetStateOffset( 1, 0.0f, 0.488281f );
		pMode1->SetDirection( push_dir );
		pMode1->SetMouseRegion( AID_A7U, 0.754426f, 0.909915f, 0.796086f, 0.964254f );
		pMode1->DefineMeshGroup( GetVCMeshIndex(), GRP_S48_A7U_VC );

		pMode2->SetStateOffset( 1, 0.0f, 0.488281f );
		pMode2->SetDirection( push_dir );
		pMode2->SetMouseRegion( AID_A7U, 0.808099f, 0.909915f, 0.850354f, 0.964254f );
		pMode2->DefineMeshGroup( GetVCMeshIndex(), GRP_S49_A7U_VC );

		pMode3->SetStateOffset( 1, 0.0f, 0.488281f );
		pMode3->SetDirection( push_dir );
		pMode3->SetMouseRegion( AID_A7U, 0.861583f, 0.909915f, 0.903355f, 0.964254f );
		pMode3->DefineMeshGroup( GetVCMeshIndex(), GRP_S50_A7U_VC );
	}

	void PanelA7U::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A7U, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A7U,
			_V( 0.255933, 2.89358, 12.2774 ) + ofs, _V( -0.263473, 2.89358, 12.2774 ) + ofs,
			_V( 0.255933, 2.50815, 12.3983 ) + ofs, _V( -0.263473, 2.50815, 12.3983 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelA7U::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "PLB_LIGHTS", 16 );
		pPLBFloodFwdStbd->ConnectPort( 1, pBundle, 0 );
		pPLBFloodFwdPort->ConnectPort( 1, pBundle, 1 );
		pPLBFloodMidStbd->ConnectPort( 1, pBundle, 2 );
		pPLBFloodMidPort->ConnectPort( 1, pBundle, 3 );
		pPLBFloodAftStbd->ConnectPort( 1, pBundle, 4 );
		pPLBFloodAftPort->ConnectPort( 1, pBundle, 5 );
		pPLBFloodFwdBhd->ConnectPort( 1, pBundle, 6 );
		pPLBFloodDocking->ConnectPort( 1, pBundle, 7 );// DIM
		pPLBFloodDocking->ConnectPort( 2, pBundle, 8 );// BRIGHT
		pPortRMSLight->ConnectPort( 1, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "VCU_input_1", 16 );
		pVideoInputA->ConnectPushButton( pBundle, 0 );
		pVideoInputB->ConnectPushButton( pBundle, 1 );
		pVideoInputC->ConnectPushButton( pBundle, 2 );
		pVideoInputD->ConnectPushButton( pBundle, 3 );
		pVideoInputRMS->ConnectPushButton( pBundle, 4 );
		pVideoInputFltDeck->ConnectPushButton( pBundle, 5 );
		pVideoInputMidDeck->ConnectPushButton( pBundle, 6 );
		pVideoInputPL1->ConnectPushButton( pBundle, 7 );
		pVideoInputPL2->ConnectPushButton( pBundle, 8 );
		pVideoInputPL3->ConnectPushButton( pBundle, 9 );
		pVideoInputMUX1->ConnectPushButton( pBundle, 10 );
		pVideoInputMUX2->ConnectPushButton( pBundle, 11 );
		pVideoInputTest->ConnectPushButton( pBundle, 12 );
		pVideoOutputMon1->ConnectPushButton( pBundle, 13 );
		pVideoOutputMon2->ConnectPushButton( pBundle, 14 );
		pVideoOutputDownLink->ConnectPushButton( pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "VCU_input_2", 16 );
		pVideoOutputDTV->ConnectPushButton( pBundle, 0 );
		pVideoOutputMUX1L->ConnectPushButton( pBundle, 1 );
		pVideoOutputMUX1R->ConnectPushButton( pBundle, 2 );
		pVideoOutputMUX2L->ConnectPushButton( pBundle, 3 );
		pVideoOutputMUX2R->ConnectPushButton( pBundle, 4 );
		pMenuALC->ConnectPushButton( pBundle, 5 );
		pMenuManGain->ConnectPushButton( pBundle, 6 );
		pMenuColorBalLTLevel->ConnectPushButton( pBundle, 7 );
		pMode1->ConnectPushButton( pBundle, 8 );
		pMode2->ConnectPushButton( pBundle, 9 );
		pMode3->ConnectPushButton( pBundle, 10 );
		pCameraPowerA->ConnectPort( 2, pBundle, 11 );
		pCameraPowerA->ConnectPort( 0, pBundle, 12 );
		pCameraPowerB->ConnectPort( 2, pBundle, 13 );
		pCameraPowerB->ConnectPort( 0, pBundle, 14 );
		pCameraPowerC->ConnectPort( 2, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "VCU_input_3", 16 );
		pCameraPowerC->ConnectPort( 0, pBundle, 0 );
		pCameraPowerD->ConnectPort( 2, pBundle, 1 );
		pCameraPowerD->ConnectPort( 0, pBundle, 2 );
		pCameraPowerRMS->ConnectPort( 2, pBundle, 3 );
		pCameraPowerRMS->ConnectPort( 0, pBundle, 4 );
		pPortRMSCamera->ConnectPort( 1, pBundle, 5 );
		pPortRMSCamera->ConnectPort( 0, pBundle, 6 );
		pPanTiltRate->ConnectPort( 2, pBundle, 7 );
		pPanTiltRate->ConnectPort( 0, pBundle, 8 );
		pCameraTilt->ConnectPort( 2, pBundle, 9 );
		pCameraTilt->ConnectPort( 0, pBundle, 10 );
		pCameraPan->ConnectPort( 2, pBundle, 11 );
		pCameraPan->ConnectPort( 0, pBundle, 12 );
		pCameraZoom->ConnectPort( 2, pBundle, 13 );
		pCameraZoom->ConnectPort( 0, pBundle, 14 );

		pBundle = STS()->BundleManager()->CreateBundle( "VCU_output_1", 16 );
		pCameraPowerA_TB->SetInput( pBundle, 0, TB_ON );
		pCameraPowerB_TB->SetInput( pBundle, 1, TB_ON );
		pCameraPowerC_TB->SetInput( pBundle, 2, TB_ON );
		pCameraPowerD_TB->SetInput( pBundle, 3, TB_ON );
		pCameraPowerRMS_TB->SetInput( pBundle, 4, TB_ON );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_1", 16 );
		pVideoOutputMon1->ConnectLight( 0, pBundle, 3 );
		pVideoOutputMUX1L->ConnectLight( 0, pBundle, 7 );
		pVideoOutputMUX1R->ConnectLight( 0, pBundle, 11 );
		pVideoOutputMon2->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_2", 16 );
		pVideoOutputMUX2L->ConnectLight( 0, pBundle, 3 );
		pVideoOutputMUX2R->ConnectLight( 0, pBundle, 7 );
		pVideoInputA->ConnectLight( 0, pBundle, 11 );
		pVideoInputB->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_3", 16 );
		pVideoInputC->ConnectLight( 0, pBundle, 3 );
		pVideoInputPL1->ConnectLight( 0, pBundle, 7 );
		pVideoInputPL2->ConnectLight( 0, pBundle, 11 );
		pVideoInputPL3->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_4", 16 );
		pMode1->ConnectLight( 0, pBundle, 3 );
		pMode2->ConnectLight( 0, pBundle, 7 );
		pMode3->ConnectLight( 0, pBundle, 11 );
		pMasterAlarm->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA4_5", 16 );
		pVideoInputMidDeck->ConnectLight( 0, pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_1", 16 );
		pVideoOutputDownLink->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_2", 16 );
		pVideoOutputDTV->ConnectLight( 0, pBundle, 7 );
		pVideoInputD->ConnectLight( 0, pBundle, 11 );
		pVideoInputRMS->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_3", 16 );
		pVideoInputFltDeck->ConnectLight( 0, pBundle, 3 );
		pVideoInputMUX1->ConnectLight( 0, pBundle, 7 );
		pVideoInputMUX2->ConnectLight( 0, pBundle, 11 );
		pVideoInputTest->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA5_4", 16 );
		pMenuALC->ConnectLight( 0, pBundle, 3 );
		pMenuManGain->ConnectLight( 0, pBundle, 7 );
		pMenuColorBalLTLevel->ConnectLight( 0, pBundle, 11 );
		pMasterAlarm->ConnectLight( 1, pBundle, 15 );

		AtlantisPanel::Realize();
	}
}
