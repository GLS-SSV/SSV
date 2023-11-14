/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/23   GLS
2022/01/25   GLS
2022/08/05   GLS
2023/07/23   GLS
2023/07/25   GLS
2023/11/12   GLS
********************************************/
#include "AMC2.h"


AMC2::AMC2( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "AMC2" )
{
}

AMC2::~AMC2()
{
}

void AMC2::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	//LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	//LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	//LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	//LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	//LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	//RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	//RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	//RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	//RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
	//L_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//L_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//L_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
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
	LH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	LH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	LH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
	//R_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	//R_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	//R_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
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
	RH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	RH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	RH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_AMC", 16 );
	//CL_LATCH_1_STOW_1.Connect( pBundle, 0 );
	CL_LATCH_1_STOW_2.Connect( pBundle, 1 );
	//CL_LATCH_1_DEPLOY_1.Connect( pBundle, 2 );
	CL_LATCH_1_DEPLOY_2.Connect( pBundle, 3 );
	//CL_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	CL_1_MOTOR_2_PWR.Connect( pBundle, 5 );
	//CL_LATCH_2_STOW_1.Connect( pBundle, 6 );
	//CL_LATCH_2_STOW_2.Connect( pBundle, 7 );
	//CL_LATCH_2_DEPLOY_1.Connect( pBundle, 8 );
	//CL_LATCH_2_DEPLOY_2.Connect( pBundle, 9 );
	//CL_2_MOTOR_1_PWR.Connect( pBundle, 10 );
	//CL_2_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_AMC", 16 );
	//LEFT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	//LEFT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	//LEFT_DOOR_OPEN_1.Connect( pBundle, 2 );
	//LEFT_DOOR_OPEN_2.Connect( pBundle, 3 );
	//LEFT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	//LEFT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	LEFT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	//LEFT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	//LEFT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	//LEFT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	LEFT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	//LEFT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	LEFT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	//LEFT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	LEFT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_RIGHT_AMC", 16 );
	//RIGHT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	RIGHT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	//RIGHT_DOOR_OPEN_1.Connect( pBundle, 2 );
	RIGHT_DOOR_OPEN_2.Connect( pBundle, 3 );
	//RIGHT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	//RIGHT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	RIGHT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	//RIGHT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	RIGHT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	//RIGHT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	RIGHT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	//RIGHT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	RIGHT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	//RIGHT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	RIGHT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_POWER", 16 );
	ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW.Connect( pBundle, 0 );
	//ET_UMBILICAL_DOOR_LEFT_CLOSE.Connect( pBundle, 1 );
	//ET_UMBILICAL_DOOR_LEFT_OPEN.Connect( pBundle, 2 );
	ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH.Connect( pBundle, 3 );
	ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE.Connect( pBundle, 4 );
	ET_UMBILICAL_DOOR_RIGHT_CLOSE.Connect( pBundle, 5 );
	ET_UMBILICAL_DOOR_RIGHT_OPEN.Connect( pBundle, 6 );
	ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH.Connect( pBundle, 7 );
	ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE.Connect( pBundle, 8 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM7_CH0", 16 );
	RH_VENTS_8_9_MOTOR_2_CLOSE_A.Connect( pBundle, 4 );
	RH_VENTS_8_9_MOTOR_2_OPEN_A.Connect( pBundle, 5 );
	RH_VENTS_8_9_MOTOR_2_PURGE_A.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA2_IOM15_CH0", 16 );
	RH_VENTS_8_9_MOTOR_2_CLOSE_B.Connect( pBundle, 3 );
	RH_VENTS_8_9_MOTOR_2_OPEN_B.Connect( pBundle, 4 );
	RH_VENTS_8_9_MOTOR_2_PURGE_B.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM7_CH0", 16 );
	LH_VENTS_8_9_MOTOR_2_CLOSE_A.Connect( pBundle, 4 );
	LH_VENTS_8_9_MOTOR_2_OPEN_A.Connect( pBundle, 5 );
	LH_VENTS_8_9_MOTOR_2_PURGE_A.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "MDM_FA4_IOM15_CH0", 16 );
	LH_VENTS_8_9_MOTOR_2_CLOSE_B.Connect( pBundle, 3 );
	LH_VENTS_8_9_MOTOR_2_OPEN_B.Connect( pBundle, 4 );
	LH_VENTS_8_9_MOTOR_2_PURGE_B.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
	OPER_STATUS_1.Connect( pBundle, 4 );
	OPER_STATUS_2.Connect( pBundle, 5 );
	OPER_STATUS_3.Connect( pBundle, 6 );
	OPER_STATUS_4.Connect( pBundle, 7 );
	return;
}

