/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/14   GLS
2020/05/25   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/16   GLS
2021/06/28   GLS
2021/08/03   GLS
2021/08/06   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/11   GLS
2021/12/23   GLS
2021/12/24   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/03/22   GLS
2022/03/23   GLS
2022/03/24   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/10/29   GLS
********************************************/
#define ORBITER_MODULE


#include "IUS_SRM2.h"
#include "IUS_MFD.h"
#include "meshres_IUS_SRM2.h"
#include <MathSSV.h>
#include <UtilsSSV.h>


const static char* MESHNAME_STAGE_2 = "SSV\\IUS\\IUS_SRM2";

constexpr VECTOR3 SRM1_POS = { 0.0, 0.0, -3.22003 };
constexpr VECTOR3 SRM1_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 SRM2_POS = { 0.0, 0.0, -0.2001 };
constexpr VECTOR3 SRM2_DIR = { 0.0, 0.0, 1.0 };

// REM 1
constexpr VECTOR3 RCS1_POS = { -0.2355, 1.3854, 0.8408 };
constexpr VECTOR3 RCS1_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 RCS2_POS = { -0.1563, 1.3966, 0.8408 };
constexpr VECTOR3 RCS2_DIR = { 0.0, 0.0, 1.0 };
// REM 6
constexpr VECTOR3 RCS3_POS = { 1.4055, 0.2083, 0.8598 };
constexpr VECTOR3 RCS3_DIR = { 0.0, -1.0, 0.0 };
constexpr VECTOR3 RCS4_POS = { 1.4051, 0.0609, 0.8408 };
constexpr VECTOR3 RCS4_DIR = { 0.0, 0.0, 1.0 };
//REM 5
constexpr VECTOR3 RCS5_POS = { 1.4051, -0.0609, 0.8408 };
constexpr VECTOR3 RCS5_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 RCS6_POS = { 1.4055, -0.2083, 0.8598 };
constexpr VECTOR3 RCS6_DIR = { 0.0, 1.0, 0.0 };
// REM 4
constexpr VECTOR3 RCS7_POS = { 0.2355, -1.3854, 0.8408 };
constexpr VECTOR3 RCS7_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 RCS8_POS = { 0.1563, -1.3966, 0.8408 };
constexpr VECTOR3 RCS8_DIR = { 0.0, 0.0, 1.0 };
// REM 3
constexpr VECTOR3 RCS9_POS = { -1.4055, -0.2083, 0.8598 };
constexpr VECTOR3 RCS9_DIR = { 0.0, 1.0, 0.0 };
constexpr VECTOR3 RCS10_POS = { -1.4051, -0.0609, 0.8408 };
constexpr VECTOR3 RCS10_DIR = { 0.0, 0.0, 1.0 };
// REM 2
constexpr VECTOR3 RCS11_POS = { -1.4051, 0.0609, 0.8408 };
constexpr VECTOR3 RCS11_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 RCS12_POS = { -1.4055, 0.2083, 0.8598 };
constexpr VECTOR3 RCS12_DIR = { 0.0, -1.0, 0.0 };


constexpr VECTOR3 STAGE1_ATTACH_OFFSET = { 0.0, 0.0, 0.386642 };
constexpr VECTOR3 ASE_ATTACH_OFFSET = { 0.0, 0.0, /*-0.719588 - 2.35112 + 0.386642*/-2.684066 };
constexpr VECTOR3 PAYLOAD_ATTACH_OFFSET = { 0.0, 0.0, 0.951832 };

constexpr double STAGE1_EMPTYMASS = 1123.276;// kg
constexpr double STAGE2_EMPTYMASS = 1010.649;// kg
constexpr double STAGE2_EEC_EMPTYMASS = 1054.19387;// kg

constexpr double STAGE1_PROPELLANT_MAXMASS = 9708.6;// kg
constexpr double STAGE2_PROPELLANT_MAXMASS = 2749.133;// kg

constexpr double STAGE1_THRUST_VAC = 184752.84;// N
constexpr double STAGE2_THRUST_VAC = 78272.0;// N
constexpr double STAGE2_EEC_THRUST_VAC = 78272.0;// N

const double STAGE1_ISP_VAC = 295.5 * G;// m/s
const double STAGE2_ISP_VAC = 289.1 * G;// m/s
const double STAGE2_EEC_ISP_VAC = 303.5 * G;// m/s

constexpr double RCS_TANK_PROPELLANT_MASS = 55.56507;// kg
constexpr double RCS_THRUST_VAC = 157.6;// N (or 133N???)
const double RCS_ISP_VAC = 320.0 * G;// m/s

constexpr double STAGE2_EEC_1_TRANSLATION = -1.201803;// [m]
constexpr double STAGE2_EEC_2_TRANSLATION = -0.573868;// [m]

