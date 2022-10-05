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
#include "PanelO3.h"
#include "StandardSwitch.h"
#include "StandardRotarySwitch.h"
#include "7SegDisp_RCSOMS_PRPLT_QTY.h"
#include "7SegDisp_MissionTime.h"
#include "StandardCurvedMechMeter.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o3.h"


namespace vc
{
	PanelO3::PanelO3( Atlantis *_sts ):AtlantisPanel( _sts, "O3" )
	{
		DefineMesh( MESHNAME_PANELO3 );

		Add( pRCSOMS_PRESS = new RotaryDemuxSwitch( _sts, "RCS/OMS/PRESS", 3 ) );
		pRCSOMS_PRESS->SetLabel( 0, "OMS PRPLT" );
		pRCSOMS_PRESS->SetLabel( 1, "RCS PRPLT" );
		pRCSOMS_PRESS->SetLabel( 2, "RCS He X10" );

		Add( pRCSOMS_PRPLTQTY = new RotaryDemuxSwitch( _sts, "RCS/OMS PRPLT QTY", 5 ) );
		pRCSOMS_PRPLTQTY->SetLabel( 0, "OMS FUEL" );
		pRCSOMS_PRPLTQTY->SetLabel( 1, "OMS OXID" );
		pRCSOMS_PRPLTQTY->SetLabel( 2, "LOWEST" );
		pRCSOMS_PRPLTQTY->SetLabel( 3, "RCS FUEL" );
		pRCSOMS_PRPLTQTY->SetLabel( 4, "RCS OXID" );

		Add( pMissionTimer = new StdSwitch3( _sts, "MISSION TIMER" ) );
		pMissionTimer->SetLabel( 0, "TEST" );
		pMissionTimer->SetLabel( 1, "MET" );
		pMissionTimer->SetLabel( 2, "GMT" );

		Add( pRCSOMS_PRPLT_QTY = new _7SegDisp_RCSOMS_PRPLT_QTY( _sts, "RCS/OMS PRPLT QTY" ) );
		Add( pMissionTime = new _7SegDisp_MissionTime( _sts, "MISSION TIME" ) );

		Add( pRCSOMSPressLeftOxidMeter = new StandardCurvedMechMeter( _sts, "RCS/OMS/PRESS LEFT OXID METER" ) );
		Add( pRCSOMSPressLeftFuelMeter = new StandardCurvedMechMeter( _sts, "RCS/OMS/PRESS LEFT FUEL METER" ) );
		Add( pRCSOMSPressFwdKitOxidMeter = new StandardCurvedMechMeter( _sts, "RCS/OMS/PRESS FWD/KIT OXID METER" ) );
		Add( pRCSOMSPressFwdKitFuelMeter = new StandardCurvedMechMeter( _sts, "RCS/OMS/PRESS FWD/KIT FUEL METER" ) );
		Add( pRCSOMSPressRightOxidMeter = new StandardCurvedMechMeter( _sts, "RCS/OMS/PRESS RIGHT OXID METER" ) );
		Add( pRCSOMSPressRightFuelMeter = new StandardCurvedMechMeter( _sts, "RCS/OMS/PRESS RIGHT FUEL METER" ) );
	}

	PanelO3::~PanelO3()
	{
	}

