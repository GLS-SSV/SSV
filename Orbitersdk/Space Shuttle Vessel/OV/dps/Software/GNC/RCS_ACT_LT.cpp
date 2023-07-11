#include "RCS_ACT_LT.h"


namespace dps
{
	// TODO I-Loads
	constexpr unsigned short NUM_MAX = 5;// (V97U6836C) [1]
	constexpr float QBAR_PITCH = 50.0f;// (V97U6858C) [lbs/ft^2]
	constexpr float QBAR_ROLL = 50.0f;// (V97U6859C) [lbs/ft^2]
	constexpr float QBAR_SAT = 50.0f;// (V97U6860C) [lbs/ft^2]


	RCS_ACT_LT::RCS_ACT_LT( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RCS_ACT_LT" )
	{
		NUM = NUM_MAX;
		EVEN_PASS_FLAG = 1;

		YL = 0;
		YR = 0;
		PD = 0;
		PU = 0;
		RL = 0;
		RR = 0;
		YAW_SAT = 0;
		RATE_SAT = 0;

		RCS_YL_LAMP = 0;
		RCS_YR_LAMP = 0;
		RCS_PD_LAMP = 0;
		RCS_PU_LAMP = 0;
		RCS_RL_LAMP = 0;
		RCS_RR_LAMP = 0;
		HUD_HYDSAT = 0;
		return;
	}

	RCS_ACT_LT::~RCS_ACT_LT( void )
	{
		return;
	}

	void RCS_ACT_LT::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short MM = ReadCOMPOOL_IS( SCP_MM );

		if ((MM == 304) || (MM == 305) || (MM == 602) || (MM == 603))
		{
			short UXCMD = ReadCOMPOOL_IS( SCP_UXCMD );
			short UYCMD = ReadCOMPOOL_IS( SCP_UYCMD );
			short UZCMD = ReadCOMPOOL_IS( SCP_UZCMD );
			float QBAR = ReadCOMPOOL_SS( SCP_QBAR );
			unsigned short RS_ELEVATOR = 0;// TODO
			unsigned short RS_AILERON = 0;// TODO

			// RCS Indicator Light Processing (25 HZ) 
			if (EVEN_PASS_FLAG == 1)
			{
				if (UZCMD < 0)
				{
					YL = 1;
				}
				else if (UZCMD > 0)
				{
					YR = 1;
				}
				if (UYCMD < 0)
				{
					PD = 1;
				}
				else if (UYCMD > 0)
				{
					PU = 1;
				}
				if (UXCMD < 0)
				{
					RL = 1;
				}
				else if (UXCMD > 0)
				{
					RR = 1;
				}
				if (abs(UZCMD) > 2)
				{
					YAW_SAT = 1;
				}
				EVEN_PASS_FLAG = 0;
			}
			else
			{
				EVEN_PASS_FLAG = 1;
			}

			if ((RS_ELEVATOR == 1) || (RS_AILERON == 1))
			{
				RATE_SAT = 1;
			}

			NUM++;
			if (NUM >= NUM_MAX)
			{
				// reset outputs
				RCS_PD_LAMP = 0;
				RCS_PU_LAMP = 0;
				RCS_RL_LAMP = 0;
				RCS_RR_LAMP = 0;
				HUD_HYDSAT = 0;

				RCS_YL_LAMP = YL;
				RCS_YR_LAMP = YR;
				if (QBAR < QBAR_PITCH)
				{
					RCS_PD_LAMP = PD;
					RCS_PU_LAMP = PU;
				}
				if (QBAR < QBAR_ROLL)
				{
					RCS_RL_LAMP = RL;
					RCS_RR_LAMP = RR;
				}
				if (QBAR > QBAR_SAT)
				{
					if (YAW_SAT == 1)
					{
						RCS_RL_LAMP = 1;
						RCS_RR_LAMP = 1;
					}
					if (RATE_SAT == 1)
					{
						RCS_PD_LAMP = 1;
						RCS_PU_LAMP = 1;
						HUD_HYDSAT = 1;
					}
				}
				YL = 0;
				YR = 0;
				PD = 0;
				PU = 0;
				RL = 0;
				RR = 0;
				YAW_SAT = 0;
				RATE_SAT = 0;
				NUM = 0;
			}
		}
		else if ((MM == 104) || (MM == 105) || (MM == 106) || (MM == 301) || (MM == 302) || (MM == 303))
		{
			float ROT_JET_CMD[3];// TODO
			ROT_JET_CMD[0] = 0.0;
			ROT_JET_CMD[1] = 0.0;
			ROT_JET_CMD[2] = 0.0;

			// RCS YAW Indicator Light Processing (12.5HZ)
			// Right Yaw Indicator Light Processing
			if (ROT_JET_CMD[2] == 1)
			{
				RCS_YR_LAMP = 1;
			}
			else
			{
				RCS_YR_LAMP = 0;
			}
			// Left Yaw Indicator Light Processing
			if (ROT_JET_CMD[2] == -1)
			{
				RCS_YL_LAMP = 1;
			}
			else
			{
				RCS_YL_LAMP = 0;
			}

			// RCS Pitch Indicator Light Processing (12.5HZ)
			// Pitch Down Indicator Light Processing
			if (ROT_JET_CMD[1] == -1)
			{
				RCS_PD_LAMP = 1;
			}
			else
			{
				RCS_PD_LAMP = 0;
			}
			// Pitch Up Indicator Light Processing
			if (ROT_JET_CMD[1] == 1)
			{
				RCS_PU_LAMP = 1;
			}
			else
			{
				RCS_PU_LAMP = 0;
			}

			// RCS Roll Indicator Light Processing (12.5HZ)
			// Left Roll Indicator Light Processing
			if (ROT_JET_CMD[0] == -1)
			{
				RCS_RL_LAMP = 1;
			}
			else
			{
				RCS_RL_LAMP = 0;
			}
			// Left Yaw Indicator Light Processing
			if (ROT_JET_CMD[0] == 1)
			{
				RCS_RR_LAMP = 1;
			}
			else
			{
				RCS_RR_LAMP = 0;
			}
		}
		else //if ((MM == 201) || (MM == 202) || (MM == 801))
		{
			float ROT_COMMAND[3];// TODO
			ROT_COMMAND[0] = 0.0;
			ROT_COMMAND[1] = 0.0;
			ROT_COMMAND[2] = 0.0;

			// RCS YAW Indicator Light Processing (12.5HZ)
			// Right Yaw Indicator Light Processing
			if (ROT_COMMAND[2] == 1)
			{
				RCS_YR_LAMP = 1;
			}
			else
			{
				RCS_YR_LAMP = 0;
			}
			// Left Yaw Indicator Light Processing
			if (ROT_COMMAND[2] == -1)
			{
				RCS_YL_LAMP = 1;
			}
			else
			{
				RCS_YL_LAMP = 0;
			}

			// RCS Pitch Indicator Light Processing (12.5HZ)
			// Pitch Down Indicator Light Processing
			if (ROT_COMMAND[1] == -1)
			{
				RCS_PD_LAMP = 1;
			}
			else
			{
				RCS_PD_LAMP = 0;
			}
			// Pitch Up Indicator Light Processing
			if (ROT_COMMAND[1] == 1)
			{
				RCS_PU_LAMP = 1;
			}
			else
			{
				RCS_PU_LAMP = 0;
			}

			// RCS Roll Indicator Light Processing (12.5HZ)
			// Left Roll Indicator Light Processing
			if (ROT_COMMAND[0] == -1)
			{
				RCS_RL_LAMP = 1;
			}
			else
			{
				RCS_RL_LAMP = 0;
			}
			// Left Yaw Indicator Light Processing
			if (ROT_COMMAND[0] == 1)
			{
				RCS_RR_LAMP = 1;
			}
			else
			{
				RCS_RR_LAMP = 0;
			}
		}


		// output
		if (RCS_YL_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0200 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0200 );
		}
		if (RCS_YR_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0400 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0400 );
		}

		if (RCS_PD_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x1000 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x1000 );
		}
		if (RCS_PU_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0800 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0800 );
		}

		if (RCS_RL_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0080 );
		}
		if (RCS_RR_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0100 );
		}

		// HUD
		WriteCOMPOOL_IS( SCP_HUD_HYDSAT, HUD_HYDSAT );
		return;
	}

	bool RCS_ACT_LT::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 104:
			case 105:
			case 106:
			case 201:
			case 202:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 602:
			case 603:
			case 801:
				return true;
			default:
				return false;
		}
	}

	bool RCS_ACT_LT::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short tmp = 0;
		if (!_stricmp( keyword, "NUM" ))
		{
			sscanf_s( value, "%hu", &NUM );
			return true;
		}
		else if (!_stricmp( keyword, "EVEN_PASS_FLAG" ))
		{
			sscanf_s( value, "%hu", &tmp );
			EVEN_PASS_FLAG = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "YL" ))
		{
			sscanf_s( value, "%hu", &tmp );
			YL = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "YR" ))
		{
			sscanf_s( value, "%hu", &tmp );
			YR = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "PD" ))
		{
			sscanf_s( value, "%hu", &tmp );
			PD = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "PU" ))
		{
			sscanf_s( value, "%hu", &tmp );
			PU = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RL" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RL = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RR" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RR = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "YAW_SAT" ))
		{
			sscanf_s( value, "%hu", &tmp );
			YAW_SAT = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RATE_SAT" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RATE_SAT = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RCS_YL_LAMP" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RCS_YL_LAMP = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RCS_YR_LAMP" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RCS_YR_LAMP = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RCS_PD_LAMP" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RCS_PD_LAMP = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RCS_PU_LAMP" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RCS_PU_LAMP = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RCS_RL_LAMP" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RCS_RL_LAMP = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "RCS_RR_LAMP" ))
		{
			sscanf_s( value, "%hu", &tmp );
			RCS_RR_LAMP = (tmp == 1) ? 1 : 0;
			return true;
		}
		else if (!_stricmp( keyword, "HUD_HYDSAT" ))
		{
			sscanf_s( value, "%hu", &tmp );
			HUD_HYDSAT = (tmp == 1) ? 1 : 0;
			return true;
		}
		return false;
	}

	void RCS_ACT_LT::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "NUM", NUM );
		oapiWriteScenario_int( scn, "EVEN_PASS_FLAG", EVEN_PASS_FLAG );
		oapiWriteScenario_int( scn, "YL", YL );
		oapiWriteScenario_int( scn, "YR", YR );
		oapiWriteScenario_int( scn, "PD", PD );
		oapiWriteScenario_int( scn, "PU", PU );
		oapiWriteScenario_int( scn, "RL", RL );
		oapiWriteScenario_int( scn, "RR", RR );
		oapiWriteScenario_int( scn, "YAW_SAT", YAW_SAT );
		oapiWriteScenario_int( scn, "RATE_SAT", RATE_SAT );
		oapiWriteScenario_int( scn, "RCS_YL_LAMP", RCS_YL_LAMP );
		oapiWriteScenario_int( scn, "RCS_YR_LAMP", RCS_YR_LAMP );
		oapiWriteScenario_int( scn, "RCS_PD_LAMP", RCS_PD_LAMP );
		oapiWriteScenario_int( scn, "RCS_PU_LAMP", RCS_PU_LAMP );
		oapiWriteScenario_int( scn, "RCS_RL_LAMP", RCS_RL_LAMP );
		oapiWriteScenario_int( scn, "RCS_RR_LAMP", RCS_RR_LAMP );
		oapiWriteScenario_int( scn, "HUD_HYDSAT", HUD_HYDSAT );
		return;
	}
}
