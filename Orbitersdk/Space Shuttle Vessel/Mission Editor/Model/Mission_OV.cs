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
********************************************/

using System;
using System.ComponentModel;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using System.IO;


namespace SSVMissionEditor.model
{
	public enum OV_Name
	{
		Columbia = 0,
		Challenger,
		Discovery,
		Atlantis,
		Endeavour
	}

	public enum TAA_Type
	{
		None = 0,
		Forward,
		Aft
	}

	public enum Airlock_Type
	{
		Internal = 0,
		External
	}

	public enum Galley_Type
	{
		None = 0,
		Original,
		SORG
	}

	public enum SleepStations_Type
	{
		None = 0,
		ThreeTier,
		FourTier
	}

	public enum FlightDeck_Type
	{
		MCDS = 0,
		MEDS
	}

	public enum LongeronSillHardware_Type
	{
		None = 0,
		RMS,
		PayloadMPM,
		SPDS
	}

	public enum CCTV_Camera_Type
	{
		_506_508 = 0,
		CTVC_ITVC
	}

	public struct PLB_Camera
	{
		public bool Installed;
		public CCTV_Camera_Type Type;
		public bool Custom;
		public double Xo;
		public double Yo;
		public double Zo;
		public double Rot;
	}


	public class Mission_OV : INotifyPropertyChanged
	{
		private const string lsDBfilepath = "Config\\SSV_RunwayDB.csv";

		public struct LandingSiteData
		{
			public string id;
			public string sitename;
			public string rwname;
			public string lat;// [rad]
			public string lon;// [rad]
			public string amsl;// [m]
			public string hdg;// [deg]
			public string lgt;// [ft]
		}

		public static readonly int PAYLOAD_ACTIVE_MAX = 5;// maximum number of "active" PLB payloads
		public static readonly int PAYLOAD_PASSIVE_MAX = 5;// maximum number of "passive" PLB payloads
		public static readonly int PAYLOAD_BAYBRIDGE_MAX = 8;// maximum number of "bay bridge" PLB payloads

		public static readonly int PAYLOADLATCH_MAX = 12;// maximum number of latches per PLB payload

		public static readonly int KEEL_CAMERA_MAX = 1;// maximum number of keel cameras


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

			ILOAD_List = new List<Mission_ILOAD>();

			SSME = new Mission_SSME[3];
			SSME[0] = new Mission_SSME();
			SSME[1] = new Mission_SSME();
			SSME[2] = new Mission_SSME();

			landingsitetable = new List<Tuple<string,string>>();

			landingsitedb = new List<LandingSiteData>();
			LoadLandingSiteDB( orbiterpath );

			PLB_Cameras = new PLB_Camera[4];
			for (int i = 0; i < 4; i++)
			{
				PLB_Cameras[i].Installed = true;
				PLB_Cameras[i].Type = CCTV_Camera_Type.CTVC_ITVC;
				PLB_Cameras[i].Custom = false;
				PLB_Cameras[i].Xo = 0.0;
				PLB_Cameras[i].Yo = 0.0;
				PLB_Cameras[i].Zo = 0.0;
				PLB_Cameras[i].Rot = 0.0;
			}

			Keel_Cameras = new int[KEEL_CAMERA_MAX];
			for (int i = 0; i < KEEL_CAMERA_MAX; i++) Keel_Cameras[i] = 0;

			LoadDefault();
		}

