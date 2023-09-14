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
	public enum SSME_Type
	{
		FMOF = 0,
		FPL_Phase_I,
		Phase_II,
		Block_I,
		Block_II
	}

	public class Mission_SSME : INotifyPropertyChanged
	{
		public Mission_SSME()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			Type = SSME_Type.Block_I;
			return;
		}

		public void LoadEmpty()
		{
			Type = SSME_Type.Block_II;
			return;
		}

		public void Load_V1( JToken jtk )
		{
			string strtmp = (string)jtk["Configuration"];
			int inttmp = Mission.String2EnumIdx( Type, strtmp );
			if (inttmp >= 0) Type = (SSME_Type)inttmp;
			else Type = SSME_Type.Block_II;

			//jtk["ControllerSW"];
			return;
		}

		public void Load_V2( JToken jtk )
		{
			Load_V1( jtk );
			return;
		}

		public JObject Save_V2()
		{
			JObject jobj = new JObject();

			jobj["Configuration"] = Type.ToString();
			//jobj["ControllerSW"] = "AD25";// TODO
			return jobj;
		}


		private SSME_Type type;
		public SSME_Type Type
		{
			get { return type; }
			set
			{
				type = value;
				OnPropertyChanged( "Type" );
			}
		}


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
		}
	}
}
