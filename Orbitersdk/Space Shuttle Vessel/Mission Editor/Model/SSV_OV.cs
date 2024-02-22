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
2020/04/08   GLS
2020/05/01   GLS
2020/05/06   GLS
2020/05/24   GLS
2020/05/31   GLS
2020/06/12   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/07/02   GLS
2020/07/03   GLS
2020/07/08   GLS
2020/07/11   GLS
2020/07/12   GLS
2020/08/22   GLS
2020/08/23   GLS
2020/08/29   GLS
2020/08/31   GLS
2020/09/02   GLS
2020/09/03   GLS
2020/10/05   GLS
2020/10/09   GLS
2020/10/10   GLS
2020/10/11   GLS
2021/02/16   GLS
2021/05/26   GLS
2021/05/30   GLS
2021/06/01   GLS
2021/06/02   GLS
2021/06/03   GLS
2021/06/07   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/06/13   GLS
2021/06/15   GLS
2021/06/16   GLS
2021/06/28   GLS
2021/07/02   GLS
2021/08/01   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/10   GLS
2021/12/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/01   GLS
2022/01/02   GLS
2022/01/10   GLS
2022/01/24   GLS
2022/02/16   GLS
2022/02/17   GLS
2022/03/04   GLS
2022/03/06   GLS
2022/05/02   GLS
2022/05/13   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/08/10   GLS
2022/08/30   GLS
2022/09/10   GLS
2022/09/11   GLS
2022/09/25   GLS
2022/10/17   GLS
2022/11/25   GLS
2022/12/06   GLS
2022/12/21   GLS
2023/02/03   GLS
2023/02/06   GLS
2023/02/17   GLS
2023/02/19   GLS
2023/04/16   GLS
2023/04/23   GLS
2023/04/26   GLS
2023/04/29   GLS
2023/06/03   GLS
2023/08/06   GLS
2023/11/12   GLS
2024/02/02   GLS
2024/02/11   GLS
2024/02/19   GLS
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
using System.ComponentModel;
using System.Collections.Generic;
using static SSVMissionEditor.model.Scenario;


namespace SSVMissionEditor.model
{
	public struct SSVscnObject
	{
		public string name;
		public List<Tuple<string,string>> param_val;
	}


	public struct SSVSimpleGPCSoftwareBlock
	{
		public string name;
		public List<Tuple<string,string>> param_val;
	}

	public struct SSVSubsystemBlock
	{
		public string name;
		public List<SSVscnObject> obj;
		public List<Tuple<string,string>> param_val;
		public List<SSVSimpleGPCSoftwareBlock> gpcsw;
	}


	public struct SSVPanelBlock
	{
		public string name;
		public List<SSVscnObject> obj;
		public List<Tuple<string,string>> switch_pos;
	}

	public class SSV_OV : OrbiterVessel
	{
		public SSV_OV( Mission mission, MFDtype[] mfds )
		{
			LOMS = 80.0;
			ROMS = 80.0;
			FRCS = 99.0;
			LRCS = 92.3;
			RRCS = 92.3;

			_class = "SSV_OV";
			name = mission.OV.Name.ToString();

			this.mission = mission;
			this.mfds = mfds;

			subsys = new List<SSVSubsystemBlock>();
			panels = new List<SSVPanelBlock>();
		}

