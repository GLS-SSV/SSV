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
#include "discsignals.h"


using namespace discsignals;


class AMC3: public AtlantisSubsystem
{
	private:
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

	public:
		explicit AMC3( AtlantisSubsystemDirector* _director );
		virtual ~AMC3();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _AMC3_H_
