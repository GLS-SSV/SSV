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
2022/08/05   GLS
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
#include "discsignals.h"


using namespace discsignals;


class MMC3: public AtlantisSubsystem
{
	private:
		DiscInPort PL_BAY_MECH_PWR_SYS_2;

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
