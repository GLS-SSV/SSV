/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
#include "PanelR1.h"
#include "StandardSwitch.h"
#include "StandardSwitchCover.h"
#include "Talkback.h"
#include "CircuitBreaker.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_r1.h"


namespace vc
{
	PanelR1::PanelR1( Atlantis *_sts ):AtlantisPanel( _sts, "R1" )
	{
		DefineMesh( MESHNAME_PANELR1 );

		Add( pControlBusPwrMNA = new StdSwitch2( _sts, "CONTROL BUS PWR MN A" ) );
		pControlBusPwrMNA->SetLabel( 1, "RESET" );
		Add( pControlBusPwrMNB = new StdSwitch2( _sts, "CONTROL BUS PWR MN B" ) );
		pControlBusPwrMNB->SetLabel( 1, "RESET" );
		Add( pControlBusPwrMNC = new StdSwitch2( _sts, "CONTROL BUS PWR MN C" ) );
		pControlBusPwrMNC->SetLabel( 1, "RESET" );

		Add( pEssBusSourceMNBC = new StdSwitch2( _sts, "ESS BUS SOURCE MN B/C" ) );
		pEssBusSourceMNBC->SetLabel( 0, "OFF" );
		pEssBusSourceMNBC->SetLabel( 1, "ON" );
		Add( pEssBusSourceMNCA = new StdSwitch2( _sts, "ESS BUS SOURCE MN C/A" ) );
		pEssBusSourceMNCA->SetLabel( 0, "OFF" );
		pEssBusSourceMNCA->SetLabel( 1, "ON" );
		Add( pEssBusSourceMNAB = new StdSwitch2( _sts, "ESS BUS SOURCE MN A/B" ) );
		pEssBusSourceMNAB->SetLabel( 0, "OFF" );
		pEssBusSourceMNAB->SetLabel( 1, "ON" );

		Add( pEssBusSourceFC1 = new StdSwitch2( _sts, "ESS BUS SOURCE FC 1" ) );
		pEssBusSourceFC1->SetLabel( 0, "OFF" );
		pEssBusSourceFC1->SetLabel( 1, "ON" );
		Add( pEssBusSourceFC2 = new StdSwitch2( _sts, "ESS BUS SOURCE FC 2" ) );
		pEssBusSourceFC2->SetLabel( 0, "OFF" );
		pEssBusSourceFC2->SetLabel( 1, "ON" );
		Add( pEssBusSourceFC3 = new StdSwitch2( _sts, "ESS BUS SOURCE FC 3" ) );
		pEssBusSourceFC3->SetLabel( 0, "OFF" );
		pEssBusSourceFC3->SetLabel( 1, "ON" );

		Add( pFCMainBusA = new LockableLever3( _sts, "FC/MAIN BUS A" ) );
		pFCMainBusA->SetLabel( 0, "OFF" );
		pFCMainBusA->SetLabel( 1, "ON" );
		Add( pFCMainBusB = new LockableLever3( _sts, "FC/MAIN BUS B" ) );
		pFCMainBusB->SetLabel( 0, "OFF" );
		pFCMainBusB->SetLabel( 1, "ON" );
		Add( pFCMainBusC = new LockableLever3( _sts, "FC/MAIN BUS C" ) );
		pFCMainBusC->SetLabel( 0, "OFF" );
		pFCMainBusC->SetLabel( 1, "ON" );

		Add( pMNBusTieA = new StdSwitch3( _sts, "MN BUS TIE A" ) );
		pMNBusTieA->SetLabel( 0, "OFF" );
		pMNBusTieA->SetLabel( 2, "ON" );
		Add( pMNBusTieB = new StdSwitch3( _sts, "MN BUS TIE B" ) );
		pMNBusTieB->SetLabel( 0, "OFF" );
		pMNBusTieB->SetLabel( 2, "ON" );
		Add( pMNBusTieC = new StdSwitch3( _sts, "MN BUS TIE C" ) );
		pMNBusTieC->SetLabel( 0, "OFF" );
		pMNBusTieC->SetLabel( 2, "ON" );

		Add( pInvPwr1 = new StdSwitch3( _sts, "INV PWR 1" ) );
		pInvPwr1->SetLabel( 0, "OFF" );
		pInvPwr1->SetLabel( 2, "ON" );
		Add( pInvPwr2 = new StdSwitch3( _sts, "INV PWR 2" ) );
		pInvPwr2->SetLabel( 0, "OFF" );
		pInvPwr2->SetLabel( 2, "ON" );
		Add( pInvPwr3 = new StdSwitch3( _sts, "INV PWR 3" ) );
		pInvPwr3->SetLabel( 0, "OFF" );
		pInvPwr3->SetLabel( 2, "ON" );

		Add( pInvACBus1 = new StdSwitch3( _sts, "INV/AC BUS 1" ) );
		pInvACBus1->SetLabel( 0, "OFF" );
		pInvACBus1->SetLabel( 2, "ON" );
		Add( pInvACBus2 = new StdSwitch3( _sts, "INV/AC BUS 2" ) );
		pInvACBus2->SetLabel( 0, "OFF" );
		pInvACBus2->SetLabel( 2, "ON" );
		Add( pInvACBus3 = new StdSwitch3( _sts, "Inv/AC Bus 3" ) );
		pInvACBus3->SetLabel( 0, "OFF" );
		pInvACBus3->SetLabel( 2, "ON" );

		Add( pAC_CONTR_AC1_A = new CircuitBreaker( _sts, "AC CONTR AC1 A" ) );
		pAC_CONTR_AC1_A->SetInitialPosition( true );
		Add( pAC_CONTR_AC1_B = new CircuitBreaker( _sts, "AC CONTR AC1 B" ) );
		pAC_CONTR_AC1_B->SetInitialPosition( true );
		Add( pAC_CONTR_AC1_C = new CircuitBreaker( _sts, "AC CONTR AC1 C" ) );
		pAC_CONTR_AC1_C->SetInitialPosition( true );

		Add( pAC_CONTR_AC2_A = new CircuitBreaker( _sts, "AC CONTR AC2 A" ) );
		pAC_CONTR_AC2_A->SetInitialPosition( true );
		Add( pAC_CONTR_AC2_B = new CircuitBreaker( _sts, "AC CONTR AC2 B" ) );
		pAC_CONTR_AC2_B->SetInitialPosition( true );
		Add( pAC_CONTR_AC2_C = new CircuitBreaker( _sts, "AC CONTR AC2 C" ) );
		pAC_CONTR_AC2_C->SetInitialPosition( true );

		Add( pAC_CONTR_AC3_A = new CircuitBreaker( _sts, "AC CONTR AC3 A" ) );
		pAC_CONTR_AC3_A->SetInitialPosition( true );
		Add( pAC_CONTR_AC3_B = new CircuitBreaker( _sts, "AC CONTR AC3 B" ) );
		pAC_CONTR_AC3_B->SetInitialPosition( true );
		Add( pAC_CONTR_AC3_C = new CircuitBreaker( _sts, "AC CONTR AC3 C" ) );
		pAC_CONTR_AC3_C->SetInitialPosition( true );

		Add( pACBusSnsr1 = new StdSwitch3( _sts, "AC BUS SNSR 1" ) );
		pACBusSnsr1->SetLabel( 0, "MONITOR" );
		pACBusSnsr1->SetLabel( 1, "OFF" );
		pACBusSnsr1->SetLabel( 2, "AUTO TRIP" );
		Add( pACBusSnsr2 = new StdSwitch3( _sts, "AC BUS SNSR 2" ) );
		pACBusSnsr2->SetLabel( 0, "MONITOR" );
		pACBusSnsr2->SetLabel( 1, "OFF" );
		pACBusSnsr2->SetLabel( 2, "AUTO TRIP" );
		Add( pACBusSnsr3 = new StdSwitch3( _sts, "AC BUS SNSR 3" ) );
		pACBusSnsr3->SetLabel( 0, "MONITOR" );
		pACBusSnsr3->SetLabel( 1, "OFF" );
		pACBusSnsr3->SetLabel( 2, "AUTO TRIP" );

		Add( pPayloadCabin = new StdSwitch3( _sts, "PAYLOAD CABIN" ) );
		pPayloadCabin->SetLabel( 0, "MN B" );
		pPayloadCabin->SetLabel( 1, "OFF" );
		pPayloadCabin->SetLabel( 2, "MN A" );

		Add( pPayloadPriMNB = new StdSwitch3( _sts, "PAYLOAD PRI MN B" ) );
		pPayloadPriMNB->SetLabel( 0, "OFF" );
		pPayloadPriMNB->SetLabel( 2, "ON" );

		Add( pPayloadPriFC3 = new StdSwitch3( _sts, "PAYLOAD PRI FC 3" ) );
		pPayloadPriFC3->SetLabel( 0, "OFF" );
		pPayloadPriFC3->SetLabel( 2, "ON" );

		Add( pPayloadPriMNC = new StdSwitch3( _sts, "PAYLOAD PRI MN C" ) );
		pPayloadPriMNC->SetLabel( 0, "OFF" );
		pPayloadPriMNC->SetLabel( 2, "ON" );

		Add( pPayloadAuxCover = new StandardSwitchCover( _sts, "PAYLOAD AUX COVER" ) );

		Add( pPayloadAux = new StdSwitch2( _sts, "PAYLOAD AUX" ) );
		pPayloadAux->SetLabel( 0, "OFF" );
		pPayloadAux->SetLabel( 1, "ON" );

		Add( pPayloadAftMNB = new StdSwitch2( _sts, "PAYLOAD AFT MN B" ) );
		pPayloadAftMNB->SetLabel( 0, "OFF" );
		pPayloadAftMNB->SetLabel( 1, "ON" );

		Add( pPayloadAftMNC = new StdSwitch2( _sts, "PAYLOAD AFT MN C" ) );
		pPayloadAftMNC->SetLabel( 0, "OFF" );
		pPayloadAftMNC->SetLabel( 1, "ON" );

		Add( pFuelCell1Reac = new StdSwitch3( _sts, "FUEL CELL 1 REAC" ) );
		pFuelCell1Reac->SetLabel( 0, "CLOSE" );
		pFuelCell1Reac->SetLabel( 2, "OPEN" );

		Add( pFuelCell2Reac = new StdSwitch3( _sts, "FUEL CELL 2 REAC" ) );
		pFuelCell2Reac->SetLabel( 0, "CLOSE" );
		pFuelCell2Reac->SetLabel( 2, "OPEN" );

		Add( pFuelCell3Reac = new StdSwitch3( _sts, "FUEL CELL 3 REAC" ) );
		pFuelCell3Reac->SetLabel( 0, "CLOSE" );
		pFuelCell3Reac->SetLabel( 2, "OPEN" );

		Add( pO2ManifoldVlvTank1 = new StdSwitch3( _sts, "O2 MANIFOLD VLV TANK 1" ) );
		pO2ManifoldVlvTank1->SetLabel( 0, "CLOSE" );
		pO2ManifoldVlvTank1->SetLabel( 2, "OPEN" );

		Add( pO2ManifoldVlvTank2 = new StdSwitch3( _sts, "O2 MANIFOLD VLV TANK 2" ) );
		pO2ManifoldVlvTank2->SetLabel( 0, "CLOSE" );
		pO2ManifoldVlvTank2->SetLabel( 2, "OPEN" );

		Add( pH2ManifoldVlvTank1 = new StdSwitch3( _sts, "H2 MANIFOLD VLV TANK 1" ) );
		pH2ManifoldVlvTank1->SetLabel( 0, "CLOSE" );
		pH2ManifoldVlvTank1->SetLabel( 2, "OPEN" );

		Add( pH2ManifoldVlvTank2 = new StdSwitch3( _sts, "H2 MANIFOLD VLV TANK 2" ) );
		pH2ManifoldVlvTank2->SetLabel( 0, "CLOSE" );
		pH2ManifoldVlvTank2->SetLabel( 2, "OPEN" );

		Add( pO2TK1HeatersA = new StdSwitch3( _sts, "O2 TK1 HEATERS A" ) );
		pO2TK1HeatersA->SetLabel( 0, "ON" );
		pO2TK1HeatersA->SetLabel( 1, "OFF" );
		pO2TK1HeatersA->SetLabel( 2, "AUTO" );

		Add( pO2TK1HeatersB = new StdSwitch3( _sts, "O2 TK1 HEATERS B" ) );
		pO2TK1HeatersB->SetLabel( 0, "ON" );
		pO2TK1HeatersB->SetLabel( 1, "OFF" );
		pO2TK1HeatersB->SetLabel( 2, "AUTO" );

		Add( pO2TK1Heaters = new StdSwitch3( _sts, "O2 TK1 HEATERS" ) );
		pO2TK1Heaters->SetLabel( 0, "TEST" );
		pO2TK1Heaters->SetLabel( 2, "RESET" );

		Add( pO2TK2HeatersA = new StdSwitch3( _sts, "O2 TK2 HEATERS A" ) );
		pO2TK2HeatersA->SetLabel( 0, "ON" );
		pO2TK2HeatersA->SetLabel( 1, "OFF" );
		pO2TK2HeatersA->SetLabel( 2, "AUTO" );

		Add( pO2TK2HeatersB = new StdSwitch3( _sts, "O2 TK2 HEATERS B" ) );
		pO2TK2HeatersB->SetLabel( 0, "ON" );
		pO2TK2HeatersB->SetLabel( 1, "OFF" );
		pO2TK2HeatersB->SetLabel( 2, "AUTO" );

		Add( pO2TK2Heaters = new StdSwitch3( _sts, "O2 TK2 HEATERS" ) );
		pO2TK2Heaters->SetLabel( 0, "TEST" );
		pO2TK2Heaters->SetLabel( 2, "RESET" );

		Add( pO2TK3HeatersA = new StdSwitch3( _sts, "O2 TK3 HEATERS A" ) );
		pO2TK3HeatersA->SetLabel( 0, "ON" );
		pO2TK3HeatersA->SetLabel( 1, "OFF" );
		pO2TK3HeatersA->SetLabel( 2, "AUTO" );

		Add( pO2TK3HeatersB = new StdSwitch3( _sts, "O2 TK3 HEATERS B" ) );
		pO2TK3HeatersB->SetLabel( 0, "ON" );
		pO2TK3HeatersB->SetLabel( 1, "OFF" );
		pO2TK3HeatersB->SetLabel( 2, "AUTO" );

		Add( pO2TK3Heaters = new StdSwitch3( _sts, "O2 TK3 HEATERS" ) );
		pO2TK3Heaters->SetLabel( 0, "TEST" );
		pO2TK3Heaters->SetLabel( 2, "RESET" );

		Add( pH2TK1HeatersA = new StdSwitch3( _sts, "H2 TK1 HEATERS A" ) );
		pH2TK1HeatersA->SetLabel( 0, "ON" );
		pH2TK1HeatersA->SetLabel( 1, "OFF" );
		pH2TK1HeatersA->SetLabel( 2, "AUTO" );

		Add( pH2TK1HeatersB = new StdSwitch3( _sts, "H2 TK1 HEATERS B" ) );
		pH2TK1HeatersB->SetLabel( 0, "ON" );
		pH2TK1HeatersB->SetLabel( 1, "OFF" );
		pH2TK1HeatersB->SetLabel( 2, "AUTO" );

		Add( pH2TK2HeatersA = new StdSwitch3( _sts, "H2 TK2 HEATERS A" ) );
		pH2TK2HeatersA->SetLabel( 0, "ON" );
		pH2TK2HeatersA->SetLabel( 1, "OFF" );
		pH2TK2HeatersA->SetLabel( 2, "AUTO" );

		Add( pH2TK2HeatersB = new StdSwitch3( _sts, "H2 TK2 HEATERS B" ) );
		pH2TK2HeatersB->SetLabel( 0, "ON" );
		pH2TK2HeatersB->SetLabel( 1, "OFF" );
		pH2TK2HeatersB->SetLabel( 2, "AUTO" );

		Add( pH2TK3HeatersA = new StdSwitch3( _sts, "H2 TK3 HEATERS A" ) );
		pH2TK3HeatersA->SetLabel( 0, "ON" );
		pH2TK3HeatersA->SetLabel( 1, "OFF" );
		pH2TK3HeatersA->SetLabel( 2, "AUTO" );

		Add( pH2TK3HeatersB = new StdSwitch3( _sts, "H2 TK3 HEATERS B" ) );
		pH2TK3HeatersB->SetLabel( 0, "ON" );
		pH2TK3HeatersB->SetLabel( 1, "OFF" );
		pH2TK3HeatersB->SetLabel( 2, "AUTO" );

		Add( pFuelCell1 = new LockableLever3( _sts, "FUEL CELL 1" ) );
		pFuelCell1->SetLabel( 0, "STOP" );
		pFuelCell1->SetLabel( 2, "START" );

		Add( pFuelCell2 = new LockableLever3( _sts, "FUEL CELL 2" ) );
		pFuelCell2->SetLabel( 0, "STOP" );
		pFuelCell2->SetLabel( 2, "START" );

		Add( pFuelCell3 = new LockableLever3( _sts, "FUEL CELL 3" ) );
		pFuelCell3->SetLabel( 0, "STOP" );
		pFuelCell3->SetLabel( 2, "START" );

		Add( pFCMainBusATB = new StandardTalkback2( _sts, "FC MAIN BUS A TB" ) );

		Add( pFCMainBusBTB = new StandardTalkback2( _sts, "FC MAIN BUS B TB" ) );

		Add( pFCMainBusCTB = new StandardTalkback2( _sts, "FC MAIN BUS C TB" ) );

		Add( pMNBusTieATB = new StandardTalkback2( _sts, "MN BUS TIE A TB" ) );

		Add( pMNBusTieBTB = new StandardTalkback2( _sts, "MN BUS TIE B TB" ) );

		Add( pMNBusTieCTB = new StandardTalkback2( _sts, "MN BUS TIE C TB" ) );

		Add( pInvPwr1TB = new StandardTalkback2( _sts, "INV PWR 1 TB" ) );

		Add( pInvPwr2TB = new StandardTalkback2( _sts, "INV PWR 2 TB" ) );

		Add( pInvPwr3TB = new StandardTalkback2( _sts, "INV PWR 3 TB" ) );

		Add( pInvACBus1TB = new StandardTalkback2( _sts, "INV/AC BUS 1 TB" ) );

		Add( pInvACBus2TB = new StandardTalkback2( _sts, "INV/AC BUS 2 TB" ) );

		Add( pInvACBus3TB = new StandardTalkback2( _sts, "INV/AC BUS 3 TB" ) );

		Add( pPayloadPriMNBTB = new StandardTalkback2( _sts, "PAYLOAD PRI MN B TB" ) );

		Add( pPayloadPriFC3TB = new StandardTalkback2( _sts, "PAYLOAD PRI FC 3 TB" ) );

		Add( pPayloadPriMNCTB = new StandardTalkback2( _sts, "PAYLOAD PRI MN C TB" ) );

		Add( pFuelCell1ReacO2 = new StandardTalkback2( _sts, "FUEL CELL 1 REAC O2" ) );

		Add( pFuelCell2ReacO2 = new StandardTalkback2( _sts, "FUEL CELL 2 REAC O2" ) );

		Add( pFuelCell3ReacO2 = new StandardTalkback2( _sts, "FUEL CELL 3 REAC O2" ) );

		Add( pFuelCell1ReacH2 = new StandardTalkback2( _sts, "FUEL CELL 1 REAC H2" ) );

		Add( pFuelCell2ReacH2 = new StandardTalkback2( _sts, "FUEL CELL 2 REAC H2" ) );

		Add( pFuelCell3ReacH2 = new StandardTalkback2( _sts, "FUEL CELL 3 REAC H2" ) );

		Add( pO2ManifoldVlvTank1TB = new StandardTalkback2( _sts, "O2 MANIFOLD VLV TANK 1 TB" ) );

		Add( pO2ManifoldVlvTank2TB = new StandardTalkback2( _sts, "O2 MANIFOLD VLV TANK 2 TB" ) );

		Add( pH2ManifoldVlvTank1TB = new StandardTalkback2( _sts, "H2 MANIFOLD VLV TANK 1 TB" ) );

		Add( pH2ManifoldVlvTank2TB = new StandardTalkback2( _sts, "H2 MANIFOLD VLV TANK 2 TB" ) );

		Add( pFuelCellReadyForLoad1 = new StandardTalkback2( _sts, "FUEL CELL READY FOR LOAD 1" ) );

		Add( pFuelCellReadyForLoad2 = new StandardTalkback2( _sts, "FUEL CELL READY FOR LOAD 2" ) );

		Add( pFuelCellReadyForLoad3 = new StandardTalkback2( _sts, "FUEL CELL READY FOR LOAD 3" ) );

		Add( pFuelCellCoolantPumpdP1 = new StandardTalkback2( _sts, "FUEL CELL COOLANT PUMP dP 1" ) );

		Add( pFuelCellCoolantPumpdP2 = new StandardTalkback2( _sts, "FUEL CELL COOLANT PUMP dP 2" ) );

		Add( pFuelCellCoolantPumpdP3 = new StandardTalkback2( _sts, "FUEL CELL COOLANT PUMP dP 3" ) );
	}

