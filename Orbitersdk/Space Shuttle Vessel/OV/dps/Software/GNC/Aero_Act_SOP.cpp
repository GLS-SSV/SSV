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
2022/12/01   indy91
2026/09/18   GLS
********************************************/
#include "Aero_Act_SOP.h"
#include <MathSSV.h>


namespace dps
{
	Aero_Act_SOP::Aero_Act_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "Aero_Act_SOP" )
	{
		{// TODO fix IO
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
		}
		return;
	}

	Aero_Act_SOP::~Aero_Act_SOP( void )
	{
		return;
	}

	void Aero_Act_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		double LOB_ELVN_CMD = ReadCOMPOOL_SS( SCP_DLOBPC );
		double LIB_ELVN_CMD = ReadCOMPOOL_SS( SCP_DLIBPC );
		double RIB_ELVN_CMD = ReadCOMPOOL_SS( SCP_DRIBPC );
		double ROB_ELVN_CMD = ReadCOMPOOL_SS( SCP_DROBPC );
		float DBFRC = ReadCOMPOOL_SS( SCP_DBFRC );
		double DRPC = ReadCOMPOOL_SS( SCP_DRPC );
		double DSBPC = ReadCOMPOOL_SS( SCP_DSBPC );
		float DNWC = ReadCOMPOOL_SS( SCP_DNWC );

		LOB_ELVN_CMD = range( -36.5, LOB_ELVN_CMD, 21.3 );
		LIB_ELVN_CMD = range( -36.5, LIB_ELVN_CMD, 21.3 );
		RIB_ELVN_CMD = range( -36.5, RIB_ELVN_CMD, 21.3 );
		ROB_ELVN_CMD = range( -36.5, ROB_ELVN_CMD, 21.3 );
		ElevonLOBCommand.SetLine( static_cast<float>(((LOB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );
		ElevonLIBCommand.SetLine( static_cast<float>(((LIB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );
		ElevonRIBCommand.SetLine( static_cast<float>(((RIB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );
		ElevonROBCommand.SetLine( static_cast<float>(((ROB_ELVN_CMD + 36.5) * 5.0) / (21.3 + 36.5)) );

		DRPC = range( -27.6, DRPC, 27.6 );
		RudderCommand.SetLine( static_cast<float>(((DRPC + 27.6) * 5.0) / (27.6 + 27.6)) );

		DSBPC = range( -9.9, DSBPC, 98.6 );
		SpeedBrakeCommand.SetLine( static_cast<float>(((DSBPC + 9.9) * 5.0) / (98.6 + 9.9)) );

		// command body flap UP (-1.0) or DN (+1.0)
		BodyFlapCommand.SetLine( DBFRC );

		NWS1_CMPTR_CMD.SetLine( static_cast<float>(range( -5.0, DNWC * (5.0 / 11.2), 5.0 )) );// [-5.0v;+5.0v] [-11.2º;+11.2º]
		NWS2_CMPTR_CMD.SetLine( static_cast<float>(range( -5.0, DNWC * (5.0 / 11.2), 5.0 )) );// [-5.0v;+5.0v] [-11.2º;+11.2º]
		return;
	}
}
