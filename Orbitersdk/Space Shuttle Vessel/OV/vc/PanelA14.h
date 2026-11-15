/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A14 definition



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
#ifndef __VC_PANELA14_H
#define __VC_PANELA14_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class LockableLever2;
	class LockableLever3;
	class StandardSwitchCover;


	class PanelA14 : public AtlantisPanel
	{
		private:
			StdSwitch3* pRCSOMS_HEATERS_FWD_RCS;
			StdSwitch2* pRCSOMS_HEATERS_LEFT_POD_A;
			StandardSwitchCover* pRCSOMS_HEATERS_LEFT_POD_A_Cover;
			StdSwitch2* pRCSOMS_HEATERS_LEFT_POD_B;
			StandardSwitchCover* pRCSOMS_HEATERS_LEFT_POD_B_Cover;
			StdSwitch2* pRCSOMS_HEATERS_RIGHT_POD_A;
			StandardSwitchCover* pRCSOMS_HEATERS_RIGHT_POD_A_Cover;
			StdSwitch2* pRCSOMS_HEATERS_RIGHT_POD_B;
			StandardSwitchCover* pRCSOMS_HEATERS_RIGHT_POD_B_Cover;

			StdSwitch2* pRCSOMS_HEATERS_FWD_RCS_JET_1;
			StdSwitch2* pRCSOMS_HEATERS_FWD_RCS_JET_2;
			StdSwitch2* pRCSOMS_HEATERS_FWD_RCS_JET_3;
			StdSwitch2* pRCSOMS_HEATERS_FWD_RCS_JET_4;
			StdSwitch2* pRCSOMS_HEATERS_FWD_RCS_JET_5;

			StdSwitch2* pRCSOMS_HEATERS_AFT_RCS_JET_1;
			StdSwitch2* pRCSOMS_HEATERS_AFT_RCS_JET_2;
			StdSwitch2* pRCSOMS_HEATERS_AFT_RCS_JET_3;
			StdSwitch2* pRCSOMS_HEATERS_AFT_RCS_JET_4;
			StdSwitch2* pRCSOMS_HEATERS_AFT_RCS_JET_5;

			StdSwitch3* pRCSOMS_HEATERS_OMS_KIT;
			StdSwitch2* pRCSOMS_HEATERS_OMS_CRSFD_LINES_A;
			StdSwitch2* pRCSOMS_HEATERS_OMS_CRSFD_LINES_B;

			LockableLever2* pPYRO_KU_ANT_ARM;
			LockableLever2* pPYRO_KU_ANT_JETT;

			LockableLever3* pPYRO_STARBOARD_RMS_ARM;
			LockableLever3* pPYRO_STARBOARD_RMS_SHLDR;
			LockableLever3* pPYRO_STARBOARD_RMS_LATCHES_FWD;
			LockableLever3* pPYRO_STARBOARD_RMS_LATCHES_MID;
			LockableLever3* pPYRO_STARBOARD_RMS_LATCHES_AFT;

			LockableLever3* pPYRO_PORT_RMS_ARM;
			LockableLever3* pPYRO_PORT_RMS_SHLDR;
			LockableLever3* pPYRO_PORT_RMS_LATCHES_FWD;
			LockableLever3* pPYRO_PORT_RMS_LATCHES_MID;
			LockableLever3* pPYRO_PORT_RMS_LATCHES_AFT;

			LockableLever3* pRMS_LATCHES;
			
			StandardSwitchCover* pPYRO_Cover;

			StdSwitch3* pCARGO_COOLANT_LOOP_HEATERS_ORBITER_A;
			StdSwitch3* pCARGO_COOLANT_LOOP_HEATERS_ORBITER_B;
			StdSwitch3* pCARGO_COOLANT_LOOP_HEATERS_ORBITER_C;
			StdSwitch2* pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_A;
			StdSwitch2* pCARGO_COOLANT_LOOP_HEATERS_CARGO_LINE_B;

			SURFHANDLE hOV103105Texture;

			bool mplm;// MPLM cargo loop controls

		public:
			explicit PanelA14( Atlantis* _sts, const std::string &orbiter );
			virtual ~PanelA14( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void VisualCreated( void ) override;
	};
}

#endif// __VC_PANELA14_H
