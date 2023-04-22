/****************************************************************************
  This file is part of Space Shuttle Vessel

  Parameter values definition


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
2020/03/25   GLS
2020/03/26   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/04/02   GLS
2020/05/07   GLS
2020/05/12   GLS
2020/05/17   GLS
2020/05/23   GLS
2020/05/29   GLS
2020/05/31   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/07/08   GLS
2020/08/10   GLS
2020/08/11   GLS
2020/09/15   GLS
2020/10/11   GLS
2021/01/11   GLS
2021/02/15   GLS
2021/02/16   GLS
2021/03/18   GLS
2021/05/26   GLS
2021/05/30   GLS
2021/05/31   GLS
2021/06/01   GLS
2021/06/28   GLS
2021/06/30   GLS
2021/07/01   GLS
2021/07/03   GLS
2021/07/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/19   GLS
2022/02/11   GLS
2022/02/17   GLS
2022/02/21   GLS
2022/03/24   GLS
2022/03/25   GLS
2022/03/26   GLS
2022/04/17   GLS
2022/08/05   GLS
2022/08/07   GLS
2022/09/29   GLS
2022/11/25   GLS
********************************************/
#ifndef _PARAMETERVALUES_H_
#define _PARAMETERVALUES_H_


#include <OrbiterAPI.h>
#include <EngConst.h>

inline constexpr double ORBITER_EMPTY_MASS_OV102 = 80739.44 - (6924.0 * LBM2KG * 3);
inline constexpr double ORBITER_EMPTY_MASS_OV099 = 79429.01 - (6924.0 * LBM2KG * 3);
inline constexpr double ORBITER_EMPTY_MASS_OV103 = 77564.3 - (6924.0 * LBM2KG * 3);
inline constexpr double ORBITER_EMPTY_MASS_OV104 = 77564.3 - (6924.0 * LBM2KG * 3);
inline constexpr double ORBITER_EMPTY_MASS_OV105 = 78017.89 - (6924.0 * LBM2KG * 3);
// Orbiter empty masses [kg]


// RCS masses are max flown loads, tank is 2387 lbs (1464 + 923) and the difference is attributed to prop in lines
inline constexpr double ORBITER_FRCS_PROPELLANT_MASS = 2473.0 * LBM2KG;// usual load ~2450 lbs
inline constexpr double ORBITER_LEFT_ARCS_PROPELLANT_MASS = 2692.0 * LBM2KG;// usual load ~2485 lbs
inline constexpr double ORBITER_RIGHT_ARCS_PROPELLANT_MASS = 2692.0 * LBM2KG;// usual load ~2485 lbs

// OMS mass is max flown load, tank load is described below and the difference is attributed to prop in lines
// Per SODB Vol 1, 3.4.3.3, maximum propellant load in the OMS tanks is 4711.5 lbs (2137.1 kg) of fuel and 7743.5 lbs (3512.393 kg) of oxidizer per pod. Min load is 2038 (924.4213 kg) lbs of fuel and 3362 lbs (1524.978 kg) of oxidizer per pod.
inline constexpr double ORBITER_MAX_OMS_PROPELLANT_MASS = 12593.5 * LBM2KG; // usual load is ~10000 lbs (per pod)


//inline constexpr double SSME_RATED_THRUST = 2090664.159; //100% thrust
inline constexpr double SSME_THRUST = 2170732.15; //Nominal "104%" thrust
//inline constexpr double ORBITER_MAX_THRUST = 2275094.273; //109% thrust
// Vacuum thrust rating per main engine [N]
inline constexpr double SSME_MAX_POWER_LEVEL = 109.0;

inline constexpr double OMS_THRUST = 26700.0;
// Vacuum thrust per unit for Orbital Maneuvering System [N] (x2 for total)

inline constexpr double OMS_PITCH_RANGE = 6.0;
inline constexpr double OMS_YAW_RANGE = 7.0;
// max gimbal angles in degrees

inline constexpr double RCS_THRUST = 7740.0;
// Vacuum thrust rating for attitude thrusters (Reaction Control System) [N]

inline constexpr double SSME_ISP0 = 453*9.80665;
inline constexpr double SSME_ISP1 = 363*9.80665;
// Vacuum and sea-level fuel-specific impulse for orbiter main engines [m/s]
// using H2/O2 (hydrogen/oxygen)

inline constexpr double OMS_ISP0 = 316*9.80665;
inline constexpr double OMS_ISP1 = OMS_ISP0*0.75;
// Vacuum and sea-level fuel-specific impulse for Orbital Maneuvering System [m/s]

