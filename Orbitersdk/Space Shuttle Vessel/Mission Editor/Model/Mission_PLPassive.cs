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
	public class Mission_PLPassive : INotifyPropertyChanged
	{
		public Mission_PLPassive()
		{
			Payload = new Mission_Payload();
			PLID = new int[Mission_OV.PAYLOADLATCH_MAX];
			IsAttachment = new bool[Mission_OV.PAYLOADLATCH_MAX];
			Reversed = new bool[Mission_OV.PAYLOADLATCHLONGERONSILL_MAX];

			LoadDefault();
		}

		public void LoadDefault()
		{
			IsUsed = false;
			Payload.LoadDefault();

			for (int i = 0; i < Mission_OV.PAYLOADLATCH_MAX; i++)
			{
				PLID[i] = 0;
				IsAttachment[i] = false;
			}

			for (int i = 0; i < Mission_OV.PAYLOADLATCHLONGERONSILL_MAX; i++)
			{
				Reversed[i] = false;
			}
			return;
		}

		public void LoadEmpty()
		{
			IsUsed = false;
			Payload.LoadEmpty();

			for (int i = 0; i < Mission_OV.PAYLOADLATCH_MAX; i++)
			{
				PLID[i] = 0;
				IsAttachment[i] = false;
			}

			for (int i = 0; i < Mission_OV.PAYLOADLATCHLONGERONSILL_MAX; i++)
			{
				Reversed[i] = false;
			}
			return;
		}

		public void Load_V1( JToken jtk )
		{
			// run latches
			JToken jpassive = jtk["Passive"];
			List<JToken> jpllatchl = jpassive.ToObject<List<JToken>>();
			int portlatch = 0;
			int stbdlatch = 4;
			int keellatch = 8;
			foreach (JToken jpllatchlitem in jpllatchl)
			{
				int latchidx = 0;
				switch ((string)jpllatchlitem["Type"])
				{
					case "Port Longeron":
						latchidx = portlatch;
						if (portlatch < 3) portlatch++;

						Reversed[latchidx] = (bool)jpllatchlitem["Reversed"];
						break;
					case "Starboard Longeron":
						latchidx = stbdlatch;
						if (stbdlatch < 7) stbdlatch++;

						Reversed[latchidx] = (bool)jpllatchlitem["Reversed"];
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
			}

			Payload.Load_V1( jtk["Payload"] );

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
					if ((j == 0) || (j == 1) || (j == 2) || (j == 3))
					{
						jlatch["Type"] = "Port Longeron";
						jlatch["PLID"] = PLID[j];

						jlatch["Reversed"] = Reversed[j];
					}
					else if ((j == 4) || (j == 5) || (j == 6) || (j == 7))
					{
						jlatch["Type"] = "Starboard Longeron";
						jlatch["PLID"] = PLID[j];

						jlatch["Reversed"] = Reversed[j];
					}
					else /*if ((j == 8) || (j == 9) || (j == 10) || (j == 11))*/
					{
						jlatch["Type"] = "Keel";
						jlatch["PLID"] = PLID[j];
					}
					jlatch["Attachment"] = IsAttachment[j];
					jlatches.Add( jlatch );
				}
			}
			jobj["Passive"] = jlatches;

			jobj["Payload"] = Payload.Save_V1();
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


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
