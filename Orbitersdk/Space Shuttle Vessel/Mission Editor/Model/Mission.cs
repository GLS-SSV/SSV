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
2020/07/16   GLS
2020/07/30   GLS
2020/08/22   GLS
2020/09/27   GLS
2020/09/28   GLS
2020/10/09   GLS
2020/10/10   GLS
2021/12/10   GLS
2021/12/11   GLS
2021/12/19   GLS
2021/12/25   GLS
2022/01/10   GLS
2022/02/23   GLS
2022/03/02   GLS
2022/03/04   GLS
2022/03/06   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/05/01   GLS
2022/05/07   GLS
2022/05/24   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/10/17   GLS
2022/10/18   GLS
2022/10/20   GLS
2022/12/08   GLS
2022/12/09   GLS
2022/12/10   GLS
2022/12/13   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra Workbench

  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/

using System;
using System.IO;
using System.ComponentModel;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters;
using System.Collections.ObjectModel;


namespace SSVMissionEditor.model
{
	/// <summary>
	/// Description of a mission in a program.
	/// </summary>
	/// <remarks>
	/// <para>
	/// Describes the resources used in a mission, the launch and landing parameters.
	/// </para>
	/// </remarks>
	public class Mission : INotifyPropertyChanged
	{
		private const string vesselconfigpath = "Config\\Vessels\\";

		public struct AvailableVessel
		{
			public string name;
			public double mass;
			public int attachment_count;// only attachments to parent
		}


		public Mission( string orbiterpath )
		{
			JsonConvert.DefaultSettings = (() =>
			{
				var settings = new JsonSerializerSettings();
				settings.Converters.Add(new StringEnumConverter {});
				return settings;
			});

			OV = new Mission_OV( this, orbiterpath );
			ET = new Mission_ET();
			SRB = new Mission_SRB();

			LargeUpperStage_PL = new Mission_Payload();

			SmallUpperStage_PL = new Mission_Payload[Defs.SMALLUPPERSTAGE_MAX];
			for (int i = 0; i < Defs.SMALLUPPERSTAGE_MAX; i++) SmallUpperStage_PL[i] = new Mission_Payload();

			SmallUpperStage = new int[Defs.SMALLUPPERSTAGE_MAX];
			SmallUpperStage_Name = new string[Defs.SMALLUPPERSTAGE_MAX];
			SmallUpperStage_Load = new double[Defs.SMALLUPPERSTAGE_MAX];
			SmallUpperStage_Adapter_Mesh = new string[Defs.SMALLUPPERSTAGE_MAX];
			SmallUpperStage_Adapter_Offset = new double[Defs.SMALLUPPERSTAGE_MAX];
			SmallUpperStage_Adapter_Mass = new double[Defs.SMALLUPPERSTAGE_MAX];

			OtherVessels = new ObservableCollection<Mission_Vessel>();


			availablevessels = new List<AvailableVessel>();
			ExtractVesselList( orbiterpath );

			LoadDefault();
		}

		private void ExtractVesselList( string orbiterpath )
		{
			string vesseldir = orbiterpath + vesselconfigpath;
			string[] vesselfiles = Directory.GetFiles( vesseldir, "*.cfg" );
			string[] subdirs = Directory.GetDirectories( vesseldir );
			foreach (string tmp in subdirs)
			{
				string[] vesselfilessubdir = Directory.GetFiles( tmp + "\\", "*.cfg" );
				string[] newlist = new string[vesselfiles.Length + vesselfilessubdir.Length];
				vesselfiles.CopyTo( newlist, 0 );
				vesselfilessubdir.CopyTo( newlist, vesselfiles.Length );

				vesselfiles = new string[newlist.Length];
				newlist.CopyTo( vesselfiles, 0 );
			}

			double mass = 0.0;
			int attachments = 0;

			foreach (string vesselfile in vesselfiles)
			{
				mass = 0.0;
				attachments = 0;

				// extract mass and attachments (only if vessel doesn't have module)
				/*{
					string line;
					string key;
					string val;
					int eq = -1;
					bool readattach = false;

					StreamReader file = new StreamReader( vesselfile );
					while ((line = file.ReadLine()) != null)
					{
						// remove comments
						eq = line.IndexOf( ";" );
						if (eq != -1) line = line.Substring( 0, eq );

						eq = line.IndexOf( "=" );
						if (eq != -1)
						{
							key = line.Substring( 0, eq );
							val = line.Substring( eq + 1, line.Length - eq - 1 );
							key = key.TrimEnd( ' ' );
							switch (key)
							{
								case "Mass":
								case "MaxFuel":
									mass += Convert.ToDouble( val );
									break;
								default:
									break;
							}
						}
						else if (line == "BEGIN_ATTACHMENT")
						{
							readattach = true;
						}
						else if (line == "END_ATTACHMENT")
						{
							readattach = false;
						}
						else if (readattach)
						{
							if (line[0] == 'P')
								attachments++;
						}
					}
					file.Close();
				}*/

				availablevessels.Add( new AvailableVessel{ name = vesselfile.Substring(vesseldir.Length, vesselfile.Length - vesseldir.Length - 4), mass = mass, attachment_count = attachments } );
			}
			return;
		}

		/*private int FindVesselIndex( string name )
		{
			for (int i = 0; i < availablevessels.Count; i++)
				if (availablevessels[i].name == name) return i;

			return -1;
		}*/

		/*public string FindVesselName( int index )
		{
			if (index >= availablevessels.Count) return "";
			else return availablevessels[index].name;
		}*/

		private void LoadDefault()
		{
			Name = "STS-101";
			Description = "Space Shuttle mission STS-101, launched on Atlantis to the ISS on 2000/05/19.";


			LargeUpperStage = 0;
			LargeUpperStage_Name = "";
			LargeUpperStage_PL.LoadDefault();
			LargeUpperStage_Adapter_Mesh = "";
			LargeUpperStage_Adapter_Offset = 0.0;
			LargeUpperStage_Adapter_Mass = 0.0;


			IUS_Texture = "IUS_stage_NASA";
			IUS_1StageLoad = 1.0;
			IUS_2StageLoad = 1.0;
			IUS_RCSTanks = 2;



			OMSKit = false;


			for (int i = 0; i < 3; i++)
			{
				SmallUpperStage[i] = 0;
				SmallUpperStage_Name[i] = "";
				SmallUpperStage_Load[i] = 1.0;
				SmallUpperStage_Adapter_Mesh[i] = "";
				SmallUpperStage_Adapter_Offset[i] = 0.0;
				SmallUpperStage_Adapter_Mass[i] = 0.0;
				SmallUpperStage_PL[i].LoadDefault();
			}



			MECO_Inc = 51.62;
			//MECO_LAN = 0;
			MECO_Alt = 105564;
			MECO_Vel = 7903.449390;
			MECO_FPA = 0.708380;



			T0Year = 2000;
			T0Month = 5;
			T0Day = 19;
			T0Hour = 10;
			T0Minute = 11;
			T0Second = 10;

			OV.LoadDefault();
			ET.LoadDefault();
			SRB.LoadDefault();

			LaunchSite = 0;
			LaunchPad = 0;
			LaunchPadType = 6;
			MLP = 0;

			OtherVessels.Clear();
			OtherVessels.Add( new Mission_Vessel{ VesselClass = "ProjectAlpha_ISS", Name = "ISS", ScnParams = "STATUS Orbiting Earth\nRPOS -6025002.08 -2396043.70 1843678.15\nRVEL -3146.174 6884.841 -1333.517\nAROT 110.00 -10.00 80.00\nPRPLEVEL 0:1.000\nIDS 0:1 100 1:2 100 2:3 100 3:4 100 4:5 100\nNAVFREQ 0 0\nXPDR 466" } );
			return;
		}

