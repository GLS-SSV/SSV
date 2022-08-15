/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/05/24   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/06/28   GLS
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
********************************************/#include "PanelA8A3.h"
#include "StandardSwitch.h"
#include "PushButton.h"
#include "StandardLight.h"
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "DiscreteBundleManager.h"
#include "../meshres_vc_a8a3.h"


namespace vc
{
	using namespace discsignals;

	PanelA8A3::PanelA8A3( Atlantis* _sts, bool defaultposition ): AtlantisPanel( _sts, defaultposition ? "A8" : "A7L" )
	{
		DefineMesh( MESHNAME_PANELA8A3 );

		Add(plADS = new StandardSingleLight(_sts, "APDS POWER ADS LT"));
		Add(plBDS = new StandardSingleLight(_sts, "APDS POWER BDS LT"));
		Add(plCDS = new StandardSingleLight(_sts, "APDS POWER CDS LT"));

		Add(plPowerOn = new StandardSingleLight(_sts, "STATUS POWER ON"));
		Add(plAPDSProtectCircOff = new StandardSingleLight(_sts, "STATUS APDS CIRCUIT PROTECT OFF"));
		Add(plRingAligned = new StandardSingleLight(_sts, "STATUS RING ALIGNED"));
		Add(plRingInitialPos = new StandardSingleLight(_sts, "STATUS RING INITIAL POSITION"));
		Add(plFixersOff = new StandardSingleLight(_sts, "STATUS FIXERS OFF"));
		Add(plHooks1Open = new StandardSingleLight(_sts, "STATUS HOOKS 1 OPEN"));
		Add(plHooks2Open = new StandardSingleLight(_sts, "STATUS HOOKS 2 OPEN"));
		Add(plLatchesClosed = new StandardSingleLight(_sts, "STATUS LATCHES CLOSED"));
		Add(plUndockComplete = new StandardSingleLight(_sts, "STATUS UNDOCK COMPLET"));

		Add(plInitialContact = new StandardSingleLight(_sts, "STATUS INITIAL CONTACT"));
		Add(plCapture = new StandardSingleLight(_sts, "STATUS CAPTURE CAPTURE"));
		Add(plRingForward = new StandardSingleLight(_sts, "STATUS RING FORWARD"));
		Add(plReadyToHook = new StandardSingleLight(_sts, "STATUS READY TO HOOK"));
		Add(plInterfSealed = new StandardSingleLight(_sts, "STATUS INTERF SEALED"));
		Add(plHooks1Closed = new StandardSingleLight(_sts, "STATUS HOOKS 1 CLOSED"));
		Add(plHooks2Closed = new StandardSingleLight(_sts, "STATUS HOOKS 2 CLOSED"));
		Add(plLatchesOpen = new StandardSingleLight(_sts, "STATUS LATCHES OPEN"));
		Add(plRingFinal = new StandardSingleLight(_sts, "STATUS RING FINAL POSITION"));

		Add( plAp = new StandardSingleLight( _sts, "PYROS Ap LT" ) );
		Add( plBp = new StandardSingleLight( _sts, "PYROS Bp LT" ) );
		Add( plCp = new StandardSingleLight( _sts, "PYROS Cp LT" ) );

		Add( pPyroProtectCircuitOff = new StandardSingleLight( _sts, "PYRO PROTECT CIRCUIT OFF" ) );

		Add(pControlPanelPowerA = new StdSwitch2(_sts, "CONTROL PANEL POWER A"));
		pControlPanelPowerA->SetLabel(0, "OFF");
		pControlPanelPowerA->SetLabel(1, "ON");

		Add(pControlPanelPowerB = new StdSwitch2(_sts, "CONTROL PANEL POWER B"));
		pControlPanelPowerB->SetLabel(0, "OFF");
		pControlPanelPowerB->SetLabel(1, "ON");

		Add(pControlPanelPowerC = new StdSwitch2(_sts, "CONTROL PANEL POWER C"));
		pControlPanelPowerC->SetLabel(0, "OFF");
		pControlPanelPowerC->SetLabel(1, "ON");

		Add(pHeatersDCUPowerH1 = new StdSwitch2(_sts, "HEATERS/DCU POWER H1"));
		pHeatersDCUPowerH1->SetLabel(0, "OFF");
		pHeatersDCUPowerH1->SetLabel(1, "ON");

		Add(pHeatersDCUPowerH2DCU = new StdSwitch2(_sts, "HEATERS/DCU POWER H2/DCU"));
		pHeatersDCUPowerH2DCU->SetLabel(0, "OFF");
		pHeatersDCUPowerH2DCU->SetLabel(1, "ON");

		Add(pHeatersDCUPowerH3DCU = new StdSwitch2(_sts, "HEATERS/DCU POWER H3/DCU"));
		pHeatersDCUPowerH3DCU->SetLabel(0, "OFF");
		pHeatersDCUPowerH3DCU->SetLabel(1, "ON");

		Add(pAPDSPowerA = new StdSwitch2(_sts, "APDS POWER ADS"));
		pAPDSPowerA->SetLabel(0, "OFF");
		pAPDSPowerA->SetLabel(1, "ON");

		Add(pAPDSPowerB = new StdSwitch2(_sts, "APDS POWER BDS"));
		pAPDSPowerB->SetLabel(0, "OFF");
		pAPDSPowerB->SetLabel(1, "ON");

		Add(pAPDSPowerC = new StdSwitch2(_sts, "APDS POWER CDS"));
		pAPDSPowerC->SetLabel(0, "OFF");
		pAPDSPowerC->SetLabel(1, "ON");


		Add(pPyrosAp = new StdSwitch2(_sts, "PYROS Ap"));
		pPyrosAp->SetLabel( 0, "OFF" );
		pPyrosAp->SetLabel( 1, "ON" );

		Add(pPyrosBp = new StdSwitch2(_sts, "PYROS Bp"));
		pPyrosBp->SetLabel( 0, "OFF" );
		pPyrosBp->SetLabel( 1, "ON" );

		Add(pPyrosCp = new StdSwitch2(_sts, "PYROS Cp"));
		pPyrosCp->SetLabel( 0, "OFF" );
		pPyrosCp->SetLabel( 1, "ON" );


		Add(pLampTest = new PushButton(_sts, "LAMP TEST"));
		Add(pPowerOn = new PushButton(_sts, "APDS CONTROL COMMANDS POWER ON"));
		Add(pPowerOff = new PushButton(_sts, "APDS CONTROL COMMANDS POWER OFF"));
		Add(pRingOut = new PushButton(_sts, "APDS CONTROL COMMANDS RING OUT"));
		Add(pRingIn = new PushButton(_sts, "APDS CONTROL COMMANDS RING IN"));
		Add(pAPDSCircProtOff = new PushButton(_sts, "APDS CONTROL COMMANDS APDS CIRC PROT OFF"));
		Add(pCloseHooks = new PushButton(_sts, "APDS CONTROL COMMANDS CLOSE HOOKS"));
		Add(pCloseLatches = new PushButton(_sts, "APDS CONTROL COMMANDS CLOSE LATCHES"));
		Add(pFixerOff = new PushButton(_sts, "APDS CONTROL COMMANDS FIXER OFF"));

		Add( pPyroCommands = new StandardSwitchCover( _sts, "PYRO COMMANDS" ) );
		Add( pAPDSControlCommands = new StandardSwitchCover( _sts, "APDS CONTROL COMMANDS" ) );

		Add( pPyroCircProtOff = new PushButton( _sts, "PYRO CIRC PROT OFF" ) );
		Add( pPyroCircProtOn = new PushButton( _sts, "PYRO CIRC PROT ON" ) );
		Add( pActHooksFiring = new PushButton( _sts, "ACT HOOKS FIRING" ) );
		Add( pPasHooksFiring = new PushButton( _sts, "PAS HOOKS FIRING" ) );
		Add( pOpenHooks = new PushButton( _sts, "OPEN HOOKS" ) );
		Add( pOpenLatches = new PushButton( _sts, "OPEN LATCHES" ) );
		Add( pUndocking = new PushButton( _sts, "UNDOCKING" ) );
	}

