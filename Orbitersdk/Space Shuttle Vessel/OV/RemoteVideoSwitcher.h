/****************************************************************************
  This file is part of Space Shuttle Vessel

  Remote Video Switcher definition


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
#ifndef __REMOTEVIDEOSWITCHER_H
#define __REMOTEVIDEOSWITCHER_H


#include <VideoSource.h>
#include "Atlantis.h"
#include "discsignals.h"


class RemoteVideoSwitcher : public VideoSource
{
	private:
		VideoSource* Elbow;
		VideoSource* Wrist;

		discsignals::DiscInPort dipSelWrist;

		discsignals::DiscInPort dipPowerOnOff;
		discsignals::DiscOutPort dopPowerOnOffElbow;
		discsignals::DiscOutPort dopPowerOnOffWrist;

	public:
		RemoteVideoSwitcher( const bool portside, VideoSource* Elbow, VideoSource* Wrist, Atlantis* sts );
		virtual ~RemoteVideoSwitcher( void );

		void TimeStep( void );
		virtual void SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout ) override;
		virtual bool GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom, double& pan, double& tilt ) const override;

		void ConnectPowerOnOff( discsignals::DiscreteBundle* Bundle, const unsigned short OnOff );
		void ConnectSelSwitch( discsignals::DiscreteBundle* Bundle, const unsigned short portWrist );
};

#endif// __REMOTEVIDEOSWITCHER_H
