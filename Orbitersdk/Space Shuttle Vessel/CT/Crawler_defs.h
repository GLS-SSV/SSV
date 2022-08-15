/****************************************************************************
  This file is part of Space Shuttle Vessel

  Crawler consts definition


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
2020/06/01   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
********************************************/

#ifndef _CRAWLER_DEFS_H
#define _CRAWLER_DEFS_H


#include <Orbitersdk.h>
#include <EngConst.h>


inline constexpr double DRIVETRUCK_X_OFFSET = 12.30;
inline constexpr double DRIVETRUCK_Y_OFFSET = 3.3524;
inline constexpr double DRIVETRUCK_Z_OFFSET = 13.58725;
// offsets between crawler DRIVETRUCKs and main body mesh

inline constexpr double DRIVETRUCK_SHOE_OFFSET = -0.00993;// [m]

const double TRUCK_MAX_TILT = 10.0 * RAD;

const VECTOR3 CRAWLER_MESH_OFFSET = _V( 0.0, 0.0, 0.0 );

const static char* MESHNAME_CRAWLER = "SSV\\CT\\mainbody_2004";
const static char* MESHNAME_CRAWLER_1980 = "SSV\\CT\\mainbody_1980";

inline constexpr int JACK_HEIGHT_COUNT = 7;// # of predefined jacking levels
inline constexpr double JACKING_HEIGHTS[JACK_HEIGHT_COUNT] = {// [m]
	0.1524,// minimum height limit: 6 in, 0.5 ft
	0.2286,// height to go under MLP: 9 in, 0.75 ft
	0.381,// travel height: 15 in, 1.25 ft
	0.7366,// MLP docking height: 29 in, 2.416667 ft
	0.889,// ramp height: 35 in, 2.916667 ft
	1.6002,// MLP stand clearance height: 63 in, 5.25 ft
	1.8288};// maximum height: 72 in, 6.0 ft

inline constexpr double JACKING_MAX_HEIGHT = JACKING_HEIGHTS[JACK_HEIGHT_COUNT - 1];

inline constexpr double MAX_TURN_ANGLE = 6.0;// max angle (in degrees) each set of trucks can be turned
inline constexpr double TRACK_TURN_SPEED = 0.0425;// speed (in deg/sec) at which Crawler trucks turn
inline constexpr double STEERING_WHEEL_SPEED = 0.2;// steering wheel deflection rate

const VECTOR3 MLP_ATTACH_POS = _V( 0.0, 5.95678, 0.0 );
const VECTOR3 MLP_ATTACH_ROT = _V( 0.0, 0.0, 1.0 );

inline constexpr double MAX_UNLOADED_SPEED = 2.0/MPS2MPH;
inline constexpr double MAX_LOADED_SPEED = 0.8/MPS2MPH;

inline constexpr double LC39_RAMP_START = 392.593994;// distance from pad at which ramp starts [m]
inline constexpr double LC39_RAMP_END = 129.227997;// distance from pad at which ramp ends [m]
inline constexpr double LC39_SURFACE_HEIGHT = 12.8016 + 0.05;// height of pad surface + vertical LC39 vessel offset [m]


// View positions
inline constexpr int VIEWPOS_FRONTCABIN		= 0;// CAB-3
inline constexpr int VIEWPOS_REARCABIN		= 1;// CAB-1
inline constexpr int VIEWPOS_ENGINEERING		= 2;
inline constexpr int VIEWPOS_GROUND		= 3;
inline constexpr int VIEWPOS_FRONTGANGWAY		= 4;
inline constexpr int VIEWPOS_REARGANGWAY		= 5;
inline constexpr int VIEWPOS_RIGHTREARGANGWAY	= 6;


inline constexpr int AID_REAR_OFFSET = 50; // offset added for rear cabs

inline constexpr int AID_LEFT_MIN			= 1;
inline constexpr int AID_COMMAND_VOLTAGE	= 4;

inline constexpr int AID_CTR_MIN			= 10;
inline constexpr int AID_SPEED_VALUE		= 11;
inline constexpr int AID_SPEED_BAR			= 12;

inline constexpr int AID_RIGHT_MIN			= 20;
inline constexpr int AID_STEERING_L_VALUE	= 25;
inline constexpr int AID_STEERING_L_BAR	= 26;
inline constexpr int AID_STEERING_R_VALUE	= 27;
inline constexpr int AID_STEERING_R_BAR	= 28;
inline constexpr int AID_STEERING_DES_VALUE= 29;
inline constexpr int AID_STEEEING_DES_BAR	= 30;
inline constexpr int AID_AVG_HEIGHT_VALUE	= 31;
inline constexpr int AID_AVG_HEIGHT_BAR	= 32;

inline constexpr int AID_LDS_AREA          = 40;


const VECTOR3 INNER_BRAKE_DISK_REF_PT = {0.30,-0.97,0.54};
const VECTOR3 OUTER_BRAKE_DISK_REF_PT = {1.96,-0.97,0.54};


#endif// _CRAWLER_DEFS_H
