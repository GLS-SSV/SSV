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

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Input;
using CommunityToolkit.Mvvm.Input;
using SSVMissionEditor.DataAccess;
using SSVMissionEditor.Model;


namespace SSVMissionEditor.ViewModel
{
	class MainWindowViewModel : INotifyPropertyChanged
	{
		private Mission mission;
		private LandingSite landingsite;


		public MainWindowViewModel( Mission mission, LandingSite landingsite )
		{
			this.mission = mission;
			this.landingsite = landingsite;

			// setup I-Load list "espionage" to update various parameters
			foreach (Mission_ILOAD iload in ILOAD_List)
			{
				switch (iload.ID)
				{
					case "T1_ILOAD_ARRAY":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
					case "DT_ILOAD_ARRAY":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
					case "EL_ILOAD_ARRAY":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
					case "XOFF_ILOAD_ARRAY":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
					case "YOFF_ILOAD_ARRAY":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
					case "ZOFF_ILOAD_ARRAY":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
					case "LAMB_ILOAD":
						iload.PropertyChanged += new PropertyChangedEventHandler( ILOAD_Changed_OrbitTargetSet );
						break;
				}
			}



			/// ORBITER tab
			// enable/disable features
			Orbiter_Update_Enables();

			if (Orbiter_Airlock == Defs.strExternal)
			{
				Orbiter_TAA_src = Orbiter_TAA_ExtAL_src;
			}
			else
			{
				Orbiter_TAA_src = Orbiter_TAA_noExtAL_src;
				if (Orbiter_TAA == Defs.strAft) Orbiter_TAA = Defs.strNone;
			}

			// update OV texture list
			Orbiter_Update_OV_Texture();
			// find if using a default texture
			bool texdone = false;
			foreach (Defs.TEX_INFO tex in Orbiter_Default_Texture_src)
			{
				if (tex.File == mission.OV.Texture)
				{
					Orbiter_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) Orbiter_Default_Texture = Orbiter_Default_Texture_src.Last();

			// update Left OMS texture list
			Orbiter_Update_LOMS_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in Orbiter_LOMS_Default_Texture_src)
			{
				if (tex.File == mission.OV.LOMStex)
				{
					Orbiter_LOMS_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) Orbiter_LOMS_Default_Texture = Orbiter_LOMS_Default_Texture_src.Last();

			// update Right OMS texture list
			Orbiter_Update_ROMS_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in Orbiter_ROMS_Default_Texture_src)
			{
				if (tex.File == mission.OV.ROMStex)
				{
					Orbiter_ROMS_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) Orbiter_ROMS_Default_Texture = Orbiter_ROMS_Default_Texture_src.Last();

			Orbiter_CCTV_Keel_PLID_src = new List<string>();
			foreach (int x in Defs.KEEL_CAMERA)
			{
				Orbiter_CCTV_Keel_PLID_src.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
			}

			Orbiter_EditPLBCameraCommand = new RelayCommand<object>( EditPLBCameraCommand );

			Orbiter_EditRMSportCommand = new RelayCommand( EditRMSportCommand );
			Orbiter_EditRMSstbdCommand = new RelayCommand( EditRMSstbdCommand );



			/// LAUNCH tab
			Launch_CalcAscentCommand = new RelayCommand( CalcAscentCommand );
			Launch_AscentSaveCommand = new RelayCommand( AscentSaveCommand, AscentSaveCommandEnabled );

			if (mission.LaunchSite == Defs.strKSC)
			{
				// KSC
				Launch_PadMLP_ena = true;
				Launch_Pad_src = Launch_PadKSC_src;
			}
			else
			{
				// VAFB
				Launch_PadMLP_ena = false;
				Launch_Pad_src = Launch_PadVAFB_src;
				// override mission data
				Launch_Pad = "";
				Launch_PadType = "";
				Launch_MLP = "";
			}

			// load default ascent target values
			// TODO load from mission
			Launch_DI = true;
			Launch_MECOInclination = 51.6;
			Launch_MECOAltitude = 52;
			Launch_OMS1MECOTargetAltitude = 160.0;
			Launch_OMS2TargetAltitude = 160.0;
			Launch_RTHU = true;



			/// ORBIT tab
			Orbit_LoadTgtSetsCommand = new RelayCommand( LoadTgtSetsCommand, LoadTgtSetsCommandEnabled );
			Orbit_PickTgtVesselCommand = new RelayCommand( PickTgtVesselCommand );

			Orbit_OrbTgtSets = Defs.OrbitTargets();

			Orbit_CurOrbTgtSet = GetCurrentOrbitTargetSet();



			/// LANDING tab
			Landing_SetDefaultLSTCommand = new RelayCommand( SetDefaultLSTCommand, SetDefaultLSTCommandEnabled );
			Landing_SetRunwayCommand = new RelayCommand( SetRunwayCommand );

			// runways
			Landing_Runways = landingsite.GetLandingSiteNames();

			// default runway tables
			List<Tuple<string,List<Tuple<string,string>>>> DefaultRunwayTables = Defs.DefaultRunwayTables();

			Landing_DefaultLSTableNames = new List<string>();
			foreach (Tuple<string,List<Tuple<string,string>>> table in DefaultRunwayTables)
			{
				Landing_DefaultLSTableNames.Add( table.Item1 );
			}

			Landing_LST = FormatLandingSiteTable( mission.OV.LandingSiteTable );

			Landing_LSDBidx = 0;
			Landing_DefaultLSidx = -1;
			Landing_ManLSID = 0;
			Landing_ManRW = "P";



			/// ET/SRB tab
			// update ET texture list
			ETSRB_ET_Update_ET_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in ETSRB_ET_Default_Texture_src)
			{
				if (tex.File == mission.ET.Texture)
				{
					ETSRB_ET_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) ETSRB_ET_Default_Texture = ETSRB_ET_Default_Texture_src.Last();

			ET_Update_Enables();
			ET_Update_Features();

			// update SRB LH Fwd Assembly texture list
			ETSRB_ET_Update_SRB_LH_Fwd_Assembly_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in ETSRB_LHFwdAssembly_Default_Texture_src)
			{
				if (tex.File == mission.SRB.LHFwdAssemblyTexture)
				{
					ETSRB_LHFwdAssembly_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) ETSRB_LHFwdAssembly_Default_Texture = ETSRB_LHFwdAssembly_Default_Texture_src.Last();

			// update SRB RH Fwd Assembly texture list
			ETSRB_ET_Update_SRB_RH_Fwd_Assembly_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in ETSRB_RHFwdAssembly_Default_Texture_src)
			{
				if (tex.File == mission.SRB.RHFwdAssemblyTexture)
				{
					ETSRB_RHFwdAssembly_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) ETSRB_RHFwdAssembly_Default_Texture = ETSRB_RHFwdAssembly_Default_Texture_src.Last();

			// update SRB LH Case texture list
			ETSRB_ET_Update_SRB_LH_Case_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in ETSRB_LHCase_Default_Texture_src)
			{
				if (tex.File == mission.SRB.LHCaseTexture)
				{
					ETSRB_LHCase_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) ETSRB_LHCase_Default_Texture = ETSRB_LHCase_Default_Texture_src.Last();

			// update SRB RH Case texture list
			ETSRB_ET_Update_SRB_RH_Case_Texture();
			// find if using a default texture
			texdone = false;
			foreach (Defs.TEX_INFO tex in ETSRB_RHCase_Default_Texture_src)
			{
				if (tex.File == mission.SRB.RHCaseTexture)
				{
					ETSRB_RHCase_Default_Texture = tex;
					texdone = true;
					break;
				}
			}
			if (texdone == false) ETSRB_RHCase_Default_Texture = ETSRB_RHCase_Default_Texture_src.Last();




			/// OTHER VESSELS tab
			OtherVessels_NewVesselCommand = new RelayCommand( NewVesselCommand );
			OtherVessels_DeleteVesselCommand = new RelayCommand( DeleteVesselCommand );
			OtherVessels_GetVesselClassCommand = new RelayCommand( GetVesselClassCommand );
			return;
		}

		private void ILOAD_Changed_OrbitTargetSet( object sender, PropertyChangedEventArgs e )
		{
			Orbit_CurOrbTgtSet = GetCurrentOrbitTargetSet();
			return;
		}

		/// FLT NO tab
		/// <summary>
		/// The name of the mission
		/// </summary>
		public string FltNo_Name
		{
			get { return mission.Name; }
			set
			{
				mission.Name = value;
				OnPropertyChanged( "FltNo_Name" );
			}
		}

		/// <summary>
		/// Mission description
		/// </summary>
		public string FltNo_Description
		{
			get { return mission.Description; }
			set
			{
				mission.Description = value;
				OnPropertyChanged( "FltNo_Description" );
			}
		}

		/// ORBITER tab
		void Orbiter_Update_Enables()
		{
			switch (Orbiter_Vehicle)
			{
				case Defs.strColumbia:
					Orbiter_SILTS_ena = true;

					Orbiter_FwdBulkDockLights_ena = false;

					Orbiter_DragChute_ena = true;

					Orbiter_DFIWireTray_ena = true;

					Orbiter_VentDoors4and7_ena = true;

					Orbiter_ExtAL_ODS_Kit_ena = true;

					CrewModule_EjectionSeats_ena = true;

					Consumables_EDOKit_ena = true;

					Consumables_EDOPallet_src = Consumables_EDOPallet_Single_src;
					break;
				case Defs.strChallenger:
					Orbiter_SILTS_ena = false;

					Orbiter_FwdBulkDockLights_ena = false;

					Orbiter_DragChute_ena = false;

					Orbiter_DFIWireTray_ena = false;

					Orbiter_VentDoors4and7_ena = false;

					Orbiter_ExtAL_ODS_Kit_ena = false;

					CrewModule_EjectionSeats_ena = false;

					Consumables_EDOKit_ena = false;

					Consumables_EDOPallet_src = Consumables_EDOPallet_Single_src;
					break;
				case Defs.strDiscovery:
					Orbiter_SILTS_ena = false;

					Orbiter_FwdBulkDockLights_ena = true;

					Orbiter_DragChute_ena = true;

					Orbiter_DFIWireTray_ena = false;

					Orbiter_VentDoors4and7_ena = true;

					Orbiter_ExtAL_ODS_Kit_ena = true;

					CrewModule_EjectionSeats_ena = false;

					Consumables_EDOKit_ena = false;

					Consumables_EDOPallet_src = Consumables_EDOPallet_Single_src;
					break;
				case Defs.strAtlantis:
					Orbiter_SILTS_ena = false;

					Orbiter_FwdBulkDockLights_ena = false;

					Orbiter_DragChute_ena = true;

					Orbiter_DFIWireTray_ena = false;

					Orbiter_VentDoors4and7_ena = true;

					Orbiter_ExtAL_ODS_Kit_ena = true;

					CrewModule_EjectionSeats_ena = false;

					Consumables_EDOKit_ena = true;

					Consumables_EDOPallet_src = Consumables_EDOPallet_Single_src;
					break;
				case Defs.strEndeavour:
					Orbiter_SILTS_ena = false;

					Orbiter_FwdBulkDockLights_ena = true;

					Orbiter_DragChute_ena = false;

					Orbiter_DFIWireTray_ena = false;

					Orbiter_VentDoors4and7_ena = true;

					Orbiter_ExtAL_ODS_Kit_ena = true;

					CrewModule_EjectionSeats_ena = false;

					Consumables_EDOKit_ena = true;

					Consumables_EDOPallet_src = Consumables_EDOPallet_Dual_src;
					break;
			}
			return;
		}

		void Orbiter_Update_Features()
		{
			switch (Orbiter_Vehicle)
			{
				case Defs.strColumbia:
					Orbiter_FwdBulkDockLights = true;

					if ((Consumables_EDOPallet < 0) || (Consumables_EDOPallet > 1)) Consumables_EDOPallet = 1;
					break;
				case Defs.strChallenger:
					Orbiter_SILTS = false;

					Orbiter_FwdBulkDockLights = true;

					Orbiter_DragChute = false;

					Orbiter_DFIWireTray = false;

					Orbiter_VentDoors4and7 = true;

					Orbiter_ExtAL_ODS_Kit = false;

					Orbiter_Airlock = Defs.strInternal;

					CrewModule_EjectionSeats = false;

					Consumables_EDOKit = false;

					if ((Consumables_EDOPallet < 0) || (Consumables_EDOPallet > 1)) Consumables_EDOPallet = 1;
					break;
				case Defs.strDiscovery:
					Orbiter_SILTS = false;

					Orbiter_DFIWireTray = false;

					CrewModule_EjectionSeats = false;

					Consumables_EDOKit = false;

					if ((Consumables_EDOPallet < 0) || (Consumables_EDOPallet > 1)) Consumables_EDOPallet = 1;
					break;
				case Defs.strAtlantis:
					Orbiter_SILTS = false;

					Orbiter_FwdBulkDockLights = true;

					Orbiter_DFIWireTray = false;

					CrewModule_EjectionSeats = false;

					if ((Consumables_EDOPallet < 0) || (Consumables_EDOPallet > 1)) Consumables_EDOPallet = 1;
					break;
				case Defs.strEndeavour:
					Orbiter_SILTS = false;

					Orbiter_DragChute = true;

					Orbiter_DFIWireTray = false;

					CrewModule_EjectionSeats = false;
					break;
			}
			return;
		}

		void Orbiter_Update_OV_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultOVTextures( mission.OV.Name );
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			Orbiter_Default_Texture_src = texlist;
			return;
		}

