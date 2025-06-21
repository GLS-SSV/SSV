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
/******* SSV File Modification Notice *******
Date         Developer
2020/05/07   GLS
2020/05/31   GLS
2020/07/01   GLS
2021/12/25   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/06/24   GLS
2025/06/21   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra Workbench

  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/

using System;


namespace SSVMissionEditor.Model
{
	class SSV_MLP : OrbiterVessel
	{
		public SSV_MLP( Mission mission )
		{
			_class = "SSV_MLP";
			name = mission.MLP;

			umb_st = 1;
			umb_pos = 1.0;

			statuslanded = true;
			statusplanet = "Earth";
			poslon = 0.0;
			poslat = 0.0;
			heading = 0.0;
			alt = 0.0;
			attached.Clear();
			attached.Add( Tuple.Create( 0, 0, mission.LaunchPad ) );

			this.mission = mission;
		}

		public override void PreSave( MissionPhase missionphase )
		{
			if ((mission.LaunchSite != Defs.strKSC) || (missionphase > MissionPhase.LaunchT31s))
			{
				save = false;
				return;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  MISSION " + mission.MissionFile );

			scn.WriteLine( "  T0_UMB " + umb_st + " " + string.Format( "{0:f4}", umb_pos ).Replace( ',', '.' ) );
			return;
		}


		Mission mission;

		protected int umb_st;
		protected double umb_pos;
	}
}
