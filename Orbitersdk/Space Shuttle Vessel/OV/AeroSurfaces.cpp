/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/01/11   GLS
2021/01/18   GLS
2021/01/20   GLS
2021/01/23   GLS
2021/01/24   GLS
2021/01/25   GLS
2021/03/18   GLS
2021/06/13   GLS
2021/07/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
2022/11/09   GLS
********************************************/
#include "AeroSurfaces.h"
#include "Atlantis.h"
#include "meshres.h"
#include <MathSSV.h>
#include <cassert>


// ============================================================
// Elevon animation constants
// ============================================================
const VECTOR3 ELEVON_LOB_REF = _V( -7.966055, -3.211068, -10.9908 );
const VECTOR3 ELEVON_LOB_AXIS = _V( -0.995805, 0.0915016, 0.0 );
const VECTOR3 ELEVON_LIB_REF = _V( -7.838518, -3.223475, -10.9908 );
const VECTOR3 ELEVON_LIB_AXIS = _V( -0.995963, 0.0897635, 0.0 );
const VECTOR3 ELEVON_RIB_REF = _V( 7.838518, -3.223475, -10.9908 );
const VECTOR3 ELEVON_RIB_AXIS = _V( -0.995963, -0.0897635, 0.0 );
const VECTOR3 ELEVON_ROB_REF = _V( 7.966055, -3.211068, -10.9908 );
const VECTOR3 ELEVON_ROB_AXIS = _V( -0.995805, -0.0915016, 0.0 );

constexpr double ELEVON_MECH_MIN = -36.5;
constexpr double ELEVON_MECH_MAX = 21.5;
constexpr double ELEVON_MECH_RANGE = ELEVON_MECH_MAX - ELEVON_MECH_MIN;

constexpr double ELEVON_CMD_MIN = -36.5;
constexpr double ELEVON_CMD_MAX = 21.3;
constexpr double ELEVON_CMD_RANGE = ELEVON_CMD_MAX - ELEVON_CMD_MIN;

constexpr double ELEVON_POS_FA_IB_MIN = -36.5;
constexpr double ELEVON_POS_FA_IB_MAX = 21.3;
constexpr double ELEVON_POS_FA_IB_RANGE = ELEVON_POS_FA_IB_MAX - ELEVON_POS_FA_IB_MIN;

constexpr double ELEVON_POS_FA_OB_MIN = -36.5;
constexpr double ELEVON_POS_FA_OB_MAX = 21.1;
constexpr double ELEVON_POS_FA_OB_RANGE = ELEVON_POS_FA_OB_MAX - ELEVON_POS_FA_OB_MIN;

constexpr double ELEVON_POS_OA_MIN = -36.5;
constexpr double ELEVON_POS_OA_MAX = 21.5;
constexpr double ELEVON_POS_OA_RANGE = ELEVON_POS_OA_MAX - ELEVON_POS_OA_MIN;


const VECTOR3 ELEVON_SEALPANEL_LOB_REF = _V( -7.939413, -2.737573, -10.54452 );
const VECTOR3 ELEVON_SEALPANEL_LOB_AXIS = _V( -0.99912, 0.041963, 0.0 );

const VECTOR3 ELEVON_SEALPANEL_LIB_REF = _V( -7.809792, -2.743635, -10.54452 );
const VECTOR3 ELEVON_SEALPANEL_LIB_AXIS = _V( -0.99905, 0.043619, 0.0 );

const VECTOR3 ELEVON_SEALPANEL_RIB_REF = _V( 7.809792, -2.743635, -10.54452 );
const VECTOR3 ELEVON_SEALPANEL_RIB_AXIS = _V( -0.99905, -0.043619, 0.0 );

const VECTOR3 ELEVON_SEALPANEL_ROB_REF = _V( 7.939413, -2.737573, -10.54452 );
const VECTOR3 ELEVON_SEALPANEL_ROB_AXIS = _V( -0.99912, -0.041963, 0.0 );



// ============================================================
// Rudder/Speedbrake animation constants
// ============================================================
const VECTOR3 RSB_REF = _V( 0.0, 9.323704, -17.344454 );
const VECTOR3 RSB_AXIS = _V( 0.0, -0.820819, 0.571188 );
constexpr double RUDDER_RANGE = 27.1;// [deg]
constexpr double SPEEDBRAKE_RANGE = 98.6;// [deg]
constexpr double RSB_MAX = 61.5;// [deg]
constexpr double RSB_RANGE = RSB_MAX + RUDDER_RANGE;// [deg]
const double lambda = 34.833134 * RAD;

// ============================================================
// Body Flap animation constants
// ============================================================
const VECTOR3 BODYFLAP_REF = _V( 0.0, -3.2973, -14.6738 );
const VECTOR3 BODYFLAP_AXIS = _V( -1.0, 0.0, 0.0 );
constexpr double BODYFLAP_MIN = -11.7;// [deg]
constexpr double BODYFLAP_MAX = 22.55;// [deg]
constexpr double BODYFLAP_RANGE = BODYFLAP_MAX - BODYFLAP_MIN;// [deg]


AeroSurfaces::AeroSurfaces( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "AeroSurfaces" )
{
	Elevon_LOB = 0.0;
	Elevon_LIB = 0.0;
	Elevon_RIB = 0.0;
	Elevon_ROB = 0.0;
	Rudder = 0.0;
	SpeedBrake = 0.0;
	BodyFlap = 0.0;
	return;
}

AeroSurfaces::~AeroSurfaces( void )
{
}

