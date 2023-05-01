/****************************************************************************
  This file is part of Space Shuttle Vessel

  Reaction Control System Redundancy Management definition


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
#ifndef _dps_RCS_RM_H_
#define _dps_RCS_RM_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * @brief	Implementation of the RCS RM software that runs in the GPCs.
	 * 
	 * This class handles the RM of RCS.
	 */
	class RCS_RM:public SimpleGPCSoftware
	{
		private:
			double step_AVAILABLE_JET_STATUS_TABLE;
			double step_JET_FAILED_OFF_MONITOR;
			double step_JET_FAILED_ON_MONITOR;
			double step_JET_LEAK_MONITOR;
			double step_MANIFOLD_STATUS_MONITOR;
			double step_JET_FAULT_LIMIT;
			double step_JET_PRIORITY_STATUS_TABLE;

			static const unsigned int FIRE_B_LEN = 3;
			bool histFIRE_CMD_B[FIRE_B_LEN][44];

			

			// AVAILABLE_JET_STATUS_TABLE
			void AVAILABLE_JET_STATUS_TABLE( void );

			// JET_FAILED_OFF_MONITOR
			unsigned short JET_FAILED_OFF_COUNTER[44];
			bool JET_DES_INHIBIT_PV_JFOFFM[44];// previous JET_DES_INHIBIT for JET_FAILED_OFF_MONITOR

			void JET_FAILED_OFF_MONITOR( void );

			// JET_FAILED_ON_MONITOR
			void JET_FAILED_ON_MONITOR( void );

			// JET_LEAK_MONITOR
			void JET_LEAK_MONITOR( void );

			// MANIFOLD_STATUS_MONITOR
			bool FUEL_MANIFOLD_VALVE_OPEN_PV[15];
			bool OXIDIZER_MANIFOLD_VALVE_OPEN_PV[15];
			bool FUEL_MANIFOLD_VALVE_CLOSE_PV[15];
			bool OXIDIZER_MANIFOLD_VALVE_CLOSE_PV[15];
			unsigned short MANF_DILEM_PASS_CONT[15];// DILEMMA PASS COUNTER
			unsigned short PWR_FAIL_PASS_CNT[15];// POWER FAIL PASS COUNTER (fwd not used)
			bool PWR_FAIL_SET[15];// (fwd not used)

			void MANIFOLD_STATUS_MONITOR( void );

			// JET_FAULT_LIMIT
			bool JET_AUTO_DES[44];
			unsigned short RCS_FWD_JET_FAIL_CNT;
			unsigned short RCS_L_JET_FAIL_CNT;
			unsigned short RCS_R_JET_FAIL_CNT;

			void JET_FAULT_LIMIT( void );

			// JET_PRIORITY_STATUS_TABLE
			bool JET_DES_INHIBIT_PV_JPST[44];// previous JET_DES_INHIBIT for JET_PRIORITY_STATUS_TABLE

			void JET_PRIORITY_STATUS_TABLE( void );

		public:
			explicit RCS_RM( SimpleGPCSystem* _gpc );
			~RCS_RM( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_RCS_RM_H_
