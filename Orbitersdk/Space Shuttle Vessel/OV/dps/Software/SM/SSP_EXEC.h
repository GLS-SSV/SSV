/****************************************************************************
  This file is part of Space Shuttle Vessel

  Special Processes Executive definition


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

#ifndef _SSP_EXEC_H_
#define _SSP_EXEC_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class SSD_SP_DATA_ACQ;
	class SSB_PL_BAY_DOORS;
	class SSO_SP_DATA_OUT;


	class SSP_EXEC : public SimpleGPCSoftware
	{
		private:
			int cycle;
			SSD_SP_DATA_ACQ* pSSD_SP_DATA_ACQ;
			SSB_PL_BAY_DOORS* pSSB_PL_BAY_DOORS;
			SSO_SP_DATA_OUT* pSSO_SP_DATA_OUT;

		public:
			SSP_EXEC( SimpleGPCSystem* pGPC );
			virtual ~SSP_EXEC( void );

			void OnPreStep( double simt, double simdt, double mjd );
	};
}

#endif// _SSP_EXEC_H_
