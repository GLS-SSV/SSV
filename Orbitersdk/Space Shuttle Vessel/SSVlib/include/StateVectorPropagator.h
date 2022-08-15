/****************************************************************************
  This file is part of Space Shuttle Vessel

  State Vector Propagator definition


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
2020/04/01   GLS
2020/08/24   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
#ifndef STATEVECTORPROPAGATOR_128F62F4_83F4_4BDD_967B_7E2CD4016D3F
#define STATEVECTORPROPAGATOR_128F62F4_83F4_4BDD_967B_7E2CD4016D3F
#pragma once

#include <OrbiterAPI.h>
#include "..\KOST\kost.h"
#include <map>

class PropagatorPerturbation
{
public:
	virtual VECTOR3 GetAcceleration(double MET, const VECTOR3& equPos, const VECTOR3& equVel) = 0;
};

class StateVectorPropagator
{
	typedef std::map<double, kostStateVector> StateVectorMap;
	typedef StateVectorMap::iterator MapIterator;
	typedef StateVectorMap::const_iterator MapConstIterator;

	//std::map<double, kostStateVector> stateVectors;
	StateVectorMap stateVectors;

	double stepLength;
	int iterationsPerStep;
	double maxPropagationTime; // total time since last state vector update we will propagate vector
	//double currentTimestamp;
	double lastSaveMET;
	double lastStateVectorUpdateMET;
	//double maxTimestamp;
	double maxPropMET;

	VECTOR3 propPos, propVel;
	double propMET;

	double mu, GM, planetRadius, J2;
	PropagatorPerturbation* perturbFunction;
	//double vesselMass;
public:
	//StateVectorPropagator(const VECTOR3& pos, const VECTOR3& vel, OBJHANDLE hPlanet, double _vesselMass, double currentMET);
	StateVectorPropagator(double propagationStepLength, int _iterationsPerStep, double _maxPropagationTime);
	~StateVectorPropagator();

	void SetParameters(double vesselMass, double planetMass, double _planetRadius, double J2Coeff);
	/**
	 * Sets functor used to calculate perturbations (drag, thrust, etc.)
	 * Caller is responsible for ensuring object is not deleted while propagator is in use
	 * \param pertubations pointer to functor which will return perturbation acceleration for each timestep - NULL if no perturbations
	 */
	void DefinePerturbations(PropagatorPerturbation* pertubations);
	void UpdateVesselMass(double vesselMass);
	/**
	 * Updates state vector if last set of state vectors has been propagated to limit or difference between new and existing state vectors exceeds limit
	 * \param forceUpdate Forces state vectors to be updated.
	 * Returns true if error between new and existing vectors exceeded limit; false otherwise (if forceUpdate is true, function always returns false)
	 */
	bool UpdateStateVector(const VECTOR3& equPos, const VECTOR3& equVel, double met, bool forceUpdate=false);

	//void SetVesselMass(double newMass);

	//void GetState(VECTOR3& pos, VECTOR3& vel) const;
	void Step(double currentMET, double simdt);

	double GetElements(double MET, ELEMENTS& el, kostOrbitParam* oparam=NULL) const;
	void GetStateVectors(double MET, VECTOR3& pos, VECTOR3& vel) const;

	//double GetLastUpdateTime() const;

	//void GetApogeeData(double& ApD, double& METAtApogee) const;
	//void GetPerigeeData(double& PeD, double& METAtPerigee) const;
	void GetApogeeData(double currentMET, double& ApD, double& METAtApogee) const;
	void GetPerigeeData(double currentMET, double& PeD, double& METAtPerigee) const;
	/**
	 * Returns MET at which the vessel will reach a given altitude, or 0 if it never crosses it.
	 * \altitude altitude (relative to Earth's surface) in meters
	 */
	double GetMETAtAltitude(double currentMET, double altitude) const;
private:
	void Propagate(unsigned int iterationCount, double simdt);
	void CalculateAccelerationVector(VECTOR3& acc) const;
};

/**
 * Used with StateVectorPropagator to correct for OMS burn
 * Currently assumes constant acceleration (not quite correct, but should be good approximation)
 */
class OMSBurnPropagator : public PropagatorPerturbation
{
	VECTOR3 equBurnDirection;
	double deltaV;
	double TIG;
	double acc;
	bool burnInProgress, burnCompleted;
	double VGO; // used to track DeltaV applied so far
	double lastMET; // used for calculating interval between calls

	VECTOR3 cutoffPos, cutoffVel;
	VECTOR3 tigPos, tigVel;
public:
	OMSBurnPropagator();
	~OMSBurnPropagator();

	void SetBurnData(double TIG, const VECTOR3 &equDeltaV, double acceleration);
	void GetTIGStateVector(VECTOR3& pos, VECTOR3& vel) const;
	void GetCutoffStateVector(VECTOR3& pos, VECTOR3& vel) const;

	VECTOR3 GetAcceleration(double MET, const VECTOR3& equPos, const VECTOR3& equVel) override;
};

/**
 * Returns time (from epoch of elements passed) when spacecraft will next pass through given altitude.
 * @param radius	distance (from centre of Earth) in meters
 * @param el
 * @param mu
 * @param timetoradius	time to radius
 * @return		true if radius distance is between apogee and perigee of elements, false otherwise
 */
bool GetTimeToRadius( double radius, const ELEMENTS& el, double mu, double& timetoradius );

#endif //STATEVECTORPROPAGATOR_128F62F4_83F4_4BDD_967B_7E2CD4016D3F
