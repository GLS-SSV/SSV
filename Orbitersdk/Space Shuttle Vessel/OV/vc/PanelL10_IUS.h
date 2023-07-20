/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel L10 definition



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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel L10 definition



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
#ifndef __VC_PANELL10_IUS_H
#define __VC_PANELL10_IUS_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch3;
	class LockableLever2;
	class LockableLever3;
	class StandardTalkback2;


	class PanelL10_IUS:public AtlantisPanel
	{
		private:
			StdSwitch3* pPowerSourceASEBatteriesPri;
			StdSwitch3* pPowerSourceASEBatteriesAlt;
			StdSwitch3* pPowerSourceOrbiterSCConvPwrPri;
			StdSwitch3* pPowerSourceOrbiterSCConvPwrAlt;
			StdSwitch3* pPowerSourceIUSSCBatteryPri;
			StdSwitch3* pPowerSourceIUSSCBatteryAlt;
			StdSwitch3* pPowerSourceIUSBusABatteriesPri;
			StdSwitch3* pPowerSourceIUSBusABatteriesAlt;
			StdSwitch3* pPowerSourceIUSBusBBatteriesPri;
			StdSwitch3* pPowerSourceIUSBusBBatteriesAlt;
			StdSwitch3* pIUSConvPwrPri;
			StdSwitch3* pIUSConvPwrAlt;
			StdSwitch3* pSCSupportSCRegPwrPri;
			StdSwitch3* pSCSupportSCRegPwrAlt;
			StdSwitch3* pSCSupportSCPowerPri;
			StdSwitch3* pSCSupportSCPowerAlt;
			StdSwitch3* pIUSSupportAFeedPri;
			StdSwitch3* pIUSSupportAFeedAlt;
			StdSwitch3* pIUSSupportBFeedPri;
			StdSwitch3* pIUSSupportBFeedAlt;
			StdSwitch3* pTestPri;
			StdSwitch3* pTestAlt;
			StdSwitch3* pIUSSupportHeatersBatteryPri;
			StdSwitch3* pIUSSupportHeatersBatteryAlt;
			StdSwitch3* pIUSSupportHeatersCriticalPri;
			StdSwitch3* pIUSSupportHeatersCriticalAlt;
			StdSwitch3* pIUSSupportWBDIPri;
			StdSwitch3* pIUSSupportWBDIAlt;
			StdSwitch3* pIUSPowerPri;
			StdSwitch3* pIUSPowerAlt;
			StdSwitch3* pNormBusPwrPri;
			StdSwitch3* pNormBusPwrAlt;
			StdSwitch3* pIUSSupportAutoShutdownStandbyModePri;
			StdSwitch3* pIUSSupportAutoShutdownStandbyModeAlt;
			StdSwitch3* pTiltTableActuatorDriveEnablePri1;
			StdSwitch3* pTiltTableActuatorDriveEnableAlt2;
			StdSwitch3* pTiltTableActuatorMotionPri1;
			StdSwitch3* pTiltTableActuatorMotionAlt2;
			StdSwitch3* pPyroBusPri;
			StdSwitch3* pPyroBusAlt;
			StdSwitch3* pUmbilicalsEnaPri;
			StdSwitch3* pUmbilicalsEnaAlt;
			StdSwitch3* pIUSDeploymentEnaPri;
			StdSwitch3* pIUSDeploymentEnaAlt;

			LockableLever2* pPanelMode;
			LockableLever2* pTiltTableActuatorAltDrAct1;
			LockableLever2* pUmbilicalsRelPri;
			LockableLever2* pUmbilicalsRelAlt;
			LockableLever2* pIUSDeploymentDpyPri;
			LockableLever2* pIUSDeploymentDpyAlt;
			LockableLever2* pPowerKill;

			LockableLever3* pCmdPathEnabled;

			StandardTalkback2* pPowerSourceASEBatteriesPriTB;
			StandardTalkback2* pPowerSourceASEBatteriesAltTB;
			StandardTalkback2* pPowerSourceOrbiterSCConvPwrPriTB;
			StandardTalkback2* pPowerSourceOrbiterSCConvPwrAltTB;
			StandardTalkback2* pPowerSourceIUSSCBatteryPriTB;
			StandardTalkback2* pPowerSourceIUSSCBatteryAltTB;
			StandardTalkback2* pPowerSourceIUSBusABatteriesPriTB;
			StandardTalkback2* pPowerSourceIUSBusABatteriesAltTB;
			StandardTalkback2* pPowerSourceIUSBusBBatteriesPriTB;
			StandardTalkback2* pPowerSourceIUSBusBBatteriesAltTB;
			StandardTalkback2* pIUSConvPwrPriTB;
			StandardTalkback2* pIUSConvPwrAltTB;
			StandardTalkback2* pSCSupportSCRegPwrPriTB;
			StandardTalkback2* pSCSupportSCRegPwrAltTB;
			StandardTalkback2* pSCSupportSCPowerPriTB;
			StandardTalkback2* pSCSupportSCPowerAltTB;
			StandardTalkback2* pIUSSupportAFeedPriTB;
			StandardTalkback2* pIUSSupportAFeedAltTB;
			StandardTalkback2* pIUSSupportBFeedPriTB;
			StandardTalkback2* pIUSSupportBFeedAltTB;
			StandardTalkback2* pMatrixStatusPriTB;
			StandardTalkback2* pMatrixStatusAltTB;
			StandardTalkback2* pIUSSupportHeatersBatteryPriTB;
			StandardTalkback2* pIUSSupportHeatersBatteryAltTB;
			StandardTalkback2* pIUSSupportHeatersCriticalPriTB;
			StandardTalkback2* pIUSSupportHeatersCriticalAltTB;
			StandardTalkback2* pIUSSupportWBDIPriTB;
			StandardTalkback2* pIUSSupportWBDIAltTB;
			StandardTalkback2* pIUSPowerPriTB;
			StandardTalkback2* pIUSPowerAltTB;
			StandardTalkback2* pNormBusPwrPriTB;
			StandardTalkback2* pNormBusPwrAltTB;
			StandardTalkback2* pIUSSupportAutoShutdownStandbyModePriTB;
			StandardTalkback2* pIUSSupportAutoShutdownStandbyModeAltTB;
			StandardTalkback2* pTiltTableActuatorMotionPri1TB;
			StandardTalkback2* pTiltTableActuatorMotionAlt2TB;
			StandardTalkback2* pTiltTableActuatorPositionPri1TB;
			StandardTalkback2* pTiltTableActuatorPositionAlt2TB;
			StandardTalkback2* pTiltTableActuatorPriDrAct1EngagedTB;
			StandardTalkback2* pTiltTableActuatorAltDrAct2EngagedTB;
			StandardTalkback2* pPyroBusPriTB;
			StandardTalkback2* pPyroBusAltTB;
			StandardTalkback2* pUmbilicalsEnaPriTB;
			StandardTalkback2* pUmbilicalsEnaAltTB;
			StandardTalkback2* pUmbilicalsRelPriTB;
			StandardTalkback2* pUmbilicalsRelAltTB;
			StandardTalkback2* pIUSDeploymentEnaPriTB;
			StandardTalkback2* pIUSDeploymentEnaAltTB;

		public:
			explicit PanelL10_IUS( Atlantis* _sts );
			virtual ~PanelL10_IUS();

			void RegisterVC() override;
			void DefineVC() override;
			void Realize() override;
	};
}

#endif // __VC_PANELL10_IUS_H
