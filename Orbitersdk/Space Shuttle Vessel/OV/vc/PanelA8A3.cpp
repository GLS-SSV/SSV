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
2022/09/29   GLS
2022/10/04   GLS
2023/12/20   GLS
2024/02/11   GLS
********************************************/
#include "PanelA8A3.h"
#include "StandardSwitch.h"
#include "PushButton.h"
#include "StandardLight.h"
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include <DiscreteBundleManager.h>
#include "../meshres_vc_a8a3.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelA8A3";
	constexpr VECTOR3 OFFSET_PANEL = {-0.265916, 2.12746, 12.5176};

	using namespace discsignals;


	PanelA8A3::PanelA8A3( Atlantis* _sts, bool defaultposition ): AtlantisPanel( _sts, defaultposition ? "A8" : "A7L" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( plADS = new StandardSingleLight( _sts, "APDS POWER ADS LT" ) );
		Add( plBDS = new StandardSingleLight( _sts, "APDS POWER BDS LT" ) );
		Add( plCDS = new StandardSingleLight( _sts, "APDS POWER CDS LT" ) );

		Add( plPowerOn_A = new StandardSingleLight( _sts, "POWER ON A LT" ) );
		Add( plPowerOn_C = new StandardSingleLight( _sts, "POWER ON C LT" ) );
		Add( plAPDSCircuitProtectOff_A = new StandardSingleLight( _sts, "APDS CIRCUIT PROTECT OFF A LT" ) );
		Add( plAPDSCircuitProtectOff_C = new StandardSingleLight( _sts, "APDS CIRCUIT PROTECT OFF C LT" ) );
		Add( plRingAligned_A = new StandardSingleLight( _sts, "RING ALIGNED A LT" ) );
		Add( plRingAligned_C = new StandardSingleLight( _sts, "RING ALIGNED C LT" ) );
		Add( plRingInitialPosition_A = new StandardSingleLight( _sts, "RING INITIAL POSITION A LT" ) );
		Add( plRingInitialPosition_C = new StandardSingleLight( _sts, "RING INITIAL POSITION C LT" ) );
		Add( plFixersOff_A = new StandardSingleLight( _sts, "FIXERS OFF A LT" ) );
		Add( plFixersOff_C = new StandardSingleLight( _sts, "FIXERS OFF C LT" ) );
		Add( plHooks1Open_A = new StandardSingleLight( _sts, "HOOKS 1 OPEN A LT" ) );
		Add( plHooks1Open_C = new StandardSingleLight( _sts, "HOOKS 1 OPEN C LT" ) );
		Add( plHooks2Open_A = new StandardSingleLight( _sts, "HOOKS 2 OPEN A LT" ) );
		Add( plHooks2Open_C = new StandardSingleLight( _sts, "HOOKS 2 OPEN C LT" ) );
		Add( plLatchesClosed_A = new StandardSingleLight( _sts, "LATCHES CLOSED A LT" ) );
		Add( plLatchesClosed_C = new StandardSingleLight( _sts, "LATCHES CLOSED C LT" ) );
		Add( plUndockComplet_A = new StandardSingleLight( _sts, "UNDOCK COMPLET A LT" ) );
		Add( plUndockComplet_C = new StandardSingleLight( _sts, "UNDOCK COMPLET C LT" ) );

		Add( plInitialContact_A = new StandardSingleLight( _sts, "INITIAL CONTACT A LT" ) );
		Add( plInitialContact_C = new StandardSingleLight( _sts, "INITIAL CONTACT C LT" ) );
		Add( plCaptureCapture_A = new StandardSingleLight( _sts, "CAPTURE CAPTURE A LT" ) );
		Add( plCaptureCapture_C = new StandardSingleLight( _sts, "CAPTURE CAPTURE C LT" ) );
		Add( plRingForwardPosition_A = new StandardSingleLight( _sts, "RING FORWARD POSITION A LT" ) );
		Add( plRingForwardPosition_C = new StandardSingleLight( _sts, "RING FORWARD POSITION C LT" ) );
		Add( plReadyToHook_A = new StandardSingleLight( _sts, "READY TO HOOK A LT" ) );
		Add( plReadyToHook_C = new StandardSingleLight( _sts, "READY TO HOOK C LT" ) );
		Add( plInterfSealed_A = new StandardSingleLight( _sts, "INTERF SEALED A LT" ) );
		Add( plInterfSealed_C = new StandardSingleLight( _sts, "INTERF SEALED C LT" ) );
		Add( plHooks1Closed_A = new StandardSingleLight( _sts, "HOOKS 1 CLOSED A LT" ) );
		Add( plHooks1Closed_C = new StandardSingleLight( _sts, "HOOKS 1 CLOSED C LT" ) );
		Add( plHooks2Closed_A = new StandardSingleLight( _sts, "HOOKS 2 CLOSED A LT" ) );
		Add( plHooks2Closed_C = new StandardSingleLight( _sts, "HOOKS 2 CLOSED C LT" ) );
		Add( plLatchesOpen_A = new StandardSingleLight( _sts, "LATCHES OPEN A LT" ) );
		Add( plLatchesOpen_C = new StandardSingleLight( _sts, "LATCHES OPEN C LT" ) );
		Add( plRingFinalPosition_A = new StandardSingleLight( _sts, "RING FINAL POSITION A LT" ) );
		Add( plRingFinalPosition_C = new StandardSingleLight( _sts, "RING FINAL POSITION C LT" ) );

		Add( plAp = new StandardSingleLight( _sts, "PYROS Ap LT" ) );
		Add( plBp = new StandardSingleLight( _sts, "PYROS Bp LT" ) );
		Add( plCp = new StandardSingleLight( _sts, "PYROS Cp LT" ) );

		Add( plPyroCircuitProtectOff_A = new StandardSingleLight( _sts, "PYRO CIRCUIT PROTECT OFF A LT" ) );
		Add( plPyroCircuitProtectOff_C = new StandardSingleLight( _sts, "PYRO CIRCUIT PROTECT OFF C LT" ) );

		Add( pControlPanelPowerA = new StdSwitch2( _sts, "CONTROL PANEL POWER A" ) );
		pControlPanelPowerA->SetLabel( 0, "OFF" );
		pControlPanelPowerA->SetLabel( 1, "ON" );

		Add( pControlPanelPowerB = new StdSwitch2( _sts, "CONTROL PANEL POWER B" ) );
		pControlPanelPowerB->SetLabel( 0, "OFF" );
		pControlPanelPowerB->SetLabel( 1, "ON" );

		Add( pControlPanelPowerC = new StdSwitch2( _sts, "CONTROL PANEL POWER C" ) );
		pControlPanelPowerC->SetLabel( 0, "OFF" );
		pControlPanelPowerC->SetLabel( 1, "ON" );

		Add( pHeatersDCUPowerH1 = new StdSwitch2( _sts, "HEATERS/DCU POWER H1" ) );
		pHeatersDCUPowerH1->SetLabel( 0, "OFF" );
		pHeatersDCUPowerH1->SetLabel( 1, "ON" );

		Add( pHeatersDCUPowerH2DCU = new StdSwitch2( _sts, "HEATERS/DCU POWER H2/DCU" ) );
		pHeatersDCUPowerH2DCU->SetLabel( 0, "OFF" );
		pHeatersDCUPowerH2DCU->SetLabel( 1, "ON" );

		Add( pHeatersDCUPowerH3DCU = new StdSwitch2( _sts, "HEATERS/DCU POWER H3/DCU" ) );
		pHeatersDCUPowerH3DCU->SetLabel( 0, "OFF" );
		pHeatersDCUPowerH3DCU->SetLabel( 1, "ON" );

		Add( pAPDSPowerA = new StdSwitch2( _sts, "APDS POWER ADS" ) );
		pAPDSPowerA->SetLabel( 0, "OFF" );
		pAPDSPowerA->SetLabel( 1, "ON" );

		Add( pAPDSPowerB = new StdSwitch2( _sts, "APDS POWER BDS" ) );
		pAPDSPowerB->SetLabel( 0, "OFF" );
		pAPDSPowerB->SetLabel( 1, "ON" );

		Add( pAPDSPowerC = new StdSwitch2( _sts, "APDS POWER CDS" ) );
		pAPDSPowerC->SetLabel( 0, "OFF" );
		pAPDSPowerC->SetLabel( 1, "ON" );


		Add( pPyrosAp = new StdSwitch2( _sts, "PYROS Ap" ) );
		pPyrosAp->SetLabel( 0, "OFF" );
		pPyrosAp->SetLabel( 1, "ON" );

		Add( pPyrosBp = new StdSwitch2( _sts, "PYROS Bp" ) );
		pPyrosBp->SetLabel( 0, "OFF" );
		pPyrosBp->SetLabel( 1, "ON" );

		Add( pPyrosCp = new StdSwitch2( _sts, "PYROS Cp" ) );
		pPyrosCp->SetLabel( 0, "OFF" );
		pPyrosCp->SetLabel( 1, "ON" );


		Add( pLampTest = new PushButton( _sts, "LAMP TEST" ) );
		Add( pPowerOn = new PushButton( _sts, "APDS CONTROL COMMANDS POWER ON" ) );
		Add( pPowerOff = new PushButton( _sts, "APDS CONTROL COMMANDS POWER OFF" ) );
		Add( pRingOut = new PushButton( _sts, "APDS CONTROL COMMANDS RING OUT" ) );
		Add( pRingIn = new PushButton( _sts, "APDS CONTROL COMMANDS RING IN" ) );
		Add( pAPDSCircProtOff = new PushButton( _sts, "APDS CONTROL COMMANDS APDS CIRC PROT OFF" ) );
		Add( pCloseHooks = new PushButton( _sts, "APDS CONTROL COMMANDS CLOSE HOOKS" ) );
		Add( pCloseLatches = new PushButton( _sts, "APDS CONTROL COMMANDS CLOSE LATCHES" ) );
		Add( pFixerOff = new PushButton( _sts, "APDS CONTROL COMMANDS FIXER OFF" ) );

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

	void PanelA8A3::Realize( void )
	{
		//Define switch connections

		oapiWriteLog( "Panel A8A3:\tRealize()" );

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_A", 16 );
		for (int i = 0; i < 16; i++) lightoutput[i].Connect( pBundle, i );
		plPowerOn_A->ConnectLight( 0, pBundle, 0 );
		plPowerOn_C->ConnectLight( 0, pBundle, 1 );
		plAPDSCircuitProtectOff_A->ConnectLight( 0, pBundle, 2 );
		plAPDSCircuitProtectOff_C->ConnectLight( 0, pBundle, 3 );
		plRingAligned_A->ConnectLight( 0, pBundle, 4 );
		plRingAligned_C->ConnectLight( 0, pBundle, 5 );
		plRingInitialPosition_A->ConnectLight( 0, pBundle, 6 );
		plRingInitialPosition_C->ConnectLight( 0, pBundle, 7 );
		plFixersOff_A->ConnectLight( 0, pBundle, 8 );
		plFixersOff_C->ConnectLight( 0, pBundle, 9 );
		plHooks1Open_A->ConnectLight( 0, pBundle, 10 );
		plHooks1Open_C->ConnectLight( 0, pBundle, 11 );
		plHooks2Open_A->ConnectLight( 0, pBundle, 12 );
		plHooks2Open_C->ConnectLight( 0, pBundle, 13 );
		plLatchesClosed_A->ConnectLight( 0, pBundle, 14 );
		plLatchesClosed_C->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_B", 16 );
		for (int i = 16; i < 32; i++) lightoutput[i].Connect( pBundle, i - 16 );
		plUndockComplet_A->ConnectLight( 0, pBundle, 0 );
		plUndockComplet_C->ConnectLight( 0, pBundle, 1 );
		plInitialContact_A->ConnectLight( 0, pBundle, 2 );
		plInitialContact_C->ConnectLight( 0, pBundle, 3 );
		plCaptureCapture_A->ConnectLight( 0, pBundle, 4 );
		plCaptureCapture_C->ConnectLight( 0, pBundle, 5 );
		plRingForwardPosition_A->ConnectLight( 0, pBundle, 6 );
		plRingForwardPosition_C->ConnectLight( 0, pBundle, 7 );
		plReadyToHook_A->ConnectLight( 0, pBundle, 8 );
		plReadyToHook_C->ConnectLight( 0, pBundle, 9 );
		plInterfSealed_A->ConnectLight( 0, pBundle, 10 );
		plInterfSealed_C->ConnectLight( 0, pBundle, 11 );
		plHooks1Closed_A->ConnectLight( 0, pBundle, 12 );
		plHooks1Closed_C->ConnectLight( 0, pBundle, 13 );
		plHooks2Closed_A->ConnectLight( 0, pBundle, 14 );
		plHooks2Closed_C->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_C", 16 );
		for (int i = 32; i < 38; i++) lightoutput[i].Connect( pBundle, i - 32 );
		lighttest.Connect( pBundle, 6 );
		plLatchesOpen_A->ConnectLight( 0, pBundle, 0 );
		plLatchesOpen_C->ConnectLight( 0, pBundle, 1 );
		plRingFinalPosition_A->ConnectLight( 0, pBundle, 2 );
		plRingFinalPosition_C->ConnectLight( 0, pBundle, 3 );
		plPyroCircuitProtectOff_A->ConnectLight( 0, pBundle, 4 );
		plPyroCircuitProtectOff_C->ConnectLight( 0, pBundle, 5 );
		pLampTest->Connect( pBundle, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "AVIONICS_TO_PANELA8A3_A", 16 );
		for (int i = 0; i < 16; i++) lightcmd[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "AVIONICS_TO_PANELA8A3_B", 16 );
		for (int i = 16; i < 32; i++) lightcmd[i].Connect( pBundle, i - 16 );

		pBundle = STS()->BundleManager()->CreateBundle( "AVIONICS_TO_PANELA8A3_C", 16 );
		for (int i = 32; i < 38; i++) lightcmd[i].Connect( pBundle, i - 32 );

		pBundle = STS()->BundleManager()->CreateBundle( "A8A3_internal", 16 );
		plADS->ConnectLight( 0, pBundle, 0 );
		plBDS->ConnectLight( 0, pBundle, 1 );
		plCDS->ConnectLight( 0, pBundle, 2 );
		plAp->ConnectLight( 0, pBundle, 3 );
		plBp->ConnectLight( 0, pBundle, 4 );
		plCp->ConnectLight( 0, pBundle, 5 );

		dopADS.Connect( pBundle, 0 );
		dopBDS.Connect( pBundle, 1 );
		dopCDS.Connect( pBundle, 2 );
		dopAp.Connect( pBundle, 3 );
		dopBp.Connect( pBundle, 4 );
		dopCp.Connect( pBundle, 5 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_TO_AVIONICS_A", 16 );// PBs
		pPowerOn->Connect( pBundle, 0 );
		pPowerOff->Connect( pBundle, 1 );
		pRingOut->Connect( pBundle, 2 );
		pRingIn->Connect( pBundle, 3 );
		pAPDSCircProtOff->Connect( pBundle, 4 );
		pCloseHooks->Connect( pBundle, 5 );
		pCloseLatches->Connect( pBundle, 6 );
		pFixerOff->Connect( pBundle, 7 );
		pPyroCircProtOff->Connect( pBundle, 8 );
		pPyroCircProtOn->Connect( pBundle, 9 );
		pActHooksFiring->Connect( pBundle, 10 );
		pPasHooksFiring->Connect( pBundle, 11 );
		pOpenHooks->Connect( pBundle, 12 );
		pOpenLatches->Connect( pBundle, 13 );
		pUndocking->Connect( pBundle, 14 );

		pBundle = STS()->BundleManager()->CreateBundle( "PANELA8A3_TO_AVIONICS_B", 16 );// CBs
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

		dipControlPanelPowerA.Connect( pBundle, 0 );
		dipControlPanelPowerB.Connect( pBundle, 1 );
		dipControlPanelPowerC.Connect( pBundle, 2 );
		dipAPDSPowerA.Connect( pBundle, 6 );
		dipAPDSPowerB.Connect( pBundle, 7 );
		dipAPDSPowerC.Connect( pBundle, 8 );
		dipPyrosAp.Connect( pBundle, 9 );
		dipPyrosBp.Connect( pBundle, 10 );
		dipPyrosCp.Connect( pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ODS_POWER", 16 );
		dipPNL_LOGIC_A.Connect( pBundle, 0 );
		dipPNL_LOGIC_B.Connect( pBundle, 1 );
		dipPNL_LOGIC_C.Connect( pBundle, 2 );
		dopCNTL_PNL_A.Connect( pBundle, 3 );
		dopCNTL_PNL_B.Connect( pBundle, 4 );
		dopCNTL_PNL_C.Connect( pBundle, 5 );
		dopPNLgnd.Connect( pBundle, 6 );
		dopWA.Connect( pBundle, 9 );
		dopWB.Connect( pBundle, 10 );
		dopWC.Connect( pBundle, 11 );
		dopCgnd.Connect( pBundle, 12 );

		AtlantisPanel::Realize();

		RunSignals();
		return;
	}

	void PanelA8A3::DefineVC( void )
	{
		const VECTOR3 switch_rot = _V( -1.0, 0.0, 0.0 );
		const VECTOR3 switch_rotV = _V( 0.0, -0.954060, 0.299615 );
		const VECTOR3 PB_VECTOR = _V( 0.0, -0.224951, -0.974370 );
		const double button_push_length = 0.004;

		//Define VC regions
		AddAIDToMouseEventList( AID_A8A3 );

		plADS->DefineMeshGroup( GetVCMeshIndex(), GRP_ADS_A8A3_VC );
		plADS->SetStateOffset( 1, 0.5f, 0.0f );

		plBDS->DefineMeshGroup( GetVCMeshIndex(), GRP_BDS_A8A3_VC );
		plBDS->SetStateOffset( 1, 0.5f, 0.0f );

		plCDS->DefineMeshGroup( GetVCMeshIndex(), GRP_CDS_A8A3_VC );
		plCDS->SetStateOffset( 1, 0.5f, 0.0f );

		plPowerOn_A->DefineMeshGroup( GetVCMeshIndex(), GRP_POWERON_A_A8A3_VC );
		plPowerOn_A->SetStateOffset( 1, 0.5f, 0.0f );

		plPowerOn_C->DefineMeshGroup( GetVCMeshIndex(), GRP_POWERON_C_A8A3_VC );
		plPowerOn_C->SetStateOffset( 1, 0.5f, 0.0f );

		plAPDSCircuitProtectOff_A->DefineMeshGroup( GetVCMeshIndex(), GRP_APDSCIRCUITPROTECTOFF_A_A8A3_VC );
		plAPDSCircuitProtectOff_A->SetStateOffset( 1, 0.5f, 0.0f );

		plAPDSCircuitProtectOff_C->DefineMeshGroup( GetVCMeshIndex(), GRP_APDSCIRCUITPROTECTOFF_C_A8A3_VC );
		plAPDSCircuitProtectOff_C->SetStateOffset( 1, 0.5f, 0.0f );

		plRingAligned_A->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGALIGNED_A_A8A3_VC );
		plRingAligned_A->SetStateOffset( 1, 0.5f, 0.0f );

		plRingAligned_C->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGALIGNED_C_A8A3_VC );
		plRingAligned_C->SetStateOffset( 1, 0.5f, 0.0f );

		plRingInitialPosition_A->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGINITIALPOSITION_A_A8A3_VC );
		plRingInitialPosition_A->SetStateOffset( 1, 0.5f, 0.0f );

		plRingInitialPosition_C->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGINITIALPOSITION_C_A8A3_VC );
		plRingInitialPosition_C->SetStateOffset( 1, 0.5f, 0.0f );

		plFixersOff_A->DefineMeshGroup( GetVCMeshIndex(), GRP_FIXERSOFF_A_A8A3_VC );
		plFixersOff_A->SetStateOffset( 1, 0.5f, 0.0f );

		plFixersOff_C->DefineMeshGroup( GetVCMeshIndex(), GRP_FIXERSOFF_C_A8A3_VC );
		plFixersOff_C->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks1Open_A->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS1OPEN_A_A8A3_VC );
		plHooks1Open_A->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks1Open_C->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS1OPEN_C_A8A3_VC );
		plHooks1Open_C->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks2Open_A->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS2OPEN_A_A8A3_VC );
		plHooks2Open_A->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks2Open_C->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS2OPEN_C_A8A3_VC );
		plHooks2Open_C->SetStateOffset( 1, 0.5f, 0.0f );

		plLatchesClosed_A->DefineMeshGroup( GetVCMeshIndex(), GRP_LATCHESCLOSED_A_A8A3_VC );
		plLatchesClosed_A->SetStateOffset( 1, 0.5f, 0.0f );

		plLatchesClosed_C->DefineMeshGroup( GetVCMeshIndex(), GRP_LATCHESCLOSED_C_A8A3_VC );
		plLatchesClosed_C->SetStateOffset( 1, 0.5f, 0.0f );

		plUndockComplet_A->DefineMeshGroup( GetVCMeshIndex(), GRP_UNDOCKCOMPLET_A_A8A3_VC );
		plUndockComplet_A->SetStateOffset( 1, 0.5f, 0.0f );

		plUndockComplet_C->DefineMeshGroup( GetVCMeshIndex(), GRP_UNDOCKCOMPLET_C_A8A3_VC );
		plUndockComplet_C->SetStateOffset( 1, 0.5f, 0.0f );

		plInitialContact_A->DefineMeshGroup( GetVCMeshIndex(), GRP_INITIALCONTACT_A_A8A3_VC );
		plInitialContact_A->SetStateOffset( 1, 0.5f, 0.0f );

		plInitialContact_C->DefineMeshGroup( GetVCMeshIndex(), GRP_INITIALCONTACT_C_A8A3_VC );
		plInitialContact_C->SetStateOffset( 1, 0.5f, 0.0f );

		plCaptureCapture_A->DefineMeshGroup( GetVCMeshIndex(), GRP_CAPTURECAPTURE_A_A8A3_VC );
		plCaptureCapture_A->SetStateOffset( 1, 0.5f, 0.0f );

		plCaptureCapture_C->DefineMeshGroup( GetVCMeshIndex(), GRP_CAPTURECAPTURE_C_A8A3_VC );
		plCaptureCapture_C->SetStateOffset( 1, 0.5f, 0.0f );

		plRingForwardPosition_A->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGFORWARDPOSITION_A_A8A3_VC );
		plRingForwardPosition_A->SetStateOffset( 1, 0.5f, 0.0f );

		plRingForwardPosition_C->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGFORWARDPOSITION_C_A8A3_VC );
		plRingForwardPosition_C->SetStateOffset( 1, 0.5f, 0.0f );

		plReadyToHook_A->DefineMeshGroup( GetVCMeshIndex(), GRP_READYTOHOOK_A_A8A3_VC );
		plReadyToHook_A->SetStateOffset( 1, 0.5f, 0.0f );

		plReadyToHook_C->DefineMeshGroup( GetVCMeshIndex(), GRP_READYTOHOOK_C_A8A3_VC );
		plReadyToHook_C->SetStateOffset( 1, 0.5f, 0.0f );

		plInterfSealed_A->DefineMeshGroup( GetVCMeshIndex(), GRP_INTERFSEALED_A_A8A3_VC );
		plInterfSealed_A->SetStateOffset( 1, 0.5f, 0.0f );

		plInterfSealed_C->DefineMeshGroup( GetVCMeshIndex(), GRP_INTERFSEALED_C_A8A3_VC );
		plInterfSealed_C->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks1Closed_A->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS1CLOSED_A_A8A3_VC );
		plHooks1Closed_A->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks1Closed_C->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS1CLOSED_C_A8A3_VC );
		plHooks1Closed_C->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks2Closed_A->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS2CLOSED_A_A8A3_VC );
		plHooks2Closed_A->SetStateOffset( 1, 0.5f, 0.0f );

		plHooks2Closed_C->DefineMeshGroup( GetVCMeshIndex(), GRP_HOOKS2CLOSED_C_A8A3_VC );
		plHooks2Closed_C->SetStateOffset( 1, 0.5f, 0.0f );

		plLatchesOpen_A->DefineMeshGroup( GetVCMeshIndex(), GRP_LATCHESOPEN_A_A8A3_VC );
		plLatchesOpen_A->SetStateOffset( 1, 0.5f, 0.0f );

		plLatchesOpen_C->DefineMeshGroup( GetVCMeshIndex(), GRP_LATCHESOPEN_C_A8A3_VC );
		plLatchesOpen_C->SetStateOffset( 1, 0.5f, 0.0f );

		plRingFinalPosition_A->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGFINALPOSITION_A_A8A3_VC );
		plRingFinalPosition_A->SetStateOffset( 1, 0.5f, 0.0f );

		plRingFinalPosition_C->DefineMeshGroup( GetVCMeshIndex(), GRP_RINGFINALPOSITION_C_A8A3_VC );
		plRingFinalPosition_C->SetStateOffset( 1, 0.5f, 0.0f );

		plAp->DefineMeshGroup( GetVCMeshIndex(), GRP_AP_A8A3_VC );
		plAp->SetStateOffset( 1, 0.5f, 0.0f );

		plBp->DefineMeshGroup( GetVCMeshIndex(), GRP_BP_A8A3_VC );
		plBp->SetStateOffset( 1, 0.5f, 0.0f );

		plCp->DefineMeshGroup( GetVCMeshIndex(), GRP_CP_A8A3_VC );
		plCp->SetStateOffset( 1, 0.5f, 0.0f );

		plPyroCircuitProtectOff_A->DefineMeshGroup( GetVCMeshIndex(), GRP_PYROCIRCUITPROTECTOFF_A_A8A3_VC );
		plPyroCircuitProtectOff_A->SetStateOffset( 1, 0.5f, 0.0f );

		plPyroCircuitProtectOff_C->DefineMeshGroup( GetVCMeshIndex(), GRP_PYROCIRCUITPROTECTOFF_C_A8A3_VC );
		plPyroCircuitProtectOff_C->SetStateOffset( 1, 0.5f, 0.0f );


		pControlPanelPowerA->SetMouseRegion( AID_A8A3, 0.078607f, 0.121607f, 0.097529f, 0.202774f );
		pControlPanelPowerA->SetReference( _V( 0.0, 0.316888, -0.101567 ), switch_rot );
		pControlPanelPowerA->DefineGroup( GRP_S1_A8A3_VC );

		pControlPanelPowerB->SetMouseRegion( AID_A8A3, 0.175489f, 0.123035f, 0.194648f, 0.204244f );
		pControlPanelPowerB->SetReference( _V( 0.0, 0.316888, -0.101567 ), switch_rot );
		pControlPanelPowerB->DefineGroup( GRP_S2_A8A3_VC );

		pControlPanelPowerC->SetMouseRegion( AID_A8A3, 0.271936f, 0.122135f, 0.291739f, 0.203266f );
		pControlPanelPowerC->SetReference( _V( 0.0, 0.316888, -0.101567 ), switch_rot );
		pControlPanelPowerC->DefineGroup( GRP_S3_A8A3_VC );

		pHeatersDCUPowerH1->SetMouseRegion( AID_A8A3, 0.078266f, 0.315846f, 0.097893f, 0.396873f );
		pHeatersDCUPowerH1->SetReference( _V( 0.0, 0.243146, -0.078524 ), switch_rot );
		pHeatersDCUPowerH1->DefineGroup( GRP_S4_A8A3_VC );

		pHeatersDCUPowerH2DCU->SetMouseRegion( AID_A8A3, 0.175297f, 0.316582f, 0.194602f, 0.397552f );
		pHeatersDCUPowerH2DCU->SetReference( _V( 0.0, 0.243146, -0.078524),switch_rot );
		pHeatersDCUPowerH2DCU->DefineGroup( GRP_S5_A8A3_VC );

		pHeatersDCUPowerH3DCU->SetMouseRegion( AID_A8A3, 0.271984f, 0.315340f, 0.291396f, 0.397430f );
		pHeatersDCUPowerH3DCU->SetReference( _V( 0.0, 0.243146, -0.078524 ), switch_rot );
		pHeatersDCUPowerH3DCU->DefineGroup( GRP_S6_A8A3_VC );

		pAPDSPowerA->SetMouseRegion( AID_A8A3, 0.078492f, 0.510377f, 0.097095f, 0.591183f );
		pAPDSPowerA->SetReference( _V( 0.0,  0.170376, -0.055444 ), switch_rot );
		pAPDSPowerA->DefineGroup( GRP_S7_A8A3_VC );

		pAPDSPowerB->SetMouseRegion( AID_A8A3, 0.175082f, 0.510769f, 0.194313f, 0.590632f );
		pAPDSPowerB->SetReference( _V( 0.0,  0.170376, -0.055444 ), switch_rot );
		pAPDSPowerB->DefineGroup( GRP_S8_A8A3_VC );

		pAPDSPowerC->SetMouseRegion( AID_A8A3, 0.271967f, 0.509268f, 0.291367f, 0.591272f );
		pAPDSPowerC->SetReference( _V( 0.0,  0.170376, -0.055444 ), switch_rot );
		pAPDSPowerC->DefineGroup( GRP_S9_A8A3_VC );

		pPyrosAp->SetMouseRegion( AID_A8A3, 0.706286f, 0.120643f, 0.725018f, 0.203573f );
		pPyrosAp->SetReference( _V( 0.0, 0.316888, -0.101567 ), switch_rot );
		pPyrosAp->DefineGroup( GRP_S10_A8A3_VC );

		pPyrosBp->SetMouseRegion( AID_A8A3, 0.802748f, 0.123284f, 0.821752f, 0.204392f );
		pPyrosBp->SetReference( _V( 0.0, 0.316888, -0.101567 ), switch_rot );
		pPyrosBp->DefineGroup( GRP_S11_A8A3_VC );

		pPyrosCp->SetMouseRegion( AID_A8A3, 0.899503f, 0.122141f, 0.918277f, 0.203744f );
		pPyrosCp->SetReference( _V( 0.0, 0.316888, -0.101567 ), switch_rot );
		pPyrosCp->DefineGroup( GRP_S12_A8A3_VC );


		pLampTest->SetMouseRegion( AID_A8A3, 0.147450f, 0.738321f, 0.223435f, 0.784995f );
		pLampTest->DefineGroup( GRP_LAMPTEST_A8A3_VC );
		pLampTest->SetDirection( PB_VECTOR );
		pLampTest->SetMotionLength( button_push_length );

		pPowerOn->SetMouseRegion( AID_A8A3, 0.572161f, 0.737224f, 0.648515f, 0.783878f );
		pPowerOn->DefineGroup( GRP_APDS_CC_POWERON_A8A3_VC );
		pPowerOn->SetDirection( PB_VECTOR );
		pPowerOn->SetMotionLength( button_push_length );

		pPowerOff->SetMouseRegion( AID_A8A3, 0.653795f, 0.736775f, 0.730674f, 0.785085f );
		pPowerOff->DefineGroup( GRP_APDS_CC_POWEROFF_A8A3_VC );
		pPowerOff->SetDirection( PB_VECTOR );
		pPowerOff->SetMotionLength( button_push_length );

		pRingOut->SetMouseRegion( AID_A8A3, 0.736206f, 0.736760f, 0.812960f, 0.785520f );
		pRingOut->DefineGroup( GRP_APDS_CC_RINGOUT_A8A3_VC );
		pRingOut->SetDirection( PB_VECTOR );
		pRingOut->SetMotionLength( button_push_length );

		pRingIn->SetMouseRegion( AID_A8A3, 0.818035f, 0.737106f, 0.894547f, 0.785520f );
		pRingIn->DefineGroup( GRP_APDS_CC_RINGIN_A8A3_VC );
		pRingIn->SetDirection( PB_VECTOR );
		pRingIn->SetMotionLength( button_push_length );

		pAPDSCircProtOff->SetMouseRegion( AID_A8A3, 0.571672f, 0.846841f, 0.648487f, 0.894743f );
		pAPDSCircProtOff->DefineGroup( GRP_APDS_CC_APDSCIRCPROTOFF_A8A3_VC );
		pAPDSCircProtOff->SetDirection( PB_VECTOR );
		pAPDSCircProtOff->SetMotionLength( button_push_length );

		pCloseHooks->SetMouseRegion( AID_A8A3, 0.653701f, 0.845757f, 0.730399f, 0.894834f );
		pCloseHooks->DefineGroup( GRP_APDS_CC_CLOSEHOOKS_A8A3_VC );
		pCloseHooks->SetDirection( PB_VECTOR );
		pCloseHooks->SetMotionLength( button_push_length );

		pCloseLatches->SetMouseRegion( AID_A8A3, 0.735965f, 0.845941f, 0.812366f, 0.894667f );
		pCloseLatches->DefineGroup( GRP_APDS_CC_CLOSELATCHES_A8A3_VC );
		pCloseLatches->SetDirection( PB_VECTOR );
		pCloseLatches->SetMotionLength( button_push_length );

		pFixerOff->SetMouseRegion( AID_A8A3, 0.817866f, 0.846560f, 0.894862f, 0.894491f );
		pFixerOff->DefineGroup( GRP_APDS_CC_FIXEROFF_A8A3_VC );
		pFixerOff->SetDirection( PB_VECTOR );
		pFixerOff->SetMotionLength( button_push_length );

		pPyroCommands->SetMouseRegion( AID_A8A3, 0, 0.693898f, 0.462332f, 0.727482f, 0.506793f );
		pPyroCommands->SetMouseRegion( AID_A8A3, 1, 0.901446f, 0.402513f, 0.918340f, 0.545360f );
		pPyroCommands->SetReference( _V( 0.047303, 0.218783, -0.063603 ), switch_rotV );
		pPyroCommands->DefineGroup( GRP_PLATEGUARD1_A8A3_VC );

		pAPDSControlCommands->SetMouseRegion( AID_A8A3, 0, 0.692924f, 0.618018f, 0.728574f, 0.667438f );
		pAPDSControlCommands->SetMouseRegion( AID_A8A3, 1, 0.901626f, 0.558671f, 0.918064f, 0.700879f );
		pAPDSControlCommands->SetReference( _V( 0.047303, 0.218783, -0.063603 ), switch_rotV );
		pAPDSControlCommands->DefineGroup( GRP_PLATEGUARD2_A8A3_VC );

		pPyroCircProtOff->SetMouseRegion( AID_A8A3, 0.735892f, 0.409768f, 0.813083f, 0.456907f );
		pPyroCircProtOff->DefineGroup( GRP_PYROCOMMANDS_PYROCIRCPROTOFF_A8A3_VC );
		pPyroCircProtOff->SetDirection( PB_VECTOR );
		pPyroCircProtOff->SetMotionLength( button_push_length );

		pPyroCircProtOn->SetMouseRegion( AID_A8A3, 0.818159f, 0.409983f, 0.894843f, 0.457091f );
		pPyroCircProtOn->DefineGroup( GRP_PYROCOMMANDS_PYROCIRCPROTON_A8A3_VC );
		pPyroCircProtOn->SetDirection( PB_VECTOR );
		pPyroCircProtOn->SetMotionLength( button_push_length );

		pActHooksFiring->SetMouseRegion( AID_A8A3, 0.736059f, 0.489543f, 0.812772f, 0.535945f );
		pActHooksFiring->DefineGroup( GRP_PYROCOMMANDS_ACTHOOKSFIRING_A8A3_VC );
		pActHooksFiring->SetDirection( PB_VECTOR );
		pActHooksFiring->SetMotionLength( button_push_length );

		pPasHooksFiring->SetMouseRegion( AID_A8A3, 0.818215f, 0.489216f, 0.894952f, 0.537039f );
		pPasHooksFiring->DefineGroup( GRP_PYROCOMMANDS_PASHOOKSFIRING_A8A3_VC );
		pPasHooksFiring->SetDirection( PB_VECTOR );
		pPasHooksFiring->SetMotionLength( button_push_length );

		pOpenHooks->SetMouseRegion( AID_A8A3, 0.735724f, 0.562760f, 0.812803f, 0.609291f );
		pOpenHooks->DefineGroup( GRP_APDS_CC_OPENHOOKS_A8A3_VC );
		pOpenHooks->SetDirection( PB_VECTOR );
		pOpenHooks->SetMotionLength( button_push_length );

		pOpenLatches->SetMouseRegion( AID_A8A3, 0.818240f, 0.562823f, 0.895010f, 0.609364f );
		pOpenLatches->DefineGroup( GRP_APDS_CC_OPENLATCHES_A8A3_VC );
		pOpenLatches->SetDirection( PB_VECTOR );
		pOpenLatches->SetMotionLength( button_push_length );

		pUndocking->SetMouseRegion( AID_A8A3, 0.817946f, 0.646157f, 0.895457f, 0.694965f );
		pUndocking->DefineGroup( GRP_APDS_CC_UNDOCKING_A8A3_VC );
		pUndocking->SetDirection( PB_VECTOR );
		pUndocking->SetMotionLength( button_push_length );
		return;
	}

	void PanelA8A3::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;
		oapiVCRegisterArea( AID_A8A3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A8A3,
			_V( 0.520632, 0.37734, -0.1185 ) + ofs, _V( 0.0, 0.37734, -0.1185 ) + ofs,
			_V( 0.520632, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.0 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelA8A3::OnPostStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPostStep( simt, simdt, mjd );

		RunSignals();
		return;
	}

	void PanelA8A3::RunSignals( void )
	{
		bool CNTL_PNL_A;
		bool CNTL_PNL_C;
		if (dipControlPanelPowerA.IsSet() && dipPNL_LOGIC_A.IsSet())
		{
			CNTL_PNL_A = true;
			dopCNTL_PNL_A.SetLine();
		}
		else
		{
			CNTL_PNL_A = false;
			dopCNTL_PNL_A.ResetLine();
		}
		if (dipControlPanelPowerB.IsSet() && dipPNL_LOGIC_B.IsSet())
		{
			dopCNTL_PNL_B.SetLine();
		}
		else
		{
			dopCNTL_PNL_B.ResetLine();
		}
		if (dipControlPanelPowerC.IsSet() && dipPNL_LOGIC_C.IsSet())
		{
			CNTL_PNL_C = true;
			dopCNTL_PNL_C.SetLine();
		}
		else
		{
			CNTL_PNL_C = false;
			dopCNTL_PNL_C.ResetLine();
		}
		if (dipControlPanelPowerA.IsSet() || dipControlPanelPowerB.IsSet() || dipControlPanelPowerC.IsSet())
		{
			dopPNLgnd.ResetLine();
		}
		else
		{
			dopPNLgnd.SetLine();
		}


		if (dipAPDSPowerA.IsSet() && dipPNL_LOGIC_A.IsSet())
		{
			dopADS.SetLine();
			dopWA.SetLine();
		}
		else
		{
			dopADS.ResetLine();
			dopWA.ResetLine();
		}
		if (dipAPDSPowerB.IsSet() && dipPNL_LOGIC_B.IsSet())
		{
			dopBDS.SetLine();
			dopWB.SetLine();
		}
		else
		{
			dopBDS.ResetLine();
			dopWB.ResetLine();
		}
		if (dipAPDSPowerC.IsSet() && dipPNL_LOGIC_C.IsSet())
		{
			dopCDS.SetLine();
			dopWC.SetLine();
		}
		else
		{
			dopCDS.ResetLine();
			dopWC.ResetLine();
		}
		if (dipAPDSPowerA.IsSet() || dipAPDSPowerB.IsSet() || dipAPDSPowerC.IsSet())
		{
			dopCgnd.ResetLine();
		}
		else
		{
			dopCgnd.SetLine();
		}


		if (dipPyrosAp.IsSet() && dipPNL_LOGIC_A.IsSet())
		{
			dopAp.SetLine();
		}
		else
		{
			dopAp.ResetLine();
		}
		if (dipPyrosBp.IsSet() && dipPNL_LOGIC_B.IsSet())
		{
			dopBp.SetLine();
		}
		else
		{
			dopBp.ResetLine();
		}
		if (dipPyrosCp.IsSet() && dipPNL_LOGIC_C.IsSet())
		{
			dopCp.SetLine();
		}
		else
		{
			dopCp.ResetLine();
		}


		// lightcmd is ground signal from avionics, power source and lamp test ground signals determined here
		if (CNTL_PNL_A)
		{
			if (lighttest.IsSet())
			{
				for (int i = 0; i < 38; i += 2) lightoutput[i].SetLine();
			}
			else
			{
				for (int i = 0; i < 38; i += 2) lightoutput[i].SetLine( (int)lightcmd[i].IsSet() * 5.0f );
			}
		}
		else
		{
			for (int i = 0; i < 38; i += 2) lightoutput[i].ResetLine();
		}
		
		if (CNTL_PNL_C)
		{
			if (lighttest.IsSet())
			{
				for (int i = 1; i < 38; i += 2) lightoutput[i].SetLine();
			}
			else
			{
				for (int i = 1; i < 38; i += 2) lightoutput[i].SetLine( (int)lightcmd[i].IsSet() * 5.0f );
			}
		}
		else
		{
			for (int i = 1; i < 38; i += 2) lightoutput[i].ResetLine();
		}
		return;
	}
}
