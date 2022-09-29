/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/06/16   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "LambertBurnTargeting.h"
#include <MathSSV.h>
#include <EngConst.h>

/**
 * Stumpff functions.
 * These are infinite series; the functions below only work for elliptical orbits (z > 0)
 */
double C_function(double z)
{
	if(z < 0.1) return 0.5 - z/24 + (z*z)/720;
	return (1-cos(sqrt(z)))/z;
}
double S_function(double z)
{
	if(z < 0.1) return 1.0/6.0 - z/120 + (z*z)/5040;
	return (sqrt(z)-sin(sqrt(z)))/pow(z, 1.5);
}

bool SolveLambertProblem(const VECTOR3& initialPos, const VECTOR3& finalPos, double transferTime, double orbitPeriod, double mu, VECTOR3& initialVelocity, VECTOR3& finalVelocity)
{
	// NOTE: algorithm defined in section 5.3 of Fundamentals of Astrodynamics (Bate, Mueller, White) is used in this function
	double dotProduct = dotp(initialPos, finalPos);
	double deltaTrueAnomaly = acos(dotProduct/(length(initialPos)*length(finalPos)));
	// TODO: handle case where transfer angle is ~180 degrees, and transfer orbit plane is undefined
	if(transferTime > orbitPeriod*0.5) deltaTrueAnomaly = PI2 - deltaTrueAnomaly;
	const double r1 = length(initialPos);
	const double r2 = length(finalPos);
	const double A = (sqrt(r1*r2)*sin(deltaTrueAnomaly))/(sqrt(1-cos(deltaTrueAnomaly)));

	// to get initial value of z, assume it is directly proportional to transfer time
	//double z = PI2*(transferTime/orbitPeriod);
	//double z = 0;
	double z_max = pow(PI2, 2);
	double z_min = 0;

	double y, tc;
	int iterations = 0;
	do {
		double z = (z_max+z_min)/2;
		double C = C_function(z);
		double S = S_function(z);
		y = r1 + r2 - A*(1-z*S)/sqrt(C);
		double x = sqrt(y/C);
		tc = (x*x*x*S + A*sqrt(y))/sqrt(mu);
		//z = (1-sqrt(C)*(r1+r2-y)/A)/S;
		if(tc > transferTime) z_max = z;
		else z_min = z;
		iterations++;
	} while(!Eq(tc, transferTime, 0.001) && iterations < 50);

	double f = 1 - y/r1;
	double g = A*sqrt(y/mu);
	double g_dot = 1 - y/r2;

	initialVelocity = (finalPos - initialPos*f)/g;
	finalVelocity = (finalPos*g_dot - initialPos)/g;
	return (iterations < 50);
}

static const double PROPAGATOR_STEP_LENGTH = 0.2;
static const int PROPAGATOR_STEP_COUNT = 400;
static const double MAX_RANGE_ERROR = 250.0/MPS2FPS;
static const int MAX_ITERATIONS = 10;

LambertBurnTargeting::LambertBurnTargeting()
	: propagator(PROPAGATOR_STEP_LENGTH, PROPAGATOR_STEP_COUNT, 7200), currentState(CONVERGED)
{
}

LambertBurnTargeting::~LambertBurnTargeting()
{
}

void LambertBurnTargeting::SetPlanetParameters(double _planetMass, double _planetRadius, double J2Coeff)
{
	planetMass = _planetMass;
	propagator.SetParameters(1.0, _planetMass, _planetRadius, J2Coeff);
}

void LambertBurnTargeting::SetTargetingData(const VECTOR3& _initialPos, const VECTOR3& _finalPos, double _transferTime, double orbitPeriod, double vesselMass)
{
	initialPos = _initialPos;
	finalPos = _finalPos;
	transferTime = _transferTime;
	period = orbitPeriod;
	mu = GGRAV*(planetMass + vesselMass);
	propagator.UpdateVesselMass(vesselMass);
	iterationCount = 0;
	totalMissOffset = _V(0, 0, 0);

	PerformTargetingIteration();
}

void LambertBurnTargeting::Step()
{
	if(currentState == RUNNING) {
		if(propagatorStepsRemaining > 0) {
			propagator.Step(0.0, 0.01);
			propagatorStepsRemaining--;
		}
		else {
			VECTOR3 propPos, propVel;
			propagator.GetStateVectors(transferTime, propPos, propVel);
			VECTOR3 missOffset = finalPos - propPos;
			totalMissOffset += missOffset;
			if(length(missOffset) < MAX_RANGE_ERROR) currentState = CONVERGED;
			else {
				PerformTargetingIteration();
				iterationCount++;
				if(iterationCount > MAX_ITERATIONS) currentState = ERR;
			}
		}
	}
}

LambertBurnTargeting::RESULT LambertBurnTargeting::CurrentState() const
{
	return currentState;
}

void LambertBurnTargeting::GetData(VECTOR3& _initialVelocity, VECTOR3& _finalVelocity) const
{
	_initialVelocity = initialVelocity;
	_finalVelocity = finalVelocity;
}

void LambertBurnTargeting::PerformTargetingIteration()
{
	SolveLambertProblem(initialPos, finalPos+totalMissOffset, transferTime, period, mu, initialVelocity, finalVelocity);
	propagator.UpdateStateVector(initialPos, initialVelocity, 0.0, true);
	propagatorStepsRemaining = static_cast<int>(transferTime/(PROPAGATOR_STEP_LENGTH*PROPAGATOR_STEP_COUNT))+1; // number of steps required before propagator reaches transfer time
	currentState = RUNNING;
}
