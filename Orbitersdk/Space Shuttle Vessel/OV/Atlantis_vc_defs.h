/****************************************************************************
  This file is part of Space Shuttle Vessel

  Constants used for defining VC views/positions


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
2020/03/20   GLS
2020/03/29   GLS
2020/05/08   GLS
2020/05/17   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/07/01   GLS
2021/08/24   GLS
2021/10/09   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Constants used for defining VC views/positions



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
#ifndef __ATLANTIS_VC_DEFS_H
#define __ATLANTIS_VC_DEFS_H
#pragma once

#include <Orbitersdk.h>
#include "ParameterValues.h"


/**
 * list of the VC positions
 */
inline constexpr int VC_CDR = 0;
inline constexpr int VC_PLT = 1;
inline constexpr int VC_MS1 = 2;
inline constexpr int VC_MS2 = 3;
inline constexpr int VC_MS3 = 4;
inline constexpr int VC_MS4 = 5;
inline constexpr int VC_MS5 = 6;
inline constexpr int VC_MSSTATION = 7;
inline constexpr int VC_AFTPILOT = 8;
inline constexpr int VC_RMSSTATION = 9;
inline constexpr int VC_PSSTATION = 10;
inline constexpr int VC_ONORBITSTATION = 11;

inline constexpr int VC_DOCKCAM = 12;
inline constexpr int VC_PLBCAMA = 13;
inline constexpr int VC_PLBCAMB = 14;
inline constexpr int VC_PLBCAMC = 15;
inline constexpr int VC_PLBCAMD = 16;
inline constexpr int VC_RMSCAMELBOW = 17;
inline constexpr int VC_RMSCAMWRIST = 18;

//New panel positions for pilot and commander
inline constexpr int VC_PANELR4 = 20;
inline constexpr int VC_PANELL4 = 21;
//Beginning of Mid deck positions
inline constexpr int VC_PANELMA73C = 100;
inline constexpr int VC_GALLEY = 101;
inline constexpr int VC_WMC = 102;
//Beginning of external airlock positions
inline constexpr int VC_EXT_AL = 200;

const static char* VC_LBL_CDR = "Commander seat";
const VECTOR3 VC_POS_CDR = _V( -0.671257, 2.629396, 14.1 );
const VECTOR3 VC_DIR_CDR = _V( 0, 0, 1 );
const VECTOR3 VC_OFS_CDR_F = _V( 0.0185, 0.0155, 0.115 );// HUD
const double VC_AZ_CDR_F = 0;
const double VC_EL_CDR_F = -8 * RAD;
const VECTOR3 VC_OFS_CDR_L = _V( -0.3, 0, 0 );// center panels
const double VC_AZ_CDR_L = 75 * RAD;
const double VC_EL_CDR_L = -5 * RAD;
const VECTOR3 VC_OFS_CDR_R = _V( 0.3, 0, 0 );// window 1
const double VC_AZ_CDR_R = -20 * RAD;
const double VC_EL_CDR_R = -27 * RAD;
const VECTOR3 VC_HUDPOS_CDR = _V( -0.6527025, 2.59925, 14.614 );

const static char* VC_LBL_PLT = "Pilot seat";
const VECTOR3 VC_POS_PLT = _V( 0.671257, 2.629396, 14.1 );
const VECTOR3 VC_DIR_PLT = _V( 0, 0, 1 );
const VECTOR3 VC_OFS_PLT_F = _V( -0.0185, 0.0155, 0.115 );// HUD
const double VC_AZ_PLT_F = 0;
const double VC_EL_PLT_F = -8 * RAD;
const VECTOR3 VC_OFS_PLT_L = _V( -0.3, 0, 0 );// center panels
const double VC_AZ_PLT_L = 20 * RAD;
const double VC_EL_PLT_L = -27 * RAD;
const VECTOR3 VC_OFS_PLT_R = _V( 0.2, -0.1, 0.25 );// panel R2
const double VC_AZ_PLT_R = -90 * RAD;
const double VC_EL_PLT_R = -72 * RAD;
const VECTOR3 VC_HUDPOS_PLT = _V(0.6528925, 2.59925, 14.614);

