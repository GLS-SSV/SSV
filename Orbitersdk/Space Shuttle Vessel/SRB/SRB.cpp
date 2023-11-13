/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/25   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/06/29   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/23   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/09/14   GLS
********************************************/
// ==============================================================
//                 ORBITER MODULE: Atlantis
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2003 Martin Schweiger
//                   All rights reserved
//
// Atlantis_SRB.cpp
// Reference implementation of Atlantis SRB(Space Shuttle - Solid
// Rocket Booster) vessel class module
// Note: Druing launch, the thrusters associated with this vessel
// do not provide any thrust; similar resources are created in
// the Atlantis module. This module takes control of the SRB after
// separation from the Shuttle's main tank.
// ==============================================================

#define ORBITER_MODULE
#include "SRB.h"
#include "../CommonDefs.h"
#include <math.h>
#include <stdio.h>


const static char* MESHNAME_LH_FWD_ASSEMBLY = "SSV\\SRB\\LH_fwd_assembly";
const static char* MESHNAME_RH_FWD_ASSEMBLY = "SSV\\SRB\\RH_fwd_assembly";

const static char* MESHNAME_LH_FWD_SPM = "SSV\\SRB\\LH_fwd_segment_SPM";
const static char* MESHNAME_LH_FWD_CTR_SPM = "SSV\\SRB\\LH_fwd_center_segment_SPM";
const static char* MESHNAME_LH_AFT_CTR_SPM = "SSV\\SRB\\LH_aft_center_segment_SPM";
const static char* MESHNAME_LH_AFT_SPM = "SSV\\SRB\\LH_aft_segment_HPM";// TODO SPM nozzle

const static char* MESHNAME_RH_FWD_SPM = "SSV\\SRB\\RH_fwd_segment_SPM";
const static char* MESHNAME_RH_FWD_CTR_SPM = "SSV\\SRB\\RH_fwd_center_segment_SPM";
const static char* MESHNAME_RH_AFT_CTR_SPM = "SSV\\SRB\\RH_aft_center_segment_SPM";
const static char* MESHNAME_RH_AFT_SPM = "SSV\\SRB\\RH_aft_segment_HPM";// TODO SPM nozzle


const static char* MESHNAME_LH_FWD_HPM = "SSV\\SRB\\LH_fwd_segment_SPM";
const static char* MESHNAME_LH_FWD_CTR_HPM = "SSV\\SRB\\LH_fwd_center_segment_SPM";
const static char* MESHNAME_LH_AFT_CTR_HPM = "SSV\\SRB\\LH_aft_center_segment_SPM";
const static char* MESHNAME_LH_AFT_HPM = "SSV\\SRB\\LH_aft_segment_HPM";

const static char* MESHNAME_RH_FWD_HPM = "SSV\\SRB\\RH_fwd_segment_SPM";
const static char* MESHNAME_RH_FWD_CTR_HPM = "SSV\\SRB\\RH_fwd_center_segment_SPM";
const static char* MESHNAME_RH_AFT_CTR_HPM = "SSV\\SRB\\RH_aft_center_segment_SPM";
const static char* MESHNAME_RH_AFT_HPM = "SSV\\SRB\\RH_aft_segment_HPM";


const static char* MESHNAME_LH_FWD_FWC = "SSV\\SRB\\LH_fwd_segment_FWC";
const static char* MESHNAME_LH_FWD_CTR_FWC = "SSV\\SRB\\LH_fwd_center_segment_FWC";
const static char* MESHNAME_LH_AFT_CTR_FWC = "SSV\\SRB\\LH_aft_center_segment_FWC";
const static char* MESHNAME_LH_AFT_FWC = "SSV\\SRB\\LH_aft_segment_FWC";

