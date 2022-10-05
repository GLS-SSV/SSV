/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A1U definition



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

  Panel A1U definition



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
#ifndef _VC_PANELA1U_H_
#define _VC_PANELA1U_H_


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class RotaryDemuxSwitch;
	class StandardTalkback2;


	class PanelA1U: public AtlantisPanel
	{
	public:
		explicit PanelA1U(Atlantis* _sts);
		virtual ~PanelA1U();

		void DefineVC() override;
		void RegisterVC() override;
		void Realize() override;

	private:
		//StdSwitch3* pSignalStrengthSelect;
		StdSwitch3* pSlewAzimuth;
		StdSwitch3* pSlewElevation;
		StdSwitch2* pSlewRate;
		StdSwitch2* pControl;
		RotaryDemuxSwitch* pSteeringMode;
		StdSwitch2* pSearch;
		StdSwitch3* pPower;
		StdSwitch3* pMode;
		StdSwitch3* pRadarOutput;
		//RotaryDemuxSwitch* pHighDataRateSP;
		//RotaryDemuxSwitch* pLowDataRateSP;
		//LockableLever2* pTAGSEncrypt;
		StandardTalkback2* pScanWarnTB;
		StandardTalkback2* pTrackTB;
		StandardTalkback2* pSearchTB;

	};
}

#endif// _VC_PANELA1U_H_
