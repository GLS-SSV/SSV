/****************************************************************************
  This file is part of Space Shuttle Vessel

  Lambert Burn Targeting definition


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
2022/09/29   GLS
********************************************/
#ifndef _LAMBERTBURNTARGETING_H_
#define _LAMBERTBURNTARGETING_H_


#include <OrbiterAPI.h>
#include "StateVectorPropagator.h"

/**
 * Solves Lambert (or Gauss) problem iteratively.
 * Does not handle case where transfer angle is ~180 degrees (transfer orbit plane is undefined)
 * \param initialPos Initial position of shuttle (input)
 * \param finalPos Final position of shuttle (input)
 * \param transferTime Time for shuttle to travel from inital to final position (input)
 * \param orbitPeriod Period of current orbit (used to determine if transfer angle is greater or less than 180 degrees; does not need to be exact). (input)
 * \param mu G*(M+m) (input)
 * \param initialVelocity Initial velocity of shuttle on transfer orbit (i.e. after burn) (output)
 * \param finalVelcity Velocity of shuttle at final position (output)
 * \returns true if converged, false if solution could not be found.
 */
bool SolveLambertProblem(const VECTOR3& initialPos, const VECTOR3& finalPos, double transferTime, double orbitPeriod, double mu, VECTOR3& initialVelocity, VECTOR3& finalVelocity);

class LambertBurnTargeting
{
public:
	enum RESULT {RUNNING, CONVERGED, ERR};

	LambertBurnTargeting();
	~LambertBurnTargeting();

	void SetPlanetParameters(double _planetMass, double _planetRadius, double J2Coeff);

	void SetTargetingData(const VECTOR3& _initialPos, const VECTOR3& _finalPos, double _transferTime, double orbitPeriod, double vesselMass);
	void Step();
	RESULT CurrentState() const;
	void GetData(VECTOR3& _initialVelocity, VECTOR3& _finalVelocity) const;
private:
	/**
	 * Runs Lambert solver and updates propagator
	 */
	void PerformTargetingIteration();

	StateVectorPropagator propagator;
	double planetMass;
	// Lambert data
	int iterationCount;
	RESULT currentState;
	int propagatorStepsRemaining;
	VECTOR3 initialPos, finalPos;
	VECTOR3 initialVelocity, finalVelocity;
	VECTOR3 totalMissOffset;
	double transferTime, period, mu;
};

#endif// _LAMBERTBURNTARGETING_H_
