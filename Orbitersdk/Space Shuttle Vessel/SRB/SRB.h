/****************************************************************************
  This file is part of Space Shuttle Vessel

  Solid Rocket Booster vessel definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/25   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/06/29   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/09   GLS
2021/12/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/03/24   GLS
2022/04/07   GLS
2022/04/17   GLS
********************************************/

#ifndef _SRB_H
#define _SRB_H
#pragma once

#include <Orbitersdk.h>
#include <cJSON.h>
#include <EngConst.h>


inline constexpr double SPM_MAX_PROPELLANT_MASS = 1110136.0 * LBM2KG;// HACK using same as HPM
inline constexpr double SPM_SRB_EMPTY_MASS = 188733.0 * LBM2KG;// from JSC-09095-57
inline constexpr double SPM_ISP0 = (267.3 - 3.0) * 9.80665;// 3 sec less than HPM
inline constexpr double SPM_ISP1 = 2368.79;// HACK using same as RSRM
inline constexpr double SPM_THRUST = 14145340.0;// from "Design Evolution of the Space Shuttle Solid Rocket Motors"
inline constexpr unsigned int SPM_nt = 30;
inline constexpr double SPM_Seq[SPM_nt] = {-0.001, 0.0, 5.0, 10.0, 15.0, 20.0, 21.5, 25.0, 30.0, 35.0,
				40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0,
				90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 160.0};
inline constexpr double SPM_Thrust[SPM_nt] = {0.0, 0.92, 0.94, 0.97, 0.99, 1.0, 1.0, 0.96, 0.89, 0.85,
				0.81, 0.78, 0.76, 0.75, 0.77, 0.8, 0.82, 0.83, 0.82, 0.77,
				0.73, 0.69, 0.64, 0.59, 0.53, 0.29, 0.1, 0.03, 0.01, 0.0};// from "Design Evolution of the Space Shuttle Solid Rocket Motors"
inline constexpr double SPM_Prop[SPM_nt] = {1.0, 1.0, 0.94525, 0.8905, 0.83575, 0.781, 0.771, 0.731, 0.681, 0.631,
				0.581, 0.539, 0.497, 0.455, 0.413, 0.36975, 0.3265, 0.28325, 0.24, 0.202,
				0.164, 0.126, 0.088, 0.058, 0.028, 0.012, 0.001, 0.0004, 0.0001, 0.0};// HACK using same as RSRM
inline constexpr double SPM_Pc[SPM_nt] = {0.0, 888.2, 871.5, 881.0, 882.7, 882.5, 870.0, 839.7, 775.7, 732.8,
				699.8, 664.0, 643.1, 627.3, 650.0, 669.0, 684.6, 688.1, 682.8, 637.3,
				605.8, 572.4, 529.7, 486.1, 432.0, 215.6, 74.7, 23.6, 8.2, 0.0};// HACK extrapolated from FWC and RSRM data

inline constexpr double HPM_MAX_PROPELLANT_MASS = 1110136.0 * LBM2KG;// from "Design Evolution of the Space Shuttle Solid Rocket Motors"
inline constexpr double HPM_SRB_EMPTY_MASS = 185396.0 * LBM2KG;// from JSC-09095-76 (LWT case)
inline constexpr double HPM_ISP0 = 267.3 * 9.80665;// from "Design Evolution of the Space Shuttle Solid Rocket Motors"
inline constexpr double HPM_ISP1 = 2368.79;// HACK using same as RSRM
inline constexpr double HPM_THRUST = 3310000.0 * 9.80665 * LBM2KG;// from "Design Evolution of the Space Shuttle Solid Rocket Motors"
inline constexpr unsigned int HPM_nt = 30;
inline constexpr double HPM_Seq[HPM_nt] = {-0.001, 0.0, 5.0, 10.0, 15.0, 20.0, 21.0, 25.0, 30.0, 35.0,
				40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0,
				90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 160.0};
inline constexpr double HPM_Thrust[HPM_nt] = {0.0, 0.95, 0.95, 0.99, 1.0, 1.0, 1.0, 0.96, 0.89, 0.84,
				0.81, 0.77, 0.75, 0.73, 0.75, 0.77, 0.78, 0.79, 0.79, 0.74,
				0.69, 0.66, 0.61, 0.56, 0.5, 0.26, 0.08, 0.02, 0.01, 0.0};// from "Design Evolution of the Space Shuttle Solid Rocket Motors"
