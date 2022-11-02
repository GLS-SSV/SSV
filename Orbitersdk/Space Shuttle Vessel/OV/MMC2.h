/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Motor Control Assembly 2 subsystem definition


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
/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/25   GLS
2022/01/31   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/05/14   GLS
2022/05/15   GLS
2022/05/16   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/11/01   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Mid Motor Control Assembly 2 definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _MMC2_H_
#define _MMC2_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class MMC2: public AtlantisSubsystem
{
	private:
		DiscOutPort PORT_MPM_SHOULDER_1_IND_PWR;
		DiscOutPort PORT_MPM_FWD_2_IND_PWR;
		DiscOutPort PORT_MPM_MID_1_IND_PWR;
		DiscOutPort STBD_MPM_MID_2_IND_PWR;
		DiscOutPort PORT_MPM_SYSTEM_2_STOW;
		DiscOutPort PORT_MPM_SYSTEM_2_DEPLOY;

		DiscInPort PORT_FWD_MECH_STOW_IND_2;
		DiscInPort PORT_MID_MECH_STOW_IND_2;
		DiscInPort PORT_AFT_MECH_STOW_IND_2;
		DiscInPort PORT_FWD_MECH_DEPLOY_IND_2;
		DiscInPort PORT_MID_MECH_DEPLOY_IND_2;
		DiscInPort PORT_AFT_MECH_DEPLOY_IND_2;

		DiscOutPort PORT_MRL_LATCHED;
		DiscOutPort PORT_MRL_RELEASED;
		DiscInPort PORT_MID_MRL_LATCH_IND_1;
		DiscInPort PORT_MID_MRL_RELEASE_IND_1;

		DiscInPort PL_BAY_MECH_PWR_SYS_1;

		// VENT DOORS
		// left no 3 motor 1
		DiscInPort LH_VENT_3_MOTOR_1_OPEN_A;
		DiscInPort LH_VENT_3_MOTOR_1_CLOSE_A;
		DiscInPort LH_VENT_3_MOTOR_1_OPEN_B;
		DiscInPort LH_VENT_3_MOTOR_1_CLOSE_B;
		DiscInPort LH_VENT_3_CLOSE_1;
		DiscInPort LH_VENT_3_OPEN_1;
		DiscOutPort LH_VENT_3_MOTOR_1_PWR;
		// right no 4/7 motor 1
		DiscInPort RH_VENTS_4_7_MOTOR_1_OPEN_A;
		DiscInPort RH_VENTS_4_7_MOTOR_1_CLOSE_A;
		DiscInPort RH_VENTS_4_7_MOTOR_1_OPEN_B;
		DiscInPort RH_VENTS_4_7_MOTOR_1_CLOSE_B;
		DiscInPort RH_VENTS_4_AND_7_CLOSE_1;
		DiscInPort RH_VENTS_4_AND_7_OPEN_1;
		DiscOutPort RH_VENTS_4_AND_7_MOTOR_1_PWR;
		// left no 6 motor 2
		bool K55;
		bool K67;
		bool K69;
		bool K57;
		DiscInPort LH_VENT_6_MOTOR_2_OPEN_A;
		DiscInPort LH_VENT_6_MOTOR_2_CLOSE_A;
		DiscInPort LH_VENT_6_MOTOR_2_PRG_1_A;
		DiscInPort LH_VENT_6_MOTOR_2_PRG_2_A;
		DiscInPort LH_VENT_6_MOTOR_2_OPEN_B;
		DiscInPort LH_VENT_6_MOTOR_2_CLOSE_B;
		DiscInPort LH_VENT_6_MOTOR_2_PRG_1_B;
		DiscInPort LH_VENT_6_MOTOR_2_PRG_2_B;
		DiscInPort LH_VENT_6_CLOSE_2;
		DiscInPort LH_VENT_6_OPEN_2;
		DiscInPort LH_VENT_6_PURGE_1_IND_2;
		DiscInPort LH_VENT_6_PURGE_2_IND_2;
		DiscOutPort LH_VENT_6_MOTOR_2_PWR;

		// PAYLOAD BAY DOORS
		DiscInPort PBD_ENABLE_SYS1;
		DiscInPort PBD_OPERATION_ENABLE_CMD_2A;
		DiscInPort PBD_OPERATION_ENABLE_CMD_2B;
		// port aft bkhd latch motor 2
		// cl 1-4 latch motort 2
		// cl 5-8 latch motor 2

		// KU BAND
		// ant a deploy motor 1
		DiscInPort KU_RNDZ_RADAR_STO_IND_1;
		DiscInPort KU_RNDZ_RADAR_DPY_IND_1;
		DiscInPort KU_ANTENNA_DIRECT_STOW_ON;
		DiscInPort KU_ANTENNA_DEPLOY;
		DiscInPort KU_ANTENNA_STOW;
		DiscInPort cmd_V54K0013N;
		DiscInPort cmd_V54K0003N;
		DiscInPort BOOM_STOW_ENABLE_I;
		DiscInPort BOOM_STOW_ENABLE_II;
		DiscOutPort KU_RNDZ_RADAR_MOTOR_1_PWR;

		// FREON RADIATOR
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_B_LATCH;
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_B_RELEASE;
		DiscOutPort STARBOARD_RAD_LATCH_REL_2;
		DiscOutPort STARBOARD_RAD_LATCH_LAT_2;
		DiscInPort RADIATOR_CONTROL_SYS_A_DEPLOY;
		DiscInPort RADIATOR_CONTROL_SYS_A_STOW;
		DiscInPort STARBOARD_RAD_DEPLOYMENT_DPY_1;
		DiscOutPort RADIATOR_STARBOARD_DPY;
		// stbd sys a deploy motor 2
		DiscInPort STARBOARD_RAD_DEPLOYMENT_DPY_2;
		DiscInPort STARBOARD_RAD_DEPLOYMENT_STO_2;
		DiscOutPort STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR;
		// stbd sys b latch 7-12 motor 2
		DiscInPort STARBOARD_RAD_LATCH_7_12_LAT_2;
		DiscInPort STARBOARD_RAD_LATCH_7_12_REL_2;
		DiscOutPort STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR;

		// REMOTE MANIPULATOR
		// port aft sys 1 retn lch motor 1
		DiscInPort PORT_MRL_LATCH;
		DiscInPort PORT_MRL_RELEASE;
		DiscInPort PORT_AFT_MRL_LATCH_IND_1;
		DiscInPort PORT_AFT_MRL_RELEASE_IND_1;
		DiscOutPort PORT_AFT_MRL_MOTOR_1_PWR;
		DiscOutPort PORT_AFT_MRL_IND_1_PWR;
		DiscOutPort PORT_AFT_RETNN_RFL_1_PWR;
		// stbd mid retn lch motor 2
		DiscInPort STBD_MRL_LATCH;
		DiscInPort STBD_MRL_RELEASE;
		DiscInPort STBD_MID_MRL_LATCH_IND_2;
		DiscInPort STBD_MID_MRL_RELEASE_IND_2;
		DiscOutPort STBD_MID_MRL_MOTOR_2_PWR;
		DiscOutPort STBD_MID_MRL_IND_2_PWR;
		DiscOutPort STBD_MID_RETNN_RFL_2_PWR;

		// VENT DOOR
		// left no 3 motor 2
		DiscInPort LH_VENT_3_MOTOR_2_OPEN_A;
		DiscInPort LH_VENT_3_MOTOR_2_CLOSE_A;
		DiscInPort LH_VENT_3_MOTOR_2_OPEN_B;
		DiscInPort LH_VENT_3_MOTOR_2_CLOSE_B;
		DiscInPort LH_VENT_3_CLOSE_2;
		DiscInPort LH_VENT_3_OPEN_2;
		DiscOutPort LH_VENT_3_MOTOR_2_PWR;

		// PAYLOAD DOORS
		DiscInPort PBD_OPERATION_ENABLE_CMD_3A;
		DiscInPort PBD_OPERATION_ENABLE_CMD_3B;
		// port pdu motor 2
		// stbd aft bkhd latch motor 2
		// cl 13-16 latch motor 2

		// FREON RAD
		// stbd sys b latch 1-6 motor 2
		DiscInPort STARBOARD_RAD_LATCH_1_6_LAT_2;
		DiscInPort STARBOARD_RAD_LATCH_1_6_REL_2;
		DiscOutPort STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR;

		// REMOTE MANIPULATOR
		// stbd deploy motor 1
		DiscInPort STBD_MPM_DEPLOY;
		DiscInPort STBD_MPM_STOW;
		DiscInPort STBD_SHLD_MECH_STOW_IND_1;
		DiscInPort STBD_SHLD_MECH_DEPLOY_IND_1;
		DiscOutPort STBD_MPM_MOTOR_1_PWR;
		// port deploy motor 2
		DiscInPort PORT_MPM_DEPLOY;
		DiscInPort PORT_MPM_STOW;
		DiscInPort PORT_SHLD_MECH_STOW_IND_2;
		DiscInPort PORT_SHLD_MECH_DEPLOY_IND_2;
		DiscOutPort PORT_MPM_MOTOR_2_PWR;
		// stbd aft retn latch motor 2
		DiscInPort STBD_AFT_MRL_LATCH_IND_2;
		DiscInPort STBD_AFT_MRL_RELEASE_IND_2;
		DiscOutPort STBD_AFT_MRL_MOTOR_2_PWR;
		DiscOutPort STBD_AFT_MRL_IND_2_PWR;
		DiscOutPort STBD_AFT_RETNN_RFL_2_PWR;
		// port fwd sys1 retn latch motor 1
		DiscInPort PORT_FWD_MRL_LATCH_IND_1;
		DiscInPort PORT_FWD_MRL_RELEASE_IND_1;
		DiscOutPort PORT_FWD_MRL_MOTOR_1_PWR;
		DiscOutPort PORT_FWD_MRL_IND_1_PWR;
		DiscOutPort PORT_FWD_RETNN_RFL_1_PWR;

	public:
		explicit MMC2( AtlantisSubsystemDirector* _director );
		virtual ~MMC2();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _MMC2_H_
