/****************************************************************************
  This file is part of Space Shuttle Vessel

  RCS Activity Light processing definition


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
#ifndef _dps_RCS_ACT_LT_H_
#define _dps_RCS_ACT_LT_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class RCS_ACT_LT:public SimpleGPCSoftware
	{
		private:
			unsigned short NUM;
			unsigned short EVEN_PASS_FLAG;

			unsigned short YL;
			unsigned short YR;
			unsigned short PD;
			unsigned short PU;
			unsigned short RL;
			unsigned short RR;
			unsigned short YAW_SAT;
			unsigned short RATE_SAT;

			unsigned short RCS_YL_LAMP;
			unsigned short RCS_YR_LAMP;
			unsigned short RCS_PD_LAMP;
			unsigned short RCS_PU_LAMP;
			unsigned short RCS_RL_LAMP;
			unsigned short RCS_RR_LAMP;
			unsigned short HUD_HYDSAT;

		public:
			explicit RCS_ACT_LT( SimpleGPCSystem* _gpc );
			~RCS_ACT_LT( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_RCS_ACT_LT_H_
