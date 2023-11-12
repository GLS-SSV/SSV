/******* SSV File Modification Notice *******
Date         Developer
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
2022/11/01   GLS
2022/11/03   GLS
2022/11/04   GLS
2022/11/05   GLS
2023/07/23   GLS
2023/07/30   GLS
2023/11/12   GLS
********************************************/
#include "MMC3.h"


MMC3::MMC3( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "MMC3" ),
K8(false), K10(false), K14(false), K16(false)
{
}

MMC3::~MMC3()
{
}

void MMC3::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PL_BAY_MECH_PWR_SYS_2.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	//LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 1 );
	LH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 2 );
	LH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	LH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	//LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
	//L_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	//LH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	//LH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	LH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	LH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	LH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	LH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	LH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	LH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	LH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	LH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	//LH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	//LH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	//LH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
	//R_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//R_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//R_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	//RH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	//RH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	RH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	RH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	//RH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	//RH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	//RH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	//RH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	//RH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	//RH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	//RH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	//RH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	//RH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorControl", 16 );
	RADIATOR_LATCH_CONTROL_SYS_A_RELEASE.Connect( pBundle, 0 );
	RADIATOR_LATCH_CONTROL_SYS_A_LATCH.Connect( pBundle, 1 );
	RADIATOR_CONTROL_SYS_B_DEPLOY.Connect( pBundle, 10 );
	RADIATOR_CONTROL_SYS_B_STOW.Connect( pBundle, 11 );
	RADIATOR_STARBOARD_STO.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorLatchMotorInd_1", 16 );
	//PORT_RAD_LATCH_1_6_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_RAD_LATCH_1_6_REL_1.Connect( pBundle, 1 );
	//PORT_RAD_LATCH_1_6_LAT_1.Connect( pBundle, 2 );
	STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_LATCH_1_6_REL_1.Connect( pBundle, 4 );
	STARBOARD_RAD_LATCH_1_6_LAT_1.Connect( pBundle, 5 );
	//PORT_RAD_LATCH_7_12_MOTOR_1_PWR.Connect( pBundle, 6 );
	//PORT_RAD_LATCH_7_12_REL_1.Connect( pBundle, 7 );
	//PORT_RAD_LATCH_7_12_LAT_1.Connect( pBundle, 8 );
	STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.Connect( pBundle, 9 );
	STARBOARD_RAD_LATCH_7_12_REL_1.Connect( pBundle, 10 );
	STARBOARD_RAD_LATCH_7_12_LAT_1.Connect( pBundle, 11 );
	//PORT_RAD_LATCH_REL_1.Connect( pBundle, 12 );
	//PORT_RAD_LATCH_LAT_1.Connect( pBundle, 13 );
	STARBOARD_RAD_LATCH_REL_1.Connect( pBundle, 14 );
	STARBOARD_RAD_LATCH_LAT_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "RadiatorMotorInd", 16 );
	//PORT_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 0 );
	//PORT_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 1 );
	//PORT_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 2 );
	STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.Connect( pBundle, 3 );
	STARBOARD_RAD_DEPLOYMENT_DPY_1.Connect( pBundle, 4 );
	STARBOARD_RAD_DEPLOYMENT_STO_1.Connect( pBundle, 5 );
	//PORT_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 6 );
	//PORT_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 7 );
	//PORT_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 8 );
	//STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR.Connect( pBundle, 9 );
	//STARBOARD_RAD_DEPLOYMENT_DPY_2.Connect( pBundle, 10 );
	STARBOARD_RAD_DEPLOYMENT_STO_2.Connect( pBundle, 11 );

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
	//LOGIC_POWER_SYS_1A.Connect( pBundle, 10 );
	//LOGIC_POWER_SYS_2A.Connect( pBundle, 11 );
	//LOGIC_POWER_SYS_3A.Connect( pBundle, 12 );
	LOGIC_POWER_SYS_1B.Connect( pBundle, 13 );
	LOGIC_POWER_SYS_2B.Connect( pBundle, 14 );
	LOGIC_POWER_SYS_3B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 16 );
	//PL_1_SEL_1A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_1_SEL_1_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_1A_1.Connect( pBundle, 3 );
	PL_1_SEL_1B_LAT.Connect( pBundle, 4 );
	PL_1_SEL_1B_REL.Connect( pBundle, 5 );
	PL_1_SEL_1_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_1B_1.Connect( pBundle, 7 );
	//PL_1_SEL_1A_LAT_TB.Connect( pBundle, 8 );
	//PL_1_SEL_1A_REL_TB.Connect( pBundle, 9 );
	//PL_1_RDY_1A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 16 );
	//PL_1_SEL_2A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_1_SEL_2_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_1A_2.Connect( pBundle, 3 );
	PL_1_SEL_2B_LAT.Connect( pBundle, 4 );
	PL_1_SEL_2B_REL.Connect( pBundle, 5 );
	PL_1_SEL_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_1B_2.Connect( pBundle, 7 );
	//PL_1_SEL_2A_LAT_TB.Connect( pBundle, 8 );
	//PL_1_SEL_2A_REL_TB.Connect( pBundle, 9 );
	//PL_1_RDY_2A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 16 );
	//PL_1_SEL_3A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_1_SEL_3_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_1A_3.Connect( pBundle, 3 );
	PL_1_SEL_3B_LAT.Connect( pBundle, 4 );
	PL_1_SEL_3B_REL.Connect( pBundle, 5 );
	PL_1_SEL_3_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_1B_3.Connect( pBundle, 7 );
	//PL_1_SEL_3A_LAT_TB.Connect( pBundle, 8 );
	//PL_1_SEL_3A_REL_TB.Connect( pBundle, 9 );
	//PL_1_RDY_3A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 16 );
	//PL_1_SEL_4A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_1_SEL_4_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_1A_4.Connect( pBundle, 3 );
	PL_1_SEL_4B_LAT.Connect( pBundle, 4 );
	PL_1_SEL_4B_REL.Connect( pBundle, 5 );
	PL_1_SEL_4_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_1B_4.Connect( pBundle, 7 );
	//PL_1_SEL_4A_LAT_TB.Connect( pBundle, 8 );
	//PL_1_SEL_4A_REL_TB.Connect( pBundle, 9 );
	//PL_1_RDY_4A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 16 );
	//PL_1_SEL_5A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_1_SEL_5_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_1A_5.Connect( pBundle, 3 );
	PL_1_SEL_5B_LAT.Connect( pBundle, 4 );
	PL_1_SEL_5B_REL.Connect( pBundle, 5 );
	PL_1_SEL_5_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_1B_5.Connect( pBundle, 7 );
	//PL_1_SEL_5A_LAT_TB.Connect( pBundle, 8 );
	//PL_1_SEL_5A_REL_TB.Connect( pBundle, 9 );
	//PL_1_RDY_5A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 16 );
	//PL_2_SEL_1A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_2_SEL_1_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_2A_1.Connect( pBundle, 3 );
	PL_2_SEL_1B_LAT.Connect( pBundle, 4 );
	PL_2_SEL_1B_REL.Connect( pBundle, 5 );
	PL_2_SEL_1_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_2B_1.Connect( pBundle, 7 );
	//PL_2_SEL_1A_LAT_TB.Connect( pBundle, 8 );
	//PL_2_SEL_1A_REL_TB.Connect( pBundle, 9 );
	//PL_2_RDY_1A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 16 );
	//PL_2_SEL_2A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_2_SEL_2_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_2A_2.Connect( pBundle, 3 );
	PL_2_SEL_2B_LAT.Connect( pBundle, 4 );
	PL_2_SEL_2B_REL.Connect( pBundle, 5 );
	PL_2_SEL_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_2B_2.Connect( pBundle, 7 );
	//PL_2_SEL_2A_LAT_TB.Connect( pBundle, 8 );
	//PL_2_SEL_2A_REL_TB.Connect( pBundle, 9 );
	//PL_2_RDY_2A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 16 );
	//PL_2_SEL_3A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_2_SEL_3_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_2A_3.Connect( pBundle, 3 );
	PL_2_SEL_3B_LAT.Connect( pBundle, 4 );
	PL_2_SEL_3B_REL.Connect( pBundle, 5 );
	PL_2_SEL_3_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_2B_3.Connect( pBundle, 7 );
	//PL_2_SEL_3A_LAT_TB.Connect( pBundle, 8 );
	//PL_2_SEL_3A_REL_TB.Connect( pBundle, 9 );
	//PL_2_RDY_3A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 16 );
	//PL_2_SEL_4A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_2_SEL_4_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_2A_4.Connect( pBundle, 3 );
	PL_2_SEL_4B_LAT.Connect( pBundle, 4 );
	PL_2_SEL_4B_REL.Connect( pBundle, 5 );
	PL_2_SEL_4_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_2B_4.Connect( pBundle, 7 );
	//PL_2_SEL_4A_LAT_TB.Connect( pBundle, 8 );
	//PL_2_SEL_4A_REL_TB.Connect( pBundle, 9 );
	//PL_2_RDY_4A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 16 );
	//PL_2_SEL_5A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_2_SEL_5_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_2A_5.Connect( pBundle, 3 );
	PL_2_SEL_5B_LAT.Connect( pBundle, 4 );
	PL_2_SEL_5B_REL.Connect( pBundle, 5 );
	PL_2_SEL_5_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_2B_5.Connect( pBundle, 7 );
	//PL_2_SEL_5A_LAT_TB.Connect( pBundle, 8 );
	//PL_2_SEL_5A_REL_TB.Connect( pBundle, 9 );
	//PL_2_RDY_5A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 16 );
	//PL_3_SEL_1A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_3_SEL_1_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_3A_1.Connect( pBundle, 3 );
	PL_3_SEL_1B_LAT.Connect( pBundle, 4 );
	PL_3_SEL_1B_REL.Connect( pBundle, 5 );
	PL_3_SEL_1_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_3B_1.Connect( pBundle, 7 );
	//PL_3_SEL_1A_LAT_TB.Connect( pBundle, 8 );
	//PL_3_SEL_1A_REL_TB.Connect( pBundle, 9 );
	//PL_3_RDY_1A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 16 );
	//PL_3_SEL_2A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_3_SEL_2_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_3A_2.Connect( pBundle, 3 );
	PL_3_SEL_2B_LAT.Connect( pBundle, 4 );
	PL_3_SEL_2B_REL.Connect( pBundle, 5 );
	PL_3_SEL_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_3B_2.Connect( pBundle, 7 );
	//PL_3_SEL_2A_LAT_TB.Connect( pBundle, 8 );
	//PL_3_SEL_2A_REL_TB.Connect( pBundle, 9 );
	//PL_3_RDY_2A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 16 );
	//PL_3_SEL_3A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_3_SEL_3_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_3A_3.Connect( pBundle, 3 );
	PL_3_SEL_3B_LAT.Connect( pBundle, 4 );
	PL_3_SEL_3B_REL.Connect( pBundle, 5 );
	PL_3_SEL_3_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_3B_3.Connect( pBundle, 7 );
	//PL_3_SEL_3A_LAT_TB.Connect( pBundle, 8 );
	//PL_3_SEL_3A_REL_TB.Connect( pBundle, 9 );
	//PL_3_RDY_3A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 16 );
	//PL_3_SEL_4A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_3_SEL_4_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_3A_4.Connect( pBundle, 3 );
	PL_3_SEL_4B_LAT.Connect( pBundle, 4 );
	PL_3_SEL_4B_REL.Connect( pBundle, 5 );
	PL_3_SEL_4_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_3B_4.Connect( pBundle, 7 );
	//PL_3_SEL_4A_LAT_TB.Connect( pBundle, 8 );
	//PL_3_SEL_4A_REL_TB.Connect( pBundle, 9 );
	//PL_3_RDY_4A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 16 );
	//PL_3_SEL_5A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_3_SEL_5_MOTOR_1_PWR.Connect( pBundle, 2 );
	//IND_3A_5.Connect( pBundle, 3 );
	PL_3_SEL_5B_LAT.Connect( pBundle, 4 );
	PL_3_SEL_5B_REL.Connect( pBundle, 5 );
	PL_3_SEL_5_MOTOR_2_PWR.Connect( pBundle, 6 );
	//IND_3B_5.Connect( pBundle, 7 );
	//PL_3_SEL_5A_LAT_TB.Connect( pBundle, 8 );
	//PL_3_SEL_5A_REL_TB.Connect( pBundle, 9 );
	//PL_3_RDY_5A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "MPM_D&C", 16 );
	//PORT_MPM_STOW.Connect( pBundle, 0 );
	//PORT_MPM_DEPLOY.Connect( pBundle, 1 );
	PORT_MPM_SYSTEM_1_STOW.Connect( pBundle, 2 );
	PORT_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 3 );
	//PORT_MPM_SYSTEM_2_STOW.Connect( pBundle, 4 );
	//PORT_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 5 );
	//STBD_MPM_STOW.Connect( pBundle, 6 );
	//STBD_MPM_DEPLOY.Connect( pBundle, 7 );
	//STBD_MPM_SYSTEM_1_STOW.Connect( pBundle, 8 );
	//STBD_MPM_SYSTEM_1_DEPLOY.Connect( pBundle, 9 );
	//STBD_MPM_SYSTEM_2_STOW.Connect( pBundle, 10 );
	//STBD_MPM_SYSTEM_2_DEPLOY.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_CTRL_1", 16 );
	//PORT_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	PORT_SHLD_MECH_STOW_IND_1_TB.Connect( pBundle, 1 );
	PORT_FWD_MECH_STOW_IND_1_TB.Connect( pBundle, 2 );
	PORT_MID_MECH_STOW_IND_1_TB.Connect( pBundle, 3 );
	PORT_AFT_MECH_STOW_IND_1_TB.Connect( pBundle, 4 );
	//PORT_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 5 );
	PORT_SHLD_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 6 );
	PORT_FWD_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 7 );
	PORT_MID_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 8 );
	PORT_AFT_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 9 );
	//PORT_MPM_MOTOR_1_PWR.Connect( pBundle, 10 );
	//PORT_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 11 );
	PORT_MPM_FWD_1_IND_PWR.Connect( pBundle, 12 );
	//PORT_MPM_MID_1_IND_PWR.Connect( pBundle, 13 );
	PORT_MPM_AFT_1_IND_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "STBD_MPM_CTRL_2", 16 );
	//STBD_SHLD_MECH_STOW_IND_2.Connect( pBundle, 0 );
	//STBD_SHLD_MECH_STOW_IND_2_TB.Connect( pBundle, 1 );
	//STBD_FWD_MECH_STOW_IND_2_TB.Connect( pBundle, 2 );
	//STBD_MID_MECH_STOW_IND_2_TB.Connect( pBundle, 3 );
	//STBD_AFT_MECH_STOW_IND_2_TB.Connect( pBundle, 4 );
	//STBD_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 5 );
	//STBD_SHLD_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 6 );
	//STBD_FWD_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 7 );
	//STBD_MID_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 8 );
	//STBD_AFT_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 9 );
	//STBD_MPM_MOTOR_2_PWR.Connect( pBundle, 10 );
	STBD_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 11 );
	//STBD_MPM_FWD_2_IND_PWR.Connect( pBundle, 12 );
	//STBD_MPM_MID_2_IND_PWR.Connect( pBundle, 13 );
	STBD_MPM_AFT_2_IND_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "MRL_D&C", 16 );
	PORT_MRL_LATCH.Connect( pBundle, 0 );
	PORT_MRL_RELEASE.Connect( pBundle, 1 );
	//PORT_MRL_LATCHED.Connect( pBundle, 2 );
	//PORT_MRL_RELEASED.Connect( pBundle, 3 );
	STBD_MRL_LATCH.Connect( pBundle, 4 );
	STBD_MRL_RELEASE.Connect( pBundle, 5 );
	//STBD_MRL_LATCHED.Connect( pBundle, 6 );
	//STBD_MRL_RELEASED.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "PORT_AFT_MRL_CTRL", 16 );
	//PORT_AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	//PORT_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	//PORT_AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 2 );
	//PORT_AFT_MRL_IND_1_PWR.Connect( pBundle, 3 );
	//PORT_AFT_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_AFT_MRL_LATCH_IND_1_TB.Connect( pBundle, 5 );
	//PORT_AFT_MRL_RELEASE_IND_1_TB.Connect( pBundle, 6 );
	//PORT_AFT_RETNN_RFL_1_TB.Connect( pBundle, 7 );
	PORT_AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	PORT_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	PORT_AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 10 );
	PORT_AFT_MRL_IND_2_PWR.Connect( pBundle, 11 );
	PORT_AFT_RETNN_RFL_2_PWR.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "STBD_AFT_MRL_CTRL", 16 );
	STBD_AFT_MRL_LATCH_IND_1.Connect( pBundle, 0 );
	STBD_AFT_MRL_RELEASE_IND_1.Connect( pBundle, 1 );
	STBD_AFT_MRL_MOTOR_1_PWR.Connect( pBundle, 2 );
	STBD_AFT_MRL_IND_1_PWR.Connect( pBundle, 3 );
	STBD_AFT_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//STBD_AFT_MRL_LATCH_IND_1_TB.Connect( pBundle, 5 );
	//STBD_AFT_MRL_RELEASE_IND_1_TB.Connect( pBundle, 6 );
	//STBD_AFT_RETNN_RFL_1_TB.Connect( pBundle, 7 );
	//STBD_AFT_MRL_LATCH_IND_2.Connect( pBundle, 8 );
	//STBD_AFT_MRL_RELEASE_IND_2.Connect( pBundle, 9 );
	//STBD_AFT_MRL_MOTOR_2_PWR.Connect( pBundle, 10 );
	//STBD_AFT_MRL_IND_2_PWR.Connect( pBundle, 11 );
	//STBD_AFT_RETNN_RFL_2_PWR.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "PayloadBayDoorControl", 16 );
	PBD_ENABLE_SYS2.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "MMC_POWER", 16 );
	MNA_MMC3.Connect( pBundle, 4 );
	MNB_MMC3.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "PLBD_CL_1", 16 );
	CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.Connect( pBundle, 0 );
	LAT_1_4_LAT_1.Connect( pBundle, 1 );
	LAT_1_4_REL_1.Connect( pBundle, 2 );
	CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.Connect( pBundle, 3 );
	LAT_5_8_LAT_1.Connect( pBundle, 4 );
	LAT_5_8_REL_1.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_1", 16 );
	BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.Connect( pBundle, 9 );
	PORT_AFT_BLKHD_LAT_1.Connect( pBundle, 10 );
	PORT_AFT_BLKHD_REL_1.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH0", 16 );
	RH_VENTS_4_7_MOTOR_2_CLOSE_B.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM2_CH2", 16 );
	RH_VENTS_4_7_MOTOR_2_OPEN_B.Connect( pBundle, 7 );
	LH_VENT_6_MOTOR_1_CLOSE_B.Connect( pBundle, 10 );
	LH_VENT_6_MOTOR_1_OPEN_B.Connect( pBundle, 11 );
	LH_VENT_6_MOTOR_1_PRG_1_B.Connect( pBundle, 12 );
	LH_VENT_6_MOTOR_1_PRG_2_B.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF1_IOM10_CH2", 16 );
	RH_VENTS_4_7_MOTOR_2_CLOSE_A.Connect( pBundle, 6 );
	RH_VENTS_4_7_MOTOR_2_OPEN_A.Connect( pBundle, 7 );
	LH_VENT_6_MOTOR_1_CLOSE_A.Connect( pBundle, 10 );
	LH_VENT_6_MOTOR_1_OPEN_A.Connect( pBundle, 11 );
	LH_VENT_6_MOTOR_1_PRG_1_A.Connect( pBundle, 12 );
	LH_VENT_6_MOTOR_1_PRG_2_A.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH1", 16 );
	LH_VENTS_4_7_MOTOR_1_CLOSE_B.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM2_CH2", 16 );
	LH_VENTS_4_7_MOTOR_1_OPEN_B.Connect( pBundle, 9 );
	LH_VENT_5_MOTOR_1_CLOSE_B.Connect( pBundle, 14 );
	LH_VENT_5_MOTOR_1_OPEN_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM10_CH2", 16 );
	LH_VENTS_4_7_MOTOR_1_CLOSE_A.Connect( pBundle, 8 );
	LH_VENTS_4_7_MOTOR_1_OPEN_A.Connect( pBundle, 9 );
	LH_VENT_5_MOTOR_1_CLOSE_A.Connect( pBundle, 14 );
	LH_VENT_5_MOTOR_1_OPEN_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "MDM_PF1_IOM2_CH0", 16 );
	PBD_OPERATION_ENABLE_CMD_4A.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_PF1_IOM7_CH0", 16 );
	LAT_1_4_REL_CMD_1.Connect( pBundle, 2 );
	LAT_1_4_LAT_CMD_1.Connect( pBundle, 3 );
	LAT_5_8_REL_CMD_1.Connect( pBundle, 4 );
	LAT_5_8_LAT_CMD_1.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_PF1_IOM14_CH0", 16 );
	PORT_AFT_BLKHD_REL_CMD_1.Connect( pBundle, 4 );
	PORT_AFT_BLKHD_LAT_CMD_1.Connect( pBundle, 5 );
	PBD_OPERATION_ENABLE_CMD_4B.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH0", 16 );
	OPER_STATUS_1.Connect( pBundle, 3 );
	OPER_STATUS_2.Connect( pBundle, 4 );

	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH0", 16 );
	OPER_STATUS_3.Connect( pBundle, 1 );
	OPER_STATUS_4.Connect( pBundle, 2 );

	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH0", 16 );
	OPER_STATUS_5.Connect( pBundle, 3 );
	OPER_STATUS_6.Connect( pBundle, 4 );

	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM6_CH0", 16 );
	OPER_STATUS_7.Connect( pBundle, 1 );
	OPER_STATUS_8.Connect( pBundle, 2 );
	return;
}

