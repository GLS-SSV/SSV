/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mobile Launcher Platform vessel definition


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
2020/06/20   GLS
2021/06/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/

#ifndef _SSVMLP_H_
#define _SSVMLP_H_


#include <Orbitersdk.h>
#include "../PadMLPInterface.h"
#include "../T0UmbilicalMLPInterface.h"
#include "../T0UmbilicalReference.h"
#include "../MLPPadInterface.h"


class MLP: public VESSEL4, public PadMLPInterface, public T0UmbilicalMLPInterface
{

public:
	MLP(OBJHANDLE hVessel, int iFlightModel);
	virtual ~MLP();

	void clbkSetClassCaps(FILEHANDLE cfg) override;
	void clbkPostCreation( void ) override;
	void clbkLoadStateEx(FILEHANDLE scn, void* status) override;
	void clbkSaveState(FILEHANDLE scn) override;
	void clbkPreStep(double simt, double simdt, double mjd) override;
	void clbkVisualCreated( VISHANDLE vis, int refcount ) override;
	void clbkVisualDestroyed( VISHANDLE vis, int refcount ) override;

	//// PadMLPInterface ////
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

private:
	T0UmbilicalReference* pSTS;
	MLPPadInterface* pPad;

	MESHHANDLE mshMLP;

	ATTACHMENTHANDLE ahHDP;

	bool HBOIOn;
	double HBOILevel;
	double HBOITime;

	double SRBwaterbagsteam_lvl;

	UINT msh_idx;
	VISHANDLE vis;

	UINT anim_t0umb;			//T0 umbilical animation
	AnimState T0Umbilical_State;

	MGROUP_ROTATE* LeftT0Umb;
	MGROUP_ROTATE* RightT0Umb;
	MGROUP_ROTATE* LeftT0UmbCover;
	MGROUP_ROTATE* RightT0UmbCover;

	ATTACHMENTHANDLE ahBase; // used to attach to crawler/LC39/VAB

	std::string strMission;

	void DefineAnimations();
	void DefineHBOIs( void );
	void DefineSRBWaterBagSteam( void );
	void HideSRBWaterBags( VISHANDLE vis );

	bool IsT0UmbilicalConnected( void ) const;
};

#endif// _SSVMLP_H_
