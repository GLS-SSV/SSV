/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel R13L definition



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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/02/01   GLS
2022/09/29   GLS
2022/11/01   GLS
2023/11/11   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel R13L definition



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
#ifndef VC_PANELR13L
#define VC_PANELR13L


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever2;
	class LockableLever3;
	class StandardTalkback3;


	class PanelR13L:public AtlantisPanel
	{
		private:
			StdSwitch2* pPL_BAY_DOOR_SYS_1;
			StdSwitch2* pPL_BAY_DOOR_SYS_2;
			StdSwitch2* pPL_BAY_MECH_PWR_SYS_1;
			StdSwitch2* pPL_BAY_MECH_PWR_SYS_2;

			StdSwitch3* pRADIATOR_LATCH_CONTROL_SYS_A;
			StdSwitch3* pRADIATOR_LATCH_CONTROL_SYS_B;
			StdSwitch3* pRADIATOR_CONTROL_SYS_A;
			StdSwitch3* pRADIATOR_CONTROL_SYS_B;
			StdSwitch3* pKU_ANTENNA;
			StdSwitch3* pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A;
			StdSwitch3* pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B;

			LockableLever3* pPL_BAY_DOOR;
			LockableLever2* pKU_ANTENNA_DIRECT_STOW;

			StandardTalkback3* pPL_BAY_DOOR_TB;
			StandardTalkback3* pRADIATOR_LATCH_CONTROL_STBD;
			StandardTalkback3* pRADIATOR_LATCH_CONTROL_PORT;
			StandardTalkback3* pRADIATOR_CONTROL_STBD;
			StandardTalkback3* pRADIATOR_CONTROL_PORT;
			StandardTalkback3* pKU_ANTENNA_TB;
			StandardTalkback3* pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_A_TB;
			StandardTalkback3* pMANNED_MANUV_UNIT_GN2_SPLY_ISOL_VLV_B_TB;

			DiscInPort PORT_RAD_LATCH_REL_1;
			DiscInPort PORT_RAD_LATCH_LAT_1;
			DiscInPort STARBOARD_RAD_LATCH_REL_1;
			DiscInPort STARBOARD_RAD_LATCH_LAT_1;
			DiscInPort PORT_RAD_LATCH_REL_2;
			DiscInPort PORT_RAD_LATCH_LAT_2;
			DiscInPort STARBOARD_RAD_LATCH_REL_2;
			DiscInPort STARBOARD_RAD_LATCH_LAT_2;
			DiscOutPort pRADIATOR_LATCH_CONTROL_PORT_REL;
			DiscOutPort pRADIATOR_LATCH_CONTROL_PORT_LAT;
			DiscOutPort pRADIATOR_LATCH_CONTROL_STBD_REL;
			DiscOutPort pRADIATOR_LATCH_CONTROL_STBD_LAT;

			DiscInPort PL_BAY_DOOR_OPEN_1;
			DiscInPort PL_BAY_DOOR_OPEN_2;
			DiscInPort PL_BAY_DOOR_CLOSE_1;
			DiscInPort PL_BAY_DOOR_CLOSE_2;
			DiscOutPort PL_BAY_DOOR_OPEN;
			DiscOutPort PL_BAY_DOOR_CLOSE;

			DiscOutPort PL_BAY_DOOR_CL_A;
			DiscOutPort PL_BAY_DOOR_CL_B;
			DiscOutPort PL_BAY_DOOR_CL_C;
			DiscOutPort PL_BAY_DOOR_CL_D;
			DiscOutPort PL_BAY_DOOR_OP_A;
			DiscOutPort PL_BAY_DOOR_OP_B;
			DiscOutPort PL_BAY_DOOR_OP_C;
			DiscOutPort PL_BAY_DOOR_OP_D;
			DiscInPort PL_BAY_DOOR_CL;
			DiscInPort PL_BAY_DOOR_OP;

		public:
			explicit PanelR13L( Atlantis* psts );
			virtual ~PanelR13L();

			void DefineVC() override;
			void RegisterVC() override;
			void Realize() override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif //VC_PANELR13L