		private void ResetMission()
		{
			// reset config to "empty" Atlantis
			Name = "";
			Description = "";

			OMSKit = false;

			for (int i = 0; i < 3; i++)
			{
				SmallUpperStage[i] = 0;
				SmallUpperStage_Name[i] = "";
				SmallUpperStage_Load[i] = 1.0;
				SmallUpperStage_Adapter_Mesh[i] = "";
				SmallUpperStage_Adapter_Offset[i] = 0.0;
				SmallUpperStage_Adapter_Mass[i] = 0.0;
				SmallUpperStage_PL[i].LoadEmpty();
			}


			MECO_Inc = 51.62;
			//MECO_LAN = 0;
			MECO_Alt = 105564;
			MECO_Vel = 7903.449390;
			MECO_FPA = 0.708380;


			T0Year = 2000;
			T0Month = 5;
			T0Day = 19;
			T0Hour = 10;
			T0Minute = 11;
			T0Second = 10;

			OV.LoadDefault();
			ET.LoadDefault();
			SRB.LoadDefault();

			LaunchSite = 0;
			LaunchPad = 0;
			LaunchPadType = 6;
			MLP = 0;

			LargeUpperStage = 0;
			LargeUpperStage_Name = "";
			LargeUpperStage_PL.LoadEmpty();
			LargeUpperStage_Adapter_Mesh = "";
			LargeUpperStage_Adapter_Offset = 0.0;
			LargeUpperStage_Adapter_Mass = 0.0;


			IUS_Texture = "IUS_stage_NASA";
			IUS_1StageLoad = 1.0;
			IUS_2StageLoad = 1.0;
			IUS_RCSTanks = 2;

			OtherVessels.Clear();
			return;
		}

		public void Load( string missionfile )
		{
			ResetMission();

			StreamReader file = new StreamReader( missionfile );
			string jsonfile = file.ReadToEnd();
			file.Close();

			JObject jmf = JObject.Parse( jsonfile );

			int version = (int)jmf["Version"];

			if (version == 1) Load_V1( jmf );
			else throw new Exception( "The mission file version is not supported." );
			return;
		}

		public void Load_V1( JObject jmf )
		{
			string strtmp;
			double dbltmp;

			//////// root ////////
			Name = (string)jmf["Name"];
			Description = (string)jmf["Description"];

			//////// Orbiter Vehicle ////////
			OV.Load_V1( jmf["Orbiter Vehicle"] );

			//////// External Tank ////////
			ET.Load_V1( jmf["External Tank"] );

			//////// Solid Rocket Boosters ////////
			SRB.Load_V1( jmf["Solid Rocket Boosters"] );

			//////// Launch Site ////////
			JToken jls = jmf["Launch Site"]["VAFB"];
			if ((jls != null) && (jls.Type != JTokenType.Null)) LaunchSite = 1;
			else
			{
				LaunchSite = 0;

				strtmp = (string)jmf["Launch Site"]["KSC"]["Pad"];
				if (strtmp == "LC-39B") LaunchPad = 1;
				else /*if (strtmp == "LC-39A")*/ LaunchPad = 0;

				strtmp = (string)jmf["Launch Site"]["KSC"]["Pad Type"];
				if (strtmp == "1981") LaunchPadType = 0;
				else if (strtmp == "1982") LaunchPadType = 1;
				else if (strtmp == "1983") LaunchPadType = 2;
				else if (strtmp == "1985") LaunchPadType = 3;
				else if (strtmp == "1986") LaunchPadType = 4;
				else if (strtmp == "1988") LaunchPadType = 5;
				else if (strtmp == "1995") LaunchPadType = 6;
				else /*if (strtmp == "2007")*/ LaunchPadType = 7;

				dbltmp = (double)jmf["Launch Site"]["KSC"]["MLP"];
				MLP = Convert.ToInt32( dbltmp ) - 1;
			}

			//////// Upper Stages ////////
			JToken jus = jmf["Upper Stages"];
			int idx_smallupperstage = 0;
			if (jus != null)
			{
				List<JToken> jusl = jus.ToObject<List<JToken>>();
				foreach (JToken juslitem in jusl)
				{
					// large upper stage
					JToken jius = juslitem["IUS 2-Stage"];
					JToken jcg = juslitem["Centaur G"];
					JToken jcgp = juslitem["Centaur G-Prime"];

					if (((jius != null) && (jius.Type != JTokenType.Null)) ||
						((jcg != null) && (jcg.Type != JTokenType.Null)) ||
						((jcgp != null) && (jcgp.Type != JTokenType.Null)))
					{
						// upper stage unique params
						if ((jius != null) && (jius.Type != JTokenType.Null))
						{
							// IUS 2-Stage
							LargeUpperStage = 1;

							IUS_Texture = (string)jius["Texture"];
							IUS_1StageLoad = (double)jius["Load Stage 1"];
							IUS_2StageLoad = (double)jius["Load Stage 2"];
							IUS_RCSTanks = (int)jius["RCS Tanks"];
							IUS_4Antennas = (bool)jius["4 Antennas"];
						}
						else if ((jcg != null) && (jcg.Type != JTokenType.Null))
						{
							// Centaur G
							LargeUpperStage = 4;
						}
						else /*else if ((jcgp != null) && (jcgp.Type != JTokenType.Null))*/
						{
							// Centaur G-Prime
							LargeUpperStage = 5;
						}

						LargeUpperStage_Name = (string)juslitem["Name"];

						// adapter
						JToken jusadp = juslitem["Adapter"];
						if (jusadp != null)
						{
							LargeUpperStage_Adapter_Mesh = (string)jusadp["Mesh"];
							LargeUpperStage_Adapter_Offset = (double)jusadp["Offset"];
							LargeUpperStage_Adapter_Mass = (double)jusadp["Mass"];
						}

						// payload
						LargeUpperStage_PL.Load_V1( juslitem["Payload"] );
					}
					else if (idx_smallupperstage < Defs.SMALLUPPERSTAGE_MAX)
					{
						// small upper stage
						JToken jpamd = juslitem["PAM-D"];
						JToken jpamdii = juslitem["PAM-DII"];
						JToken jpama = juslitem["PAM-A"];

						if (((jpamd != null) && (jpamd.Type != JTokenType.Null)) ||
							((jpamdii != null) && (jpamdii.Type != JTokenType.Null)) ||
							((jpama != null) && (jpama.Type != JTokenType.Null)))
						{
							// upper stage unique params
							if ((jpamd != null) && (jpamd.Type != JTokenType.Null))
							{
								// PAM-D
								SmallUpperStage[idx_smallupperstage] = 1;

								SmallUpperStage_Load[idx_smallupperstage] = (double)jpamd["Load"];
							}
							else if ((jpamdii != null) && (jpamdii.Type != JTokenType.Null))
							{
								// PAM-DII
								SmallUpperStage[idx_smallupperstage] = 2;

								SmallUpperStage_Load[idx_smallupperstage] = (double)jpamdii["Load"];
							}
							else /*if ((jpama != null) && (jpama.Type != JTokenType.Null))*/
							{
								// PAM-A
								SmallUpperStage[idx_smallupperstage] = 3;

								SmallUpperStage_Load[idx_smallupperstage] = (double)jpama["Load"];
							}

							SmallUpperStage_Name[idx_smallupperstage] = (string)juslitem["Name"];

							// adapter
							JToken jusadp = juslitem["Adapter"];
							if ((jusadp != null) && (jusadp.Type != JTokenType.Null))
							{
								SmallUpperStage_Adapter_Mesh[idx_smallupperstage] = (string)jusadp["Mesh"];
								SmallUpperStage_Adapter_Offset[idx_smallupperstage] = (double)jusadp["Offset"];
								SmallUpperStage_Adapter_Mass[idx_smallupperstage] = (double)jusadp["Mass"];
							}

							// payload
							SmallUpperStage_PL[idx_smallupperstage].Load_V1( juslitem["Payload"] );

							idx_smallupperstage++;
						}
					}
				}

			}

			//////// Other Vessels ////////
			OtherVessels.Clear();
			JToken jov = jmf["Other Vessels"];
			if (jov != null)
			{
				List<JToken> jovl = jov.ToObject<List<JToken>>();
				foreach (JToken jovlitem in jovl)
				{
					Mission_Vessel tmp = new Mission_Vessel();
					tmp.Load_V1( jovlitem );
					OtherVessels.Add( tmp );
				}
			}

			//////// Legacy Launch Parameters ////////
			dbltmp = (double)jmf["Legacy Launch Parameters"]["T0"];
			{
				DateTime dt = DateTime.FromOADate( dbltmp - 15018.0 );
				T0Year = dt.Year;
				T0Month = dt.Month;
				T0Day = dt.Day;
				T0Hour = dt.Hour;
				T0Minute = dt.Minute;
				T0Second = dt.Second + (0.001 * dt.Millisecond);
			}
			MECO_Inc = (double)jmf["Legacy Launch Parameters"]["TargetInc"];
			//MECO_LAN = (double)jmf["Legacy Launch Parameters"]["TargetLAN"];
			MECO_Alt = (double)jmf["Legacy Launch Parameters"]["MECOAlt"];
			MECO_Vel = (double)jmf["Legacy Launch Parameters"]["MECOVel"];
			MECO_FPA = (double)jmf["Legacy Launch Parameters"]["MECOFPA"];
			return;
		}

