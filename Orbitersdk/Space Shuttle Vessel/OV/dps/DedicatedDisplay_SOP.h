/****************************************************************************
  This file is part of Space Shuttle Vessel

  Dedicated Display Subsystem Operating Program definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/10/09   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Dedicated Display Subsystem Operating Program definition



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
#ifndef _dps_DD_SOP_H_
#define _dps_DD_SOP_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	/**
	 * @brief	Implementation of the Dedicated Display SOP software that runs in the GPCs.
	 *
	 * This class processes and sends data to the HUD.
	 */
	class DedicatedDisplay_SOP:public SimpleGPCSoftware
	{
		private:
			double primarydistance;// [NM]
			double secondarydistance;// [NM]
			double primarybearing;// [deg]
			char primarybearingtype;
			double secondarybearing;// [deg]
			char secondarybearingtype;
			double coursedeviation;// [NM] or [deg]
			double coursedeviationscale;// [NM] or [deg]
			double glideslopedeviation;// [ft]
			double glideslopedeviationscale;// [ft]
			bool gsflag;


			unsigned short QuantizeUnsigned( double val, double minval, double maxval, unsigned int numbits ) const;

			void Output_ADI( void );
			void Output_HSI( void );
			void Output_AVVI( void );
			void Output_AMI( void );
			void Output_SPI( void );
			void Output_HUD( void );

			void Output_HSI_MEDS( void );

		public:
			explicit DedicatedDisplay_SOP( SimpleGPCSystem* _gpc );
			~DedicatedDisplay_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			/**
			 * Gets selected runway range (NM).
			 * @return	range in NM
			 */
			double GetSelectedRunwayRange( void ) const;

			/**
			 * Gets HAC center range (NM).
			 * @return	range in NM
			 */
			double GetHACCRange( void ) const;

			double GetPrimaryBearing( void ) const;
			char GetPrimaryBearingType( void ) const;

			double GetSecondaryBearing( void ) const;
			char GetSecondaryBearingType( void ) const;

			double GetCourseDeviation( void ) const;

			double GetCourseDeviationScale( void ) const;

			double GetGlideSlopeDeviation( void ) const;

			double GetGlideSlopeDeviationScale( void ) const;

			bool GetGSFlag( void ) const;
	};
}

#endif// _dps_DD_SOP_H_
