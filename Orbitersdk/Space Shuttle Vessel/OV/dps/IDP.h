/****************************************************************************
  This file is part of Space Shuttle Vessel

  IDP subsystem definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/06/12   GLS
2020/06/20   GLS
2021/01/19   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  IDP subsystem definition



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
#ifndef _IDP_H_
#define _IDP_H_


#include <vector>
#include "dps_defs.h"
#include "../AtlantisSubsystem.h"
#include <DiscInPort.h>
#include <map>


namespace vc
{
	class MDU;
}


namespace dps {
	using discsignals::DiscInPort;

	using namespace std;

	class IO_Control;
	class SSME_Operations;
	class AscentDAP;
	class AerojetDAP;
	class Landing_SOP;
	class OMSBurnSoftware;
	class Elevon_PFB_SOP;
	class Rudder_PFB_SOP;
	class Speedbrake_PFB_SOP;
	class BodyFlap_PFB_SOP;
	class DedicatedDisplay_SOP;

	inline constexpr char DEUATT_NORMAL = 0;
	inline constexpr char DEUATT_OVERBRIGHT = 1;
	inline constexpr char DEUATT_FLASHING = 2;
	inline constexpr char DEUATT_UNDERLINED = 4;
	inline constexpr char DEUATT_DASHED = 8;

	/**
	 * Used to set IDP SPEC/DISP to undefined (not set)
	 */
	inline constexpr unsigned short MODE_UNDEFINED = (unsigned short)-1;


	/**
	 * Implementation of the Integrated display processor. Each can deal with a infinite number of
	 * MDUs.
 	 */
	class IDP : public AtlantisSubsystem
	{
	public:
		typedef enum __memory_state {
			MS_EMPTY = 0,
			MS_IPL,
			MS_OPERATIONAL
		} MEMORY_STATE;

	private:
		unsigned short usIDPID;
		vc::MDU* mdu_list[7];
		MAJORFUNCTION majfunc;
		MEMORY_STATE memstate;

		unsigned short usGPCDay;
		unsigned short usGPCHour;
		unsigned short usGPCMinute;
		unsigned short usGPCSecond;

		bool bGPCTimerActive;

		unsigned short usTimerDay;
		unsigned short usTimerHour;
		unsigned short usTimerMinute;
		unsigned short usTimerSecond;

		unsigned short usOPS;
		unsigned short usSPEC;
		unsigned short usDISP;
		char cScratchPadLine[64];
		short sScratchPadLength;
		char cFaultMessageLine[52];
		bool syntaxerr;
		unsigned short usGPCDriver;
		unsigned short usSelectedFC;
		DiscInPort Power;
		DiscInPort KeybSelectA;// Left IDP/CRT Sel
		DiscInPort KeybSelectB;// Right IDP/CRT Sel
		DiscInPort MajorFuncGNC;
		DiscInPort MajorFuncPL;

		IO_Control* pIO_Control;
		SSME_Operations* pSSME_Operations;
		AscentDAP* pAscentDAP;
		AerojetDAP* pAerojetDAP;
		Landing_SOP* pLanding_SOP;
		OMSBurnSoftware* pOMSBurnSoftware;
		Elevon_PFB_SOP* pElevon_PFB_SOP;
		Rudder_PFB_SOP* pRudder_PFB_SOP;
		Speedbrake_PFB_SOP* pSpeedbrake_PFB_SOP;
		BodyFlap_PFB_SOP* pBodyFlap_PFB_SOP;
		DedicatedDisplay_SOP* pDedicatedDisplay_SOP;


		void AppendScratchPadLine(char cKey);
		void ClearScratchPadLine();
		void DelFromScratchPadLine();
	protected:
		virtual void OnMMChange(unsigned short usNewMM);
		virtual void OnSysSummary();
		virtual void OnFaultSummary( bool ClearList );
		virtual void OnMsgReset();
		virtual void OnAck();
		virtual void OnClear();
		virtual void OnExec();
		virtual void OnPro();
		virtual void OnResume();

		void PrintTime(vc::MDU* mdu);
	public:
		IDP( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short _usIDPID );
		virtual ~IDP();
		void Realize() override;
		void ConnectToMDU(vc::MDU* pMDU, bool bPrimary = true);
		unsigned short GetIDPID() const;
		unsigned short GetOps() const;
		unsigned short GetSpec() const;
		unsigned short GetDisp() const;
		bool IsKeyboardSelected( unsigned short usKeyboardID ) const;
		virtual MAJORFUNCTION GetMajfunc() const;
		virtual const char* GetScratchPadLineString() const;
		virtual const char* GetScratchPadLineString_B( void ) const;
		virtual const char* GetScratchPadLineScan() const;
		virtual int GetFlashingEntry( void ) const;
		void PrintScratchPadLine( vc::MDU* pMDU ) const;
		void PrintFaultMessageLine( vc::MDU* pMDU ) const;

		/**
		 * Perform a initial program load.
		 * Basically just reset software configuration to basic and
		 * request critical format data from assigned GPC.
		 */
		virtual void IPL();
		bool IsBFS() const;
		virtual bool PutKey(unsigned short usKeyboardID, char cKey);
		void SetSpec(unsigned short spec);
		void SetDisp(unsigned short disp);
		void SetMajFunc(MAJORFUNCTION func);
		void OnSaveState(FILEHANDLE scn) const override;
		bool OnParseLine(const char* line) override;
		bool SingleParamParseLine() const override {return true;};
		//
		inline bool IsOPSLine() const {return (cScratchPadLine[0] == SSV_KEY_OPS);};
		inline bool IsSPECLine() const {return (cScratchPadLine[0] == SSV_KEY_SPEC);};
		inline bool IsITEMLine() const {return (cScratchPadLine[0] == SSV_KEY_ITEM);};
		inline bool IsGPCIDPLine() const {return (cScratchPadLine[0] == SSV_KEY_GPCCRT);};
		inline bool IsNoLine() const {return (cScratchPadLine[0] == '\0');};
		bool IsCompleteLine() const;

		/**
		 * Returns active keyboards:
		 * 0 none
		 * 1 CDR
		 * 2 PLT
		 * 3 CDR & PLT
		 */
		int GetActiveKeyboard( void ) const;

		virtual bool OnPaint(vc::MDU* pMDU);

		int GetADIAttitude( void );
		int GetADIError( void );
		int GetADIRate( void );
		bool GetMECOConfirmedFlag( void ) const;
		bool GetAutoThrottleState( void ) const;
		VECTOR3 GetAttitudeErrors_AscentDAP( void ) const;
		VECTOR3 GetAttitudeErrors_AerojetDAP( void ) const;
		VECTOR3 GetRates( void ) const;
		VECTOR3 GetAttitudeCommandErrors( void ) const;
		bool GetAutoPitchState( void ) const;
		bool GetAutoRollYawState( void ) const;
		bool GetAutoSpeedbrakeState( void ) const;
		double GetAutoSpeedbrakeCommand( void ) const;
		void GetAerosurfacePositions( double& LOB, double& LIB, double& RIB, double& ROB, double& DAFB, double& DRFB, double& DSBFB, double& DBFOFB ) const;
		bool GetWOW( void ) const;
		double GetNZError( void ) const;
		bool GetPrefinalState( void ) const;
		double GetYRunwayPositionError( void ) const;
		bool GetOnHACState( void ) const;
		double GetHACRadialError( void ) const;
		double GetTimeToHAC( void ) const;
		double GetdeltaAZ( void ) const;
		void GetSelectedRunway( char* rw ) const;
		bool GetApproachAndLandState( void ) const;
		double GetVacc( void ) const;
		double GetHTA( void ) const;
		double GetGlideSlopeDistance( void ) const;
		double GetNZ( void ) const;
		double GetdeltaAZLimit( void ) const;
		double GetSelectedRunwayHeading( void ) const;
		double GetTargetHeading( void ) const;
		bool GetFCSmode( void ) const;
		double GetAltitude( void ) const;
		double GetAltitudeRate( void ) const;
		double GetVrel( void ) const;
		double GetSelectedRunwayRange( void ) const;
		double GetHACCRange( void ) const;
		double GetPrimaryBearing( void ) const;
		char GetPrimaryBearingType( void ) const;
		double GetSecondaryBearing( void ) const;
		char GetSecondaryBearingType( void ) const;
		double GetCourseDeviation( void ) const;
		double GetCourseDeviationScale( void ) const;
		double GetGlideSlopeDeviation( void ) const;
		double GetGlideSlopeDeviationScale( void ) const;
		bool GetGSFlag( void ) const;
	};
}

#endif// _IDP_H_
