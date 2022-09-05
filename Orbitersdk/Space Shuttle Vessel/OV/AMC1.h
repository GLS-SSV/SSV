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
2020/06/20   GLS
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
		// VENT DOORS
		// left 8/9 motor 1
		DiscInPort LH_VENTS_8_9_MOTOR_1_OPEN_A;
		DiscInPort LH_VENTS_8_9_MOTOR_1_CLOSE_A;
		DiscInPort LH_VENTS_8_9_MOTOR_1_PURGE_A;
		DiscInPort LH_VENTS_8_9_MOTOR_1_OPEN_B;
		DiscInPort LH_VENTS_8_9_MOTOR_1_CLOSE_B;
		DiscInPort LH_VENTS_8_9_MOTOR_1_PURGE_B;
		DiscInPort LH_VENTS_8_AND_9_CLOSE_1;
		DiscInPort LH_VENTS_8_AND_9_OPEN_1;
		DiscInPort LH_VENTS_8_AND_9_PURGE_IND_1;
		DiscOutPort LH_VENTS_8_AND_9_MOTOR_1_PWR;

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

	public:
		explicit AMC1( AtlantisSubsystemDirector* _director );
		virtual ~AMC1();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _AMC1_H_
