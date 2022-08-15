/****************************************************************************
  This file is part of Space Shuttle Vessel

  Crawler Transporter vessel definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/08/31   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/08/05   GLS
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
  *	$Log: Crawler.h,v $
  *	Revision 1.1  2009/02/18 23:21:14  tschachim
  *	Moved files as proposed by Artlav.
  *	
  *	Revision 1.16  2007/12/15 19:48:26  lassombra
  *	Added functionality to allow ProjectApollo MFD to get mission time from the Crawler as well as the Saturn.  The Crawler actually extracts the mission time from the Saturn, no updates to scenario files needed.
  *	
  *	Revision 1.15  2007/08/16 16:49:53  tschachim
  *	New meshes.
  *	
  *	Revision 1.14  2007/03/03 00:14:41  tschachim
  *	Bugfix generic cockpit.
  *	
  *	Revision 1.13  2007/03/02 18:34:37  tschachim
  *	Improved crawler VC.
  *	
  *	Revision 1.12  2007/03/01 17:58:26  tschachim
  *	New VC panel
  *	
  *	Revision 1.11  2006/06/26 19:05:36  movieman523
  *	More doxygen, made Lunar EVA a VESSEL2, made SM breakup, made LRV use VESSEL2 save/load functions.
  *	
  *	Revision 1.10  2006/04/25 13:32:50  tschachim
  *	New KSC.
  *	
  *	Revision 1.9  2005/11/23 21:36:55  movieman523
  *	Allow specification of LV name in scenario file.
  *	
  *	Revision 1.8  2005/10/31 19:18:39  tschachim
  *	Bugfixes.
  *	
  *	Revision 1.7  2005/10/31 10:30:35  tschachim
  *	New VAB.
  *	
  *	Revision 1.6  2005/08/05 13:01:49  tschachim
  *	Saturn detachment handling
  *	
  *	Revision 1.5  2005/07/05 17:23:11  tschachim
  *	Scenario saving/loading
  *	
  *	Revision 1.4  2005/07/01 12:23:48  tschachim
  *	Introduced standalone flag
  *	
  *	Revision 1.3  2005/06/29 11:01:18  tschachim
  *	new dynamics, added attachment management
  *	
  *	Revision 1.2  2005/06/14 16:14:41  tschachim
  *	File header inserted.
  *	
  **************************************************************************/
#ifndef _CRAWLER_H
#define _CRAWLER_H
#pragma once

#include <vector>
#include <Orbitersdk.h>
#include <discsignals.h>
#include <PanelGroup.h>
#include <SubsystemDirector.h>
#include "meshres_drivetruck.h"
#include "Crawler_vc_defs.h"


class CrawlerEngine;
class SurfaceRoving;

using namespace discsignals;

typedef struct
{
	HINSTANCE hDll;
	SURFHANDLE digits_7seg;
} GlobalHandles;


///
/// \ingroup Ground
///
class Crawler: public VESSEL4 {

public:
	Crawler(OBJHANDLE hObj, int fmodel);
	virtual ~Crawler();

	void clbkSetClassCaps(FILEHANDLE cfg) override;
	void clbkLoadStateEx(FILEHANDLE scn, void *status) override;
	void clbkSaveState(FILEHANDLE scn) override;
	int clbkConsumeDirectKey(char *kstate) override;
	int clbkConsumeBufferedKey(DWORD key, bool down, char *kstate) override;
	void clbkPostCreation() override;
	void clbkPreStep (double simt, double simdt, double mjd) override;
	void clbkPostStep(double simt, double simdt, double mjd) override;
	void clbkVisualCreated(VISHANDLE vis, int refcount) override;
	void clbkVisualDestroyed(VISHANDLE vis, int refcount) override;

	bool clbkLoadGenericCockpit() override;
	bool clbkLoadVC (int id) override;
	bool clbkVCMouseEvent(int id, int event, VECTOR3& p) override;
	bool clbkVCRedrawEvent(int id, int event, SURFHANDLE surf) override;

	DiscreteBundleManager* BundleManager() const;
	int GetSoundID() const;
	MESHHANDLE GetVCMesh(vc::CRAWLER_CAB cab) const;
	UINT GetVCMeshIdx( vc::CRAWLER_CAB cab ) const;


private:
	void DoFirstTimestep();
	/**
	 * Populates vector with all launchpads in scenario
	 **/
	void FindLaunchpads();
	bool IsAttached();
	void Attach();
	void Detach();
	void SetView();
	void SetView(int viewpos);
	void SlowIfDesired(double timeAcceleration);
	void SetMeshesVisibility(WORD mode);

	void DefineAnimations(bool b1980Mesh);
	void DefineDrivetruckAnimations();
	void DefineStrutAnimations();
	void Define1980StrutAnimations();

	/**
	 * Returns crawler position in vessel-centered local horizon frame
	 * Assumes vessels are close and Earth is flat
	 * @param hVessel -handle of target vessel
	 * @param vs -struct containing crawler's current surf. position
	 */
	VECTOR3 CalcRelSurfPos(OBJHANDLE hVessel, const VESSELSTATUS2& vs) const;
	/**
	 * Sets touchdown points based on position relative to launchpad.
	 * @returns true if crawler is on pad ramp/surface
	 */
	bool UpdateTouchdownPoints(const VECTOR3 &relPos);
	/**
	 * Sets touchdown points based on current hieght/angle values
	 */
	void UpdateTouchdownPoints( void );
	/**
	 * Wrapper for AddAnimationComponent function
	 * MGROUP_TRANSFORM passed MUST be allocated with new and will be deleted by destructor
	 */
	ANIMATIONCOMPONENT_HANDLE AddManagedAnimationComponent(UINT anim, double state0, double state1,
		MGROUP_TRANSFORM *trans, ANIMATIONCOMPONENT_HANDLE parent = NULL);