		public void LoadDefault()
		{
			Name = OV_Name.Atlantis;
			Texture = "OV-104_5thmod";
			LOMStex = "OMSpod_7thmod";
			ROMStex = "OMSpod_7thmod";
			KubandAntenna = true;
			ExtAL_ODS_Kit = true;
			ODS = true;
			TAA = TAA_Type.None;
			Airlock = Airlock_Type.External;
			FwdBulkDockLights = true;
			DragChute = true;
			PLBLiner = false;
			SILTS = false;
			DFIWireTray = false;
			VentDoors4and7 = false;

			Crew = 7;
			Galley = Galley_Type.SORG;
			SleepStations = SleepStations_Type.None;
			EjectionSeats = false;
			CrewEscapeHardware = true;
			FlightDeck = FlightDeck_Type.MEDS;

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
			StbdLongeronSill = LongeronSillHardware_Type.None;
			Stbd_RMS.LoadDefault();
			Stbd_PL_MPM.LoadDefault();

			ILOAD_List = Mission_ILOAD.LoadDefault();

			foreach (Mission_SSME me in SSME) me.LoadDefault();

			landingsitetable.Clear();
			landingsitetable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			landingsitetable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			landingsitetable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 3
			landingsitetable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 4
			landingsitetable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 5
			landingsitetable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 6
			landingsitetable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 7
			landingsitetable.Add( new Tuple<string,string>( "NTU32R", "NTU23L" ) );// 8
			landingsitetable.Add( new Tuple<string,string>( "WAL28", "WAL04" ) );// 9
			landingsitetable.Add( new Tuple<string,string>( "DOV32", "DOV19" ) );// 10
			landingsitetable.Add( new Tuple<string,string>( "ACY31", "ACY13" ) );// 11
			landingsitetable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 12
			landingsitetable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 13
			landingsitetable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 14
			landingsitetable.Add( new Tuple<string,string>( "FOK06", "FOK24" ) );// 15
			landingsitetable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 16
			landingsitetable.Add( new Tuple<string,string>( "PSM34", "PSM16" ) );// 17
			landingsitetable.Add( new Tuple<string,string>( "YHZ23", "YHZ32" ) );// 18
			landingsitetable.Add( new Tuple<string,string>( "YJT09", "YJT27" ) );// 19
			landingsitetable.Add( new Tuple<string,string>( "YYT29", "YYT11" ) );// 20
			landingsitetable.Add( new Tuple<string,string>( "YQX21", "YQX31" ) );// 21
			landingsitetable.Add( new Tuple<string,string>( "BYD32", "BYD14" ) );// 22
			landingsitetable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 23
			landingsitetable.Add( new Tuple<string,string>( "VBG30", "VBG12" ) );// 24
			landingsitetable.Add( new Tuple<string,string>( "IKF20", "IKF29" ) );// 25
			landingsitetable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			landingsitetable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			landingsitetable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			landingsitetable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			landingsitetable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			landingsitetable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			landingsitetable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			landingsitetable.Add( new Tuple<string,string>( "AMB15", "PTN14" ) );// 33
			landingsitetable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 34
			landingsitetable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 35
			landingsitetable.Add( new Tuple<string,string>( "BDA30", "BDA12" ) );// 36
			landingsitetable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 37
			landingsitetable.Add( new Tuple<string,string>( "EIP28", "EIP10" ) );// 38
			landingsitetable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 39
			landingsitetable.Add( new Tuple<string,string>( "AWG25", "AWG07" ) );// 40
			landingsitetable.Add( new Tuple<string,string>( "HAW31", "HAW13" ) );// 41
			landingsitetable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 42
			landingsitetable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 43
			landingsitetable.Add( new Tuple<string,string>( "EDW15", "EDW18L" ) );// 44
			landingsitetable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45

			TgtVessel = "ISS";

			for (int i = 0; i < 4; i++)
			{
				PLB_Cameras[i].Installed = true;
				PLB_Cameras[i].Type = CCTV_Camera_Type.CTVC_ITVC;
				PLB_Cameras[i].Custom = false;
				PLB_Cameras[i].Xo = 0.0;
				PLB_Cameras[i].Yo = 0.0;
				PLB_Cameras[i].Zo = 0.0;
				PLB_Cameras[i].Rot = 0.0;
			}

			Keel_Cameras[0] = 0;
			return;
		}

