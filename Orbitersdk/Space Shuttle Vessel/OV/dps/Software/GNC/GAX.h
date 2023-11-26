/****************************************************************************
  This file is part of Space Shuttle Vessel

  GNC Annunciation Interface definition


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

#ifndef _dps_GAX_H_
#define _dps_GAX_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * @brief	Implementation of the GNC Annunciation Interface software that runs in the GPCs.
	 * 
	 * This class generates the GNC fault messages and sends them to the Fault Annunciation module.
	 */
	class GAX:public SimpleGPCSoftware
	{
		private:
			double step;

			bool bET_SEP_INH;
			bool bMPS_CMD[3];
			bool bMPS_DATA[3];
			bool bMPS_ELEC[3];
			bool bMPS_HYD[3];
			bool bOTT_ST_IN;
			bool bROLL_REF;
			bool bSSME_FAIL[3];
			bool bSW_TO_MEP;
			bool bDAP_DNMODE_RHC;
			bool bFCS_SAT_POS;
			bool bSPD_BRK;
			bool bPROBES;
			bool bTGT_DELTA_T;
			bool bTGT_EL_ANG;
			bool bTGT_ITER;
			bool bL_OMS_GMBL;
			bool bR_OMS_GMBL;

			void ET_SEP_INH( void );
			void MPS_CMD_X( void );
			void MPS_DATA_X( void );
			void MPS_ELEC_X( void );
			void MPS_HYD_X( void );
			void OTT_ST_IN( void );
			void ROLL_REF( void );
			void SSME_FAIL_X( void );
			void SW_TO_MEP( void );
			void DAP_DNMODE_RHC( void );
			void FCS_SAT_POS( void );
			void SPD_BRK( void );
			void PROBES( void );
			void TGT_DELTA_T( void );
			void TGT_EL_ANG( void );
			void TGT_ITER( void );
			void L_OMS_GMBL( void );
			void R_OMS_GMBL( void );

		public:
			explicit GAX( SimpleGPCSystem* _gpc );
			~GAX( void );

			void Realize( void ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_GAX_H_