const static char* MESHNAME_RH_FWD_FWC = "SSV\\SRB\\RH_fwd_segment_FWC";
const static char* MESHNAME_RH_FWD_CTR_FWC = "SSV\\SRB\\RH_fwd_center_segment_FWC";
const static char* MESHNAME_RH_AFT_CTR_FWC = "SSV\\SRB\\RH_aft_center_segment_FWC";
const static char* MESHNAME_RH_AFT_FWC = "SSV\\SRB\\RH_aft_segment_FWC";


const static char* MESHNAME_LH_FWD_RSRM = "SSV\\SRB\\LH_fwd_segment_RSRM";
const static char* MESHNAME_LH_FWD_CTR_RSRM = "SSV\\SRB\\LH_fwd_center_segment_RSRM";
const static char* MESHNAME_LH_AFT_CTR_RSRM = "SSV\\SRB\\LH_aft_center_segment_RSRM";
const static char* MESHNAME_LH_AFT_RSRM = "SSV\\SRB\\LH_aft_segment_RSRM";

const static char* MESHNAME_RH_FWD_RSRM = "SSV\\SRB\\RH_fwd_segment_RSRM";
const static char* MESHNAME_RH_FWD_CTR_RSRM = "SSV\\SRB\\RH_fwd_center_segment_RSRM";
const static char* MESHNAME_RH_AFT_CTR_RSRM = "SSV\\SRB\\RH_aft_center_segment_RSRM";
const static char* MESHNAME_RH_AFT_RSRM = "SSV\\SRB\\RH_aft_segment_RSRM";


constexpr double SRB_CUTOUT_TIME = 160.0;

constexpr double BSM_MAX_PROPELLANT_MASS = 75.0 * 0.45359237;//BSM propellant mass for each "pack", four motors per "pack", two "packs" per SRB, forward and aft
constexpr double BSM_THRUST0 = 82.76475E3;
constexpr double BSM_ISP0 = 2400.0;

constexpr double NO_SLAG_TIME = 160.0;// match SRB_CUTOUT_TIME

constexpr VECTOR3 SLAG_DIR = { 0.0, -1.0, 0.0 };

constexpr double SRB_SECTION_YPOS[SRB_SECTION_COUNT] = {
	24.81167/*mid pos between attach points XB+976.8375*/ - 40.06799/*ET attach factory joint XB+1577.48*/,// Aft segment
	SRB_SECTION_YPOS[0] + 6.2484,// Aft center segment
	SRB_SECTION_YPOS[1] + 8.128,// Forward center segment
	SRB_SECTION_YPOS[2] + 8.128,// Forward segment
	SRB_SECTION_YPOS[3] + 7.378192// Forward skirt assembly
};

constexpr VECTOR3 CG_OFFSET = { 0.0, 7.319328, 0.0 };// offset between cg at sep and mid point between attachments [m] (cg at SRB SEP ~XB+1265.0)

constexpr VECTOR3 PLUME_LIGHT = { 0.0, -41.22833, 0.0 };// location of plume light source [m] (XB+2600.0)
constexpr VECTOR3 SRM_GIMBAL_POS = { 0.0, -22.94033, 0.0 };// (aprox) location of nozzle gimbal [m] (XB+1880.0)

constexpr VECTOR3 LEFT_FWD_BSM_POS = { 0.295402, 17.35677, -0.81153 };// avg location of left forward BSMs [m] (YB+11.63, XB+293.5, ZB+31.95)
constexpr VECTOR3 LEFT_AFT_BSM_POS = { 0.95151, -23.05463, -2.55 };// avg location of left aft BSMs [m] (XB+1884.5)

constexpr VECTOR3 RIGHT_FWD_BSM_POS = { -0.295402, 17.35677, -0.81153 };// avg location of right forward BSMs [m] (YB-11.63, XB+293.5, ZB+31.95)
constexpr VECTOR3 RIGHT_AFT_BSM_POS = { -0.95151, -23.05463, -2.55 };// avg location of right aft BSMs [m] (XB+1884.5)

constexpr VECTOR3 LEFT_FWD_BSM_DIR = { -0.262003, -0.642788, 0.719846 };// avg direction of left forward BSMs
constexpr VECTOR3 LEFT_AFT_BSM_DIR = { -0.262003, 0.642788, 0.719846 };// avg direction of left aft BSMs

