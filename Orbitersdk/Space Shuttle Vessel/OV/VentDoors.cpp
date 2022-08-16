#include "VentDoors.h"
#include "Atlantis.h"
#include "meshres.h"
#include <MathSSV.h>


constexpr double DOOR_SPEED = 0.1;// single motor time (10 sec) [1/sec]

const VECTOR3 LH1_REF = _V( -1.91553, -1.12358, 14.519199 );
const VECTOR3 LH1_AXIS = _V( 0.216297, -0.211166, 0.95322 );
const VECTOR3 LH2_REF = _V( -2.01751, -1.03281, 14.11105 );
const VECTOR3 LH2_AXIS = _V( 0.21637, -0.21124, 0.95319 );
const VECTOR3 LH3_REF = _V( -2.66446, -0.708278, 4.80496 );
const VECTOR3 LH3_AXIS = _V( 0.0, 0.0, 1.0 );
const VECTOR3 LH4_REF = _V( -2.66446, -0.708278, 1.25962 );
const VECTOR3 LH4_AXIS = _V( 0.0, 0.0, 1.0 );
const VECTOR3 LH5_REF = _V( -2.66446, -0.708278, -1.0467 );
const VECTOR3 LH5_AXIS = _V( 0.0, 0.0, 1.0 );
const VECTOR3 LH6_REF = _V( -2.66446, -0.708278, -4.40814 );
const VECTOR3 LH6_AXIS = _V( 0.0, 0.0, 1.0 );
const VECTOR3 LH7_REF = _V( -2.66446, -1.45174, 0.51235 );
const VECTOR3 LH7_AXIS = _V( 0.0, 0.0, 1.0 );
const VECTOR3 LH8_REF = _V( -2.953055, -1.61963, -12.06665 );
const VECTOR3 LH8_AXIS = _V( -0.099154, 0.0, -0.99507 );
const VECTOR3 LH9_REF = _V( -2.857375, -1.61786, -11.05915 );
const VECTOR3 LH9_AXIS = _V( -0.090154, 0.0, -0.99593 );

const VECTOR3 RH1_REF = _V( 1.91553, -1.12358, 14.519199 );
const VECTOR3 RH1_AXIS = _V( 0.216297, 0.211166, -0.95322 );
const VECTOR3 RH2_REF = _V( 2.01751, -1.03281, 14.11105 );
const VECTOR3 RH2_AXIS = _V( 0.21637, 0.21124, -0.95319 );
const VECTOR3 RH3_REF = _V( 2.66446, -0.708278, 4.80496 );
const VECTOR3 RH3_AXIS = _V( 0.0, 0.0, -1.0 );
const VECTOR3 RH4_REF = _V( 2.66446, -0.708278, 1.25962 );
const VECTOR3 RH4_AXIS = _V( 0.0, 0.0, -1.0 );
const VECTOR3 RH5_REF = _V( 2.66446, -0.708278, -1.0467 );
const VECTOR3 RH5_AXIS = _V( 0.0, 0.0, -1.0 );
const VECTOR3 RH6_REF = _V( 2.66446, -0.708278, -4.40814 );
const VECTOR3 RH6_AXIS = _V( 0.0, 0.0, -1.0 );
const VECTOR3 RH7_REF = _V( 2.66446, -1.45174, 0.51235 );
const VECTOR3 RH7_AXIS = _V( 0.0, 0.0, -1.0 );
const VECTOR3 RH8_REF = _V( 2.953055, -1.61963, -12.06665 );
const VECTOR3 RH8_AXIS = _V( -0.099154, 0.0, 0.99507 );
const VECTOR3 RH9_REF = _V( 2.857375, -1.61786, -11.05915 );
const VECTOR3 RH9_AXIS = _V( -0.090154, 0.0, 0.99593 );

const float DOOR12_TRAVEL_ANGLE = static_cast<float>(90.0 * RAD);
const float DOOR345689_TRAVEL_ANGLE = static_cast<float>(75.0 * RAD);
const float DOOR7_TRAVEL_ANGLE = static_cast<float>(65.0 * RAD);

const float DOOR12_PURGE_1_ANGLE = static_cast<float>(12.0 * RAD);
const float DOOR12_PURGE_1_POS = DOOR12_PURGE_1_ANGLE / DOOR12_TRAVEL_ANGLE;

const float DOOR6_PURGE_1_ANGLE = static_cast<float>(10.0 * RAD);
const float DOOR6_PURGE_2_ANGLE = static_cast<float>(15.0 * RAD);
const float DOOR6_PURGE_1_POS = DOOR6_PURGE_1_ANGLE / DOOR345689_TRAVEL_ANGLE;
const float DOOR6_PURGE_2_POS = DOOR6_PURGE_2_ANGLE / DOOR345689_TRAVEL_ANGLE;

const float DOOR89_PURGE_1_ANGLE = static_cast<float>(20.0 * RAD);
const float DOOR89_PURGE_1_POS = DOOR89_PURGE_1_ANGLE / DOOR345689_TRAVEL_ANGLE;


