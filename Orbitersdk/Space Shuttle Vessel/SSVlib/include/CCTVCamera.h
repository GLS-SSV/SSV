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


class CCTVCamera : public VideoSource
{
	private:
		MGROUP_ROTATE* CAMERAZO;
		MGROUP_ROTATE* CAMERAYO;
		UINT anim_Zo;
		UINT anim_Yo;

		// dummy vector for base camera orientation animation
		VECTOR3 dummyzo;

	protected:
		discsignals::DiscInPort dipPowerOnOff;
		discsignals::DiscInPort dipPower;
		discsignals::DiscInPort dipHeater;

		VESSEL4* v;

		bool PanLeftCmd;
		bool PanRightCmd;
		bool TiltUpCmd;
		bool TiltDownCmd;
		bool PanTiltCtrlClk;// HACK set = fast, not set = slow
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
		/**
		 * Constructor for CCTVCamera class.
		 * @param v		pointer to VESSEL4 class
		 * @param pos	camera position
		 */
		CCTVCamera( VESSEL4* const v, const VECTOR3& pos );
		virtual ~CCTVCamera( void );

		/**
		 * Loads camera state (zoom).
		 * @param line	pointer to camera state string
		 */
		virtual void LoadState( const char* line );
		/**
		 * Saves camera state (zoom).
		 * @param line	pointer to camera state string
		 */
		virtual void SaveState( char* line ) const;

		/**
		 * Updates camera state.
		 * @param dt	interval from last time step [s]
		 */
		virtual void TimeStep( const double dt );

		/**
		 * Defines initial camera orientation and rotates camera mesh. Used when camera mesh is pointing along the +Xo axis.
		 * @param mesh_idx	camera mesh handle for rotation
		 * @param rotZo		base camera rotation on Zo axis [deg]
		 * @param rotYo		base camera rotation on Yo axis [deg]
		 */
		virtual void DefineAnimations( const UINT mesh_idx, const double rotZo, const double rotYo );
		/**
		 * Defines initial camera orientation. Used when camera mesh is already correctly oriented.
		 * @param rotZo		base camera rotation on Zo axis [deg]
		 * @param rotYo		base camera rotation on Yo axis [deg]
		 */
		void DefineAnimations( const double rotZo, const double rotYo );

		/**
		 * Commands camera and PTU (sync/cmd input).
		 * @param panleft	pan left command signal
		 * @param panright	pan right command signal
		 * @param tiltup	tilt up command signal
		 * @param tiltdown	tilt down command signal
		 * @param pantiltclk	pan/tilt control clock signal (HACK set = fast, not set = slow)
		 * @param zoomin	zoom in command signal
		 * @param zoomout	zoom out command signal
		 */
		virtual void SetCommands( const bool panleft, const bool panright, const bool tiltup, const bool tiltdown, const bool pantiltclk, const bool zoomin, const bool zoomout ) override;
		/**
		 *  Returns needed information to VSU for video image generation (video output).
		 * @param pos	camera position [m]
		 * @param dir	camera lens direction [1]
		 * @param top	camera top direction [1]
		 * @param zoom	camera field of view [deg]
		 * @param pan	PTU pan angle (0 for non-PTU cameras) [deg]
		 * @param tilt	PTU tilt angle (0 for non-PTU cameras) [deg]
		 * @return	true if camera powered up (data valid), false otherwise
		 */
		virtual bool GetPhysicalData( VECTOR3& pos, VECTOR3& dir, VECTOR3& top, double& zoom, double& pan, double& tilt ) const override;

		/**
		 * Sets camera physical base parameters (pan and tilt = 0º).
		 * @param pos	camera position
		 * @param dir	camera direction
		 * @param top	top direction
		 **/
		virtual void SetPhysicalParams( const VECTOR3& pos, const VECTOR3& dir, const VECTOR3& top );
		/**
		 * Connects Camera power on/off indication.
		 * @param Bundle	pointer to DiscreteBundle
		 * @param Line		DiscreteBundle line index
		 */
		void ConnectPowerOnOff( discsignals::DiscreteBundle* Bundle, const unsigned short Line );
		/**
		 * Connects Camera and PTU power.
		 * @param Bundle	pointer to DiscreteBundle
		 * @param Line		DiscreteBundle line index
		 */
		void ConnectPowerCameraPTU( discsignals::DiscreteBundle* Bundle, const unsigned short Line );
		/**
		 * Connects Camera heater power.
		 * @param Bundle	pointer to DiscreteBundle
		 * @param Line		DiscreteBundle line index
		 */
		void ConnectPowerHeater( discsignals::DiscreteBundle* Bundle, const unsigned short Line );
};

#endif// __CCTV_CAMERA_H
