/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel O2 definition



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

  Panel O2 definition



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
#ifndef __VC_PANELO2_H
#define __VC_PANELO2_H


#include "AtlantisPanel.h"
#include <discsignals.h>


namespace vc
{
	class StandardCurvedMechMeter;
	class StandardRotarySwitch;
	class StdSwitch3;

	using namespace discsignals;


	class PanelO2 : public AtlantisPanel
	{
		private:
			StandardCurvedMechMeter* pCryoO2HtrAssyTempMeter;
			StandardCurvedMechMeter* pCryoO2PressMeter;
			StandardCurvedMechMeter* pCryoO2QtyMeter;
			StandardCurvedMechMeter* pCryoH2PressMeter;
			StandardCurvedMechMeter* pCryoH2QtyMeter;
			StandardCurvedMechMeter* pFuelCellStackTempMeter;

			StandardRotarySwitch* pCryoO2HtrAssyTemp;
			StandardRotarySwitch* pCryoPressQty;
			StdSwitch3* pFuelCellStackTemp;

			DiscInPort pFuelCellStackTemp1;
			DiscInPort pFuelCellStackTemp3;
			DiscOutPort pFuelCellStackTempMeterInput;

		public:
			explicit PanelO2( Atlantis* _sts );
			virtual ~PanelO2();

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __VC_PANELO2_H