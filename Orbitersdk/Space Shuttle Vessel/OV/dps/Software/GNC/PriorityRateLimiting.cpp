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
2022/09/16   GLS
2022/12/01   indy91
2023/11/26   GLS
2026/09/18   GLS
********************************************/
#include "PriorityRateLimiting.h"
#include <MathSSV.h>


namespace dps
{
	const double ELEVON_RATE_0 = 20.0;// elevon rate for NHSF = 0 [deg/s]
	const double RUDDER_RATE_0 = 14.0;// rudder rate for NHSF = 0 [deg/s]
	const double SPEEDBRAKE_OPEN_RATE_0 = 6.1;// speedbrake open rate for NHSF = 0 [deg/s]
	const double SPEEDBRAKE_CLOSE_RATE_0 = 10.86;// speedbrake close rate for NHSF = 0 [deg/s]


	PriorityRateLimiting::PriorityRateLimiting( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "PriorityRateLimiting" ),
		firstpass(true)
	{
		return;
	}

	PriorityRateLimiting::~PriorityRateLimiting( void )
	{
		return;
	}

	void PriorityRateLimiting::OnPostStep( double simt, double simdt, double mjd )
	{
		float DECC = ReadCOMPOOL_SS( SCP_DECC );
		float DAC = ReadCOMPOOL_SS( SCP_DAC_ );
		float DRC = ReadCOMPOOL_SS( SCP_DRC );
		float DSBC = ReadCOMPOOL_SS( SCP_DSBC );

		float LOB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_LOB_ELVN_POS_FDBK );
		float LIB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_LIB_ELVN_POS_FDBK );
		float RIB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_RIB_ELVN_POS_FDBK );
		float ROB_ELVN_POS_FDBK = ReadCOMPOOL_SS( SCP_ROB_ELVN_POS_FDBK );
		float DRFB = ReadCOMPOOL_SS( SCP_DRFB );
		float DSBFB = ReadCOMPOOL_SS( SCP_DSBOFB );

		double LH = DECC + (DAC * 0.5);
		double RH = DECC - (DAC * 0.5);
		double DLOBPC = range( max(-36.5, LOB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), LH, min(21.3, LOB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		double DLIBPC = range( max(-36.5, LIB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), LH, min(21.3, LIB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		double DRIBPC = range( max(-36.5, RIB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), RH, min(21.3, RIB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		double DROBPC = range( max(-36.5, ROB_ELVN_POS_FDBK - (simdt * ELEVON_RATE_0)), RH, min(21.3, ROB_ELVN_POS_FDBK + (simdt * ELEVON_RATE_0)) );
		WriteCOMPOOL_SS( SCP_DLOBPC, static_cast<float>(DLOBPC) );
		WriteCOMPOOL_SS( SCP_DLIBPC, static_cast<float>(DLIBPC) );
		WriteCOMPOOL_SS( SCP_DRIBPC, static_cast<float>(DRIBPC) );
		WriteCOMPOOL_SS( SCP_DROBPC, static_cast<float>(DROBPC) );

		double DRPC = range( max(-27.6, DRFB - (simdt * RUDDER_RATE_0)), DRC, min(27.6, DRFB + (simdt * RUDDER_RATE_0)) );
		WriteCOMPOOL_SS( SCP_DRPC, static_cast<float>(DRPC) );

		double DSBPC = range( max(-9.9, DSBFB - (simdt * SPEEDBRAKE_CLOSE_RATE_0)), DSBC, min(98.6, DSBFB + (simdt * SPEEDBRAKE_OPEN_RATE_0)) );
		//double SPEED_BRAKE_CMD0 = ReadCOMPOOL_SS( SCP_SPEED_BRAKE_CMD );
		WriteCOMPOOL_SS( SCP_DSBPC, static_cast<float>(DSBPC) );

		// calc speedbrake increment
		/*if (!firstpass)// HACK don't calculate in first run as it will give a big value (previous command not being saved)
			WriteCOMPOOL_SS( SCP_DSBPC, static_cast<float>(DSBC - SPEED_BRAKE_CMD0) );

		firstpass = false;*/
		return;
	}
}
