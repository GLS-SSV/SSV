// ======================================================
// Created by ssvmeshc 1.2
// Input file: FSS.msh
// ======================================================

#ifndef _MESH_FSS_H_
#define _MESH_FSS_H_

inline constexpr unsigned int NUMGRP_FSS = 63;

inline constexpr unsigned int GRP_ELEVATOR_ROOM_FSS	=	0;	//Elevator_room
inline constexpr unsigned int GRP_GH2_AFT_VENT_FLEX_HOSE_FSS	=	1;	//GH2_aft_vent_flex_hose
inline constexpr unsigned int GRP_GH2_AFT_VENT_HARD_LINE_FSS	=	2;	//GH2_aft_vent_hard_line
inline constexpr unsigned int GRP_GH2_FWD_VENT_FLEX_LINE_FSS	=	3;	//GH2_fwd_vent_flex_line
inline constexpr unsigned int GRP_GH2_PIVOT_POINT_FSS	=	4;	//GH2_Pivot_point
inline constexpr unsigned int GRP_GH2_VENT_HARD_LINE_FSS	=	5;	//GH2_vent_hard_line
inline constexpr unsigned int GRP_GH2_VENT_LINE_HAUNCH_FSS	=	6;	//GH2_vent_line_haunch
inline constexpr unsigned int GRP_GUCP_FSS	=	7;	//GUCP
inline constexpr unsigned int GRP_GVA_LATCH_BACK_COLUMNS_FSS	=	8;	//GVA_Latch_Back_columns
inline constexpr unsigned int GRP_HINGE_COLUMNS_FSS	=	9;	//Hinge_columns
inline constexpr unsigned int GRP_HINGE_COLUMNS_GVA_PLATFORM_FSS	=	10;	//Hinge_columns_GVA_platform
inline constexpr unsigned int GRP_IAA_EXTENSIBLE_PLATFORM_FSS	=	11;	//IAA_extensible_platform
inline constexpr unsigned int GRP_INTERTANK_ACCESS_ARM_FSS	=	12;	//Intertank_Access_Arm
inline constexpr unsigned int GRP_MAIN_FSS_STRUCTURE_FSS	=	13;	//Main_FSS_structure
inline constexpr unsigned int GRP_MAIN_FSS_STRUCTURE_OWP_FSS	=	14;	//Main_FSS_structure_OWP
inline constexpr unsigned int GRP_OTV_CAM_01_FSS	=	15;	//OTV_Cam_01
inline constexpr unsigned int GRP_OTV_CAM_03_FSS	=	16;	//OTV_Cam_03
inline constexpr unsigned int GRP_OTV_CAM_07_FSS	=	17;	//OTV_Cam_07
inline constexpr unsigned int GRP_OTV_CAM_08_FSS	=	18;	//OTV_Cam_08
inline constexpr unsigned int GRP_OTV_CAM_09_FSS	=	19;	//OTV_Cam_09
inline constexpr unsigned int GRP_OTV_CAM_12_FSS	=	20;	//OTV_Cam_12
inline constexpr unsigned int GRP_OTV_CAM_49_FSS	=	21;	//OTV_Cam_49
inline constexpr unsigned int GRP_OTV_CAM_61_FSS	=	22;	//OTV_Cam_61
inline constexpr unsigned int GRP_OTV_CAM_63_FSS	=	23;	//OTV_Cam_63
inline constexpr unsigned int GRP_OTV_CAM_64_FSS	=	24;	//OTV_Cam_64
inline constexpr unsigned int GRP_OTV_CAM_SUPPORT_FSS	=	25;	//OTV_cam_support
inline constexpr unsigned int GRP_OTV_CAMERA_STANDS_FSS	=	26;	//OTV_camera_stands
inline constexpr unsigned int GRP_WHITE_ROOM_FSS	=	27;	//White_Room
inline constexpr unsigned int GRP_ORBITER_ACCESS_ARM_FSS	=	28;	//Orbiter_Access_Arm
inline constexpr unsigned int GRP_FSS_LEVELS_FSS	=	29;	//FSS_levels
inline constexpr unsigned int GRP_OUTER_OWP_CURTAIN_WALL_PANEL_FSS	=	30;	//Outer_OWP_Curtain_Wall_panel
inline constexpr unsigned int GRP_INNER_OWP_CURTAIN_WALL_STRUCTURE_FSS	=	31;	//Inner_OWP_Curtain_Wall_structure
inline constexpr unsigned int GRP_LIGHTNING_MAST_NEW_FSS	=	32;	//Lightning_mast_new
inline constexpr unsigned int GRP_INNER_OWP_CURTAIN_WALL_PANEL_FSS	=	33;	//Inner_OWP_Curtain_Wall_panel
inline constexpr unsigned int GRP_LIGHTNING_MAST_BASE_NEW_FSS	=	34;	//Lightning_mast_base_new
inline constexpr unsigned int GRP_PHOTO_TARGET_01_FSS	=	35;	//Photo_target_01
inline constexpr unsigned int GRP_PHOTO_TARGET_02_FSS	=	36;	//Photo_target_02
inline constexpr unsigned int GRP_PHOTO_TARGET_03_FSS	=	37;	//Photo_target_03
inline constexpr unsigned int GRP_PHOTO_TARGET_04_FSS	=	38;	//Photo_target_04
inline constexpr unsigned int GRP_NORTH_GOX_VENT_CYLINDER_02_FSS	=	39;	//North_GOX_vent_cylinder_02
inline constexpr unsigned int GRP_SOUTH_GOX_VENT_CYLINDER_02_FSS	=	40;	//South_GOX_vent_cylinder_02
inline constexpr unsigned int GRP_SOUTH_GOX_VENT_CYLINDER_01_FSS	=	41;	//South_GOX_vent_cylinder_01
inline constexpr unsigned int GRP_SOUTH_GOX_DOCKSEAL_FSS	=	42;	//South_GOX_dockseal
inline constexpr unsigned int GRP_NORTH_GOX_DOCKSEAL_FSS	=	43;	//North_GOX_dockseal
inline constexpr unsigned int GRP_NORTH_GOX_VENT_CYLINDER_01_FSS	=	44;	//North_GOX_vent_cylinder_01
inline constexpr unsigned int GRP_SOUTH_GOX_VENT_CYLINDER_03_FSS	=	45;	//South_GOX_vent_cylinder_03
inline constexpr unsigned int GRP_GVA_SWING_ARM_FENCES_FSS	=	46;	//GVA_swing_arm_fences
inline constexpr unsigned int GRP_GVA_SWING_ARM_FSS	=	47;	//GVA_swing_arm
inline constexpr unsigned int GRP_GOX_VENT_PIPES_FSS	=	48;	//GOX_vent_pipes
inline constexpr unsigned int GRP_GOX_VENT_HOOD_FSS	=	49;	//GOX_Vent_Hood
inline constexpr unsigned int GRP_NORTH_GOX_VENT_CYLINDER_03_FSS	=	50;	//North_GOX_vent_cylinder_03
inline constexpr unsigned int GRP_GVA_ACCESS_PLATFORM_FSS	=	51;	//GVA_access_platform
inline constexpr unsigned int GRP_OUTER_OWP_CURTAIN_WALL_STRUTS_FSS	=	52;	//Outer_OWP_Curtain_Wall_struts
inline constexpr unsigned int GRP_NORTH_CURTAIN_WALL_STRUTS_FSS	=	53;	//North_Curtain_Wall_struts
inline constexpr unsigned int GRP_RBUS_CARRIER_PLATE_FSS	=	54;	//RBUS_carrier_plate
inline constexpr unsigned int GRP_RBUS_INCLINE_STRUCTURE_FSS	=	55;	//RBUS_incline_structure
inline constexpr unsigned int GRP_RBUS_PLATFORM_FSS	=	56;	//RBUS_Platform
inline constexpr unsigned int GRP_RBUS_UMBILICAL_BEAM_FSS	=	57;	//RBUS_umbilical_beam
inline constexpr unsigned int GRP_LIGHTNING_MAST_FSS	=	58;	//Lightning_mast
inline constexpr unsigned int GRP_LIGHTNING_MAST_BOTTOM_FSS	=	59;	//Lightning_mast_bottom
inline constexpr unsigned int GRP_LIGHTNING_MAST_BASE_FSS	=	60;	//Lightning_mast_base
inline constexpr unsigned int GRP_HAMMERHEAD_CRANE_TRUSS_FSS	=	61;	//Hammerhead_crane_truss
inline constexpr unsigned int GRP_HAMMERHEAD_CRANE_COUNTERWEIGHT_FSS	=	62;	//Hammerhead_crane_counterweight

#endif// _MESH_FSS_H_
