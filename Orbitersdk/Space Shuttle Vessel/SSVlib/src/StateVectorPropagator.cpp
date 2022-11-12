/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/06/16   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/09/30   GLS
********************************************/
#include <cassert>
#include <StateVectorPropagator.h>
#include <MathSSV.h>

//StateVectorPropagator::StateVectorPropagator(const VECTOR3& pos, const VECTOR3& vel, OBJHANDLE hPlanet, double _vesselMass, double currentMET)
	//: curPos(pos), curVel(vel), curMET(currentMET), vesselMass(_vesselMass)
StateVectorPropagator::StateVectorPropagator(double propagationStepLength, int _iterationsPerStep, double _maxPropagationTime)
	: stepLength(propagationStepLength), iterationsPerStep(_iterationsPerStep), maxPropagationTime(_maxPropagationTime),
	lastSaveMET(-1000.0), maxPropMET(-1000.0), propMET(0), perturbFunction(NULL)
{
}

StateVectorPropagator::~StateVectorPropagator()
{
}

void StateVectorPropagator::SetParameters(double vesselMass, double planetMass, double _planetRadius, double J2Coeff)
{
	GM = planetMass*GGRAV;
	mu = GGRAV*(planetMass+vesselMass);
	planetRadius = _planetRadius;
	J2 = J2Coeff;
}

void StateVectorPropagator::DefinePerturbations(PropagatorPerturbation* pertubations)
{
	perturbFunction = pertubations;
}

void StateVectorPropagator::UpdateVesselMass(double vesselMass)
{
	mu = GM + GGRAV*vesselMass;
}

bool StateVectorPropagator::UpdateStateVector(const VECTOR3& equPos, const VECTOR3& equVel, double met, bool forceUpdate)
{
	// only update vectors if last set of state vectors has been propagated to limit or error between propagated and actual vectors exceeds limit
	const double MAX_POS_ERROR = 100.0; // max position error in any axis
	const double MAX_VEL_ERROR = 2.0; // max velocity error in any axis
	bool retVal = false;
	if(propMET < maxPropMET && !forceUpdate) {
		VECTOR3 curPos, curVel;
		GetStateVectors(met, curPos, curVel);
		if(Eq(curPos, equPos, MAX_POS_ERROR) && Eq(curVel, equVel, MAX_VEL_ERROR)) {
			return false; // no need to update vectors
		}
		else {
			stateVectors.clear(); // state vectors have changed (probably due to maneuer or pertubration), so clear out old vectors
			retVal = true; // if we have not propagated vectors to limit, return true (since state vectors have changed)
		}
	}
	else if(forceUpdate) stateVectors.clear(); // state vectors have changed (probably due to maneuer or pertubration), so clear out old vectors

	propPos = equPos;
	propVel = equVel;
	propMET = met;
	maxPropMET = met+maxPropagationTime;
	lastSaveMET = propMET-1000.0; // force data to be saved
	lastStateVectorUpdateMET = met;

	if(stateVectors.size()==0) {
		kostStateVector state;
		state.pos = ConvertBetweenLHAndRHFrames(equPos);
		state.vel = ConvertBetweenLHAndRHFrames(equVel);
		stateVectors.insert(std::make_pair(met, state));
	}
	/*if(stateVectors.size() > 0) {
		VECTOR3 pos, vel;
		GetStateVectors(met, pos, vel);
		//sprintf_s(oapiDebugString(), 256, "Pos error: %f %f %f Vel error: %f %f %f total pos error: %f total vel error: %f",
			//propPos.x-pos.x, propPos.y-pos.y, propPos.z-pos.z, propVel.x-vel.x, propVel.y-vel.y, propVel.z-vel.z, length(propPos-pos), length(propVel-vel));
	}*/

	return retVal;
}

