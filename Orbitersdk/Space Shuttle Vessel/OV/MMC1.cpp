/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/23   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/23   GLS
2022/01/25   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/05/14   GLS
2022/05/15   GLS
2022/05/16   GLS
2022/08/05   GLS
********************************************/
#include "MMC1.h"


MMC1::MMC1( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "MMC1" ),
K81(false), K69(false), K83(false), K71(false)
{
}

MMC1::~MMC1()
{
}

void MMC1::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PL_BAY_MECH_PWR_SYS_1.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	//LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 6 );
	RH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 8 );
	RH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	//LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
	//L_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	//LH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	//LH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	//LH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	//LH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	LH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	LH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	//LH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	//LH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	//LH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	//LH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	//LH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	//LH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	//LH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
	//R_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	//R_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	//R_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	RH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	RH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	//RH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	//RH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	RH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	RH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	RH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	RH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	RH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	RH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	//RH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	//RH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	//RH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2A", 16 );
	//LH_VENTS_1_2_MOTOR_2_OPEN_A.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_2_CLOSE_A.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_2_PURGE_A.Connect( pBundle, 2 );
	//LH_VENT_3_MOTOR_2_OPEN_A.Connect( pBundle, 3 );
	//LH_VENT_3_MOTOR_2_CLOSE_A.Connect( pBundle, 4 );
	//LH_VENTS_4_7_MOTOR_2_OPEN_A.Connect( pBundle, 5 );
	//LH_VENTS_4_7_MOTOR_2_CLOSE_A.Connect( pBundle, 6 );
	LH_VENT_5_MOTOR_2_OPEN_A.Connect( pBundle, 7 );
	LH_VENT_5_MOTOR_2_CLOSE_A.Connect( pBundle, 8 );
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
	//LH_VENTS_4_7_MOTOR_2_OPEN_B.Connect( pBundle, 5 );
	//LH_VENTS_4_7_MOTOR_2_CLOSE_B.Connect( pBundle, 6 );
	LH_VENT_5_MOTOR_2_OPEN_B.Connect( pBundle, 7 );
	LH_VENT_5_MOTOR_2_CLOSE_B.Connect( pBundle, 8 );
	//LH_VENT_6_MOTOR_2_OPEN_B.Connect( pBundle, 9 );
	//LH_VENT_6_MOTOR_2_CLOSE_B.Connect( pBundle, 10 );
	//LH_VENT_6_MOTOR_2_PRG_1_B.Connect( pBundle, 11 );
	//LH_VENT_6_MOTOR_2_PRG_2_B.Connect( pBundle, 12 );
	//LH_VENTS_8_9_MOTOR_2_OPEN_B.Connect( pBundle, 13 );
	//LH_VENTS_8_9_MOTOR_2_CLOSE_B.Connect( pBundle, 14 );
	//LH_VENTS_8_9_MOTOR_2_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1A", 16 );
	//RH_VENTS_1_2_MOTOR_1_OPEN_A.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_1_CLOSE_A.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_1_PURGE_A.Connect( pBundle, 2 );
	RH_VENT_3_MOTOR_1_OPEN_A.Connect( pBundle, 3 );
	RH_VENT_3_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
	//RH_VENTS_4_7_MOTOR_1_OPEN_A.Connect( pBundle, 5 );
	//RH_VENTS_4_7_MOTOR_1_CLOSE_A.Connect( pBundle, 6 );
	RH_VENT_5_MOTOR_1_OPEN_A.Connect( pBundle, 7 );
	RH_VENT_5_MOTOR_1_CLOSE_A.Connect( pBundle, 8 );
	RH_VENT_6_MOTOR_1_OPEN_A.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_1_CLOSE_A.Connect( pBundle, 10 );
	RH_VENT_6_MOTOR_1_PRG_1_A.Connect( pBundle, 11 );
	RH_VENT_6_MOTOR_1_PRG_2_A.Connect( pBundle, 12 );
	//RH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 13 );
	//RH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 14 );
	//RH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1B", 16 );
	//RH_VENTS_1_2_MOTOR_1_OPEN_B.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_1_CLOSE_B.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_1_PURGE_B.Connect( pBundle, 2 );
	RH_VENT_3_MOTOR_1_OPEN_B.Connect( pBundle, 3 );
	RH_VENT_3_MOTOR_1_CLOSE_B.Connect( pBundle, 4 );
	//RH_VENTS_4_7_MOTOR_1_OPEN_B.Connect( pBundle, 5 );
	//RH_VENTS_4_7_MOTOR_1_CLOSE_B.Connect( pBundle, 6 );
	RH_VENT_5_MOTOR_1_OPEN_B.Connect( pBundle, 7 );
	RH_VENT_5_MOTOR_1_CLOSE_B.Connect( pBundle, 8 );
	RH_VENT_6_MOTOR_1_OPEN_B.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_1_CLOSE_B.Connect( pBundle, 10 );
	RH_VENT_6_MOTOR_1_PRG_1_B.Connect( pBundle, 11 );
	RH_VENT_6_MOTOR_1_PRG_2_B.Connect( pBundle, 12 );
	//RH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 13 );
	//RH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 14 );
	//RH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorControl", 16 );
	RADIATOR_LATCH_CONTROL_SYS_A_RELEASE.Connect( pBundle, 0 );
	RADIATOR_LATCH_CONTROL_SYS_A_LATCH.Connect( pBundle, 1 );
	RADIATOR_CONTROL_SYS_A_DEPLOY.Connect( pBundle, 8 );
	RADIATOR_CONTROL_SYS_A_STOW.Connect( pBundle, 9 );
	RADIATOR_PORT_STO.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "RadiatorLatchMotorInd_1", 16 );
	PORT_RAD_LATCH_1_6_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_RAD_LATCH_1_6_REL_1.Connect( pBundle, 1 );
	PORT_RAD_LATCH_1_6_LAT_1.Connect( pBundle, 2 );
	//STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.Connect( pBundle, 3 );
	//STARBOARD_RAD_LATCH_1_6_REL_1.Connect( pBundle, 4 );
	//STARBOARD_RAD_LATCH_1_6_LAT_1.Connect( pBundle, 5 );
	PORT_RAD_LATCH_7_12_MOTOR_1_PWR.Connect( pBundle, 6 );
	PORT_RAD_LATCH_7_12_REL_1.Connect( pBundle, 7 );
	PORT_RAD_LATCH_7_12_LAT_1.Connect( pBundle, 8 );
	//STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.Connect( pBundle, 9 );
	//STARBOARD_RAD_LATCH_7_12_REL_1.Connect( pBundle, 10 );
	//STARBOARD_RAD_LATCH_7_12_LAT_1.Connect( pBundle, 11 );
	PORT_RAD_LATCH_REL_1.Connect( pBundle, 12 );
	PORT_RAD_LATCH_LAT_1.Connect( pBundle, 13 );
	//STARBOARD_RAD_LATCH_REL_1.Connect( pBundle, 14 );
	//STARBOARD_RAD_LATCH_LAT_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorMotorInd", 16 );
	PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 0 );
	PORT_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 1 );
	PORT_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 2 );
	//STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 3 );
	//STARBOARD_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 4 );
	//STARBOARD_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 5 );
	//PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 6 );
	//PORT_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 7 );
	PORT_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 8 );
	//STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 9 );
	//STARBOARD_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 10 );
	//STARBOARD_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PL_RETENTION_A6U_MMC", 16 );
	PL_RETENTION_1_RELEASE.Connect( pBundle, 0 );
	PL_RETENTION_1_LATCH.Connect( pBundle, 1 );
	PL_RETENTION_2_RELEASE.Connect( pBundle, 2 );
	PL_RETENTION_2_LATCH.Connect( pBundle, 3 );
	PL_RETENTION_3_RELEASE.Connect( pBundle, 4 );
	PL_RETENTION_3_LATCH.Connect( pBundle, 5 );
	PL_RETENTION_4_RELEASE.Connect( pBundle, 6 );
	PL_RETENTION_4_LATCH.Connect( pBundle, 7 );
	PL_RETENTION_5_RELEASE.Connect( pBundle, 8 );
	PL_RETENTION_5_LATCH.Connect( pBundle, 9 );
	LOGIC_POWER_SYS_1A.Connect( pBundle, 10 );
	LOGIC_POWER_SYS_2A.Connect( pBundle, 11 );
	LOGIC_POWER_SYS_3A.Connect( pBundle, 12 );
	//LOGIC_POWER_SYS_1B.Connect( pBundle, 13 );
	//LOGIC_POWER_SYS_2B.Connect( pBundle, 14 );
	//LOGIC_POWER_SYS_3B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 10 );
	PL_1_SEL_1A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_1A.Connect( pBundle, 2 );
	PL_1_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_1.Connect( pBundle, 4 );
	//PL_1_SEL_1B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_1B.Connect( pBundle, 7 );
	//PL_1_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 10 );
	PL_1_SEL_2A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_2A.Connect( pBundle, 2 );
	PL_1_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_2.Connect( pBundle, 4 );
	//PL_1_SEL_2B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_2B.Connect( pBundle, 7 );
	//PL_1_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 10 );
	PL_1_SEL_3A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_3A.Connect( pBundle, 2 );
	PL_1_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_3.Connect( pBundle, 4 );
	//PL_1_SEL_3B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_3B.Connect( pBundle, 7 );
	//PL_1_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 10 );
	PL_1_SEL_4A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_4A.Connect( pBundle, 2 );
	PL_1_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_4.Connect( pBundle, 4 );
	//PL_1_SEL_4B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_4B.Connect( pBundle, 7 );
	//PL_1_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 10 );
	PL_1_SEL_5A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_5A.Connect( pBundle, 2 );
	PL_1_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_5.Connect( pBundle, 4 );
	//PL_1_SEL_5B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_5B.Connect( pBundle, 7 );
	//PL_1_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
	PL_2_SEL_1A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_1A.Connect( pBundle, 2 );
	PL_2_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_1.Connect( pBundle, 4 );
	//PL_2_SEL_1B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_1B.Connect( pBundle, 7 );
	//PL_2_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
	PL_2_SEL_2A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_2A.Connect( pBundle, 2 );
	PL_2_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_2.Connect( pBundle, 4 );
	//PL_2_SEL_2B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_2B.Connect( pBundle, 7 );
	//PL_2_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
	PL_2_SEL_3A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_3A.Connect( pBundle, 2 );
	PL_2_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_3.Connect( pBundle, 4 );
	//PL_2_SEL_3B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_3B.Connect( pBundle, 7 );
	//PL_2_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 10 );
	PL_2_SEL_4A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_4A.Connect( pBundle, 2 );
	PL_2_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_4.Connect( pBundle, 4 );
	//PL_2_SEL_4B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_4B.Connect( pBundle, 7 );
	//PL_2_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 10 );
	PL_2_SEL_5A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_5A.Connect( pBundle, 2 );
	PL_2_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_5.Connect( pBundle, 4 );
	//PL_2_SEL_5B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_5B.Connect( pBundle, 7 );
	//PL_2_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 10 );
	PL_3_SEL_1A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_1A.Connect( pBundle, 2 );
	PL_3_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_1.Connect( pBundle, 4 );
	//PL_3_SEL_1B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_1B.Connect( pBundle, 7 );
	//PL_3_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 10 );
	PL_3_SEL_2A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_2A.Connect( pBundle, 2 );
	PL_3_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_2.Connect( pBundle, 4 );
	//PL_3_SEL_2B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_2B.Connect( pBundle, 7 );
	//PL_3_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
	PL_3_SEL_3A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_3A.Connect( pBundle, 2 );
	PL_3_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_3.Connect( pBundle, 4 );
	//PL_3_SEL_3B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_3B.Connect( pBundle, 7 );
	//PL_3_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
	PL_3_SEL_4A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_4A.Connect( pBundle, 2 );
	PL_3_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_4.Connect( pBundle, 4 );
	//PL_3_SEL_4B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_4B.Connect( pBundle, 7 );
	//PL_3_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
	PL_3_SEL_5A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_5A.Connect( pBundle, 2 );
	PL_3_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_5.Connect( pBundle, 4 );
	//PL_3_SEL_5B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_5B.Connect( pBundle, 7 );
	//PL_3_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "MPM_D&C", 16 );
	//PORT_MPM_STOW.Connect( pBundle, 0 );
	//PORT_MPM_DEPLOY.Connect( pBundle, 1 );
	//PORT_MPM_SYSTEM_1_STOW.Connect( pBundle, 2 );
	//PORT_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 3 );
	//PORT_MPM_SYSTEM_2_STOW.Connect( pBundle, 4 );
	//PORT_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 5 );
	//STBD_MPM_STOW.Connect( pBundle, 6 );
	//STBD_MPM_DEPLOY.Connect( pBundle, 7 );
	//STBD_MPM_SYSTEM_1_STOW.Connect( pBundle, 8 );
	//STBD_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 9 );
	STBD_MPM_SYSTEM_2_STOW.Connect( pBundle, 10 );
	STBD_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 11 );

	//pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
	//PORT_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	//PORT_FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
	//PORT_MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
	//PORT_AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
	//PORT_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
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
	//STBD_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	//STBD_FWD_MECH_STOW_IND_1.Connect( pBundle, 1 );
	//STBD_MID_MECH_STOW_IND_1.Connect( pBundle, 2 );
	//STBD_AFT_MECH_STOW_IND_1.Connect( pBundle, 3 );
	//STBD_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
	//STBD_FWD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	//STBD_MID_MECH_DEPLOY_IND_1.Connect( pBundle, 6 );
	//STBD_AFT_MECH_DEPLOY_IND_1.Connect( pBundle, 7 );
	STBD_SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
	STBD_FWD_MECH_STOW_IND_2.Connect( pBundle, 9 );
	STBD_MID_MECH_STOW_IND_2.Connect( pBundle, 10 );
	STBD_AFT_MECH_STOW_IND_2.Connect( pBundle, 11 );
	STBD_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
	STBD_FWD_MECH_DEPLOY_IND_2.Connect( pBundle, 13 );
	STBD_MID_MECH_DEPLOY_IND_2.Connect( pBundle, 14 );
	STBD_AFT_MECH_DEPLOY_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_PWR", 16 );
	//PORT_MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	//PORT_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	//PORT_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	//PORT_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	//PORT_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	PORT_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	//PORT_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	//PORT_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "STBD_MPM_PWR", 16 );
	//STBD_MPM_MOTOR_1_PWR.Connect( pBundle, 0 );
	//STBD_MPM_MOTOR_2_PWR.Connect( pBundle, 1 );
	STBD_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	//STBD_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	//STBD_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	STBD_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	STBD_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	//STBD_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	//STBD_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	//STBD_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "MRL_D&C", 16 );
	PORT_MRL_LATCH.Connect( pBundle, 0 );
	PORT_MRL_RELEASE.Connect( pBundle, 1 );
	//PORT_MRL_LATCHED.Connect( pBundle, 2 );
	//PORT_MRL_RELEASED.Connect( pBundle, 3 );
	STBD_MRL_LATCH.Connect( pBundle, 4 );
	STBD_MRL_RELEASE.Connect( pBundle, 5 );
	//STBD_MRL_LATCHED.Connect( pBundle, 6 );
	//STBD_MRL_RELEASED.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
	//PORT_FWD_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	//PORT_FWD_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_FWD_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	//PORT_FWD_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_FWD_RETNN_RFL_2.Connect( pBundle, 5 );
	//STBD_FWD_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	//STBD_FWD_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	STBD_FWD_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	STBD_FWD_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
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
	//STBD_MID_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_MID_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_MID_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_MID_RETNN_RFL_2.Connect( pBundle, 11 );

	//pBundle = BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
	//PORT_AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	//PORT_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_AFT_MRL_LATCH_IND_2.Connect( pBundle, 2 );
	//PORT_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 3 );
	//PORT_AFT_RETNN_RFL_1.Connect( pBundle, 4 );
	//PORT_AFT_RETNN_RFL_2.Connect( pBundle, 5 );
	//STBD_AFT_MRL_LATCH_IND_1.Connect( pBundle, 6 );
	//STBD_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 7 );
	//STBD_AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_AFT_RETNN_RFL_1.Connect( pBundle, 10 );
	//STBD_AFT_RETNN_RFL_2.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_PWR", 16 );
	//PORT_FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	//PORT_FWD_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_FWD_MRL_IND_2_PWR.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	//STBD_FWD_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	STBD_FWD_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	//STBD_FWD_MRL_IND_1_PWR.Connect( pBundle, 8 );
	STBD_FWD_MRL_IND_2_PWR.Connect( pBundle, 9 );
	//STBD_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
	STBD_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MID_MRL_PWR", 16 );
	PORT_MID_MRL_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_MID_MRL_MOTOR_2_PWR.Connect( pBundle, 1 );
	PORT_MID_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_MID_MRL_IND_2_PWR.Connect( pBundle, 3 );
	PORT_MID_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_MID_RETNN_RFL_2_PWR.Connect( pBundle, 5 );
	//STBD_MID_MRL_MOTOR_1_PWR.Connect( pBundle, 6 );
	//STBD_MID_MRL_MOTOR_2_PWR.Connect( pBundle, 7 );
	//STBD_MID_MRL_IND_1_PWR.Connect( pBundle, 8 );
	//STBD_MID_MRL_IND_2_PWR.Connect( pBundle, 9 );
	//STBD_MID_RETNN_RFL_1_PWR.Connect( pBundle, 10 );
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

