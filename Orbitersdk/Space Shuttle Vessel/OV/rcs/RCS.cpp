#include "RCS.h"
#include <SolenoidValve.h>
#include <MotorValve.h>
#include <MathSSV.h>
#include "..\Atlantis.h"
#include "..\ParameterValues.h"


namespace rcs
{
	constexpr double VLV_OP = 0.95;// 0 = CL, 1 = OP


	RCS::RCS( AtlantisSubsystemDirector* _director, const string& _ident ):AtlantisSubsystem( _director, _ident )
	{
		vman.AddValve( FRCSHePressFuelIsolAVlv = new SolenoidLatchingValve( "Fwd He Fuel Isol A", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( FRCSHePressFuelIsolBVlv = new SolenoidLatchingValve( "Fwd He Fuel Isol B", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( FRCSHePressOxidIsolAVlv = new SolenoidLatchingValve( "Fwd He Oxid Isol A", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( FRCSHePressOxidIsolBVlv = new SolenoidLatchingValve( "Fwd He Oxid Isol B", 0.0, 1000.0, nullptr, nullptr ) );

		vman.AddValve( FRCSFuelTankIsol12Vlv = new MotorValve( "Fwd RCS Fuel Tank Isol 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidTankIsol12Vlv = new MotorValve( "Fwd RCS Oxid Tank Isol 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSFuelTankIsol345Vlv = new MotorValve( "Fwd RCS Fuel Tank Isol 3/4/5", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidTankIsol345Vlv = new MotorValve( "Fwd RCS Oxid Tank Isol 3/4/5", 0.0, 100.0, nullptr, nullptr ) );

		vman.AddValve( FRCSFuelManifIsol1Vlv = new MotorValve( "Fwd RCS Fuel Manif Isol 1", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidManifIsol1Vlv = new MotorValve( "Fwd RCS Oxid Manif Isol 1", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSFuelManifIsol2Vlv = new MotorValve( "Fwd RCS Fuel Manif Isol 2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidManifIsol2Vlv = new MotorValve( "Fwd RCS Oxid Manif Isol 2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSFuelManifIsol3Vlv = new MotorValve( "Fwd RCS Fuel Manif Isol 3", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidManifIsol3Vlv = new MotorValve( "Fwd RCS Oxid Manif Isol 3", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSFuelManifIsol4Vlv = new MotorValve( "Fwd RCS Fuel Manif Isol 4", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidManifIsol4Vlv = new MotorValve( "Fwd RCS Oxid Manif Isol 4", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( FRCSFuelManifIsol5Vlv = new SolenoidLatchingValve( "Fwd RCS Fuel Manif Isol 5", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( FRCSOxidManifIsol5Vlv = new SolenoidLatchingValve( "Fwd RCS Oxid Manif Isol 5", 0.0, 1000.0, nullptr, nullptr ) );


		vman.AddValve( LRCSHePressFuelIsolAVlv = new SolenoidLatchingValve( "Left He Fuel Isol A", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( LRCSHePressFuelIsolBVlv = new SolenoidLatchingValve( "Left He Fuel Isol B", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( LRCSHePressOxidIsolAVlv = new SolenoidLatchingValve( "Left He Oxid Isol A", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( LRCSHePressOxidIsolBVlv = new SolenoidLatchingValve( "Left He Oxid Isol B", 0.0, 1000.0, nullptr, nullptr ) );

		vman.AddValve( LRCSFuelTankIsol12Vlv = new MotorValve( "Left RCS Fuel Tank Isol 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidTankIsol12Vlv = new MotorValve( "Left RCS Oxid Tank Isol 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelTankIsol345AVlv = new MotorValve( "Left RCS Fuel Tank Isol 3/4/5 A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelTankIsol345BVlv = new MotorValve( "Left RCS Fuel Tank Isol 3/4/5 B", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidTankIsol345AVlv = new MotorValve( "Left RCS Oxid Tank Isol 3/4/5 A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidTankIsol345BVlv = new MotorValve( "Left RCS Oxid Tank Isol 3/4/5 B", 0.0, 100.0, nullptr, nullptr ) );

		vman.AddValve( LRCSFuelManifIsol1Vlv = new MotorValve( "Left RCS Fuel Manif Isol 1", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidManifIsol1Vlv = new MotorValve( "Left RCS Oxid Manif Isol 1", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelManifIsol2Vlv = new MotorValve( "Left RCS Fuel Manif Isol 2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidManifIsol2Vlv = new MotorValve( "Left RCS Oxid Manif Isol 2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelManifIsol3Vlv = new MotorValve( "Left RCS Fuel Manif Isol 3", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidManifIsol3Vlv = new MotorValve( "Left RCS Oxid Manif Isol 3", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelManifIsol4Vlv = new MotorValve( "Left RCS Fuel Manif Isol 4", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidManifIsol4Vlv = new MotorValve( "Left RCS Oxid Manif Isol 4", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelManifIsol5Vlv = new SolenoidLatchingValve( "Left RCS Fuel Manif Isol 5", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidManifIsol5Vlv = new SolenoidLatchingValve( "Left RCS Oxid Manif Isol 5", 0.0, 1000.0, nullptr, nullptr ) );

		vman.AddValve( LRCSFuelCrossfeed12Vlv = new MotorValve( "Left RCS Fuel Crossfeed 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidCrossfeed12Vlv = new MotorValve( "Left RCS Oxid Crossfeed 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSFuelCrossfeed345Vlv = new MotorValve( "Left RCS Fuel Crossfeed 3/4/5", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( LRCSOxidCrossfeed345Vlv = new MotorValve( "Left RCS Oxid Crossfeed 3/4/5", 0.0, 100.0, nullptr, nullptr ) );


		vman.AddValve( RRCSHePressFuelIsolAVlv = new SolenoidLatchingValve( "Right He Fuel Isol A", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( RRCSHePressFuelIsolBVlv = new SolenoidLatchingValve( "Right He Fuel Isol B", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( RRCSHePressOxidIsolAVlv = new SolenoidLatchingValve( "Right He Oxid Isol A", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( RRCSHePressOxidIsolBVlv = new SolenoidLatchingValve( "Right He Oxid Isol B", 0.0, 1000.0, nullptr, nullptr ) );

		vman.AddValve( RRCSFuelTankIsol12Vlv = new MotorValve( "Right RCS Fuel Tank Isol 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidTankIsol12Vlv = new MotorValve( "Right RCS Oxid Tank Isol 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelTankIsol345AVlv = new MotorValve( "Right RCS Fuel Tank Isol 3/4/5 A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelTankIsol345BVlv = new MotorValve( "Right RCS Fuel Tank Isol 3/4/5 B", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidTankIsol345AVlv = new MotorValve( "Right RCS Oxid Tank Isol 3/4/5 A", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidTankIsol345BVlv = new MotorValve( "Right RCS Oxid Tank Isol 3/4/5 B", 0.0, 100.0, nullptr, nullptr ) );

		vman.AddValve( RRCSFuelManifIsol1Vlv = new MotorValve( "Right RCS Fuel Manif Isol 1", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidManifIsol1Vlv = new MotorValve( "Right RCS Oxid Manif Isol 1", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelManifIsol2Vlv = new MotorValve( "Right RCS Fuel Manif Isol 2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidManifIsol2Vlv = new MotorValve( "Right RCS Oxid Manif Isol 2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelManifIsol3Vlv = new MotorValve( "Right RCS Fuel Manif Isol 3", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidManifIsol3Vlv = new MotorValve( "Right RCS Oxid Manif Isol 3", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelManifIsol4Vlv = new MotorValve( "Right RCS Fuel Manif Isol 4", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidManifIsol4Vlv = new MotorValve( "Right RCS Oxid Manif Isol 4", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelManifIsol5Vlv = new SolenoidLatchingValve( "Right RCS Fuel Manif Isol 5", 0.0, 1000.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidManifIsol5Vlv = new SolenoidLatchingValve( "Right RCS Oxid Manif Isol 5", 0.0, 1000.0, nullptr, nullptr ) );

		vman.AddValve( RRCSFuelCrossfeed12Vlv = new MotorValve( "Right RCS Fuel Crossfeed 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidCrossfeed12Vlv = new MotorValve( "Right RCS Oxid Crossfeed 1/2", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSFuelCrossfeed345Vlv = new MotorValve( "Right RCS Fuel Crossfeed 3/4/5", 0.0, 100.0, nullptr, nullptr ) );
		vman.AddValve( RRCSOxidCrossfeed345Vlv = new MotorValve( "Right RCS Oxid Crossfeed 3/4/5", 0.0, 100.0, nullptr, nullptr ) );

		FRCS1source = 0;
		FRCS2source = 0;
		FRCS3source = 0;
		FRCS4source = 0;
		FRCS5source = 0;

		LRCS1source = 0;
		LRCS2source = 0;
		LRCS3source = 0;
		LRCS4source = 0;
		LRCS5source = 0;

		RRCS1source = 0;
		RRCS2source = 0;
		RRCS3source = 0;
		RRCS4source = 0;
		RRCS5source = 0;
		return;
	}

	RCS::~RCS( void )
	{
	}

	void RCS::Realize( void )
	{
		// driver
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_FRCS", 16 );
		dipDriver[RCS_F2F].Connect( pBundle, 0 );
		dipDriver[RCS_F3F].Connect( pBundle, 1 );
		dipDriver[RCS_F1F].Connect( pBundle, 2 );
		dipDriver[RCS_F1L].Connect( pBundle, 3 );
		dipDriver[RCS_F3L].Connect( pBundle, 4 );
		dipDriver[RCS_F2R].Connect( pBundle, 5 );
		dipDriver[RCS_F4R].Connect( pBundle, 6 );
		dipDriver[RCS_F2U].Connect( pBundle, 7 );
		dipDriver[RCS_F3U].Connect( pBundle, 8 );
		dipDriver[RCS_F1U].Connect( pBundle, 9 );
		dipDriver[RCS_F2D].Connect( pBundle, 10 );
		dipDriver[RCS_F1D].Connect( pBundle, 11 );
		dipDriver[RCS_F4D].Connect( pBundle, 12 );
		dipDriver[RCS_F3D].Connect( pBundle, 13 );
		dipDriver[RCS_F5R].Connect( pBundle, 14 );
		dipDriver[RCS_F5L].Connect( pBundle, 15 );
		
		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_LRCS", 14 );
		dipDriver[RCS_L3A].Connect( pBundle, 0 );
		dipDriver[RCS_L1A].Connect( pBundle, 1 );
		dipDriver[RCS_L4L].Connect( pBundle, 2 );
		dipDriver[RCS_L2L].Connect( pBundle, 3 );
		dipDriver[RCS_L3L].Connect( pBundle, 4 );
		dipDriver[RCS_L1L].Connect( pBundle, 5 );
		dipDriver[RCS_L4U].Connect( pBundle, 6 );
		dipDriver[RCS_L2U].Connect( pBundle, 7 );
		dipDriver[RCS_L1U].Connect( pBundle, 8 );
		dipDriver[RCS_L4D].Connect( pBundle, 9 );
		dipDriver[RCS_L2D].Connect( pBundle, 10 );
		dipDriver[RCS_L3D].Connect( pBundle, 11 );
		dipDriver[RCS_L5D].Connect( pBundle, 12 );
		dipDriver[RCS_L5L].Connect( pBundle, 13 );
		
		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_RRCS", 14 );
		dipDriver[RCS_R3A].Connect( pBundle, 0 );
		dipDriver[RCS_R1A].Connect( pBundle, 1 );
		dipDriver[RCS_R4R].Connect( pBundle, 2 );
		dipDriver[RCS_R2R].Connect( pBundle, 3 );
		dipDriver[RCS_R3R].Connect( pBundle, 4 );
		dipDriver[RCS_R1R].Connect( pBundle, 5 );
		dipDriver[RCS_R4U].Connect( pBundle, 6 );
		dipDriver[RCS_R2U].Connect( pBundle, 7 );
		dipDriver[RCS_R1U].Connect( pBundle, 8 );
		dipDriver[RCS_R4D].Connect( pBundle, 9 );
		dipDriver[RCS_R2D].Connect( pBundle, 10 );
		dipDriver[RCS_R3D].Connect( pBundle, 11 );
		dipDriver[RCS_R5D].Connect( pBundle, 12 );
		dipDriver[RCS_R5R].Connect( pBundle, 13 );

		// PC
		pBundle = BundleManager()->CreateBundle( "RCS_PC_FRCS", 16 );
		dopPC[RCS_F2F].Connect( pBundle, 0 );
		dopPC[RCS_F3F].Connect( pBundle, 1 );
		dopPC[RCS_F1F].Connect( pBundle, 2 );
		dopPC[RCS_F1L].Connect( pBundle, 3 );
		dopPC[RCS_F3L].Connect( pBundle, 4 );
		dopPC[RCS_F2R].Connect( pBundle, 5 );
		dopPC[RCS_F4R].Connect( pBundle, 6 );
		dopPC[RCS_F2U].Connect( pBundle, 7 );
		dopPC[RCS_F3U].Connect( pBundle, 8 );
		dopPC[RCS_F1U].Connect( pBundle, 9 );
		dopPC[RCS_F2D].Connect( pBundle, 10 );
		dopPC[RCS_F1D].Connect( pBundle, 11 );
		dopPC[RCS_F4D].Connect( pBundle, 12 );
		dopPC[RCS_F3D].Connect( pBundle, 13 );
		dopPC[RCS_F5R].Connect( pBundle, 14 );
		dopPC[RCS_F5L].Connect( pBundle, 15 );
		
		pBundle = BundleManager()->CreateBundle( "RCS_PC_LRCS", 14 );
		dopPC[RCS_L3A].Connect( pBundle, 0 );
		dopPC[RCS_L1A].Connect( pBundle, 1 );
		dopPC[RCS_L4L].Connect( pBundle, 2 );
		dopPC[RCS_L2L].Connect( pBundle, 3 );
		dopPC[RCS_L3L].Connect( pBundle, 4 );
		dopPC[RCS_L1L].Connect( pBundle, 5 );
		dopPC[RCS_L4U].Connect( pBundle, 6 );
		dopPC[RCS_L2U].Connect( pBundle, 7 );
		dopPC[RCS_L1U].Connect( pBundle, 8 );
		dopPC[RCS_L4D].Connect( pBundle, 9 );
		dopPC[RCS_L2D].Connect( pBundle, 10 );
		dopPC[RCS_L3D].Connect( pBundle, 11 );
		dopPC[RCS_L5D].Connect( pBundle, 12 );
		dopPC[RCS_L5L].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "RCS_PC_RRCS", 14 );
		dopPC[RCS_R3A].Connect( pBundle, 0 );
		dopPC[RCS_R1A].Connect( pBundle, 1 );
		dopPC[RCS_R4R].Connect( pBundle, 2 );
		dopPC[RCS_R2R].Connect( pBundle, 3 );
		dopPC[RCS_R3R].Connect( pBundle, 4 );
		dopPC[RCS_R1R].Connect( pBundle, 5 );
		dopPC[RCS_R4U].Connect( pBundle, 6 );
		dopPC[RCS_R2U].Connect( pBundle, 7 );
		dopPC[RCS_R1U].Connect( pBundle, 8 );
		dopPC[RCS_R4D].Connect( pBundle, 9 );
		dopPC[RCS_R2D].Connect( pBundle, 10 );
		dopPC[RCS_R3D].Connect( pBundle, 11 );
		dopPC[RCS_R5D].Connect( pBundle, 12 );
		dopPC[RCS_R5R].Connect( pBundle, 13 );


		pBundle = BundleManager()->CreateBundle( "FRCS_HE_ISOL", 16 );
		FRCSHePressFuelIsolAVlv->ConnectInput( 0, true, pBundle, 0 );
		FRCSHePressFuelIsolAVlv->ConnectInput( 0, false, pBundle, 1 );
		FRCSHePressFuelIsolAVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		FRCSHePressFuelIsolAVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		FRCSHePressOxidIsolAVlv->ConnectInput( 0, true, pBundle, 4 );
		FRCSHePressOxidIsolAVlv->ConnectInput( 0, false, pBundle, 5 );
		FRCSHePressOxidIsolAVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		FRCSHePressOxidIsolAVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		FRCSHePressFuelIsolBVlv->ConnectInput( 0, true, pBundle, 8 );
		FRCSHePressFuelIsolBVlv->ConnectInput( 0, false, pBundle, 9 );
		FRCSHePressFuelIsolBVlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		FRCSHePressFuelIsolBVlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		FRCSHePressOxidIsolBVlv->ConnectInput( 0, true, pBundle, 12 );
		FRCSHePressOxidIsolBVlv->ConnectInput( 0, false, pBundle, 13 );
		FRCSHePressOxidIsolBVlv->ConnectPositionSensor( 0, true, pBundle, 14 );
		FRCSHePressOxidIsolBVlv->ConnectPositionSensor( 0, false, pBundle, 15 );
		FWD_HE_FU_ISOV_A_POWER_OP.Connect( pBundle, 0 );
		FWD_HE_FU_ISOV_A_POWER_CL.Connect( pBundle, 1 );
		F_HE_FU_PRESS_V_A_OP.Connect( pBundle, 2 );
		F_HE_FU_PRESS_V_A_CL.Connect( pBundle, 3 );
		FWD_HE_OX_ISOV_A_POWER_OP.Connect( pBundle, 4 );
		FWD_HE_OX_ISOV_A_POWER_CL.Connect( pBundle, 5 );
		F_HE_OX_PRESS_V_A_OP.Connect( pBundle, 6 );
		F_HE_OX_PRESS_V_A_CL.Connect( pBundle, 7 );
		FWD_HE_FU_ISOV_B_POWER_OP.Connect( pBundle, 8 );
		FWD_HE_FU_ISOV_B_POWER_CL.Connect( pBundle, 9 );
		F_HE_FU_PRESS_V_B_OP.Connect( pBundle, 10 );
		F_HE_FU_PRESS_V_B_CL.Connect( pBundle, 11 );
		FWD_HE_OX_ISOV_B_POWER_OP.Connect( pBundle, 12 );
		FWD_HE_OX_ISOV_B_POWER_CL.Connect( pBundle, 13 );
		F_HE_OX_PRESS_V_B_OP.Connect( pBundle, 14 );
		F_HE_OX_PRESS_V_B_CL.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "FRCS_TANK_ISOL", 12 );
		FRCSFuelTankIsol12Vlv->ConnectInput( pBundle, 0 );
		FRCSOxidTankIsol12Vlv->ConnectInput( pBundle, 1 );
		FRCSFuelTankIsol12Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		FRCSFuelTankIsol12Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		FRCSOxidTankIsol12Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		FRCSOxidTankIsol12Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		FRCSFuelTankIsol345Vlv->ConnectInput( pBundle, 6 );
		FRCSOxidTankIsol345Vlv->ConnectInput( pBundle, 7 );
		FRCSFuelTankIsol345Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		FRCSFuelTankIsol345Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		FRCSOxidTankIsol345Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		FRCSOxidTankIsol345Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		F_FU_TK_ISOV_12_OP.Connect( pBundle, 2 );
		F_FU_TK_ISOV_12_CL.Connect( pBundle, 3 );
		F_OX_TK_ISOV_12_OP.Connect( pBundle, 4 );
		F_OX_TK_ISOV_12_CL.Connect( pBundle, 5 );
		F_FU_TK_ISOV_345_OP.Connect( pBundle, 8 );
		F_FU_TK_ISOV_345_CL.Connect( pBundle, 9 );
		F_OX_TK_ISOV_345_OP.Connect( pBundle, 10 );
		F_OX_TK_ISOV_345_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "FRCS_MANF_12_ISOL", 12 );
		FRCSFuelManifIsol1Vlv->ConnectInput( pBundle, 0 );
		FRCSOxidManifIsol1Vlv->ConnectInput( pBundle, 1 );
		FRCSFuelManifIsol1Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		FRCSFuelManifIsol1Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		FRCSOxidManifIsol1Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		FRCSOxidManifIsol1Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		FRCSFuelManifIsol2Vlv->ConnectInput( pBundle, 6 );
		FRCSOxidManifIsol2Vlv->ConnectInput( pBundle, 7 );
		FRCSFuelManifIsol2Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		FRCSFuelManifIsol2Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		FRCSOxidManifIsol2Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		FRCSOxidManifIsol2Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		F_FU_MANF_ISOV_1_OP.Connect( pBundle, 2 );
		F_FU_MANF_ISOV_1_CL.Connect( pBundle, 3 );
		F_OX_MANF_ISOV_1_OP.Connect( pBundle, 4 );
		F_OX_MANF_ISOV_1_CL.Connect( pBundle, 5 );
		F_FU_MANF_ISOV_2_OP.Connect( pBundle, 8 );
		F_FU_MANF_ISOV_2_CL.Connect( pBundle, 9 );
		F_OX_MANF_ISOV_2_OP.Connect( pBundle, 10 );
		F_OX_MANF_ISOV_2_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "FRCS_MANF_34_ISOL", 12 );
		FRCSFuelManifIsol3Vlv->ConnectInput( pBundle, 0 );
		FRCSOxidManifIsol3Vlv->ConnectInput( pBundle, 1 );
		FRCSFuelManifIsol3Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		FRCSFuelManifIsol3Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		FRCSOxidManifIsol3Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		FRCSOxidManifIsol3Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		FRCSFuelManifIsol4Vlv->ConnectInput( pBundle, 6 );
		FRCSOxidManifIsol4Vlv->ConnectInput( pBundle, 7 );
		FRCSFuelManifIsol4Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		FRCSFuelManifIsol4Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		FRCSOxidManifIsol4Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		FRCSOxidManifIsol4Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		F_FU_MANF_ISOV_3_OP.Connect( pBundle, 2 );
		F_FU_MANF_ISOV_3_CL.Connect( pBundle, 3 );
		F_OX_MANF_ISOV_3_OP.Connect( pBundle, 4 );
		F_OX_MANF_ISOV_3_CL.Connect( pBundle, 5 );
		F_FU_MANF_ISOV_4_OP.Connect( pBundle, 8 );
		F_FU_MANF_ISOV_4_CL.Connect( pBundle, 9 );
		F_OX_MANF_ISOV_4_OP.Connect( pBundle, 10 );
		F_OX_MANF_ISOV_4_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "FRCS_MANF_5_ISOL", 8 );
		FRCSFuelManifIsol5Vlv->ConnectInput( 0, true, pBundle, 0 );
		FRCSFuelManifIsol5Vlv->ConnectInput( 0, false, pBundle, 1 );
		FRCSOxidManifIsol5Vlv->ConnectInput( 0, true, pBundle, 2 );
		FRCSOxidManifIsol5Vlv->ConnectInput( 0, false, pBundle, 3 );
		FRCSFuelManifIsol5Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		FRCSFuelManifIsol5Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		FRCSOxidManifIsol5Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		FRCSOxidManifIsol5Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		F_FU_MANF_ISOV_NO_5_POWER_OP.Connect( pBundle, 0 );
		F_FU_MANF_ISOV_NO_5_POWER_CL.Connect( pBundle, 1 );
		F_OX_MANF_ISOV_NO_5_POWER_OP.Connect( pBundle, 2 );
		F_OX_MANF_ISOV_NO_5_POWER_CL.Connect( pBundle, 3 );
		F_FU_MANF_ISOV_5_OP.Connect( pBundle, 4 );
		F_FU_MANF_ISOV_5_CL.Connect( pBundle, 5 );
		F_OX_MANF_ISOV_5_OP.Connect( pBundle, 6 );
		F_OX_MANF_ISOV_5_CL.Connect( pBundle, 7 );


		pBundle = BundleManager()->CreateBundle( "LRCS_HE_ISOL", 16 );
		LRCSHePressFuelIsolAVlv->ConnectInput( 0, true, pBundle, 0 );
		LRCSHePressFuelIsolAVlv->ConnectInput( 0, false, pBundle, 1 );
		LRCSHePressFuelIsolAVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		LRCSHePressFuelIsolAVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		LRCSHePressOxidIsolAVlv->ConnectInput( 0, true, pBundle, 4 );
		LRCSHePressOxidIsolAVlv->ConnectInput( 0, false, pBundle, 5 );
		LRCSHePressOxidIsolAVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		LRCSHePressOxidIsolAVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		LRCSHePressFuelIsolBVlv->ConnectInput( 0, true, pBundle, 8 );
		LRCSHePressFuelIsolBVlv->ConnectInput( 0, false, pBundle, 9 );
		LRCSHePressFuelIsolBVlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		LRCSHePressFuelIsolBVlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		LRCSHePressOxidIsolBVlv->ConnectInput( 0, true, pBundle, 12 );
		LRCSHePressOxidIsolBVlv->ConnectInput( 0, false, pBundle, 13 );
		LRCSHePressOxidIsolBVlv->ConnectPositionSensor( 0, true, pBundle, 14 );
		LRCSHePressOxidIsolBVlv->ConnectPositionSensor( 0, false, pBundle, 15 );
		LEFT_HE_FU_ISOV_A_POWER_OP.Connect( pBundle, 0 );
		LEFT_HE_FU_ISOV_A_POWER_CL.Connect( pBundle, 1 );
		L_HE_FU_PRESS_V_A_OP.Connect( pBundle, 2 );
		L_HE_FU_PRESS_V_A_CL.Connect( pBundle, 3 );
		LEFT_HE_OX_ISOV_A_POWER_OP.Connect( pBundle, 4 );
		LEFT_HE_OX_ISOV_A_POWER_CL.Connect( pBundle, 5 );
		L_HE_OX_PRESS_V_A_OP.Connect( pBundle, 6 );
		L_HE_OX_PRESS_V_A_CL.Connect( pBundle, 7 );
		LEFT_HE_FU_ISOV_B_POWER_OP.Connect( pBundle, 8 );
		LEFT_HE_FU_ISOV_B_POWER_CL.Connect( pBundle, 9 );
		L_HE_FU_PRESS_V_B_OP.Connect( pBundle, 10 );
		L_HE_FU_PRESS_V_B_CL.Connect( pBundle, 11 );
		LEFT_HE_OX_ISOV_B_POWER_OP.Connect( pBundle, 12 );
		LEFT_HE_OX_ISOV_B_POWER_CL.Connect( pBundle, 13 );
		L_HE_OX_PRESS_V_B_OP.Connect( pBundle, 14 );
		L_HE_OX_PRESS_V_B_CL.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "LRCS_TANK_ISOL_12", 10 );
		LRCSFuelTankIsol12Vlv->ConnectInput( pBundle, 0 );
		LRCSOxidTankIsol12Vlv->ConnectInput( pBundle, 1 );
		LRCSFuelTankIsol12Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		LRCSFuelTankIsol12Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		LRCSFuelTankIsol12Vlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		LRCSFuelTankIsol12Vlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		LRCSOxidTankIsol12Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		LRCSOxidTankIsol12Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		LRCSOxidTankIsol12Vlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		LRCSOxidTankIsol12Vlv->ConnectPositionSensor( 1, false, pBundle, 9 );
		L_FU_TK_ISO_V_12_OP_1.Connect( pBundle, 2 );
		L_FU_TK_ISO_V_12_CL_1.Connect( pBundle, 3 );
		L_OX_TK_ISO_V_12_OP_1.Connect( pBundle, 6 );
		L_OX_TK_ISO_V_12_CL_1.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "LRCS_TANK_ISOL_345", 12 );
		LRCSFuelTankIsol345AVlv->ConnectInput( pBundle, 0 );
		LRCSOxidTankIsol345AVlv->ConnectInput( pBundle, 1 );
		LRCSFuelTankIsol345BVlv->ConnectInput( pBundle, 2 );
		LRCSOxidTankIsol345BVlv->ConnectInput( pBundle, 3 );
		LRCSFuelTankIsol345AVlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		LRCSFuelTankIsol345AVlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		LRCSOxidTankIsol345AVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		LRCSOxidTankIsol345AVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		LRCSFuelTankIsol345BVlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		LRCSFuelTankIsol345BVlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		LRCSOxidTankIsol345BVlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		LRCSOxidTankIsol345BVlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		L_FU_TK_ISO_V_345_A_OP.Connect( pBundle, 4 );
		L_FU_TK_ISO_V_345_A_CL.Connect( pBundle, 5 );
		L_OX_TK_ISO_V_345_A_OP.Connect( pBundle, 6 );
		L_OX_TK_ISO_V_345_A_CL.Connect( pBundle, 7 );
		L_FU_TK_ISO_V_345_B_OP.Connect( pBundle, 8 );
		L_FU_TK_ISO_V_345_B_CL.Connect( pBundle, 9 );
		L_OX_TK_ISO_V_345_B_OP.Connect( pBundle, 10 );
		L_OX_TK_ISO_V_345_B_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_12_ISOL", 12 );
		LRCSFuelManifIsol1Vlv->ConnectInput( pBundle, 0 );
		LRCSOxidManifIsol1Vlv->ConnectInput( pBundle, 1 );
		LRCSFuelManifIsol1Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		LRCSFuelManifIsol1Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		LRCSOxidManifIsol1Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		LRCSOxidManifIsol1Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		LRCSFuelManifIsol2Vlv->ConnectInput( pBundle, 6 );
		LRCSOxidManifIsol2Vlv->ConnectInput( pBundle, 7 );
		LRCSFuelManifIsol2Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		LRCSFuelManifIsol2Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		LRCSOxidManifIsol2Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		LRCSOxidManifIsol2Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		L_FU_MANF_ISOV_1_OP.Connect( pBundle, 2 );
		L_FU_MANF_ISOV_1_CL.Connect( pBundle, 3 );
		L_OX_MANF_ISOV_1_OP.Connect( pBundle, 4 );
		L_OX_MANF_ISOV_1_CL.Connect( pBundle, 5 );
		L_FU_MANF_ISOV_2_OP.Connect( pBundle, 8 );
		L_FU_MANF_ISOV_2_CL.Connect( pBundle, 9 );
		L_OX_MANF_ISOV_2_OP.Connect( pBundle, 10 );
		L_OX_MANF_ISOV_2_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_34_ISOL", 12 );
		LRCSFuelManifIsol3Vlv->ConnectInput( pBundle, 0 );
		LRCSOxidManifIsol3Vlv->ConnectInput( pBundle, 1 );
		LRCSFuelManifIsol3Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		LRCSFuelManifIsol3Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		LRCSOxidManifIsol3Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		LRCSOxidManifIsol3Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		LRCSFuelManifIsol4Vlv->ConnectInput( pBundle, 6 );
		LRCSOxidManifIsol4Vlv->ConnectInput( pBundle, 7 );
		LRCSFuelManifIsol4Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		LRCSFuelManifIsol4Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		LRCSOxidManifIsol4Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		LRCSOxidManifIsol4Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		L_FU_MANF_ISOV_3_OP.Connect( pBundle, 2 );
		L_FU_MANF_ISOV_3_CL.Connect( pBundle, 3 );
		L_OX_MANF_ISOV_3_OP.Connect( pBundle, 4 );
		L_OX_MANF_ISOV_3_CL.Connect( pBundle, 5 );
		L_FU_MANF_ISOV_4_OP.Connect( pBundle, 8 );
		L_FU_MANF_ISOV_4_CL.Connect( pBundle, 9 );
		L_OX_MANF_ISOV_4_OP.Connect( pBundle, 10 );
		L_OX_MANF_ISOV_4_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_5_ISOL", 8 );
		LRCSFuelManifIsol5Vlv->ConnectInput( 0, true, pBundle, 0 );
		LRCSFuelManifIsol5Vlv->ConnectInput( 0, false, pBundle, 1 );
		LRCSOxidManifIsol5Vlv->ConnectInput( 0, true, pBundle, 2 );
		LRCSOxidManifIsol5Vlv->ConnectInput( 0, false, pBundle, 3 );
		LRCSFuelManifIsol5Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		LRCSFuelManifIsol5Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		LRCSOxidManifIsol5Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		LRCSOxidManifIsol5Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		L_FU_MANF_ISOV_NO_5_POWER_OP.Connect( pBundle, 0 );
		L_FU_MANF_ISOV_NO_5_POWER_CL.Connect( pBundle, 1 );
		L_OX_MANF_ISOV_NO_5_POWER_OP.Connect( pBundle, 2 );
		L_OX_MANF_ISOV_NO_5_POWER_CL.Connect( pBundle, 3 );
		L_FU_MANF_ISOV_5_OP.Connect( pBundle, 4 );
		L_FU_MANF_ISOV_5_CL.Connect( pBundle, 5 );
		L_OX_MANF_ISOV_5_OP.Connect( pBundle, 6 );
		L_OX_MANF_ISOV_5_CL.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "LRCS_XFD_12", 10 );
		LRCSFuelCrossfeed12Vlv->ConnectInput( pBundle, 0 );
		LRCSOxidCrossfeed12Vlv->ConnectInput( pBundle, 1 );
		LRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		LRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		LRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		LRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		LRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		LRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		LRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		LRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 1, false, pBundle, 9 );
		L_RCS_FU_XFD_12_OP_1.Connect( pBundle, 2 );
		L_RCS_FU_XFD_12_CL_1.Connect( pBundle, 3 );
		L_RCS_OX_XFD_12_OP_1.Connect( pBundle, 6 );
		L_RCS_OX_XFD_12_CL_1.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "LRCS_XFD_345", 10 );
		LRCSFuelCrossfeed345Vlv->ConnectInput( pBundle, 0 );
		LRCSOxidCrossfeed345Vlv->ConnectInput( pBundle, 1 );
		LRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		LRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		LRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		LRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		LRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		LRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		LRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		LRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 1, false, pBundle, 9 );
		L_RCS_FU_XFD_345_OP_1.Connect( pBundle, 2 );
		L_RCS_FU_XFD_345_CL_1.Connect( pBundle, 3 );
		L_RCS_OX_XFD_345_OP_1.Connect( pBundle, 6 );
		L_RCS_OX_XFD_345_CL_1.Connect( pBundle, 7 );


		pBundle = BundleManager()->CreateBundle( "RRCS_HE_ISOL", 16 );
		RRCSHePressFuelIsolAVlv->ConnectInput( 0, true, pBundle, 0 );
		RRCSHePressFuelIsolAVlv->ConnectInput( 0, false, pBundle, 1 );
		RRCSHePressFuelIsolAVlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		RRCSHePressFuelIsolAVlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		RRCSHePressOxidIsolAVlv->ConnectInput( 0, true, pBundle, 4 );
		RRCSHePressOxidIsolAVlv->ConnectInput( 0, false, pBundle, 5 );
		RRCSHePressOxidIsolAVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		RRCSHePressOxidIsolAVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		RRCSHePressFuelIsolBVlv->ConnectInput( 0, true, pBundle, 8 );
		RRCSHePressFuelIsolBVlv->ConnectInput( 0, false, pBundle, 9 );
		RRCSHePressFuelIsolBVlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		RRCSHePressFuelIsolBVlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		RRCSHePressOxidIsolBVlv->ConnectInput( 0, true, pBundle, 12 );
		RRCSHePressOxidIsolBVlv->ConnectInput( 0, false, pBundle, 13 );
		RRCSHePressOxidIsolBVlv->ConnectPositionSensor( 0, true, pBundle, 14 );
		RRCSHePressOxidIsolBVlv->ConnectPositionSensor( 0, false, pBundle, 15 );
		RIGHT_HE_FU_ISOV_A_POWER_OP.Connect( pBundle, 0 );
		RIGHT_HE_FU_ISOV_A_POWER_CL.Connect( pBundle, 1 );
		R_HE_FU_PRESS_V_A_OP.Connect( pBundle, 2 );
		R_HE_FU_PRESS_V_A_CL.Connect( pBundle, 3 );
		RIGHT_HE_OX_ISOV_A_POWER_OP.Connect( pBundle, 4 );
		RIGHT_HE_OX_ISOV_A_POWER_CL.Connect( pBundle, 5 );
		R_HE_OX_PRESS_V_A_OP.Connect( pBundle, 6 );
		R_HE_OX_PRESS_V_A_CL.Connect( pBundle, 7 );
		RIGHT_HE_FU_ISOV_B_POWER_OP.Connect( pBundle, 8 );
		RIGHT_HE_FU_ISOV_B_POWER_CL.Connect( pBundle, 9 );
		R_HE_FU_PRESS_V_B_OP.Connect( pBundle, 10 );
		R_HE_FU_PRESS_V_B_CL.Connect( pBundle, 11 );
		RIGHT_HE_OX_ISOV_B_POWER_OP.Connect( pBundle, 12 );
		RIGHT_HE_OX_ISOV_B_POWER_CL.Connect( pBundle, 13 );
		R_HE_OX_PRESS_V_B_OP.Connect( pBundle, 14 );
		R_HE_OX_PRESS_V_B_CL.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "RRCS_TANK_ISOL_12", 10 );
		RRCSFuelTankIsol12Vlv->ConnectInput( pBundle, 0 );
		RRCSOxidTankIsol12Vlv->ConnectInput( pBundle, 1 );
		RRCSFuelTankIsol12Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		RRCSFuelTankIsol12Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		RRCSFuelTankIsol12Vlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		RRCSFuelTankIsol12Vlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		RRCSOxidTankIsol12Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		RRCSOxidTankIsol12Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		RRCSOxidTankIsol12Vlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		RRCSOxidTankIsol12Vlv->ConnectPositionSensor( 1, false, pBundle, 9 );
		R_FU_TK_ISO_V_12_OP_1.Connect( pBundle, 2 );
		R_FU_TK_ISO_V_12_CL_1.Connect( pBundle, 3 );
		R_OX_TK_ISO_V_12_OP_1.Connect( pBundle, 6 );
		R_OX_TK_ISO_V_12_CL_1.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "RRCS_TANK_ISOL_345", 12 );
		RRCSFuelTankIsol345AVlv->ConnectInput( pBundle, 0 );
		RRCSOxidTankIsol345AVlv->ConnectInput( pBundle, 1 );
		RRCSFuelTankIsol345BVlv->ConnectInput( pBundle, 2 );
		RRCSOxidTankIsol345BVlv->ConnectInput( pBundle, 3 );
		RRCSFuelTankIsol345AVlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		RRCSFuelTankIsol345AVlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		RRCSOxidTankIsol345AVlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		RRCSOxidTankIsol345AVlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		RRCSFuelTankIsol345BVlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		RRCSFuelTankIsol345BVlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		RRCSOxidTankIsol345BVlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		RRCSOxidTankIsol345BVlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		R_FU_TK_ISO_V_345_A_OP.Connect( pBundle, 4 );
		R_FU_TK_ISO_V_345_A_CL.Connect( pBundle, 5 );
		R_OX_TK_ISO_V_345_A_OP.Connect( pBundle, 6 );
		R_OX_TK_ISO_V_345_A_CL.Connect( pBundle, 7 );
		R_FU_TK_ISO_V_345_B_OP.Connect( pBundle, 8 );
		R_FU_TK_ISO_V_345_B_CL.Connect( pBundle, 9 );
		R_OX_TK_ISO_V_345_B_OP.Connect( pBundle, 10 );
		R_OX_TK_ISO_V_345_B_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_12_ISOL", 12 );
		RRCSFuelManifIsol1Vlv->ConnectInput( pBundle, 0 );
		RRCSOxidManifIsol1Vlv->ConnectInput( pBundle, 1 );
		RRCSFuelManifIsol1Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		RRCSFuelManifIsol1Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		RRCSOxidManifIsol1Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		RRCSOxidManifIsol1Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		RRCSFuelManifIsol2Vlv->ConnectInput( pBundle, 6 );
		RRCSOxidManifIsol2Vlv->ConnectInput( pBundle, 7 );
		RRCSFuelManifIsol2Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		RRCSFuelManifIsol2Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		RRCSOxidManifIsol2Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		RRCSOxidManifIsol2Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		R_FU_MANF_ISOV_1_OP.Connect( pBundle, 2 );
		R_FU_MANF_ISOV_1_CL.Connect( pBundle, 3 );
		R_OX_MANF_ISOV_1_OP.Connect( pBundle, 4 );
		R_OX_MANF_ISOV_1_CL.Connect( pBundle, 5 );
		R_FU_MANF_ISOV_2_OP.Connect( pBundle, 8 );
		R_FU_MANF_ISOV_2_CL.Connect( pBundle, 9 );
		R_OX_MANF_ISOV_2_OP.Connect( pBundle, 10 );
		R_OX_MANF_ISOV_2_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_34_ISOL", 12 );
		RRCSFuelManifIsol3Vlv->ConnectInput( pBundle, 0 );
		RRCSOxidManifIsol3Vlv->ConnectInput( pBundle, 1 );
		RRCSFuelManifIsol3Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		RRCSFuelManifIsol3Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		RRCSOxidManifIsol3Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		RRCSOxidManifIsol3Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		RRCSFuelManifIsol4Vlv->ConnectInput( pBundle, 6 );
		RRCSOxidManifIsol4Vlv->ConnectInput( pBundle, 7 );
		RRCSFuelManifIsol4Vlv->ConnectPositionSensor( 0, true, pBundle, 8 );
		RRCSFuelManifIsol4Vlv->ConnectPositionSensor( 0, false, pBundle, 9 );
		RRCSOxidManifIsol4Vlv->ConnectPositionSensor( 0, true, pBundle, 10 );
		RRCSOxidManifIsol4Vlv->ConnectPositionSensor( 0, false, pBundle, 11 );
		R_FU_MANF_ISOV_3_OP.Connect( pBundle, 2 );
		R_FU_MANF_ISOV_3_CL.Connect( pBundle, 3 );
		R_OX_MANF_ISOV_3_OP.Connect( pBundle, 4 );
		R_OX_MANF_ISOV_3_CL.Connect( pBundle, 5 );
		R_FU_MANF_ISOV_4_OP.Connect( pBundle, 8 );
		R_FU_MANF_ISOV_4_CL.Connect( pBundle, 9 );
		R_OX_MANF_ISOV_4_OP.Connect( pBundle, 10 );
		R_OX_MANF_ISOV_4_CL.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_5_ISOL", 8 );
		RRCSFuelManifIsol5Vlv->ConnectInput( 0, true, pBundle, 0 );
		RRCSFuelManifIsol5Vlv->ConnectInput( 0, false, pBundle, 1 );
		RRCSOxidManifIsol5Vlv->ConnectInput( 0, true, pBundle, 2 );
		RRCSOxidManifIsol5Vlv->ConnectInput( 0, false, pBundle, 3 );
		RRCSFuelManifIsol5Vlv->ConnectPositionSensor( 0, true, pBundle, 4 );
		RRCSFuelManifIsol5Vlv->ConnectPositionSensor( 0, false, pBundle, 5 );
		RRCSOxidManifIsol5Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		RRCSOxidManifIsol5Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		R_FU_MANF_ISOV_NO_5_POWER_OP.Connect( pBundle, 0 );
		R_FU_MANF_ISOV_NO_5_POWER_CL.Connect( pBundle, 1 );
		R_OX_MANF_ISOV_NO_5_POWER_OP.Connect( pBundle, 2 );
		R_OX_MANF_ISOV_NO_5_POWER_CL.Connect( pBundle, 3 );
		R_FU_MANF_ISOV_5_OP.Connect( pBundle, 4 );
		R_FU_MANF_ISOV_5_CL.Connect( pBundle, 5 );
		R_OX_MANF_ISOV_5_OP.Connect( pBundle, 6 );
		R_OX_MANF_ISOV_5_CL.Connect( pBundle, 7 );
		
		pBundle = BundleManager()->CreateBundle( "RRCS_XFD_12", 10 );
		RRCSFuelCrossfeed12Vlv->ConnectInput( pBundle, 0 );
		RRCSOxidCrossfeed12Vlv->ConnectInput( pBundle, 1 );
		RRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		RRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		RRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		RRCSFuelCrossfeed12Vlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		RRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		RRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		RRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		RRCSOxidCrossfeed12Vlv->ConnectPositionSensor( 1, false, pBundle, 9 );
		R_RCS_FU_XFD_12_OP_1.Connect( pBundle, 2 );
		R_RCS_FU_XFD_12_CL_1.Connect( pBundle, 3 );
		R_RCS_OX_XFD_12_OP_1.Connect( pBundle, 6 );
		R_RCS_OX_XFD_12_CL_1.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "RRCS_XFD_345", 10 );
		RRCSFuelCrossfeed345Vlv->ConnectInput( pBundle, 0 );
		RRCSOxidCrossfeed345Vlv->ConnectInput( pBundle, 1 );
		RRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 0, true, pBundle, 2 );
		RRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 0, false, pBundle, 3 );
		RRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 1, true, pBundle, 4 );
		RRCSFuelCrossfeed345Vlv->ConnectPositionSensor( 1, false, pBundle, 5 );
		RRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 0, true, pBundle, 6 );
		RRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 0, false, pBundle, 7 );
		RRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 1, true, pBundle, 8 );
		RRCSOxidCrossfeed345Vlv->ConnectPositionSensor( 1, false, pBundle, 9 );
		R_RCS_FU_XFD_345_OP_1.Connect( pBundle, 2 );
		R_RCS_FU_XFD_345_CL_1.Connect( pBundle, 3 );
		R_RCS_OX_XFD_345_OP_1.Connect( pBundle, 6 );
		R_RCS_OX_XFD_345_CL_1.Connect( pBundle, 7 );


		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_HePress_TankIsol_SW", 16 );
		FWD_RCS_HE_PRESS_A_SW_OPEN.Connect( pBundle, 0 );
		FWD_RCS_HE_PRESS_A_SW_CLOSE.Connect( pBundle, 1 );
		FWD_RCS_HE_PRESS_B_SW_OPEN.Connect( pBundle, 2 );
		FWD_RCS_HE_PRESS_B_SW_CLOSE.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_HePress_TankIsol_TB", 16 );
		FWD_RCS_HE_PRESS_A_TB_OPEN.Connect( pBundle, 0 );
		FWD_RCS_HE_PRESS_A_TB_CLOSE.Connect( pBundle, 1 );
		FWD_RCS_HE_PRESS_B_TB_OPEN.Connect( pBundle, 2 );
		FWD_RCS_HE_PRESS_B_TB_CLOSE.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_ManifIsol_SW", 16 );
		FWD_RCS_MANIFOLD_ISOLATION_SW_OPEN.Connect( pBundle, 8 );
		FWD_RCS_MANIFOLD_ISOLATION_SW_CLOSE.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_ManifIsol_TB", 16 );
		FWD_RCS_MANIFOLD_ISOLATION_TB_OPEN.Connect( pBundle, 8 );
		FWD_RCS_MANIFOLD_ISOLATION_TB_CLOSE.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_SW", 16 );
		AFT_LEFT_RCS_HE_PRESS_A_SW_OPEN.Connect( pBundle, 0 );
		AFT_LEFT_RCS_HE_PRESS_A_SW_CLOSE.Connect( pBundle, 1 );
		AFT_LEFT_RCS_HE_PRESS_B_SW_OPEN.Connect( pBundle, 2 );
		AFT_LEFT_RCS_HE_PRESS_B_SW_CLOSE.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_TB", 16 );
		AFT_LEFT_RCS_HE_PRESS_A_TB_OPEN.Connect( pBundle, 0 );
		AFT_LEFT_RCS_HE_PRESS_A_TB_CLOSE.Connect( pBundle, 1 );
		AFT_LEFT_RCS_HE_PRESS_B_TB_OPEN.Connect( pBundle, 2 );
		AFT_LEFT_RCS_HE_PRESS_B_TB_CLOSE.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_ManifIsol_SW", 16 );
		AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_OPEN.Connect( pBundle, 8 );
		AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_CLOSE.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_ManifIsol_TB", 16 );
		AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_OPEN.Connect( pBundle, 8 );
		AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_CLOSE.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_SW", 16 );
		AFT_RIGHT_RCS_HE_PRESS_A_SW_OPEN.Connect( pBundle, 0 );
		AFT_RIGHT_RCS_HE_PRESS_A_SW_CLOSE.Connect( pBundle, 1 );
		AFT_RIGHT_RCS_HE_PRESS_B_SW_OPEN.Connect( pBundle, 2 );
		AFT_RIGHT_RCS_HE_PRESS_B_SW_CLOSE.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_TB", 16 );
		AFT_RIGHT_RCS_HE_PRESS_A_TB_OPEN.Connect( pBundle, 0 );
		AFT_RIGHT_RCS_HE_PRESS_A_TB_CLOSE.Connect( pBundle, 1 );
		AFT_RIGHT_RCS_HE_PRESS_B_TB_OPEN.Connect( pBundle, 2 );
		AFT_RIGHT_RCS_HE_PRESS_B_TB_CLOSE.Connect( pBundle, 3 );

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_ManifIsol_SW", 16 );
		AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_OPEN.Connect( pBundle, 8 );
		AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_CLOSE.Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_ManifIsol_TB", 16 );
		AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_OPEN.Connect( pBundle, 8 );
		AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_CLOSE.Connect( pBundle, 9 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH0", 16 );
		F_MANF_ISOL_5_OP_B.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM4_CH0", 16 );
		F_FU_MANF_ISOV_1_OP_TM.Connect( pBundle, 7 );
		F_FU_MANF_ISOV_1_CL_TM.Connect( pBundle, 8 );
		F_FU_TK_ISOV_345_OP_TM.Connect( pBundle, 9 );
		F_FU_TK_ISOV_345_CL_TM.Connect( pBundle, 10 );
		F_HE_FU_PRESS_V_A_OP_TM.Connect( pBundle, 11 );
		F_HE_FU_PRESS_V_A_CL_TM.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH0", 16 );
		F_MANF_ISOL_5_CL_A.Connect( pBundle, 12 );
		F_HE_PR_VLV_A_OP_A.Connect( pBundle, 13 );
		F_HE_PR_VLV_A_CL_A.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM12_CH0", 16 );
		F_OX_MANF_ISOV_1_OP_TM.Connect( pBundle, 7 );
		F_OX_MANF_ISOV_1_CL_TM.Connect( pBundle, 8 );
		F_HE_OX_PRESS_V_A_OP_TM.Connect( pBundle, 9 );
		F_HE_OX_PRESS_V_A_CL_TM.Connect( pBundle, 10 );
		F_OX_TK_ISOV_345_OP_TM.Connect( pBundle, 11 );
		F_OX_TK_ISOV_345_CL_TM.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM2_CH0", 16 );
		F_MANF_ISOL_5_CL_C.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM4_CH0", 16 );
		F_FU_MANF_ISOV_2_OP_TM.Connect( pBundle, 7 );
		F_FU_MANF_ISOV_2_CL_TM.Connect( pBundle, 8 );
		F_HE_FU_PRESS_V_B_OP_TM.Connect( pBundle, 9 );
		F_HE_FU_PRESS_V_B_CL_TM.Connect( pBundle, 10 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM10_CH0", 16 );
		F_MANF_ISOL_5_OP_C.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM12_CH0", 16 );
		F_OX_MANF_ISOV_2_OP_TM.Connect( pBundle, 7 );
		F_OX_MANF_ISOV_2_CL_TM.Connect( pBundle, 8 );
		F_HE_OX_PRESS_V_B_OP_TM.Connect( pBundle, 9 );
		F_HE_OX_PRESS_V_B_CL_TM.Connect( pBundle, 10 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH0", 16 );
		F_MANF_ISOL_5_CL_B.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM4_CH0", 16 );
		F_FU_MANF_ISOV_4_OP_TM.Connect( pBundle, 7 );
		F_FU_MANF_ISOV_4_CL_TM.Connect( pBundle, 8 );
		F_FU_TK_ISOV_12_OP_TM.Connect( pBundle, 9 );
		F_FU_TK_ISOV_12_CL_TM.Connect( pBundle, 10 );
		F_FU_MANF_ISOV_5_OP_TM.Connect( pBundle, 11 );
		F_FU_MANF_ISOV_5_CL_TM.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH0", 16 );
		F_MANF_ISOL_5_OP_A.Connect( pBundle, 12 );
		F_HE_PR_VLV_B_OP_A.Connect( pBundle, 13 );
		F_HE_PR_VLV_B_CL_A.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM12_CH0", 16 );
		F_OX_MANF_ISOV_4_OP_TM.Connect( pBundle, 7 );
		F_OX_MANF_ISOV_4_CL_TM.Connect( pBundle, 8 );
		F_OX_TK_ISOV_12_OP_TM.Connect( pBundle, 9 );
		F_OX_TK_ISOV_12_CL_TM.Connect( pBundle, 10 );
		F_OX_MANF_ISOV_5_OP_TM.Connect( pBundle, 11 );
		F_OX_MANF_ISOV_5_CL_TM.Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM4_CH0", 16 );
		F_FU_MANF_ISOV_3_OP_TM.Connect( pBundle, 7 );
		F_FU_MANF_ISOV_3_CL_TM.Connect( pBundle, 8 );

		pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM12_CH0", 16 );
		F_OX_MANF_ISOV_3_OP_TM.Connect( pBundle, 7 );
		F_OX_MANF_ISOV_3_CL_TM.Connect( pBundle, 8 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM3_CH2", 16 );
		R_FU_MANF_ISOV_1_OP_TM.Connect( pBundle, 0 );
		R_FU_MANF_ISOV_1_CL_TM.Connect( pBundle, 1 );
		R_OX_MANF_ISOV_1_OP_TM.Connect( pBundle, 2 );
		R_OX_MANF_ISOV_1_CL_TM.Connect( pBundle, 3 );
		R_RCS_OX_XFD_345_OP_TM.Connect( pBundle, 4 );
		R_RCS_OX_XFD_345_CL_TM.Connect( pBundle, 5 );
		R_RCS_FU_XFD_345_OP_TM.Connect( pBundle, 6 );
		R_RCS_FU_XFD_345_CL_TM.Connect( pBundle, 7 );
		R_HE_OX_PRESS_V_A_OP_TM.Connect( pBundle, 8 );
		R_HE_OX_PRESS_V_A_CL_TM.Connect( pBundle, 9 );
		R_HE_FU_PRESS_V_A_OP_TM.Connect( pBundle, 10 );
		R_HE_FU_PRESS_V_A_CL_TM.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH2", 16 );
		L_HE_PR_VLV_A_OP_A.Connect( pBundle, 9 );
		L_HE_PR_VLV_A_CL_A.Connect( pBundle, 10 );
		L_MANF_ISO_5_OPEN_A.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM11_CH2", 16 );
		L_FU_MANF_ISOV_1_OP_TM.Connect( pBundle, 0 );
		L_FU_MANF_ISOV_1_CL_TM.Connect( pBundle, 1 );
		L_OX_MANF_ISOV_1_OP_TM.Connect( pBundle, 2 );
		L_OX_MANF_ISOV_1_CL_TM.Connect( pBundle, 3 );
		L_OX_TK_ISO_V_12_OP_TM.Connect( pBundle, 4 );
		L_OX_TK_ISO_V_12_CL_TM.Connect( pBundle, 5 );
		L_FU_TK_ISO_V_12_OP_TM.Connect( pBundle, 6 );
		L_FU_TK_ISO_V_12_CL_TM.Connect( pBundle, 7 );
		L_HE_OX_PRESS_V_A_OP_TM.Connect( pBundle, 8 );
		L_HE_OX_PRESS_V_A_CL_TM.Connect( pBundle, 9 );
		L_HE_FU_PRESS_V_A_OP_TM.Connect( pBundle, 10 );
		L_HE_FU_PRESS_V_A_CL_TM.Connect( pBundle, 11 );
		L_OX_MANF_ISOV_5_OP_TM.Connect( pBundle, 12 );
		L_FU_MANF_ISOV_5_OP_TM.Connect( pBundle, 13 );
		L_OX_MANF_ISOV_5_CL_TM.Connect( pBundle, 14 );
		L_FU_MANF_ISOV_5_CL_TM.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM15_CH2", 16 );
		R_HE_PR_VLV_A_OP_A.Connect( pBundle, 9 );
		R_HE_PR_VLV_A_CL_A.Connect( pBundle, 10 );
		R_MANF_ISO_5_CLOSE_A.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM3_CH2", 16 );
		R_FU_MANF_ISOV_3_OP_TM.Connect( pBundle, 0 );
		R_FU_MANF_ISOV_3_CL_TM.Connect( pBundle, 1 );
		R_OX_MANF_ISOV_3_OP_TM.Connect( pBundle, 2 );
		R_OX_MANF_ISOV_3_CL_TM.Connect( pBundle, 3 );
		R_OX_TK_ISO_V_12_OP_TM.Connect( pBundle, 4 );
		R_OX_TK_ISO_V_12_CL_TM.Connect( pBundle, 5 );
		R_FU_TK_ISO_V_12_OP_TM.Connect( pBundle, 6 );
		R_FU_TK_ISO_V_12_CL_TM.Connect( pBundle, 7 );
		R_HE_OX_PRESS_V_B_OP_TM.Connect( pBundle, 8 );
		R_HE_OX_PRESS_V_B_CL_TM.Connect( pBundle, 9 );
		R_HE_FU_PRESS_V_B_OP_TM.Connect( pBundle, 10 );
		R_HE_FU_PRESS_V_B_CL_TM.Connect( pBundle, 11 );
		R_OX_MANF_ISOV_5_OP_TM.Connect( pBundle, 12 );
		R_FU_MANF_ISOV_5_OP_TM.Connect( pBundle, 13 );
		R_OX_MANF_ISOV_5_CL_TM.Connect( pBundle, 14 );
		R_FU_MANF_ISOV_5_CL_TM.Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM7_CH2", 16 );
		L_HE_PR_VLV_B_OP_A.Connect( pBundle, 9 );
		L_HE_PR_VLV_B_CL_A.Connect( pBundle, 10 );
		L_MANF_ISO_5_CLOSE_A.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM11_CH2", 16 );
		L_FU_MANF_ISOV_3_OP_TM.Connect( pBundle, 0 );
		L_FU_MANF_ISOV_3_CL_TM.Connect( pBundle, 1 );
		L_OX_MANF_ISOV_3_OP_TM.Connect( pBundle, 2 );
		L_OX_MANF_ISOV_3_CL_TM.Connect( pBundle, 3 );
		L_RCS_OX_XFD_345_OP_TM.Connect( pBundle, 4 );
		L_RCS_OX_XFD_345_CL_TM.Connect( pBundle, 5 );
		L_RCS_FU_XFD_345_OP_TM.Connect( pBundle, 6 );
		L_RCS_FU_XFD_345_CL_TM.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM15_CH2", 16 );
		R_HE_PR_VLV_B_OP_A.Connect( pBundle, 9 );
		R_HE_PR_VLV_B_CL_A.Connect( pBundle, 10 );
		R_MANF_ISO_5_OPEN_A.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM3_CH2", 16 );
		R_FU_MANF_ISOV_2_OP_TM.Connect( pBundle, 0 );
		R_FU_MANF_ISOV_2_CL_TM.Connect( pBundle, 1 );
		R_OX_MANF_ISOV_2_OP_TM.Connect( pBundle, 2 );
		R_OX_MANF_ISOV_2_CL_TM.Connect( pBundle, 3 );
		R_OX_TK_ISO_V_345_A_OP_TM.Connect( pBundle, 4 );
		R_OX_TK_ISO_V_345_A_CL_TM.Connect( pBundle, 5 );
		R_FU_TK_ISO_V_345_A_OP_TM.Connect( pBundle, 6 );
		R_FU_TK_ISO_V_345_A_CL_TM.Connect( pBundle, 7 );
		L_RCS_OX_XFD_12_OP_TM.Connect( pBundle, 8 );
		L_RCS_OX_XFD_12_CL_TM.Connect( pBundle, 9 );
		L_RCS_FU_XFD_12_OP_TM.Connect( pBundle, 10 );
		L_RCS_FU_XFD_12_CL_TM.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM7_CH2", 16 );
		R_MANF_ISO_5_OPEN_B.Connect( pBundle, 9 );
		R_MANF_ISO_5_CLOSE_B.Connect( pBundle, 10 );
		L_MANF_ISO_5_OPEN_B.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM11_CH2", 16 );
		L_FU_MANF_ISOV_2_OP_TM.Connect( pBundle, 0 );
		L_FU_MANF_ISOV_2_CL_TM.Connect( pBundle, 1 );
		L_OX_MANF_ISOV_2_OP_TM.Connect( pBundle, 2 );
		L_OX_MANF_ISOV_2_CL_TM.Connect( pBundle, 3 );
		L_OX_TK_ISO_V_345_A_OP_TM.Connect( pBundle, 4 );
		L_OX_TK_ISO_V_345_A_CL_TM.Connect( pBundle, 5 );
		L_FU_TK_ISO_V_345_A_OP_TM.Connect( pBundle, 6 );
		L_FU_TK_ISO_V_345_A_CL_TM.Connect( pBundle, 7 );
		L_HE_OX_PRESS_V_B_OP_TM.Connect( pBundle, 8 );
		L_HE_OX_PRESS_V_B_CL_TM.Connect( pBundle, 9 );
		L_HE_FU_PRESS_V_B_OP_TM.Connect( pBundle, 10 );
		L_HE_FU_PRESS_V_B_CL_TM.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM15_CH2", 16 );
		L_MANF_ISO_5_CLOSE_B.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM3_CH2", 16 );
		R_FU_MANF_ISOV_4_OP_TM.Connect( pBundle, 0 );
		R_FU_MANF_ISOV_4_CL_TM.Connect( pBundle, 1 );
		R_OX_MANF_ISOV_4_OP_TM.Connect( pBundle, 2 );
		R_OX_MANF_ISOV_4_CL_TM.Connect( pBundle, 3 );
		R_OX_TK_ISO_V_345_B_OP_TM.Connect( pBundle, 4 );
		R_OX_TK_ISO_V_345_B_CL_TM.Connect( pBundle, 5 );
		R_FU_TK_ISO_V_345_B_OP_TM.Connect( pBundle, 6 );
		R_FU_TK_ISO_V_345_B_CL_TM.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM7_CH2", 16 );
		L_MANF_ISO_5_OPEN_C.Connect( pBundle, 9 );
		L_MANF_ISO_5_CLOSE_C.Connect( pBundle, 10 );
		R_MANF_ISO_5_OPEN_C.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM11_CH2", 16 );
		L_FU_MANF_ISOV_4_OP_TM.Connect( pBundle, 0 );
		L_FU_MANF_ISOV_4_CL_TM.Connect( pBundle, 1 );
		L_OX_MANF_ISOV_4_OP_TM.Connect( pBundle, 2 );
		L_OX_MANF_ISOV_4_CL_TM.Connect( pBundle, 3 );
		L_OX_TK_ISO_V_345_B_OP_TM.Connect( pBundle, 4 );
		L_OX_TK_ISO_V_345_B_CL_TM.Connect( pBundle, 5 );
		L_FU_TK_ISO_V_345_B_OP_TM.Connect( pBundle, 6 );
		L_FU_TK_ISO_V_345_B_CL_TM.Connect( pBundle, 7 );
		R_RCS_OX_XFD_12_OP_TM.Connect( pBundle, 8 );
		R_RCS_OX_XFD_12_CL_TM.Connect( pBundle, 9 );
		R_RCS_FU_XFD_12_OP_TM.Connect( pBundle, 10 );
		R_RCS_FU_XFD_12_CL_TM.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM15_CH2", 16 );
		R_MANF_ISO_5_CLOSE_C.Connect( pBundle, 11 );
		return;
	}

	bool RCS::OnParseLine( const char* line )
	{
		return vman.OnParseLine( line );
	}

	void RCS::OnSaveState( FILEHANDLE scn ) const
	{
		vman.OnSaveState( scn );
		return;
	}

	void RCS::OnPreStep( double simt, double simdt, double mjd )
	{
		// solenoid valves driver logic
		// FRCS He Press A
		{
			bool cl_c = !FWD_RCS_HE_PRESS_A_SW_OPEN && !(F_HE_FU_PRESS_V_A_CL && F_HE_OX_PRESS_V_A_CL);
			bool cl_p = FWD_RCS_HE_PRESS_A_SW_CLOSE || F_HE_PR_VLV_A_CL_A.IsSet( 26.0f );

			bool op_man = FWD_RCS_HE_PRESS_A_SW_OPEN && !(F_HE_FU_PRESS_V_A_OP && F_HE_OX_PRESS_V_A_OP);
			bool op_gpc = F_HE_PR_VLV_A_OP_A.IsSet( 26.0f ) && !cl_p;

			if (op_man || op_gpc)
			{
				FWD_HE_FU_ISOV_A_POWER_OP.SetLine( 5.0f );
				FWD_HE_OX_ISOV_A_POWER_OP.SetLine( 5.0f );
			}
			else
			{
				FWD_HE_FU_ISOV_A_POWER_OP.SetLine( 0.0f );
				FWD_HE_OX_ISOV_A_POWER_OP.SetLine( 0.0f );
			}
			if (cl_c && cl_p)
			{
				FWD_HE_FU_ISOV_A_POWER_CL.SetLine( 5.0f );
				FWD_HE_OX_ISOV_A_POWER_CL.SetLine( 5.0f );
			}
			else
			{
				FWD_HE_FU_ISOV_A_POWER_CL.SetLine( 0.0f );
				FWD_HE_OX_ISOV_A_POWER_CL.SetLine( 0.0f );
			}

			if (F_HE_FU_PRESS_V_A_OP && F_HE_OX_PRESS_V_A_OP) FWD_RCS_HE_PRESS_A_TB_OPEN.SetLine();
			else FWD_RCS_HE_PRESS_A_TB_OPEN.ResetLine();
			if (F_HE_FU_PRESS_V_A_CL && F_HE_OX_PRESS_V_A_CL) FWD_RCS_HE_PRESS_A_TB_CLOSE.SetLine();
			else FWD_RCS_HE_PRESS_A_TB_CLOSE.ResetLine();

			if (F_HE_FU_PRESS_V_A_OP) F_HE_FU_PRESS_V_A_OP_TM.SetLine( 28.0f );
			else F_HE_FU_PRESS_V_A_OP_TM.ResetLine();
			if (F_HE_FU_PRESS_V_A_CL) F_HE_FU_PRESS_V_A_CL_TM.SetLine( 28.0f );
			else F_HE_FU_PRESS_V_A_CL_TM.ResetLine();
			if (F_HE_OX_PRESS_V_A_OP) F_HE_OX_PRESS_V_A_OP_TM.SetLine( 28.0f );
			else F_HE_OX_PRESS_V_A_OP_TM.ResetLine();
			if (F_HE_OX_PRESS_V_A_CL) F_HE_OX_PRESS_V_A_CL_TM.SetLine( 28.0f );
			else F_HE_OX_PRESS_V_A_CL_TM.ResetLine();
		}

		// FRCS He Press B
		{
			bool cl_c = !FWD_RCS_HE_PRESS_B_SW_OPEN && !(F_HE_FU_PRESS_V_B_CL && F_HE_OX_PRESS_V_B_CL);
			bool cl_p = FWD_RCS_HE_PRESS_B_SW_CLOSE || F_HE_PR_VLV_B_CL_A.IsSet( 26.0f );

			bool op_man = FWD_RCS_HE_PRESS_B_SW_OPEN && !(F_HE_FU_PRESS_V_B_OP && F_HE_OX_PRESS_V_B_OP);
			bool op_gpc = F_HE_PR_VLV_B_OP_A.IsSet( 26.0f ) && !cl_p;

			if (op_man || op_gpc)
			{
				FWD_HE_FU_ISOV_B_POWER_OP.SetLine( 5.0f );
				FWD_HE_OX_ISOV_B_POWER_OP.SetLine( 5.0f );
			}
			else
			{
				FWD_HE_FU_ISOV_B_POWER_OP.SetLine( 0.0f );
				FWD_HE_OX_ISOV_B_POWER_OP.SetLine( 0.0f );
			}
			if (cl_c && cl_p)
			{
				FWD_HE_FU_ISOV_B_POWER_CL.SetLine( 5.0f );
				FWD_HE_OX_ISOV_B_POWER_CL.SetLine( 5.0f );
			}
			else
			{
				FWD_HE_FU_ISOV_B_POWER_CL.SetLine( 0.0f );
				FWD_HE_OX_ISOV_B_POWER_CL.SetLine( 0.0f );
			}

			if (F_HE_FU_PRESS_V_B_OP && F_HE_OX_PRESS_V_B_OP) FWD_RCS_HE_PRESS_B_TB_OPEN.SetLine();
			else FWD_RCS_HE_PRESS_B_TB_OPEN.ResetLine();
			if (F_HE_FU_PRESS_V_B_CL && F_HE_OX_PRESS_V_B_CL) FWD_RCS_HE_PRESS_B_TB_CLOSE.SetLine();
			else FWD_RCS_HE_PRESS_B_TB_CLOSE.ResetLine();

			if (F_HE_FU_PRESS_V_B_OP) F_HE_FU_PRESS_V_B_OP_TM.SetLine( 28.0f );
			else F_HE_FU_PRESS_V_B_OP_TM.ResetLine();
			if (F_HE_FU_PRESS_V_B_CL) F_HE_FU_PRESS_V_B_CL_TM.SetLine( 28.0f );
			else F_HE_FU_PRESS_V_B_CL_TM.ResetLine();
			if (F_HE_OX_PRESS_V_B_OP) F_HE_OX_PRESS_V_B_OP_TM.SetLine( 28.0f );
			else F_HE_OX_PRESS_V_B_OP_TM.ResetLine();
			if (F_HE_OX_PRESS_V_B_CL) F_HE_OX_PRESS_V_B_CL_TM.SetLine( 28.0f );
			else F_HE_OX_PRESS_V_B_CL_TM.ResetLine();
		}

		// FRCS Manif Isol 5
		{
			bool gnd = FWD_RCS_MANIFOLD_ISOLATION_SW_OPEN || FWD_RCS_MANIFOLD_ISOLATION_SW_CLOSE || F_MANF_ISOL_5_OP_C.IsSet( 26.0f ) || F_MANF_ISOL_5_CL_C.IsSet( 26.0f );
			if (gnd)
			{
				bool cl = ((FWD_RCS_MANIFOLD_ISOLATION_SW_CLOSE || F_MANF_ISOL_5_CL_B.IsSet( 26.0f )) && !(F_FU_MANF_ISOV_5_CL && F_OX_MANF_ISOV_5_CL)) && (FWD_RCS_MANIFOLD_ISOLATION_SW_CLOSE || F_MANF_ISOL_5_CL_A.IsSet( 26.0f ));
				bool op = ((FWD_RCS_MANIFOLD_ISOLATION_SW_OPEN || F_MANF_ISOL_5_OP_B.IsSet( 26.0f )) && !(F_FU_MANF_ISOV_5_OP && F_OX_MANF_ISOV_5_OP)) && ((FWD_RCS_MANIFOLD_ISOLATION_SW_OPEN || F_MANF_ISOL_5_OP_A.IsSet( 26.0f )) && !(FWD_RCS_MANIFOLD_ISOLATION_SW_CLOSE || F_MANF_ISOL_5_CL_A.IsSet( 26.0f )));

				if (op)
				{
					F_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 5.0f );
					F_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 5.0f );
				}
				else
				{
					F_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
					F_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				}
				if (cl)
				{
					F_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 5.0f );
					F_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 5.0f );
				}
				else
				{
					F_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
					F_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
				}
			}
			else
			{
				F_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				F_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
				F_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				F_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
			}

			if (F_FU_MANF_ISOV_5_OP && F_OX_MANF_ISOV_5_OP) FWD_RCS_MANIFOLD_ISOLATION_TB_OPEN.SetLine();
			else FWD_RCS_MANIFOLD_ISOLATION_TB_OPEN.ResetLine();
			if (F_FU_MANF_ISOV_5_CL && F_OX_MANF_ISOV_5_CL) FWD_RCS_MANIFOLD_ISOLATION_TB_CLOSE.SetLine();
			else FWD_RCS_MANIFOLD_ISOLATION_TB_CLOSE.ResetLine();

			if (F_FU_MANF_ISOV_5_OP) F_FU_MANF_ISOV_5_OP_TM.SetLine( 28.0f );
			else F_FU_MANF_ISOV_5_OP_TM.ResetLine();
			if (F_FU_MANF_ISOV_5_CL) F_FU_MANF_ISOV_5_CL_TM.SetLine( 28.0f );
			else F_FU_MANF_ISOV_5_CL_TM.ResetLine();
			if (F_OX_MANF_ISOV_5_OP) F_OX_MANF_ISOV_5_OP_TM.SetLine( 28.0f );
			else F_OX_MANF_ISOV_5_OP_TM.ResetLine();
			if (F_OX_MANF_ISOV_5_CL) F_OX_MANF_ISOV_5_CL_TM.SetLine( 28.0f );
			else F_OX_MANF_ISOV_5_CL_TM.ResetLine();
		}

		// LRCS Manif Isol 5
		{
			bool gnd = AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_OPEN || AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || L_MANF_ISO_5_OPEN_C.IsSet( 26.0f ) || L_MANF_ISO_5_CLOSE_C.IsSet( 26.0f );
			if (gnd)
			{
				bool cl = ((AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || L_MANF_ISO_5_CLOSE_B.IsSet( 26.0f )) && !(L_FU_MANF_ISOV_5_CL && L_OX_MANF_ISOV_5_CL)) && (AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || L_MANF_ISO_5_CLOSE_A.IsSet( 26.0f ));
				bool op = ((AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_OPEN || L_MANF_ISO_5_OPEN_B.IsSet( 26.0f )) && !(L_FU_MANF_ISOV_5_OP && L_OX_MANF_ISOV_5_OP)) && ((AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_OPEN || L_MANF_ISO_5_OPEN_A.IsSet( 26.0f )) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || L_MANF_ISO_5_CLOSE_A.IsSet( 26.0f )));

				if (op)
				{
					L_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 5.0f );
					L_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 5.0f );
				}
				else
				{
					L_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
					L_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				}
				if (cl)
				{
					L_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 5.0f );
					L_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 5.0f );
				}
				else
				{
					L_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
					L_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
				}
			}
			else
			{
				L_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				L_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
				L_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				L_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
			}

			if (L_FU_MANF_ISOV_5_OP && L_OX_MANF_ISOV_5_OP) AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_OPEN.SetLine();
			else AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_OPEN.ResetLine();
			if (L_FU_MANF_ISOV_5_CL && L_OX_MANF_ISOV_5_CL) AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_CLOSE.SetLine();
			else AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_CLOSE.ResetLine();

			if (L_FU_MANF_ISOV_5_OP) L_FU_MANF_ISOV_5_OP_TM.SetLine( 28.0f );
			else L_FU_MANF_ISOV_5_OP_TM.ResetLine();
			if (L_FU_MANF_ISOV_5_CL) L_FU_MANF_ISOV_5_CL_TM.SetLine( 28.0f );
			else L_FU_MANF_ISOV_5_CL_TM.ResetLine();
			if (L_OX_MANF_ISOV_5_OP) L_OX_MANF_ISOV_5_OP_TM.SetLine( 28.0f );
			else L_OX_MANF_ISOV_5_OP_TM.ResetLine();
			if (L_OX_MANF_ISOV_5_CL) L_OX_MANF_ISOV_5_CL_TM.SetLine( 28.0f );
			else L_OX_MANF_ISOV_5_CL_TM.ResetLine();
		}

		// LRCS He Press A
		{
			bool cl_c = !AFT_LEFT_RCS_HE_PRESS_A_SW_OPEN && !(L_HE_FU_PRESS_V_A_CL && L_HE_OX_PRESS_V_A_CL);
			bool cl_p = AFT_LEFT_RCS_HE_PRESS_A_SW_CLOSE || L_HE_PR_VLV_A_CL_A.IsSet( 26.0f );

			bool op_man = AFT_LEFT_RCS_HE_PRESS_A_SW_OPEN && !(L_HE_FU_PRESS_V_A_OP && L_HE_OX_PRESS_V_A_OP);
			bool op_gpc = L_HE_PR_VLV_A_OP_A.IsSet( 26.0f ) && !(AFT_LEFT_RCS_HE_PRESS_A_SW_CLOSE || L_HE_PR_VLV_A_CL_A.IsSet( 26.0f ));

			if (op_man || op_gpc)
			{
				LEFT_HE_FU_ISOV_A_POWER_OP.SetLine( 5.0f );
				LEFT_HE_OX_ISOV_A_POWER_OP.SetLine( 5.0f );
			}
			else
			{
				LEFT_HE_FU_ISOV_A_POWER_OP.SetLine( 0.0f );
				LEFT_HE_OX_ISOV_A_POWER_OP.SetLine( 0.0f );
			}
			if (cl_c && cl_p)
			{
				LEFT_HE_FU_ISOV_A_POWER_CL.SetLine( 5.0f );
				LEFT_HE_OX_ISOV_A_POWER_CL.SetLine( 5.0f );
			}
			else
			{
				LEFT_HE_FU_ISOV_A_POWER_CL.SetLine( 0.0f );
				LEFT_HE_OX_ISOV_A_POWER_CL.SetLine( 0.0f );
			}

			if (L_HE_FU_PRESS_V_A_OP && L_HE_OX_PRESS_V_A_OP) AFT_LEFT_RCS_HE_PRESS_A_TB_OPEN.SetLine();
			else AFT_LEFT_RCS_HE_PRESS_A_TB_OPEN.ResetLine();
			if (L_HE_FU_PRESS_V_A_CL && L_HE_OX_PRESS_V_A_CL) AFT_LEFT_RCS_HE_PRESS_A_TB_CLOSE.SetLine();
			else AFT_LEFT_RCS_HE_PRESS_A_TB_CLOSE.ResetLine();

			if (L_HE_FU_PRESS_V_A_OP) L_HE_FU_PRESS_V_A_OP_TM.SetLine( 28.0f );
			else L_HE_FU_PRESS_V_A_OP_TM.ResetLine();
			if (L_HE_FU_PRESS_V_A_CL) L_HE_FU_PRESS_V_A_CL_TM.SetLine( 28.0f );
			else L_HE_FU_PRESS_V_A_CL_TM.ResetLine();
			if (L_HE_OX_PRESS_V_A_OP) L_HE_OX_PRESS_V_A_OP_TM.SetLine( 28.0f );
			else L_HE_OX_PRESS_V_A_OP_TM.ResetLine();
			if (L_HE_OX_PRESS_V_A_CL) L_HE_OX_PRESS_V_A_CL_TM.SetLine( 28.0f );
			else L_HE_OX_PRESS_V_A_CL_TM.ResetLine();
		}

		// LRCS He Press B
		{
			bool cl_c = !AFT_LEFT_RCS_HE_PRESS_B_SW_OPEN && !(L_HE_FU_PRESS_V_B_CL && L_HE_OX_PRESS_V_B_CL);
			bool cl_p = AFT_LEFT_RCS_HE_PRESS_B_SW_CLOSE || L_HE_PR_VLV_B_CL_A.IsSet( 26.0f );

			bool op_man = AFT_LEFT_RCS_HE_PRESS_B_SW_OPEN && !(L_HE_FU_PRESS_V_B_OP && L_HE_OX_PRESS_V_B_OP);
			bool op_gpc = L_HE_PR_VLV_B_OP_A.IsSet( 26.0f ) && !(AFT_LEFT_RCS_HE_PRESS_B_SW_CLOSE || L_HE_PR_VLV_B_CL_A.IsSet( 26.0f ));

			if (op_man || op_gpc)
			{
				LEFT_HE_FU_ISOV_B_POWER_OP.SetLine( 5.0f );
				LEFT_HE_OX_ISOV_B_POWER_OP.SetLine( 5.0f );
			}
			else
			{
				LEFT_HE_FU_ISOV_B_POWER_OP.SetLine( 0.0f );
				LEFT_HE_OX_ISOV_B_POWER_OP.SetLine( 0.0f );
			}
			if (cl_c && cl_p)
			{
				LEFT_HE_FU_ISOV_B_POWER_CL.SetLine( 5.0f );
				LEFT_HE_OX_ISOV_B_POWER_CL.SetLine( 5.0f );
			}
			else
			{
				LEFT_HE_FU_ISOV_B_POWER_CL.SetLine( 0.0f );
				LEFT_HE_OX_ISOV_B_POWER_CL.SetLine( 0.0f );
			}

			if (L_HE_FU_PRESS_V_B_OP && L_HE_OX_PRESS_V_B_OP) AFT_LEFT_RCS_HE_PRESS_B_TB_OPEN.SetLine();
			else AFT_LEFT_RCS_HE_PRESS_B_TB_OPEN.ResetLine();
			if (L_HE_FU_PRESS_V_B_CL && L_HE_OX_PRESS_V_B_CL) AFT_LEFT_RCS_HE_PRESS_B_TB_CLOSE.SetLine();
			else AFT_LEFT_RCS_HE_PRESS_B_TB_CLOSE.ResetLine();

			if (L_HE_FU_PRESS_V_B_OP) L_HE_FU_PRESS_V_B_OP_TM.SetLine( 28.0f );
			else L_HE_FU_PRESS_V_B_OP_TM.ResetLine();
			if (L_HE_FU_PRESS_V_B_CL) L_HE_FU_PRESS_V_B_CL_TM.SetLine( 28.0f );
			else L_HE_FU_PRESS_V_B_CL_TM.ResetLine();
			if (L_HE_OX_PRESS_V_B_OP) L_HE_OX_PRESS_V_B_OP_TM.SetLine( 28.0f );
			else L_HE_OX_PRESS_V_B_OP_TM.ResetLine();
			if (L_HE_OX_PRESS_V_B_CL) L_HE_OX_PRESS_V_B_CL_TM.SetLine( 28.0f );
			else L_HE_OX_PRESS_V_B_CL_TM.ResetLine();
		}

		// RRCS Manif Isol 5
		{
			bool gnd = AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_OPEN || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || R_MANF_ISO_5_OPEN_C.IsSet( 26.0f ) || R_MANF_ISO_5_CLOSE_C.IsSet( 26.0f );
			if (gnd)
			{
				bool cl = ((AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || R_MANF_ISO_5_CLOSE_B.IsSet( 26.0f )) && !(R_FU_MANF_ISOV_5_CL & R_OX_MANF_ISOV_5_CL)) && (AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || R_MANF_ISO_5_CLOSE_A.IsSet( 26.0f ));
				bool op = ((AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_OPEN || R_MANF_ISO_5_OPEN_B.IsSet( 26.0f )) && !(R_FU_MANF_ISOV_5_OP & R_OX_MANF_ISOV_5_OP)) && ((AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_OPEN || R_MANF_ISO_5_OPEN_A.IsSet( 26.0f )) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_CLOSE || R_MANF_ISO_5_CLOSE_A.IsSet( 26.0f )));

				if (op)
				{
					R_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 5.0f );
					R_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 5.0f );
				}
				else
				{
					R_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
					R_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				}
				if (cl)
				{
					R_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 5.0f );
					R_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 5.0f );
				}
				else
				{
					R_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
					R_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
				}
			}
			else
			{
				R_FU_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				R_FU_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
				R_OX_MANF_ISOV_NO_5_POWER_OP.SetLine( 0.0f );
				R_OX_MANF_ISOV_NO_5_POWER_CL.SetLine( 0.0f );
			}

			if (R_FU_MANF_ISOV_5_OP && R_OX_MANF_ISOV_5_OP) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_OPEN.SetLine();
			else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_OPEN.ResetLine();
			if (R_FU_MANF_ISOV_5_CL && R_OX_MANF_ISOV_5_CL) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_CLOSE.SetLine();
			else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_CLOSE.ResetLine();

			if (R_FU_MANF_ISOV_5_OP) R_FU_MANF_ISOV_5_OP_TM.SetLine( 28.0f );
			else R_FU_MANF_ISOV_5_OP_TM.ResetLine();
			if (R_FU_MANF_ISOV_5_CL) R_FU_MANF_ISOV_5_CL_TM.SetLine( 28.0f );
			else R_FU_MANF_ISOV_5_CL_TM.ResetLine();
			if (R_OX_MANF_ISOV_5_OP) R_OX_MANF_ISOV_5_OP_TM.SetLine( 28.0f );
			else R_OX_MANF_ISOV_5_OP_TM.ResetLine();
			if (R_OX_MANF_ISOV_5_CL) R_OX_MANF_ISOV_5_CL_TM.SetLine( 28.0f );
			else R_OX_MANF_ISOV_5_CL_TM.ResetLine();
		}

		// RRCS He Press A
		{
			bool cl_c = !AFT_RIGHT_RCS_HE_PRESS_A_SW_OPEN && !(R_HE_FU_PRESS_V_A_CL && R_HE_OX_PRESS_V_A_CL);
			bool cl_p = AFT_RIGHT_RCS_HE_PRESS_A_SW_CLOSE || R_HE_PR_VLV_A_CL_A.IsSet( 26.0f );

			bool op_man = AFT_RIGHT_RCS_HE_PRESS_A_SW_OPEN && !(R_HE_FU_PRESS_V_A_OP && R_HE_OX_PRESS_V_A_OP);
			bool op_gpc = R_HE_PR_VLV_A_OP_A.IsSet( 26.0f ) && !(AFT_RIGHT_RCS_HE_PRESS_A_SW_CLOSE || R_HE_PR_VLV_A_CL_A.IsSet( 26.0f ));

			if (op_man || op_gpc)
			{
				RIGHT_HE_FU_ISOV_A_POWER_OP.SetLine( 5.0f );
				RIGHT_HE_OX_ISOV_A_POWER_OP.SetLine( 5.0f );
			}
			else
			{
				RIGHT_HE_FU_ISOV_A_POWER_OP.SetLine( 0.0f );
				RIGHT_HE_OX_ISOV_A_POWER_OP.SetLine( 0.0f );
			}
			if (cl_c && cl_p)
			{
				RIGHT_HE_FU_ISOV_A_POWER_CL.SetLine( 5.0f );
				RIGHT_HE_OX_ISOV_A_POWER_CL.SetLine( 5.0f );
			}
			else
			{
				RIGHT_HE_FU_ISOV_A_POWER_CL.SetLine( 0.0f );
				RIGHT_HE_OX_ISOV_A_POWER_CL.SetLine( 0.0f );
			}

			if (R_HE_FU_PRESS_V_A_OP && R_HE_OX_PRESS_V_A_OP) AFT_RIGHT_RCS_HE_PRESS_A_TB_OPEN.SetLine();
			else AFT_RIGHT_RCS_HE_PRESS_A_TB_OPEN.ResetLine();
			if (R_HE_FU_PRESS_V_A_CL && R_HE_OX_PRESS_V_A_CL) AFT_RIGHT_RCS_HE_PRESS_A_TB_CLOSE.SetLine();
			else AFT_RIGHT_RCS_HE_PRESS_A_TB_CLOSE.ResetLine();

			if (R_HE_FU_PRESS_V_A_OP) R_HE_FU_PRESS_V_A_OP_TM.SetLine( 28.0f );
			else R_HE_FU_PRESS_V_A_OP_TM.ResetLine();
			if (R_HE_FU_PRESS_V_A_CL) R_HE_FU_PRESS_V_A_CL_TM.SetLine( 28.0f );
			else R_HE_FU_PRESS_V_A_CL_TM.ResetLine();
			if (R_HE_OX_PRESS_V_A_OP) R_HE_OX_PRESS_V_A_OP_TM.SetLine( 28.0f );
			else R_HE_OX_PRESS_V_A_OP_TM.ResetLine();
			if (R_HE_OX_PRESS_V_A_CL) R_HE_OX_PRESS_V_A_CL_TM.SetLine( 28.0f );
			else R_HE_OX_PRESS_V_A_CL_TM.ResetLine();
		}

		// RRCS He Press B
		{
			bool cl_c = !AFT_RIGHT_RCS_HE_PRESS_B_SW_OPEN && !(R_HE_FU_PRESS_V_B_CL && R_HE_OX_PRESS_V_B_CL);
			bool cl_p = AFT_RIGHT_RCS_HE_PRESS_B_SW_CLOSE || R_HE_PR_VLV_B_CL_A.IsSet( 26.0f );

			bool op_man = AFT_RIGHT_RCS_HE_PRESS_B_SW_OPEN && !(R_HE_FU_PRESS_V_B_OP && R_HE_OX_PRESS_V_B_OP);
			bool op_gpc = R_HE_PR_VLV_B_OP_A.IsSet( 26.0f ) && !(AFT_RIGHT_RCS_HE_PRESS_B_SW_CLOSE || R_HE_PR_VLV_B_CL_A.IsSet( 26.0f ));

			if (op_man || op_gpc)
			{
				RIGHT_HE_FU_ISOV_B_POWER_OP.SetLine( 5.0f );
				RIGHT_HE_OX_ISOV_B_POWER_OP.SetLine( 5.0f );
			}
			else
			{
				RIGHT_HE_FU_ISOV_B_POWER_OP.SetLine( 0.0f );
				RIGHT_HE_OX_ISOV_B_POWER_OP.SetLine( 0.0f );
			}
			if (cl_c && cl_p)
			{
				RIGHT_HE_FU_ISOV_B_POWER_CL.SetLine( 5.0f );
				RIGHT_HE_OX_ISOV_B_POWER_CL.SetLine( 5.0f );
			}
			else
			{
				RIGHT_HE_FU_ISOV_B_POWER_CL.SetLine( 0.0f );
				RIGHT_HE_OX_ISOV_B_POWER_CL.SetLine( 0.0f );
			}

			if (R_HE_FU_PRESS_V_B_OP && R_HE_OX_PRESS_V_B_OP) AFT_RIGHT_RCS_HE_PRESS_B_TB_OPEN.SetLine();
			else AFT_RIGHT_RCS_HE_PRESS_B_TB_OPEN.ResetLine();
			if (R_HE_FU_PRESS_V_B_CL && R_HE_OX_PRESS_V_B_CL) AFT_RIGHT_RCS_HE_PRESS_B_TB_CLOSE.SetLine();
			else AFT_RIGHT_RCS_HE_PRESS_B_TB_CLOSE.ResetLine();

			if (R_HE_FU_PRESS_V_B_OP) R_HE_FU_PRESS_V_B_OP_TM.SetLine( 28.0f );
			else R_HE_FU_PRESS_V_B_OP_TM.ResetLine();
			if (R_HE_FU_PRESS_V_B_CL) R_HE_FU_PRESS_V_B_CL_TM.SetLine( 28.0f );
			else R_HE_FU_PRESS_V_B_CL_TM.ResetLine();
			if (R_HE_OX_PRESS_V_B_OP) R_HE_OX_PRESS_V_B_OP_TM.SetLine( 28.0f );
			else R_HE_OX_PRESS_V_B_OP_TM.ResetLine();
			if (R_HE_OX_PRESS_V_B_CL) R_HE_OX_PRESS_V_B_CL_TM.SetLine( 28.0f );
			else R_HE_OX_PRESS_V_B_CL_TM.ResetLine();
		}

		// tank isol valves position output
		if (F_FU_TK_ISOV_12_OP) F_FU_TK_ISOV_12_OP_TM.SetLine( 28.0f );
		else F_FU_TK_ISOV_12_OP_TM.ResetLine();

		if (F_FU_TK_ISOV_12_CL) F_FU_TK_ISOV_12_CL_TM.SetLine( 28.0f );
		else F_FU_TK_ISOV_12_CL_TM.ResetLine();

		if (F_OX_TK_ISOV_12_OP) F_OX_TK_ISOV_12_OP_TM.SetLine( 28.0f );
		else F_OX_TK_ISOV_12_OP_TM.ResetLine();

		if (F_OX_TK_ISOV_12_CL) F_OX_TK_ISOV_12_CL_TM.SetLine( 28.0f );
		else F_OX_TK_ISOV_12_CL_TM.ResetLine();

		if (F_FU_TK_ISOV_345_OP) F_FU_TK_ISOV_345_OP_TM.SetLine( 28.0f );
		else F_FU_TK_ISOV_345_OP_TM.ResetLine();

		if (F_FU_TK_ISOV_345_CL) F_FU_TK_ISOV_345_CL_TM.SetLine( 28.0f );
		else F_FU_TK_ISOV_345_CL_TM.ResetLine();

		if (F_OX_TK_ISOV_345_OP) F_OX_TK_ISOV_345_OP_TM.SetLine( 28.0f );
		else F_OX_TK_ISOV_345_OP_TM.ResetLine();

		if (F_OX_TK_ISOV_345_CL) F_OX_TK_ISOV_345_CL_TM.SetLine( 28.0f );
		else F_OX_TK_ISOV_345_CL_TM.ResetLine();

		if (L_FU_TK_ISO_V_12_OP_1) L_FU_TK_ISO_V_12_OP_TM.SetLine( 28.0f );
		else L_FU_TK_ISO_V_12_OP_TM.ResetLine();

		if (L_FU_TK_ISO_V_12_CL_1) L_FU_TK_ISO_V_12_CL_TM.SetLine( 28.0f );
		else L_FU_TK_ISO_V_12_CL_TM.ResetLine();

		if (L_OX_TK_ISO_V_12_OP_1) L_OX_TK_ISO_V_12_OP_TM.SetLine( 28.0f );
		else L_OX_TK_ISO_V_12_OP_TM.ResetLine();

		if (L_OX_TK_ISO_V_12_CL_1) L_OX_TK_ISO_V_12_CL_TM.SetLine( 28.0f );
		else L_OX_TK_ISO_V_12_CL_TM.ResetLine();

		if (L_FU_TK_ISO_V_345_A_OP) L_FU_TK_ISO_V_345_A_OP_TM.SetLine( 28.0f );
		else L_FU_TK_ISO_V_345_A_OP_TM.ResetLine();

		if (L_FU_TK_ISO_V_345_A_CL) L_FU_TK_ISO_V_345_A_CL_TM.SetLine( 28.0f );
		else L_FU_TK_ISO_V_345_A_CL_TM.ResetLine();

		if (L_OX_TK_ISO_V_345_A_OP) L_OX_TK_ISO_V_345_A_OP_TM.SetLine( 28.0f );
		else L_OX_TK_ISO_V_345_A_OP_TM.ResetLine();

		if (L_OX_TK_ISO_V_345_A_CL) L_OX_TK_ISO_V_345_A_CL_TM.SetLine( 28.0f );
		else L_OX_TK_ISO_V_345_A_CL_TM.ResetLine();

		if (L_FU_TK_ISO_V_345_B_OP) L_FU_TK_ISO_V_345_B_OP_TM.SetLine( 28.0f );
		else L_FU_TK_ISO_V_345_B_OP_TM.ResetLine();

		if (L_FU_TK_ISO_V_345_B_CL) L_FU_TK_ISO_V_345_B_CL_TM.SetLine( 28.0f );
		else L_FU_TK_ISO_V_345_B_CL_TM.ResetLine();

		if (L_OX_TK_ISO_V_345_B_OP) L_OX_TK_ISO_V_345_B_OP_TM.SetLine( 28.0f );
		else L_OX_TK_ISO_V_345_B_OP_TM.ResetLine();

		if (L_OX_TK_ISO_V_345_B_CL) L_OX_TK_ISO_V_345_B_CL_TM.SetLine( 28.0f );
		else L_OX_TK_ISO_V_345_B_CL_TM.ResetLine();

		if (R_FU_TK_ISO_V_12_OP_1) R_FU_TK_ISO_V_12_OP_TM.SetLine( 28.0f );
		else R_FU_TK_ISO_V_12_OP_TM.ResetLine();

		if (R_FU_TK_ISO_V_12_CL_1) R_FU_TK_ISO_V_12_CL_TM.SetLine( 28.0f );
		else R_FU_TK_ISO_V_12_CL_TM.ResetLine();

		if (R_OX_TK_ISO_V_12_OP_1) R_OX_TK_ISO_V_12_OP_TM.SetLine( 28.0f );
		else R_OX_TK_ISO_V_12_OP_TM.ResetLine();

		if (R_OX_TK_ISO_V_12_CL_1) R_OX_TK_ISO_V_12_CL_TM.SetLine( 28.0f );
		else R_OX_TK_ISO_V_12_CL_TM.ResetLine();

		if (R_FU_TK_ISO_V_345_A_OP) R_FU_TK_ISO_V_345_A_OP_TM.SetLine( 28.0f );
		else R_FU_TK_ISO_V_345_A_OP_TM.ResetLine();

		if (R_FU_TK_ISO_V_345_A_CL) R_FU_TK_ISO_V_345_A_CL_TM.SetLine( 28.0f );
		else R_FU_TK_ISO_V_345_A_CL_TM.ResetLine();

		if (R_OX_TK_ISO_V_345_A_OP) R_OX_TK_ISO_V_345_A_OP_TM.SetLine( 28.0f );
		else R_OX_TK_ISO_V_345_A_OP_TM.ResetLine();

		if (R_OX_TK_ISO_V_345_A_CL) R_OX_TK_ISO_V_345_A_CL_TM.SetLine( 28.0f );
		else R_OX_TK_ISO_V_345_A_CL_TM.ResetLine();

		if (R_FU_TK_ISO_V_345_B_OP) R_FU_TK_ISO_V_345_B_OP_TM.SetLine( 28.0f );
		else R_FU_TK_ISO_V_345_B_OP_TM.ResetLine();

		if (R_FU_TK_ISO_V_345_B_CL) R_FU_TK_ISO_V_345_B_CL_TM.SetLine( 28.0f );
		else R_FU_TK_ISO_V_345_B_CL_TM.ResetLine();

		if (R_OX_TK_ISO_V_345_B_OP) R_OX_TK_ISO_V_345_B_OP_TM.SetLine( 28.0f );
		else R_OX_TK_ISO_V_345_B_OP_TM.ResetLine();

		if (R_OX_TK_ISO_V_345_B_CL) R_OX_TK_ISO_V_345_B_CL_TM.SetLine( 28.0f );
		else R_OX_TK_ISO_V_345_B_CL_TM.ResetLine();


		// manif isol valves position output
		if (F_FU_MANF_ISOV_1_OP) F_FU_MANF_ISOV_1_OP_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_1_OP_TM.ResetLine();

		if (F_FU_MANF_ISOV_1_CL) F_FU_MANF_ISOV_1_CL_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_1_CL_TM.ResetLine();

		if (F_OX_MANF_ISOV_1_OP) F_OX_MANF_ISOV_1_OP_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_1_OP_TM.ResetLine();

		if (F_OX_MANF_ISOV_1_CL) F_OX_MANF_ISOV_1_CL_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_1_CL_TM.ResetLine();

		if (F_FU_MANF_ISOV_2_OP) F_FU_MANF_ISOV_2_OP_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_2_OP_TM.ResetLine();

		if (F_FU_MANF_ISOV_2_CL) F_FU_MANF_ISOV_2_CL_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_2_CL_TM.ResetLine();

		if (F_OX_MANF_ISOV_2_OP) F_OX_MANF_ISOV_2_OP_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_2_OP_TM.ResetLine();

		if (F_OX_MANF_ISOV_2_CL) F_OX_MANF_ISOV_2_CL_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_2_CL_TM.ResetLine();

		if (F_FU_MANF_ISOV_3_OP) F_FU_MANF_ISOV_3_OP_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_3_OP_TM.ResetLine();

		if (F_FU_MANF_ISOV_3_CL) F_FU_MANF_ISOV_3_CL_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_3_CL_TM.ResetLine();

		if (F_OX_MANF_ISOV_3_OP) F_OX_MANF_ISOV_3_OP_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_3_OP_TM.ResetLine();

		if (F_OX_MANF_ISOV_3_CL) F_OX_MANF_ISOV_3_CL_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_3_CL_TM.ResetLine();

		if (F_FU_MANF_ISOV_4_OP) F_FU_MANF_ISOV_4_OP_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_4_OP_TM.ResetLine();

		if (F_FU_MANF_ISOV_4_CL) F_FU_MANF_ISOV_4_CL_TM.SetLine( 28.0f );
		else F_FU_MANF_ISOV_4_CL_TM.ResetLine();

		if (F_OX_MANF_ISOV_4_OP) F_OX_MANF_ISOV_4_OP_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_4_OP_TM.ResetLine();

		if (F_OX_MANF_ISOV_4_CL) F_OX_MANF_ISOV_4_CL_TM.SetLine( 28.0f );
		else F_OX_MANF_ISOV_4_CL_TM.ResetLine();

		if (L_FU_MANF_ISOV_1_OP) L_FU_MANF_ISOV_1_OP_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_1_OP_TM.ResetLine();

		if (L_FU_MANF_ISOV_1_CL) L_FU_MANF_ISOV_1_CL_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_1_CL_TM.ResetLine();

		if (L_OX_MANF_ISOV_1_OP) L_OX_MANF_ISOV_1_OP_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_1_OP_TM.ResetLine();

		if (L_OX_MANF_ISOV_1_CL) L_OX_MANF_ISOV_1_CL_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_1_CL_TM.ResetLine();

		if (L_FU_MANF_ISOV_2_OP) L_FU_MANF_ISOV_2_OP_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_2_OP_TM.ResetLine();

		if (L_FU_MANF_ISOV_2_CL) L_FU_MANF_ISOV_2_CL_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_2_CL_TM.ResetLine();

		if (L_OX_MANF_ISOV_2_OP) L_OX_MANF_ISOV_2_OP_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_2_OP_TM.ResetLine();

		if (L_OX_MANF_ISOV_2_CL) L_OX_MANF_ISOV_2_CL_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_2_CL_TM.ResetLine();

		if (L_FU_MANF_ISOV_3_OP) L_FU_MANF_ISOV_3_OP_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_3_OP_TM.ResetLine();

		if (L_FU_MANF_ISOV_3_CL) L_FU_MANF_ISOV_3_CL_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_3_CL_TM.ResetLine();

		if (L_OX_MANF_ISOV_3_OP) L_OX_MANF_ISOV_3_OP_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_3_OP_TM.ResetLine();

		if (L_OX_MANF_ISOV_3_CL) L_OX_MANF_ISOV_3_CL_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_3_CL_TM.ResetLine();

		if (L_FU_MANF_ISOV_4_OP) L_FU_MANF_ISOV_4_OP_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_4_OP_TM.ResetLine();

		if (L_FU_MANF_ISOV_4_CL) L_FU_MANF_ISOV_4_CL_TM.SetLine( 28.0f );
		else L_FU_MANF_ISOV_4_CL_TM.ResetLine();

		if (L_OX_MANF_ISOV_4_OP) L_OX_MANF_ISOV_4_OP_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_4_OP_TM.ResetLine();

		if (L_OX_MANF_ISOV_4_CL) L_OX_MANF_ISOV_4_CL_TM.SetLine( 28.0f );
		else L_OX_MANF_ISOV_4_CL_TM.ResetLine();

		if (R_FU_MANF_ISOV_1_OP) R_FU_MANF_ISOV_1_OP_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_1_OP_TM.ResetLine();

		if (R_FU_MANF_ISOV_1_CL) R_FU_MANF_ISOV_1_CL_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_1_CL_TM.ResetLine();

		if (R_OX_MANF_ISOV_1_OP) R_OX_MANF_ISOV_1_OP_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_1_OP_TM.ResetLine();

		if (R_OX_MANF_ISOV_1_CL) R_OX_MANF_ISOV_1_CL_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_1_CL_TM.ResetLine();

		if (R_FU_MANF_ISOV_2_OP) R_FU_MANF_ISOV_2_OP_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_2_OP_TM.ResetLine();

		if (R_FU_MANF_ISOV_2_CL) R_FU_MANF_ISOV_2_CL_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_2_CL_TM.ResetLine();

		if (R_OX_MANF_ISOV_2_OP) R_OX_MANF_ISOV_2_OP_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_2_OP_TM.ResetLine();

		if (R_OX_MANF_ISOV_2_CL) R_OX_MANF_ISOV_2_CL_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_2_CL_TM.ResetLine();

		if (R_FU_MANF_ISOV_3_OP) R_FU_MANF_ISOV_3_OP_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_3_OP_TM.ResetLine();

		if (R_FU_MANF_ISOV_3_CL) R_FU_MANF_ISOV_3_CL_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_3_CL_TM.ResetLine();

		if (R_OX_MANF_ISOV_3_OP) R_OX_MANF_ISOV_3_OP_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_3_OP_TM.ResetLine();

		if (R_OX_MANF_ISOV_3_CL) R_OX_MANF_ISOV_3_CL_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_3_CL_TM.ResetLine();

		if (R_FU_MANF_ISOV_4_OP) R_FU_MANF_ISOV_4_OP_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_4_OP_TM.ResetLine();

		if (R_FU_MANF_ISOV_4_CL) R_FU_MANF_ISOV_4_CL_TM.SetLine( 28.0f );
		else R_FU_MANF_ISOV_4_CL_TM.ResetLine();

		if (R_OX_MANF_ISOV_4_OP) R_OX_MANF_ISOV_4_OP_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_4_OP_TM.ResetLine();

		if (R_OX_MANF_ISOV_4_CL) R_OX_MANF_ISOV_4_CL_TM.SetLine( 28.0f );
		else R_OX_MANF_ISOV_4_CL_TM.ResetLine();

		// crossfeed valves position output
		if (L_RCS_FU_XFD_12_OP_1) L_RCS_FU_XFD_12_OP_TM.SetLine( 28.0f );
		else L_RCS_FU_XFD_12_OP_TM.ResetLine();

		if (L_RCS_FU_XFD_12_CL_1) L_RCS_FU_XFD_12_CL_TM.SetLine( 28.0f );
		else L_RCS_FU_XFD_12_CL_TM.ResetLine();

		if (L_RCS_OX_XFD_12_OP_1) L_RCS_OX_XFD_12_OP_TM.SetLine( 28.0f );
		else L_RCS_OX_XFD_12_OP_TM.ResetLine();

		if (L_RCS_OX_XFD_12_CL_1) L_RCS_OX_XFD_12_CL_TM.SetLine( 28.0f );
		else L_RCS_OX_XFD_12_CL_TM.ResetLine();

		if (L_RCS_FU_XFD_345_OP_1) L_RCS_FU_XFD_345_OP_TM.SetLine( 28.0f );
		else L_RCS_FU_XFD_345_OP_TM.ResetLine();

		if (L_RCS_FU_XFD_345_CL_1) L_RCS_FU_XFD_345_CL_TM.SetLine( 28.0f );
		else L_RCS_FU_XFD_345_CL_TM.ResetLine();

		if (L_RCS_OX_XFD_345_OP_1) L_RCS_OX_XFD_345_OP_TM.SetLine( 28.0f );
		else L_RCS_OX_XFD_345_OP_TM.ResetLine();

		if (L_RCS_OX_XFD_345_CL_1) L_RCS_OX_XFD_345_CL_TM.SetLine( 28.0f );
		else L_RCS_OX_XFD_345_CL_TM.ResetLine();

		if (R_RCS_FU_XFD_12_OP_1) R_RCS_FU_XFD_12_OP_TM.SetLine( 28.0f );
		else R_RCS_FU_XFD_12_OP_TM.ResetLine();

		if (R_RCS_FU_XFD_12_CL_1) R_RCS_FU_XFD_12_CL_TM.SetLine( 28.0f );
		else R_RCS_FU_XFD_12_CL_TM.ResetLine();

		if (R_RCS_OX_XFD_12_OP_1) R_RCS_OX_XFD_12_OP_TM.SetLine( 28.0f );
		else R_RCS_OX_XFD_12_OP_TM.ResetLine();

		if (R_RCS_OX_XFD_12_CL_1) R_RCS_OX_XFD_12_CL_TM.SetLine( 28.0f );
		else R_RCS_OX_XFD_12_CL_TM.ResetLine();

		if (R_RCS_FU_XFD_345_OP_1) R_RCS_FU_XFD_345_OP_TM.SetLine( 28.0f );
		else R_RCS_FU_XFD_345_OP_TM.ResetLine();

		if (R_RCS_FU_XFD_345_CL_1) R_RCS_FU_XFD_345_CL_TM.SetLine( 28.0f );
		else R_RCS_FU_XFD_345_CL_TM.ResetLine();

		if (R_RCS_OX_XFD_345_OP_1) R_RCS_OX_XFD_345_OP_TM.SetLine( 28.0f );
		else R_RCS_OX_XFD_345_OP_TM.ResetLine();

		if (R_RCS_OX_XFD_345_CL_1) R_RCS_OX_XFD_345_CL_TM.SetLine( 28.0f );
		else R_RCS_OX_XFD_345_CL_TM.ResetLine();


		// TODO pre or post?
		vman.OnPostStep( simt, simdt, mjd );


		// TODO check ISOL VLVs and determine what manifolds are feed by what prop sources
		unsigned short source = 0;

		// FRCS
		if ((FRCSFuelTankIsol12Vlv->GetPos() > VLV_OP) && (FRCSOxidTankIsol12Vlv->GetPos() > VLV_OP)) source = FRCS;
		else source = 0;

		if ((FRCSFuelManifIsol1Vlv->GetPos() > VLV_OP) && (FRCSOxidManifIsol1Vlv->GetPos() > VLV_OP)) SetFRCS1PropSource( source );
		else SetFRCS1PropSource( 0 );

		if ((FRCSFuelManifIsol2Vlv->GetPos() > VLV_OP) && (FRCSOxidManifIsol2Vlv->GetPos() > VLV_OP)) SetFRCS2PropSource( source );
		else SetFRCS2PropSource( 0 );

		if ((FRCSFuelTankIsol345Vlv->GetPos() > VLV_OP) && (FRCSOxidTankIsol345Vlv->GetPos() > VLV_OP)) source = FRCS;
		else source = 0;

		if ((FRCSFuelManifIsol3Vlv->GetPos() > VLV_OP) && (FRCSOxidManifIsol3Vlv->GetPos() > VLV_OP)) SetFRCS3PropSource( source );
		else SetFRCS3PropSource( 0 );

		if ((FRCSFuelManifIsol4Vlv->GetPos() > VLV_OP) && (FRCSOxidManifIsol4Vlv->GetPos() > VLV_OP)) SetFRCS4PropSource( source );
		else SetFRCS4PropSource( 0 );

		if ((FRCSFuelManifIsol5Vlv->GetPos() > VLV_OP) && (FRCSOxidManifIsol5Vlv->GetPos() > VLV_OP)) SetFRCS5PropSource( source );
		else SetFRCS5PropSource( 0 );

		// LRCS
		/*
		LRCS
		RRCS
		LOMS
		ROMS
		KOMS
		*/
		// TODO make list with tank pressures of available sources
		// TODO search list for highest tank pressure

		if ((LRCSFuelManifIsol1Vlv->GetPos() > VLV_OP) && (LRCSOxidManifIsol1Vlv->GetPos() > VLV_OP)) SetLRCS1PropSource( source );
		else SetLRCS1PropSource( 0 );

		if ((LRCSFuelManifIsol2Vlv->GetPos() > VLV_OP) && (LRCSOxidManifIsol2Vlv->GetPos() > VLV_OP)) SetLRCS2PropSource( source );
		else SetLRCS2PropSource( 0 );


		if (((LRCSFuelTankIsol345AVlv->GetPos() + LRCSFuelTankIsol345BVlv->GetPos()) > VLV_OP) &&
			((LRCSOxidTankIsol345AVlv->GetPos() + LRCSOxidTankIsol345BVlv->GetPos()) > VLV_OP)) source = LRCS;
		else source = 0;////////

		if ((LRCSFuelManifIsol3Vlv->GetPos() > VLV_OP) && (LRCSOxidManifIsol3Vlv->GetPos() > VLV_OP)) SetLRCS3PropSource( source );
		else SetLRCS3PropSource( 0 );

		if ((LRCSFuelManifIsol4Vlv->GetPos() > VLV_OP) && (LRCSOxidManifIsol4Vlv->GetPos() > VLV_OP)) SetLRCS4PropSource( source );
		else SetLRCS4PropSource( 0 );

		if ((LRCSFuelManifIsol5Vlv->GetPos() > VLV_OP) && (LRCSOxidManifIsol5Vlv->GetPos() > VLV_OP)) SetLRCS5PropSource( source );
		else SetLRCS5PropSource( 0 );


		// RRCS
		/*
		RRCS
		LRCS
		LOMS
		ROMS
		KOMS
		*/
		// TODO make list with tank pressures of available (connected) sources
		// TODO search list for highest tank pressure
		if ((RRCSFuelTankIsol12Vlv->GetPos() > VLV_OP) && (RRCSOxidTankIsol12Vlv->GetPos() > VLV_OP)) source = RRCS;
		else source = 0;////////

		if ((RRCSFuelManifIsol1Vlv->GetPos() > VLV_OP) && (RRCSOxidManifIsol1Vlv->GetPos() > VLV_OP)) SetRRCS1PropSource( source );
		else SetRRCS1PropSource( 0 );

		if ((RRCSFuelManifIsol2Vlv->GetPos() > VLV_OP) && (RRCSOxidManifIsol2Vlv->GetPos() > VLV_OP)) SetRRCS2PropSource( source );
		else SetRRCS2PropSource( 0 );

		if (((RRCSFuelTankIsol345AVlv->GetPos() + RRCSFuelTankIsol345BVlv->GetPos()) > VLV_OP) &&
			((RRCSOxidTankIsol345AVlv->GetPos() + RRCSOxidTankIsol345BVlv->GetPos()) > VLV_OP)) source = RRCS;
		else source = 0;

		if ((RRCSFuelManifIsol3Vlv->GetPos() > VLV_OP) && (RRCSOxidManifIsol3Vlv->GetPos() > VLV_OP)) SetRRCS3PropSource( source );
		else SetRRCS3PropSource( 0 );

		if ((RRCSFuelManifIsol4Vlv->GetPos() > VLV_OP) && (RRCSOxidManifIsol4Vlv->GetPos() > VLV_OP)) SetRRCS4PropSource( source );
		else SetRRCS4PropSource( 0 );

		if ((RRCSFuelManifIsol5Vlv->GetPos() > VLV_OP) && (RRCSOxidManifIsol5Vlv->GetPos() > VLV_OP)) SetRRCS5PropSource( source );
		else SetRRCS5PropSource( 0 );
		

		// check RCS driver cmds and use them
		for (int i = 0; i < 44; i++) STS()->SetRCSThrustLevel( i, dipDriver[i].IsSet() ? 1.0 : 0.0 );
		
		// TODO handle RCS sounds

		// output PC data
		// PRCS 152psia
		// VRCS 110psia
		// TODO atmospheric pressure
		double pc = 0.0;// [psia]
		double v = 0.0;// [v]
		for (int i = 0; i < 44; i++)
		{
			pc = STS()->GetRCSThrustLevel( i );
			if ((i == RCS_F5R) || (i == RCS_F5L) || (i == RCS_L5L) || (i == RCS_R5R)) pc *= 110.0;
			else pc *= 152.0;

			// scale pc to volts: 0,200 psia to 0,-5.11 v
			v = (range( 0.0, pc, 200.0 ) / 200.0) * 5.11;

			dopPC[i].SetLine( static_cast<float>(v) );
		}
		return;
	}

	void RCS::SetFRCS1PropSource( unsigned short source )
	{
		if (FRCS1source == source) return;

		STS()->SetRCSPropSource( RCS_F1L, source );
		STS()->SetRCSPropSource( RCS_F1U, source );
		STS()->SetRCSPropSource( RCS_F1D, source );
		STS()->SetRCSPropSource( RCS_F1F, source );

		FRCS1source = source;
		return;
	}

	void RCS::SetFRCS2PropSource( unsigned short source )
	{
		if (FRCS2source == source) return;

		STS()->SetRCSPropSource( RCS_F2R, source );
		STS()->SetRCSPropSource( RCS_F2U, source );
		STS()->SetRCSPropSource( RCS_F2D, source );
		STS()->SetRCSPropSource( RCS_F2F, source );

		FRCS2source = source;
		return;
	}

	void RCS::SetFRCS3PropSource( unsigned short source )
	{
		if (FRCS3source == source) return;

		STS()->SetRCSPropSource( RCS_F3L, source );
		STS()->SetRCSPropSource( RCS_F3U, source );
		STS()->SetRCSPropSource( RCS_F3D, source );
		STS()->SetRCSPropSource( RCS_F3F, source );

		FRCS3source = source;
		return;
	}

	void RCS::SetFRCS4PropSource( unsigned short source )
	{
		if (FRCS4source == source) return;

		STS()->SetRCSPropSource( RCS_F4R, source );
		STS()->SetRCSPropSource( RCS_F4D, source );

		FRCS4source = source;
		return;
	}

	void RCS::SetFRCS5PropSource( unsigned short source )
	{
		if (FRCS5source == source) return;

		STS()->SetRCSPropSource( RCS_F5L, source );
		STS()->SetRCSPropSource( RCS_F5R, source );

		FRCS5source = source;
		return;
	}

	void RCS::SetLRCS1PropSource( unsigned short source )
	{
		if (LRCS1source == source) return;

		STS()->SetRCSPropSource( RCS_L1L, source );
		STS()->SetRCSPropSource( RCS_L1U, source );
		STS()->SetRCSPropSource( RCS_L1A, source );

		LRCS1source = source;
		return;
	}

	void RCS::SetLRCS2PropSource( unsigned short source )
	{
		if (LRCS2source == source) return;

		STS()->SetRCSPropSource( RCS_L2L, source );
		STS()->SetRCSPropSource( RCS_L2U, source );
		STS()->SetRCSPropSource( RCS_L2D, source );

		LRCS2source = source;
		return;
	}

	void RCS::SetLRCS3PropSource( unsigned short source )
	{
		if (LRCS3source == source) return;

		STS()->SetRCSPropSource( RCS_L3L, source );
		STS()->SetRCSPropSource( RCS_L3A, source );
		STS()->SetRCSPropSource( RCS_L3D, source );

		LRCS3source = source;
		return;
	}

	void RCS::SetLRCS4PropSource( unsigned short source )
	{
		if (LRCS4source == source) return;

		STS()->SetRCSPropSource( RCS_L4L, source );
		STS()->SetRCSPropSource( RCS_L4U, source );
		STS()->SetRCSPropSource( RCS_L4D, source );

		LRCS4source = source;
		return;
	}

	void RCS::SetLRCS5PropSource( unsigned short source )
	{
		if (LRCS5source == source) return;

		STS()->SetRCSPropSource( RCS_L5L, source );
		STS()->SetRCSPropSource( RCS_L5D, source );

		LRCS5source = source;
		return;
	}

	void RCS::SetRRCS1PropSource( unsigned short source )
	{
		if (RRCS1source == source) return;

		STS()->SetRCSPropSource( RCS_R1R, source );
		STS()->SetRCSPropSource( RCS_R1U, source );
		STS()->SetRCSPropSource( RCS_R1A, source );

		RRCS1source = source;
		return;
	}

	void RCS::SetRRCS2PropSource( unsigned short source )
	{
		if (RRCS2source == source) return;

		STS()->SetRCSPropSource( RCS_R2R, source );
		STS()->SetRCSPropSource( RCS_R2U, source );
		STS()->SetRCSPropSource( RCS_R2D, source );

		RRCS2source = source;
		return;
	}

	void RCS::SetRRCS3PropSource( unsigned short source )
	{
		if (RRCS3source == source) return;

		STS()->SetRCSPropSource( RCS_R3R, source );
		STS()->SetRCSPropSource( RCS_R3A, source );
		STS()->SetRCSPropSource( RCS_R3D, source );

		RRCS3source = source;
		return;
	}

	void RCS::SetRRCS4PropSource( unsigned short source )
	{
		if (RRCS4source == source) return;

		STS()->SetRCSPropSource( RCS_R4R, source );
		STS()->SetRCSPropSource( RCS_R4U, source );
		STS()->SetRCSPropSource( RCS_R4D, source );

		RRCS4source = source;
		return;
	}

	void RCS::SetRRCS5PropSource( unsigned short source )
	{
		if (RRCS5source == source) return;

		STS()->SetRCSPropSource( RCS_R5R, source );
		STS()->SetRCSPropSource( RCS_R5D, source );

		RRCS5source = source;
		return;
	}
}