inline constexpr double HPM_Prop[HPM_nt] = {1.0, 1.0, 0.94525, 0.8905, 0.83575, 0.781, 0.771, 0.731, 0.681, 0.631,
				0.581, 0.539, 0.497, 0.455, 0.413, 0.36975, 0.3265, 0.28325, 0.24, 0.202,
				0.164, 0.126, 0.088, 0.058, 0.028, 0.012, 0.001, 0.0004, 0.0001, 0.0};// HACK using same as RSRM
inline constexpr double HPM_Pc[HPM_nt] = {0.0, 917.2, 880.8, 899.2, 891.7, 882.5, 872.4, 839.7, 775.7, 724.1,
				699.8, 655.5, 634.6, 610.6, 633.1, 643.9, 651.2, 655.0, 657.8, 612.4,
				572.6, 547.5, 504.9, 461.4, 407.5, 193.3, 59.8, 15.7, 8.2, 0.0};// HACK extrapolated from FWC and RSRM data

inline constexpr double FWC_MAX_PROPELLANT_MASS = 1105486.0 * LBM2KG;// from "Space Shuttle Filament Wound Case Solid Rocket Motor Static Test Results (DM-6)"
inline constexpr double FWC_SRB_EMPTY_MASS = (185396.0 - 28000.0) * LBM2KG;// HACK value derived from the ~28000 lbs weight reduction from HPM to FWC
inline constexpr double FWC_ISP0 = 268.32 * 9.80665;// from "Space Shuttle Filament Wound Case Solid Rocket Motor Static Test Results (DM-6)"
inline constexpr double FWC_ISP1 = 2368.79;// HACK using same as RSRM
inline constexpr double FWC_THRUST = 15484260.0;// from "Space Shuttle Filament Wound Case Solid Rocket Motor Static Test Results (DM-6)"
inline constexpr unsigned int FWC_nt = 30;
inline constexpr double FWC_Seq[FWC_nt] = {-0.001, 0.0, 5.0, 10.0, 15.0, 20.0, 21.5, 25.0, 30.0, 35.0,
				40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0,
				90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 160.0};
inline constexpr double FWC_Thrust[FWC_nt] = {0.0, 0.95, 0.97, 1.0, 1.0, 1.0, 1.0, 0.95, 0.88, 0.84,
				0.8, 0.76, 0.74, 0.72, 0.73, 0.75, 0.76, 0.77, 0.76, 0.72,
				0.68, 0.63, 0.59, 0.53, 0.48, 0.28, 0.07, 0.02, 0.01, 0.0};// from "Space Shuttle Filament Wound Case Solid Rocket Motor Static Test Results (DM-6)"
inline constexpr double FWC_Prop[FWC_nt] = {1.0, 1.0, 0.94525, 0.8905, 0.83575, 0.781, 0.771, 0.731, 0.681, 0.631,
				0.581, 0.539, 0.497, 0.455, 0.413, 0.36975, 0.3265, 0.28325, 0.24, 0.202,
				0.164, 0.126, 0.088, 0.058, 0.028, 0.012, 0.001, 0.0004, 0.0001, 0.0};// HACK using same as RSRM
inline constexpr double FWC_Pc[FWC_nt] = {0.0, 912.0, 892.7, 900.7, 890.0, 880.7, 864.89, 828.0, 770.7, 722.0,
				698.0, 644.0, 618.0, 600.7, 616.7, 625.3, 633.3, 638.7, 633.3, 595.3,
				558.7, 522.0, 489.3, 441.3, 390.0, 176.0, 44.0, 12.0, 4.0, 0.0};// from "Space Shuttle Filament Wound Case Solid Rocket Motor Static Test Results (DM-6)"

inline constexpr double RSRM_MAX_PROPELLANT_MASS = 501673.161;// from ATK SRB fundamentals presentation
inline constexpr double RSRM_SRB_EMPTY_MASS = 87603.65;
inline constexpr double RSRM_ISP0 = 2638.89;
inline constexpr double RSRM_ISP1 = 2368.79;
inline constexpr double RSRM_THRUST = 14679131.3;
inline constexpr unsigned int RSRM_nt = 30;
inline constexpr double RSRM_Seq[RSRM_nt] = {-0.001, 0.0, 5.0, 10.0, 15.0, 20.0, 21.0, 25.0, 30.0, 35.0,
				40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0,
				90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 160.0};
inline constexpr double RSRM_Thrust[RSRM_nt] = {0.000, 0.95, 0.97, 0.99, 1.0, 1.0, 1.0, 0.93, 0.87, 0.82,
				0.78, 0.74, 0.7, 0.72, 0.73, 0.75, 0.76, 0.77, 0.74, 0.7,
				0.65, 0.62, 0.58, 0.53, 0.46, 0.18, 0.05, 0.01, 0.003, 0.0};// from "Flight Motor Set 360L001 (STS-26R) Final Report - Volume 1"
