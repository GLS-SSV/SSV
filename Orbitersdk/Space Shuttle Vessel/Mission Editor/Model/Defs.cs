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
2020/05/31   GLS
2020/06/28   GLS
2020/06/30   GLS
2020/07/01   GLS
2020/09/27   GLS
2020/09/28   GLS
2021/12/25   GLS
2022/01/10   GLS
2022/02/25   GLS
2022/03/01   GLS
2022/03/24   GLS
2022/04/07   GLS
2022/05/24   GLS
2022/06/19   GLS
2022/06/24   GLS
2022/08/05   GLS
2022/10/14   GLS
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


namespace SSVMissionEditor
{
	class Defs
	{
		public const double MAXLOAD_FRCS = 2473.0;// [lbs]
		public const double MINLOAD_FRCS = 2473.0 * 0.68;// [lbs]

		public const double MAXLOAD_ARCS = 2692.0;// [lbs]
		public const double MINLOAD_ARCS = 2692.0 * 0.6;// [lbs]

		public const double MAXLOAD_OMS = 12593.5;// [lbs]
		public const double MINLOAD_OMS = 5400.0;// [lbs]
		
		public const int PLID_Xo_base = 154;// PLID of base index
		public static readonly double[] PLID_Xo = {// Xo coordinates of PLIDs
			/*bay  1: 154-160*/608.80, 612.73, 616.67, 620.60, 624.53, 628.47, 632.40,
			/*161-162*/-1.0, -1.0,
			/*bay  2: 163-173*/644.20, 648.13, 652.07, 656.00, 659.93, 663.87, 667.80, 671.73, 675.67, 679.60, 683.53,
			/*174-176*/-1.0, -1.0, -1.0,
			/*bay  3: 177-189*/699.27, 703.20, 707.13, 711.07, 715.00, 718.93, 722.87, 726.80, 730.73, 734.67, 738.60, 742.53, 746.47,
			/*190-191*/-1.0, -1.0,
			/*bay  4: 192-204*/758.27, 762.20, 766.13, 770.07, 774.00, 777.93, 781.87, 785.80, 789.73, 793.67, 797.60, 801.53, 805.47,
			/*205*/-1.0,
			/*bay  5: 206-218*/813.33, 817.27, 821.20, 825.13, 829.07, 833.00, 836.93, 840.87, 844.80, 848.73, 852.67, 856.60, 860.53,
			/*219-220*/-1.0, -1.0,
			/*bay  6: 221-230*/872.33, 876.27, 880.20, 884.13, 888.07, 892.00, 895.93, 899.87, 903.80, 907.73,
			/*231-233*/-1.0, -1.0, -1.0,
			/*bay  7: 234-247*/923.47, 927.40, 931.33, 935.27, 939.20, 943.13, 947.07, 951.00, 954.93, 958.87, 962.80, 966.73, 970.67, 974.60,
			/*248-249*/-1.0, -1.0,
			/*bay  8: 250-263*/986.40, 990.33, 994.27, 998.20, 1002.13, 1006.07, 1010.00, 1013.93, 1017.87, 1021.80, 1025.73, 1029.67, 1033.60, 1037.53,
			/*264-265*/-1.0, -1.0,
			/*bay  9: 266-276*/1049.33, 1053.27, 1057.20, 1061.13, 1065.07, 1069.00, 1072.93, 1076.87, 1080.80, 1084.73, 1088.67,
			/*bay 10: 277-289*/1092.60, 1096.53, 1100.47, 1104.40, 1108.33, 1112.27, 1116.20, 1120.13, 1124.07, 1128.00, 1131.93, 1135.87, 1139.80,
			/*290-291*/-1.0, -1.0,
			/*bay 11: 292-301*/1151.60, 1155.53, 1159.47, 1163.40, 1167.33, 1171.27, 1175.20, 1179.13, 1183.07, 1187.0/*???*/,
			/*302-303*/-1.0, -1.0,
			/*bay 12: 304-316*/1198.80, 1202.73, 1206.67, 1210.60, 1214.53, 1218.47, 1222.40, 1226.33, 1230.27, 1234.20, 1238.13, 1242.07, 1246.00,
			/*bay 13: 317-330*/1249.93, -1.0, -1.0, -1.0, -1.0, 1269.60, 1273.53, 1277.47, 1281.40, -1.0, -1.0, -1.0, -1.0, 1303.00
		};