	double CalcRampHeight(double dist) const;

public:
	VISHANDLE vccVis;

	unsigned short GetCabInControl( void ) const {return CabInControl;}
private:
	SubsystemDirector<Crawler>* psubsystems;
	DiscreteBundleManager* pBundleManager;

	vc::PanelGroup<Crawler>* pgFwdCab;
	vc::PanelGroup<Crawler>* pgRearCab;

	CrawlerEngine* pEngine;
	SurfaceRoving* surfaceroving;

	double targetSpeed[2];
	double currentSpeed;
	double maxSpeed;
	bool velocityStop;
	bool bGenericCockpitView;
	int viewPos;
	double steeringWheel[2];// steering wheel position [-1.0 (left); +1.0 (right)]
	double steeringActual[2];// actual steering angle [deg]
	double steeringCommanded[2];// commanded steering wheel position [deg]
	bool increaseTgtSpeed;
	bool decreaseTgtSpeed;
	int standalone;
	bool firstTimestepDone;

	double curFrontHeight, curBackHeight; // height above ground (m)
	double curFrontAngle, curBackAngle; // angle rel. to horizontal (rad)
	double targetjackHeight; // target height to which platform has/is to been jacked.
	double jackHeight; // height to which platform has been jacked.
	int targetJackHeightIndex; // index of target height

	VESSELSTATUS2 vs;

	DiscInPort CabAckPBIFwd;
	DiscInPort CabAckPBIAft;
	DiscOutPort CabSelectedLightFwd;
	DiscOutPort CabSelectedLightAft;
	DiscOutPort CabInControlLightFwd;
	DiscOutPort CabInControlLightAft;

	DiscInPort BrakePBIFwd;
	DiscInPort BrakePBIAft;
	DiscOutPort BrakeONLightFwd;
	DiscOutPort BrakeOFFLightFwd;
	DiscOutPort BrakeONLightAft;
	DiscOutPort BrakeOFFLightAft;

	DiscInPort GCIRCPBIFwd;
	DiscInPort GCIRCPBIAft;
	DiscOutPort GCIRCLightFwd;
	DiscOutPort GCIRCLightAft;
	DiscInPort CRABPBIFwd;
	DiscInPort CRABPBIAft;
	DiscOutPort CRABLightFwd;
	DiscOutPort CRABLightAft;
	DiscInPort INDEPPBIFwd;
	DiscInPort INDEPPBIAft;
	DiscOutPort INDEPLightFwd;
	DiscOutPort INDEPLightAft;

	DiscInPort ModePBIFwd;
	DiscInPort ModePBIAft;
	DiscOutPort ModeLight6Fwd;
	DiscOutPort ModeLight2Fwd;
	DiscOutPort ModeLight6Aft;
	DiscOutPort ModeLight2Aft;

	DiscOutPort port_JackHeight;
	DiscOutPort steeringWheelFwd;
	DiscOutPort steeringWheelAft;
	DiscOutPort port_steeringCommand[2];
	DiscOutPort port_steeringActualFwd[2];
	DiscOutPort port_steeringActualAft[2];
	DiscOutPort port_currentSpeedFwd;
	DiscOutPort port_currentSpeedAft;
	DiscOutPort port_targetSpeedFwd;
	DiscOutPort port_targetSpeedAft;

	bool cabackPBIpressed;
	bool CabSelectedFwd;
	bool CabSelectedAft;
	unsigned short CabInControl;// 0 = none, 1 = fwd, 2 = aft

	bool brakePBIpressed;
	bool ParkingBrakeOn;
	bool PedalBrakeOn;

	unsigned short Steer;// 0 = GCRIC, 1 = CRAB, 2 = INDEP

	bool steermodePBIpressed;
	bool SteerModeFwd;// true = 6º, false = 2º
	bool SteerModeAft;// true = 6º, false = 2º

	bool keyLeft;
	bool keyRight;
	bool keyCenter;

	OBJHANDLE hMLP;
	ATTACHMENTHANDLE hMLPAttach;
	ATTACHMENTHANDLE ahMLP;
	char MLPclassname[255];

	MESHHANDLE hFwdVCMesh;
	MESHHANDLE hRearVCMesh;

	double vccSpeed, vccSteering;
	int meshidxCrawler;
	int meshidxTruck1;
	int meshidxTruck2;
	int meshidxTruck3;
	int meshidxTruck4;
	UINT fwdVCIdx, rearVCIdx;
	UINT anim_truck_trans[4];
	UINT anim_truck_rot[4];
	UINT anim_brake_discs;
	double brake_discs_state;
	UINT DrivetruckGrpList[NUMGRP_TRUCK-4]; // array used to define drivetruck animations
	MGROUP_ROTATE* InnerBrakeDiscs[4];
	MGROUP_ROTATE* OuterBrakeDiscs[4];


	std::vector<MGROUP_TRANSFORM*> vpAnimations;

	int SoundID;

	OBJHANDLE hEarth;
	std::vector<OBJHANDLE> vhLC39;
};

#endif //_CRAWLER_H
