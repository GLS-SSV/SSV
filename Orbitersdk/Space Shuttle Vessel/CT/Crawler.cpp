/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/07   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/24   GLS
2020/08/31   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/***************************************************************************
  This file is part of Project Apollo - NASSP
  Copyright 2004-2005

  Crawler Transporter vessel

  Project Apollo is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Project Apollo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Project Apollo; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See http://nassp.sourceforge.net/license/ for more details.

  **************************** Revision History ****************************
  *	$Log: Crawler.cpp,v $
  *	Revision 1.2  2009/06/15 16:11:32  tschachim
  *	New CollisionSDK.
  *	
  *	Revision 1.1  2009/02/18 23:21:14  tschachim
  *	Moved files as proposed by Artlav.
  *	
  *	Revision 1.28  2008/09/04 22:01:58  tschachim
  *	Bugfix
  *	
  *	Revision 1.27  2008/04/11 11:49:09  tschachim
  *	Fixed BasicExcel for VC6, reduced VS2005 warnings, bugfixes.
  *	
  *	Revision 1.26  2007/12/15 19:48:26  lassombra
  *	Added functionality to allow ProjectApollo MFD to get mission time from the Crawler as well as the Saturn.  The Crawler actually extracts the mission time from the Saturn, no updates to scenario files needed.
  *	
  *	Revision 1.25  2007/08/16 16:49:53  tschachim
  *	New meshes.
  *	
  *	Revision 1.24  2007/08/13 16:05:33  tschachim
  *	Moved bitmaps to subdirectory.
  *	New VAGC mission time pad load handling.
  *	New telescope and sextant panels.
  *	Fixed CSM/LV separation speed.
  *	
  *	Revision 1.23  2007/06/06 15:02:07  tschachim
  *	OrbiterSound 3.5 support, various fixes and improvements.
  *	
  *	Revision 1.22  2007/03/03 19:32:29  tschachim
  *	More viewpoints.
  *	
  *	Revision 1.21  2007/03/03 00:14:40  tschachim
  *	Bugfix generic cockpit.
  *	
  *	Revision 1.20  2007/03/02 18:34:37  tschachim
  *	Improved crawler VC.
  *	
  *	Revision 1.19  2007/03/01 17:58:26  tschachim
  *	New VC panel
  *	
  *	Revision 1.18  2007/02/18 01:35:28  dseagrav
  *	MCC / LVDC++ CHECKPOINT COMMIT. No user-visible functionality added. lvimu.cpp/h and mcc.cpp/h added.
  *	
  *	Revision 1.17  2006/07/24 20:47:27  orbiter_fan
  *	Changed turn speed. Now the Crawler can turn corners just like the real one!
  *	
  *	Revision 1.16  2006/07/17 19:33:36  tschachim
  *	Small improvements of LC39.
  *	
  *	Revision 1.15  2006/06/23 11:58:07  tschachim
  *	Smaller turning diameter
  *	Slower acceleration/braking during time acceleration.
  *	
  *	Revision 1.14  2006/04/25 13:51:32  tschachim
  *	New KSC.
  *	
  *	Revision 1.13  2006/03/02 14:54:39  tschachim
  *	Velocity dependent sound disabled.
  *	
  *	Revision 1.12  2005/12/19 16:46:33  tschachim
  *	Bugfix touchdownpoints.
  *	
  *	Revision 1.11  2005/11/23 21:36:55  movieman523
  *	Allow specification of LV name in scenario file.
  *	
  *	Revision 1.10  2005/10/31 19:18:39  tschachim
  *	Bugfixes.
  *	
  *	Revision 1.9  2005/10/31 10:15:06  tschachim
  *	New VAB.
  *	
  *	Revision 1.8  2005/10/19 11:06:24  tschachim
  *	Changed log file name.
  *	
  *	Revision 1.7  2005/08/14 16:08:20  tschachim
  *	LM is now a VESSEL2
  *	Changed panel restore mechanism because the CSM mechanism
  *	caused CTDs, reason is still unknown.
  *	
  *	Revision 1.6  2005/08/05 12:59:35  tschachim
  *	Saturn detachment handling
  *	
  *	Revision 1.5  2005/07/05 17:23:11  tschachim
  *	Scenario saving/loading
  *	
  *	Revision 1.4  2005/07/01 12:23:48  tschachim
  *	Introduced standalone flag
  *	
  *	Revision 1.3  2005/06/29 11:01:17  tschachim
  *	new dynamics, added attachment management
  *	
  *	Revision 1.2  2005/06/14 16:14:41  tschachim
  *	File header inserted.
  *	
  **************************************************************************/

#define ORBITER_MODULE

// To force orbitersdk.h to use <fstream> in any compiler version
#pragma include_alias( <fstream.h>, <fstream> )
#include "Crawler.h"
#include <Orbitersdk.h>

#include <stdio.h>
#include <math.h>
#include <string>
#include <cassert>
#include "../SSVSound.h"
#include "resource_Crawler.h"

#include <MathSSV.h>
#include "CrawlerLeftPanel.h"
#include "CrawlerCenterPanel.h"
#include "CrawlerRightPanel.h"
#include "LDSPanel.h"
#include "CrawlerEngine.h"
#include "Crawler_defs.h"
#include <EngConst.h>
#include <SurfaceRoving.h>


GlobalHandles g_Resources;

DLLCLBK void InitModule(HINSTANCE hModule)
{
	try
	{
		//g_hDLL = hModule;
		g_Resources.hDll = hModule;
		HBITMAP hBmp = LoadBitmap(g_Resources.hDll, MAKEINTRESOURCE(IDB_7SEGDIGITS));
		g_Resources.digits_7seg = oapiCreateSurface(hBmp);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in InitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in InitModule" );
		abort();
	}
}

DLLCLBK void ExitModule (HINSTANCE hModule)
{
	try
	{
		if(g_Resources.digits_7seg)
			oapiDestroySurface(g_Resources.digits_7seg);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in ExitModule: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in ExitModule" );
		abort();
	}
}

