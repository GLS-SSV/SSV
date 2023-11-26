/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel F8 definition



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
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
2023/05/12   GLS
2023/06/03   GLS
2023/11/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel F8 definition



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
#ifndef _VC_PANELF8_H_
#define _VC_PANELF8_H_


#include "AtlantisPanel.h"


namespace vc
{
	class MDU;
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever2;
	class StandardTalkback3;
	class StandardSwitchCover;
	class PushButton;
	class PushButtonIndicatorSingleLight;
	class RotarySwitchPotentiometer;


	class PanelF8: public AtlantisPanel
	{
			MDU* pPLT1;
			MDU* pPLT2;
			StdSwitch3* pHSISelectMode;
			StdSwitch3* pHSISelectSource;
			StdSwitch3* pHSISelectChannel;
			LockableLever2* pFltCntlrPower;
			StdSwitch3* pADIAttitude;
			StdSwitch3* pADIError;
			StdSwitch3* pADIRate;
			StdSwitch3* pAirData;

			PushButton* pAttRef;

			StandardTalkback3* pLandingGearTB[3];

			StandardSwitchCover* pLandingGearArmDeployCover[2];
			PushButtonIndicatorSingleLight *pLandingGearArmDeploy[2];

			StdSwitch3* pHUDMode;
			RotarySwitchPotentiometer* pHUDBrightness;
			StdSwitch3* pHUDBright;

			StdSwitch2* pRDRALTM;

		public:
			PanelF8( Atlantis* _sts, BusManager* pBusManager );
			virtual ~PanelF8();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
}

#endif// _VC_PANELF8_H_
