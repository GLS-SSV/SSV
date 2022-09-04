/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/21   GLS
2020/03/24   GLS
2020/03/25   GLS
2020/03/26   GLS
2020/03/28   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/04/02   GLS
2020/04/03   GLS
2020/04/06   GLS
2020/04/07   GLS
2020/04/08   GLS
2020/04/10   GLS
2020/04/14   GLS
2020/04/15   GLS
2020/04/16   GLS
2020/04/20   GLS
2020/04/21   GLS
2020/04/22   GLS
2020/04/23   GLS
2020/04/28   GLS
2020/05/01   GLS
2020/05/05   GLS
2020/05/06   GLS
2020/05/07   GLS
2020/05/08   GLS
2020/05/09   GLS
2020/05/10   GLS
2020/05/14   GLS
2020/05/17   GLS
2020/05/23   GLS
2020/05/24   GLS
2020/05/25   GLS
2020/05/28   GLS
2020/05/29   GLS
2020/05/31   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/07/03   GLS
2020/07/08   GLS
2020/07/10   GLS
2020/07/11   GLS
2020/07/26   GLS
2020/07/30   GLS
2020/08/10   GLS
2020/08/11   GLS
2020/08/16   GLS
2020/08/19   GLS
2020/08/22   GLS
2020/08/24   GLS
2020/08/25   GLS
2020/08/30   GLS
2020/08/31   GLS
2020/09/02   GLS
2020/09/04   GLS
2020/09/07   GLS
2020/09/12   GLS
2020/09/15   GLS
2020/09/29   GLS
2020/10/03   GLS
2020/10/05   GLS
2020/10/06   GLS
2020/10/07   GLS
2020/10/10   GLS
2020/10/11   GLS
2020/11/10   GLS
2021/01/11   GLS
2021/02/15   GLS
2021/02/16   GLS
2021/02/28   GLS
2021/03/18   GLS
2021/03/19   GLS
2021/03/20   GLS
2021/03/21   GLS
2021/04/06   GLS
2021/04/07   GLS
2021/04/17   GLS
2021/05/21   GLS
2021/05/30   GLS
2021/05/31   GLS
2021/06/01   GLS
2021/06/03   GLS
2021/06/06   GLS
2021/06/07   GLS
2021/06/09   GLS
2021/06/11   GLS
2021/06/13   GLS
2021/06/15   GLS
2021/06/16   GLS
2021/06/18   GLS
2021/06/19   GLS
2021/06/20   GLS
2021/06/23   GLS
2021/06/28   GLS
2021/06/29   GLS
2021/07/01   GLS
2021/07/02   GLS
2021/07/31   GLS
2021/08/03   GLS
2021/08/07   GLS
2021/08/08   GLS
2021/08/13   GLS
2021/08/24   GLS
2021/09/13   GLS
2021/09/20   GLS
2021/10/09   GLS
2021/10/23   GLS
2021/11/13   GLS
2021/11/27   GLS
2021/12/05   GLS
2021/12/23   GLS
2021/12/27   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/01   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/01/19   GLS
2022/01/23   GLS
2022/02/05   GLS
2022/02/07   GLS
2022/02/16   GLS
2022/02/17   GLS
2022/02/19   GLS
2022/03/21   GLS
2022/03/24   GLS
2022/03/25   GLS
2022/03/26   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/05   GLS
2022/04/17   GLS
2022/04/26   GLS
2022/05/13   GLS
2022/05/29   GLS
2022/06/16   GLS
2022/06/19   GLS
2022/06/24   GLS
2022/07/18   GLS
2022/08/05   GLS
2022/08/08   GLS
2022/08/10   GLS
2022/08/20   GLS
2022/08/27   GLS
********************************************/
// ==============================================================
//                 ORBITER MODULE: Atlantis
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2003 Martin Schweiger
//                   All rights reserved
//
// Atlantis.cpp
// Reference implementation of Atlantis (Space Shuttle) vessel
// class module
//
// RMS, grappling and MMU capabilities by Robert Conley
// ==============================================================

#define STRICT 1
#define ORBITER_MODULE
#include "Atlantis.h"
#include "..\SRB\SRB.h"
#include "..\ET\ET.h"
#include "CRT.h"
#include "ParameterValues.h"
#include "AerodynamicData.h"
#include "..\CommonDefs.h"
#include "SSVOptions.h"
#include "Atlantis_vc_defs.h"
#include "..\SSVSound.h"
#include "meshres.h"
#include "meshres_vc.h"
#include "meshres_vcext.h"
#include "resource.h"
#include "AtlantisSubsystemDirector.h"
#include "dps/IDP.h"
#include "dps/MasterTimingUnit.h"
#include "dps/SimpleGPCSystem.h"
#include "dps/SimpleShuttleBus.h"
#include "dps\SimpleMDM_FF1.h"
#include "dps\SimpleMDM_FF2.h"
#include "dps\SimpleMDM_FF3.h"
#include "dps\SimpleMDM_FF4.h"
#include "dps\SimpleMDM_FA1.h"
#include "dps\SimpleMDM_FA2.h"
#include "dps\SimpleMDM_FA3.h"
#include "dps\SimpleMDM_FA4.h"
#include "dps\SimpleMDM_PF1.h"
#include "dps\SimpleMDM_PF2.h"
#include "dps\SimpleMDM_OF1.h"
#include "dps\SimpleMDM_OF2.h"
#include "dps\SimpleMDM_OF3.h"
#include "dps\SimpleMDM_OF4.h"
#include "dps\SimpleMDM_OA1.h"
#include "dps\SimpleMDM_OA2.h"
#include "dps\SimpleMDM_OA3.h"
#include "dps/SSME_SOP.h"
#include "dps/MPS_ATVC_CMD_SOP.h"
#include "dps/RSLS.h"
#include "dps/MasterTimingUnit.h"
#include "eva_docking/ODS.h"
#include "eva_docking\TunnelAdapterAssembly.h"
#include "eva_docking\IntAirlock.h"
#include "AirDataProbes.h"
#include "ETUmbilicalDoors.h"
#include "WSB.h"
#include "FMC1.h"
#include "FMC2.h"
#include "FMC3.h"
#include "MMC1.h"
#include "MMC2.h"
#include "MMC3.h"
#include "MMC4.h"
#include "AMC1.h"
#include "AMC2.h"
#include "AMC3.h"
#include "ActiveLatchGroup.h"
#include "RMS.h"
#include "Payload_MPM.h"
#include "ASE_IUS.h"
#include "CISS.h"
#include "PayloadBay.h"
#include "LandingGear.h"
#include "AeroSurfaces.h"
#include "mps/SSME.h"
#include "mps/SSME_BLOCK_II.h"
#include "mps/EIU.h"
#include "mps/HeliumSystem.h"
#include "mps/MPS.h"
#include "oms\OMS.h"
#include "oms\OMS_TVC.h"
#include "vc/PanelA7A3.h"
#include "vc/PanelA8A3.h"
#include "vc/PanelF2.h"
#include "vc/PanelF3.h"
#include "vc/PanelF4.h"
#include "vc/PanelF6.h"
#include "vc/PanelF7.h"
#include "vc/PanelF8.h"
#include "vc/PanelF9.h"
#include "vc/PanelO1.h"
#include "vc/PanelO2.h"
#include "vc/PanelO3.h"
#include "vc/PanelO5.h"
#include "vc/PanelO6.h"
#include "vc/PanelO7.h"
#include "vc/PanelO8.h"
#include "vc/PanelO9.h"
#include "vc/PanelO13.h"
#include "vc/PanelO14.h"
#include "vc/PanelO15.h"
#include "vc/PanelO16.h"
#include "vc/PanelO17.h"
#include "vc/PanelA1U.h"
#include "vc/PanelA1L.h"
#include "vc/PanelA1R.h"
#include "vc/PanelA2.h"
#include "vc/PanelA3.h"
#include "vc/PanelA4.h"
#include "vc/PanelA6U.h"
#include "vc/PanelA8A1.h"
#include "vc/PanelA8A2.h"
#include "vc/PanelA7U.h"
#include "vc/PanelR1.h"
#include "vc/PanelR2.h"
#include "vc/PanelR4.h"
#include "vc/PanelR10.h"
#include "vc/PanelA12A1.h"
#include "vc/PanelA12A2.h"
#include "vc/PanelR13U.h"
#include "vc/PanelR13L.h"
#include "vc/AftMDU.h"
#include "vc/PanelC2.h"
#include "vc/PanelC3.h"
#include "vc/PanelL1.h"
#include "vc/PanelL2.h"
#include "vc/PanelL4.h"
#include "vc/PanelL9.h"
#include "vc/PanelL10_IUS.h"
#include "vc/PanelL12U_IUS.h"
#include "vc/PanelL12U_Centaur.h"
#include "vc/MDU.h"
#include "vc\vc_defs.h"
#include "comm\GCIL.h"
#include "comm\DeployedAssembly.h"
#include "comm\ElectronicsAssembly1.h"
#include "comm\ElectronicsAssembly2.h"
#include "MasterEventsController.h"
#include "gnc\RA.h"
#include "gnc/ATVC.h"
#include "MPS_TVC.h"
#include "DragChute.h"
#include "eps\PRSD.h"
#include "AnnunciatorControlAssembly.h"
#include "VideoControlUnit.h"
#include "DDU.h"
#include "HUD.h"
#include "APU.h"
#include "RHC.h"
#include "THC.h"
#include "RPTA.h"
#include "SBTC.h"
#include "StarTrackerDoors.h"
#include "VentDoors.h"
#include "..\T0UmbilicalReference.h"
#include "mission\Mission.h"
#include "MissionFileManagement.h"
#include <MathSSV.h>
#include <UtilsSSV.h>
#include <cassert>
#include "gcConst.h"
#include <EngConst.h>


#include <stdio.h>
#include <fstream>

//#include <Stopwatch.h>


#define LOADBMP(id) (LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (id)))

// ==============================================================
// Global (class-wide) parameters

GDIParams g_Param;

#if _DEBUG
std::ofstream animlog;
#endif// _DEBUG

inline void BeginLoggingAnims(void)
{
#if _DEBUG
	animlog.open("SSVAnimation.log");
	animlog << "ANIMATION LOG" << std::endl;
#endif// _DEBUG
}

inline void LogAnim(const std::string& name, UINT anim)
{
#if _DEBUG
	animlog << name << "\t" << std::dec << anim << " ( 0x" << std::hex << anim << ")" << std::endl;
#endif// _DEBUG
}

inline void EndLoggingAnims(void)
{
#if _DEBUG
	animlog.close();
#endif// _DEBUG
}

VECTOR3 CalcOMSThrustDir( unsigned int side, double pitch, double yaw )
{
	VECTOR3 dir;
	VECTOR3 axisP;
	VECTOR3 axisY;

	if (side == 0)
	{
		dir = L_OMS_DIR;
		axisP = L_OMS_AXIS_PITCH;
		axisY = L_OMS_AXIS_YAW;
	}
	else
	{
		dir = R_OMS_DIR;
		axisP = R_OMS_AXIS_PITCH;
		axisY = R_OMS_AXIS_YAW;
	}

	MATRIX3 mrot = rotm( axisP, pitch * RAD );
	dir = mul( mrot, dir );
	axisY = mul( mrot, axisY );

	mrot = rotm( axisY, yaw * RAD );
	dir = mul( mrot, dir );

	return dir;
}


inline void ssuAssert(bool expression, const char* context)
{
	static char buf[200];
	if (!expression)
	{
		sprintf_s(buf, 200, "(SSV_OV) [ERROR] assertion failed : %s", context);
		oapiWriteLog(buf);
	}

}


DLLCLBK void InitModule( HINSTANCE hModule )
{
	try
	{
		g_Param.hDLL = hModule;

		// initialize aerodynamic lookup tables
		oapiWriteLog( "(SSV_OV) [INFO] Loading aerodynamic lookup tables..." );
		LoadAerodynamicData();

		oapiWriteLog( "(SSV_OV) [INFO] Loading bitmaps..." );
		g_Param.clock_digits = oapiCreateSurface(LOADBMP(IDB_CLOCKDIGITS));
		if (g_Param.clock_digits == NULL) throw std::exception( "Loading bitmap \"clocknums.bmp\" failed." );

		g_Param.deu_characters = LOADBMP(IDB_DEUCHARACTERS);
		HDC Temp1DC = CreateDC( "DISPLAY", NULL, NULL, NULL );
		g_Param.DeuCharBitmapDC = CreateCompatibleDC( Temp1DC );
		SelectObject( g_Param.DeuCharBitmapDC, g_Param.deu_characters );
		SetStretchBltMode( g_Param.DeuCharBitmapDC, HALFTONE );
		StretchBlt( g_Param.DeuCharBitmapDC, 0, 0, 284, 256, g_Param.DeuCharBitmapDC, 0, 0, 512, 512, SRCCOPY );
		//DeleteDC( Temp1DC );

		g_Param.deu_characters_overbright = LOADBMP(IDB_DEUCHARACTERSOVERBRIGHT);
		//Temp1DC = CreateDC( "DISPLAY", NULL, NULL, NULL );
		g_Param.DeuCharOvrBrgtBitmapDC = CreateCompatibleDC( Temp1DC );
		SelectObject( g_Param.DeuCharOvrBrgtBitmapDC, g_Param.deu_characters_overbright );
		SetStretchBltMode( g_Param.DeuCharOvrBrgtBitmapDC, HALFTONE );
		StretchBlt( g_Param.DeuCharOvrBrgtBitmapDC, 0, 0, 284, 256, g_Param.DeuCharOvrBrgtBitmapDC, 0, 0, 512, 512, SRCCOPY );
		//DeleteDC( Temp1DC );

		g_Param.deu_characters_fault = LOADBMP(IDB_DEUCHARACTERSFAULT);
		//Temp1DC = CreateDC( "DISPLAY", NULL, NULL, NULL );
		g_Param.DeuCharFaultBitmapDC = CreateCompatibleDC( Temp1DC );
		SelectObject( g_Param.DeuCharFaultBitmapDC, g_Param.deu_characters_fault );
		SetStretchBltMode( g_Param.DeuCharOvrBrgtBitmapDC, HALFTONE );
		StretchBlt( g_Param.DeuCharFaultBitmapDC, 0, 0, 284, 256, g_Param.DeuCharFaultBitmapDC, 0, 0, 512, 512, SRCCOPY );
		DeleteDC( Temp1DC );

		g_Param.deu_charactersSH = oapiCreateSurface( LOADBMP(IDB_DEUCHARACTERS) );
		if (g_Param.deu_charactersSH == NULL) throw std::exception( "Loading bitmap \"DEU_Raw.bmp\" failed." );

		g_Param.deu_characters_overbrightSH = oapiCreateSurface( LOADBMP(IDB_DEUCHARACTERSOVERBRIGHT) );
		if (g_Param.deu_characters_overbrightSH == NULL) throw std::exception( "Loading bitmap \"DEU_Raw_overbright.bmp\" failed." );

		g_Param.deu_characters_faultSH = oapiCreateSurface( LOADBMP(IDB_DEUCHARACTERSFAULT) );
		if (g_Param.deu_characters_faultSH == NULL) throw std::exception( "Loading bitmap \"DEU_Raw_fault.bmp\" failed." );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in InitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in InitModule" );
		abort();
	}
}

