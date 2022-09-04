/****************************************************************************
  This file is part of Space Shuttle Vessel

  Forward Motor Control Assembly 1 subsystem definition


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
2021/05/30   GLS
2021/06/01   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/25   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Forward Motor Control Assembly 1 definition



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
#ifndef _FMC1_H_
#define _FMC1_H_


#include "AtlantisSubsystem.h"
#include "discsignals.h"


using namespace discsignals;


class FMC1: public AtlantisSubsystem
{
	private:
		// VENT DOORS
		// right 1/2 motor 1
		DiscInPort RH_VENTS_1_2_MOTOR_1_OPEN_A;
		DiscInPort RH_VENTS_1_2_MOTOR_1_CLOSE_A;
		DiscInPort RH_VENTS_1_2_MOTOR_1_PURGE_A;
		DiscInPort RH_VENTS_1_2_MOTOR_1_OPEN_B;
		DiscInPort RH_VENTS_1_2_MOTOR_1_CLOSE_B;
		DiscInPort RH_VENTS_1_2_MOTOR_1_PURGE_B;
		DiscInPort R_VENTS_1_AND_2_CLOSE_1;
		DiscInPort R_VENTS_1_AND_2_OPEN_1;
		DiscInPort R_VENTS_1_AND_2_PURGE_1_IND_1;
		DiscOutPort RH_VENTS_1_AND_2_MOTOR_1_PWR;

		// FWD RCS ISOLATION VALVES MANF 1
		DiscInPort F_MANF_ISOV_NO_1_OP;
		DiscInPort F_MANF_ISOV_NO_1_CL_A;
		DiscInPort F_MANF_ISOV_NO_1_CL_B;
		DiscInPort FWD_RCS_MANIFOLD_ISOLATION_1_SW_OPEN;
		DiscInPort FWD_RCS_MANIFOLD_ISOLATION_1_SW_CLOSE;
		DiscInPort F_FU_MANF_ISOV_1_OP;
		DiscInPort F_FU_MANF_ISOV_1_CL;
		DiscInPort F_OX_MANF_ISOV_1_OP;
		DiscInPort F_OX_MANF_ISOV_1_CL;
		DiscOutPort FWD_RCS_MANIFOLD_ISOLATION_1_TB_OPEN;
		DiscOutPort FWD_RCS_MANIFOLD_ISOLATION_1_TB_CLOSE;
		DiscOutPort F_FU_MANF_ISOV_NO_1_MOTOR_PWR;
		DiscOutPort F_OX_MANF_ISOV_NO_1_MOTOR_PWR;

		// FWD RCS ISOLATION VALVES TANK 3/4/5
		DiscInPort F_FU_TK_ISOV_345_OP_A;
		DiscInPort F_FU_TK_ISOV_345_CL_B;
		DiscInPort F_TK_ISOV_345_CL_A;
		DiscInPort F_OX_TK_ISOV_345_OP_A;
		DiscInPort F_OX_TK_ISOV_345_CL_B;
		DiscInPort FWD_RCS_TANK_ISOLATION_345_SW_OPEN;
		DiscInPort FWD_RCS_TANK_ISOLATION_345_SW_CLOSE;
		DiscInPort F_FU_TK_ISOV_345_OP;
		DiscInPort F_FU_TK_ISOV_345_CL;
		DiscInPort F_OX_TK_ISOV_345_OP;
		DiscInPort F_OX_TK_ISOV_345_CL;
		DiscOutPort FWD_RCS_TANK_ISOLATION_345_TB_OPEN;
		DiscOutPort FWD_RCS_TANK_ISOLATION_345_TB_CLOSE;
		DiscOutPort F_FU_TK_ISOL_345_MOTOR_PWR;
		DiscOutPort F_OX_TK_ISOL_345_MOTOR_PWR;

		// AIR DATA
		DiscInPort AIR_DATA_PROBE_LEFT_DEPLOYHEAT;
		DiscInPort AIR_DATA_PROBE_LEFT_DEPLOY;
		DiscInPort AIR_DATA_PROBE_LEFT_STOW;
		DiscInPort AIR_DATA_PROBE_STOW_LEFT_ENABLE;
		// left probe motor 1
		DiscInPort L_ADP_STOW_1;
		DiscInPort L_ADP_DEPLOY_1;
		DiscOutPort LEFT_PROBE_MOTOR_1_PWR;

		// STAR TRACKER
		DiscInPort STAR_TRACKER_POWER_Y;
		DiscInPort STAR_TRACKER_DOOR_CONTROL_SYS_1_CLOSE;
		DiscInPort STAR_TRACKER_DOOR_CONTROL_SYS_1_OPEN;
		// -y system 1 motor control
		DiscInPort STAR_TRACKER_Y_DOOR_CLS_1;
		DiscInPort STAR_TRACKER_Y_DOOR_OP_1;
		DiscOutPort SYS_1_MOTOR_1_PWR;

	public:
		explicit FMC1( AtlantisSubsystemDirector* _director );
		virtual ~FMC1();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _FMC1_H_