inline constexpr double RCS_ISP0 = OMS_ISP0;
inline constexpr double RCS_ISP1 = RCS_ISP0*0.75;
// Vacuum and sea-level fuel-specific impulse for Reaction Control System [m/s]

inline constexpr double ORBITER_PITCH_TORQUE = 239900.00;
inline constexpr double ORBITER_YAW_TORQUE = 239900.00;
inline constexpr double ORBITER_ROLL_TORQUE = 41800.00;
// Vacuum RCS Torque [N]

inline constexpr double OMS_HELIUM_TANK_MASS = 21.0;
//Helium tank mass [kg]

inline constexpr double ORBITER_WING_AREA = 2690*0.3048*0.3048; // [m^2]
inline constexpr double ORBITER_SPAN = 78.056*0.3048; //Turns out span is not used...
inline constexpr double ORBITER_CHORD_LENGTH=39.56*0.3048; //...but chord is
inline constexpr double ORBITER_WING_ASPECT_RATIO = ORBITER_SPAN*ORBITER_SPAN/ORBITER_WING_AREA; //Has to be passed, doesn't have to be correct


inline constexpr VECTOR3 ORBITER_CS = {304.62,457.57,149.27};
// Orbiter cross sections (projections into principal axes) [m^2]


inline constexpr double PTU_HIGHRATE_SPEED = 12.0;// [deg/s]
inline constexpr double PTU_LOWRATE_SPEED = 1.2;// [deg/s]
inline constexpr double MIN_CAM_ZOOM = 9.0;// horizontal FOV (approx) [deg]
inline constexpr double MAX_CAM_ZOOM = 77.0;// horizontal FOV (approx) [deg]
inline constexpr double PLB_CAM_ZOOM_RATE = 5.0;// [deg/s]
inline constexpr double PLB_CAM_PAN_MIN = -170.0;// [deg]
inline constexpr double PLB_CAM_PAN_MAX = 170.0;// [deg]
inline constexpr double PLB_CAM_TILT_MIN = -80.0;// [deg]
inline constexpr double PLB_CAM_TILT_MAX = 260.0;// [deg]

inline constexpr VECTOR3 CAM_LENS_OFFSET = { 0.0, 0.0, 0.1778 };// [m] lens have ~7'' offset from axis



inline constexpr double RHC_RATE = 0.75;// 1/x seconds from detent to full deflection
inline constexpr double RPTA_RATE = 0.75;// 1/x seconds from detent to full deflection
inline constexpr double BRAKE_RATE = 0.75;// 1/x seconds from detent to full deflection


const static char* MESHNAME_VC = "SSV\\OV\\VC";
const static char* MESHNAME_VC_EXTERNAL = "SSV\\OV\\VC_external";
const static char* MESHNAME_MIDDECK = "SSV\\OV\\MidDeck";
const static char* MESHNAME_ORBITER = "SSV\\OV\\OV";
const static char* MESHNAME_OV_VERTICALTAIL_OV102 = "SSV\\OV\\OV_VerticalTail_OV-102";
const static char* MESHNAME_OV_VERTICALTAIL_OV099 = "SSV\\OV\\OV_VerticalTail_OV-099";
const static char* MESHNAME_OV_VERTICALTAIL_OV102_SILTS = "SSV\\OV\\OV_VerticalTail_OV-102_SILTS";
const static char* MESHNAME_OV_VERTICALTAIL_OV105 = "SSV\\OV\\OV_VerticalTail_OV-105";
const static char* MESHNAME_OV_VERTICALTAIL_OV102_DC = "SSV\\OV\\OV_VerticalTail_OV-102_DC";
const static char* MESHNAME_CHUTE = "SSV\\DragChute";
const static char* MESHNAME_OMSKIT = "SSV\\";
const static char* TEXTURENAME_AFTBULKHEAD_FLAGSTARBOARD = "SSV\\OV\\PLB_AftBulkhead_FlagStarboard.dds";
const static char* TEXTURENAME_AFTBULKHEAD_FLAGNONE = "SSV\\OV\\PLB_AftBulkhead_FlagNone.dds";


inline constexpr VECTOR3 OFS_ZERO             = { 0.0, 0.0, 0.0 };
inline constexpr VECTOR3 VC_OFFSET = { 0.0, -1.41, -2.42 };// main "internal view" vc mesh offset [m]
inline constexpr VECTOR3 VC_EXTERNAL_OFFSET = { 0.0, 0.0, 0.0 };// simple "external view" vc mesh offset [m]

