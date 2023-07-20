/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/07/11   GLS
2021/08/22   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelO17.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o17.h"


namespace vc
{

	PanelO17::PanelO17(Atlantis* psts):AtlantisPanel(psts, "O17")
	{
		DefineMesh( MESHNAME_PANELO17 );

		Add( pATVC[0] = new StdSwitch2( psts, "ATVC 1" ) );
		pATVC[0]->SetLabel( 0, "OFF" );
		pATVC[0]->SetLabel( 1, "ON" );
		Add( pATVC[1] = new StdSwitch2( psts, "ATVC 2" ) );
		pATVC[1]->SetLabel( 0, "OFF" );
		pATVC[1]->SetLabel( 1, "ON" );
		Add( pATVC[2] = new StdSwitch2( psts, "ATVC 3" ) );
		pATVC[2]->SetLabel( 0, "OFF" );
		pATVC[2]->SetLabel( 1, "ON" );
		Add( pATVC[3] = new StdSwitch2( psts, "ATVC 4" ) );
		pATVC[3]->SetLabel( 0, "OFF" );
		pATVC[3]->SetLabel( 1, "ON" );

		Add( pEIU_LC = new StdSwitch2( psts, "EIU L-C" ) );
		pEIU_LC->SetLabel( 0, "OFF" );
		pEIU_LC->SetLabel( 1, "ON" );

		Add( pEIU_CR = new StdSwitch2( psts, "EIU C-R" ) );
		pEIU_CR->SetLabel( 0, "OFF" );
		pEIU_CR->SetLabel( 1, "ON" );

		Add( pEIU_RL = new StdSwitch2( psts, "EIU R-L" ) );
		pEIU_RL->SetLabel( 0, "OFF" );
		pEIU_RL->SetLabel( 1, "ON" );

		Add( pMDM_OA123 = new StdSwitch2( psts, "MDM OA1/2/3" ) );
		pMDM_OA123->SetLabel( 0, "OFF" );
		pMDM_OA123->SetLabel( 1, "ON" );

		Add( pMEC[0] = new StdSwitch2( psts, "MEC 1" ) );
		pMEC[0]->SetLabel( 0, "OFF" );
		pMEC[0]->SetLabel( 1, "ON" );
		Add( pMEC[1] = new StdSwitch2( psts, "MEC 2" ) );
		pMEC[1]->SetLabel( 0, "OFF" );
		pMEC[1]->SetLabel( 1, "ON" );
	}

	PanelO17::~PanelO17()
	{
	}

