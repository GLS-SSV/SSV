/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/01   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/09   GLS
********************************************/
#include "OMS.h"
#include <MotorValve.h>
#include <SolenoidValve.h>
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include <cassert>


namespace oms
{
	OMS::OMS( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID ):AtlantisSubsystem( _director, _ident )
	{
		assert( (ID <= 1) && "OMS::OMS.ID" );
		this->ID = ID;

		ChamberPressure = Sensor( 0.0, 160.0 );
		N2TankPressure1 = Sensor( 0.0, 5000.0 );
		N2TankPressure2 = Sensor( 0.0, 5000.0 );
		HeTankPressure1 = Sensor( 0.0, 5000.0 );
		HeTankPressure2 = Sensor( 0.0, 5000.0 );
		
		source = 0;

		vman.AddValve( OMSHeliumIsolationAVlv = new SolenoidValve_2( "OMS Helium Isolation A", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSHeliumIsolationBVlv = new SolenoidValve_2( "OMS Helium Isolation B", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSVaporIsolation1Vlv = new SolenoidValve_2( "OMS Vapor Isolation 1", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSVaporIsolation2Vlv = new SolenoidValve_2( "OMS Vapor Isolation 2", 0.0, 1000.0, true, nullptr, nullptr ) );

		vman.AddValve( OMSFuelTankIsolationAVlv = new MotorValve( "OMS Fuel Tank Isolation A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( OMSOxidTankIsolationAVlv = new MotorValve( "OMS Oxid Tank Isolation A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( OMSFuelTankIsolationBVlv = new MotorValve( "OMS Fuel Tank Isolation B", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( OMSOxidTankIsolationBVlv = new MotorValve( "OMS Oxid Tank Isolation B", 0.0, 100.0, nullptr, nullptr ) );

		vman.AddValve( OMSFuelCrossfeedAVlv = new MotorValve( "OMS Fuel Crossfeed A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( OMSOxidCrossfeedAVlv = new MotorValve( "OMS Oxid Crossfeed A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( OMSFuelCrossfeedBVlv = new MotorValve( "OMS Fuel Crossfeed B", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( OMSOxidCrossfeedBVlv = new MotorValve( "OMS Oxid Crossfeed B", 0.0, 100.0, nullptr, nullptr ) );

		vman.AddValve( OMSEnginePressureVlv = new SolenoidValve_2( "OMS Engine Pressure", 0.0, 1000.0, true, nullptr, nullptr ) );
		//vman.AddValve( OMSEngineN2Vlv = new SolenoidValve_2( "OMS Engine N2", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSEngineControl1Vlv = new SolenoidValve_2( "OMS Engine Control 1", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSEngineControl2Vlv = new SolenoidValve_2( "OMS Engine Control 2", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSEnginePurge1Vlv = new SolenoidValve_2( "OMS Engine Purge 1", 0.0, 1000.0, true, nullptr, nullptr ) );
		vman.AddValve( OMSEnginePurge2Vlv = new SolenoidValve_2( "OMS Engine Purge 2", 0.0, 1000.0, true, nullptr, nullptr ) );
		return;
	}

	OMS::~OMS( void )
	{
	}

	void OMS::Realize( void )
	{
		DiscreteBundle* pBundle;
		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_HE_VAPOR_ISOL_A", 8 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_HE_VAPOR_ISOL_A", 8 );
		OMSHeliumIsolationAVlv->ConnectInput( 0, pBundle, 0 );
		OMSHeliumIsolationAVlv->ConnectPositionSensor( 0, true, pBundle, 1 );
		OMSHeliumIsolationBVlv->ConnectInput( 0, pBundle, 2 );
		OMSHeliumIsolationBVlv->ConnectPositionSensor( 0, true, pBundle, 3 );
		OMSVaporIsolation1Vlv->ConnectInput( 0, pBundle, 4 );
		OMSVaporIsolation1Vlv->ConnectPositionSensor( 0, true, pBundle, 5 );
		OMSVaporIsolation2Vlv->ConnectInput( 0, pBundle, 6 );
		OMSVaporIsolation2Vlv->ConnectPositionSensor( 0, true, pBundle, 7 );
		OMS_HE_ISOV_A_POWER_OP.Connect( pBundle, 0 );
		OMS_HE_ISOV_B_POWER_OP.Connect( pBundle, 2 );
		OMS_VAP_ISOV_1_POWER_OP.Connect( pBundle, 4 );
		OMS_VAP_ISOV_2_POWER_OP.Connect( pBundle, 6 );
		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_TANK_ISOL_A", 10 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_TANK_ISOL_A", 10 );
		OMSFuelTankIsolationAVlv->ConnectInput( pBundle, 0 );
		OMSOxidTankIsolationAVlv->ConnectInput( pBundle, 1 );
		OMSFuelTankIsolationAVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		OMSFuelTankIsolationAVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		OMSFuelTankIsolationAVlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		OMSFuelTankIsolationAVlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		OMSOxidTankIsolationAVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		OMSOxidTankIsolationAVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		OMSOxidTankIsolationAVlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		OMSOxidTankIsolationAVlv->ConnectPositionSensor( 1, false, pBundle, 9 );

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_TANK_ISOL_B", 10 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_TANK_ISOL_B", 10 );
		OMSFuelTankIsolationBVlv->ConnectInput( pBundle, 0 );
		OMSOxidTankIsolationBVlv->ConnectInput( pBundle, 1 );
		OMSFuelTankIsolationBVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		OMSFuelTankIsolationBVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		OMSFuelTankIsolationBVlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		OMSFuelTankIsolationBVlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		OMSOxidTankIsolationBVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		OMSOxidTankIsolationBVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		OMSOxidTankIsolationBVlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		OMSOxidTankIsolationBVlv->ConnectPositionSensor( 1, false, pBundle, 9 );

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_XFD_A", 10 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_XFD_A", 10 );
		OMSFuelCrossfeedAVlv->ConnectInput( pBundle, 0 );
		OMSOxidCrossfeedAVlv->ConnectInput( pBundle, 1 );
		OMSFuelCrossfeedAVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		OMSFuelCrossfeedAVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		OMSFuelCrossfeedAVlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		OMSFuelCrossfeedAVlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		OMSOxidCrossfeedAVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		OMSOxidCrossfeedAVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		OMSOxidCrossfeedAVlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		OMSOxidCrossfeedAVlv->ConnectPositionSensor( 1, false, pBundle, 9 );

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_XFD_B", 10 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_XFD_B", 10 );
		OMSFuelCrossfeedBVlv->ConnectInput( pBundle, 0 );
		OMSOxidCrossfeedBVlv->ConnectInput( pBundle, 1 );
		OMSFuelCrossfeedBVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		OMSFuelCrossfeedBVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		OMSFuelCrossfeedBVlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		OMSFuelCrossfeedBVlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		OMSOxidCrossfeedBVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		OMSOxidCrossfeedBVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		OMSOxidCrossfeedBVlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		OMSOxidCrossfeedBVlv->ConnectPositionSensor( 1, false, pBundle, 9 );

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_ENGINE", 16 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_ENGINE", 16 );
		OMSEnginePressureVlv->ConnectInput( 0, pBundle, 0 );
		OMSEnginePressureVlv->ConnectInput( 1, pBundle, 1 );
		OMSEnginePressureVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		//OMSEngineN2Vlv->ConnectInput( 0, pBundle, 3 );
		OMSEngineControl1Vlv->ConnectInput( 0, pBundle, 4 );
		OMSEngineControl1Vlv->ConnectInput( 1, pBundle, 5 );
		OMSEngineControl1Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		OMSEngineControl2Vlv->ConnectInput( 0, pBundle, 7 );
		OMSEngineControl2Vlv->ConnectInput( 1, pBundle, 8 );
		OMSEngineControl2Vlv->ConnectPositionSensor( 0, true, pBundle, 9 );
		OMSEngineBipropellent1OPVlv.Connect( pBundle, 10 );
		OMSEngineBipropellent2OPVlv.Connect( pBundle, 11 );
		OMSEnginePurge1Vlv->ConnectInput( 0, pBundle, 12 );
		OMSEnginePurge1Vlv->ConnectPositionSensor( 0, true, pBundle, 13 );
		OMSEnginePurge2Vlv->ConnectInput( 0, pBundle, 14 );
		OMSEnginePurge2Vlv->ConnectPositionSensor( 0, true, pBundle, 15 );
		OMS_ENG_PRESS_V_POWER_OP_1.Connect( pBundle, 0 );
		OMS_ENG_PRESS_V_POWER_OP_2.Connect( pBundle, 1 );
		OMS_ENG_CNT_V1_POWER_OP_1.Connect( pBundle, 4 );
		OMS_ENG_CNT_V1_POWER_OP_2.Connect( pBundle, 5 );
		OMS_ENG_CNT_V2_POWER_OP_1.Connect( pBundle, 7 );
		OMS_ENG_CNT_V2_POWER_OP_2.Connect( pBundle, 8 );

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LeftOMS_DC", 16 );
		else pBundle = BundleManager()->CreateBundle( "RightOMS_DC", 16 );
		OMS_HEPRESS_VAPORISOL_A_SW_OPEN.Connect( pBundle, 0 );
		OMS_HEPRESS_VAPORISOL_A_SW_CLOSE.Connect( pBundle, 1 );
		OMS_HEPRESS_VAPORISOL_B_SW_OPEN.Connect( pBundle, 2 );
		OMS_HEPRESS_VAPORISOL_B_SW_CLOSE.Connect( pBundle, 3 );

		pBundle = BundleManager()->CreateBundle( "OMS_ENGINE_SWITCHES", 6 );
		if (ID == 0)
		{
			OMS_ENG_SW_ARM.Connect( pBundle, 0 );
			OMS_ENG_SW_ARMPRESS.Connect( pBundle, 1 );
			OMS_ENG_VLV_SW_ON.Connect( pBundle, 4 );
		}
		else
		{
			OMS_ENG_SW_ARM.Connect( pBundle, 2 );
			OMS_ENG_SW_ARMPRESS.Connect( pBundle, 3 );
			OMS_ENG_VLV_SW_ON.Connect( pBundle, 5 );
		}

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_GPC_CMD", 8 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_GPC_CMD", 8 );
		OMS_HE_ISOV_A_OP.Connect( pBundle, 0 );
		OMS_HE_ISOV_B_OP.Connect( pBundle, 1 );
		OMS_VAP_ISOV_1_OP.Connect( pBundle, 2 );
		OMS_VAP_ISOV_2_OP.Connect( pBundle, 3 );
		OMS_VLV_1_COIL_1_CMD.Connect( pBundle, 4 );
		OMS_VLV_2_COIL_1_CMD.Connect( pBundle, 5 );
		OMS_VLV_1_COIL_2_CMD.Connect( pBundle, 6 );
		OMS_VLV_2_COIL_2_CMD.Connect( pBundle, 7 );

		if (ID == 0) pBundle = BundleManager()->CreateBundle( "LOMS_SENSORS", 16 );
		else pBundle = BundleManager()->CreateBundle( "ROMS_SENSORS", 16 );
		ChamberPressure.Connect( pBundle, 0 );
		N2TankPressure1.Connect( pBundle, 1 );
		N2TankPressure2.Connect( pBundle, 2 );
		HeTankPressure1.Connect( pBundle, 3 );
		HeTankPressure2.Connect( pBundle, 4 );
		return;
	}

	bool OMS::OnParseLine( const char* line )
	{
		return vman.OnParseLine( line );
	}

	void OMS::OnSaveState( FILEHANDLE scn ) const
	{
		vman.OnSaveState( scn );
		return;
	}

	void OMS::OnPreStep( double simt, double simdt, double mjd )
	{
		// solenoid valves driver logic
		// OMS Helium Isolation A
		{
			bool op = OMS_HEPRESS_VAPORISOL_A_SW_OPEN | (OMS_HE_ISOV_A_OP & !OMS_HEPRESS_VAPORISOL_A_SW_CLOSE);
			if (op) OMS_HE_ISOV_A_POWER_OP.SetLine();
			else OMS_HE_ISOV_A_POWER_OP.ResetLine();
		}

		// OMS Helium Isolation B
		{
			bool op = OMS_HEPRESS_VAPORISOL_B_SW_OPEN | (OMS_HE_ISOV_B_OP & !OMS_HEPRESS_VAPORISOL_B_SW_CLOSE);
			if (op) OMS_HE_ISOV_B_POWER_OP.SetLine();
			else OMS_HE_ISOV_B_POWER_OP.ResetLine();
		}

		// OMS Vapor Isolation 1
		{
			bool op = OMS_VAP_ISOV_1_OP | OMS_HEPRESS_VAPORISOL_A_SW_OPEN | OMS_HEPRESS_VAPORISOL_B_SW_OPEN;
			if (op) OMS_VAP_ISOV_1_POWER_OP.SetLine();
			else OMS_VAP_ISOV_1_POWER_OP.ResetLine();
		}

		// OMS Vapor Isolation 2
		{
			bool op = OMS_VAP_ISOV_2_OP | OMS_HEPRESS_VAPORISOL_A_SW_OPEN | OMS_HEPRESS_VAPORISOL_B_SW_OPEN;
			if (op) OMS_VAP_ISOV_2_POWER_OP.SetLine();
			else OMS_VAP_ISOV_2_POWER_OP.ResetLine();
		}

		// OMS Engine Press
		{
			bool op_c1 = OMS_ENG_SW_ARMPRESS;
			bool op_c2 = OMS_ENG_SW_ARMPRESS;

			if (op_c1) OMS_ENG_PRESS_V_POWER_OP_1.SetLine();
			else OMS_ENG_PRESS_V_POWER_OP_1.ResetLine();

			if (op_c2) OMS_ENG_PRESS_V_POWER_OP_2.SetLine();
			else OMS_ENG_PRESS_V_POWER_OP_2.ResetLine();
		}

		// OMS Engine Control 1
		{
			bool op_c1 = ((OMS_ENG_SW_ARM | OMS_ENG_SW_ARMPRESS) & OMS_ENG_VLV_SW_ON) & OMS_VLV_1_COIL_1_CMD;
			bool op_c2 = ((OMS_ENG_SW_ARM | OMS_ENG_SW_ARMPRESS) & OMS_ENG_VLV_SW_ON) & OMS_VLV_1_COIL_2_CMD;

			if (op_c1) OMS_ENG_CNT_V1_POWER_OP_1.SetLine();
			else OMS_ENG_CNT_V1_POWER_OP_1.ResetLine();

			if (op_c2) OMS_ENG_CNT_V1_POWER_OP_2.SetLine();
			else OMS_ENG_CNT_V1_POWER_OP_2.ResetLine();
		}

		// OMS Engine Control 2
		{
			bool op_c1 = ((OMS_ENG_SW_ARM | OMS_ENG_SW_ARMPRESS) & OMS_ENG_VLV_SW_ON) & OMS_VLV_2_COIL_1_CMD;
			bool op_c2 = ((OMS_ENG_SW_ARM | OMS_ENG_SW_ARMPRESS) & OMS_ENG_VLV_SW_ON) & OMS_VLV_2_COIL_2_CMD;

			if (op_c1) OMS_ENG_CNT_V2_POWER_OP_1.SetLine();
			else OMS_ENG_CNT_V2_POWER_OP_1.ResetLine();

			if (op_c2) OMS_ENG_CNT_V2_POWER_OP_2.SetLine();
			else OMS_ENG_CNT_V2_POWER_OP_2.ResetLine();
		}

		// biprop vlv pos
		OMSEngineBipropellent1OPVlv.SetLine( static_cast<float>(OMSEngineControl1Vlv->GetPos() * 5.0) );
		OMSEngineBipropellent2OPVlv.SetLine( static_cast<float>(OMSEngineControl2Vlv->GetPos() * 5.0) );

		// TODO pre or post?
		vman.OnPostStep( simt, simdt, mjd );

		unsigned short src = 0;
		// TODO calculate prop source from valve positions
		if (true/*src != source*/)
		{
			STS()->SetOMSPropSource( ID, LOMS+ID/*src*/ );
			source = src;
		}

		//STS()->SetOMSThrustLevel( ID, 1.0 * (((OMS_Arm | OMS_ArmPress) & OMS_Eng_Vlv) & OMS_Vlv_Coil) );

		ChamberPressure.SetValue( 100.0 * STS()->GetThrusterLevel( STS()->th_oms[ID] ) + (STS()->GetAtmPressure() * 0.00011603) );
		N2TankPressure1.SetValue( 0.0 );
		N2TankPressure2.SetValue( 0.0 );
		HeTankPressure1.SetValue( 0.0 );
		HeTankPressure2.SetValue( 0.0 );
		return;
	}
}
