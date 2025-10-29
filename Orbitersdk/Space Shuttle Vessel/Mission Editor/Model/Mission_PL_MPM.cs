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
using SSVMissionEditor.Model;


namespace SSVMissionEditor
{
	public enum MRL_Type
	{
		None = 0,
		Forward,
		Mid,
		Aft
	}

	public enum MPM_Attachment_Type
	{
		Shoulder = 0,
		Forward,
		Mid,
		Aft
	}


	public class Mission_PL_MPM
	{
		public Mission_PL_MPM()
		{
			Payload = new Mission_Payload();
			LoadDefault();
		}

		public void LoadDefault()
		{
			Attachment = MPM_Attachment_Type.Forward;

			HasShoulder = false;
			HasForward = false;
			HasMid = false;
			HasAft = false;

			ShoulderMesh = "";
			ForwardMesh = "";
			MidMesh = "";
			AftMesh = "";

			ShoulderPedestalMRL = MRL_Type.None;
			ForwardPedestalMRL = MRL_Type.Forward;
			MidPedestalMRL = MRL_Type.Mid;
			AftPedestalMRL = MRL_Type.Aft;


			HasPayload = false;
			Payload.LoadDefault();
			return;
		}

		public void LoadEmpty()
		{
			Attachment = MPM_Attachment_Type.Forward;

			HasShoulder = false;
			HasForward = false;
			HasMid = false;
			HasAft = false;

			ShoulderMesh = "";
			ForwardMesh = "";
			MidMesh = "";
			AftMesh = "";

			ShoulderPedestalMRL = MRL_Type.None;
			ForwardPedestalMRL = MRL_Type.Forward;
			MidPedestalMRL = MRL_Type.Mid;
			AftPedestalMRL = MRL_Type.Aft;

			HasPayload = false;
			Payload.LoadEmpty();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			JToken jpedestals = jtk["Pedestals"];

			{
				string strtmp = (string)jpedestals["Attachment"];
				int inttmp = Mission.String2EnumIdx( Attachment, strtmp );
				if (inttmp >= 0) Attachment = (MPM_Attachment_Type)inttmp;
				else Attachment = MPM_Attachment_Type.Forward;
			}

			JToken jpedestal;
			jpedestal = jpedestals["Shoulder"];
			if ((jpedestal != null) && (jpedestal.Type != JTokenType.Null))
			{
				HasShoulder = true;
				ShoulderMesh = (string)jpedestal["Mesh"];
				{
					string strtmp = (string)jpedestal["MRL"];
					int inttmp = Mission.String2EnumIdx( ShoulderPedestalMRL, strtmp );
					if (inttmp >= 0) ShoulderPedestalMRL = (MRL_Type)inttmp;
					else ShoulderPedestalMRL = MRL_Type.None;
				}
			}

			jpedestal = jpedestals["Forward"];
			if ((jpedestal != null) && (jpedestal.Type != JTokenType.Null))
			{
				HasForward = true;
				ForwardMesh = (string)jpedestal["Mesh"];
				{
					string strtmp = (string)jpedestal["MRL"];
					int inttmp = Mission.String2EnumIdx( ForwardPedestalMRL, strtmp );
					if (inttmp >= 0) ForwardPedestalMRL = (MRL_Type)inttmp;
					else ForwardPedestalMRL = MRL_Type.Forward;
				}
			}

			jpedestal = jpedestals["Mid"];
			if ((jpedestal != null) && (jpedestal.Type != JTokenType.Null))
			{
				HasMid = true;
				MidMesh = (string)jpedestal["Mesh"];
				{
					string strtmp = (string)jpedestal["MRL"];
					int inttmp = Mission.String2EnumIdx( MidPedestalMRL, strtmp );
					if (inttmp >= 0) MidPedestalMRL = (MRL_Type)inttmp;
					else MidPedestalMRL = MRL_Type.Mid;
				}
			}

			jpedestal = jpedestals["Aft"];
			if ((jpedestal != null) && (jpedestal.Type != JTokenType.Null))
			{
				HasAft = true;
				AftMesh = (string)jpedestal["Mesh"];
				{
					string strtmp = (string)jpedestal["MRL"];
					int inttmp = Mission.String2EnumIdx( AftPedestalMRL, strtmp );
					if (inttmp >= 0) AftPedestalMRL = (MRL_Type)inttmp;
					else AftPedestalMRL = MRL_Type.Aft;
				}
			}

			JToken jpl = jtk["Payload"];
			if ((jpl != null) && (jpl.Type != JTokenType.Null))
			{
				Payload.Load_V1( jpl );
				HasPayload = true;
			}
			return;
		}

