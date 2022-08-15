/****************************************************************************
  This file is part of Space Shuttle Vessel

  PEG4 Targeting definition


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
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
********************************************/
#ifndef PEG4TARGETING_H_1438E6C9_2A9B_4824_94AB_A9574F5F27A6
#define PEG4TARGETING_H_1438E6C9_2A9B_4824_94AB_A9574F5F27A6
#pragma once
#include <OrbiterAPI.h>
#include "StateVectorPropagator.h"

/**
 * Calculates PEG7 targets and transfer time from initial to target position
 * Assumes instantaneous burn (and no perturbations)
 * \param transferAngle angle between initial and target position (may exceed pi) [rad]
 * \param initialPos position at TIG (equatorial, inertial frame) [m]
 * \param initialVel velocity at TIG (equatorial, inertial frame) [m/s]
 * \param targetPos target position (equatorial, inertial frame) [m]
 * \param mu standard gravitational parameter G*(M1+M2)
 * \param transferTime reference to variable which will be populated with transfer time (in seconds)
 * \returns required Delta V [m/s]
 */
VECTOR3 CalculatePEG7Targets(double C1, double C2, double transferAngle, const VECTOR3& initialPos, const VECTOR3& initialVel, const VECTOR3& targetPos, double mu, double& transferTime);

/**
 * Iteratively calculates DeltaV (in m/s) for PEG4 values
 * Algorithm:
 * 	1. Compute DeltaV assuming instantaneous burn, no perturbations
 *	2. Propagate state to burn cutoff point
 *	3. First iteration: go to step
 *	4. Propagate state to target point (include J2 perturbations)
 *	5. Compute offset between actual and target position (ignore OOP error); add offset to target point
 *	6. Recalculate target velocity at burn cutoff point
 *	7. Iterate steps 2-6
 * This always works for shuttle, but might not converge for vessels with low acceleration (i.e. < 0.2 m/s^2)
 */
class PEG4Targeting
{
public:
	enum STATE {BURN_PROP, COAST_PROP, COMPLETE, ERR};

	PEG4Targeting();
	~PEG4Targeting();

	/**
	 * \returns true if complete (converged or error)
	 */
	bool Step();

	void SetPlanetParameters(double _planetMass, double _planetRadius, double J2Coeff);
	/**
	 * Sets PEG4 targets.
	 * For OPS 1, transfer angle needs to be calculated from ThetaT and position at TIG.
	 * For OPS 3, transfer angle is equal to ThetaT.
	 * \param C1 [m/s]
	 * \param C2 no units
	 * \param HT altitude [m]
	 * \param transferAngle angle between initial and target positions [radians]
	 * \param _initialPos position of shuttle at TIG (inertial, equatorial frame) [m]
	 * \param _initialVel velocity of shuttle at TIG (inertial, equatorial frame) [m/s]
	 */
	void SetPEG4Targets(double C1, double C2, double HT, double transferAngle, const VECTOR3& _initialPos, const VECTOR3& _initialVel, double vesselAcceleration);

	/**
	 * Returns required DeltaV in inertial equatorial frame [m/s]
	 */
	VECTOR3 GetDeltaV() const;
	/**
	 * Returns predicted time from initial to target position
	 * Assumes instantaneous burn
	 */
	double GetTransferTime() const;
	/**
	 * Returns true if complete, false if running or error
	 */
	bool Converged() const;
private:
	void PerformTargetingIteration();

	int propagatorStepsRemaining;
	StateVectorPropagator propagator;
	double planetMass, planetRadius;
	double J2;
	double mu;
	OMSBurnPropagator omsPropagator;
	double acceleration;

	STATE currentState;
	double C1, C2;
	double transferAngle;
	VECTOR3 initialPos, initialVel;
	VECTOR3 cutoffPos, cutoffVel;
	VECTOR3 targetPos;
	VECTOR3 orbitPlane; // unit vector normal to orbit plane
	//double transferTime;
	double coastTime, burnTime;
	VECTOR3 totalMissOffset;

	int iterationCount;

	VECTOR3 equDeltaV;
};

#endif //PEG4TARGETING_H_1438E6C9_2A9B_4824_94AB_A9574F5F27A6
