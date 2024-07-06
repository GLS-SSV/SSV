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
2022/12/23   GLS
2023/11/26   GLS
2024/07/06   GLS
********************************************/
#include "MM801.h"
#include "../CRT_Interface.h"
#include "../../../Atlantis.h"
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

	void MM801::OnPaint( CRT_Interface* crt ) const
	{
		//ACTIVE STRING HERE
		if(bFCSTestActive) {
			if(ElevonTargetIdx != FV3) crt->TextGrid( 39, 10, "*" );
			else crt->TextGrid( 49, 10, "*" );
		}


		// MODE LT
		if (ModeLT == true) crt->TextGrid( 27, 6, "*" );
		else crt->TextGrid( 27, 7, "*" );


		//FCS COMMAND
		char buff[16];
		PrintElevonPos( ElevonTarget, buff );
		crt->TextGrid( 29, 14, buff );
		crt->TextGrid( 29, 15, buff );
		crt->TextGrid( 29, 16, buff );
		crt->TextGrid( 29, 17, buff );
		PrintRudderPos( RudderTarget, buff );
		crt->TextGrid( 29, 18, buff );
		PrintSpeedbrakePos( SpeedbrakeTarget, buff );
		crt->TextGrid( 29, 19, buff );
		if (BodyflapDrive > 0.0) crt->TextGrid( 32, 20, "DN" );
		else if (BodyflapDrive < 0.0) crt->TextGrid( 32, 20, "UP" );

		//FCS ACTUAL POS
		double LOB = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
		double LIB = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
		double RIB = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
		double ROB = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
		double DRFB = ReadCOMPOOL_SS( SCP_DRFB );
		double DSBFB = ReadCOMPOOL_SS( SCP_DSBFBP );
		double DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );

		PrintElevonPos( LOB, buff );
		crt->TextGrid( 36, 14, buff );
		if (downarrow_ElevonLOB) crt->TextGrid( 41, 14, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintElevonPos( LIB, buff );
		crt->TextGrid( 36, 15, buff );
		if (downarrow_ElevonLIB) crt->TextGrid( 41, 15, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintElevonPos( RIB, buff );
		crt->TextGrid( 36, 16, buff );
		if (downarrow_ElevonRIB) crt->TextGrid( 41, 16, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintElevonPos( ROB, buff );
		crt->TextGrid( 36, 17, buff );
		if (downarrow_ElevonROB) crt->TextGrid( 41, 17, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintRudderPos( DRFB, buff );
		crt->TextGrid( 36, 18, buff );
		if (downarrow_Rudder) crt->TextGrid( 41, 18, "\x1D", crt->DEUATT_OVERBRIGHT );

		PrintSpeedbrakePos( DSBFB, buff );
		crt->TextGrid( 36, 19, buff );
		if (downarrow_Speedbrake) crt->TextGrid( 41, 19, "\x1D", crt->DEUATT_OVERBRIGHT );

		sprintf_s( buff, 6, "%05.1f", range( 0.0, fabs( (DBFOFB + 11.7) * 2.919708 ), 100.0 ) );
		crt->TextGrid( 36, 20, buff );
		return;
	}

	void MM801::BackgroundData( CRT_Interface* crt ) const
	{
		// title
		crt->TextGrid( 17, 1, "FCS/DED DIS C/O" );

		// DED DIS
		crt->TextGrid( 3, 5, "DED DIS" );
		crt->TextGrid( 2, 6, "FWD 1" );
		crt->TextGrid( 2, 7, "AFT 2" );
		crt->TextGrid( 10, 6, "HIGH 3" );
		crt->TextGrid( 10, 7, "LOW  4" );
		crt->TextGrid( 10, 8, "FLAG 5" );
		crt->TextGrid( 10, 9, "OFF  6" );

		// BODY FLP DES
		crt->TextGrid( 3, 11, "BODY FLP DES" );
		crt->TextGrid( 2, 12, "VLV" );
		crt->TextGrid( 6, 12, "1" );
		crt->TextGrid( 6, 13, "2" );
		crt->TextGrid( 6, 14, "3" );
		crt->TextGrid( 12, 12, "12" );
		crt->TextGrid( 12, 13, "13" );
		crt->TextGrid( 12, 14, "14" );

		// SEC ACT CK
		crt->TextGrid( 3, 16, "SEC ACT CK" );
		crt->TextGrid( 2, 17, "CH 1" );
		crt->TextGrid( 8, 17, "15" );
		crt->TextGrid( 2, 18, "CH 2" );
		crt->TextGrid( 8, 18, "16" );
		crt->TextGrid( 2, 19, "CH 3" );
		crt->TextGrid( 8, 19, "17" );
		crt->TextGrid( 2, 20, "CH 4" );
		crt->TextGrid( 8, 20, "18" );
		crt->TextGrid( 2, 21, "STOP" );
		crt->TextGrid( 8, 21, "19" );
		crt->TextGrid( 2, 22, "POS STIM" );
		crt->TextGrid( 4, 23, "ENA 20" );

		// MODE LT
		crt->TextGrid( 22, 5, "MODE" );
		crt->TextGrid( 27, 5, "LT" );
		crt->TextGrid( 21, 6, "ON" );
		crt->TextGrid( 26, 6, "7" );
		crt->TextGrid( 21, 7, "OFF  8" );

		// AVG G ON
		crt->TextGrid( 37, 5, "AVG G" );
		crt->TextGrid( 44, 5, "ON" );
		crt->TextGrid( 48, 5, "9" );

		// SURF DR
		crt->TextGrid( 22, 10, "SURF" );
		crt->TextGrid( 27, 10, "DR" );
		crt->TextGrid( 31, 10, "START 10" );
		crt->TextGrid( 42, 10, "STOP" );
		crt->TextGrid( 47, 10, "11" );

		crt->TextGrid( 19, 13, "SURF" );
		crt->TextGrid( 30, 13, "CMD" );
		crt->TextGrid( 37, 13, "POS" );
		crt->TextGrid( 43, 13, "1 2 3 4" );

		crt->TextGrid( 18, 14, "ELEV" );
		crt->TextGrid( 23, 14, "L OB" );
		crt->TextGrid( 25, 15, "IB" );
		crt->TextGrid( 23, 16, "R IB" );
		crt->TextGrid( 25, 17, "OB" );
		crt->TextGrid( 18, 18, "RUD" );
		crt->TextGrid( 18, 19, "SPD BRK" );
		crt->TextGrid( 18, 20, "BDY FLP" );

		// SEC ACT
		crt->TextGrid( 38, 22, "SEC ACT" );
		crt->TextGrid( 37, 23, "21" );
		crt->TextGrid( 48, 23, "\x7D\x7D" );
		crt->TextGrid( 40, 23, "BYPASS" );
		crt->TextGrid( 37, 24, "22 RESET" );
		crt->TextGrid( 48, 24, "\x7D\x7D" );
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
					SpeedbrakeTarget = ReadCOMPOOL_SS( SCP_DSBOFB );
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
		double DSBFB = ReadCOMPOOL_SS( SCP_DSBOFB );
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
