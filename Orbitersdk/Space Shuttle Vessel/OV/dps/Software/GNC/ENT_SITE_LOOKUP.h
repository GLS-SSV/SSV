/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry Site Lookup definition


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

#ifndef _dps_ENT_SITE_LOOKUP_H_
#define _dps_ENT_SITE_LOOKUP_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ENT_SITE_LOOKUP:public SimpleGPCSoftware
	{
		private:
			unsigned short ALTERNATE_SITE_1[45];
			unsigned short ALTERNATE_SITE_2[45];
			float RUNWAY_ALT[90];// [ft]
			char* RUNWAY_NAME[90];
			float RW_AZIMUTH[90];// [rad]
			float RW_DELH[90];// [ft]
			float RW_LAT[90];// [rad]
			unsigned short RW_LENGTH[90];// [ft]
			float RW_LON[90];// [rad]
			float RW_MAG_VAR[90];// [rad]

			unsigned short FIRST_PASS;
			unsigned short PRIME_RUNWAY_INDEX;
			unsigned short ALT_SITES_RESET_INH;
			unsigned short TAL_ALT_SITE_INIT;

			void ENTRY_SITE_LOOKUP_INIT( void );
			void ENTRY_RUNWAY_SITE_LOOKUP( void );
			void ENTRY_TACAN_SITE_LOOKUP( void );

		public:
			explicit ENT_SITE_LOOKUP( SimpleGPCSystem* _gpc );
			~ENT_SITE_LOOKUP( void );

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_ENT_SITE_LOOKUP_H_
