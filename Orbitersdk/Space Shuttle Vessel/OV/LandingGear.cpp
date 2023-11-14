/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/02/16   GLS
2021/02/21   GLS
2021/02/28   GLS
2021/04/15   GLS
2021/06/13   GLS
2021/07/07   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
2022/08/21   GLS
2023/09/03   GLS
2023/11/14   GLS
********************************************/
#include "LandingGear.h"
#include "Atlantis.h"
#include "meshres.h"
#include <MathSSV.h>
#include <cassert>


constexpr double GEAR_CLOSED_POS = 0.0;// [deg]
constexpr double NLG_OPEN_POS = 108.0;// [deg]
constexpr double MLG_OPEN_POS = 98.0;// [deg]
constexpr double GEAR_RATE = 35.0;// [deg/s]

const VECTOR3 NW_POSITION = _V( 0.0, -5.1, 14.9 );// [m]
constexpr double NWS_MAX = 12.0;// [deg]
constexpr double NWS_MAX_RT = 20.0;// [deg/s]


const VECTOR3 MLG_REF = _V( 0.0, -3.3989, -5.733 );
const VECTOR3 MLG_AXIS = _V( 1.0, 0.0, 0.0 );
const float MLG_ANGLE = static_cast<float>(98.0 * RAD);

const VECTOR3 MLG_DOOR_LEFT_REF = _V( -4.445, -3.48839, -4.041237 );
const VECTOR3 MLG_DOOR_RIGHT_REF = _V( 4.445, -3.48839, -4.041237 );
const VECTOR3 MLG_DOOR_AXIS = _V( 0.0, -0.0436194, -0.999048 );
const float MLG_DOOR_ANGLE = static_cast<float>(88.0 * RAD);

const VECTOR3 NLG_REF = _V( 0.0, -3.0179, 14.7013 );
const VECTOR3 NLG_AXIS = _V( 1.0, 0.0, 0.0 );
const float NLG_ANGLE = static_cast<float>(110.25 * RAD);

const VECTOR3 NLG_DOOR_LEFT_REF = _V( -0.7239, -2.86, 16.156982 );
const VECTOR3 NLG_DOOR_LEFT_AXIS = _V( 0.0, -0.258819, -0.965926 );
const float NLG_DOOR_LEFT_ANGLE = static_cast<float>(66.0 * RAD);

const VECTOR3 NLG_DOOR_RIGHT_REF = _V( 0.7239, -2.86, 16.156982 );
const VECTOR3 NLG_DOOR_RIGHT_AXIS = _V( 0.0, 0.258819, 0.965926 );
const float NLG_DOOR_RIGHT_ANGLE = static_cast<float>(58.0 * RAD);


LandingGear::LandingGear( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "LandingGear" )
{
	Arm = false;
	Down = false;

	NLG = 0.0;
	LMG = 0.0;
	RMG = 0.0;

	NLG_NoWOW = true;
	LMG_NoWOW = true;
	RMG_NoWOW = true;

	NWSpos = 0.0;

	STS()->SetMaxWheelbrakeForce( 100000.0 );// per wheel (based on ~10fps deceleration)
	return;
}

LandingGear::~LandingGear( void )
{
}

bool LandingGear::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "ARM", 3 ))
	{
		int tmp = 0;
		sscanf_s( line + 3, "%d", &tmp );
		Arm = (tmp != 0);
	}
	else if (!_strnicmp( line, "DOWN", 4 ))
	{
		int tmp = 0;
		sscanf_s( line + 4, "%d", &tmp );
		Down = (tmp != 0);
	}
	else if (!_strnicmp( line, "NLG", 3 ))
	{
		sscanf_s( line + 3, "%lf", &NLG );
		NLG = range( GEAR_CLOSED_POS, NLG, NLG_OPEN_POS );
	}
	else if (!_strnicmp( line, "LMG", 3 ))
	{
		sscanf_s( line + 3, "%lf", &LMG );
		LMG = range( GEAR_CLOSED_POS, LMG, MLG_OPEN_POS );
	}
	else if (!_strnicmp( line, "RMG", 3 ))
	{
		sscanf_s( line + 3, "%lf", &RMG );
		RMG = range( GEAR_CLOSED_POS, RMG, MLG_OPEN_POS );
	}
	else if (!_strnicmp( line, "NOWOW_NLG", 9 ))
	{
		int tmp = 0;
		sscanf_s( line + 9, "%d", &tmp );
		NLG_NoWOW = (tmp != 0);
	}
	else if (!_strnicmp( line, "NOWOW_LMG", 9 ))
	{
		int tmp = 0;
		sscanf_s( line + 9, "%d", &tmp );
		LMG_NoWOW = (tmp != 0);
	}
	else if (!_strnicmp( line, "NOWOW_RMG", 9 ))
	{
		int tmp = 0;
		sscanf_s( line + 9, "%d", &tmp );
		RMG_NoWOW = (tmp != 0);
	}
	else return false;

	return true;
}