		public void Save( string missionfile )
		{
			// create JSON object
			JObject jroot = Save_V1();

			// save to file
			string json = /*JsonConvert.SerializeObject(this);*/jroot.ToString( Formatting.None );
			StreamWriter file = new StreamWriter( missionfile );
			file.Write( json );
			file.Close();
			return;
		}

		public JObject Save_V1()
		{
			//////// root ////////
			JObject jroot = new JObject
			{
				["Version"] = 1,
				["Name"] = Name,
				["Description"] = Description,
			};

			//////// Orbiter Vehicle ////////
			jroot["Orbiter Vehicle"] = OV.Save_V1();

			//////// External Tank ////////
			jroot["External Tank"] = ET.Save_V1();

			//////// Solid Rocket Boosters ////////
			jroot["Solid Rocket Boosters"] = SRB.Save_V1();

			//////// Launch Site ////////
			JObject jlaunchsite = new JObject();
			if (LaunchSite == 1)
			{
				jlaunchsite["VAFB"] = new JObject();// empty
			}
			else
			{
				JObject jksc = new JObject();

				if (LaunchPad == 1) jksc["Pad"] = "LC-39B";
				else jksc["Pad"] = "LC-39A";

				if (LaunchPadType == 0) jksc["Pad Type"] = "1981";
				else if (LaunchPadType == 1) jksc["Pad Type"] = "1982";
				else if (LaunchPadType == 2) jksc["Pad Type"] = "1983";
				else if (LaunchPadType == 3) jksc["Pad Type"] = "1985";
				else if (LaunchPadType == 4) jksc["Pad Type"] = "1986";
				else if (LaunchPadType == 5) jksc["Pad Type"] = "1988";
				else if (LaunchPadType == 6) jksc["Pad Type"] = "1995";
				else if (LaunchPadType == 7) jksc["Pad Type"] = "2007";

				jksc["MLP"] = MLP + 1;

				jlaunchsite["KSC"] = jksc;
			}
			jroot["Launch Site"] = jlaunchsite;

			//////// Upper Stages ////////
			JArray jus = new JArray();
			if (LargeUpperStage != 0)
			{
				JObject jlus = new JObject();
				jlus["Name"] = LargeUpperStage_Name;
				if (LargeUpperStage == 1)// IUS 2-Stage
				{
					jlus["IUS 2-Stage"] = new JObject()
					{
						["Texture"] = IUS_Texture,
						["Load Stage 1"] = IUS_1StageLoad,
						["Load Stage 2"] = IUS_2StageLoad,
						["RCS Tanks"] = IUS_RCSTanks,
						["4 Antennas"] = IUS_4Antennas
					};
				}
				else if (LargeUpperStage == 4)// Centaur G
				{
					jlus["Centaur G"] = new JObject();
				}
				else if (LargeUpperStage == 5)// Centaur G-Prime
				{
					jlus["Centaur G-Prime"] = new JObject();
				}
				jlus["Adapter"] = new JObject
				{
					["Mesh"] = LargeUpperStage_Adapter_Mesh,
					["Offset"] = LargeUpperStage_Adapter_Offset,
					["Mass"] = LargeUpperStage_Adapter_Mass
				};
				jlus["Payload"] = LargeUpperStage_PL.Save_V1();
				jus.Add( jlus );
			}
			for (int i = 0; i < Defs.SMALLUPPERSTAGE_MAX; i++)
			{
				if (SmallUpperStage[i] != 0)
				{
					JObject jsus = new JObject();
					jsus["Name"] = SmallUpperStage_Name[i];
					if (SmallUpperStage[i] == 1)// PAM-D
					{
						jsus["PAM-D"] = new JObject()
						{
							["Load"] = SmallUpperStage_Load[i]
						};
					}
					else if (SmallUpperStage[i] == 2)// PAM-DII
					{
						jsus["PAM-DII"] = new JObject()
						{
							["Load"] = SmallUpperStage_Load[i]
						};
					}
					else if (SmallUpperStage[i] == 3)// PAM-A
					{
						jsus["PAM-A"] = new JObject()
						{
							["Load"] = SmallUpperStage_Load[i]
						};
					}
					jsus["Adapter"] = new JObject
					{
						["Mesh"] = SmallUpperStage_Adapter_Mesh[i],
						["Offset"] = SmallUpperStage_Adapter_Offset[i],
						["Mass"] = SmallUpperStage_Adapter_Mass[i]
					};
					jsus["Payload"] = SmallUpperStage_PL[i].Save_V1();
					jus.Add( jsus );
				}
			}
			jroot["Upper Stages"] = jus;

			//////// Other Vessels ////////
			JArray jov = new JArray();
			foreach (Mission_Vessel ovitem in OtherVessels)
			{
				jov.Add( ovitem.Save_V1() );
			}
			jroot["Other Vessels"] = jov;

			//////// Legacy Launch Parameters ////////
			JObject joldlaunchparams = new JObject();
			int ms = Convert.ToInt32( 1000 * (T0Second - (int)T0Second) );
			DateTime dt = new DateTime( T0Year, T0Month, T0Day, T0Hour, T0Minute, (int)T0Second, ms );
			joldlaunchparams["T0"] = dt.ToOADate() + 15018.0;
			joldlaunchparams["TargetInc"] = MECO_Inc;
			//joldlaunchparams["TargetLAN"] = MECO_LAN;
			joldlaunchparams["MECOAlt"] = MECO_Alt;
			joldlaunchparams["MECOVel"] = MECO_Vel;
			joldlaunchparams["MECOFPA"] = MECO_FPA;
			jroot["Legacy Launch Parameters"] = joldlaunchparams;
			return jroot;
		}