	PanelA8A3::~PanelA8A3()
	{
	}

	void PanelA8A3::Realize()
	{
		//Define switch connections

		oapiWriteLog( "Panel A8A3:\tRealize()" );

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_A", 16 );
		for (int i = 0; i < 16; i++) lightoutput[i].Connect( pBundle, i );
		plPowerOn->ConnectLight( 0, pBundle, 0 );
		plAPDSProtectCircOff->ConnectLight( 0, pBundle, 1 );
		plRingAligned->ConnectLight( 0, pBundle, 2 );
		plRingInitialPos->ConnectLight( 0, pBundle, 3 );
		plFixersOff->ConnectLight( 0, pBundle, 4 );
		plHooks1Open->ConnectLight( 0, pBundle, 5 );
		plHooks2Open->ConnectLight( 0, pBundle, 6 );
		plLatchesClosed->ConnectLight( 0, pBundle, 7 );
		plUndockComplete->ConnectLight( 0, pBundle, 8 );
		plInitialContact->ConnectLight( 0, pBundle, 9 );
		plCapture->ConnectLight( 0, pBundle, 10 );
		plRingForward->ConnectLight( 0, pBundle, 11 );
		plReadyToHook->ConnectLight( 0, pBundle, 12 );
		plInterfSealed->ConnectLight( 0, pBundle, 13 );
		plHooks1Closed->ConnectLight( 0, pBundle, 14 );
		plHooks2Closed->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_B", 16 );
		for (int i = 16; i < 19; i++) lightoutput[i].Connect( pBundle, i - 16 );
		lighttest.Connect( pBundle, 3 );
		plLatchesOpen->ConnectLight( 0, pBundle, 0 );
		plRingFinal->ConnectLight( 0, pBundle, 1 );
		pPyroProtectCircuitOff->ConnectLight( 0, pBundle, 2 );
		pLampTest->output.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle("DSCU_TO_PANELA8A3_A", 16);
		for (int i = 0; i < 16; i++) lightcmd[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle("DSCU_TO_PANELA8A3_B", 16);
		for (int i = 16; i < 19; i++) lightcmd[i].Connect( pBundle, i - 16 );
		plADS->ConnectLight( 0, pBundle, 3 );
		plBDS->ConnectLight( 0, pBundle, 4 );
		plCDS->ConnectLight( 0, pBundle, 5 );
		plAp->ConnectLight( 0, pBundle, 6 );
		plBp->ConnectLight( 0, pBundle, 7 );
		plCp->ConnectLight( 0, pBundle, 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_TO_DSCU_A", 16 );// PBs
		pPowerOn->output.Connect( pBundle, 0 );
		pPowerOff->output.Connect( pBundle, 1 );
		pRingOut->output.Connect( pBundle, 2 );
		pRingIn->output.Connect( pBundle, 3 );
		pAPDSCircProtOff->output.Connect( pBundle, 4 );
		pCloseHooks->output.Connect( pBundle, 5 );
		pCloseLatches->output.Connect( pBundle, 6 );
		pFixerOff->output.Connect( pBundle, 7 );
		pPyroCircProtOff->output.Connect( pBundle, 8 );
		pPyroCircProtOn->output.Connect( pBundle, 9 );
		pActHooksFiring->output.Connect( pBundle, 10 );
		pPasHooksFiring->output.Connect( pBundle, 11 );
		pOpenHooks->output.Connect( pBundle, 12 );
		pOpenLatches->output.Connect( pBundle, 13 );
		pUndocking->output.Connect( pBundle, 14 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_TO_DSCU_B", 16 );// CBs
		pControlPanelPowerA->ConnectPort( 1, pBundle, 0 );
		pControlPanelPowerB->ConnectPort( 1, pBundle, 1 );
		pControlPanelPowerC->ConnectPort( 1, pBundle, 2 );
		pHeatersDCUPowerH1->ConnectPort( 1, pBundle, 3 );
		pHeatersDCUPowerH2DCU->ConnectPort( 1, pBundle, 4 );
		pHeatersDCUPowerH3DCU->ConnectPort( 1, pBundle, 5 );
		pAPDSPowerA->ConnectPort( 1, pBundle, 6 );
		pAPDSPowerB->ConnectPort( 1, pBundle, 7 );
		pAPDSPowerC->ConnectPort( 1, pBundle, 8 );
		pPyrosAp->ConnectPort( 1, pBundle, 9 );
		pPyrosBp->ConnectPort( 1, pBundle, 10 );
		pPyrosCp->ConnectPort( 1, pBundle, 11 );
		CNTL_PNL_A.Connect( pBundle, 0 );
		CNTL_PNL_V.Connect( pBundle, 2 );

		AtlantisPanel::Realize();

		oapiWriteLog("Panel A8A3:\tRealize done.");
	}

	void PanelA8A3::DefineVC()
	{
		oapiWriteLog( "Panel A8A3:\tDefine VC" );
		//Define VC regions
		AddAIDToMouseEventList( AID_A8A3 );

		plADS->DefineMeshGroup( GetVCMeshIndex(), GRP_ADS_A8A3_VC );
		plADS->SetStateOffset( 1, -0.342773f, 0.0f );
		plADS->SetDefaultState( 1 );

		plBDS->DefineMeshGroup( GetVCMeshIndex(), GRP_BDS_A8A3_VC );
		plBDS->SetStateOffset( 1, -0.342773f, 0.0f );
		plBDS->SetDefaultState( 1 );

		plCDS->DefineMeshGroup( GetVCMeshIndex(), GRP_CDS_A8A3_VC );
		plCDS->SetStateOffset( 1, -0.342773f, 0.0f );
		plCDS->SetDefaultState( 1 );


		plPowerOn->DefineMeshGroup( GetVCMeshIndex(), GRP_POWER_ON_A8A3_VC );
		plPowerOn->SetStateOffset( 1, -0.342773f, 0.0f );
		plPowerOn->SetDefaultState( 1 );

		plAPDSProtectCircOff->DefineMeshGroup( GetVCMeshIndex(), GRP_APDS_CIRC_PROT_OFF_A8A3_VC );
		plAPDSProtectCircOff->SetStateOffset( 1, -0.342773f, 0.0f );
		plAPDSProtectCircOff->SetDefaultState( 1 );

		plRingAligned->DefineMeshGroup( GetVCMeshIndex(), GRP_RING_ALIGNED_A8A3_VC );
		plRingAligned->SetStateOffset( 1, -0.342773f, 0.0f );
		plRingAligned->SetDefaultState( 1 );

		plRingInitialPos->DefineMeshGroup( GetVCMeshIndex(), GRP_RING_INITIAL_POS_A8A3_VC );
		plRingInitialPos->SetStateOffset( 1, -0.342773f, 0.0f );
		plRingInitialPos->SetDefaultState( 1 );

		plFixersOff->DefineMeshGroup( GetVCMeshIndex(), GRP_FIXERS_OFF_A8A3_VC );
		plFixersOff->SetStateOffset( 1, -0.342773f, 0.0f );
		plFixersOff->SetDefaultState( 1 );

		plHooks1Open->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS1_OPEN_A8A3_VC );
		plHooks1Open->SetStateOffset( 1, -0.342773f, 0.0f );
		plHooks1Open->SetDefaultState( 1 );

		plHooks2Open->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS2_OPEN_A8A3_VC );
		plHooks2Open->SetStateOffset( 1, -0.342773f, 0.0f );
		plHooks2Open->SetDefaultState( 1 );

		plLatchesClosed->DefineMeshGroup( GetVCMeshIndex(), GRP_LATCHES_CLOSED_A8A3_VC );
		plLatchesClosed->SetStateOffset( 1, -0.342773f, 0.0f );
		plLatchesClosed->SetDefaultState( 1 );

		plUndockComplete->DefineMeshGroup( GetVCMeshIndex(), GRP_UNDOCK_COMPLET_A8A3_VC );
		plUndockComplete->SetStateOffset( 1, -0.342773f, 0.0f );
		plUndockComplete->SetDefaultState( 1 );

		plInitialContact->DefineMeshGroup( GetVCMeshIndex(), GRP_INITIAL_CONTACT_A8A3_VC );
		plInitialContact->SetStateOffset( 1, -0.342773f, 0.0f );
		plInitialContact->SetDefaultState( 1 );

		plCapture->DefineMeshGroup( GetVCMeshIndex(), GRP_CAPTURE_A8A3_VC );
		plCapture->SetStateOffset( 1, -0.342773f, 0.0f );
		plCapture->SetDefaultState( 1 );

		plRingForward->DefineMeshGroup( GetVCMeshIndex(), GRP_RING_FORWARD_POS_A8A3_VC );
		plRingForward->SetStateOffset( 1, -0.342773f, 0.0f );
		plRingForward->SetDefaultState( 1 );

		plReadyToHook->DefineMeshGroup( GetVCMeshIndex(), GRP_READY_TO_HOOK_A8A3_VC );
		plReadyToHook->SetStateOffset( 1, -0.342773f, 0.0f );
		plReadyToHook->SetDefaultState( 1 );

		plInterfSealed->DefineMeshGroup( GetVCMeshIndex(), GRP_INTERF_SEALED_A8A3_VC );
		plInterfSealed->SetStateOffset( 1, -0.342773f, 0.0f );
		plInterfSealed->SetDefaultState( 1 );

		plHooks1Closed->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS1_CLOSED_A8A3_VC );
		plHooks1Closed->SetStateOffset( 1, -0.342773f, 0.0f );
		plHooks1Closed->SetDefaultState( 1 );

		plHooks2Closed->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS2_CLOSED_A8A3_VC );
		plHooks2Closed->SetStateOffset( 1, -0.342773f, 0.0f );
		plHooks2Closed->SetDefaultState( 1 );