bool AeroSurfaces::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "ELEVON_LOB", 10 ))
	{
		sscanf_s( line + 10, "%lf", &Elevon_LOB );
		Elevon_LOB = range( ELEVON_MECH_MIN, Elevon_LOB, ELEVON_MECH_MAX );
	}
	else if (!_strnicmp( line, "ELEVON_LIB", 10 ))
	{
		sscanf_s( line + 10, "%lf", &Elevon_LIB );
		Elevon_LIB = range( ELEVON_MECH_MIN, Elevon_LIB, ELEVON_MECH_MAX );
	}
	else if (!_strnicmp( line, "ELEVON_RIB", 10 ))
	{
		sscanf_s( line + 10, "%lf", &Elevon_RIB );
		Elevon_RIB = range( ELEVON_MECH_MIN, Elevon_RIB, ELEVON_MECH_MAX );
	}
	else if (!_strnicmp( line, "ELEVON_ROB", 10 ))
	{
		sscanf_s( line + 10, "%lf", &Elevon_ROB );
		Elevon_ROB = range( ELEVON_MECH_MIN, Elevon_ROB, ELEVON_MECH_MAX );
	}
	else if (!_strnicmp( line, "RUDDER", 6 ))
	{
		sscanf_s( line + 6, "%lf", &Rudder );
		Rudder = range( -27.1, Rudder, 27.1 );
	}
	else if (!_strnicmp( line, "SPEEDBRAKE", 10 ))
	{
		sscanf_s( line + 10, "%lf", &SpeedBrake );
		SpeedBrake = range( 0.0, SpeedBrake, 98.6 );
	}
	else if (!_strnicmp( line, "BODYFLAP", 8 ))
	{
		sscanf_s( line + 8, "%lf", &BodyFlap );
		BodyFlap = range( -11.7, BodyFlap, 22.55 );
	}
	else return false;

	return true;
}

void AeroSurfaces::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "ELEVON_LOB", Elevon_LOB );
	oapiWriteScenario_float( scn, "ELEVON_LIB", Elevon_LIB );
	oapiWriteScenario_float( scn, "ELEVON_RIB", Elevon_RIB );
	oapiWriteScenario_float( scn, "ELEVON_ROB", Elevon_ROB );
	oapiWriteScenario_float( scn, "RUDDER", Rudder );
	oapiWriteScenario_float( scn, "SPEEDBRAKE", SpeedBrake );
	oapiWriteScenario_float( scn, "BODYFLAP", BodyFlap );
	return;
}

void AeroSurfaces::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_CMD", 16 );
	dipElevon_LOB.Connect( pBundle, 0 );
	dipElevon_LIB.Connect( pBundle, 1 );
	dipElevon_RIB.Connect( pBundle, 2 );
	dipElevon_ROB.Connect( pBundle, 3 );
	dipRudder.Connect( pBundle, 4 );
	dipSpeedBrake.Connect( pBundle, 5 );
	dipBodyFlap.Connect( pBundle, 6 );

	pBundle = BundleManager()->CreateBundle( "AEROSURFACE_POS", 16 );
	dopElevon_LOB.Connect( pBundle, 0 );
	dopElevon_LIB.Connect( pBundle, 1 );
	dopElevon_RIB.Connect( pBundle, 2 );
	dopElevon_ROB.Connect( pBundle, 3 );
	dopRudder.Connect( pBundle, 4 );
	dopSpeedBrake.Connect( pBundle, 5 );
	dopBodyFlap.Connect( pBundle, 6 );

	AddAnimation();

	SetAerosurfacePosition( Elevon_LOB, Elevon_LIB, Elevon_RIB, Elevon_ROB, Rudder, SpeedBrake, BodyFlap );
	SetDigitals();
	return;
}