void LandingGear::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_int( scn, "ARM", Arm ? 1 : 0 );
	oapiWriteScenario_int( scn, "DOWN", Down ? 1 : 0 );
	oapiWriteScenario_float( scn, "NLG", NLG );
	oapiWriteScenario_float( scn, "LMG", LMG );
	oapiWriteScenario_float( scn, "RMG", RMG );
	oapiWriteScenario_int( scn, "NOWOW_NLG", NLG_NoWOW ? 1 : 0 );
	oapiWriteScenario_int( scn, "NOWOW_LMG", LMG_NoWOW ? 1 : 0 );
	oapiWriteScenario_int( scn, "NOWOW_RMG", RMG_NoWOW ? 1 : 0 );
	return;
}

void LandingGear::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "LANDING_GEAR", 16 );
	dipArm[0].Connect( pBundle, 0 );
	dipArm[1].Connect( pBundle, 1 );
	dipDeploy[0].Connect( pBundle, 2 );
	dipDeploy[1].Connect( pBundle, 3 );
	dipReset.Connect( pBundle, 4 );
	dopLG_NOSE_UP.Connect( pBundle, 5 );
	dopLG_NOSE_DN.Connect( pBundle, 6 );
	dopLG_LEFT_UP.Connect( pBundle, 7 );
	dopLG_LEFT_DN.Connect( pBundle, 8 );
	dopLG_RIGHT_UP.Connect( pBundle, 9 );
	dopLG_RIGHT_DN.Connect( pBundle, 10 );

	//dopLMG_DOWN.Connect( pBundle, 99 );// OF2
	//dopLMGDOOR_UP.Connect( pBundle, 99 );// OF2
	//dopRMG_DOWN.Connect( pBundle, 99 );// OF3
	//dopRMGDOOR_UP.Connect( pBundle, 99 );// OF3
	//dopNLG_DOWN.Connect( pBundle, 99 );// OF2
	//dopNLGDOOR_UP.Connect( pBundle, 99 );// OF2

	pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM12_CH0", 16 );
	dopNLG_NO_WOW_2.Connect( pBundle, 11 );
	dopNLG_UP.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF2_IOM12_CH2", 16 );
	dopLMG_NO_WOW.Connect( pBundle, 9 );
	dopLMG_UP.Connect( pBundle, 10 );
	dopRMG_DOOR_UP.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM12_CH0", 16 );
	dopNLG_NO_WOW_1.Connect( pBundle, 13 );
	dopNLG_DOOR_UP.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "MDM_FF3_IOM12_CH2", 16 );
	dopRMG_NO_WOW.Connect( pBundle, 9 );
	dopRMG_UP.Connect( pBundle, 10 );
	dopLMG_DOOR_UP.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "ACA2_2", 16 );
	dopAntiSkidFail.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "ACA2_5", 16 );
	dopArm[1].Connect( pBundle, 6 );
	dopDown[1].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA3_4", 16 );
	dopArm[0].Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "ACA3_5", 16 );
	dopDown[0].Connect( pBundle, 0 );
	dopNWSFail.Connect( pBundle, 4 );

	pBundle = BundleManager()->CreateBundle( "BRAKES", 16 );
	dipBrakesMNA.Connect( pBundle, 0 );
	dipBrakesMNB.Connect( pBundle, 1 );
	dipBrakesMNC.Connect( pBundle, 2 );
	dipAntiSkid.Connect( pBundle, 3 );

	pBundle = BundleManager()->CreateBundle( "NWS", 16 );
	dipNWSMNA.Connect( pBundle, 0 );
	dipNWSMNB.Connect( pBundle, 1 );
	dipNWS1.Connect( pBundle, 2 );
	dipNWS2.Connect( pBundle, 3 );
	dipNWS1_CMPTR_CMD.Connect( pBundle, 4 );
	dipNWS2_CMPTR_CMD.Connect( pBundle, 5 );
	dipNWS1_ENABLE_A_CMD.Connect( pBundle, 6 );
	dipNWS1_ENABLE_B_CMD.Connect( pBundle, 7 );
	dipNWS2_ENABLE_A_CMD.Connect( pBundle, 8 );
	dipNWS2_ENABLE_B_CMD.Connect( pBundle, 9 );
	dopNWS_POS_A.Connect( pBundle, 10 );
	dopNWS_POS_B.Connect( pBundle, 11 );
	dopNWS_POS_C.Connect( pBundle, 12 );
	dopNWS1_ACT.Connect( pBundle, 13 );
	dopNWS2_ACT.Connect( pBundle, 14 );
	dipNW_POSN_ERROR.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "DDU_POWER", 16 );
	dipDDU2PowerSupply.Connect( pBundle, 7 );

	AddAnimation();

	SetLandingGearPosition();
	SetDigitals();
	return;
}