		public bool Test( ref string str )
		{
			bool ok = true;
			/* Test list:
			-----------------------------------------------------------------------------------------------------------------------------------------
			| ID	| Name				| Description											|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 1	| latch assignments		| check if payload latch systems are not used more than one payload latch			|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 2	| payload latch collision	| check if payload latches are not colliding							|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 3	| bridge usage			| check if no bay bridge payloads are installed in already used bay bridges			|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 4	| payload settings		| check if payload has all needed parameters defined						|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 5	| payload adapter settings	| check if upper stage payloads have all needed payload adapter parameters defined		|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 6	| propellant load check		| check if RCS and OMS loads are between maximum and minimum values				|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 7	| CISS pad version check	| check if CISS used, pad is version 1986 of LC39						|
			-----------------------------------------------------------------------------------------------------------------------------------------
			| 8	| landing site check		| check landing site list integrity								|
			-----------------------------------------------------------------------------------------------------------------------------------------
			*/
			// TODO minimum latch config
			// TODO attachment is in used latch

			/////// latch assignments ///////
			bool[] latch = new bool[15];
			for (int k = 0; k < 15; k++) latch[k] = false;

			foreach (Mission_PLActive pl in OV.PL_Active)
			{
				for (int j = 0; j < 12; j++)
				{
					if (pl.Latches[j].PLID > 0)// PRLA used
					{
						if (latch[pl.Latches[j].Latch])
						{
							// already used
							ok = false;
							int plsys = (pl.Latches[j].Latch / 5) + 1;
							int ltch = (pl.Latches[j].Latch - (5 * (plsys - 1))) + 1;
							str += "Latch usage collision: PL Sys " + plsys + ", Latch " + ltch + "\n\n";
						}
						else latch[pl.Latches[j].Latch] = true;// not used, mark it
					}
				}
			}

			if (LargeUpperStage == 1)// IUS 2-Stage
			{
				for (int j = 0; j < 2; j++)
				{
					if (latch[OV.LargeUpperStage_Latch[j]])
					{
						// already used
						ok = false;
						int plsys = (OV.LargeUpperStage_Latch[j] / 5) + 1;
						int ltch = (OV.LargeUpperStage_Latch[j] - (5 * (plsys - 1))) + 1;
						str += "Latch usage collision: PL Sys " + plsys + ", Latch " + ltch + "\n\n";
					}
					else latch[OV.LargeUpperStage_Latch[j]] = true;// not used, mark it
				}
			}
			else if ( (LargeUpperStage == 4) || (LargeUpperStage == 5))// Centaurs
			{
				for (int j = 0; j < 3; j++)
				{
					if (latch[OV.LargeUpperStage_Latch[j]])
					{
						// already used
						ok = false;
						int plsys = (OV.LargeUpperStage_Latch[j] / 5) + 1;
						int ltch = (OV.LargeUpperStage_Latch[j] - (5 * (plsys - 1))) + 1;
						str += "Latch usage collision: PL Sys " + plsys + ", Latch " + ltch + "\n\n";
					}
					else latch[OV.LargeUpperStage_Latch[j]] = true;// not used, mark it
				}
			}

			/////// payload latch collision ///////
			// TODO

			/////// bridge usage ///////
			// for each bay bridge payload, compare with:
			// a) bay bridge used in each active and passive payload attachment
			bool[] bbpPort = new bool[13];
			bool[] bbpStbd = new bool[13];
			bool[] bbpKeel = new bool[12];
			foreach (Mission_PLBayBridge pl in OV.PL_BayBridge)
			{
				if (pl.IsUsed)// payload "slot" used
				{
					if (pl.Bridge == Bridge_Type.Port)
					{
						bbpPort[pl.Bay - 1] = true;
					}
					else if (pl.Bridge == Bridge_Type.Starboard)
					{
						bbpStbd[pl.Bay - 1] = true;
					}
					else if (pl.Bridge == Bridge_Type.Keel)
					{
						bbpKeel[pl.Bay - 1] = true;
					}
				}
			}
			int i = 1;
			foreach (Mission_PLActive pl in OV.PL_Active)
			{
				if (pl.IsUsed)// payload "slot" used
				{
					int plididx = 0;
					foreach (Mission_PayloadLatch pl_latch in pl.Latches)
					{
						if (pl_latch.PLID != 0)// PLID defined
						{
							int bay = Defs.FindBridgeByPLID( pl_latch.PLID );
							switch (plididx)
							{
								case 0:// port 1
								case 1:// port 2
								case 2:// port 3
								case 3:// port 4
									if (bbpPort[bay - 1])
									{
										str += "Active Payload " + i + " needs used Port Bay Bridge " + bay + "\n\n";
										ok = false;
									}
									break;
								case 4:// stbd 1
								case 5:// stbd 2
								case 6:// stbd 3
								case 7:// stbd 4
									if (bbpStbd[bay - 1])
									{
										str += "Active Payload " + i + " needs used Starboard Bay Bridge " + bay + "\n\n";
										ok = false;
									}
									break;
								case 8:// keel 1
								case 9:// keel 2
								case 10:// keel 3
								case 11:// keel 4
									if (bbpKeel[bay - 1])
									{
										str += "Active Payload " + i + " needs used Keel Bay Bridge " + bay + "\n\n";
										ok = false;
									}
									break;
							}
						}
						plididx++;
					}
				}
				i++;
			}
			i = 1;
			foreach (Mission_PLPassive pl in OV.PL_Passive)
			{
				if (pl.IsUsed)// payload "slot" used
				{
					int plididx = 0;
					foreach (Mission_PayloadLatch pl_latch in pl.Latches)
					{
						if (pl_latch.PLID != 0)// PLID defined
						{
							int bay = Defs.FindBridgeByPLID( pl_latch.PLID );
							switch (plididx)
							{
								case 0:// port 1
								case 1:// port 2
								case 2:// port 3
								case 3:// port 4
									if (bbpPort[bay - 1])
									{
										str += "Passive Payload " + i + " needs used Port Bay Bridge " + bay + "\n\n";
										ok = false;
									}
									break;
								case 4:// stbd 1
								case 5:// stbd 2
								case 6:// stbd 3
								case 7:// stbd 4
									if (bbpStbd[bay - 1])
									{
										str += "Passive Payload " + i + " needs used Starboard Bay Bridge " + bay + "\n\n";
										ok = false;
									}
									break;
								case 8:// keel 1
								case 9:// keel 2
								case 10:// keel 3
								case 11:// keel 4
									if (bbpKeel[bay - 1])
									{
										str += "Passive Payload " + i + " needs used Keel Bay Bridge " + bay + "\n\n";
										ok = false;
									}
									break;
							}
						}
						plididx++;
					}
				}
				i++;
			}

			// b) bay bridge used in External Airlock
			if ((OV.Airlock == Airlock_Type.External) || (OV.ODS))
			{
				if (OV.TAA == TAA_Type.Forward)
				{
					// port and starboard bays 3 and 4
					if (bbpPort[2])
					{
						str += "External Airlock needs used Port Bay Bridge 3\n\n";
						ok = false;
					}
					if (bbpPort[3])
					{
						str += "External Airlock needs used Port Bay Bridge 4\n\n";
						ok = false;
					}
					if (bbpStbd[2])
					{
						str += "External Airlock needs used Starboard Bay Bridge 3\n\n";
						ok = false;
					}
					if (bbpStbd[3])
					{
						str += "External Airlock needs used Starboard Bay Bridge 4\n\n";
						ok = false;
					}
					// keel bay 4
					if (bbpKeel[3])
					{
						str += "External Airlock needs used Keel Bay Bridge 4\n\n";
						ok = false;
					}
				}
				else
				{
					// port and starboard bays 1 and 2
					if (bbpPort[0])
					{
						str += "External Airlock needs used Port Bay Bridge 1\n\n";
						ok = false;
					}
					if (bbpPort[1])
					{
						str += "External Airlock needs used Port Bay Bridge 2\n\n";
						ok = false;
					}
					if (bbpStbd[0])
					{
						str += "External Airlock needs used Starboard Bay Bridge 1\n\n";
						ok = false;
					}
					if (bbpStbd[1])
					{
						str += "External Airlock needs used Starboard Bay Bridge 2\n\n";
						ok = false;
					}
					// keel bay 2
					if (bbpKeel[1])
					{
						str += "External Airlock needs used Keel Bay Bridge 2\n\n";
						ok = false;
					}
				}
			}

			// c) bay bridge used in TAA
			if (OV.TAA == TAA_Type.Aft)
			{
				// port and starboard bays 3 and 4
				if (bbpPort[2])
				{
					str += "TAA needs used Port Bay Bridge 3\n\n";
					ok = false;
				}
				if (bbpPort[3])
				{
					str += "TAA needs used Port Bay Bridge 4\n\n";
					ok = false;
				}
				if (bbpStbd[2])
				{
					str += "TAA needs used Starboard Bay Bridge 3\n\n";
					ok = false;
				}
				if (bbpStbd[3])
				{
					str += "TAA needs used Starboard Bay Bridge 4\n\n";
					ok = false;
				}

				// keel bay 4
				if (bbpKeel[3])
				{
					str += "TAA needs used Keel Bay Bridge 4\n\n";
					ok = false;
				}
			}

			// d) bay bridge used in Large Upper Stage
			switch (LargeUpperStage)
			{
				case 1:// IUS 2-Stage
					if (OV.IUS_AftPosition)
					{
						// port and starboard bays 10, 12 and 13
						if (bbpPort[9])
						{
							str += "IUS ASE needs used Port Bay Bridge 10\n\n";
							ok = false;
						}
						if (bbpPort[11])
						{
							str += "IUS ASE needs used Port Bay Bridge 12\n\n";
							ok = false;
						}
						if (bbpPort[12])
						{
							str += "IUS ASE needs used Port Bay Bridge 13\n\n";
							ok = false;
						}
						if (bbpStbd[9])
						{
							str += "IUS ASE needs used Starboard Bay Bridge 10\n\n";
							ok = false;
						}
						if (bbpStbd[11])
						{
							str += "IUS ASE needs used Starboard Bay Bridge 12\n\n";
							ok = false;
						}
						if (bbpStbd[12])
						{
							str += "IUS ASE needs used Starboard Bay Bridge 13\n\n";
							ok = false;
						}

						// keel bay 10
						if (bbpKeel[9])
						{
							str += "IUS ASE needs used Keel Bay Bridge 10\n\n";
							ok = false;
						}
					}
					else
					{
						// port and starboard bays 9, 11 and 12
						if (bbpPort[8])
						{
							str += "IUS ASE needs used Port Bay Bridge 9\n\n";
							ok = false;
						}
						if (bbpPort[10])
						{
							str += "IUS ASE needs used Port Bay Bridge 11\n\n";
							ok = false;
						}
						if (bbpPort[11])
						{
							str += "IUS ASE needs used Port Bay Bridge 12\n\n";
							ok = false;
						}
						if (bbpStbd[8])
						{
							str += "IUS ASE needs used Starboard Bay Bridge 9\n\n";
							ok = false;
						}
						if (bbpStbd[10])
						{
							str += "IUS ASE needs used Starboard Bay Bridge 11\n\n";
							ok = false;
						}
						if (bbpStbd[11])
						{
							str += "IUS ASE needs used Starboard Bay Bridge 12\n\n";
							ok = false;
						}

						// keel bay 9
						if (bbpKeel[8])
						{
							str += "IUS ASE needs used Keel Bay Bridge 9\n\n";
							ok = false;
						}
					}
					break;
				case 2:// IUS Twin-Stage
					break;
				case 3:// IUS 3-Stage
					break;
				case 4:// Centaur G
					// CISS
					// port and starboard bays 12 and 13
					if (bbpPort[11])
					{
						str += "CISS needs used Port Bay Bridge 12\n\n";
						ok = false;
					}
					if (bbpPort[12])
					{
						str += "CISS needs used Port Bay Bridge 13\n\n";
						ok = false;
					}
					if (bbpStbd[11])
					{
						str += "CISS needs used Starboard Bay Bridge 12\n\n";
						ok = false;
					}
					if (bbpStbd[12])
					{
						str += "CISS needs used Starboard Bay Bridge 13\n\n";
						ok = false;
					}

					// keel bay 12
					if (bbpKeel[11])
					{
						str += "CISS needs used Keel Bay Bridge 12\n\n";
						ok = false;
					}

					// Centaur
					// port starboard and keel bay 9
					if (bbpPort[8])
					{
						str += "Centaur needs used Port Bay Bridge 9\n\n";
						ok = false;
					}
					if (bbpStbd[8])
					{
						str += "Centaur needs used Starboard Bay Bridge 9\n\n";
						ok = false;
					}
					if (bbpKeel[8])
					{
						str += "Centaur needs used Keel Bay Bridge 9\n\n";
						ok = false;
					}
					break;
				case 5:// Centaur G'
					// CISS
					// port and starboard bays 11 and 13
					if (bbpPort[10])
					{
						str += "CISS needs used Port Bay Bridge 11\n\n";
						ok = false;
					}
					if (bbpPort[12])
					{
						str += "CISS needs used Port Bay Bridge 13\n\n";
						ok = false;
					}
					if (bbpStbd[10])
					{
						str += "CISS needs used Starboard Bay Bridge 11\n\n";
						ok = false;
					}
					if (bbpStbd[12])
					{
						str += "CISS needs used Starboard Bay Bridge 13\n\n";
						ok = false;
					}

					// keel bay 12
					if (bbpKeel[11])
					{
						str += "CISS needs used Keel Bay Bridge 12\n\n";
						ok = false;
					}

					// Centaur
					// port starboard and keel bay 7
					if (bbpPort[6])
					{
						str += "Centaur needs used Port Bay Bridge 7\n\n";
						ok = false;
					}
					if (bbpStbd[6])
					{
						str += "Centaur needs used Starboard Bay Bridge 7\n\n";
						ok = false;
					}
					if (bbpKeel[6])
					{
						str += "Centaur needs used Keel Bay Bridge 7\n\n";
						ok = false;
					}
					break;
			}

			// TODO e) bay bridge used in Small Upper Stages

			// f) bay bridge used in EDO pallet
			if (OV.EDOPallet == 1)// TODO handle dual pallet
			{
				// port, starboard and keel bay 12
				if (bbpPort[11])
				{
					str += "EDO pallet needs used Port Bay Bridge 12\n\n";
					ok = false;
				}
				if (bbpStbd[11])
				{
					str += "EDO pallet needs used Starboard Bay Bridge 12\n\n";
					ok = false;
				}
				if (bbpKeel[11])
				{
					str += "EDO pallet needs used Keel Bay Bridge 12\n\n";
					ok = false;
				}
			}

			// TODO g) bay bridge used in OMS Kit


			/////// payload settings ///////
			// active
			i = 1;
			foreach (Mission_PLActive pl in OV.PL_Active)
			{
				if (pl.IsUsed && pl.HasPayload)// payload "slot" used and has payload
				{
					if (pl.Payload.Name.Length == 0)
					{
						str += "Active Payload " + i + " Name is empty\n\n";
						ok = false;
					}
					if (pl.Payload.VesselClass.Length == 0)
					{
						str += "Active Payload " + i + " Vessel Class is empty\n\n";
						ok = false;
					}
					if (pl.Payload.AttachmentID < 0)
					{
						str += "Active Payload " + i + " attachment ID is negative\n\n";
						ok = false;
					}
				}
				i++;
			}

			// passive
			i = 1;
			foreach (Mission_PLPassive pl in OV.PL_Passive)
			{
				if (pl.IsUsed)// payload "slot" used
				{
					if (pl.Payload.Name.Length == 0)
					{
						str += "Passive Payload Name is empty\n\n";
						ok = false;
					}
					if (pl.Payload.VesselClass.Length == 0)
					{
						str += "Passive Payload " + i + " Vessel Class is empty\n\n";
						ok = false;
					}
					if (pl.Payload.AttachmentID < 0)
					{
						str += "Passive Payload " + i + " attachment ID is negative\n\n";
						ok = false;
					}
				}
				i++;
			}

			// bay bridge
			i = 1;
			foreach (Mission_PLBayBridge pl in OV.PL_BayBridge)
			{
				if (pl.IsUsed)// payload "slot" used
				{
					if (pl.Payload.Name.Length == 0)
					{
						str += "Bay Bridge Payload " + i + " Name is empty\n\n";
						ok = false;
					}
					if (pl.Payload.VesselClass.Length == 0)
					{
						str += "Bay Bridge Payload " + i + " Vessel Class is empty\n\n";
						ok = false;
					}
					if (pl.Payload.AttachmentID < 0)
					{
						str += "Bay Bridge Payload " + i + " attachment ID is negative\n\n";
						ok = false;
					}
				}
				i++;
			}


			// upper stages
			if (LargeUpperStage != 0)
			{
				if (LargeUpperStage_PL.Name.Length == 0)
				{
					str += "Large Upper Stage Payload Name is empty\n\n";
					ok = false;
				}
				if (LargeUpperStage_PL.VesselClass.Length == 0)
				{
					str += "Large Upper Stage Payload Class is empty\n\n";
					ok = false;
				}
				if (LargeUpperStage_PL.AttachmentID < 0)
				{
					str += "Large Upper Stage Payload attachment ID is negative\n\n";
					ok = false;
				}
			}

			for (i = 0; i < Defs.SMALLUPPERSTAGE_MAX; i++)
			{
				if (SmallUpperStage[i] == 0) continue;

				if (SmallUpperStage_PL[i].Name.Length == 0)
				{
					str += "Small Upper Stage " + i + " Payload Name is empty\n\n";
					ok = false;
				}
				if (SmallUpperStage_PL[i].VesselClass.Length == 0)
				{
					str += "Small Upper Stage " + i + " Payload Class is empty\n\n";
					ok = false;
				}
				if (SmallUpperStage_PL[i].AttachmentID < 0)
				{
					str += "Small Upper Stage " + i + " Payload attachment ID is negative\n\n";
					ok = false;
				}
			}

			// mpm pl
			if (OV.StbdLongeronSill == LongeronSillHardware_Type.PayloadMPM)
			{
				// pedestals
				if (!OV.Stbd_PL_MPM.HasShoulder && !OV.Stbd_PL_MPM.HasForward && !OV.Stbd_PL_MPM.HasMid && !OV.Stbd_PL_MPM.HasAft)
				{
					str += "Stbd MPM Pedestals are not defined\n\n";
					ok = false;
				}

				// TODO attachment

				// TODO mrl

				// pl
				if (OV.Stbd_PL_MPM.HasPayload)
				{
					if (OV.Stbd_PL_MPM.Payload.Name.Length == 0)
					{
						str += "Stbd MPM Payload Name is empty\n\n";
						ok = false;
					}
					if (OV.Stbd_PL_MPM.Payload.VesselClass.Length == 0)
					{
						str += "Stbd MPM Payload Class is empty\n\n";
						ok = false;
					}
					if (OV.Stbd_PL_MPM.Payload.AttachmentID < 0)
					{
						str += "Stbd MPM Payload attachment ID is negative\n\n";
						ok = false;
					}
				}
			}


			/////// payload adapter settings ///////
			if (LargeUpperStage != 0)
			{
				if (LargeUpperStage_Adapter_Mesh.Length == 0)
				{
					str += "Large Upper Stage Payload Adapter Mesh is empty\n\n";
					ok = false;
				}
				if (LargeUpperStage_Adapter_Mass <= 0)
				{
					str += "Large Upper Stage Payload Adapter Mass is equal or less than 0\n\n";
					ok = false;
				}
				if (LargeUpperStage_Adapter_Offset < 0)
				{
					str += "Large Upper Stage Payload Adapter Offset is equal or less than 0\n\n";
					ok = false;
				}
			}

			for (i = 0; i < Defs.SMALLUPPERSTAGE_MAX; i++)
			{
				if (SmallUpperStage[i] == 0) continue;

				if (SmallUpperStage_Adapter_Mesh[i].Length == 0)
				{
					str += "Small Upper Stage " + i + " Payload Adapter Mesh is empty\n\n";
					ok = false;
				}
				if (SmallUpperStage_Adapter_Mass[i] <= 0)
				{
					str += "Small Upper Stage " + i + " Payload Adapter Mass is equal or less than 0\n\n";
					ok = false;
				}
				if (SmallUpperStage_Adapter_Offset[i] < 0)
				{
					str += "Small Upper Stage " + i + " Payload Adapter Offset is equal or less than 0\n\n";
					ok = false;
				}
			}

			/////// propellant load check ///////
			if (OV.FRCS_Load < Defs.MINLOAD_FRCS)
			{
				str += "FRCS propellant load under minimum\n\n";
				ok = false;
			}
			if (OV.FRCS_Load > Defs.MAXLOAD_FRCS)
			{
				str += "FRCS propellant load over maximum\n\n";
				ok = false;
			}

			if (OV.LRCS_Load < Defs.MINLOAD_ARCS)
			{
				str += "LRCS propellant load under minimum\n\n";
				ok = false;
			}
			if (OV.LRCS_Load > Defs.MAXLOAD_ARCS)
			{
				str += "LRCS propellant load over maximum\n\n";
				ok = false;
			}

			if (OV.RRCS_Load < Defs.MINLOAD_ARCS)
			{
				str += "RRCS propellant load under minimum\n\n";
				ok = false;
			}
			if (OV.RRCS_Load > Defs.MAXLOAD_ARCS)
			{
				str += "RRCS propellant load over maximum\n\n";
				ok = false;
			}

			if (OV.LOMS_Load < Defs.MINLOAD_OMS)
			{
				str += "LOMS propellant load under minimum\n\n";
				ok = false;
			}
			if (OV.LOMS_Load > Defs.MAXLOAD_OMS)
			{
				str += "LOMS propellant load over maximum\n\n";
				ok = false;
			}

			if (OV.ROMS_Load < Defs.MINLOAD_OMS)
			{
				str += "ROMS propellant load under minimum\n\n";
				ok = false;
			}
			if (OV.ROMS_Load > Defs.MAXLOAD_OMS)
			{
				str += "ROMS propellant load over maximum\n\n";
				ok = false;
			}

			if (OV.OMSKitTanks != 0)
			{
				if (OV.KOMS_Load < (Defs.MINLOAD_OMS + (Defs.MAXLOAD_OMS * (OV.OMSKitTanks - 1))))
				{
					str += "OMS Kit propellant load under minimum\n\n";
					ok = false;
				}
				if (OV.KOMS_Load > (Defs.MAXLOAD_OMS * OV.OMSKitTanks))
				{
					str += "OMS Kit propellant load over maximum\n\n";
					ok = false;
				}
			}

			/////// CISS pad version check ///////
			if ((LargeUpperStage == 4) || (LargeUpperStage == 5))
			{
				if (((LaunchPad != 0) && (LaunchPad != 1)) || (LaunchPadType != 4))
				{
					str += "Launch Pad is not 1986 version of LC-39A or LC-39B (Centaur is used)\n\n";
					ok = false;
				}
			}

			/////// landing site check ///////
			foreach (Tuple<string,string> ls in OV.LandingSiteTable)
			{
				// check pri rw
				if (FindLandingSite( OV.LandingSiteDB, ls.Item1 ) == -1)
				{
					str += "Invalid Landing Site " + ls.Item1 + "\n\n";
					ok = false;
				}
				// check sec rw
				if (FindLandingSite( OV.LandingSiteDB, ls.Item2 ) == -1)
				{
					str += "Invalid Landing Site " + ls.Item2 + "\n\n";
					ok = false;
				}
			}
			return ok;
		}

