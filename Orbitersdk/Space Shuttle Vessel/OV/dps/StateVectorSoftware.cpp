/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/12/06   GLS
2022/11/12   indy91
2022/12/13   GLS
2022/12/18   indy91
2022/11/21   indy91
********************************************/
#include "StateVectorSoftware.h"
#include "../Atlantis.h"
#include "GNCUtilities.h"
#include "../vc/MDU.h"
#include <MathSSV.h>

namespace dps
{

void GetStateVectors(VESSEL* v, OBJHANDLE hEarth, VECTOR3& pos, VECTOR3& vel)
{
	v->GetRelativePos(hEarth, pos);
	v->GetRelativeVel(hEarth, vel);

	pos = ConvertBetweenLHAndRHFrames(pos);
	vel = ConvertBetweenLHAndRHFrames(vel);

	pos = mul(M_J2000_to_M50, pos);
	vel = mul(M_J2000_to_M50, vel);
}

StateVectorSoftware::StateVectorSoftware(SimpleGPCSystem * _gpc)
: SimpleGPCSoftware(_gpc, "StateVectorSoftware"),
R_M50_AT_LIFTOFF{0.0, 0.0, 0.0}, pTargetVessel(NULL)
{
	SQR_EMU = sqrt(EARTH_MU);

	//Near circular orbit at 28.5° inclination
	R_RESET = R_TV_RESET = _V(21824624.2, 0, 0);
	V_RESET = V_TV_RESET = _V(0, 22330.0, 12124.2);
	T_RESET = 0.0;
	FILT_UPDATE = false;

	lastUpdateSimTime = -10000.0;
	lastUpdateSimTime2 = -10000.0;

	//I-loads
	LOC = -0.03343547684;
	LOSK1 = 0.9174635884;
	LOSK3 = 0.3978197723;
	LOS_ZERO = 187.0760356051715;
	PHASE_C = 188.4343505051714;
}

StateVectorSoftware::~StateVectorSoftware()
{
}

void StateVectorSoftware::Realize()
{
	pGNCUtilities = dynamic_cast<GNCUtilities*>(FindSoftware("GNCUtilities"));
	assert((pGNCUtilities != NULL) && "OMSBurnSoftware::Realize.pGNCUtilities");

	hEarth = STS()->GetGravityRef();
	if(!targetVesselName.empty()) SetTargetVessel(const_cast<char*>(targetVesselName.c_str()));
	else
	{
		oapiWriteLogV( "(SSV_OV) [INFO] No rendezvous target vessel specified" );
	}

	//Make really sure the rendezvous navigation flag is off if there is no target vessel
	if (pTargetVessel == NULL)
	{
		WriteCOMPOOL_IS(SCP_DOING_REND_NAV, 0);
	}

	if (STS()->NonsphericalGravityEnabled())
	{
		GRAV_ZONAL[0] = 0.0; GRAV_ZONAL[1] = 1082.6271e-6; GRAV_ZONAL[2] = -2.5358868e-6; GRAV_ZONAL[3] = -1.624618e-6;
		GRAV_C[0] = 0.0; GRAV_C[1] = 0.0; GRAV_C[2] = 0.0; GRAV_C[3] = 0.0; GRAV_C[4] = 0.0; GRAV_C[5] = 0.0; GRAV_C[6] = 0.0; GRAV_C[7] = 0.0; GRAV_C[8] = 0.0;
		GRAV_S[0] = 0.0; GRAV_S[1] = 0.0; GRAV_S[2] = 0.0; GRAV_S[3] = 0.0; GRAV_S[4] = 0.0; GRAV_S[5] = 0.0; GRAV_S[6] = 0.0; GRAV_S[7] = 0.0; GRAV_S[8] = 0.0;

		//TBD: These are not supported by Orbiter. Use them when that changes
		//GRAV_C[0] = -2.7635957e-10; GRAV_C[1] = 1.5711423e-6; GRAV_C[2] = 2.1907694e-6; GRAV_C[3] = 3.0466825e-7; GRAV_C[4] = 9.7966803e-8;
		//GRAV_C[5] = -5.0552749e-7; GRAV_C[6] = 7.8842515e-8; GRAV_C[7] = 5.9073749e-8; GRAV_C[8] = -4.1542493e-9;
		//GRAV_S[0] = -5.2357454e-9; GRAV_S[1] = -9.0231337e-7; GRAV_S[2] = 2.7267074e-7; GRAV_S[3] = -2.1259298e-8; GRAV_S[4] = 1.9681077e-7;
		//GRAV_S[5] = -4.4125015e-7; GRAV_S[6] = 1.4818958e-7; GRAV_S[7] = -1.2140873e-8; GRAV_S[8] = 6.3163541e-9;
	}
	else
	{
		GRAV_ZONAL[0] = 0.0; GRAV_ZONAL[1] = 0.0; GRAV_ZONAL[2] = 0.0; GRAV_ZONAL[3] = 0.0;
		GRAV_C[0] = 0.0; GRAV_C[1] = 0.0; GRAV_C[2] = 0.0; GRAV_C[3] = 0.0; GRAV_C[4] = 0.0; GRAV_C[5] = 0.0; GRAV_C[6] = 0.0; GRAV_C[7] = 0.0; GRAV_C[8] = 0.0;
		GRAV_S[0] = 0.0; GRAV_S[1] = 0.0; GRAV_S[2] = 0.0; GRAV_S[3] = 0.0; GRAV_S[4] = 0.0; GRAV_S[5] = 0.0; GRAV_S[6] = 0.0; GRAV_S[7] = 0.0; GRAV_S[8] = 0.0;
	}

	UpdatePropagatorStateVectors();
	//Some things might need UPP state vectors on the first timestep
	WriteCOMPOOL_VD(SCP_R_AVGG, R_RESET);
	WriteCOMPOOL_VD(SCP_V_AVGG, V_RESET);
	WriteCOMPOOL_SD(SCP_T_STATE, T_RESET);
	WriteCOMPOOL_VD(SCP_R_TARGET, R_TV_RESET);
	WriteCOMPOOL_VD(SCP_V_TARGET, V_TV_RESET);
}

void StateVectorSoftware::OnPreStep(double simt, double simdt, double mjd)
{
	if (GetMajorMode() < 104) return;

	double timeBetweenUpdates = max(4.0, 4.0*oapiGetTimeAcceleration());
	if((simt-lastUpdateSimTime) > timeBetweenUpdates) {
		UpdatePropagatorStateVectors();

		lastUpdateSimTime = simt;
	}

	//On-Orbit/Rendezvous User Parameter Processing
	if (simt - lastUpdateSimTime2 > 0.96)
	{
		ONORBIT_REND_USER_PARAM_STATE_PROP();
		ONORBIT_USER_PARAMETER_CALCULATIONS();
		REL_EXEC();
		lastUpdateSimTime2 = simt;
	}
}

bool StateVectorSoftware::OnMajorModeChange(unsigned int newMajorMode)
{
	if(newMajorMode == 102) { // liftoff - get position at T0
		VECTOR3 vel;
		GetStateVectors(STS(), hEarth, R_M50_AT_LIFTOFF, vel);
	}
	if(newMajorMode >= 101 && newMajorMode <= 303) return true;
	return false;
}

bool StateVectorSoftware::ItemInput(int spec, int item, const char * Data, bool &IllegalEntry )
{
	if (spec != 33) return false;

	switch (item) {
	case 1:
		if (strlen(Data) == 0)
		{
			if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1)
			{
				WriteCOMPOOL_IS(SCP_DOING_REND_NAV, 0);
			}
			else if (pTargetVessel)
			{
				WriteCOMPOOL_IS(SCP_DOING_REND_NAV, 1);
			}
			else IllegalEntry = true;
		}
		else IllegalEntry = true;
		return true;
	}

