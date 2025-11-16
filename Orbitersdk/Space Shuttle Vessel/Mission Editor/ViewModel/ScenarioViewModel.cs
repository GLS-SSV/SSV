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

using System.ComponentModel;
using SSVMissionEditor.Model;


namespace SSVMissionEditor.ViewModel
{
	class ScenarioViewModel : INotifyPropertyChanged
	{
		public ScenarioViewModel( Scenario scn )
		{
			this.scn = scn;

			CameraPos_Update();
			CameraGrDir_Update();
			return;
		}

		readonly Scenario scn;


		private void CameraPos_Update()
		{
			switch (scn.scnCameraTrackMode)
			{
				case 0:// TargetRelative
					CameraTrackModeRef_ena = false;

					TargetLock_ena = false;
					TargetLock = true;

					CameraGrPosLon_ena = false;
					CameraGrPosLat_ena = false;
					CameraGrPosAlt_ena = false;

					CameraPosTheta_lbl = "Vessel Beta";
					CameraPosPhi_lbl = "Vessel Alpha";
					break;
				case 1:// AbsoluteDirection
					CameraTrackModeRef_ena = false;

					TargetLock_ena = false;
					TargetLock = true;

					CameraGrPosLon_ena = false;
					CameraGrPosLat_ena = false;
					CameraGrPosAlt_ena = false;

					CameraPosTheta_lbl = "Vessel Beta";
					CameraPosPhi_lbl = "Vessel Alpha";
					break;
				case 2:// GlobalFrame
					CameraTrackModeRef_ena = false;

					TargetLock_ena = false;
					TargetLock = true;

					CameraGrPosLon_ena = false;
					CameraGrPosLat_ena = false;
					CameraGrPosAlt_ena = false;

					CameraPosTheta_lbl= "Ecliptic Longitude";
					CameraPosPhi_lbl = "Ecliptic Latitude";
					break;
				case 3:// TargetTo
					CameraTrackModeRef_ena = true;

					TargetLock_ena = false;
					TargetLock = true;

					CameraGrPosLon_ena = false;
					CameraGrPosLat_ena = false;
					CameraGrPosAlt_ena = false;

					CameraPosTheta_lbl = "Vessel Beta";
					CameraPosPhi_lbl = "Vessel Alpha";
					break;
				case 4:// TargetFrom
					CameraTrackModeRef_ena = true;

					TargetLock_ena = false;
					TargetLock = true;

					CameraGrPosLon_ena = false;
					CameraGrPosLat_ena = false;
					CameraGrPosAlt_ena = false;

					CameraPosTheta_lbl = "Vessel Beta";
					CameraPosPhi_lbl = "Vessel Alpha";
					break;
				case 5:// Ground
					CameraTrackModeRef_ena = true;

					TargetLock_ena = true;

					CameraGrPosLon_ena = true;
					CameraGrPosLat_ena = true;
					CameraGrPosAlt_ena = true;

					CameraPosTheta_lbl = "Vessel Beta";
					CameraPosPhi_lbl = "Vessel Alpha";
					break;
			}
			return;
		}

		private void CameraGrDir_Update()
		{
			if (scn.scnTargetLock == true)
			{
				CameraGrDirH_ena = false;
				CameraGrDirV_ena = false;
			}
			else
			{
				CameraGrDirH_ena = true;
				CameraGrDirV_ena = true;
			}
			return;
		}

		public string Description
		{
			get { return scn.Description; }
			set
			{
				scn.Description = value;
				OnPropertyChanged( "Description" );
			}
		}

		/// <summary>
		/// The date/time at the start of the simulation.
		/// </summary>
		public string Date
		{
			get { return scn.scnDate; }
			set
			{
				scn.scnDate = value;
				OnPropertyChanged( "Date" );
			}
		}

		/// <summary>
		/// List of Mission Phase options.
		/// </summary>
		public static string[] MissionPhase_src{ get; } = { "Launch (T-9 Minutes)", "Launch (T-31 Seconds)" };

		/// <summary>
		/// Mission Phase
		/// 0 = Launch (T-9 Minutes)
		/// 1 = Launch (T-31 Seconds)
		/// </summary>
		public int MissionPhase
		{
			get
			{
				if (scn.scnMissionPhase == Model.MissionPhase.LaunchT9m)
				{
					return 0;
				}
				else if (scn.scnMissionPhase == Model.MissionPhase.LaunchT31s)
				{
					return 1;
				}
				else
				{
					// should not happen, but still force actual value to 31s
					scn.scnMissionPhase = Model.MissionPhase.LaunchT31s;
					return 1;
				}
			}
			set
			{
				if (value == 0)
				{
					scn.scnMissionPhase = Model.MissionPhase.LaunchT9m;
				}
				else
				{
					scn.scnMissionPhase = Model.MissionPhase.LaunchT31s;
				}
				OnPropertyChanged( "MissionPhase" );
			}
		}