constexpr VECTOR3 RIGHT_FWD_BSM_DIR = { 0.262003, -0.642788, 0.719846 };// avg direction of right forward BSMs
constexpr VECTOR3 RIGHT_AFT_BSM_DIR = { 0.262003, 0.642788, 0.719846 };// avg direction of right aft BSMs

// ==============================================================
// Specialised vessel class Atlantis_SRB
// ==============================================================

// Constructor
SRB::SRB (OBJHANDLE hObj)
: VESSEL4(hObj), Left(true), SRMtype(RSRM), hFwdAssemblyTexture(NULL), hCaseTexture(NULL), bMainEngine(false), bSeparationEngine(false)
{
	for(unsigned short i=0;i<SRB_SECTION_COUNT;i++) {
		hSRMSegmentMesh[i] = NULL;
	}

	hVis = NULL;

	slag1 = 0.0;
	slag2 = 0.0;
	slag3 = 0.0;

	COLOUR4 col_diff = {1.0,0.733f,0.196f,0};
	COLOUR4 col_zero = {0.0,0.0,0.0,0.0};
	COLOUR4 col_ambient = {0.5,0.5,0.5,0};
	SRBLight = AddPointLight( PLUME_LIGHT + CG_OFFSET, 300.0, 1.0, 0.0, 0.0001, col_diff, col_zero, col_ambient );
	SRBLight->Activate( false );

	// default to RSRM
	SRB_MAX_PROPELLANT_MASS = RSRM_MAX_PROPELLANT_MASS;
	SRB_THRUST = RSRM_THRUST;
	SRB_ISP0 = RSRM_ISP0;
	SRB_ISP1 = RSRM_ISP1;
	SRB_nt = RSRM_nt;
	SRB_Seq = RSRM_Seq;
	SRB_Thrust = RSRM_Thrust;
	SRB_Prop = RSRM_Prop;
	SRB_Pc = RSRM_Pc;
}

SRB::~SRB( void )
{
	if (hFwdAssemblyTexture) oapiReleaseTexture( hFwdAssemblyTexture );
	if (hCaseTexture) oapiReleaseTexture( hCaseTexture );
}

void SRB::SetPostSeparationState( double launch_time, double thrust_level, double prop_level )
{
	t0 = launch_time;
	SetPropellantMass(ph_main, prop_level*SRB_MAX_PROPELLANT_MASS);
	SetThrusterLevel(th_main, thrust_level);

	bMainEngine = true;
	bSeparationEngine = true;
	srb_separation_time = oapiGetSimTime();

	SRBLight->Activate( true );
}

void SRB::SetTexture( DEVMESHHANDLE hDevMesh, SURFHANDLE tex )
{
	if (!hDevMesh) return;// no mesh handle

	if (!oapiSetTexture( hDevMesh, 1, tex ))
		oapiWriteLog( "(SSV_SRB) [ERROR] Could not update texture" );
	return;
}

void SRB::LoadTextures( void )
{
	if (!strFwdAssemblyTextureName.empty())
	{
		if (hFwdAssemblyTexture == NULL) hFwdAssemblyTexture = oapiLoadTexture( strFwdAssemblyTextureName.c_str() );
		if (hFwdAssemblyTexture == NULL) throw std::exception( "Could not load SRB Fwd Assembly texture" );
	}

	if (!strCaseTextureName.empty())
	{
		if (hCaseTexture == NULL) hCaseTexture = oapiLoadTexture( strCaseTextureName.c_str() );
		if (hCaseTexture == NULL) throw std::exception( "Could not load SRB Case texture" );
	}
	return;
}

// ==============================================================
// Callback functions
// ==============================================================

