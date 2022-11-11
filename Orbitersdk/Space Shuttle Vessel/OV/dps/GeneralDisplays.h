/****************************************************************************
  This file is part of Space Shuttle Vessel

  General Displays definition


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
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/08/18   GLS
2022/09/14   GLS
2022/10/27   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  General Displays definition



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
#ifndef _dps_GENDISP_H_
#define _dps_GENDISP_H_


#include "SimpleGPCSoftware.h"
#include <discsignals.h>


using namespace discsignals;


namespace dps
{
	class AscentDAP;
	class SRBSepSequence;

	class GeneralDisplays:public SimpleGPCSoftware
	{
		private:
			AscentDAP* pAscentDAP;
			SRBSepSequence* pSRBSepSequence;

			DiscInPort dipBFCCRTDisplay;
			DiscInPort dipBFCCRTSelect[2];

			DiscInPort dipLO2UllagePressureSensor[3];
			DiscInPort dipLH2UllagePressureSensor[3];

			DiscInPort dipHeSysPressureSensor[12];
			DiscInPort dipMPSManifPressureSensor[2];

			DiscInPort LeftRHC[9];
			DiscInPort RightRHC[9];
			DiscInPort AftRHC[9];
			DiscInPort LeftRPTA[3];
			DiscInPort RightRPTA[3];
			DiscInPort LeftSBTC[3];
			DiscInPort RightSBTC[3];

			double He_dPdT[3];
			double He_P[3];
			double He_T;

			/**
			 * Data for ENTRY TRAJ and VERT SIT displays.
			 */
			unsigned short CurrentET;
			double ET_History_updatetime;
			int ET_History_X[6];
			int ET_History_X_Drag[6];
			int ET_History_Y[6];


			// Data for SPEC0/OPS000
			unsigned char engunit_hex;// 0 = hex, otherwise eng unit
			bool addidvalid[6];
			unsigned int addid[6];

			// PASS displays
			void OnPaint_GPCMEMORY_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC2_PASS( vc::MDU* pMDU ) const;
			void OnPaint_DISP18_PASS( vc::MDU* pMDU ) const;
			void OnPaint_DISP19_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC25_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC42_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC43_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC44_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC50_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC51_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC53_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC55_PASS( vc::MDU* pMDU ) const;
			void OnPaint_DISP99_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC112_PASS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC113_PASS( vc::MDU* pMDU ) const;
			void OnPaint_LAUNCHTRAJ1_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ASCENTTRAJ1_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ASCENTTRAJ2_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ENTRYTRAJ1_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ENTRYTRAJ2_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ENTRYTRAJ3_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ENTRYTRAJ4_PASS( vc::MDU* pMDU ) const;
			void OnPaint_ENTRYTRAJ5_PASS( vc::MDU* pMDU ) const;
			void OnPaint_VERTSIT1_PASS( vc::MDU* pMDU ) const;
			void OnPaint_VERTSIT2_PASS( vc::MDU* pMDU ) const;

			bool ItemInput_GPCMEMORY( int item, const char* Data, bool &IllegalEntry );
			bool ItemInput_ENTRYTRAJ( int item, const char* Data, bool &IllegalEntry );
			bool ItemInput_SPEC2( int item, const char* Data, bool &IllegalEntry );
			bool ItemInput_SPEC50( int item, const char* Data, bool &IllegalEntry );
			bool ItemInput_SPEC51( int item, const char* Data, bool &IllegalEntry );
			void ItemInput_SPEC112( int item, const char* Data, bool &IllegalEntry );
			void ItemInput_SPEC113( int item, const char* Data, bool &IllegalEntry );

			// BFS dislays
			void OnPaint_DISP18_BFS( vc::MDU* pMDU ) const;
			void OnPaint_DISP19_BFS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC51_BFS( vc::MDU* pMDU ) const;
			void OnPaint_SPEC55_BFS( vc::MDU* pMDU ) const;
			void OnPaint_DISP99_BFS( vc::MDU* pMDU ) const;

			// item state lists for SPEC displays
			bool ITEM_STATE_SPEC112[32];
			bool ITEM_STATE_SPEC113[44];

			void SPEC25_SPEC43_printTHC( vc::MDU* pMDU, bool axis_plus, bool axis_minus, int x, int y ) const;
			void SPEC25_SPEC43_printRHC_P( vc::MDU* pMDU, double val, int x, int y ) const;
			void SPEC25_SPEC43_printRHC_RY( vc::MDU* pMDU, double val, int x, int y ) const;
			void SPEC43_printRPTA( vc::MDU* pMDU, double val, int x, int y ) const;
			void ENTRYTRAJ_PrintTrimGuidanceParams( vc::MDU* pMDU, double NY, double DRTI, double DATRIM, double DRTRIM, double DLRDOT, double RDTREF, double ROLLREF, double ROLLCMD ) const;
			double GetConversionParameter( unsigned char engunit ) const;

			unsigned short GetGPCLVLHVel( VECTOR3 &vel ) const;

		public:
			explicit GeneralDisplays( SimpleGPCSystem* _gpc );
			~GeneralDisplays( void );

			void Realize() override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			bool ItemInput( int spec, int item, const char* Data, bool &IllegalEntry ) override;

			bool OnPaint( int spec, vc::MDU* pMDU ) const override;
	};
}


#endif// _dps_GENDISP_H_