	PanelR1::~PanelR1()
	{
	}

	void PanelR1::DefineVC( void )
	{
		const VECTOR3 switch_rot = _V( 0.33298, -0.00978, -0.9404 );
		const VECTOR3 switch_pull = _V( -0.9171, 0.2194, -0.3328 );
		const VECTOR3 CB_PULL = switch_pull;

		AddAIDToMouseEventList( AID_R1 );

		pControlBusPwrMNA->SetInitialAnimState( 0.5f );
		pControlBusPwrMNA->DefineGroup( GRP_A1_S1_R1_VC );
		pControlBusPwrMNA->SetReference( _V( 1.1925, 2.1526, 14.6480 ), switch_rot );
		pControlBusPwrMNA->SetMouseRegion( AID_R1, 0.069446f, 0.166435f, 0.088014f, 0.233550f );
		pControlBusPwrMNA->SetSpringLoaded( true );

		pControlBusPwrMNB->SetInitialAnimState( 0.5f );
		pControlBusPwrMNB->DefineGroup( GRP_A1_S2_R1_VC );
		pControlBusPwrMNB->SetReference( _V( 1.1797, 2.0951, 14.6441 ), switch_rot );
		pControlBusPwrMNB->SetMouseRegion( AID_R1, 0.057635f, 0.339876f, 0.077927f, 0.408386f );
		pControlBusPwrMNB->SetSpringLoaded( true );

		pControlBusPwrMNC->SetInitialAnimState( 0.5f );
		pControlBusPwrMNC->DefineGroup( GRP_A1_S3_R1_VC );
		pControlBusPwrMNC->SetReference( _V( 1.1664, 2.0381, 14.6399 ), switch_rot );
		pControlBusPwrMNC->SetMouseRegion( AID_R1, 0.047596f, 0.514156f, 0.068455f, 0.585026f );
		pControlBusPwrMNC->SetSpringLoaded( true );

		pEssBusSourceMNBC->SetInitialAnimState( 0.5f );
		pEssBusSourceMNBC->DefineGroup( GRP_A1_S4_R1_VC );
		pEssBusSourceMNBC->SetReference( _V( 1.1925, 2.1526, 14.6480 ), switch_rot );
		pEssBusSourceMNBC->SetMouseRegion( AID_R1, 0.119187f, 0.164126f, 0.137888f, 0.233977f );

		pEssBusSourceMNCA->SetInitialAnimState( 0.5f );
		pEssBusSourceMNCA->DefineGroup( GRP_A1_S5_R1_VC );
		pEssBusSourceMNCA->SetReference( _V( 1.1797, 2.0951, 14.6441 ), switch_rot );
		pEssBusSourceMNCA->SetMouseRegion( AID_R1, 0.107904f, 0.340237f, 0.125902f, 0.408059f );

		pEssBusSourceMNAB->SetInitialAnimState( 0.5f );
		pEssBusSourceMNAB->DefineGroup( GRP_A1_S6_R1_VC );
		pEssBusSourceMNAB->SetReference( _V( 1.1664, 2.0381, 14.6399 ), switch_rot );
		pEssBusSourceMNAB->SetMouseRegion( AID_R1, 0.096658f, 0.514786f, 0.115279f, 0.582150f );

		pEssBusSourceFC1->SetInitialAnimState( 0.5f );
		pEssBusSourceFC1->DefineGroup( GRP_A1_S7_R1_VC );
		pEssBusSourceFC1->SetReference( _V( 1.1925, 2.1526, 14.6480 ), switch_rot );
		pEssBusSourceFC1->SetMouseRegion( AID_R1, 0.169292f, 0.166575f, 0.187370f, 0.236009f );

		pEssBusSourceFC2->SetInitialAnimState( 0.5f );
		pEssBusSourceFC2->DefineGroup( GRP_A1_S8_R1_VC );
		pEssBusSourceFC2->SetReference( _V( 1.1797, 2.0951, 14.6441 ), switch_rot );
		pEssBusSourceFC2->SetMouseRegion( AID_R1, 0.158506f, 0.342708f, 0.177224f, 0.410471f );

		pEssBusSourceFC3->SetInitialAnimState( 0.5f );
		pEssBusSourceFC3->DefineGroup( GRP_A1_S9_R1_VC );
		pEssBusSourceFC3->SetReference( _V( 1.1664, 2.0381, 14.6399 ), switch_rot );
		pEssBusSourceFC3->SetMouseRegion( AID_R1, 0.147168f, 0.512602f, 0.165938f, 0.581663f );

		pFCMainBusA->SetInitialAnimState( 0.5f );
		pFCMainBusA->DefineGroup( GRP_A1_S10_R1_VC );
		pFCMainBusA->SetReference( _V( 1.1925, 2.1526, 14.6480 ), switch_rot );
		pFCMainBusA->SetPullDirection( switch_pull );
		pFCMainBusA->SetMouseRegion( AID_R1, 0.218102f, 0.164787f, 0.238058f, 0.234013f );
		pFCMainBusA->SetSpringLoaded( true, 0 );
		pFCMainBusA->SetSpringLoaded( true, 2 );

		pFCMainBusB->SetInitialAnimState( 0.5f );
		pFCMainBusB->DefineGroup( GRP_A1_S11_R1_VC );
		pFCMainBusB->SetReference( _V( 1.1797, 2.0951, 14.6441 ), switch_rot );
		pFCMainBusB->SetPullDirection( switch_pull );
		pFCMainBusB->SetMouseRegion( AID_R1, 0.207947f, 0.340869f, 0.228262f, 0.409300f );
		pFCMainBusB->SetSpringLoaded( true, 0 );
		pFCMainBusB->SetSpringLoaded( true, 2 );

		pFCMainBusC->SetInitialAnimState( 0.5f );
		pFCMainBusC->DefineGroup( GRP_A1_S12_R1_VC );
		pFCMainBusC->SetReference( _V( 1.1664, 2.0381, 14.6399 ), switch_rot );
		pFCMainBusC->SetPullDirection( switch_pull );
		pFCMainBusC->SetMouseRegion( AID_R1, 0.196878f, 0.513641f, 0.217177f, 0.579977f );
		pFCMainBusC->SetSpringLoaded( true, 0 );
		pFCMainBusC->SetSpringLoaded( true, 2 );

		pMNBusTieA->SetInitialAnimState( 0.5f );
		pMNBusTieA->DefineGroup( GRP_A1_S13_R1_VC );
		pMNBusTieA->SetReference( _V( 1.1925, 2.1526, 14.6480 ), switch_rot );
		pMNBusTieA->SetMouseRegion( AID_R1, 0.286649f, 0.163550f, 0.306875f, 0.233598f );
		pMNBusTieA->SetSpringLoaded( true, 0 );
		pMNBusTieA->SetSpringLoaded( true, 2 );

		pMNBusTieB->SetInitialAnimState( 0.5f );
		pMNBusTieB->DefineGroup( GRP_A1_S14_R1_VC );
		pMNBusTieB->SetReference( _V( 1.1797, 2.0951, 14.6441 ), switch_rot );
		pMNBusTieB->SetMouseRegion( AID_R1, 0.274631f, 0.339246f, 0.294351f, 0.409492f );
		pMNBusTieB->SetSpringLoaded( true, 0 );
		pMNBusTieB->SetSpringLoaded( true, 2 );

		pMNBusTieC->SetInitialAnimState( 0.5f );
		pMNBusTieC->DefineGroup( GRP_A1_S15_R1_VC );
		pMNBusTieC->SetReference( _V( 1.1664, 2.0381, 14.6399 ), switch_rot );
		pMNBusTieC->SetMouseRegion( AID_R1, 0.265610f, 0.515440f, 0.284506f, 0.582897f );
		pMNBusTieC->SetSpringLoaded( true, 0 );
		pMNBusTieC->SetSpringLoaded( true, 2 );

		pInvPwr1->SetInitialAnimState( 0.5f );
		pInvPwr1->DefineGroup( GRP_A1_S16_R1_VC );
		pInvPwr1->SetReference( _V( 1.2845, 2.1147, 14.3638 ), switch_rot );
		pInvPwr1->SetMouseRegion( AID_R1, 0.364295f, 0.267669f, 0.382682f, 0.340316f );
		pInvPwr1->SetSpringLoaded( true, 0 );
		pInvPwr1->SetSpringLoaded( true, 2 );

		pInvPwr2->SetInitialAnimState( 0.5f );
		pInvPwr2->DefineGroup( GRP_A1_S17_R1_VC );
		pInvPwr2->SetReference( _V( 1.2654, 2.0300, 14.3561 ), switch_rot );
		pInvPwr2->SetMouseRegion( AID_R1, 0.348628f, 0.527914f, 0.368419f, 0.600194f );
		pInvPwr2->SetSpringLoaded( true, 0 );
		pInvPwr2->SetSpringLoaded( true, 2 );

		pInvPwr3->SetInitialAnimState( 0.5f );
		pInvPwr3->DefineGroup( GRP_A1_S18_R1_VC );
		pInvPwr3->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pInvPwr3->SetMouseRegion( AID_R1, 0.331337f, 0.788743f, 0.351055f, 0.862777f );
		pInvPwr3->SetSpringLoaded( true, 0 );
		pInvPwr3->SetSpringLoaded( true, 2 );

		pInvACBus1->SetInitialAnimState( 0.5f );
		pInvACBus1->DefineGroup( GRP_A1_S19_R1_VC );
		pInvACBus1->SetReference( _V( 1.2845, 2.1147, 14.3638 ), switch_rot );
		pInvACBus1->SetMouseRegion( AID_R1, 0.411120f, 0.266515f, 0.431888f, 0.342026f );
		pInvACBus1->SetSpringLoaded( true, 0 );
		pInvACBus1->SetSpringLoaded( true, 2 );

		pInvACBus2->SetInitialAnimState( 0.5f );
		pInvACBus2->DefineGroup( GRP_A1_S20_R1_VC );
		pInvACBus2->SetReference( _V( 1.2654, 2.0300, 14.3561 ), switch_rot );
		pInvACBus2->SetMouseRegion( AID_R1, 0.396130f, 0.527200f, 0.415532f, 0.600780f );
		pInvACBus2->SetSpringLoaded( true, 0 );
		pInvACBus2->SetSpringLoaded( true, 2 );

		pInvACBus3->SetInitialAnimState( 0.5f );
		pInvACBus3->DefineGroup( GRP_A1_S21_R1_VC );
		pInvACBus3->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pInvACBus3->SetMouseRegion( AID_R1, 0.378402f, 0.789128f, 0.397712f, 0.863190f );
		pInvACBus3->SetSpringLoaded( true, 0 );
		pInvACBus3->SetSpringLoaded( true, 2 );

		pAC_CONTR_AC1_A->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC1_A->DefineGroup( GRP_A1_CB1_R1_VC );
		pAC_CONTR_AC1_A->SetDirection( CB_PULL );
		pAC_CONTR_AC1_A->SetMouseRegion( AID_R1, 0.469309f, 0.132224f, 0.488917f, 0.204546f );

		pAC_CONTR_AC1_B->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC1_B->DefineGroup( GRP_A1_CB2_R1_VC );
		pAC_CONTR_AC1_B->SetDirection( CB_PULL );
		pAC_CONTR_AC1_B->SetMouseRegion( AID_R1, 0.464212f, 0.218165f, 0.484293f, 0.290714f );

		pAC_CONTR_AC1_C->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC1_C->DefineGroup( GRP_A1_CB3_R1_VC );
		pAC_CONTR_AC1_C->SetDirection( CB_PULL );
		pAC_CONTR_AC1_C->SetMouseRegion( AID_R1, 0.458189f, 0.306294f, 0.478605f, 0.376894f );

		pAC_CONTR_AC2_A->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC2_A->DefineGroup( GRP_A1_CB4_R1_VC );
		pAC_CONTR_AC2_A->SetDirection( CB_PULL );
		pAC_CONTR_AC2_A->SetMouseRegion( AID_R1, 0.452358f, 0.394015f, 0.473053f, 0.462225f );

		pAC_CONTR_AC2_B->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC2_B->DefineGroup( GRP_A1_CB5_R1_VC );
		pAC_CONTR_AC2_B->SetDirection( CB_PULL );
		pAC_CONTR_AC2_B->SetMouseRegion( AID_R1, 0.447105f, 0.480824f, 0.467379f, 0.550284f );

		pAC_CONTR_AC2_C->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC2_C->DefineGroup( GRP_A1_CB6_R1_VC );
		pAC_CONTR_AC2_C->SetDirection( CB_PULL );
		pAC_CONTR_AC2_C->SetMouseRegion( AID_R1, 0.441951f, 0.566732f, 0.462295f, 0.635933f );

		pAC_CONTR_AC3_A->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC3_A->DefineGroup( GRP_A1_CB7_R1_VC );
		pAC_CONTR_AC3_A->SetDirection( CB_PULL );
		pAC_CONTR_AC3_A->SetMouseRegion( AID_R1, 0.435587f, 0.654342f, 0.456408f, 0.723313f );

		pAC_CONTR_AC3_B->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC3_B->DefineGroup( GRP_A1_CB8_R1_VC );
		pAC_CONTR_AC3_B->SetDirection( CB_PULL );
		pAC_CONTR_AC3_B->SetMouseRegion( AID_R1, 0.429836f, 0.742306f, 0.450628f, 0.812281f );

		pAC_CONTR_AC3_C->SetInitialAnimState( 1.0f );
		pAC_CONTR_AC3_C->DefineGroup( GRP_A1_CB9_R1_VC );
		pAC_CONTR_AC3_C->SetDirection( CB_PULL );
		pAC_CONTR_AC3_C->SetMouseRegion( AID_R1, 0.424435f, 0.831931f, 0.443429f, 0.902909f );

		pACBusSnsr1->SetInitialAnimState( 0.5f );
		pACBusSnsr1->DefineGroup( GRP_A1_S22_R1_VC );
		pACBusSnsr1->SetReference( _V( 1.3400, 2.1310, 14.2199 ), switch_rot );
		pACBusSnsr1->SetMouseRegion( AID_R1, 0.520422f, 0.216326f, 0.541343f, 0.293934f );

		pACBusSnsr2->SetInitialAnimState( 0.5f );
		pACBusSnsr2->DefineGroup( GRP_A1_S23_R1_VC );
		pACBusSnsr2->SetReference( _V( 1.3203, 2.0466, 14.2126 ), switch_rot );
		pACBusSnsr2->SetMouseRegion( AID_R1, 0.504962f, 0.477589f, 0.525558f, 0.550331f );

		pACBusSnsr3->SetInitialAnimState( 0.5f );
		pACBusSnsr3->DefineGroup( GRP_A1_S24_R1_VC );
		pACBusSnsr3->SetReference( _V( 1.3017, 1.9596, 14.2075 ), switch_rot );
		pACBusSnsr3->SetMouseRegion( AID_R1, 0.486880f, 0.734950f, 0.507597f, 0.812667f );

		pPayloadCabin->SetInitialAnimState( 0.5f );
		pPayloadCabin->DefineGroup( GRP_A1_S25_R1_VC );
		pPayloadCabin->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadCabin->SetMouseRegion( AID_R1, 0.045919f, 0.787858f, 0.065093f, 0.860649f );

		pPayloadPriMNB->SetInitialAnimState( 0.5f );
		pPayloadPriMNB->DefineGroup( GRP_A1_S26_R1_VC );
		pPayloadPriMNB->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadPriMNB->SetMouseRegion( AID_R1, 0.093539f, 0.784247f, 0.111473f, 0.861887f );
		pPayloadPriMNB->SetSpringLoaded( true, 0 );
		pPayloadPriMNB->SetSpringLoaded( true, 2 );

		pPayloadPriFC3->SetInitialAnimState( 0.5f );
		pPayloadPriFC3->DefineGroup( GRP_A1_S27_R1_VC );
		pPayloadPriFC3->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadPriFC3->SetMouseRegion( AID_R1, 0.124323f, 0.784175f, 0.142225f, 0.864527f );
		pPayloadPriFC3->SetSpringLoaded( true, 0 );
		pPayloadPriFC3->SetSpringLoaded( true, 2 );

		pPayloadPriMNC->SetInitialAnimState( 0.5f );
		pPayloadPriMNC->DefineGroup( GRP_A1_S28_R1_VC );
		pPayloadPriMNC->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadPriMNC->SetMouseRegion( AID_R1, 0.154036f, 0.786062f, 0.172829f, 0.862178f );
		pPayloadPriMNC->SetSpringLoaded( true, 0 );
		pPayloadPriMNC->SetSpringLoaded( true, 2 );

		pPayloadAuxCover->SetMouseRegion( AID_R1, 0, 0.200874f, 0.776744f, 0.219259f, 0.864713f );
		pPayloadAuxCover->SetMouseRegion( AID_R1, 1, 0.203431f, 0.732213f, 0.225585f, 0.768312f );
		pPayloadAuxCover->DefineGroup( GRP_A1_COVER29_R1_VC );
		pPayloadAuxCover->SetReference( _V( 1.2095, 1.9622, 14.4680 ), switch_rot );

		pPayloadAux->SetInitialAnimState( 0.5f );
		pPayloadAux->DefineGroup( GRP_A1_S29_R1_VC );
		pPayloadAux->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadAux->SetMouseRegion( AID_R1, 0.199678f, 0.790226f, 0.218994f, 0.863155f );

		pPayloadAftMNB->SetInitialAnimState( 0.5f );
		pPayloadAftMNB->DefineGroup( GRP_A1_S30_R1_VC );
		pPayloadAftMNB->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadAftMNB->SetMouseRegion( AID_R1, 0.246471f, 0.790336f, 0.265298f, 0.863592f );

		pPayloadAftMNC->SetInitialAnimState( 0.5f );
		pPayloadAftMNC->DefineGroup( GRP_A1_S31_R1_VC );
		pPayloadAftMNC->SetReference( _V( 1.2465, 1.9432, 14.3505 ), switch_rot );
		pPayloadAftMNC->SetMouseRegion( AID_R1, 0.277791f, 0.791175f, 0.295811f, 0.864617f );

		pFuelCell1Reac->SetInitialAnimState( 0.5f );
		pFuelCell1Reac->DefineGroup( GRP_A2_S1_R1_VC );
		pFuelCell1Reac->SetReference( _V( 1.4330, 2.1530, 13.9740 ), switch_rot );
		pFuelCell1Reac->SetMouseRegion( AID_R1, 0.789772f, 0.139809f, 0.809598f, 0.215341f );
		pFuelCell1Reac->SetSpringLoaded( true, 0 );
		pFuelCell1Reac->SetSpringLoaded( true, 2 );

		pFuelCell2Reac->SetInitialAnimState( 0.5f );
		pFuelCell2Reac->DefineGroup( GRP_A2_S7_R1_VC );
		pFuelCell2Reac->SetReference( _V( 1.4115, 2.0517, 13.9664 ), switch_rot );
		pFuelCell2Reac->SetMouseRegion( AID_R1, 0.768949f, 0.445541f, 0.788966f, 0.522213f );
		pFuelCell2Reac->SetSpringLoaded( true, 0 );
		pFuelCell2Reac->SetSpringLoaded( true, 2 );

		pFuelCell3Reac->SetInitialAnimState( 0.5f );
		pFuelCell3Reac->DefineGroup( GRP_A2_S4_R1_VC );
		pFuelCell3Reac->SetReference( _V( 1.4225, 2.1024, 13.9698 ), switch_rot );
		pFuelCell3Reac->SetMouseRegion( AID_R1, 0.779078f, 0.292172f, 0.799463f, 0.370995f );
		pFuelCell3Reac->SetSpringLoaded( true, 0 );
		pFuelCell3Reac->SetSpringLoaded( true, 2 );

		pO2ManifoldVlvTank1->SetInitialAnimState( 0.5f );
		pO2ManifoldVlvTank1->DefineGroup( GRP_A2_S2_R1_VC );
		pO2ManifoldVlvTank1->SetReference( _V( 1.3974, 2.1473, 14.0685 ), switch_rot );
		pO2ManifoldVlvTank1->SetMouseRegion( AID_R1, 0.686635f, 0.159957f, 0.707208f, 0.235806f );
		pO2ManifoldVlvTank1->SetSpringLoaded( true, 0 );
		pO2ManifoldVlvTank1->SetSpringLoaded( true, 2 );

		pO2ManifoldVlvTank2->SetInitialAnimState( 0.5f );
		pO2ManifoldVlvTank2->DefineGroup( GRP_A2_S5_R1_VC );
		pO2ManifoldVlvTank2->SetReference( _V( 1.4225, 2.1024, 13.9698 ), switch_rot );
		pO2ManifoldVlvTank2->SetMouseRegion( AID_R1, 0.677626f, 0.292308f, 0.698955f, 0.365463f );
		pO2ManifoldVlvTank2->SetSpringLoaded( true, 0 );
		pO2ManifoldVlvTank2->SetSpringLoaded( true, 2 );

		pH2ManifoldVlvTank1->SetInitialAnimState( 0.5f );
		pH2ManifoldVlvTank1->DefineGroup( GRP_A2_S3_R1_VC );
		pH2ManifoldVlvTank1->SetReference( _V( 1.3974, 2.1473, 14.0685 ), switch_rot );
		pH2ManifoldVlvTank1->SetMouseRegion( AID_R1, 0.887703f, 0.163310f, 0.907984f, 0.242464f );
		pH2ManifoldVlvTank1->SetSpringLoaded( true, 0 );
		pH2ManifoldVlvTank1->SetSpringLoaded( true, 2 );

		pH2ManifoldVlvTank2->SetInitialAnimState( 0.5f );
		pH2ManifoldVlvTank2->DefineGroup( GRP_A2_S6_R1_VC );
		pH2ManifoldVlvTank2->SetReference( _V( 1.4225, 2.1024, 13.9698 ), switch_rot );
		pH2ManifoldVlvTank2->SetMouseRegion( AID_R1, 0.879691f, 0.294468f, 0.899239f, 0.372147f );
		pH2ManifoldVlvTank2->SetSpringLoaded( true, 0 );
		pH2ManifoldVlvTank2->SetSpringLoaded( true, 2 );

		pO2TK1HeatersA->SetInitialAnimState( 0.5f );
		pO2TK1HeatersA->DefineGroup( GRP_A2_S8_R1_VC );
		pO2TK1HeatersA->SetReference( _V( 1.3533, 2.0372, 14.1175 ), switch_rot );
		pO2TK1HeatersA->SetMouseRegion( AID_R1, 0.604301f, 0.494231f, 0.624059f, 0.572430f );

		pO2TK1HeatersB->SetInitialAnimState( 0.5f );
		pO2TK1HeatersB->DefineGroup( GRP_A2_S9_R1_VC );
		pO2TK1HeatersB->SetReference( _V( 1.3533, 2.0372, 14.1175 ), switch_rot );
		pO2TK1HeatersB->SetMouseRegion( AID_R1, 0.643711f, 0.493677f, 0.664358f, 0.571084f );

		pO2TK1Heaters->SetInitialAnimState( 0.5f );
		pO2TK1Heaters->DefineGroup( GRP_A2_S10_R1_VC );
		pO2TK1Heaters->SetReference( _V( 1.3533, 2.0372, 14.1175 ), switch_rot );
		pO2TK1Heaters->SetMouseRegion( AID_R1, 0.680614f, 0.492395f, 0.699791f, 0.568913f );
		pO2TK1Heaters->SetSpringLoaded( true, 0 );
		pO2TK1Heaters->SetSpringLoaded( true, 2 );

		pO2TK2HeatersA->SetInitialAnimState( 0.5f );
		pO2TK2HeatersA->DefineGroup( GRP_A2_S13_R1_VC );
		pO2TK2HeatersA->SetReference( _V( 1.3428, 1.9859, 14.1137 ), switch_rot );
		pO2TK2HeatersA->SetMouseRegion( AID_R1, 0.594756f, 0.649479f, 0.614555f, 0.724077f );

		pO2TK2HeatersB->SetInitialAnimState( 0.5f );
		pO2TK2HeatersB->DefineGroup( GRP_A2_S14_R1_VC );
		pO2TK2HeatersB->SetReference( _V( 1.3428, 1.9859, 14.1137 ), switch_rot );
		pO2TK2HeatersB->SetMouseRegion( AID_R1, 0.635746f, 0.646391f, 0.653571f, 0.725934f );

		pO2TK2Heaters->SetInitialAnimState( 0.5f );
		pO2TK2Heaters->DefineGroup( GRP_A2_S15_R1_VC );
		pO2TK2Heaters->SetReference( _V( 1.3428, 1.9859, 14.1137 ), switch_rot );
		pO2TK2Heaters->SetMouseRegion( AID_R1, 0.671732f, 0.643791f, 0.689679f, 0.723404f );
		pO2TK2Heaters->SetSpringLoaded( true, 0 );
		pO2TK2Heaters->SetSpringLoaded( true, 2 );

		pO2TK3HeatersA->SetInitialAnimState( 0.5f );
		pO2TK3HeatersA->DefineGroup( GRP_A2_S21_R1_VC );
		pO2TK3HeatersA->SetReference( _V( 1.3319, 1.9360, 14.1100 ), switch_rot );
		pO2TK3HeatersA->SetMouseRegion( AID_R1, 0.586690f, 0.796075f, 0.604818f, 0.876574f );

		pO2TK3HeatersB->SetInitialAnimState( 0.5f );
		pO2TK3HeatersB->DefineGroup( GRP_A2_S22_R1_VC );
		pO2TK3HeatersB->SetReference( _V( 1.3319, 1.9360, 14.1100 ), switch_rot );
		pO2TK3HeatersB->SetMouseRegion( AID_R1, 0.624927f, 0.796604f, 0.643888f, 0.875995f );

		pO2TK3Heaters->SetInitialAnimState( 0.5f );
		pO2TK3Heaters->DefineGroup( GRP_A2_S23_R1_VC );
		pO2TK3Heaters->SetReference( _V( 1.3319, 1.9360, 14.1100 ), switch_rot );
		pO2TK3Heaters->SetMouseRegion( AID_R1, 0.660057f, 0.794125f, 0.679893f, 0.875792f );
		pO2TK3Heaters->SetSpringLoaded( true, 0 );
		pO2TK3Heaters->SetSpringLoaded( true, 2 );

		pH2TK1HeatersA->SetInitialAnimState( 0.5f );
		pH2TK1HeatersA->DefineGroup( GRP_A2_S11_R1_VC );
		pH2TK1HeatersA->SetReference( _V( 1.3533, 2.0372, 14.1175 ), switch_rot );
		pH2TK1HeatersA->SetMouseRegion( AID_R1, 0.850473f, 0.497816f, 0.871936f, 0.569279f );

		pH2TK1HeatersB->SetInitialAnimState( 0.5f );
		pH2TK1HeatersB->DefineGroup( GRP_A2_S12_R1_VC );
		pH2TK1HeatersB->SetReference( _V( 1.3533, 2.0372, 14.1175 ), switch_rot );
		pH2TK1HeatersB->SetMouseRegion( AID_R1, 0.889951f, 0.496632f, 0.909783f, 0.573041f );

		pH2TK2HeatersA->SetInitialAnimState( 0.5f );
		pH2TK2HeatersA->DefineGroup( GRP_A2_S19_R1_VC );
		pH2TK2HeatersA->SetReference( _V( 1.3428, 1.9859, 14.1137 ), switch_rot );
		pH2TK2HeatersA->SetMouseRegion( AID_R1, 0.840319f, 0.647562f, 0.859615f, 0.717474f );

		pH2TK2HeatersB->SetInitialAnimState( 0.5f );
		pH2TK2HeatersB->DefineGroup( GRP_A2_S20_R1_VC );
		pH2TK2HeatersB->SetReference( _V( 1.3428, 1.9859, 14.1137 ), switch_rot );
		pH2TK2HeatersB->SetMouseRegion( AID_R1, 0.880004f, 0.646139f, 0.899238f, 0.719269f );

		pH2TK3HeatersA->SetInitialAnimState( 0.5f );
		pH2TK3HeatersA->DefineGroup( GRP_A2_S24_R1_VC );
		pH2TK3HeatersA->SetReference( _V( 1.3319, 1.9360, 14.1100 ), switch_rot );
		pH2TK3HeatersA->SetMouseRegion( AID_R1, 0.829226f, 0.797709f, 0.849242f, 0.868222f );

		pH2TK3HeatersB->SetInitialAnimState( 0.5f );
		pH2TK3HeatersB->DefineGroup( GRP_A2_S25_R1_VC );
		pH2TK3HeatersB->SetReference( _V( 1.3319, 1.9360, 14.1100 ), switch_rot );
		pH2TK3HeatersB->SetMouseRegion( AID_R1, 0.868802f, 0.799046f, 0.888961f, 0.869549f );

		pFuelCell1->SetInitialAnimState( 0.5f );
		pFuelCell1->DefineGroup( GRP_A2_S16_R1_VC );
		pFuelCell1->SetReference( _V( 1.3718, 1.9650, 14.0063 ), switch_rot );
		pFuelCell1->SetPullDirection( switch_pull );
		pFuelCell1->SetMouseRegion( AID_R1, 0.711174f, 0.710608f, 0.731550f, 0.790725f );
		pFuelCell1->SetSpringLoaded( true, 0 );
		pFuelCell1->SetSpringLoaded( true, 2 );

		pFuelCell2->SetInitialAnimState( 0.5f );
		pFuelCell2->DefineGroup( GRP_A2_S17_R1_VC );
		pFuelCell2->SetReference( _V( 1.3718, 1.9650, 14.0063 ), switch_rot );
		pFuelCell2->SetPullDirection( switch_pull );
		pFuelCell2->SetMouseRegion( AID_R1, 0.750424f, 0.708584f, 0.771162f, 0.788885f );
		pFuelCell2->SetSpringLoaded( true, 0 );
		pFuelCell2->SetSpringLoaded( true, 2 );

		pFuelCell3->SetInitialAnimState( 0.5f );
		pFuelCell3->DefineGroup( GRP_A2_S18_R1_VC );
		pFuelCell3->SetReference( _V( 1.3718, 1.9650, 14.0063 ), switch_rot );
		pFuelCell3->SetPullDirection( switch_pull );
		pFuelCell3->SetMouseRegion( AID_R1, 0.791352f, 0.712022f, 0.811377f, 0.793408f );
		pFuelCell3->SetSpringLoaded( true, 0 );
		pFuelCell3->SetSpringLoaded( true, 2 );

		pFCMainBusATB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS1_U_R1_VC, GRP_A1_DS1_L_R1_VC );
		pFCMainBusATB->SetInactiveSegment( TB_OFF );

