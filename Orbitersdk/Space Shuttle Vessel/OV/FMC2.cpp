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
2022/08/05   GLS
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
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "FRCS_MANF_12_ISOL", 12 );
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

	pBundle = BundleManager()->CreateBundle( "FRCS_MANIFISOL_1234_VLV_CMD", 12 );
	F_MANF_ISOV_NO_2_OP.Connect( pBundle, 3 );// MANF_ISOV_NO_2_OP
	F_MANF_ISOV_NO_2_CL_A.Connect( pBundle, 4 );// MANF_ISOV_NO_2_CL_A
	F_MANF_ISOV_NO_2_CL_B.Connect( pBundle, 5 );// MANF_ISOV_NO_2_CL_B

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
	return;
}

void FMC2::OnPreStep( double simt, double simdt, double mjd )
{
	// FWD RCS ISOL MANIF 2
	bool K1 = (F_MANF_ISOV_NO_2_OP | FWD_RCS_MANIFOLD_ISOLATION_2_SW_OPEN) & !(FWD_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE | (F_FU_MANF_ISOV_2_OP & F_OX_MANF_ISOV_2_OP));// OP
	bool K2 = (F_MANF_ISOV_NO_2_CL_A | F_MANF_ISOV_NO_2_CL_B | FWD_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE) & !(FWD_RCS_MANIFOLD_ISOLATION_2_SW_OPEN | (F_FU_MANF_ISOV_2_CL & F_OX_MANF_ISOV_2_CL));// CL
	
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

	// VENTS DOORS
	// left 1/2 motor 2
	// right 1/2 motor 2

	// AIR DATA
	// left probe motor 2
	bool K7 = (AIR_DATA_PROBE_LEFT_DEPLOY || AIR_DATA_PROBE_LEFT_DEPLOYHEAT) && !L_ADP_DEPLOY_2;// DPY A
	bool K8 = (AIR_DATA_PROBE_LEFT_DEPLOY || AIR_DATA_PROBE_LEFT_DEPLOYHEAT) && !L_ADP_DEPLOY_2;// DPY B
	bool K9 = AIR_DATA_PROBE_LEFT_STOW && !L_ADP_STOW_2;// STW A
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
	bool K11 = (AIR_DATA_PROBE_RIGHT_DEPLOY || AIR_DATA_PROBE_RIGHT_DEPLOYHEAT) && !R_ADP_DEPLOY_2;// DPY A
	bool K12 = (AIR_DATA_PROBE_RIGHT_DEPLOY || AIR_DATA_PROBE_RIGHT_DEPLOYHEAT) && !R_ADP_DEPLOY_2;// DPY B
	bool K13 = AIR_DATA_PROBE_RIGHT_STOW && !R_ADP_STOW_2;// STW A
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
	bool K15 = STAR_TRACKER_POWER_Z && !STAR_TRACKER_Z_DOOR_OP_2;// OP
	bool K16 = STAR_TRACKER_DOOR_CONTROL_SYS_1_OPEN && !STAR_TRACKER_Z_DOOR_OP_2;// OP
	bool K17 = STAR_TRACKER_DOOR_CONTROL_SYS_1_CLOSE && !STAR_TRACKER_Z_DOOR_CLS_2;// CL
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
	bool K3 = STAR_TRACKER_POWER_Y && !STAR_TRACKER_Y_DOOR_OP_2;// OP
	bool K4 = STAR_TRACKER_DOOR_CONTROL_SYS_2_OPEN && !STAR_TRACKER_Y_DOOR_OP_2;// OP
	bool K5 = STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE && !STAR_TRACKER_Y_DOOR_CLS_2;// CL
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
	return;
}
