/****************************************************************************
  This file is part of Space Shuttle Vessel

  System Displays definition


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
2022/08/18   GLS
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
#ifndef _dps_SYSDISP_H_
#define _dps_SYSDISP_H_


#include "GeneralDisplays.h"


namespace dps
{
	class SystemDisplays:public GeneralDisplays
	{
		private:
			// Data for SPEC0/OPS000
			unsigned char engunit_hex;// 0 = hex, otherwise eng unit
			bool addidvalid[6];
			unsigned int addid[6];

			void OnPaint_GPCMEMORY( CRT_Interface* crt ) const;
			void OnPaint_SPEC2( CRT_Interface* crt ) const;
			void OnPaint_DISP6( CRT_Interface* crt ) const;
			void OnPaint_DISP99( CRT_Interface* crt ) const;

			void BackgroundData_GPCMEMORY( CRT_Interface* crt ) const;
			void BackgroundData_SPEC2( CRT_Interface* crt ) const;
			void BackgroundData_DISP6( CRT_Interface* crt ) const;
			void BackgroundData_DISP99( CRT_Interface* crt ) const;

			bool ItemInput_GPCMEMORY( int item, const char* Data );
			bool ItemInput_SPEC2( int item, const char* Data );

			double GetConversionParameter( unsigned char engunit ) const;

		public:
			explicit SystemDisplays( SimpleGPCSystem* _gpc );
			~SystemDisplays( void );

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


#endif// _dps_SYSDISP_H_
