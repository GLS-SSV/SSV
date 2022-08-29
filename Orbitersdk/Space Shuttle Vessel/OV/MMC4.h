/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Motor Control Assembly 4 subsystem definition


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
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Mid Motor Control Assembly 4 definition



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
#ifndef _MMC4_H_
#define _MMC4_H_


#include "AtlantisSubsystem.h"
#include "discsignals.h"


using namespace discsignals;


class MMC4: public AtlantisSubsystem
{
	private:
		DiscOutPort PORT_MPM_SHOULDER_2_IND_PWR;
		DiscOutPort PORT_MPM_AFT_2_IND_PWR;
		DiscOutPort STBD_MPM_FWD_1_IND_PWR;
		DiscOutPort STBD_MPM_AFT_1_IND_PWR;
		DiscOutPort STBD_MPM_SYSTEM_1_STOW;
		DiscOutPort STBD_MPM_SYSTEM_1_DEPLOY;

		DiscInPort STBD_SHLD_MECH_STOW_IND_1;
		DiscInPort STBD_FWD_MECH_STOW_IND_1;
		DiscInPort STBD_MID_MECH_STOW_IND_1;
		DiscInPort STBD_AFT_MECH_STOW_IND_1;
		DiscInPort STBD_SHLD_MECH_DEPLOY_IND_1;
		DiscInPort STBD_FWD_MECH_DEPLOY_IND_1;
		DiscInPort STBD_MID_MECH_DEPLOY_IND_1;
		DiscInPort STBD_AFT_MECH_DEPLOY_IND_1;

		DiscOutPort STBD_MRL_LATCHED;
		DiscOutPort STBD_MRL_RELEASED;
		DiscInPort STBD_AFT_MRL_LATCH_IND_1;
		DiscInPort STBD_AFT_MRL_RELEASE_IND_1;

		DiscInPort PL_BAY_MECH_PWR_SYS_2;

		// VENT DOORS
		// left no 4/7 motor 2
		DiscInPort LH_VENTS_4_7_MOTOR_2_OPEN_A;
		DiscInPort LH_VENTS_4_7_MOTOR_2_CLOSE_A;
		DiscInPort LH_VENTS_4_7_MOTOR_2_OPEN_B;
		DiscInPort LH_VENTS_4_7_MOTOR_2_CLOSE_B;
		DiscInPort LH_VENTS_4_AND_7_CLOSE_2;
		DiscInPort LH_VENTS_4_AND_7_OPEN_2;
		DiscOutPort LH_VENTS_4_AND_7_MOTOR_2_PWR;
		// right no 6 motor 2
		bool K19;
		bool K17;
		bool K7;
		bool K5;
		DiscInPort RH_VENT_6_MOTOR_2_OPEN_A;
		DiscInPort RH_VENT_6_MOTOR_2_CLOSE_A;
		DiscInPort RH_VENT_6_MOTOR_2_PRG_1_A;
		DiscInPort RH_VENT_6_MOTOR_2_PRG_2_A;
		DiscInPort RH_VENT_6_MOTOR_2_OPEN_B;
		DiscInPort RH_VENT_6_MOTOR_2_CLOSE_B;
		DiscInPort RH_VENT_6_MOTOR_2_PRG_1_B;
		DiscInPort RH_VENT_6_MOTOR_2_PRG_2_B;
		DiscInPort RH_VENT_6_CLOSE_2;
		DiscInPort RH_VENT_6_OPEN_2;
		DiscInPort RH_VENT_6_PURGE_1_IND_2;
		DiscInPort RH_VENT_6_PURGE_2_IND_2;
		DiscOutPort RH_VENT_6_MOTOR_2_PWR;

		// PAYLOAD BAY DOORS
		// stbd pdu motor 2
		// port fwd bkhd latch motor 2
		// stbd fwd bkhd latch motor 2

		// KU BAND
		// ant a deploy motor 2
		DiscInPort KU_RNDZ_RADAR_STO_IND_2;
		DiscInPort KU_RNDZ_RADAR_DPY_IND_2;
		DiscInPort KU_ANTENNA_DIRECT_STOW_ON;
		DiscInPort KU_ANTENNA_DEPLOY;
		DiscInPort KU_ANTENNA_STOW;
		DiscInPort cmd_V54K0014N;
		DiscInPort cmd_V54K0004N;
		DiscInPort BOOM_STOW_ENABLE_I;
		DiscInPort BOOM_STOW_ENABLE_II;
		DiscOutPort KU_RNDZ_RADAR_MOTOR_2_PWR;

		// FREON RAD
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_B_LATCH;
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_B_RELEASE;
		// port sys b latch 1-6 motor 2
		DiscInPort PORT_RAD_LATCH_1_6_LAT_2;
		DiscInPort PORT_RAD_LATCH_1_6_REL_2;
		DiscOutPort PORT_RAD_LATCH_1_6_MOTOR_2_PWR;