/*void StateVectorPropagator::GetState(VECTOR3& pos, VECTOR3& vel) const
{
	pos = curPos;
	vel = curVel;
}*/
void StateVectorPropagator::Step(double currentMET, double simdt)
{
	// delete any elements older than current time
	while(stateVectors.size()>1 && stateVectors.begin()->first < currentMET) stateVectors.erase(stateVectors.begin());

	if(propMET<maxPropMET && simdt<(stepLength*iterationsPerStep)) { // don't bother propagating if time acceleration is too fast
		Propagate(iterationsPerStep, stepLength);

		if((propMET-lastSaveMET) > 20.0) {
			// clean out values from old state vectors
			MapConstIterator start = stateVectors.upper_bound(lastSaveMET);
			if(start != stateVectors.end()) {
				MapConstIterator end = stateVectors.lower_bound(propMET);
				stateVectors.erase(start, end);
				//if(start != end) stateVectors.erase(start, end);
				//else stateVectors.erase(start);
			}
			// save state vectors
			kostStateVector state;
			state.pos=ConvertBetweenLHAndRHFrames(propPos);
			state.vel=ConvertBetweenLHAndRHFrames(propVel);
			stateVectors.insert(std::make_pair(propMET, state));
			lastSaveMET = propMET;
		}
	}
	//sprintf_s(oapiDebugString(), 256, "SVP propMET: %f maxMET: %f", propMET, maxPropMET);
}

double StateVectorPropagator::GetElements(double MET, ELEMENTS& el, kostOrbitParam* oparam) const
{
	//std::deque<double>::iterator it = std::lower_bound(stateVectorTimestamps.
	//std::map<double, kostStateVector>::const_iterator it = stateVectors.lower_bound(MET);
	MapConstIterator it = stateVectors.lower_bound(MET);
	if(it == stateVectors.end()) --it; // set iterator to last element in map
	kostStateVector2Elements(mu, &(it->second), &el, oparam);
	return it->first;
}

void StateVectorPropagator::GetStateVectors(double MET, VECTOR3& pos, VECTOR3& vel) const
{
	ELEMENTS el;
	double epoch = GetElements(MET, el);
	kostStateVector state;
	kostElements2StateVectorAtTime(mu, &el, &state, MET-epoch, 1e-5, 50, planetRadius, 0.0);
	pos = ConvertBetweenLHAndRHFrames(state.pos);
	vel = ConvertBetweenLHAndRHFrames(state.vel);
}

void StateVectorPropagator::GetApogeeData(double currentMET, double& ApD, double& METAtApogee) const
{
	if(stateVectors.size() == 0) return; // no data

	bool bIncreasingAlt = false;
	MapConstIterator it=stateVectors.begin();
	double previousAlt = length(it->second.pos);
	++it;
	while(it!=stateVectors.end()) {
		double alt = length(it->second.pos);
		// state vectors closest to apogee are when altitude stops increasing and starts decreasing
		if(alt > previousAlt) {
			bIncreasingAlt = true;
		}
		else if(alt < previousAlt && bIncreasingAlt) {
			--it; // go back to previous set of state vectors
			ELEMENTS el;
			kostOrbitParam oparam;
			kostStateVector2Elements(mu, &(it->second), &el, &oparam);
			ApD = oparam.ApD;
			METAtApogee = oparam.ApT + it->first;
			if(METAtApogee < currentMET) METAtApogee +=oparam.T;
			if((METAtApogee-currentMET) > oparam.T) METAtApogee-= oparam.T;
			return;
		}
		previousAlt = alt;
		++it;
	}
	//ApD = 0.0;
	//METAtApogee = 0.0;
	//return;
	// could not find apogee; use earliest set of data to calculate elements
	it = stateVectors.begin();
	//MapConstIterator it = stateVectors.begin();
	ELEMENTS el;
	kostOrbitParam oparam;
	kostStateVector2Elements(mu, &(it->second), &el, &oparam);
	ApD = oparam.ApD;
	METAtApogee = oparam.ApT + it->first;
	if(METAtApogee < currentMET) METAtApogee +=oparam.T;
	if((METAtApogee-currentMET) > oparam.T) METAtApogee-= oparam.T;
}

void StateVectorPropagator::GetPerigeeData(double currentMET, double& PeD, double& METAtPerigee) const
{
	if(stateVectors.size() == 0) return; // no data

	bool bDecreasingAlt = false;
	MapConstIterator it=stateVectors.begin();
	double previousAlt = length(it->second.pos);
	++it;
	while(it!=stateVectors.end()) {
		double alt = length(it->second.pos);
		// state vectors closest to perigee are when altitude stops decreasing and starts increasing
		if(alt < previousAlt) {
			bDecreasingAlt = true;
		}
		else if(alt > previousAlt && bDecreasingAlt) {
			--it; // go back to previous set of state vectors
			ELEMENTS el;
			kostOrbitParam oparam;
			kostStateVector2Elements(mu, &(it->second), &el, &oparam);
			PeD = oparam.PeD;
			METAtPerigee = oparam.PeT + it->first;
			if(METAtPerigee < currentMET) METAtPerigee +=oparam.T;
			if((METAtPerigee-currentMET) > oparam.T) METAtPerigee-= oparam.T;
			return;
		}
		previousAlt = alt;
		++it;
	}
	//PeD = 0.0;
	//METAtPerigee = 0.0;
	//return;
	// could not find apogee; use earliest set of data to calculate elements
	it = stateVectors.begin();
	//MapConstIterator it = stateVectors.begin();
	ELEMENTS el;
	kostOrbitParam oparam;
	kostStateVector2Elements(mu, &(it->second), &el, &oparam);
	PeD = oparam.PeD;
	METAtPerigee = oparam.PeT + it->first;
	if(METAtPerigee < currentMET) METAtPerigee +=oparam.T;
	if((METAtPerigee-currentMET) > oparam.T) METAtPerigee-= oparam.T;
}