		public void SetMECOparams( double inc, double alt, double vel, double fpa )
		{
			MECO_Inc = inc;
			MECO_Alt = alt;
			MECO_Vel = vel;
			MECO_FPA = fpa;
			return;
		}

		// sets OBSS in starboard MPM
		public void SetOBSS()
		{
			OV.StbdLongeronSill = LongeronSillHardware_Type.PayloadMPM;

			OV.Stbd_PL_MPM.HasShoulder = true;
			OV.Stbd_PL_MPM.HasForward  = true;
			OV.Stbd_PL_MPM.HasMid = false;
			OV.Stbd_PL_MPM.HasAft = true;

			OV.Stbd_PL_MPM.ShoulderMesh = "SSV\\MPMUpperPedestal_Starboard_Shoulder_OBSS";
			OV.Stbd_PL_MPM.ForwardMesh = "SSV\\MPMUpperPedestal_Starboard_OBSS";
			OV.Stbd_PL_MPM.MidMesh = "";
			OV.Stbd_PL_MPM.AftMesh = "SSV\\MPMUpperPedestal_Starboard_OBSS";

			OV.Stbd_PL_MPM.ShoulderPedestalMRL = MRL_Type.Forward;
			OV.Stbd_PL_MPM.ForwardPedestalMRL = MRL_Type.Mid;
			OV.Stbd_PL_MPM.MidPedestalMRL = MRL_Type.None;
			OV.Stbd_PL_MPM.AftPedestalMRL = MRL_Type.Aft;

			OV.Stbd_PL_MPM.Attachment = MPM_Attachment_Type.Forward;

			OV.Stbd_PL_MPM.HasPayload = true;

			OV.Stbd_PL_MPM.Payload.Name = "OBSS";
			OV.Stbd_PL_MPM.Payload.VesselClass = "SSV_OBSS";
			OV.Stbd_PL_MPM.Payload.AttachmentID = 0;
			OV.Stbd_PL_MPM.Payload.ScnParams = "";
			return;
		}

