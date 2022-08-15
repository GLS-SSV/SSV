/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel O3 definition



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
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel O3 definition



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
#ifndef __VC_PANELO3_H
#define __VC_PANELO3_H


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class RotaryDemuxSwitch;
	class StdSwitch3;
	class _7SegDisp_RCSOMS_PRPLT_QTY;
	class _7SegDisp_MissionTime;
	class StandardCurvedMechMeter;

	using namespace discsignals;


	class PanelO3 : public AtlantisPanel
	{
		private:
			RotaryDemuxSwitch* pRCSOMS_PRESS;
			RotaryDemuxSwitch* pRCSOMS_PRPLTQTY;

			StdSwitch3* pMissionTimer;

			_7SegDisp_RCSOMS_PRPLT_QTY* pRCSOMS_PRPLT_QTY;
			_7SegDisp_MissionTime* pMissionTime;

			StandardCurvedMechMeter* pRCSOMSPressLeftOxidMeter;
			StandardCurvedMechMeter* pRCSOMSPressLeftFuelMeter;
			StandardCurvedMechMeter* pRCSOMSPressFwdKitOxidMeter;
			StandardCurvedMechMeter* pRCSOMSPressFwdKitFuelMeter;
			StandardCurvedMechMeter* pRCSOMSPressRightOxidMeter;
			StandardCurvedMechMeter* pRCSOMSPressRightFuelMeter;

			DiscInPort pRCSOMS_PRESS_RCSHeX10;
			DiscInPort pRCSOMS_PRESS_RCSPRPLT;
			DiscInPort pRCSOMS_PRESS_OMSPRPLT;
			DiscOutPort pRCSOMSPressLeftOxidMeterInput;
			DiscOutPort pRCSOMSPressLeftFuelMeterInput;
			DiscOutPort pRCSOMSPressFwdKitOxidMeterInput;
			DiscOutPort pRCSOMSPressFwdKitFuelMeterInput;
			DiscOutPort pRCSOMSPressRightOxidMeterInput;
			DiscOutPort pRCSOMSPressRightFuelMeterInput;

		public:
			explicit PanelO3( Atlantis* _sts );
			virtual ~PanelO3();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __VC_PANELO3_H