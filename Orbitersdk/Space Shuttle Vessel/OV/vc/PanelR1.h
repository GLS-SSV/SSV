/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel R1 definition



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
2021/06/03   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel R1 definition



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
#ifndef __VC_PANELR1_H
#define __VC_PANELR1_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever3;
	class StandardSwitchCover;
	class StandardTalkback2;
	class CircuitBreaker;


	class PanelR1 : public AtlantisPanel
	{
		private:
			StdSwitch2* pControlBusPwrMNA;
			StdSwitch2* pControlBusPwrMNB;
			StdSwitch2* pControlBusPwrMNC;

			StdSwitch2* pEssBusSourceMNBC;
			StdSwitch2* pEssBusSourceMNCA;
			StdSwitch2* pEssBusSourceMNAB;

			StdSwitch2* pEssBusSourceFC1;
			StdSwitch2* pEssBusSourceFC2;
			StdSwitch2* pEssBusSourceFC3;

			LockableLever3* pFCMainBusA;
			LockableLever3* pFCMainBusB;
			LockableLever3* pFCMainBusC;

			StdSwitch3* pMNBusTieA;
			StdSwitch3* pMNBusTieB;
			StdSwitch3* pMNBusTieC;

			StdSwitch3* pInvPwr1;
			StdSwitch3* pInvPwr2;
			StdSwitch3* pInvPwr3;

			StdSwitch3* pInvACBus1;
			StdSwitch3* pInvACBus2;
			StdSwitch3* pInvACBus3;

			CircuitBreaker* pAC_CONTR_AC1_A;
			CircuitBreaker* pAC_CONTR_AC1_B;
			CircuitBreaker* pAC_CONTR_AC1_C;
			CircuitBreaker* pAC_CONTR_AC2_A;
			CircuitBreaker* pAC_CONTR_AC2_B;
			CircuitBreaker* pAC_CONTR_AC2_C;
			CircuitBreaker* pAC_CONTR_AC3_A;
			CircuitBreaker* pAC_CONTR_AC3_B;
			CircuitBreaker* pAC_CONTR_AC3_C;

			StdSwitch3* pACBusSnsr1;
			StdSwitch3* pACBusSnsr2;
			StdSwitch3* pACBusSnsr3;

			StdSwitch3* pPayloadCabin;
			StdSwitch3* pPayloadPriMNB;
			StdSwitch3* pPayloadPriFC3;
			StdSwitch3* pPayloadPriMNC;
			StandardSwitchCover* pPayloadAuxCover;
			StdSwitch2* pPayloadAux;
			StdSwitch2* pPayloadAftMNB;
			StdSwitch2* pPayloadAftMNC;

			StdSwitch3* pFuelCell1Reac;
			StdSwitch3* pFuelCell2Reac;
			StdSwitch3* pFuelCell3Reac;
			StdSwitch3* pO2ManifoldVlvTank1;
			StdSwitch3* pO2ManifoldVlvTank2;
			StdSwitch3* pH2ManifoldVlvTank1;
			StdSwitch3* pH2ManifoldVlvTank2;

			StdSwitch3* pO2TK1HeatersA;
			StdSwitch3* pO2TK1HeatersB;
			StdSwitch3* pO2TK1Heaters;
			StdSwitch3* pO2TK2HeatersA;
			StdSwitch3* pO2TK2HeatersB;
			StdSwitch3* pO2TK2Heaters;
			StdSwitch3* pO2TK3HeatersA;
			StdSwitch3* pO2TK3HeatersB;
			StdSwitch3* pO2TK3Heaters;

			StdSwitch3* pH2TK1HeatersA;
			StdSwitch3* pH2TK1HeatersB;
			StdSwitch3* pH2TK2HeatersA;
			StdSwitch3* pH2TK2HeatersB;
			StdSwitch3* pH2TK3HeatersA;
			StdSwitch3* pH2TK3HeatersB;

			LockableLever3* pFuelCell1;
			LockableLever3* pFuelCell2;
			LockableLever3* pFuelCell3;

			StandardTalkback2* pFCMainBusATB;
			StandardTalkback2* pFCMainBusBTB;
			StandardTalkback2* pFCMainBusCTB;

			StandardTalkback2* pMNBusTieATB;
			StandardTalkback2* pMNBusTieBTB;
			StandardTalkback2* pMNBusTieCTB;

			StandardTalkback2* pInvPwr1TB;
			StandardTalkback2* pInvPwr2TB;
			StandardTalkback2* pInvPwr3TB;

			StandardTalkback2* pInvACBus1TB;
			StandardTalkback2* pInvACBus2TB;
			StandardTalkback2* pInvACBus3TB;

			StandardTalkback2* pPayloadPriMNBTB;
			StandardTalkback2* pPayloadPriFC3TB;
			StandardTalkback2* pPayloadPriMNCTB;

			StandardTalkback2* pFuelCell1ReacO2;
			StandardTalkback2* pFuelCell2ReacO2;
			StandardTalkback2* pFuelCell3ReacO2;
			StandardTalkback2* pFuelCell1ReacH2;
			StandardTalkback2* pFuelCell2ReacH2;
			StandardTalkback2* pFuelCell3ReacH2;

			StandardTalkback2* pO2ManifoldVlvTank1TB;
			StandardTalkback2* pO2ManifoldVlvTank2TB;
			StandardTalkback2* pH2ManifoldVlvTank1TB;
			StandardTalkback2* pH2ManifoldVlvTank2TB;

			StandardTalkback2* pFuelCellReadyForLoad1;
			StandardTalkback2* pFuelCellReadyForLoad2;
			StandardTalkback2* pFuelCellReadyForLoad3;

			StandardTalkback2* pFuelCellCoolantPumpdP1;
			StandardTalkback2* pFuelCellCoolantPumpdP2;
			StandardTalkback2* pFuelCellCoolantPumpdP3;

		public:
			explicit PanelR1( Atlantis* _sts );
			virtual ~PanelR1();

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELR1_H