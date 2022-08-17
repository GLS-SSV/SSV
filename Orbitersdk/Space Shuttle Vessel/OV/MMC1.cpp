/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/23   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "MMC1.h"


MMC1::MMC1( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "MMC1" )
{
}

MMC1::~MMC1()
{
}

void MMC1::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PL_BAY_MECH_PWR_SYS_1.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "PL_RETENTION_A6U_MMC", 16 );
	PL_RETENTION_1_RELEASE.Connect( pBundle, 0 );
	PL_RETENTION_1_LATCH.Connect( pBundle, 1 );
	PL_RETENTION_2_RELEASE.Connect( pBundle, 2 );
	PL_RETENTION_2_LATCH.Connect( pBundle, 3 );
	PL_RETENTION_3_RELEASE.Connect( pBundle, 4 );
	PL_RETENTION_3_LATCH.Connect( pBundle, 5 );
	PL_RETENTION_4_RELEASE.Connect( pBundle, 6 );
	PL_RETENTION_4_LATCH.Connect( pBundle, 7 );
	PL_RETENTION_5_RELEASE.Connect( pBundle, 8 );
	PL_RETENTION_5_LATCH.Connect( pBundle, 9 );
	LOGIC_POWER_SYS_1A.Connect( pBundle, 10 );
	LOGIC_POWER_SYS_2A.Connect( pBundle, 11 );
	LOGIC_POWER_SYS_3A.Connect( pBundle, 12 );
	//LOGIC_POWER_SYS_1B.Connect( pBundle, 13 );
	//LOGIC_POWER_SYS_2B.Connect( pBundle, 14 );
	//LOGIC_POWER_SYS_3B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 10 );
	PL_1_SEL_1A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_1A.Connect( pBundle, 2 );
	PL_1_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_1.Connect( pBundle, 4 );
	//PL_1_SEL_1B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_1B.Connect( pBundle, 7 );
	//PL_1_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 10 );
	PL_1_SEL_2A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_2A.Connect( pBundle, 2 );
	PL_1_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_2.Connect( pBundle, 4 );
	//PL_1_SEL_2B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_2B.Connect( pBundle, 7 );
	//PL_1_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 10 );
	PL_1_SEL_3A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_3A.Connect( pBundle, 2 );
	PL_1_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_3.Connect( pBundle, 4 );
	//PL_1_SEL_3B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_3B.Connect( pBundle, 7 );
	//PL_1_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 10 );
	PL_1_SEL_4A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_4A.Connect( pBundle, 2 );
	PL_1_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_4.Connect( pBundle, 4 );
	//PL_1_SEL_4B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_4B.Connect( pBundle, 7 );
	//PL_1_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 10 );
	PL_1_SEL_5A_LAT.Connect( pBundle, 0 );
	PL_1_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_5A.Connect( pBundle, 2 );
	PL_1_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_5.Connect( pBundle, 4 );
	//PL_1_SEL_5B_LAT.Connect( pBundle, 5 );
	//PL_1_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_5B.Connect( pBundle, 7 );
	//PL_1_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
	PL_2_SEL_1A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_1A.Connect( pBundle, 2 );
	PL_2_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_1.Connect( pBundle, 4 );
	//PL_2_SEL_1B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_1B.Connect( pBundle, 7 );
	//PL_2_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
	PL_2_SEL_2A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_2A.Connect( pBundle, 2 );
	PL_2_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_2.Connect( pBundle, 4 );
	//PL_2_SEL_2B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_2B.Connect( pBundle, 7 );
	//PL_2_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
	PL_2_SEL_3A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_3A.Connect( pBundle, 2 );
	PL_2_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_3.Connect( pBundle, 4 );
	//PL_2_SEL_3B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_3B.Connect( pBundle, 7 );
	//PL_2_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 10 );
	PL_2_SEL_4A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_4A.Connect( pBundle, 2 );
	PL_2_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_4.Connect( pBundle, 4 );
	//PL_2_SEL_4B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_4B.Connect( pBundle, 7 );
	//PL_2_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 10 );
	PL_2_SEL_5A_LAT.Connect( pBundle, 0 );
	PL_2_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_5A.Connect( pBundle, 2 );
	PL_2_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_5.Connect( pBundle, 4 );
	//PL_2_SEL_5B_LAT.Connect( pBundle, 5 );
	//PL_2_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_5B.Connect( pBundle, 7 );
	//PL_2_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 10 );
	PL_3_SEL_1A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_1A.Connect( pBundle, 2 );
	PL_3_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_1.Connect( pBundle, 4 );
	//PL_3_SEL_1B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_1B.Connect( pBundle, 7 );
	//PL_3_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 10 );
	PL_3_SEL_2A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_2A.Connect( pBundle, 2 );
	PL_3_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_2.Connect( pBundle, 4 );
	//PL_3_SEL_2B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_2B.Connect( pBundle, 7 );
	//PL_3_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
	PL_3_SEL_3A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_3A.Connect( pBundle, 2 );
	PL_3_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_3.Connect( pBundle, 4 );
	//PL_3_SEL_3B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_3B.Connect( pBundle, 7 );
	//PL_3_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
	PL_3_SEL_4A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_4A.Connect( pBundle, 2 );
	PL_3_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_4.Connect( pBundle, 4 );
	//PL_3_SEL_4B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_4B.Connect( pBundle, 7 );
	//PL_3_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
	PL_3_SEL_5A_LAT.Connect( pBundle, 0 );
	PL_3_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_5A.Connect( pBundle, 2 );
	PL_3_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_5.Connect( pBundle, 4 );
	//PL_3_SEL_5B_LAT.Connect( pBundle, 5 );
	//PL_3_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_5B.Connect( pBundle, 7 );
	//PL_3_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_5.Connect( pBundle, 9 );
	return;
}

