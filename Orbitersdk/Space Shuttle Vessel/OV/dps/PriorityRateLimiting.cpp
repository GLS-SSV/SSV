/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/29   GLS
2022/04/01   GLS
2022/04/02   GLS
2022/04/26   GLS
********************************************/
#include "PriorityRateLimiting.h"
#include <MathSSV.h>


namespace dps
{
	const double ELEVON_RATE_0 = 20.0;// elevon rate for NHSF = 0 [deg/s]
	const double RUDDER_RATE_0 = 14.0;// rudder rate for NHSF = 0 [deg/s]
	const double SPEEDBRAKE_OPEN_RATE_0 = 6.1;// speedbrake open rate for NHSF = 0 [deg/s]
	const double SPEEDBRAKE_CLOSE_RATE_0 = 10.86;// speedbrake close rate for NHSF = 0 [deg/s]


	PriorityRateLimiting::PriorityRateLimiting( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "PriorityRateLimiting" )
	{
		return;
	}

	PriorityRateLimiting::~PriorityRateLimiting( void )
	{
		return;
	}

	void PriorityRateLimiting::OnPostStep( double simt, double simdt, double mjd )
	{
		double DECC = ReadCOMPOOL_SD( SCP_DECC );
		double DAC = ReadCOMPOOL_SD( SCP_DAC );
		double DRC = ReadCOMPOOL_SD( SCP_DRC );
		double DSBC = ReadCOMPOOL_SD( SCP_DSBC );

		double LOB_ELVN_POS_FDBK = ReadCOMPOOL_SD( SCP_LOB_ELVN_POS_FDBK );
		double LIB_ELVN_POS_FDBK = ReadCOMPOOL_SD( SCP_LIB_ELVN_POS_FDBK );
		double RIB_ELVN_POS_FDBK = ReadCOMPOOL_SD( SCP_RIB_ELVN_POS_FDBK );
		double ROB_ELVN_POS_FDBK = ReadCOMPOOL_SD( SCP_ROB_ELVN_POS_FDBK );
		double DRFB = ReadCOMPOOL_SD( SCP_DRFB );
		double DSBFB = ReadCOMPOOL_SD( SCP_DSBFB_DEG );

		double LH = DECC + (DAC * 0.5);
		double RH = DECC - (DAC * 0.5);
		double LOB = range( max(-36.5, LOB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), LH, min(21.3, LOB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		double LIB = range( max(-36.5, LIB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), LH, min(21.3, LIB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		double RIB = range( max(-36.5, RIB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), RH, min(21.3, RIB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		double ROB = range( max(-36.5, ROB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), RH, min(21.3, ROB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		WriteCOMPOOL_SD( SCP_ELOC, static_cast<float>(LOB) );
		WriteCOMPOOL_SD( SCP_ELIC, static_cast<float>(LIB) );
		WriteCOMPOOL_SD( SCP_ERIC, static_cast<float>(RIB) );
		WriteCOMPOOL_SD( SCP_EROC, static_cast<float>(ROB) );

		DRC = range( max(-27.6, DRFB - (simdt * RUDDER_RATE_0)), DRC, min(27.6, DRFB + (simdt * RUDDER_RATE_0)) );
		WriteCOMPOOL_SD( SCP_RUDDER_CMD, static_cast<float>(DRC) );

		DSBC = range( max(-9.9, DSBFB - (simdt * SPEEDBRAKE_CLOSE_RATE_0)), DSBC, min(98.6, DSBFB + (simdt * SPEEDBRAKE_OPEN_RATE_0)) );
		double SPEED_BRAKE_CMD0 = ReadCOMPOOL_SD( SCP_SPEED_BRAKE_CMD );
		WriteCOMPOOL_SD( SCP_SPEED_BRAKE_CMD, static_cast<float>(DSBC) );

		// calc speedbrake increment
		WriteCOMPOOL_SD( SCP_DSBPC, static_cast<float>(DSBC - SPEED_BRAKE_CMD0) );
		return;
	}

	bool PriorityRateLimiting::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 304:
			case 305:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}
}