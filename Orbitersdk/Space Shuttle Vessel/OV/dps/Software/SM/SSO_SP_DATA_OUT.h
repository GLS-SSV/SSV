/****************************************************************************
  This file is part of Space Shuttle Vessel

  Special Processes Data Out definition


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

#ifndef _dps_SSO_SP_DATA_OUT_H_
#define _dps_SSO_SP_DATA_OUT_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	using namespace discsignals;

	/**
	 * @brief	Implementation of the Special Processes Data Out software that runs in the GPCs.
	 *
	 * This class handles output for several SM modules.
	 */
	class SSO_SP_DATA_OUT:public SimpleGPCSoftware
	{
		private:
			unsigned short PF01_OUTPUT_1;// PF1_IOM2_CH0
			unsigned short PF01_OUTPUT_2;// PF1_IOM7_CH0
			unsigned short PF01_OUTPUT_3;// PF1_IOM14_CH0
			unsigned short PF01_OUTPUT_4;// PF1_IOM14_CH2
			unsigned short PF02_OUTPUT_1;// PF2_IOM2_CH0
			unsigned short PF02_OUTPUT_2;// PF2_IOM7_CH0
			unsigned short PF02_OUTPUT_3;// PF2_IOM14_CH0
			unsigned short PF02_OUTPUT_4;// PF2_IOM14_CH2

		public:
			explicit SSO_SP_DATA_OUT( SimpleGPCSystem* _gpc );
			~SSO_SP_DATA_OUT( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_SSO_SP_DATA_OUT_H_
