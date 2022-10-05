/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelO2.h"
#include "StandardSwitch.h"
#include "StandardRotarySwitch.h"
#include "StandardCurvedMechMeter.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o2.h"


namespace vc
{
	PanelO2::PanelO2( Atlantis *_sts ):AtlantisPanel( _sts, "O2" )
	{
		DefineMesh( MESHNAME_PANELO2 );

		Add( pCryoO2HtrAssyTempMeter = new StandardCurvedMechMeter( _sts, "CRYO O2 HTR ASSY TEMP METER" ) );
		Add( pCryoO2PressMeter = new StandardCurvedMechMeter( _sts, "CRYO O2 PRESS METER" ) );
		Add( pCryoO2QtyMeter = new StandardCurvedMechMeter( _sts, "CRYO O2 QTY METER" ) );
		Add( pCryoH2PressMeter = new StandardCurvedMechMeter( _sts, "CRYO H2 PRESS METER" ) );
		Add( pCryoH2QtyMeter = new StandardCurvedMechMeter( _sts, "CRYO H2 QTY METER" ) );
		Add( pFuelCellStackTempMeter = new StandardCurvedMechMeter( _sts, "FUEL CELL STACK TEMP METER" ) );

		Add( pCryoO2HtrAssyTemp = new StandardRotarySwitch( _sts, "CRYO O2 HTR ASSY TEMP", 10, 1 ) );
		pCryoO2HtrAssyTemp->SetLabel( 0, "TK 5 2" );
		pCryoO2HtrAssyTemp->SetLabel( 1, "TK 5 1" );
		pCryoO2HtrAssyTemp->SetLabel( 2, "TK 4 2" );
		pCryoO2HtrAssyTemp->SetLabel( 3, "TK 4 1" );
		pCryoO2HtrAssyTemp->SetLabel( 4, "TK 3 2" );
		pCryoO2HtrAssyTemp->SetLabel( 5, "TK 3 1" );
		pCryoO2HtrAssyTemp->SetLabel( 6, "TK 2 2" );
		pCryoO2HtrAssyTemp->SetLabel( 7, "TK 2 1" );
		pCryoO2HtrAssyTemp->SetLabel( 8, "TK 1 2" );
		pCryoO2HtrAssyTemp->SetLabel( 9, "TK 1 1" );

		Add( pCryoPressQty = new StandardRotarySwitch( _sts, "CRYO PRESS QTY", 5, 4 ) );
		pCryoPressQty->SetLabel( 0, "TK5" );
		pCryoPressQty->SetLabel( 1, "TK4" );
		pCryoPressQty->SetLabel( 2, "TK3" );
		pCryoPressQty->SetLabel( 3, "TK2" );
		pCryoPressQty->SetLabel( 4, "TK1" );

		Add( pFuelCellStackTemp = new StdSwitch3( _sts, "FUEL CELL STACK TEMP" ) );
		pFuelCellStackTemp->SetLabel( 0, "3" );
		pFuelCellStackTemp->SetLabel( 1, "2" );
		pFuelCellStackTemp->SetLabel( 2, "1" );
	}

	PanelO2::~PanelO2()
	{
	}

