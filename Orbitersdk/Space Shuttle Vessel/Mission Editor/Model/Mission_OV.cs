/****************************************************************************
  This file is part of Space Shuttle Vessel Mission Editor
  
  Space Shuttle Vessel is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/05/31   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/07/02   GLS
2020/07/03   GLS
2020/07/08   GLS
2020/07/30   GLS
2020/08/22   GLS
2020/08/23   GLS
2020/09/19   GLS
2020/10/06   GLS
2020/10/09   GLS
2020/10/10   GLS
2021/11/13   GLS
2021/11/27   GLS
2021/12/05   GLS
2021/12/10   GLS
2021/12/11   GLS
2021/12/24   GLS
2022/01/10   GLS
2022/02/05   GLS
2022/02/23   GLS
2022/02/25   GLS
2022/03/02   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/05/01   GLS
2022/06/16   GLS
2022/06/19   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/10/17   GLS
2022/12/05   GLS
2022/12/08   GLS
2022/12/09   GLS
2022/12/10   GLS
2022/12/13   GLS
2023/02/13   GLS
2023/02/14   GLS
2023/03/30   GLS
2023/04/09   GLS
2023/08/06   GLS
2024/09/09   GLS
2025/06/21   GLS
2025/07/16   GLS
2025/08/30   GLS
2025/09/26   GLS
2025/10/02   GLS
********************************************/

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.Model
{
	public enum LongeronSillHardware_Type
	{
		None = 0,
		RMS,
		PayloadMPM,
		SPDS
	}


	public class Mission_OV
	{
		public static readonly int PAYLOAD_ACTIVE_MAX = 5;// maximum number of "active" PLB payloads
		public static readonly int PAYLOAD_PASSIVE_MAX = 5;// maximum number of "passive" PLB payloads
		public static readonly int PAYLOAD_BAYBRIDGE_MAX = 8;// maximum number of "bay bridge" PLB payloads

		public static readonly int PAYLOADLATCH_MAX = 12;// maximum number of latches per PLB payload


		public Mission_OV( Mission mission, string orbiterpath )
		{
			this.mission = mission;

			PL_Active = new Mission_PLActive[PAYLOAD_ACTIVE_MAX];
			for (int i = 0; i < PAYLOAD_ACTIVE_MAX; i++) PL_Active[i] = new Mission_PLActive();

			PL_Passive = new Mission_PLPassive[PAYLOAD_PASSIVE_MAX];
			for (int i = 0; i < PAYLOAD_PASSIVE_MAX; i++) PL_Passive[i] = new Mission_PLPassive();

			PL_BayBridge = new Mission_PLBayBridge[PAYLOAD_BAYBRIDGE_MAX];
			for (int i = 0; i < PAYLOAD_BAYBRIDGE_MAX; i++) PL_BayBridge[i] = new Mission_PLBayBridge();

			LargeUpperStage_Latch = new int[3];

			SmallUpperStage_ASEPLID = new int[Defs.SMALLUPPERSTAGE_MAX];
			SmallUpperStage_LargeSunshield = new bool[Defs.SMALLUPPERSTAGE_MAX];

			Port_RMS = new Mission_RMS();
			Stbd_RMS = new Mission_RMS();
			Port_PL_MPM = new Mission_PL_MPM();
			Stbd_PL_MPM = new Mission_PL_MPM();
			Port_SPDS = new Mission_SPDS();
			Stbd_SPDS = new Mission_SPDS();

			ILOAD_List = new ObservableCollection<Mission_ILOAD>();

			SSME = new Mission_SSME[3];
			SSME[0] = new Mission_SSME();
			SSME[1] = new Mission_SSME();
			SSME[2] = new Mission_SSME();

			LandingSiteTable = new List<Tuple<string,string>>();

			PLB_Cameras = new Mission_PLB_Camera();

			LoadDefault();
		}

		public void LoadDefault()
		{
			Name = Defs.strAtlantis;
			Texture = "OV-104_5thmod";
			LOMStex = "OMSpod_7thmod";
			ROMStex = "OMSpod_7thmod";
			KubandAntenna = true;
			ExtAL_ODS_Kit = true;
			ODS = true;
			TAA = Defs.strNone;
			Airlock = Defs.strExternal;
			FwdBulkDockLights = true;
			DragChute = true;
			PLBLiner = false;
			SILTS = false;
			DFIWireTray = false;
			VentDoors4and7 = false;

			Crew = 7;
			Galley = Defs.strSORG;
			SleepStations = Defs.strNone;
			EjectionSeats = false;
			CrewEscapeHardware = true;
			FlightDeck = Defs.strMEDS;

			FRCS_Load = 2473.0;
			LRCS_Load = 2692.0;
			RRCS_Load = 2692.0;
			LOMS_Load = 12593.5;
			ROMS_Load = 12593.5;

			PRSDInternalTanks = 5;
			EDOKit = true;
			EDOPallet = 0;

			for (int i = 0; i < PAYLOAD_ACTIVE_MAX; i++) PL_Active[i].LoadDefault();
			for (int i = 0; i < PAYLOAD_PASSIVE_MAX; i++) PL_Passive[i].LoadDefault();
			for (int i = 0; i < PAYLOAD_BAYBRIDGE_MAX; i++) PL_BayBridge[i].LoadDefault();

			for (int i = 0; i < 3; i++) LargeUpperStage_Latch[i] = 0;

			for (int i = 0; i < 3; i++)
			{
				SmallUpperStage_ASEPLID[i] = 0;
				SmallUpperStage_LargeSunshield[i] = false;
			}

			PortLongeronSill = LongeronSillHardware_Type.RMS;
			Port_RMS.LoadDefault();
			Port_PL_MPM.LoadDefault();
			Port_SPDS.LoadDefault();
			StbdLongeronSill = LongeronSillHardware_Type.None;
			Stbd_RMS.LoadDefault();
			Stbd_PL_MPM.LoadDefault();
			Stbd_SPDS.LoadDefault();

			ILOAD_List = Mission_ILOAD.LoadDefault();

			foreach (Mission_SSME me in SSME) me.LoadDefault();

			LandingSiteTable.Clear();
			LandingSiteTable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			LandingSiteTable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			LandingSiteTable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 3
			LandingSiteTable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 4
			LandingSiteTable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 5
			LandingSiteTable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 6
			LandingSiteTable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 7
			LandingSiteTable.Add( new Tuple<string,string>( "NTU32R", "NTU23L" ) );// 8
			LandingSiteTable.Add( new Tuple<string,string>( "WAL28", "WAL04" ) );// 9
			LandingSiteTable.Add( new Tuple<string,string>( "DOV32", "DOV19" ) );// 10
			LandingSiteTable.Add( new Tuple<string,string>( "ACY31", "ACY13" ) );// 11
			LandingSiteTable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 12
			LandingSiteTable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 13
			LandingSiteTable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 14
			LandingSiteTable.Add( new Tuple<string,string>( "FOK06", "FOK24" ) );// 15
			LandingSiteTable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 16
			LandingSiteTable.Add( new Tuple<string,string>( "PSM34", "PSM16" ) );// 17
			LandingSiteTable.Add( new Tuple<string,string>( "YHZ23", "YHZ32" ) );// 18
			LandingSiteTable.Add( new Tuple<string,string>( "YJT09", "YJT27" ) );// 19
			LandingSiteTable.Add( new Tuple<string,string>( "YYT29", "YYT11" ) );// 20
			LandingSiteTable.Add( new Tuple<string,string>( "YQX21", "YQX31" ) );// 21
			LandingSiteTable.Add( new Tuple<string,string>( "YYR26", "YYR34" ) );// 22
			LandingSiteTable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 23
			LandingSiteTable.Add( new Tuple<string,string>( "BEJ01L", "BEJ19R" ) );// 24
			LandingSiteTable.Add( new Tuple<string,string>( "IKF20", "IKF29" ) );// 25
			LandingSiteTable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			LandingSiteTable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			LandingSiteTable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			LandingSiteTable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			LandingSiteTable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			LandingSiteTable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			LandingSiteTable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			LandingSiteTable.Add( new Tuple<string,string>( "AMB15", "PTN14" ) );// 33
			LandingSiteTable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 34
			LandingSiteTable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 35
			LandingSiteTable.Add( new Tuple<string,string>( "WAK28", "WAK10" ) );// 36
			LandingSiteTable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 37
			LandingSiteTable.Add( new Tuple<string,string>( "EDF24", "EDF06" ) );// 38
			LandingSiteTable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 39
			LandingSiteTable.Add( new Tuple<string,string>( "EDT22R", "EDT04L" ) );// 40
			LandingSiteTable.Add( new Tuple<string,string>( "HAW13", "HAW31" ) );// 41
			LandingSiteTable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 42
			LandingSiteTable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 43
			LandingSiteTable.Add( new Tuple<string,string>( "EDW15", "EDW18L" ) );// 44
			LandingSiteTable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45

			TgtVessel = "ISS";

			PLB_Cameras.LoadDefault();
			return;
		}

		public void LoadEmpty()
		{
			Name = Defs.strAtlantis;
			Texture = "OV-104_5thmod";
			LOMStex = "OMSpod_7thmod";
			ROMStex = "OMSpod_7thmod";
			KubandAntenna = true;
			ExtAL_ODS_Kit = false;
			ODS = false;
			TAA = Defs.strNone;
			Airlock = Defs.strInternal;
			FwdBulkDockLights = true;
			DragChute = true;
			PLBLiner = false;
			SILTS = false;
			DFIWireTray = false;
			VentDoors4and7 = false;

			Crew = 7;
			Galley = Defs.strSORG;
			SleepStations = Defs.strNone;
			EjectionSeats = false;
			CrewEscapeHardware = true;
			FlightDeck = Defs.strMEDS;

			// full loads
			FRCS_Load = 2473.0;
			LRCS_Load = 2692.0;
			RRCS_Load = 2692.0;
			LOMS_Load = 12593.5;
			ROMS_Load = 12593.5;

			PRSDInternalTanks = 5;
			EDOKit = true;
			EDOPallet = 0;

			// no payloads or upper stages
			for (int i = 0; i < PAYLOAD_ACTIVE_MAX; i++) PL_Active[i].LoadEmpty();
			for (int i = 0; i < PAYLOAD_PASSIVE_MAX; i++) PL_Passive[i].LoadEmpty();
			for (int i = 0; i < PAYLOAD_BAYBRIDGE_MAX; i++) PL_BayBridge[i].LoadEmpty();

			for (int i = 0; i < 3; i++) LargeUpperStage_Latch[i] = 0;

			PortLongeronSill = LongeronSillHardware_Type.RMS;
			Port_RMS.LoadEmpty();
			Port_PL_MPM.LoadEmpty();
			Port_SPDS.LoadEmpty();
			StbdLongeronSill = LongeronSillHardware_Type.None;
			Stbd_RMS.LoadEmpty();
			Stbd_PL_MPM.LoadEmpty();
			Stbd_SPDS.LoadEmpty();

			ILOAD_List = Mission_ILOAD.LoadDefault();

			foreach (Mission_SSME me in SSME) me.LoadEmpty();

			LandingSiteTable.Clear();
			LandingSiteTable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			LandingSiteTable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			LandingSiteTable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 3
			LandingSiteTable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 4
			LandingSiteTable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 5
			LandingSiteTable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 6
			LandingSiteTable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 7
			LandingSiteTable.Add( new Tuple<string,string>( "NTU32R", "NTU23L" ) );// 8
			LandingSiteTable.Add( new Tuple<string,string>( "WAL28", "WAL04" ) );// 9
			LandingSiteTable.Add( new Tuple<string,string>( "DOV32", "DOV19" ) );// 10
			LandingSiteTable.Add( new Tuple<string,string>( "ACY31", "ACY13" ) );// 11
			LandingSiteTable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 12
			LandingSiteTable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 13
			LandingSiteTable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 14
			LandingSiteTable.Add( new Tuple<string,string>( "FOK06", "FOK24" ) );// 15
			LandingSiteTable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 16
			LandingSiteTable.Add( new Tuple<string,string>( "PSM34", "PSM16" ) );// 17
			LandingSiteTable.Add( new Tuple<string,string>( "YHZ23", "YHZ32" ) );// 18
			LandingSiteTable.Add( new Tuple<string,string>( "YJT09", "YJT27" ) );// 19
			LandingSiteTable.Add( new Tuple<string,string>( "YYT29", "YYT11" ) );// 20
			LandingSiteTable.Add( new Tuple<string,string>( "YQX21", "YQX31" ) );// 21
			LandingSiteTable.Add( new Tuple<string,string>( "BYD32", "BYD14" ) );// 22
			LandingSiteTable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 23
			LandingSiteTable.Add( new Tuple<string,string>( "VBG30", "VBG12" ) );// 24
			LandingSiteTable.Add( new Tuple<string,string>( "IKF20", "IKF29" ) );// 25
			LandingSiteTable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			LandingSiteTable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			LandingSiteTable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			LandingSiteTable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			LandingSiteTable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			LandingSiteTable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			LandingSiteTable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			LandingSiteTable.Add( new Tuple<string,string>( "AMB15", "PTN14" ) );// 33
			LandingSiteTable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 34
			LandingSiteTable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 35
			LandingSiteTable.Add( new Tuple<string,string>( "BDA30", "BDA12" ) );// 36
			LandingSiteTable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 37
			LandingSiteTable.Add( new Tuple<string,string>( "EIP28", "EIP10" ) );// 38
			LandingSiteTable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 39
			LandingSiteTable.Add( new Tuple<string,string>( "AWG25", "AWG07" ) );// 40
			LandingSiteTable.Add( new Tuple<string,string>( "HAW31", "HAW13" ) );// 41
			LandingSiteTable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 42
			LandingSiteTable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 43
			LandingSiteTable.Add( new Tuple<string,string>( "EDW15", "EDW18L" ) );// 44
			LandingSiteTable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45

			TgtVessel = "";

			PLB_Cameras.LoadEmpty();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			{
				string strtmp = (string)jtk["Name"];
				if (strtmp == Defs.strColumbia) Name = Defs.strColumbia;
				else if (strtmp == Defs.strChallenger) Name = Defs.strChallenger;
				else if (strtmp == Defs.strDiscovery) Name = Defs.strDiscovery;
				else if (strtmp == Defs.strAtlantis) Name = Defs.strAtlantis;
				else if (strtmp == Defs.strEndeavour) Name = Defs.strEndeavour;
				else
				{
					// TODO kaput
				}
			}
			Texture = (string)jtk["Texture"];
			LOMStex = (string)jtk["LOMS Pod Texture"];
			ROMStex = (string)jtk["ROMS Pod Texture"];
			KubandAntenna = (bool)jtk["Ku-band Antenna"];
			ExtAL_ODS_Kit = (bool)jtk["External Airlock / ODS Kit"];
			{
				string strtmp = (string)jtk["Airlock"];
				if (strtmp == Defs.strInternal) Airlock = Defs.strInternal;
				else if (strtmp == Defs.strExternal) Airlock = Defs.strExternal;
				{
					// TODO kaput
				}
			}
			{
				string strtmp = (string)jtk["TAA"];
				if (strtmp == Defs.strNone) TAA = Defs.strNone;
				else if (strtmp == Defs.strForward) TAA = Defs.strForward;
				else if (strtmp == Defs.strAft) TAA = Defs.strAft;
				{
					// TODO kaput
				}
			}
			ODS = (bool)jtk["ODS"];
			FwdBulkDockLights = (bool)jtk["Fwd Bulkhead / Dock Lights"];
			DragChute = (bool)jtk["Drag Chute"];
			PLBLiner = (bool)jtk["PLB Liner"];
			SILTS = (bool)jtk["SILTS"];
			DFIWireTray = (bool)jtk["DFI Wire Tray"];
			VentDoors4and7 = (bool)jtk["Vent Doors 4 and 7"];
			{
				////// CrewModule //////
				JToken jcm = jtk["Crew Module"];
				Crew = (int)jcm["Crew"];

				{
					string strtmp = (string)jcm["Galley"];
					if (strtmp == Defs.strNone) Galley = Defs.strNone;
					else if (strtmp == Defs.strOriginal) Galley = Defs.strOriginal;
					else if (strtmp == Defs.strSORG) Galley = Defs.strSORG;
					{
						// TODO kaput
					}
				}
				{
					string strtmp = (string)jcm["Sleep Stations"];
					if (strtmp == Defs.strNone) SleepStations = Defs.strNone;
					else if (strtmp == "ThreeTier") SleepStations = Defs.strThreeTier;
					else if (strtmp == "FourTier") SleepStations = Defs.strFourTier;
					{
						// TODO kaput
					}
					// TODO for v2 file
					/*string strtmp = (string)jcm["Sleep Stations"];
					if (strtmp == Defs.strNone) SleepStations = Defs.strNone;
					else if (strtmp == Defs.strThreeTier) SleepStations = Defs.strThreeTier;
					else if (strtmp == Defs.strFourTier) SleepStations = Defs.strFourTier;
					{
						// TODO kaput
					}*/
				}
				EjectionSeats = (bool)jcm["Ejection Seats"];
				CrewEscapeHardware = (bool)jcm["Crew Escape Hardware"];
				{
					string strtmp = (string)jcm["Flight Deck"];
					if (strtmp == Defs.strMCDS) FlightDeck = Defs.strMCDS;
					else if (strtmp == Defs.strMEDS) FlightDeck = Defs.strMEDS;
					{
						// TODO kaput
					}
				}
			}
			{
				////// Propellant //////
				JToken jprop = jtk["Propellant"];
				if ((jprop != null) && (jprop.Type != JTokenType.Null))
				{
					FRCS_Load = (double)jprop["FRCS"];
					LRCS_Load = (double)jprop["LRCS"];
					RRCS_Load = (double)jprop["RRCS"];
					LOMS_Load = (double)jprop["LOMS"];
					ROMS_Load = (double)jprop["ROMS"];
				}
			}
			{
				////// PRSD //////
				JToken jprsd = jtk["PRSD"];
				PRSDInternalTanks = (int)jprsd["Internal Tank Sets"];
				JToken jprsdedo = jprsd["EDO Kit"];
				if ((jprsdedo != null) && (jprsdedo.Type != JTokenType.Null))
				{
					EDOKit = true;

					string strtmp = (string)jprsdedo["Pallet"];
					if (strtmp == "Single") EDOPallet = 1;
					else if (strtmp == "Dual") EDOPallet = 2;
					else /*if (strtmp == "None")*/ EDOPallet = 0;
				}
				else
				{
					EDOKit = false;
					EDOPallet = 0;
				}
			}
			{
				////// TODO ECLSS //////
			}
			{
				////// Payload Bay //////
				JToken jplb = jtk["Payload Bay"];

				//// Payloads ////
				JToken jpl = jplb["Payloads"];
				if (jpl != null)
				{
					int activeidx = 0;
					int passiveidx = 0;
					int baybridgeidx = 0;
					List<JToken> jpll = jpl.ToObject<List<JToken>>();
					foreach (JToken jpllitem in jpll)
					{
						// find attachment type
						JToken jactive = jpllitem["Active"];
						JToken jpassive = jpllitem["Passive"];
						JToken jbaybridge = jpllitem["Bay Bridge"];

						if ((jactive != null) && (jactive.Type != JTokenType.Null))
						{
							if (activeidx < PAYLOAD_ACTIVE_MAX)
							{
								PL_Active[activeidx].Load_V1( jpllitem );
								activeidx++;
							}
							else
							{
								// TODO kaput
							}
						}
						else if ((jpassive != null) && (jpassive.Type != JTokenType.Null))
						{
							if (passiveidx < PAYLOAD_PASSIVE_MAX)
							{
								PL_Passive[passiveidx].Load_V1( jpllitem );
								passiveidx++;
							}
							else
							{
								// TODO kaput
							}
						}
						else if ((jbaybridge != null) && (jbaybridge.Type != JTokenType.Null))
						{
							if (baybridgeidx < PAYLOAD_BAYBRIDGE_MAX)
							{
								PL_BayBridge[baybridgeidx].Load_V1( jpllitem );
								baybridgeidx++;
							}
							else
							{
								// TODO kaput
							}
						}
						else
						{
							// TODO kaput
						}
					}
				}

				//// Upper Stage Cradles ////
				JToken jusc = jplb["Upper Stage Cradles"];
				int idx_smallupperstagecradle = 0;
				if (jusc != null)
				{
					List<JToken> juscl = jusc.ToObject<List<JToken>>();
					foreach (JToken jusclitem in juscl)
					{
						// large upper stage cradle
						JToken jius = jusclitem["IUS 2-Stage ASE"];
						JToken jcg = jusclitem["CISS G"];
						JToken jcgp = jusclitem["CISS G-Prime"];

						if (((jius != null) && (jius.Type != JTokenType.Null)) ||
							((jcg != null) && (jcg.Type != JTokenType.Null)) ||
							((jcgp != null) && (jcgp.Type != JTokenType.Null)))
						{
							// upper stage cradle params
							if ((jius != null) && (jius.Type != JTokenType.Null))
							{
								// IUS
								IUS_AftPosition = (bool)jius["Aft Position"];

								JToken jiuslatch = jius["Port Latch"];
								int pl = (int)jiuslatch["Payload"];
								int ltch = (int)jiuslatch["Latch"];
								LargeUpperStage_Latch[0] = ((pl - 1) * 5) + ltch - 1;

								jiuslatch = jius["Starboard Latch"];
								pl = (int)jiuslatch["Payload"];
								ltch = (int)jiuslatch["Latch"];
								LargeUpperStage_Latch[1] = ((pl - 1) * 5) + ltch - 1;
							}
							else if ((jcg != null) && (jcg.Type != JTokenType.Null))
							{
								// Centaur G
								JToken jcglatch = jcg["Port Latch"];
								int pl = (int)jcglatch["Payload"];
								int ltch = (int)jcglatch["Latch"];
								LargeUpperStage_Latch[0] = ((pl - 1) * 5) + ltch - 1;

								jcglatch = jcg["Starboard Latch"];
								pl = (int)jcglatch["Payload"];
								ltch = (int)jcglatch["Latch"];
								LargeUpperStage_Latch[1] = ((pl - 1) * 5) + ltch - 1;

								jcglatch = jcg["Keel Latch"];
								pl = (int)jcglatch["Payload"];
								ltch = (int)jcglatch["Latch"];
								LargeUpperStage_Latch[2] = ((pl - 1) * 5) + ltch - 1;
							}
							else /*else if ((jcgp != null) && (jcgp.Type != JTokenType.Null))*/
							{
								// Centaur G-Prime
								JToken jcgplatch = jcgp["Port Latch"];
								int pl = (int)jcgplatch["Payload"];
								int ltch = (int)jcgplatch["Latch"];
								LargeUpperStage_Latch[0] = ((pl - 1) * 5) + ltch - 1;

								jcgplatch = jcgp["Starboard Latch"];
								pl = (int)jcgplatch["Payload"];
								ltch = (int)jcgplatch["Latch"];
								LargeUpperStage_Latch[1] = ((pl - 1) * 5) + ltch - 1;

								jcgplatch = jcgp["Keel Latch"];
								pl = (int)jcgplatch["Payload"];
								ltch = (int)jcgplatch["Latch"];
								LargeUpperStage_Latch[2] = ((pl - 1) * 5) + ltch - 1;
							}
						}
						else if (idx_smallupperstagecradle < Defs.SMALLUPPERSTAGE_MAX)
						{
							// small upper stage
							JToken jpamd = jusclitem["PAM-D ASE"];
							JToken jpamdii = jusclitem["PAM-DII ASE"];
							JToken jpama = jusclitem["PAM-A ASE"];

							if (((jpamd != null) && (jpamd.Type != JTokenType.Null)) ||
								((jpamdii != null) && (jpamdii.Type != JTokenType.Null)) ||
								((jpama != null) && (jpama.Type != JTokenType.Null)))
							{
								// upper stage unique params
								if ((jpamd != null) && (jpamd.Type != JTokenType.Null))
								{
									// PAM-D
									SmallUpperStage_ASEPLID[idx_smallupperstagecradle] = (int)jpamd["PLID"];
									SmallUpperStage_LargeSunshield[idx_smallupperstagecradle] = (bool)jpamd["Large Sunshield"];
								}
								else if ((jpamdii != null) && (jpamdii.Type != JTokenType.Null))
								{
									// PAM-DII
									SmallUpperStage_ASEPLID[idx_smallupperstagecradle] = (int)jpamdii["PLID"];
									SmallUpperStage_LargeSunshield[idx_smallupperstagecradle] = (bool)jpamdii["Large Sunshield"];
								}
								else /*if ((jpama != null) && (jpama.Type != JTokenType.Null))*/
								{
									// PAM-A
									SmallUpperStage_ASEPLID[idx_smallupperstagecradle] = (int)jpama["PLID"];
								}

								idx_smallupperstagecradle++;
							}
						}
					}

				}

				//// Port Longeron Sill ////
				JToken jpls = jplb["Port Longeron Sill"];
				JToken jplsrms = jpls["RMS"];
				JToken jplsspds = jpls["SPDS"];
				if (jplsrms != null)
				{
					PortLongeronSill = LongeronSillHardware_Type.RMS;
					Port_RMS.Load_V1( jplsrms );
				}
				else if (jplsspds != null)
				{
					PortLongeronSill = LongeronSillHardware_Type.SPDS;
					Port_SPDS.Load_V1( jplsspds );
				}
				else PortLongeronSill = LongeronSillHardware_Type.None;

				//// Starboard Longeron Sill ////
				JToken jsls = jplb["Starboard Longeron Sill"];
				JToken jspl = jsls["Payload MPM"];
				if (jspl != null)
				{
					StbdLongeronSill = LongeronSillHardware_Type.PayloadMPM;
					Stbd_PL_MPM.Load_V1( jspl );
				}
				else StbdLongeronSill = LongeronSillHardware_Type.None;

				//// Cameras ////
				JToken jcctv = jplb["Cameras"];
				if (jcctv != null)
				{
					PLB_Cameras.Load_V1( jcctv );
				}
			}
			{
				////// DPS //////
				JToken jdps = jtk["DPS"];
				string lstmp = (string)jdps["Landing Site Table"];
				if (lstmp != null)
				{
					// parse landing site line
					string[] lslistentry = lstmp.Split( '\n' );
					if (lslistentry.Length != 45)
					{
						// TODO error msg?
					}
					foreach (string lsentry in lslistentry)
					{
						// parse runways
						// "1,KSC15,KSC33\r\n"
						string[] ls = lsentry.Split( ',' );
						if (ls.Length != 3)
						{
							// TODO error msg?
						}
						int LSID = int.Parse( ls[0] );// LSID
						// TODO validate LSID
						Tuple<string,string> tp = new Tuple<string,string>( ls[1]/*pri*/, ls[2].TrimEnd('\r')/*sec (with \r)*/ );
						LandingSiteTable[LSID - 1] = tp;
					}
				}
				// read iloads and update list
				JToken jiloads = jdps["I-load"];
				List<Mission_ILOAD> iloadlist = jiloads.ToObject<List<Mission_ILOAD>>();
				foreach (Mission_ILOAD newiload in iloadlist)
				{
					foreach (Mission_ILOAD curiload in ILOAD_List)
					{
						if (curiload.ID == newiload.ID)
						{
							curiload.Val = newiload.Val;
							break;
						}
					}
				}
				string tvtmp = (string)jdps["Target Vessel"];
				if (tvtmp != null) TgtVessel = tvtmp;
			}
			{
				////// MPS //////
				JToken jmps = jtk["MPS"];
				SSME[0].Load_V1( jmps["SSME-1"] );
				SSME[1].Load_V1( jmps["SSME-2"] );
				SSME[2].Load_V1( jmps["SSME-3"] );
			}
			return;
		}

		public JObject Save_V1()
		{
			JObject jobj = new JObject();

			jobj["Name"] = Name;
			jobj["Texture"] = Texture;
			jobj["LOMS Pod Texture"] = LOMStex;
			jobj["ROMS Pod Texture"] = ROMStex;
			jobj["Ku-band Antenna"] = KubandAntenna;
			jobj["External Airlock / ODS Kit"] = ExtAL_ODS_Kit;
			jobj["Airlock"] = Airlock;
			jobj["TAA"] = TAA;
			jobj["ODS"] = ODS;
			jobj["Fwd Bulkhead / Dock Lights"] = FwdBulkDockLights;
			jobj["Drag Chute"] = DragChute;
			jobj["PLB Liner"] = PLBLiner;
			jobj["SILTS"] = SILTS;
			jobj["DFI Wire Tray"] = DFIWireTray;
			jobj["Vent Doors 4 and 7"] = VentDoors4and7;
			{
				////// CrewModule //////
				JObject jcm = new JObject();
				jcm["Crew"] = Crew;
				jcm["Galley"] = Galley;

				if (SleepStations == Defs.strNone) jcm["Sleep Stations"] = Defs.strNone;
				else if (SleepStations == Defs.strThreeTier) jcm["Sleep Stations"] = "ThreeTier";
				else if (SleepStations == Defs.strFourTier) jcm["Sleep Stations"] = "FourTier";
				else
				{
					// TODO kaput
				}
				// TODO for v2 file
				//jcm["Sleep Stations"] = SleepStations;

				jcm["Ejection Seats"] = EjectionSeats;
				jcm["Crew Escape Hardware"] = CrewEscapeHardware;
				jcm["Flight Deck"] = FlightDeck;

				jobj["Crew Module"] = jcm;
			}
			{
				////// Propellant //////
				JObject jprop = new JObject()
				{
					["FRCS"] = FRCS_Load,
					["LRCS"] = LRCS_Load,
					["RRCS"] = RRCS_Load,
					["LOMS"] = LOMS_Load,
					["ROMS"] = ROMS_Load
				};
				jobj["Propellant"] = jprop;
			}
			{
				////// PRSD //////
				JObject jprsd = new JObject();
				jprsd["Internal Tank Sets"] = PRSDInternalTanks;
				if (EDOKit)
				{
					jprsd["EDO Kit"] = new JObject
					{
						["Pallet"] = (EDOPallet == 1) ? "Single" : ((EDOPallet == 2) ? "Dual" : "None")
					};
				}
				else jprsd["EDO Kit"] = null;
				jobj["PRSD"] = jprsd;
			}
			{
				////// TODO ECLSS //////
				jobj["ECLSS"] = null;
			}
			{
				////// PayloadBay //////
				JObject jplb = new JObject();

				{
					//// Payloads ////
					JArray jpayloads = new JArray();

					// active
					for (int i = 0; i < PAYLOAD_ACTIVE_MAX; i++)
					{
						JObject jplactive = PL_Active[i].Save_V1();
						if (jplactive != null) jpayloads.Add( jplactive );
					}

					// passive
					for (int i = 0; i < PAYLOAD_PASSIVE_MAX; i++)
					{
						JObject jplpassive = PL_Passive[i].Save_V1();
						if (jplpassive != null) jpayloads.Add( jplpassive );
					}

					// bay bridge
					for (int i = 0; i < PAYLOAD_BAYBRIDGE_MAX; i++)
					{
						JObject jplbaybridge = PL_BayBridge[i].Save_V1();
						if (jplbaybridge != null) jpayloads.Add( jplbaybridge );
					}

					jplb["Payloads"] = jpayloads;
				}


				//// UpperStageCradles ////
				JArray jusc = new JArray();
				if (mission.LargeUpperStage == 1)// IUS
				{
					JObject jiusase = new JObject();
					JObject jiusase2 = new JObject();
					jiusase["IUS 2-Stage ASE"] = jiusase2;

					JObject jlusltch0 = new JObject();
					int pl = (LargeUpperStage_Latch[0] / 5) + 1;
					int ltch = (LargeUpperStage_Latch[0] - (5 * (pl - 1))) + 1;
					jlusltch0["Payload"] = pl;
					jlusltch0["Latch"] = ltch;

					JObject jlusltch1 = new JObject();
					pl = (LargeUpperStage_Latch[1] / 5) + 1;
					ltch = (LargeUpperStage_Latch[1] - (5 * (pl - 1))) + 1;
					jlusltch1["Payload"] = pl;
					jlusltch1["Latch"] = ltch;

					jiusase2["Aft Position"] = IUS_AftPosition;
					jiusase2["Port Latch"] = jlusltch0;
					jiusase2["Starboard Latch"] = jlusltch1;
					jusc.Add( jiusase );
				}
				else if (mission.LargeUpperStage == 4)// Centaur G
				{
					JObject jcissg = new JObject();
					JObject jcissg2 = new JObject();
					jcissg["CISS G"] = jcissg2;

					JObject jlusltch0 = new JObject();
					int pl = (LargeUpperStage_Latch[0] / 5) + 1;
					int ltch = (LargeUpperStage_Latch[0] - (5 * (pl - 1))) + 1;
					jlusltch0["Payload"] = pl;
					jlusltch0["Latch"] = ltch;

					JObject jlusltch1 = new JObject();
					pl = (LargeUpperStage_Latch[1] / 5) + 1;
					ltch = (LargeUpperStage_Latch[1] - (5 * (pl - 1))) + 1;
					jlusltch1["Payload"] = pl;
					jlusltch1["Latch"] = ltch;

					JObject jlusltch2 = new JObject();
					pl = (LargeUpperStage_Latch[2] / 5) + 1;
					ltch = (LargeUpperStage_Latch[2] - (5 * (pl - 1))) + 1;
					jlusltch2["Payload"] = pl;
					jlusltch2["Latch"] = ltch;

					jcissg2["Port Latch"] = jlusltch0;
					jcissg2["Starboard Latch"] = jlusltch1;
					jcissg2["Keel Latch"] = jlusltch2;
					jusc.Add( jcissg );
				}
				else if (mission.LargeUpperStage == 5)// Centaur G-Prime
				{
					JObject jcissgp = new JObject();
					JObject jcissgp2 = new JObject();
					jcissgp["CISS G-Prime"] = jcissgp2;

					JObject jlusltch0 = new JObject();
					int pl = (LargeUpperStage_Latch[0] / 5) + 1;
					int ltch = (LargeUpperStage_Latch[0] - (5 * (pl - 1))) + 1;
					jlusltch0["Payload"] = pl;
					jlusltch0["Latch"] = ltch;

					JObject jlusltch1 = new JObject();
					pl = (LargeUpperStage_Latch[1] / 5) + 1;
					ltch = (LargeUpperStage_Latch[1] - (5 * (pl - 1))) + 1;
					jlusltch1["Payload"] = pl;
					jlusltch1["Latch"] = ltch;

					JObject jlusltch2 = new JObject();
					pl = (LargeUpperStage_Latch[2] / 5) + 1;
					ltch = (LargeUpperStage_Latch[2] - (5 * (pl - 1))) + 1;
					jlusltch2["Payload"] = pl;
					jlusltch2["Latch"] = ltch;

					jcissgp2["Port Latch"] = jlusltch0;
					jcissgp2["Starboard Latch"] = jlusltch1;
					jcissgp2["Keel Latch"] = jlusltch2;
					jusc.Add( jcissgp );
				}
				for (int i = 0; i < Defs.SMALLUPPERSTAGE_MAX; i++)
				{
					if (mission.SmallUpperStage[i] == 1)// PAM-D
					{
						JObject jpamd = new JObject
						{
							["PAM-D ASE"] = new JObject()
							{
								["PLID"] = SmallUpperStage_ASEPLID[i],
								["Large Sunshield"] = SmallUpperStage_LargeSunshield[i]
							}
						};
						jusc.Add( jpamd );
					}
					else if (mission.SmallUpperStage[i] == 2)// PAM-DII
					{
						JObject jpamdii = new JObject()
						{
							["PAM-DII ASE"] = new JObject()
							{
								["PLID"] = SmallUpperStage_ASEPLID[i],
								["Large Sunshield"] = SmallUpperStage_LargeSunshield[i]
							}
						};
						jusc.Add( jpamdii );
					}
					else if (mission.SmallUpperStage[i] == 3)// PAM-A
					{
						JObject jpama = new JObject()
						{
							["PAM-A ASE"] = new JObject()
							{
								["PLID"] = SmallUpperStage_ASEPLID[i]
							}
						};
						jusc.Add( jpama );
					}
				}
				jplb["Upper Stage Cradles"] = jusc;

				//// Port Longeron Sill ////
				JObject jpls = new JObject();
				if (PortLongeronSill == LongeronSillHardware_Type.RMS)
				{
					jpls["RMS"] = Port_RMS.Save_V1();
				}
				else if (PortLongeronSill == LongeronSillHardware_Type.SPDS)
				{
					jpls["SPDS"] = Port_SPDS.Save_V1();
				}
				jplb["Port Longeron Sill"] = jpls;

				//// Starboard Longeron Sill ////
				JObject jsls = new JObject();
				if (StbdLongeronSill == LongeronSillHardware_Type.PayloadMPM)
				{
					jsls["Payload MPM"] = Stbd_PL_MPM.Save_V1();
				}
				jplb["Starboard Longeron Sill"] = jsls;

				//// Cameras ////
				jplb["Cameras"] = PLB_Cameras.Save_V1();
				jobj["Payload Bay"] = jplb;
			}
			{
				////// DPS //////
				JObject jdps = new JObject();
				string lslist = "";
				for (int i = 0; i < 45; i++)
				{
					lslist += (i + 1) + "," + LandingSiteTable[i].Item1 + "," + LandingSiteTable[i].Item2 + ((i == 44) ? "" : "\r\n");
				}
				jdps["Landing Site Table"] = lslist;
				jdps["I-load"] = JToken.FromObject( ILOAD_List );
				jdps["Target Vessel"] = TgtVessel;
				jobj["DPS"] = jdps;
			}
			{
				////// MPS //////
				JObject jtmps = new JObject();
				jtmps["SSME-1"] = SSME[0].Save_V1();
				jtmps["SSME-2"] = SSME[1].Save_V1();
				jtmps["SSME-3"] = SSME[2].Save_V1();
				jobj["MPS"] = jtmps;
			}
			return jobj;
		}


		/// <summary>
		/// Name of OV used in this mission
		/// </summary>
		public string Name { get; set; }

		/// <summary>
		/// The name of the OV texture
		/// </summary>
		public string Texture { get; set; }

		/// <summary>
		/// The name of the left OMS pod texture
		/// </summary>
		public string LOMStex { get; set; }

		/// <summary>
		/// The name of the right OMS pod texture
		/// </summary>
		public string ROMStex { get; set; }

		/// <summary>
		/// Is the Ku-band Antenna installed
		/// </summary>
		public bool KubandAntenna { get; set; }

		/// <summary>
		/// Is the External Airlock / ODS Kit installed
		/// </summary>
		public bool ExtAL_ODS_Kit { get; set; }

		/// <summary>
		/// Is the ODS installed
		/// </summary>
		public bool ODS { get; set; }

		/// <summary>
		/// Is the TAA installed and where
		/// </summary>
		public string TAA { get; set; }

		/// <summary>
		/// Where is the Airlock installed
		/// </summary>
		public string Airlock { get; set; }

		/// <summary>
		/// Are the forward bulkhead and docking lights installed
		/// </summary>
		public bool FwdBulkDockLights { get; set; }

		/// <summary>
		/// Is the Drag Chute installed
		/// </summary>
		public bool DragChute { get; set; }

		/// <summary>
		/// Is the Payload Bay Liner installed
		/// </summary>
		public bool PLBLiner { get; set; }

		/// <summary>
		/// Is the SILTS pod installed
		/// </summary>
		public bool SILTS { get; set; }

		/// <summary>
		/// Is the DFI Wire Tray installed
		/// </summary>
		public bool DFIWireTray { get; set; }

		/// <summary>
		/// Are the Vent Doors 4 and 7 installed
		/// </summary>
		public bool VentDoors4and7 { get; set; }

		/// <summary>
		/// Number of crew members
		/// </summary>
		public int Crew { get; set; }

		/// <summary>
		/// Type of Galley installed
		/// </summary>
		public string Galley { get; set; }

		/// <summary>
		/// Type of Sleep Stations installed
		/// </summary>
		public string SleepStations { get; set; }

		/// <summary>
		/// Are Ejection Seats installed
		/// </summary>
		public bool EjectionSeats { get; set; }

		/// <summary>
		/// Is Crew Escape Hardware installed
		/// </summary>
		public bool CrewEscapeHardware { get; set; }

		/// <summary>
		/// Type of Flight Deck
		/// </summary>
		public string FlightDeck { get; set; }

		public double FRCS_Load { get; set; }

		public double LRCS_Load { get; set; }

		public double RRCS_Load { get; set; }

		public double LOMS_Load { get; set; }

		public double ROMS_Load { get; set; }

		public double KOMS_Load { get; set; }

		public int OMSKitTanks { get; set; }

		public int PRSDInternalTanks { get; set; }

		public bool EDOKit { get; set; }

		public int EDOPallet { get; set; }

		public Mission_PLActive[] PL_Active { get; set; }

		public Mission_PLPassive[] PL_Passive { get; set; }

		public Mission_PLBayBridge[] PL_BayBridge { get; set; }

		public int[] LargeUpperStage_Latch { get; set; }

		/// <summary>
		/// IUS ASE is installed in aft position
		/// </summary>
		public bool IUS_AftPosition { get; set; }


		/// <summary>
		/// Hardware installed on Port Longeron Sill
		/// </summary>
		public LongeronSillHardware_Type PortLongeronSill { get; set; }

		/// <summary>
		/// Port RMS
		/// </summary>
		public Mission_RMS Port_RMS { get; set; }

		/// <summary>
		/// Port Payload MPM
		/// </summary>
		public Mission_PL_MPM Port_PL_MPM { get; set; }

		/// <summary>
		/// Port SPDS
		/// </summary>
		public Mission_SPDS Port_SPDS { get; set; }

		/// <summary>
		/// Hardware installed on Starboard Longeron Sill
		/// </summary>
		public LongeronSillHardware_Type StbdLongeronSill { get; set; }

		/// <summary>
		/// Starboard RMS
		/// </summary>
		public Mission_RMS Stbd_RMS { get; set; }

		/// <summary>
		/// Starboard Payload MPM
		/// </summary>
		public Mission_PL_MPM Stbd_PL_MPM { get; set; }

		/// <summary>
		/// Starboard SPDS
		/// </summary>
		public Mission_SPDS Stbd_SPDS { get; set; }

		/// <summary>
		/// PLID (keel) of "small" upper stage ASEs
		/// </summary>
		public int[] SmallUpperStage_ASEPLID { get; set; }

		/// <summary>
		/// ASE for "small" upper stages has large Sunshield (PAM-D and PAM-DII only)
		/// </summary>
		public bool[] SmallUpperStage_LargeSunshield { get; set; }

		public ObservableCollection<Mission_ILOAD> ILOAD_List { get; set; }

		/// <summary>
		/// SSMEs
		/// </summary>
		public Mission_SSME[] SSME { get; set; }

		/// <summary>
		/// Landing site table file
		/// </summary>
		public List<Tuple<string,string>> LandingSiteTable { get; set; }

		/// <summary>
		/// The name of the target vessel
		/// </summary>
		public string TgtVessel { get; set; }

		/// <summary>
		/// Data of PLB CCTV cameras
		/// </summary>
		public Mission_PLB_Camera PLB_Cameras { get; set; }


		readonly Mission mission;
	}
}
