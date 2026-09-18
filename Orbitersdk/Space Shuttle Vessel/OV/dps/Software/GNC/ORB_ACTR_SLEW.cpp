#include "ORB_ACTR_SLEW.h"
#include <MathSSV.h>


namespace dps
{
	// K-Loads
	constexpr unsigned short AERO_CYC = 1;// AERO SLEW COMPLETE CYCLES (V97U4181C) [cycle]
	constexpr unsigned short MPS_CYC = 1;// MPS SLEW COMPLETE CYCLES (V97U4182C) [cycle]
	constexpr unsigned short AERO_SLEW_TIME[3] = {100, 100, 100};// AERO SLEW TIME (V97U4183C, V97U4184C, V97U4185C) [cycle]
	constexpr unsigned short MPS_SLEW_TIME[3] = {125, 25, 25};// MPS SLEW TIME (V97U4186C, V97U4187C, V97U4188C) [cycle]
	constexpr unsigned short MPS_NULL_CYC = 75;// MPS SLEW NULL POSN DELAY CYCLES (V97U4194C) [cycle]
	constexpr float POSN_AERO[2] = {0.0f, 1.0f};// AERO SLEW CHECK POSN (V97U4249C, V97U4250C) [1]
	constexpr float POSN_MPS[2] = {0.0f, 1.0f};// MPS SLEW CHECK POSN (V97U4251C, V97U4252C) [1]
	constexpr unsigned short AERO_NULL_CYC = 20;// AERO SLEW NULL POSN DELAY CYCLES (V97U4253C) [cycle]
	constexpr float DELTA_MPS = 0.02f;// MPS SLEW CHECK DELTA INCREMENT (V97U4256C) [1]
	constexpr float DELTA_AERO = 0.04f;// AERO SLEW CHECK DELTA INCREMENT (V97U4257C) [1]


	ORB_ACTR_SLEW::ORB_ACTR_SLEW( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ORB_ACTR_SLEW" ),
		FP(1), AERO_I(1), MPS_I(1), cycledt(0.04)
	{
		return;
	}

	ORB_ACTR_SLEW::~ORB_ACTR_SLEW( void )
	{
		return;
	}

	void ORB_ACTR_SLEW::OnPreStep( double simt, double simdt, double mjd )
	{
		// TODO first pass
		if (FP == 1)
		{
			P = 1;// HACK added
			TRAP_CYC = 1;
			//CMD FP = 0;
			//PAUSE = 1;
			DELAY = 0;
			HOLD = 0;// HACK added
			SLEW_COMPLETE[0] = 0;
			SLEW_COMPLETE[1] = 0;
			SLEW_COMPLETE[2] = 0;
			SLEW_FLAG[0] = 0;
			SLEW_FLAG[1] = 0;
			SLEW_FLAG[2] = 0;
			SLEW_PROG = 0;

			FP = 0;
		}


		if (ReadCOMPOOL_IS( SCP_AERO_SLEW ) == 1)
		{
			SLEW_FLAG[1 - 1] = 1;
			SLEW_COMPLETE[1 - 1] = 0;
		}
		if (ReadCOMPOOL_IS( SCP_MPS_SLEW ) == 1)
		{
			SLEW_FLAG[2 - 1] = 1;
			SLEW_COMPLETE[2 - 1] = 0;
		}
		if (ReadCOMPOOL_IS( SCP_SRB_SLEW ) == 1)
		{
			//SLEW_FLAG[3 - 1] = 1;
			//SLEW_COMPLETE[3 - 1] = 0;

			WriteCOMPOOL_IS( SCP_SRB_SLEW, 0 );// HACK reset
		}

		if (SLEW_PROG == 0)
		{
			if (SLEW_FLAG[1 - 1] == 1)
			{
				SLEW_PROG = 1;
				P = 1;// AEROSURFACE SLEW PARAMETERS
			}
			else if (SLEW_FLAG[2 - 1] == 1)
			{
				SLEW_PROG = 1;
				P = 2;// MPS SLEW PARAMETERS
			}
			/*else if (SLEW_FLAG[3 - 1] == 1)
			{
				SLEW_PROG = 1;
				P = 3;// SRB SLEW PARAMETERS
			}*/
		}

		if (SLEW_PROG == 1)
		{
			if (P == 1)
			{
				float AERO_CMD = ReadCOMPOOL_SS( SCP_AERO_SLEW_CMD );
				SLEW_CHK( AERO_NULL_CYC, AERO_CYC, AERO_SLEW_TIME, POSN_AERO, DELTA_AERO, AERO_I, AERO_CMD, simdt );

				// outputs
				WriteCOMPOOL_SS( SCP_AERO_SLEW_CMD, AERO_CMD );
				if (SLEW_COMPLETE[1 - 1] == 1)
				{
					WriteCOMPOOL_IS( SCP_AERO_SLEW_CMPL, 1 );
					WriteCOMPOOL_IS( SCP_AERO_SLEW, 0 );// HACK reset
				}
				oapiWriteLogV( "AERO_CMD=%f", AERO_CMD );
			}
			else if (P == 2)
			{
				float MPS_CMD = ReadCOMPOOL_SS( SCP_MPS_SLEW_CMD );
				SLEW_CHK( MPS_NULL_CYC, MPS_CYC, MPS_SLEW_TIME, POSN_MPS, DELTA_MPS, MPS_I, MPS_CMD, simdt );

				// outputs
				WriteCOMPOOL_SS( SCP_MPS_SLEW_CMD, MPS_CMD );
				if (SLEW_COMPLETE[2 - 1] == 1)
				{
					WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, 1 );
					WriteCOMPOOL_IS( SCP_MPS_SLEW, 0 );// HACK reset
				}
				oapiWriteLogV( "MPS_CMD=%f", MPS_CMD );
			}
		}
		return;
	}