		void Orbiter_Update_LOMS_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultLOMSTextures();
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			Orbiter_LOMS_Default_Texture_src = texlist;
			return;
		}

		void Orbiter_Update_ROMS_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultROMSTextures();
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			Orbiter_ROMS_Default_Texture_src = texlist;
			return;
		}

		/// <summary>
		/// List of OV options.
		/// </summary>
		public static string[] Orbiter_Vehicle_src{ get; } = { Defs.strColumbia, Defs.strChallenger, Defs.strDiscovery, Defs.strAtlantis, Defs.strEndeavour };

		/// <summary>
		/// Selected OV.
		/// </summary>
		public string Orbiter_Vehicle
		{
			get { return mission.OV.Name; }
			set
			{
				mission.OV.Name = value;

				// update OV texture list
				Orbiter_Update_OV_Texture();
				Orbiter_Default_Texture = Orbiter_Default_Texture_src[0];

				// enable/disable features
				Orbiter_Update_Enables();
				Orbiter_Update_Features();
				OnPropertyChanged( "Orbiter_Vehicle" );
			}
		}

		/// <summary>
		/// Is the SILTS pod installed
		/// </summary>
		public bool Orbiter_SILTS
		{
			get { return mission.OV.SILTS; }
			set
			{
				mission.OV.SILTS = value;
				OnPropertyChanged( "Orbiter_SILTS" );
			}
		}

		/// <summary>
		/// Is the SILTS pod option enabled
		/// </summary>
		private bool orbiter_silts_ena;
		public bool Orbiter_SILTS_ena
		{
			get { return orbiter_silts_ena; }
			set
			{
				orbiter_silts_ena = value;
				OnPropertyChanged( "Orbiter_SILTS_ena" );
			}
		}

		/// <summary>
		/// Are the forward bulkhead and docking lights installed
		/// </summary>
		public bool Orbiter_FwdBulkDockLights
		{
			get { return mission.OV.FwdBulkDockLights; }
			set
			{
				mission.OV.FwdBulkDockLights = value;
				OnPropertyChanged( "Orbiter_FwdBulkDockLights" );
			}
		}

		/// <summary>
		/// Is the forward bulkhead and docking lights option enabled
		/// </summary>
		private bool orbiter_fwdbulkdocklights_ena;
		public bool Orbiter_FwdBulkDockLights_ena
		{
			get { return orbiter_fwdbulkdocklights_ena; }
			set
			{
				orbiter_fwdbulkdocklights_ena = value;
				OnPropertyChanged( "Orbiter_FwdBulkDockLights_ena" );
			}
		}

		/// <summary>
		/// Is the Drag Chute installed
		/// </summary>
		public bool Orbiter_DragChute
		{
			get { return mission.OV.DragChute; }
			set
			{
				mission.OV.DragChute = value;
				OnPropertyChanged( "Orbiter_DragChute" );
			}
		}

		/// <summary>
		/// Is the Drag Chute option enabled
		/// </summary>
		private bool orbiter_dragchute_ena;
		public bool Orbiter_DragChute_ena
		{
			get { return orbiter_dragchute_ena; }
			set
			{
				orbiter_dragchute_ena = value;
				OnPropertyChanged( "Orbiter_DragChute_ena" );
			}
		}

		/// <summary>
		/// Is the Ku-band Antenna installed
		/// </summary>
		public bool Orbiter_KubandAntenna
		{
			get { return mission.OV.KubandAntenna; }
			set
			{
				mission.OV.KubandAntenna = value;
				OnPropertyChanged( "Orbiter_KubandAntenna" );
			}
		}

		/// <summary>
		/// Is the Payload Bay Liner installed
		/// </summary>
		public bool Orbiter_PLBLiner
		{
			get { return mission.OV.PLBLiner; }
			set
			{
				mission.OV.PLBLiner = value;
				OnPropertyChanged( "Orbiter_PLBLiner" );
			}
		}

		/// <summary>
		/// Is the DFI Wire Tray installed
		/// </summary>
		public bool Orbiter_DFIWireTray
		{
			get { return mission.OV.DFIWireTray; }
			set
			{
				mission.OV.DFIWireTray = value;
				OnPropertyChanged( "Orbiter_DFIWireTray" );
			}
		}

		/// <summary>
		/// Is the DFI Wire Tray installed option enabled
		/// </summary>
		private bool orbiter_dfiwiretray_ena;
		public bool Orbiter_DFIWireTray_ena
		{
			get { return orbiter_dfiwiretray_ena; }
			set
			{
				orbiter_dfiwiretray_ena = value;
				OnPropertyChanged( "Orbiter_DFIWireTray_ena" );
			}
		}

		/// <summary>
		/// Are the Vent Doors 4 and 7 installed
		/// </summary>
		public bool Orbiter_VentDoors4and7
		{
			get { return mission.OV.VentDoors4and7; }
			set
			{
				mission.OV.VentDoors4and7 = value;
				OnPropertyChanged( "Orbiter_VentDoors4and7" );
			}
		}

		/// <summary>
		/// Are the Vent Doors 4 and 7 installed enabled
		/// </summary>
		private bool orbiter_ventdoors4and7_ena;
		public bool Orbiter_VentDoors4and7_ena
		{
			get { return orbiter_ventdoors4and7_ena; }
			set
			{
				orbiter_ventdoors4and7_ena = value;
				OnPropertyChanged( "Orbiter_VentDoors4and7_ena" );
			}
		}

		/// <summary>
		/// The name of the OV texture
		/// </summary>
		public string Orbiter_Texture
		{
			get { return mission.OV.Texture; }
			set
			{
				mission.OV.Texture = value;
				OnPropertyChanged( "Orbiter_Texture" );
			}
		}

		/// <summary>
		/// Is OV texture field enabled
		/// </summary>
		private bool orbiter_texture_ena;
		public bool Orbiter_Texture_ena
		{
			get { return orbiter_texture_ena; }
			set
			{
				orbiter_texture_ena = value;
				OnPropertyChanged( "Orbiter_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default OV textures
		/// </summary>
		private List<Defs.TEX_INFO> orbiter_default_texture_src;
		public List<Defs.TEX_INFO> Orbiter_Default_Texture_src
		{
			get { return orbiter_default_texture_src; }
			set
			{
				orbiter_default_texture_src = value;
				OnPropertyChanged( "Orbiter_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default OV texture
		/// </summary>
		private Defs.TEX_INFO orbiter_default_texture;
		public Defs.TEX_INFO Orbiter_Default_Texture
		{
			get { return orbiter_default_texture; }
			set
			{
				if (value == null) return;

				orbiter_default_texture = value;

				if (value.File == "")
				{
					Orbiter_Texture_ena = true;
				}
				else
				{
					Orbiter_Texture_ena = false;
					Orbiter_Texture = value.File;
				}
				OnPropertyChanged( "Orbiter_Default_Texture" );
			}
		}

		/// <summary>
		/// The name of the Left OMS texture
		/// </summary>
		public string Orbiter_LOMS_Texture
		{
			get { return mission.OV.LOMStex; }
			set
			{
				mission.OV.LOMStex = value;
				OnPropertyChanged( "Orbiter_LOMS_Texture" );
			}
		}

		/// <summary>
		/// Is Left OMS texture field enabled
		/// </summary>
		private bool orbiter_loms_texture_ena;
		public bool Orbiter_LOMS_Texture_ena
		{
			get { return orbiter_loms_texture_ena; }
			set
			{
				orbiter_loms_texture_ena = value;
				OnPropertyChanged( "Orbiter_LOMS_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default Left OMS textures
		/// </summary>
		private List<Defs.TEX_INFO> orbiter_loms_default_texture_src;
		public List<Defs.TEX_INFO> Orbiter_LOMS_Default_Texture_src
		{
			get { return orbiter_loms_default_texture_src; }
			set
			{
				orbiter_loms_default_texture_src = value;
				OnPropertyChanged( "Orbiter_LOMS_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default Left OMS texture
		/// </summary>
		private Defs.TEX_INFO orbiter_loms_default_texture;
		public Defs.TEX_INFO Orbiter_LOMS_Default_Texture
		{
			get { return orbiter_loms_default_texture; }
			set
			{
				if (value == null) return;

				orbiter_loms_default_texture = value;

				if (value.File == "")
				{
					Orbiter_LOMS_Texture_ena = true;
				}
				else
				{
					Orbiter_LOMS_Texture_ena = false;
					Orbiter_LOMS_Texture = value.File;
				}
				OnPropertyChanged( "Orbiter_LOMS_Default_Texture" );
			}
		}

		/// <summary>
		/// The name of the Right OMS texture
		/// </summary>
		public string Orbiter_ROMS_Texture
		{
			get { return mission.OV.ROMStex; }
			set
			{
				mission.OV.ROMStex = value;
				OnPropertyChanged( "Orbiter_ROMS_Texture" );
			}
		}

		/// <summary>
		/// Is Right OMS texture field enabled
		/// </summary>
		private bool orbiter_roms_texture_ena;
		public bool Orbiter_ROMS_Texture_ena
		{
			get { return orbiter_roms_texture_ena; }
			set
			{
				orbiter_roms_texture_ena = value;
				OnPropertyChanged( "Orbiter_ROMS_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default Right OMS textures
		/// </summary>
		private List<Defs.TEX_INFO> orbiter_roms_default_texture_src;
		public List<Defs.TEX_INFO> Orbiter_ROMS_Default_Texture_src
		{
			get { return orbiter_roms_default_texture_src; }
			set
			{
				orbiter_roms_default_texture_src = value;
				OnPropertyChanged( "Orbiter_ROMS_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default Right OMS texture
		/// </summary>
		private Defs.TEX_INFO orbiter_roms_default_texture;
		public Defs.TEX_INFO Orbiter_ROMS_Default_Texture
		{
			get { return orbiter_roms_default_texture; }
			set
			{
				if (value == null) return;

				orbiter_roms_default_texture = value;

				if (value.File == "")
				{
					Orbiter_ROMS_Texture_ena = true;
				}
				else
				{
					Orbiter_ROMS_Texture_ena = false;
					Orbiter_ROMS_Texture = value.File;
				}
				OnPropertyChanged( "Orbiter_ROMS_Default_Texture" );
			}
		}

		/// <summary>
		/// Is the External Airlock / ODS Kit installed
		/// </summary>
		private bool orbiter_extal_ods_kit_ena;
		public bool Orbiter_ExtAL_ODS_Kit_ena
		{
			get { return orbiter_extal_ods_kit_ena; }
			set
			{
				orbiter_extal_ods_kit_ena = value;
				OnPropertyChanged( "Orbiter_ExtAL_ODS_Kit_ena" );
			}
		}

		/// <summary>
		/// Is the External Airlock / ODS Kit installed
		/// </summary>
		public bool Orbiter_ExtAL_ODS_Kit
		{
			get { return mission.OV.ExtAL_ODS_Kit; }
			set
			{
				mission.OV.ExtAL_ODS_Kit = value;
				if (value == false)
				{
					Orbiter_ODS = false;
					Orbiter_Airlock = Defs.strInternal;
				}
				OnPropertyChanged( "Orbiter_ExtAL_ODS_Kit" );
			}
		}

		/// <summary>
		/// Is the ODS installed
		/// </summary>
		public bool Orbiter_ODS
		{
			get { return mission.OV.ODS; }
			set
			{
				mission.OV.ODS = value;
				OnPropertyChanged( "Orbiter_ODS" );
			}
		}

		/// <summary>
		/// List of TAA position options, without External Airlock.
		/// </summary>
		public static string[] Orbiter_TAA_noExtAL_src{ get; } = { Defs.strNone, Defs.strForward };

		/// <summary>
		/// List of TAA position options, with External Airlock.
		/// </summary>
		public static string[] Orbiter_TAA_ExtAL_src{ get; } = { Defs.strNone, Defs.strForward, Defs.strAft };

		/// <summary>
		/// List of TAA position options.
		/// </summary>
		private string[] orbiter_taa_src;
		public string[] Orbiter_TAA_src
		{
			get { return orbiter_taa_src; }
			set
			{
				orbiter_taa_src = value;
				OnPropertyChanged( "Orbiter_TAA_src" );
			}
		}

		/// <summary>
		/// Is the TAA installed and where
		/// </summary>
		public string Orbiter_TAA
		{
			get { return mission.OV.TAA; }
			set
			{
				mission.OV.TAA = value;
				OnPropertyChanged( "Orbiter_TAA" );
			}
		}

		/// <summary>
		/// List of Airlock options.
		/// </summary>
		public static string[] Orbiter_Airlock_src{ get; } = { Defs.strInternal, Defs.strExternal };

		/// <summary>
		/// Where is the Airlock installed
		/// </summary>
		public string Orbiter_Airlock
		{
			get { return mission.OV.Airlock; }
			set
			{
				mission.OV.Airlock = value;
				if (value == Defs.strExternal)
				{
					Orbiter_TAA_src = Orbiter_TAA_ExtAL_src;
				}
				else
				{
					Orbiter_TAA_src = Orbiter_TAA_noExtAL_src;
					Orbiter_TAA = Defs.strNone;
				}
				OnPropertyChanged( "Orbiter_Airlock" );
			}
		}

		/// <summary>
		/// Is the PLB CCTV Camera A installed
		/// </summary>
		public bool Orbiter_CCTV_A
		{
			get { return mission.OV.PLB_Cameras.Installed[0]; }
			set
			{
				mission.OV.PLB_Cameras.Installed[0] = value;
				OnPropertyChanged( "Orbiter_CCTV_A" );
			}
		}

		/// <summary>
		/// Is the PLB CCTV Camera B installed
		/// </summary>
		public bool Orbiter_CCTV_B
		{
			get { return mission.OV.PLB_Cameras.Installed[1]; }
			set
			{
				mission.OV.PLB_Cameras.Installed[1] = value;
				OnPropertyChanged( "Orbiter_CCTV_B" );
			}
		}

		/// <summary>
		/// Is the PLB CCTV Camera C installed
		/// </summary>
		public bool Orbiter_CCTV_C
		{
			get { return mission.OV.PLB_Cameras.Installed[2]; }
			set
			{
				mission.OV.PLB_Cameras.Installed[2] = value;
				OnPropertyChanged( "Orbiter_CCTV_C" );
			}
		}

		/// <summary>
		/// Is the PLB CCTV Camera D installed
		/// </summary>
		public bool Orbiter_CCTV_D
		{
			get { return mission.OV.PLB_Cameras.Installed[3]; }
			set
			{
				mission.OV.PLB_Cameras.Installed[3] = value;
				OnPropertyChanged( "Orbiter_CCTV_D" );
			}
		}

		/// <summary>
		/// Is the PLB CCTV Keel Camera installed
		/// </summary>
		public bool Orbiter_CCTV_Keel
		{
			get { return mission.OV.PLB_Cameras.Keel_Installed[0]; }
			set
			{
				mission.OV.PLB_Cameras.Keel_Installed[0] = value;
				OnPropertyChanged( "Orbiter_CCTV_Keel" );
			}
		}

		/// <summary>
		/// PLID list for PLB CCTV Keel Camera
		/// </summary>
		private List<string> orbiter_cctv_keel_plid_src;
		public List<string> Orbiter_CCTV_Keel_PLID_src
		{
			get { return orbiter_cctv_keel_plid_src; }
			set
			{
				orbiter_cctv_keel_plid_src = value;
				OnPropertyChanged( "Orbiter_CCTV_Keel_PLID_src" );
			}
		}

		/// <summary>
		/// Selected PLID for PLB CCTV Keel Camera
		/// </summary>
		public int Orbiter_CCTV_Keel_PLID
		{
			get
			{
				int i = Array.FindIndex( Defs.KEEL_CAMERA, item => item == mission.OV.PLB_Cameras.Keel_Cameras[0] );
				if (i < 0) i = 0;
				return i;
			}
			set
			{
				mission.OV.PLB_Cameras.Keel_Cameras[0] = Defs.KEEL_CAMERA[value];
				OnPropertyChanged( "Orbiter_CCTV_Keel_PLID" );
			}
		}

		public ICommand Orbiter_EditPLBCameraCommand{ get; private set; }
		void EditPLBCameraCommand( object parameter )
		{
			try
			{
				EditPLBCameraViewModel plbcctv = new EditPLBCameraViewModel( mission.OV.PLB_Cameras, (string)parameter );

				EditPLBCamera cctv = new EditPLBCamera( plbcctv );
				cctv.Owner = Application.Current.MainWindow;
				cctv.ShowDialog();
			}
			catch (Exception)
			{
			}
			return;
		}

		/// <summary>
		/// Is the Port RMS installed?
		/// </summary>
		public bool Orbiter_RMSport
		{
			get { return mission.OV.PortLongeronSill == LongeronSillHardware_Type.RMS; }
			set
			{
				if (value) mission.OV.PortLongeronSill = LongeronSillHardware_Type.RMS;
				else mission.OV.PortLongeronSill = LongeronSillHardware_Type.None;
				UpdatePayloadTypeList();
				OnPropertyChanged( "Orbiter_RMSport" );
			}
		}

		/// <summary>
		/// Is the Starboard RMS installed?
		/// </summary>
		public bool Orbiter_RMSstbd
		{
			get { return mission.OV.StbdLongeronSill == LongeronSillHardware_Type.RMS; }
			set
			{
				if (value) mission.OV.StbdLongeronSill = LongeronSillHardware_Type.RMS;
				else mission.OV.StbdLongeronSill = LongeronSillHardware_Type.None;
				UpdatePayloadTypeList();
				OnPropertyChanged( "Orbiter_RMSstbd" );
			}
		}

		/// <summary>
		/// Is the Port RMS option enabled?
		/// </summary>
		public bool Orbiter_RMSport_ena
		{
			get { return (mission.OV.PortLongeronSill == LongeronSillHardware_Type.None) || (mission.OV.PortLongeronSill == LongeronSillHardware_Type.RMS); }
		}

		/// <summary>
		/// Is the Starboard RMS option enabled?
		/// </summary>
		public bool Orbiter_RMSstbd_ena
		{
			get { return (mission.OV.StbdLongeronSill == LongeronSillHardware_Type.None) || (mission.OV.StbdLongeronSill == LongeronSillHardware_Type.RMS); }
		}

		public ICommand Orbiter_EditRMSportCommand{ get; private set; }
		void EditRMSportCommand()
		{
			EditRMSViewModel rmsvm = new EditRMSViewModel( mission.OV.Port_RMS );
			EditRMS rms = new EditRMS( rmsvm );
			rms.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			rms.ShowDialog();
			return;
		}

		public ICommand Orbiter_EditRMSstbdCommand{ get; private set; }
		void EditRMSstbdCommand()
		{
			EditRMSViewModel rmsvm = new EditRMSViewModel( mission.OV.Stbd_RMS );
			EditRMS rms = new EditRMS( rmsvm );
			rms.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			rms.ShowDialog();
			return;
		}



		/// CREW MODULE tab
		/// <summary>
		/// List of Crew size options.
		/// </summary>
		public static int[] CrewModule_Crew_src{ get; } = new int[] { 2, 3, 4, 5, 6, 7 };

		/// <summary>
		/// Number of crew members
		/// </summary>
		public int CrewModule_Crew
		{
			get { return mission.OV.Crew; }
			set
			{
				mission.OV.Crew = value;
				OnPropertyChanged( "CrewModule_Crew" );
			}
		}

		/// <summary>
		/// List of Galley options.
		/// </summary>
		public static string[] CrewModule_Galley_src{ get; } = { Defs.strNone, Defs.strOriginal, Defs.strSORG };

		/// <summary>
		/// Type of Galley installed
		/// </summary>
		public string CrewModule_Galley
		{
			get { return mission.OV.Galley; }
			set
			{
				mission.OV.Galley = value;
				OnPropertyChanged( "CrewModule_Galley" );
			}
		}

		/// <summary>
		/// List of Sleep Stations options.
		/// </summary>
		public static string[] CrewModule_SleepStations_src{ get; } = { Defs.strNone, Defs.strThreeTier, Defs.strFourTier };

		/// <summary>
		/// Type of Sleep Stations installed
		/// </summary>
		public string CrewModule_SleepStations
		{
			get { return mission.OV.SleepStations; }
			set
			{
				mission.OV.SleepStations = value;
				OnPropertyChanged( "CrewModule_SleepStations" );
			}
		}

		/// <summary>
		/// Are Ejection Seats installed
		/// </summary>
		public bool CrewModule_EjectionSeats
		{
			get { return mission.OV.EjectionSeats; }
			set
			{
				mission.OV.EjectionSeats = value;
				OnPropertyChanged( "CrewModule_EjectionSeats" );
			}
		}

		/// <summary>
		/// Is the Ejection Seats option enabled
		/// </summary>
		private bool crewmodule_ejectionseats_ena;
		public bool CrewModule_EjectionSeats_ena
		{
			get { return crewmodule_ejectionseats_ena; }
			set
			{
				crewmodule_ejectionseats_ena = value;
				OnPropertyChanged( "CrewModule_EjectionSeats_ena" );
			}
		}

		/// <summary>
		/// Is Crew Escape Hardware installed
		/// </summary>
		public bool CrewModule_CrewEscapeHardware
		{
			get { return mission.OV.CrewEscapeHardware; }
			set
			{
				mission.OV.CrewEscapeHardware = value;
				OnPropertyChanged( "CrewModule_CrewEscapeHardware" );
			}
		}

		/// <summary>
		/// List of Flight Deck options.
		/// </summary>
		public static string[] CrewModule_FlightDeck_src{ get; } = { Defs.strMCDS, Defs.strMEDS };

		/// <summary>
		/// Type of Flight Deck
		/// </summary>
		public string CrewModule_FlightDeck
		{
			get { return mission.OV.FlightDeck; }
			set
			{
				mission.OV.FlightDeck = value;
				OnPropertyChanged( "CrewModule_FlightDeck" );
			}
		}



		/// LAUNCH tab
		public ICommand Launch_CalcAscentCommand{ get; private set; }
		void CalcAscentCommand()
		{
			Launch_ResultString = "calculating...";

			OrbitTgtCalcOptions opt = new OrbitTgtCalcOptions
			{
				H_Insertion = Launch_MECOAltitude * Defs.NM2KM * 1000.0,
				H_OMS1 = Launch_OMS1MECOTargetAltitude * Defs.NM2KM * 1000.0,
				H_OMS2 = Launch_OMS2TargetAltitude * Defs.NM2KM * 1000.0,
				Inclination = Launch_MECOInclination * Defs.RAD,
				InsertionMode = Launch_DI
			};

			OrbitTgtCalc orbittgtcalc = new OrbitTgtCalc();
			OrbitTgtCalcOutput res = orbittgtcalc.Calculate( opt );

			Launch_MECOAltitude2 = res.TGTMECOaltitude;
			Launch_MECOVelocity = res.TGTMECOvel * Defs.MPS2FPS;
			Launch_MECOFPA = res.TGTMECOfpa;
			//Launch_MECOInclination = res.TGTMECOinclination;

			Launch_OMS1DTIG = res.oms1.DTIG;
			Launch_OMS1HTGT = res.oms1.HTGT * Defs.MPS2FPS;
			Launch_OMS1THETA = res.oms1.THETA;
			Launch_OMS1C1 = res.oms1.C1 * Defs.MPS2FPS;
			Launch_OMS1C2 = res.oms1.C2;

			Launch_OMS2DTIG = res.oms2.DTIG;
			Launch_OMS2HTGT = res.oms2.HTGT * Defs.MPS2FPS;
			Launch_OMS2THETA = res.oms2.THETA;
			Launch_OMS2C1 = res.oms2.C1 * Defs.MPS2FPS;
			Launch_OMS2C2 = res.oms2.C2;



			Launch_ResultString = string.Format(">> MECO <<\n" +
				"Inclination: {0:f2}º\n" +
				"Altitude: {1:f0}ft ({2:f0}km)\n" +
				"Velocity: {3:f0}fps ({4:f0}m/s)\n" +
				"Flight Path Angle: {5:f4}º\n" +
				"Ap/Pe: {6:f0}x{7:f0}NM ({8:f0}x{9:f0}Km)\n",
				Launch_MECOInclination,
				res.TGTMECOaltitude * Defs.MPS2FPS, res.TGTMECOaltitude * 0.001,
				res.TGTMECOvel * Defs.MPS2FPS, res.TGTMECOvel,
				res.TGTMECOfpa,
				res.TGTMECOap / (Defs.NM2KM * 1000.0), res.TGTMECOpe / (Defs.NM2KM * 1000.0), res.TGTMECOap * 0.001, res.TGTMECOpe * 0.001 );

			if (!Launch_DI)
			{
				// SI
				Launch_ResultString += string.Format("\n>> OMS-1 <<\n" +
					"TIG: {0:D2}:{1:D2}\n" +
					"dV: {2:f1}fps ({3:f1}m/s)\n" +
					"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
					(int)res.TGTOMS1tig[0], (int)res.TGTOMS1tig[1],
					res.TGTOMS1dv * Defs.MPS2FPS, res.TGTOMS1dv,
					res.TGTOMS1ap / (Defs.NM2KM * 1000.0), res.TGTOMS1pe / (Defs.NM2KM * 1000.0), res.TGTOMS1ap * 0.001, res.TGTOMS1pe * 0.001 );
			}
			else
			{
				// DI
				Launch_ResultString += string.Format("\n>> OMS-1 <<\n(not performed)\n" +
					"Ap/Pe: {0:f0}x{1:f0}NM ({2:f0}x{3:f0}Km)\n",
					res.TGTOMS1ap / (Defs.NM2KM * 1000.0), res.TGTOMS1pe / (Defs.NM2KM * 1000.0), res.TGTOMS1ap * 0.001, res.TGTOMS1pe * 0.001 );
			}

			Launch_ResultString += string.Format("\n>> OMS-2 <<\n" +
				"TIG: {0:D2}:{1:D2}\n" +
				"dV: {2:f1}fps ({3:f1}m/s)\n" +
				"Ap/Pe: {4:f0}x{5:f0}NM ({6:f0}x{7:f0}Km)\n",
				(int)res.TGTOMS2tig[0], (int)res.TGTOMS2tig[1],
				res.TGTOMS2dv * Defs.MPS2FPS, res.TGTOMS2dv,
				res.TGTOMS2ap / (Defs.NM2KM * 1000.0), res.TGTOMS2pe / (Defs.NM2KM * 1000.0), res.TGTOMS2ap * 0.001, res.TGTOMS2pe * 0.001 );

			// enable Save button
			Launch_CalcDone = true;
			((RelayCommand)Launch_AscentSaveCommand).NotifyCanExecuteChanged();
			return;
		}

		public ICommand Launch_AscentSaveCommand{ get; private set; }
		void AscentSaveCommand()
		{
			// save legacy MECO target
			MECO_Inc = Launch_MECOInclination;
			MECO_Alt = Launch_MECOAltitude2;
			MECO_Vel = Launch_MECOVelocity / Defs.MPS2FPS;
			MECO_FPA = Launch_MECOFPA;

			// set I-LOADs for roll to heads up and OMS-1/2 targets
			foreach (Mission_ILOAD iload in ILOAD_List)
			{
				if (iload.ID == "PHI_2STG")
				{
					iload.Val = Launch_RTHU ? "0.0" : "3.141593";
				}
				else if (iload.ID == "TVR_ROLL")
				{
					iload.Val = Launch_RTHU ? "0" : "180";
				}
				else if (iload.ID == "DTIG_OMS")
				{
					iload.Val = string.Format("{0:f1} {1:f1}", Launch_OMS1DTIG, Launch_OMS2DTIG );
				}
				else if (iload.ID == "HTGT_OMS")
				{
					iload.Val = string.Format("{0:f1} {1:f1}", Launch_OMS1HTGT, Launch_OMS2HTGT );
				}
				else if (iload.ID == "THETA_OMS")
				{
					iload.Val = string.Format("{0:f6} {1:f6}", Launch_OMS1THETA, Launch_OMS2THETA );
				}
				else if (iload.ID == "C1_OMS")
				{
					iload.Val = string.Format("{0:f0} {1:f0}", Launch_OMS1C1, Launch_OMS2C1 );
				}
				else if (iload.ID == "C2_OMS")
				{
					iload.Val = string.Format("{0:f4} {1:f4}", Launch_OMS1C2, Launch_OMS2C2 );
				}
			}
			return;
		}

		private bool AscentSaveCommandEnabled()
		{
			return Launch_CalcDone;
		}

		private bool Launch_CalcDone = false;

		/// <summary>
		/// List of Site options.
		/// </summary>
		public static string[] Launch_Site_src{ get; } = { Defs.strKSC, Defs.strVAFB };
		/// <summary>
		/// List of Pad options (KSC only).
		/// </summary>
		public static string[] Launch_PadKSC_src{ get; } = { Defs.strLC39A, Defs.strLC39B };
		/// <summary>
		/// List of Pad options (VAFB only).
		/// </summary>
		public static string[] Launch_PadVAFB_src{ get; } = { Defs.strSLC6 };
		/// <summary>
		/// List of PadType options (KSC only).
		/// </summary>
		public static string[] Launch_PadType_src{ get; } = { Defs.str1981, Defs.str1982, Defs.str1983, Defs.str1985, Defs.str1986, Defs.str1988, Defs.str1995, Defs.str2007 };
		/// <summary>
		/// List of MLP options.
		/// </summary>
		public static string[] Launch_MLP_src{ get; } = { Defs.strMLP1, Defs.strMLP2, Defs.strMLP3 };

		/// <summary>
		/// List of Pad options.
		/// </summary>
		private string[] launch_pad_src;
		public string[] Launch_Pad_src
		{
			get { return launch_pad_src; }
			set
			{
				launch_pad_src = value;
				OnPropertyChanged( "Launch_Pad_src" );
			}
		}

		/// <summary>
		/// Defines enabled state of controls for Pad, PadType and MLP editing.
		/// </summary>
		private bool padmlp_ena;
		public bool Launch_PadMLP_ena
		{
			get { return padmlp_ena; }
			set
			{
				padmlp_ena = value;
				OnPropertyChanged( "Launch_PadMLP_ena" );
			}
		}

		/// <summary>
		/// Exposes LaunchSite property of Mission, and updates displayed information.
		/// </summary>
		public string Launch_Site
		{
			get { return mission.LaunchSite; }
			set
			{
				mission.LaunchSite = value;
				if (value == Defs.strKSC)
				{
					// KSC
					Launch_PadMLP_ena = true;
					Launch_Pad_src = Launch_PadKSC_src;
					Launch_Pad = Defs.strLC39A;
					Launch_PadType = Defs.str1981;
					Launch_MLP = Defs.strMLP1;
				}
				else
				{
					// VAFB
					Launch_PadMLP_ena = false;
					Launch_Pad_src = Launch_PadVAFB_src;
					Launch_Pad = Defs.strSLC6;
					Launch_PadType = "";
					Launch_MLP = "";
				}
				OnPropertyChanged( "Launch_Site" );
			}
		}

		/// <summary>
		/// Exposes LaunchPad property of Mission.
		/// </summary>
		public string Launch_Pad
		{
			get { return mission.LaunchPad; }
			set
			{
				mission.LaunchPad = value;
				OnPropertyChanged( "Launch_Pad" );
			}
		}

		/// <summary>
		/// Exposes LaunchPadType property of Mission.
		/// </summary>
		public string Launch_PadType
		{
			get { return mission.LaunchPadType; }
			set
			{
				mission.LaunchPadType = value;
				OnPropertyChanged( "Launch_PadType" );
			}
		}

		/// <summary>
		/// Exposes MLP property of Mission.
		/// </summary>
		public string Launch_MLP
		{
			get { return mission.MLP; }
			set
			{
				mission.MLP = value;
				OnPropertyChanged( "Launch_MLP" );
			}
		}


		/// <summary>
		/// Direct Insertion if true, Standard Insertion if false
		/// </summary>
		private bool launch_di;
		public bool Launch_DI
		{
			get { return launch_di; }
			set
			{
				launch_di = value;

				if (launch_di)
				OnPropertyChanged( "Launch_DI" );
			}
		}

		/// <summary>
		/// MECO inclination [deg]
		/// </summary>
		private double launch_mecoinclination;
		public double Launch_MECOInclination
		{
			get { return launch_mecoinclination; }
			set
			{
				launch_mecoinclination = value;
				OnPropertyChanged( "Launch_MECOInclination" );
			}
		}

		/// <summary>
		/// MECO altitude, referenced to STS Earth [NM]
		/// </summary>
		public static int[] Launch_cmbATMECOAlt_src{ get; } = { 60, 57, 52 };

		/// <summary>
		/// MECO altitude, referenced to STS Earth [NM]
		/// </summary>
		private int launch_mecoaltitude;
		public int Launch_MECOAltitude
		{
			get { return launch_mecoaltitude; }
			set
			{
				launch_mecoaltitude = value;
				OnPropertyChanged( "Launch_MECOAltitude" );
			}
		}

		/// <summary>
		/// OMS-1 (SI) / MECO (DI) target altitude [NM]
		/// </summary>
		private double launch_oms1mecotargetaltitude;
		public double Launch_OMS1MECOTargetAltitude
		{
			get { return launch_oms1mecotargetaltitude; }
			set
			{
				launch_oms1mecotargetaltitude = value;
				OnPropertyChanged( "Launch_OMS1MECOTargetAltitude" );
			}
		}

		/// <summary>
		/// OMS-2 target altitude [NM]
		/// </summary>
		private double launch_oms2targetaltitude;
		public double Launch_OMS2TargetAltitude
		{
			get { return launch_oms2targetaltitude; }
			set
			{
				launch_oms2targetaltitude = value;
				OnPropertyChanged( "Launch_OMS2TargetAltitude" );
			}
		}

		/// <summary>
		/// If true, roll to heads up is performed.
		/// </summary>
		private bool launch_rthu;
		public bool Launch_RTHU
		{
			get { return launch_rthu; }
			set
			{
				launch_rthu = value;
				OnPropertyChanged( "Launch_RTHU" );
			}
		}



		/// <summary>
		/// Formatted string containg several calculated parameters.
		/// </summary>
		private string launch_resultstring;
		public string Launch_ResultString
		{
			get { return launch_resultstring; }
			set
			{
				launch_resultstring = value;
				OnPropertyChanged( "Launch_ResultString" );
			}
		}

		/// <summary>
		/// MECO altitude, referenced to Orbiter Earth [m]
		/// </summary>
		private double launch_mecoaltitude2;
		public double Launch_MECOAltitude2
		{
			get { return launch_mecoaltitude2; }
			set
			{
				launch_mecoaltitude2 = value;
				OnPropertyChanged( "Launch_MECOAltitude2" );
			}
		}

		/// <summary>
		/// MECO velocity [fps]
		/// </summary>
		private double launch_mecovelocity;
		public double Launch_MECOVelocity
		{
			get { return launch_mecovelocity; }
			set
			{
				launch_mecovelocity = value;
				OnPropertyChanged( "Launch_MECOVelocity" );
			}
		}

		/// <summary>
		/// MECO FPA [deg]
		/// </summary>
		private double launch_mecofpa;
		public double Launch_MECOFPA
		{
			get { return launch_mecofpa; }
			set
			{
				launch_mecofpa = value;
				OnPropertyChanged( "Launch_MECOFPA" );
			}
		}

		/// <summary>
		/// Time between ET separation and OMS-1 [s]
		/// </summary>
		private double launch_oms1dtig;
		public double Launch_OMS1DTIG
		{
			get { return launch_oms1dtig; }
			set
			{
				launch_oms1dtig = value;
				OnPropertyChanged( "Launch_OMS1DTIG" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 HTGT [ft]
		/// </summary>
		private double launch_oms1htgt;
		public double Launch_OMS1HTGT
		{
			get { return launch_oms1htgt; }
			set
			{
				launch_oms1htgt = value;
				OnPropertyChanged( "Launch_OMS1HTGT" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 Theta [rad]
		/// </summary>
		private double launch_oms1theta;
		public double Launch_OMS1THETA
		{
			get { return launch_oms1theta; }
			set
			{
				launch_oms1theta = value;
				OnPropertyChanged( "Launch_OMS1THETA" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 C1 [fps]
		/// </summary>
		private double launch_oms1c1;
		public double Launch_OMS1C1
		{
			get { return launch_oms1c1; }
			set
			{
				launch_oms1c1 = value;
				OnPropertyChanged( "Launch_OMS1C1" );
			}
		}

		/// <summary>
		/// OMS-1 PEG-4 C2 [1]
		/// </summary>
		private double launch_oms1c2;
		public double Launch_OMS1C2
		{
			get { return launch_oms1c1; }
			set
			{
				launch_oms1c2 = value;
				OnPropertyChanged( "Launch_OMS1C2" );
			}
		}

		/// <summary>
		/// Time between ET separation and OMS-2 [s]
		/// </summary>
		private double launch_oms2dtig;
		public double Launch_OMS2DTIG
		{
			get { return launch_oms2dtig; }
			set
			{
				launch_oms2dtig = value;
				OnPropertyChanged( "Launch_OMS2DTIG" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 HTGT [ft]
		/// </summary>
		private double launch_oms2htgt;
		public double Launch_OMS2HTGT
		{
			get { return launch_oms2htgt; }
			set
			{
				launch_oms2htgt = value;
				OnPropertyChanged( "Launch_OMS2HTGT" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 Theta [rad]
		/// </summary>
		private double launch_oms2theta;
		public double Launch_OMS2THETA
		{
			get { return launch_oms2theta; }
			set
			{
				launch_oms2theta = value;
				OnPropertyChanged( "Launch_OMS2THETA" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 C1 [fps]
		/// </summary>
		private double launch_oms2c1;
		public double Launch_OMS2C1
		{
			get { return launch_oms2c1; }
			set
			{
				launch_oms2c1 = value;
				OnPropertyChanged( "Launch_OMS2C1" );
			}
		}

		/// <summary>
		/// OMS-2 PEG-4 C2 [1]
		/// </summary>
		private double launch_oms2c2;
		public double Launch_OMS2C2
		{
			get { return launch_oms2c1; }
			set
			{
				launch_oms2c2 = value;
				OnPropertyChanged( "Launch_OMS2C2" );
			}
		}

		/// <summary>
		/// The date/time at the start of the simulation
		/// </summary>
		public int T0Year
		{
			get { return mission.T0Year; }
			set
			{
				mission.T0Year = value;
				OnPropertyChanged( "T0Year" );
			}
		}
		public int T0Month
		{
			get { return mission.T0Month; }
			set
			{
				mission.T0Month = value;
				OnPropertyChanged( "T0Month" );
			}
		}
		public int T0Day
		{
			get { return mission.T0Day; }
			set
			{
				mission.T0Day = value;
				OnPropertyChanged( "T0Day" );
			}
		}
		public int T0Hour
		{
			get { return mission.T0Hour; }
			set
			{
				mission.T0Hour = value;
				OnPropertyChanged( "T0Hour" );
			}
		}
		public int T0Minute
		{
			get { return mission.T0Minute; }
			set
			{
				mission.T0Minute = value;
				OnPropertyChanged( "T0Minute" );
			}
		}
		public double T0Second
		{
			get { return mission.T0Second; }
			set
			{
				mission.T0Second = value;
				OnPropertyChanged( "T0Second" );
			}
		}

		/// <summary>
		/// MECO target inclination
		/// </summary>
		public double MECO_Inc
		{
			get { return mission.MECO_Inc; }
			set { mission.MECO_Inc = value; OnPropertyChanged( "MECO_Inc" ); }
		}

		/// <summary>
		/// MECO target altitude
		/// </summary>
		public double MECO_Alt
		{
			get { return mission.MECO_Alt; }
			set { mission.MECO_Alt = value; OnPropertyChanged( "MECO_Alt" ); }
		}

		/// <summary>
		/// MECO target velocity
		/// </summary>
		public double MECO_Vel
		{
			get { return mission.MECO_Vel; }
			set { mission.MECO_Vel = value; OnPropertyChanged( "MECO_Vel" ); }
		}

		/// <summary>
		/// MECO target flight path angle
		/// </summary>
		public double MECO_FPA
		{
			get { return mission.MECO_FPA; }
			set { mission.MECO_FPA = value; OnPropertyChanged( "MECO_FPA" ); }
		}


		/// ORBIT tab
		private string GetCurrentOrbitTargetSet()
		{
			string T1 = "";
			string DT = "";
			string EL = "";
			string XOFF = "";
			string YOFF = "";
			string ZOFF = "";
			string LAMB = "";

			foreach (Mission_ILOAD iload in ILOAD_List)
			{
				switch (iload.ID)
				{
					case "T1_ILOAD_ARRAY":
						T1 = iload.Val;
						break;
					case "DT_ILOAD_ARRAY":
						DT = iload.Val;
						break;
					case "EL_ILOAD_ARRAY":
						EL = iload.Val;
						break;
					case "XOFF_ILOAD_ARRAY":
						XOFF = iload.Val;
						break;
					case "YOFF_ILOAD_ARRAY":
						YOFF = iload.Val;
						break;
					case "ZOFF_ILOAD_ARRAY":
						ZOFF = iload.Val;
						break;
					case "LAMB_ILOAD":
						LAMB = iload.Val;
						break;
				}
			}

			// compare with Defs and if equal return corresponding name
			foreach (Defs.ORB_TGT_SET ots in Orbit_OrbTgtSets)
			{
				if (ots.T1 != T1) continue;
				if (ots.DT != DT) continue;
				if (ots.EL != EL) continue;
				if (ots.XOFF != XOFF) continue;
				if (ots.YOFF != YOFF) continue;
				if (ots.ZOFF != ZOFF) continue;
				if (ots.LAMB != LAMB) continue;

				return ots.Name;
			}
			return "(custom targets currently loaded)";
		}

		public ICommand Orbit_LoadTgtSetsCommand{ get; private set; }
		void LoadTgtSetsCommand()
		{
			// set target set in I-Load list
			foreach (Mission_ILOAD iload in ILOAD_List)
			{
				switch (iload.ID)
				{
					case "T1_ILOAD_ARRAY":
						iload.Val = Orbit_SelOrbTgtSet.T1;
						break;
					case "DT_ILOAD_ARRAY":
						iload.Val = Orbit_SelOrbTgtSet.DT;
						break;
					case "EL_ILOAD_ARRAY":
						iload.Val = Orbit_SelOrbTgtSet.EL;
						break;
					case "XOFF_ILOAD_ARRAY":
						iload.Val = Orbit_SelOrbTgtSet.XOFF;
						break;
					case "YOFF_ILOAD_ARRAY":
						iload.Val = Orbit_SelOrbTgtSet.YOFF;
						break;
					case "ZOFF_ILOAD_ARRAY":
						iload.Val = Orbit_SelOrbTgtSet.ZOFF;
						break;
					case "LAMB_ILOAD":
						iload.Val = Orbit_SelOrbTgtSet.LAMB;
						break;
				}
			}
			return;
		}

		private bool LoadTgtSetsCommandEnabled()
		{
			return Orbit_SelOrbTgtSet != null;
		}

		public ICommand Orbit_PickTgtVesselCommand{ get; private set; }
		void PickTgtVesselCommand()
		{
			PickTgtVesselNameViewModel ptvn = new PickTgtVesselNameViewModel( mission );

			PickTgtVesselName picktgtvesselname = new PickTgtVesselName( ptvn );
			picktgtvesselname.Owner = Application.Current.MainWindow;
			picktgtvesselname.ShowDialog();

			if (picktgtvesselname.DialogResult == true) Orbit_SelTgtVessel = ptvn.SelTargetVessel;
			return;
		}

		/// <summary>
		/// List of orbit targeting sets.
		/// </summary>
		private List<Defs.ORB_TGT_SET> orbit_orbtgtsets;
		public List<Defs.ORB_TGT_SET> Orbit_OrbTgtSets
		{
			get
			{
				return orbit_orbtgtsets;
			}
			set
			{
				orbit_orbtgtsets = value;
				OnPropertyChanged( "Orbit_OrbTgtSets" );
			}
		}

		/// <summary>
		/// Selected orbit targeting set.
		/// </summary>
		private Defs.ORB_TGT_SET orbit_selorbtgtset;
		public Defs.ORB_TGT_SET Orbit_SelOrbTgtSet
		{
			get
			{
				return orbit_selorbtgtset;
			}
			set
			{
				orbit_selorbtgtset = value;
				Orbit_SelOrbTgtSetDesc = value.Description;
				// enable button
				((RelayCommand)Orbit_LoadTgtSetsCommand).NotifyCanExecuteChanged();
				OnPropertyChanged( "Orbit_SelOrbTgtSet" );
			}
		}

		/// <summary>
		/// Description of the selected orbit targeting set.
		/// </summary>
		private string orbit_selorbtgtsetdesc;
		public string Orbit_SelOrbTgtSetDesc
		{
			get
			{
				return orbit_selorbtgtsetdesc;
			}
			set
			{
				orbit_selorbtgtsetdesc = value;
				OnPropertyChanged( "Orbit_SelOrbTgtSetDesc" );
			}
		}

		/// <summary>
		/// Name of current mission orbit targeting set.
		/// </summary>
		private string orbit_curorbtgtset;
		public string Orbit_CurOrbTgtSet
		{
			get
			{
				return orbit_curorbtgtset;
			}
			set
			{
				orbit_curorbtgtset = value;
				OnPropertyChanged( "Orbit_CurOrbTgtSet" );
			}
		}

		/// <summary>
		/// Selected target vessel.
		/// </summary>
		public string Orbit_SelTgtVessel
		{
			get
			{
				return mission.OV.TgtVessel;
			}
			set
			{
				mission.OV.TgtVessel = value;
				OnPropertyChanged( "Orbit_SelTgtVessel" );
			}
		}



		/// LANDING tab
		private const string LINE = "+----+----------------------+--------+-------+\n";
		private const string HEADER = "| S  |                      |        |       |\n" +
						"| I  |      LOCATION        |  RWY   |  LG   |\n" +
						"| T  |                      |        |       |\n" +
						"| E  |                      |        |       |\n";

		public string FormatLandingSiteTable( List<Tuple<string,string>> lstable )
		{
			string strls = "";
			if (lstable.Count == 0) return "";// TODO check null?

			strls += LINE + HEADER;
			for (int lsid = 1; lsid <= 45; lsid++)
			{
				string prisite = "";
				string loc = "";
				string lgt = "";
				LandingSite.LandingSiteData ls;
				//// primary rwy ////
				if ((ls = landingsite.FindLandingSite( lstable[lsid - 1].Item1 )) != null)
				{
					loc = ls.sitename;
					prisite = loc;
					lgt = ls.lgt;
				}
				else
				{
					loc = "<ERROR>";
					lgt = "";
				}
				strls += LINE;
				// SITE: len 2
				strls += "| " + lsid.ToString().PadRight( 2 ) + " | ";
				// LOCATION: len 20
				strls += loc.PadRight( 20 ) + " | ";
				// RWY: len 6
				strls += lstable[lsid - 1].Item1.PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";

				//// secondary rwy ////
				if ((ls = landingsite.FindLandingSite( lstable[lsid - 1].Item2 )) != null)
				{
					loc = ls.sitename;
					lgt = ls.lgt;
				}
				else
				{
					loc = "<ERROR>";
					lgt = "";
				}
				// SITE: len 2
				strls += "|    | ";
				// LOCATION: len 20
				if (loc == prisite) loc = "";
				strls += loc.PadRight( 20 ) + " | ";
				// RWY: len 6
				strls += lstable[lsid - 1].Item2.PadRight( 6 ) + " | ";
				// LG: len 5
				strls += lgt.PadLeft( 5 ) + " |\n";
			}
			strls += LINE;
			return strls;
		}

		public string FormatLandingSiteDB( int idx )
		{
			LandingSite.LandingSiteData ls = landingsite.GetLandingSite( idx );

			if (ls == null)
			{
				return "";
			}

			string strls = "Location: " + ls.sitename + "\n" +
				"Runway: " + ls.rwname + "\n";

			if (ls.lgt != "0")
			{
				double lat = Math.Round( double.Parse( ls.lat ) * Defs.DEG, 6 );
				double lon = Math.Round( double.Parse( ls.lon ) * Defs.DEG, 6 );
				strls += "Lat: " + lat + "º   Lon: " + lon + "º\n" +
					"AMSL: " + ls.amsl + "m\n" +
					"Heading: " + ls.hdg + "º\n" +
					"Length: " + ls.lgt + "ft";
			}
			else
			{
				strls += "(runway not implemented)";
			}
			return strls;
		}

		public ICommand Landing_SetDefaultLSTCommand{ get; private set; }
		void SetDefaultLSTCommand()
		{
			mission.OV.LandingSiteTable = Defs.DefaultRunwayTables()[Landing_DefaultLSidx].Item2;

			Landing_LST = FormatLandingSiteTable( mission.OV.LandingSiteTable );
			return;
		}

		private bool SetDefaultLSTCommandEnabled()
		{
			return Landing_DefaultLSidx != -1;
		}

		public ICommand Landing_SetRunwayCommand{ get; private set; }
		void SetRunwayCommand()
		{
			LandingSite.LandingSiteData ls = landingsite.GetLandingSite( Landing_LSDBidx );
			if (ls == null)
			{
				return;
			}
			if ((Landing_ManLSID < 0) || (Landing_ManLSID >= 45))
			{
				return;
			}
			if ((Landing_ManRW != "P") && (Landing_ManRW != "S"))
			{
				return;
			}

			List<Tuple<string,string>> lstable = mission.OV.LandingSiteTable;
			string priRW;
			string secRW;

			if (Landing_ManRW == "P")
			{
				priRW = ls.id;
				secRW = lstable[Landing_ManLSID].Item2;
			}
			else
			{
				priRW = lstable[Landing_ManLSID].Item1;
				secRW = ls.id;
			}

			Tuple<string,string> tp = new Tuple<string,string>( priRW, secRW );
			lstable[Landing_ManLSID] = tp;
			mission.OV.LandingSiteTable = lstable;

			Landing_LST = FormatLandingSiteTable( mission.OV.LandingSiteTable );
			return;
		}

		/// <summary>
		/// Current LST, in formatted version.
		/// </summary>
		private string landing_lst;
		public string Landing_LST
		{
			get
			{
				return landing_lst;
			}
			set
			{
				landing_lst = value;
				OnPropertyChanged( "Landing_LST" );
			}
		}

		/// <summary>
		/// List of runways in landing site database.
		/// Format: "<runway name> <site name>"
		/// </summary>
		private List<string> landing_runways;
		public List<string> Landing_Runways
		{
			get
			{
				return landing_runways;
			}
			set
			{
				landing_runways = value;
				OnPropertyChanged( "Landing_Runways" );
			}
		}

		/// <summary>
		/// Information about the selected runway.
		/// </summary>
		private string landing_runwayinfo;
		public string Landing_RunwayInfo
		{
			get
			{
				return landing_runwayinfo;
			}
			set
			{
				landing_runwayinfo = value;
				OnPropertyChanged( "Landing_RunwayInfo" );
			}
		}

		/// <summary>
		/// Selected index of runway in landing site database, for viewing and manual LST update.
		/// </summary>
		private int landing_lsdbidx;
		public int Landing_LSDBidx
		{
			get
			{
				return landing_lsdbidx;
			}
			set
			{
				landing_lsdbidx = value;
				Landing_RunwayInfo = FormatLandingSiteDB( landing_lsdbidx );// update runway info
				OnPropertyChanged( "Landing_LSDBidx" );
			}
		}

		/// <summary>
		/// List of default LST names.
		/// </summary>
		private List<string> landing_defaultlstablenames;
		public List<string> Landing_DefaultLSTableNames
		{
			get
			{
				return landing_defaultlstablenames;
			}
			set
			{
				landing_defaultlstablenames = value;
				OnPropertyChanged( "Landing_DefaultLSTableNames" );
			}
		}

		/// <summary>
		/// Selected index of default LST.
		/// </summary>
		private int landing_defaultlsidx;
		public int Landing_DefaultLSidx
		{
			get
			{
				return landing_defaultlsidx;
			}
			set
			{
				landing_defaultlsidx = value;
				// enable button
				((RelayCommand)Landing_SetDefaultLSTCommand).NotifyCanExecuteChanged();
				OnPropertyChanged( "Landing_DefaultLSidx" );
			}
		}

		/// <summary>
		/// Selected index of landing site in LST, for manual LST update. [0-44]
		/// </summary>
		private int landing_manlsid;
		public int Landing_ManLSID
		{
			get
			{
				return landing_manlsid;
			}
			set
			{
				landing_manlsid = value;
				OnPropertyChanged( "Landing_ManLSID" );
			}
		}

		/// <summary>
		/// Selected runway end: true = Pri, false = Sec.
		/// </summary>
		private string landing_manrw;
		public string Landing_ManRW
		{
			get
			{
				return landing_manrw;
			}
			set
			{
				landing_manrw = value;
				OnPropertyChanged( "Landing_ManRW" );
			}
		}


		/// SSME tab
		/// <summary>
		/// SSME type list
		/// </summary>
		public static string[] SSME_Type_src{ get; } = { Defs.strFMOF, Defs.strFPL_Phase_I, Defs.strPhase_II, Defs.strBlock_I, Defs.strBlock_II };

		/// <summary>
		/// SSME-1 type
		/// </summary>
		public string SSME_1_Type
		{
			get
			{
				return mission.OV.SSME[0].Type;
			}
			set
			{
				mission.OV.SSME[0].Type = value;
				OnPropertyChanged( "SSME_1_Type" );
			}
		}

		/// <summary>
		/// SSME-1 type
		/// </summary>
		public string SSME_2_Type
		{
			get
			{
				return mission.OV.SSME[1].Type;
			}
			set
			{
				mission.OV.SSME[1].Type = value;
				OnPropertyChanged( "SSME_2_Type" );
			}
		}

		/// <summary>
		/// SSME-1 type
		/// </summary>
		public string SSME_3_Type
		{
			get
			{
				return mission.OV.SSME[2].Type;
			}
			set
			{
				mission.OV.SSME[2].Type = value;
				OnPropertyChanged( "SSME_3_Type" );
			}
		}


		/// CONSUMABLES tab
		public double Consumables_FRCS_Load
		{
			get { return mission.OV.FRCS_Load; }
			set
			{
				mission.OV.FRCS_Load = value;
				OnPropertyChanged( "Consumables_FRCS_Load" );
			}
		}

		public double Consumables_LRCS_Load
		{
			get { return mission.OV.LRCS_Load; }
			set
			{
				mission.OV.LRCS_Load = value;
				OnPropertyChanged( "Consumables_LRCS_Load" );
			}
		}

		public double Consumables_RRCS_Load
		{
			get { return mission.OV.RRCS_Load; }
			set
			{
				mission.OV.RRCS_Load = value;
				OnPropertyChanged( "Consumables_RRCS_Load" );
			}
		}

		public double Consumables_LOMS_Load
		{
			get { return mission.OV.LOMS_Load; }
			set
			{
				mission.OV.LOMS_Load = value;
				OnPropertyChanged( "Consumables_LOMS_Load" );
			}
		}

		public double Consumables_ROMS_Load
		{
			get { return mission.OV.ROMS_Load; }
			set
			{
				mission.OV.ROMS_Load = value;
				OnPropertyChanged( "Consumables_ROMS_Load" );
			}
		}

		public double Consumables_KOMS_Load
		{
			get { return mission.OV.KOMS_Load; }
			set
			{
				mission.OV.KOMS_Load = value;
				OnPropertyChanged( "Consumables_KOMS_Load" );
			}
		}

		public string Consumables_FRCS_Tooltip
		{
			get { return "Max Load: " + Defs.MAXLOAD_FRCS + " lbs\nMin Load: " + Defs.MINLOAD_FRCS + " lbs"; }
		}

		public string Consumables_ARCS_Tooltip
		{
			get { return "Max Load: " + Defs.MAXLOAD_ARCS + " lbs\nMin Load: " + Defs.MINLOAD_ARCS + " lbs"; }
		}

		public string Consumables_OMS_Tooltip
		{
			get { return "Max Load: " + Defs.MAXLOAD_OMS + " lbs\nMin Load: " + Defs.MINLOAD_OMS + " lbs"; }
		}

		public string Consumables_KOMS_Tooltip
		{
			get
			{
				if (mission.OV.OMSKitTanks != 0)
				{
					return "Max Load: " + (Defs.MAXLOAD_OMS * mission.OV.OMSKitTanks) + " lbs\nMin Load: " + (Defs.MINLOAD_OMS + (Defs.MAXLOAD_OMS * (mission.OV.OMSKitTanks - 1))) + " lbs";
				}
				else return "";
			}
		}

		/// <summary>
		/// Is the OMS Kit load field enabled
		/// </summary>
		private bool consumables_koms_load_ena;
		public bool Consumables_KOMS_Load_ena
		{
			get { return consumables_koms_load_ena; }
			set
			{
				consumables_koms_load_ena = value;
				OnPropertyChanged( "Consumables_KOMS_Load_ena" );
			}
		}

		public static string[] Consumables_OMSKitTanks_src{ get; } = { Defs.strNoOMSKit, Defs.strOMSKit1TankSet, Defs.strOMSKit2TankSets, Defs.strOMSKit3TankSets };

		public int Consumables_OMSKitTanks
		{
			get { return mission.OV.OMSKitTanks; }
			set
			{
				if (value > 3) mission.OV.OMSKitTanks = 3;
				else if (value < 0) mission.OV.OMSKitTanks = 0;
				else mission.OV.OMSKitTanks = value;

				Consumables_KOMS_Load_ena = (mission.OV.OMSKitTanks != 0);

				OnPropertyChanged( "Consumables_OMSKitTanks" );
			}
		}

		public static string[] Consumables_PRSDInternalTanks_src{ get; } = { Defs.strPRSD2TankSets, Defs.strPRSD3TankSets, Defs.strPRSD4TankSets, Defs.strPRSD5TankSets };

		public int Consumables_PRSDInternalTanks
		{
			get { return mission.OV.PRSDInternalTanks - 2; }
			set
			{
				if (value > 3) mission.OV.PRSDInternalTanks = 5;
				else if (value < 0) mission.OV.PRSDInternalTanks = 2;
				else mission.OV.PRSDInternalTanks = value + 2;
				OnPropertyChanged( "Consumables_PRSDInternalTanks" );
			}
		}

		public bool Consumables_EDOKit
		{
			get { return mission.OV.EDOKit; }
			set
			{
				mission.OV.EDOKit = value;
				OnPropertyChanged( "Consumables_EDOKit" );
			}
		}

		/// <summary>
		/// Is the EDO Kit option enabled
		/// </summary>
		private bool consumables_edokit_ena;
		public bool Consumables_EDOKit_ena
		{
			get { return consumables_edokit_ena; }
			set
			{
				consumables_edokit_ena = value;
				OnPropertyChanged( "Consumables_EDOKit_ena" );
			}
		}

		/// <summary>
		/// List of EDO Pallet options, without Dual Pallet.
		/// </summary>
		public static string[] Consumables_EDOPallet_Single_src{ get; } = { Defs.strNoEDOPallet, Defs.strSingleEDOPallet };

		/// <summary>
		/// List of EDO Pallet options, with Dual Pallet.
		/// </summary>
		public static string[] Consumables_EDOPallet_Dual_src{ get; } = { Defs.strNoEDOPallet, Defs.strSingleEDOPallet, Defs.strDualEDOPallet };

		/// <summary>
		/// List of EDO Pallet options.
		/// </summary>
		private string[] consumables_edopallet_src;// TODO hide dual pallet option instead of switching lists?
		public string[] Consumables_EDOPallet_src
		{
			get { return consumables_edopallet_src; }
			set
			{
				consumables_edopallet_src = value;
				OnPropertyChanged( "Consumables_EDOPallet_src" );
			}
		}

		public int Consumables_EDOPallet
		{
			get { return mission.OV.EDOPallet; }
			set
			{
				mission.OV.EDOPallet = value;
				OnPropertyChanged( "Consumables_EDOPallet" );
			}
		}


		/// ET/SRB tab
		void ET_Update_Enables()
		{
			switch (ETSRB_ET)
			{
				case Defs.strSWT:
					ETSRB_FRL_ena = true;
					ETSRB_Bipod_Ramps_ena = false;
					ETSRB_PAL_Ramps_ena = false;
					break;
				case Defs.strLWT:
					ETSRB_FRL_ena = false;
					ETSRB_Bipod_Ramps_ena = false;
					ETSRB_PAL_Ramps_ena = false;
					break;
				case Defs.strSLWT:
					ETSRB_FRL_ena = false;
					ETSRB_Bipod_Ramps_ena = true;
					ETSRB_PAL_Ramps_ena = true;
					break;
			}
			return;
		}

		void ET_Update_Features()
		{
			switch (ETSRB_ET)
			{
				case Defs.strSWT:
					ETSRB_Bipod_Ramps = true;
					ETSRB_PAL_Ramps = true;
					break;
				case Defs.strLWT:
					if (ETSRB_FRL) ETSRB_FRL = false;
					ETSRB_Bipod_Ramps = true;
					ETSRB_PAL_Ramps = true;
					break;
				case Defs.strSLWT:
					if (ETSRB_FRL) ETSRB_FRL = false;
					break;
			}
			return;
		}

		void ETSRB_ET_Update_ET_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultETTextures( mission.ET.Type, mission.ET.FRL );
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			ETSRB_ET_Default_Texture_src = texlist;
			return;
		}

		void ETSRB_ET_Update_SRB_LH_Fwd_Assembly_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultSRBLHFwdAssemblyTextures( mission.SRB.SRM );
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			ETSRB_LHFwdAssembly_Default_Texture_src = texlist;
			return;
		}

		void ETSRB_ET_Update_SRB_RH_Fwd_Assembly_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultSRBRHFwdAssemblyTextures( mission.SRB.SRM );
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			ETSRB_RHFwdAssembly_Default_Texture_src = texlist;
			return;
		}

		void ETSRB_ET_Update_SRB_LH_Case_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultSRBLHCaseTextures( mission.SRB.SRM );
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			ETSRB_LHCase_Default_Texture_src = texlist;
			return;
		}

		void ETSRB_ET_Update_SRB_RH_Case_Texture()
		{
			List<Defs.TEX_INFO> texlist = Defs.DefaultSRBRHCaseTextures( mission.SRB.SRM );
			texlist.Add( new Defs.TEX_INFO{ Name = "Custom...", File = "" } );
			ETSRB_RHCase_Default_Texture_src = texlist;
			return;
		}

		/// <summary>
		/// ET type list
		/// </summary>
		public static string[] ETSRB_ET_src{ get; } = { Defs.strSWT, Defs.strLWT, Defs.strSLWT };

		/// <summary>
		/// ET type
		/// </summary>
		public string ETSRB_ET
		{
			get { return mission.ET.Type; }
			set
			{
				mission.ET.Type = value;

				ET_Update_Enables();
				ET_Update_Features();

				// update texture list
				ETSRB_ET_Update_ET_Texture();
				ETSRB_ET_Default_Texture = ETSRB_ET_Default_Texture_src[0];

				OnPropertyChanged( "ETSRB_ET" );
			}
		}

		/// <summary>
		/// Does the ET have FRL (for SWT ET only)
		/// </summary>
		public bool ETSRB_FRL
		{
			get { return mission.ET.FRL; }
			set
			{
				mission.ET.FRL = value;

				// update texture list
				ETSRB_ET_Update_ET_Texture();
				ETSRB_ET_Default_Texture = ETSRB_ET_Default_Texture_src[0];

				OnPropertyChanged( "ETSRB_FRL" );
			}
		}

		/// <summary>
		/// The name of the ET texture
		/// </summary>
		public string ETSRB_ET_Texture
		{
			get { return mission.ET.Texture; }
			set
			{
				mission.ET.Texture = value;
				OnPropertyChanged( "ETSRB_ET_Texture" );
			}
		}

		/// <summary>
		/// Is ET texture field enabled
		/// </summary>
		private bool etsrb_et_texture_ena;
		public bool ETSRB_ET_Texture_ena
		{
			get { return etsrb_et_texture_ena; }
			set
			{
				etsrb_et_texture_ena = value;
				OnPropertyChanged( "ETSRB_ET_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default ET textures
		/// </summary>
		private List<Defs.TEX_INFO> etsrb_et_default_texture_src;
		public List<Defs.TEX_INFO> ETSRB_ET_Default_Texture_src
		{
			get { return etsrb_et_default_texture_src; }
			set
			{
				etsrb_et_default_texture_src = value;
				OnPropertyChanged( "ETSRB_ET_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default ET texture
		/// </summary>
		private Defs.TEX_INFO etsrb_et_default_texture;
		public Defs.TEX_INFO ETSRB_ET_Default_Texture
		{
			get { return etsrb_et_default_texture; }
			set
			{
				if (value == null) return;

				etsrb_et_default_texture = value;

				if (value.File == "")
				{
					ETSRB_ET_Texture_ena = true;
				}
				else
				{
					ETSRB_ET_Texture_ena = false;
					ETSRB_ET_Texture = value.File;
				}
				OnPropertyChanged( "ETSRB_ET_Default_Texture" );
			}
		}

		/// <summary>
		/// Is the FRL option enabled
		/// </summary>
		private bool etsrb_frl_ena;
		public bool ETSRB_FRL_ena
		{
			get { return etsrb_frl_ena; }
			set
			{
				etsrb_frl_ena = value;
				OnPropertyChanged( "ETSRB_FRL_ena" );
			}
		}

		/// <summary>
		/// Does the ET have Bipod Ramps (for SLWT ET only)
		/// </summary>
		public bool ETSRB_Bipod_Ramps
		{
			get { return mission.ET.Bipod_Ramps; }
			set
			{
				mission.ET.Bipod_Ramps = value;
				OnPropertyChanged( "ETSRB_Bipod_Ramps" );
			}
		}

		/// <summary>
		/// Is the Bipod Ramps option enabled
		/// </summary>
		private bool etsrb_bipod_ramps_ena;
		public bool ETSRB_Bipod_Ramps_ena
		{
			get { return etsrb_bipod_ramps_ena; }
			set
			{
				etsrb_bipod_ramps_ena = value;
				OnPropertyChanged( "ETSRB_Bipod_Ramps_ena" );
			}
		}

		/// <summary>
		/// Does the ET have PAL Ramps (for SLWT ET only)
		/// </summary>
		public bool ETSRB_PAL_Ramps
		{
			get { return mission.ET.PAL_Ramps; }
			set
			{
				mission.ET.PAL_Ramps = value;
				OnPropertyChanged( "ETSRB_PAL_Ramps" );
			}
		}

		/// <summary>
		/// Is the PAL Ramps option enabled
		/// </summary>
		private bool etsrb_pal_ramps_ena;
		public bool ETSRB_PAL_Ramps_ena
		{
			get { return etsrb_pal_ramps_ena; }
			set
			{
				etsrb_pal_ramps_ena = value;
				OnPropertyChanged( "ETSRB_PAL_Ramps_ena" );
			}
		}

		/// <summary>
		/// SRM type list
		/// </summary>
		public static string[] ETSRB_SRM_src{ get; } = { Defs.strSPM, Defs.strHPM, Defs.strFWC, Defs.strRSRM };

		/// <summary>
		/// SRM type
		/// </summary>
		public string ETSRB_SRM
		{
			get { return mission.SRB.SRM; }
			set
			{
				mission.SRB.SRM = value;

				// update LH Fwd Assembly texture list
				ETSRB_ET_Update_SRB_LH_Fwd_Assembly_Texture();
				ETSRB_LHFwdAssembly_Default_Texture = ETSRB_LHFwdAssembly_Default_Texture_src[0];

				// update LH Fwd Assembly texture list
				ETSRB_ET_Update_SRB_RH_Fwd_Assembly_Texture();
				ETSRB_RHFwdAssembly_Default_Texture = ETSRB_RHFwdAssembly_Default_Texture_src[0];

				// update LH Fwd Assembly texture list
				ETSRB_ET_Update_SRB_LH_Case_Texture();
				ETSRB_LHCase_Default_Texture = ETSRB_LHCase_Default_Texture_src[0];

				// update LH Fwd Assembly texture list
				ETSRB_ET_Update_SRB_RH_Case_Texture();
				ETSRB_RHCase_Default_Texture = ETSRB_RHCase_Default_Texture_src[0];

				OnPropertyChanged( "ETSRB_SRM" );
			}
		}

		/// <summary>
		/// The name of the LH Fwd Assembly texture
		/// </summary>
		public string ETSRB_LHFwdAssembly_Texture
		{
			get { return mission.SRB.LHFwdAssemblyTexture; }
			set
			{
				mission.SRB.LHFwdAssemblyTexture = value;
				OnPropertyChanged( "ETSRB_LHFwdAssembly_Texture" );
			}
		}

		/// <summary>
		/// Is LH Fwd Assembly texture field enabled
		/// </summary>
		private bool etsrb_lhfwdassembly_texture_ena;
		public bool ETSRB_LHFwdAssembly_Texture_ena
		{
			get { return etsrb_lhfwdassembly_texture_ena; }
			set
			{
				etsrb_lhfwdassembly_texture_ena = value;
				OnPropertyChanged( "ETSRB_LHFwdAssembly_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default LH Fwd Assembly textures
		/// </summary>
		private List<Defs.TEX_INFO> etsrb_lhfwdassembly_default_texture_src;
		public List<Defs.TEX_INFO> ETSRB_LHFwdAssembly_Default_Texture_src
		{
			get { return etsrb_lhfwdassembly_default_texture_src; }
			set
			{
				etsrb_lhfwdassembly_default_texture_src = value;
				OnPropertyChanged( "ETSRB_LHFwdAssembly_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default LH Fwd Assembly texture
		/// </summary>
		private Defs.TEX_INFO etsrb_lhfwdassembly_default_texture;
		public Defs.TEX_INFO ETSRB_LHFwdAssembly_Default_Texture
		{
			get { return etsrb_lhfwdassembly_default_texture; }
			set
			{
				if (value == null) return;

				etsrb_lhfwdassembly_default_texture = value;

				if (value.File == "")
				{
					ETSRB_LHFwdAssembly_Texture_ena = true;
				}
				else
				{
					ETSRB_LHFwdAssembly_Texture_ena = false;
					ETSRB_LHFwdAssembly_Texture = value.File;
				}
				OnPropertyChanged( "ETSRB_LHFwdAssembly_Default_Texture" );
			}
		}

		/// <summary>
		/// The name of the RH Fwd Assembly texture
		/// </summary>
		public string ETSRB_RHFwdAssembly_Texture
		{
			get { return mission.SRB.RHFwdAssemblyTexture; }
			set
			{
				mission.SRB.RHFwdAssemblyTexture = value;
				OnPropertyChanged( "ETSRB_RHFwdAssembly_Texture" );
			}
		}

		/// <summary>
		/// Is RH Fwd Assembly texture field enabled
		/// </summary>
		private bool etsrb_rhfwdassembly_texture_ena;
		public bool ETSRB_RHFwdAssembly_Texture_ena
		{
			get { return etsrb_rhfwdassembly_texture_ena; }
			set
			{
				etsrb_rhfwdassembly_texture_ena = value;
				OnPropertyChanged( "ETSRB_RHFwdAssembly_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default RH Fwd Assembly textures
		/// </summary>
		private List<Defs.TEX_INFO> etsrb_rhfwdassembly_default_texture_src;
		public List<Defs.TEX_INFO> ETSRB_RHFwdAssembly_Default_Texture_src
		{
			get { return etsrb_rhfwdassembly_default_texture_src; }
			set
			{
				etsrb_rhfwdassembly_default_texture_src = value;
				OnPropertyChanged( "ETSRB_RHFwdAssembly_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default RH Fwd Assembly texture
		/// </summary>
		private Defs.TEX_INFO etsrb_rhfwdassembly_default_texture;
		public Defs.TEX_INFO ETSRB_RHFwdAssembly_Default_Texture
		{
			get { return etsrb_rhfwdassembly_default_texture; }
			set
			{
				if (value == null) return;

				etsrb_rhfwdassembly_default_texture = value;

				if (value.File == "")
				{
					ETSRB_RHFwdAssembly_Texture_ena = true;
				}
				else
				{
					ETSRB_RHFwdAssembly_Texture_ena = false;
					ETSRB_RHFwdAssembly_Texture = value.File;
				}
				OnPropertyChanged( "ETSRB_RHFwdAssembly_Default_Texture" );
			}
		}

		/// <summary>
		/// The name of the LH Case texture
		/// </summary>
		public string ETSRB_LHCase_Texture
		{
			get { return mission.SRB.LHCaseTexture; }
			set
			{
				mission.SRB.LHCaseTexture = value;
				OnPropertyChanged( "ETSRB_LHCase_Texture" );
			}
		}

		/// <summary>
		/// Is LH Case texture field enabled
		/// </summary>
		private bool etsrb_lhcase_texture_ena;
		public bool ETSRB_LHCase_Texture_ena
		{
			get { return etsrb_lhcase_texture_ena; }
			set
			{
				etsrb_lhcase_texture_ena = value;
				OnPropertyChanged( "ETSRB_LHCase_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default LH Case textures
		/// </summary>
		private List<Defs.TEX_INFO> etsrb_lhcase_default_texture_src;
		public List<Defs.TEX_INFO> ETSRB_LHCase_Default_Texture_src
		{
			get { return etsrb_lhcase_default_texture_src; }
			set
			{
				etsrb_lhcase_default_texture_src = value;
				OnPropertyChanged( "ETSRB_LHCase_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default LH Case texture
		/// </summary>
		private Defs.TEX_INFO etsrb_lhcase_default_texture;
		public Defs.TEX_INFO ETSRB_LHCase_Default_Texture
		{
			get { return etsrb_lhcase_default_texture; }
			set
			{
				if (value == null) return;

				etsrb_lhcase_default_texture = value;

				if (value.File == "")
				{
					ETSRB_LHCase_Texture_ena = true;
				}
				else
				{
					ETSRB_LHCase_Texture_ena = false;
					ETSRB_LHCase_Texture = value.File;
				}
				OnPropertyChanged( "ETSRB_LHCase_Default_Texture" );
			}
		}

		/// <summary>
		/// The name of the RH Case texture
		/// </summary>
		public string ETSRB_RHCase_Texture
		{
			get { return mission.SRB.RHCaseTexture; }
			set
			{
				mission.SRB.RHCaseTexture = value;
				OnPropertyChanged( "ETSRB_RHCase_Texture" );
			}
		}

		/// <summary>
		/// Is RH Case texture field enabled
		/// </summary>
		private bool etsrb_rhcase_texture_ena;
		public bool ETSRB_RHCase_Texture_ena
		{
			get { return etsrb_rhcase_texture_ena; }
			set
			{
				etsrb_rhcase_texture_ena = value;
				OnPropertyChanged( "ETSRB_RHCase_Texture_ena" );
			}
		}

		/// <summary>
		/// List of default RH Case textures
		/// </summary>
		private List<Defs.TEX_INFO> etsrb_rhcase_default_texture_src;
		public List<Defs.TEX_INFO> ETSRB_RHCase_Default_Texture_src
		{
			get { return etsrb_rhcase_default_texture_src; }
			set
			{
				etsrb_rhcase_default_texture_src = value;
				OnPropertyChanged( "ETSRB_RHCase_Default_Texture_src" );
			}
		}

		/// <summary>
		/// Selected default RH Case texture
		/// </summary>
		private Defs.TEX_INFO etsrb_rhcase_default_texture;
		public Defs.TEX_INFO ETSRB_RHCase_Default_Texture
		{
			get { return etsrb_rhcase_default_texture; }
			set
			{
				if (value == null) return;

				etsrb_rhcase_default_texture = value;

				if (value.File == "")
				{
					ETSRB_RHCase_Texture_ena = true;
				}
				else
				{
					ETSRB_RHCase_Texture_ena = false;
					ETSRB_RHCase_Texture = value.File;
				}
				OnPropertyChanged( "ETSRB_RHCase_Default_Texture" );
			}
		}


		/// PAYLOAD tab
		// TODO

		/// MECO (Legacy) tab
		// TODO?????


		/// I-LOADs tab
		public ObservableCollection<Mission_ILOAD> ILOAD_List
		{
			get
			{
				return mission.OV.ILOAD_List;
			}
			set
			{
				mission.OV.ILOAD_List = value;
				OnPropertyChanged( "ILOAD_List" );
			}
		}

		/// OTHER VESSELS tab
		public ICommand OtherVessels_NewVesselCommand{ get; private set; }
		void NewVesselCommand()
		{
			Mission_Vessel tmp = new Mission_Vessel();
			tmp.Name = "New Vessel";

			mission.OtherVessels.Add( tmp );
			return;
		}

		public ICommand OtherVessels_DeleteVesselCommand{ get; private set; }
		void DeleteVesselCommand()
		{
			mission.OtherVessels.Remove( OtherVessels_Vessel );
			return;
		}

		public ICommand OtherVessels_GetVesselClassCommand{ get; private set; }
		void GetVesselClassCommand()
		{
			MainWindow mw = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			PickVesselClass pickvesselclass = new PickVesselClass( mw.mission.AvailableVessels );
			pickvesselclass.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			if (pickvesselclass.ShowDialog() == true) OtherVessels_Vessel.VesselClass = pickvesselclass.vesselclass;
			return;
		}


		/// <summary>
		/// List of OtherVessels.
		/// </summary>
		public ObservableCollection<Mission_Vessel> OtherVessels_List
		{
			get { return mission.OtherVessels; }
			set
			{
				mission.OtherVessels = value;
				OnPropertyChanged( "OtherVessels_List" );
			}
		}

		/// <summary>
		/// OtherVessel currently selected from OtherVessels list.
		/// </summary>
		private Mission_Vessel othervessels_vessel;
		public Mission_Vessel OtherVessels_Vessel
		{
			get { return othervessels_vessel; }
			set
			{
				othervessels_vessel = value;
				OnPropertyChanged( "OtherVessels_Vessel" );
			}
		}



		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
			return;
		}
	}
}
