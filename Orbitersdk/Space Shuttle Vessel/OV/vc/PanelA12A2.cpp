/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/05/24   GLS
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
2022/09/29   GLS
********************************************/
#include "PanelA12A2.h"
#include "StandardSwitch.h"
#include "Keyboard.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_A12A2.h"


namespace vc
{
	PanelA12A2::PanelA12A2( Atlantis *_sts, bool defaultposition ) : AtlantisPanel( _sts, defaultposition ? "R12L" : "R11L" )
	{
		DefineMesh( MESHNAME_PANELA12A2 );

		Add( pKeyboardAft = new Keyboard( _sts, "KEYBOARD", 3 ) );

		Add( pIDPCRTPower = new StdSwitch2( _sts, "IDP/CRT 4 POWER" ) );
		pIDPCRTPower->SetLabel( 0, "OFF" );
		pIDPCRTPower->SetLabel( 1, "ON" );
		pIDPCRTPower->SetInitialPosition( 1 );

		Add( pIDPCRTMajFunc = new StdSwitch3( _sts, "IDP/CRT 4 MAJ FUNC" ) );
		pIDPCRTMajFunc->SetLabel( 0, "PL" );
		pIDPCRTMajFunc->SetLabel( 1, "SM" );
		pIDPCRTMajFunc->SetLabel( 2, "GNC" );
		pIDPCRTMajFunc->SetInitialPosition( 2 );
	}

	PanelA12A2::~PanelA12A2()
	{
	}

	void PanelA12A2::DefineVC()
	{
		VECTOR3 switch_rot = _V( 0, 0, -1 );
		VECTOR3 panel_normal = _V( -0.547240, 0.836976, 0.0 );

		AddAIDToMouseEventList( AID_A12A2 );

		UINT AftKeyboardGrp[32] = {GRP_MSS_KEYBOARD_FAULTSUMM_A12A2_VC, GRP_MSS_KEYBOARD_SYSSUMM_A12A2_VC, GRP_MSS_KEYBOARD_MSGRESET_A12A2_VC, GRP_MSS_KEYBOARD_ACK_A12A2_VC,
					GRP_MSS_KEYBOARD_GPCCRT_A12A2_VC, GRP_MSS_KEYBOARD_A_A12A2_VC, GRP_MSS_KEYBOARD_B_A12A2_VC, GRP_MSS_KEYBOARD_C_A12A2_VC,
					GRP_MSS_KEYBOARD_IORESET_A12A2_VC, GRP_MSS_KEYBOARD_D_A12A2_VC, GRP_MSS_KEYBOARD_E_A12A2_VC, GRP_MSS_KEYBOARD_F_A12A2_VC,
					GRP_MSS_KEYBOARD_ITEM_A12A2_VC, GRP_MSS_KEYBOARD_1_A12A2_VC, GRP_MSS_KEYBOARD_2_A12A2_VC, GRP_MSS_KEYBOARD_3_A12A2_VC,
					GRP_MSS_KEYBOARD_EXEC_A12A2_VC, GRP_MSS_KEYBOARD_4_A12A2_VC, GRP_MSS_KEYBOARD_5_A12A2_VC, GRP_MSS_KEYBOARD_6_A12A2_VC,
					GRP_MSS_KEYBOARD_OPS_A12A2_VC, GRP_MSS_KEYBOARD_7_A12A2_VC, GRP_MSS_KEYBOARD_8_A12A2_VC, GRP_MSS_KEYBOARD_9_A12A2_VC,
					GRP_MSS_KEYBOARD_SPEC_A12A2_VC, GRP_MSS_KEYBOARD_MINUS_A12A2_VC, GRP_MSS_KEYBOARD_0_A12A2_VC, GRP_MSS_KEYBOARD_PLUS_A12A2_VC,
					GRP_MSS_KEYBOARD_RESUME_A12A2_VC, GRP_MSS_KEYBOARD_CLEAR_A12A2_VC, GRP_MSS_KEYBOARD_DOT_A12A2_VC, GRP_MSS_KEYBOARD_PRO_A12A2_VC};
		pKeyboardAft->DefineGroup( AftKeyboardGrp );
		pKeyboardAft->SetDirection( -panel_normal );
		pKeyboardAft->SetMouseRegion( AID_A12A2, 0.096993f, 0.052562f, 0.263457f, 0.581455f );

		pIDPCRTPower->SetInitialAnimState( 0.5f );
		pIDPCRTPower->DefineGroup( GRP_S1_A12A2_VC );
		pIDPCRTPower->SetReference( _V( 1.2491, 2.2434, 13.4210 ), switch_rot );
		pIDPCRTPower->SetMouseRegion( AID_A12A2, 0.351296f, 0.252018f, 0.387000f, 0.325645f );


		pIDPCRTMajFunc->SetInitialAnimState( 0.5f );
		pIDPCRTMajFunc->DefineGroup( GRP_S2_A12A2_VC );
		pIDPCRTMajFunc->SetReference( _V( 1.1616, 2.1864, 13.4197 ), switch_rot );
		pIDPCRTMajFunc->SetMouseRegion( AID_A12A2, 0.354039f, 0.559495f, 0.389576f, 0.630744f );
	}

	void PanelA12A2::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_A12A2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A12A2,
			_V( 1.3315, 2.29614, 13.6093 ) + ofs, _V( 1.3315, 2.29657, 13.0865 ) + ofs,
			_V( 1.04733, 2.11034, 13.6093 ) + ofs, _V( 1.04728, 2.11042, 13.0865 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
	}

	void PanelA12A2::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "C2_A12A1_A12A2_IDP", 14 );
		pIDPCRTPower->ConnectPort( 1, pBundle, 3 );

		pIDPCRTMajFunc->ConnectPort( 0, pBundle, 7 );

		pIDPCRTMajFunc->ConnectPort( 2, pBundle, 11 );


		pKeyboardAft->ConnectIDP( 0, STS()->GetIDP( 4 ) );

		AtlantisPanel::Realize();
		return;
	}
}