DLLCLBK void ExitModule( HINSTANCE hModule )
{
	try
	{
		if (g_Param.clock_digits)
		{
			oapiDestroySurface(g_Param.clock_digits);
		}

		DeleteDC( g_Param.DeuCharBitmapDC );
		if (g_Param.deu_characters)
		{
			DeleteObject( g_Param.deu_characters );
		}

		DeleteDC( g_Param.DeuCharOvrBrgtBitmapDC );
		if (g_Param.deu_characters_overbright)
		{
			DeleteObject( g_Param.deu_characters_overbright );
		}

		DeleteDC( g_Param.DeuCharFaultBitmapDC );
		if (g_Param.deu_characters_fault)
		{
			DeleteObject( g_Param.deu_characters_fault );
		}

		if (g_Param.deu_charactersSH)
		{
			oapiDestroySurface( g_Param.deu_charactersSH );
		}

		if (g_Param.deu_characters_overbrightSH)
		{
			oapiDestroySurface( g_Param.deu_characters_overbrightSH );
		}

		if (g_Param.deu_characters_faultSH)
		{
			oapiDestroySurface( g_Param.deu_characters_faultSH );
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in ExitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in ExitModule" );
		abort();
	}
}

DLLCLBK VESSEL* ovcInit( OBJHANDLE hvessel, int flightmodel )
{
	try
	{
		return new Atlantis(hvessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit( VESSEL* vessel )
{
	try
	{
		if (vessel) delete static_cast<Atlantis*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}


Atlantis::Atlantis( OBJHANDLE hVessel, int fmodel ):VESSEL4( hVessel, fmodel ),
pActiveLatches( 5, NULL )
{
	int i;

	// init D3D9
	if (pD3D9 = gcGetCoreInterface()) oapiWriteLogV( "(SSV_OV) [INFO] Using D3D9" );
	else oapiWriteLogV( "(SSV_OV) [INFO] Using MOGE" );


	//----------------------------------------------------
	// Make these first, for avoiding CTDs
	//----------------------------------------------------
	InitMissionManagementMemory();
	pMission = ssvGetDefaultMission();			//No mission selected
	options = new SSVOptions();
	bundleManager = new DiscreteBundleManager();

	for (i = 0; i < 11; i++) mdus[i] = NULL;

	pExtAirlock = NULL;

	psubsystems = new AtlantisSubsystemDirector( this );

	pgForward = new vc::PanelGroup<Atlantis>();
	pgLeft = new vc::PanelGroup<Atlantis>();
	pgCenter = new vc::PanelGroup<Atlantis>();
	pgRight = new vc::PanelGroup<Atlantis>();
	pgOverhead = new vc::PanelGroup<Atlantis>();
	pgOverheadAft = new vc::PanelGroup<Atlantis>();
	pgAftPort = new vc::PanelGroup<Atlantis>();
	pgAft = new vc::PanelGroup<Atlantis>();
	pgAftStbd = new vc::PanelGroup<Atlantis>();

	pSimpleBus = new dps::SimpleShuttleBus();

	pASE_IUS = NULL;
	pCISS = NULL;

	pRMS = NULL;
	pPLMPM = NULL;

	pDragChute = NULL;

	ahLeftSRB = NULL;
	ahRightSRB = NULL;

	pT0UmbRef = new T0UmbilicalReference( this );

	simTtwang = -1.0;
	met = 0.0;

	status = STATE_ORBITER;
	mesh_orbiter = MESH_UNDEFINED;
	mesh_vcexternal = MESH_UNDEFINED;
	mesh_vc = MESH_UNDEFINED;
	mesh_middeck = MESH_UNDEFINED;
	mesh_verticaltail = MESH_UNDEFINED;
	mesh_ssme[0] = MESH_UNDEFINED;
	mesh_ssme[1] = MESH_UNDEFINED;
	mesh_ssme[2] = MESH_UNDEFINED;

	vis = NULL;

	hOVTexture = NULL;
	hLOMSTexture = NULL;
	hROMSTexture = NULL;
	hAftBulkheadTexture = NULL;

	//SRB slag effects
	slag1 = 0.0;
	slag2 = 0.0;
	slag3 = 0.0;

	pshSlag1[0] = pshSlag1[1] = NULL;
	pshSlag2[0] = pshSlag2[1] = NULL;
	pshSlag3[0] = pshSlag3[1] = NULL;

	pshSRBFlame[0] = NULL;
	pshSRBFlame[1] = NULL;
	pshSRBSmoke[0] = NULL;
	pshSRBSmoke[1] = NULL;

	huds.ngroup = GRP_VIRTUALHUD_VC;
	huds.size = 0.13372;

	VCMode = 0;
	scnVCMode = 0;

	// propellant resources
	ph_loms = NULL;
	ph_roms = NULL;
	ph_koms = NULL;
	ph_frcs = NULL;
	ph_lrcs = NULL;
	ph_rrcs = NULL;
	ph_mps = NULL;
	ph_srb = NULL;

	SRBpc = 0.0;

	LOXmass = 0;
	LH2mass = 0;

	th_oms[0] = th_oms[1] = NULL;

	for (i = 0; i < 3; i++)
	{
		th_ssme[i] = NULL;
		th_ssme_gox[i] = NULL;
	}
	thMPSDump[0] = NULL;
	thMPSDump[1] = NULL;
	thMPSDump[2] = NULL;
	thMPSDump[3] = NULL;
	thMPSDump[4] = NULL;
	thMPSDump[5] = NULL;
	thMPSDump[6] = NULL;
	thMPSDump[7] = NULL;
	th_srb[0] = th_srb[1] = NULL;

	thg_pitchup = thg_pitchdown = NULL;
	thg_yawleft = thg_yawright = NULL;
	thg_rollleft = thg_rollright = NULL;
	thg_transfwd = thg_transaft = NULL;
	thg_transleft = thg_transright = NULL;
	thg_transup = thg_transdown = NULL;

	bSSMEsDefined = false;
	bOMSDefined = false;
	bRCSDefined = false;

	phLOXdump = NULL;
	phLH2dump = NULL;

	for (i = 0; i < 3; i++) {
		ex_main[i] = NULL;
	}

	hStackAirfoil = NULL;
	hOVAirfoilV = NULL;
	hOVAirfoilH = NULL;

	orbiter_ofs = _V(0, 0, 0);
	currentCoG = _V(0.0, 0.0, 0.0);

	// preload meshes
	hOrbiterMesh = oapiLoadMeshGlobal( MESHNAME_ORBITER );
	hVerticalTailMesh = NULL;
	hOrbiterVCExternalMesh = oapiLoadMeshGlobal( MESHNAME_VC_EXTERNAL );
	hOrbiterVCMesh = oapiLoadMeshGlobal( MESHNAME_VC );
	hMidDeckMesh = oapiLoadMeshGlobal( MESHNAME_MIDDECK );
	hDevOrbiterMesh = NULL;
	hDevOrbiterVCExternalMesh = NULL;
	hDevVerticalTailMesh = NULL;
	hSSMEMesh[0] = NULL;
	hSSMEMesh[1] = NULL;
	hSSMEMesh[2] = NULL;

	ahHDP = NULL;
	ahTow = NULL;

	hasPORT_RMS = false;
	hasSTBD_MPM = false;

	bLastCamInternal = false;

	pl_mass = 0.0;

	bSRMsmoke = false;

	// gpc
	firstStep = true;

	// controller inputs
	THC_AltInput = _V( 0.0, 0.0, 0.0 );
	RHC_TrimUp = false;
	RHC_TrimDown = false;
	RHC_TrimLeft = false;
	RHC_TrimRight = false;

	RPTA_Input = 0.0;

	SBTCTO_Input = false;
	SBTC_Input = 0.0;

	LeftBrake_Input = 0.0;
	RightBrake_Input = 0.0;

	// controller positions
	LeftRHC[0] = 0.0;
	LeftRHC[1] = 0.0;
	LeftRHC[2] = 0.0;
	RightRHC[0] = 0.0;
	RightRHC[1] = 0.0;
	RightRHC[2] = 0.0;
	AftRHC[0] = 0.0;
	AftRHC[1] = 0.0;
	AftRHC[2] = 0.0;
	LeftRHCTrim[0] = 0;
	LeftRHCTrim[1] = 0;
	RightRHCTrim[0] = 0;
	RightRHCTrim[1] = 0;

	LeftTHC[0] = 0;
	LeftTHC[1] = 0;
	LeftTHC[2] = 0;
	AftTHC[0] = 0;
	AftTHC[1] = 0;
	AftTHC[2] = 0;

	RPTAs = 0.0;

	LeftSBTC = 1.0;// default is full forward
	RightSBTC = 1.0;// default is full forward
	LeftSBTCTO = false;
	RightSBTCTO = false;

	BrakeCDR[0] = 0.0;
	BrakeCDR[1] = 0.0;
	BrakePLT[0] = 0.0;
	BrakePLT[1] = 0.0;


	for (i = 0; i < 3; i++) {
		lastRotCommand[i] = 0;
		lastTransCommand[i] = 0;
		RotationCommand.data[i] = 0.0;
		TranslationCommand.data[i] = 0.0;
		TransForce[0].data[i] = TransForce[1].data[i] = 0.0001; //small number to avoid divide by zero
	}

	aerosurfaces.Elevator = 0.0;
	aerosurfaces.Aileron = 0.0;
	aerosurfaces.BodyFlap = 0.0;
	aerosurfaces.Speedbrake = 0.0;
	aerosurfaces.Rudder = 0.0;
	aerosurfaces.LandingGear = 0.0;
	aerosurfaces.SILTSPOD = false;

	ControlRMS = false;
	lastRMSSJCommand = 0;

	SERCstop = true;

	LO2LowLevelSensor[0] = Sensor(65, 80);
	LO2LowLevelSensor[1] = Sensor(65, 80);
	LO2LowLevelSensor[2] = Sensor(65, 80);
	LO2LowLevelSensor[3] = Sensor(65, 80);

	fTimeCameraLabel = 0.0;
	nhCameraLabel = oapiCreateAnnotation(true, 1.0, _V(1.0, 1.0, 1.0));
	oapiAnnotationSetPos(nhCameraLabel, 0.4, 0.05, 0.6, 0.15);

	SoundID = -1;

	bPLBCamPanLeft_Man = false;
	bPLBCamPanRight_Man = false;
	bPLBCamTiltUp_Man = false;
	bPLBCamTiltDown_Man = false;

	for (i = 0; i < 3; i++)
	{
		ssme_dir[i] = _V( 0.0, 0.0, 1.0 );
		ssme_gox_pos[i] = SSME_GOX_REF;
		ssme_vent_pos[i] = SSME_VENT_REF;
	}

	for (i = 0; i < 2; i++) SRBNullDirection[i] = _V(0.0, 0.0, 1.0);

	// RCS exhaust
	RCS_Exhaust_tex = oapiRegisterExhaustTexture("SSV\\Exhaust_atrcs");
	SURFHANDLE RCS_tex = oapiRegisterParticleTexture("SSV\\ps-rcs2");
	RCS_PSSpec.srcsize = 0.2;
	RCS_PSSpec.srcrate = 1000.0;
	RCS_PSSpec.v0 = 100.0;
	RCS_PSSpec.srcspread = 0.0;
	RCS_PSSpec.lifetime = 0.05;
	RCS_PSSpec.growthrate = 60.0;
	RCS_PSSpec.atmslowdown = 30.0;
	RCS_PSSpec.ltype = PARTICLESTREAMSPEC::EMISSIVE;
	RCS_PSSpec.levelmap = PARTICLESTREAMSPEC::LVL_PLIN;
	RCS_PSSpec.lmin = 0.1;
	RCS_PSSpec.lmax = 0.5;
	RCS_PSSpec.atmsmap = PARTICLESTREAMSPEC::ATM_FLAT;
	RCS_PSSpec.amin = 1.0;
	RCS_PSSpec.tex = RCS_tex;


	SSMEGH2burn[0] = NULL;
	SSMEGH2burn[1] = NULL;
	SSMEGH2burn[2] = NULL;

	hasCISS = false;

	static char *name = "CRT";
	MFDMODESPECEX spec;
	spec.name = name;
	spec.key = OAPI_KEY_T;
	spec.context = NULL;
	spec.msgproc = CRT::MsgProc;
	mfdID = RegisterMFDMode( spec );
}

// --------------------------------------------------------------
// Destructor
// --------------------------------------------------------------
Atlantis::~Atlantis()
{
	delete psubsystems;

	delete pgForward;
	delete pgLeft;
	delete pgCenter;
	delete pgRight;
	delete pgOverhead;
	delete pgOverheadAft;
	delete pgAftPort;
	delete pgAft;
	delete pgAftStbd;

	for (unsigned int i = 0; i < vpAnimations.size(); i++) delete vpAnimations.at(i);

	delete bundleManager;
	delete options;

	delete pT0UmbRef;

	delete pSimpleBus;

	ClearMissionManagementMemory();

	UnregisterMFDMode( mfdID );

	if (hOVTexture) oapiReleaseTexture( hOVTexture );
	if (hLOMSTexture) oapiReleaseTexture( hLOMSTexture );
	if (hROMSTexture) oapiReleaseTexture( hROMSTexture );
	if (hAftBulkheadTexture) oapiReleaseTexture( hAftBulkheadTexture );
}

void Atlantis::clbkSetClassCaps( FILEHANDLE cfg )
{
	try
	{
		oapiWriteLogV( "(SSV_OV) [INFO] Reading cfg file" );
		options->Parse( cfg );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkSetClassCaps" );
		abort();
	}
}

void Atlantis::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		char cbuf[256];

		// save default vessel parameters
		// set CoG to center of mesh before saving scenario; otherwise, shuttle position will change slightly when saved scenario is loaded
		ShiftCG(-currentCoG);
		VESSEL4::clbkSaveState(scn);
		ShiftCG(currentCoG); // reset CoG to correct position

		if (!pMission->GetMissionFileName().empty())
		{
			strcpy(cbuf, pMission->GetMissionFileName().c_str());
			oapiWriteScenario_string(scn, "MISSION", cbuf);
		}

		// custom parameters
		oapiWriteScenario_int(scn, "CONFIGURATION", status);
		oapiWriteScenario_int(scn, "VC_POS", VCMode);

		sprintf( cbuf, "%0.2f %0.2f", LeftSBTC, RightSBTC );
		oapiWriteScenario_string( scn, "SBTC", cbuf );

		if (pl_mass != 0.0) oapiWriteScenario_float(scn, "PAYLOAD_MASS", pl_mass);

		oapiWriteLog("(SSV_OV) [INFO] Save subsystem states...");
		psubsystems->SaveState(scn);

		oapiWriteLog("(SSV_OV) [INFO] Save panel states...");
		pgForward->OnSaveState(scn);
		pgLeft->OnSaveState(scn);
		pgCenter->OnSaveState(scn);
		pgRight->OnSaveState(scn);
		pgOverhead->OnSaveState(scn);
		pgOverheadAft->OnSaveState(scn);
		pgAftPort->OnSaveState(scn);
		pgAft->OnSaveState(scn);
		pgAftStbd->OnSaveState(scn);
		oapiWriteLog("(SSV_OV) [INFO] Saving state done.");
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkSaveState" );
		abort();
	}
	return;
}

void Atlantis::clbkLoadStateEx( FILEHANDLE scn, void* status )
{
	try
	{
		ClearMeshes();// TODO should be deleted?

		char *line;

		while (oapiReadScenario_nextline(scn, line))
		{
			if (!_strnicmp(line, "CONFIGURATION", 13))
			{
				sscanf(line + 13, "%d", &this->status);
			}
			else if (!_strnicmp(line, "VC_POS", 6))
			{
				sscanf(line + 6, "%d", &scnVCMode);
			}
			else if (!_strnicmp(line, "MISSION", 7))
			{
				char pszBuffer[256];
				strncpy(pszBuffer, line + 8, 255);

				oapiWriteLogV( "(SSV_OV) [INFO] Loading mission %s", pszBuffer );

				// load vehicle config
				pMission = ssvGetMission(pszBuffer);

				hasPORT_RMS = pMission->HasRMS();
				hasSTBD_MPM = pMission->HasPLMPM();
				hasCISS = pMission->UseCISS();

				// create subsystems and panels for loaded vehicle config
				CreateSubsystems();
				CreatePanels();

				// connect MDUs to IDPs
				mdus[vc::MDUID_CDR1]->SetPrimaryIDP( pIDP[2] );
				mdus[vc::MDUID_CDR1]->SetSecondaryIDP( pIDP[0] );
				mdus[vc::MDUID_CDR2]->SetPrimaryIDP( pIDP[0] );
				mdus[vc::MDUID_CDR2]->SetSecondaryIDP( pIDP[1] );
				mdus[vc::MDUID_CRT1]->SetPrimaryIDP( pIDP[0] );
				mdus[vc::MDUID_CRT2]->SetPrimaryIDP( pIDP[1] );
				mdus[vc::MDUID_CRT3]->SetPrimaryIDP( pIDP[2] );
				mdus[vc::MDUID_CRT4]->SetPrimaryIDP( pIDP[3] );
				mdus[vc::MDUID_MFD1]->SetPrimaryIDP( pIDP[1] );
				mdus[vc::MDUID_MFD1]->SetSecondaryIDP( pIDP[2] );
				mdus[vc::MDUID_MFD2]->SetPrimaryIDP( pIDP[0] );
				mdus[vc::MDUID_MFD2]->SetSecondaryIDP( pIDP[2] );
				mdus[vc::MDUID_PLT1]->SetPrimaryIDP( pIDP[1] );
				mdus[vc::MDUID_PLT1]->SetSecondaryIDP( pIDP[0] );
				mdus[vc::MDUID_PLT2]->SetPrimaryIDP( pIDP[2] );
				mdus[vc::MDUID_PLT2]->SetSecondaryIDP( pIDP[1] );
				mdus[vc::MDUID_AFD1]->SetPrimaryIDP( pIDP[3] );
				mdus[vc::MDUID_AFD1]->SetSecondaryIDP( pIDP[1] );

				pSimpleGPC->LoadILOADs( pMission->GetILOADs() );
				pMission->ClearILOADs();

				aerosurfaces.SILTSPOD = pMission->UseSILTS();
			}
			else if (!_strnicmp( line, "SBTC", 4 ))
			{
				double left = 0.0;
				double right = 0.0;
				sscanf( line + 4, "%lf %lf", &left, &right );
				if ((left >= 0.0) && (left <= 1.0)) LeftSBTC = left;
				if ((right >= 0.0) && (right <= 1.0)) RightSBTC = right;
			}
			else if (!_strnicmp(line, "PAYLOAD_MASS", 12))
			{
				sscanf(line + 12, "%lf", &pl_mass);
			}
			else if (!_strnicmp(line, "@PANEL", 6))
			{
				char pszPanelName[30];
				sscanf_s(line + 6, "%s", pszPanelName, sizeof(pszPanelName));
				oapiWriteLogV( "Look up panel \"%s\"... \t\t(%s)", pszPanelName, line );

				if (!pgForward->ParsePanelBlock( pszPanelName, scn ))
				if (!pgLeft->ParsePanelBlock( pszPanelName, scn ))
				if (!pgCenter->ParsePanelBlock( pszPanelName, scn ))
				if (!pgRight->ParsePanelBlock( pszPanelName, scn ))
				if (!pgOverhead->ParsePanelBlock( pszPanelName, scn ))
				if (!pgOverheadAft->ParsePanelBlock( pszPanelName, scn ))
				if (!pgAftPort->ParsePanelBlock( pszPanelName, scn ))
				if (!pgAft->ParsePanelBlock( pszPanelName, scn ))
				if (!pgAftStbd->ParsePanelBlock( pszPanelName, scn ))
					oapiWriteLogV( "(SSV_OV) [ERROR] Panel %s does not exist", pszPanelName );

				oapiWriteLog("\tLeave @PANEL block.");
			}
			else
			{
				if (psubsystems->ParseScenarioLine(scn, line)) continue; // offer line to subsystem simulation
				ParseScenarioLineEx(line, status);// unrecognised option - pass to Orbiter's generic parser
			}
		}

		switch (this->status)
		{
		case 0:
			SetLaunchConfiguration();
			break;
		case 1:
			SetPostLaunchConfiguration();
			break;
		case 2:
			SetOrbiterTankConfiguration();
			break;
		case 3:
			SetOrbiterConfiguration();
			break;
		}
		if (this->status >= STATE_STAGE1) pMTU->StartMET(); // make sure timer is running
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkLoadStateEx" );
		abort();
	}
	return;
}

void Atlantis::clbkSetStateEx( const void* status )
{
	try
	{
		// default parameter initialisation
		DefSetStateEx(status);

		oapiWriteLog("(SSV_OV) [INFO] Set Orbiter configuration.");
		// reset vessel-specific parameters to defaults
		SetOrbiterConfiguration();
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkSetStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkSetStateEx" );
		abort();
	}
}

void Atlantis::clbkPostCreation( void )
{
	try
	{
		oapiWriteLog( "(SSV_OV) [INFO] In clbkPostCreation" );

		// correct SRB parameters
		if (status <= STATE_STAGE1)
		{
			SRB* pSRB = GetSRBInterface( LEFT );
			if (pSRB)
			{
				// use correct values
				if (ph_srb) SetPropellantMaxMass( ph_srb, pSRB->SRB_MAX_PROPELLANT_MASS * 2.0 );
				SetThrusterMax0( th_srb[0], pSRB->SRB_THRUST );
				SetThrusterIsp( th_srb[0], pSRB->SRB_ISP0, pSRB->SRB_ISP1 );
				SetThrusterMax0( th_srb[1], pSRB->SRB_THRUST );
				SetThrusterIsp( th_srb[1], pSRB->SRB_ISP0, pSRB->SRB_ISP1 );
			}
		}

		pT0UmbRef->Connect();

		SoundID = ConnectToOrbiterSoundDLL(GetHandle());
		if (SoundID != -1)
		{
			//NOTE: (char*) casts in OrbiterSound calls should be safe; I think function just stores the file names (SiameseCat)
			SetMyDefaultWaveDirectory( const_cast<char*>(SOUND_DIRECTORY) );

			ReplaceStockSound( SoundID, const_cast<char*>(AIR_CONDITIONING_SOUND_FILE), REPLACE_AIR_CONDITIONNING );

			SoundOptionOnOff( SoundID, PLAYCOUNTDOWNWHENTAKEOFF, FALSE );
			SoundOptionOnOff( SoundID, PLAYGPWS, FALSE );
			SoundOptionOnOff( SoundID, PLAYMAINTHRUST, FALSE );
			SoundOptionOnOff( SoundID, PLAYHOVERTHRUST, FALSE );
			SoundOptionOnOff( SoundID, PLAYATTITUDETHRUST, FALSE );
			SoundOptionOnOff( SoundID, PLAYDOCKINGSOUND, FALSE );
			SoundOptionOnOff( SoundID, PLAYRADARBIP, FALSE );
			SoundOptionOnOff( SoundID, PLAYDOCKLANDCLEARANCE, FALSE );
			SoundOptionOnOff( SoundID, PLAYRADIOATC, FALSE );
			SoundOptionOnOff( SoundID, DISPLAYTIMER, FALSE );
			SoundOptionOnOff( SoundID, DISABLEAUTOPILOTWHENTIMEWARP, FALSE );
			SoundOptionOnOff( SoundID, PLAYRETROTHRUST, FALSE );
			SoundOptionOnOff( SoundID, PLAYUSERTHRUST, FALSE );

			// RCS sounds
			RequestLoadVesselWave( SoundID, PRCS_SOUND, const_cast<char*>(PRCS_SOUND_FILE), INTERNAL_ONLY );
			RequestLoadVesselWave( SoundID, VRCS_SOUND, const_cast<char*>(VRCS_SOUND_FILE), INTERNAL_ONLY );

			// SSME sounds
			RequestLoadVesselWave( SoundID, SSME_START, const_cast<char*>(SSME_START_FILE), EXTERNAL_ONLY_FADED_FAR );
			RequestLoadVesselWave( SoundID, SSME_RUNNING, const_cast<char*>(SSME_RUNNING_FILE), EXTERNAL_ONLY_FADED_FAR );
			RequestLoadVesselWave( SoundID, SSME_SHUTDOWN, const_cast<char*>(SSME_SHUTDOWN_FILE), EXTERNAL_ONLY_FADED_FAR );

			// APU sounds
			RequestLoadVesselWave( SoundID, APU_1_START, const_cast<char*>(APU_START_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_2_START, const_cast<char*>(APU_START_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_3_START, const_cast<char*>(APU_START_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_1_RUNNING, const_cast<char*>(APU_RUNNING_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_2_RUNNING, const_cast<char*>(APU_RUNNING_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_3_RUNNING, const_cast<char*>(APU_RUNNING_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_1_SHUTDOWN, const_cast<char*>(APU_SHUTDOWN_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_2_SHUTDOWN, const_cast<char*>(APU_SHUTDOWN_FILE), EXTERNAL_ONLY_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, APU_3_SHUTDOWN, const_cast<char*>(APU_SHUTDOWN_FILE), EXTERNAL_ONLY_FADED_MEDIUM );

			// vc sounds
			RequestLoadVesselWave( SoundID, SWITCH_GUARD_SOUND, const_cast<char*>(SWITCH_GUARD_FILE), INTERNAL_ONLY );
			RequestLoadVesselWave( SoundID, SWITCH_THROW_SOUND, const_cast<char*>(SWITCH_THROW_FILE), INTERNAL_ONLY );
			RequestLoadVesselWave( SoundID, KEY_PRESS_SOUND, const_cast<char*>(KEY_PRESS_FILE), INTERNAL_ONLY );

			RequestLoadVesselWave( SoundID, TB_OFF_SOUND, const_cast<char*>(TB_OFF_FILE), INTERNAL_ONLY );
			RequestLoadVesselWave( SoundID, TB_ON_SOUND, const_cast<char*>(TB_ON_FILE), INTERNAL_ONLY );

			RequestLoadVesselWave( SoundID, CW_TONE_SOUND, const_cast<char*>(CW_TONE_FILE), BOTHVIEW_FADED_MEDIUM );// play outside as it is "critical"
			RequestLoadVesselWave( SoundID, CW_TONE_RMS_SOUND, const_cast<char*>(CW_TONE_FILE), BOTHVIEW_FADED_MEDIUM );

			RequestLoadVesselWave( SoundID, CB_SOUND, const_cast<char*>(CB_FILE), INTERNAL_ONLY );
			RequestLoadVesselWave( SoundID, ROTATION_SWITCH_SOUND, const_cast<char*>(ROTATION_SWITCH_FILE), INTERNAL_ONLY );
		}
		else oapiWriteLogV( "(SSV_OV) [INFO] No sound available" );

		CreateLights();

		psubsystems->RealizeAll();
		pgForward->Realize();
		pgLeft->Realize();
		pgCenter->Realize();
		pgRight->Realize();
		pgOverhead->Realize();
		pgOverheadAft->Realize();
		pgAftPort->Realize();
		pgAft->Realize();
		pgAftStbd->Realize();

		RealizeSubsystemConnections();

#if _DEBUG
		pgForward->LogPanels("Forward");
		pgLeft->LogPanels("Left");
		pgCenter->LogPanels("Center");
		pgRight->LogPanels("Right");
		pgOverhead->LogPanels("Overhead");
		pgOverheadAft->LogPanels("Aft Overhead");
		pgAftPort->LogPanels("Aft Port");
		pgAft->LogPanels("Aft");
		pgAftStbd->LogPanels("Aft Starboard");
#endif// _DEBUG
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkPostCreation" );
		abort();
	}
}

void Atlantis::clbkFocusChanged( bool getfocus, OBJHANDLE hNewVessel, OBJHANDLE hOldVessel )
{
	try
	{
		if (getfocus) {
			oapiDisableMFDMode(MFD_LANDING);
			// no VTOL MFD mode for Atlantis
			//Enable communication overlays
		}
		else
		{
			//Disable all Communication overlays
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkFocusChanged: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkFocusChanged" );
		abort();
	}
}

void Atlantis::clbkPreStep( double simt, double simdt, double mjd )
{
	static bool ___PreStep_flag = false;

	try
	{
		if (firstStep) {
			UpdateMassAndCoG();// update visual before simulation starts

			if (status == STATE_PRELAUNCH)
			{
				// update touchdown points to match height of attachment to pad
				// otherwise, stack will either fall through pad or bounce upwards at T-0
				OBJHANDLE hPad = GetAttachmentStatus(ahHDP);
				if (hPad) {
					VESSEL* v = oapiGetVesselInterface(hPad);
					DWORD count = v->AttachmentCount(false);
					//ATTACHMENTHANDLE ahParent = NULL;
					VECTOR3 parentAttachPos, dir, rot;
					for (DWORD i = 0; i < count; i++) {
						ATTACHMENTHANDLE ah = v->GetAttachmentHandle(false, i);
						if (v->GetAttachmentStatus(ah) == GetHandle()) {
							v->GetAttachmentParams(ah, parentAttachPos, dir, rot);
							break;
						}
					}
					VECTOR3 pt1, pt2, pt3;
					v->GetTouchdownPoints(pt1, pt2, pt3);
					// assume y-axis of pad is in vertical direction and pt1.y==pt2.y==pt3.y
					VECTOR3 pos = POS_HDP - currentCoG;
					double touchdownZ = pt1.y - parentAttachPos.y + pos.z;
					DWORD ntdvtx = 4;
					static TOUCHDOWNVTX tdvtx[4] = {
						{_V( 0, -10, touchdownZ ), 1e5, 1e2, 0.5, 0.005},
						{_V( -7, 7, touchdownZ ), 1e5, 1e2, 0.5, 0.005},
						{_V( 7, 7, touchdownZ ), 1e5, 1e2, 0.5, 0.005},
						{_V( 0, 0, 20 ), 1e5, 1e2, 0.5}
					};
					SetTouchdownPoints( tdvtx, ntdvtx );
				}
			}
		}

		if (!___PreStep_flag)
		{
			oapiWriteLog("(SSV_OV) [INFO] In clbkPreStep");
			___PreStep_flag = true;
		}

		// update MET; needs to be done as early as possible, before subsytem PreStep functions are called
		if (status == STATE_PRELAUNCH) {
			met = 0.0;
		}
		else {
			// calculate MET (in seconds) from MTU
			met = pMTU->GetMETDay(0)*86400.0 + pMTU->GetMETHour(0)*3600.0 + pMTU->GetMETMin(0)*60.0 + pMTU->GetMETSec(0) + pMTU->GetMETMilli(0) / 1000.0;
		}

		UpdateControllers( simdt );

		//Stopwatch st, stSub;
		//st.Start();

		//stSub.Start();
		psubsystems->PreStep( simt, simdt, mjd );
		pgForward->OnPreStep( simt, simdt, mjd );
		pgLeft->OnPreStep( simt, simdt, mjd );
		pgCenter->OnPreStep( simt, simdt, mjd );
		pgRight->OnPreStep( simt, simdt, mjd );
		pgOverhead->OnPreStep( simt, simdt, mjd );
		pgOverheadAft->OnPreStep( simt, simdt, mjd );
		pgAftPort->OnPreStep( simt, simdt, mjd );
		pgAft->OnPreStep( simt, simdt, mjd );
		pgAftStbd->OnPreStep( simt, simdt, mjd );
		//double subTime = stSub.Stop();

		// disable all Orbitersim autopilots
		for (int i = NAVMODE_KILLROT; i <= NAVMODE_HOLDALT; i++) DeactivateNavmode(i);


		// check inputs from GPC and set thrusters
		//PITCH Commands to Thrusters
		double pitchcmd = RotThrusterCommands[PITCH].GetVoltage();
		if (pitchcmd > 0.0001)
		{
			SetThrusterGroupLevel(thg_pitchup, pitchcmd);
			SetThrusterGroupLevel(thg_pitchdown, 0.0);

			if (lastRotCommand[PITCH] != 1) {
				lastRotCommand[PITCH] = 1;
				if ((pitchcmd * oapiGetTimeAcceleration()) > 0.101) PlayVesselWave( SoundID, PRCS_SOUND );
				else PlayVesselWave( SoundID, VRCS_SOUND );
			}
		}
		else if (pitchcmd < -0.0001)
		{
			SetThrusterGroupLevel(thg_pitchdown, -pitchcmd);
			SetThrusterGroupLevel(thg_pitchup, 0.0);

			if (lastRotCommand[PITCH] != -1) {
				lastRotCommand[PITCH] = -1;
				if ((pitchcmd * oapiGetTimeAcceleration()) < -0.101) PlayVesselWave( SoundID, PRCS_SOUND );
				else PlayVesselWave( SoundID, VRCS_SOUND );
			}
		}
		else
		{
			SetThrusterGroupLevel(thg_pitchup, 0.0);
			SetThrusterGroupLevel(thg_pitchdown, 0.0);
			lastRotCommand[PITCH] = 0;

		}


		//YAW Commands to thrusters
		if (RotThrusterCommands[YAW].GetVoltage() > 0.0001) {
			SetThrusterGroupLevel(thg_yawright, RotThrusterCommands[YAW].GetVoltage());
			SetThrusterGroupLevel(thg_yawleft, 0.0);

			if (lastRotCommand[YAW] != 1) {
				lastRotCommand[YAW] = 1;
				if ((RotThrusterCommands[YAW].GetVoltage() * oapiGetTimeAcceleration()) > 0.101) PlayVesselWave( SoundID, PRCS_SOUND );
				else PlayVesselWave( SoundID, VRCS_SOUND );
			}
		}
		else if (RotThrusterCommands[YAW].GetVoltage() < -0.0001) {
			SetThrusterGroupLevel(thg_yawleft, -RotThrusterCommands[YAW].GetVoltage());
			SetThrusterGroupLevel(thg_yawright, 0.0);

			if (lastRotCommand[YAW] != -1) {
				lastRotCommand[YAW] = -1;
				if ((RotThrusterCommands[YAW].GetVoltage() * oapiGetTimeAcceleration()) < -0.101) PlayVesselWave( SoundID, PRCS_SOUND );
				else PlayVesselWave( SoundID, VRCS_SOUND );
			}
		}
		else {
			SetThrusterGroupLevel(thg_yawright, 0.0);
			SetThrusterGroupLevel(thg_yawleft, 0.0);
			lastRotCommand[YAW] = 0;
		}

		//ROLL Commands to Thruster
		if (RotThrusterCommands[ROLL].GetVoltage() > 0.0001) {
			SetThrusterGroupLevel(thg_rollright, RotThrusterCommands[ROLL].GetVoltage());
			SetThrusterGroupLevel(thg_rollleft, 0.0);

			if (lastRotCommand[ROLL] != 1) {
				lastRotCommand[ROLL] = 1;
				if ((RotThrusterCommands[ROLL].GetVoltage() * oapiGetTimeAcceleration()) > 0.101) PlayVesselWave( SoundID, PRCS_SOUND );
				else PlayVesselWave( SoundID, VRCS_SOUND );
			}
		}
		else if (RotThrusterCommands[ROLL].GetVoltage() < -0.0001) {
			SetThrusterGroupLevel(thg_rollleft, -RotThrusterCommands[ROLL].GetVoltage());
			SetThrusterGroupLevel(thg_rollright, 0.0);

			if (lastRotCommand[ROLL] != -1) {
				lastRotCommand[ROLL] = -1;
				if ((RotThrusterCommands[ROLL].GetVoltage() * oapiGetTimeAcceleration()) < -0.101) PlayVesselWave( SoundID, PRCS_SOUND );
				else PlayVesselWave( SoundID, VRCS_SOUND );
			}
		}
		else {
			SetThrusterGroupLevel(thg_rollright, 0.0);
			SetThrusterGroupLevel(thg_rollleft, 0.0);
			lastRotCommand[ROLL] = 0;
		}

		// SERC
		if (RotThrusterCommands[3].GetVoltage() > 0.0001)
		{
			// roll left
			SetThrusterLevel(th_att_rcs[12], RotThrusterCommands[3].GetVoltage());// L1U, L2U, L4U
			SetThrusterLevel(th_att_rcs[13], RotThrusterCommands[3].GetVoltage());// R2D, R3D, R4D
			SetThrusterLevel(th_att_rcs[7], RotThrusterCommands[3].GetVoltage());// F2R, F4R
			SetThrusterLevel(th_att_rcs[10], RotThrusterCommands[3].GetVoltage());// R1R, R2R, R3R, R4R

			SetThrusterLevel(th_att_rcs[16], 0);// R1U, R2U, R4U
			SetThrusterLevel(th_att_rcs[15], 0);// L2D, L3D, L4D
			SetThrusterLevel(th_att_rcs[9], 0);// F1L, F3L
			SetThrusterLevel(th_att_rcs[8], 0);// L1L, L2L, L3L, L4L

			SERCstop = false;
		}
		else if (RotThrusterCommands[3].GetVoltage() < -0.0001)
		{
			// roll right
			SetThrusterLevel(th_att_rcs[12], 0);// L1U, L2U, L4U
			SetThrusterLevel(th_att_rcs[13], 0);// R2D, R3D, R4D
			SetThrusterLevel(th_att_rcs[7], 0);// F2R, F4R
			SetThrusterLevel(th_att_rcs[10], 0);// R1R, R2R, R3R, R4R

			SetThrusterLevel(th_att_rcs[16], -RotThrusterCommands[3].GetVoltage());// R1U, R2U, R4U
			SetThrusterLevel(th_att_rcs[15], -RotThrusterCommands[3].GetVoltage());// L2D, L3D, L4D
			SetThrusterLevel(th_att_rcs[9], -RotThrusterCommands[3].GetVoltage());// F1L, F3L
			SetThrusterLevel(th_att_rcs[8], -RotThrusterCommands[3].GetVoltage());// L1L, L2L, L3L, L4L

			SERCstop = false;
		}
		else
		{
			if (SERCstop == false)
			{
				SetThrusterLevel(th_att_rcs[12], 0);// L1U, L2U, L4U
				SetThrusterLevel(th_att_rcs[13], 0);// R2D, R3D, R4D
				SetThrusterLevel(th_att_rcs[7], 0);// F2R, F4R
				SetThrusterLevel(th_att_rcs[10], 0);// R1R, R2R, R3R, R4R

				SetThrusterLevel(th_att_rcs[16], 0);// R1U, R2U, R4U
				SetThrusterLevel(th_att_rcs[15], 0);// L2D, L3D, L4D
				SetThrusterLevel(th_att_rcs[9], 0);// F1L, F3L
				SetThrusterLevel(th_att_rcs[8], 0);// L1L, L2L, L3L, L4L

				SERCstop = true;
			}
		}


		if (TransThrusterCommands[0].GetVoltage() > 0.0001) {
			SetThrusterGroupLevel(thg_transfwd, 1.0);
			SetThrusterGroupLevel(thg_transaft, 0.0);

			if (lastTransCommand[0] != 1) {
				lastTransCommand[0] = 1;
				PlayVesselWave(SoundID, PRCS_SOUND);
			}
		}
		else if (TransThrusterCommands[0].GetVoltage() < -0.0001) {
			SetThrusterGroupLevel(thg_transaft, 1.0);
			SetThrusterGroupLevel(thg_transfwd, 0.0);

			if (lastTransCommand[0] != -1) {
				lastTransCommand[0] = -1;
				PlayVesselWave(SoundID, PRCS_SOUND);
			}
		}
		else {
			SetThrusterGroupLevel(thg_transfwd, 0.0);
			SetThrusterGroupLevel(thg_transaft, 0.0);
			lastTransCommand[0] = 0;
		}
		if (TransThrusterCommands[1].GetVoltage() > 0.0001) {
			SetThrusterGroupLevel(thg_transright, 1.0);
			SetThrusterGroupLevel(thg_transleft, 0.0);

			if (lastTransCommand[1] != 1) {
				lastTransCommand[1] = 1;
				PlayVesselWave(SoundID, PRCS_SOUND);
			}
		}
		else if (TransThrusterCommands[1].GetVoltage() < -0.0001) {
			SetThrusterGroupLevel(thg_transleft, 1.0);
			SetThrusterGroupLevel(thg_transright, 0.0);

			if (lastTransCommand[1] != -1) {
				lastTransCommand[1] = -1;
				PlayVesselWave(SoundID, PRCS_SOUND);
			}
		}
		else {
			SetThrusterGroupLevel(thg_transright, 0.0);
			SetThrusterGroupLevel(thg_transleft, 0.0);
			lastTransCommand[1] = 0;
		}
		if (TransThrusterCommands[2].GetVoltage() > 0.0001) {
			SetThrusterGroupLevel(thg_transdown, 1.0);
			SetThrusterGroupLevel(thg_transup, 0.0);

			if (lastTransCommand[2] != 1) {
				lastTransCommand[2] = 1;
				PlayVesselWave(SoundID, PRCS_SOUND);
			}
		}
		else if (TransThrusterCommands[2].GetVoltage() < -0.0001) {
			SetThrusterGroupLevel(thg_transup, 1.0);
			SetThrusterGroupLevel(thg_transdown, 0.0);

			if (lastTransCommand[2] != -1) {
				lastTransCommand[2] = -1;
				PlayVesselWave(SoundID, PRCS_SOUND);
			}
		}
		else {
			SetThrusterGroupLevel(thg_transdown, 0.0);
			SetThrusterGroupLevel(thg_transup, 0.0);
			lastTransCommand[2] = 0;
		}

		// if we reenter PLB cam view from external view, update camera direction
		if (!bLastCamInternal && oapiCameraInternal()) {
			if (VCMode >= VC_PLBCAMA && VCMode <= VC_RMSCAM) pPayloadBay->SetAnimationCameras();
		}
		bLastCamInternal = oapiCameraInternal();

		// during launch, turn engine light source on
		if (status <= STATE_STAGE2 && GetSSMEThrustLevel(0) > 1.0) {
			SSMELight->Activate(true);
			SSMELight->SetIntensity(GetSSMEThrustLevel(0) / SSME_MAX_POWER_LEVEL);
		}
		else {
			SSMELight->Activate(false);
		}
		if (status == STATE_STAGE1) {
			SRBLight[0]->Activate(true);
			SRBLight[1]->Activate(true);
		}
		else {
			SRBLight[0]->Activate(false);
			SRBLight[1]->Activate(false);
		}

		//double time=st.Stop();
		//sprintf_s(oapiDebugString(), 256, "PreStep time: %f Subsystem time: %f", time, subTime);
		//oapiWriteLog(oapiDebugString());

		if (status > STATE_PRELAUNCH) UpdateMassAndCoG(); // TODO: refine

	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkPreStep" );
		abort();
	}
}

void Atlantis::clbkPostStep( double simt, double simdt, double mjd )
{
	static bool ___PostStep_flag = false;

	try
	{
		//Stopwatch st, stSub;
		//st.Start();

		if (!___PostStep_flag)
		{
			oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkPostStep) Entering.");
		}

		if (firstStep) {
			firstStep = false;
			UpdateMassAndCoG(true);
		}

		if (!___PostStep_flag)
		{
			oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkPostStep) Processing subsystems.");
		}
		//stSub.Start();
		psubsystems->PostStep(simt, simdt, mjd);
		//double subTime = stSub.Stop();

		if (!___PostStep_flag)
		{
			oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkPostStep) Processing panels.");
		}

		//Panel groups
		pgForward->OnPostStep(simt, simdt, mjd);
		pgLeft->OnPostStep(simt, simdt, mjd);
		pgCenter->OnPostStep(simt, simdt, mjd);
		pgRight->OnPostStep(simt, simdt, mjd);
		pgOverhead->OnPostStep(simt, simdt, mjd);
		pgOverheadAft->OnPostStep(simt, simdt, mjd);
		pgAftPort->OnPostStep(simt, simdt, mjd);
		pgAft->OnPostStep(simt, simdt, mjd);
		pgAftStbd->OnPostStep(simt, simdt, mjd);
		//stSub.Stop();


		if (!___PostStep_flag)
		{
			oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkPostStep) Executing state depending behavior.");
		}

		switch (status) {
		case STATE_PRELAUNCH: // launch configuration
			// check SSME state and trigger liftoff when required
			if (Eq(GetSSMEThrustLevel(0), 0.0, 0.0001))
			{
				if (GetPropellantLevel(ph_mps) > 0.5)
				{
					for (unsigned short i = 0; i < 3; i++)
					{
						if (th_ssme_gox[i] != NULL) {
							SetThrusterLevel(th_ssme_gox[i], 1.0);
						}
					}
				}
				else
				{
					for (unsigned short i = 0; i < 3; i++)
					{
						if (th_ssme_gox[i] != NULL) {
							SetThrusterLevel(th_ssme_gox[i], 0.0);
						}
					}
				}
			}
			else
			{
				if (simTtwang == -1.0)
				{
					simTtwang = simt;
					PlayVesselWave( SoundID, SSME_START, NOLOOP );
				}

				// play sounds
				if (pRSLS->GetLaunchSequenceAbortFlag())
				{
					// handle pad abort
					if (IsPlaying( SoundID, SSME_RUNNING )) PlayVesselWave( SoundID, SSME_SHUTDOWN, NOLOOP );
					StopVesselWave( SoundID, SSME_RUNNING );
				}
				else if (!IsPlaying( SoundID, SSME_START )) PlayVesselWave( SoundID, SSME_RUNNING, LOOP );

				for (unsigned short i = 0; i < 3; i++)
				{
					if (th_ssme_gox[i] != NULL) {
						SetThrusterLevel(th_ssme_gox[i], 0.0);
					}
				}

				Twang( simt - simTtwang );
			}
			break;
		case STATE_STAGE1: // SRB's ignited
			// extract current thrust level and propellant level as a function of time
			double thrust_level, prop_level;
			GetSRBInterface( LEFT )->GetSRB_State( met, thrust_level, prop_level, SRBpc );
			for (unsigned short i = 0; i < 2; i++) {
				SetThrusterLevel(th_srb[i], thrust_level);
				SetPropellantMass(ph_srb, prop_level*GetPropellantMaxMass(ph_srb));
			}

			if ((!bSRMsmoke) && (met > 3.5))// add SRM smoke after rising a bit above ground to avoid "particle stream explosion"
			{
				AddSRBExhaust( true );
				bSRMsmoke = true;
			}

			if (met > 15.0)
			{
				slag1 = pow(1.0 - thrust_level, 3);
				slag2 = pow(1.0 - thrust_level, 2);
				slag3 = 1.0 - thrust_level;
			}
			break;
		case STATE_STAGE2: // post SRB separation
			break;
		case STATE_ORBITER: // post tank separation
			// deploy gear
			if (GetAltitude( ALTMODE_GROUND ) < 92.44) ManLandingGearDown();
			else if (GetAltitude( ALTMODE_GROUND ) < 609.6) ManLandingGearArm();

			break;
		}

		// ----------------------------------------------------------
		// Animate payload bay cameras.
		// ----------------------------------------------------------
		if (VCMode >= VC_PLBCAMA && VCMode <= VC_RMSCAM) {
			if (bPLBCamPanLeft_Man) {
				PLBCamPanLeft_Man.SetLine();
				PLBCamPanRight_Man.ResetLine();
			}
			else if (bPLBCamPanRight_Man) {
				PLBCamPanLeft_Man.ResetLine();
				PLBCamPanRight_Man.SetLine();
			}
			else {
				PLBCamPanLeft_Man.ResetLine();
				PLBCamPanRight_Man.ResetLine();
			}

			if (bPLBCamTiltUp_Man) {
				PLBCamTiltUp_Man.SetLine();
				PLBCamTiltDown_Man.ResetLine();
			}
			else if (bPLBCamTiltDown_Man) {
				PLBCamTiltUp_Man.ResetLine();
				PLBCamTiltDown_Man.SetLine();
			}
			else {
				PLBCamTiltUp_Man.ResetLine();
				PLBCamTiltDown_Man.ResetLine();
			}
		}

		// ----------------------------------------------------------
		// VC position label display
		// ----------------------------------------------------------
		if (fTimeCameraLabel > 0)
		{
			fTimeCameraLabel -= simdt;
			if (fTimeCameraLabel < 0)
				fTimeCameraLabel = 0;
			if (0 == fTimeCameraLabel)
			{
				oapiAnnotationSetText(nhCameraLabel, NULL);
			}
		}

		//double time=st.Stop();
		//sprintf_s(oapiDebugString(), 256, "PostStep time: %f", time);
		//oapiWriteLog(oapiDebugString());


		// Calculations used to modulate the alpha level (AKA visibility) of the entry plasma mesh
		{
			double dens = GetAtmDensity();
			double speed = GetAirspeed();
			double flux = (dens * pow( speed, 4 )) / 1e11;
			double heating_factor = flux - 0.5;
			double heating_scalar = range( 0, heating_factor, 1 );
			//sprintf( oapiDebugString(), "%f %f", flux, heating_scalar );
		}

		//double time = st.Stop();
		//sprintf_s(oapiDebugString(), 256, "PostStep time: %f Subsystem time: %f", time, subTime);
		//sprintf(oapiDebugString(),"Heating scalar %lf",heating_scalar);

		if (!___PostStep_flag)
		{
			oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkPostStep) Leaving.");
			___PostStep_flag = true;
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkPostStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkPostStep" );
		abort();
	}
}

bool Atlantis::clbkPlaybackEvent( double simt, double event_t, const char* event_type, const char* event )
{
	/*if (!_stricmp(event_type, "STATUS")) {
		if (!_stricmp(event, "SRB_IGNITION")) {
			status = 1;
			return true;
		}
	}/* else if (!_stricmp (event_type, "CARGODOOR")) {
	  plop->SetDoorAction (!_stricmp (event, "CLOSE") ? AnimState::CLOSING : AnimState::OPENING);
	  return true;
	  } else if (!_stricmp(event_type, "GEAR")) {
		if (!_stricmp(event, "UP")) DeployLandingGear();
		else RetractLandingGear();
		return true;
	}
	  else if (!_stricmp(event_type, "SPEEDBRAKE")) {
		  OperateSpeedbrake(!_stricmp(event, "CLOSE") ? AnimState::CLOSING : AnimState::OPENING);
		  return true;
	  } else if (!_stricmp (event_type, "KUBAND")) {
		plop->SetKuAntennaAction (!_stricmp (event, "CLOSE") ? AnimState::CLOSING : AnimState::OPENING);
		return true;
		} else if (psubsystems->PlaybackEvent(simt, event_t, event_type, event)) {
		  return true;
	  }*/

	  return false;
}

void Atlantis::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkVisualCreated) Entered.");
		if (refcount > 1) return; // we don't support more than one visual per object
		this->vis = vis;

		// get device-specific mesh handles
		hDevOrbiterMesh = GetDevMesh( vis, mesh_orbiter );
		hDevOrbiterVCExternalMesh = GetDevMesh( vis, mesh_vcexternal );
		hDevVerticalTailMesh = GetDevMesh( vis, mesh_verticaltail );
		oapiWriteLog("(SSV_OV) [INFO] GETTING DEVMESH");

		// set surfaces as CTVM textures
		if (pD3D9)
		{
			oapiWriteLog( "(SSV_OV) [INFO] Setting CTVM surfaces" );
			DEVMESHHANDLE hDevMeshpanelA3 = GetDevMesh( vis, panelA3->GetVCMeshIndex() );
			oapiSetTexture( hDevMeshpanelA3, 2, pVCU->GetMonitorSurf( 0 ) );
			oapiSetTexture( hDevMeshpanelA3, 3, pVCU->GetMonitorSurf( 1 ) );
		}

		if (pRMS) pRMS->UpdateAttachment();
		if (pPLMPM) pPLMPM->UpdateAttachment();
		if (pASE_IUS) pASE_IUS->UpdateAttachment();
		if (pCISS) pCISS->UpdateAttachment();

		// update default textures
		if (!pMission->GetOrbiterTextureName().empty()) UpdateOrbiterTexture( pMission->GetOrbiterTextureName() );
		if (!pMission->GetLOMSPodTextureName().empty()) UpdateLOMSPodTexture( pMission->GetLOMSPodTextureName() );
		if (!pMission->GetROMSPodTextureName().empty()) UpdateROMSPodTexture( pMission->GetROMSPodTextureName() );
		UpdateAftBulkheadTexture( pMission->GetOrbiter() );

		// hide unused PLBD hinge fairings
		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_SETUSERFLAG;
		grpSpec.UsrFlag = 0x00000003; // hide group and shadow
		if (pMission->GetPLBDHingeFairings() == 0)
		{
			oapiEditMeshGroup( hDevOrbiterMesh, GRP_PLBD_HINGE_DOUBLE_FAIRING_AFT, &grpSpec );
			oapiEditMeshGroup( hDevOrbiterMesh, GRP_PLBD_HINGE_SINGLE_FAIRING_FWD, &grpSpec );
			oapiEditMeshGroup( hDevOrbiterMesh, GRP_PLBD_HINGE_SINGLE_FAIRING_AFT, &grpSpec );
		}
		else if (pMission->GetPLBDHingeFairings() == 1) oapiEditMeshGroup( hDevOrbiterMesh, GRP_PLBD_HINGE_SINGLE_FAIRING_FWD, &grpSpec );
		else /*if (pMission->GetPLBDHingeFairings() == 2)*/ oapiEditMeshGroup( hDevOrbiterMesh, GRP_PLBD_HINGE_DOUBLE_FAIRING_AFT, &grpSpec );

		// hide unused chin panel
		if (pMission->GetChinPanel()) oapiEditMeshGroup( hDevOrbiterMesh, GRP_CHIN_PANEL_HRSI, &grpSpec );
		else oapiEditMeshGroup( hDevOrbiterMesh, GRP_CHIN_PANEL_RCC, &grpSpec );

		// handle window seals of "The Penguin"
		if (pMission->GetOrbiter() == "Columbia")
		{
			oapiWriteLog( "(SSV_OV) [INFO] Set OV-102 windows" );
			DEVMESHHANDLE hMesh = GetDevMesh( vis, mesh_vcexternal );
			MATERIAL mat;
			oapiMeshMaterial( hMesh, MAT_PURGESEAL_VCEXT, &mat );
			mat.diffuse.r = 0.666667f;
			mat.diffuse.g = 0.160784f;
			mat.diffuse.b = 0.090196f;
			mat.ambient.r = 0.666667f;
			mat.ambient.g = 0.160784f;
			mat.ambient.b = 0.090196f;
			mat.emissive.r = 0.666667f;
			mat.emissive.g = 0.160784f;
			mat.emissive.b = 0.090196f;
			oapiSetMaterial( hMesh, MAT_PURGESEAL_VCEXT, &mat );
		}

		oapiWriteLog( "(SSV_OV) [INFO] Calling subsystems VisualCreated" );
		psubsystems->VisualCreated( vis );

		// update UVs for talkbacks and lights
		oapiWriteLog( "(SSV_OV) [INFO] Started Panels VisualCreated" );
		pgForward->VisualCreated();
		pgLeft->VisualCreated();
		pgCenter->VisualCreated();
		pgRight->VisualCreated();
		pgOverhead->VisualCreated();
		pgOverheadAft->VisualCreated();
		pgAftPort->VisualCreated();
		pgAft->VisualCreated();
		pgAftStbd->VisualCreated();
		oapiWriteLog( "(SSV_OV) [INFO] Ended Panels VisualCreated" );

		psubsystems->Animate();// for first timestep (clbkAnimate doesn't run in the first timestep: https://www.orbiter-forum.com/project.php?issueid=1353)

		oapiWriteLog("(SSV_OV) [INFO] (Atlantis::clbkVisualCreated) Leaving.");
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkVisualCreated" );
		abort();
	}
}

void Atlantis::clbkVisualDestroyed( VISHANDLE vis, int refcount )
{
	try
	{
		if (this->vis == vis) this->vis = NULL;
		hDevOrbiterMesh = NULL;
		hDevOrbiterVCExternalMesh = NULL;
		hDevVerticalTailMesh = NULL;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkVisualDestroyed: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkVisualDestroyed" );
		abort();
	}
}

void Atlantis::clbkAnimate( double simt )
{
	try
	{
		// this will only be called if at least one subsystem calls RegisterAnimation()
		psubsystems->Animate();
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkAnimate: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkAnimate" );
		abort();
	}
}

int Atlantis::clbkConsumeDirectKey( char* kstate )
{
	try
	{
		if (KEYDOWN(kstate, OAPI_KEY_COMMA))
		{
			RESETKEY(kstate, OAPI_KEY_COMMA);// prevent default processing of the key
			LeftBrake_Input = 1.0;
		}
		else LeftBrake_Input = 0.0;

		if (KEYDOWN(kstate, OAPI_KEY_PERIOD))
		{
			RESETKEY(kstate, OAPI_KEY_PERIOD);// prevent default processing of the key
			RightBrake_Input = 1.0;
		}
		else RightBrake_Input = 0.0;
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkConsumeDirectKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkConsumeDirectKey" );
		abort();
	}
}

int Atlantis::clbkConsumeBufferedKey( DWORD key, bool down, char* kstate )
{
	try
	{
		if (!down) {
			if (KEYMOD_ALT(kstate)) {
				if (VCMode >= VC_PLBCAMA && VCMode <= VC_RMSCAM) {
					switch (key) {
					case OAPI_KEY_LEFT:
						bPLBCamPanLeft_Man = false;
						return 1;
					case OAPI_KEY_RIGHT:
						bPLBCamPanRight_Man = false;
						return 1;
					case OAPI_KEY_UP:
						bPLBCamTiltUp_Man = false;
						return 1;
					case OAPI_KEY_DOWN:
						bPLBCamTiltDown_Man = false;
						return 1;
					default:
						return 0;
					}
				}
			}
			else if (KEYMOD_SHIFT(kstate))
			{
				switch (key)
				{
					case OAPI_KEY_UP:
						RHC_TrimDown = false;
						return 1;
					case OAPI_KEY_LEFT:
						RHC_TrimLeft = false;
						return 1;
					case OAPI_KEY_RIGHT:
						RHC_TrimRight = false;
						return 1;
					case OAPI_KEY_DOWN:
						RHC_TrimUp = false;
						return 1;
				}
			}
			else if (!KEYMOD_ALT(kstate) && !KEYMOD_SHIFT(kstate)) { // Ctrl or unmodified
				switch (key) {
				case OAPI_KEY_LEFT:
				case OAPI_KEY_RIGHT:
					THC_AltInput.y = 0.0;
					return 1;
				case OAPI_KEY_INSERT:
				case OAPI_KEY_DELETE:
					THC_AltInput.x = 0.0;
					return 1;
				case OAPI_KEY_UP:
				case OAPI_KEY_DOWN:
					THC_AltInput.z = 0.0;
					return 1;
				case OAPI_KEY_RETURN:
				case OAPI_KEY_BACK:
					RMSGrapple.ResetLine();
					RMSRelease.ResetLine();
					return 1;
				case OAPI_KEY_K:
				case OAPI_KEY_L:
					RPTA_Input = 0.0;
					return 1;
				case OAPI_KEY_MINUS:
					SBTCTO_Input = false;
					return 1;
				default:
					return 0;
				}
			}
		}

		if (KEYMOD_CONTROL(kstate)) {
			switch (key) {
			case OAPI_KEY_G:
				ManLandingGearArm();
				return 1;
			case OAPI_KEY_A:
				if (pRMS)
				{
					ControlRMS = !ControlRMS;
					if (ControlRMS) DisplayCameraLabel(TEXT_RMSCONTROL);
					else DisplayCameraLabel(TEXT_RCSCONTROL);
					return 1;
				}
				else return 0;
			case OAPI_KEY_O:
				if (RMSCoarseRateIn) RMSCoarseRateOut.ResetLine();
				else RMSCoarseRateOut.SetLine();
				return 1;
			case OAPI_KEY_RETURN:
				RMSGrapple.SetLine();
				RMSRelease.ResetLine();
				return 1;
			case OAPI_KEY_BACK:
				RMSGrapple.ResetLine();
				RMSRelease.SetLine();
				return 1;
#if _DEBUG
			case OAPI_KEY_2:
				oapiSetShowGrapplePoints( !oapiGetShowGrapplePoints() );
				return 1;
			case OAPI_KEY_3:
				pgForward->ToggleCoordinateDisplayMode();
				pgLeft->ToggleCoordinateDisplayMode();
				pgCenter->ToggleCoordinateDisplayMode();
				pgRight->ToggleCoordinateDisplayMode();
				pgOverhead->ToggleCoordinateDisplayMode();
				pgOverheadAft->ToggleCoordinateDisplayMode();
				pgAftPort->ToggleCoordinateDisplayMode();
				pgAft->ToggleCoordinateDisplayMode();
				pgAftStbd->ToggleCoordinateDisplayMode();
				sprintf_s(oapiDebugString(), 256, "COORDINATE DISPLAY MODE");
				return 1;
#endif// _DEBUG
			}
		}
		else if (KEYMOD_ALT(kstate)) {
			if (VCMode >= VC_PLBCAMA && VCMode <= VC_RMSCAM) {
				switch (key) {
				case OAPI_KEY_LEFT:
					bPLBCamPanLeft_Man = true;
					return 1;
				case OAPI_KEY_RIGHT:
					bPLBCamPanRight_Man = true;
					return 1;
				case OAPI_KEY_UP:
					bPLBCamTiltUp_Man = true;
					return 1;
				case OAPI_KEY_DOWN:
					bPLBCamTiltDown_Man = true;
					return 1;
				default:
					return 0;
				}
			}
		}
		else if (KEYMOD_SHIFT(kstate))
		{
			switch (key)
			{
				case OAPI_KEY_UP:
					RHC_TrimDown = true;
					return 1;
				case OAPI_KEY_LEFT:
					RHC_TrimLeft = true;
					return 1;
				case OAPI_KEY_RIGHT:
					RHC_TrimRight = true;
					return 1;
				case OAPI_KEY_DOWN:
					RHC_TrimUp = true;
					return 1;
			}
		}
		else /*if (!KEYMOD_SHIFT(kstate) && !KEYMOD_ALT(kstate))*/ { // unmodified keys
			switch (key) {
				/*case OAPI_KEY_TAB:
					pCommModeHandler->EnterCommMode();
					break;*/
			case OAPI_KEY_K:
				RPTA_Input = -1.0;
				return 1;
			case OAPI_KEY_L:
				RPTA_Input = 1.0;
				return 1;
			case OAPI_KEY_G:
				ManLandingGearDown();
				return 1;
			case OAPI_KEY_LEFT:
				THC_AltInput.y = -1.0;
				return 1;
			case OAPI_KEY_RIGHT:
				THC_AltInput.y = 1.0;
				return 1;
			case OAPI_KEY_INSERT:
				THC_AltInput.x = 1.0;
				return 1;
			case OAPI_KEY_DELETE:
				THC_AltInput.x = -1.0;
				return 1;
			case OAPI_KEY_UP:
				THC_AltInput.z = -1.0;
				return 1;
			case OAPI_KEY_DOWN:
				THC_AltInput.z = 1.0;
				return 1;
			case OAPI_KEY_MULTIPLY: // NUMPAD *
				for (int i = 0; i < 3; i++) SSMEPBAnalog[i].SetLine();
				return 0; // this key is used by Orbitersim, so make sure Orbitersim processes it as well
			case OAPI_KEY_ADD:
				SBTC_Input = -0.05;// back
				return 0;
			case OAPI_KEY_SUBTRACT:
				SBTC_Input = 0.05;// forward
				return 1;
			case OAPI_KEY_MINUS:
				SBTCTO_Input = true;
				return 1;
			}
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkConsumeBufferedKey" );
		abort();
	}
}

bool Atlantis::clbkLoadGenericCockpit( void )
{
	try
	{
		SetCameraOffset(_V(orbiter_ofs.x - 0.67, orbiter_ofs.y + 2.55, orbiter_ofs.z + 14.4));
		SetCameraDefaultDirection(_V(0, 0, 1));
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkLoadGenericCockpit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkLoadGenericCockpit" );
		abort();
	}
}

bool Atlantis::clbkLoadVC( int id )
{
	try
	{
		bool ok = false;
		bool bUpdateVC = false;

		// when loading scenario, use cockpit position loaded from scenario instead of default position
		if (firstStep) id = scnVCMode;

		// Get the VC Mode.
		VCMode = id;
		//Reset Clip Radius settings
		SetClipRadius(0.0);

		if (pRMS) {
			if (id != VC_LEECAM) pRMS->SetEECameraView(false);
			if (id != VC_RMSCAM) pRMS->SetElbowCamView(false);
		}

		switch (id)
		{
			case VC_CDR: // commander position
				DisplayCameraLabel( VC_LBL_CDR );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_CDR );
				SetCameraDefaultDirection( VC_DIR_CDR );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 100 * RAD, 75 * RAD );
				SetCameraMovement( VC_OFS_CDR_F, VC_AZ_CDR_F, VC_EL_CDR_F, VC_OFS_CDR_L, VC_AZ_CDR_L, VC_EL_CDR_L, VC_OFS_CDR_R, VC_AZ_CDR_R, VC_EL_CDR_R );

				if (bHasODS) oapiVCSetNeighbours(VC_PANELL4, VC_PLT, VC_DOCKCAM, VC_MS2);
				else oapiVCSetNeighbours(VC_PANELL4, VC_PLT, VC_PLBCAMA, VC_MS2);

				huds.hudcnt = orbiter_ofs + VC_OFFSET + VC_HUDPOS_CDR;

				pgForward->RegisterVC();
				pgLeft->RegisterVC();
				pgCenter->RegisterVC();
				pgOverhead->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_PLT: // pilot position
				DisplayCameraLabel( VC_LBL_PLT );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_PLT );
				SetCameraDefaultDirection( VC_DIR_PLT );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 100 * RAD, 75 * RAD );
				SetCameraMovement( VC_OFS_PLT_F, VC_AZ_PLT_F, VC_EL_PLT_F, VC_OFS_PLT_L, VC_AZ_PLT_L, VC_EL_PLT_L, VC_OFS_PLT_R, VC_AZ_PLT_R, VC_EL_PLT_R );

				if (bHasODS) oapiVCSetNeighbours( VC_CDR, VC_PANELR4, VC_DOCKCAM, VC_MS1 );
				else oapiVCSetNeighbours( VC_CDR, VC_PANELR4, VC_PLBCAMD, VC_MS1 );

				huds.hudcnt = orbiter_ofs + VC_OFFSET + VC_HUDPOS_PLT;

				pgForward->RegisterVC();
				pgCenter->RegisterVC();
				pgRight->RegisterVC();
				pgOverhead->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_PANELR4:
				DisplayCameraLabel( VC_LBL_PANELR4 );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_PANELR4 );
				SetCameraDefaultDirection( VC_DIR_PANELR4, VC_TILT_PANELR4 );
				SetCameraRotationRange( 30 * RAD, 30 * RAD, 20 * RAD, 40 * RAD );
				SetCameraMovement( VC_OFS_PANELR4_F, VC_AZ_PANELR4_F, VC_EL_PANELR4_F, VC_OFS_PANELR4_L, VC_AZ_PANELR4_L, VC_EL_PANELR4_L, VC_OFS_PANELR4_R, VC_AZ_PANELR4_R, VC_EL_PANELR4_R );

				if (bHasODS) oapiVCSetNeighbours( VC_PLT, VC_STBDSTATION, VC_DOCKCAM, VC_MS1 );
				else oapiVCSetNeighbours( VC_PLT, VC_STBDSTATION, VC_PLBCAMD, VC_MS1 );

				pgForward->RegisterVC();
				pgCenter->RegisterVC();
				pgRight->RegisterVC();
				pgOverhead->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_PANELL4:
				DisplayCameraLabel( VC_LBL_PANELL4 );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_PANELL4 );
				SetCameraDefaultDirection( VC_DIR_PANELL4, VC_TILT_PANELL4 );
				SetCameraRotationRange( 30 * RAD, 30 * RAD, 20 * RAD, 40 * RAD );
				SetCameraMovement( VC_OFS_PANELL4_F, VC_AZ_PANELL4_F, VC_EL_PANELL4_F, VC_OFS_PANELL4_L, VC_AZ_PANELL4_L, VC_EL_PANELL4_L, VC_OFS_PANELL4_R, VC_AZ_PANELL4_R, VC_EL_PANELL4_R );

				if (bHasODS) oapiVCSetNeighbours( VC_PORTSTATION, VC_CDR, VC_DOCKCAM, VC_MS2 );
				else oapiVCSetNeighbours( VC_PORTSTATION, VC_CDR, VC_PLBCAMD, VC_MS2 );

				pgForward->RegisterVC();
				pgLeft->RegisterVC();
				pgCenter->RegisterVC();
				pgOverhead->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_STBDSTATION:
				DisplayCameraLabel( VC_LBL_STBDSTATION );
				SetCameraOffset( VC_OFFSET + VC_POS_STBDSTATION + orbiter_ofs );
				SetCameraDefaultDirection( VC_DIR_STBDSTATION );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_STBDSTATION_F, VC_AZ_STBDSTATION_F, VC_EL_STBDSTATION_F, VC_OFS_STBDSTATION_L, VC_AZ_STBDSTATION_L, VC_EL_STBDSTATION_L, VC_OFS_STBDSTATION_R, VC_AZ_STBDSTATION_R, VC_EL_STBDSTATION_R );

				if (bHasODS) oapiVCSetNeighbours( VC_PLT, VC_AFTPILOT, VC_DOCKCAM, VC_AFTWORKSTATION );
				else oapiVCSetNeighbours( VC_PLT, VC_AFTPILOT, VC_PLBCAMD, VC_AFTWORKSTATION );

				pgOverheadAft->RegisterVC();
				pgAft->RegisterVC();
				pgAftStbd->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_LEECAM: //RMS End Effector Camera
				if (pRMS)
				{
					DisplayCameraLabel( VC_LBL_LEECAM );
					pRMS->SetEECameraView( true );
					oapiVCSetNeighbours( VC_RMSCAM, -1, -1, VC_RMSSTATION );

					ok = true;
				}
				else ok = false;
				break;
			case VC_RMSCAM:
				if (pRMS)
				{
					DisplayCameraLabel( VC_LBL_ELBOWCAM );
					pRMS->SetElbowCamView( true );
					oapiVCSetNeighbours( -1, VC_LEECAM, -1, VC_RMSSTATION );
					ok = true;
				}
				else ok = false;
				break;
			case VC_PLBCAMA:
				DisplayCameraLabel( VC_LBL_PLBCAMA );
				if (bHasODS)
				{
					if (pRMS) oapiVCSetNeighbours( VC_PLBCAMD, VC_PLBCAMB, VC_LEECAM, VC_DOCKCAM );
					else oapiVCSetNeighbours( VC_PLBCAMD, VC_PLBCAMB, -1, VC_DOCKCAM );
				}
				else if (pRMS) oapiVCSetNeighbours( VC_PLBCAMD, VC_PLBCAMB, VC_LEECAM, VC_RMSSTATION );
				else oapiVCSetNeighbours( VC_PLBCAMD, VC_PLBCAMB, -1, VC_RMSSTATION );

				ok = true;
				break;
			case VC_PLBCAMB:
				DisplayCameraLabel( VC_LBL_PLBCAMB );
				if (bHasODS)
				{
					if (pRMS) oapiVCSetNeighbours( VC_PLBCAMA, VC_PLBCAMC, VC_LEECAM, VC_DOCKCAM );
					else oapiVCSetNeighbours( VC_PLBCAMA, VC_PLBCAMC, -1, VC_DOCKCAM );
				}
				else if (pRMS) oapiVCSetNeighbours( VC_PLBCAMA, VC_PLBCAMC, VC_LEECAM, VC_RMSSTATION );
				else oapiVCSetNeighbours( VC_PLBCAMA, VC_PLBCAMC, -1, VC_RMSSTATION );

				ok = true;
				break;
			case VC_PLBCAMC:
				DisplayCameraLabel( VC_LBL_PLBCAMC );
				if (bHasODS)
				{
					if (pRMS) oapiVCSetNeighbours( VC_PLBCAMB, VC_PLBCAMD, VC_LEECAM, VC_DOCKCAM );
					else oapiVCSetNeighbours( VC_PLBCAMB, VC_PLBCAMD, -1, VC_DOCKCAM );
				}
				else if (pRMS) oapiVCSetNeighbours( VC_PLBCAMB, VC_PLBCAMD, VC_LEECAM, VC_AFTPILOT );
				else oapiVCSetNeighbours( VC_PLBCAMB, VC_PLBCAMD, -1, VC_AFTPILOT );

				ok = true;
				break;
			case VC_PLBCAMD:
				DisplayCameraLabel( VC_LBL_PLBCAMD );
				if (bHasODS)
				{
					if (pRMS) oapiVCSetNeighbours( VC_PLBCAMC, VC_PLBCAMA, VC_LEECAM, VC_DOCKCAM );
					else oapiVCSetNeighbours( VC_PLBCAMC, VC_PLBCAMA, -1, VC_DOCKCAM );
				}
				else if (pRMS) oapiVCSetNeighbours( VC_PLBCAMC, VC_PLBCAMA, VC_LEECAM, VC_AFTPILOT );
				else oapiVCSetNeighbours( VC_PLBCAMC, VC_PLBCAMA, -1, VC_AFTPILOT );

				ok = true;
				break;
			case VC_DOCKCAM: //Docking camera
				if (pExtAirlock)
				{
					DisplayCameraLabel( VC_LBL_DOCKCAM );
					SetCameraOffset( _V( orbiter_ofs.x, orbiter_ofs.y + 0.05, orbiter_ofs.z + pExtAirlock->GetZPos() ) );
					SetCameraDefaultDirection( _V( 0.0, 1.0, 0.0 ), PI );
					//oapiCameraSetAperture( 15 * RAD );
					SetCameraRotationRange( 0, 0, 0, 0 );
					oapiVCSetNeighbours( -1, -1, VC_PLBCAMA, VC_AFTPILOT );

					ok = true;
				}
				break;
			case VC_AFTPILOT: //Aft Flight Deck
				DisplayCameraLabel( VC_LBL_AFTPILOT );
				SetCameraOffset( VC_OFFSET + VC_POS_AFTPILOT + orbiter_ofs );
				SetCameraDefaultDirection( VC_DIR_AFTPILOT );
				//oapiCameraSetAperture( 20 * RAD );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 95 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_AFTPILOT_F, VC_AZ_AFTPILOT_F, VC_EL_AFTPILOT_F, VC_OFS_AFTPILOT_L, VC_AZ_AFTPILOT_L, VC_EL_AFTPILOT_L, VC_OFS_AFTPILOT_R, VC_AZ_AFTPILOT_R, VC_EL_AFTPILOT_R );

				if (bHasODS) oapiVCSetNeighbours( VC_STBDSTATION, VC_RMSSTATION, VC_DOCKCAM, VC_AFTWORKSTATION );
				oapiVCSetNeighbours( VC_STBDSTATION, VC_RMSSTATION, VC_PLBCAMD, VC_AFTWORKSTATION );

				pgAftPort->RegisterVC();
				pgAft->RegisterVC();
				pgAftStbd->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_RMSSTATION:
				DisplayCameraLabel( VC_LBL_RMSSTATION );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_RMSSTATION );
				SetCameraDefaultDirection( VC_DIR_RMSSTATION );
				//oapiCameraSetAperture( 20 * RAD );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 95 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_RMSSTATION_F, VC_AZ_RMSSTATION_F, VC_EL_RMSSTATION_F, VC_OFS_RMSSTATION_L, VC_AZ_RMSSTATION_L, VC_EL_RMSSTATION_L, VC_OFS_RMSSTATION_R, VC_AZ_RMSSTATION_R, VC_EL_RMSSTATION_R );

				if (bHasODS) oapiVCSetNeighbours( VC_AFTPILOT, VC_PORTSTATION, VC_DOCKCAM, VC_AFTWORKSTATION );
				else oapiVCSetNeighbours( VC_AFTPILOT, VC_PORTSTATION, VC_PLBCAMA, VC_AFTWORKSTATION );

				pgAftPort->RegisterVC();
				pgAft->RegisterVC();
				pgAftStbd->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_PORTSTATION:
				DisplayCameraLabel( VC_LBL_PORTSTATION );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_PORTSTATION );
				SetCameraDefaultDirection( VC_DIR_PORTSTATION );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_PORTSTATION_F, VC_AZ_PORTSTATION_F, VC_EL_PORTSTATION_F, VC_OFS_PORTSTATION_L, VC_AZ_PORTSTATION_L, VC_EL_PORTSTATION_L, VC_OFS_PORTSTATION_R, VC_AZ_PORTSTATION_R, VC_EL_PORTSTATION_R );

				if (bHasODS) oapiVCSetNeighbours( VC_RMSSTATION, VC_CDR, VC_DOCKCAM, VC_MIDDECK );
				else oapiVCSetNeighbours( VC_RMSSTATION, VC_CDR, VC_PLBCAMA, VC_MIDDECK );

				pgOverheadAft->RegisterVC();
				pgAftPort->RegisterVC();
				pgAft->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_AFTWORKSTATION:
				DisplayCameraLabel( VC_LBL_AFTWORKSTATION );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_AFTWORKSTATION );
				SetCameraDefaultDirection( VC_DIR_AFTWORKSTATION );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_AFTWORKSTATION_F, VC_AZ_AFTWORKSTATION_F, VC_EL_AFTWORKSTATION_F, VC_OFS_AFTWORKSTATION_L, VC_AZ_AFTWORKSTATION_L, VC_EL_AFTWORKSTATION_L, VC_OFS_AFTWORKSTATION_R, VC_AZ_AFTWORKSTATION_R, VC_EL_AFTWORKSTATION_R );
				oapiVCSetNeighbours( VC_STBDSTATION, VC_PORTSTATION, VC_RMSSTATION, VC_MS1 );

				pgOverheadAft->RegisterVC();
				pgAftPort->RegisterVC();
				pgAft->RegisterVC();
				pgAftStbd->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_MS2:
				DisplayCameraLabel( VC_LBL_MS2 );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_MS2 );
				SetCameraDefaultDirection( VC_DIR_MS2 );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_MS2_F, VC_AZ_MS2_F, VC_EL_MS2_F, VC_OFS_MS2_L, VC_AZ_MS2_L, VC_EL_MS2_L, VC_OFS_MS2_R, VC_AZ_MS2_R, VC_EL_MS2_R );

				if (bHasODS) oapiVCSetNeighbours( VC_PORTSTATION, VC_MS1, VC_CDR, VC_DOCKCAM );
				else oapiVCSetNeighbours( VC_PORTSTATION, VC_MS1, VC_CDR, VC_PLBCAMA );

				pgForward->RegisterVC();
				pgCenter->RegisterVC();
				pgOverhead->RegisterVC();
				pgOverheadAft->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_MS1:
				DisplayCameraLabel( VC_LBL_MS1 );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_MS1 );
				SetCameraDefaultDirection( VC_DIR_MS1 );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );
				SetCameraMovement( VC_OFS_MS1_F, VC_AZ_MS1_F, VC_EL_MS1_F, VC_OFS_MS1_L, VC_AZ_MS1_L, VC_EL_MS1_L, VC_OFS_MS1_R, VC_AZ_MS1_R, VC_EL_MS1_R );

				if (bHasODS) oapiVCSetNeighbours( VC_MS2, VC_STBDSTATION, VC_PLT, VC_DOCKCAM );
				else oapiVCSetNeighbours( VC_MS2, VC_STBDSTATION, VC_PLT, VC_PLBCAMA );

				pgCenter->RegisterVC();
				pgOverhead->RegisterVC();
				pgOverheadAft->RegisterVC();
				pgAftStbd->RegisterVC();

				ok = true;
				bUpdateVC = true;
				break;
			case VC_MIDDECK:
				DisplayCameraLabel( VC_LBL_MIDDECK );
				SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_MIDDECK );
				SetCameraDefaultDirection( VC_DIR_MIDDECK );
				SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );

				if (pMission->HasExtAL() || pMission->HasODS()) oapiVCSetNeighbours( -1, -1, VC_PORTSTATION, VC_EXT_AL );
				else oapiVCSetNeighbours( -1, -1, VC_PORTSTATION, -1 );

				ok = true;
				break;
			case VC_EXT_AL:
				if (pExtAirlock)
				{
					DisplayCameraLabel( VC_LBL_EXT_AL );
					SetCameraOffset( orbiter_ofs + VC_OFFSET + VC_POS_EXT_AL + _V( 0, 0, pExtAirlock->GetZPos() ) );
					SetCameraDefaultDirection( VC_DIR_EXT_AL );

					SetCameraRotationRange( 144 * RAD, 144 * RAD, 72 * RAD, 72 * RAD );

					if (bHasODS) oapiVCSetNeighbours( -1, -1, VC_MIDDECK, VC_DOCKCAM );
					else oapiVCSetNeighbours( -1, -1, VC_MIDDECK, -1 );

					ok = true;
				}
				break;
		}

		// VC Cockpit not visible from Payload cameras or RMS camera.
		if (id >= VC_DOCKCAM && id <= VC_LEECAM)
		{
			// hide internal VC mesh (and individual panels) and middeck, and show cockpit mesh meant to be seen in external views
			SetMeshVisibilityMode(mesh_vc, MESHVIS_NEVER);
			HideMidDeck();
			pgForward->HidePanels();
			pgLeft->HidePanels();
			pgCenter->HidePanels();
			pgRight->HidePanels();
			pgOverhead->HidePanels();
			pgOverheadAft->HidePanels();
			pgAftPort->HidePanels();
			pgAft->HidePanels();
			pgAftStbd->HidePanels();

			SetMeshVisibilityMode( mesh_vcexternal, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

			// Pan and tilt from camera control not from alt + arrow but from the dialog
			SetCameraRotationRange( 0, 0, 0, 0 );
			// No lean for payload camera
			SetCameraMovement( _V(0, 0, 0), 0, 0, _V(0, 0, 0), 0, 0, _V(0, 0, 0), 0, 0 );

			// Refresh camera meshes and view positions
			pPayloadBay->SetAnimationCameras();
		}
		else
		{
			SetMeshVisibilityMode( mesh_vc, MESHVIS_VC );
			ShowMidDeck();
			pgForward->ShowPanels();
			pgLeft->ShowPanels();
			pgCenter->ShowPanels();
			pgRight->ShowPanels();
			pgOverhead->ShowPanels();
			pgOverheadAft->ShowPanels();
			pgAftPort->ShowPanels();
			pgAft->ShowPanels();
			pgAftStbd->ShowPanels();

			SetMeshVisibilityMode( mesh_vcexternal, MESHVIS_EXTERNAL );
		}

		if (bUpdateVC) {
			// register the HUDs (synced)
			oapiVCRegisterHUD(&huds);
			// register all MFD displays
			for (int i = 0; i < 11; i++)
			{
				mdus[i]->RealizeMFD(i);
			}
		}
		oapiCameraSetCockpitDir(0, 0);
		return ok;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkLoadVC: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkLoadVC" );
		abort();
	}
}

