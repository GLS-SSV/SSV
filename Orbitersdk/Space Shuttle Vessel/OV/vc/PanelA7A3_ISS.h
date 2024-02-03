/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A7A3 ISS definition



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
#ifndef __VC_PANELA7A3ISS_H
#define __VC_PANELA7A3ISS_H


#include "AtlantisPanel.h"


namespace vc
{
	class CircuitBreaker;
	class StdSwitch2;
	class StdSwitch3;
	class StandardTalkback3;
	class StandardTalkback2;


	class PanelA7A3_ISS : public AtlantisPanel
	{
		private:
			CircuitBreaker* pESS_1BC_SYS_PWR_CNTL_SYS_1;
			CircuitBreaker* pESS_1BC_DEPRESS_SYS_1_VENT_ISOL;
			CircuitBreaker* pMAIN_A_DEPRESS_SYS_1_VENT;
			CircuitBreaker* pMAIN_A_DOCK_LIGHT_TRUSS_FWD;
			CircuitBreaker* pMAIN_A_DOCK_LIGHT_VEST_PORT;

			CircuitBreaker* pESS_2CA_SYS_PWR_CNTL_SYS_2;
			CircuitBreaker* pESS_2CA_DEPRESS_SYS_2_VENT_ISOL;
			CircuitBreaker* pMAIN_B_DEPRESS_SYS_2_VENT;
			CircuitBreaker* pMAIN_B_DOCK_LIGHT_TRUSS_AFT;
			CircuitBreaker* pMAIN_B_DOCK_LIGHT_VEST_STBD;

			CircuitBreaker* pMAIN_A_LOGIC_3;
			CircuitBreaker* pMAIN_A_LOGIC_1;
			CircuitBreaker* pMAIN_B_LOGIC_1;
			CircuitBreaker* pMAIN_B_LOGIC_2;
			CircuitBreaker* pMAIN_C_LOGIC_2;
			CircuitBreaker* pMAIN_C_LOGIC_3;

			CircuitBreaker* pPMA_2_3_GRP_1_HOOKS_SYS_A_OPEN;
			CircuitBreaker* pPMA_2_3_GRP_1_HOOKS_SYS_A_CLOSE;
			CircuitBreaker* pPMA_2_3_GRP_1_HOOKS_SYS_B_OPEN;
			CircuitBreaker* pPMA_2_3_GRP_1_HOOKS_SYS_B_CLOSE;

			CircuitBreaker* pPMA_2_3_GRP_2_HOOKS_SYS_A_OPEN;
			CircuitBreaker* pPMA_2_3_GRP_2_HOOKS_SYS_A_CLOSE;
			CircuitBreaker* pPMA_2_3_GRP_2_HOOKS_SYS_B_OPEN;
			CircuitBreaker* pPMA_2_3_GRP_2_HOOKS_SYS_B_CLOSE;


			StandardTalkback2* pSYSTEM_POWER_SYS_1;
			StandardTalkback2* pSYSTEM_POWER_SYS_2;

			StandardTalkback3* pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL_TB;
			StandardTalkback3* pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_TB;
			StandardTalkback3* pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL_TB;
			StandardTalkback3* pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_TB;

			StandardTalkback3* pPMA_2_3_HOOKS_GROUP_1;
			StandardTalkback3* pPMA_2_3_HOOKS_GROUP_2;


			StdSwitch3* pSYSTEM_POWER_MN_A;
			StdSwitch3* pSYSTEM_POWER_MN_B;

			StdSwitch2* pPYRO_POWER_MN_A;
			StdSwitch2* pPYRO_POWER_MN_B;

			StdSwitch3* pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL;
			StdSwitch3* pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT;
			StdSwitch3* pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL;
			StdSwitch3* pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT;

			StdSwitch2* pPSU_POWER_MN_A;
			StdSwitch2* pPSU_POWER_MN_B;

			StdSwitch2* pLIGHTS_TRUSS_FWD;
			StdSwitch2* pLIGHTS_TRUSS_AFT;
			StdSwitch2* pLIGHTS_VESTIBULE_PORT;
			StdSwitch2* pLIGHTS_VESTIBULE_STBD;

			StdSwitch3* pPMA_2_3_HOOKS_SYS_A;
			StdSwitch3* pPMA_2_3_HOOKS_SYS_B;


			DiscInPort dipMAIN_A_LOGIC_3;
			DiscInPort dipMAIN_A_LOGIC_1;
			DiscInPort dipMAIN_B_LOGIC_1;
			DiscInPort dipMAIN_B_LOGIC_2;
			DiscInPort dipMAIN_C_LOGIC_2;
			DiscInPort dipMAIN_C_LOGIC_3;
			DiscInPort dipPSU_POWER_MN_A;
			DiscInPort dipPSU_POWER_MN_B;
			DiscInPort dipMAIN_A_DOCK_LIGHT_TRUSS_FWD;
			DiscInPort dipMAIN_B_DOCK_LIGHT_TRUSS_AFT;
			DiscInPort dipMAIN_A_DOCK_LIGHT_VEST_PORT;
			DiscInPort dipMAIN_B_DOCK_LIGHT_VEST_STBD;
			DiscInPort dipLIGHTS_TRUSS_FWD;
			DiscInPort dipLIGHTS_TRUSS_AFT;
			DiscInPort dipLIGHTS_VESTIBULE_PORT;
			DiscInPort dipLIGHTS_VESTIBULE_STBD;

			DiscOutPort dopPNL_LOGIC_A;
			DiscOutPort dopPNL_LOGIC_B;
			DiscOutPort dopPNL_LOGIC_C;
			DiscOutPort dopCW1;
			DiscOutPort dopCW2;
			DiscOutPort dopLIGHT_TRUSS_FWD;
			DiscOutPort dopLIGHT_TRUSS_AFT;
			DiscOutPort dopLIGHT_VEST_PORT;
			DiscOutPort dopLIGHT_VEST_STBD;

		public:
			explicit PanelA7A3_ISS( Atlantis* _sts );
			virtual ~PanelA7A3_ISS( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __VC_PANELA7A3ISS_H
