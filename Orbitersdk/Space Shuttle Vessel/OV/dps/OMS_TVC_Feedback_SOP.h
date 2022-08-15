/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbital Maneuvering System Thrust Vector Control Feedback Subsystem Operating Program definition


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
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Orbital Maneuvering System Thrust Vector Control Feedback Subsystem Operating Program definition



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
#ifndef _dps_OMSTVCFDBK_SOP_H_
#define _dps_OMSTVCFDBK_SOP_H_


#include "SimpleGPCSoftware.h"
#include <discsignals.h>


namespace dps
{
	class OMSBurnSoftware;

	class OMSTVCFDBK_SOP:public SimpleGPCSoftware
	{
		private:
			DiscInPort L_OMS_PRI_P_ACTR_POS;// V43H2500C
			DiscInPort L_OMS_PRI_Y_ACTR_POS;// V43H2502C
			DiscInPort L_OMS_SEC_P_ACTR_POS;// V43H2504C
			DiscInPort L_OMS_SEC_Y_ACTR_POS;// V43H2506C
			DiscInPort R_OMS_PRI_P_ACTR_POS;// V43H2550C
			DiscInPort R_OMS_PRI_Y_ACTR_POS;// V43H2552C
			DiscInPort R_OMS_SEC_P_ACTR_POS;// V43H2554C
			DiscInPort R_OMS_SEC_Y_ACTR_POS;// V43H2556C

			OMSBurnSoftware* pOMSBurnSoftware;

		public:
			explicit OMSTVCFDBK_SOP( SimpleGPCSystem* _gpc );
			~OMSTVCFDBK_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			bool GetActrPos( unsigned int eng, double& p, double& y ) const;
	};
}


#endif// _dps_OMSTVCFDBK_SOP_H_