void LandingGear::AddAnimation( void )
{
	// assume doors open in the initial ~10º of gear motion

	static UINT LNosewheelDoorGrp[2] = {GRP_NLG_DOOR_LEFT_EXTERIOR, GRP_NLG_DOOR_LEFT_INTERIOR};
	MGROUP_ROTATE* LNosewheelDoor = new MGROUP_ROTATE( STS()->OVmesh(), LNosewheelDoorGrp, 2, NLG_DOOR_LEFT_REF, NLG_DOOR_LEFT_AXIS, NLG_DOOR_LEFT_ANGLE );
	static UINT RNosewheelDoorGrp[2] = {GRP_NLG_DOOR_RIGHT_EXTERIOR, GRP_NLG_DOOR_RIGHT_INTERIOR};
	MGROUP_ROTATE* RNosewheelDoor = new MGROUP_ROTATE( STS()->OVmesh(), RNosewheelDoorGrp, 2, NLG_DOOR_RIGHT_REF, NLG_DOOR_RIGHT_AXIS, NLG_DOOR_RIGHT_ANGLE );
	static UINT NosewheelGrp[6] = {GRP_NLG_STRUT, GRP_NLG_SHOCK_STRUT, GRP_NLG_TORQUE_ARM_UPPER, GRP_NLG_TORQUE_ARM_LOWER, GRP_NLG_TIRES, GRP_NLG_RIMS};
	MGROUP_ROTATE* Nosewheel = new MGROUP_ROTATE( STS()->OVmesh(), NosewheelGrp, 6, NLG_REF, NLG_AXIS, NLG_ANGLE );
	anim_nosegear = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_nosegear, 0.0, 0.1, LNosewheelDoor );
	STS()->AddAnimationComponent( anim_nosegear, 0.0, 0.1, RNosewheelDoor );
	STS()->AddAnimationComponent( anim_nosegear, 0.0, 1.0, Nosewheel );
	SaveAnimation( LNosewheelDoor );
	SaveAnimation( RNosewheelDoor );
	SaveAnimation( Nosewheel );

	static UINT LGearDoorGrp[2] = {GRP_MLG_LEFT_DOOR_EXTERIOR, GRP_MLG_LEFT_DOOR_INTERIOR};
	MGROUP_ROTATE* LGearDoor = new MGROUP_ROTATE( STS()->OVmesh(), LGearDoorGrp, 2, MLG_DOOR_LEFT_REF, MLG_DOOR_AXIS, MLG_DOOR_ANGLE );
	static UINT LMainGearGrp[5] = {GRP_MLG_LEFT_STRUT, GRP_MLG_LEFT_STRUT_SILVER, GRP_MLG_LEFT_SHOCK_STRUT, GRP_MLG_LEFT_RIMS, GRP_MLG_LEFT_TIRES};
	MGROUP_ROTATE* LMainGear = new MGROUP_ROTATE( STS()->OVmesh(), LMainGearGrp, 5, MLG_REF, MLG_AXIS, MLG_ANGLE );
	anim_leftgear = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_leftgear, 0.0, 0.1, LGearDoor );
	STS()->AddAnimationComponent( anim_leftgear, 0.0, 1.0, LMainGear );
	SaveAnimation( LGearDoor );
	SaveAnimation( LMainGear );

	static UINT RGearDoorGrp[2] = {GRP_MLG_RIGHT_DOOR_EXTERIOR, GRP_MLG_RIGHT_DOOR_INTERIOR};
	MGROUP_ROTATE* RGearDoor = new MGROUP_ROTATE( STS()->OVmesh(), RGearDoorGrp, 2, MLG_DOOR_RIGHT_REF, MLG_DOOR_AXIS, -MLG_DOOR_ANGLE );
	static UINT RMainGearGrp[5] = {GRP_MLG_RIGHT_STRUT, GRP_MLG_RIGHT_STRUT_SILVER, GRP_MLG_RIGHT_SHOCK_STRUT, GRP_MLG_RIGHT_RIMS, GRP_MLG_RIGHT_TIRES};
	MGROUP_ROTATE* RMainGear = new MGROUP_ROTATE( STS()->OVmesh(), RMainGearGrp, 5, MLG_REF, MLG_AXIS, MLG_ANGLE );
	anim_rightgear = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_rightgear, 0.0, 0.1, RGearDoor );
	STS()->AddAnimationComponent( anim_rightgear, 0.0, 1.0, RMainGear );
	SaveAnimation( RGearDoor );
	SaveAnimation( RMainGear );
	return;
}

