/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/23   GLS
2022/01/25   GLS
2022/01/31   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/05/14   GLS
2022/05/15   GLS
2022/05/16   GLS
2022/11/01   GLS
2022/11/03   GLS
2022/11/04   GLS
2022/11/05   GLS
2022/11/12   GLS
********************************************/
#include "MMC2.h"


MMC2::MMC2( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "MMC2" ),
K55(false), K67(false), K69(false), K57(false)
{
}

MMC2::~MMC2()
{
}

void MMC2::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PL_BAY_MECH_PWR_SYS_1.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "RadiatorControl", 16 );
	RADIATOR_LATCH_CONTROL_SYS_B_RELEASE.Connect( pBundle, 2 );
	RADIATOR_LATCH_CONTROL_SYS_B_LATCH.Connect( pBundle, 3 );
	RADIATOR_CONTROL_SYS_A_DEPLOY.Connect( pBundle, 8 );
	RADIATOR_CONTROL_SYS_A_STOW.Connect( pBundle, 9 );
	RADIATOR_STARBOARD_DPY.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "RadiatorLatchMotorInd_2", 16 );
	//PORT_RAD_LATCH_1_6_MOTOR_2_PWR.Connect( pBundle, 0 );
	//PORT_RAD_LATCH_1_6_REL_2.Connect( pBundle, 1 );
	//PORT_RAD_LATCH_1_6_LAT_2.Connect( pBundle, 2 );
	STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_LATCH_1_6_REL_2.Connect( pBundle, 4 );
	STARBOARD_RAD_LATCH_1_6_LAT_2.Connect( pBundle, 5 );
	//PORT_RAD_LATCH_7_12_MOTOR_2_PWR.Connect( pBundle, 6 );
	//PORT_RAD_LATCH_7_12_REL_2.Connect( pBundle, 7 );
	//PORT_RAD_LATCH_7_12_LAT_2.Connect( pBundle, 8 );
	STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.Connect( pBundle, 9 );
	STARBOARD_RAD_LATCH_7_12_REL_2.Connect( pBundle, 10 );
	STARBOARD_RAD_LATCH_7_12_LAT_2.Connect( pBundle, 11 );
	//PORT_RAD_LATCH_REL_2.Connect( pBundle, 12 );
	//PORT_RAD_LATCH_LAT_2.Connect( pBundle, 13 );
	STARBOARD_RAD_LATCH_REL_2.Connect( pBundle, 14 );
	STARBOARD_RAD_LATCH_LAT_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorMotorInd", 16 );
	//PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 1 );
	//PORT_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 2 );
	//STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 4 );
	//STARBOARD_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 5 );
	//PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 6 );
	//PORT_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 7 );
	//PORT_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 8 );
	STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 9 );
	STARBOARD_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 10 );
	STARBOARD_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	//LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
	LH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 7 );
	RH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	//LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
	//L_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	LH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	LH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	//LH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	//LH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	//LH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	//LH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	//LH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	//LH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	//LH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	//LH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	//LH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	//LH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	//LH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
	//L_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	LH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	LH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	//LH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	//LH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	//LH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	//LH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	LH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	LH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	LH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	LH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	//LH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	//LH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	//LH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
	//R_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	//R_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	//R_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	//RH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	//RH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	RH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	RH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	//RH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	//RH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	//RH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	//RH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	//RH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	//RH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	//RH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	//RH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	//RH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1A", 16 );
	//LH_VENTS_1_2_MOTOR_1_OPEN_A.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_1_CLOSE_A.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_1_PURGE_A.Connect( pBundle, 2 );
	LH_VENT_3_MOTOR_1_OPEN_A.Connect( pBundle, 3 );
	LH_VENT_3_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
	//LH_VENTS_4_7_MOTOR_1_OPEN_A.Connect( pBundle, 5 );
	//LH_VENTS_4_7_MOTOR_1_CLOSE_A.Connect( pBundle, 6 );
	//LH_VENT_5_MOTOR_1_OPEN_A.Connect( pBundle, 7 );
	//LH_VENT_5_MOTOR_1_CLOSE_A.Connect( pBundle, 8 );
	//LH_VENT_6_MOTOR_1_OPEN_A.Connect( pBundle, 9 );
	//LH_VENT_6_MOTOR_1_CLOSE_A.Connect( pBundle, 10 );
	//LH_VENT_6_MOTOR_1_PRG_1_A.Connect( pBundle, 11 );
	//LH_VENT_6_MOTOR_1_PRG_2_A.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1B", 16 );
	//LH_VENTS_1_2_MOTOR_1_OPEN_B.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_1_CLOSE_B.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_1_PURGE_B.Connect( pBundle, 2 );
	LH_VENT_3_MOTOR_1_OPEN_B.Connect( pBundle, 3 );
	LH_VENT_3_MOTOR_1_CLOSE_B.Connect( pBundle, 4 );
	//LH_VENTS_4_7_MOTOR_1_OPEN_B.Connect( pBundle, 5 );
	//LH_VENTS_4_7_MOTOR_1_CLOSE_B.Connect( pBundle, 6 );
	//LH_VENT_5_MOTOR_1_OPEN_B.Connect( pBundle, 7 );
	//LH_VENT_5_MOTOR_1_CLOSE_B.Connect( pBundle, 8 );
	//LH_VENT_6_MOTOR_1_OPEN_B.Connect( pBundle, 9 );
	//LH_VENT_6_MOTOR_1_CLOSE_B.Connect( pBundle, 10 );
	//LH_VENT_6_MOTOR_1_PRG_1_B.Connect( pBundle, 11 );
	//LH_VENT_6_MOTOR_1_PRG_2_B.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2A", 16 );
	//LH_VENTS_1_2_MOTOR_2_OPEN_A.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_2_CLOSE_A.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_2_PURGE_A.Connect( pBundle, 2 );
	LH_VENT_3_MOTOR_2_OPEN_A.Connect( pBundle, 3 );
	LH_VENT_3_MOTOR_2_CLOSE_A.Connect( pBundle, 4 );
	//LH_VENTS_4_7_MOTOR_2_OPEN_A.Connect( pBundle, 5 );
	//LH_VENTS_4_7_MOTOR_2_CLOSE_A.Connect( pBundle, 6 );
	//LH_VENT_5_MOTOR_2_OPEN_A.Connect( pBundle, 7 );
	//LH_VENT_5_MOTOR_2_CLOSE_A.Connect( pBundle, 8 );
	LH_VENT_6_MOTOR_2_OPEN_A.Connect( pBundle, 9 );
	LH_VENT_6_MOTOR_2_CLOSE_A.Connect( pBundle, 10 );
	LH_VENT_6_MOTOR_2_PRG_1_A.Connect( pBundle, 11 );
	LH_VENT_6_MOTOR_2_PRG_2_A.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_2_OPEN_A.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_2_CLOSE_A.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_2_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2B", 16 );
	//LH_VENTS_1_2_MOTOR_2_OPEN_B.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_2_CLOSE_B.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_2_PURGE_B.Connect( pBundle, 2 );
	LH_VENT_3_MOTOR_2_OPEN_B.Connect( pBundle, 3 );
	LH_VENT_3_MOTOR_2_CLOSE_B.Connect( pBundle, 4 );
	//LH_VENTS_4_7_MOTOR_2_OPEN_B.Connect( pBundle, 5 );
	//LH_VENTS_4_7_MOTOR_2_CLOSE_B.Connect( pBundle, 6 );
	//LH_VENT_5_MOTOR_2_OPEN_B.Connect( pBundle, 7 );
	//LH_VENT_5_MOTOR_2_CLOSE_B.Connect( pBundle, 8 );
	LH_VENT_6_MOTOR_2_OPEN_B.Connect( pBundle, 9 );
	LH_VENT_6_MOTOR_2_CLOSE_B.Connect( pBundle, 10 );
	LH_VENT_6_MOTOR_2_PRG_1_B.Connect( pBundle, 11 );
	LH_VENT_6_MOTOR_2_PRG_2_B.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_2_OPEN_B.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_2_CLOSE_B.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_2_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1A", 16 );
	//RH_VENTS_1_2_MOTOR_1_OPEN_A.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_1_CLOSE_A.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_1_PURGE_A.Connect( pBundle, 2 );
	//RH_VENT_3_MOTOR_1_OPEN_A.Connect( pBundle, 3 );
	//RH_VENT_3_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
	RH_VENTS_4_7_MOTOR_1_OPEN_A.Connect( pBundle, 5 );
	RH_VENTS_4_7_MOTOR_1_CLOSE_A.Connect( pBundle, 6 );
	//RH_VENT_5_MOTOR_1_OPEN_A.Connect( pBundle, 7 );
	//RH_VENT_5_MOTOR_1_CLOSE_A.Connect( pBundle, 8 );
	//RH_VENT_6_MOTOR_1_OPEN_A.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_CLOSE_A.Connect( pBundle, 10 );
	//RH_VENT_6_MOTOR_1_PRG_1_A.Connect( pBundle, 11 );
	//RH_VENT_6_MOTOR_1_PRG_2_A.Connect( pBundle, 12 );
	//RH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 13 );
	//RH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 14 );
	//RH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1B", 16 );
	//RH_VENTS_1_2_MOTOR_1_OPEN_B.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_1_CLOSE_B.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_1_PURGE_B.Connect( pBundle, 2 );
	//RH_VENT_3_MOTOR_1_OPEN_B.Connect( pBundle, 3 );
	//RH_VENT_3_MOTOR_1_CLOSE_B.Connect( pBundle, 4 );
	RH_VENTS_4_7_MOTOR_1_OPEN_B.Connect( pBundle, 5 );
	RH_VENTS_4_7_MOTOR_1_CLOSE_B.Connect( pBundle, 6 );
	//RH_VENT_5_MOTOR_1_OPEN_B.Connect( pBundle, 7 );
	//RH_VENT_5_MOTOR_1_CLOSE_B.Connect( pBundle, 8 );
	//RH_VENT_6_MOTOR_1_OPEN_B.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_CLOSE_B.Connect( pBundle, 10 );
	//RH_VENT_6_MOTOR_1_PRG_1_B.Connect( pBundle, 11 );
	//RH_VENT_6_MOTOR_1_PRG_2_B.Connect( pBundle, 12 );
	//RH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 13 );
	//RH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 14 );
	//RH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "KuBandAntennaCommand", 16 );
	KU_ANTENNA_DIRECT_STOW_ON.Connect( pBundle, 0 );
	KU_ANTENNA_STOW.Connect( pBundle, 1 );
	KU_ANTENNA_DEPLOY.Connect( pBundle, 2 );

	pBundle = BundleManager()->CreateBundle( "KuBandAntennaControl", 16 );
	BOOM_STOW_ENABLE_I.Connect( pBundle, 0 );
	BOOM_STOW_ENABLE_II.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "KuBandAntennaMotorInd", 16 );
	KU_RNDZ_RADAR_MOTOR_1_PWR.Connect( pBundle, 0 );
	KU_RNDZ_RADAR_STO_IND_1.Connect( pBundle, 1 );
	KU_RNDZ_RADAR_DPY_IND_1.Connect( pBundle, 2 );
	//KU_RNDZ_RADAR_MOTOR_2_PWR.Connect( pBundle, 3 );
	//KU_RNDZ_RADAR_STO_IND_2.Connect( pBundle, 4 );
	//KU_RNDZ_RADAR_DPY_IND_2.Connect( pBundle, 5 );
	//KU_RNDZ_RADAR_STO_IND.Connect( pBundle, 6 );
	//KU_RNDZ_RADAR_DPY_IND.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "MPM_D&C", 16 );
	PORT_MPM_STOW.Connect( pBundle, 0 );
	PORT_MPM_DEPLOY.Connect( pBundle, 1 );
	//PORT_MPM_SYSTEM_1_STOW.Connect( pBundle, 2 );
	//PORT_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 3 );
	PORT_MPM_SYSTEM_2_STOW.Connect( pBundle, 4 );
	PORT_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 5 );
	STBD_MPM_STOW.Connect( pBundle, 6 );
	STBD_MPM_DEPLOY.Connect( pBundle, 7 );
	//STBD_MPM_SYSTEM_1_STOW.Connect( pBundle, 8 );
	//STBD_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 9 );
	//STBD_MPM_SYSTEM_2_STOW.Connect( pBundle, 10 );
	//STBD_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
	//PORT_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	//PORT_FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
	//PORT_MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
	//PORT_AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
	//PORT_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
	//PORT_FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	//PORT_MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
	//PORT_AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
	PORT_SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
	PORT_FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
	PORT_MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
	PORT_AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
	PORT_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
	PORT_FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
	PORT_MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
	PORT_AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "STBD_MPM_IND", 16 );
	STBD_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	//STBD_FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
	//STBD_MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
	//STBD_AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
	STBD_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
	//STBD_FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	//STBD_MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
	//STBD_AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
	//STBD_SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
	//STBD_FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
	//STBD_MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
	//STBD_AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
	//STBD_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
	//STBD_FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
	//STBD_MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
	//STBD_AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_PWR", 16 );
	//PORT_MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
	PORT_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	//PORT_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	//PORT_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	PORT_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	PORT_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	//PORT_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	//PORT_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	//PORT_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "STBD_MPM_PWR", 16 );
	STBD_MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
	//STBD_MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
	//STBD_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	//STBD_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	//STBD_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	//STBD_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	//STBD_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	STBD_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	//STBD_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	//STBD_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "MRL_D&C", 16 );
	PORT_MRL_LATCH.Connect( pBundle, 0 );
	PORT_MRL_RELEASE.Connect( pBundle, 1 );
	PORT_MRL_LATCHED.Connect( pBundle, 2 );
	PORT_MRL_RELEASED.Connect( pBundle, 3 );
	STBD_MRL_LATCH.Connect( pBundle, 4 );
	STBD_MRL_RELEASE.Connect( pBundle, 5 );
	//STBD_MRL_LATCHED.Connect( pBundle, 6 );
	//STBD_MRL_RELEASED.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
	PORT_FWD_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	PORT_FWD_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_FWD_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	//PORT_FWD_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_FWD_RETNN_RFL_2.Connect( pBundle, 5 );
	//STBD_FWD_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	//STBD_FWD_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	//STBD_FWD_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_FWD_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_FWD_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_FWD_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
	PORT_MID_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	PORT_MID_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_MID_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	//PORT_MID_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_MID_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_MID_RETNN_RFL_2.Connect( pBundle, 5 );
	//STBD_MID_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	//STBD_MID_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	STBD_MID_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	STBD_MID_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_MID_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_MID_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
	PORT_AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	PORT_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_AFT_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	//PORT_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_AFT_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_AFT_RETNN_RFL_2.Connect( pBundle, 5 );
	//STBD_AFT_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	//STBD_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	STBD_AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	STBD_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_AFT_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_AFT_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_PWR", 16 );
	PORT_FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	PORT_FWD_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_FWD_MRL_IND_2_PWR.Connect( pBundle, 3 );
	PORT_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	//STBD_FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	//STBD_FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	//STBD_FWD_MRL_IND_1_PWR.Connect( pBundle, 8 );
	//STBD_FWD_MRL_IND_2_PWR.Connect( pBundle, 9 );
	//STBD_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	//STBD_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MID_MRL_PWR", 16 );
	//PORT_MID_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_MID_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_MID_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_MID_MRL_IND_2_PWR.Connect( pBundle, 3 );
	//PORT_MID_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_MID_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	//STBD_MID_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	STBD_MID_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	//STBD_MID_MRL_IND_1_PWR.Connect( pBundle, 8 );
	STBD_MID_MRL_IND_2_PWR.Connect( pBundle, 9 );
	//STBD_MID_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	STBD_MID_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "AFT_MRL_PWR", 16 );
	PORT_AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	PORT_AFT_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_AFT_MRL_IND_2_PWR.Connect( pBundle, 3 );
	PORT_AFT_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_AFT_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	//STBD_AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	STBD_AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	//STBD_AFT_MRL_IND_1_PWR.Connect( pBundle, 8 );
	STBD_AFT_MRL_IND_2_PWR.Connect( pBundle, 9 );
	//STBD_AFT_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	STBD_AFT_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PBD_OPERATION_ENABLE", 16 );
	PBD_OPERATION_ENABLE_CMD_2A.Connect( pBundle, 2 );
	PBD_OPERATION_ENABLE_CMD_2B.Connect( pBundle, 3 );
	PBD_OPERATION_ENABLE_CMD_3A.Connect( pBundle, 4 );
	PBD_OPERATION_ENABLE_CMD_3B.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "PayloadBayDoorControl", 16 );
	PBD_ENABLE_SYS1.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "MMC_POWER", 16 );
	MNB_MMC2.Connect( pBundle, 2 );
	MNC_MMC2.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "PLBD_PORT_PDU", 16 );
	PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.Connect( pBundle, 1 );
	PORT_DOOR_CLOSE_2.Connect( pBundle, 9 );
	PORT_DOOR_OPEN_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PLBD_CL_2", 16 );
	CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.Connect( pBundle, 0 );
	LAT_1_4_LAT_2.Connect( pBundle, 1 );
	LAT_1_4_REL_2.Connect( pBundle, 2 );
	CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.Connect( pBundle, 3 );
	LAT_5_8_LAT_2.Connect( pBundle, 4 );
	LAT_5_8_REL_2.Connect( pBundle, 5 );
	CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.Connect( pBundle, 9 );
	LAT_13_16_LAT_2.Connect( pBundle, 10 );
	LAT_13_16_REL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_2", 16 );
	BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.Connect( pBundle, 3 );
	STBD_AFT_BLKHD_LAT_2.Connect( pBundle, 4 );
	STBD_AFT_BLKHD_REL_2.Connect( pBundle, 5 );
	BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.Connect( pBundle, 9 );
	PORT_AFT_BLKHD_LAT_2.Connect( pBundle, 10 );
	PORT_AFT_BLKHD_REL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PLBD_PDU_CMD", 16 );
	PORT_DOOR_POWER_DRIVE_UNIT_OPEN_CMD_2.Connect( pBundle, 2 );
	PORT_DOOR_POWER_DRIVE_UNIT_CLOSE_CMD_2.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "PLBD_CL_CMD", 16 );
	LAT_1_4_REL_CMD_2.Connect( pBundle, 8 );
	LAT_1_4_LAT_CMD_2.Connect( pBundle, 9 );
	LAT_5_8_REL_CMD_2.Connect( pBundle, 10 );
	LAT_5_8_LAT_CMD_2.Connect( pBundle, 11 );
	LAT_13_16_REL_CMD_2.Connect( pBundle, 14 );
	LAT_13_16_LAT_CMD_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_CMD", 16 );
	PORT_AFT_BLKHD_REL_CMD_2.Connect( pBundle, 6 );
	PORT_AFT_BLKHD_LAT_CMD_2.Connect( pBundle, 7 );
	STBD_AFT_BLKHD_REL_CMD_2.Connect( pBundle, 14 );
	STBD_AFT_BLKHD_LAT_CMD_2.Connect( pBundle, 15 );
	return;
}