		plLatchesOpen->DefineMeshGroup( GetVCMeshIndex(), GRP_LATCHES_OPEN_A8A3_VC );
		plLatchesOpen->SetStateOffset( 1, -0.342773f, 0.0f );
		plLatchesOpen->SetDefaultState( 1 );

		plRingFinal->DefineMeshGroup( GetVCMeshIndex(), GRP_RING_FINAL_POS_A8A3_VC );
		plRingFinal->SetStateOffset( 1, -0.342773f, 0.0f );
		plRingFinal->SetDefaultState( 1 );

		plAp->DefineMeshGroup( GetVCMeshIndex(), GRP_AP_A8A3_VC );
		plAp->SetStateOffset( 1, 0.0f, 0.199219f );

		plBp->DefineMeshGroup( GetVCMeshIndex(), GRP_BP_A8A3_VC );
		plBp->SetStateOffset( 1, 0.0f, 0.199219f );

		plCp->DefineMeshGroup( GetVCMeshIndex(), GRP_CP_A8A3_VC );
		plCp->SetStateOffset( 1, 0.0f, 0.199219f );

		pPyroProtectCircuitOff->DefineMeshGroup( GetVCMeshIndex(), GRP_PYROPROTECTCIRCUITOFF_A8A3_VC );
		pPyroProtectCircuitOff->SetStateOffset( 1, 0.0f, 0.199219f );