DLLCLBK VESSEL *ovcInit(OBJHANDLE hvessel, int flightmodel)
{
	try
	{
		return new Crawler(hvessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL *vessel)
{
	try
	{
		if (vessel) delete static_cast<Crawler*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}

Crawler::Crawler(OBJHANDLE hObj, int fmodel)
: VESSEL4 (hObj, fmodel)
{
	pBundleManager = new DiscreteBundleManager();
	psubsystems = new SubsystemDirector<Crawler>(this);
	psubsystems->AddSubsystem(pEngine = new CrawlerEngine(psubsystems));

	surfaceroving = new SurfaceRoving( this, 13.6, 13.4, -DRIVETRUCK_SHOE_OFFSET );

	pgFwdCab = new vc::PanelGroup<Crawler>();
	pgRearCab = new vc::PanelGroup<Crawler>();

	pgFwdCab->AddPanel(new vc::CrawlerLeftPanel(this, "FWD_CAB_LEFT", vc::FWD));
	pgFwdCab->AddPanel(new vc::CrawlerCenterPanel(this, "FWD_CAB_CTR", vc::FWD));
	pgFwdCab->AddPanel(new vc::CrawlerRightPanel(this, "FWD_CAB_RIGHT", vc::FWD));
	pgRearCab->AddPanel(new vc::CrawlerLeftPanel(this, "REAR_CAB_LEFT", vc::REAR));
	pgRearCab->AddPanel(new vc::CrawlerCenterPanel(this, "REAR_CAB_CTR", vc::REAR));
	pgRearCab->AddPanel(new vc::CrawlerRightPanel(this, "REAR_CAB_RIGHT", vc::REAR));
	pgFwdCab->AddPanel(new vc::LDS(this,"FWD_LDS", vc::FWD));
	pgRearCab->AddPanel(new vc::LDS(this,"REAR_LDS", vc::REAR));

	currentSpeed = 0.0;
	targetSpeed[0] = 0.0;
	targetSpeed[1] = 0.0;
	maxSpeed = MAX_UNLOADED_SPEED;
	velocityStop = false;
	steeringWheel[0] = 0.0;
	steeringWheel[1] = 0.0;
	steeringActual[0] = steeringActual[1] = 0.0;
	steeringCommanded[0] = steeringCommanded[1] = 0.0;
	viewPos = VIEWPOS_FRONTCABIN;
	firstTimestepDone = false;
	standalone = false;

	curFrontAngle = 0.0;
	curBackAngle = 0.0;
	curFrontHeight = 0.0;
	curBackHeight = 0.0;
	jackHeight = 0.0;
	targetjackHeight = 0.0;
	targetJackHeightIndex = 0;

	keyLeft= false;
	keyRight= false;
	keyCenter = false;
	increaseTgtSpeed = false;
	decreaseTgtSpeed = false;

	cabackPBIpressed = false;
	CabSelectedFwd = false;
	CabSelectedAft = false;
	CabInControl = 0;

	brakePBIpressed = false;
	ParkingBrakeOn = false;
	PedalBrakeOn = false;

	Steer = 0;
	steermodePBIpressed = false;
	SteerModeFwd = true;
	SteerModeAft = true;

	hMLP = NULL;
	hMLPAttach = NULL;
	vccVis = NULL;
	vccSpeed = 0;
	vccSteering = 0;
	meshidxCrawler = 0;
	meshidxTruck1 = 0;
	meshidxTruck2 = 0;
	meshidxTruck3 = 0;
	meshidxTruck4 = 0;
	hFwdVCMesh = NULL;
	hRearVCMesh = NULL;
	brake_discs_state = 0;

	hEarth = NULL;

	strcpy_s( MLPclassname, "SSV_MLP" );
}

Crawler::~Crawler() {
	// delete MGROUP_TRANSFORMs
	for(unsigned short i=0;i<vpAnimations.size();i++) delete vpAnimations.at(i);

	delete psubsystems;
	delete pBundleManager;

	delete pgFwdCab;
	delete pgRearCab;
}

void Crawler::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		SetEmptyMass(2721000);
		SetSize(40);
		SetPMI(_V(133, 189, 89));

		SetRotDrag (_V(0, 0, 0));
		SetCW(0, 0, 0, 0);
		SetPitchMomentScale(0);
		SetYawMomentScale( 0 );
		SetLiftCoeffFunc(0);

		ClearMeshes( true );

		// Crawler
		bool mesh_1980 = false;
		if(!oapiReadItem_bool(cfg, "1980_Mesh", mesh_1980)) mesh_1980 = false;
		VECTOR3 crawler_meshoffset = CRAWLER_MESH_OFFSET;
		if(mesh_1980) {
			meshidxCrawler = AddMesh(oapiLoadMeshGlobal( MESHNAME_CRAWLER_1980 ), &crawler_meshoffset);
		}
		else {
			meshidxCrawler = AddMesh(oapiLoadMeshGlobal( MESHNAME_CRAWLER ), &crawler_meshoffset);
		}
		SetMeshVisibilityMode(meshidxCrawler, MESHVIS_ALWAYS);

		// Tracks
		MESHHANDLE track = oapiLoadMeshGlobal("SSV\\CT\\drivetrucks");
		MESHHANDLE track_reversed = oapiLoadMeshGlobal("SSV\\CT\\drivetrucks_reversed");

		VECTOR3 meshoffset = _V(DRIVETRUCK_X_OFFSET, DRIVETRUCK_Y_OFFSET, DRIVETRUCK_Z_OFFSET);
		meshidxTruck1 = AddMesh(track_reversed, &meshoffset);
		SetMeshVisibilityMode(meshidxTruck1, MESHVIS_ALWAYS);

		meshoffset = _V(-DRIVETRUCK_X_OFFSET, DRIVETRUCK_Y_OFFSET, DRIVETRUCK_Z_OFFSET);
		meshidxTruck2 = AddMesh(track, &meshoffset);
		SetMeshVisibilityMode(meshidxTruck2, MESHVIS_ALWAYS);

		meshoffset = _V(DRIVETRUCK_X_OFFSET, DRIVETRUCK_Y_OFFSET, -DRIVETRUCK_Z_OFFSET);
		meshidxTruck3 = AddMesh(track_reversed, &meshoffset);
		SetMeshVisibilityMode(meshidxTruck3, MESHVIS_ALWAYS);

		meshoffset = _V(-DRIVETRUCK_X_OFFSET, DRIVETRUCK_Y_OFFSET, -DRIVETRUCK_Z_OFFSET);
		meshidxTruck4 = AddMesh(track, &meshoffset);
		SetMeshVisibilityMode(meshidxTruck4, MESHVIS_ALWAYS);

		VECTOR3 crawler_vc_offset = CRAWLER_FWD_VC_OFFSET;
		hFwdVCMesh = oapiLoadMeshGlobal("SSV\\CT\\panels_reversed");
		fwdVCIdx = AddMesh(hFwdVCMesh, &crawler_vc_offset);
		SetMeshVisibilityMode(fwdVCIdx, MESHVIS_COCKPIT | MESHVIS_VC | MESHVIS_EXTERNAL);
		crawler_vc_offset = CRAWLER_REAR_VC_OFFSET;
		hRearVCMesh = oapiLoadMeshGlobal("SSV\\CT\\panels");
		rearVCIdx = AddMesh(hRearVCMesh, &crawler_vc_offset);
		SetMeshVisibilityMode(rearVCIdx, MESHVIS_COCKPIT | MESHVIS_VC | MESHVIS_EXTERNAL);

		DefineAnimations(mesh_1980);

		char cbuf[255];
		if (oapiReadItem_string( cfg, "MLPclass", cbuf ))
		{
			if (strlen( cbuf ) > 0)
			{
				strcpy_s( MLPclassname, cbuf );

				oapiWriteLogV( "Changed target MLP class to: %s", MLPclassname );
			}
		}

		ahMLP = CreateAttachment(false, MLP_ATTACH_POS, _V(0, -1, 0), MLP_ATTACH_ROT, "XMLP");

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] ={
			{_V( -17.5, DRIVETRUCK_SHOE_OFFSET, 17.5 ), 1e8, 2e7, 0.5, 0.005},
			{_V( -17.5, DRIVETRUCK_SHOE_OFFSET, -17.5 ), 1e8, 2e7, 0.5, 0.005},
			{_V( 17.5, DRIVETRUCK_SHOE_OFFSET, -17.5 ), 1e8, 2e7, 0.5, 0.005},
			{_V( 17.5, DRIVETRUCK_SHOE_OFFSET, 17.5 ), 1e8, 2e7, 0.5}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );
		//ShiftCG(_V(0, -16, 0));

		pgFwdCab->DefineVC();
		pgFwdCab->DefineVCAnimations(fwdVCIdx);
		pgRearCab->DefineVC();
		pgRearCab->DefineVCAnimations(rearVCIdx);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkSetClassCaps" );
		abort();
	}
}

void Crawler::DefineAnimations(bool b1980Mesh)
{
	DefineDrivetruckAnimations();

	if(b1980Mesh) Define1980StrutAnimations();
	else DefineStrutAnimations();
}

