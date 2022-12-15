/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/18   GLS
2021/06/17   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/06/10   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/21   GLS
2022/10/28   GLS
2022/12/01   indy91
********************************************/
#include "MM801.h"
#include "IDP.h"
#include "../vc/MDU.h"
#include "../Atlantis.h"
#include <MathSSV.h>


constexpr double ELEVON_RATE = 5.8; // rate in deg/sec
constexpr double RUDDER_RATE = 5.0; // rate in deg/sec
constexpr double SPEEDBRAKE_RATE = 2.7; // rate in deg/sec
constexpr double ELEVON_POSITIONS[3] = {18.0, -33.0, -7.5}; // angles in degrees
constexpr double RUDDER_POSITIONS[3] = {5.0, -5.0, 0.0}; // angles in degrees
constexpr double SPEEDBRAKE_POSITIONS[3] = {10.0, 2.0, 10.0}; // deflection in degrees
constexpr double BODYFLAP_POSITIONS[3] = {20.3, -10.5, 4.5}; // deflection in degrees


namespace dps
{
	MM801::MM801( SimpleGPCSystem* _gpc ) : SimpleGPCSoftware( _gpc, "MM801" ),
	  ElevonTarget(0.0), RudderTarget(0.0), SpeedbrakeTarget(0.0), BodyflapDrive(0.0)
	{
		bFCSTestActive = false;
		ModeLT = false;

		downarrow_ElevonLOB = false;
		downarrow_ElevonLIB = false;
		downarrow_ElevonRIB = false;
		downarrow_ElevonROB = false;
		downarrow_Rudder = false;
		downarrow_Speedbrake = false;
	}

	MM801::~MM801()
	{

	}

	bool MM801::OnMajorModeChange(unsigned int newMajorMode)
	{
		bFCSTestActive = false;
		ModeLT = false;
		return (newMajorMode == 801);
	}

