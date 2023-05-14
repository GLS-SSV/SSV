/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/07   GLS
2020/05/08   GLS
2020/05/24   GLS
2020/06/12   GLS
2020/06/20   GLS
2021/01/19   GLS
2021/06/01   GLS
2021/07/31   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/04/17   GLS
2022/07/17   GLS
2022/07/24   GLS
2022/08/05   GLS
2022/08/17   GLS
2022/09/15   GLS
2022/09/29   GLS
2022/10/02   GLS
2022/10/09   GLS
2022/10/11   GLS
2022/10/12   GLS
2022/10/13   GLS
2022/10/21   GLS
2022/10/25   GLS
2022/10/28   GLS
2022/12/23   GLS
2023/01/11   GLS
2023/04/26   GLS
2023/04/28   GLS
2023/05/12   GLS
2023/05/14   GLS
********************************************/
#include "IDP.h"
#include "IDP_software.h"
#include "../Atlantis.h"
#include "../AtlantisSubsystemDirector.h"
#include "../vc/MDU.h"
#include "SimpleGPCSystem.h"
#include <MathSSV.h>
#include "Software/GNC/IO_Control.h"
#include "Software/GNC/SSME_Operations.h"
#include "Software/GNC/AscentDAP.h"
#include "Software/GNC/AerojetDAP.h"
#include "Software/GNC/Landing_SOP.h"
#include "Software/GNC/OMSBurnSoftware.h"
#include "Software/GNC/DedicatedDisplay_SOP.h"


namespace dps
{
	constexpr BUS_ID MEDS_BUS_ID[4] = {
		BUS_MEDS1,// IDP 1
		BUS_MEDS2,// IDP 2
		BUS_MEDS3,// IDP 3
		BUS_MEDS4// IDP 4
	};

	constexpr unsigned short DEU_KYBD_KEY_CODE[32] = {
		0xFFF9,// KEY_SWITCH_ACK
		0xFFF1,// KEY_SWITCH_MSGRESET
		0xFFE9,// KEY_SWITCH_SYSSUMM
		0xFFE1,// KEY_SWITCH_FAULTSUMM
		0xFFD9,// KEY_SWITCH_C
		0xFFD1,// KEY_SWITCH_B
		0xFFC9,// KEY_SWITCH_A
		0xFFC1,// KEY_SWITCH_GPCCRT
		0xFFFA,// KEY_SWITCH_F
		0xFFBA,// KEY_SWITCH_E
		0xFF7A,// KEY_SWITCH_D
		0xFF3A,// KEY_SWITCH_IORESET
		0xFEFA,// KEY_SWITCH_3
		0xFEBA,// KEY_SWITCH_2
		0xFE7A,// KEY_SWITCH_1
		0xFE3A,// KEY_SWITCH_ITEM
		0xFFFB,// KEY_SWITCH_6
		0xFDFB,// KEY_SWITCH_5
		0xFBFB,// KEY_SWITCH_4
		0xF9FB,// KEY_SWITCH_EXEC
		0xF7FB,// KEY_SWITCH_9
		0xF5FB,// KEY_SWITCH_8
		0xF3FB,// KEY_SWITCH_7
		0xF1FB,// KEY_SWITCH_OPS
		0xFFFC,// KEY_SWITCH_PLUS
		0xEFFC,// KEY_SWITCH_0
		0xDFFC,// KEY_SWITCH_MINUS
		0xCFFC,// KEY_SWITCH_SPEC
		0xBFFC,// KEY_SWITCH_PRO
		0xAFFC,// KEY_SWITCH_DOT
		0x9FFC,// KEY_SWITCH_CLEAR
		0x8FFC,// KEY_SWITCH_RESUME
	};

