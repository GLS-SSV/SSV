/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/08/05   GLS
********************************************/
#include "Aero_Act_SOP.h"
#include <MathSSV.h>


namespace dps
{
	Aero_Act_SOP::Aero_Act_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Aero_Act_SOP" )
	{
		return;
	}

	Aero_Act_SOP::~Aero_Act_SOP( void )
	{
		return;
	}

	void Aero_Act_SOP::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AEROSURFACE_CMD", 16 );
		ElevonLOBCommand.Connect( pBundle, 0 );
		ElevonLIBCommand.Connect( pBundle, 1 );
		ElevonRIBCommand.Connect( pBundle, 2 );
		ElevonROBCommand.Connect( pBundle, 3 );
		RudderCommand.Connect( pBundle, 4 );
		SpeedBrakeCommand.Connect( pBundle, 5 );
		BodyFlapCommand.Connect( pBundle, 6 );

		pBundle = BundleManager()->CreateBundle( "NWS", 16 );
		NWS1_CMPTR_CMD.Connect( pBundle, 4 );
		NWS2_CMPTR_CMD.Connect( pBundle, 5 );
		return;
	}

	void Aero_Act_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		double LOB_ELVN_CMD = ReadCOMPOOL_SD( SCP_ELOC );
		double LIB_ELVN_CMD = ReadCOMPOOL_SD( SCP_ELIC );
		double RIB_ELVN_CMD = ReadCOMPOOL_SD( SCP_ERIC );
		double ROB_ELVN_CMD = ReadCOMPOOL_SD( SCP_EROC );
		double DBFRC = ReadCOMPOOL_SD( SCP_DBFRC );
		double RUDDER_CMD = ReadCOMPOOL_SD( SCP_RUDDER_CMD );
		double SPEED_BRAKE_CMD = ReadCOMPOOL_SD( SCP_SPEED_BRAKE_CMD );
		double DNWC = ReadCOMPOOL_SD( SCP_DNWC );

		LOB_ELVN_CMD = range( -36.5, LOB_ELVN_CMD, 21.3 );
		LIB_ELVN_CMD = range( -36.5, LIB_ELVN_CMD, 21.3 );
		RIB_ELVN_CMD = range( -36.5, RIB_ELVN_CMD, 21.3 );
		ROB_ELVN_CMD = range( -36.5, ROB_ELVN_CMD, 21.3 );
		ElevonLOBCommand.SetLine( static_cast<float>(((LOB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );
		ElevonLIBCommand.SetLine( static_cast<float>(((LIB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );
		ElevonRIBCommand.SetLine( static_cast<float>(((RIB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );
		ElevonROBCommand.SetLine( static_cast<float>(((ROB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );

		RUDDER_CMD = range( -27.6, RUDDER_CMD, 27.6 );
		RudderCommand.SetLine( static_cast<float>(((RUDDER_CMD + 27.6) * 5.0) / (27.6 + 27.6)) );

		SPEED_BRAKE_CMD = range( -9.9, SPEED_BRAKE_CMD, 98.6 );
		SpeedBrakeCommand.SetLine( static_cast<float>(((SPEED_BRAKE_CMD + 9.9) * 5.0) / (98.6 + 9.9)) );

		// command body flap UP (-1.0) or DN (+1.0)
		BodyFlapCommand.SetLine( static_cast<float>(DBFRC) );

		NWS1_CMPTR_CMD.SetLine( static_cast<float>(range( -5.0, DNWC * (5.0 / 11.2), 5.0 )) );// [-5.0v;+5.0v] [-11.2º;+11.2º]
		NWS2_CMPTR_CMD.SetLine( static_cast<float>(range( -5.0, DNWC * (5.0 / 11.2), 5.0 )) );// [-5.0v;+5.0v] [-11.2º;+11.2º]
		return;
	}

	bool Aero_Act_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}
}