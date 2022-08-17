/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Motor Control Assembly 1 subsystem definition


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

  Mid Motor Control Assembly 1 definition



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
#ifndef _MMC1_H_
#define _MMC1_H_


#include "AtlantisSubsystem.h"
#include "discsignals.h"


using namespace discsignals;


class MMC1: public AtlantisSubsystem
{
	private:
		DiscInPort PL_BAY_MECH_PWR_SYS_1;

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
		DiscInPort LOGIC_POWER_SYS_1A;
		// latch 1a
		DiscInPort PL_1_SEL_1A_LAT;
		DiscInPort PL_1_SEL_1A_REL;
		DiscOutPort PL_1_SEL_1_MOTOR_1_PWR;
		// latch 2a
		DiscInPort PL_1_SEL_2A_LAT;
		DiscInPort PL_1_SEL_2A_REL;
		DiscOutPort PL_1_SEL_2_MOTOR_1_PWR;
		// latch 3a
		DiscInPort PL_1_SEL_3A_LAT;
		DiscInPort PL_1_SEL_3A_REL;
		DiscOutPort PL_1_SEL_3_MOTOR_1_PWR;
		// latch 4a
		DiscInPort PL_1_SEL_4A_LAT;
		DiscInPort PL_1_SEL_4A_REL;
		DiscOutPort PL_1_SEL_4_MOTOR_1_PWR;
		// latch 5a
		DiscInPort PL_1_SEL_5A_LAT;
		DiscInPort PL_1_SEL_5A_REL;
		DiscOutPort PL_1_SEL_5_MOTOR_1_PWR;

		// pl select pos 2 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_2A;
		// latch 1a
		DiscInPort PL_2_SEL_1A_LAT;
		DiscInPort PL_2_SEL_1A_REL;
		DiscOutPort PL_2_SEL_1_MOTOR_1_PWR;
		// latch 2a
		DiscInPort PL_2_SEL_2A_LAT;
		DiscInPort PL_2_SEL_2A_REL;
		DiscOutPort PL_2_SEL_2_MOTOR_1_PWR;
		// latch 3a
		DiscInPort PL_2_SEL_3A_LAT;
		DiscInPort PL_2_SEL_3A_REL;
		DiscOutPort PL_2_SEL_3_MOTOR_1_PWR;
		// latch 4a
		DiscInPort PL_2_SEL_4A_LAT;
		DiscInPort PL_2_SEL_4A_REL;
		DiscOutPort PL_2_SEL_4_MOTOR_1_PWR;
		// latch 5a
		DiscInPort PL_2_SEL_5A_LAT;
		DiscInPort PL_2_SEL_5A_REL;
		DiscOutPort PL_2_SEL_5_MOTOR_1_PWR;

		// pl select pos 3 sys 1 latch motors
		DiscInPort LOGIC_POWER_SYS_3A;
		// latch 1a
		DiscInPort PL_3_SEL_1A_LAT;
		DiscInPort PL_3_SEL_1A_REL;
		DiscOutPort PL_3_SEL_1_MOTOR_1_PWR;
		// latch 2a
		DiscInPort PL_3_SEL_2A_LAT;
		DiscInPort PL_3_SEL_2A_REL;
		DiscOutPort PL_3_SEL_2_MOTOR_1_PWR;
		// latch 3a
		DiscInPort PL_3_SEL_3A_LAT;
		DiscInPort PL_3_SEL_3A_REL;
		DiscOutPort PL_3_SEL_3_MOTOR_1_PWR;
		// latch 4a
		DiscInPort PL_3_SEL_4A_LAT;
		DiscInPort PL_3_SEL_4A_REL;
		DiscOutPort PL_3_SEL_4_MOTOR_1_PWR;
		// latch 5a
		DiscInPort PL_3_SEL_5A_LAT;
		DiscInPort PL_3_SEL_5A_REL;
		DiscOutPort PL_3_SEL_5_MOTOR_1_PWR;

	public:
		explicit MMC1( AtlantisSubsystemDirector* _director );
		virtual ~MMC1();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _MMC1_H_
