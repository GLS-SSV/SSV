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

namespace SSVMissionEditor.Model
{
	class SSV_XenonLights : OrbiterVessel
	{
		public SSV_XenonLights( Mission mission, string site, string pos )
		{
			_class = "SSV_XenonLights";

			name = "XenonLights_" + site + "_" + pos;

			statuslanded = true;
			statusplanet = "Earth";

			List<Defs.XenonLightSite> list = Defs.GetXenonLightList();
			foreach (Defs.XenonLightSite xenonlight in list)
			{
				if (xenonlight.Name == site)
				{
					foreach (Defs.XenonLightPosition xenonlightpos in xenonlight.Positions)
					{
						if (xenonlightpos.Name == pos)
						{
							poslon = xenonlightpos.Lon;
							poslat = xenonlightpos.Lat;
							arotx = xenonlightpos.ArotX;
							aroty = xenonlightpos.ArotY;
							arotz = xenonlightpos.ArotZ;
							heading = xenonlightpos.Heading;
							alt = xenonlightpos.Alt;
							break;
						}
					}
				}
			}

			pan = 0.0;
			tilt = 0.0;
			return;
		}

		public override void PreSave( MissionPhase missionphase )
		{
			// build state from "mission" and "missionphase"
			switch (missionphase)
			{
				case MissionPhase.Preview:
					save = false;
					break;
				case MissionPhase.LaunchT20m:
				case MissionPhase.LaunchT9m:
				case MissionPhase.LaunchT31s:
					break;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  POWER " + "0" );
			scn.WriteLine( "  PAN_TILT " + pan + " " + tilt );
			return;
		}


		protected double pan;
		protected double tilt;
	}
}
