/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/07/11   GLS
2021/06/01   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/11/12   GLS
********************************************/
#include "PanelO14.h"
#include "StandardSwitch.h"
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o14.h"


namespace vc
{
	PanelO14::PanelO14( Atlantis* _sts ):AtlantisPanel( _sts, "O14" )
	{
		DefineMesh( MESHNAME_PANELO14 );

		Add( pBRAKES_MN_A = new StdSwitch2( _sts, "BRAKES MN A" ) );
		pBRAKES_MN_A->SetLabel( 0, "OFF" );
		pBRAKES_MN_A->SetLabel( 1, "ON" );

		Add( pMDM_OF_12_A = new CircuitBreaker( _sts, "MDM OF 1/2 A" ) );
		pMDM_OF_12_A->SetInitialPosition( true );

		Add( pMDM_OF_34_A = new CircuitBreaker( _sts, "MDM OF 3/4 A" ) );
		pMDM_OF_34_A->SetInitialPosition( true );

		Add( pSTAR_TRKR_Z = new CircuitBreaker( _sts, "STAR TRKR -Z" ) );
		pSTAR_TRKR_Z->SetInitialPosition( true );

		Add( pDDU_LEFT_MN_A = new CircuitBreaker( _sts, "DDU LEFT MN A" ) );
		pDDU_LEFT_MN_A->SetInitialPosition( true );

		Add( pDDU_AFT_MN_A = new CircuitBreaker( _sts, "DDU AFT MN A" ) );
		pDDU_AFT_MN_A->SetInitialPosition( true );

		Add( pNOSE_WHEEL_STEERING_MN_A = new CircuitBreaker( _sts, "NOSE WHEEL STEERING MN A" ) );
		pNOSE_WHEEL_STEERING_MN_A->SetInitialPosition( true );

		Add( pRJDA_1A_LOGIC = new StdSwitch2( _sts, "RJDA 1A LOGIC" ) );
		pRJDA_1A_LOGIC->SetLabel( 0, "OFF" );
		pRJDA_1A_LOGIC->SetLabel( 1, "ON" );
		pRJDA_1A_LOGIC->SetInitialPosition( 1 );

		Add( pRJDA_1A_DRIVER = new StdSwitch2( _sts, "RJDA 1A DRIVER" ) );
		pRJDA_1A_DRIVER->SetLabel( 0, "OFF" );
		pRJDA_1A_DRIVER->SetLabel( 1, "ON" );
		pRJDA_1A_DRIVER->SetInitialPosition( 1 );

		Add( pRJDA_2A_LOGIC = new StdSwitch2( _sts, "RJDA 2A LOGIC" ) );
		pRJDA_2A_LOGIC->SetLabel( 0, "OFF" );
		pRJDA_2A_LOGIC->SetLabel( 1, "ON" );
		pRJDA_2A_LOGIC->SetInitialPosition( 1 );

		Add( pRJDA_2A_DRIVER = new StdSwitch2( _sts, "RJDA 2A DRIVER" ) );
		pRJDA_2A_DRIVER->SetLabel( 0, "OFF" );
		pRJDA_2A_DRIVER->SetLabel( 1, "ON" );
		pRJDA_2A_DRIVER->SetInitialPosition( 1 );

		Add( pRJDF_1B_LOGIC = new StdSwitch2( _sts, "RJDF 1B LOGIC" ) );
		pRJDF_1B_LOGIC->SetLabel( 0, "OFF" );
		pRJDF_1B_LOGIC->SetLabel( 1, "ON" );
		pRJDF_1B_LOGIC->SetInitialPosition( 1 );

		Add( pRJDF_1B_DRIVER = new StdSwitch2( _sts, "RJDF 1B DRIVER" ) );
		pRJDF_1B_DRIVER->SetLabel( 0, "OFF" );
		pRJDF_1B_DRIVER->SetLabel( 1, "ON" );
		pRJDF_1B_DRIVER->SetInitialPosition( 1 );

		Add( pL_OMS_ENG_VLV = new StdSwitch2( _sts, "L OMS ENG VLV" ) );
		pL_OMS_ENG_VLV->SetLabel( 0, "OFF" );
		pL_OMS_ENG_VLV->SetLabel( 1, "ON" );
		pL_OMS_ENG_VLV->SetInitialPosition( 1 );
	}