	return false;
}

bool StateVectorSoftware::OnPaint(int spec, vc::MDU * pMDU) const
{
	if (spec != 33) return false;

	PrintCommonHeader("    REL NAV", pMDU);

	pMDU->mvprint(2, 1, "RNDZ NAV ENA 1");

	pMDU->mvprint(2, 2, "KU ANT   ENA 2");
	pMDU->mvprint(2, 3, "MEAS     ENA 3");

	pMDU->mvprint(9, 4, "VEL");
	pMDU->mvprint(2, 5, "SV SEL 4");
	pMDU->mvprint(2, 6, "RNG");
	pMDU->mvprint(2, 7, "R");
	pMDU->DotCharacter(2, 7);
	pMDU->Theta(2, 8);
	pMDU->mvprint(2, 9, "Y");
	pMDU->mvprint(2, 10, "Y");
	pMDU->DotCharacter(2, 10);
	pMDU->mvprint(2, 11, "NODE");

	pMDU->mvprint(19, 1, "SV UPDATE");
	pMDU->mvprint(20, 2, "POS");
	pMDU->mvprint(20, 3, "VEL");

	pMDU->mvprint(20, 5, "RR");

	pMDU->mvprint(20, 6, "RNG");
	pMDU->mvprint(20, 7, "R");
	pMDU->DotCharacter(20, 7);
	pMDU->mvprint(20, 8, "EL");
	pMDU->mvprint(20, 9, "AZ");
	pMDU->Omega(20, 10);
	pMDU->mvprint(21, 10, "P");
	pMDU->Omega(20, 11);
	pMDU->mvprint(21, 11, "R");

	pMDU->mvprint(13, 12, "FILTER");
	pMDU->mvprint(2, 13, "S TRK 12");
	pMDU->mvprint(14, 13, "RR 13");
	pMDU->mvprint(23, 13, "COAS 14");
	pMDU->mvprint(25, 14, "X");
	pMDU->mvprint(25, 15, "Y");
	pMDU->mvprint(2, 14, "STAT");
	pMDU->mvprint(2, 15, "FLTR UPDATE  15");
	pMDU->mvprint(2, 16, "COVAR REINIT 16");

	pMDU->mvprint(10, 17, "RESID");
	pMDU->mvprint(17, 17, "RATIO");
	pMDU->mvprint(23, 17, "ACPT");
	pMDU->mvprint(29, 17, "REJ");

	pMDU->mvprint(2, 18, "RNG");
	pMDU->mvprint(2, 19, "R");
	pMDU->DotCharacter(2, 19);
	pMDU->mvprint(2, 20, "V/EL/Y");
	pMDU->mvprint(2, 21, "H/AZ/Y");
	pMDU->mvprint(2, 22, "GPS");

	pMDU->mvprint(38, 16, "EDIT OVRD");
	pMDU->mvprint(36, 17, "AUT  INH  FOR");
	pMDU->mvprint(36, 18, "17   18   19");
	pMDU->mvprint(36, 19, "20   21   22");
	pMDU->mvprint(36, 20, "23   24   25");
	pMDU->mvprint(36, 22, "42   43   44");

	pMDU->mvprint(36, 2, "AVG G ON    5");

	pMDU->mvprint(41, 3, "GPS");
	pMDU->mvprint(37, 4, "STAT  P 1  DES");
	pMDU->Sigma(46, 4);
	pMDU->mvprint(34, 5, "1S");
	pMDU->mvprint(48, 5, "31");
	pMDU->mvprint(34, 6, "2S");
	pMDU->mvprint(48, 6, "32");
	pMDU->mvprint(34, 7, "3S");
	pMDU->mvprint(48, 7, "33");

	pMDU->mvprint(37, 8, "SV TRANSFER");
	pMDU->mvprint(35, 9, "FLTR MINUS PROP");
	pMDU->mvprint(36, 10, "POS");
	pMDU->mvprint(36, 11, "VEL");
	pMDU->mvprint(35, 12, "FLTR TO PROP  8");
	pMDU->mvprint(35, 13, "PROP TO FLTR  9");
	pMDU->mvprint(34, 14, "ORB   TO TGT  10");
	pMDU->mvprint(34, 15, "TGT   TO ORB  11");

	//The numbers for these lines were done by trial and error. Improve?
	pMDU->Line(15, 169, 332, 169);
	pMDU->Line(332, 44, 332, 223);
	pMDU->Line(332, 44, 500, 44);
	pMDU->Line(332, 113, 500, 113);
	pMDU->Line(332, 223, 500, 223);

	if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1)
	{
		pMDU->mvprint(16, 1, "*");

		//TBD: Anything that is blank with rendezvous navigation off
	}

	return true;
}

