/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry/Landing ADI Processing definition


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

#ifndef _dps_EL_ADI_PROC_H_
#define _dps_EL_ADI_PROC_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class EL_ADI_PROC:public SimpleGPCSoftware
	{
		private:
			bool firstpass304602;
			bool firstpass305603r;
			bool firstpass305603e;

			bool DO_ADI_TGO_DISPLAY;
			bool DISPLAY_RATE_MED;
			bool STOW_MED;
			bool HAC_TIME_SNAPPED;
			bool ALT_TIME_SNAPPED;
			double HAC_TIME;
			double ALT_TIME;

			unsigned short IPHASE_PREV;
			unsigned short RW_ID_PREV;
			float YSGN_PREV;
			unsigned short NEP_FB_PREV;
			unsigned short CSSRY_IND_PREV;
			unsigned short CSSP_IND_PREV;
			bool ZERO_PR_INT;
			bool ZERO_R_INT;
			bool ZERO_P_INT;
			bool ZERO_5_INT;

			unsigned short ZERO_PR_INT_COUNT;
			unsigned short ZERO_R_INT_COUNT;
			unsigned short ZERO_P_INT_COUNT;
			unsigned short ZERO_5_INT_COUNT;

			double RERR_INTP;
			double RERR_INTN;

			double NZ_INTP;
			double NZ_INTN;

		public:
			explicit EL_ADI_PROC( SimpleGPCSystem* _gpc );
			~EL_ADI_PROC( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_EL_ADI_PROC_H_
