/****************************************************************************
  This file is part of Space Shuttle Vessel

  Horizontal Situation Display Processing definition


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

#ifndef _dps_HORIZ_SIT_SPEC_H_
#define _dps_HORIZ_SIT_SPEC_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class HORIZ_SIT_SPEC:public SimpleGPCSoftware
	{
		private:
			bool init;

			float TGO_MIN;
			float YSGNPO;
			float HAC_TIME;
			unsigned short HAC_TIME_SNAPPED;
			float HERROR_MAX;
			float TGO_SCALE_FACTOR;
			float HERROR_SCALE_FACTOR;
			float RERRC_SCALE_FACTOR;
			float Y_SCALE_FACTOR;

		public:
			explicit HORIZ_SIT_SPEC( SimpleGPCSystem* _gpc );
			~HORIZ_SIT_SPEC( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_HORIZ_SIT_SPEC_H_
