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
2020/03/20   GLS
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
2022/11/11   indy91
2022/12/21   indy91
2022/12/23   GLS
2022/12/28   GLS
2023/02/08   indy91
2023/02/10   indy91
2023/05/27   GLS
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


#include "../SimpleGPCSoftware.h"
#include <discsignals.h>
#include <PEG4Targeting.h>


namespace dps
{
	class OrbitDAP;
	class StateVectorSoftware;
	class GNCUtilities;

class OMSBurnSoftware : public SimpleGPCSoftware
{
	int OMS; //0=BOTH, 1=LEFT, 2=RIGHT, 3=RCS
	double tig; // TIG in seconds (GMT)
	double TIG[4]; // day,hour,min,sec
	double IgnitionTime; //GMT at ignition
	bool BurnInProg, BurnCompleted;
	float WT_DISP; //Displayed mass in lbs
	VECTOR3 EXT_DV_LVLH; // DV in fps (values entered on CRT display; LVLH at TIG frame)
	VECTOR3 VGO_LVLH;	//DV in fps (calculated values for PEG4, LVLH at current time)
	double C1_DISP, C2_DISP, HTGT_DISP, THETA_DISP; // PEG4 Targets
	VECTOR3 Trim; // 0=P, 1=LY, 2=RY
	int TVR_ROLL;
	double TGO;
	VECTOR3 VGO_DISP; // fps, body vector frame (VGO values displayed on CRT display)
	VECTOR3 VGO; // ft/s, M50 frame
	double DV_TOT;
	bool MnvrLoad, MnvrToBurnAtt;
	bool EXEC_CMD; // V93X1050XA, burn execute command
	bool ST_CRT_TIMER; // V93X6553X, start CRT timer flag
	VECTOR3 BurnAtt;
	bool X_FLAG; // false = attitude singularity, blank pitch and yaw
	float REI_LS; // Range to landing site in nautical miles
	double CUR_HA, CUR_HP; //Current apogee/perigee heights in NM
	double TXX;  //Time to next apsis
	int TXX_FLAG; //Flag for next apsis. 0 = TFF, 1 = TTA, 2 = TTP, 3 = TTC
	double TGT_HA, TGT_HP; //Target orbit heights in NM
	int MNVR_TITLE_IND; //Title number on display
	bool PEG_MODE_4;	//V93X6976, Guidance mode discrete
	float PROP_DEP; //Propellant to be used during maneuver with sign indicating out-of

	bool bCalculatingPEG4Burn;
	PEG4Targeting peg4Targeting;

	bool bBurnMode; //true = MM that allows burn, false = other MMs

	bool AlternatePass;
	float M; //Internal mass in slugs

	double lastUpdateSimTime;

	//PEG state vector
	VECTOR3 RGD, VGD;
	double TGD;
	//Current propulsion system flag
	int PROP_FLAG;
	//Prime propulsion system flag
	int PROP_FLAG_OFS;
	//Previous value of PROP_FLAG_OFS
	int PROP_FLAG_OFS_P;
	//Prime propulsion system flag for guidance
	int PROP_FLAG_GUID;
	//Steering flag
	bool SSTEER;
	//Thrust direction in body coordinates
	VECTOR3 THRUST_BODY;
	//Cutoff commanded flag
	bool SCO;
	//Time of cutoff
	double T_CUTOFF;
	//Accumulated IMU velocity
	VECTOR3 VS;
	//Previous value of VS
	VECTOR3 VSP;

	//Present GMT
	double T_GMT;

	//I-loads

	//PEG-4 targets for OMS-1, OMS-2 and AOA/ATO
	float HTGT_OMS[3]; //Height in feet
	float THETA_OMS[3]; //Target in–plane downrange angle in radians
	float C1_OMS[3], C2_OMS[3]; //Target intercept and slope in fps and ND
	float DTIG_OMS[3]; //Time from ET separation to ignition in seconds

	DiscOutPort omsEngineCommand[2];

	OrbitDAP* pOrbitDAP;
	StateVectorSoftware* pStateVector;
	GNCUtilities* pGNCUtilities;

public:
	explicit OMSBurnSoftware(SimpleGPCSystem* _gpc);
	virtual ~OMSBurnSoftware();

	void Realize() override;

	void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput( int item, const char* Data );
	void OnPaint( vc::MDU* pMDU ) const;

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

private:
	void StartBurn();
	void TerminateBurn();

	//Display initialization tasks
	void OPS1_INIT(int mm);
	void OPS2_INIT();
	void OPS3_INIT(int mm);

	//Pre-maneuver display support task
	bool PRE_MAN_DISP_SUPT_TSK1(); //Through starting the PEG task
	void PRE_MAN_DISP_SUPT_TSK2(); //After PEG task
	//Current orbit task
	void CUR_ORBIT_TSK();
	//Orbit altitude task
	void OPS2_ORB_ALT_TSK(VECTOR3 R, VECTOR3 V, double &HA, double &HP, double &TT_X, int &TXX_FL);
	void OPS3_ORB_ALT_TSK(VECTOR3 R, VECTOR3 V, double &HA, double &HP);
	//Pre-entry coast task
	void PRE_ENT_COAST_TSK();
	//Range to landing site task
	void RNG_TO_LS_TSK(VECTOR3 R1, VECTOR3 V1, double T1, double H_PERIGEE, bool showTimer);
	//Velocity-to-go display task
	void VGO_DISP_TSK();

	//On orbit guidance sequence
	void ON_ORB_GUID_SEQ();
	//Guidance input task
	void GUID_INP_TSK();
	//Guidance task
	void GUID_TSK();
	//Commanded body attitude task
	void CMD_BDY_ATT_TSK();
	//OMS Task
	void OMS_TSK();
};

}

#endif// _OMSBURNSOFTWARE_H_
