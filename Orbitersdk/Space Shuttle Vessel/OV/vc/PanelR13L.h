/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel R13L7 definition



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
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel R13L definition



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
#ifndef VC_PANELR13L
#define VC_PANELR13L


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever2;
	class LockableLever3;
	class StandardTalkback3;


	class PanelR13L:public AtlantisPanel
	{
			StdSwitch2* pPLBayDoor[2];
			StdSwitch2* pPLBayMechPWR[2];

			StdSwitch3* pLatchControl[2];
			StdSwitch3* pRadiatorControl[2];
			StdSwitch3* pKUAntenna;
			StdSwitch3* pMMUGN2SPLYISOLVLV[2];

			LockableLever3* pPLBayDoorLL;
			LockableLever2* pKUAntennaDirectStow;

			StandardTalkback3* pPLBayDoorTB;
			StandardTalkback3* pLatch[2];
			StandardTalkback3* pRadiator[2];
			StandardTalkback3* pKUAntennaTB;
			StandardTalkback3* pMMUGN2SPLYISOLVLVTB[2];
		public:
			explicit PanelR13L( Atlantis* psts );
			virtual ~PanelR13L();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
};

#endif //VC_PANELR13L
