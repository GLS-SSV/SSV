/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbital Maneuvering System Thrust Vector Control Command Subsystem Operating Program definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/12/23   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Orbital Maneuvering System Thrust Vector Control Command Subsystem Operating Program definition



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
#ifndef _dps_OMSTVCCMD_SOP_H_
#define _dps_OMSTVCCMD_SOP_H_


#include "../SimpleGPCSoftware.h"
#include <discsignals.h>


namespace dps
{
	class OMSBurnSoftware;

	class OMSTVCCMD_SOP:public SimpleGPCSoftware
	{
		private:
			double L_pitch;
			double L_yaw;
			double R_pitch;
			double R_yaw;
			double GimbalCheckTimer;

			bool GimbalCheck;

			DiscOutPort L_OMS_ENG_PRI_ENA_1;// V43K1020X
			DiscOutPort L_OMS_ENG_PRI_ENA_2;// V43K1021X
			DiscOutPort L_OMS_ENG_SEC_ENA_1;// V43K1023X
			DiscOutPort L_OMS_ENG_SEC_ENA_2;// V43K1024X
			DiscOutPort R_OMS_ENG_PRI_ENA_1;// V43K2020X
			DiscOutPort R_OMS_ENG_PRI_ENA_2;// V43K2021X
			DiscOutPort R_OMS_ENG_SEC_ENA_1;// V43K2023X
			DiscOutPort R_OMS_ENG_SEC_ENA_2;// V43K2024X
			DiscOutPort L_OMS_PRI_P_ACTR_CMD;// V43K1016C
			DiscOutPort L_OMS_SEC_P_ACTR_CMD;// V43K1017C
			DiscOutPort L_OMS_PRI_Y_ACTR_CMD;// V43K1018C
			DiscOutPort L_OMS_SEC_Y_ACTR_CMD;// V43K1019C
			DiscOutPort R_OMS_PRI_P_ACTR_CMD;// V43K2016C
			DiscOutPort R_OMS_SEC_P_ACTR_CMD;// V43K2017C
			DiscOutPort R_OMS_PRI_Y_ACTR_CMD;// V43K2018C
			DiscOutPort R_OMS_SEC_Y_ACTR_CMD;// V43K2019C

			OMSBurnSoftware* pOMSBurnSoftware;

		public:
			explicit OMSTVCCMD_SOP( SimpleGPCSystem* _gpc );
			~OMSTVCCMD_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			void SetGimbalCheckFlag( void );
			bool GetGimbalCheckFlag( void ) const;

			void SetPitch( unsigned int eng, double pitch );
			void SetYaw( unsigned int eng, double yaw );
	};
}


#endif// _dps_OMSTVCCMD_SOP_H_