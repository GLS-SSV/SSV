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

namespace SSVMissionEditor.Model
{
	public class Mission_SSME : INotifyPropertyChanged
	{
		public Mission_SSME()
		{
			LoadDefault();
		}

		public void LoadDefault()
		{
			Type = Defs.strBlock_I;
			return;
		}

		public void LoadEmpty()
		{
			Type = Defs.strBlock_II;
			return;
		}

		public void Load_V1( JToken jtk )
		{
			string strtmp = (string)jtk["Configuration"];
			if (strtmp == "FMOF") Type = Defs.strFMOF;
			else if (strtmp == "FPL_Phase_I") Type = Defs.strFPL_Phase_I;
			else if (strtmp == "Phase_II") Type = Defs.strPhase_II;
			else if (strtmp == "Block_I") Type = Defs.strBlock_I;
			else if (strtmp == "Block_II") Type = Defs.strBlock_II;
			else
			{
				// TODO kaput
			}

			//jtk["ControllerSW"];
			return;
		}

		public JObject Save_V1()
		{
			JObject jobj = new JObject();

			if (Type == Defs.strFMOF) jobj["Configuration"] = "FMOF";
			else if (Type == Defs.strFPL_Phase_I) jobj["Configuration"] = "FPL_Phase_I";
			else if (Type == Defs.strPhase_II) jobj["Configuration"] = "Phase_II";
			else if (Type == Defs.strBlock_I) jobj["Configuration"] = "Block_I";
			else if (Type == Defs.strBlock_II) jobj["Configuration"] = "Block_II";
			else
			{
				// TODO kaput
			}

			// TODO for v2 file
			//jobj["Type"] = Type;

			//jobj["ControllerSW"] = "AD25";// TODO
			return jobj;
		}


		private string type;
		public string Type
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
