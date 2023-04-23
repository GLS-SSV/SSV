/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel R14 definition



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
#ifndef __VC_PANELR14_H
#define __VC_PANELR14_H


#include "AtlantisPanel.h"


namespace vc
{
	class CircuitBreaker;


	class PanelR14:public AtlantisPanel
	{
		private:
			CircuitBreaker* pMNC_MDU_CDR_1;
			CircuitBreaker* pMNB_MDU_CDR_2;
			CircuitBreaker* pMNB_MDU_MFD_1;
			CircuitBreaker* pMNA_MDU_MFD_2;
			CircuitBreaker* pMNA_MDU_PLT_1;
			CircuitBreaker* pMNC_MDU_PLT_2;
			CircuitBreaker* pMNC_MDU_AFD_1;
			CircuitBreaker* pMNA_ADC_1A_2A;
			CircuitBreaker* pMNB_ADC_1B_2B;
			CircuitBreaker* pMNB_TV_A_CAMR_CAMR_PTU;
			CircuitBreaker* pMNB_TV_A_CAMR_CAMR_HTR;
			CircuitBreaker* pMNB_TV_A_CAMR_ILLUM_PTU_HTR;
			CircuitBreaker* pMNC_TV_B_CAMR_CAMR_PTU;
			CircuitBreaker* pMNC_TV_B_CAMR_CAMR_HTR;
			CircuitBreaker* pMNC_TV_B_CAMR_ILLUM_PTU_HTR;
			CircuitBreaker* pMNA_TV_C_CAMR_CAMR_PTU;
			CircuitBreaker* pMNA_TV_C_CAMR_CAMR_HTR;
			CircuitBreaker* pMNA_TV_C_CAMR_ILLUM_PTU_HTR;
			CircuitBreaker* pMNA_TV_D_CAMR_CAMR_PTU;
			CircuitBreaker* pMNA_TV_D_CAMR_CAMR_HTR;
			CircuitBreaker* pMNA_TV_D_CAMR_ILLUM_PTU_HTR;
			CircuitBreaker* pMNB_TV_RMS_CAMR_CAMR_PTU;
			CircuitBreaker* pMNB_TV_RMS_CAMR_WRIST_ILLUM_CAMR_HTR;
			CircuitBreaker* pMNB_TV_RMS_CAMR_ELB_ILLUM_PTU_HTR;
			CircuitBreaker* pMNA_TV_CONTR_UNIT;
			CircuitBreaker* pMNB_TV_CONTR_UNIT;
			CircuitBreaker* pMNA_TV_MON_1;
			CircuitBreaker* pMNB_TV_MON_2;

		public:
			explicit PanelR14( Atlantis* _sts );
			virtual ~PanelR14( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELR14_H
