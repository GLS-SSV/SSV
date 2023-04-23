/****************************************************************************
  This file is part of Space Shuttle Vessel

  Video Source interface definition


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
#ifndef __VIDEOSOURCE_H
#define __VIDEOSOURCE_H


#include <OrbiterAPI.h>


class VideoSource
{
	public:
		/**
		 * Commands camera and PTU (sync/cmd input).
		 * @param panleft	pan left command signal
		 * @param panright	pan right command signal
		 * @param tiltup	tilt up command signal
		 * @param tiltdown	tilt down command signal
		 * @param pantiltclk	pan/tilt control clock signal (HACK set = fast, not set = slow)
		 * @param zoomin	zoom in command signal
		 * @param zoomout	zoom out command signal
		 **/
		virtual void SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout ) = 0;

		/**
		 * Returns needed information to VSU for video image generation (video output).
		 * @param pos	camera position [m]
		 * @param dir	camera lens direction [1]
		 * @param top	camera top direction [1]
		 * @param zoom	camera field of view [deg]
		 * @param pan	PTU pan angle [deg]
		 * @param tilt	PTU tilt angle [deg]
		 * @return	validity
		 **/
		virtual bool GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom, double& pan, double& tilt ) const = 0;
};

#endif// __VIDEOSOURCE_H
