/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A13 definition



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
#ifndef __VC_PANELA13_H
#define __VC_PANELA13_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class RotarySwitchPotentiometer;


	class PanelA13 : public AtlantisPanel
	{
		private:
			StdSwitch3* pGPS_PRE_AMP_LC;
			StdSwitch3* pGPS_PRE_AMP_UC;
			StdSwitch2* pS14;
			StdSwitch2* pS15;
			StdSwitch3* pS16;
			StdSwitch3* pS17;
			StdSwitch3* pOS_AUDIO_SPKR_PWR;

			RotarySwitchPotentiometer* pOS_AUDIO_MASTER_SPEAKER_VOLUME;

			SURFHANDLE hOV099Texture;

			bool OV099;

		public:
			PanelA13( Atlantis* _sts, const std::string& ov );
			virtual ~PanelA13( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
			void VisualCreated( void ) override;
	};
}

#endif// __VC_PANELA13_H