bool StateVectorSoftware::OnParseLine(const char* keyword, const char* value)
{
	if(!_strnicmp(keyword, "TARGET_VESSEL", 13)) {
		targetVesselName = value;
		return true;
	}
	else if(!_strnicmp(keyword, "T0_POS", 6)) {
		sscanf_s(value, "%lf%lf%lf", &R_M50_AT_LIFTOFF.x, &R_M50_AT_LIFTOFF.y, &R_M50_AT_LIFTOFF.z);
		return true;
	}
	else if (!_strnicmp(keyword, "DOING_REND_NAV", 14)) {
		WriteCOMPOOL_IS(SCP_DOING_REND_NAV, 1);
		return true;
	}
	return false;
}

void StateVectorSoftware::OnSaveState(FILEHANDLE scn) const
{
	if(!targetVesselName.empty()) oapiWriteScenario_string(scn, "TARGET_VESSEL", const_cast<char*>(targetVesselName.c_str()));
	oapiWriteScenario_vec(scn, "T0_POS", R_M50_AT_LIFTOFF);
	if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1) oapiWriteScenario_string(scn, "DOING_REND_NAV", "");
}

void StateVectorSoftware::SetTargetVessel(char* vesselName)
{
	OBJHANDLE hTarget = oapiGetVesselByName(vesselName);
	if(hTarget)	{
		pTargetVessel = oapiGetVesselInterface(hTarget);
		 targetVesselName = vesselName;
	}
	else {
		pTargetVessel = NULL;
		targetVesselName = "";
	}
}

void StateVectorSoftware::GetCurrentStateVectorsM50(VECTOR3& pos, VECTOR3& vel) const
{
	GetStateVectors(STS(), hEarth, pos, vel);
}

VECTOR3 StateVectorSoftware::GetPositionAtT0() const
{
	return R_M50_AT_LIFTOFF;
}

void StateVectorSoftware::UpdatePropagatorStateVectors()
{
	VECTOR3 pos, vel;

	GetStateVectors(STS(), hEarth, pos, vel);

	R_RESET = pos * MPS2FPS;
	V_RESET = vel * MPS2FPS;

	if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1)
	{
		GetStateVectors(pTargetVessel, hEarth, pos, vel);

		R_TV_RESET = pos * MPS2FPS;
		V_TV_RESET = vel * MPS2FPS;
	}

	T_RESET = ReadClock();
	FILT_UPDATE = true;
}

void StateVectorSoftware::ONORBIT_REND_USER_PARAM_STATE_PROP()
{
	VECTOR3 R_AVGG, V_AVGG;
	double T_STATE, T_IMU, DT_IMU;

	//Snap IMU time tag. TBD: Get IMU-accumulated sensed velocity and use actual IMU time
	T_IMU = ReadClock();

	//Is there a filter update?
	if (FILT_UPDATE)
	{
		//Update user parameter state vector with the one from the "filter"
		R_AVGG = R_RESET;
		V_AVGG = V_RESET;
		T_STATE = T_RESET;
	}
	else
	{
		//Continue to use user parameter state vector
		R_AVGG = ReadCOMPOOL_VD(SCP_R_AVGG);
		V_AVGG = ReadCOMPOOL_VD(SCP_V_AVGG);
		T_STATE = ReadCOMPOOL_SD(SCP_T_STATE);
	}

	//Compute the interval over which advancement is required
	DT_IMU = T_IMU - T_STATE;

	//TBD: Powered flag, measured acceleration etc

	//Call user parameter state integrator
	AVERAGE_G_INTEGRATOR(R_AVGG, V_AVGG, DT_IMU, _V(0, 0, 0), T_STATE, T_IMU);
	//Write result to COMPOOL
	WriteCOMPOOL_VD(SCP_R_AVGG, R_AVGG);
	WriteCOMPOOL_VD(SCP_V_AVGG, V_AVGG);

	if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1)
	{
		VECTOR3 R_TARGET, V_TARGET;

		//Is there a filter update?
		if (FILT_UPDATE)
		{
			//Update user parameter state vector with the one from the "filter"
			R_TARGET = R_TV_RESET;
			V_TARGET = V_TV_RESET;
		}
		else
		{
			//Continue to use user parameter state vector
			R_TARGET = ReadCOMPOOL_VD(SCP_R_TARGET);
			V_TARGET = ReadCOMPOOL_VD(SCP_V_TARGET);
		}

		//Call user parameter state integrator
		AVERAGE_G_INTEGRATOR(R_TARGET, V_TARGET, DT_IMU, _V(0, 0, 0), T_STATE, T_IMU);

		//Write result to COMPOOL
		WriteCOMPOOL_VD(SCP_R_TARGET, R_TARGET);
		WriteCOMPOOL_VD(SCP_V_TARGET, V_TARGET);
	}

	//Save time tag output for use in the next cycle
	WriteCOMPOOL_SD(SCP_T_STATE, T_IMU);
	//Set the filter flag to off
	FILT_UPDATE = false;
}

