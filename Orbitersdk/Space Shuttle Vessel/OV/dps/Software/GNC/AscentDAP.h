/****************************************************************************
  This file is part of Space Shuttle Vessel

  Ascent DAP definition


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
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/28   GLS
2021/07/03   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/05/01   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/11/15   GLS
2022/12/23   GLS
2023/06/14   GLS
2025/12/27   indy91
2026/01/06   indy91
2026/01/24   indy91
********************************************/
#ifndef _dps_ASCENTDAP_H_
#define _dps_ASCENTDAP_H_


#include "../SimpleGPCSoftware.h"
#include <discsignals.h>
#include <PIDControl.h>


namespace dps
{
class SSME_SOP;
class SSME_Operations;
class MPS_ATVC_CMD_SOP;
class SRBSepSequence;
class RHC_SOP;
class GNCUtilities;
class StateVectorSoftware;

class AscentGuidance
{
public:
	AscentGuidance();

	void Init(double T_GMTLO, double r_D, double v_D, double gamma_D, VECTOR3 IY_M50);

	void Cycle(VECTOR3 R, VECTOR3 V, double T, int K_CMD, int N_SSME, int N_OMS, double mass, VECTOR3 DV, VECTOR3& U_STEER);

	// Convert inclination to IY vector
	VECTOR3 CalculateEFIYVector(double Incl, double Lat, double Lng, bool north, double dt_bias) const;
	// Get time remaining
	double GetTimeRemaining() const;
	// Get IY vector
	VECTOR3 GetIYVector() const;
	// Get desired insertion velocity
	double GetVDMAG() const;
private:

	void AscentGuidanceTask();
	void PEGTask();
	void PositionMagnitudeSubTask();
	void VGOUpdateSubtask();
	void ModeIndependentInit();
	void StandardAscentModeInit();
	void DesiredOrbitPlaneCorrectionSubtask();
	void DesiredPositionAscentRTLSSubtask();
	void DesiredVelocitySubtask();
	void VGOCorrectionSubtask();
	void ConvergenceCheckSubtask();
	void TGOSubtask();
	void ThrustIntegralsSubtask();
	void ReferenceThrustVectorSubtask();
	void RangeToGoSubtask();
	void TurningRateVectorSubtask();
	void SteeringInputsUpdateSubtask();
	void BurnoutStateVectorPredictionSubtask();
	void ThrustTimeIntegralsLogic(int I);
	void CutoffPositionConstraintReleaseSubtask();

	// TBD: Move this to navigation code
	void CENTRAL(VECTOR3 R, VECTOR3& ACCEL, double& R_INV) const;
	void ASC_PREC_PRED(VECTOR3 R_INIT, VECTOR3 V_INIT, double T_INIT, double T_FINAL, int GMD_PRED, int GMO_PRED, double DT_MAX, VECTOR3& R_FINAL, VECTOR3& V_FINAL) const;

	// INPUTS
	// Desired MECO radius magnitude [FT]
	double RDMAG;
	// Desired MECO velocity magnitude [FT/SEC]
	double VDMAG;
	// Desired MECO flight path angle [RAD]
	double GAMD;
	// Target orbital plane (negative of relative angular momentum vector) [ND]
	VECTOR3 IYD;
	// Time at which guidance assumes an SSME failure [SEC]
	double TFAIL;

	// Launch GMT. TBD: AVAILABLE FROM COMPOOL, TEMPORARY
	double T_GMTLO;

	// INTERNAL
	// VGO correction [FT/SEC]
	VECTOR3 DVGO;
	// Change in accumulated sensed velocity from previous value [FT/SEC]
	VECTOR3 DVS;
	// Guidance coordinate system X–axis in M50 coordinates [ND]
	VECTOR3 IX;
	// Unit vector normal to desired plane [ND]
	VECTOR3 IY;
	// Unit vector in direction of velocity–to–go [ND]
	VECTOR3 LAM;
	// M50 desired thrust vector [ND]
	VECTOR3 LAMC;
	// Turning rate vector [1/SEC]
	VECTOR3 LAMD;
	// Thrust turning rate vector [1/SEC]
	VECTOR3 OMEGA;
	// Difference between RGOG and RTHRUST [FT]
	VECTOR3 RBIAS;
	// Desired thrust cutoff position vector [FT]
	VECTOR3 RD;
	// Guidance position vector [FT]
	VECTOR3 RGD;
	// Desired position change due to thrust [FT]
	VECTOR3 RGO;
	// Position contributation of gravity [FT]
	VECTOR3 RGRAV;
	// Predicted cutoff position vector [FT]
	VECTOR3 RP;
	// Position change due to thrust [FT]
	VECTOR3 RTHRUST;
	// Desired thrust cutoff velocity vector [FT]
	VECTOR3 VD;
	// Guidance velocity vector [FT/SEC]
	VECTOR3 VGD;
	// Velocity-to-be gained vector [FT/SEC]
	VECTOR3 VGO;
	// Cutoff velocity error [FT/SEC]
	VECTOR3 VMISS;
	// Predicted cutoff velocity vector [FT/SEC]
	VECTOR3 VP;
	// Velocity change due to thrust [FT/SEC]
	VECTOR3 VTHRUST;