		public JObject Save_V1()
		{
			JObject jobj = new JObject();

			JObject jpedestals = new JObject();
			jpedestals["Attachment"] = Attachment.ToString();

			if (HasShoulder)
			{
				JObject jpedestal = new JObject
				{
					["Mesh"] = ShoulderMesh,
					["MRL"] = ShoulderPedestalMRL.ToString()
				};
				jpedestals["Shoulder"] = jpedestal;
			}
			else jpedestals["Shoulder"] = null;

			if (HasForward)
			{
				JObject jpedestal = new JObject
				{
					["Mesh"] = ForwardMesh,
					["MRL"] = ForwardPedestalMRL.ToString()
				};
				jpedestals["Forward"] = jpedestal;
			}
			else jpedestals["Forward"] = null;

			if (HasMid)
			{
				JObject jpedestal = new JObject
				{
					["Mesh"] = MidMesh,
					["MRL"] = MidPedestalMRL.ToString()
				};
				jpedestals["Mid"] = jpedestal;
			}
			else jpedestals["Mid"] = null;

			if (HasAft)
			{
				JObject jpedestal = new JObject
				{
					["Mesh"] = AftMesh,
					["MRL"] = AftPedestalMRL.ToString()
				};
				jpedestals["Aft"] = jpedestal;
			}
			else jpedestals["Aft"] = null;

			jobj["Pedestals"] = jpedestals;

			if (HasPayload) jobj["Payload"] = Payload.Save_V1();
			else jobj["Payload"] = null;

			return jobj;
		}

		/// <summary>
		/// Attachment Pedestal
		/// </summary>
		public MPM_Attachment_Type Attachment { get; set; }

		/// <summary>
		/// Is the Shoulder Pedestal installed
		/// </summary>
		public bool HasShoulder { get; set; }

		/// <summary>
		/// Is the Forward Pedestal installed
		/// </summary>
		public bool HasForward { get; set; }

		/// <summary>
		/// Is the Mid Pedestal installed
		/// </summary>
		public bool HasMid { get; set; }

		/// <summary>
		/// Is the Aft Pedestal installed
		/// </summary>
		public bool HasAft { get; set; }

		/// <summary>
		/// Mesh file for Shoulder Upper Pedestal
		/// </summary>
		public string ShoulderMesh { get; set; }

		/// <summary>
		/// Mesh file for Forward Upper Pedestal
		/// </summary>
		public string ForwardMesh { get; set; }

		/// <summary>
		/// Mesh file for Mid Upper Pedestal
		/// </summary>
		public string MidMesh { get; set; }

		/// <summary>
		/// Mesh file for Aft Upper Pedestal
		/// </summary>«
		public string AftMesh { get; set; }

		/// <summary>
		/// MRL latch for Shoulder Pedestal
		/// </summary>
		public MRL_Type ShoulderPedestalMRL { get; set; }

		/// <summary>
		/// MRL latch for Forward Pedestal
		/// </summary>
		public MRL_Type ForwardPedestalMRL { get; set; }

		/// <summary>
		/// MRL latch for Mid Pedestal
		/// </summary>
		public MRL_Type MidPedestalMRL { get; set; }

		/// <summary>
		/// MRL latch for Aft Pedestal
		/// </summary>
		public MRL_Type AftPedestalMRL { get; set; }


		/// <summary>
		/// Is Payload installed at launch
		/// </summary>
		public bool HasPayload { get; set; }

		/// <summary>
		/// Payload installed in attachment
		/// </summary>
		private Mission_Payload payload;
		public Mission_Payload Payload
		{
			get { return payload; }
			set
			{
				payload = value;
			}
		}
	}
}