void StateVectorSoftware::ONORBIT_USER_PARAMETER_CALCULATIONS()
{
	//TBD
}

void StateVectorSoftware::REL_EXEC()
{
	if (ReadCOMPOOL_IS(SCP_DOING_REND_NAV) == 1)
	{
		REL_MO_PAR();
	}
}

void StateVectorSoftware::REL_MO_PAR()
{
	//TBD
}

void StateVectorSoftware::ONORBIT_PREDICT(VECTOR3 R_PRED_INIT, VECTOR3 V_PRED_INIT, double T_PRED_INIT, double T_PRED_FINAL, int GMOP, int GMDP, bool DMP, bool VMP, int ATMP, double PRED_STEP, VECTOR3 &R_PRED_FINAL, VECTOR3 &V_PRED_FINAL) const
{
	//INPUTS:
	//R_PRED_INIT: Initial position vector
	//V_PRED_INIT: Initial velocity vector
	//T_PRED_INIT: Time of initial state
	//T_PRED_FINAL: Final time at the end of the prediction interval
	//GMOP: Order of gravity potential
	//GMDP: Degree of gravity potential (GDMP >= GMDO)
	//DMP: Drag flag. false = don't consider, true = consider drag
	//VMP: Venting and uncoupled thrusting flag. false = don't consider venting, true = consider venting
	//ATMP: Vehicle-attitude flag.

	//OUTPUTS:
	//R_PRED_FINAL: Final position vector
	//V_PRED_FINAL: Final velocity vector

	double XN[7], DERIV[7], X[6], T_CUR, TIME_DEL, DT_STEP;

	//Rename initial state vector for use in the Pines equations-of-motion formulation and the seventh variable of integration (XN6) initialized to zero
	XN[0] = R_PRED_INIT.x;
	XN[1] = R_PRED_INIT.y;
	XN[2] = R_PRED_INIT.z;
	XN[3] = V_PRED_INIT.x;
	XN[4] = V_PRED_INIT.y;
	XN[5] = V_PRED_INIT.z;
	XN[6] = 0.0;

	//Make a check on the gravity mode flag (GMDP), to determine if prediction is to be accomplished through the use of a simple two-body solution or a more precise integration technique
	if (GMDP == 0)
	{
		//If a two-body solution is required, the predicted interval is computed as
		T_CUR = T_PRED_FINAL - T_PRED_INIT;
	}
	else
	{
		//If a more precise integration is required (GMDP != 0), several step are performed to set up parameters required for the integration process
		//Maximum step
		if (PRED_STEP > DT_MAX)
		{
			PRED_STEP = DT_MAX;
		}
		//The total prediction time interval is calculated from input initial and final times and the current integrator time is set to zero
		TIME_DEL = T_PRED_FINAL - T_PRED_INIT;
		T_CUR = 0.0;

		//If the total prediction time interval, TIME_DEL, is less than zero, a backward predcition has been requested and the internal integration step (DT_STEP)
		//is set to a negative value of the input step size
		if (TIME_DEL < 0.0)
		{
			DT_STEP = -PRED_STEP;
		}
		//Otherwise, TIME_DEL >= 0, the internal prediction step is set to the input prediction step
		else
		{
			DT_STEP = PRED_STEP;
		}

		//The actual integration of the Orbiter or target state equations (formulated according to the Pines technique) shall now be performed by proceeding as follows for
		//each step in the integration interval. Note that, in the Pines equations-of-motion formulation, it is the initial conditions (R_PRED_INIT, V_PRED_INIT, and T_PRED_INIT)
		//that are integrated and then used in the closed-form solution of a two-body, unperturbed orbital problem using an F and G series.

		//The fourth-order Runge-Kutta-Gill integration technique shall be invoked in conjunction with the Pines equation-of-motion formulation for each
		//predictor step until the prediction interval has been covered as follows (i.e. until T_CUR = TIME_DEL)
		do
		{
			//Check, on each step, to determine if the absolute value of the prediction step is greater than the absolute value of the prediction interval remaining
			if (abs(DT_STEP) > abs(TIME_DEL - T_CUR))
			{
				DT_STEP = TIME_DEL - T_CUR;
			}
			//The Runge-Kutta-Goll integrator is invoked, with the input or adjusted value of DT_STEP
			RK_GILL(XN, DT_STEP, T_CUR, GMOP, GMDP, DMP, VMP, ATMP, T_PRED_INIT);
			//The output vector (XN) are the adjusted initial conditions to be used in the Pines equations of motion for a precision prediction conic solution
		} while (abs(T_CUR - TIME_DEL) > PRED_TIME_TOL);
	}

	//After the calculations have been performed, the Pines equations of motion will be invoked to solve for the position and velocity vectors corresponding to T_PRED_FINAL
	PINES_METHOD(XN, T_CUR, GMOP, GMDP, DMP, VMP, ATMP, T_PRED_INIT, DERIV, X);
	//Upon being calculated (whether by a precise technique or a single	step two-body solution), the final position and velocity are renamed for output
	R_PRED_FINAL = _V(X[0], X[1], X[2]);
	V_PRED_FINAL = _V(X[3], X[4], X[5]);
}