bool Atlantis::clbkVCMouseEvent( int id, int event, VECTOR3& p )
{
	try
	{
		if (pgForward->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgLeft->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgCenter->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgRight->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgOverhead->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgOverheadAft->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgAftPort->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgAft->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgAftStbd->OnVCMouseEvent( id, event, p ))
			return true;
		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkVCMouseEvent: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkVCMouseEvent" );
		abort();
	}
}

bool Atlantis::clbkVCRedrawEvent( int id, int event, SURFHANDLE surf )
{
	try
	{
		if (pgForward->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgLeft->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgCenter->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgRight->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgOverhead->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgOverheadAft->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgAftPort->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgAft->OnVCRedrawEvent(id, event, surf))
			return true;
		if (pgAftStbd->OnVCRedrawEvent(id, event, surf))
			return true;
		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkVCRedrawEvent: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkVCRedrawEvent" );
		abort();
	}
}

bool Atlantis::clbkDrawHUD( int mode, const HUDPAINTSPEC* hps, oapi::Sketchpad* skp )
{
	try
	{
		if (!pHUD[0]->Draw( hps, skp ))
			pHUD[1]->Draw( hps, skp );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in clbkDrawHUD: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OV) [FATAL ERROR] Exception in clbkDrawHUD" );
		abort();
	}
	return true;
}


