/******* SSV File Modification Notice *******
Date         Developer
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
********************************************/
#include "PanelO15.h"
#include "StandardSwitch.h"
#include "CircuitBreaker.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_o15.h"


namespace vc
{
	PanelO15::PanelO15( Atlantis* _sts ):AtlantisPanel( _sts, "O15" )
	{
		DefineMesh( MESHNAME_PANELO15 );

		Add( pBRAKES_MN_B = new StdSwitch2( _sts, "BRAKES MN B" ) );
		pBRAKES_MN_B->SetLabel( 0, "OFF" );
		pBRAKES_MN_B->SetLabel( 1, "ON" );

		Add( pMDM_OF_12_B = new CircuitBreaker( _sts, "MDM OF 1/2 B" ) );
		pMDM_OF_12_B->SetInitialPosition( true );

		Add( pNOSE_WHEEL_STEERING_MN_B = new CircuitBreaker( _sts, "NOSE WHEEL STEERING MN B" ) );
		pNOSE_WHEEL_STEERING_MN_B->SetInitialPosition( true );

		Add( pSTAR_TRKR_Y = new CircuitBreaker( _sts, "STAR TRKR -Y" ) );
		pSTAR_TRKR_Y->SetInitialPosition( true );

		Add( pDDU_LEFT_MN_B = new CircuitBreaker( _sts, "DDU LEFT MN B" ) );
		pDDU_LEFT_MN_B->SetInitialPosition( true );

		Add( pDDU_RIGHT_MN_B = new CircuitBreaker( _sts, "DDU RIGHT MN B" ) );
		pDDU_RIGHT_MN_B->SetInitialPosition( true );
	}

	PanelO15::~PanelO15()
	{
	}

	void PanelO15::DefineVC()
	{
		VECTOR3 SWITCH_ROT = _V( 1.0, 0.0, 0.0 );
		VECTOR3 CB_PULL = _V( 0.0, -1.0, 0.0 );

		AddAIDToMouseEventList( AID_O15 );

		pBRAKES_MN_B->SetInitialAnimState( 0.5f );
		pBRAKES_MN_B->DefineGroup( GRP_S1_O15_VC );
		pBRAKES_MN_B->SetReference( _V( -0.16394, 3.18545, 13.2829 ), SWITCH_ROT );
		pBRAKES_MN_B->SetMouseRegion( AID_O15, 0.109116f, 0.172754f, 0.165937f, 0.221280f );

		pMDM_OF_12_B->SetInitialAnimState( 1.0f );
		pMDM_OF_12_B->DefineGroup( GRP_CB5_O15_VC );
		pMDM_OF_12_B->SetDirection( CB_PULL );
		pMDM_OF_12_B->SetMouseRegion( AID_O15, 0.400301f, 0.337088f, 0.454505f, 0.389520f );

		pNOSE_WHEEL_STEERING_MN_B->SetInitialAnimState( 1.0f );
		pNOSE_WHEEL_STEERING_MN_B->DefineGroup( GRP_CB41_O15_VC );
		pNOSE_WHEEL_STEERING_MN_B->SetDirection( CB_PULL );
		pNOSE_WHEEL_STEERING_MN_B->SetMouseRegion( AID_O15, 0.259781f, 0.590850f, 0.309601f, 0.638679f );

		pSTAR_TRKR_Y->SetInitialAnimState( 1.0f );
		pSTAR_TRKR_Y->DefineGroup( GRP_CB26_O15_VC );
		pSTAR_TRKR_Y->SetDirection( CB_PULL );
		pSTAR_TRKR_Y->SetMouseRegion( AID_O15, 0.328963f, 0.695190f, 0.387294f, 0.752352f );

		pDDU_LEFT_MN_B->SetInitialAnimState( 1.0f );
		pDDU_LEFT_MN_B->DefineGroup( GRP_CB29_O15_VC );
		pDDU_LEFT_MN_B->SetDirection( CB_PULL );
		pDDU_LEFT_MN_B->SetMouseRegion( AID_O15, 0.537924f, 0.701171f, 0.590104f, 0.748846f );

		pDDU_RIGHT_MN_B->SetInitialAnimState( 1.0f );
		pDDU_RIGHT_MN_B->DefineGroup( GRP_CB30_O15_VC );
		pDDU_RIGHT_MN_B->SetDirection( CB_PULL );
		pDDU_RIGHT_MN_B->SetMouseRegion( AID_O15, 0.611308f, 0.701257f, 0.668372f, 0.751584f );
		return;
	}

	void PanelO15::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O15, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O15,
			_V( -0.21516, 3.18687, 13.2044 ) + ofs, _V( 0.199259, 3.18771, 13.2044 ) + ofs,
			_V( -0.21516, 3.18591, 13.6093 ) + ofs, _V( 0.199259, 3.18591, 13.6093 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO15::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "BRAKES", 16 );
		pBRAKES_MN_B->ConnectPort( 1, pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_Power", 16 );
		pMDM_OF_12_B->Connect( pBundle, 14 );

		pBundle = STS()->BundleManager()->CreateBundle( "DDU_POWER", 16 );
		pDDU_LEFT_MN_B->Connect( pBundle, 0 );
		pDDU_RIGHT_MN_B->Connect( pBundle, 5 );

		pBundle = STS()->BundleManager()->CreateBundle( "NWS", 16 );
		pNOSE_WHEEL_STEERING_MN_B->Connect( pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "STAR_TRACKER_POWER", 16 );
		pSTAR_TRKR_Y->Connect( pBundle, 1 );

		AtlantisPanel::Realize();
		return;
	}
};