/****************************************************************************
  This file is part of Space Shuttle Vessel

  Speedbrake/Thrust Controller Subsystem Operating Program definition


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
2020/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/11/15   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Speedbrake/Thrust Controller Subsystem Operating Program definition



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
#ifndef _dps_SBTC_SOP_H_
#define _dps_SBTC_SOP_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	class SBTC_RM;
	class SSME_SOP;

	/**
	 * @brief	Implementation of the SBTC SOP software that runs in the GPCs.
	 *
	 * This class receives and processes SBTC commands.
	 */
	class SBTC_SOP:public SimpleGPCSoftware
	{
		private:
			SBTC_RM* pSBTC_RM;
			SSME_SOP* pSSME_SOP;

			bool MAN_THROTTLE;
			bool MAN_THROTTLE_ACTIVE;
			double MAN_THROTTLE_COMMAND;

			bool CDR_TAKEOVER;
			bool PLT_TAKEOVER;
			double MAN_SPEEDBRAKE_COMMAND;// [deg]
			bool CDR_DATA;

			void ManSpeedbrake( void );
			void ManThrottle( void );

		public:
			explicit SBTC_SOP( SimpleGPCSystem* _gpc );
			~SBTC_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			bool GetManThrottle( void ) const;
			double GetManThrottleCommand( void ) const;

			bool GetCDRTakeover( void ) const;
			bool GetPLTTakeover( void ) const;

			/**
			 * Outputs manual commanded speedbrake position in degrees.
			 */
			double GetManSpeedbrakeCommand( void ) const;
	};
}


#endif// _dps_SBTC_SOP_H_
