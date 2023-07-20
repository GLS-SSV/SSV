/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbital Maneuvering System Thrust Vector Control definition


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
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/12/28   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Orbital Maneuvering System Thrust Vector Control definition



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
#ifndef __OMSTVC_H_
#define __OMSTVC_H_


#include "../AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;


namespace oms
{
	class OMS_TVC:public AtlantisSubsystem
	{
		private:
			unsigned int ID;// 0 = L, 1 = R

			double pitch;// pitch actuator position [deg]
			double yaw;// yaw actuator position [deg]

			bool PRI_P_driving;
			bool PRI_Y_driving;
			bool SEC_P_driving;
			bool SEC_Y_driving;

			DiscInPort OMS_ENG_PRI_ENA_1;// V43K1020X
			DiscInPort OMS_ENG_PRI_ENA_2;// V43K1021X
			DiscInPort OMS_ENG_SEC_ENA_1;// V43K1023X
			DiscInPort OMS_ENG_SEC_ENA_2;// V43K1024X

			DiscInPort OMS_PRI_P_ACTR_CMD;// V43K1016C
			DiscInPort OMS_PRI_Y_ACTR_CMD;// V43K1018C
			DiscInPort OMS_SEC_P_ACTR_CMD;// V43K1017C
			DiscInPort OMS_SEC_Y_ACTR_CMD;// V43K1019C

			DiscOutPort OMS_PRI_P_ACTR_POS;// V43H2500C
			DiscOutPort OMS_PRI_Y_ACTR_POS;// V43H2502C
			DiscOutPort OMS_SEC_P_ACTR_POS;// V43H2504C
			DiscOutPort OMS_SEC_Y_ACTR_POS;// V43H2506C

			void Actuator( bool &driving, double &cur, double tgt, double step, double max );

		public:
			OMS_TVC( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID );
			virtual ~OMS_TVC( void );

			void Realize( void ) override;
			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			bool SingleParamParseLine( void ) const override {return true;};
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __OMSTVC_H_
