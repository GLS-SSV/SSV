/****************************************************************************
  This file is part of Space Shuttle Vessel

  State Vector Software definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/26   indy91
2022/09/29   GLS
2022/12/13   GLS
********************************************/
#ifndef _STATEVECTORSOFTWARE_H_
#define _STATEVECTORSOFTWARE_H_

#include "SimpleGPCSoftware.h"
#include <StateVectorPropagator.h>

namespace dps
{

/**
 * GPC code for propagating state vectors.
 * Will eventually implemented SPEC 33 REL NAV display.
 */
class StateVectorSoftware : public SimpleGPCSoftware
{
	OBJHANDLE hEarth;
	double lastUpdateSimTime;
	StateVectorPropagator propagator, targetPropagator;
	VECTOR3 lastVelocity;

	VECTOR3 t0Pos;

	std::string targetVesselName;
	VESSEL* pTargetVessel;
public:
	explicit StateVectorSoftware(SimpleGPCSystem* _gpc);
	~StateVectorSoftware();

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput(int spec, int item, const char* Data, bool &IllegalEntry ) override;
	bool OnPaint(int spec, vc::MDU* pMDU) const override;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;

	/**
	 * Sets target vessel for tracking. This is the vessel that will be used for rendezvous burn targeting, etc.
	 * In real life, MCC will just upload state vectors for target. Ku/star tracker data will be used (REL NAV display) to refine shuttle's orbit data.
	 * In Orbiter, vessel name will be specified and we will track vessel.
	 * NOTE: code assumes target vessel is not deleted at any point
	 */
	void SetTargetVessel(char* vesselName);

	double GetMETAtAltitude(double altitude) const;
	void GetPropagatedStateVectors(double met, VECTOR3& pos, VECTOR3& vel) const;
	void GetCurrentStateVectorsM50(VECTOR3& pos, VECTOR3& vel) const;
	void GetApogeeData(double& ApD, double& ApT) const;
	void GetPerigeeData(double& PeD, double& PeT) const;
	VECTOR3 GetPositionAtT0() const;

	void GetTargetStateVectors(double met, VECTOR3& pos, VECTOR3& vel) const;

	StateVectorPropagator2 newpropagator;
private:
	bool UpdatePropagatorStateVectors();
	void UpdateTargetStateVectors( VESSEL* v );
};

}

#endif// _STATEVECTORSOFTWARE_H_