void SRB::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		hVis = vis;

		LoadTextures();

		if (hFwdAssemblyTexture) SetTexture( GetDevMesh( vis, mesh_segment[4] ), hFwdAssemblyTexture );
		if (hCaseTexture) for (int i = 0; i < 4; i++) SetTexture( GetDevMesh( vis, mesh_segment[i] ), hCaseTexture );

		if (SRMtype == RSRM)// show cable for RSRM
		{
			DEVMESHHANDLE hDevMesh = GetDevMesh( vis, mesh_segment[4] );
			if (hDevMesh)
			{
				GROUPEDITSPEC grpSpec;
				grpSpec.flags = GRPEDIT_SETUSERFLAG;
				grpSpec.UsrFlag = 0x00000000;
				oapiEditMeshGroup( hDevMesh, 3, &grpSpec );
			}
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkVisualCreated: %s", e.what());
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkVisualCreated" );
		abort();
	}
}

void SRB::clbkVisualDestroyed( VISHANDLE vis, int refcount )
{
	try
	{
		if (vis == hVis) hVis = NULL;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkVisualDestroyed: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkVisualDestroyed" );
		abort();
	}
}

// Set SRB class specs
void SRB::clbkSetClassCaps( FILEHANDLE cfg )
{
	try
	{
		oapiReadItem_bool( cfg, "Left", Left );


		SetEnableFocus (false);
		// SRB cannot receive input focus

		// *********************** physical parameters *********************************

		SetSize (28.0);

		SetCW (1.4, 1.4, 1.4, 0.2);
		SetCrossSections (_V(167.42,22.92,172.64));
		SetRotDrag (_V(0.7,0.1,0.7));
		SetPMI (_V(128.72,2.31,128.64));

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 0, -26.0, -2 ) + CG_OFFSET, 1e5, 1e2, 0.5, 0.005},
			{_V( -2, -26.0, 1 ) + CG_OFFSET, 1e5, 1e2, 0.5, 0.005},
			{_V( 2, -26.0, 1 ) + CG_OFFSET, 1e5, 1e2, 0.5, 0.005},
			{_V( 0, 20.0, 0 ) + CG_OFFSET, 1e5, 1e2, 0.5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		SetLiftCoeffFunc (0);

		ahToOrbiter = CreateAttachment(true, _V( 0.0, 0.0, 0.0 ) + CG_OFFSET, _V(1, 0, 0), _V(0, 1, 0), "SSV_SRB");
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkSetClassCaps" );
		abort();
	}
}

// Finish setup
void SRB::clbkPostCreation ()
{
	try
	{
		SetPropellantMass(ph_main, 0.0);
		SetPropellantMass(phBSM, GetPropellantMaxMass(phBSM));
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkPostCreation" );
		abort();
	}
}

// Simulation time step
void SRB::clbkPostStep (double simt, double simdt, double mjd)
{
	try
	{
		if (bMainEngine) {
			double met = simt-t0;
			if (met >= NO_SLAG_TIME)
			{
				slag1 = 0.0;
				slag2 = 0.0;
				slag3 = 0.0;
			} else
			{
				slag1 = 1.0 - met/NO_SLAG_TIME;
				slag2 = 1.0 - met/NO_SLAG_TIME;
				slag3 = 1.0 - met/NO_SLAG_TIME;
			}

			if (met >= SRB_CUTOUT_TIME) {
				SetThrusterLevel (th_main, 0);
				bMainEngine = false;
				SRBLight->Activate( false );
				// After the propellant is burnt out we should be airborne.
				// Now we can prepare touchdown points for "landing"
				//SetTouchdownPoints (_V(0,9,3), _V(-1,1,-3), _V(1,1,-3));
			} else {
				double thrust_level, prop_level, pc;
				GetSRB_State (met, thrust_level, prop_level, pc);
				SetThrusterLevel (th_main, thrust_level);
				SetPropellantMass( ph_main, prop_level * GetPropellantMaxMass( ph_main ) );
			}
			if (bSeparationEngine) {
				//static double bolt_t = 0.5;
				double srb_dt = simt - srb_separation_time;

				if(srb_dt < 1.2)
				{
					for(int i=0;i<2;i++) SetThrusterLevel(thBSM[i], 1.0-(srb_dt*0.583));
				} else {
					for(int i=0;i<2;i++) SetThrusterLevel(thBSM[i], 0.0);
				}
			}
		}
		// self delete
		if (GetAltitude() < 250.0 && !GetAttachmentStatus(ahToOrbiter)) oapiDeleteVessel (GetHandle());
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkPostStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkPostStep" );
		abort();
	}
}

