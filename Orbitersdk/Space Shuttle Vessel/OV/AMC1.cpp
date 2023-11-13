/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/23   GLS
2022/01/25   GLS
2022/08/05   GLS
2022/09/08   GLS
2023/07/23   GLS
2023/07/25   GLS
2023/10/02   GLS
2023/11/12   GLS
********************************************/
#include "AMC1.h"


AMC1::AMC1( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "AMC1" )
{
}

AMC1::~AMC1()
{
}

void AMC1::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	//LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 4 );
	LH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
	//L_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	//LH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	//LH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	//LH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	//LH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	//LH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	//LH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	//LH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	//LH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	//LH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	//LH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	LH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	LH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	LH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_AMC", 16 );
	CL_LATCH_1_STOW_1.Connect( pBundle, 0 );
	//CL_LATCH_1_STOW_2.Connect( pBundle, 1 );
	CL_LATCH_1_DEPLOY_1.Connect( pBundle, 2 );
	//CL_LATCH_1_DEPLOY_2.Connect( pBundle, 3 );
	CL_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	//CL_1_MOTOR_2_PWR.Connect( pBundle, 5 );
	CL_LATCH_2_STOW_1.Connect( pBundle, 6 );
	//CL_LATCH_2_STOW_2.Connect( pBundle, 7 );
	CL_LATCH_2_DEPLOY_1.Connect( pBundle, 8 );
	//CL_LATCH_2_DEPLOY_2.Connect( pBundle, 9 );
	CL_2_MOTOR_1_PWR.Connect( pBundle, 10 );
	//CL_2_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_AMC", 16 );
	LEFT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	//LEFT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	LEFT_DOOR_OPEN_1.Connect( pBundle, 2 );
	//LEFT_DOOR_OPEN_2.Connect( pBundle, 3 );
	LEFT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	//LEFT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	//LEFT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	LEFT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	//LEFT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	LEFT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	//LEFT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	LEFT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	//LEFT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	LEFT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	//LEFT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_POWER", 16 );
	ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW.Connect( pBundle, 0 );
	ET_UMBILICAL_DOOR_LEFT_CLOSE.Connect( pBundle, 1 );
	ET_UMBILICAL_DOOR_LEFT_OPEN.Connect( pBundle, 2 );
	ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH.Connect( pBundle, 3 );
	ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE.Connect( pBundle, 4 );
	//ET_UMBILICAL_DOOR_RIGHT_CLOSE.Connect( pBundle, 5 );
	//ET_UMBILICAL_DOOR_RIGHT_OPEN.Connect( pBundle, 6 );
	//ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH.Connect( pBundle, 7 );
	//ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "LRCS_MANF_12_ISOL", 12 );
	L_FU_MANF_ISOV_NO_2_MOTOR_PWR.Connect( pBundle, 6 );
	L_OX_MANF_ISOV_NO_2_MOTOR_PWR.Connect( pBundle, 7 );
	L_FU_MANF_ISOV_2_OP.Connect( pBundle, 8 );
	L_FU_MANF_ISOV_2_CL.Connect( pBundle, 9 );
	L_OX_MANF_ISOV_2_OP.Connect( pBundle, 10 );
	L_OX_MANF_ISOV_2_CL.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "RRCS_MANF_12_ISOL", 12 );
	R_FU_MANF_ISOV_NO_2_MOTOR_PWR.Connect( pBundle, 6 );
	R_OX_MANF_ISOV_NO_2_MOTOR_PWR.Connect( pBundle, 7 );
	R_FU_MANF_ISOV_2_OP.Connect( pBundle, 8 );
	R_FU_MANF_ISOV_2_CL.Connect( pBundle, 9 );
	R_OX_MANF_ISOV_2_OP.Connect( pBundle, 10 );
	R_OX_MANF_ISOV_2_CL.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "LRCS_TANK_ISOL_345", 12 );
	L_FU_TK_ISOL_345_A_MOTOR_PWR.Connect( pBundle, 0 );
	L_OX_TK_ISOL_345_A_MOTOR_PWR.Connect( pBundle, 1 );
	L_FU_TK_ISO_V_345_A_OP.Connect( pBundle, 4 );
	L_FU_TK_ISO_V_345_A_CL.Connect( pBundle, 5 );
	L_OX_TK_ISO_V_345_A_OP.Connect( pBundle, 6 );
	L_OX_TK_ISO_V_345_A_CL.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RRCS_TANK_ISOL_345", 12 );
	R_FU_TK_ISOL_345_A_MOTOR_PWR.Connect( pBundle, 0 );
	R_OX_TK_ISOL_345_A_MOTOR_PWR.Connect( pBundle, 1 );
	R_FU_TK_ISO_V_345_A_OP.Connect( pBundle, 4 );
	R_FU_TK_ISO_V_345_A_CL.Connect( pBundle, 5 );
	R_OX_TK_ISO_V_345_A_OP.Connect( pBundle, 6 );
	R_OX_TK_ISO_V_345_A_CL.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RRCS_XFD_345", 10 );
	R_RCS_FU_XFD_V_345_MOTOR_PWR.Connect( pBundle, 0 );
	R_RCS_OX_XFD_V_345_MOTOR_PWR.Connect( pBundle, 1 );
	R_RCS_FU_XFD_345_OP_1.Connect( pBundle, 2 );
	R_RCS_FU_XFD_345_CL_1.Connect( pBundle, 3 );
	R_RCS_FU_XFD_345_OP_2.Connect( pBundle, 4 );
	R_RCS_FU_XFD_345_CL_2.Connect( pBundle, 5 );
	R_RCS_OX_XFD_345_OP_1.Connect( pBundle, 6 );
	R_RCS_OX_XFD_345_CL_1.Connect( pBundle, 7 );
	R_RCS_OX_XFD_345_OP_2.Connect( pBundle, 8 );
	R_RCS_OX_XFD_345_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LRCS_XFD_345", 10 );
	L_RCS_FU_XFD_V_345_MOTOR_PWR.Connect( pBundle, 0 );
	L_RCS_OX_XFD_V_345_MOTOR_PWR.Connect( pBundle, 1 );
	L_RCS_FU_XFD_345_OP_1.Connect( pBundle, 2 );
	L_RCS_FU_XFD_345_CL_1.Connect( pBundle, 3 );
	L_RCS_FU_XFD_345_OP_2.Connect( pBundle, 4 );
	L_RCS_FU_XFD_345_CL_2.Connect( pBundle, 5 );
	L_RCS_OX_XFD_345_OP_1.Connect( pBundle, 6 );
	L_RCS_OX_XFD_345_CL_1.Connect( pBundle, 7 );
	L_RCS_OX_XFD_345_OP_2.Connect( pBundle, 8 );
	L_RCS_OX_XFD_345_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LOMS_XFD_A", 10 );
	L_OMS_FU_XFD_V_A_MOTOR_PWR.Connect( pBundle, 0 );
	L_OMS_OX_XFD_V_A_MOTOR_PWR.Connect( pBundle, 1 );
	L_OMS_FU_XFD_V_A_OP_1.Connect( pBundle, 2 );
	L_OMS_FU_XFD_V_A_CL_1.Connect( pBundle, 3 );
	L_OMS_FU_XFD_V_A_OP_2.Connect( pBundle, 4 );
	L_OMS_FU_XFD_V_A_CL_2.Connect( pBundle, 5 );
	L_OMS_OX_XFD_V_A_OP_1.Connect( pBundle, 6 );
	L_OMS_OX_XFD_V_A_CL_1.Connect( pBundle, 7 );
	L_OMS_OX_XFD_V_A_OP_2.Connect( pBundle, 8 );
	L_OMS_OX_XFD_V_A_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LOMS_TANK_ISOL_A", 10 );
	L_OMS_FU_TK_ISOV_A_MOTOR_PWR.Connect( pBundle, 0 );
	L_OMS_OX_TK_ISOV_A_MOTOR_PWR.Connect( pBundle, 1 );
	L_OMS_FU_TK_ISOV_A_OP_1.Connect( pBundle, 2 );
	L_OMS_FU_TK_ISOV_A_CL_1.Connect( pBundle, 3 );
	L_OMS_FU_TK_ISOV_A_OP_2.Connect( pBundle, 4 );
	L_OMS_FU_TK_ISOV_A_CL_2.Connect( pBundle, 5 );
	L_OMS_OX_TK_ISOV_A_OP_1.Connect( pBundle, 6 );
	L_OMS_OX_TK_ISOV_A_CL_1.Connect( pBundle, 7 );
	L_OMS_OX_TK_ISOV_A_OP_2.Connect( pBundle, 8 );
	L_OMS_OX_TK_ISOV_A_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "ROMS_TANK_ISOL_A", 10 );
	R_OMS_FU_TK_ISOV_A_MOTOR_PWR.Connect( pBundle, 0 );
	R_OMS_OX_TK_ISOV_A_MOTOR_PWR.Connect( pBundle, 1 );
	R_OMS_FU_TK_ISOV_A_OP_1.Connect( pBundle, 2 );
	R_OMS_FU_TK_ISOV_A_CL_1.Connect( pBundle, 3 );
	R_OMS_FU_TK_ISOV_A_OP_2.Connect( pBundle, 4 );
	R_OMS_FU_TK_ISOV_A_CL_2.Connect( pBundle, 5 );
	R_OMS_OX_TK_ISOV_A_OP_1.Connect( pBundle, 6 );
	R_OMS_OX_TK_ISOV_A_CL_1.Connect( pBundle, 7 );
	R_OMS_OX_TK_ISOV_A_OP_2.Connect( pBundle, 8 );
	R_OMS_OX_TK_ISOV_A_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_ManifIsol_TB", 16 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.Connect( pBundle, 2 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_ManifIsol_TB", 16 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.Connect( pBundle, 2 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_ManifIsol_SW", 16 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN.Connect( pBundle, 2 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_ManifIsol_SW", 16 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN.Connect( pBundle, 2 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_TB", 16 );
	AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_OPEN.Connect( pBundle, 6 );
	AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_TB", 16 );
	AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_OPEN.Connect( pBundle, 6 );
	AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_SW", 16 );
	AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_OPEN.Connect( pBundle, 6 );
	AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_SW", 16 );
	AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_OPEN.Connect( pBundle, 6 );
	AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RCS_Crossfeed_SW", 16 );
	AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN.Connect( pBundle, 2 );
	AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE.Connect( pBundle, 3 );
	AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN.Connect( pBundle, 6 );
	AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RCS_Crossfeed_TB", 16 );
	AFT_LEFT_RCS_CROSSFEED_345_TB_OPEN.Connect( pBundle, 2 );
	AFT_LEFT_RCS_CROSSFEED_345_TB_CLOSE.Connect( pBundle, 3 );
	AFT_RIGHT_RCS_CROSSFEED_345_TB_OPEN.Connect( pBundle, 6 );
	AFT_RIGHT_RCS_CROSSFEED_345_TB_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "OMS_Crossfeed_DC", 16 );
	LEFT_OMS_CROSSFEED_A_SW_OPEN.Connect( pBundle, 0 );
	LEFT_OMS_CROSSFEED_A_SW_CLOSE.Connect( pBundle, 1 );
	LEFT_OMS_CROSSFEED_A_TB_OPEN.Connect( pBundle, 8 );
	LEFT_OMS_CROSSFEED_A_TB_CLOSE.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LeftOMS_DC", 16 );
	LEFT_OMS_TANK_ISOLATION_A_SW_OPEN.Connect( pBundle, 4 );
	LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE.Connect( pBundle, 5 );
	LEFT_OMS_TANK_ISOLATION_A_TB_OPEN.Connect( pBundle, 8 );
	LEFT_OMS_TANK_ISOLATION_A_TB_CLOSE.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "RightOMS_DC", 16 );
	RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN.Connect( pBundle, 4 );
	RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE.Connect( pBundle, 5 );
	RIGHT_OMS_TANK_ISOLATION_A_TB_OPEN.Connect( pBundle, 8 );
	RIGHT_OMS_TANK_ISOLATION_A_TB_CLOSE.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "RCS_XFD_AMC_MDM", 4 );
	RCS_L_OXFU_XFD_VLV_345_OP.Connect( pBundle, 2 );
	RCS_R_OXFU_XFD_VLV_345_OP.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH0", 16 );
	LH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
	LH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 5 );
	LH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH1", 16 );
	L_OMS_FU_TK_ISOV_A_OP.Connect( pBundle, 3 );
	L_OMS_FU_TK_ISOV_A_CL.Connect( pBundle, 4 );
	L_OMS_OX_TK_ISOV_A_OP.Connect( pBundle, 5 );
	L_OMS_OX_TK_ISOV_A_CL.Connect( pBundle, 6 );
	L_OMS_FU_XFD_V_A_OP.Connect( pBundle, 7 );
	L_OMS_FU_XFD_V_A_CL.Connect( pBundle, 8 );
	L_OMS_OX_XFD_V_A_OP.Connect( pBundle, 11 );
	L_OMS_OX_XFD_V_A_CL.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH2", 16 );
	L_RCS_XFD_345_CL.Connect( pBundle, 0 );
	L_RCS_XFD_345_OP.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM15_CH0", 16 );
	LH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 3 );
	LH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 4 );
	LH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM15_CH2", 16 );
	R_RCS_OX_XFD_345_CL.Connect( pBundle, 0 );
	R_RCS_OX_XFD_345_OP.Connect( pBundle, 1 );
	R_RCS_FU_XFD_345_CL.Connect( pBundle, 2 );
	R_RCS_FU_XFD_345_OP.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM7_CH1", 16 );
	L_OMS_TK_V_A_OP.Connect( pBundle, 5 );
	L_OMS_TK_V_A_CL.Connect( pBundle, 6 );
	L_OMS_XFD_A_OP.Connect( pBundle, 11 );
	L_OMS_XFD_A_CL.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM7_CH2", 16 );
	L_RCS_OX_XFD_345_CL.Connect( pBundle, 0 );
	L_RCS_OX_XFD_345_OP.Connect( pBundle, 1 );
	L_RCS_FU_XFD_345_CL.Connect( pBundle, 2 );
	L_RCS_FU_XFD_345_OP.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM15_CH2", 16 );
	R_RCS_XFD_345_CL.Connect( pBundle, 0 );
	R_RCS_XFD_345_OP.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM7_CH1", 16 );
	R_OMS_TK_V_A_OP.Connect( pBundle, 5 );
	R_OMS_TK_V_A_CL.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM7_CH2", 16 );
	L_FU_TK_ISOV_345_A_CL.Connect( pBundle, 2 );
	L_FU_TK_ISOV_345_A_OP.Connect( pBundle, 3 );
	L_OX_TK_ISOV_345_A_CL.Connect( pBundle, 4 );
	L_OX_TK_ISOV_345_A_OP.Connect( pBundle, 5 );
	L_MANF_ISOV_NO_2_OP.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM15_CH2", 16 );
	R_FU_TK_ISOV_345_A_CL.Connect( pBundle, 2 );
	R_FU_TK_ISOV_345_A_OP.Connect( pBundle, 3 );
	R_OX_TK_ISOV_345_A_CL.Connect( pBundle, 4 );
	R_OX_TK_ISOV_345_A_OP.Connect( pBundle, 5 );
	R_MANF_ISOV_NO_2_OP.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM7_CH0", 16 );
	L_MANF_ISOV_NO_2_CL_A.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM7_CH1", 16 );
	R_OMS_FU_TK_ISOV_A_OP.Connect( pBundle, 3 );
	R_OMS_FU_TK_ISOV_A_CL.Connect( pBundle, 4 );
	R_OMS_OX_TK_ISOV_A_OP.Connect( pBundle, 5 );
	R_OMS_OX_TK_ISOV_A_CL.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM7_CH2", 16 );
	R_MANF_ISOV_NO_2_CL_B.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM15_CH0", 16 );
	R_MANF_ISOV_NO_2_CL_A.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM15_CH2", 16 );
	L_MANF_ISOV_NO_2_CL_B.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM1_CH1", 16 );
	OPER_STATUS_1.Connect( pBundle, 2 );
	OPER_STATUS_2.Connect( pBundle, 3 );
	OPER_STATUS_3.Connect( pBundle, 4 );
	OPER_STATUS_4.Connect( pBundle, 5 );
	return;
}