		/// <summary>
		/// List of Cockpit Type options.
		/// </summary>
		public static string[] CockpitType_src{ get; } = { "Normal", "2D", "3D" };

		/// <summary>
		/// Scenario cockpit type
		/// 0 = normal
		/// 1 = 2D
		/// 2 = 3D
		/// </summary>
		public int CockpitType
		{
			get { return scn.scnCockpitType; }
			set
			{
				scn.scnCockpitType = value;
				OnPropertyChanged( "CockpitType" );
			}
		}

		/// <summary>
		/// List of HUD Type options.
		/// </summary>
		public static string[] HUDType_src{ get; } = { "Off", "Orbit", "Surface", "Docking" };

		/// <summary>
		/// HUD type
		/// 0 = (off)
		/// 1 = Orbit
		/// 2 = Surface
		/// 3 = Docking
		/// </summary>
		public int HUDType
		{
			get { return scn.scnHUDType; }
			set
			{
				scn.scnHUDType = value;
				OnPropertyChanged( "HUDType" );
			}
		}

		/// <summary>
		/// List of Camera Mode options.
		/// </summary>
		public static string[] CameraMode_src{ get; } = { "Cockpit", "External" };

		/// <summary>
		/// Scenario camera mode
		/// 0 = Cockpit
		/// 1 = Extern
		/// </summary>
		public int CameraMode
		{
			get { return scn.scnCameraMode; }
			set
			{
				scn.scnCameraMode = value;

				if (value == 0)// Cockpit
				{
					CameraTrackMode_ena = false;
					CameraTrackMode = 0;

					CameraVesselRadius_ena = false;
					CameraPosPhi_ena = false;
					CameraPosTheta_ena = false;
				}
				else// Extern
				{
					CameraTrackMode_ena = true;
					CameraTrackMode = 0;

					CameraVesselRadius_ena = true;
					CameraPosPhi_ena = true;
					CameraPosTheta_ena = true;
				}

				OnPropertyChanged( "CameraMode" );
			}
		}

		/// <summary>
		/// List of Camera Track Mode options.
		/// </summary>
		public static string[] CameraTrackMode_src{ get; } = { "Target Relative", "Absolute Direction", "Global Frame", "Target To", "Target From", "Ground" };

		private bool cameratrackmode_ena;
		public bool CameraTrackMode_ena
		{
			get { return cameratrackmode_ena; }
			set
			{
				cameratrackmode_ena = value;
				OnPropertyChanged( "CameraTrackMode_ena" );
			}
		}

		/// <summary>
		/// Scenario camera track mode (for External camera mode only)
		/// 0 = Target Relative
		/// 1 = Absolute Direction
		/// 2 = Global Frame
		/// 3 = Target To
		/// 4 = Target From
		/// 5 = Ground
		/// </summary>
		public int CameraTrackMode
		{
			get { return scn.scnCameraTrackMode; }
			set
			{
				scn.scnCameraTrackMode = value;

				CameraPos_Update();

				OnPropertyChanged( "CameraTrackMode" );
			}
		}

		/// <summary>
		/// Scenario camera track mode reference (for Target To, Target From and Ground modes only)
		/// </summary>
		public string CameraTrackModeRef
		{
			get { return scn.scnCameraTrackModeRef; }
			set
			{
				scn.scnCameraTrackModeRef = value;
			}
		}

		private bool cameratrackmoderef_ena;
		public bool CameraTrackModeRef_ena
		{
			get { return cameratrackmoderef_ena; }
			set
			{
				cameratrackmoderef_ena = value;
				OnPropertyChanged( "CameraTrackModeRef_ena" );
			}
		}

		/// <summary>
		/// Scenario camera position (for External camera mode only)
		/// </summary>
		public double CameraVesselRadius
		{
			get { return scn.scnCameraVesselRadius; }
			set
			{
				if (value < 1.0) scn.scnCameraVesselRadius = 1.0;
				else scn.scnCameraVesselRadius = value;
				OnPropertyChanged( "scnCameraVesselRadius" );
			}
		}

		private bool cameravesselradius_ena;
		public bool CameraVesselRadius_ena
		{
			get { return cameravesselradius_ena; }
			set
			{
				cameravesselradius_ena = value;
				OnPropertyChanged( "CameraVesselRadius_ena" );
			}
		}