void StateVectorSoftware::RK_GILL(double *XN, double DT_STEP, double &T_CUR, int GMO, int GMD, bool DM, bool VM, int ATM, double T_IN) const
{
	//INPUTS:
	//XN: an array containing the seven variables of integration (integrated initial conditions)
	//DT_STEP: the integration step size
	//T_CUR: the RK_GILL step size subinterval time (i.e., there are four cycles of RK_GILL per integration step size)
	//GMO: the Earth gravitational potential model order
	//GMD: the Earth gravitational potential model degree
	//DM: the drag acceleration model flag
	//VM: the vent and uncoupled thrust acceleration model flag
	//ATM: the vehicle attitude mode flag
	//T_IN: the initial state time

	//OUTPUTS:
	//XN: See above
	//T_CUR: See above

	double T_STOR, P, DERIV[7], X[6];
	double Q[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	int J, L;

	//The initial time of the current integration step, T_CUR, is saved	in T_STOR
	T_STOR = T_CUR;

	//A counter, J, is tested to ensure that four evaluations of Runge-Kutta-Gill are determined
	for (J = 0;J < 4;J++)
	{
		//A new value of T_CUR (the integration step size) is determined
		T_CUR = T_STOR + GRAV_AA[0] * GRAV_BB[J] * DT_STEP;
		//The Pines method is called to calculate derivatives (DERIV) of the initial condition
		PINES_METHOD(XN, T_CUR, GMO, GMD, DM, VM, ATM, T_IN, DERIV, X);
		//The Runge-Kutta-Gill integration continues with the numerical integration of derivatives of the initial condition (XN[L]), where:
		//AA, BB, CC, DD: premission-loaded array (J=0 to 3) containing coefficients required for this formulation of the Runge-Kutta- Gill integration technique
		//XN: an array containing the seven variables of integration
		//DERIV: an array containing the total derivatives of the initial conditions at the current time
		//P, Q[L]: integration variables used in the Runge-Kutta-Gill technique
		for (L = 0;L < 7;L++)
		{
			P = DT_STEP * DERIV[L];
			XN[L] = XN[L] + GRAV_AA[J] * (P - GRAV_BB[J] * Q[L]);
			Q[L] = GRAV_CC[J] * P + GRAV_DD[J] * Q[L];
		}
	}
}

void StateVectorSoftware::PINES_METHOD(double *XN, double T_CUR, int GMO, int GMD, bool DM, bool VM, int ATM, double T_IN, double *DERIV, double *X) const
{
	//INPUTS:
	//XN: The seven variables of integration
	//T_CUR: the initial integration time of the current step
	//GMO: Earth's gravitational potential model order
	//GMD: Earth's gravitational potential model degree
	//DM: drag model acceleration computation flag
	//VM: vent and thrusting acceleration model flag
	//ATM: attitude mode flag
	//T_IN: initial time

	//OUTPUTS:
	//DERIV: the output total derivatives of integration
	//X: Output two body position and velocity vectors of conic

	VECTOR3 R_IN, V_IN, R_OUT, V_OUT, G_CENTRAL, P;
	double R_IN_INV, SMA, C1, DELTAT, D_IN, F, G, FDOT, GDOT, S0, S1, S2, S3, THETA, T_ACCEL;
	double C2, C3, D_TAU, D_AUX, S4, S5, C4, C5, DD1, S6, R_IN_TAU, R_IN_AUX, F_TAU, G_TAU, FD_TAU, GD_TAU, R_FIN_INV;

	//Several terms used in the F and G series calculations for the closed-form two-body equations are computed
	R_IN = _V(XN[0], XN[1], XN[2]);
	R_IN_INV = 1.0 / length(R_IN);
	V_IN = _V(XN[3], XN[4], XN[5]);
	SMA = 1.0 / (2.0*R_IN_INV - dotp(V_IN, V_IN) / EARTH_MU);
	C1 = sqrt(SMA) / SQR_EMU;
	DELTAT = T_CUR - XN[6];
	D_IN = dotp(R_IN, V_IN);
	R_FIN_INV = 0.0;

	//The conic solution subfunction is invoked to calculate several terms used in computation of the conic position and velocity vectors
	F_AND_G(R_IN, V_IN, DELTAT, SMA, C1, R_IN_INV, D_IN, 0.0, F, G, FDOT, GDOT, S0, S1, S2, S3, R_OUT, R_FIN_INV, THETA);
	V_OUT = R_IN * FDOT + V_IN * GDOT;
	X[0] = R_OUT.x; X[1] = R_OUT.y; X[2] = R_OUT.z; X[3] = V_OUT.x; X[4] = V_OUT.y; X[5] = V_OUT.z;

	//Perturbation accelerations is now calculated and several computations are performed to compute perturbation derivatives for F and G series terms
	//used in calculating total derivatives of the seven variables of integration
	T_ACCEL = T_IN + T_CUR;
	P = ACCEL_ONORBIT(R_OUT, V_OUT, T_ACCEL, GMD, GMO, DM, VM, ATM, G_CENTRAL);
	P = P - G_CENTRAL;
	D_TAU = dotp(R_OUT, P);
	D_AUX = dotp(V_OUT, P);

	C2 = C1 * C1;
	S1 = C1 * S1;
	S2 = C2 * S2;
	C3 = 1.0 / C2;
	S3 = SMA * S2;
	S4 = 2.0 * S3*D_AUX;
	C4 = C2 * D_AUX;
	C5 = C4 * S1;
	S5 = S2 * D_TAU;

	DD1 = S1 * C3*length(R_IN)*(SMA*R_IN_INV - 1.0) + S0 * D_IN;
	S6 = 2.0 * S2*C4*DD1 + S5;
	R_IN_TAU = S4 - C2 * S1*D_AUX*DD1 - S1 * D_TAU;
	R_IN_AUX = R_IN_INV * R_IN_TAU;
	F_TAU = (S3*C3*R_IN_AUX - S4)*R_IN_INV;
	G_TAU = C5 / R_FIN_INV - S6;
	FD_TAU = FDOT * (C4 - R_IN_AUX);
	GD_TAU = -S4 * R_FIN_INV;

	//Finally, the total derivatives of the variables of integration are to be computed as follows
	DERIV[0] = GD_TAU * X[0] - G_TAU * X[3] - P.x *G;
	DERIV[1] = GD_TAU * X[1] - G_TAU * X[4] - P.y *G;
	DERIV[2] = GD_TAU * X[2] - G_TAU * X[5] - P.z *G;
	DERIV[3] = -FD_TAU * X[0] + F_TAU * X[3] + P.x*F;
	DERIV[4] = -FD_TAU * X[1] + F_TAU * X[4] + P.y*F;
	DERIV[5] = -FD_TAU * X[2] + F_TAU * X[5] + P.z*F;
	DERIV[6] = S6 - 3.0 * C4*SMA*(C1*THETA - S1) - C5 / R_FIN_INV;
}

void StateVectorSoftware::F_AND_G(VECTOR3 R_IN, VECTOR3 V_IN, double DELTAT, double SMA, double C1, double R_IN_INV, double D_IN, double D_FIN, double &F, double &G, double &FDOT, double &GDOT, double &S0, double &S1, double &S2, double &S3, VECTOR3 &R_FIN, double &R_FIN_INV, double &THETA) const
{
	//INPUTS:
	//SMA: Semi-major axis
	//DELTAT: transfer time
	//C1: auxiliary constant, equal to the square root of SMA divided by the square root of Earth's gravitational constant
	//R_IN: the initial position vector (M50)
	//R_IN_INV: the reciprocal of the magnitude of R_IN
	//R_FIN_INV: the reciprocal of R_FIN (if unknown, a zero shall be input)
	//V_IN: the initial velocity vector (M50)
	//D_IN: the dot product of the initial position and velocity vectors
	//D_FIN: the dot product of the final position and velocity vectors (if unknown, a zero shall be input)

	//OUTPUTS:
	//F, G, FDOT, GDOT: parameters of the difference in eccentric anomaly between initial position and velocity vectors and a final time when they are required
	//S0, S1, S2, S3: auxiliary variables
	//R_FIN_INV: see above
	//R_FIN: Final position vector
	//THETA: Difference in eccentric anomaly

	//Check the value of R_FIN_INV to see if Kepler's equation is to be solved
	if (R_FIN_INV == 0.0)
	{
		//The final position vector is to be calculated. This requires solving a modified form of Kepler's equation, which shall be accomplished by an iterative process
		double ONEMRIN, D_MN_AN, S0, S1, S2, ERR, THETA_COR;
		INT I;

		//Two auxiliary quantities shall be obtained from the input data
		ONEMRIN = (SMA - 1.0 / R_IN_INV) / SMA;
		D_MN_AN = DELTAT / (C1*SMA);

		THETA = D_MN_AN;
		I = 0;
		while (I < NUM_KEP_ITER)
		{
			S0 = cos(THETA);
			S1 = sin(THETA);
			S2 = 1.0 - S0;
			ERR = D_MN_AN - THETA - D_IN * C1*S2 / SMA + ONEMRIN * S1;
			THETA_COR = ERR / (1.0 + D_IN * C1*S1 / SMA - ONEMRIN * S0);
			THETA = THETA + THETA_COR;
			I++;
		}
	}
	else
	{
		//Final position vector is already known, calculate difference in eccentric anomaly
		THETA = (C1*(D_FIN - D_IN) + DELTAT / C1) / SMA;
	}

	//When the difference in eccentric anomaly is determined, certain auxiliary variables shall be calculated
	S0 = cos(THETA);
	S1 = sin(THETA);
	S2 = 1.0 - S0;
	S3 = THETA - S1;

	//The values of F and G shall then be determined
	F = 1.0 - SMA * S2*R_IN_INV;
	G = DELTAT - C1 * SMA*S3;

	//If the final position vector and the reciprocal of its magnitude were not known, they shall be calculated
	if (R_FIN_INV == 0.0)
	{
		R_FIN = R_IN * F + V_IN * G;
		R_FIN_INV = 1.0 / length(R_FIN);
	}

	//The functions FDOT and GDOT, required for the calculation of the final velocity vector, shall be evaluated
	FDOT = -EARTH_MU * C1*S1*R_IN_INV*R_FIN_INV;
	GDOT = 1.0 - SMA * S2*R_FIN_INV;
}

VECTOR3 StateVectorSoftware::ACCEL_ONORBIT(VECTOR3 R, VECTOR3 V, double T, int GMD, int GMO, bool DM, bool VM, int ATM, VECTOR3 &G_CENTRAL) const
{
	//Acceleration models

	//INPUTS:
	//GMD: Input degree of Earth gravitational potential model
	//GMO: Input order of Earth gravitational potential model
	//DM: Flag indicating use (true) or non-use (false) of vehicle drag acceleration model (ACCEL_ONORBIT_DRAG)
	//VM: Flag indicating use (true) or non-use (false) of vent and thrust model (ACCEL_ONORBIT_VENT_AND_THRUST)
	//ATM: Attitude mode flag (used when DM and/or VM are set to 1.)
	//R: Position vector of vehicle
	//V: Velocity vector of vehicle
	//T: Position and velocity vectors time tag

	//OUTPUTS:
	//G_CENTRAL: Point mass acceleration
	//Return value: total acceleration

	MATRIX3 FIFTY;
	VECTOR3 G, D, VENT, R_EF, UR;
	double R_INV;

	//Null non-spherical gravity, drag and vent acceleration vectors
	G = _V(0, 0, 0);
	D = _V(0, 0, 0);
	VENT = _V(0, 0, 0);

	//Get matrix
	FIFTY = pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T);
	R_EF = tmul(FIFTY, R);

	//Components of Earth fixed position unit vector
	R_INV = 1.0 / length(R);
	UR = unit(R_EF);

	//Acceleration vector due to the Earth's gravitational attraction as a point mass
	G_CENTRAL = -R * EARTH_MU*pow(R_INV, 3);

	// GMD is equal or greater than 2, the gravitational acceleration vector due to the Earth's non-sphericity is determined
	if (GMD >= 2)
	{
		ACCEL_EARTH_GRAV(UR, R_INV, GMO, GMD, FIFTY, G);
	}
	if (VM)
	{
		//TBD: ACCEL_ONONRBIT_VENT_AND_THRUST
	}
	if (DM)
	{
		//double SDEC, CDEC1, COS_SOL_RA, SIN_SOL_RA;
		//SOLAR_EPHEM(T, SDEC, CDEC1, COS_SOL_RA, SIN_SOL_RA);
	}

	//Finally, add vectors together
	return G_CENTRAL + G + D + VENT;
}

