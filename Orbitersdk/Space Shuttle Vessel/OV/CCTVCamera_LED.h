/****************************************************************************
  This file is part of Space Shuttle Vessel

  CCTV Camera with LED illuminator definition


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
#ifndef __CCTV_CAMERA_LED_H
#define __CCTV_CAMERA_LED_H


#include <CCTVCamera.h>
#include "Atlantis.h"


class ExternalLight;


class CCTVCamera_LED : public CCTVCamera
{
	private:
		ExternalLight* light;

	public:
		/**
		 * Constructor for CCTVCamera_LED class.
		 * @param sts	pointer to Atlantis class
		 * @param pos	camera position
		 */
		CCTVCamera_LED( Atlantis* sts, const VECTOR3& pos );
		virtual ~CCTVCamera_LED( void );

		/**
		 * Updates camera state.
		 * @param dt	interval from last time step [s]
		 */
		void TimeStep( const double dt ) override;

		/**
		 * Updates light visuals.
		 */
		void VisualCreated( void );

		/**
		 * Connects LED power.
		 * @param Bundle	pointer to DiscreteBundle
		 * @param Line		DiscreteBundle line index
		 */
		void ConnectLEDPower( discsignals::DiscreteBundle* Bundle, const unsigned short Line );

		/**
		 * Defines mesh group for light.
		 * @param _mesh		mesh index
		 * @param _grpIndex	group index
		 */
		void DefineMeshGroup( UINT _mesh, UINT _grpIndex );
};

#endif// __CCTV_CAMERA_LED_H