		public double CameraPosPhi
		{
			get { return scn.scnCameraPosPhi; }
			set
			{
				scn.scnCameraPosPhi = value;
				OnPropertyChanged( "CameraPosPhi" );
			}
		}

		private bool cameraposphi_ena;
		public bool CameraPosPhi_ena
		{
			get { return cameraposphi_ena; }
			set
			{
				cameraposphi_ena = value;
				OnPropertyChanged( "CameraPosPhi_ena" );
			}
		}

		private string cameraposphi_lbl;
		public string CameraPosPhi_lbl
		{
			get { return cameraposphi_lbl; }
			set
			{
				cameraposphi_lbl = value;
				OnPropertyChanged( "CameraPosPhi_lbl" );
			}
		}

		public double CameraPosTheta
		{
			get { return scn.scnCameraPosTheta; }
			set
			{
				scn.scnCameraPosTheta = value;
				OnPropertyChanged( "CameraPosTheta" );
			}
		}

		private bool camerapostheta_ena;
		public bool CameraPosTheta_ena
		{
			get { return camerapostheta_ena; }
			set
			{
				camerapostheta_ena = value;
				OnPropertyChanged( "CameraPosTheta_ena" );
			}
		}

		private string camerapostheta_lbl;
		public string CameraPosTheta_lbl
		{
			get { return camerapostheta_lbl; }
			set
			{
				camerapostheta_lbl = value;
				OnPropertyChanged( "CameraPosTheta_lbl" );
			}
		}

		public double CameraGrDirH
		{
			get { return scn.scnCameraGrDirH; }
			set
			{
				scn.scnCameraGrDirH = value;
				OnPropertyChanged( "CameraGrDirH" );
			}
		}

		private bool cameragrdirh_ena;
		public bool CameraGrDirH_ena
		{
			get { return cameragrdirh_ena; }
			set
			{
				cameragrdirh_ena = value;
				OnPropertyChanged( "CameraGrDirH_ena" );
			}
		}

		public double CameraGrDirV
		{
			get { return scn.scnCameraGrDirV; }
			set
			{
				scn.scnCameraGrDirV = value;
				OnPropertyChanged( "CameraGrDirV" );
			}
		}

		private bool cameragrdirv_ena;
		public bool CameraGrDirV_ena
		{
			get { return cameragrdirv_ena; }
			set
			{
				cameragrdirv_ena = value;
				OnPropertyChanged( "CameraGrDirV_ena" );
			}
		}

		/// <summary>
		/// Scenario camera field of view
		/// </summary>
		public double CameraFOV
		{
			get { return scn.scnCameraFOV; }
			set
			{
				scn.scnCameraFOV = value;
				OnPropertyChanged( "CameraFOV" );
			}
		}

		public double CameraGrPosLon
		{
			get { return scn.scnCameraGrPosLon; }
			set
			{
				scn.scnCameraGrPosLon = value;
				OnPropertyChanged( "CameraGrPosLon" );
			}
		}

		private bool cameragrposlon_ena;
		public bool CameraGrPosLon_ena
		{
			get { return cameragrposlon_ena; }
			set
			{
				cameragrposlon_ena = value;
				OnPropertyChanged( "CameraGrPosLon_ena" );
			}
		}

		public double CameraGrPosLat
		{
			get { return scn.scnCameraGrPosLat; }
			set
			{
				scn.scnCameraGrPosLat = value;
				OnPropertyChanged( "CameraGrPosLat" );
			}
		}

		private bool cameragrposlat_ena;
		public bool CameraGrPosLat_ena
		{
			get { return cameragrposlat_ena; }
			set
			{
				cameragrposlat_ena = value;
				OnPropertyChanged( "CameraGrPosLat_ena" );
			}
		}

		public double CameraGrPosAlt
		{
			get { return scn.scnCameraGrPosAlt; }
			set
			{
				scn.scnCameraGrPosAlt = value;
				OnPropertyChanged( "CameraGrPosAlt" );
			}
		}

		private bool cameragrposalt_ena;
		public bool CameraGrPosAlt_ena
		{
			get { return cameragrposalt_ena; }
			set
			{
				cameragrposalt_ena = value;
				OnPropertyChanged( "CameraGrPosAlt_ena" );
			}
		}

		public bool TargetLock
		{
			get { return scn.scnTargetLock; }
			set
			{
				scn.scnTargetLock = value;

				CameraGrDir_Update();

				OnPropertyChanged( "TargetLock" );
			}
		}

		private bool targetlock_ena;
		public bool TargetLock_ena
		{
			get { return targetlock_ena; }
			set
			{
				targetlock_ena = value;
				OnPropertyChanged( "TargetLock_ena" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		protected void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
			return;
		}
	}
}
