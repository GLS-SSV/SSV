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


class CCTVCameraPTU : public CCTVCamera
{
	private:
		discsignals::DiscInPort dipPTUHeater;

		MGROUP_ROTATE* CAMERAZO;
		MGROUP_ROTATE* CAMERAXO;
		MGROUP_ROTATE* CAMERAPAN;
		MGROUP_ROTATE* CAMERATILT;
		UINT anim_Zo;
		UINT anim_Xo;
		UINT anim_Pan;
		UINT anim_Tilt;

		const double panmax;// [deg]
		const double panmin;// [deg]
		const double tiltmax;// [deg]
		const double tiltmin;// [deg]
		const double pantiltlowrate;// [deg/s]
		const double pantilthighrate;// [deg/s]

		// dummy vectors for base camera orientation animation
		VECTOR3 dummyzo;
		VECTOR3 dummyxo;

		void Update( void );

	public:
		/**
		 * Constructor for CCTVCameraPTU class.
		 * @param v	pointer to VESSEL4 class
		 * @param pos	camera position
		 */
		CCTVCameraPTU( VESSEL4* const v, const VECTOR3& pos );
		virtual ~CCTVCameraPTU( void );

		/**
		 * Loads camera state (pan, tilt, zoom).
		 * @param line	pointer to camera state string
		 */
		void LoadState( const char* line ) override;
		/**
		 * Saves camera state (pan, tilt, zoom).
		 * @param line	pointer to camera state string
		 */
		void SaveState( char* line ) const override;

		/**
		 * Updates camera state.
		 * @param dt	interval from last time step [s]
		 */
		virtual void TimeStep( const double dt );

		/**
		 * Defines initial camera orientation, rotates camera mesh and provides mesh group information for pan and tilt animations. Used when camera mesh is pointing along the +Xo axis.
		 * @param mesh_idx	camera mesh handle for rotation
		 * @param rotZo		base camera rotation on Zo axis [deg]
		 * @param rotXo		base camera rotation on Xo axis [deg]
		 * @param base_grp	array of mesh groups in camera PTU base (used for initial orientation animation)
		 * @param base_grp_sz	number of groups in base_grp
		 * @param pan_grp	array of mesh groups for pan animation
		 * @param pan_grp_sz	number of groups in pan_grp
		 * @param tilt_grp	array of mesh groups for tilt animation
		 * @param tilt_grp_sz	number of groups in tilt_grp
		 */
		void DefineAnimations( const UINT mesh_idx, const double rotZo, const double rotXo, const UINT* base_grp, const UINT base_grp_sz, const UINT* pan_grp, const UINT pan_grp_sz, const UINT* tilt_grp, const UINT tilt_grp_sz );
		/**
		 * Defines initial camera orientation, and provides pan and tilt animation handles. Used when camera mesh is already correctly oriented.
		 * @param rotZo		base camera rotation on Zo axis [deg]
		 * @param rotXo		base camera rotation on Xo axis [deg]
		 * @param anim_pan	index for pan animation
		 * @param anim_tilt	index for tilt animation
		 */
		void DefineAnimations( const double rotZo, const double rotXo, const UINT anim_pan, const UINT anim_tilt );

		/**
		 * Connects PTU heater power.
		 * @param Bundle	pointer to DiscreteBundle
		 * @param Line		DiscreteBundle line index
		 */
		void ConnectPowerPTUHeater( discsignals::DiscreteBundle* Bundle, const unsigned short Line );
};

#endif// __CCTV_CAMERA_PTU_H
