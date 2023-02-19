/****************************************************************************
  This file is part of Space Shuttle Vessel

  MPS Dump definition


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
2021/10/23   GLS
2021/12/30   GLS
2022/06/10   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/12/23   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  MPS Dump definition



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
#ifndef _dps_MPS_Dump_H_
#define _dps_MPS_Dump_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class SSME_SOP;
	class IO_Control;
	class MPS_ATVC_CMD_SOP;

	/**
	 * @brief	Implementation of the MPS Dump software running in the GPCs.
	 *
	 * Controls the post-MECO MPS Dump sequence by issuing open and close commands to appropriate valves at specified times.
	 */
	class MPS_Dump:public SimpleGPCSoftware
	{
		private:
			SSME_SOP* pSSME_SOP;
			IO_Control* pIO_Control;
			MPS_ATVC_CMD_SOP* pMPS_ATVC_CMD_SOP;

			double t_MECO;
			double t_dump_start;
			double t_last;
			double t_MM106_trans;

			bool active;
			bool dump_started;
			bool MM106_trans;

		public:
			explicit MPS_Dump( SimpleGPCSystem* _gpc );
			~MPS_Dump( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;

			void Realize( void ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_MPS_Dump_H_