/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel 36V73A8A2 definition



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
2020/09/02   GLS
2020/09/03   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/05/15   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel A8 definition



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

#ifndef __VC_PANELA8A2_H
#define __VC_PANELA8A2_H


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class StdSwitch3;
	class StandardSwitchCover;
	class StandardTalkback2;
	class StandardTalkback3;

	using namespace discsignals;


	class PanelA8A2 : public AtlantisPanel
	{
			StdSwitch3* pPortMRL;
			StdSwitch3* pStbdMRL;
			StdSwitch3* pPortRMS;
			StdSwitch3* pStbdRMS;
			StdSwitch3* pRMSSelect;

			StandardSwitchCover* pPortRMSCover;
			StandardSwitchCover* pStbdRMSCover;

			StandardTalkback3* pPortMRLTb;
			StandardTalkback3* pStbdMRLTb;
			StandardTalkback3* pPortRMSTb;
			StandardTalkback3* pStbdRMSTb;

			StandardTalkback2* pPortMRL_RTL[3];
			StandardTalkback2* pStbdMRL_RTL[3];

			DiscInPort PORT_MPM_SYSTEM_1_STOW;
			DiscInPort PORT_MPM_SYSTEM_1_DEPLOY;
			DiscInPort PORT_MPM_SYSTEM_2_STOW;
			DiscInPort PORT_MPM_SYSTEM_2_DEPLOY;
			DiscInPort STBD_MPM_SYSTEM_1_STOW;
			DiscInPort STBD_MPM_SYSTEM_1_DEPLOY;
			DiscInPort STBD_MPM_SYSTEM_2_STOW;
			DiscInPort STBD_MPM_SYSTEM_2_DEPLOY;
			DiscOutPort PORT_MPM_STOW;
			DiscOutPort PORT_MPM_DEPLOY;
			DiscOutPort STBD_MPM_STOW;
			DiscOutPort STBD_MPM_DEPLOY;

		public:
			explicit PanelA8A2( Atlantis* _sts );
			virtual ~PanelA8A2();

			void RegisterVC() override;
			void DefineVC() override;
			void Realize() override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __VC_PANELA8A2_H