		pControlPanelPowerA->SetMouseRegion( AID_A8A3, 0.078607f, 0.121607f, 0.097529f, 0.202774f );
		pControlPanelPowerA->SetReference(_V(0.0, 2.443722, 12.41595), _V(-1.0, 0.0, 0.0));
		pControlPanelPowerA->DefineGroup(GRP_S1_A8A3_VC);

		pControlPanelPowerB->SetMouseRegion( AID_A8A3, 0.175489f, 0.123035f, 0.194648f, 0.204244f );
		pControlPanelPowerB->SetReference(_V(0.0, 2.443722, 12.41595), _V(-1.0, 0.0, 0.0));
		pControlPanelPowerB->DefineGroup(GRP_S2_A8A3_VC);

		pControlPanelPowerC->SetMouseRegion( AID_A8A3, 0.271936f, 0.122135f, 0.291739f, 0.203266f );
		pControlPanelPowerC->SetReference(_V(0.0, 2.443722, 12.41595), _V(-1.0, 0.0, 0.0));
		pControlPanelPowerC->DefineGroup(GRP_S3_A8A3_VC);

		pHeatersDCUPowerH1->SetMouseRegion( AID_A8A3, 0.078266f, 0.315846f, 0.097893f, 0.396873f );
		pHeatersDCUPowerH1->SetReference(_V(0.0, 2.370605, 12.43914), _V(-1.0, 0.0, 0.0));
		pHeatersDCUPowerH1->DefineGroup(GRP_S4_A8A3_VC);