void AeroSurfaces::AddAnimation( void )
{
	// elevons
	static UINT LOBElevGrp[1] = {GRP_LEFT_OUTBOARD_ELEVON};
	MGROUP_ROTATE* LOBElevon = new MGROUP_ROTATE( STS()->OVmesh(), LOBElevGrp, 1, ELEVON_LOB_REF, ELEVON_LOB_AXIS, static_cast<float>(ELEVON_MECH_RANGE * RAD) );
	anim_lobelevon = STS()->CreateAnimation( -ELEVON_MECH_MIN / ELEVON_MECH_RANGE );
	STS()->AddAnimationComponent( anim_lobelevon, 0.0, 1.0, LOBElevon );
	SaveAnimation( LOBElevon );

	static UINT LIBElevGrp[1] = {GRP_LEFT_INBOARD_ELEVON};
	MGROUP_ROTATE* LIBElevon = new MGROUP_ROTATE( STS()->OVmesh(), LIBElevGrp, 1, ELEVON_LIB_REF, ELEVON_LIB_AXIS, static_cast<float>(ELEVON_MECH_RANGE * RAD) );
	anim_libelevon = STS()->CreateAnimation( -ELEVON_MECH_MIN / ELEVON_MECH_RANGE );
	STS()->AddAnimationComponent( anim_libelevon, 0.0, 1.0, LIBElevon );
	SaveAnimation( LIBElevon );

	static UINT RIBElevGrp[1] = {GRP_RIGHT_INBOARD_ELEVON};
	MGROUP_ROTATE* RIBElevon = new MGROUP_ROTATE( STS()->OVmesh(), RIBElevGrp, 1, ELEVON_RIB_REF, ELEVON_RIB_AXIS, static_cast<float>(ELEVON_MECH_RANGE * RAD) );
	anim_ribelevon = STS()->CreateAnimation( -ELEVON_MECH_MIN / ELEVON_MECH_RANGE );
	STS()->AddAnimationComponent( anim_ribelevon, 0.0, 1.0, RIBElevon );
	SaveAnimation( RIBElevon );

	static UINT ROBElevGrp[1] = {GRP_RIGHT_OUTBOARD_ELEVON};
	MGROUP_ROTATE* ROBElevon = new MGROUP_ROTATE( STS()->OVmesh(), ROBElevGrp, 1, ELEVON_ROB_REF, ELEVON_ROB_AXIS, static_cast<float>(ELEVON_MECH_RANGE * RAD) );
	anim_robelevon = STS()->CreateAnimation( -ELEVON_MECH_MIN / ELEVON_MECH_RANGE );
	STS()->AddAnimationComponent( anim_robelevon, 0.0, 1.0, ROBElevon );
	SaveAnimation( ROBElevon );

	// elevon seal panels
	static UINT LeftElevonSealPanel1Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_1};
	MGROUP_ROTATE* LeftElevonSealPanel1 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel1Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel1 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel1, 0.0, 1.0, LeftElevonSealPanel1 );
	SaveAnimation( LeftElevonSealPanel1 );

	static UINT LeftElevonSealPanel2Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_2};
	MGROUP_ROTATE* LeftElevonSealPanel2 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel2Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel2 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel2, 0.0, 1.0, LeftElevonSealPanel2 );
	SaveAnimation( LeftElevonSealPanel2 );

	static UINT LeftElevonSealPanel3Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_3};
	MGROUP_ROTATE* LeftElevonSealPanel3 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel3Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel3 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel3, 0.0, 1.0, LeftElevonSealPanel3 );
	SaveAnimation( LeftElevonSealPanel3 );

	static UINT LeftElevonSealPanel4Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_4};
	MGROUP_ROTATE* LeftElevonSealPanel4 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel4Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel4 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel4, 0.0, 1.0, LeftElevonSealPanel4 );
	SaveAnimation( LeftElevonSealPanel4 );

	static UINT LeftElevonSealPanel5Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_5};
	MGROUP_ROTATE* LeftElevonSealPanel5 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel5Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel5 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel5, 0.0, 1.0, LeftElevonSealPanel5 );
	SaveAnimation( LeftElevonSealPanel5 );

	static UINT LeftElevonSealPanel6Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_6};
	MGROUP_ROTATE* LeftElevonSealPanel6 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel6Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel6 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel6, 0.0, 1.0, LeftElevonSealPanel6 );
	SaveAnimation( LeftElevonSealPanel6 );

	static UINT LeftElevonSealPanel7Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_7};
	MGROUP_ROTATE* LeftElevonSealPanel7 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel7Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel7 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel7, 0.0, 1.0, LeftElevonSealPanel7 );
	SaveAnimation( LeftElevonSealPanel7 );

	static UINT LeftElevonSealPanel8Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_8};
	MGROUP_ROTATE* LeftElevonSealPanel8 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevonSealPanel8Grp, 1, ELEVON_SEALPANEL_LIB_REF, ELEVON_SEALPANEL_LIB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel8 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel8, 0.0, 1.0, LeftElevonSealPanel8 );
	SaveAnimation( LeftElevonSealPanel8 );

	static UINT LeftElevSealPanel9Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_9};
	MGROUP_ROTATE* LeftElevonSealPanel9 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel9Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel9 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel9, 0.0, 1.0, LeftElevonSealPanel9 );
	SaveAnimation( LeftElevonSealPanel9 );

	static UINT LeftElevSealPanel10Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_10};
	MGROUP_ROTATE* LeftElevonSealPanel10 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel10Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel10 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel10, 0.0, 1.0, LeftElevonSealPanel10 );
	SaveAnimation( LeftElevonSealPanel10 );

	static UINT LeftElevSealPanel11Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_11};
	MGROUP_ROTATE* LeftElevonSealPanel11 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel11Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel11 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel11, 0.0, 1.0, LeftElevonSealPanel11 );
	SaveAnimation( LeftElevonSealPanel11 );

	static UINT LeftElevSealPanel12Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_12};
	MGROUP_ROTATE* LeftElevonSealPanel12 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel12Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel12 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel12, 0.0, 1.0, LeftElevonSealPanel12 );
	SaveAnimation( LeftElevonSealPanel12 );

	static UINT LeftElevSealPanel13Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_13};
	MGROUP_ROTATE* LeftElevonSealPanel13 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel13Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel13 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel13, 0.0, 1.0, LeftElevonSealPanel13 );
	SaveAnimation( LeftElevonSealPanel13 );

	static UINT LeftElevSealPanel14Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_14};
	MGROUP_ROTATE* LeftElevonSealPanel14 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel14Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel14 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel14, 0.0, 1.0, LeftElevonSealPanel14 );
	SaveAnimation( LeftElevonSealPanel14 );

	static UINT LeftElevSealPanel15Grp[1] = {GRP_ELEVON_SEAL_PANEL_LEFT_15};
	MGROUP_ROTATE* LeftElevonSealPanel15 = new MGROUP_ROTATE( STS()->OVmesh(), LeftElevSealPanel15Grp, 1, ELEVON_SEALPANEL_LOB_REF, ELEVON_SEALPANEL_LOB_AXIS, static_cast<float>(PI2) );
	anim_leftelevonsealpanel15 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_leftelevonsealpanel15, 0.0, 1.0, LeftElevonSealPanel15 );
	SaveAnimation( LeftElevonSealPanel15 );

	static UINT RightElevonSealPanel1Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_1};
	MGROUP_ROTATE* RightElevonSealPanel1 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel1Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel1 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel1, 0.0, 1.0, RightElevonSealPanel1 );
	SaveAnimation( RightElevonSealPanel1 );

	static UINT RightElevonSealPanel2Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_2};
	MGROUP_ROTATE* RightElevonSealPanel2 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel2Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel2 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel2, 0.0, 1.0, RightElevonSealPanel2 );
	SaveAnimation( RightElevonSealPanel2 );

	static UINT RightElevonSealPanel3Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_3};
	MGROUP_ROTATE* RightElevonSealPanel3 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel3Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel3 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel3, 0.0, 1.0, RightElevonSealPanel3 );
	SaveAnimation( RightElevonSealPanel3 );

	static UINT RightElevonSealPanel4Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_4};
	MGROUP_ROTATE* RightElevonSealPanel4 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel4Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel4 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel4, 0.0, 1.0, RightElevonSealPanel4 );
	SaveAnimation( RightElevonSealPanel4 );

	static UINT RightElevonSealPanel5Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_5};
	MGROUP_ROTATE* RightElevonSealPanel5 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel5Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel5 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel5, 0.0, 1.0, RightElevonSealPanel5 );
	SaveAnimation( RightElevonSealPanel5 );

	static UINT RightElevonSealPanel6Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_6};
	MGROUP_ROTATE* RightElevonSealPanel6 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel6Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel6 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel6, 0.0, 1.0, RightElevonSealPanel6 );
	SaveAnimation( RightElevonSealPanel6 );

	static UINT RightElevonSealPanel7Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_7};
	MGROUP_ROTATE* RightElevonSealPanel7 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel7Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel7 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel7, 0.0, 1.0, RightElevonSealPanel7 );
	SaveAnimation( RightElevonSealPanel7 );

	static UINT RightElevonSealPanel8Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_8};
	MGROUP_ROTATE* RightElevonSealPanel8 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevonSealPanel8Grp, 1, ELEVON_SEALPANEL_RIB_REF, ELEVON_SEALPANEL_RIB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel8 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel8, 0.0, 1.0, RightElevonSealPanel8 );
	SaveAnimation( RightElevonSealPanel8 );

	static UINT RightElevSealPanel9Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_9};
	MGROUP_ROTATE* RightElevonSealPanel9 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel9Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel9 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel9, 0.0, 1.0, RightElevonSealPanel9 );
	SaveAnimation( RightElevonSealPanel9 );

	static UINT RightElevSealPanel10Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_10};
	MGROUP_ROTATE* RightElevonSealPanel10 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel10Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel10 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel10, 0.0, 1.0, RightElevonSealPanel10 );
	SaveAnimation( RightElevonSealPanel10 );

	static UINT RightElevSealPanel11Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_11};
	MGROUP_ROTATE* RightElevonSealPanel11 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel11Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel11 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel11, 0.0, 1.0, RightElevonSealPanel11 );
	SaveAnimation( RightElevonSealPanel11 );

	static UINT RightElevSealPanel12Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_12};
	MGROUP_ROTATE* RightElevonSealPanel12 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel12Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel12 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel12, 0.0, 1.0, RightElevonSealPanel12 );
	SaveAnimation( RightElevonSealPanel12 );

	static UINT RightElevSealPanel13Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_13};
	MGROUP_ROTATE* RightElevonSealPanel13 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel13Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel13 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel13, 0.0, 1.0, RightElevonSealPanel13 );
	SaveAnimation( RightElevonSealPanel13 );

	static UINT RightElevSealPanel14Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_14};
	MGROUP_ROTATE* RightElevonSealPanel14 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel14Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel14 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel14, 0.0, 1.0, RightElevonSealPanel14 );
	SaveAnimation( RightElevonSealPanel14 );

	static UINT RightElevSealPanel15Grp[1] = {GRP_ELEVON_SEAL_PANEL_RIGHT_15};
	MGROUP_ROTATE* RightElevonSealPanel15 = new MGROUP_ROTATE( STS()->OVmesh(), RightElevSealPanel15Grp, 1, ELEVON_SEALPANEL_ROB_REF, ELEVON_SEALPANEL_ROB_AXIS, static_cast<float>(PI2) );
	anim_rightelevonsealpanel15 = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_rightelevonsealpanel15, 0.0, 1.0, RightElevonSealPanel15 );
	SaveAnimation( RightElevonSealPanel15 );

	// bodyflap
	static UINT bfGrp[1] = { GRP_BODYFLAP };
	MGROUP_ROTATE* BF = new MGROUP_ROTATE(STS()->OVmesh(), bfGrp, 1, BODYFLAP_REF, BODYFLAP_AXIS, static_cast<float>(BODYFLAP_RANGE * RAD) );
	anim_bf = STS()->CreateAnimation( -BODYFLAP_MIN / BODYFLAP_RANGE );
	STS()->AddAnimationComponent( anim_bf, 0.0, 1.0, BF );
	SaveAnimation( BF );

	// rudder/speedbrake
	static UINT RSBRightGrp[4] = {GRP_RSB_ACTUATORS_RIGHT, GRP_RSB_ACTUATOR_ARMS_RIGHT, GRP_RSB_CONICAL_SEAL_RIGHT, GRP_RSB_PANEL_RIGHT};
	MGROUP_ROTATE* RSBRight = new MGROUP_ROTATE( STS()->OVmesh(), RSBRightGrp, 4, RSB_REF, RSB_AXIS, static_cast<float>(-RSB_RANGE * RAD) );
	static UINT RSBLeftGrp[4] = {GRP_RSB_ACTUATORS_LEFT, GRP_RSB_ACTUATOR_ARMS_LEFT, GRP_RSB_CONICAL_SEAL_LEFT, GRP_RSB_PANEL_LEFT};
	MGROUP_ROTATE* RSBLeft = new MGROUP_ROTATE( STS()->OVmesh(), RSBLeftGrp, 4, RSB_REF, RSB_AXIS, static_cast<float>(-RSB_RANGE * RAD) );
	anim_rsb_right = STS()->CreateAnimation( RSB_MAX / RSB_RANGE );
	anim_rsb_left = STS()->CreateAnimation( RUDDER_RANGE / RSB_RANGE );
	STS()->AddAnimationComponent( anim_rsb_right, 0.0, 1.0, RSBRight );
	STS()->AddAnimationComponent( anim_rsb_left, 0.0, 1.0, RSBLeft );
	SaveAnimation( RSBRight );
	SaveAnimation( RSBLeft );
	return;
}