		public int FindLandingSite( List<Mission_OV.LandingSiteData> lsDB, string rw )
		{
			int i = 0;
			foreach (Mission_OV.LandingSiteData ls in lsDB)
			{
				if (ls.id == rw) return i;
				i++;
			}
			return -1;
		}


		/// <summary>
		/// The name of the mission
		/// </summary>
		private string name;
		public string Name
		{
			get { return name; }
			set
			{
				name = value;
				OnPropertyChanged( "Name" );
			}
		}

		/// <summary>
		/// Mission description
		/// </summary>
		private string description;
		public string Description
		{
			get { return description; }
			set
			{
				description = value;
				OnPropertyChanged( "Description" );
			}
		}



		/// <summary>
		/// MECO target inclination
		/// </summary>
		private double meco_inc;
		public double MECO_Inc
		{
			get { return meco_inc; }
			set { meco_inc = value; OnPropertyChanged( "MECO_Inc" ); }
		}

		/// <summary>
		/// MECO target longitude of ascending node
		/// </summary>
		/*private double meco_lan;
		public double MECO_LAN
		{
			get { return meco_lan; }
			set { meco_lan = value; }
		}*/

		/// <summary>
		/// MECO target altitude
		/// </summary>
		private double meco_alt;
		public double MECO_Alt
		{
			get { return meco_alt; }
			set { meco_alt = value; OnPropertyChanged( "MECO_Alt" ); }
		}