		pHeatersDCUPowerH2DCU->SetMouseRegion( AID_A8A3, 0.175297f, 0.316582f, 0.194602f, 0.397552f );
		pHeatersDCUPowerH2DCU->SetReference(_V(0.0, 2.370605, 12.43914),_V(-1.0, 0.0, 0.0));
		pHeatersDCUPowerH2DCU->DefineGroup(GRP_S5_A8A3_VC);

		pHeatersDCUPowerH3DCU->SetMouseRegion( AID_A8A3, 0.271984f, 0.315340f, 0.291396f, 0.397430f );
		pHeatersDCUPowerH3DCU->SetReference(_V(0.0, 2.370605, 12.43914), _V(-1.0, 0.0, 0.0));
		pHeatersDCUPowerH3DCU->DefineGroup(GRP_S6_A8A3_VC);

		pAPDSPowerA->SetMouseRegion( AID_A8A3, 0.078492f, 0.510377f, 0.097095f, 0.591183f );
		pAPDSPowerA->SetReference(_V(0.0,  2.297854, 12.46215), _V(-1.0, 0.0, 0.0));
		pAPDSPowerA->DefineGroup(GRP_S7_A8A3_VC);

		pAPDSPowerB->SetMouseRegion( AID_A8A3, 0.175082f, 0.510769f, 0.194313f, 0.590632f );
		pAPDSPowerB->SetReference(_V(0.0,  2.297854, 12.46215), _V(-1.0, 0.0, 0.0));
		pAPDSPowerB->DefineGroup(GRP_S8_A8A3_VC);

