/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbit Targeting definition


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
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
********************************************/
#ifndef ORBITTGTSOFTWARE_H_E031D277_4DA3_4827_9F8D_D2BB8BE2F2D8
#define ORBITTGTSOFTWARE_H_E031D277_4DA3_4827_9F8D_D2BB8BE2F2D8
#pragma once

#include "SimpleGPCSoftware.h"
#include "LambertBurnTargeting.h"

namespace dps
{
	class OMSBurnSoftware;
	class StateVectorSoftware;
/**
 * Struct for I-Load maneuvers.
 * Not used yet (I-loading maneuver data is not implemented)
 */
struct BurnTargetingData
{
	VECTOR3 finalOffset;
	double elevation;
	double T1_TIG; // relative to base time
	double transferTime; // time between T1 and T2

	BurnTargetingData& operator = (const BurnTargetingData& rhs) {
		// copy all values from other config into this one
		finalOffset = rhs.finalOffset;
		elevation = rhs.elevation;
		T1_TIG = rhs.T1_TIG;
		transferTime = rhs.transferTime;
		return *this;
	}
};

/**
 * GPC software for targeting rendezvous burns (solving Lambert/Gauss problem).
 * Implements SPEC 34 ORBIT TGT display.
 */
class OrbitTgtSoftware : public SimpleGPCSoftware
{
	// values displayed on SPEC 34 display
	double TIG_T1[4], TIG_T2[4], BASE_TIME[4]; // day,hour,min,sec
	double transferTime;
	VECTOR3 relPos_T1, relVel_T1;
	VECTOR3 relPos_T2;
	double elevation;
	//double dT_T2;
	VECTOR3 DeltaV;
	VECTOR3 t1Vel, t1Pos;

	bool bCalculatingT1Burn;
	LambertBurnTargeting burnTargeting;

	bool bMNVRDataCalculated;
	bool bValuesChanged; // indicates that values have been changed from I-Loaded defaults
	// data used for burn targeting
	BurnTargetingData targetData;

	OMSBurnSoftware* pOMSBurnSoftware;
	StateVectorSoftware* pStateVectorSoftware;
public:
	explicit OrbitTgtSoftware(SimpleGPCSystem* _gpc);
	virtual ~OrbitTgtSoftware();

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput( int item, const char* Data );
	void OnPaint( vc::MDU* pMDU) const;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;
private:
	void StartCalculatingT1Burn();
	void GetT1BurnData(const VECTOR3& targetEquVelocity);
};

};

#endif // ORBITTGTSOFTWARE_H_E031D277_4DA3_4827_9F8D_D2BB8BE2F2D8