		/// <summary>
		/// MECO target velocity
		/// </summary>
		private double meco_vel;
		public double MECO_Vel
		{
			get { return meco_vel; }
			set { meco_vel = value; OnPropertyChanged( "MECO_Vel" ); }
		}

		/// <summary>
		/// MECO target flight path angle
		/// </summary>
		private double meco_fpa;
		public double MECO_FPA
		{
			get { return meco_fpa; }
			set { meco_fpa = value; OnPropertyChanged( "MECO_FPA" ); }
		}








		/// <summary>
		/// Launch Site
		/// 0 = KSC
		/// 1 = VAFB
		/// </summary>
		private int launchsite;
		public int LaunchSite
		{
			get { return launchsite; }
			set
			{
				launchsite = value;
				OnPropertyChanged( "LaunchSite" );
			}
		}

		/// <summary>
		/// Launch Pad
		/// 0 = LC-39A (for KSC launch site only)
		/// 1 = LC-39B (for KSC launch site only)
		/// (0 = SLC-6 (for VAFB launch site only))
		/// </summary>
		private int launchpad;
		public int LaunchPad
		{
			get { return launchpad; }
			set
			{
				launchpad = value;
				OnPropertyChanged( "LaunchPad" );
			}
		}

		/// <summary>
		/// Launch Pad Type
		/// 0 = 1981 (for KSC launch site only)
		/// 1 = 1982 (for KSC launch site only)
		/// 2 = 1983 (for KSC launch site only)
		/// 3 = 1985 (for KSC launch site only)
		/// 4 = 1986 (for KSC launch site only)
		/// 5 = 1988 (for KSC launch site only)
		/// 6 = 1995 (for KSC launch site only)
		/// 7 = 2007 (for KSC launch site only)
		/// (0 = SLC-6 (for VAFB launch site only))
		/// </summary>
		private int launchpadtype;
		public int LaunchPadType
		{
			get { return launchpadtype; }
			set
			{
				launchpadtype = value;
				OnPropertyChanged( "LaunchPadType" );
			}
		}

		/// <summary>
		/// MLP number (for KSC launch site only)
		/// 0 = MLP-1
		/// 1 = MLP-2
		/// 2 = MLP-3
		/// </summary>
		private int mlp;
		public int MLP
		{
			get { return mlp; }
			set
			{
				mlp = value;
				OnPropertyChanged( "MLP" );
			}
		}

		/// <summary>
		/// The date/time at the start of the simulation
		/// </summary>
		private int t0year;
		public int T0Year
		{
			get { return t0year; }
			set
			{
				t0year = value;
				OnPropertyChanged( "T0Year" );
			}
		}
		private int t0month;
		public int T0Month
		{
			get { return t0month; }
			set
			{
				t0month = value;
				OnPropertyChanged( "T0Month" );
			}
		}
		private int t0day;
		public int T0Day
		{
			get { return t0day; }
			set
			{
				t0day = value;
				OnPropertyChanged( "T0Day" );
			}
		}
		private int t0hour;
		public int T0Hour
		{
			get { return t0hour; }
			set
			{
				t0hour = value;
				OnPropertyChanged( "T0Hour" );
			}
		}
		private int t0minute;
		public int T0Minute
		{
			get { return t0minute; }
			set
			{
				t0minute = value;
				OnPropertyChanged( "T0Minute" );
			}
		}
		private double t0second;
		public double T0Second
		{
			get { return t0second; }
			set
			{
				t0second = value;
				OnPropertyChanged( "T0Second" );
			}
		}



		private bool omskit;
		public bool OMSKit
		{
			get { return omskit; }
			set
			{
				omskit = value;
				OnPropertyChanged( "OMSKit" );
			}
		}





		private List<AvailableVessel> availablevessels;
		public string[] AvailableVessels
		{
			get
			{
				if (availablevessels.Count == 0) return null;

				string[] list = new string[availablevessels.Count];

				for (int i = 0; i < availablevessels.Count; i++)
					list[i] = availablevessels[i].name;
				return list;
			}
			set{}
		}







