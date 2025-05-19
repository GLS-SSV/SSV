/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/07   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/04   GLS
2020/08/24   GLS
2021/06/14   GLS
2021/06/18   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/01/10   GLS
2022/02/20   GLS
2022/07/03   GLS
2022/08/05   GLS
2022/09/29   GLS
2024/12/30   GLS
2025/05/10   GLS
********************************************/
#define ORBITER_MODULE

#include "SLC6.h"
#include <MathSSV.h>
#include "meshres_AT.h"
#include "meshres_Pad.h"
#include "meshres_SAB.h"
#include "meshres_PCR.h"
#include "resource.h"
#include "../OV/Atlantis.h"
#include "../LCC/LCC.h"
#include "../T0UmbilicalReference.h"
#include "../PadLCCInterface.h"
#include <DlgCtrl.h>
#include "../SSVSound.h"
#include <UtilsSSV.h>


HINSTANCE hModule;


static const char* MESHNAME_PADSURFACE = "SSV\\SLC6\\terrain";
static const char* MESHNAME_LAUNCHMOUNT = "SSV\\SLC6\\LaunchMount";
static const char* MESHNAME_TOWER = "SSV\\SLC6\\AT";
static const char* MESHNAME_PCR = "SSV\\SLC6\\PCR";
static const char* MESHNAME_SAB = "SSV\\SLC6\\SAB";
static const char* MESHNAME_MST = "SSV\\SLC6\\MST";
static const char* MESHNAME_PPR = "SSV\\SLC6\\PPR";

constexpr double VERT_MESH_OFFSET = 0.0;
const VECTOR3 PADSURFACE_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );
const VECTOR3 LAUNCHMOUNT_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );
const VECTOR3 TOWER_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );
const VECTOR3 PCR_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );
const VECTOR3 SAB_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );
const VECTOR3 MST_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );
const VECTOR3 PPR_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 0.0 );

const VECTOR3 GOXVENT_LEFT = TOWER_MESH_OFFSET + _V( 9.22983, 59.938, -3.35498 );// East duct
const VECTOR3 GOXVENT_RIGHT = TOWER_MESH_OFFSET + _V( 9.75014, 59.938, -1.17495 );// West duct
const VECTOR3 GOXVENT_DIRREF = _V( 0.4852, -0.8667, -0.1158 );

constexpr double PCR_MOVE_DIST = 228.6;// (750ft) [m]
constexpr double SAB_MOVE_DIST = 87.0204;// (285.5ft) [m]
constexpr double MST_MOVE_DIST = 114.3;// (375ft) [m]


constexpr double SLC6_OAA_RATE_NORMAL = 0.0222222;// 45 seconds [1/sec]
constexpr double SLC6_OAA_RATE_EMERGENCY = 0.0666667;// 15 seconds [1/sec]

constexpr double SLC6_TSM_UMBILICAL_RETRACT_SPEED = 1.181;// sec
constexpr double SLC6_PCR_TRANSLATE_RATE = 6.096 / (PCR_MOVE_DIST * 60.0);// 20ft/min (6.096m/min) [1/sec]
constexpr double SLC6_SAB_TRANSLATE_RATE = 6.096 / (SAB_MOVE_DIST * 60.0);// 20ft/min (6.096m/min) [1/sec]
constexpr double SLC6_MST_TRANSLATE_RATE = 6.096 / (MST_MOVE_DIST * 60.0);// 20ft/min (6.096m/min) [1/sec]
constexpr double SLC6_SAB_DOOR_RATE = 1/600.0;
constexpr double EAA_RATE = 1 / 300.0;
constexpr double SDWW_RATE = 1 / 180.0;

constexpr double SLC6_WATERTANK_CAP = 760000.0;// gallons (400k tank + pipes)
constexpr double SLC6_PRELOWATER_FLOWRATE = 984400.0 / 60.0;// gallons/sec
constexpr double SLC6_POSTLOWATER_FLOWRATE = 0.0;// gallons/sec (no "post-liftoff water")


constexpr unsigned int SLC6_LIGHT_COUNT = 10;
const VECTOR3 SLC6_LIGHT_POS[SLC6_LIGHT_COUNT] = {
	_V( 37.702301, 22.22995, -25.611351 ) + PADSURFACE_MESH_OFFSET, // North-East light 1
	_V( 38.978798, 22.22995, -21.69825 ) + PADSURFACE_MESH_OFFSET, // North-East light 2
	_V( 39.763802, 22.191851, 30.499901 ) + PADSURFACE_MESH_OFFSET, // North-West light 1
	_V( 25.285999, 22.22995, 79.0009 ) + PADSURFACE_MESH_OFFSET, // North-West light 2
	_V( -34.0075, 22.191851, 22.22485 ) + PADSURFACE_MESH_OFFSET, // South-West light
	_V( -48.131451, 22.22995, -20.668301 ) + PADSURFACE_MESH_OFFSET, // South-East light 1
	_V( -55.220299, 22.22995, -28.656151 ) + PADSURFACE_MESH_OFFSET, // South-East light 2
	_V( -44.679298, 22.22995, -64.368752 ) + PADSURFACE_MESH_OFFSET, // South-East light 3
	_V( -44.679298, 22.22995, -91.698746 ) + PADSURFACE_MESH_OFFSET, // South-East light 4
	_V( -44.679298, 22.22995, -121.147995 ) + PADSURFACE_MESH_OFFSET // South-East light 5
};
const VECTOR3 SLC6_LIGHT_DIR[SLC6_LIGHT_COUNT] = {
	_V( -1.0, 0.0, 0.0 ), // North-East light 1
	_V( -0.819152, 0.0, 0.573576 ), // North-East light 2
	_V( -0.866025, 0.0, -0.5 ), // North-West light 1
	_V( -1.0, 0.0, 0.0 ), // North-West light 2
	_V( 0.981627, 0.0, -0.190809 ), // South-West light
	_V( 0.939693, 0.0, 0.342020 ), // South-East light 1
	_V( 1.0, 0.0, 0.0 ), // South-East light 2
	_V( 1.0, 0.0, 0.0 ), // South-East light 3
	_V( 1.0, 0.0, 0.0 ), // South-East light 4
	_V( 1.0, 0.0, 0.0 )  // South-East light 5
};
const COLOUR4 SLC6_LIGHT_DIFFUSE = { 0.3f, 0.3f, 0.3f, 0 };
const COLOUR4 SLC6_LIGHT_SPECULAR = {0,0,0,0};
const COLOUR4 SLC6_LIGHT_AMBIENT = { 1.0f, 1.0f, 1.0f, 0.0f };
constexpr double SLC6_LIGHT_RANGE = 100.0;
constexpr double SLC6_LIGHT_ATT0 = 1e-3;
constexpr double SLC6_LIGHT_ATT1 = 0;
constexpr double SLC6_LIGHT_ATT2 = 0.00025;
const double SLC6_LIGHT_UMBRA = 30.0*RAD;//45.0 default
const double SLC6_LIGHT_PENUMBRA = 120.0*RAD;//180.0 default

const VECTOR3 HDP_POS = _V( 0.0, 9.1813, 0.0 ) + LAUNCHMOUNT_MESH_OFFSET;

constexpr VECTOR3 OAA_DIR = {-0.982301, 0.0, 0.187309};
const double OAA_MOVE_DIST = 20.0;// [m]

constexpr VECTOR3 GVA_POS = {25.9842, 0.0, -6.20165};
constexpr VECTOR3 GVA_DIR = {0.0, -1.0, 0.0};

const double GVA_ANGLE_MIN = -4.0 * RAD;
const double GVA_ANGLE_MAX = 76.5763343749973510306847789144588 * RAD;
const double GVA_ANGLE = GVA_ANGLE_MAX - GVA_ANGLE_MIN;


const VECTOR3 PCR_DOOR_DIR = _V( 0.0, 1.0, 0.0 );

const float PCR_DOOR_1_ROT = static_cast<float>(-180.0 * RAD);
const VECTOR3 PCR_DOOR_1_PORT_POS = _V( 2.50958, 0.0, 240.956 );
const VECTOR3 PCR_DOOR_1_STBD_POS = _V( -2.50958, 0.0, 240.956 );

