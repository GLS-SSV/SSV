/****************************************************************************
  This file is part of Space Shuttle Vessel

  CCTV Camera definition


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
#ifndef __CCTV_CAMERA_H
#define __CCTV_CAMERA_H


#include <BasicCamera.h>
#include "Atlantis.h"


class CCTVCamera : public BasicCamera
{
	private:
		Atlantis* sts;
		UINT anim_Zo;
		UINT anim_Yo;
		MESHHANDLE hMesh;
		UINT mesh_idx;

	public:
		CCTVCamera( Atlantis* const sts, const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top );
		virtual ~CCTVCamera( void );

		void TimeStep( const double dt );
		void AddMesh( void );
		void DefineAnimations( const double rotZo, const double rotYo, const ANIMATIONCOMPONENT_HANDLE baseparent );
};

#endif// __CCTV_CAMERA_H
