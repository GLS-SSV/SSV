/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel O7 definition



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

  Panel O7 definition



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
#ifndef __VC_PANELO7_H
#define __VC_PANELO7_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch3;
	class LockableLever3;
	class StandardTalkback3;


	class PanelO7:public AtlantisPanel
	{
		private:
			StdSwitch3* pAftLeftRCSHePressA;
			StdSwitch3* pAftLeftRCSHePressB;
			StdSwitch3* pAftLeftRCSTankIsolation12;
			StdSwitch3* pAftLeftRCSTankIsolation345A;
			StdSwitch3* pAftLeftRCSTankIsolation345B;
			StdSwitch3* pAftLeftRCSManifoldIsolation1;
			StdSwitch3* pAftLeftRCSManifoldIsolation2;
			StdSwitch3* pAftLeftRCSManifoldIsolation3;
			StdSwitch3* pAftLeftRCSManifoldIsolation4;
			StdSwitch3* pAftLeftRCSManifoldIsolation5;
			StdSwitch3* pAftRightRCSHePressA;
			StdSwitch3* pAftRightRCSHePressB;
			StdSwitch3* pAftRightRCSTankIsolation12;
			StdSwitch3* pAftRightRCSTankIsolation345A;
			StdSwitch3* pAftRightRCSTankIsolation345B;
			StdSwitch3* pAftRightRCSManifoldIsolation1;
			StdSwitch3* pAftRightRCSManifoldIsolation2;
			StdSwitch3* pAftRightRCSManifoldIsolation3;
			StdSwitch3* pAftRightRCSManifoldIsolation4;
			StdSwitch3* pAftRightRCSManifoldIsolation5;

			StdSwitch3* pLeftRCSCrossfeed12;
			StdSwitch3* pLeftRCSCrossfeed345;
			StdSwitch3* pRightRCSCrossfeed12;
			StdSwitch3* pRightRCSCrossfeed345;
			LockableLever3* MasterRCSCrossfeed;

			StandardTalkback3* pAftLeftRCSHePressA_TB;
			StandardTalkback3* pAftLeftRCSHePressB_TB;
			StandardTalkback3* pAftLeftRCSTankIsolation12_TB;
			StandardTalkback3* pAftLeftRCSTankIsolation345A_TB;
			StandardTalkback3* pAftLeftRCSTankIsolation345B_TB;
			StandardTalkback3* pAftLeftRCSManifoldIsolation1_TB;
			StandardTalkback3* pAftLeftRCSManifoldIsolation2_TB;
			StandardTalkback3* pAftLeftRCSManifoldIsolation3_TB;
			StandardTalkback3* pAftLeftRCSManifoldIsolation4_TB;
			StandardTalkback3* pAftLeftRCSManifoldIsolation5_TB;
			StandardTalkback3* pAftRightRCSHePressA_TB;
			StandardTalkback3* pAftRightRCSHePressB_TB;
			StandardTalkback3* pAftRightRCSTankIsolation12_TB;
			StandardTalkback3* pAftRightRCSTankIsolation345A_TB;
			StandardTalkback3* pAftRightRCSTankIsolation345B_TB;
			StandardTalkback3* pAftRightRCSManifoldIsolation1_TB;
			StandardTalkback3* pAftRightRCSManifoldIsolation2_TB;
			StandardTalkback3* pAftRightRCSManifoldIsolation3_TB;
			StandardTalkback3* pAftRightRCSManifoldIsolation4_TB;
			StandardTalkback3* pAftRightRCSManifoldIsolation5_TB;

			StandardTalkback3* pLeftRCSCrossfeed12_TB;
			StandardTalkback3* pLeftRCSCrossfeed345_TB;
			StandardTalkback3* pRightRCSCrossfeed12_TB;
			StandardTalkback3* pRightRCSCrossfeed345_TB;

		public:
			explicit PanelO7( Atlantis* _sts );
			virtual ~PanelO7();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
}

#endif// __VC_PANELO7_H