void MMC2::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNB_RELAY_LOGIC_POWER = true;
	bool MNC_RELAY_LOGIC_POWER = true;

	if (MNB_RELAY_LOGIC_POWER) MNB_MMC2.SetLine();
	else MNB_MMC2.ResetLine();
	if (MNC_RELAY_LOGIC_POWER) MNC_MMC2.SetLine();
	else MNC_MMC2.ResetLine();

	// MPM indication power and position status
	PORT_MPM_MID_1_IND_PWR.SetLine();
	PORT_MPM_FWD_2_IND_PWR.SetLine();
	PORT_MPM_SHOULDER_1_IND_PWR.SetLine();
	STBD_MPM_MID_2_IND_PWR.SetLine();

	if (PORT_SHLD_MECH_STOW_IND_2 && PORT_FWD_MECH_STOW_IND_2 && PORT_MID_MECH_STOW_IND_2 && PORT_AFT_MECH_STOW_IND_2) PORT_MPM_SYSTEM_2_STOW.SetLine();
	else PORT_MPM_SYSTEM_2_STOW.ResetLine();

	if (PORT_SHLD_MECH_DEPLOY_IND_2 && PORT_FWD_MECH_DEPLOY_IND_2 && PORT_MID_MECH_DEPLOY_IND_2 && PORT_AFT_MECH_DEPLOY_IND_2) PORT_MPM_SYSTEM_2_DEPLOY.SetLine();
	else PORT_MPM_SYSTEM_2_DEPLOY.ResetLine();

	// MRL position status
	if (PORT_FWD_MRL_LATCH_IND_1 && PORT_MID_MRL_LATCH_IND_1 && PORT_AFT_MRL_LATCH_IND_1) PORT_MRL_LATCHED.SetLine();
	else PORT_MRL_LATCHED.ResetLine();

	if (PORT_FWD_MRL_RELEASE_IND_1 && PORT_MID_MRL_RELEASE_IND_1 && PORT_AFT_MRL_RELEASE_IND_1) PORT_MRL_RELEASED.SetLine();
	else PORT_MRL_RELEASED.ResetLine();

	// power enables
	bool K61 = PL_BAY_MECH_PWR_SYS_1;
	bool K63 = PL_BAY_MECH_PWR_SYS_1;
	bool K58 = PL_BAY_MECH_PWR_SYS_1;
	bool K56 = PL_BAY_MECH_PWR_SYS_1;
	bool K54 = PBD_OPERATION_ENABLE_CMD_2A && PBD_ENABLE_SYS1;
	bool K42 = PBD_OPERATION_ENABLE_CMD_2B && PBD_ENABLE_SYS1;
	bool K37 = PBD_OPERATION_ENABLE_CMD_3A && PBD_ENABLE_SYS1;
	bool K39 = PBD_OPERATION_ENABLE_CMD_3B && PBD_ENABLE_SYS1;

	// VENT DOORS
	// left no 3 motor 1
	bool K31 = LH_VENT_3_MOTOR_1_OPEN_B && !LH_VENT_3_OPEN_1;// OPN B
	bool K45 = LH_VENT_3_MOTOR_1_OPEN_A && !LH_VENT_3_OPEN_1;// OPN A
	bool K33 = LH_VENT_3_MOTOR_1_CLOSE_B && !LH_VENT_3_CLOSE_1;// CLS B
	bool K35 = LH_VENT_3_MOTOR_1_CLOSE_A && !LH_VENT_3_CLOSE_1;// CLS A

	if (K31 && K45)
	{
		if (K33 && K35) LH_VENT_3_MOTOR_1_PWR.SetLine( 0.0f );
		else LH_VENT_3_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K33 && K35) LH_VENT_3_MOTOR_1_PWR.SetLine( -1.0f );
		else LH_VENT_3_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// right no 4/7 motor 1
	bool K40 = RH_VENTS_4_7_MOTOR_1_OPEN_B && !RH_VENTS_4_AND_7_OPEN_1;// OPN B
	bool K26 = RH_VENTS_4_7_MOTOR_1_OPEN_A && !RH_VENTS_4_AND_7_OPEN_1;// OPN A
	bool K28 = RH_VENTS_4_7_MOTOR_1_CLOSE_B && !RH_VENTS_4_AND_7_CLOSE_1;// CLS B
	bool K30 = RH_VENTS_4_7_MOTOR_1_CLOSE_A && !RH_VENTS_4_AND_7_CLOSE_1;// CLS A

	if (K40 && K26)
	{
		if (K28 && K30) RH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( 0.0f );
		else RH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K28 && K30) RH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( -1.0f );
		else RH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// left no 6 motor 2
	K55 = (!LH_VENT_6_PURGE_2_IND_2 && LH_VENT_6_CLOSE_2) || (K55 && !LH_VENT_6_PURGE_2_IND_2) || (K55 && LH_VENT_6_CLOSE_2);
	K67 = (!LH_VENT_6_CLOSE_2 && LH_VENT_6_PURGE_2_IND_2) || (K67 && !LH_VENT_6_CLOSE_2) || (K67 && LH_VENT_6_PURGE_2_IND_2);
	K69 = (!LH_VENT_6_PURGE_1_IND_2 && LH_VENT_6_OPEN_2) || (K69 && !LH_VENT_6_PURGE_1_IND_2) || (K69 && LH_VENT_6_OPEN_2);
	K57 = (!LH_VENT_6_OPEN_2 && LH_VENT_6_PURGE_1_IND_2) || (K57 && !LH_VENT_6_OPEN_2) || (K57 && LH_VENT_6_PURGE_1_IND_2);

	bool PRG1_2A = LH_VENT_6_MOTOR_2_PRG_1_A && !LH_VENT_6_PURGE_1_IND_2;
	bool PRG1_2B = LH_VENT_6_MOTOR_2_PRG_1_B && !LH_VENT_6_PURGE_1_IND_2;
	bool PRG2_2A = LH_VENT_6_MOTOR_2_PRG_2_A && !LH_VENT_6_PURGE_2_IND_2;
	bool PRG2_2B = LH_VENT_6_MOTOR_2_PRG_2_B && !LH_VENT_6_PURGE_2_IND_2;

	bool K5 = (LH_VENT_6_MOTOR_2_OPEN_B || (PRG1_2B && K55) || (PRG2_2B && K57)) && !LH_VENT_6_OPEN_2;// OPN B
	bool K15 = (LH_VENT_6_MOTOR_2_OPEN_A || (PRG1_2A && K55) || (PRG2_2A && K57)) && !LH_VENT_6_OPEN_2;// OPN A
	bool K3 = (LH_VENT_6_MOTOR_2_CLOSE_B || (PRG1_2B && K67) || (PRG2_2B && K69)) && !LH_VENT_6_CLOSE_2;// CLS B
	bool K1 = (LH_VENT_6_MOTOR_2_CLOSE_A || (PRG1_2A && K67) || (PRG2_2A && K69)) && !LH_VENT_6_CLOSE_2;// CLS A

	if (K5 && K15)
	{
		if (K1 && K3) LH_VENT_6_MOTOR_2_PWR.SetLine( 0.0f );
		else LH_VENT_6_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K1 && K3) LH_VENT_6_MOTOR_2_PWR.SetLine( -1.0f );
		else LH_VENT_6_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// PAYLOAD BAY DOORS
	// port aft bkhd latch motor 2
	bool K19 = MNC_RELAY_LOGIC_POWER && (PORT_AFT_BLKHD_REL_CMD_2 && !PORT_AFT_BLKHD_REL_2);// REL
	bool K7 = MNC_RELAY_LOGIC_POWER && (PORT_AFT_BLKHD_LAT_CMD_2 && !PORT_AFT_BLKHD_LAT_2);// LCH

	if (K42 && K54)
	{
		if (K19)
		{
			if (K7) BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.SetLine( 0.0f );
			else BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K7) BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.SetLine( -1.0f );
			else BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR.SetLine( 0.0f );
	// cl 1-4 latch motort 2
	bool K50 = MNC_RELAY_LOGIC_POWER && (LAT_1_4_REL_CMD_2 && !LAT_1_4_REL_2);// REL
	bool K38 = MNC_RELAY_LOGIC_POWER && (LAT_1_4_LAT_CMD_2 && !LAT_1_4_LAT_2);// LCH

	if (K42 && K54)
	{
		if (K50)
		{
			if (K38) CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.SetLine( 0.0f );
			else CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K38) CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.SetLine( -1.0f );
			else CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR.SetLine( 0.0f );
	// cl 5-8 latch motor 2
	bool K4 = MNC_RELAY_LOGIC_POWER && (LAT_5_8_REL_CMD_2 && !LAT_5_8_REL_2);// REL
	bool K6 = MNC_RELAY_LOGIC_POWER && (LAT_5_8_LAT_CMD_2 && !LAT_5_8_LAT_2);// LCH

	if (K42 && K54)
	{
		if (K4)
		{
			if (K6) CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.SetLine( 0.0f );
			else CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K6) CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.SetLine( -1.0f );
			else CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR.SetLine( 0.0f );

	// KU BAND
	// ant a deploy motor 1
	bool KU_ANTENNA_GND = !KU_ANTENNA_DEPLOY && !KU_ANTENNA_STOW;// HACK due to switch implementation limitations
	bool K14 = (KU_ANTENNA_DIRECT_STOW_ON || KU_ANTENNA_STOW) && ((KU_ANTENNA_DIRECT_STOW_ON || BOOM_STOW_ENABLE_II) && !KU_RNDZ_RADAR_STO_IND_1);// STW II
	bool K70 = (KU_ANTENNA_GND || KU_ANTENNA_DEPLOY) && ((cmd_V54K0013N || KU_ANTENNA_DEPLOY) && !KU_RNDZ_RADAR_DPY_IND_1);// DPY B
	bool K72 = (KU_ANTENNA_GND || KU_ANTENNA_DEPLOY) && ((cmd_V54K0003N || KU_ANTENNA_DEPLOY) && !KU_RNDZ_RADAR_DPY_IND_1);// DPY A
	bool K68 = (KU_ANTENNA_DIRECT_STOW_ON || KU_ANTENNA_STOW) && ((KU_ANTENNA_DIRECT_STOW_ON || BOOM_STOW_ENABLE_I) && !KU_RNDZ_RADAR_STO_IND_1);// STW I

	if (K61 && K63)
	{
		if (K70 && K72)
		{
			if (K14 && K68) KU_RNDZ_RADAR_MOTOR_1_PWR.SetLine( 0.0f );
			else KU_RNDZ_RADAR_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K14 && K68) KU_RNDZ_RADAR_MOTOR_1_PWR.SetLine( -1.0f );
			else KU_RNDZ_RADAR_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else KU_RNDZ_RADAR_MOTOR_1_PWR.SetLine( 0.0f );

	// FREON RADIATOR
	if (STARBOARD_RAD_LATCH_1_6_LAT_2 && STARBOARD_RAD_LATCH_7_12_LAT_2) STARBOARD_RAD_LATCH_LAT_2.SetLine();
	else STARBOARD_RAD_LATCH_LAT_2.ResetLine();

	bool bSTARBOARD_RAD_LATCH_REL_2;
	if (STARBOARD_RAD_LATCH_1_6_REL_2 && STARBOARD_RAD_LATCH_7_12_REL_2)
	{
		STARBOARD_RAD_LATCH_REL_2.SetLine();
		bSTARBOARD_RAD_LATCH_REL_2 = true;
	}
	else
	{
		STARBOARD_RAD_LATCH_REL_2.ResetLine();
		bSTARBOARD_RAD_LATCH_REL_2 = false;
	}

	if (STARBOARD_RAD_DEPLOYMENT_DPY_1 && STARBOARD_RAD_DEPLOYMENT_DPY_2) RADIATOR_STARBOARD_DPY.SetLine();
	else RADIATOR_STARBOARD_DPY.ResetLine();

	// stbd sys a deploy motor 2
	bool K62 = RADIATOR_CONTROL_SYS_A_DEPLOY && !STARBOARD_RAD_DEPLOYMENT_DPY_2;// DPY
	bool K52 = RADIATOR_CONTROL_SYS_A_DEPLOY && (bSTARBOARD_RAD_LATCH_REL_2 && !STARBOARD_RAD_DEPLOYMENT_DPY_2);// DPY
	bool K64 = RADIATOR_CONTROL_SYS_A_STOW && !STARBOARD_RAD_DEPLOYMENT_STO_2;// STW
	bool K66 = RADIATOR_CONTROL_SYS_A_STOW && !STARBOARD_RAD_DEPLOYMENT_STO_2;// STW

	if (K61 && K63)
	{
		if (K62 && K52)
		{
			if (K64 && K66) STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 0.0f );
			else STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K64 && K66) STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( -1.0f );
			else STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 0.0f );

	// stbd sys b latch 7-12 motor 2
	bool K48 = RADIATOR_LATCH_CONTROL_SYS_B_LATCH && !STARBOARD_RAD_LATCH_7_12_LAT_2;// LCH
	bool K60 = RADIATOR_LATCH_CONTROL_SYS_B_RELEASE && !STARBOARD_RAD_LATCH_7_12_REL_2;// REL

	if (K61 && K63)
	{
		if (K60)
		{
			if (K48) STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 0.0f );
			else STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K48) STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( -1.0f );
			else STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 0.0f );

	// REMOTE MANIPULATOR
	// port aft sys 1 retn lch motor 1
	bool K77 = true;// TODO deadface
	bool K75 = K77 && (PORT_MRL_LATCH && !PORT_AFT_MRL_LATCH_IND_1);// LCH
	bool K73 = K77 && (PORT_MRL_RELEASE && !PORT_AFT_MRL_RELEASE_IND_1);// REL

	if (K61 && K63)
	{
		if (K73)
		{
			if (K75) PORT_AFT_MRL_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_AFT_MRL_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K75) PORT_AFT_MRL_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_AFT_MRL_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_AFT_MRL_MOTOR_1_PWR.SetLine( 0.0f );

	if (K77)
	{
		PORT_AFT_MRL_IND_1_PWR.SetLine();
		PORT_AFT_RETNN_RFL_1_PWR.SetLine();
	}
	else
	{
		PORT_AFT_MRL_IND_1_PWR.ResetLine();
		PORT_AFT_RETNN_RFL_1_PWR.ResetLine();
	}

	// stbd mid retn lch motor 2
	bool K78 = true;// TODO deadface and coil ID
	bool K76 = K78 && (STBD_MRL_LATCH && !STBD_MID_MRL_LATCH_IND_2);// LCH
	bool K74 = K78 && (STBD_MRL_RELEASE && !STBD_MID_MRL_RELEASE_IND_2);// REL

	if (K61 && K63)
	{
		if (K74)
		{
			if (K76) STBD_MID_MRL_MOTOR_2_PWR.SetLine( 0.0f );
			else STBD_MID_MRL_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K76) STBD_MID_MRL_MOTOR_2_PWR.SetLine( -1.0f );
			else STBD_MID_MRL_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STBD_MID_MRL_MOTOR_2_PWR.SetLine( 0.0f );

	if (K78)
	{
		STBD_MID_MRL_IND_2_PWR.SetLine();
		STBD_MID_RETNN_RFL_2_PWR.SetLine();
	}
	else
	{
		STBD_MID_MRL_IND_2_PWR.ResetLine();
		STBD_MID_RETNN_RFL_2_PWR.ResetLine();
	}

	// VENT DOOR
	// left no 3 motor 2
	bool K32 = LH_VENT_3_MOTOR_2_OPEN_B && !LH_VENT_3_OPEN_2;// OPN B
	bool K46 = LH_VENT_3_MOTOR_2_OPEN_A && !LH_VENT_3_OPEN_2;// OPN A
	bool K34 = LH_VENT_3_MOTOR_2_CLOSE_B && !LH_VENT_3_CLOSE_2;// CLS B
	bool K36 = LH_VENT_3_MOTOR_2_CLOSE_A && !LH_VENT_3_CLOSE_2;// CLS A

	if (K32 && K46)
	{
		if (K34 && K36) LH_VENT_3_MOTOR_2_PWR.SetLine( 0.0f );
		else LH_VENT_3_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K34 && K36) LH_VENT_3_MOTOR_2_PWR.SetLine( -1.0f );
		else LH_VENT_3_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// PAYLOAD DOORS
	// port pdu motor 2
	bool K12 = MNB_RELAY_LOGIC_POWER && (PORT_DOOR_POWER_DRIVE_UNIT_CLOSE_CMD_2 && !PORT_DOOR_CLOSE_2);// CLS
	bool K10 = MNB_RELAY_LOGIC_POWER && (PORT_DOOR_POWER_DRIVE_UNIT_OPEN_CMD_2 && !PORT_DOOR_OPEN_2);// OPN

	if (K37 && K39)
	{
		if (K10)
		{
			if (K12) PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K12) PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR.SetLine( 0.0f );
	// stbd aft bkhd latch motor 2
	bool K25 = MNB_RELAY_LOGIC_POWER && (STBD_AFT_BLKHD_REL_CMD_2 && !STBD_AFT_BLKHD_REL_2);// REL
	bool K13 = MNB_RELAY_LOGIC_POWER && (STBD_AFT_BLKHD_LAT_CMD_2 && !STBD_AFT_BLKHD_LAT_2);// LCH

	if (K37 && K39)
	{
		if (K25)
		{
			if (K13) BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.SetLine( 0.0f );
			else BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K13) BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.SetLine( -1.0f );
			else BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR.SetLine( 0.0f );
	// cl 13-16 latch motor 2
	bool K9 = MNB_RELAY_LOGIC_POWER && (LAT_13_16_LAT_CMD_2 && !LAT_13_16_LAT_2);// LCH
	bool K21 = MNB_RELAY_LOGIC_POWER && (LAT_13_16_REL_CMD_2 && !LAT_13_16_REL_2);// REL

	if (K37 && K39)
	{
		if (K21)
		{
			if (K9) CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.SetLine( 0.0f );
			else CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K9) CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.SetLine( -1.0f );
			else CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR.SetLine( 0.0f );

	// FREON RAD
	// stbd sys b latch 1-6 motor 2
	bool K65 = RADIATOR_LATCH_CONTROL_SYS_B_RELEASE && !STARBOARD_RAD_LATCH_1_6_REL_2;// REL
	bool K53 = RADIATOR_LATCH_CONTROL_SYS_B_LATCH && !STARBOARD_RAD_LATCH_1_6_LAT_2;// LCH

	if (K58 && K56)
	{
		if (K65)
		{
			if (K53) STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 0.0f );
			else STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K53) STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( -1.0f );
			else STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 0.0f );

	// REMOTE MANIPULATOR
	// stbd deploy motor 1
	bool K49 = STBD_MPM_DEPLOY && !STBD_SHLD_MECH_DEPLOY_IND_1;// DPY
	bool K51 = STBD_MPM_STOW && !STBD_SHLD_MECH_STOW_IND_1;// STW

	if (K58 && K56)
	{
		if (K49)
		{
			if (K51) STBD_MPM_MOTOR_1_PWR.SetLine( 0.0f );
			else STBD_MPM_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K51) STBD_MPM_MOTOR_1_PWR.SetLine( -1.0f );
			else STBD_MPM_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STBD_MPM_MOTOR_1_PWR.SetLine( 0.0f );

	// port deploy motor 2
	bool K22 = PORT_MPM_STOW && !PORT_SHLD_MECH_STOW_IND_2;// STW
	bool K24 = PORT_MPM_DEPLOY && !PORT_SHLD_MECH_DEPLOY_IND_2;// DPY

	if (K58 && K56)
	{
		if (K24)
		{
			if (K22) PORT_MPM_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_MPM_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K22) PORT_MPM_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_MPM_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_MPM_MOTOR_2_PWR.SetLine( 0.0f );

	// stbd aft retn latch motor 2
	bool K99 = true;// TODO deadface and coil ID
	bool K29 = K99 && (STBD_MRL_RELEASE && !STBD_AFT_MRL_RELEASE_IND_2);// REL
	bool K27 = K99 && (STBD_MRL_LATCH && !STBD_AFT_MRL_LATCH_IND_2);// LCH

	if (K58 && K56)
	{
		if (K29)
		{
			if (K27) STBD_AFT_MRL_MOTOR_2_PWR.SetLine( 0.0f );
			else STBD_AFT_MRL_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K27) STBD_AFT_MRL_MOTOR_2_PWR.SetLine( -1.0f );
			else STBD_AFT_MRL_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STBD_AFT_MRL_MOTOR_2_PWR.SetLine( 0.0f );

	if (K99)
	{
		STBD_AFT_MRL_IND_2_PWR.SetLine();
		STBD_AFT_RETNN_RFL_2_PWR.SetLine();
	}
	else
	{
		STBD_AFT_MRL_IND_2_PWR.ResetLine();
		STBD_AFT_RETNN_RFL_2_PWR.ResetLine();
	}

	// port fwd sys1 retn latch motor 1
	bool K44 = true;// TODO deadface
	bool K20 = K44 && (PORT_MRL_LATCH && !PORT_FWD_MRL_LATCH_IND_1);// LCH
	bool K8 = K44 && (PORT_MRL_RELEASE && !PORT_FWD_MRL_RELEASE_IND_1);// REL

	if (K58 && K56)
	{
		if (K8)
		{
			if (K20) PORT_FWD_MRL_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_FWD_MRL_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K20) PORT_FWD_MRL_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_FWD_MRL_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_FWD_MRL_MOTOR_1_PWR.SetLine( 0.0f );

	if (K44)
	{
		PORT_FWD_MRL_IND_1_PWR.SetLine();
		PORT_FWD_RETNN_RFL_1_PWR.SetLine();
	}
	else
	{
		PORT_FWD_MRL_IND_1_PWR.ResetLine();
		PORT_FWD_RETNN_RFL_1_PWR.ResetLine();
	}
	return;
}