VentDoors::VentDoors( AtlantisSubsystemDirector *_director, bool hasVentDoor47 ):AtlantisSubsystem( _director, "VentDoors" ),
posLH12(0.0), posLH3(0.0), posLH47(0.0), posLH5(0.0), posLH6(0.0), posLH89(0.0),
posRH12(0.0), posRH3(0.0), posRH47(0.0), posRH5(0.0), posRH6(0.0), posRH89(0.0),
hasVentDoor47(hasVentDoor47)
{
}

VentDoors::~VentDoors()
{
}

void VentDoors::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_1", 12 );
	LH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 0 );
	LH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 1 );
	LH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 2 );
	LH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 3 );
	LH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 4 );
	LH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 5 );
	RH_VENTS_1_AND_2_MOTOR_1_PWR.Connect( pBundle, 6 );
	RH_VENT_3_MOTOR_1_PWR.Connect( pBundle, 7 );
	RH_VENTS_4_AND_7_MOTOR_1_PWR.Connect( pBundle, 8 );
	RH_VENT_5_MOTOR_1_PWR.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_1_PWR.Connect( pBundle, 10 );
	RH_VENTS_8_AND_9_MOTOR_1_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_MOTORS_2", 12 );
	LH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 0 );
	LH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 1 );
	LH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 2 );
	LH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 3 );
	LH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 4 );
	LH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 5 );
	RH_VENTS_1_AND_2_MOTOR_2_PWR.Connect( pBundle, 6 );
	RH_VENT_3_MOTOR_2_PWR.Connect( pBundle, 7 );
	RH_VENTS_4_AND_7_MOTOR_2_PWR.Connect( pBundle, 8 );
	RH_VENT_5_MOTOR_2_PWR.Connect( pBundle, 9 );
	RH_VENT_6_MOTOR_2_PWR.Connect( pBundle, 10 );
	RH_VENTS_8_AND_9_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
	L_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	L_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	L_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	LH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	LH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	LH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	LH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	LH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	LH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	LH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	LH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	LH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	LH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	LH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	LH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	LH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
	L_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	L_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	L_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	LH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	LH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	LH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	LH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	LH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	LH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	LH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	LH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	LH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	LH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	LH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	LH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	LH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
	R_VENTS_1_AND_2_CLOSE_1.Connect( pBundle, 0 );
	R_VENTS_1_AND_2_OPEN_1.Connect( pBundle, 1 );
	R_VENTS_1_AND_2_PURGE_1_IND_1.Connect( pBundle, 2 );
	RH_VENT_3_CLOSE_1.Connect( pBundle, 3 );
	RH_VENT_3_OPEN_1.Connect( pBundle, 4 );
	RH_VENTS_4_AND_7_CLOSE_1.Connect( pBundle, 5 );
	RH_VENTS_4_AND_7_OPEN_1.Connect( pBundle, 6 );
	RH_VENT_5_CLOSE_1.Connect( pBundle, 7 );
	RH_VENT_5_OPEN_1.Connect( pBundle, 8 );
	RH_VENT_6_CLOSE_1.Connect( pBundle, 9 );
	RH_VENT_6_OPEN_1.Connect( pBundle, 10 );
	RH_VENT_6_PURGE_1_IND_1.Connect( pBundle, 11 );
	RH_VENT_6_PURGE_2_IND_1.Connect( pBundle, 12 );
	RH_VENTS_8_AND_9_CLOSE_1.Connect( pBundle, 13 );
	RH_VENTS_8_AND_9_OPEN_1.Connect( pBundle, 14 );
	RH_VENTS_8_AND_9_PURGE_IND_1.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
	R_VENTS_1_AND_2_CLOSE_2.Connect( pBundle, 0 );
	R_VENTS_1_AND_2_OPEN_2.Connect( pBundle, 1 );
	R_VENTS_1_AND_2_PURGE_1_IND_2.Connect( pBundle, 2 );
	RH_VENT_3_CLOSE_2.Connect( pBundle, 3 );
	RH_VENT_3_OPEN_2.Connect( pBundle, 4 );
	RH_VENTS_4_AND_7_CLOSE_2.Connect( pBundle, 5 );
	RH_VENTS_4_AND_7_OPEN_2.Connect( pBundle, 6 );
	RH_VENT_5_CLOSE_2.Connect( pBundle, 7 );
	RH_VENT_5_OPEN_2.Connect( pBundle, 8 );
	RH_VENT_6_CLOSE_2.Connect( pBundle, 9 );
	RH_VENT_6_OPEN_2.Connect( pBundle, 10 );
	RH_VENT_6_PURGE_1_IND_2.Connect( pBundle, 11 );
	RH_VENT_6_PURGE_2_IND_2.Connect( pBundle, 12 );
	RH_VENTS_8_AND_9_CLOSE_2.Connect( pBundle, 13 );
	RH_VENTS_8_AND_9_OPEN_2.Connect( pBundle, 14 );
	RH_VENTS_8_AND_9_PURGE_IND_2.Connect( pBundle, 15 );

	DefineAnimations();

	SetAnimations();
	return;
}