	void ORB_ACTR_SLEW::SLEW_CHK( const unsigned short NULL_CYC, const unsigned short CYC, const unsigned short* SLEW_TIME, const float* POSN, const float DELTA, unsigned short& I, float& CMD, const double dt )
	{
		// HACK handle variable sim dt
		cycledt += dt;
		if (cycledt < 0.04) return;
		unsigned short cycleincr = static_cast<unsigned short>(trunc( cycledt / 0.04 ));// number of cycles
		cycledt -= (0.04 * cycleincr);

		if (DELAY < NULL_CYC)
		{
			DELAY = DELAY + cycleincr;// HACK variable increment
			CMD = POSN[1 - 1];// HACK output first position
		}
		else
		{
			// HACK determine INCR sign from "master" index
			float INCR = DELTA * cycleincr;// HACK variable increment
			if ((I == 2) || (I == 3)) INCR = -INCR;

			// HACK determine POSN index from "master" index
			unsigned short Iposn = (I % 2 == 0) ? 1 : 2;

			if (fabs( (sign( INCR ) * POSN[Iposn - 1]) - CMD ) <= fabs( INCR ))// when increment puts cmd past posn
			{
				CMD = static_cast<float>(sign( INCR )) * POSN[Iposn - 1];

				// HACK determine SLEW_TIME index from "master" index
				unsigned short Islewtime = I;
				if (I == 3) Islewtime = 1;
				else if (I == 4) Islewtime = 3;

				// HACK changed test to allow variable increments
				if (HOLD >= SLEW_TIME[Islewtime - 1])// hold posn
				{
					I = I + 1;// next posn

					HOLD = 1;

					if (I == 5/*S*/)// end check
					{
						I = 1;

						if (TRAP_CYC == CYC)
						{
							SLEW_COMPLETE[P - 1] = 1;
							SLEW_PROG = 0;
							SLEW_FLAG[P - 1] = 0;
							DELAY = 0;
							//PAUSE = 1;
							CMD = 0;
							TRAP_CYC = 1;
							//MEi_RLIM_TF = RATE_CAPABILITY_LIFTOFF;
						}
						else
						{
							TRAP_CYC = TRAP_CYC + cycleincr;// HACK variable increment
						}
					}
				}
				else
				{
					HOLD = HOLD + cycleincr;// HACK variable increment
				}
			}
			else// cmd increment
			{
				CMD = CMD + INCR;
			}
		}
		return;
	}

	bool ORB_ACTR_SLEW::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "FP", 2 ))
		{
			sscanf_s( value, "%hu", &FP );
		}
		else if (!_strnicmp( keyword, "P", 2 ))
		{
			sscanf_s( value, "%hu", &P );
		}
		else if (!_strnicmp( keyword, "DELAY", 5 ))
		{
			sscanf_s( value, "%hu", &DELAY );
		}
		else if (!_strnicmp( keyword, "HOLD", 4 ))
		{
			sscanf_s( value, "%hu", &HOLD );
		}
		else if (!_strnicmp( keyword, "TRAP_CYC", 8 ))
		{
			sscanf_s( value, "%hu", &TRAP_CYC );
		}
		else if (!_strnicmp( keyword, "SLEW_PROG", 9 ))
		{
			sscanf_s( value, "%hu", &SLEW_PROG );
		}
		else if (!_strnicmp( keyword, "SLEW_FLAG", 9 ))
		{
			sscanf_s( value, "%hu %hu %hu", &SLEW_FLAG[0], &SLEW_FLAG[1], &SLEW_FLAG[2] );
		}
		else if (!_strnicmp( keyword, "SLEW_COMPLETE", 13 ))
		{
			sscanf_s( value, "%hu %hu %hu", &SLEW_COMPLETE[0], &SLEW_COMPLETE[1], &SLEW_COMPLETE[2] );
		}
		else if (!_strnicmp( keyword, "AERO_I", 6 ))
		{
			sscanf_s( value, "%hu", &AERO_I );
		}
		else if (!_strnicmp( keyword, "MPS_I", 5 ))
		{
			sscanf_s( value, "%hu", &MPS_I );
		}
		else return false;

		return true;
	}

	void ORB_ACTR_SLEW::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "FP", FP );
		oapiWriteScenario_int( scn, "P", P );
		oapiWriteScenario_int( scn, "DELAY", DELAY );
		oapiWriteScenario_int( scn, "HOLD", HOLD );
		oapiWriteScenario_int( scn, "TRAP_CYC", TRAP_CYC );
		oapiWriteScenario_int( scn, "SLEW_PROG", SLEW_PROG );

		char cbuf[256];
		sprintf_s( cbuf, 256, "%hu %hu %hu", SLEW_FLAG[0], SLEW_FLAG[1], SLEW_FLAG[2] );
		oapiWriteScenario_string( scn, "SLEW_FLAG", cbuf );
		sprintf_s( cbuf, 256, "%hu %hu %hu", SLEW_COMPLETE[0], SLEW_COMPLETE[1], SLEW_COMPLETE[2] );
		oapiWriteScenario_string( scn, "SLEW_COMPLETE", cbuf );

		oapiWriteScenario_int( scn, "AERO_I", AERO_I );
		oapiWriteScenario_int( scn, "MPS_I", MPS_I );
		return;
	}
}
