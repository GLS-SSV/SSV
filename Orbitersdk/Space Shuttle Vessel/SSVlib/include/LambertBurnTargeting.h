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

class LambertBurnTargeting
{
public:
	enum RESULT {RUNNING, CONVERGED, ERR};

	LambertBurnTargeting();
	~LambertBurnTargeting();

	void SetTargetingData(const VECTOR3& _RS_T1TIG, const VECTOR3& _VS_T1TIG, const VECTOR3& _RS_T2TIG, double _T1_TIG, double _T2_TIG, double vesselMass, int _GMD, int _GMO);
	void Step();
	RESULT CurrentState() const;
	void GetData(VECTOR3& _VS_REQUIRED, VECTOR3& _R_OFFSET, double &_T_OFFSET, int &_S_ROTATE, double &_MissDistance, int &_ALARM) const;
private:
	/**
	 * Runs Lambert solver and updates propagator
	 */
	void LAMBERT(VECTOR3 R0, VECTOR3 R1, VECTOR3 UN, double DEL_T_TRAN, VECTOR3 &VS_REQUIRED);

	StateVectorPropagator2 propagator;
	double planetMass;
	// Lambert data
	int step;
	RESULT currentState;
	int propagatorStepsRemaining;
	VECTOR3 RS_T1TIG, VS_T1TIG, RS_T2TIG;
	double T1_TIG, T2_TIG;
	int GMD, GMO;

	//I-Loads
	int N_MAX, N_MIN;
	double DU, EP_TRANSFER, EPS_U, EARTH_MU, CONE, R_TOL;

	//Temporary variables

	//1 = Parabolic transfer, 2 = too close to 0° or 180°, 5 = Maximum number of iterations in LAMBERT, 6 = Maximum number of iterations in PREVR
	//7 = Maximum number of iterations in elevation angle search
	int ALARM;
	int N, S_ROTATE;
	double DEL_T_TRAN, T_OFFSET, VG_MAG, ALPHA, ORB_RATE, ACC, SBETA, CBETA, BBEF, BAFT;
	VECTOR3 R_OFFSET, VG, UN_REF, RS_REF, RS_IP0, UN, VS_REQUIRED, RS_TERMINAL, VS_TERMINAL, R_MISS;
};

#endif// _LAMBERTBURNTARGETING_H_
