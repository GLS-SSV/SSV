/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel L12U definition



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

  Panel L12U definition



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
#ifndef __VC_PANELL12U_CENTAUR_H
#define __VC_PANELL12U_CENTAUR_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class StandardTalkback2;


	class PanelL12U_Centaur:public AtlantisPanel
	{
		private:
			StdSwitch2* pSUPER_ZIP_PRI_FIRE;
			StdSwitch2* pSUPER_ZIP_PRI_ARM;
			StdSwitch3* pDA_PRI_ROT;
			StdSwitch2* pLOGIC_PRI_PWR;
			StdSwitch2* pSSP_PRI_PWR;
			StdSwitch3* pMECH_PRI_PWR;

			StdSwitch2* pSUPER_ZIP_BKUP_FIRE;
			StdSwitch2* pSUPER_ZIP_BKUP_ARM;
			StdSwitch3* pDA_BKUP_ROT;
			StdSwitch2* pLOGIC_BKUP_PWR;
			StdSwitch2* pSSP_BKUP_PWR;
			StdSwitch3* pMECH_BKUP_PWR;

			StandardTalkback2* pMECH_PRI_PWR_TB;
			StandardTalkback2* pPosition_PRI_TB;
			StandardTalkback2* pSUPER_ZIP_PRI_ARM_TB;

			StandardTalkback2* pMECH_BKUP_PWR_TB;
			StandardTalkback2* pPosition_BKUP_TB;
			StandardTalkback2* pSUPER_ZIP_BKUP_ARM_TB;

		public:
			explicit PanelL12U_Centaur( Atlantis* _sts );
			virtual ~PanelL12U_Centaur();

			void RegisterVC() override;
			void DefineVC() override;
			void Realize() override;
	};
}

#endif // __VC_PANELL12U_CENTAUR_H
