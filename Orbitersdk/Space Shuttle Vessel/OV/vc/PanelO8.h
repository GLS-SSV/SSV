/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel O8 definition



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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel O8 definition



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
#ifndef VC_PANELO8
#define VC_PANELO8


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class StandardTalkback3;


	class PanelO8:public AtlantisPanel
	{
		private:
			StdSwitch2* pRadarAltimeter[2];
			StdSwitch3* pAnnunciatorLampTest;

			StdSwitch3* pOMSKitHePressVaporIsolA;
			StdSwitch3* pOMSKitHePressVaporIsolB;
			StdSwitch3* pOMSKitTankIsolationA;
			StdSwitch3* pOMSKitTankIsolationB;
			StdSwitch3* pLeftOMSHePressVaporIsolA;
			StdSwitch3* pLeftOMSHePressVaporIsolB;
			StdSwitch3* pLeftOMSTankIsolationA;
			StdSwitch3* pLeftOMSTankIsolationB;
			StdSwitch3* pRightOMSHePressVaporIsolA;
			StdSwitch3* pRightOMSHePressVaporIsolB;
			StdSwitch3* pRightOMSTankIsolationA;
			StdSwitch3* pRightOMSTankIsolationB;
			StdSwitch3* pLeftOMSCrossfeedA;
			StdSwitch3* pLeftOMSCrossfeedB;
			StdSwitch3* pRightOMSCrossfeedA;
			StdSwitch3* pRightOMSCrossfeedB;

			StdSwitch3* pFwdRCSHePressA;
			StdSwitch3* pFwdRCSHePressB;
			StdSwitch3* pFwdRCSTankIsolation12;
			StdSwitch3* pFwdRCSTankIsolation345;
			StdSwitch3* pFwdRCSManifoldIsolation1;
			StdSwitch3* pFwdRCSManifoldIsolation2;
			StdSwitch3* pFwdRCSManifoldIsolation3;
			StdSwitch3* pFwdRCSManifoldIsolation4;
			StdSwitch3* pFwdRCSManifoldIsolation5;

			StandardTalkback3* pOMSKitTankIsolationA_TB;
			StandardTalkback3* pOMSKitTankIsolationB_TB;
			StandardTalkback3* pLeftOMSTankIsolationA_TB;
			StandardTalkback3* pLeftOMSTankIsolationB_TB;
			StandardTalkback3* pRightOMSTankIsolationA_TB;
			StandardTalkback3* pRightOMSTankIsolationB_TB;
			StandardTalkback3* pLeftOMSCrossfeedA_TB;
			StandardTalkback3* pLeftOMSCrossfeedB_TB;
			StandardTalkback3* pRightOMSCrossfeedA_TB;
			StandardTalkback3* pRightOMSCrossfeedB_TB;
			StandardTalkback3* pFwdRCSHePressA_TB;
			StandardTalkback3* pFwdRCSHePressB_TB;
			StandardTalkback3* pFwdRCSTankIsolation12_TB;
			StandardTalkback3* pFwdRCSTankIsolation345_TB;
			StandardTalkback3* pFwdRCSManifoldIsolation1_TB;
			StandardTalkback3* pFwdRCSManifoldIsolation2_TB;
			StandardTalkback3* pFwdRCSManifoldIsolation3_TB;
			StandardTalkback3* pFwdRCSManifoldIsolation4_TB;
			StandardTalkback3* pFwdRCSManifoldIsolation5_TB;

		public:
			explicit PanelO8( Atlantis* psts );
			virtual ~PanelO8();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
};

#endif //VC_PANELO8