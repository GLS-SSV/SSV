/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2022/01/31   GLS
2022/02/01   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelR13L.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_r13l.h"


namespace vc
{
	PanelR13L::PanelR13L( Atlantis* psts ):AtlantisPanel( psts, "R13L" )
	{
		oapiWriteLog( "(PanelR13L::PanelR13L) Enter constructor." );

		DefineMesh( MESHNAME_PANELR13L );

		Add( pPL_BAY_DOOR_SYS_1 = new StdSwitch2( psts, "PL BAY DOOR SYS 1" ) );
		pPL_BAY_DOOR_SYS_1->SetLabel( 0, "DISABLE" );
		pPL_BAY_DOOR_SYS_1->SetLabel( 1, "ENABLE" );
		Add( pPL_BAY_DOOR_SYS_2 = new StdSwitch2( psts, "PL BAY DOOR SYS 2" ) );
		pPL_BAY_DOOR_SYS_2->SetLabel( 0, "DISABLE" );
		pPL_BAY_DOOR_SYS_2->SetLabel( 1, "ENABLE" );

		Add( pPL_BAY_MECH_PWR_SYS_1 = new StdSwitch2( psts, "PL BAY MECH PWR SYS 1" ) );
		pPL_BAY_MECH_PWR_SYS_1->SetLabel( 0, "OFF" );
		pPL_BAY_MECH_PWR_SYS_1->SetLabel( 1, "ON" );
		Add( pPL_BAY_MECH_PWR_SYS_2 = new StdSwitch2( psts, "PL BAY MECH PWR SYS 2" ) );
		pPL_BAY_MECH_PWR_SYS_2->SetLabel( 0, "OFF" );
		pPL_BAY_MECH_PWR_SYS_2->SetLabel( 1, "ON" );

		Add( pPL_BAY_DOOR = new LockableLever3( psts, "PL BAY DOOR" ) );
		pPL_BAY_DOOR->SetLabel( 0, "CLOSE" );
		pPL_BAY_DOOR->SetLabel( 1, "STOP" );
		pPL_BAY_DOOR->SetLabel( 2, "OPEN" );

		Add( pRADIATOR_LATCH_CONTROL_SYS_A = new StdSwitch3( psts, "RADIATOR LATCH CONTROL SYS A" ) );
		pRADIATOR_LATCH_CONTROL_SYS_A->SetLabel( 0, "LATCH" );
		pRADIATOR_LATCH_CONTROL_SYS_A->SetLabel( 1, "OFF" );
		pRADIATOR_LATCH_CONTROL_SYS_A->SetLabel( 2, "RELEASE" );
		Add( pRADIATOR_LATCH_CONTROL_SYS_B = new StdSwitch3( psts, "RADIATOR LATCH CONTROL SYS B" ) );
		pRADIATOR_LATCH_CONTROL_SYS_B->SetLabel( 0, "LATCH" );
		pRADIATOR_LATCH_CONTROL_SYS_B->SetLabel( 1, "OFF" );
		pRADIATOR_LATCH_CONTROL_SYS_B->SetLabel( 2, "RELEASE" );

		Add( pRADIATOR_CONTROL_SYS_A = new StdSwitch3( psts, "RADIATOR CONTROL SYS A" ) );
		pRADIATOR_CONTROL_SYS_A->SetLabel( 0, "STOW" );
		pRADIATOR_CONTROL_SYS_A->SetLabel( 1, "OFF" );
		pRADIATOR_CONTROL_SYS_A->SetLabel( 2, "DEPLOY" );
		Add( pRADIATOR_CONTROL_SYS_B = new StdSwitch3( psts, "RADIATOR CONTROL SYS B" ) );
		pRADIATOR_CONTROL_SYS_B->SetLabel( 0, "STOW" );
		pRADIATOR_CONTROL_SYS_B->SetLabel( 1, "OFF" );
		pRADIATOR_CONTROL_SYS_B->SetLabel( 2, "DEPLOY" );

		Add( pKU_ANTENNA_DIRECT_STOW = new LockableLever2( psts, "KU ANTENNA DIRECT STOW" ) );
		pKU_ANTENNA_DIRECT_STOW->SetLabel( 0, "OFF" );
		pKU_ANTENNA_DIRECT_STOW->SetLabel( 1, "ON" );

		Add( pKU_ANTENNA = new StdSwitch3( psts, "KU ANTENNA" ) );
		pKU_ANTENNA->SetLabel( 0, "STOW" );
		pKU_ANTENNA->SetLabel( 1, "GND" );
		pKU_ANTENNA->SetLabel( 2, "DEPLOY" );

		Add( pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A = new StdSwitch3( psts, "MANNED MANUV UNIT GN2 SPLY ISOL VLV A" ) );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetLabel( 0, "CLOSE" );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetLabel( 1, "-" );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetLabel( 2, "OPEN" );
		Add( pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B = new StdSwitch3( psts, "MANNED MANUV UNIT GN2 SPLY ISOL VLV B" ) );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetLabel( 0, "CLOSE" );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetLabel( 1, "-" );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetLabel( 2, "OPEN" );

		Add( pPL_BAY_DOOR_TB = new StandardTalkback3( psts, "PL BAY DOOR" ) );

		Add( pRADIATOR_LATCH_CONTROL_STBD = new StandardTalkback3( psts, "RADIATOR LATCH STBD" ) );
		Add( pRADIATOR_LATCH_CONTROL_PORT = new StandardTalkback3( psts, "RADIATOR LATCH PORT" ) );

		Add( pRADIATOR_CONTROL_STBD = new StandardTalkback3( psts, "RADIATOR STBD" ) );
		Add( pRADIATOR_CONTROL_PORT = new StandardTalkback3( psts, "RADIATOR PORT" ) );

		Add( pKU_ANTENNA_TB = new StandardTalkback3( psts, "KU ANTENNA" ) );

		Add( pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A_TB = new StandardTalkback3( psts, "MMU GN2 SPLY ISOL VLV A" ) );
		Add( pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B_TB = new StandardTalkback3( psts, "MMU GN2 SPLY ISOL VLV B" ) );

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

		pPL_BAY_DOOR_SYS_1->SetInitialAnimState( 0.5f );
		pPL_BAY_DOOR_SYS_1->DefineGroup( GRP_S15_R13L_VC );
		pPL_BAY_DOOR_SYS_1->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPL_BAY_DOOR_SYS_1->SetMouseRegion( AID_R13L, 0.168642f, 0.143249f, 0.235304f, 0.210372f );

		pPL_BAY_DOOR_SYS_2->SetInitialAnimState( 0.5f );
		pPL_BAY_DOOR_SYS_2->DefineGroup( GRP_S14_R13L_VC );
		pPL_BAY_DOOR_SYS_2->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPL_BAY_DOOR_SYS_2->SetMouseRegion( AID_R13L, 0.328042f, 0.143249f, 0.389222f, 0.210372f );

		pPL_BAY_MECH_PWR_SYS_1->SetInitialAnimState( 0.5f );
		pPL_BAY_MECH_PWR_SYS_1->DefineGroup( GRP_S1_R13L_VC );
		pPL_BAY_MECH_PWR_SYS_1->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPL_BAY_MECH_PWR_SYS_1->SetMouseRegion( AID_R13L, 0.477183f, 0.143249f, 0.540203f, 0.210372f );

		pPL_BAY_MECH_PWR_SYS_2->SetInitialAnimState( 0.5f );
		pPL_BAY_MECH_PWR_SYS_2->DefineGroup( GRP_S2_R13L_VC );
		pPL_BAY_MECH_PWR_SYS_2->SetReference( _V( 1.2589, 2.2510, 12.4970 ), SWITCH_ROT );
		pPL_BAY_MECH_PWR_SYS_2->SetMouseRegion( AID_R13L, 0.631861f, 0.143249f, 0.695974f, 0.210372f );


		pRADIATOR_LATCH_CONTROL_SYS_A->SetInitialAnimState( 0.5f );
		pRADIATOR_LATCH_CONTROL_SYS_A->DefineGroup( GRP_S4_R13L_VC );
		pRADIATOR_LATCH_CONTROL_SYS_A->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pRADIATOR_LATCH_CONTROL_SYS_A->SetMouseRegion( AID_R13L, 0.317112f, 0.494518f, 0.382363f, 0.560706f );

		pRADIATOR_LATCH_CONTROL_SYS_B->SetInitialAnimState( 0.5f );
		pRADIATOR_LATCH_CONTROL_SYS_B->DefineGroup( GRP_S6_R13L_VC );
		pRADIATOR_LATCH_CONTROL_SYS_B->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pRADIATOR_LATCH_CONTROL_SYS_B->SetMouseRegion( AID_R13L, 0.475552f, 0.496065f, 0.536584f, 0.560706f );

		pRADIATOR_CONTROL_SYS_A->SetInitialAnimState( 0.5f );
		pRADIATOR_CONTROL_SYS_A->DefineGroup( GRP_S5_R13L_VC );
		pRADIATOR_CONTROL_SYS_A->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pRADIATOR_CONTROL_SYS_A->SetMouseRegion( AID_R13L, 0.635115f, 0.496065f, 0.700500f, 0.560706f );

		pRADIATOR_CONTROL_SYS_B->SetInitialAnimState( 0.5f );
		pRADIATOR_CONTROL_SYS_B->DefineGroup( GRP_S7_R13L_VC );
		pRADIATOR_CONTROL_SYS_B->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pRADIATOR_CONTROL_SYS_B->SetMouseRegion( AID_R13L, 0.793256f, 0.496065f, 0.856982f, 0.560706f );

		pKU_ANTENNA->SetInitialAnimState( 0.5f );
		pKU_ANTENNA->DefineGroup( GRP_S8_R13L_VC );
		pKU_ANTENNA->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pKU_ANTENNA->SetMouseRegion( AID_R13L, 0.318068f, 0.829212f, 0.381281f, 0.895379f );

		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetInitialAnimState( 0.5f );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->DefineGroup( GRP_S11_R13L_VC );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetMouseRegion( AID_R13L, 0.632811f, 0.829212f, 0.699357f, 0.895379f );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetSpringLoaded( true, 0 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->SetSpringLoaded( true, 2 );

		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetInitialAnimState( 0.5f );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->DefineGroup( GRP_S10_R13L_VC );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetMouseRegion( AID_R13L, 0.792294f, 0.829212f, 0.857664f, 0.895379f );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetSpringLoaded( true, 0 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->SetSpringLoaded( true, 2 );


		pPL_BAY_DOOR->SetInitialAnimState( 0.5f );
		pPL_BAY_DOOR->DefineGroup( GRP_S3_R13L_VC );
		pPL_BAY_DOOR->SetReference( _V( 1.1680, 2.1914, 12.4524 ), SWITCH_ROT );
		pPL_BAY_DOOR->SetMouseRegion( AID_R13L, 0.158612f, 0.496065f, 0.225865f, 0.560706f );
		pPL_BAY_DOOR->SetPullDirection( SWITCH_PULL );

		pKU_ANTENNA_DIRECT_STOW->SetInitialAnimState( 0.5f );
		pKU_ANTENNA_DIRECT_STOW->DefineGroup( GRP_S12_R13L_VC );
		pKU_ANTENNA_DIRECT_STOW->SetReference( _V( 1.0815, 2.1346, 12.3583 ), SWITCH_ROT );
		pKU_ANTENNA_DIRECT_STOW->SetMouseRegion( AID_R13L, 0.164952f, 0.829212f, 0.230913f, 0.895379f );
		pKU_ANTENNA_DIRECT_STOW->SetPullDirection( SWITCH_PULL );


		pPL_BAY_DOOR_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_R13L_VC );

		pRADIATOR_LATCH_CONTROL_STBD->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_R13L_VC );

		pRADIATOR_LATCH_CONTROL_PORT->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_R13L_VC );

