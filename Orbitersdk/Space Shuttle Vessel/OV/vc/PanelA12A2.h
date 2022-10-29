/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel 32V73A12A2 definition



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
2020/05/24   GLS
2020/06/20   GLS
2020/07/11   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel R11 definition



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
#ifndef _PANELA12A2_H
#define _PANELA12A2_H


#include "AtlantisPanel.h"


namespace vc
{
	class Keyboard;
	class StdSwitch2;
	class StdSwitch3;


	class PanelA12A2 : public AtlantisPanel
	{
		private:
			Keyboard* pKeyboardAft;

			StdSwitch2* pIDPCRTPower;
			StdSwitch3* pIDPCRTMajFunc;

		public:
			explicit PanelA12A2( Atlantis* _sts, bool defaultposition );
			virtual ~PanelA12A2();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
	};
}

#endif //_PANELA12A2_H
