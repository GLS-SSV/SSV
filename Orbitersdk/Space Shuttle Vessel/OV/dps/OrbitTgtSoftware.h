/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbit Targeting definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/11/28   GLS
2022/11/29   GLS
********************************************/
#ifndef _dps_ORBITTGTSOFTWARE_H_
#define _dps_ORBITTGTSOFTWARE_H_


#include "SimpleGPCSoftware.h"

namespace dps
{
	class OMSBurnSoftware;
	class StateVectorSoftware;

/**
 * GPC software for targeting rendezvous burns (solving Lambert/Gauss problem).
 * Implements SPEC 34 ORBIT TGT display.
 */
class OrbitTgtSoftware : public SimpleGPCSoftware
{
	OMSBurnSoftware* pOMSBurnSoftware;
	StateVectorSoftware* pStateVectorSoftware;

	double CalculationTimer;

	//COMMONS

	//World

	//Orbit targeting executive first pass status flag
	bool PROX_FIRST_PASS_STATUS;
	//Background calculations in progress
	bool BACKGROUND_CALC;
	//Begin targeting calculations flag
	bool START_BACKGROUND;
	//Alarm discrete requesting TGT ITER to be display
	bool ALARM_A;
	//Alarm discrete requesting TGT EL ANG to be display
	bool ALARM_B;
	//Alarm discrete requesting TGT ITER to be display
	bool ALARM_C;
	//Alarm discrete requesting TGT DELTA T to be display
	bool ALARM_D;

	//Display variables

	//T1 maneuver compute star flag
	bool PROX_T1_STAR_STATUS;
	//T2 maneuver compute star glag
	bool PROX_T2_STAR_STATUS;
	//Maneuver past time status flag
	bool PROX_PAST_STATUS;
	//ILOAD set number selected for targeting
	int PROX_TGT_SET_NO;
	//Displayed delta-t between T1 and T2
	double DISP_PROX_DT;
	//Displayed target elevation angle at T1, degrees
	double DISP_EL_ANG;
	//Displayed relative position at T1, kilofeet
	VECTOR3 DISP_T1_X;
	//Displayed relative position at T2, ft/s
	VECTOR3 DISP_T1_XD;
	//Displayed T1 time
	double DISP_T1_TIG[4];
	//Displayed T2 time
	double DISP_T2_TIG[4];
	//Orbiter desired relative position at T2, kilofeet
	VECTOR3 DISP_T2_OFF;
	//Maneuver LVLH velocity vector
	VECTOR3 DISP_DV;
	//Maneuver velocity mangitude
	double DISP_DV_MAG;
	//Item 1 data entry status flag
	bool PROX_ITEM_1_STATUS;
	//Item 2 through 20 data entry status flag
	bool PROX_ITEM_2TO20_STATUS;
	//Item 21 through 24 data entry status flag
	bool PROX_ITEM_21TO24_STATUS;
	//Item 25 data entry status flag
	bool PROX_ITEM_25_STATUS;
	//Item 26 data entry status flag
	bool PROX_ITEM_26_STATUS;
	//Item 28 data entry status flag
	bool PROX_ITEM_28_STATUS;
	//Item 29 data entry status flag
	bool PROX_ITEM_29_STATUS;
	//"LOAD" flash status flag
	bool PROX_LOAD_FLASH;
	//Targeting base time
	double PROX_BASE[4];
	//Displayed maneuver time
	double DISP_TMAN_TIME;
	double DISP_TMAN[4];
	//Target set for which maneuver was computed
	int MAN_TGT;
	//Convergence of solution
	double DSP_MISS;

	//General variables (PROX_VARIABLES_COMMON)

	//T1 maneuver time (MET)
	double T1_TIG;
	//T2 maneuver time (MET)
	double T2_TIG;
	//Current MET time
	double PROX_T_CURRENT;
	//Prox ops base time
	double PROX_BASE_TIME;

	//Delta-t in the computation buffer
	double COMP_PROX_DT;
	//Computational desired position at T2, meters
	VECTOR3 COMP_T2_OFF;
	//Impulsive maneuver in LVLH reference frame
	VECTOR3 DV_LVLH;
	//Time tag for M50 state (assumed MET)
	double TIME_PROX;

	//Use the WT calculation flag
	bool USE_OMEGA_DT;
	//Use displayed relative state flag
	bool USE_DISP_REL_STATE;
	//Computation relative position, meters
	VECTOR3 COMP_X;
	//Computation relative velocity, meters/second
	VECTOR3 COMP_XD;
	//Orbital angular rate of target
	double OMEGA_PROX;

	//Desired elevation angle at TPI, radians
	double EL_ANG;
	//Rotation flag for near 180° transfers
	int S_ROTATE;
	//Offset position vector
	VECTOR3 R_OFFSET;
	//Time of offset position vector (MET)
	double T_OFFSET;

	//Time of the computed maneuver (MET)
	double T_MAN;
	//Prox ops Orbiter M50 state vector
	VECTOR3 RS_M50_PROX, VS_M50_PROX;
	//Prox ops target M50 state vector
	VECTOR3 RT_M50_PROX, VT_M50_PROX;
	//Guidance option flag
	bool GUID_FLAG;
	//Target mode discrete
	bool LAMB;
	//Stop computations flag
	bool ALARM_KILL;

