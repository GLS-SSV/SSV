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

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1A", 16 );
	//LH_VENTS_1_2_MOTOR_1_OPEN_A.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_1_CLOSE_A.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_1_PURGE_A.Connect( pBundle, 2 );
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
	LH_VENTS_8_9_MOTOR_1_OPEN_A.Connect( pBundle, 13 );
	LH_VENTS_8_9_MOTOR_1_CLOSE_A.Connect( pBundle, 14 );
	LH_VENTS_8_9_MOTOR_1_PURGE_A.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1B", 16 );
	//LH_VENTS_1_2_MOTOR_1_OPEN_B.Connect( pBundle, 0 );
	//LH_VENTS_1_2_MOTOR_1_CLOSE_B.Connect( pBundle, 1 );
	//LH_VENTS_1_2_MOTOR_1_PURGE_B.Connect( pBundle, 2 );
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
	LH_VENTS_8_9_MOTOR_1_OPEN_B.Connect( pBundle, 13 );
	LH_VENTS_8_9_MOTOR_1_CLOSE_B.Connect( pBundle, 14 );
	LH_VENTS_8_9_MOTOR_1_PURGE_B.Connect( pBundle, 15 );

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

	pBundle = BundleManager()->CreateBundle( "AMC_STATUS", 16 );
	OPER_STATUS_1.Connect( pBundle, 0 );// AMC 1 OPER STATUS 1
	OPER_STATUS_2.Connect( pBundle, 1 );// AMC 1 OPER STATUS 2
	OPER_STATUS_3.Connect( pBundle, 2 );// AMC 1 OPER STATUS 3
	OPER_STATUS_4.Connect( pBundle, 3 );// AMC 1 OPER STATUS 4
	//OPER_STATUS_1.Connect( pBundle, 4 );// AMC 2 OPER STATUS 1
	//OPER_STATUS_2.Connect( pBundle, 5 );// AMC 2 OPER STATUS 2
	//OPER_STATUS_3.Connect( pBundle, 6 );// AMC 2 OPER STATUS 3
	//OPER_STATUS_4.Connect( pBundle, 7 );// AMC 2 OPER STATUS 4
	//OPER_STATUS_1.Connect( pBundle, 8 );// AMC 3 OPER STATUS 1
	//OPER_STATUS_2.Connect( pBundle, 9 );// AMC 3 OPER STATUS 2
	//OPER_STATUS_3.Connect( pBundle, 10 );// AMC 3 OPER STATUS 3
	//OPER_STATUS_4.Connect( pBundle, 11 );// AMC 3 OPER STATUS 4
	return;
}

void AMC1::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO switch input
	bool MNA_RELAY_LOGIC_POWER = true;

	// VENT DOORS
	// left 8/9 motor 1
	bool K4 = MNA_RELAY_LOGIC_POWER && (LH_VENTS_8_9_MOTOR_1_OPEN_A && !LH_VENTS_8_AND_9_OPEN_1);// OPN A
	bool K3 = MNA_RELAY_LOGIC_POWER && (LH_VENTS_8_9_MOTOR_1_OPEN_B && !LH_VENTS_8_AND_9_OPEN_1);// OPN B
	bool K2 = MNA_RELAY_LOGIC_POWER && ((LH_VENTS_8_9_MOTOR_1_CLOSE_A || (LH_VENTS_8_9_MOTOR_1_PURGE_A && !LH_VENTS_8_AND_9_PURGE_IND_1)) && !LH_VENTS_8_AND_9_CLOSE_1);// CLS A
	bool K1 = MNA_RELAY_LOGIC_POWER && ((LH_VENTS_8_9_MOTOR_1_CLOSE_B || (LH_VENTS_8_9_MOTOR_1_PURGE_B && !LH_VENTS_8_AND_9_PURGE_IND_1)) && !LH_VENTS_8_AND_9_CLOSE_1);// CLS B

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

	// oper status
	bool oper_status_1 = MNA_RELAY_LOGIC_POWER && !(/*K62 || K36 || K22 ||*/ K20 || /*K38 || K54 || K66 || K46 || K52 || K60 || K44 || K25 ||*/ K4 || K16 || K11 || K8 /*|| K30 || K71*/);
	bool oper_status_2 = MNA_RELAY_LOGIC_POWER && !(/*K61 || K21 || K35 ||*/ K19 || /*K37 || K53 || K68 || K45 || K51 || K26 || K43 ||*/ K3 || K7 || K10 /*|| K29 || K59 || K69*/);
	bool oper_status_3 = MNA_RELAY_LOGIC_POWER && !(/*K64 || K34 ||*/ K18 || /*K27 || K32 || K40 || K56 || K48 || K72 || K50 || K42 ||*/ K2 || K15 || K6 || K13 /*|| K24 || K58 || K67*/);
	bool oper_status_4 = MNA_RELAY_LOGIC_POWER && !(/*K63 || K33 ||*/ K17 || /*K28 || K31 || K39 || K55 || K47 || K70 || K65 || K49 || K57 || K23 || K41 ||*/ K12 || K5 || K1);

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
