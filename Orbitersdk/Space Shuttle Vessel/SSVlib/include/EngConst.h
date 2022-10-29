/****************************************************************************
  This file is part of Space Shuttle Vessel

  Engineering and conversion constants definition


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
2020/08/24   GLS
2021/06/26   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  SSU Engineering constants



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
#ifndef _ENGCONST_H
#define _ENGCONST_H


inline constexpr double LBM2KG = 0.45359237;// pounds to kilograms
inline constexpr double KG2LBM = 2.205;// kilograms to pounds

inline constexpr double FPS2MS = 0.3048;// feet per second to meters per seconds
inline constexpr double MPS2FPS = 3.280839895;// meters per seconds to feet per second

inline constexpr double MPS2KTS = 1.943844492;// meter per second to knots

inline constexpr double MPS2MPH = 2.23693629; // meters per second to miles per hour

inline constexpr double PA2PSF = 0.02088545;// pascal to pounds per square foot

inline constexpr double PSI2PA = 6894.757;// pounds per square inch to pascal

inline constexpr double NM2M = 1852.0; // nautical mile to meter

inline constexpr double FT2NM = 0.0001645784;// feet to nautical mile

inline constexpr double LBF = 4.4482216152605; //lb(f) to Newton

inline constexpr double IN2M = 0.0254;// inches to meters

inline constexpr double LBS2SL = 0.03108094974306777490144308538848;// pounds to slugs

inline constexpr double G2FPS2 = 32.17417;// g to fps2



enum AXIS {PITCH, YAW, ROLL};

/**
 * Convert orbiter station coordinates (Xo, Yo, Zo) in inches to Orbiter local coordinates in meters
 *
 * \param Xo X-axis of the orbiter station coordinate system (pointing backwards)
 * \param Yo Y-axis of the orbiter station coordinate system (pointing right)
 * \param Zo Z-axis of the orbiter station coordinate system (pointing up)
 * \return Orbiter local coordinates, origin is still the origin of the station coordinate system.
 */
inline VECTOR3 _XYZO(double Xo, double Yo, double Zo) {
	return _V(Yo * IN2M, Zo * IN2M, -Xo * IN2M);
}

/**
 * Convert a thrust vector defined in dynamic body coordinates (Xb, Yb, Zb) into a direction vector of for orbiter
 */
inline VECTOR3 _FXYZB_TO_DIRECTION(double FXb, double FYb, double FZb) {
	double total = sqrt(pow(FXb, 2) + pow(FYb, 2) + pow(FZb, 2));
	return _V(FYb / total, -FZb / total, FXb / total);
}

#endif// _ENGCONST_H