double StateVectorPropagator::GetMETAtAltitude(double currentMET, double altitude) const
{
	if(stateVectors.size() == 0) return 0.0; // no data

	double radius = altitude + planetRadius;

	MapConstIterator it=stateVectors.begin();
	double previousAlt = length(it->second.pos);
	++it;
	while(it != stateVectors.end()) {
		double alt = length(it->second.pos);
		if((alt<=radius && previousAlt>=radius) ||( alt>=radius && previousAlt<=radius)) {
			break;
		}
		previousAlt = alt;
		++it;
	}
	--it;
	ELEMENTS el;
	kostStateVector2Elements(mu, &(it->second), &el, NULL);
	double timetoradius = 0.0;
	if (GetTimeToRadius( radius, el, mu, timetoradius ) == false) return 0.0;
	return timetoradius + it->first;
}

void StateVectorPropagator::Propagate(unsigned int iterationCount, double simdt)
{
	for(unsigned int i=0;i<iterationCount;i++) {
		VECTOR3 initialGrav;
		CalculateAccelerationVector(initialGrav);
		propPos += (propVel + initialGrav*(0.5*simdt))*simdt;
		VECTOR3 finalGrav;
		CalculateAccelerationVector(finalGrav);
		propVel += (initialGrav+finalGrav)*0.5*simdt;
		propMET += simdt;
	}
	//propMET += iterationCount*simdt;
}

void StateVectorPropagator::CalculateAccelerationVector(VECTOR3& acc) const
{
	double lat = asin(propPos.y/length(propPos));
	double r = length(propPos);
	// acceleration magnitudes in r and theta directions
	double a_r = -GM/(r*r) + 1.5*(GM*planetRadius*planetRadius*J2/pow(r, 4))*(3*pow(sin(lat), 2) - 1);
	double a_theta = -3*(GM*planetRadius*planetRadius*J2/pow(r, 4))*sin(lat)*cos(lat);
	// unit vectors
	VECTOR3 r_hat = propPos/r;
	VECTOR3 phi = crossp(_V(0, 1, 0), r_hat);
	VECTOR3 theta_hat = crossp(r_hat, phi);
	theta_hat/=length(theta_hat);

	acc = r_hat*a_r + theta_hat*a_theta;
	if(perturbFunction) acc += perturbFunction->GetAcceleration(propMET, propPos, propVel);
}

OMSBurnPropagator::OMSBurnPropagator()
: burnInProgress(false), burnCompleted(false)
{
}

OMSBurnPropagator::~OMSBurnPropagator()
{
}

void OMSBurnPropagator::SetBurnData(double TIG, const VECTOR3 &equDeltaV, double acceleration)
{
	burnInProgress = false;
	burnCompleted = false;
	this->TIG = TIG;
	lastMET = TIG;
	deltaV = length(equDeltaV);
	VGO = deltaV;
	equBurnDirection = equDeltaV/VGO; // normalise DV vector
	acc = acceleration;
}

void OMSBurnPropagator::GetTIGStateVector(VECTOR3& pos, VECTOR3& vel) const
{
	pos = tigPos;
	vel = tigVel;
}

void OMSBurnPropagator::GetCutoffStateVector(VECTOR3& pos, VECTOR3& vel) const
{
	pos = cutoffPos;
	vel = cutoffVel;
}