DiscreteBundleManager* Atlantis::BundleManager() const
{
	return bundleManager;
}

mission::Mission* Atlantis::GetMissionData() const
{
	return pMission;
}

SSVOptions* Atlantis::GetOptionsData() const
{
	return options;
}

const VECTOR3& Atlantis::GetOrbiterCoGOffset( void ) const
{
	return orbiter_ofs;
}

// --------------------------------------------------------------
// launch configuration setup (orbiter + tank + SRB)
// --------------------------------------------------------------
void Atlantis::SetLaunchConfiguration(void)
{
	// default RSRM
	double SRB_MAX_PROPELLANT_MASS = RSRM_MAX_PROPELLANT_MASS;
	double SRB_THRUST = RSRM_THRUST;
	double SRB_ISP0 = RSRM_ISP0;
	double SRB_ISP1 = RSRM_ISP1;

	SRB* pSRB = GetSRBInterface( LEFT );
	if (pSRB)
	{
		// use correct values if available
		SRB_MAX_PROPELLANT_MASS = pSRB->SRB_MAX_PROPELLANT_MASS;
		SRB_THRUST = pSRB->SRB_THRUST;
		SRB_ISP0 = pSRB->SRB_ISP0;
		SRB_ISP1 = pSRB->SRB_ISP1;
	}

	// *********************** physical parameters *********************************

	SetSize(30.0);
	SetCrossSections(_V(668.94, 676.94, 258.97));
	SetRotDrag(_V(0.7, 0.1, 0.3));
	SetPMI(_V(249.62, 239.97, 67.43));

	DefineTouchdownPoints();

	SetGravityGradientDamping(0.05);

	// ************************* propellant specs **********************************
	CreateOrbiterTanks();

	if (!ph_mps) ph_mps = CreatePropellantResource(MPS_MANIFOLD_MASS_TOTAL);    // mps manifold
	LOXmass = MPS_MANIFOLD_MASS_LOX;
	LH2mass = MPS_MANIFOLD_MASS_LH2;
	if (!ph_srb)  ph_srb = CreatePropellantResource(SRB_MAX_PROPELLANT_MASS*2.0); // SRB's

	// *********************** thruster definitions ********************************
	ClearThrusterDefinitions();

	phLOXdump = ph_mps;
	phLH2dump = ph_mps;

	CreateSSMEs( orbiter_ofs );

	CreateOMSEngines( orbiter_ofs );

	CreateAttControls_RCS( orbiter_ofs );

	// SRBs
	th_srb[0] = CreateThruster(LSRB_OFFSET + _V( 0.0, 0.0, -22.94033 ), SRB_THRUST_DIR, SRB_THRUST, ph_srb, SRB_ISP0, SRB_ISP1);
	th_srb[1] = CreateThruster(RSRB_OFFSET + _V( 0.0, 0.0, -22.94033 ), SRB_THRUST_DIR, SRB_THRUST, ph_srb, SRB_ISP0, SRB_ISP1);
	AddSRBExhaust( false );

	// ************************* aerodynamics **************************************

	hStackAirfoil = CreateAirfoil2(LIFT_VERTICAL, _V(0, 0, 0), AscentLiftCoeff, ORBITER_CHORD_LENGTH, ORBITER_WING_AREA, ORBITER_WING_ASPECT_RATIO);
	ClearVariableDragElements();
	// ************************ visual parameters **********************************

	AddOrbiterVisual();

	status = STATE_PRELAUNCH;

}

// --------------------------------------------------------------
// Configuration after launch, before SRB separation
// --------------------------------------------------------------
void Atlantis::SetPostLaunchConfiguration( void )
{
	SetLaunchConfiguration();
	status = STATE_STAGE1;
	return;
}

// --------------------------------------------------------------
// Configuration after booster separation (orbiter + tank)
// --------------------------------------------------------------
void Atlantis::SetOrbiterTankConfiguration(void)
{
	// *********************** physical parameters *********************************

	SetSize(28.8);
	//SetEmptyMass (ORBITER_EMPTY_MASS + TANK_EMPTY_MASS + pl_mass);
	SetCrossSections(_V(303.91, 422.33, 153.51));
	SetRotDrag(_V(0.7, 0.1, 0.3));
	SetPMI(_V(131.82, 131.49, 59.28));
	SetTouchdownPoints(_V(0, -5, 30), _V(-10, -10, -30), _V(10, 0, -30));

	// ************************* propellant specs **********************************
	CreateOrbiterTanks();

	if (!ph_mps) ph_mps = CreatePropellantResource(MPS_MANIFOLD_MASS_TOTAL);    // mps manifold
	LOXmass = MPS_MANIFOLD_MASS_LOX;
	LH2mass = MPS_MANIFOLD_MASS_LH2;

	// *********************** thruster definitions ********************************

	// Orbiter main engines
	phLOXdump = ph_mps;
	phLH2dump = ph_mps;

	CreateSSMEs( orbiter_ofs );

	CreateOMSEngines( orbiter_ofs );

	CreateAttControls_RCS( orbiter_ofs );

	// ************************* aerodynamics **************************************

	ClearAirfoilDefinitions();
	hStackAirfoil = NULL;
	ClearVariableDragElements();
	// ************************ visual parameters **********************************

	// status has to be updated before AddTankVisual is called to update ET texture
	status = STATE_STAGE2;

	AddOrbiterVisual();
}

// --------------------------------------------------------------
// Configuration after tank separation (orbiter only)
// --------------------------------------------------------------
void Atlantis::SetOrbiterConfiguration(void)
{
	// *********************** physical parameters *********************************

	SetSize(19.6);
	SetPMI(_V(120.2, 108.8, 13.497));
	SetGravityGradientDamping(20.0);
	SetCrossSections(ORBITER_CS);
	DefineTouchdownPoints();

	// ************************* aerodynamics **************************************

	ClearAirfoilDefinitions();
	hStackAirfoil = NULL;
	SetRotDrag(_V(0.43, 0.43, 0.29)); // angular drag
	hOVAirfoilV = CreateAirfoil3( LIFT_VERTICAL, _V( 0.0, 0.0/*-2.9671*/, 0.7/*-4.638006*/ ), VLiftCoeff, &aerosurfaces, ORBITER_CHORD_LENGTH, ORBITER_WING_AREA, ORBITER_WING_ASPECT_RATIO );
	hOVAirfoilH = CreateAirfoil3( LIFT_HORIZONTAL, _V( 0.0, 0.0/*5.555108*/, 0.0/*-12.93009*/ ), HLiftCoeff, &aerosurfaces, /*5.075174*/ORBITER_CHORD_LENGTH, /*38.39218*/ORBITER_WING_AREA, /*1.675*/ORBITER_WING_ASPECT_RATIO );

	ClearVariableDragElements();
	if (pDragChute) pDragChute->AddAero();

	SetADCtrlMode(7);

	// ************************* particle streams **********************************

	PARTICLESTREAMSPEC rps = {
		0, 20, 20, 0, 0.03, 0.5, 100, 3, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1, PARTICLESTREAMSPEC::ATM_PLIN, 6e7, 12e7
	};
	AddReentryStream(&rps);

	// ************************* propellant specs **********************************
	CreateOrbiterTanks();

	// *********************** thruster definitions ********************************
	CreateSSMEs( orbiter_ofs );

	CreateOMSEngines( orbiter_ofs );

	CreateAttControls_RCS( orbiter_ofs );

	// ************************ visual parameters **********************************
	AddOrbiterVisual();

	status = 3;
}


void assertValidHandles(const char* context, THRUSTER_HANDLE *thx, int count)
{
	static char buf[200];
	for (int i = 0; i < count; i++) {
		if (thx[i] == NULL) {
			sprintf_s(buf, 200, "(SSV_OV) [ERROR] %s : Thruster handle is NULL (at index %d)", context, i);
			oapiWriteLog(buf);
		}
	}
}

