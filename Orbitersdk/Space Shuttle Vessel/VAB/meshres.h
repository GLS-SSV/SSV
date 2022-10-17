// ======================================================
// Created by ssvmeshc 1.1
// Input file: exterior_1980.msh
// ======================================================

#ifndef _MESH_EXTERIOR_1980_H_
#define _MESH_EXTERIOR_1980_H_

inline constexpr unsigned int NUMGRP_VAB = 89;

inline constexpr unsigned int GRP_GROUP_1_STATIC_VAB	=	0;	//Group_1_STATIC
inline constexpr unsigned int GRP_GROUP_169_VAB	=	1;	//Group_169
inline constexpr unsigned int GRP_GROUP_76_VAB	=	2;	//Group_76
inline constexpr unsigned int GRP_GROUP_147_VAB	=	3;	//Group_147
inline constexpr unsigned int GRP_BOX_VAB	=	4;	//box
inline constexpr unsigned int GRP_BOX2_VAB	=	5;	//box2
inline constexpr unsigned int GRP_BOX3_VAB	=	6;	//box3
inline constexpr unsigned int GRP_GROUP_166_VAB	=	7;	//Group_166
inline constexpr unsigned int GRP_VAB_FLOOR_VAB	=	8;	//VAB_floor
inline constexpr unsigned int GRP_MESH_VAB	=	9;	//mesh
inline constexpr unsigned int GRP_A_VAB	=	10;	//A
inline constexpr unsigned int GRP_A1_VAB	=	11;	//A1
inline constexpr unsigned int GRP_R_VAB	=	12;	//R
inline constexpr unsigned int GRP_NORTH_ENTRANCE_TAIL1_VAB	=	13;	//North_entrance_tail1
inline constexpr unsigned int GRP_BOX4_VAB	=	14;	//box4
inline constexpr unsigned int GRP_HB3_HORIZONTAL_DOOR_R2_VAB	=	15;	//HB3_Horizontal_door_R2
inline constexpr unsigned int GRP_BLOCK_VAB	=	16;	//block
inline constexpr unsigned int GRP_HB3_VLD1_VAB	=	17;	//HB3_VLD1
inline constexpr unsigned int GRP_HB3_VLD2_VAB	=	18;	//HB3_VLD2
inline constexpr unsigned int GRP_HB1_VLD1_VAB	=	19;	//HB1_VLD1
inline constexpr unsigned int GRP_HB1_VLD5_VAB	=	20;	//HB1_VLD5
inline constexpr unsigned int GRP_HB1_VLD6_VAB	=	21;	//HB1_VLD6
inline constexpr unsigned int GRP_HB1_VLD7_VAB	=	22;	//HB1_VLD7
inline constexpr unsigned int GRP_HB1_HORIZONTAL_DOOR_L1_VAB	=	23;	//HB1_Horizontal_door_L1
inline constexpr unsigned int GRP_HB1_HORIZONTAL_DOOR_R1_VAB	=	24;	//HB1_Horizontal_door_R1
inline constexpr unsigned int GRP_HB1_HORIZONTAL_DOOR_L2_VAB	=	25;	//HB1_Horizontal_door_L2
inline constexpr unsigned int GRP_HB1_HORIZONTAL_DOOR_R2_VAB	=	26;	//HB1_Horizontal_door_R2
inline constexpr unsigned int GRP_HB1_VLD2_VAB	=	27;	//HB1_VLD2
inline constexpr unsigned int GRP_HB1_VLD4_VAB	=	28;	//HB1_VLD4
inline constexpr unsigned int GRP_HB1_VLD3_VAB	=	29;	//HB1_VLD3
inline constexpr unsigned int GRP_VAB_FLOORA_VAB	=	30;	//VAB_floor
inline constexpr unsigned int GRP_DOORBOX_VAB	=	31;	//doorbox
inline constexpr unsigned int GRP_BLOCK2_VAB	=	32;	//block2
inline constexpr unsigned int GRP_XFER_AISLE_CRANE_RAIL_VAB	=	33;	//Xfer_aisle_crane_rail
inline constexpr unsigned int GRP_BLOCK3_VAB	=	34;	//block3
inline constexpr unsigned int GRP_BLOCK4_VAB	=	35;	//block4
inline constexpr unsigned int GRP_HB3_VLD7_VAB	=	36;	//HB3_VLD7
inline constexpr unsigned int GRP_HB3_VLD6_VAB	=	37;	//HB3_VLD6
inline constexpr unsigned int GRP_HB3_VLD5_VAB	=	38;	//HB3_VLD5
inline constexpr unsigned int GRP_HB3_VLD4_VAB	=	39;	//HB3_VLD4
inline constexpr unsigned int GRP_HB3_VLD3_VAB	=	40;	//HB3_VLD3
inline constexpr unsigned int GRP_DOORBOX1_VAB	=	41;	//doorbox1
inline constexpr unsigned int GRP_BLOCK5_VAB	=	42;	//block5
inline constexpr unsigned int GRP_BLOCK6_VAB	=	43;	//block6
inline constexpr unsigned int GRP_BLOCK7_VAB	=	44;	//block7
inline constexpr unsigned int GRP_GROUP_146_VAB	=	45;	//Group_146
inline constexpr unsigned int GRP_HB3_HORIZONTAL_DOOR_L1_VAB	=	46;	//HB3_Horizontal_door_L1
inline constexpr unsigned int GRP_HB3_HORIZONTAL_DOOR_R1_VAB	=	47;	//HB3_Horizontal_door_R1
inline constexpr unsigned int GRP_HB3_HORIZONTAL_DOOR_L2_VAB	=	48;	//HB3_Horizontal_door_L2
inline constexpr unsigned int GRP_HB2_HORIZONTAL_DOOR_L2_VAB	=	49;	//HB2_Horizontal_door_L2
inline constexpr unsigned int GRP_HB2_HORIZONTAL_DOOR_R2_VAB	=	50;	//HB2_Horizontal_door_R2
inline constexpr unsigned int GRP_HB2_HORIZONTAL_DOOR_R1_VAB	=	51;	//HB2_Horizontal_door_R1
inline constexpr unsigned int GRP_HB2_HORIZONTAL_DOOR_L1_VAB	=	52;	//HB2_Horizontal_door_L1
inline constexpr unsigned int GRP_HB2_VLD3_VAB	=	53;	//HB2_VLD3
inline constexpr unsigned int GRP_HB2_VLD4_VAB	=	54;	//HB2_VLD4
inline constexpr unsigned int GRP_HB2_VLD5_VAB	=	55;	//HB2_VLD5
inline constexpr unsigned int GRP_HB2_VLD6_VAB	=	56;	//HB2_VLD6
inline constexpr unsigned int GRP_HB2_VLD7_VAB	=	57;	//HB2_VLD7
inline constexpr unsigned int GRP_HB4_VLD2_VAB	=	58;	//HB4_VLD2
inline constexpr unsigned int GRP_HB4_VLD3_VAB	=	59;	//HB4_VLD3
inline constexpr unsigned int GRP_HB4_VLD4_VAB	=	60;	//HB4_VLD4
inline constexpr unsigned int GRP_HB4_HORIZONTAL_DOOR_R2_VAB	=	61;	//HB4_Horizontal_door_R2
inline constexpr unsigned int GRP_HB4_HORIZONTAL_DOOR_L2_VAB	=	62;	//HB4_Horizontal_door_L2
inline constexpr unsigned int GRP_HB4_HORIZONTAL_DOOR_R1_VAB	=	63;	//HB4_Horizontal_door_R1
inline constexpr unsigned int GRP_HB4_HORIZONTAL_DOOR_L1_VAB	=	64;	//HB4_Horizontal_door_L1
inline constexpr unsigned int GRP_HB4_VLD7_VAB	=	65;	//HB4_VLD7
inline constexpr unsigned int GRP_HB4_VLD6_VAB	=	66;	//HB4_VLD6
inline constexpr unsigned int GRP_HB4_VLD5_VAB	=	67;	//HB4_VLD5
inline constexpr unsigned int GRP_HB4_VLD1_VAB	=	68;	//HB4_VLD1
inline constexpr unsigned int GRP_HB2_VLD2_VAB	=	69;	//HB2_VLD2
inline constexpr unsigned int GRP_HB2_VLD1_VAB	=	70;	//HB2_VLD1
inline constexpr unsigned int GRP_BLOCK8_VAB	=	71;	//block8
inline constexpr unsigned int GRP_LOWBAY_ENTRANCE1_VAB	=	72;	//LowBay_entrance1
inline constexpr unsigned int GRP_GROUP_160_VAB	=	73;	//Group_160
inline constexpr unsigned int GRP_GROUP_161_VAB	=	74;	//Group_161
inline constexpr unsigned int GRP_GROUP_162_VAB	=	75;	//Group_162
inline constexpr unsigned int GRP_GROUP_164_VAB	=	76;	//Group_164
inline constexpr unsigned int GRP_GROUP_165_VAB	=	77;	//Group_165
inline constexpr unsigned int GRP_GROUP_166A_VAB	=	78;	//Group_166
inline constexpr unsigned int GRP_GROUP_167_VAB	=	79;	//Group_167
inline constexpr unsigned int GRP_BLOCK9_VAB	=	80;	//block9
inline constexpr unsigned int GRP_BLOCK10_VAB	=	81;	//block10
inline constexpr unsigned int GRP_NORTH_ENTRANCE_R1_VAB	=	82;	//North_entrance_R1
inline constexpr unsigned int GRP_NORTH_ENTRANCE_L1_VAB	=	83;	//North_entrance_L1
inline constexpr unsigned int GRP_BOX5_VAB	=	84;	//box5
inline constexpr unsigned int GRP_VAB_FLOORB_VAB	=	85;	//VAB_floor
inline constexpr unsigned int GRP_MLP_PEDESTAL_BOX_VAB	=	86;	//MLP_pedestal_box
inline constexpr unsigned int GRP_MLP_PEDESTALS_LIGHTYELLOW_VAB	=	87;	//MLP_pedestals_lightyellow
inline constexpr unsigned int GRP_MLP_PEDESTALS_YELLOW_VAB	=	88;	//MLP_pedestals_yellow

#endif// _MESH_EXTERIOR_1980_H_
