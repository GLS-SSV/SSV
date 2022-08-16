/****************************************************************************
  This file is part of Space Shuttle Vessel

  Primary Caution and Warning subsystem definition


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
  file Doc\Space Shuttle Vessel\GPL.txt for more details.

  **************************************************************************/
#ifndef __PCW_H_
#define __PCW_H_


#include "AtlantisSubsystem.h"
#include <DiscInPort.h>
#include <DiscOutPort.h>
#include <FlipFlopD.h>


using namespace discsignals;


class PrimaryCautionWarning:public AtlantisSubsystem
{
	private:
		DiscInPort ParameterData[128];
		DiscOutPort AnnunciatorLightSignals[40];
		DiscOutPort MatrixLightSignals[120];
		DiscOutPort ST[8];

		DiscInPort PARAMSTATUS_INHIBITED;
		DiscInPort PARAMSTATUS_INACTIVE;
		DiscInPort PARAMSTATUS_TRIPPED;
		DiscInPort MEMORY_CLEAR;
		DiscInPort MEMORY_INACTIVE;
		DiscInPort MEMORY_READ;
		DiscInPort LAMPTEST_RIGHT;
		DiscInPort LAMPTEST_INACTIVE;
		DiscInPort LAMPTEST_LEFT;
		DiscInPort LIMIT_LOWER;
		DiscInPort LIMIT_UPPER;
		DiscInPort FUNC_READ;
		DiscInPort FUNC_INACTIVE;
		DiscInPort FUNC_SET;
		DiscInPort PARAM_INHIBIT;
		DiscInPort PARAM_INACTIVE;
		DiscInPort PARAM_ENABLE;
		DiscInPort CAUTIONWARNINGMEMORY_CLEAR;
		DiscInPort CAUTIONWARNINGMEMORY_INACTIVE;
		DiscInPort CAUTIONWARNINGMEMORY_READ;
		DiscInPort CAUTIONWARNINGMODE_ASCENT;
		DiscInPort CAUTIONWARNINGMODE_NORM;
		DiscInPort CAUTIONWARNINGMODE_ACK;

		DiscInPort ParameterSelect[9];
		DiscInPort LimitValue[8];


		DiscInPort BU_CW_A_CMD_1;
		DiscInPort BU_CW_A_CMD_2;
		DiscInPort BU_CW_A_CMD_3;
		DiscInPort BU_CW_A_CMD_4;
		DiscInPort BU_CW_B_CMD_1;
		DiscInPort BU_CW_B_CMD_2;

		DiscInPort SM_LIGHT_A_CMD_1;
		DiscInPort SM_LIGHT_A_CMD_2;
		DiscInPort SM_LIGHT_A_CMD_3;
		DiscInPort SM_LIGHT_A_CMD_4;
		DiscInPort SM_LIGHT_B_CMD_1;
		DiscInPort SM_LIGHT_B_CMD_2;

		DiscInPort SM_TONE_A_CMD_1;
		DiscInPort SM_TONE_A_CMD_2;
		DiscInPort SM_TONE_A_CMD_3;
		DiscInPort SM_TONE_A_CMD_4;
		DiscInPort SM_TONE_B_CMD_1;
		DiscInPort SM_TONE_B_CMD_2;

		DiscInPort MASTER_ALARM_RESET_A1;
		DiscInPort MASTER_ALARM_RESET_A2;
		DiscInPort MASTER_ALARM_RESET_B1;
		DiscInPort MASTER_ALARM_RESET_B2;

		DiscOutPort SMAlert_ACA2;
		DiscOutPort SMAlert_ACA3;

		DiscOutPort MasterAlarm_F2_A;
		DiscOutPort MasterAlarm_F2_B;
		DiscOutPort MasterAlarm_F4_A;
		DiscOutPort MasterAlarm_F4_B;
		DiscOutPort MasterAlarm_A7U_A;
		DiscOutPort MasterAlarm_A7U_B;
		DiscOutPort MasterAlarm_MO52J_A;
		DiscOutPort MasterAlarm_MO52J_B;


		// indicates if tones are playing
		bool bCW_TONE;
		bool bSM_TONE;
		

		bool TurnOn_TDout[2];
		bool TurnOff_TDout[2];
		double TurnOn_TDtime[2];
		double TurnOff_TDtime[2];

		bool InhibitMemory[128];// 1x128
		unsigned char NCountMemory[128];// 4x128
		bool NCountOverflowMemory[128];// 1x128
		bool RecallMemory[128];// 1x128
		bool PrimaryCWTriggerMemory[128];// 1x128
		unsigned char LimitValueRAM[256];// 8x256 (content: bits 0-6 = value, bit 7 = value set)
		
		// 0 = A, 1 = B
		FlipFlopD PRI_CW[2];
		FlipFlopD CW_TONE_ENABLE[2];
		FlipFlopD BU_CW_TONE[2];
		FlipFlopD BU_CW_LIGHT[2];
		FlipFlopD SW_TONE[2];
		FlipFlopD ST_FAIL_1[2];
		FlipFlopD ST_FAIL_2[2];

	public:
		explicit PrimaryCautionWarning( AtlantisSubsystemDirector* _director  );
		~PrimaryCautionWarning( void );

		void Realize( void ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine() const override {return true;};
		void OnPreStep( double simt, double simdt, double mjd ) override;

		void MasterAlarmToneLogic( unsigned int side, bool Pri_CW_Trigger, bool BU_CW, bool SM_TONE, bool& MasterAlarmRelaySignal, bool& cw_tone_request, bool& sm_tone_request, bool& PriCWlight, bool& BUCWlight, double dt );
};


#endif// __PCW_H_
