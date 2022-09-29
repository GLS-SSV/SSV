/******* SSV File Modification Notice *******
Date         Developer
2020/03/25   GLS
2020/04/01   GLS
2020/05/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/25   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/07/03   GLS
2020/07/30   GLS
2020/08/22   GLS
2020/08/23   GLS
2020/08/24   GLS
2020/08/29   GLS
2020/09/20   GLS
2020/10/03   GLS
2020/10/06   GLS
2020/10/10   GLS
2021/01/19   GLS
2021/01/20   GLS
2021/06/13   GLS
2021/06/15   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/11/13   GLS
2021/11/27   GLS
2021/12/05   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/11   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/02/05   GLS
2022/02/07   GLS
2022/02/25   GLS
2022/03/01   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/05/01   GLS
2022/06/19   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "Mission.h"
#include <OrbiterAPI.h>
#include <UtilsSSV.h>
#include "../ParameterValues.h"
#include <limits>
#include <vector>
#include <cassert>


namespace mission
{
	Mission::Mission(const std::string& strMission)
	{
		memset( &payloads, 0, sizeof(MissionPayloads) );

		Stbd_PayloadMPM.attachment = 0;
		Stbd_PayloadMPM.Shoulder.IsUsed = false;
		Stbd_PayloadMPM.Forward.IsUsed = false;
		Stbd_PayloadMPM.Mid.IsUsed = false;
		Stbd_PayloadMPM.Aft.IsUsed = false;

		SetDefaultValues();
		if (!strMission.empty())
		{
			if (!LoadMissionFile( strMission ))
			{
				oapiWriteLog( "(SSV_OV) [INFO] Loaded default mission." );
			}
		}
		else oapiWriteLog( "(SSV_OV) [INFO] Loaded default mission." );
	}

	Mission::~Mission()
	{
	}

	void Mission::SetDefaultValues( void )
	{
		// STS-101 params
		fTargetInc = 51.62 * RAD;
		fMECOAlt = 105564;
		fMECOVel = 7903.449390;
		fMECOFPA = 0.708380 * RAD;

		// default to Atlantis
		strOrbiter = "Atlantis";
		OVmass = ORBITER_EMPTY_MASS_OV104;

		/////////////////////////////////////////
		// the following options must be false by default, as their panels and/or subsystems are only created if a mission file is specified
		PortLongeronSill = None;
		StbdLongeronSill = None;
		bHasKUBand = false;
		bHasExtALODSKit = true;
		bHasODS = false;
		bHasExtAL = false;
		bHasTAA = false;
		bAftTAA = false;
		bUseASE_IUS = false;
		bUseCISS = false;
		bHasDragChute = false;
		/////////////////////////////////////////
		bASE_IUS_Aft_Location = false;
		bCISS_GPrime = true;

		bHasPLBLiner = false;

		bHasDFIWireTray = false;

		bHasBulkheadFloodlights = true;

		bHasVentDoors4and7 = false;

		bUseSILTS = false;

		InternalPRSDTankSets = 5;
		bHasEDOKit = true;
		EDOPallet = 0;

		bHasOMSKit = false;

		strLandingSiteTable = "1,KSC15,KSC33" + std::string( "\r\n" ) +
				"2,BEN36,BEN18" + std::string( "\r\n" ) +
				"3,MRN20,MRN02" + std::string( "\r\n" ) +
				"4,ZZA30L,ZZA12R" + std::string( "\r\n" ) +
				"5,MYR36,MYR18" + std::string( "\r\n" ) +
				"6,ILM06,ILM24" + std::string( "\r\n" ) +
				"7,NKT32L,NKT23R" + std::string( "\r\n" ) +
				"8,NTU32R,NTU23L" + std::string( "\r\n" ) +
				"9,WAL28,WAL04" + std::string( "\r\n" ) +
				"10,DOV32,DOV19" + std::string( "\r\n" ) +
				"11,ACY31,ACY13" + std::string( "\r\n" ) +
				"12,BEN36,BEN18" + std::string( "\r\n" ) +
				"13,MRN20,MRN02" + std::string( "\r\n" ) +
				"14,ZZA30L,ZZA12R" + std::string( "\r\n" ) +
				"15,FOK06,FOK24" + std::string( "\r\n" ) +
				"16,FMH32,FMH23" + std::string( "\r\n" ) +
				"17,PSM34,PSM16" + std::string( "\r\n" ) +
				"18,YHZ23,YHZ32" + std::string( "\r\n" ) +
				"19,YJT09,YJT27" + std::string( "\r\n" ) +
				"20,YYT29,YYT11" + std::string( "\r\n" ) +
				"21,YQX21,YQX31" + std::string( "\r\n" ) +
				"22,BYD32,BYD14" + std::string( "\r\n" ) +
				"23,LAJ15,LAJ33" + std::string( "\r\n" ) +
				"24,VBG30,VBG12" + std::string( "\r\n" ) +
				"25,IKF20,IKF29" + std::string( "\r\n" ) +
				"26,INN06,INN24" + std::string( "\r\n" ) +
				"27,FFA27,FFA09" + std::string( "\r\n" ) +
				"28,KBO14L,KBO32R" + std::string( "\r\n" ) +
				"29,FMI33,FMI15" + std::string( "\r\n" ) +
				"30,ESN03R,ESN21L" + std::string( "\r\n" ) +
				"31,KKI15R,KKI33L" + std::string( "\r\n" ) +
				"32,JDG31,JDG13" + std::string( "\r\n" ) +
				"33,AMB15,PTN14" + std::string( "\r\n" ) +
				"34,JTY36,JTY18" + std::string( "\r\n" ) +
				"35,GUA06L,GUA24R" + std::string( "\r\n" ) +
				"36,BDA30,BDA12" + std::string( "\r\n" ) +
				"37,HNL08R,HNL26L" + std::string( "\r\n" ) +
				"38,EIP28,EIP10" + std::string( "\r\n" ) +
				"39,HAO12,HAO30" + std::string( "\r\n" ) +
				"40,AWG25,AWG07" + std::string( "\r\n" ) +
				"41,HAW31,HAW13" + std::string( "\r\n" ) +
				"42,NOR17,NOR23" + std::string( "\r\n" ) +
				"43,NOR05,NOR35" + std::string( "\r\n" ) +
				"44,EDW15,EDW18L" + std::string( "\r\n" ) +
				"45,EDW22,EDW04";

		PLBDHingeFairings = 2;
		ChinPanel = true;

		Crew = 7;
		Galley = 2;
		SleepStations = 0;
		EjectionSeats = false;
		CrewEscapeHardware = true;
		MEDSFlightDeck = true;
	}

	bool Mission::LoadMissionFile( const std::string& strMission )
	{
		std::string filename;
		filename = "Missions\\SSV\\" + strMission + ".json";
		strFileName = strMission;

		FILE* hF = fopen( filename.c_str(), "r" );
		if (hF == NULL)
		{
			oapiWriteLogV( "(SSV_OV) [ERROR] Can't open mission file %s", strMission.c_str() );
			return false;
		}

		oapiWriteLogV( "(SSV_OV) [INFO] Loading mission file %s", filename.c_str() );

		fseek( hF, 0, SEEK_END );
		long filesize = ftell( hF );
		if (filesize < 0)
		{
			fclose( hF );
			return false;
		}

		char* missionfilestr = new char[filesize];
		rewind( hF );
		fread( missionfilestr, sizeof(char), filesize, hF );
		fclose( hF );

		cJSON* root = cJSON_Parse( missionfilestr );
		if (!root)
		{
			oapiWriteLog( "(SSV_OV) [ERROR] Error parsing mission file version" );
			delete[] missionfilestr;
			return false;
		}

		cJSON* version = cJSON_GetObjectItemCaseSensitive( root, "Version" );
		switch (version->valueint)
		{
			case 1:
				LoadMissionV1( root );
				break;
			default:
				oapiWriteLogV( "(SSV_OV) [ERROR] Unknown mission file version %s", version->valueint );
				cJSON_Delete( root );
				delete[] missionfilestr;
				return false;
		}

		cJSON_Delete( root );
		delete[] missionfilestr;
		return true;
	}

	void Mission::LoadMissionV1( cJSON* root )
	{
		// Orbiter Vehicle
		cJSON* ov = cJSON_GetObjectItemCaseSensitive( root, "Orbiter Vehicle" );
		if (ov)
		{
			cJSON* tmp = cJSON_GetObjectItemCaseSensitive( ov, "Name" );
			if (!strcmp( "Columbia", tmp->valuestring ))
			{
				strOrbiter = "Columbia";
				OVmass = ORBITER_EMPTY_MASS_OV102;
				strOrbiterTexName = "SSV\\OV\\OV-102_8thmod.dds";
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "Challenger", tmp->valuestring ))
			{
				strOrbiter = "Challenger";
				OVmass = ORBITER_EMPTY_MASS_OV099;
				strOrbiterTexName = "SSV\\OV\\OV-099_original.dds";
				PLBDHingeFairings = 0;
				ChinPanel = false;
			}
			else if (!strcmp( "Discovery", tmp->valuestring ))
			{
				strOrbiter = "Discovery";
				OVmass = ORBITER_EMPTY_MASS_OV103;
				strOrbiterTexName = "SSV\\OV\\OV-103_9thmod.dds";
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "Endeavour", tmp->valuestring ))
			{
				strOrbiter = "Endeavour";
				OVmass = ORBITER_EMPTY_MASS_OV105;
				strOrbiterTexName = "SSV\\OV\\OV-105_3rdmod.dds";
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			// default already loaded ORBITER_EMPTY_MASS_OV104 and "OV-104_5thmod.dds" texture is default in mesh

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "Texture" );
			strOrbiterTexName = "SSV\\OV\\" + std::string( tmp->valuestring ) + ".dds";
			if (!strcmp( "OV-102_original", tmp->valuestring ))
			{
				PLBDHingeFairings = 0;
				ChinPanel = false;
			}
			else if (!strcmp( "OV-102_4thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-102_6thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-102_8thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-099_original", tmp->valuestring ))
			{
				PLBDHingeFairings = 0;
				ChinPanel = false;
			}
			else if (!strcmp( "OV-103_original", tmp->valuestring ))
			{
				PLBDHingeFairings = 1;
				ChinPanel = false;
			}
			else if (!strcmp( "OV-103_6thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 1;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-103_9thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-104_original", tmp->valuestring ))
			{
				PLBDHingeFairings = 1;
				ChinPanel = false;
			}
			else if (!strcmp( "OV-104_4thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 1;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-104_5thmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-105_original", tmp->valuestring ))
			{
				PLBDHingeFairings = 1;
				ChinPanel = true;
			}
			else if (!strcmp( "OV-105_3rdmod", tmp->valuestring ))
			{
				PLBDHingeFairings = 2;
				ChinPanel = true;
			}

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "LOMS Pod Texture" );
			strLOMSPodTexName = "SSV\\OV\\" + std::string( tmp->valuestring ) + ".dds";

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "ROMS Pod Texture" );
			strROMSPodTexName = "SSV\\OV\\" + std::string( tmp->valuestring ) + ".dds";

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "Ku-band Antenna" );
			bHasKUBand = cJSON_IsTrue( tmp );

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "External Airlock / ODS Kit" );
			bHasExtALODSKit = cJSON_IsTrue( tmp );

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "Airlock" );
			if (!strcmp( tmp->valuestring, "Internal" )) bHasExtAL = false;
			else /*if (!strcmp( tmp->valuestring, "External" ))*/ bHasExtAL = true;

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "TAA" );
			if (!strcmp( tmp->valuestring, "Forward" ))
			{
				bHasTAA = true;
				bAftTAA = false;
			}
			else if (!strcmp( tmp->valuestring, "Aft" ))
			{
				bHasTAA = true;
				bAftTAA = true;
			}
			else /*if (!strcmp( tmp->valuestring, "None" ))*/ bHasTAA = false;

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "ODS" );
			bHasODS = cJSON_IsTrue( tmp );

			if ((strOrbiter == "Discovery") || (strOrbiter == "Endeavour"))
			{
				tmp = cJSON_GetObjectItemCaseSensitive( ov, "Fwd Bulkhead / Dock Lights" );
				bHasBulkheadFloodlights = cJSON_IsTrue( tmp );
			}

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "Drag Chute" );
			bHasDragChute = cJSON_IsTrue( tmp );

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "PLB Liner" );
			bHasPLBLiner = cJSON_IsTrue( tmp );

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "SILTS" );
			bUseSILTS = cJSON_IsTrue( tmp );

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "DFI Wire Tray" );
			bHasDFIWireTray = cJSON_IsTrue( tmp );

			tmp = cJSON_GetObjectItemCaseSensitive( ov, "Vent Doors 4 and 7" );
			bHasVentDoors4and7 = cJSON_IsTrue( tmp );

			// CrewModule
			tmp = cJSON_GetObjectItemCaseSensitive( ov, "Crew Module" );
			if (tmp)
			{
				cJSON* tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Crew" );
				Crew = tmp2->valueint;
				if (Crew > 7) Crew = 7;
				else if (Crew < 2) Crew = 2;

				tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Galley" );
				if (!strcmp( "None", tmp2->valuestring )) Galley = 0;
				else if (!strcmp( "Original", tmp2->valuestring )) Galley = 1;
				else /*if (!strcmp( "SORG", tmp2->valuestring ))*/ Galley = 2;

				tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Sleep Stations" );
				if (!strcmp( "ThreeTier", tmp2->valuestring )) SleepStations = 1;
				else if (!strcmp( "FourTier", tmp2->valuestring )) SleepStations = 2;
				else /*if (!strcmp( "None", tmp2->valuestring ))*/ SleepStations = 0;

				tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Ejection Seats" );
				EjectionSeats = cJSON_IsTrue( tmp2 );

				tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Crew Escape Hardware" );
				CrewEscapeHardware = cJSON_IsTrue( tmp2 );

				tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Flight Deck" );
				if (!strcmp( "MCDS", tmp2->valuestring )) MEDSFlightDeck = false;
				else /*if (!strcmp( "MEDS", tmp2->valuestring ))*/ MEDSFlightDeck = true;
			}

			// DPS
			tmp = cJSON_GetObjectItemCaseSensitive( ov, "DPS" );
			if (tmp)
			{
				cJSON* tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Landing Site Table" );
				if (tmp2)
					strLandingSiteTable = std::string( tmp2->valuestring );

				if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "I-load" ))
				{
					for (int i = 0; i < cJSON_GetArraySize( tmp2 ); i++)
					{
						cJSON* tmp3 = cJSON_GetArrayItem( tmp2, i );
						if (tmp3)
						{
							cJSON* id;
							cJSON* val;
							id = cJSON_GetObjectItemCaseSensitive( tmp3, "ID" );
							val = cJSON_GetObjectItemCaseSensitive( tmp3, "Val" );
							if (id && val) ILOADlist.insert( std::pair<std::string,std::string>( std::string( id->valuestring ), std::string( val->valuestring ) ) );
						}
					}
				}
			}

			// PRSD
			cJSON* prsd = cJSON_GetObjectItemCaseSensitive( ov, "PRSD" );
			if (prsd)
			{
				cJSON* tmp2;
				if (tmp2 = cJSON_GetObjectItemCaseSensitive( prsd, "Internal Tank Sets" )) InternalPRSDTankSets = tmp2->valueint;
				if (tmp2 = cJSON_GetObjectItemCaseSensitive( prsd, "EDO Kit" ))
				{
					if (tmp2->type != cJSON_NULL)
					{
						bHasEDOKit = true;
						cJSON* tmp3;
						if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Pallet" ))
						{
							if (!strcmp( "Single", tmp3->valuestring )) EDOPallet = 1;
							else if (!strcmp( "Dual", tmp3->valuestring )) EDOPallet = 2;
							else /*if (!strcmp( "None", tmp3->valuestring ))*/ EDOPallet = 0;
						}
					}
					else bHasEDOKit = false;
				}
				else bHasEDOKit = false;
			}

			// PayloadBay
			cJSON* plb = cJSON_GetObjectItemCaseSensitive( ov, "Payload Bay" );
			if (plb)
			{
				// Payloads
				int activeidx = 0;
				int passiveidx = 0;
				int baybridgeidx = 0;
				tmp = cJSON_GetObjectItemCaseSensitive( plb, "Payloads" );
				for (int i = 0; i < cJSON_GetArraySize( tmp ); i++)
				{
					cJSON* tmp2 = cJSON_GetArrayItem( tmp, i );
					if (tmp2)
					{
						cJSON* tmp3;
						if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Active" ))
						{
							if (activeidx < 5)
							{
								LoadActivePayload( payloads.active[activeidx], tmp3 );
								activeidx++;
							}
							else
							{
								// TODO kaput
							}
						}
						else if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Passive" ))
						{
							if (passiveidx < 5)
							{
								LoadPassivePayload( payloads.passive[passiveidx], tmp3 );
								passiveidx++;
							}
							else
							{
								// TODO kaput
							}
						}
						else if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Bay Bridge" ))
						{
							if (baybridgeidx < 8)
							{
								LoadBayBridgePayload( payloads.baybridge[baybridgeidx], tmp3 );
								baybridgeidx++;
							}
							else
							{
								// TODO kaput
							}
						}

					}
				}

				// UpperStageCradles
				tmp = cJSON_GetObjectItemCaseSensitive( plb, "Upper Stage Cradles" );
				for (int i = 0; i < cJSON_GetArraySize( tmp ); i++)
				{
					cJSON* tmp2 = cJSON_GetArrayItem( tmp, i );
					if (tmp2)
					{
						cJSON* tmp3;
						if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "IUS 2-Stage ASE" ))
						{
							bUseASE_IUS = true;

							cJSON* tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Aft Position" );
							bASE_IUS_Aft_Location = cJSON_IsTrue( tmp4 );

							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Port Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[0].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[0].Latch = tmp5->valueint;
							}
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Starboard Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[1].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[1].Latch = tmp5->valueint;
							}
						}
						else if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "CISS G" ))
						{
							bUseCISS = true;
							bCISS_GPrime = false;

							cJSON* tmp4;
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Port Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[0].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[0].Latch = tmp5->valueint;
							}
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Starboard Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[1].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[1].Latch = tmp5->valueint;
							}
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Keel Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[2].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[2].Latch = tmp5->valueint;
							}
						}
						else if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "CISS G-Prime" ))
						{
							bUseCISS = true;
							bCISS_GPrime = true;

							cJSON* tmp4;
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Port Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[0].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[0].Latch = tmp5->valueint;
							}
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Starboard Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[1].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[1].Latch = tmp5->valueint;
							}
							if (tmp4 = cJSON_GetObjectItemCaseSensitive( tmp3, "Keel Latch" ))
							{
								cJSON* tmp5;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Payload" )) LargeUpperStage_Latches[2].PL = tmp5->valueint;
								if (tmp5 = cJSON_GetObjectItemCaseSensitive( tmp4, "Latch" )) LargeUpperStage_Latches[2].Latch = tmp5->valueint;
							}
						}
					}
				}

				// PortLongeronSill
				tmp = cJSON_GetObjectItemCaseSensitive( plb, "Port Longeron Sill" );
				if (tmp)
				{
					cJSON* tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "RMS" );
					if (tmp2) PortLongeronSill = RMS;
				}

				// StarboardLongeronSill
				tmp = cJSON_GetObjectItemCaseSensitive( plb, "Starboard Longeron Sill" );
				if (tmp)
				{
					cJSON* tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Payload MPM" );
					if (tmp2)
					{
						StbdLongeronSill = PLMPM;
						LoadPayloadMPM( Stbd_PayloadMPM, tmp2 );
					}
				}
			}
		}

		// Legacy Launch Parameters
		cJSON* legacymeco = cJSON_GetObjectItemCaseSensitive( root, "Legacy Launch Parameters" );
		if (legacymeco)
		{
			cJSON* tmp = cJSON_GetObjectItemCaseSensitive( legacymeco, "TargetInc" );
			fTargetInc = tmp->valuedouble * RAD;

			tmp = cJSON_GetObjectItemCaseSensitive( legacymeco, "MECOAlt" );
			fMECOAlt = tmp->valuedouble;

			tmp = cJSON_GetObjectItemCaseSensitive( legacymeco, "MECOVel" );
			fMECOVel = tmp->valuedouble;

			tmp = cJSON_GetObjectItemCaseSensitive( legacymeco, "MECOFPA" );
			fMECOFPA = tmp->valuedouble * RAD;
		}
		return;
	}

	void Mission::LoadActivePayload( ActivePayload& pl, cJSON* root )
	{
		cJSON* tmp;
		int portlatch = 0;
		int stbdlatch = 4;
		int keellatch = 8;
		pl.IsUsed = true;

		for (int i = 0; i < cJSON_GetArraySize( root ); i++)
		{
			tmp = cJSON_GetArrayItem( root, i );
			if (tmp)
			{
				cJSON* tmp2;
				if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Type" ))
				{
					int idx = 0;
					if (!strcmp( tmp2->valuestring, "Port Longeron" ))
					{
						// PortLongeron
						idx = portlatch;
						if (portlatch < 3) portlatch++;

						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "PLID" )) pl.PLID[idx] = tmp2->valueint;
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" )) pl.IsAttachment[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Reversed" )) pl.Reversed[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Payload Latch" ))
						{
							cJSON* tmp3;
							if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Payload" )) pl.Latches[idx].PL = tmp3->valueint;
							if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Latch" )) pl.Latches[idx].Latch = tmp3->valueint;
						}

						tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Forward Guide" );
						if (!strcmp( "22''", tmp2->valuestring )) pl.FwdGuide[idx] = 1;
						else if (!strcmp( "24''", tmp2->valuestring )) pl.FwdGuide[idx] = 2;
						else /*if (!strcmp( "None", tmp2->valuestring ))*/ pl.FwdGuide[idx] = 0;

						tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Aft Guide" );
						if (!strcmp( "22''", tmp2->valuestring )) pl.AftGuide[idx] = 1;
						else if (!strcmp( "24''", tmp2->valuestring )) pl.AftGuide[idx] = 2;
						else /*if (!strcmp( "None", tmp2->valuestring ))*/ pl.AftGuide[idx] = 0;
					}
					else if (!strcmp( tmp2->valuestring, "Starboard Longeron" ))
					{
						// StarboardLongeron
						idx = stbdlatch;
						if (stbdlatch < 7) stbdlatch++;

						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "PLID" )) pl.PLID[idx] = tmp2->valueint;
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" )) pl.IsAttachment[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Reversed" )) pl.Reversed[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Payload Latch" ))
						{
							cJSON* tmp3;
							if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Payload" )) pl.Latches[idx].PL = tmp3->valueint;
							if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Latch" )) pl.Latches[idx].Latch = tmp3->valueint;
						}

						tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Forward Guide" );
						if (!strcmp( "22''", tmp2->valuestring )) pl.FwdGuide[idx] = 1;
						else if (!strcmp( "24''", tmp2->valuestring )) pl.FwdGuide[idx] = 2;
						else /*if (!strcmp( "None", tmp2->valuestring ))*/ pl.FwdGuide[idx] = 0;

						tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Aft Guide" );
						if (!strcmp( "22''", tmp2->valuestring )) pl.AftGuide[idx] = 1;
						else if (!strcmp( "24''", tmp2->valuestring )) pl.AftGuide[idx] = 2;
						else /*if (!strcmp( "None", tmp2->valuestring ))*/ pl.AftGuide[idx] = 0;
					}
					else if (!strcmp( tmp2->valuestring, "Keel" ))
					{
						// Keel
						idx = keellatch;
						if (keellatch < 11) keellatch++;

						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "PLID" )) pl.PLID[idx] = tmp2->valueint;
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" )) pl.IsAttachment[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Payload Latch" ))
						{
							cJSON* tmp3;
							if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Payload" )) pl.Latches[idx].PL = tmp3->valueint;
							if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Latch" )) pl.Latches[idx].Latch = tmp3->valueint;
						}
					}
				}
			}
		}
		return;
	}

	void Mission::LoadPassivePayload( PassivePayload& pl, cJSON* root )
	{
		cJSON* tmp;
		int portlatch = 0;
		int stbdlatch = 4;
		int keellatch = 8;
		pl.IsUsed = true;

		for (int i = 0; i < cJSON_GetArraySize( root ); i++)
		{
			tmp = cJSON_GetArrayItem( root, i );
			if (tmp)
			{
				cJSON* tmp2;
				if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Type" ))
				{
					int idx = 0;
					if (!strcmp( tmp2->valuestring, "Port Longeron" ))
					{
						// PortLongeron
						idx = portlatch;
						if (portlatch < 3) portlatch++;

						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "PLID" )) pl.PLID[idx] = tmp2->valueint;
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" )) pl.IsAttachment[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Reversed" )) pl.Reversed[idx] = (tmp2->valueint == 1);
					}
					else if (!strcmp( tmp2->valuestring, "Starboard Longeron" ))
					{
						// StarboardLongeron
						idx = stbdlatch;
						if (stbdlatch < 7) stbdlatch++;

						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "PLID" )) pl.PLID[idx] = tmp2->valueint;
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" )) pl.IsAttachment[idx] = (tmp2->valueint == 1);
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Reversed" )) pl.Reversed[idx] = (tmp2->valueint == 1);
					}
					else if (!strcmp( tmp2->valuestring, "Keel" ))
					{
						// Keel
						idx = keellatch;
						if (keellatch < 11) keellatch++;

						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "PLID" )) pl.PLID[idx] = tmp2->valueint;
						if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" )) pl.IsAttachment[idx] = (tmp2->valueint == 1);
					}
				}
			}
		}
		return;
	}

	void Mission::LoadBayBridgePayload( BayBridgePayload& pl, cJSON* root )
	{
		cJSON* tmp = cJSON_GetObjectItemCaseSensitive( root, "Bay" );
		if (tmp) pl.bay = tmp->valueint;

		tmp = cJSON_GetObjectItemCaseSensitive( root, "Bridge" );
		if (!strcmp( tmp->valuestring, "Port" )) pl.bridge = 0;
		else if (!strcmp( tmp->valuestring, "Starboard" )) pl.bridge = 1;
		else if (!strcmp( tmp->valuestring, "Keel" )) pl.bridge = 2;

		pl.IsUsed = true;
		return;
	}

	void Mission::LoadPayloadMPM( PayloadMPM& plmpm, cJSON* root )
	{
		cJSON* tmp;
		cJSON* tmp2;
		cJSON* tmp3;

		if (tmp = cJSON_GetObjectItemCaseSensitive( root, "Pedestals" ))
		{
			if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Attachment" ))
			{
				if (!strcmp( "Shoulder", tmp2->valuestring )) plmpm.attachment = 0;
				else if (!strcmp( "Forward", tmp2->valuestring )) plmpm.attachment = 1;
				else if (!strcmp( "Mid", tmp2->valuestring )) plmpm.attachment = 2;
				else /*if (!strcmp( "Aft", tmp2->valuestring ))*/ plmpm.attachment = 3;
			}

			if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Shoulder" ))
			{
				if (tmp2->type != cJSON_NULL)
				{
					plmpm.Shoulder.IsUsed = true;

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Mesh" ))
						plmpm.Shoulder.mesh = std::string( tmp3->valuestring );
					//else // TODO kaput

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "MRL" ))
					{
						if (!strcmp( "None", tmp3->valuestring )) plmpm.Shoulder.MRL = 0;
						else if (!strcmp( "Forward", tmp3->valuestring )) plmpm.Shoulder.MRL = 1;
						else if (!strcmp( "Mid", tmp3->valuestring )) plmpm.Shoulder.MRL = 2;
						else /*if (!strcmp( "Aft", tmp3->valuestring ))*/ plmpm.Shoulder.MRL = 3;
					}
				}
			}

			if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Forward" ))
			{
				if (tmp2->type != cJSON_NULL)
				{
					plmpm.Forward.IsUsed = true;

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Mesh" ))
						plmpm.Forward.mesh = std::string( tmp3->valuestring );
					//else // TODO kaput

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "MRL" ))
					{
						if (!strcmp( "None", tmp3->valuestring )) plmpm.Forward.MRL = 0;
						else if (!strcmp( "Forward", tmp3->valuestring )) plmpm.Forward.MRL = 1;
						else if (!strcmp( "Mid", tmp3->valuestring )) plmpm.Forward.MRL = 2;
						else /*if (!strcmp( "Aft", tmp3->valuestring ))*/ plmpm.Forward.MRL = 3;
					}
				}
			}

			if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Mid" ))
			{
				if (tmp2->type != cJSON_NULL)
				{
					plmpm.Mid.IsUsed = true;

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Mesh" ))
						plmpm.Mid.mesh = std::string( tmp3->valuestring );
					//else // TODO kaput

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "MRL" ))
					{
						if (!strcmp( "None", tmp3->valuestring )) plmpm.Mid.MRL = 0;
						else if (!strcmp( "Forward", tmp3->valuestring )) plmpm.Mid.MRL = 1;
						else if (!strcmp( "Mid", tmp3->valuestring )) plmpm.Mid.MRL = 2;
						else /*if (!strcmp( "Aft", tmp3->valuestring ))*/ plmpm.Mid.MRL = 3;
					}
				}
			}

			if (tmp2 = cJSON_GetObjectItemCaseSensitive( tmp, "Aft" ))
			{
				if (tmp2->type != cJSON_NULL)
				{
					plmpm.Aft.IsUsed = true;

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "Mesh" ))
						plmpm.Aft.mesh = std::string( tmp3->valuestring );
					//else // TODO kaput

					if (tmp3 = cJSON_GetObjectItemCaseSensitive( tmp2, "MRL" ))
					{
						if (!strcmp( "None", tmp3->valuestring )) plmpm.Aft.MRL = 0;
						else if (!strcmp( "Forward", tmp3->valuestring )) plmpm.Aft.MRL = 1;
						else if (!strcmp( "Mid", tmp3->valuestring )) plmpm.Aft.MRL = 2;
						else /*if (!strcmp( "Aft", tmp3->valuestring ))*/ plmpm.Aft.MRL = 3;
					}
				}
			}
		}
		//else // TODO kaput
		return;
	}

	double Mission::GetMECOInc( void ) const
	{
		return fTargetInc;
	}

	double Mission::GetMECOAlt( void ) const
	{
		return fMECOAlt;
	}

	double Mission::GetMECOVel( void ) const
	{
		return fMECOVel;
	}

	double Mission::GetMECOFPA( void ) const
	{
		return fMECOFPA;
	}

	bool Mission::IsExternalAirlockAftPos( void ) const
	{
		return (bHasTAA && !bAftTAA);
	}

	const std::string& Mission::GetOrbiter( void ) const
	{
		return strOrbiter;
	}

	const std::string& Mission::GetMissionFileName( void ) const
	{
		return strFileName;
	}

	const std::string& Mission::GetOrbiterTextureName( void ) const
	{
		return strOrbiterTexName;
	}

	const std::string& Mission::GetLOMSPodTextureName( void ) const
	{
		return strLOMSPodTexName;
	}

	const std::string& Mission::GetROMSPodTextureName( void ) const
	{
		return strROMSPodTexName;
	}

	bool Mission::HasRMS( void ) const
	{
		return PortLongeronSill == RMS;
	}

	bool Mission::HasPLMPM( void ) const
	{
		return StbdLongeronSill == PLMPM;
	}

	bool Mission::HasExtALODSKit( void ) const
	{
		return bHasExtALODSKit;
	}

	bool Mission::HasODS( void ) const
	{
		return bHasODS;
	}

	bool Mission::HasExtAL( void ) const
	{
		return bHasExtAL;
	}

	bool Mission::HasTAA( void ) const
	{
		return bHasTAA;
	}

	bool Mission::AftTAA( void ) const
	{
		return bAftTAA;
	}

	bool Mission::HasBulkheadFloodlights( void ) const
	{
		return bHasBulkheadFloodlights;
	}

	bool Mission::HasDragChute( void ) const
	{
		return bHasDragChute;
	}

	bool Mission::HasPLBLiner( void ) const
	{
		return bHasPLBLiner;
	}

	bool Mission::HasDFIWireTray( void ) const
	{
		return bHasDFIWireTray;
	}

	bool Mission::HasVentDoors4and7( void ) const
	{
		return bHasVentDoors4and7;
	}

	double Mission::GetOrbiterMass( void ) const
	{
		return OVmass;
	}

	bool Mission::HasKUBand( void ) const
	{
		return bHasKUBand;
	}

	bool Mission::UseSILTS( void ) const
	{
		return bUseSILTS;
	}

	bool Mission::UseASE_IUS( void ) const
	{
		return bUseASE_IUS;
	}

	bool Mission::IsASELocationAft( void ) const
	{
		return bASE_IUS_Aft_Location;
	}

	bool Mission::UseCISS( void ) const
	{
		return bUseCISS;
	}

	bool Mission::IsCISSGPrime( void ) const
	{
		return bCISS_GPrime;
	}

	int Mission::GetInternalPRSDTankSets( void ) const
	{
		return InternalPRSDTankSets;
	}

	bool Mission::HasEDOKit( void ) const
	{
		return bHasEDOKit;
	}

	unsigned short Mission::GetEDOPallet( void ) const
	{
		return EDOPallet;
	}

	bool Mission::HasOMSKit( void ) const
	{
		return bHasOMSKit;
	}

	const std::string& Mission::GetLandingSiteTable( void ) const
	{
		return strLandingSiteTable;
	}

	const std::map<std::string,std::string>& Mission::GetILOADs( void ) const
	{
		return ILOADlist;
	}

	void Mission::ClearILOADs( void )
	{
		ILOADlist.clear();
		return;
	}

	const struct MissionPayloads& Mission::GetPayloads( void ) const
	{
		return payloads;
	}

	const struct PayloadMPM& Mission::GetPayloadMPM( bool port ) const
	{
		return port ? Stbd_PayloadMPM/*TODO port side*/ : Stbd_PayloadMPM;
	}

	const struct Latches* Mission::GetLargeUpperStageLatches( void ) const
	{
		return LargeUpperStage_Latches;
	}

	unsigned short Mission::GetPLBDHingeFairings( void ) const
	{
		return PLBDHingeFairings;
	}

	bool Mission::GetChinPanel( void ) const
	{
		return ChinPanel;
	}
}