inline constexpr double RSRM_Prop[RSRM_nt] = {1.0, 1.0, 0.94525, 0.8905, 0.83575, 0.781, 0.771, 0.731, 0.681, 0.631,
				0.581, 0.539, 0.497, 0.455, 0.413, 0.36975, 0.3265, 0.28325, 0.24, 0.202,
				0.164, 0.126, 0.088, 0.058, 0.028, 0.012, 0.001, 0.0004, 0.0001, 0.0};// from "Flight Motor Set 360T004 (STS-30R) Final Report - Volume I (System Overview)"
inline constexpr double RSRM_Pc[RSRM_nt] = {0.0, 922.4, 906.0, 906.7, 893.3, 884.3, 874.7, 816.4, 754.5, 709.0,
				667.2, 632.8, 600.0, 603.7, 615.7, 629.1, 635.8, 638.1, 615.7, 579.9,
				544.8, 514.9, 479.1, 432.1, 376.1, 154.5, 43.3, 9.7, 3.7, 0.0};// from "Flight Motor Set 360L001 (STS-26R) Final Report - Volume 1"

const unsigned short SRB_SECTION_COUNT = 5;// 4 fueled segments and FWD skirt assembly

inline constexpr double SLAG_SPREAD = 0.2;

inline constexpr double SLAG1_RATE = 5;
inline constexpr double SLAG2_RATE = 11.0;
inline constexpr double SLAG3_RATE = 49.0;


// ==========================================================
// Interface for derived vessel class: Atlantis_SRB
// ==========================================================

class SRB: public VESSEL4 {
public:
	explicit SRB (OBJHANDLE hObj);
	~SRB( void );

	/**
	 * @param launch_time simtime at which SRB ignition occured (seconds)
	 * @param thrust_level thrust (between 0 and 1) of booster
	 * @param prop_level amount of fuel remaining (between 0 and 1)
	 */
	virtual void SetPostSeparationState(double launch_time, double thrust_level, double prop_level);

	// Overloaded callback functions
	void clbkVisualCreated(VISHANDLE vis, int refcount) override;
	void clbkVisualDestroyed(VISHANDLE vis, int refcount) override;
	void clbkSetClassCaps (FILEHANDLE cfg) override;
	void clbkPostStep (double simt, double simdt, double mjd) override;
	void clbkPostCreation () override;

	void clbkLoadStateEx(FILEHANDLE scn, void* status) override;
	void clbkSaveState(FILEHANDLE scn) override;

	virtual void GetSRB_State( double met, double &thrust_level, double &prop_level, double& pc );

	double SRB_MAX_PROPELLANT_MASS;
	double SRB_THRUST;
	double SRB_ISP0;
	double SRB_ISP1;
	unsigned int SRB_nt;
	const double* SRB_Seq;
	const double* SRB_Thrust;
	const double* SRB_Prop;
	const double* SRB_Pc;

private:
	typedef enum {SPM, HPM, FWC, RSRM} SRM_TYPE;

	bool Left;

	SRM_TYPE SRMtype;

	void SetTexture( DEVMESHHANDLE hDevMesh, SURFHANDLE tex );
	void LoadTextures( void );

	void LoadMissionFile( void );
	void LoadMissionV1( cJSON* root );

	void SetConfiguration( void );

	std::string strMission;

	MESHHANDLE hSRMSegmentMesh[SRB_SECTION_COUNT];
	UINT mesh_segment[SRB_SECTION_COUNT];

	SURFHANDLE hFwdAssemblyTexture;
	SURFHANDLE hCaseTexture;

	std::string strFwdAssemblyTextureName;
	std::string strCaseTextureName;

	VISHANDLE hVis;

	double t0;                  // reference time: liftoff
	double srb_separation_time; // simulation time at which SRB separation was initiated
	bool bMainEngine;           // main engine firing?
	bool bSeparationEngine;     // separation thrusters firing?
	double slag1, slag2, slag3;
	PROPELLANT_HANDLE ph_main;  // handle for propellant resource
	PROPELLANT_HANDLE phBSM;	//separation motor fuel resource
	THRUSTER_HANDLE th_main;    // engine handle
	THRUSTER_HANDLE thBSM[3];	//represent engines by a single logical thruster for each group.
	ATTACHMENTHANDLE ahToOrbiter;

	LightEmitter* SRBLight;
};

#endif// _SRB_H