void MMC1::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO missing logic
	bool K80 = PL_BAY_MECH_PWR_SYS_1;
	bool K84 = PL_BAY_MECH_PWR_SYS_1;

	// PAYLOAD RETENTION (no "ret" path back to panel)
	// pl select pos 1 sys 1 latch motors
	// latch 1a
	bool K34 = (PL_RETENTION_1_RELEASE && !PL_1_SEL_1A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K46 = (PL_RETENTION_1_LATCH && !PL_1_SEL_1A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K34)
		{
			if (K46) PL_1_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_1_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K46) PL_1_SEL_1_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 2a
	bool K39 = (PL_RETENTION_2_RELEASE && !PL_1_SEL_2A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K27 = (PL_RETENTION_2_LATCH && !PL_1_SEL_2A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K39)
		{
			if (K27) PL_1_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_2_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K27) PL_1_SEL_2_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 3a
	bool K59 = (PL_RETENTION_3_RELEASE && !PL_1_SEL_3A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K47 = (PL_RETENTION_3_LATCH && !PL_1_SEL_3A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K59)
		{
			if (K47) PL_1_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_3_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K47) PL_1_SEL_3_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 4a
	bool K29 = (PL_RETENTION_4_RELEASE && !PL_1_SEL_4A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K17 = (PL_RETENTION_4_LATCH && !PL_1_SEL_4A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K29)
		{
			if (K17) PL_1_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K17) PL_1_SEL_4_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 5a
	bool K64 = (PL_RETENTION_5_RELEASE && !PL_1_SEL_5A_REL) && LOGIC_POWER_SYS_1A;// REL
	bool K52 = (PL_RETENTION_5_LATCH && !PL_1_SEL_5A_LAT) && LOGIC_POWER_SYS_1A;// LAT

	if (K80 && K84)
	{
		if (K64)
		{
			if (K52) PL_1_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_1_SEL_5_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K52) PL_1_SEL_5_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_1_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );

	// pl select pos 2 sys 1 latch motors
	// latch 1a
	bool K60 = (PL_RETENTION_1_RELEASE && !PL_2_SEL_1A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K48 = (PL_RETENTION_1_LATCH && !PL_2_SEL_1A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K60)
		{
			if (K48) PL_2_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_1_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K48) PL_2_SEL_1_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 2a
	bool K13 = (PL_RETENTION_2_RELEASE && !PL_2_SEL_2A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K25 = (PL_RETENTION_2_LATCH && !PL_2_SEL_2A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K13)
		{
			if (K25) PL_2_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_2_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K25) PL_2_SEL_2_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 3a
	bool K49 = (PL_RETENTION_3_RELEASE && !PL_2_SEL_3A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K37 = (PL_RETENTION_3_LATCH && !PL_2_SEL_3A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K49)
		{
			if (K37) PL_2_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_3_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K37) PL_2_SEL_3_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 4a
	bool K63 = (PL_RETENTION_4_RELEASE && !PL_2_SEL_4A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K51 = (PL_RETENTION_4_LATCH && !PL_2_SEL_4A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K63)
		{
			if (K51) PL_2_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K51) PL_2_SEL_4_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 5a
	bool K38 = (PL_RETENTION_5_RELEASE && !PL_2_SEL_5A_REL) && LOGIC_POWER_SYS_2A;// REL
	bool K50 = (PL_RETENTION_5_LATCH && !PL_2_SEL_5A_LAT) && LOGIC_POWER_SYS_2A;// LAT

	if (K80 && K84)
	{
		if (K38)
		{
			if (K50) PL_2_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_2_SEL_5_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K50) PL_2_SEL_5_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_2_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );

	// pl select pos 3 sys 1 latch motors
	// latch 1a
	bool K36 = (PL_RETENTION_1_RELEASE && !PL_3_SEL_1A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K24 = (PL_RETENTION_1_LATCH && !PL_3_SEL_1A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K36)
		{
			if (K24) PL_3_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_1_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K24) PL_3_SEL_1_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_1_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 2a
	bool K77 = (PL_RETENTION_2_RELEASE && !PL_3_SEL_2A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K65 = (PL_RETENTION_2_LATCH && !PL_3_SEL_2A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K77)
		{
			if (K65) PL_3_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_2_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K65) PL_3_SEL_2_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_2_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 3a
	bool K41 = (PL_RETENTION_3_RELEASE && !PL_3_SEL_3A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K53 = (PL_RETENTION_3_LATCH && !PL_3_SEL_3A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K41)
		{
			if (K53) PL_3_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_3_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K53) PL_3_SEL_3_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_3_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 4a
	bool K61 = (PL_RETENTION_4_RELEASE && !PL_3_SEL_4A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K73 = (PL_RETENTION_4_LATCH && !PL_3_SEL_4A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K61)
		{
			if (K73) PL_3_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_4_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K73) PL_3_SEL_4_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_4_MOTOR_1_PWR.SetLine( 0.0f );

	// latch 5a
	bool K74 = (PL_RETENTION_5_RELEASE && !PL_3_SEL_5A_REL) && LOGIC_POWER_SYS_3A;// REL
	bool K62 = (PL_RETENTION_5_LATCH && !PL_3_SEL_5A_LAT) && LOGIC_POWER_SYS_3A;// LAT

	if (K80 && K84)
	{
		if (K74)
		{
			if (K62) PL_3_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
			else PL_3_SEL_5_MOTOR_1_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K62) PL_3_SEL_5_MOTOR_1_PWR.SetLine( -1.0f );
			else PL_3_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_5_MOTOR_1_PWR.SetLine( 0.0f );
	return;
}
