#include "PanelA15_EDO.h"
#include "CircuitBreaker.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a15_edo.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA15_EDO";
	constexpr VECTOR3 OFFSET_PANEL = {-1.64295, 1.27607, 12.4756};


	PanelA15_EDO::PanelA15_EDO( Atlantis* _sts, const std::string &orbiter ) : AtlantisPanel( _sts, "A15" ),
		hTexture(NULL), ov102(false), ov103(false), ov104(false), ov105(false)
	{
		if (orbiter == "Columbia") ov102 = true;
		else if (orbiter == "Discovery") ov103 = true;
		else if (orbiter == "Atlantis") ov104 = true;
		else ov105 = true;

		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		if (ov103 || ov104 || ov105)
		{
			Add( pCryoTank5HeatersO2A = new StdSwitch3( _sts, "CRYO TANK 5 HEATERS O2 A" ) );
			pCryoTank5HeatersO2A->SetLabel( 0, "ON" );
			pCryoTank5HeatersO2A->SetLabel( 1, "OFF" );
			pCryoTank5HeatersO2A->SetLabel( 2, "AUTO" );
			Add( pCryoTank5HeatersO2B = new StdSwitch3( _sts, "CRYO TANK 5 HEATERS O2 B" ) );
			pCryoTank5HeatersO2B->SetLabel( 0, "ON" );
			pCryoTank5HeatersO2B->SetLabel( 1, "OFF" );
			pCryoTank5HeatersO2B->SetLabel( 2, "AUTO" );
			Add( pCryoTank5HeatersO2ResetTest = new StdSwitch3( _sts, "CRYO TANK 5 HEATERS O2 RESET TEST" ) );
			Add( pCryoTank5HeatersH2A = new StdSwitch3( _sts, "CRYO TANK 5 HEATERS H2 A" ) );
			pCryoTank5HeatersH2A->SetLabel( 0, "ON" );
			pCryoTank5HeatersH2A->SetLabel( 1, "OFF" );
			pCryoTank5HeatersH2A->SetLabel( 2, "AUTO" );
			Add( pCryoTank5HeatersH2B = new StdSwitch3( _sts, "CRYO TANK 5 HEATERS H2 B" ) );
			pCryoTank5HeatersH2B->SetLabel( 0, "ON" );
			pCryoTank5HeatersH2B->SetLabel( 1, "OFF" );
			pCryoTank5HeatersH2B->SetLabel( 2, "AUTO" );
		}

		if (ov102 || ov105)
		{
			Add( pPalletPowerPPCA1 = new StandardTalkback2( _sts, "PALLET POWER PPCA-1/3" ) );
			Add( pPalletPowerPPCA2 = new StandardTalkback2( _sts, "PALLET POWER PPCA-2/4" ) );

			Add( pPalletPowerMNA = new StdSwitch3( _sts, "PALLET POWER MN A" ) );
			Add( pPalletPowerMNB = new StdSwitch3( _sts, "PALLET POWER MN B" ) );

			Add( pPPCAContPwr1ESS1BC = new CircuitBreaker( _sts, "PPCA CONT PWR 1/3 ESS 1BC" ) );
			Add( pPPCAContPwr2ESS2CA = new CircuitBreaker( _sts, "PPCA CONT PWR 2/4 ESS 2CA" ) );

			Add( pPalletHeatersA = new StdSwitch2( _sts, "PALLET HEATERS A" ) );
			pPalletHeatersA->SetLabel( 0, "OFF" );
			pPalletHeatersA->SetLabel( 1, "AUTO" );
			Add( pPalletHeatersB = new StdSwitch2( _sts, "PALLET HEATERS B" ) );
			pPalletHeatersB->SetLabel( 0, "OFF" );
			pPalletHeatersB->SetLabel( 1, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank6A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 6 A" ) );
			pPalletCryoTankHeatersO2Tank6A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank6A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank6A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank6B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 6 B" ) );
			pPalletCryoTankHeatersO2Tank6B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank6B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank6B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank6ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 6 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank6A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 6 A" ) );
			pPalletCryoTankHeatersH2Tank6A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank6A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank6A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank6B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 6 B" ) );
			pPalletCryoTankHeatersH2Tank6B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank6B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank6B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank7A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 7 A" ) );
			pPalletCryoTankHeatersO2Tank7A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank7A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank7A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank7B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 7 B" ) );
			pPalletCryoTankHeatersO2Tank7B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank7B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank7B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank7ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 7 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank7A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 7 A" ) );
			pPalletCryoTankHeatersH2Tank7A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank7A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank7A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank7B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 7 B" ) );
			pPalletCryoTankHeatersH2Tank7B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank7B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank7B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank8A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 8 A" ) );
			pPalletCryoTankHeatersO2Tank8A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank8A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank8A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank8B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 8 B" ) );
			pPalletCryoTankHeatersO2Tank8B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank8B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank8B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank8ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 8 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank8A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 8 A" ) );
			pPalletCryoTankHeatersH2Tank8A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank8A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank8A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank8B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 8 B" ) );
			pPalletCryoTankHeatersH2Tank8B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank8B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank8B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank9A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 9 A" ) );
			pPalletCryoTankHeatersO2Tank9A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank9A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank9A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank9B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 9 B" ) );
			pPalletCryoTankHeatersO2Tank9B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank9B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank9B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank9ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 9 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank9A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 9 A" ) );
			pPalletCryoTankHeatersH2Tank9A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank9A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank9A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank9B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 9 B" ) );
			pPalletCryoTankHeatersH2Tank9B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank9B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank9B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTank6CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6 CNTRL O2" ) );
			Add( pPalletCryoTank6CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6 CNTRL H2" ) );
			Add( pPalletCryoTank6QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6 QTY O2" ) );
			Add( pPalletCryoTank6QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6 QTY H2" ) );
			Add( pPalletCryoTank6O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank6O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6 O2 HTR SNSR 2" ) );

			Add( pPalletCryoTank7CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7 CNTRL O2" ) );
			Add( pPalletCryoTank7CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7 CNTRL H2" ) );
			Add( pPalletCryoTank7QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7 QTY O2" ) );
			Add( pPalletCryoTank7QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7 QTY H2" ) );
			Add( pPalletCryoTank7O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank7O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7 O2 HTR SNSR 2" ) );

			Add( pPalletCryoTank8CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8 CNTRL O2" ) );
			Add( pPalletCryoTank8CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8 CNTRL H2" ) );
			Add( pPalletCryoTank8QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8 QTY O2" ) );
			Add( pPalletCryoTank8QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8 QTY H2" ) );
			Add( pPalletCryoTank8O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank8O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8 O2 HTR SNSR 2" ) );

			Add( pPalletCryoTank9CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9 CNTRL O2" ) );
			Add( pPalletCryoTank9CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9 CNTRL H2" ) );
			Add( pPalletCryoTank9QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9 QTY O2" ) );
			Add( pPalletCryoTank9QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9 QTY H2" ) );
			Add( pPalletCryoTank9O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank9O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9 O2 HTR SNSR 2" ) );
		}
		else if (ov104)
		{
			Add( pPalletPowerPPCA1 = new StandardTalkback2( _sts, "PALLET POWER PPCA-1" ) );
			Add( pPalletPowerPPCA2 = new StandardTalkback2( _sts, "PALLET POWER PPCA-2" ) );

			Add( pPalletPowerMNA = new StdSwitch3( _sts, "PALLET POWER MN A" ) );
			Add( pPalletPowerMNB = new StdSwitch3( _sts, "PALLET POWER MN B" ) );

			Add( pPPCAContPwr1ESS1BC = new CircuitBreaker( _sts, "PPCA CONT PWR 1 ESS 1BC" ) );
			Add( pPPCAContPwr2ESS2CA = new CircuitBreaker( _sts, "PPCA CONT PWR 2 ESS 2CA" ) );

			Add( pPalletHeatersA = new StdSwitch2( _sts, "PALLET HEATERS A" ) );
			pPalletHeatersA->SetLabel( 0, "OFF" );
			pPalletHeatersA->SetLabel( 1, "AUTO" );
			Add( pPalletHeatersB = new StdSwitch2( _sts, "PALLET HEATERS B" ) );
			pPalletHeatersB->SetLabel( 0, "OFF" );
			pPalletHeatersB->SetLabel( 1, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank6A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 6/10 A" ) );
			pPalletCryoTankHeatersO2Tank6A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank6A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank6A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank6B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 6/10 B" ) );
			pPalletCryoTankHeatersO2Tank6B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank6B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank6B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank6ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 6/10 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank6A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 6/10 A" ) );
			pPalletCryoTankHeatersH2Tank6A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank6A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank6A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank6B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 6/10 B" ) );
			pPalletCryoTankHeatersH2Tank6B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank6B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank6B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank7A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 7/11 A" ) );
			pPalletCryoTankHeatersO2Tank7A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank7A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank7A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank7B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 7/11 B" ) );
			pPalletCryoTankHeatersO2Tank7B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank7B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank7B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank7ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 7/11 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank7A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 7/11 A" ) );
			pPalletCryoTankHeatersH2Tank7A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank7A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank7A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank7B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 7/11 B" ) );
			pPalletCryoTankHeatersH2Tank7B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank7B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank7B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank8A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 8/12 A" ) );
			pPalletCryoTankHeatersO2Tank8A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank8A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank8A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank8B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 8/12 B" ) );
			pPalletCryoTankHeatersO2Tank8B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank8B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank8B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank8ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 8/12 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank8A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 8/12 A" ) );
			pPalletCryoTankHeatersH2Tank8A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank8A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank8A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank8B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 8/12 B" ) );
			pPalletCryoTankHeatersH2Tank8B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank8B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank8B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTankHeatersO2Tank9A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 9/13 A" ) );
			pPalletCryoTankHeatersO2Tank9A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank9A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank9A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank9B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 9/13 B" ) );
			pPalletCryoTankHeatersO2Tank9B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersO2Tank9B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersO2Tank9B->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersO2Tank9ResetTest = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS O2 TANK 9/13 RESET/TEST" ) );
			Add( pPalletCryoTankHeatersH2Tank9A = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 9/13 A" ) );
			pPalletCryoTankHeatersH2Tank9A->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank9A->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank9A->SetLabel( 2, "AUTO" );
			Add( pPalletCryoTankHeatersH2Tank9B = new StdSwitch3( _sts, "PALLET CRYO TANK HEATERS H2 TANK 9/13 B" ) );
			pPalletCryoTankHeatersH2Tank9B->SetLabel( 0, "ON" );
			pPalletCryoTankHeatersH2Tank9B->SetLabel( 1, "OFF" );
			pPalletCryoTankHeatersH2Tank9B->SetLabel( 2, "AUTO" );

			Add( pPalletCryoTank6CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6/10 CNTRL O2" ) );
			Add( pPalletCryoTank6CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6/10 CNTRL H2" ) );
			Add( pPalletCryoTank6QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6/10 QTY O2" ) );
			Add( pPalletCryoTank6QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6/10 QTY H2" ) );
			Add( pPalletCryoTank6O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6/10 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank6O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 6/10 O2 HTR SNSR 2" ) );

			Add( pPalletCryoTank7CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7/11 CNTRL O2" ) );
			Add( pPalletCryoTank7CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7/11 CNTRL H2" ) );
			Add( pPalletCryoTank7QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7/11 QTY O2" ) );
			Add( pPalletCryoTank7QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7/11 QTY H2" ) );
			Add( pPalletCryoTank7O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7/11 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank7O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 7/11 O2 HTR SNSR 2" ) );

			Add( pPalletCryoTank8CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8/12 CNTRL O2" ) );
			Add( pPalletCryoTank8CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8/12 CNTRL H2" ) );
			Add( pPalletCryoTank8QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8/12 QTY O2" ) );
			Add( pPalletCryoTank8QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8/12 QTY H2" ) );
			Add( pPalletCryoTank8O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8/12 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank8O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 8/12 O2 HTR SNSR 2" ) );

			Add( pPalletCryoTank9CntrlO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9/13 CNTRL O2" ) );
			Add( pPalletCryoTank9CntrlH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9/13 CNTRL H2" ) );
			Add( pPalletCryoTank9QtyO2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9/13 QTY O2" ) );
			Add( pPalletCryoTank9QtyH2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9/13 QTY H2" ) );
			Add( pPalletCryoTank9O2HtrSnsr1 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9/13 O2 HTR SNSR 1" ) );
			Add( pPalletCryoTank9O2HtrSnsr2 = new CircuitBreaker( _sts, "PALLET CRYO TANK 9/13 O2 HTR SNSR 2" ) );
		}
		
		Add( pPSCommCCUPwr = new StdSwitch2( _sts, "PS COMM CCU PWR" ) );
		pPSCommCCUPwr->SetLabel( 0, "OFF" );
		pPSCommCCUPwr->SetLabel( 1, "ON" );
		Add( pDCUtilityPower = new StdSwitch2( _sts, "DC UTILITY POWER" ) );
		pDCUtilityPower->SetLabel( 0, "OFF" );
		pDCUtilityPower->SetLabel( 1, "ON" );
		Add( pACUtilityPower = new StdSwitch2( _sts, "AC UTILITY POWER" ) );
		pACUtilityPower->SetLabel( 0, "OFF" );
		pACUtilityPower->SetLabel( 1, "ON" );
		return;
	}

	PanelA15_EDO::~PanelA15_EDO( void )
	{
		if (hTexture) oapiReleaseTexture( hTexture );
		return;
	}

	void PanelA15_EDO::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.0, 1.0 );

		AddAIDToMouseEventList( AID_A15 );

		if (ov103 || ov104 || ov105)
		{
			pCryoTank5HeatersO2A->DefineGroup( GRP_S4_A15_EDO_VC );
			pCryoTank5HeatersO2A->SetInitialAnimState( 0.5 );
			pCryoTank5HeatersO2A->SetReference( _V( 0.0, 0.710594, -0.025329 ), switch_rot );
			pCryoTank5HeatersO2A->SetMouseRegion( AID_A15, 0.103134f, 0.134506f, 0.144907f, 0.160996f );

			pCryoTank5HeatersO2B->DefineGroup( GRP_S5_A15_EDO_VC );
			pCryoTank5HeatersO2B->SetInitialAnimState( 0.5 );
			pCryoTank5HeatersO2B->SetReference( _V( 0.0, 0.710594, -0.025329 ), switch_rot );
			pCryoTank5HeatersO2B->SetMouseRegion( AID_A15, 0.169050f, 0.134506f, 0.202941f, 0.160996f );

			pCryoTank5HeatersO2ResetTest->DefineGroup( GRP_S6_A15_EDO_VC );
			pCryoTank5HeatersO2ResetTest->SetInitialAnimState( 0.5 );
			pCryoTank5HeatersO2ResetTest->SetReference( _V( 0.0, 0.710594, -0.025329 ), switch_rot );
			pCryoTank5HeatersO2ResetTest->SetMouseRegion( AID_A15, 0.225283f, 0.134506f, 0.270236f, 0.160996f );
			pCryoTank5HeatersO2ResetTest->SetSpringLoaded( true, 0 );
			pCryoTank5HeatersO2ResetTest->SetSpringLoaded( true, 2 );

			pCryoTank5HeatersH2A->DefineGroup( GRP_S7_A15_EDO_VC );
			pCryoTank5HeatersH2A->SetInitialAnimState( 0.5 );
			pCryoTank5HeatersH2A->SetReference( _V( 0.0, 0.710594, -0.025329 ), switch_rot );
			pCryoTank5HeatersH2A->SetMouseRegion( AID_A15, 0.291263f, 0.134506f, 0.329176f, 0.160996f );

			pCryoTank5HeatersH2B->DefineGroup( GRP_S8_A15_EDO_VC );
			pCryoTank5HeatersH2B->SetInitialAnimState( 0.5 );
			pCryoTank5HeatersH2B->SetReference( _V( 0.0, 0.710594, -0.025329 ), switch_rot );
			pCryoTank5HeatersH2B->SetMouseRegion( AID_A15, 0.350556f, 0.134506f, 0.392626f, 0.160996f );
		}

		if (ov102 || ov104 || ov105)
		{
			pPalletPowerPPCA1->DefineMeshGroups( GetVCMeshIndex(), GRP_DS9_U_A15_EDO_VC, GRP_DS9_L_A15_EDO_VC );
			pPalletPowerPPCA1->SetInactiveSegment( TB_OFF );
			pPalletPowerPPCA2->DefineMeshGroups( GetVCMeshIndex(), GRP_DS10_U_A15_EDO_VC, GRP_DS10_L_A15_EDO_VC );
			pPalletPowerPPCA2->SetInactiveSegment( TB_OFF );

			pPalletPowerMNA->DefineGroup( GRP_S9_A15_EDO_VC );
			pPalletPowerMNA->SetInitialAnimState( 0.5 );
			pPalletPowerMNA->SetReference( _V( 0.0, 0.609506, -0.025329 ), switch_rot );
			pPalletPowerMNA->SetMouseRegion( AID_A15, 0.100548f, 0.256056f, 0.147826f, 0.281271f );
			pPalletPowerMNA->SetSpringLoaded( true, 0 );
			pPalletPowerMNA->SetSpringLoaded( true, 2 );

			pPalletPowerMNB->DefineGroup( GRP_S10_A15_EDO_VC );
			pPalletPowerMNB->SetInitialAnimState( 0.5 );
			pPalletPowerMNB->SetReference( _V( 0.0, 0.609506, -0.025329 ), switch_rot );
			pPalletPowerMNB->SetMouseRegion( AID_A15, 0.169920f, 0.256056f, 0.206065f, 0.281271f );
			pPalletPowerMNB->SetSpringLoaded( true, 0 );
			pPalletPowerMNB->SetSpringLoaded( true, 2 );

			pPPCAContPwr1ESS1BC->SetInitialAnimState( 1.0f );
			pPPCAContPwr1ESS1BC->DefineGroup( ov104 ? GRP_CB1_104_A15_EDO_VC : GRP_CB1_A15_EDO_VC );
			pPPCAContPwr1ESS1BC->SetDirection( pull_dir );
			pPPCAContPwr1ESS1BC->SetMouseRegion( AID_A15, 0.310297f, 0.200581f, 0.344802f, 0.227326f );

			pPPCAContPwr2ESS2CA->SetInitialAnimState( 1.0f );
			pPPCAContPwr2ESS2CA->DefineGroup( ov104 ? GRP_CB2_104_A15_EDO_VC : GRP_CB2_A15_EDO_VC );
			pPPCAContPwr2ESS2CA->SetDirection( pull_dir );
			pPPCAContPwr2ESS2CA->SetMouseRegion( AID_A15, 0.355958f, 0.200581f, 0.390130f, 0.227326f );

			pPalletHeatersA->DefineGroup( GRP_S11_A15_EDO_VC );
			pPalletHeatersA->SetInitialAnimState( 0.5 );
			pPalletHeatersA->SetReference( _V( 0.0, 0.609506, -0.025329 ), switch_rot );
			pPalletHeatersA->SetMouseRegion( AID_A15, 0.265429f, 0.256056f, 0.298860f, 0.281271f );

			pPalletHeatersB->DefineGroup( GRP_S12_A15_EDO_VC );
			pPalletHeatersB->SetInitialAnimState( 0.5 );
			pPalletHeatersB->SetReference( _V( 0.0, 0.609506, -0.025329 ), switch_rot );
			pPalletHeatersB->SetMouseRegion( AID_A15, 0.322139f, 0.256056f, 0.366044f, 0.281271f );

			pPalletCryoTankHeatersO2Tank6A->DefineGroup( GRP_S13_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank6A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank6A->SetReference( _V( 0.0, 0.53101, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank6A->SetMouseRegion( AID_A15, 0.102103f, 0.349930f, 0.144091f, 0.377107f );

			pPalletCryoTankHeatersO2Tank6B->DefineGroup( GRP_S14_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank6B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank6B->SetReference( _V( 0.0, 0.53101, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank6B->SetMouseRegion( AID_A15, 0.166568f, 0.349930f, 0.202572f, 0.377107f );

			pPalletCryoTankHeatersO2Tank6ResetTest->DefineGroup( GRP_S15_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank6ResetTest->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank6ResetTest->SetReference( _V( 0.0, 0.53101, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank6ResetTest->SetMouseRegion( AID_A15, 0.227540f, 0.349930f, 0.267543f, 0.377107f );
			pPalletCryoTankHeatersO2Tank6ResetTest->SetSpringLoaded( true, 0 );
			pPalletCryoTankHeatersO2Tank6ResetTest->SetSpringLoaded( true, 2 );

			pPalletCryoTankHeatersH2Tank6A->DefineGroup( GRP_S16_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank6A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank6A->SetReference( _V( 0.0, 0.53101, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank6A->SetMouseRegion( AID_A15, 0.291023f, 0.349930f, 0.328039f, 0.377107f );

			pPalletCryoTankHeatersH2Tank6B->DefineGroup( GRP_S17_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank6B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank6B->SetReference( _V( 0.0, 0.53101, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank6B->SetMouseRegion( AID_A15, 0.351077f, 0.349930f, 0.392287f, 0.377107f );


			pPalletCryoTankHeatersO2Tank7A->DefineGroup( GRP_S18_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank7A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank7A->SetReference( _V( 0.0, 0.47896, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank7A->SetMouseRegion( AID_A15, 0.102103f, 0.413000f, 0.144091f, 0.439182f );

			pPalletCryoTankHeatersO2Tank7B->DefineGroup( GRP_S19_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank7B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank7B->SetReference( _V( 0.0, 0.47896, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank7B->SetMouseRegion( AID_A15, 0.166568f, 0.413000f, 0.202572f, 0.439182f );

			pPalletCryoTankHeatersO2Tank7ResetTest->DefineGroup( GRP_S20_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank7ResetTest->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank7ResetTest->SetReference( _V( 0.0, 0.47896, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank7ResetTest->SetMouseRegion( AID_A15, 0.227540f, 0.413000f, 0.267543f, 0.439182f );
			pPalletCryoTankHeatersO2Tank7ResetTest->SetSpringLoaded( true, 0 );
			pPalletCryoTankHeatersO2Tank7ResetTest->SetSpringLoaded( true, 2 );

			pPalletCryoTankHeatersH2Tank7A->DefineGroup( GRP_S21_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank7A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank7A->SetReference( _V( 0.0, 0.47896, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank7A->SetMouseRegion( AID_A15, 0.291023f, 0.413000f, 0.328039f, 0.439182f );

			pPalletCryoTankHeatersH2Tank7B->DefineGroup( GRP_S22_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank7B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank7B->SetReference( _V( 0.0, 0.47896, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank7B->SetMouseRegion( AID_A15, 0.351077f, 0.413000f, 0.392287f, 0.439182f );


			pPalletCryoTankHeatersO2Tank8A->DefineGroup( GRP_S23_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank8A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank8A->SetReference( _V( 0.0, 0.426469, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank8A->SetMouseRegion( AID_A15, 0.102103f, 0.475658f, 0.144091f, 0.501898f );

			pPalletCryoTankHeatersO2Tank8B->DefineGroup( GRP_S24_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank8B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank8B->SetReference( _V( 0.0, 0.426469, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank8B->SetMouseRegion( AID_A15, 0.166568f, 0.475658f, 0.202572f, 0.501898f );

			pPalletCryoTankHeatersO2Tank8ResetTest->DefineGroup( GRP_S25_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank8ResetTest->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank8ResetTest->SetReference( _V( 0.0, 0.426469, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank8ResetTest->SetMouseRegion( AID_A15, 0.227540f, 0.475658f, 0.267543f, 0.501898f );
			pPalletCryoTankHeatersO2Tank8ResetTest->SetSpringLoaded( true, 0 );
			pPalletCryoTankHeatersO2Tank8ResetTest->SetSpringLoaded( true, 2 );

			pPalletCryoTankHeatersH2Tank8A->DefineGroup( GRP_S26_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank8A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank8A->SetReference( _V( 0.0, 0.426469, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank8A->SetMouseRegion( AID_A15, 0.291023f, 0.475658f, 0.328039f, 0.501898f );

			pPalletCryoTankHeatersH2Tank8B->DefineGroup( GRP_S27_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank8B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank8B->SetReference( _V( 0.0, 0.426469, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank8B->SetMouseRegion( AID_A15, 0.351077f, 0.475658f, 0.392287f, 0.501898f );


			pPalletCryoTankHeatersO2Tank9A->DefineGroup( GRP_S28_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank9A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank9A->SetReference( _V( 0.0, 0.374435, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank9A->SetMouseRegion( AID_A15, 0.102103f, 0.537514f, 0.144091f, 0.564339f );

			pPalletCryoTankHeatersO2Tank9B->DefineGroup( GRP_S29_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank9B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank9B->SetReference( _V( 0.0, 0.374435, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank9B->SetMouseRegion( AID_A15, 0.166568f, 0.537514f, 0.202572f, 0.564339f );

			pPalletCryoTankHeatersO2Tank9ResetTest->DefineGroup( GRP_S30_A15_EDO_VC );
			pPalletCryoTankHeatersO2Tank9ResetTest->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersO2Tank9ResetTest->SetReference( _V( 0.0, 0.374435, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersO2Tank9ResetTest->SetMouseRegion( AID_A15, 0.227540f, 0.537514f, 0.267543f, 0.564339f );
			pPalletCryoTankHeatersO2Tank9ResetTest->SetSpringLoaded( true, 0 );
			pPalletCryoTankHeatersO2Tank9ResetTest->SetSpringLoaded( true, 2 );

			pPalletCryoTankHeatersH2Tank9A->DefineGroup( GRP_S31_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank9A->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank9A->SetReference( _V( 0.0, 0.374435, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank9A->SetMouseRegion( AID_A15, 0.291023f, 0.537514f, 0.328039f, 0.564339f );

			pPalletCryoTankHeatersH2Tank9B->DefineGroup( GRP_S32_A15_EDO_VC );
			pPalletCryoTankHeatersH2Tank9B->SetInitialAnimState( 0.5 );
			pPalletCryoTankHeatersH2Tank9B->SetReference( _V( 0.0, 0.374435, -0.025329 ), switch_rot );
			pPalletCryoTankHeatersH2Tank9B->SetMouseRegion( AID_A15, 0.351077f, 0.537514f, 0.392287f, 0.564339f );

			pPalletCryoTank6CntrlO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank6CntrlO2->DefineGroup( GRP_CB3_A15_EDO_VC );
			pPalletCryoTank6CntrlO2->SetDirection( pull_dir );
			pPalletCryoTank6CntrlO2->SetMouseRegion( AID_A15, 0.095994f, 0.632285f, 0.133550f, 0.658674f );

			pPalletCryoTank6CntrlH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank6CntrlH2->DefineGroup( GRP_CB4_A15_EDO_VC );
			pPalletCryoTank6CntrlH2->SetDirection( pull_dir );
			pPalletCryoTank6CntrlH2->SetMouseRegion( AID_A15, 0.148001f, 0.632285f, 0.185057f, 0.658674f );

			pPalletCryoTank6QtyO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank6QtyO2->DefineGroup( GRP_CB5_A15_EDO_VC );
			pPalletCryoTank6QtyO2->SetDirection( pull_dir );
			pPalletCryoTank6QtyO2->SetMouseRegion( AID_A15, 0.199976f, 0.632285f, 0.238166f, 0.658674f );

			pPalletCryoTank6QtyH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank6QtyH2->DefineGroup( GRP_CB6_A15_EDO_VC );
			pPalletCryoTank6QtyH2->SetDirection( pull_dir );
			pPalletCryoTank6QtyH2->SetMouseRegion( AID_A15, 0.258435f, 0.632285f, 0.296172f, 0.658674f );

			pPalletCryoTank6O2HtrSnsr1->SetInitialAnimState( 1.0f );
			pPalletCryoTank6O2HtrSnsr1->DefineGroup( GRP_CB7_A15_EDO_VC );
			pPalletCryoTank6O2HtrSnsr1->SetDirection( pull_dir );
			pPalletCryoTank6O2HtrSnsr1->SetMouseRegion( AID_A15, 0.311611f, 0.632285f, 0.347808f, 0.658674f );

			pPalletCryoTank6O2HtrSnsr2->SetInitialAnimState( 1.0f );
			pPalletCryoTank6O2HtrSnsr2->DefineGroup( GRP_CB8_A15_EDO_VC );
			pPalletCryoTank6O2HtrSnsr2->SetDirection( pull_dir );
			pPalletCryoTank6O2HtrSnsr2->SetMouseRegion( AID_A15, 0.362275f, 0.632285f, 0.401474f, 0.658674f );


			pPalletCryoTank7CntrlO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank7CntrlO2->DefineGroup( GRP_CB9_A15_EDO_VC );
			pPalletCryoTank7CntrlO2->SetDirection( pull_dir );
			pPalletCryoTank7CntrlO2->SetMouseRegion( AID_A15, 0.095994f, 0.683528f, 0.133550f, 0.708837f );

			pPalletCryoTank7CntrlH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank7CntrlH2->DefineGroup( GRP_CB10_A15_EDO_VC );
			pPalletCryoTank7CntrlH2->SetDirection( pull_dir );
			pPalletCryoTank7CntrlH2->SetMouseRegion( AID_A15, 0.148001f, 0.683528f, 0.185057f, 0.708837f );

			pPalletCryoTank7QtyO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank7QtyO2->DefineGroup( GRP_CB11_A15_EDO_VC );
			pPalletCryoTank7QtyO2->SetDirection( pull_dir );
			pPalletCryoTank7QtyO2->SetMouseRegion( AID_A15, 0.199976f, 0.683528f, 0.238166f, 0.708837f );

			pPalletCryoTank7QtyH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank7QtyH2->DefineGroup( GRP_CB12_A15_EDO_VC );
			pPalletCryoTank7QtyH2->SetDirection( pull_dir );
			pPalletCryoTank7QtyH2->SetMouseRegion( AID_A15, 0.258435f, 0.683528f, 0.296172f, 0.708837f );

			pPalletCryoTank7O2HtrSnsr1->SetInitialAnimState( 1.0f );
			pPalletCryoTank7O2HtrSnsr1->DefineGroup( GRP_CB13_A15_EDO_VC );
			pPalletCryoTank7O2HtrSnsr1->SetDirection( pull_dir );
			pPalletCryoTank7O2HtrSnsr1->SetMouseRegion( AID_A15, 0.311611f, 0.683528f, 0.347808f, 0.708837f );

			pPalletCryoTank7O2HtrSnsr2->SetInitialAnimState( 1.0f );
			pPalletCryoTank7O2HtrSnsr2->DefineGroup( GRP_CB14_A15_EDO_VC );
			pPalletCryoTank7O2HtrSnsr2->SetDirection( pull_dir );
			pPalletCryoTank7O2HtrSnsr2->SetMouseRegion( AID_A15, 0.362275f, 0.683528f, 0.401474f, 0.708837f );


			pPalletCryoTank8CntrlO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank8CntrlO2->DefineGroup( GRP_CB15_A15_EDO_VC );
			pPalletCryoTank8CntrlO2->SetDirection( pull_dir );
			pPalletCryoTank8CntrlO2->SetMouseRegion( AID_A15, 0.095994f, 0.740107f, 0.133550f, 0.765952f );

			pPalletCryoTank8CntrlH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank8CntrlH2->DefineGroup( GRP_CB16_A15_EDO_VC );
			pPalletCryoTank8CntrlH2->SetDirection( pull_dir );
			pPalletCryoTank8CntrlH2->SetMouseRegion( AID_A15, 0.148001f, 0.740107f, 0.185057f, 0.765952f );

			pPalletCryoTank8QtyO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank8QtyO2->DefineGroup( GRP_CB17_A15_EDO_VC );
			pPalletCryoTank8QtyO2->SetDirection( pull_dir );
			pPalletCryoTank8QtyO2->SetMouseRegion( AID_A15, 0.199976f, 0.740107f, 0.238166f, 0.765952f );

			pPalletCryoTank8QtyH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank8QtyH2->DefineGroup( GRP_CB18_A15_EDO_VC );
			pPalletCryoTank8QtyH2->SetDirection( pull_dir );
			pPalletCryoTank8QtyH2->SetMouseRegion( AID_A15, 0.258435f, 0.740107f, 0.296172f, 0.765952f );

			pPalletCryoTank8O2HtrSnsr1->SetInitialAnimState( 1.0f );
			pPalletCryoTank8O2HtrSnsr1->DefineGroup( GRP_CB19_A15_EDO_VC );
			pPalletCryoTank8O2HtrSnsr1->SetDirection( pull_dir );
			pPalletCryoTank8O2HtrSnsr1->SetMouseRegion( AID_A15, 0.311611f, 0.740107f, 0.347808f, 0.765952f );

			pPalletCryoTank8O2HtrSnsr2->SetInitialAnimState( 1.0f );
			pPalletCryoTank8O2HtrSnsr2->DefineGroup( GRP_CB20_A15_EDO_VC );
			pPalletCryoTank8O2HtrSnsr2->SetDirection( pull_dir );
			pPalletCryoTank8O2HtrSnsr2->SetMouseRegion( AID_A15, 0.362275f, 0.740107f, 0.401474f, 0.765952f );


			pPalletCryoTank9CntrlO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank9CntrlO2->DefineGroup( GRP_CB21_A15_EDO_VC );
			pPalletCryoTank9CntrlO2->SetDirection( pull_dir );
			pPalletCryoTank9CntrlO2->SetMouseRegion( AID_A15, 0.095994f, 0.790519f, 0.133550f, 0.816670f );

			pPalletCryoTank9CntrlH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank9CntrlH2->DefineGroup( GRP_CB22_A15_EDO_VC );
			pPalletCryoTank9CntrlH2->SetDirection( pull_dir );
			pPalletCryoTank9CntrlH2->SetMouseRegion( AID_A15, 0.148001f, 0.790519f, 0.185057f, 0.816670f );

			pPalletCryoTank9QtyO2->SetInitialAnimState( 1.0f );
			pPalletCryoTank9QtyO2->DefineGroup( GRP_CB23_A15_EDO_VC );
			pPalletCryoTank9QtyO2->SetDirection( pull_dir );
			pPalletCryoTank9QtyO2->SetMouseRegion( AID_A15, 0.199976f, 0.790519f, 0.238166f, 0.816670f );

			pPalletCryoTank9QtyH2->SetInitialAnimState( 1.0f );
			pPalletCryoTank9QtyH2->DefineGroup( GRP_CB24_A15_EDO_VC );
			pPalletCryoTank9QtyH2->SetDirection( pull_dir );
			pPalletCryoTank9QtyH2->SetMouseRegion( AID_A15, 0.258435f, 0.790519f, 0.296172f, 0.816670f );

			pPalletCryoTank9O2HtrSnsr1->SetInitialAnimState( 1.0f );
			pPalletCryoTank9O2HtrSnsr1->DefineGroup( GRP_CB25_A15_EDO_VC );
			pPalletCryoTank9O2HtrSnsr1->SetDirection( pull_dir );
			pPalletCryoTank9O2HtrSnsr1->SetMouseRegion( AID_A15, 0.311611f, 0.790519f, 0.347808f, 0.816670f );

			pPalletCryoTank9O2HtrSnsr2->SetInitialAnimState( 1.0f );
			pPalletCryoTank9O2HtrSnsr2->DefineGroup( GRP_CB26_A15_EDO_VC );
			pPalletCryoTank9O2HtrSnsr2->SetDirection( pull_dir );
			pPalletCryoTank9O2HtrSnsr2->SetMouseRegion( AID_A15, 0.362275f, 0.790519f, 0.401474f, 0.816670f );
		}

		pPSCommCCUPwr->DefineGroup( GRP_S1_A15_EDO_VC );
		pPSCommCCUPwr->SetInitialAnimState( 0.5 );
		pPSCommCCUPwr->SetReference( _V( 0.0, 0.512777, -0.025329 ), switch_rot );
		pPSCommCCUPwr->SetMouseRegion( AID_A15, 0.451285f, 0.371773f, 0.484630f, 0.398001f );

		pDCUtilityPower->DefineGroup( GRP_S2_A15_EDO_VC );
		pDCUtilityPower->SetInitialAnimState( 0.5 );
		pDCUtilityPower->SetReference( _V( 0.0, 0.407409, -0.025329 ), switch_rot );
		pDCUtilityPower->SetMouseRegion( AID_A15, 0.452191f, 0.497690f, 0.484402f, 0.524807f );

		pACUtilityPower->DefineGroup( GRP_S3_A15_EDO_VC );
		pACUtilityPower->SetInitialAnimState( 0.5 );
		pACUtilityPower->SetReference( _V( 0.0, 0.30462, -0.025329 ), switch_rot );
		pACUtilityPower->SetMouseRegion( AID_A15, 0.446693f, 0.622405f, 0.484785f, 0.647413f );
		return;
	}

	void PanelA15_EDO::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A15, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A15,
			_V( 0.84285, 0.83336, -0.0254 ) + ofs, _V( 0.27786, 0.83336, -0.0254 ) + ofs,
			_V( 0.84285, 0.0, -0.0254 ) + ofs, _V( 0.27786, 0.0, -0.0254 ) + ofs );
		return;
	}

	void PanelA15_EDO::Realize( void )
	{
		AtlantisPanel::Realize();

		/*DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "TODO", 16 );
		pPalletPowerPPCA1->SetInput( pBundle, 0, TB_ON );
		pPalletPowerPPCA2->SetInput( pBundle, 1, TB_ON );*/
		return;
	}

	void PanelA15_EDO::VisualCreated( void )
	{
		// hide unneeded controls and load correct texture
		DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
		if (hDevMesh != NULL)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;// hide group and shadow

			if (ov102)
			{
				if (hTexture == NULL) hTexture = oapiLoadTexture( "SSV\\OV\\panelA15_102_EDO.dds" );
				if (hTexture == NULL) throw std::exception( "Could not load texture in panel A15" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELA15_105_EDO_A15_EDO_VC, hTexture );

				oapiEditMeshGroup( hDevMesh, GRP_CB1_104_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB2_104_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S5_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S7_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S8_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_GUARDS_CRYO5_A15_EDO_VC, &grpSpec );

			}
			else if (ov103)
			{
				if (hTexture == NULL) hTexture = oapiLoadTexture( "SSV\\OV\\panelA15_103_EDO.dds" );
				if (hTexture == NULL) throw std::exception( "Could not load texture in panel A15" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELA15_105_EDO_A15_EDO_VC, hTexture );

				oapiEditMeshGroup( hDevMesh, GRP_CB1_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB1_104_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB2_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB2_104_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB3_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB4_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB5_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB6_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB7_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB8_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB9_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB10_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB11_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB12_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB13_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB14_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB15_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB16_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB17_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB18_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB19_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB20_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB21_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB22_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB23_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB24_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB25_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB26_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_DS9_U_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_DS9_L_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_DS10_U_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_DS10_L_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S9_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S10_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S11_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S12_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S13_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S14_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S15_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S16_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S17_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S18_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S19_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S20_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S21_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S22_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S23_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S24_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S25_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S26_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S27_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S28_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S29_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S30_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S31_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S32_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_GUARDS_EDO_A15_EDO_VC, &grpSpec );
			}
			else if (ov104)
			{
				if (hTexture == NULL) hTexture = oapiLoadTexture( "SSV\\OV\\panelA15_104_EDO.dds" );
				if (hTexture == NULL) throw std::exception( "Could not load texture in panel A15" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELA15_105_EDO_A15_EDO_VC, hTexture );

				oapiEditMeshGroup( hDevMesh, GRP_CB1_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB2_A15_EDO_VC, &grpSpec );
			}
			else// if (ov105)
			{
				oapiEditMeshGroup( hDevMesh, GRP_CB1_104_A15_EDO_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_CB2_104_A15_EDO_VC, &grpSpec );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}