void AeroSurfaces::OnPostStep( double simt, double simdt, double mjd )
{
	// move aerosurfaces
	if (STS()->HydraulicsOK())
	{
		Elevon_LOB = range( ELEVON_CMD_MIN, ((dipElevon_LOB.GetVoltage() * ELEVON_CMD_RANGE) / 5.0) + ELEVON_CMD_MIN, ELEVON_CMD_MAX );
		Elevon_LIB = range( ELEVON_CMD_MIN, ((dipElevon_LIB.GetVoltage() * ELEVON_CMD_RANGE) / 5.0) + ELEVON_CMD_MIN, ELEVON_CMD_MAX );
		Elevon_RIB = range( ELEVON_CMD_MIN, ((dipElevon_RIB.GetVoltage() * ELEVON_CMD_RANGE) / 5.0) + ELEVON_CMD_MIN, ELEVON_CMD_MAX );
		Elevon_ROB = range( ELEVON_CMD_MIN, ((dipElevon_ROB.GetVoltage() * ELEVON_CMD_RANGE) / 5.0) + ELEVON_CMD_MIN, ELEVON_CMD_MAX );
		Rudder = range( -27.6, ((dipRudder.GetVoltage() * (27.6 + 27.6)) / 5.0) - 27.6, 27.6 );
		SpeedBrake = range( -9.9, ((dipSpeedBrake.GetVoltage() * (98.6 + 9.9)) / 5.0) - 9.9, 98.6 );
		BodyFlap = range( -11.7, BodyFlap + (dipBodyFlap.GetVoltage() * 2.25 * simdt), 22.55 );// 1-3º/s, 2.25º/s without hinge moment

		SpeedBrake = max(0.0,SpeedBrake);// physically limit SB to 0.0º

		// limit RBS panel motion
		double RSB_LH = Rudder + (SpeedBrake * 0.5);// CW position from centerline [deg]
		double RSB_RH = Rudder - (SpeedBrake * 0.5);// CW position from centerline [deg]
		RSB_LH = min(RSB_LH, 61.5);
		RSB_RH = max(RSB_RH, -61.5);
		Rudder = (RSB_LH + RSB_RH) * 0.5;
		SpeedBrake = RSB_LH - RSB_RH;
	}

	// set physical and visual outputs
	SetAerosurfacePosition( Elevon_LOB, Elevon_LIB, Elevon_RIB, Elevon_ROB, Rudder, SpeedBrake, BodyFlap );

	// set digital outputs
	SetDigitals();
	return;
}

