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
	public class Mission_PayloadLatch : INotifyPropertyChanged
	{
		/// <summary>
		/// latchtype:
		/// 0 = Active
		/// 1 = Passive
		/// 2 = SPDS
		/// 
		/// type:
		/// 0 = Port Longeron
		/// 1 = Starboard Longeron
		/// 2 = Keel
		/// </summary>
		public Mission_PayloadLatch( int latchtype, int type )
		{
			this.latchtype = latchtype;
			this.type = type;

			PLID = 0;
			IsAttachment = false;
			Latch = 0;
			Reversed = false;
			ForwardGuide = 0;
			AftGuide = 0;
		}

		public void LoadDefault()
		{
			PLID = 0;
			IsAttachment = false;
			Latch = 0;
			Reversed = false;
			ForwardGuide = 0;
			AftGuide = 0;
			return;
		}

		public void LoadEmpty()
		{
			LoadDefault();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			// TODO confirm type?
			//// "Type": "Starboard Longeron"

			PLID = (int)jtk["PLID"];

			if (type < 2) Reversed = (bool)jtk["Reversed"];

			if (latchtype != 2) IsAttachment = (bool)jtk["Attachment"];
			
			if (latchtype == 0)
			{
				JToken jtkpll = jtk["Payload Latch"];
				int pl = (int)jtkpll["Payload"];
				int ltch = (int)jtkpll["Latch"];
				Latch = ((pl - 1) * 5) + ltch - 1;
			}

			if (type < 2)
			{
				string fwdguidestr = (string)jtk["Forward Guide"];
				if (fwdguidestr == "None") ForwardGuide = 0;
				else if (fwdguidestr == "22''") ForwardGuide = 1;
				else if (fwdguidestr == "24''") ForwardGuide = 2;

				string aftguidestr = (string)jtk["Aft Guide"];
				if (aftguidestr == "None") AftGuide = 0;
				else if (aftguidestr == "22''") AftGuide = 1;
				else if (aftguidestr == "24''") AftGuide = 2;
			}
			return;
		}

		public void Load_V2( JToken jtk )
		{
			Load_V1( jtk );
			return;
		}

		public JObject Save_V2()
		{
			if (PLID == 0) return null;

			JObject jobj = new JObject();

			if (type == 0) jobj["Type"] = PORT_LATCH;
			else if (type == 1) jobj["Type"] = STBD_LATCH;
			else /*if (type == 2)*/ jobj["Type"] = KEEL_LATCH;

			jobj["PLID"] = PLID;

			if (type < 2) jobj["Reversed"] = Reversed;

			if (latchtype != 2) jobj["Attachment"] = IsAttachment;

			if (latchtype == 0)
			{
				JObject jplltch = new JObject();
				int pl = (Latch / 5) + 1;
				int ltch = (Latch - (5 * (pl - 1))) + 1;
				jplltch["Payload"] = pl;
				jplltch["Latch"] = ltch;
				jobj["Payload Latch"] = jplltch;
			}

			if ((type < 2) && (latchtype == 0))
			{
				if (ForwardGuide == 1) jobj["Forward Guide"] = "22''";
				else if (ForwardGuide == 2) jobj["Forward Guide"] = "24''";
				else /*if (ForwardGuide == 0)*/ jobj["Forward Guide"] = "None";

				if (AftGuide == 1) jobj["Aft Guide"] = "22''";
				else if (AftGuide == 2) jobj["Aft Guide"] = "24''";
				else /*if (AftGuide == 0)*/ jobj["Aft Guide"] = "None";
			}
			return jobj;
		}


		private const string PORT_LATCH = "Port Longeron";
		private const string STBD_LATCH = "Starboard Longeron";
		private const string KEEL_LATCH = "Keel";

		/// <summary>
		/// 0 = Active
		/// 1 = Passive
		/// 2 = SPDS
		/// </summary>
		private int latchtype;

		/// <summary>
		/// 0 = Port Longeron
		/// 1 = Starboard Longeron
		/// 2 = Keel
		/// </summary>
		private int type;


		/// <summary>
		/// PLID
		/// </summary>
		private int plid;
		public int PLID
		{
			get { return plid; }
			set
			{
				plid = value;
				OnPropertyChanged( "PLID" );
			}
		}

		/// <summary>
		/// Is attachment?
		/// </summary>
		private bool isattachment;
		public bool IsAttachment
		{
			get { return isattachment; }
			set
			{
				isattachment = value;
				OnPropertyChanged( "IsAttachment" );
			}
		}

		/// <summary>
		/// PRLA drive system
		/// </summary>
		private int latch;
		public int Latch
		{
			get { return latch; }
			set
			{
				latch = value;
				OnPropertyChanged( "Latch" );
			}
		}

		/// <summary>
		/// Is reversed?
		/// </summary>
		private bool reversed;
		public bool Reversed
		{
			get { return reversed; }
			set
			{
				reversed = value;
				OnPropertyChanged( "Reversed" );
			}
		}

		/// <summary>
		/// Forward Guide type
		/// 0 = None
		/// 1 = 22''
		/// 2 = 24''
		/// </summary>
		private int fwdguide;
		public int ForwardGuide
		{
			get { return fwdguide; }
			set
			{
				fwdguide = value;
				OnPropertyChanged( "ForwardGuide" );
			}
		}

		/// <summary>
		/// Aft Guide type
		/// 0 = None
		/// 1 = 22''
		/// 2 = 24''
		/// </summary>
		private int aftguide;
		public int AftGuide
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