	IDP::IDP( AtlantisSubsystemDirector* _director, const string& _ident, unsigned short _usIDPID, BusManager* pBusManager )
		: AtlantisSubsystem( _director, _ident ), BusTerminal( pBusManager ), usIDPID(_usIDPID)
	{
		//// software init ////
		SPLkeyslen = 0;
		SPLerror = false;
		SPL[0] = 0;
		GPCkeybufflen = 0;
		KeyboardInput.clear();
		memset( ADCdata[0], 0, 32 * sizeof(unsigned short) );
		memset( ADCdata[1], 0, 32 * sizeof(unsigned short) );

		pSW = new IDP_software( this );
		//// software init ////

		majfunc=GNC;

		for (auto& x : keystateA) x = false;
		for (auto& x : keystateB) x = false;

		BusConnect( MEDS_BUS_ID[usIDPID - 1] );
		return;
	}

	IDP::~IDP()
	{
	}

	void IDP::Realize()
	{
		pGPC1 = dynamic_cast<SimpleGPCSystem*>(STS()->SubsystemDirector()->GetSubsystemByName( "SimpleGPC1" ));
		assert( (pGPC1 != NULL) && "IDP::Realize.pGPC1" );
		pGPC2 = dynamic_cast<SimpleGPCSystem*>(STS()->SubsystemDirector()->GetSubsystemByName( "SimpleGPC2" ));
		assert( (pGPC2 != NULL) && "IDP::Realize.pGPC2" );

		pIO_Control = dynamic_cast<IO_Control*> (pGPC1->FindSoftware( "IO_Control" ));
		assert( (pIO_Control != NULL) && "IDP::Realize.pIO_Control" );
		pSSME_Operations = dynamic_cast<SSME_Operations*> (pGPC1->FindSoftware( "SSME_Operations" ));
		assert( (pSSME_Operations != NULL) && "IDP::Realize.pSSME_Operations" );
		pAscentDAP = dynamic_cast<AscentDAP*> (pGPC1->FindSoftware( "AscentDAP" ));
		assert( (pAscentDAP != NULL) && "IDP::Realize.pAscentDAP" );
		pAerojetDAP = dynamic_cast<AerojetDAP*> (pGPC1->FindSoftware( "AerojetDAP" ));
		assert( (pAerojetDAP != NULL) && "IDP::Realize.pAerojetDAP" );
		pLanding_SOP = dynamic_cast<Landing_SOP*> (pGPC1->FindSoftware( "Landing_SOP" ));
		assert( (pLanding_SOP != NULL) && "IDP::Realize.pLanding_SOP" );
		pOMSBurnSoftware = dynamic_cast<OMSBurnSoftware*> (pGPC1->FindSoftware( "OMSBurnSoftware" ));
		assert( (pOMSBurnSoftware != NULL) && "IDP::Realize.pOMSBurnSoftware" );
		pDedicatedDisplay_SOP = dynamic_cast<DedicatedDisplay_SOP*> (pGPC1->FindSoftware( "DedicatedDisplay_SOP" ));
		assert( (pDedicatedDisplay_SOP != NULL) && "IDP::Realize.pDedicatedDisplay_SOP" );

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "CRT_IDP_Power", 16 );
		DiscreteBundle* pBundle4 = pBundle;
		Power.Connect( pBundle, ((usIDPID - 1) * 2) + 0 );

		pBundle = STS()->BundleManager()->CreateBundle( "IDP_Switches", 16 );
		MajorFuncPL.Connect( pBundle, ((usIDPID - 1) * 3) + 0 );
		MajorFuncSM.Connect( pBundle, ((usIDPID - 1) * 3) + 1 );
		MajorFuncGNC.Connect( pBundle, ((usIDPID - 1) * 3) + 2 );

