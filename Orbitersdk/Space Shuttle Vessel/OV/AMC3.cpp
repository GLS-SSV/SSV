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
2023/11/17   GLS
********************************************/
#include "AMC3.h"


AMC3::AMC3( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "AMC3" )
{
}

AMC3::~AMC3()
{
}

void AMC3::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	//LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 10 );
	RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
	//R_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	//R_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	//R_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	//RH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	//RH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	//RH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	//RH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	//RH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	//RH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	//RH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	//RH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	//RH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	//RH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	RH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	RH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	RH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_AMC", 16 );
	//CL_LATCH_1_STOW_1.Connect( pBundle, 0 );
	//CL_LATCH_1_STOW_2.Connect( pBundle, 1 );
	//CL_LATCH_1_DEPLOY_1.Connect( pBundle, 2 );
	//CL_LATCH_1_DEPLOY_2.Connect( pBundle, 3 );
	//CL_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	//CL_1_MOTOR_2_PWR.Connect( pBundle, 5 );
	//CL_LATCH_2_STOW_1.Connect( pBundle, 6 );
	CL_LATCH_2_STOW_2.Connect( pBundle, 7 );
	//CL_LATCH_2_DEPLOY_1.Connect( pBundle, 8 );
	CL_LATCH_2_DEPLOY_2.Connect( pBundle, 9 );
	//CL_2_MOTOR_1_PWR.Connect( pBundle, 10 );
	CL_2_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_AMC", 16 );
	//LEFT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	LEFT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	//LEFT_DOOR_OPEN_1.Connect( pBundle, 2 );
	LEFT_DOOR_OPEN_2.Connect( pBundle, 3 );
	//LEFT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	//LEFT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	//LEFT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	//LEFT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	LEFT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	//LEFT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	//LEFT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	//LEFT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	//LEFT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	//LEFT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	//LEFT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_RIGHT_AMC", 16 );
	RIGHT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	//RIGHT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	RIGHT_DOOR_OPEN_1.Connect( pBundle, 2 );
	//RIGHT_DOOR_OPEN_2.Connect( pBundle, 3 );
	RIGHT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	//RIGHT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	//RIGHT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	RIGHT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	//RIGHT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	RIGHT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	//RIGHT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	RIGHT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	//RIGHT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	RIGHT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	//RIGHT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_POWER", 16 );
	ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW.Connect( pBundle, 0 );
	ET_UMBILICAL_DOOR_LEFT_CLOSE.Connect( pBundle, 1 );
	ET_UMBILICAL_DOOR_LEFT_OPEN.Connect( pBundle, 2 );
	//ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH.Connect( pBundle, 3 );
	//ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE.Connect( pBundle, 4 );
	ET_UMBILICAL_DOOR_RIGHT_CLOSE.Connect( pBundle, 5 );
	ET_UMBILICAL_DOOR_RIGHT_OPEN.Connect( pBundle, 6 );
	ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH.Connect( pBundle, 7 );
	ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "LRCS_MANF_34_ISOL", 12 );
	L_FU_MANF_ISOV_NO_3_MOTOR_PWR.Connect( pBundle, 0 );
	L_OX_MANF_ISOV_NO_3_MOTOR_PWR.Connect( pBundle, 1 );
	L_FU_MANF_ISOV_3_OP.Connect( pBundle, 2 );
	L_FU_MANF_ISOV_3_CL.Connect( pBundle, 3 );
	L_OX_MANF_ISOV_3_OP.Connect( pBundle, 4 );
	L_OX_MANF_ISOV_3_CL.Connect( pBundle, 5 );
	L_FU_MANF_ISOV_NO_4_MOTOR_PWR.Connect( pBundle, 6 );
	L_OX_MANF_ISOV_NO_4_MOTOR_PWR.Connect( pBundle, 7 );
	L_FU_MANF_ISOV_4_OP.Connect( pBundle, 8 );
	L_FU_MANF_ISOV_4_CL.Connect( pBundle, 9 );
	L_OX_MANF_ISOV_4_OP.Connect( pBundle, 10 );
	L_OX_MANF_ISOV_4_CL.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "RRCS_MANF_34_ISOL", 12 );
	R_FU_MANF_ISOV_NO_3_MOTOR_PWR.Connect( pBundle, 0 );
	R_OX_MANF_ISOV_NO_3_MOTOR_PWR.Connect( pBundle, 1 );
	R_FU_MANF_ISOV_3_OP.Connect( pBundle, 2 );
	R_FU_MANF_ISOV_3_CL.Connect( pBundle, 3 );
	R_OX_MANF_ISOV_3_OP.Connect( pBundle, 4 );
	R_OX_MANF_ISOV_3_CL.Connect( pBundle, 5 );
	R_FU_MANF_ISOV_NO_4_MOTOR_PWR.Connect( pBundle, 6 );
	R_OX_MANF_ISOV_NO_4_MOTOR_PWR.Connect( pBundle, 7 );
	R_FU_MANF_ISOV_4_OP.Connect( pBundle, 8 );
	R_FU_MANF_ISOV_4_CL.Connect( pBundle, 9 );
	R_OX_MANF_ISOV_4_OP.Connect( pBundle, 10 );
	R_OX_MANF_ISOV_4_CL.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "LRCS_TANK_ISOL_12", 10 );
	L_FU_TK_ISOL_12_MOTOR_PWR.Connect( pBundle, 0 );
	L_OX_TK_ISOL_12_MOTOR_PWR.Connect( pBundle, 1 );
	L_FU_TK_ISO_V_12_OP_1.Connect( pBundle, 2 );
	L_FU_TK_ISO_V_12_CL_1.Connect( pBundle, 3 );
	L_FU_TK_ISO_V_12_OP_2.Connect( pBundle, 4 );
	L_FU_TK_ISO_V_12_CL_2.Connect( pBundle, 5 );
	L_OX_TK_ISO_V_12_OP_1.Connect( pBundle, 6 );
	L_OX_TK_ISO_V_12_CL_1.Connect( pBundle, 7 );
	L_OX_TK_ISO_V_12_OP_2.Connect( pBundle, 8 );
	L_OX_TK_ISO_V_12_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "RRCS_TANK_ISOL_12", 10 );
	R_FU_TK_ISOL_12_MOTOR_PWR.Connect( pBundle, 0 );
	R_OX_TK_ISOL_12_MOTOR_PWR.Connect( pBundle, 1 );
	R_FU_TK_ISO_V_12_OP_1.Connect( pBundle, 2 );
	R_FU_TK_ISO_V_12_CL_1.Connect( pBundle, 3 );
	R_FU_TK_ISO_V_12_OP_2.Connect( pBundle, 4 );
	R_FU_TK_ISO_V_12_CL_2.Connect( pBundle, 5 );
	R_OX_TK_ISO_V_12_OP_1.Connect( pBundle, 6 );
	R_OX_TK_ISO_V_12_CL_1.Connect( pBundle, 7 );
	R_OX_TK_ISO_V_12_OP_2.Connect( pBundle, 8 );
	R_OX_TK_ISO_V_12_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LRCS_XFD_12", 10 );
	L_RCS_FU_XFD_V_12_MOTOR_PWR.Connect( pBundle, 0 );
	L_RCS_OX_XFD_V_12_MOTOR_PWR.Connect( pBundle, 1 );
	L_RCS_FU_XFD_12_OP_1.Connect( pBundle, 2 );
	L_RCS_FU_XFD_12_CL_1.Connect( pBundle, 3 );
	L_RCS_FU_XFD_12_OP_2.Connect( pBundle, 4 );
	L_RCS_FU_XFD_12_CL_2.Connect( pBundle, 5 );
	L_RCS_OX_XFD_12_OP_1.Connect( pBundle, 6 );
	L_RCS_OX_XFD_12_CL_1.Connect( pBundle, 7 );
	L_RCS_OX_XFD_12_OP_2.Connect( pBundle, 8 );
	L_RCS_OX_XFD_12_CL_2.Connect( pBundle, 9 );
		
	pBundle = BundleManager()->CreateBundle( "RRCS_XFD_12", 10 );
	R_RCS_FU_XFD_V_12_MOTOR_PWR.Connect( pBundle, 0 );
	R_RCS_OX_XFD_V_12_MOTOR_PWR.Connect( pBundle, 1 );
	R_RCS_FU_XFD_12_OP_1.Connect( pBundle, 2 );
	R_RCS_FU_XFD_12_CL_1.Connect( pBundle, 3 );
	R_RCS_FU_XFD_12_OP_2.Connect( pBundle, 4 );
	R_RCS_FU_XFD_12_CL_2.Connect( pBundle, 5 );
	R_RCS_OX_XFD_12_OP_1.Connect( pBundle, 6 );
	R_RCS_OX_XFD_12_CL_1.Connect( pBundle, 7 );
	R_RCS_OX_XFD_12_OP_2.Connect( pBundle, 8 );
	R_RCS_OX_XFD_12_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "ROMS_XFD_A", 10 );
	R_OMS_FU_XFD_V_A_MOTOR_PWR.Connect( pBundle, 0 );
	R_OMS_OX_XFD_V_A_MOTOR_PWR.Connect( pBundle, 1 );
	R_OMS_FU_XFD_V_A_OP_1.Connect( pBundle, 2 );
	R_OMS_FU_XFD_V_A_CL_1.Connect( pBundle, 3 );
	R_OMS_FU_XFD_V_A_OP_2.Connect( pBundle, 4 );
	R_OMS_FU_XFD_V_A_CL_2.Connect( pBundle, 5 );
	R_OMS_OX_XFD_V_A_OP_1.Connect( pBundle, 6 );
	R_OMS_OX_XFD_V_A_CL_1.Connect( pBundle, 7 );
	R_OMS_OX_XFD_V_A_OP_2.Connect( pBundle, 8 );
	R_OMS_OX_XFD_V_A_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LOMS_TANK_ISOL_B", 10 );
	L_OMS_FU_TK_ISOV_B_MOTOR_PWR.Connect( pBundle, 0 );
	L_OMS_OX_TK_ISOV_B_MOTOR_PWR.Connect( pBundle, 1 );
	L_OMS_FU_TK_ISOV_B_OP_1.Connect( pBundle, 2 );
	L_OMS_FU_TK_ISOV_B_CL_1.Connect( pBundle, 3 );
	L_OMS_FU_TK_ISOV_B_OP_2.Connect( pBundle, 4 );
	L_OMS_FU_TK_ISOV_B_CL_2.Connect( pBundle, 5 );
	L_OMS_OX_TK_ISOV_B_OP_1.Connect( pBundle, 6 );
	L_OMS_OX_TK_ISOV_B_CL_1.Connect( pBundle, 7 );
	L_OMS_OX_TK_ISOV_B_OP_2.Connect( pBundle, 8 );
	L_OMS_OX_TK_ISOV_B_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "ROMS_TANK_ISOL_B", 10 );
	R_OMS_FU_TK_ISOV_B_MOTOR_PWR.Connect( pBundle, 0 );
	R_OMS_OX_TK_ISOV_B_MOTOR_PWR.Connect( pBundle, 1 );
	R_OMS_FU_TK_ISOV_B_OP_1.Connect( pBundle, 2 );
	R_OMS_FU_TK_ISOV_B_CL_1.Connect( pBundle, 3 );
	R_OMS_FU_TK_ISOV_B_OP_2.Connect( pBundle, 4 );
	R_OMS_FU_TK_ISOV_B_CL_2.Connect( pBundle, 5 );
	R_OMS_OX_TK_ISOV_B_OP_1.Connect( pBundle, 6 );
	R_OMS_OX_TK_ISOV_B_CL_1.Connect( pBundle, 7 );
	R_OMS_OX_TK_ISOV_B_OP_2.Connect( pBundle, 8 );
	R_OMS_OX_TK_ISOV_B_CL_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_ManifIsol_TB", 16 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.Connect( pBundle, 4 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.Connect( pBundle, 5 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.Connect( pBundle, 6 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_ManifIsol_TB", 16 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.Connect( pBundle, 4 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.Connect( pBundle, 5 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.Connect( pBundle, 6 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_ManifIsol_SW", 16 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN.Connect( pBundle, 4 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE.Connect( pBundle, 5 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN.Connect( pBundle, 6 );
	AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_ManifIsol_SW", 16 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN.Connect( pBundle, 4 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE.Connect( pBundle, 5 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN.Connect( pBundle, 6 );
	AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_TB", 16 );
	AFT_LEFT_RCS_TANK_ISOLATION_12_TB_OPEN.Connect( pBundle, 4 );
	AFT_LEFT_RCS_TANK_ISOLATION_12_TB_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_TB", 16 );
	AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_OPEN.Connect( pBundle, 4 );
	AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_SW", 16 );
	AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN.Connect( pBundle, 4 );
	AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_SW", 16 );
	AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN.Connect( pBundle, 4 );
	AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "RCS_Crossfeed_SW", 16 );
	AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN.Connect( pBundle, 0 );
	AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE.Connect( pBundle, 1 );
	AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN.Connect( pBundle, 4 );
	AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "RCS_Crossfeed_TB", 16 );
	AFT_LEFT_RCS_CROSSFEED_12_TB_OPEN.Connect( pBundle, 0 );
	AFT_LEFT_RCS_CROSSFEED_12_TB_CLOSE.Connect( pBundle, 1 );
	AFT_RIGHT_RCS_CROSSFEED_12_TB_OPEN.Connect( pBundle, 4 );
	AFT_RIGHT_RCS_CROSSFEED_12_TB_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "OMS_Crossfeed_DC", 16 );
	RIGHT_OMS_CROSSFEED_A_SW_OPEN.Connect( pBundle, 4 );
	RIGHT_OMS_CROSSFEED_A_SW_CLOSE.Connect( pBundle, 5 );
	RIGHT_OMS_CROSSFEED_A_TB_OPEN.Connect( pBundle, 12 );
	RIGHT_OMS_CROSSFEED_A_TB_CLOSE.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "LeftOMS_DC", 16 );
	LEFT_OMS_TANK_ISOLATION_B_SW_OPEN.Connect( pBundle, 6 );
	LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE.Connect( pBundle, 7 );
	LEFT_OMS_TANK_ISOLATION_B_TB_OPEN.Connect( pBundle, 10 );
	LEFT_OMS_TANK_ISOLATION_B_TB_CLOSE.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "RightOMS_DC", 16 );
	RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN.Connect( pBundle, 6 );
	RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE.Connect( pBundle, 7 );
	RIGHT_OMS_TANK_ISOLATION_B_TB_OPEN.Connect( pBundle, 10 );
	RIGHT_OMS_TANK_ISOLATION_B_TB_CLOSE.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH0", 16 );
	L_MANF_ISOV_NO_3_CL_A.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH1", 16 );
	R_OMS_FU_XFD_V_A_OP.Connect( pBundle, 9 );
	R_OMS_FU_XFD_V_A_CL.Connect( pBundle, 10 );
	R_OMS_OX_XFD_V_A_OP.Connect( pBundle, 13 );
	R_OMS_OX_XFD_V_A_CL.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM7_CH2", 16 );
	L_FU_TK_ISOV_12_CL_B.Connect( pBundle, 2 );
	L_FU_TK_ISOV_12_OP_B.Connect( pBundle, 3 );
	L_OX_TK_ISOV_12_CL_B.Connect( pBundle, 4 );
	L_OX_TK_ISOV_12_OP_B.Connect( pBundle, 5 );
	R_MANF_ISOV_NO_3_CL_B.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM15_CH0", 16 );
	R_MANF_ISOV_NO_3_CL_A.Connect( pBundle, 1 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM15_CH1", 16 );
	L_OMS_TK_V_B_OP.Connect( pBundle, 5 );
	L_OMS_TK_V_B_CL.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA1_IOM15_CH2", 16 );
	R_TK_ISOV_12_CL_A.Connect( pBundle, 4 );
	R_TK_ISOV_12_OP_A.Connect( pBundle, 5 );
	L_MANF_ISOV_NO_3_CL_B.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM7_CH1", 16 );
	R_OMS_XFD_A_OP.Connect( pBundle, 13 );
	R_OMS_XFD_A_CL.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM7_CH2", 16 );
	L_TK_ISOV_12_CL_A.Connect( pBundle, 4 );
	L_TK_ISOV_12_OP_A.Connect( pBundle, 5 );
	L_MANF_ISOV_NO_3_OP.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM15_CH1", 16 );
	L_OMS_FU_TK_ISOV_B_OP.Connect( pBundle, 3 );
	L_OMS_FU_TK_ISOV_B_CL.Connect( pBundle, 4 );
	L_OMS_OX_TK_ISOV_B_OP.Connect( pBundle, 5 );
	L_OMS_OX_TK_ISOV_B_CL.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM15_CH2", 16 );
	R_FU_TK_ISOV_12_CL_B.Connect( pBundle, 2 );
	R_FU_TK_ISOV_12_OP_B.Connect( pBundle, 3 );
	R_OX_TK_ISOV_12_CL_B.Connect( pBundle, 4 );
	R_OX_TK_ISOV_12_OP_B.Connect( pBundle, 5 );
	R_MANF_ISOV_NO_3_OP.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM7_CH0", 16 );
	L_MANF_ISOV_NO_4_CL_A.Connect( pBundle, 0 );
	RH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
	RH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 5 );
	RH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM7_CH2", 16 );
	L_RCS_OX_XFD_12_CL.Connect( pBundle, 0 );
	L_RCS_OX_XFD_12_OP.Connect( pBundle, 1 );
	R_MANF_ISOV_NO_4_CL_B.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM11_CH1", 16 );
	RCS_R_OXFU_XFD_VLV_12_OP.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM15_CH0", 16 );
	R_MANF_ISOV_NO_4_CL_A.Connect( pBundle, 1 );
	RH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 3 );
	RH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 4 );
	RH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM15_CH1", 16 );
	R_OMS_FU_TK_ISOV_B_OP.Connect( pBundle, 3 );
	R_OMS_FU_TK_ISOV_B_CL.Connect( pBundle, 4 );
	R_OMS_OX_TK_ISOV_B_OP.Connect( pBundle, 5 );
	R_OMS_OX_TK_ISOV_B_CL.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA3_IOM15_CH2", 16 );
	R_RCS_XFD_12_CL.Connect( pBundle, 0 );
	R_RCS_XFD_12_OP.Connect( pBundle, 1 );
	L_MANF_ISOV_NO_4_CL_B.Connect( pBundle, 8 );
	L_RCS_FU_XFD_12_CL.Connect( pBundle, 9 );
	L_RCS_FU_XFD_12_OP.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM7_CH2", 16 );
	L_RCS_XFD_12_CL.Connect( pBundle, 0 );
	L_RCS_XFD_12_OP.Connect( pBundle, 1 );
	L_MANF_ISOV_NO_4_OP.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM11_CH1", 16 );
	RCS_L_OXFU_XFD_VLV_12_OP.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM15_CH1", 16 );
	R_OMS_TK_V_B_OP.Connect( pBundle, 5 );
	R_OMS_TK_V_B_CL.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM15_CH2", 16 );
	R_RCS_OX_XFD_12_CL.Connect( pBundle, 0 );
	R_RCS_OX_XFD_12_OP.Connect( pBundle, 1 );
	R_MANF_ISOV_NO_4_OP.Connect( pBundle, 6 );
	R_RCS_FU_XFD_12_CL.Connect( pBundle, 9 );
	R_RCS_FU_XFD_12_OP.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH1", 16 );
	OPER_STATUS_1.Connect( pBundle, 2 );
	OPER_STATUS_2.Connect( pBundle, 3 );
	OPER_STATUS_3.Connect( pBundle, 4 );
	OPER_STATUS_4.Connect( pBundle, 5 );
	return;
}

