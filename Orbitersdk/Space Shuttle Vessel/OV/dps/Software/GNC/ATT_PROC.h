/****************************************************************************
  This file is part of Space Shuttle Vessel

  Ascent/Entry Attitude Processing definition


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

#ifndef _dps_ATT_PROC_H_
#define _dps_ATT_PROC_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ATT_PROC:public SimpleGPCSoftware
	{
		private:
#if 1// for OSFS2016 only, r87 fixes issue
			bool firststep;
			float COSPHI_0;
			float SINPHI_0;
			float BETA_0;
			float ALPHA_0;
			float PHI_0;
#endif// for OSFS2016 only, r87 fixes issue

			void ATT_PROC_INIT( void );
			void ATT_PROC_OUTER( void );
			void ATT_PROC_INNER( void );
			void ATT_PROC_EULER( const unsigned short ATT_MODE, const unsigned short MM );
			void ATT_PROC_DISP( const unsigned short ATT_MODE, const unsigned short MM );
			void ATT_PROC_PREFIL( void );
			void ATT_PROC_RGASW( void );
			void ADI_QUAT_UPLINK( void );

		public:
			explicit ATT_PROC( SimpleGPCSystem* _gpc );
			~ATT_PROC( void );

			void Realize( void ) override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_ATT_PROC_H_