		pAPDSPowerC->SetMouseRegion( AID_A8A3, 0.271967f, 0.509268f, 0.291367f, 0.591272f );
		pAPDSPowerC->SetReference(_V(0.0,  2.297854, 12.46215), _V(-1.0, 0.0, 0.0));
		pAPDSPowerC->DefineGroup(GRP_S9_A8A3_VC);

		pPyrosAp->SetMouseRegion( AID_A8A3, 0.706286f, 0.120643f, 0.725018f, 0.203573f );
		pPyrosAp->SetReference(_V(0.0, 2.443722, 12.41595), _V(-1.0, 0.0, 0.0));
		pPyrosAp->DefineGroup(GRP_S10_A8A3_VC);

		pPyrosBp->SetMouseRegion( AID_A8A3, 0.802748f, 0.123284f, 0.821752f, 0.204392f );
		pPyrosBp->SetReference(_V(0.0, 2.443722, 12.41595), _V(-1.0, 0.0, 0.0));
		pPyrosBp->DefineGroup(GRP_S11_A8A3_VC);

		pPyrosCp->SetMouseRegion( AID_A8A3, 0.899503f, 0.122141f, 0.918277f, 0.203744f );
		pPyrosCp->SetReference(_V(0.0, 2.443722, 12.41595), _V(-1.0, 0.0, 0.0));
		pPyrosCp->DefineGroup(GRP_S12_A8A3_VC);

