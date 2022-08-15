/****************************************************************************
  This file is part of Space Shuttle Vessel

  Rotational Hand Controller Subsystem Operating Program definition


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
#ifndef _dps_RHC_SOP_H_
#define _dps_RHC_SOP_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	class RHC_RM;

	/**
	 * @brief	Implementation of the RHC SOP software that runs in the GPCs.
	 *
	 * This class receives and processes RHC commands.
	 */
	class RHC_SOP:public SimpleGPCSoftware
	{
		private:
			RHC_RM* pRHC_RM;

			bool FCS_MAN_TAKEOVER_PITCH;
			bool FCS_MAN_TAKEOVER_ROLL;
			bool FCS_MAN_TAKEOVER_YAW;

			bool DETENT_PITCH;
			bool DETENT_ROLL;
			bool DETENT_YAW;

			bool PAST_SOFTSTOP_PITCH;
			bool PAST_SOFTSTOP_ROLL;
			bool PAST_SOFTSTOP_YAW;

			double RHC_P;
			double RHC_R;
			double RHC_Y;

			void TwoAxis( void );
			void ThreeAxis( void );

		public:
			explicit RHC_SOP( SimpleGPCSystem* _gpc );
			~RHC_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			double GetPitchCommand( void ) const;
			double GetRollCommand( void ) const;
			double GetYawCommand( void ) const;

			bool GetPitchManTakeOver( void ) const;
			bool GetRollManTakeOver( void ) const;
			bool GetYawManTakeOver( void ) const;

			bool GetPitchDetent( void ) const;
			bool GetRollDetent( void ) const;
			bool GetYawDetent( void ) const;

			bool GetPitchPastSoftStop( void ) const;
			bool GetRollPastSoftStop( void ) const;
			bool GetYawPastSoftStop( void ) const;
	};
}


#endif// _dps_RHC_SOP_H_