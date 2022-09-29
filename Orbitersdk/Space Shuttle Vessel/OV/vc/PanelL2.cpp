/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/06/06   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelL2.h"
#include "StandardSwitch.h"
#include "vc_defs.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "../meshres_vc_l2.h"


namespace vc
{
	PanelL2::PanelL2( Atlantis* _sts ):AtlantisPanel( _sts, "L2" )
	{
		DefineMesh( MESHNAME_PANELL2 );

		Add( pAntiSkid = new StdSwitch2( _sts, "ANTISKID" ) );
		pAntiSkid->SetLabel( 0, "OFF" );
		pAntiSkid->SetLabel( 1, "ON" );

		Add( pNoseWheelSteering = new StdSwitch3( _sts, "NOSE WHEEL STEERING" ) );
		pNoseWheelSteering->SetLabel( 0, "OFF" );
		pNoseWheelSteering->SetLabel( 1, "1" );
		pNoseWheelSteering->SetLabel( 2, "2" );

		Add( pBodyFlap = new LockableLever3( _sts, "BODY FLAP" ) );
		pBodyFlap->SetLabel( 0, "DOWN" );
		pBodyFlap->SetLabel( 1, "AUTO/OFF" );
		pBodyFlap->SetLabel( 2, "UP" );

		Add( pEntryMode = new LockableLever3( _sts, "ENTRY MODE" ) );
		pEntryMode->SetLabel( 0, "NO Y JET" );
		pEntryMode->SetLabel( 1, "LO GAIN" );
		pEntryMode->SetLabel( 2, "AUTO" );
		pEntryMode->SetInitialPosition( 2 );

		Add( pPitchTrim = new StdSwitch3( _sts, "PITCH TRIM" ) );
		pPitchTrim->SetLabel( 0, "DOWN" );
		pPitchTrim->SetLabel( 2, "UP" );

		Add( pRollTrim = new StdSwitch3( _sts, "ROLL TRIM" ) );
		pRollTrim->SetLabel( 0, "L" );
		pRollTrim->SetLabel( 2, "R" );

		Add( pYawTrim = new StdSwitch3( _sts, "YAW TRIM" ) );
		pYawTrim->SetLabel( 0, "L" );
		pYawTrim->SetLabel( 2, "R" );
	}

	PanelL2::~PanelL2()
	{
	}

	void PanelL2::DefineVC()
	{
		const VECTOR3 switch_rot = _V( 0.958, -0.2826, 0.0471 );
		const VECTOR3 switch_rotV = _V( 0.008441, 0.1735, 0.9848 );
		const VECTOR3 pull_dir = _V( 0.2821, 0.9435, -0.17404 );

		AddAIDToMouseEventList( AID_L2_TOP );
		AddAIDToMouseEventList( AID_L2_MID );
		AddAIDToMouseEventList( AID_L2_BOT );

		pAntiSkid->SetInitialAnimState( 0.5f );
		pAntiSkid->DefineGroup( GRP_S5_L2_VC );
		pAntiSkid->SetReference( _V( -1.2146, 1.86544, 14.2621 ), switch_rot );
		pAntiSkid->SetMouseRegion( AID_L2_MID, 0.158305f, 0.537474f, 0.339768f, 0.643991f );

		pNoseWheelSteering->DefineGroup( GRP_S6_L2_VC );
		pNoseWheelSteering->SetInitialAnimState( 0.5f );
		pNoseWheelSteering->SetReference( _V( -1.16436, 1.84826, 14.2628 ), switch_rot );
		pNoseWheelSteering->SetMouseRegion( AID_L2_MID, 0.470647f, 0.548667f, 0.642366f, 0.654416f );

		pBodyFlap->SetMouseRegion( AID_L2_MID, 0.770593f, 0.561757f, 0.939368f, 0.663765f );
		pBodyFlap->SetReference( _V( -1.11938, 1.83673, 14.2634 ), switch_rot );
		pBodyFlap->SetPullDirection( pull_dir );
		pBodyFlap->DefineGroup( GRP_S7_L2_VC );
		pBodyFlap->SetInitialAnimState( 0.5f );
		pBodyFlap->SetSpringLoaded( true, 0 );
		pBodyFlap->SetSpringLoaded( true, 2 );

		pEntryMode->SetMouseRegion( AID_L2_MID, 0.194711f, 0.826458f, 0.361584f, 0.921627f );
		pEntryMode->SetReference( _V( -1.2188, 1.85775, 14.199 ), switch_rot );
		pEntryMode->SetPullDirection( pull_dir );
		pEntryMode->DefineGroup( GRP_S25_L2_VC );
		pEntryMode->SetInitialAnimState( 0.5f );

		pPitchTrim->DefineGroup( GRP_S9_L2_VC );
		pPitchTrim->SetInitialAnimState( 0.5f );
		pPitchTrim->SetReference( _V( -1.12473, 1.8308, 14.2004 ), switch_rot );
		pPitchTrim->SetMouseRegion( AID_L2_MID, 0.835611f, 0.849526f, 0.999024f, 0.946449f );
		pPitchTrim->SetSpringLoaded( true, 0 );
		pPitchTrim->SetSpringLoaded( true, 2 );

		pRollTrim->DefineGroup( GRP_S8_L2_VC );
		pRollTrim->SetInitialAnimState( 0.5f );
		pRollTrim->SetReference( _V( -1.1648, 1.84224, 14.195 ), switch_rotV );
		pRollTrim->SetMouseRegion( AID_L2_MID, 0.532553f, 0.828619f, 0.685502f, 0.943098f );
		pRollTrim->SetOrientation( true );
		pRollTrim->SetSpringLoaded( true, 0 );
		pRollTrim->SetSpringLoaded( true, 2 );

		pYawTrim->DefineGroup( GRP_S10_L2_VC );
		pYawTrim->SetInitialAnimState( 0.5f );
		pYawTrim->SetReference( _V( -1.07625, 1.80121, 14.0754 ), switch_rotV );
		pYawTrim->SetMouseRegion( AID_L2_BOT, 0.677954f, 0.110878f, 0.733693f, 0.207377f );
		pYawTrim->SetOrientation( true );
		pYawTrim->SetSpringLoaded( true, 0 );
		pYawTrim->SetSpringLoaded( true, 2 );
		return;
	}

