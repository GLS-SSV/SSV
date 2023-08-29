/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A6U definition



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
2020/06/28   GLS
2021/01/19   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/04/27   GLS
2022/04/28   GLS
2022/05/21   GLS
2022/08/05   GLS
2022/09/06   GLS
2022/09/29   GLS
2023/07/25   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel A6U definition



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
#ifndef _VC_PANELA6U_H_
#define _VC_PANELA6U_H_


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class LockableLever2;
	class StdSwitch2;
	class StdSwitch3;
	class RotaryDemuxSwitch;
	class PushButtonIndicatorSingleLight;
	class StandardTalkback2;
	class StandardTalkback3;
	class SelectorWheel;

	using namespace discsignals;


	class PanelA6U: public AtlantisPanel
	{
		public:
			explicit PanelA6U( Atlantis* _sts, const std::string &orbiter );
			virtual ~PanelA6U();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
			void VisualCreated( void ) override;

			void OnPreStep(double simt, double simdt, double mjd) override;

		private:
			typedef enum { PL1=0, PL2=1, PL3=2, MON=3 } PAYLOAD; // both monitor positions are the same, so we only need 1 MON enum

			PanelA6U::PAYLOAD GetSelectedPayload() const;

			LockableLever2* pFltCntlrPower;
			StdSwitch2* pSense;

			StdSwitch2* pPayloadRetentionLogicPowerSys[2];

			StdSwitch3* pPayloadRetentionLatches[5];

			RotaryDemuxSwitch* pPayloadSelect;

			//DAP PBIs
			PushButtonIndicatorSingleLight* pPBIs[24];

			StandardTalkback3* pLatchState[5];
			StandardTalkback2* pLatchRTL[5];

			StdSwitch3* pADIAttitude;
			StdSwitch3* pADIError;
			StdSwitch3* pADIRate;

			StdSwitch3* pAnnunciatorBusSelect;
			StdSwitch3* pAnnunciatorLampTest;

			StdSwitch3* pEventTimerMode;
			StdSwitch3* pEventTimerControl;
			StdSwitch3* pEventTimerTimer;

			// panel input
			DiscInPort PL_1_SEL_1A_LAT_TB;
			DiscInPort PL_1_SEL_2A_LAT_TB;
			DiscInPort PL_1_SEL_3A_LAT_TB;
			DiscInPort PL_1_SEL_4A_LAT_TB;
			DiscInPort PL_1_SEL_5A_LAT_TB;
			DiscInPort PL_2_SEL_1A_LAT_TB;
			DiscInPort PL_2_SEL_2A_LAT_TB;
			DiscInPort PL_2_SEL_3A_LAT_TB;
			DiscInPort PL_2_SEL_4A_LAT_TB;
			DiscInPort PL_2_SEL_5A_LAT_TB;
			DiscInPort PL_3_SEL_1A_LAT_TB;
			DiscInPort PL_3_SEL_2A_LAT_TB;
			DiscInPort PL_3_SEL_3A_LAT_TB;
			DiscInPort PL_3_SEL_4A_LAT_TB;
			DiscInPort PL_3_SEL_5A_LAT_TB;

			DiscInPort PL_1_SEL_1A_REL_TB;
			DiscInPort PL_1_SEL_2A_REL_TB;
			DiscInPort PL_1_SEL_3A_REL_TB;
			DiscInPort PL_1_SEL_4A_REL_TB;
			DiscInPort PL_1_SEL_5A_REL_TB;
			DiscInPort PL_2_SEL_1A_REL_TB;
			DiscInPort PL_2_SEL_2A_REL_TB;
			DiscInPort PL_2_SEL_3A_REL_TB;
			DiscInPort PL_2_SEL_4A_REL_TB;
			DiscInPort PL_2_SEL_5A_REL_TB;
			DiscInPort PL_3_SEL_1A_REL_TB;
			DiscInPort PL_3_SEL_2A_REL_TB;
			DiscInPort PL_3_SEL_3A_REL_TB;
			DiscInPort PL_3_SEL_4A_REL_TB;
			DiscInPort PL_3_SEL_5A_REL_TB;

			DiscInPort PL_1_RDY_1A_TB;
			DiscInPort PL_1_RDY_2A_TB;
			DiscInPort PL_1_RDY_3A_TB;
			DiscInPort PL_1_RDY_4A_TB;
			DiscInPort PL_1_RDY_5A_TB;
			DiscInPort PL_2_RDY_1A_TB;
			DiscInPort PL_2_RDY_2A_TB;
			DiscInPort PL_2_RDY_3A_TB;
			DiscInPort PL_2_RDY_4A_TB;
			DiscInPort PL_2_RDY_5A_TB;
			DiscInPort PL_3_RDY_1A_TB;
			DiscInPort PL_3_RDY_2A_TB;
			DiscInPort PL_3_RDY_3A_TB;
			DiscInPort PL_3_RDY_4A_TB;
			DiscInPort PL_3_RDY_5A_TB;

			// panel output
			DiscOutPort IND_1A_1;
			DiscOutPort IND_1A_2;
			DiscOutPort IND_1A_3;
			DiscOutPort IND_1A_4;
			DiscOutPort IND_1A_5;
			DiscOutPort IND_1B_1;
			DiscOutPort IND_1B_2;
			DiscOutPort IND_1B_3;
			DiscOutPort IND_1B_4;
			DiscOutPort IND_1B_5;
			DiscOutPort IND_2A_1;
			DiscOutPort IND_2A_2;
			DiscOutPort IND_2A_3;
			DiscOutPort IND_2A_4;
			DiscOutPort IND_2A_5;
			DiscOutPort IND_2B_1;
			DiscOutPort IND_2B_2;
			DiscOutPort IND_2B_3;
			DiscOutPort IND_2B_4;
			DiscOutPort IND_2B_5;
			DiscOutPort IND_3A_1;
			DiscOutPort IND_3A_2;
			DiscOutPort IND_3A_3;
			DiscOutPort IND_3A_4;
			DiscOutPort IND_3A_5;
			DiscOutPort IND_3B_1;
			DiscOutPort IND_3B_2;
			DiscOutPort IND_3B_3;
			DiscOutPort IND_3B_4;
			DiscOutPort IND_3B_5;

			DiscOutPort LOGIC_POWER_SYS_1A;
			DiscOutPort LOGIC_POWER_SYS_2A;
			DiscOutPort LOGIC_POWER_SYS_3A;
			DiscOutPort LOGIC_POWER_SYS_1B;
			DiscOutPort LOGIC_POWER_SYS_2B;
			DiscOutPort LOGIC_POWER_SYS_3B;

			DiscOutPort PLD_SEL_POS_1;
			DiscOutPort PLD_SEL_POS_2;
			DiscOutPort PLD_SEL_POS_3;
			DiscOutPort PLD_SEL_MONITOR;

			// panel internal
			DiscInPort PLRetLogicPwrSysSwitch[2];
			DiscInPort PayloadSelect[3];
			DiscOutPort Latch_LatchedTkbk[5], Latch_ReleasedTkbk[5], Latch_RTLTkbk[5];

			SelectorWheel* pEventTimerMin10;
			SelectorWheel* pEventTimerMin1;
			SelectorWheel* pEventTimerSec10;
			SelectorWheel* pEventTimerSec1;

			bool thumbwheels;// thumbwheels or pushwheels
	};
}

#endif// _VC_PANELA6U_H_
