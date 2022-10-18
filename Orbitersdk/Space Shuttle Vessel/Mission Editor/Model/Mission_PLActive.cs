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
			Latches = new Mission_PayloadLatch[/*Mission_OV.PAYLOADLATCH_MAX*/]
			{
				new Mission_PayloadLatch( true, 0 ),
				new Mission_PayloadLatch( true, 0 ),
				new Mission_PayloadLatch( true, 0 ),
				new Mission_PayloadLatch( true, 0 ),
				new Mission_PayloadLatch( true, 1 ),
				new Mission_PayloadLatch( true, 1 ),
				new Mission_PayloadLatch( true, 1 ),
				new Mission_PayloadLatch( true, 1 ),
				new Mission_PayloadLatch( true, 2 ),
				new Mission_PayloadLatch( true, 2 ),
				new Mission_PayloadLatch( true, 2 ),
				new Mission_PayloadLatch( true, 2 )
			};

			LoadDefault();
		}

		public void LoadDefault()
		{
			IsUsed = false;
			HasPayload = false;
			Payload.LoadDefault();

			for (int i = 0; i < Mission_OV.PAYLOADLATCH_MAX; i++)
			{
				Latches[i].LoadDefault();
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
				Latches[i].LoadEmpty();
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
				switch ((string)jpllatchlitem["Type"])
				{
					case "Port Longeron":
						if (portlatch < 3)
						{
							Latches[portlatch].Load_V1( jpllatchlitem );
							portlatch++;
						}
						else {}// TODO kaput
						break;
					case "Starboard Longeron":
						if (stbdlatch < 7)
						{
							Latches[stbdlatch].Load_V1( jpllatchlitem );
							stbdlatch++;
						}
						else {}// TODO kaput
						break;
					case "Keel":
						if (keellatch < 11)
						{
							Latches[keellatch].Load_V1( jpllatchlitem );
							keellatch++;
						}
						else {}// TODO kaput
						break;
					default:
						// TODO kaput
						break;
				}
			}

			JToken jpl = jtk["Payload"];
			if ((jpl != null) && (jpl.Type != JTokenType.Null))
			{
				Payload.Load_V1( jpl );
				HasPayload = true;
			}

			IsUsed = true;
			
			// validate IsAttachment (only one is allowed)
			// finds first latch with IsAttachment = true and sets rest to false
			int attachidx = -1;
			for (int i = 0; i < Mission_OV.PAYLOADLATCH_MAX; i++)
			{
				if (Latches[i].PLID == 0) continue;
				
				if (attachidx == -1)
				{
					// if no index yet, search for one
					if (Latches[i].IsAttachment)
					{
						attachidx = i;
					}
				}
				else
				{
					// if index already, clear following
					Latches[i].IsAttachment = false;
				}
			}
			return;
		}

		public JObject Save_V1()
		{
			if (!IsUsed) return null;

			JObject jobj = new JObject();

			JArray jlatches = new JArray();
			for (int j = 0; j < Mission_OV.PAYLOADLATCH_MAX; j++)
			{
				JObject jlatch = Latches[j].Save_V1();
				if (jlatch != null) jlatches.Add( jlatch );
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
		/// Latch array
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
		private Mission_PayloadLatch[] latches;
		public Mission_PayloadLatch[] Latches
		{
			get { return latches; }
			set
			{
				latches = value;
				OnPropertyChanged( "Latches" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
