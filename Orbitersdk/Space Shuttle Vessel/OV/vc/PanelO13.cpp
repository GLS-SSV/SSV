/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
2022/09/25   GLS
2022/09/29   GLS
********************************************/
#include "PanelO13.h"
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o13.h"


namespace vc
{
	PanelO13::PanelO13( Atlantis* _sts ):AtlantisPanel( _sts, "O13" )
	{
		DefineMesh( MESHNAME_PANELO13 );

		Add( pCW_A = new CircuitBreaker( _sts, "C&W A" ) );
		pCW_A->SetInitialPosition( true );

		Add( pCW_B = new CircuitBreaker( _sts, "C&W B" ) );
		pCW_B->SetInitialPosition( true );
	}

	PanelO13::~PanelO13()
	{
	}

	void PanelO13::DefineVC()
	{
		VECTOR3 CB_PULL = _V( 0.615661, -0.788011, 0.0 );

		AddAIDToMouseEventList( AID_O13 );

		pCW_A->SetInitialAnimState( 1.0f );
		pCW_A->DefineGroup( GRP_CB1_O13_VC );
		pCW_A->SetDirection( CB_PULL );
		pCW_A->SetMouseRegion( AID_O13, 0.177147f, 0.078382f, 0.294141f, 0.135277f );

		pCW_B->SetInitialAnimState( 1.0f );
		pCW_B->DefineGroup( GRP_CB9_O13_VC );
		pCW_B->SetDirection( CB_PULL );
		pCW_B->SetMouseRegion( AID_O13, 0.175674f, 0.364423f, 0.292300f, 0.420858f );
		return;
	}

	void PanelO13::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O13, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O13,
			_V( -0.9374, 3.023, 13.226 ) + ofs, _V( -0.8098, 3.122, 13.226 ) + ofs,
			_V( -0.9374, 3.023, 13.579 ) + ofs, _V( -0.8098, 3.122, 13.579 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO13::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "CW_SW_2", 16 );
		pCW_A->Connect( pBundle, 11 );
		pCW_B->Connect( pBundle, 12 );

		AtlantisPanel::Realize();
		return;
	}
}
