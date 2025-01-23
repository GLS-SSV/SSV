/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry/Landing Reaction Control System Command Subsystem Operating Program definition


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
#ifndef _dps_EL_RCS_CMD_SOP_H_
#define _dps_EL_RCS_CMD_SOP_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * @brief	Implementation of the E/L RCS CMD SOP software that runs in the GPCs.
	 * 
	 * This class interfaces with the hardware of the RCS.
	 */
	class EL_RCS_CMD_SOP:public SimpleGPCSoftware
	{
		private:
			double step40ms;
			double step80ms;

			bool RCS_ON[44];

			unsigned short availablejets[44];
			unsigned short availablejetsdump[44];

			unsigned short DUMP0;// 4 +X
			unsigned short DUMP1;// 8 +/-Y
			unsigned short DUMP2;// 12 +/-Z
			unsigned short DELAY1;
			unsigned short DELAY2;
			unsigned short NCYC1;
			unsigned short NCYC2;

			unsigned short OLDABT_JETS;
			unsigned short OLDDELAY1;
			unsigned short OLD20NULL;
			unsigned short OLDXNULL;

			unsigned short ABT_X_ON_LAST_PASS;
			unsigned short ABT_20_NULL_LAST_PASS;
			unsigned short AFT_MANIFOLD_12_JET_INH_FLAG_LAST_PASS;
			unsigned short AFT_MANIFOLD_345_JET_INH_FLAG_LAST_PASS;
			unsigned short IC_CPLT_LAST;// OMSRCS_INTERCONNECT_COMPLETE_FLAG_LAST_PASS
			unsigned short RCS_12_ALL_JET_INHIBIT_FLAG_LAST_PASS;
			unsigned short RCS_345_ALL_JET_INHIBIT_FLAG_LAST_PASS;

			unsigned short counter_RCS_12_ALL_JET_INHIBIT;
			unsigned short counter_RCS_345_ALL_JET_INHIBIT;
			unsigned short counter_AFT_MANIFOLD_12_JET_INH_X;
			unsigned short counter_AFT_MANIFOLD_12_JET_INH_Y;
			unsigned short counter_AFT_MANIFOLD_345_JET_INH_X;
			unsigned short counter_AFT_MANIFOLD_345_JET_INH_Y;
			bool ena_RCS_12_ALL_JET_INHIBIT;
			bool ena_RCS_345_ALL_JET_INHIBIT;
			bool ena_AFT_MANIFOLD_12_JET_INH_X;
			bool ena_AFT_MANIFOLD_12_JET_INH_Y;
			bool ena_AFT_MANIFOLD_345_JET_INH_X;
			bool ena_AFT_MANIFOLD_345_JET_INH_Y;

			void FRCS( double dt );

			void N_CYCLE( const unsigned short INPUT, const unsigned short NN, unsigned short& LASTIN, unsigned short& N, unsigned short& OUTPUT );

		public:
			explicit EL_RCS_CMD_SOP( SimpleGPCSystem* _gpc );
			~EL_RCS_CMD_SOP( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_EL_RCS_CMD_SOP_H_