VECTOR3 OMSBurnPropagator::GetAcceleration(double MET, const VECTOR3& equPos, const VECTOR3& equVel)
{
	//char cbuf[255];
	if(!burnInProgress && !burnCompleted && MET>=TIG) {
		burnInProgress = true;
		tigPos = equPos;
		tigVel = equPos;
	}
	else if(MET<=TIG && lastMET>=TIG) { // needed in case propagator propagates past burn, then gets new state vectors and returns to time before TIG
		burnInProgress = false;
		burnCompleted = false;
		VGO = deltaV;
		lastMET = MET;
	}

	if(burnInProgress) {
		VGO -= acc*(MET-lastMET);
		if(VGO <= 0.0) {
			burnCompleted = true;
			burnInProgress = false;
			cutoffPos = equPos;
			cutoffVel = equVel;
			//sprintf_s(cbuf, 255, "MET: %f burn completeted", MET);
			//oapiWriteLog(cbuf);
		}
		//sprintf_s(cbuf, 255, "MET: %f VGO: %f burn in progress", MET, VGO);
		//oapiWriteLog(cbuf);
		lastMET = MET;
		return equBurnDirection*acc;
	}

	return _V(0, 0, 0);
}

StateVectorPropagator2::StateVectorPropagator2()
{
	EARTH_MU = 1.40764487566e16; // ft^3/sec^2 GGRAV * 5.973698968e+24; 
	SQR_EMU = sqrt(EARTH_MU);
	EARTH_RADIUS_GRAV = 2.09256561680e7; //ft 6.37101e6;
}

void StateVectorPropagator2::SetParameters(bool nonspherical)
{
	if (nonspherical)
	{
		ZONAL[0] = 0.0; ZONAL[1] = 1082.6271e-6; ZONAL[2] = -2.5358868e-6; ZONAL[3] = -1.624618e-6;
		C[0] = 0.0; C[1] = 0.0; C[2] = 0.0; C[3] = 0.0; C[4] = 0.0; C[5] = 0.0; C[6] = 0.0; C[7] = 0.0; C[8] = 0.0;
		S[0] = 0.0; S[1] = 0.0; S[2] = 0.0; S[3] = 0.0; S[4] = 0.0; S[5] = 0.0; S[6] = 0.0; S[7] = 0.0; S[8] = 0.0;

		//TBD: These are not supported by Orbiter. Use them when that changes
		//C[0] = -2.7635957e-10; C[1] = 1.5711423e-6; C[2] = 2.1907694e-6; C[3] = 3.0466825e-7; C[4] = 9.7966803e-8; C[5] = -5.0552749e-7; C[6] = 7.8842515e-8; C[7] = 5.9073749e-8; C[8] = -4.1542493e-9;
		//S[0] = -5.2357454e-9; S[1] = -9.0231337e-7; S[2] = 2.7267074e-7; S[3] = -2.1259298e-8; S[4] = 1.9681077e-7; S[5] = -4.4125015e-7; S[6] = 1.4818958e-7; S[7] = -1.2140873e-8; S[8] = 6.3163541e-9;
	}
	else
	{
		ZONAL[0] = 0.0; ZONAL[1] = 0.0; ZONAL[2] = 0.0; ZONAL[3] = 0.0;
		C[0] = 0.0; C[1] = 0.0; C[2] = 0.0; C[3] = 0.0; C[4] = 0.0; C[5] = 0.0; C[6] = 0.0; C[7] = 0.0; C[8] = 0.0;
		S[0] = 0.0; S[1] = 0.0; S[2] = 0.0; S[3] = 0.0; S[4] = 0.0; S[5] = 0.0; S[6] = 0.0; S[7] = 0.0; S[8] = 0.0;
	}
}

void StateVectorPropagator2::ONORBIT_PREDICT(VECTOR3 R_PRED_INIT, VECTOR3 V_PRED_INIT, double T_PRED_INIT, double T_PRED_FINAL, int GMOP, int GMDP, bool DMP, bool VMP, int ATMP, double PRED_STEP, VECTOR3 &R_PRED_FINAL, VECTOR3 &V_PRED_FINAL)
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

void StateVectorPropagator2::RK_GILL(double *XN, double DT_STEP, double &T_CUR, int GMO, int GMD, bool DM, bool VM, int ATM, double T_IN)
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
		T_CUR = T_STOR + AA[0] * BB[J] * DT_STEP;
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
			XN[L] = XN[L] + AA[J] * (P - BB[J] * Q[L]);
			Q[L] = CC[J] * P + DD[J] * Q[L];
		}
	}
}