	void PanelO17::DefineVC()
	{
		const VECTOR3 SWITCH_ROT = _V( 0.788502306017, -0.615031798693, 0.0 );
		AddAIDToMouseEventList( AID_O17 );

		pATVC[0]->SetInitialAnimState( 0.5f );
		pATVC[0]->DefineGroup( GRP_S1_O17_VC );
		pATVC[0]->SetReference( _V( 0.75668, 3.1587, 13.278351 ), SWITCH_ROT );
		pATVC[0]->SetMouseRegion( AID_O17, 0.106819f, 0.161480f, 0.158223f, 0.204400f );

		pATVC[1]->SetInitialAnimState( 0.5f );
		pATVC[1]->DefineGroup( GRP_S2_O17_VC );
		pATVC[1]->SetReference( _V( 0.75668, 3.1587, 13.278351 ), SWITCH_ROT );
		pATVC[1]->SetMouseRegion( AID_O17, 0.201367f, 0.161480f, 0.253558f, 0.204400f );

		pATVC[2]->SetInitialAnimState( 0.5f );
		pATVC[2]->DefineGroup( GRP_S3_O17_VC );
		pATVC[2]->SetReference( _V( 0.75668, 3.1587, 13.278351 ), SWITCH_ROT );
		pATVC[2]->SetMouseRegion( AID_O17, 0.300887f, 0.161480f, 0.353027f, 0.204400f );

		pATVC[3]->SetInitialAnimState( 0.5f );
		pATVC[3]->DefineGroup( GRP_S4_O17_VC );
		pATVC[3]->SetReference( _V( 0.75668, 3.1587, 13.278351 ), SWITCH_ROT );
		pATVC[3]->SetMouseRegion( AID_O17, 0.396741f, 0.161480f, 0.447839f, 0.204400f );

		pEIU_LC->SetInitialAnimState( 0.5f );
		pEIU_LC->DefineGroup( GRP_S8_O17_VC );
		pEIU_LC->SetReference( _V( 0.7605, 3.1545, 13.336 ), SWITCH_ROT );
		pEIU_LC->SetMouseRegion( AID_O17, 0.106819f, 0.302806f, 0.158223f, 0.348183f );

		pEIU_CR->SetInitialAnimState( 0.5f );
		pEIU_CR->DefineGroup( GRP_S7_O17_VC );
		pEIU_CR->SetReference( _V (0.78925, 3.1325, 13.336 ), SWITCH_ROT );
		pEIU_CR->SetMouseRegion( AID_O17, 0.201367f, 0.302806f, 0.253558f, 0.348183f );

		pEIU_RL->SetInitialAnimState( 0.5f );
		pEIU_RL->DefineGroup( GRP_S9_O17_VC );
		pEIU_RL->SetReference( _V( 0.81725, 3.1105, 13.3365 ), SWITCH_ROT );
		pEIU_RL->SetMouseRegion( AID_O17, 0.300887f, 0.302806f, 0.353027f, 0.348183f );

		pMDM_OA123->SetInitialAnimState( 0.5f );
		pMDM_OA123->DefineGroup( GRP_S19_O17_VC );
		pMDM_OA123->SetReference( _V( 0.8507, 3.0852, 13.4520 ), SWITCH_ROT );
		pMDM_OA123->SetMouseRegion( AID_O17, 0.201367f, 0.589246f, 0.253558f, 0.634865f );

		pMEC[0]->SetInitialAnimState( 0.5f );
		pMEC[0]->DefineGroup( GRP_S5_O17_VC );
		pMEC[0]->SetReference( _V( 0.8507, 3.0852, 13.4520 ), SWITCH_ROT );
		pMEC[0]->SetMouseRegion( AID_O17, 0.300887f, 0.589246f, 0.353027f, 0.634865f );

		pMEC[1]->SetInitialAnimState( 0.5f );
		pMEC[1]->DefineGroup( GRP_S6_O17_VC );
		pMEC[1]->SetReference( _V( 0.8507, 3.0852, 13.4520 ), SWITCH_ROT );
		pMEC[1]->SetMouseRegion( AID_O17, 0.396741f, 0.589246f, 0.447839f, 0.634865f );
		return;
	}

	void PanelO17::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O17, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O17,
			_V( 0.721258, 3.18682, 13.20465 ) + ofs, _V( 1.021227, 2.952998, 13.20465 ) + ofs,
			_V( 0.721258, 3.18682, 13.6095 ) + ofs, _V( 1.021227, 2.952998, 13.6095 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelO17::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "ATVC_POWER", 4 );
		pATVC[0]->ConnectPort( 1, pBundle, 0 );
		pATVC[1]->ConnectPort( 1, pBundle, 1 );
		pATVC[2]->ConnectPort( 1, pBundle, 2 );
		pATVC[3]->ConnectPort( 1, pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "O17_to_EIU", 3 );
		pEIU_CR->ConnectPort( 1, pBundle, 0 );// CNTL AB2 / CNTL BC1 (MNA APC4)
		pEIU_LC->ConnectPort( 1, pBundle, 1 );// CNTL BC1 / CNTL CA2 (MNB APC5)
		pEIU_RL->ConnectPort( 1, pBundle, 2 );// CNTL CA2 / CNTL AB3 (MNC APC6)

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_Power", 16 );
		pMDM_OA123->ConnectPort( 1, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "O17_MEC", 2 );
		pMEC[0]->ConnectPort( 1, pBundle, 0 );
		pMEC[1]->ConnectPort( 1, pBundle, 1 );

		AtlantisPanel::Realize();
		return;
	}
}
