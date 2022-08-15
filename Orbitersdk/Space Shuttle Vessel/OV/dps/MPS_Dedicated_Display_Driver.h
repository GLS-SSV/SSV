/****************************************************************************
  This file is part of Space Shuttle Vessel

  Main Propulsion System Dedicated Display Driver definition


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
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Main Propulsion System Dedicated Display Driver definition



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
#ifndef _dps_MPS_DDD_H_
#define _dps_MPS_DDD_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	class SSME_SOP;
	class ETSepSequence;

	/**
	 * @brief	Implementation of the MPS Dedicated Display Driver software running in the GPCs.
	 *
	 * Currently in MEDS it only controls the MPS Engine Red and Amber lights, but before it also controlled the MPS Engine PC meters.
	 */
	class MPS_Dedicated_Display_Driver:public SimpleGPCSoftware
	{
		private:
			/**
			 * Pointer to SSME SOP class, source of data.
			 */
			SSME_SOP* pSSME_SOP;

			ETSepSequence* pETSepSequence;

			bool AmberStatusLight[3];// V72X0035X, V72X0036X, V72X0037X
			bool RedStatusLight[3];// V72X0030X, V72X0031X, V72X0032X
		public:
			explicit MPS_Dedicated_Display_Driver( SimpleGPCSystem* _gpc );
			~MPS_Dedicated_Display_Driver( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void Realize( void ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_MPS_DDD_H_