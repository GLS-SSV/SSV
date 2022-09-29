/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel 36V73A8A1 definition



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
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/01/10   GLS
2022/01/12   GLS
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

#ifndef __VC_PANELA8A1_H
#define __VC_PANELA8A1_H


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class StdSwitch3;
	class LockableLever3;
	class StandardTalkback2;
	class RotaryDemuxSwitch;
	class StandardSingleLight;
	class PushButtonIndicatorSingleLight;
	class _7SegDisp_RMS;

	using namespace discsignals;


	class PanelA8A1 : public AtlantisPanel
	{
			StdSwitch3* pEEMode;
			StdSwitch3* pEEManContr;
			LockableLever3* pShoulderBrace;
			StdSwitch3* pSingleDirectDrive;

			StandardTalkback2* pEECapture;
			StandardTalkback2* pEEExtend;
			StandardTalkback2* pEEClose;
			StandardTalkback2* pEEOpen;
			StandardTalkback2* pEERigid;
			StandardTalkback2* pEEDerigid;
			StandardTalkback2* pShoulderBraceTb;
			StandardTalkback2* pSoftStopTB;
			StandardTalkback2* pRateMinTB;

			RotaryDemuxSwitch* pLEDParameter;
			RotaryDemuxSwitch* pLEDJoint;
			RotaryDemuxSwitch* pRMSMode;

			StandardSingleLight* pModeLights[12];
			StandardSingleLight* pCWLights[11];
			StandardSingleLight* pSequenceLights[2];

			PushButtonIndicatorSingleLight* pMasterAlarm;

			_7SegDisp_RMS* pRMS;

			DiscInPort lighttest;
			DiscInPort lightcmd[26];
			DiscOutPort lightoutput[26];

		public:
			explicit PanelA8A1( Atlantis* _sts );
			virtual ~PanelA8A1();

			void RegisterVC() override;
			void DefineVC() override;
			void Realize() override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __VC_PANELA8A1_H