// --------------------------------------------------------------
// Attitude controls (RCS) during orbital phase
// --------------------------------------------------------------
void Atlantis::CreateAttControls_RCS(VECTOR3 center)
{
	// delete existing exhaust definitions and update positions
	// we only need to define the thruster positions once; after that ShiftCG should set up positions
	while (!vExRCS.empty()) {
		DelExhaust(vExRCS.back());
		vExRCS.pop_back();
	}
	while (!vExStreamRCS.empty()) {
		DelExhaustStream(vExStreamRCS.back());
		vExStreamRCS.pop_back();
	}

	// set of attitude thrusters (idealised). The arrangement is such that no angular
	// momentum is created in linear mode, and no linear momentum is created in rotational mode.
	// PU, PD, Z+, Z-
	if (!bRCSDefined) {
		th_att_rcs[0] = CreateThruster(_V(-1.6, 0, 15.5), _V( 0.601815, 0.798636, 0.0 ), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[1] = CreateThruster(_V(1.6, 0, 15.5), _V( -0.601815, 0.798636, 0.0 ), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[2] = CreateThruster(_V(0, 0, -15.5), _V(0, -1, 0), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[3] = CreateThruster(_V(0, 0, -15.5), _V(0, -1, 0), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[4] = CreateThruster(_V(0, 0, 15.5), _V(0, -1, 0), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[5] = CreateThruster(_V(0, 0, -15.5), _V(0.2844, 0.9481, 0.1422), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[6] = CreateThruster(_V(0, 0, -15.5), _V(-0.2844, 0.9481, 0.1422), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		thg_pitchup = CreateThrusterGroup(th_att_rcs, 4, THGROUP_USER);
		thg_pitchdown = CreateThrusterGroup(th_att_rcs + 4, 3, THGROUP_USER);

		th_att_lin[0] = CreateThruster(_V(-1.6, 0, 15.5), _V( 0.601815, 0.798636, 0.0 ), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[1] = CreateThruster(_V(1.6, 0, 15.5), _V( -0.601815, 0.798636, 0.0 ), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[5] = CreateThruster(_V(0, 0, -15.5), _V(0, -1, 0), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[6] = CreateThruster(_V(0, 0, -15.5), _V(0, -1, 0), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[4] = CreateThruster(_V(0, 0, 15.5), _V(0, -1, 0), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[2] = CreateThruster(_V(0, 0, -15.5), _V(0.2844, 0.9481, 0.1422), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[3] = CreateThruster(_V(0, 0, -15.5), _V(-0.2844, 0.9481, 0.1422), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		thg_transup = CreateThrusterGroup(th_att_lin, 4, THGROUP_USER);
		thg_transdown = CreateThrusterGroup(th_att_lin + 4, 3, THGROUP_USER);
	}
	else { // update thruster positions
		SetThrusterRef(th_att_rcs[0], _V(-1.6, 0, 15.5));
		SetThrusterRef(th_att_rcs[1], _V(1.6, 0, 15.5));
		SetThrusterRef(th_att_rcs[2], _V(0, 0, -15.5));
		SetThrusterRef(th_att_rcs[3], _V(0, 0, -15.5));
		SetThrusterRef(th_att_rcs[4], _V(0, 0, 15.5));
		SetThrusterRef(th_att_rcs[5], _V(0, 0, -15.5));
		SetThrusterRef(th_att_rcs[6], _V(0, 0, -15.5));

		SetThrusterRef(th_att_lin[0], _V(-1.6, 0, 15.5));
		SetThrusterRef(th_att_lin[1], _V(1.6, 0, 15.5));
		SetThrusterRef(th_att_lin[5], _V(0, 0, -15.5));
		SetThrusterRef(th_att_lin[6], _V(0, 0, -15.5));
		SetThrusterRef(th_att_lin[4], _V(0, 0, 15.5));
		SetThrusterRef(th_att_lin[2], _V(0, 0, -15.5));
		SetThrusterRef(th_att_lin[3], _V(0, 0, -15.5));
	}

	AddRCSExhaust( th_att_rcs[0], center + _V( -1.560068, -1.52057, 15.759464 ), _V( -0.601815, -0.798636, 0.0 ) );//F1D
	AddRCSExhaust( th_att_rcs[0], center + _V( -1.682242, -1.482724, 15.388624 ), _V( -0.601815, -0.798636, 0.0 ) );//F3D

	AddRCSExhaust( th_att_rcs[1], center + _V( 1.560068, -1.52057, 15.759464 ), _V( 0.601815, -0.798636, 0.0 ) );//F2D
	AddRCSExhaust( th_att_rcs[1], center + _V( 1.682242, -1.482724, 15.388624 ), _V( 0.601815, -0.798636, 0.0 ) );//F4D

	AddRCSExhaust( th_att_rcs[2], center + _V( -3.3528, 1.6176, -14.2674 ), _V( 0.0, 1.0, 0.0 ) );//L4U
	AddRCSExhaust( th_att_rcs[2], center + _V( -3.3528, 1.6176, -14.5976 ), _V( 0.0, 1.0, 0.0 ) );//L2U
	AddRCSExhaust( th_att_rcs[2], center + _V( -3.3528, 1.6176, -14.9278 ), _V( 0.0, 1.0, 0.0 ) );//L1U

	AddRCSExhaust( th_att_rcs[3], center + _V( 3.3528, 1.6176, -14.2674 ), _V( 0.0, 1.0, 0.0 ) );//R4U
	AddRCSExhaust( th_att_rcs[3], center + _V( 3.3528, 1.6176, -14.5976 ), _V( 0.0, 1.0, 0.0 ) );//R2U
	AddRCSExhaust( th_att_rcs[3], center + _V( 3.3528, 1.6176, -14.9278 ), _V( 0.0, 1.0, 0.0 ) );//R1U

	AddRCSExhaust( th_att_rcs[4], center + _V( -0.3656076, -0.085216, 15.325505 ), _V( 0.0, 1.0, 0.0 ) );//F1U
	AddRCSExhaust( th_att_rcs[4], center + _V( 0.0, -0.058038, 15.3257082 ), _V( 0.0, 1.0, 0.0 ) );//F3U
	AddRCSExhaust( th_att_rcs[4], center + _V( 0.3656076, -0.085216, 15.325505 ), _V( 0.0, 1.0, 0.0 ) );//F2U

	AddRCSExhaust( th_att_rcs[5], center + _V( -2.84353, 0.52286, -14.2674 ), _V( -0.2844, -0.9481, -0.1422 ) );//L4D
	AddRCSExhaust( th_att_rcs[5], center + _V( -2.84353, 0.52286, -14.5976 ), _V( -0.2844, -0.9481, -0.1422 ) );//L2D
	AddRCSExhaust( th_att_rcs[5], center + _V( -2.84353, 0.52286, -14.9278 ), _V( -0.2844, -0.9481, -0.1422 ) );//L3D

	AddRCSExhaust( th_att_rcs[6], center + _V( 2.84353, 0.52286, -14.2674 ), _V( 0.2844, -0.9481, -0.1422 ) );//R4D
	AddRCSExhaust( th_att_rcs[6], center + _V( 2.84353, 0.52286, -14.5976 ), _V( 0.2844, -0.9481, -0.1422 ) );//R2D
	AddRCSExhaust( th_att_rcs[6], center + _V( 2.84353, 0.52286, -14.9278 ), _V( 0.2844, -0.9481, -0.1422 ) );//R3D

	AddRCSExhaust( th_att_lin[0], center + _V( -1.560068, -1.52057, 15.759464 ), _V( -0.601815, -0.798636, 0.0 ) );//F1D
	AddRCSExhaust( th_att_lin[0], center + _V( -1.682242, -1.482724, 15.388624 ), _V( -0.601815, -0.798636, 0.0 ) );//F3D

	AddRCSExhaust( th_att_lin[1], center + _V( 1.560068, -1.52057, 15.759464 ), _V( 0.601815, -0.798636, 0.0 ) );//F2D
	AddRCSExhaust( th_att_lin[1], center + _V( 1.682242, -1.482724, 15.388624 ), _V( 0.601815, -0.798636, 0.0 ) );//F4D

	AddRCSExhaust( th_att_lin[5], center + _V( -3.3528, 1.6176, -14.2674 ), _V( 0.0, 1.0, 0.0 ) );//L4U
	AddRCSExhaust( th_att_lin[5], center + _V( -3.3528, 1.6176, -14.5976 ), _V( 0.0, 1.0, 0.0 ) );//L2U
	AddRCSExhaust( th_att_lin[5], center + _V( -3.3528, 1.6176, -14.9278 ), _V( 0.0, 1.0, 0.0 ) );//L1U

	AddRCSExhaust( th_att_lin[6], center + _V( 3.3528, 1.6176, -14.2674 ), _V( 0.0, 1.0, 0.0 ) );//R4U
	AddRCSExhaust( th_att_lin[6], center + _V( 3.3528, 1.6176, -14.5976 ), _V( 0.0, 1.0, 0.0 ) );//R2U
	AddRCSExhaust( th_att_lin[6], center + _V( 3.3528, 1.6176, -14.9278 ), _V( 0.0, 1.0, 0.0 ) );//R1U

	AddRCSExhaust( th_att_lin[4], center + _V( -0.3656076, -0.085216, 15.325505 ), _V( 0.0, 1.0, 0.0 ) );//F1U
	AddRCSExhaust( th_att_lin[4], center + _V( 0.0, -0.058038, 15.3257082 ), _V( 0.0, 1.0, 0.0 ) );//F3U
	AddRCSExhaust( th_att_lin[4], center + _V( 0.3656076, -0.085216, 15.325505 ), _V( 0.0, 1.0, 0.0 ) );//F2U

	AddRCSExhaust( th_att_lin[2], center + _V( -2.84353, 0.52286, -14.2674 ), _V( -0.2844, -0.9481, -0.1422 ) );//L4D
	AddRCSExhaust( th_att_lin[2], center + _V( -2.84353, 0.52286, -14.5976 ), _V( -0.2844, -0.9481, -0.1422 ) );//L2D
	AddRCSExhaust( th_att_lin[2], center + _V( -2.84353, 0.52286, -14.9278 ), _V( -0.2844, -0.9481, -0.1422 ) );//L3D

	AddRCSExhaust( th_att_lin[3], center + _V( 2.84353, 0.52286, -14.2674 ), _V( 0.2844, -0.9481, -0.1422 ) );//R4D
	AddRCSExhaust( th_att_lin[3], center + _V( 2.84353, 0.52286, -14.5976 ), _V( 0.2844, -0.9481, -0.1422 ) );//R2D
	AddRCSExhaust( th_att_lin[3], center + _V( 2.84353, 0.52286, -14.9278 ), _V( 0.2844, -0.9481, -0.1422 ) );//R3D

	// YL, YR, Y+, Y-
	if (!bRCSDefined) {
		th_att_rcs[7] = CreateThruster(_V(0, 0, 15.5), _V(-1, 0, 0), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[8] = CreateThruster(_V(0, 0, -15.5), _V(1, 0, 0), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[9] = CreateThruster(_V(0, 0, 15.5), _V(1, 0, 0), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[10] = CreateThruster(_V(0, 0, -15.5), _V(-1, 0, 0), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		thg_yawleft = CreateThrusterGroup(th_att_rcs + 7, 2, THGROUP_USER);
		thg_yawright = CreateThrusterGroup(th_att_rcs + 9, 2, THGROUP_USER);

		th_att_lin[7] = CreateThruster(_V(0, 0, 15.5), _V(-1, 0, 0), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[8] = CreateThruster(_V(0, 0, -15.5), _V(-1, 0, 0), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[9] = CreateThruster(_V(0, 0, 15.5), _V(1, 0, 0), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[10] = CreateThruster(_V(0, 0, -15.5), _V(1, 0, 0), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		thg_transleft = CreateThrusterGroup(th_att_lin + 7, 2, THGROUP_USER);
		thg_transright = CreateThrusterGroup(th_att_lin + 9, 2, THGROUP_USER);
	}
	else { // update thruster positions
		SetThrusterRef(th_att_rcs[7], _V(0, 0, 15.5));
		SetThrusterRef(th_att_rcs[8], _V(0, 0, -15.5));
		SetThrusterRef(th_att_rcs[9], _V(0, 0, 15.5));
		SetThrusterRef(th_att_rcs[10], _V(0, 0, -15.5));

		SetThrusterRef(th_att_lin[7], _V(0, 0, 15.5));
		SetThrusterRef(th_att_lin[8], _V(0, 0, -15.5));
		SetThrusterRef(th_att_lin[9], _V(0, 0, 15.5));
		SetThrusterRef(th_att_lin[10], _V(0, 0, -15.5));
	}

	AddRCSExhaust( th_att_rcs[7], center + _V( 1.7653, -1.094358, 15.027182 ), _V( 1.0, 0.0, 0.0 ) );//F2R
	AddRCSExhaust( th_att_rcs[7], center + _V( 1.4879066, -1.46215, 14.9754168 ), _V( 1.0, 0.0, 0.0 ) );//F4R
	AddRCSExhaust( th_att_rcs[9], center + _V( -1.7653, -1.094358, 15.027182 ), _V( -1.0, 0.0, 0.0 ) );//F1L
	AddRCSExhaust( th_att_rcs[9], center + _V( -1.4879066, -1.46215, 14.9754168 ), _V( -1.0, 0.0, 0.0 ) );//F3L

	AddRCSExhaust( th_att_rcs[8], center + _V( -3.806698, 1.0715, -14.2674 ), _V( -1.0, 0.0, 0.0 ) );//L4L
	AddRCSExhaust( th_att_rcs[8], center + _V( -3.806698, 1.0715, -14.5976 ), _V( -1.0, 0.0, 0.0 ) );//L2L
	AddRCSExhaust( th_att_rcs[8], center + _V( -3.806698, 1.0715, -14.9278 ), _V( -1.0, 0.0, 0.0 ) );//L3L
	AddRCSExhaust( th_att_rcs[8], center + _V( -3.806698, 1.0715, -15.258 ), _V( -1.0, 0.0, 0.0 ) );//L1L

	AddRCSExhaust( th_att_rcs[10], center + _V( 3.806698, 1.0715, -14.2674 ), _V( 1.0, 0.0, 0.0 ) );//R4R
	AddRCSExhaust( th_att_rcs[10], center + _V( 3.806698, 1.0715, -14.5976 ), _V( 1.0, 0.0, 0.0 ) );//R2R
	AddRCSExhaust( th_att_rcs[10], center + _V( 3.806698, 1.0715, -14.9278 ), _V( 1.0, 0.0, 0.0 ) );//R3R
	AddRCSExhaust( th_att_rcs[10], center + _V( 3.806698, 1.0715, -15.258 ), _V( 1.0, 0.0, 0.0 ) );//R1R

	AddRCSExhaust( th_att_lin[7], center + _V( 1.7653, -1.094358, 15.027182 ), _V( 1.0, 0.0, 0.0 ) );//F2R
	AddRCSExhaust( th_att_lin[7], center + _V( 1.4879066, -1.46215, 14.9754168 ), _V( 1.0, 0.0, 0.0 ) );//F4R
	AddRCSExhaust( th_att_lin[9], center + _V( -1.7653, -1.094358, 15.027182 ), _V( -1.0, 0.0, 0.0 ) );//F1L
	AddRCSExhaust( th_att_lin[9], center + _V( -1.4879066, -1.46215, 14.9754168 ), _V( -1.0, 0.0, 0.0 ) );//F3L

	AddRCSExhaust( th_att_lin[10], center + _V( -3.806698, 1.0715, -14.2674 ), _V( -1.0, 0.0, 0.0 ) );//L4L
	AddRCSExhaust( th_att_lin[10], center + _V( -3.806698, 1.0715, -14.5976 ), _V( -1.0, 0.0, 0.0 ) );//L2L
	AddRCSExhaust( th_att_lin[10], center + _V( -3.806698, 1.0715, -14.9278 ), _V( -1.0, 0.0, 0.0 ) );//L3L
	AddRCSExhaust( th_att_lin[10], center + _V( -3.806698, 1.0715, -15.258 ), _V( -1.0, 0.0, 0.0 ) );//L1L

	AddRCSExhaust( th_att_lin[8], center + _V( 3.806698, 1.0715, -14.2674 ), _V( 1.0, 0.0, 0.0 ) );//R4R
	AddRCSExhaust( th_att_lin[8], center + _V( 3.806698, 1.0715, -14.5976 ), _V( 1.0, 0.0, 0.0 ) );//R2R
	AddRCSExhaust( th_att_lin[8], center + _V( 3.806698, 1.0715, -14.9278 ), _V( 1.0, 0.0, 0.0 ) );//R3R
	AddRCSExhaust( th_att_lin[8], center + _V( 3.806698, 1.0715, -15.258 ), _V( 1.0, 0.0, 0.0 ) );//R1R

	// RL, RR
	if (!bRCSDefined) {
		th_att_rcs[11] = CreateThruster(_V(1.6, 0, 15.5), _V( -0.601815, 0.798636, 0.0 ), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[12] = CreateThruster(_V(-2.7, 0, -15.5), _V(0, -1, 0), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[13] = CreateThruster(_V(2.7, 0, -15.5), _V(-0.2844, 0.9481, 0.1422), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[14] = CreateThruster(_V(-1.6, 0, 15.5), _V( 0.601815, 0.798636, 0.0 ), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[15] = CreateThruster(_V(-2.7, 0, -15.5), _V(0.2844, 0.9481, 0.1422), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_rcs[16] = CreateThruster(_V(2.7, 0, -15.5), _V(0, -1, 0), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		thg_rollleft = CreateThrusterGroup(th_att_rcs + 11, 3, THGROUP_USER);
		thg_rollright = CreateThrusterGroup(th_att_rcs + 14, 3, THGROUP_USER);
	}
	else { // update thruster positions
		SetThrusterRef(th_att_rcs[11], _V(1.6, 0, 15.5));
		SetThrusterRef(th_att_rcs[12], _V(-2.7, 0, -15.5));
		SetThrusterRef(th_att_rcs[13], _V(2.7, 0, -15.5));
		SetThrusterRef(th_att_rcs[14], _V(-1.6, 0, 15.5));
		SetThrusterRef(th_att_rcs[15], _V(-2.7, 0, -15.5));
		SetThrusterRef(th_att_rcs[16], _V(2.7, 0, -15.5));
	}

	AddRCSExhaust( th_att_rcs[11], center + _V( 1.560068, -1.52057, 15.759464 ), _V( 0.601815, -0.798636, 0.0 ) );//F2D
	AddRCSExhaust( th_att_rcs[11], center + _V( 1.682242, -1.482724, 15.388624 ), _V( 0.601815, -0.798636, 0.0 ) );//F4D

	AddRCSExhaust( th_att_rcs[14], center + _V( -1.560068, -1.52057, 15.759464 ), _V( -0.601815, -0.798636, 0.0 ) );//F1D
	AddRCSExhaust( th_att_rcs[14], center + _V( -1.682242, -1.482724, 15.388624 ), _V( -0.601815, -0.798636, 0.0 ) );//F3D

	AddRCSExhaust( th_att_rcs[12], center + _V( -3.3528, 1.6176, -14.2674 ), _V( 0.0, 1.0, 0.0 ) );//L4U
	AddRCSExhaust( th_att_rcs[12], center + _V( -3.3528, 1.6176, -14.5976 ), _V( 0.0, 1.0, 0.0 ) );//L2U
	AddRCSExhaust( th_att_rcs[12], center + _V( -3.3528, 1.6176, -14.9278 ), _V( 0.0, 1.0, 0.0 ) );//L1U

	AddRCSExhaust( th_att_rcs[16], center + _V( 3.3528, 1.6176, -14.2674 ), _V( 0.0, 1.0, 0.0 ) );//R4U
	AddRCSExhaust( th_att_rcs[16], center + _V( 3.3528, 1.6176, -14.5976 ), _V( 0.0, 1.0, 0.0 ) );//R2U
	AddRCSExhaust( th_att_rcs[16], center + _V( 3.3528, 1.6176, -14.9278 ), _V( 0.0, 1.0, 0.0 ) );//R1U

	AddRCSExhaust( th_att_rcs[15], center + _V( -2.84353, 0.52286, -14.2674 ), _V( -0.2844, -0.9481, -0.1422 ) );//L4D
	AddRCSExhaust( th_att_rcs[15], center + _V( -2.84353, 0.52286, -14.5976 ), _V( -0.2844, -0.9481, -0.1422 ) );//L2D
	AddRCSExhaust( th_att_rcs[15], center + _V( -2.84353, 0.52286, -14.9278 ), _V( -0.2844, -0.9481, -0.1422 ) );//L3D

	AddRCSExhaust( th_att_rcs[13], center + _V( 2.84353, 0.52286, -14.2674 ), _V( 0.2844, -0.9481, -0.1422 ) );//R4D
	AddRCSExhaust( th_att_rcs[13], center + _V( 2.84353, 0.52286, -14.5976 ), _V( 0.2844, -0.9481, -0.1422 ) );//R2D
	AddRCSExhaust( th_att_rcs[13], center + _V( 2.84353, 0.52286, -14.9278 ), _V( 0.2844, -0.9481, -0.1422 ) );//R3D

	// +X, -X
	if (!bRCSDefined) {
		th_att_lin[11] = CreateThruster(_V(-3.3, 0, -16), _V(0.0, -0.173648, 0.984808), RCS_THRUST, ph_lrcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[12] = CreateThruster(_V(3.3, 0, -16), _V(0.0, -0.173648, 0.984808), RCS_THRUST, ph_rrcs, RCS_ISP0, RCS_ISP1);
		th_att_lin[13] = CreateThruster(_V(0, 0, 16), _V(0, 0, -1), RCS_THRUST, ph_frcs, RCS_ISP0, RCS_ISP1);
		thg_transfwd = CreateThrusterGroup(th_att_lin + 11, 2, THGROUP_USER);
		thg_transaft = CreateThrusterGroup(th_att_lin + 13, 1, THGROUP_USER);
	}
	else { // update thruster positions
		SetThrusterRef(th_att_lin[11], _V(-3.3, 0, -16));
		SetThrusterRef(th_att_lin[12], _V(3.3, 0, -16));
		SetThrusterRef(th_att_lin[13], _V(0, 0, 16));
	}

	AddRCSExhaust( th_att_lin[11], center + _V( -3.1496, 1.428624, -15.265366 ), _V( 0.0, 0.173648, -0.984808 ) );//L1A
	AddRCSExhaust( th_att_lin[11], center + _V( -3.4798, 1.428624, -15.265366 ), _V( 0.0, 0.173648, -0.984808 ) );//L3A

	AddRCSExhaust( th_att_lin[12], center + _V( 3.1496, 1.428624, -15.265366 ), _V( 0.0, 0.173648, -0.984808 ) );//R1A
	AddRCSExhaust( th_att_lin[12], center + _V( 3.4798, 1.428624, -15.265366 ), _V( 0.0, 0.173648, -0.984808 ) );//R3A

	AddRCSExhaust( th_att_lin[13], center + _V( 0.0, -0.56807, 16.448312 ), _V( 0.0, 0.0, 1.0 ) );//F3F
	AddRCSExhaust( th_att_lin[13], center + _V( -0.3722116, -0.606043, 16.448312 ), _V( 0.0, 0.0, 1.0 ) );//F1F
	AddRCSExhaust( th_att_lin[13], center + _V( 0.3722116, -0.606043, 16.448312 ), _V( 0.0, 0.0, 1.0 ) );//F2F


	UpdateTranslationForces();

	bRCSDefined = true;
}

void Atlantis::AddRCSExhaust(THRUSTER_HANDLE thX, const VECTOR3& pos, const VECTOR3& dir)
{
	const double eh = 0;             // exhaust length scale
	const double ew1 = 0.0; // exhaust width scales
	vExRCS.push_back(AddExhaust(thX, eh, ew1, pos, dir, RCS_Exhaust_tex));
	vExStreamRCS.push_back(AddExhaustStream(thX, pos, &RCS_PSSpec));
}

void Atlantis::AddVRCSExhaust(THRUSTER_HANDLE thX, const VECTOR3& pos, const VECTOR3& dir)
{
	const double eh = 0.5754;             // exhaust length scale
	const double ew1 = 0.1; // exhaust width scales
	vExRCS.push_back(AddExhaust(thX, eh, ew1, pos, dir, RCS_Exhaust_tex));
	vExStreamRCS.push_back(AddExhaustStream(thX, pos, &RCS_PSSpec));
}

// --------------------------------------------------------------
// Define animation sequences for moving parts
// --------------------------------------------------------------
void Atlantis::DefineAnimations(void)
{
	UINT midx = mesh_orbiter; // mesh index for all external animations

	ANIMATIONCOMPONENT_HANDLE parent;
	BeginLoggingAnims();

	// ======================================================
	// SSME Animations
	// ======================================================
	static VECTOR3 dummy1p = _V( 0.0, 0.0, 1.0 );
	MGROUP_ROTATE* SSME1_PITCH = new MGROUP_ROTATE( LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy1p), 1, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>((SSME_PITCH_MAX - SSME_INSTALL_PITCH[0]) * RAD) );
	anim_ssme_pitch[0] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_pitch[0]", anim_ssme_pitch[0] );
	parent = AddManagedAnimationComponent( anim_ssme_pitch[0], 0.0, 1.0, SSME1_PITCH );

	MGROUP_ROTATE* SSME1_YAW = new MGROUP_ROTATE( mesh_ssme[0], NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>((SSME_YAW_MAX - SSME_YAW_MIN) * RAD) );
	anim_ssme_yaw[0] = CreateAnimation( (SSME_INSTALL_YAW[0] - SSME_YAW_MIN) / (SSME_YAW_MAX - SSME_YAW_MIN) );
	LogAnim( "anim_ssme_yaw[0]", anim_ssme_yaw[0] );
	parent = AddManagedAnimationComponent( anim_ssme_yaw[0], 0.0, 1.0, SSME1_YAW, parent );

	MGROUP_TRANSFORM* SSME1_GOX_POS = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(&ssme_gox_pos[0]), 1 );
	anim_ssme_gox_pos[0] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_gox_pos[0]", anim_ssme_gox_pos[0] );
	AddManagedAnimationComponent( anim_ssme_gox_pos[0], 0.0, 1.0, SSME1_GOX_POS, parent );

	MGROUP_TRANSFORM* SSME1_VENT_POS = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(&ssme_vent_pos[0]), 1 );
	anim_ssme_vent_pos[0] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_vent_pos[0]", anim_ssme_vent_pos[0] );
	AddManagedAnimationComponent( anim_ssme_vent_pos[0], 0.0, 1.0, SSME1_VENT_POS, parent );


	static VECTOR3 dummy2p = _V( 0.0, 0.0, 1.0 );
	static VECTOR3 dummy2y = _V( 0.0, 0.0, 1.0 );
	MGROUP_ROTATE* SSME2_PITCH = new MGROUP_ROTATE( LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy2p), 1, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>((SSME_PITCH_MAX - SSME_PITCH_MIN) * RAD) );
	anim_ssme_pitch[1] = CreateAnimation( (SSME_INSTALL_PITCH[1] - SSME_PITCH_MIN) / (SSME_PITCH_MAX - SSME_PITCH_MIN) );
	LogAnim( "anim_ssme_pitch[1]", anim_ssme_pitch[1] );
	parent = AddManagedAnimationComponent( anim_ssme_pitch[1], 0.0, 1.0, SSME2_PITCH );

	MGROUP_ROTATE* SSME2_YAW = new MGROUP_ROTATE( LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy2y), 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>((SSME_YAW_MAX - SSME_YAW_MIN) * RAD) );
	anim_ssme_yaw[1] = CreateAnimation( (SSME_INSTALL_YAW[1] - SSME_YAW_MIN) / (SSME_YAW_MAX - SSME_YAW_MIN) );
	LogAnim( "anim_ssme_yaw[1]", anim_ssme_yaw[1] );
	parent = AddManagedAnimationComponent( anim_ssme_yaw[1], 0.0, 1.0, SSME2_YAW, parent );

	MGROUP_ROTATE* SSME2_ROLL = new MGROUP_ROTATE( mesh_ssme[1], NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), static_cast<float>(90.0 * RAD) );
	anim_ssme2_roll = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme2_roll", anim_ssme2_roll );
	parent = AddManagedAnimationComponent( anim_ssme2_roll, 0.0, 1.0, SSME2_ROLL, parent );
	SetAnimation( anim_ssme2_roll, 1.0 );

	MGROUP_TRANSFORM* SSME2_GOX_POS = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(&ssme_gox_pos[1]), 1 );
	anim_ssme_gox_pos[1] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_gox_pos[1]", anim_ssme_gox_pos[1] );
	AddManagedAnimationComponent( anim_ssme_gox_pos[1], 0.0, 1.0, SSME2_GOX_POS, parent );

	MGROUP_TRANSFORM* SSME2_VENT_POS = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(&ssme_vent_pos[1]), 1 );
	anim_ssme_vent_pos[1] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_vent_pos[1]", anim_ssme_vent_pos[1] );
	AddManagedAnimationComponent( anim_ssme_vent_pos[1], 0.0, 1.0, SSME2_VENT_POS, parent );


	static VECTOR3 dummy3p = _V( 0.0, 0.0, 1.0 );
	MGROUP_ROTATE* SSME3_PITCH = new MGROUP_ROTATE( LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy3p), 1, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>((SSME_PITCH_MAX - SSME_PITCH_MIN) * RAD) );
	anim_ssme_pitch[2] = CreateAnimation( (SSME_INSTALL_PITCH[2] - SSME_PITCH_MIN) / (SSME_PITCH_MAX - SSME_PITCH_MIN) );
	LogAnim( "anim_ssme_pitch[2]", anim_ssme_pitch[2] );
	parent = AddManagedAnimationComponent( anim_ssme_pitch[2], 0.0, 1.0, SSME3_PITCH );

	MGROUP_ROTATE* SSME3_YAW = new MGROUP_ROTATE( mesh_ssme[2], NULL, 0, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>((SSME_YAW_MAX - SSME_YAW_MIN) * RAD) );
	anim_ssme_yaw[2] = CreateAnimation( (SSME_INSTALL_YAW[2] - SSME_YAW_MIN) / (SSME_YAW_MAX - SSME_YAW_MIN) );
	LogAnim( "anim_ssme_yaw[2]", anim_ssme_yaw[2] );
	parent = AddManagedAnimationComponent( anim_ssme_yaw[2], 0.0, 1.0, SSME3_YAW, parent );

	MGROUP_TRANSFORM* SSME3_GOX_POS = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(&ssme_gox_pos[2]), 1 );
	anim_ssme_gox_pos[2] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_gox_pos[2]", anim_ssme_gox_pos[2] );
	AddManagedAnimationComponent( anim_ssme_gox_pos[2], 0.0, 1.0, SSME3_GOX_POS, parent );

	MGROUP_TRANSFORM* SSME3_VENT_POS = new MGROUP_TRANSFORM( LOCALVERTEXLIST, MAKEGROUPARRAY(&ssme_vent_pos[2]), 1 );
	anim_ssme_vent_pos[2] = CreateAnimation( 0.0 );
	LogAnim( "anim_ssme_vent_pos[2]", anim_ssme_vent_pos[2] );
	AddManagedAnimationComponent( anim_ssme_vent_pos[2], 0.0, 1.0, SSME3_VENT_POS, parent );

	// SBTCs
	static UINT LeftSBTC_GRP[1] = {GRP_LEFT_SBTC_VC};
	anim_leftsbtc = CreateAnimation( 0.6 );
	MGROUP_ROTATE* LeftSBTC = new MGROUP_ROTATE( mesh_vc, LeftSBTC_GRP, 1, _V( 0, 1.6685, 14.2797 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(60.0 * RAD) );
	parent = AddManagedAnimationComponent( anim_leftsbtc, 0.0, 1.0, LeftSBTC );

	static UINT LeftSBTCTO_GRP[1] = {GRP_LEFT_SBTC_TAKEOVER_VC};
	anim_leftsbtcto = CreateAnimation( 0.0 );
	MGROUP_TRANSLATE* LeftSBTCTO = new MGROUP_TRANSLATE( mesh_vc, LeftSBTCTO_GRP, 1, _V( -0.006, 0.0, 0.0 ) );
	AddManagedAnimationComponent( anim_leftsbtcto, 0.0, 1.0, LeftSBTCTO, parent );

	static UINT RightSBTC_GRP[1] = {GRP_RIGHT_SBTC_VC};
	anim_rightsbtc = CreateAnimation( 0.6 );
	MGROUP_ROTATE* RightSBTC = new MGROUP_ROTATE( mesh_vc, RightSBTC_GRP, 1, _V( 0, 1.621335, 14.255357 ), _V( 1.0, 0.0, 0.0 ), static_cast<float>(60.0 * RAD) );
	parent = AddManagedAnimationComponent( anim_rightsbtc, 0.0, 1.0, RightSBTC );

	static UINT RightSBTCTO_GRP[1] = {GRP_RIGHT_SBTC_TAKEOVER_VC};
	anim_rightsbtcto = CreateAnimation( 0.0 );
	MGROUP_TRANSLATE* RightSBTCTO = new MGROUP_TRANSLATE( mesh_vc, RightSBTCTO_GRP, 1, _V( -0.006, 0.0, 0.0 ) );
	AddManagedAnimationComponent( anim_rightsbtcto, 0.0, 1.0, RightSBTCTO, parent );

	// OMS
	MGROUP_ROTATE* LeftOMSPitch = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, L_OMS_REF, L_OMS_AXIS_PITCH, static_cast<float>(OMS_PITCH_RANGE * 2.0 * RAD) );
	anim_leftOMSpitch = CreateAnimation( 0.5 );
	LogAnim( "anim_leftOMSpitch", anim_leftOMSpitch );
	parent = AddManagedAnimationComponent( anim_leftOMSpitch, 0.0, 1.0, LeftOMSPitch );

	static UINT LeftOMS_Grp[2] = {GRP_OME_LEFT, GRP_OME_EYELID_LEFT};
	MGROUP_ROTATE* LeftOMSYaw = new MGROUP_ROTATE( midx, LeftOMS_Grp, 2, L_OMS_REF, L_OMS_AXIS_YAW, static_cast<float>(OMS_YAW_RANGE * 2.0 * RAD) );
	anim_leftOMSyaw = CreateAnimation( 0.5 );
	LogAnim( "anim_leftOMSyaw", anim_leftOMSyaw );
	AddManagedAnimationComponent( anim_leftOMSyaw, 0.0, 1.0, LeftOMSYaw, parent );


	MGROUP_ROTATE* RightOMSPitch = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, R_OMS_REF, R_OMS_AXIS_PITCH, static_cast<float>(OMS_PITCH_RANGE * 2.0 * RAD) );
	anim_rightOMSpitch = CreateAnimation( 0.5 );
	LogAnim( "anim_rightOMSpitch", anim_rightOMSpitch );
	parent = AddManagedAnimationComponent( anim_rightOMSpitch, 0.0, 1.0, RightOMSPitch );

	static UINT RightOMS_Grp[2] = {GRP_OME_RIGHT, GRP_OME_EYELID_RIGHT};
	MGROUP_ROTATE* RightOMSYaw = new MGROUP_ROTATE( midx, RightOMS_Grp, 2, R_OMS_REF, R_OMS_AXIS_YAW, static_cast<float>(OMS_YAW_RANGE * 2.0 * RAD) );
	anim_rightOMSyaw = CreateAnimation( 0.5 );
	LogAnim( "anim_rightOMSyaw", anim_rightOMSyaw );
	AddManagedAnimationComponent( anim_rightOMSyaw, 0.0, 1.0, RightOMSYaw, parent );

	EndLoggingAnims();
	return;
}

void Atlantis::DefineAttachments(const VECTOR3& ofs0)
{
	//// to parent ////
	// 0
	if (ahHDP) SetAttachmentParams( ahHDP, POS_HDP, _V( 0.0, 0.0, -1.0 ), _V( 0.0, 1.0, 0.0 ) );
	else ahHDP = CreateAttachment( true, POS_HDP, _V( 0.0, 0.0, -1.0 ), _V( 0.0, 1.0, 0.0 ), "XHDP" );

	// 1
	if (ahTow) SetAttachmentParams( ahTow, POS_TOW, _V( 0.0, 0.0749788, 0.997185 ), _V( 0.0, 0.997185, -0.0749787 ) );
	else ahTow = CreateAttachment( true, POS_TOW, _V( 0.0, 0.0749788, 0.997185 ), _V( 0.0, 0.997185, -0.0749787 ), "T" );


	//// to child ////
	// 0. port RMS / Payload MPM / SPDS
	if (pRMS) pRMS->CreateAttachment();
	else CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );

	// 1. stbd RMS / Payload MPM / SPDS
	if (pPLMPM) pPLMPM->CreateAttachment();
	else CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );

	/*
	MMU / airlock payload
	2. port
	3. stbd
	*/
	CreateAttachment( false, ofs0 + OFS_PORTMMU, _V( 1.0, 0.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), "XS" );
	CreateAttachment( false, ofs0 + OFS_STBDMMU, _V( -1.0, 0.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), "XS" );

	// 4
	/*eva_docking::ODS* pODS = dynamic_cast<eva_docking::ODS*>(pExtAirlock);
	if (pODS) pODS->UpdateODSAttachment();
	else */CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );

	/*
	Active (centerline) payloads
	5. Active payload 1
	6. Active payload 2
	7. Active payload 3
	8. Active payload 4
	9. Active payload 5
	*/
	for (unsigned int i = 0; i < 5; i++)
	{
		if (pActiveLatches[i]) pActiveLatches[i]->CreateAttachment();
		else CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );// dummy
	}

	/*
	Passive payloads:
	10. Passive payload 1
	11. Passive payload 2
	12. Passive payload 3
	13. Passive payload 4
	14. Passive payload 5

	Passive bay bridge payloads
	15. Passive bay bridge 1
	16. Passive bay bridge 2
	17. Passive bay bridge 3
	18. Passive bay bridge 4
	19. Passive bay bridge 5
	20. Passive bay bridge 6
	21. Passive bay bridge 7
	22. Passive bay bridge 8
	*/
	pPayloadBay->CreateAttachments();

	/*
	Large upper stage
	23. CISS / ASE IUS
	*/
	if (pASE_IUS) pASE_IUS->CreateAttachment();
	else if (pCISS) pCISS->CreateAttachment();
	else CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );

	/*
	Small upper stages
	24. Small upper stage 1
	25. Small upper stage 2
	26. Small upper stage 3
	*/
	// TODO
	CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );
	CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );
	CreateAttachment( false, _V( 0.0, 0.0, 0.0 ), _V( 1.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), "INVALID" );

	/*
	27. ET
	28. LSRB
	29. RSRB
	*/
	ahET = CreateAttachment( false, ET_OFFSET + ofs0, _V( 0.0, 1.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), "SSV_ET" );
	ahLeftSRB = CreateAttachment( false, LSRB_OFFSET + ofs0, _V( -1.0, 0.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), "SSV_SRB" );
	ahRightSRB = CreateAttachment( false, RSRB_OFFSET + ofs0, _V( -1.0, 0.0, 0.0 ), _V( 0.0, 0.0, 1.0 ), "SSV_SRB" );


#ifdef _DEBUG
	oapiWriteLogV( "(SSV_OV) [INFO] Attachment count: %d to parent, %d to child", AttachmentCount( true ), AttachmentCount( false ) );
#endif
	return;
}


void Atlantis::AddOrbiterVisual()
{
	huds.hudcnt = VC_HUDPOS_CDR;

	bHasODS = pMission->HasODS();
	bHasExtAL = pMission->HasExtAL();

	if (mesh_orbiter == MESH_UNDEFINED) {

		// ***** Load meshes
		mesh_vcexternal = AddMesh( hOrbiterVCExternalMesh, &VC_EXTERNAL_OFFSET );
		SetMeshVisibilityMode( mesh_vcexternal, MESHVIS_EXTERNAL );

		mesh_orbiter = AddMesh( hOrbiterMesh, &OFS_ZERO);
		SetMeshVisibilityMode( mesh_orbiter, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

		for (int i = 0; i < 3; i++)
		{
			mesh_ssme[i] = AddMesh( hSSMEMesh[i], &SSME_REF[i] );
			SetMeshVisibilityMode( mesh_ssme[i], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
		}

		// load correct vertical tail
		if (pMission->GetOrbiter() == "Columbia")
		{
			if (pMission->HasDragChute())
			{
				hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV102_DC );
				oapiWriteLog( "(SSV_OV) [INFO] OV-102 DC vertical tail mesh loaded" );
			}
			else
			{
				if (pMission->UseSILTS())
				{
					hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV102_SILTS );
					oapiWriteLog( "(SSV_OV) [INFO] OV-102 SILTS vertical tail mesh loaded" );
				}
				else
				{
					hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV102 );
					oapiWriteLog( "(SSV_OV) [INFO] OV-102 vertical tail mesh loaded" );
				}
			}
		}
		else if (pMission->GetOrbiter() == "Challenger")
		{
			hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV099 );
			oapiWriteLog( "(SSV_OV) [INFO] OV-099 vertical tail mesh loaded" );
		}
		else if ((pMission->GetOrbiter() == "Discovery") || (pMission->GetOrbiter() == "Atlantis"))
		{
			if (pMission->HasDragChute())
			{
				hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV105 );
				oapiWriteLog( "(SSV_OV) [INFO] OV-105 vertical tail mesh loaded" );
			}
			else
			{
				hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV099 );
				oapiWriteLog( "(SSV_OV) [INFO] OV-099 vertical tail mesh loaded" );
			}
		}
		else if (pMission->GetOrbiter() == "Endeavour")
		{
			hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV105 );
			oapiWriteLog( "(SSV_OV) [INFO] OV-105 vertical tail mesh loaded" );
		}
		else
		{
			// default to Challenger tail
			hVerticalTailMesh = oapiLoadMeshGlobal( MESHNAME_OV_VERTICALTAIL_OV099 );
			oapiWriteLog( "(SSV_OV) [INFO] default (OV-099) vertical tail mesh loaded" );
		}

		mesh_verticaltail = AddMesh( hVerticalTailMesh );
		SetMeshVisibilityMode( mesh_verticaltail, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
		oapiWriteLog( "(SSV_OV) [INFO] vertical tail mesh added" );

		/*if (pMission->HasOMSKit() == true)
		{
			hOMSKitMesh = oapiLoadMeshGlobal( MESHNAME_OMSKIT );
			mesh_OMSKit = AddMesh( hOMSKitMesh, &OMSKIT_OFFSET );
			SetMeshVisibilityMode( mesh_OMSKit, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
			oapiWriteLog( "OMS pallet mesh added" );
		}*/

		mesh_vc = AddMesh(hOrbiterVCMesh, &VC_OFFSET);
		SetMeshVisibilityMode(mesh_vc, MESHVIS_VC);

		mesh_middeck = AddMesh(hMidDeckMesh, &VC_OFFSET);
		//Only make visible when actually inside the mid deck
		bMidDeckVisible = false;
		SetMeshVisibilityMode(mesh_middeck, MESHVIS_NEVER);

		pgForward->AddMeshes( VC_OFFSET );
		pgForward->DefineVC();
		pgForward->DefineVCAnimations(mesh_vc);

		pgLeft->AddMeshes( VC_OFFSET );
		pgLeft->DefineVC();
		pgLeft->DefineVCAnimations(mesh_vc);

		pgCenter->AddMeshes( VC_OFFSET );
		pgCenter->DefineVC();
		pgCenter->DefineVCAnimations(mesh_vc);

		pgRight->AddMeshes( VC_OFFSET );
		pgRight->DefineVC();
		pgRight->DefineVCAnimations(mesh_vc);

		pgOverhead->AddMeshes( VC_OFFSET );
		pgOverhead->DefineVC();
		pgOverhead->DefineVCAnimations(mesh_vc);

		pgOverheadAft->AddMeshes( VC_OFFSET );
		pgOverheadAft->DefineVC();
		pgOverheadAft->DefineVCAnimations(mesh_vc);

		pgAftPort->AddMeshes( VC_OFFSET );
		pgAftPort->DefineVC();
		pgAftPort->DefineVCAnimations(mesh_vc);

		pgAft->AddMeshes( VC_OFFSET );
		pgAft->DefineVC();
		pgAft->DefineVCAnimations(mesh_vc);

		pgAftStbd->AddMeshes( VC_OFFSET );
		pgAftStbd->DefineVC();
		pgAftStbd->DefineVCAnimations(mesh_vc);

		huds.nmesh = mesh_vc;

		// ***** Attachment definitions
		DefineAttachments(OFS_ZERO);

		// ***** Cockpit camera definition

		SetCameraOffset(_V(-0.67, 2.55, 14.4));
		oapiVCRegisterHUD(&huds); // register changes in HUD parameters

		DefineAnimations();
	}
}

void Atlantis::SeparateBoosters(double met)
{
	//char buffer[120];

	double thrust_level, prop_level;
	GetSRBInterface( LEFT )->GetSRB_State( met, thrust_level, prop_level, SRBpc );
	prop_level = GetPropellantMass( ph_srb ) / GetPropellantMaxMass( ph_srb );

	DetachSRB( LEFT, thrust_level, prop_level );
	DetachSRB( RIGHT, thrust_level, prop_level );

	/*sprintf(buffer, "MG_Atlantis: Residual SRB propellant mass is %f kg\n", GetPropellantMass(ph_srb));
	oapiWriteLog(buffer);*/

	// Remove SRB's from Shuttle instance
	for (int i = 0; i < 2; i++)
	{
		if (pshSlag1[i]) DelExhaustStream( pshSlag1[i] );
		if (pshSlag2[i]) DelExhaustStream( pshSlag2[i] );
		if (pshSlag3[i]) DelExhaustStream( pshSlag3[i] );
		pshSlag1[i] = NULL;
		pshSlag2[i] = NULL;
		pshSlag3[i] = NULL;

		if (pshSRBFlame[i]) DelExhaustStream( pshSRBFlame[i] );
		if (pshSRBSmoke[i]) DelExhaustStream( pshSRBSmoke[i] );
		pshSRBFlame[i] = NULL;
		pshSRBSmoke[i] = NULL;
	}
	DelPropellantResource( ph_srb );
	DelThruster( th_srb[0] );
	DelThruster( th_srb[1] );

	// reconfigure
	SetOrbiterTankConfiguration();
	oapiWriteLog( "(SSV_OV) [INFO] SRBs separated" );

	//stop playing sound
	StopVesselWave( SoundID, SSME_RUNNING );

	// change ET texture
	OBJHANDLE hTank = GetAttachmentStatus( ahET );
	if (hTank)
	{
		VESSEL* vET = oapiGetVesselInterface( hTank );
		if (vET->Version() >= 2)
			((VESSEL3*)vET)->clbkGeneric( VMSG_USER + 0x0001, 0, NULL );
	}
	return;
}

void Atlantis::DetachSRB(SIDE side, double thrust, double prop)
{
	SRB* pSRB = GetSRBInterface(side);
	if (side == LEFT) DetachChildAndUpdateMass(ahLeftSRB);
	else DetachChildAndUpdateMass(ahRightSRB);
	pSRB->SetPostSeparationState(oapiGetSimTime() - met, thrust, prop);
}

void Atlantis::SeparateTank(void)
{
	DetachChildAndUpdateMass(ahET, 0.0);

	// create separate tanks for MPS dumps
	// using remaining mass in manifold to estimate LO2 & LH2 masses
	phLOXdump = CreatePropellantResource(LOXmass);
	phLH2dump = CreatePropellantResource(LH2mass);

	// re-map vents prop sources
	for (int i = 0; i < 3; i++)
	{
		if (thMPSDump[i] != NULL) SetThrusterResource( thMPSDump[i], phLOXdump );
	}
	if (thMPSDump[3] != NULL) SetThrusterResource( thMPSDump[3], phLH2dump );
	if (thMPSDump[4] != NULL) SetThrusterResource( thMPSDump[4], phLH2dump );
	if (thMPSDump[5] != NULL) SetThrusterResource( thMPSDump[5], phLOXdump );
	if (thMPSDump[6] != NULL) SetThrusterResource( thMPSDump[6], phLH2dump );
	if (thMPSDump[7] != NULL) SetThrusterResource( thMPSDump[7], phLOXdump );

	// delete joint mps manifold
	DelPropellantResource(ph_mps);

	// reconfigure
	SetOrbiterConfiguration();
}

ET* Atlantis::GetTankInterface() const
{
	OBJHANDLE hTank = GetAttachmentStatus(ahET);
	if (hTank)
		return static_cast<ET*>(oapiGetVesselInterface(hTank));
	return NULL;
}

SRB* Atlantis::GetSRBInterface(SIDE side) const
{
	OBJHANDLE hSRB = NULL;
	if (side == LEFT)
	{
		if (!ahLeftSRB) return NULL;
		hSRB = GetAttachmentStatus(ahLeftSRB);
	}
	else
	{
		if (!ahRightSRB) return NULL;
		hSRB = GetAttachmentStatus(ahRightSRB);
	}

	if (hSRB)
		return static_cast<SRB*>(oapiGetVesselInterface(hSRB));
	return NULL;
}

bool Atlantis::HydraulicsOK( void ) const
{
	return ((pAPU[0]->GetHydraulicPressure() >= 2800) || (pAPU[1]->GetHydraulicPressure() >= 2800) || (pAPU[2]->GetHydraulicPressure() >= 2800));
}

void Atlantis::GimbalOMS( unsigned int engine, double pitch, double yaw )
{
	assert( (engine <= 1) && "Atlantis::GimbalOMS.engine" );

	VECTOR3 dir = CalcOMSThrustDir( engine, pitch, yaw );

	SetThrusterDir( th_oms[engine], dir );

	if (engine == 0)
	{
		SetAnimation( anim_leftOMSpitch, (pitch + OMS_PITCH_RANGE) / (OMS_PITCH_RANGE * 2.0) );
		SetAnimation( anim_leftOMSyaw, (yaw + OMS_YAW_RANGE) / (OMS_YAW_RANGE * 2.0) );
	}
	else
	{
		SetAnimation( anim_rightOMSpitch, (pitch + OMS_PITCH_RANGE) / (OMS_PITCH_RANGE * 2.0) );
		SetAnimation( anim_rightOMSyaw, (yaw + OMS_YAW_RANGE) / (OMS_YAW_RANGE * 2.0) );
	}

	/*char cbuf[255];
	sprintf_s(cbuf, 255, "OMS DIR: %d %f %f %f", engine, dir.x, dir.y, dir.z);
	oapiWriteLog(cbuf);*/
	return;
}

double Atlantis::CalcNetSSMEThrust() const
{
	VECTOR3 N = _V(0, 0, 0), F, M;
	for (int i = 0; i < 3; i++) {
		GetThrusterMoment(th_ssme[i], F, M);
		N += F;
	}
	return length(N);
}

double Atlantis::GetSSMEISP() const
{
	return GetThrusterIsp(th_ssme[0]);
}

void Atlantis::CalcSSMEThrustAngles( unsigned int eng, double& degAngleP, double& degAngleY ) const
{
	assert( (eng <= 3) && "Atlantis::CalcSSMEThrustAngles.eng" );

	VECTOR3 N = _V(0, 0, 0);
	VECTOR3 dir = _V(0, 0, 0);
	if (eng == 0)
	{
		for (int i = 0; i < 3; i++) {
			GetThrusterRef(th_ssme[i], dir);
			dir = Normalize(-dir);
			N += dir*GetThrusterLevel(th_ssme[i]);
		}
	}
	else
	{
		GetThrusterRef(th_ssme[eng - 1], dir);
		N = -dir;
	}
	degAngleP = DEG*atan2(N.y, N.z);
	degAngleY = -DEG*atan2(cos(RAD*degAngleP) * N.x, N.z);
}

void Atlantis::ShowMidDeck()
{
	if (!bMidDeckVisible)
	{
		SetMeshVisibilityMode(mesh_middeck, MESHVIS_VC);
		bMidDeckVisible = true;
	}
}
void Atlantis::HideMidDeck()
{
	if (bMidDeckVisible)
	{
		SetMeshVisibilityMode(mesh_middeck, MESHVIS_NEVER);
		bMidDeckVisible = false;
	}
}

void Atlantis::ManLandingGearArm( void )
{
	LandingGearArm.SetLine();
	return;
}

void Atlantis::ManLandingGearDown( void )
{
	LandingGearDown.SetLine();
	return;
}

void Atlantis::DefineTouchdownPoints()
{
	switch (status)
	{
		//case STATE_PRELAUNCH:// set in first call to clbkPreStep() with exact pad/MLP elevation
		case STATE_STAGE1:
		case STATE_STAGE2:
			 {
				DWORD ntdvtx = 4;
				static TOUCHDOWNVTX tdvtx[4] = {
					{_V( 0, -10, -55.8 ), 1e5, 1e2, 0.5, 0.005},
					{_V( -7, 7, -55.8 ), 1e5, 1e2, 0.5, 0.005},
					{_V( 7, 7, -55.8 ), 1e5, 1e2, 0.5, 0.005},
					{_V( 0, 0, 20 ), 1e5, 1e2, 0.5}
				};
				SetTouchdownPoints( tdvtx, ntdvtx );
			 }
			break;
		case STATE_ORBITER:
			{
				DWORD ntdvtx = 11;
				static TOUCHDOWNVTX tdvtx[11];
				const double stiffness_MLG = 1e7;
				const double damping_MLG = 7e5;
				const double stiffness_NLG = 1e7;
				const double damping_NLG = 7e5;
				const double stiffness_other = 1e7;
				const double damping_other = 1e6;
				// points do not necessarily represent EXACT locations in order to decrease total point count
				// nose tip
				tdvtx[3].pos = _V( 0, -2.0295, 18.6573 ) + orbiter_ofs;
				tdvtx[3].stiffness = stiffness_other;
				tdvtx[3].damping = damping_other;
				tdvtx[3].mu = 1;
				//tdvtx[3].mu_lng = 0;
				// top of forward fuselage
				tdvtx[4].pos = _V( 0, 2.044398, 11.882727 ) + orbiter_ofs;
				tdvtx[4].stiffness = stiffness_other;
				tdvtx[4].damping = damping_other;
				tdvtx[4].mu = 1;
				//tdvtx[4].mu_lng = 0;
				// fwd top of tail
				tdvtx[5].pos = _V( 0, 10.158712, -16.740328 ) + orbiter_ofs;
				tdvtx[5].stiffness = stiffness_other;
				tdvtx[5].damping = damping_other;
				tdvtx[5].mu = 1;
				//tdvtx[5].mu_lng = 0;
				// aft top of tail
				tdvtx[6].pos = _V( 0, 10.158712, -18.880327 ) + orbiter_ofs;
				tdvtx[6].stiffness = stiffness_other;
				tdvtx[6].damping = damping_other;
				tdvtx[6].mu = 1;
				//tdvtx[6].mu_lng = 0;
				// BF LH tip
				tdvtx[7].pos = _V( -2.7904, -3.3344, -16.7121 ) + orbiter_ofs;
				tdvtx[7].stiffness = stiffness_other;
				tdvtx[7].damping = damping_other;
				tdvtx[7].mu = 1;
				//tdvtx[7].mu_lng = 0;
				// BF RH tip
				tdvtx[8].pos = _V( 2.7904, -3.3344, -16.7121 ) + orbiter_ofs;
				tdvtx[8].stiffness = stiffness_other;
				tdvtx[8].damping = damping_other;
				tdvtx[8].mu = 1;
				//tdvtx[8].mu_lng = 0;
				// LH wing tip
				tdvtx[9].pos = _V( -12.3260, -2.7311, -10.5948 ) + orbiter_ofs;
				tdvtx[9].stiffness = stiffness_other;
				tdvtx[9].damping = damping_other;
				tdvtx[9].mu = 1;
				//tdvtx[9].mu_lng = 0;
				// RH wing tip
				tdvtx[10].pos = _V( 12.3260, -2.7311, -10.5948 ) + orbiter_ofs;
				tdvtx[10].stiffness = stiffness_other;
				tdvtx[10].damping = damping_other;
				tdvtx[10].mu = 1;
				//tdvtx[10].mu_lng = 0;

				// TODO improve to allow points to move with individual gear motion
				if (aerosurfaces.LandingGear == 98.0)// HACK using gear aero position
				{// gear fully deployed
					// NLG (open)
					tdvtx[0].pos = _V( 0.0, -5.350457, 14.73767 ) + orbiter_ofs;
					tdvtx[0].stiffness = stiffness_NLG;
					tdvtx[0].damping = damping_NLG;
					tdvtx[0].mu = 2;
					tdvtx[0].mu_lng = 0.0175;
					// LH MLG (open)
					tdvtx[1].pos = _V( -3.454402, -6.681706, -5.542565 ) + orbiter_ofs;
					tdvtx[1].stiffness = stiffness_MLG;
					tdvtx[1].damping = damping_MLG;
					tdvtx[1].mu = 2;
					tdvtx[1].mu_lng = 0.0175;
					// RH MLG (open)
					tdvtx[2].pos = _V( 3.454402, -6.681706, -5.542565 ) + orbiter_ofs;
					tdvtx[2].stiffness = stiffness_MLG;
					tdvtx[2].damping = damping_MLG;
					tdvtx[2].mu = 2;
					tdvtx[2].mu_lng = 0.0175;
				}
				else
				{// belly landing
					// NLG area (closed)
					tdvtx[0].pos = _V( 0.0, -3.388465, 14.523001 ) + orbiter_ofs;
					tdvtx[0].stiffness = stiffness_other;
					tdvtx[0].damping = damping_other;
					tdvtx[0].mu = 1;
					tdvtx[0].mu_lng = 1;
					// LH MLG area (closed)
					tdvtx[1].pos = _V( -3.39985, -3.728588, -6.137314 ) + orbiter_ofs;
					tdvtx[1].stiffness = stiffness_other;
					tdvtx[1].damping = damping_other;
					tdvtx[1].mu = 1;
					tdvtx[1].mu_lng = 1;
					// RH MLG area (closed)
					tdvtx[2].pos = _V( 3.39985, -3.728588, -6.137314 ) + orbiter_ofs;
					tdvtx[2].stiffness = stiffness_other;
					tdvtx[2].damping = damping_other;
					tdvtx[2].mu = 1;
					tdvtx[2].mu_lng = 1;
				}

				SetTouchdownPoints( tdvtx, ntdvtx );
			}
			break;
	}

	return;
}

void Atlantis::ClearMeshes()
{
	VESSEL::ClearMeshes( true );
	mesh_orbiter = MESH_UNDEFINED;
	mesh_vcexternal = MESH_UNDEFINED;
	mesh_vc = MESH_UNDEFINED;
}

void Atlantis::EnableThrusters(const int Thrusters[], int nThrusters)
{
	for (int i = 0; i < nThrusters; i++)
	{
		switch (Thrusters[i])
		{
			case 0:
			case 3:
			case 6:
			case 8:
			case 10:
			case 13:
				SetThrusterResource(th_att_rcs[Thrusters[i]], ph_frcs);
				break;
			case 1:
			case 4:
			case 7:
			case 11:
			case 14:
				SetThrusterResource(th_att_rcs[Thrusters[i]], ph_lrcs);
				break;
			case 2:
			case 5:
			case 9:
			case 12:
			case 15:
				SetThrusterResource(th_att_rcs[Thrusters[i]], ph_rrcs);
				break;
		}
	}
}

void Atlantis::DisableThrusters(const int Thrusters[], int nThrusters)
{
	for (int i = 0; i < nThrusters; i++) {
		SetThrusterResource(th_att_rcs[Thrusters[i]], NULL);
	}
}

void Atlantis::UpdateTranslationForces()
{
	TransForce[0].x = GetThrusterGroupMaxThrust(thg_transfwd);
	TransForce[1].x = GetThrusterGroupMaxThrust(thg_transaft);
	TransForce[0].y = GetThrusterGroupMaxThrust(thg_transright);
	TransForce[1].y = GetThrusterGroupMaxThrust(thg_transleft);
	TransForce[0].z = GetThrusterGroupMaxThrust(thg_transdown);
	TransForce[1].z = GetThrusterGroupMaxThrust(thg_transup);
}

double Atlantis::GetThrusterGroupMaxThrust(THGROUP_HANDLE thg) const
{
	VECTOR3 Total = _V(0.0, 0.0, 0.0), Dir;
	for (DWORD i = 0; i < GetGroupThrusterCount(thg); i++) {
		THRUSTER_HANDLE th = GetGroupThruster(thg, i);
		GetThrusterDir(th, Dir);
		Total += Dir*GetThrusterMax0(th);
	}
	return length(Total);
}

double Atlantis::GetPropellantLevel(PROPELLANT_HANDLE ph) const
{
	return 100.0*(GetPropellantMass(ph) / GetPropellantMaxMass(ph));
}

void Atlantis::UpdateControllers( double dt )
{
	// RHC and THC input (RMS included)
	if (ControlRMS)
	{
		// use RHC/THC input to control RMS

		// kill FCS input
		for (int i = 0; i < 3; i++)
		{
			LeftRHC[i] = 0.0;
			RightRHC[i] = 0.0;
			AftRHC[i] = 0.0;

			LeftTHC[i] = 0;
			AftTHC[i] = 0;
		}
		for (int i = 0; i < 2; i++)
		{
			LeftRHCTrim[i] = 0;
			RightRHCTrim[i] = 0;
		}

		RMS_RHCInput[PITCH].SetLine( 5.0f * static_cast<float>(GetManualControlLevel( THGROUP_ATT_PITCHUP ) - GetManualControlLevel( THGROUP_ATT_PITCHDOWN )) );
		RMS_RHCInput[YAW].SetLine( 5.0f * static_cast<float>(GetManualControlLevel( THGROUP_ATT_YAWRIGHT ) - GetManualControlLevel( THGROUP_ATT_YAWLEFT )) );
		RMS_RHCInput[ROLL].SetLine( 5.0f * static_cast<float>(GetManualControlLevel( THGROUP_ATT_BANKRIGHT ) - GetManualControlLevel( THGROUP_ATT_BANKLEFT )) );
		if (GetAttitudeMode() == RCS_ROT) { // use arrow, Ins/Del keys for translation input
			RMS_THCInput[0].SetLine( 5.0f * static_cast<float>(THC_AltInput.x) );
			RMS_THCInput[1].SetLine( 5.0f * static_cast<float>(THC_AltInput.y) );
			RMS_THCInput[2].SetLine( 5.0f * static_cast<float>(THC_AltInput.z)) ;
		}
		else {
			RMS_THCInput[0].SetLine( 5.0f * static_cast<float>(GetManualControlLevel( THGROUP_ATT_BACK ) - GetManualControlLevel( THGROUP_ATT_FORWARD )) );
			RMS_THCInput[1].SetLine( 5.0f * static_cast<float>(GetManualControlLevel( THGROUP_ATT_RIGHT ) - GetManualControlLevel( THGROUP_ATT_LEFT )) );
			RMS_THCInput[2].SetLine( 5.0f * static_cast<float>(GetManualControlLevel( THGROUP_ATT_UP ) - GetManualControlLevel( THGROUP_ATT_DOWN )) );
		}

		// use RHC pitch commands to drive single joint input
		// in theory, these discrete lines should only be set if RMS is in SINGLE or DIRECT mode
		// in practice, RMS code only looks at these discrete lines if in appropriate mode
		if ((GetManualControlLevel( THGROUP_ATT_PITCHUP ) - GetManualControlLevel( THGROUP_ATT_PITCHDOWN )) > 0.5) {
			RMSDrivePlus.SetLine();
			RMSDriveMinus.ResetLine();
			lastRMSSJCommand = 1;
		}
		else if ((GetManualControlLevel( THGROUP_ATT_PITCHUP ) - GetManualControlLevel( THGROUP_ATT_PITCHDOWN )) < -0.5) {
			RMSDrivePlus.ResetLine();
			RMSDriveMinus.SetLine();
			lastRMSSJCommand = -1;
		}
		else {
			if (lastRMSSJCommand != 0) { // only reset lines once, so Panel A8 joint drive switch works
				RMSDrivePlus.ResetLine();
				RMSDriveMinus.ResetLine();
				lastRMSSJCommand = 0;
			}
		}
	}
	else
	{
		// use RHC/THC input to control FCS
		// TODO add option for MANCTRL_ANYMODE to allow simo RHC and THC inputs
		DWORD attrot = MANCTRL_ATTMODE;
		DWORD attlin = MANCTRL_ATTMODE;

		// kill RMS input
		for (int i = 0; i < 3; i++)
		{
			RMS_RHCInput[i].ResetLine();
			RMS_THCInput[i].ResetLine();
		}

		double pitch;
		double roll;
		double yaw;
		bool inOV = oapiGetFocusInterface() == this;

		// left RHC & THC
		if (inOV && (VCMode == VC_CDR))
		{
			// user is "here", use input
			pitch = GetManualControlLevel( THGROUP_ATT_PITCHUP, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_PITCHDOWN, attrot, MANCTRL_ANYDEVICE );
			roll = GetManualControlLevel( THGROUP_ATT_BANKRIGHT, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_BANKLEFT, attrot, MANCTRL_ANYDEVICE );
			yaw = GetManualControlLevel( THGROUP_ATT_YAWRIGHT, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_YAWLEFT, attrot, MANCTRL_ANYDEVICE );

			if (GetAttitudeMode() == RCS_ROT)
			{
				// use arrows and Ins and Del keys
				if (THC_AltInput.x == 1.0) LeftTHC[0] = 1;
				else if (THC_AltInput.x == -1.0) LeftTHC[0] = -1;
				else LeftTHC[0] = 0;

				if (THC_AltInput.y == 1.0) LeftTHC[1] = 1;
				else if (THC_AltInput.y == -1.0) LeftTHC[1] = -1;
				else LeftTHC[1] = 0;

				if (THC_AltInput.z == 1.0) LeftTHC[2] = 1;
				else if (THC_AltInput.z == -1.0) LeftTHC[2] = -1;
				else LeftTHC[2] = 0;
			}
			else
			{
				// use numpad keys
				if (GetManualControlLevel( THGROUP_ATT_BACK, attlin, MANCTRL_ANYDEVICE ) != 0.0) LeftTHC[0] = 1;
				else if (GetManualControlLevel( THGROUP_ATT_FORWARD, attlin, MANCTRL_ANYDEVICE ) != 0.0) LeftTHC[0] = -1;
				else LeftTHC[0] = 0;

				if (GetManualControlLevel( THGROUP_ATT_RIGHT, attlin, MANCTRL_ANYDEVICE ) != 0.0) LeftTHC[1] = 1;
				else if (GetManualControlLevel( THGROUP_ATT_LEFT, attlin, MANCTRL_ANYDEVICE ) != 0.0) LeftTHC[1] = -1;
				else LeftTHC[1] = 0;

				if (GetManualControlLevel( THGROUP_ATT_UP, attlin, MANCTRL_ANYDEVICE ) != 0.0) LeftTHC[2] = 1;
				else if (GetManualControlLevel( THGROUP_ATT_DOWN, attlin, MANCTRL_ANYDEVICE ) != 0.0) LeftTHC[2] = -1;
				else LeftTHC[2] = 0;
			}

			if (RHC_TrimUp) LeftRHCTrim[0] = 1;
			else if (RHC_TrimDown) LeftRHCTrim[0] = -1;
			else LeftRHCTrim[0] = 0;

			if (RHC_TrimRight) LeftRHCTrim[1] = 1;
			else if (RHC_TrimLeft) LeftRHCTrim[1] = -1;
			else LeftRHCTrim[1] = 0;
		}
		else
		{
			// empty seat, no input
			pitch = 0.0;
			roll = 0.0;
			yaw = 0.0;

			LeftRHCTrim[0] = 0;
			LeftRHCTrim[1] = 0;

			LeftTHC[0] = 0;
			LeftTHC[1] = 0;
			LeftTHC[2] = 0;
		}
		if (pitch > LeftRHC[0])
		{
			LeftRHC[0] += RHC_RATE * dt;
			if (LeftRHC[0] > pitch) LeftRHC[0] = pitch;
		}
		else if (pitch < LeftRHC[0])
		{
			LeftRHC[0] -= RHC_RATE * dt;
			if (LeftRHC[0] < pitch) LeftRHC[0] = pitch;
		}
		if (roll > LeftRHC[1])
		{
			LeftRHC[1] += RHC_RATE * dt;
			if (LeftRHC[1] > roll) LeftRHC[1] = roll;
		}
		else if (roll < LeftRHC[1])
		{
			LeftRHC[1] -= RHC_RATE * dt;
			if (LeftRHC[1] < roll) LeftRHC[1] = roll;
		}
		if (yaw > LeftRHC[2])
		{
			LeftRHC[2] += RHC_RATE * dt;
			if (LeftRHC[2] > yaw) LeftRHC[2] = yaw;
		}
		else if (yaw < LeftRHC[2])
		{
			LeftRHC[2] -= RHC_RATE * dt;
			if (LeftRHC[2] < yaw) LeftRHC[2] = yaw;
		}

		// right RHC
		if (inOV && (VCMode == VC_PLT))
		{
			// user is "here", use input
			pitch = GetManualControlLevel( THGROUP_ATT_PITCHUP, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_PITCHDOWN, attrot, MANCTRL_ANYDEVICE );
			roll = GetManualControlLevel( THGROUP_ATT_BANKRIGHT, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_BANKLEFT, attrot, MANCTRL_ANYDEVICE );
			yaw = GetManualControlLevel( THGROUP_ATT_YAWRIGHT, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_YAWLEFT, attrot, MANCTRL_ANYDEVICE );

			if (RHC_TrimUp) RightRHCTrim[0] = 1;
			else if (RHC_TrimDown) RightRHCTrim[0] = -1;
			else RightRHCTrim[0] = 0;

			if (RHC_TrimRight) RightRHCTrim[1] = 1;
			else if (RHC_TrimLeft) RightRHCTrim[1] = -1;
			else RightRHCTrim[1] = 0;
		}
		else
		{
			// empty seat, no input
			pitch = 0.0;
			roll = 0.0;
			yaw = 0.0;

			RightRHCTrim[0] = 0;
			RightRHCTrim[1] = 0;
		}
		if (pitch > RightRHC[0])
		{
			RightRHC[0] += RHC_RATE * dt;
			if (RightRHC[0] > pitch) RightRHC[0] = pitch;
		}
		else if (pitch < RightRHC[0])
		{
			RightRHC[0] -= RHC_RATE * dt;
			if (RightRHC[0] < pitch) RightRHC[0] = pitch;
		}
		if (roll > RightRHC[1])
		{
			RightRHC[1] += RHC_RATE * dt;
			if (RightRHC[1] > roll) RightRHC[1] = roll;
		}
		else if (roll < RightRHC[1])
		{
			RightRHC[1] -= RHC_RATE * dt;
			if (RightRHC[1] < roll) RightRHC[1] = roll;
		}
		if (yaw > RightRHC[2])
		{
			RightRHC[2] += RHC_RATE * dt;
			if (RightRHC[2] > yaw) RightRHC[2] = yaw;
		}
		else if (yaw < RightRHC[2])
		{
			RightRHC[2] -= RHC_RATE * dt;
			if (RightRHC[2] < yaw) RightRHC[2] = yaw;
		}

		// aft RHC & THC
		if (inOV && ((VCMode == VC_AFTPILOT) || (VCMode == VC_DOCKCAM)))
		{
			// user is "here", use input
			pitch = GetManualControlLevel( THGROUP_ATT_PITCHUP, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_PITCHDOWN, attrot, MANCTRL_ANYDEVICE );
			roll = GetManualControlLevel( THGROUP_ATT_BANKRIGHT, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_BANKLEFT, attrot, MANCTRL_ANYDEVICE );
			yaw = GetManualControlLevel( THGROUP_ATT_YAWRIGHT, attrot, MANCTRL_ANYDEVICE ) - GetManualControlLevel( THGROUP_ATT_YAWLEFT, attrot, MANCTRL_ANYDEVICE );

			// connections below are due to physical orientation of aft THC
			if (GetAttitudeMode() == RCS_ROT)
			{
				// use arrows and Ins and Del keys
				if (THC_AltInput.x == 1.0) AftTHC[0] = 1;
				else if (THC_AltInput.x == -1.0) AftTHC[0] = -1;
				else AftTHC[0] = 0;

				if (THC_AltInput.z == 1.0) AftTHC[1] = 1;
				else if (THC_AltInput.z == -1.0) AftTHC[1] = -1;
				else AftTHC[1] = 0;

				if (THC_AltInput.y == 1.0) AftTHC[2] = 1;
				else if (THC_AltInput.y == -1.0) AftTHC[2] = -1;
				else AftTHC[2] = 0;
			}
			else
			{
				// use numpad keys
				if (GetManualControlLevel( THGROUP_ATT_BACK, attlin, MANCTRL_ANYDEVICE ) != 0.0) AftTHC[0] = 1;
				else if (GetManualControlLevel( THGROUP_ATT_FORWARD, attlin, MANCTRL_ANYDEVICE ) != 0.0) AftTHC[0] = -1;
				else AftTHC[0] = 0;

				if (GetManualControlLevel( THGROUP_ATT_UP, attlin, MANCTRL_ANYDEVICE ) != 0.0) AftTHC[1] = 1;
				else if (GetManualControlLevel( THGROUP_ATT_DOWN, attlin, MANCTRL_ANYDEVICE ) != 0.0) AftTHC[1] = -1;
				else AftTHC[1] = 0;

				if (GetManualControlLevel( THGROUP_ATT_LEFT, attlin, MANCTRL_ANYDEVICE ) != 0.0) AftTHC[2] = 1;
				else if (GetManualControlLevel( THGROUP_ATT_RIGHT, attlin, MANCTRL_ANYDEVICE ) != 0.0) AftTHC[2] = -1;
				else AftTHC[2] = 0;
			}
		}
		else
		{
			// empty seat, no input
			pitch = 0.0;
			roll = 0.0;
			yaw = 0.0;

			AftTHC[0] = 0;
			AftTHC[1] = 0;
			AftTHC[2] = 0;
		}
		if (pitch > AftRHC[0])
		{
			AftRHC[0] += RHC_RATE * dt;
			if (AftRHC[0] > pitch) AftRHC[0] = pitch;
		}
		else if (pitch < AftRHC[0])
		{
			AftRHC[0] -= RHC_RATE * dt;
			if (AftRHC[0] < pitch) AftRHC[0] = pitch;
		}
		if (roll > AftRHC[1])
		{
			AftRHC[1] += RHC_RATE * dt;
			if (AftRHC[1] > roll) AftRHC[1] = roll;
		}
		else if (roll < AftRHC[1])
		{
			AftRHC[1] -= RHC_RATE * dt;
			if (AftRHC[1] < roll) AftRHC[1] = roll;
		}
		if (yaw > AftRHC[2])
		{
			AftRHC[2] += RHC_RATE * dt;
			if (AftRHC[2] > yaw) AftRHC[2] = yaw;
		}
		else if (yaw < AftRHC[2])
		{
			AftRHC[2] -= RHC_RATE * dt;
			if (AftRHC[2] < yaw) AftRHC[2] = yaw;
		}
	}

	// RPTA input
	double RPTAtmp = 0.0;
	if ((VCMode == VC_CDR) || (VCMode == VC_PLT)) RPTAtmp = RPTA_Input;
	if (RPTAtmp > RPTAs)
	{
		RPTAs += RPTA_RATE * dt;
		if (RPTAs > RPTAtmp) RPTAs = RPTAtmp;
	}
	else if (RPTAtmp < RPTAs)
	{
		RPTAs -= RPTA_RATE * dt;
		if (RPTAs < RPTAtmp) RPTAs = RPTAtmp;
	}

	// SBTC input
	LeftSBTCTO = false;
	RightSBTCTO = false;
	if (VCMode == VC_CDR)
	{
		LeftSBTC = range( 0.0, LeftSBTC + SBTC_Input, 1.0 );
		LeftSBTCTO = SBTCTO_Input;
	}
	else if (VCMode == VC_PLT)
	{
		RightSBTC = range( 0.0, RightSBTC + SBTC_Input, 1.0 );
		RightSBTCTO = SBTCTO_Input;
	}
	SBTC_Input = 0.0;

	SetAnimation( anim_leftsbtc, LeftSBTC );
	SetAnimation( anim_leftsbtcto, LeftSBTCTO ? 1.0 : 0.0 );
	SetAnimation( anim_rightsbtc, RightSBTC );
	SetAnimation( anim_rightsbtcto, RightSBTCTO ? 1.0 : 0.0 );


	// brake input
	if (VCMode == VC_CDR)
	{
		BrakeCDR[0] = range( 0.0, BrakeCDR[0] + ((LeftBrake_Input * 2.0) - 1.0) * BRAKE_RATE * dt, 1.0 );
		BrakeCDR[1] = range( 0.0, BrakeCDR[1] + ((RightBrake_Input * 2.0) - 1.0) * BRAKE_RATE * dt, 1.0 );
		BrakePLT[0] = 0.0;
		BrakePLT[1] = 0.0;
	}
	else if (VCMode == VC_PLT)
	{
		BrakeCDR[0] = 0.0;
		BrakeCDR[1] = 0.0;
		BrakePLT[0] = range( 0.0, BrakePLT[0] + ((LeftBrake_Input * 2.0) - 1.0) * BRAKE_RATE * dt, 1.0 );
		BrakePLT[1] = range( 0.0, BrakePLT[1] + ((RightBrake_Input * 2.0) - 1.0) * BRAKE_RATE * dt, 1.0 );
	}
	else
	{
		BrakeCDR[0] = 0.0;
		BrakeCDR[1] = 0.0;
		BrakePLT[0] = 0.0;
		BrakePLT[1] = 0.0;
	}
	return;
}

bool Atlantis::RegisterMDU(unsigned short usMDUID, vc::MDU* pMDU)
{
	assert( (usMDUID < 11) && "Atlantis::RegisterMDU.usMDUID" );

	if (mdus[usMDUID] != NULL)
	{
		return false;
	}
	else {
		mdus[usMDUID] = pMDU;
		return true;
	}
}

void Atlantis::GetRHCPosition( unsigned short ID, double& Pitch, double& Roll, double& Yaw, short& TrimPitch, short& TrimRoll ) const
{
	if (ID == 1)// left
	{
		Pitch = LeftRHC[0];
		Roll = LeftRHC[1];
		Yaw = LeftRHC[2];
		TrimPitch = LeftRHCTrim[0];
		TrimRoll = LeftRHCTrim[1];
	}
	else if (ID == 2)// right
	{
		Pitch = RightRHC[0];
		Roll = RightRHC[1];
		Yaw = RightRHC[2];
		TrimPitch = RightRHCTrim[0];
		TrimRoll = RightRHCTrim[1];
	}
	else if (ID == 3)// aft
	{
		Pitch = AftRHC[0];
		Roll = AftRHC[1];
		Yaw = AftRHC[2];
	}
	return;
}

void Atlantis::GetTHCPosition( unsigned short ID, short& X, short& Y, short& Z ) const
{
	if (ID == 1)// left
	{
		X = LeftTHC[0];
		Y = LeftTHC[1];
		Z = LeftTHC[2];
	}
	else if (ID == 3)// aft
	{
		X = AftTHC[0];
		Y = AftTHC[1];
		Z = AftTHC[2];
	}
	return;
}

void Atlantis::GetRPTAPosition( double& pos ) const
{
	pos = RPTAs;
	return;
}

void Atlantis::GetSBTCPosition( unsigned short ID, double& pos, bool& TO ) const
{
	if (ID == 1)// left
	{
		pos = LeftSBTC;
		TO = LeftSBTCTO;
	}
	else if (ID == 2)// right
	{
		pos = RightSBTC;
		TO = RightSBTCTO;
	}
	return;
}

void Atlantis::GetBrakePosition( double& CDRLeft, double& CDRRight, double& PLTLeft, double& PLTRight ) const
{
	CDRLeft = BrakeCDR[0];
	CDRRight = BrakeCDR[1];
	PLTLeft = BrakePLT[0];
	PLTRight = BrakePLT[1];
	return;
}

bool Atlantis::SetSSMEParams(unsigned short usMPSNo, double fThrust0, double fISP0, double fISP1)
{
	assert( (usMPSNo > 0) && (usMPSNo <= 3) && "Atlantis::SetSSMEParams.usMPSNo" );

	SetThrusterMax0(th_ssme[usMPSNo - 1], fThrust0);
	SetThrusterIsp(th_ssme[usMPSNo - 1], fISP0, fISP1);
	return true;
}

bool Atlantis::SetSSMEGimbalAngles( unsigned usMPSNo, double degPitch, double degYaw )
{
	assert( (usMPSNo < 3) && "Atlantis::SetSSMEGimbalAngles.usMPSNo" );

	double anim_yaw = linterp( SSME_YAW_MIN, 0.0, SSME_YAW_MAX, 1.0, degYaw );
	double anim_pitch;

	switch (usMPSNo)
	{
		case 0:
			anim_pitch = linterp( SSME_INSTALL_PITCH[0], 0.0, SSME_PITCH_MAX, 1.0, degPitch );
			break;
		case 1:
			anim_pitch = linterp( SSME_PITCH_MIN, 0.0, SSME_PITCH_MAX, 1.0, degPitch );
			break;
		case 2:
			anim_pitch = linterp( SSME_PITCH_MIN, 0.0, SSME_PITCH_MAX, 1.0, degPitch );
			break;
		default:
			return false;
	}

	// set animation
	SetAnimation( anim_ssme_yaw[usMPSNo], anim_yaw );
	SetAnimation( anim_ssme_pitch[usMPSNo], anim_pitch );

	// set thruster and vents direction
	VECTOR3 dir = RotateVectorX( _V( 0.0, 0.0, 1.0 ), -(degPitch - SSME_INSTALL_PITCH[usMPSNo]) );
	ssme_dir[usMPSNo] = RotateVectorY( dir, -(degYaw - SSME_INSTALL_YAW[usMPSNo]) );
	SetThrusterDir( th_ssme[usMPSNo], ssme_dir[usMPSNo] );
	SetThrusterDir( th_ssme_gox[usMPSNo], ssme_dir[usMPSNo] );
	SetThrusterDir( thMPSDump[usMPSNo], ssme_dir[usMPSNo] );

	// set vents position
	// TODO calc positions here instead of relying on LOCALVERTEXLIST, which only runs when vessel is in view
	SetThrusterRef( th_ssme_gox[usMPSNo], orbiter_ofs + SSME_REF[usMPSNo] + ssme_gox_pos[usMPSNo] );
	SetThrusterRef( thMPSDump[usMPSNo], orbiter_ofs + SSME_REF[usMPSNo] + ssme_vent_pos[usMPSNo] );
	return true;
}

bool Atlantis::SetSSMEThrustLevel(unsigned short usMPSNo, double fThrustLevel)
{
	assert( (usMPSNo > 0) && (usMPSNo <= 3) && "Atlantis::SetSSMEThrustLevel.usMPSNo" );

	SetThrusterLevel(th_ssme[usMPSNo - 1], fThrustLevel / SSME_MAX_POWER_LEVEL);
	return true;
}

double Atlantis::GetSSMEThrustLevel(unsigned short usMPSNo)
{
	assert( (usMPSNo <= 3) && "Atlantis::GetSSMEThrustLevel.usMPSNo" );

	if (usMPSNo == 0) return (GetSSMEThrustLevel(1) + GetSSMEThrustLevel(2) + GetSSMEThrustLevel(3)) / 3.0; // return average thrust
	return GetThrusterLevel(th_ssme[usMPSNo - 1])*SSME_MAX_POWER_LEVEL;
}

void Atlantis::SetSRBGimbalAngles(SIDE SRB, double degPitch, double degYaw)
{
	VECTOR3 dir = RotateVectorX(SRBNullDirection[SRB], range(-5.0, degPitch, 5.0));
	dir = RotateVectorY(dir, range(-5.0, degYaw, 5.0));
	SetThrusterDir(th_srb[SRB], dir);
}

void Atlantis::IgniteSRBs()
{
	double thrust_level, prop_level;
	GetSRBInterface( LEFT )->GetSRB_State( 0.0, thrust_level, prop_level, SRBpc );
	for (int i = 0; i < 2; i++)
		SetThrusterLevel(th_srb[i], thrust_level);

	status = STATE_STAGE1;
	return;
}

void Atlantis::SetMPSDumpLevel( unsigned int vent, double level )
{
	assert((vent <= 7) && " Atlantis::SetMPSDumpLevel.vent");
	assert((level >= 0) && (level <= 1) && " Atlantis::SetMPSDumpLevel.level");
	if (thMPSDump[vent] != NULL) SetThrusterLevel(thMPSDump[vent], level);
	return;
}

void Atlantis::SetSSMEGH2burn(int eng, bool burn)
{
	assert((eng >= 1) && (eng <= 3) && " Atlantis::SetSSMEGH2burn.eng");
	if (SSMEGH2burn[eng - 1] != NULL) DelExhaustStream(SSMEGH2burn[eng - 1]);

	if (burn == false)
	{
		SSMEGH2burn[eng - 1] = NULL;
		return;
	}

	static PARTICLESTREAMSPEC psSSMEGH2burn = {
		0,
		1,
		40,
		35,
		0.4,
		0.2,
		5,
		5,
		PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_FLAT,
		1, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};
	if (GetAtmPressure() > 25000)
	{
		//psSSMEGH2burn.srcrate = 40;
		//psSSMEGH2burn.growthrate = 5;
		//psSSMEGH2burn.levelmap = PARTICLESTREAMSPEC::LVL_FLAT;
		psSSMEGH2burn.tex = oapiRegisterParticleTexture("SSV\\OV\\SSMEstream");
	}
	else
	{
		psSSMEGH2burn.srcrate = 80;
		psSSMEGH2burn.growthrate = 15;
		psSSMEGH2burn.levelmap = PARTICLESTREAMSPEC::LVL_LIN;
		psSSMEGH2burn.tex = 0;
	}

	SSMEGH2burn[eng - 1] = AddExhaustStream( th_ssme[eng - 1], orbiter_ofs + SSME_REF[eng - 1] + ssme_vent_pos[eng - 1], &psSSMEGH2burn );
	return;
}

double Atlantis::GetSRBChamberPressure( void )
{
	if (status > STATE_STAGE1) return 0.0;

	return SRBpc;
}

unsigned short Atlantis::GetGPCMET(unsigned short usGPCID, unsigned short &usDay, unsigned short &usHour, unsigned short &usMin, unsigned short &usSec)
{
	usDay = pMTU->GetMETDay(0);
	usHour = pMTU->GetMETHour(0);
	usMin = pMTU->GetMETMin(0);
	usSec = pMTU->GetMETSec(0);
	return 0;
}

short Atlantis::GetETPropellant() const
{
	ET* et = GetTankInterface();

	if (et != NULL) return min((short)et->GetPropellantLevel(), 99);
	else return -1;
}

double Atlantis::GetETPropellant_B(void) const
{
	ET* et = GetTankInterface();

	if (et != NULL) return et->GetPropellantLevel();
	else return -1;
}

double Atlantis::GetETLOXUllagePressure(void) const
{
	ET* et = GetTankInterface();

	if (et != NULL) return et->GetLOXUllagePressure();
	else return 0;
}

double Atlantis::GetETLH2UllagePressure(void) const
{
	ET* et = GetTankInterface();

	if (et != NULL) return et->GetLH2UllagePressure();
	else return 0;
}

dps::IDP* Atlantis::GetIDP(unsigned short usIDPNumber) const
{
	assert( (usIDPNumber >= 1) && (usIDPNumber <= 4) && "Atlantis::GetIDP.usIDPNumber" );
	return pIDP[usIDPNumber - 1];
}

vc::MDU* Atlantis::GetMDU(unsigned short usMDUID) const
{
	if (usMDUID >= 11) return NULL;
	return mdus[usMDUID];
}

void Atlantis::CreateSSMEs(const VECTOR3 &ofs)
{
	if (!bSSMEsDefined) {
		th_ssme[0] = CreateThruster(ofs + SSME_REF[0], ssme_dir[0], SSME_THRUST, ph_mps, SSME_ISP0, SSME_ISP1);
		th_ssme[1] = CreateThruster(ofs + SSME_REF[1], ssme_dir[1], SSME_THRUST, ph_mps, SSME_ISP0, SSME_ISP1);
		th_ssme[2] = CreateThruster(ofs + SSME_REF[2], ssme_dir[2], SSME_THRUST, ph_mps, SSME_ISP0, SSME_ISP1);

		CreateMPSGOXVents( ofs );
		CreateMPSDumpVents( ofs );
		DefineSSMEExhaust();

		bSSMEsDefined = true;
	}

	// calculate null direction for each engine
	UpdateNullDirections();
}

void Atlantis::DefineSSMEExhaust()
{
	int i;

	SURFHANDLE tex_main = oapiRegisterExhaustTexture("SSV\\OV\\SSME_exhaust");
	for (i = 0; i < 3; i++)
	{
		ex_main[i] = AddExhaust(th_ssme[i], 55.0, 3.0, 3.5, tex_main);
	}
}

void Atlantis::UpdateNullDirections()
{
	// calculate null direction for each engine
	if (status <= STATE_STAGE1) {
		for (unsigned short i = 0; i < 2; i++) {
			if (th_srb[i]) {
				GetThrusterRef(th_srb[i], SRBNullDirection[i]);
				SRBNullDirection[i].x = 0.0; // keep both SRBs pointing up without any gimballing left/right (otherwise, we get some losses fomr both SRBs thrusting in opposing directions)
				SRBNullDirection[i] = Normalize(-SRBNullDirection[i]);
				SetThrusterDir(th_srb[i], SRBNullDirection[i]);
			}
		}
	}
}

unsigned int Atlantis::GetGPCMajorMode() const
{
	return pSimpleGPC->GetMajorMode();
}

double Atlantis::GetMET() const
{
	return met;
}

void Atlantis::CreateOrbiterTanks()
{
	if (ph_loms) return;// create tanks only once

	ph_loms = CreatePropellantResource( ORBITER_MAX_OMS_PROPELLANT_MASS );
	ph_roms = CreatePropellantResource( ORBITER_MAX_OMS_PROPELLANT_MASS );
	ph_koms = CreatePropellantResource( 1.0 );// dummy tank for OMS kit (TODO max mass updated when OMS kit installed)
	ph_frcs = CreatePropellantResource( ORBITER_FRCS_PROPELLANT_MASS );
	ph_lrcs = CreatePropellantResource( ORBITER_LEFT_ARCS_PROPELLANT_MASS );
	ph_rrcs = CreatePropellantResource( ORBITER_RIGHT_ARCS_PROPELLANT_MASS );
}

void Atlantis::AddPrimaryRCSExhaust(THRUSTER_HANDLE thX)
{
	VECTOR3 pos, dir;
	GetThrusterRef(thX, pos);
	GetThrusterDir(thX, dir);
	AddRCSExhaust(thX, pos, -dir);
}

void Atlantis::AddVernierRCSExhaust(THRUSTER_HANDLE thX)
{
	VECTOR3 pos, dir;
	GetThrusterRef(thX, pos);
	GetThrusterDir(thX, dir);
	AddVRCSExhaust(thX, pos, -dir);
}

void Atlantis::DisplayCameraLabel(const char* pszLabel)
{
	if (!oapiCameraInternal()) return;
	strcpy(pszCameraLabelBuffer, pszLabel);
	oapiAnnotationSetText(nhCameraLabel, pszCameraLabelBuffer);
	fTimeCameraLabel = 5.0;
}

void Atlantis::CreateMPSGOXVents(const VECTOR3& ref_pos)
{
	int i;

	static PARTICLESTREAMSPEC gox_stream = {
		0, 0.03, 100, 10, 0, 0.8, 1.2, 1.35, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_FLAT, 1, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-50, 1
	};

	gox_stream.tex = oapiRegisterParticleTexture("contrail1");

	for (i = 0; i < 3; i++)
	{
		th_ssme_gox[i] = CreateThruster( ref_pos + SSME_REF[i] + ssme_gox_pos[i], ssme_dir[i], 0.0, ph_mps, 250.0, 100.0 );
		AddExhaustStream(th_ssme_gox[i], &gox_stream);
	}
	return;
}

void Atlantis::CreateMPSDumpVents( const VECTOR3& ofs )
{
	static PARTICLESTREAMSPEC psLOXdump_SSME = {
		0,
		1,
		80,
		20,
		0.4,
		0.4,
		10,
		5,
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PLIN,
		0, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};

	static PARTICLESTREAMSPEC psLOXdump_FD = {
		0,
		0.2,
		80,
		20,
		0.4,
		0.4,
		5,
		5,
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PLIN,
		0, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};

	static PARTICLESTREAMSPEC psLH2dump_BU = {
		0,
		0.0381,///<     particle size at creation [m]
		200,///<     average particle creation rate [Hz]
		15,///<     emission velocity [m/s]
		0.2,///<     velocity spread during creation
		0.3,///<     average particle lifetime [s]
		6,///<     particle growth rate [m/s]
		7,///<     slowdown rate in atmosphere
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PLIN,
		0, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};

	static PARTICLESTREAMSPEC psLH2dump_FD = {
		0,
		0.2,///<     particle size at creation [m]
		200,///<     average particle creation rate [Hz]
		15,///<     emission velocity [m/s]
		0.2,///<     velocity spread during creation
		0.35,///<     average particle lifetime [s]
		7,///<     particle growth rate [m/s]
		7,///<     slowdown rate in atmosphere
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PLIN,
		0, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};

	static PARTICLESTREAMSPEC psLH2dump_FDLN = {
		0,
		0.0254,///<     particle size at creation [m]
		200,///<     average particle creation rate [Hz]
		15,///<     emission velocity [m/s]
		0.1,///<     velocity spread during creation
		0.3,///<     average particle lifetime [s]
		2,///<     particle growth rate [m/s]
		7,///<     slowdown rate in atmosphere
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PLIN,
		0, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};

	static PARTICLESTREAMSPEC psLOXdump_FDLN = {
		0,
		0.0254,///<     particle size at creation [m]
		200,///<     average particle creation rate [Hz]
		20,///<     emission velocity [m/s]
		0.1,///<     velocity spread during creation
		0.4,///<     average particle lifetime [s]
		2,///<     particle growth rate [m/s]
		5,///<     slowdown rate in atmosphere
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PLIN,
		0, 1,
		PARTICLESTREAMSPEC::ATM_FLAT,
		1, 1,
		0
	};

	// LOX dump -> dv = 9-11 fps
	// LOX dump SSME
	for (int i = 0; i < 3; i++)
	{
		thMPSDump[i] = CreateThruster( ofs + SSME_REF[i] + ssme_vent_pos[i], ssme_dir[i], 4000, phLOXdump, 80, 80 );
		AddExhaustStream( thMPSDump[i], &psLOXdump_SSME );
	}

	// LH2 dump B/U
	thMPSDump[3] = CreateThruster( ofs + MPS_LH2_BU_DUMP_POS, MPS_LH2_BU_DUMP_DIR, 60, phLH2dump, 60, 60);
	AddExhaustStream(thMPSDump[3], &psLH2dump_BU);

	// LH2 dump F/D
	thMPSDump[4] = CreateThruster( ofs + MPS_LH2_FD_POS, MPS_LH2_FD_DIR, 90, phLH2dump, 30, 30);
	AddExhaustStream(thMPSDump[4], &psLH2dump_FD);

	// LOX dump F/D
	thMPSDump[5] = CreateThruster( ofs + MPS_LOX_FD_POS, MPS_LOX_FD_DIR, 600, phLOXdump, 60, 60);
	AddExhaustStream(thMPSDump[5], &psLOXdump_FD);

	// LH2 FDLN Relief vent
	thMPSDump[6] = CreateThruster( ofs + MPS_LH2_FDLN_RV_POS, MPS_LH2_FDLN_RV_DIR, 34, phLH2dump, 60, 60);
	AddExhaustStream(thMPSDump[6], &psLH2dump_FDLN);

	// LOX FDLN Relief vent
	thMPSDump[7] = CreateThruster( ofs + MPS_LOX_FDLN_RV_POS, MPS_LOX_FDLN_RV_DIR, 331, phLOXdump, 60, 60);
	AddExhaustStream(thMPSDump[7], &psLOXdump_FDLN);
	return;
}

void Atlantis::RealizeSubsystemConnections( void )
{
	discsignals::DiscreteBundle* pBundle = bundleManager->CreateBundle("THRUSTER_CMD", 16);
	for (unsigned int i = 0; i < 3; i++) {
		RotThrusterCommands[i].Connect(pBundle, i);
		TransThrusterCommands[i].Connect(pBundle, i + 3);

		// at start, make sure lines are set to 0;
		DiscOutPort temp;
		temp.Connect(pBundle, i);
		temp.ResetLine();
		temp.Connect(pBundle, i + 3);
		temp.ResetLine();
	}
	RotThrusterCommands[3].Connect(pBundle, 6);// SERC RCS thrusters

	pBundle = bundleManager->CreateBundle("RMS_EE", 16);
	RMSGrapple.Connect(pBundle, 0);
	RMSRelease.Connect(pBundle, 1);

	pBundle = bundleManager->CreateBundle("RMS_HC_INPUT", 16);
	for (int i = 0; i < 3; i++) {
		RMS_RHCInput[i].Connect(pBundle, i);
		RMS_THCInput[i].Connect(pBundle, i + 3);
	}



	pBundle = bundleManager->CreateBundle("RMS_MODE", 16);
	RMSCoarseRateIn.Connect(pBundle, 12);
	RMSCoarseRateOut.Connect(pBundle, 12);

	pBundle = bundleManager->CreateBundle("RMS_SINGLE_JOINT", 16);
	RMSDrivePlus.Connect(pBundle, 8);
	RMSDriveMinus.Connect(pBundle, 9);

	pBundle = bundleManager->CreateBundle( "C3_LIMITS_SSMEPB", 6 );
	for (int i = 0; i < 3; i++) SSMEPBAnalog[i].Connect( pBundle, i + 3 );

	pBundle = bundleManager->CreateBundle("ET_LOX_SENSORS", 16);
	LO2LowLevelSensor[0].Connect(pBundle, 0);
	LO2LowLevelSensor[1].Connect(pBundle, 1);
	LO2LowLevelSensor[2].Connect(pBundle, 2);
	LO2LowLevelSensor[3].Connect(pBundle, 3);

	// ports for manual camera pan/tilt (inside camera vc position)
	pBundle = bundleManager->CreateBundle( "CameraManControl", 16 );
	PLBCamPanLeft_Man.Connect( pBundle, 0 );
	PLBCamPanRight_Man.Connect( pBundle, 1 );
	PLBCamTiltUp_Man.Connect( pBundle, 2 );
	PLBCamTiltDown_Man.Connect( pBundle, 3 );

	pBundle = bundleManager->CreateBundle( "LANDING_GEAR", 16 );
	LandingGearArm.Connect( pBundle, 1 );
	LandingGearDown.Connect( pBundle, 3 );


	// simple shuttle bus connections
	pSimpleBus->ConnectTo( pSimpleGPC, 1 );
	pSimpleBus->ConnectTo( pEIU[0], 17 );
	pSimpleBus->ConnectTo( pEIU[1], 23 );
	pSimpleBus->ConnectTo( pEIU[2], 24 );
	pSimpleBus->ConnectTo( pHUD[0], 6 );
	pSimpleBus->ConnectTo( pHUD[1], 9 );
	pSimpleBus->ConnectTo( pSimpleMDM_FF1, 25 );
	pSimpleBus->ConnectTo( pSimpleMDM_FF2, 26 );
	pSimpleBus->ConnectTo( pSimpleMDM_FF3, 27 );
	pSimpleBus->ConnectTo( pSimpleMDM_FF4, 28 );
	pSimpleBus->ConnectTo( pSimpleMDM_FA1, 19 );
	pSimpleBus->ConnectTo( pSimpleMDM_FA2, 20 );
	pSimpleBus->ConnectTo( pSimpleMDM_FA3, 21 );
	pSimpleBus->ConnectTo( pSimpleMDM_FA4, 22 );
	pSimpleBus->ConnectTo( pSimpleMDM_PF1, 29 );
	pSimpleBus->ConnectTo( pSimpleMDM_PF2, 30 );
	pSimpleBus->ConnectTo( pSimpleMDM_OF1, 10 );
	pSimpleBus->ConnectTo( pSimpleMDM_OF2, 11 );
	pSimpleBus->ConnectTo( pSimpleMDM_OF3, 12 );
	pSimpleBus->ConnectTo( pSimpleMDM_OF4, 13 );
	pSimpleBus->ConnectTo( pSimpleMDM_OA1, 14 );
	pSimpleBus->ConnectTo( pSimpleMDM_OA2, 15 );
	pSimpleBus->ConnectTo( pSimpleMDM_OA3, 16 );
	return;
}

void Atlantis::SetGMTLO( double GMTLO )
{
	pRSLS->SetGMTLO( GMTLO );
	return;
}

void Atlantis::SetGMTLOSetCommandFlag( bool val )
{
	pRSLS->SetGMTLOSetCommandFlag( val );
	return;
}

void Atlantis::SetLPSCountdownHoldFlag( bool val )
{
	pRSLS->SetLPSCountdownHoldFlag( val );
	return;
}

void Atlantis::SetLPSGoForAutoSequenceStartFlag( bool val )
{
	pRSLS->SetLPSGoForAutoSequenceStartFlag( val );
	return;
}

void Atlantis::SetLPSGoForEngineStartFlag( bool val )
{
	pRSLS->SetLPSGoForEngineStartFlag( val );
	return;
}

void Atlantis::SetResumeCountCommandFlag( bool val )
{
	pRSLS->SetResumeCountCommandFlag( val );
	return;
}

bool Atlantis::GetRSCountdownHoldFlag( void ) const
{
	return pRSLS->GetRSCountdownHoldFlag();
}

bool Atlantis::GetLaunchSequenceAbortFlag( void ) const
{
	return pRSLS->GetLaunchSequenceAbortFlag();
}

void Atlantis::PSN4( void )
{
	pEIU[0]->command(0xBC00);
	pEIU[1]->command(0xBC00);
	pEIU[2]->command(0xBC00);
}

void Atlantis::SetSSMEActPos( int num, double Ppos, double Ypos )
{
	pMPS_ATVC_CMD_SOP->SetSSMEActPos( num, Ppos, Ypos );
	return;
}

unsigned int Atlantis::GetHoldFlags( void ) const
{
	return pRSLS->GetHoldFlags();
}

double Atlantis::GetHydSysPress( int sys ) const
{
	assert( (sys >= 1) && (sys <= 3) && "Atlantis::GetHydSysPress" );
	return pAPU[sys - 1]->GetHydraulicPressure();
}

int Atlantis::GetSSMEPress(int eng)
{
	return pSSME_SOP->GetPercentChamberPressVal(eng);
}

int Atlantis::GetHeTankPress(int sys) const
{
	assert((sys >= 0) && (sys <= 3) && "Atlantis::GetHeTankPress");
	if (sys == 0) return pHePneu->GetTankPress();
	return pHeEng[sys - 1]->GetTankPress();
}

int Atlantis::GetHeRegPress(int sys) const
{
	assert((sys >= 0) && (sys <= 3) && "Atlantis::GetHeRegPress");
	if (sys == 0) return pHePneu->GetRegPress();
	return pHeEng[sys - 1]->GetRegPress();
}

void Atlantis::HeFillTank(int sys, double mass)
{
	assert((sys >= 0) && (sys <= 3) && "Atlantis::HeFillTank");
	if (sys == 0) pHePneu->FillTank(mass);
	else pHeEng[sys - 1]->FillTank(mass);
}

PROPELLANT_HANDLE Atlantis::GetLH2Tank(void) const
{
	return phLH2dump;
}

PROPELLANT_HANDLE Atlantis::GetLOXTank(void) const
{
	return phLOXdump;
}

double Atlantis::GetLOXManifPress(void) const
{
	return pMPS->GetLOXManifPress();
}

double Atlantis::GetLH2ManifPress(void) const
{
	return pMPS->GetLH2ManifPress();
}

void Atlantis::UpdateOrbiterTexture( const std::string& strTextureName )
{
	if ((!hDevOrbiterMesh) || (!hDevOrbiterVCExternalMesh) || (!hDevVerticalTailMesh)) return;// no mesh handle
	if (hOVTexture == NULL) hOVTexture = oapiLoadTexture( strTextureName.c_str() );
	if (hOVTexture == NULL) throw std::exception( "Could not load Orbiter texture" );
	else
	{
		oapiSetTexture( hDevOrbiterMesh, TEX_SSV_OV_OV104_5THMOD, hOVTexture );
		oapiSetTexture( hDevVerticalTailMesh, 1, hOVTexture );
		oapiSetTexture( hDevOrbiterVCExternalMesh, TEX_SSV_OV_OV104_5THMOD_VCEXT, hOVTexture );
	}
	return;
}

void Atlantis::UpdateLOMSPodTexture( const std::string& strTextureName )
{
	if (!hDevOrbiterMesh) return;// no mesh handle
	if (hLOMSTexture == NULL) hLOMSTexture = oapiLoadTexture( strTextureName.c_str() );
	if (hLOMSTexture == NULL) throw std::exception( "Could not load LOMSPod texture" );
	else oapiSetTexture( hDevOrbiterMesh, TEX_SSV_OV_OMSPOD_7THMOD, hLOMSTexture );
	return;
}

void Atlantis::UpdateROMSPodTexture( const std::string& strTextureName )
{
	if (!hDevOrbiterMesh) return;// no mesh handle
	if (hROMSTexture == NULL) hROMSTexture = oapiLoadTexture( strTextureName.c_str() );
	if (hROMSTexture == NULL) throw std::exception( "Could not load ROMSPod texture" );
	else oapiSetTexture( hDevOrbiterMesh, TEX_SSV_OV_OMSPOD_7THMODA, hROMSTexture );
	return;
}

void Atlantis::UpdateAftBulkheadTexture( const std::string& ov )
{
	if (!hDevOrbiterMesh) return;// no mesh handle
	if (ov == "Columbia")
	{
		// starboard flag
		if (hAftBulkheadTexture == NULL) hAftBulkheadTexture = oapiLoadTexture( TEXTURENAME_AFTBULKHEAD_FLAGSTARBOARD );
		if (hAftBulkheadTexture == NULL) throw std::exception( "Could not load TEXTURENAME_AFTBULKHEAD_FLAGSTARBOARD texture" );
		else oapiSetTexture( hDevOrbiterMesh, TEX_SSV_OV_PLB_AFTBULKHEAD_FLAGPORT, hAftBulkheadTexture );
	}
	else if (ov == "Challenger")
	{
		// no flag
		if (hAftBulkheadTexture == NULL) hAftBulkheadTexture = oapiLoadTexture( TEXTURENAME_AFTBULKHEAD_FLAGNONE );
		if (hAftBulkheadTexture == NULL) throw std::exception( "Could not load TEXTURENAME_AFTBULKHEAD_FLAGNONE texture" );
		else oapiSetTexture( hDevOrbiterMesh, TEX_SSV_OV_PLB_AFTBULKHEAD_FLAGPORT, hAftBulkheadTexture );
	}
	return;
}

int Atlantis::GetSoundID() const {
	return SoundID;
}

ANIMATIONCOMPONENT_HANDLE Atlantis::AddManagedAnimationComponent(UINT anim, double state0, double state1,
	MGROUP_TRANSFORM *trans, ANIMATIONCOMPONENT_HANDLE parent)
{
	vpAnimations.push_back(trans);
	return AddAnimationComponent(anim, state0, state1, trans, parent);
}

void Atlantis::SetOMSThrustLevel( unsigned short usEng, double level )
{
	assert( (usEng < 2) && "Atlantis::OMSEngControl.usEng" );
	assert( (level >= 0.0) && (level <= 1.0) && "Atlantis::OMSEngControl.level" );

	SetThrusterLevel( th_oms[usEng], level );
	return;
}

bool Atlantis::AttachChildAndUpdateMass(OBJHANDLE child, ATTACHMENTHANDLE attachment, ATTACHMENTHANDLE child_attachment)
{
	bool result = AttachChild( child, attachment, child_attachment );
	return result;
}

bool Atlantis::DetachChildAndUpdateMass(ATTACHMENTHANDLE attachment, double vel)
{
	bool result = DetachChild( attachment, vel );
	return result;
}

void Atlantis::ETPressurization(double GOXmass, double GH2mass)
{
	ET* et = GetTankInterface();

	if (et != NULL) et->PressurantFlow(GOXmass, GH2mass);
	return;
}

void Atlantis::UpdateMPSManifold(void)
{
	ET* et = GetTankInterface();

	if (et == NULL) return;

	double LH2deltamass = (LOXmass + LH2mass - GetPropellantMass(ph_mps)) / 7.032;
	double LOXdeltamass = LH2deltamass * 6.032;

	LOXmass -= LOXdeltamass;
	LH2mass -= LH2deltamass;

	et->PropellantFlow(LOXdeltamass, LH2deltamass);

	LOXmass += LOXdeltamass;
	if (LOXmass < 1) LOXmass = 0;// so it doesn't last forever
	LH2mass += LH2deltamass;
	if (LH2mass < 1) LH2mass = 0;// so it doesn't last forever

	SetPropellantMass(ph_mps, LOXmass + LH2mass);

	// HACK no clue... using 65-80% LOX mass
	double lvl = 100 * LOXmass / MPS_MANIFOLD_MASS_LOX;
	LO2LowLevelSensor[0].SetValue(lvl);
	LO2LowLevelSensor[1].SetValue(lvl);
	LO2LowLevelSensor[2].SetValue(lvl);
	LO2LowLevelSensor[3].SetValue(lvl);
	return;
}

void Atlantis::UpdateMassAndCoG( bool bUpdateAttachedVessels )
{
	std::vector<double> masses;
	std::vector<VECTOR3> positions;
	double stackMass = 0.0;// mass of ET & SRBs (if attached)
	double payloadMass = 0.0;// mass of attached payloads
	VECTOR3 payloadCoG = _V( 0.0, 0.0, 0.0 );

	double subsysMass = 0.0;// mass of subsystems
	VECTOR3 subsysCoG = _V( 0.0, 0.0, 0.0 );

	// get mass and c.g. of attached payloads
	//if (bUpdateAttachedVessels)
	//{
		DWORD attachmentCount = AttachmentCount( false );
		for (DWORD i = 0; i < attachmentCount; i++)
		{
			ATTACHMENTHANDLE ah = GetAttachmentHandle( false, i );
			if ((ah != ahET) && (ah != ahLeftSRB) && (ah != ahRightSRB))
			{
				if (GetAttachmentStatus( ah ))
				{
					double mass;
					VECTOR3 CoG;
					mass = GetMassAndCoGOfAttachedObject( this, ah, CoG );
					CoG += currentCoG * 2.0;// corrected for current c.g. offset (still haven't figured out why it must by twice...)
					payloadMass += mass;
					payloadCoG += CoG * mass;

					if (bUpdateAttachedVessels)
					{
						oapiWriteLogV( "(SSV_OV) [INFO] Payload: %s Mass: %flbs CoG: Xo%+f Yo%+f Zo%+f", oapiGetVesselInterface( GetAttachmentStatus( ah ) )->GetName(), mass * KG2LBM, (24.239 - CoG.z) / IN2M, CoG.x / IN2M, (CoG.y + 10.5871) / IN2M );
					}
				}
			}
		}
		if ((payloadMass > 0.1) && (bUpdateAttachedVessels)) payloadCoG = payloadCoG / payloadMass;
		else payloadCoG = _V( 0.0, 0.0, 0.0 );
	//}

	// get mass and c.g. of subsystems
	subsysMass = psubsystems->GetTotalSubsystemMassCoG( subsysCoG, ORBITER_CG );

	// ET/SRB masses
	if (status <= STATE_STAGE2)
	{
		if (status <= STATE_STAGE1)
		{
			OBJHANDLE hLeftSRB = GetAttachmentStatus( ahLeftSRB );
			if (hLeftSRB) stackMass += oapiGetMass( hLeftSRB );
			OBJHANDLE hRightSRB = GetAttachmentStatus( ahRightSRB );
			if (hRightSRB) stackMass += oapiGetMass( hRightSRB );
		}
		OBJHANDLE hET = GetAttachmentStatus( ahET );
		if (hET) stackMass += oapiGetMass( hET );
	}

	// set empty mass
	SetEmptyMass( pMission->GetOrbiterMass() + subsysMass + pl_mass + payloadMass + stackMass );


	// calc overall c.g.
	double shuttleMass = GetMass();// as we add masses, subtract them from this parameter

	// attached payloads c.g.
	shuttleMass -= payloadMass;
	masses.push_back( payloadMass );
	positions.push_back( payloadCoG );

	// subsystems c.g.
	shuttleMass -= subsysMass;
	masses.push_back( subsysMass );
	positions.push_back( subsysCoG );

	// ET c.g.
	if (status <= STATE_STAGE2)
	{
		// density in kg/m^3 (calculated from ET tank mass/volume values in SCOM)
		const double LOX_DENSITY = 1138.43342579;
		const double LH2_DENSITY = 70.8014107928;
		const double TANK_RADIUS = 4.2;

		VESSEL* pTank = GetTankInterface();
		if (pTank)
		{
			double ETMass = pTank->GetEmptyMass();
			shuttleMass -= ETMass;
			masses.push_back( ETMass );
			positions.push_back( ET_EMPTY_CG );

			// approximate propellant tanks as cylinders where position of bottom of cylinder is known
			double prop = GetETPropellant_B();
			double LOXMass = LOX_MAX_PROPELLANT_MASS * (prop * 0.01);
			double LH2Mass = LH2_MAX_PROPELLANT_MASS * (prop * 0.01);
			double LOXHeight = LOXMass / (LOX_DENSITY * PI * TANK_RADIUS * TANK_RADIUS); // height of LOX in cylindrical tank
			double LH2Height = LH2Mass / (LH2_DENSITY * PI * TANK_RADIUS * TANK_RADIUS); // height of LH2 in cylindrical tank
			shuttleMass -= LOXMass;
			shuttleMass -= LH2Mass;
			masses.push_back( LOXMass );
			positions.push_back( ET_LOX_BASE + _V( 0.0, 0.0, LOXHeight * 0.5 ) );
			masses.push_back( LH2Mass );
			positions.push_back( ET_LH2_BASE + _V( 0.0, 0.0, LH2Height * 0.5 ) );
		}

		// SRBs c.g. (assume SRB CG doesn't change and SRBs are symmetric)
		if (status <= STATE_STAGE1)
		{
			VESSEL* pLSRB = GetSRBInterface( LEFT );
			if (pLSRB)
			{
				double SRBMass = pLSRB->GetEmptyMass() + (GetPropellantMass( ph_srb ) * 0.5);
				shuttleMass -= SRBMass;
				masses.push_back( SRBMass );
				positions.push_back( LSRB_CG );
			}

			VESSEL* pRSRB = GetSRBInterface( RIGHT );
			if (pRSRB)
			{
				double SRBMass = pRSRB->GetEmptyMass() + (GetPropellantMass( ph_srb ) * 0.5);
				shuttleMass -= SRBMass;
				masses.push_back( SRBMass );
				positions.push_back( RSRB_CG );
			}
		}
	}

	// OMS c.g.
	{
		double OMSmass = GetPropellantMass( ph_loms );
		shuttleMass -= OMSmass;
		masses.push_back( OMSmass );
		positions.push_back( LOMS_PROP_CG );

		OMSmass = GetPropellantMass( ph_roms );
		shuttleMass -= OMSmass;
		masses.push_back( OMSmass );
		positions.push_back( ROMS_PROP_CG );

		// TODO OMS Kit
	}

	// RCS c.g.
	{
		double RCSmass = GetPropellantMass( ph_frcs );
		shuttleMass -= RCSmass;
		masses.push_back( RCSmass );
		positions.push_back( FRCS_PROP_CG );

		RCSmass = GetPropellantMass( ph_lrcs );
		shuttleMass -= RCSmass;
		masses.push_back( RCSmass );
		positions.push_back( LRCS_PROP_CG );

		RCSmass = GetPropellantMass( ph_rrcs );
		shuttleMass -= RCSmass;
		masses.push_back( RCSmass );
		positions.push_back( RRCS_PROP_CG );
	}

	// remaining mass in "default" c.g.
	masses.push_back( shuttleMass );
	positions.push_back( ORBITER_CG );

	// calculate center of gravity (relative to center of Orbiter mesh)
	double totalMass = 0.0;
	VECTOR3 newCoG = _V( 0.0, 0.0, 0.0 );
	for (unsigned int i = 0; i < masses.size(); i++)
	{
		totalMass += masses[i];
		newCoG += positions[i] * masses[i];
	}
	newCoG = newCoG / totalMass;

	if (length( newCoG - currentCoG ) > 0.1)// to avoid rounding errors during launch, only shift CG when magnitude of change is large enough
	{
		VECTOR3 CoGShift = newCoG - currentCoG;
		ShiftCG( CoGShift );
		currentCoG = newCoG;
		orbiter_ofs = -currentCoG;
		oapiWriteLogV( "(SSV_OV) [INFO] OV Mass: %flbs CoG: Xo%+f Yo%+f Zo%+f", totalMass * KG2LBM, (24.239 - newCoG.z) / IN2M, newCoG.x / IN2M, (newCoG.y + 10.5871) / IN2M );

		DefineTouchdownPoints();

		CreateAttControls_RCS( orbiter_ofs ); // update RCS thruster positions

		pPayloadBay->UpdateLights();
		if (pRMS) pRMS->UpdateEELight();
		eva_docking::ODS* pODS = dynamic_cast<eva_docking::ODS*>(pExtAirlock);
		if (pODS) pODS->UpdateLights();

		if (hStackAirfoil) EditAirfoil( hStackAirfoil, 1, CoGShift, NULL, 0.0, 0.0, 0.0 );
		//if (hOVAirfoilV) EditAirfoil( hOVAirfoilV, 1, orbiter_ofs, NULL, 0.0, 0.0, 0.0 );
		//if (hOVAirfoilH) EditAirfoil( hOVAirfoilH, 1, orbiter_ofs, NULL, 0.0, 0.0, 0.0 );

		if (status <= STATE_STAGE2)
		{
			UpdateNullDirections();

			// update SSME light position
			SSMELight->SetPosition( _V( 0.0, SSME_REF[0].y, SSME_REF[1].z - 6.5 ) + orbiter_ofs );

			if (status <= STATE_STAGE1)
			{
				// update SRB lights positions
				SRBLight[0]->SetPosition( _V( LSRB_OFFSET.x, LSRB_OFFSET.y, LSRB_OFFSET.z - 41.22833 ) + orbiter_ofs );
				SRBLight[1]->SetPosition( _V( RSRB_OFFSET.x, RSRB_OFFSET.y, RSRB_OFFSET.z - 41.22833 ) + orbiter_ofs );
			}
		}
	}
	return;
}

void Atlantis::Twang(double timeFromEngineStart) const
{
	double twangParam = (6.5 - timeFromEngineStart) / 4.5;
	if (twangParam < 0 || twangParam > 1) return;
	double twangAngle = (1 - cos(twangParam * PI2))*2.0 / 184.0; //Approximately 2 feet of twang on top of a 184 foot stack
	double c = cos(twangAngle);
	double s = sin(twangAngle);
	SetAttachmentParams(ahHDP, POS_HDP - currentCoG, _V(0, -s, -c), _V(0.0, c, -s));
}

void Atlantis::CreateOMSEngines( const VECTOR3 &ofs )
{
	if (!bOMSDefined)
	{
		th_oms[0] = CreateThruster( ofs + L_OMS_REF, L_OMS_DIR, OMS_THRUST, ph_loms, OMS_ISP0, OMS_ISP1 );
		th_oms[1] = CreateThruster( ofs + R_OMS_REF, R_OMS_DIR, OMS_THRUST, ph_roms, OMS_ISP0, OMS_ISP1 );

		SURFHANDLE tex_oms = oapiRegisterExhaustTexture( "SSV\\OMSExhaust" );
		AddExhaust( th_oms[0], 0, 1.5, 1.55, tex_oms );
		AddExhaust( th_oms[1], 0, 1.5, 1.55, tex_oms );

		bOMSDefined = true;
	}
	return;
}

void Atlantis::CreateLights( void )
{
	// light for engines during launch
	//SSME light
	COLOUR4 col_diff_SSME = { 1.0, 1.0, 1.0, 0 };
	COLOUR4 col_zero_SSME = { 0, 0, 0, 0 };
	COLOUR4 col_ambient_SSME = { 0.5, 0.5, 0.5, 0 };
	//SRB light
	COLOUR4 col_diff_SRB = { 1.0, 0.733f, 0.196f, 0 };
	COLOUR4 col_zero_SRB = { 0, 0, 0, 0 };
	COLOUR4 col_ambient_SRB = { 0.5, 0.5, 0.5, 0 };
	SRBLight[0] = AddPointLight( _V( LSRB_OFFSET.x, LSRB_OFFSET.y, LSRB_OFFSET.z - 41.22833 ) + orbiter_ofs, 300.0, 0.8, 0.01, 0.0001, col_diff_SRB, col_zero_SRB, col_ambient_SRB);
	SRBLight[1] = AddPointLight( _V( RSRB_OFFSET.x, RSRB_OFFSET.y, RSRB_OFFSET.z - 41.22833 ) + orbiter_ofs, 300.0, 0.8, 0.01, 0.0001, col_diff_SRB, col_zero_SRB, col_ambient_SRB);
	SSMELight = AddPointLight( _V( 0.0, SSME_REF[0].y, SSME_REF[1].z - 6.5 ) + orbiter_ofs, 100.0, 1.0, 0.05, 0.0005, col_diff_SSME, col_zero_SSME, col_ambient_SSME);
	return;
}

void Atlantis::AddSRBExhaust( bool smoke )
{
	static PARTICLESTREAMSPEC srb_contrail = {
		0, 1.0, 20.0, 50.0, 0.1, 10.0, 10.0, 0.5, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-6, 1,
	};
	static PARTICLESTREAMSPEC srb_exhaust = {
		0, 1.2, 20.0, 50.0, 0.05, 1.0, 12.0, 0.5, PARTICLESTREAMSPEC::EMISSIVE,
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

	// delete existing
	if (pshSRBSmoke[0]) DelExhaustStream( pshSRBSmoke[0] );
	if (pshSRBSmoke[1]) DelExhaustStream( pshSRBSmoke[1] );

	if (pshSRBFlame[0]) DelExhaustStream( pshSRBFlame[0] );
	if (pshSRBFlame[1]) DelExhaustStream( pshSRBFlame[1] );

	for (int i = 0; i < 2; i++)
	{
		if (pshSlag1[i]) DelExhaustStream( pshSlag1[i] );
		if (pshSlag2[i]) DelExhaustStream( pshSlag2[i] );
		if (pshSlag3[i]) DelExhaustStream( pshSlag3[i] );
	}

	// add new
	SURFHANDLE tex = oapiRegisterExhaustTexture( "Exhaust2" );
	AddExhaust( th_srb[0], 16.0, 3.0, 3.0, tex );
	AddExhaust( th_srb[1], 16.0, 3.0, 3.0, tex );

	if (smoke)
	{
		srb_contrail.tex = oapiRegisterParticleTexture( "SSV\\SRB\\SRB_contrail" );
		pshSRBSmoke[0] = AddExhaustStream( th_srb[0], &srb_contrail );
		pshSRBSmoke[1] = AddExhaustStream( th_srb[1], &srb_contrail );
	}

	srb_exhaust.tex = oapiRegisterParticleTexture( "SSV\\SRB\\SRB_exhaust" );
	pshSRBFlame[0] = AddExhaustStream( th_srb[0], &srb_exhaust );
	pshSRBFlame[1] = AddExhaustStream( th_srb[1], &srb_exhaust );

	// Add slag effect streams
	for (int i = 0; i < 2; i++)
	{
		pshSlag1[i] = AddExhaustStream(th_srb[i], &srb_slag1);
		pshSlag2[i] = AddExhaustStream(th_srb[i], &srb_slag2);
		pshSlag3[i] = AddExhaustStream(th_srb[i], &srb_slag3);
	}
	return;
}

void Atlantis::SetSSMEMesh( unsigned short ID, MESHHANDLE hMesh )
{
	assert( (ID < 3) && "Atlantis::SetSSMEMesh.ID" );
	hSSMEMesh[ID] = hMesh;
	return;
}

gcCore* Atlantis::D3D9( void ) const
{
	return pD3D9;
}

UINT Atlantis::OVmesh( void ) const
{
	return mesh_orbiter;
}

dps::MasterTimingUnit* Atlantis::MTU( void ) const
{
	return pMTU;
}

T0UmbilicalReference* Atlantis::T0UmbRef( void ) const
{
	return pT0UmbRef;
}

APU* Atlantis::GetAPU( int apu ) const
{
	assert( (apu >= 1) && (apu <= 3) && "Atlantis::GetAPU.apu" );
	return pAPU[apu + 1];
}

MPM* Atlantis::GetPortMPM( void ) const
{
	return pRMS;
}

MPM* Atlantis::GetStarboardMPM( void ) const
{
	return pPLMPM;
}

ATTACHMENTHANDLE Atlantis::GetHDP( void ) const
{
	return ahHDP;
}

VISHANDLE Atlantis::Get_vis( void ) const
{
	return vis;
}

DEVMESHHANDLE Atlantis::GetOVDevMesh( void ) const
{
	return hDevOrbiterMesh;
}

int Atlantis::Get_status( void ) const
{
	return status;
}

int Atlantis::GetVCMode( void ) const
{
	return VCMode;
}

AtlantisSubsystemDirector* Atlantis::SubsystemDirector( void ) const
{
	return psubsystems;
}

void Atlantis::CreateSubsystems( void )
{
	psubsystems->AddSubsystem( pHeEng[0] = new mps::HeSysEng( psubsystems, "HeEng_C", 1 ) );
	psubsystems->AddSubsystem( pHeEng[1] = new mps::HeSysEng( psubsystems, "HeEng_L", 2 ) );
	psubsystems->AddSubsystem( pHeEng[2] = new mps::HeSysEng( psubsystems, "HeEng_R", 3 ) );
	psubsystems->AddSubsystem( pHePneu = new mps::HeSysPneu( psubsystems, "HePneu" ) );

	psubsystems->AddSubsystem( pMPS = new mps::MPS( psubsystems, pHePneu ) );

	mps::SSME* pSSME[3];
	psubsystems->AddSubsystem( pSSME[0] = new mps::SSME_BLOCK_II( psubsystems, "SSME1", 1, 2, "AD08", pHeEng[0] ) );
	psubsystems->AddSubsystem( pSSME[1] = new mps::SSME_BLOCK_II( psubsystems, "SSME2", 2, 2, "AD08", pHeEng[1] ) );
	psubsystems->AddSubsystem( pSSME[2] = new mps::SSME_BLOCK_II( psubsystems, "SSME3", 3, 2, "AD08", pHeEng[2] ) );

	psubsystems->AddSubsystem( new FMC1( psubsystems ) );
	psubsystems->AddSubsystem( new FMC2( psubsystems ) );
	psubsystems->AddSubsystem( new FMC3( psubsystems ) );
	psubsystems->AddSubsystem( new MMC1( psubsystems ) );
	psubsystems->AddSubsystem( new MMC2( psubsystems ) );
	psubsystems->AddSubsystem( new MMC3( psubsystems ) );
	psubsystems->AddSubsystem( new MMC4( psubsystems ) );
	psubsystems->AddSubsystem( new AMC1( psubsystems ) );
	psubsystems->AddSubsystem( new AMC2( psubsystems ) );
	psubsystems->AddSubsystem( new AMC3( psubsystems ) );

	psubsystems->AddSubsystem( pEIU[0] = new mps::EIU( psubsystems, "EIU1", 1, pSSME[0] ) );
	psubsystems->AddSubsystem( pEIU[1] = new mps::EIU( psubsystems, "EIU2", 2, pSSME[1] ) );
	psubsystems->AddSubsystem( pEIU[2] = new mps::EIU( psubsystems, "EIU3", 3, pSSME[2] ) );

	psubsystems->AddSubsystem( pMTU = new dps::MasterTimingUnit( psubsystems ));

	psubsystems->AddSubsystem( pIDP[0] = new dps::IDP( psubsystems, "IDP1", 1 ) );
	psubsystems->AddSubsystem( pIDP[1] = new dps::IDP( psubsystems, "IDP2", 2 ) );
	psubsystems->AddSubsystem( pIDP[2] = new dps::IDP( psubsystems, "IDP3", 3 ) );
	psubsystems->AddSubsystem( pIDP[3] = new dps::IDP( psubsystems, "IDP4", 4 ) );

	psubsystems->AddSubsystem( pSimpleGPC = new dps::SimpleGPCSystem( psubsystems, "SimpleGPC1" ) );
	pRSLS = dynamic_cast<dps::RSLS*>(pSimpleGPC->FindSoftware( "RSLS" ));
	assert( (pRSLS != NULL) && "Atlantis::CreateSubsystems.pRSLS" );
	pMPS_ATVC_CMD_SOP = dynamic_cast<dps::MPS_ATVC_CMD_SOP*>(pSimpleGPC->FindSoftware( "MPS_ATVC_CMD_SOP" ));
	assert( (pMPS_ATVC_CMD_SOP != NULL) && "Atlantis::CreateSubsystems.pMPS_ATVC_CMD_SOP" );
	pSSME_SOP = dynamic_cast<dps::SSME_SOP*>(pSimpleGPC->FindSoftware( "SSME_SOP" ));
	assert( (pSSME_SOP != NULL) && "Atlantis::CreateSubsystems.pSSME_SOP" );

	psubsystems->AddSubsystem( pSimpleMDM_FF1 = new dps::SimpleMDM_FF1( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_FF2 = new dps::SimpleMDM_FF2( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_FF3 = new dps::SimpleMDM_FF3( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_FF4 = new dps::SimpleMDM_FF4( psubsystems ) );

	psubsystems->AddSubsystem( pSimpleMDM_FA1 = new dps::SimpleMDM_FA1( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_FA2 = new dps::SimpleMDM_FA2( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_FA3 = new dps::SimpleMDM_FA3( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_FA4 = new dps::SimpleMDM_FA4( psubsystems ) );

	psubsystems->AddSubsystem( pSimpleMDM_PF1 = new dps::SimpleMDM_PF1( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_PF2 = new dps::SimpleMDM_PF2( psubsystems ) );

	psubsystems->AddSubsystem( pSimpleMDM_OF1 = new dps::SimpleMDM_OF1( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_OF2 = new dps::SimpleMDM_OF2( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_OF3 = new dps::SimpleMDM_OF3( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_OF4 = new dps::SimpleMDM_OF4( psubsystems ) );

	psubsystems->AddSubsystem( pSimpleMDM_OA1 = new dps::SimpleMDM_OA1( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_OA2 = new dps::SimpleMDM_OA2( psubsystems ) );
	psubsystems->AddSubsystem( pSimpleMDM_OA3 = new dps::SimpleMDM_OA3( psubsystems ) );

	psubsystems->AddSubsystem( new AirDataProbes( psubsystems ) );

	psubsystems->AddSubsystem( new ETUmbilicalDoors( psubsystems ) );

	psubsystems->AddSubsystem( new comm::GCIL( psubsystems ) );

	psubsystems->AddSubsystem( new gnc::ATVC( psubsystems, "ATVC", 1 ) );// HACK should be 4 of this

	psubsystems->AddSubsystem( new MPS_TVC( psubsystems ) );

	psubsystems->AddSubsystem( new MasterEventsController( psubsystems, "MEC1", 1 ) );
	psubsystems->AddSubsystem( new MasterEventsController( psubsystems, "MEC2", 2 ) );

	psubsystems->AddSubsystem( new gnc::RadarAltimeter( psubsystems, "RA1", 1 ) );
	psubsystems->AddSubsystem( new gnc::RadarAltimeter( psubsystems, "RA2", 2 ) );

	psubsystems->AddSubsystem( pPayloadBay = new PayloadBay( psubsystems, pMission->GetPayloads(), pMission->GetOrbiter(), pMission->HasKUBand(), pMission->HasBulkheadFloodlights(), pMission->HasPLBLiner(), pMission->HasDFIWireTray(), pMission->HasVentDoors4and7(), pMission->HasEDOKit(), pMission->HasExtALODSKit() ) );
	psubsystems->AddSubsystem( new LandingGear( psubsystems ) );
	psubsystems->AddSubsystem( new AeroSurfaces( psubsystems ) );

	psubsystems->AddSubsystem( new oms::OMS( psubsystems, "OMS_LEFT", 0 ) );
	psubsystems->AddSubsystem( new oms::OMS( psubsystems, "OMS_RIGHT", 1 ) );

	psubsystems->AddSubsystem( new oms::OMS_TVC( psubsystems, "OMS_TVC_LEFT", 0 ) );
	psubsystems->AddSubsystem( new oms::OMS_TVC( psubsystems, "OMS_TVC_RIGHT", 1 ) );

	psubsystems->AddSubsystem( new DDU( psubsystems, "DDU1", 1 ) );
	psubsystems->AddSubsystem( new DDU( psubsystems, "DDU2", 2 ) );
	psubsystems->AddSubsystem( new DDU( psubsystems, "DDU3", 3 ) );

	psubsystems->AddSubsystem( pHUD[0] = new HUD( psubsystems, "HUD1", 1 ) );
	psubsystems->AddSubsystem( pHUD[1] = new HUD( psubsystems, "HUD2", 2 ) );

	psubsystems->AddSubsystem( new RHC( psubsystems, "LeftRHC", 1 ) );
	psubsystems->AddSubsystem( new RHC( psubsystems, "RightRHC", 2 ) );
	psubsystems->AddSubsystem( new RHC( psubsystems, "AftRHC", 3 ) );

	psubsystems->AddSubsystem( new THC( psubsystems, "LeftTHC", 1 ) );
	psubsystems->AddSubsystem( new THC( psubsystems, "AftTHC", 3 ) );

	psubsystems->AddSubsystem( new RPTA( psubsystems, "LeftRPTA", 1 ) );
	psubsystems->AddSubsystem( new RPTA( psubsystems, "RightRPTA", 2 ) );

	psubsystems->AddSubsystem( new SBTC( psubsystems, "LeftSBTC", 1 ) );
	psubsystems->AddSubsystem( new SBTC( psubsystems, "RightSBTC", 2 ) );

	psubsystems->AddSubsystem(pAPU[0] = new APU(psubsystems, "APU1", 1));
	psubsystems->AddSubsystem(pAPU[1] = new APU(psubsystems, "APU2", 2));
	psubsystems->AddSubsystem(pAPU[2] = new APU(psubsystems, "APU3", 3));

	psubsystems->AddSubsystem(new WSB(psubsystems, "WSB1", 1));
	psubsystems->AddSubsystem(new WSB(psubsystems, "WSB2", 2));
	psubsystems->AddSubsystem(new WSB(psubsystems, "WSB3", 3));

	struct mission::MissionPayloads missionpl = pMission->GetPayloads();
	for (unsigned short i = 0; i < 5; i++)
	{
		if (missionpl.active[i].IsUsed)
		{
			string name = "Payload_Latch_" + std::to_string( i + 1 );
			psubsystems->AddSubsystem( pActiveLatches[i] = new ActiveLatchGroup( psubsystems, name, i, pMission->GetPayloads() ) );
		}
	}

	psubsystems->AddSubsystem( new eps::PRSD( pMission->GetInternalPRSDTankSets(), pMission->HasEDOKit(), pMission->GetEDOPallet(), psubsystems ) );

	psubsystems->AddSubsystem( pVCU = new VideoControlUnit( psubsystems ) );

	psubsystems->AddSubsystem( new AnnunciatorControlAssembly( psubsystems, "ACA1", 1 ) );
	psubsystems->AddSubsystem( new AnnunciatorControlAssembly( psubsystems, "ACA2", 2 ) );
	psubsystems->AddSubsystem( new AnnunciatorControlAssembly( psubsystems, "ACA3", 3 ) );
	psubsystems->AddSubsystem( new AnnunciatorControlAssembly( psubsystems, "ACA4", 4 ) );
	psubsystems->AddSubsystem( new AnnunciatorControlAssembly( psubsystems, "ACA5", 5 ) );

	psubsystems->AddSubsystem( new StarTrackerDoors( psubsystems ) );

	psubsystems->AddSubsystem( new VentDoors( psubsystems, pMission->HasVentDoors4and7() ) );

	if (hasPORT_RMS) psubsystems->AddSubsystem( pRMS = new RMS( psubsystems, "PORT_RMS", true ) );
	if (hasSTBD_MPM) psubsystems->AddSubsystem( pPLMPM = new Payload_MPM( psubsystems, pMission->GetPayloadMPM( false ), false ) );

	if (!pMission->HasExtAL())
	{
		psubsystems->AddSubsystem( new eva_docking::IntAirlock( psubsystems ) );
		if (pMission->HasODS()) psubsystems->AddSubsystem( pExtAirlock = new eva_docking::ODS( psubsystems, pMission->IsExternalAirlockAftPos() ) );
	}
	else
	{
		if (pMission->HasODS()) psubsystems->AddSubsystem( pExtAirlock = new eva_docking::ODS( psubsystems, pMission->IsExternalAirlockAftPos() ) );
		else psubsystems->AddSubsystem( pExtAirlock = new eva_docking::ExtAirlock( psubsystems, "ExternalAirlock", pMission->IsExternalAirlockAftPos() ) );
	}

	if (pMission->HasTAA()) psubsystems->AddSubsystem( new eva_docking::TunnelAdapterAssembly( psubsystems, pMission->AftTAA(), pMission->HasExtAL() || pMission->HasODS() ) );

	if (pMission->HasKUBand())
	{
		comm::DeployedAssembly* pDeployedAssembly;
		psubsystems->AddSubsystem( pDeployedAssembly = new comm::DeployedAssembly( psubsystems ) );
		psubsystems->AddSubsystem( new comm::ElectronicsAssembly1( psubsystems, pDeployedAssembly ) );
		psubsystems->AddSubsystem( new comm::ElectronicsAssembly2( psubsystems, pDeployedAssembly ) );
	}

	if (pMission->HasDragChute()) psubsystems->AddSubsystem( pDragChute = new DragChute( psubsystems ) );

	if (pMission->UseASE_IUS()) psubsystems->AddSubsystem( pASE_IUS = new ASE_IUS( psubsystems, pMission->IsASELocationAft(), pMission->GetLargeUpperStageLatches() ) );
	else if (pMission->UseCISS()) psubsystems->AddSubsystem( pCISS = new CISS( psubsystems, pMission->IsCISSGPrime(), pMission->GetLargeUpperStageLatches() ) );
	return;
}

void Atlantis::CreatePanels( void )
{
	pgForward->AddPanel( new vc::PanelF2( this, pMission->HasDragChute() ) );
	pgForward->AddPanel( new vc::PanelF3( this, pMission->HasDragChute() ) );
	pgForward->AddPanel( new vc::PanelF4( this, pMission->HasDragChute() ) );
	pgForward->AddPanel( new vc::PanelF6( this ) );
	pgForward->AddPanel( new vc::PanelF7( this ) );
	pgForward->AddPanel( new vc::PanelF8( this ) );
	pgForward->AddPanel( new vc::PanelF9( this ) );

	pgLeft->AddPanel( new vc::PanelL1( this ) );
	pgLeft->AddPanel( new vc::PanelL2( this ) );
	pgLeft->AddPanel( new vc::PanelL4( this ) );

	pgCenter->AddPanel( new vc::PanelC2( this ) );
	pgCenter->AddPanel( new vc::PanelC3( this, pMission->GetOrbiter() ) );

	pgRight->AddPanel( new vc::PanelR2( this ) );
	pgRight->AddPanel( new vc::PanelR1( this ) );// HACK should be placed before R2, but click area on R2 is too big
	pgRight->AddPanel( new vc::PanelR4( this ) );

	pgOverhead->AddPanel( new vc::PanelO1( this ) );
	pgOverhead->AddPanel( new vc::PanelO2( this ) );
	pgOverhead->AddPanel( new vc::PanelO3( this ) );
	pgOverhead->AddPanel( new vc::PanelO5( this ) );
	pgOverhead->AddPanel( new vc::PanelO6( this ) );
	pgOverhead->AddPanel( new vc::PanelO7( this ) );
	pgOverhead->AddPanel( new vc::PanelO8( this ) );
	pgOverhead->AddPanel( new vc::PanelO9( this ) );

	pgOverheadAft->AddPanel( new vc::PanelO13( this ) );
	pgOverheadAft->AddPanel( new vc::PanelO14( this ) );
	pgOverheadAft->AddPanel( new vc::PanelO15( this ) );
	pgOverheadAft->AddPanel( new vc::PanelO16( this ) );
	pgOverheadAft->AddPanel( new vc::PanelO17( this ) );

	pgAftPort->AddPanel( new vc::PanelL9( this ) );
	if (pMission->UseASE_IUS())
	{
		pgAftPort->AddPanel( new vc::PanelL10_IUS( this ) );
		pgAftPort->AddPanel( new vc::PanelL12U_IUS( this ) );
	}
	else if (pMission->UseCISS()) pgAftPort->AddPanel( new vc::PanelL12U_Centaur( this ) );

	pgAft->AddPanel( new vc::PanelA1U( this ) );
	pgAft->AddPanel( new vc::PanelA1L( this ) );
	pgAft->AddPanel( new vc::PanelA1R( this ) );
	pgAft->AddPanel( new vc::AftMDU( this ) );
	pgAft->AddPanel( new vc::PanelA2( this ) );
	pgAft->AddPanel( panelA3 = new vc::PanelA3( this ) );
	pgAft->AddPanel( new vc::PanelA4( this ) );
	pgAft->AddPanel( new vc::PanelA6U( this ) );
	pgAft->AddPanel( new vc::PanelA7U( this ) );
	if (pMission->HasODS())
	{
		pgAft->AddPanel( new vc::PanelA7A3( this, false ) );
		pgAft->AddPanel( new vc::PanelA8A3( this, false ) );
	}
	if (hasPORT_RMS || hasSTBD_MPM)
	{
		pgAft->AddPanel( new vc::PanelA8A1( this ) );
		pgAft->AddPanel( new vc::PanelA8A2( this ) );
	}

	pgAftStbd->AddPanel( new vc::PanelR10( this ) );
	pgAftStbd->AddPanel( new vc::PanelA12A1( this, false ) );
	pgAftStbd->AddPanel( new vc::PanelA12A2( this, false ) );
	pgAftStbd->AddPanel( new vc::PanelR13U( this ) );
	pgAftStbd->AddPanel( new vc::PanelR13L( this ) );
	return;
}