		/// <summary>
		/// "Large" Upper Stage used:
		/// 0: none
		/// 1: IUS 2-Stage
		/// 2: IUS Twin-Stage
		/// 3: IUS 3-Stage
		/// 4: Centaur G
		/// 5: Centaur G'
		/// </summary>
		private int largeupperstage;
		public int LargeUpperStage
		{
			get { return largeupperstage; }
			set
			{
				largeupperstage = value;
				OnPropertyChanged( "LargeUpperStage" );
			}
		}

		/// <summary>
		/// Name of "large" upper stage vessel
		/// </summary>
		private string largeupperstage_name;
		public string LargeUpperStage_Name
		{
			get { return largeupperstage_name; }
			set
			{
				largeupperstage_name = value;
				OnPropertyChanged( "LargeUpperStage_Name" );
			}
		}

		/// <summary>
		/// Payload attached to "large" upper stage
		/// </summary>
		private Mission_Payload largeupperstage_pl;
		public Mission_Payload LargeUpperStage_PL
		{
			get { return largeupperstage_pl; }
			set
			{
				largeupperstage_pl = value;
				OnPropertyChanged( "LargeUpperStage_PL" );
			}
		}

		/// <summary>
		/// Mesh of payload adapter on "large" upper stage
		/// </summary>
		private string largeupperstage_adapter_mesh;
		public string LargeUpperStage_Adapter_Mesh
		{
			get { return largeupperstage_adapter_mesh; }
			set
			{
				largeupperstage_adapter_mesh = value;
				OnPropertyChanged( "LargeUpperStage_Adapter_Mesh" );
			}
		}

		/// <summary>
		/// Offset of mesh of payload adapter on "large" upper stage
		/// </summary>
		private double largeupperstage_adapter_offset;
		public double LargeUpperStage_Adapter_Offset
		{
			get { return largeupperstage_adapter_offset; }
			set
			{
				largeupperstage_adapter_offset = value;
				OnPropertyChanged( "LargeUpperStage_Adapter_Offset" );
			}
		}

		/// <summary>
		/// Mass of payload adapter on "large" upper stage
		/// </summary>
		private double largeupperstage_adapter_mass;
		public double LargeUpperStage_Adapter_Mass
		{
			get { return largeupperstage_adapter_mass; }
			set
			{
				largeupperstage_adapter_mass = value;
				OnPropertyChanged( "LargeUpperStage_Adapter_Mass" );
			}
		}

		/// <summary>
		/// The name of the IUS texture 
		/// </summary>
		private string ius_texture;
		public string IUS_Texture
		{
			get { return ius_texture; }
			set
			{
				ius_texture = value;
				OnPropertyChanged( "IUS_Texture" );
			}
		}

		/// <summary>
		/// IUS 1º stage propellant load
		/// </summary>
		private double ius_1stageload;
		public double IUS_1StageLoad
		{
			get { return ius_1stageload; }
			set
			{
				ius_1stageload = value;
				OnPropertyChanged( "IUS_1StageLoad" );
			}
		}

		/// <summary>
		/// IUS 2º stage propellant load
		/// </summary>
		private double ius_2stageload;
		public double IUS_2StageLoad
		{
			get { return ius_2stageload; }
			set
			{
				ius_2stageload = value;
				OnPropertyChanged( "IUS_2StageLoad" );
			}
		}

		/// <summary>
		/// Number of IUS RCS tanks
		/// </summary>
		private int ius_rcstanks;
		public int IUS_RCSTanks
		{
			get { return ius_rcstanks; }
			set
			{
				ius_rcstanks = value;
				OnPropertyChanged( "IUS_RCSTanks" );
			}
		}

		/// <summary>
		/// IUS has 4 antennas
		/// </summary>
		private bool ius_4antennas;
		public bool IUS_4Antennas
		{
			get { return ius_4antennas; }
			set
			{
				ius_4antennas = value;
				OnPropertyChanged( "IUS_4Antennas" );
			}
		}



		/// <summary>
		/// "Small" Upper Stages used:
		/// 0: none
		/// 1: PAM-D
		/// 2: PAM-DII
		/// 3: PAM-A
		/// </summary>
		private int[] smallupperstage;
		public int[] SmallUpperStage
		{
			get { return smallupperstage; }
			set
			{
				smallupperstage = value;
				OnPropertyChanged( "SmallUpperStage" );
			}
		}

		/// <summary>
		/// Name of "small" upper stage vessels
		/// </summary>
		private string[] smallupperstage_name;
		public string[] SmallUpperStage_Name
		{
			get { return smallupperstage_name; }
			set
			{
				smallupperstage_name = value;
				OnPropertyChanged( "SmallUpperStage_Name" );
			}
		}

		/// <summary>
		/// Payload attached to "small" upper stages
		/// </summary>
		private Mission_Payload[] smallupperstage_pl;
		public Mission_Payload[] SmallUpperStage_PL
		{
			get { return smallupperstage_pl; }
			set
			{
				smallupperstage_pl = value;
				OnPropertyChanged( "SmallUpperStage_PL" );
			}
		}

		/// <summary>
		/// Propellant load of "small" upper stages
		/// </summary>
		private double[] smallupperstage_load;
		public double[] SmallUpperStage_Load
		{
			get { return smallupperstage_load; }
			set
			{
				smallupperstage_load = value;
				OnPropertyChanged( "SmallUpperStage_Load" );
			}
		}

		/// <summary>
		/// Mesh of payload adapter on "small" upper stages
		/// </summary>
		private string[] smallupperstage_adapter_mesh;
		public string[] SmallUpperStage_Adapter_Mesh
		{
			get { return smallupperstage_adapter_mesh; }
			set
			{
				smallupperstage_adapter_mesh = value;
				OnPropertyChanged( "SmallUpperStage_Adapter_Mesh" );
			}
		}

		/// <summary>
		/// Offset of mesh of payload adapter on "small" upper stages
		/// </summary>
		private double[] smallupperstage_adapter_offset;
		public double[] SmallUpperStage_Adapter_Offset
		{
			get { return smallupperstage_adapter_offset; }
			set
			{
				smallupperstage_adapter_offset = value;
				OnPropertyChanged( "SmallUpperStage_Adapter_Offset" );
			}
		}

		/// <summary>
		/// Mass of payload adapter on "small" upper stages
		/// </summary>
		private double[] smallupperstage_adapter_mass;
		public double[] SmallUpperStage_Adapter_Mass
		{
			get { return smallupperstage_adapter_mass; }
			set
			{
				smallupperstage_adapter_mass = value;
				OnPropertyChanged( "SmallUpperStage_Adapter_Mass" );
			}
		}







		private string missionfile;
		public string MissionFile
		{
			get { return missionfile; }
			set { missionfile = value; }
		}




		private Mission_OV ov;
		public Mission_OV OV
		{
			get { return ov; }
			set
			{
				ov = value;
				OnPropertyChanged( "OV" );
			}
		}

		private Mission_ET et;
		public Mission_ET ET
		{
			get { return et; }
			set
			{
				et = value;
				OnPropertyChanged( "ET" );
			}
		}

		private Mission_SRB srb;
		public Mission_SRB SRB
		{
			get { return srb; }
			set
			{
				srb = value;
				OnPropertyChanged( "SRB" );
			}
		}

		private ObservableCollection<Mission_Vessel> othervessels;
		public ObservableCollection<Mission_Vessel> OtherVessels
		{
			get { return othervessels; }
			set
			{
				othervessels = value;
				OnPropertyChanged( "OtherVessels" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}


		public static int String2EnumIdx<TEnum>( TEnum _enum, string val )
		{
			string[] names = Enum.GetNames( typeof( TEnum ) );
			int i = 0;
			foreach (string str in names)
			{
				if (str == val) return i;
				i++;
			}
			return -1;
		}
	}
}