	// Current acceleration [FT/SEC^2]
	double ATR;
	// Maximum integration step size for gravity prediction [SEC]
	double DT_LIMIT;
	// Maximum value of VMISS for PEG convergence [FT/SEC]
	double EMISS;
	// Total vehicle thrust force [LBF]
	double FT;
	// Magnitude of linear tangent vector at start of thrust phase [ND]
	double IF_MAG_I;
	// Thrust integrals for Ith thrust phase
	double LA[3], SA[3], QA[3];
	// Magnitude of LAMD [1/SEC]
	double LAMDMAG;
	// Current mass [SLUGS]
	double M;
	//Thrust turn angle [RAD]
	double PHI;
	// Magnitude of position vector [FT]
	double RMAG;
	// Hypothetical time until total vehicle mass is consumed [SEC]
	double TAU[3];
	// Burn time of Ith thrust phase [SEC]
	double TB[3];
	// Time of guidance state vector [SEC]
	double TGD;
	// Time-to-go [SEC]
	double TGO;
	// Time to end of Ith thrust phase [SEC]
	double TGOA[3];
	// Previous value of TGO [SEC]
	double TGOP;
	// Value of (t-JOL) at start of thrust phase [SEC]
	double TI;
	// Time associated with reference thrust vector [SEC]
	double TLAM;
	// Predicted time of thrust cutoff [SEC]
	double TP;
	// Previous value of TP [SEC]
	double TPREV;
	// Previous value of TGD [SEC]
	double TPRIME;
	// Equivalent exhaust velocity [FT/SEC]
	double VEX;
	// Average exhaust velocity [FT/SEC]
	double VEXA[3];
	// Magnitude of VGO vector [SEC]
	double VGOMAG;
	// Q–S JOL [FT-SEC]
	double QPRIME;
	// Total thrust integrals
	double L, J, S, JOL;

	// Current phase
	int KPHASE;
	// Number of guidance phases
	int N;
	// Cycle counter
	int N_CYCLE;

	// Cutoff altitude constrained discrete
	bool SALT;
	// PEG convergence discrete
	bool SCONV;
	// PEG init discrete
	bool SINIT;
	// Constrain desired plane
	bool SPLANE;


	// CONSTANTS
	// Acceleration limit [FT/SEC**2]
	const double AL = 95.5;
	// Minimum step size, ascent precision predictor [SEC]
	double DTMIN = 2.0;
	// Maximum step size, ascent precision predictor [SEC]
	double DTMAX = 1.e20;
	// Minimum TBN-1 computation of TGO [SEC]
	const double ETB = 5.0;
	// Thrust scaling factor [ND]
	const double FT_FACTOR = 0.998;
	// OMS vacuum thrust [LBF]
	const double FT_OMS = 6.087e3;
	// Decimal fraction for VGO to be used for convergence criterion for VMISS [ND]
	const double KMISS = 1e-2;
	// OMS mass flow rate [SLUGS/SEC]
	const double MDOT_OMS = 6.004849e-1;
	// Maximum number of PEG iterations
	const int N_MAX = 1;
	// Number of integration steps for PEG gravity prediction [ND]
	const double NSEG = 10.0;
	// Maximum turning rate [RAD/SEC]
	const double PHIDOT_MAX = 3.5e-2;
	// Scalar damping factor applied to VMISS to correct V
	const double RHOMAG = 1.0;
	// TGO remaining when position constraints released [SEC]
	const double DTRD = 40.0;
};

/**
 * Controls shuttle during ascent (first and second stage).
 */
class AscentDAP : public SimpleGPCSoftware
{
public:
	explicit AscentDAP(SimpleGPCSystem* _gpc);
	virtual ~AscentDAP();

	void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;

	bool OnMajorModeChange(unsigned int newMajorMode) override;

	bool OnParseLine(const char* keyword, const char* value) override;
	void OnSaveState(FILEHANDLE scn) const override;

	void NullSRBNozzles( void );

	/**
	 * Gets current vehicle attitude errors (deg).
	 * @return	attitude errors (deg) (x=pitch, y=yaw, z=roll)
	 */
	VECTOR3 GetAttitudeErrors( void ) const;

	/**
	 * Gets current target heading
	 * @return target heading (rad)
	 */
	double GetTargetHeading( void ) const;

	/**
	 * Gets current FCS mode (true = AUTO, false = CSS)
	 * @return FCS mode
	 */
	bool GetFCSmode( void ) const;