const float PCR_DOOR_2_ROT = static_cast<float>(90.0 * RAD);
const VECTOR3 PCR_DOOR_2_PORT_POS = _V( 5.01917, 0.0, 241.335 );
const VECTOR3 PCR_DOOR_2_STBD_POS = _V( -5.01917, 0.0, 241.335 );


const COLOUR4 PCR_LIGHT_DIFFUSE = {1.0f, 1.0f, 1.0f, 1.0f};
const COLOUR4 PCR_LIGHT_SPECULAR = {0.0f, 0.0f, 0.0f, 0.0f};
const COLOUR4 PCR_LIGHT_AMBIENT = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr double PCR_LIGHT_RANGE = 15.0;
constexpr double PCR_LIGHT_ATT0 = 1.0;
constexpr double PCR_LIGHT_ATT1 = 0.1;
constexpr double PCR_LIGHT_ATT2 = 0.01;
const double PCR_LIGHT_UMBRA = 45.0 * RAD;
const double PCR_LIGHT_PENUMBRA = 100.0 * RAD;


SLC6::SLC6(OBJHANDLE hVessel, int flightmodel)
	: BaseSSVPad(hVessel, flightmodel, SLC6_WATERTANK_CAP, SLC6_PRELOWATER_FLOWRATE, SLC6_POSTLOWATER_FLOWRATE),
	pXRSound(NULL)
{
	hPadSurfaceMesh = oapiLoadMeshGlobal( MESHNAME_PADSURFACE );
	hLaunchMountMesh = oapiLoadMeshGlobal( MESHNAME_LAUNCHMOUNT );
	hTowerMesh = oapiLoadMeshGlobal( MESHNAME_TOWER );
	hPCRMesh = oapiLoadMeshGlobal( MESHNAME_PCR );
	hSABMesh = oapiLoadMeshGlobal( MESHNAME_SAB );
	hMSTMesh = oapiLoadMeshGlobal( MESHNAME_MST );
	hPPRMesh = oapiLoadMeshGlobal( MESHNAME_PPR );

	GOXVentLevel = 0.0;

	OAA_State.Set(AnimState::CLOSED, 0.0);
	GVA_State.Set(AnimState::CLOSED, 0.0);
	GOXVentHood_State.Set(AnimState::OPEN, 1.0);
	ETVAS_State.Set(AnimState::CLOSED, 0.0);
	T0Umbilical_State.Set(AnimState::CLOSED, 0.0);
	IAA_State.Set(AnimState::CLOSED, 0.0);
	PCR_State.Set(AnimState::CLOSED, 0.0);
	SAB_State.Set(AnimState::CLOSED, 0.0);
	MST_State.Set(AnimState::CLOSED, 0.0);
	SABDoor_State.Set(AnimState::CLOSED, 0.0);
	EAA_State.Set( AnimState::OPEN, 1.0 );
	SSMEDuctWestWall_State.Set( AnimState::CLOSED, 0.0 );

	sprintf_s( LCCName, sizeof(LCCName), "" );

	pSTS = NULL;
	pLCC = NULL;

	HBOIOn = false;
	HBOILevel = 0.0;
	HBOITime = 35.0;

	pcrref[0] = _V( 4.5, 33.7249, 243.673 ) + PCR_MESH_OFFSET;// POS port top
	pcrref[1] = _V( 4.5, 29.2249, 243.673 ) + PCR_MESH_OFFSET;// POS port center
	pcrref[2] = _V( 4.5, 24.7249, 243.673 ) + PCR_MESH_OFFSET;// POS port aft
	pcrref[3] = _V( -4.5, 33.7249, 243.673 ) + PCR_MESH_OFFSET;// POS starboard top
	pcrref[4] = _V( -4.5, 29.2249, 243.673 ) + PCR_MESH_OFFSET;// POS starboard center
	pcrref[5] = _V( -4.5, 24.7249, 243.673 ) + PCR_MESH_OFFSET;// POS starboard aft
	pcrref[6] = _V( -0.707107, 0.0, -0.707107 );// DIR port top
	pcrref[7] = _V( -0.707107, 0.0, -0.707107 );// DIR port center
	pcrref[8] = _V( -0.707107, 0.0, -0.707107 );// DIR port aft
	pcrref[9] = _V( 0.707107, 0.0, -0.707107 );// DIR starboard top
	pcrref[10] = _V( 0.707107, 0.0, -0.707107 );// DIR starboard center
	pcrref[11] = _V( 0.707107, 0.0, -0.707107 );// DIR starboard aft
}

SLC6::~SLC6()
{
}

void SLC6::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		padsurface_mesh_idx = AddMesh( hPadSurfaceMesh, &PADSURFACE_MESH_OFFSET );
		launchmount_mesh_idx = AddMesh( hLaunchMountMesh, &LAUNCHMOUNT_MESH_OFFSET );
		tower_mesh_idx = AddMesh( hTowerMesh, &TOWER_MESH_OFFSET );
		pcr_mesh_idx = AddMesh( hPCRMesh, &PCR_MESH_OFFSET );
		sab_mesh_idx = AddMesh( hSABMesh, &SAB_MESH_OFFSET );
		mst_mesh_idx = AddMesh( hMSTMesh, &MST_MESH_OFFSET );
		ppr_mesh_idx = AddMesh( hPPRMesh, &PPR_MESH_OFFSET );

		ahHDP = CreateAttachment( false, HDP_POS, _V( 0.0, 1.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), "XHDP" );

		DefineAnimations();
		DefineHBOIs();
		DefineSSS();
		DefineExhaustSteam();
		DefineGOXVents();

		SetOrbiterAccessArmRate( SLC6_OAA_RATE_NORMAL, OAA_RATE_NORMAL );
		SetOrbiterAccessArmRate( SLC6_OAA_RATE_EMERGENCY, OAA_RATE_EMERGENCY );
		SetEmptyMass(2000001);
		SetSize( 300 );

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 0.0, -16.0, 1.0 ), 1e8, 1e2, 5, 5},
			{_V( -0.866025, -16.0, -0.5 ), 1e8, 1e2, 5, 5},
			{_V( 0.866025, -16.0, -0.5 ), 1e8, 1e2, 5, 5},
			{_V( 0.0, 50.0, 0.0 ), 1e8, 1e2, 5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		CreateStadiumLights(SLC6_LIGHT_POS, SLC6_LIGHT_DIR, SLC6_LIGHT_COUNT, SLC6_LIGHT_RANGE, SLC6_LIGHT_ATT0, SLC6_LIGHT_ATT1, SLC6_LIGHT_ATT2, SLC6_LIGHT_UMBRA, SLC6_LIGHT_PENUMBRA, SLC6_LIGHT_DIFFUSE, SLC6_LIGHT_SPECULAR, SLC6_LIGHT_AMBIENT);

		CreatePCRLights( pcrref, pcrref + 6, 6, PCR_LIGHT_RANGE, PCR_LIGHT_ATT0, PCR_LIGHT_ATT1, PCR_LIGHT_ATT2, PCR_LIGHT_UMBRA, PCR_LIGHT_PENUMBRA, PCR_LIGHT_DIFFUSE, PCR_LIGHT_SPECULAR, PCR_LIGHT_AMBIENT );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkSetClassCaps" );
		abort();
	}
}

void SLC6::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		UpdatePCRLights( pcrref, pcrref + 6, 6 );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkVisualCreated" );
		abort();
	}
}

