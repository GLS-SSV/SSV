/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel A13 (OV-102) definition



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
#ifndef __VC_PANELA13_102_H
#define __VC_PANELA13_102_H


#include "AtlantisPanel.h"


namespace vc
{
	class StdSwitch2;
	class StdSwitch3;
	class ThumbWheel;
	class RotarySwitchPotentiometer;
	class RotaryDemuxSwitch;


	class PanelA13_102 : public AtlantisPanel
	{
		private:
			StdSwitch2* pOS_AUDIO_PAGE;

			StdSwitch3* pOS_AUDIO_POWER;
			StdSwitch3* pOS_AUDIO_AG_1;
			StdSwitch3* pOS_AUDIO_AG_2;
			StdSwitch3* pOS_AUDIO_AA;
			StdSwitch3* pOS_AUDIO_ICOM_A;
			StdSwitch3* pOS_AUDIO_ICOM_B;
			StdSwitch3* pOS_AUDIO_SPKR_PWR;

			RotarySwitchPotentiometer* pOS_AUDIO_VOX_SENSE;
			RotarySwitchPotentiometer* pOS_AUDIO_MASTER_SPEAKER_VOLUME;
			RotaryDemuxSwitch* pOS_AUDIO_XMIT_ICOM_MODE;

			ThumbWheel* pOS_AUDIO_VOLUME_AG_1;
			ThumbWheel* pOS_AUDIO_VOLUME_AG_2;
			ThumbWheel* pOS_AUDIO_VOLUME_AA;
			ThumbWheel* pOS_AUDIO_VOLUME_ICOM_A;
			ThumbWheel* pOS_AUDIO_VOLUME_ICOM_B;

		public:
			explicit PanelA13_102( Atlantis* _sts );
			virtual ~PanelA13_102( void );

			void DefineVC( void ) override;
			void RegisterVC( void ) override;
			void Realize( void ) override;
	};
}

#endif// __VC_PANELA13_102_H