	bool SERCenabled( void ) const;
	double GetEOVI( int EO ) const;
	double GetTgtSpd( void ) const;
	double GetInertialVelocity( void ) const;
	double GetThrustAcceleration( void ) const;
	double GetTimeRemaining( void ) const;
	double GetCrossTrack(void) const;
	double GetDeltaInclination(void) const;

private:
	/**
	 * First stage auto guidance
	 */
	void FirstStageGuidance( double dt );

	/**
	 * Second stage auto guidance
	 */
	void SecondStageGuidance( double dt );

	void InitializeAutopilot();

	/**
	 * Returns current heading in radians.
	 */
	double GetCurrentHeading() const;

	void GimbalSRBs( double simdt, const VECTOR3& degReqdRates, const VECTOR3& AngularVelocity );
	void GimbalSSMEs( double simdt, const VECTOR3& degReqdRates, const VECTOR3& AngularVelocity );

	/**
	 * Calculates target rates during first stage
	 * This phase uses fixed pitch profile
	 */
	void FirstStageRateCommand();
	/**
	 * Calculates target rates during second stage.
	 * Uses PEG guidance.
	 */
	void SecondStageRateCommand();
	/**
	 * Sets SSME throttle value during first stage.
	 */
	void FirstStageThrottle( double dt );
	/**
	 * Sets SSME throttle value during second stage.
	 */
	void SecondStageThrottle( double dt );

	void MajorCycle();
	void Navigate(double dt);

	void AdaptiveGuidanceThrottling( void );

	// TBD: Additional guidance and navigation tasks temporarily here
	// PFG input task
	void PFG_INP_TSK();
	// Ascent User Parameter Processing
	void AscentUPP();

	OBJHANDLE hEarth;

	// Velocity at cutoff (does not include tailoff)
	double TgtSpd;

	unsigned short KMAX_NOM;
	unsigned short KMAX_ABORT;
	unsigned short KMAX_SECONDARY;
	unsigned short K_CO_MAX;
	double VREF_ADJUST;
	double TREF_ADJUST;
	unsigned short OMSASS;
	double NOMTM;
	double MASS_LOW_LEVEL;
	double ALIM_1;
	double ALIM_2;
	double PHI_CMD;
	double PHI_2STG;
	double V_RHO_PHI;

	bool LAUTO_PLAMP;
	bool LCSS_PLAMP;
	bool LAUTO_RYLAMP;
	bool LCSS_RYLAMP;
	bool LAUTO_BFLAMP;
	bool LMNL_BFLAMP;
	bool RAUTO_PLAMP;
	bool RCSS_PLAMP;
	bool RAUTO_RYLAMP;
	bool RCSS_RYLAMP;
	bool RAUTO_BFLAMP;
	bool RMNL_BFLAMP;

	// ports for commanding thrusters
	discsignals::DiscOutPort OMSCommand[2];
	discsignals::DiscOutPort SERC;

	/**
	 * If true, the FCS is in AUTO mode. If false, the FCS is in CSS mode.
	 */
	bool AutoFCS;

	/**
	 * Vehicle rates calculated by guidance
	 */
	VECTOR3 degReqdRatesGuidance;

	PIDControl SRBGimbal[2][3];

	// copied from Atlantis.h
	double radTargetHeading;
	std::vector<double> stage1GuidanceVelTable, stage1GuidancePitchTable;

	//bool bAutopilot, bThrottle;
	double tSRBSep; //time(MET)
	double tLastMajorCycle;

	double target_pitch; // target second stage pitch in degrees
	double CmdPDot; // commanded second stage pitch rate in deg/sec
	double inertialVelocity; // velocity relative to Earth's center (v)

	double thrustAcceleration; // a0
	double ThrAngleP, ThrAngleY;
	double timeRemaining; // timeRemaining - T
	VECTOR3 VS, VSP, DVS; // Sensed velocity change

	SSME_SOP* pSSME_SOP;
	SSME_Operations* pSSME_Operations;
	MPS_ATVC_CMD_SOP* pMPS_ATVC_CMD_SOP;
	SRBSepSequence* pSRBSepSequence;
	RHC_SOP* pRHC_SOP;
	GNCUtilities* pGNCUtilities;
	StateVectorSoftware* pStateVectorSoftware;

	bool glimiting;// g limiting in progress
	double dt_thrt_glim;// timer for g limiting throttle cmds

	bool enaSERC;
	bool MEFail[3];
	int NSSME;
	bool finecount;

	double QPOLY[4];// SSME throttle velocity
	unsigned short THROT[4];// SSME throttle command
	int J;

	bool AGT_done;

	bool bNullSRBNozzles;

	double EOVI[2];

	double SSMETailoffDV[3];

	// TBD: This code should be in the Ascent UPP
	// Crosstrack [NM]
	double XTRK;
	// Delta inclination [RAD]
	double MEDS_D_INCL;

	AscentGuidance guid;
};
}

#endif// _dps_ASCENTDAP_H_