void StateVectorSoftware::ACCEL_EARTH_GRAV(VECTOR3 UR, double R_INV, int GMO, int GMD, const MATRIX3 &FIFTY, VECTOR3 &G_VEC) const
{
	double MAT_A[5][2];
	double ZETA_REAL[5], ZETA_IMAG[5];
	double R0_ZERO, R0_N, AUXILIARY, F1, F2, F3, F4, DNM;
	int I, N, J, N1, L;

	//The following variables are to be set up to serve as starting	values for recursive relations used in the Pines formulation
	//A is a two-column array used for temporary storage of Legendre polynomials and derived Legendre functions (which are latitude-dependent terms), and
	//R0_Nis the distance-related term. AUXILIARY is an intermediate scalar variable.
	R0_ZERO = EARTH_RADIUS_GRAV * R_INV;
	R0_N = R0_ZERO * EARTH_MU*R_INV*R_INV;
	MAT_A[0][1] = 3.0*UR.z;
	MAT_A[1][1] = 3.0;
	ZETA_REAL[0] = 1.0;
	ZETA_IMAG[0] = 0.0;
	L = 1;
	AUXILIARY = 0.0;

	//Effects of tesseral harmonics, terms that depend on the vehicle's longitude
	for (I = 1;I <= GMO;I++)
	{
		ZETA_REAL[I] = UR.x*ZETA_REAL[I - 1] - UR.y*ZETA_IMAG[I - 1];
		ZETA_IMAG[I] = UR.x*ZETA_IMAG[I - 1] + UR.y*ZETA_REAL[I - 1];
	}
	for (N = 2;N <= GMD;N++)
	{
		//Derived Legendre functions by means of recursion formulas, multiplied by appropiate combinations of tesseral harmonics (Legendre polynomials shall be multiplied by
		//zonal harmonics coefficients), and stored as certain auxiliary variables F1-F4.
		MAT_A[N][0] = 0.0;
		MAT_A[N][1] = (2.0*(double)N + 1.0)*MAT_A[N - 1][1];
		MAT_A[N - 1][0] = MAT_A[N - 1][1];
		MAT_A[N - 1][1] = UR.z*MAT_A[N][1];
		for (J = 2;J <= N;J++)
		{
			MAT_A[N - J][0] = MAT_A[N - J][1];
			MAT_A[N - J][1] = (UR.z*MAT_A[N - J + 1][1] - MAT_A[N - J + 1][0]) / ((double)J);
		}
		F1 = 0.0;
		F2 = 0.0;
		F3 = -MAT_A[0][0] * GRAV_ZONAL[N - 1];
		F4 = -MAT_A[0][1] * GRAV_ZONAL[N - 1];
		//If the maximum order of tesserals wanted has not been attained, do for N1=1 to N (these take into account contributions of tesseral and sectorial harmonics):
		if (N <= GMO)
		{
			for (N1 = 1;N1 <= N;N1++)
			{
				F1 = F1 + (double)N1*MAT_A[N1 - 1][0] * (GRAV_C[L - 1] * ZETA_REAL[N1 - 1] + GRAV_S[L - 1] * ZETA_IMAG[N1 - 1]);
				F2 = F2 + (double)N1*MAT_A[N1 - 1][0] * (GRAV_S[L - 1] * ZETA_REAL[N1 - 1] - GRAV_C[L - 1] * ZETA_IMAG[N1 - 1]);
				DNM = GRAV_C[L - 1] * ZETA_REAL[N1] + GRAV_S[L - 1] * ZETA_IMAG[N1];
				F3 = F3 + DNM * MAT_A[N1][0];
				F4 = F4 + DNM * MAT_A[N1][1];
				L++;
			}
		}
		//Multiply the sum of zonal and tesseral effects by appropiate distance-related factors, store the results as components of the acceleration vector G_VEC, and prepare for 
		//final computation by obtaining the intermediate scalar variable AUXILIARY, which accounts for an additional effect proportional to the unit radius vector UR.
		R0_N = R0_N * R0_ZERO;
		G_VEC.x = G_VEC.x + R0_N * F1;
		G_VEC.y = G_VEC.y + R0_N * F2;
		G_VEC.z = G_VEC.z + R0_N * F3;
		AUXILIARY = AUXILIARY + R0_N * F4;
	}
	//Lastly, the planet fixed acceleration vector shall be obtained and rotated to ecliptic coordinates
	G_VEC = G_VEC - UR * AUXILIARY;
	G_VEC = mul(FIFTY, G_VEC);
}

