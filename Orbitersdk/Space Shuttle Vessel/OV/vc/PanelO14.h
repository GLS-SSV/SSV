/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel O14 definition



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
2020/07/11   GLS
2021/06/01   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel O14 definition



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
#ifndef __VC_PANELO14_H
#define __VC_PANELO14_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class CircuitBreaker;


	class PanelO14:public AtlantisPanel
	{
			StdSwitch2* pBRAKES_MN_A;
			StdSwitch2* pRJDA_1A_LOGIC;
			StdSwitch2* pRJDA_1A_DRIVER;
			StdSwitch2* pRJDA_2A_LOGIC;
			StdSwitch2* pRJDA_2A_DRIVER;
			StdSwitch2* pRJDF_1B_LOGIC;
			StdSwitch2* pRJDF_1B_DRIVER;
			StdSwitch2* pL_OMS_ENG_VLV;

			CircuitBreaker* pMDM_OF_12_A;
			CircuitBreaker* pMDM_OF_34_A;

			CircuitBreaker* pSTAR_TRKR_Z;

			CircuitBreaker* pDDU_LEFT_MN_A;
			CircuitBreaker* pDDU_AFT_MN_A;
			CircuitBreaker* pNOSE_WHEEL_STEERING_MN_A;

		public:
			explicit PanelO14( Atlantis* _sts );
			virtual ~PanelO14();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
}

#endif// __VC_PANELO14_H
