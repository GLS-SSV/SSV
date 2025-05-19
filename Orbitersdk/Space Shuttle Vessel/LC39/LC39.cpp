/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/07   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/04   GLS
2020/08/24   GLS
2021/06/14   GLS
2021/06/16   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/05/07   GLS
2022/07/03   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/29   GLS
2022/12/29   GLS
2023/09/14   GLS
2024/12/30   GLS
2025/03/20   GLS
********************************************/
#define ORBITER_MODULE
#include "LC39.h"
#include "LC39_resource.h"
#include "meshres_FSS.h"
#include "meshres_RSS.h"
#include "meshres_Hardstand.h"
#include "../MLP/MLP.h"
#include "../LCC/LCC.h"
#include "../PadMLPInterface.h"
#include "../PadLCCInterface.h"
#include <DlgCtrl.h>
#include "../SSVSound.h"
#include <UtilsSSV.h>
#include <cJSON.h>


//global dll handle
HINSTANCE hPad_DLL;


//#define DEBUG_DISPLAY_OWP_STRUT_ANIMATION_VALUES

static const char* MESHNAME_FSS="SSV\\LC39\\FSS";
static const char* MESHNAME_RSS="SSV\\LC39\\RSS";
static const char* MESHNAME_HARDSTAND="SSV\\LC39\\LC39A_hardstand";
static const char* MESHNAME_WATERTOWER="SSV\\LC39\\WaterTower";

constexpr double LC39_OAA_RATE_NORMAL = 0.00769231;// 130 seconds [1/sec]
constexpr double LC39_OAA_RATE_EMERGENCY = 0.0666667;// 15 seconds [1/sec]

constexpr double RSS_OWP_RATE = 0.002381;
constexpr double FSS_OWP_RATE = 0.005;
constexpr double RSS_RATE = 0.000325;
constexpr double RBUS_RATE = 0.333333;// < 3sec
constexpr double SRB_SFD_RATE = 0.00333333;// 300sec

//FSS OWP strut animation constants

//Measured from mesh:
//FSS_OWP_BRACKET_LENGTH: 11.8745
//FSS_OWP_STRUT_OFFSET : 17.305
//FSS_OWP_STRUT_LENGTH : 17.9491
//FSS_OWP_STRUT_NULL_ANGLE : 83°

//FSS_OWP_STRUT_NULL_ANGLE : 72.3892° calculated by given lengths
//FSS_OWP_BRACKET_LENGTH   : 11.894 m calculated by animations
//FSS_OWP_STRUT_NULL_ANGLE : 72.4545° calculated by animations

//Rail X-Pos is 7.1742
//FSS_OWP_STRUT_OFFSET : 13.5442 by the new rail position
//FSS_OWP_STRUT_NULL_ANGLE : 84.725° calculated by rail position
//FSS_OWP_STRUT_LENGTH : 16.7456 m
//FSS_OWP_STRUT_NULL_ANGLE : 84.345° calculated by new strut length

constexpr double FSS_OWP_ROTATION_INTERVAL_END = 0.769;

const VECTOR3 FSS_OWP_BRACKET_ROTATION_REF = _V( -5.29429, 0.0, 22.012001 );
const VECTOR3 FSS_OWP_STRUT_ROTATION_REF = _V( 6.47513, 0.0, 22.012001 );

constexpr double FSS_OWP_BRACKET_LENGTH = 11.894;
constexpr double FSS_OWP_STRUT_LENGTH = 17.0456;
constexpr double FSS_OWP_STRUT_OFFSET = 13.5442;
constexpr double FSS_OWP_STRUT_NULL_ANGLE = 84.345; //angle in degrees

const VECTOR3 FSS_POS_GOXVENTL = _V( 5.51954, 78.7643, 18.5347 );// North duct
const VECTOR3 FSS_POS_GOXVENTR = _V( 3.50903, 78.7643, 19.0145 );// South duct
const VECTOR3 FSS_POS_GOXVENTDIR = _V( 0.164334, -0.707398, 0.687446 );

const VECTOR3 FSS_POS_GOXVENTL_NEW = _V( 3.38659, 78.173, 9.22256 );// North duct
const VECTOR3 FSS_POS_GOXVENTR_NEW = _V( 1.20654, 78.173, 9.74288 );// South duct
const VECTOR3 FSS_POS_GOXVENTDIR_NEW = _V( 0.115383, -0.867916, 0.483125 );


constexpr double LC39_WATERTANK_CAP = 350000.0;// gallons (300k tank + pipes)
constexpr double LC39_PRELOWATER_FLOWRATE = 450000.0 / 60.0;// gallons/sec
constexpr double LC39_POSTLOWATER_FLOWRATE = 450000.0 / 60.0;// gallons/sec


constexpr unsigned int WT_STROBE_COUNT = 1;
VECTOR3 WT_STROBE_POS[WT_STROBE_COUNT] = {
	_V( 118.470703, 93.204399, -98.588303 )
};


constexpr unsigned int LC39_LIGHT_COUNT = 5;
const VECTOR3 LC39_LIGHT_POS[LC39_LIGHT_COUNT] = {
	_V( -50.865944, 29.569723, -41.297249 ),// POS of SE light
	_V( 0.289551, 24.772814, -43.31155 ),// POS of E light
	_V( 51.7728, 29.569601, -41.306763 ),// POS of NE light
	_V( 61.5098, 29.569525, 29.849501 ),// POS of NW light
	_V( -65.478455, 29.569626, 23.664337 )// POS of SW light
};

const VECTOR3 LC39_LIGHT_DIR[LC39_LIGHT_COUNT] = {
	_V(0.791015, 0.0193902, 0.61149), // DIR of SE light
	_V(0.0, 0.0, 1.0), // DIR of E light
	_V(-0.477215, 0.0192925, 0.878575), // DIR of NE light
	_V(-0.878479, 0.0193991, -0.477387), // DIR of NW light
	_V(0.956121, 0.0193869, -0.292329) // DIR of SW light
};
const COLOUR4 LC39_LIGHT_DIFFUSE = {0.95f, 1.0f, 0.95f, 1.0f};//{0.95f, 1.0f, 0.95f, 1.0f};
const COLOUR4 LC39_LIGHT_SPECULAR = {0,0,0,0};
const COLOUR4 LC39_LIGHT_AMBIENT = {0.85f, 1.0f, 0.85f, 1.0f};
constexpr double LC39_LIGHT_RANGE = 100.0;
constexpr double LC39_LIGHT_ATT0 = 1e-3;
constexpr double LC39_LIGHT_ATT1 = 0;
constexpr double LC39_LIGHT_ATT2 = 0.0005;
const double LC39_LIGHT_UMBRA = 45.0*RAD;
const double LC39_LIGHT_PENUMBRA = 180.0*RAD;



const VECTOR3 PCR_DOOR_DIR = _V( 0.0, 1.0, 0.0 );

const float PCR_DOOR_1_ROT = static_cast<float>(-30.0 * RAD);
const VECTOR3 PCR_DOOR_1_PORT_POS = _V( -11.487368, 0.0, 3.831917 );
const VECTOR3 PCR_DOOR_1_STBD_POS = _V( -11.487368, 0.0, -3.831917 );

const float PCR_DOOR_2_ROT = static_cast<float>(105.0 * RAD);
const VECTOR3 PCR_DOOR_2_PORT_POS = _V( -9.68124, 0.0, 4.541426 );
const VECTOR3 PCR_DOOR_2_STBD_POS = _V( -9.68124, 0.0, -4.541426 );


const COLOUR4 PCR_LIGHT_DIFFUSE = {1.0f, 1.0f, 1.0f, 1.0f};
const COLOUR4 PCR_LIGHT_SPECULAR = {0.0f, 0.0f, 0.0f, 0.0f};
const COLOUR4 PCR_LIGHT_AMBIENT = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr double PCR_LIGHT_RANGE = 15.0;
constexpr double PCR_LIGHT_ATT0 = 1.0;
constexpr double PCR_LIGHT_ATT1 = 0.1;
constexpr double PCR_LIGHT_ATT2 = 0.01;
const double PCR_LIGHT_UMBRA = 45.0 * RAD;
const double PCR_LIGHT_PENUMBRA = 100.0 * RAD;


//global functions
DLLCLBK void InitModule(HINSTANCE hDLL)
{
	try
	{
		hPad_DLL=hDLL;
		oapiRegisterCustomControls(hDLL);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in InitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in InitModule" );
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
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in ExitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in ExitModule" );
		abort();
	}
}