// mesh offsets
// Orbiter mesh is always at (0,0,0)
inline constexpr VECTOR3 ET_OFFSET = { 0.0, -8.97424, 4.2134 }; // offset between ET and shuttle meshes, equivalent to Yo0, Zo63.4988, Xt2058 - (Xt2058=Xo1317) - (tank shrink=0.1011m)
inline constexpr VECTOR3 LSRB_OFFSET = { -6.3627, -8.97424, 4.3554275 }; // offset between SRB and shuttle mesh, equivalent to Yo-250.5, Zo63.4988, Xb+976.8375 - 198.0 = Xo+778.8375 - (tank shrink=0.1011m)
inline constexpr VECTOR3 RSRB_OFFSET = { 6.3627, -8.97424, 4.3554275 }; // offset between SRB and shuttle mesh, equivalent to Yo250.5, Zo63.4988, Xb+976.8375 - 198.0 = Xo+778.8375 - (tank shrink=0.1011m)
inline constexpr VECTOR3 OMSKIT_OFFSET = { 0.0, 0.0, 0.0 };
inline constexpr VECTOR3 ENTRY_OFFSET = { 0.0, -0.02, 0.0 };


inline constexpr double MPS_MANIFOLD_MASS_LOX = 2306;// kg
inline constexpr double MPS_MANIFOLD_MASS_LH2 = 144;// kg
inline constexpr double MPS_MANIFOLD_MASS_TOTAL = MPS_MANIFOLD_MASS_LOX + MPS_MANIFOLD_MASS_LH2;// estimated 5400 lbs LOX/LH2 in mps manifold


inline constexpr VECTOR3 SSME_REF[3] = {
	{0.0, 0.6651, -12.464},// Xo+1445.0 Yo+0.0 Zo+443.0
	{-1.3462, -1.884044, -13.052518},// Xo+1468.17 Yo-53.0 Zo+342.64
	{1.3462, -1.884044, -13.052518}};// Xo+1468.17 Yo+53.0 Zo+342.64

inline constexpr double SSME_PITCH_MIN = -10.5;// [deg]
inline constexpr double SSME_PITCH_MAX = 10.5;// [deg]
inline constexpr double SSME_YAW_MIN = -8.5;// [deg]
inline constexpr double SSME_YAW_MAX = 8.5;// [deg]

inline constexpr double SSME_INSTALL_PITCH[3] = {-16.0, -10.0, -10.0};// [deg]
inline constexpr double SSME_INSTALL_YAW[3] = {0.0, -3.5, 3.5};// [deg]

inline constexpr VECTOR3 SSME_GOX_REF = { 1.196044, 0.197608, -3.91901 };
inline constexpr VECTOR3 SSME_VENT_REF = { -0.000077, 0.002896, -3.94315 };// center of nozzle exit plane


inline constexpr VECTOR3 MPS_LH2_BU_DUMP_POS = { -2.7432, -2.57594, -9.6446 };// Xo+1334, Yo-108, Zo+315.4
inline constexpr VECTOR3 MPS_LH2_BU_DUMP_DIR = { 0.999, -0.017, 0.0 };

inline constexpr VECTOR3 MPS_LH2_FD_POS = { -2.96672, -0.62268, -12.66974 };// Xo+1453.1, Yo-116.8, Zo+392.3
inline constexpr VECTOR3 MPS_LH2_FD_DIR = { 1.0, 0.0, 0.0 };

inline constexpr VECTOR3 MPS_LOX_FD_POS = { 2.96672, -0.62268, -12.66974 };// Xo+1453.1, Yo+116.8, Zo+392.3
inline constexpr VECTOR3 MPS_LOX_FD_DIR = { -1.0, 0.0, 0.0 };

inline constexpr VECTOR3 MPS_LH2_FDLN_RV_POS = { -0.41402, 2.3796, -11.21178 };// Xo+1395.7, Yo-16.3, Zo+510.5
inline constexpr VECTOR3 MPS_LH2_FDLN_RV_DIR = { 0.0, -1.0, 0.0 };

inline constexpr VECTOR3 MPS_LOX_FDLN_RV_POS = { 2.9591, -2.5607, -11.5242 };// approx. Xo+1408, Yo+116.5, Zo+316
inline constexpr VECTOR3 MPS_LOX_FDLN_RV_DIR = { -1.0, 0.0, 0.0 };


inline constexpr VECTOR3 SRB_THRUST_DIR = { 0.0, 0.0, 1.0 };