		const VECTOR3 PB_VECTOR = _V( 0.0, -0.224951, -0.974370 );

		pLampTest->SetMouseRegion( AID_A8A3, 0.143f, 0.792f, 0.225f, 0.853f);
		pLampTest->DefineGroup(GRP_LAMPTEST_A8A3_VC);
		pLampTest->SetDirection(PB_VECTOR);
		pLampTest->SetMotionLength( 0.004 );

		pPowerOn->SetMouseRegion( AID_A8A3, 0.625f, 0.787f, 0.708f, 0.851f);
		pPowerOn->DefineGroup(GRP_APDSCC_POWERON_A8A3_VC);
		pPowerOn->SetDirection(PB_VECTOR);
		pPowerOn->SetMotionLength( 0.004 );

		pPowerOff->SetMouseRegion( AID_A8A3, 0.708f, 0.787f, 0.7875f, 0.851f);
		pPowerOff->DefineGroup(GRP_APDSCC_POWEROFF_A8A3_VC);
		pPowerOff->SetDirection(PB_VECTOR);
		pPowerOff->SetMotionLength( 0.004 );

		pRingOut->SetMouseRegion( AID_A8A3, 0.7875f, 0.787f, 0.8674f, 0.851f);
		pRingOut->DefineGroup(GRP_APDSCC_RINGOUT_A8A3_VC);
		pRingOut->SetDirection(PB_VECTOR);
		pRingOut->SetMotionLength( 0.004 );

		pRingIn->SetMouseRegion( AID_A8A3, 0.8674f, 0.787f, 0.949f, 0.851f);
		pRingIn->DefineGroup(GRP_APDSCC_RINGIN_A8A3_VC);
		pRingIn->SetDirection(PB_VECTOR);
		pRingIn->SetMotionLength( 0.004 );

		pAPDSCircProtOff->SetMouseRegion( AID_A8A3, 0.625f, 0.903f, 0.708f, 0.962f);
		pAPDSCircProtOff->DefineGroup(GRP_APDSCC_APDS_CIRC_PROT_OFF_A8A3_VC);
		pAPDSCircProtOff->SetDirection(PB_VECTOR);
		pAPDSCircProtOff->SetMotionLength( 0.004 );

		pCloseHooks->SetMouseRegion( AID_A8A3, 0.708f, 0.903f, 0.7875f, 0.962f);
		pCloseHooks->DefineGroup(GRP_APDSCC_CLOSEHOOKS_A8A3_VC);
		pCloseHooks->SetDirection(PB_VECTOR);
		pCloseHooks->SetMotionLength( 0.004 );

		pCloseLatches->SetMouseRegion( AID_A8A3, 0.7875f, 0.903f, 0.8674f, 0.962f);
		pCloseLatches->DefineGroup(GRP_APDSCC_CLOSELATCHES_A8A3_VC);
		pCloseLatches->SetDirection(PB_VECTOR);
		pCloseLatches->SetMotionLength( 0.004 );

		pFixerOff->SetMouseRegion( AID_A8A3, 0.8674f, 0.903f, 0.949f, 0.962f);
		pFixerOff->DefineGroup(GRP_APDSCC_FIXEROFF_A8A3_VC);
		pFixerOff->SetDirection(PB_VECTOR);
		pFixerOff->SetMotionLength( 0.004 );

		pPyroCommands->SetMouseRegion( AID_A8A3, 0, 0.716620f, 0.422147f, 0.911504f, 0.555984f );
		pPyroCommands->SetMouseRegion( AID_A8A3, 1, 0.921100f, 0.432651f, 0.951956f, 0.548972f );
		pPyroCommands->SetReference( _V( -0.2320, 2.3437, 12.4556 ), _V( 0.0, -0.9499, 0.3126 ) );
		pPyroCommands->DefineGroup( GRP_PLATEGUARD1_A8A3_VC );

