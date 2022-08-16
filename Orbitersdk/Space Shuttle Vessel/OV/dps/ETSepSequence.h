/****************************************************************************
  This file is part of Space Shuttle Vessel

  External Tank Separation Sequence definition


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
2021/10/23   GLS
2021/12/30   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  External Tank Separation Sequence definition



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
#ifndef _dps_ETSEP_H_
#define _dps_ETSEP_H_


#include "SimpleGPCSoftware.h"
#include <discsignals.h>


using namespace discsignals;


namespace dps
{
	class SSME_Operations;
	class TransitionDAP;
	class IO_Control;
	class MPS_ATVC_CMD_SOP;
	class MEC_SOP;

	/**
	 * @brief	Implementation of the ET Separation Sequencer running in the GPCs.
	 *
	 * Controls and executes the ET Separation, closing the appropriate valves and checking that separation conditions are met.
	 */
	class ETSepSequence:public SimpleGPCSoftware
	{
		private:
			SSME_Operations* pSSME_Operations;
			TransitionDAP* pTransitionDAP;
			IO_Control* pIO_Control;
			MPS_ATVC_CMD_SOP* pMPS_ATVC_CMD_SOP;
			MEC_SOP* pMEC_SOP;

			DiscOutPort PD1_OP;
			DiscOutPort PD1_CL;
			DiscOutPort PD2_OP;
			DiscOutPort PD2_CL;
			DiscOutPort PD3_OP;
			DiscOutPort PD3_CL;

			DiscInPort PD1_CL_Ind_A;
			DiscInPort PD1_CL_Ind_B;
			DiscInPort PD2_CL_Ind_A;
			DiscInPort PD2_CL_Ind_B;
			DiscInPort PD3_CL_Ind;

			bool active;
			bool done;
			bool autoETSEP;
			bool ETSEPCommand;

			double t_MECO;
			double t_last;
			double timerSEP;
		public:
			explicit ETSepSequence( SimpleGPCSystem* _gpc );
			~ETSepSequence( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void Realize( void ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			bool GetETSEPCommandFlag( void ) const;
	};
}


#endif// _dps_ETSEP_H_