bool VentDoors::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "LEFT_1/2", 8 ))
	{
		sscanf_s( (char*)(line + 8), "%lf", &posLH12 );
		posLH12 = range( 0.0, posLH12, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "LEFT_3", 6 ))
	{
		sscanf_s( (char*)(line + 6), "%lf", &posLH3 );
		posLH3 = range( 0.0, posLH3, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "LEFT_4/7", 8 ))
	{
		sscanf_s( (char*)(line + 8), "%lf", &posLH47 );
		posLH47 = range( 0.0, posLH47, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "LEFT_5", 6 ))
	{
		sscanf_s( (char*)(line + 6), "%lf", &posLH5 );
		posLH5 = range( 0.0, posLH5, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "LEFT_6", 6 ))
	{
		sscanf_s( (char*)(line + 6), "%lf", &posLH6 );
		posLH6 = range( 0.0, posLH6, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "LEFT_8/9", 8 ))
	{
		sscanf_s( (char*)(line + 8), "%lf", &posLH89 );
		posLH89 = range( 0.0, posLH89, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT_1/2", 9 ))
	{
		sscanf_s( (char*)(line + 9), "%lf", &posRH12 );
		posRH12 = range( 0.0, posRH12, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT_3", 7 ))
	{
		sscanf_s( (char*)(line + 7), "%lf", &posRH3 );
		posRH3 = range( 0.0, posRH3, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT_4/7", 9 ))
	{
		sscanf_s( (char*)(line + 9), "%lf", &posRH47 );
		posRH47 = range( 0.0, posRH47, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT_5", 7 ))
	{
		sscanf_s( (char*)(line + 7), "%lf", &posRH5 );
		posRH5 = range( 0.0, posRH5, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT_6", 7 ))
	{
		sscanf_s( (char*)(line + 7), "%lf", &posRH6 );
		posRH6 = range( 0.0, posRH6, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT_8/9", 9 ))
	{
		sscanf_s( (char*)(line + 9), "%lf", &posRH89 );
		posRH89 = range( 0.0, posRH89, 1.0 );
		return true;
	}
	else return false;
}

void VentDoors::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "LEFT_1/2", posLH12 );
	oapiWriteScenario_float( scn, "LEFT_3", posLH3 );
	if (hasVentDoor47) oapiWriteScenario_float( scn, "LEFT_4/7", posLH47 );
	oapiWriteScenario_float( scn, "LEFT_5", posLH5 );
	oapiWriteScenario_float( scn, "LEFT_6", posLH6 );
	oapiWriteScenario_float( scn, "LEFT_8/9", posLH89 );
	oapiWriteScenario_float( scn, "RIGHT_1/2", posRH12 );
	oapiWriteScenario_float( scn, "RIGHT_3", posRH3 );
	if (hasVentDoor47) oapiWriteScenario_float( scn, "RIGHT_4/7", posRH47 );
	oapiWriteScenario_float( scn, "RIGHT_5", posRH5 );
	oapiWriteScenario_float( scn, "RIGHT_6", posRH6 );
	oapiWriteScenario_float( scn, "RIGHT_8/9", posRH89 );
	return;
}

void VentDoors::OnPostStep( double simt, double simdt, double mjd )
{
	// motors
	posLH12 = range( 0.0, posLH12 + (simdt * DOOR_SPEED * (LH_VENTS_1_AND_2_MOTOR_1_PWR.GetVoltage() + LH_VENTS_1_AND_2_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posLH3 = range( 0.0, posLH3 + (simdt * DOOR_SPEED * (LH_VENT_3_MOTOR_1_PWR.GetVoltage() + LH_VENT_3_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posLH47 = range( 0.0, posLH47 + (simdt * DOOR_SPEED * (LH_VENTS_4_AND_7_MOTOR_1_PWR.GetVoltage() + LH_VENTS_4_AND_7_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posLH5 = range( 0.0, posLH5 + (simdt * DOOR_SPEED * (LH_VENT_5_MOTOR_1_PWR.GetVoltage() + LH_VENT_5_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posLH6 = range( 0.0, posLH6 + (simdt * DOOR_SPEED * (LH_VENT_6_MOTOR_1_PWR.GetVoltage() + LH_VENT_6_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posLH89 = range( 0.0, posLH89 + (simdt * DOOR_SPEED * (LH_VENTS_8_AND_9_MOTOR_1_PWR.GetVoltage() + LH_VENTS_8_AND_9_MOTOR_2_PWR.GetVoltage())), 1.0 );

	posRH12 = range( 0.0, posRH12 + (simdt * DOOR_SPEED * (RH_VENTS_1_AND_2_MOTOR_1_PWR.GetVoltage() + RH_VENTS_1_AND_2_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posRH3 = range( 0.0, posRH3 + (simdt * DOOR_SPEED * (RH_VENT_3_MOTOR_1_PWR.GetVoltage() + RH_VENT_3_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posRH47 = range( 0.0, posRH47 + (simdt * DOOR_SPEED * (RH_VENTS_4_AND_7_MOTOR_1_PWR.GetVoltage() + RH_VENTS_4_AND_7_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posRH5 = range( 0.0, posRH5 + (simdt * DOOR_SPEED * (RH_VENT_5_MOTOR_1_PWR.GetVoltage() + RH_VENT_5_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posRH6 = range( 0.0, posRH6 + (simdt * DOOR_SPEED * (RH_VENT_6_MOTOR_1_PWR.GetVoltage() + RH_VENT_6_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posRH89 = range( 0.0, posRH89 + (simdt * DOOR_SPEED * (RH_VENTS_8_AND_9_MOTOR_1_PWR.GetVoltage() + RH_VENTS_8_AND_9_MOTOR_2_PWR.GetVoltage())), 1.0 );

	// indications
	SetIndications();

	// set animations
	SetAnimations();
	return;
}

void VentDoors::DefineAnimations( void )
{
	static UINT LH1_Grp[1] = {GRP_VENT_DOOR_LEFT_1};
	MGROUP_ROTATE* LH1 = new MGROUP_ROTATE( STS()->OVmesh(), LH1_Grp, 1, LH1_REF, LH1_AXIS, DOOR12_TRAVEL_ANGLE );
	anim_LH1 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH1, 0.0, 1.0, LH1 );
	SaveAnimation( LH1 );

	static UINT LH2_Grp[1] = {GRP_VENT_DOOR_LEFT_2};
	MGROUP_ROTATE* LH2 = new MGROUP_ROTATE( STS()->OVmesh(), LH2_Grp, 1, LH2_REF, LH2_AXIS, DOOR12_TRAVEL_ANGLE );
	anim_LH2 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH2, 0.0, 1.0, LH2 );
	SaveAnimation( LH2 );

	static UINT LH3_Grp[1] = {GRP_VENT_DOOR_LEFT_3};
	MGROUP_ROTATE* LH3 = new MGROUP_ROTATE( STS()->OVmesh(), LH3_Grp, 1, LH3_REF, LH3_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_LH3 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH3, 0.0, 1.0, LH3 );
	SaveAnimation( LH3 );

	if (hasVentDoor47)
	{
		static UINT LH4_Grp[1] = {GRP_VENT_DOOR_LEFT_4};
		MGROUP_ROTATE* LH4 = new MGROUP_ROTATE( STS()->OVmesh(), LH4_Grp, 1, LH4_REF, LH4_AXIS, DOOR345689_TRAVEL_ANGLE );
		anim_LH4 = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_LH4, 0.0, 1.0, LH4 );
		SaveAnimation( LH4 );
	}

	static UINT LH5_Grp[1] = {GRP_VENT_DOOR_LEFT_5};
	MGROUP_ROTATE* LH5 = new MGROUP_ROTATE( STS()->OVmesh(), LH5_Grp, 1, LH5_REF, LH5_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_LH5 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH5, 0.0, 1.0, LH5 );
	SaveAnimation( LH5 );

	static UINT LH6_Grp[1] = {GRP_VENT_DOOR_LEFT_6};
	MGROUP_ROTATE* LH6 = new MGROUP_ROTATE( STS()->OVmesh(), LH6_Grp, 1, LH6_REF, LH6_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_LH6 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH6, 0.0, 1.0, LH6 );
	SaveAnimation( LH6 );

	if (hasVentDoor47)
	{
		static UINT LH7_Grp[1] = {GRP_VENT_DOOR_LEFT_7};
		MGROUP_ROTATE* LH7 = new MGROUP_ROTATE( STS()->OVmesh(), LH7_Grp, 1, LH7_REF, LH7_AXIS, DOOR7_TRAVEL_ANGLE );
		anim_LH7 = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_LH7, 0.0, 1.0, LH7 );
		SaveAnimation( LH7 );
	}

	static UINT LH8_Grp[1] = {GRP_VENT_DOOR_LEFT_8};
	MGROUP_ROTATE* LH8 = new MGROUP_ROTATE( STS()->OVmesh(), LH8_Grp, 1, LH8_REF, LH8_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_LH8 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH8, 0.0, 1.0, LH8 );
	SaveAnimation( LH8 );

	static UINT LH9_Grp[1] = {GRP_VENT_DOOR_LEFT_9};
	MGROUP_ROTATE* LH9 = new MGROUP_ROTATE( STS()->OVmesh(), LH9_Grp, 1, LH9_REF, LH9_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_LH9 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_LH9, 0.0, 1.0, LH9 );
	SaveAnimation( LH9 );

	static UINT RH1_Grp[1] = {GRP_VENT_DOOR_RIGHT_1};
	MGROUP_ROTATE* RH1 = new MGROUP_ROTATE( STS()->OVmesh(), RH1_Grp, 1, RH1_REF, RH1_AXIS, DOOR12_TRAVEL_ANGLE );
	anim_RH1 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH1, 0.0, 1.0, RH1 );
	SaveAnimation( RH1 );

	static UINT RH2_Grp[1] = {GRP_VENT_DOOR_RIGHT_2};
	MGROUP_ROTATE* RH2 = new MGROUP_ROTATE( STS()->OVmesh(), RH2_Grp, 1, RH2_REF, RH2_AXIS, DOOR12_TRAVEL_ANGLE );
	anim_RH2 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH2, 0.0, 1.0, RH2 );
	SaveAnimation( RH2 );

	static UINT RH3_Grp[1] = {GRP_VENT_DOOR_RIGHT_3};
	MGROUP_ROTATE* RH3 = new MGROUP_ROTATE( STS()->OVmesh(), RH3_Grp, 1, RH3_REF, RH3_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_RH3 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH3, 0.0, 1.0, RH3 );
	SaveAnimation( RH3 );

	if (hasVentDoor47)
	{
		static UINT RH4_Grp[1] = {GRP_VENT_DOOR_RIGHT_4};
		MGROUP_ROTATE* RH4 = new MGROUP_ROTATE( STS()->OVmesh(), RH4_Grp, 1, RH4_REF, RH4_AXIS, DOOR345689_TRAVEL_ANGLE );
		anim_RH4 = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_RH4, 0.0, 1.0, RH4 );
		SaveAnimation( RH4 );
	}

	static UINT RH5_Grp[1] = {GRP_VENT_DOOR_RIGHT_5};
	MGROUP_ROTATE* RH5 = new MGROUP_ROTATE( STS()->OVmesh(), RH5_Grp, 1, RH5_REF, RH5_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_RH5 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH5, 0.0, 1.0, RH5 );
	SaveAnimation( RH5 );

	static UINT RH6_Grp[1] = {GRP_VENT_DOOR_RIGHT_6};
	MGROUP_ROTATE* RH6 = new MGROUP_ROTATE( STS()->OVmesh(), RH6_Grp, 1, RH6_REF, RH6_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_RH6 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH6, 0.0, 1.0, RH6 );
	SaveAnimation( RH6 );

	if (hasVentDoor47)
	{
		static UINT RH7_Grp[1] = {GRP_VENT_DOOR_RIGHT_7};
		MGROUP_ROTATE* RH7 = new MGROUP_ROTATE( STS()->OVmesh(), RH7_Grp, 1, RH7_REF, RH7_AXIS, DOOR7_TRAVEL_ANGLE );
		anim_RH7 = STS()->CreateAnimation( 0.0 );
		STS()->AddAnimationComponent( anim_RH7, 0.0, 1.0, RH7 );
		SaveAnimation( RH7 );
	}

	static UINT RH8_Grp[1] = {GRP_VENT_DOOR_RIGHT_8};
	MGROUP_ROTATE* RH8 = new MGROUP_ROTATE( STS()->OVmesh(), RH8_Grp, 1, RH8_REF, RH8_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_RH8 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH8, 0.0, 1.0, RH8 );
	SaveAnimation( RH8 );

	static UINT RH9_Grp[1] = {GRP_VENT_DOOR_RIGHT_9};
	MGROUP_ROTATE* RH9 = new MGROUP_ROTATE( STS()->OVmesh(), RH9_Grp, 1, RH9_REF, RH9_AXIS, DOOR345689_TRAVEL_ANGLE );
	anim_RH9 = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_RH9, 0.0, 1.0, RH9 );
	SaveAnimation( RH9 );
	return;
}

void VentDoors::SetIndications( void )
{
	if (posLH12 <= DOOR12_PURGE_1_POS)// PG
	{
		L_VENTS_1_AND_2_PURGE_1_IND_1.SetLine();
		L_VENTS_1_AND_2_PURGE_1_IND_2.SetLine();
		L_VENTS_1_AND_2_OPEN_1.ResetLine();
		L_VENTS_1_AND_2_OPEN_2.ResetLine();

		if (posLH12 == 0.0)// CL
		{
			L_VENTS_1_AND_2_CLOSE_1.SetLine();
			L_VENTS_1_AND_2_CLOSE_2.SetLine();
			
		}
		else
		{
			L_VENTS_1_AND_2_CLOSE_1.ResetLine();
			L_VENTS_1_AND_2_CLOSE_2.ResetLine();
		}
	}
	else
	{
		L_VENTS_1_AND_2_PURGE_1_IND_1.ResetLine();
		L_VENTS_1_AND_2_PURGE_1_IND_2.ResetLine();
		L_VENTS_1_AND_2_CLOSE_1.ResetLine();
		L_VENTS_1_AND_2_CLOSE_2.ResetLine();

		if (posLH12 == 1.0)// OP
		{
			L_VENTS_1_AND_2_OPEN_1.SetLine();
			L_VENTS_1_AND_2_OPEN_2.SetLine();
		}
		else
		{
			L_VENTS_1_AND_2_OPEN_1.ResetLine();
			L_VENTS_1_AND_2_OPEN_2.ResetLine();
		}
	}

	if (posLH3 == 0.0)// CL
	{
		LH_VENT_3_CLOSE_1.SetLine();
		LH_VENT_3_CLOSE_2.SetLine();
		LH_VENT_3_OPEN_1.ResetLine();
		LH_VENT_3_OPEN_2.ResetLine();
	}
	else if (posLH3 == 1.0)// OP
	{
		LH_VENT_3_CLOSE_1.ResetLine();
		LH_VENT_3_CLOSE_2.ResetLine();
		LH_VENT_3_OPEN_1.SetLine();
		LH_VENT_3_OPEN_2.SetLine();
	}
	else
	{
		LH_VENT_3_CLOSE_1.ResetLine();
		LH_VENT_3_CLOSE_2.ResetLine();
		LH_VENT_3_OPEN_1.ResetLine();
		LH_VENT_3_OPEN_2.ResetLine();
	}

	if (hasVentDoor47)
	{
		if (posLH47 == 0.0)// CL
		{
			LH_VENTS_4_AND_7_CLOSE_1.SetLine();
			LH_VENTS_4_AND_7_CLOSE_2.SetLine();
			LH_VENTS_4_AND_7_OPEN_1.ResetLine();
			LH_VENTS_4_AND_7_OPEN_2.ResetLine();
		}
		else if (posLH47 == 1.0)// OP
		{
			LH_VENTS_4_AND_7_CLOSE_1.ResetLine();
			LH_VENTS_4_AND_7_CLOSE_2.ResetLine();
			LH_VENTS_4_AND_7_OPEN_1.SetLine();
			LH_VENTS_4_AND_7_OPEN_2.SetLine();
		}
		else
		{
			LH_VENTS_4_AND_7_CLOSE_1.ResetLine();
			LH_VENTS_4_AND_7_CLOSE_2.ResetLine();
			LH_VENTS_4_AND_7_OPEN_1.ResetLine();
			LH_VENTS_4_AND_7_OPEN_2.ResetLine();
		}
	}

	if (posLH5 == 0.0)// CL
	{
		LH_VENT_5_CLOSE_1.SetLine();
		LH_VENT_5_CLOSE_2.SetLine();
		LH_VENT_5_OPEN_1.ResetLine();
		LH_VENT_5_OPEN_2.ResetLine();
	}
	else if (posLH5 == 1.0)// OP
	{
		LH_VENT_5_CLOSE_1.ResetLine();
		LH_VENT_5_CLOSE_2.ResetLine();
		LH_VENT_5_OPEN_1.SetLine();
		LH_VENT_5_OPEN_2.SetLine();
	}
	else
	{
		LH_VENT_5_CLOSE_1.ResetLine();
		LH_VENT_5_CLOSE_2.ResetLine();
		LH_VENT_5_OPEN_1.ResetLine();
		LH_VENT_5_OPEN_2.ResetLine();
	}

	if (posLH6 <= DOOR6_PURGE_1_POS)// PG 1
	{
		LH_VENT_6_PURGE_1_IND_1.SetLine();
		LH_VENT_6_PURGE_1_IND_2.SetLine();
		LH_VENT_6_PURGE_2_IND_1.ResetLine();
		LH_VENT_6_PURGE_2_IND_2.ResetLine();
		LH_VENT_6_OPEN_1.ResetLine();
		LH_VENT_6_OPEN_2.ResetLine();

		if (posLH6 == 0.0)// CL
		{
			LH_VENT_6_CLOSE_1.SetLine();
			LH_VENT_6_CLOSE_2.SetLine();
			
		}
		else
		{
			LH_VENT_6_CLOSE_1.ResetLine();
			LH_VENT_6_CLOSE_2.ResetLine();
		}
	}
	else if (posLH6 >= DOOR6_PURGE_2_POS)// PG 2
	{
		LH_VENT_6_PURGE_1_IND_1.ResetLine();
		LH_VENT_6_PURGE_1_IND_2.ResetLine();
		LH_VENT_6_PURGE_2_IND_1.SetLine();
		LH_VENT_6_PURGE_2_IND_2.SetLine();
		LH_VENT_6_CLOSE_1.ResetLine();
		LH_VENT_6_CLOSE_2.ResetLine();

		if (posLH6 == 1.0)// OP
		{
			LH_VENT_6_OPEN_1.SetLine();
			LH_VENT_6_OPEN_2.SetLine();
			
		}
		else
		{
			LH_VENT_6_OPEN_1.ResetLine();
			LH_VENT_6_OPEN_2.ResetLine();
		}
	}
	else
	{
		LH_VENT_6_PURGE_1_IND_1.ResetLine();
		LH_VENT_6_PURGE_1_IND_2.ResetLine();
		LH_VENT_6_PURGE_2_IND_1.ResetLine();
		LH_VENT_6_PURGE_2_IND_2.ResetLine();
		LH_VENT_6_CLOSE_1.ResetLine();
		LH_VENT_6_CLOSE_2.ResetLine();
		LH_VENT_6_OPEN_1.ResetLine();
		LH_VENT_6_OPEN_2.ResetLine();
	}

	if (posLH89 <= DOOR89_PURGE_1_POS)// PG
	{
		LH_VENTS_8_AND_9_PURGE_IND_1.SetLine();
		LH_VENTS_8_AND_9_PURGE_IND_2.SetLine();
		LH_VENTS_8_AND_9_OPEN_1.ResetLine();
		LH_VENTS_8_AND_9_OPEN_2.ResetLine();

		if (posLH89 == 0.0)// CL
		{
			LH_VENTS_8_AND_9_CLOSE_1.SetLine();
			LH_VENTS_8_AND_9_CLOSE_2.SetLine();
			
		}
		else
		{
			LH_VENTS_8_AND_9_CLOSE_1.ResetLine();
			LH_VENTS_8_AND_9_CLOSE_2.ResetLine();
		}
	}
	else
	{
		LH_VENTS_8_AND_9_PURGE_IND_1.ResetLine();
		LH_VENTS_8_AND_9_PURGE_IND_2.ResetLine();
		LH_VENTS_8_AND_9_CLOSE_1.ResetLine();
		LH_VENTS_8_AND_9_CLOSE_2.ResetLine();

		if (posLH89 == 1.0)// OP
		{
			LH_VENTS_8_AND_9_OPEN_1.SetLine();
			LH_VENTS_8_AND_9_OPEN_2.SetLine();
		}
		else
		{
			LH_VENTS_8_AND_9_OPEN_1.ResetLine();
			LH_VENTS_8_AND_9_OPEN_2.ResetLine();
		}
	}

	if (posRH12 <= DOOR12_PURGE_1_POS)// PG
	{
		R_VENTS_1_AND_2_PURGE_1_IND_1.SetLine();
		R_VENTS_1_AND_2_PURGE_1_IND_2.SetLine();
		R_VENTS_1_AND_2_OPEN_1.ResetLine();
		R_VENTS_1_AND_2_OPEN_2.ResetLine();

		if (posRH12 == 0.0)// CL
		{
			R_VENTS_1_AND_2_CLOSE_1.SetLine();
			R_VENTS_1_AND_2_CLOSE_2.SetLine();
			
		}
		else
		{
			R_VENTS_1_AND_2_CLOSE_1.ResetLine();
			R_VENTS_1_AND_2_CLOSE_2.ResetLine();
		}
	}
	else
	{
		R_VENTS_1_AND_2_PURGE_1_IND_1.ResetLine();
		R_VENTS_1_AND_2_PURGE_1_IND_2.ResetLine();
		R_VENTS_1_AND_2_CLOSE_1.ResetLine();
		R_VENTS_1_AND_2_CLOSE_2.ResetLine();

		if (posRH12 == 1.0)// OP
		{
			R_VENTS_1_AND_2_OPEN_1.SetLine();
			R_VENTS_1_AND_2_OPEN_2.SetLine();
		}
		else
		{
			R_VENTS_1_AND_2_OPEN_1.ResetLine();
			R_VENTS_1_AND_2_OPEN_2.ResetLine();
		}
	}

	if (posRH3 == 0.0)// CL
	{
		RH_VENT_3_CLOSE_1.SetLine();
		RH_VENT_3_CLOSE_2.SetLine();
		RH_VENT_3_OPEN_1.ResetLine();
		RH_VENT_3_OPEN_2.ResetLine();
	}
	else if (posRH3 == 1.0)// OP
	{
		RH_VENT_3_CLOSE_1.ResetLine();
		RH_VENT_3_CLOSE_2.ResetLine();
		RH_VENT_3_OPEN_1.SetLine();
		RH_VENT_3_OPEN_2.SetLine();
	}
	else
	{
		RH_VENT_3_CLOSE_1.ResetLine();
		RH_VENT_3_CLOSE_2.ResetLine();
		RH_VENT_3_OPEN_1.ResetLine();
		RH_VENT_3_OPEN_2.ResetLine();
	}

	if (hasVentDoor47)
	{
		if (posRH47 == 0.0)// CL
		{
			RH_VENTS_4_AND_7_CLOSE_1.SetLine();
			RH_VENTS_4_AND_7_CLOSE_2.SetLine();
			RH_VENTS_4_AND_7_OPEN_1.ResetLine();
			RH_VENTS_4_AND_7_OPEN_2.ResetLine();
		}
		else if (posRH47 == 1.0)// OP
		{
			RH_VENTS_4_AND_7_CLOSE_1.ResetLine();
			RH_VENTS_4_AND_7_CLOSE_2.ResetLine();
			RH_VENTS_4_AND_7_OPEN_1.SetLine();
			RH_VENTS_4_AND_7_OPEN_2.SetLine();
		}
		else
		{
			RH_VENTS_4_AND_7_CLOSE_1.ResetLine();
			RH_VENTS_4_AND_7_CLOSE_2.ResetLine();
			RH_VENTS_4_AND_7_OPEN_1.ResetLine();
			RH_VENTS_4_AND_7_OPEN_2.ResetLine();
		}
	}

	if (posRH5 == 0.0)// CL
	{
		RH_VENT_5_CLOSE_1.SetLine();
		RH_VENT_5_CLOSE_2.SetLine();
		RH_VENT_5_OPEN_1.ResetLine();
		RH_VENT_5_OPEN_2.ResetLine();
	}
	else if (posRH5 == 1.0)// OP
	{
		RH_VENT_5_CLOSE_1.ResetLine();
		RH_VENT_5_CLOSE_2.ResetLine();
		RH_VENT_5_OPEN_1.SetLine();
		RH_VENT_5_OPEN_2.SetLine();
	}
	else
	{
		RH_VENT_5_CLOSE_1.ResetLine();
		RH_VENT_5_CLOSE_2.ResetLine();
		RH_VENT_5_OPEN_1.ResetLine();
		RH_VENT_5_OPEN_2.ResetLine();
	}

	if (posRH6 <= DOOR6_PURGE_1_POS)// PG 1
	{
		RH_VENT_6_PURGE_1_IND_1.SetLine();
		RH_VENT_6_PURGE_1_IND_2.SetLine();
		RH_VENT_6_PURGE_2_IND_1.ResetLine();
		RH_VENT_6_PURGE_2_IND_2.ResetLine();
		RH_VENT_6_OPEN_1.ResetLine();
		RH_VENT_6_OPEN_2.ResetLine();

		if (posRH6 == 0.0)// CL
		{
			RH_VENT_6_CLOSE_1.SetLine();
			RH_VENT_6_CLOSE_2.SetLine();
			
		}
		else
		{
			RH_VENT_6_CLOSE_1.ResetLine();
			RH_VENT_6_CLOSE_2.ResetLine();
		}
	}
	else if (posRH6 >= DOOR6_PURGE_2_POS)// PG 2
	{
		RH_VENT_6_PURGE_1_IND_1.ResetLine();
		RH_VENT_6_PURGE_1_IND_2.ResetLine();
		RH_VENT_6_PURGE_2_IND_1.SetLine();
		RH_VENT_6_PURGE_2_IND_2.SetLine();
		RH_VENT_6_CLOSE_1.ResetLine();
		RH_VENT_6_CLOSE_2.ResetLine();

		if (posRH6 == 1.0)// OP
		{
			RH_VENT_6_OPEN_1.SetLine();
			RH_VENT_6_OPEN_2.SetLine();
			
		}
		else
		{
			RH_VENT_6_OPEN_1.ResetLine();
			RH_VENT_6_OPEN_2.ResetLine();
		}
	}
	else
	{
		RH_VENT_6_PURGE_1_IND_1.ResetLine();
		RH_VENT_6_PURGE_1_IND_2.ResetLine();
		RH_VENT_6_PURGE_2_IND_1.ResetLine();
		RH_VENT_6_PURGE_2_IND_2.ResetLine();
		RH_VENT_6_CLOSE_1.ResetLine();
		RH_VENT_6_CLOSE_2.ResetLine();
		RH_VENT_6_OPEN_1.ResetLine();
		RH_VENT_6_OPEN_2.ResetLine();
	}

	if (posRH89 <= DOOR89_PURGE_1_POS)// PG
	{
		RH_VENTS_8_AND_9_PURGE_IND_1.SetLine();
		RH_VENTS_8_AND_9_PURGE_IND_2.SetLine();
		RH_VENTS_8_AND_9_OPEN_1.ResetLine();
		RH_VENTS_8_AND_9_OPEN_2.ResetLine();

		if (posRH89 == 0.0)// CL
		{
			RH_VENTS_8_AND_9_CLOSE_1.SetLine();
			RH_VENTS_8_AND_9_CLOSE_2.SetLine();
			
		}
		else
		{
			RH_VENTS_8_AND_9_CLOSE_1.ResetLine();
			RH_VENTS_8_AND_9_CLOSE_2.ResetLine();
		}
	}
	else
	{
		RH_VENTS_8_AND_9_PURGE_IND_1.ResetLine();
		RH_VENTS_8_AND_9_PURGE_IND_2.ResetLine();
		RH_VENTS_8_AND_9_CLOSE_1.ResetLine();
		RH_VENTS_8_AND_9_CLOSE_2.ResetLine();

		if (posRH89 == 1.0)// OP
		{
			RH_VENTS_8_AND_9_OPEN_1.SetLine();
			RH_VENTS_8_AND_9_OPEN_2.SetLine();
		}
		else
		{
			RH_VENTS_8_AND_9_OPEN_1.ResetLine();
			RH_VENTS_8_AND_9_OPEN_2.ResetLine();
		}
	}
	return;
}

void VentDoors::SetAnimations( void )
{
	STS()->SetAnimation( anim_LH1, posLH12 );
	STS()->SetAnimation( anim_LH2, posLH12 );
	STS()->SetAnimation( anim_LH3, posLH3 );
	if (hasVentDoor47) STS()->SetAnimation( anim_LH4, posLH47 );
	STS()->SetAnimation( anim_LH5, posLH5 );
	STS()->SetAnimation( anim_LH6, posLH6 );
	if (hasVentDoor47) STS()->SetAnimation( anim_LH7, posLH47 );
	STS()->SetAnimation( anim_LH8, posLH89 );
	STS()->SetAnimation( anim_LH9, posLH89 );

	STS()->SetAnimation( anim_RH1, posRH12 );
	STS()->SetAnimation( anim_RH2, posRH12 );
	STS()->SetAnimation( anim_RH3, posRH3 );
	if (hasVentDoor47) STS()->SetAnimation( anim_RH4, posRH47 );
	STS()->SetAnimation( anim_RH5, posRH5 );
	STS()->SetAnimation( anim_RH6, posRH6 );
	if (hasVentDoor47) STS()->SetAnimation( anim_RH7, posRH47 );
	STS()->SetAnimation( anim_RH8, posRH89 );
	STS()->SetAnimation( anim_RH9, posRH89 );
	return;
}
