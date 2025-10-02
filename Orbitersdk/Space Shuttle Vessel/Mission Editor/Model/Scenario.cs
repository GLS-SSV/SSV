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
2020/05/01   GLS
2020/05/07   GLS
2020/05/14   GLS
2020/05/25   GLS
2020/05/31   GLS
2020/06/12   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/07/02   GLS
2020/07/03   GLS
2020/07/08   GLS
2020/07/30   GLS
2020/08/22   GLS
2020/09/28   GLS
2020/10/09   GLS
2020/10/10   GLS
2021/12/19   GLS
2021/12/24   GLS
2021/12/25   GLS
2022/01/10   GLS
2022/03/04   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/11/13   GLS
2023/08/06   GLS
2025/01/23   GLS
2025/02/11   GLS
2025/05/10   GLS
2025/06/21   GLS
2025/10/02   GLS
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
using System.Collections.Generic;


namespace SSVMissionEditor.Model
{
	public enum MissionPhase
	{
		Preview = -1,
		LaunchT20m = 0,
		LaunchT9m,
		LaunchT31s
	}

	public class Scenario
	{
		public struct MFDtype
		{
			public bool on;
			public string type;
			public List<string> _params;
		}

		public Scenario( Mission mission )
		{
			mfds = new MFDtype[12];
			for (int i = 0; i < 12; i++) mfds[i]._params = new List<string>();

			this.mission = mission;

			// add SSV vessels
			scnvessels = new List<OrbiterVessel>();
			SSV_LCC ssvlcc = new SSV_LCC( mission );
			scnvessels.Add( ssvlcc );
			if (mission.LaunchSite == Defs.strKSC)
			{
				SSV_LC39 ssvpad = new SSV_LC39( mission );
				scnvessels.Add( ssvpad );
				SSV_MLP ssvmlp = new SSV_MLP( mission );
				scnvessels.Add( ssvmlp );
			}
			else
			{
				SSV_SLC6 ssvpad = new SSV_SLC6( mission );
				scnvessels.Add( ssvpad );
			}
			ssv_ov = new SSV_OV( mission, mfds );
			scnvessels.Add( ssv_ov );
			SSV_ET ssvet = new SSV_ET( mission );
			scnvessels.Add( ssvet );
			SSV_SRB ssvlsrb = new SSV_SRB( mission, true );
			scnvessels.Add( ssvlsrb );
			SSV_SRB ssvrsrb = new SSV_SRB( mission, false );
			scnvessels.Add( ssvrsrb );

			// add SSV upper stages
			if (mission.LargeUpperStage == 1)
			{
				SSV_IUS_SRM1 ssvius1 = new SSV_IUS_SRM1( mission );
				scnvessels.Add( ssvius1 );

				SSV_IUS_SRM2 ssvius2 = new SSV_IUS_SRM2( mission );
				scnvessels.Add( ssvius2 );
			}
			else if (mission.LargeUpperStage == 4)
			{
				SSV_CentaurG ssvcentaurg = new SSV_CentaurG( mission );
				scnvessels.Add( ssvcentaurg );
			}
			else if (mission.LargeUpperStage == 5)
			{
				SSV_CentaurGPrime ssvcentaurgprime = new SSV_CentaurGPrime( mission );
				scnvessels.Add( ssvcentaurgprime );
			}

			// add OV payloads
			// active
			for (int i = 0; i < Mission_OV.PAYLOAD_ACTIVE_MAX; i++)
			{
				if (mission.OV.PL_Active[i].IsUsed && mission.OV.PL_Active[i].HasPayload)
				{
					OrbiterVessel pl = new OrbiterVessel();
					pl.Class = mission.OV.PL_Active[i].Payload.VesselClass;
					pl.Name = mission.OV.PL_Active[i].Payload.Name;
					pl.StatusLanded = true;
					pl.StatusPlanet = "Earth";
					pl.Attached.Add( Tuple.Create( mission.OV.PL_Active[i].Payload.AttachmentID, 5 + i, ssv_ov.Name ) );
					string[] scnparamlist = System.Text.RegularExpressions.Regex.Split( mission.OV.PL_Active[i].Payload.ScnParams, "\r\n|\r|\n" );
					foreach (string tmp in scnparamlist) if (tmp.Length != 0) pl.OtherParams.Add( tmp );

					scnvessels.Add( pl );
				}
			}

			// passive
			for (int i = 0; i < Mission_OV.PAYLOAD_PASSIVE_MAX; i++)
			{
				if (mission.OV.PL_Passive[i].IsUsed)
				{
					OrbiterVessel pl = new OrbiterVessel();
					pl.Class = mission.OV.PL_Passive[i].Payload.VesselClass;
					pl.Name = mission.OV.PL_Passive[i].Payload.Name;
					pl.StatusLanded = true;
					pl.StatusPlanet = "Earth";
					pl.Attached.Add( Tuple.Create( mission.OV.PL_Passive[i].Payload.AttachmentID, 10 + i, ssv_ov.Name ) );
					string[] scnparamlist = System.Text.RegularExpressions.Regex.Split( mission.OV.PL_Passive[i].Payload.ScnParams, "\r\n|\r|\n" );
					foreach (string tmp in scnparamlist) if (tmp.Length != 0) pl.OtherParams.Add( tmp );

					scnvessels.Add( pl );
				}
			}

			// bay bridge
			for (int i = 0; i < Mission_OV.PAYLOAD_BAYBRIDGE_MAX; i++)
			{
				if (mission.OV.PL_BayBridge[i].IsUsed)
				{
					OrbiterVessel pl = new OrbiterVessel();
					pl.Class = mission.OV.PL_BayBridge[i].Payload.VesselClass;
					pl.Name = mission.OV.PL_BayBridge[i].Payload.Name;
					pl.StatusLanded = true;
					pl.StatusPlanet = "Earth";
					pl.Attached.Add( Tuple.Create( mission.OV.PL_BayBridge[i].Payload.AttachmentID, 15 + i, ssv_ov.Name ) );
					string[] scnparamlist = System.Text.RegularExpressions.Regex.Split( mission.OV.PL_BayBridge[i].Payload.ScnParams, "\r\n|\r|\n" );
					foreach (string tmp in scnparamlist) if (tmp.Length != 0) pl.OtherParams.Add( tmp );

					scnvessels.Add( pl );
				}
			}

			// Port SPDS payload
			if (mission.OV.PortLongeronSill == LongeronSillHardware_Type.SPDS)
			{
				OrbiterVessel pl = new OrbiterVessel();
				pl.Class = mission.OV.Port_SPDS.Payload.VesselClass;
				pl.Name = mission.OV.Port_SPDS.Payload.Name;
				pl.StatusLanded = true;
				pl.StatusPlanet = "Earth";
				pl.Attached.Add( Tuple.Create( mission.OV.Port_SPDS.Payload.AttachmentID, 0, ssv_ov.Name ) );
				string[] scnparamlist = System.Text.RegularExpressions.Regex.Split( mission.OV.Port_SPDS.Payload.ScnParams, "\r\n|\r|\n" );
				foreach (string tmp in scnparamlist) if (tmp.Length != 0) pl.OtherParams.Add( tmp );

				scnvessels.Add( pl );
			}

			// STBD MPM payload
			if (mission.OV.StbdLongeronSill == LongeronSillHardware_Type.PayloadMPM)
			{
				OrbiterVessel pl = new OrbiterVessel();
				pl.Class = mission.OV.Stbd_PL_MPM.Payload.VesselClass;
				pl.Name = mission.OV.Stbd_PL_MPM.Payload.Name;
				pl.StatusLanded = true;
				pl.StatusPlanet = "Earth";
				pl.Attached.Add( Tuple.Create( mission.OV.Stbd_PL_MPM.Payload.AttachmentID, 1, ssv_ov.Name ) );
				string[] scnparamlist = System.Text.RegularExpressions.Regex.Split( mission.OV.Stbd_PL_MPM.Payload.ScnParams, "\r\n|\r|\n" );
				foreach (string tmp in scnparamlist) if (tmp.Length != 0) pl.OtherParams.Add( tmp );

				scnvessels.Add( pl );
			}

			// add upper stage payloads
			if (mission.LargeUpperStage != 0)
			{
				OrbiterVessel pl = new OrbiterVessel();
				pl.Class = mission.LargeUpperStage_PL.VesselClass;
				pl.Name = mission.LargeUpperStage_PL.Name;
				pl.StatusLanded = true;
				pl.StatusPlanet = "Earth";
				pl.Attached.Add( Tuple.Create( mission.LargeUpperStage_PL.AttachmentID, 0, mission.LargeUpperStage_Name ) );
				string[] scnparamlist = System.Text.RegularExpressions.Regex.Split( mission.LargeUpperStage_PL.ScnParams, "\r\n|\r|\n" );
				foreach (string tmp in scnparamlist) if (tmp.Length != 0) pl.OtherParams.Add( tmp );

				scnvessels.Add( pl );
			}

			// other vessels
			foreach (Mission_Vessel tmp in mission.OtherVessels)
			{
				OtherVessel v = new OtherVessel( tmp );
				scnvessels.Add( v );
			}

			missionphase = MissionPhase.LaunchT31s;
			Description = mission.Description;

			scnSystem = "Sol";
			scnContext = "SSV";
			scnCameraMode = 0;
			scnShip = mission.OV.Name.ToString();
			scnCameraTarget = mission.OV.Name.ToString();
			scnCameraVesselRadius = 5.0;
			scnCameraFOV = 40.0;
			scnCameraTrackMode = 0;
			scnCameraTrackModeRef = "Earth";
			scnTargetLock = true;
			scnCameraGrDirH = 0.0;
			scnCameraGrDirV = 0.0;
			scnCameraGrPosLon = 0.0;
			scnCameraGrPosLat = 0.0;
			scnCameraGrPosAlt = 0.0;
			scnCockpitType = 2;

			Create();
		}

