/****************************************************************************
  This file is part of Space Shuttle Vessel

  Entry Area Navigation definition


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

#ifndef _dps_ENT_AREA_NAV_H_
#define _dps_ENT_AREA_NAV_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ENT_AREA_NAV:public SimpleGPCSoftware
	{
		private:
			unsigned short FIRST_PASS;
			unsigned short LEFT_SIDE;
			unsigned short IGS;
			unsigned short MASS_FLAG;
			unsigned short OVHD_LAST;
			float P;// +1 = right; -1 = left
			float ARC_LEFT;
			float ARC_RIGHT;
			float RTURN_HSI_LEFT;
			float RTURN_HSI_RIGHT;
			float ALT_LAND;
			float X_GSI;
			VECTOR3 R_VEH_EF;
			VECTOR3 R_VEH_RW;
			float DELX_NEP;
			float DELX_REF;
			float DELX_MEP;
			float X_EP;
			float PSD_HSI;
			float V_HSI;
			float VH_HSI;
			double H;
			float C0[2][2];
			float C1[2][2];
			float C2[2][2];
			float C3[2][2];
			float CUBRC[2];
			float HCO[2];
			float HMEP[2];

			unsigned short N;
			unsigned short SOURCE;
			unsigned short MODE;
			unsigned short RCVR;

			float PRI_BEAR;
			float PRI_RANGE;
			float CDI;
			float GSI;
			float HEADING;
			unsigned short HSI_MODE_INDICATOR;
			unsigned short BRG_FLAG;
			unsigned short GSI_FLAG;
			unsigned short CDI_FLAG;
			float SEC_BEAR;
			float SEC_RANGE;

			double PHAVGC;
			double PHAVGS;
			double PHAVGLL;
			double PHAVGUL;

			unsigned short FIRST_PASS_TAEM;

			void HSI_SEQUENCER( void );
			void NAV_STATE_TO_RW( void );
			void TAC_BARO_TO_RW( void );
			void TAC_BARO_TO_TOPODETIC( void );
			void GPS_TO_RW( void );
			void MSBLS_TO_RW( void );
			void ENTRY_HSI_COMP( void );
			void TAEM_HSI_COMP( void );
			void LAND_HSI_COMP( void );
			void RANGE_BEAR_TO_HAC_ENTRY( const VECTOR3& R_CC_EF, const float R_CC_MAG, const unsigned short OVHD, const float P, const float R_VEH_MAG, const VECTOR3& R_VEH_EF, const float AZIMUTH_RW, const float ANGLE_CORR_TNTOMAG_RW, float& RANGE, float& BEARING );

		public:
			explicit ENT_AREA_NAV( SimpleGPCSystem* _gpc );
			~ENT_AREA_NAV( void );

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
			bool OnMajorModeChange( unsigned int newMajorMode ) override;
			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
	};
}

#endif// _dps_ENT_AREA_NAV_H_