void MMC1::OnPreStep( double simt, double simdt, double mjd )
{
	// MPM indication power and position status
	PORT_MPM_MID_2_IND_PWR.SetLine();

	STBD_MPM_SHOULDER_1_IND_PWR.SetLine();
	STBD_MPM_MID_1_IND_PWR.SetLine();
	STBD_MPM_FWD_2_IND_PWR.SetLine();

	if (STBD_SHLD_MECH_STOW_IND_2 && STBD_FWD_MECH_STOW_IND_2 && STBD_MID_MECH_STOW_IND_2 && STBD_AFT_MECH_STOW_IND_2) STBD_MPM_SYSTEM_2_STOW.SetLine();
	else STBD_MPM_SYSTEM_2_STOW.ResetLine();

	if (STBD_SHLD_MECH_DEPLOY_IND_2 && STBD_FWD_MECH_DEPLOY_IND_2 && STBD_MID_MECH_DEPLOY_IND_2 && STBD_AFT_MECH_DEPLOY_IND_2) STBD_MPM_SYSTEM_2_DEPLOY.SetLine();
	else STBD_MPM_SYSTEM_2_DEPLOY.ResetLine();

	// TODO missing logic
	bool K80 = PL_BAY_MECH_PWR_SYS_1;
	bool K84 = PL_BAY_MECH_PWR_SYS_1;

	// VENT DOOR
	// left no 5 motor 2
	bool K82 = LH_VENT_5_MOTOR_2_CLOSE_B && !LH_VENT_5_CLOSE_2;// CLS B
	bool K72 = LH_VENT_5_MOTOR_2_CLOSE_A && !LH_VENT_5_CLOSE_2;// CLS A
	bool K70 = LH_VENT_5_MOTOR_2_OPEN_B && !LH_VENT_5_OPEN_2;// OPN B
	bool K68 = LH_VENT_5_MOTOR_2_OPEN_A && !LH_VENT_5_OPEN_2;// OPN A

	if (K70 && K68)
	{
		if (K82 && K72) LH_VENT_5_MOTOR_2_PWR.SetLine( 0.0f );
		else LH_VENT_5_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K82 && K72) LH_VENT_5_MOTOR_2_PWR.SetLine( -1.0f );
		else LH_VENT_5_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// VENT DOORS
	// right no 3 motor 1
	bool K7 = RH_VENT_3_MOTOR_1_CLOSE_A && !RH_VENT_3_CLOSE_1;// CLS A
	bool K21 = RH_VENT_3_MOTOR_1_CLOSE_B && !RH_VENT_3_CLOSE_1;// CLS B
	bool K11 = RH_VENT_3_MOTOR_1_OPEN_A && !RH_VENT_3_OPEN_1;// OPN A
	bool K9 = RH_VENT_3_MOTOR_1_OPEN_B && !RH_VENT_3_OPEN_1;// OPN B

	if (K11 && K9)
	{
		if (K7 && K21) RH_VENT_3_MOTOR_1_PWR.SetLine( 0.0f );
		else RH_VENT_3_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K7 && K21) RH_VENT_3_MOTOR_1_PWR.SetLine( -1.0f );
		else RH_VENT_3_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// right no 5 motor 1
	bool K1 = RH_VENT_5_MOTOR_1_CLOSE_A && !RH_VENT_5_CLOSE_1;// CLS A
	bool K15 = RH_VENT_5_MOTOR_1_CLOSE_B && !RH_VENT_5_CLOSE_1;// CLS B
	bool K5 = RH_VENT_5_MOTOR_1_OPEN_A && !RH_VENT_5_OPEN_1;// OPN A
	bool K3 = RH_VENT_5_MOTOR_1_OPEN_B && !RH_VENT_5_OPEN_1;// OPN B

	if (K5 && K3)
	{
		if (K1 && K15) RH_VENT_5_MOTOR_1_PWR.SetLine( 0.0f );
		else RH_VENT_5_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K1 && K15) RH_VENT_5_MOTOR_1_PWR.SetLine( -1.0f );
		else RH_VENT_5_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// right no 6 motor 1
	K81 = (!RH_VENT_6_PURGE_2_IND_1 && RH_VENT_6_CLOSE_1) || (K81 && !RH_VENT_6_PURGE_2_IND_1) || (K81 && RH_VENT_6_CLOSE_1);
	K69 = (!RH_VENT_6_CLOSE_1 && RH_VENT_6_PURGE_2_IND_1) || (K69 && !RH_VENT_6_CLOSE_1) || (K69 && RH_VENT_6_PURGE_2_IND_1);
	K83 = (!RH_VENT_6_PURGE_1_IND_1 && RH_VENT_6_OPEN_1) || (K83 && !RH_VENT_6_PURGE_1_IND_1) || (K83 && RH_VENT_6_OPEN_1);
	K71 = (!RH_VENT_6_OPEN_1 && RH_VENT_6_PURGE_1_IND_1) || (K71 && !RH_VENT_6_OPEN_1) || (K71 && RH_VENT_6_PURGE_1_IND_1);

	bool PRG1_1A = RH_VENT_6_MOTOR_1_PRG_1_A && !RH_VENT_6_PURGE_1_IND_1;
	bool PRG1_1B = RH_VENT_6_MOTOR_1_PRG_1_B && !RH_VENT_6_PURGE_1_IND_1;
	bool PRG2_1A = RH_VENT_6_MOTOR_1_PRG_2_A && !RH_VENT_6_PURGE_2_IND_1;
	bool PRG2_1B = RH_VENT_6_MOTOR_1_PRG_2_B && !RH_VENT_6_PURGE_2_IND_1;

	bool K6 = (RH_VENT_6_MOTOR_1_OPEN_A || (PRG1_1A && K81) || (PRG2_1A && K71)) && !RH_VENT_6_OPEN_1;// OPN A
	bool K16 = (RH_VENT_6_MOTOR_1_OPEN_B || (PRG1_1B && K81) || (PRG2_1B && K71)) && !RH_VENT_6_OPEN_1;// OPN B
	bool K2 = (RH_VENT_6_MOTOR_1_CLOSE_A || (PRG1_1A && K69) || (PRG2_1A && K83)) && !RH_VENT_6_CLOSE_1;// CLS A
	bool K4 = (RH_VENT_6_MOTOR_1_CLOSE_B || (PRG1_1B && K69) || (PRG2_1B && K83)) && !RH_VENT_6_CLOSE_1;// CLS B

	if (K6 && K16)
	{
		if (K2 && K4) RH_VENT_6_MOTOR_1_PWR.SetLine( 0.0f );
		else RH_VENT_6_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K2 && K4) RH_VENT_6_MOTOR_1_PWR.SetLine( -1.0f );
		else RH_VENT_6_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// PAYLOAD BAY DOORS
	// stbd pdu motor 1
	// port fwd bkhd latch motor 1
	// stbd fwd bkhd latch motor 1
	// cl latch 9-12 motor 1

	// FREON RADIATOR
	if (PORT_RAD_LATCH_1_6_LAT_1 && PORT_RAD_LATCH_7_12_LAT_1) PORT_RAD_LATCH_LAT_1.SetLine();
	else PORT_RAD_LATCH_LAT_1.ResetLine();

	bool bPORT_RAD_LATCH_REL_1;
	if (PORT_RAD_LATCH_1_6_REL_1 && PORT_RAD_LATCH_7_12_REL_1)
	{
		PORT_RAD_LATCH_REL_1.SetLine();
		bPORT_RAD_LATCH_REL_1 = true;
	}
	else
	{
		PORT_RAD_LATCH_REL_1.ResetLine();
		bPORT_RAD_LATCH_REL_1 = false;
	}

	if (PORT_RAD_DEPLOYMENT_STO_1 && PORT_RAD_DEPLOYMENT_STO_2) RADIATOR_PORT_STO.SetLine();
	else RADIATOR_PORT_STO.ResetLine();

	// port sys a deploy motor 1
	bool K8 = RADIATOR_CONTROL_SYS_A_STOW && !PORT_RAD_DEPLOYMENT_STO_1;// STW
	bool K12 = RADIATOR_CONTROL_SYS_A_DEPLOY && (bPORT_RAD_LATCH_REL_1 && !PORT_RAD_DEPLOYMENT_DPY_1);// DPY
	bool K22 = RADIATOR_CONTROL_SYS_A_DEPLOY && !PORT_RAD_DEPLOYMENT_DPY_1;// DPY
	bool K10 = RADIATOR_CONTROL_SYS_A_STOW && !PORT_RAD_DEPLOYMENT_STO_1;// STW

	if (K80 && K84)
	{
		if (K12 && K22)
		{
			if (K8 && K10) PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K8 && K10) PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 0.0f );

	// port sys a latch 1-6 motor 1
	bool K18 = RADIATOR_LATCH_CONTROL_SYS_A_LATCH && !PORT_RAD_LATCH_1_6_LAT_1;// LCH
	bool K30 = RADIATOR_LATCH_CONTROL_SYS_A_RELEASE && !PORT_RAD_LATCH_1_6_REL_1;// REL

	if (K80 && K84)
	{
		if (K30)
		{
			if (K18) PORT_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K18) PORT_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 0.0f );

	// port sys a latch 7-12 motor 1
	bool K14 = RADIATOR_LATCH_CONTROL_SYS_A_LATCH && !PORT_RAD_LATCH_7_12_LAT_1;// LCH
	bool K26 = RADIATOR_LATCH_CONTROL_SYS_A_RELEASE && !PORT_RAD_LATCH_7_12_REL_1;// REL

	if (K80 && K84)
	{
		if (K26)
		{
			if (K14) PORT_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K14) PORT_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 0.0f );

	// REMOTE MANIPULATOR
	// port mid retn latch motor 1
	bool K57 = true;// TODO deadface
	bool K55 = K57 && (PORT_MRL_LATCH && !PORT_MID_MRL_LATCH_IND_1);// LCH
	bool K43 = K57 && (PORT_MRL_RELEASE && !PORT_MID_MRL_RELEASE_IND_1);// REL

	if (K80 && K84)
	{
		if (K43)
		{
			if (K55) PORT_MID_MRL_MOTOR_1_PWR.SetLine( 0.0f );
			else PORT_MID_MRL_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K55) PORT_MID_MRL_MOTOR_1_PWR.SetLine( -1.0f );
			else PORT_MID_MRL_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PORT_MID_MRL_MOTOR_1_PWR.SetLine( 0.0f );

	if (K57)
	{
		PORT_MID_MRL_IND_1_PWR.SetLine();
		PORT_MID_RETNN_RFL_1_PWR.SetLine();
	}
	else
	{
		PORT_MID_MRL_IND_1_PWR.ResetLine();
		PORT_MID_RETNN_RFL_1_PWR.ResetLine();
	}

	// stbd fwd retn latch motor 2
	bool K58 = true;// TODO deadface and coil ID
	bool K44 = K58 && (STBD_MRL_RELEASE && !STBD_FWD_MRL_RELEASE_IND_2);// REL
	bool K56 = K58 && (STBD_MRL_LATCH && !STBD_FWD_MRL_LATCH_IND_2);// LCH

	if (K80 && K84)
	{
		if (K44)
		{
			if (K56) STBD_FWD_MRL_MOTOR_2_PWR.SetLine( 0.0f );
			else STBD_FWD_MRL_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K56) STBD_FWD_MRL_MOTOR_2_PWR.SetLine( -1.0f );
			else STBD_FWD_MRL_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else STBD_FWD_MRL_MOTOR_2_PWR.SetLine( 0.0f );

	if (K58)
	{
		STBD_FWD_MRL_IND_2_PWR.SetLine();
		STBD_FWD_RETNN_RFL_2_PWR.SetLine();
	}
	else
	{
		STBD_FWD_MRL_IND_2_PWR.ResetLine();
		STBD_FWD_RETNN_RFL_2_PWR.ResetLine();
	}

	// PAYLOAD RETENTION (no "ret" path back to panel)
	// pl select pos 1 sys 1 latch motors
	// latch 1a
	bool K34 = (PL_RETENTION_1_RELEASE && !PL_1_SEL_1A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K46 = (PL_RETENTION_1_LATCH && !PL_1_SEL_1A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K34)
		{
			if (K46) PL_1_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_1_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K46) PL_1_SEL_1_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 2a
	bool K39 = (PL_RETENTION_2_RELEASE && !PL_1_SEL_2A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K27 = (PL_RETENTION_2_LATCH && !PL_1_SEL_2A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K39)
		{
			if (K27) PL_1_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_2_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K27) PL_1_SEL_2_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 3a
	bool K59 = (PL_RETENTION_3_RELEASE && !PL_1_SEL_3A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K47 = (PL_RETENTION_3_LATCH && !PL_1_SEL_3A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K59)
		{
			if (K47) PL_1_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_3_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K47) PL_1_SEL_3_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 4a
	bool K29 = (PL_RETENTION_4_RELEASE && !PL_1_SEL_4A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K17 = (PL_RETENTION_4_LATCH && !PL_1_SEL_4A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K29)
		{
			if (K17) PL_1_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K17) PL_1_SEL_4_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 5a
	bool K64 = (PL_RETENTION_5_RELEASE && !PL_1_SEL_5A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K52 = (PL_RETENTION_5_LATCH && !PL_1_SEL_5A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K64)
		{
			if (K52) PL_1_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_5_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K52) PL_1_SEL_5_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );

	// pl select pos 2 sys 1 latch motors
	// latch 1a
	bool K60 = (PL_RETENTION_1_RELEASE && !PL_2_SEL_1A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K48 = (PL_RETENTION_1_LATCH && !PL_2_SEL_1A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K60)
		{
			if (K48) PL_2_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_1_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K48) PL_2_SEL_1_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 2a
	bool K13 = (PL_RETENTION_2_RELEASE && !PL_2_SEL_2A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K25 = (PL_RETENTION_2_LATCH && !PL_2_SEL_2A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K13)
		{
			if (K25) PL_2_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_2_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K25) PL_2_SEL_2_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 3a
	bool K49 = (PL_RETENTION_3_RELEASE && !PL_2_SEL_3A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K37 = (PL_RETENTION_3_LATCH && !PL_2_SEL_3A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K49)
		{
			if (K37) PL_2_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_3_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K37) PL_2_SEL_3_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 4a
	bool K63 = (PL_RETENTION_4_RELEASE && !PL_2_SEL_4A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K51 = (PL_RETENTION_4_LATCH && !PL_2_SEL_4A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K63)
		{
			if (K51) PL_2_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K51) PL_2_SEL_4_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 5a
	bool K38 = (PL_RETENTION_5_RELEASE && !PL_2_SEL_5A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K50 = (PL_RETENTION_5_LATCH && !PL_2_SEL_5A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K38)
		{
			if (K50) PL_2_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_5_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K50) PL_2_SEL_5_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );

	// pl select pos 3 sys 1 latch motors
	// latch 1a
	bool K36 = (PL_RETENTION_1_RELEASE && !PL_3_SEL_1A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K24 = (PL_RETENTION_1_LATCH && !PL_3_SEL_1A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K36)
		{
			if (K24) PL_3_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_1_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K24) PL_3_SEL_1_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 2a
	bool K77 = (PL_RETENTION_2_RELEASE && !PL_3_SEL_2A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K65 = (PL_RETENTION_2_LATCH && !PL_3_SEL_2A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K77)
		{
			if (K65) PL_3_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_2_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K65) PL_3_SEL_2_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 3a
	bool K41 = (PL_RETENTION_3_RELEASE && !PL_3_SEL_3A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K53 = (PL_RETENTION_3_LATCH && !PL_3_SEL_3A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K41)
		{
			if (K53) PL_3_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_3_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K53) PL_3_SEL_3_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 4a
	bool K61 = (PL_RETENTION_4_RELEASE && !PL_3_SEL_4A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K73 = (PL_RETENTION_4_LATCH && !PL_3_SEL_4A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K61)
		{
			if (K73) PL_3_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K73) PL_3_SEL_4_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 5a
	bool K74 = (PL_RETENTION_5_RELEASE && !PL_3_SEL_5A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K62 = (PL_RETENTION_5_LATCH && !PL_3_SEL_5A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K74)
		{
			if (K62) PL_3_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_5_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K62) PL_3_SEL_5_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
	return;
}
