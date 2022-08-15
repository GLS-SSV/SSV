#include "StarTrackerDoors.h"
#include "Atlantis.h"
#include "meshres.h"
#include <MathSSV.h>


constexpr double DOOR_SPEED = 0.0714286;// single motor time (14 sec) [1/sec]
const VECTOR3 Z_REF = _V( -0.97248, 0.292585, 13.742961 );
const VECTOR3 Z_AXIS = _V( 0.18245, -0.91716, -0.3543 );
const VECTOR3 Y_REF = _V( -1.909097, -0.248751, 13.214093 );
const VECTOR3 Y_AXIS = _V( 0.86612, -0.39931, -0.300656 );
const float DOOR_TRAVEL_ANGLE = static_cast<float>(77.0 * RAD);


StarTrackerDoors::StarTrackerDoors( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "StarTrackerDoors" ),
Ypos(0.0),
Zpos(0.0)
{
	return;
}

StarTrackerDoors::~StarTrackerDoors( void )
{
	return;
}


void StarTrackerDoors::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "STAR_TRACKER_DOORS_FMC", 16 );
	STAR_TRACKER_Y_DOOR_CLS_1.Connect( pBundle, 0 );
	STAR_TRACKER_Y_DOOR_CLS_2.Connect( pBundle, 1 );
	STAR_TRACKER_Y_DOOR_OP_1.Connect( pBundle, 2 );
	STAR_TRACKER_Y_DOOR_OP_2.Connect( pBundle, 3 );
	SYS_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	SYS_2_MOTOR_2_PWR.Connect( pBundle, 5 );
	STAR_TRACKER_Z_DOOR_CLS_1.Connect( pBundle, 6 );
	STAR_TRACKER_Z_DOOR_CLS_2.Connect( pBundle, 7 );
	STAR_TRACKER_Z_DOOR_OP_1.Connect( pBundle, 8 );
	STAR_TRACKER_Z_DOOR_OP_2.Connect( pBundle, 9 );
	SYS_1_MOTOR_2_PWR.Connect( pBundle, 10 );
	SYS_2_MOTOR_1_PWR.Connect( pBundle, 11 );

	DefineAnimations();

	STS()->SetAnimation( anim_Z, Zpos );
	STS()->SetAnimation( anim_Y, Ypos );
	return;
}

bool StarTrackerDoors::OnParseLine( const char* keyword, const char* value )
{
	double tmp = 0.0;

	if (!_stricmp( keyword, "-Z_DOOR" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Zpos = range( 0.0, tmp, 1.0 );
	}
	else if (!_stricmp( keyword, "-Y_DOOR" ))
	{
		sscanf_s( value, "%lf", &tmp );
		Ypos = range( 0.0, tmp, 1.0 );
	}
	else return false;
	return true;
}

void StarTrackerDoors::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "-Z_DOOR", Zpos );
	oapiWriteScenario_float( scn, "-Y_DOOR", Ypos );
	return;
}

void StarTrackerDoors::OnPostStep( double simt, double simdt, double mjd )
{
	// motors
	Zpos = range( 0.0, Zpos + (simdt * DOOR_SPEED * (SYS_1_MOTOR_2_PWR.GetVoltage() + SYS_2_MOTOR_1_PWR.GetVoltage())), 1.0 );
	Ypos = range( 0.0, Ypos + (simdt * DOOR_SPEED * (SYS_1_MOTOR_1_PWR.GetVoltage() + SYS_2_MOTOR_2_PWR.GetVoltage())), 1.0 );

	// indications
	if (Zpos == 0.0)// CL
	{
		STAR_TRACKER_Z_DOOR_CLS_1.SetLine();
		STAR_TRACKER_Z_DOOR_CLS_2.SetLine();
		STAR_TRACKER_Z_DOOR_OP_1.ResetLine();
		STAR_TRACKER_Z_DOOR_OP_2.ResetLine();
	}
	else if (Zpos == 1.0)// OP
	{
		STAR_TRACKER_Z_DOOR_CLS_1.ResetLine();
		STAR_TRACKER_Z_DOOR_CLS_2.ResetLine();
		STAR_TRACKER_Z_DOOR_OP_1.SetLine();
		STAR_TRACKER_Z_DOOR_OP_2.SetLine();
	}
	else
	{
		STAR_TRACKER_Z_DOOR_CLS_1.ResetLine();
		STAR_TRACKER_Z_DOOR_CLS_2.ResetLine();
		STAR_TRACKER_Z_DOOR_OP_1.ResetLine();
		STAR_TRACKER_Z_DOOR_OP_2.ResetLine();
	}

	if (Ypos == 0.0)// CL
	{
		STAR_TRACKER_Y_DOOR_CLS_1.SetLine();
		STAR_TRACKER_Y_DOOR_CLS_2.SetLine();
		STAR_TRACKER_Y_DOOR_OP_1.ResetLine();
		STAR_TRACKER_Y_DOOR_OP_2.ResetLine();
	}
	else if (Ypos == 1.0)// OP
	{
		STAR_TRACKER_Y_DOOR_CLS_1.ResetLine();
		STAR_TRACKER_Y_DOOR_CLS_2.ResetLine();
		STAR_TRACKER_Y_DOOR_OP_1.SetLine();
		STAR_TRACKER_Y_DOOR_OP_2.SetLine();
	}
	else
	{
		STAR_TRACKER_Y_DOOR_CLS_1.ResetLine();
		STAR_TRACKER_Y_DOOR_CLS_2.ResetLine();
		STAR_TRACKER_Y_DOOR_OP_1.ResetLine();
		STAR_TRACKER_Y_DOOR_OP_2.ResetLine();
	}

	// set animations
	STS()->SetAnimation( anim_Z, Zpos );
	STS()->SetAnimation( anim_Y, Ypos );
	return;
}

void StarTrackerDoors::DefineAnimations( void )
{
	static UINT Z_Grp[1] = {GRP_STAR_TRACKER_DOOR_Z};
	static UINT Y_Grp[1] = {GRP_STAR_TRACKER_DOOR_Y};

	MGROUP_ROTATE* Z = new MGROUP_ROTATE( STS()->OVmesh(), Z_Grp, 1, Z_REF, Z_AXIS, DOOR_TRAVEL_ANGLE );
	MGROUP_ROTATE* Y = new MGROUP_ROTATE( STS()->OVmesh(), Y_Grp, 1, Y_REF, Y_AXIS, DOOR_TRAVEL_ANGLE );

	anim_Z = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_Z, 0.0, 1.0, Z );
	SaveAnimation( Z );

	anim_Y = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_Y, 0.0, 1.0, Y );
	SaveAnimation( Y );
	return;
}
