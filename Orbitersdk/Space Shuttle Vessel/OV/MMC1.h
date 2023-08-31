/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Motor Control Assembly 1 subsystem definition


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
2020/03/20   GLS
2020/06/20   GLS
2020/06/28   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/25   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/05/14   GLS
2022/05/15   GLS
2022/05/16   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/11/01   GLS
2022/11/03   GLS
2022/11/05   GLS
2023/07/23   GLS
2023/07/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Mid Motor Control Assembly 1 definition



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
#ifndef _MMC1_H_
#define _MMC1_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class MMC1: public AtlantisSubsystem
{
	private:
		DiscOutPort MNA_MMC1;
		DiscOutPort MNB_MMC1;

		DiscOutPort PORT_MPM_MID_2_IND_PWR;
		DiscOutPort STBD_MPM_SHOULDER_1_IND_PWR;
		DiscOutPort STBD_MPM_MID_1_IND_PWR;
		DiscOutPort STBD_MPM_FWD_2_IND_PWR;
		DiscOutPort STBD_MPM_SYSTEM_2_STOW;
		DiscOutPort STBD_MPM_SYSTEM_2_DEPLOY;

		DiscInPort STBD_SHLD_MECH_STOW_IND_2_TB;
		DiscInPort STBD_FWD_MECH_STOW_IND_2_TB;
		DiscInPort STBD_MID_MECH_STOW_IND_2_TB;
		DiscInPort STBD_AFT_MECH_STOW_IND_2_TB;
		DiscInPort STBD_SHLD_MECH_DEPLOY_IND_2_TB;
		DiscInPort STBD_FWD_MECH_DEPLOY_IND_2_TB;
		DiscInPort STBD_MID_MECH_DEPLOY_IND_2_TB;
		DiscInPort STBD_AFT_MECH_DEPLOY_IND_2_TB;

		DiscInPort PL_BAY_MECH_PWR_SYS_1;

		// VENT DOOR
		// left no 5 motor 2
		DiscInPort LH_VENT_5_MOTOR_2_OPEN_A;
		DiscInPort LH_VENT_5_MOTOR_2_CLOSE_A;
		DiscInPort LH_VENT_5_MOTOR_2_OPEN_B;
		DiscInPort LH_VENT_5_MOTOR_2_CLOSE_B;
		DiscInPort LH_VENT_5_CLOSE_2;
		DiscInPort LH_VENT_5_OPEN_2;
		DiscOutPort LH_VENT_5_MOTOR_2_PWR;

		// VENT DOORS
		// right no 3 motor 1
		DiscInPort RH_VENT_3_MOTOR_1_OPEN_A;
		DiscInPort RH_VENT_3_MOTOR_1_CLOSE_A;
		DiscInPort RH_VENT_3_MOTOR_1_OPEN_B;
		DiscInPort RH_VENT_3_MOTOR_1_CLOSE_B;
		DiscInPort RH_VENT_3_CLOSE_1;
		DiscInPort RH_VENT_3_OPEN_1;
		DiscOutPort RH_VENT_3_MOTOR_1_PWR;
		// right no 5 motor 1
		DiscInPort RH_VENT_5_MOTOR_1_OPEN_A;
		DiscInPort RH_VENT_5_MOTOR_1_CLOSE_A;
		DiscInPort RH_VENT_5_MOTOR_1_OPEN_B;
		DiscInPort RH_VENT_5_MOTOR_1_CLOSE_B;
		DiscInPort RH_VENT_5_CLOSE_1;
		DiscInPort RH_VENT_5_OPEN_1;
		DiscOutPort RH_VENT_5_MOTOR_1_PWR;
		// right no 6 motor 1
		bool K81;
		bool K69;
		bool K83;
		bool K71;
		DiscInPort RH_VENT_6_MOTOR_1_OPEN_A;
		DiscInPort RH_VENT_6_MOTOR_1_CLOSE_A;
		DiscInPort RH_VENT_6_MOTOR_1_PRG_1_A;
		DiscInPort RH_VENT_6_MOTOR_1_PRG_2_A;
		DiscInPort RH_VENT_6_MOTOR_1_OPEN_B;
		DiscInPort RH_VENT_6_MOTOR_1_CLOSE_B;
		DiscInPort RH_VENT_6_MOTOR_1_PRG_1_B;
		DiscInPort RH_VENT_6_MOTOR_1_PRG_2_B;
		DiscInPort RH_VENT_6_CLOSE_1;
		DiscInPort RH_VENT_6_OPEN_1;
		DiscInPort RH_VENT_6_PURGE_1_IND_1;
		DiscInPort RH_VENT_6_PURGE_2_IND_1;
		DiscOutPort RH_VENT_6_MOTOR_1_PWR;

		// PAYLOAD BAY DOORS
		DiscInPort PBD_ENABLE_SYS1;
		DiscInPort PBD_OPERATION_ENABLE_CMD_1A;
		DiscInPort PBD_OPERATION_ENABLE_CMD_1B;
		// stbd pdu motor 1
		DiscInPort STARBOARD_DOOR_POWER_DRIVE_UNIT_OPEN_CMD_1;
		DiscInPort STARBOARD_DOOR_POWER_DRIVE_UNIT_CLOSE_CMD_1;
		DiscInPort STBD_DOOR_OPEN_1;
		DiscInPort STBD_DOOR_CLOSE_1;
		DiscOutPort STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR;
		// port fwd bkhd latch motor 1
		DiscInPort PORT_FWD_BLKHD_LAT_CMD_1;
		DiscInPort PORT_FWD_BLKHD_REL_CMD_1;
		DiscInPort PORT_FWD_BLKHD_LAT_1;
		DiscInPort PORT_FWD_BLKHD_REL_1;
		DiscOutPort BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_1_PWR;
		// stbd fwd bkhd latch motor 1
		DiscInPort STBD_FWD_BLKHD_LAT_CMD_1;
		DiscInPort STBD_FWD_BLKHD_REL_CMD_1;
		DiscInPort STBD_FWD_BLKHD_LAT_1;
		DiscInPort STBD_FWD_BLKHD_REL_1;
		DiscOutPort BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_1_PWR;
		// cl latch 9-12 motor 1
		DiscInPort LAT_9_12_LAT_CMD_1;
		DiscInPort LAT_9_12_REL_CMD_1;
		DiscInPort LAT_9_12_LAT_1;
		DiscInPort LAT_9_12_REL_1;
		DiscOutPort CENTERLINE_ACTUATOR_9_12_MOTOR_1_PWR;

		// FREON RADIATOR
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_A_LATCH;
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_A_RELEASE;
		DiscOutPort PORT_RAD_LATCH_REL_1;
		DiscOutPort PORT_RAD_LATCH_LAT_1;
		DiscInPort RADIATOR_CONTROL_SYS_A_DEPLOY;
		DiscInPort RADIATOR_CONTROL_SYS_A_STOW;
		DiscInPort PORT_RAD_DEPLOYMENT_STO_2;
		DiscOutPort RADIATOR_PORT_STO;
		// port sys a deploy motor 1
		DiscInPort PORT_RAD_DEPLOYMENT_DPY_1;
		DiscInPort PORT_RAD_DEPLOYMENT_STO_1;
		DiscOutPort PORT_RAD_DEPLOYMENT_MOTOR_1_PWR;
		// port sys a latch 1-6 motor 1
		DiscInPort PORT_RAD_LATCH_1_6_LAT_1;
		DiscInPort PORT_RAD_LATCH_1_6_REL_1;
		DiscOutPort PORT_RAD_LATCH_1_6_MOTOR_1_PWR;
		// port sys a latch 7-12 motor 1
		DiscInPort PORT_RAD_LATCH_7_12_LAT_1;
		DiscInPort PORT_RAD_LATCH_7_12_REL_1;
		DiscOutPort PORT_RAD_LATCH_7_12_MOTOR_1_PWR;

		// REMOTE MANIPULATOR
		// port mid retn latch motor 1
		DiscInPort PORT_MRL_LATCH;
		DiscInPort PORT_MRL_RELEASE;
		DiscInPort PORT_MID_MRL_LATCH_IND_1;
		DiscInPort PORT_MID_MRL_RELEASE_IND_1;
		DiscOutPort PORT_MID_MRL_MOTOR_1_PWR;
		DiscOutPort PORT_MID_MRL_IND_1_PWR;
		DiscOutPort PORT_MID_RETNN_RFL_1_PWR;
		// stbd fwd retn latch motor 2
		DiscInPort STBD_MRL_LATCH;
		DiscInPort STBD_MRL_RELEASE;
		DiscInPort STBD_FWD_MRL_LATCH_IND_2;
		DiscInPort STBD_FWD_MRL_RELEASE_IND_2;
		DiscOutPort STBD_FWD_MRL_MOTOR_2_PWR;
		DiscOutPort STBD_FWD_MRL_IND_2_PWR;
		DiscOutPort STBD_FWD_RETNN_RFL_2_PWR;

		// PAYLOAD RETENTION
		DiscInPort PL_RETENTION_1_RELEASE;
		DiscInPort PL_RETENTION_1_LATCH;
		DiscInPort PL_RETENTION_2_RELEASE;
		DiscInPort PL_RETENTION_2_LATCH;
		DiscInPort PL_RETENTION_3_RELEASE;
		DiscInPort PL_RETENTION_3_LATCH;
		DiscInPort PL_RETENTION_4_RELEASE;
		DiscInPort PL_RETENTION_4_LATCH;
		DiscInPort PL_RETENTION_5_RELEASE;
		DiscInPort PL_RETENTION_5_LATCH;

		// pl select pos 1 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_1A;
		// latch 1a
		DiscInPort PL_1_SEL_1A_LAT;
		DiscInPort PL_1_SEL_1A_REL;
		DiscOutPort PL_1_SEL_1_MOTOR_1_PWR;
		// latch 2a
		DiscInPort PL_1_SEL_2A_LAT;
		DiscInPort PL_1_SEL_2A_REL;
		DiscOutPort PL_1_SEL_2_MOTOR_1_PWR;
		// latch 3a
		DiscInPort PL_1_SEL_3A_LAT;
		DiscInPort PL_1_SEL_3A_REL;
		DiscOutPort PL_1_SEL_3_MOTOR_1_PWR;
		// latch 4a
		DiscInPort PL_1_SEL_4A_LAT;
		DiscInPort PL_1_SEL_4A_REL;
		DiscOutPort PL_1_SEL_4_MOTOR_1_PWR;
		// latch 5a
		DiscInPort PL_1_SEL_5A_LAT;
		DiscInPort PL_1_SEL_5A_REL;
		DiscOutPort PL_1_SEL_5_MOTOR_1_PWR;

		// pl select pos 2 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_2A;
		// latch 1a
		DiscInPort PL_2_SEL_1A_LAT;
		DiscInPort PL_2_SEL_1A_REL;
		DiscOutPort PL_2_SEL_1_MOTOR_1_PWR;
		// latch 2a
		DiscInPort PL_2_SEL_2A_LAT;
		DiscInPort PL_2_SEL_2A_REL;
		DiscOutPort PL_2_SEL_2_MOTOR_1_PWR;
		// latch 3a
		DiscInPort PL_2_SEL_3A_LAT;
		DiscInPort PL_2_SEL_3A_REL;
		DiscOutPort PL_2_SEL_3_MOTOR_1_PWR;
		// latch 4a
		DiscInPort PL_2_SEL_4A_LAT;
		DiscInPort PL_2_SEL_4A_REL;
		DiscOutPort PL_2_SEL_4_MOTOR_1_PWR;
		// latch 5a
		DiscInPort PL_2_SEL_5A_LAT;
		DiscInPort PL_2_SEL_5A_REL;
		DiscOutPort PL_2_SEL_5_MOTOR_1_PWR;

		// pl select pos 3 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_3A;
		// latch 1a
		DiscInPort PL_3_SEL_1A_LAT;
		DiscInPort PL_3_SEL_1A_REL;
		DiscOutPort PL_3_SEL_1_MOTOR_1_PWR;
		// latch 2a
		DiscInPort PL_3_SEL_2A_LAT;
		DiscInPort PL_3_SEL_2A_REL;
		DiscOutPort PL_3_SEL_2_MOTOR_1_PWR;
		// latch 3a
		DiscInPort PL_3_SEL_3A_LAT;
		DiscInPort PL_3_SEL_3A_REL;
		DiscOutPort PL_3_SEL_3_MOTOR_1_PWR;
		// latch 4a
		DiscInPort PL_3_SEL_4A_LAT;
		DiscInPort PL_3_SEL_4A_REL;
		DiscOutPort PL_3_SEL_4_MOTOR_1_PWR;
		// latch 5a
		DiscInPort PL_3_SEL_5A_LAT;
		DiscInPort PL_3_SEL_5A_REL;
		DiscOutPort PL_3_SEL_5_MOTOR_1_PWR;

		DiscOutPort OPER_STATUS_1;
		DiscOutPort OPER_STATUS_2;
		DiscOutPort OPER_STATUS_3;
		DiscOutPort OPER_STATUS_4;
		DiscOutPort OPER_STATUS_5;
		DiscOutPort OPER_STATUS_6;
		DiscOutPort OPER_STATUS_7;
		DiscOutPort OPER_STATUS_8;

	public:
		explicit MMC1( AtlantisSubsystemDirector* _director );
		virtual ~MMC1();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _MMC1_H_