void MMC3::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNA_RELAY_LOGIC_POWER = true;
	bool MNB_RELAY_LOGIC_POWER = true;

	if (MNA_RELAY_LOGIC_POWER) MNA_MMC3.SetLine();
	else MNA_MMC3.ResetLine();
	if (MNB_RELAY_LOGIC_POWER) MNB_MMC3.SetLine();
	else MNB_MMC3.ResetLine();

	// MPM indication power and position status
	PORT_MPM_FWD_1_IND_PWR.SetLine();
	PORT_MPM_AFT_1_IND_PWR.SetLine();
	STBD_MPM_SHOULDER_2_IND_PWR.SetLine();
	STBD_MPM_AFT_2_IND_PWR.SetLine();

	if (PORT_SHLD_MECH_STOW_IND_1_TB && PORT_FWD_MECH_STOW_IND_1_TB && PORT_MID_MECH_STOW_IND_1_TB && PORT_AFT_MECH_STOW_IND_1_TB) PORT_MPM_SYSTEM_1_STOW.SetLine();
	else PORT_MPM_SYSTEM_1_STOW.ResetLine();

	if (PORT_SHLD_MECH_DEPLOY_IND_1_TB && PORT_FWD_MECH_DEPLOY_IND_1_TB && PORT_MID_MECH_DEPLOY_IND_1_TB && PORT_AFT_MECH_DEPLOY_IND_1_TB) PORT_MPM_SYSTEM_1_DEPLOY.SetLine();
	else PORT_MPM_SYSTEM_1_DEPLOY.ResetLine();

	// power enables
	bool K77 = PL_BAY_MECH_PWR_SYS_2;
	bool K65 = PL_BAY_MECH_PWR_SYS_2;
	bool K7 = PL_BAY_MECH_PWR_SYS_2;
	bool K9 = PL_BAY_MECH_PWR_SYS_2;
	bool K22 = PBD_OPERATION_ENABLE_CMD_4A.IsSet( 26.0f ) && PBD_ENABLE_SYS2;
	bool K20 = PBD_OPERATION_ENABLE_CMD_4B.IsSet( 26.0f ) && PBD_ENABLE_SYS2;

	// VENT DOORS
	// right no 4/7 motor 2
	bool K49 = RH_VENTS_4_7_MOTOR_2_CLOSE_A.IsSet( 26.0f ) && !RH_VENTS_4_AND_7_CLOSE_2.IsSet( 26.0f );// CLS A
	bool K53 = RH_VENTS_4_7_MOTOR_2_OPEN_A.IsSet( 26.0f ) && !RH_VENTS_4_AND_7_OPEN_2.IsSet( 26.0f );// OPN A
	bool K51 = RH_VENTS_4_7_MOTOR_2_OPEN_B.IsSet( 26.0f ) && !RH_VENTS_4_AND_7_OPEN_2.IsSet( 26.0f );// OPN B
	bool K63 = RH_VENTS_4_7_MOTOR_2_CLOSE_B.IsSet( 26.0f ) && !RH_VENTS_4_AND_7_CLOSE_2.IsSet( 26.0f );// CLS B

	if (K53 && K51)
	{
		if (K49 && K63) RH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( 0.0f );
		else RH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K49 && K63) RH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( -1.0f );
		else RH_VENTS_4_AND_7_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// VENT DOORS
	// left no 4/7 motor 1
	bool K4 = LH_VENTS_4_7_MOTOR_1_CLOSE_B.IsSet( 26.0f ) && !LH_VENTS_4_AND_7_CLOSE_1.IsSet( 26.0f );// CLS B
	bool K18 = LH_VENTS_4_7_MOTOR_1_CLOSE_A.IsSet( 26.0f ) && !LH_VENTS_4_AND_7_CLOSE_1.IsSet( 26.0f );// CLS A
	bool K2 = LH_VENTS_4_7_MOTOR_1_OPEN_B.IsSet( 26.0f ) && !LH_VENTS_4_AND_7_OPEN_1.IsSet( 26.0f );// OPN B
	bool K6 = LH_VENTS_4_7_MOTOR_1_OPEN_A.IsSet( 26.0f ) && !LH_VENTS_4_AND_7_OPEN_1.IsSet( 26.0f );// OPN A

	if (K6 && K2)
	{
		if (K18 && K4) LH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( 0.0f );
		else LH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K18 && K4) LH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( -1.0f );
		else LH_VENTS_4_AND_7_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// left no 5 motor 1
	bool K40 = LH_VENT_5_MOTOR_1_OPEN_B.IsSet( 26.0f ) && !LH_VENT_5_OPEN_1.IsSet( 26.0f );// OPN B
	bool K30 = LH_VENT_5_MOTOR_1_OPEN_A.IsSet( 26.0f ) && !LH_VENT_5_OPEN_1.IsSet( 26.0f );// OPN A
	bool K26 = LH_VENT_5_MOTOR_1_CLOSE_B.IsSet( 26.0f ) && !LH_VENT_5_CLOSE_1.IsSet( 26.0f );// CLS B
	bool K28 = LH_VENT_5_MOTOR_1_CLOSE_A.IsSet( 26.0f ) && !LH_VENT_5_CLOSE_1.IsSet( 26.0f );// CLS A

	if (K40 && K30)
	{
		if (K26 && K28) LH_VENT_5_MOTOR_1_PWR.SetLine( 0.0f );
		else LH_VENT_5_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K26 && K28) LH_VENT_5_MOTOR_1_PWR.SetLine( -1.0f );
		else LH_VENT_5_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// left no 6 motor 1
	K8 = (!LH_VENT_6_PURGE_2_IND_1.IsSet( 26.0f ) && LH_VENT_6_CLOSE_1.IsSet( 26.0f )) || (K8 && !LH_VENT_6_PURGE_2_IND_1.IsSet( 26.0f )) || (K8 && LH_VENT_6_CLOSE_1.IsSet( 26.0f ));
	K10 = (!LH_VENT_6_CLOSE_1.IsSet( 26.0f ) && LH_VENT_6_PURGE_2_IND_1.IsSet( 26.0f )) || (K10 && !LH_VENT_6_CLOSE_1.IsSet( 26.0f )) || (K10 && LH_VENT_6_PURGE_2_IND_1.IsSet( 26.0f ));
	K14 = (!LH_VENT_6_PURGE_1_IND_1.IsSet( 26.0f ) && LH_VENT_6_OPEN_1.IsSet( 26.0f )) || (K14 && !LH_VENT_6_PURGE_1_IND_1.IsSet( 26.0f )) || (K14 && LH_VENT_6_OPEN_1.IsSet( 26.0f ));
	K16 = (!LH_VENT_6_OPEN_1.IsSet( 26.0f ) && LH_VENT_6_PURGE_1_IND_1.IsSet( 26.0f )) || (K16 && !LH_VENT_6_OPEN_1.IsSet( 26.0f )) || (K16 && LH_VENT_6_PURGE_1_IND_1.IsSet( 26.0f ));

	bool PRG1_1A = LH_VENT_6_MOTOR_1_PRG_1_A.IsSet( 26.0f ) && !LH_VENT_6_PURGE_1_IND_1.IsSet( 26.0f );
	bool PRG1_1B = LH_VENT_6_MOTOR_1_PRG_1_B.IsSet( 26.0f ) && !LH_VENT_6_PURGE_1_IND_1.IsSet( 26.0f );
	bool PRG2_1A = LH_VENT_6_MOTOR_1_PRG_2_A.IsSet( 26.0f ) && !LH_VENT_6_PURGE_2_IND_1.IsSet( 26.0f );
	bool PRG2_1B = LH_VENT_6_MOTOR_1_PRG_2_B.IsSet( 26.0f ) && !LH_VENT_6_PURGE_2_IND_1.IsSet( 26.0f );

	bool K52 = (LH_VENT_6_MOTOR_1_CLOSE_B.IsSet( 26.0f ) || (PRG1_1B && K10) || (PRG2_1B && K14)) && !LH_VENT_6_CLOSE_1.IsSet( 26.0f );// CLS B
	bool K66 = (LH_VENT_6_MOTOR_1_CLOSE_A.IsSet( 26.0f ) || (PRG1_1A && K10) || (PRG2_1A && K14)) && !LH_VENT_6_CLOSE_1.IsSet( 26.0f );// CLS A
	bool K54 = (LH_VENT_6_MOTOR_1_OPEN_B.IsSet( 26.0f ) || (PRG1_1B && K8) || (PRG2_1B && K16)) && !LH_VENT_6_OPEN_1.IsSet( 26.0f );// OPN B
	bool K42 = (LH_VENT_6_MOTOR_1_OPEN_A.IsSet( 26.0f ) || (PRG1_1A && K8) || (PRG2_1A && K16)) && !LH_VENT_6_OPEN_1.IsSet( 26.0f );// OPN A

	if (K54 && K42)
	{
		if (K52 && K66) LH_VENT_6_MOTOR_1_PWR.SetLine( 0.0f );
		else LH_VENT_6_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K52 && K66) LH_VENT_6_MOTOR_1_PWR.SetLine( -1.0f );
		else LH_VENT_6_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// PAYLOAD BAY DOORS
	// port aft bkhd latch motor 1
	bool K64 = MNA_RELAY_LOGIC_POWER && (PORT_AFT_BLKHD_REL_CMD_1.IsSet( 26.0f ) && !PORT_AFT_BLKHD_REL_1);// REL
	bool K62 = MNA_RELAY_LOGIC_POWER && (PORT_AFT_BLKHD_LAT_CMD_1.IsSet( 26.0f ) && !PORT_AFT_BLKHD_LAT_1);// LCH

	if (K20 && K22)
	{
		if (K64)
		{
			if (K62) BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.SetLine( 0.0f );
			else BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K62) BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.SetLine( -1.0f );
			else BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR.SetLine( 0.0f );
	// cl latch 1-4 motor 1
	bool K3 = MNA_RELAY_LOGIC_POWER && (LAT_1_4_REL_CMD_1.IsSet( 26.0f ) && !LAT_1_4_REL_1);// REL
	bool K1 = MNA_RELAY_LOGIC_POWER && (LAT_1_4_LAT_CMD_1.IsSet( 26.0f ) && !LAT_1_4_LAT_1);// LCH

	if (K20 && K22)
	{
		if (K3)
		{
			if (K1) CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.SetLine( 0.0f );
			else CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K1) CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.SetLine( -1.0f );
			else CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR.SetLine( 0.0f );
	// cl latch 5-8 motor 1
	bool K15 = MNA_RELAY_LOGIC_POWER && (LAT_5_8_REL_CMD_1.IsSet( 26.0f ) && !LAT_5_8_REL_1);// REL
	bool K13 = MNA_RELAY_LOGIC_POWER && (LAT_5_8_LAT_CMD_1.IsSet( 26.0f ) && !LAT_5_8_LAT_1);// LCH

	if (K20 && K22)
	{
		if (K15)
		{
			if (K13) CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.SetLine( 0.0f );
			else CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K13) CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.SetLine( -1.0f );
			else CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR.SetLine( 0.0f );

	// FREON RADIATOR
	if (STARBOARD_RAD_LATCH_1_6_LAT_1 && STARBOARD_RAD_LATCH_7_12_LAT_1) STARBOARD_RAD_LATCH_LAT_1.SetLine();
	else STARBOARD_RAD_LATCH_LAT_1.ResetLine();

	bool bSTARBOARD_RAD_LATCH_REL_1;
	if (STARBOARD_RAD_LATCH_1_6_REL_1 && STARBOARD_RAD_LATCH_7_12_REL_1)
	{
		STARBOARD_RAD_LATCH_REL_1.SetLine();
		bSTARBOARD_RAD_LATCH_REL_1 = true;
	}
	else
	{
		STARBOARD_RAD_LATCH_REL_1.ResetLine();
		bSTARBOARD_RAD_LATCH_REL_1 = false;
	}

	if (STARBOARD_RAD_DEPLOYMENT_STO_1 && STARBOARD_RAD_DEPLOYMENT_STO_2) RADIATOR_STARBOARD_STO.SetLine();
	else RADIATOR_STARBOARD_STO.ResetLine();

	// stbd sys b deploy motor 1
	bool K39 = RADIATOR_CONTROL_SYS_B_STOW && !STARBOARD_RAD_DEPLOYMENT_STO_1;// STW
	bool K41 = RADIATOR_CONTROL_SYS_B_DEPLOY && !STARBOARD_RAD_DEPLOYMENT_DPY_1;// DPY
	bool K27 = RADIATOR_CONTROL_SYS_B_STOW && !STARBOARD_RAD_DEPLOYMENT_STO_1;// STW
	bool K29 = RADIATOR_CONTROL_SYS_B_DEPLOY && (bSTARBOARD_RAD_LATCH_REL_1 && !STARBOARD_RAD_DEPLOYMENT_DPY_1);// DPY

	if (K7 && K9)
	{
		if (K41 && K29)
		{
			if (K39 && K27) STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 0.0f );
			else STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K39 && K27) STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( -1.0f );
			else STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR.SetLine( 0.0f );

	// stbd sys a latch 1-6 motor 1
	bool K38 = RADIATOR_LATCH_CONTROL_SYS_A_LATCH && !STARBOARD_RAD_LATCH_1_6_LAT_1;// LCH
	bool K50 = RADIATOR_LATCH_CONTROL_SYS_A_RELEASE && !STARBOARD_RAD_LATCH_1_6_REL_1;// REL

	if (K7 && K9)
	{
		if (K50)
		{
			if (K38) STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 0.0f );
			else STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K38) STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( -1.0f );
			else STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR.SetLine( 0.0f );

	// stbd sys a latch 7-12 motor 1
	bool K25 = RADIATOR_LATCH_CONTROL_SYS_A_RELEASE && !STARBOARD_RAD_LATCH_7_12_REL_1;// REL
	bool K37 = RADIATOR_LATCH_CONTROL_SYS_A_LATCH && !STARBOARD_RAD_LATCH_7_12_LAT_1;// LCH

	if (K7 && K9)
	{
		if (K25)
		{
			if (K37) STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 0.0f );
			else STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K37) STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( -1.0f );
			else STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR.SetLine( 0.0f );

	// REMOTE MANIPULATOR
	// port aft retn latch motor 2
	bool K23 = true;// TODO deadface
	bool K12 = K23 && (PORT_MRL_LATCH && !PORT_AFT_MRL_LATCH_IND_2);// LCH
	bool K24 = K23 && (PORT_MRL_RELEASE && !PORT_AFT_MRL_RELEASE_IND_2);// REL

	if (K7 && K9)
	{
		if (K24)
		{
			if (K12) PORT_AFT_MRL_MOTOR_2_PWR.SetLine( 0.0f );
			else PORT_AFT_MRL_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K12) PORT_AFT_MRL_MOTOR_2_PWR.SetLine( -1.0f );
			else PORT_AFT_MRL_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PORT_AFT_MRL_MOTOR_2_PWR.SetLine( 0.0f );

	if (K23)
	{
		PORT_AFT_MRL_IND_2_PWR.SetLine();
		PORT_AFT_RETNN_RFL_2_PWR.SetLine();
	}
	else
	{
		PORT_AFT_MRL_IND_2_PWR.ResetLine();
		PORT_AFT_RETNN_RFL_2_PWR.ResetLine();
	}

	// stbd aft retn latch motor 1
	bool K99 = true;// TODO deadface and coil ID
	bool K78 = K99 && (STBD_MRL_LATCH && !STBD_AFT_MRL_LATCH_IND_1);// LCH
	bool K76 = K99 && (STBD_MRL_RELEASE && !STBD_AFT_MRL_RELEASE_IND_1);// REL

	if (K7 && K9)
	{
		if (K76)
		{
			if (K78) STBD_AFT_MRL_MOTOR_1_PWR.SetLine( 0.0f );
			else STBD_AFT_MRL_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K78) STBD_AFT_MRL_MOTOR_1_PWR.SetLine( -1.0f );
			else STBD_AFT_MRL_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else STBD_AFT_MRL_MOTOR_1_PWR.SetLine( 0.0f );

	if (K99)
	{
		STBD_AFT_MRL_IND_1_PWR.SetLine();
		STBD_AFT_RETNN_RFL_1_PWR.SetLine();
	}
	else
	{
		STBD_AFT_MRL_IND_1_PWR.ResetLine();
		STBD_AFT_RETNN_RFL_1_PWR.ResetLine();
	}

	// PAYLOAD RETENTION (no "ret" path back to panel)
	// pl select pos 1 sys 2 latch motors
	// latch 1b
	bool K17 = (PL_RETENTION_1_RELEASE && !PL_1_SEL_1B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K5 = (PL_RETENTION_1_LATCH && !PL_1_SEL_1B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K17)
		{
			if (K5) PL_1_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_1_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K5) PL_1_SEL_1_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 2b
	bool K34 = (PL_RETENTION_2_RELEASE && !PL_1_SEL_2B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K32 = (PL_RETENTION_2_LATCH && !PL_1_SEL_2B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K34)
		{
			if (K32) PL_1_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_2_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K32) PL_1_SEL_2_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 3b
	bool K70 = (PL_RETENTION_3_RELEASE && !PL_1_SEL_3B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K68 = (PL_RETENTION_3_LATCH && !PL_1_SEL_3B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K70)
		{
			if (K68) PL_1_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_3_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K68) PL_1_SEL_3_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 4b
	bool K81 = (PL_RETENTION_4_RELEASE && !PL_1_SEL_4B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K79 = (PL_RETENTION_4_LATCH && !PL_1_SEL_4B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K81)
		{
			if (K79) PL_1_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K79) PL_1_SEL_4_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 5b
	bool K47 = (PL_RETENTION_5_RELEASE && !PL_1_SEL_5B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K35 = (PL_RETENTION_5_LATCH && !PL_1_SEL_5B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K47)
		{
			if (K35) PL_1_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_5_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K35) PL_1_SEL_5_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );

	// pl select pos 2 sys 2 latch motors
	// latch 1b
	bool K57 = (PL_RETENTION_1_RELEASE && !PL_2_SEL_1B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K55 = (PL_RETENTION_1_LATCH && !PL_2_SEL_1B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K57)
		{
			if (K55) PL_2_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_1_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K55) PL_2_SEL_1_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 2b
	bool K33 = (PL_RETENTION_2_RELEASE && !PL_2_SEL_2B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K31 = (PL_RETENTION_2_LATCH && !PL_2_SEL_2B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K33)
		{
			if (K31) PL_2_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_2_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K31) PL_2_SEL_2_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 3b
	bool K58 = (PL_RETENTION_3_RELEASE && !PL_2_SEL_3B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K56 = (PL_RETENTION_3_LATCH && !PL_2_SEL_3B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K58)
		{
			if (K56) PL_2_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_3_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K56) PL_2_SEL_3_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 4b
	bool K69 = (PL_RETENTION_4_RELEASE && !PL_2_SEL_4B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K67 = (PL_RETENTION_4_LATCH && !PL_2_SEL_4B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K69)
		{
			if (K67) PL_2_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K67) PL_2_SEL_4_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 5b
	bool K48 = (PL_RETENTION_5_RELEASE && !PL_2_SEL_5B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K36 = (PL_RETENTION_5_LATCH && !PL_2_SEL_5B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K48)
		{
			if (K36) PL_2_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_5_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K36) PL_2_SEL_5_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );

	// pl select pos 3 sys 2 latch motors
	// latch 1b
	bool K75 = (PL_RETENTION_1_RELEASE && !PL_3_SEL_1B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K73 = (PL_RETENTION_1_LATCH && !PL_3_SEL_1B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K75)
		{
			if (K73) PL_3_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_1_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K73) PL_3_SEL_1_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 2b
	bool K21 = (PL_RETENTION_2_RELEASE && !PL_3_SEL_2B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K19 = (PL_RETENTION_2_LATCH && !PL_3_SEL_2B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K21)
		{
			if (K19) PL_3_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_2_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K19) PL_3_SEL_2_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 3b
	bool K46 = (PL_RETENTION_3_RELEASE && !PL_3_SEL_3B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K44 = (PL_RETENTION_3_LATCH && !PL_3_SEL_3B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K46)
		{
			if (K44) PL_3_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_3_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K44) PL_3_SEL_3_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 4b
	bool K45 = (PL_RETENTION_4_RELEASE && !PL_3_SEL_4B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K43 = (PL_RETENTION_4_LATCH && !PL_3_SEL_4B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K45)
		{
			if (K43) PL_3_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K43) PL_3_SEL_4_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 5b
	bool K82 = (PL_RETENTION_5_RELEASE && !PL_3_SEL_5B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K80 = (PL_RETENTION_5_LATCH && !PL_3_SEL_5B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K82)
		{
			if (K80) PL_3_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_5_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K80) PL_3_SEL_5_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );

	// oper status
	bool oper_status_1 = MNA_RELAY_LOGIC_POWER && !(K43 || K29 || K37 || K6 || K28 || K62 || K5 || K34 || K46);
	bool oper_status_2 = MNA_RELAY_LOGIC_POWER && !(K25 || K27 || K2 || K26 || K64 || K17 || K32 || K48 || K44);
	bool oper_status_3 = MNA_RELAY_LOGIC_POWER && !(K57 || K81 || K1 || K41 || K18 || K42 || K76 || K36 || K31);
	bool oper_status_4 = MNA_RELAY_LOGIC_POWER && !(K35 || K69 || K3 || K39 || K75 || K4 || K19 || K54 || K78);
	bool oper_status_5 = MNA_RELAY_LOGIC_POWER && !(K79 || K50 || K13 || K30 || K66 || K24 || K70 || K82);
	bool oper_status_6 = MNA_RELAY_LOGIC_POWER && !(K38 || K67 || K15 || K40 || K52 || K12 || K58);
	bool oper_status_7 = MNB_RELAY_LOGIC_POWER && !(K45 || K53 || K63 || K73 || K68 || K80 || K33);
	bool oper_status_8 = MNB_RELAY_LOGIC_POWER && !(K47 || K55 || K49 || K51 || K21 || K56);

	if (oper_status_1) OPER_STATUS_1.SetLine();
	else OPER_STATUS_1.ResetLine();
	if (oper_status_2) OPER_STATUS_2.SetLine();
	else OPER_STATUS_2.ResetLine();
	if (oper_status_3) OPER_STATUS_3.SetLine();
	else OPER_STATUS_3.ResetLine();
	if (oper_status_4) OPER_STATUS_4.SetLine();
	else OPER_STATUS_4.ResetLine();
	if (oper_status_5) OPER_STATUS_5.SetLine();
	else OPER_STATUS_5.ResetLine();
	if (oper_status_6) OPER_STATUS_6.SetLine();
	else OPER_STATUS_6.ResetLine();
	if (oper_status_7) OPER_STATUS_7.SetLine();
	else OPER_STATUS_7.ResetLine();
	if (oper_status_8) OPER_STATUS_8.SetLine();
	else OPER_STATUS_8.ResetLine();
	return;
}