const VECTOR3 POS_HDP = { 0.0, LSRB_OFFSET.y, - 19.770056/*XB+1930.64 - 198.0 = Xo+1732.64*/ - 0.1011/*tank shrink*/ };
inline constexpr VECTOR3 POS_TOW = { 0.0, -5.64, 14.73 };



inline constexpr VECTOR3 L_OMS_REF = { -2.2352, 1.9097, -14.3182 };
inline constexpr VECTOR3 R_OMS_REF = { 2.2352, 1.9097, -14.3182 };
inline constexpr VECTOR3 L_OMS_DIR = { 0.108926, -0.27228, 0.956033 };
inline constexpr VECTOR3 R_OMS_DIR = { -0.108926, -0.27228, 0.956033 };
inline constexpr VECTOR3 L_OMS_AXIS_YAW = { 0.0, 0.962102, 0.272691 };
inline constexpr VECTOR3 L_OMS_AXIS_PITCH = { -0.993572, 0.0, 0.113203 };
inline constexpr VECTOR3 R_OMS_AXIS_YAW = { 0.0, 0.962102, 0.272691 };
inline constexpr VECTOR3 R_OMS_AXIS_PITCH = { -0.993572, 0.0, -0.113203 };


inline constexpr int STATE_PRELAUNCH = 0;
inline constexpr int STATE_STAGE1 = 1;	//SRBs ignited
inline constexpr int STATE_STAGE2 = 2;	//ET only
inline constexpr int STATE_ORBITER = 3; //post ET separation
inline constexpr int STATE_DESTROYED = 99;	//don't use!
//



//==================================================
// Real RCS thruster offsets and directions
//Source: ODB, p 429-430
//==================================================


//const VECTOR3 RCS_F2F_OFS = _V(0.4, 0.7, 19.0);			//previous coordinates
const VECTOR3 STATION_TO_CG0 = _V(0.0, -10.31553, 24.4715)		//Position by old exhaust coordinates
								+ _V(0.0, 0.0, -0.4);			//Correction factor

const VECTOR3 RCS_F2F_OFS = _V(0.3721, 9.9811, -7.7907) + STATION_TO_CG0;				//Real coordinates
const VECTOR3 RCS_F2F_DIR = _V(-0.29597827, -0.135037729, -0.99042685);						//Direction from ODB
inline constexpr double RCS_F2F_THRUST0 = 887.9 * LBF;												//Thrust from ODB

//const VECTOR3 RCS_F3F_OFS = _V(0.0, 0.75, 19.0);
const VECTOR3 RCS_F3F_OFS = _V(0.0, 10.0190, -7.7907) + STATION_TO_CG0;
const VECTOR3 RCS_F3F_DIR = _V(0.0, -0.138175676, -0.990427928);				//Direction from ODB
inline constexpr double RCS_F3F_THRUST0 = 888.0 * LBF;									//Thrust from ODB

//const VECTOR3 RCS_F1F_OFS = _V(-0.4, 0.7, 19.0);
const VECTOR3 RCS_F1F_OFS = _V(-0.3721, 9.9811, -7.7907) + STATION_TO_CG0;
const VECTOR3 RCS_F1F_DIR = _V(0.29597827, -0.135037729, -0.99042685);			//Direction from ODB
inline constexpr double RCS_F1F_THRUST0 = 887.9 * LBF;									//Thrust from ODB

//const VECTOR3 RCS_F1L_OFS = _V(-1.7 ,-0.15, 17.40);
const VECTOR3 RCS_F1L_OFS = _V(-1.7653, 9.4927, -9.2112) + STATION_TO_CG0;
const VECTOR3 RCS_F1L_DIR = _V(0.999313658, -0.020819035,-0.030084648);			//Direction from ODB
inline constexpr double RCS_F1L_THRUST0 = 874.2 * LBF;									//Thrust from ODB

//const VECTOR3 RCS_F3L_OFS = _V(-1.65, 0.25, 17.45);
const VECTOR3 RCS_F3L_OFS = _V(-1.8199, 9.1250, -9.2636) + STATION_TO_CG0;
const VECTOR3 RCS_F3L_DIR = _V(0.99965541, -0.000574317, -0.024121296);			//Direction from ODB
inline constexpr double RCS_F3L_THRUST0 = 870.6 * LBF;									//Thrust from ODB

//const VECTOR3 RCS_F2R_OFS = _V(1.75, 0.25, 17.45);
const VECTOR3 RCS_F2R_OFS = _V(1.7653, 9.4927, -9.2112) + STATION_TO_CG0;
const VECTOR3 RCS_F2R_DIR = _V(-0.999313658, -0.020819035, -0.030084648);		//Direction from ODB
inline constexpr double RCS_F2R_THRUST0 = 874.62 * LBF;									//Thrust from ODB