void AeroSurfaces::SetDigitals( void )
{
	// TODO missing OA outputs
	dopElevon_LOB.SetLine( static_cast<float>(((range( ELEVON_POS_FA_OB_MIN, Elevon_LOB, ELEVON_POS_FA_OB_MAX ) - ELEVON_POS_FA_OB_MIN) * 5.0) / ELEVON_POS_FA_OB_RANGE) );// (-36.5,+21.1) [deg]
	dopElevon_LIB.SetLine( static_cast<float>(((range( ELEVON_POS_FA_IB_MIN, Elevon_LIB, ELEVON_POS_FA_IB_MAX ) - ELEVON_POS_FA_IB_MIN) * 5.0) / ELEVON_POS_FA_IB_RANGE) );// (-36.5,+21.3) [deg]
	dopElevon_RIB.SetLine( static_cast<float>(((range( ELEVON_POS_FA_IB_MIN, Elevon_RIB, ELEVON_POS_FA_IB_MAX ) - ELEVON_POS_FA_IB_MIN) * 5.0) / ELEVON_POS_FA_IB_RANGE) );// (-36.5,+21.3) [deg]
	dopElevon_ROB.SetLine( static_cast<float>(((range( ELEVON_POS_FA_OB_MIN, Elevon_ROB, ELEVON_POS_FA_OB_MAX ) - ELEVON_POS_FA_OB_MIN) * 5.0) / ELEVON_POS_FA_OB_RANGE) );// (-36.5,+21.1) [deg]
	dopRudder.SetLine( static_cast<float>(((range( -27.6, Rudder, 27.6 ) + 27.6) * 5.0) / (27.6 + 27.6)) );// (-27.6;+27.6) [deg]
	dopSpeedBrake.SetLine( static_cast<float>(((range( -9.9, SpeedBrake, 98.6 ) + 9.9) * 5.0) / (98.6 + 9.9)) );// (-9.9;+98.6) [deg]
	dopBodyFlap.SetLine( static_cast<float>(((range( -16.6, BodyFlap, 27.5 ) + 16.6) * 5.0) / (27.5 + 16.6)) );// (-16.6;+27.5) [deg]
	return;
}