	//I-LOADS
	// T1 time for target sets (times are relative to prox ops base time), in minutes
	double T1_ILOAD_ARRAY[40];
	// Delta times from T1 maneuver to T2 maneuver for target sets, in minutes
	double DT_ILOAD_ARRAY[40];
	//Maneuver elevation angle, in radians
	double EL_ILOAD_ARRAY[40];
	// LVLH offset position for target sets, in feet
	double XOFF_ILOAD_ARRAY[40];
	double YOFF_ILOAD_ARRAY[40];
	double ZOFF_ILOAD_ARRAY[40];
	//Target mode discrete. 1 = Lambert, 0 = Clohessy-Wiltshire
	unsigned short LAMB_ILOAD[40];
	//Tolerance on minimum time in the future to compute a prox ops maneuver solution
	double PROX_DT_MIN;
	//Tolerance on minimum time in the future to compute a Lambert maneuver solution
	double PROX_DTMIN_LAMB;
	//Referenced base time for targetData
	double BASE_START[4];
	//Tolerance between computed and desired elevation angle
	double EL_TOL;
	//Elevation angle-differential altitude incompatibility, tolerance
	double EL_DH_TOL;
	//Convergence tolerance in terminal point offset iteration
	double R_TOL;
	//Maximum allowed number of iterations
	int N_MAX_ITER;
	//Angular tolerance used to determine if the transfer angle	is near 180°
	double CONE;
	//Maximum step size used during any given iteration
	double DEL_T_MAX;
	//Small deviation to prevent orbit from being almost parabolic
	double DU;
	//Parameter to test if transfer angle is close to 0°
	double EP_TRANSFER;
	//Parameter to test convergence of the Newton–Raphson iteration
	double EPS_U;
	//Minimum allowed number of iterations
	int N_MIN;
	//DX guess to be used in iterator if no prediction is possible. 1 = for OMEGA_DT_COMP, 2 = for ELITER
	double DEL_X_GUESS[2];
	//Maximum allowed number of iterations
	int IC_MAX;
	//Tolerance of dependent variable to ensure that a slope exists
	double DEL_X_TOL[2];
	//Gravity model degree flag
	int GMD_I;
	//Gravity model order flag
	int GMO_I;
	//Attitude mode flag
	int ATM_I[2];
	//Integration step size
	double DTMIN_I;
	//Drag model flag
	bool DMP_I[2];
	//Vent model flag
	bool VMP_I[2];
	//Earth gravitational constant
	double EARTH_MU;
	//CW iteration tolerance
	double R_TOL_CW;

	
public:
	explicit OrbitTgtSoftware(SimpleGPCSystem* _gpc);
	virtual ~OrbitTgtSoftware();

	void Realize() override;

	void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput(int spec, int item, const char* Data, bool &IllegalEntry ) override;
	bool OnPaint(int spec, vc::MDU* pMDU) const override;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;
private:
	//void StartCalculatingT1Burn();

	//Proximity operations targeting executive task
	void PROX_EXEC();
	//Proximity operations targeting status task
	void PROX_STAT();
	//Proximity operations targeting status task
	void PROX_TGT_SEL();
	//Proximity operations targeting initialization task
	void PROX_INIT();
	//Proximity operations targeting guidance quantity transfer task
	void PROX_TRANS();
	//Proximity operations targeting supervisory logic task
	void PROX_TGT_SUP();
	//Proximity operations targeting supervisory Lambert logic task
	void PROX_TGT_SUP_LAMB();
	//Proximity operations targeting start timer task
	void PROX_STIME();
	//Maneuver to offset targeting task
	void OFFSET_TGT(VECTOR3 X_OFFTGT, VECTOR3 XD_OFFTGT, VECTOR3 X2_OFFTGT, double DT_OFFTGT, double DIFF_DR, VECTOR3 &DV);
	//Orbiter LVLH transformation task
	VECTOR3 ORBLV(VECTOR3 RS, VECTOR3 VS, VECTOR3 DV_INER);
	//Relative state compute task
	void REL_COMP(bool INER_TO_LVC, VECTOR3 R_T_INER, VECTOR3 V_T_INER, VECTOR3 &R_S_INER, VECTOR3 &V_S_INER, VECTOR3 &R_REL, VECTOR3 &V_REL);
	//Proximity operations targeting output display load task
	void PROX_DISP_LOAD();
	//Newton-Raphson iteration task
	bool ITERV(int &IC, double X_DEP, double &X_DEP_PRIME, double &X_IND, double &X_IND_PRIME, double FIRST_JUMP, double DY_TOL);
	//Elevation angle iteration task
	void ELITER(int &IC, double ERR, double &ERR_PRIME, double &TTPI, double &TTPI_PRIME, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT);
	//Elevation angle computation task
	double COMELE(VECTOR3 RS_COM, VECTOR3 VS_COM, VECTOR3 RT_COM);
	//Delta-T compute task
	void DT_COMP(double T1_TIG, double &T2_TIG, double &COMP_RPOX_DT);
	//Omega-DT calculation task
	void OMEGA_DT_COMP();
	//Elevation angle search task
	void TELEV(double EL_ANG, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT, double &TTPI);
	//Precision velocity-required task
	void PREVR(double T1_TIG, double T2_TIG, VECTOR3 RS_T1TIG, VECTOR3 VS_T1TIG, VECTOR3 RS_T2TIG, VECTOR3 &VS_REQUIRED);
	//State vector update task
	void UPDATVP(int S_OPTION, VECTOR3 R_IN, VECTOR3 V_IN, double T_IN, double T_OUT, VECTOR3 &R_OUT, VECTOR3 &V_OUT);
	//Lambert conic-velocity-required task
	void LAMBERT(VECTOR3 R0, VECTOR3 R1, VECTOR3 UN, double DEL_T_TRAN, VECTOR3 &VS_REQUIRED);

	//Utility
	MATRIX3 LVLHMatrix(VECTOR3 R, VECTOR3 V);
	void SaveTargetData(char *buf, unsigned int i) const;
	void LoadTargetData(const char *val);
};

}

#endif// _dps_ORBITTGTSOFTWARE_H_