//const VECTOR3 RCS_F4R_OFS = _V(1.8, -0.15, 17.40);
const VECTOR3 RCS_F4R_OFS = _V(1.8199, 9.1250, -9.2636) + STATION_TO_CG0;
const VECTOR3 RCS_F4R_DIR = _V(-0.99965541, -0.000574317, -0.024121296);		//Direction from ODB
inline constexpr double RCS_F4R_THRUST0 = 870.6 * LBF;									//Thrust from ODB

//const VECTOR3 RCS_F2U_OFS = _V(0.4, 1.10, 17.9);
const VECTOR3 RCS_F2U_OFS = _V(0.3655, 10.501, -8.9136) + STATION_TO_CG0;
const VECTOR3 RCS_F2U_DIR = _V(-0.013369901, -0.999200091, -0.036910067);		//Direction from ODB
inline constexpr double RCS_F2U_THRUST0 = 875.1 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F3U_OFS = _V(0.0 , 10.5291, -8.9134 ) + STATION_TO_CG0;
const VECTOR3 RCS_F3U_DIR = _V(0.0, -0.99931358, -0.03649468);					//Direction from ODB
inline constexpr double RCS_F3U_THRUST0 = 874.1 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F1U_OFS = _V(-0.3655, 10.501, -8.9136) + STATION_TO_CG0;
const VECTOR3 RCS_F1U_DIR = _V(0.013369901, -0.999200091, -0.036910067);		//Direction from ODB
inline constexpr double RCS_F1U_THRUST0 = 875.1 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F2D_OFS = _V(1.560068, 9.06653, -8.479536) + STATION_TO_CG0;
const VECTOR3 RCS_F2D_DIR = _V(-0.693675445, 0.719671393, -0.031510241);			//Direction from ODB
inline constexpr double RCS_F2D_THRUST0 = 888.6 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F1D_OFS = _V(-1.560068, 9.06653, -8.479536) + STATION_TO_CG0;
const VECTOR3 RCS_F1D_DIR = _V(0.693675445, 0.719671393, -0.031510241);		//Direction from ODB
inline constexpr double RCS_F1D_THRUST0 = 888.6 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F4D_OFS = _V(1.6822, 9.1044, -8.8504) + STATION_TO_CG0;
const VECTOR3 RCS_F4D_DIR = _V(-0.691500169, 0.721751891, -0.02799413);			//Direction from ODB
inline constexpr double RCS_F4D_THRUST0 = 885.9 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F3D_OFS = _V(-1.6822, 9.1044, -8.8504) + STATION_TO_CG0;
const VECTOR3 RCS_F3D_DIR = _V(0.691500169, 0.721751891, -0.02799413);			//Direction from ODB
inline constexpr double RCS_F3D_THRUST0 = 885.9 * LBF;									//Thrust from ODB

const VECTOR3 RCS_F5R_OFS = _V(1.5164, 8.8931, -8.2385) + STATION_TO_CG0;
const VECTOR3 RCS_F5R_DIR = _V(-0.693877551, 0.718367347, -0.032653061);		//Direction from ODB
inline constexpr double RCS_F5R_THRUST0 = 24.5 * LBF;										//Thrust from ODB

const VECTOR3 RCS_F5L_OFS = _V(-1.5164, 8.8931, -8.2385) + STATION_TO_CG0;
const VECTOR3 RCS_F5L_DIR = _V(0.693877551, 0.718367347, -0.032653061);			//Direction from ODB
inline constexpr double RCS_F5L_THRUST0 = 24.5 * LBF;										//Thrust from ODB