const static char* VC_LBL_MS1 = "MS1 seat";
const VECTOR3 VC_POS_MS1 = OFS_SEAT3 + OFS_HEAD;
const VECTOR3 VC_DIR_MS1 = _V( 0.0, 0.0, 1.0 );
const VECTOR3 VC_OFS_MS1_F = _V( 0.1, -0.1, 0.2 );
const double VC_AZ_MS1_F = -20 * RAD;
const double VC_EL_MS1_F = 0;
const VECTOR3 VC_OFS_MS1_L = _V( -0.1, -0.1, 0.1 );
const double VC_AZ_MS1_L = 45 * RAD;
const double VC_EL_MS1_L = -5 * RAD;
const VECTOR3 VC_OFS_MS1_R = _V( 0.1, 0, 0.1 );
const double VC_AZ_MS1_R = -70 * RAD;
const double VC_EL_MS1_R = -40 * RAD;

const static char* VC_LBL_MS2 = "MS2 seat";
const VECTOR3 VC_POS_MS2 = OFS_SEAT4 + OFS_HEAD;
const VECTOR3 VC_DIR_MS2 = _V( 0.0, 0, 1.0 );
const VECTOR3 VC_OFS_MS2_F = _V( 0, 0, 0.3 );
const double VC_AZ_MS2_F = 0;
const double VC_EL_MS2_F = 0;
const VECTOR3 VC_OFS_MS2_L = _V( -0.3, 0, 0.1 );// panels O14/O15
const double VC_AZ_MS2_L = 0;
const double VC_EL_MS2_L = 70 * RAD;
const VECTOR3 VC_OFS_MS2_R = _V( 0.3, 0, 0.1 );// panels O15/O16
const double VC_AZ_MS2_R = 0;
const double VC_EL_MS2_R = 70 * RAD;

const static char* VC_LBL_MS3 = "MS3 seat";
const VECTOR3 VC_POS_MS3 = OFS_SEAT5 + OFS_HEAD;
const VECTOR3 VC_POS_MS3_ESCAPE = OFS_SEAT5A + OFS_HEAD;
const VECTOR3 VC_DIR_MS3 = _V( 0.0, 0.0, 1.0 );
const VECTOR3 VC_OFS_MS3_F = _V( 0.1, -0.1, 0.2 );
const double VC_AZ_MS3_F = -20 * RAD;
const double VC_EL_MS3_F = 0;
const VECTOR3 VC_OFS_MS3_L = _V( -0.1, -0.1, 0.1 );
const double VC_AZ_MS3_L = 45 * RAD;
const double VC_EL_MS3_L = -5 * RAD;
const VECTOR3 VC_OFS_MS3_R = _V( 0.1, 0, 0.1 );
const double VC_AZ_MS3_R = -70 * RAD;
const double VC_EL_MS3_R = -40 * RAD;

const static char* VC_LBL_MS4 = "MS4 seat";
const VECTOR3 VC_POS_MS4 = OFS_SEAT6 + OFS_HEAD;
const VECTOR3 VC_DIR_MS4 = _V( 0.0, 0.0, 1.0 );
const VECTOR3 VC_OFS_MS4_F = _V( 0.1, -0.1, 0.2 );
const double VC_AZ_MS4_F = -20 * RAD;
const double VC_EL_MS4_F = 0;
const VECTOR3 VC_OFS_MS4_L = _V( -0.1, -0.1, 0.1 );
const double VC_AZ_MS4_L = 45 * RAD;
const double VC_EL_MS4_L = -5 * RAD;
const VECTOR3 VC_OFS_MS4_R = _V( 0.1, 0, 0.1 );
const double VC_AZ_MS4_R = -70 * RAD;
const double VC_EL_MS4_R = -40 * RAD;

const static char* VC_LBL_MS5 = "MS5 seat";
const VECTOR3 VC_POS_MS5 = OFS_SEAT7 + OFS_HEAD;
const VECTOR3 VC_DIR_MS5 = _V( 0.0, 0.0, 1.0 );
const VECTOR3 VC_OFS_MS5_F = _V( 0.1, -0.1, 0.2 );
const double VC_AZ_MS5_F = -20 * RAD;
const double VC_EL_MS5_F = 0;
const VECTOR3 VC_OFS_MS5_L = _V( -0.1, -0.1, 0.1 );
const double VC_AZ_MS5_L = 45 * RAD;
const double VC_EL_MS5_L = -5 * RAD;
const VECTOR3 VC_OFS_MS5_R = _V( 0.1, 0, 0.1 );
const double VC_AZ_MS5_R = -70 * RAD;
const double VC_EL_MS5_R = -40 * RAD;

