/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2021/05/30   GLS
2021/06/01   GLS
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
********************************************/
#include "FMC3.h"


FMC3::FMC3( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "FMC3" )
{
}

FMC3::~FMC3()
{
}

void FMC3::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
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
	//RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
	L_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	L_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	L_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
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
	//LH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	//LH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	//LH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1A", 16 );
	LH_VENTS_1_2_MOTOR_1_OPEN_A.Connect( pBundle, 0 );
	LH_VENTS_1_2_MOTOR_1_CLOSE_A.Connect( pBundle, 1 );
	LH_VENTS_1_2_MOTOR_1_PURGE_A.Connect( pBundle, 2 );
	//LH_VENT_3_MOTOR_1_OPEN_A.Connect( pBundle, 3 );
	//LH_VENT_3_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
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
	LH_VENTS_1_2_MOTOR_1_OPEN_B.Connect( pBundle, 0 );
	LH_VENTS_1_2_MOTOR_1_CLOSE_B.Connect( pBundle, 1 );
	LH_VENTS_1_2_MOTOR_1_PURGE_B.Connect( pBundle, 2 );
	//LH_VENT_3_MOTOR_1_OPEN_B.Connect( pBundle, 3 );
	//LH_VENT_3_MOTOR_1_CLOSE_B.Connect( pBundle, 4 );
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

	pBundle = BundleManager()->CreateBundle( "FRCS_TANK_ISOL", 12 );
	F_FU_TK_ISOL_12_MOTOR_PWR.Connect( pBundle, 0 );
	F_OX_TK_ISOL_12_MOTOR_PWR.Connect( pBundle, 1 );
	F_FU_TK_ISOV_12_OP.Connect( pBundle, 2 );
	F_FU_TK_ISOV_12_CL.Connect( pBundle, 3 );
	F_OX_TK_ISOV_12_OP.Connect( pBundle, 4 );
	F_OX_TK_ISOV_12_CL.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "FRCS_MANF_34_ISOL", 12 );
	F_FU_MANF_ISOV_NO_3_MOTOR_PWR.Connect( pBundle, 0 );
	F_OX_MANF_ISOV_NO_3_MOTOR_PWR.Connect( pBundle, 1 );
	F_FU_MANF_ISOV_3_OP.Connect( pBundle, 2 );
	F_FU_MANF_ISOV_3_CL.Connect( pBundle, 3 );
	F_OX_MANF_ISOV_3_OP.Connect( pBundle, 4 );
	F_OX_MANF_ISOV_3_CL.Connect( pBundle, 5 );
	F_FU_MANF_ISOV_NO_4_MOTOR_PWR.Connect( pBundle, 6 );
	F_OX_MANF_ISOV_NO_4_MOTOR_PWR.Connect( pBundle, 7 );
	F_FU_MANF_ISOV_4_OP.Connect( pBundle, 8 );
	F_FU_MANF_ISOV_4_CL.Connect( pBundle, 9 );
	F_OX_MANF_ISOV_4_OP.Connect( pBundle, 10 );
	F_OX_MANF_ISOV_4_CL.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "FwdRCS_HePress_TankIsol_TB", 16 );
	FWD_RCS_TANK_ISOLATION_12_TB_OPEN.Connect( pBundle, 4 );
	FWD_RCS_TANK_ISOLATION_12_TB_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "FwdRCS_HePress_TankIsol_SW", 16 );
	FWD_RCS_TANK_ISOLATION_12_SW_OPEN.Connect( pBundle, 4 );
	FWD_RCS_TANK_ISOLATION_12_SW_CLOSE.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "FwdRCS_ManifIsol_SW", 16 );
	FWD_RCS_MANIFOLD_ISOLATION_3_SW_OPEN.Connect( pBundle, 4 );
	FWD_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE.Connect( pBundle, 5 );
	FWD_RCS_MANIFOLD_ISOLATION_4_SW_OPEN.Connect( pBundle, 6 );
	FWD_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "FwdRCS_ManifIsol_TB", 16 );
	FWD_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.Connect( pBundle, 4 );
	FWD_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.Connect( pBundle, 5 );
	FWD_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.Connect( pBundle, 6 );
	FWD_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "FRCS_HEISOL_TANKISOL_VLV_CMD", 14 );
	F_FU_TK_ISOV_12_OP_A.Connect( pBundle, 4 );// F_FU_TK_ISOV_12_OP_A
	F_FU_TK_ISOV_12_CL_B.Connect( pBundle, 5 );// F_FU_TK_ISOV_12_CL_B
	F_OX_TK_ISOV_12_OP_A.Connect( pBundle, 6 );// F_OX_TK_ISOV_12_OP_A
	F_OX_TK_ISOV_12_CL_B.Connect( pBundle, 7 );// F_OX_TK_ISOV_12_CL_B
	F_TK_ISOV_12_CL_A.Connect( pBundle, 8 );// F_TK_ISOV_12_CL_A

	pBundle = BundleManager()->CreateBundle( "FRCS_MANIFISOL_1234_VLV_CMD", 12 );
	F_MANF_ISOV_NO_3_OP.Connect( pBundle, 6 );// MANF_ISOV_NO_3_OP
	F_MANF_ISOV_NO_3_CL_A.Connect( pBundle, 7 );// MANF_ISOV_NO_3_CL_A
	F_MANF_ISOV_NO_3_CL_B.Connect( pBundle, 8 );// MANF_ISOV_NO_3_CL_B
	F_MANF_ISOV_NO_4_OP.Connect( pBundle, 9 );// MANF_ISOV_NO_4_OP
	F_MANF_ISOV_NO_4_CL_A.Connect( pBundle, 10 );// MANF_ISOV_NO_4_CL_A
	F_MANF_ISOV_NO_4_CL_B.Connect( pBundle, 11 );// MANF_ISOV_NO_4_CL_B

	pBundle = BundleManager()->CreateBundle( "AIR_DATA_PROBES_FMC", 16 );
	//L_ADP_STOW_1.Connect( pBundle, 0 );
	//L_ADP_STOW_2.Connect( pBundle, 1 );
	//L_ADP_DEPLOY_1.Connect( pBundle, 2 );
	//L_ADP_DEPLOY_2.Connect( pBundle, 3 );
	//LEFT_PROBE_MOTOR_1_PWR.Connect( pBundle, 4 );
	//LEFT_PROBE_MOTOR_2_PWR.Connect( pBundle, 5 );
	R_ADP_STOW_1.Connect( pBundle, 6 );
	//R_ADP_STOW_2.Connect( pBundle, 7 );
	R_ADP_DEPLOY_1.Connect( pBundle, 8 );
	//R_ADP_DEPLOY_2.Connect( pBundle, 9 );
	RIGHT_PROBE_MOTOR_1_PWR.Connect( pBundle, 10 );
	//RIGHT_PROBE_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "AIR_DATA_PROBES_POWER", 16 );
	//AIR_DATA_PROBE_LEFT_DEPLOYHEAT.Connect( pBundle, 0 );
	//AIR_DATA_PROBE_LEFT_DEPLOY.Connect( pBundle, 1 );
	//AIR_DATA_PROBE_LEFT_STOW.Connect( pBundle, 2 );
	//AIR_DATA_PROBE_STOW_LEFT_ENABLE.Connect( pBundle, 3 );
	AIR_DATA_PROBE_RIGHT_DEPLOYHEAT.Connect( pBundle, 4 );
	AIR_DATA_PROBE_RIGHT_DEPLOY.Connect( pBundle, 5 );
	AIR_DATA_PROBE_RIGHT_STOW.Connect( pBundle, 6 );
	AIR_DATA_PROBE_STOW_RIGHT_ENABLE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "STAR_TRACKER_DOORS_FMC", 16 );
	//STAR_TRACKER_Y_DOOR_CLS_1.Connect( pBundle, 0 );
	//STAR_TRACKER_Y_DOOR_CLS_2.Connect( pBundle, 1 );
	//STAR_TRACKER_Y_DOOR_OP_1.Connect( pBundle, 2 );
	//STAR_TRACKER_Y_DOOR_OP_2.Connect( pBundle, 3 );
	//SYS_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	//SYS_2_MOTOR_2_PWR.Connect( pBundle, 5 );
	STAR_TRACKER_Z_DOOR_CLS_1.Connect( pBundle, 6 );
	//STAR_TRACKER_Z_DOOR_CLS_2.Connect( pBundle, 7 );
	STAR_TRACKER_Z_DOOR_OP_1.Connect( pBundle, 8 );
	//STAR_TRACKER_Z_DOOR_OP_2.Connect( pBundle, 9 );
	//SYS_1_MOTOR_2_PWR.Connect( pBundle, 10 );
	SYS_2_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "STAR_TRACKER_POWER", 16 );
	STAR_TRACKER_POWER_Z.Connect( pBundle, 2 );
	STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE.Connect( pBundle, 6 );// CLOSE
	STAR_TRACKER_DOOR_CONTROL_SYS_2_OPEN.Connect( pBundle, 7 );// OPEN

	pBundle = BundleManager()->CreateBundle( "MDM_OF3_IOM6_CH0", 16 );
	OPER_STATUS_1.Connect( pBundle, 0 );
	OPER_STATUS_2.Connect( pBundle, 1 );
	OPER_STATUS_3.Connect( pBundle, 2 );
	OPER_STATUS_4.Connect( pBundle, 3 );
	return;
}

