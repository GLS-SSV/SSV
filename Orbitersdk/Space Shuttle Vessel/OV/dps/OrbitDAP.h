/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbit DAP definition


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
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
********************************************/
#ifndef ORBITDAP_H_A2BBDD5A_0C8C_41E5_B501_2EF4028378C5
#define ORBITDAP_H_A2BBDD5A_0C8C_41E5_B501_2EF4028378C5
#pragma once

#include "SimpleGPCSoftware.h"
#include <PIDControl.h>
#include <discsignals.h>


namespace dps
{
const unsigned int convert[69] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

struct AttManeuver
{
	typedef enum {MNVR, TRK, ROT} TYPE; // at the moment, ROT is not supported
	bool IsValid;
	MATRIX3 tgtMatrix; // target attitude (rotation matrix) in right-handed frame (LVLH or M50, as appropriate)
	TYPE Type; // at the moment, ROT is not supported
};

struct DAPConfig
{
	double PRI_ROT_RATE, PRI_ATT_DB, PRI_RATE_DB, PRI_ROT_PLS, PRI_COMP, PRI_TRAN_PLS;
	int PRI_P_OPTION, PRI_Y_OPTION; //0=ALL, 1=NOSE, 2=TAIL
	double ALT_RATE_DB, ALT_ON_TIME, ALT_DELAY;
	int ALT_JET_OPT, ALT_JETS;
	double VERN_ROT_RATE, VERN_ATT_DB, VERN_RATE_DB, VERN_ROT_PLS, VERN_COMP;
	int VERN_CNTL_ACC;

	DAPConfig& operator = (const DAPConfig& rhs) {
		// copy all values from other config into this one
		PRI_ROT_RATE=rhs.PRI_ROT_RATE;
		PRI_ATT_DB=rhs.PRI_ATT_DB;
		PRI_RATE_DB=rhs.PRI_RATE_DB;
		PRI_ROT_PLS=rhs.PRI_ROT_PLS;
		PRI_COMP=rhs.PRI_COMP;
		PRI_TRAN_PLS=rhs.PRI_TRAN_PLS;
		PRI_P_OPTION=rhs.PRI_P_OPTION;
		PRI_Y_OPTION=rhs.PRI_Y_OPTION;
		ALT_RATE_DB=rhs.ALT_RATE_DB;
		ALT_ON_TIME=rhs.ALT_ON_TIME;
		ALT_DELAY=rhs.ALT_DELAY;
		ALT_JET_OPT=rhs.ALT_JET_OPT;
		ALT_JETS=rhs.ALT_JETS;
		VERN_ROT_RATE=rhs.VERN_ROT_RATE;
		VERN_ATT_DB=rhs.VERN_ATT_DB;
		VERN_RATE_DB=rhs.VERN_RATE_DB;
		VERN_ROT_PLS=rhs.VERN_ROT_PLS;
		VERN_COMP=rhs.VERN_COMP;
		VERN_CNTL_ACC=rhs.VERN_CNTL_ACC;

		return *this;
	}
};

class RHC_SOP;
class THC_SOP;
class OMSTVCCMD_SOP;
class StateVectorSoftware;

/**
 * Controls shuttle's attitude during orbital flight.
 * Also performs OMS TVC.
 * All calculations are done using right-handed matrices in M50 frame.
 */
class OrbitDAP : public SimpleGPCSoftware
{
public:
	typedef enum {RCS, LEFT_OMS, RIGHT_OMS, BOTH_OMS} CONTROL_MODE;
	typedef enum {PRI, ALT, VERN} DAP_MODE;
	typedef enum {A, B} DAP_SELECT;
	typedef enum {AUTO, INRTL, LVLH, FREE} DAP_CONTROL_MODE;
	typedef enum {DISC_RATE, ROT_PULSE} ROT_MODE;
	typedef enum {NORM, TRANS_PULSE} TRANS_MODE;
private:
	class ContactSwitch
	{
			bool q;
			bool s;
		public:
			ContactSwitch(){ q = false; s = false; }
			~ContactSwitch(){};