void AMC1::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNA_RELAY_LOGIC_POWER = true;

	// VENT DOORS
	// left 8/9 motor 1
	bool K4 = MNA_RELAY_LOGIC_POWER && (LH_VENTS_8_9_MOTOR_1_OPEN_A.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_OPEN_1.IsSet( 26.0f ));// OPN A
	bool K3 = MNA_RELAY_LOGIC_POWER && (LH_VENTS_8_9_MOTOR_1_OPEN_B.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_OPEN_1.IsSet( 26.0f ));// OPN B
	bool K2 = MNA_RELAY_LOGIC_POWER && ((LH_VENTS_8_9_MOTOR_1_CLOSE_A.IsSet( 26.0f ) || (LH_VENTS_8_9_MOTOR_1_PURGE_A.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_PURGE_IND_1.IsSet( 26.0f ))) && !LH_VENTS_8_AND_9_CLOSE_1.IsSet( 26.0f ));// CLS A
	bool K1 = MNA_RELAY_LOGIC_POWER && ((LH_VENTS_8_9_MOTOR_1_CLOSE_B.IsSet( 26.0f ) || (LH_VENTS_8_9_MOTOR_1_PURGE_B.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_PURGE_IND_1.IsSet( 26.0f ))) && !LH_VENTS_8_AND_9_CLOSE_1.IsSet( 26.0f ));// CLS B

	if (K4 && K3)
	{
		if (K2 && K1) LH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( 0.0f );
		else LH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K2 && K1) LH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( -1.0f );
		else LH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// ET UMBILICAL DOORS
	bool K9 = ET_DR_CLS_AND_LAT_ARM_1_FA1 || ET_DR_CLS_AND_LAT_ARM_1_FA3;
	// left drive motor 1
	bool K16 = ((L_DOOR_CL_1_FA4 || L_DOOR_CL_1_FA2) || ET_UMBILICAL_DOOR_LEFT_CLOSE) && !LEFT_DOOR_CLOSE_1 && (ET_UMBILICAL_DOOR_LEFT_CLOSE || K9);// CL
	bool K15 = ET_UMBILICAL_DOOR_LEFT_OPEN && !LEFT_DOOR_OPEN_1;// OP

	if (K16)
	{
		if (K15) LEFT_DOOR_MOTOR_1_PWR.SetLine( 0.0f );
		else LEFT_DOOR_MOTOR_1_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K15) LEFT_DOOR_MOTOR_1_PWR.SetLine( 1.0f );
		else LEFT_DOOR_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// left latch motor 1
	bool K20 = ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE && !LEFT_DOOR_LATCH_REL_1;// RLS A
	bool K19 = ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE && !LEFT_DOOR_LATCH_REL_1;// RLS B
	bool K18 = (((L_LATCH_A1_FA2 || L_LATCH_A1_FA1) || ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH) && !LEFT_DOOR_LATCH_LAT_1) && (ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH || K9);// LCH A
	bool K17 = (((L_LATCH_B1_FA3 || L_LATCH_B1_FA4) || ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH) && !LEFT_DOOR_LATCH_LAT_1) && LEFT_DOOR_RDY_TO_LCH_1;// LCH B

	if (K20 && K19)
	{
		if (K18 && K17) LEFT_DOOR_LATCH_MOTOR_1_PWR.SetLine( 0.0f );
		else LEFT_DOOR_LATCH_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K18 && K17) LEFT_DOOR_LATCH_MOTOR_1_PWR.SetLine( -1.0f );
		else LEFT_DOOR_LATCH_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// cl latch 1 motor 1
	bool K8 = ((CL_1_STOW_A1_FA3 || CL_1_STOW_A1_FA4) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_1_STOW_1;// STW A
	bool K7 = ((CL_1_STOW_B1_FA2 || CL_1_STOW_B1_FA1) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_1_STOW_1;// STW B
	bool K6 = (CL_1_DEPLOY_A1_FA2 || CL_1_DEPLOY_A1_FA1) && !CL_LATCH_1_DEPLOY_1;// DPLY A
	bool K5 = (CL_1_DEPLOY_B1_FA3 || CL_1_DEPLOY_B1_FA4) && !CL_LATCH_1_DEPLOY_1;// DPLY B

	if (K8 && K7)
	{
		if (K6 && K5) CL_1_MOTOR_1_PWR.SetLine( 0.0f );
		else CL_1_MOTOR_1_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K6 && K5) CL_1_MOTOR_1_PWR.SetLine( 1.0f );
		else CL_1_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// cl latch 2 motor 1
	bool K11 = (CL_2_DEPLOY_A1_FA2 || CL_2_DEPLOY_A1_FA4) && !CL_LATCH_2_DEPLOY_1;// DPLY A
	bool K10 = (CL_2_DEPLOY_B1_FA3 || CL_2_DEPLOY_B1_FA1) && !CL_LATCH_2_DEPLOY_1;// DPLY B
	bool K13 = ((CL_2_STOW_A1_FA3 || CL_2_STOW_A1_FA1) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_2_STOW_1;// STW A
	bool K12 = ((CL_2_STOW_B1_FA2 || CL_2_STOW_B1_FA4) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_2_STOW_1;// STW B

	if (K13 && K12)
	{
		if (K11 && K10) CL_2_MOTOR_1_PWR.SetLine( 0.0f );
		else CL_2_MOTOR_1_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K11 && K10) CL_2_MOTOR_1_PWR.SetLine( 1.0f );
		else CL_2_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// AFT RCS ISOLATION VALVES MANIFOLD 2
	bool K23 = (L_MANF_ISOV_NO_2_CL_A.IsSet( 26.0f ) || L_MANF_ISOV_NO_2_CL_B.IsSet( 26.0f ) || AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN || (L_FU_MANF_ISOV_2_CL && L_OX_MANF_ISOV_2_CL));// CL
	bool K24 = (L_MANF_ISOV_NO_2_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE || (L_FU_MANF_ISOV_2_OP && L_OX_MANF_ISOV_2_OP));// OP
	
	if (K24)
	{
		if (K23)
		{
			L_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
			L_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			L_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 1.0f );
			L_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K23)
		{
			L_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( -1.0f );
			L_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			L_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
			L_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (L_FU_MANF_ISOV_2_OP && L_OX_MANF_ISOV_2_OP) AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.SetLine();
	else AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.ResetLine();
	if (L_FU_MANF_ISOV_2_CL && L_OX_MANF_ISOV_2_CL) AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.ResetLine();

	bool K21 = (R_MANF_ISOV_NO_2_CL_A.IsSet( 26.0f ) || R_MANF_ISOV_NO_2_CL_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN || (R_FU_MANF_ISOV_2_CL && R_OX_MANF_ISOV_2_CL));// CL
	bool K22 = (R_MANF_ISOV_NO_2_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE || (R_FU_MANF_ISOV_2_OP && R_OX_MANF_ISOV_2_OP));// OP
	
	if (K22)
	{
		if (K21)
		{
			R_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
			R_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			R_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 1.0f );
			R_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K21)
		{
			R_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( -1.0f );
			R_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			R_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
			R_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (R_FU_MANF_ISOV_2_OP && R_OX_MANF_ISOV_2_OP) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.SetLine();
	else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.ResetLine();
	if (R_FU_MANF_ISOV_2_CL && R_OX_MANF_ISOV_2_CL) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.ResetLine();

	
	// AFT RCS ISOLATION VALVES TANK 3/4/5A
	bool K25 = (AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || R_OX_TK_ISOV_345_A_CL.IsSet( 26.0f )) && !(AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_OPEN || (R_FU_TK_ISO_V_345_A_CL && R_OX_TK_ISO_V_345_A_CL));// CL
	bool K26 = (AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_OPEN || R_OX_TK_ISOV_345_A_OP.IsSet( 26.0f )) && !(AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || R_OX_TK_ISO_V_345_A_OP);// OP

	if (K25)
	{
		if (K26) R_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
		else R_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K26) R_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( 1.0f );
		else R_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K27 = (AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || R_FU_TK_ISOV_345_A_CL.IsSet( 26.0f )) && !(AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_OPEN || (R_FU_TK_ISO_V_345_A_CL && R_OX_TK_ISO_V_345_A_CL));// CL
	bool K28 = (AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_OPEN || R_FU_TK_ISOV_345_A_OP.IsSet( 26.0f )) && !(AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || R_FU_TK_ISO_V_345_A_OP);// OP

	if (K27)
	{
		if (K28) R_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
		else R_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K28) R_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( 1.0f );
		else R_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_FU_TK_ISO_V_345_A_OP && R_OX_TK_ISO_V_345_A_OP) AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_OPEN.SetLine();
	else AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_OPEN.ResetLine();
	if (R_FU_TK_ISO_V_345_A_CL && R_OX_TK_ISO_V_345_A_CL) AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_CLOSE.ResetLine();


	bool K29 = (AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || L_OX_TK_ISOV_345_A_CL.IsSet( 26.0f )) && !(AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_OPEN || (L_FU_TK_ISO_V_345_A_CL && L_OX_TK_ISO_V_345_A_CL));// CL
	bool K30 = (AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_OPEN || L_OX_TK_ISOV_345_A_OP.IsSet( 26.0f )) && !(AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || L_OX_TK_ISO_V_345_A_OP);// OP

	if (K29)
	{
		if (K30) L_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
		else L_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K30) L_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( 1.0f );
		else L_OX_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K31 = (AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || L_FU_TK_ISOV_345_A_CL.IsSet( 26.0f )) && !(AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_OPEN || (L_FU_TK_ISO_V_345_A_CL && L_OX_TK_ISO_V_345_A_CL));// CL
	bool K32 = (AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_OPEN || L_FU_TK_ISOV_345_A_OP.IsSet( 26.0f )) && !(AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_CLOSE || L_FU_TK_ISO_V_345_A_OP);// OP

	if (K31)
	{
		if (K32) L_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
		else L_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K32) L_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( 1.0f );
		else L_FU_TK_ISOL_345_A_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_FU_TK_ISO_V_345_A_OP && L_OX_TK_ISO_V_345_A_OP) AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_OPEN.SetLine();
	else AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_OPEN.ResetLine();
	if (L_FU_TK_ISO_V_345_A_CL && L_OX_TK_ISO_V_345_A_CL) AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_CLOSE.ResetLine();

	
	// RIGHT RCS XFEED MANIFOLD 3/4/5
	bool K33 = (R_RCS_FU_XFD_345_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN || R_RCS_FU_XFD_345_CL_1);// CL B
	bool K34 = (R_RCS_XFD_345_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN || R_RCS_FU_XFD_345_CL_1);// CL A
	bool K35 = (R_RCS_FU_XFD_345_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE || R_RCS_FU_XFD_345_OP_1);// OP B
	bool K36 = (R_RCS_XFD_345_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE || R_RCS_FU_XFD_345_OP_2);// OP A
	
	if (K35) R_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else if (K36) R_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K34)
		{
			if (K33) R_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( -1.0f );
			else R_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K37 = (R_RCS_OX_XFD_345_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN || R_RCS_OX_XFD_345_CL_1);// CL B
	bool K38 = (R_RCS_XFD_345_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN || R_RCS_OX_XFD_345_CL_1);// CL A
	bool K39 = (R_RCS_OX_XFD_345_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE || R_RCS_OX_XFD_345_OP_1);// OP B
	bool K40 = (R_RCS_XFD_345_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE || R_RCS_OX_XFD_345_OP_2);// OP A
	
	if (K39) R_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else if (K40) R_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K38)
		{
			if (K37) R_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( -1.0f );
			else R_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_RCS_FU_XFD_345_OP_2 && R_RCS_OX_XFD_345_OP_2)
	{
		AFT_RIGHT_RCS_CROSSFEED_345_TB_OPEN.SetLine();
		RCS_R_OXFU_XFD_VLV_345_OP.SetLine();
	}
	else
	{
		AFT_RIGHT_RCS_CROSSFEED_345_TB_OPEN.ResetLine();
		RCS_R_OXFU_XFD_VLV_345_OP.ResetLine();
	}
	if (R_RCS_FU_XFD_345_CL_2 && R_RCS_OX_XFD_345_CL_2) AFT_RIGHT_RCS_CROSSFEED_345_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_CROSSFEED_345_TB_CLOSE.ResetLine();
	

	// LEFT RCS XFEED MANIFOLD 3/4/5
	bool K66 = (L_RCS_XFD_345_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE || L_RCS_FU_XFD_345_OP_2);// OP A
	bool K68 = (L_RCS_FU_XFD_345_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE || L_RCS_FU_XFD_345_OP_1);// OP B
	bool K70 = (L_RCS_XFD_345_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN || L_RCS_FU_XFD_345_CL_1);// CL B
	bool K72 = (L_RCS_FU_XFD_345_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN || L_RCS_FU_XFD_345_CL_1);// CL A
	
	if (K68) L_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else if (K66) L_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K70)
		{
			if (K72) L_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( -1.0f );
			else L_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_RCS_FU_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K65 = (L_RCS_OX_XFD_345_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE || L_RCS_OX_XFD_345_OP_1);// OP B
	bool K67 = (L_RCS_XFD_345_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE || L_RCS_OX_XFD_345_OP_2);// OP A
	bool K69 = (L_RCS_XFD_345_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN || L_RCS_OX_XFD_345_CL_1);// CL B
	bool K71 = (L_RCS_OX_XFD_345_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN || L_RCS_OX_XFD_345_CL_1);// CL A
	
	if (K65) L_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else if (K67) L_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K69)
		{
			if (K71) L_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( -1.0f );
			else L_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_RCS_OX_XFD_V_345_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_RCS_FU_XFD_345_OP_2 && L_RCS_OX_XFD_345_OP_2)
	{
		AFT_LEFT_RCS_CROSSFEED_345_TB_OPEN.SetLine();
		RCS_L_OXFU_XFD_VLV_345_OP.SetLine();
	}
	else
	{
		AFT_LEFT_RCS_CROSSFEED_345_TB_OPEN.ResetLine();
		RCS_L_OXFU_XFD_VLV_345_OP.ResetLine();
	}
	if (L_RCS_FU_XFD_345_CL_2 && L_RCS_OX_XFD_345_CL_2) AFT_LEFT_RCS_CROSSFEED_345_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_CROSSFEED_345_TB_CLOSE.ResetLine();
	

	// LEFT OMS XFEED
	bool K49 = (L_OMS_FU_XFD_V_A_CL.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_CLOSE) && !(LEFT_OMS_CROSSFEED_A_SW_OPEN || L_OMS_FU_XFD_V_A_CL_1);// CL B
	bool K50 = (L_OMS_XFD_A_CL.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_CLOSE) && !(LEFT_OMS_CROSSFEED_A_SW_OPEN || L_OMS_FU_XFD_V_A_CL_1);// CL A
	bool K51 = (L_OMS_FU_XFD_V_A_OP.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_OPEN) && !(LEFT_OMS_CROSSFEED_A_SW_CLOSE || L_OMS_FU_XFD_V_A_OP_1);// OP A
	bool K52 = (L_OMS_XFD_A_OP.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_OPEN) && !(LEFT_OMS_CROSSFEED_A_SW_CLOSE || L_OMS_FU_XFD_V_A_OP_2);// OP B
	
	if (K51) L_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K52) L_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K50)
		{
			if (K49) L_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( -1.0f );
			else L_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K53 = (L_OMS_OX_XFD_V_A_CL.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_CLOSE) && !(LEFT_OMS_CROSSFEED_A_SW_OPEN || L_OMS_OX_XFD_V_A_CL_1);// CL B
	bool K54 = (L_OMS_XFD_A_CL.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_CLOSE) && !(LEFT_OMS_CROSSFEED_A_SW_OPEN || L_OMS_OX_XFD_V_A_CL_1);// CL A
	bool K55 = (L_OMS_OX_XFD_V_A_OP.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_OPEN) && !(LEFT_OMS_CROSSFEED_A_SW_CLOSE || L_OMS_OX_XFD_V_A_OP_1);// OP A
	bool K56 = (L_OMS_XFD_A_OP.IsSet( 26.0f ) || LEFT_OMS_CROSSFEED_A_SW_OPEN) && !(LEFT_OMS_CROSSFEED_A_SW_CLOSE || L_OMS_OX_XFD_V_A_OP_2);// OP B
	
	if (K55) L_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K56) L_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K54)
		{
			if (K53) L_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( -1.0f );
			else L_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_OMS_FU_XFD_V_A_OP_2 && L_OMS_OX_XFD_V_A_OP_2) LEFT_OMS_CROSSFEED_A_TB_OPEN.SetLine();
	else LEFT_OMS_CROSSFEED_A_TB_OPEN.ResetLine();
	if (L_OMS_FU_XFD_V_A_CL_2 && L_OMS_OX_XFD_V_A_CL_2) LEFT_OMS_CROSSFEED_A_TB_CLOSE.SetLine();
	else LEFT_OMS_CROSSFEED_A_TB_CLOSE.ResetLine();


	// OMS ISOLATION VALVES
	bool K41 = (L_OMS_FU_TK_ISOV_A_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_A_SW_OPEN || L_OMS_FU_TK_ISOV_A_CL_1);// CL B
	bool K42 = (L_OMS_TK_V_A_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_A_SW_OPEN || L_OMS_FU_TK_ISOV_A_CL_1);// CL A
	bool K43 = (L_OMS_FU_TK_ISOV_A_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE || L_OMS_FU_TK_ISOV_A_OP_1);// OP B
	bool K44 = (L_OMS_TK_V_A_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE || L_OMS_FU_TK_ISOV_A_OP_2);// OP A
	
	if (K44) L_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K43) L_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K42)
		{
			if (K41) L_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( -1.0f );
			else L_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K45 = (L_OMS_OX_TK_ISOV_A_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_A_SW_OPEN || L_OMS_OX_TK_ISOV_A_CL_1);// CL B
	bool K46 = (L_OMS_TK_V_A_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_A_SW_OPEN || L_OMS_OX_TK_ISOV_A_CL_1);// CL A
	bool K47 = (L_OMS_OX_TK_ISOV_A_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE || L_OMS_OX_TK_ISOV_A_OP_1);// OP B
	bool K48 = (L_OMS_TK_V_A_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE || L_OMS_OX_TK_ISOV_A_OP_2);// OP A
	
	if (K48) L_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K47) L_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K46)
		{
			if (K45) L_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( -1.0f );
			else L_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_OMS_FU_TK_ISOV_A_OP_2 && L_OMS_OX_TK_ISOV_A_OP_2) LEFT_OMS_TANK_ISOLATION_A_TB_OPEN.SetLine();
	else LEFT_OMS_TANK_ISOLATION_A_TB_OPEN.ResetLine();
	if (L_OMS_FU_TK_ISOV_A_CL_2 && L_OMS_OX_TK_ISOV_A_CL_2) LEFT_OMS_TANK_ISOLATION_A_TB_CLOSE.SetLine();
	else LEFT_OMS_TANK_ISOLATION_A_TB_CLOSE.ResetLine();

	bool K57 = (R_OMS_FU_TK_ISOV_A_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN || R_OMS_FU_TK_ISOV_A_CL_1);// CL B
	bool K58 = (R_OMS_TK_V_A_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN || R_OMS_FU_TK_ISOV_A_CL_1);// CL A
	bool K59 = (R_OMS_FU_TK_ISOV_A_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE || R_OMS_FU_TK_ISOV_A_OP_1);// OP B
	bool K60 = (R_OMS_TK_V_A_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE || R_OMS_FU_TK_ISOV_A_OP_2);// OP A
	
	if (K60) R_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K59) R_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K58)
		{
			if (K57) R_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( -1.0f );
			else R_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OMS_FU_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K61 = (R_OMS_OX_TK_ISOV_A_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN || R_OMS_OX_TK_ISOV_A_CL_1);// CL B
	bool K62 = (R_OMS_TK_V_A_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN || R_OMS_OX_TK_ISOV_A_CL_1);// CL A
	bool K63 = (R_OMS_OX_TK_ISOV_A_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE || R_OMS_OX_TK_ISOV_A_OP_1);// OP B
	bool K64 = (R_OMS_TK_V_A_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE || R_OMS_OX_TK_ISOV_A_OP_2);// OP A
	
	if (K64) R_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K63) R_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K62)
		{
			if (K61) R_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( -1.0f );
			else R_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OMS_OX_TK_ISOV_A_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_OMS_FU_TK_ISOV_A_OP_2 && R_OMS_OX_TK_ISOV_A_OP_2) RIGHT_OMS_TANK_ISOLATION_A_TB_OPEN.SetLine();
	else RIGHT_OMS_TANK_ISOLATION_A_TB_OPEN.ResetLine();
	if (R_OMS_FU_TK_ISOV_A_CL_2 && R_OMS_OX_TK_ISOV_A_CL_2) RIGHT_OMS_TANK_ISOLATION_A_TB_CLOSE.SetLine();
	else RIGHT_OMS_TANK_ISOLATION_A_TB_CLOSE.ResetLine();

	// oper status
	bool oper_status_1 = MNA_RELAY_LOGIC_POWER && !(K62 || K36 || K22 || K20 || K38 || K54 || K66 || K46 || K52 || K60 || K44 || K25 || K4 || K16 || K11 || K8 || K30 || K71);
	bool oper_status_2 = MNA_RELAY_LOGIC_POWER && !(K61 || K21 || K35 || K19 || K37 || K53 || K68 || K45 || K51 || K26 || K43 || K3 || K7 || K10 || K29 || K59 || K69);
	bool oper_status_3 = MNA_RELAY_LOGIC_POWER && !(K64 || K34 || K18 || K27 || K32 || K40 || K56 || K48 || K72 || K50 || K42 || K2 || K15 || K6 || K13 || K24 || K58 || K67);
	bool oper_status_4 = MNA_RELAY_LOGIC_POWER && !(K63 || K33 || K17 || K28 || K31 || K39 || K55 || K47 || K70 || K65 || K49 || K57 || K23 || K41 || K12 || K5 || K1);

	if (oper_status_1) OPER_STATUS_1.SetLine();
	else OPER_STATUS_1.ResetLine();
	if (oper_status_2) OPER_STATUS_2.SetLine();
	else OPER_STATUS_2.ResetLine();
	if (oper_status_3) OPER_STATUS_3.SetLine();
	else OPER_STATUS_3.ResetLine();
	if (oper_status_4) OPER_STATUS_4.SetLine();
	else OPER_STATUS_4.ResetLine();
	return;
}
