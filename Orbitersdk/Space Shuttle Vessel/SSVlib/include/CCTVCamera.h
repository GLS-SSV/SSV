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


#include "VideoSource.h"
#include <VesselAPI.h>
#include "discsignals.h"


inline constexpr char MESHNAME_CCTV_CAMERA[] = "SSV\\CCTVCamera";


class CCTVCamera : public VideoSource
{
	private:
		MGROUP_ROTATE* CAMERAZO;
		MGROUP_ROTATE* CAMERAYO;
		UINT anim_Zo;
		UINT anim_Yo;

	protected:
		discsignals::DiscInPort dipPowerOnOff;
		discsignals::DiscInPort dipPower;
		discsignals::DiscInPort dipHeater;

		VESSEL* v;
		UINT mesh_idx;

		bool PanLeftCmd;
		bool PanRightCmd;
		bool TiltUpCmd;
		bool TiltDownCmd;
		bool PanTiltCtrlClk;// HACK set = fast, no set = slow
		bool ZoomInCmd;
		bool ZoomOutCmd;


		VECTOR3 dir0;// base camera direction
		VECTOR3 top0;// base top direction
		VECTOR3 pos;// current camera position
		VECTOR3 dir;// current camera direction
		VECTOR3 top;// current top direction
		double zoom;// horizontal FOV [deg]
		double pan;// [deg]
		double tilt;// [deg]
		const double zoommax;// [deg]
		const double zoommin;// [deg]
		const double zoomrate;// [deg/s]

	public:
		CCTVCamera( VESSEL* const v, const VECTOR3& pos, const char* meshname = MESHNAME_CCTV_CAMERA );
		virtual ~CCTVCamera( void );

		virtual void LoadState( const char* line );
		virtual void SaveState( char* line ) const;

		void TimeStep( const double dt );

		/**
		 * @param rotZo		base camera rotation on Zo axis [deg]
		 * @param rotYo		base camera rotation on Yo axis [deg]
		 * @param baseparent	base animation component handle
		 */
		void DefineAnimations( const double rotZo, const double rotYo );

		virtual void SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout ) override;
		virtual bool GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom, double& pan, double& tilt ) const override;

		/**
		 * Sets camera physical base parameters (pan and tilt = 0º).
		 * @param pos	camera position
		 * @param dir	camera direction
		 * @param top	top direction
		 **/
		void SetPhysicalParams( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top );
		void ConnectPowerOnOff( discsignals::DiscreteBundle* Bundle, const unsigned short OnOff );
		void ConnectPowerCameraPTU( discsignals::DiscreteBundle* Bundle, const unsigned short Camera_PTU );
		void ConnectPowerHeater( discsignals::DiscreteBundle* Bundle, const unsigned short Heater );
};

#endif// __CCTV_CAMERA_H
