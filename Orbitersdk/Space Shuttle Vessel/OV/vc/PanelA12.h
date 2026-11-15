/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A12 definition



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
#ifndef __VC_PANELA12_H
#define __VC_PANELA12_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever2;
	class StandardTalkback2;
	class StandardSwitchCover;


	class PanelA12 : public AtlantisPanel
	{
		private:
			StdSwitch3* pAPU_HEATER_GAS_GEN_FUEL_PUMP_1;
			StdSwitch3* pAPU_HEATER_GAS_GEN_FUEL_PUMP_2;
			StdSwitch3* pAPU_HEATER_GAS_GEN_FUEL_PUMP_3;
			StdSwitch3* pAPU_HEATER_LUBE_OIL_LINE_1;
			StdSwitch3* pAPU_HEATER_LUBE_OIL_LINE_2;
			StdSwitch3* pAPU_HEATER_LUBE_OIL_LINE_3;

			StdSwitch2* pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1A;
			StdSwitch2* pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_1B;
			StdSwitch2* pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2A;
			StdSwitch2* pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_2B;
			StdSwitch2* pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3A;
			StdSwitch2* pAPU_HEATER_TANK_FUEL_LINE_H2O_SYS_3B;
			StdSwitch2* pHYDRAULIC_HEATER_RUDDER_SPD_BK_A;
			StdSwitch2* pHYDRAULIC_HEATER_RUDDER_SPD_BK_B;
			StdSwitch2* pHYDRAULIC_HEATER_BODY_FLAP_A;
			StdSwitch2* pHYDRAULIC_HEATER_BODY_FLAP_B;
			StdSwitch2* pHYDRAULIC_HEATER_ELEVON_A;
			StdSwitch2* pHYDRAULIC_HEATER_ELEVON_B;
			StdSwitch2* pHYDRAULIC_HEATER_AFT_FUSELAGE_A;
			StdSwitch2* pHYDRAULIC_HEATER_AFT_FUSELAGE_B;
			StdSwitch2* pHYD_CIRC_PUMP_POWER_1;
			StdSwitch2* pHYD_CIRC_PUMP_POWER_2;
			StdSwitch2* pHYD_CIRC_PUMP_POWER_3;

			LockableLever2* pLG_ARM_DN_RESET;

			StandardTalkback2* pFC_3_STRUCT_RTN_TB;

			StdSwitch3* pFC_3_STRUCT_RTN;
			StandardSwitchCover* pFC_3_STRUCT_RTN_Cover;

			StdSwitch2* pGPS_POWER;
			StdSwitch2* pENCRYPT;
			StdSwitch2* pGPS_PRE_AMP_UPPER;
			StdSwitch2* pGPS_PRE_AMP_LOWER;

			SURFHANDLE hOV099Texture;

			bool OV102;
			bool OV099;

		public:
			PanelA12( Atlantis* _sts, const std::string &orbiter );
			virtual ~PanelA12( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void VisualCreated( void ) override;
	};
}

#endif// __VC_PANELA12_H
