/****************************************************************************
  This file is part of Space Shuttle Vessel

  On-Orbit Attitude Director Indicator Processing definition


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

#ifndef _dps_ORB_ADI_PROC_H_
#define _dps_ORB_ADI_PROC_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ORB_ADI_PROC:public SimpleGPCSoftware
	{
		private:

		public:
			explicit ORB_ADI_PROC( SimpleGPCSystem* _gpc );
			~ORB_ADI_PROC( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_ORB_ADI_PROC_H_