		switch (usIDPID)
		{
			case 1:
				KeyboardSelectB.Connect( pBundle, 13 );

				pBundle = STS()->BundleManager()->CreateBundle( "LeftKeyboard_chB_1", 16 );
				for (int i = 0; i < 16; i++) KeyboardB[i].Connect( pBundle, i );
				pBundle = STS()->BundleManager()->CreateBundle( "LeftKeyboard_chB_2", 16 );
				for (int i = 0; i < 16; i++) KeyboardB[i + 16].Connect( pBundle, i );
				break;
			case 2:
				KeyboardSelectA.Connect( pBundle, 14 );

				pBundle = STS()->BundleManager()->CreateBundle( "RightKeyboard_chA_1", 16 );
				for (int i = 0; i < 16; i++) KeyboardA[i].Connect( pBundle, i );
				pBundle = STS()->BundleManager()->CreateBundle( "RightKeyboard_chA_2", 16 );
				for (int i = 0; i < 16; i++) KeyboardA[i + 16].Connect( pBundle, i );
				break;
			case 3:
				KeyboardSelectA.Connect( pBundle, 12 );
				KeyboardSelectB.Connect( pBundle, 15 );

				pBundle = STS()->BundleManager()->CreateBundle( "LeftKeyboard_chA_1", 16 );
				for (int i = 0; i < 16; i++) KeyboardA[i].Connect( pBundle, i );
				pBundle = STS()->BundleManager()->CreateBundle( "LeftKeyboard_chA_2", 16 );
				for (int i = 0; i < 16; i++) KeyboardA[i + 16].Connect( pBundle, i );

				pBundle = STS()->BundleManager()->CreateBundle( "RightKeyboard_chB_1", 16 );
				for (int i = 0; i < 16; i++) KeyboardB[i].Connect( pBundle, i );
				pBundle = STS()->BundleManager()->CreateBundle( "RightKeyboard_chB_2", 16 );
				for (int i = 0; i < 16; i++) KeyboardB[i + 16].Connect( pBundle, i );
				break;
			case 4:
				// HACK keyboard sel port A is always on (should be ground actually)
				// set from IDP power signal, so this will be on when needed
				KeyboardSelectA.Connect( pBundle4, 6 );

				pBundle = STS()->BundleManager()->CreateBundle( "MSSKeyboard_chA_1", 16 );
				for (int i = 0; i < 16; i++) KeyboardA[i].Connect( pBundle, i );
				pBundle = STS()->BundleManager()->CreateBundle( "MSSKeyboard_chA_2", 16 );
				for (int i = 0; i < 16; i++) KeyboardA[i + 16].Connect( pBundle, i );
				break;
		}
		