void SLC6::clbkPostCreation()
{
	try
	{
		// get pointer to T0UmbilicalReference
		OBJHANDLE hSTS = GetAttachmentStatus( ahHDP );
		if (hSTS != NULL)
		{
			VESSEL* pVessel = oapiGetVesselInterface( hSTS );
			if (pVessel != NULL)
			{
				if (!_strnicmp( pVessel->GetClassName(), "SSV_OV", 6 ))
				{
					pSTS = (static_cast<Atlantis*>(pVessel))->T0UmbRef();
					oapiWriteLog( "(SSV_SLC6) [INFO] Connected to T0UmbilicalReference" );
				}
			}
		}

		// get pointer to PadLCCInterface
		OBJHANDLE hLCC = oapiGetVesselByName( LCCName );
		if (hLCC != NULL)
		{
			VESSEL* pVessel = oapiGetVesselInterface( hLCC );
			if (pVessel != NULL)
			{
				if (!_strnicmp( pVessel->GetClassName(), "SSV_LCC", 7 ))
				{
					pLCC = static_cast<LCC*>(pVessel);
					oapiWriteLog( "(SSV_SLC6) [INFO] Connected to PadLCCInterface" );
				}
			}
		}

		// load XRSound
		pXRSound = XRSound::CreateInstance( this );

		// disable default sounds
		pXRSound->SetDefaultSoundEnabled( XRSound::AudioGreeting, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::MainEngines, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RetroEngines, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::HoverEngines, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::SwitchOn, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::SwitchOff, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::CustomEngines, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::AFPitch, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::AFOn, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::AFOff, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::Touchdown, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::OneHundredKnots, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::Liftoff, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::WarningGearIsUp, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::YouAreClearedToLand, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::Docking, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::DockingCallout, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::Undocking, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::UndockingCallout, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::Wheekbrakes, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::DockingRadarBeep, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::AutopilotOn, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::AutopilotOff, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::SubsonicCallout, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RCSAttackPlusX, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RCSAttackPlusY, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RCSAttackPlusZ, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RCSAttackMinusX, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RCSAttackMinusY, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::RCSAttackMinusZ, false );

		pXRSound->SetDefaultSoundEnabled( XRSound::RadioATCGroup, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::CabinAmbienceGroup, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::MachCalloutsGroup, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::AltitudeCalloutsGroup, false );
		pXRSound->SetDefaultSoundEnabled( XRSound::DockingDistanceCalloutsGroup, false );

		// define custom sounds
		pXRSound->LoadWav( RSS_ROTATE_SOUND, RSS_ROTATE_SOUND_FILE, XRSound::PlaybackType::BothViewFar );
		pXRSound->LoadWav( CRYO_HISS, CRYO_HISS_SOUND_FILE, XRSound::PlaybackType::BothViewFar );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkPostCreation" );
		abort();
	}
}

void SLC6::clbkPreStep(double simt, double simdt, double mjd)
{
	try
	{
		BaseSSVPad::clbkPreStep(simt, simdt, mjd);

		bool RSS_Sound_On = false;

		if(T0Umbilical_State.Moving()) {
			double dp=simdt*SLC6_TSM_UMBILICAL_RETRACT_SPEED;
			T0Umbilical_State.Move(dp);
			SetAnimation(anim_T0Umb, T0Umbilical_State.pos);
		}

		if(PCR_State.Moving()) {
			PCR_State.Move(simdt*SLC6_PCR_TRANSLATE_RATE);
			SetAnimation(anim_PCR, PCR_State.pos);
			RSS_Sound_On = true;
			UpdatePCRLights( pcrref, pcrref + 6, 6 );
		}

		if(SAB_State.Moving()) {
			SAB_State.Move(simdt*SLC6_SAB_TRANSLATE_RATE);
			SetAnimation(anim_SAB, SAB_State.pos);
			RSS_Sound_On = true;
		}

		if(SABDoor_State.Moving()) {
			SABDoor_State.Move(simdt*SLC6_SAB_DOOR_RATE);
			SetAnimation(anim_SABDoor, SABDoor_State.pos);
		}

		if (EAA_State.Moving())
		{
			EAA_State.Move( simdt * EAA_RATE );
			SetAnimation( anim_EAA, EAA_State.pos );
		}

		if (MST_State.Moving())
		{
			MST_State.Move(simdt*SLC6_MST_TRANSLATE_RATE);
			SetAnimation(anim_MST, MST_State.pos);
			RSS_Sound_On = true;
		}
		
		if (SSMEDuctWestWall_State.Moving())
		{
			SSMEDuctWestWall_State.Move( simdt * SDWW_RATE );
			SetAnimation( anim_SSMEDuctWestWall, SSMEDuctWestWall_State.pos );
		}

		if (RSS_Sound_On) SoundPlay( pXRSound, RSS_ROTATE_SOUND, true );
		else SoundStop( pXRSound, RSS_ROTATE_SOUND );

		SoundPlay( pXRSound, CRYO_HISS, true );

		// HBOI operation
		if (HBOIOn)
		{
			HBOITime -= simdt;
			if (HBOITime <= 0.0)
			{
				HBOIOn = false;
				HBOILevel = 0.0;
			}
			else HBOILevel = 1.0;
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkPreStep" );
		abort();
	}
}

void SLC6::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		SaveState( scn );

		if (HBOIOn) oapiWriteScenario_float( scn, "HBOI", HBOITime );

		WriteScenario_state(scn, "T0_UMB", T0Umbilical_State);
		WriteScenario_state(scn, "PCR", PCR_State);
		WriteScenario_state(scn, "SAB", SAB_State);
		WriteScenario_state(scn, "MST", MST_State);
		WriteScenario_state(scn, "SABDoor", SABDoor_State);
		WriteScenario_state( scn, "EAA", EAA_State );
		WriteScenario_state( scn, "SDWW", SSMEDuctWestWall_State );
		oapiWriteScenario_string( scn, "LCC_NAME", LCCName );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkSaveState" );
		abort();
	}
}

void SLC6::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "HBOI", 4 ))
			{
				sscanf_s( line + 4, "%lf", &HBOITime );
				HBOIOn = true;
			}
			else if (!_strnicmp( line, "T0_UMB", 6 ))
			{
				sscan_state( line + 6, T0Umbilical_State );
				SetAnimation( anim_T0Umb, T0Umbilical_State.pos );
			}
			else if (!_strnicmp( line, "PCR ", 4 ))
			{
				sscan_state( line + 3, PCR_State );
				SetAnimation( anim_PCR, PCR_State.pos );
			}
			else if (!_strnicmp( line, "SAB ", 4 ))
			{
				sscan_state( line + 3, SAB_State );
				SetAnimation( anim_SAB, SAB_State.pos );
			}
			else if (!_strnicmp( line, "MST", 3 ))
			{
				sscan_state( line + 3, MST_State );
				SetAnimation( anim_MST, MST_State.pos );
			}
			else if (!_strnicmp( line, "SABDoor", 7 ))
			{
				sscan_state( line + 7, SABDoor_State );
				SetAnimation( anim_SABDoor, SABDoor_State.pos );
			}
			else if (!_strnicmp( line, "EAA", 3 ))
			{
				sscan_state( line + 3, EAA_State );
				SetAnimation( anim_EAA, EAA_State.pos );
			}
			else if (!_strnicmp( line, "SDWW", 4 ))
			{
				sscan_state( line + 4, SSMEDuctWestWall_State );
				SetAnimation( anim_SSMEDuctWestWall, SSMEDuctWestWall_State.pos );
			}
			else if (!_strnicmp( line, "LCC_NAME", 8 ))
			{
				sscanf_s( line + 8, "%s", LCCName, sizeof(LCCName) );
			}
			else if (LoadState( line ) == false)
				ParseScenarioLineEx( line, status );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkLoadStateEx" );
		abort();
	}
}

int SLC6::clbkConsumeBufferedKey(DWORD key, bool down, char * keystate)
{
	try
	{
		if(!down) return 0; //only handle keydown events

		if (KEYMOD_CONTROL(keystate))
		{
			switch(key)
			{
				case OAPI_KEY_SPACE:
					if (oapiOpenDialogEx(hModule, IDD_DLG_ANIMCTRL, SLC6_DlgProc, DLG_CAPTIONCLOSE, this))
						oapiWriteLog( "(SSV_SCL6) [INFO] Dialog opened" );
					else if(hModule) sprintf_s(oapiDebugString(), 256, "Error: %d", GetLastError());
					return 1;
				case OAPI_KEY_C:
					if(PCR_State.Closed()) ExtendPCR();
					else RetractPCR();
					return 1;
				case OAPI_KEY_Y:
					if(SAB_State.Closed()) ExtendSAB();
					else RetractSAB();
					return 1;
				case OAPI_KEY_M:
					if(MST_State.Closed()) ExtendMST();
					else RetractMST();
					return 1;
				case OAPI_KEY_D:
					if(SABDoor_State.Closed()) OpenSABDoor();
					else CloseSABDoor();
					return 1;
			}
		}

		return BaseSSVPad::clbkConsumeBufferedKey( key, down, keystate );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6::clbkConsumeBufferedKey" );
		abort();
	}
}

void SLC6::ExtendOAA( int mode )
{
	// only move OAA when MST is retracted or extended
	if (!MST_State.Closed() && !MST_State.Open()) return;
	oaa_mode = mode;
	OAA_State.action=AnimState::OPENING;
}