void Crawler::DefineDrivetruckAnimations()
{
	// initialize array of groups needed for drivetruck translation animation
	for(int i=0, j=0 ; i<NUMGRP_TRUCK ; i++) {
		if(i!=GRP_JEL__GUIDE_CYLINDERS_TRUCK && i!=GRP_JEL_GUIDE_CYLINDER_DUST_SHIELDS_TRUCK && i!=GRP_DC_TRACTION_MOTOR_BRAKE_DISCS_INNER_TRUCK && i!=GRP_DC_TRACTION_MOTOR_BRAKE_DISCS_OUTER_TRUCK) {
			assert(j < NUMGRP_TRUCK-4); // ensure index is within limits
			DrivetruckGrpList[j]=i;
			j++;
		}
	}
	static UINT GRP_JEL_Cylinders = GRP_JEL__GUIDE_CYLINDERS_TRUCK;
	static UINT GRP_Brake_Discs[2] = {GRP_DC_TRACTION_MOTOR_BRAKE_DISCS_INNER_TRUCK, GRP_DC_TRACTION_MOTOR_BRAKE_DISCS_OUTER_TRUCK};

	static VECTOR3 dummy_vec[4];
	anim_brake_discs = CreateAnimation(0.0);

	MGROUP_ROTATE* Rot_Truck1 = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy_vec[0]), 1, _V(0, 0, 0), _V(-1, 0, 0), static_cast<float>(TRUCK_MAX_TILT));
	anim_truck_rot[0] = CreateAnimation(0.5);
	ANIMATIONCOMPONENT_HANDLE parent = AddManagedAnimationComponent(anim_truck_rot[0], 0.0, 1.0, Rot_Truck1);
	MGROUP_SCALE* Scale_Truck1 = new MGROUP_SCALE(meshidxTruck1, &GRP_JEL_Cylinders, 1, _V(0, 2.548, 0), _V(1, 0.8*JACKING_MAX_HEIGHT, 1));
	anim_truck_trans[0] = CreateAnimation(0.0);
	AddManagedAnimationComponent(anim_truck_trans[0], 0.0, 1.0, Scale_Truck1, parent);
	MGROUP_TRANSLATE* Trans_Truck1 = new MGROUP_TRANSLATE(meshidxTruck1, DrivetruckGrpList, NUMGRP_TRUCK-4, _V(0.0, -JACKING_MAX_HEIGHT, 0.0));
	parent = AddManagedAnimationComponent(anim_truck_trans[0], 0.0, 1.0, Trans_Truck1, parent);
	//brake discs inner truck 1
	InnerBrakeDiscs[0] = new MGROUP_ROTATE(meshidxTruck1,&GRP_Brake_Discs[0],1,_V(INNER_BRAKE_DISK_REF_PT.x,INNER_BRAKE_DISK_REF_PT.y,INNER_BRAKE_DISK_REF_PT.z),_V(0,0,1),static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,InnerBrakeDiscs[0],parent);
	//brake discs outer
	OuterBrakeDiscs[0] = new MGROUP_ROTATE(meshidxTruck1,&GRP_Brake_Discs[1],1,_V(OUTER_BRAKE_DISK_REF_PT.x,OUTER_BRAKE_DISK_REF_PT.y,OUTER_BRAKE_DISK_REF_PT.z),_V(0,0,1),-static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,OuterBrakeDiscs[0], parent);

	MGROUP_ROTATE* Rot_Truck2 = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy_vec[1]), 1, _V(0, 0, 0), _V(-1, 0, 0), static_cast<float>(TRUCK_MAX_TILT));
	anim_truck_rot[1] = CreateAnimation(0.5);
	parent = AddManagedAnimationComponent(anim_truck_rot[1], 0.0, 1.0, Rot_Truck2);
	MGROUP_SCALE* Scale_Truck2 = new MGROUP_SCALE(meshidxTruck2, &GRP_JEL_Cylinders, 1, _V(0, 2.548, 0), _V(1, 0.8*JACKING_MAX_HEIGHT, 1));
	anim_truck_trans[1] = CreateAnimation(0.0);
	AddManagedAnimationComponent(anim_truck_trans[1], 0.0, 1.0, Scale_Truck2, parent);
	MGROUP_TRANSLATE* Trans_Truck2 = new MGROUP_TRANSLATE(meshidxTruck2, DrivetruckGrpList, NUMGRP_TRUCK-4, _V(0.0, -JACKING_MAX_HEIGHT, 0.0));
	parent = AddManagedAnimationComponent(anim_truck_trans[1], 0.0, 1.0, Trans_Truck2, parent);
	//brake discs inner truck 2
	InnerBrakeDiscs[1] = new MGROUP_ROTATE(meshidxTruck2,&GRP_Brake_Discs[0],1,_V(-INNER_BRAKE_DISK_REF_PT.x,INNER_BRAKE_DISK_REF_PT.y,INNER_BRAKE_DISK_REF_PT.z),_V(0,0,1),-static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,InnerBrakeDiscs[1], parent);
	//brake discs outer
	OuterBrakeDiscs[1] = new MGROUP_ROTATE(meshidxTruck2,&GRP_Brake_Discs[1],1,_V(-OUTER_BRAKE_DISK_REF_PT.x,OUTER_BRAKE_DISK_REF_PT.y,OUTER_BRAKE_DISK_REF_PT.z),_V(0,0,1),static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,OuterBrakeDiscs[1], parent);


	MGROUP_ROTATE* Rot_Truck3 = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy_vec[2]), 1, _V(0, 0, 0), _V(-1, 0, 0), static_cast<float>(TRUCK_MAX_TILT));
	anim_truck_rot[2] = CreateAnimation(0.5);
	parent = AddManagedAnimationComponent(anim_truck_rot[2], 0.0, 1.0, Rot_Truck3);
	MGROUP_SCALE* Scale_Truck3 = new MGROUP_SCALE(meshidxTruck3, &GRP_JEL_Cylinders, 1,_V(0, 2.548, 0), _V(1, 0.8*JACKING_MAX_HEIGHT, 1));
	anim_truck_trans[2] = CreateAnimation(0.0);
	AddManagedAnimationComponent(anim_truck_trans[2], 0.0, 1.0, Scale_Truck3, parent);
	MGROUP_TRANSLATE* Trans_Truck3 = new MGROUP_TRANSLATE(meshidxTruck3, DrivetruckGrpList, NUMGRP_TRUCK-4, _V(0.0, -JACKING_MAX_HEIGHT, 0.0));
	parent = AddManagedAnimationComponent(anim_truck_trans[2], 0.0, 1.0, Trans_Truck3, parent);
	//brake discs inner truck 3
	InnerBrakeDiscs[2] = new MGROUP_ROTATE(meshidxTruck3,&GRP_Brake_Discs[0],1,_V(INNER_BRAKE_DISK_REF_PT.x,INNER_BRAKE_DISK_REF_PT.y,INNER_BRAKE_DISK_REF_PT.z),_V(0,0,1),static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,InnerBrakeDiscs[2], parent);
	//brake discs outer
	OuterBrakeDiscs[2] = new MGROUP_ROTATE(meshidxTruck3,&GRP_Brake_Discs[1],1,_V(OUTER_BRAKE_DISK_REF_PT.x,OUTER_BRAKE_DISK_REF_PT.y,OUTER_BRAKE_DISK_REF_PT.z),_V(0,0,1),-static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,OuterBrakeDiscs[2], parent);

	MGROUP_ROTATE* Rot_Truck4 = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(&dummy_vec[3]), 1, _V(0, 0, 0), _V(-1, 0, 0), static_cast<float>(TRUCK_MAX_TILT));
	anim_truck_rot[3] = CreateAnimation(0.5);
	parent = AddManagedAnimationComponent(anim_truck_rot[3], 0.0, 1.0, Rot_Truck4);
	MGROUP_SCALE* Scale_Truck4 = new MGROUP_SCALE(meshidxTruck4, &GRP_JEL_Cylinders, 1,_V(0, 2.548, 0), _V(1, 0.8*JACKING_MAX_HEIGHT, 1));
	anim_truck_trans[3] = CreateAnimation(0.0);
	AddManagedAnimationComponent(anim_truck_trans[3], 0.0, 1.0, Scale_Truck4, parent);
	MGROUP_TRANSLATE* Trans_Truck4 = new MGROUP_TRANSLATE(meshidxTruck4, DrivetruckGrpList, NUMGRP_TRUCK-4, _V(0.0, -JACKING_MAX_HEIGHT, 0.0));
	parent = AddManagedAnimationComponent(anim_truck_trans[3], 0.0, 1.0, Trans_Truck4, parent);
	//brake discs inner truck 4
	InnerBrakeDiscs[3] = new MGROUP_ROTATE(meshidxTruck4,&GRP_Brake_Discs[0],1,_V(-INNER_BRAKE_DISK_REF_PT.x,INNER_BRAKE_DISK_REF_PT.y,INNER_BRAKE_DISK_REF_PT.z),_V(0,0,1),-static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,InnerBrakeDiscs[3], parent);
	//brake discs outer
	OuterBrakeDiscs[3] = new MGROUP_ROTATE(meshidxTruck4,&GRP_Brake_Discs[1],1,_V(-OUTER_BRAKE_DISK_REF_PT.x,OUTER_BRAKE_DISK_REF_PT.y,OUTER_BRAKE_DISK_REF_PT.z),_V(0,0,1),static_cast<float>(360*RAD));
	AddManagedAnimationComponent(anim_brake_discs,0,1,OuterBrakeDiscs[3], parent);
}

void Crawler::clbkPostCreation()
{
	try
	{
		SoundID = ConnectToOrbiterSoundDLL( GetHandle() );
		if (SoundID != -1)
		{
			SetMyDefaultWaveDirectory( const_cast<char*>(SOUND_DIRECTORY) );
			RequestLoadVesselWave( SoundID, ENGINE_SOUND_ID, const_cast<char*>(ENGINE_SOUND_FILE), BOTHVIEW_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, ENGINE_START_SOUND_ID, const_cast<char*>(ENGINE_START_SOUND_FILE), BOTHVIEW_FADED_MEDIUM );
			RequestLoadVesselWave( SoundID, ENGINE_STOP_SOUND_ID, const_cast<char*>(ENGINE_STOP_SOUND_FILE), BOTHVIEW_FADED_MEDIUM );
		}

		psubsystems->RealizeAll();
		pgFwdCab->Realize();
		pgRearCab->Realize();

		// connect DiscPorts
		DiscreteBundle* pBundle = pBundleManager->CreateBundle( "CRAWLER_STEERING_FWD", 16 );
		port_steeringCommand[0].Connect(pBundle, 0);
		port_steeringActualFwd[0].Connect(pBundle, 1);
		port_steeringActualFwd[1].Connect(pBundle, 2);
		GCIRCPBIFwd.Connect( pBundle, 3 );
		CRABPBIFwd.Connect( pBundle, 4 );
		INDEPPBIFwd.Connect( pBundle, 5 );
		ModePBIFwd.Connect( pBundle, 6 );
		GCIRCLightFwd.Connect( pBundle, 7 );
		CRABLightFwd.Connect( pBundle, 8 );
		INDEPLightFwd.Connect( pBundle, 9 );
		ModeLight2Fwd.Connect( pBundle, 10 );
		ModeLight6Fwd.Connect( pBundle, 11 );
		steeringWheelFwd.Connect( pBundle, 15 );

		pBundle = pBundleManager->CreateBundle( "CRAWLER_STEERING_AFT", 16 );
		port_steeringCommand[1].Connect(pBundle, 0);
		port_steeringActualAft[1].Connect(pBundle, 1);
		port_steeringActualAft[0].Connect(pBundle, 2);
		GCIRCPBIAft.Connect( pBundle, 3 );
		CRABPBIAft.Connect( pBundle, 4 );
		INDEPPBIAft.Connect( pBundle, 5 );
		ModePBIAft.Connect( pBundle, 6 );
		GCIRCLightAft.Connect( pBundle, 7 );
		CRABLightAft.Connect( pBundle, 8 );
		INDEPLightAft.Connect( pBundle, 9 );
		ModeLight2Aft.Connect( pBundle, 10 );
		ModeLight6Aft.Connect( pBundle, 11 );
		steeringWheelAft.Connect( pBundle, 15 );

		/*port_steeringCommand[0].SetLine(static_cast<float>(steeringCommanded[0]));
		port_steeringCommand[1].SetLine(static_cast<float>(steeringCommanded[1]));
		port_steeringActual[0].SetLine(static_cast<float>(steeringActual[0]));
		port_steeringActual[1].SetLine(static_cast<float>(steeringActual[1]));*/

		pBundle = pBundleManager->CreateBundle( "CRAWLER_BRAKE_FWD", 16 );
		BrakePBIFwd.Connect( pBundle, 0 );
		BrakeONLightFwd.Connect( pBundle, 1 );
		BrakeOFFLightFwd.Connect( pBundle, 2 );

		pBundle = pBundleManager->CreateBundle( "CRAWLER_BRAKE_AFT", 16 );
		BrakePBIAft.Connect( pBundle, 0 );
		BrakeONLightAft.Connect( pBundle, 1 );
		BrakeOFFLightAft.Connect( pBundle, 2 );

		pBundle = pBundleManager->CreateBundle( "CRAWLER_SPEED_FWD", 16 );
		port_currentSpeedFwd.Connect(pBundle, 0);
		port_targetSpeedFwd.Connect(pBundle, 1);

		pBundle = pBundleManager->CreateBundle( "CRAWLER_SPEED_AFT", 16 );
		port_currentSpeedAft.Connect(pBundle, 0);
		port_targetSpeedAft.Connect(pBundle, 1);

		/*port_currentSpeed.SetLine(static_cast<float>(currentSpeed));
		port_targetSpeed.SetLine(static_cast<float>(targetSpeed));*/

		pBundle = pBundleManager->CreateBundle("CRAWLER_JEL", 1);
		port_JackHeight.Connect(pBundle, 0);
		port_JackHeight.SetLine(static_cast<float>(jackHeight/JACKING_MAX_HEIGHT));

		pBundle = pBundleManager->CreateBundle( "CRAWLER_CONTROL_FWD", 16 );
		CabAckPBIFwd.Connect( pBundle, 0 );
		CabSelectedLightFwd.Connect( pBundle, 1 );
		CabInControlLightFwd.Connect( pBundle, 2 );

		pBundle = pBundleManager->CreateBundle( "CRAWLER_CONTROL_AFT", 16 );
		CabAckPBIAft.Connect( pBundle, 0 );
		CabSelectedLightAft.Connect( pBundle, 1 );
		CabInControlLightAft.Connect( pBundle, 2 );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkPostCreation" );
		abort();
	}
}