		void Create()
		{
			for (int i = 0; i < scnvessels.Count; i++) scnvessels[i].PreSave( missionphase );// TODO better name

			switch (missionphase)
			{
				case MissionPhase.Preview:
					{
						int ms = Convert.ToInt32( 1000 * (mission.T0Second - (int)mission.T0Second) );
						DateTime dt = new DateTime( mission.T0Year, mission.T0Month, mission.T0Day, mission.T0Hour, mission.T0Minute, (int)mission.T0Second, ms );
						dt = dt.AddMinutes( -20000.0 );// about 2 weeks

						scnDate = dt.ToString( "yyyy/MM/dd HH:mm:ss.f" );
						scnMJD = dt.ToOADate() + 15018.0;

						// set ground view of PLB
						scnCameraMode = 1;
						scnCameraVesselRadius = 1.0;
						scnCameraFOV = 70.0;
						scnCameraTrackMode = 5;
						scnTargetLock = false;
						scnCockpitType = 0;
						if (mission.LaunchSite == Defs.strKSC)
						{
							scnCameraGrDirH = 90.0;
							scnCameraGrDirV = 20.0;
							scnCameraGrPosAlt = 40.0;
							if (mission.LaunchPad == Defs.strLC39A)
							{
								scnShip = "LC-39A";
								scnCameraTarget = "LC-39A";
								scnCameraGrPosLon = -80.60407;
								scnCameraGrPosLat = 28.60817;
							}
							else
							{
								scnShip = "LC-39B";
								scnCameraTarget = "LC-39B";
								scnCameraGrPosLon = -80.62086;
								scnCameraGrPosLat = 28.627;
							}
						}
						else
						{
							scnShip = "SLC-6";
							scnCameraTarget = "SLC-6";
							scnCameraGrDirH = 0.0;
							scnCameraGrDirV = 20.0;
							scnCameraGrPosLon = -120.62619;
							scnCameraGrPosLat = 34.580850;
							scnCameraGrPosAlt = 39.0;
						}
					}
					break;
				case MissionPhase.LaunchT20m:
					{
						int ms = Convert.ToInt32( 1000 * (mission.T0Second - (int)mission.T0Second) );
						DateTime dt = new DateTime( mission.T0Year, mission.T0Month, mission.T0Day, mission.T0Hour, mission.T0Minute, (int)mission.T0Second, ms );
						dt = dt.AddMinutes( -20.0 );// TODO should include holds
						dt = dt.AddSeconds( -Defs.SCN_TIME_OFFSET );

						scnDate = dt.ToString( "yyyy/MM/dd HH:mm:ss.f" );
						scnMJD = dt.ToOADate() + 15018.0;
					}
					break;
				case MissionPhase.LaunchT9m:
					{
						int ms = Convert.ToInt32( 1000 * (mission.T0Second - (int)mission.T0Second) );
						DateTime dt = new DateTime( mission.T0Year, mission.T0Month, mission.T0Day, mission.T0Hour, mission.T0Minute, (int)mission.T0Second, ms );
						dt = dt.AddMinutes( -9.0 );
						dt = dt.AddSeconds( -Defs.SCN_TIME_OFFSET );

						scnDate = dt.ToString( "yyyy/MM/dd HH:mm:ss.f" );
						scnMJD = dt.ToOADate() + 15018.0;
					}
					break;
				case MissionPhase.LaunchT31s:
					{
						int ms = Convert.ToInt32( 1000 * (mission.T0Second - (int)mission.T0Second) );
						DateTime dt = new DateTime( mission.T0Year, mission.T0Month, mission.T0Day, mission.T0Hour, mission.T0Minute, (int)mission.T0Second, ms );
						dt = dt.AddSeconds( -31.0 );
						dt = dt.AddSeconds( -Defs.SCN_TIME_OFFSET );

						scnDate = dt.ToString( "yyyy/MM/dd HH:mm:ss.f" );
						scnMJD = dt.ToOADate() + 15018.0;
					}
					break;
			}
			return;
		}