	void PanelO2::DefineVC( void )
	{
		VECTOR3 switch_rot = _V( 1, 0, 0 );
		VECTOR3 rotary_switch_rot = _V( 0, -0.1984, -0.9801 );
		VECTOR3 needle_ref = _V( 0, 2.952158, 14.59572 );// 0.27m radius
		VECTOR3 needle_rot = _V( 1, 0, 0 );

		AddAIDToMouseEventList( AID_O2 );

		pCryoO2HtrAssyTempMeter->DefineNeedleGroup( GRP_M5_O2_VC );
		pCryoO2HtrAssyTempMeter->SetInitialAnimState( 0.55 );
		pCryoO2HtrAssyTempMeter->SetMotionRange( 12.5 );
		pCryoO2HtrAssyTempMeter->SetReference( needle_ref, needle_rot );

		pCryoO2PressMeter->DefineNeedleGroup( GRP_M6_L_O2_VC );
		pCryoO2PressMeter->SetInitialAnimState( 0.55 );
		pCryoO2PressMeter->SetMotionRange( 15.0 );
		pCryoO2PressMeter->SetReference( needle_ref, needle_rot );

		pCryoO2QtyMeter->DefineNeedleGroup( GRP_M6_R_O2_VC );
		pCryoO2QtyMeter->SetInitialAnimState( 0.55 );
		pCryoO2QtyMeter->SetMotionRange( 15.0 );
		pCryoO2QtyMeter->SetReference( needle_ref, needle_rot );

		pCryoH2PressMeter->DefineNeedleGroup( GRP_M7_L_O2_VC );
		pCryoH2PressMeter->SetInitialAnimState( 0.55 );
		pCryoH2PressMeter->SetMotionRange( 15.0 );
		pCryoH2PressMeter->SetReference( needle_ref, needle_rot );

		pCryoH2QtyMeter->DefineNeedleGroup( GRP_M7_R_O2_VC );
		pCryoH2QtyMeter->SetInitialAnimState( 0.55 );
		pCryoH2QtyMeter->SetMotionRange( 15.0 );
		pCryoH2QtyMeter->SetReference( needle_ref, needle_rot );

		pFuelCellStackTempMeter->DefineNeedleGroup( GRP_M8_O2_VC );
		pFuelCellStackTempMeter->SetInitialAnimState( 0.5 );
		pFuelCellStackTempMeter->SetMotionRange( 15.0 );
		pFuelCellStackTempMeter->SetReference( needle_ref, needle_rot );

		pCryoO2HtrAssyTemp->DefineGroup( GRP_S7_O2_VC );
		pCryoO2HtrAssyTemp->DefineRotationAngle( 270.0f );
		pCryoO2HtrAssyTemp->SetOffset( 45.0f );
		pCryoO2HtrAssyTemp->SetInitialAnimState( 1.0 );
		pCryoO2HtrAssyTemp->SetReference( _V( -0.0746, 2.7949, 14.3503 ), rotary_switch_rot );
		pCryoO2HtrAssyTemp->SetMouseRegion( AID_O2, 0.098072f, 0.698591f, 0.253288f, 0.816324f );

		pCryoPressQty->DefineGroup( GRP_S8_O2_VC );
		pCryoPressQty->DefineRotationAngle( 120.0f );
		pCryoPressQty->SetOffset( 120.0f );
		pCryoPressQty->SetInitialAnimState( 1.0 );
		pCryoPressQty->SetReference( _V( -0.0031, 2.7910, 14.3511 ), rotary_switch_rot );
		pCryoPressQty->SetMouseRegion( AID_O2, 0.397906f, 0.715321f, 0.576245f, 0.827557f );

		pFuelCellStackTemp->DefineGroup( GRP_S9_O2_VC );
		pFuelCellStackTemp->SetInitialAnimState( 0.5 );
		pFuelCellStackTemp->SetReference( _V( 0.0523, 2.7866, 14.3599 ), switch_rot );
		pFuelCellStackTemp->SetMouseRegion( AID_O2, 0.728346f, 0.749182f, 0.823905f, 0.834874f );
		return;
	}