void AMC3::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNC_RELAY_LOGIC_POWER = true;

	// VENT DOORS
	// right 8/9 motor 1
	bool K3 = MNC_RELAY_LOGIC_POWER && (RH_VENTS_8_9_MOTOR_1_OPEN_A.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_OPEN_1.IsSet( 26.0f ));// OPN A
	bool K4 = MNC_RELAY_LOGIC_POWER && (RH_VENTS_8_9_MOTOR_1_OPEN_B.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_OPEN_1.IsSet( 26.0f ));// OPN B
	bool K1 = MNC_RELAY_LOGIC_POWER && ((RH_VENTS_8_9_MOTOR_1_CLOSE_A.IsSet( 26.0f ) || (RH_VENTS_8_9_MOTOR_1_PURGE_A.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_PURGE_IND_1.IsSet( 26.0f ))) && !RH_VENTS_8_AND_9_CLOSE_1.IsSet( 26.0f ));// CLS A
	bool K2 = MNC_RELAY_LOGIC_POWER && ((RH_VENTS_8_9_MOTOR_1_CLOSE_B.IsSet( 26.0f ) || (RH_VENTS_8_9_MOTOR_1_PURGE_B.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_PURGE_IND_1.IsSet( 26.0f ))) && !RH_VENTS_8_AND_9_CLOSE_1.IsSet( 26.0f ));// CLS B

	if (K4 && K3)
	{
		if (K2 && K1) RH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( 0.0f );
		else RH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K2 && K1) RH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( -1.0f );
		else RH_VENTS_8_AND_9_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// ET UMBILICAL DOORS
	bool K9 = ET_DR_CLS_AND_LAT_ARM_3_FA3 || ET_DR_CLS_AND_LAT_ARM_3_FA2;
	// left drive motor 2
	bool K10 = ((L_DOOR_CL_2_FA1 || L_DOOR_CL_2_FA4) || ET_UMBILICAL_DOOR_LEFT_CLOSE) && !LEFT_DOOR_CLOSE_2 && (ET_UMBILICAL_DOOR_LEFT_CLOSE || K9);// CL
	bool K11 = ET_UMBILICAL_DOOR_LEFT_OPEN && !LEFT_DOOR_OPEN_2;// OP

	if (K10)
	{
		if (K11) LEFT_DOOR_MOTOR_2_PWR.SetLine( 0.0f );
		else LEFT_DOOR_MOTOR_2_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K11) LEFT_DOOR_MOTOR_2_PWR.SetLine( 1.0f );
		else LEFT_DOOR_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// cl latch 2 motor 2
	bool K5 = (CL_2_DEPLOY_A2_FA4 || CL_2_DEPLOY_A2_FA1) && !CL_LATCH_2_DEPLOY_2;// DPLY A
	bool K6 = (CL_2_DEPLOY_B2_FA3 || CL_2_DEPLOY_B2_FA2) && !CL_LATCH_2_DEPLOY_2;// DPLY B
	bool K7 = ((CL_2_STOW_A2_FA4 || CL_2_STOW_A2_FA1) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_2_STOW_2;// STW A
	bool K8 = ((CL_2_STOW_B2_FA3 || CL_2_STOW_B2_FA2) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_2_STOW_2;// STW B

	if (K7 && K8)
	{
		if (K5 && K6) CL_2_MOTOR_2_PWR.SetLine( 0.0f );
		else CL_2_MOTOR_2_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K5 && K6) CL_2_MOTOR_2_PWR.SetLine( 1.0f );
		else CL_2_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right drive motor 1
	bool K16 = ((R_DOOR_CL_1_FA1 || R_DOOR_CL_1_FA4) || ET_UMBILICAL_DOOR_RIGHT_CLOSE) && !RIGHT_DOOR_CLOSE_1 && (ET_UMBILICAL_DOOR_RIGHT_CLOSE || K9);// CL
	bool K17 = ET_UMBILICAL_DOOR_RIGHT_OPEN && !RIGHT_DOOR_OPEN_1;// OP

	if (K16)
	{
		if (K17) RIGHT_DOOR_MOTOR_1_PWR.SetLine( 0.0f );
		else RIGHT_DOOR_MOTOR_1_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K17) RIGHT_DOOR_MOTOR_1_PWR.SetLine( 1.0f );
		else RIGHT_DOOR_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// right latch motor 1
	bool K14 = ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE && !RIGHT_DOOR_LATCH_REL_1;// RLS A
	bool K15 = ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE && !RIGHT_DOOR_LATCH_REL_1;// RLS B
	bool K12 = (((R_LATCH_A1_FA3 || R_LATCH_A1_FA1) || ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH) && !RIGHT_DOOR_LATCH_LAT_1) && (ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH || K9);// LCH A
	bool K13 = (((R_LATCH_B1_FA2 || R_LATCH_B1_FA4) || ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH) && !RIGHT_DOOR_LATCH_LAT_1) && RIGHT_DOOR_RDY_TO_LCH_1;// LCH B

	if (K14 && K15)
	{
		if (K12 && K13) RIGHT_DOOR_LATCH_MOTOR_1_PWR.SetLine( 0.0f );
		else RIGHT_DOOR_LATCH_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K12 && K13) RIGHT_DOOR_LATCH_MOTOR_1_PWR.SetLine( -1.0f );
		else RIGHT_DOOR_LATCH_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// AFT RCS ISOLATION VALVES TANK 1/2
	bool K26 = (L_FU_TK_ISOV_12_CL_B.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN || L_FU_TK_ISO_V_12_CL_1);// CL B
	bool K27 = (L_FU_TK_ISOV_12_OP_B.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE || L_FU_TK_ISO_V_12_OP_1);// OP B
	bool K28 = (L_TK_ISOV_12_CL_A.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN || L_FU_TK_ISO_V_12_CL_1);// CL A
	bool K29 = (L_TK_ISOV_12_OP_A.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE || L_FU_TK_ISO_V_12_OP_2);// OP A
	
	if (K29) L_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K27) L_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K28)
		{
			if (K26) L_FU_TK_ISOL_12_MOTOR_PWR.SetLine( -1.0f );
			else L_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K30 = (L_TK_ISOV_12_OP_A.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE || L_OX_TK_ISO_V_12_OP_2);// OP A
	bool K31 = (L_OX_TK_ISOV_12_OP_B.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE || L_OX_TK_ISO_V_12_OP_1);// OP B
	bool K32 = (L_TK_ISOV_12_CL_A.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN || L_OX_TK_ISO_V_12_CL_1);// CL B
	bool K33 = (L_OX_TK_ISOV_12_CL_B.IsSet( 26.0f ) || AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN || L_OX_TK_ISO_V_12_CL_1);// CL A
	
	if (K30) L_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K31) L_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K33)
		{
			if (K32) L_OX_TK_ISOL_12_MOTOR_PWR.SetLine( -1.0f );
			else L_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_FU_TK_ISO_V_12_OP_2 && L_OX_TK_ISO_V_12_OP_2) AFT_LEFT_RCS_TANK_ISOLATION_12_TB_OPEN.SetLine();
	else AFT_LEFT_RCS_TANK_ISOLATION_12_TB_OPEN.ResetLine();
	if (L_FU_TK_ISO_V_12_CL_2 && L_OX_TK_ISO_V_12_CL_2) AFT_LEFT_RCS_TANK_ISOLATION_12_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_TANK_ISOLATION_12_TB_CLOSE.ResetLine();

	bool K34 = (R_FU_TK_ISOV_12_CL_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN || R_FU_TK_ISO_V_12_CL_1);// CL B
	bool K35 = (R_FU_TK_ISOV_12_OP_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE || R_FU_TK_ISO_V_12_OP_1);// OP B
	bool K36 = (R_TK_ISOV_12_CL_A.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN || R_FU_TK_ISO_V_12_CL_1);// CL A
	bool K37 = (R_TK_ISOV_12_OP_A.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE || R_FU_TK_ISO_V_12_OP_2);// OP A
	
	if (K37) R_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K35) R_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K36)
		{
			if (K34) R_FU_TK_ISOL_12_MOTOR_PWR.SetLine( -1.0f );
			else R_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K38 = (R_TK_ISOV_12_OP_A.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE || R_OX_TK_ISO_V_12_OP_2);// OP A
	bool K39 = (R_OX_TK_ISOV_12_OP_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE || R_OX_TK_ISO_V_12_OP_1);// OP B
	bool K40 = (R_OX_TK_ISOV_12_CL_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN || R_OX_TK_ISO_V_12_CL_1);// CL A
	bool K41 = (R_TK_ISOV_12_CL_A.IsSet( 26.0f ) || AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN || R_OX_TK_ISO_V_12_CL_1);// CL B
	
	if (K38) R_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K39) R_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K40)
		{
			if (K41) R_OX_TK_ISOL_12_MOTOR_PWR.SetLine( -1.0f );
			else R_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_FU_TK_ISO_V_12_OP_2 && R_OX_TK_ISO_V_12_OP_2) AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_OPEN.SetLine();
	else AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_OPEN.ResetLine();
	if (R_FU_TK_ISO_V_12_CL_2 && R_OX_TK_ISO_V_12_CL_2) AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_CLOSE.ResetLine();
	

	// AFT RCS ISOLATION VALVES MANIFOLD 3
	bool K18 = (L_MANF_ISOV_NO_3_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE || (L_FU_MANF_ISOV_3_OP && L_OX_MANF_ISOV_3_OP));// OP
	bool K19 = (L_MANF_ISOV_NO_3_CL_A.IsSet( 26.0f ) || L_MANF_ISOV_NO_3_CL_B.IsSet( 26.0f ) || AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN || (L_FU_MANF_ISOV_3_CL && L_OX_MANF_ISOV_3_CL));// CL
	
	if (K18)
	{
		if (K19)
		{
			L_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
			L_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			L_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 1.0f );
			L_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K19)
		{
			L_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( -1.0f );
			L_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			L_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
			L_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (L_FU_MANF_ISOV_3_OP && L_OX_MANF_ISOV_3_OP) AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.SetLine();
	else AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.ResetLine();
	if (L_FU_MANF_ISOV_3_CL && L_OX_MANF_ISOV_3_CL) AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.ResetLine();

	bool K20 = (R_MANF_ISOV_NO_3_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE || (R_FU_MANF_ISOV_3_OP && R_OX_MANF_ISOV_3_OP));// OP
	bool K21 = (R_MANF_ISOV_NO_3_CL_A.IsSet( 26.0f ) || R_MANF_ISOV_NO_3_CL_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN || (R_FU_MANF_ISOV_3_CL && R_OX_MANF_ISOV_3_CL));// CL
	
	if (K20)
	{
		if (K21)
		{
			R_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
			R_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			R_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 1.0f );
			R_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K21)
		{
			R_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( -1.0f );
			R_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			R_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
			R_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (R_FU_MANF_ISOV_3_OP && R_OX_MANF_ISOV_3_OP) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.SetLine();
	else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.ResetLine();
	if (R_FU_MANF_ISOV_3_CL && R_OX_MANF_ISOV_3_CL) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.ResetLine();
	

	// AFT RCS ISOLATION VALVES MANIFOLD 4
	bool K22 = (L_MANF_ISOV_NO_4_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE || (L_FU_MANF_ISOV_4_OP && L_OX_MANF_ISOV_4_OP));// OP
	bool K23 = (L_MANF_ISOV_NO_4_CL_A.IsSet( 26.0f ) || L_MANF_ISOV_NO_4_CL_B.IsSet( 26.0f ) || AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE) && !(AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN || (L_FU_MANF_ISOV_4_CL && L_OX_MANF_ISOV_4_CL));// CL
	
	if (K22)
	{
		if (K23)
		{
			L_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
			L_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			L_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 1.0f );
			L_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K23)
		{
			L_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( -1.0f );
			L_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			L_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
			L_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (L_FU_MANF_ISOV_4_OP && L_OX_MANF_ISOV_4_OP) AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.SetLine();
	else AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.ResetLine();
	if (L_FU_MANF_ISOV_4_CL && L_OX_MANF_ISOV_4_CL) AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.ResetLine();

	bool K24 = (R_MANF_ISOV_NO_4_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE || (R_FU_MANF_ISOV_4_OP && R_OX_MANF_ISOV_4_OP));// OP
	bool K25 = (R_MANF_ISOV_NO_4_CL_A.IsSet( 26.0f ) || R_MANF_ISOV_NO_4_CL_B.IsSet( 26.0f ) || AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE) && !(AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN || (R_FU_MANF_ISOV_4_CL && R_OX_MANF_ISOV_4_CL));// CL
	
	if (K24)
	{
		if (K25)
		{
			R_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
			R_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			R_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 1.0f );
			R_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K25)
		{
			R_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( -1.0f );
			R_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			R_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
			R_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (R_FU_MANF_ISOV_4_OP && R_OX_MANF_ISOV_4_OP) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.SetLine();
	else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.ResetLine();
	if (R_FU_MANF_ISOV_4_CL && R_OX_MANF_ISOV_4_CL) AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.ResetLine();

	
	// RCS XFEED MANIFOLD 1/2
	bool K46 = (L_RCS_XFD_12_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE || L_RCS_FU_XFD_12_OP_2);// OP A
	bool K47 = (L_RCS_FU_XFD_12_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE || L_RCS_FU_XFD_12_OP_1);// OP B
	bool K48 = (L_RCS_FU_XFD_12_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN || L_RCS_FU_XFD_12_CL_1);// CL A
	bool K49 = (L_RCS_XFD_12_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN || L_RCS_FU_XFD_12_CL_1);// CL B
	
	if (K47) L_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K46) L_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K49)
		{
			if (K48) L_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( -1.0f );
			else L_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K42 = (L_RCS_OX_XFD_12_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN || L_RCS_OX_XFD_12_CL_1);// CL B
	bool K43 = (L_RCS_OX_XFD_12_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE || L_RCS_OX_XFD_12_OP_1);// OP B
	bool K44 = (L_RCS_XFD_12_CL.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN || L_RCS_OX_XFD_12_CL_1);// CL A
	bool K45 = (L_RCS_XFD_12_OP.IsSet( 26.0f ) || AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE || L_RCS_OX_XFD_12_OP_2);// OP A
	
	if (K43) L_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K45) L_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K44)
		{
			if (K42) L_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( -1.0f );
			else L_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_RCS_FU_XFD_12_OP_2 && L_RCS_OX_XFD_12_OP_2)
	{
		AFT_LEFT_RCS_CROSSFEED_12_TB_OPEN.SetLine();
		RCS_L_OXFU_XFD_VLV_12_OP.SetLine( 28.0f );
	}
	else
	{
		AFT_LEFT_RCS_CROSSFEED_12_TB_OPEN.ResetLine();
		RCS_L_OXFU_XFD_VLV_12_OP.ResetLine();
	}
	if (L_RCS_FU_XFD_12_CL_2 && L_RCS_OX_XFD_12_CL_2) AFT_LEFT_RCS_CROSSFEED_12_TB_CLOSE.SetLine();
	else AFT_LEFT_RCS_CROSSFEED_12_TB_CLOSE.ResetLine();

	bool K54 = (R_RCS_XFD_12_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE || R_RCS_FU_XFD_12_OP_2);// OP A
	bool K55 = (R_RCS_FU_XFD_12_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE || R_RCS_FU_XFD_12_OP_1);// OP B
	bool K56 = (R_RCS_FU_XFD_12_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN || R_RCS_FU_XFD_12_CL_1);// CL A
	bool K57 = (R_RCS_XFD_12_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN || R_RCS_FU_XFD_12_CL_1);// CL B
	
	if (K55) R_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K54) R_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K57)
		{
			if (K56) R_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( -1.0f );
			else R_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_RCS_FU_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K50 = (R_RCS_OX_XFD_12_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN || R_RCS_OX_XFD_12_CL_1);// CL B
	bool K51 = (R_RCS_OX_XFD_12_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE || R_RCS_OX_XFD_12_OP_1);// OP B
	bool K52 = (R_RCS_XFD_12_CL.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN || R_RCS_OX_XFD_12_CL_1);// CL A
	bool K53 = (R_RCS_XFD_12_OP.IsSet( 26.0f ) || AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN) && !(AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE || R_RCS_OX_XFD_12_OP_2);// OP A
	
	if (K51) R_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else if (K53) R_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K52)
		{
			if (K50) R_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( -1.0f );
			else R_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_RCS_OX_XFD_V_12_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_RCS_FU_XFD_12_OP_2 && R_RCS_OX_XFD_12_OP_2)
	{
		AFT_RIGHT_RCS_CROSSFEED_12_TB_OPEN.SetLine();
		RCS_R_OXFU_XFD_VLV_12_OP.SetLine( 28.0f );
	}
	else
	{
		AFT_RIGHT_RCS_CROSSFEED_12_TB_OPEN.ResetLine();
		RCS_R_OXFU_XFD_VLV_12_OP.ResetLine();
	}
	if (R_RCS_FU_XFD_12_CL_2 && R_RCS_OX_XFD_12_CL_2) AFT_RIGHT_RCS_CROSSFEED_12_TB_CLOSE.SetLine();
	else AFT_RIGHT_RCS_CROSSFEED_12_TB_CLOSE.ResetLine();

	
	// RIGHT OMS XFEED
	bool K77 = (R_OMS_XFD_A_OP.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_OPEN) && !(RIGHT_OMS_CROSSFEED_A_SW_CLOSE || R_OMS_FU_XFD_V_A_OP_2);// OP A
	bool K76 = (R_OMS_XFD_A_CL.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_CLOSE) && !(RIGHT_OMS_CROSSFEED_A_SW_OPEN || R_OMS_FU_XFD_V_A_CL_1);// CL A
	bool K74 = (R_OMS_FU_XFD_V_A_CL.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_CLOSE) && !(RIGHT_OMS_CROSSFEED_A_SW_OPEN || R_OMS_FU_XFD_V_A_CL_1);// CL B
	bool K75 = (R_OMS_FU_XFD_V_A_OP.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_OPEN) && !(RIGHT_OMS_CROSSFEED_A_SW_CLOSE || R_OMS_FU_XFD_V_A_OP_1);// OP B
	
	if (K75) R_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K77) R_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K76)
		{
			if (K74) R_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( -1.0f );
			else R_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OMS_FU_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
	}
	
	bool K78 = (R_OMS_XFD_A_OP.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_OPEN) && !(RIGHT_OMS_CROSSFEED_A_SW_CLOSE || R_OMS_OX_XFD_V_A_OP_2);// OP A
	bool K79 = (R_OMS_OX_XFD_V_A_OP.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_OPEN) && !(RIGHT_OMS_CROSSFEED_A_SW_CLOSE || R_OMS_OX_XFD_V_A_OP_1);// OP B
	bool K80 = (R_OMS_OX_XFD_V_A_CL.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_CLOSE) && !(RIGHT_OMS_CROSSFEED_A_SW_OPEN || R_OMS_OX_XFD_V_A_CL_1);// CL A
	bool K81 = (R_OMS_XFD_A_CL.IsSet( 26.0f ) || RIGHT_OMS_CROSSFEED_A_SW_CLOSE) && !(RIGHT_OMS_CROSSFEED_A_SW_OPEN || R_OMS_OX_XFD_V_A_CL_1);// CL B

	if (K79) R_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else if (K78) R_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K81)
		{
			if (K80) R_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( -1.0f );
			else R_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OMS_OX_XFD_V_A_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_OMS_FU_XFD_V_A_OP_2 && R_OMS_OX_XFD_V_A_OP_2) RIGHT_OMS_CROSSFEED_A_TB_OPEN.SetLine();
	else RIGHT_OMS_CROSSFEED_A_TB_OPEN.ResetLine();
	if (R_OMS_FU_XFD_V_A_CL_2 && R_OMS_OX_XFD_V_A_CL_2) RIGHT_OMS_CROSSFEED_A_TB_CLOSE.SetLine();
	else RIGHT_OMS_CROSSFEED_A_TB_CLOSE.ResetLine();
	

	// OMS ISOLATION VALVES
	bool K66 = (L_OMS_TK_V_B_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE || L_OMS_FU_TK_ISOV_B_OP_2);// OP A
	bool K67 = (L_OMS_FU_TK_ISOV_B_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE || L_OMS_FU_TK_ISOV_B_OP_1);// OP B
	bool K68 = (L_OMS_TK_V_B_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_B_SW_OPEN || L_OMS_FU_TK_ISOV_B_CL_1);// CL A
	bool K69 = (L_OMS_FU_TK_ISOV_B_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_B_SW_OPEN || L_OMS_FU_TK_ISOV_B_CL_1);// CL B
	
	if (K66) L_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else if (K67) L_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K68)
		{
			if (K69) L_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( -1.0f );
			else L_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
	}
	
	bool K70 = (L_OMS_TK_V_B_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE || L_OMS_OX_TK_ISOV_B_OP_2);// OP A
	bool K71 = (L_OMS_OX_TK_ISOV_B_OP.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE || L_OMS_OX_TK_ISOV_B_OP_1);// OP B
	bool K72 = (L_OMS_OX_TK_ISOV_B_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_B_SW_OPEN || L_OMS_OX_TK_ISOV_B_CL_1);// CL A
	bool K73 = (L_OMS_TK_V_B_CL.IsSet( 26.0f ) || LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(LEFT_OMS_TANK_ISOLATION_B_SW_OPEN || L_OMS_OX_TK_ISOV_B_CL_1);// CL B
	
	if (K70) L_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else if (K71) L_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K73)
		{
			if (K72) L_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( -1.0f );
			else L_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
		}
		else L_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
	}

	if (L_OMS_FU_TK_ISOV_B_OP_2 && L_OMS_OX_TK_ISOV_B_OP_2) LEFT_OMS_TANK_ISOLATION_B_TB_OPEN.SetLine();
	else LEFT_OMS_TANK_ISOLATION_B_TB_OPEN.ResetLine();
	if (L_OMS_FU_TK_ISOV_B_CL_2 && L_OMS_OX_TK_ISOV_B_CL_2) LEFT_OMS_TANK_ISOLATION_B_TB_CLOSE.SetLine();
	else LEFT_OMS_TANK_ISOLATION_B_TB_CLOSE.ResetLine();

	bool K58 = (R_OMS_FU_TK_ISOV_B_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN || R_OMS_FU_TK_ISOV_B_CL_1);// CL B
	bool K59 = (R_OMS_FU_TK_ISOV_B_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE || R_OMS_FU_TK_ISOV_B_OP_1);// OP B
	bool K60 = (R_OMS_TK_V_B_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN || R_OMS_FU_TK_ISOV_B_CL_1);// CL A
	bool K61 = (R_OMS_TK_V_B_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE || R_OMS_FU_TK_ISOV_B_OP_2);// OP A
	
	if (K61) R_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else if (K59) R_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K60)
		{
			if (K58) R_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( -1.0f );
			else R_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OMS_FU_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
	}
	
	bool K62 = (R_OMS_TK_V_B_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE || R_OMS_OX_TK_ISOV_B_OP_2);// OP A
	bool K63 = (R_OMS_OX_TK_ISOV_B_OP.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE || R_OMS_OX_TK_ISOV_B_OP_1);// OP B
	bool K64 = (R_OMS_OX_TK_ISOV_B_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN || R_OMS_OX_TK_ISOV_B_CL_1);// CL B
	bool K65 = (R_OMS_TK_V_B_CL.IsSet( 26.0f ) || RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE) && !(RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN || R_OMS_OX_TK_ISOV_B_CL_1);// CL A
	
	if (K62) R_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else if (K63) R_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 1.0f );
	else
	{
		if (K65)
		{
			if (K64) R_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( -1.0f );
			else R_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
		}
		else R_OMS_OX_TK_ISOV_B_MOTOR_PWR.SetLine( 0.0f );
	}

	if (R_OMS_FU_TK_ISOV_B_OP_2 && R_OMS_OX_TK_ISOV_B_OP_2) RIGHT_OMS_TANK_ISOLATION_B_TB_OPEN.SetLine();
	else RIGHT_OMS_TANK_ISOLATION_B_TB_OPEN.ResetLine();
	if (R_OMS_FU_TK_ISOV_B_CL_2 && R_OMS_OX_TK_ISOV_B_CL_2) RIGHT_OMS_TANK_ISOLATION_B_TB_CLOSE.SetLine();
	else RIGHT_OMS_TANK_ISOLATION_B_TB_CLOSE.ResetLine();

	// oper status
	bool oper_status_1 = MNC_RELAY_LOGIC_POWER && !(K66 || K53 || K23 || K3 || K5 || K14 || K16 || K45 || K57 || K73 || K77 || K65 || K41 || K18 || K29 || K32 || K49 || K37 || K61 || K81);
	bool oper_status_2 = MNC_RELAY_LOGIC_POWER && !(K51 || K67 || K22 || K6 || K4 || K15 || K10 || K43 || K72 || K56 || K64 || K75 || K40 || K27 || K19 || K33 || K48 || K35 || K59 || K80);
	bool oper_status_3 = MNC_RELAY_LOGIC_POWER && !(K52 || K68 || K7 || K25 || K1 || K12 || K44 || K17 || K54 || K70 || K76 || K62 || K38 || K28 || K20 || K30 || K36 || K46 || K60 || K78);
	bool oper_status_4 = MNC_RELAY_LOGIC_POWER && !(K69 || K50 || K24 || K8 || K2 || K11 || K13 || K42 || K55 || K71 || K74 || K63 || K39 || K26 || K21 || K31 || K34 || K47 || K58 || K79);

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