void AeroSurfaces::SetAerosurfacePosition( double Elevon_LOB, double Elevon_LIB, double Elevon_RIB, double Elevon_ROB, double Rudder, double SpeedBrake, double BodyFlap )
{
	// set physical effects
	STS()->aerosurfaces.Elevator = (Elevon_LOB + Elevon_LIB + Elevon_RIB + Elevon_ROB) * 0.25;
	STS()->aerosurfaces.Aileron = (Elevon_LOB + Elevon_LIB - Elevon_RIB - Elevon_ROB) * 0.25;
	STS()->aerosurfaces.Rudder = range( -22.8, 2.0 * atan( cos( lambda ) * tan( Rudder * 0.5 * RAD ) ) * DEG, 22.8 );// rudder angle, in plane [deg]
	STS()->aerosurfaces.Speedbrake = range( 0.0, 2.0 * atan( cos( lambda ) * tan( SpeedBrake * 0.986 * 0.5 * RAD ) ) * DEG, 87.2 );// speedbrake angle, in plane [deg]
	if (STS()->aerosurfaces.BodyFlap != BodyFlap) STS()->DefineTouchdownPoints();// update BF td points
	STS()->aerosurfaces.BodyFlap = BodyFlap;

	// set animations
	STS()->SetAnimation( anim_lobelevon, (Elevon_LOB - ELEVON_MECH_MIN) / ELEVON_MECH_RANGE );
	STS()->SetAnimation( anim_libelevon, (Elevon_LIB - ELEVON_MECH_MIN) / ELEVON_MECH_RANGE );
	STS()->SetAnimation( anim_ribelevon, (Elevon_RIB - ELEVON_MECH_MIN) / ELEVON_MECH_RANGE );
	STS()->SetAnimation( anim_robelevon, (Elevon_ROB - ELEVON_MECH_MIN) / ELEVON_MECH_RANGE );

	double leftelevonsealpanel1 = GetElevonSealPanel1AnimState( Elevon_LIB );
	double leftelevonsealpanel8 = GetElevonSealPanel8AnimState( Elevon_LIB );
	double leftelevonsealpanel2 = leftelevonsealpanel1 - ((leftelevonsealpanel1 - leftelevonsealpanel8) * (1.0 / 7.0));
	double leftelevonsealpanel3 = leftelevonsealpanel1 - ((leftelevonsealpanel1 - leftelevonsealpanel8) * (2.0 / 7.0));
	double leftelevonsealpanel4 = leftelevonsealpanel1 - ((leftelevonsealpanel1 - leftelevonsealpanel8) * (3.0 / 7.0));
	double leftelevonsealpanel5 = leftelevonsealpanel1 - ((leftelevonsealpanel1 - leftelevonsealpanel8) * (4.0 / 7.0));
	double leftelevonsealpanel6 = leftelevonsealpanel1 - ((leftelevonsealpanel1 - leftelevonsealpanel8) * (5.0 / 7.0));
	double leftelevonsealpanel7 = leftelevonsealpanel1 - ((leftelevonsealpanel1 - leftelevonsealpanel8) * (6.0 / 7.0));
	double leftelevonsealpanel9 = GetElevonSealPanel9AnimState( Elevon_LOB );
	double leftelevonsealpanel15 = GetElevonSealPanel15AnimState( Elevon_LOB );
	double leftelevonsealpanel10 = leftelevonsealpanel9 - ((leftelevonsealpanel9 - leftelevonsealpanel15) * (1.0 / 6.0));
	double leftelevonsealpanel11 = leftelevonsealpanel9 - ((leftelevonsealpanel9 - leftelevonsealpanel15) * (2.0 / 6.0));
	double leftelevonsealpanel12 = leftelevonsealpanel9 - ((leftelevonsealpanel9 - leftelevonsealpanel15) * (3.0 / 6.0));
	double leftelevonsealpanel13 = leftelevonsealpanel9 - ((leftelevonsealpanel9 - leftelevonsealpanel15) * (4.0 / 6.0));
	double leftelevonsealpanel14 = leftelevonsealpanel9 - ((leftelevonsealpanel9 - leftelevonsealpanel15) * (5.0 / 6.0));

	STS()->SetAnimation( anim_leftelevonsealpanel1, leftelevonsealpanel1 );
	STS()->SetAnimation( anim_leftelevonsealpanel2, leftelevonsealpanel2 );
	STS()->SetAnimation( anim_leftelevonsealpanel3, leftelevonsealpanel3 );
	STS()->SetAnimation( anim_leftelevonsealpanel4, leftelevonsealpanel4 );
	STS()->SetAnimation( anim_leftelevonsealpanel5, leftelevonsealpanel5 );
	STS()->SetAnimation( anim_leftelevonsealpanel6, leftelevonsealpanel6 );
	STS()->SetAnimation( anim_leftelevonsealpanel7, leftelevonsealpanel7 );
	STS()->SetAnimation( anim_leftelevonsealpanel8, leftelevonsealpanel8 );
	STS()->SetAnimation( anim_leftelevonsealpanel9, leftelevonsealpanel9 );
	STS()->SetAnimation( anim_leftelevonsealpanel10, leftelevonsealpanel10 );
	STS()->SetAnimation( anim_leftelevonsealpanel11, leftelevonsealpanel11 );
	STS()->SetAnimation( anim_leftelevonsealpanel12, leftelevonsealpanel12 );
	STS()->SetAnimation( anim_leftelevonsealpanel13, leftelevonsealpanel13 );
	STS()->SetAnimation( anim_leftelevonsealpanel14, leftelevonsealpanel14 );
	STS()->SetAnimation( anim_leftelevonsealpanel15, leftelevonsealpanel15 );

	double rightelevonsealpanel1 = GetElevonSealPanel1AnimState( Elevon_RIB );
	double rightelevonsealpanel8 = GetElevonSealPanel8AnimState( Elevon_RIB );
	double rightelevonsealpanel2 = rightelevonsealpanel1 - ((rightelevonsealpanel1 - rightelevonsealpanel8) * (1.0 / 7.0));
	double rightelevonsealpanel3 = rightelevonsealpanel1 - ((rightelevonsealpanel1 - rightelevonsealpanel8) * (2.0 / 7.0));
	double rightelevonsealpanel4 = rightelevonsealpanel1 - ((rightelevonsealpanel1 - rightelevonsealpanel8) * (3.0 / 7.0));
	double rightelevonsealpanel5 = rightelevonsealpanel1 - ((rightelevonsealpanel1 - rightelevonsealpanel8) * (4.0 / 7.0));
	double rightelevonsealpanel6 = rightelevonsealpanel1 - ((rightelevonsealpanel1 - rightelevonsealpanel8) * (5.0 / 7.0));
	double rightelevonsealpanel7 = rightelevonsealpanel1 - ((rightelevonsealpanel1 - rightelevonsealpanel8) * (6.0 / 7.0));
	double rightelevonsealpanel9 = GetElevonSealPanel9AnimState( Elevon_ROB );
	double rightelevonsealpanel15 = GetElevonSealPanel15AnimState( Elevon_ROB );
	double rightelevonsealpanel10 = rightelevonsealpanel9 - ((rightelevonsealpanel9 - rightelevonsealpanel15) * (1.0 / 6.0));
	double rightelevonsealpanel11 = rightelevonsealpanel9 - ((rightelevonsealpanel9 - rightelevonsealpanel15) * (2.0 / 6.0));
	double rightelevonsealpanel12 = rightelevonsealpanel9 - ((rightelevonsealpanel9 - rightelevonsealpanel15) * (3.0 / 6.0));
	double rightelevonsealpanel13 = rightelevonsealpanel9 - ((rightelevonsealpanel9 - rightelevonsealpanel15) * (4.0 / 6.0));
	double rightelevonsealpanel14 = rightelevonsealpanel9 - ((rightelevonsealpanel9 - rightelevonsealpanel15) * (5.0 / 6.0));

	STS()->SetAnimation( anim_rightelevonsealpanel1, rightelevonsealpanel1 );
	STS()->SetAnimation( anim_rightelevonsealpanel2, rightelevonsealpanel2 );
	STS()->SetAnimation( anim_rightelevonsealpanel3, rightelevonsealpanel3 );
	STS()->SetAnimation( anim_rightelevonsealpanel4, rightelevonsealpanel4 );
	STS()->SetAnimation( anim_rightelevonsealpanel5, rightelevonsealpanel5 );
	STS()->SetAnimation( anim_rightelevonsealpanel6, rightelevonsealpanel6 );
	STS()->SetAnimation( anim_rightelevonsealpanel7, rightelevonsealpanel7 );
	STS()->SetAnimation( anim_rightelevonsealpanel8, rightelevonsealpanel8 );
	STS()->SetAnimation( anim_rightelevonsealpanel9, rightelevonsealpanel9 );
	STS()->SetAnimation( anim_rightelevonsealpanel10, rightelevonsealpanel10 );
	STS()->SetAnimation( anim_rightelevonsealpanel11, rightelevonsealpanel11 );
	STS()->SetAnimation( anim_rightelevonsealpanel12, rightelevonsealpanel12 );
	STS()->SetAnimation( anim_rightelevonsealpanel13, rightelevonsealpanel13 );
	STS()->SetAnimation( anim_rightelevonsealpanel14, rightelevonsealpanel14 );
	STS()->SetAnimation( anim_rightelevonsealpanel15, rightelevonsealpanel15 );

	STS()->SetAnimation( anim_rsb_left, (Rudder + (SpeedBrake * 0.5) + RUDDER_RANGE) / RSB_RANGE );
	STS()->SetAnimation( anim_rsb_right, (Rudder - (SpeedBrake * 0.5) + RSB_MAX) / RSB_RANGE );
	STS()->SetAnimation( anim_bf, (BodyFlap - BODYFLAP_MIN) / BODYFLAP_RANGE );
	return;
}

