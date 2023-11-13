/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbital Maneuvering System subsystem definition


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
2020/04/01   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/10/09   GLS
2023/11/12   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Orbital Maneuvering System definition



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
#ifndef __OMS_H_
#define __OMS_H_


#include "../AtlantisSubsystem.h"
#include <discsignals.h>
#include <ValveManager.h>
#include <Sensor.h>


using namespace discsignals;

class MotorValve;
class SolenoidValve_2;


namespace oms
{
	class OMS:public AtlantisSubsystem
	{
		private:
			unsigned int ID;

			unsigned short source;

			Sensor ChamberPressure;
			Sensor N2TankPressure1;
			Sensor N2TankPressure2;
			Sensor HeTankPressure1;
			Sensor HeTankPressure2;

			ValveManager vman;

			SolenoidValve_2* OMSHeliumIsolationAVlv;
			SolenoidValve_2* OMSHeliumIsolationBVlv;
			SolenoidValve_2* OMSVaporIsolation1Vlv;
			SolenoidValve_2* OMSVaporIsolation2Vlv;

			MotorValve* OMSFuelTankIsolationAVlv;
			MotorValve* OMSOxidTankIsolationAVlv;
			MotorValve* OMSFuelTankIsolationBVlv;
			MotorValve* OMSOxidTankIsolationBVlv;

			MotorValve* OMSFuelCrossfeedAVlv;
			MotorValve* OMSOxidCrossfeedAVlv;
			MotorValve* OMSFuelCrossfeedBVlv;
			MotorValve* OMSOxidCrossfeedBVlv;

			SolenoidValve_2* OMSEnginePressureVlv;
			//SolenoidValve_2* OMSEngineN2Vlv;
			SolenoidValve_2* OMSEngineControl1Vlv;
			SolenoidValve_2* OMSEngineControl2Vlv;
			SolenoidValve_2* OMSEnginePurge1Vlv;
			SolenoidValve_2* OMSEnginePurge2Vlv;


			DiscOutPort OMSEngineBipropellent1OPVlv;
			DiscOutPort OMSEngineBipropellent2OPVlv;

			DiscInPort OMS_HE_ISOV_A_OP;
			DiscInPort OMS_HEPRESS_VAPORISOL_A_SW_OPEN;
			DiscInPort OMS_HEPRESS_VAPORISOL_A_SW_CLOSE;
			DiscOutPort OMS_HE_ISOV_A_POWER_OP;
			DiscInPort OMS_HE_ISOV_B_OP;
			DiscInPort OMS_HEPRESS_VAPORISOL_B_SW_OPEN;
			DiscInPort OMS_HEPRESS_VAPORISOL_B_SW_CLOSE;
			DiscOutPort OMS_HE_ISOV_B_POWER_OP;

			DiscInPort OMS_VAP_ISOV_1_OP;
			DiscOutPort OMS_VAP_ISOV_1_POWER_OP;
			DiscInPort OMS_VAP_ISOV_2_OP;
			DiscOutPort OMS_VAP_ISOV_2_POWER_OP;

			DiscInPort OMS_VLV_1_COIL_1_CMD;
			DiscInPort OMS_VLV_2_COIL_1_CMD;
			DiscInPort OMS_VLV_1_COIL_2_CMD;
			DiscInPort OMS_VLV_2_COIL_2_CMD;
			DiscInPort OMS_ENG_SW_ARM_1;
			DiscInPort OMS_ENG_SW_ARM_2;
			DiscInPort OMS_ENG_SW_ARMPRESS_1;
			DiscInPort OMS_ENG_SW_ARMPRESS_2;
			DiscInPort OMS_ENG_VLV_SW_ON_1;
			DiscInPort OMS_ENG_VLV_SW_ON_2;
			DiscOutPort OMS_ENG_PRESS_V_POWER_OP_1;
			DiscOutPort OMS_ENG_PRESS_V_POWER_OP_2;
			DiscOutPort OMS_ENG_CNT_V1_POWER_OP_1;
			DiscOutPort OMS_ENG_CNT_V2_POWER_OP_1;
			DiscOutPort OMS_ENG_CNT_V1_POWER_OP_2;
			DiscOutPort OMS_ENG_CNT_V2_POWER_OP_2;

		public:
			OMS( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID );
			virtual ~OMS( void );

			void Realize( void ) override;
			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			bool SingleParamParseLine( void ) const override {return true;};
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}


#endif// __OMS_H_