void Crawler::clbkPreStep(double simt, double simdt, double mjd)
{
	try
	{
		if (!firstTimestepDone) DoFirstTimestep();

		psubsystems->PreStep(simt, simdt, mjd);
		pgFwdCab->OnPreStep(simt, simdt, mjd);
		pgRearCab->OnPreStep(simt, simdt, mjd);

		vs.version = 2;
		GetStatusEx( &vs );

		// cab control
		if (!cabackPBIpressed)
		{
			if (CabAckPBIFwd.IsSet())
			{
				CabSelectedFwd = !CabSelectedFwd;
				cabackPBIpressed = true;
			}

			if (CabAckPBIAft.IsSet())
			{
				CabSelectedAft = !CabSelectedAft;
				cabackPBIpressed = true;
			}
		}
		else if (!CabAckPBIFwd.IsSet() && !CabAckPBIAft.IsSet()) cabackPBIpressed = false;

		if (CabSelectedFwd && !CabSelectedAft)
		{
			CabInControl = 1;
			CabInControlLightFwd.SetLine();
			CabInControlLightAft.ResetLine();
		}
		else if (!CabSelectedFwd && CabSelectedAft)
		{
			CabInControl = 2;
			CabInControlLightFwd.ResetLine();
			CabInControlLightAft.SetLine();
		}
		else
		{
			CabInControl = 0;
			CabInControlLightFwd.ResetLine();
			CabInControlLightAft.ResetLine();
		}

		CabSelectedLightFwd.SetLine( (int)CabSelectedFwd * 5.0f );
		CabSelectedLightAft.SetLine( (int)CabSelectedAft * 5.0f );

		// parking brake
		if (!brakePBIpressed)
		{
			if (BrakePBIFwd.IsSet() || BrakePBIAft.IsSet())
			{
				ParkingBrakeOn = !ParkingBrakeOn;
				brakePBIpressed = true;
			}
		}
		else if (!BrakePBIFwd.IsSet() && !BrakePBIAft.IsSet()) brakePBIpressed = false;

		if (ParkingBrakeOn)
		{
			BrakeONLightFwd.SetLine();
			BrakeONLightAft.SetLine();
			BrakeOFFLightFwd.ResetLine();
			BrakeOFFLightAft.ResetLine();
		}
		else
		{
			BrakeONLightFwd.ResetLine();
			BrakeONLightAft.ResetLine();
			BrakeOFFLightFwd.SetLine();
			BrakeOFFLightAft.SetLine();
		}

		// steer modes
		if (CabInControl == 1)
		{
			if (GCIRCPBIFwd.IsSet()) Steer = 0;
			else if (CRABPBIFwd.IsSet()) Steer = 1;
			else if (INDEPPBIFwd.IsSet()) Steer = 2;
		}
		else if (CabInControl == 2)
		{
			if (GCIRCPBIAft.IsSet()) Steer = 0;
			else if (CRABPBIAft.IsSet()) Steer = 1;
			else if (INDEPPBIAft.IsSet()) Steer = 2;
		}

		if (Steer == 0)
		{
			GCIRCLightFwd.SetLine();
			GCIRCLightAft.SetLine();
			CRABLightFwd.ResetLine();
			CRABLightAft.ResetLine();
			INDEPLightFwd.ResetLine();
			INDEPLightAft.ResetLine();
		}
		else if (Steer == 1)
		{
			GCIRCLightFwd.ResetLine();
			GCIRCLightAft.ResetLine();
			CRABLightFwd.SetLine();
			CRABLightAft.SetLine();
			INDEPLightFwd.ResetLine();
			INDEPLightAft.ResetLine();
		}
		else //if (Steer == 2)
		{
			GCIRCLightFwd.ResetLine();
			GCIRCLightAft.ResetLine();
			CRABLightFwd.ResetLine();
			CRABLightAft.ResetLine();
			INDEPLightFwd.SetLine();
			INDEPLightAft.SetLine();
		}

		if (!steermodePBIpressed)
		{
			if (ModePBIFwd.IsSet())
			{
				SteerModeFwd = !SteerModeFwd;
				steermodePBIpressed = true;
			}

			if (ModePBIAft.IsSet())
			{
				SteerModeAft = !SteerModeAft;
				steermodePBIpressed = true;
			}
		}
		else if (!ModePBIFwd.IsSet() && !ModePBIAft.IsSet()) steermodePBIpressed = false;

		if (SteerModeFwd)
		{
			ModeLight6Fwd.SetLine();
			ModeLight2Fwd.ResetLine();
		}
		else
		{
			ModeLight6Fwd.ResetLine();
			ModeLight2Fwd.SetLine();
		}

		if (SteerModeAft)
		{
			ModeLight6Aft.SetLine();
			ModeLight2Aft.ResetLine();
		}
		else
		{
			ModeLight6Aft.ResetLine();
			ModeLight2Aft.SetLine();
		}


		// control crawler speed
		/*if(IsAttached()) maxSpeed = MAX_LOADED_SPEED;
		else*/ maxSpeed = MAX_UNLOADED_SPEED;
		//if(IsAttached()) pEngine->SetMaxSpeed(MAX_LOADED_SPEED);
		//else pEngine->SetMaxSpeed(MAX_UNLOADED_SPEED);
		//pEngine->OnPreStep(simt, simdt, mjd);

		//if (IsAttached()) maxVelocity = maxVelocity / 2.0;

		// set target speed
		if(increaseTgtSpeed) {
			double dv = simdt*0.1;
			targetSpeed[viewPos] = range(0.0, targetSpeed[viewPos]+dv, maxSpeed);
		}
		else if(decreaseTgtSpeed) {
			double dv = simdt*-0.1;
			targetSpeed[viewPos] = range(0.0, targetSpeed[viewPos]+dv, maxSpeed);
		}

		// update speed
		double acceleration = pEngine->GetAcceleration();
		if(!Eq(currentSpeed, 0.0, 0.01) || !Eq(acceleration, 0.0))
		{
			// add engine acceleration
			currentSpeed += acceleration * simdt;

			// simulate friction and brakes
			double friction = 0.0025;
			if (PedalBrakeOn) friction += 0.005;// brakes
			if (ParkingBrakeOn) friction += 0.01;

			if (currentSpeed >= 0.0) currentSpeed = max(0.0, currentSpeed - (friction * simdt));
			else currentSpeed = min(0.0, currentSpeed + (friction * simdt));
		}
		else currentSpeed = 0.0;
		port_currentSpeedFwd.SetLine( static_cast<float>(currentSpeed) );
		port_currentSpeedAft.SetLine( static_cast<float>(-currentSpeed) );
		port_targetSpeedFwd.SetLine( static_cast<float>(targetSpeed[0]) );
		port_targetSpeedAft.SetLine( static_cast<float>(targetSpeed[1]) );

		// steering wheel motion
		if (keyRight && (viewPos==VIEWPOS_FRONTCABIN || viewPos==VIEWPOS_REARCABIN))
		{
			double d = STEERING_WHEEL_SPEED * (simdt / oapiGetTimeAcceleration());
			steeringWheel[viewPos] = min(1.0, steeringWheel[viewPos] + d);
		}
		else if (keyLeft && (viewPos==VIEWPOS_FRONTCABIN || viewPos==VIEWPOS_REARCABIN))
		{
			double d = STEERING_WHEEL_SPEED * (simdt / oapiGetTimeAcceleration());
			steeringWheel[viewPos] = max(-1.0, steeringWheel[viewPos] - d);
		}
		else if (keyCenter)
		{
			steeringWheel[viewPos] = 0.0;
		}
		keyLeft = false;
		keyRight = false;
		keyCenter = false;

		steeringWheelFwd.SetLine( static_cast<float>(steeringWheel[0]) );
		steeringWheelAft.SetLine( static_cast<float>(steeringWheel[1]) );


		// track steering
		double steeringAngleScaleFactorFwd = MAX_TURN_ANGLE;
		double steeringAngleScaleFactorAft = MAX_TURN_ANGLE;
		if (!SteerModeFwd) steeringAngleScaleFactorFwd = MAX_TURN_ANGLE / 3.0;
		if (!SteerModeAft) steeringAngleScaleFactorAft = MAX_TURN_ANGLE / 3.0;

		steeringCommanded[0] = steeringWheel[0] * steeringAngleScaleFactorFwd;
		steeringCommanded[1] = steeringWheel[1] * steeringAngleScaleFactorAft;

		port_steeringCommand[0].SetLine( static_cast<float>(steeringCommanded[0] / MAX_TURN_ANGLE) );
		port_steeringCommand[1].SetLine( static_cast<float>(steeringCommanded[1] / MAX_TURN_ANGLE) );

		double cmdfwd = steeringActual[0];
		double cmdaft = steeringActual[1];
		if (CabInControl == 1)
		{
			if (Steer == 0)
			{
				cmdfwd = steeringCommanded[0];
				cmdaft = -steeringCommanded[0];
			}
			else if (Steer == 1)
			{
				cmdfwd = steeringCommanded[0];
				cmdaft = steeringCommanded[0];
			}
			else //if (Steer == 2)
			{
				cmdfwd = steeringCommanded[0];
				cmdaft = steeringCommanded[1];// TODO not sure if should remain unchanged
			}
		}
		else if (CabInControl == 2)
		{
			if (Steer == 0)
			{
				cmdfwd = -steeringCommanded[1];
				cmdaft = /*-*/steeringCommanded[1];
			}
			else if (Steer == 1)
			{
				cmdfwd = steeringCommanded[1];
				cmdaft = steeringCommanded[1];
			}
			else //if (Steer == 2)
			{
				cmdfwd = steeringCommanded[0];// TODO not sure if should remain unchanged
				cmdaft = steeringCommanded[1];
			}
		}

		double dAngle = TRACK_TURN_SPEED * simdt;
		double steeringError = cmdfwd - steeringActual[0];
		if (steeringError < -0.001) steeringActual[0] = max(cmdfwd, steeringActual[0] - dAngle);
		else if (steeringError > 0.001) steeringActual[0] = min(cmdfwd, steeringActual[0] + dAngle);

		steeringError = cmdaft - steeringActual[1];
		if (steeringError < -0.001) steeringActual[1] = max(cmdaft, steeringActual[1] - dAngle);
		else if (steeringError > 0.001) steeringActual[1] = min(cmdaft, steeringActual[1] + dAngle);

		port_steeringActualFwd[0].SetLine( static_cast<float>(steeringActual[0] / MAX_TURN_ANGLE) );
		port_steeringActualAft[0].SetLine( static_cast<float>(steeringActual[0] / MAX_TURN_ANGLE) );
		port_steeringActualFwd[1].SetLine( static_cast<float>(steeringActual[1] / MAX_TURN_ANGLE) );
		port_steeringActualAft[1].SetLine( static_cast<float>(steeringActual[1] / MAX_TURN_ANGLE) );

		// jack crawler to driver target
		if(!Eq(targetjackHeight, JACKING_HEIGHTS[targetJackHeightIndex], 0.001)) {
			if(targetjackHeight < JACKING_HEIGHTS[targetJackHeightIndex])
				targetjackHeight=min(targetjackHeight+0.0025*simdt, JACKING_HEIGHTS[targetJackHeightIndex]);
			else
				targetjackHeight=max(targetjackHeight-0.0025*simdt, JACKING_HEIGHTS[targetJackHeightIndex]);
			UpdateTouchdownPoints();
		}

		// check distance from pads; adjust touchdown points to simulate going up ramp and correct jack height if one JEL hits stops
		for(unsigned int i=0; i<vhLC39.size(); i++) {
			VECTOR3 rpos = CalcRelSurfPos(vhLC39[i], vs);

			if(UpdateTouchdownPoints(rpos)) break;
		}

		port_JackHeight.SetLine(static_cast<float>(jackHeight/JACKING_MAX_HEIGHT));

		surfaceroving->SetHeight( -DRIVETRUCK_SHOE_OFFSET + jackHeight + ((curFrontHeight + curBackHeight) * 0.5) );
		surfaceroving->Move( simdt, currentSpeed, steeringActual[0], steeringActual[1] );

		//braking cylinders animation
		if(oapiGetTimeAcceleration() <= 5.0) //on time acceleration there are some offsets, so we don't want to animate when time accel is enabled
		{
			brake_discs_state += (simdt*currentSpeed*0.44704/5.252742917)*168; //how many evolutions does the disc per second
			if(brake_discs_state > 1)
				brake_discs_state = 0;
			else if(brake_discs_state < 0)
				brake_discs_state = 1;

			SetAnimation(anim_brake_discs,brake_discs_state);
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkPreStep" );
		abort();
	}
}

void Crawler::clbkPostStep(double simt, double simdt, double mjd)
{
	try
	{
		psubsystems->PostStep(simt, simdt, mjd);
		pgFwdCab->OnPostStep(simt, simdt, mjd);
		pgRearCab->OnPostStep(simt, simdt, mjd);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkPostStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkPostStep" );
		abort();
	}
}

void Crawler::DoFirstTimestep() {

	SetView();

	FindLaunchpads();
	hEarth = GetGravityRef();

	if (!standalone) {
		hMLP = GetAttachmentStatus(ahMLP);
		if(hMLP) {
			// find point on MLP we are attached to
			VESSEL* pMLP = oapiGetVesselInterface(hMLP);
			for(DWORD i=0;i<pMLP->AttachmentCount(true);i++) {
				ATTACHMENTHANDLE aH = pMLP->GetAttachmentHandle(true, i);
				if(pMLP->GetAttachmentStatus(aH)==GetHandle()) hMLPAttach = aH;
			}
		}
	}
	firstTimestepDone = true;
}

void Crawler::FindLaunchpads()
{
	for(DWORD i=0;i<oapiGetVesselCount();i++) {
		OBJHANDLE hVessel=oapiGetVesselByIndex(i);
		if(hVessel && !_strnicmp(oapiGetVesselInterface(hVessel)->GetClassName(), "SSV_LC39", 8)) {
			vhLC39.push_back(hVessel);
			//oapiWriteLog("Found pad");
		}
	}
}

void Crawler::clbkLoadStateEx(FILEHANDLE scn, void *status)
{
	try
	{
		char *line;

		while (oapiReadScenario_nextline (scn, line)) {
			if (!_strnicmp (line, "VELOCITY", 8)) {
				sscanf_s(line + 8, "%lf", &currentSpeed);
			} else if (!_strnicmp (line, "STEERING_ACTUAL", 15)) {
				sscanf_s(line + 15, "%lf%lf", &steeringActual[0], &steeringActual[1]);
			} else if (!_strnicmp (line, "JACK_HEIGHT", 11)) {
				sscanf_s(line + 11, "%lf", &targetjackHeight);
			} else if (!_strnicmp (line, "TARGET_JACK_INDEX", 17))
			{
				sscanf_s(line + 17, "%d", &targetJackHeightIndex);
				if (targetJackHeightIndex < 0) targetJackHeightIndex = 0;
				if (targetJackHeightIndex > JACK_HEIGHT_COUNT) targetJackHeightIndex = JACK_HEIGHT_COUNT;
			}
			else if (!_strnicmp (line, "VIEWPOS", 7)) {
				sscanf_s(line + 7, "%i", &viewPos);
			} else if (!_strnicmp (line, "STANDALONE", 10)) {
				sscanf_s(line + 10, "%i", &standalone);
			}
			else if (!_strnicmp( line, "CAB_CONTROL", 11 ))
			{
				int fwd = 0;
				int aft = 0;
				sscanf_s( line + 12, "%d %d %hu", &fwd, &aft, &CabInControl );
				CabSelectedFwd = (fwd != 0);
				CabSelectedAft = (aft != 0);
			}
			else if (!_strnicmp( line, "STEERING_WHEEL", 14 ))
			{
				sscanf_s( line + 15, "%lf %lf", &steeringWheel[0], &steeringWheel[1] );
			}
			else if (!_strnicmp( line, "STEER_TYPE", 10 ))
			{
				sscanf_s( line + 11, "%hu", &Steer );
			}
			else if (!_strnicmp( line, "STEER_MODE", 10 ))
			{
				int fwd = 0;
				int aft = 0;
				sscanf_s( line + 11, "%d %d", &fwd, &aft );
				SteerModeFwd = (fwd != 0);
				SteerModeAft = (aft != 0);
			}
			else if (!_strnicmp( line, "SPEED_CONTROL", 13 ))
			{
				sscanf_s( line + 14, "%lf %lf", &targetSpeed[0], &targetSpeed[1] );
			}
			else if (!_strnicmp( line, "PARKING_BRAKE", 13 ))
			{
				int tmp = 0;
				sscanf_s( line + 14, "%d", &tmp );
				ParkingBrakeOn = (tmp != 0);
			}
			else if (!_strnicmp(line, "@PANEL", 6)) {
				char pszPanelName[30];
				sscanf_s(line+6, "%s", pszPanelName, sizeof(pszPanelName));
				oapiWriteLog(pszPanelName);

				if (!pgFwdCab->ParsePanelBlock( pszPanelName, scn ))
				if (!pgRearCab->ParsePanelBlock( pszPanelName, scn ))
					oapiWriteLogV( "(SSV_CT) [ERROR] Panel %s does not exist", pszPanelName );

				oapiWriteLog("\tLeave @PANEL block.");
			} else {
				if(!psubsystems->ParseScenarioLine(scn, line))
					ParseScenarioLineEx (line, status);
			}
		}

		//UpdateTouchdownPoints();
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkLoadStateEx" );
		abort();
	}
}

void Crawler::clbkSaveState(FILEHANDLE scn)
{
	try
	{
		VESSEL4::clbkSaveState(scn);

		char cbuf[255];

		oapiWriteScenario_float(scn, "VELOCITY", currentSpeed);

		sprintf_s(cbuf, 255, "%f %f", steeringActual[0], steeringActual[1]);
		oapiWriteScenario_string(scn, "STEERING_ACTUAL", cbuf);

		oapiWriteScenario_float(scn, "JACK_HEIGHT", targetjackHeight);
		oapiWriteScenario_int(scn, "TARGET_JACK_INDEX", targetJackHeightIndex);

		oapiWriteScenario_int(scn, "VIEWPOS", viewPos);
		oapiWriteScenario_int(scn, "STANDALONE", standalone);

		sprintf_s( cbuf, 255, "%d %d %hu", CabSelectedFwd, CabSelectedAft, CabInControl );
		oapiWriteScenario_string( scn, "CAB_CONTROL", cbuf );

		sprintf_s( cbuf, 255, "%f %f", steeringWheel[0], steeringWheel[1] );
		oapiWriteScenario_string( scn, "STEERING_WHEEL", cbuf );

		oapiWriteScenario_int( scn, "STEER_TYPE", Steer );

		sprintf_s( cbuf, 255, "%d %d", SteerModeFwd, SteerModeAft );
		oapiWriteScenario_string( scn, "STEER_MODE", cbuf );

		sprintf_s( cbuf, 255, "%f %f", targetSpeed[0], targetSpeed[1] );
		oapiWriteScenario_string( scn, "SPEED_CONTROL", cbuf );

		oapiWriteScenario_int( scn, "PARKING_BRAKE", ParkingBrakeOn );

		psubsystems->SaveState(scn);
		pgFwdCab->OnSaveState(scn);
		pgRearCab->OnSaveState(scn);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkSaveState" );
		abort();
	}
}

int Crawler::clbkConsumeDirectKey(char *kstate)
{
	try
	{
		if (!firstTimestepDone) return 0;

		if (KEYMOD_SHIFT(kstate) /*|| KEYMOD_CONTROL(kstate)*/) {
			return 0;
		}

		if (KEYDOWN(kstate, OAPI_KEY_NUMPAD1)) {
			keyLeft = true;
			RESETKEY(kstate, OAPI_KEY_NUMPAD1);
		}
		if (KEYDOWN(kstate, OAPI_KEY_NUMPAD2)) {
			keyCenter = true;
			RESETKEY(kstate, OAPI_KEY_NUMPAD2);
		}
		if (KEYDOWN(kstate, OAPI_KEY_NUMPAD3)) {
			keyRight = true;
			RESETKEY(kstate, OAPI_KEY_NUMPAD3);
		}
		if (KEYDOWN(kstate, OAPI_KEY_NUMPAD5)) {
			keyCenter = true;
			RESETKEY(kstate, OAPI_KEY_NUMPAD5);
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkConsumeDirectKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkConsumeDirectKey" );
		abort();
	}
}

int Crawler::clbkConsumeBufferedKey(DWORD key, bool down, char *kstate)
{
	try
	{
		if (!firstTimestepDone) return 0;

		if(KEYMOD_CONTROL(kstate)) {
			if(!down && key == OAPI_KEY_3) {
				pgFwdCab->ToggleCoordinateDisplayMode();
				pgRearCab->ToggleCoordinateDisplayMode();
				oapiWriteLog("Toggling coordinate display mode");
				return 1;
			}
			else if(!down && key == OAPI_KEY_J) {
				targetJackHeightIndex = min(targetJackHeightIndex+1, JACK_HEIGHT_COUNT-1);
				return 1;
			}
			else if(!down && key == OAPI_KEY_K) {
				targetJackHeightIndex = max(targetJackHeightIndex-1, 0);
				return 1;
			}
			else return 0;
		}

		if (KEYMOD_SHIFT(kstate)) {
			return 0;
		}

		if (key == OAPI_KEY_ADD) {
			//pEngine->IncreaseTgtSpeed(down);
			increaseTgtSpeed = down;
			decreaseTgtSpeed = false;
			return 1;
		}
		else if (key == OAPI_KEY_SUBTRACT) {
			//pEngine->DecreaseTgtSpeed(down);
			decreaseTgtSpeed = down;
			increaseTgtSpeed = false;
			return 1;
		}
		else if (key == OAPI_KEY_B) {
			if(down) PedalBrakeOn = true;
			else PedalBrakeOn = false;
			return 1;
		}

		if(down) {
			if (key == OAPI_KEY_J) {
				if (IsAttached())
					Detach();
				else
					Attach();
				return 1;
			}

			if(bGenericCockpitView) {
				if (key == OAPI_KEY_1) {
					SetView(VIEWPOS_FRONTCABIN);
					return 1;
				}
				if (key == OAPI_KEY_2) {
					SetView(VIEWPOS_REARCABIN);
					return 1;
				}
				if (key == OAPI_KEY_3) {
					SetView(VIEWPOS_ENGINEERING);
					return 1;
				}
				if (key == OAPI_KEY_4) {
					SetView(VIEWPOS_GROUND);
					return 1;
				}
				if (key == OAPI_KEY_5) {
					SetView(VIEWPOS_FRONTGANGWAY);
					return 1;
				}
				if (key == OAPI_KEY_6) {
					SetView(VIEWPOS_REARGANGWAY);
					return 1;
				}
				if (key == OAPI_KEY_7) {
					SetView(VIEWPOS_RIGHTREARGANGWAY);
					return 1;
				}
			}

			if(key==OAPI_KEY_G) {
				oapiSetShowGrapplePoints(true);
				return 1;
			}
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkConsumeBufferedKey" );
		abort();
	}
}

void Crawler::Attach() {

	if (standalone) return;
	//if (!Eq(pEngine->GetSpeed(), 0.0)) return;
	if (!Eq(currentSpeed, 0.0)) return;
	if (IsAttached()) return;

	VECTOR3 pos, dir, rot;
	VECTOR3 gpos, gattach;

	Local2Global(MLP_ATTACH_POS, gattach);

	for(DWORD i=0; i<oapiGetVesselCount(); i++) {
		OBJHANDLE hV=oapiGetVesselByIndex(i);
		if(hV == GetHandle()) continue;

		VESSEL* pVessel=oapiGetVesselInterface(hV);
		std::string className=pVessel->GetClassName();
		if(className == MLPclassname) { //found an MLP
			ATTACHMENTHANDLE ahAttach=pVessel->GetAttachmentHandle(true, 0);

			//check attachment string
			if(_strnicmp(pVessel->GetAttachmentId(ahAttach), "XMLP", 4)) continue;

			pVessel->GetAttachmentParams(ahAttach, pos, dir, rot);
			pVessel->Local2Global(pos, gpos);

			VECTOR3 gdist = gpos-gattach;
			MATRIX3 RotMatrix;
			GetRotationMatrix(RotMatrix);
			VECTOR3 ldist = tmul(RotMatrix, gdist);
			if (length(_V(ldist.x, 0.0, ldist.z)) < 0.1 && abs(ldist.y) < 0.05)
			{
				// if MLP is attached to something else, detach it
				if(pVessel->GetAttachmentStatus(ahAttach)) {
					VESSEL* pParent = oapiGetVesselInterface(pVessel->GetAttachmentStatus(ahAttach));
					for(DWORD j=0;j<pParent->AttachmentCount(false);j++) {
						ATTACHMENTHANDLE ahParent = pParent->GetAttachmentHandle(false, j);
						if(pParent->GetAttachmentStatus(ahParent)==hV) {
							pParent->DetachChild(ahParent);
							oapiWriteLogV( "(SSV_CT) [INFO] Detached MLP '%s' from vessel '%s'", pVessel->GetName(), pParent->GetName() );
							break;
						}
					}
				}

				AttachChild(hV, ahMLP, ahAttach);
				hMLP = hV;
				hMLPAttach = ahAttach;
				oapiWriteLogV( "(SSV_CT) [INFO] Attached MLP '%s'", pVessel->GetName()  );
				break; // get out of for_loop
			}
			else oapiWriteLogV( "(SSV_CT) [INFO] Failed to attach MLP '%s'\n\thorizontal offset: %.2f (limit 0.1)\n\tvertical offset %.2f (limit 0.05)",
				pVessel->GetName(), length( _V( ldist.x, 0.0, ldist.z ) ), fabs( ldist.y ) );
		}
	}
}

void Crawler::Detach()
{
	if (standalone) return;
	if (!Eq(currentSpeed, 0.0)) return;
	if (!IsAttached()) return;

	// loop thorugh all landed vessels and find one within range with MLP attach point
	// release MLP and attach it to vessel
	for(DWORD i=0;i<oapiGetVesselCount();i++) {
		OBJHANDLE hV = oapiGetVesselByIndex(i);
		if(hV == GetHandle()) continue;
		VESSEL* pV = oapiGetVesselInterface(hV);

		// check if vessel is landed
		if((pV->GetFlightStatus() & 1)) {
			VECTOR3 rpos = CalcRelSurfPos(hV, vs);

			for(DWORD j=0;j<pV->AttachmentCount(false);j++) {
				ATTACHMENTHANDLE aH = pV->GetAttachmentHandle(false, j);
				if(!_strnicmp("XMLP", pV->GetAttachmentId(aH), 4) && !pV->GetAttachmentStatus(aH)) {
					VECTOR3 attach_pos, attach_dir, attach_rot;
					VECTOR3 pt1, pt2, pt3;
					double heading;
					pV->GetAttachmentParams(aH, attach_pos, attach_dir, attach_rot);
					pV->GetTouchdownPoints(pt1, pt2, pt3);
					oapiGetHeading(hV, &heading);

					attach_pos = rpos-RotateVectorY(attach_pos, heading*DEG)+MLP_ATTACH_POS;
					attach_pos.y+=(jackHeight+curFrontHeight+pt1.y); //we can use any TD point; y coordinate should be the same

					if (length(_V(attach_pos.x, 0.0, attach_pos.z)) < 0.1 && abs(attach_pos.y) < 0.05)// attach MLP to VAB/LC39
					{
						DetachChild(ahMLP);
						bool success = pV->AttachChild(hMLP, aH, hMLPAttach);
						hMLP = NULL;
						hMLPAttach = NULL;

						if (!success) oapiWriteLogV( "(SSV_CT) [ERROR] Failed to attach MLP to vessel '%s'", pV->GetName() );
						else oapiWriteLogV( "(SSV_CT) [INFO] Attached MLP to vessel '%s'", pV->GetName() );
					}
					//else
					{
						oapiWriteLogV( "(SSV_CT) [INFO] Failed to attach MLP to vessel '%s'\n\thorizontal offset: %.2f (limit 0.1)\n\tvertical offset %.2f (limit 0.05)",
							pV->GetName(), length( _V( attach_pos.x, 0.0, attach_pos.z ) ), fabs( attach_pos.y ) );
					}
				}
			}
		}
	}
}

bool Crawler::IsAttached() {

	if (standalone) return false;

	return (GetAttachmentStatus(ahMLP) != NULL);
}

void Crawler::SetView() {
	SetView(viewPos);
}

void Crawler::SetView(int viewpos) {

	viewPos = viewpos;
	if (viewPos == VIEWPOS_REARCABIN) {
		SetCameraOffset(CRAWLER_REAR_VC_OFFSET + _V(0.0, 0.456, 0.476));
		SetCameraShiftRange(_V(0.0, 0.2, -0.3), _V(0, 0, 0), _V(0, 0, 0));
		SetCameraDefaultDirection(_V(0, 0, -1));
		SetMeshesVisibility(MESHVIS_ALWAYS);

	} else if (viewPos == VIEWPOS_FRONTCABIN) {
		SetCameraOffset(CRAWLER_FWD_VC_OFFSET + _V(0.0, 0.456, -0.476));
		SetCameraShiftRange(_V(0.0, 0.2, 0.3), _V(0, 0, 0), _V(0, 0, 0));
		SetCameraDefaultDirection(_V(0, 0, 1));
		SetMeshesVisibility(MESHVIS_ALWAYS);

	} else if (viewPos == VIEWPOS_ENGINEERING) {
		SetCameraOffset(_V(4.4, 4.1, -1.3));
		SetCameraDefaultDirection(_V(-1,0,0));
		SetMeshesVisibility(MESHVIS_ALWAYS | MESHVIS_EXTPASS);

	} else if (viewPos == VIEWPOS_GROUND) {
		SetCameraOffset(_V(21.5, 1.75, 1));
		SetCameraDefaultDirection(_V(0, 0, 1));
		SetMeshesVisibility(MESHVIS_ALWAYS | MESHVIS_EXTPASS);

	} else if (viewPos == VIEWPOS_FRONTGANGWAY) {
		SetCameraOffset(_V(0, 4.1, 19.934));
		SetCameraDefaultDirection(_V(0, 0, 1));
		SetMeshesVisibility(MESHVIS_ALWAYS);

	} else if (viewPos == VIEWPOS_REARGANGWAY) {
		SetCameraOffset(_V(0, 4.1, -19.234));
		SetCameraDefaultDirection(_V(0, 0, -1));
		SetMeshesVisibility(MESHVIS_ALWAYS);

	} else if (viewPos == VIEWPOS_RIGHTREARGANGWAY) {
		SetCameraOffset(_V(15, 5.7, -11.934));
		SetCameraDefaultDirection(_V(0, 0, -1));
		SetMeshesVisibility(MESHVIS_ALWAYS);
	}
	oapiCameraSetCockpitDir(0, 0);
}

void Crawler::SetMeshesVisibility(WORD mode) {

	SetMeshVisibilityMode(meshidxCrawler, mode);
	SetMeshVisibilityMode(meshidxTruck1, mode);
	SetMeshVisibilityMode(meshidxTruck2, mode);
	SetMeshVisibilityMode(meshidxTruck3, mode);
	SetMeshVisibilityMode(meshidxTruck4, mode);

}

void Crawler::SlowIfDesired(double timeAcceleration) {

	if (oapiGetTimeAcceleration() > timeAcceleration) {
		oapiSetTimeAcceleration(timeAcceleration);
	}
}

void Crawler::clbkVisualCreated(VISHANDLE vis, int refcount)
{
	try
	{
		vccVis = vis;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVisualCreated" );
		abort();
	}
}

void Crawler::clbkVisualDestroyed(VISHANDLE vis, int refcount)
{
	try
	{
		vccVis = NULL;
		// reset the variables keeping track of console mesh animation
		vccSpeed = 0;
		vccSteering = 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVisualDestroyed: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVisualDestroyed" );
		abort();
	}
}

bool Crawler::clbkLoadGenericCockpit()
{
	try
	{
		bGenericCockpitView = true;
		SetView();
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkLoadGenericCockpit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkLoadGenericCockpit" );
		abort();
	}
}

bool Crawler::clbkLoadVC (int id)
{
	try
	{
		bool bValid = false;

		switch(id) {
			case VIEWPOS_FRONTCABIN:
			case VIEWPOS_REARCABIN:
				//oapiWriteLog("Showing VC");
				if(id==VIEWPOS_FRONTCABIN) pgFwdCab->RegisterVC();
				else pgRearCab->RegisterVC();
				oapiVCSetNeighbours(1-id, 1-id, VIEWPOS_ENGINEERING, VIEWPOS_GROUND); // left, right neighbours are other panels
				bValid = true;
				break;
			case VIEWPOS_ENGINEERING:
				oapiVCSetNeighbours(-1, -1, -1, VIEWPOS_FRONTGANGWAY);
				bValid = true;
				break;
			case VIEWPOS_GROUND:
				oapiVCSetNeighbours(-1, -1, VIEWPOS_FRONTGANGWAY, -1);
				bValid = true;
				break;
			case VIEWPOS_FRONTGANGWAY:
				oapiVCSetNeighbours(VIEWPOS_REARGANGWAY, VIEWPOS_RIGHTREARGANGWAY, VIEWPOS_ENGINEERING, VIEWPOS_FRONTCABIN);
				bValid = true;
				break;
			case VIEWPOS_REARGANGWAY:
				oapiVCSetNeighbours(VIEWPOS_RIGHTREARGANGWAY, VIEWPOS_FRONTGANGWAY, VIEWPOS_ENGINEERING, VIEWPOS_REARCABIN);
				bValid = true;
				break;
			case VIEWPOS_RIGHTREARGANGWAY:
				oapiVCSetNeighbours(VIEWPOS_FRONTGANGWAY, VIEWPOS_REARGANGWAY, VIEWPOS_ENGINEERING, VIEWPOS_REARCABIN);
				bValid = true;
				break;
		}

		if(bValid) {
			bGenericCockpitView = false;
			SetView(id);
		}

		return bValid;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkLoadVC: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkLoadVC" );
		abort();
	}
}

bool Crawler::clbkVCMouseEvent(int id, int event, VECTOR3& p)
{
	try
	{
		oapiWriteLog("clbkVCMouseEvent called");

		if (pgFwdCab->OnVCMouseEvent( id, event, p ))
			return true;
		if (pgRearCab->OnVCMouseEvent( id, event, p ))
			return true;
		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVCMouseEvent: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVCMouseEvent" );
		abort();
	}
}

bool Crawler::clbkVCRedrawEvent(int id, int event, SURFHANDLE surf)
{
	try
	{
		if(pgFwdCab->OnVCRedrawEvent(id, event, surf))
			return true;
		if(pgRearCab->OnVCRedrawEvent(id, event, surf))
			return true;

		return false;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVCRedrawEvent: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_CT) [FATAL ERROR] Exception in Crawler::clbkVCRedrawEvent" );
		abort();
	}
}

bool Crawler::UpdateTouchdownPoints(const VECTOR3 &relPos)
{
	double front_dist, back_dist;
	double dist=fabs(relPos.z);//length(relPos);
	double dCos = cos(GetYaw()/*lastHead*/);

	front_dist = dist-(DRIVETRUCK_Z_OFFSET+5.723)*abs(dCos);
	back_dist = dist+(DRIVETRUCK_Z_OFFSET+5.723)*abs(dCos);

	// ramp to LC39 starts 390 m from pad and ends 131.5 m from pad
	if(front_dist < LC39_RAMP_START && abs(relPos.x)<10.0)
	{
		double front_dist2 = dist-(DRIVETRUCK_Z_OFFSET-5.723)*abs(dCos);
		double back_dist2 = dist+(DRIVETRUCK_Z_OFFSET-5.723)*abs(dCos);

		double front_height = CalcRampHeight(front_dist);
		double back_height = CalcRampHeight(back_dist);
		double front_height2 = CalcRampHeight(front_dist2);
		double back_height2 = CalcRampHeight(back_dist2);

		double fwdAngle=atan((front_height-front_height2)/(front_dist2-front_dist));
		double backAngle=atan((back_height2-back_height)/(back_dist-back_dist2));
		double fwd_rot_anim_pos = fwdAngle / TRUCK_MAX_TILT;
		double back_rot_anim_pos = backAngle / TRUCK_MAX_TILT;
		if(dCos<0.0) {
			fwd_rot_anim_pos = -fwd_rot_anim_pos;
			back_rot_anim_pos = -back_rot_anim_pos;
		}

		curFrontHeight=CalcRampHeight(dist-DRIVETRUCK_Z_OFFSET);//front_height;
		curBackHeight=CalcRampHeight(dist+DRIVETRUCK_Z_OFFSET);//back_height2;
		curFrontAngle=fwdAngle;
		curBackAngle=backAngle;

		UpdateTouchdownPoints();

		return true;
	}
	else {
		curFrontHeight=curBackHeight=0.0;
		curFrontAngle=curBackAngle=0.0;
		UpdateTouchdownPoints();
	}
	return false;
}

void Crawler::UpdateTouchdownPoints( void )
{
	double dCos = cos(GetYaw()/*lastHead*/);
	unsigned short usAftIndex, usFwdIndex; // indicates which tracks are at 'aft' of crawler
	if(dCos >= 0.0) {
		usAftIndex = 2;
		usFwdIndex = 0;
	}
	else {
		usAftIndex = 0;
		usFwdIndex = 2;
	}

	double fwd_rot_anim_pos = curFrontAngle / TRUCK_MAX_TILT;
	double back_rot_anim_pos = curBackAngle / TRUCK_MAX_TILT;
	if(dCos<0.0) {
		fwd_rot_anim_pos = -fwd_rot_anim_pos;
		back_rot_anim_pos = -back_rot_anim_pos;
	}

	// calc front and back jack heights, spliting the ramp jacking needs and limiting to JEL range
	double jackheightstep = (curFrontHeight - curBackHeight) * 0.5;
	double front_jackheight = targetjackHeight - jackheightstep;
	double back_jackheight = targetjackHeight + jackheightstep;
	if (front_jackheight < JACKING_HEIGHTS[0])
	{
		// shift "excess" to other end
		back_jackheight += JACKING_HEIGHTS[0] - front_jackheight;
		// limit this end
		front_jackheight = JACKING_HEIGHTS[0];
	}
	else if (back_jackheight > JACKING_HEIGHTS[JACK_HEIGHT_COUNT - 1])
	{
		// shift "excess" to other end
		front_jackheight -= back_jackheight - JACKING_HEIGHTS[JACK_HEIGHT_COUNT - 1];
		// limit this end
		back_jackheight = JACKING_HEIGHTS[JACK_HEIGHT_COUNT - 1];
	}

	// update average jacking height
	jackHeight = (front_jackheight + back_jackheight) * 0.5;

	DWORD ntdvtx = 4;
	static TOUCHDOWNVTX tdvtx[4] ={
		{_V( -17.5, DRIVETRUCK_SHOE_OFFSET + jackHeight + ((curFrontHeight + curBackHeight) * 0.5), 17.5 ), 1e8, 2e7, 0.5, 0.005},
		{_V( -17.5, DRIVETRUCK_SHOE_OFFSET + jackHeight + ((curFrontHeight + curBackHeight) * 0.5), -17.5 ), 1e8, 2e7, 0.5, 0.005},
		{_V( 17.5, DRIVETRUCK_SHOE_OFFSET + jackHeight + ((curFrontHeight + curBackHeight) * 0.5), -17.5 ), 1e8, 2e7, 0.5, 0.005},
		{_V( 17.5, DRIVETRUCK_SHOE_OFFSET + jackHeight + ((curFrontHeight + curBackHeight) * 0.5), 17.5 ), 1e8, 2e7, 0.5},
	};
	SetTouchdownPoints( tdvtx, ntdvtx );
	for(int i=0;i<2;i++) {
		SetAnimation(anim_truck_rot[i+usFwdIndex], 0.5+fwd_rot_anim_pos);
		SetAnimation(anim_truck_rot[i+usAftIndex], 0.5+back_rot_anim_pos);

		SetAnimation( anim_truck_trans[usFwdIndex + i], front_jackheight / JACKING_MAX_HEIGHT );
		SetAnimation( anim_truck_trans[usAftIndex + i], back_jackheight / JACKING_MAX_HEIGHT );
	}

	return;
}

ANIMATIONCOMPONENT_HANDLE Crawler::AddManagedAnimationComponent(UINT anim, double state0, double state1,
		MGROUP_TRANSFORM *trans, ANIMATIONCOMPONENT_HANDLE parent)
{
	/*for(unsigned short i=0;i<vpAnimations.size();i++) {
		if(vpAnimations.at(i) == trans) {
			oapiWriteLog("ERROR: adding animation twice");
			return NULL;
		}
	}*/
	vpAnimations.push_back(trans);
	return AddAnimationComponent(anim, state0, state1, trans, parent);
}

VECTOR3 Crawler::CalcRelSurfPos(OBJHANDLE hVessel, const VESSELSTATUS2& vs) const
{
	double padLat, padLong, padRad;
	oapiGetEquPos(hVessel, &padLong, &padLat, &padRad);
	return _V( padLong - vs.surf_lng, 0.0, padLat - vs.surf_lat ) * oapiGetSize( hEarth );// HACK error should be very small at KSC's elevation
}

DiscreteBundleManager* Crawler::BundleManager() const
{
	return pBundleManager;
}

int Crawler::GetSoundID() const
{
	return SoundID;
}

MESHHANDLE Crawler::GetVCMesh(vc::CRAWLER_CAB cab) const
{
	if(cab==vc::FWD) return hFwdVCMesh;
	else return hRearVCMesh;
}

UINT Crawler::GetVCMeshIdx( vc::CRAWLER_CAB cab ) const
{
	if (cab == vc::FWD) return fwdVCIdx;
	else return rearVCIdx;
}

double Crawler::CalcRampHeight(double dist) const
{
	return range( 0.0, (LC39_RAMP_START - dist) * (LC39_SURFACE_HEIGHT / (LC39_RAMP_START - LC39_RAMP_END)), LC39_SURFACE_HEIGHT );
};