void LandingGear::OnPostStep( double simt, double simdt, double mjd )
{
	// gear logic
	Arm = (!dipReset && Arm) || ((dipArm[0] || dipArm[1]) && !dipReset) || ((dipArm[0] || dipArm[1]) && Arm);
	Down = (!dipReset && Down) + ((dipDeploy[0] || dipDeploy[1]) && Arm && !dipReset) + ((dipDeploy[0] || dipDeploy[1]) && Arm && Down);

	if (Down)
	{
		NLG = min(NLG_OPEN_POS, NLG + (simdt * GEAR_RATE));
		LMG = min(MLG_OPEN_POS, LMG + (simdt * GEAR_RATE));
		RMG = min(MLG_OPEN_POS, RMG + (simdt * GEAR_RATE));
	}

	// set gear physical and visual outputs
	SetLandingGearPosition();

	// weight on wheels
	if ((NLG == NLG_OPEN_POS) && (STS()->GroundContact()) && (STS()->GetPitch() < (-3.5 * RAD))) NLG_NoWOW = false;
	else NLG_NoWOW = true;

	if ((LMG == MLG_OPEN_POS) && STS()->GroundContact()) LMG_NoWOW = false;
	else LMG_NoWOW = true;

	if ((RMG == MLG_OPEN_POS) && STS()->GroundContact()) RMG_NoWOW = false;
	else RMG_NoWOW = true;

	// brakes
	Brakes();

	// NWS
	NWS( simdt );

	// set digital outputs
	SetDigitals();
	return;
}


void LandingGear::Brakes( void )
{
	bool VbrakeCA = dipBrakesMNC.IsSet() || dipBrakesMNA.IsSet();
	bool VbrakeBC = dipBrakesMNB.IsSet() || dipBrakesMNC.IsSet();
	bool VantiskidCA = dipAntiSkid.IsSet() && VbrakeCA;
	bool VantiskidBC = dipAntiSkid.IsSet() && VbrakeBC;

	bool TouchdownProtection = (VantiskidCA || VantiskidBC) && ((VbrakeCA || VbrakeBC) && (NLG_NoWOW && LMG_NoWOW && RMG_NoWOW));

	bool AntiSkidFail = !dipAntiSkid.IsSet() && VbrakeBC;
	// HACK anti-skid fail light
	dopAntiSkidFail.SetLine( 5.0f * static_cast<int>(AntiSkidFail) );

	double LeftBrakeCommand = 0.0;
	double RightBrakeCommand = 0.0;
	if (VbrakeCA || VbrakeBC)
	{
		double CDRLeft = 0.0;
		double CDRRight = 0.0;
		double PLTLeft = 0.0;
		double PLTRight = 0.0;

		STS()->GetBrakePosition( CDRLeft, CDRRight, PLTLeft, PLTRight );

		// HACK added factor to control brake effectiveness
		LeftBrakeCommand = range( 0.0, max(CDRLeft, PLTLeft), 1.0 ) * 0.2;
		RightBrakeCommand = range( 0.0, max(CDRRight, PLTRight), 1.0 ) * 0.2;
	}

	if (STS()->HydraulicsOK() && !TouchdownProtection)
	{
		STS()->SetWheelbrakeLevel( LeftBrakeCommand, 1, false );
		STS()->SetWheelbrakeLevel( RightBrakeCommand, 2, false );
	}
	return;
}