		return;
	}

	void IDP::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power.IsSet()) return;

		// read keyboard switches
		ReadKeyboard();

		pSW->RUN( simdt );
		return;
	}

	unsigned short IDP::GetIDPID() const {
		return usIDPID;
	}

	MAJORFUNCTION IDP::GetMajfunc() const
	{
		return majfunc;
	}

	int IDP::GetActiveKeyboard( void ) const
	{
		int kb = 0;

		switch (usIDPID)
		{
			case 1:
				if (KeyboardSelectB.IsSet()) kb = 1;
				break;
			case 2:
				if (KeyboardSelectA.IsSet()) kb = 2;
				break;
			case 3:
				if (KeyboardSelectA.IsSet()) kb = 1;
				if (KeyboardSelectB.IsSet()) kb += 2;
				break;
		}
		return kb;
	}

	void IDP::ReadKeyboard( void )
	{
		if (KeyboardSelectA.IsSet())
		{
			for (char i = 0; i < 32; i++)
			{
				if (KeyboardA[i].IsSet() != keystateA[i])
				{
					if (KeyboardA[i].IsSet()) KeyboardInput.push_back( DEU_KYBD_KEY_CODE[i] );
					keystateA[i] = !keystateA[i];
				}
			}
		}

		if (KeyboardSelectB.IsSet())
		{
			for (char i = 0; i < 32; i++)
			{
				if (KeyboardB[i].IsSet() != keystateB[i])
				{
					if (KeyboardB[i].IsSet()) KeyboardInput.push_back( DEU_KYBD_KEY_CODE[i] );
					keystateB[i] = !keystateB[i];
				}
			}
		}
		return;
	}

	void IDP::SetMajFunc(MAJORFUNCTION func)
	{
		majfunc=func;
	}

	void IDP::ConnectToMDU(vc::MDU* pMDU, bool bPrimary)
	{
		if(pMDU) {
			if(bPrimary) {
				pMDU->SetPrimaryIDP(this);
			}
			else pMDU->SetSecondaryIDP(this);
		}
	}

	void IDP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool IDP::OnParseLine( const char* line )
	{
		return false;
	}

	bool IDP::OnPaint( vc::MDU* pMDU )
	{
		if (GetGPC()->OnPaint( usIDPID, pMDU ))
		{
			// print fault message line
			PrintFaultMessageLine( pMDU );

			//print Scratch Pad line
			PrintScratchPadLine( pMDU );
			return true;
		}
		return false;
	}

	void IDP::PrintScratchPadLine( vc::MDU* pMDU ) const
	{
		size_t len = strlen( SPL );
		char tmp[2];
		tmp[1] = 0;
		for (unsigned int i = 0; i < len; i++)
		{
			tmp[0] = SPL[i];
			pMDU->mvprint( i, 25, tmp, SPLatt[i] );
		}
		return;
	}

	void IDP::PrintFaultMessageLine( vc::MDU* pMDU ) const
	{
		// get from GPC
		bool flash = false;
		char cFaultMessageLine[64];
		memset( cFaultMessageLine, 0, 64 * sizeof(char) );
		GetGPC()->GetFaultMsg( cFaultMessageLine, flash, usIDPID );

		if (cFaultMessageLine[0]) pMDU->mvprint( 0, 24, cFaultMessageLine, flash ? dps::DEUATT_FLASHING : dps::DEUATT_NORMAL );
		return;
	}

	int IDP::GetADIAttitude( void )
	{
		switch (usIDPID)
		{
			case 1:
				return pIO_Control->GetSWPos( SW_ADI_ATTITUDE_F6 );
			case 2:
				return pIO_Control->GetSWPos( SW_ADI_ATTITUDE_F8 );
			case 4:
				return pIO_Control->GetSWPos( SW_ADI_ATTITUDE_A6U );
			default:
				return 1;// switch in LVLH
		}
	}

	int IDP::GetADIError( void )
	{
		switch (usIDPID)
		{
			case 1:
				return pIO_Control->GetSWPos( SW_ADI_ERROR_F6 );
			case 2:
				return pIO_Control->GetSWPos( SW_ADI_ERROR_F8 );
			case 4:
				return pIO_Control->GetSWPos( SW_ADI_ERROR_A6U );
			default:
				return 1;// switch in MED
		}
	}

	int IDP::GetADIRate( void )
	{
		switch (usIDPID)
		{
			case 1:
				return pIO_Control->GetSWPos( SW_ADI_RATE_F6 );
			case 2:
				return pIO_Control->GetSWPos( SW_ADI_RATE_F8 );
			case 4:
				return pIO_Control->GetSWPos( SW_ADI_RATE_A6U );
			default:
				return 1;// switch in MED
		}
	}

	bool IDP::GetMECOConfirmedFlag( void ) const
	{
		return pSSME_Operations->GetMECOConfirmedFlag();
	}

	bool IDP::GetAutoThrottleState( void ) const
	{
		return pAscentDAP->GetAutoThrottleState();
	}

	VECTOR3 IDP::GetAttitudeErrors_AscentDAP( void ) const
	{
		return pAscentDAP->GetAttitudeErrors();
	}

	VECTOR3 IDP::GetAttitudeErrors_AerojetDAP( void ) const
	{
		return pAerojetDAP->GetAttitudeErrors();
	}

	VECTOR3 IDP::GetRates( void ) const
	{
		return pAerojetDAP->GetRates();
	}

	VECTOR3 IDP::GetAttitudeCommandErrors( void ) const
	{
		return pOMSBurnSoftware->GetAttitudeCommandErrors();
	}

	bool IDP::GetAutoPitchState( void ) const
	{
		return pAerojetDAP->GetAutoPitchState();
	}

	bool IDP::GetAutoRollYawState( void ) const
	{
		return pAerojetDAP->GetAutoRollYawState();
	}

	bool IDP::GetAutoSpeedbrakeState( void ) const
	{
		return pAerojetDAP->GetAutoSpeedbrakeState();
	}

	bool IDP::GetAerosurfacePositions( double& LOB, double& LIB, double& RIB, double& ROB, double& Aileron, double& Rudder, double& BodyFlap, double& SpeedBrake_Pos, double& SpeedBrake_Cmd ) const
	{
		switch (STS()->GetGPCMajorMode())
		{
			case 304:
			case 305:
			case 602:
			case 603:
			case 801:
			case 901:
				break;
			default:
				return false;
		}

		BodyFlap = (100.0 * ADCdata[0][0]) / 2048;
		Aileron = ((10.0 * ADCdata[0][1]) / 2048) - 5.0;
		LIB = ((55.0 * ADCdata[0][2]) / 2048) - 35.0;
		LOB = ((55.0 * ADCdata[0][3]) / 2048) - 35.0;
		RIB = ((55.0 * ADCdata[0][4]) / 2048) - 35.0;
		ROB = ((55.0 * ADCdata[0][5]) / 2048) - 35.0;
		SpeedBrake_Pos = (100.0 * ADCdata[0][6]) / 2048;
		Rudder = ((60.0 * ADCdata[0][7]) / 2048) - 30.0;
		SpeedBrake_Cmd = (100.0 * ADCdata[0][9]) / 2048;
		return true;
	}

	bool IDP::GetOMSdata( unsigned short& PC_L, unsigned short& PC_R, unsigned short& He_L, unsigned short& He_R, unsigned short& N2_L, unsigned short& N2_R ) const
	{
		He_L = Round( (5000.0 * ADCdata[0][23]) / 2048 );
		N2_L = Round( (3000.0 * ADCdata[0][24]) / 2048 );
		PC_L = Round( (160.0 * ADCdata[0][25]) / 2048 );
		He_R = Round( (5000.0 * ADCdata[0][27]) / 2048 );
		N2_R = Round( (3000.0 * ADCdata[0][28]) / 2048 );
		PC_R = Round( (160.0 * ADCdata[0][29]) / 2048 );
		return true;
	}

	bool IDP::GetMPSdata( unsigned short& PC_C, unsigned short& PC_L, unsigned short& PC_R, unsigned short& HeTk_C, unsigned short& HeTk_L, unsigned short& HeTk_R, unsigned short& HeTk_Pneu, unsigned short& HeReg_C, unsigned short& HeReg_L, unsigned short& HeReg_R, unsigned short& HeReg_Pneu, unsigned short& LH2_Manif, unsigned short& LO2_Manif ) const
	{
		PC_C = Round( (115.0 * ADCdata[0][10]) / 2048 );
		PC_L = Round( (115.0 * ADCdata[0][11]) / 2048 );
		PC_R = Round( (115.0 * ADCdata[0][12]) / 2048 );
		LH2_Manif = Round( (100.0 * ADCdata[0][13]) / 2048 );
		HeTk_L = Round( (5000.0 * ADCdata[0][14]) / 2048 );
		HeReg_L = Round( (1000.0 * ADCdata[0][15]) / 2048 );
		HeTk_Pneu = Round( (5000.0 * ADCdata[0][16]) / 2048 );
		HeReg_Pneu = Round( (1000.0 * ADCdata[0][17]) / 2048 );
		LO2_Manif = Round( (300.0 * ADCdata[0][18]) / 2048 );
		HeTk_C = Round( (5000.0 * ADCdata[0][19]) / 2048 );
		HeReg_C = Round( (1000.0 * ADCdata[0][20]) / 2048 );
		HeTk_R = Round( (5000.0 * ADCdata[0][21]) / 2048 );
		HeReg_R = Round( (1000.0 * ADCdata[0][22]) / 2048 );
		return true;
	}

	bool IDP::GetAPUdata( unsigned short& FuQty_1, unsigned short& FuQty_2, unsigned short& FuQty_3, unsigned short& Fu_Press_1, unsigned short& Fu_Press_2, unsigned short& Fu_Press_3, unsigned short& H2OQty_1, unsigned short& H2OQty_2, unsigned short& H2OQty_3, unsigned short& OilIn_1, unsigned short& OilIn_2, unsigned short& OilIn_3 ) const
	{
		FuQty_1 = Round( (100.0 * ADCdata[1][0]) / 2048 );
		H2OQty_1 = Round( (100.0 * ADCdata[1][1]) / 2048 );
		FuQty_2 = Round( (100.0 * ADCdata[1][2]) / 2048 );
		H2OQty_2 = Round( (100.0 * ADCdata[1][3]) / 2048 );
		H2OQty_3 = Round( (100.0 * ADCdata[1][4]) / 2048 );
		FuQty_3 = Round( (100.0 * ADCdata[1][5]) / 2048 );
		Fu_Press_1 = Round( (500.0 * ADCdata[1][6]) / 2048 );
		OilIn_1 = Round( (500.0 * ADCdata[1][7]) / 2048 );
		Fu_Press_2 = Round( (500.0 * ADCdata[1][11]) / 2048 );
		OilIn_2 = Round( (500.0 * ADCdata[1][12]) / 2048 );
		Fu_Press_3 = Round( (500.0 * ADCdata[1][16]) / 2048 );
		OilIn_3 = Round( (500.0 * ADCdata[1][17]) / 2048 );
		return true;
	}

	bool IDP::GetHYDdata( unsigned short& Qty_1, unsigned short& Qty_2, unsigned short& Qty_3, unsigned short& Press_1, unsigned short& Press_2, unsigned short& Press_3 ) const
	{
		Press_1 = Round( (4000.0 * ADCdata[1][9]) / 2048 );
		Qty_1 = Round( (100.0 * ADCdata[1][10]) / 2048 );
		Press_2 = Round( (4000.0 * ADCdata[1][14]) / 2048 );
		Qty_2 = Round( (100.0 * ADCdata[1][15]) / 2048 );
		Press_3 = Round( (4000.0 * ADCdata[1][19]) / 2048 );
		Qty_3 = Round( (100.0 * ADCdata[1][20]) / 2048 );
		return true;
	}

	bool IDP::GetWOW( void ) const
	{
		return pLanding_SOP->GetWOWLON();
	}

	double IDP::GetNZError( void ) const
	{
		return pAerojetDAP->GetNZError();
	}

	bool IDP::GetPrefinalState( void ) const
	{
		return pAerojetDAP->GetPrefinalState();
	}

	double IDP::GetYRunwayPositionError( void ) const
	{
		return pAerojetDAP->GetYRunwayPositionError();
	}

	bool IDP::GetOnHACState( void ) const
	{
		return pAerojetDAP->GetOnHACState();
	}

	double IDP::GetHACRadialError( void ) const
	{
		return pAerojetDAP->GetHACRadialError();
	}

	double IDP::GetTimeToHAC( void ) const
	{
		return pAerojetDAP->GetTimeToHAC();
	}

	double IDP::GetdeltaAZ( void ) const
	{
		return pAerojetDAP->GetdeltaAZ();
	}

	void IDP::GetSelectedRunway( char* rw ) const
	{
		pAerojetDAP->GetSelectedRunway( rw );
		return;
	}

	bool IDP::GetApproachAndLandState( void ) const
	{
		return pAerojetDAP->GetApproachAndLandState();
	}

	double IDP::GetVacc( void ) const
	{
		return pAerojetDAP->GetVacc();
	}

	double IDP::GetHTA( void ) const
	{
		return pAerojetDAP->GetHTA();
	}

	double IDP::GetGlideSlopeDistance( void ) const
	{
		return pAerojetDAP->GetGlideSlopeDistance();
	}

	double IDP::GetNZ( void ) const
	{
		return pAerojetDAP->GetNZ();
	}

	double IDP::GetdeltaAZLimit( void ) const
	{
		return pAerojetDAP->GetdeltaAZLimit();
	}

	double IDP::GetSelectedRunwayHeading( void ) const
	{
		return pAerojetDAP->GetSelectedRunwayHeading();
	}

	double IDP::GetTargetHeading( void ) const
	{
		return pAscentDAP->GetTargetHeading();
	}

	bool IDP::GetFCSmode( void ) const
	{
		return pAscentDAP->GetFCSmode();
	}

	double IDP::GetAltitude( void ) const
	{
		return pAerojetDAP->GetAltitude();
	}

	double IDP::GetAltitudeRate( void ) const
	{
		return pAerojetDAP->GetAltitudeRate();
	}

	double IDP::GetVrel( void ) const
	{
		return pAerojetDAP->GetVrel();
	}

	double IDP::GetSelectedRunwayRange( void ) const
	{
		return pDedicatedDisplay_SOP->GetSelectedRunwayRange();
	}

	double IDP::GetHACCRange( void ) const
	{
		return pDedicatedDisplay_SOP->GetHACCRange();
	}

	double IDP::GetPrimaryBearing( void ) const
	{
		return pDedicatedDisplay_SOP->GetPrimaryBearing();
	}

	char IDP::GetPrimaryBearingType( void ) const
	{
		return pDedicatedDisplay_SOP->GetPrimaryBearingType();
	}

	double IDP::GetSecondaryBearing( void ) const
	{
		return pDedicatedDisplay_SOP->GetSecondaryBearing();
	}

	char IDP::GetSecondaryBearingType( void ) const
	{
		return pDedicatedDisplay_SOP->GetSecondaryBearingType();
	}

	double IDP::GetCourseDeviation( void ) const
	{
		return pDedicatedDisplay_SOP->GetCourseDeviation();
	}

	double IDP::GetCourseDeviationScale( void ) const
	{
		return pDedicatedDisplay_SOP->GetCourseDeviationScale();
	}

	double IDP::GetGlideSlopeDeviation( void ) const
	{
		return pDedicatedDisplay_SOP->GetGlideSlopeDeviation();
	}

	double IDP::GetGlideSlopeDeviationScale( void ) const
	{
		return pDedicatedDisplay_SOP->GetGlideSlopeDeviationScale();
	}

	bool IDP::GetGSFlag( void ) const
	{
		return pDedicatedDisplay_SOP->GetGSFlag();
	}

	SimpleGPCSystem* IDP::GetGPC( void ) const
	{
		if (!MajorFuncPL.IsSet() && !MajorFuncGNC.IsSet()) return pGPC2;
		else return pGPC1;
	}

	void IDP::MEDStransaction( const unsigned short RTaddress, const unsigned short TR, const unsigned short subaddressmode, unsigned short* const data, const unsigned short datalen )
	{
		unsigned int outdata[33];
		memset( outdata, 0, 33 * sizeof(unsigned int) );

		unsigned short datawordcount = datalen;
		if (datawordcount == 32) datawordcount = 0;

		outdata[0] |= RTaddress << 12;// remote terminal address
		outdata[0] |= TR << 11;// transmit/receive
		outdata[0] |= subaddressmode << 6;// subaddress/mode
		outdata[0] |= datawordcount << 1;// data word count/mode code
		outdata[0] |= (~CalcParity( outdata[0] )) & 1;// parity

		if (TR == 0)
		{
			// append data for RT
			for (int i = 0; i < datalen; i++)
			{
				outdata[i + 1] |= data[i] << 1;// data
				outdata[i + 1] |= (~CalcParity( outdata[i + 1] )) & 1;// parity
			}

			busrecvbufaddr = 0;
			busrecvbuflen = 0;
			busterminaladdress = RTaddress;
		}
		else
		{
			// prepare to receive data from RT
			busrecvbufaddr = data;
			busrecvbuflen = datalen;
			busterminaladdress = RTaddress;
		}

		Tx( MEDS_BUS_ID[usIDPID - 1], outdata, 1 + (TR == 0) ? datalen : 0 );
		return;
	}

	void IDP::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!Power.IsSet()) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process status word
		{
			// check addr
			int dataaddr = (rcvd[0] >> 12) & 0b11111;
			if (busterminaladdress != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		// TODO decode

		//// process data word
		if ((busrecvbuflen + 1) != datalen) return;

		for (int i = 1; i <= busrecvbuflen; i++)
		{
			// check parity
			if (CalcParity( rcvd[i] ) == 0) break;

			busrecvbufaddr[i - 1] = (rcvd[i] >> 1) & 0xFFFF;// data
		}
		return;
	}
}