void StateVectorSoftware::SOLAR_EPHEM(double T, double &SDEC, double &CDEC1, double &COS_SOL_RA, double &SIN_SOL_RA) const
{
	double LOS;

	LOS = LOS_ZERO + T * LOS_R - LOC * sin(T*OMEG_C + PHASE_C);
	SDEC = LOSK3 * sin(LOS);
	CDEC1 = sqrt(1.0 - SDEC * SDEC);
	COS_SOL_RA = cos(LOS) / CDEC1;
	SIN_SOL_RA = LOSK1 * sin(LOS) / CDEC1;
}

void StateVectorSoftware::AVERAGE_G_INTEGRATOR(VECTOR3 &R_AV, VECTOR3 &V_AV, double DTIME, VECTOR3 AC, double T_STATE, double T_IMU) const
{
	//INPUTS:
	//R_AV and V_AV: user parameter state vector
	//DTIME: interval to propagate state vector
	//AC: acceleration vector
	//T_STATE: user parameter time tag
	//T_IMU: current time

	//OUTPUTS:
	//R_AV and V_AV: user parameter state vector

	VECTOR3 GR, GR1, G_CENTRAL;

	GR = ACCEL_ONORBIT(R_AV, V_AV, T_STATE, 2, 0, false, false, 0, G_CENTRAL);
	R_AV = R_AV + (V_AV + (AC + GR)*DTIME*0.5)*DTIME;
	GR1 = ACCEL_ONORBIT(R_AV, V_AV, T_IMU, 2, 0, false, false, 0, G_CENTRAL);
	V_AV = V_AV + (AC + (GR + GR1)*0.5)*DTIME;
}