double AeroSurfaces::GetElevonSealPanel1AnimState( double elevon ) const
{
	// elevon sealpanel
	// +21.5 +7.3
	// +20	+7.0
	// +15	+5.6
	// +10	+4.0
	// +5	+2.1
	// 0	0.0
	// -5	-2.3
	// -10	-5.0
	// -15	-7.9
	// -20	-11.1
	// -25	-14.7
	// -30	-18.5
	// -35	-22.7
	// -36.5 -24.0
	double pos = 0.0;

	if (elevon > 0.0)// ordered to search from 0º out
	{
		if (elevon < 5.0) pos = elevon * 0.42;// 0;+5
		else if (elevon < 10.0) pos = (elevon * 0.38) + 0.2;// +5;+10
		else if (elevon < 15.0) pos = (elevon * 0.32) + 0.8;// +10;+15
		else if (elevon < 20.0) pos = (elevon * 0.28) + 1.4;// +15;+20
		else pos = (elevon * 0.2) + 3.0;// +20;+21.5
	}
	else
	{
		if (elevon > -5.0) pos = elevon * 0.46;// -5;0
		else if (elevon > -10.0) pos = (elevon * 0.54) + 0.4;// -10;-5
		else if (elevon > -15.0) pos = (elevon * 0.58) + 0.8;// -15;-10
		else if (elevon > -20.0) pos = (elevon * 0.64) + 1.7;// -20;-15
		else if (elevon > -25.0) pos = (elevon * 0.72) + 3.3;// -25;-20
		else if (elevon > -30.0) pos = (elevon * 0.76) + 4.3;// -30;-25
		else if (elevon > -35.0) pos = (elevon * 0.84) + 6.7;// -35;-30
		else pos = (elevon * 0.866667) + 7.633333;// -36.5;-35
	}

	//sprintf_s( oapiDebugString(), 256, "%f %f", elevon, pos );
	return (pos * RAD / PI2) + 0.5;
}

