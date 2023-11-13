/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/07/11   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/11/12   GLS
********************************************/
#include "PanelO16.h"
#include "StandardSwitch.h"
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o16.h"


namespace vc
{
	PanelO16::PanelO16( Atlantis* _sts ):AtlantisPanel( _sts, "O16" )
	{
		DefineMesh( MESHNAME_PANELO16 );

		Add( pBRAKES_MN_C = new StdSwitch2( _sts, "BRAKES MN C" ) );
		pBRAKES_MN_C->SetLabel( 0, "OFF" );
		pBRAKES_MN_C->SetLabel( 1, "ON" );

		Add( pMDM_OF_34_B = new CircuitBreaker( _sts, "MDM OF 3/4 B" ) );
		pMDM_OF_34_B->SetInitialPosition( true );

		Add( pDDU_RIGHT_MN_C = new CircuitBreaker( _sts, "DDU RIGHT MN C" ) );
		pDDU_RIGHT_MN_C->SetInitialPosition( true );

		Add( pDDU_AFT_MN_C = new CircuitBreaker( _sts, "DDU AFT MN C" ) );
		pDDU_AFT_MN_C->SetInitialPosition( true );

		Add( pRJDA_2B_LOGIC = new StdSwitch2( _sts, "RJDA 2B LOGIC" ) );
		pRJDA_2B_LOGIC->SetLabel( 0, "OFF" );
		pRJDA_2B_LOGIC->SetLabel( 1, "ON" );
		pRJDA_2B_LOGIC->SetInitialPosition( 1 );

		Add( pRJDA_2B_DRIVER = new StdSwitch2( _sts, "RJDA 2B DRIVER" ) );
		pRJDA_2B_DRIVER->SetLabel( 0, "OFF" );
		pRJDA_2B_DRIVER->SetLabel( 1, "ON" );
		pRJDA_2B_DRIVER->SetInitialPosition( 1 );

		Add( pRJDF_2A_LOGIC = new StdSwitch2( _sts, "RJDF 2A LOGIC" ) );
		pRJDF_2A_LOGIC->SetLabel( 0, "OFF" );
		pRJDF_2A_LOGIC->SetLabel( 1, "ON" );
		pRJDF_2A_LOGIC->SetInitialPosition( 1 );

		Add( pRJDF_2A_DRIVER = new StdSwitch2( _sts, "RJDF 2A DRIVER" ) );
		pRJDF_2A_DRIVER->SetLabel( 0, "OFF" );
		pRJDF_2A_DRIVER->SetLabel( 1, "ON" );
		pRJDF_2A_DRIVER->SetInitialPosition( 1 );

		Add( pRJDF_2B_LOGIC = new StdSwitch2( _sts, "RJDF 2B LOGIC" ) );
		pRJDF_2B_LOGIC->SetLabel( 0, "OFF" );
		pRJDF_2B_LOGIC->SetLabel( 1, "ON" );
		pRJDF_2B_LOGIC->SetInitialPosition( 1 );

		Add( pRJDF_2B_DRIVER = new StdSwitch2( _sts, "RJDF 2B DRIVER" ) );
		pRJDF_2B_DRIVER->SetLabel( 0, "OFF" );
		pRJDF_2B_DRIVER->SetLabel( 1, "ON" );
		pRJDF_2B_DRIVER->SetInitialPosition( 1 );

		Add( pR_OMS_ENG_VLV = new StdSwitch2( _sts, "R OMS ENG VLV" ) );
		pR_OMS_ENG_VLV->SetLabel( 0, "OFF" );
		pR_OMS_ENG_VLV->SetLabel( 1, "ON" );
		pR_OMS_ENG_VLV->SetInitialPosition( 1 );

		Add( pRJD_MANF_DRIVER = new StdSwitch2( _sts, "RJD MANF DRIVER" ) );
		pRJD_MANF_DRIVER->SetLabel( 0, "OFF" );
		pRJD_MANF_DRIVER->SetLabel( 1, "ON" );
		pRJD_MANF_DRIVER->SetInitialPosition( 1 );
	}

	PanelO16::~PanelO16()
	{
	}

