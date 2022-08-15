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
2020/05/14   GLS
2020/05/31   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/07/08   GLS
2021/12/25   GLS
2022/01/10   GLS
2022/03/01   GLS
2022/06/24   GLS
2022/08/05   GLS
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


namespace SSVMissionEditor.model
{
	class SSV_CentaurG : OrbiterVessel
	{
		public SSV_CentaurG( Mission mission )
		{
			_class = "SSV_CentaurG";
			name = mission.LargeUpperStage_Name;

			prplevel.Clear();
			prplevel.Add( Tuple.Create( 0, 1.0 ) );
			prplevel.Add( Tuple.Create( 1, 1.0 ) );

			attached.Clear();
			attached.Add( Tuple.Create( 0, 23, mission.OV.Name.ToString() ) );

			this.mission = mission;
		}

		public override void PreSave( MissionPhase missionphase )
		{
			// build state from "mission" and "missionphase"
			switch (missionphase)
			{
				case MissionPhase.LaunchT20m:
				case MissionPhase.LaunchT9m:
				case MissionPhase.LaunchT31s:
					statuslanded = true;
					statusplanet = "Earth";
					break;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  MISSION " + mission.MissionFile );
			return;
		}


		Mission mission;
	}
}
