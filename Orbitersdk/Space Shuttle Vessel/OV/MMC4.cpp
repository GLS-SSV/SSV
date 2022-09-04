/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/23   GLS
2022/01/25   GLS
2022/01/30   GLS
2022/01/31   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/05/14   GLS
2022/05/15   GLS
2022/05/16   GLS
********************************************/
#include "MMC4.h"


MMC4::MMC4( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "MMC4" ),
K19(false), K17(false), K7(false), K5(false)
{
}

MMC4::~MMC4()
{
}

void MMC4::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PL_BAY_MECH_PWR_SYS_2.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "RadiatorControl", 16 );
	RADIATOR_LATCH_CONTROL_SYS_B_RELEASE.Connect( pBundle, 2 );
	RADIATOR_LATCH_CONTROL_SYS_B_LATCH.Connect( pBundle, 3 );
	RADIATOR_CONTROL_SYS_B_DEPLOY.Connect( pBundle, 10 );
	RADIATOR_CONTROL_SYS_B_STOW.Connect( pBundle, 11 );
	RADIATOR_PORT_DPY.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "RadiatorLatchMotorInd_2", 16 );
	PORT_RAD_LATCH_1_6_MOTOR_2_PWR.Connect( pBundle, 0 );
	PORT_RAD_LATCH_1_6_REL_2.Connect( pBundle, 1 );
	PORT_RAD_LATCH_1_6_LAT_2.Connect( pBundle, 2 );
	//STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR.Connect( pBundle, 3 );
	//STARBOARD_RAD_LATCH_1_6_REL_2.Connect( pBundle, 4 );
	//STARBOARD_RAD_LATCH_1_6_LAT_2.Connect( pBundle, 5 );
	PORT_RAD_LATCH_7_12_MOTOR_2_PWR.Connect( pBundle, 6 );
	PORT_RAD_LATCH_7_12_REL_2.Connect( pBundle, 7 );
	PORT_RAD_LATCH_7_12_LAT_2.Connect( pBundle, 8 );
	//STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR.Connect( pBundle, 9 );
	//STARBOARD_RAD_LATCH_7_12_REL_2.Connect( pBundle, 10 );
	//STARBOARD_RAD_LATCH_7_12_LAT_2.Connect( pBundle, 11 );
	PORT_RAD_LATCH_REL_2.Connect( pBundle, 12 );
	PORT_RAD_LATCH_LAT_2.Connect( pBundle, 13 );
	//STARBOARD_RAD_LATCH_REL_2.Connect( pBundle, 14 );
	//STARBOARD_RAD_LATCH_LAT_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorMotorInd", 16 );
	//PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 1 );
	//PORT_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 2 );
	//STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 3 );
	//STARBOARD_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 4 );
	//STARBOARD_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 5 );
	PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 6 );
	PORT_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 7 );
	PORT_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 8 );
	//STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 9 );
	//STARBOARD_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 10 );
	//STARBOARD_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	//LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
	//L_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	//LH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	//LH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	LH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	LH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	//LH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	//LH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	//LH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	//LH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	//LH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	//LH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	//LH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	//LH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	//LH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
	//R_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//R_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//R_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	RH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	RH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	//RH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	//RH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	RH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	RH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	RH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	RH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	RH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	RH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	//RH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	//RH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	//RH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2A", 16 );
	//LH_VENTS_1_2_MOTOR_2_OPEN_A.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_2_CLOSE_A.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_2_PURGE_A.Connect( pBundle, 2 );
	//LH_VENT_3_MOTOR_2_OPEN_A.Connect( pBundle, 3 );
	//LH_VENT_3_MOTOR_2_CLOSE_A.Connect( pBundle, 4 );
	LH_VENTS_4_7_MOTOR_2_OPEN_A.Connect( pBundle, 5 );
	LH_VENTS_4_7_MOTOR_2_CLOSE_A.Connect( pBundle, 6 );
	//LH_VENT_5_MOTOR_2_OPEN_A.Connect( pBundle, 7 );
	//LH_VENT_5_MOTOR_2_CLOSE_A.Connect( pBundle, 8 );
	//LH_VENT_6_MOTOR_2_OPEN_A.Connect( pBundle, 9 );
	//LH_VENT_6_MOTOR_2_CLOSE_A.Connect( pBundle, 10 );
	//LH_VENT_6_MOTOR_2_PRG_1_A.Connect( pBundle, 11 );
	//LH_VENT_6_MOTOR_2_PRG_2_A.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_2_OPEN_A.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_2_CLOSE_A.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_2_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2B", 16 );
	//LH_VENTS_1_2_MOTOR_2_OPEN_B.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_2_CLOSE_B.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_2_PURGE_B.Connect( pBundle, 2 );
	//LH_VENT_3_MOTOR_2_OPEN_B.Connect( pBundle, 3 );
	//LH_VENT_3_MOTOR_2_CLOSE_B.Connect( pBundle, 4 );
	LH_VENTS_4_7_MOTOR_2_OPEN_B.Connect( pBundle, 5 );
	LH_VENTS_4_7_MOTOR_2_CLOSE_B.Connect( pBundle, 6 );
	//LH_VENT_5_MOTOR_2_OPEN_B.Connect( pBundle, 7 );
	//LH_VENT_5_MOTOR_2_CLOSE_B.Connect( pBundle, 8 );
	//LH_VENT_6_MOTOR_2_OPEN_B.Connect( pBundle, 9 );
	//LH_VENT_6_MOTOR_2_CLOSE_B.Connect( pBundle, 10 );
	//LH_VENT_6_MOTOR_2_PRG_1_B.Connect( pBundle, 11 );
	//LH_VENT_6_MOTOR_2_PRG_2_B.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_2_OPEN_B.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_2_CLOSE_B.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_2_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2A", 16 );
	//RH_VENTS_1_2_MOTOR_2_OPEN_A.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_2_CLOSE_A.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_2_PURGE_A.Connect( pBundle, 2 );
	RH_VENT_3_MOTOR_2_OPEN_A.Connect( pBundle, 3 );
	RH_VENT_3_MOTOR_2_CLOSE_A.Connect( pBundle, 4 );
	//RH_VENTS_4_7_MOTOR_2_OPEN_A.Connect( pBundle, 5 );
	//RH_VENTS_4_7_MOTOR_2_CLOSE_A.Connect( pBundle, 6 );
	RH_VENT_5_MOTOR_2_OPEN_A.Connect( pBundle, 7 );
	RH_VENT_5_MOTOR_2_CLOSE_A.Connect( pBundle, 8 );
	RH_VENT_6_MOTOR_2_OPEN_A.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_2_CLOSE_A.Connect( pBundle, 10 );
	RH_VENT_6_MOTOR_2_PRG_1_A.Connect( pBundle, 11 );
	RH_VENT_6_MOTOR_2_PRG_2_A.Connect( pBundle, 12 );
	//RH_VENTS_8_9_MOTOR_2_OPEN_A.Connect( pBundle, 13 );
	//RH_VENTS_8_9_MOTOR_2_CLOSE_A.Connect( pBundle, 14 );
	//RH_VENTS_8_9_MOTOR_2_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2B", 16 );
	//RH_VENTS_1_2_MOTOR_2_OPEN_B.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_2_CLOSE_B.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_2_PURGE_B.Connect( pBundle, 2 );
	RH_VENT_3_MOTOR_2_OPEN_B.Connect( pBundle, 3 );
	RH_VENT_3_MOTOR_2_CLOSE_B.Connect( pBundle, 4 );
	//RH_VENTS_4_7_MOTOR_2_OPEN_B.Connect( pBundle, 5 );
	//RH_VENTS_4_7_MOTOR_2_CLOSE_B.Connect( pBundle, 6 );
	RH_VENT_5_MOTOR_2_OPEN_B.Connect( pBundle, 7 );
	RH_VENT_5_MOTOR_2_CLOSE_B.Connect( pBundle, 8 );
	RH_VENT_6_MOTOR_2_OPEN_B.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_2_CLOSE_B.Connect( pBundle, 10 );
	RH_VENT_6_MOTOR_2_PRG_1_B.Connect( pBundle, 11 );
	RH_VENT_6_MOTOR_2_PRG_2_B.Connect( pBundle, 12 );
	//RH_VENTS_8_9_MOTOR_2_OPEN_B.Connect( pBundle, 13 );
	//RH_VENTS_8_9_MOTOR_2_CLOSE_B.Connect( pBundle, 14 );
	//RH_VENTS_8_9_MOTOR_2_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "KuBandAntennaCommand", 16 );
	KU_ANTENNA_DIRECT_STOW_ON.Connect( pBundle, 0 );
	KU_ANTENNA_STOW.Connect( pBundle, 1 );
	KU_ANTENNA_DEPLOY.Connect( pBundle, 2 );

	pBundle = BundleManager()->CreateBundle( "KuBandAntennaControl", 16 );
	BOOM_STOW_ENABLE_I.Connect( pBundle, 0 );
	BOOM_STOW_ENABLE_II.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "KuBandAntennaMotorInd", 16 );
	//KU_RNDZ_RADAR_MOTOR_1_PWR.Connect( pBundle, 0 );
	//KU_RNDZ_RADAR_STO_IND_1.Connect( pBundle, 1 );
	//KU_RNDZ_RADAR_DPY_IND_1.Connect( pBundle, 2 );
	KU_RNDZ_RADAR_MOTOR_2_PWR.Connect( pBundle, 3 );
	KU_RNDZ_RADAR_STO_IND_2.Connect( pBundle, 4 );
	KU_RNDZ_RADAR_DPY_IND_2.Connect( pBundle, 5 );
	//KU_RNDZ_RADAR_STO_IND.Connect( pBundle, 6 );
	//KU_RNDZ_RADAR_DPY_IND.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "MPM_D&C", 16 );
	PORT_MPM_STOW.Connect( pBundle, 0 );
	PORT_MPM_DEPLOY.Connect( pBundle, 1 );
	//PORT_MPM_SYSTEM_1_STOW.Connect( pBundle, 2 );
	//PORT_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 3 );
	//PORT_MPM_SYSTEM_2_STOW.Connect( pBundle, 4 );
	//PORT_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 5 );
	STBD_MPM_STOW.Connect( pBundle, 6 );
	STBD_MPM_DEPLOY.Connect( pBundle, 7 );
	STBD_MPM_SYSTEM_1_STOW.Connect( pBundle, 8 );
	STBD_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 9 );
	//STBD_MPM_SYSTEM_2_STOW.Connect( pBundle, 10 );
	//STBD_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
	PORT_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	//PORT_FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
	//PORT_MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
	//PORT_AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
	PORT_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
	//PORT_FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	//PORT_MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
	//PORT_AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
	//PORT_SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
	//PORT_FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
	//PORT_MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
	//PORT_AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
	//PORT_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
	//PORT_FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
	//PORT_MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
	//PORT_AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "STBD_MPM_IND", 16 );
	STBD_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	STBD_FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
	STBD_MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
	STBD_AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
	STBD_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
	STBD_FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	STBD_MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
	STBD_AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
	STBD_SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
	//STBD_FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
	//STBD_MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
	//STBD_AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
	STBD_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
	//STBD_FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
	//STBD_MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
	//STBD_AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_PWR", 16 );
	PORT_MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	PORT_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	//PORT_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	//PORT_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	//PORT_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	//PORT_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	//PORT_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	PORT_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "STBD_MPM_PWR", 16 );
	//STBD_MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
	STBD_MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
	//STBD_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	//STBD_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	STBD_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	//STBD_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	//STBD_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	//STBD_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	STBD_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	//STBD_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "MRL_D&C", 16 );
	PORT_MRL_LATCH.Connect( pBundle, 0 );
	PORT_MRL_RELEASE.Connect( pBundle, 1 );
	//PORT_MRL_LATCHED.Connect( pBundle, 2 );
	//PORT_MRL_RELEASED.Connect( pBundle, 3 );
	STBD_MRL_LATCH.Connect( pBundle, 4 );
	STBD_MRL_RELEASE.Connect( pBundle, 5 );
	STBD_MRL_LATCHED.Connect( pBundle, 6 );
	STBD_MRL_RELEASED.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
	//PORT_FWD_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	//PORT_FWD_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	PORT_FWD_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	PORT_FWD_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_FWD_RETNN_RFL_2.Connect( pBundle, 5 );
	STBD_FWD_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	STBD_FWD_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	//STBD_FWD_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_FWD_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_FWD_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_FWD_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
	//PORT_MID_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	//PORT_MID_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	PORT_MID_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	PORT_MID_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_MID_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_MID_RETNN_RFL_2.Connect( pBundle, 5 );
	STBD_MID_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	STBD_MID_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	//STBD_MID_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_MID_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_MID_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_MID_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
	//PORT_AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	//PORT_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_AFT_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	//PORT_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_AFT_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_AFT_RETNN_RFL_2.Connect( pBundle, 5 );
	STBD_AFT_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	STBD_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	//STBD_AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_AFT_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_AFT_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_PWR", 16 );
	//PORT_FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_FWD_MRL_IND_1_PWR.Connect( pBundle, 2 );
	PORT_FWD_MRL_IND_2_PWR.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	PORT_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	STBD_FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	//STBD_FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	STBD_FWD_MRL_IND_1_PWR.Connect( pBundle, 8 );
	//STBD_FWD_MRL_IND_2_PWR.Connect( pBundle, 9 );
	STBD_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	//STBD_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MID_MRL_PWR", 16 );
	//PORT_MID_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_MID_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_MID_MRL_IND_1_PWR.Connect( pBundle, 2 );
	PORT_MID_MRL_IND_2_PWR.Connect( pBundle, 3 );
	//PORT_MID_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	PORT_MID_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	STBD_MID_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	//STBD_MID_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	STBD_MID_MRL_IND_1_PWR.Connect( pBundle, 8 );
	//STBD_MID_MRL_IND_2_PWR.Connect( pBundle, 9 );
	STBD_MID_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	//STBD_MID_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

	//pBundle = BundleManager()->CreateBundle( "AFT_MRL_PWR", 16 );
	//PORT_AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_AFT_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_AFT_MRL_IND_2_PWR.Connect( pBundle, 3 );
	//PORT_AFT_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_AFT_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	//STBD_AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	//STBD_AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	//STBD_AFT_MRL_IND_1_PWR.Connect( pBundle, 8 );
	//STBD_AFT_MRL_IND_2_PWR.Connect( pBundle, 9 );
	//STBD_AFT_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	//STBD_AFT_RETNN_RFL_2_PWR.Connect( pBundle, 11 );
	return;
}

