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
2026/09/18   GLS
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
			WriteCOMPOOL_SS( SCP_DLOBPC, static_cast<float>(ElevonTarget) );
			WriteCOMPOOL_SS( SCP_DLIBPC, static_cast<float>(ElevonTarget) );
			WriteCOMPOOL_SS( SCP_DRIBPC, static_cast<float>(ElevonTarget) );
			WriteCOMPOOL_SS( SCP_DROBPC, static_cast<float>(ElevonTarget) );

			RudderTarget = GetAerosurfaceCommand(RudderTarget, simdt, RudderTargetIdx, RUDDER_RATE, RUDDER_POSITIONS);
			WriteCOMPOOL_SS( SCP_DRPC, static_cast<float>(RudderTarget) );

			SpeedbrakeTarget = GetAerosurfaceCommand(SpeedbrakeTarget, simdt, SpeedbrakeTargetIdx, SPEEDBRAKE_RATE, SPEEDBRAKE_POSITIONS);
			WriteCOMPOOL_SS( SCP_DSBPC, static_cast<float>(SpeedbrakeTarget) );

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
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0200 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0200 );
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0800 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0800 );
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0400 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0400 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0200 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0200 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0800 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0800 );
			WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0400 );
			WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0400 );
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