DLLCLBK VESSEL* ovcInit(OBJHANDLE vessel, int flightmodel)
{
	try
	{
		return new LC39(vessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	try
	{
		if (vessel) delete static_cast<LC39*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}

void DisableRBUSbuttons( HWND hWnd )
{
	EnableWindow( GetDlgItem(hWnd, IDC_RBUS_EXTEND), FALSE );
	EnableWindow( GetDlgItem(hWnd, IDC_RBUS_RETRACT), FALSE );
	return;
}

void DisableOWPbuttons( HWND hWnd )
{
	EnableWindow( GetDlgItem(hWnd, IDC_RSSOWP_OPEN), FALSE );
	EnableWindow( GetDlgItem(hWnd, IDC_RSSOWP_CLOSE), FALSE );
	EnableWindow( GetDlgItem(hWnd, IDC_FSSOWP_OPEN), FALSE );
	EnableWindow( GetDlgItem(hWnd, IDC_FSSOWP_CLOSE), FALSE );
	return;
}

BOOL CALLBACK LC39_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	try
	{
		if(uMsg==WM_COMMAND) {
			LC39* pad=static_cast<LC39*>(oapiGetDialogContext(hWnd));
			switch(LOWORD(wParam)) {
				case IDCANCEL:
					oapiCloseDialog(hWnd);
					return TRUE;
				case IDC_RSS_OPEN:
					pad->MoveRSS(AnimState::OPENING);
					return TRUE;
				case IDC_RSS_STOP:
					pad->MoveRSS(AnimState::STOPPED);
					return TRUE;
				case IDC_RSS_CLOSE:
					pad->MoveRSS(AnimState::CLOSING);
					return TRUE;
				case IDC_FSSOWP_OPEN:
					pad->MoveFSS_OWP(AnimState::OPENING);
					return TRUE;
				case IDC_FSSOWP_CLOSE:
					pad->MoveFSS_OWP(AnimState::CLOSING);
					return TRUE;
				case IDC_RSSOWP_OPEN:
					pad->MoveRSS_OWP(AnimState::OPENING);
					return TRUE;
				case IDC_RSSOWP_CLOSE:
					pad->MoveRSS_OWP(AnimState::CLOSING);
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
				case IDC_CREWARM_EXTEND:
					pad->ExtendOAA( OAA_RATE_NORMAL );
					return TRUE;
				case IDC_CREWARM_RETRACT:
					pad->RetractOAA();
					return TRUE;
				case IDC_CREWARM_STOP:
					pad->HaltOAA();
					return TRUE;
				case IDC_GH2_EXTEND:
					pad->AttachETVAS();
					return TRUE;
				case IDC_GH2_RETRACT:
					pad->DetachETVAS();
					return TRUE;
				case IDC_VHOOD_DEPLOY:
					pad->LowerGOXVentHood();
					return TRUE;
				case IDC_VHOOD_RETRACT:
					pad->RaiseGOXVentHood();
					return TRUE;
				case IDC_VHOOD_HALT:
					pad->HaltGOXVentHood();
					return TRUE;
				case IDC_VARM_EXTEND:
					pad->ExtendGVA();
					return TRUE;
				case IDC_VARM_RETRACT:
					pad->RetractGVA();
					return TRUE;
				case IDC_VARM_HALT:
					pad->HaltGVA();
					return TRUE;
				case IDC_RBUS_EXTEND:
					pad->MoveRBUS(AnimState::OPENING);
					return TRUE;
				case IDC_RBUS_RETRACT:
					pad->MoveRBUS(AnimState::CLOSING);
					return TRUE;
				case IDC_SRBEAST_EXTEND:
					pad->MoveEastSRBSFD( AnimState::OPENING );
					return TRUE;
				case IDC_SRBEAST_RETRACT:
					pad->MoveEastSRBSFD( AnimState::CLOSING );
					return TRUE;
				case IDC_SRBWEST_EXTEND:
					pad->MoveWestSRBSFD( AnimState::OPENING );
					return TRUE;
				case IDC_SRBWEST_RETRACT:
					pad->MoveWestSRBSFD( AnimState::CLOSING );
					return TRUE;
			}
		}
		else if(uMsg==WM_SHOWWINDOW) {
			LC39* pad=static_cast<LC39*>(oapiGetDialogContext(hWnd));
			switch (pad->padtype)
			{
				case pad->_1981:
				case pad->_1982:
				case pad->_1983:
					DisableRBUSbuttons( hWnd );
					DisableOWPbuttons( hWnd );
					break;
				case pad->_1985:
					DisableOWPbuttons( hWnd );
					break;
				case pad->_1986:
					break;
				case pad->_1988:
				case pad->_1995:
				case pad->_2007:
					DisableRBUSbuttons( hWnd );
					break;
			}
			// let Orbiter perform default actions
			return oapiDefDialogProc(hWnd, uMsg, wParam, lParam);
		}

		//if message has not been handled in this function, perform default action
		return oapiDefDialogProc(hWnd, uMsg, wParam, lParam);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39_DlgProc: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in LC39_DlgProc" );
		abort();
	}
}

LC39::LC39(OBJHANDLE hVessel, int flightmodel)
	: BaseSSVPad(hVessel, flightmodel, LC39_WATERTANK_CAP, LC39_PRELOWATER_FLOWRATE, LC39_POSTLOWATER_FLOWRATE),
	padtype(_2007), pXRSound(NULL)
{
	GOXVentLevel = 0.0;

	sprintf_s( LCCName, sizeof(LCCName), "" );

	pMLP = NULL;
	pLCC = NULL;

	pcrref[0] = _V( -16.333664, 54.0, 7.121572 );// POS port top
	pcrref[1] = _V( -16.333664, 47.5, 7.121572 );// POS port center
	pcrref[2] = _V( -16.333664, 41.0, 7.121572 );// POS port aft
	pcrref[3] = _V( -16.333664, 54.0, -7.121572 );// POS starboard top
	pcrref[4] = _V( -16.333664, 47.5, -7.121572 );// POS starboard center
	pcrref[5] = _V( -16.333664, 41.0, -7.121572 );// POS starboard aft
	pcrref[6] = _V( 0.707107, 0.0, -0.707107 ) + pcrref[0];// DIR port top
	pcrref[7] = _V( 0.707107, 0.0, -0.707107 ) + pcrref[1];// DIR port center
	pcrref[8] = _V( 0.707107, 0.0, -0.7071070 ) + pcrref[2];// DIR port aft
	pcrref[9] = _V( 0.707107, 0.0, 0.7071070 ) + pcrref[3];// DIR starboard top
	pcrref[10] = _V( 0.707107, 0.0, 0.7071070 ) + pcrref[4];// DIR starboard center
	pcrref[11] = _V( 0.707107, 0.0, 0.7071070 ) + pcrref[5];// DIR starboard aft
}

LC39::~LC39()
{
}

void LC39::DefineAnimations()
{
	// OAA
	static UINT OrbiterAccessArmGrp[2] = {GRP_ORBITER_ACCESS_ARM_FSS, GRP_WHITE_ROOM_FSS};
	MGROUP_ROTATE* OrbiterAccessArm = DefineRotation( fss_mesh_idx, OrbiterAccessArmGrp, 2, _V( -2.8956, 0.0, 21.6408 ), _V( 0.0, -1.0, 0.0 ), static_cast<float>(70.6 * RAD) );
	OAA_State.Set( AnimState::CLOSED, 0.0 );
	anim_OAA = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_OAA, 0.0, 1.0, OrbiterAccessArm );

	// GOX arm
	GVA_State.Set( AnimState::CLOSED, 0.0 );
	anim_GVA = CreateAnimation( 0.0 );
	static UINT GVAGrp[18] = {GRP_GVA_STRUCTURE_FSS, GRP_GVA_STRUCTURE_REINFORCEMENT_FSS, GRP_GVA_GRATING_FSS, GRP_GVA_FENCES_FSS, GRP_GVA_GN2_PURGE_LINE_FSS, GRP_GVA_GN2_PURGE_LINE_ADDITION_FSS, GRP_GVA_GN2_PURGE_LINE_FLEX_1_FSS, GRP_GOX_VENT_PIPES_FSS, GRP_GOX_VENT_PIPES_NEW_FSS, GRP_GOX_VENT_CYLINDER_NORTH_1_FSS, GRP_GOX_VENT_CYLINDER_NORTH_2_FSS, GRP_GOX_VENT_CYLINDER_SOUTH_1_FSS, GRP_GOX_VENT_CYLINDER_SOUTH_2_FSS, GRP_GOX_VENT_CYLINDER_NORTH_1_NEW_FSS, GRP_GOX_VENT_CYLINDER_NORTH_2_NEW_FSS, GRP_GOX_VENT_CYLINDER_SOUTH_1_NEW_FSS, GRP_GOX_VENT_CYLINDER_SOUTH_2_NEW_FSS, GRP_GVA_GN2_PURGE_LINE_ADDITION_FLEX_FSS};
	MGROUP_ROTATE* GVA = DefineRotation( fss_mesh_idx, GVAGrp, 18, _V( 5.15398, 0.0, 21.4549 ), _V( 0.0, -1.0, 0.0 ), static_cast<float>(73.0 * RAD) );
	ANIMATIONCOMPONENT_HANDLE parent = AddAnimationComponent( anim_GVA, 0.0, 1.0, GVA );

	// GOX hood
	GOXVentHood_State.Set( AnimState::OPEN, 1.0 );
	anim_GOXVentHood = CreateAnimation(1.0);
	static UINT VentHoodGrp[6] = {GRP_GOX_VENT_HOOD_FSS, GRP_NORTH_GOX_DOCKSEAL_FSS, GRP_SOUTH_GOX_DOCKSEAL_FSS, GRP_GOX_VENT_CYLINDER_FIXED_FSS, GRP_GOX_VENT_CYLINDER_FIXED_NEW_FSS, GRP_GVA_GN2_PURGE_LINE_FLEX_2_FSS};
	MGROUP_ROTATE* VentHood = DefineRotation( fss_mesh_idx, VentHoodGrp, 6, _V( -14.8851, 81.3055, 20.2025 ), _V( 0.0, 0.0, 1.0), static_cast<float>(48.0 * RAD) );
	AddAnimationComponent( anim_GOXVentHood, 0.0, 1.0, VentHood, parent );

	// GH2 Vent Arm
	ETVAS_State.Set( AnimState::CLOSED, 0.0 );
	static UINT FSS_GH2_Arm[3] = {GRP_GH2_FWD_VENT_FLEX_LINE_FSS, GRP_GH2_VENT_HARD_LINE_FSS, GRP_GUCP_FSS};
	MGROUP_ROTATE* FSS_GH2_ArmRot = DefineRotation( fss_mesh_idx, FSS_GH2_Arm, 3, _V( 6.829425, 64.799706, 11.83005 ), _V( 0.866025, 0.0, -0.5 ), static_cast<float>(90.0 * RAD) );
	anim_ETVAS = CreateAnimation( 1.0 );
	AddAnimationComponent( anim_ETVAS, 0.0, 1.0, FSS_GH2_ArmRot );

	// IAA rotation
	IAA_State.Set( AnimState::CLOSED, 0.0 );
	static UINT IAAGrp[2] = {GRP_INTERTANK_ACCESS_ARM_FSS, GRP_IAA_EXTENSIBLE_PLATFORM_FSS};
	MGROUP_ROTATE* IAA_Deploy = DefineRotation( fss_mesh_idx, IAAGrp, 2, _V( 10.7696, 0.0, 15.676563 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(210.0 * RAD) );
	anim_IAA = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_IAA, 0.0, 1.0, IAA_Deploy );

	// RSS rotation
	RSS_State.Set( AnimState::CLOSED, 0.0 );
	static UINT RSSGrp[36] = {
		GRP_BOX01_RSS,
		GRP_ELEVATOR_DOOR_RSS,
		GRP_METAL_PANELS_RSS,
		GRP_PCR_RSS,
		GRP_RCS_ROOM_AND_ELEVATOR_RSS,
		GRP_WING_PANELS_RSS,
		GRP_ORBITER_WING_TIP_PROTECTION_WALL_RSS,
		GRP_BOX03_RSS,
		GRP_CANISTER_GUIDES_RSS,
		GRP_PCR_DOOR_HINGE_RSS,
		GRP_PCR_PORT_SIDE_SEAL_PANEL_RSS,
		GRP_PCR_STARBOARD_SIDE_SEAL_PANEL_RSS,
		GRP_PCR_TOP_SEAL_RSS,
		GRP_RCS_ROOM_FLOOR_RSS,
		GRP_RSS_CAB_RSS,
		GRP_RSS_CAB_WINDOWS_RSS,
		GRP_ET_PLATFORMS_RSS,
		GRP_HOIST_EQUIPMENT_ROOM_RSS,
		GRP_LINE02_RSS,
		GRP_OMBUU_RSS,
		GRP_OWP_CURTAIN_WALL_RAILS_RSS,
		GRP_RSS_DRIVE_TRUCK_FWD_RSS,
		GRP_RSS_DRIVE_TRUCK_REAR_RSS,
		GRP_RSS_TUBE_FRAME_RSS,
		GRP_PCR_GIRTS_RSS,
		GRP_RSS_TUBE_FRAME_OWP_RSS,
		GRP_UPPER_CATWALKS_AND_STAIRS_RSS,
		GRP_WEATHER_PROTECTION_ROOF_RSS,
		GRP_AC_DUCT_HARD_RSS,
		GRP_APS_APU_SERVICING_PLATFORMS_RSS,
		GRP_HVAC_DUCTS_RSS,
		GRP_PCR_PORT_SIDE_SEAL_RSS,
		GRP_PCR_STARBOARD_SIDE_SEAL_RSS,
		GRP_RSS_CAB_DOOR_RSS,
		GRP_WEATHER_PROTECTION_ROOF_SEAL_RSS,
		GRP_AC_DUCT_FLEX_RSS
		};
	MGROUP_ROTATE* RSS_Rotation = DefineRotation( rss_mesh_idx, RSSGrp, 36, _V( -13.423902, 0.0, 23.3172 ), _V( 0.0, -1.0, 0.0 ), static_cast<float>(120.0 * RAD) );
	anim_rss = CreateAnimation( 1.0 );
	ANIMATIONCOMPONENT_HANDLE RSSparent = AddAnimationComponent( anim_rss, 0.06, 0.95, RSS_Rotation );

	// RCS room door
	static UINT RCS_DoorGrp[1] = {GRP_RCS_ROOM_DOOR_RSS};
	MGROUP_SCALE* RCS_door1 = DefineScale( rss_mesh_idx, RCS_DoorGrp, 1, _V( 0.0, 66.9391, 0.0 ), _V( 1.0, 0.01, 1.0 ) );
	MGROUP_SCALE* RCS_door2 = DefineScale( rss_mesh_idx, RCS_DoorGrp, 1, _V( 0.0, 66.9391, 0.0 ), _V( 1.0, 100.0, 1.0 ) );
	AddAnimationComponent( anim_rss, 0.0, 0.05, RCS_door1, RSSparent );
	AddAnimationComponent( anim_rss, 0.95, 1.0, RCS_door2 );

	// RCS room flip-ups
	static UINT RCS_FlipUp_Port_Grp[2] = {GRP_RCS_ROOM_FLIPUP_PORT_LADDER_RSS, GRP_RCS_ROOM_FLIPUP_PORT_ADJACENT_RSS};
	MGROUP_ROTATE* RCS_FlipUp_Port = DefineRotation( rss_mesh_idx, RCS_FlipUp_Port_Grp, 2, _V( 0.0, 61.315651, 3.794125 ), _V( -1.0, 0.0, 0.0 ), static_cast<float>(80.0 * RAD) );
	AddAnimationComponent( anim_rss, 0.95, 1.0, RCS_FlipUp_Port, RSSparent );

	static UINT RCS_FlipUp_Stbd_Grp[1] = {GRP_RCS_ROOM_FLIPUP_STARBOARD_RSS};
	MGROUP_ROTATE* RCS_FlipUp_Stbd = DefineRotation( rss_mesh_idx, RCS_FlipUp_Stbd_Grp, 1, _V( 0.0, 61.315651, -2.8194 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(80.0 * RAD) );
	AddAnimationComponent( anim_rss, 0.95, 1.0, RCS_FlipUp_Stbd, RSSparent );

	// track PCR
	MGROUP_TRANSFORM* pPCRref = DefineTransform( pcrref, 12 );
	AddAnimationComponent( anim_rss, 0.0, 1.0, pPCRref, RSSparent );

	// port PCR door
	static UINT PCR_Door_1PGrp[2] = {GRP_PCR_PORT_DOOR_1_RSS, GRP_PCR_PORT_DOOR_MAN_RSS};
	MGROUP_ROTATE* PCR_Door_1P = DefineRotation( rss_mesh_idx, PCR_Door_1PGrp, 2, PCR_DOOR_1_PORT_POS, PCR_DOOR_DIR, PCR_DOOR_1_ROT );
	static UINT PCR_Door_2PGrp[1] = {GRP_PCR_PORT_DOOR_2_RSS};
	MGROUP_ROTATE* PCR_Door_2P = DefineRotation( rss_mesh_idx, PCR_Door_2PGrp, 1, PCR_DOOR_2_PORT_POS, PCR_DOOR_DIR, PCR_DOOR_2_ROT );
	anim_PCR_Door_P = CreateAnimation( 0.0 );
	parent = AddAnimationComponent( anim_PCR_Door_P, 0.0, 1.0, PCR_Door_2P, RSSparent );
	AddAnimationComponent( anim_PCR_Door_P, 0.0, 1.0, PCR_Door_1P, parent );
	PCR_Door_P_State.Set( AnimState::CLOSED, 0.0 );

	// starboard PCR door
	static UINT PCR_Door_1SGrp[2] = {GRP_PCR_STBD_DOOR_1_RSS, GRP_PCR_STBD_DOOR_MAN_RSS};
	MGROUP_ROTATE* PCR_Door_1S = DefineRotation( rss_mesh_idx, PCR_Door_1SGrp, 2, PCR_DOOR_1_STBD_POS, PCR_DOOR_DIR, -PCR_DOOR_1_ROT );
	static UINT PCR_Door_2SGrp[1] = {GRP_PCR_STBD_DOOR_2_RSS};
	MGROUP_ROTATE* PCR_Door_2S = DefineRotation( rss_mesh_idx, PCR_Door_2SGrp, 1, PCR_DOOR_2_STBD_POS, PCR_DOOR_DIR, -PCR_DOOR_2_ROT );
	anim_PCR_Door_S = CreateAnimation( 0.0 );
	parent = AddAnimationComponent( anim_PCR_Door_S, 0.0, 1.0, PCR_Door_2S, RSSparent );
	AddAnimationComponent( anim_PCR_Door_S, 0.0, 1.0, PCR_Door_1S, parent );
	PCR_Door_S_State.Set( AnimState::CLOSED, 0.0 );

	// east SRB side flame deflector
	static UINT East_SRB_SFD_group[2] = {GRP_EAST_SIDE_FLAME_DEFLECTOR_HARDSTAND, GRP_EAST_SIDE_FLAME_DEFLECTOR_STRUCTURE_HARDSTAND};
	MGROUP_TRANSLATE* East_SRB_SFD_Translate = DefineTranslation( hs_mesh_idx, East_SRB_SFD_group, 2, _V( -46.978999, 0, 0 ) );
	anim_East_SRB_SFD = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_East_SRB_SFD, 0, 1, East_SRB_SFD_Translate );
	East_SRB_SFD_State.Set( AnimState::OPEN, 1.0 );
	SetAnimation( anim_East_SRB_SFD, East_SRB_SFD_State.pos );// default to launch position

	// west SRB side flame deflector
	static UINT West_SRB_SFD_group[2] = {GRP_WEST_SIDE_FLAME_DEFLECTOR_HARDSTAND, GRP_WEST_SIDE_FLAME_DEFLECTOR_STRUCTURE_HARDSTAND};
	MGROUP_TRANSLATE* West_SRB_SFD_Translate = DefineTranslation( hs_mesh_idx, West_SRB_SFD_group, 2, _V( -46.978999, 0, 0 ) );
	anim_West_SRB_SFD = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_West_SRB_SFD, 0, 1, West_SRB_SFD_Translate );
	West_SRB_SFD_State.Set( AnimState::OPEN, 1.0 );
	SetAnimation( anim_West_SRB_SFD, West_SRB_SFD_State.pos );// default to launch position

	switch (padtype)
	{
		case _1981:
		case _1982:
		case _1983:
			break;
		case _1985:
			DefineRBUSanimations();
			break;
		case _1986:
			DefineRBUSanimations();
			DefineOWPanimations( RSSparent );
			break;
		case _1988:
		case _1995:
		case _2007:
			DefineOWPanimations( RSSparent );
			break;
	}
}

