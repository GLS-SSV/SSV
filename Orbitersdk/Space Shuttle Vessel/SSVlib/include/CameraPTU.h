/****************************************************************************
  This file is part of Space Shuttle Vessel

  Camera mounted on Pan/Tilt Unit definition


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
#ifndef __CAMERA_PTU_H
#define __CAMERA_PTU_H


#include "BasicCamera.h"


class CameraPTU : public BasicCamera
{
	protected:
		discsignals::DiscInPort PanLeftCmd;
		discsignals::DiscInPort PanRightCmd;
		discsignals::DiscInPort TiltUpCmd;
		discsignals::DiscInPort TiltDownCmd;
		discsignals::DiscInPort PanTiltCtrlClk;// HACK set = fast, no set = slow

		double pan;// [deg]
		const double panmax;// [deg]
		const double panmin;// [deg]
		double tilt;// [deg]
		const double tiltmax;// [deg]
		const double tiltmin;// [deg]
		const double pantiltlowrate;// [deg/s]
		const double pantilthighrate;// [deg/s]

	public:
		CameraPTU( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top, const double zoomrate, const double zoommax, const double zoommin, const double panmax, const double panmin, const double tiltrate, const double tiltmax, const double pantiltlowrate, const double pantilthighrate );
		virtual ~CameraPTU( void );

		void Connect( discsignals::DiscreteBundle* bundle, const unsigned short panleft, const unsigned short panright, const unsigned short tiltup, const unsigned short tiltdown, const unsigned short pantiltctr );
		void TimeStep( const double dt );
};

#endif// __CAMERA_PTU_H
