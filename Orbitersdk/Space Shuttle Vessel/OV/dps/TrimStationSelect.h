/****************************************************************************
  This file is part of Space Shuttle Vessel

  Trim Station Select definition


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

#ifndef _dps_TRIM_STATION_SELECT_H_
#define _dps_TRIM_STATION_SELECT_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * @brief	Implementation of the Trim Station Select software that runs in the GPCs.
	 *
	 * This class handles Trim Station Select.
	 */
	class TrimStationSelect:public SimpleGPCSoftware
	{
		public:
			explicit TrimStationSelect( SimpleGPCSystem* _gpc );
			~TrimStationSelect( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_TRIM_STATION_SELECT_H_