const static char* VC_LBL_MSSTATION = "Mission Specialist Station";
const VECTOR3 VC_POS_MSSTATION = _V( 0.6, 2.95, 13.0 );
const VECTOR3 VC_DIR_MSSTATION = _V( cos( 25.0 * RAD ), -sin( 25.0 * RAD ), 0 );
const VECTOR3 VC_OFS_MSSTATION_F = _V( 0.3, 0, 0 );
const double VC_AZ_MSSTATION_F = 0;
const double VC_EL_MSSTATION_F = -30.0 * RAD;
const VECTOR3 VC_OFS_MSSTATION_L = _V( 0.3, 0, 0.2 );// panel R11
const double VC_AZ_MSSTATION_L = 15.0 * RAD;
const double VC_EL_MSSTATION_L = -30.0 * RAD;
const VECTOR3 VC_OFS_MSSTATION_R = _V( 0.55, -0.3, -0.55 );// panel R13
const double VC_AZ_MSSTATION_R = -10.0 * RAD;
const double VC_EL_MSSTATION_R = -30.0 * RAD;

const static char* VC_LBL_AFTPILOT = "Aft Pilot Station";
const VECTOR3 VC_POS_AFTPILOT = _V( 0.4, 3.15, 12.7 );
const VECTOR3 VC_DIR_AFTPILOT = _V( 0, 0, -1 );
const VECTOR3 VC_OFS_AFTPILOT_F = _V( 0.4, 3.15, 12.6 ) - VC_POS_AFTPILOT;// COAS
const double VC_AZ_AFTPILOT_F = 0;
const double VC_EL_AFTPILOT_F = 90.0 * RAD;
const VECTOR3 VC_OFS_AFTPILOT_L = _V( 0.5, -0.5, 0.0 );// panel A1
const double VC_AZ_AFTPILOT_L = 20.0 * RAD;
const double VC_EL_AFTPILOT_L = -10.0 * RAD;
const VECTOR3 VC_OFS_AFTPILOT_R = _V( -0.4, 0.0, 0.0 );// panel A2
const double VC_AZ_AFTPILOT_R = 0;
const double VC_EL_AFTPILOT_R = 0;

const static char* VC_LBL_RMSSTATION = "RMS Station";
const VECTOR3 VC_POS_RMSSTATION = _V( -0.4, 3.15, 12.7 );
const VECTOR3 VC_DIR_RMSSTATION = _V( 0.0, 0.0, -1.0 );
const VECTOR3 VC_OFS_RMSSTATION_F = _V( 0.4, 3.15, 12.6 ) - VC_POS_AFTPILOT;
const double VC_AZ_RMSSTATION_F = 0;
const double VC_EL_RMSSTATION_F = 90.0 * RAD;
const VECTOR3 VC_OFS_RMSSTATION_L = _V( -0.07, -0.05, -0.35 );// window 10
const double VC_AZ_RMSSTATION_L = 0;
const double VC_EL_RMSSTATION_L = 0;
const VECTOR3 VC_OFS_RMSSTATION_R = _V( 0, -0.3, 0.15 );// panel A8
const double VC_AZ_RMSSTATION_R = 0;
const double VC_EL_RMSSTATION_R = 0;

const static char* VC_LBL_PSSTATION = "Payload Specialist Station";
const VECTOR3 VC_POS_PSSTATION = _V( -0.6, 2.95, 13.0 );
const VECTOR3 VC_DIR_PSSTATION = _V( -cos( 25.0 * RAD ), -sin( 25.0 * RAD ), 0 );
const VECTOR3 VC_OFS_PSSTATION_F = _V( -0.3, 0, 0 );// panel L11
const double VC_AZ_PSSTATION_F = 0;
const double VC_EL_PSSTATION_F = -30 * RAD;
const VECTOR3 VC_OFS_PSSTATION_L = _V( -0.45, -0.2, -0.35 );// panel L12
const double VC_AZ_PSSTATION_L = 20 * RAD;
const double VC_EL_PSSTATION_L = -25 * RAD;
const VECTOR3 VC_OFS_PSSTATION_R = _V( -0.3, 0, 0.3 );// panel L10
const double VC_AZ_PSSTATION_R = 0;
const double VC_EL_PSSTATION_R = -30 * RAD;

