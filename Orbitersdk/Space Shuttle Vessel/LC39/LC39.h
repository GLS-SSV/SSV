/****************************************************************************
  This file is part of Space Shuttle Vessel

  LC-39 vessel definition


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
2020/05/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/

#ifndef __LC39_H
#define __LC39_H
#pragma once

#include <Orbitersdk.h>
#include "../BaseSSVPad.h"
#include "../LCCPadInterface.h"
#include "../MLPPadInterface.h"
#include "../PadMLPInterface.h"
#include "../PadLCCInterface.h"


struct cJSON;

class LC39 : public BaseSSVPad, public LCCPadInterface, public MLPPadInterface
{
	friend BOOL CALLBACK LC39_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	LC39(OBJHANDLE hVessel, int flightmodel);
	~LC39();

	void clbkPostCreation() override;
	void clbkVisualCreated( VISHANDLE vis, int refcount ) override;
	void clbkPreStep(double simt, double simdt, double mjd) override;
	void clbkSetClassCaps(FILEHANDLE cfg) override;
	int clbkConsumeBufferedKey(DWORD key, bool down, char *keystate) override;
	void clbkSaveState( FILEHANDLE scn ) override;
	void clbkLoadStateEx( FILEHANDLE scn, void* status ) override;

	void RetractOAA() override;

	void MoveRSS_OWP(AnimState::Action action);
	void MoveFSS_OWP(AnimState::Action action);
	void MoveRSS(AnimState::Action action);
	void MoveRBUS(AnimState::Action action);
	void MoveEastSRBSFD( AnimState::Action action );
	void MoveWestSRBSFD( AnimState::Action action );

	//// LCCPadInterface ////
	void RetractOrbiterAccessArm( void ) override;
	void ExtendOrbiterAccessArm( bool EmergencyRate ) override;
	void RetractGOXVentArm( void ) override;
	void ExtendGOXVentArm( void ) override;
	void ActivatePreLOSSWS( void ) override;
	void DeactivatePreLOSSWS( void ) override;
	void ActivatePostLOSSWS( void ) override;
	void DeactivatePostLOSSWS( void ) override;
	void ActivateFirex( unsigned int sys ) override;
	void DeactivateFirex( unsigned int sys ) override;
	bool GetFirexState( unsigned int sys ) override;

	void FireSSMEH2BurnPICs( void ) override;

	void SetGMTLO( double GMTLO ) override;
	void SetGMTLOSetCommandFlag( bool val ) override;
	void SetLPSCountdownHoldFlag( bool val ) override;
	void SetLPSGoForAutoSequenceStartFlag( bool val ) override;
	void SetLPSGoForEngineStartFlag( bool val ) override;
	void SetResumeCountCommandFlag( bool val ) override;
	bool GetRSCountdownHoldFlag( void ) override;
	bool GetLaunchSequenceAbortFlag( void ) override;
	void PSN4( void ) override;
	double GetHydSysPress( int sys ) override;
	int GetHeTankPress( int sys ) override;
	int GetHeRegPress( int sys ) override;
	void HeFillTank( int sys, double mass ) override;
	void SetSSMEActPos( int num, double Ppos, double Ypos ) override;
	unsigned int GetHoldFlags( void ) override;

	//// MLPPadInterface ////
	void FireETVASPICs( void ) override;

private:
	void DefineAnimations();
	void DefineRBUSanimations( void );
	void DefineOWPanimations( void );
	void DefineSSS( void );
	void DefineExhaustSteam( void );
	void AnimateFSSOWPStrut();
	void CreateGOXVents( void );

	void HideRBUSPorch( DEVMESHHANDLE hmesh );
	void HideRBUS( DEVMESHHANDLE hmesh );
	void HideOWP( DEVMESHHANDLE hmeshFSS, DEVMESHHANDLE hmeshRSS );
	void HideNewLightingMast( DEVMESHHANDLE hmesh );
	void HideCraneTruss( DEVMESHHANDLE hmesh );
	void HideCraneWeightLightingMast( DEVMESHHANDLE hmesh );
	void HideGVAAccessPlatform( DEVMESHHANDLE hmesh );

	void LoadMissionFile( void );
	void LoadMissionV1( cJSON* root );

	void SetConfiguration( void );

	void CalculateSteamProduction( double simt, double simdt ) override;

	enum PADTYPE
	{
		_1981,// TODO STS-1 version
		_1982,// new GVA GOX pipes
		_1983,// RBUS porch
		_1985,// RBUS arm
		_1986,// OWP + RBUS
		_1988,// OWP
		_1995,// no crane
		_2007// no counter weight
	} padtype;

	std::string strMission;

	MESHHANDLE FSSMesh, RSSMesh, HardStandMesh, WaterTowerMesh;
	UINT fss_mesh_idx, rss_mesh_idx, hs_mesh_idx, wt_mesh_idx;

	UINT anim_rss_y_owp;
	UINT anim_fss_y_owp, anim_fss_y_owp_strut;
	UINT anim_rss;
	UINT anim_rbus;
	UINT anim_East_SRB_SFD;
	UINT anim_West_SRB_SFD;

	AnimState RSS_OWP_State, FSS_OWP_State;
	AnimState RSS_State;
	AnimState RBUS_State;
	AnimState East_SRB_SFD_State;
	AnimState West_SRB_SFD_State;

	int SoundID;

	ATTACHMENTHANDLE ahMLP;

	char LCCName[256];

	PadMLPInterface* pMLP;
	PadLCCInterface* pLCC;

	VECTOR3 MLPCoord2Pad( VECTOR3 v ) const;
	VECTOR3 MLPDir2Pad( VECTOR3 v ) const;
};

#endif //__LC39_H