	void MM801::OnPaint( vc::MDU* pMDU ) const
	{
		PrintCommonHeader(" FCS/DED DIS C/O",pMDU);

		//DED DIS SECTION
		pMDU->mvprint(2,4,"DED DIS");
		pMDU->mvprint(1,5,"FWD 1");
		pMDU->mvprint(1,6,"AFT 2");
		pMDU->mvprint(9,5,"HIGH 3");
		pMDU->mvprint(9,6,"LOW  4");
		pMDU->mvprint(9,7,"FLAG 5");
		pMDU->mvprint(9,8,"OFF  6");

		//BODY FLP DES SECTION
		pMDU->mvprint(2,10,"BODY FLP DES");
		pMDU->mvprint(1,11,"VLV");
		pMDU->mvprint(5,11,"1");
		pMDU->mvprint(5,12,"2");
		pMDU->mvprint(5,13,"3");
		pMDU->mvprint(11,11,"12");
		pMDU->mvprint(11,12,"13");
		pMDU->mvprint(11,13,"14");

		//SEC ACT CK SECTION
		pMDU->mvprint(2,15,"SEC ACT CK");
		pMDU->mvprint(1,16,"CH 1  15");
		pMDU->mvprint(1,17,"CH 2  16");
		pMDU->mvprint(1,18,"CH 3  17");
		pMDU->mvprint(1,19,"CH 4  18");
		pMDU->mvprint(1,20,"STOP  19");
		pMDU->mvprint(1,21,"POS STIM");
		pMDU->mvprint(3,22,"ENA 20");

		//MODE LT SECTION
		pMDU->mvprint(21,4,"MODE LT");
		pMDU->mvprint(20,5,"ON   7");
		pMDU->mvprint(20,6,"OFF  8");

		//AVG G ON SECTION
		pMDU->mvprint(36,4,"AVG G  ON  9");

		//SURF DR SECTION
		pMDU->mvprint(21,9,"SURF DR");
		pMDU->mvprint(30,9,"START 10");
		pMDU->mvprint(41,9,"STOP 11");

		pMDU->mvprint(18,12,"SURF");
		pMDU->mvprint(29,12,"CMD");
		pMDU->mvprint(36,12,"POS");
		pMDU->mvprint(42,12,"1 2 3 4");

		pMDU->mvprint(17,13,"ELEV L OB");
		pMDU->mvprint(24,14,"IB");
		pMDU->mvprint(22,15,"R IB");
		pMDU->mvprint(24,16,"OB");
		pMDU->mvprint(17,17,"RUD");
		pMDU->mvprint(17,18,"SPD BRK");
		pMDU->mvprint(17,19,"BDY FLP");

		//SEC ACT SECTION
		pMDU->mvprint(37,21,"SEC ACT");
		pMDU->mvprint(36,22,"21 BYPASS");
		pMDU->mvprint(36,23,"22 RESET");


		//ACTIVE STRING HERE
		if(bFCSTestActive) {
			if(ElevonTargetIdx != FV3) pMDU->mvprint(38,9,"*");
			else pMDU->mvprint(48,9,"*");
		}


		// MODE LT
		if (ModeLT == true) pMDU->mvprint( 26, 5, "*" );
		else pMDU->mvprint( 26, 6, "*" );


		//FCS COMMAND
		char buff[16];
		PrintElevonPos(ElevonTarget, buff);
		pMDU->mvprint(28, 13, buff);
		pMDU->mvprint(28, 14, buff);
		pMDU->mvprint(28, 15, buff);
		pMDU->mvprint(28, 16, buff);
		PrintRudderPos(RudderTarget, buff);
		pMDU->mvprint(28, 17, buff);
		PrintSpeedbrakePos(SpeedbrakeTarget, buff);
		pMDU->mvprint(28, 18, buff);
		if (BodyflapDrive > 0.0) pMDU->mvprint( 31, 19, "DN" );
		else if (BodyflapDrive < 0.0) pMDU->mvprint( 31, 19, "UP" );

		//FCS ACTUAL POS
		double LOB = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
		double LIB = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
		double RIB = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
		double ROB = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
		double DRFB = ReadCOMPOOL_SS( SCP_DRFB );
		double DSBFB = ReadCOMPOOL_SS( SCP_DSBFB_PCT );
		double DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );

		PrintElevonPos( LOB, buff );
		pMDU->mvprint( 35, 13, buff );
		if (downarrow_ElevonLOB) pMDU->DownArrow( 40, 13, DEUATT_OVERBRIGHT );

		PrintElevonPos( LIB, buff );
		pMDU->mvprint( 35, 14, buff );
		if (downarrow_ElevonLIB) pMDU->DownArrow( 40, 14, DEUATT_OVERBRIGHT );

		PrintElevonPos( RIB, buff );
		pMDU->mvprint( 35, 15, buff );
		if (downarrow_ElevonRIB) pMDU->DownArrow( 40, 15, DEUATT_OVERBRIGHT );

		PrintElevonPos( ROB, buff );
		pMDU->mvprint( 35, 16, buff );
		if (downarrow_ElevonROB) pMDU->DownArrow( 40, 16, DEUATT_OVERBRIGHT );

		PrintRudderPos( DRFB, buff );
		pMDU->mvprint( 35, 17, buff );
		if (downarrow_Rudder) pMDU->DownArrow( 40, 17, DEUATT_OVERBRIGHT );

		PrintSpeedbrakePos( DSBFB, buff );
		pMDU->mvprint( 35, 18, buff );
		if (downarrow_Speedbrake) pMDU->DownArrow( 40, 18, DEUATT_OVERBRIGHT );

