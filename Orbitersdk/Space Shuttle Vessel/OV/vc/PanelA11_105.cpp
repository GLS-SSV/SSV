#include "PanelA11_105.h"
#include "CircuitBreaker.h"
#include "StandardSwitch.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a11_105.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA11_105";
	constexpr VECTOR3 OFFSET_PANEL = {0.8001, 1.27607, 12.4756};


	PanelA11_105::PanelA11_105( Atlantis* _sts ) : AtlantisPanel( _sts, "A11" )
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

		Add( pPalletCryoTankHeatersO2Tank10A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 10 A" ) );
		pPalletCryoTankHeatersO2Tank10A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank10A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank10A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank10B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 10 B" ) );
		pPalletCryoTankHeatersO2Tank10B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank10B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank10B->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank10ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 10 RESET/TEST" ) );
		Add( pPalletCryoTankHeatersH2Tank10A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 10 A" ) );
		pPalletCryoTankHeatersH2Tank10A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank10A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank10A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersH2Tank10B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 10 B" ) );
		pPalletCryoTankHeatersH2Tank10B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank10B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank10B->SetLabel( 2, "AUTO" );

		Add( pPalletCryoTankHeatersO2Tank11A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 11 A" ) );
		pPalletCryoTankHeatersO2Tank11A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank11A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank11A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank11B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 11 B" ) );
		pPalletCryoTankHeatersO2Tank11B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank11B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank11B->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank11ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 11 RESET/TEST" ) );
		Add( pPalletCryoTankHeatersH2Tank11A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 11 A" ) );
		pPalletCryoTankHeatersH2Tank11A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank11A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank11A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersH2Tank11B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 11 B" ) );
		pPalletCryoTankHeatersH2Tank11B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank11B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank11B->SetLabel( 2, "AUTO" );

		Add( pPalletCryoTankHeatersO2Tank12A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 12 A" ) );
		pPalletCryoTankHeatersO2Tank12A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank12A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank12A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank12B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 12 B" ) );
		pPalletCryoTankHeatersO2Tank12B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank12B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank12B->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank12ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 12 RESET/TEST" ) );
		Add( pPalletCryoTankHeatersH2Tank12A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 12 A" ) );
		pPalletCryoTankHeatersH2Tank12A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank12A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank12A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersH2Tank12B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 12 B" ) );
		pPalletCryoTankHeatersH2Tank12B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank12B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank12B->SetLabel( 2, "AUTO" );

		Add( pPalletCryoTankHeatersO2Tank13A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 13 A" ) );
		pPalletCryoTankHeatersO2Tank13A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank13A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank13A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank13B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 13 B" ) );
		pPalletCryoTankHeatersO2Tank13B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersO2Tank13B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersO2Tank13B->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersO2Tank13ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 13 RESET/TEST" ) );
		Add( pPalletCryoTankHeatersH2Tank13A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 13 A" ) );
		pPalletCryoTankHeatersH2Tank13A->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank13A->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank13A->SetLabel( 2, "AUTO" );
		Add( pPalletCryoTankHeatersH2Tank13B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 13 B" ) );
		pPalletCryoTankHeatersH2Tank13B->SetLabel( 0, "ON" );
		pPalletCryoTankHeatersH2Tank13B->SetLabel( 1, "OFF" );
		pPalletCryoTankHeatersH2Tank13B->SetLabel( 2, "AUTO" );

		Add( pPalletCryoTank10CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 CNTRL O2" ) );
		Add( pPalletCryoTank10CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 CNTRL H2" ) );
		Add( pPalletCryoTank10QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 QTY O2" ) );
		Add( pPalletCryoTank10QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 QTY H2" ) );
		Add( pPalletCryoTank10O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 O2 HTR SNSR 1" ) );
		Add( pPalletCryoTank10O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 10 O2 HTR SNSR 2" ) );

		Add( pPalletCryoTank11CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 CNTRL O2" ) );
		Add( pPalletCryoTank11CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 CNTRL H2" ) );
		Add( pPalletCryoTank11QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 QTY O2" ) );
		Add( pPalletCryoTank11QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 QTY H2" ) );
		Add( pPalletCryoTank11O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 O2 HTR SNSR 1" ) );
		Add( pPalletCryoTank11O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 11 O2 HTR SNSR 2" ) );

		Add( pPalletCryoTank12CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 CNTRL O2" ) );
		Add( pPalletCryoTank12CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 CNTRL H2" ) );
		Add( pPalletCryoTank12QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 QTY O2" ) );
		Add( pPalletCryoTank12QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 QTY H2" ) );
		Add( pPalletCryoTank12O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 O2 HTR SNSR 1" ) );
		Add( pPalletCryoTank12O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 12 O2 HTR SNSR 2" ) );

		Add( pPalletCryoTank13CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 CNTRL O2" ) );
		Add( pPalletCryoTank13CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 CNTRL H2" ) );
		Add( pPalletCryoTank13QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 QTY O2" ) );
		Add( pPalletCryoTank13QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 QTY H2" ) );
		Add( pPalletCryoTank13O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 O2 HTR SNSR 1" ) );
		Add( pPalletCryoTank13O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 13 O2 HTR SNSR 2" ) );

		Add( pMSCommCCUPwr = new StdSwitch2( _sts, "MS COMM CCU PWR" ) );
		pMSCommCCUPwr->SetLabel( 0, "OFF" );
		pMSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pDCUtilityPower = new StdSwitch2( _sts, "DC UTILITY POWER" ) );
		pDCUtilityPower->SetLabel( 0, "OFF" );
		pDCUtilityPower->SetLabel( 1, "ON" );

		Add( pPalletHeaterC = new StdSwitch2( _sts, "PALLET HEATER C" ) );
		pPalletHeaterC->SetLabel( 0, "OFF" );
		pPalletHeaterC->SetLabel( 1, "AUTO" );
		Add( pPalletHeaterD = new StdSwitch2( _sts, "PALLET HEATER D" ) );
		pPalletHeaterD->SetLabel( 0, "OFF" );
		pPalletHeaterD->SetLabel( 1, "AUTO" );
		return;
	}

	PanelA11_105::~PanelA11_105( void )
	{
		return;
	}

	void PanelA11_105::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A11 );

		pCryoTank4HeatersO2A->DefineGroup( GRP_S1_A11_105_VC );
		pCryoTank4HeatersO2A->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2A->SetMouseRegion( AID_A11, 0.601616f, 0.138093f, 0.647027f, 0.161360f );

		pCryoTank4HeatersO2B->DefineGroup( GRP_S2_A11_105_VC );
		pCryoTank4HeatersO2B->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2B->SetMouseRegion( AID_A11, 0.664558f, 0.138093f, 0.702383f, 0.161360f );

		pCryoTank4HeatersO2ResetTest->DefineGroup( GRP_S3_A11_105_VC );
		pCryoTank4HeatersO2ResetTest->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersO2ResetTest->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersO2ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.138093f, 0.763174f, 0.161360f );
		pCryoTank4HeatersO2ResetTest->SetSpringLoaded( true, 0 );
		pCryoTank4HeatersO2ResetTest->SetSpringLoaded( true, 2 );

		pCryoTank4HeatersH2A->DefineGroup( GRP_S4_A11_105_VC );
		pCryoTank4HeatersH2A->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersH2A->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersH2A->SetMouseRegion( AID_A11, 0.781676f, 0.138093f, 0.820024f, 0.161360f );

		pCryoTank4HeatersH2B->DefineGroup( GRP_S5_A11_105_VC );
		pCryoTank4HeatersH2B->SetInitialAnimState( 0.5 );
		pCryoTank4HeatersH2B->SetReference( _V( 0.0, 0.709524, -0.025329 ), switch_rot );
		pCryoTank4HeatersH2B->SetMouseRegion( AID_A11, 0.836851f, 0.138093f, 0.883301f, 0.161360f );


		pPalletCryoTankHeatersO2Tank10A->DefineGroup( GRP_S16_A11_105_VC );
		pPalletCryoTankHeatersO2Tank10A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank10A->SetReference( _V( 0.0, 0.654019, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank10A->SetMouseRegion( AID_A11, 0.601616f, 0.203640f, 0.647027f, 0.228555f );

		pPalletCryoTankHeatersO2Tank10B->DefineGroup( GRP_S17_A11_105_VC );
		pPalletCryoTankHeatersO2Tank10B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank10B->SetReference( _V( 0.0, 0.654019, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank10B->SetMouseRegion( AID_A11, 0.664558f, 0.203640f, 0.702383f, 0.228555f );

		pPalletCryoTankHeatersO2Tank10ResetTest->DefineGroup( GRP_S18_A11_105_VC );
		pPalletCryoTankHeatersO2Tank10ResetTest->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank10ResetTest->SetReference( _V( 0.0, 0.654019, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank10ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.203640f, 0.763174f, 0.228555f );
		pPalletCryoTankHeatersO2Tank10ResetTest->SetSpringLoaded( true, 0 );
		pPalletCryoTankHeatersO2Tank10ResetTest->SetSpringLoaded( true, 2 );

		pPalletCryoTankHeatersH2Tank10A->DefineGroup( GRP_S19_A11_105_VC );
		pPalletCryoTankHeatersH2Tank10A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank10A->SetReference( _V( 0.0, 0.654019, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank10A->SetMouseRegion( AID_A11, 0.781676f, 0.203640f, 0.820024f, 0.228555f );

		pPalletCryoTankHeatersH2Tank10B->DefineGroup( GRP_S20_A11_105_VC );
		pPalletCryoTankHeatersH2Tank10B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank10B->SetReference( _V( 0.0, 0.654019, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank10B->SetMouseRegion( AID_A11, 0.836851f, 0.203640f, 0.883301f, 0.228555f );


		pPalletCryoTankHeatersO2Tank11A->DefineGroup( GRP_S21_A11_105_VC );
		pPalletCryoTankHeatersO2Tank11A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank11A->SetReference( _V( 0.0, 0.603653, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank11A->SetMouseRegion( AID_A11, 0.601616f, 0.264078f, 0.647027f, 0.288274f );

		pPalletCryoTankHeatersO2Tank11B->DefineGroup( GRP_S22_A11_105_VC );
		pPalletCryoTankHeatersO2Tank11B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank11B->SetReference( _V( 0.0, 0.603653, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank11B->SetMouseRegion( AID_A11, 0.664558f, 0.264078f, 0.702383f, 0.288274f );

		pPalletCryoTankHeatersO2Tank11ResetTest->DefineGroup( GRP_S23_A11_105_VC );
		pPalletCryoTankHeatersO2Tank11ResetTest->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank11ResetTest->SetReference( _V( 0.0, 0.603653, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank11ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.264078f, 0.763174f, 0.288274f );
		pPalletCryoTankHeatersO2Tank11ResetTest->SetSpringLoaded( true, 0 );
		pPalletCryoTankHeatersO2Tank11ResetTest->SetSpringLoaded( true, 2 );

		pPalletCryoTankHeatersH2Tank11A->DefineGroup( GRP_S24_A11_105_VC );
		pPalletCryoTankHeatersH2Tank11A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank11A->SetReference( _V( 0.0, 0.603653, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank11A->SetMouseRegion( AID_A11, 0.781676f, 0.264078f, 0.820024f, 0.288274f );

		pPalletCryoTankHeatersH2Tank11B->DefineGroup( GRP_S25_A11_105_VC );
		pPalletCryoTankHeatersH2Tank11B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank11B->SetReference( _V( 0.0, 0.603653, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank11B->SetMouseRegion( AID_A11, 0.836851f, 0.264078f, 0.883301f, 0.288274f );


		pPalletCryoTankHeatersO2Tank12A->DefineGroup( GRP_S26_A11_105_VC );
		pPalletCryoTankHeatersO2Tank12A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank12A->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank12A->SetMouseRegion( AID_A11, 0.601616f, 0.317092f, 0.647027f, 0.341703f );

		pPalletCryoTankHeatersO2Tank12B->DefineGroup( GRP_S27_A11_105_VC );
		pPalletCryoTankHeatersO2Tank12B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank12B->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank12B->SetMouseRegion( AID_A11, 0.664558f, 0.317092f, 0.702383f, 0.341703f );

		pPalletCryoTankHeatersO2Tank12ResetTest->DefineGroup( GRP_S28_A11_105_VC );
		pPalletCryoTankHeatersO2Tank12ResetTest->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank12ResetTest->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank12ResetTest->SetMouseRegion( AID_A11, 0.718793f, 0.317092f, 0.763174f, 0.341703f );
		pPalletCryoTankHeatersO2Tank12ResetTest->SetSpringLoaded( true, 0 );
		pPalletCryoTankHeatersO2Tank12ResetTest->SetSpringLoaded( true, 2 );

		pPalletCryoTankHeatersH2Tank12A->DefineGroup( GRP_S29_A11_105_VC );
		pPalletCryoTankHeatersH2Tank12A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank12A->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank12A->SetMouseRegion( AID_A11, 0.781676f, 0.317092f, 0.820024f, 0.341703f );

		pPalletCryoTankHeatersH2Tank12B->DefineGroup( GRP_S30_A11_105_VC );
		pPalletCryoTankHeatersH2Tank12B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank12B->SetReference( _V( 0.0, 0.559428, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank12B->SetMouseRegion( AID_A11, 0.836851f, 0.317092f, 0.883301f, 0.341703f );


		pPalletCryoTankHeatersO2Tank13A->DefineGroup( GRP_S31_A11_105_VC );
		pPalletCryoTankHeatersO2Tank13A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank13A->SetReference( _V( 0.0, 0.344022, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank13A->SetMouseRegion( AID_A11, 0.553591f, 0.576069f, 0.593739f, 0.600056f );

		pPalletCryoTankHeatersO2Tank13B->DefineGroup( GRP_S32_A11_105_VC );
		pPalletCryoTankHeatersO2Tank13B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank13B->SetReference( _V( 0.0, 0.344022, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank13B->SetMouseRegion( AID_A11, 0.615155f, 0.576069f, 0.650886f, 0.600056f );

		pPalletCryoTankHeatersO2Tank13ResetTest->DefineGroup( GRP_S33_A11_105_VC );
		pPalletCryoTankHeatersO2Tank13ResetTest->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersO2Tank13ResetTest->SetReference( _V( 0.0, 0.344022, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersO2Tank13ResetTest->SetMouseRegion( AID_A11, 0.672039f, 0.576069f, 0.711144f, 0.600056f );
		pPalletCryoTankHeatersO2Tank13ResetTest->SetSpringLoaded( true, 0 );
		pPalletCryoTankHeatersO2Tank13ResetTest->SetSpringLoaded( true, 2 );

		pPalletCryoTankHeatersH2Tank13A->DefineGroup( GRP_S34_A11_105_VC );
		pPalletCryoTankHeatersH2Tank13A->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank13A->SetReference( _V( 0.0, 0.344022, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank13A->SetMouseRegion( AID_A11, 0.731785f, 0.576069f, 0.770755f, 0.600056f );

		pPalletCryoTankHeatersH2Tank13B->DefineGroup( GRP_S35_A11_105_VC );
		pPalletCryoTankHeatersH2Tank13B->SetInitialAnimState( 0.5 );
		pPalletCryoTankHeatersH2Tank13B->SetReference( _V( 0.0, 0.344022, -0.025329 ), switch_rot );
		pPalletCryoTankHeatersH2Tank13B->SetMouseRegion( AID_A11, 0.790733f, 0.576069f, 0.829444f, 0.600056f );


		pPalletCryoTank10CntrlO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10CntrlO2->DefineGroup( GRP_CB1_A11_105_VC );
		pPalletCryoTank10CntrlO2->SetDirection( pull_dir );
		pPalletCryoTank10CntrlO2->SetMouseRegion( AID_A11, 0.552871f, 0.647948f, 0.595235f, 0.671465f );

		pPalletCryoTank10CntrlH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10CntrlH2->DefineGroup( GRP_CB2_A11_105_VC );
		pPalletCryoTank10CntrlH2->SetDirection( pull_dir );
		pPalletCryoTank10CntrlH2->SetMouseRegion( AID_A11, 0.603419f, 0.647948f, 0.642489f, 0.671465f );

		pPalletCryoTank10QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10QtyO2->DefineGroup( GRP_CB3_A11_105_VC );
		pPalletCryoTank10QtyO2->SetDirection( pull_dir );
		pPalletCryoTank10QtyO2->SetMouseRegion( AID_A11, 0.648689f, 0.647948f, 0.690063f, 0.671465f );

		pPalletCryoTank10QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10QtyH2->DefineGroup( GRP_CB4_A11_105_VC );
		pPalletCryoTank10QtyH2->SetDirection( pull_dir );
		pPalletCryoTank10QtyH2->SetMouseRegion( AID_A11, 0.697770f, 0.647948f, 0.735827f, 0.671465f );

		pPalletCryoTank10O2HtrSnsr1->SetInitialAnimState( 1.0f );
		pPalletCryoTank10O2HtrSnsr1->DefineGroup( GRP_CB5_A11_105_VC );
		pPalletCryoTank10O2HtrSnsr1->SetDirection( pull_dir );
		pPalletCryoTank10O2HtrSnsr1->SetMouseRegion( AID_A11, 0.742382f, 0.647948f, 0.783565f, 0.671465f );

		pPalletCryoTank10O2HtrSnsr2->SetInitialAnimState( 1.0f );
		pPalletCryoTank10O2HtrSnsr2->DefineGroup( GRP_CB6_A11_105_VC );
		pPalletCryoTank10O2HtrSnsr2->SetDirection( pull_dir );
		pPalletCryoTank10O2HtrSnsr2->SetMouseRegion( AID_A11, 0.790614f, 0.647948f, 0.831799f, 0.671465f );


		pPalletCryoTank11CntrlO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11CntrlO2->DefineGroup( GRP_CB7_A11_105_VC );
		pPalletCryoTank11CntrlO2->SetDirection( pull_dir );
		pPalletCryoTank11CntrlO2->SetMouseRegion( AID_A11, 0.552871f, 0.700739f, 0.595235f, 0.724063f );

		pPalletCryoTank11CntrlH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11CntrlH2->DefineGroup( GRP_CB8_A11_105_VC );
		pPalletCryoTank11CntrlH2->SetDirection( pull_dir );
		pPalletCryoTank11CntrlH2->SetMouseRegion( AID_A11, 0.603419f, 0.700739f, 0.642489f, 0.724063f );

		pPalletCryoTank11QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11QtyO2->DefineGroup( GRP_CB9_A11_105_VC );
		pPalletCryoTank11QtyO2->SetDirection( pull_dir );
		pPalletCryoTank11QtyO2->SetMouseRegion( AID_A11, 0.648689f, 0.700739f, 0.690063f, 0.724063f );

		pPalletCryoTank11QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11QtyH2->DefineGroup( GRP_CB10_A11_105_VC );
		pPalletCryoTank11QtyH2->SetDirection( pull_dir );
		pPalletCryoTank11QtyH2->SetMouseRegion( AID_A11, 0.697770f, 0.700739f, 0.735827f, 0.724063f );

		pPalletCryoTank11O2HtrSnsr1->SetInitialAnimState( 1.0f );
		pPalletCryoTank11O2HtrSnsr1->DefineGroup( GRP_CB11_A11_105_VC );
		pPalletCryoTank11O2HtrSnsr1->SetDirection( pull_dir );
		pPalletCryoTank11O2HtrSnsr1->SetMouseRegion( AID_A11, 0.742382f, 0.700739f, 0.783565f, 0.724063f );

		pPalletCryoTank11O2HtrSnsr2->SetInitialAnimState( 1.0f );
		pPalletCryoTank11O2HtrSnsr2->DefineGroup( GRP_CB12_A11_105_VC );
		pPalletCryoTank11O2HtrSnsr2->SetDirection( pull_dir );
		pPalletCryoTank11O2HtrSnsr2->SetMouseRegion( AID_A11, 0.790614f, 0.700739f, 0.831799f, 0.724063f );


		pPalletCryoTank12CntrlO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12CntrlO2->DefineGroup( GRP_CB13_A11_105_VC );
		pPalletCryoTank12CntrlO2->SetDirection( pull_dir );
		pPalletCryoTank12CntrlO2->SetMouseRegion( AID_A11, 0.552871f, 0.760069f, 0.595235f, 0.784216f );

		pPalletCryoTank12CntrlH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12CntrlH2->DefineGroup( GRP_CB14_A11_105_VC );
		pPalletCryoTank12CntrlH2->SetDirection( pull_dir );
		pPalletCryoTank12CntrlH2->SetMouseRegion( AID_A11, 0.603419f, 0.760069f, 0.642489f, 0.784216f );

		pPalletCryoTank12QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12QtyO2->DefineGroup( GRP_CB15_A11_105_VC );
		pPalletCryoTank12QtyO2->SetDirection( pull_dir );
		pPalletCryoTank12QtyO2->SetMouseRegion( AID_A11, 0.648689f, 0.760069f, 0.690063f, 0.784216f );

		pPalletCryoTank12QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12QtyH2->DefineGroup( GRP_CB16_A11_105_VC );
		pPalletCryoTank12QtyH2->SetDirection( pull_dir );
		pPalletCryoTank12QtyH2->SetMouseRegion( AID_A11, 0.697770f, 0.760069f, 0.735827f, 0.784216f );

		pPalletCryoTank12O2HtrSnsr1->SetInitialAnimState( 1.0f );
		pPalletCryoTank12O2HtrSnsr1->DefineGroup( GRP_CB17_A11_105_VC );
		pPalletCryoTank12O2HtrSnsr1->SetDirection( pull_dir );
		pPalletCryoTank12O2HtrSnsr1->SetMouseRegion( AID_A11, 0.742382f, 0.760069f, 0.783565f, 0.784216f );

		pPalletCryoTank12O2HtrSnsr2->SetInitialAnimState( 1.0f );
		pPalletCryoTank12O2HtrSnsr2->DefineGroup( GRP_CB18_A11_105_VC );
		pPalletCryoTank12O2HtrSnsr2->SetDirection( pull_dir );
		pPalletCryoTank12O2HtrSnsr2->SetMouseRegion( AID_A11, 0.790614f, 0.760069f, 0.831799f, 0.784216f );


		pPalletCryoTank13CntrlO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13CntrlO2->DefineGroup( GRP_CB19_A11_105_VC );
		pPalletCryoTank13CntrlO2->SetDirection( pull_dir );
		pPalletCryoTank13CntrlO2->SetMouseRegion( AID_A11, 0.552871f, 0.812727f, 0.595235f, 0.836517f );

		pPalletCryoTank13CntrlH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13CntrlH2->DefineGroup( GRP_CB20_A11_105_VC );
		pPalletCryoTank13CntrlH2->SetDirection( pull_dir );
		pPalletCryoTank13CntrlH2->SetMouseRegion( AID_A11, 0.603419f, 0.812727f, 0.642489f, 0.836517f );

		pPalletCryoTank13QtyO2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13QtyO2->DefineGroup( GRP_CB21_A11_105_VC );
		pPalletCryoTank13QtyO2->SetDirection( pull_dir );
		pPalletCryoTank13QtyO2->SetMouseRegion( AID_A11, 0.648689f, 0.812727f, 0.690063f, 0.836517f );

		pPalletCryoTank13QtyH2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13QtyH2->DefineGroup( GRP_CB22_A11_105_VC );
		pPalletCryoTank13QtyH2->SetDirection( pull_dir );
		pPalletCryoTank13QtyH2->SetMouseRegion( AID_A11, 0.697770f, 0.812727f, 0.735827f, 0.836517f );

		pPalletCryoTank13O2HtrSnsr1->SetInitialAnimState( 1.0f );
		pPalletCryoTank13O2HtrSnsr1->DefineGroup( GRP_CB23_A11_105_VC );
		pPalletCryoTank13O2HtrSnsr1->SetDirection( pull_dir );
		pPalletCryoTank13O2HtrSnsr1->SetMouseRegion( AID_A11, 0.742382f, 0.812727f, 0.783565f, 0.836517f );

		pPalletCryoTank13O2HtrSnsr2->SetInitialAnimState( 1.0f );
		pPalletCryoTank13O2HtrSnsr2->DefineGroup( GRP_CB24_A11_105_VC );
		pPalletCryoTank13O2HtrSnsr2->SetDirection( pull_dir );
		pPalletCryoTank13O2HtrSnsr2->SetMouseRegion( AID_A11, 0.790614f, 0.812727f, 0.831799f, 0.836517f );


		pMSCommCCUPwr->DefineGroup( GRP_S11_A11_105_VC );
		pMSCommCCUPwr->SetInitialAnimState( 0.5 );
		pMSCommCCUPwr->SetReference( _V( 0.0, 0.625982, -0.025329 ), switch_rot );
		pMSCommCCUPwr->SetMouseRegion( AID_A11, 0.496442f, 0.236308f, 0.537153f, 0.262506f );

		pDCUtilityPower->DefineGroup( GRP_S13_A11_105_VC );
		pDCUtilityPower->SetInitialAnimState( 0.5 );
		pDCUtilityPower->SetReference( _V( 0.0, 0.492321, -0.025329 ), switch_rot );
		pDCUtilityPower->SetMouseRegion( AID_A11, 0.570514f, 0.398099f, 0.608857f, 0.420492f );

		pPalletHeaterC->DefineGroup( GRP_S14_A11_105_VC );
		pPalletHeaterC->SetInitialAnimState( 0.5 );
		pPalletHeaterC->SetReference( _V( 0.0, 0.269425, -0.025329 ), switch_rot );
		pPalletHeaterC->SetMouseRegion( AID_A11, 0.371307f, 0.665038f, 0.408873f, 0.688305f );

		pPalletHeaterD->DefineGroup( GRP_S15_A11_105_VC );
		pPalletHeaterD->SetInitialAnimState( 0.5 );
		pPalletHeaterD->SetReference( _V( 0.0, 0.269425, -0.025329 ), switch_rot );
		pPalletHeaterD->SetMouseRegion( AID_A11, 0.449338f, 0.665038f, 0.487704f, 0.688305f );
		return;
	}

	void PanelA11_105::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A11, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A11,
			_V( 0.56014, 0.83336, -0.0254 ) + ofs, _V( 0.0, 0.83336, -0.0254 ) + ofs,
			_V( 0.56014, 0.0, -0.0254 ) + ofs, _V( 0.0, 0.0, -0.0254 ) + ofs );
		return;
	}

	void PanelA11_105::Realize( void )
	{
		AtlantisPanel::Realize();

		// TODO
		return;
	}
}
