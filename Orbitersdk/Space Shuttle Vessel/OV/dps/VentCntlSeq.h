/****************************************************************************
  This file is part of Space Shuttle Vessel

  Vent Door Control Sequence definition


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

#ifndef _dps_VENT_CNTL_SEQ_H_
#define _dps_VENT_CNTL_SEQ_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	using namespace discsignals;

	/**
	 * @brief	Implementation of the Vent Door Control Sequence software that runs in the GPCs.
	 *
	 * This class generates commands to position vent doors.
	 */
	class VentCntlSeq:public SimpleGPCSoftware
	{
		private:
			double VENT_CMDS_TIME_DELAY;

			double et_umb_dr_timer;
			double he_purge_timer;
			double timerA;
			double timerB;
			double timerC;
			double timerD;
			double timerE;
			double timerF;
			double timerG;
			double timerH;
			double timerJ;
			double timerK;
			double timerL;
			double timerM;
			double timerN;
			double timerP;
			double timerQ;

			double timera;
			double timerb;
			double timerc;
			double timerd;
			double timere;
			double timerf;
			double timerg;
			double timerh;
			double timerj;
			double timerk;
			double timerl;
			double timerm;

			bool firstpass2;
			bool firstpass2a_1;
			bool firstpass2a_2;
			bool firstpass2a_3;
			bool firstpass2a_4;
			bool firstpass2a_5;
			bool firstpass3_1;
			bool firstpass3_2;
			bool firstpass4;
			bool firstpass5;
			bool firstpass6;
			bool firstpass8_1;
			bool firstpass8_2;
			bool firstpass8_3;
			bool firstpass8_4;
			bool firstpass8_5;
			bool firstpass8_6;
			bool firstpass8_7;
			bool firstpass9_1;
			bool firstpass9_2;
			bool firstpass9_3;
			bool firstpass9_4;
			bool firstpass9_5;
			bool firstpass9_6;
			bool firstpass9_7;

			bool LEFT_VENTS_1_AND_6_OPEN_FLAG;// not config indication, but "command"

			bool L_FWD_VENTS_12_OPEN_CMD;
			bool L_PB_VENT_3_OPEN_CMD;
			bool L_PB_VENT_5_OPEN_CMD;
			bool L_PBW_VENTS_47_OPEN_CMD;
			bool L_PB_VENT_6_OPEN_CMD;
			bool L_AFT_VENTS_89_OPEN_CMD;
			bool R_FWD_VENTS_12_OPEN_CMD;
			bool R_PB_VENT_3_OPEN_CMD;
			bool R_PB_VENT_5_OPEN_CMD;
			bool R_PBW_VENTS_47_OPEN_CMD;
			bool R_PB_VENT_6_OPEN_CMD;
			bool R_AFT_VENTS_89_OPEN_CMD;

			bool L_FWD_VENTS_12_CLOSE_CMD;
			bool L_PB_VENT_3_CLOSE_CMD;
			bool L_PB_VENT_5_CLOSE_CMD;
			bool L_PBW_VENTS_47_CLOSE_CMD;
			bool L_PB_VENT_6_CLOSE_CMD;
			bool L_AFT_VENTS_89_CLOSE_CMD;
			bool R_FWD_VENTS_12_CLOSE_CMD;
			bool R_PB_VENT_3_CLOSE_CMD;
			bool R_PB_VENT_5_CLOSE_CMD;
			bool R_PBW_VENTS_47_CLOSE_CMD;
			bool R_PB_VENT_6_CLOSE_CMD;
			bool R_AFT_VENTS_89_CLOSE_CMD;

		public:
			explicit VentCntlSeq( SimpleGPCSystem* _gpc );
			~VentCntlSeq( void );

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_VENT_CNTL_SEQ_H_