constexpr double STAGE2_EEC_CONE_DEPLOY_DELAY = 7.0;// [s]
constexpr double STAGE2_EEC_CONE_DEPLOY_TIME = 10.0;// [s]
constexpr double STAGE2_EEC_STRIP_ROTATE_DELAY = 2.0;// [s]
constexpr double STAGE2_EEC_STRIP_ROTATE_TIME = 3.0;// [s]

constexpr double tA = STAGE2_EEC_CONE_DEPLOY_DELAY / (STAGE2_EEC_CONE_DEPLOY_DELAY + STAGE2_EEC_CONE_DEPLOY_TIME + STAGE2_EEC_STRIP_ROTATE_DELAY + STAGE2_EEC_STRIP_ROTATE_TIME);
constexpr double tB = tA + (STAGE2_EEC_CONE_DEPLOY_TIME / (STAGE2_EEC_CONE_DEPLOY_DELAY + STAGE2_EEC_CONE_DEPLOY_TIME + STAGE2_EEC_STRIP_ROTATE_DELAY + STAGE2_EEC_STRIP_ROTATE_TIME));
constexpr double tC = tB + (STAGE2_EEC_STRIP_ROTATE_DELAY / (STAGE2_EEC_CONE_DEPLOY_DELAY + STAGE2_EEC_CONE_DEPLOY_TIME + STAGE2_EEC_STRIP_ROTATE_DELAY + STAGE2_EEC_STRIP_ROTATE_TIME));
constexpr double tAA = tA + (((STAGE2_EEC_1_TRANSLATION - STAGE2_EEC_2_TRANSLATION) / STAGE2_EEC_1_TRANSLATION) * (tB - tA));

constexpr double VEHICLE_MAX_RATE_CMD = 5.0;// deg/s
constexpr double SRM_MAX_GIMBAL_RATE = 2.0;// deg/s
constexpr double SRM1_GIMBAL_RANGE = 4.0;// deg
constexpr double SRM2_GIMBAL_RANGE = 7.0;// deg


