/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/12/06   GLS
2022/11/12   indy91
2022/12/13   GLS
2022/12/23   GLS
********************************************/
#include "StateVectorSoftware.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>

namespace dps
{

void GetStateVectors(VESSEL* v, OBJHANDLE hEarth, VECTOR3& pos, VECTOR3& vel)
{
	MATRIX3 obliquityMat;
	oapiGetPlanetObliquityMatrix(hEarth, &obliquityMat);
	v->GetRelativePos(hEarth, pos);
	v->GetRelativeVel(hEarth, vel);
	pos=tmul(obliquityMat, pos);
	vel=tmul(obliquityMat, vel);
}

StateVectorSoftware::StateVectorSoftware(SimpleGPCSystem * _gpc)
: SimpleGPCSoftware(_gpc, "StateVectorSoftware"),
lastUpdateSimTime(-10000.0), propagator(0.2, 50, 7200.0), targetPropagator(0.2, 50, 7200.0), t0Pos{0.0, 0.0, 0.0}, pTargetVessel(NULL)
{
}

StateVectorSoftware::~StateVectorSoftware()
{
}

void StateVectorSoftware::Realize()
{
	hEarth = STS()->GetGravityRef();
	if(!targetVesselName.empty()) SetTargetVessel(const_cast<char*>(targetVesselName.c_str()));
	else
	{
		oapiWriteLogV( "(SSV_OV) [INFO] No rendezvous target vessel specified" );
	}

	double J2 = 0;
	if(STS()->NonsphericalGravityEnabled()) J2 = oapiGetPlanetJCoeff(hEarth, 0);
	propagator.SetParameters(STS()->GetMass(), oapiGetMass(hEarth), oapiGetSize(hEarth), J2);
	targetPropagator.SetParameters(1.0, oapiGetMass(hEarth), oapiGetSize(hEarth), J2); // we may not have valid target vessel pointer, so use placeholder mass

	UpdatePropagatorStateVectors();
	UpdateTargetStateVectors( pTargetVessel ? pTargetVessel : STS() );// if no target, use OV state vector

	newpropagator.SetParameters(STS()->NonsphericalGravityEnabled());
}

void StateVectorSoftware::OnPreStep(double simt, double simdt, double mjd)
{
	if (GetMajorMode() < 104) return;

	double timeBetweenUpdates = max(4.0, 4.0*oapiGetTimeAcceleration());
	if((simt-lastUpdateSimTime) > timeBetweenUpdates) {
		UpdatePropagatorStateVectors();
		propagator.UpdateVesselMass(STS()->GetMass());

		// if no target, use OV state vector
		UpdateTargetStateVectors( pTargetVessel ? pTargetVessel : STS() );
		targetPropagator.UpdateVesselMass( pTargetVessel ? pTargetVessel->GetMass() : STS()->GetMass() );

		lastUpdateSimTime = simt;
	}

	propagator.Step(STS()->GetMET(), simdt);
	if(pTargetVessel) targetPropagator.Step(STS()->GetMET(), simdt);
}

bool StateVectorSoftware::OnMajorModeChange(unsigned int newMajorMode)
{
	if(newMajorMode == 102) { // liftoff - get position at T0
		VECTOR3 vel;
		GetStateVectors(STS(), hEarth, t0Pos, vel);
	}
	if(newMajorMode >= 101 && newMajorMode <= 303) return true;
	return false;
}

bool StateVectorSoftware::OnParseLine(const char* keyword, const char* value)
{
	if(!_strnicmp(keyword, "TARGET_VESSEL", 13)) {
		targetVesselName = value;
		return true;
	}
	else if(!_strnicmp(keyword, "T0_POS", 6)) {
		sscanf_s(value, "%lf%lf%lf", &t0Pos.x, &t0Pos.y, &t0Pos.z);
		return true;
	}
	return false;
}

void StateVectorSoftware::OnSaveState(FILEHANDLE scn) const
{
	if(!targetVesselName.empty()) oapiWriteScenario_string(scn, "TARGET_VESSEL", const_cast<char*>(targetVesselName.c_str()));
	oapiWriteScenario_vec(scn, "T0_POS", t0Pos);
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

double StateVectorSoftware::GetMETAtAltitude(double altitude) const
{
	return propagator.GetMETAtAltitude(STS()->GetMET(), altitude);
}

void StateVectorSoftware::GetPropagatedStateVectors(double met, VECTOR3 & pos, VECTOR3 & vel) const
{
	propagator.GetStateVectors(met, pos, vel);
}

void StateVectorSoftware::GetCurrentStateVectorsM50(VECTOR3& pos, VECTOR3& vel) const
{
	GetStateVectors(STS(), hEarth, pos, vel);
	// GetStateVectors already converts to equatorial (LH M50) frame, so we just need to swap Z and Y axes
	pos = ConvertBetweenLHAndRHFrames(pos);
	vel = ConvertBetweenLHAndRHFrames(vel);
}
void StateVectorSoftware::GetApogeeData(double& ApD, double& ApT) const
{
	propagator.GetApogeeData(STS()->GetMET(), ApD, ApT);
}

void StateVectorSoftware::GetPerigeeData(double& PeD, double& PeT) const
{
	propagator.GetPerigeeData(STS()->GetMET(), PeD, PeT);
}

VECTOR3 StateVectorSoftware::GetPositionAtT0() const
{
	return t0Pos;
}

void StateVectorSoftware::GetTargetStateVectors(double met, VECTOR3 & pos, VECTOR3 & vel) const
{
	targetPropagator.GetStateVectors(met, pos, vel);
}

bool StateVectorSoftware::UpdatePropagatorStateVectors()
{
	VECTOR3 pos, vel;
	GetStateVectors(STS(), hEarth, pos, vel);
	//oapiWriteLogV( "Pos: %f %f %f Vel: %f %f %f", pos.x, pos.y, pos.z, vel.x, vel.y, vel.z );
	return propagator.UpdateStateVector(pos, vel, STS()->GetMET());
}

void StateVectorSoftware::UpdateTargetStateVectors( VESSEL* v )
{
	VECTOR3 pos, vel;
	GetStateVectors(v, hEarth, pos, vel);
	targetPropagator.UpdateStateVector(pos, vel, STS()->GetMET());
}

}