			void Set( bool i ){ s = i & !q; q = i; }
			bool Get( void ){ return s; }
	};

	PIDControl OMSTVCControlP, OMSTVCControlY, OMSTVCControlR;
	VECTOR3 OMSTrim;
	VECTOR3 OMSAttBias;// attitude correction for OMS TVC c.g. pointing
	CONTROL_MODE ControlMode;

	DAP_MODE DAPMode;
	DAP_SELECT DAPSelect;
	DAP_CONTROL_MODE DAPControlMode;
	ROT_MODE RotMode[3];
	TRANS_MODE TransMode[3]; // 0=X, 1=Y, 2=Z

	bool ERRTOT;// attitude error output: true = "ERR TOT", false = "ERR DAP"

	int editDAP; // -1=None, 0=A, 1=B
	DAPConfig DAPConfiguration[3]; //0=A, 1=B, 2=Edit

	// values change depending on DAP mode selected
	// initialized in Realize() function
	double degRotPulse, TransPulse;
	double degRotRate, degAttDeadband, degRateDeadband;

	bool RotatingAxis[3];
	bool NullingRates[3];
	bool RotPulseInProg[3];
	bool TransPulseInProg[3];
	VECTOR3 TransPulseDV; //negative DV for pulses along negative axes

	VECTOR3 degReqdRates;
	VECTOR3 degNullRates; // rates (in body axis frame) required to null rotation
	MATRIX3 attErrorMatrix;
	enum {MNVR_OFF, MNVR_IN_PROGRESS, MNVR_COMPLETE} ManeuverStatus;
	// ActiveManeuver is whatever attitude is currently being held (in AUTO, INRTL or LVLH)
	// Cur/FutManeuver are maneuvers loaded using UNIV PTG; in AUTO mode, Active and Cur maneuvers are always (check this) the same
	AttManeuver ActiveManeuver, CurManeuver, FutManeuver;
	double FutMnvrStartTime; // MET when future loaded maneuver starts
	double mnvrCompletionMET; // MET when current maneuver will be complete
	double lastUpdateTime; // time when null rates and final inertial attitude was last estimated for TRK maneuver

	//VECTOR3 radCurrentOrbiterAtt;
	MATRIX3 curM50Matrix;
	VECTOR3 radAngularVelocity, degAngularVelocity; // in Orbiter body axis frame
	//VECTOR3 GlobalPos;
	double OrbiterMass;
	VECTOR3 PMI;
	VECTOR3 Torque;

	bool bFirstStep;
	double lastStepdt;

	// values used in UNIV PTG to store attitude maneuvers
	int START_TIME[4];
	VECTOR3 MNVR_OPTION;
	int TGT_ID, BODY_VECT;
	double P, Y, OM;
	double RA;
	double DEC;
	double LAT;
	double LON;
	double _ALT;

	VECTOR3 CUR_ATT, REQD_ATT, ATT_ERR; // attitudes in degrees in M50 frame

	//PCT
	bool PCTArmed;
	bool PCTActive;
	double PCTStartTime;

	DiscOutPort RotThrusterCommands[3];
	DiscOutPort TransThrusterCommands[3]; // 0=X, 1=Y, 2=Z

	ContactSwitch cdrspdbkthrot;
	ContactSwitch pltspdbkthrot;
	ContactSwitch cdrbodyflap;
	ContactSwitch sparepbi;

	bool RA_DEC_flash;
	bool LAT_LON_ALT_flash;
	bool P_Y_flash;

	StateVectorSoftware* pStateVector;
	RHC_SOP *pRHC_SOP;
	THC_SOP *pTHC_SOP;
	OMSTVCCMD_SOP* pOMSTVCCMD_SOP;
public:
	explicit OrbitDAP(SimpleGPCSystem* pGPC);
	virtual ~OrbitDAP();

