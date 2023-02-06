/****************************************************************************
  This file is part of Space Shuttle Vessel

  PRLA and related definitions


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
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
#ifndef __PRLA_DEFS_H
#define __PRLA_DEFS_H


const static char* MESHNAME_PRLA_PORT_ACTIVE = "SSV\\OV\\PRLA_Port_Active";
const static char* MESHNAME_PRLA_STBD_ACTIVE = "SSV\\OV\\PRLA_Starboard_Active";
const static char* MESHNAME_AKA_FWD = "SSV\\OV\\AKA_Forward";
const static char* MESHNAME_AKA_AFT = "SSV\\OV\\AKA_Aft";


inline constexpr int PLID_Xo_base = 154;// PLID of base index
inline constexpr double PLID_Xo[] = {// Xo coordinates of PLIDs
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


inline constexpr int PLID_AKA_base = 154;// PLID of base index
inline constexpr bool PLID_AKA_FWD[] = {// true if AKA is fwd version
	/*154-155*/false, false,
	/*bay  1: 156-157*/false, false,
	/*158-165*/false, false, false, false, false, false, false, false,
	/*bay  2: 166-172*/true, true, true, false, false, false, false,
	/*173-179*/false, false, false, false, false, false, false,
	/*bay  3: 180-186*/true, true, true, true, false, false, false,
	/*187-194*/false, false, false, false, false, false, false, false,
	/*bay  4: 195-201*/true, true, true, false, false, false, false,
	/*202-208*/false, false, false, false, false, false, false,
	/*bay  5: 209-215*/true, true, true, false, false, false, false,
	/*216-222*/false, false, false, false, false, false, false,
	/*bay  6: 223-229*/true, true, true, true, false, false, false,
	/*230-237*/false, false, false, false, false, false, false, false,
	/*bay  7: 238-244*/true, true, true, false, false, false, false,
	/*245-252*/false, false, false, false, false, false, false, false,
	/*bay  8: 253-260*/true, true, true, true, false, false, false, false,
	/*261-267*/false, false, false, false, false, false, false,
	/*bay  9: 268-273*/true, true, true, false, false, false,
	/*274-280*/false, false, false, false, false, false, false,
	/*bay 10: 281-285*/true, true, true, false, false,
	/*286-293*/false, false, false, false, false, false, false, false,
	/*bay 11: 294-298*/true, true, false, false, false,
	/*299-305*/false, false, false, false, false, false, false,
	/*bay 12: 306-311*/true, true, true, false, false, false,
	/*312-330*/false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};
inline constexpr bool PLID_AKA_onesided[] = {// true if AKA is one sided version
	/*154-155*/false, false,
	/*bay  1: 156-157*/false, false,
	/*158-165*/false, false, false, false, false, false, false, false,
	/*bay  2: 166-172*/false, false, false, false, false, false, true,
	/*173-179*/false, false, false, false, false, false, false,
	/*bay  3: 180-186*/true, false, false, false, false, false, false,
	/*187-194*/false, false, false, false, false, false, false, false,
	/*bay  4: 195-201*/false, false, false, false, false, false, true,
	/*202-208*/false, false, false, false, false, false, false,
	/*bay  5: 209-215*/true, false, false, false, false, false, false,
	/*216-222*/false, false, false, false, false, false, false,
	/*bay  6: 223-229*/true, true, false, false, false, false, false,
	/*230-237*/false, false, false, false, false, false, false, false,
	/*bay  7: 238-244*/false, false, false, false, false, false, false,
	/*245-252*/false, false, false, false, false, false, false, false,
	/*bay  8: 253-260*/false, false, false, false, false, false, false, false,
	/*261-267*/false, false, false, false, false, false, false,
	/*bay  9: 268-273*/true, false, false, false, false, true,
	/*274-280*/false, false, false, false, false, false, false,
	/*bay 10: 281-285*/true, false, false, false, false,
	/*286-293*/false, false, false, false, false, false, false, false,
	/*bay 11: 294-298*/false, false, false, false, false,
	/*299-305*/false, false, false, false, false, false, false,
	/*bay 12: 306-311*/false, false, false, false, false, false,
	/*312-330*/false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};


const VECTOR3 PRLA_HOOK_HINGE_POS = _V( 0.0, -0.0715, -0.086696 );
const VECTOR3 PRLA_HOOK_HINGE_DIR = _V( -1.0, 0.0, 0.0 );
const double PRLA_HOOK_HINGE_ANG = 90.0 * RAD;

const VECTOR3 AKA_FWD_DYNAMIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, -0.1143 );
const VECTOR3 AKA_FWD_STATIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, 0.1143 );
const VECTOR3 AKA_AFT_DYNAMIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, 0.1143 );
const VECTOR3 AKA_AFT_STATIC_LATCH_OPEN_TRANSLATION = _V( 0.0, 0.0, -0.1143 );


#endif// __PRLA_DEFS_H
