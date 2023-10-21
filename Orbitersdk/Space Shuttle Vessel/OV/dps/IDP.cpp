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
2023/05/27   GLS
2023/06/03   GLS
2023/06/14   GLS
2023/10/22   GLS
********************************************/
#include "IDP.h"
#include "IDP_software.h"
#include "../Atlantis.h"
#include "../AtlantisSubsystemDirector.h"
#include "../vc/MDU.h"
#include "SimpleGPCSystem.h"
#include <MathSSV.h>
#include "Software/GNC/SSME_Operations.h"


namespace dps
{
	constexpr BUS_ID DK_BUS_ID[4] = {
		BUS_DK1,// DK 1
		BUS_DK2,// DK 2
		BUS_DK3,// DK 3
		BUS_DK4// DK 4
	};
	constexpr BUS_ID MEDS_BUS_ID[4] = {
		BUS_MEDS1,// IDP 1
		BUS_MEDS2,// IDP 2
		BUS_MEDS3,// IDP 3
		BUS_MEDS4// IDP 4
	};

	constexpr unsigned short DK_ADDR = 10;

	constexpr unsigned short FC_ADDR[4] = {
		6,
		9,
		29,// HACK no clue
		15
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
		selFC[0] = 1;
		selFC[1] = 2;
		memset( ADCdata[0], 0, 32 * sizeof(unsigned short) );
		memset( ADCdata[1], 0, 32 * sizeof(unsigned short) );
		memset( FCdata[0], 0, 36 * sizeof(unsigned short) );
		memset( FCdata[1], 0, 36 * sizeof(unsigned short) );
		memset( MEDSdata[0], 0, 120 * sizeof(unsigned short) );
		memset( MEDSdata[1], 0, 120 * sizeof(unsigned short) );
		memset( PollResponseBuffer, 0, 16 * sizeof(unsigned short) );

		pSW = new IDP_software( this );
		//// software init ////

		for (auto& x : keystateA) x = false;
		for (auto& x : keystateB) x = false;

		BusConnect( DK_BUS_ID[usIDPID - 1] );
		BusConnect( BUS_FC1 );
		BusConnect( BUS_FC2 );
		BusConnect( BUS_FC3 );
		BusConnect( BUS_FC4 );
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

		pSSME_Operations = dynamic_cast<SSME_Operations*> (pGPC1->FindSoftware( "SSME_Operations" ));
		assert( (pSSME_Operations != NULL) && "IDP::Realize.pSSME_Operations" );

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

	bool IDP::GetMECOConfirmedFlag( void ) const
	{
		return pSSME_Operations->GetMECOConfirmedFlag();
	}

	bool IDP::GetAutoThrottleState( void ) const
	{
		return true;//pAscentDAP->GetAutoThrottleState();
	}

	VECTOR3 IDP::GetAttitudeCommandErrors( void ) const
	{
		return _V(0,0,0);//pOMSBurnSoftware->GetAttitudeCommandErrors();
	}

	bool IDP::GetAutoPitchState( void ) const
	{
		return true;//pAerojetDAP->GetAutoPitchState();
	}

	bool IDP::GetAutoRollYawState( void ) const
	{
		return true;//pAerojetDAP->GetAutoRollYawState();
	}

	bool IDP::GetAutoSpeedbrakeState( void ) const
	{
		return true;//pAerojetDAP->GetAutoSpeedbrakeState();
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

	double IDP::GetNZError( void ) const
	{
		return 0;//pAerojetDAP->GetNZError();
	}

	bool IDP::GetPrefinalState( void ) const
	{
		return 0;//pAerojetDAP->GetPrefinalState();
	}

	unsigned short IDP::GetdeltaAZ( void ) const
	{
		unsigned short daz = (MEDSdata[0][22] & 0x01FF) >> 0;// HACK
		return daz;
	}

	bool IDP::FlashdeltaAZ( void ) const
	{
		unsigned short flash = (MEDSdata[0][22] & 0x0200) >> 9;// HACK
		return (flash != 0);
	}

	void IDP::GetSelectedRunway( char* rw ) const
	{
		rw[0] = (MEDSdata[0][24] & 0x00FF) >> 0;
		rw[1] = (MEDSdata[0][24] & 0xFF00) >> 8;
		rw[2] = (MEDSdata[0][25] & 0x00FF) >> 0;
		rw[3] = (MEDSdata[0][25] & 0xFF00) >> 8;
		rw[4] = (MEDSdata[0][26] & 0x00FF) >> 0;
		return;
	}

	double IDP::GetVacc( void ) const
	{
		return 0.0;//pAerojetDAP->GetVacc();
	}

	double IDP::GetHTA( void ) const
	{
		return 0.0;//pAerojetDAP->GetHTA();
	}

	double IDP::GetNZ( void ) const
	{
		return 0;//pAerojetDAP->GetNZ();
	}

	double IDP::GetHeading( void ) const
	{
		return (FCdata[0][17] / 16) * (PI / 1024.0);// HACK
	}

	double IDP::GetCourse( void ) const
	{
		return (FCdata[0][16] / 16) * (PI / 1024.0);// HACK
	}

	bool IDP::DrawCourse( void ) const
	{
		unsigned short mm = (MEDSdata[0][7] & 0x03FF) >> 0;// HACK

		return (mm != 601);
	}

	bool IDP::GetFCSmode( void ) const
	{
		return 0;//pAscentDAP->GetFCSmode();
	}

	double IDP::GetAltitude( void ) const
	{
		return 0;//pAerojetDAP->GetAltitude();
	}

	double IDP::GetAltitudeRate( void ) const
	{
		return 0;//pAerojetDAP->GetAltitudeRate();
	}

	double IDP::GetVrel( void ) const
	{
		return 0;//pAerojetDAP->GetVrel();
	}

	double IDP::GetSelectedRunwayRange( void ) const
	{
		unsigned short bcd = FCdata[0][20];
		unsigned short rng = ((bcd & 0b11110) >> 1) * 1;
		rng += ((bcd & 0b111100000) >> 5) * 10;
		rng += ((bcd & 0b1111000000000) >> 9) * 100;
		rng += ((bcd & 0b110000000000000) >> 13) * 1000;

		unsigned short hsi_mode = (MEDSdata[0][12] & 0x000C) >> 2;// HACK left only
		if (hsi_mode != 1) return rng / 10.0;
		else return rng;
	}

	double IDP::GetHACCRange( void ) const
	{
		unsigned short bcd = FCdata[0][21];
		unsigned short rng = ((bcd & 0b11110) >> 1) * 1;
		rng += ((bcd & 0b111100000) >> 5) * 10;
		rng += ((bcd & 0b1111000000000) >> 9) * 100;
		rng += ((bcd & 0b110000000000000) >> 13) * 1000;

		unsigned short hsi_mode = (MEDSdata[0][12] & 0x000C) >> 2;// HACK left only
		if (hsi_mode != 1) return rng / 10.0;
		else return rng;
	}

	double IDP::GetPrimaryBearing( void ) const
	{
		return (FCdata[0][18] / 16) * (PI / 1024.0);// HACK
	}

	char IDP::GetPrimaryBearingType( void ) const
	{
		unsigned short hsi_mode = (MEDSdata[0][12] & 0x000C) >> 2;// HACK left only

		if (hsi_mode == 3)
		{
			return 'R';
		}
		else
		{
			return 'H';
		}
	}

	double IDP::GetSecondaryBearing( void ) const
	{
		return (FCdata[0][19] / 16) * (PI / 1024.0);// HACK
	}

	char IDP::GetSecondaryBearingType( void ) const
	{
		unsigned short hsi_mode = (MEDSdata[0][12] & 0x000C) >> 2;// HACK left only

		if (hsi_mode == 2)
		{
			return 'C';
		}
		else
		{
			return 0;
		}
	}

	short IDP::GetCourseDeviation( void ) const
	{
		return static_cast<short>(FCdata[0][22]) / 64;
	}

	double IDP::GetCourseDeviationScale( void ) const
	{
		double scale = 0;
		unsigned short mm = (MEDSdata[0][7] & 0x03FF) >> 0;// HACK
		
		if ((mm / 100) == 3)
		{
			unsigned short tg_end = (MEDSdata[0][11] & 0x0002) >> 1;// HACK

			if (tg_end == 0) scale = 10.0;
			else scale = 2.5;
		}
		else if (mm != 601)
		{
			scale = ((MEDSdata[0][21] & 0x01FF) >> 0) / 10.0;// HACK
		}
		return scale;
	}

	bool IDP::GetCourseDeviationFlag( void ) const
	{
		return ((FCdata[0][14] & 0x0100) == 0);// HACK
	}

	bool IDP::DrawCourseDeviation( void ) const
	{
		unsigned short mm = (MEDSdata[0][7] & 0x03FF) >> 0;// HACK

		return (mm != 601);
	}

	short IDP::GetGlideSlopeDeviation( void ) const
	{
		return static_cast<short>(FCdata[0][23]) / 64;
	}

	double IDP::GetGlideSlopeDeviationScale( void ) const
	{
		unsigned short hsi_mode = (MEDSdata[0][12] & 0x000C) >> 2;// HACK left only

		if (hsi_mode == 2) return 5000.0;
		else if (hsi_mode == 3) return 1000.0;
		return 0.0;
	}

	bool IDP::GetGlideSlopeDeviationFlag( void ) const
	{
		return ((FCdata[0][14] & 0x0080) == 0);// HACK
	}

	bool IDP::DrawGlideSlopeDeviation( void ) const
	{
		unsigned short hsi_mode = (MEDSdata[0][12] & 0x000C) >> 2;// HACK left only

		return (hsi_mode != 1);
	}

	void IDP::GetADIAtt( const unsigned short MDU, double& sinpitch, double& cospitch, double& sinroll, double& cosroll, double& sinyaw, double& cosyaw ) const
	{
		unsigned int st = 0;
		if ((MDU == 2) || (MDU == 3)) st = 1;

		sinpitch = static_cast<short>(FCdata[st][4]) / (8.0 * 4095);
		cospitch = static_cast<short>(FCdata[st][5]) / (8.0 * 4095);
		sinroll = static_cast<short>(FCdata[st][2]) / (8.0 * 4095);
		cosroll = static_cast<short>(FCdata[st][3]) / (8.0 * 4095);
		sinyaw = static_cast<short>(FCdata[st][6]) / (8.0 * 4095);
		cosyaw = static_cast<short>(FCdata[st][7]) / (8.0 * 4095);

		//double pitch = atan2( static_cast<short>(FCdata[st][4]), static_cast<short>(FCdata[st][5]) );
		//double roll = atan2( static_cast<short>(FCdata[st][2]), static_cast<short>(FCdata[st][3]) );
		//double yaw = atan2( static_cast<short>(FCdata[st][6]), static_cast<short>(FCdata[st][7]) );

		//if (pitch < 0.0) pitch += PI2;

		///*if (yaw > PI05) yaw = PI - yaw;
		//if (yaw < -PI05) yaw = PI - yaw;*/
		//if (yaw < 0.0) yaw += PI2;

		//if (roll < 0.0) roll += PI2;

		return;
	}

	void IDP::GetADIRate( const unsigned short MDU, unsigned short& pitchrate, unsigned short& rollrate, unsigned short& yawrate, unsigned short& pitchratescale, unsigned short& rollratescale, unsigned short& yawratescale, unsigned short& TGOSEC, unsigned short& ADIRR_0_ON_R ) const
	{
		unsigned int st = 0;
		if ((MDU == 2) || (MDU == 3)) st = 1;

		pitchrate = FCdata[st][9];
		rollrate = FCdata[st][8];
		yawrate = FCdata[st][10];

		// HACK left-right
		pitchratescale = (MEDSdata[st][15 + st] & 0x1FFF) >> 0;
		if (st == 0) rollratescale = (MEDSdata[st][19] & 0x00F0) >> 4;
		else rollratescale = (MEDSdata[st][19] & 0x000F) >> 0;
		yawratescale = (MEDSdata[st][17 + st] & 0x1FFF) >> 0;

		TGOSEC = (MEDSdata[st][15 + st] & 0x8000) >> 15;
		ADIRR_0_ON_R = (MEDSdata[st][15] & 0x4000) >> 14;
		return;
	}

	void IDP::GetADIError( const unsigned short MDU, unsigned short& pitcherror, unsigned short& rollerror, unsigned short& yawerror, unsigned short& pitcherrorscale ) const
	{
		unsigned int st = 0;
		if ((MDU == 2) || (MDU == 3)) st = 1;

		pitcherror = FCdata[st][12];
		rollerror = FCdata[st][11];
		yawerror = FCdata[st][13];

		// HACK left-right
		if (st == 0) pitcherrorscale = (MEDSdata[st][20] & 0xFF00) >> 8;
		else pitcherrorscale = (MEDSdata[st][20] & 0x00FF) >> 0;
		return;
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

		Tx( MEDS_BUS_ID[usIDPID - 1], outdata, 1 + ((TR == 0) ? datalen : 0) );
		return;
	}

	void IDP::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!Power.IsSet()) return;

		switch (id)
		{
			case BUS_DK1:
			case BUS_DK2:
			case BUS_DK3:
			case BUS_DK4:
				Rx_DK( id, data, datalen );
				break;
			case BUS_FC1:
			case BUS_FC2:
			case BUS_FC3:
			case BUS_FC4:
				Rx_FC( id, data, datalen );
				break;
			case BUS_MEDS1:
			case BUS_MEDS2:
			case BUS_MEDS3:
			case BUS_MEDS4:
				Rx_MEDS( id, data, datalen );
				break;
			default:
				break;
		}
		return;
	}