void SLC6::RetractOAA()
{
	// only move OAA when MST is retracted or extended
	if (!MST_State.Closed() && !MST_State.Open()) return;
	oaa_mode = OAA_RATE_NORMAL;
	OAA_State.action=AnimState::CLOSING;
}

void SLC6::ExtendGVA()
{
	// only extend GVA when hood is closed (retracted), SAB and MST are retracted
	if (GOXVentHood_State.Closed() && SAB_State.Closed() && MST_State.Closed())
		GVA_State.action = AnimState::OPENING;
}

void SLC6::ExtendPCR()
{
	// only move PCR with SAB doors open
	if (SABDoor_State.Open())
		PCR_State.action = AnimState::OPENING;
}

void SLC6::HaltPCR()
{
	if (PCR_State.Moving()) PCR_State.action = AnimState::STOPPED;
}

void SLC6::RetractPCR()
{
	// only move PCR with SAB doors open
	if (SABDoor_State.Open())
		PCR_State.action = AnimState::CLOSING;
}

void SLC6::ExtendSAB()
{
	// only extend SAB if GVA is retracted
	if (GVA_State.Closed())
		SAB_State.action = AnimState::OPENING;
}

void SLC6::HaltSAB()
{
	if (SAB_State.Moving()) SAB_State.action = AnimState::STOPPED;
}

void SLC6::RetractSAB()
{
	SAB_State.action = AnimState::CLOSING;
}

void SLC6::OpenSABDoor()
{
	SABDoor_State.action = AnimState::OPENING;
}

void SLC6::HaltSABDoor()
{
	if (SABDoor_State.Moving()) SABDoor_State.action = AnimState::STOPPED;
}

void SLC6::CloseSABDoor()
{
	SABDoor_State.action = AnimState::CLOSING;
}

void SLC6::ExtendMST()
{
	// only extend MST if EAA is retracted, OAA is retracted and GVA is retracted
	if (EAA_State.Closed() && OAA_State.Closed() && GVA_State.Closed())
		MST_State.action = AnimState::OPENING;
}

void SLC6::HaltMST()
{
	if (MST_State.Moving()) MST_State.action = AnimState::STOPPED;
}

void SLC6::RetractMST()
{
	// only retract MST if OAA is retracted
	if (OAA_State.Closed())
	MST_State.action = AnimState::CLOSING;
}