void LandingGear::NWS( double dt )
{
	bool NWS1_PWR = dipNWSMNA.IsSet() && dipNWS1.IsSet();
	bool NWS2_PWR = dipNWSMNB.IsSet() && dipNWS2.IsSet();

	// steering engaged valve
	bool SteeringEngagedValve = true;// true = closed
	if ((dipNWS1_ENABLE_A_CMD.IsSet() || dipNWS2_ENABLE_A_CMD.IsSet()) && (dipNWS1_ENABLE_B_CMD.IsSet() || dipNWS2_ENABLE_B_CMD.IsSet()))
	{
		if (STS()->HydraulicsOK()) SteeringEngagedValve = false;
	}

	if (!SteeringEngagedValve)
	{
		dopNWS1_ACT.SetLine( 5.0f * static_cast<int>(NWS1_PWR) );
		dopNWS2_ACT.SetLine( 5.0f * static_cast<int>(NWS2_PWR) );
	}
	else
	{
		dopNWS1_ACT.ResetLine();
		dopNWS2_ACT.ResetLine();
	}

	// HACK NWS Fail light
	if (dipNW_POSN_ERROR.IsSet() ||
		((dipNWS1.IsSet() && ((dipNWS1_ENABLE_A_CMD.IsSet() || dipNWS1_ENABLE_B_CMD.IsSet()) && SteeringEngagedValve)) ||
		(dipNWS2.IsSet() && ((dipNWS2_ENABLE_A_CMD.IsSet() || dipNWS2_ENABLE_B_CMD.IsSet()) && SteeringEngagedValve))))
			dopNWSFail.SetLine();
	else dopNWSFail.ResetLine();

	// set command
	double cmd = 0.0;
	if (SteeringEngagedValve) cmd = 0.0;// HACK without hydraulics or with pilot valves closed, set cmd to 0 to return wheels to neutral
	else if (NWS1_PWR) cmd = dipNWS1_CMPTR_CMD.GetVoltage() * (11.2 / 5.0);
	else if (NWS2_PWR) cmd = dipNWS2_CMPTR_CMD.GetVoltage() * (11.2 / 5.0);

	NWSpos = range( -NWS_MAX, range( NWSpos - (dt * NWS_MAX_RT), cmd, NWSpos + (dt * NWS_MAX_RT) ), NWS_MAX );

	// set physical effect, only after nose wheel is down
	if (!NLG_NoWOW)
	{
		double steerforce = min(50000.0, 50000.0 * (STS()->GetGroundspeed() / 90.0)) * NWSpos;
		if (fabs( steerforce ) >= 500.0)// HACK deadband so vessel can stop
			STS()->AddForce( _V( steerforce, 0.0, 0.0 ), NW_POSITION );// TODO force orthogonal to wheels?
	}

	// set position output
	if (dipDDU2PowerSupply.IsSet())
	{
		// 1 degree bias to the left
		dopNWS_POS_A.SetLine( static_cast<float>(range( -5.0, (-NWSpos - 1.0) * (5.0 / 12.0), 5.0 )) );
		dopNWS_POS_B.SetLine( static_cast<float>(range( -5.0, (-NWSpos - 1.0) * (5.0 / 12.0), 5.0 )) );
		dopNWS_POS_C.SetLine( static_cast<float>(range( -5.0, (-NWSpos - 1.0) * (5.0 / 12.0), 5.0 )) );
	}
	else
	{
		dopNWS_POS_A.ResetLine();
		dopNWS_POS_B.ResetLine();
		dopNWS_POS_C.ResetLine();
	}
	return;
}

void LandingGear::SetLandingGearPosition( void )
{
	if (STS()->aerosurfaces.LandingGear == LMG) return;// HACK if no change, don't set touchdown points as it prevents vessel changing to landed state

	// set physical effects
	// aero
	STS()->aerosurfaces.LandingGear = LMG;// HACK not sure how gear aero is implemented (is data for each gear, or all 3?)

	// touchdown points
	STS()->DefineTouchdownPoints();

	// set visual effects
	STS()->SetAnimation( anim_nosegear, range( 0.0, NLG / 108.0, 1.0 ) );
	STS()->SetAnimation( anim_leftgear, range( 0.0, LMG / 98.0, 1.0 ) );
	STS()->SetAnimation( anim_rightgear, range( 0.0, RMG / 98.0, 1.0 ) );
	return;
}