	void PanelO16::DefineVC()
	{
		VECTOR3 SWITCH_ROT = _V( 1.0, 0.0, 0.0 );
		VECTOR3 CB_PULL = _V( 0.0, -1.0, 0.0 );

		AddAIDToMouseEventList( AID_O16 );

		pBRAKES_MN_C->SetInitialAnimState( 0.5f );
		pBRAKES_MN_C->DefineGroup( GRP_S1_O16_VC );
		pBRAKES_MN_C->SetReference( _V( 0.268704, 3.18545, 13.275 ), SWITCH_ROT );
		pBRAKES_MN_C->SetMouseRegion( AID_O16, 0.122328f, 0.151632f, 0.163512f, 0.197418f );

		pMDM_OF_34_B->SetInitialAnimState( 1.0f );
		pMDM_OF_34_B->DefineGroup( GRP_CB3_O16_VC );
		pMDM_OF_34_B->SetDirection( CB_PULL );
		pMDM_OF_34_B->SetMouseRegion( AID_O16, 0.219559f, 0.323496f, 0.260889f, 0.369393f );

		pDDU_RIGHT_MN_C->SetInitialAnimState( 1.0f );
		pDDU_RIGHT_MN_C->DefineGroup( GRP_CB22_O16_VC );
		pDDU_RIGHT_MN_C->SetDirection( CB_PULL );
		pDDU_RIGHT_MN_C->SetMouseRegion( AID_O16, 0.386919f, 0.683403f, 0.427044f, 0.728441f );

		pDDU_AFT_MN_C->SetInitialAnimState( 1.0f );
		pDDU_AFT_MN_C->DefineGroup( GRP_CB23_O16_VC );
		pDDU_AFT_MN_C->SetDirection( CB_PULL );
		pDDU_AFT_MN_C->SetMouseRegion( AID_O16, 0.443351f, 0.682820f, 0.484950f, 0.728806f );

		pRJDA_2B_LOGIC->SetInitialAnimState( 0.5f );
		pRJDA_2B_LOGIC->DefineGroup( GRP_S3_O16_VC );
		pRJDA_2B_LOGIC->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJDA_2B_LOGIC->SetMouseRegion( AID_O16, 0.112245f, 0.818639f, 0.154459f, 0.872149f );

		pRJDA_2B_DRIVER->SetInitialAnimState( 0.5f );
		pRJDA_2B_DRIVER->DefineGroup( GRP_S4_O16_VC );
		pRJDA_2B_DRIVER->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJDA_2B_DRIVER->SetMouseRegion( AID_O16, 0.184150f, 0.818639f, 0.226174f, 0.872149f );

		pRJDF_2A_LOGIC->SetInitialAnimState( 0.5f );
		pRJDF_2A_LOGIC->DefineGroup( GRP_S5_O16_VC );
		pRJDF_2A_LOGIC->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJDF_2A_LOGIC->SetMouseRegion( AID_O16, 0.257171f, 0.818639f, 0.298899f, 0.872149f );

		pRJDF_2A_DRIVER->SetInitialAnimState( 0.5f );
		pRJDF_2A_DRIVER->DefineGroup( GRP_S6_O16_VC );
		pRJDF_2A_DRIVER->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJDF_2A_DRIVER->SetMouseRegion( AID_O16, 0.314629f, 0.818639f, 0.367993f, 0.872149f );

		pRJDF_2B_LOGIC->SetInitialAnimState( 0.5f );
		pRJDF_2B_LOGIC->DefineGroup( GRP_S12_O16_VC );
		pRJDF_2B_LOGIC->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJDF_2B_LOGIC->SetMouseRegion( AID_O16, 0.380998f, 0.818639f, 0.424960f, 0.872149f );

		pRJDF_2B_DRIVER->SetInitialAnimState( 0.5f );
		pRJDF_2B_DRIVER->DefineGroup( GRP_S13_O16_VC );
		pRJDF_2B_DRIVER->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJDF_2B_DRIVER->SetMouseRegion( AID_O16, 0.437778f, 0.818639f, 0.490072f, 0.872149f );

		pR_OMS_ENG_VLV->SetInitialAnimState( 0.5f );
		pR_OMS_ENG_VLV->DefineGroup( GRP_S7_O16_VC );
		pR_OMS_ENG_VLV->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pR_OMS_ENG_VLV->SetMouseRegion( AID_O16, 0.503610f, 0.818639f, 0.546293f, 0.872149f );

		pRJD_MANF_DRIVER->SetInitialAnimState( 0.5f );
		pRJD_MANF_DRIVER->DefineGroup( GRP_S15_O16_VC );
		pRJD_MANF_DRIVER->SetReference( _V( 0.4679, 3.1854, 13.5473 ), SWITCH_ROT );
		pRJD_MANF_DRIVER->SetMouseRegion( AID_O16, 0.780370f, 0.818639f, 0.824181f, 0.872149f );
		return;
	}

	void PanelO16::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O16, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O16,
			_V( 0.199259, 3.18771, 13.2044 ) + ofs, _V( 0.721294, 3.18614, 13.2044 ) + ofs,
			_V( 0.199259, 3.18591, 13.6093 ) + ofs, _V( 0.721267, 3.18591, 13.6093 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO16::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "BRAKES", 16 );
		pBRAKES_MN_C->ConnectPort( 1, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_Power", 16 );
		pMDM_OF_34_B->Connect( pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "DDU_POWER", 16 );
		pDDU_RIGHT_MN_C->Connect( pBundle, 4 );
		pDDU_AFT_MN_C->Connect( pBundle, 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "OMS_ENGINE_SWITCHES", 16 );
		pR_OMS_ENG_VLV->ConnectPort( 1, 0, pBundle, 12 );
		pR_OMS_ENG_VLV->ConnectPort( 1, 1, pBundle, 13 );

		// TODO RJD power

		AtlantisPanel::Realize();
		return;
	}
}