	void IDP::Rx_DK( const BUS_ID id, void* data, const unsigned short datalen )
	{
		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (DK_ADDR != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned short messagetype = (rcvd[0] >> 15) & 0b11111;// message type field
		unsigned short msgtypesub = (rcvd[0] >> 12) & 0b111;// msg type subfield
		//unsigned short wordcount = (rcvd[0] >> 1) & 0b111111111;// word count

		switch (messagetype)
		{
			case 0b00000:
				switch (msgtypesub)
				{
					case 0b100:
						// MCDS status request
						{
							unsigned int outdata[16];
							memset( outdata, 0, 16 * sizeof(unsigned int) );

							// DW1 (std header)
							PollResponseBuffer[0] |= 0b0000 << 12;// msg type indicator
							PollResponseBuffer[0] |= usIDPID << 8;// DEU ID (HACK should be sent by GPC)
							/*PollResponseBuffer[0] |= 0 << 4;// display freeze
							PollResponseBuffer[0] |= 0 << 2;// stand-alone self-test in progress
							PollResponseBuffer[0] |= 0 << 1;// critical BITE status present
							PollResponseBuffer[0] |= 0 << 0;// initialization required
							*/
							// DW2
							PollResponseBuffer[1] |= 0b00000000 << 8;// format index

							// DW3-12 (keystrokes)

							// DW13 (hardware status 1)

							// DW14 (hardware status 2)

							// DW15 (software status)
							// 0 - display/format data fill error
							// 1 - spare
							// 2 - initialization performed (critical BITE)
							// 3 - invalid fill/dump word count
							// 4 - MIA wrap word error
							// 5 - command overload
							// 6 - spare
							// 7 - CPU memory parity error (critial BITE)
							// 8 - spare
							// 9 - invalid message received
							// 10 - ripple test error
							// 11 - checksum error (format/IPL)
							// 12 - invalid fill/dump data address
							// 13 - received message incomplete
							// 14 - CPU self-test error (critical BITE)
							// 15 - incomplete DEU transmission

							// DW16 (check sum)
							unsigned int checksum = 0;
							for (int i = 0; i < 15; i++) checksum += PollResponseBuffer[i];
							PollResponseBuffer[15] = ((~checksum) + 1) & 0xFFFF;

							for (unsigned int i = 0; i < 16; i++)
							{
								outdata[i] |= DK_ADDR << 20;
								outdata[i] |= PollResponseBuffer[i] << 4;
								outdata[i] |= 0b101 << 1;// SEV
								outdata[i] |= (~CalcParity( outdata[i] )) & 1;// parity
							}

							Tx( id, outdata, 16 );

							// reset
							PollResponseBuffer[0] &= ~(1 << 11);// MSG RESET
							PollResponseBuffer[0] &= ~(1 << 5);// ACK
							PollResponseBuffer[0] &= ~(1 << 3);// keyboard msg present
							PollResponseBuffer[1] &= ~(0b11111 << 0);// keystroke count
						}
						break;
					default:
						break;
				}
				break;
			case 0b00010:
				// IPL BITE status request
				break;
			case 0b00100:
				// reset scratch pad line
				break;
			case 0b00110:
				// buffer fill
				break;
			case 0b11100:
				switch (msgtypesub)
				{
					case 0b000:
						// time fill
						break;
					case 0b011:
						// display fill
						break;
					case 0b101:
						// format fill
						break;
					default:
						break;
				}
				break;
			case 0b11101:
				// DEU memory dump
				break;
			default:
				break;
		}
		return;
	}

	void IDP::Rx_FC( const BUS_ID id, void* data, const unsigned short datalen )
	{
		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (FC_ADDR[usIDPID - 1] != dataaddr) return;
		}

		// check if FC selected
		unsigned short fc;
		if (id == BUS_FC1) fc = 1;
		else if (id == BUS_FC2) fc = 2;
		else if (id == BUS_FC3) fc = 3;
		else /*if (id == BUS_FC4)*/ fc = 4;

		unsigned short slot;
		if (selFC[0] == fc) slot = 0;
		else if (selFC[1] == fc) slot = 1;
		else return;

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned short wdcount = ((rcvd[0] >> 1) & 0b11111) + 1;// data words (rcvd = 0b00000 => 1 word)

		unsigned short msgid = (rcvd[0] >> 6) & 0b11111111111111;


		//// process command data words
		unsigned short datawords[32];// data field of command data words
		bool datawordsvalid[32];
		for (int i = 1; i <= wdcount; i++)
		{
			// check reception of words
			if (i > (datalen - 1))
			{
				datawordsvalid[i - 1] = false;
				continue;
			}

			// check parity
			if (CalcParity( rcvd[i] ) == 0)
			{
				datawordsvalid[i - 1] = false;
				continue;
			}

			// check address
			int dataaddr = (rcvd[i] >> 20) & 0b11111;
			if (FC_ADDR[usIDPID - 1] != dataaddr)
			{
				datawordsvalid[i - 1] = false;
				continue;
			}

			// check SEV
			unsigned short SEV = (rcvd[i] >> 1) & 0b111;
			if (SEV != 0b101)
			{
				datawordsvalid[i - 1] = false;
				continue;
			}

			// save data
			datawords[i - 1] = (rcvd[i] >> 4) & 0xFFFF;
			datawordsvalid[i - 1] = true;
		}

		switch (msgid)
		{
			case 0b10000000000001:// ADI L
			case 0b01000000000001:// ADI R
			case 0b00100000000001:// ADI A
				if (wdcount == 14)// 14 data words
				{
					for (int i = 0; i < 14; i++) if (datawordsvalid[i]) FCdata[slot][0 + i] = datawords[i];
				}
				break;
			case 0b10000000000010:// HSI L
			case 0b01000000000010:// HSI R
				if (wdcount == 10)// 10 data words
				{
					for (int i = 0; i < 10; i++) if (datawordsvalid[i]) FCdata[slot][14 + i] = datawords[i];
				}
				break;
			case 0b10000000000100:// AVVI L
			case 0b01000000000100:// AVVI R
				if (wdcount == 6)// 6 data words
				{
					for (int i = 0; i < 6; i++) if (datawordsvalid[i]) FCdata[slot][24 + i] = datawords[i];
				}
				break;
			case 0b10000000001000:// AMI L
			case 0b01000000001000:// AMI R
				if (wdcount == 6)// 6 data words
				{
					for (int i = 0; i < 6; i++) if (datawordsvalid[i]) FCdata[slot][30 + i] = datawords[i];
				}
				break;
			case 0b10000001000001:// MEDS FC GNC XFER 1
				if (wdcount == 30)// 30 data words
				{
					for (int i = 0; i < 30; i++) if (datawordsvalid[i]) MEDSdata[slot][0 + i] = datawords[i];
				}
				break;
			case 0b10000001000010:// MEDS FC GNC XFER 2
				if (wdcount == 30)// 30 data words
				{
					for (int i = 0; i < 30; i++) if (datawordsvalid[i]) MEDSdata[slot][30 + i] = datawords[i];
				}
				break;
			case 0b10000001000100:// MEDS FC GNC XFER 3
				if (wdcount == 30)// 30 data words
				{
					for (int i = 0; i < 30; i++) if (datawordsvalid[i]) MEDSdata[slot][60 + i] = datawords[i];
				}
				break;
			case 0b10000001001000:// MEDS FC GNC XFER 4
				if (wdcount == 30)// 30 data words
				{
					for (int i = 0; i < 30; i++) if (datawordsvalid[i]) MEDSdata[slot][90 + i] = datawords[i];
				}
				break;
		}
		return;
	}

	void IDP::Rx_MEDS( const BUS_ID id, void* data, const unsigned short datalen )
	{
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
