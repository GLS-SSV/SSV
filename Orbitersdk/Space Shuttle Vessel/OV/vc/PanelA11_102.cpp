#include "PanelA11_102.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a11_102.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA11_102";
	constexpr VECTOR3 OFFSET_PANEL = {0.8001, 1.27607, 12.4756};


	PanelA11_102::PanelA11_102( Atlantis* _sts ) : AtlantisPanel( _sts, "A11" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pCryoTank45HeatersO2TK4 = new StdSwitch3( _sts, "CRYO TANK 4/5 HEATERS O2 TK4" ) );
		pCryoTank45HeatersO2TK4->SetLabel( 0, "ON" );
		pCryoTank45HeatersO2TK4->SetLabel( 1, "OFF" );
		pCryoTank45HeatersO2TK4->SetLabel( 2, "AUTO" );
		Add( pCryoTank45HeatersO2TK5 = new StdSwitch3( _sts, "CRYO TANK 4/5 HEATERS O2 TK5" ) );
		pCryoTank45HeatersO2TK5->SetLabel( 0, "ON" );
		pCryoTank45HeatersO2TK5->SetLabel( 1, "OFF" );
		pCryoTank45HeatersO2TK5->SetLabel( 2, "AUTO" );
		Add( pCryoTank45HeatersO2TK45ResetTest = new StdSwitch3( _sts, "CRYO TANK 4/5 HEATERS O2 TK4/5 RESET TEST" ) );
		Add( pCryoTank45HeatersH2TK45A = new StdSwitch3( _sts, "CRYO TANK 4/5 HEATERS H2 TK4/5A" ) );
		pCryoTank45HeatersH2TK45A->SetLabel( 0, "ON" );
		pCryoTank45HeatersH2TK45A->SetLabel( 1, "OFF" );
		pCryoTank45HeatersH2TK45A->SetLabel( 2, "AUTO" );
		Add( pCryoTank45HeatersH2TK45B = new StdSwitch3( _sts, "CRYO TANK 4/5 HEATERS H2 TK4/5B" ) );
		pCryoTank45HeatersH2TK45B->SetLabel( 0, "ON" );
		pCryoTank45HeatersH2TK45B->SetLabel( 1, "OFF" );
		pCryoTank45HeatersH2TK45B->SetLabel( 2, "AUTO" );

		Add( pMSCommCCUPwr = new StdSwitch2( _sts, "MS COMM CCU PWR" ) );
		pMSCommCCUPwr->SetLabel( 0, "OFF" );
		pMSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pOSCommCCUPwr = new StdSwitch2( _sts, "OS COMM CCU PWR" ) );
		pOSCommCCUPwr->SetLabel( 0, "OFF" );
		pOSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pDCUtilityPower = new StdSwitch2( _sts, "DC UTILITY POWER" ) );
		pDCUtilityPower->SetLabel( 0, "OFF" );
		pDCUtilityPower->SetLabel( 1, "ON" );
		return;
	}

	PanelA11_102::~PanelA11_102( void )
	{
		return;
	}

	void PanelA11_102::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );

		AddAIDToMouseEventList( AID_A11 );

		pCryoTank45HeatersO2TK4->DefineGroup( GRP_S1_A11_102_VC );
		pCryoTank45HeatersO2TK4->SetInitialAnimState( 0.5 );
		pCryoTank45HeatersO2TK4->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank45HeatersO2TK4->SetMouseRegion( AID_A11, 0.601616f, 0.129450f, 0.647027f, 0.167532f );

		pCryoTank45HeatersO2TK5->DefineGroup( GRP_S2_A11_102_VC );
		pCryoTank45HeatersO2TK5->SetInitialAnimState( 0.5 );
		pCryoTank45HeatersO2TK5->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank45HeatersO2TK5->SetMouseRegion( AID_A11, 0.664558f, 0.129450f, 0.702383f, 0.167532f );

		pCryoTank45HeatersO2TK45ResetTest->DefineGroup( GRP_S3_A11_102_VC );
		pCryoTank45HeatersO2TK45ResetTest->SetInitialAnimState( 0.5 );
		pCryoTank45HeatersO2TK45ResetTest->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank45HeatersO2TK45ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.129450f, 0.763174f, 0.167532f );
		pCryoTank45HeatersO2TK45ResetTest->SetSpringLoaded( true, 0 );
		pCryoTank45HeatersO2TK45ResetTest->SetSpringLoaded( true, 2 );

		pCryoTank45HeatersH2TK45A->DefineGroup( GRP_S4_A11_102_VC );
		pCryoTank45HeatersH2TK45A->SetInitialAnimState( 0.5 );
		pCryoTank45HeatersH2TK45A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank45HeatersH2TK45A->SetMouseRegion( AID_A11, 0.781676f, 0.129450f, 0.820024f, 0.167532f );

		pCryoTank45HeatersH2TK45B->DefineGroup( GRP_S5_A11_102_VC );
		pCryoTank45HeatersH2TK45B->SetInitialAnimState( 0.5 );
		pCryoTank45HeatersH2TK45B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank45HeatersH2TK45B->SetMouseRegion( AID_A11, 0.836851f, 0.129450f, 0.883301f, 0.167532f );


		pMSCommCCUPwr->DefineGroup( GRP_S11_A11_102_VC );
		pMSCommCCUPwr->SetInitialAnimState( 0.5 );
		pMSCommCCUPwr->SetReference( _V( 0.0, 0.634462, -0.025329 ), switch_rot );
		pMSCommCCUPwr->SetMouseRegion( AID_A11, 0.683569f, 0.226172f, 0.721536f, 0.250722f );

		pOSCommCCUPwr->DefineGroup( GRP_S12_A11_102_VC );
		pOSCommCCUPwr->SetInitialAnimState( 0.5 );
		pOSCommCCUPwr->SetReference( _V( 0.0, 0.634462, -0.025329 ), switch_rot );
		pOSCommCCUPwr->SetMouseRegion( AID_A11, 0.869980f, 0.226172f, 0.905396f, 0.250722f );

		pDCUtilityPower->DefineGroup( GRP_S13_A11_102_VC );
		pDCUtilityPower->SetInitialAnimState( 0.5 );
		pDCUtilityPower->SetReference( _V( 0.0, 0.545504, -0.025329 ), switch_rot );
		pDCUtilityPower->SetMouseRegion( AID_A11, 0.769007f, 0.333452f, 0.804333f, 0.356417f );
		return;
	}

	void PanelA11_102::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A11, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A11,
			_V( 0.56014, 0.83336, -0.0254 ) + ofs, _V( 0.0, 0.83336, -0.0254 ) + ofs,
			_V( 0.56014, 0.0, -0.0254 ) + ofs, _V( 0.0, 0.0, -0.0254 ) + ofs );
		return;
	}

	void PanelA11_102::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}
}
