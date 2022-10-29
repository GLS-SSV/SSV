/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Motor Control Assembly 3 subsystem definition


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
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Mid Motor Control Assembly 3 definition



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
#ifndef _MMC3_H_
#define _MMC3_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class MMC3: public AtlantisSubsystem
{
	private:
		DiscOutPort PORT_MPM_FWD_1_IND_PWR;
		DiscOutPort PORT_MPM_AFT_1_IND_PWR;
		DiscOutPort STBD_MPM_SHOULDER_2_IND_PWR;
		DiscOutPort STBD_MPM_AFT_2_IND_PWR;
		DiscOutPort PORT_MPM_SYSTEM_1_STOW;
		DiscOutPort PORT_MPM_SYSTEM_1_DEPLOY;

		DiscInPort PORT_SHLD_MECH_STOW_IND_1;
		DiscInPort PORT_FWD_MECH_STOW_IND_1;
		DiscInPort PORT_MID_MECH_STOW_IND_1;
		DiscInPort PORT_AFT_MECH_STOW_IND_1;
		DiscInPort PORT_SHLD_MECH_DEPLOY_IND_1;
		DiscInPort PORT_FWD_MECH_DEPLOY_IND_1;
		DiscInPort PORT_MID_MECH_DEPLOY_IND_1;
		DiscInPort PORT_AFT_MECH_DEPLOY_IND_1;

		DiscInPort PL_BAY_MECH_PWR_SYS_2;

		// VENT DOORS
		// right no 4/7 motor 2
		DiscInPort RH_VENTS_4_7_MOTOR_2_OPEN_A;
		DiscInPort RH_VENTS_4_7_MOTOR_2_CLOSE_A;
		DiscInPort RH_VENTS_4_7_MOTOR_2_OPEN_B;
		DiscInPort RH_VENTS_4_7_MOTOR_2_CLOSE_B;
		DiscInPort RH_VENTS_4_AND_7_CLOSE_2;
		DiscInPort RH_VENTS_4_AND_7_OPEN_2;
		DiscOutPort RH_VENTS_4_AND_7_MOTOR_2_PWR;

		// VENT DOORS
		// left no 4/7 motor 1
		DiscInPort LH_VENTS_4_7_MOTOR_1_OPEN_A;
		DiscInPort LH_VENTS_4_7_MOTOR_1_CLOSE_A;
		DiscInPort LH_VENTS_4_7_MOTOR_1_OPEN_B;
		DiscInPort LH_VENTS_4_7_MOTOR_1_CLOSE_B;
		DiscInPort LH_VENTS_4_AND_7_CLOSE_1;
		DiscInPort LH_VENTS_4_AND_7_OPEN_1;
		DiscOutPort LH_VENTS_4_AND_7_MOTOR_1_PWR;
		// left no 5 motor 1
		DiscInPort LH_VENT_5_MOTOR_1_OPEN_A;
		DiscInPort LH_VENT_5_MOTOR_1_CLOSE_A;
		DiscInPort LH_VENT_5_MOTOR_1_OPEN_B;
		DiscInPort LH_VENT_5_MOTOR_1_CLOSE_B;
		DiscInPort LH_VENT_5_CLOSE_1;
		DiscInPort LH_VENT_5_OPEN_1;
		DiscOutPort LH_VENT_5_MOTOR_1_PWR;
		// left no 6 motor 1
		bool K8;
		bool K10;
		bool K14;
		bool K16;
		DiscInPort LH_VENT_6_MOTOR_1_OPEN_A;
		DiscInPort LH_VENT_6_MOTOR_1_CLOSE_A;
		DiscInPort LH_VENT_6_MOTOR_1_PRG_1_A;
		DiscInPort LH_VENT_6_MOTOR_1_PRG_2_A;
		DiscInPort LH_VENT_6_MOTOR_1_OPEN_B;
		DiscInPort LH_VENT_6_MOTOR_1_CLOSE_B;
		DiscInPort LH_VENT_6_MOTOR_1_PRG_1_B;
		DiscInPort LH_VENT_6_MOTOR_1_PRG_2_B;
		DiscInPort LH_VENT_6_CLOSE_1;
		DiscInPort LH_VENT_6_OPEN_1;
		DiscInPort LH_VENT_6_PURGE_1_IND_1;
		DiscInPort LH_VENT_6_PURGE_2_IND_1;
		DiscOutPort LH_VENT_6_MOTOR_1_PWR;

		// PAYLOAD BAY DOORS
		// port aft bkhd latch motor 1
		// cl latch 1-4 motor 1
		// cl latch 5-8 motor 1

		// FREON RADIATOR
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_A_LATCH;
		DiscInPort RADIATOR_LATCH_CONTROL_SYS_A_RELEASE;
		DiscOutPort STARBOARD_RAD_LATCH_REL_1;
		DiscOutPort STARBOARD_RAD_LATCH_LAT_1;
		DiscInPort RADIATOR_CONTROL_SYS_B_DEPLOY;
		DiscInPort RADIATOR_CONTROL_SYS_B_STOW;
		DiscInPort STARBOARD_RAD_DEPLOYMENT_STO_2;
		DiscOutPort RADIATOR_STARBOARD_STO;
		// stbd sys b deploy motor 1
		DiscInPort STARBOARD_RAD_DEPLOYMENT_DPY_1;
		DiscInPort STARBOARD_RAD_DEPLOYMENT_STO_1;
		DiscOutPort STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR;
		// stbd sys a latch 1-6 motor 1
		DiscInPort STARBOARD_RAD_LATCH_1_6_LAT_1;
		DiscInPort STARBOARD_RAD_LATCH_1_6_REL_1;
		DiscOutPort STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR;
		// stbd sys a latch 7-12 motor 1
		DiscInPort STARBOARD_RAD_LATCH_7_12_LAT_1;
		DiscInPort STARBOARD_RAD_LATCH_7_12_REL_1;
		DiscOutPort STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR;

		// REMOTE MANIPULATOR
		// port aft retn latch motor 2
		DiscInPort PORT_MRL_LATCH;
		DiscInPort PORT_MRL_RELEASE;
		DiscInPort PORT_AFT_MRL_LATCH_IND_2;
		DiscInPort PORT_AFT_MRL_RELEASE_IND_2;
		DiscOutPort PORT_AFT_MRL_MOTOR_2_PWR;
		DiscOutPort PORT_AFT_MRL_IND_2_PWR;
		DiscOutPort PORT_AFT_RETNN_RFL_2_PWR;
		// stbd aft retn latch motor 1
		DiscInPort STBD_MRL_LATCH;
		DiscInPort STBD_MRL_RELEASE;
		DiscInPort STBD_AFT_MRL_LATCH_IND_1;
		DiscInPort STBD_AFT_MRL_RELEASE_IND_1;
		DiscOutPort STBD_AFT_MRL_MOTOR_1_PWR;
		DiscOutPort STBD_AFT_MRL_IND_1_PWR;
		DiscOutPort STBD_AFT_RETNN_RFL_1_PWR;

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
		DiscInPort LOGIC_POWER_SYS_1B;
		// latch 1a
		DiscInPort PL_1_SEL_1B_LAT;
		DiscInPort PL_1_SEL_1B_REL;
		DiscOutPort PL_1_SEL_1_MOTOR_2_PWR;
		// latch 2a
		DiscInPort PL_1_SEL_2B_LAT;
		DiscInPort PL_1_SEL_2B_REL;
		DiscOutPort PL_1_SEL_2_MOTOR_2_PWR;
		// latch 3a
		DiscInPort PL_1_SEL_3B_LAT;
		DiscInPort PL_1_SEL_3B_REL;
		DiscOutPort PL_1_SEL_3_MOTOR_2_PWR;
		// latch 4a
		DiscInPort PL_1_SEL_4B_LAT;
		DiscInPort PL_1_SEL_4B_REL;
		DiscOutPort PL_1_SEL_4_MOTOR_2_PWR;
		// latch 5a
		DiscInPort PL_1_SEL_5B_LAT;
		DiscInPort PL_1_SEL_5B_REL;
		DiscOutPort PL_1_SEL_5_MOTOR_2_PWR;

		// pl select pos 2 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_2B;
		// latch 1a
		DiscInPort PL_2_SEL_1B_LAT;
		DiscInPort PL_2_SEL_1B_REL;
		DiscOutPort PL_2_SEL_1_MOTOR_2_PWR;
		// latch 2a
		DiscInPort PL_2_SEL_2B_LAT;
		DiscInPort PL_2_SEL_2B_REL;
		DiscOutPort PL_2_SEL_2_MOTOR_2_PWR;
		// latch 3a
		DiscInPort PL_2_SEL_3B_LAT;
		DiscInPort PL_2_SEL_3B_REL;
		DiscOutPort PL_2_SEL_3_MOTOR_2_PWR;
		// latch 4a
		DiscInPort PL_2_SEL_4B_LAT;
		DiscInPort PL_2_SEL_4B_REL;
		DiscOutPort PL_2_SEL_4_MOTOR_2_PWR;
		// latch 5a
		DiscInPort PL_2_SEL_5B_LAT;
		DiscInPort PL_2_SEL_5B_REL;
		DiscOutPort PL_2_SEL_5_MOTOR_2_PWR;

		// pl select pos 3 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_3B;
		// latch 1a
		DiscInPort PL_3_SEL_1B_LAT;
		DiscInPort PL_3_SEL_1B_REL;
		DiscOutPort PL_3_SEL_1_MOTOR_2_PWR;
		// latch 2a
		DiscInPort PL_3_SEL_2B_LAT;
		DiscInPort PL_3_SEL_2B_REL;
		DiscOutPort PL_3_SEL_2_MOTOR_2_PWR;
		// latch 3a
		DiscInPort PL_3_SEL_3B_LAT;
		DiscInPort PL_3_SEL_3B_REL;
		DiscOutPort PL_3_SEL_3_MOTOR_2_PWR;
		// latch 4a
		DiscInPort PL_3_SEL_4B_LAT;
		DiscInPort PL_3_SEL_4B_REL;
		DiscOutPort PL_3_SEL_4_MOTOR_2_PWR;
		// latch 5a
		DiscInPort PL_3_SEL_5B_LAT;
		DiscInPort PL_3_SEL_5B_REL;
		DiscOutPort PL_3_SEL_5_MOTOR_2_PWR;

	public:
		explicit MMC3( AtlantisSubsystemDirector* _director );
		virtual ~MMC3();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _MMC3_H_
