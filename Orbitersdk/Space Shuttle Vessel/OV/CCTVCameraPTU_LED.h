/****************************************************************************
  This file is part of Space Shuttle Vessel

  CCTV Camera mounted on Pan/Tilt Unit with LED illuminator definition


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
#ifndef __CCTV_CAMERA_PTU_LED_H
#define __CCTV_CAMERA_PTU_LED_H


#include <CCTVCameraPTU.h>
#include "Atlantis.h"


class ExternalLight;


class CCTVCameraPTU_LED : public CCTVCameraPTU
{
	private:
		VECTOR3 posLED;

		ExternalLight* light;

	public:
		CCTVCameraPTU_LED( Atlantis* sts, const VECTOR3& pos );
		virtual ~CCTVCameraPTU_LED( void );

		void TimeStep( const double dt ) override;
		void VisualCreated( void );
		void ConnectPowerPTUHeater( discsignals::DiscreteBundle* Bundle, const unsigned short Heater ) override;
		void DefineMeshGroup( UINT _mesh, UINT _grpIndex );
};

#endif// __CCTV_CAMERA_PTU_LED_H