		public override void PreSave( MissionPhase missionphase )
		{
			// build state from "mission" and "missionphase"
			switch (missionphase)
			{
				case MissionPhase.LaunchT9m:
					config = 0;
					vcpos = 0;
					sbtc_l = 1.0;
					sbtc_r = 1.0;
					statuslanded = true;
					statusplanet = "Earth";
					poslon = 0.0;
					poslat = 0.0;
					heading = 0.0;
					alt = 0.0;
					afcmode = 7;

					prplevel.Clear();
					prplevel.Add( Tuple.Create( 0, mission.OV.LOMS_Load / Defs.MAXLOAD_OMS ) );// LOMS
					prplevel.Add( Tuple.Create( 1, mission.OV.ROMS_Load / Defs.MAXLOAD_OMS ) );// ROMS
					// OMS kit
					prplevel.Add( Tuple.Create( 3, mission.OV.FRCS_Load / Defs.MAXLOAD_FRCS ) );// FRCS
					prplevel.Add( Tuple.Create( 4, mission.OV.LRCS_Load / Defs.MAXLOAD_ARCS ) );// LRCS
					prplevel.Add( Tuple.Create( 5, mission.OV.RRCS_Load / Defs.MAXLOAD_ARCS ) );// RRCS
					prplevel.Add( Tuple.Create( 6, 1.0 ) );// MPS
					prplevel.Add( Tuple.Create( 7, 1.0 ) );// SRBs

					attached.Clear();
					if (mission.LaunchSite == 0)
					{
						if (mission.MLP == 0) attached.Add( Tuple.Create( 0, 0, "MLP-1" ) );
						else if (mission.MLP == 1) attached.Add( Tuple.Create( 0, 0, "MLP-2" ) );
						else attached.Add( Tuple.Create( 0, 0, "MLP-3" ) );
					}
					else attached.Add( Tuple.Create( 0, 0, "SLC-6" ) );

					// subystems
					subsys.Clear();
					Subsystems_LaunchT9m();

					// panels
					panels.Clear();
					Panels_LaunchT9m();

					// set MFDs
					SetMFDs_LaunchT9m();
					break;
				case MissionPhase.LaunchT31s:
					config = 0;
					vcpos = 0;
					sbtc_l = 1.0;
					sbtc_r = 1.0;
					statuslanded = true;
					statusplanet = "Earth";
					poslon = 0.0;
					poslat = 0.0;
					heading = 0.0;
					alt = 0.0;
					afcmode = 7;

					prplevel.Clear();
					prplevel.Add( Tuple.Create( 0, mission.OV.LOMS_Load / Defs.MAXLOAD_OMS ) );// LOMS
					prplevel.Add( Tuple.Create( 1, mission.OV.ROMS_Load / Defs.MAXLOAD_OMS ) );// ROMS
					// OMS kit
					prplevel.Add( Tuple.Create( 3, mission.OV.FRCS_Load / Defs.MAXLOAD_FRCS ) );// FRCS
					prplevel.Add( Tuple.Create( 4, mission.OV.LRCS_Load / Defs.MAXLOAD_ARCS ) );// LRCS
					prplevel.Add( Tuple.Create( 5, mission.OV.RRCS_Load / Defs.MAXLOAD_ARCS ) );// RRCS
					prplevel.Add( Tuple.Create( 6, 1.0 ) );// MPS
					prplevel.Add( Tuple.Create( 7, 1.0 ) );// SRBs

					attached.Clear();
					if (mission.LaunchSite == 0)
					{
						if (mission.MLP == 0) attached.Add( Tuple.Create( 0, 0, "MLP-1" ) );
						else if (mission.MLP == 1) attached.Add( Tuple.Create( 0, 0, "MLP-2" ) );
						else attached.Add( Tuple.Create( 0, 0, "MLP-3" ) );
					}
					else attached.Add( Tuple.Create( 0, 0, "SLC-6" ) );

					// subystems
					subsys.Clear();
					Subsystems_LaunchT31s();

					// panels
					panels.Clear();
					Panels_LaunchT31s();

					// set MFDs
					SetMFDs_LaunchT31s();
					break;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  MISSION " + mission.MissionFile );

			scn.WriteLine( "  CONFIGURATION " + config );

			scn.WriteLine( "  VC_POS " + vcpos );

			scn.WriteLine( "  SBTC " + string.Format( "{0:f2} {1:f2}", sbtc_l, sbtc_r ).Replace( ',', '.' ) );

			if (!String.IsNullOrEmpty( staticcargo_mesh ))
			{
				scn.WriteLine( "  CARGO_STATIC_MESH " + staticcargo_mesh );
				if ((staticcargo_ofsx != 0) && (staticcargo_ofsy != 0) && (staticcargo_ofsz != 0)) scn.WriteLine( "  CARGO_STATIC_OFS " + string.Format( "{0:f2} {1:f2} {2:f2}", staticcargo_ofsx, staticcargo_ofsy, staticcargo_ofsz ).Replace( ',', '.' ) );
			}
			if (plmass > 0) scn.WriteLine( "  PAYLOAD_MASS " + string.Format( "{0:f2}", plmass ).Replace( ',', '.' ) );

			// subsystems
			for (int i = 0; i < subsys.Count; i++)
			{
				scn.WriteLine( "@SUBSYSTEM " + subsys[i].name );

				for (int j = 0; j < subsys[i].param_val.Count; j++)
				{
					scn.WriteLine( "  " + subsys[i].param_val[j].Item1 + " " + subsys[i].param_val[j].Item2 );
				}

				if (subsys[i].obj != null)
				{
				for (int j = 0; j < subsys[i].obj.Count; j++)
				{
					scn.WriteLine( "  @OBJECT " + subsys[i].obj[j].name );

					for (int k = 0; k < subsys[i].obj[j].param_val.Count; k++)
					{
						scn.WriteLine( "  " + subsys[i].obj[j].param_val[k].Item1 + " " + subsys[i].obj[j].param_val[k].Item2 );
					}

					scn.WriteLine( "  @ENDOBJECT" );
				}
				}

				// SimpleGPCSoftware
				if (subsys[i].gpcsw != null)
				{
					for (int k = 0; k < subsys[i].gpcsw.Count; k++)
					{
						scn.WriteLine( "  @BEGINSOFTWARE " + subsys[i].gpcsw[k].name );
						for (int j = 0; j < subsys[i].gpcsw[k].param_val.Count; j++)
						{
							scn.WriteLine( "  " + subsys[i].gpcsw[k].param_val[j].Item1 + " " + subsys[i].gpcsw[k].param_val[j].Item2 );
						}
						scn.WriteLine( "  @ENDSOFTWARE" );
					}
				}

				scn.WriteLine( "@ENDSUBSYSTEM" );
			}

			// panels
			for (int i = 0; i < panels.Count; i++)
			{
				scn.WriteLine( "@PANEL " + panels[i].name );

				for (int j = 0; j < panels[i].obj.Count; j++)
				{
					scn.WriteLine( "  @OBJECT \"" + panels[i].obj[j].name + "\"" );

					for (int k = 0; k < panels[i].obj[j].param_val.Count; k++)
					{
						scn.WriteLine( "  " + panels[i].obj[j].param_val[k].Item1 + " " + panels[i].obj[j].param_val[k].Item2 );
					}

					scn.WriteLine( "  @ENDOBJECT" );
				}

				for (int j = 0; j < panels[i].switch_pos.Count; j++)
				{
					scn.WriteLine( "  \"" + panels[i].switch_pos[j].Item1 + "\" " + panels[i].switch_pos[j].Item2 );
				}

				scn.WriteLine( "@ENDPANEL" );
			}
			return;
		}

		private void Subsystems_LaunchT9m()
		{
			SSVSubsystemBlock subsysblock;
			SSVscnObject subsysobject;

			subsysblock = new SSVSubsystemBlock{name = "HeEng_C", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HeEng_L", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HeEng_R", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HePneu", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MPS", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "SSME1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "SSME config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "VIE config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chB config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chB config", "1" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "SSME2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "SSME config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "VIE config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chB config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chB config", "1" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "SSME3",param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "SSME config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "VIE config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chB config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chB config", "1" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MPC1", param_val = new List<Tuple<string,string>>()};
			if (mission.OV.ExtAL_ODS_Kit)
			{
				subsysblock.param_val.Add( Tuple.Create( "K5", "0" ) );
			}
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MPC2", param_val = new List<Tuple<string,string>>()};
			if (mission.OV.ExtAL_ODS_Kit)
			{
				subsysblock.param_val.Add( Tuple.Create( "K5", "0" ) );
			}
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MPC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "FMC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "FMC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "FMC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AMC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AMC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AMC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "EIU1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "EIU2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "EIU3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MTU", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "MET_RUNNING", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "MET0", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MET1", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MET2", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "IDP1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "IDP2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "IDP3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "IDP4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC1A", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC1B", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC2A", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC2B", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			// SimpleGPCSystem
			GPC_LaunchT9m();


			subsysblock = new SSVSubsystemBlock{name = "MDM_FF1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM5", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM8", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM13", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FF2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM5", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM8", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM13", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FF3", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM5", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM8", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM13", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FF4", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM5", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM8", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM13", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM0", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM4", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM7", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM12", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM15", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM0", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM4", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM7", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM12", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM15", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA3", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM0", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM4", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM7", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM12", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM15", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA4", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM0", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM4", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM7", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM12", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM15", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_PF1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM0", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM7", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM12", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM14", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_PF2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "IOM0", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM2", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM7", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM10", "0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM12", "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "IOM14", "0 0 0" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OA3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "AirDataProbes", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LEFT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "ETUmbilicalDoors", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LEFT_DOOR", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_DOOR_LATCH", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_DOOR", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_DOOR_LATCH", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CL_LATCH_1", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CL_LATCH_2", "1.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "GCIL", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "ATVC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MPS_TVC", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "CenterPitch", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CenterYaw", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LeftPitch", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LeftYaw", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RightPitch", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RightYaw", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MEC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MEC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "RA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "PayloadBay", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "DOOR_PORT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_STBD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_1_4", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_5_8", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_9_12", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_13_16", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_PORT_FWD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_PORT_AFT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_STBD_FWD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_STBD_AFT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_PORT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_STBD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_PORT_1_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_PORT_7_12", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_STBD_1_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_STBD_7_12", "0.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[0]) subsysblock.param_val.Add( Tuple.Create( "CAM_A", "-90.000000 0.000000 40.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[1]) subsysblock.param_val.Add( Tuple.Create( "CAM_B", "90.000000 0.000000 40.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[2]) subsysblock.param_val.Add( Tuple.Create( "CAM_C", "-90.000000 0.000000 40.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[3]) subsysblock.param_val.Add( Tuple.Create( "CAM_D", "90.000000 0.000000 40.000000" ) );
			if (mission.OV.KubandAntenna) subsysblock.param_val.Add( Tuple.Create( "KU_BAND", "0.000000" ) );
			if (mission.OV.PLB_Cameras.Keel_Installed[0]) subsysblock.param_val.Add( Tuple.Create( "KEEL_CAM", "40.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "LandingGear", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "ARM", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOWN", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "NLG", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LMG", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RMG", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "NOWOW_NLG", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "NOWOW_LMG", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "NOWOW_RMG", "1" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "AeroSurfaces", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_LOB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_LIB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_RIB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_ROB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RUDDER", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "SPEEDBRAKE", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "BODYFLAP", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "OMS_LEFT", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "OMS_RIGHT", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "OMS_TVC_LEFT", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PITCH", "5.800000" ) );
			subsysblock.param_val.Add( Tuple.Create( "YAW", "6.010000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "OMS_TVC_RIGHT", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PITCH", "5.800000" ) );
			subsysblock.param_val.Add( Tuple.Create( "YAW", "-6.010000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "DDU1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "DDU2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "DDU3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "HUD1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "DECLUTTER", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "GEAR", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CSS", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MLSNV", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "B/F", "0 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HUD2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "DECLUTTER", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "GEAR", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CSS", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MLSNV", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "B/F", "0 0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "LeftRHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RightRHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AftRHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "LeftTHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AftTHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "LeftRPTA", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RightRPTA", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "LeftSBTC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RightSBTC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "APU1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "State", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelMass", "325.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelPress", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "HydPress", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "Speed", "0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "APU2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "State", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelMass", "325.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelPress", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "HydPress", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "Speed", "0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "APU3", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "State", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelMass", "325.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelPress", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "HydPress", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "Speed", "0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "WSB1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "WSB2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "WSB3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			for (int i = 0, k = 1; i < 5; i++)
			{
				if (mission.OV.PL_Active[i].IsUsed)
				{
					subsysblock = new SSVSubsystemBlock{name = "Payload_Latch_" + k, param_val = new List<Tuple<string,string>>()};
					string latchpos = "1.000000";
					if (mission.OV.PL_Active[i].HasPayload)
					{
						latchpos = "0.000000";
						subsysblock.param_val.Add( Tuple.Create( "ATTACHED_PAYLOAD", mission.OV.PL_Active[i].Payload.Name + " " + mission.OV.PL_Active[i].Payload.AttachmentID ) );
					}

					for (int j = 0, m = 1; j < 4; j++)
					{
						if (mission.OV.PL_Active[i].Latches[j].PLID > 0)
						{
							subsysblock.param_val.Add( Tuple.Create( "LATCH_STATE_" + m, latchpos ) );
							m++;
						}
					}
					for (int j = 4, m = 5; j < 8; j++)
					{
						if (mission.OV.PL_Active[i].Latches[j].PLID > 0)
						{
							subsysblock.param_val.Add( Tuple.Create( "LATCH_STATE_" + m, latchpos ) );
							m++;
						}
					}
					for (int j = 8, m = 9; j < 12; j++)
					{
						if (mission.OV.PL_Active[i].Latches[j].PLID > 0)
						{
							subsysblock.param_val.Add( Tuple.Create( "LATCH_STATE_" + m, latchpos ) );
							m++;
						}
					}
					subsys.Add( subsysblock );
					k++;
				}
			}

			subsysblock = new SSVSubsystemBlock{name = "PRSD", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LV011", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV021", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV031", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV041", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV013", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV023", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV024", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV033", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV043", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV044", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV012", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV022", "1.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "VideoControlUnit", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "CAMERA_POWER", "0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "OUTPUT", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "INPUTS", "0 0 0 0 0 0 0 0" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "ACA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA5", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "StarTrackerDoors", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "-Z_DOOR", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "-Y_DOOR", "0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "VentDoors", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LEFT_1/2", "0.133333" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_3", "0.000000" ) );
			if (mission.OV.VentDoors4and7) subsysblock.param_val.Add( Tuple.Create( "LEFT_4/7", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_5", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_8/9", "0.266667" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_1/2", "0.133333" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_3", "0.000000" ) );
			if (mission.OV.VentDoors4and7) subsysblock.param_val.Add( Tuple.Create( "RIGHT_4/7", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_5", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_8/9", "0.266667" ) );
			subsys.Add( subsysblock );

			CW_LaunchT9m();

			switch (mission.OV.PortLongeronSill)
			{
				case LongeronSillHardware_Type.RMS:
					subsysblock = new SSVSubsystemBlock{name = "PORT_RMS", param_val = new List<Tuple<string,string>>()};
					subsysblock.param_val.Add( Tuple.Create( "ANGLES", "0.000000 0.000000 0.000000 0.000000 0.000000 0.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "SHOULDER_BRACE", "1.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "GRAPPLE", "1 1.0000" ) );
					subsysblock.param_val.Add( Tuple.Create( "RIGIDIZE", "1 1.0000" ) );
					subsysblock.param_val.Add( Tuple.Create( "EXTEND", "1 1.0000" ) );
					subsysblock.param_val.Add( Tuple.Create( "ELBOW_CAM", "-90.000000 105.000000 40.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "WRIST_CAM", "40.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "MPM_ROLLOUT", "0.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "MPM_LATCHES", "0.000000 0.000000 0.000000" ) );
					subsys.Add( subsysblock );
					break;
				case LongeronSillHardware_Type.PayloadMPM:
					break;
				case LongeronSillHardware_Type.SPDS:
					subsysblock = new SSVSubsystemBlock{name = "SPDS", param_val = new List<Tuple<string,string>>()};
					subsysblock.param_val.Add( Tuple.Create( "RDU_PRI_PED_ENGAGED", "1" ) );
					subsysblock.param_val.Add( Tuple.Create( "RDU_SEC_PED_ENGAGED", "0" ) );
					subsysblock.param_val.Add( Tuple.Create( "Yo", "0.400000" ) );
					subsysblock.param_val.Add( Tuple.Create( "Zo", "0.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "RDU", "0.0731707 0.0731707" ) );
					subsysblock.param_val.Add( Tuple.Create( "LATCHES", "0.000000 0.000000 0.000000 0.000000 0.000000" ) );
					subsys.Add( subsysblock );
					break;
				default:
					break;
			}

			switch (mission.OV.StbdLongeronSill)
			{
				case LongeronSillHardware_Type.RMS:
					break;
				case LongeronSillHardware_Type.PayloadMPM:
					subsysblock = new SSVSubsystemBlock{name = "STBD_MPM_PL", param_val = new List<Tuple<string,string>>()};
					subsysblock.param_val.Add( Tuple.Create( "MPM_ROLLOUT", "0.000000" ) );
					if (mission.OV.Stbd_PL_MPM.HasPayload)
					{
						subsysblock.param_val.Add( Tuple.Create( "MPM_LATCHES", "0.000000 0.000000 0.000000" ) );
						subsysblock.param_val.Add( Tuple.Create( "ATTACHED_PAYLOAD", mission.OV.Stbd_PL_MPM.Payload.Name + " " + mission.OV.Stbd_PL_MPM.Payload.AttachmentID ) );
					}
					else subsysblock.param_val.Add( Tuple.Create( "MPM_LATCHES", "1.000000 1.000000 1.000000" ) );
					subsys.Add( subsysblock );
					break;
				case LongeronSillHardware_Type.SPDS:
					break;
				default:
					break;
			}

			if (mission.OV.Airlock == Airlock_Type.Internal)
			{
				subsysblock = new SSVSubsystemBlock{name = "InternalAirlock", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}
			else if (!mission.OV.ODS)
			{
				subsysblock = new SSVSubsystemBlock{name = "ExternalAirlock", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.OV.ODS)
			{
				subsysblock = new SSVSubsystemBlock{name = "ODS", obj = new List<SSVscnObject>(), param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "RING", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "HOOKS_1", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "HOOKS_2", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCH_1", "180.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCH_2", "180.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCH_3", "180.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "CL_CAM", "40.000000" ) );
				subsysobject = new SSVscnObject{name = "PSU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "K1", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K2", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K3", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K4", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K5", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K6", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K11", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K12", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K13", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K14", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K15", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K16", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "E10_OUT_ON", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E12_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E12_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E23_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "DSCU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "GND_CT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "KP", "0 0 0" ) );
				subsysobject.param_val.Add( Tuple.Create( "E1_OUT_OFF", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E15_OUT_OFF", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E37_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E102_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E103_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E113_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E114_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E124_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E128_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E134_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E139_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E140_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E148_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT4", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT5", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT6", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT60", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT61", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT62", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E1_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E28_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E33_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E101_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E202_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E204_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E206_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E208_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "DMCU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "K01", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K02", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K03", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K04", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K05", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K06", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K07", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K08", "0" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "PACU_1", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "PACU_2", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "LACU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "K1", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K2", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K3", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K4", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K5", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K6", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K7", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K8", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT16", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT17", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT18", "0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsys.Add( subsysblock );
			}

			if (mission.OV.TAA != TAA_Type.None)
			{
				subsysblock = new SSVSubsystemBlock{name = "TunnelAdapterAssembly", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.OV.KubandAntenna)
			{
				subsysblock = new SSVSubsystemBlock{name = "DeployedAssembly", param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "ALPHA", "124.300000" ) );
				subsysblock.param_val.Add( Tuple.Create( "BETA", "-27.500000" ) );
				subsys.Add( subsysblock );

				subsysblock = new SSVSubsystemBlock{name = "ElectronicsAssembly1", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );

				subsysblock = new SSVSubsystemBlock{name = "ElectronicsAssembly2", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.OV.DragChute)
			{
				subsysblock = new SSVSubsystemBlock{name = "DragChute", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.LargeUpperStage == 1)
			{
				subsysblock = new SSVSubsystemBlock{name = "ASE_IUS", param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "TILT_TABLE", "0.089552" ) );
				subsysblock.param_val.Add( Tuple.Create( "UMBILICAL", "1" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCHES", "0.000000 0.000000" ) );
				subsys.Add( subsysblock );
			}

			if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
			{
				subsysblock = new SSVSubsystemBlock{name = "CISS", param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "MOTOR", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCHES", "0.000000 0.000000 0.000000" ) );
				subsys.Add( subsysblock );
			}
			return;
		}

		private void Subsystems_LaunchT31s()
		{
			SSVSubsystemBlock subsysblock;
			SSVscnObject subsysobject;

			subsysblock = new SSVSubsystemBlock{name = "HeEng_C", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HeEng_L", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HeEng_R", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HePneu", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PRESS", "4200.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "VALVES", "1.000000 1.000000 0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MPS", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "SSME1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "SSME config", "2" ) );
			subsysblock.param_val.Add( Tuple.Create( "VIE config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chA config", "3" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chB config", "3" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chB config", "1" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "SSME2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "SSME config", "2" ) );
			subsysblock.param_val.Add( Tuple.Create( "VIE config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chA config", "3" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chB config", "3" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chB config", "1" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "SSME3",param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "SSME config", "2" ) );
			subsysblock.param_val.Add( Tuple.Create( "VIE config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chA config", "3" ) );
			subsysblock.param_val.Add( Tuple.Create( "DCU_chB config", "3" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chA config", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "CIE_chB config", "1" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MPC1", param_val = new List<Tuple<string,string>>()};
			if (mission.OV.ExtAL_ODS_Kit)
			{
				subsysblock.param_val.Add( Tuple.Create( "K5", "0" ) );
			}
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MPC2", param_val = new List<Tuple<string,string>>()};
			if (mission.OV.ExtAL_ODS_Kit)
			{
				subsysblock.param_val.Add( Tuple.Create( "K5", "0" ) );
			}
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MPC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "FMC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "FMC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "FMC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MMC4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AMC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AMC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AMC3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "EIU1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "EIU2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "EIU3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MTU", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "MET_RUNNING", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "MET0", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MET1", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MET2", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "IDP1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "IDP2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "IDP3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "IDP4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC1A", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC1B", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC2A", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ADC2B", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			// SimpleGPCSystem
			GPC_LaunchT31s();


			subsysblock = new SSVSubsystemBlock{name = "MDM_FF1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FF2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FF3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FF4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_FA4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_PF1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_PF2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OF4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MDM_OA3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "AirDataProbes", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LEFT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "ETUmbilicalDoors", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LEFT_DOOR", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_DOOR_LATCH", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_DOOR", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_DOOR_LATCH", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CL_LATCH_1", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CL_LATCH_2", "1.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "GCIL", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "ATVC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MPS_TVC", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "CenterPitch", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CenterYaw", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LeftPitch", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LeftYaw", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RightPitch", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RightYaw", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "MEC1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "MEC2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "RA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "PayloadBay", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "DOOR_PORT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_STBD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_1_4", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_5_8", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_9_12", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_CL_13_16", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_PORT_FWD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_PORT_AFT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_STBD_FWD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOOR_LATCH_BLKD_STBD_AFT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_PORT", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_STBD", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_PORT_1_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_PORT_7_12", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_STBD_1_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RADIATOR_LATCH_STBD_7_12", "0.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[0]) subsysblock.param_val.Add( Tuple.Create( "CAM_A", "-90.000000 0.000000 40.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[1]) subsysblock.param_val.Add( Tuple.Create( "CAM_B", "90.000000 0.000000 40.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[2]) subsysblock.param_val.Add( Tuple.Create( "CAM_C", "-90.000000 0.000000 40.000000" ) );
			if (mission.OV.PLB_Cameras.Installed[3]) subsysblock.param_val.Add( Tuple.Create( "CAM_D", "90.000000 0.000000 40.000000" ) );
			if (mission.OV.KubandAntenna) subsysblock.param_val.Add( Tuple.Create( "KU_BAND", "0.000000" ) );
			if (mission.OV.PLB_Cameras.Keel_Installed[0]) subsysblock.param_val.Add( Tuple.Create( "KEEL_CAM", "40.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "LandingGear", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "ARM", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "DOWN", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "NLG", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LMG", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RMG", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "NOWOW_NLG", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "NOWOW_LMG", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "NOWOW_RMG", "1" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "AeroSurfaces", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_LOB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_LIB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_RIB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "ELEVON_ROB", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RUDDER", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "SPEEDBRAKE", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "BODYFLAP", "0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "OMS_LEFT", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "OMS_RIGHT", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "OMS_TVC_LEFT", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PITCH", "5.800000" ) );
			subsysblock.param_val.Add( Tuple.Create( "YAW", "6.010000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "OMS_TVC_RIGHT", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "PITCH", "5.800000" ) );
			subsysblock.param_val.Add( Tuple.Create( "YAW", "-6.010000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "DDU1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "DDU2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "DDU3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "HUD1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "DECLUTTER", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "GEAR", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CSS", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MLSNV", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "B/F", "0 0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "HUD2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "DECLUTTER", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "GEAR", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "CSS", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "MLSNV", "0 0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "B/F", "0 0.000000" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "LeftRHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RightRHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AftRHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "LeftTHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "AftTHC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "LeftRPTA", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RightRPTA", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "LeftSBTC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "RightSBTC", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "APU1", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "State", "2" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelMass", "311.75" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelPress", "1475.143826" ) );
			subsysblock.param_val.Add( Tuple.Create( "HydPress", "2994.599475" ) );
			subsysblock.param_val.Add( Tuple.Create( "Speed", "101.695439" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "APU2", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "State", "2" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelMass", "312.0" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelPress", "1461.373518" ) );
			subsysblock.param_val.Add( Tuple.Create( "HydPress", "2999.972076" ) );
			subsysblock.param_val.Add( Tuple.Create( "Speed", "91.375667" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "APU3", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "State", "2" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelMass", "312.25" ) );
			subsysblock.param_val.Add( Tuple.Create( "FuelPress", "1436.310257" ) );
			subsysblock.param_val.Add( Tuple.Create( "HydPress", "2984.859951" ) );
			subsysblock.param_val.Add( Tuple.Create( "Speed", "99.583206" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "WSB1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "WSB2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "WSB3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			for (int i = 0, k = 1; i < 5; i++)
			{
				if (mission.OV.PL_Active[i].IsUsed)
				{
					subsysblock = new SSVSubsystemBlock{name = "Payload_Latch_" + k, param_val = new List<Tuple<string,string>>()};
					string latchpos = "1.000000";
					if (mission.OV.PL_Active[i].HasPayload)
					{
						latchpos = "0.000000";
						subsysblock.param_val.Add( Tuple.Create( "ATTACHED_PAYLOAD", mission.OV.PL_Active[i].Payload.Name + " " + mission.OV.PL_Active[i].Payload.AttachmentID ) );
					}

					for (int j = 0, m = 1; j < 4; j++)
					{
						if (mission.OV.PL_Active[i].Latches[j].PLID > 0)
						{
							subsysblock.param_val.Add( Tuple.Create( "LATCH_STATE_" + m, latchpos ) );
							m++;
						}
					}
					for (int j = 4, m = 5; j < 8; j++)
					{
						if (mission.OV.PL_Active[i].Latches[j].PLID > 0)
						{
							subsysblock.param_val.Add( Tuple.Create( "LATCH_STATE_" + m, latchpos ) );
							m++;
						}
					}
					for (int j = 8, m = 9; j < 12; j++)
					{
						if (mission.OV.PL_Active[i].Latches[j].PLID > 0)
						{
							subsysblock.param_val.Add( Tuple.Create( "LATCH_STATE_" + m, latchpos ) );
							m++;
						}
					}
					subsys.Add( subsysblock );
					k++;
				}
			}

			subsysblock = new SSVSubsystemBlock{name = "PRSD", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LV011", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV021", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV031", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV041", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV013", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV023", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV024", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV033", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV043", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV044", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV012", "1.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LV022", "1.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "VideoControlUnit", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "CAMERA_POWER", "0 0 0 0 0" ) );
			subsysblock.param_val.Add( Tuple.Create( "OUTPUT", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "INPUTS", "0 0 0 0 0 0 0 0" ) );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "ACA1", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA2", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA3", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA4", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "ACA5", param_val = new List<Tuple<string,string>>()};
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "StarTrackerDoors", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "-Z_DOOR", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "-Y_DOOR", "0.000000" ) );
			subsys.Add( subsysblock );

			subsysblock = new SSVSubsystemBlock{name = "VentDoors", param_val = new List<Tuple<string,string>>()};
			subsysblock.param_val.Add( Tuple.Create( "LEFT_1/2", "0.133333" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_3", "0.000000" ) );
			if (mission.OV.VentDoors4and7) subsysblock.param_val.Add( Tuple.Create( "LEFT_4/7", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_5", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "LEFT_8/9", "0.266667" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_1/2", "0.133333" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_3", "0.000000" ) );
			if (mission.OV.VentDoors4and7) subsysblock.param_val.Add( Tuple.Create( "RIGHT_4/7", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_5", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_6", "0.000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RIGHT_8/9", "0.266667" ) );
			subsys.Add( subsysblock );

			CW_LaunchT31s();

			switch (mission.OV.PortLongeronSill)
			{
				case LongeronSillHardware_Type.RMS:
					subsysblock = new SSVSubsystemBlock{name = "PORT_RMS", param_val = new List<Tuple<string,string>>()};
					subsysblock.param_val.Add( Tuple.Create( "ANGLES", "0.000000 0.000000 0.000000 0.000000 0.000000 0.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "SHOULDER_BRACE", "1.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "GRAPPLE", "1 1.0000" ) );
					subsysblock.param_val.Add( Tuple.Create( "RIGIDIZE", "1 1.0000" ) );
					subsysblock.param_val.Add( Tuple.Create( "EXTEND", "1 1.0000" ) );
					subsysblock.param_val.Add( Tuple.Create( "ELBOW_CAM", "-90.000000 105.000000 40.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "WRIST_CAM", "40.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "MPM_ROLLOUT", "0.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "MPM_LATCHES", "0.000000 0.000000 0.000000" ) );
					subsys.Add( subsysblock );
					break;
				case LongeronSillHardware_Type.PayloadMPM:
					break;
				case LongeronSillHardware_Type.SPDS:
					subsysblock = new SSVSubsystemBlock{name = "SPDS", param_val = new List<Tuple<string,string>>()};
					subsysblock.param_val.Add( Tuple.Create( "RDU_PRI_PED_ENGAGED", "1" ) );
					subsysblock.param_val.Add( Tuple.Create( "RDU_SEC_PED_ENGAGED", "0" ) );
					subsysblock.param_val.Add( Tuple.Create( "Yo", "0.400000" ) );
					subsysblock.param_val.Add( Tuple.Create( "Zo", "0.000000" ) );
					subsysblock.param_val.Add( Tuple.Create( "RDU", "0.0731707 0.0731707" ) );
					subsysblock.param_val.Add( Tuple.Create( "LATCHES", "0.000000 0.000000 0.000000 0.000000 0.000000" ) );
					subsys.Add( subsysblock );
					break;
				default:
					break;
			}

			switch (mission.OV.StbdLongeronSill)
			{
				case LongeronSillHardware_Type.RMS:
					break;
				case LongeronSillHardware_Type.PayloadMPM:
					subsysblock = new SSVSubsystemBlock{name = "STBD_MPM_PL", param_val = new List<Tuple<string,string>>()};
					subsysblock.param_val.Add( Tuple.Create( "MPM_ROLLOUT", "0.000000" ) );
					if (mission.OV.Stbd_PL_MPM.HasPayload)
					{
						subsysblock.param_val.Add( Tuple.Create( "MPM_LATCHES", "0.000000 0.000000 0.000000" ) );
						subsysblock.param_val.Add( Tuple.Create( "ATTACHED_PAYLOAD", mission.OV.Stbd_PL_MPM.Payload.Name + " " + mission.OV.Stbd_PL_MPM.Payload.AttachmentID ) );
					}
					else subsysblock.param_val.Add( Tuple.Create( "MPM_LATCHES", "1.000000 1.000000 1.000000" ) );
					subsys.Add( subsysblock );
					break;
				case LongeronSillHardware_Type.SPDS:
					break;
				default:
					break;
			}

			if (mission.OV.Airlock == Airlock_Type.Internal)
			{
				subsysblock = new SSVSubsystemBlock{name = "InternalAirlock", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}
			else if (!mission.OV.ODS)
			{
				subsysblock = new SSVSubsystemBlock{name = "ExternalAirlock", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.OV.ODS)
			{
				subsysblock = new SSVSubsystemBlock{name = "ODS", obj = new List<SSVscnObject>(), param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "RING", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "HOOKS_1", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "HOOKS_2", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCH_1", "180.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCH_2", "180.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCH_3", "180.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "CL_CAM", "40.000000" ) );
				subsysobject = new SSVscnObject{name = "PSU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "K1", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K2", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K3", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K4", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K5", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K6", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K11", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K12", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K13", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K14", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K15", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K16", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "E10_OUT_ON", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E12_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E12_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E23_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "DSCU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "GND_CT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "KP", "0 0 0" ) );
				subsysobject.param_val.Add( Tuple.Create( "E1_OUT_OFF", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E15_OUT_OFF", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E37_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E102_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E103_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E113_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E114_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E124_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E128_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E134_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E139_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E140_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E148_OUT", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT4", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT5", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT6", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT60", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT61", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT62", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E1_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E28_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E33_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E101_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E202_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E204_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E206_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E208_CTRL_GND", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "DMCU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "K01", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K02", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K03", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K04", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K05", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K06", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K07", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K08", "0" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "PACU_1", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "PACU_2", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21A_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M1", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_OFF_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E21B_ON_OUT_M2", "1 1 1" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E30_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M1", "0.000000 0.000000 0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "E31_CTRL_GND_M2", "0.000000 0.000000 0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsysobject = new SSVscnObject{name = "LACU", param_val = new List<Tuple<string,string>>()};
				subsysobject.param_val.Add( Tuple.Create( "K1", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K2", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K3", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K4", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K5", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K6", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K7", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "K8", "0" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT16", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT17", "0.000000" ) );
				subsysobject.param_val.Add( Tuple.Create( "KT18", "0.000000" ) );
				subsysblock.obj.Add( subsysobject );
				subsys.Add( subsysblock );
			}

			if (mission.OV.TAA != TAA_Type.None)
			{
				subsysblock = new SSVSubsystemBlock{name = "TunnelAdapterAssembly", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.OV.KubandAntenna)
			{
				subsysblock = new SSVSubsystemBlock{name = "DeployedAssembly", param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "ALPHA", "124.300000" ) );
				subsysblock.param_val.Add( Tuple.Create( "BETA", "-27.500000" ) );
				subsys.Add( subsysblock );

				subsysblock = new SSVSubsystemBlock{name = "ElectronicsAssembly1", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );

				subsysblock = new SSVSubsystemBlock{name = "ElectronicsAssembly2", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.OV.DragChute)
			{
				subsysblock = new SSVSubsystemBlock{name = "DragChute", param_val = new List<Tuple<string,string>>()};
				subsys.Add( subsysblock );
			}

			if (mission.LargeUpperStage == 1)
			{
				subsysblock = new SSVSubsystemBlock{name = "ASE_IUS", param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "TILT_TABLE", "0.089552" ) );
				subsysblock.param_val.Add( Tuple.Create( "UMBILICAL", "1" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCHES", "0.000000 0.000000" ) );
				subsys.Add( subsysblock );
			}

			if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
			{
				subsysblock = new SSVSubsystemBlock{name = "CISS", param_val = new List<Tuple<string,string>>()};
				subsysblock.param_val.Add( Tuple.Create( "MOTOR", "0.000000" ) );
				subsysblock.param_val.Add( Tuple.Create( "LATCHES", "0.000000 0.000000 0.000000" ) );
				subsys.Add( subsysblock );
			}
			return;
		}

		private void Panels_LaunchT9m()
		{
			SSVPanelBlock panelblock;
			SSVscnObject panelobject;

			//// Forward
			// F2
			panelblock = new SSVPanelBlock{name = "F2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			if (mission.OV.DragChute)
			{
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE ARM COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE DPY COVER", "CLOSED" ) );
			}
			panels.Add( panelblock );

			// F3
			panelblock = new SSVPanelBlock{name = "F3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "TRIM RHC/PNL CDR", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TRIM PANEL CDR", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TRIM RHC/PNL PLT", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TRIM PANEL PLT", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD POWER CDR", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD POWER PLT", "OFF" ) );
			if (mission.OV.DragChute)
			{
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE ARM COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE DPY COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE JETT COVER", "CLOSED" ) );
			}
			panels.Add( panelblock );

			// F4
			panelblock = new SSVPanelBlock{name = "F4", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			if (mission.OV.DragChute) panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE JETT COVER", "CLOSED" ) );
			panels.Add( panelblock );

			// F6
			panelblock = new SSVPanelBlock{name = "F6", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "CDR1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "CDR2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelblock.switch_pos.Add( Tuple.Create( "FLT CNTLR POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HSI SELECT MODE", "ENTRY" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HSI SELECT SOURCE", "NAV" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HSI SELECT CHANNEL", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ATTITUDE", "REF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ERROR", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI RATE", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR ARM COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR DN COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD MODE", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHTNESS", "0.500000" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHT", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RDR ALTM", "1" ) );
			panels.Add( panelblock );

			// F7
			panelblock = new SSVPanelBlock{name = "F7", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "CRT1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "CRT2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "CRT3", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "MFD1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "4" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "MFD2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIME", "540 0.000000 1 0" ) );
			panels.Add( panelblock );

			// F8
			panelblock = new SSVPanelBlock{name = "F8", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "PLT1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "PLT2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "4" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelblock.switch_pos.Add( Tuple.Create( "FLT CNTLR POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HSI SELECT MODE", "ENTRY" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HSI SELECT SOURCE", "NAV" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HSI SELECT CHANNEL", "2" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ATTITUDE", "REF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ERROR", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI RATE", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR ARM COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR DN COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD MODE", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHTNESS", "0.500000" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHT", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RDR ALTM", "2" ) );
			panels.Add( panelblock );

			// F9

			//// Left
			// L1
			panelblock = new SSVPanelBlock{name = "L1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "FIRE SUPPRESSION AV BAY 1 AGENT DISCH COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FIRE SUPPRESSION AV BAY 2 AGENT DISCH COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FIRE SUPPRESSION AV BAY 3 AGENT DISCH COVER", "CLOSED" ) );
			panels.Add( panelblock );

			// L2
			panelblock = new SSVPanelBlock{name = "L2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "ANTISKID", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "NOSE WHEEL STEERING", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ENTRY MODE", "AUTO" ) );
			panels.Add( panelblock );

			// L4


			//// Center
			// C2
			panelblock = new SSVPanelBlock{name = "C2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 1 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 2 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 3 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 1 MAJ FUNC", "GNC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 2 MAJ FUNC", "GNC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 3 MAJ FUNC", "GNC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LEFT IDP/CRT SEL", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RIGHT IDP/CRT SEL", "2" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MODE", "DOWN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 1", "9" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 1", "0" ) );
			panels.Add( panelblock );

			// C3
			panelblock = new SSVPanelBlock{name = "C3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "OMS ENG LEFT", "ARM/PRESS" ) );
			panelblock.switch_pos.Add( Tuple.Create( "OMS ENG RIGHT", "ARM/PRESS" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BFC CRT DISPLAY", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BFC CRT SELECT", "3+1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE STOW LEFT", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE STOW RIGHT", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE LEFT", "STOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE RIGHT", "STOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE LIMIT SHUT DN", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE SHUT DOWN LEFT COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE SHUT DOWN CTR COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE SHUT DOWN RIGHT COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "SRB SEPARATION", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "SRB SEPARATION SEP COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET SEPARATION", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET SEPARATION SEP COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CAUTION/WARNING MODE", "NORM" ) );
			panels.Add( panelblock );


			//// Right
			// HACK switched R1 and R2, as click area on R2 is too big
			// R2
			panelblock = new SSVPanelBlock{name = "R2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "MPS PRPLT DUMP SEQUENCE", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS PRPLT BACKUP LH2 VLV", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER LEFT AC2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER CTR AC1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER RIGHT AC3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER LEFT AC3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER CTR AC2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER RIGHT AC1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION A LEFT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION A CTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION A RIGHT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION B LEFT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION B CTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION B RIGHT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS PNEUMATICS L ENG He XOVR", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS PNEUMATICS He ISOL", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He INTERCONNECT LEFT", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He INTERCONNECT CTR", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He INTERCONNECT RIGHT", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS LH2 ULLAGE PRESS", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU OPERATE 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU OPERATE 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU OPERATE 3", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HYD MAIN PUMP PRESS 1", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HYD MAIN PUMP PRESS 2", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HYD MAIN PUMP PRESS 3", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU CNTLR PWR 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU CNTLR PWR 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU CNTLR PWR 3", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU FUEL TK VLV 1", "CLOSE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU FUEL TK VLV 2", "CLOSE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU FUEL TK VLV 3", "CLOSE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER CNTLR/HTR 1", "A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER CNTLR/HTR 2", "A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER CNTLR/HTR 3", "A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER PWR 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER PWR 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER PWR 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER N2 SUPPLY 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER N2 SUPPLY 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER N2 SUPPLY 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR MODE", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR CENTERLINE LATCH", "GND" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR LEFT DOOR", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR LEFT LATCH", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR RIGHT DOOR", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR RIGHT LATCH", "OFF" ) );
			panels.Add( panelblock );

			// R1
			panelblock = new SSVPanelBlock{name = "R1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE MN B/C", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE MN C/A", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE MN A/B", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE FC 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE FC 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE FC 3", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC1 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC1 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC1 C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC2 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC2 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC2 C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC3 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC3 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC3 C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC BUS SNSR 1", "MONITOR" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC BUS SNSR 2", "MONITOR" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC BUS SNSR 3", "MONITOR" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD CABIN", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AUX COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AUX", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AFT MN B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AFT MN C", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK1 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK1 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK2 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK2 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK3 HEATERS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK3 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK1 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK1 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK2 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK2 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK3 HEATERS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK3 HEATERS B", "OFF" ) );
			panels.Add( panelblock );

			// R4


			//// Overhead
			// O1
			panelblock = new SSVPanelBlock{name = "O1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panels.Add( panelblock );

			// O2
			panelblock = new SSVPanelBlock{name = "O2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "CRYO O2 HTR ASSY TEMP", "TK 1 1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CRYO PRESS QTY", "TK1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FUEL CELL STACK TEMP", "1" ) );
			panels.Add( panelblock );

			// O3
			panelblock = new SSVPanelBlock{name = "O3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "RCS/OMS/PRESS", "RCS He X10" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RCS/OMS PRPLT QTY", "OMS FUEL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MISSION TIMER", "MET" ) );
			panels.Add( panelblock );

			// O5

			// O6
			panelblock = new SSVPanelBlock{name = "O6", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 1 Cover", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 2 Cover", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER POWER -Y", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER POWER -Z", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ANNUNCIATOR BUS SELECT ACA 1", "MN A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ANNUNCIATOR BUS SELECT ACA 2/3", "MN B" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM PL1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM PL2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM PL3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 1 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 2 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 3 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 4 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 5 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 5", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 1 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 2 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 3 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 4 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 5 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 1", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 2", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 3", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 4", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 5", "BACKUP" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IPL SOURCE", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 1", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 2", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 3", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 4", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 5", "RUN" ) );
			panels.Add( panelblock );

			// O7

			// O8
			panelblock = new SSVPanelBlock{name = "O8", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "RADAR ALTIMETER 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADAR ALTIMETER 2", "ON" ) );
			panels.Add( panelblock );

			// O9


			//// Overhead aft
			// O13
			panelblock = new SSVPanelBlock{name = "O13", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "C&W A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "C&W B", "CLOSED" ) );
			panels.Add( panelblock );

			// O14
			panelblock = new SSVPanelBlock{name = "O14", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "BRAKES MN A", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 1/2 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 3/4 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRKR -Z", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU LEFT MN A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU AFT MN A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "NOSE WHEEL STEERING MN A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "L OMS ENG VLV", "ON" ) );
			panels.Add( panelblock );

			// O15
			panelblock = new SSVPanelBlock{name = "O15", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "BRAKES MN B", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 1/2 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "NOSE WHEEL STEERING MN B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRKR -Y", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU LEFT MN B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU RIGHT MN B", "CLOSED" ) );
			panels.Add( panelblock );

			// O16
			panelblock = new SSVPanelBlock{name = "O16", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "BRAKES MN C", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 3/4 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU RIGHT MN C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU AFT MN C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "R OMS ENG VLV", "ON" ) );
			panels.Add( panelblock );

			// O17
			panelblock = new SSVPanelBlock{name = "O17", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EIU L-C", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EIU C-R", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EIU R-L", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OA1/2/3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MEC 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MEC 2", "ON" ) );
			panels.Add( panelblock );


			//// Overhead aft
			// L9

			// L10
			if (mission.LargeUpperStage == 1)
			{
				panelblock = new SSVPanelBlock{name = "L10_IUS", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "PANEL MODE", "PRIMARY" ) );
				panelblock.switch_pos.Add( Tuple.Create( "TILT TABLE ACTUATOR DRIVE ENABLE PRI 1", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "TILT TABLE ACTUATOR DRIVE ENABLE ALT 2", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "CMD PATH ENABLED", "RF" ) );
				panels.Add( panelblock );
			}

			// L12
			if (mission.LargeUpperStage == 1)
			{
				panelblock = new SSVPanelBlock{name = "L12U_IUS", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "ACT ORD ARM", "SAFE" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ACT 1 DISENG", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "IUS RF ANT E/D", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ACT 2 DISENG", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ACT ORD PREARM", "OFF" ) );
				panels.Add( panelblock );
			}
			else if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
			{
				panelblock = new SSVPanelBlock{name = "L12U_Centaur", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "SUPER*ZIP PRI ARM", "SAFE" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LOGIC PRI PWR", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "SSP PRI PWR", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "SUPER*ZIP BKUP ARM", "SAFE" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LOGIC BKUP PWR", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "SSP BKUP PWR", "OFF" ) );
				panels.Add( panelblock );
			}


			//// Aft
			// A1U
			panelblock = new SSVPanelBlock{name = "A1U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "SLEW RATE", "SLOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CONTROL", "COMMAND" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND STEERING MODE", "MAN SLEW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND POWER", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND MODE", "RDR PASSIVE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND RADAR OUTPUT", "HIGH" ) );
			panels.Add( panelblock );

			// A1L

			// A1R

			// AFD
			panelblock = new SSVPanelBlock{name = "AftMDU", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "AFD1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panels.Add( panelblock );

			// A2
			panelblock = new SSVPanelBlock{name = "A2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "DIGI DIS SELECT", "EL/AZ" ) );
			panelblock.switch_pos.Add( Tuple.Create( "X-PNTR SCALE", "X10" ) );
			panels.Add( panelblock );

			// A3
			panelblock = new SSVPanelBlock{name = "A3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "MONITOR 1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "L-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "C-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "XHAIR", "0" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "MONITOR 2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "L-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "C-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "XHAIR", "0" ) );
			panelblock.obj.Add( panelobject );
			panels.Add( panelblock );

			// A4
			panelblock = new SSVPanelBlock{name = "A4", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "MISSION TIMER", "MET" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIME", "0 0.000000 0 1" ) );
			panels.Add( panelblock );

			// A6U
			panelblock = new SSVPanelBlock{name = "A6U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "SENSE", "-Z" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FLT CNTLR POWER", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LOGIC POWER SYS 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LOGIC POWER SYS 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 3", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 4", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 5", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD SELECT", GetPayloadSelectSwitch() ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ATTITUDE", "INRTL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ERROR", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI RATE", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ANNUNCIATOR BUS SELECT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MODE", "UP" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 1", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 1", "0" ) );
			panels.Add( panelblock );

			// A6L
			if (mission.OV.ODS)
			{
				panelblock = new SSVPanelBlock{name = "A6L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "ESS 1BC SYS PWR CNTL SYS 1", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ESS 1BC DEPRESS SYS 1 VENT ISOL", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A DEPRESS SYS 1 VENT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A DOCK LIGHT TRUSS FWD", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A DOCK LIGHT VEST PORT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ESS 2CA SYS PWR CNTL SYS 2", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ESS 2CA DEPRESS SYS 2 VENT ISOL", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B DEPRESS SYS 2 VENT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B DOCK LIGHT TRUSS AFT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B DOCK LIGHT VEST STBD", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A LOGIC 3", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A LOGIC 1", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B LOGIC 1", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B LOGIC 2", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN C LOGIC 2", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN C LOGIC 3", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS A OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS A CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS B OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS B CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS A OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS A CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS B OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS B CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYRO POWER MN A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYRO POWER MN B", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PSU POWER MN A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PSU POWER MN B", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS TRUSS FWD", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS TRUSS AFT", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS VESTIBULE PORT", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS VESTIBULE STBD", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 HOOKS SYS A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 HOOKS SYS B", "OFF" ) );
				panels.Add( panelblock );
			}

			// A7U
			panelblock = new SSVPanelBlock{name = "A7U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD AFT STBD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD AFT PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD MID STBD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD MID PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD FWD STBD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD FWD PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD DOCKING", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD FWD BHD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RMS SPOTLIGHT PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RMS CAMERA PORT", "ELBOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CAMERA COMMAND PAN/TILT", "LOW RATE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TV POWER CONTR UNIT", "OFF" ) );
			panels.Add( panelblock );

			// A7L
			if (mission.OV.ODS)
			{
				panelblock = new SSVPanelBlock{name = "A7L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "CONTROL PANEL POWER A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "CONTROL PANEL POWER B", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "CONTROL PANEL POWER C", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "HEATERS/DCU POWER H1", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "HEATERS/DCU POWER H2/DCU", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "HEATERS/DCU POWER H3/DCU", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS POWER ADS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS POWER BDS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS POWER CDS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYROS Ap", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYROS Bp", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYROS Cp", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYRO COMMANDS", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS CONTROL COMMANDS", "CLOSED" ) );
				panels.Add( panelblock );
			}
			else if (mission.OV.PortLongeronSill == LongeronSillHardware_Type.SPDS)
			{
				panelblock = new SSVPanelBlock{name = "A7A3_SPDS", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE MN A", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE MN B", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER MN A", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER MN B", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS A ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS B ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS A FIRE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS B FIRE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS A ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS B ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS A FIRE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS B FIRE", "OFF" ) );
				panels.Add( panelblock );
			}

			// A8U
			if ((mission.OV.PortLongeronSill == LongeronSillHardware_Type.RMS) || (mission.OV.StbdLongeronSill == LongeronSillHardware_Type.RMS))
			{
				panelblock = new SSVPanelBlock{name = "A8A1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "MODE", "TEST" ) );
				panelblock.switch_pos.Add( Tuple.Create( "END EFFECTOR MODE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PARAMETER", "PORT TEMP LED/ABE/ID" ) );
				panelblock.switch_pos.Add( Tuple.Create( "JOINT", "CRIT TEMP" ) );
				panels.Add( panelblock );
			}

			// A8L
			if ((mission.OV.PortLongeronSill != LongeronSillHardware_Type.None) || (mission.OV.StbdLongeronSill != LongeronSillHardware_Type.None))
			{
				panelblock = new SSVPanelBlock{name = "A8A2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "RMS SELECT", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "STARBOARD RMS COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "STARBOARD RMS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "STARBOARD RMS RETENTION LATCHES", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PORT RMS COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PORT RMS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PORT RMS RETENTION LATCHES", "OFF" ) );
				panels.Add( panelblock );
			}


			//// Right
			// R10

			// R11U
			panelblock = new SSVPanelBlock{name = "R11U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "CRT4", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panels.Add( panelblock );

			// R11L
			panelblock = new SSVPanelBlock{name = "R11L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 4 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 4 MAJ FUNC", "GNC" ) );
			panels.Add( panelblock );

			// R13U
			panelblock = new SSVPanelBlock{name = "R13U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "PARAMETER SELECT 100", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PARAMETER SELECT 10", "2" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PARAMETER SELECT 1", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT SET VALUE 1", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT SET VALUE 01", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT SET VALUE 005", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT", "LOWER" ) );
			panels.Add( panelblock );

			// R13L
			panelblock = new SSVPanelBlock{name = "R13L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY DOOR SYS 1", "DISABLE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY DOOR SYS 2", "DISABLE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY MECH PWR SYS 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY MECH PWR SYS 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY DOOR", "STOP" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR LATCH CONTROL SYS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR LATCH CONTROL SYS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR CONTROL SYS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR CONTROL SYS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU ANTENNA DIRECT STOW", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU ANTENNA", "GND" ) );
			panels.Add( panelblock );

			// R14
			panelblock = new SSVPanelBlock{name = "R14", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "MNC MDU CDR 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB MDU CDR 2", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB MDU MFD 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA MDU MFD 2", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA MDU PLT 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC MDU PLT 2", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC MDU AFD 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA ADC 1A 2A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB ADC 1B 2B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV A CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV A CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV A CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC TV B CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC TV B CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC TV B CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV C CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV C CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV C CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV D CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV D CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV D CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV RMS CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV RMS CAMR WRIST ILLUM/CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV RMS CAMR ELB ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV CONTR UNIT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV CONTR UNIT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV MON 1", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV MON 2", "OPEN" ) );
			panels.Add( panelblock );
			return;
		}

		private void Panels_LaunchT31s()
		{
			SSVPanelBlock panelblock;
			SSVscnObject panelobject;

			//// Forward
			// F2
			panelblock = new SSVPanelBlock{name = "F2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			if (mission.OV.DragChute)
			{
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE ARM COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE DPY COVER", "CLOSED" ) );
			}
			panels.Add( panelblock );

			// F3
			panelblock = new SSVPanelBlock{name = "F3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "TRIM RHC/PNL CDR", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TRIM PANEL CDR", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TRIM RHC/PNL PLT", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TRIM PANEL PLT", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD POWER CDR", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD POWER PLT", "OFF" ) );
			if (mission.OV.DragChute)
			{
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE ARM COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE DPY COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE JETT COVER", "CLOSED" ) );
			}
			panels.Add( panelblock );

			// F4
			panelblock = new SSVPanelBlock{name = "F4", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			if (mission.OV.DragChute) panelblock.switch_pos.Add( Tuple.Create( "DRAG CHUTE JETT COVER", "CLOSED" ) );
			panels.Add( panelblock );

			// F6
			panelblock = new SSVPanelBlock{name = "F6", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "CDR1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "CDR2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelblock.switch_pos.Add( Tuple.Create( "FLT CNTLR POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ATTITUDE", "REF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ERROR", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI RATE", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR ARM COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR DN COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD MODE", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHTNESS", "0.500000" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHT", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RDR ALTM", "1" ) );
			panels.Add( panelblock );

			// F7
			panelblock = new SSVPanelBlock{name = "F7", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "CRT1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "CRT2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "CRT3", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "MFD1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "4" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "MFD2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIME", "31 0.000000 1 0" ) );
			panels.Add( panelblock );

			// F8
			panelblock = new SSVPanelBlock{name = "F8", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "PLT1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "1" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "PLT2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "ON" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "4" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "2" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panelblock.switch_pos.Add( Tuple.Create( "FLT CNTLR POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ATTITUDE", "REF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ERROR", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI RATE", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR ARM COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LANDING GEAR DN COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD MODE", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHTNESS", "0.500000" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HUD BRIGHT", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RDR ALTM", "2" ) );
			panels.Add( panelblock );

			// F9


			//// Left
			// L1
			panelblock = new SSVPanelBlock{name = "L1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "FIRE SUPPRESSION AV BAY 1 AGENT DISCH COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FIRE SUPPRESSION AV BAY 2 AGENT DISCH COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FIRE SUPPRESSION AV BAY 3 AGENT DISCH COVER", "CLOSED" ) );
			panels.Add( panelblock );

			// L2
			panelblock = new SSVPanelBlock{name = "L2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "ANTISKID", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "NOSE WHEEL STEERING", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ENTRY MODE", "AUTO" ) );
			panels.Add( panelblock );

			// L4


			//// Center
			// C2
			panelblock = new SSVPanelBlock{name = "C2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 1 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 2 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 3 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 1 MAJ FUNC", "GNC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 2 MAJ FUNC", "GNC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 3 MAJ FUNC", "GNC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LEFT IDP/CRT SEL", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RIGHT IDP/CRT SEL", "2" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MODE", "DOWN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 1", "9" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 1", "0" ) );
			panels.Add( panelblock );

			// C3
			panelblock = new SSVPanelBlock{name = "C3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "OMS ENG LEFT", "ARM/PRESS" ) );
			panelblock.switch_pos.Add( Tuple.Create( "OMS ENG RIGHT", "ARM/PRESS" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BFC CRT DISPLAY", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BFC CRT SELECT", "3+1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE STOW LEFT", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE STOW RIGHT", "INHIBIT" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE LEFT", "STOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AIR DATA PROBE RIGHT", "STOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE LIMIT SHUT DN", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE SHUT DOWN LEFT COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE SHUT DOWN CTR COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MAIN ENGINE SHUT DOWN RIGHT COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "SRB SEPARATION", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "SRB SEPARATION SEP COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET SEPARATION", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET SEPARATION SEP COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CAUTION/WARNING MODE", "NORM" ) );
			panels.Add( panelblock );


			//// Right
			// HACK switched R1 and R2, as click area on R2 is too big
			// R2
			panelblock = new SSVPanelBlock{name = "R2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "MPS PRPLT DUMP SEQUENCE", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS PRPLT BACKUP LH2 VLV", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER LEFT AC2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER CTR AC1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER RIGHT AC3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER LEFT AC3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER CTR AC2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS ENGINE POWER RIGHT AC1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION A LEFT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION A CTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION A RIGHT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION B LEFT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION B CTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He ISOLATION B RIGHT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS PNEUMATICS L ENG He XOVR", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS PNEUMATICS He ISOL", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He INTERCONNECT LEFT", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He INTERCONNECT CTR", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS He INTERCONNECT RIGHT", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MPS LH2 ULLAGE PRESS", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU OPERATE 1", "START/RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU OPERATE 2", "START/RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU OPERATE 3", "START/RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HYD MAIN PUMP PRESS 1", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HYD MAIN PUMP PRESS 2", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "HYD MAIN PUMP PRESS 3", "NORM" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU CNTLR PWR 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU CNTLR PWR 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU CNTLR PWR 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU FUEL TK VLV 1", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU FUEL TK VLV 2", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "APU FUEL TK VLV 3", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER CNTLR/HTR 1", "A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER CNTLR/HTR 2", "A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER CNTLR/HTR 3", "A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER PWR 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER PWR 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER PWR 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER N2 SUPPLY 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER N2 SUPPLY 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "BOILER N2 SUPPLY 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR MODE", "GPC" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR CENTERLINE LATCH", "GND" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR LEFT DOOR", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR LEFT LATCH", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR RIGHT DOOR", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ET UMBILICAL DOOR RIGHT LATCH", "OFF" ) );
			panels.Add( panelblock );

			// R1
			panelblock = new SSVPanelBlock{name = "R1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE MN B/C", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE MN C/A", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE MN A/B", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE FC 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE FC 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ESS BUS SOURCE FC 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC1 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC1 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC1 C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC2 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC2 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC2 C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC3 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC3 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC CONTR AC3 C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC BUS SNSR 1", "MONITOR" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC BUS SNSR 2", "MONITOR" ) );
			panelblock.switch_pos.Add( Tuple.Create( "AC BUS SNSR 3", "MONITOR" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD CABIN", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AUX COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AUX", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AFT MN B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD AFT MN C", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK1 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK1 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK2 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK2 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK3 HEATERS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "O2 TK3 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK1 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK1 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK2 HEATERS A", "AUTO" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK2 HEATERS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK3 HEATERS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "H2 TK3 HEATERS B", "OFF" ) );
			panels.Add( panelblock );

			// R4


			//// Overhead
			// O1
			panelblock = new SSVPanelBlock{name = "O1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panels.Add( panelblock );

			// O2
			panelblock = new SSVPanelBlock{name = "O2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "CRYO O2 HTR ASSY TEMP", "TK 1 1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CRYO PRESS QTY", "TK1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FUEL CELL STACK TEMP", "1" ) );
			panels.Add( panelblock );

			// O3
			panelblock = new SSVPanelBlock{name = "O3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "RCS/OMS/PRESS", "RCS He X10" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RCS/OMS PRPLT QTY", "OMS FUEL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MISSION TIMER", "MET" ) );
			panels.Add( panelblock );

			// O5

			// O6
			panelblock = new SSVPanelBlock{name = "O6", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 1 Cover", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 2 Cover", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER DOOR CONTROL SYS 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER POWER -Y", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRACKER POWER -Z", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ANNUNCIATOR BUS SELECT ACA 1", "MN A" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ANNUNCIATOR BUS SELECT ACA 2/3", "MN B" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM PL1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM PL2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM PL3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FA4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM FF4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 1 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 2 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 3 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 4 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 5 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC POWER 5", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 1 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 2 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 3 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 4 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 5 COVER", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 1", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 2", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 3", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 4", "NORMAL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC OUTPUT 5", "BACKUP" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IPL SOURCE", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 1", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 2", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 3", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 4", "RUN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "GPC MODE 5", "RUN" ) );
			panels.Add( panelblock );

			// O7

			// O8
			panelblock = new SSVPanelBlock{name = "O8", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "RADAR ALTIMETER 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADAR ALTIMETER 2", "ON" ) );
			panels.Add( panelblock );

			// O9

			//// Overhead aft
			// O13
			panelblock = new SSVPanelBlock{name = "O13", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "C&W A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "C&W B", "CLOSED" ) );
			panels.Add( panelblock );

			// O14
			panelblock = new SSVPanelBlock{name = "O14", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "BRAKES MN A", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 1/2 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 3/4 A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRKR -Z", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU LEFT MN A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU AFT MN A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "NOSE WHEEL STEERING MN A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "L OMS ENG VLV", "ON" ) );
			panels.Add( panelblock );

			// O15
			panelblock = new SSVPanelBlock{name = "O15", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "BRAKES MN B", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 1/2 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "NOSE WHEEL STEERING MN B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "STAR TRKR -Y", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU LEFT MN B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU RIGHT MN B", "CLOSED" ) );
			panels.Add( panelblock );

			// O16
			panelblock = new SSVPanelBlock{name = "O16", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "BRAKES MN C", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OF 3/4 B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU RIGHT MN C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "DDU AFT MN C", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "R OMS ENG VLV", "ON" ) );
			panels.Add( panelblock );

			// O17
			panelblock = new SSVPanelBlock{name = "O17", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 2", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ATVC 4", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EIU L-C", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EIU C-R", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EIU R-L", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MDM OA1/2/3", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MEC 1", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MEC 2", "ON" ) );
			panels.Add( panelblock );


			//// Overhead aft
			// L9

			// L10
			if (mission.LargeUpperStage == 1)
			{
				panelblock = new SSVPanelBlock{name = "L10_IUS", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "PANEL MODE", "PRIMARY" ) );
				panelblock.switch_pos.Add( Tuple.Create( "TILT TABLE ACTUATOR DRIVE ENABLE PRI 1", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "TILT TABLE ACTUATOR DRIVE ENABLE ALT 2", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "CMD PATH ENABLED", "RF" ) );
				panels.Add( panelblock );
			}

			// L12
			if (mission.LargeUpperStage == 1)
			{
				panelblock = new SSVPanelBlock{name = "L12U_IUS", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "ACT ORD ARM", "SAFE" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ACT 1 DISENG", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "IUS RF ANT E/D", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ACT 2 DISENG", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ACT ORD PREARM", "OFF" ) );
				panels.Add( panelblock );
			}
			else if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
			{
				panelblock = new SSVPanelBlock{name = "L12U_Centaur", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "SUPER*ZIP PRI ARM", "SAFE" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LOGIC PRI PWR", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "SSP PRI PWR", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "SUPER*ZIP BKUP ARM", "SAFE" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LOGIC BKUP PWR", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "SSP BKUP PWR", "OFF" ) );
				panels.Add( panelblock );
			}


			//// Aft
			// A1U
			panelblock = new SSVPanelBlock{name = "A1U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "SLEW RATE", "SLOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CONTROL", "COMMAND" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND STEERING MODE", "MAN SLEW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND POWER", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND MODE", "RDR PASSIVE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU BAND RADAR OUTPUT", "HIGH" ) );
			panels.Add( panelblock );

			// A1L

			// A1R

			// AFD
			panelblock = new SSVPanelBlock{name = "AftMDU", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "AFD1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panels.Add( panelblock );

			// A2
			panelblock = new SSVPanelBlock{name = "A2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "DIGI DIS SELECT", "EL/AZ" ) );
			panelblock.switch_pos.Add( Tuple.Create( "X-PNTR SCALE", "X10" ) );
			panels.Add( panelblock );

			// A3
			panelblock = new SSVPanelBlock{name = "A3", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "MONITOR 1", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "L-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "C-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "XHAIR", "0" ) );
			panelblock.obj.Add( panelobject );
			panelobject = new SSVscnObject{name = "MONITOR 2", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "L-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "C-DATA", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "XHAIR", "0" ) );
			panelblock.obj.Add( panelobject );
			panels.Add( panelblock );

			// A4
			panelblock = new SSVPanelBlock{name = "A4", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "MISSION TIMER", "MET" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIME", "0 0.000000 0 1" ) );
			panels.Add( panelblock );

			// A6U
			panelblock = new SSVPanelBlock{name = "A6U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "SENSE", "-Z" ) );
			panelblock.switch_pos.Add( Tuple.Create( "FLT CNTLR POWER", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LOGIC POWER SYS 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LOGIC POWER SYS 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 3", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 4", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RETENTION LATCHES 5", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD SELECT", GetPayloadSelectSwitch() ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ATTITUDE", "INRTL" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI ERROR", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ADI RATE", "MED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "ANNUNCIATOR BUS SELECT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MODE", "UP" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER MIN 1", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 10", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "EVENT TIMER SEC 1", "0" ) );
			panels.Add( panelblock );

			// A6L
			if (mission.OV.ODS)
			{
				panelblock = new SSVPanelBlock{name = "A6L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "ESS 1BC SYS PWR CNTL SYS 1", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ESS 1BC DEPRESS SYS 1 VENT ISOL", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A DEPRESS SYS 1 VENT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A DOCK LIGHT TRUSS FWD", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A DOCK LIGHT VEST PORT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ESS 2CA SYS PWR CNTL SYS 2", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "ESS 2CA DEPRESS SYS 2 VENT ISOL", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B DEPRESS SYS 2 VENT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B DOCK LIGHT TRUSS AFT", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B DOCK LIGHT VEST STBD", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A LOGIC 3", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN A LOGIC 1", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B LOGIC 1", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN B LOGIC 2", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN C LOGIC 2", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "MAIN C LOGIC 3", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS A OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS A CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS B OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 1 HOOKS SYS B CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS A OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS A CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS B OPEN", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 GRP 2 HOOKS SYS B CLOSE", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYRO POWER MN A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYRO POWER MN B", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PSU POWER MN A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PSU POWER MN B", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS TRUSS FWD", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS TRUSS AFT", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS VESTIBULE PORT", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "LIGHTS VESTIBULE STBD", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 HOOKS SYS A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PMA 2/3 HOOKS SYS B", "OFF" ) );
				panels.Add( panelblock );
			}

			// A7U
			panelblock = new SSVPanelBlock{name = "A7U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD AFT STBD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD AFT PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD MID STBD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD MID PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD FWD STBD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD FWD PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD DOCKING", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD BAY FLOOD FWD BHD", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RMS SPOTLIGHT PORT", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RMS CAMERA PORT", "ELBOW" ) );
			panelblock.switch_pos.Add( Tuple.Create( "CAMERA COMMAND PAN/TILT", "LOW RATE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "TV POWER CONTR UNIT", "OFF" ) );
			panels.Add( panelblock );

			// A7L
			if (mission.OV.ODS)
			{
				panelblock = new SSVPanelBlock{name = "A7L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "CONTROL PANEL POWER A", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "CONTROL PANEL POWER B", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "CONTROL PANEL POWER C", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "HEATERS/DCU POWER H1", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "HEATERS/DCU POWER H2/DCU", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "HEATERS/DCU POWER H3/DCU", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS POWER ADS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS POWER BDS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS POWER CDS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYROS Ap", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYROS Bp", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYROS Cp", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PYRO COMMANDS", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "APDS CONTROL COMMANDS", "CLOSED" ) );
				panels.Add( panelblock );
			}
			else if (mission.OV.PortLongeronSill == LongeronSillHardware_Type.SPDS)
			{
				panelblock = new SSVPanelBlock{name = "A7A3_SPDS", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE MN A", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE MN B", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER MN A", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER MN B", "OPEN" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS A ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS B ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS A FIRE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PAYLOAD RELEASE SYS B FIRE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS A ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS B ARM", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS A FIRE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PEDESTAL DRIVE XFER SYS B FIRE", "OFF" ) );
				panels.Add( panelblock );
			}

			// A8U
			if ((mission.OV.PortLongeronSill == LongeronSillHardware_Type.RMS) || (mission.OV.StbdLongeronSill == LongeronSillHardware_Type.RMS))
			{
				panelblock = new SSVPanelBlock{name = "A8A1", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "MODE", "TEST" ) );
				panelblock.switch_pos.Add( Tuple.Create( "END EFFECTOR MODE", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PARAMETER", "PORT TEMP LED/ABE/ID" ) );
				panelblock.switch_pos.Add( Tuple.Create( "JOINT", "CRIT TEMP" ) );
				panels.Add( panelblock );
			}

			// A8L
			if ((mission.OV.PortLongeronSill != LongeronSillHardware_Type.None) || (mission.OV.StbdLongeronSill != LongeronSillHardware_Type.None))
			{
				panelblock = new SSVPanelBlock{name = "A8A2", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
				panelblock.switch_pos.Add( Tuple.Create( "RMS SELECT", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "STARBOARD RMS COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "STARBOARD RMS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "STARBOARD RMS RETENTION LATCHES", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PORT RMS COVER", "CLOSED" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PORT RMS", "OFF" ) );
				panelblock.switch_pos.Add( Tuple.Create( "PORT RMS RETENTION LATCHES", "OFF" ) );
				panels.Add( panelblock );
			}


			//// Right
			// R10

			// R11U
			panelblock = new SSVPanelBlock{name = "R11U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelobject = new SSVscnObject{name = "CRT4", param_val = new List<Tuple<string,string>>()};
			panelobject.param_val.Add( Tuple.Create( "POWER", "OFF" ) );
			panelobject.param_val.Add( Tuple.Create( "DISPLAY", "0" ) );
			panelobject.param_val.Add( Tuple.Create( "MENU", "3" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_CFG", "AUTO" ) );
			panelobject.param_val.Add( Tuple.Create( "PORT_SEL", "PRI" ) );
			panelobject.param_val.Add( Tuple.Create( "BRIGHTNESS", "0.800000" ) );
			panelblock.obj.Add( panelobject );
			panels.Add( panelblock );

			// R11L
			panelblock = new SSVPanelBlock{name = "R11L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 4 POWER", "ON" ) );
			panelblock.switch_pos.Add( Tuple.Create( "IDP/CRT 4 MAJ FUNC", "GNC" ) );
			panels.Add( panelblock );

			// R13U
			panelblock = new SSVPanelBlock{name = "R13U", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "PARAMETER SELECT 100", "1" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PARAMETER SELECT 10", "2" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PARAMETER SELECT 1", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT SET VALUE 1", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT SET VALUE 01", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT SET VALUE 005", "0" ) );
			panelblock.switch_pos.Add( Tuple.Create( "LIMIT", "LOWER" ) );
			panels.Add( panelblock );

			// R13L
			panelblock = new SSVPanelBlock{name = "R13L", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY DOOR SYS 1", "DISABLE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY DOOR SYS 2", "DISABLE" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY MECH PWR SYS 1", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY MECH PWR SYS 2", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "PL BAY DOOR", "STOP" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR LATCH CONTROL SYS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR LATCH CONTROL SYS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR CONTROL SYS A", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "RADIATOR CONTROL SYS B", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU ANTENNA DIRECT STOW", "OFF" ) );
			panelblock.switch_pos.Add( Tuple.Create( "KU ANTENNA", "GND" ) );
			panels.Add( panelblock );

			// R14
			panelblock = new SSVPanelBlock{name = "R14", obj = new List<SSVscnObject>(), switch_pos = new List<Tuple<string,string>>()};
			panelblock.switch_pos.Add( Tuple.Create( "MNC MDU CDR 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB MDU CDR 2", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB MDU MFD 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA MDU MFD 2", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA MDU PLT 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC MDU PLT 2", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC MDU AFD 1", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA ADC 1A 2A", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB ADC 1B 2B", "CLOSED" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV A CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV A CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV A CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC TV B CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC TV B CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNC TV B CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV C CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV C CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV C CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV D CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV D CAMR CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV D CAMR ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV RMS CAMR CAMR/PTU", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV RMS CAMR WRIST ILLUM/CAMR HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV RMS CAMR ELB ILLUM/PTU HTR", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV CONTR UNIT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV CONTR UNIT", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNA TV MON 1", "OPEN" ) );
			panelblock.switch_pos.Add( Tuple.Create( "MNB TV MON 2", "OPEN" ) );
			panels.Add( panelblock );
			return;
		}

		private void SetMFDs_LaunchT9m()
		{
			// the on/off status must match the scenario blocks below

			// CDR 1
			mfds[0].on = true;
			mfds[0].type = "User";
			mfds[0]._params.Clear();
			mfds[0]._params.Add( "MODE CRT" );

			// CDR 2
			mfds[1].on = true;
			mfds[1].type = "User";
			mfds[1]._params.Clear();
			mfds[1]._params.Add( "MODE CRT" );

			// PLT 1
			mfds[2].on = true;
			mfds[2].type = "User";
			mfds[2]._params.Clear();
			mfds[2]._params.Add( "MODE CRT" );

			// PLT 2
			mfds[3].on = true;
			mfds[3].type = "User";
			mfds[3]._params.Clear();
			mfds[3]._params.Add( "MODE CRT" );

			// CRT 1
			mfds[4].on = true;
			mfds[4].type = "User";
			mfds[4]._params.Clear();
			mfds[4]._params.Add( "MODE CRT" );

			// CRT 2
			mfds[5].on = true;
			mfds[5].type = "User";
			mfds[5]._params.Clear();
			mfds[5]._params.Add( "MODE CRT" );

			// CRT 3
			mfds[6].on = true;
			mfds[6].type = "User";
			mfds[6]._params.Clear();
			mfds[6]._params.Add( "MODE CRT" );

			// CRT 4
			mfds[7].on = false;

			// MFD 1
			mfds[8].on = true;
			mfds[8].type = "User";
			mfds[8]._params.Clear();
			mfds[8]._params.Add( "MODE CRT" );

			// MFD 2
			mfds[9].on = true;
			mfds[9].type = "User";
			mfds[9]._params.Clear();
			mfds[9]._params.Add( "MODE CRT" );

			// AFD 1
			mfds[10].on = false;

			// not used
			mfds[11].on = false;
			return;
		}

		private void SetMFDs_LaunchT31s()
		{
			SetMFDs_LaunchT9m();
			return;
		}

		private void GPC_LaunchT9m()
		{
			SSVSimpleGPCSoftwareBlock gpcswblock;
			SSVSubsystemBlock subsysblock = new SSVSubsystemBlock{name = "SimpleGPC1", param_val = new List<Tuple<string,string>>(), gpcsw = new List<SSVSimpleGPCSoftwareBlock>()};
			// COMPOOL vars
			subsysblock.param_val.Add( Tuple.Create( "MM", "101" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_SPEC", "65535 65535 65535 65535" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_DISP", "65535 18 18 65535" ) );
			subsysblock.param_val.Add( Tuple.Create( "OVHD", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "IGS", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "IGI", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "RWID", "1" ) );
			if (mission.LaunchSite == 1) subsysblock.param_val.Add( Tuple.Create( "LSID", "24" ) );
			else subsysblock.param_val.Add( Tuple.Create( "LSID", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "ALL_VENT_CLOSE_CMD", "1" ) );
			// TODO software vars
			gpcswblock = new SSVSimpleGPCSoftwareBlock{name = "SSME_SOP", param_val = new List<Tuple<string,string>>()};
			gpcswblock.param_val.Add( Tuple.Create( "ShutdownPhase_1", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "ShutdownPhase_2", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "ShutdownPhase_3", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "PostShutdownPhase_1", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "PostShutdownPhase_2", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "PostShutdownPhase_3", "0" ) );
			subsysblock.gpcsw.Add( gpcswblock );
			if (mission.OV.TgtVessel.Length != 0)
			{
				gpcswblock = new SSVSimpleGPCSoftwareBlock{name = "StateVectorSoftware", param_val = new List<Tuple<string,string>>()};
				gpcswblock.param_val.Add( Tuple.Create( "TARGET_VESSEL", mission.OV.TgtVessel ) );
				subsysblock.gpcsw.Add( gpcswblock );
			}
			gpcswblock = new SSVSimpleGPCSoftwareBlock{name = "MPS_ATVC_CMD_SOP", param_val = new List<Tuple<string,string>>()};
			gpcswblock.param_val.Add( Tuple.Create( "CenterPitch", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "CenterYaw", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "LeftPitch", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "LeftYaw", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "RightPitch", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "RightYaw", "0.000000" ) );
			subsysblock.gpcsw.Add( gpcswblock );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "SimpleGPC2", param_val = new List<Tuple<string,string>>(), gpcsw = new List<SSVSimpleGPCSoftwareBlock>()};
			// COMPOOL vars
			subsysblock.param_val.Add( Tuple.Create( "MM", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_SPEC", "65535 65535 65535 65535" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_DISP", "65535 65535 65535 65535" ) );

			subsys.Add( subsysblock );
			return;
		}

		private void GPC_LaunchT31s()
		{
			SSVSimpleGPCSoftwareBlock gpcswblock;
			SSVSubsystemBlock subsysblock = new SSVSubsystemBlock{name = "SimpleGPC1", param_val = new List<Tuple<string,string>>(), gpcsw = new List<SSVSimpleGPCSoftwareBlock>()};
			// COMPOOL vars
			subsysblock.param_val.Add( Tuple.Create( "MM", "101" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_SPEC", "65535 65535 65535 65535" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_DISP", "65535 18 18 65535" ) );
			subsysblock.param_val.Add( Tuple.Create( "OVHD", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "IGS", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "IGI", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "RWID", "1" ) );
			if (mission.LaunchSite == 1) subsysblock.param_val.Add( Tuple.Create( "LSID", "24" ) );
			else subsysblock.param_val.Add( Tuple.Create( "LSID", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "ALL_VENT_CLOSE_CMD", "1" ) );
			// TODO software vars
			gpcswblock = new SSVSimpleGPCSoftwareBlock{name = "SSME_SOP", param_val = new List<Tuple<string,string>>()};
			gpcswblock.param_val.Add( Tuple.Create( "ShutdownPhase_1", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "ShutdownPhase_2", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "ShutdownPhase_3", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "PostShutdownPhase_1", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "PostShutdownPhase_2", "0" ) );
			gpcswblock.param_val.Add( Tuple.Create( "PostShutdownPhase_3", "0" ) );
			subsysblock.gpcsw.Add( gpcswblock );
			if (mission.OV.TgtVessel.Length != 0)
			{
				gpcswblock = new SSVSimpleGPCSoftwareBlock{name = "StateVectorSoftware", param_val = new List<Tuple<string,string>>()};
				gpcswblock.param_val.Add( Tuple.Create( "TARGET_VESSEL", mission.OV.TgtVessel ) );
				subsysblock.gpcsw.Add( gpcswblock );
			}
			gpcswblock = new SSVSimpleGPCSoftwareBlock{name = "MPS_ATVC_CMD_SOP", param_val = new List<Tuple<string,string>>()};
			gpcswblock.param_val.Add( Tuple.Create( "CenterPitch", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "CenterYaw", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "LeftPitch", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "LeftYaw", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "RightPitch", "0.000000" ) );
			gpcswblock.param_val.Add( Tuple.Create( "RightYaw", "0.000000" ) );
			subsysblock.gpcsw.Add( gpcswblock );
			subsys.Add( subsysblock );


			subsysblock = new SSVSubsystemBlock{name = "SimpleGPC2", param_val = new List<Tuple<string,string>>(), gpcsw = new List<SSVSimpleGPCSoftwareBlock>()};
			// COMPOOL vars
			subsysblock.param_val.Add( Tuple.Create( "MM", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_SPEC", "65535 65535 65535 65535" ) );
			subsysblock.param_val.Add( Tuple.Create( "CRT_DISP", "65535 65535 65535 65535" ) );

			subsys.Add( subsysblock );
			return;
		}

		void CW_LaunchT9m()
		{
			SSVSubsystemBlock subsysblock = new SSVSubsystemBlock{name = "PrimaryCaution&Warning", param_val = new List<Tuple<string,string>>()};
			{
				// inhibited params
				byte[] inhibit = new byte[128];
				inhibit[8] = 1;// 8	APU-1 EGT
				inhibit[18] = 1;// 18	APU-2 EGT
				inhibit[28] = 1;// 28	APU-3 EGT
				inhibit[77] = 1;// 77	OMS PBK OXID TK ULL P
				inhibit[87] = 1;// 87	OMS PBK FUEL TK ULL P
				if (mission.OV.PRSDInternalTanks < 3)// only if PRSD TK3 not flown
				{
					inhibit[20] = 1;// 20	CRYO O2 P TK3
					inhibit[41] = 1;// 41	CRYO O2 HTR1 TK3
					inhibit[51] = 1;// 51	CRYO O2 HTR2 TK3
					inhibit[70] = 1;// 70	CRYO H2 P TK3
				}
				if (mission.OV.PRSDInternalTanks < 4)// only if PRSD TK4 not flown
				{
					inhibit[30] = 1;// 30	CRYO O2 P TK4
					inhibit[61] = 1;// 61	CRYO O2 HTR1 TK4
					inhibit[71] = 1;// 71	CRYO O2 HTR2 TK4
					inhibit[80] = 1;// 80	CRYO H2 P TK4
				}
				if (mission.OV.PRSDInternalTanks < 5)// only if PRSD TK5 not flown
				{
					inhibit[40] = 1;// 40	CRYO O2 P TK5
					inhibit[81] = 1;// 81	CRYO O2 HTR1 TK5
					inhibit[90] = 1;// 90	CRYO H2 P TK5
				}
				int itmp;
				string stmp = "";
				for (int i = 0; i < 128; i += 8)
				{
					itmp = (inhibit[i + 7] << 7) | (inhibit[i + 6] << 6) | (inhibit[i + 5] << 5) | (inhibit[i + 4] << 4) | (inhibit[i + 3] << 3) | (inhibit[i + 2] << 2) | (inhibit[i + 1] << 1) | inhibit[i];
					stmp = ((byte)itmp).ToString( "x2" ) + stmp;
				}
				subsysblock.param_val.Add( Tuple.Create( "INHIBITMEMORY", stmp ) );
			}
			subsysblock.param_val.Add( Tuple.Create( "NCOUNTMEMORY", "00000000800000000080000000008000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "NCOUNTOVERFLOWMEMORY", "00802008000000000000000000000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RECALLMEMORY", "00802008000000000000000000000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "PRIMARYCWTRIGGERMEMORY", "00802008000000000000000000000000" ) );
			{
				// lower limit changes
				double[] lower = new double[128];
				for (int i = 0; i < 128; i++) lower[i] = -1.0;
				lower[74] = 2.60;// 74	CABIN FAN dP		2.60v / 4.16'' H2O
				lower[106] = 0.80;// 106	FREON FLOW 1		0.80v / 1186lb/h
				lower[116] = 0.80;// 116	FREON FLOW 2		0.80v / 1186lb/h
				int itmp;
				string stmp = "";
				for (int i = 0; i < 128; i++)
				{
					if (lower[i] < 0.0)
					{
						stmp = "00" + stmp;
						continue;
					}
					itmp = (int)(lower[i] * 20);
					itmp |= 0x80;// set value used
					stmp = ((byte)itmp).ToString( "x2" ) + stmp;
				}

				// upper limit changes
				double[] upper = new double[128];
				for (int i = 0; i < 128; i++) upper[i] = -1.0;
				upper[4] = 3.85;// 4	CABIN PRESS		3.85v (average)
				if (mission.OV.Name != OV_Name.Endeavour)
					upper[7] = 3.60;// 7	OMS TK P OX-L		3.60v / 288psi (OV-102,103,104)
				else
					upper[7] = 3.70;// 7	OMS TK P OX-L		3.70v / 296psi (OV-105)
				upper[17] = 3.60;// 17	OMS TK P FU-L		3.60v / 288psi
				upper[37] = 3.60;// 37	OMS TK P OX-R		3.60v / 288psi
				upper[47] = 3.60;// 47	OMS TK P FU-R		3.60v / 288psi
				upper[74] = 4.25;// 74	CABIN FAN dP		4.25v / 6.80'' H2O
				upper[79] = 3.25;// 79	MANF P LH2		3.25v / 65psi
				upper[107] = 4.30;// 107	FREON LOOP 1 EVAP OUT T	4.30v / 115.2ºF
				upper[117] = 4.30;// 117	FREON LOOP 2 EVAP OUT T	4.30v / 115.2ºF
				for (int i = 0; i < 128; i++)
				{
					if (upper[i] < 0.0)
					{
						stmp = "00" + stmp;
						continue;
					}
					itmp = (int)(upper[i] * 20);
					itmp |= 0x80;// set value used
					stmp = ((byte)itmp).ToString( "x2" ) + stmp;
				}
				subsysblock.param_val.Add( Tuple.Create( "LIMITVALUERAM", stmp ) );
			}
			subsysblock.param_val.Add( Tuple.Create( "PRI_CW_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "PRI_CW_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "CW_TONE_ENABLE_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "CW_TONE_ENABLE_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_TONE_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_TONE_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_LIGHT_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_LIGHT_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "SW_TONE_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "SW_TONE_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_1_A", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_1_B", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_2_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_2_B", "0" ) );
			subsys.Add( subsysblock );
			return;
		}

		void CW_LaunchT31s()
		{
			SSVSubsystemBlock subsysblock = new SSVSubsystemBlock{name = "PrimaryCaution&Warning", param_val = new List<Tuple<string,string>>()};
			{
				// inhibited params
				byte[] inhibit = new byte[128];
				inhibit[8] = 1;// 8	APU-1 EGT
				inhibit[18] = 1;// 18	APU-2 EGT
				inhibit[28] = 1;// 28	APU-3 EGT
				inhibit[77] = 1;// 77	OMS PBK OXID TK ULL P
				inhibit[87] = 1;// 87	OMS PBK FUEL TK ULL P
				if (mission.OV.PRSDInternalTanks < 3)// only if PRSD TK3 not flown
				{
					inhibit[20] = 1;// 20	CRYO O2 P TK3
					inhibit[41] = 1;// 41	CRYO O2 HTR1 TK3
					inhibit[51] = 1;// 51	CRYO O2 HTR2 TK3
					inhibit[70] = 1;// 70	CRYO H2 P TK3
				}
				if (mission.OV.PRSDInternalTanks < 4)// only if PRSD TK4 not flown
				{
					inhibit[30] = 1;// 30	CRYO O2 P TK4
					inhibit[61] = 1;// 61	CRYO O2 HTR1 TK4
					inhibit[71] = 1;// 71	CRYO O2 HTR2 TK4
					inhibit[80] = 1;// 80	CRYO H2 P TK4
				}
				if (mission.OV.PRSDInternalTanks < 5)// only if PRSD TK5 not flown
				{
					inhibit[40] = 1;// 40	CRYO O2 P TK5
					inhibit[81] = 1;// 81	CRYO O2 HTR1 TK5
					inhibit[90] = 1;// 90	CRYO H2 P TK5
				}
				int itmp;
				string stmp = "";
				for (int i = 0; i < 128; i += 8)
				{
					itmp = (inhibit[i + 7] << 7) | (inhibit[i + 6] << 6) | (inhibit[i + 5] << 5) | (inhibit[i + 4] << 4) | (inhibit[i + 3] << 3) | (inhibit[i + 2] << 2) | (inhibit[i + 1] << 1) | inhibit[i];
					stmp = ((byte)itmp).ToString( "x2" ) + stmp;
				}
				subsysblock.param_val.Add( Tuple.Create( "INHIBITMEMORY", stmp ) );
			}
			subsysblock.param_val.Add( Tuple.Create( "NCOUNTMEMORY", "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "NCOUNTOVERFLOWMEMORY", "00000000000000000000000000000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "RECALLMEMORY", "00000000000000000000000000000000" ) );
			subsysblock.param_val.Add( Tuple.Create( "PRIMARYCWTRIGGERMEMORY", "00000000000000000000000000000000" ) );
			{
				// lower limit changes
				double[] lower = new double[128];
				for (int i = 0; i < 128; i++) lower[i] = -1.0;
				lower[74] = 2.60;// 74	CABIN FAN dP		2.60v / 4.16'' H2O
				lower[106] = 0.80;// 106	FREON FLOW 1		0.80v / 1186lb/h
				lower[116] = 0.80;// 116	FREON FLOW 2		0.80v / 1186lb/h
				int itmp;
				string stmp = "";
				for (int i = 0; i < 128; i++)
				{
					if (lower[i] < 0.0)
					{
						stmp = "00" + stmp;
						continue;
					}
					itmp = (int)(lower[i] * 20);
					itmp |= 0x80;// set value used
					stmp = ((byte)itmp).ToString( "x2" ) + stmp;
				}

				// upper limit changes
				double[] upper = new double[128];
				for (int i = 0; i < 128; i++) upper[i] = -1.0;
				upper[4] = 3.85;// 4	CABIN PRESS		3.85v (average)
				if (mission.OV.Name != OV_Name.Endeavour)
					upper[7] = 3.60;// 7	OMS TK P OX-L		3.60v / 288psi (OV-102,103,104)
				else
					upper[7] = 3.70;// 7	OMS TK P OX-L		3.70v / 296psi (OV-105)
				upper[17] = 3.60;// 17	OMS TK P FU-L		3.60v / 288psi
				upper[37] = 3.60;// 37	OMS TK P OX-R		3.60v / 288psi
				upper[47] = 3.60;// 47	OMS TK P FU-R		3.60v / 288psi
				upper[74] = 4.25;// 74	CABIN FAN dP		4.25v / 6.80'' H2O
				upper[79] = 3.25;// 79	MANF P LH2		3.25v / 65psi
				upper[107] = 4.30;// 107	FREON LOOP 1 EVAP OUT T	4.30v / 115.2ºF
				upper[117] = 4.30;// 117	FREON LOOP 2 EVAP OUT T	4.30v / 115.2ºF
				for (int i = 0; i < 128; i++)
				{
					if (upper[i] < 0.0)
					{
						stmp = "00" + stmp;
						continue;
					}
					itmp = (int)(upper[i] * 20);
					itmp |= 0x80;// set value used
					stmp = ((byte)itmp).ToString( "x2" ) + stmp;
				}
				subsysblock.param_val.Add( Tuple.Create( "LIMITVALUERAM", stmp ) );
			}
			subsysblock.param_val.Add( Tuple.Create( "PRI_CW_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "PRI_CW_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "CW_TONE_ENABLE_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "CW_TONE_ENABLE_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_TONE_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_TONE_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_LIGHT_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "BU_CW_LIGHT_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "SW_TONE_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "SW_TONE_B", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_1_A", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_1_B", "1" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_2_A", "0" ) );
			subsysblock.param_val.Add( Tuple.Create( "ST_FAIL_2_B", "0" ) );
			subsys.Add( subsysblock );
			return;
		}

		string GetPayloadSelectSwitch()
		{
			// if only 1 PL position is used, set that PL position for launch
			// otherwise, set monitor

			int prev_plsys = 0;
			foreach (Mission_PLActive pl in mission.OV.PL_Active)
			{
				if (pl.IsUsed)
				{
					foreach (Mission_PayloadLatch ltch in pl.Latches)
					{
						if (ltch.PLID != 0)
						{
							int plsys = (ltch.Latch / 5) + 1;
							if (plsys != prev_plsys)
							{
								if (prev_plsys != 0)
								{
									// found a new PL position, and already used another, set monitor
									return "MON1";
								}
								prev_plsys = plsys;
							}
						}
					}
				}
			}

			if ((mission.LargeUpperStage == 1) || (mission.LargeUpperStage == 2) || (mission.LargeUpperStage == 3))
			{
				for (int i = 0; i < 2; i++)
				{
					int plsys = (mission.OV.LargeUpperStage_Latch[i] / 5) + 1;
					if (plsys != prev_plsys)
					{
						if (prev_plsys != 0)
						{
							// found a new PL position, and already used another, set monitor
							return "MON1";
						}
						prev_plsys = plsys;
					}
				}
			}

			if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
			{
				for (int i = 0; i < 2; i++)
				{
					int plsys = (mission.OV.LargeUpperStage_Latch[i] / 5) + 1;
					if (plsys != prev_plsys)
					{
						if (prev_plsys != 0)
						{
							// found a new PL position, and already used another, set monitor
							return "MON1";
						}
						prev_plsys = plsys;
					}
				}
			}

			if (prev_plsys != 0)
			{
				// only one PL position used, set switch to it
				if ((prev_plsys >= 1) && (prev_plsys <= 3))// just to make sure the position is valid
				{
					return prev_plsys.ToString();
				}
			}

			// default
			return "MON1";
		}


		Mission mission;
		MFDtype[] mfds;

		protected int config;

		protected int vcpos;

		protected double sbtc_l;
		protected double sbtc_r;

		protected string staticcargo_mesh;

		protected double staticcargo_ofsx;
		protected double staticcargo_ofsy;
		protected double staticcargo_ofsz;

		protected double plmass;

		protected List<SSVSubsystemBlock> subsys;
		protected List<SSVPanelBlock> panels;


		private double loms;// 0-100%
		public double LOMS
		{
			get { return loms; }
			set
			{
				loms = value;
				OnPropertyChanged( "LOMS" );
			}
		}

		private double roms;// 0-100%
		public double ROMS
		{
			get { return roms; }
			set
			{
				roms = value;
				OnPropertyChanged( "ROMS" );
			}
		}

		private double frcs;// 0-100%
		public double FRCS
		{
			get { return frcs; }
			set
			{
				frcs = value;
				OnPropertyChanged( "FRCS" );
			}
		}

		private double lrcs;// 0-100%
		public double LRCS
		{
			get { return lrcs; }
			set
			{
				lrcs = value;
				OnPropertyChanged( "LRCS" );
			}
		}

		private double rrcs;// 0-100%
		public double RRCS
		{
			get { return rrcs; }
			set
			{
				rrcs = value;
				OnPropertyChanged( "RRCS" );
			}
		}

		public event PropertyChangedEventHandler PropertyChanged;

		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
