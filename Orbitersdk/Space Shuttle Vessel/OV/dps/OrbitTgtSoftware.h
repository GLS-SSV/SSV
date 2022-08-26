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
********************************************/
#ifndef ORBITTGTSOFTWARE_H_E031D277_4DA3_4827_9F8D_D2BB8BE2F2D8
#define ORBITTGTSOFTWARE_H_E031D277_4DA3_4827_9F8D_D2BB8BE2F2D8
#pragma once

#include "SimpleGPCSoftware.h"
#include "LambertBurnTargeting.h"

namespace dps
{
	class OMSBurnSoftware;
	class StateVectorSoftware;
/**
 * Struct for I-Load maneuvers.
 * Not used yet (I-loading maneuver data is not implemented)
 */
struct BurnTargetingData
{
	//LVLH offset position for target sets, in kilofeet
	VECTOR3 finalOffset;
	//Maneuver elevation angle, in degrees
	double elevation;
	//T1 time for target sets (times are relative to prox ops base time), in minutes
	double T1_TIG;
	//Delta times from T1 maneuver to T2 maneuver for target sets, in minutes
	double transferTime;

	BurnTargetingData& operator = (const BurnTargetingData& rhs) {
		// copy all values from other config into this one
		finalOffset = rhs.finalOffset;
		elevation = rhs.elevation;
		T1_TIG = rhs.T1_TIG;
		transferTime = rhs.transferTime;
		return *this;
	}
};

/**
 * GPC software for targeting rendezvous burns (solving Lambert/Gauss problem).
 * Implements SPEC 34 ORBIT TGT display.
 */
class OrbitTgtSoftware : public SimpleGPCSoftware
{
	LambertBurnTargeting burnTargeting;

	OMSBurnSoftware* pOMSBurnSoftware;
	StateVectorSoftware* pStateVectorSoftware;

	//COMMONS

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
	double DISP_PRED_MATCH;

	//Lambert variables
	int ALARM;

	//General variables

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

	//Time of the computed maneuver (MET)
	double T_MAN;
	//Prox ops Orbiter M50 state vector
	VECTOR3 RS_M50_PROX, VS_M50_PROX;
	//Prox ops target M50 state vector
	VECTOR3 RT_M50_PROX, VT_M50_PROX;

	int GUID_FLAG;

	//I-LOADS
	BurnTargetingData targetData[40];
	//Tolerance on minimum time in the future to compute a prox ops maneuver solution
	double PROX_DT_MIN;
	//Tolerance on minimum time in the future to compute a Lambert maneuver solution
	double PROX_DTMIN_LAMB;
	//Number of Lambert targeted target sets
	int NLAMB;
	//Tolerance between computed and desired elevation angle
	double EL_TOL;
	//Elevation angle-differential altitude incompatibility, tolerance
	double EL_DH_TOL;

	//Maximum step size used during any given iteration
	double DEL_T_MAX;
	//DX guess to be used in iterator if no prediction is possible
	double DEL_X_GUESS;
	//Maximum allowed number of iterations
	int IC_MAX;
	//Tolerance of dependent variable to ensure that a slope exists
	double DEL_X_TOL;
	
public:
	explicit OrbitTgtSoftware(SimpleGPCSystem* _gpc);
	virtual ~OrbitTgtSoftware();

	void Realize() override;

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
	VECTOR3 OFFSET_TGT(VECTOR3 X_OFFTGT, VECTOR3 XD_OFFTGT, VECTOR3 X2_OFFTGT, double DT_OFFTGT);
	//Orbiter LVLH transformation task
	void ORBLV(VECTOR3 RS, VECTOR3 VS, VECTOR3 RT, VECTOR3 VT, VECTOR3 &RSLV, VECTOR3 &VSLV);
	//Relative state prediction task
	void REL_PRED(VECTOR3 X, VECTOR3 XD, double DTIME, VECTOR3 &X2, VECTOR3 &XD2);
	//Relative state compute task
	void REL_COMP(bool INER_TO_LVC, VECTOR3 R_T_INER, VECTOR3 V_T_INER, VECTOR3 &R_S_INER, VECTOR3 &V_S_INER, VECTOR3 &R_REL, VECTOR3 &V_REL);
	//Proximity operations targeting output display load task
	void PROX_DISP_LOAD();
	//Newton-Raphson iteration task
	bool ITERV(int &IC, double X_DEP, double &X_DEP_PRIME, double &X_IND, double &X_IND_PRIME, double DEL_X_GUESS_TEMP, int ICMAX_TEMP, double DEL_X_TOL_TEMP);
	//Elevation angle iteration task
	void ELITER(int &IC, double ERR, double &ERR_PRIME, double &TTPI, double &TTPI_PRIME, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT);
	//Elevation angle computation task
	double COMELE(VECTOR3 RS_COM, VECTOR3 VS_COM, VECTOR3 RT_COM);
	//Delta-T compute task
	void DT_COMP(double T1_TIG, double &T2_TIG, double &COMP_RPOX_DT);
	//Omega-DT calculation task
	void OMEGA_DT_COMP();
	//Elevation angle search task
	double TELEV(double EL_ANG, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT);
	//Precision-required velocity task
	VECTOR3 PREVR(double T1_TIG, double T2_TIG, VECTOR3 RS_T1TIG, VECTOR3 VS_T1TIG, VECTOR3 RS_T2TIG);
	//State vector update task
	void UPDATVP(int S_OPTION, VECTOR3 R_IN, VECTOR3 V_IN, double T_IN, double T_OUT, VECTOR3 &R_OUT, VECTOR3 &V_OUT);

	//Utility
	MATRIX3 LVLHMatrix(VECTOR3 R, VECTOR3 V);
	void SaveTargetData(char *buf, BurnTargetingData cfg, unsigned int i) const;
	void LoadTargetData(const char *val, BurnTargetingData &cfg, unsigned int &i);
};

};

#endif // ORBITTGTSOFTWARE_H_E031D277_4DA3_4827_9F8D_D2BB8BE2F2D8