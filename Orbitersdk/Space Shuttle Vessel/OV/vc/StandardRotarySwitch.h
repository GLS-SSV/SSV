/****************************************************************************
  This file is part of Space Shuttle Vessel

  Standard Rotary Switch VC component definition


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
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Standard Rotary Switch VC component



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
#ifndef _VC_STANDARDROTARYSWITCH_H
#define _VC_STANDARDROTARYSWITCH_H
#pragma once

#include "BasicRotarySwitch.h"
#include <discsignals.h>

namespace vc
{
	using ::discsignals::DiscreteBundle;
	using ::discsignals::DiscOutPort;
	using ::discsignals::DiscInPort;

	/**
	 * Rotary switch that sends single input signal to multiple possible output signals
	 */
	class RotaryDemuxSwitch: public BasicRotarySwitch
	{
	protected:
		vector<DiscOutPort> outputSignals;
		DiscInPort inputSignal;
		bool bInputConnected;
	public:
		RotaryDemuxSwitch(Atlantis* _sts, const std::string& _ident, unsigned short _usNumPositions);
		virtual ~RotaryDemuxSwitch();

		void OnPositionChange(unsigned short usNewPosition) override;

		void ConnectInputSignal(DiscreteBundle* pBundle, unsigned short usLine);
		void ConnectOutputSignal(unsigned short usIndex, DiscreteBundle* pBundle, unsigned short usLine);
	};

	/**
	 * Rotary switch that sends single output signal from multiple possible input signals
	 */
	class StandardRotarySwitch:public BasicRotarySwitch
	{
		protected:
			vector<vector<DiscInPort>> inputSignals;
			vector<DiscOutPort> outputSignal;

		public:
			StandardRotarySwitch( Atlantis* _sts, const std::string& _ident, unsigned short _usNumPositions, unsigned short _usNumMuxes );
			virtual ~StandardRotarySwitch();

			void OnPreStep( double simt, double simdt, double mjd ) override;

			void ConnectInputSignal( unsigned short usMux, unsigned short usIndex, DiscreteBundle* pBundle, unsigned short usLine );
			void ConnectOutputSignal( unsigned short usMux, DiscreteBundle* pBundle, unsigned short usLine );
	};
};

#endif // _VC_STANDARDROTARYSWITCH_H