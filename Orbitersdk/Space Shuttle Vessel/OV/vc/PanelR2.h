/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel R2 definition



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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/11   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel R2 VC Component



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
#ifndef __VC_PANEL_R2_H_12F72432_EB9D_4b53_BC9D_4BCD6DD61C17
#define __VC_PANEL_R2_H_12F72432_EB9D_4b53_BC9D_4BCD6DD61C17
#pragma once

#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever2;
	class LockableLever3;
	class StandardTalkback2;
	class StandardTalkback3;

	using namespace discsignals;


	class PanelR2 : public AtlantisPanel
	{
		StdSwitch3* pBlrCntlrHtr[3];
		StdSwitch2* pBlrPower[3];
		StdSwitch2* pBlrN2Supply[3];

		LockableLever3* pAPUOperate[3];
		LockableLever2* pHydPumpPress[3];
		LockableLever2* pAPUCntlrPwr[3];
		LockableLever2* pAPUFuelTkVlv[3];
		//StdSwitch2* pAPUSpeedSelect[3];

		LockableLever2* pETUmbDoorMode;
		StdSwitch2* pETUmbDoorCenterlineLatch;
		StdSwitch3* pETUmbDoorLeft;
		StdSwitch3* pETUmbDoorLeftLatch;
		StdSwitch3* pETUmbDoorRight;
		StdSwitch3* pETUmbDoorRightLatch;

		StdSwitch2* pMPSPower[2][3];
		StdSwitch3* pMPSHeIsolA[3];
		StdSwitch3* pMPSHeIsolB[3];

		StdSwitch3* pMPSPRPLTDumpSequence;
		StdSwitch3* pMPSPRPLTBackupLH2vlv;

		StdSwitch3* pPneuLEngHeXOVR;
		StdSwitch3* pPneuHeIsol;

		StdSwitch3* pHeInterconnect[3];

		LockableLever2* pLH2UllagePress;

		StandardTalkback2* pAPUReadyToStart[3];

		StandardTalkback3* pETUmbDoorCLLatch;
		StandardTalkback3* pETUmbLDoor;
		StandardTalkback3* pETUmbLLatch;
		StandardTalkback3* pETUmbRDoor;
		StandardTalkback3* pETUmbRLatch;

		DiscInPort APU_HydraulicPress[3];

		DiscInPort dipETUmbDoorMode_GPC;
		DiscInPort dipETUmbDoorCenterlineLatch_STOW;
		DiscInPort dipETUmbDoorLeft_CL;
		DiscInPort dipETUmbDoorLeft_OP;
		DiscInPort dipETUmbDoorLeftLatch_LAT;
		DiscInPort dipETUmbDoorLeftLatch_REL;
		DiscInPort dipETUmbDoorRight_CL;
		DiscInPort dipETUmbDoorRight_OP;
		DiscInPort dipETUmbDoorRightLatch_LAT;
		DiscInPort dipETUmbDoorRightLatch_REL;

		DiscOutPort dopETUmbDoorCenterlineLatch_STOW;
		DiscOutPort dopETUmbDoorLeft_CL;
		DiscOutPort dopETUmbDoorLeft_OP;
		DiscOutPort dopETUmbDoorLeftLatch_LAT;
		DiscOutPort dopETUmbDoorLeftLatch_REL;
		DiscOutPort dopETUmbDoorRight_CL;
		DiscOutPort dopETUmbDoorRight_OP;
		DiscOutPort dopETUmbDoorRightLatch_LAT;
		DiscOutPort dopETUmbDoorRightLatch_REL;

		DiscInPort CL_LATCH_1_STOW_1;
		DiscInPort CL_LATCH_1_STOW_2;
		DiscInPort CL_LATCH_2_STOW_1;
		DiscInPort CL_LATCH_2_STOW_2;

		DiscInPort LEFT_DOOR_OPEN_1;
		DiscInPort LEFT_DOOR_OPEN_2;
		DiscInPort LEFT_DOOR_RDY_TO_LCH_1;
		DiscInPort LEFT_DOOR_RDY_TO_LCH_2;
		DiscInPort LEFT_DOOR_RDY_TO_LCH_3;
		DiscInPort LEFT_DOOR_LATCH_REL_1;
		DiscInPort LEFT_DOOR_LATCH_REL_2;
		DiscInPort LEFT_DOOR_LATCH_LAT_1;
		DiscInPort LEFT_DOOR_LATCH_LAT_2;

		DiscInPort RIGHT_DOOR_OPEN_1;
		DiscInPort RIGHT_DOOR_OPEN_2;
		DiscInPort RIGHT_DOOR_RDY_TO_LCH_1;
		DiscInPort RIGHT_DOOR_RDY_TO_LCH_2;
		DiscInPort RIGHT_DOOR_RDY_TO_LCH_3;
		DiscInPort RIGHT_DOOR_LATCH_REL_1;
		DiscInPort RIGHT_DOOR_LATCH_REL_2;
		DiscInPort RIGHT_DOOR_LATCH_LAT_1;
		DiscInPort RIGHT_DOOR_LATCH_LAT_2;

		DiscOutPort dopETUmbDoorCLLatch_STOW;
		DiscOutPort dopETUmbLDoor_CL;
		DiscOutPort dopETUmbLDoor_OP;
		DiscOutPort dopETUmbLLatch_LAT;
		DiscOutPort dopETUmbLLatch_REL;
		DiscOutPort dopETUmbRDoor_CL;
		DiscOutPort dopETUmbRDoor_OP;
		DiscOutPort dopETUmbRLatch_LAT;
		DiscOutPort dopETUmbRLatch_REL;

	public:
		explicit PanelR2(Atlantis* psts);
		virtual ~PanelR2();

		void OnPreStep( double simt, double simdt, double mjd ) override;

		void RegisterVC() override;
		void DefineVC() override;
		void Realize() override;
	};
};

#endif //__VC_PANEL_R2_H_12F72432_EB9D_4b53_BC9D_4BCD6DD61C17