/****************************************************************************
  This file is part of Space Shuttle Vessel

  State Vector Software definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/26   indy91
2022/09/29   GLS
2022/12/13   GLS
2022/12/18   indy91
2022/12/21   indy91
2022/12/23   GLS
********************************************/
#ifndef _STATEVECTORSOFTWARE_H_
#define _STATEVECTORSOFTWARE_H_

#include "../SimpleGPCSoftware.h"

namespace dps
{
	class GNCUtilities;

/**
 * GPC code for propagating state vectors.
 * Will eventually implemented SPEC 33 REL NAV display.
 */
class StateVectorSoftware : public SimpleGPCSoftware
{
	OBJHANDLE hEarth;
	double lastUpdateSimTime; //4s rate
	double lastUpdateSimTime2; //0.96s rate

	std::string targetVesselName;
	VESSEL* pTargetVessel;
public:
	explicit StateVectorSoftware(SimpleGPCSystem* _gpc);
	~StateVectorSoftware();

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput(int item, const char* Data);
	bool OnPaint(vc::MDU* pMDU) const;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;

	/**
	 * Sets target vessel for tracking. This is the vessel that will be used for rendezvous burn targeting, etc.
	 * In real life, MCC will just upload state vectors for target. Ku/star tracker data will be used (REL NAV display) to refine shuttle's orbit data.
	 * In Orbiter, vessel name will be specified and we will track vessel.
	 * NOTE: code assumes target vessel is not deleted at any point
	 */
	void SetTargetVessel(char* vesselName);

	void GetCurrentStateVectorsM50(VECTOR3& pos, VECTOR3& vel) const;
	VECTOR3 GetPositionAtT0() const;

	//OPS2
	void ONORBIT_PREDICT(VECTOR3 R_PRED_INIT, VECTOR3 V_PRED_INIT, double T_PRED_INIT, double T_PRED_FINAL, int GMOP, int GMDP, bool DMP, bool VMP, int ATMP, double PRED_STEP, VECTOR3 &R_PRED_FINAL, VECTOR3 &V_PRED_FINAL) const;
	//OPS3
	void ENTRY_PRECISE_PREDICTOR(VECTOR3 R_INIT, VECTOR3 V_INIT, double T_INIT, double T_FINAL, int GMD_PRED, int GMO_PRED, double DT_MAX, VECTOR3 &R_FINAL, VECTOR3 &V_FINAL) const;
private:
	void UpdatePropagatorStateVectors();

	//OPS2
	//Integration of the equations of motion
	void RK_GILL(double *XN, double DT_STEP, double &T_CUR, int GMO, int GMD, bool DM, bool VM, int ATM, double T_IN) const;
	//Equations of motion
	void PINES_METHOD(double *XN, double T_CUR, int GMO, int GMD, bool DM, bool VM, int ATM, double T_IN, double *DERIV, double *X) const;
	//Conic solution
	void F_AND_G(VECTOR3 R_IN, VECTOR3 V_IN, double DELTAT, double SMA, double C1, double R_IN_INV, double D_IN, double D_FIN, double &F, double &G, double &FDOT, double &GDOT, double &S0, double &S1, double &S2, double &S3, VECTOR3 &R_FIN, double &R_FIN_INV, double &THETA) const;
	//Acceleration model
	VECTOR3 ACCEL_ONORBIT(VECTOR3 R0, VECTOR3 V0, double T0, int GMD, int GMO, bool DM, bool VM, int ATM, VECTOR3 &G_CENTRAL) const;
	//Non-spherical gravity acceleration
	void ACCEL_EARTH_GRAV(VECTOR3 UR, double R_INV, int GMO, int GMD, const MATRIX3 &FIFTY, VECTOR3 &G_VEC) const;
	//Solar ephemeris
	void SOLAR_EPHEM(double T, double &SDEC, double &CDEC1, double &COS_SOL_RA, double &SIN_SOL_RA) const;
	//Average G
	void AVERAGE_G_INTEGRATOR(VECTOR3 &R_AV, VECTOR3 &V_AV, double DTIME, VECTOR3 AC, double T_STATE, double T_IMU) const;
	//UPP
	void ONORBIT_REND_USER_PARAM_STATE_PROP();
	void ONORBIT_USER_PARAMETER_CALCULATIONS();
	//REL NAV
	void REL_EXEC();
	void REL_MO_PAR();

	//OPS3
	void CENTRAL(VECTOR3 R, VECTOR3 &ACCEL, double &R_INV) const;
	VECTOR3 ACCEL_ENTRY(VECTOR3 R, VECTOR3 V, double T, int GMD, int GMO) const;

	//VARIABLES

	//Shuttle and target propagated state vectors
	VECTOR3 R_RESET, V_RESET;
	double T_RESET;
	VECTOR3 R_TV_RESET, V_TV_RESET;
	bool FILT_UPDATE;

	//Liftoff state vector in M50 coordinate for OPS 1 PEG-4
	VECTOR3 R_M50_AT_LIFTOFF;

	//Square root of EARTH_MU
	double SQR_EMU;

	//I-LOADS

	//Solar ephemeris
	double LOC, LOSK1, LOSK3, LOS_ZERO, PHASE_C;

	//CONSTANTS

	//Should be constants, but are not to support spherical gravity
	//Zonal harmonics coefficients used in ACCEL_EARTH_GRAV
	double GRAV_ZONAL[4];
	//Tesseral harmonics coefficients used in ACCEL_EARTH_GRAV
	double GRAV_C[9], GRAV_S[9];

	//Array of coefficients required by RK_GILL
	const double GRAV_AA[4] = { 0.5, 1.0 - sqrt(0.5), 1.0 + sqrt(0.5), 1.0 / 6.0 };
	const double GRAV_BB[4] = { 0.0, 1.0, 1.0, 2.0 };
	const double GRAV_CC[4] = { 1.0, 2.0*(1.0 - sqrt(0.5)), 2.0*(1.0 + sqrt(0.5)), 0.0 };
	const double GRAV_DD[4] = { 0.0, -2.0 + 3.0*sqrt(0.5), -2.0 - 3.0*sqrt(0.5), 0.0 };

	//Coefficients used in ACCEL_ONORBIT solar ephemeris model
	const double OMEG_C = 1.990968715e-7;
	const double LOS_R = 1.990986594e-7;

	//Time tolerance for predictor
	const double PRED_TIME_TOL = 1.e-8;
	//Maximum number of iterationsin the solution of Kepler's equation (F and G)
	const int NUM_KEP_ITER = 5;
	//Maximum integration step size used for prediction
	const double DT_MAX = 1200.0;

	GNCUtilities* pGNCUtilities;
};

}

#endif// _STATEVECTORSOFTWARE_H_