void SRB::clbkLoadStateEx(FILEHANDLE scn, void *status)
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
			else ParseScenarioLineEx( line, status );
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkLoadStateEx" );
		abort();
	}
}

void SRB::clbkSaveState(FILEHANDLE scn)
{
	try
	{
		VESSEL4::clbkSaveState( scn );
		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in SRB::clbkSaveState" );
		abort();
	}
}

// time-dependent calculation of SRB thrust and remaining propellant
void SRB::GetSRB_State( double met, double &thrust_level, double &prop_level, double& pc )
{
	int i;
	for (i = SRB_nt-2; i >= 0; i--)
		if (met > SRB_Seq[i]) break;

	double SRB_ThrSCL=(SRB_Thrust[i+1]-SRB_Thrust[i])/(SRB_Seq[i+1]-SRB_Seq[i]);
	thrust_level = SRB_ThrSCL * (met-SRB_Seq[i]) + SRB_Thrust[i];
	if (met>0.0) thrust_level += (0.01435 * oapiRand()) - (0.01435 * oapiRand());
	thrust_level = max(0.0, thrust_level);

	double SRB_PrpSCL=(SRB_Prop[i+1]-SRB_Prop[i])/(SRB_Seq[i+1]-SRB_Seq[i]);
	prop_level = SRB_PrpSCL * (met-SRB_Seq[i]) + SRB_Prop[i];

	double SRB_PcSCL = (SRB_Pc[i + 1] - SRB_Pc[i]) / (SRB_Seq[i + 1] - SRB_Seq[i]);
	pc = SRB_PcSCL * (met - SRB_Seq[i]) + SRB_Pc[i];

	return;
}

void SRB::LoadMissionFile( void )
{
	std::string filename;
	filename = "Missions\\SSV\\" + strMission + ".json";

	FILE* hF = fopen( filename.c_str(), "r" );
	if (hF == NULL)
	{
		oapiWriteLogV( "(SSV_SRB) [ERROR] Can't open mission file %s", strMission.c_str() );
		return;
	}

	oapiWriteLogV( "(SSV_SRB) [INFO] Loading mission file %s", strMission.c_str() );

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
		oapiWriteLog( "(SSV_SRB) [ERROR] Error parsing mission file version" );
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
			oapiWriteLogV( "(SSV_SRB) [ERROR] Unknown mission file version %d", version->valueint );
			break;
	}

	cJSON_Delete( root );
	delete[] missionfilestr;
	return;
}

void SRB::LoadMissionV1( cJSON* root )
{
	// read SolidRocketBoosters
	cJSON* srb = cJSON_GetObjectItemCaseSensitive( root, "Solid Rocket Boosters" );

	cJSON* tmp = cJSON_GetObjectItemCaseSensitive( srb, "SRM" );
	if (!strcmp( "SPM", tmp->valuestring ))
	{
		SRMtype = SPM;
	}
	else if (!strcmp( "HPM", tmp->valuestring ))
	{
		SRMtype = HPM;
	}
	else if (!strcmp( "FWC", tmp->valuestring ))
	{
		SRMtype = FWC;
	}
	else //if (!strcmp( "RSRM", tmp->valuestring ))
	{
		SRMtype = RSRM;
	}

	tmp = cJSON_GetObjectItemCaseSensitive( srb, Left ? "LH Fwd Assembly Texture" : "RH Fwd Assembly Texture" );
	strFwdAssemblyTextureName = "SSV\\SRB\\" + std::string( tmp->valuestring ) + ".dds";

	tmp = cJSON_GetObjectItemCaseSensitive( srb, Left ? "LH Case Texture" : "RH Case Texture" );
	strCaseTextureName = "SSV\\SRB\\" + std::string( tmp->valuestring ) + ".dds";
	return;
}