		public void LoadEmpty()
		{
			Name = OV_Name.Atlantis;
			Texture = "OV-104_5thmod";
			LOMStex = "OMSpod_7thmod";
			ROMStex = "OMSpod_7thmod";
			KubandAntenna = true;
			ExtAL_ODS_Kit = false;
			ODS = false;
			TAA = TAA_Type.None;
			Airlock = Airlock_Type.Internal;
			FwdBulkDockLights = true;
			DragChute = true;
			PLBLiner = false;
			SILTS = false;
			DFIWireTray = false;
			VentDoors4and7 = false;

			Crew = 7;
			Galley = Galley_Type.SORG;
			SleepStations = SleepStations_Type.None;
			EjectionSeats = false;
			CrewEscapeHardware = true;
			FlightDeck = FlightDeck_Type.MEDS;

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
			StbdLongeronSill = LongeronSillHardware_Type.None;
			Stbd_RMS.LoadEmpty();
			Stbd_PL_MPM.LoadEmpty();

			ILOAD_List = Mission_ILOAD.LoadDefault();

			foreach (Mission_SSME me in SSME) me.LoadEmpty();

			landingsitetable.Clear();
			landingsitetable.Add( new Tuple<string,string>( "KSC15", "KSC33" ) );// 1
			landingsitetable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 2
			landingsitetable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 3
			landingsitetable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 4
			landingsitetable.Add( new Tuple<string,string>( "MYR36", "MYR18" ) );// 5
			landingsitetable.Add( new Tuple<string,string>( "ILM06", "ILM24" ) );// 6
			landingsitetable.Add( new Tuple<string,string>( "NKT32L", "NKT23R" ) );// 7
			landingsitetable.Add( new Tuple<string,string>( "NTU32R", "NTU23L" ) );// 8
			landingsitetable.Add( new Tuple<string,string>( "WAL28", "WAL04" ) );// 9
			landingsitetable.Add( new Tuple<string,string>( "DOV32", "DOV19" ) );// 10
			landingsitetable.Add( new Tuple<string,string>( "ACY31", "ACY13" ) );// 11
			landingsitetable.Add( new Tuple<string,string>( "BEN36", "BEN18" ) );// 12
			landingsitetable.Add( new Tuple<string,string>( "MRN20", "MRN02" ) );// 13
			landingsitetable.Add( new Tuple<string,string>( "ZZA30L", "ZZA12R" ) );// 14
			landingsitetable.Add( new Tuple<string,string>( "FOK06", "FOK24" ) );// 15
			landingsitetable.Add( new Tuple<string,string>( "FMH32", "FMH23" ) );// 16
			landingsitetable.Add( new Tuple<string,string>( "PSM34", "PSM16" ) );// 17
			landingsitetable.Add( new Tuple<string,string>( "YHZ23", "YHZ32" ) );// 18
			landingsitetable.Add( new Tuple<string,string>( "YJT09", "YJT27" ) );// 19
			landingsitetable.Add( new Tuple<string,string>( "YYT29", "YYT11" ) );// 20
			landingsitetable.Add( new Tuple<string,string>( "YQX21", "YQX31" ) );// 21
			landingsitetable.Add( new Tuple<string,string>( "BYD32", "BYD14" ) );// 22
			landingsitetable.Add( new Tuple<string,string>( "LAJ15", "LAJ33" ) );// 23
			landingsitetable.Add( new Tuple<string,string>( "VBG30", "VBG12" ) );// 24
			landingsitetable.Add( new Tuple<string,string>( "IKF20", "IKF29" ) );// 25
			landingsitetable.Add( new Tuple<string,string>( "INN06", "INN24" ) );// 26
			landingsitetable.Add( new Tuple<string,string>( "FFA27", "FFA09" ) );// 27
			landingsitetable.Add( new Tuple<string,string>( "KBO14L", "KBO32R" ) );// 28
			landingsitetable.Add( new Tuple<string,string>( "FMI33", "FMI15" ) );// 29
			landingsitetable.Add( new Tuple<string,string>( "ESN03R", "ESN21L" ) );// 30
			landingsitetable.Add( new Tuple<string,string>( "KKI15R", "KKI33L" ) );// 31
			landingsitetable.Add( new Tuple<string,string>( "JDG31", "JDG13" ) );// 32
			landingsitetable.Add( new Tuple<string,string>( "AMB15", "PTN14" ) );// 33
			landingsitetable.Add( new Tuple<string,string>( "JTY36", "JTY18" ) );// 34
			landingsitetable.Add( new Tuple<string,string>( "GUA06L", "GUA24R" ) );// 35
			landingsitetable.Add( new Tuple<string,string>( "BDA30", "BDA12" ) );// 36
			landingsitetable.Add( new Tuple<string,string>( "HNL08R", "HNL26L" ) );// 37
			landingsitetable.Add( new Tuple<string,string>( "EIP28", "EIP10" ) );// 38
			landingsitetable.Add( new Tuple<string,string>( "HAO12", "HAO30" ) );// 39
			landingsitetable.Add( new Tuple<string,string>( "AWG25", "AWG07" ) );// 40
			landingsitetable.Add( new Tuple<string,string>( "HAW31", "HAW13" ) );// 41
			landingsitetable.Add( new Tuple<string,string>( "NOR17", "NOR23" ) );// 42
			landingsitetable.Add( new Tuple<string,string>( "NOR05", "NOR35" ) );// 43
			landingsitetable.Add( new Tuple<string,string>( "EDW15", "EDW18L" ) );// 44
			landingsitetable.Add( new Tuple<string,string>( "EDW22", "EDW04" ) );// 45

			TgtVessel = "";

			for (int i = 0; i < 4; i++)
			{
				PLB_Cameras[i].Installed = true;
				PLB_Cameras[i].Type = CCTV_Camera_Type.CTVC_ITVC;
				PLB_Cameras[i].Custom = false;
				PLB_Cameras[i].Xo = 0.0;
				PLB_Cameras[i].Yo = 0.0;
				PLB_Cameras[i].Zo = 0.0;
				PLB_Cameras[i].Rot = 0.0;
			}

			Keel_Cameras[0] = 0;
			return;
		}