		// REMOTE MANIPULATOR
		// port mid retn latch motor 2
		DiscInPort PORT_MRL_LATCH;
		DiscInPort PORT_MRL_RELEASE;
		DiscInPort PORT_MID_MRL_LATCH_IND_2;
		DiscInPort PORT_MID_MRL_RELEASE_IND_2;
		DiscOutPort PORT_MID_MRL_MOTOR_2_PWR;
		DiscOutPort PORT_MID_MRL_IND_2_PWR;
		DiscOutPort PORT_MID_RETNN_RFL_2_PWR;
		// stbd mid retn latch motor 1
		DiscInPort STBD_MRL_LATCH;
		DiscInPort STBD_MRL_RELEASE;
		DiscInPort STBD_MID_MRL_LATCH_IND_1;
		DiscInPort STBD_MID_MRL_RELEASE_IND_1;
		DiscOutPort STBD_MID_MRL_MOTOR_1_PWR;
		DiscOutPort STBD_MID_MRL_IND_1_PWR;
		DiscOutPort STBD_MID_RETNN_RFL_1_PWR;

		// VENT DOORS
		// right no 3 motor 2
		DiscInPort RH_VENT_3_MOTOR_2_OPEN_A;
		DiscInPort RH_VENT_3_MOTOR_2_CLOSE_A;
		DiscInPort RH_VENT_3_MOTOR_2_OPEN_B;
		DiscInPort RH_VENT_3_MOTOR_2_CLOSE_B;
		DiscInPort RH_VENT_3_CLOSE_2;
		DiscInPort RH_VENT_3_OPEN_2;
		DiscOutPort RH_VENT_3_MOTOR_2_PWR;
		// right no 5 motor 2
		DiscInPort RH_VENT_5_MOTOR_2_OPEN_A;
		DiscInPort RH_VENT_5_MOTOR_2_CLOSE_A;
		DiscInPort RH_VENT_5_MOTOR_2_OPEN_B;
		DiscInPort RH_VENT_5_MOTOR_2_CLOSE_B;
		DiscInPort RH_VENT_5_CLOSE_2;
		DiscInPort RH_VENT_5_OPEN_2;
		DiscOutPort RH_VENT_5_MOTOR_2_PWR;

		// PAYLOAD BAY DOORS
		// port pdu motor 1
		// stbd aft bkhd latch motor 1
		// cl 9-12 latch motor 2
		// cl 13-16 latch motor 1

		// FREON RADIATOR
		DiscOutPort PORT_RAD_LATCH_REL_2;
		DiscOutPort PORT_RAD_LATCH_LAT_2;
		DiscInPort RADIATOR_CONTROL_SYS_B_DEPLOY;
		DiscInPort RADIATOR_CONTROL_SYS_B_STOW;
		DiscInPort PORT_RAD_DEPLOYMENT_DPY_1;
		DiscOutPort RADIATOR_PORT_DPY;
		// port sys b deploy motor 2
		DiscInPort PORT_RAD_DEPLOYMENT_DPY_2;
		DiscInPort PORT_RAD_DEPLOYMENT_STO_2;
		DiscOutPort PORT_RAD_DEPLOYMENT_MOTOR_2_PWR;
		// port sys b latch 7-12 motor 2
		DiscInPort PORT_RAD_LATCH_7_12_LAT_2;
		DiscInPort PORT_RAD_LATCH_7_12_REL_2;
		DiscOutPort PORT_RAD_LATCH_7_12_MOTOR_2_PWR;

		// REMOTE MANIPULATOR
		// port deploy motor 1
		DiscInPort PORT_MPM_DEPLOY;
		DiscInPort PORT_MPM_STOW;
		DiscInPort PORT_SHLD_MECH_STOW_IND_1;
		DiscInPort PORT_SHLD_MECH_DEPLOY_IND_1;
		DiscOutPort PORT_MPM_MOTOR_1_PWR;
		// stbd deploy motor 2
		DiscInPort STBD_MPM_DEPLOY;
		DiscInPort STBD_MPM_STOW;
		DiscInPort STBD_SHLD_MECH_STOW_IND_2;
		DiscInPort STBD_SHLD_MECH_DEPLOY_IND_2;
		DiscOutPort STBD_MPM_MOTOR_2_PWR;
		// port fwd retn latch motor 2
		DiscInPort PORT_FWD_MRL_LATCH_IND_2;
		DiscInPort PORT_FWD_MRL_RELEASE_IND_2;
		DiscOutPort PORT_FWD_MRL_MOTOR_2_PWR;
		DiscOutPort PORT_FWD_MRL_IND_2_PWR;
		DiscOutPort PORT_FWD_RETNN_RFL_2_PWR;
		// stbd fwd retn latch motor 1
		DiscInPort STBD_FWD_MRL_LATCH_IND_1;
		DiscInPort STBD_FWD_MRL_RELEASE_IND_1;
		DiscOutPort STBD_FWD_MRL_MOTOR_1_PWR;
		DiscOutPort STBD_FWD_MRL_IND_1_PWR;
		DiscOutPort STBD_FWD_RETNN_RFL_1_PWR;

	public:
		explicit MMC4( AtlantisSubsystemDirector* _director );
		virtual ~MMC4();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _MMC4_H_
