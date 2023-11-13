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
2023/11/12   GLS
********************************************/
#include "FMC2.h"


FMC2::FMC2( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "FMC2" )
{
}

FMC2::~FMC2()
{
}

void FMC2::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	//LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	//RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
	L_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	L_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	L_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	//LH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	//LH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	//LH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	//LH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
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
	R_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	R_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	R_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	//RH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	//RH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	//RH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	//RH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	//RH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	//RH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	//RH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	//RH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	//RH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	//RH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	//RH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	//RH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	//RH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "FRCS_MANF_12_ISOL", 12 );
	F_FU_MANF_ISOV_NO_2_MOTOR_PWR.Connect( pBundle, 6 );
	F_OX_MANF_ISOV_NO_2_MOTOR_PWR.Connect( pBundle, 7 );
	F_FU_MANF_ISOV_2_OP.Connect( pBundle, 8 );
	F_FU_MANF_ISOV_2_CL.Connect( pBundle, 9 );
	F_OX_MANF_ISOV_2_OP.Connect( pBundle, 10 );
	F_OX_MANF_ISOV_2_CL.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "FwdRCS_ManifIsol_SW", 16 );
	FWD_RCS_MANIFOLD_ISOLATION_2_SW_OPEN.Connect( pBundle, 2 );
	FWD_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "FwdRCS_ManifIsol_TB", 16 );
	FWD_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.Connect( pBundle, 2 );
	FWD_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "AIR_DATA_PROBES_FMC", 16 );
	//L_ADP_STOW_1.Connect( pBundle, 0 );
	L_ADP_STOW_2.Connect( pBundle, 1 );
	//L_ADP_DEPLOY_1.Connect( pBundle, 2 );
	L_ADP_DEPLOY_2.Connect( pBundle, 3 );
	//LEFT_PROBE_MOTOR_1_PWR.Connect( pBundle, 4 );
	LEFT_PROBE_MOTOR_2_PWR.Connect( pBundle, 5 );
	//R_ADP_STOW_1.Connect( pBundle, 6 );
	R_ADP_STOW_2.Connect( pBundle, 7 );
	//R_ADP_DEPLOY_1.Connect( pBundle, 8 );
	R_ADP_DEPLOY_2.Connect( pBundle, 9 );
	//RIGHT_PROBE_MOTOR_1_PWR.Connect( pBundle, 10 );
	RIGHT_PROBE_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "AIR_DATA_PROBES_POWER", 16 );
	AIR_DATA_PROBE_LEFT_DEPLOYHEAT.Connect( pBundle, 0 );
	AIR_DATA_PROBE_LEFT_DEPLOY.Connect( pBundle, 1 );
	AIR_DATA_PROBE_LEFT_STOW.Connect( pBundle, 2 );
	AIR_DATA_PROBE_STOW_LEFT_ENABLE.Connect( pBundle, 3 );
	AIR_DATA_PROBE_RIGHT_DEPLOYHEAT.Connect( pBundle, 4 );
	AIR_DATA_PROBE_RIGHT_DEPLOY.Connect( pBundle, 5 );
	AIR_DATA_PROBE_RIGHT_STOW.Connect( pBundle, 6 );
	AIR_DATA_PROBE_STOW_RIGHT_ENABLE.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "STAR_TRACKER_DOORS_FMC", 16 );
	//STAR_TRACKER_Y_DOOR_CLS_1.Connect( pBundle, 0 );
	STAR_TRACKER_Y_DOOR_CLS_2.Connect( pBundle, 1 );
	//STAR_TRACKER_Y_DOOR_OP_1.Connect( pBundle, 2 );
	STAR_TRACKER_Y_DOOR_OP_2.Connect( pBundle, 3 );
	//SYS_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	SYS_2_MOTOR_2_PWR.Connect( pBundle, 5 );
	//STAR_TRACKER_Z_DOOR_CLS_1.Connect( pBundle, 6 );
	STAR_TRACKER_Z_DOOR_CLS_2.Connect( pBundle, 7 );
	//STAR_TRACKER_Z_DOOR_OP_1.Connect( pBundle, 8 );
	STAR_TRACKER_Z_DOOR_OP_2.Connect( pBundle, 9 );
	SYS_1_MOTOR_2_PWR.Connect( pBundle, 10 );
	//SYS_2_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "STAR_TRACKER_POWER", 16 );
	STAR_TRACKER_POWER_Z.Connect( pBundle, 2 );
	STAR_TRACKER_POWER_Y.Connect( pBundle, 3 );
	STAR_TRACKER_DOOR_CONTROL_SYS_1_CLOSE.Connect( pBundle, 4 );// CLOSE
	STAR_TRACKER_DOOR_CONTROL_SYS_1_OPEN.Connect( pBundle, 5 );// OPEN
	STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE.Connect( pBundle, 6 );// CLOSE
	STAR_TRACKER_DOOR_CONTROL_SYS_2_OPEN.Connect( pBundle, 7 );// OPEN

	pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM2_CH0", 16 );
	LH_VENTS_1_2_MOTOR_2_CLOSE_B.Connect( pBundle, 0 );
	LH_VENTS_1_2_MOTOR_2_OPEN_B.Connect( pBundle, 1 );
	LH_VENTS_1_2_MOTOR_2_PURGE_B.Connect( pBundle, 2 );
	F_MANF_ISOV_NO_2_OP.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM10_CH0", 16 );
	LH_VENTS_1_2_MOTOR_2_CLOSE_A.Connect( pBundle, 0 );
	LH_VENTS_1_2_MOTOR_2_OPEN_A.Connect( pBundle, 1 );
	LH_VENTS_1_2_MOTOR_2_PURGE_A.Connect( pBundle, 2 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM2_CH0", 16 );
	RH_VENTS_1_2_MOTOR_2_OPEN_B.Connect( pBundle, 1 );
	RH_VENTS_1_2_MOTOR_2_PURGE_B.Connect( pBundle, 2 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM2_CH2", 16 );
	F_MANF_ISOV_NO_2_CL_A.Connect( pBundle, 4 );
	RH_VENTS_1_2_MOTOR_2_CLOSE_B.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM10_CH0", 16 );
	RH_VENTS_1_2_MOTOR_2_CLOSE_A.Connect( pBundle, 0 );
	RH_VENTS_1_2_MOTOR_2_OPEN_A.Connect( pBundle, 1 );
	F_MANF_ISOV_NO_2_CL_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF4_IOM10_CH2", 16 );
	RH_VENTS_1_2_MOTOR_2_PURGE_A.Connect( pBundle, 7 );

	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH1", 16 );
	OPER_STATUS_1.Connect( pBundle, 2 );
	OPER_STATUS_2.Connect( pBundle, 3 );
	OPER_STATUS_3.Connect( pBundle, 4 );
	OPER_STATUS_4.Connect( pBundle, 5 );
	return;
}

void FMC2::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNB_RELAY_LOGIC_POWER = true;

	// FWD RCS ISOL MANIF 2
	bool K1 = (F_MANF_ISOV_NO_2_OP.IsSet( 26.0f ) || FWD_RCS_MANIFOLD_ISOLATION_2_SW_OPEN) && !(FWD_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE || (F_FU_MANF_ISOV_2_OP && F_OX_MANF_ISOV_2_OP));// OP
	bool K2 = (F_MANF_ISOV_NO_2_CL_A.IsSet( 26.0f ) || F_MANF_ISOV_NO_2_CL_B.IsSet( 26.0f ) || FWD_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE) && !(FWD_RCS_MANIFOLD_ISOLATION_2_SW_OPEN || (F_FU_MANF_ISOV_2_CL && F_OX_MANF_ISOV_2_CL));// CL
	
	if (K1)
	{
		if (K2)
		{
			F_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
			F_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
		}
		else
		{
			F_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 1.0f );
			F_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 1.0f );
		}
	}
	else
	{
		if (K2)
		{
			F_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( -1.0f );
			F_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( -1.0f );
		}
		else
		{
			F_FU_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
			F_OX_MANF_ISOV_NO_2_MOTOR_PWR.SetLine( 0.0f );
		}
	}

	if (F_FU_MANF_ISOV_2_OP && F_OX_MANF_ISOV_2_OP) FWD_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.SetLine();
	else FWD_RCS_MANIFOLD_ISOLATION_2_TB_OPEN.ResetLine();
	if (F_FU_MANF_ISOV_2_CL && F_OX_MANF_ISOV_2_CL) FWD_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.SetLine();
	else FWD_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE.ResetLine();

	// VENT DOORS
	// left 1/2 motor 2
	bool K21 = MNB_RELAY_LOGIC_POWER && ((LH_VENTS_1_2_MOTOR_2_CLOSE_A.IsSet( 26.0f ) || (LH_VENTS_1_2_MOTOR_2_PURGE_A.IsSet( 26.0f ) && !L_VENTS_1_AND_2_PURGE_1_IND_2.IsSet( 26.0f ))) && !L_VENTS_1_AND_2_CLOSE_2.IsSet( 26.0f ));// CLS A
	bool K20 = MNB_RELAY_LOGIC_POWER && (LH_VENTS_1_2_MOTOR_2_OPEN_B.IsSet( 26.0f ) && !L_VENTS_1_AND_2_OPEN_2.IsSet( 26.0f ));// OPN B
	bool K22 = MNB_RELAY_LOGIC_POWER && ((LH_VENTS_1_2_MOTOR_2_CLOSE_B.IsSet( 26.0f ) || (LH_VENTS_1_2_MOTOR_2_PURGE_B.IsSet( 26.0f ) && !L_VENTS_1_AND_2_PURGE_1_IND_2.IsSet( 26.0f ))) && !L_VENTS_1_AND_2_CLOSE_2.IsSet( 26.0f ));// CLS B
	bool K19 = MNB_RELAY_LOGIC_POWER && (LH_VENTS_1_2_MOTOR_2_OPEN_A.IsSet( 26.0f ) && !L_VENTS_1_AND_2_OPEN_2.IsSet( 26.0f ));// OPN A

	if (K20 && K19)
	{
		if (K21 && K22) LH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( 0.0f );
		else LH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K21 && K22) LH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( -1.0f );
		else LH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right 1/2 motor 2
	bool K23 = MNB_RELAY_LOGIC_POWER && (RH_VENTS_1_2_MOTOR_2_OPEN_A.IsSet( 26.0f ) && !R_VENTS_1_AND_2_OPEN_2.IsSet( 26.0f ));// OPN A
	bool K25 = MNB_RELAY_LOGIC_POWER && ((RH_VENTS_1_2_MOTOR_2_CLOSE_A.IsSet( 26.0f ) || (RH_VENTS_1_2_MOTOR_2_PURGE_A.IsSet( 26.0f ) && !R_VENTS_1_AND_2_PURGE_1_IND_2.IsSet( 26.0f ))) && !R_VENTS_1_AND_2_CLOSE_2.IsSet( 26.0f ));// CLS A
	bool K24 = MNB_RELAY_LOGIC_POWER && (RH_VENTS_1_2_MOTOR_2_OPEN_B.IsSet( 26.0f ) && !R_VENTS_1_AND_2_OPEN_2.IsSet( 26.0f ));// OPN B
	bool K26 = MNB_RELAY_LOGIC_POWER && ((RH_VENTS_1_2_MOTOR_2_CLOSE_B.IsSet( 26.0f ) || (RH_VENTS_1_2_MOTOR_2_PURGE_B.IsSet( 26.0f ) && !R_VENTS_1_AND_2_PURGE_1_IND_2.IsSet( 26.0f ))) && !R_VENTS_1_AND_2_CLOSE_2.IsSet( 26.0f ));// CLS B

	if (K23 && K24)
	{
		if (K25 && K26) RH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( 0.0f );
		else RH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K25 && K26) RH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( -1.0f );
		else RH_VENTS_1_AND_2_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// AIR DATA
	// left probe motor 2
	bool K7 = MNB_RELAY_LOGIC_POWER && ((AIR_DATA_PROBE_LEFT_DEPLOY || AIR_DATA_PROBE_LEFT_DEPLOYHEAT) && !L_ADP_DEPLOY_2);// DPY A
	bool K8 = (AIR_DATA_PROBE_LEFT_DEPLOY || AIR_DATA_PROBE_LEFT_DEPLOYHEAT) && !L_ADP_DEPLOY_2;// DPY B
	bool K9 = MNB_RELAY_LOGIC_POWER && (AIR_DATA_PROBE_LEFT_STOW && !L_ADP_STOW_2);// STW A
	bool K10 = AIR_DATA_PROBE_STOW_LEFT_ENABLE && !L_ADP_STOW_2;// STW B

	if (K7 && K8)
	{
		if (K9 && K10) LEFT_PROBE_MOTOR_2_PWR.SetLine( 0.0f );
		else LEFT_PROBE_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K9 && K10) LEFT_PROBE_MOTOR_2_PWR.SetLine( -1.0f );
		else LEFT_PROBE_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right probe motor 2
	bool K11 = MNB_RELAY_LOGIC_POWER && ((AIR_DATA_PROBE_RIGHT_DEPLOY || AIR_DATA_PROBE_RIGHT_DEPLOYHEAT) && !R_ADP_DEPLOY_2);// DPY A
	bool K12 = (AIR_DATA_PROBE_RIGHT_DEPLOY || AIR_DATA_PROBE_RIGHT_DEPLOYHEAT) && !R_ADP_DEPLOY_2;// DPY B
	bool K13 = MNB_RELAY_LOGIC_POWER && (AIR_DATA_PROBE_RIGHT_STOW && !R_ADP_STOW_2);// STW A
	bool K14 = AIR_DATA_PROBE_STOW_RIGHT_ENABLE && !R_ADP_STOW_2;// STW B

	if (K11 && K12)
	{
		if (K13 && K14) RIGHT_PROBE_MOTOR_2_PWR.SetLine( 0.0f );
		else RIGHT_PROBE_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K13 && K14) RIGHT_PROBE_MOTOR_2_PWR.SetLine( -1.0f );
		else RIGHT_PROBE_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// STAR TRACKER
	// -z system 1 motor control
	bool K15 = MNB_RELAY_LOGIC_POWER && (STAR_TRACKER_POWER_Z && !STAR_TRACKER_Z_DOOR_OP_2);// OP
	bool K16 = STAR_TRACKER_DOOR_CONTROL_SYS_1_OPEN && !STAR_TRACKER_Z_DOOR_OP_2;// OP
	bool K17 = MNB_RELAY_LOGIC_POWER && (STAR_TRACKER_DOOR_CONTROL_SYS_1_CLOSE && !STAR_TRACKER_Z_DOOR_CLS_2);// CL
	bool K18 = STAR_TRACKER_DOOR_CONTROL_SYS_1_CLOSE && !STAR_TRACKER_Z_DOOR_CLS_2;// CL

	if (K15 && K16)
	{
		if (K17 && K18) SYS_1_MOTOR_2_PWR.SetLine( 0.0f );
		else SYS_1_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K17 && K18) SYS_1_MOTOR_2_PWR.SetLine( -1.0f );
		else SYS_1_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// -y system 2 motor control
	bool K3 = MNB_RELAY_LOGIC_POWER && (STAR_TRACKER_POWER_Y && !STAR_TRACKER_Y_DOOR_OP_2);// OP
	bool K4 = STAR_TRACKER_DOOR_CONTROL_SYS_2_OPEN && !STAR_TRACKER_Y_DOOR_OP_2;// OP
	bool K5 = MNB_RELAY_LOGIC_POWER && (STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE && !STAR_TRACKER_Y_DOOR_CLS_2);// CL
	bool K6 = STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE && !STAR_TRACKER_Y_DOOR_CLS_2;// CL

	if (K3 && K4)
	{
		if (K5 && K6) SYS_2_MOTOR_2_PWR.SetLine( 0.0f );
		else SYS_2_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K5 && K6) SYS_2_MOTOR_2_PWR.SetLine( -1.0f );
		else SYS_2_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// oper status
	bool oper_status_1 = MNB_RELAY_LOGIC_POWER && !(K2 || K14 || K7 || K3 || K17 || K21 || K23);
	bool oper_status_2 = MNB_RELAY_LOGIC_POWER && !(K11 || K10 || K6 || K16 || K20 || K25);
	bool oper_status_3 = MNB_RELAY_LOGIC_POWER && !(K1 || K13 || K8 || K4 || K18 || K22 || K24);
	bool oper_status_4 = MNB_RELAY_LOGIC_POWER && !(K12 || K9 || K5 || K15 || K19 || K26);

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
