#include "PanelA11_104_EDO.h"
#include "CircuitBreaker.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a11_104_EDO.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA11_104_EDO";
	constexpr VECTOR3 OFFSET_PANEL = {0.8001, 1.27607, 12.4756};


	PanelA11_104_EDO::PanelA11_104_EDO( Atlantis* _sts ) : AtlantisPanel( _sts, "A11" )
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

		Add( pCryoTankSelect6_10_O2 = new StdSwitch3( _sts, "CRYO TANK SELECT 6/10 O2" ) );
		pCryoTankSelect6_10_O2->SetLabel( 0, "6" );
		pCryoTankSelect6_10_O2->SetLabel( 1, "-" );
		pCryoTankSelect6_10_O2->SetLabel( 2, "10" );
		Add( pCryoTankSelect6_10_H2 = new StdSwitch3( _sts, "CRYO TANK SELECT 6/10 H2" ) );
		pCryoTankSelect6_10_H2->SetLabel( 0, "6" );
		pCryoTankSelect6_10_H2->SetLabel( 1, "-" );
		pCryoTankSelect6_10_H2->SetLabel( 2, "10" );

		Add( pCryoTankSelect7_11_O2 = new StdSwitch3( _sts, "CRYO TANK SELECT 7/11 O2" ) );
		pCryoTankSelect7_11_O2->SetLabel( 0, "7" );
		pCryoTankSelect7_11_O2->SetLabel( 1, "-" );
		pCryoTankSelect7_11_O2->SetLabel( 2, "11" );
		Add( pCryoTankSelect7_11_H2 = new StdSwitch3( _sts, "CRYO TANK SELECT 7/11 H2" ) );
		pCryoTankSelect7_11_H2->SetLabel( 0, "7" );
		pCryoTankSelect7_11_H2->SetLabel( 1, "-" );
		pCryoTankSelect7_11_H2->SetLabel( 2, "11" );

		Add( pCryoTankSelect8_12_O2 = new StdSwitch3( _sts, "CRYO TANK SELECT 8/12 O2" ) );
		pCryoTankSelect8_12_O2->SetLabel( 0, "8" );
		pCryoTankSelect8_12_O2->SetLabel( 1, "-" );
		pCryoTankSelect8_12_O2->SetLabel( 2, "12" );
		Add( pCryoTankSelect8_12_H2 = new StdSwitch3( _sts, "CRYO TANK SELECT 8/12 H2" ) );
		pCryoTankSelect8_12_H2->SetLabel( 0, "8" );
		pCryoTankSelect8_12_H2->SetLabel( 1, "-" );
		pCryoTankSelect8_12_H2->SetLabel( 2, "12" );

		Add( pCryoTankSelect9_13_O2 = new StdSwitch3( _sts, "CRYO TANK SELECT 9/13 O2" ) );
		pCryoTankSelect9_13_O2->SetLabel( 0, "9" );
		pCryoTankSelect9_13_O2->SetLabel( 1, "-" );
		pCryoTankSelect9_13_O2->SetLabel( 2, "13" );
		Add( pCryoTankSelect9_13_H2 = new StdSwitch3( _sts, "CRYO TANK SELECT 9/13 H2" ) );
		pCryoTankSelect9_13_H2->SetLabel( 0, "9" );
		pCryoTankSelect9_13_H2->SetLabel( 1, "-" );
		pCryoTankSelect9_13_H2->SetLabel( 2, "13" );

		Add( pPalletCryoTank10QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 QTY O2" ) );
		Add( pPalletCryoTank10QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 QTY H2" ) );

		Add( pPalletCryoTank11QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 QTY O2" ) );
		Add( pPalletCryoTank11QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 QTY H2" ) );

		Add( pPalletCryoTank12QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 QTY O2" ) );
		Add( pPalletCryoTank12QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 QTY H2" ) );

		Add( pPalletCryoTank13QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 QTY O2" ) );
		Add( pPalletCryoTank13QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 QTY H2" ) );

		Add( pMSCommCCUPwr = new StdSwitch2( _sts, "MS COMM CCU PWR" ) );
		pMSCommCCUPwr->SetLabel( 0, "OFF" );
		pMSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pDCUtilityPower = new StdSwitch2( _sts, "DC UTILITY POWER" ) );
		pDCUtilityPower->SetLabel( 0, "OFF" );
		pDCUtilityPower->SetLabel( 1, "ON" );
		return;
	}

	PanelA11_104_EDO::~PanelA11_104_EDO( void )
	{
		return;
	}

	void PanelA11_104_EDO::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A11 );

		pCryoTank4HeatersO2A->DefineGroup( GRP_S1_A11_104_EDO_VC );
		pCryoTank4HeatersO2A->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2A->SetMouseRegion( AID_A11, 0.601616f, 0.138093f, 0.647027f, 0.161360f );

		pCryoTank4HeatersO2B->DefineGroup( GRP_S2_A11_104_EDO_VC );
		pCryoTank4HeatersO2B->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2B->SetMouseRegion( AID_A11, 0.664558f, 0.138093f, 0.702383f, 0.161360f );

		pCryoTank4HeatersO2ResetTest->DefineGroup( GRP_S3_A11_104_EDO_VC );
		pCryoTank4HeatersO2ResetTest->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2ResetTest->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.138093f, 0.763174f, 0.161360f );
		pCryoTank4HeatersO2ResetTest->SetSpringLoaded( true, 0 );
		pCryoTank4HeatersO2ResetTest->SetSpringLoaded( true, 2 );

		pCryoTank4HeatersH2A->DefineGroup( GRP_S4_A11_104_EDO_VC );
		pCryoTank4HeatersH2A->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersH2A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersH2A->SetMouseRegion( AID_A11, 0.781676f, 0.138093f, 0.820024f, 0.161360f );

		pCryoTank4HeatersH2B->DefineGroup( GRP_S5_A11_104_EDO_VC );
		pCryoTank4HeatersH2B->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersH2B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersH2B->SetMouseRegion( AID_A11, 0.836851f, 0.138093f, 0.883301f, 0.161360f );


		pCryoTankSelect6_10_O2->DefineGroup( GRP_S_A_A11_104_EDO_VC );
		pCryoTankSelect6_10_O2->SetInitialAnimState( 0.5 );
		pCryoTankSelect6_10_O2->SetReference( _V( 0.0, 0.635019, -0.025329 ), switch_rot );
		pCryoTankSelect6_10_O2->SetMouseRegion( AID_A11, 0.601616f, 0.227271f, 0.647027f, 0.250605f );

		pCryoTankSelect6_10_H2->DefineGroup( GRP_S_B_A11_104_EDO_VC );
		pCryoTankSelect6_10_H2->SetInitialAnimState( 0.5 );
		pCryoTankSelect6_10_H2->SetReference( _V( 0.0, 0.635019, -0.025329 ), switch_rot );
		pCryoTankSelect6_10_H2->SetMouseRegion( AID_A11, 0.664558f, 0.227271f, 0.702383f, 0.250605f );


		pCryoTankSelect7_11_O2->DefineGroup( GRP_S_C_A11_104_EDO_VC );
		pCryoTankSelect7_11_O2->SetInitialAnimState( 0.5 );
		pCryoTankSelect7_11_O2->SetReference( _V( 0.0, 0.635019, -0.025329 ), switch_rot );
		pCryoTankSelect7_11_O2->SetMouseRegion( AID_A11, 0.781676f, 0.227271f, 0.820024f, 0.250605f );

		pCryoTankSelect7_11_H2->DefineGroup( GRP_S_D_A11_104_EDO_VC );
		pCryoTankSelect7_11_H2->SetInitialAnimState( 0.5 );
		pCryoTankSelect7_11_H2->SetReference( _V( 0.0, 0.635019, -0.025329 ), switch_rot );
		pCryoTankSelect7_11_H2->SetMouseRegion( AID_A11, 0.836851f, 0.227271f, 0.883301f, 0.250605f );


		pCryoTankSelect8_12_O2->DefineGroup( GRP_S_E_A11_104_EDO_VC );
		pCryoTankSelect8_12_O2->SetInitialAnimState( 0.5 );
		pCryoTankSelect8_12_O2->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pCryoTankSelect8_12_O2->SetMouseRegion( AID_A11, 0.601616f, 0.317291f, 0.647027f, 0.341291f );

		pCryoTankSelect8_12_H2->DefineGroup( GRP_S_F_A11_104_EDO_VC );
		pCryoTankSelect8_12_H2->SetInitialAnimState( 0.5 );
		pCryoTankSelect8_12_H2->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pCryoTankSelect8_12_H2->SetMouseRegion( AID_A11, 0.664558f, 0.317291f, 0.702383f, 0.341291f );


		pCryoTankSelect9_13_O2->DefineGroup( GRP_S_G_A11_104_EDO_VC );
		pCryoTankSelect9_13_O2->SetInitialAnimState( 0.5 );
		pCryoTankSelect9_13_O2->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pCryoTankSelect9_13_O2->SetMouseRegion( AID_A11, 0.781676f, 0.317291f, 0.820024f, 0.341291f );

		pCryoTankSelect9_13_H2->DefineGroup( GRP_S_H_A11_104_EDO_VC );
		pCryoTankSelect9_13_H2->SetInitialAnimState( 0.5 );
		pCryoTankSelect9_13_H2->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pCryoTankSelect9_13_H2->SetMouseRegion( AID_A11, 0.836851f, 0.317291f, 0.883301f, 0.341291f );


		pPalletCryoTank10QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10QtyO2->DefineGroup( GRP_CB_A_A11_104_EDO_VC );
		pPalletCryoTank10QtyO2->SetDirection( pull_dir );
		pPalletCryoTank10QtyO2->SetMouseRegion( AID_A11, 0.555352f, 0.589759f, 0.593564f, 0.613827f );

		pPalletCryoTank10QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10QtyH2->DefineGroup( GRP_CB_B_A11_104_EDO_VC );
		pPalletCryoTank10QtyH2->SetDirection( pull_dir );
		pPalletCryoTank10QtyH2->SetMouseRegion( AID_A11, 0.635219f, 0.589759f, 0.672958f, 0.613827f );


		pPalletCryoTank11QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11QtyO2->DefineGroup( GRP_CB_C_A11_104_EDO_VC );
		pPalletCryoTank11QtyO2->SetDirection( pull_dir );
		pPalletCryoTank11QtyO2->SetMouseRegion( AID_A11, 0.711304f, 0.589759f, 0.751800f, 0.613827f );

		pPalletCryoTank11QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11QtyH2->DefineGroup( GRP_CB_D_A11_104_EDO_VC );
		pPalletCryoTank11QtyH2->SetDirection( pull_dir );
		pPalletCryoTank11QtyH2->SetMouseRegion( AID_A11, 0.792041f, 0.589759f, 0.828739f, 0.613827f );


		pPalletCryoTank12QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12QtyO2->DefineGroup( GRP_CB_E_A11_104_EDO_VC );
		pPalletCryoTank12QtyO2->SetDirection( pull_dir );
		pPalletCryoTank12QtyO2->SetMouseRegion( AID_A11, 0.555352f, 0.645317f, 0.593564f, 0.669422f );

		pPalletCryoTank12QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12QtyH2->DefineGroup( GRP_CB_F_A11_104_EDO_VC );
		pPalletCryoTank12QtyH2->SetDirection( pull_dir );
		pPalletCryoTank12QtyH2->SetMouseRegion( AID_A11, 0.635219f, 0.645317f, 0.672958f, 0.669422f );


		pPalletCryoTank13QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13QtyO2->DefineGroup( GRP_CB_G_A11_104_EDO_VC );
		pPalletCryoTank13QtyO2->SetDirection( pull_dir );
		pPalletCryoTank13QtyO2->SetMouseRegion( AID_A11, 0.711304f, 0.645317f, 0.751800f, 0.669422f );

		pPalletCryoTank13QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13QtyH2->DefineGroup( GRP_CB_H_A11_104_EDO_VC );
		pPalletCryoTank13QtyH2->SetDirection( pull_dir );
		pPalletCryoTank13QtyH2->SetMouseRegion( AID_A11, 0.792041f, 0.645317f, 0.828739f, 0.669422f );


		pMSCommCCUPwr->DefineGroup( GRP_S11_A11_104_EDO_VC );
		pMSCommCCUPwr->SetInitialAnimState( 0.5 );
		pMSCommCCUPwr->SetReference( _V( 0.0, 0.625982, -0.025329 ), switch_rot );
		pMSCommCCUPwr->SetMouseRegion( AID_A11, 0.496442f, 0.236308f, 0.537153f, 0.262506f );

		pDCUtilityPower->DefineGroup( GRP_S13_A11_104_EDO_VC );
		pDCUtilityPower->SetInitialAnimState( 0.5 );
		pDCUtilityPower->SetReference( _V( 0.0, 0.492321, -0.025329 ), switch_rot );
		pDCUtilityPower->SetMouseRegion( AID_A11, 0.570514f, 0.398099f, 0.608857f, 0.420492f );
		return;
	}

	void PanelA11_104_EDO::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A11, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A11,
			_V( 0.56014, 0.83336, -0.0254 ) + ofs, _V( 0.0, 0.83336, -0.0254 ) + ofs,
			_V( 0.56014, 0.0, -0.0254 ) + ofs, _V( 0.0, 0.0, -0.0254 ) + ofs );
		return;
	}

	void PanelA11_104_EDO::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}
}