void StateVectorPropagator2::PINES_METHOD(double *XN, double T_CUR, int GMOP, int GMDP, bool DM, bool VM, int ATM, double T_IN, double *DERIV, double *X)
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
	P = ACCEL_ONORBIT(R_OUT, V_OUT, T_ACCEL, GMDP, GMOP, DM, VM, ATM, G_CENTRAL);
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

VECTOR3 StateVectorPropagator2::ACCEL_ONORBIT(VECTOR3 R, VECTOR3 V, double T, int GMD, int GMO, bool DM, bool VM, int ATM, VECTOR3 &G_CENTRAL)
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
	FIFTY = EARTH_FIXED_TO_M50_COORD(T);
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

void StateVectorPropagator2::SOLAR_EPHEM(double T, double &SDEC, double &CDEC1, double &COS_SOL_RA, double &SIN_SOL_RA)
{
	//double LOS;

	//LOS = LOS_ZERO + T * LOS_R - LOC * sin(T*OMEG_C + PHASE_C);
	//SDEC = LOSK3 * sin(LOS);
	//CDEC1 = sqrt(1.0 - SDEC * SDEC);
	//COS_SOL_RAD = cos(LOS) / CDEC1;
	//SIN_SOL_RA = LOSK1 * sin(LOS) / CDEC1;
}

MATRIX3 StateVectorPropagator2::EARTH_FIXED_TO_M50_COORD(double T)
{
	//This is fine as long as the terms for the non-spherical gravity as a function of longitude are not used (Orbiter doesn't simulate it) and as long as the true M50 coordinate system
	//isn't used, but oapiGetPlanetObliquityMatrix near the current time is used
	return _M(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

void StateVectorPropagator2::ACCEL_EARTH_GRAV(VECTOR3 UR, double R_INV, int GMO, int GMD, const MATRIX3 &FIFTY, VECTOR3 &G_VEC)
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
		F3 = -MAT_A[0][0] * ZONAL[N - 1];
		F4 = -MAT_A[0][1] * ZONAL[N - 1];
		//If the maximum order of tesserals wanted has not been attained, do for N1=1 to N (these take into account contributions of tesseral and sectorial harmonics):
		if (N <= GMO)
		{
			for (N1 = 1;N1 <= N;N1++)
			{
				F1 = F1 + (double)N1*MAT_A[N1 - 1][0] * (C[L - 1] * ZETA_REAL[N1 - 1] + S[L - 1] * ZETA_IMAG[N1 - 1]);
				F2 = F2 + (double)N1*MAT_A[N1 - 1][0] * (S[L - 1] * ZETA_REAL[N1 - 1] - C[L - 1] * ZETA_IMAG[N1 - 1]);
				DNM = C[L - 1] * ZETA_REAL[N1] + S[L - 1] * ZETA_IMAG[N1];
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

void StateVectorPropagator2::F_AND_G(VECTOR3 R_IN, VECTOR3 V_IN, double DELTAT, double SMA, double C1, double R_IN_INV, double D_IN, double D_FIN, double &F, double &G, double &FDOT, double &GDOT, double &S0, double &S1, double &S2, double &S3, VECTOR3 &R_FIN, double &R_FIN_INV, double &THETA)
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


bool GetTimeToRadius( double radius, const ELEMENTS& el, double mu, double& timetoradius )
{
	// if radius is not between perigee and apogee, return false
	if ((radius < (el.a * (1.0 - el.e))) || (radius > (el.a * (1.0 + el.e)))) return false;

	double n = sqrt(mu/pow(el.a, 3));
	double trueAnomaly = acos((el.a*(1-el.e*el.e)/radius - 1)/el.e);
	double eccentricAnomaly = acos((el.e+cos(trueAnomaly))/(1+el.e*cos(trueAnomaly)));
	double meanAnomaly = eccentricAnomaly - el.e*sin(eccentricAnomaly);
	double meanAnomaly2 = PI2 - meanAnomaly; // two possible mean anomaly values
	double currentMeanAnomaly = kostGetMeanAnomaly(mu, &el);
	double deltaM = meanAnomaly-currentMeanAnomaly;
	double deltaM2 = meanAnomaly2-currentMeanAnomaly;
	//if(deltaM < 0.0) deltaM += PI2;
	//if(deltaM2 < 0.0) deltaM2 += PI2;
	if(abs(deltaM2) < abs(deltaM)) deltaM = deltaM2;
	//deltaM = min(deltaM, deltaM2);
	timetoradius = deltaM/n;
	return true;
}