const VECTOR3 RCS_R3A_OFS = _XYZO(1555.29, 137.0, 473.06) + STATION_TO_CG0;
const VECTOR3 RCS_R3A_DIR = _FXYZB_TO_DIRECTION(856.8, 0.0, 151.1);
inline constexpr double RCS_R3A_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R1A_OFS = _XYZO(1555.29, 124.00, 473.06) + STATION_TO_CG0;
const VECTOR3 RCS_R1A_DIR = _FXYZB_TO_DIRECTION(856.8, 0.0, 151.1);
inline constexpr double RCS_R1A_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L3A_OFS = _XYZO(1555.29, -137.0, 473.06) + STATION_TO_CG0;
const VECTOR3 RCS_L3A_DIR = _FXYZB_TO_DIRECTION(856.8, 0.0, 151.1);
inline constexpr double RCS_L3A_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L1A_OFS = _XYZO(1555.29, -124.00, 473.06) + STATION_TO_CG0;
const VECTOR3 RCS_L1A_DIR = _FXYZB_TO_DIRECTION(856.8, 0.0, 151.1);
inline constexpr double RCS_L1A_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L4L_OFS = _XYZO(1516.00, -149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_L4L_DIR = _FXYZB_TO_DIRECTION(0.0, 870.5, -22.4);
inline constexpr double RCS_L4L_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_L2L_OFS = _XYZO(1529.00, -149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_L2L_DIR = _FXYZB_TO_DIRECTION(0.0, 870.5, -22.4);
inline constexpr double RCS_L2L_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_L3L_OFS = _XYZO(1542.00, -149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_L3L_DIR = _FXYZB_TO_DIRECTION(0.0, 870.5, -22.4);
inline constexpr double RCS_L3L_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_L1L_OFS = _XYZO(1555.00, -149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_L1L_DIR = _FXYZB_TO_DIRECTION(0.0, 870.5, -22.4);
inline constexpr double RCS_L1L_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_R4R_OFS = _XYZO(1516.00, 149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_R4R_DIR = _FXYZB_TO_DIRECTION(0.0, -870.5, -22.4);
inline constexpr double RCS_R4R_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_R2R_OFS = _XYZO(1529.00, 149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_R2R_DIR = _FXYZB_TO_DIRECTION(0.0, -870.5, -22.4);
inline constexpr double RCS_R2R_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_R3R_OFS = _XYZO(1542.00, 149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_R3R_DIR = _FXYZB_TO_DIRECTION(0.0, -870.5, -22.4);
inline constexpr double RCS_R3R_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_R1R_OFS = _XYZO(1555.00, 149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_R1R_DIR = _FXYZB_TO_DIRECTION(0.0, -870.5, -22.4);
inline constexpr double RCS_R1R_THRUST0 = 870.8 * LBF;

const VECTOR3 RCS_L4U_OFS = _XYZO(1516.00, -132.00, 480.50) + STATION_TO_CG0;
const VECTOR3 RCS_L4U_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, 870.0);
inline constexpr double RCS_L4U_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L2U_OFS = _XYZO(1529.00, -132.00, 480.50) + STATION_TO_CG0;
const VECTOR3 RCS_L2U_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, 870.0);
inline constexpr double RCS_L2U_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L1U_OFS = _XYZO(1542.00, -132.00, 480.50) + STATION_TO_CG0;
const VECTOR3 RCS_L1U_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, 870.0);
inline constexpr double RCS_L1U_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R4U_OFS = _XYZO(1516.00, 132.00, 480.50) + STATION_TO_CG0;
const VECTOR3 RCS_R4U_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, 870.0);
inline constexpr double RCS_R4U_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R2U_OFS = _XYZO(1529.00, 132.00, 480.50) + STATION_TO_CG0;
const VECTOR3 RCS_R2U_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, 870.0);
inline constexpr double RCS_R2U_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R1U_OFS = _XYZO(1542.00, 132.00, 480.50) + STATION_TO_CG0;
const VECTOR3 RCS_R1U_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, 870.0);
inline constexpr double RCS_R1U_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L4D_OFS = _XYZO(1516.00, -111.95, 437.40) + STATION_TO_CG0;
const VECTOR3 RCS_L4D_DIR = _FXYZB_TO_DIRECTION(170.4, 291.8, -801.7);
inline constexpr double RCS_L4D_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L2D_OFS = _XYZO(1529.00, -111.00, 440.00) + STATION_TO_CG0;
const VECTOR3 RCS_L2D_DIR = _FXYZB_TO_DIRECTION(170.4, 291.8, -801.7);
inline constexpr double RCS_L2D_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L3D_OFS = _XYZO(1542.00, -110.06, 442.60) + STATION_TO_CG0;
const VECTOR3 RCS_L3D_DIR = _FXYZB_TO_DIRECTION(170.4, 291.8, -801.7);
inline constexpr double RCS_L3D_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R4D_OFS = _XYZO(1516.00, 111.95, 437.40) + STATION_TO_CG0;
const VECTOR3 RCS_R4D_DIR = _FXYZB_TO_DIRECTION(170.4, -291.8, -801.7);
inline constexpr double RCS_R4D_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R2D_OFS = _XYZO(1529.00, 111.00, 440.00) + STATION_TO_CG0;
const VECTOR3 RCS_R2D_DIR = _FXYZB_TO_DIRECTION(170.4, -291.8, -801.7);
inline constexpr double RCS_R2D_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_R3D_OFS = _XYZO(1542.00, 110.06, 442.60) + STATION_TO_CG0;
const VECTOR3 RCS_R3D_DIR = _FXYZB_TO_DIRECTION(170.4, -291.8, -801.7);
inline constexpr double RCS_R3D_THRUST0 = 870.0 * LBF;

const VECTOR3 RCS_L5D_OFS = _XYZO(1565.00, -118.00, 445.44) + STATION_TO_CG0;
const VECTOR3 RCS_L5D_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, -24.0);
inline constexpr double RCS_L5D_THRUST0 = 24.0 * LBF;

const VECTOR3 RCS_R5D_OFS = _XYZO(1565.00, 118.00, 445.44) + STATION_TO_CG0;
const VECTOR3 RCS_R5D_DIR = _FXYZB_TO_DIRECTION(0.0, 0.0, -24.0);
inline constexpr double RCS_R5D_THRUST0 = 24.0 * LBF;

const VECTOR3 RCS_L5L_OFS = _XYZO(1565.00, -149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_L5L_DIR = _FXYZB_TO_DIRECTION(0.0, 24.0, -0.6);
inline constexpr double RCS_L5L_THRUST0 = 24.0 * LBF;

const VECTOR3 RCS_R5R_OFS = _XYZO(1565.00, 149.87, 459.00) + STATION_TO_CG0;
const VECTOR3 RCS_R5R_DIR = _FXYZB_TO_DIRECTION(0.0, -24.0, -0.6);
inline constexpr double RCS_R5R_THRUST0 = 24.0 * LBF;

//---------------------------------------------------------------------------------------
//RCS end
//---------------------------------------------------------------------------------------

/* RCS GROUPS:
   G-1 : F2F, F3F, F1F :
   G-2 : F1L, F3L : + yaw, +y
   G-3 : F2R, F4R : - yaw, -y
   G-4 : F2U, F3U, F1U :
   G-5 : F5R, F2D, F4D : -roll, +pitch, -z
   G-6 : F5L, F1D, F3D : +roll, +pitch, -z
   G-7 : R3A, R1A : +x
   G-8 : L1A, L3A : +x
   G-9 : L4L, L2L, L3L, L1L : -yaw, +y
   G-10: R1R, R3R, R2R, R4R : +yaw, -y
   G-11: L1U, L2U, L4U : -roll, +pitch, +z
   G-12: R1U, R2U, R4U : +roll, +pitch, +z
   G-13: L3D, L2D, L4D : +roll, -pitch, -z
   G-14: R3D, R2D, R4D : -roll, -pitch, -z
 */



const VECTOR3 OFS_PORTMMU = _V(-2.424, -0.546, 8.0);
const VECTOR3 OFS_STBDMMU = _V( 2.424, -0.546, 8.0);



inline constexpr int PLID_Xo_base = 154;// PLID of base index
inline constexpr double PLID_Xo[] = {// Xo coordinates of PLIDs
	/*bay  1: 154-160*/608.80, 612.73, 616.67, 620.60, 624.53, 628.47, 632.40,
	/*161-162*/-1.0, -1.0,
	/*bay  2: 163-173*/644.20, 648.13, 652.07, 656.00, 659.93, 663.87, 667.80, 671.73, 675.67, 679.60, 683.53,
	/*174-176*/-1.0, -1.0, -1.0,
	/*bay  3: 177-189*/699.27, 703.20, 707.13, 711.07, 715.00, 718.93, 722.87, 726.80, 730.73, 734.67, 738.60, 742.53, 746.47,
	/*190-191*/-1.0, -1.0,
	/*bay  4: 192-204*/758.27, 762.20, 766.13, 770.07, 774.00, 777.93, 781.87, 785.80, 789.73, 793.67, 797.60, 801.53, 805.47,
	/*205*/-1.0,
	/*bay  5: 206-218*/813.33, 817.27, 821.20, 825.13, 829.07, 833.00, 836.93, 840.87, 844.80, 848.73, 852.67, 856.60, 860.53,
	/*219-220*/-1.0, -1.0,
	/*bay  6: 221-230*/872.33, 876.27, 880.20, 884.13, 888.07, 892.00, 895.93, 899.87, 903.80, 907.73,
	/*231-233*/-1.0, -1.0, -1.0,
	/*bay  7: 234-247*/923.47, 927.40, 931.33, 935.27, 939.20, 943.13, 947.07, 951.00, 954.93, 958.87, 962.80, 966.73, 970.67, 974.60,
	/*248-249*/-1.0, -1.0,
	/*bay  8: 250-263*/986.40, 990.33, 994.27, 998.20, 1002.13, 1006.07, 1010.00, 1013.93, 1017.87, 1021.80, 1025.73, 1029.67, 1033.60, 1037.53,
	/*264-265*/-1.0, -1.0,
	/*bay  9: 266-276*/1049.33, 1053.27, 1057.20, 1061.13, 1065.07, 1069.00, 1072.93, 1076.87, 1080.80, 1084.73, 1088.67,
	/*bay 10: 277-289*/1092.60, 1096.53, 1100.47, 1104.40, 1108.33, 1112.27, 1116.20, 1120.13, 1124.07, 1128.00, 1131.93, 1135.87, 1139.80,
	/*290-291*/-1.0, -1.0,
	/*bay 11: 292-301*/1151.60, 1155.53, 1159.47, 1163.40, 1167.33, 1171.27, 1175.20, 1179.13, 1183.07, 1187.0/*???*/,
	/*302-303*/-1.0, -1.0,
	/*bay 12: 304-316*/1198.80, 1202.73, 1206.67, 1210.60, 1214.53, 1218.47, 1222.40, 1226.33, 1230.27, 1234.20, 1238.13, 1242.07, 1246.00,
	/*bay 13: 317-330*/1249.93, -1.0, -1.0, -1.0, -1.0, 1269.60, 1273.53, 1277.47, 1281.40, -1.0, -1.0, -1.0, -1.0, 1303.00
};

inline constexpr int Bay_PLID[13] = {160, 175, 189, 204, 218, 232, 248, 263, 276, 289, 302, 316, 330};// last PLID of bay


// =====================================================================
// CG definitions (location of CG relative to center of Orbiter mesh)
// =====================================================================
inline constexpr VECTOR3 ORBITER_CG = {-0.0127, -1.3034, -2.6723};// Xo+1059.5 Yo-0.5 Zo+365.5
inline constexpr VECTOR3 ET_LWT_CG = {0.0635, -8.3265, 8.8466};// Xt+1347.0 Yt+2.5 Zt+425.5 (Xo+606.0 Yo+2.5 Zo+89.0)
//inline constexpr VECTOR3 ET_SLWT_CG = {0.0762, -8.22744, 8.7196};// Xt+1352.0 Yt+3.0 Zt+429.40 (Xo+611.0 Yo+3.0 Zo+92.9)
inline constexpr VECTOR3 ET_EMPTY_CG = ET_LWT_CG;
inline constexpr VECTOR3 LSRB_IGNITION_CG = {-6.3627, -8.9742, -0.4498};// Xb+1170.0 Yb0.0 Zb0.0
inline constexpr VECTOR3 LSRB_SEPARATION_CG = {-6.3627, -8.9488, -2.939};// Xb+1268.0 Yb0.0 Zb+1.0
inline constexpr VECTOR3 RSRB_IGNITION_CG = {6.3627, -8.9742, -0.4498};// Xb+1170.0 Yb0.0 Zb0.0
inline constexpr VECTOR3 RSRB_SEPARATION_CG = {6.3627, -8.9488, -2.939};// Xb+1268.0 Yb0.0 Zb+1.0
const VECTOR3 LSRB_CG = LSRB_IGNITION_CG;
const VECTOR3 RSRB_CG = RSRB_IGNITION_CG;
const VECTOR3 ET_LH2_BASE = ET_OFFSET + _V(0.0, 0.0, -15.8);
const VECTOR3 ET_LOX_BASE = ET_OFFSET + _V(0.0, 0.0, 15.0); // might not be exactly correct
inline constexpr VECTOR3 LOMS_PROP_CG = {-2.40792, 1.50076, -11.77312};// Xo+1417.8 Yo-94.8 Zo+475.9
inline constexpr VECTOR3 ROMS_PROP_CG = {2.40792, 1.50076, -11.77312};// Xo+1417.8 Yo+94.8 Zo+475.9
inline constexpr VECTOR3 FRCS_PROP_CG = {0.13462, -1.30848, 16.16688};// Xo+317.8 Yo+5.3 Zo+365.3
inline constexpr VECTOR3 LRCS_PROP_CG = {-2.0574, 1.3636, -9.92908};// Xo+1345.2 (eyeballed)Yo-81.0 Zo+470.5
inline constexpr VECTOR3 RRCS_PROP_CG = {2.0574, 1.3636, -9.92908};// Xo+1345.2 (eyeballed)Yo+81.0 Zo+470.5

#endif// _PARAMETERVALUES_H_
