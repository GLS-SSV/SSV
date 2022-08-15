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
********************************************/
#include "PanelR13L.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_r13l.h"


namespace vc
{
	PanelR13L::PanelR13L( Atlantis* psts ):AtlantisPanel( psts, "R13L" )
	{
		oapiWriteLog( "(PanelR13L::PanelR13L) Enter constructor." );

		DefineMesh( MESHNAME_PANELR13L );

		Add( pPLBayDoor[0] = new StdSwitch2( psts, "PL BAY DOOR SYS 1" ) );
		pPLBayDoor[0]->SetLabel( 0, "DISABLE" );
		pPLBayDoor[0]->SetLabel( 1, "ENABLE" );
		Add( pPLBayDoor[1] = new StdSwitch2( psts, "PL BAY DOOR SYS 2" ) );
		pPLBayDoor[1]->SetLabel( 0, "DISABLE" );
		pPLBayDoor[1]->SetLabel( 1, "ENABLE" );

		Add( pPLBayMechPWR[0] = new StdSwitch2( psts, "PL BAY MECH PWR SYS 1" ) );
		pPLBayMechPWR[0]->SetLabel( 0, "OFF" );
		pPLBayMechPWR[0]->SetLabel( 1, "ON" );
		Add( pPLBayMechPWR[1] = new StdSwitch2( psts, "PL BAY MECH PWR SYS 2" ) );
		pPLBayMechPWR[1]->SetLabel( 0, "OFF" );
		pPLBayMechPWR[1]->SetLabel( 1, "ON" );

		Add( pPLBayDoorLL = new LockableLever3( psts, "PL BAY DOOR" ) );
		pPLBayDoorLL->SetLabel( 0, "CLOSE" );
		pPLBayDoorLL->SetLabel( 1, "STOP" );
		pPLBayDoorLL->SetLabel( 2, "OPEN" );

		Add( pLatchControl[0] = new StdSwitch3( psts, "RADIATOR LATCH CONTROL SYS A" ) );
		pLatchControl[0]->SetLabel( 0, "LATCH" );
		pLatchControl[0]->SetLabel( 1, "OFF" );
		pLatchControl[0]->SetLabel( 2, "RELEASE" );
		Add( pLatchControl[1] = new StdSwitch3( psts, "RADIATOR LATCH CONTROL SYS B" ) );
		pLatchControl[1]->SetLabel( 0, "LATCH" );
		pLatchControl[1]->SetLabel( 1, "OFF" );
		pLatchControl[1]->SetLabel( 2, "RELEASE" );

		Add( pRadiatorControl[0] = new StdSwitch3( psts, "RADIATOR CONTROL SYS A" ) );
		pRadiatorControl[0]->SetLabel( 0, "STOW" );
		pRadiatorControl[0]->SetLabel( 1, "OFF" );
		pRadiatorControl[0]->SetLabel( 2, "DEPLOY" );
		Add( pRadiatorControl[1] = new StdSwitch3( psts, "RADIATOR CONTROL SYS B" ) );
		pRadiatorControl[1]->SetLabel( 0, "STOW" );
		pRadiatorControl[1]->SetLabel( 1, "OFF" );
		pRadiatorControl[1]->SetLabel( 2, "DEPLOY" );

		Add( pKUAntennaDirectStow = new LockableLever2( psts, "KU ANTENNA DIRECT STOW" ) );
		pKUAntennaDirectStow->SetLabel( 0, "OFF" );
		pKUAntennaDirectStow->SetLabel( 1, "ON" );

		Add( pKUAntenna = new StdSwitch3( psts, "KU ANTENNA" ) );
		pKUAntenna->SetLabel( 0, "STOW" );
		pKUAntenna->SetLabel( 1, "GND" );
		pKUAntenna->SetLabel( 2, "DEPLOY" );

		Add( pMMUGN2SPLYISOLVLV[0] = new StdSwitch3( psts, "MANNED MANUV UNIT GN2 SPLY ISOL VLV A" ) );
		pMMUGN2SPLYISOLVLV[0]->SetLabel( 0, "CLOSE" );
		pMMUGN2SPLYISOLVLV[0]->SetLabel( 1, "-" );
		pMMUGN2SPLYISOLVLV[0]->SetLabel( 2, "OPEN" );
		Add( pMMUGN2SPLYISOLVLV[1] = new StdSwitch3( psts, "MANNED MANUV UNIT GN2 SPLY ISOL VLV B" ) );
		pMMUGN2SPLYISOLVLV[1]->SetLabel( 0, "CLOSE" );
		pMMUGN2SPLYISOLVLV[1]->SetLabel( 1, "-" );
		pMMUGN2SPLYISOLVLV[1]->SetLabel( 2, "OPEN" );

		Add( pPLBayDoorTB = new StandardTalkback3( psts, "PL BAY DOOR" ) );

		Add( pLatch[0] = new StandardTalkback3( psts, "RADIATOR LATCH STBD" ) );
		Add( pLatch[1] = new StandardTalkback3( psts, "RADIATOR LATCH PORT" ) );

		Add( pRadiator[0] = new StandardTalkback3( psts, "RADIATOR STBD" ) );
		Add( pRadiator[1] = new StandardTalkback3( psts, "RADIATOR PORT" ) );

		Add( pKUAntennaTB = new StandardTalkback3( psts, "KU ANTENNA" ) );

		Add( pMMUGN2SPLYISOLVLVTB[0] = new StandardTalkback3( psts, "MMU GN2 SPLY ISOL VLV A" ) );
		Add( pMMUGN2SPLYISOLVLVTB[1] = new StandardTalkback3( psts, "MMU GN2 SPLY ISOL VLV B" ) );

		oapiWriteLog( "(PanelR13L::PanelR13L) Leave constructor." );
	}