	void PanelL2::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_L2_TOP, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L2_TOP,
			_V( -1.15355, 1.88576, 14.5684 ) + ofs, _V( -0.991701, 1.84031, 14.5764 ) + ofs,
			_V( -1.15354, 1.86985, 14.4447 ) + ofs, _V( -0.99153, 1.82334, 14.4479 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCRegisterArea( AID_L2_MID, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L2_MID,
			_V( -1.22753, 1.88481, 14.3921 ) + ofs, _V( -1.077, 1.84193, 14.4016 ) + ofs,
			_V( -1.26024, 1.86572, 14.1689 ) + ofs, _V( -1.07717, 1.81233, 14.1716 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCRegisterArea( AID_L2_BOT, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L2_BOT,
			_V( -1.33256, 1.87894, 14.1066 ) + ofs, _V( -0.968126, 1.77295, 14.1155 ) + ofs,
			_V( -1.34025, 1.84649, 13.8381 ) + ofs, _V( -0.969675, 1.7367, 13.8375 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelL2::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		if (dipTrimPanelOn)
		{
			// on
			if (dipUpPitchTrim) dopUpPitchTrim.SetLine();
			else dopUpPitchTrim.ResetLine();

			if (dipDownPitchTrim) dopDownPitchTrim.SetLine();
			else dopDownPitchTrim.ResetLine();

			if (dipRightRollTrim) dopRightRollTrim.SetLine();
			else dopRightRollTrim.ResetLine();

			if (dipLeftRollTrim) dopLeftRollTrim.SetLine();
			else dopLeftRollTrim.ResetLine();

			if (dipRightYawTrim) dopRightYawTrim.SetLine();
			else dopRightYawTrim.ResetLine();

			if (dipLeftYawTrim) dopLeftYawTrim.SetLine();
			else dopLeftYawTrim.ResetLine();
		}
		else
		{
			// off
			dopUpPitchTrim.ResetLine();
			dopDownPitchTrim.ResetLine();
			dopRightRollTrim.ResetLine();
			dopLeftRollTrim.ResetLine();
			dopRightYawTrim.ResetLine();
			dopLeftYawTrim.ResetLine();
		}
		return;
	}

	void PanelL2::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "CDR_TRIM_BF_EM", 16 );
		// 0: F3 CDR TRIM RHC/PNL inh
		dipTrimPanelOn.Connect( pBundle, 1 );// 1: F3 CDR TRIM PANEL on
		dopUpPitchTrim.Connect( pBundle, 2 );// 2: L2 CDR PITCH TRIM up
		dopDownPitchTrim.Connect( pBundle, 3 );// 3: L2 CDR PITCH TRIM down
		dopRightRollTrim.Connect( pBundle, 4 );// 4: L2 CDR ROLL TRIM right
		dopLeftRollTrim.Connect( pBundle, 5 );// 5: L2 CDR ROLL TRIM left
		dopRightYawTrim.Connect( pBundle, 6 );// 6: L2 CDR YAW TRIM right
		dopLeftYawTrim.Connect( pBundle, 7 );// 7: L2 CDR YAW TRIM left
		pBodyFlap->ConnectPort( 0, pBundle, 8 );// 8: L2 CDR BODY FLAP down
		pBodyFlap->ConnectPort( 2, pBundle, 9 );// 9: L2 CDR BODY FLAP up
		pEntryMode->ConnectPort( 0, pBundle, 10 );// 10: L2 ENTRY MODE no y jet
		pEntryMode->ConnectPort( 1, pBundle, 11 );// 11: L2 ENTRY MODE lo gain

		pBundle = STS()->BundleManager()->CreateBundle( "BRAKES", 16 );
		pAntiSkid->ConnectPort( 1, pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "NWS", 16 );
		pNoseWheelSteering->ConnectPort( 1, pBundle, 2 );
		pNoseWheelSteering->ConnectPort( 2, pBundle, 3 );

		DiscreteBundle* pBundleL2 = STS()->BundleManager()->CreateBundle( "L2_INTERNAL", 16 );
		pPitchTrim->ConnectPort( 0, pBundleL2, 6 );
		pPitchTrim->ConnectPort( 2, pBundleL2, 7 );
		pRollTrim->ConnectPort( 0, pBundleL2, 8 );
		pRollTrim->ConnectPort( 2, pBundleL2, 9 );
		pYawTrim->ConnectPort( 0, pBundleL2, 10 );
		pYawTrim->ConnectPort( 2, pBundleL2, 11 );
		dipUpPitchTrim.Connect( pBundleL2, 6 );
		dipDownPitchTrim.Connect( pBundleL2, 7 );
		dipRightRollTrim.Connect( pBundleL2, 8 );
		dipLeftRollTrim.Connect( pBundleL2, 9 );
		dipRightYawTrim.Connect( pBundleL2, 10 );
		dipLeftYawTrim.Connect( pBundleL2, 11 );

		AtlantisPanel::Realize();
		return;
	}
};