/****************************************************************************
  This file is part of Space Shuttle Vessel

  ET Umbilical Door definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/02/15   GLS
2021/05/30   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  ET Umbilical Door Component



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
#ifndef _ETUMBDOORS_H_
#define _ETUMBDOORS_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


class ETUmbilicalDoors : public AtlantisSubsystem
{
	public:
		explicit ETUmbilicalDoors( AtlantisSubsystemDirector* _director );
		virtual ~ETUmbilicalDoors();

		void Realize() override;
		void OnPreStep(double simt, double simdt, double mjd) override;

		void OnSaveState(FILEHANDLE scn) const override;
		bool OnParseLine(const char* keyword, const char* line) override;

	private:
		DiscOutPort CL_LATCH_1_STOW_1;
		DiscOutPort CL_LATCH_1_STOW_2;
		DiscOutPort CL_LATCH_1_DEPLOY_1;
		DiscOutPort CL_LATCH_1_DEPLOY_2;
		DiscInPort CL_1_MOTOR_1_PWR;
		DiscInPort CL_1_MOTOR_2_PWR;
		DiscOutPort CL_LATCH_2_STOW_1;
		DiscOutPort CL_LATCH_2_STOW_2;
		DiscOutPort CL_LATCH_2_DEPLOY_1;
		DiscOutPort CL_LATCH_2_DEPLOY_2;
		DiscInPort CL_2_MOTOR_1_PWR;
		DiscInPort CL_2_MOTOR_2_PWR;

		DiscOutPort LEFT_DOOR_CLOSE_1;
		DiscOutPort LEFT_DOOR_CLOSE_2;
		DiscOutPort LEFT_DOOR_OPEN_1;
		DiscOutPort LEFT_DOOR_OPEN_2;
		DiscOutPort LEFT_DOOR_RDY_TO_LCH_1;
		DiscOutPort LEFT_DOOR_RDY_TO_LCH_2;
		DiscOutPort LEFT_DOOR_RDY_TO_LCH_3;
		DiscInPort LEFT_DOOR_MOTOR_1_PWR;
		DiscInPort LEFT_DOOR_MOTOR_2_PWR;
		DiscOutPort LEFT_DOOR_LATCH_REL_1;
		DiscOutPort LEFT_DOOR_LATCH_REL_2;
		DiscOutPort LEFT_DOOR_LATCH_LAT_1;
		DiscOutPort LEFT_DOOR_LATCH_LAT_2;
		DiscInPort LEFT_DOOR_LATCH_MOTOR_1_PWR;
		DiscInPort LEFT_DOOR_LATCH_MOTOR_2_PWR;

		DiscOutPort RIGHT_DOOR_CLOSE_1;
		DiscOutPort RIGHT_DOOR_CLOSE_2;
		DiscOutPort RIGHT_DOOR_OPEN_1;
		DiscOutPort RIGHT_DOOR_OPEN_2;
		DiscOutPort RIGHT_DOOR_RDY_TO_LCH_1;
		DiscOutPort RIGHT_DOOR_RDY_TO_LCH_2;
		DiscOutPort RIGHT_DOOR_RDY_TO_LCH_3;
		DiscInPort RIGHT_DOOR_MOTOR_1_PWR;
		DiscInPort RIGHT_DOOR_MOTOR_2_PWR;
		DiscOutPort RIGHT_DOOR_LATCH_REL_1;
		DiscOutPort RIGHT_DOOR_LATCH_REL_2;
		DiscOutPort RIGHT_DOOR_LATCH_LAT_1;
		DiscOutPort RIGHT_DOOR_LATCH_LAT_2;
		DiscInPort RIGHT_DOOR_LATCH_MOTOR_1_PWR;
		DiscInPort RIGHT_DOOR_LATCH_MOTOR_2_PWR;

		DiscInPort ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH;
		DiscInPort ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH;

		double posleftdoor;// 0 = cl, 1 = op
		double posleftdoorlatch;// 0 = lat, 1 = rel
		double posrightdoor;// 0 = cl, 1 = op
		double posrightdoorlatch;// 0 = lat, 1 = rel
		double poscllatch1;// 0 = sto, 1 = lat
		double poscllatch2;// 0 = sto, 1 = lat

		UINT anim_doorleft;
		UINT anim_doorhingeleft;
		UINT anim_doorright;
		UINT anim_doorhingeright;
		UINT anim_cllatch1;
		UINT anim_cllatch2;

		void AddAnimation( void );
};

#endif// _ETUMBDOORS_H_