DLLCLBK VESSEL *ovcInit( OBJHANDLE hvessel, int flightmodel )
{
	try
	{
		return new IUS_SRM2( hvessel );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit( VESSEL *vessel )
{
	try
	{
		if (vessel) delete static_cast<IUS_SRM2*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}


IUS_SRM2::IUS_SRM2( OBJHANDLE hObj ):VESSEL4( hObj ),
RCStanks(2), FourAntennas(false), propload{1.0, 1.0}, SRM_P(0.0), SRM_Y(0.0), manP(0.0), manY(0.0), deployed(false),
timer_RCS_ENA(-1.0), RCS_ENA(false), timer_SRM_ENA(-1.0), SRM_ENA(false), rollRCSonly(false), AdapterOffset(0.0), AdapterMass(0.0), hTexture(NULL)
{
	ctrlSRM_P.SetGains( 0.1, 0.01, 0.0 );
	ctrlSRM_Y.SetGains( 0.1, 0.01, 0.0 );

	static char *name = "SSV_IUS";
	MFDMODESPECEX spec;
	spec.name = name;
	spec.key = OAPI_KEY_T;
	spec.context = NULL;
	spec.msgproc = IUS_MFD::MsgProc;
	mfdID = RegisterMFDMode( spec );
	return;
}

IUS_SRM2::~IUS_SRM2( void )
{
	UnregisterMFDMode( mfdID );

	delete EEC_1;
	delete EEC_2;
	delete EEC_DEVICE_1;
	delete EEC_DEVICE_2;
	delete EEC_DEVICE_3;
	delete EEC_STRIP_1;
	delete EEC_STRIP_2;
	delete EEC_STRIP_3;

	if (hTexture) oapiReleaseTexture( hTexture );
	return;
}

void IUS_SRM2::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		// default to full vehicle
		SetSize( 5.0 );
		SetEmptyMass( STAGE2_EEC_EMPTYMASS );// don't add SRM-1 mass until deployed from ASE
		SetCrossSections( _V( 13.73, 17.84, 10.71 ) );
		SetPMI( _V( 2.29, 2.4, 1.79 ) );

		mesh_stage = AddMesh( oapiLoadMeshGlobal( MESHNAME_STAGE_2 ) );
		SetMeshVisibilityMode( mesh_stage, MESHVIS_ALWAYS );

		SetCameraOffset( _V( 0.0, 1.8, 0.8 ) );

		ahPayload = CreateAttachment( false, PAYLOAD_ATTACH_OFFSET, _V( 0.0, 0.0, 1.0 ), _V( 0.0, 1.0, 0.0 ), "SSV_PLD" );
		ahSRM1 = CreateAttachment( false, STAGE1_ATTACH_OFFSET, _V( 0.0, 0.0, -1.0 ), _V( 0.0, 1.0, 0.0 ), "IUS_SRM" );
		ahASE = CreateAttachment( true, ASE_ATTACH_OFFSET, _V( 0.0, 0.0, -1.0 ), _V( 0.0, -1.0, 0.0 ), "SSV_ASE" );

		// SRM
		ph_main[0] = CreatePropellantResource( STAGE1_PROPELLANT_MAXMASS );
		ph_main[1] = CreatePropellantResource( STAGE2_PROPELLANT_MAXMASS );
		SetDefaultPropellantResource( ph_main[0] );

		PARTICLESTREAMSPEC psSRM = {
			0,
			0.4,
			25,
			50,
			0,
			0.12,
			40,
			5,
			PARTICLESTREAMSPEC::DIFFUSE,
			PARTICLESTREAMSPEC::LVL_SQRT,
			0, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0};

		th_main[0] = CreateThruster( SRM1_POS, SRM1_DIR, STAGE1_THRUST_VAC, ph_main[0], STAGE1_ISP_VAC );
		AddExhaust( th_main[0], 5, 0.5, 1.0 );
		AddExhaustStream( th_main[0], SRM1_POS + _V( 0.0, 0.0, -1.0 ), &psSRM );

		th_main[1] = CreateThruster( SRM2_POS, SRM2_DIR, STAGE2_THRUST_VAC, ph_main[1], STAGE2_EEC_ISP_VAC );
		AddExhaust( th_main[1], 5, 0.6, 2.0 );
		AddExhaustStream( th_main[1], SRM2_POS + _V( 0.0, 0.0, -2.0 ), &psSRM );

		// RCS
		ph_rcs = CreatePropellantResource( RCS_TANK_PROPELLANT_MASS * RCStanks );
		PARTICLESTREAMSPEC psRCS = {
			0,
			0.03,
			100,
			3,
			0,
			0.08,
			0.5,
			10,
			PARTICLESTREAMSPEC::DIFFUSE,
			PARTICLESTREAMSPEC::LVL_SQRT,
			0, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0};

		th_rcs[0] = CreateThruster( RCS1_POS, RCS1_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[0], 0.5, 0.05 );
		AddExhaustStream( th_rcs[0], &psRCS );
		th_rcs[1] = CreateThruster( RCS2_POS, RCS2_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[1], 0.5, 0.05 );
		AddExhaustStream( th_rcs[1], &psRCS );
		th_rcs[2] = CreateThruster( RCS3_POS, RCS3_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[2], 0.5, 0.05 );
		AddExhaustStream( th_rcs[2], &psRCS );
		th_rcs[3] = CreateThruster( RCS4_POS, RCS4_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[3], 0.5, 0.05 );
		AddExhaustStream( th_rcs[3], &psRCS );
		th_rcs[4] = CreateThruster( RCS5_POS, RCS5_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[4], 0.5, 0.05 );
		AddExhaustStream( th_rcs[4], &psRCS );
		th_rcs[5] = CreateThruster( RCS6_POS, RCS6_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[5], 0.5, 0.05 );
		AddExhaustStream( th_rcs[5], &psRCS );
		th_rcs[6] = CreateThruster( RCS7_POS, RCS7_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[6], 0.5, 0.05 );
		AddExhaustStream( th_rcs[6], &psRCS );
		th_rcs[7] = CreateThruster( RCS8_POS, RCS8_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[7], 0.5, 0.05 );
		AddExhaustStream( th_rcs[7], &psRCS );
		th_rcs[8] = CreateThruster( RCS9_POS, RCS9_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[8], 0.5, 0.05 );
		AddExhaustStream( th_rcs[8], &psRCS );
		th_rcs[9] = CreateThruster( RCS10_POS, RCS10_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[9], 0.5, 0.05 );
		AddExhaustStream( th_rcs[9], &psRCS );
		th_rcs[10] = CreateThruster( RCS11_POS, RCS11_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[10], 0.5, 0.05 );
		AddExhaustStream( th_rcs[10], &psRCS );
		th_rcs[11] = CreateThruster( RCS12_POS, RCS12_DIR, RCS_THRUST_VAC, ph_rcs, RCS_ISP_VAC );
		AddExhaust( th_rcs[11], 0.5, 0.05 );
		AddExhaustStream( th_rcs[11], &psRCS );

		DefineAnimations();

		COLOUR4 col_diff = { 1.0f, 0.8f, 0.6f, 0.0f };
		COLOUR4 col_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
		COLOUR4 col_ambient = { 1.0f, 0.8f, 0.6f, 0.0f };
		SRMlight[0] = AddPointLight( _V( SRM1_POS.x, SRM1_POS.y, SRM1_POS.z - 1.5 ), 20.0, 1.0, 0.0, 0.02, col_diff, col_zero, col_ambient );
		SRMlight[1] = AddPointLight( _V( SRM2_POS.x, SRM2_POS.y, SRM2_POS.z - 2.5 ), 20.0, 1.0, 0.0, 0.02, col_diff, col_zero, col_ambient );
		SRMlight[0]->Activate( false );
		SRMlight[1]->Activate( false );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkSetClassCaps" );
		abort();
	}
}

void IUS_SRM2::clbkPostCreation( void )
{
	try
	{
		if (GetAttachmentStatus( ahASE ) == NULL)
		{
			// if it starts the sim deployed from ASE, assume it deployed a long time ago and enable all engines without delay
			EnableRCS();
			RCS_ENA = true;
			SRM_ENA = true;

			deployed = true;

			// add payload mass to IUS dry mass
			OBJHANDLE ohPL = GetAttachmentStatus( ahPayload );
			if (ohPL)
			{
				VECTOR3 cg;
				double mass = GetMassAndCoGOfAttachedObject( this, ahPayload, cg );
				SetEmptyMass( GetEmptyMass() + mass );
			}

			// add SRM-1 mass to IUS dry mass
			SetEmptyMass( GetEmptyMass() + STAGE1_EMPTYMASS );
		}

		// if stage 1 gone, update config
		if (GetAttachmentStatus( ahSRM1 ) == NULL)
		{
			// update vehicle defs
			SetStage2Config();
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkPostCreation" );
		abort();
	}
}

void IUS_SRM2::clbkPostStep( double simt, double simdt, double mjd )
{
	try
	{
		if ((!RCS_ENA) && (timer_RCS_ENA != -1))
		{
			timer_RCS_ENA += simdt;
			if (timer_RCS_ENA >= RCS_ENA_DELAY)
			{
				EnableRCS();
				RCS_ENA = true;
			}
		}

		if ((!SRM_ENA) && (timer_SRM_ENA != -1))
		{
			timer_SRM_ENA += simdt;
			if (timer_SRM_ENA >= SRM_ENA_DELAY)
			{
				SRM_ENA = true;
			}
		}

		// check for deployment from ASE
		if (deployed == false)
		{
			if (GetAttachmentStatus( ahASE ) == NULL)
			{
				timer_RCS_ENA = 0;
				timer_SRM_ENA = 0;

				deployed = true;

				// add payload mass to IUS dry mass
				OBJHANDLE ohPL = GetAttachmentStatus( ahPayload );
				if (ohPL)
				{
					VECTOR3 cg;
					double mass = GetMassAndCoGOfAttachedObject( this, ahPayload, cg );
					SetEmptyMass( GetEmptyMass() + mass );
				}

				// add SRM-1 mass to IUS dry mass
				SetEmptyMass( GetEmptyMass() + STAGE1_EMPTYMASS );
			}
		}

		// engine TVC (rate command)
		if (GetThrusterLevel( th_main[0] ) != 0)// SRM-1
		{
			VECTOR3 avel;
			GetAngularVel( avel );

			// pitch
			// command rate
			double newP = ctrlSRM_P.Step( (avel.x * DEG) - manP, simdt );
			// nozzle rate limit
			if ((newP - SRM_P) > SRM_MAX_GIMBAL_RATE) newP = SRM_P + SRM_MAX_GIMBAL_RATE;
			else if ((newP - SRM_P) < -SRM_MAX_GIMBAL_RATE) newP = SRM_P - SRM_MAX_GIMBAL_RATE;
			SRM_P = newP;

			// yaw
			// command rate
			double newY = ctrlSRM_Y.Step( (avel.y * DEG) - manY, simdt );
			// nozzle rate limit
			if ((newY - SRM_Y) > SRM_MAX_GIMBAL_RATE) newY = SRM_Y + SRM_MAX_GIMBAL_RATE;
			else if ((newY - SRM_Y) < -SRM_MAX_GIMBAL_RATE) newY = SRM_Y - SRM_MAX_GIMBAL_RATE;
			SRM_Y = newY;

			// output
			VECTOR3 tv = _V( -sin( range( -SRM1_GIMBAL_RANGE, SRM_Y, SRM1_GIMBAL_RANGE ) * RAD ), sin( range( -SRM1_GIMBAL_RANGE, SRM_P, SRM1_GIMBAL_RANGE ) * RAD ), 1 );
			normalise( tv );
			SetThrusterDir( th_main[0], tv );
		}
		else if (GetThrusterLevel( th_main[1] ) != 0)// SRM-2
		{
			VECTOR3 avel;
			GetAngularVel( avel );

			// pitch
			// command rate
			double newP = ctrlSRM_P.Step( (avel.x * DEG) - manP, simdt );
			// nozzle rate limit
			if ((newP - SRM_P) > SRM_MAX_GIMBAL_RATE) newP = SRM_P + SRM_MAX_GIMBAL_RATE;
			else if ((newP - SRM_P) < -SRM_MAX_GIMBAL_RATE) newP = SRM_P - SRM_MAX_GIMBAL_RATE;
			SRM_P = newP;

			// yaw
			// command rate
			double newY = ctrlSRM_Y.Step( (avel.y * DEG) - manY, simdt );
			// nozzle rate limit
			if ((newY - SRM_Y) > SRM_MAX_GIMBAL_RATE) newY = SRM_Y + SRM_MAX_GIMBAL_RATE;
			else if ((newY - SRM_Y) < -SRM_MAX_GIMBAL_RATE) newY = SRM_Y - SRM_MAX_GIMBAL_RATE;
			SRM_Y = newY;

			// output
			VECTOR3 tv = _V( -sin( range( -SRM2_GIMBAL_RANGE, SRM_Y, SRM2_GIMBAL_RANGE ) * RAD ), sin( range( -SRM2_GIMBAL_RANGE, SRM_P, SRM2_GIMBAL_RANGE ) * RAD ), 1 );
			normalise( tv );
			SetThrusterDir( th_main[1], tv );
		}
		else if (rollRCSonly)
		{
			// re-enable RCS after burns
			EnablePitchYawRCS();
			rollRCSonly = false;
			// reset gimbal command
			SRM_P = 0.0;
			SRM_Y = 0.0;

			SRMlight[0]->Activate( false );
			SRMlight[1]->Activate( false );
		}

		// animation
		if (asEXTENDNOZZLE.Opening())
		{
			asEXTENDNOZZLE.Move( simdt / (STAGE2_EEC_CONE_DEPLOY_DELAY + STAGE2_EEC_CONE_DEPLOY_TIME + STAGE2_EEC_STRIP_ROTATE_DELAY + STAGE2_EEC_STRIP_ROTATE_TIME) );
			SetAnimation( anim_EXTENDNOZZLE, asEXTENDNOZZLE.pos );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkPostStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkPostStep" );
		abort();
	}
}

void IUS_SRM2::DefineAnimations( void )
{
	static UINT EEC1Grp[1] = {GRP_EXTENDABLE_EXIT_CONE_1_IUS_SRM2};
	EEC_1 = new MGROUP_TRANSLATE( mesh_stage, EEC1Grp, 1, _V( 0.0, 0.0, STAGE2_EEC_1_TRANSLATION ) );
	anim_EXTENDNOZZLE = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_EXTENDNOZZLE, tA, tB, EEC_1 );

	static UINT EEC2Grp[1] = {GRP_EXTENDABLE_EXIT_CONE_2_IUS_SRM2};
	EEC_2 = new MGROUP_TRANSLATE( mesh_stage, EEC2Grp, 1, _V( 0.0, 0.0, STAGE2_EEC_2_TRANSLATION ) );
	AddAnimationComponent( anim_EXTENDNOZZLE, tAA, tB, EEC_2 );


	static UINT EECDevice1Grp[1] = {GRP_EEC_EXTENSION_DEVICE_1_IUS_SRM2};
	EEC_DEVICE_1 = new MGROUP_ROTATE( mesh_stage, EECDevice1Grp, 1, _V( 0.404694, -0.404693, -0.442899 ), _V( 0.707107, -0.707107, 0.0 ), static_cast<float>(PI05) );
	ANIMATIONCOMPONENT_HANDLE parent = AddAnimationComponent( anim_EXTENDNOZZLE, tC, 1.0, EEC_DEVICE_1 );

	static UINT EECStrip1Grp[1] = {GRP_EEC_EXTENSION_STRIP_1_IUS_SRM2};
	EEC_STRIP_1 = new MGROUP_SCALE( mesh_stage, EECStrip1Grp, 1, _V( 0.409991, -0.409991, -0.46141 ), _V( 1.0, 1.0, 41.35725 ) );
	AddAnimationComponent( anim_EXTENDNOZZLE, tA, tB, EEC_STRIP_1, parent );


	static UINT EECDevice2Grp[1] = {GRP_EEC_EXTENSION_DEVICE_2_IUS_SRM2};
	EEC_DEVICE_2 = new MGROUP_ROTATE( mesh_stage, EECDevice2Grp, 1, _V( 0.209757, 0.532499, -0.442899 ), _V( 0.366501, 0.930418, 0.0 ), static_cast<float>(PI05) );
	parent = AddAnimationComponent( anim_EXTENDNOZZLE, tC, 1.0, EEC_DEVICE_2 );

	static UINT EECStrip2Grp[1] = {GRP_EEC_EXTENSION_STRIP_2_IUS_SRM2};
	EEC_STRIP_2 = new MGROUP_SCALE( mesh_stage, EECStrip2Grp, 1, _V( 0.212503, 0.53947, -0.46141 ), _V( 1.0, 1.0, 41.35725 ) );
	AddAnimationComponent( anim_EXTENDNOZZLE, tA, tB, EEC_STRIP_2, parent );


	static UINT EECDevice3Grp[1] = {GRP_EEC_EXTENSION_DEVICE_3_IUS_SRM2};
	EEC_DEVICE_3 = new MGROUP_ROTATE( mesh_stage, EECDevice3Grp, 1, _V( -0.541142, -0.18633, -0.442899 ), _V( -0.945519, -0.325568, 0.0 ), static_cast<float>(PI05) );
	parent = AddAnimationComponent( anim_EXTENDNOZZLE, tC, 1.0, EEC_DEVICE_3 );

	static UINT EECStrip3Grp[1] = {GRP_EEC_EXTENSION_STRIP_3_IUS_SRM2};
	EEC_STRIP_3 = new MGROUP_SCALE( mesh_stage, EECStrip3Grp, 1, _V( -0.548226, -0.188769, -0.46141 ), _V( 1.0, 1.0, 41.35725 ) );
	AddAnimationComponent( anim_EXTENDNOZZLE, tA, tB, EEC_STRIP_3, parent );

	asEXTENDNOZZLE.Set( AnimState::CLOSED, 0.0 );
	return;
}

int IUS_SRM2::clbkConsumeBufferedKey( DWORD key, bool down, char* kstate )
{
	try
	{
		if (!down)
		{
			// man gimbal
			if (key == OAPI_KEY_NUMPAD2)
			{
				manP -= VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD8)
			{
				manP -= -VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD1)
			{
				manY -= VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD3)
			{
				manY -= -VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			return 0;
		}

		// man gimbal
		if (key == OAPI_KEY_NUMPAD2)
		{
			manP += VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD8)
		{
			manP += -VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD1)
		{
			manY += VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD3)
		{
			manY += -VEHICLE_MAX_RATE_CMD;
			return 1;
		}

		if ((KEYMOD_SHIFT( kstate ) == false) && (KEYMOD_CONTROL( kstate ) == true) && (KEYMOD_ALT( kstate ) == false))// only CTRL key modifier
		{
			if ((GetThrusterLevel( th_main[0] ) != 0.0) || (GetThrusterLevel( th_main[1] ) != 0.0) || GetAttachmentStatus( ahASE ) || !SRM_ENA) return 0;// no separations while engines are firing or still attached to ASE or nearby OV

			if (key == OAPI_KEY_J)
			{
				// remove payload mass from IUS dry mass
				OBJHANDLE ohPL = GetAttachmentStatus( ahPayload );
				if (ohPL)
				{
					VECTOR3 cg;
					double mass = GetMassAndCoGOfAttachedObject( this, ahPayload, cg );
					SetEmptyMass( GetEmptyMass() - mass );
				}
				// separate payload
				DetachChild( ahPayload, 0.3 );
				return 1;
			}
			else if (key == OAPI_KEY_G)
			{
				if (GetAttachmentStatus( ahSRM1 ) != NULL)
				{
					// detach stage 1
					DetachChild( ahSRM1, 0.2 );

					// update vehicle defs
					SetStage2Config();

					// start EEC deployment
					asEXTENDNOZZLE.action = AnimState::OPENING;
					return 1;
				}
			}
			else if ((key >= OAPI_KEY_1) && (key <= OAPI_KEY_8))
			{
				OBJHANDLE ohPL = GetAttachmentStatus( ahPayload );
				if (ohPL)
				{
					VESSEL* vPL = oapiGetVesselInterface( ohPL );
					if (vPL->Version() >= 2)
						((VESSEL3*)vPL)->clbkGeneric( VMSG_USER + 0x0101, key - 1, NULL );
				}
				return 1;
			}
		}

		if ((KEYMOD_SHIFT( kstate ) == false) && (KEYMOD_CONTROL( kstate ) == false) && (KEYMOD_ALT( kstate ) == false))// no key modifiers
		{
			if (key == OAPI_KEY_ADD)// check for start
			{
				if (SRM_ENA)
				{
					if (GetAttachmentStatus( ahSRM1 ) != NULL)
					{
						SetThrusterLevel( th_main[0], 1 );
						SRMlight[0]->Activate( true );
						rollRCSonly = true;
						InhibitPitchYawRCS();
						return 1;
					}
					else if (asEXTENDNOZZLE.Open())
					{
						SetThrusterLevel( th_main[1], 1 );
						SRMlight[1]->Activate( true );
						rollRCSonly = true;
						InhibitPitchYawRCS();
						return 1;
					}
				}
			}
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkConsumeBufferedKey" );
		abort();
	}
}

void IUS_SRM2::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		SetAnimation( anim_EXTENDNOZZLE, asEXTENDNOZZLE.pos );

		if (!strTextureName.empty()) UpdateTexture( GetDevMesh( vis, mesh_stage ) );

		if (!FourAntennas)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;
			DEVMESHHANDLE hDevStage = GetDevMesh( vis, mesh_stage );

			oapiWriteLog( "(SSV_IUS_SRM2) [INFO] Hiding optional antennas" );
			oapiEditMeshGroup( hDevStage, GRP_ANTENNA_1_IUS_SRM2, &grpSpec );
			oapiEditMeshGroup( hDevStage, GRP_ANTENNA_3_IUS_SRM2, &grpSpec );
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkVisualCreated" );
		abort();
	}
}

void IUS_SRM2::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );

		WriteScenario_state( scn, "EEC", asEXTENDNOZZLE );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkSaveState" );
		abort();
	}
}