void AMC2::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNB_RELAY_LOGIC_POWER = true;

	// VENT DOORS
	// left 8/9 motor 2
	bool K7 = MNB_RELAY_LOGIC_POWER && ((LH_VENTS_8_9_MOTOR_2_CLOSE_A.IsSet( 26.0f ) || (LH_VENTS_8_9_MOTOR_2_PURGE_A.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_PURGE_IND_2.IsSet( 26.0f ))) && !LH_VENTS_8_AND_9_CLOSE_2.IsSet( 26.0f ));// CLS A
	bool K8 = MNB_RELAY_LOGIC_POWER && ((LH_VENTS_8_9_MOTOR_2_CLOSE_B.IsSet( 26.0f ) || (LH_VENTS_8_9_MOTOR_2_PURGE_B.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_PURGE_IND_2.IsSet( 26.0f ))) && !LH_VENTS_8_AND_9_CLOSE_2.IsSet( 26.0f ));// CLS B
	bool K5 = MNB_RELAY_LOGIC_POWER && (LH_VENTS_8_9_MOTOR_2_OPEN_A.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_OPEN_2.IsSet( 26.0f ));// OPN A
	bool K6 = MNB_RELAY_LOGIC_POWER && (LH_VENTS_8_9_MOTOR_2_OPEN_B.IsSet( 26.0f ) && !LH_VENTS_8_AND_9_OPEN_2.IsSet( 26.0f ));// OPN B

	if (K5 && K6)
	{
		if (K7 && K8) LH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( 0.0f );
		else LH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K7 && K8) LH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( -1.0f );
		else LH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right 8/9 motor 2
	bool K1 = MNB_RELAY_LOGIC_POWER && (RH_VENTS_8_9_MOTOR_2_OPEN_A.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_OPEN_2.IsSet( 26.0f ));// OPN A
	bool K2 = MNB_RELAY_LOGIC_POWER && (RH_VENTS_8_9_MOTOR_2_OPEN_B.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_OPEN_2.IsSet( 26.0f ));// OPN B
	bool K3 = MNB_RELAY_LOGIC_POWER && ((RH_VENTS_8_9_MOTOR_2_CLOSE_A.IsSet( 26.0f ) || (RH_VENTS_8_9_MOTOR_2_PURGE_A.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_PURGE_IND_2.IsSet( 26.0f ))) && !RH_VENTS_8_AND_9_CLOSE_2.IsSet( 26.0f ));// CLS A
	bool K4 = MNB_RELAY_LOGIC_POWER && ((RH_VENTS_8_9_MOTOR_2_CLOSE_B.IsSet( 26.0f ) || (RH_VENTS_8_9_MOTOR_2_PURGE_B.IsSet( 26.0f ) && !RH_VENTS_8_AND_9_PURGE_IND_2.IsSet( 26.0f ))) && !RH_VENTS_8_AND_9_CLOSE_2.IsSet( 26.0f ));// CLS B

	if (K1 && K2)
	{
		if (K3 && K4) RH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( 0.0f );
		else RH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K3 && K4) RH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( -1.0f );
		else RH_VENTS_8_AND_9_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// ET UMBILICAL DOORS
	bool K19 = ET_DR_CLS_AND_LAT_ARM_2_FA2 || ET_DR_CLS_AND_LAT_ARM_2_FA1;
	// left latch motor 2
	bool K58 = ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE && !LEFT_DOOR_LATCH_REL_2;// RLS A
	bool K59 = (((L_LATCH_B2_FA2 || L_LATCH_B2_FA3) || ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH) && !LEFT_DOOR_LATCH_LAT_2) && LEFT_DOOR_RDY_TO_LCH_3;// LCH B
	bool K56 = ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE && !LEFT_DOOR_LATCH_REL_2;// RLS B
	bool K57 = (((L_LATCH_A2_FA4 || L_LATCH_A2_FA1) || ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH) && !LEFT_DOOR_LATCH_LAT_2) && (ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH || K19);// LCH A

	if (K58 && K56)
	{
		if (K57 && K59) LEFT_DOOR_LATCH_MOTOR_2_PWR.SetLine( 0.0f );
		else LEFT_DOOR_LATCH_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K57 && K59) LEFT_DOOR_LATCH_MOTOR_2_PWR.SetLine( -1.0f );
		else LEFT_DOOR_LATCH_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// cl latch 1 motor 2
	bool K17 = (CL_1_DEPLOY_A2_FA4 || CL_1_DEPLOY_A2_FA1) && !CL_LATCH_1_DEPLOY_2;// DPLY A
	bool K18 = (CL_1_DEPLOY_B2_FA3 || CL_1_DEPLOY_B2_FA2) && !CL_LATCH_1_DEPLOY_2;// DPLY B
	bool K15 = ((CL_1_STOW_A2_FA4 || CL_1_STOW_A2_FA1) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_1_STOW_2;// STW A
	bool K16 = ((CL_1_STOW_B2_FA3 || CL_1_STOW_B2_FA2) || ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW) && !CL_LATCH_1_STOW_2;// STW B

	if (K15 && K16)
	{
		if (K17 && K18) CL_1_MOTOR_2_PWR.SetLine( 0.0f );
		else CL_1_MOTOR_2_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K17 && K18) CL_1_MOTOR_2_PWR.SetLine( 1.0f );
		else CL_1_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right drive motor 2
	bool K10 = ET_UMBILICAL_DOOR_RIGHT_OPEN && !RIGHT_DOOR_OPEN_2;// OP
	bool K9 = ((R_DOOR_CL_2_FA4 || R_DOOR_CL_2_FA3) || ET_UMBILICAL_DOOR_RIGHT_CLOSE) && !RIGHT_DOOR_CLOSE_2 && (ET_UMBILICAL_DOOR_RIGHT_CLOSE || K19);// CL

	if (K9)
	{
		if (K10) RIGHT_DOOR_MOTOR_2_PWR.SetLine( 0.0f );
		else RIGHT_DOOR_MOTOR_2_PWR.SetLine( -1.0f );
	}
	else
	{
		if (K10) RIGHT_DOOR_MOTOR_2_PWR.SetLine( 1.0f );
		else RIGHT_DOOR_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// right latch motor 2
	bool K13 = (((R_LATCH_A2_FA3 || R_LATCH_A2_FA1) || ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH) && !RIGHT_DOOR_LATCH_LAT_2) && (ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH || K19);// LCH A
	bool K14 = (((R_LATCH_B2_FA2 || R_LATCH_B2_FA4) || ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH) && !RIGHT_DOOR_LATCH_LAT_2) && RIGHT_DOOR_RDY_TO_LCH_3;// LCH B
	bool K11 = ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE && !RIGHT_DOOR_LATCH_REL_2;// RLS A
	bool K12 = ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE && !RIGHT_DOOR_LATCH_REL_2;// RLS B

	if (K11 && K12)
	{
		if (K13 && K14) RIGHT_DOOR_LATCH_MOTOR_2_PWR.SetLine( 0.0f );
		else RIGHT_DOOR_LATCH_MOTOR_2_PWR.SetLine( 1.0f );
	}
	else
	{
		if (K13 && K14) RIGHT_DOOR_LATCH_MOTOR_2_PWR.SetLine( -1.0f );
		else RIGHT_DOOR_LATCH_MOTOR_2_PWR.SetLine( 0.0f );
	}

	// oper status
	bool oper_status_1 = MNB_RELAY_LOGIC_POWER && !(/*K39 || K31 ||*/ K58 || /*K35 || K29 || K22 || K43 || K51 ||*/ K7 || K10 || K1 || /*K47 ||*/ K17 || /*K55 ||*/ K13);
	bool oper_status_2 = MNB_RELAY_LOGIC_POWER && !(/*K38 || K30 ||*/ K59 || /*K27 || K32 || K20 || K40 || K48 ||*/ K8 || K2 || /*K46 ||*/ K18 || /*K54 ||*/ K14);
	bool oper_status_3 = MNB_RELAY_LOGIC_POWER && !(/*K36 || K26 ||*/ K56 || /*K34 || K24 || K23 || K42 || K50 ||*/ K5 || K3 || K9 || /*K44 || K52 ||*/ K15 || K11);
	bool oper_status_4 = MNB_RELAY_LOGIC_POWER && !(/*K37 || K28 ||*/ K57 || /*K33 || K25 || K21 || K41 ||*/ K6 || /*K49 ||*/ K4 || /*K45 || K53 ||*/ K16 || K12);

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
