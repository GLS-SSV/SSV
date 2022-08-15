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
	class SSV_LCC : OrbiterVessel
	{
		public const double LC39_LCC_LAT = 28.5852249;// deg
		public const double LC39_LCC_LON = -80.6493245;// deg

		public const double SLC6_LCC_LAT = 34.5815600;// deg
		public const double SLC6_LCC_LON = -120.6299800;// deg

		public SSV_LCC( Mission mission )
		{
			_class = "SSV_LCC";
			name = "LCC";

			int ms = Convert.ToInt32( 1000 * (mission.T0Second - (int)mission.T0Second) );
			t0 = new DateTime( mission.T0Year, mission.T0Month, mission.T0Day, mission.T0Hour, mission.T0Minute, (int)mission.T0Second, ms );

			if (mission.LaunchSite == 0)
			{
				if (mission.LaunchPad == 0) pad_name = "LC-39A";
				else pad_name = "LC-39B";
			}
			else pad_name = "SLC-6";

			statuslanded = true;
			statusplanet = "Earth";
			if (mission.LaunchSite == 0)
			{
				poslon = LC39_LCC_LON;
				poslat = LC39_LCC_LAT;
				heading = 35.6;
				alt = 2.0;
			}
			else
			{
				poslon = SLC6_LCC_LON;
				poslat = SLC6_LCC_LAT;
				heading = 97.0;
				alt = 18.0;
			}

			this.mission = mission;
		}

		public override void PreSave( MissionPhase missionphase )
		{
			if (missionphase > MissionPhase.LaunchT31s)
			{
				save = false;
				return;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  MISSION " + mission.MissionFile );

			scn.WriteLine( "  LAUNCH_MJD " + string.Format( "{0:f10}", t0.ToOADate() + 15018.0 ).Replace( ',', '.' ) );

			scn.WriteLine( "  PAD_NAME " + pad_name );
			return;
		}


		Mission mission;

		DateTime t0;

		protected string pad_name;
	}
}
