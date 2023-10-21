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
2020/03/20   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/12   GLS
2020/06/20   GLS
2021/01/19   GLS
2021/07/03   GLS
2021/07/31   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/07/24   GLS
2022/08/05   GLS
2022/09/15   GLS
2022/09/29   GLS
2022/10/02   GLS
2022/10/09   GLS
2022/10/11   GLS
2022/10/12   GLS
2022/10/21   GLS
2022/11/09   GLS
2023/04/26   GLS
2023/04/28   GLS
2023/05/12   GLS
2023/05/14   GLS
2023/05/27   GLS
2023/06/03   GLS
2023/10/22   GLS
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
#include <BusTerminal.h>
#include <map>


namespace vc
{
	class MDU;
}


namespace dps
{
	using discsignals::DiscInPort;

	using namespace std;

	class SimpleGPCSystem;
	class SSME_Operations;

	inline constexpr char DEUATT_NORMAL = 0;
	inline constexpr char DEUATT_OVERBRIGHT = 1;
	inline constexpr char DEUATT_FLASHING = 2;
	inline constexpr char DEUATT_UNDERLINED = 4;
	inline constexpr char DEUATT_DASHED = 8;


	/**
	 * Implementation of the Integrated display processor. Each can deal with a infinite number of
	 * MDUs.
 	 */
	class IDP : public AtlantisSubsystem, public BusTerminal
	{
		friend class IDP_software;

	private:
		unsigned short usIDPID;

		//// software memory ////
		unsigned char SPLkeys[31];// 30-key limit for GPC transmission (+1 for error detection)
		unsigned char ITEMstate[31];// keeps track of ITEM input state
		unsigned char SPLkeyslen;
		bool SPLerror;// indicates SPL syntax error

		char SPL[128];// key inputs for display
		char SPLatt[128];// attributes of key inputs for display

		unsigned char GPCkeybuff[30];
		unsigned char GPCkeybufflen;

		vector<unsigned short> KeyboardInput;

		unsigned short MDUstatus[11][32];

		unsigned short ADCdata[2][32];
		
		/*
		selected FC data source
		0 - CDR (IDP-1), PLT (IDP-2), CDR (IDP-3), Aft (IDP-1)
		1 - PLT (IDP-3)
		*/
		unsigned short selFC[2];

		/*
		0-13	ADI (14)
		14-23	HSI (10)
		24-29	AVVI (6)
		30-35	AMI (6)
		*/
		unsigned short FCdata[2][36];

		/*
		0-29	MEDS MSG 1 (30)
		30-59	MEDS MSG 2 (30)
		60-89	MEDS MSG 3 (30)
		90-119	MEDS MSG 4 (30)
		*/
		unsigned short MEDSdata[2][120];

		unsigned short PollResponseBuffer[16];
		//// software memory ////

		IDP_software* pSW;


		DiscInPort Power;
		DiscInPort KeyboardSelectA;
		DiscInPort KeyboardSelectB;
		DiscInPort KeyboardA[32];
		DiscInPort KeyboardB[32];
		DiscInPort MajorFuncGNC;
		DiscInPort MajorFuncSM;
		DiscInPort MajorFuncPL;

		SimpleGPCSystem* pGPC1;
		SimpleGPCSystem* pGPC2;
		SSME_Operations* pSSME_Operations;

		bool keystateA[32];
		bool keystateB[32];

		unsigned short* busrecvbufaddr;
		unsigned short busrecvbuflen;
		unsigned short busterminaladdress;


		SimpleGPCSystem* GetGPC( void ) const;

		void Rx_DK( const BUS_ID id, void* data, const unsigned short datalen );
		void Rx_FC( const BUS_ID id, void* data, const unsigned short datalen );
		void Rx_MEDS( const BUS_ID id, void* data, const unsigned short datalen );

	public:
		IDP( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short _usIDPID, BusManager* pBusManager );
		virtual ~IDP();
		void Realize() override;
		void OnPreStep( double simt, double simdt, double mjd ) override;
		unsigned short GetIDPID() const;
		void ReadKeyboard( void );

		void PrintScratchPadLine( vc::MDU* pMDU ) const;
		void PrintFaultMessageLine( vc::MDU* pMDU ) const;

