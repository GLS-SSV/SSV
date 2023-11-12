/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel L2 definition



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
2021/12/30   GLS
2023/11/11   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel L2 definition



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
#ifndef __VC_PANELL2_H
#define __VC_PANELL2_H


#include "AtlantisPanel.h"


namespace vc
{
	class LockableLever3;
	class StdSwitch2;
	class StdSwitch3;


	class PanelL2:public AtlantisPanel
	{
		private:
			LockableLever3* pBodyFlap;
			LockableLever3* pEntryMode;
			StdSwitch3* pPitchTrim;
			StdSwitch3* pRollTrim;
			StdSwitch3* pYawTrim;
			StdSwitch3* pNoseWheelSteering;
			StdSwitch2* pAntiSkid;


			DiscInPort dipTrimPanelOn;
			DiscInPort dipUpPitchTrim;
			DiscInPort dipDownPitchTrim;
			DiscInPort dipRightRollTrim;
			DiscInPort dipLeftRollTrim;
			DiscInPort dipRightYawTrim;
			DiscInPort dipLeftYawTrim;
			DiscOutPort dopUpPitchTrim_A;
			DiscOutPort dopUpPitchTrim_B;
			DiscOutPort dopDownPitchTrim_A;
			DiscOutPort dopDownPitchTrim_B;
			DiscOutPort dopRightRollTrim_A;
			DiscOutPort dopRightRollTrim_B;
			DiscOutPort dopLeftRollTrim_A;
			DiscOutPort dopLeftRollTrim_B;
			DiscOutPort dopRightYawTrim_A;
			DiscOutPort dopRightYawTrim_B;
			DiscOutPort dopLeftYawTrim_A;
			DiscOutPort dopLeftYawTrim_B;

		public:
			explicit PanelL2( Atlantis* _sts );
			virtual ~PanelL2();

			void DefineVC() override;
			void RegisterVC() override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
			void Realize() override;
	};
}

#endif// __VC_PANELL2_H
