/****************************************************************************
  This file is part of Space Shuttle Vessel

  Aft Motor Control Assembly 1 subsystem definition


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
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Aft Motor Control Assembly 1 definition



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
#ifndef _AMC1_H_
#define _AMC1_H_


#include "AtlantisSubsystem.h"
#include "discsignals.h"


using namespace discsignals;


class AMC1: public AtlantisSubsystem
{
	private:
		// ET UMBILICAL DOORS
		DiscInPort ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_CLOSE;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_OPEN;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH;
		DiscInPort ET_DR_CLS_AND_LAT_ARM_1_FA1;
		DiscInPort ET_DR_CLS_AND_LAT_ARM_1_FA3;
		// left drive motor 1
		DiscInPort L_DOOR_CL_1_FA4;
		DiscInPort L_DOOR_CL_1_FA2;
		DiscInPort LEFT_DOOR_CLOSE_1;
		DiscInPort LEFT_DOOR_OPEN_1;
		DiscOutPort LEFT_DOOR_MOTOR_1_PWR;
		// left latch motor 1
		DiscInPort L_LATCH_A1_FA2;
		DiscInPort L_LATCH_A1_FA1;
		DiscInPort L_LATCH_B1_FA3;
		DiscInPort L_LATCH_B1_FA4;
		DiscInPort LEFT_DOOR_LATCH_REL_1;
		DiscInPort LEFT_DOOR_LATCH_LAT_1;
		DiscInPort LEFT_DOOR_RDY_TO_LCH_1;
		DiscOutPort LEFT_DOOR_LATCH_MOTOR_1_PWR;
		// cl latch 1 motor 1
		DiscInPort CL_1_STOW_A1_FA3;
		DiscInPort CL_1_STOW_A1_FA4;
		DiscInPort CL_1_STOW_B1_FA2;
		DiscInPort CL_1_STOW_B1_FA1;
		DiscInPort CL_1_DEPLOY_A1_FA2;
		DiscInPort CL_1_DEPLOY_A1_FA1;
		DiscInPort CL_1_DEPLOY_B1_FA3;
		DiscInPort CL_1_DEPLOY_B1_FA4;
		DiscInPort CL_LATCH_1_STOW_1;
		DiscInPort CL_LATCH_1_DEPLOY_1;
		DiscOutPort CL_1_MOTOR_1_PWR;
		// cl latch 2 motor 1
		DiscInPort CL_2_STOW_A1_FA3;
		DiscInPort CL_2_STOW_A1_FA1;
		DiscInPort CL_2_STOW_B1_FA2;
		DiscInPort CL_2_STOW_B1_FA4;
		DiscInPort CL_2_DEPLOY_A1_FA2;
		DiscInPort CL_2_DEPLOY_A1_FA4;
		DiscInPort CL_2_DEPLOY_B1_FA3;
		DiscInPort CL_2_DEPLOY_B1_FA1;
		DiscInPort CL_LATCH_2_STOW_1;
		DiscInPort CL_LATCH_2_DEPLOY_1;
		DiscOutPort CL_2_MOTOR_1_PWR;

		// AFT RCS ISOLATION VALVES MANIFOLD 2
		DiscInPort R_MANF_ISOV_NO_2_OP;
		DiscInPort R_MANF_ISOV_NO_2_CL_A;
		DiscInPort R_MANF_ISOV_NO_2_CL_B;
		DiscInPort L_MANF_ISOV_NO_2_OP;
		DiscInPort L_MANF_ISOV_NO_2_CL_A;
		DiscInPort L_MANF_ISOV_NO_2_CL_B;
		DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE;
		DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_SW_CLOSE;
		DiscInPort R_FU_MANF_ISOV_2_OP;
		DiscInPort R_FU_MANF_ISOV_2_CL;
		DiscInPort R_OX_MANF_ISOV_2_OP;
		DiscInPort R_OX_MANF_ISOV_2_CL;
		DiscInPort L_FU_MANF_ISOV_2_OP;
		DiscInPort L_FU_MANF_ISOV_2_CL;
		DiscInPort L_OX_MANF_ISOV_2_OP;
		DiscInPort L_OX_MANF_ISOV_2_CL;
		DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE;
		DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_2_TB_CLOSE;
		DiscOutPort R_FU_MANF_ISOV_NO_2_MOTOR_PWR;
		DiscOutPort R_OX_MANF_ISOV_NO_2_MOTOR_PWR;
		DiscOutPort L_FU_MANF_ISOV_NO_2_MOTOR_PWR;
		DiscOutPort L_OX_MANF_ISOV_NO_2_MOTOR_PWR;

		// AFT RCS ISOLATION VALVES TANK 3/4/5A
		DiscInPort R_OX_TK_ISOV_345_A_OP;
		DiscInPort R_OX_TK_ISOV_345_A_CL;
		DiscInPort R_FU_TK_ISOV_345_A_OP;
		DiscInPort R_FU_TK_ISOV_345_A_CL;
		DiscInPort L_OX_TK_ISOV_345_A_OP;
		DiscInPort L_OX_TK_ISOV_345_A_CL;
		DiscInPort L_FU_TK_ISOV_345_A_OP;
		DiscInPort L_FU_TK_ISOV_345_A_CL;
		DiscInPort AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_TANK_ISOLATION_345_A_SW_CLOSE;
		DiscInPort AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_TANK_ISOLATION_345_A_SW_CLOSE;
		DiscInPort R_FU_TK_ISO_V_345_A_OP;
		DiscInPort R_FU_TK_ISO_V_345_A_CL;
		DiscInPort R_OX_TK_ISO_V_345_A_OP;
		DiscInPort R_OX_TK_ISO_V_345_A_CL;
		DiscInPort L_FU_TK_ISO_V_345_A_OP;
		DiscInPort L_FU_TK_ISO_V_345_A_CL;
		DiscInPort L_OX_TK_ISO_V_345_A_OP;
		DiscInPort L_OX_TK_ISO_V_345_A_CL;
		DiscOutPort AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_TANK_ISOLATION_345_A_TB_CLOSE;
		DiscOutPort AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_TANK_ISOLATION_345_A_TB_CLOSE;
		DiscOutPort R_FU_TK_ISOL_345_A_MOTOR_PWR;
		DiscOutPort R_OX_TK_ISOL_345_A_MOTOR_PWR;
		DiscOutPort L_FU_TK_ISOL_345_A_MOTOR_PWR;
		DiscOutPort L_OX_TK_ISOL_345_A_MOTOR_PWR;

		// RIGHT RCS XFEED MANIFOLD 3/4/5
		DiscInPort R_RCS_FU_XFD_345_OP;
		DiscInPort R_RCS_FU_XFD_345_CL;
		DiscInPort R_RCS_OX_XFD_345_OP;
		DiscInPort R_RCS_OX_XFD_345_CL;
		DiscInPort R_RCS_XFD_345_OP;
		DiscInPort R_RCS_XFD_345_CL;
		DiscInPort AFT_RIGHT_RCS_CROSSFEED_345_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_CROSSFEED_345_SW_CLOSE;
		DiscInPort R_RCS_FU_XFD_345_OP_1;
		DiscInPort R_RCS_FU_XFD_345_CL_1;
		DiscInPort R_RCS_OX_XFD_345_OP_1;
		DiscInPort R_RCS_OX_XFD_345_CL_1;
		DiscInPort R_RCS_FU_XFD_345_OP_2;
		DiscInPort R_RCS_FU_XFD_345_CL_2;
		DiscInPort R_RCS_OX_XFD_345_OP_2;
		DiscInPort R_RCS_OX_XFD_345_CL_2;
		DiscOutPort AFT_RIGHT_RCS_CROSSFEED_345_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_CROSSFEED_345_TB_CLOSE;
		DiscOutPort R_RCS_FU_XFD_V_345_MOTOR_PWR;
		DiscOutPort R_RCS_OX_XFD_V_345_MOTOR_PWR;

		// LEFT RCS XFEED MANIFOLD 3/4/5
		DiscInPort L_RCS_FU_XFD_345_OP;
		DiscInPort L_RCS_FU_XFD_345_CL;
		DiscInPort L_RCS_OX_XFD_345_OP;
		DiscInPort L_RCS_OX_XFD_345_CL;
		DiscInPort L_RCS_XFD_345_OP;
		DiscInPort L_RCS_XFD_345_CL;
		DiscInPort AFT_LEFT_RCS_CROSSFEED_345_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_CROSSFEED_345_SW_CLOSE;
		DiscInPort L_RCS_FU_XFD_345_OP_1;
		DiscInPort L_RCS_FU_XFD_345_CL_1;
		DiscInPort L_RCS_OX_XFD_345_OP_1;
		DiscInPort L_RCS_OX_XFD_345_CL_1;
		DiscInPort L_RCS_FU_XFD_345_OP_2;
		DiscInPort L_RCS_FU_XFD_345_CL_2;
		DiscInPort L_RCS_OX_XFD_345_OP_2;
		DiscInPort L_RCS_OX_XFD_345_CL_2;
		DiscOutPort AFT_LEFT_RCS_CROSSFEED_345_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_CROSSFEED_345_TB_CLOSE;
		DiscOutPort L_RCS_FU_XFD_V_345_MOTOR_PWR;
		DiscOutPort L_RCS_OX_XFD_V_345_MOTOR_PWR;

		// LEFT OMS XFEED
		DiscInPort L_OMS_FU_XFD_V_A_OP;
		DiscInPort L_OMS_FU_XFD_V_A_CL;
		DiscInPort L_OMS_OX_XFD_V_A_OP;
		DiscInPort L_OMS_OX_XFD_V_A_CL;
		DiscInPort L_OMS_XFD_A_OP;
		DiscInPort L_OMS_XFD_A_CL;
		DiscInPort LEFT_OMS_CROSSFEED_A_SW_OPEN;
		DiscInPort LEFT_OMS_CROSSFEED_A_SW_CLOSE;
		DiscInPort L_OMS_FU_XFD_V_A_OP_1;
		DiscInPort L_OMS_FU_XFD_V_A_CL_1;
		DiscInPort L_OMS_OX_XFD_V_A_OP_1;
		DiscInPort L_OMS_OX_XFD_V_A_CL_1;
		DiscInPort L_OMS_FU_XFD_V_A_OP_2;
		DiscInPort L_OMS_FU_XFD_V_A_CL_2;
		DiscInPort L_OMS_OX_XFD_V_A_OP_2;
		DiscInPort L_OMS_OX_XFD_V_A_CL_2;
		DiscOutPort LEFT_OMS_CROSSFEED_A_TB_OPEN;
		DiscOutPort LEFT_OMS_CROSSFEED_A_TB_CLOSE;
		DiscOutPort L_OMS_FU_XFD_V_A_MOTOR_PWR;
		DiscOutPort L_OMS_OX_XFD_V_A_MOTOR_PWR;

		// OMS ISOLATION VALVES
		DiscInPort L_OMS_FU_TK_ISOV_A_OP;
		DiscInPort L_OMS_FU_TK_ISOV_A_CL;
		DiscInPort L_OMS_OX_TK_ISOV_A_OP;
		DiscInPort L_OMS_OX_TK_ISOV_A_CL;
		DiscInPort L_OMS_TK_V_A_OP;
		DiscInPort L_OMS_TK_V_A_CL;
		DiscInPort LEFT_OMS_TANK_ISOLATION_A_SW_OPEN;
		DiscInPort LEFT_OMS_TANK_ISOLATION_A_SW_CLOSE;
		DiscInPort L_OMS_FU_TK_ISOV_A_OP_1;
		DiscInPort L_OMS_FU_TK_ISOV_A_CL_1;
		DiscInPort L_OMS_OX_TK_ISOV_A_OP_1;
		DiscInPort L_OMS_OX_TK_ISOV_A_CL_1;
		DiscInPort L_OMS_FU_TK_ISOV_A_OP_2;
		DiscInPort L_OMS_FU_TK_ISOV_A_CL_2;
		DiscInPort L_OMS_OX_TK_ISOV_A_OP_2;
		DiscInPort L_OMS_OX_TK_ISOV_A_CL_2;
		DiscOutPort LEFT_OMS_TANK_ISOLATION_A_TB_OPEN;
		DiscOutPort LEFT_OMS_TANK_ISOLATION_A_TB_CLOSE;
		DiscOutPort L_OMS_FU_TK_ISOV_A_MOTOR_PWR;
		DiscOutPort L_OMS_OX_TK_ISOV_A_MOTOR_PWR;
		DiscInPort R_OMS_FU_TK_ISOV_A_OP;
		DiscInPort R_OMS_FU_TK_ISOV_A_CL;
		DiscInPort R_OMS_OX_TK_ISOV_A_OP;
		DiscInPort R_OMS_OX_TK_ISOV_A_CL;
		DiscInPort R_OMS_TK_V_A_OP;
		DiscInPort R_OMS_TK_V_A_CL;
		DiscInPort RIGHT_OMS_TANK_ISOLATION_A_SW_OPEN;
		DiscInPort RIGHT_OMS_TANK_ISOLATION_A_SW_CLOSE;
		DiscInPort R_OMS_FU_TK_ISOV_A_OP_1;
		DiscInPort R_OMS_FU_TK_ISOV_A_CL_1;
		DiscInPort R_OMS_OX_TK_ISOV_A_OP_1;
		DiscInPort R_OMS_OX_TK_ISOV_A_CL_1;
		DiscInPort R_OMS_FU_TK_ISOV_A_OP_2;
		DiscInPort R_OMS_FU_TK_ISOV_A_CL_2;
		DiscInPort R_OMS_OX_TK_ISOV_A_OP_2;
		DiscInPort R_OMS_OX_TK_ISOV_A_CL_2;
		DiscOutPort RIGHT_OMS_TANK_ISOLATION_A_TB_OPEN;
		DiscOutPort RIGHT_OMS_TANK_ISOLATION_A_TB_CLOSE;
		DiscOutPort R_OMS_FU_TK_ISOV_A_MOTOR_PWR;
		DiscOutPort R_OMS_OX_TK_ISOV_A_MOTOR_PWR;

	public:
		explicit AMC1( AtlantisSubsystemDirector* _director );
		virtual ~AMC1();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _AMC1_H_