const static char* VC_LBL_ONORBITSTATION = "On Orbit Station";
const VECTOR3 VC_POS_ONORBITSTATION = _V( 0.0, 2.95, 13.2 );
const VECTOR3 VC_DIR_ONORBITSTATION = _V( 0.0, 0.0, -1.0 );
const VECTOR3 VC_OFS_ONORBITSTATION_F = _V( 0.0, 0.0, -0.2 );
const double VC_AZ_ONORBITSTATION_F = 0.0 * RAD;
const double VC_EL_ONORBITSTATION_F = -20.0 * RAD;
const VECTOR3 VC_OFS_ONORBITSTATION_L = _V( 0.4, -0.2, -0.2 );
const double VC_AZ_ONORBITSTATION_L = 0.0 * RAD;
const double VC_EL_ONORBITSTATION_L = -25.0 * RAD;
const VECTOR3 VC_OFS_ONORBITSTATION_R = _V( 0.0, -0.35, -0.2 );
const double VC_AZ_ONORBITSTATION_R = 0.0 * RAD;
const double VC_EL_ONORBITSTATION_R = -25.0 * RAD;

const static char* VC_LBL_DOCKCAM = "ODS centerline camera";

const static char* VC_LBL_RMSCAMELBOW = "RMS Elbow camera";

const static char* VC_LBL_RMSCAMWRIST = "RMS Wrist camera";

const static char* VC_LBL_PLBCAMA = "Payload bay A camera";

const static char* VC_LBL_PLBCAMB = "Payload bay B camera";

const static char* VC_LBL_PLBCAMC = "Payload bay C camera";

const static char* VC_LBL_PLBCAMD = "Payload bay D camera";


const static char* VC_LBL_PANELMA73C = "Panel MA73C";
const VECTOR3 VC_POS_PANELMA73C = _V( -1.248346, 0.771165, 13.461403 );
const VECTOR3 VC_DIR_PANELMA73C = _V( 0.0, 0.0, -1.0 );

const static char* VC_LBL_GALLEY = "Galley";
const VECTOR3 VC_POS_GALLEY = _V( -0.95, 0.15, 15.1 );
const VECTOR3 VC_DIR_GALLEY = _V( -1.0, 0.0, 0.0 );

const static char* VC_LBL_WMC = "Waste Management Compartment";
const VECTOR3 VC_POS_WMC = _V( -1.7646, 0.477935, 12.612556 );
const VECTOR3 VC_DIR_WMC = _V( 0.0, 0.0, 1.0 );

const static char* VC_LBL_EXT_AL = "External Airlock";
const VECTOR3 VC_POS_EXT_AL = _V(0.0, 0.1, 2.0);
const VECTOR3 VC_DIR_EXT_AL = _V(0.0, -sin(24.5*RAD), cos(24.5 * RAD));

const static char* VC_LBL_PANELR4 = "Panel R4";
const VECTOR3 VC_POS_PANELR4 = _V( 1.271257, 2.229396, 14.2 );
const VECTOR3 VC_DIR_PANELR4 = _V( 0, -sin( 15 * RAD ), -cos( 15 * RAD ) );
const double VC_TILT_PANELR4 = 90.0 * RAD;
const VECTOR3 VC_OFS_PANELR4_F = _V( 0, 0, 0.3 );
const double VC_AZ_PANELR4_F = 0;
const double VC_EL_PANELR4_F = 0;
const VECTOR3 VC_OFS_PANELR4_L = _V( -0.3, 0, 0 );
const double VC_AZ_PANELR4_L = 20 * RAD;
const double VC_EL_PANELR4_L = -27 * RAD;
const VECTOR3 VC_OFS_PANELR4_R = _V( 0.2, -0.1, 0.25 );
const double VC_AZ_PANELR4_R = -90 * RAD;
const double VC_EL_PANELR4_R = -72 * RAD;

const static char* VC_LBL_PANELL4 = "Panel L4";
const VECTOR3 VC_POS_PANELL4 = _V( -1.271257, 2.229396, 14.2 );
const VECTOR3 VC_DIR_PANELL4 = _V( 0, 0, -1 );
const double VC_TILT_PANELL4 = -90.0 * RAD;
const VECTOR3 VC_OFS_PANELL4_F = _V( 0, 0, 0.3 );
const double VC_AZ_PANELL4_F = 0;
const double VC_EL_PANELL4_F = 0;
const VECTOR3 VC_OFS_PANELL4_L = _V( -0.3, 0, 0 );
const double VC_AZ_PANELL4_L = 20 * RAD;
const double VC_EL_PANELL4_L = -27 * RAD;
const VECTOR3 VC_OFS_PANELL4_R = _V( 0.2, -0.1, 0.25 );
const double VC_AZ_PANELL4_R = -90 * RAD;
const double VC_EL_PANELL4_R = -72 * RAD;


const static char* TEXT_RCSCONTROL = "Controlling RCS";
const static char* TEXT_RMSCONTROL = "Controlling RMS";


#endif //__ATLANTIS_VC_DEFS_H
