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

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1A", 16 );
	//RH_VENTS_1_2_MOTOR_1_OPEN_A.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_1_CLOSE_A.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_1_PURGE_A.Connect( pBundle, 2 );
	//RH_VENT_3_MOTOR_1_OPEN_A.Connect( pBundle, 3 );
	//RH_VENT_3_MOTOR_1_CLOSE_A.Connect( pBundle, 4 );
	//RH_VENTS_4_7_MOTOR_1_OPEN_A.Connect( pBundle, 5 );
	//RH_VENTS_4_7_MOTOR_1_CLOSE_A.Connect( pBundle, 6 );
	//RH_VENT_5_MOTOR_1_OPEN_A.Connect( pBundle, 7 );
	//RH_VENT_5_MOTOR_1_CLOSE_A.Connect( pBundle, 8 );
	//RH_VENT_6_MOTOR_1_OPEN_A.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_CLOSE_A.Connect( pBundle, 10 );
	//RH_VENT_6_MOTOR_1_PRG_1_A.Connect( pBundle, 11 );
	//RH_VENT_6_MOTOR_1_PRG_2_A.Connect( pBundle, 12 );
	RH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 13 );
	RH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 14 );
	RH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1B", 16 );
	//RH_VENTS_1_2_MOTOR_1_OPEN_B.Connect( pBundle, 0 );
	//RH_VENTS_1_2_MOTOR_1_CLOSE_B.Connect( pBundle, 1 );
	//RH_VENTS_1_2_MOTOR_1_PURGE_B.Connect( pBundle, 2 );
	//RH_VENT_3_MOTOR_1_OPEN_B.Connect( pBundle, 3 );
	//RH_VENT_3_MOTOR_1_CLOSE_B.Connect( pBundle, 4 );
	//RH_VENTS_4_7_MOTOR_1_OPEN_B.Connect( pBundle, 5 );
	//RH_VENTS_4_7_MOTOR_1_CLOSE_B.Connect( pBundle, 6 );
	//RH_VENT_5_MOTOR_1_OPEN_B.Connect( pBundle, 7 );
	//RH_VENT_5_MOTOR_1_CLOSE_B.Connect( pBundle, 8 );
	//RH_VENT_6_MOTOR_1_OPEN_B.Connect( pBundle, 9 );
	//RH_VENT_6_MOTOR_1_CLOSE_B.Connect( pBundle, 10 );
	//RH_VENT_6_MOTOR_1_PRG_1_B.Connect( pBundle, 11 );
	//RH_VENT_6_MOTOR_1_PRG_2_B.Connect( pBundle, 12 );
	RH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 13 );
	RH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 14 );
	RH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_FMC", 16 );
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

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_FMC", 16 );
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

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_RIGHT_FMC", 16 );
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

	pBundle = BundleManager()->CreateBundle( "AMC_STATUS", 16 );
	//OPER_STATUS_1.Connect( pBundle, 0 );// AMC 1 OPER STATUS 1
	//OPER_STATUS_2.Connect( pBundle, 1 );// AMC 1 OPER STATUS 2
	//OPER_STATUS_3.Connect( pBundle, 2 );// AMC 1 OPER STATUS 3
	//OPER_STATUS_4.Connect( pBundle, 3 );// AMC 1 OPER STATUS 4
	//OPER_STATUS_1.Connect( pBundle, 4 );// AMC 2 OPER STATUS 1
	//OPER_STATUS_2.Connect( pBundle, 5 );// AMC 2 OPER STATUS 2
	//OPER_STATUS_3.Connect( pBundle, 6 );// AMC 2 OPER STATUS 3
	//OPER_STATUS_4.Connect( pBundle, 7 );// AMC 2 OPER STATUS 4
	OPER_STATUS_1.Connect( pBundle, 8 );// AMC 3 OPER STATUS 1
	OPER_STATUS_2.Connect( pBundle, 9 );// AMC 3 OPER STATUS 2
	OPER_STATUS_3.Connect( pBundle, 10 );// AMC 3 OPER STATUS 3
	OPER_STATUS_4.Connect( pBundle, 11 );// AMC 3 OPER STATUS 4
	return;
}

void AMC3::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNC_RELAY_LOGIC_POWER = true;

	// VENT DOORS
	// right 8/9 motor 1
	bool K3 = MNC_RELAY_LOGIC_POWER && (RH_VENTS_8_9_MOTOR_1_OPEN_A && !RH_VENTS_8_AND_9_OPEN_1);// OPN A
	bool K4 = MNC_RELAY_LOGIC_POWER && (RH_VENTS_8_9_MOTOR_1_OPEN_B && !RH_VENTS_8_AND_9_OPEN_1);// OPN B
	bool K1 = MNC_RELAY_LOGIC_POWER && ((RH_VENTS_8_9_MOTOR_1_CLOSE_A || (RH_VENTS_8_9_MOTOR_1_PURGE_A && !RH_VENTS_8_AND_9_PURGE_IND_1)) && !RH_VENTS_8_AND_9_CLOSE_1);// CLS A
	bool K2 = MNC_RELAY_LOGIC_POWER && ((RH_VENTS_8_9_MOTOR_1_CLOSE_B || (RH_VENTS_8_9_MOTOR_1_PURGE_B && !RH_VENTS_8_AND_9_PURGE_IND_1)) && !RH_VENTS_8_AND_9_CLOSE_1);// CLS B

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

	// oper status
	bool oper_status_1 = MNC_RELAY_LOGIC_POWER && !(/*K66 || K53 || K23 ||*/ K3 || K5 || K14 || K16 /*|| K45 || K57 || K73 || K77 || K65 || K41 || K18 || K29 || K32 || K49 || K37 || K61 || K81*/);
	bool oper_status_2 = MNC_RELAY_LOGIC_POWER && !(/*K51 || K67 || K22 ||*/ K6 || K4 || K15 || K10 /*|| K43 || K72 || K56 || K64 || K75 || K40 || K27 || K19 || K33 || K48 || K35 || K59 || K80*/);
	bool oper_status_3 = MNC_RELAY_LOGIC_POWER && !(/*K52 || K68 ||*/ K7 /*|| K25*/ || K1 || K12 /*|| K44*/ || K17 /*|| K54 || K70 || K76 || K62 || K38 || K28 || K20 || K30 || K36 || K46 || K60 || K78*/);
	bool oper_status_4 = MNC_RELAY_LOGIC_POWER && !(/*K69 || K50 || K24 ||*/ K8 || K2 || K11 || K13 /*|| K42 || K55 || K71 || K74 || K63 || K39 || K26 || K21 || K31 || K34 || K47 || K58 || K79*/);

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