void IUS_SRM2::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char *line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				LoadMissionFile();
				AddPayloadAdapter();

				if ((propload[0] >= 0.5) && (propload[0] <= 1.0)) SetPropellantMaxMass( ph_main[0], STAGE1_PROPELLANT_MAXMASS * propload[0] );

				if ((propload[1] >= 0.5) && (propload[1] <= 1.0)) SetPropellantMaxMass( ph_main[1], STAGE2_PROPELLANT_MAXMASS * propload[1] );

				if ((RCStanks >= 1) && (RCStanks <= 3)) SetPropellantMaxMass( ph_rcs, RCS_TANK_PROPELLANT_MASS * RCStanks );
			}
			else if (!_strnicmp( line, "EEC", 3 ))
			{
				sscan_state( line + 3, asEXTENDNOZZLE );
			}
			else ParseScenarioLineEx( line, status );
		}

		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [FATAL ERROR] Exception in IUS_SRM2::clbkLoadStateEx" );
		abort();
	}
}

void IUS_SRM2::UpdateTexture( DEVMESHHANDLE hDevMesh )
{
	if (!hDevMesh) return;// no mesh handle
	if (hTexture == NULL) hTexture = oapiLoadTexture( strTextureName.c_str() );
	if (hTexture == NULL) throw std::exception( "Could not load texture" );
	else oapiSetTexture( hDevMesh, 1, hTexture );
	return;
}

