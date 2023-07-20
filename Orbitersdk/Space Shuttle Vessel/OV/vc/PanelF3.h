/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel F3 definition



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

  Panel F3 definition



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
#ifndef __PANELF3_H
#define __PANELF3_H


#include "AtlantisPanel.h"


namespace vc
{
	class StandardSwitchCover;
	class PushButtonIndicatorDoubleLight;
	class StdSwitch2;
	class StandardSingleLight;


	class PanelF3:public AtlantisPanel
	{
		StandardSwitchCover* pDragChuteARMCover;
		StandardSwitchCover* pDragChuteDPYCover;
		StandardSwitchCover* pDragChuteJETTCover;

		PushButtonIndicatorDoubleLight* pDragChuteARM;
		PushButtonIndicatorDoubleLight* pDragChuteDPY;
		PushButtonIndicatorDoubleLight* pDragChuteJETT;

		StdSwitch2* pHUDPower[2];

		StandardSingleLight* pNWSFail;
		StandardSingleLight* pAntiSkidFail;

		StdSwitch2* pCDRTRIMRHCPNL;
		StdSwitch2* pCDRTRIMPANEL;
		StdSwitch2* pPLTTRIMRHCPNL;
		StdSwitch2* pPLTTRIMPANEL;

		bool HasDragChute;

	public:
		explicit PanelF3( Atlantis* _sts, bool HasDragChute );
		~PanelF3();

		void Realize() override;

		void DefineVC() override;
		void RegisterVC() override;
		void VisualCreated( void ) override;
	};
}

#endif //__PANELF3_H