		void OnSaveState( FILEHANDLE scn ) const override;
		bool OnParseLine( const char* line ) override;
		bool SingleParamParseLine() const override {return true;};

		/**
		 * Returns active keyboards:
		 * 0 none
		 * 1 CDR
		 * 2 PLT
		 * 3 CDR & PLT
		 */
		int GetActiveKeyboard( void ) const;


		void MEDStransaction( const unsigned short RTaddress, const unsigned short TR, const unsigned short subaddressmode, unsigned short* const data, const unsigned short datalen );
		void Rx( const BUS_ID id, void* data, const unsigned short datalen ) override;

		virtual bool OnPaint(vc::MDU* pMDU);

		bool GetMECOConfirmedFlag( void ) const;
		bool GetAutoThrottleState( void ) const;
		VECTOR3 GetAttitudeCommandErrors( void ) const;
		bool GetAutoPitchState( void ) const;
		bool GetAutoRollYawState( void ) const;
		bool GetAutoSpeedbrakeState( void ) const;
		bool GetAerosurfacePositions( double& LOB, double& LIB, double& RIB, double& ROB, double& Aileron, double& Rudder, double& BodyFlap, double& SpeedBrake_Pos, double& SpeedBrake_Cmd ) const;
		bool GetOMSdata( unsigned short& PC_L, unsigned short& PC_R, unsigned short& He_L, unsigned short& He_R, unsigned short& N2_L, unsigned short& N2_R ) const;
		bool GetMPSdata( unsigned short& PC_C, unsigned short& PC_L, unsigned short& PC_R, unsigned short& HeTk_C, unsigned short& HeTk_L, unsigned short& HeTk_R, unsigned short& HeTk_Pneu, unsigned short& HeReg_C, unsigned short& HeReg_L, unsigned short& HeReg_R, unsigned short& HeReg_Pneu, unsigned short& LH2_Manif, unsigned short& LO2_Manif ) const;
		bool GetAPUdata( unsigned short& FuQty_1, unsigned short& FuQty_2, unsigned short& FuQty_3, unsigned short& Fu_Press_1, unsigned short& Fu_Press_2, unsigned short& Fu_Press_3, unsigned short& H2OQty_1, unsigned short& H2OQty_2, unsigned short& H2OQty_3, unsigned short& OilIn_1, unsigned short& OilIn_2, unsigned short& OilIn_3 ) const;
		bool GetHYDdata( unsigned short& Qty_1, unsigned short& Qty_2, unsigned short& Qty_3, unsigned short& Press_1, unsigned short& Press_2, unsigned short& Press_3 ) const;
		double GetNZError( void ) const;
		bool GetPrefinalState( void ) const;
		unsigned short GetdeltaAZ( void ) const;
		bool FlashdeltaAZ( void ) const;
		void GetSelectedRunway( char* rw ) const;
		double GetVacc( void ) const;
		double GetHTA( void ) const;
		double GetNZ( void ) const;
		double GetHeading( void ) const;
		double GetCourse( void ) const;
		bool DrawCourse( void ) const;
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
		short GetCourseDeviation( void ) const;
		double GetCourseDeviationScale( void ) const;
		bool GetCourseDeviationFlag( void ) const;
		bool DrawCourseDeviation( void ) const;
		short GetGlideSlopeDeviation( void ) const;
		double GetGlideSlopeDeviationScale( void ) const;
		bool GetGlideSlopeDeviationFlag( void ) const;
		bool DrawGlideSlopeDeviation( void ) const;
		void GetADIAtt( const unsigned short MDU, double& sinpitch, double& cospitch, double& sinroll, double& cosroll, double& sinyaw, double& cosyaw ) const;
		void GetADIRate( const unsigned short MDU, unsigned short& pitchrate, unsigned short& rollrate, unsigned short& yawrate, unsigned short& pitchratescale, unsigned short& rollratescale, unsigned short& yawratescale, unsigned short& TGOSEC, unsigned short& ADIRR_0_ON_R ) const;
		void GetADIError( const unsigned short MDU, unsigned short& pitcherror, unsigned short& rollerror, unsigned short& yawerror, unsigned short& pitcherrorscale ) const;
	};
}

#endif// _IDP_H_
