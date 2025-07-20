/****************************************************************************
  This file is part of Space Shuttle Vessel

  2-Axis Rotational Hand Controller Subsystem Operating Program definition


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
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/04   GLS
2022/08/05   GLS
2022/12/23   GLS
2025/07/20   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Rotational Hand Controller Subsystem Operating Program definition



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
#ifndef _dps_2_AX_RHC_SOP_H_
#define _dps_2_AX_RHC_SOP_H_


#include "../SimpleGPCSoftware.h"
#include <MathSSV.h>


namespace dps
{
	static inline float DEADBAND( const float INPUT, const float DB )
	{
		float OUTPUT;

		if (fabs( INPUT ) <= DB)
		{
			OUTPUT = 0.0;
		}
		else
		{
			OUTPUT = INPUT - static_cast<float>(DB * sign( INPUT ));
		}
		return OUTPUT;
	}

	static inline void HYSTER_1( short& OUTPUT, const float INPUT, const float HI, const float LO )
	{
		double AI = fabs( INPUT );

		if (AI <= LO) OUTPUT = 0;
		else if (AI >= HI) OUTPUT = static_cast<short>(sign( INPUT ));

		return;
	}

	static inline void HYSTER_2( bool& OUTPUT, const float INPUT, const float HI, const float LO )
	{
		double AI = fabs( INPUT );

		if (AI <= LO) OUTPUT = false;
		else if (AI >= HI) OUTPUT = true;

		return;
	}


	class RHC_RM;

	/**
	 * @brief	Implementation of the 2-Axis RHC SOP software that runs in the GPCs.
	 *
	 * This class receives and processes RHC commands.
	 */
	class TWO_AX_RHC_SOP:public SimpleGPCSoftware
	{
		private:
			RHC_RM* pRHC_RM;

			bool ALERT1;
			bool ALERT2;

			float DACC;// compensated left roll [deg]
			float DAPC;// compensated right roll [deg]
			float DECC;// compensated left pitch [deg]
			float DEPC;// compensated right pitch [deg]

			float DACS;// validated left roll [deg]
			float DAPS;// validated right roll [deg]
			float DECS;// validated left pitch [deg]
			float DEPS;// validated right pitch [deg]

			float DACDB;// deadbanded left roll [deg]
			float DAPDB;// deadbanded right roll [deg]
			float DECDB;// deadbanded left pitch [deg]
			float DEPDB;// deadbanded right pitch [deg]

			void RHC_COMP( void );
			void RHC_DB( void );
			void RHC_DOWNMODE( void );
			void RHC_STA_SEL( void );
			void PAN_TRIM( void );
			void RHC_TRIM( void );

		public:
			explicit TWO_AX_RHC_SOP( SimpleGPCSystem* _gpc );
			~TWO_AX_RHC_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_2_AX_RHC_SOP_H_