void IUS_SRM2::SetStage2Config( void )
{
	SetDefaultPropellantResource( ph_main[1] );
	SetSize( 3.0 );
	SetEmptyMass( GetEmptyMass() - STAGE1_EMPTYMASS );
	SetPropellantMass( ph_main[0], 0.0 );
	SetCrossSections(_V( 4.29, 8.18, 4.18 ) );
	SetPMI( _V( 0.88, 0.99, 0.84 ) );

	// TODO new TVC consts
	return;
}

void IUS_SRM2::EnableRCS( void ) const
{
	THRUSTER_HANDLE th_group[8];
	//  "BANK-RIGHT"
	th_group[0] = th_rcs[2];
	th_group[1] = th_rcs[8];
	CreateThrusterGroup(th_group, 2, THGROUP_ATT_BANKRIGHT);
	//  "BANK-LEFT"
	th_group[0] = th_rcs[5];
	th_group[1] = th_rcs[11];
	CreateThrusterGroup(th_group, 2, THGROUP_ATT_BANKLEFT);
	//FORWARD
	th_group[0] = th_rcs[0];
	th_group[1] = th_rcs[1];
	th_group[2] = th_rcs[3];
	th_group[3] = th_rcs[4];
	th_group[4] = th_rcs[6];
	th_group[5] = th_rcs[7];
	th_group[6] = th_rcs[9];
	th_group[7] = th_rcs[10];
	CreateThrusterGroup(th_group, 8, THGROUP_ATT_FORWARD);

	EnablePitchYawRCS();
	return;
}

