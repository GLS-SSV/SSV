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
class SBTC_SOP;

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
	 * Gets current state of throttle commanding.
	 * @return	true if AUTO, false if MAN
	 */
	bool GetAutoThrottleState( void ) const;

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

	/**
	 * Calculates heading required to reach target inclination.
	 * \returns heading in radians
	 */
	double CalculateAzimuth();
	void MajorCycle();
	void Navigate();
	void Estimate();
	void Guide();

	void AdaptiveGuidanceThrottling( void );

	// utility functions required by PEG guidance
	inline double b0(double TT) {
		return -Isp*log(1-TT/tau);
	}
	inline double bn(double TT, int n) {
		if(n==0) return b0(TT);
		return bn(TT,n-1)*tau-Isp*pow(TT,n)/n;
	}
	inline double c0(double TT) {
		return b0(TT)*TT-bn(TT,1);
	}
	inline double cn(double TT, int n) {
		if(n==0) return c0(TT);
		return cn(TT,n-1)*tau-Isp*pow(TT,n+1)/(n*(n+1));
	}

	OBJHANDLE hEarth;
	double mu;
	double EarthRadius, SidDay;

	// guidance parameters
	double TgtInc, TgtFPA, TgtAlt, TgtSpd;

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
	double radTargetHeading, TAp, TPe, TTrA, TEcc, TgtRad;
	std::vector<double> stage1GuidanceVelTable, stage1GuidancePitchTable;
	bool dogleg;

	//bool bAutopilot, bThrottle;
	double tSRBSep; //time(MET)
	double tLastMajorCycle;

	double target_pitch; // target second stage pitch in degrees
	double CmdPDot; // commanded second stage pitch rate in deg/sec
	VECTOR3 rh0;
	double radius; // distance from centre of Earth (r)
	double inertialVelocity; // velocity relative to Earth's center (v)
	double /*r,*/h,/*theta,*/omega/*,phi*/;
	VECTOR3 rh,thetah,hh;
	//VECTOR3 posMoon,velMoon,rmh;
	double vr,vtheta/*,vh*/;

	//double fh;
	//double pitch,yaw,roll;

	//double g;
	double thrustAcceleration; // a0
	double Isp, tau, ThrAngleP, ThrAngleY;
	double timeRemaining; // timeRemaining - T
	//double deltatheta,thetaT;
	//double fr,fdotr;
	//double d1,d2,d3,d4;
	double A,C;
	//double eCurrent;

	SSME_SOP* pSSME_SOP;
	SSME_Operations* pSSME_Operations;
	MPS_ATVC_CMD_SOP* pMPS_ATVC_CMD_SOP;
	SRBSepSequence* pSRBSepSequence;
	RHC_SOP* pRHC_SOP;
	SBTC_SOP* pSBTC_SOP;

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
};

}

#endif// _dps_ASCENTDAP_H_
