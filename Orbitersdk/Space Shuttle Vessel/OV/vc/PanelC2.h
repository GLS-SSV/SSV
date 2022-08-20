/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel C2 definition



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
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/04/27   GLS
2022/04/28   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel C2 definition



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
#ifndef VC_PANELC2
#define VC_PANELC2


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class Keyboard;
	class ThumbWheel;

	using namespace discsignals;


	class PanelC2:public AtlantisPanel
	{
			StdSwitch2* pIDPCRTPower[3];
			StdSwitch3* pIDPCRTMajFunc[3];
			StdSwitch2* pCRTSEL[2];

			StdSwitch3* pEventTimerMode;
			StdSwitch3* pEventTimerControl;
			StdSwitch3* pTimer;

			Keyboard* pKeyboardCDR;
			Keyboard* pKeyboardPLT;

			ThumbWheel* pEventTimerMin10;
			ThumbWheel* pEventTimerMin1;
			ThumbWheel* pEventTimerSec10;
			ThumbWheel* pEventTimerSec1;

		public:
			explicit PanelC2( Atlantis* _sts );
			virtual ~PanelC2();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
};

#endif //VC_PANELC2
