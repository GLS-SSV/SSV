/****************************************************************************
  This file is part of Space Shuttle Vessel

  DPS Reconfiguration definition


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
#ifndef _dps_DPSRECON_H_
#define _dps_DPSRECON_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * System Services \ System Control \ System Reconfiguration
	 */
	class DPS_Reconfiguration : public SimpleGPCSoftware
	{
		private:
			unsigned short ARDVL_CRT;// Input_DEU
			unsigned short ARDVL_MF;// Input_MF (1-PL, 2-GNC, 3-SM)
			unsigned short ARDVL_CMDR_SET;// Commander_Set
			unsigned short ARDVL_NEW_CMDR;// New_Bus_Commander
			unsigned short ARDVL_CURR_CMDR;// Current_Bus_Commander
			unsigned short ARDVL_CRT_FLG[4];// Assigned_OPS_0_GPC
			unsigned short ARDVL_RUN;// Run_GPC
			unsigned short ARDVL_STBY;// Standby_GPC
			unsigned short ARDVL_ZERO;// Zero_GPC
			unsigned short ARDVL_BUS;// Bus_Number

			bool ARDVL_MF_FLAG;// MF_Flag
			bool STAT;// Handover_Status


			void Major_Function_Switch_Change_Processing( unsigned short iccmsg );// (830.1)
			void CMPTR_CRT_Key_Processing( void );// (830.2)
			void OPS_Initiate_Processing( void );// (830.4)
			void Fail_To_Sync_Processing( void );// (830.5)
			void Force_OPS_0_Processing( void );// (830.6)
			void Major_Function_Hierarchy( void );// (830.7)
			void Assign_DEU_Processor( void );// (830.8)
			void Bus_Handover_Cooperation( void );// (830.9)

		public:
			explicit DPS_Reconfiguration( SimpleGPCSystem* pGPC );
			virtual ~DPS_Reconfiguration( void );

			void ARD_BUS_CHG( unsigned short B/*ICC_Buffer_Number*/, unsigned short I/*ICC_Array_Index*/ );// Bus_Configuration_Change (830) (renamed "Common Set Bus Configuration Change"?)
	};
}

#endif// _dps_DPSRECON_H_
