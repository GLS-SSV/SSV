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


namespace SSVMissionEditor.model
{
	class SSV_SLC6 : OrbiterVessel
	{

		public const double SLC6_LAT = 34.5808470;// deg
		public const double SLC6_LON = -120.6259500;// deg

		public SSV_SLC6( Mission mission )
		{
			_class = "SSV_SLC6";
			name = "SLC-6";
			lcc = "LCC";

			statuslanded = true;
			statusplanet = "Earth";
			poslon = SLC6_LON;
			poslat = SLC6_LAT;
			heading = 270.0;
			alt = 16.0;

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
					etvas_st = 1;
					etvas_pos = 1.0;
					iaa_st = 0;
					iaa_pos = 0.0;
					t0umb_st = 1;
					t0umb_pos = 1.0;
					pcr_st = 0;
					pcr_pos = 0.0;
					sab_st = 0;
					sab_pos = 0.0;
					mst_st = 0;
					mst_pos = 0.0;
					sabdoor_st = 1;
					sabdoor_pos = 1.0;
					break;
				case MissionPhase.LaunchT31s:
					oaa_st = 0;
					oaa_pos = 0.0;
					gva_st = 0;
					gva_pos = 0.0;
					venthood_st = 0;
					venthood_pos = 0.0;
					etvas_st = 1;
					etvas_pos = 1.0;
					iaa_st = 0;
					iaa_pos = 0.0;
					t0umb_st = 1;
					t0umb_pos = 1.0;
					pcr_st = 0;
					pcr_pos = 0.0;
					sab_st = 0;
					sab_pos = 0.0;
					mst_st = 0;
					mst_pos = 0.0;
					sabdoor_st = 1;
					sabdoor_pos = 1.0;
					break;
			}
			return;
		}

		protected override void SaveSpecificParams( System.IO.StreamWriter scn )
		{
			scn.WriteLine( "  OAA " + oaa_st + " " + string.Format( "{0:f4}", oaa_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  GVA " + gva_st + " " + string.Format( "{0:f4}", gva_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  VENT_HOOD " + venthood_st + " " + string.Format( "{0:f4}", venthood_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  ETVAS " + etvas_st + " " + string.Format( "{0:f4}", etvas_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  IAA " + iaa_st + " " + string.Format( "{0:f4}", iaa_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  T0_UMB " + t0umb_st + " " + string.Format( "{0:f4}", t0umb_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  PCR " + pcr_st + " " + string.Format( "{0:f4}", pcr_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  SAB " + sab_st + " " + string.Format( "{0:f4}", sab_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  MST " + mst_st + " " + string.Format( "{0:f4}", mst_pos ).Replace( ',', '.' ) );

			scn.WriteLine( "  SABDoor " + sabdoor_st + " " + string.Format( "{0:f4}", sabdoor_pos ).Replace( ',', '.' ) );

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

		protected int etvas_st;
		protected double etvas_pos;

		protected int iaa_st;
		protected double iaa_pos;

		protected int t0umb_st;
		protected double t0umb_pos;

		protected int pcr_st;
		protected double pcr_pos;

		protected int sab_st;
		protected double sab_pos;

		protected int mst_st;
		protected double mst_pos;

		protected int sabdoor_st;
		protected double sabdoor_pos;

		protected string lcc;
	}
}
