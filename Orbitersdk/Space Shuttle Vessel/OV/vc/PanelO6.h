/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel O6 definition



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
2020/03/20   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/01   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel O6 definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#pragma once

#include "AtlantisPanel.h"
#include <discsignals.h>


using namespace discsignals;


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class StandardTalkback2;
	class StandardTalkback3;
	class StandardSwitchCover;
	class PushButton;
	class LockableLever3;


	class PanelO6 : public AtlantisPanel {
	private:
		//StdSwitch3* pLGlareShieldFlood;
		StandardTalkback3* pStarTrackerDoorPositionY;
		StandardTalkback3* pStarTrackerDoorPositionZ;
		StandardSwitchCover* pStarTrackerDoorControlSys1Cover;
		StandardSwitchCover* pStarTrackerDoorControlSys2Cover;
		StdSwitch3* pStarTrackerDoorControlSys1;
		StdSwitch3* pStarTrackerDoorControlSys2;
		StdSwitch2* pStarTrackerPowerY;
		StdSwitch2* pStarTrackerPowerZ;
		//StdSwitch3* pLeftSeatCenterFlood;
		//StdSwitch2* pUHFXmitFreq;
		//StdSwitch2* pUHFSPLXPowerAmp;
		//StdSwitch2* pUHFSquelch;

		StdSwitch3* pAnnunciatorLampTest;
		StdSwitch3* pAnnunciatorBusSelectACA1;
		StdSwitch3* pAnnunciatorBusSelectACA23;

		//StdSwitch2* pAnnunciatorIntensitySel;
		//StdSwitch3* pMTU;
		//StdSwitch2* pIDP1;
		//StdSwitch2* pIDP2;
		//StdSwitch2* pIDP3;
		//StdSwitch2* pIDP4;
		StdSwitch2* pMDMPL1;
		StdSwitch2* pMDMPL2;
		StdSwitch2* pMDMPL3;
		StdSwitch2* pMDMFA1;
		StdSwitch2* pMDMFA2;
		StdSwitch2* pMDMFA3;
		StdSwitch2* pMDMFA4;
		StdSwitch2* pMDMFF1;
		StdSwitch2* pMDMFF2;
		StdSwitch2* pMDMFF3;
		StdSwitch2* pMDMFF4;

		StandardSwitchCover* pGPCPowerCover[5];

		StdSwitch2* pGPC1Pwr;
		StdSwitch2* pGPC2Pwr;
		StdSwitch2* pGPC3Pwr;
		StdSwitch2* pGPC4Pwr;
		StdSwitch2* pGPC5Pwr;

		StandardTalkback2* pGPCOutput[5];

		StandardSwitchCover* pGPCOutputCover[5];

		StdSwitch3* pGPC1Output;
		StdSwitch3* pGPC2Output;
		StdSwitch3* pGPC3Output;
		StdSwitch3* pGPC4Output;
		StdSwitch3* pGPC5Output;

		StdSwitch3* pIPLSource;
		PushButton* pIPL1;
		PushButton* pIPL2;
		PushButton* pIPL3;
		PushButton* pIPL4;
		PushButton* pIPL5;

		StandardTalkback3* pGPCMode[5];

		LockableLever3* pGPC1Mode;
		LockableLever3* pGPC2Mode;
		LockableLever3* pGPC3Mode;
		LockableLever3* pGPC4Mode;
		LockableLever3* pGPC5Mode;

		// panel internal
		DiscInPort dipSTPowerZ;
		DiscInPort dipSTPowerY;
		DiscInPort dipCBSTPowerZ;
		DiscInPort dipCBSTPowerY;
		DiscOutPort dopSTPowerZ;
		DiscOutPort dopSTPowerY;

		DiscInPort STAR_TRACKER_Y_DOOR_CLS_1;
		DiscInPort STAR_TRACKER_Y_DOOR_CLS_2;
		DiscInPort STAR_TRACKER_Y_DOOR_OP_1;
		DiscInPort STAR_TRACKER_Y_DOOR_OP_2;
		DiscInPort STAR_TRACKER_Z_DOOR_CLS_1;
		DiscInPort STAR_TRACKER_Z_DOOR_CLS_2;
		DiscInPort STAR_TRACKER_Z_DOOR_OP_1;
		DiscInPort STAR_TRACKER_Z_DOOR_OP_2;
		DiscOutPort dopSTDoorY_OP;
		DiscOutPort dopSTDoorY_CL;
		DiscOutPort dopSTDoorZ_OP;
		DiscOutPort dopSTDoorZ_CL;

	public:
		explicit PanelO6(Atlantis* _sts);
		virtual ~PanelO6();

		void OnPreStep( double simt, double simdt, double mjd ) override;

		void DefineVC() override;
		void RegisterVC() override;
		void Realize() override;

	};
};