void IUS_SRM2::EnablePitchYawRCS( void ) const
{
	THRUSTER_HANDLE th_group[2];
	//  "PITCH-UP"
	th_group[0] = th_rcs[6];
	th_group[1] = th_rcs[7];
	CreateThrusterGroup(th_group, 2, THGROUP_ATT_PITCHUP);
	//  "PITCH-DOWN"
	th_group[0] = th_rcs[0];
	th_group[1] = th_rcs[1];
	CreateThrusterGroup(th_group, 2, THGROUP_ATT_PITCHDOWN);
	//  "YAW-RIGHT"
	th_group[0] = th_rcs[9];
	th_group[1] = th_rcs[10];
	CreateThrusterGroup(th_group, 2, THGROUP_ATT_YAWRIGHT);
	//  "YAW-LEFT"
	th_group[0] = th_rcs[3];
	th_group[1] = th_rcs[4];
	CreateThrusterGroup(th_group, 2, THGROUP_ATT_YAWLEFT);
	return;
}

void IUS_SRM2::InhibitPitchYawRCS( void ) const
{
	DelThrusterGroup( THGROUP_ATT_PITCHUP );
	DelThrusterGroup( THGROUP_ATT_PITCHDOWN );
	DelThrusterGroup( THGROUP_ATT_YAWRIGHT );
	DelThrusterGroup( THGROUP_ATT_YAWLEFT );
	return;
}

