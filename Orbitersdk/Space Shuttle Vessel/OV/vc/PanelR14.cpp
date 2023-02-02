#include "PanelR14.h"
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
//#include "../meshres_vc_r14.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelR14";
	constexpr VECTOR3 OFFSET_PANEL = {1.33375, 1.626377, 13.604449};


	PanelR14::PanelR14( Atlantis* _sts ):AtlantisPanel( _sts, "R14" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pMNB_TV_A_CAMR_CAMR_PTU = new CircuitBreaker( _sts, "MNB TV A CAMR CAMR/PTU" ) );
		pMNB_TV_A_CAMR_CAMR_PTU->SetInitialPosition( true );


		/*
MNB TV A CAMR CAMR/PTU
MNB TV A CAMR CAMR HTR
MNB TV A CAMR ILLUM/PTU HTR

MNC TV B CAMR CAMR/PTU
MNC TV B CAMR CAMR HTR
MNC TV B CAMR ILLUM/PTU HTR

MNA TV C CAMR CAMR/PTU
MNA TV C CAMR CAMR HTR
MNA TV C CAMR ILLUM/PTU HTR

MNA TV D CAMR CAMR/PTU
MNA TV D CAMR CAMR HTR
MNA TV D CAMR ILLUM/PTU HTR

MNB TV RMS CAMR CAMR/PTU
MNB TV RMS CAMR WRIST ILLUM/CAMR HTR
MNB TV RMS CAMR ELB ILLUM/PTU HTR

MNA TV CONTR UNIT
MNB TV CONTR UNIT
MNA TV MON 1
MNB TV MON 2
		*/
		return;
	}

	PanelR14::~PanelR14( void )
	{
		return;
	}

	void PanelR14::DefineVC( void )
	{
		const VECTOR3 CB_PULL = _V( -0.858513, -0.512792, 0.0 );

		AddAIDToMouseEventList( AID_R14 );

		/*pMNB_TV_A_CAMR_CAMR_PTU->SetInitialAnimState( 1.0f );
		pMNB_TV_A_CAMR_CAMR_PTU->DefineGroup( GRP_CB41_R14_VC );// TODO
		pMNB_TV_A_CAMR_CAMR_PTU->SetDirection( CB_PULL );
		pMNB_TV_A_CAMR_CAMR_PTU->SetMouseRegion( AID_R14, 0.259781f, 0.590850f, 0.309601f, 0.638679f );// TODO
		*/return;
	}

	void PanelR14::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_R14, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R14,
			_V( -0.254983, 0.426891, 0.0 ) + ofs, _V( -0.254983, 0.426891, -0.519337 ) + ofs,
			_V( 0.0, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, -0.519337 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR14::Realize( void )
	{
		AtlantisPanel::Realize();

		/*DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "TODO", 16 );
		pMNB_TV_A_CAMR_CAMR_PTU->Connect( pBundle, 0 );
		*/return;
	}
}
