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
#include "MMC3.h"


MMC3::MMC3( AtlantisSubsystemDirector *_director ):AtlantisSubsystem( _director, "MMC3" )
{
}

MMC3::~MMC3()
{
}

void MMC3::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "RadiatorControlSW", 10 );
	PL_BAY_MECH_PWR_SYS_2.Connect( pBundle, 1 );

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
	//LOGIC_POWER_SYS_1A.Connect( pBundle, 10 );
	//LOGIC_POWER_SYS_2A.Connect( pBundle, 11 );
	//LOGIC_POWER_SYS_3A.Connect( pBundle, 12 );
	LOGIC_POWER_SYS_1B.Connect( pBundle, 13 );
	LOGIC_POWER_SYS_2B.Connect( pBundle, 14 );
	LOGIC_POWER_SYS_3B.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 10 );
	//PL_1_SEL_1A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_1A.Connect( pBundle, 2 );
	//PL_1_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_1.Connect( pBundle, 4 );
	PL_1_SEL_1B_LAT.Connect( pBundle, 5 );
	PL_1_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_1B.Connect( pBundle, 7 );
	PL_1_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 10 );
	//PL_1_SEL_2A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_2A.Connect( pBundle, 2 );
	//PL_1_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_2.Connect( pBundle, 4 );
	PL_1_SEL_2B_LAT.Connect( pBundle, 5 );
	PL_1_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_2B.Connect( pBundle, 7 );
	PL_1_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 10 );
	//PL_1_SEL_3A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_3A.Connect( pBundle, 2 );
	//PL_1_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_3.Connect( pBundle, 4 );
	PL_1_SEL_3B_LAT.Connect( pBundle, 5 );
	PL_1_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_3B.Connect( pBundle, 7 );
	PL_1_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 10 );
	//PL_1_SEL_4A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_4A.Connect( pBundle, 2 );
	//PL_1_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_4.Connect( pBundle, 4 );
	PL_1_SEL_4B_LAT.Connect( pBundle, 5 );
	PL_1_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_4B.Connect( pBundle, 7 );
	PL_1_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 10 );
	//PL_1_SEL_5A_LAT.Connect( pBundle, 0 );
	//PL_1_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_1_RDY_5A.Connect( pBundle, 2 );
	//PL_1_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_1A_5.Connect( pBundle, 4 );
	PL_1_SEL_5B_LAT.Connect( pBundle, 5 );
	PL_1_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_1_RDY_5B.Connect( pBundle, 7 );
	PL_1_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_1B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
	//PL_2_SEL_1A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_1A.Connect( pBundle, 2 );
	//PL_2_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_1.Connect( pBundle, 4 );
	PL_2_SEL_1B_LAT.Connect( pBundle, 5 );
	PL_2_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_1B.Connect( pBundle, 7 );
	PL_2_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
	//PL_2_SEL_2A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_2A.Connect( pBundle, 2 );
	//PL_2_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_2.Connect( pBundle, 4 );
	PL_2_SEL_2B_LAT.Connect( pBundle, 5 );
	PL_2_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_2B.Connect( pBundle, 7 );
	PL_2_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
	//PL_2_SEL_3A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_3A.Connect( pBundle, 2 );
	//PL_2_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_3.Connect( pBundle, 4 );
	PL_2_SEL_3B_LAT.Connect( pBundle, 5 );
	PL_2_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_3B.Connect( pBundle, 7 );
	PL_2_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 10 );
	//PL_2_SEL_4A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_4A.Connect( pBundle, 2 );
	//PL_2_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_4.Connect( pBundle, 4 );
	PL_2_SEL_4B_LAT.Connect( pBundle, 5 );
	PL_2_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_4B.Connect( pBundle, 7 );
	PL_2_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 10 );
	//PL_2_SEL_5A_LAT.Connect( pBundle, 0 );
	//PL_2_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_2_RDY_5A.Connect( pBundle, 2 );
	//PL_2_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_2A_5.Connect( pBundle, 4 );
	PL_2_SEL_5B_LAT.Connect( pBundle, 5 );
	PL_2_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_2_RDY_5B.Connect( pBundle, 7 );
	PL_2_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_2B_5.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 10 );
	//PL_3_SEL_1A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_1A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_1A.Connect( pBundle, 2 );
	//PL_3_SEL_1_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_1.Connect( pBundle, 4 );
	PL_3_SEL_1B_LAT.Connect( pBundle, 5 );
	PL_3_SEL_1B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_1B.Connect( pBundle, 7 );
	PL_3_SEL_1_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_1.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 10 );
	//PL_3_SEL_2A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_2A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_2A.Connect( pBundle, 2 );
	//PL_3_SEL_2_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_2.Connect( pBundle, 4 );
	PL_3_SEL_2B_LAT.Connect( pBundle, 5 );
	PL_3_SEL_2B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_2B.Connect( pBundle, 7 );
	PL_3_SEL_2_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_2.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
	//PL_3_SEL_3A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_3A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_3A.Connect( pBundle, 2 );
	//PL_3_SEL_3_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_3.Connect( pBundle, 4 );
	PL_3_SEL_3B_LAT.Connect( pBundle, 5 );
	PL_3_SEL_3B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_3B.Connect( pBundle, 7 );
	PL_3_SEL_3_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_3.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
	//PL_3_SEL_4A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_4A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_4A.Connect( pBundle, 2 );
	//PL_3_SEL_4_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_4.Connect( pBundle, 4 );
	PL_3_SEL_4B_LAT.Connect( pBundle, 5 );
	PL_3_SEL_4B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_4B.Connect( pBundle, 7 );
	PL_3_SEL_4_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_4.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
	//PL_3_SEL_5A_LAT.Connect( pBundle, 0 );
	//PL_3_SEL_5A_REL.Connect( pBundle, 1 );
	//PL_3_RDY_5A.Connect( pBundle, 2 );
	//PL_3_SEL_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	//IND_3A_5.Connect( pBundle, 4 );
	PL_3_SEL_5B_LAT.Connect( pBundle, 5 );
	PL_3_SEL_5B_REL.Connect( pBundle, 6 );
	//PL_3_RDY_5B.Connect( pBundle, 7 );
	PL_3_SEL_5_MOTOR_2_PWR.Connect( pBundle, 8 );
	//IND_3B_5.Connect( pBundle, 9 );
	return;
}