void LC39::DefineRBUSanimations( void )
{
	RBUS_State.Set( AnimState::CLOSED, 0.0 );
	static UINT RBUS_grp[3] = {GRP_RBUS_UMBILICAL_BEAM_FSS, GRP_RBUS_CARRIER_PLATE_FSS, GRP_RBUS_BEAM_PIPES_FSS};
	MGROUP_TRANSLATE* rbus_translate = DefineTranslation( fss_mesh_idx, RBUS_grp, 3, _V( 0.0, 1.220249, -11.609889 ) );// 6º, 11.67384m
	anim_rbus = CreateAnimation( 1.0 );
	AddAnimationComponent( anim_rbus, 0.0, 1.0, rbus_translate );
	return;
}
void LC39::DefineOWPanimations( ANIMATIONCOMPONENT_HANDLE RSSparent )
{
	// FSS OWP
	FSS_OWP_State.Set( AnimState::CLOSED, 0.0 );
	anim_fss_y_owp = CreateAnimation( 0.0 );
	static UINT FSS_Y_OWPRotGrp[2] = {GRP_OUTER_OWP_CURTAIN_WALL_PANEL_FSS, GRP_OUTER_OWP_CURTAIN_WALL_STRUTS_FSS};
	MGROUP_ROTATE* FSS_Y_OWPRot = DefineRotation( fss_mesh_idx, FSS_Y_OWPRotGrp, 2, FSS_OWP_BRACKET_ROTATION_REF, _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI05) );
	ANIMATIONCOMPONENT_HANDLE parent = AddAnimationComponent( anim_fss_y_owp, 0.0, FSS_OWP_ROTATION_INTERVAL_END, FSS_Y_OWPRot );

	static UINT FSS_Y_OWPTransGrp[2] = {GRP_INNER_OWP_CURTAIN_WALL_STRUCTURE_FSS, GRP_INNER_OWP_CURTAIN_WALL_PANEL_FSS};
	MGROUP_TRANSLATE* FSS_Y_OWPTrans = DefineTranslation( fss_mesh_idx, FSS_Y_OWPTransGrp, 2, _V( 8.0, 0.0, 0.0 ) );
	AddAnimationComponent( anim_fss_y_owp, FSS_OWP_ROTATION_INTERVAL_END, 1.0, FSS_Y_OWPTrans, parent );

	static UINT FSS_Y_OWPStrutGrp[1] = {GRP_NORTH_CURTAIN_WALL_STRUTS_FSS};
	MGROUP_ROTATE* FSS_Y_OWPStrut = DefineRotation( fss_mesh_idx, FSS_Y_OWPStrutGrp, 1, FSS_OWP_STRUT_ROTATION_REF, _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
	anim_fss_y_owp_strut = CreateAnimation( 0.5 );
	AddAnimationComponent( anim_fss_y_owp_strut, 0.0, 1.0, FSS_Y_OWPStrut, parent );

	// RSS OWP
	RSS_OWP_State.Set( AnimState::CLOSED, 0.0 );
	anim_rss_y_owp = CreateAnimation( 0.0 );

	static UINT RSS_Y_LOWPGrp[2] = {GRP_OWP_CURTAIN_WALL_RSS, GRP_SRB_IEA_PLATFORM_RSS};
	MGROUP_TRANSLATE* RSS_Y_LOWP = DefineTranslation( rss_mesh_idx, RSS_Y_LOWPGrp, 2, _V( 0.0, 0.0, 11.8491 ) );
	AddAnimationComponent( anim_rss_y_owp, 0.38, 1.0, RSS_Y_LOWP, RSSparent );

	static UINT RSS_Y_UOWPGrp[2] = {GRP_METAL_PANEL_FLIP_RIGHT_RSS, GRP_METAL_PANEL_FLIP_RIGHT_LOWER_RSS};
	MGROUP_ROTATE* RSS_Y_UOWP = DefineRotation( rss_mesh_idx, RSS_Y_UOWPGrp, 2, _V( 0.0, 49.7142, -4.60998 ), _V( -1.0, 0.0, 0.0 ), static_cast<float>(33.0 * RAD) );
	AddAnimationComponent( anim_rss_y_owp, 0, 0.35, RSS_Y_UOWP, RSSparent );

	static UINT RSS_flip_upperGrp[1] = {GRP_METAL_PANEL_FLIP_UPPER_LEFT_RSS};
	MGROUP_ROTATE* RSS_flip_upper = DefineRotation( rss_mesh_idx, RSS_flip_upperGrp, 1, _V( 0.0, 60.942177, 4.50395 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(90.0 * RAD) );
	AddAnimationComponent( anim_rss_y_owp, 0, 0.35, RSS_flip_upper, RSSparent );

	static UINT RSS_flip_lowerGrp[2] = {GRP_METAL_PANEL_FLIP_LOWER_LEFT_RSS, GRP_METAL_PANEL_STRUCTURE_FLIP_LOWER_LEFT_RSS};
	MGROUP_ROTATE* RSS_flip_lower = DefineRotation( rss_mesh_idx, RSS_flip_lowerGrp, 2, _V( -4.6355, 0.0, 6.096 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(117.5 * RAD) );
	AddAnimationComponent( anim_rss_y_owp, 0.05, 0.35, RSS_flip_lower, RSSparent );
	return;
}


void LC39::DefineSSS( void )
{
	static PARTICLESTREAMSPEC sss_water_SSME = {
		0, 0.05, 15.0, 11.0, 0.1, 0.6, 1.5, 0.8, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC sss_water_SRB = {
		0, 0.5, 15.0, 11.0, 0.1, 0.7, 3, 0.8, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC sss_water_Rainbirds = {
		0, 0.5, 25.0, 20.0, 0.1, 0.5, 5.5, 2.5, PARTICLESTREAMSPEC::EMISSIVE,
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
	// water SSME hole (east/west side)
	for (int i = 0; i < 45; i++)
	{
		// water SSME hole (east/west side)
		AddParticleStream( &sss_water_SSME, MLPCoord2Pad( _V( 4.6576, 7.658105, -12.1199 - (i * 0.22696) ) ), MLPDir2Pad( _V( -0.7071, -0.7071, 0 ) ), &PreLOWaterLevel );
		AddParticleStream( &sss_water_SSME, MLPCoord2Pad( _V( -4.6576, 7.658105, -11.5 - (i * 0.22696) ) ), MLPDir2Pad( _V( 0.7071, -0.7071, 0 ) ), &PreLOWaterLevel );

		// water SSME hole (north/south side)
		AddParticleStream( &sss_water_SSME, MLPCoord2Pad( _V( -4.6 + (i * 0.207004), 7.658105, -12.1199 ) ), MLPDir2Pad( _V( 0, -0.7071, -0.7071 ) ), &PreLOWaterLevel );
		AddParticleStream( &sss_water_SSME, MLPCoord2Pad( _V( -4.6 + (i * 0.207004), 7.658105, -22.333099 ) ), MLPDir2Pad( _V( 0, -0.7071, 0.7071 ) ), &PreLOWaterLevel );
	}

	// water SSME hole (TSM)
	for (int i = 0; i < 8; i++)
	{
		AddParticleStream( &sss_water_SSME, MLPCoord2Pad( _V( 4.277445, 8.724215, -16.257999 + (i * 0.3) ) ), MLPDir2Pad( _V( -0.7071, -0.7071, 0 ) ), &PreLOWaterLevel );
		AddParticleStream( &sss_water_SSME, MLPCoord2Pad( _V( -4.277445, 8.724215, -16.257999 + (i * 0.3) ) ), MLPDir2Pad( _V( 0.7071, -0.7071, 0 ) ), &PreLOWaterLevel );
	}

	// water LH SRB hole
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( -7.04205, 3.16816, -4.06202 ) ), MLPDir2Pad( _V(  0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// NW
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( -8.38979, 5.19612, -5.29158 ) ), MLPDir2Pad( _V(  0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// W
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( -8.38979, 5.19612, -8.05427 ) ), MLPDir2Pad( _V( 0.40825, -0.81650, 0.40825 ) ), &PreLOWaterLevel );// SW
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( -4.13662, 5.19612, -8.05252 ) ), MLPDir2Pad( _V( -0.40825, -0.81650, 0.40825 ) ), &PreLOWaterLevel );// SE
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( -4.13662, 5.19612, -5.29158 ) ), MLPDir2Pad( _V( -0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// E
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( -5.4844, 3.16816, -4.06202 ) ), MLPDir2Pad( _V( -0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// NE

	// water RH SRB hole
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( 7.04205, 3.16816, -4.06202 ) ), MLPDir2Pad( _V( -0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// NE
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( 8.38979, 5.19612, -5.29158 ) ), MLPDir2Pad( _V( -0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// E
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( 8.38979, 5.19612, -8.05427 ) ), MLPDir2Pad( _V( -0.40825, -0.81650, 0.40825 ) ), &PreLOWaterLevel );// SE
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( 4.13662, 5.19612, -8.05252 ) ), MLPDir2Pad( _V( 0.40825, -0.81650, 0.40825 ) ), &PreLOWaterLevel );// SW
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( 4.13662, 5.19612, -5.29158 ) ), MLPDir2Pad( _V( 0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// W
	AddParticleStream( &sss_water_SRB, MLPCoord2Pad( _V( 5.4844, 3.16816, -4.06202 ) ), MLPDir2Pad( _V( 0.40825, -0.81650, -0.40825 ) ), &PreLOWaterLevel );// NW

	// FSS
	AddParticleStream( &sss_water_FSS, _V( 5.0, 79.0, 22.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// GVA
	AddParticleStream( &sss_water_FSS, _V( 8.0, 63.0, 21.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA
	AddParticleStream( &sss_water_FSS, _V( 8.0, 63.0, 18.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA
	AddParticleStream( &sss_water_FSS, _V( 8.0, 63.0, 15.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// IAA

	if ((padtype == _1985) || (padtype == _1986))
	{
		AddParticleStream( &sss_water_FSS, _V( -7.0, 38.7, 15.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// RBUS
		AddParticleStream( &sss_water_FSS, _V( -7.0, 38.7, 18.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// RBUS
		AddParticleStream( &sss_water_FSS, _V( -7.0, 38.7, 21.0 ), _V( 0.0, -1.0, 0.0 ), &PreLOWaterLevel );// RBUS
	}

	//// Post L/O Water ////
	AddParticleStream( &sss_water_Rainbirds, MLPCoord2Pad( _V( 0.0, 11.235253, 21.0168 ) ), MLPDir2Pad( _V( 0.0, 0.0, -1 ) ), &PostLOWaterLevel );// N
	AddParticleStream( &sss_water_Rainbirds, MLPCoord2Pad( _V( -12.3975, 11.235253, 16.8155 ) ), MLPDir2Pad( _V( 0.7071, 0.0, -0.7071 ) ), &PostLOWaterLevel );// NW
	AddParticleStream( &sss_water_Rainbirds, MLPCoord2Pad( _V( -12.08, 10.9723, 1.19278 ) ), MLPDir2Pad( _V( 0.7071, 0.0, 0.7071 ) ), &PostLOWaterLevel );// SW
	AddParticleStream( &sss_water_Rainbirds, MLPCoord2Pad( _V( 0.0, 10.9723, 1.37882 ) ), MLPDir2Pad( _V( 0.0, 0.0, 1.0 ) ), &PostLOWaterLevel );// S
	AddParticleStream( &sss_water_Rainbirds, MLPCoord2Pad( _V( 11.9428, 10.9723, 1.48673 ) ), MLPDir2Pad( _V( -0.7071, 0.0, 0.7071 ) ), &PostLOWaterLevel );// SE
	AddParticleStream( &sss_water_Rainbirds, MLPCoord2Pad( _V( 12.3975, 11.235253, 16.8155 ) ), MLPDir2Pad( _V( -0.7071, 0.0, -0.7071 ) ), &PostLOWaterLevel );// NE

	//// Firex ////
	// Orbiter SSME Water Deluge System
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -5.392935, 8.993945, -11.32465 ) ), MLPDir2Pad( _V( 0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -3.808005, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( 0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -3.199395, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( 0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -2.788685, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( 0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -2.13084, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( 0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -1.72526, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( 0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NW

	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 5.388175, 8.990525, -11.325649 ) ), MLPDir2Pad( _V( -0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 3.798865, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( -0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 3.190255, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( -0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 2.779545, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( -0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 2.1217, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( -0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 1.71612, 8.53578, -11.89925 ) ), MLPDir2Pad( _V( -0.353553, 0.866025, -0.353553 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole NE

	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -5.04265, 8.48437, -18.4202 ) ), MLPDir2Pad( _V( 0.5, 0.707107, 0.5 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole W
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -5.04265, 8.48437, -19.1133 ) ), MLPDir2Pad( _V( 0.5, 0.707107, 0.5 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole W
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -5.04265, 8.48437, -20.079899 ) ), MLPDir2Pad( _V( 0.664463, 0.707107, 0.241845 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SW
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -5.042645, 8.484369, -20.404049 ) ), MLPDir2Pad( _V( 0.664463, 0.707107, 0.241845 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SW

	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 5.042655, 8.484369, -18.42025 ) ), MLPDir2Pad( _V( -0.5, 0.707107, 0.5 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole E
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 5.042655, 8.484369, -19.11335 ) ), MLPDir2Pad( _V( -0.5, 0.707107, 0.5 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole E
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 5.042655, 8.484369, -20.079899 ) ), MLPDir2Pad( _V( -0.664463, 0.707107, 0.241845 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SE
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 5.042655, 8.48437, -20.404049 ) ), MLPDir2Pad( _V( -0.664463, 0.707107, 0.241845 ) ), &FirexLevel_OrbiterSSMEWaterDelugeSystem );// SSME hole SE

	// LH2/LO2 T-0 Water Deluge System
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -4.45544, 16.237499, -16.369551 ) ), MLPDir2Pad( _V( 0.41245, -0.4623, 0.785 ) ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// LH2
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 4.45544, 16.237499, -16.369551 ) ), MLPDir2Pad( _V( -0.41245, -0.4623, 0.785 ) ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// LO2
	if ((padtype == _1985) || (padtype == _1986))
	{
		AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -6.600522, 17.235416, -16.022934 ) ), MLPDir2Pad( _V( 0.866025, 0.5, 0.0 ) ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// RBUS
		AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -6.600522, 17.235416, -14.130172 ) ), MLPDir2Pad( _V( 0.866025, 0.5, 0.0 ) ), &FirexLevel_LH2LO2T0WaterDelugeSystem );// RBUS
	}

	// Orbiter Skin Spray System
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -4.914545, 17.20015, -13.2889 ) ), MLPDir2Pad( _V( 1.0, 0.0, 0.0 ) ), &FirexLevel_OrbiterSkinSpraySystem );// 50-1 (N)
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( -4.950425, 17.2521, -16.779949 ) ), MLPDir2Pad( _V( 1.0, 0.0, 0.0 ) ), &FirexLevel_OrbiterSkinSpraySystem );// 50-1 (S)
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 4.914545, 17.20015, -13.2889 ) ), MLPDir2Pad( _V( -1.0, 0.0, 0.0 ) ), &FirexLevel_OrbiterSkinSpraySystem );// 50-2 (N)
	AddParticleStream( &sss_water_Firex, MLPCoord2Pad( _V( 4.950425, 17.2521, -16.779949 ) ), MLPDir2Pad( _V( -1.0, 0.0, 0.0 ) ), &FirexLevel_OrbiterSkinSpraySystem );// 50-2 (S)
	return;
}

void LC39::DefineExhaustSteam( void )
{
	static PARTICLESTREAMSPEC sss_steam_SSME = {
		0, 6, 50, 500.0, 0.3, 15, 6, 8, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1.0};
	sss_steam_SSME.tex = oapiRegisterParticleTexture("contrail4");

	static PARTICLESTREAMSPEC sss_steam_SRB = {
		0, 4, 100, 1000, 0.5, 15, 8, 12, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1.0};
	sss_steam_SRB.tex = oapiRegisterParticleTexture( "SSV\\SRB\\SRB_contrail" );

	const VECTOR3 POS_MPS_SMOKE = _V( -16.0, 10.0, 0.0 );
	const VECTOR3 POS_SRB_SMOKE = _V( 8.0, 7.0, 0.0 );

	const VECTOR3 DIR_MPS_SMOKE = _V( -cos( 10.0 * RAD ), sin( 10.0 * RAD ), 0.0 );
	const VECTOR3 DIR_SRB_SMOKE = _V( 1.0, 0.0, 0.0 );

	AddParticleStream( &sss_steam_SSME, POS_MPS_SMOKE, DIR_MPS_SMOKE, &fSSMESteamLevel );
	AddParticleStream( &sss_steam_SRB, POS_SRB_SMOKE, DIR_SRB_SMOKE, &fSRBSteamLevel );
	return;
}

void LC39::CalculateSteamProduction( double simt, double simdt )
{
	VECTOR3 M0, M1, M2, M3;// MPS Hole
	VECTOR3 L0, L1, L2, L3;// Left SRB Hole
	VECTOR3 R0, R1, R2, R3;// Right SRB Hole

	Local2Global( MLPCoord2Pad( _V( -4.6576, 7.80712, -22.333099 ) ), M0 );
	Local2Global( MLPCoord2Pad( _V( 4.6576, 7.80712, -22.333099 ) ), M1 );
	Local2Global( MLPCoord2Pad( _V( 4.6576, 7.80712, -12.1199 ) ), M2 );
	Local2Global( MLPCoord2Pad( _V( -4.6576, 7.80712, -12.1199 ) ), M3 );

	Local2Global( MLPCoord2Pad( _V( -8.91557, 5.0, -9.45772 ) ), L0 );
	Local2Global( MLPCoord2Pad( _V( -3.60953, 5.0, -9.45772 ) ), L1 );
	Local2Global( MLPCoord2Pad( _V( -3.60953, 5.0, 3.31758 ) ), L2 );
	Local2Global( MLPCoord2Pad( _V( -8.91557, 5.0, 3.31758 ) ), L3 );

	Local2Global( MLPCoord2Pad( _V( 8.91557, 5.0, -9.45772 ) ), R0 );
	Local2Global( MLPCoord2Pad( _V( 3.60953, 5.0, -9.45772 ) ), R1 );
	Local2Global( MLPCoord2Pad( _V( 3.60953, 5.0, 3.31758 ) ), R2 );
	Local2Global( MLPCoord2Pad( _V( 8.91557, 5.0, 3.31758 ) ), R3 );

	double fPowerM = CalculateThrustPower( this, M0, M1, M2, M3 );
	double fPowerL = CalculateThrustPower( this, L0, L1, L2, L3 );
	double fPowerR = CalculateThrustPower( this, R0, R1, R2, R3 );

	double delay = 7.5E8;// factor controls delay
	if(fPowerM > delay) fSSMESteamLevel = min( 1.0, (fPowerM - delay) / (1.79E10 - delay) );
	else fSSMESteamLevel = 0.0;

	if ((fPowerL + fPowerR) > 0.0) fSRBSteamLevel = min( 1.0, (fPowerL + fPowerR) / 5.92E10 );
	else fSRBSteamLevel = 0.0;
	return;
}

void LC39::RetractOAA()
{
	if (!RSS_State.Closed()) return;// don't retract OAA if RSS is in mate
	oaa_mode = OAA_RATE_NORMAL;
	OAA_State.action = AnimState::CLOSING;
}

void LC39::MoveFSS_OWP(AnimState::Action action)
{
	if (padtype <= _1985) return;// no OWP before 1986
	if(action==AnimState::OPENING || action==AnimState::CLOSING)
		FSS_OWP_State.action=action;
}

void LC39::MoveRSS_OWP(AnimState::Action action)
{
	if (padtype <= _1985) return;// no OWP before 1986
	if(RSS_State.Open() && (action==AnimState::OPENING || action==AnimState::CLOSING))
		RSS_OWP_State.action=action;
}

void LC39::MoveRSS(AnimState::Action action)
{
	if ((padtype <= _1985) || RSS_OWP_State.Closed())
	{
		if ((action == AnimState::OPENING) && !OAA_State.Open()) return;// only move RSS to mate if OAA is extended
		RSS_State.action = action;
	}
	return;
}

void LC39::MoveRBUS(AnimState::Action action)
{
	if ((padtype != _1985) && (padtype != _1986)) return;// RBUS is only on 1985 and 1986 pads
	if(action == AnimState::CLOSING || action == AnimState::OPENING)
		RBUS_State.action = action;
}

void LC39::MoveEastSRBSFD( AnimState::Action action )
{
	if ((action == AnimState::CLOSING) || (action == AnimState::OPENING)) East_SRB_SFD_State.action = action;
	return;
}

void LC39::MoveWestSRBSFD( AnimState::Action action )
{
	if ((action == AnimState::CLOSING) || (action == AnimState::OPENING)) West_SRB_SFD_State.action = action;
	return;
}

void LC39::AnimateFSSOWPStrut()
{
	double angle = PI05 * (min(FSS_OWP_State.pos, FSS_OWP_ROTATION_INTERVAL_END) / FSS_OWP_ROTATION_INTERVAL_END);
	//calculate horizontal distance between FSS strut attachment (to OWP bracket) and FSS bracket attachment (to FSS)
	double YPos = FSS_OWP_BRACKET_LENGTH*cos(angle);
	//calculate angle between struts and OWP bracket
	double StrutAngle = acos((FSS_OWP_STRUT_OFFSET - YPos) / FSS_OWP_STRUT_LENGTH) + angle;
	double pos = (FSS_OWP_STRUT_NULL_ANGLE - StrutAngle*DEG) / 180.0 + 0.5;
	pos = min(1, max(0, pos)); //make sure pos value is within limits

#ifdef DEBUG_DISPLAY_OWP_STRUT_ANIMATION_VALUES
		sprintf_s(oapiDebugString(), 256, "-Y-OWP: OWP-Pos: %5.1f%% | Angle: %5.1f° | Y-Pos: %5.2f m | StrutAngle: %5.1f° | pos: %5.1f%%",
			FSS_OWP_State.pos * 100.0, angle * DEG, YPos, StrutAngle * DEG, pos*100.0);
#endif// DEBUG_DISPLAY_OWP_STRUT_ANIMATION_VALUES

	SetAnimation(anim_fss_y_owp_strut, pos);
}

void LC39::clbkPostCreation()
{
	try
	{
		// get pointer to PadMLPInterface
		OBJHANDLE hMLP = GetAttachmentStatus( ahMLP );
		if (hMLP != NULL)
		{
			VESSEL* pVessel = oapiGetVesselInterface( hMLP );
			if (pVessel != NULL)
			{
				if (!_strnicmp( pVessel->GetClassName(), "SSV_MLP", 7 ))
				{
					pMLP = static_cast<MLP*>(pVessel);
					oapiWriteLog( "(SSV_LC39) [INFO] Connected to PadMLPInterface" );
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
					oapiWriteLog( "(SSV_LC39) [INFO] Connected to PadLCCInterface" );
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
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkPostCreation" );
		abort();
	}
}

void LC39::clbkPreStep(double simt, double simdt, double mjd)
{
	try
	{
		BaseSSVPad::clbkPreStep(simt, simdt, mjd);

		if (padtype >= _1986)
		{
			if (RSS_OWP_State.Moving()) {
				double dp=simdt*RSS_OWP_RATE;
				RSS_OWP_State.Move(dp);
				SetAnimation(anim_rss_y_owp, RSS_OWP_State.pos);
			}
			if (FSS_OWP_State.Moving()) {
				double dp=simdt*FSS_OWP_RATE;
				FSS_OWP_State.Move(dp);
				SetAnimation(anim_fss_y_owp, FSS_OWP_State.pos);

				if (FSS_OWP_State.pos <= FSS_OWP_ROTATION_INTERVAL_END) AnimateFSSOWPStrut();
			}
		}

		if(RSS_State.Moving()) {
			double dp=simdt*RSS_RATE;
			RSS_State.Move(dp);
			SetAnimation(anim_rss, RSS_State.pos);
			SoundPlay( pXRSound, RSS_ROTATE_SOUND, true );
			VECTOR3 d[6];
			for (int i = 0; i < 6; i++) d[i] = pcrref[i + 6] - pcrref[i];
			UpdatePCRLights( pcrref, d, 6 );
		}
		else SoundStop( pXRSound, RSS_ROTATE_SOUND );

		if (((padtype == _1985) || (padtype == _1986)) && RBUS_State.Moving())
		{
			double dp = simdt * RBUS_RATE;
			RBUS_State.Move( dp );
			SetAnimation( anim_rbus, RBUS_State.pos );
		}

		if (East_SRB_SFD_State.Moving() == true)
		{
			East_SRB_SFD_State.Move( simdt * SRB_SFD_RATE );
			SetAnimation( anim_East_SRB_SFD, East_SRB_SFD_State.pos );
		}
		if (West_SRB_SFD_State.Moving() == true)
		{
			West_SRB_SFD_State.Move( simdt * SRB_SFD_RATE );
			SetAnimation( anim_West_SRB_SFD, West_SRB_SFD_State.pos );
		}

		SoundPlay( pXRSound, CRYO_HISS, true );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkPreStep" );
		abort();
	}
}

void LC39::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );

		SaveState( scn );

		WriteScenario_state( scn, "RSS", RSS_State);
		if (padtype >= _1986)
		{
			WriteScenario_state( scn, "FSS_OWP", FSS_OWP_State );
			WriteScenario_state( scn, "RSS_OWP", RSS_OWP_State );
		}
		if ((padtype == _1985) || (padtype == _1986)) WriteScenario_state( scn, "RBUS", RBUS_State );
		WriteScenario_state( scn, "EAST_SRB_SFD", East_SRB_SFD_State );
		WriteScenario_state( scn, "WEST_SRB_SFD", West_SRB_SFD_State );

		oapiWriteScenario_string( scn, "LCC_NAME", LCCName );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkSaveState" );
		abort();
	}
}

void LC39::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				LoadMissionFile();

				SetConfiguration();
			}
			else if (!_strnicmp( line, "FSS_OWP", 7 ))
			{
				if (padtype >= _1986)
				{
					sscan_state( line + 7, FSS_OWP_State );
					SetAnimation( anim_fss_y_owp, FSS_OWP_State.pos );
					AnimateFSSOWPStrut();
				}
			}
			else if (!_strnicmp( line, "RSS_OWP", 7 ))
			{
				if (padtype >= _1986)
				{
					sscan_state( line + 7, RSS_OWP_State );
					SetAnimation( anim_rss_y_owp, RSS_OWP_State.pos );
				}
			}
			else if (!_strnicmp( line, "RSS", 3 ))
			{
				sscan_state( line + 3, RSS_State );
				SetAnimation( anim_rss, RSS_State.pos );
			}
			else if (((padtype == _1985) || (padtype == _1986)) && !_strnicmp( line, "RBUS", 4 ))
			{
				sscan_state( line + 4, RBUS_State );
				SetAnimation( anim_rbus, RBUS_State.pos );
			}
			else if (!_strnicmp( line, "EAST_SRB_SFD", 12 ))
			{
				sscan_state( line + 12, East_SRB_SFD_State );
				SetAnimation( anim_East_SRB_SFD, East_SRB_SFD_State.pos );
			}
			else if (!_strnicmp( line, "WEST_SRB_SFD", 12 ))
			{
				sscan_state( line + 12, West_SRB_SFD_State );
				SetAnimation( anim_West_SRB_SFD, West_SRB_SFD_State.pos );
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
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkLoadStateEx" );
		abort();
	}
}

int LC39::clbkConsumeBufferedKey(DWORD key, bool down, char *keystate)
{
	try
	{
		if(!down) return 0; //only handle keydown events

		if(KEYMOD_CONTROL(keystate)) {
			switch(key) {
				case OAPI_KEY_SPACE:
					if(oapiOpenDialogEx(hPad_DLL, IDD_ANIMCTRL, LC39_DlgProc, DLG_CAPTIONCLOSE, this))
						oapiWriteLog( "(SSV_LC39) [INFO] Dialog opened" );
					else if(hPad_DLL) sprintf_s(oapiDebugString(), 256, "Error: %d", GetLastError());
					return 1;
				case OAPI_KEY_K:
					if(RSS_State.Closing() || RSS_State.Closed()) RSS_State.action=AnimState::OPENING;
					else RSS_State.action=AnimState::CLOSING;
					return 1;
				case OAPI_KEY_X:
					if (padtype <= _1985) return 0;// OWP only from 1986 pad onwards
					if(RSS_State.Open()) {
						if(RSS_OWP_State.Closing() || RSS_OWP_State.Closed()) RSS_OWP_State.action=AnimState::OPENING;
						else RSS_OWP_State.action=AnimState::CLOSING;
					}
					return 1;
				case OAPI_KEY_Y:
					if (padtype <= _1985) return 0;// OWP only from 1986 pad onwards
					if(FSS_OWP_State.Closing() || FSS_OWP_State.Closed()) FSS_OWP_State.action=AnimState::OPENING;
					else FSS_OWP_State.action=AnimState::CLOSING;
					return 1;
			}
		}

		return BaseSSVPad::clbkConsumeBufferedKey(key, down, keystate);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkConsumeBufferedKey" );
		abort();
	}
}

void LC39::CreateGOXVents( void )
{
	static PARTICLESTREAMSPEC gox_stream = {
		0, 0.3, 140, 5, 0, 0.8, 1.6, 1.35, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-50, 1
		};
	gox_stream.tex = oapiRegisterParticleTexture( "SSV\\GOX_stream" );

	VECTOR3 pos_l = FSS_POS_GOXVENTL_NEW;
	VECTOR3 pos_r = FSS_POS_GOXVENTR_NEW;
	VECTOR3 dir = FSS_POS_GOXVENTDIR_NEW;
	if (padtype == _1981)
	{
		gox_stream.srcsize = 0.15;
		gox_stream.v0 = 10;
		pos_l = FSS_POS_GOXVENTL;
		pos_r = FSS_POS_GOXVENTR;
		dir = FSS_POS_GOXVENTDIR;
	}
	AddParticleStream( &gox_stream, pos_l, dir, &GOXVentLevel );
	AddParticleStream( &gox_stream, pos_r, dir, &GOXVentLevel );
	return;
}

void LC39::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		SetEmptyMass(2.000001);
		SetSize(392.5);

		//add meshes
		FSSMesh=oapiLoadMeshGlobal(MESHNAME_FSS);
		RSSMesh=oapiLoadMeshGlobal(MESHNAME_RSS);
		HardStandMesh=oapiLoadMeshGlobal(MESHNAME_HARDSTAND);
		WaterTowerMesh=oapiLoadMeshGlobal(MESHNAME_WATERTOWER);

		fss_mesh_idx = AddMesh( FSSMesh );
		rss_mesh_idx = AddMesh( RSSMesh );
		hs_mesh_idx = AddMesh( HardStandMesh );
		wt_mesh_idx = AddMesh( WaterTowerMesh );

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 1.0, 0.0, 0.0 ), 1e8, 1e2, 5, 5},
			{_V( -1.0, 0.0, 1.0 ), 1e8, 1e2, 5, 5},
			{_V( -1.0, 0.0, -1.0 ), 1e8, 1e2, 5, 5},
			{_V( 0, 50, 0 ), 1e8, 1e2, 5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		DefineExhaustSteam();

		SetOrbiterAccessArmRate( LC39_OAA_RATE_NORMAL, OAA_RATE_NORMAL );
		SetOrbiterAccessArmRate( LC39_OAA_RATE_EMERGENCY, OAA_RATE_EMERGENCY );

		CreateSmallLights( WT_STROBE_POS, WT_STROBE_COUNT );
		CreateStadiumLights(LC39_LIGHT_POS, LC39_LIGHT_DIR, LC39_LIGHT_COUNT, LC39_LIGHT_RANGE, LC39_LIGHT_ATT0, LC39_LIGHT_ATT1, LC39_LIGHT_ATT2, LC39_LIGHT_UMBRA, LC39_LIGHT_PENUMBRA, LC39_LIGHT_DIFFUSE, LC39_LIGHT_SPECULAR, LC39_LIGHT_AMBIENT);

		VECTOR3 d[6];
		for (int i = 0; i < 6; i++) d[i] = pcrref[i + 6] - pcrref[i];
		CreatePCRLights( pcrref, d, 6, PCR_LIGHT_RANGE, PCR_LIGHT_ATT0, PCR_LIGHT_ATT1, PCR_LIGHT_ATT2, PCR_LIGHT_UMBRA, PCR_LIGHT_PENUMBRA, PCR_LIGHT_DIFFUSE, PCR_LIGHT_SPECULAR, PCR_LIGHT_AMBIENT );

		// mid point between stands
		ahMLP = CreateAttachment( false, _V( 6.705599, 19.5072, 0.0 ), _V( 0.0, -1.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), "XMLP" );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkSetClassCaps" );
		abort();
	}
}

void LC39::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		DEVMESHHANDLE hDevMeshFSS = GetDevMesh( vis, fss_mesh_idx );
		DEVMESHHANDLE hDevMeshRSS = GetDevMesh( vis, rss_mesh_idx );

		switch (padtype)
		{
			case _1981:
				HideCentaurPlatform( hDevMeshFSS );
				HideRBUS( hDevMeshFSS );
				HideOWP( hDevMeshFSS, hDevMeshRSS );
				HideNewLightningMast( hDevMeshFSS );
				HideGVANewVents( hDevMeshFSS );
				HideGVAReinforcement( hDevMeshFSS );
				HideGVAAccessPlatform( hDevMeshFSS );
				RedPaintFSS( hDevMeshFSS );
				break;
			case _1982:
				HideCentaurPlatform( hDevMeshFSS );
				HideRBUS( hDevMeshFSS );
				HideOWP( hDevMeshFSS, hDevMeshRSS );
				HideNewLightningMast( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				HideGVAReinforcement( hDevMeshFSS );
				HideGVAAccessPlatform( hDevMeshFSS );
				RedPaintFSS( hDevMeshFSS );
				break;
			case _1983:
				HideRBUS( hDevMeshFSS );
				HideOWP( hDevMeshFSS, hDevMeshRSS );
				HideNewLightningMast( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				HideGVAReinforcement( hDevMeshFSS );
				HideGVAAccessPlatform( hDevMeshFSS );
				break;
			case _1985:
				HideOWP( hDevMeshFSS, hDevMeshRSS );
				HideNewLightningMast( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				HideGVAReinforcement( hDevMeshFSS );
				HideGVAAccessPlatform( hDevMeshFSS );
				break;
			case _1986:
				HideNewLightningMast( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				HideGVAReinforcement( hDevMeshFSS );
				HideGVAAccessPlatform( hDevMeshFSS );
				break;
			case _1988:
				HideRBUS( hDevMeshFSS );
				HideNewLightningMast( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				HideGVAReinforcement( hDevMeshFSS );
				HideGVAAccessPlatform( hDevMeshFSS );
				break;
			case _1995:
				HideRBUS( hDevMeshFSS );
				HideNewLightningMast( hDevMeshFSS );
				HideCraneTruss( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				break;
			case _2007:
				HideRBUS( hDevMeshFSS );
				HideCraneTruss( hDevMeshFSS );
				HideCraneWeightLightningMast( hDevMeshFSS );
				HideGVAOriginalVents( hDevMeshFSS );
				break;
		}

		VECTOR3 d[6];
		for (int i = 0; i < 6; i++) d[i] = pcrref[i + 6] - pcrref[i];
		UpdatePCRLights( pcrref, d, 6 );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_LC39) [FATAL ERROR] Exception in LC39::clbkVisualCreated" );
		abort();
	}
}

void LC39::HideCentaurPlatform( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiEditMeshGroup( hmesh, GRP_CENTAUR_PLATFORM_FSS, &grpSpec );
	return;
}

void LC39::HideRBUS( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiEditMeshGroup( hmesh, GRP_RBUS_CARRIER_PLATE_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_RBUS_INCLINE_STRUCTURE_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_RBUS_UMBILICAL_BEAM_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_RBUS_BEAM_PIPES_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_RBUS_FIXED_PIPES_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_RBUS_ACCESS_PLATFORM_FSS, &grpSpec );
	return;
}

void LC39::HideOWP( DEVMESHHANDLE hmeshFSS, DEVMESHHANDLE hmeshRSS )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	// FSS
	oapiEditMeshGroup( hmeshFSS, GRP_OUTER_OWP_CURTAIN_WALL_STRUTS_FSS, &grpSpec );
	oapiEditMeshGroup( hmeshFSS, GRP_NORTH_CURTAIN_WALL_STRUTS_FSS, &grpSpec );
	oapiEditMeshGroup( hmeshFSS, GRP_OUTER_OWP_CURTAIN_WALL_PANEL_FSS, &grpSpec );
	oapiEditMeshGroup( hmeshFSS, GRP_INNER_OWP_CURTAIN_WALL_STRUCTURE_FSS, &grpSpec );
	oapiEditMeshGroup( hmeshFSS, GRP_INNER_OWP_CURTAIN_WALL_PANEL_FSS, &grpSpec );
	oapiEditMeshGroup( hmeshFSS, GRP_OWP_SUPPORT_STRUCTURE_FSS, &grpSpec );

	// RSS
	oapiEditMeshGroup( hmeshRSS, GRP_OWP_CURTAIN_WALL_RAILS_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_OWP_CURTAIN_WALL_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_SRB_IEA_PLATFORM_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_METAL_PANEL_FLIP_RIGHT_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_METAL_PANEL_FLIP_RIGHT_LOWER_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_METAL_PANEL_FLIP_UPPER_LEFT_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_METAL_PANEL_FLIP_LOWER_LEFT_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_METAL_PANEL_STRUCTURE_FLIP_LOWER_LEFT_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_RSS_TUBE_FRAME_OWP_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_ORBITER_WING_TIP_PROTECTION_WALL_RSS, &grpSpec );
	oapiEditMeshGroup( hmeshRSS, GRP_LINE02_RSS, &grpSpec );

	oapiEditMeshGroup( hmeshRSS, GRP_BOX01_RSS, &grpSpec );// unknown use, but appeared at about the same time as the OWP
	return;
}

void LC39::HideNewLightningMast( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding new lightning mast" );
	oapiEditMeshGroup( hmesh, GRP_LIGHTNING_MAST_NEW_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_LIGHTNING_MAST_BASE_NEW_FSS, &grpSpec );
	return;
}

void LC39::HideCraneTruss( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding crane truss" );
	oapiEditMeshGroup( hmesh, GRP_HAMMERHEAD_CRANE_TRUSS_FSS, &grpSpec );
	return;
}

void LC39::HideCraneWeightLightningMast( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding crane weight and lightning mast" );
	oapiEditMeshGroup( hmesh, GRP_HAMMERHEAD_CRANE_COUNTERWEIGHT_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_LIGHTNING_MAST_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_LIGHTNING_MAST_BOTTOM_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_LIGHTNING_MAST_BASE_FSS, &grpSpec );
	return;
}

void LC39::HideGVAAccessPlatform( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding GVA access platform" );
	oapiEditMeshGroup( hmesh, GRP_GVA_ACCESS_PLATFORM_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_HINGE_COLUMNS_GVA_PLATFORM_FSS, &grpSpec );
	return;
}

void LC39::HideGVANewVents( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding GVA new vents" );
	oapiEditMeshGroup( hmesh, GRP_GVA_GN2_PURGE_LINE_ADDITION_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GVA_GN2_PURGE_LINE_ADDITION_FLEX_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_PIPES_NEW_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_NORTH_1_NEW_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_NORTH_2_NEW_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_SOUTH_1_NEW_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_SOUTH_2_NEW_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_FIXED_NEW_FSS, &grpSpec );
	return;
}

void LC39::HideGVAOriginalVents( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding GVA original vents" );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_PIPES_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_NORTH_1_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_NORTH_2_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_SOUTH_1_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_SOUTH_2_FSS, &grpSpec );
	oapiEditMeshGroup( hmesh, GRP_GOX_VENT_CYLINDER_FIXED_FSS, &grpSpec );
	return;
}

void LC39::HideGVAReinforcement( DEVMESHHANDLE hmesh )
{
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 0x00000003;// hide group and shadow

	oapiWriteLog( "(SSV_LC39) [INFO] Hiding GVA reinforcement" );
	oapiEditMeshGroup( hmesh, GRP_GVA_STRUCTURE_REINFORCEMENT_FSS, &grpSpec );
	return;
}

void LC39::RedPaintFSS( DEVMESHHANDLE hmesh )
{
	MATERIAL mat;

	oapiWriteLog( "(SSV_LC39) [INFO] Painting FSS red" );
	oapiMeshMaterial( hmesh, MAT_METAL_FSS, &mat );
	mat.diffuse.r = 0.729412f;
	mat.diffuse.g = 0.08627451f;
	mat.diffuse.b = 0.04705882f;

	mat.ambient.r = 0.729412f;
	mat.ambient.g = 0.08627451f;
	mat.ambient.b = 0.04705882f;
	oapiSetMaterial( hmesh, MAT_METAL_FSS, &mat );
	return;
}

void LC39::LoadMissionFile( void )
{
	std::string filename;
	filename = "Missions\\SSV\\" + strMission + ".json";

	FILE* hF = fopen( filename.c_str(), "r" );
	if (hF == NULL)
	{
		oapiWriteLogV( "(SSV_LC39) [ERROR] Can't open mission file %s", strMission.c_str() );
		return;
	}

	oapiWriteLogV( "(SSV_LC39) [INFO] Loading mission file %s", strMission.c_str() );

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
		oapiWriteLog( "(SSV_LC39) [ERROR] Error parsing mission file version" );
		delete[] missionfilestr;
		return;
	}

	cJSON* version = cJSON_GetObjectItemCaseSensitive( root, "Version" );
	switch (version->valueint)
	{
		case 2:// unchanged from V1
			LoadMissionV1( root );
			break;
		default:
			oapiWriteLogV( "(SSV_LC39) [ERROR] Unknown mission file version %d", version->valueint );
			break;
	}

	cJSON_Delete( root );
	delete[] missionfilestr;
	return;
}

void LC39::LoadMissionV1( cJSON* root )
{
	// read Launch Site.KSC
	cJSON* ksc = cJSON_GetObjectItemCaseSensitive( cJSON_GetObjectItemCaseSensitive( root, "Launch Site" ), "KSC" );

	cJSON* tmp = cJSON_GetObjectItemCaseSensitive( ksc, "Pad Type" );
	if (!strcmp( "1981", tmp->valuestring ))
	{
		padtype = _1981;
	}
	else if (!strcmp( "1982", tmp->valuestring ))
	{
		padtype = _1982;
	}
	else if (!strcmp( "1983", tmp->valuestring ))
	{
		padtype = _1983;
	}
	else if (!strcmp( "1985", tmp->valuestring ))
	{
		padtype = _1985;
	}
	else if (!strcmp( "1986", tmp->valuestring ))
	{
		padtype = _1986;
	}
	else if (!strcmp( "1988", tmp->valuestring ))
	{
		padtype = _1988;
	}
	else if (!strcmp( "1995", tmp->valuestring ))
	{
		padtype = _1995;
	}
	else //if (!strcmp( "2007", tmp->valuestring ))
	{
		padtype = _2007;
	}
	return;
}

void LC39::SetConfiguration( void )
{
	DefineAnimations();
	DefineSSS();
	CreateGOXVents();
	return;
}

void LC39::RetractOrbiterAccessArm( void )
{
	RetractOAA();
	return;
}

void LC39::ExtendOrbiterAccessArm( bool EmergencyRate )
{
	if (EmergencyRate) ExtendOAA( OAA_RATE_EMERGENCY );
	else ExtendOAA( OAA_RATE_NORMAL );
	return;
}

void LC39::RetractGOXVentArm( void )
{
	RetractGVAandHood();
	return;
}

void LC39::ExtendGOXVentArm( void )
{
	ExtendGVAandHood();
	return;
}

void LC39::ActivatePreLOSSWS( void )
{
	PreLOWaterOn = true;
	return;
}

void LC39::DeactivatePreLOSSWS( void )
{
	PreLOWaterOn = false;
	return;
}

void LC39::ActivatePostLOSSWS( void )
{
	PostLOWaterOn = true;
	return;
}

void LC39::DeactivatePostLOSSWS( void )
{
	PostLOWaterOn = false;
	return;
}

void LC39::ActivateFirex( unsigned int sys )
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

void LC39::DeactivateFirex( unsigned int sys )
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

bool LC39::GetFirexState( unsigned int sys )
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

void LC39::FireSSMEH2BurnPICs( void )
{
	pMLP->FireSSMEH2BurnPICs();
	return;
}

void LC39::SetGMTLO( double GMTLO )
{
	pMLP->SetGMTLO( GMTLO );
	return;
}

void LC39::SetGMTLOSetCommandFlag( bool val )
{
	pMLP->SetGMTLOSetCommandFlag( val );
	return;
}

void LC39::SetLPSCountdownHoldFlag( bool val )
{
	pMLP->SetLPSCountdownHoldFlag( val );
	return;
}

void LC39::SetLPSGoForAutoSequenceStartFlag( bool val )
{
	pMLP->SetLPSGoForAutoSequenceStartFlag( val );
	return;
}

void LC39::SetLPSGoForEngineStartFlag( bool val )
{
	pMLP->SetLPSGoForEngineStartFlag( val );
	return;
}

void LC39::SetResumeCountCommandFlag( bool val )
{
	pMLP->SetResumeCountCommandFlag( val );
	return;
}

bool LC39::GetRSCountdownHoldFlag( void )
{
	return pMLP->GetRSCountdownHoldFlag();
}

bool LC39::GetLaunchSequenceAbortFlag( void )
{
	return pMLP->GetLaunchSequenceAbortFlag();
}

void LC39::PSN4( void )
{
	pMLP->PSN4();
	return;
}

double LC39::GetHydSysPress( int sys )
{
	return pMLP->GetHydSysPress( sys );
}

int LC39::GetHeTankPress( int sys )
{
	return pMLP->GetHeTankPress( sys );
}

int LC39::GetHeRegPress( int sys )
{
	return pMLP->GetHeRegPress( sys );
}

void LC39::HeFillTank( int sys, double mass )
{
	pMLP->HeFillTank( sys, mass );
	return;
}

void LC39::SetSSMEActPos( int num, double Ppos, double Ypos )
{
	pMLP->SetSSMEActPos( num, Ppos, Ypos );
	return;
}

unsigned int LC39::GetHoldFlags( void )
{
	return pMLP->GetHoldFlags();
}

void LC39::FireETVASPICs( void )
{
	DetachETVAS();
	MoveRBUS( AnimState::CLOSING );
	return;
}

VECTOR3 LC39::MLPCoord2Pad( VECTOR3 v ) const
{
	const VECTOR3 PAD_ATTACH_OFFSET = _V( 6.705599, 19.5072, 0.0 );
	const VECTOR3 MLP_ATTACH_OFFSET = _V( 0.0, 0.0, 0.0 );

	// rotate Y CW 90º
	return PAD_ATTACH_OFFSET + _V( v.z, v.y, -v.x ) - _V( MLP_ATTACH_OFFSET.z, MLP_ATTACH_OFFSET.y, -MLP_ATTACH_OFFSET.x );
}

VECTOR3 LC39::MLPDir2Pad( VECTOR3 v ) const
{
	// rotate Y CW 90º
	return _V( v.z, v.y, -v.x );
}