	PanelO14::~PanelO14()
	{
	}

	void PanelO14::DefineVC()
	{
		VECTOR3 SWITCH_ROT = _V( 1.0, 0.0, 0.0 );
		VECTOR3 CB_PULL = _V( 0.0, -1.0, 0.0 );

		AddAIDToMouseEventList( AID_O14 );

		pBRAKES_MN_A->SetInitialAnimState( 0.5f );
		pBRAKES_MN_A->DefineGroup( GRP_S1_O14_VC );
		pBRAKES_MN_A->SetReference( _V( -0.647365, 3.18545, 13.2819 ), SWITCH_ROT );
		pBRAKES_MN_A->SetMouseRegion( AID_O14, 0.141717f, 0.169526f, 0.186154f, 0.214447f );

		pMDM_OF_12_A->SetInitialAnimState( 1.0f );
		pMDM_OF_12_A->DefineGroup( GRP_CB4_O14_VC );
		pMDM_OF_12_A->SetDirection( CB_PULL );
		pMDM_OF_12_A->SetMouseRegion( AID_O14, 0.319047f, 0.321113f, 0.358091f, 0.378700f );

		pMDM_OF_34_A->SetInitialAnimState( 1.0f );
		pMDM_OF_34_A->DefineGroup( GRP_CB5_O14_VC );
		pMDM_OF_34_A->SetDirection( CB_PULL );
		pMDM_OF_34_A->SetMouseRegion( AID_O14, 0.371195f, 0.321113f, 0.412511f, 0.378700f );

		pSTAR_TRKR_Z->SetInitialAnimState( 1.0f );
		pSTAR_TRKR_Z->DefineGroup( GRP_CB27_O14_VC );
		pSTAR_TRKR_Z->SetDirection( CB_PULL );
		pSTAR_TRKR_Z->SetMouseRegion( AID_O14, 0.310436f, 0.680053f, 0.360643f, 0.730799f );

		pDDU_LEFT_MN_A->SetInitialAnimState( 1.0f );
		pDDU_LEFT_MN_A->DefineGroup( GRP_CB30_O14_VC );
		pDDU_LEFT_MN_A->SetDirection( CB_PULL );
		pDDU_LEFT_MN_A->SetMouseRegion( AID_O14, 0.490916f, 0.682574f, 0.535039f, 0.731509f );

		pDDU_AFT_MN_A->SetInitialAnimState( 1.0f );
		pDDU_AFT_MN_A->DefineGroup( GRP_CB31_O14_VC );
		pDDU_AFT_MN_A->SetDirection( CB_PULL );
		pDDU_AFT_MN_A->SetMouseRegion( AID_O14, 0.549635f, 0.680936f, 0.586676f, 0.730200f );

		pNOSE_WHEEL_STEERING_MN_A->SetInitialAnimState( 1.0f );
		pNOSE_WHEEL_STEERING_MN_A->DefineGroup( GRP_CB23_O14_VC );
		pNOSE_WHEEL_STEERING_MN_A->SetDirection( CB_PULL );
		pNOSE_WHEEL_STEERING_MN_A->SetMouseRegion( AID_O14, 0.665127f, 0.683048f, 0.704549f, 0.729597f );

		pRJDA_1A_LOGIC->SetInitialAnimState( 0.5f );
		pRJDA_1A_LOGIC->DefineGroup( GRP_S3_O14_VC );
		pRJDA_1A_LOGIC->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pRJDA_1A_LOGIC->SetMouseRegion( AID_O14, 0.217074f, 0.804414f, 0.258620f, 0.861203f );

		pRJDA_1A_DRIVER->SetInitialAnimState( 0.5f );
		pRJDA_1A_DRIVER->DefineGroup( GRP_S4_O14_VC );
		pRJDA_1A_DRIVER->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pRJDA_1A_DRIVER->SetMouseRegion( AID_O14, 0.288432f, 0.804414f, 0.333687f, 0.861203f );

		pRJDA_2A_LOGIC->SetInitialAnimState( 0.5f );
		pRJDA_2A_LOGIC->DefineGroup( GRP_S5_O14_VC );
		pRJDA_2A_LOGIC->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pRJDA_2A_LOGIC->SetMouseRegion( AID_O14, 0.360903f, 0.804414f, 0.406915f, 0.861203f );

		pRJDA_2A_DRIVER->SetInitialAnimState( 0.5f );
		pRJDA_2A_DRIVER->DefineGroup( GRP_S6_O14_VC );
		pRJDA_2A_DRIVER->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pRJDA_2A_DRIVER->SetMouseRegion( AID_O14, 0.433949f, 0.804414f, 0.479804f, 0.861203f );

		pRJDF_1B_LOGIC->SetInitialAnimState( 0.5f );
		pRJDF_1B_LOGIC->DefineGroup( GRP_S7_O14_VC );
		pRJDF_1B_LOGIC->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pRJDF_1B_LOGIC->SetMouseRegion( AID_O14, 0.507515f, 0.804414f, 0.552477f, 0.861203f );

		pRJDF_1B_DRIVER->SetInitialAnimState( 0.5f );
		pRJDF_1B_DRIVER->DefineGroup( GRP_S8_O14_VC );
		pRJDF_1B_DRIVER->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pRJDF_1B_DRIVER->SetMouseRegion( AID_O14, 0.571362f, 0.804414f, 0.631375f, 0.861203f );

		pL_OMS_ENG_VLV->SetInitialAnimState( 0.5f );
		pL_OMS_ENG_VLV->DefineGroup( GRP_S9_O14_VC );
		pL_OMS_ENG_VLV->SetReference( _V( -0.3865, 3.1854, 13.5419 ), SWITCH_ROT );
		pL_OMS_ENG_VLV->SetMouseRegion( AID_O14, 0.653738f, 0.804414f, 0.700622f, 0.861203f );
		return;
	}

