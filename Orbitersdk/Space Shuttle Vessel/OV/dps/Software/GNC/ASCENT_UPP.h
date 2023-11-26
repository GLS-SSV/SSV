/****************************************************************************
  This file is part of Space Shuttle Vessel

  Ascent User Parameter Processing definition


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

#ifndef _dps_ASCENT_UPP_H_
#define _dps_ASCENT_UPP_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ASCENT_UPP:public SimpleGPCSoftware
	{
		private:
			OBJHANDLE hEarth;

			void STATE_PROPAGATION( const VECTOR3& ECEF_vel, const VECTOR3& ECI_vel );
			void ASCENT_RTLS_COMPS( const VECTOR3& ECEF_vel, const VECTOR3& ECEF_pos );
			void PW_HSI_COMPS( const VECTOR3& ECEF_vel, const VECTOR3& ECI_vel, const VECTOR3& ECEF_pos, const VECTOR3& ECI_pos );
			void ASCENT_UPP_INIT( void );

		public:
			explicit ASCENT_UPP( SimpleGPCSystem* _gpc );
			~ASCENT_UPP( void );

			void Realize( void ) override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_ASCENT_UPP_H_