		pRADIATOR_CONTROL_STBD->DefineMeshGroup( GetVCMeshIndex(), GRP_DS3_R13L_VC );

		pRADIATOR_CONTROL_PORT->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_R13L_VC );

		pKU_ANTENNA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS6_R13L_VC );

		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS9_R13L_VC );

		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_R13L_VC );
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
		pPL_BAY_DOOR_SYS_1->ConnectPort( 1, pBundle, 0 );
		pPL_BAY_DOOR_SYS_2->ConnectPort( 1, pBundle, 1 );
		pPL_BAY_DOOR->ConnectPort( 0, pBundle, 2 );
		pPL_BAY_DOOR->ConnectPort( 2, pBundle, 3 );
		pPL_BAY_DOOR_TB->SetInput( 0, pBundle, 4, TB_OP );
		pPL_BAY_DOOR_TB->SetInput( 1, pBundle, 5, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
		pPL_BAY_MECH_PWR_SYS_1->ConnectPort( 1, pBundle, 0 );
		pPL_BAY_MECH_PWR_SYS_2->ConnectPort( 1, pBundle, 1 );
		
		pBundle = STS()->BundleManager()->CreateBundle( "RadiatorControl", 16 );
		pRADIATOR_LATCH_CONTROL_SYS_A->ConnectPort( 2, pBundle, 0 );
		pRADIATOR_LATCH_CONTROL_SYS_A->ConnectPort( 0, pBundle, 1 );
		pRADIATOR_LATCH_CONTROL_SYS_B->ConnectPort( 2, pBundle, 2 );
		pRADIATOR_LATCH_CONTROL_SYS_B->ConnectPort( 0, pBundle, 3 );
		pRADIATOR_LATCH_CONTROL_PORT->SetInput( 0, pBundle, 4, TB_REL );
		pRADIATOR_LATCH_CONTROL_PORT->SetInput( 1, pBundle, 5, TB_LAT );
		pRADIATOR_LATCH_CONTROL_STBD->SetInput( 0, pBundle, 6, TB_REL );
		pRADIATOR_LATCH_CONTROL_STBD->SetInput( 1, pBundle, 7, TB_LAT );
		pRADIATOR_CONTROL_SYS_A->ConnectPort( 2, pBundle, 8 );
		pRADIATOR_CONTROL_SYS_A->ConnectPort( 0, pBundle, 9 );
		pRADIATOR_CONTROL_SYS_B->ConnectPort( 2, pBundle, 10 );
		pRADIATOR_CONTROL_SYS_B->ConnectPort( 0, pBundle, 11 );
		pRADIATOR_CONTROL_PORT->SetInput( 0, pBundle, 12, TB_DPY );
		pRADIATOR_CONTROL_PORT->SetInput( 1, pBundle, 13, TB_STO );
		pRADIATOR_CONTROL_STBD->SetInput( 0, pBundle, 14, TB_DPY );
		pRADIATOR_CONTROL_STBD->SetInput( 1, pBundle, 15, TB_STO );

		pRADIATOR_LATCH_CONTROL_PORT_REL.Connect( pBundle, 4 );
		pRADIATOR_LATCH_CONTROL_PORT_LAT.Connect( pBundle, 5 );
		pRADIATOR_LATCH_CONTROL_STBD_REL.Connect( pBundle, 6 );
		pRADIATOR_LATCH_CONTROL_STBD_LAT.Connect( pBundle, 7 );

		pBundle = STS()->BundleManager()->CreateBundle( "RadiatorLatchMotorInd_1", 16 );
		PORT_RAD_LATCH_REL_1.Connect( pBundle, 12 );
		PORT_RAD_LATCH_LAT_1.Connect( pBundle, 13 );
		STARBOARD_RAD_LATCH_REL_1.Connect( pBundle, 14 );
		STARBOARD_RAD_LATCH_LAT_1.Connect( pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "RadiatorLatchMotorInd_2", 16 );
		PORT_RAD_LATCH_REL_2.Connect( pBundle, 12 );
		PORT_RAD_LATCH_LAT_2.Connect( pBundle, 13 );
		STARBOARD_RAD_LATCH_REL_2.Connect( pBundle, 14 );
		STARBOARD_RAD_LATCH_LAT_2.Connect( pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "KuBandAntennaCommand", 16 );
		pKU_ANTENNA_DIRECT_STOW->ConnectPort( 1, pBundle, 0 );
		pKU_ANTENNA->ConnectPort( 0, pBundle, 1 );
		pKU_ANTENNA->ConnectPort( 2, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "KuBandAntennaMotorInd", 16 );
		pKU_ANTENNA_TB->SetInput( 0, pBundle, 6, TB_STO );
		pKU_ANTENNA_TB->SetInput( 1, pBundle, 7, TB_DPY );

		/*pBundle = STS()->BundleManager()->CreateBundle( "MMUGN2SPLYISOLVLV", 8 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->ConnectPort( 0, pBundle, 0 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A->ConnectPort( 2, pBundle, 1 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->ConnectPort( 0, pBundle, 2 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B->ConnectPort( 2, pBundle, 3 );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A_TB->SetInput( 0, pBundle, 4, TB_OP );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A_TB->SetInput( 1, pBundle, 5, TB_CLO );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B_TB->SetInput( 0, pBundle, 6, TB_OP );
		pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B_TB->SetInput( 1, pBundle, 7, TB_CLO );*/

		AtlantisPanel::Realize();
		return;
	}

	void PanelR13L::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		if (PORT_RAD_LATCH_REL_1 && PORT_RAD_LATCH_REL_2) pRADIATOR_LATCH_CONTROL_PORT_REL.SetLine();
		else pRADIATOR_LATCH_CONTROL_PORT_REL.ResetLine();

		if (PORT_RAD_LATCH_LAT_1 && PORT_RAD_LATCH_LAT_2) pRADIATOR_LATCH_CONTROL_PORT_LAT.SetLine();
		else pRADIATOR_LATCH_CONTROL_PORT_LAT.ResetLine();

		if (STARBOARD_RAD_LATCH_REL_1 && STARBOARD_RAD_LATCH_REL_2) pRADIATOR_LATCH_CONTROL_STBD_REL.SetLine();
		else pRADIATOR_LATCH_CONTROL_STBD_REL.ResetLine();

		if (STARBOARD_RAD_LATCH_LAT_1 && STARBOARD_RAD_LATCH_LAT_2) pRADIATOR_LATCH_CONTROL_STBD_LAT.SetLine();
		else pRADIATOR_LATCH_CONTROL_STBD_LAT.ResetLine();
		return;
	}
}