void FMC3::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNC_RELAY_LOGIC_POWER = true;

	// FWD RCS ISOLATION VALVES TANK 1/2
	bool K1 = (F_FU_TK_ISOV_12_OP_A || FWD_RCS_TANK_ISOLATION_12_SW_OPEN) && !(FWD_RCS_TANK_ISOLATION_12_SW_CLOSE || F_FU_TK_ISOV_12_OP);// OP
	bool K2 = (F_TK_ISOV_12_CL_A || FWD_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(FWD_RCS_TANK_ISOLATION_12_SW_OPEN || F_FU_TK_ISOV_12_CL);// CL A
	bool K3 = (F_FU_TK_ISOV_12_CL_B || FWD_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(FWD_RCS_TANK_ISOLATION_12_SW_OPEN || F_FU_TK_ISOV_12_CL);// CL B
	
	if (K1)
	{
		if (K3) F_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		else F_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K2)
		{
			if (K3) F_FU_TK_ISOL_12_MOTOR_PWR.SetLine( -1.0f );
			else F_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else F_FU_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
	}

	bool K4 = (F_OX_TK_ISOV_12_OP_A || FWD_RCS_TANK_ISOLATION_12_SW_OPEN) && !(FWD_RCS_TANK_ISOLATION_12_SW_CLOSE || F_OX_TK_ISOV_12_OP);// OP
	bool K5 = (F_TK_ISOV_12_CL_A || FWD_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(FWD_RCS_TANK_ISOLATION_12_SW_OPEN || F_OX_TK_ISOV_12_CL);// CL A
	bool K6 = (F_OX_TK_ISOV_12_CL_B || FWD_RCS_TANK_ISOLATION_12_SW_CLOSE) && !(FWD_RCS_TANK_ISOLATION_12_SW_OPEN || F_OX_TK_ISOV_12_CL);// CL B
	
	if (K4)
	{
		if (K6) F_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		else F_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K5)
		{
			if (K6) F_OX_TK_ISOL_12_MOTOR_PWR.SetLine( -1.0f );
			else F_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
		}
		else F_OX_TK_ISOL_12_MOTOR_PWR.SetLine( 0.0f );
	}

	if (F_FU_TK_ISOV_12_OP && F_OX_TK_ISOV_12_OP) FWD_RCS_TANK_ISOLATION_12_TB_OPEN.SetLine();
	else FWD_RCS_TANK_ISOLATION_12_TB_OPEN.ResetLine();
	if (F_FU_TK_ISOV_12_CL && F_OX_TK_ISOV_12_CL) FWD_RCS_TANK_ISOLATION_12_TB_CLOSE.SetLine();
	else FWD_RCS_TANK_ISOLATION_12_TB_CLOSE.ResetLine();

	
	// FWD RCS ISOLATION VALVES MANF 3
	bool K7 = (F_MANF_ISOV_NO_3_OP || FWD_RCS_MANIFOLD_ISOLATION_3_SW_OPEN) && !(FWD_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE || (F_FU_MANF_ISOV_3_OP && F_OX_MANF_ISOV_3_OP));// OP
	bool K8 = (F_MANF_ISOV_NO_3_CL_A || F_MANF_ISOV_NO_3_CL_B || FWD_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE) && !(FWD_RCS_MANIFOLD_ISOLATION_3_SW_OPEN || (F_FU_MANF_ISOV_3_CL && F_OX_MANF_ISOV_3_CL));// CL
	
	if (K7)
	{
		if (K8)
		{
			F_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
			F_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			F_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 1.0f );
			F_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K8)
		{
			F_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( -1.0f );
			F_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			F_FU_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
			F_OX_MANF_ISOV_NO_3_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (F_FU_MANF_ISOV_3_OP && F_OX_MANF_ISOV_3_OP) FWD_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.SetLine();
	else FWD_RCS_MANIFOLD_ISOLATION_3_TB_OPEN.ResetLine();
	if (F_FU_MANF_ISOV_3_CL && F_OX_MANF_ISOV_3_CL) FWD_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.SetLine();
	else FWD_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE.ResetLine();

	
	// FWD RCS ISOLATION VALVES MANF 4
	bool K9 = (F_MANF_ISOV_NO_4_OP || FWD_RCS_MANIFOLD_ISOLATION_4_SW_OPEN) && !(FWD_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE || (F_FU_MANF_ISOV_4_OP && F_OX_MANF_ISOV_4_OP));// OP
	bool K10 = (F_MANF_ISOV_NO_4_CL_A || F_MANF_ISOV_NO_4_CL_B || FWD_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE) && !(FWD_RCS_MANIFOLD_ISOLATION_4_SW_OPEN || (F_FU_MANF_ISOV_4_CL && F_OX_MANF_ISOV_4_CL));// CL
	
	if (K9)
	{
		if (K10)
		{
			F_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
			F_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			F_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 1.0f );
			F_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K10)
		{
			F_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( -1.0f );
			F_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			F_FU_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
			F_OX_MANF_ISOV_NO_4_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (F_FU_MANF_ISOV_4_OP && F_OX_MANF_ISOV_4_OP) FWD_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.SetLine();
	else FWD_RCS_MANIFOLD_ISOLATION_4_TB_OPEN.ResetLine();
	if (F_FU_MANF_ISOV_4_CL && F_OX_MANF_ISOV_4_CL) FWD_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.SetLine();
	else FWD_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE.ResetLine();

	// VENT DOORS
	// left 1/2 motor 1
	bool K19 = MNC_RELAY_LOGIC_POWER && (LH_VENTS_1_2_MOTOR_1_OPEN_A && !L_VENTS_1_AND_2_OPEN_1);// OPN A
	bool K20 = MNC_RELAY_LOGIC_POWER && (LH_VENTS_1_2_MOTOR_1_OPEN_B && !L_VENTS_1_AND_2_OPEN_1);// OPN B
	bool K21 = MNC_RELAY_LOGIC_POWER && ((LH_VENTS_1_2_MOTOR_1_CLOSE_A || (LH_VENTS_1_2_MOTOR_1_PURGE_A && !L_VENTS_1_AND_2_PURGE_1_IND_1)) && !L_VENTS_1_AND_2_CLOSE_1);// CLS A
	bool K22 = (MNC_RELAY_LOGIC_POWER && (LH_VENTS_1_2_MOTOR_1_CLOSE_B || (LH_VENTS_1_2_MOTOR_1_PURGE_B && !L_VENTS_1_AND_2_PURGE_1_IND_1)) && !L_VENTS_1_AND_2_CLOSE_1);// CLS B

	if (K20 && K19)
	{
		if (K21 && K22) LH_VENTS_1_AND_2_MOTOR_1_PWR.SetLine( 0.0f );
		else LH_VENTS_1_AND_2_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K21 && K22) LH_VENTS_1_AND_2_MOTOR_1_PWR.SetLine( -1.0f );
		else LH_VENTS_1_AND_2_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// AIR DATA
	// right probe motor 1
	bool K11 = MNC_RELAY_LOGIC_POWER && ((AIR_DATA_PROBE_RIGHT_DEPLOY || AIR_DATA_PROBE_RIGHT_DEPLOYHEAT) && !R_ADP_DEPLOY_1);// DPY A
	bool K12 = (AIR_DATA_PROBE_RIGHT_DEPLOY || AIR_DATA_PROBE_RIGHT_DEPLOYHEAT) && !R_ADP_DEPLOY_1;// DPY B
	bool K13 = MNC_RELAY_LOGIC_POWER && (AIR_DATA_PROBE_RIGHT_STOW && !R_ADP_STOW_1);// STW A
	bool K14 = AIR_DATA_PROBE_STOW_RIGHT_ENABLE && !R_ADP_STOW_1;// STW B

	if (K11 && K12)
	{
		if (K13 && K14) RIGHT_PROBE_MOTOR_1_PWR.SetLine( 0.0f );
		else RIGHT_PROBE_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K13 && K14) RIGHT_PROBE_MOTOR_1_PWR.SetLine( -1.0f );
		else RIGHT_PROBE_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// STAR TRACKER
	// -z system 2 motor control
	bool K15 = MNC_RELAY_LOGIC_POWER && (STAR_TRACKER_POWER_Z && !STAR_TRACKER_Z_DOOR_OP_1);// OP
	bool K16 = STAR_TRACKER_DOOR_CONTROL_SYS_2_OPEN && !STAR_TRACKER_Z_DOOR_OP_1;// OP
	bool K17 = MNC_RELAY_LOGIC_POWER && (STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE && !STAR_TRACKER_Z_DOOR_CLS_1);// CL
	bool K18 = STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE && !STAR_TRACKER_Z_DOOR_CLS_1;// CL

	if (K15 && K16)
	{
		if (K17 && K18) SYS_2_MOTOR_1_PWR.SetLine( 0.0f );
		else SYS_2_MOTOR_1_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K17 && K18) SYS_2_MOTOR_1_PWR.SetLine( -1.0f );
		else SYS_2_MOTOR_1_PWR.SetLine( 0.0f );
	}

	// oper status
	bool oper_status_1 = MNC_RELAY_LOGIC_POWER && !(K4 || K5 || K9 || K11 || K15 || K19);
	bool oper_status_2 = MNC_RELAY_LOGIC_POWER && !(K1 || K2 || K7 || K12 || K16 || K20);
	bool oper_status_3 = MNC_RELAY_LOGIC_POWER && !(K6 || K10 || K13 || K17 || K21);
	bool oper_status_4 = MNC_RELAY_LOGIC_POWER && !(K3 || K8 || K14 || K18 || K22);

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
