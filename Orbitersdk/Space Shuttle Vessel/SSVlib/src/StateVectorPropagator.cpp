/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/06/16   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
2022/08/26   indy91
2022/09/29   GLS
2022/09/30   GLS
2022/11/11   indy91
2022/11/12   indy91
2022/12/18   indy91
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
