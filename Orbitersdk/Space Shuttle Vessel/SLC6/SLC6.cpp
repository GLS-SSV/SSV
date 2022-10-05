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
2022/10/05   GLS
********************************************/
#define ORBITER_MODULE

#include "SLC6.h"
#include <MathSSV.h>
#include "meshres_AT.h"
#include "meshres_Pad.h"
#include "meshres_SAB.h"
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
const VECTOR3 TOWER_MESH_OFFSET = _V( 22.61, 0.0 + VERT_MESH_OFFSET, 16.05 );
const VECTOR3 PCR_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 236.0 );
const VECTOR3 SAB_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 125.0 );
const VECTOR3 MST_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, -113.5 );
const VECTOR3 PPR_MESH_OFFSET = _V( 0.0, 0.0 + VERT_MESH_OFFSET, 299.8991 );

const VECTOR3 GOXVENT_LEFT = TOWER_MESH_OFFSET + _V( -13.993204, 59.58920, -20.493432 );// East duct
const VECTOR3 GOXVENT_RIGHT = TOWER_MESH_OFFSET + _V( -13.508098, 59.58920, -18.305259 );// West duct
const VECTOR3 GOXVENT_DIRREF = _V( 0.226652, -0.973976, 0.0 );

constexpr double PCR_MOVE_DIST = 218.0;// [m]
constexpr double SAB_MOVE_DIST = 89.2125;// [m]
constexpr double MST_MOVE_DIST = 113.5;// [m]


constexpr double SLC6_OAA_RATE_NORMAL = 0.0222222;// 45 seconds [1/sec]
constexpr double SLC6_OAA_RATE_EMERGENCY = 0.0666667;// 15 seconds [1/sec]

constexpr double SLC6_TSM_UMBILICAL_RETRACT_SPEED = 1.181;// sec
constexpr double SLC6_PCR_TRANSLATE_RATE = 6.096 / (PCR_MOVE_DIST * 60.0);// 20ft/min (6.096m/min) [1/sec]
constexpr double SLC6_SAB_TRANSLATE_RATE = 6.096 / (SAB_MOVE_DIST * 60.0);// 20ft/min (6.096m/min) [1/sec]
constexpr double SLC6_MST_TRANSLATE_RATE = 6.096 / (MST_MOVE_DIST * 60.0);// 20ft/min (6.096m/min) [1/sec]
constexpr double SLC6_SAB_DOOR_RATE = 1/600.0;

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

const VECTOR3 HDP_POS = _V( 0.0, 9.00036, -1.2475 ) + LAUNCHMOUNT_MESH_OFFSET;

constexpr VECTOR3 OAA_DIR = {-0.982301, 0.0, 0.187309};
const double OAA_MOVE_DIST = 20.0;// [m]

constexpr VECTOR3 GVA_POS = {3.28101, 60.859798, -23.1399};
constexpr VECTOR3 GVA_DIR = {0.0, -1.0, 0.0};
const double GVA_ANGLE = (77.25/*out*/ + 5.0/*in*/) * RAD;


