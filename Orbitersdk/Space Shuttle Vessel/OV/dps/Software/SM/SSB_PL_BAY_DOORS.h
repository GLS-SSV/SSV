/****************************************************************************
  This file is part of Space Shuttle Vessel

  Payload Bay Doors software definition


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

#ifndef _dps_SSB_PL_BAY_DOORS_H_
#define _dps_SSB_PL_BAY_DOORS_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	using namespace discsignals;

	/**
	 * @brief	Implementation of the Payload Bay Doors software that runs in the GPCs.
	 *
	 * This class generates commands to drive Payload Bay doors and latches.
	 */
	class SSB_PL_BAY_DOORS:public SimpleGPCSoftware
	{
		private:
			unsigned short PF1_IOM3_CH0;
			unsigned short PF1_IOM6_CH0;
			unsigned short PF1_IOM9_CH0;
			unsigned short PF2_IOM3_CH0;
			unsigned short PF2_IOM6_CH0;
			unsigned short PF2_IOM9_CH0;

			unsigned short PF01_OUTPUT_1;// PF1_IOM2_CH0
			unsigned short PF01_OUTPUT_2;// PF1_IOM7_CH0
			unsigned short PF01_OUTPUT_3;// PF1_IOM14_CH0
			unsigned short PF01_OUTPUT_4;// PF1_IOM14_CH2
			unsigned short PF02_OUTPUT_1;// PF2_IOM2_CH0
			unsigned short PF02_OUTPUT_2;// PF2_IOM7_CH0
			unsigned short PF02_OUTPUT_3;// PF2_IOM14_CH0
			unsigned short PF02_OUTPUT_4;// PF2_IOM14_CH2

			bool SSB_PBD_MORE_WORK_IND;
			double SSB_LATCH_DOOR_EXPIR_TIME;
			bool SSB_OPEN_CLOSE_FEEDBACK_INDIC;
			unsigned short SSB_PREVIOUS_SWITCH_POS;
			/**
			 * 1 = op; 2 = cl
			 */
			unsigned short SSB_OPEN_CLOSE_COMPLETE;
			unsigned short SSB_CURRENT_LATCH_DOOR_POINTER;
			unsigned short SSB_COMMANDS_ENABLED_ARRAY[6][2];


			void PBD_LATCH_STATUS( const bool p1, const bool p2, const bool p3, const bool p4, char* computedvalue ) const;
			void PBD_DOOR_STATUS( const bool p1, const bool p2, const bool p3, const bool p4, char* computedvalue ) const;
			void MODE_SELECTION( void );
			void DISABLE_COMMANDS( void );
			void DISABLE_UNVERIFIED_COMMANDS( void );

		public:
			explicit SSB_PL_BAY_DOORS( SimpleGPCSystem* _gpc );
			~SSB_PL_BAY_DOORS( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_SSB_PL_BAY_DOORS_H_
