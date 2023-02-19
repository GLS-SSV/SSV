/****************************************************************************
  This file is part of Space Shuttle Vessel

  Nose Wheel Position Subsystem Operating Program definition


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
2020/06/20   GLS
2021/07/03   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/12/23   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Nose Wheel Position Subsystem Operating Program definition



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
#ifndef _dps_NW_POSN_SOP_H_
#define _dps_NW_POSN_SOP_H_


#include "../SimpleGPCSoftware.h"
#include <discsignals.h>


namespace dps
{
	using namespace discsignals;

	/**
	 * @brief	Implementation of the Nose Wheel Position Subsystem Operating Program software that runs in the GPCs.
	 *
	 * This class retrieves the Nose Wheel position, compares it to the command, and generates NWS enable signals.
	 */
	class NW_POSN_SOP:public SimpleGPCSoftware
	{
		private:
			DiscOutPort dopNWS1_ENABLE_A_CMD;
			DiscOutPort dopNWS1_ENABLE_B_CMD;
			DiscOutPort dopNWS2_ENABLE_A_CMD;
			DiscOutPort dopNWS2_ENABLE_B_CMD;
			DiscOutPort dopNW_POSN_ERROR;

			DiscInPort dipNWS1_ON;
			DiscInPort dipNWS2_ON;
			DiscInPort dipNWS_POS_A;
			DiscInPort dipNWS_POS_B;
			DiscInPort dipNWS_POS_C;
			DiscInPort dipNWS1_ACT;
			DiscInPort dipNWS2_ACT;

			double DNWC;// store NWS command for next cycle
			double LAST_NW_POS;
			double NW_POS_ERR_CNT[2];

			bool NW_POS_ERR;
			bool NWS1_fail;
			bool NWS2_fail;

			bool NosewheelPositionComparison( double DNWC, double NW_POS, double dt );

		public:
			explicit NW_POSN_SOP( SimpleGPCSystem* _gpc );
			virtual ~NW_POSN_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_NW_POSN_SOP_H_