		public void Save( string scnfile )
		{
			Create();

			System.IO.StreamWriter file = new System.IO.StreamWriter( scnfile );

			////////////////// description //////////////////
			file.WriteLine( "BEGIN_DESC" );
			file.WriteLine( Description );
			file.WriteLine( "END_DESC" );
			file.WriteLine( "" );

			////////////////// environment //////////////////
			file.WriteLine( "BEGIN_ENVIRONMENT" );
			file.WriteLine( "  System " + scnSystem );
			file.WriteLine( "  Date MJD " + string.Format( "{0:f10}", scnMJD ).Replace( ',', '.' ) );
			if (!String.IsNullOrEmpty( scnContext )) file.WriteLine( "  Context " + scnContext );
			if (!String.IsNullOrEmpty( scnScript )) file.WriteLine( "  Script " + scnScript );
			file.WriteLine( "END_ENVIRONMENT" );
			file.WriteLine( "" );

			////////////////// focus //////////////////
			file.WriteLine( "BEGIN_FOCUS" );
			file.WriteLine( "  Ship " + scnShip );
			file.WriteLine( "END_FOCUS\r\n" );

			////////////////// camera //////////////////
			file.WriteLine( "BEGIN_CAMERA" );
			file.WriteLine( "  TARGET " + scnCameraTarget );
			if (scnCameraMode == 0) file.WriteLine( "  MODE Cockpit" );
			else file.WriteLine( "  MODE Extern" );
			if (scnCameraMode == 1)
			{
				if (scnCameraTrackMode != 5) file.WriteLine( "  POS " + string.Format( "{0:f6} {1:f6} {2:f6}", scnCameraVesselRadius, scnCameraPosPhi, scnCameraPosTheta ).Replace( ',', '.' ) );
	
				if (scnCameraTrackMode == 1) file.WriteLine( "  TRACKMODE AbsoluteDirection" );
				else if (scnCameraTrackMode == 2) file.WriteLine( "  TRACKMODE GlobalFrame" );
				else if (scnCameraTrackMode == 3) file.WriteLine( "  TRACKMODE TargetTo " + scnCameraTrackModeRef );
				else if (scnCameraTrackMode == 4) file.WriteLine( "  TRACKMODE TargetFrom " + scnCameraTrackModeRef );
				else if (scnCameraTrackMode == 5)
				{
					file.WriteLine( "  TRACKMODE Ground " + scnCameraTrackModeRef );
					file.WriteLine( "  GROUNDLOCATION " + string.Format( "{0:f5} {1:f5} {2:f2}", scnCameraGrPosLon, scnCameraGrPosLat, scnCameraGrPosAlt ).Replace( ',', '.' ) );
					if (scnTargetLock == false) file.WriteLine( "  GROUNDDIRECTION " + string.Format( "{0:f2} {1:f2}", scnCameraGrDirH, scnCameraGrDirV ).Replace( ',', '.' ) );
				}
				else /*if (scnCameraTrackMode == 0)*/ file.WriteLine( "  TRACKMODE TargetRelative" );
			}
			file.WriteLine( "  FOV " + string.Format( "{0:f2}", scnCameraFOV ).Replace( ',', '.' ) );
			file.WriteLine( "END_CAMERA" );
			file.WriteLine( "" );

			////////////////// hud //////////////////
			if (scnHUDType != 0)
			{
				file.WriteLine( "BEGIN_HUD" );
				if (scnHUDType == 1)
				{
					file.WriteLine( "  TYPE Orbit" );
					if (!String.IsNullOrEmpty( scnHUDRef )) file.WriteLine( "  REF " + scnHUDRef );
				}
				else if (scnHUDType == 2) file.WriteLine( "  TYPE Surface" );
				else
				{
					file.WriteLine( "  TYPE Docking" );
					if (scnHUDNAV != -1) file.WriteLine( "  NAV " + scnHUDNAV );
				}
				file.WriteLine( "END_HUD" );
				file.WriteLine( "" );
			}

			////////////////// mfd //////////////////
			string[] MFDname = {"Left", "Right", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
			for (int i = 0; i < 12; i++)
			{
				if (mfds[i].on)
				{
					file.WriteLine( "BEGIN_MFD " + MFDname[i] );
					file.WriteLine( "  TYPE " + mfds[i].type );
					for (int k = 0; k < mfds[i]._params.Count; k++)
					{
						file.WriteLine( "  " + mfds[i]._params[k] );
					}
					file.WriteLine( "END_MFD" );
					file.WriteLine( "" );
				}
			}

			////////////////// panel //////////////////
			if (scnCockpitType == 1)
			{
				file.WriteLine( "BEGIN_PANEL" );
				file.WriteLine( "END_PANEL" );
				file.WriteLine( "" );
			}

			////////////////// vc //////////////////
			if (scnCockpitType == 2)
			{
				file.WriteLine( "BEGIN_VC" );
				file.WriteLine( "END_VC" );
				file.WriteLine( "" );
			}

			////////////////// ships //////////////////
			file.WriteLine( "BEGIN_SHIPS" );
			for (int i = 0; i < scnvessels.Count; i++) scnvessels[i].Save( file );
			file.WriteLine( "END_SHIPS" );

			file.Close();

			return;
		}


		readonly Mission mission;

		private MissionPhase missionphase;
		public MissionPhase scnMissionPhase
		{
			get { return missionphase; }
			set
			{
				missionphase = value;
				Create();// recalculate scenario time
			}
		}

		private readonly SSV_OV ssv_ov;

		/// <summary>
		/// List of vessels used in this mission
		/// </summary>
		public List<OrbiterVessel> scnvessels;

		/// <summary>
		/// Description to be used in the scenario file 
		/// </summary>
		public string Description { get; set; }

		/// <summary>
		/// Scenario system
		/// </summary>
		public string scnSystem;

		/// <summary>
		/// The date/time at the start of the simulation.
		/// </summary>
		public string scnDate { get; set; }

		/// <summary>
		/// The date/time at the start of the simulation in MJD format.
		/// </summary>
		public double scnMJD;

		/// <summary>
		/// Scenario context
		/// (null if none)
		/// </summary>
		private readonly string scnContext;

		/// <summary>
		/// Scenario script
		/// (null if none)
		/// </summary>
		public string scnScript;

		/// <summary>
		/// Ship controlled in the scenario
		/// </summary>
		public string scnShip;

		/// <summary>
		/// Scenario camera target
		/// </summary>
		public string scnCameraTarget;

		/// <summary>
		/// Scenario camera mode
		/// 0 = Cockpit
		/// 1 = Extern
		/// </summary>
		public int scnCameraMode { get; set; }

		/// <summary>
		/// Scenario camera field of view
		/// </summary>
		public double scnCameraFOV { get; set; }

		/// <summary>
		/// Scenario camera position (for External camera mode only)
		/// </summary>
		public double scnCameraVesselRadius { get; set; }

		public double scnCameraPosPhi { get; set; }

		public double scnCameraPosTheta { get; set; }

		/// <summary>
		/// Scenario camera track mode (for External camera mode only)
		/// 0 = Target Relative
		/// 1 = Absolute Direction
		/// 2 = Global Frame
		/// 3 = Target To
		/// 4 = Target From
		/// 5 = Ground
		/// </summary>
		public int scnCameraTrackMode { get; set; }

		/// <summary>
		/// Scenario camera track mode reference (for Target To, Target From and Ground modes only)
		/// </summary>
		public string scnCameraTrackModeRef { get; set; }

		/// <summary>
		/// Scenario camera position for Ground mode
		/// </summary>
		public double scnCameraGrPosLon { get; set; }
		public double scnCameraGrPosLat { get; set; }
		public double scnCameraGrPosAlt { get; set; }

		public bool scnTargetLock { get; set; }

		/// <summary>
		/// Scenario camera direction for Ground mode
		/// </summary>
		public double scnCameraGrDirH { get; set; }
		public double scnCameraGrDirV { get; set; }

		/// <summary>
		/// Scenario cockpit type
		/// 0 = normal
		/// 1 = 2D
		/// 2 = 3D
		/// </summary>
		public int scnCockpitType { get; set; }

		/// <summary>
		/// HUD type
		/// 0 = (off)
		/// 1 = Orbit
		/// 2 = Surface
		/// 3 = Docking
		/// </summary>
		public int scnHUDType { get; set; }

		/// <summary>
		/// HUD reference (Orbit type only)
		/// </summary>
		public string scnHUDRef { get; set; }

		/// <summary>
		/// HUD nav (Docking type only)
		/// </summary>
		public int scnHUDNAV { get; set; }

		/// <summary>
		/// MFD list:
		/// 0: Left
		/// 1: Right
		/// 2: 3
		/// 3: 4
		/// 4: 5
		/// 5: 6
		/// 6: 7
		/// 7: 8
		/// 8: 9
		/// 9: 10
		/// 10: 11
		/// 11: 12
		/// </summary>
		private readonly MFDtype[] mfds;
	}
}