void IUS_SRM2::LoadMissionFile( void )
{
	std::string filename;
	filename = "Missions\\SSV\\" + strMission + ".json";

	FILE* hF = fopen( filename.c_str(), "r" );
	if (hF == NULL)
	{
		oapiWriteLogV( "(SSV_IUS_SRM2) [ERROR] Can't open mission file %s", strMission.c_str() );
		return;
	}

	oapiWriteLogV( "(SSV_IUS_SRM2) [INFO] Loading mission file %s", strMission.c_str() );

	fseek( hF, 0, SEEK_END );
	long filesize = ftell( hF );
	if (filesize < 0)
	{
		fclose( hF );
		return;
	}

	char* missionfilestr = new char[filesize];
	rewind( hF );
	fread( missionfilestr, sizeof(char), filesize, hF );
	fclose( hF );

	cJSON* root = cJSON_Parse( missionfilestr );
	if (!root)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [ERROR] Error parsing mission file version" );
		delete[] missionfilestr;
		return;
	}

	cJSON* version = cJSON_GetObjectItemCaseSensitive( root, "Version" );
	switch (version->valueint)
	{
		case 1:
			LoadMissionV1( root );
			break;
		default:
			oapiWriteLogV( "(SSV_IUS_SRM2) [ERROR] Unknown mission file version %s", version->valueint );
			break;
	}

	cJSON_Delete( root );
	delete[] missionfilestr;
	return;
}

