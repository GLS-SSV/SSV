#include "RCS_ACT_LT.h"


namespace dps
{
	RCS_ACT_LT::RCS_ACT_LT( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "RCS_ACT_LT" )
	{
		NUM = ReadCOMPOOL_IS( SCP_NUM_MAX );
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
		unsigned short MM_CODE_104 = ReadCOMPOOL_IS( SCP_MM_CODE_104 );
		unsigned short MM_CODE_105 = ReadCOMPOOL_IS( SCP_MM_CODE_105 );
		unsigned short MM_CODE_106 = ReadCOMPOOL_IS( SCP_MM_CODE_106 );
		unsigned short MM_CODE_301 = ReadCOMPOOL_IS( SCP_MM_CODE_301 );
		unsigned short MM_CODE_302 = ReadCOMPOOL_IS( SCP_MM_CODE_302 );
		unsigned short MM_CODE_303 = ReadCOMPOOL_IS( SCP_MM_CODE_303 );
		unsigned short MM_CODE_304 = ReadCOMPOOL_IS( SCP_MM_CODE_304 );
		unsigned short MM_CODE_305 = ReadCOMPOOL_IS( SCP_MM_CODE_305 );
		unsigned short MM_CODE_602 = ReadCOMPOOL_IS( SCP_MM_CODE_602 );
		unsigned short MM_CODE_603 = ReadCOMPOOL_IS( SCP_MM_CODE_603 );

		if ((MM_CODE_304 == 1) || (MM_CODE_305 == 1) || (MM_CODE_602 == 1) || (MM_CODE_603 == 1))
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
			if (NUM >= ReadCOMPOOL_IS( SCP_NUM_MAX ))
			{
				// reset outputs
				RCS_PD_LAMP = 0;
				RCS_PU_LAMP = 0;
				RCS_RL_LAMP = 0;
				RCS_RR_LAMP = 0;
				HUD_HYDSAT = 0;

				RCS_YL_LAMP = YL;
				RCS_YR_LAMP = YR;
				if (QBAR < ReadCOMPOOL_SS( SCP_QBAR_PITCH ))
				{
					RCS_PD_LAMP = PD;
					RCS_PU_LAMP = PU;
				}
				if (QBAR < ReadCOMPOOL_SS( SCP_QBAR_ROLL ))
				{
					RCS_RL_LAMP = RL;
					RCS_RR_LAMP = RR;
				}
				if (QBAR > ReadCOMPOOL_SS( SCP_QBAR_SAT ))
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
		else if ((MM_CODE_104 == 1) || (MM_CODE_105 == 1) || (MM_CODE_106 == 1) || (MM_CODE_301 == 1) || (MM_CODE_302 == 1) || (MM_CODE_303 == 1))
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
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0040 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0040 );
		}
		if (RCS_YR_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0020 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0020 );
		}

		if (RCS_PD_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0008 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0008 );
		}
		if (RCS_PU_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0010 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0010 );
		}

		if (RCS_RL_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0100 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0100 );
		}
		if (RCS_RR_LAMP)
		{
			WriteCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH1_DATA ) | 0x0080 );
			WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | 0x0080 );
		}

		// HUD
		WriteCOMPOOL_IS( SCP_HUD_HYDSAT, HUD_HYDSAT );
		return;
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
