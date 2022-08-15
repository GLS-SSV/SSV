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

using System;


namespace SSVMissionEditor.model
{
	class OtherVessel : OrbiterVessel
	{
		public OtherVessel( Mission_Vessel v )
		{
			Class = v.VesselClass;
			Name = v.Name;

			string[] scnparamlist = v.ScnParams.Split( new[] { "\r\n", "\r", "\n" }, System.StringSplitOptions.RemoveEmptyEntries );
			foreach (string scnparam in scnparamlist)
			{
				string[] param = scnparam.Split( ' ' );
				switch (param[0])
				{
					case "STATUS":
						statuslanded = (param[1] == "Landed");
						statusplanet = param[2];
						break;
					case "BASE":
						_base = param[1];
						break;
					case "POS":
						poslon = Convert.ToDouble( param[1] );
						poslat = Convert.ToDouble( param[2] );
						break;
					case "HEADING":
						heading = Convert.ToDouble( param[1] );
						break;
					case "ALT":
						alt = Convert.ToDouble( param[1] );
						break;
					case "AROT":
						arotx = Convert.ToDouble( param[1] );
						aroty = Convert.ToDouble( param[2] );
						arotz = Convert.ToDouble( param[3] );
						break;
					case "RPOS":
						rposx = Convert.ToDouble( param[1] );
						rposy = Convert.ToDouble( param[2] );
						rposz = Convert.ToDouble( param[3] );
						break;
					case "RVEL":
						rvelx = Convert.ToDouble( param[1] );
						rvely = Convert.ToDouble( param[2] );
						rvelz = Convert.ToDouble( param[3] );
						break;
					case "ELEMENTS":
						elements_a = Convert.ToDouble( param[1] );
						elements_e = Convert.ToDouble( param[2] );
						elements_i = Convert.ToDouble( param[3] );
						elements_lan = Convert.ToDouble( param[4] );
						elements_lp = Convert.ToDouble( param[5] );
						elements_ml = Convert.ToDouble( param[6] );
						elements_date = Convert.ToDouble( param[7] );
						break;
					case "VROT":
						vrotx = Convert.ToDouble( param[1] );
						vroty = Convert.ToDouble( param[2] );
						vrotz = Convert.ToDouble( param[3] );
						break;
					/*case "ATTACHED":
						break;
					case "RCSMODE":
						break;
					case "AFCMODE":
						break;
					case "FUEL":
						break;
					case "PRPLEVEL":
						break;
					case "THLEVEL":
						break;
					case "DOCKINFO":
						break;
					case "IDS":
						break;
					case "NAVFREQ":
						break;
					case "XPDR":
						break;*/
					default:// vessel parameter
						OtherParams.Add( scnparam );
						break;
				}
			}
		}
	}
}