double AeroSurfaces::GetElevonSealPanel8AnimState( double elevon ) const
{
	// elevon sealpanel
	// +21.5 +7.0
	// +20	+6.6
	// +15	+5.2
	// +10	+3.6
	// +5	+1.9
	// 0	0.0
	// -5	-2.2
	// -10	-4.6
	// -15	-7.2
	// -20	-10.0
	// -25	-13.1
	// -30	-16.5
	// -35	-20.2
	// -36.5 -21.3
	double pos = 0.0;

	if (elevon > 0.0)// ordered to search from 0º out
	{
		if (elevon < 5.0) pos = elevon * 0.38;// 0;+5
		else if (elevon < 10.0) pos = (elevon * 0.34) + 0.2;// +5;+10
		else if (elevon < 15.0) pos = (elevon * 0.32) + 0.4;// +10;+15
		else if (elevon < 20.0) pos = (elevon * 0.28) + 1.0;// +15;+20
		else pos = (elevon * 0.266667) + 1.366667;// +20;+21.5
	}
	else
	{
		if (elevon > -5.0) pos = elevon * 0.44;// -5;0
		else if (elevon > -10.0) pos = (elevon * 0.48) + 0.2;// -10;-5
		else if (elevon > -15.0) pos = (elevon * 0.52) + 0.6;// -15;-10
		else if (elevon > -20.0) pos = (elevon * 0.56) + 1.2;// -20;-15
		else if (elevon > -25.0) pos = (elevon * 0.62) + 2.4;// -25;-20
		else if (elevon > -30.0) pos = (elevon * 0.68) + 3.9;// -30;-25
		else if (elevon > -35.0) pos = (elevon * 0.74) + 5.7;// -35;-30
		else pos = (elevon * 0.266667) + 1.266667;// -36.5;-35
	}

	//sprintf_s( oapiDebugString(), 256, "%f %f", elevon, pos );
	return (pos * RAD / PI2) + 0.5;
}

double AeroSurfaces::GetElevonSealPanel9AnimState( double elevon ) const
{
	// elevon sealpanel
	// +21.5 +7.0
	// +20	+6.6
	// +15	+5.2
	// +10	+3.6
	// +5	+1.9
	// 0	0.0
	// -5	-2.2
	// -10	-4.5
	// -15	-7.0
	// -20	-9.8
	// -25	-12.9
	// -30	-16.2
	// -35	-19.7
	// -36.5 -20.9
	double pos = 0.0;

	if (elevon > 0.0)// ordered to search from 0º out
	{
		if (elevon < 5.0) pos = elevon * 0.38;// 0;+5
		else if (elevon < 10.0) pos = (elevon * 0.34) + 0.2;// +5;+10
		else if (elevon < 15.0) pos = (elevon * 0.32) + 0.4;// +10;+15
		else if (elevon < 20.0) pos = (elevon * 0.28) + 1.0;// +15;+20
		else pos = (elevon * 0.266667) + 1.266667;// +20;+21.5
	}
	else
	{
		if (elevon > -5.0) pos = elevon * 0.44;// -5;0
		else if (elevon > -10.0) pos = (elevon * 0.46) + 0.1;// -10;-5
		else if (elevon > -15.0) pos = (elevon * 0.5) + 0.5;// -15;-10
		else if (elevon > -20.0) pos = (elevon * 0.56) + 1.4;// -20;-15
		else if (elevon > -25.0) pos = (elevon * 0.62) + 2.6;// -25;-20
		else if (elevon > -30.0) pos = (elevon * 0.66) + 3.6;// -30;-25
		else if (elevon > -35.0) pos = (elevon * 0.7) + 4.8;// -35;-30
		else pos = (elevon * 0.8) + 8.3;// -36.5;-35
	}

	//sprintf_s( oapiDebugString(), 256, "%f %f", elevon, pos );
	return (pos * RAD / PI2) + 0.5;
}

double AeroSurfaces::GetElevonSealPanel15AnimState( double elevon ) const
{
	// elevon sealpanel
	// +21.5 +7.0
	// +20	+6.6
	// +15	+5.1
	// +10	+3.5
	// +5	+1.8
	// 0	0.0
	// -5	-2.0
	// -10	-4.0
	// -15	-6.2
	// -20	-8.6
	// -25	-11.2
	// -30	-14.0
	// -35	-17.0
	// -36.5 -17.9
	double pos = 0.0;

	if (elevon > 0.0)// ordered to search from 0º out
	{
		if (elevon < 5.0) pos = elevon * 0.36;// 0;+5
		else if (elevon < 10.0) pos = (elevon * 0.34) + 0.1;// +5;+10
		else if (elevon < 15.0) pos = (elevon * 0.32) + 0.3;// +10;+15
		else if (elevon < 20.0) pos = (elevon * 0.3) + 0.6;// +15;+20
		else pos = (elevon * 0.266667) + 1.266667;// +20;+21.5
	}
	else
	{
		/*if (elevon > -5.0) pos = elevon * 0.4;// -5;0
		else*/ if (elevon > -10.0) pos = elevon * 0.4;// -10;-5
		else if (elevon > -15.0) pos = (elevon * 0.44) + 0.4;// -15;-10
		else if (elevon > -20.0) pos = (elevon * 0.48) + 1.0;// -20;-15
		else if (elevon > -25.0) pos = (elevon * 0.52) + 1.8;// -25;-20
		else if (elevon > -30.0) pos = (elevon * 0.56) + 2.8;// -30;-25
		//else if (elevon > -35.0) pos = (elevon * 0.6) + 4.0;// -35;-30
		else pos = (elevon * 0.6) + 4.0;// -36.5;-35
	}

	//sprintf_s( oapiDebugString(), 256, "%f %f", elevon, pos );
	return (pos * RAD / PI2) + 0.5;
}
