#include "PanelA11_099_103_104.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a11_099_103_104.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA11_099_103_104";
	constexpr VECTOR3 OFFSET_PANEL = {0.8001, 1.27607, 12.4756};


	PanelA11_099_103_104::PanelA11_099_103_104( Atlantis* _sts ) : AtlantisPanel( _sts, "A11" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pCryoTank4HeatersO2A = new StdSwitch3( _sts, "CRYO TANK 4 HEATERS O2 A" ) );
		pCryoTank4HeatersO2A->SetLabel( 0, "ON" );
		pCryoTank4HeatersO2A->SetLabel( 1, "OFF" );
		pCryoTank4HeatersO2A->SetLabel( 2, "AUTO" );
		Add( pCryoTank4HeatersO2B = new StdSwitch3( _sts, "CRYO TANK 4 HEATERS O2 B" ) );
		pCryoTank4HeatersO2B->SetLabel( 0, "ON" );
		pCryoTank4HeatersO2B->SetLabel( 1, "OFF" );
		pCryoTank4HeatersO2B->SetLabel( 2, "AUTO" );
		Add( pCryoTank4HeatersO2ResetTest = new StdSwitch3( _sts, "CRYO TANK 4 HEATERS O2 RESET TEST" ) );
		Add( pCryoTank4HeatersH2A = new StdSwitch3( _sts, "CRYO TANK 4 HEATERS H2 A" ) );
		pCryoTank4HeatersH2A->SetLabel( 0, "ON" );
		pCryoTank4HeatersH2A->SetLabel( 1, "OFF" );
		pCryoTank4HeatersH2A->SetLabel( 2, "AUTO" );
		Add( pCryoTank4HeatersH2B = new StdSwitch3( _sts, "CRYO TANK 4 HEATERS H2 B" ) );
		pCryoTank4HeatersH2B->SetLabel( 0, "ON" );
		pCryoTank4HeatersH2B->SetLabel( 1, "OFF" );
		pCryoTank4HeatersH2B->SetLabel( 2, "AUTO" );

		Add( pMSCommCCUPwr = new StdSwitch2( _sts, "MS COMM CCU PWR" ) );
		pMSCommCCUPwr->SetLabel( 0, "OFF" );
		pMSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pDCUtilityPower = new StdSwitch2( _sts, "DC UTILITY POWER" ) );
		pDCUtilityPower->SetLabel( 0, "OFF" );
		pDCUtilityPower->SetLabel( 1, "ON" );
		return;
	}

	PanelA11_099_103_104::~PanelA11_099_103_104( void )
	{
		return;
	}

	void PanelA11_099_103_104::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );

		AddAIDToMouseEventList( AID_A11 );

		pCryoTank4HeatersO2A->DefineGroup( GRP_S1_A11_099_103_104_VC );
		pCryoTank4HeatersO2A->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2A->SetMouseRegion( AID_A11, 0.601616f, 0.129450f, 0.647027f, 0.161360f );

		pCryoTank4HeatersO2B->DefineGroup( GRP_S2_A11_099_103_104_VC );
		pCryoTank4HeatersO2B->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2B->SetMouseRegion( AID_A11, 0.664558f, 0.129450f, 0.702383f, 0.161360f );

		pCryoTank4HeatersO2ResetTest->DefineGroup( GRP_S3_A11_099_103_104_VC );
		pCryoTank4HeatersO2ResetTest->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2ResetTest->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.129450f, 0.763174f, 0.161360f );
		pCryoTank4HeatersO2ResetTest->SetSpringLoaded( true, 0 );
		pCryoTank4HeatersO2ResetTest->SetSpringLoaded( true, 2 );

		pCryoTank4HeatersH2A->DefineGroup( GRP_S4_A11_099_103_104_VC );
		pCryoTank4HeatersH2A->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersH2A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersH2A->SetMouseRegion( AID_A11, 0.781676f, 0.129450f, 0.820024f, 0.161360f );

		pCryoTank4HeatersH2B->DefineGroup( GRP_S5_A11_099_103_104_VC );
		pCryoTank4HeatersH2B->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersH2B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersH2B->SetMouseRegion( AID_A11, 0.836851f, 0.129450f, 0.883301f, 0.161360f );


		pMSCommCCUPwr->DefineGroup( GRP_S11_A11_099_103_104_VC );
		pMSCommCCUPwr->SetInitialAnimState( 0.5 );
		pMSCommCCUPwr->SetReference( _V( 0.0, 0.634462, -0.025329 ), switch_rot );
		pMSCommCCUPwr->SetMouseRegion( AID_A11, 0.683569f, 0.226172f, 0.721536f, 0.250722f );

		pDCUtilityPower->DefineGroup( GRP_S13_A11_099_103_104_VC );
		pDCUtilityPower->SetInitialAnimState( 0.5 );
		pDCUtilityPower->SetReference( _V( 0.0, 0.545504, -0.025329 ), switch_rot );
		pDCUtilityPower->SetMouseRegion( AID_A11, 0.769007f, 0.333452f, 0.804333f, 0.356417f );
		return;
	}

	void PanelA11_099_103_104::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A11, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A11,
			_V( 0.56014, 0.83336, -0.0254 ) + ofs, _V( 0.0, 0.83336, -0.0254 ) + ofs,
			_V( 0.56014, 0.0, -0.0254 ) + ofs, _V( 0.0, 0.0, -0.0254 ) + ofs );
		return;
	}

	void PanelA11_099_103_104::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}
}
