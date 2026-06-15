/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry Display Processing definition


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

#ifndef _dps_ENT_DIP_H_
#define _dps_ENT_DIP_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ENT_DIP:public SimpleGPCSoftware
	{
		private:
			unsigned short FIRST_PASS;
			unsigned short I;
			unsigned short TRAILER_NO;
			double ELAPSED_TIME;
			short SHUTTLE_X_PREV;
			short SHUTTLE_Y_PREV;
			short GUID_X_PREV;

		public:
			explicit ENT_DIP( SimpleGPCSystem* _gpc );
			~ENT_DIP( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _dps_ENT_DIP_H_
