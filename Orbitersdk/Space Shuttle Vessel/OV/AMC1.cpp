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
#include "AMC1.h"


AMC1::AMC1( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "AMC1" )
{
}

AMC1::~AMC1()
{
}

void AMC1::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_FMC", 16 );
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

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_FMC", 16 );
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
	return;
}

void AMC1::OnPreStep( double simt, double simdt, double mjd )
{
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
	return;
}
