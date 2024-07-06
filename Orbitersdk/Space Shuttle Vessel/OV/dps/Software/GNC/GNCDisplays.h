/****************************************************************************
  This file is part of Space Shuttle Vessel

  Guidance Navigation and Control Displays definition


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
2020/03/20   GLS
2020/04/01   GLS
2020/04/28   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/07/03   GLS
2021/07/31   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/27   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/05/19   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/09/14   GLS
2022/10/27   GLS
2022/11/15   GLS
2022/12/23   GLS
2024/07/06   GLS
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
#ifndef _dps_GNCDISP_H_
#define _dps_GNCDISP_H_


#include "../GeneralDisplays.h"
#include <discsignals.h>


using namespace discsignals;


namespace dps
{
	class AscentDAP;
	class SRBSepSequence;
	class OMSBurnSoftware;
	class OrbitTgtSoftware;
	class StateVectorSoftware;
	class OrbitDAP;
	class MM801;

	class GNCDisplays:public GeneralDisplays
	{
		private:
			AscentDAP* pAscentDAP;
			SRBSepSequence* pSRBSepSequence;
			OMSBurnSoftware* pOMSBurnSoftware;
			OrbitTgtSoftware* pOrbitTgtSoftware;
			StateVectorSoftware* pStateVectorSoftware;
			OrbitDAP* pOrbitDAP;
			MM801* pMM801;

			DiscInPort LeftRHC[9];
			DiscInPort RightRHC[9];
			DiscInPort AftRHC[9];
			DiscInPort LeftRPTA[3];
			DiscInPort RightRPTA[3];

			void OnPaint_DISP18( CRT_Interface* crt ) const;
			void OnPaint_DISP19( CRT_Interface* crt ) const;
			void OnPaint_SPEC25( CRT_Interface* crt ) const;
			void OnPaint_SPEC42( CRT_Interface* crt ) const;
			void OnPaint_SPEC43( CRT_Interface* crt ) const;
			void OnPaint_SPEC44( CRT_Interface* crt ) const;
			void OnPaint_SPEC50( CRT_Interface* crt ) const;
			void OnPaint_SPEC51( CRT_Interface* crt ) const;
			void OnPaint_SPEC53( CRT_Interface* crt ) const;
			void OnPaint_SPEC55( CRT_Interface* crt ) const;
			void OnPaint_SPEC112( CRT_Interface* crt ) const;
			void OnPaint_SPEC113( CRT_Interface* crt ) const;
			void OnPaint_XXXXXXTRAJ1( CRT_Interface* crt ) const;
			void OnPaint_XXXXXXTRAJ2( CRT_Interface* crt ) const;
			void OnPaint_RTLSTRAJ2( CRT_Interface* crt ) const;
			void OnPaint_ENTRYTRAJ( CRT_Interface* crt ) const;
			void OnPaint_VERTSIT( CRT_Interface* crt ) const;

			void BackgroundData_DISP18( CRT_Interface* crt ) const;
			void BackgroundData_DISP19( CRT_Interface* crt ) const;
			void BackgroundData_SPEC25( CRT_Interface* crt ) const;
			void BackgroundData_SPEC42( CRT_Interface* crt ) const;
			void BackgroundData_SPEC43( CRT_Interface* crt ) const;
			void BackgroundData_SPEC44( CRT_Interface* crt ) const;
			void BackgroundData_SPEC50( CRT_Interface* crt ) const;
			void BackgroundData_SPEC51( CRT_Interface* crt ) const;
			void BackgroundData_SPEC53( CRT_Interface* crt ) const;
			void BackgroundData_SPEC55( CRT_Interface* crt ) const;
			void BackgroundData_SPEC112( CRT_Interface* crt ) const;
			void BackgroundData_SPEC113( CRT_Interface* crt ) const;
			void BackgroundData_XXXXXXTRAJ1( CRT_Interface* crt ) const;
			void BackgroundData_XXXXXXTRAJ2( CRT_Interface* crt ) const;
			void BackgroundData_RTLSTRAJ2( CRT_Interface* crt ) const;
			void BackgroundData_ENTRYTRAJ( CRT_Interface* crt ) const;
			void BackgroundData_VERTSIT( CRT_Interface* crt ) const;

			bool ItemInput_ENTRYTRAJ( int item, const char* Data );
			bool ItemInput_SPEC50( int item, const char* Data );
			bool ItemInput_SPEC51( int item, const char* Data );
			bool ItemInput_SPEC112( int item, const char* Data );
			bool ItemInput_SPEC113( int item, const char* Data );

			// item state lists for SPEC displays
			bool ITEM_STATE_SPEC112[32];
			bool ITEM_STATE_SPEC113[44];

			void SPEC25_SPEC43_printTHC( CRT_Interface* crt, bool axis_plus, bool axis_minus, int x, int y ) const;
			void SPEC25_SPEC43_printRHC_P( CRT_Interface* crt, double val, int x, int y ) const;
			void SPEC25_SPEC43_printRHC_RY( CRT_Interface* crt, double val, int x, int y ) const;
			void SPEC43_printRPTA( CRT_Interface* crt, double val, int x, int y ) const;

			unsigned short GetGPCLVLHVel( VECTOR3 &vel ) const;

		public:
			explicit GNCDisplays( SimpleGPCSystem* _gpc );
			~GNCDisplays( void );

			void Realize( void ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			/**
			 * Handles Item entry on shuttle's keyboard.
			 * Returns true if input OK, false for illegal entry.
			 * @param spec spec currently displayed
			 * @param item ITEM number
			 * @param Data string containing data entered
			 */
			bool ItemInput( int spec, int item, const char* Data ) override;

			/**
			 * Draws display on MDU.
			 */
			void Paint( CRT_Interface* crt, unsigned short page ) const override;

			/**
			 * Draws display on MDU.
			 */
			void PaintBackground( CRT_Interface* crt, unsigned short page ) const override;
	};
}


#endif// _dps_GNCDISP_H_