		private void LoadLandingSiteDB( string orbiterpath )
		{
			string line;
			StreamReader file = new StreamReader( orbiterpath + lsDBfilepath );
			while ((line = file.ReadLine()) != null)
			{
				// format: id,site name,rw name,lat(n)[rad],lon(e)[rad],amsl[m],hdg[deg],lgt[ft]
				string[] items = line.Split( ',' );
				if (items.Length != 8)
				{
					// TODO error msg?
					continue;
				}
				LandingSiteData lsd = new LandingSiteData
				{
					id = items[0],
					sitename = items[1],
					rwname = items[2],
					lat = items[3],
					lon = items[4],
					amsl = items[5],
					hdg = items[6],
					lgt = items[7]
				};

				landingsitedb.Add( lsd );
			}
			file.Close();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			{
				string strtmp = (string)jtk["Name"];
				int inttmp = Mission.String2EnumIdx( Name, strtmp );
				if (inttmp >= 0) Name = (OV_Name)inttmp;
				else Name = OV_Name.Atlantis;
			}
			Texture = (string)jtk["Texture"];
			LOMStex = (string)jtk["LOMS Pod Texture"];
			ROMStex = (string)jtk["ROMS Pod Texture"];
			KubandAntenna = (bool)jtk["Ku-band Antenna"];
			ExtAL_ODS_Kit = (bool)jtk["External Airlock / ODS Kit"];
			{
				string strtmp = (string)jtk["Airlock"];
				int inttmp = Mission.String2EnumIdx( Airlock, strtmp );
				if (inttmp >= 0) Airlock = (Airlock_Type)inttmp;
				else Airlock = Airlock_Type.External;
			}
			{
				string strtmp = (string)jtk["TAA"];
				int inttmp = Mission.String2EnumIdx( TAA, strtmp );
				if (inttmp >= 0) TAA = (TAA_Type)inttmp;
				else TAA = TAA_Type.None;
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

				string strtmp = (string)jcm["Galley"];
				int inttmp = Mission.String2EnumIdx( Galley, strtmp );
				if (inttmp >= 0) Galley = (Galley_Type)inttmp;
				else Galley = Galley_Type.SORG;

				strtmp = (string)jcm["Sleep Stations"];
				inttmp = Mission.String2EnumIdx( SleepStations, strtmp );
				if (inttmp >= 0) SleepStations = (SleepStations_Type)inttmp;
				else SleepStations = SleepStations_Type.None;

				EjectionSeats = (bool)jcm["Ejection Seats"];
				CrewEscapeHardware = (bool)jcm["Crew Escape Hardware"];

				strtmp = (string)jcm["Flight Deck"];
				inttmp = Mission.String2EnumIdx( FlightDeck, strtmp );
				if (inttmp >= 0) FlightDeck = (FlightDeck_Type)inttmp;
				else FlightDeck = FlightDeck_Type.MEDS;
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
				if (jplsrms != null)
				{
					PortLongeronSill = LongeronSillHardware_Type.RMS;
					Port_RMS.Load_V1( jplsrms );
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
					LoadPLBCameras_V1( jcctv, 0, "A" );
					LoadPLBCameras_V1( jcctv, 1, "B" );
					LoadPLBCameras_V1( jcctv, 2, "C" );
					LoadPLBCameras_V1( jcctv, 3, "D" );

					JToken jkeel = jcctv["Keel"];
					if (jkeel != null)
					{
						int idx = 0;
						List<JToken> jkeellist = jkeel.ToObject<List<JToken>>();
						foreach (JToken jkeelcam in jkeellist)
						{
							if (idx >= KEEL_CAMERA_MAX) break;
							Keel_Cameras[idx] = (int)jkeelcam["PLID"];
							idx++;
						}
					}
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

		private void LoadPLBCameras_V1( JToken jcctv, int camidx, string camname )
		{
			JToken jcctvcam = jcctv[camname];
			if (jcctvcam != null)
			{
				PLB_Cameras[camidx].Installed = (bool)jcctvcam["Installed"];
				if (PLB_Cameras[camidx].Installed)
				{
					if ((string)jcctvcam["Type"] == "-506/-508") PLB_Cameras[camidx].Type = CCTV_Camera_Type._506_508;
					else PLB_Cameras[camidx].Type = CCTV_Camera_Type.CTVC_ITVC;
	
					JToken jcustom = jcctvcam["Custom"];
					if (jcustom != null)
					{
						PLB_Cameras[camidx].Custom = true;
						PLB_Cameras[camidx].Xo = (double)jcustom["Xo"];
						PLB_Cameras[camidx].Yo = (double)jcustom["Yo"];
						PLB_Cameras[camidx].Zo = (double)jcustom["Zo"];
						PLB_Cameras[camidx].Rot = (double)jcustom["Rot"];
					}
				}
			}
			return;
		}

		public JObject Save_V1()
		{
			JObject jobj = new JObject();

			jobj["Name"] = Name.ToString();
			jobj["Texture"] = Texture;
			jobj["LOMS Pod Texture"] = LOMStex;
			jobj["ROMS Pod Texture"] = ROMStex;
			jobj["Ku-band Antenna"] = KubandAntenna;
			jobj["External Airlock / ODS Kit"] = ExtAL_ODS_Kit;
			jobj["Airlock"] = Airlock.ToString();
			jobj["TAA"] = TAA.ToString();
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
				jcm["Galley"] = Galley.ToString();
				jcm["Sleep Stations"] = SleepStations.ToString();
				jcm["Ejection Seats"] = EjectionSeats;
				jcm["Crew Escape Hardware"] = CrewEscapeHardware;
				jcm["Flight Deck"] = FlightDeck.ToString();

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
				jplb["Port Longeron Sill"] = jpls;

				//// Starboard Longeron Sill ////
				JObject jsls = new JObject();
				if (StbdLongeronSill == LongeronSillHardware_Type.PayloadMPM)
				{
					jsls["Payload MPM"] = Stbd_PL_MPM.Save_V1();
				}
				jplb["Starboard Longeron Sill"] = jsls;

				//// Cameras ////
				JObject jcctv = new JObject();
				jcctv["A"] = SavePLBCameras_V1( 0 );
				jcctv["B"] = SavePLBCameras_V1( 1 );
				jcctv["C"] = SavePLBCameras_V1( 2 );
				jcctv["D"] = SavePLBCameras_V1( 3 );

				JArray jakeel = new JArray();
				if (Keel_Cameras[0] != 0)
				{
					JObject jkeel = new JObject()
					{
						["PLID"] = Keel_Cameras[0]
					};
					jakeel.Add( jkeel );
				}
				jcctv["Keel"] = jakeel;
				jplb["Cameras"] = jcctv;
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
				jdps["I-load"] = JToken.FromObject( iloads );
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

		private JToken SavePLBCameras_V1( int camidx )
		{
			JObject jcam = new JObject()
			{
				["Installed"] = PLB_Cameras[camidx].Installed
			};

			if (PLB_Cameras[camidx].Installed)
			{
				jcam["Type"] = ((PLB_Cameras[camidx].Type == CCTV_Camera_Type._506_508) ? "-506/-508" : "CTVC/ITVC");

				if (PLB_Cameras[camidx].Custom)
				{
					JObject jcamcust = new JObject()
					{
						["Xo"] = PLB_Cameras[camidx].Xo,
						["Yo"] = PLB_Cameras[camidx].Yo,
						["Zo"] = PLB_Cameras[camidx].Zo,
						["Rot"] = PLB_Cameras[camidx].Rot
					};
					jcam["Custom"] = jcamcust;
				}
			}
			return jcam;
		}


		/// <summary>
		/// Name of OV used in this mission
		/// </summary>
		private OV_Name name;
		public OV_Name Name
		{
			get { return name; }
			set
			{
				name = value;
				OnPropertyChanged( "Name" );
				OnPropertyChanged( "IsEDODualPalletEnabled" );
				OnPropertyChanged( "IsEDOKitEnabled" );
				OnPropertyChanged( "IsCentaurEnabled" );
			}
		}

		/// <summary>
		/// The name of the OV texture
		/// </summary>
		private string texture;
		public string Texture
		{
			get { return texture; }
			set
			{
				texture = value;
				OnPropertyChanged( "Texture" );
			}
		}

		/// <summary>
		/// The name of the left OMS pod texture
		/// </summary>
		private string lomstex;
		public string LOMStex
		{
			get { return lomstex; }
			set
			{
				lomstex = value;
				OnPropertyChanged( "LOMSex" );
			}
		}

		/// <summary>
		/// The name of the right OMS pod texture
		/// </summary>
		private string romstex;
		public string ROMStex
		{
			get { return romstex; }
			set
			{
				romstex = value;
				OnPropertyChanged( "ROMStex" );
			}
		}

		/// <summary>
		/// Is the Ku-band Antenna installed
		/// </summary>
		private bool kubandantenna;
		public bool KubandAntenna
		{
			get { return kubandantenna; }
			set
			{
				kubandantenna = value;
				OnPropertyChanged( "KubandAntenna" );
			}
		}

		/// <summary>
		/// Is the External Airlock / ODS Kit installed
		/// </summary>
		private bool extal_ods_kit;
		public bool ExtAL_ODS_Kit
		{
			get { return extal_ods_kit; }
			set
			{
				extal_ods_kit = value;
				OnPropertyChanged( "ExtAL_ODS_Kit" );
				OnPropertyChanged( "Airlock" );
				OnPropertyChanged( "ODS" );
			}
		}

		/// <summary>
		/// Is the ODS installed
		/// </summary>
		private bool ods;
		public bool ODS
		{
			get { return ods; }
			set
			{
				ods = value;
				OnPropertyChanged( "ODS" );
				OnPropertyChanged( "TAA" );
			}
		}

		/// <summary>
		/// Is the TAA installed and where
		/// </summary>
		private TAA_Type taa;
		public TAA_Type TAA
		{
			get { return taa; }
			set
			{
				taa = value;
				OnPropertyChanged( "TAA" );
			}
		}

		private Airlock_Type airlock;
		public Airlock_Type Airlock
		{
			get { return airlock; }
			set
			{
				airlock = value;
				OnPropertyChanged( "Airlock" );
				OnPropertyChanged( "TAA" );
			}
		}

		/// <summary>
		/// Are the forward bulkhead and docking lights installed
		/// </summary>
		private bool fwdbulkdocklights;
		public bool FwdBulkDockLights
		{
			get { return fwdbulkdocklights; }
			set
			{
				fwdbulkdocklights = value;
				OnPropertyChanged( "FwdBulkDockLights" );
			}
		}

		/// <summary>
		/// Is the Drag Chute installed
		/// </summary>
		private bool dragchute;
		public bool DragChute
		{
			get { return dragchute; }
			set
			{
				dragchute = value;
				OnPropertyChanged( "DragChute" );
			}
		}

		/// <summary>
		/// Is the Payload Bay Liner installed
		/// </summary>
		private bool plbliner;
		public bool PLBLiner
		{
			get { return plbliner; }
			set
			{
				plbliner = value;
				OnPropertyChanged( "PLBLiner" );
			}
		}

		/// <summary>
		/// Is the SILTS pod installed
		/// </summary>
		private bool silts;
		public bool SILTS
		{
			get { return silts; }
			set
			{
				silts = value;
				OnPropertyChanged( "SILTS" );
			}
		}

		/// <summary>
		/// Is the DFI Wire Tray installed
		/// </summary>
		private bool dfiwiretray;
		public bool DFIWireTray
		{
			get { return dfiwiretray; }
			set
			{
				dfiwiretray = value;
				OnPropertyChanged( "DFIWireTray" );
			}
		}

		/// <summary>
		/// Are the Vent Doors 4 and 7 installed
		/// </summary>
		private bool ventdoors4and7;
		public bool VentDoors4and7
		{
			get { return ventdoors4and7; }
			set
			{
				ventdoors4and7 = value;
				OnPropertyChanged( "VentDoors4and7" );
			}
		}

		/// <summary>
		/// Number of crew members
		/// </summary>
		private int crew;
		public int Crew
		{
			get { return crew; }
			set
			{
				crew = value;
				OnPropertyChanged( "Crew" );
			}
		}

		/// <summary>
		/// Type of Galley installed
		/// </summary>
		private Galley_Type galley;
		public Galley_Type Galley
		{
			get { return galley; }
			set
			{
				galley = value;
				OnPropertyChanged( "Galley" );
			}
		}

		/// <summary>
		/// Type of Sleep Stations installed
		/// </summary>
		private SleepStations_Type sleepstations;
		public SleepStations_Type SleepStations
		{
			get { return sleepstations; }
			set
			{
				sleepstations = value;
				OnPropertyChanged( "SleepStations" );
			}
		}

		/// <summary>
		/// Are Ejection Seats installed
		/// </summary>
		private bool ejectionseats;
		public bool EjectionSeats
		{
			get { return ejectionseats; }
			set
			{
				ejectionseats = value;
				OnPropertyChanged( "EjectionSeats" );
			}
		}

		/// <summary>
		/// Is Crew Escape Hardware installed
		/// </summary>
		private bool crewescapehardware;
		public bool CrewEscapeHardware
		{
			get { return crewescapehardware; }
			set
			{
				crewescapehardware = value;
				OnPropertyChanged( "CrewEscapeHardware" );
			}
		}

		/// <summary>
		/// Type of Flight Deck
		/// </summary>
		private FlightDeck_Type flightdeck;
		public FlightDeck_Type FlightDeck
		{
			get { return flightdeck; }
			set
			{
				flightdeck = value;
				OnPropertyChanged( "FlightDeck" );
			}
		}

		private double frcs_load;
		public double FRCS_Load
		{
			get { return frcs_load; }
			set
			{
				frcs_load = value;
				OnPropertyChanged( "FRCS_Load" );
			}
		}

		private double lrcs_load;
		public double LRCS_Load
		{
			get { return lrcs_load; }
			set
			{
				lrcs_load = value;
				OnPropertyChanged( "LRCS_Load" );
			}
		}

		private double rrcs_load;
		public double RRCS_Load
		{
			get { return rrcs_load; }
			set
			{
				rrcs_load = value;
				OnPropertyChanged( "RRCS_Load" );
			}
		}

		private double loms_load;
		public double LOMS_Load
		{
			get { return loms_load; }
			set
			{
				loms_load = value;
				OnPropertyChanged( "LOMS_Load" );
			}
		}

		private double roms_load;
		public double ROMS_Load
		{
			get { return roms_load; }
			set
			{
				roms_load = value;
				OnPropertyChanged( "ROMS_Load" );
			}
		}

		private double koms_load;
		public double KOMS_Load
		{
			get { return koms_load; }
			set
			{
				koms_load = value;
				OnPropertyChanged( "KOMS_Load" );
			}
		}

		private int omskittanks;
		public int OMSKitTanks
		{
			get { return omskittanks; }
			set
			{
				if (value > 3) omskittanks = 3;
				else if (value < 0) omskittanks = 0;
				else omskittanks = value;
				OnPropertyChanged( "OMSKitTanks" );
			}
		}

		private int prsdinternaltanks;
		public int PRSDInternalTanks
		{
			get { return prsdinternaltanks; }
			set
			{
				if (value > 5) prsdinternaltanks = 5;
				else if (value < 2) prsdinternaltanks = 2;
				else prsdinternaltanks = value;
				OnPropertyChanged( "PRSDInternalTanks" );
			}
		}

		private bool edokit;
		public bool EDOKit
		{
			get { return edokit; }
			set
			{
				edokit = value;
				OnPropertyChanged( "EDOKit" );
			}
		}

		private int edopallet;
		public int EDOPallet
		{
			get { return edopallet; }
			set
			{
				edopallet = value;
				OnPropertyChanged( "EDOPallet" );
			}
		}

		private Mission_PLActive[] pl_active;
		public Mission_PLActive[] PL_Active
		{
			get { return pl_active; }
			set
			{
				pl_active = value;
				OnPropertyChanged( "PL_Active" );
			}
		}

		private Mission_PLPassive[] pl_passive;
		public Mission_PLPassive[] PL_Passive
		{
			get { return pl_passive; }
			set
			{
				pl_passive = value;
				OnPropertyChanged( "PL_Passive" );
			}
		}

		private Mission_PLBayBridge[] pl_baybridge;
		public Mission_PLBayBridge[] PL_BayBridge
		{
			get { return pl_baybridge; }
			set
			{
				pl_baybridge = value;
				OnPropertyChanged( "PL_BayBridge" );
			}
		}

		private int[] largeupperstage_latch;
		public int[] LargeUpperStage_Latch
		{
			get { return largeupperstage_latch; }
			set
			{
				largeupperstage_latch = value;
				OnPropertyChanged( "LargeUpperStage_Latch" );
			}
		}

		/// <summary>
		/// IUS ASE is installed in aft position
		/// </summary>
		private bool ius_aftposition;
		public bool IUS_AftPosition
		{
			get { return ius_aftposition; }
			set
			{
				ius_aftposition = value;
				OnPropertyChanged( "IUS_AftPosition" );
			}
		}


		/// <summary>
		/// Hardware installed on Port Longeron Sill
		/// </summary>
		private LongeronSillHardware_Type portlongeronsill;
		public LongeronSillHardware_Type PortLongeronSill
		{
			get { return portlongeronsill; }
			set
			{
				portlongeronsill = value;
				OnPropertyChanged( "PortLongeronSill" );
				OnPropertyChanged( "IsPortLongeronSillEditEnabled" );
			}
		}

		/// <summary>
		/// Port RMS
		/// </summary>
		private Mission_RMS port_rms;
		public Mission_RMS Port_RMS
		{
			get { return port_rms; }
			set
			{
				port_rms = value;
				OnPropertyChanged( "Port_RMS" );
			}
		}

		/// <summary>
		/// Port Payload MPM
		/// </summary>
		private Mission_PL_MPM port_pl_mpm;
		public Mission_PL_MPM Port_PL_MPM
		{
			get { return port_pl_mpm; }
			set
			{
				port_pl_mpm = value;
				OnPropertyChanged( "Port_PL_MPM" );
			}
		}

		/// <summary>
		/// Hardware installed on Starboard Longeron Sill
		/// </summary>
		private LongeronSillHardware_Type stbdlongeronsill;
		public LongeronSillHardware_Type StbdLongeronSill
		{
			get { return stbdlongeronsill; }
			set
			{
				stbdlongeronsill = value;
				OnPropertyChanged( "StbdLongeronSill" );
				OnPropertyChanged( "IsStarboardLongeronSillEditEnabled" );
			}
		}

		/// <summary>
		/// Starboard RMS
		/// </summary>
		private Mission_RMS stbd_rms;
		public Mission_RMS Stbd_RMS
		{
			get { return stbd_rms; }
			set
			{
				stbd_rms = value;
				OnPropertyChanged( "Stbd_RMS" );
			}
		}

		/// <summary>
		/// Starboard Payload MPM
		/// </summary>
		private Mission_PL_MPM stbd_pl_mpm;
		public Mission_PL_MPM Stbd_PL_MPM
		{
			get { return stbd_pl_mpm; }
			set
			{
				stbd_pl_mpm = value;
				OnPropertyChanged( "Stbd_PL_MPM" );
			}
		}

		/// <summary>
		/// PLID (keel) of "small" upper stage ASEs
		/// </summary>
		private int[] smallupperstage_aseplid;
		public int[] SmallUpperStage_ASEPLID
		{
			get { return smallupperstage_aseplid; }
			set
			{
				smallupperstage_aseplid = value;
				OnPropertyChanged( "SmallUpperStage_ASEPLID" );
			}
		}

		/// <summary>
		/// ASE for "small" upper stages has large Sunshield (PAM-D and PAM-DII only)
		/// </summary>
		private bool[] smallupperstage_largesunshield;
		public bool[] SmallUpperStage_LargeSunshield
		{
			get { return smallupperstage_largesunshield; }
			set
			{
				smallupperstage_largesunshield = value;
				OnPropertyChanged( "SmallUpperStage_LargeSunshield" );
			}
		}

		private List<Mission_ILOAD> iloads;
		public List<Mission_ILOAD> ILOAD_List
		{
			get { return iloads; }
			set
			{
				iloads = value;
				OnPropertyChanged( "ILOAD_List" );
			}
		}

		/// <summary>
		/// SSMEs
		/// </summary>
		private Mission_SSME[] ssme;
		public Mission_SSME[] SSME
		{
			get { return ssme; }
			set
			{
				ssme = value;
				OnPropertyChanged( "SSME" );
			}
		}

		private List<LandingSiteData> landingsitedb;
		public List<LandingSiteData> LandingSiteDB
		{
			get
			{
				return landingsitedb;
			}
			set{}
		}

		/// <summary>
		/// Landing site table file
		/// </summary>
		private List<Tuple<string,string>> landingsitetable;
		public List<Tuple<string,string>> LandingSiteTable
		{
			get
			{
				return landingsitetable;
			}
			set
			{
				landingsitetable = value;
				OnPropertyChanged( "LandingSiteTable" );
			}
		}

		/// <summary>
		/// The name of the target vessel
		/// </summary>
		private string tgtvessel;
		public string TgtVessel
		{
			get { return tgtvessel; }
			set
			{
				tgtvessel = value;
				OnPropertyChanged( "TgtVessel" );
			}
		}

		/// <summary>
		/// Data of PLB CCTV cameras
		/// </summary>
		private PLB_Camera[] plb_cameras;
		public PLB_Camera[] PLB_Cameras
		{
			get
			{
				return plb_cameras;
			}
			set
			{
				plb_cameras = value;
				OnPropertyChanged( "PLB_Cameras" );
			}
		}

		/// <summary>
		/// List of PLIDs of keel cameras
		/// </summary>
		private int[] keel_cameras;
		public int[] Keel_Cameras
		{
			get
			{
				return keel_cameras;
			}
			set
			{
				keel_cameras = value;
				OnPropertyChanged( "Keel_Cameras" );
			}
		}



		Mission mission;


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}


		// properties only for UI option control
		public bool IsEDOKitEnabled
		{
			get { return (name == OV_Name.Columbia) || (name == OV_Name.Atlantis) || (name == OV_Name.Endeavour); }
			set {}
		}

		public bool IsEDODualPalletEnabled
		{
			get { return name == OV_Name.Endeavour; }
			set {}
		}

		public bool IsCentaurEnabled
		{
			get { return (name == OV_Name.Challenger) || (name == OV_Name.Atlantis); }
			set {}
		}

		public bool IsPortLongeronSillEditEnabled
		{
			get { return portlongeronsill != LongeronSillHardware_Type.None; }
			set {}
		}

		public bool IsStarboardLongeronSillEditEnabled
		{
			get { return stbdlongeronsill != LongeronSillHardware_Type.None; }
			set {}
		}
	}
}
