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
********************************************/
#include "SSME_SOP.h"
#include "..\Atlantis.h"
#include <MathSSV.h>
#include <cassert>


namespace dps
{
	SSME_SOP::SSME_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SSME_SOP" )
	{
		StartEnableCommand = false;

		for (int i = 0; i < 3; i++)
		{
			EngineStartCommand[i] = false;
			ShutdownEnableCommand[i] = false;
			ShutdownCommand[i] = false;
			ThrottleCommand[i] = false;
			OxidizerDumpStartCommand[i] = false;
			DumpStopCommand[i] = false;
			LimitInhibitCommand[i] = false;
			LimitEnableCommand[i] = false;
			DCUSwitchVDTCommand[i] = false;

			ShutdownEnableCommandIssued[i] = false;

			PadDataPathFailure[i] = false;
			MajorComponentFailure[i] = false;
			ChannelFailure[i] = false;

			last_priTREF[i] = -1;
			last_secTREF[i] = -1;

			PrimaryDataFail[i] = false;
			SecondaryDataFail[i] = false;
			DCUProcess[i] = false;

			PrimaryFailCounter[i] = 0;
			SecondaryFailCounter[i] = 0;
			DataFailCounter[i] = 0;
		}

		// I-LOADs init
		CPRESS[0] = 0.0364062;
		CPRESS[1] = 0.0364062;
		CPRESS[2] = 0.0364062;
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
			PadDataPathFailure[i] = false;
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
					PadDataPathFailure[i] = true;
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

			if ((PrimaryDataFail[i] == true) || (GetMajorMode() == 101))// SRB not ignited
			{
				if (secTREF == last_secTREF[i])
				{
					if (SecondaryDataFail[i] == true)
					{
						PadDataPathFailure[i] = true;
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

								if (DataFailCounter[i] == DATA_FAIL)
								{
									PercentChamberPress[i] = 0;// so it displays 0 on data path failure
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

				if (GetMajorMode() == 101)
				{
					if (CommandStatus[i] > 0)
					{
						if (ChannelStatus[i] != 0)
						{
							ChannelFailure[i] = true;
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

				MajorComponentFailure[i] = false;
				WriteCOMPOOL_AIS( SCP_ME_LIM_EX, i + 1, 0, 3 );

				if (SelfTestStatus[i] == 2)
				{
					MajorComponentFailure[i] = true;
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

		for (int i = 0; i < 3; i++)
		{
			outputcmd = 0;

			if (LastCommand[i] == STEN)
			{
				if (EngineStartCommand[i] == true)
				{
					outputcmd = IGNT;
					LastCommand[i] = IGNT;
					EngineStartCommand[i] = false;
					StartEnableCommand = false;// it appears one flag works for all 3 engines
				}
			}
			else
			{
				if (LastCommand[i] == SDEN)
				{
					if (ShutdownCommand[i] == true)
					{
						outputcmd = STDN;
						LastCommand[i] = STDN;
						ShutdownCommand[i] = false;
						ShutdownEnableCommandIssued[i] = false;
					}
				}
				else
				{
					if (ShutdownEnableCommand[i] == true)
					{
						outputcmd = SDEN;
						LastCommand[i] = SDEN;
						ShutdownEnableCommand[i] = false;
						ShutdownEnableCommandIssued[i] = true;
					}
					else if (DCUSwitchVDTCommand[i] == true)
					{
						outputcmd = SVRC;
						LastCommand[i] = SVRC;
						DCUSwitchVDTCommand[i] = false;
					}
					else if (LimitInhibitCommand[i] == true)
					{
						outputcmd = INLS;
						LastCommand[i] = INLS;
						LimitInhibitCommand[i] = false;
					}
					else if (LimitEnableCommand[i] == true)
					{
						outputcmd = ENLS;
						LastCommand[i] = ENLS;
						LimitEnableCommand[i] = false;
					}
					else if (ThrottleCommand[i] == true)
					{
						outputcmd = THRT + (CommandedThrottle - MPL);
						ThrottleCommand[i] = false;
					}
					else if (StartEnableCommand == true)
					{
						outputcmd = STEN;
						LastCommand[i] = STEN;
					}
					else if (OxidizerDumpStartCommand[i] == true)
					{
						outputcmd = LOXD;
						LastCommand[i] = LOXD;
						OxidizerDumpStartCommand[i] = false;
					}
					else if (DumpStopCommand[i] == true)
					{
						outputcmd = TMSQ;
						LastCommand[i] = TMSQ;
						DumpStopCommand[i] = false;
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

	bool SSME_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	void SSME_SOP::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "CPRESS", ILOADs, 3, CPRESS );
		return;
	}

	void SSME_SOP::ProcessPriData( int eng )
	{
		unsigned short ESW = 0;

		switch (eng)
		{
			case 0:
				PercentChamberPress[eng] = Round( ReadCOMPOOL_AIS( SCP_EIU_1_PRIDATA, 6, 32 ) * CPRESS[0] );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_1_PRIDATA, 3, 32 );
				break;
			case 1:
				PercentChamberPress[eng] = Round( ReadCOMPOOL_AIS( SCP_EIU_2_PRIDATA, 6, 32 ) * CPRESS[1] );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_2_PRIDATA, 3, 32 );
				break;
			case 2:
				PercentChamberPress[eng] = Round( ReadCOMPOOL_AIS( SCP_EIU_3_PRIDATA, 6, 32 ) * CPRESS[2] );
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
				PercentChamberPress[eng] = Round( ReadCOMPOOL_AIS( SCP_EIU_1_SECDATA, 6, 6 ) * CPRESS[0] );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_1_SECDATA, 3, 6 );
				break;
			case 1:
				PercentChamberPress[eng] = Round( ReadCOMPOOL_AIS( SCP_EIU_2_SECDATA, 6, 6 ) * CPRESS[1] );
				ESW = ReadCOMPOOL_AIS( SCP_EIU_2_SECDATA, 3, 6 );
				break;
			case 2:
				PercentChamberPress[eng] = Round( ReadCOMPOOL_AIS( SCP_EIU_3_SECDATA, 6, 6 ) * CPRESS[2] );
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

	void SSME_SOP::SetStartEnableCommandFlag( void )
	{
		StartEnableCommand = true;
		return;
	}

	void SSME_SOP::SetEngineStartCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetEngineStartCommandFlag.eng" );
		EngineStartCommand[eng - 1] = true;
		return;
	}

	void SSME_SOP::SetShutdownEnableCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetShutdownEnableCommandFlag.eng" );
		ShutdownEnableCommand[eng - 1] = true;
		return;
	}

	void SSME_SOP::ResetShutdownEnableCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetShutdownEnableCommandFlag.eng" );
		ShutdownEnableCommand[eng - 1] = false;
		return;
	}

	void SSME_SOP::SetShutdownCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetShutdownCommandFlag.eng" );
		ShutdownCommand[eng - 1] = true;
		return;
	}

	void SSME_SOP::ResetShutdownCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetShutdownCommandFlag.eng" );
		ShutdownCommand[eng - 1] = false;
		return;
	}

	bool SSME_SOP::SetThrottlePercent( unsigned short pct )
	{
		if ((pct < MPL) || (pct > FPL)) return false;

		CommandedThrottle = pct;
		ThrottleCommand[0] = true;
		ThrottleCommand[1] = true;
		ThrottleCommand[2] = true;
		return true;
	}

	void SSME_SOP::SetLimitInhibitCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetLimitInhibitCommandFlag.eng" );
		LimitInhibitCommand[eng - 1] = true;
		return;
	}

	void SSME_SOP::SetLimitEnableCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetLimitEnableCommandFlag.eng" );
		LimitEnableCommand[eng - 1] = true;
		return;
	}

	void SSME_SOP::SetOxidizerDumpStartCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetOxidizerDumpStartCommandFlag.eng" );
		OxidizerDumpStartCommand[eng - 1] = true;
		return;
	}

	void SSME_SOP::SetDumpStopCommandFlag( int eng )
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::SetDumpStopCommandFlag.eng" );
		DumpStopCommand[eng - 1] = true;
		return;
	}

	bool SSME_SOP::GetShutdownEnableCommandIssuedFlag( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::GetShutdownEnableCommandIssuedFlag.eng" );
		return ShutdownEnableCommandIssued[eng - 1];
	}

	bool SSME_SOP::GetPadDataPathFailureFlag( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::GetPadDataPathFailureFlag.eng" );
		return PadDataPathFailure[eng - 1];
	}

	bool SSME_SOP::GetMajorComponentFailureFlag( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::GetMajorComponentFailureFlag.eng" );
		return MajorComponentFailure[eng - 1];
	}

	bool SSME_SOP::GetChannelFailureFlag( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::GetChannelFailureFlag.eng" );
		return ChannelFailure[eng - 1];
	}

	unsigned short SSME_SOP::GetPercentChamberPressVal( int eng ) const
	{
		assert( (eng >= 1) && (eng <= 3) && "SSME_SOP::GetPercentChamberPressVal.eng" );
		return PercentChamberPress[eng - 1];
	}
}