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


namespace SSVMissionEditor
{
	public class Mission_RMS
	{
		public Mission_RMS()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			SN = 202;

			Elbow = Defs.strCTVC_ITVC;
			Wrist = Defs.strCTVC_ITVC;

			ElbowIlluminator = true;
			WristIlluminator = true;
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
					if ((string)jelbowcam["Type"] == "-506/-508")
					{
						Elbow = Defs.str_506_508;
						ElbowIlluminator = false;
					}
					else if ((string)jelbowcam["Type"] == "CTVC/ITVC")
					{
						Elbow = Defs.strCTVC_ITVC;
						ElbowIlluminator = (bool)jelbowcam["Illuminator"];// illuminators only in CTVC/ITVC
					}
					else
					{
						Elbow = Defs.strCTVC_ITVC;
						ElbowIlluminator = false;
					}
				}

				JToken jwristcam = jcctvcam["Wrist"];
				if (jwristcam != null)
				{
					if ((string)jwristcam["Type"] == "-506/-508")
					{
						Wrist = Defs.str_506_508;
						WristIlluminator = false;
					}
					else if ((string)jwristcam["Type"] == "CTVC/ITVC")
					{
						Wrist = Defs.strCTVC_ITVC;
						WristIlluminator = (bool)jwristcam["Illuminator"];// illuminators only in CTVC/ITVC
					}
					else
					{
						Wrist = Defs.strCTVC_ITVC;
						WristIlluminator = false;
					}
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
						["Type"] = Elbow,
						["Illuminator"] = (Elbow == Defs.strCTVC_ITVC) ? ElbowIlluminator : false// illuminators only in CTVC/ITVC
					},
					["Wrist"] = new JObject()
					{
						["Type"] = Wrist,
						["Illuminator"] = (Wrist == Defs.strCTVC_ITVC) ? WristIlluminator : false// illuminators only in CTVC/ITVC
					}
				}
			};
			return jobj;
		}


		/// <summary>
		/// Serial number
		/// </summary>
		public int SN { get; set; }

		/// <summary>
		/// Elbow camera type
		/// </summary>
		public string Elbow { get; set; }

		/// <summary>
		/// Wrist camera type
		/// </summary>
		public string Wrist { get; set; }

		/// <summary>
		/// Is Illuminator installed in Elbow camera?
		/// </summary>
		public bool ElbowIlluminator { get; set; }

		/// <summary>
		/// Is Illuminator installed in Wrist camera?
		/// </summary>
		public bool WristIlluminator { get; set; }
	}
}
