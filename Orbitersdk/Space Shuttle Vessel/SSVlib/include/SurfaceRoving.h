/****************************************************************************
  This file is part of Space Shuttle Vessel

  Surface Roving definition

  This class contains code from the GeneralVehicle addon by Fred18.

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
/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/06/13   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Surface Roving definition

  This class contains code from the GeneralVehicle addon by Fred18.

  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _SURFACEROVING_H_
#define _SURFACEROVING_H_


#include <Orbitersdk.h>


/**
 * Implementation of SurfaceRoving which contains logic to move a vessel on a planetary surface.
 * Notes:
 * (1) vessel center is assumed to be located in the geometric center of the wheels;
 * (2) wheel animations, wheel turn speed and limits, and vessel speed control are the responsability of the vessel;
 * (3) "normal" turns assume wheel slip, as Akerman turn is not implemented;
 * (4) crab turn performance assumes no wheel slip;
 * (5) logic has not been tested near poles of planets.
 */
class SurfaceRoving
{
	private:
		VESSEL* v;
		double wheelbase;// wheelbase distance [m]
		double track;// wheel track distance [m]
		double height;// height from bottom of wheels to vessel center [m]

	public:
		SurfaceRoving( VESSEL* v, double wheelbase, double track, double height );
		~SurfaceRoving( void );

		void SetHeight( double height );

		/**
		 * Moves vessel according to parameters.
		 * @param dt			time step length [s]
		 * @param speed			vessel velocity (positive = forward, negative = backward) [m/s]
		 * @param forward_steering	forward steering angle (positive = wheels right, negative = wheels left) [deg]
		 * @param rear_steering		rear steering angle (positive = wheels right, negative = wheels left) [deg]
		 */
		void Move( double dt, double speed, double forward_steering, double rear_steering );

		/**
		 * Moves vessel in crab mode (turn in place).
		 * @param dt			time step length [s]
		 * @param speed			vessel velocity (positive = right turn, negative = left turn) [m/s]
		 */
		void Move_Crab( double dt, double speed );
};

#endif// _SURFACEROVING_H_
