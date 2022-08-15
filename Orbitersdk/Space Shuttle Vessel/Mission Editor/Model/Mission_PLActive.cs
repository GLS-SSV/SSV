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

using System.Collections.Generic;
using System.ComponentModel;
using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.model
{
	public class Mission_PLActive : INotifyPropertyChanged
	{
		public Mission_PLActive()
		{
			Payload = new Mission_Payload();
			PLID = new int[Mission_OV.PAYLOADLATCH_MAX];
			IsAttachment = new bool[Mission_OV.PAYLOADLATCH_MAX];
			Latch = new int[Mission_OV.PAYLOADLATCH_MAX];
			Reversed = new bool[Mission_OV.PAYLOADLATCHLONGERONSILL_MAX];
			ForwardGuide = new int[Mission_OV.PAYLOADLATCHLONGERONSILL_MAX];
			AftGuide = new int[Mission_OV.PAYLOADLATCHLONGERONSILL_MAX];

			LoadDefault();
		}

		public void LoadDefault()
		{
			IsUsed = false;
			HasPayload = false;
			Payload.LoadDefault();

			for (int i = 0; i < Mission_OV.PAYLOADLATCH_MAX; i++)
			{
				PLID[i] = 0;
				IsAttachment[i] = false;
				Latch[i] = 0;
			}

			for (int i = 0; i < Mission_OV.PAYLOADLATCHLONGERONSILL_MAX; i++)
			{
				Reversed[i] = false;
				ForwardGuide[i] = 0;
				AftGuide[i] = 0;
			}
			return;
		}

		public void LoadEmpty()
		{
			IsUsed = false;
			HasPayload = false;
			Payload.LoadEmpty();

			for (int i = 0; i < Mission_OV.PAYLOADLATCH_MAX; i++)
			{
				PLID[i] = 0;
				IsAttachment[i] = false;
				Latch[i] = 0;
			}

			for (int i = 0; i < Mission_OV.PAYLOADLATCHLONGERONSILL_MAX; i++)
			{
				Reversed[i] = false;
				ForwardGuide[i] = 0;
				AftGuide[i] = 0;
			}
			return;
		}

		public void Load_V1( JToken jtk )
		{
			// run latches
			JToken jactive = jtk["Active"];
			List<JToken> jpllatchl = jactive.ToObject<List<JToken>>();
			int portlatch = 0;
			int stbdlatch = 4;
			int keellatch = 8;
			foreach (JToken jpllatchlitem in jpllatchl)
			{
				int latchidx = 0;
				switch ((string)jpllatchlitem["Type"])
				{
					case "Port Longeron":
						{
							latchidx = portlatch;
							if (portlatch < 3) portlatch++;

							Reversed[latchidx] = (bool)jpllatchlitem["Reversed"];

							string fwdguidestr = (string)jpllatchlitem["Forward Guide"];
							if (fwdguidestr == "None") ForwardGuide[latchidx] = 0;
							else if (fwdguidestr == "22''") ForwardGuide[latchidx] = 1;
							else if (fwdguidestr == "24''") ForwardGuide[latchidx] = 2;

							string aftguidestr = (string)jpllatchlitem["Aft Guide"];
							if (aftguidestr == "None") AftGuide[latchidx] = 0;
							else if (aftguidestr == "22''") AftGuide[latchidx] = 1;
							else if (aftguidestr == "24''") AftGuide[latchidx] = 2;
						}
						break;
					case "Starboard Longeron":
						{
							latchidx = stbdlatch;
							if (stbdlatch < 7) stbdlatch++;

							Reversed[latchidx] = (bool)jpllatchlitem["Reversed"];

							string fwdguidestr = (string)jpllatchlitem["Forward Guide"];
							if (fwdguidestr == "None") ForwardGuide[latchidx] = 0;
							else if (fwdguidestr == "22''") ForwardGuide[latchidx] = 1;
							else if (fwdguidestr == "24''") ForwardGuide[latchidx] = 2;

							string aftguidestr = (string)jpllatchlitem["Aft Guide"];
							if (aftguidestr == "None") AftGuide[latchidx] = 0;
							else if (aftguidestr == "22''") AftGuide[latchidx] = 1;
							else if (aftguidestr == "24''") AftGuide[latchidx] = 2;
						}
						break;
					case "Keel":
						latchidx = keellatch;
						if (keellatch < 11) keellatch++;
						break;
					default:
						// TODO kaput
						break;
				}
				PLID[latchidx] = (int)jpllatchlitem["PLID"];
				// TODO clear other true values (or change bool array to int?)
				IsAttachment[latchidx] = (bool)jpllatchlitem["Attachment"];
				JToken jpllatchlitempll = jpllatchlitem["Payload Latch"];
				int pl = (int)jpllatchlitempll["Payload"];
				int ltch = (int)jpllatchlitempll["Latch"];
				Latch[latchidx] = ((pl - 1) * 5) + ltch - 1;
			}

			JToken jpl = jtk["Payload"];
			if ((jpl != null) && (jpl.Type != JTokenType.Null))
			{
				Payload.Load_V1( jpl );
				HasPayload = true;
			}

			IsUsed = true;
			return;
		}

		public JObject Save_V1()
		{
			if (!IsUsed) return null;

			JObject jobj = new JObject();

			JArray jlatches = new JArray();
			for (int j = 0; j < Mission_OV.PAYLOADLATCH_MAX; j++)
			{
				if (PLID[j] > 0)
				{
					JObject jlatch = new JObject();
					JObject jplltch = new JObject();
					int pl = (Latch[j] / 5) + 1;
					int ltch = (Latch[j] - (5 * (pl - 1))) + 1;
					jplltch["Payload"] = pl;
					jplltch["Latch"] = ltch;

					if ((j == 0) || (j == 1) || (j == 2) || (j == 3))
					{
						jlatch["Type"] = "Port Longeron";
						jlatch["PLID"] = PLID[j];

						jlatch["Attachment"] = IsAttachment[j];
						jlatch["Payload Latch"] = jplltch;

						jlatch["Reversed"] = Reversed[j];

						if (ForwardGuide[j] == 1) jlatch["Forward Guide"] = "22''";
						else if (ForwardGuide[j] == 2) jlatch["Forward Guide"] = "24''";
						else /*if (ForwardGuide[j] == 0)*/ jlatch["Forward Guide"] = "None";

						if (AftGuide[j] == 1) jlatch["Aft Guide"] = "22''";
						else if (AftGuide[j] == 2) jlatch["Aft Guide"] = "24''";
						else /*if (AftGuide[j] == 0)*/ jlatch["Aft Guide"] = "None";
						jlatches.Add( jlatch );

					}
					else if ((j == 4) || (j == 5) || (j == 6) || (j == 7))
					{
						jlatch["Type"] = "Starboard Longeron";
						jlatch["PLID"] = PLID[j];

						jlatch["Attachment"] = IsAttachment[j];
						jlatch["Payload Latch"] = jplltch;

						jlatch["Reversed"] = Reversed[j];

						if (ForwardGuide[j] == 1) jlatch["Forward Guide"] = "22''";
						else if (ForwardGuide[j] == 2) jlatch["Forward Guide"] = "24''";
						else /*if (ForwardGuide[j] == 0)*/ jlatch["Forward Guide"] = "None";

						if (AftGuide[j] == 1) jlatch["Aft Guide"] = "22''";
						else if (AftGuide[j] == 2) jlatch["Aft Guide"] = "24''";
						else /*if (AftGuide[j] == 0)*/ jlatch["Aft Guide"] = "None";
						jlatches.Add( jlatch );
					}
					else /*if ((j == 8) || (j == 9) || (j == 10) || (j == 11))*/
					{
						jlatch["Type"] = "Keel";
						jlatch["PLID"] = PLID[j];

						jlatch["Attachment"] = IsAttachment[j];
						jlatch["Payload Latch"] = jplltch;
						jlatches.Add( jlatch );
					}
				}
			}
			jobj["Active"] = jlatches;

			if (HasPayload) jobj["Payload"] = Payload.Save_V1();
			else jobj["Payload"] = null;
			return jobj;
		}


		/// <summary>
		/// Is attachment used
		/// </summary>
		private bool isused;
		public bool IsUsed
		{
			get { return isused; }
			set
			{
				isused = value;
				OnPropertyChanged( "IsUsed" );
			}
		}

		/// <summary>
		/// Is Payload installed at launch
		/// </summary>
		private bool haspayload;
		public bool HasPayload
		{
			get { return haspayload; }
			set
			{
				haspayload = value;
				OnPropertyChanged( "HasPayload" );
			}
		}

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
				OnPropertyChanged( "Payload" );
			}
		}

		/// <summary>
		/// PLID array
		/// 0	port 1
		/// 1	port 2
		/// 2	port 3
		/// 3	port 4
		/// 4	stbd 1
		/// 5	stbd 2
		/// 6	stbd 3
		/// 7	stbd 4
		/// 8	keel 1
		/// 9	keel 2
		/// 10	keel 3
		/// 11	keel 4
		/// </summary>
		private int[] plid;
		public int[] PLID
		{
			get { return plid; }
			set
			{
				plid = value;
				OnPropertyChanged( "PLID" );
			}
		}

		/// <summary>
		/// Is PLID attachment array
		/// </summary>
		private bool[] isattachment;
		public bool[] IsAttachment
		{
			get { return isattachment; }
			set
			{
				isattachment = value;
				OnPropertyChanged( "IsAttachment" );
			}
		}

		/// <summary>
		/// Latch info array
		/// </summary>
		private int[] latch;
		public int[] Latch
		{
			get { return latch; }
			set
			{
				latch = value;
				OnPropertyChanged( "Latch" );
			}
		}

		/// <summary>
		/// Is PRLA reversed?
		/// </summary>
		private bool[] reversed;
		public bool[] Reversed
		{
			get { return reversed; }
			set
			{
				reversed = value;
				OnPropertyChanged( "Reversed" );
			}
		}

		/// <summary>
		/// Forward Guide type array
		/// </summary>
		private int[] fwdguide;
		public int[] ForwardGuide
		{
			get { return fwdguide; }
			set
			{
				fwdguide = value;
				OnPropertyChanged( "ForwardGuide" );
			}
		}

		/// <summary>
		/// Aft Guide type array
		/// </summary>
		private int[] aftguide;
		public int[] AftGuide
		{
			get { return aftguide; }
			set
			{
				aftguide = value;
				OnPropertyChanged( "AftGuide" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
