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
2022/09/29   GLS
2022/12/21   indy91
2023/02/10   indy91
********************************************/
#ifndef _PEG4TARGETING_H_
#define _PEG4TARGETING_H_


#include <OrbiterAPI.h>

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
	bool PEG_TSK();

	void SetPlanetParameters(double mu);
	/**
	 * Sets PEG4 targets.
	 * \param C1 [ft/s]
	 * \param C2 [N/A]
	 * \param RGD position of shuttle at TIG (inertial, M50 frame) [ft]
     * \param VGD velocity of shuttle at TIG (inertial, M50 frame) [ft/s]
	 * \param TGD time associated with RGD and VGD [s]
	 * \param RT target position vector (inertial, M50 frame) [ft]
	 * \param FT vacuum thrust of maneuver engine(s) [lbf]
	 * \param VEX total effectivre exhaust velocity [ft/s]
	 * \param M estimated vehicle mass [slugs]
	 * \param MBO desired final mass [slugs]
	 * \param SFUELD fuel wasting flag. 0 = not desired, 1 = desired in direction of angular momentum vector, -1 = opposite direction [N/A]
	 * \param NMAX maximum number of iterations [N/A]

	 */
	void SetPEG4Targets(double C1, double C2, const VECTOR3& _RGD, const VECTOR3& _VGD, double _TGD, const VECTOR3 &_RT, double _FT, double _VEX, float _M, float _MBO, int _SFUELD, int _NMAX);

	/**
	 * Returns required DeltaV in inertial M50 frame [ft/s]
	 */
	VECTOR3 GetDeltaV() const;

	/**
	* Returns position and velocity vectors for prediction of burnout state [ft and ft/s]
	*/
	void GetStateVectors(VECTOR3 &_RP, VECTOR3 &_VD, VECTOR3 &_RC1, VECTOR3 &_VC1, VECTOR3 &_RC2, VECTOR3 &_VC2) const;

	/**
	 * Returns true if complete, false if running or error
	 */
	bool Converged() const;
private:
	void PREDICTOR(VECTOR3 R_INIT, VECTOR3 V_INIT, double T_INIT, double T_FINAL, double DT_MAX, VECTOR3 &R_FINAL, VECTOR3 &V_FINAL) const;
	void CENTRAL(VECTOR3 R, VECTOR3 &ACCEL, double &R_INV) const;

	bool VelocityToBeGainedSubtask();
	void VelocityToBeGainedFuelDepletionSubtask();
	void TimeToGoSubtask();
	void ThrustIntegralSubtask();
	void ReferenceThrustVectorsSubtask();
	void BurnoutStateVectorPredictionSubtask();
	void ConvergenceCheckSubtask();

	int propagatorStepsRemaining;
	double EARTH_MU;

	STATE currentState;

	double C1, C2;
	double VEX;
	float M; //Initial mass in slugs
	double FT; //Thrust in lbf
	float MBO; //Desired burnout mass in slugs
	int SFUELD; //Fuel wasting flag

	VECTOR3 RGD, VGD;
	double TGD;

	VECTOR3 RP, VP;
	double TP;

	VECTOR3 RC1, VC1, RC2, VC2; //Position and velocity vectors at start and end of PEG gravity computation

	VECTOR3 RT;
	VECTOR3 IY; // unit vector normal to orbit plane
	double TGO;
	double ATR; //Acceleration at ignition, ft/s/s
	VECTOR3 VGO; //Velocity to go ft/s
	VECTOR3 VD; //Desired burnout velocity vector
	double LAMDXZ; //Turning rate
	double THETA_DOT; //Orb rate
	VECTOR3 VMISS; //Velocity miss
	double VGOMAG;
	bool SCONV;
	double VRATIO;

	double JOL, QPRIME, S; //Thrust integrals
	VECTOR3 LAMD, LAM;

	int NMAX;
	int iterationCounter;

	const double KMISS = 0.01;
	const double EP_TRANSFER = 8.0*RAD;
};

#endif// _PEG4TARGETING_H_