	PanelR13L::~PanelR13L()
	{
	}

	void PanelR13L::DefineVC()
	{
		const VECTOR3 SWITCH_ROT = _V( 0, 0, -1 );
		const VECTOR3 SWITCH_PULL = _V( -0.548687, 0.836028, 0 );
		AddAIDToMouseEventList( AID_R13L );

		pPLBayDoor[0]->SetInitialAnimState( 0.5f );
		pPLBayDoor[0]->DefineGroup( GRP_S15_R13L_VC );
		pPLBayDoor[0]->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPLBayDoor[0]->SetMouseRegion( AID_R13L, 0.168642f, 0.143249f, 0.235304f, 0.210372f );

		pPLBayDoor[1]->SetInitialAnimState( 0.5f );
		pPLBayDoor[1]->DefineGroup( GRP_S14_R13L_VC );
		pPLBayDoor[1]->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPLBayDoor[1]->SetMouseRegion( AID_R13L, 0.328042f, 0.143249f, 0.389222f, 0.210372f );

		pPLBayMechPWR[0]->SetInitialAnimState( 0.5f );
		pPLBayMechPWR[0]->DefineGroup( GRP_S1_R13L_VC );
		pPLBayMechPWR[0]->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPLBayMechPWR[0]->SetMouseRegion( AID_R13L, 0.477183f, 0.143249f, 0.540203f, 0.210372f );

		pPLBayMechPWR[1]->SetInitialAnimState( 0.5f );
		pPLBayMechPWR[1]->DefineGroup( GRP_S2_R13L_VC );
		pPLBayMechPWR[1]->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPLBayMechPWR[1]->SetMouseRegion( AID_R13L, 0.631861f, 0.143249f, 0.695974f, 0.210372f );


		pLatchControl[0]->SetInitialAnimState( 0.5f );
		pLatchControl[0]->DefineGroup( GRP_S4_R13L_VC );
		pLatchControl[0]->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pLatchControl[0]->SetMouseRegion( AID_R13L, 0.317112f, 0.494518f, 0.382363f, 0.560706f );

		pLatchControl[1]->SetInitialAnimState( 0.5f );
		pLatchControl[1]->DefineGroup( GRP_S6_R13L_VC );
		pLatchControl[1]->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pLatchControl[1]->SetMouseRegion( AID_R13L, 0.475552f, 0.496065f, 0.536584f, 0.560706f );

		pRadiatorControl[0]->SetInitialAnimState( 0.5f );
		pRadiatorControl[0]->DefineGroup( GRP_S5_R13L_VC );
		pRadiatorControl[0]->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pRadiatorControl[0]->SetMouseRegion( AID_R13L, 0.635115f, 0.496065f, 0.700500f, 0.560706f );

		pRadiatorControl[1]->SetInitialAnimState( 0.5f );
		pRadiatorControl[1]->DefineGroup( GRP_S7_R13L_VC );
		pRadiatorControl[1]->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pRadiatorControl[1]->SetMouseRegion( AID_R13L, 0.793256f, 0.496065f, 0.856982f, 0.560706f );

		pKUAntenna->SetInitialAnimState( 0.5f );
		pKUAntenna->DefineGroup( GRP_S8_R13L_VC );
		pKUAntenna->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pKUAntenna->SetMouseRegion( AID_R13L, 0.318068f, 0.829212f, 0.381281f, 0.895379f );

		pMMUGN2SPLYISOLVLV[0]->SetInitialAnimState( 0.5f );
		pMMUGN2SPLYISOLVLV[0]->DefineGroup( GRP_S11_R13L_VC );
		pMMUGN2SPLYISOLVLV[0]->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pMMUGN2SPLYISOLVLV[0]->SetMouseRegion( AID_R13L, 0.632811f, 0.829212f, 0.699357f, 0.895379f );
		pMMUGN2SPLYISOLVLV[0]->SetSpringLoaded( true, 0 );
		pMMUGN2SPLYISOLVLV[0]->SetSpringLoaded( true, 2 );

		pMMUGN2SPLYISOLVLV[1]->SetInitialAnimState( 0.5f );
		pMMUGN2SPLYISOLVLV[1]->DefineGroup( GRP_S10_R13L_VC );
		pMMUGN2SPLYISOLVLV[1]->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pMMUGN2SPLYISOLVLV[1]->SetMouseRegion( AID_R13L, 0.792294f, 0.829212f, 0.857664f, 0.895379f );
		pMMUGN2SPLYISOLVLV[1]->SetSpringLoaded( true, 0 );
		pMMUGN2SPLYISOLVLV[1]->SetSpringLoaded( true, 2 );


		pPLBayDoorLL->SetInitialAnimState( 0.5f );
		pPLBayDoorLL->DefineGroup( GRP_S3_R13L_VC );
		pPLBayDoorLL->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pPLBayDoorLL->SetMouseRegion( AID_R13L, 0.158612f, 0.496065f, 0.225865f, 0.560706f );
		pPLBayDoorLL->SetPullDirection( SWITCH_PULL );

		pKUAntennaDirectStow->SetInitialAnimState( 0.5f );
		pKUAntennaDirectStow->DefineGroup( GRP_S12_R13L_VC );
		pKUAntennaDirectStow->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pKUAntennaDirectStow->SetMouseRegion( AID_R13L, 0.164952f, 0.829212f, 0.230913f, 0.895379f );
		pKUAntennaDirectStow->SetPullDirection( SWITCH_PULL );


		pPLBayDoorTB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_R13L_VC );