void SRB::SetConfiguration( void )
{
	if (SRMtype == SPM)
	{
		SRB_MAX_PROPELLANT_MASS = SPM_MAX_PROPELLANT_MASS;
		SRB_THRUST = SPM_THRUST;
		SRB_ISP0 = SPM_ISP0;
		SRB_ISP1 = SPM_ISP1;
		SRB_nt = SPM_nt;
		SRB_Seq = SPM_Seq;
		SRB_Thrust = SPM_Thrust;
		SRB_Prop = SPM_Prop;
		SRB_Pc = SPM_Pc;
	}
	else if (SRMtype == HPM)
	{
		SRB_MAX_PROPELLANT_MASS = HPM_MAX_PROPELLANT_MASS;
		SRB_THRUST = HPM_THRUST;
		SRB_ISP0 = HPM_ISP0;
		SRB_ISP1 = HPM_ISP1;
		SRB_nt = HPM_nt;
		SRB_Seq = HPM_Seq;
		SRB_Thrust = HPM_Thrust;
		SRB_Prop = HPM_Prop;
		SRB_Pc = HPM_Pc;
	}
	else if (SRMtype == FWC)
	{
		SRB_MAX_PROPELLANT_MASS = FWC_MAX_PROPELLANT_MASS;
		SRB_THRUST = FWC_THRUST;
		SRB_ISP0 = FWC_ISP0;
		SRB_ISP1 = FWC_ISP1;
		SRB_nt = FWC_nt;
		SRB_Seq = FWC_Seq;
		SRB_Thrust = FWC_Thrust;
		SRB_Prop = FWC_Prop;
		SRB_Pc = FWC_Pc;
	}
	/*else if (SRMtype == RSRM)
	{
		SRB_MAX_PROPELLANT_MASS = RSRM_MAX_PROPELLANT_MASS;
		SRB_THRUST = RSRM_THRUST;
		SRB_ISP0 = RSRM_ISP0;
		SRB_ISP1 = RSRM_ISP1;
		SRB_nt = RSRM_nt;
		SRB_Seq = RSRM_Seq;
		SRB_Thrust = RSRM_Thrust;
		SRB_Prop = RSRM_Prop;
		SRB_Pc = RSRM_Pc;
	}*/

	hSRMSegmentMesh[4] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_ASSEMBLY : MESHNAME_RH_FWD_ASSEMBLY );

	if (SRMtype == SPM)
	{
		hSRMSegmentMesh[0] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_SPM : MESHNAME_RH_AFT_SPM );
		hSRMSegmentMesh[1] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_CTR_SPM : MESHNAME_RH_AFT_CTR_SPM );
		hSRMSegmentMesh[2] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_CTR_SPM : MESHNAME_RH_FWD_CTR_SPM );
		hSRMSegmentMesh[3] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_SPM : MESHNAME_RH_FWD_SPM );

	}
	else if (SRMtype == HPM)
	{
		hSRMSegmentMesh[0] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_HPM : MESHNAME_RH_AFT_HPM );
		hSRMSegmentMesh[1] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_CTR_HPM : MESHNAME_RH_AFT_CTR_HPM );
		hSRMSegmentMesh[2] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_CTR_HPM : MESHNAME_RH_FWD_CTR_HPM );
		hSRMSegmentMesh[3] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_HPM : MESHNAME_RH_FWD_HPM );
	}
	else if (SRMtype == FWC)
	{
		hSRMSegmentMesh[0] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_FWC : MESHNAME_RH_AFT_FWC );
		hSRMSegmentMesh[1] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_CTR_FWC : MESHNAME_RH_AFT_CTR_FWC );
		hSRMSegmentMesh[2] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_CTR_FWC : MESHNAME_RH_FWD_CTR_FWC );
		hSRMSegmentMesh[3] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_FWC : MESHNAME_RH_FWD_FWC );
	}
	else// default RSRM
	{
		hSRMSegmentMesh[0] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_RSRM : MESHNAME_RH_AFT_RSRM );
		hSRMSegmentMesh[1] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_AFT_CTR_RSRM : MESHNAME_RH_AFT_CTR_RSRM );
		hSRMSegmentMesh[2] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_CTR_RSRM : MESHNAME_RH_FWD_CTR_RSRM );
		hSRMSegmentMesh[3] = oapiLoadMeshGlobal( Left ? MESHNAME_LH_FWD_RSRM : MESHNAME_RH_FWD_RSRM );
	}

	if (SRMtype == SPM) SetEmptyMass( SPM_SRB_EMPTY_MASS );
	else if (SRMtype == HPM) SetEmptyMass( HPM_SRB_EMPTY_MASS );
	else if (SRMtype == FWC) SetEmptyMass( FWC_SRB_EMPTY_MASS );
	else SetEmptyMass( RSRM_SRB_EMPTY_MASS );

	// ************************* propellant specs **********************************

	if (SRMtype == SPM) ph_main = CreatePropellantResource( SPM_MAX_PROPELLANT_MASS );
	else if (SRMtype == HPM) ph_main = CreatePropellantResource( HPM_MAX_PROPELLANT_MASS );
	else if (SRMtype == FWC) ph_main = CreatePropellantResource( FWC_MAX_PROPELLANT_MASS );
	else ph_main = CreatePropellantResource( RSRM_MAX_PROPELLANT_MASS );

	phBSM = CreatePropellantResource(BSM_MAX_PROPELLANT_MASS * 8.0);

	// *********************** thruster definitions ********************************
	// reduced v0 so gas "drags" with post SRB sep tumble
	// (currently a gap in the gas appears at sep, can't do better with current setup)
	static PARTICLESTREAMSPEC srb_contrail = {
		0, 1.0, 20.0, /*50.0*/25.0, 0.1, 10.0, 10.0, 0.5, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1,
	};
	static PARTICLESTREAMSPEC srb_exhaust = {
		0, 1.2, 20.0, /*50.0*/25.0, 0.05, 1.0, 12.0, 0.5, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1,
	};
	static PARTICLESTREAMSPEC srb_slag1 = {
		0, 0.1, SLAG1_RATE, 50.0, SLAG_SPREAD, 4, 0, 0.1, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};
	static PARTICLESTREAMSPEC srb_slag2 = {
		0, 0.05, SLAG2_RATE, 50.0, SLAG_SPREAD, 3, 0, 0.1, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};
	static PARTICLESTREAMSPEC srb_slag3 = {
		0, 0.01, SLAG3_RATE, 50.0, SLAG_SPREAD, 3, 0, 0.1, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	static PARTICLESTREAMSPEC bsm_exhaust = {
		0, 2.4, 5000, 45, 0.1, 0.2, 30, 3.0, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT, 1, 1
	};

	/*static PARTICLESTREAMSPEC bsm_contrail = {
		0, 1.6, 40, 70.0, 0.1, 10, 8, 3.0, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.5,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 0.1
	};

	static PARTICLESTREAMSPEC bsm_residual = {
		0, 0.3, 20, 5.0, 0.3, 10, 1, 1.5, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 0.5,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 0.1
	};*/

	// main engine
	if (SRMtype == SPM) th_main = CreateThruster( SRM_GIMBAL_POS + CG_OFFSET, _V( 0.0, 1.0, 0.0 ), SPM_THRUST, ph_main, SPM_ISP0, SPM_ISP1 );
	else if (SRMtype == HPM) th_main = CreateThruster( SRM_GIMBAL_POS + CG_OFFSET, _V( 0.0, 1.0, 0.0 ), HPM_THRUST, ph_main, HPM_ISP0, HPM_ISP1 );
	else if (SRMtype == FWC) th_main = CreateThruster( SRM_GIMBAL_POS + CG_OFFSET, _V( 0.0, 1.0, 0.0 ), FWC_THRUST, ph_main, FWC_ISP0, FWC_ISP1 );
	else th_main = CreateThruster( SRM_GIMBAL_POS + CG_OFFSET, _V( 0.0, 1.0, 0.0 ), RSRM_THRUST, ph_main, RSRM_ISP0, RSRM_ISP1 );

	SURFHANDLE tex = oapiRegisterExhaustTexture( "Exhaust2" );
	srb_exhaust.tex = oapiRegisterParticleTexture( "SSV\\SRB\\SRB_exhaust" );
	srb_contrail.tex = oapiRegisterParticleTexture( "SSV\\SRB\\SRB_contrail" );
	AddExhaust( th_main, 16.0, 2.0, 3.0, tex );
	AddExhaustStream( th_main, &srb_contrail );
	AddExhaustStream( th_main, &srb_exhaust );

	//BSM
	if (Left)
	{
		thBSM[0] = CreateThruster( LEFT_AFT_BSM_POS + CG_OFFSET, LEFT_AFT_BSM_DIR, 4.0 * BSM_THRUST0, phBSM, BSM_ISP0 );
		thBSM[1] = CreateThruster( LEFT_FWD_BSM_POS + CG_OFFSET, LEFT_FWD_BSM_DIR, 4.0 * BSM_THRUST0, phBSM, BSM_ISP0 );
	} else
	{
		thBSM[0] = CreateThruster( RIGHT_AFT_BSM_POS + CG_OFFSET, RIGHT_AFT_BSM_DIR, 4.0 * BSM_THRUST0, phBSM, BSM_ISP0 );
		thBSM[1] = CreateThruster( RIGHT_FWD_BSM_POS + CG_OFFSET, RIGHT_FWD_BSM_DIR, 4.0 * BSM_THRUST0, phBSM, BSM_ISP0 );
	}
	// for simplicity, the separation bolts directly use SRB propellant. We give
	// them an insanely high ISP to avoid significant propellant drainage

	//AddExhaust (thBSM[0], 5.0, 0.25);
	//AddExhaust (thBSM[1], 5.0, 0.25);
	bsm_exhaust.tex = oapiRegisterParticleTexture ("SSV\\SRB\\SRB_contrail");
	AddExhaustStream (thBSM[0], &bsm_exhaust);
	AddExhaustStream (thBSM[1], &bsm_exhaust);
	//AddExhaustStream (thBSM[0], &bsm_contrail);
	//AddExhaustStream (thBSM[1], &bsm_contrail);

	//Add slag effect streams
	AddParticleStream(&srb_slag1, SRM_GIMBAL_POS + CG_OFFSET, SLAG_DIR, &slag1);
	AddParticleStream(&srb_slag2, SRM_GIMBAL_POS + CG_OFFSET, SLAG_DIR, &slag2);
	AddParticleStream(&srb_slag3, SRM_GIMBAL_POS + CG_OFFSET, SLAG_DIR, &slag3);


	// show meshes
	//ClearMeshes( true );

	for (int i = 0; i < SRB_SECTION_COUNT; i++)
	{
		VECTOR3 ofs;
		ofs = _V( 0.0, SRB_SECTION_YPOS[i], 0.0 ) + CG_OFFSET;
		mesh_segment[i] = AddMesh( hSRMSegmentMesh[i], &ofs );

	}
	return;
}

// ==============================================================
// API interface
// ==============================================================

// Initialisation
DLLCLBK VESSEL *ovcInit (OBJHANDLE hvessel, int flightmodel)
{
	try
	{
		return new SRB( hvessel );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

// Cleanup
DLLCLBK void ovcExit (VESSEL *vessel)
{
	try
	{
		if (vessel) delete static_cast<SRB*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_SRB) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_SRB) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}