	void InitOMSTVC( const VECTOR3& Trim, CONTROL_MODE Mode );
	void UseOMSTVC( CONTROL_MODE Mode );
	void UseRCS();

	DAP_CONTROL_MODE GetDAPMode() const;

	/**
	 * Starts maneuver to INRTL attitude.
	 * Maneuver will start as soon as AUTO is selected.
	 * Currently only needed for OMSBurnSoftware class (to manuver to burn att).
	 * \param degINRTLAtt Attitude (in degrees) in M50 frame in standard PRY order
	 */
	void ManeuverToINRTLAttitude(const VECTOR3& degINRTLAtt);

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;
	bool ItemInput(int spec, int item, const char* Data, bool &IllegalEntry ) override;

	bool OnPaint(int spec, vc::MDU* pMDU) const override;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;

	VECTOR3 GetAttitudeErrors( void ) const;
	bool GetTimeToAttitude( double& time ) const;
private:
	/**
	 * Updates variables with current attitude data.
	 * Data from Orbitersim is converted to appropriate right-handed frame.
	 */
	void GetAttitudeData();

	void PaintUNIVPTGDisplay(vc::MDU* pMDU) const;
	void PaintDAPCONFIGDisplay(vc::MDU* pMDU) const;

	void LoadCurLVLHManeuver(const MATRIX3& tgtMatrixLVLH);
	void LoadFutLVLHManeuver(const MATRIX3& tgtMatrixLVLH);
	void LoadCurINRTLManeuver(const MATRIX3& tgtMatrixM50);
	void LoadFutINRTLManeuver(const MATRIX3& tgtMatrixM50);
	void StartCurManeuver();
	void StartManeuver(const MATRIX3& tgtAtt, AttManeuver::TYPE type);

	/**
	 * Determines rates due to RHC input.
	 * Returns true if RHC is out of detent.
	 */
	bool GetRHCRequiredRates();
	/**
	 * Fires translation thrusters based on THC input
	 */
	void HandleTHCInput(double simdt);

	/**
	 * Calculates required rotation rates based on rotation around Euler axis.
	 * Does not compensate for rotation of reference frame.
	 */
	void CalcEulerAxisRates();
	/**
	 * Calculates rotation rates based on errors in each individual axis.
	 * Adjusts rates to compenstate for rotation of reference frame.
	 * \param degNullRatesLocal Rotation rate (in Orbiter body frame) required to maintain constant attitude.
	 */
	void CalcMultiAxisRates(const VECTOR3& degNullRatesLocal);

	void UpdateNullRates();

	void SetRates(const VECTOR3 &degRates, double simdt);

	void OMSTVC(const VECTOR3 &AttErr, double SimDT);

	void ArmPCT( void );
	void DisarmPCT( void );
	void StartPCT();
	void StopPCT();
	void PCTControl(double simt);

	/**
	 * Updates DAP parameters with values from currently selected DAP configuration
	 */
	void UpdateDAPParameters();

	/**
	* Sets DAP light commands in COMPOOL.
	*/
	void CommandDAPLights( void );
	/**
	 * Handles DAP PBI being pressed.
	 */
	void DAP_PBI_Press( void );

	double CalcManeuverCompletionTime(const MATRIX3& curM50Matrix, const MATRIX3& tgtLVLHMatrix, const MATRIX3& curLVLHMatrix, double degOrbitalRate) const;

	/*** Vector/Matrix manipulation functions ***/
	/**
	 * Returns rotation matrix to convert from LVLH to M50 frame
	 */
	MATRIX3 GetCurrentLVLHRefMatrix() const;
	/**
	 * Returns rotation matrix representing current attitude in LVLH frame
	 */
	MATRIX3 GetCurrentLVLHAttMatrix() const;
};

};

#endif
