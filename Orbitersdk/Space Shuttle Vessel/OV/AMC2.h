/****************************************************************************
  This file is part of Space Shuttle Vessel

  Aft Motor Control Assembly 2 subsystem definition


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

  Aft Motor Control Assembly 2 definition



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
#ifndef _AMC2_H_
#define _AMC2_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class AMC2: public AtlantisSubsystem
{
	private:
		// VENT DOORS
		// left 8/9 motor 2
		DiscInPort LH_VENTS_8_9_MOTOR_2_OPEN_A;
		DiscInPort LH_VENTS_8_9_MOTOR_2_CLOSE_A;
		DiscInPort LH_VENTS_8_9_MOTOR_2_PURGE_A;
		DiscInPort LH_VENTS_8_9_MOTOR_2_OPEN_B;
		DiscInPort LH_VENTS_8_9_MOTOR_2_CLOSE_B;
		DiscInPort LH_VENTS_8_9_MOTOR_2_PURGE_B;
		DiscInPort LH_VENTS_8_AND_9_CLOSE_2;
		DiscInPort LH_VENTS_8_AND_9_OPEN_2;
		DiscInPort LH_VENTS_8_AND_9_PURGE_IND_2;
		DiscOutPort LH_VENTS_8_AND_9_MOTOR_2_PWR;

		// right 8/9 motor 2
		DiscInPort RH_VENTS_8_9_MOTOR_2_OPEN_A;
		DiscInPort RH_VENTS_8_9_MOTOR_2_CLOSE_A;
		DiscInPort RH_VENTS_8_9_MOTOR_2_PURGE_A;
		DiscInPort RH_VENTS_8_9_MOTOR_2_OPEN_B;
		DiscInPort RH_VENTS_8_9_MOTOR_2_CLOSE_B;
		DiscInPort RH_VENTS_8_9_MOTOR_2_PURGE_B;
		DiscInPort RH_VENTS_8_AND_9_CLOSE_2;
		DiscInPort RH_VENTS_8_AND_9_OPEN_2;
		DiscInPort RH_VENTS_8_AND_9_PURGE_IND_2;
		DiscOutPort RH_VENTS_8_AND_9_MOTOR_2_PWR;

		// ET UMBILICAL DOORS
		DiscInPort ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_CLOSE;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_OPEN;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE;
		DiscInPort ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH;
		DiscInPort ET_DR_CLS_AND_LAT_ARM_2_FA2;
		DiscInPort ET_DR_CLS_AND_LAT_ARM_2_FA1;
		// left latch motor 2
		DiscInPort L_LATCH_A2_FA4;
		DiscInPort L_LATCH_A2_FA1;
		DiscInPort L_LATCH_B2_FA2;
		DiscInPort L_LATCH_B2_FA3;
		DiscInPort LEFT_DOOR_LATCH_REL_2;
		DiscInPort LEFT_DOOR_LATCH_LAT_2;
		DiscInPort LEFT_DOOR_RDY_TO_LCH_3;
		DiscOutPort LEFT_DOOR_LATCH_MOTOR_2_PWR;
		// cl latch 1 motor 2
		DiscInPort CL_1_STOW_A2_FA4;
		DiscInPort CL_1_STOW_A2_FA1;
		DiscInPort CL_1_STOW_B2_FA3;
		DiscInPort CL_1_STOW_B2_FA2;
		DiscInPort CL_1_DEPLOY_A2_FA4;
		DiscInPort CL_1_DEPLOY_A2_FA1;
		DiscInPort CL_1_DEPLOY_B2_FA3;
		DiscInPort CL_1_DEPLOY_B2_FA2;
		DiscInPort CL_LATCH_1_STOW_2;
		DiscInPort CL_LATCH_1_DEPLOY_2;
		DiscOutPort CL_1_MOTOR_2_PWR;
		// right drive motor 2
		DiscInPort R_DOOR_CL_2_FA4;
		DiscInPort R_DOOR_CL_2_FA3;
		DiscInPort RIGHT_DOOR_CLOSE_2;
		DiscInPort RIGHT_DOOR_OPEN_2;
		DiscOutPort RIGHT_DOOR_MOTOR_2_PWR;
		// right latch motor 2
		DiscInPort R_LATCH_A2_FA3;
		DiscInPort R_LATCH_A2_FA1;
		DiscInPort R_LATCH_B2_FA2;
		DiscInPort R_LATCH_B2_FA4;
		DiscInPort RIGHT_DOOR_LATCH_REL_2;
		DiscInPort RIGHT_DOOR_LATCH_LAT_2;
		DiscInPort RIGHT_DOOR_RDY_TO_LCH_3;
		DiscOutPort RIGHT_DOOR_LATCH_MOTOR_2_PWR;

	public:
		explicit AMC2( AtlantisSubsystemDirector* _director );
		virtual ~AMC2();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _AMC2_H_