		public static readonly int[] KEEL_ACTIVE = {
			/*bay  1*/156, 157,
			/*bay  2*/166, 167, 168, 169, 170, 171, 172,
			/*bay  3*/180, 181, 182, 183, 184, 185, 186,
			/*bay  4*/195, 196, 197, 198, 199, 200, 201,
			/*bay  5*/209, 210, 211, 212, 213, 214, 215,
			/*bay  6*/223, 224, 225, 226, 227, 228, 229,
			/*bay  7*/238, 239, 240, 241, 242, 243, 244,
			/*bay  8*/253, 254, 255, 256, 257, 258, 259, 260,
			/*bay  9*/268, 269, 270, 271, 272, 273,
			/*bay 10*/281, 282, 283, 284, 285,
			/*bay 11*/294, 295, 296, 297, 298,
			/*bay 12*/306, 307, 308, 309, 310, 311
			/*bay 13*/
			};
		public static readonly int[] KEEL_PASSIVE = {
			/*bay  1*/155, 156, 157, 158,
			/*bay  2*/165, 166, 167, 168, 169, 170, 171, 172,
			/*bay  3*/180, 181, 182, 183, 184, 185, 186, 187,
			/*bay  4*/194, 195, 196, 197, 198, 199, 200, 201,
			/*bay  5*/208, 209, 210, 211, 212, 213, 214, 215, 216,
			/*bay  6*/223, 224, 225, 226, 227, 228, 229, 230,
			/*bay  7*/237, 238, 239, 240, 241, 242, 243, 244, 245,
			/*bay  8*/252, 253, 254, 255, 256, 257, 258, 259, 260, 261,
			/*bay  9*/268, 269, 270, 271, 272, 273,
			/*bay 10*/281, 282, 283, 284, 285, 286,
			/*bay 11*/293, 294, 295, 296, 297, 298, 299,
			/*bay 12*/306, 307, 308, 309, 310, 311
			/*bay 13*/
			};

		public static readonly int[] LONGERON_ACTIVE = {
			/*bay  1*/156, 157, 158, 159, 160,
			/*bay  2*/163, 164, 165, 166, 167,
			/*bay  3*/177, 178, 179, 180, 181, 182, 183, 184, 185,
			/*bay  4*/192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203,
			/*bay  5*/206, 207, 208, 209, 210, 211, 214, 215, 216, 217, 218,
			/*bay  6*/221, 222, 223, 224, 225, 226, 227,
			/*bay  7*/234, 235, 236, 237, 238, 239, 240, 241, 242, 243,
			/*bay  8*/250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263,
			/*bay  9*/266, 267, 268, 269, 270, 271, 272, 273, 274,
			/*bay 10*/277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288,
			/*bay 11*/292, 293, 294, 295, 296, 297, 298,
			/*bay 12*/305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315,
			/*bay 13*/322, 323, 324
			};
		public static readonly int[] LONGERON_PASSIVE = {
			/*bay  1*/156, 157, 158, 159, 160,
			/*bay  2*/163, 164, 165, 166, 167,
			/*bay  3*/177, 178, 179, 180, 181, 182, 183, 184, 185, 188, 189,
			/*bay  4*/192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203,
			/*bay  5*/206, 207, 208, 209, 210, 211, 214, 215, 216, 217, 218,
			/*bay  6*/221, 222, 223, 224, 225, 226, 227,
			/*bay  7*/234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 247,
			/*bay  8*/250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263,
			/*bay  9*/266, 267, 268, 269, 270, 271, 272, 273, 274,
			/*bay 10*/277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288,
			/*bay 11*/292, 293, 294, 295, 296, 297, 298, 299,
			/*bay 12*/304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316,
			/*bay 13*/322, 323, 324, 325
			};

		public static readonly int[] KEEL_PAM_D = {// longeron aft = longeron fwd + 20 = keel + 19
			/*bay  1*/158,
			/*bay  2*/165, 166,
			/*bay  3*/180, 181, 182, 183, 184,
			/*bay  4*/195, 196, 197, 198, 199,
			/*bay  5*/208, 215, 216,
			/*bay  6*/223, 224, 228,
			/*bay  7*/237, 238, 239, 240, 241, 242, 243, 244,
			/*bay  8*/252, 253, 254, 255, 258, 259, 260, 261,
			/*bay  9*/268, 269, 273,
			/*bay 10*/285, 286,
			/*bay 11*/293, 294, 295, 296, 297,
			/*bay 12*/306
			/*bay 13*/
			};

		public static readonly int[] KEEL_PAM_A = {// longeron aft = keel/longeron fwd + 18
			/*bay  1*/
			/*bay  2*/165, 166, 167,
			/*bay  3*/180, 181, 182, 183, 184, 185,
			/*bay  4*/196, 197, 198, 199, 200,
			/*bay  5*/216,
			/*bay  6*/223, 224, 225,
			/*bay  7*/237, 238, 239, 240, 241, 242, 243,
			/*bay  8*/252, 253, 254, 255, 256, 259, 260, 261,
			/*bay  9*/268, 269, 270,
			/*bay 10*/281, 286,
			/*bay 11*/293, 294, 295, 296, 297, 298,
			/*bay 12*/306, 307
			/*bay 13*/
			};

		private static readonly int[] Bay_PLID = {160, 175, 189, 204, 218, 232, 248, 263, 276, 289, 302, 316, 330};// last PLID of bay

		public static int FindBridgeByPLID( int PLID )
		{
			if (PLID == 0) return 0;

			for (int k = 0; k < 13; k++)
			{
				if (PLID < Bay_PLID[k])
				{
					return k + 1;
				}
			}
			return 0;
		}

		public static readonly int SMALLUPPERSTAGE_MAX = 3;// maximum number of "small" upper stages
	}
}
