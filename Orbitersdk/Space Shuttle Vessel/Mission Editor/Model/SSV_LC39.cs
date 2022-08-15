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
2020/06/28   GLS
2020/07/01   GLS
2021/12/25   GLS
2022/01/07   GLS
2022/01/08   GLS
2022/01/09   GLS
2022/01/10   GLS
2022/03/01   GLS
2022/03/04   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/08/10   GLS
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

namespace SSVMissionEditor.model
{
	class SSV_LC39 : OrbiterVessel
	{
		public const double LC39A_LAT = 28.6083850;// deg
		public const double LC39A_LON = -80.6040720;// deg

		public const double LC39B_LAT = 28.6272150;// deg
		public const double LC39B_LON = -80.6208620;// deg


		public SSV_LC39( Mission mission )
		{
			_class = "SSV_LC39";

			if (mission.LaunchPad == 0) name = "LC-39A";
			else name = "LC-39B";

			lcc = "LCC";

			statuslanded = true;
			statusplanet = "Earth";
			if (mission.LaunchPad == 0)
			{
				poslon = LC39A_LON;
				poslat = LC39A_LAT;
				arotx = -180.0;
				aroty = 80.604;
				arotz = 118.608;
			}
			else
			{
				poslon = LC39B_LON;
				poslat = LC39B_LAT;
				arotx = -180.0;
				aroty = 80.621;
				arotz = 118.627;
			}
			heading = 270.0;
			alt = 0.05;

			this.mission = mission;
		}

		public override void PreSave( MissionPhase missionphase )
		{
			if (missionphase > MissionPhase.LaunchT31s)
			{
				save = false;
				return;
			}

			// build state from "mission" and "missionphase"
			switch (missionphase)
			{
				case MissionPhase.LaunchT20m:
				case MissionPhase.LaunchT9m:
					oaa_st = 1;
					oaa_pos = 1.0;
					gva_st = 1;
					gva_pos = 1.0;
					venthood_st = 1;
					venthood_pos = 1.0;
					owpfss_st = 0;
					owpfss_pos = 0.0;
					owprss_st = 0;
					owprss_pos = 0.0;
					rss_st = 0;
					rss_pos = 0.0;
					etvas_st = 1;
					etvas_pos = 1.0;
					iaa_st = 0;
					iaa_pos = 0.0;
					eastsfd_st = 1;
					eastsfd_pos = 1.0;
					westsfd_st = 1;
					westsfd_pos = 1.0;
					if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
					{
						rbus_st = 1;
						rbus_pos = 1.0;
					}
					else
					{
						rbus_st = 0;
						rbus_pos = 0.0;
					}
					break;
				case MissionPhase.LaunchT31s:
					oaa_st = 0;
					oaa_pos = 0.0;
					gva_st = 0;
					gva_pos = 0.0;
					venthood_st = 0;
					venthood_pos = 0.0;
					owpfss_st = 0;
					owpfss_pos = 0.0;
					owprss_st = 0;
					owprss_pos = 0.0;
					rss_st = 0;
					rss_pos = 0.0;
					etvas_st = 1;
					etvas_pos = 1.0;
					iaa_st = 0;
					iaa_pos = 0.0;
					eastsfd_st = 1;
					eastsfd_pos = 1.0;
					westsfd_st = 1;
					westsfd_pos = 1.0;
					if ((mission.LargeUpperStage == 4) || (mission.LargeUpperStage == 5))
					{
						rbus_st = 1;
						rbus_pos = 1.0;
					}
					else
					{
						rbus_st = 0;
						rbus_pos = 0.0;
					}
					break;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  MISSION " + mission.MissionFile );

			scn.WriteLine( "  OAA " + oaa_st + " " + string.Format( "{0:f4}", oaa_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  GVA " + gva_st + " " + string.Format( "{0:f4}", gva_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  VENT_HOOD " + venthood_st + " " + string.Format( "{0:f4}", venthood_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  ETVAS " + etvas_st + " " + string.Format( "{0:f4}", etvas_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  IAA " + iaa_st + " " + string.Format( "{0:f4}", iaa_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  RSS " + rss_st + " " + string.Format( "{0:f4}", rss_pos ).Replace( ',', '.' ) );

			if (mission.LaunchPadType >= 3)
			{
				scn.WriteLine( "  FSS_OWP " + owpfss_st + " " + string.Format( "{0:f4}", owpfss_pos ).Replace( ',', '.' ) );

				scn.WriteLine( "  RSS_OWP " + owprss_st + " " + string.Format( "{0:f4}", owprss_pos ).Replace( ',', '.' ) );
			}

			if ((mission.LaunchPadType == 3) || (mission.LaunchPadType == 4))
				scn.WriteLine( "  RBUS " + rbus_st + " " + string.Format( "{0:f4}", rbus_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  EAST_SRB_SFD " + eastsfd_st + " " + string.Format( "{0:f4}", eastsfd_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  WEST_SRB_SFD " + westsfd_st + " " + string.Format( "{0:f4}", westsfd_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  LCC_NAME " + lcc );
			return;
		}


		Mission mission;

		protected int oaa_st;
		protected double oaa_pos;

		protected int gva_st;
		protected double gva_pos;

		protected int venthood_st;
		protected double venthood_pos;

		protected int owpfss_st;
		protected double owpfss_pos;

		protected int owprss_st;
		protected double owprss_pos;

		protected int rss_st;
		protected double rss_pos;

		protected int etvas_st;
		protected double etvas_pos;

		protected int iaa_st;
		protected double iaa_pos;

		protected int eastsfd_st;
		protected double eastsfd_pos;

		protected int westsfd_st;
		protected double westsfd_pos;

		protected int rbus_st;
		protected double rbus_pos;

		protected string lcc;
	}
}