void IUS_SRM2::LoadMissionV1( cJSON* root )
{
	// read UpperStages
	cJSON* us = cJSON_GetObjectItemCaseSensitive( root, "Upper Stages" );
	for (int i = 0; i < cJSON_GetArraySize( us ); i++)
	{
		// find correct item
		cJSON* usi = cJSON_GetArrayItem( us, i );
		if (usi)
		{
			cJSON* name = cJSON_GetObjectItemCaseSensitive( usi, "Name" );
			cJSON* usown = cJSON_GetObjectItemCaseSensitive( usi, "IUS 2-Stage" );
			if ((name) && (usown))
			{
				if (!strcmp( GetName(), name->valuestring ))
				{
					// read own params
					{
						cJSON* tmp = cJSON_GetObjectItemCaseSensitive( usown, "Texture" );
						strTextureName = "SSV\\IUS\\" + std::string( tmp->valuestring ) + ".dds";

						tmp = cJSON_GetObjectItemCaseSensitive( usown, "Load Stage 1" );
						propload[0] = tmp->valuedouble;

						tmp = cJSON_GetObjectItemCaseSensitive( usown, "Load Stage 2" );
						propload[1] = tmp->valuedouble;

						tmp = cJSON_GetObjectItemCaseSensitive( usown, "RCS Tanks" );
						RCStanks = tmp->valueint;

						tmp = cJSON_GetObjectItemCaseSensitive( usown, "4 Antennas" );
						FourAntennas = cJSON_IsTrue( tmp );

					}

					// read payload adapter params
					cJSON* adapter = cJSON_GetObjectItemCaseSensitive( usi, "Adapter" );
					if (adapter)
					{
						cJSON* tmp = cJSON_GetObjectItemCaseSensitive( adapter, "Mesh" );
						AdapterMeshName = tmp->valuestring;

						tmp = cJSON_GetObjectItemCaseSensitive( adapter, "Offset" );
						AdapterOffset = tmp->valuedouble;

						tmp = cJSON_GetObjectItemCaseSensitive( adapter, "Mass" );
						AdapterMass = tmp->valuedouble;
					}
					break;
				}
			}
		}
	}
	return;
}

void IUS_SRM2::AddPayloadAdapter( void )
{
	// small sanity checks
	if (AdapterMeshName.length())
	{
		if (AdapterOffset <= 0.0)
		{
			oapiWriteLog( "(SSV_IUS_SRM2) [ERROR] AdapterOffset was not specified or isn't greater than 0" );
			return;
		}

		if (AdapterMass <= 0.0)
		{
			oapiWriteLog( "(SSV_IUS_SRM2) [ERROR] AdapterMass was not specified or isn't greater than 0" );
			return;
		}
	}
	else return;

	VECTOR3 pos;
	VECTOR3 dir;
	VECTOR3 rot;
	GetAttachmentParams( ahPayload, pos, dir, rot );

	// add mesh
	MESHHANDLE hAdapterMesh = oapiLoadMeshGlobal( AdapterMeshName.c_str() );
	if (hAdapterMesh == NULL)
	{
		oapiWriteLog( "(SSV_IUS_SRM2) [ERROR] AdapterMesh file not found" );
		return;
	}
	SetMeshVisibilityMode( AddMesh( hAdapterMesh, &pos ), MESHVIS_ALWAYS );

	// correct spacecraft attachment
	pos.z += AdapterOffset;
	SetAttachmentParams( ahPayload, pos, dir, rot );

	// correct mass
	SetEmptyMass( GetEmptyMass() + AdapterMass );

	oapiWriteLogV( "(SSV_IUS_SRM2) [INFO] Added payload adapter: mesh:%s|height:%lf|mass:%lf", AdapterMeshName.c_str(), AdapterOffset, AdapterMass );
	return;
}
