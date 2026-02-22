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
2022/11/27   GLS
2022/12/05   GLS
2022/12/09   GLS
2023/02/14   GLS
2023/03/30   GLS
2023/04/04   GLS
2023/08/15   GLS
2023/08/28   GLS
2025/02/11   GLS
2025/06/21   GLS
2025/07/16   GLS
2025/11/16   GLS
2026/01/02   GLS
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
using System.Collections.Generic;


namespace SSVMissionEditor
{
	class Defs
	{
		public const double SCN_TIME_OFFSET = 0.1;// time offset to add to scenario start time [s]

		public const double PI = 3.14159265358979323846;// pi
		public const double RAD = PI / 180.0;//  factor to map degrees to radians
		public const double DEG = 180.0 / PI;// factor to map radians to degrees
		public const double NM2KM = 1.8520;// nautical mile to meter
		public const double MPS2FPS = 3.280839895;// meters per seconds to feet per second


		public const double LC39A_LAT = 28.6083850;// deg
		public const double LC39A_LON = -80.6040720;// deg

		public const double LC39B_LAT = 28.6272150;// deg
		public const double LC39B_LON = -80.6208620;// deg

		public const double SLC6_LAT = 34.5808470;// deg
		public const double SLC6_LON = -120.6259500;// deg


		public const string strKSC = "KSC";
		public const string strVAFB = "VAFB";

		public const string strLC39A = "LC-39A";
		public const string strLC39B = "LC-39B";
		public const string strSLC6 = "SLC-6";

		public const string str1981 = "1981";
		public const string str1982 = "1982";
		public const string str1983 = "1983";
		public const string str1985 = "1985";
		public const string str1986 = "1986";
		public const string str1988 = "1988";
		public const string str1995 = "1995";
		public const string str2007 = "2007";

		public const string strMLP1 = "MLP-1";
		public const string strMLP2 = "MLP-2";
		public const string strMLP3 = "MLP-3";

		public const string strColumbia = "Columbia";
		public const string strChallenger = "Challenger";
		public const string strDiscovery = "Discovery";
		public const string strAtlantis = "Atlantis";
		public const string strEndeavour = "Endeavour";

		public const string strInternal = "Internal";
		public const string strExternal = "External";

		public const string strNone = "None";
		public const string strForward = "Forward";
		public const string strAft = "Aft";

		public const string strOriginal = "Original";
		public const string strSORG = "SORG";

		public const string strThreeTier = "Three Tier";
		public const string strFourTier = "Four Tier";

		public const string strMCDS = "MCDS";
		public const string strMEDS = "MEDS";

		public const string str_506_508 = "-506/-508";
		public const string strCTVC_ITVC = "CTVC/ITVC";

		public const string strFMOF = "FMOF";
		public const string strFPL_Phase_I = "FPL/Phase-I";
		public const string strPhase_II = "Phase-II";
		public const string strBlock_I = "Block-I";
		public const string strBlock_II = "Block-II";

		public const string strNoOMSKit = "No OMS Kit";
		public const string strOMSKit1TankSet = "1 Tank Set";
		public const string strOMSKit2TankSets = "2 Tank Sets";
		public const string strOMSKit3TankSets = "3 Tank Sets";

		public const string strPRSD2TankSets = "2 Tank Sets";
		public const string strPRSD3TankSets = "3 Tank Sets";
		public const string strPRSD4TankSets = "4 Tank Sets";
		public const string strPRSD5TankSets = "5 Tank Sets";

		public const string strNoEDOPallet = "No EDO Pallet";
		public const string strSingleEDOPallet = "Single EDO Pallet (9 Tank Sets)";
		public const string strDualEDOPallet = "Dual EDO Pallet (13 Tank Sets)";

		public const string strSWT = "SWT";
		public const string strLWT = "LWT";
		public const string strSLWT = "SLWT";

		public const string strSPM = "SPM";
		public const string strHPM = "HPM";
		public const string strFWC = "FWC";
		public const string strRSRM = "RSRM";


		// default texture lists
		public class TEX_INFO
		{
			public string Name;
			public string File;

			public override string ToString() { return Name; }
		};

