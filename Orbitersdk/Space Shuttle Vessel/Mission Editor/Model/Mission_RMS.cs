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
using System.ComponentModel;


namespace SSVMissionEditor
{
	public class Mission_RMS : INotifyPropertyChanged
	{
		public Mission_RMS()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			SN = 202;

			Elbow = CCTV_Camera_Type.CTVC_ITVC;
			Wrist = CCTV_Camera_Type.CTVC_ITVC;
			return;
		}

		public void LoadEmpty()
		{
			LoadDefault();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			SN = (int)jtk["SN"];

			JToken jcctvcam = jtk["Cameras"];
			if (jcctvcam != null)
			{
				JToken jelbowcam = jcctvcam["Elbow"];
				if (jelbowcam != null)
				{
					if ((string)jelbowcam["Type"] == "-506/-508") Elbow = CCTV_Camera_Type._506_508;
					else Elbow = CCTV_Camera_Type.CTVC_ITVC;
				}

				JToken jwristcam = jcctvcam["Wrist"];
				if (jwristcam != null)
				{
					if ((string)jwristcam["Type"] == "-506/-508") Wrist = CCTV_Camera_Type._506_508;
					else Wrist = CCTV_Camera_Type.CTVC_ITVC;
				}
			}
			return;
		}

		public JObject Save_V1()
		{
			JObject jobj = new JObject()
			{
				["SN"] = SN,
				["Cameras"] = new JObject()
				{
					["Elbow"] = new JObject()
					{
						["Type"] = ((Elbow == CCTV_Camera_Type._506_508) ? "-506/-508" : "CTVC/ITVC")
					},
					["Wrist"] = new JObject()
					{
						["Type"] = ((Wrist == CCTV_Camera_Type._506_508) ? "-506/-508" : "CTVC/ITVC")
					}
				}
			};
			return jobj;
		}

		/// <summary>
		/// Serial number
		/// </summary>
		private int sn;
		public int SN
		{
			get { return sn; }
			set
			{
				sn = value;
				OnPropertyChanged( "SN" );
			}
		}

		/// <summary>
		/// Elbow camera type
		/// </summary>
		private CCTV_Camera_Type elbow;
		public CCTV_Camera_Type Elbow
		{
			get { return elbow; }
			set
			{
				elbow = value;
				OnPropertyChanged( "Elbow" );
			}
		}

		/// <summary>
		/// Wrist camera type
		/// </summary>
		private CCTV_Camera_Type wrist;
		public CCTV_Camera_Type Wrist
		{
			get { return wrist; }
			set
			{
				wrist = value;
				OnPropertyChanged( "Wrist" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