		sprintf_s( buff, 6, "%05.1f", range( 0.0, fabs( (DBFOFB + 11.7) * 2.919708 ), 100.0 ) );
		pMDU->mvprint( 35, 19, buff );
		return;
	}

	bool MM801::ItemInput( int item, const char* Data )
	{
		switch (item)
		{
			case 7:
				if (strlen( Data ) == 0)
				{
					ModeLT = true;
				}
				else return false;
				break;
			case 8:
				if (strlen( Data ) == 0)
				{
					ModeLT = false;
				}
				else return false;
				break;
			case 10:
				if (strlen( Data ) == 0)
				{
					bFCSTestActive = true;
					bFCSTestEnding = false;
					ElevonTargetIdx = FV1;
					RudderTargetIdx = FV1;
					SpeedbrakeTargetIdx = FV1;
					BodyflapTargetIdx = FV1;

					ElevonTarget = (ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK ) + ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK ) + ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK ) + ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK )) * 0.25;
					RudderTarget = ReadCOMPOOL_SS( SCP_DRFB );
					SpeedbrakeTarget = ReadCOMPOOL_SS( SCP_DSBFB_DEG );
					BodyflapDrive = 0.0;
				}
				else return false;
				break;
			case 11:
				if (strlen( Data ) == 0)
				{
					bFCSTestEnding = true;
					ElevonTargetIdx = FV3;
					RudderTargetIdx = FV3;
					SpeedbrakeTargetIdx = FV3;
					BodyflapTargetIdx = FV3;
					BodyflapDrive = 0.0;
				}
				else return false;
				break;
			default:
				return false;
		}
		return true;
	}

	void MM801::OnPreStep(double simt, double simdt, double mjd)
	{
		double LOB = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
		double LIB = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
		double RIB = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
		double ROB = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
		double DRFB = ReadCOMPOOL_SS( SCP_DRFB );
		double DSBFB = ReadCOMPOOL_SS( SCP_DSBFB_DEG );
		double DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );

		if (bFCSTestActive)
		{
			ElevonTarget = GetAerosurfaceCommand(ElevonTarget, simdt, ElevonTargetIdx, ELEVON_RATE, ELEVON_POSITIONS);
			WriteCOMPOOL_SS( SCP_ELOC, static_cast<float>(ElevonTarget) );
			WriteCOMPOOL_SS( SCP_ELIC, static_cast<float>(ElevonTarget) );
			WriteCOMPOOL_SS( SCP_ERIC, static_cast<float>(ElevonTarget) );
			WriteCOMPOOL_SS( SCP_EROC, static_cast<float>(ElevonTarget) );

			RudderTarget = GetAerosurfaceCommand(RudderTarget, simdt, RudderTargetIdx, RUDDER_RATE, RUDDER_POSITIONS);
			WriteCOMPOOL_SS( SCP_RUDDER_CMD, static_cast<float>(RudderTarget) );

			SpeedbrakeTarget = GetAerosurfaceCommand(SpeedbrakeTarget, simdt, SpeedbrakeTargetIdx, SPEEDBRAKE_RATE, SPEEDBRAKE_POSITIONS);
			WriteCOMPOOL_SS( SCP_SPEED_BRAKE_CMD, static_cast<float>(SpeedbrakeTarget) );

			BodyflapDrive = GetBodyflapCommand( BodyflapDrive, DBFOFB, BodyflapTargetIdx, BODYFLAP_POSITIONS );
			WriteCOMPOOL_SS( SCP_DBFRC, static_cast<float>(BodyflapDrive) );

			// if all aerosurfaces have reached their final position, set test state to inactive
			if (bFCSTestEnding)
			{
				if (Eq( LOB, ELEVON_POSITIONS[FV3], 0.01 ) &&
					Eq( LIB, ELEVON_POSITIONS[FV3], 0.01 ) &&
					Eq( RIB, ELEVON_POSITIONS[FV3], 0.01 ) &&
					Eq( ROB, ELEVON_POSITIONS[FV3], 0.01 ) &&
					Eq( DRFB, RUDDER_POSITIONS[FV3], 0.01 ) &&
					Eq( DSBFB, SPEEDBRAKE_POSITIONS[FV3], 0.001 ) &&
					BodyflapDrive == 0.0)
				{
					bFCSTestActive = false;
					bFCSTestEnding = false;
				}
			}
		}

		// test cmd vs position
		if (fabs( ElevonTarget - LOB ) > ELEVON_RATE) downarrow_ElevonLOB = true;
		else downarrow_ElevonLOB = false;

		if (fabs( ElevonTarget - LIB ) > ELEVON_RATE) downarrow_ElevonLIB = true;
		else downarrow_ElevonLIB = false;

		if (fabs( ElevonTarget - RIB ) > ELEVON_RATE) downarrow_ElevonRIB = true;
		else downarrow_ElevonRIB = false;

		if (fabs( ElevonTarget - ROB ) > ELEVON_RATE) downarrow_ElevonROB = true;
		else downarrow_ElevonROB = false;

		if (fabs( RudderTarget - DRFB ) > RUDDER_RATE) downarrow_Rudder = true;
		else downarrow_Rudder = false;

		if (fabs( SpeedbrakeTarget - DSBFB ) > SPEEDBRAKE_RATE) downarrow_Speedbrake = true;
		else downarrow_Speedbrake = false;

		if (ModeLT)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0040 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0040 );
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0010 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0010 );
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0020 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0020 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0040 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0040 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0010 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0010 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0020 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0020 );
		}
		return;
	}

	double MM801::GetAerosurfaceCommand(double curTarget, double simdt, AEROSURFACE_DRIVE_TARGET& targetIdx, const double RATE, const double* POSITIONS)
	{
		double dir = sign(POSITIONS[targetIdx] - curTarget);
		double newTarget = curTarget + dir*RATE*simdt;
		if(!Eq(dir, sign(POSITIONS[targetIdx] - newTarget))) {
			newTarget = POSITIONS[targetIdx];
			if(targetIdx == FV1) targetIdx = FV2;
			else if(targetIdx == FV2) targetIdx = FV1;
		}
		return newTarget;
	}

	double MM801::GetBodyflapCommand( double curDrive, double curPosition, AEROSURFACE_DRIVE_TARGET& targetIdx, const double* POSITIONS )
	{
		double tgtdrive = sign( POSITIONS[targetIdx] - curPosition );

		if (sign( tgtdrive * curDrive ) == -1.0)// past tgt
		{
			// switch targets...
			if (targetIdx == FV1) targetIdx = FV2;
			else if (targetIdx == FV2) targetIdx = FV1;
			else tgtdrive = 0.0;// ...stop when reached FV3
		}

		return tgtdrive;
	}

	void MM801::PrintElevonPos(double pos, char* buff) const
	{
		if(pos >= 0) sprintf_s(buff, 6, "D%04.1f",pos);
		else sprintf_s(buff, 6, "U%04.1f",-pos);
	}

	void MM801::PrintRudderPos(double pos, char* buff) const
	{
		if(pos >= 0) sprintf_s(buff, 6, "L%04.1f",pos);
		else sprintf_s(buff, 6, "R%04.1f",-pos);
	}

	void MM801::PrintSpeedbrakePos(double pos, char* buff) const
	{
		sprintf_s(buff, 6, "%05.1f", pos);
	}

	bool MM801::OnParseLine( const char* keyword, const char* value )
	{
		if(!_strnicmp( keyword, "SURF_DR", 7 ))
		{
			if (!_strnicmp( value, "ACTIVE", 6 ))
			{
				bFCSTestActive = true;
				ElevonTargetIdx = FV1;
				RudderTargetIdx = FV1;
				SpeedbrakeTargetIdx = FV1;
				BodyflapTargetIdx = FV1;
				return true;
			}
		}
		return false;
	}

	void MM801::OnSaveState( FILEHANDLE scn ) const
	{
		if (bFCSTestActive == true) oapiWriteScenario_string( scn, "SURF_DR", "ACTIVE" );
		else oapiWriteScenario_string( scn, "SURF_DR", "INACTIVE" );
	}
}