		pLatch[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_R13L_VC );

		pLatch[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_R13L_VC );

		pRadiator[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS3_R13L_VC );

		pRadiator[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_R13L_VC );

		pKUAntennaTB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS6_R13L_VC );

		pMMUGN2SPLYISOLVLVTB[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS9_R13L_VC );

		pMMUGN2SPLYISOLVLVTB[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_R13L_VC );
		return;
	}

	void PanelR13L::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_R13L, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R13L,
			_V( 1.30517, 2.28139, 12.5617 ) + ofs, _V( 1.30517, 2.28139, 12.2607 ) + ofs,
			_V( 1.04497, 2.11062, 12.5617 ) + ofs, _V( 1.04497, 2.11062, 12.2607 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR13L::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "PayloadBayDoorControl", 6 );
		pPLBayDoor[0]->ConnectPort( 1, pBundle, 0 );
		pPLBayDoor[1]->ConnectPort( 1, pBundle, 1 );
		pPLBayDoorLL->ConnectPort( 0, pBundle, 2 );
		pPLBayDoorLL->ConnectPort( 2, pBundle, 3 );
		pPLBayDoorTB->SetInput( 0, pBundle, 4, TB_OP );
		pPLBayDoorTB->SetInput( 1, pBundle, 5, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
		pPLBayMechPWR[0]->ConnectPort( 1, pBundle, 0 );
		pPLBayMechPWR[1]->ConnectPort( 1, pBundle, 1 );
		pLatchControl[0]->ConnectPort( 0, pBundle, 2 );
		pLatchControl[0]->ConnectPort( 2, pBundle, 3 );
		pLatchControl[1]->ConnectPort( 0, pBundle, 4 );
		pLatchControl[1]->ConnectPort( 2, pBundle, 5 );
		pRadiatorControl[0]->ConnectPort( 0, pBundle, 6 );
		pRadiatorControl[0]->ConnectPort( 2, pBundle, 7 );
		pRadiatorControl[1]->ConnectPort( 0, pBundle, 8 );
		pRadiatorControl[1]->ConnectPort( 2, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "RadiatorControlTB", 8 );
		pLatch[0]->SetInput( 0, pBundle, 0, TB_LAT );
		pLatch[0]->SetInput( 1, pBundle, 1, TB_REL );
		pLatch[1]->SetInput( 0, pBundle, 2, TB_LAT );
		pLatch[1]->SetInput( 1, pBundle, 3, TB_REL );
		pRadiator[0]->SetInput( 0, pBundle, 4, TB_STO );
		pRadiator[0]->SetInput( 1, pBundle, 5, TB_DPY );
		pRadiator[1]->SetInput( 0, pBundle, 6, TB_STO );
		pRadiator[1]->SetInput( 1, pBundle, 7, TB_DPY );

		pBundle = STS()->BundleManager()->CreateBundle( "KUAntennaControl", 16 );
		pKUAntennaDirectStow->ConnectPort( 1, pBundle, 0 );
		pKUAntenna->ConnectPort( 0, pBundle, 1 );
		pKUAntenna->ConnectPort( 2, pBundle, 2 );
		pKUAntennaTB->SetInput( 0, pBundle, 3, TB_STO );
		pKUAntennaTB->SetInput( 1, pBundle, 4, TB_DPY );

		/*pBundle = STS()->BundleManager()->CreateBundle( "MMUGN2SPLYISOLVLV", 8 );
		pMMUGN2SPLYISOLVLV[0]->ConnectPort( 0, pBundle, 0 );
		pMMUGN2SPLYISOLVLV[0]->ConnectPort( 2, pBundle, 1 );
		pMMUGN2SPLYISOLVLV[1]->ConnectPort( 0, pBundle, 2 );
		pMMUGN2SPLYISOLVLV[1]->ConnectPort( 2, pBundle, 3 );
		pMMUGN2SPLYISOLVLVTB[0]->SetInput( 0, pBundle, 4, TB_OP );
		pMMUGN2SPLYISOLVLVTB[0]->SetInput( 1, pBundle, 5, TB_CLO );
		pMMUGN2SPLYISOLVLVTB[1]->SetInput( 0, pBundle, 6, TB_OP );
		pMMUGN2SPLYISOLVLVTB[1]->SetInput( 1, pBundle, 7, TB_CLO );*/

		AtlantisPanel::Realize();
		return;
	}
};
