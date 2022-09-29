/****************************************************************************
  This file is part of Space Shuttle Vessel

  SLC-6 vessel definition


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
2020/05/07   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/14   GLS
2021/08/23   GLS
2021/12/25   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/09/29   GLS
********************************************/

#ifndef _SLC6_H_
#define _SLC6_H_
#pragma once


#include <Orbitersdk.h>
#include "../BaseSSVPad.h"
#include "../LCCPadInterface.h"
#include "../T0UmbilicalMLPInterface.h"
#include "../T0UmbilicalReference.h"
#include "../PadLCCInterface.h"


class SLC6 : public BaseSSVPad, public LCCPadInterface, public T0UmbilicalMLPInterface
{
	friend BOOL CALLBACK SLC6_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	MESHHANDLE hPadSurfaceMesh;
	MESHHANDLE hLaunchMountMesh;
	MESHHANDLE hTowerMesh;
	MESHHANDLE hPCRMesh;
	MESHHANDLE hMSTMesh;
	MESHHANDLE hSABMesh;
	MESHHANDLE hPPRMesh;
	UINT padsurface_mesh_idx;
	UINT launchmount_mesh_idx;
	UINT tower_mesh_idx;
	UINT pcr_mesh_idx;
	UINT mst_mesh_idx;
	UINT sab_mesh_idx;
	UINT ppr_mesh_idx;

	ATTACHMENTHANDLE ahHDP;

	AnimState PCR_State, SAB_State, MST_State;
	AnimState SABDoor_State;
	AnimState T0Umbilical_State;

	UINT anim_PCR, anim_SAB, anim_MST;
	UINT anim_SABDoor;
	UINT anim_T0Umb;

	int SoundID;

	bool HBOIOn;
	double HBOILevel;
	double HBOITime;

	char LCCName[256];

	T0UmbilicalReference* pSTS;
	PadLCCInterface* pLCC;

	void DefineAnimations();
	void DefineHBOIs( void );
	void DefineSSS( void );
	void DefineExhaustSteam( void );
	void CalculateSteamProduction( double simt, double simdt ) override;
	void DefineGOXVents( void );

	bool IsT0UmbilicalConnected( void ) const;

public:
	SLC6(OBJHANDLE hVessel, int flightmodel);
	~SLC6();

	void clbkSetClassCaps(FILEHANDLE cfg) override;
	void clbkPostCreation() override;
	void clbkPreStep(double simt, double simdt, double mjd) override;
	int clbkConsumeBufferedKey(DWORD key, bool down, char *keystate) override;
	void clbkSaveState( FILEHANDLE scn ) override;
	void clbkLoadStateEx( FILEHANDLE scn, void* status ) override;

	void ExtendOAA( int mode ) override;
	void RetractOAA() override;
	void ExtendGVA() override;

	virtual void ExtendPCR();
	virtual void HaltPCR();
	virtual void RetractPCR();

	virtual void ExtendSAB();
	virtual void HaltSAB();
	virtual void RetractSAB();
	virtual void OpenSABDoor();
	virtual void HaltSABDoor();
	virtual void CloseSABDoor();

	virtual void ExtendMST();
	virtual void HaltMST();
	virtual void RetractMST();

	// override to handle MST
	void DeployIAA() override;

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

	//// T0UmbilicalMLPInterface ////
	void FireHDPPICs( void ) override;
	void FireT0UmbilicalPICs( void ) override;
};

#endif// _SLC6_H_