void StateVectorSoftware::ENTRY_PRECISE_PREDICTOR(VECTOR3 R_INIT, VECTOR3 V_INIT, double T_INIT, double T_FINAL, int GMD_PRED, int GMO_PRED, double DT_MAX, VECTOR3 &R_FINAL, VECTOR3 &V_FINAL) const
{
	//INPUTS:
	//R_INIT, V_INIT and T_INIT: initial state and time
	//T_FINAL: time at which the final state is desired
	//GMD_PRED and GMO_PRED: gravitational model indicators
	//DT_MAX: Upper bound for the integration step size

	//OUTPUTS:
	//R_FINAL and V_FINAL: final state

	//Save initial as final state
	R_FINAL = R_INIT;
	V_FINAL = V_INIT;

	VECTOR3 G_PREVIOUS, G_FINAL;
	double STEP_SIZE, T, R_INV;
	int NUMBER_STEPS;

	//Establish the fixed integration STEP_SIZE by dividing the time interval into the smallest number(NUMBER_STEPS) of subintervals consistent with DT_MAX
	NUMBER_STEPS = (int)(max(round(abs(T_FINAL - T_INIT) / DT_MAX), 1));
	STEP_SIZE = (T_FINAL - T_INIT) / NUMBER_STEPS;
	T = T_INIT;

	//Check the input parameter GMD_PRED. If the value of this parameter is zero (a setting which indicates the user wants to use
	//a conic approximation), the acceleration vector G_PREVIOUS will contain only the central force term
	if (GMD_PRED == 0)
	{
		CENTRAL(R_FINAL, G_PREVIOUS, R_INV);
	}
	else
	{
		G_PREVIOUS = ACCEL_ENTRY(R_FINAL, V_FINAL, T, GMD_PRED, GMO_PRED);
	}

	for (int I = 0;I < NUMBER_STEPS;I++)
	{
		//Advance the time by an amount equal to STEP_SIZE
		T = T + STEP_SIZE;
		//Advance the position
		R_FINAL = R_FINAL + (V_FINAL + G_PREVIOUS * 0.5*STEP_SIZE)*STEP_SIZE;

		if (GMD_PRED == 0)
		{
			CENTRAL(R_FINAL, G_FINAL, R_INV);
		}
		else
		{
			G_FINAL = ACCEL_ENTRY(R_FINAL, V_FINAL, T, GMD_PRED, GMO_PRED);
		}

		//Advance the velocity
		V_FINAL = V_FINAL + (G_PREVIOUS + G_FINAL)*0.5*STEP_SIZE;
		//Obtain a corrected value for the position
		R_FINAL = R_FINAL + (G_FINAL - G_PREVIOUS)*pow(STEP_SIZE, 2) / 6.0;
		//Save the value of G for the next cycle
		G_PREVIOUS = G_FINAL;
	}
}

void StateVectorSoftware::CENTRAL(VECTOR3 R, VECTOR3 &ACCEL, double &R_INV) const
{
	R_INV = 1.0 / length(R);
	ACCEL = -R * EARTH_MU*pow(R_INV, 3);
}

VECTOR3 StateVectorSoftware::ACCEL_ENTRY(VECTOR3 R, VECTOR3 V, double T, int GMD, int GMO) const
{
	VECTOR3 ACCEL;
	double R_INV;

	CENTRAL(R, ACCEL, R_INV);

	if (GMD != 0)
	{
		MATRIX3 FIFTY;
		VECTOR3 G, D, R_EF, UR;

		G = D = _V(0, 0, 0);
		FIFTY = pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T);
		R_EF = tmul(FIFTY, R);
		UR = R_EF * R_INV;
		ACCEL_EARTH_GRAV(UR, R_INV, GMO, GMD, FIFTY, G);

		if (GMD == 4)
		{
			//TBD: Drag
		}
		ACCEL = ACCEL + G + D;
	}
	return ACCEL;
}

}
