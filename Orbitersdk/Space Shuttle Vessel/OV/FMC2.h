/****************************************************************************
  This file is part of Space Shuttle Vessel

  Forward Motor Control Assembly 2 subsystem definition


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
2021/05/30   GLS
2021/06/01   GLS
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

  Forward Motor Control Assembly 2 definition



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
#ifndef _FMC2_H_
#define _FMC2_H_


#include "AtlantisSubsystem.h"
#include "discsignals.h"


using namespace discsignals;


class FMC2: public AtlantisSubsystem
{
	private:
		// AIR DATA
		DiscInPort AIR_DATA_PROBE_LEFT_DEPLOYHEAT;
		DiscInPort AIR_DATA_PROBE_LEFT_DEPLOY;
		DiscInPort AIR_DATA_PROBE_LEFT_STOW;
		DiscInPort AIR_DATA_PROBE_STOW_LEFT_ENABLE;
		DiscInPort AIR_DATA_PROBE_RIGHT_DEPLOYHEAT;
		DiscInPort AIR_DATA_PROBE_RIGHT_DEPLOY;
		DiscInPort AIR_DATA_PROBE_RIGHT_STOW;
		DiscInPort AIR_DATA_PROBE_STOW_RIGHT_ENABLE;
		// left probe motor 2
		DiscInPort L_ADP_STOW_2;
		DiscInPort L_ADP_DEPLOY_2;
		DiscOutPort LEFT_PROBE_MOTOR_2_PWR;
		// right probe motor 2
		DiscInPort R_ADP_STOW_2;
		DiscInPort R_ADP_DEPLOY_2;
		DiscOutPort RIGHT_PROBE_MOTOR_2_PWR;

		// STAR TRACKER
		DiscInPort STAR_TRACKER_POWER_Z;
		DiscInPort STAR_TRACKER_POWER_Y;
		DiscInPort STAR_TRACKER_DOOR_CONTROL_SYS_1_CLOSE;
		DiscInPort STAR_TRACKER_DOOR_CONTROL_SYS_1_OPEN;
		DiscInPort STAR_TRACKER_DOOR_CONTROL_SYS_2_CLOSE;
		DiscInPort STAR_TRACKER_DOOR_CONTROL_SYS_2_OPEN;
		// -z system 1 motor control
		DiscInPort STAR_TRACKER_Z_DOOR_CLS_2;
		DiscInPort STAR_TRACKER_Z_DOOR_OP_2;
		DiscOutPort SYS_1_MOTOR_2_PWR;
		// -y system 2 motor control
		DiscInPort STAR_TRACKER_Y_DOOR_CLS_2;
		DiscInPort STAR_TRACKER_Y_DOOR_OP_2;
		DiscOutPort SYS_2_MOTOR_2_PWR;

	public:
		explicit FMC2( AtlantisSubsystemDirector* _director );
		virtual ~FMC2();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _FMC2_H_