void MMC3::OnPreStep( double simt, double simdt, double mjd )
{
	// TODO missing logic
	bool K77 = PL_BAY_MECH_PWR_SYS_2;
	bool K65 = PL_BAY_MECH_PWR_SYS_2;

	// PAYLOAD RETENTION (no "ret" path back to panel)
	// pl select pos 1 sys 2 latch motors
	// latch 1b
	bool K17 = (PL_RETENTION_1_RELEASE && !PL_1_SEL_1B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K5 = (PL_RETENTION_1_LATCH && !PL_1_SEL_1B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K17)
		{
			if (K5) PL_1_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_1_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K5) PL_1_SEL_1_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 2b
	bool K34 = (PL_RETENTION_2_RELEASE && !PL_1_SEL_2B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K32 = (PL_RETENTION_2_LATCH && !PL_1_SEL_2B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K34)
		{
			if (K32) PL_1_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_2_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K32) PL_1_SEL_2_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 3b
	bool K70 = (PL_RETENTION_3_RELEASE && !PL_1_SEL_3B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K68 = (PL_RETENTION_3_LATCH && !PL_1_SEL_3B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K70)
		{
			if (K68) PL_1_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_3_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K68) PL_1_SEL_3_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 4b
	bool K81 = (PL_RETENTION_4_RELEASE && !PL_1_SEL_4B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K79 = (PL_RETENTION_4_LATCH && !PL_1_SEL_4B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K81)
		{
			if (K79) PL_1_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K79) PL_1_SEL_4_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 5b
	bool K47 = (PL_RETENTION_5_RELEASE && !PL_1_SEL_5B_REL) && LOGIC_POWER_SYS_1B;// REL
	bool K35 = (PL_RETENTION_5_LATCH && !PL_1_SEL_5B_LAT) && LOGIC_POWER_SYS_1B;// LAT

	if (K77 && K65)
	{
		if (K47)
		{
			if (K35) PL_1_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_1_SEL_5_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K35) PL_1_SEL_5_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_1_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_1_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );

	// pl select pos 2 sys 2 latch motors
	// latch 1b
	bool K57 = (PL_RETENTION_1_RELEASE && !PL_2_SEL_1B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K55 = (PL_RETENTION_1_LATCH && !PL_2_SEL_1B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K57)
		{
			if (K55) PL_2_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_1_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K55) PL_2_SEL_1_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 2b
	bool K33 = (PL_RETENTION_2_RELEASE && !PL_2_SEL_2B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K31 = (PL_RETENTION_2_LATCH && !PL_2_SEL_2B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K33)
		{
			if (K31) PL_2_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_2_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K31) PL_2_SEL_2_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 3b
	bool K58 = (PL_RETENTION_3_RELEASE && !PL_2_SEL_3B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K56 = (PL_RETENTION_3_LATCH && !PL_2_SEL_3B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K58)
		{
			if (K56) PL_2_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_3_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K56) PL_2_SEL_3_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 4b
	bool K69 = (PL_RETENTION_4_RELEASE && !PL_2_SEL_4B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K67 = (PL_RETENTION_4_LATCH && !PL_2_SEL_4B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K69)
		{
			if (K67) PL_2_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K67) PL_2_SEL_4_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 5b
	bool K48 = (PL_RETENTION_5_RELEASE && !PL_2_SEL_5B_REL) && LOGIC_POWER_SYS_2B;// REL
	bool K36 = (PL_RETENTION_5_LATCH && !PL_2_SEL_5B_LAT) && LOGIC_POWER_SYS_2B;// LAT

	if (K77 && K65)
	{
		if (K48)
		{
			if (K36) PL_2_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_2_SEL_5_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K36) PL_2_SEL_5_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_2_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_2_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );

	// pl select pos 3 sys 2 latch motors
	// latch 1b
	bool K75 = (PL_RETENTION_1_RELEASE && !PL_3_SEL_1B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K73 = (PL_RETENTION_1_LATCH && !PL_3_SEL_1B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K75)
		{
			if (K73) PL_3_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_1_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K73) PL_3_SEL_1_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_1_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 2b
	bool K21 = (PL_RETENTION_2_RELEASE && !PL_3_SEL_2B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K19 = (PL_RETENTION_2_LATCH && !PL_3_SEL_2B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K21)
		{
			if (K19) PL_3_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_2_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K19) PL_3_SEL_2_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_2_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 3b
	bool K46 = (PL_RETENTION_3_RELEASE && !PL_3_SEL_3B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K44 = (PL_RETENTION_3_LATCH && !PL_3_SEL_3B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K46)
		{
			if (K44) PL_3_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_3_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K44) PL_3_SEL_3_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_3_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 4b
	bool K45 = (PL_RETENTION_4_RELEASE && !PL_3_SEL_4B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K43 = (PL_RETENTION_4_LATCH && !PL_3_SEL_4B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K45)
		{
			if (K43) PL_3_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_4_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K43) PL_3_SEL_4_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_4_MOTOR_2_PWR.SetLine( 0.0f );

	// latch 5b
	bool K82 = (PL_RETENTION_5_RELEASE && !PL_3_SEL_5B_REL) && LOGIC_POWER_SYS_3B;// REL
	bool K80 = (PL_RETENTION_5_LATCH && !PL_3_SEL_5B_LAT) && LOGIC_POWER_SYS_3B;// LAT

	if (K77 && K65)
	{
		if (K82)
		{
			if (K80) PL_3_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
			else PL_3_SEL_5_MOTOR_2_PWR.SetLine( 1.0f );
		}
		else
		{
			if (K80) PL_3_SEL_5_MOTOR_2_PWR.SetLine( -1.0f );
			else PL_3_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
		}
	}
	else PL_3_SEL_5_MOTOR_2_PWR.SetLine( 0.0f );
	return;
}
