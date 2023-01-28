/****************************************************************************
  This file is part of Space Shuttle Vessel

  CCTV Camera mounted on Pan/Tilt Unit definition


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
#ifndef __CCTV_CAMERA_PTU_H
#define __CCTV_CAMERA_PTU_H


#include "CCTVCamera.h"
#include <VesselAPI.h>


inline constexpr char MESHNAME_CCTV_CAMERA_PTU[] = "SSV\\CCTVCameraPTU";


class CCTVCameraPTU : public CCTVCamera
{
	private:
		MGROUP_ROTATE* CAMERAZO;
		MGROUP_ROTATE* CAMERAXO;
		UINT anim_Zo;
		UINT anim_Xo;
		UINT anim_Pan;
		UINT anim_Tilt;
		UINT PanGrp;
		UINT TiltGrp;

		const double panmax;// [deg]
		const double panmin;// [deg]
		const double tiltmax;// [deg]
		const double tiltmin;// [deg]
		const double pantiltlowrate;// [deg/s]
		const double pantilthighrate;// [deg/s]

		VECTOR3 pan_axis;
		VECTOR3 tilt_axis;

		// dummy vectors for base camera orientation animation
		VECTOR3 dummyzo;
		VECTOR3 dummyxo;

	public:
		CCTVCameraPTU( VESSEL* const v, const VECTOR3& pos, const std::string& meshname = MESHNAME_CCTV_CAMERA_PTU );
		virtual ~CCTVCameraPTU( void );

		void TimeStep( const double dt );

		/**
		 * @param rotZo		base camera rotation on Zo axis [deg]
		 * @param rotXo		base camera rotation on Xo axis [deg]
		 * @param baseparent	base animation component handle
		 * @param pan_grp	mesh group index for pan animation
		 * @param tilt_grp	mesh group index for tilt animation
		 */
		void DefineAnimations( const double rotZo, const double rotXo, const ANIMATIONCOMPONENT_HANDLE baseparent, const UINT pan_grp, const UINT tilt_grp );
};

#endif// __CCTV_CAMERA_PTU_H