	void PanelO3::DefineVC()
	{
		VECTOR3 switch_rot = _V( 1, 0, 0 );
		VECTOR3 rotary_switch_rot = _V( 0, -0.1984, -0.9801 );
		VECTOR3 needle_ref = _V( 0, 2.952158, 14.59572 );// 0.27m radius
		VECTOR3 needle_rot = _V( 1, 0, 0 );

		AddAIDToMouseEventList( AID_O3 );

		pRCSOMS_PRESS->DefineGroup( GRP_S10_O3_VC );
		pRCSOMS_PRESS->DefineRotationAngle( 64.0f );
		pRCSOMS_PRESS->SetOffset( 148.0f );
		pRCSOMS_PRESS->SetInitialAnimState( 0.0f );
		pRCSOMS_PRESS->SetReference( _V( 0.2147, 2.7921, 14.3509 ), rotary_switch_rot );
		pRCSOMS_PRESS->SetMouseRegion( AID_O3, 0.142551f, 0.704583f, 0.202544f, 0.829816f );

		pRCSOMS_PRPLTQTY->DefineGroup( GRP_S11_O3_VC );
		pRCSOMS_PRPLTQTY->DefineRotationAngle( 130.0f );
		pRCSOMS_PRPLTQTY->SetOffset( 115.0f );
		pRCSOMS_PRPLTQTY->SetInitialAnimState( 0.25f );
		pRCSOMS_PRPLTQTY->SetReference( _V( 0.3653, 2.7950, 14.3503 ), rotary_switch_rot );
		pRCSOMS_PRPLTQTY->SetMouseRegion( AID_O3, 0.398181f, 0.692892f, 0.454926f, 0.814155f );

		pMissionTimer->DefineGroup( GRP_S12_O3_VC );
		pMissionTimer->SetInitialAnimState( 0.5f );
		pMissionTimer->SetReference( _V( 0.5121638,  2.799416,  14.35993 ), switch_rot );
		pMissionTimer->SetMouseRegion( AID_O3, 0.655579f, 0.695221f, 0.687731f, 0.794568f );
		pMissionTimer->SetSpringLoaded( true, 0 );

		pRCSOMS_PRPLT_QTY->DefineMesh( GetVCMeshIndex() );
		pRCSOMS_PRPLT_QTY->DefineComponent( GRP_M12_1_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pRCSOMS_PRPLT_QTY->DefineComponent( GRP_M12_2_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pRCSOMS_PRPLT_QTY->DefineComponent( GRP_M12_3_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pRCSOMS_PRPLT_QTY->DefineComponent( GRP_M12_4_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pRCSOMS_PRPLT_QTY->DefineComponent( GRP_M12_5_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pRCSOMS_PRPLT_QTY->DefineComponent( GRP_M12_6_O3_VC, true, false, false, _7SD_STATE_NUM0 );

		pMissionTime->DefineMesh( GetVCMeshIndex() );
		pMissionTime->DefineComponent( GRP_M13_1_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_2_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_3_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_4_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_5_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_6_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_7_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_8_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->DefineComponent( GRP_M13_9_O3_VC, true, false, false, _7SD_STATE_NUM0 );
		pMissionTime->SetLocation( true );

		pRCSOMSPressLeftOxidMeter->DefineNeedleGroup( GRP_M9_L_O3_VC );
		pRCSOMSPressLeftOxidMeter->SetInitialAnimState( 0.55 );
		pRCSOMSPressLeftOxidMeter->SetMotionRange( 15.0 );
		pRCSOMSPressLeftOxidMeter->SetReference( needle_ref, needle_rot );

		pRCSOMSPressLeftFuelMeter->DefineNeedleGroup( GRP_M9_R_O3_VC );
		pRCSOMSPressLeftFuelMeter->SetInitialAnimState( 0.55 );
		pRCSOMSPressLeftFuelMeter->SetMotionRange( 15.0 );
		pRCSOMSPressLeftFuelMeter->SetReference( needle_ref, needle_rot );

		pRCSOMSPressFwdKitOxidMeter->DefineNeedleGroup( GRP_M10_L_O3_VC );
		pRCSOMSPressFwdKitOxidMeter->SetInitialAnimState( 0.55 );
		pRCSOMSPressFwdKitOxidMeter->SetMotionRange( 15.0 );
		pRCSOMSPressFwdKitOxidMeter->SetReference( needle_ref, needle_rot );

		pRCSOMSPressFwdKitFuelMeter->DefineNeedleGroup( GRP_M10_R_O3_VC );
		pRCSOMSPressFwdKitFuelMeter->SetInitialAnimState( 0.55 );
		pRCSOMSPressFwdKitFuelMeter->SetMotionRange( 15.0 );
		pRCSOMSPressFwdKitFuelMeter->SetReference( needle_ref, needle_rot );

		pRCSOMSPressRightOxidMeter->DefineNeedleGroup( GRP_M11_L_O3_VC );
		pRCSOMSPressRightOxidMeter->SetInitialAnimState( 0.55 );
		pRCSOMSPressRightOxidMeter->SetMotionRange( 15.0 );
		pRCSOMSPressRightOxidMeter->SetReference( needle_ref, needle_rot );

		pRCSOMSPressRightFuelMeter->DefineNeedleGroup( GRP_M11_R_O3_VC );
		pRCSOMSPressRightFuelMeter->SetInitialAnimState( 0.55 );
		pRCSOMSPressRightFuelMeter->SetMotionRange( 15.0 );
		pRCSOMSPressRightFuelMeter->SetReference( needle_ref, needle_rot );
		return;
	}

	void PanelO3::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O3,
			_V( 0.110078, 3.0096, 14.3151 ) + ofs, _V( 0.713058, 3.0096, 14.3151 ) + ofs,
			_V( 0.110078, 2.72832, 14.3729 ) + ofs , _V( 0.713058, 2.72832, 14.3729 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO3::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "O3_Timer_OMSRCS", 16 );
		pMissionTimer->ConnectPort( 0, pBundle, 0 );
		pMissionTimer->ConnectPort( 2, pBundle, 1 );
		pRCSOMS_PRPLTQTY->ConnectOutputSignal( 0, pBundle, 2 );
		pRCSOMS_PRPLTQTY->ConnectOutputSignal( 1, pBundle, 3 );
		pRCSOMS_PRPLTQTY->ConnectOutputSignal( 2, pBundle, 4 );
		pRCSOMS_PRPLTQTY->ConnectOutputSignal( 3, pBundle, 5 );
		pRCSOMS_PRPLTQTY->ConnectOutputSignal( 4, pBundle, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "PanelO3", 16 );
		pRCSOMS_PRESS->ConnectOutputSignal( 0, pBundle, 0 );
		pRCSOMS_PRESS->ConnectOutputSignal( 1, pBundle, 1 );
		pRCSOMS_PRESS->ConnectOutputSignal( 2, pBundle, 2 );
		pRCSOMS_PRESS_OMSPRPLT.Connect( pBundle, 0 );
		pRCSOMS_PRESS_RCSPRPLT.Connect( pBundle, 1 );
		pRCSOMS_PRESS_RCSHeX10.Connect( pBundle, 2 );

		pRCSOMSPressLeftOxidMeter->SetInput( pBundle, 3 );
		pRCSOMSPressLeftFuelMeter->SetInput( pBundle, 4 );
		pRCSOMSPressFwdKitOxidMeter->SetInput( pBundle, 5 );
		pRCSOMSPressFwdKitFuelMeter->SetInput( pBundle, 6 );
		pRCSOMSPressRightOxidMeter->SetInput( pBundle, 7 );
		pRCSOMSPressRightFuelMeter->SetInput( pBundle, 8 );
		pRCSOMSPressLeftOxidMeterInput.Connect( pBundle, 3 );
		pRCSOMSPressLeftFuelMeterInput.Connect( pBundle, 4 );
		pRCSOMSPressFwdKitOxidMeterInput.Connect( pBundle, 5 );
		pRCSOMSPressFwdKitFuelMeterInput.Connect( pBundle, 6 );
		pRCSOMSPressRightOxidMeterInput.Connect( pBundle, 7 );
		pRCSOMSPressRightFuelMeterInput.Connect( pBundle, 8 );

		AtlantisPanel::Realize();
		return;
	}

	void PanelO3::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		// TODO sensor value conversion to meter range

		if (pRCSOMS_PRESS_OMSPRPLT.IsSet())
		{
			// OMS PRPLT
			pRCSOMSPressLeftOxidMeterInput.SetLine( 1.0f );
			pRCSOMSPressLeftFuelMeterInput.SetLine( 2.0f );
			pRCSOMSPressFwdKitOxidMeterInput.SetLine( 3.0f );
			pRCSOMSPressFwdKitFuelMeterInput.SetLine( 4.0f );
			pRCSOMSPressRightOxidMeterInput.SetLine( 0.0f );
			pRCSOMSPressRightFuelMeterInput.SetLine( 5.0f );
		}
		else if (pRCSOMS_PRESS_RCSPRPLT.IsSet())
		{
			// RCS PRPLT
			pRCSOMSPressLeftOxidMeterInput.SetLine( 2.0f );
			pRCSOMSPressLeftFuelMeterInput.SetLine( 3.0f );
			pRCSOMSPressFwdKitOxidMeterInput.SetLine( 0.0f );
			pRCSOMSPressFwdKitFuelMeterInput.SetLine( 5.0f );
			pRCSOMSPressRightOxidMeterInput.SetLine( 4.0f );
			pRCSOMSPressRightFuelMeterInput.SetLine( 1.0f );
		}
		else //if (pRCSOMS_PRESS_RCSHeX10.IsSet())
		{
			// RCS He X10
			pRCSOMSPressLeftOxidMeterInput.SetLine( 0.0f );
			pRCSOMSPressLeftFuelMeterInput.SetLine( 5.0f );
			pRCSOMSPressFwdKitOxidMeterInput.SetLine( 1.0f );
			pRCSOMSPressFwdKitFuelMeterInput.SetLine( 2.0f );
			pRCSOMSPressRightOxidMeterInput.SetLine( 3.0f );
			pRCSOMSPressRightFuelMeterInput.SetLine( 4.0f );
		}
		return;
	}
}