		pAPDSControlCommands->SetMouseRegion( AID_A8A3, 0, 0.716260f, 0.572989f, 0.901355f, 0.712548f );
		pAPDSControlCommands->SetMouseRegion( AID_A8A3, 1, 0.924516f, 0.581548f, 0.950181f, 0.694610f );
		pAPDSControlCommands->SetReference( _V( -0.2320, 2.3437, 12.4556 ), _V( 0.0, -0.9499, 0.3126 ) );
		pAPDSControlCommands->DefineGroup( GRP_PLATEGUARD2_A8A3_VC );

		pPyroCircProtOff->SetMouseRegion( AID_A8A3, 0.753635f, 0.449135f, 0.806399f, 0.484442f );
		pPyroCircProtOff->DefineGroup( GRP_PYRO_CIRC_PROT_OFF_A8A3_VC );
		pPyroCircProtOff->SetDirection( PB_VECTOR );
		pPyroCircProtOff->SetMotionLength( 0.004 );

		pPyroCircProtOn->SetMouseRegion( AID_A8A3, 0.816807f, 0.448902f, 0.868185f, 0.483662f );
		pPyroCircProtOn->DefineGroup( GRP_PYRO_CIRC_PROT_ON_A8A3_VC );
		pPyroCircProtOn->SetDirection( PB_VECTOR );
		pPyroCircProtOn->SetMotionLength( 0.004 );

		pActHooksFiring->SetMouseRegion( AID_A8A3, 0.753999f, 0.497091f, 0.805913f, 0.530741f );
		pActHooksFiring->DefineGroup( GRP_ACT_HOOKS_FIRING_A8A3_VC );
		pActHooksFiring->SetDirection( PB_VECTOR );
		pActHooksFiring->SetMotionLength( 0.004 );

		pPasHooksFiring->SetMouseRegion( AID_A8A3, 0.816745f, 0.497108f, 0.868219f, 0.530819f );
		pPasHooksFiring->DefineGroup( GRP_PAS_HOOKS_FIRING_A8A3_VC );
		pPasHooksFiring->SetDirection( PB_VECTOR );
		pPasHooksFiring->SetMotionLength( 0.004 );

		pOpenHooks->SetMouseRegion( AID_A8A3, 0.754024f, 0.600301f, 0.806527f, 0.634483f );
		pOpenHooks->DefineGroup( GRP_OPEN_HOOKS_A8A3_VC );
		pOpenHooks->SetDirection( PB_VECTOR );
		pOpenHooks->SetMotionLength( 0.004 );

		pOpenLatches->SetMouseRegion( AID_A8A3, 0.816430f, 0.600107f, 0.868482f, 0.634369f );
		pOpenLatches->DefineGroup( GRP_OPEN_LATCHES_A8A3_VC );
		pOpenLatches->SetDirection( PB_VECTOR );
		pOpenLatches->SetMotionLength( 0.004 );

		pUndocking->SetMouseRegion( AID_A8A3, 0.815996f, 0.647695f, 0.868637f, 0.683079f );
		pUndocking->DefineGroup( GRP_UNDOCKING_A8A3_VC );
		pUndocking->SetDirection( PB_VECTOR );
		pUndocking->SetMotionLength( 0.004 );
		return;
	}

	void PanelA8A3::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_A8A3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A8A3,
			_V( 0.254716, 2.5048, 12.3991 ) + ofs, _V( -0.265916, 2.5048, 12.3991 ) + ofs,
			_V( 0.254716, 2.12746, 12.5176 ) + ofs, _V( -0.265916, 2.12746, 12.5176 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelA8A3::OnPostStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPostStep( simt, simdt, mjd );

		if (lighttest.IsSet() && (CNTL_PNL_A.IsSet() || CNTL_PNL_V.IsSet()))
		{
			for (int i = 0; i < 19; i++) lightoutput[i].SetLine();
		}
		else
		{
			for (int i = 0; i < 19; i++) lightoutput[i].SetLine( (int)lightcmd[i].IsSet() * 5.0f );
		}
		return;
	}
};