		public static List<TEX_INFO> DefaultOVTextures( string strOV )
		{
			List<TEX_INFO> lst = null;

			switch (strOV)
			{
				case strColumbia:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "Original",
							File = "OV-102_original"
						},
						new TEX_INFO
						{
							Name = "4th mod",
							File = "OV-102_4thmod"
						},
						new TEX_INFO
						{
							Name = "6th mod",
							File = "OV-102_6thmod"
						},
						new TEX_INFO
						{
							Name = "8th mod",
							File = "OV-102_8thmod"
						}
					};
					break;
				case strChallenger:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "Original",
							File = "OV-099_original"
						}
					};
					break;
				case strDiscovery:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "Original",
							File = "OV-103_original"
						},
						new TEX_INFO
						{
							Name = "6th mod",
							File = "OV-103_6thmod"
						},
						new TEX_INFO
						{
							Name = "9th mod",
							File = "OV-103_9thmod"
						}
					};
					break;
				case strAtlantis:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "Original",
							File = "OV-104_original"
						},
						new TEX_INFO
						{
							Name = "4th mod",
							File = "OV-104_4thmod"
						},
						new TEX_INFO
						{
							Name = "5th mod",
							File = "OV-104_5thmod"
						}
					};
					break;
				case strEndeavour:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "Original",
							File = "OV-105_original"
						},
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "OV-105_3rdmod"
						}
					};
					break;
			}

			return lst;
		}

		public static List<TEX_INFO> DefaultLOMSTextures()
		{
			List<TEX_INFO> lst = new List<TEX_INFO>
			{
				/*new TEX_INFO// STS 1
				{
					Name = "Original",
					File = "OMSpod_original"
				},
				new TEX_INFO// STS 2
				{
					Name = "1st mod",
					File = "OMSpod_1stmod"
				},
				new TEX_INFO// STS 6
				{
					Name = "2nd mod",
					File = "OMSpod_2ndmod"
				},
				new TEX_INFO// STS 9
				{
					Name = "3rd mod",
					File = "OMSpod_3rdmod"
				},
				new TEX_INFO// STS 41C
				{
					Name = "4th mod",
					File = "OMSpod_4thmod"
				},
				new TEX_INFO// STS 41G
				{
					Name = "5th mod",
					File = "OMSpod_5thmod"
				},
				new TEX_INFO// STS 51A
				{
					Name = "6th mod",
					File = "OMSpod_6thmod"
				},*/
				new TEX_INFO// STS 51B
				{
					Name = "7th mod",
					File = "OMSpod_7thmod"
				}
			};
			return lst;
		}

		public static List<TEX_INFO> DefaultROMSTextures()
		{
			return DefaultLOMSTextures();
		}

		public static List<TEX_INFO> DefaultETTextures( string strET, bool FRL )
		{
			List<TEX_INFO> lst = null;

			switch (strET)
			{
				case strSWT:
					if (FRL)
					{
						lst = new List<TEX_INFO>
						{
							new TEX_INFO
							{
								Name = "SWT_FRL",
								File = "SWT_FRL"
							}
						};
					}
					else
					{
						lst = new List<TEX_INFO>
						{
							new TEX_INFO
							{
								Name = "SWT",
								File = "SWT"
							}
						};
					}
					break;
				case strLWT:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "LWT",
							File = "LWT"
						}
					};
					break;
				case strSLWT:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "SLWT",
							File = "SLWT"
						}
					};
					break;
			}

			return lst;
		}

		/**
		* Original	1
		* 1		2
		* 2		41C
		* 3		41D
		* 4		61
		* 5		90
		**/
		public static List<TEX_INFO> DefaultSRBLHFwdAssemblyTextures( string strSRM )
		{
			List<TEX_INFO> lst = null;

			switch (strSRM)
			{
				case strSPM:
					lst = new List<TEX_INFO>
					{
						/*new TEX_INFO
						{
							Name = "Original",
							File = "fwd_assembly_original"
						},*/
						new TEX_INFO
						{
							Name = "1st mod",
							File = "fwd_assembly_1stmod"
						}
					};
					break;
				case strHPM:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "1st mod",
							File = "fwd_assembly_1stmod"
						},
						/*new TEX_INFO
						{
							Name = "2nd mod",
							File = "LH_fwd_assembly_2ndmod"
						},*/
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "LH_fwd_assembly_3rdmod"
						}
					};
					break;
				case strFWC:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "LH_fwd_assembly_3rdmod"
						}
					};
					break;
				case strRSRM:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "LH_fwd_assembly_3rdmod"
						},
						new TEX_INFO
						{
							Name = "4th mod",
							File = "LH_fwd_assembly_4thmod"
						},
						new TEX_INFO
						{
							Name = "5th mod",
							File = "LH_fwd_assembly_5thmod"
						}
					};
					break;
			}

			return lst;
		}

		public static List<TEX_INFO> DefaultSRBRHFwdAssemblyTextures( string strSRM )
		{
			List<TEX_INFO> lst = null;

			switch (strSRM)
			{
				case strSPM:
					lst = new List<TEX_INFO>
					{
						/*new TEX_INFO
						{
							Name = "Original",
							File = "fwd_assembly_original"
						},*/
						new TEX_INFO
						{
							Name = "1st mod",
							File = "fwd_assembly_1stmod"
						}
					};
					break;
				case strHPM:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "1st mod",
							File = "fwd_assembly_1stmod"
						},
						/*new TEX_INFO
						{
							Name = "2nd mod",
							File = "RH_fwd_assembly_2ndmod"
						},*/
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "RH_fwd_assembly_3rdmod"
						}
					};
					break;
				case strFWC:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "RH_fwd_assembly_3rdmod"
						}
					};
					break;
				case strRSRM:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "RH_fwd_assembly_3rdmod"
						},
						new TEX_INFO
						{
							Name = "4th mod",
							File = "RH_fwd_assembly_4thmod"
						},
						new TEX_INFO
						{
							Name = "5th mod",
							File = "RH_fwd_assembly_5thmod"
						}
					};
					break;
			}

			return lst;
		}

		/**
		* Original	1
		* 1		2
		* 2		6
		* 3		9
		* 4		51D
		* 5		51I
		* 6		51L
		* 7		62A
		* 8		26R
		* 9		60
		**/
		public static List<TEX_INFO> DefaultSRBLHCaseTextures( string strSRM )
		{
			List<TEX_INFO> lst = null;

			switch (strSRM)
			{
				case strSPM:
					lst = new List<TEX_INFO>
					{
						/*new TEX_INFO
						{
							Name = "Original",
							File = "case_original"
						},*/
						new TEX_INFO
						{
							Name = "1st mod",
							File = "case_1stmod"
						},
						new TEX_INFO
						{
							Name = "2nd mod",
							File = "case_2ndmod"
						}
					};
					break;
				case strHPM:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "3rd mod",
							File = "case_3rdmod"
						},
						new TEX_INFO
						{
							Name = "4th mod",
							File = "case_4thmod"
						}/*,
						new TEX_INFO
						{
							Name = "5th mod",
							File = "case_5thmod"
						},
						new TEX_INFO
						{
							Name = "6th mod",
							File = "case_6thmod"
						}*/
					};
					break;
				case strFWC:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "7th mod",
							File = "case_7thmod"
						}
					};
					break;
				case strRSRM:
					lst = new List<TEX_INFO>
					{
						new TEX_INFO
						{
							Name = "8th mod",
							File = "case_8thmod"
						},
						new TEX_INFO
						{
							Name = "9th mod",
							File = "case_9thmod"
						}
					};
					break;
			}

			return lst;
		}

		public static List<TEX_INFO> DefaultSRBRHCaseTextures( string strSRM )
		{
			return DefaultSRBLHCaseTextures( strSRM );
		}


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
		public static readonly int[] KEEL_SPDS = {
			/*bay  1*/156, 157,
			/*bay  2*/166, 167, 168, 169, 170, 171,
			/*bay  3*/181, 182, 183, 184, 185, 186,
			/*bay  4*/195, 196, 197, 198, 199, 200,
			/*bay  5*/210, 211, 212, 213, 214, 215,
			/*bay  6*/225, 226, 227, 228, 229,
			/*bay  7*/238, 239, 240, 241, 242, 243, 244,
			/*bay  8*/253, 254, 255, 256, 257, 258, 259, 260,
			/*bay  9*/269, 270, 271, 272,
			/*bay 10*/282, 283, 284, 285,
			/*bay 11*/294, 295, 296, 297, 298,
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
		public static readonly int[] LONGERON_SPDS_3 = {// reversed PRLA
			/*bay  1*//*156, 157,*/
			/*bay  2*//*163, 164,*/
			/*bay  3*/177, 178, 179, 180, 181, /*182,*/
			/*bay  4*//*192,*/ 193, 194, 195, 196, 197, 198, 199, 200,
			/*bay  5*//*206, 207, 208, 209, 210, 211,*/ 214, 215,
			/*bay  6*/221, /*222, 223, 224,*/
			/*bay  7*//*234, 235, 236, 237, 238, 239, 240,*/
			/*bay  8*/250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260,
			/*bay  9*/266, 267, 268, 269, 270, 271,
			/*bay 10*/277, /*278, 279, 280, 281, 282, 283, 284, 285,*/
			/*bay 11*//*292, 293,*/ 294, 295,
			/*bay 12*/305, 306, 307, 308, 309, 310, 311, 312,
			/*bay 13*/
			};
		public static readonly int[] LONGERON_SPDS_5 = {// "regular" PRLA
			/*bay  1*/
			/*bay  2*/
			/*bay  3*/177, 178, 179, /*180,*/
			/*bay  4*/192, 193, 194, 195, 196, 197, 198,
			/*bay  5*//*206, 207, 208, 209, 210,*/ 211,
			/*bay  6*//*221, 222,*/
			/*bay  7*//*234, 235, 236, 237, 238,*/
			/*bay  8*/250, 251, 252, 253, 254, 255, 256, 257, 258,
			/*bay  9*/266, 267, 268, 269,
			/*bay 10*/277, 278, 279, 280, 281, 282, 283,
			/*bay 11*/292, 293,
			/*bay 12*/305, 306, 307, 308, 309, 310
			/*bay 13*/
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

		public static readonly int[] KEEL_CAMERA = {
			/*bay  1*/156, 157,
			/*bay  2*/164, 165, 166, 167, 168, 169, 170, 171,
			/*bay  3*/180, 181, 182, 183, 184, 185, 186,
			/*bay  4*/195, 196, 197, 198, 199, 200, 201,
			/*bay  5*/209, 210, 211, 212, 213, 214, 215,
			/*bay  6*/223, 224, 225, 226, 227, 228, 229,
			/*bay  7*/237, 238, 239, 240, 241, 242, 243, 244,
			/*bay  8*/253, 254, 255, 256, 257, 258, 259, 260,
			/*bay  9*/268, 269, 270, 271, 272, 273,
			/*bay 10*/280, 281, 282, 283, 284, 285, 286,
			/*bay 11*/294, 295, 296, 297, 298
			/*bay 12*/
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


		//// rendezvous target sets ////
		public class ORB_TGT_SET
		{
			public string Name;
			public string Description;
			public string T1;
			public string DT;
			public string EL;
			public string XOFF;
			public string YOFF;
			public string ZOFF;
			public string LAMB;

			public override string ToString() { return Name; }	
		};

		public static List<ORB_TGT_SET> OrbitTargets()
		{
			List<ORB_TGT_SET> lst = new List<ORB_TGT_SET>
			{
				new ORB_TGT_SET
				{
					Name = "ORBT (130 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 130 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -55.8 0.0 20.0 47.4 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 55.8 74.4 54.4 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.496546 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (150 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 150 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -56.3 0.0 20.0 48.1 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 56.3 75.1 55.1 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.4967205 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (170 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 170 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -56.8 0.0 20.0 48.7 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 56.8 75.7 55.7 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5002112 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (190 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 190 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -57.2 0.0 20.0 49.3 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 57.2 76.3 56.3 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5035273 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (210 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 210 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -57.7 0.0 20.0 49.9 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 57.7 76.9 56.9 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.507367 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (230 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 230 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -58.2 0.0 20.0 50.6 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 58.2 77.6 57.6 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5117304 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (250 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 250 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -58.7 0.0 20.0 51.2 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 58.7 78.2 58.2 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5157446 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (270 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 270 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -59.1 0.0 20.0 51.9 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 59.1 78.9 58.9 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5201079 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (290 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 290 Nautical Miles\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -59.6 0.0 20.0 52.5 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 59.6 79.5 59.5 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5241222 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				},
				new ORB_TGT_SET
				{
					Name = "ORBT (310 NM)",
					Description = "Optimized R-Bar Targeted Rendezvous (ORBT) for targets orbiting at 310 Nautical Miles, with Inertial Approach option\n" +
							"9: NCC\n" +
							"10: Ti\n" +
							"11: MC1\n" +
							"12: MC2\n" +
							"13: MC3\n" +
							"14: MC4\n" +
							"19: MC2 on time\n" +
							"29: NCC (inertial approach)\n" +
							"30: Ti (inertial approach)\n" +
							"31: MC1 (inertial approach)\n" +
							"32: MC2 (inertial approach)\n" +
							"33: MC3 (inertial approach)\n" +
							"34: MC4 (inertial approach)\n" +
							"39: MC2 on time (inertial approach)",
					T1 = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -60.1 0.0 20.0 53.1 17.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -60.1 0.0 26.4 52.8 10.0 20.0 0.0 0.0 0.0 0.0 0.0 0.0",
					DT = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 60.1 80.1 60.1 27.0 10.0 13.0 0.0 0.0 0.0 0.0 27.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 60.1 85.5 59.1 32.7 22.7 12.7 0.0 0.0 0.0 0.0 32.7 0.0",
					EL = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5279619 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.5146974 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					XOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 -900.0 -900.0 -900.0 -900.0 0.0 0.0 0.0 0.0 0.0 -900.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -48600.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					YOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					ZOFF = "0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 1200.0 1800.0 1800.0 1800.0 1800.0 600.0 0.0 0.0 0.0 0.0 1800.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 -1200.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0",
					LAMB = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
				}
			};

			return lst;
		}



		public static List<Tuple<string,List<Tuple<string,string>>>> DefaultRunwayTables()
		{
			List<Tuple<string,List<Tuple<string,string>>>> defaultrw = new List<Tuple<string,List<Tuple<string,string>>>>
			{
				new Tuple<string,List<Tuple<string,string>>>
				(
					"Low Inclination: 28.45º - 30.9º (Early)", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "KSC15", "KSC33" ),// 1
						new Tuple<string,string>( "CBA17", "CBA35" ),// 2
						new Tuple<string,string>( "OOY18", "OOY36" ),// 3
						new Tuple<string,string>( "AAT02", "AAT20" ),// 4
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 5
						new Tuple<string,string>( "DDN11", "DDN29" ),// 6
						new Tuple<string,string>( "ROZ28", "ROZ10" ),// 7
						new Tuple<string,string>( "KIN06", "KIN24" ),// 8
						new Tuple<string,string>( "LRB04", "LRB22" ),// 9
						new Tuple<string,string>( "JDG31", "JDG13" ),// 10
						new Tuple<string,string>( "DNA05L", "DNA23R" ),// 11
						new Tuple<string,string>( "GDV03L", "GDV21R" ),// 12
						new Tuple<string,string>( "YNN14", "YNN32" ),// 13
						new Tuple<string,string>( "PMR13", "PMR31" ),// 14
						new Tuple<string,string>( "AMB15", "AMB33" ),// 15
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 16
						new Tuple<string,string>( "MYR36", "MYR18" ),// 17
						new Tuple<string,string>( "AHS18", "AHS36" ),// 18
						new Tuple<string,string>( "NOR17", "NOR23" ),// 19
						new Tuple<string,string>( "NOR05", "NOR35" ),// 20
						new Tuple<string,string>( "EDW05R", "EDW23L" ),// 21
						new Tuple<string,string>( "EDW15", "EDW33" ),// 22
						new Tuple<string,string>( "EDW35", "EDW17" ),// 23
						new Tuple<string,string>( "EDW22", "EDW04" ),// 24
						new Tuple<string,string>( "KSC15", "KSC33" ),// 25

						new Tuple<string,string>( "JTY36", "JTY18" ),// 26
						new Tuple<string,string>( "GUA06L", "GUA24R" ),// 27
						new Tuple<string,string>( "WAK28", "WAK10" ),// 28
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 29
						new Tuple<string,string>( "HAO12", "HAO30" ),// 30
						new Tuple<string,string>( "HAW13", "HAW31" ),// 31
						new Tuple<string,string>( "KSC15", "KSC33" ),// 32
						new Tuple<string,string>( "YNN14", "YNN32" ),// 33
						new Tuple<string,string>( "PMR13", "PMR31" ),// 34
						new Tuple<string,string>( "MCO36L", "MCO18R" ),// 35
						new Tuple<string,string>( "NZC18L", "NZC36R" ),// 36
						new Tuple<string,string>( "MCF04", "MCF22" ),// 37
						new Tuple<string,string>( "NID03", "NID21" ),// 38
						new Tuple<string,string>( "VBG12", "VBG30" ),// 39
						new Tuple<string,string>( "LNK18", "LNK36" ),// 40
						new Tuple<string,string>( "NOR17", "NOR23" ),// 41
						new Tuple<string,string>( "NOR05", "NOR35" ),// 42
						new Tuple<string,string>( "EDW15", "EDW33" ),// 43
						new Tuple<string,string>( "EDW18L", "EDW18L" ),// 44
						new Tuple<string,string>( "EDW22", "EDW04" )// 45
					}
				),
				new Tuple<string,List<Tuple<string,string>>>
				(
					"Low Inclination: 28.45º - 30.9º (Late)", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "KSC15", "KSC33" ),// 1
						new Tuple<string,string>( "BEN36", "BEN18" ),// 2
						new Tuple<string,string>( "OOY36", "OOY36" ),// 3
						new Tuple<string,string>( "MRN20", "MRN02" ),// 4
						new Tuple<string,string>( "BYD32", "BYD14" ),// 5
						new Tuple<string,string>( "BDA30", "BDA12" ),// 6
						new Tuple<string,string>( "AML01", "AML19" ),// 7
						new Tuple<string,string>( "GDV03L", "GDV21R" ),// 8
						new Tuple<string,string>( "DYS16", "DYS34" ),// 9
						new Tuple<string,string>( "MRN20", "MRN02" ),// 10
						new Tuple<string,string>( "BEN36", "BEN18" ),// 11
						new Tuple<string,string>( "ILM06", "ILM24" ),// 12
						new Tuple<string,string>( "BYD32", "BYD14" ),// 13
						new Tuple<string,string>( "NKT32L", "NKT23R" ),// 14
						new Tuple<string,string>( "EIP10", "EIP28" ),// 15
						new Tuple<string,string>( "LRB04", "LRB22" ),// 16
						new Tuple<string,string>( "KIN24", "KIN06" ),// 17
						new Tuple<string,string>( "AHS18", "AHS36" ),// 18
						new Tuple<string,string>( "AAT02", "AAT20" ),// 19
						new Tuple<string,string>( "GSA29", "GSA11" ),// 20
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 21
						new Tuple<string,string>( "JDG31", "JDG13" ),// 22
						new Tuple<string,string>( "PEA18L", "PEA36R" ),// 23
						new Tuple<string,string>( "PTN14", "PTN32" ),// 24
						new Tuple<string,string>( "AMB15", "AMB33" ),// 25
						new Tuple<string,string>( "JTY36", "JTY18" ),// 26
						new Tuple<string,string>( "GUA06L", "GUA24R" ),// 27
						new Tuple<string,string>( "WAK28", "WAK10" ),// 28
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 29
						new Tuple<string,string>( "HAO12", "HAO30" ),// 30
						new Tuple<string,string>( "HAW13", "HAW31" ),// 31
						new Tuple<string,string>( "KSC15", "KSC33" ),// 32
						new Tuple<string,string>( "YNN14", "YNN32" ),// 33
						new Tuple<string,string>( "PMR13", "PMR31" ),// 34
						new Tuple<string,string>( "MCO36L", "MCO18R" ),// 35
						new Tuple<string,string>( "NZC18L", "NZC36R" ),// 36
						new Tuple<string,string>( "MCF04", "MCF22" ),// 37
						new Tuple<string,string>( "NID03", "NID21" ),// 38
						new Tuple<string,string>( "VBG12", "VBG30" ),// 39
						new Tuple<string,string>( "EDT22R", "EDT04L" ),// 40
						new Tuple<string,string>( "NOR17", "NOR23" ),// 41
						new Tuple<string,string>( "NOR05", "NOR35" ),// 42
						new Tuple<string,string>( "EDW15", "EDW33" ),// 43
						new Tuple<string,string>( "EDW18L", "EDW18L" ),// 44
						new Tuple<string,string>( "EDW22", "EDW04" )// 45
					}
				),
				new Tuple<string,List<Tuple<string,string>>>
				(
					"Mid Inclination: 31.0º - 49.9º (Early)", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "KSC15", "KSC33" ),// 1
						new Tuple<string,string>( "CBA17", "CBA35" ),// 2
						new Tuple<string,string>( "OOY18", "OOY36" ),// 3
						new Tuple<string,string>( "AAT02", "AAT20" ),// 4
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 5
						new Tuple<string,string>( "DDN11", "DDN29" ),// 6
						new Tuple<string,string>( "ROZ28", "ROZ10" ),// 7
						new Tuple<string,string>( "KIN06", "KIN24" ),// 8
						new Tuple<string,string>( "LAJ15", "LAJ33" ),// 9
						new Tuple<string,string>( "JDG31", "JDG13" ),// 10
						new Tuple<string,string>( "DNA05L", "DNA23R" ),// 11
						new Tuple<string,string>( "GDV03L", "GDV21R" ),// 12
						new Tuple<string,string>( "KBO14L", "KBO32R" ),// 13
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 14
						new Tuple<string,string>( "AMB15", "AMB33" ),// 15
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 16
						new Tuple<string,string>( "MYR36", "MYR18" ),// 17
						new Tuple<string,string>( "AHS18", "AHS36" ),// 18
						new Tuple<string,string>( "GSA29", "GSA11" ),// 19
						new Tuple<string,string>( "NOR17", "NOR23" ),// 20
						new Tuple<string,string>( "NOR05", "NOR35" ),// 21
						new Tuple<string,string>( "EDW05R", "EDW23L" ),// 22
						new Tuple<string,string>( "EDW15", "EDW33" ),// 23
						new Tuple<string,string>( "EDW35", "EDW17" ),// 24
						new Tuple<string,string>( "EDW22", "EDW04" ),// 25

						new Tuple<string,string>( "JTY36", "JTY18" ),// 26
						new Tuple<string,string>( "GUA06L", "GUA24R" ),// 27
						new Tuple<string,string>( "WAK28", "WAK10" ),// 28
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 29
						new Tuple<string,string>( "HAO12", "HAO30" ),// 30
						new Tuple<string,string>( "HAW13", "HAW31" ),// 31
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 32
						new Tuple<string,string>( "YNN14", "YNN32" ),// 33
						new Tuple<string,string>( "PMR13", "PMR31" ),// 34
						new Tuple<string,string>( "MCO36L", "MCO18R" ),// 35
						new Tuple<string,string>( "NZC18L", "NZC36R" ),// 36
						new Tuple<string,string>( "GUS23", "GUS05" ),// 37
						new Tuple<string,string>( "MWH14L", "MWH32R" ),// 38
						new Tuple<string,string>( "FFO23R", "FFO05L" ),// 39
						new Tuple<string,string>( "LNK18", "LNK36" ),// 40
						new Tuple<string,string>( "NKT32L", "NKT23R" ),// 41
						new Tuple<string,string>( "FMH32", "FMH23" ),// 42
						new Tuple<string,string>( "PBG35", "PBG17" ),// 43
						new Tuple<string,string>( "RCA13", "RCA31" ),// 44
						new Tuple<string,string>( "CEF05", "CEF23" )// 45
					}
				),
				new Tuple<string,List<Tuple<string,string>>>
				(
					"Mid Inclination: 31.0º - 49.9º (Late)", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "KSC15", "KSC33" ),// 1
						new Tuple<string,string>( "BEN36", "BEN18" ),// 2
						new Tuple<string,string>( "MRN20", "MRN02" ),// 3
						new Tuple<string,string>( "ZZA30L", "ZZA12R" ),// 4
						new Tuple<string,string>( "BYD32", "BYD14" ),// 5
						new Tuple<string,string>( "BDA30", "BDA12" ),// 6
						new Tuple<string,string>( "AML01", "AML19" ),// 7
						new Tuple<string,string>( "GDV03L", "GDV21R" ),// 8
						new Tuple<string,string>( "LAJ15", "LAJ33" ),// 9
						new Tuple<string,string>( "BEJ01L", "BEJ19R" ),// 10
						new Tuple<string,string>( "FMI33", "FMI15" ),// 11
						new Tuple<string,string>( "ILM06", "ILM24" ),// 12
						new Tuple<string,string>( "MRN20", "MRN02" ),// 13
						new Tuple<string,string>( "NKT32L", "NKT23R" ),// 14
						new Tuple<string,string>( "EIP10", "EIP28" ),// 15
						new Tuple<string,string>( "LRB04", "LRB22" ),// 16
						new Tuple<string,string>( "KIN24", "KIN06" ),// 17
						new Tuple<string,string>( "AHS18", "AHS36" ),// 18
						new Tuple<string,string>( "AAT02", "AAT20" ),// 19
						new Tuple<string,string>( "GSA29", "GSA11" ),// 20
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 21
						new Tuple<string,string>( "JDG31", "JDG13" ),// 22
						new Tuple<string,string>( "PEA18L", "PEA36R" ),// 23
						new Tuple<string,string>( "PTN14", "PTN32" ),// 24
						new Tuple<string,string>( "AMB15", "AMB33" ),// 25
						new Tuple<string,string>( "JTY36", "JTY18" ),// 26
						new Tuple<string,string>( "GUA06L", "GUA24R" ),// 27
						new Tuple<string,string>( "WAK28", "WAK10" ),// 28
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 29
						new Tuple<string,string>( "HAO12", "HAO30" ),// 30
						new Tuple<string,string>( "HAW13", "HAW31" ),// 31
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 32
						new Tuple<string,string>( "YNN14", "YNN32" ),// 33
						new Tuple<string,string>( "PMR13", "PMR31" ),// 34
						new Tuple<string,string>( "MCO36L", "MCO18R" ),// 35
						new Tuple<string,string>( "NZC18L", "NZC36R" ),// 36
						new Tuple<string,string>( "MCF04", "MCF22" ),// 37
						new Tuple<string,string>( "NID03", "NID21" ),// 38
						new Tuple<string,string>( "VBG12", "VBG30" ),// 39
						new Tuple<string,string>( "EDT22R", "EDT04L" ),// 40
						new Tuple<string,string>( "NOR17", "NOR23" ),// 41
						new Tuple<string,string>( "NOR05", "NOR35" ),// 42
						new Tuple<string,string>( "EDW15", "EDW33" ),// 43
						new Tuple<string,string>( "EDW18L", "EDW18L" ),// 44
						new Tuple<string,string>( "EDW22", "EDW04" )// 45
					}
				),
				new Tuple<string,List<Tuple<string,string>>>
				(
					"High Inclination: 50.0º - 63.5º (Early)", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "KSC15", "KSC33" ),// 1
						new Tuple<string,string>( "CBA17", "CBA35" ),// 2
						new Tuple<string,string>( "OOY18", "OOY36" ),// 3
						new Tuple<string,string>( "AAT02", "AAT20" ),// 4
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 5
						new Tuple<string,string>( "DDN11", "DDN29" ),// 6
						new Tuple<string,string>( "ROZ28", "ROZ10" ),// 7
						new Tuple<string,string>( "KIN06", "KIN24" ),// 8
						new Tuple<string,string>( "LAJ15", "LAJ33" ),// 9
						new Tuple<string,string>( "JDG31", "JDG13" ),// 10
						new Tuple<string,string>( "DNA05L", "DNA23R" ),// 11
						new Tuple<string,string>( "GDV03L", "GDV21R" ),// 12
						new Tuple<string,string>( "KBO14L", "KBO32R" ),// 13
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 14
						new Tuple<string,string>( "AMB15", "AMB33" ),// 15
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 16
						new Tuple<string,string>( "MYR36", "MYR18" ),// 17
						new Tuple<string,string>( "AHS18", "AHS36" ),// 18
						new Tuple<string,string>( "ARL01", "ARL19" ),// 19
						new Tuple<string,string>( "NOR17", "NOR23" ),// 20
						new Tuple<string,string>( "NOR05", "NOR35" ),// 21
						new Tuple<string,string>( "EDW05R", "EDW23L" ),// 22
						new Tuple<string,string>( "EDW15", "EDW33" ),// 23
						new Tuple<string,string>( "EDW35", "EDW17" ),// 24
						new Tuple<string,string>( "EDW22", "EDW04" ),// 25

						new Tuple<string,string>( "INN06", "INN24" ),// 26
						new Tuple<string,string>( "FFA27", "FFA09" ),// 27
						new Tuple<string,string>( "KBO14L", "KBO32R" ),// 28
						new Tuple<string,string>( "FMI33", "FMI15" ),// 29
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 30
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 31
						new Tuple<string,string>( "JDG31", "JDG13" ),// 32
						new Tuple<string,string>( "GUS23", "GUS05" ),// 33
						new Tuple<string,string>( "MWH14L", "MWH32R" ),// 34
						new Tuple<string,string>( "FFO23R", "FFO05L" ),// 35
						new Tuple<string,string>( "LNK18", "LNK36" ),// 36
						new Tuple<string,string>( "NKT32L", "NKT23R" ),// 37
						new Tuple<string,string>( "FMH32", "FMH23" ),// 38
						new Tuple<string,string>( "PBG35", "PBG17" ),// 39
						new Tuple<string,string>( "RCA13", "RCA31" ),// 40
						new Tuple<string,string>( "CEF23", "CEF05" ),// 41
						new Tuple<string,string>( "FFA27", "FFA09" ),// 42
						new Tuple<string,string>( "INN06", "INN06" ),// 43
						new Tuple<string,string>( "IKF11", "IKF29" ),// 44
						new Tuple<string,string>( "IKF29", "IKF02" )// 45
					}
				),
				new Tuple<string,List<Tuple<string,string>>>
				(
					"High Inclination: 50.0º - 63.5º (Late)", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "KSC15", "KSC33" ),// 1
						new Tuple<string,string>( "BEN36", "BEN18" ),// 2
						new Tuple<string,string>( "MRN20", "MRN02" ),// 3
						new Tuple<string,string>( "ZZA30L", "ZZA12R" ),// 4
						new Tuple<string,string>( "MYR36", "MYR18" ),// 5
						new Tuple<string,string>( "ILM06", "ILM24" ),// 6
						new Tuple<string,string>( "NKT32L", "NKT23R" ),// 7
						new Tuple<string,string>( "NTU32R", "NTU23L" ),// 8
						new Tuple<string,string>( "WAL28", "WAL04" ),// 9
						new Tuple<string,string>( "DOV32", "DOV19" ),// 10
						new Tuple<string,string>( "ACY31", "ACY13" ),// 11
						new Tuple<string,string>( "BEN36", "BEN18" ),// 12
						new Tuple<string,string>( "MRN20", "MRN02" ),// 13
						new Tuple<string,string>( "ZZA30L", "ZZA12R" ),// 14
						new Tuple<string,string>( "FOK06", "FOK24" ),// 15
						new Tuple<string,string>( "FMH32", "FMH23" ),// 16
						new Tuple<string,string>( "PSM34", "PSM16" ),// 17
						new Tuple<string,string>( "YHZ23", "YHZ32" ),// 18
						new Tuple<string,string>( "YJT09", "YJT27" ),// 19
						new Tuple<string,string>( "YYT29", "YYT11" ),// 20
						new Tuple<string,string>( "YQX21", "YQX31" ),// 21
						new Tuple<string,string>( "YYR26", "YYR34" ),// 22
						new Tuple<string,string>( "LAJ15", "LAJ33" ),// 23
						new Tuple<string,string>( "BEJ01L", "BEJ19R" ),// 24
						new Tuple<string,string>( "IKF20", "IKF29" ),// 25
						new Tuple<string,string>( "INN06", "INN24" ),// 26
						new Tuple<string,string>( "FFA27", "FFA09" ),// 27
						new Tuple<string,string>( "KBO14L", "KBO32R" ),// 28
						new Tuple<string,string>( "FMI33", "FMI15" ),// 29
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 30
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 31
						new Tuple<string,string>( "JDG31", "JDG13" ),// 32
						new Tuple<string,string>( "AMB15", "PTN14" ),// 33
						new Tuple<string,string>( "JTY36", "JTY18" ),// 34
						new Tuple<string,string>( "GUA06L", "GUA24R" ),// 35
						new Tuple<string,string>( "WAK28", "WAK10" ),// 36
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 37
						new Tuple<string,string>( "EDF24", "EDF06" ),// 38
						new Tuple<string,string>( "HAO12", "HAO30" ),// 39
						new Tuple<string,string>( "EDT22R", "EDT04L" ),// 40
						new Tuple<string,string>( "HAW13", "HAW31" ),// 41
						new Tuple<string,string>( "NOR17", "NOR23" ),// 42
						new Tuple<string,string>( "NOR05", "NOR35" ),// 43
						new Tuple<string,string>( "EDW15", "EDW18L" ),// 44
						new Tuple<string,string>( "EDW22", "EDW04" )// 45
					}
				),
				new Tuple<string,List<Tuple<string,string>>>
				(
					"Western Test Range", new List<Tuple<string, string>>
					{
						new Tuple<string,string>( "VBG30", "VBG12" ),// 1
						new Tuple<string,string>( "NKX24R", "NKX06L" ),// 2
						new Tuple<string,string>( "EIP28", "EIP10" ),// 3
						new Tuple<string,string>( "HAO12", "HAO30" ),// 4
						new Tuple<string,string>( "KSC15", "KSC33" ),// 5
						new Tuple<string,string>( "HNL08R", "HNL26L" ),// 6
						new Tuple<string,string>( "AAT02", "AAT20" ),// 7
						new Tuple<string,string>( "KBO14L", "KBO32R" ),// 8
						new Tuple<string,string>( "DNA05L", "DNA23R" ),// 9
						new Tuple<string,string>( "CBA17", "CBA35" ),// 10
						new Tuple<string,string>( "ARL01", "ARL19" ),// 11
						new Tuple<string,string>( "EDF24", "EDF06" ),// 12
						new Tuple<string,string>( "AHS18", "AHS36" ),// 13
						new Tuple<string,string>( "EST17", "EST35" ),// 14
						new Tuple<string,string>( "DDN11", "DDN29" ),// 15
						new Tuple<string,string>( "JDG31", "JDG13" ),// 16
						new Tuple<string,string>( "PBG35", "PBG17" ),// 17
						new Tuple<string,string>( "RCA13", "RCA31" ),// 18
						new Tuple<string,string>( "NOR17", "NOR23" ),// 19
						new Tuple<string,string>( "NOR05", "NOR35" ),// 20
						new Tuple<string,string>( "EDW05R", "EDW23L" ),// 21
						new Tuple<string,string>( "EDW15", "EDW33" ),// 22
						new Tuple<string,string>( "EDW35", "EDW17" ),// 23
						new Tuple<string,string>( "EDW22", "EDW04" ),// 24
						new Tuple<string,string>( "KSC15", "KSC33" ),// 25

						new Tuple<string,string>( "INN06", "INN24" ),// 26
						new Tuple<string,string>( "FFA27", "FFA09" ),// 27
						new Tuple<string,string>( "KBO14L", "KBO32R" ),// 28
						new Tuple<string,string>( "FMI33", "FMI15" ),// 29
						new Tuple<string,string>( "ESN03R", "ESN21L" ),// 30
						new Tuple<string,string>( "KKI15R", "KKI33L" ),// 31
						new Tuple<string,string>( "JDG31", "JDG13" ),// 32
						new Tuple<string,string>( "GUS23", "GUS05" ),// 33
						new Tuple<string,string>( "MWH14L", "MWH32R" ),// 34
						new Tuple<string,string>( "FFO23R", "FFO05L" ),// 35
						new Tuple<string,string>( "LNK18", "LNK36" ),// 36
						new Tuple<string,string>( "NKT32L", "NKT23R" ),// 37
						new Tuple<string,string>( "FMH32", "FMH23" ),// 38
						new Tuple<string,string>( "PBG35", "PBG17" ),// 39
						new Tuple<string,string>( "RCA13", "RCA31" ),// 40
						new Tuple<string,string>( "CEF23", "CEF05" ),// 41
						new Tuple<string,string>( "FFA27", "FFA09" ),// 42
						new Tuple<string,string>( "INN06", "INN06" ),// 43
						new Tuple<string,string>( "IKF11", "IKF29" ),// 44
						new Tuple<string,string>( "IKF29", "IKF02" )// 45
					}
				),
			};
	
			return defaultrw;
		}


		public struct XenonLightPosition
		{
			public string Name;
			public double Lon;
			public double Lat;
			public double ArotX;
			public double ArotY;
			public double ArotZ;
			public double Heading;
			public double Alt;
		};

		public struct XenonLightSite
		{
			public string Name;
			public List<XenonLightPosition> Positions;

			public override string ToString() { return Name; }
		};

		public static List<XenonLightSite> GetXenonLightList()
		{
			List<XenonLightSite> xenonlightlist = new List<XenonLightSite>
			{
				new XenonLightSite
				{
					Name = "KSC33",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -80.6812130,
							Lat = 28.593580,
							ArotX = 66.015,
							ArotY = 30.888,
							ArotZ = 9.536,
							Heading = 333.25,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -80.6811330,
							Lat = 28.593610,
							ArotX = 66.015,
							ArotY = 30.888,
							ArotZ = 9.537,
							Heading = 333.25,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -80.6801230,
							Lat = 28.594130,
							ArotX = 67.479,
							ArotY = 37.784,
							ArotZ = 10.365,
							Heading = 326.25,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -80.6800530,
							Lat = 28.594170,
							ArotX = 67.310,
							ArotY = 37.046,
							ArotZ = 10.262,
							Heading = 326.25,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "KSC15",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -80.7074930,
							Lat = 28.636170,
							ArotX = -114.374,
							ArotY = -29.157,
							ArotZ = 170.660,
							Heading = 154.25,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -80.7075830,
							Lat = 28.636130,
							ArotX = -114.374,
							ArotY = -29.157,
							ArotZ = 170.660,
							Heading = 154.25,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -80.7086130,
							Lat = 28.635640,
							ArotX = -112.753,
							ArotY = -37.041,
							ArotZ = 169.774,
							Heading = 146.25,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -80.7086930,
							Lat = 28.635590,
							ArotX = -112.753,
							ArotY = -37.041,
							ArotZ = 169.774,
							Heading = 146.25,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "EDW22",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -117.8583230,
							Lat = 34.917570,
							ArotX = -63.376,
							ArotY = 65.392,
							ArotZ = -113.052,
							Heading = 242.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -117.8583630,
							Lat = 34.917630,
							ArotX = -69.701,
							ArotY = 64.079,
							ArotZ = -118.773,
							Heading = 242.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -117.8591130,
							Lat = 34.918660,
							ArotX = -77.171,
							ArotY = 61.949,
							ArotZ = -125.432,
							Heading = 234.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -117.8591630,
							Lat = 34.918720,
							ArotX = -82.081,
							ArotY = 60.118,
							ArotZ = -129.729,
							Heading = 234.14,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "EDW04",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -117.9062830,
							Lat = 34.894720,
							ArotX = 116.727,
							ArotY = -65.360,
							ArotZ = -67.039,
							Heading = 62.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -117.9062230,
							Lat = 34.894630,
							ArotX = 110.404,
							ArotY = -64.052,
							ArotZ = -61.321,
							Heading = 62.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -117.9054930,
							Lat = 34.893610,
							ArotX = 102.931,
							ArotY = -61.927,
							ArotZ = -54.659,
							Heading = 54.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -117.9054230,
							Lat = 34.893530,
							ArotX = 99.593,
							ArotY = -60.728,
							ArotZ = -51.730,
							Heading = 54.14,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "EDT22R",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -117.8675030,
							Lat = 34.921210,
							ArotX = -65.236,
							ArotY = 65.041,
							ArotZ = -114.734,
							Heading = 242.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -117.8675530,
							Lat = 34.921290,
							ArotX = -65.235,
							ArotY = 65.041,
							ArotZ = -114.734,
							Heading = 242.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -117.8680530,
							Lat = 34.921940,
							ArotX = -80.268,
							ArotY = 60.834,
							ArotZ = -128.145,
							Heading = 234.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -117.8681030,
							Lat = 34.922010,
							ArotX = -80.268,
							ArotY = 60.834,
							ArotZ = -128.144,
							Heading = 234.14,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "EDT04L",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -117.9083530,
							Lat = 34.901540,
							ArotX = 114.853,
							ArotY = -65.015,
							ArotZ = -65.345,
							Heading = 62.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -117.9083030,
							Lat = 34.901460,
							ArotX = 114.853,
							ArotY = -65.015,
							ArotZ = -65.345,
							Heading = 62.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -117.9077730,
							Lat = 34.900690,
							ArotX = 99.817,
							ArotY = -60.818,
							ArotZ = -51.932,
							Heading = 54.14,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -117.9077130,
							Lat = 34.900620,
							ArotX = 99.817,
							ArotY = -60.818,
							ArotZ = -51.932,
							Heading = 54.14,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "EDW18L",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -117.8510930,
							Lat = 34.979540,
							ArotX = -110.536,
							ArotY = 36.449,
							ArotZ = -151.584,
							Heading = 203.17,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -117.8511930,
							Lat = 34.979570,
							ArotX = -110.536,
							ArotY = 36.449,
							ArotZ = -151.584,
							Heading = 203.17,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -117.8524630,
							Lat = 34.97990,
							ArotX = -114.893,
							ArotY = 29.332,
							ArotZ = -153.954,
							Heading = 195.17,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -117.8525630,
							Lat = 34.979920,
							ArotX = -114.893,
							ArotY = 29.332,
							ArotZ = -153.954,
							Heading = 195.17,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "NOR17",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -106.4160930,
							Lat = 32.963750,
							ArotX = -119.047,
							ArotY = 19.704,
							ArotZ = -165.412,
							Heading = 191.20,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -106.4161930,
							Lat = 32.963760,
							ArotX = -119.047,
							ArotY = 19.704,
							ArotZ = -165.412,
							Heading = 191.20,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -106.4174930,
							Lat = 32.963880,
							ArotX = -121.10,
							ArotY = 11.952,
							ArotZ = -165.972,
							Heading = 183.20,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -106.4175930,
							Lat = 32.963890,
							ArotX = -121.10,
							ArotY = 11.952,
							ArotZ = -165.972,
							Heading = 183.20,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "BEN36",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -7.8767530,
							Lat = 32.103150,
							ArotX = 85.086,
							ArotY = 31.765,
							ArotZ = 80.724,
							Heading = 0.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -7.8766530,
							Lat = 32.103150,
							ArotX = 85.086,
							ArotY = 31.765,
							ArotZ = 80.724,
							Heading = 0.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -7.8757330,
							Lat = 32.103180,
							ArotX = 94.482,
							ArotY = 32.709,
							ArotZ = 85.745,
							Heading = 352.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -7.8756330,
							Lat = 32.103190,
							ArotX = 94.482,
							ArotY = 32.709,
							ArotZ = 85.745,
							Heading = 352.0,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "MRN20",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -5.6072630,
							Lat = 37.192540,
							ArotX = -122.012,
							ArotY = -30.731,
							ArotZ = 112.733,
							Heading = 203.80,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -5.6073630,
							Lat = 37.192580,
							ArotX = -122.012,
							ArotY = -30.731,
							ArotZ = 112.733,
							Heading = 203.80,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -5.6086230,
							Lat = 37.19290,
							ArotX = -113.156,
							ArotY = -33.523,
							ArotZ = 108.016,
							Heading = 195.80,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -5.6087330,
							Lat = 37.192930,
							ArotX = -113.156,
							ArotY = -33.523,
							ArotZ = 108.017,
							Heading = 195.80,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "ZZA30L",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -1.0399630,
							Lat = 41.661440,
							ArotX = 153.063,
							ArotY = 22.749,
							ArotZ = 125.907,
							Heading = 304.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -1.0399030,
							Lat = 41.661510,
							ArotX = 153.063,
							ArotY = 22.749,
							ArotZ = 125.907,
							Heading = 304.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -1.0394030,
							Lat = 41.662190,
							ArotX = 159.868,
							ArotY = 17.918,
							ArotZ = 128.277,
							Heading = 296.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -1.0393530,
							Lat = 41.662270,
							ArotX = 159.868,
							ArotY = 17.918,
							ArotZ = 128.277,
							Heading = 296.0,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "BYD32",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -16.6372030,
							Lat = 13.324590,
							ArotX = 132.516,
							ArotY = 21.014,
							ArotZ = 87.156,
							Heading = 315.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -16.6371430,
							Lat = 13.324650,
							ArotX = 132.516,
							ArotY = 21.014,
							ArotZ = 87.157,
							Heading = 315.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -16.6366230,
							Lat = 13.325230,
							ArotX = 141.090,
							ArotY = 21.195,
							ArotZ = 90.250,
							Heading = 307.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -16.6365630,
							Lat = 13.32530,
							ArotX = 141.090,
							ArotY = 21.195,
							ArotZ = 90.250,
							Heading = 307.0,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "HNL08R",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = -157.9482730,
							Lat = 21.307190,
							ArotX = -176.020,
							ArotY = -20.551,
							ArotZ = -112.754,
							Heading = 94.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = -157.9482830,
							Lat = 21.307110,
							ArotX = -176.020,
							ArotY = -20.551,
							ArotZ = -112.753,
							Heading = 94.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = -157.9482730,
							Lat = 21.306220,
							ArotX = 175.938,
							ArotY = -23.455,
							ArotZ = -109.734,
							Heading = 86.0,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = -157.9482630,
							Lat = 21.306140,
							ArotX = 175.938,
							ArotY = -23.455,
							ArotZ = -109.734,
							Heading = 86.0,
							Alt = 1.997
						}
					}
				},
				new XenonLightSite
				{
					Name = "GUA06L",
					Positions = new List<XenonLightPosition>
					{
						new XenonLightPosition
						{
							Name = "LL",
							Lon = 144.9119630,
							Lat = 13.579020,
							ArotX = 157.503,
							ArotY = 28.195,
							ArotZ = -115.514,
							Heading = 69.70,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "L",
							Lon = 144.9119930,
							Lat = 13.578940,
							ArotX = 157.503,
							ArotY = 28.195,
							ArotZ = -115.514,
							Heading = 69.70,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "R",
							Lon = 144.9123330,
							Lat = 13.578190,
							ArotX = 149.567,
							ArotY = 24.522,
							ArotZ = -119.042,
							Heading = 61.70,
							Alt = 1.997
						},
						new XenonLightPosition
						{
							Name = "RR",
							Lon = 144.9123730,
							Lat = 13.578110,
							ArotX = 149.567,
							ArotY = 24.522,
							ArotZ = -119.042,
							Heading = 61.70,
							Alt = 1.997
						}
					}
				}
			};

			return xenonlightlist;
		}
	}
}