void SLC6::DefineHBOIs( void )
{
	const VECTOR3 FWD_LEFT_HBOI_POS = _V( 4.12067, 11.5222, 8.97939 ) + LAUNCHMOUNT_MESH_OFFSET;
	const VECTOR3 FWD_RIGHT_HBOI_POS = _V( -4.12067, 11.5222, 8.97939 ) + LAUNCHMOUNT_MESH_OFFSET;
	const VECTOR3 AFT_LEFT_HBOI_POS = _V( -4.37154, 11.0831, 5.29769) + LAUNCHMOUNT_MESH_OFFSET;
	const VECTOR3 AFT_LEFT_HBOI2_POS = _V( -4.37797, 11.1063, 5.42249 ) + LAUNCHMOUNT_MESH_OFFSET;
	const VECTOR3 AFT_RIGHT_HBOI_POS = _V( 4.37154, 11.0831, 5.29769 ) + LAUNCHMOUNT_MESH_OFFSET;
	const VECTOR3 AFT_RIGHT_HBOI2_POS = _V( 4.37797, 11.1063, 5.42249 ) + LAUNCHMOUNT_MESH_OFFSET;

	static PARTICLESTREAMSPEC HBOI_Stream = {
		0, 0.1, 300.0, 17.5, 0.2, 0.25, 0, 0.5, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};
	HBOI_Stream.tex = oapiRegisterParticleTexture( "contrail3" );

	AddParticleStream( &HBOI_Stream, FWD_LEFT_HBOI_POS, _V( -0.985, 0.0, 0.174 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, FWD_RIGHT_HBOI_POS, _V( 0.985, 0.0, 0.174 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_LEFT_HBOI_POS, _V( -1.0, 0.0, 0.0 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_LEFT_HBOI2_POS, _V( -0.985, 0.0, 0.174 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_RIGHT_HBOI_POS, _V( 1.0, 0.0, 0.0 ), &HBOILevel );
	AddParticleStream( &HBOI_Stream, AFT_RIGHT_HBOI2_POS, _V( 0.985, 0.0, 0.174 ), &HBOILevel );

	return;
}

void SLC6::DefineSSS( void )
{
	static PARTICLESTREAMSPEC sss_water = {
		0, 0.05, 30.0, 18.0, 0.05, 0.45, 5.0, 4.0, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC sss_water_FSS = {
		0, 1.0, 10.0, 9.0, 0.1, 1.5, 0.5, 1.0, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC sss_water_Firex = {
		0, 0.1, 60.0, 10.0, 0.5, 0.4, 1.5, 0.8, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	//// Pre L/O Water ////
	// SSME hole
	for (int i = 0; i < 10; i++)
	{
		double zposTSM = 4.62936 + (0.52 * i);// first E nozzle
		double zpos = 11.3801 + (0.47 * i);// first E nozzle
		AddParticleStream( &sss_water, _V( 4.80043, 7.9649, zposTSM ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N (TSM)
		AddParticleStream( &sss_water, _V( 5.334, 8.77392, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N
		AddParticleStream( &sss_water, _V( -4.80043, 7.9649, zposTSM ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S (TSM)
		AddParticleStream( &sss_water, _V( -5.334, 8.77392, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S
	}
	for (int i = 0; i < 20; i++)
	{
		double xpos = 4.6 - (0.46 * i);// first N nozzle
		AddParticleStream( &sss_water, _V( xpos, 8.23724, 4.58277 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, -0.707107, 0.707107 ), &PreLOWaterLevel );// E
	}

	// SRB primary hole
	for (int i = 0; i < 9; i++)
	{
		double zpos = -1.6 + (i * 0.4);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 9.07495, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N outside (top)
		AddParticleStream( &sss_water, _V( 9.07495, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N outside (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -9.07495, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S outside (top)
		AddParticleStream( &sss_water, _V( -9.07495, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S outside (bottom)
	}
	for (int i = 0; i < 10; i++)
	{
		double zpos = -1.6 + (i * 0.4);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 3.3147, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N inside (top)
		AddParticleStream( &sss_water, _V( 3.3147, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N inside (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -3.3147, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S inside (top)
		AddParticleStream( &sss_water, _V( -3.3147, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S inside (bottom)
	}
	for (int i = 0; i < 5; i++)
	{
		double xpos = 5.77 + (i * 0.3);// first S nozzle (LH)
		// LH
		AddParticleStream( &sss_water, _V( xpos, 7.3079, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, -0.707107, -0.707107 ), &PreLOWaterLevel );// W (top)
		AddParticleStream( &sss_water, _V( xpos, 6.8019, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, -0.707107, -0.707107 ), &PreLOWaterLevel );// W (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -xpos, 7.3079, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, -0.707107, -0.707107 ), &PreLOWaterLevel );// W (top)
		AddParticleStream( &sss_water, _V( -xpos, 6.8019, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, -0.707107, -0.707107 ), &PreLOWaterLevel );// W (bottom)
	}

	// SRB secondary hole
	for (int i = 0; i < 12; i++)
	{
		double zpos = -12.85 + (i * 0.65);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 12.0081, 1.2, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (top)
		if (i > 0) AddParticleStream( &sss_water, _V( 11.5053, 0.55, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (bottom)
		AddParticleStream( &sss_water, _V( 2.3, 1.2, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (top)
		if (i > 0) AddParticleStream( &sss_water, _V( 2.83, 0.55, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -2.3, 1.2, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (top)
		if (i > 0) AddParticleStream( &sss_water, _V( -2.83, 0.55, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (bottom)
		AddParticleStream( &sss_water, _V( -12.0081, 1.2, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (top)
		if (i > 0) AddParticleStream( &sss_water, _V( -11.5053, 0.55, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (bottom)
	}

	// SRB curtain
	for (int i = 0; i < 2; i++)
	{
		double zpos = -4.1 + (i * 0.94);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 3.3147, 7.2679, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N horiz inside (top)
		AddParticleStream( &sss_water, _V( 3.3147, 6.7619, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N horiz inside (middle)
		AddParticleStream( &sss_water, _V( 3.3147, 6.2559, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N horiz inside (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -3.3147, 7.2679, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S horiz inside (top)
		AddParticleStream( &sss_water, _V( -3.3147, 6.7619, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S horiz inside (middle)
		AddParticleStream( &sss_water, _V( -3.3147, 6.2559, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S horiz inside (bottom)
	}
	for (int i = 0; i < 14; i++)
	{
		double ypos = 7.3079 - (i * 0.45);// top nozzle
		// LH
		AddParticleStream( &sss_water, _V( 3.3147, ypos, -4.72914 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert inside
		// RH
		AddParticleStream( &sss_water, _V( -3.3147, ypos, -4.72914 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert inside
	}
	for (int i = 0; i < 3; i++)
	{
		double zpos = -4.0 + (i * 0.33);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 9.07495, 7.2679, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N horiz outside (middle)
		AddParticleStream( &sss_water, _V( 9.07495, 6.7619, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N horiz outside (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -9.07495, 7.2679, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S horiz outside (middle)
		AddParticleStream( &sss_water, _V( -9.07495, 6.7619, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S horiz outside (bottom)
	}
	double _xpos = 9.0749;
	for (int i = 0; i < 13; i++)
	{
		double ypos = 6.8579 - (i * 0.43);// second top nozzle
		if (i > 5) _xpos += 0.2;
		// LH
		AddParticleStream( &sss_water, _V( _xpos, ypos, -4.72914 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert outside
		// RH
		AddParticleStream( &sss_water, _V( -_xpos, ypos, -4.72914 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert outside
	}
	// LH
	AddParticleStream( &sss_water, _V( 9.07495, 7.2679, -4.53 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert outside (top)
	AddParticleStream( &sss_water, _V( 9.07495, 7.2679, -4.93 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert outside (top)
	// RH
	AddParticleStream( &sss_water, _V( -9.07495, 7.2679, -4.53 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert outside (top)
	AddParticleStream( &sss_water, _V( -9.07495, 7.2679, -4.93 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert outside (top)

	// pad surface
	for (int i = 0; i < 7; i++)
	{
		double xpos = 3.6 + (i * 1.4);// center-most nozzle (N)
		AddParticleStream( &sss_water, _V( xpos, 2.0, -15.433 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// E (N)
		AddParticleStream( &sss_water, _V( -xpos, 2.0, -15.433 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// E (S)
	}
	AddParticleStream( &sss_water, _V( 14.0933, 2.0, -14.96 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.866025, 0.0, -0.5 ), &PreLOWaterLevel );// NE (N)
	AddParticleStream( &sss_water, _V( 13.5, 2.0, -15.433 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.5, 0.0, -0.866025 ), &PreLOWaterLevel );// NE (E)
	AddParticleStream( &sss_water, _V( -13.5, 2.0, -15.433 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.5, 0.0, -0.866025 ), &PreLOWaterLevel );// SE (E)
	AddParticleStream( &sss_water, _V( -14.0933, 2.0, -14.96 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.866025, 0.0, -0.5 ), &PreLOWaterLevel );// SE (S)
	for (int i = 0; i < 8; i++)
	{
		double zpos = -5.0 - (i * 1.35);// first W nozzle
		AddParticleStream( &sss_water, _V( 14.0933, 2.0, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N
		AddParticleStream( &sss_water, _V( -14.0933, 2.0, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S
	}

	// Access Tower
	AddParticleStream( &sss_water_FSS, _V( 21.0, 44.0, -7.5 ) + TOWER_MESH_OFFSET, _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA
	AddParticleStream( &sss_water_FSS, _V( 18.0, 44.0, -7.5 ) + TOWER_MESH_OFFSET, _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA
	AddParticleStream( &sss_water_FSS, _V( 15.0, 44.0, -7.5 ) + TOWER_MESH_OFFSET, _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA

	//// Firex ////
	// Orbiter SSME Water Deluge System
	AddParticleStream( &sss_water_Firex, _V( 4.43165, 9.4488, 4.13884 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.353553, 0.866025, 0.353553 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, _V( 1.78439, 9.4488, 4.13884 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.866025, 0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole E
	AddParticleStream( &sss_water_Firex, _V( -1.78439, 9.4488, 4.13884 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.866025, 0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole E
	AddParticleStream( &sss_water_Firex, _V( -4.43165, 9.4488, 4.13884 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.353553, 0.866025, 0.353553 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SE

	AddParticleStream( &sss_water_Firex, _V( 5.24284, 10.784, 11.9884 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole N
	AddParticleStream( &sss_water_Firex, _V( 5.24284, 10.784, 12.7602 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole N
	AddParticleStream( &sss_water_Firex, _V( 5.24284, 10.784, 13.4003 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, _V( 5.24284, 10.784, 13.7207 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW

	AddParticleStream( &sss_water_Firex, _V( -5.24284, 10.784, 11.9884 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole S
	AddParticleStream( &sss_water_Firex, _V( -5.24284, 10.784, 12.7602 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole S
	AddParticleStream( &sss_water_Firex, _V( -5.24284, 10.784, 13.4003 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SW
	AddParticleStream( &sss_water_Firex, _V( -5.24284, 10.784, 13.7207 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SW

	// LH2/LO2 T-0 Water Deluge System
	AddParticleStream( &sss_water_Firex, _V( 4.47149, 17.5496, 9.2353 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, 0.0, -0.707107 ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// LH2
	AddParticleStream( &sss_water_Firex, _V( -4.47149, 17.5496, 9.2353 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, 0.0, -0.707107 ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// LO2

	// Orbiter Skin Spray System
	AddParticleStream( &sss_water_Firex, _V( 4.73633, 18.0309, 9.76481 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-1 (W)
	AddParticleStream( &sss_water_Firex, _V( 4.8656, 18.0309, 6.80406 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-1 (E)
	AddParticleStream( &sss_water_Firex, _V( -4.73633, 18.0309, 9.76481 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-2 (W)
	AddParticleStream( &sss_water_Firex, _V( -4.8656, 18.0309, 6.80406 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-2 (E)
	return;
}

void SLC6::DefineExhaustSteam( void )
{
	static PARTICLESTREAMSPEC sss_steam_SSME = {
		0, 8, 50, 400.0, 0.3, 15, 6, 6, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1.0};
	sss_steam_SSME.tex = oapiRegisterParticleTexture( "contrail4" );

	static PARTICLESTREAMSPEC sss_steam_SRB = {
		0, 8, 100, 1000.0, 0.5, 12, 7, 30, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1.0};
	sss_steam_SRB.tex = oapiRegisterParticleTexture( "SSV\\SRB\\SRB_contrail" );

	AddParticleStream(&sss_steam_SSME, _V( -25.146, -10.8363, 47.0916 ) + PADSURFACE_MESH_OFFSET, _V( -cos( 10.0 * RAD ), sin( 10.0 * RAD ), 0.0 ), &fSSMESteamLevel );
	AddParticleStream( &sss_steam_SRB, _V( -36.0794, -7.88933, -4.572 ) + PADSURFACE_MESH_OFFSET, _V( -cos( 10.0 * RAD ), sin( 10.0 * RAD ), 0.0 ), &fSRBSteamLevel );// S
	AddParticleStream( &sss_steam_SRB, _V( 36.0794, -7.88933, -4.572 ) + PADSURFACE_MESH_OFFSET, _V (cos( 10.0 * RAD ), sin( 10.0 * RAD ), 0.0 ), &fSRBSteamLevel );// N
	return;
}

void SLC6::CalculateSteamProduction( double simt, double simdt )
{
	VECTOR3 M0, M1, M2, M3;// MPS Hole
	VECTOR3 L0, L1, L2, L3;// Left SRB Hole
	VECTOR3 R0, R1, R2, R3;// Right SRB Hole

	Local2Global( _V( 5.334, 0.0, 6.8199 ) + LAUNCHMOUNT_MESH_OFFSET, M0 );
	Local2Global( _V( 5.334, 0.0, 18.5547 ) + LAUNCHMOUNT_MESH_OFFSET, M1 );
	Local2Global( _V( -5.334, 0.0, 18.5547 ) + LAUNCHMOUNT_MESH_OFFSET, M2 );
	Local2Global( _V( -5.334, 0.0, 6.8199 ) + LAUNCHMOUNT_MESH_OFFSET, M3 );

	Local2Global( _V( 11.0744, 0.0, -12.192 ) + LAUNCHMOUNT_MESH_OFFSET, L0 );
	Local2Global( _V( 11.0744, 0.0, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, L1 );
	Local2Global( _V( 3.3147, 0.0, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, L2 );
	Local2Global( _V( 3.3147, 0.0, -12.192 ) + LAUNCHMOUNT_MESH_OFFSET, L3 );

	Local2Global( _V( -11.0744, 0.0, -12.192 ) + LAUNCHMOUNT_MESH_OFFSET, R0 );
	Local2Global( _V( -11.0744, 0.0, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, R1 );
	Local2Global( _V( -3.3147, 0.0, 3.048 ) + LAUNCHMOUNT_MESH_OFFSET, R2 );
	Local2Global( _V( -3.3147, 0.0, -12.192 ) + LAUNCHMOUNT_MESH_OFFSET, R3 );

	double fPowerM = CalculateThrustPower( this, M0, M1, M2, M3 );
	double fPowerL = CalculateThrustPower( this, L0, L1, L2, L3 );
	double fPowerR = CalculateThrustPower( this, R0, R1, R2, R3 );

	double delay = 5E9;// factor controls delay
	if(fPowerM > delay) fSSMESteamLevel = min( 1.0, (fPowerM - delay) / (1.79E10 - delay) );
	else fSSMESteamLevel = 0.0;

	if ((fPowerL + fPowerR) > 0.0) fSRBSteamLevel = min( 1.0, (fPowerL + fPowerR) / 5.92E10 );
	else fSRBSteamLevel = 0.0;

	return;
}

void SLC6::DefineGOXVents( void )
{
	static PARTICLESTREAMSPEC gox_stream = {
		0, 0.3, 140, 5, 0, 0.8, 1.6, 1.35, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-50, 1
		};
	gox_stream.tex = oapiRegisterParticleTexture ("SSV\\GOX_stream");

	AddParticleStream( &gox_stream, GOXVENT_LEFT, GOXVENT_DIRREF, &GOXVentLevel );
	AddParticleStream( &gox_stream, GOXVENT_RIGHT, GOXVENT_DIRREF, &GOXVentLevel );
	return;
}

void SLC6::DefineAnimations()
{
	static UINT AccessArmGrp[1] = {GRP_OAA_AT};
	MGROUP_TRANSLATE* pAccessArm = DefineTranslation( tower_mesh_idx, AccessArmGrp, 1, OAA_DIR * OAA_MOVE_DIST );
	anim_OAA = CreateAnimation(0.0);
	AddAnimationComponent(anim_OAA, 0.0, 1.0, pAccessArm);

	static UINT VentArmGrp[11] = {GRP_GVA_STRUCTURE_AT, GRP_GVA_FENCES_AT, GRP_GVA_GRATING_AT, GRP_GVA_GN2_PURGE_LINE_AT, GRP_GVA_GN2_PURGE_LINE_FLEX_1_AT, GRP_GVA_GN2_PURGE_LINE_FLEX_AT, GRP_GOX_VENT_PIPES_AT, GRP_GOX_VENT_CYLINDER_NORTH_1_AT, GRP_GOX_VENT_CYLINDER_NORTH_2_AT, GRP_GOX_VENT_CYLINDER_SOUTH_1_AT, GRP_GOX_VENT_CYLINDER_SOUTH_2_AT};
	MGROUP_ROTATE* pVentArm = DefineRotation( tower_mesh_idx, VentArmGrp, 11, GVA_POS, GVA_DIR, static_cast<float>(GVA_ANGLE) );
	anim_GVA = CreateAnimation( (-GVA_ANGLE_MIN) / GVA_ANGLE );
	ANIMATIONCOMPONENT_HANDLE parent = AddAnimationComponent( anim_GVA, 0.0, 1.0, pVentArm );

	static UINT VentHoodGrp[5] = {GRP_GOX_VENT_HOOD_AT, GRP_GOX_VENT_CYLINDER_FIXED_AT, GRP_GVA_GN2_PURGE_LINE_FLEX_2_AT, GRP_NORTH_GOX_DOCKSEAL_AT, GRP_SOUTH_GOX_DOCKSEAL_AT};
	MGROUP_ROTATE* pVentHood = DefineRotation( tower_mesh_idx, VentHoodGrp, 5, _V( 0.0, 63.0705, 18.4838 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(48.0 * RAD) );
	anim_GOXVentHood = CreateAnimation( 1.0 );
	AddAnimationComponent( anim_GOXVentHood, 0.0, 1.0, pVentHood, parent );

	// rotate IAA structure out of way when MST is extended
	// in theory, the IAA and GH2 ventline animations should be children of this animation component; for the moment, we just prevent the MST from moving when the IAA is deployed or the GH2 ventline is attached
	static UINT EAAGrp[5] = {GRP_EAA_AT, GRP_GH2_AFT_VENT_FLEX_HOSE_AT, GRP_GH2_AFT_VENT_HARD_LINE_AT, GRP_ETVAS_HAUNCH_AT, GRP_ETVAS_HAUNCH_BLAST_SHIELD_AT};
	MGROUP_ROTATE* pEAA = DefineRotation( tower_mesh_idx, EAAGrp, 5, _V( 28.2702, 0.0, -7.92167 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(90.0 * RAD) );
	anim_EAA = CreateAnimation( 1.0 );
	parent = AddAnimationComponent( anim_EAA, 0.0, 1.0, pEAA );

	static UINT ETVASLineGrp[3] = {GRP_GH2_FWD_VENT_FLEX_LINE_AT, GRP_GH2_VENT_HARD_LINE_AT, GRP_GUCP_AT};
	MGROUP_ROTATE* pETVASLine = DefineRotation( tower_mesh_idx, ETVASLineGrp, 3, _V( 11.8301, 46.5647, -6.82942 ), _V( -0.5, 0.0, -0.866025 ), static_cast<float>(90.0 * RAD) );
	anim_ETVAS = CreateAnimation( 1.0 );
	AddAnimationComponent( anim_ETVAS, 0.0, 1.0, pETVASLine, parent );

	static UINT IAAGrp[2] = {GRP_INTERTANK_ACCESS_ARM_AT, GRP_IAA_EXTENSIBLE_PLATFORM_AT};
	MGROUP_ROTATE* pIAA = DefineRotation( tower_mesh_idx, IAAGrp, 2, _V( 15.6766, 0, -10.7696 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(210.0 * RAD) );
	anim_IAA = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_IAA, 0.0, 1.0, pIAA, parent );

	static UINT SDWWGrp[2] = {GRP_SSME_DUCT_WEST_WALL_SLC6_PAD};
	MGROUP_ROTATE* pSDWW = DefineRotation( launchmount_mesh_idx, SDWWGrp, 1, _V( 0.0, -0.26205, 18.7938 ), _V( -1.0, 0.0, 0.0 ), static_cast<float>(71.780178 * RAD) );
	anim_SSMEDuctWestWall = CreateAnimation( 1.0 );
	AddAnimationComponent( anim_SSMEDuctWestWall, 0.0, 1.0, pSDWW );
	SetAnimation( anim_SSMEDuctWestWall, SSMEDuctWestWall_State.pos );

	// T0 umbilical animation detais
	// 1.181sec total time
	// 0.147sec delay between PIC fire and plate motion
	// plate stop and door motion at 0.669sec
	static UINT LeftT0UmbGrp[1] = {GRP_LH2_TSM_UMBILICALS_SLC6_PAD};
	MGROUP_ROTATE* pLeftT0Umb = DefineRotation(launchmount_mesh_idx, LeftT0UmbGrp, 1, _V( 5.333994, 9.20036, 7.308244 ), _V( -0.0436194, 0.0, 0.999048 ), (float)(26.0*RAD));
	static UINT RightT0UmbGrp[1] = {GRP_LOX_TSM_UMBILICALS_SLC6_PAD};
	MGROUP_ROTATE* pRightT0Umb = DefineRotation(launchmount_mesh_idx, RightT0UmbGrp, 1, _V( -5.333994, 9.20036, 7.308244 ), _V( -0.0436194, 0.0, -0.999048 ), (float)(26.0*RAD));
	static UINT LeftT0UmbCoverGrp[1] = {GRP_LH2_TSM_BONNET_SLC6_PAD};
	MGROUP_ROTATE* pLeftT0UmbCover = DefineRotation(launchmount_mesh_idx, LeftT0UmbCoverGrp, 1, _V( 6.05635, 16.3897, 8.14729 ), _V( -0.0436194, 0.0, -0.999048 ), (float)(90.0*RAD));
	static UINT RightT0UmbCoverGrp[1] = {GRP_LOX_TSM_BONNET_SLC6_PAD};
	MGROUP_ROTATE* pRightT0UmbCover = DefineRotation(launchmount_mesh_idx, RightT0UmbCoverGrp, 1, _V( -6.05635, 16.3897, 8.14729 ), _V( -0.0436194, 0.0, 0.999048 ), (float)(90.0*RAD));
	anim_T0Umb = CreateAnimation(0.0);
	AddAnimationComponent(anim_T0Umb, 0.434, 0.876, pLeftT0Umb);
	AddAnimationComponent(anim_T0Umb, 0.434, 0.876, pRightT0Umb);
	AddAnimationComponent(anim_T0Umb, 0.0, 0.434, pLeftT0UmbCover);
	AddAnimationComponent(anim_T0Umb, 0.0, 0.434, pRightT0UmbCover);

	static UINT PCRGrp[9] = {
		GRP_BOX01_PCR,
		GRP_BOX04_PCR,
		GRP_PCR_SIDE_SEAL_PCR,
		GRP_BOX05_PCR,
		GRP_ACCESS_PLATFORMS_PCR,
		GRP_TOP_STRUCTURE_PCR,
		GRP_PCR_PCR,
		GRP_BOTTOM_STRUCTURE_PCR,
		GRP_DRIVE_PCR
		};
	MGROUP_TRANSLATE* pPCR = DefineTranslation( pcr_mesh_idx, PCRGrp, 9, _V( 0.0, 0.0, -PCR_MOVE_DIST ) );
	anim_PCR = CreateAnimation( 0.0 );
	ANIMATIONCOMPONENT_HANDLE PCRparent = AddAnimationComponent( anim_PCR, 0.0, 1.0, pPCR );
	// track PCR
	MGROUP_TRANSFORM* pPCRref = DefineTransform( pcrref, 6 );
	AddAnimationComponent( anim_PCR, 0, 1, pPCRref, PCRparent );

	MGROUP_TRANSLATE* pSAB = DefineTranslation( sab_mesh_idx, NULL, 0, _V( 0.0, 0.0, -SAB_MOVE_DIST ) );
	anim_SAB = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_SAB, 0.0, 1.0, pSAB );

	MGROUP_TRANSLATE* pMST = DefineTranslation( mst_mesh_idx, NULL, 0, _V( 0.0, 0.0, MST_MOVE_DIST ) );
	anim_MST = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_MST, 0.0, 1.0, pMST );

	static UINT SABDoorGrp[7] = {GRP_DOOR_PANEL7_SAB, GRP_DOOR_PANEL6_SAB, GRP_DOOR_PANEL5_SAB, GRP_DOOR_PANEL4_SAB, GRP_DOOR_PANEL3_SAB, GRP_DOOR_PANEL2_SAB, GRP_DOOR_PANEL1_SAB};
	MGROUP_TRANSLATE* pSABDoor[7];
	anim_SABDoor = CreateAnimation( 0.0 );
	double start = 0.0;
	for (int i = 0; i < 7; i++)
	{
		pSABDoor[i] = DefineTranslation( sab_mesh_idx, &SABDoorGrp[i], 1, _V( 0.0, (7 - i) * 8.139, 0.0 ) );
		AddAnimationComponent( anim_SABDoor, start, 1.0, pSABDoor[i] );
		start += 1.0 / 7.0;
	}

	// port PCR door
	static UINT PCR_Door_1PGrp[1] = {GRP_PCR_PORT_DOOR_1_PCR};
	MGROUP_ROTATE* PCR_Door_1P = DefineRotation( pcr_mesh_idx, PCR_Door_1PGrp, 1, PCR_DOOR_1_PORT_POS, PCR_DOOR_DIR, PCR_DOOR_1_ROT );
	static UINT PCR_Door_2PGrp[1] = {GRP_PCR_PORT_DOOR_2_PCR};
	MGROUP_ROTATE* PCR_Door_2P = DefineRotation( pcr_mesh_idx, PCR_Door_2PGrp, 1, PCR_DOOR_2_PORT_POS, PCR_DOOR_DIR, PCR_DOOR_2_ROT );
	anim_PCR_Door_P = CreateAnimation( 0.0 );
	parent = AddAnimationComponent( anim_PCR_Door_P, 0.0, 1.0, PCR_Door_2P, PCRparent );
	AddAnimationComponent( anim_PCR_Door_P, 0.0, 1.0, PCR_Door_1P, parent );
	PCR_Door_P_State.Set( AnimState::CLOSED, 0.0 );

	// starboard PCR door
	static UINT PCR_Door_1SGrp[1] = {GRP_PCR_STBD_DOOR_1_PCR};
	MGROUP_ROTATE* PCR_Door_1S = DefineRotation( pcr_mesh_idx, PCR_Door_1SGrp, 1, PCR_DOOR_1_STBD_POS, PCR_DOOR_DIR, -PCR_DOOR_1_ROT );
	static UINT PCR_Door_2SGrp[1] = {GRP_PCR_STBD_DOOR_2_PCR};
	MGROUP_ROTATE* PCR_Door_2S = DefineRotation( pcr_mesh_idx, PCR_Door_2SGrp, 1, PCR_DOOR_2_STBD_POS, PCR_DOOR_DIR, -PCR_DOOR_2_ROT );
	anim_PCR_Door_S = CreateAnimation( 0.0 );
	parent = AddAnimationComponent( anim_PCR_Door_S, 0.0, 1.0, PCR_Door_2S, PCRparent );
	AddAnimationComponent( anim_PCR_Door_S, 0.0, 1.0, PCR_Door_1S, parent );
	PCR_Door_S_State.Set( AnimState::CLOSED, 0.0 );
	return;
}

//global functions
DLLCLBK void InitModule(HINSTANCE hDLL)
{
	try
	{
		hModule=hDLL;
		oapiRegisterCustomControls(hDLL);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in InitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in InitModule" );
		abort();
	}
}

DLLCLBK void ExitModule(HINSTANCE hDLL)
{
	try
	{
		oapiUnregisterCustomControls(hDLL);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in ExitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in ExitModule" );
		abort();
	}
}

DLLCLBK VESSEL* ovcInit(OBJHANDLE vessel, int flightmodel )
{
	try
	{
		return new SLC6(vessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	try
	{
		if (vessel) delete static_cast<SLC6*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}

BOOL CALLBACK SLC6_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	try
	{
		if(uMsg==WM_COMMAND) {
			SLC6* pad=static_cast<SLC6*>(oapiGetDialogContext(hWnd));
			switch(LOWORD(wParam)) {
				case IDCANCEL:
					oapiCloseDialog(hWnd);
					return TRUE;
				case IDC_OAA_DEPLOY:
					pad->ExtendOAA( OAA_RATE_NORMAL );
					return TRUE;
				case IDC_OAA_HALT:
					pad->HaltOAA();
					return TRUE;
				case IDC_OAA_RETRACT:
					pad->RetractOAA();
					return TRUE;
				case IDC_GVA_EXTEND:
					pad->ExtendGVA();
					return TRUE;
				case IDC_GVA_HALT:
					pad->HaltGVA();
					return TRUE;
				case IDC_GVA_RETRACT:
					pad->RetractGVA();
					return TRUE;
				case IDC_HOOD_LOWER:
					pad->LowerGOXVentHood();
					return TRUE;
				case IDC_HOOD_HALT:
					pad->HaltGOXVentHood();
					return TRUE;
				case IDC_HOOD_RAISE:
					pad->RaiseGOXVentHood();
					return TRUE;
				case IDC_GH2_DETACH:
					pad->DetachETVAS();
					return TRUE;
				case IDC_GH2_ATTACH:
					pad->AttachETVAS();
					return TRUE;
				case IDC_IAA_DEPLOY:
					pad->DeployIAA();
					return TRUE;
				case IDC_IAA_HALT:
					pad->HaltIAA();
					return TRUE;
				case IDC_IAA_RETRACT:
					pad->RetractIAA();
					return TRUE;
				case IDC_PCR_EXTEND:
					pad->ExtendPCR();
					return TRUE;
				case IDC_PCR_HALT:
					pad->HaltPCR();
					return TRUE;
				case IDC_PCR_RETRACT:
					pad->RetractPCR();
					return TRUE;
				case IDC_SAB_EXTEND:
					pad->ExtendSAB();
					return TRUE;
				case IDC_SAB_HALT:
					pad->HaltSAB();
					return TRUE;
				case IDC_SAB_RETRACT:
					pad->RetractSAB();
					return TRUE;
				case IDC_SAB_DOOR_OPEN:
					pad->OpenSABDoor();
					return TRUE;
				case IDC_SAB_DOOR_HALT:
					pad->HaltSABDoor();
					return TRUE;
				case IDC_SAB_DOOR_CLOSE:
					pad->CloseSABDoor();
					return TRUE;
				case IDC_MST_EXTEND:
					pad->ExtendMST();
					return TRUE;
				case IDC_MST_HALT:
					pad->HaltMST();
					return TRUE;
				case IDC_MST_RETRACT:
					pad->RetractMST();
					return TRUE;
				case IDC_EAA_DEPLOY:
					pad->DeployEAA();
					return TRUE;
				case IDC_EAA_HALT:
					pad->HaltEAA();
					return TRUE;
				case IDC_EAA_RETRACT:
					pad->RetractEAA();
					return TRUE;
				case IDC_SDWW_LOWER:
					pad->LowerSDWW();
					return TRUE;
				case IDC_SDWW_RAISE:
					pad->RaiseSDWW();
					return TRUE;
			}
		}
		//if message has not been handled in this function, perform default action
		return oapiDefDialogProc(hWnd, uMsg, wParam, lParam);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6_DlgProc: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SLC6) [FATAL ERROR] Exception in SLC6_DlgProc" );
		abort();
	}
}

void SLC6::RetractOrbiterAccessArm( void )
{
	RetractOAA();
	return;
}

void SLC6::ExtendOrbiterAccessArm( bool EmergencyRate )
{
	if (EmergencyRate) ExtendOAA( OAA_RATE_EMERGENCY );
	else ExtendOAA( OAA_RATE_NORMAL );
	return;
}

void SLC6::RetractGOXVentArm( void )
{
	RetractGVAandHood();
	return;
}

void SLC6::ExtendGOXVentArm( void )
{
	ExtendGVAandHood();
	return;
}

void SLC6::ActivatePreLOSSWS( void )
{
	PreLOWaterOn = true;
	return;
}

void SLC6::DeactivatePreLOSSWS( void )
{
	PreLOWaterOn = false;
	return;
}

void SLC6::ActivatePostLOSSWS( void )
{
	PostLOWaterOn = true;
	return;
}

void SLC6::DeactivatePostLOSSWS( void )
{
	PostLOWaterOn = false;
	return;
}

void SLC6::ActivateFirex( unsigned int sys )
{
	switch (sys)
	{
		case 1:
			FirexOn_OrbiterSSMEWaterDelugeSystem = true;
			break;
		case 2:
			FirexOn_LH2LO2T0WaterDelugeSystem = true;
			break;
		case 3:
			FirexOn_OrbiterSkinSpraySystem = true;
			break;
	}
	return;
}

void SLC6::DeactivateFirex( unsigned int sys )
{
	switch (sys)
	{
		case 1:
			FirexOn_OrbiterSSMEWaterDelugeSystem = false;
			break;
		case 2:
			FirexOn_LH2LO2T0WaterDelugeSystem = false;
			break;
		case 3:
			FirexOn_OrbiterSkinSpraySystem = false;
			break;
	}
	return;
}

bool SLC6::GetFirexState( unsigned int sys )
{
	switch (sys)
	{
		case 1:
			return FirexOn_OrbiterSSMEWaterDelugeSystem;
			break;
		case 2:
			return FirexOn_LH2LO2T0WaterDelugeSystem;
			break;
		case 3:
			return FirexOn_OrbiterSkinSpraySystem;
			break;
	}
	return false;
}

void SLC6::FireSSMEH2BurnPICs( void )
{
	HBOIOn = true;
	return;
}

void SLC6::SetGMTLO( double GMTLO )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetGMTLO( GMTLO );
	return;
}

void SLC6::SetGMTLOSetCommandFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetGMTLOSetCommandFlag( val );
	return;
}

void SLC6::SetLPSCountdownHoldFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetLPSCountdownHoldFlag( val );
	return;
}

void SLC6::SetLPSGoForAutoSequenceStartFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetLPSGoForAutoSequenceStartFlag( val );
	return;
}

void SLC6::SetLPSGoForEngineStartFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetLPSGoForEngineStartFlag( val );
	return;
}

void SLC6::SetResumeCountCommandFlag( bool val )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetResumeCountCommandFlag( val );
	return;
}

bool SLC6::GetRSCountdownHoldFlag( void )
{
	if (!IsT0UmbilicalConnected()) return false;
	return pSTS->GetRSCountdownHoldFlag();
}

bool SLC6::GetLaunchSequenceAbortFlag( void )
{
	if (!IsT0UmbilicalConnected()) return false;
	return pSTS->GetLaunchSequenceAbortFlag();
}

void SLC6::PSN4( void )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->PSN4();
	return;
}

double SLC6::GetHydSysPress( int sys )
{
	if (!IsT0UmbilicalConnected()) return 0.0;
	return pSTS->GetHydSysPress( sys );
}

int SLC6::GetHeTankPress( int sys )
{
	if (!IsT0UmbilicalConnected()) return 0;
	return pSTS->GetHeTankPress( sys );
}

int SLC6::GetHeRegPress( int sys )
{
	if (!IsT0UmbilicalConnected()) return 0;
	return pSTS->GetHeRegPress( sys );
}

void SLC6::HeFillTank( int sys, double mass )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->HeFillTank( sys, mass );
	return;
}

void SLC6::SetSSMEActPos( int num, double Ppos, double Ypos )
{
	if (!IsT0UmbilicalConnected()) return;
	pSTS->SetSSMEActPos( num, Ppos, Ypos );
	return;
}

unsigned int SLC6::GetHoldFlags( void )
{
	if (!IsT0UmbilicalConnected()) return 0;
	return pSTS->GetHoldFlags();
}

void SLC6::FireHDPPICs( void )
{
	OBJHANDLE hShuttle = GetAttachmentStatus( ahHDP );
	if (hShuttle)
	{
		VESSELSTATUS2 st;
		st.version = 2;
		st.flag = 0;
		VESSELSTATUS2 st2;
		st2.version = 2;
		st2.flag = 0;
		GetStatusEx( &st2 );

		DetachChild( ahHDP );

		VESSEL* pV = oapiGetVesselInterface( hShuttle );
		pV->GetStatusEx( &st );
		st.rbody = st2.rbody;
		st.rvel = st2.rvel;
		st.status = 0;
		pV->DefSetStateEx( &st );
	}

	DetachETVAS();
	return;
}

void SLC6::FireT0UmbilicalPICs( void )
{
	T0Umbilical_State.action=AnimState::CLOSING;
	return;
}

bool SLC6::IsT0UmbilicalConnected( void ) const
{
	return (T0Umbilical_State.action == AnimState::OPEN);
}

void SLC6::DeployIAA()
{
	// only deploy IAA if EAA deployed
	if (EAA_State.Open()) IAA_State.action=AnimState::OPENING;
}

void SLC6::DeployEAA( void )
{
	if (MST_State.Closed()) EAA_State.action = AnimState::OPENING;
	return;
}

void SLC6::HaltEAA( void )
{
	EAA_State.action = AnimState::STOPPED;
	return;
}

void SLC6::RetractEAA( void )
{
	if (IAA_State.Closed() && ETVAS_State.Closed()) EAA_State.action = AnimState::CLOSING;
	return;
}

void SLC6::LowerSDWW( void )
{
	SSMEDuctWestWall_State.action = AnimState::OPENING;
	return;
}

void SLC6::RaiseSDWW( void )
{
	SSMEDuctWestWall_State.action = AnimState::CLOSING;
	return;
}