SLC6::SLC6(OBJHANDLE hVessel, int flightmodel)
	: BaseSSVPad(hVessel, flightmodel, SLC6_WATERTANK_CAP, SLC6_PRELOWATER_FLOWRATE, SLC6_POSTLOWATER_FLOWRATE)
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

	SoundID = -1;

	sprintf_s( LCCName, sizeof(LCCName), "" );

	pSTS = NULL;
	pLCC = NULL;

	HBOIOn = false;
	HBOILevel = 0.0;
	HBOITime = 35.0;
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

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 1.0, -16.0, 0.0 ), 1e8, 1e2, 5, 5},
			{_V( -1.0, -16.0, 1.0 ), 1e8, 1e2, 5, 5},
			{_V( -1.0, -16.0, -1.0 ), 1e8, 1e2, 5, 5},
			{_V( 0, 50, 0 ), 1e8, 1e2, 5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		CreateStadiumLights(SLC6_LIGHT_POS, SLC6_LIGHT_DIR, SLC6_LIGHT_COUNT, SLC6_LIGHT_RANGE, SLC6_LIGHT_ATT0, SLC6_LIGHT_ATT1, SLC6_LIGHT_ATT2, SLC6_LIGHT_UMBRA, SLC6_LIGHT_PENUMBRA, SLC6_LIGHT_DIFFUSE, SLC6_LIGHT_SPECULAR, SLC6_LIGHT_AMBIENT);
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

		SoundID=ConnectToOrbiterSoundDLL(GetHandle());
		if(SoundID!=-1) {
			SetMyDefaultWaveDirectory(const_cast<char*>(SOUND_DIRECTORY));
			RequestLoadVesselWave(SoundID, RSS_ROTATE_SOUND, const_cast<char*>(RSS_ROTATE_SOUND_FILE), BOTHVIEW_FADED_FAR);
			RequestLoadVesselWave(SoundID, CRYO_HISS, const_cast<char*>(CRYO_HISS_SOUND_FILE), BOTHVIEW_FADED_MEDIUM);
		}
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

		if (MST_State.Moving() && (IAA_State.Closed() && ETVAS_State.Closed())) {// only allow MST to move if IAA is retracted and GH2 ventline is detached
			MST_State.Move(simdt*SLC6_MST_TRANSLATE_RATE);
			SetAnimation(anim_MST, MST_State.pos);
			RSS_Sound_On = true;
		}

		if (RSS_Sound_On) PlayVesselWave( SoundID, RSS_ROTATE_SOUND, LOOP );
		else StopVesselWave( SoundID, RSS_ROTATE_SOUND );

		PlayVesselWave( SoundID, CRYO_HISS, LOOP );

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
			else if (!_strnicmp( line, "PCR", 3 ))
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
	// only extend MST if IAA is retracted, GH2 ventline is detached, OAA is retracted and GVA is retracted
	if (IAA_State.Closed() && ETVAS_State.Closed() && OAA_State.Closed() && GVA_State.Closed())
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
		0, 0.05, 30.0, 18.0, 0.05, 0.25, 5.0, 4.0, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC sss_water_FSS = {
		0, 1.0, 10.0, 9.0, 0.1, 1.5, 0.5, 1.0, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC sss_water_Firex = {
		0, 0.3, 80.0, 10.0, 0.5, 0.4, 1.0, 0.8, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	//// Pre L/O Water ////
	// SSME hole
	for (int i = 0; i < 10; i++)
	{
		double zposTSM = 3.45 + (0.55 * i);// first E nozzle
		double zpos = 8.95 + (0.55 * i);// first E nozzle
		AddParticleStream( &sss_water, _V( 4.8675, 7.9649, zposTSM ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (TSM)
		AddParticleStream( &sss_water, _V( 4.8675, 7.9649, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N
		AddParticleStream( &sss_water, _V( -4.8675, 7.9649, zposTSM ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (TSM)
		AddParticleStream( &sss_water, _V( -4.8675, 7.9649, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S
	}
	for (int i = 0; i < 19; i++)
	{
		double xpos = 4.41 - (0.49 * i);// first N nozzle
		AddParticleStream( &sss_water, _V( xpos, 7.9649, 3.0423 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, 1.0 ), &PreLOWaterLevel );// W
	}

	// SRB primary hole
	for (int i = 0; i < 9; i++)
	{
		double zpos = -2.49 + (i * 0.3);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 9.0749, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (top)
		AddParticleStream( &sss_water, _V( 9.0749, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -9.0749, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (top)
		AddParticleStream( &sss_water, _V( -9.0749, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (bottom)
	}
	for (int i = 0; i < 10; i++)
	{
		double zpos = -2.49 + (i * 0.3);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 3.4689, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (top)
		AddParticleStream( &sss_water, _V( 3.4689, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -3.4689, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (top)
		AddParticleStream( &sss_water, _V( -3.4689, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (bottom)
	}
	for (int i = 0; i < 5; i++)
	{
		double xpos = 5.67 + (i * 0.3);// first S nozzle (LH)
		// LH
		AddParticleStream( &sss_water, _V( xpos, 7.3079, 1.7375 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// W (top)
		AddParticleStream( &sss_water, _V( xpos, 6.8019, 1.7375 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// W (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -xpos, 7.3079, 1.7375 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// W (top)
		AddParticleStream( &sss_water, _V( -xpos, 6.8019, 1.7375 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// W (bottom)
	}

	// SRB secondary hole
	for (int i = 0; i < 14; i++)
	{
		double zpos = -15.52 + (i * 0.56);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 11.9072, 0.9325, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (top)
		AddParticleStream( &sss_water, _V( 11.3595, 0.3698, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (bottom)
		AddParticleStream( &sss_water, _V( 2.5544, 0.8702, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (top)
		AddParticleStream( &sss_water, _V( 3.1092, 0.3423, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -2.5544, 0.8702, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (top)
		AddParticleStream( &sss_water, _V( -3.1092, 0.3423, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N (bottom)
		AddParticleStream( &sss_water, _V( -11.9072, 0.9325, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (top)
		AddParticleStream( &sss_water, _V( -11.3595, 0.3698, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S (bottom)
	}

	// SRB curtain
	for (int i = 0; i < 2; i++)
	{
		double zpos = -5.88 + (i * 0.94);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 3.4689, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (S) (top)
		AddParticleStream( &sss_water, _V( 3.4689, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (S) (middle)
		AddParticleStream( &sss_water, _V( 3.4689, 6.2959, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (S) (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -3.4689, 7.3079, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (N) (top)
		AddParticleStream( &sss_water, _V( -3.4689, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (N) (middle)
		AddParticleStream( &sss_water, _V( -3.4689, 6.2959, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (N) (bottom)
	}
	for (int i = 0; i < 14; i++)
	{
		double ypos = 7.3079 - (i * 0.45);// top nozzle
		// LH
		AddParticleStream( &sss_water, _V( 3.4689, ypos, -6.82 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert
		// RH
		AddParticleStream( &sss_water, _V( -3.4689, ypos, -6.82 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert
	}
	for (int i = 0; i < 3; i++)
	{
		double zpos = -6.5 + (i * 0.73);// first E nozzle
		// LH
		AddParticleStream( &sss_water, _V( 9.0749, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (N) (middle)
		AddParticleStream( &sss_water, _V( 9.0749, 6.2959, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (N) (bottom)
		// RH
		AddParticleStream( &sss_water, _V( -9.0749, 6.8019, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (S) (middle)
		AddParticleStream( &sss_water, _V( -9.0749, 6.2959, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (S) (bottom)
	}
	// LH
	AddParticleStream( &sss_water, _V( 9.0749, 7.3079, -4.3 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (N) (top)
	// RH
	AddParticleStream( &sss_water, _V( -9.0749, 7.3079, -4.3 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// E horiz (S) (top)
	double _xpos = 9.0749;
	for (int i = 0; i < 13; i++)
	{
		double ypos = 6.8579 - (i * 0.45);// second top nozzle
		if (i > 5) _xpos += 0.2;
		// LH
		AddParticleStream( &sss_water, _V( _xpos, ypos, -7.51 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert
		// RH
		AddParticleStream( &sss_water, _V( -_xpos, ypos, -7.51 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert
	}
	// LH
	AddParticleStream( &sss_water, _V( 9.0749, 7.3079, -7.31 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert
	AddParticleStream( &sss_water, _V( 9.0749, 7.3079, -7.71 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// N vert
	// RH
	AddParticleStream( &sss_water, _V( -9.0749, 7.3079, -7.31 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert
	AddParticleStream( &sss_water, _V( -9.0749, 7.3079, -7.71 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, -0.707107, 0.0 ), &PreLOWaterLevel );// S vert

	// pad surface
	for (int i = 0; i < 7; i++)
	{
		double xpos = 3.6 + (i * 1.45);// center-most nozzle (N)
		AddParticleStream( &sss_water, _V( xpos, 1.6469, -18.7 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// E (N)
		AddParticleStream( &sss_water, _V( -xpos, 1.6469, -18.7 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.0, -1.0 ), &PreLOWaterLevel );// E (S)
	}
	AddParticleStream( &sss_water, _V( 14.1, 1.6469, -18.2 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.866025, 0.0, -0.5 ), &PreLOWaterLevel );// NE (N)
	AddParticleStream( &sss_water, _V( 13.5, 1.6469, -18.9 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.5, 0.0, -0.866025 ), &PreLOWaterLevel );// NE (E)
	AddParticleStream( &sss_water, _V( -13.5, 1.6469, -18.9 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.5, 0.0, -0.866025 ), &PreLOWaterLevel );// SE (E)
	AddParticleStream( &sss_water, _V( -14.1, 1.6469, -18.2 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.866025, 0.0, -0.5 ), &PreLOWaterLevel );// SE (S)
	for (int i = 0; i < 7; i++)
	{
		double zpos = -8.12 - (i * 1.45);// first W nozzle
		AddParticleStream( &sss_water, _V( 14.0888, 1.6469, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &PreLOWaterLevel );// N
		AddParticleStream( &sss_water, _V( -14.0888, 1.6469, zpos ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &PreLOWaterLevel );// S
	}

	// Access Tower
	AddParticleStream( &sss_water_FSS, _V( -3.0, 44.0, -25.0 ) + TOWER_MESH_OFFSET, _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA
	AddParticleStream( &sss_water_FSS, _V( -6.0, 44.0, -25.0 ) + TOWER_MESH_OFFSET, _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA
	AddParticleStream( &sss_water_FSS, _V( -9.0, 44.0, -25.0 ) + TOWER_MESH_OFFSET, _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA

	//// Firex ////
	// Orbiter SSME Water Deluge System
	AddParticleStream( &sss_water_Firex, _V( 5.2555, 9.0, 2.4988 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.353553, 0.866025, 0.353553 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, _V( 0.0, 9.0, 2.4988 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.0, 0.866025, 0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole E
	AddParticleStream( &sss_water_Firex, _V( -5.2555, 9.0, 2.4988 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.353553, 0.866025, 0.353553 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SE

	AddParticleStream( &sss_water_Firex, _V( 5.2866, 9.0, 9.8466 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole N
	AddParticleStream( &sss_water_Firex, _V( 5.2866, 9.0, 10.3941 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole N
	AddParticleStream( &sss_water_Firex, _V( 5.2866, 9.0, 11.8151 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, _V( 5.2866, 9.0, 12.2536 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW

	AddParticleStream( &sss_water_Firex, _V( -5.2866, 9.0, 9.8466 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole S
	AddParticleStream( &sss_water_Firex, _V( -5.2866, 9.0, 10.3941 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.5, 0.707107, -0.5 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole S
	AddParticleStream( &sss_water_Firex, _V( -5.2866, 9.0, 11.8151 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SW
	AddParticleStream( &sss_water_Firex, _V( -5.2866, 9.0, 12.2536 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.664463, 0.707107, -0.241845 ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SW

	// LH2/LO2 T-0 Water Deluge System
	AddParticleStream( &sss_water_Firex, _V( 4.47149, 17.549601, 8.1238 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -0.707107, 0.0, -0.707107 ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// LH2
	AddParticleStream( &sss_water_Firex, _V( -4.47149, 17.549601, 8.1238 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 0.707107, 0.0, -0.707107 ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// LO2

	// Orbiter Skin Spray System
	AddParticleStream( &sss_water_Firex, _V( 4.73633, 18.030899, 8.65331 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-1 (N)
	AddParticleStream( &sss_water_Firex, _V( 4.8656, 18.030899, 5.69256 ) + LAUNCHMOUNT_MESH_OFFSET, _V( -1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-1 (S)
	AddParticleStream( &sss_water_Firex, _V( -4.73633, 18.030899, 8.65331 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-2 (N)
	AddParticleStream( &sss_water_Firex, _V( -4.8656, 18.030899, 5.69256 ) + LAUNCHMOUNT_MESH_OFFSET, _V( 1.0, 0.0, 0.0 ), &FirexLevel_OrbiterSkinSpraySystem );// 50-2 (S)
	return;
}

void SLC6::DefineExhaustSteam( void )
{
	static PARTICLESTREAMSPEC sss_steam_SSME = {
		0, 8, 20, 300.0, 0.3, 10, 6, 6, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1.0};
	sss_steam_SSME.tex = oapiRegisterParticleTexture("contrail4");

	static PARTICLESTREAMSPEC sss_steam_SRB = {
		0, 10, 100, 800.0, 0.5, 10, 7, 50, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1.0};
	sss_steam_SRB.tex = oapiRegisterParticleTexture("contrail4");

	AddParticleStream(&sss_steam_SSME, _V( -52.532749, -5.188478, 51.707397 ) + PADSURFACE_MESH_OFFSET, _V(-cos(10.0*RAD), sin(10.0*RAD), 0), &fSSMESteamLevel);
	AddParticleStream(&sss_steam_SRB, _V( -57.832451, -4.913425, -6.01262 ) + PADSURFACE_MESH_OFFSET, _V(-cos(10.0*RAD), sin(10.0*RAD), 0), &fSRBSteamLevel);
	AddParticleStream(&sss_steam_SRB, _V( 59.084301, -5.0355, -7.28567 ) + PADSURFACE_MESH_OFFSET, _V(cos(10.0*RAD), sin(10.0*RAD), 0), &fSRBSteamLevel);
	return;
}

void SLC6::CalculateSteamProduction( double simt, double simdt )
{
	VECTOR3 M0, M1, M2, M3;// MPS Hole
	VECTOR3 L0, L1, L2, L3;// Left SRB Hole
	VECTOR3 R0, R1, R2, R3;// Right SRB Hole

	Local2Global( _V( 4.87, 9.00, 3.04 ) + LAUNCHMOUNT_MESH_OFFSET, M0 );
	Local2Global( _V( 4.87, 9.00, 14.13 ) + LAUNCHMOUNT_MESH_OFFSET, M1 );
	Local2Global( _V( -4.87, 9.00, 14.13 ) + LAUNCHMOUNT_MESH_OFFSET, M2 );
	Local2Global( _V( -4.87, 9.00, 3.04 ) + LAUNCHMOUNT_MESH_OFFSET, M3 );

	Local2Global( _V( 9.07, 0.0, -14.91 ) + LAUNCHMOUNT_MESH_OFFSET, L0 );
	Local2Global( _V( 9.07, 0.0, 1.74 ) + LAUNCHMOUNT_MESH_OFFSET, L1 );
	Local2Global( _V( 3.47, 0.0, 1.74 ) + LAUNCHMOUNT_MESH_OFFSET, L2 );
	Local2Global( _V( 3.47, 0.0, -14.91 ) + LAUNCHMOUNT_MESH_OFFSET, L3 );

	Local2Global( _V( -9.07, 0.0, -14.91 ) + LAUNCHMOUNT_MESH_OFFSET, R0 );
	Local2Global( _V( -9.07, 0.0, 1.74 ) + LAUNCHMOUNT_MESH_OFFSET, R1 );
	Local2Global( _V( -3.47, 0.0, 1.74 ) + LAUNCHMOUNT_MESH_OFFSET, R2 );
	Local2Global( _V( -3.47, 0.0, -14.91 ) + LAUNCHMOUNT_MESH_OFFSET, R3 );

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

	static UINT VentArmGrp[4] = {GRP_GOX_VENT_PIPES_AT, GRP_GVA_SWING_ARM_AT, GRP_NORTH_GOX_VENT_CYLINDER_01_AT, GRP_SOUTH_GOX_VENT_CYLINDER_01_AT};
	MGROUP_ROTATE* pVentArm = DefineRotation(tower_mesh_idx, VentArmGrp, 4, GVA_POS, GVA_DIR, static_cast<float>(GVA_ANGLE) );
	anim_GVA = CreateAnimation( 5.0 / (77.25/*out*/ + 5.0/*in*/) );
	ANIMATIONCOMPONENT_HANDLE parent = AddAnimationComponent(anim_GVA, 0.0, 1.0, pVentArm);

	static UINT VentHoodGrp[5] = {GRP_GOX_VENT_HOOD_AT, GRP_NORTH_GOX_VENT_CYLINDER_02_AT, GRP_NORTH_GOX_VENT_CYLINDER_03_AT,
		GRP_SOUTH_GOX_VENT_CYLINDER_02_AT, GRP_SOUTH_GOX_VENT_CYLINDER_03_AT};
	MGROUP_ROTATE* pVentHood = DefineRotation(tower_mesh_idx, VentHoodGrp, 5, _V(3.327, 62.599, 1.888), _V(1, 0, 0), static_cast<float>(48.0*RAD));
	anim_GOXVentHood = CreateAnimation(1.0);
	AddAnimationComponent(anim_GOXVentHood, 0.0, 1.0, pVentHood, parent);

	static UINT ETVASLineGrp[3] = {GRP_GH2_FWD_VENT_FLEX_LINE_AT, GRP_GH2_VENT_HARD_LINE_AT, GRP_GUCP_AT};
	MGROUP_ROTATE* pETVASLine = DefineRotation(tower_mesh_idx, ETVASLineGrp, 3, _V(-11.928, 45.48, -24.215), _V( -0.5, 0.0, -0.866025 ), static_cast<float>(90.0*RAD));
	anim_ETVAS = CreateAnimation(1.0);
	AddAnimationComponent(anim_ETVAS, 0.0, 1.0, pETVASLine);

	static UINT IAAGrp[1] = {GRP_INTERTANK_ACCESS_ARM_AT};
	MGROUP_ROTATE* pIAA = DefineRotation(tower_mesh_idx, IAAGrp, 1, _V(-7.725, 43.15, -28.065), _V(0, 1, 0), static_cast<float>(210.0*RAD));
	anim_IAA = CreateAnimation(0.0);
	AddAnimationComponent(anim_IAA, 0.0, 1.0, pIAA);

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

	MGROUP_TRANSLATE* pPCR = DefineTranslation(pcr_mesh_idx, NULL, 0, _V(0, 0, -PCR_MOVE_DIST));
	anim_PCR = CreateAnimation(0.0);
	AddAnimationComponent(anim_PCR, 0.0, 1.0, pPCR);

	MGROUP_TRANSLATE* pSAB = DefineTranslation(sab_mesh_idx, NULL, 0, _V(0, 0, -SAB_MOVE_DIST));
	anim_SAB = CreateAnimation(0.0);
	AddAnimationComponent(anim_SAB, 0.0, 1.0, pSAB);

	MGROUP_TRANSLATE* pMST = DefineTranslation(mst_mesh_idx, NULL, 0, _V(0, 0, MST_MOVE_DIST));
	anim_MST = CreateAnimation(0.0);
	AddAnimationComponent(anim_MST, 0.0, 1.0, pMST);
	// rotate IAA structure out of way when MST is extended
	// in theory, the IAA and GH2 ventline animations should be children of this animation component; for the moment, we just prevent the MST from moving when the IAA is deployed or the GH2 ventline is attached
	static UINT IAAStructureGrp[9] = {GRP_IAA_STRUCTURE_AT, GRP_GH2_AFT_VENT_FLEX_HOSE_AT, GRP_GH2_AFT_VENT_HARD_LINE_AT, GRP_GH2_PIVOT_POINT_AT, GRP_GH2_VENT_LINE_HAUNCH_AT, GRP_GH2_FWD_VENT_FLEX_LINE_AT, GRP_GH2_VENT_HARD_LINE_AT, GRP_GUCP_AT, GRP_INTERTANK_ACCESS_ARM_AT};
	MGROUP_ROTATE* pIAAStructure = DefineRotation(tower_mesh_idx, IAAStructureGrp, 9, _V(4.348, 0.0, -25.298), _V(0, 1, 0), static_cast<float>(-90.0*RAD)); // rotation angle is just a guess
	AddAnimationComponent(anim_MST, 0.0, 0.05, pIAAStructure);

	static UINT SABDoorGrp[7] = {GRP_DOOR_PANEL7_SAB, GRP_DOOR_PANEL6_SAB, GRP_DOOR_PANEL5_SAB, GRP_DOOR_PANEL4_SAB, GRP_DOOR_PANEL3_SAB, GRP_DOOR_PANEL2_SAB, GRP_DOOR_PANEL1_SAB};
	MGROUP_TRANSLATE* pSABDoor[7];
	anim_SABDoor = CreateAnimation(0.0);
	double start = 0.0;
	for(int i=0;i<7;i++) {
		pSABDoor[i] = DefineTranslation(sab_mesh_idx, &SABDoorGrp[i], 1, _V(0, (7-i)*8.1386, 0));
		AddAnimationComponent(anim_SABDoor, start, 1.0, pSABDoor[i]);
		start += 1.0/7.0;
	}
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

INT_PTR CALLBACK SLC6_DlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
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
	// only deploy IAA if MST retracted
	if (MST_State.Closed()) IAA_State.action=AnimState::OPENING;
}
