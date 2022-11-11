/****************************************************************************
  This file is part of Space Shuttle Vessel

  OMS Burn Software definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  OMS Burn Software definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _OMSBURNSOFTWARE_H_
#define	_OMSBURNSOFTWARE_H_


#include "SimpleGPCSoftware.h"
#include <discsignals.h>
#include <PEG4Targeting.h>


namespace dps
{
	class OrbitDAP;
	class StateVectorSoftware;
	class OMSTVCCMD_SOP;
	class OMSTVCFDBK_SOP;

class OMSBurnSoftware : public SimpleGPCSoftware
{
	int OMS; //0=BOTH, 1=LEFT, 2=RIGHT, 3=RCS
	double tig; // TIG in seconds
	double TIG[4]; // day,hour,min,sec
	double IgnitionTime; //MET at ignition
	bool BurnInProg, BurnCompleted;
	double WT;
	VECTOR3 PEG7; // DV in fps (values entered on CRT display; LVLH at TIG frame)
	VECTOR3 DeltaV; // DV in m/s (LVLH at TIG frame)
	double C1, C2, HT, ThetaT; // PEG4 Targets
	VECTOR3 Trim; // 0=P, 1=LY, 2=RY
	int TVR_ROLL;
	double DeltaVTot;
	double BurnTime;
	VECTOR3 VGO; // fps, body vector frame (VGO values displayed on CRT display)
	VECTOR3 VGO_Global; // m/s, Orbitersim global frame
	double vgoTot;
	bool MnvrLoad, MnvrExecute, MnvrToBurnAtt;
	bool bShowTimer;
	VECTOR3 BurnAtt;
	unsigned int OMSGimbalActr[2];// index: 0 = L, 1 = R; value: 0 = OFF, 1 = PRI, 2 = SEC

	bool bCalculatingPEG4Burn;
	PEG4Targeting peg4Targeting;

	OBJHANDLE hEarth;
	//ORBITPARAM oparam;
	//ELEMENTS el;
	double ApD, ApT, PeD, PeT;
	double metAt400KFeet;
	double lastUpdateSimTime;
	double lastMET;
	StateVectorPropagator propagator;
	OMSBurnPropagator omsBurnPropagator;
	double tgtApD, tgtPeD;

	DiscOutPort omsEngineCommand[2];

	OrbitDAP* pOrbitDAP;
	StateVectorSoftware* pStateVector;
	OMSTVCCMD_SOP* pOMSTVCCMD_SOP;
	OMSTVCFDBK_SOP* pOMSTVCFDBK_SOP;
public:
	explicit OMSBurnSoftware(SimpleGPCSystem* _gpc);
	virtual ~OMSBurnSoftware();

	void Realize() override;

	void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput(int spec, int item, const char* Data, bool &IllegalEntry ) override;
	bool ExecPressed(int spec) override;
	bool OnPaint(int spec, vc::MDU* pMDU) const override;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;

	/**
	 * Sets maneuver data (TIG and DV).
	 * Used for other programs (i.e. Orbit Tgt) to set burn data.
	 * \param maneuverTIG TIG of burn (MET, in seconds)
	 * \param maneuverDV DeltaV of burn in ft/s
	 */
	void SetManeuverData(double maneuverTIG, const VECTOR3& maneuverDV);

	VECTOR3 GetAttitudeCommandErrors() const;

	unsigned int GetOMSGimbalActrSel( unsigned int eng ) const;
private:
	void StartBurn();
	void TerminateBurn();

	void StartCalculatingPEG4Targets();
	void LoadManeuver(bool calculateBurnAtt = true);
	void CalculateEIMinus5Att(VECTOR3& degAtt) const;
	void UpdateOrbitData();
	void UpdateBurnPropagator();
};

}

#endif// _OMSBURNSOFTWARE_H_
