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
using Newtonsoft.Json.Linq;


namespace SSVMissionEditor.model
{
	public enum Bridge_Type
{
		Port = 0,
		Starboard,
		Keel
	}

	public class Mission_PLBayBridge : INotifyPropertyChanged
	{
		public Mission_PLBayBridge()
		{
			Payload = new Mission_Payload();
			LoadDefault();
		}

		public void LoadDefault()
		{
			IsUsed = false;
			Payload.LoadDefault();
			Bay = 1;
			Bridge = Bridge_Type.Port;
			return;
		}

		public void LoadEmpty()
		{
			IsUsed = false;
			Payload.LoadEmpty();
			Bay = 1;
			Bridge = Bridge_Type.Port;
			return;
		}

		public void Load_V1( JToken jtk )
		{
			JToken jbaybridge = jtk["Bay Bridge"];

			Bay = (int)jbaybridge["Bay"];

			string strtmp = (string)jbaybridge["Bridge"];
			int inttmp = Mission.String2EnumIdx( Bridge, strtmp );
			if (inttmp >= 0) Bridge = (Bridge_Type)inttmp;
			else Bridge = Bridge_Type.Port;

			Payload.Load_V1( jtk.SelectToken( "Payload" ) );

			IsUsed = true;
			return;
		}

		public JObject Save_V1()
		{
			if (!IsUsed) return null;

			JObject jobj = new JObject();

			JObject jobj2 = new JObject();
			jobj2["Bay"] = bay;
			jobj2["Bridge"] = Bridge.ToString();
			jobj["Bay Bridge"] = jobj2;

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
		/// Is attachment used
		/// </summary>
		private int bay;
		public int Bay
		{
			get { return bay; }
			set
			{
				bay = value;
				OnPropertyChanged( "Bay" );
			}
		}

		/// <summary>
		/// Location of attachment
		/// </summary>
		private Bridge_Type bridge;
		public Bridge_Type Bridge
		{
			get { return bridge; }
			set
			{
				bridge = value;
				OnPropertyChanged( "Bridge" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
