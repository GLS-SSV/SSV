/****************************************************************************
  This file is part of Space Shuttle Vessel

  Aft Motor Control Assembly 3 subsystem definition


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
2022/01/25   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Aft Motor Control Assembly 3 definition



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
#ifndef _AMC3_H_
#define _AMC3_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class AMC3: public AtlantisSubsystem
{
	private:
		// VENT DOORS
		// right 8/9 motor 1
		DiscInPort RH_VENTS_8_9_MOTOR_1_OPEN_A;
		DiscInPort RH_VENTS_8_9_MOTOR_1_CLOSE_A;
		DiscInPort RH_VENTS_8_9_MOTOR_1_PURGE_A;
		DiscInPort RH_VENTS_8_9_MOTOR_1_OPEN_B;
		DiscInPort RH_VENTS_8_9_MOTOR_1_CLOSE_B;
		DiscInPort RH_VENTS_8_9_MOTOR_1_PURGE_B;
		DiscInPort RH_VENTS_8_AND_9_CLOSE_1;
		DiscInPort RH_VENTS_8_AND_9_OPEN_1;
		DiscInPort RH_VENTS_8_AND_9_PURGE_IND_1;
		DiscOutPort RH_VENTS_8_AND_9_MOTOR_1_PWR;

		// ET UMBILICAL DOORS
		DiscInPort ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_CLOSE;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_OPEN;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_CLOSE;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_OPEN;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH;
		DiscInPort ET_DR_CLS_AND_LAT_ARM_3_FA3;
		DiscInPort ET_DR_CLS_AND_LAT_ARM_3_FA2;
		// left drive motor 2
		DiscInPort L_DOOR_CL_2_FA1;
		DiscInPort L_DOOR_CL_2_FA4;
		DiscInPort LEFT_DOOR_CLOSE_2;
		DiscInPort LEFT_DOOR_OPEN_2;
		DiscOutPort LEFT_DOOR_MOTOR_2_PWR;
		// cl latch 2 motor 2
		DiscInPort CL_2_STOW_A2_FA4;
		DiscInPort CL_2_STOW_A2_FA1;
		DiscInPort CL_2_STOW_B2_FA3;
		DiscInPort CL_2_STOW_B2_FA2;
		DiscInPort CL_2_DEPLOY_A2_FA4;
		DiscInPort CL_2_DEPLOY_A2_FA1;
		DiscInPort CL_2_DEPLOY_B2_FA3;
		DiscInPort CL_2_DEPLOY_B2_FA2;
		DiscInPort CL_LATCH_2_STOW_2;
		DiscInPort CL_LATCH_2_DEPLOY_2;
		DiscOutPort CL_2_MOTOR_2_PWR;
		// right drive motor 1
		DiscInPort R_DOOR_CL_1_FA1;
		DiscInPort R_DOOR_CL_1_FA4;
		DiscInPort RIGHT_DOOR_CLOSE_1;
		DiscInPort RIGHT_DOOR_OPEN_1;
		DiscOutPort RIGHT_DOOR_MOTOR_1_PWR;
		// right latch motor 1
		DiscInPort R_LATCH_A1_FA3;
		DiscInPort R_LATCH_A1_FA1;
		DiscInPort R_LATCH_B1_FA2;
		DiscInPort R_LATCH_B1_FA4;
		DiscInPort RIGHT_DOOR_LATCH_REL_1;
		DiscInPort RIGHT_DOOR_LATCH_LAT_1;
		DiscInPort RIGHT_DOOR_RDY_TO_LCH_1;
		DiscOutPort RIGHT_DOOR_LATCH_MOTOR_1_PWR;

		// AFT RCS ISOLATION VALVES TANK 1/2
		DiscInPort L_FU_TK_ISOV_12_OP_B;
		DiscInPort L_FU_TK_ISOV_12_CL_B;
		DiscInPort L_OX_TK_ISOV_12_OP_B;
		DiscInPort L_OX_TK_ISOV_12_CL_B;
		DiscInPort L_TK_ISOV_12_OP_A;
		DiscInPort L_TK_ISOV_12_CL_A;
		DiscInPort R_FU_TK_ISOV_12_OP_B;
		DiscInPort R_FU_TK_ISOV_12_CL_B;
		DiscInPort R_OX_TK_ISOV_12_OP_B;
		DiscInPort R_OX_TK_ISOV_12_CL_B;
		DiscInPort R_TK_ISOV_12_OP_A;
		DiscInPort R_TK_ISOV_12_CL_A;
		DiscInPort AFT_LEFT_RCS_TANK_ISOLATION_12_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_TANK_ISOLATION_12_SW_CLOSE;
		DiscInPort AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_TANK_ISOLATION_12_SW_CLOSE;
		DiscInPort L_FU_TK_ISO_V_12_OP_1;
		DiscInPort L_FU_TK_ISO_V_12_CL_1;
		DiscInPort L_FU_TK_ISO_V_12_OP_2;
		DiscInPort L_FU_TK_ISO_V_12_CL_2;
		DiscInPort L_OX_TK_ISO_V_12_OP_1;
		DiscInPort L_OX_TK_ISO_V_12_CL_1;
		DiscInPort L_OX_TK_ISO_V_12_OP_2;
		DiscInPort L_OX_TK_ISO_V_12_CL_2;
		DiscInPort R_FU_TK_ISO_V_12_OP_1;
		DiscInPort R_FU_TK_ISO_V_12_CL_1;
		DiscInPort R_FU_TK_ISO_V_12_OP_2;
		DiscInPort R_FU_TK_ISO_V_12_CL_2;
		DiscInPort R_OX_TK_ISO_V_12_OP_1;
		DiscInPort R_OX_TK_ISO_V_12_CL_1;
		DiscInPort R_OX_TK_ISO_V_12_OP_2;
		DiscInPort R_OX_TK_ISO_V_12_CL_2;
		DiscOutPort AFT_LEFT_RCS_TANK_ISOLATION_12_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_TANK_ISOLATION_12_TB_CLOSE;
		DiscOutPort AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_TANK_ISOLATION_12_TB_CLOSE;
		DiscOutPort L_FU_TK_ISOL_12_MOTOR_PWR;
		DiscOutPort L_OX_TK_ISOL_12_MOTOR_PWR;
		DiscOutPort R_FU_TK_ISOL_12_MOTOR_PWR;
		DiscOutPort R_OX_TK_ISOL_12_MOTOR_PWR;

		// AFT RCS ISOLATION VALVES MANIFOLD 3
		DiscInPort R_MANF_ISOV_NO_3_OP;
		DiscInPort R_MANF_ISOV_NO_3_CL_A;
		DiscInPort R_MANF_ISOV_NO_3_CL_B;
		DiscInPort L_MANF_ISOV_NO_3_OP;
		DiscInPort L_MANF_ISOV_NO_3_CL_A;
		DiscInPort L_MANF_ISOV_NO_3_CL_B;
		DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE;
		DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_SW_CLOSE;
		DiscInPort R_FU_MANF_ISOV_3_OP;
		DiscInPort R_FU_MANF_ISOV_3_CL;
		DiscInPort R_OX_MANF_ISOV_3_OP;
		DiscInPort R_OX_MANF_ISOV_3_CL;
		DiscInPort L_FU_MANF_ISOV_3_OP;
		DiscInPort L_FU_MANF_ISOV_3_CL;
		DiscInPort L_OX_MANF_ISOV_3_OP;
		DiscInPort L_OX_MANF_ISOV_3_CL;
		DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE;
		DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_3_TB_CLOSE;
		DiscOutPort R_FU_MANF_ISOV_NO_3_MOTOR_PWR;
		DiscOutPort R_OX_MANF_ISOV_NO_3_MOTOR_PWR;
		DiscOutPort L_FU_MANF_ISOV_NO_3_MOTOR_PWR;
		DiscOutPort L_OX_MANF_ISOV_NO_3_MOTOR_PWR;

		// AFT RCS ISOLATION VALVES MANIFOLD 4
		DiscInPort R_MANF_ISOV_NO_4_OP;
		DiscInPort R_MANF_ISOV_NO_4_CL_A;
		DiscInPort R_MANF_ISOV_NO_4_CL_B;
		DiscInPort L_MANF_ISOV_NO_4_OP;
		DiscInPort L_MANF_ISOV_NO_4_CL_A;
		DiscInPort L_MANF_ISOV_NO_4_CL_B;
		DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE;
		DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_SW_CLOSE;
		DiscInPort R_FU_MANF_ISOV_4_OP;
		DiscInPort R_FU_MANF_ISOV_4_CL;
		DiscInPort R_OX_MANF_ISOV_4_OP;
		DiscInPort R_OX_MANF_ISOV_4_CL;
		DiscInPort L_FU_MANF_ISOV_4_OP;
		DiscInPort L_FU_MANF_ISOV_4_CL;
		DiscInPort L_OX_MANF_ISOV_4_OP;
		DiscInPort L_OX_MANF_ISOV_4_CL;
		DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE;
		DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_4_TB_CLOSE;
		DiscOutPort R_FU_MANF_ISOV_NO_4_MOTOR_PWR;
		DiscOutPort R_OX_MANF_ISOV_NO_4_MOTOR_PWR;
		DiscOutPort L_FU_MANF_ISOV_NO_4_MOTOR_PWR;
		DiscOutPort L_OX_MANF_ISOV_NO_4_MOTOR_PWR;

		// RCS XFEED MANIFOLD 1/2
		DiscInPort L_RCS_FU_XFD_12_OP;
		DiscInPort L_RCS_FU_XFD_12_CL;
		DiscInPort L_RCS_OX_XFD_12_OP;
		DiscInPort L_RCS_OX_XFD_12_CL;
		DiscInPort L_RCS_XFD_12_OP;
		DiscInPort L_RCS_XFD_12_CL;
		DiscInPort AFT_LEFT_RCS_CROSSFEED_12_SW_OPEN;
		DiscInPort AFT_LEFT_RCS_CROSSFEED_12_SW_CLOSE;
		DiscInPort L_RCS_FU_XFD_12_OP_1;
		DiscInPort L_RCS_FU_XFD_12_CL_1;
		DiscInPort L_RCS_OX_XFD_12_OP_1;
		DiscInPort L_RCS_OX_XFD_12_CL_1;
		DiscInPort L_RCS_FU_XFD_12_OP_2;
		DiscInPort L_RCS_FU_XFD_12_CL_2;
		DiscInPort L_RCS_OX_XFD_12_OP_2;
		DiscInPort L_RCS_OX_XFD_12_CL_2;
		DiscOutPort AFT_LEFT_RCS_CROSSFEED_12_TB_OPEN;
		DiscOutPort AFT_LEFT_RCS_CROSSFEED_12_TB_CLOSE;
		DiscOutPort L_RCS_FU_XFD_V_12_MOTOR_PWR;
		DiscOutPort L_RCS_OX_XFD_V_12_MOTOR_PWR;
		DiscInPort R_RCS_FU_XFD_12_OP;
		DiscInPort R_RCS_FU_XFD_12_CL;
		DiscInPort R_RCS_OX_XFD_12_OP;
		DiscInPort R_RCS_OX_XFD_12_CL;
		DiscInPort R_RCS_XFD_12_OP;
		DiscInPort R_RCS_XFD_12_CL;
		DiscInPort AFT_RIGHT_RCS_CROSSFEED_12_SW_OPEN;
		DiscInPort AFT_RIGHT_RCS_CROSSFEED_12_SW_CLOSE;
		DiscInPort R_RCS_FU_XFD_12_OP_1;
		DiscInPort R_RCS_FU_XFD_12_CL_1;
		DiscInPort R_RCS_OX_XFD_12_OP_1;
		DiscInPort R_RCS_OX_XFD_12_CL_1;
		DiscInPort R_RCS_FU_XFD_12_OP_2;
		DiscInPort R_RCS_FU_XFD_12_CL_2;
		DiscInPort R_RCS_OX_XFD_12_OP_2;
		DiscInPort R_RCS_OX_XFD_12_CL_2;
		DiscOutPort AFT_RIGHT_RCS_CROSSFEED_12_TB_OPEN;
		DiscOutPort AFT_RIGHT_RCS_CROSSFEED_12_TB_CLOSE;
		DiscOutPort R_RCS_FU_XFD_V_12_MOTOR_PWR;
		DiscOutPort R_RCS_OX_XFD_V_12_MOTOR_PWR;

		// RIGHT OMS XFEED
		DiscInPort R_OMS_FU_XFD_V_A_OP;
		DiscInPort R_OMS_FU_XFD_V_A_CL;
		DiscInPort R_OMS_OX_XFD_V_A_OP;
		DiscInPort R_OMS_OX_XFD_V_A_CL;
		DiscInPort R_OMS_XFD_A_OP;
		DiscInPort R_OMS_XFD_A_CL;
		DiscInPort RIGHT_OMS_CROSSFEED_A_SW_OPEN;
		DiscInPort RIGHT_OMS_CROSSFEED_A_SW_CLOSE;
		DiscInPort R_OMS_FU_XFD_V_A_OP_1;
		DiscInPort R_OMS_FU_XFD_V_A_CL_1;
		DiscInPort R_OMS_OX_XFD_V_A_OP_1;
		DiscInPort R_OMS_OX_XFD_V_A_CL_1;
		DiscInPort R_OMS_FU_XFD_V_A_OP_2;
		DiscInPort R_OMS_FU_XFD_V_A_CL_2;
		DiscInPort R_OMS_OX_XFD_V_A_OP_2;
		DiscInPort R_OMS_OX_XFD_V_A_CL_2;
		DiscOutPort RIGHT_OMS_CROSSFEED_A_TB_OPEN;
		DiscOutPort RIGHT_OMS_CROSSFEED_A_TB_CLOSE;
		DiscOutPort R_OMS_FU_XFD_V_A_MOTOR_PWR;
		DiscOutPort R_OMS_OX_XFD_V_A_MOTOR_PWR;

		// OMS ISOLATION VALVES
		DiscInPort L_OMS_FU_TK_ISOV_B_OP;
		DiscInPort L_OMS_FU_TK_ISOV_B_CL;
		DiscInPort L_OMS_OX_TK_ISOV_B_OP;
		DiscInPort L_OMS_OX_TK_ISOV_B_CL;
		DiscInPort L_OMS_TK_V_B_OP;
		DiscInPort L_OMS_TK_V_B_CL;
		DiscInPort LEFT_OMS_TANK_ISOLATION_B_SW_OPEN;
		DiscInPort LEFT_OMS_TANK_ISOLATION_B_SW_CLOSE;
		DiscInPort L_OMS_FU_TK_ISOV_B_OP_1;
		DiscInPort L_OMS_FU_TK_ISOV_B_CL_1;
		DiscInPort L_OMS_OX_TK_ISOV_B_OP_1;
		DiscInPort L_OMS_OX_TK_ISOV_B_CL_1;
		DiscInPort L_OMS_FU_TK_ISOV_B_OP_2;
		DiscInPort L_OMS_FU_TK_ISOV_B_CL_2;
		DiscInPort L_OMS_OX_TK_ISOV_B_OP_2;
		DiscInPort L_OMS_OX_TK_ISOV_B_CL_2;
		DiscOutPort LEFT_OMS_TANK_ISOLATION_B_TB_OPEN;
		DiscOutPort LEFT_OMS_TANK_ISOLATION_B_TB_CLOSE;
		DiscOutPort L_OMS_FU_TK_ISOV_B_MOTOR_PWR;
		DiscOutPort L_OMS_OX_TK_ISOV_B_MOTOR_PWR;
		DiscInPort R_OMS_FU_TK_ISOV_B_OP;
		DiscInPort R_OMS_FU_TK_ISOV_B_CL;
		DiscInPort R_OMS_OX_TK_ISOV_B_OP;
		DiscInPort R_OMS_OX_TK_ISOV_B_CL;
		DiscInPort R_OMS_TK_V_B_OP;
		DiscInPort R_OMS_TK_V_B_CL;
		DiscInPort RIGHT_OMS_TANK_ISOLATION_B_SW_OPEN;
		DiscInPort RIGHT_OMS_TANK_ISOLATION_B_SW_CLOSE;
		DiscInPort R_OMS_FU_TK_ISOV_B_OP_1;
		DiscInPort R_OMS_FU_TK_ISOV_B_CL_1;
		DiscInPort R_OMS_OX_TK_ISOV_B_OP_1;
		DiscInPort R_OMS_OX_TK_ISOV_B_CL_1;
		DiscInPort R_OMS_FU_TK_ISOV_B_OP_2;
		DiscInPort R_OMS_FU_TK_ISOV_B_CL_2;
		DiscInPort R_OMS_OX_TK_ISOV_B_OP_2;
		DiscInPort R_OMS_OX_TK_ISOV_B_CL_2;
		DiscOutPort RIGHT_OMS_TANK_ISOLATION_B_TB_OPEN;
		DiscOutPort RIGHT_OMS_TANK_ISOLATION_B_TB_CLOSE;
		DiscOutPort R_OMS_FU_TK_ISOV_B_MOTOR_PWR;
		DiscOutPort R_OMS_OX_TK_ISOV_B_MOTOR_PWR;

	public:
		explicit AMC3( AtlantisSubsystemDirector* _director );
		virtual ~AMC3();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _AMC3_H_