	void PanelO14::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O14, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O14,
			_V( -0.72639, 3.18614, 13.2044 ) + ofs, _V( -0.21516, 3.18687, 13.2044 ) + ofs,
			_V( -0.726224, 3.18591, 13.6093 ) + ofs, _V( -0.21516, 3.18591, 13.6093 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO14::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "BRAKES", 16 );
		pBRAKES_MN_A->ConnectPort( 1, pBundle, 0 );

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_Power", 16 );
		pMDM_OF_12_A->Connect( pBundle, 12 );
		pMDM_OF_34_A->Connect( pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "DDU_POWER", 16 );
		pDDU_LEFT_MN_A->Connect( pBundle, 1 );
		pDDU_AFT_MN_A->Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "NWS", 16 );
		pNOSE_WHEEL_STEERING_MN_A->Connect( pBundle, 0 );

		pBundle = STS()->BundleManager()->CreateBundle( "OMS_ENGINE_SWITCHES", 16 );
		pL_OMS_ENG_VLV->ConnectPort( 1, 0, pBundle, 4 );
		pL_OMS_ENG_VLV->ConnectPort( 1, 1, pBundle, 5 );

		// TODO RJD power

		pBundle = STS()->BundleManager()->CreateBundle( "STAR_TRACKER_POWER", 16 );
		pSTAR_TRKR_Z->Connect( pBundle, 0 );

		AtlantisPanel::Realize();
		return;
	}
}
