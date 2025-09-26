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
using System.Collections.Generic;


namespace SSVMissionEditor
{
	public class Mission_PLB_Camera
	{
		public static readonly int KEEL_CAMERA_MAX = 1;// maximum number of keel cameras


		public Mission_PLB_Camera()
		{
			Installed = new bool[4];
			Type = new string[4];
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
				Type[i] = Defs.strCTVC_ITVC;
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
						Type[camidx] = Defs.str_506_508;
						Illuminator[camidx] = false;
					}
					else if ((string)jcctvcam["Type"] == "CTVC/ITVC")
					{
						Type[camidx] = Defs.strCTVC_ITVC;
						Illuminator[camidx] = (bool)jcctvcam["Illuminator"];// illuminators only in CTVC/ITVC
					}
					else
					{
						Type[camidx] = Defs.strCTVC_ITVC;
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

		public JObject Save_V1()
		{
			JObject jcctv = new JObject();
			jcctv["A"] = SaveCameras_V1( 0 );
			jcctv["B"] = SaveCameras_V1( 1 );
			jcctv["C"] = SaveCameras_V1( 2 );
			jcctv["D"] = SaveCameras_V1( 3 );

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

		private JToken SaveCameras_V1( int camidx )
		{
			JObject jcam = new JObject()
			{
				["Installed"] = Installed[camidx]
			};

			if (Installed[camidx])
			{
				jcam["Type"] = Type[camidx];
				jcam["Illuminator"] = (Type[camidx] == Defs.strCTVC_ITVC) ? Illuminator[camidx] : false;// illuminators only in CTVC/ITVC

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
		public bool[] Installed { get; set; }

		/// <summary>
		/// Camera type
		/// </summary>
		public string[] Type { get; set; }

		/// <summary>
		/// Is Illuminator installed in camera?
		/// </summary>
		public bool[] Illuminator { get; set; }

		/// <summary>
		/// Does camera have custom coordinates?
		/// </summary>
		public bool[] Custom { get; set; }

		/// <summary>
		/// Custom Xo coordinate
		/// </summary>
		public double[] Xo { get; set; }

		/// <summary>
		/// Custom Yo coordinate
		/// </summary>
		public double[] Yo { get; set; }

		/// <summary>
		/// Custom Zo coordinate
		/// </summary>
		public double[] Zo { get; set; }

		/// <summary>
		/// Custom rotation [deg]
		/// </summary>
		public double[] Rot { get; set; }

		/// <summary>
		/// Is keel camera installed?
		/// </summary>
		public bool[] Keel_Installed { get; set; }

		/// <summary>
		/// List of PLIDs of keel cameras
		/// </summary>
		public int[] Keel_Cameras { get; set; }
	}
}
