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
using System.Collections.ObjectModel;
using System.Linq;
using Newtonsoft.Json.Linq;

namespace SSVMissionEditor.Model
{
	public class Mission_XenonLights
	{
		public Mission_XenonLights()
		{
			LocationList = new ObservableCollection<string>();

			LoadDefault();
		}

		public void LoadDefault()
		{
			LocationList.Clear();
			LocationList.Add( "KSC33" );
			LocationList.Add( "KSC15" );
			LocationList.Add( "EDW22" );
			LocationList.Add( "EDW04" );
			return;
		}

		public void LoadEmpty()
		{
			LocationList.Clear();
			return;
		}

		public void Load_V1( JToken jtk )
		{
			if (jtk == null) return;

			LocationList = jtk.ToObject<ObservableCollection<string>>();

			// remove any entries not supported
			List<Defs.XenonLightSite> XenonLightsDB = Defs.GetXenonLightList();
			for (int i = LocationList.Count - 1; i >= 0; i--)
			{
				if (XenonLightsDB.Any( item => (item.Name == LocationList[i]) ) == false)
				{
					LocationList.RemoveAt( i );
				}
			}
			return;
		}

		public JArray Save_V1()
		{
			JArray jarr = JArray.FromObject( LocationList );
			return jarr;
		}


		public ObservableCollection<string> LocationList { get; set; }
	}
}