void LandingGear::SetDigitals( void )
{
	// set arm and down indications
	dopArm[0].SetLine( 28.0f * static_cast<int>(Arm) );
	dopArm[1].SetLine( 28.0f * static_cast<int>(Arm) );
	dopDown[0].SetLine( 28.0f * static_cast<int>(Down) );
	dopDown[1].SetLine( 28.0f * static_cast<int>(Down) );

	// set up/down lock indications
	if (NLG == GEAR_CLOSED_POS)
	{
		dopLG_NOSE_UP.SetLine( 28.0f );
		dopLG_NOSE_DN.ResetLine();

		dopNLG_UP.SetLine( 28.0f );
		dopNLG_DOOR_UP.SetLine( 28.0f );
		dopNLGDOOR_UP.SetLine( 28.0f );
		dopNLG_DOWN.ResetLine();
	}
	else if (NLG == NLG_OPEN_POS)
	{
		dopLG_NOSE_UP.ResetLine();
		dopLG_NOSE_DN.SetLine( 28.0f );

		dopNLG_UP.ResetLine();
		dopNLG_DOOR_UP.ResetLine();
		dopNLGDOOR_UP.ResetLine();
		dopNLG_DOWN.SetLine( 28.0f );
	}
	else
	{
		dopLG_NOSE_UP.ResetLine();
		dopLG_NOSE_DN.ResetLine();

		dopNLG_UP.ResetLine();
		dopNLG_DOOR_UP.ResetLine();
		dopNLGDOOR_UP.ResetLine();
		dopNLG_DOWN.ResetLine();
	}

	// MLG door up logic is reversed
	if (LMG == GEAR_CLOSED_POS)
	{
		dopLG_LEFT_UP.SetLine( 28.0f );
		dopLG_LEFT_DN.ResetLine();

		dopLMG_UP.SetLine( 28.0f );
		dopLMG_DOOR_UP.ResetLine();
		dopLMGDOOR_UP.SetLine( 28.0f );
		dopLMG_DOWN.ResetLine();
	}
	else if (LMG == MLG_OPEN_POS)
	{
		dopLG_LEFT_UP.ResetLine();
		dopLG_LEFT_DN.SetLine( 28.0f );

		dopLMG_UP.ResetLine();
		dopLMG_DOOR_UP.SetLine( 28.0f );
		dopLMGDOOR_UP.ResetLine();
		dopLMG_DOWN.SetLine( 28.0f );
	}
	else
	{
		dopLG_LEFT_UP.ResetLine();
		dopLG_LEFT_DN.ResetLine();

		dopLMG_UP.ResetLine();
		dopLMG_DOOR_UP.SetLine( 28.0f );
		dopLMGDOOR_UP.ResetLine();
		dopLMG_DOWN.ResetLine();
	}

	if (RMG == GEAR_CLOSED_POS)
	{
		dopLG_RIGHT_UP.SetLine( 28.0f );
		dopLG_RIGHT_DN.ResetLine();

		dopRMG_UP.SetLine( 28.0f );
		dopRMG_DOOR_UP.ResetLine();
		dopRMGDOOR_UP.SetLine( 28.0f );
		dopRMG_DOWN.ResetLine();
	}
	else if (RMG == MLG_OPEN_POS)
	{
		dopLG_RIGHT_UP.ResetLine();
		dopLG_RIGHT_DN.SetLine( 28.0f );

		dopRMG_UP.ResetLine();
		dopRMG_DOOR_UP.SetLine( 28.0f );
		dopRMGDOOR_UP.ResetLine();
		dopRMG_DOWN.SetLine( 28.0f );
	}
	else
	{
		dopLG_RIGHT_UP.ResetLine();
		dopLG_RIGHT_DN.ResetLine();

		dopRMG_UP.ResetLine();
		dopRMG_DOOR_UP.SetLine( 28.0f );
		dopRMGDOOR_UP.ResetLine();
		dopRMG_DOWN.ResetLine();
	}

	// weight on wheels indications
	dopNLG_NO_WOW_1.SetLine( 28.0f * static_cast<int>(NLG_NoWOW) );
	dopNLG_NO_WOW_2.SetLine( 28.0f * static_cast<int>(NLG_NoWOW) );
	dopLMG_NO_WOW.SetLine( 28.0f * static_cast<int>(LMG_NoWOW) );
	dopRMG_NO_WOW.SetLine( 28.0f * static_cast<int>(RMG_NoWOW) );
	return;
}
