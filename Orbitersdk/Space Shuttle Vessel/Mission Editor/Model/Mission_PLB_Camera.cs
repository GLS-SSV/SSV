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

using Newtonsoft.Json.Linq;
using SSVMissionEditor.model;
using System.Collections.Generic;
using System.ComponentModel;


namespace SSVMissionEditor
{
	public class Mission_PLB_Camera : INotifyPropertyChanged
	{
		public static readonly int KEEL_CAMERA_MAX = 1;// maximum number of keel cameras


		public Mission_PLB_Camera()
		{
			Installed = new bool[4];
			Type = new CCTV_Camera_Type[4];
			Illuminator = new bool[4];
			Custom = new bool[4];
			Xo = new double[4];
			Yo = new double[4];
			Zo = new double[4];
			Rot = new double[4];

			Keel_Installed = new bool[KEEL_CAMERA_MAX];
			Keel_Cameras = new int[KEEL_CAMERA_MAX];

			LoadDefault();
			return;
		}

		public void LoadDefault()
		{
			for (int i = 0; i < 4; i++)
			{
				Installed[i] = true;
				Type[i] = CCTV_Camera_Type.CTVC_ITVC;
				Illuminator[i] = true;
				Custom[i] = false;
				Xo[i] = 0.0;
				Yo[i] = 0.0;
				Zo[i] = 0.0;
				Rot[i] = 0.0;
			}

			for (int i = 0; i < KEEL_CAMERA_MAX; i++)
			{
				Keel_Installed[i] = false;
				Keel_Cameras[i] = 0;
			}
			return;
		}

		public void LoadEmpty()
		{
			LoadDefault();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			LoadCameras_V1( jtk, 0, "A" );
			LoadCameras_V1( jtk, 1, "B" );
			LoadCameras_V1( jtk, 2, "C" );
			LoadCameras_V1( jtk, 3, "D" );

			JToken jkeel = jtk["Keel"];
			if (jkeel != null)
			{
				int idx = 0;
				List<JToken> jkeellist = jkeel.ToObject<List<JToken>>();
				foreach (JToken jkeelcam in jkeellist)
				{
					if (idx >= KEEL_CAMERA_MAX) break;
					Keel_Cameras[idx] = (int)jkeelcam["PLID"];
					Keel_Installed[idx] = true;
					idx++;
				}
			}
			return;
		}

		public void Load_V2( JToken jtk )
		{
			Load_V1( jtk );
			return;
		}

		private void LoadCameras_V1( JToken jcctv, int camidx, string camname )
		{
			JToken jcctvcam = jcctv[camname];
			if (jcctvcam != null)
			{
				Installed[camidx] = (bool)jcctvcam["Installed"];
				if (Installed[camidx])
				{
					if ((string)jcctvcam["Type"] == "-506/-508")
					{
						Type[camidx] = CCTV_Camera_Type._506_508;
						Illuminator[camidx] = false;
					}
					else if ((string)jcctvcam["Type"] == "CTVC/ITVC")
					{
						Type[camidx] = CCTV_Camera_Type.CTVC_ITVC;
						Illuminator[camidx] = (bool)jcctvcam["Illuminator"];// illuminators only in CTVC/ITVC
					}
					else
					{
						Type[camidx] = CCTV_Camera_Type.CTVC_ITVC;
						Illuminator[camidx] = false;
					}

					JToken jcustom = jcctvcam["Custom"];
					if (jcustom != null)
					{
						Custom[camidx] = true;
						Xo[camidx] = (double)jcustom["Xo"];
						Yo[camidx] = (double)jcustom["Yo"];
						Zo[camidx] = (double)jcustom["Zo"];
						Rot[camidx] = (double)jcustom["Rot"];
					}
				}
			}
			return;
		}

		public JObject Save_V2()
		{
			JObject jcctv = new JObject();
			jcctv["A"] = SaveCameras_V2( 0 );
			jcctv["B"] = SaveCameras_V2( 1 );
			jcctv["C"] = SaveCameras_V2( 2 );
			jcctv["D"] = SaveCameras_V2( 3 );

			JArray jakeel = new JArray();
			if (Keel_Installed[0])
			{
				JObject jkeel = new JObject()
				{
					["PLID"] = Keel_Cameras[0]
				};
				jakeel.Add( jkeel );
			}
			jcctv["Keel"] = jakeel;
			return jcctv;
		}

		private JToken SaveCameras_V2( int camidx )
		{
			JObject jcam = new JObject()
			{
				["Installed"] = Installed[camidx]
			};

			if (Installed[camidx])
			{
				jcam["Type"] = ((Type[camidx] == CCTV_Camera_Type._506_508) ? "-506/-508" : "CTVC/ITVC");
				jcam["Illuminator"] = (Type[camidx] == CCTV_Camera_Type.CTVC_ITVC) ? Illuminator[camidx] : false;// illuminators only in CTVC/ITVC

				if (Custom[camidx])
				{
					JObject jcamcust = new JObject()
					{
						["Xo"] = Xo[camidx],
						["Yo"] = Yo[camidx],
						["Zo"] = Zo[camidx],
						["Rot"] = Rot[camidx]
					};
					jcam["Custom"] = jcamcust;
				}
			}
			return jcam;
		}


		/// <summary>
		/// Is camera installed?
		/// </summary>
		private bool[] installed;
		public bool[] Installed
		{
			get { return installed; }
			set
			{
				installed = value;
				OnPropertyChanged( "Installed" );
			}
		}

		/// <summary>
		/// Camera type
		/// </summary>
		private CCTV_Camera_Type[] type;
		public CCTV_Camera_Type[] Type
		{
			get { return type; }
			set
			{
				type = value;
				OnPropertyChanged( "Type" );
			}
		}

		/// <summary>
		/// Is Illuminator installed in camera?
		/// </summary>
		private bool[] illuminator;
		public bool[] Illuminator
		{
			get { return illuminator; }
			set
			{
				illuminator = value;
				OnPropertyChanged( "Illuminator" );
			}
		}

		/// <summary>
		/// Does camera have custom coordinates?
		/// </summary>
		private bool[] custom;
		public bool[] Custom
		{
			get { return custom; }
			set
			{
				custom = value;
				OnPropertyChanged( "Custom" );
			}
		}

		/// <summary>
		/// Custom Xo coordinate
		/// </summary>
		private double[] xo;
		public double[] Xo
		{
			get { return xo; }
			set
			{
				xo = value;
				OnPropertyChanged( "Xo" );
			}
		}

		/// <summary>
		/// Custom Xo coordinate
		/// </summary>
		private double[] yo;
		public double[] Yo
		{
			get { return yo; }
			set
			{
				yo = value;
				OnPropertyChanged( "Yo" );
			}
		}

		/// <summary>
		/// Custom Xo coordinate
		/// </summary>
		private double[] zo;
		public double[] Zo
		{
			get { return zo; }
			set
			{
				zo = value;
				OnPropertyChanged( "Zo" );
			}
		}

		/// <summary>
		/// Custom Xo coordinate
		/// </summary>
		private double[] rot;
		public double[] Rot
		{
			get { return rot; }
			set
			{
				rot = value;
				OnPropertyChanged( "Rot" );
			}
		}

		/// <summary>
		/// Is keel camera installed?
		/// </summary>
		private bool[] keel_installed;
		public bool[] Keel_Installed
		{
			get { return keel_installed; }
			set
			{
				keel_installed = value;
				OnPropertyChanged( "Keel_Installed" );
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


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