	void PanelO2::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O2,
			_V( -0.1146, 3.0096, 14.3150 ) + ofs, _V( 0.1082, 3.0096, 14.3150 ) + ofs,
			_V( -0.1146, 2.7283, 14.3728 ) + ofs, _V( 0.1082, 2.7283, 14.3728 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO2::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2HtrAssyTemp2", 16 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 9, pBundle, 0 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 7, pBundle, 2 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 5, pBundle, 4 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 3, pBundle, 6 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 1, pBundle, 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2HtrAssyTemp1", 16 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 8, pBundle, 0 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 6, pBundle, 3 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 4, pBundle, 5 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 2, pBundle, 7 );
		pCryoO2HtrAssyTemp->ConnectInputSignal( 0, 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_H2Qty", 16 );
		pCryoPressQty->ConnectInputSignal( 0, 4, pBundle, 0 );
		pCryoPressQty->ConnectInputSignal( 0, 3, pBundle, 1 );
		pCryoPressQty->ConnectInputSignal( 0, 2, pBundle, 2 );
		pCryoPressQty->ConnectInputSignal( 0, 1, pBundle, 3 );
		pCryoPressQty->ConnectInputSignal( 0, 0, pBundle, 4 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_H2Press", 16 );
		pCryoPressQty->ConnectInputSignal( 1, 4, pBundle, 0 );
		pCryoPressQty->ConnectInputSignal( 1, 3, pBundle, 1 );
		pCryoPressQty->ConnectInputSignal( 1, 2, pBundle, 2 );
		pCryoPressQty->ConnectInputSignal( 1, 1, pBundle, 3 );
		pCryoPressQty->ConnectInputSignal( 1, 0, pBundle, 4 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2Qty", 16 );
		pCryoPressQty->ConnectInputSignal( 2, 4, pBundle, 0 );
		pCryoPressQty->ConnectInputSignal( 2, 3, pBundle, 1 );
		pCryoPressQty->ConnectInputSignal( 2, 2, pBundle, 2 );
		pCryoPressQty->ConnectInputSignal( 2, 1, pBundle, 3 );
		pCryoPressQty->ConnectInputSignal( 2, 0, pBundle, 4 );

		pBundle = STS()->BundleManager()->CreateBundle( "PRSD_O2Press", 16 );
		pCryoPressQty->ConnectInputSignal( 3, 4, pBundle, 0 );
		pCryoPressQty->ConnectInputSignal( 3, 3, pBundle, 1 );
		pCryoPressQty->ConnectInputSignal( 3, 2, pBundle, 2 );
		pCryoPressQty->ConnectInputSignal( 3, 1, pBundle, 3 );
		pCryoPressQty->ConnectInputSignal( 3, 0, pBundle, 4 );

		pBundle = STS()->BundleManager()->CreateBundle( "PanelO2", 16 );
		pFuelCellStackTemp->ConnectPort( 0, pBundle, 0 );
		pFuelCellStackTemp->ConnectPort( 2, pBundle, 1 );
		pFuelCellStackTemp3.Connect( pBundle, 0 );
		pFuelCellStackTemp1.Connect( pBundle, 1 );

		pCryoO2HtrAssyTemp->ConnectOutputSignal( 0, pBundle, 2 );
		pCryoO2HtrAssyTempMeter->SetInput( pBundle, 2 );

		pCryoPressQty->ConnectOutputSignal( 3, pBundle, 3 );
		pCryoO2PressMeter->SetInput( pBundle, 3 );

		pCryoPressQty->ConnectOutputSignal( 2, pBundle, 4 );
		pCryoO2QtyMeter->SetInput( pBundle, 4 );

		pCryoPressQty->ConnectOutputSignal( 1, pBundle, 5 );
		pCryoH2PressMeter->SetInput( pBundle, 5 );

		pCryoPressQty->ConnectOutputSignal( 0, pBundle, 6 );
		pCryoH2QtyMeter->SetInput( pBundle, 6 );

		pFuelCellStackTempMeter->SetInput( pBundle, 7 );
		pFuelCellStackTempMeterInput.Connect( pBundle, 7 );

		AtlantisPanel::Realize();
		return;
	}

	void PanelO2::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		// TODO sensor value conversion to meter range

		if (pFuelCellStackTemp1.IsSet())
		{
			// FC 1
			pFuelCellStackTempMeterInput.SetLine( 1.25f );
		}
		else if (pFuelCellStackTemp3.IsSet())
		{
			// FC 3
			pFuelCellStackTempMeterInput.SetLine( 3.75f );
		}
		else
		{
			// FC 2
			pFuelCellStackTempMeterInput.SetLine( 2.5f );
		}
		return;
	}
}