void MMC4::OnPreStep( double simt, double simdt, double mjd )
{
	// MPM indication power and position status
	PORT_MPM_SHOULDER_2_IND_PWR.SetLine();
	PORT_MPM_AFT_2_IND_PWR.SetLine();

	STBD_MPM_FWD_1_IND_PWR.SetLine();
	STBD_MPM_AFT_1_IND_PWR.SetLine();

	if (STBD_SHLD_MECH_STOW_IND_1 && STBD_FWD_MECH_STOW_IND_1 && STBD_MID_MECH_STOW_IND_1 && STBD_AFT_MECH_STOW_IND_1) STBD_MPM_SYSTEM_1_STOW.SetLine();
	else STBD_MPM_SYSTEM_1_STOW.ResetLine();

	if (STBD_SHLD_MECH_DEPLOY_IND_1 && STBD_FWD_MECH_DEPLOY_IND_1 && STBD_MID_MECH_DEPLOY_IND_1 && STBD_AFT_MECH_DEPLOY_IND_1) STBD_MPM_SYSTEM_1_DEPLOY.SetLine();
	else STBD_MPM_SYSTEM_1_DEPLOY.ResetLine();

	// MRL position status
	if (STBD_FWD_MRL_LATCH_IND_1 && STBD_MID_MRL_LATCH_IND_1 && STBD_AFT_MRL_LATCH_IND_1) STBD_MRL_LATCHED.SetLine();
	else STBD_MRL_LATCHED.ResetLine();

	if (STBD_FWD_MRL_RELEASE_IND_1 && STBD_MID_MRL_RELEASE_IND_1 && STBD_AFT_MRL_RELEASE_IND_1) STBD_MRL_RELEASED.SetLine();
	else STBD_MRL_RELEASED.ResetLine();

	// TODO missing logic
	bool K49 = PL_BAY_MECH_PWR_SYS_2;
	bool K61 = PL_BAY_MECH_PWR_SYS_2;
	bool K30 = PL_BAY_MECH_PWR_SYS_2;
	bool K42 = PL_BAY_MECH_PWR_SYS_2;

	// VENT DOORS
	// left no 4/7 motor 2
	bool K9 = LH_VENTS_4_7_MOTOR_2_CLOSE_A && !LH_VENTS_4_AND_7_CLOSE_2;// CLS A
	bool K21 = LH_VENTS_4_7_MOTOR_2_CLOSE_B && !LH_VENTS_4_AND_7_CLOSE_2;// CLS B
	bool K11 = LH_VENTS_4_7_MOTOR_2_OPEN_A && !LH_VENTS_4_AND_7_OPEN_2;// OPN A
	bool K23 = LH_VENTS_4_7_MOTOR_2_OPEN_B && !LH_VENTS_4_AND_7_OPEN_2;// OPN B

	if (K11 && K23)
	{
		if (K9 && K21) LH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( 0.0f );
		else LH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K9 && K21) LH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( -1.0f );
		else LH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right no 6 motor 2
	K19 = (!RH_VENT_6_PURGE_2_IND_2 && RH_VENT_6_CLOSE_2) || (K19 && !RH_VENT_6_PURGE_2_IND_2) || (K19 && RH_VENT_6_CLOSE_2);
	K17 = (!RH_VENT_6_CLOSE_2 && RH_VENT_6_PURGE_2_IND_2) || (K17 && !RH_VENT_6_CLOSE_2) || (K17 && RH_VENT_6_PURGE_2_IND_2);
	K7 = (!RH_VENT_6_PURGE_1_IND_2 && RH_VENT_6_OPEN_2) || (K7 && !RH_VENT_6_PURGE_1_IND_2) || (K7 && RH_VENT_6_OPEN_2);
	K5 = (!RH_VENT_6_OPEN_2 && RH_VENT_6_PURGE_1_IND_2) || (K5 && !RH_VENT_6_OPEN_2) || (K5 && RH_VENT_6_PURGE_1_IND_2);

	bool PRG1_2A = RH_VENT_6_MOTOR_2_PRG_1_A && !RH_VENT_6_PURGE_1_IND_2;
	bool PRG1_2B = RH_VENT_6_MOTOR_2_PRG_1_B && !RH_VENT_6_PURGE_1_IND_2;
	bool PRG2_2A = RH_VENT_6_MOTOR_2_PRG_2_A && !RH_VENT_6_PURGE_2_IND_2;
	bool PRG2_2B = RH_VENT_6_MOTOR_2_PRG_2_B && !RH_VENT_6_PURGE_2_IND_2;

	bool K1 = (RH_VENT_6_MOTOR_2_OPEN_A || (PRG1_2A && K19) || (PRG2_2A && K5)) && !RH_VENT_6_OPEN_2;// OPN A
	bool K13 = (RH_VENT_6_MOTOR_2_OPEN_B || (PRG1_2B && K19) || (PRG2_2B && K5)) && !RH_VENT_6_OPEN_2;// OPN B
	bool K3 = (RH_VENT_6_MOTOR_2_CLOSE_A || (PRG1_2A && K17) || (PRG2_2A && K7)) && !RH_VENT_6_CLOSE_2;// CLS A
	bool K15 = (RH_VENT_6_MOTOR_2_CLOSE_B || (PRG1_2B && K17) || (PRG2_2B && K7)) && !RH_VENT_6_CLOSE_2;// CLS B

	if (K1 && K13)
	{
		if (K3 && K15) RH_VENT_6_MOTOR_2_PWR.SetLine( 0.0f );
		else RH_VENT_6_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K3 && K15) RH_VENT_6_MOTOR_2_PWR.SetLine( -1.0f );
		else RH_VENT_6_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// PAYLOAD BAY DOORS
	// stbd pdu motor 2
	// port fwd bkhd latch motor 2
	// stbd fwd bkhd latch motor 2

	// KU BAND
	// ant a deploy motor 2
	bool KU_ANTENNA_GND = !KU_ANTENNA_DEPLOY && !KU_ANTENNA_STOW;// HACK due to switch implementation limitations
	bool K25 = (KU_ANTENNA_DIRECT_STOW_ON || KU_ANTENNA_STOW) && ((KU_ANTENNA_DIRECT_STOW_ON || BOOM_STOW_ENABLE_I) && !KU_RNDZ_RADAR_STO_IND_2);// STW I
	bool K37 = (KU_ANTENNA_GND || KU_ANTENNA_DEPLOY) && ((cmd_V54K0004N || KU_ANTENNA_DEPLOY) && !KU_RNDZ_RADAR_DPY_IND_2);// DPY B
	bool K27 = (KU_ANTENNA_GND || KU_ANTENNA_DEPLOY) && ((cmd_V54K0014N || KU_ANTENNA_DEPLOY) && !KU_RNDZ_RADAR_DPY_IND_2);// DPY A
	bool K2 = (KU_ANTENNA_DIRECT_STOW_ON || KU_ANTENNA_STOW) && ((KU_ANTENNA_DIRECT_STOW_ON || BOOM_STOW_ENABLE_II) && !KU_RNDZ_RADAR_STO_IND_2);// STW II

	if (K49 && K61)
	{
		if (K37 && K27)
		{
			if (K25 && K2) KU_RNDZ_RADAR_MOTOR_2_PWR.SetLine( 0.0f );
			else KU_RNDZ_RADAR_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K25 && K2) KU_RNDZ_RADAR_MOTOR_2_PWR.SetLine( -1.0f );
			else KU_RNDZ_RADAR_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else KU_RNDZ_RADAR_MOTOR_2_PWR.SetLine( 0.0f );

	// FREON RAD
	// port sys b latch 1-6 motor 2
	bool K63 = RADIATOR_LATCH_CONTROL_SYS_B_RELEASE && !PORT_RAD_LATCH_1_6_REL_2;// REL
	bool K51 = RADIATOR_LATCH_CONTROL_SYS_B_LATCH && !PORT_RAD_LATCH_1_6_LAT_2;// LCH

	if (K49 && K61)
	{
		if (K63)
		{
			if (K51) PORT_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K51) PORT_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_RAD_LATCH_1_6_MOTOR_2_PWR.SetLine( 0.0f );

	// REMOTE MANIPULATOR
	// port mid retn latch motor 2
	bool K78 = true;// TODO deadface
	bool K59 = K78 && (PORT_MRL_RELEASE && !PORT_MID_MRL_RELEASE_IND_2);// REL
	bool K71 = K78 && (PORT_MRL_LATCH && !PORT_MID_MRL_LATCH_IND_2);// LCH

	if (K49 && K61)
	{
		if (K59)
		{
			if (K71) PORT_MID_MRL_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_MID_MRL_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K71) PORT_MID_MRL_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_MID_MRL_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_MID_MRL_MOTOR_2_PWR.SetLine( 0.0f );

	if (K78)
	{
		PORT_MID_MRL_IND_2_PWR.SetLine();
		PORT_MID_RETNN_RFL_2_PWR.SetLine();
	}
	else
	{
		PORT_MID_MRL_IND_2_PWR.ResetLine();
		PORT_MID_RETNN_RFL_2_PWR.ResetLine();
	}

	// stbd mid retn latch motor 1
	bool K76 = true;// TODO deadface and coil ID
	bool K69 = K76 && (STBD_MRL_LATCH && !STBD_MID_MRL_LATCH_IND_1);// LCH
	bool K57 = K76 && (STBD_MRL_RELEASE && !STBD_MID_MRL_RELEASE_IND_1);// REL

	if (K49 && K61)
	{
		if (K57)
		{
			if (K69) STBD_MID_MRL_MOTOR_1_PWR.SetLine( 0.0f );
			else STBD_MID_MRL_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K69) STBD_MID_MRL_MOTOR_1_PWR.SetLine( -1.0f );
			else STBD_MID_MRL_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STBD_MID_MRL_MOTOR_1_PWR.SetLine( 0.0f );

	if (K76)
	{
		STBD_MID_MRL_IND_1_PWR.SetLine();
		STBD_MID_RETNN_RFL_1_PWR.SetLine();
	}
	else
	{
		STBD_MID_MRL_IND_1_PWR.ResetLine();
		STBD_MID_RETNN_RFL_1_PWR.ResetLine();
	}

	// VENT DOORS
	// right no 3 motor 2
	bool K79 = RH_VENT_3_MOTOR_2_CLOSE_A && !RH_VENT_3_CLOSE_2;// CLS A
	bool K77 = RH_VENT_3_MOTOR_2_CLOSE_B && !RH_VENT_3_CLOSE_2;// CLS B
	bool K73 = RH_VENT_3_MOTOR_2_OPEN_A && !RH_VENT_3_OPEN_2;// OPN A
	bool K75 = RH_VENT_3_MOTOR_2_OPEN_B && !RH_VENT_3_OPEN_2;// OPN B

	if (K73 && K75)
	{
		if (K79 && K77) RH_VENT_3_MOTOR_2_PWR.SetLine( 0.0f );
		else RH_VENT_3_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K79 && K77) RH_VENT_3_MOTOR_2_PWR.SetLine( -1.0f );
		else RH_VENT_3_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right no 5 motor 2
	bool K14 = RH_VENT_5_MOTOR_2_OPEN_A && !RH_VENT_5_OPEN_2;// OPN A
	bool K16 = RH_VENT_5_MOTOR_2_OPEN_B && !RH_VENT_5_OPEN_2;// OPN B
	bool K18 = RH_VENT_5_MOTOR_2_CLOSE_A && !RH_VENT_5_CLOSE_2;// CLS A
	bool K6 = RH_VENT_5_MOTOR_2_CLOSE_B && !RH_VENT_5_CLOSE_2;// CLS B

	if (K14 && K16)
	{
		if (K18 && K6) RH_VENT_5_MOTOR_2_PWR.SetLine( 0.0f );
		else RH_VENT_5_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K18 && K6) RH_VENT_5_MOTOR_2_PWR.SetLine( -1.0f );
		else RH_VENT_5_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// PAYLOAD BAY DOORS
	// port pdu motor 1
	// stbd aft bkhd latch motor 1
	// cl 9-12 latch motor 2
	// cl 13-16 latch motor 1

	// FREON RADIATOR
	if (PORT_RAD_LATCH_1_6_LAT_2 && PORT_RAD_LATCH_7_12_LAT_2) PORT_RAD_LATCH_LAT_2.SetLine();
	else PORT_RAD_LATCH_LAT_2.ResetLine();

	bool bPORT_RAD_LATCH_REL_2;
	if (PORT_RAD_LATCH_1_6_REL_2 && PORT_RAD_LATCH_7_12_REL_2)
	{
		PORT_RAD_LATCH_REL_2.SetLine();
		bPORT_RAD_LATCH_REL_2 = true;
	}
	else
	{
		PORT_RAD_LATCH_REL_2.ResetLine();
		bPORT_RAD_LATCH_REL_2 = false;
	}

	if (PORT_RAD_DEPLOYMENT_DPY_1 && PORT_RAD_DEPLOYMENT_DPY_2) RADIATOR_PORT_DPY.SetLine();
	else RADIATOR_PORT_DPY.ResetLine();

	// port sys b deploy motor 2
	bool K34 = RADIATOR_CONTROL_SYS_B_DEPLOY && (bPORT_RAD_LATCH_REL_2 && !PORT_RAD_DEPLOYMENT_DPY_2);// DPY
	bool K32 = RADIATOR_CONTROL_SYS_B_STOW && !PORT_RAD_DEPLOYMENT_STO_2;// STW
	bool K46 = RADIATOR_CONTROL_SYS_B_DEPLOY && !PORT_RAD_DEPLOYMENT_DPY_2;// DPY
	bool K44 = RADIATOR_CONTROL_SYS_B_STOW && !PORT_RAD_DEPLOYMENT_STO_2;// STW

	if (K30 && K42)
	{
		if (K34 && K46)
		{
			if (K32 && K44) PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K32 && K44) PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.SetLine( 0.0f );

	// port sys b latch 7-12 motor 2
	bool K48 = RADIATOR_LATCH_CONTROL_SYS_B_LATCH && !PORT_RAD_LATCH_7_12_LAT_2;// LCH
	bool K36 = RADIATOR_LATCH_CONTROL_SYS_B_RELEASE && !PORT_RAD_LATCH_7_12_REL_2;// REL

	if (K30 && K42)
	{
		if (K36)
		{
			if (K48) PORT_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K48) PORT_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_RAD_LATCH_7_12_MOTOR_2_PWR.SetLine( 0.0f );

	// REMOTE MANIPULATOR
	// port deploy motor 1
	bool K60 = PORT_MPM_STOW && !PORT_SHLD_MECH_STOW_IND_1;// STW
	bool K72 = PORT_MPM_DEPLOY && !PORT_SHLD_MECH_DEPLOY_IND_1;// DPY

	if (K30 && K42)
	{
		if (K72)
		{
			if (K60) PORT_MPM_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_MPM_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K60) PORT_MPM_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_MPM_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_MPM_MOTOR_1_PWR.SetLine( 0.0f );

	// stbd deploy motor 2
	bool K50 = STBD_MPM_DEPLOY && !STBD_SHLD_MECH_DEPLOY_IND_2;// DPY
	bool K62 = STBD_MPM_STOW && !STBD_SHLD_MECH_STOW_IND_2;// STW

	if (K30 && K42)
	{
		if (K50)
		{
			if (K62) STBD_MPM_MOTOR_2_PWR.SetLine( 0.0f );
			else STBD_MPM_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K62) STBD_MPM_MOTOR_2_PWR.SetLine( -1.0f );
			else STBD_MPM_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STBD_MPM_MOTOR_2_PWR.SetLine( 0.0f );

	// port fwd retn latch motor 2
	bool K68 = true;// TODO deadface
	bool K66 = K68 && (PORT_MRL_LATCH && !PORT_FWD_MRL_LATCH_IND_2);// LCH
	bool K54 = K68 && (PORT_MRL_RELEASE && !PORT_FWD_MRL_RELEASE_IND_2);// REL

	if (K30 && K42)
	{
		if (K54)
		{
			if (K66) PORT_FWD_MRL_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_FWD_MRL_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K66) PORT_FWD_MRL_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_FWD_MRL_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_FWD_MRL_MOTOR_2_PWR.SetLine( 0.0f );

	if (K68)
	{
		PORT_FWD_MRL_IND_2_PWR.SetLine();
		PORT_FWD_RETNN_RFL_2_PWR.SetLine();
	}
	else
	{
		PORT_FWD_MRL_IND_2_PWR.ResetLine();
		PORT_FWD_RETNN_RFL_2_PWR.ResetLine();
	}

	// stbd fwd retn latch motor 1
	bool K99 = true;// TODO deadface and coil ID
	bool K64 = K99 && (STBD_MRL_LATCH && !STBD_FWD_MRL_LATCH_IND_1);// LCH
	bool K52 = K99 && (STBD_MRL_RELEASE && !STBD_FWD_MRL_RELEASE_IND_1);// REL

	if (K49 && K61)
	{
		if (K52)
		{
			if (K64) STBD_FWD_MRL_MOTOR_1_PWR.SetLine( 0.0f );
			else STBD_FWD_MRL_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K64) STBD_FWD_MRL_MOTOR_1_PWR.SetLine( -1.0f );
			else STBD_FWD_MRL_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STBD_FWD_MRL_MOTOR_1_PWR.SetLine( 0.0f );

	if (K99)
	{
		STBD_FWD_MRL_IND_1_PWR.SetLine();
		STBD_FWD_RETNN_RFL_1_PWR.SetLine();
	}
	else
	{
		STBD_FWD_MRL_IND_1_PWR.ResetLine();
		STBD_FWD_RETNN_RFL_1_PWR.ResetLine();
	}
	return;
}
