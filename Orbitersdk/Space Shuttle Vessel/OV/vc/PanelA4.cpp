/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
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
********************************************/
#include "PanelA4.h"
#include "StandardSwitch.h"
#include "7SegDisp_MissionTime.h"
#include "7SegDisp_EventTime.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_a4.h"


namespace vc
{
	PanelA4::PanelA4( Atlantis *_sts ):AtlantisPanel( _sts, "A4" )
	{
		DefineMesh( MESHNAME_PANELA4 );

		Add( pMissionTimer = new StdSwitch3( _sts, "MISSION TIMER" ) );
		pMissionTimer->SetLabel( 0, "TEST" );
		pMissionTimer->SetLabel( 1, "MET" );
		pMissionTimer->SetLabel( 2, "GMT" );

		Add( pMissionTime = new _7SegDisp_MissionTime( _sts, "MISSION TIME" ) );
		Add( pEventTime = new _7SegDisp_EventTime( _sts, "EVENT TIME" ) );
	}

	PanelA4::~PanelA4()
	{
	}

	void PanelA4::DefineVC()
	{
		VECTOR3 switch_rot = _V( -0.96598, 0, 0.25860 );

		AddAIDToMouseEventList( AID_A4 );

		pMissionTimer->DefineGroup( GRP_S1_A4_VC );
		pMissionTimer->SetInitialAnimState( 0.5 );
		pMissionTimer->SetReference( _V( -0.7997, 2.9475, 12.3330 ), switch_rot );
		pMissionTimer->SetMouseRegion( AID_A4, 0.741337f, 0.766488f, 0.860226f, 0.890987f );
		pMissionTimer->SetSpringLoaded( true, 0 );

		pMissionTime->DefineMesh( GetVCMeshIndex() );
		pMissionTime->DefineComponent( GRP_M1_1_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_2_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_3_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_4_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_5_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_6_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_7_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_8_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M1_9_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->SetLocation( false );

		pEventTime->DefineMesh( GetVCMeshIndex() );
		pEventTime->DefineComponent( GRP_M2_1_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pEventTime->DefineComponent( GRP_M2_2_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pEventTime->DefineComponent( GRP_M2_3_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		pEventTime->DefineComponent( GRP_M2_4_A4_VC, true, false, false, _7SD_STATE_NUM0 );
		return;
	}

	void PanelA4::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A4, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A4,
			_V( -0.6351, 3.1074, 12.2873 ) + ofs, _V( -0.8416, 3.1074, 12.3431 ) + ofs,
			_V( -0.6351, 2.9140, 12.2873 ) + ofs, _V( -0.8416, 2.9140, 12.3431 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA4::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "A4_Timer", 2 );
		pMissionTimer->ConnectPort( 0, pBundle, 0 );
		pMissionTimer->ConnectPort( 2, pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "AftEventTimer_A", 16 );
		pEventTime->Mode_Test.Connect( pBundle, 0 );
		pEventTime->Mode_Up.Connect( pBundle, 1 );
		pEventTime->Control_Stop.Connect( pBundle, 2 );
		pEventTime->Control_Start.Connect( pBundle, 3 );
		pEventTime->Timer_Reset.Connect( pBundle, 4 );
		pEventTime->Timer_Set.Connect( pBundle, 5 );

		pBundle = STS()->BundleManager()->CreateBundle( "AftEventTimer_B", 16 );
		pEventTime->Seconds_1.Connect( pBundle, 0 );
		pEventTime->Seconds_2.Connect( pBundle, 1 );
		pEventTime->Seconds_4.Connect( pBundle, 2 );
		pEventTime->Seconds_8.Connect( pBundle, 3 );
		pEventTime->Seconds_10.Connect( pBundle, 4 );
		pEventTime->Seconds_20.Connect( pBundle, 5 );
		pEventTime->Seconds_40.Connect( pBundle, 6 );
		pEventTime->Minutes_1.Connect( pBundle, 7 );
		pEventTime->Minutes_2.Connect( pBundle, 8 );
		pEventTime->Minutes_4.Connect( pBundle, 9 );
		pEventTime->Minutes_8.Connect( pBundle, 10 );
		pEventTime->Minutes_10.Connect( pBundle, 11 );
		pEventTime->Minutes_20.Connect( pBundle, 12 );
		pEventTime->Minutes_40.Connect( pBundle, 13 );

		AtlantisPanel::Realize();
		return;
	}
}
