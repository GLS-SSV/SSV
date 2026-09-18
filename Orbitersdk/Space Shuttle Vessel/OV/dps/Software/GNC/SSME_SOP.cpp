/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/09/29   GLS
2022/10/12   GLS
2022/10/21   GLS
2022/12/23   GLS
2025/07/20   GLS
2025/01/14   GLS
2026/09/18   GLS
********************************************/
#include "SSME_SOP.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	// K-Loads
	constexpr float KPRESS[3] = {0.0, 0.0, 0.0};// (V97U4090C, V97U4091C, V97U4092C) [pct]


	SSME_SOP::SSME_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SSME_SOP" ),
		oldkcmd(0)
	{
		for (int i = 0; i < 3; i++)
		{
			DCUSwitchVDTCommand[i] = false;

			last_priTREF[i] = -1;
			last_secTREF[i] = -1;

			PrimaryDataFail[i] = false;
			SecondaryDataFail[i] = false;
			DCUProcess[i] = false;

			PrimaryFailCounter[i] = 0;
			SecondaryFailCounter[i] = 0;
			DataFailCounter[i] = 0;
		}
		return;
	}

	SSME_SOP::~SSME_SOP( void )
	{
		return;
	}

	void SSME_SOP::OnPreStep( double simt, double simdt, double mjd )
	{
		double priTREF = 0.0;
		double secTREF = 0.0;

		for (int i = 0; i < 3; i++)
		{
			// always gets previous time
			/*A data path failure occurs when the GPC’s (PASS or BFS) either do not see the main engine time reference
			word (TREF) updating or when the two main engine identification words (ID words 1 & 2) are not one’s
			complements.*/
			WriteCOMPOOL_AIS( SCP_ME_PAD_DATA_PATH_FAIL, i + 1, 0, 3 );
			switch (i)
			{
				case 0:
					priTREF = ReadCOMPOOL_AIS( SCP_EIU_1_PRIDATA, 1, 32 ) + ((double)ReadCOMPOOL_AIS( SCP_EIU_1_PRIDATA, 2, 32 ) / 10000);
					secTREF = ReadCOMPOOL_AIS( SCP_EIU_1_SECDATA, 1, 6 ) + ((double)ReadCOMPOOL_AIS( SCP_EIU_1_SECDATA, 2, 6 ) / 10000);
					break;
				case 1:
					priTREF = ReadCOMPOOL_AIS( SCP_EIU_2_PRIDATA, 1, 32 ) + ((double)ReadCOMPOOL_AIS( SCP_EIU_2_PRIDATA, 2, 32 ) / 10000);
					secTREF = ReadCOMPOOL_AIS( SCP_EIU_2_SECDATA, 1, 6 ) + ((double)ReadCOMPOOL_AIS( SCP_EIU_2_SECDATA, 2, 6 ) / 10000);
					break;
				case 2:
					priTREF = ReadCOMPOOL_AIS( SCP_EIU_3_PRIDATA, 1, 32 ) + ((double)ReadCOMPOOL_AIS( SCP_EIU_3_PRIDATA, 2, 32 ) / 10000);
					secTREF = ReadCOMPOOL_AIS( SCP_EIU_3_SECDATA, 1, 6 ) + ((double)ReadCOMPOOL_AIS( SCP_EIU_3_SECDATA, 2, 6 ) / 10000);
					break;
			}

			if (priTREF == last_priTREF[i])
			{
				if (PrimaryDataFail[i] == true)
				{
					WriteCOMPOOL_AIS( SCP_ME_PAD_DATA_PATH_FAIL, i + 1, 1, 3 );
				}
				else
				{
					PrimaryDataFail[i] = true;
				}
			}
			else
			{
				PrimaryDataFail[i] = false;
				PrimaryFailCounter[i] = 0;
			}

			if ((PrimaryDataFail[i] == true) || (ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1))// SRB not ignited
			{
				if (secTREF == last_secTREF[i])
				{
					if (SecondaryDataFail[i] == true)
					{
						WriteCOMPOOL_AIS( SCP_ME_PAD_DATA_PATH_FAIL, i + 1, 1, 3 );
					}
					else
					{
						SecondaryDataFail[i] = true;
					}
				}
				else
				{
					SecondaryDataFail[i] = false;
					SecondaryFailCounter[i] = 0;
				}

				if (PrimaryDataFail[i] == true)
				{
					if (SecondaryDataFail[i] == true)
					{
						if (DCUProcess[i] == false)
						{
							DataFailCounter[i]++;

							if (DataFailCounter[i] == 2)
							{
								// set TVC servo bypass ovrd flag
							}
							else
							{
								if (DataFailCounter[i] == 4)
								{
									DCUSwitchVDTCommand[i] = true;
									DCUProcess[i] = true;
									DataFailCounter[i] = 0;
								}
							}
						}
						else
						{
							if (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i + 1, 3 ) == 0)
							{
								DataFailCounter[i]++;

								if (DataFailCounter[i] == static_cast<int>(ReadCOMPOOL_SS( SCP_DATA_FAIL )))
								{
									WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i + 1, 1, 3 );
								}
							}
						}
					}
					else
					{
						ProcessSecData( i );
					}
				}
				else
				{
					ProcessPriData( i );
				}
			}
			else
			{
				ProcessPriData( i );
			}

			if ((PrimaryDataFail[i] == false) || (SecondaryDataFail[i] == false))
			{
				// HACK command and channel status not really perfect
				if (CommandStatus[i] == 1)// || (CommandStatus[i] == 2))
				{
					WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, i + 1, 1, 3 );
				}

				if (ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1)
				{
					if (CommandStatus[i] > 0)
					{
						if (ChannelStatus[i] != 0)
						{
							WriteCOMPOOL_AIS( SCP_ME_CHANNEL_FAIL, i + 1, 1, 3 );
						}
					}
				}

				WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, i + 1, 0, 3 );
				WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, i + 1, 0, 3 );

				switch (Phase[i])
				{
					case 4:// Mainstage
						switch (Mode[i])
						{
							case 4:// Hydraulic Lockup
								WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, i + 1, 1, 3 );
								break;
							case 5:// Electrical Lockup
								WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, i + 1, 1, 3 );
								break;
						}
						break;
					case 5:// Shutdown
						WriteCOMPOOL_AIS( SCP_MESHDN, i + 1, 1, 3 );
						break;
					case 6:// Post-Shutdown
						WriteCOMPOOL_AIS( SCP_MESHDN, i + 1, 0, 3 );
						WriteCOMPOOL_AIS( SCP_MEPSTSHDN, i + 1, 1, 3 );
						break;
					case 2:// Start-Prep
						if (Mode[i] == 5)// Engine Ready
						{
							WriteCOMPOOL_AIS( SCP_ME_READY, i + 1, 1, 3 );
						}
						else
						{
							WriteCOMPOOL_AIS( SCP_ME_READY, i + 1, 0, 3 );
						}
						break;
				}

				WriteCOMPOOL_AIS( SCP_ME_MAJOR_COMPONENT_FAIL, i + 1, 0, 3 );
				WriteCOMPOOL_AIS( SCP_ME_LIM_EX, i + 1, 0, 3 );

				if (SelfTestStatus[i] == 2)
				{
					WriteCOMPOOL_AIS( SCP_ME_MAJOR_COMPONENT_FAIL, i + 1, 1, 3 );
				}
				else if (SelfTestStatus[i] == 3)
				{
					WriteCOMPOOL_AIS( SCP_ME_LIM_EX, i + 1, 1, 3 );
				}
			}

			last_priTREF[i] = priTREF;
			last_secTREF[i] = secTREF;
		}
		return;
	}

	void SSME_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		unsigned short outputcmd;

		// HACK determine if K_CMD changed to issue new throttle command
		if (ReadCOMPOOL_IS( SCP_K_CMD ) != oldkcmd)
		{
			COMMANDED_SSME_THROTTLE_FLAG = true;
		}

		for (int i = 0; i < 3; i++)
		{
			outputcmd = 0;

			if (LastCommand[i] == STEN)
			{
				if (ReadCOMPOOL_AIS( SCP_MESTRTCMD, i + 1, 3 ) == 1)
				{
					outputcmd = IGNT;
					LastCommand[i] = IGNT;
					WriteCOMPOOL_AIS( SCP_MESTRTCMD, i + 1, 0, 3 );
					WriteCOMPOOL_IS( SCP_MESTRTENA, 0 );
				}
			}
			else
			{
				if (LastCommand[i] == SDEN)
				{
					if (ReadCOMPOOL_AIS( SCP_MESHDNCMD, i + 1, 3 ) == 1)
					{
						outputcmd = STDN;
						LastCommand[i] = STDN;
						WriteCOMPOOL_AIS( SCP_MESHDNCMD, i + 1, 0, 3 );
					}
				}
				else
				{
					if (ReadCOMPOOL_AIS( SCP_MESHDNENA, i + 1, 3 ) == 1)
					{
						outputcmd = SDEN;
						LastCommand[i] = SDEN;
						WriteCOMPOOL_AIS( SCP_MESHDNENA, i + 1, 0, 3 );
					}
					else if (DCUSwitchVDTCommand[i] == true)
					{
						outputcmd = SVRC;
						LastCommand[i] = SVRC;
						DCUSwitchVDTCommand[i] = false;
					}
					else if (ReadCOMPOOL_AIS( SCP_MPS_INH, i + 1, 3 ) == 1)
					{
						outputcmd = INLS;
						LastCommand[i] = INLS;
						WriteCOMPOOL_AIS( SCP_MPS_INH, i + 1, 0, 3 );
					}
					else if (ReadCOMPOOL_AIS( SCP_MPS_ENA, i + 1, 3 ) == 1)
					{
						outputcmd = ENLS;
						LastCommand[i] = ENLS;
						WriteCOMPOOL_AIS( SCP_MPS_ENA, i + 1, 0, 3 );
					}
					else if (COMMANDED_SSME_THROTTLE_FLAG == true)
					{
						if ((ReadCOMPOOL_IS( SCP_K_CMD ) >= MPL) && (ReadCOMPOOL_IS( SCP_K_CMD ) <= FPL))
						{
							outputcmd = THRT + (ReadCOMPOOL_IS( SCP_K_CMD ) - MPL);
							if (i == (3 - 1))
							{
								COMMANDED_SSME_THROTTLE_FLAG = false;
								oldkcmd = ReadCOMPOOL_IS( SCP_K_CMD );
							}
						}
					}
					else if (ReadCOMPOOL_IS( SCP_MESTRTENA ) == 1)
					{
						outputcmd = STEN;
						LastCommand[i] = STEN;
						if (i == (3 - 1)) WriteCOMPOOL_IS( SCP_MESTRTENA, 0 );
					}
					else if (ReadCOMPOOL_IS( SCP_MPS_LO2_DUMP_START ) == 1)
					{
						outputcmd = LOXD;
						LastCommand[i] = LOXD;
						if (i == (3 - 1)) WriteCOMPOOL_IS( SCP_MPS_LO2_DUMP_START, 0 );
					}
					else if (ReadCOMPOOL_IS( SCP_MPS_LO2_DUMP_STOP ) == 1)
					{
						outputcmd = TMSQ;
						LastCommand[i] = TMSQ;
						if (i == (3 - 1)) WriteCOMPOOL_IS( SCP_MPS_LO2_DUMP_STOP, 0 );
					}
				}
			}

			switch (i)
			{
				case 0:
					WriteCOMPOOL_IS( SCP_EIU_1_CMD, outputcmd );
					break;
				case 1:
					WriteCOMPOOL_IS( SCP_EIU_2_CMD, outputcmd );
					break;
				case 2:
					WriteCOMPOOL_IS( SCP_EIU_3_CMD, outputcmd );
					break;
			}
		}
		return;
	}

	bool SSME_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void SSME_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void SSME_SOP::ProcessPriData( int eng )
	{
		unsigned short ESW = 0;

		switch (eng)
		{
			case 0:
				WriteCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK, Round( (ReadCOMPOOL_AIS( SCP_EIU_1_PRIDATA, 6, 32 ) * ReadCOMPOOL_ASS( SCP_CPRESS, 1, 3 )) + KPRESS[0] ) );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_1_PRIDATA, 3, 32 );
				break;
			case 1:
				WriteCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK, Round( (ReadCOMPOOL_AIS( SCP_EIU_2_PRIDATA, 6, 32 ) * ReadCOMPOOL_ASS( SCP_CPRESS, 2, 3 )) + KPRESS[1] ) );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_2_PRIDATA, 3, 32 );
				break;
			case 2:
				WriteCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK, Round( (ReadCOMPOOL_AIS( SCP_EIU_3_PRIDATA, 6, 32 ) * ReadCOMPOOL_ASS( SCP_CPRESS, 3, 3 )) + KPRESS[2] ) );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_3_PRIDATA, 3, 32 );
				break;
		}

		Phase[eng] = (ESW & 0x0700) >> 8;
		Mode[eng] = (ESW & 0x3800) >> 11;
		SelfTestStatus[eng] = (ESW & 0xC000) >> 14;
		ChannelStatus[eng] = (ESW & 0x0038) >> 3;
		CommandStatus[eng] = (ESW & 0x0006) >> 1;
		return;
	}

	void SSME_SOP::ProcessSecData( int eng )
	{
		unsigned short ESW = 0;

		switch (eng)
		{
			case 0:
				WriteCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK, Round( (ReadCOMPOOL_AIS( SCP_EIU_1_SECDATA, 6, 6 ) * ReadCOMPOOL_ASS( SCP_CPRESS, 1, 3 )) + KPRESS[0] ) );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_1_SECDATA, 3, 6 );
				break;
			case 1:
				WriteCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK, Round( (ReadCOMPOOL_AIS( SCP_EIU_2_SECDATA, 6, 6 ) * ReadCOMPOOL_ASS( SCP_CPRESS, 2, 3 )) + KPRESS[1] ) );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_2_SECDATA, 3, 6 );
				break;
			case 2:
				WriteCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK, Round( (ReadCOMPOOL_AIS( SCP_EIU_3_SECDATA, 6, 6 ) * ReadCOMPOOL_ASS( SCP_CPRESS, 3, 3 )) + KPRESS[2] ) );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_3_SECDATA, 3, 6 );
				break;
		}

		Phase[eng] = (ESW & 0x0700) >> 8;
		Mode[eng] = (ESW & 0x3800) >> 11;
		SelfTestStatus[eng] = (ESW & 0xC000) >> 14;
		ChannelStatus[eng] = (ESW & 0x0038) >> 3;
		CommandStatus[eng] = (ESW & 0x0006) >> 1;
		return;
	}
}