		pFCMainBusBTB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS3_U_R1_VC, GRP_A1_DS3_L_R1_VC );
		pFCMainBusBTB->SetInactiveSegment( TB_OFF );

		pFCMainBusCTB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS5_U_R1_VC, GRP_A1_DS5_L_R1_VC );
		pFCMainBusCTB->SetInactiveSegment( TB_OFF );

		pMNBusTieATB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS2_U_R1_VC, GRP_A1_DS2_L_R1_VC );
		pMNBusTieATB->SetInactiveSegment( TB_OFF );

		pMNBusTieBTB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS4_U_R1_VC, GRP_A1_DS4_L_R1_VC );
		pMNBusTieBTB->SetInactiveSegment( TB_OFF );

		pMNBusTieCTB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS6_U_R1_VC, GRP_A1_DS6_L_R1_VC );
		pMNBusTieCTB->SetInactiveSegment( TB_OFF );

		pInvPwr1TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS7_U_R1_VC, GRP_A1_DS7_L_R1_VC );
		pInvPwr1TB->SetInactiveSegment( TB_ON );

		pInvPwr2TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS9_U_R1_VC, GRP_A1_DS9_L_R1_VC );
		pInvPwr2TB->SetInactiveSegment( TB_ON );

		pInvPwr3TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS11_U_R1_VC, GRP_A1_DS11_L_R1_VC );
		pInvPwr3TB->SetInactiveSegment( TB_ON );

		pInvACBus1TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS8_U_R1_VC, GRP_A1_DS8_L_R1_VC );
		pInvACBus1TB->SetInactiveSegment( TB_OFF );

		pInvACBus2TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS10_U_R1_VC, GRP_A1_DS10_L_R1_VC );
		pInvACBus2TB->SetInactiveSegment( TB_OFF );

		pInvACBus3TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS12_U_R1_VC, GRP_A1_DS12_L_R1_VC );
		pInvACBus3TB->SetInactiveSegment( TB_OFF );

		pPayloadPriMNBTB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS15_U_R1_VC, GRP_A1_DS15_L_R1_VC );
		pPayloadPriMNBTB->SetInactiveSegment( TB_OFF );

		pPayloadPriFC3TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS16_U_R1_VC, GRP_A1_DS16_L_R1_VC );
		pPayloadPriFC3TB->SetInactiveSegment( TB_OFF );

		pPayloadPriMNCTB->DefineMeshGroups( GetVCMeshIndex(), GRP_A1_DS17_U_R1_VC, GRP_A1_DS17_L_R1_VC );
		pPayloadPriMNCTB->SetInactiveSegment( TB_OFF );

		pFuelCell1ReacO2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS1_U_R1_VC, GRP_A2_DS1_L_R1_VC );
		pFuelCell1ReacO2->SetInactiveSegment( TB_CL );

		pFuelCell2ReacO2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS9_U_R1_VC, GRP_A2_DS9_L_R1_VC );
		pFuelCell2ReacO2->SetInactiveSegment( TB_CL );

		pFuelCell3ReacO2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS5_U_R1_VC, GRP_A2_DS5_L_R1_VC );
		pFuelCell3ReacO2->SetInactiveSegment( TB_CL );

		pFuelCell1ReacH2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS2_U_R1_VC, GRP_A2_DS2_L_R1_VC );
		pFuelCell1ReacH2->SetInactiveSegment( TB_CL );

		pFuelCell2ReacH2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS10_U_R1_VC, GRP_A2_DS10_L_R1_VC );
		pFuelCell2ReacH2->SetInactiveSegment( TB_CL );

		pFuelCell3ReacH2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS6_U_R1_VC, GRP_A2_DS6_L_R1_VC );
		pFuelCell3ReacH2->SetInactiveSegment( TB_CL );

		pO2ManifoldVlvTank1TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS3_U_R1_VC, GRP_A2_DS3_L_R1_VC );
		pO2ManifoldVlvTank1TB->SetInactiveSegment( TB_CL );

		pO2ManifoldVlvTank2TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS7_U_R1_VC, GRP_A2_DS7_L_R1_VC );
		pO2ManifoldVlvTank2TB->SetInactiveSegment( TB_CL );

		pH2ManifoldVlvTank1TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS4_U_R1_VC, GRP_A2_DS4_L_R1_VC );
		pH2ManifoldVlvTank1TB->SetInactiveSegment( TB_CL );

		pH2ManifoldVlvTank2TB->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS8_U_R1_VC, GRP_A2_DS8_L_R1_VC );
		pH2ManifoldVlvTank2TB->SetInactiveSegment( TB_CL );

		pFuelCellReadyForLoad1->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS11_U_R1_VC, GRP_A2_DS11_L_R1_VC );

		pFuelCellReadyForLoad2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS12_U_R1_VC, GRP_A2_DS12_L_R1_VC );

		pFuelCellReadyForLoad3->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS13_U_R1_VC, GRP_A2_DS13_L_R1_VC );

		pFuelCellCoolantPumpdP1->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS14_U_R1_VC, GRP_A2_DS14_L_R1_VC );

		pFuelCellCoolantPumpdP2->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS15_U_R1_VC, GRP_A2_DS15_L_R1_VC );

		pFuelCellCoolantPumpdP3->DefineMeshGroups( GetVCMeshIndex(), GRP_A2_DS16_U_R1_VC, GRP_A2_DS16_L_R1_VC );
		return;
	}

	void PanelR1::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_R1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R1,
			_V( 1.17636, 2.21861, 14.7453 ) + ofs, _V( 1.50934, 2.20883, 13.8049 ) + ofs,
			_V( 1.12278, 1.88993, 14.66 ) + ofs, _V( 1.42939, 1.87552, 13.8055 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR1::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "PRSD_ValveComands", 16 );
		pO2ManifoldVlvTank1->ConnectPort( 0, pBundle, 0 );
		pO2ManifoldVlvTank1->ConnectPort( 2, pBundle, 1 );
		pO2ManifoldVlvTank2->ConnectPort( 0, pBundle, 2 );
		pO2ManifoldVlvTank2->ConnectPort( 2, pBundle, 3 );
		pH2ManifoldVlvTank1->ConnectPort( 0, pBundle, 4 );
		pH2ManifoldVlvTank1->ConnectPort( 2, pBundle, 5 );
		pH2ManifoldVlvTank2->ConnectPort( 0, pBundle, 6 );
		pH2ManifoldVlvTank2->ConnectPort( 2, pBundle, 7 );

		pFuelCell1Reac->ConnectPort( 0, pBundle, 8 );
		pFuelCell1Reac->ConnectPort( 2, pBundle, 9 );
		pFuelCell2Reac->ConnectPort( 0, pBundle, 10 );
		pFuelCell2Reac->ConnectPort( 2, pBundle, 11 );
		pFuelCell3Reac->ConnectPort( 0, pBundle, 12 );
		pFuelCell3Reac->ConnectPort( 2, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_ValvePositions", 16 );
		pO2ManifoldVlvTank1TB->SetInput( pBundle, 0, TB_OP );
		pO2ManifoldVlvTank2TB->SetInput( pBundle, 1, TB_OP );
		pH2ManifoldVlvTank1TB->SetInput( pBundle, 2, TB_OP );
		pH2ManifoldVlvTank2TB->SetInput( pBundle, 3, TB_OP );

		pFuelCell1ReacO2->SetInput( pBundle, 4, TB_OP );
		pFuelCell2ReacO2->SetInput( pBundle, 5, TB_OP );
		pFuelCell3ReacO2->SetInput( pBundle, 6, TB_OP );
		pFuelCell1ReacH2->SetInput( pBundle, 7, TB_OP );
		pFuelCell2ReacH2->SetInput( pBundle, 8, TB_OP );
		pFuelCell3ReacH2->SetInput( pBundle, 9, TB_OP );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2HeatersA_On", 16 );
		pO2TK1HeatersA->ConnectPort( 0, pBundle, 0 );
		pO2TK2HeatersA->ConnectPort( 0, pBundle, 1 );
		pO2TK3HeatersA->ConnectPort( 0, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2HeatersA_Auto", 16 );
		pO2TK1HeatersA->ConnectPort( 2, pBundle, 0 );
		pO2TK2HeatersA->ConnectPort( 2, pBundle, 1 );
		pO2TK3HeatersA->ConnectPort( 2, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2HeatersB_On", 16 );
		pO2TK1HeatersB->ConnectPort( 0, pBundle, 0 );
		pO2TK2HeatersB->ConnectPort( 0, pBundle, 1 );
		pO2TK3HeatersB->ConnectPort( 0, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2HeatersB_Auto", 16 );
		pO2TK1HeatersB->ConnectPort( 2, pBundle, 0 );
		pO2TK2HeatersB->ConnectPort( 2, pBundle, 1 );
		pO2TK3HeatersB->ConnectPort( 2, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2Heaters_Test", 16 );
		pO2TK1Heaters->ConnectPort( 0, pBundle, 0 );
		pO2TK2Heaters->ConnectPort( 0, pBundle, 1 );
		pO2TK3Heaters->ConnectPort( 0, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2Heaters_Reset", 16 );
		pO2TK1Heaters->ConnectPort( 2, pBundle, 0 );
		pO2TK2Heaters->ConnectPort( 2, pBundle, 1 );
		pO2TK3Heaters->ConnectPort( 2, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_H2HeatersA_On", 16 );
		pH2TK1HeatersA->ConnectPort( 0, pBundle, 0 );
		pH2TK2HeatersA->ConnectPort( 0, pBundle, 1 );
		pH2TK3HeatersA->ConnectPort( 0, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_H2HeatersA_Auto", 16 );
		pH2TK1HeatersA->ConnectPort( 2, pBundle, 0 );
		pH2TK2HeatersA->ConnectPort( 2, pBundle, 1 );
		pH2TK3HeatersA->ConnectPort( 2, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_H2HeatersB_On", 16 );
		pH2TK1HeatersB->ConnectPort( 0, pBundle, 0 );
		pH2TK2HeatersB->ConnectPort( 0, pBundle, 1 );
		pH2TK3HeatersB->ConnectPort( 0, pBundle, 2 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_H2HeatersB_Auto", 16 );
		pH2TK1HeatersB->ConnectPort( 2, pBundle, 0 );
		pH2TK2HeatersB->ConnectPort( 2, pBundle, 1 );
		pH2TK3HeatersB->ConnectPort( 2, pBundle, 2 );

		AtlantisPanel::Realize();
		return;
	}
}
