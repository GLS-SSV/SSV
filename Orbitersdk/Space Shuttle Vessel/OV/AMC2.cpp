/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
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
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_FMC", 16 );
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

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_FMC", 16 );
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

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_RIGHT_FMC", 16 );
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
	return;
}

void AMC2::OnPreStep( double simt, double simdt, double mjd )
{
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
	return;
}
