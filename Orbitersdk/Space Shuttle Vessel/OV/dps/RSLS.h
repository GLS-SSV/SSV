/****************************************************************************
  This file is part of Space Shuttle Vessel

  RSLS software definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/10/18   GLS
2021/05/08   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/20   GLS
2022/09/29   GLS
2022/10/26   GLS
2022/12/15   indy91
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  RSLS software definition



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
#ifndef _RSLS_H
#define _RSLS_H


#include "SimpleGPCSoftware.h"
#include <discsignals.h>


using namespace discsignals;


namespace dps
{
	class SSME_SOP;
	class IO_Control;
	class MPS_ATVC_CMD_SOP;
	class MEC_SOP;
	class FCOS;

	class RSLS:public SimpleGPCSoftware
	{
	public:
		explicit RSLS( SimpleGPCSystem* _gpc );
		~RSLS();

		void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

		void OnPostStep(double simT, double dT, double mjd) override;

		void Realize() override;
		bool OnMajorModeChange( unsigned int newMajorMode ) override;

		void SetGMTLO( double GMTLO );
		void SetGMTLOSetCommandFlag( bool val );
		void SetLPSCountdownHoldFlag( bool val );
		void SetLPSGoForAutoSequenceStartFlag( bool val );
		void SetLPSGoForEngineStartFlag( bool val );
		void SetResumeCountCommandFlag( bool val );
		bool GetRSCountdownHoldFlag( void ) const;
		bool GetLaunchSequenceAbortFlag( void ) const;
		unsigned int GetHoldFlags( void ) const;

	private:
		SSME_SOP* pSSME_SOP;
		IO_Control* pIO_Control;
		MPS_ATVC_CMD_SOP* pMPS_ATVC_CMD_SOP;
		MEC_SOP* pMEC_SOP;
		FCOS* pFCOS;

		bool Active;

		// internal
		bool T0UmbilicalReleased;
		bool EngStartCmdIssued;
		bool ShtdnEnableCmdsIssued;
		bool FlagA;
		short CounterA;
		bool Eng1StartCmdIssued;
		bool Eng2StartCmdIssued;
		bool Eng3StartCmdIssued;
		bool ME1PrevalvesCmddClosed;
		bool ME2PrevalvesCmddClosed;
		bool ME3PrevalvesCmddClosed;

		// timers
		double ME1LOXPrevalveCloseDelayTimer;
		double ME2LOXPrevalveCloseDelayTimer;
		double ME3LOXPrevalveCloseDelayTimer;
		double ME1LH2PrevalveCloseDelayTimer;
		double ME2LH2PrevalveCloseDelayTimer;
		double ME3LH2PrevalveCloseDelayTimer;

		double EngStartTimer;
		double EngTimerThrustOK;
		double EngShutdownTimer;
		double AllEngShutdownTimer;
		double SRBIgnitionTimer;

		double FRFCutOffTimer;
		double FltCntlTVCInitTimer;
		double FRFThrottleTo92Timer;
		double FRFThrottleTo100Timer;

		bool CountdownClockCounting;
		bool firstpass_step1c;
		bool firstpass_step16a;
		bool firstpass_step19a;
		bool firstpass_step34;
		bool firstpass_step41h;

		bool SRBIgnitionCommand;// V90X8377X
		double CountdownTime;// V90W8380C
		bool LaunchSequenceAbort;// V90X8382X (a.k.a. "RSLS abort flag")
		bool EngineShutdownVerificationHold;// V90X8389X
		bool MPSLOXAccRecircVlvHold;// V90X8392X
		bool LPSGoForAutoSeqStartHold;// V90X8393X
		bool LPSGoForEngineStartHold;// V90X8394X
		bool RSSeqSSMEGoForLaunchHold;// V90X8395X
		bool MPSE1LH2PrevlvOpenHold;// V90X8396X
		bool MPSE2LH2PrevlvOpenHold;// V90X8397X
		bool MPSE3LH2PrevlvOpenHold;// V90X8398X
		bool MPSLO2OvbdBVCloseHold;// V90X8399X
		bool RSCountdownHold;// V90X8667X
		bool ME1PadDataPathFailHold;// V90X8670X
		bool ME2PadDataPathFailHold;// V90X8671X
		bool ME3PadDataPathFailHold;// V90X8672X
		bool ME1ControlFailHold;// V90X8679X
		bool ME2ControlFailHold;// V90X8680X
		bool ME3ControlFailHold;// V90X8681X
		bool VentDoorPositionHold;// V90X8770X
		bool ME1LowChamberPressureAbort;// V90X8773X
		bool ME2LowChamberPressureAbort;// V90X8774X
		bool ME3LowChamberPressureAbort;// V90X8775X
		bool UncommandedEngineShutdownAbort;// V90X8771X
		bool FlightCriticalMDMHoldAbort;// V90X8767X
		double GMTLO;// V99W8801C
		bool LPSGoForAutoSequenceStart;// V99X8803C
		bool LPSGoForEngineStart;// V99X8804X
		bool GMTLOSetCommand;// V99X8827X
		bool ResumeCountCommand;// V99X8828X
		bool LPSCountdownHold;// V99X8829X
		bool RecycleCountCmd;// V99X8830X

		// I-LOAD
		double LPS_GO_FOR_AUTO_SEQ_T;// V97U9700C
		double SRB_IGN_ARM_T;// V97U9701C
		double SRB_PIC_VOLTS_CHK_T;// V97U9702C
		//double OUTBD_FILL_VALVES_CLOSE_TIME;// V97U9703C
		double IMU_TO_INERTIAL_T;// V97U9704C
		double AUTO_RECYCLE_T;// V97U9705C
		double OPN_LO2_ACC_RECIRC_VLV_T;// V97U9706C
		double NAV_INIT_T;// V97U9707C
		double CONFIG_VNT_DRS_FOR_LCH_T;// V97U9708C
		double CHK_MPS_VLVS_POS_T;// V97U9709C
		double CLSE_LO2_OVBD_BV_T;// V97U9710C
		double CHK_PREVLVS_OPN_T;// V97U9711C
		double START_SSMES_T;// V97U9712C
		unsigned short ALL_ENG_PERCENT_CHB_PRS_CHK;// V97U9713C
		unsigned short ENG_PERCENT_CHB_PRS_FOR_GO;// V97U9714C
		double ENG_TIMER_FOR_THRUST_OK;// V97U9716C
		double VERIFY_ALL_ENG_SHTDN_TIMER;// V97U9719C
		double ME1_LOX_PREVLV_CLSE_DELAY;// V97U9720C
		double ME2_LOX_PREVLV_CLSE_DELAY;// V97U9721C
		double ME3_LOX_PREVLV_CLSE_DELAY;// V97U9722C
		double SRB_IGN_TIME_DELAY;// V97U9726C
		double ME1_LH2_PREVLV_CLSE_T_DELAY;// V97U9727C
		double ME2_LH2_PREVLV_CLSE_T_DELAY;// V97U9728C
		double ME3_LH2_PREVLV_CLSE_T_DELAY;// V97U9729C
		unsigned short SRB_IGN_PIC_LEVEL;// V97U9853C
		double FRF_CUTOFF_TIME_DELAY;// V97U9854C
		double FLT_CNTL_TVC_INIT_TIME_DELAY;// V97U9855C
		double FRF_THROTTLE_TO_92_TIME_DELAY;// V97U9856C
		double FRF_THROTTLE_TO_100_TIME_DELAY;// V97U9857C
		unsigned short FRF_TEST_FLAG;// V97U9858C

		DiscInPort PV19_CLInd[2];
		DiscInPort PV4_OPInd[2];
		DiscInPort PV5_OPInd[2];
		DiscInPort PV6_OPInd[2];
		DiscInPort PV20_OPInd;
		DiscInPort PV21_OPInd;
	};
}


#endif //_RSLS_H
