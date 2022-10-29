// ======================================================
// Created by ssvmeshc 1.2
// Input file: SLWT.msh
// ======================================================

#ifndef _MESH_SLWT_H_
#define _MESH_SLWT_H_

inline constexpr unsigned int NUMGRP_SLWT = 70;

inline constexpr unsigned int GRP_SRB_THRUST_BEAM_SLWT	=	0;	//SRB_THRUST_BEAM
inline constexpr unsigned int GRP_MSH_OBJECT_55_SLWT	=	1;	//MSH_object_55
inline constexpr unsigned int GRP_NOSECONE_SLWT	=	2;	//NOSECONE
inline constexpr unsigned int GRP_LOX_IFRS_SLWT	=	3;	//LOX_IFRs
inline constexpr unsigned int GRP_LH2_PAL_RAMP_SLWT	=	4;	//LH2_PAL_RAMP
inline constexpr unsigned int GRP_LOX_PAL_RAMP_SLWT	=	5;	//LOX_PAL_RAMP
inline constexpr unsigned int GRP_LH2_TANK_IFRS_SLWT	=	6;	//LH2_TANK_IFRS
inline constexpr unsigned int GRP_BIPOD_SPINDLES_SLWT	=	7;	//BIPOD_SPINDLES
inline constexpr unsigned int GRP_MINUSY_BIPOD_STRUT_SPINDLE_ENDCAP_SLWT	=	8;	//-Y_BIPOD_STRUT_SPINDLE_ENDCAP
inline constexpr unsigned int GRP_PLUSY_BIPOD_STRUT_SPINDLE_ENDCAP_SLWT	=	9;	//+Y_BIPOD_STRUT_SPINDLE_ENDCAP
inline constexpr unsigned int GRP_BIPOD_YOKE_SLWT	=	10;	//BIPOD_YOKE
inline constexpr unsigned int GRP_BIPOD_FOAM_RAMPS_SLWT	=	11;	//BIPOD_FOAM_RAMPS
inline constexpr unsigned int GRP_LOX_FEEDLINE_FAIRING_SLWT	=	12;	//LOX_FEEDLINE_FAIRING
inline constexpr unsigned int GRP_ORBITER_XBEAM_SLWT	=	13;	//ORBITER_XBEAM
inline constexpr unsigned int GRP_BALL_INTERFACE_FITTINGS_SLWT	=	14;	//BALL_INTERFACE_FITTINGS
inline constexpr unsigned int GRP_DIAGONAL_THRUST_STRUTS_SLWT	=	15;	//DIAGONAL_THRUST_STRUTS
inline constexpr unsigned int GRP_LH2_TANK_SLWT	=	16;	//LH2_TANK
inline constexpr unsigned int GRP_AFT_UPPER_SRB_ATTACHMENTS_SLWT	=	17;	//AFT_UPPER_SRB_ATTACHMENTS
inline constexpr unsigned int GRP_AFT_LOX_CABLE_TRAY_SLWT	=	18;	//AFT_LOX_CABLE_TRAY
inline constexpr unsigned int GRP_AFT_X_BEAM_CABLE_TRAY_SLWT	=	19;	//AFT_X_BEAM_CABLE_TRAY
inline constexpr unsigned int GRP_BOLT_CATCHERS_SLWT	=	20;	//BOLT_CATCHERS
inline constexpr unsigned int GRP_AFT_LOWER_SRB_ATTACHMENTS_BRACKETS_SLWT	=	21;	//AFT_LOWER_SRB_ATTACHMENTS_BRACKETS
inline constexpr unsigned int GRP_Z_LOX_TANK_SQUARE_SLWT	=	22;	//Z_LOX_TANK_SQUARE
inline constexpr unsigned int GRP_BOX16_SLWT	=	23;	//Box16
inline constexpr unsigned int GRP_CABLE_TRAY_TRANSITIONS_SLWT	=	24;	//CABLE_TRAY_TRANSITIONS
inline constexpr unsigned int GRP_AFT_VERTICAL_STRUT_HINGES_SLWT	=	25;	//AFT_VERTICAL_STRUT_HINGES
inline constexpr unsigned int GRP_MINUSY_BIPOD_STRUT_YOKE_ENDCAP_SLWT	=	26;	//-Y_BIPOD_STRUT_YOKE_ENDCAP
inline constexpr unsigned int GRP_BIPOD_STRUTS_SLWT	=	27;	//BIPOD_STRUTS
inline constexpr unsigned int GRP_PLUSY_BIPOD_STRUT_YOKE_ENDCAP_SLWT	=	28;	//+Y_BIPOD_STRUT_YOKE_ENDCAP
inline constexpr unsigned int GRP_DIAGONAL_STRUT_SLWT	=	29;	//DIAGONAL_STRUT
inline constexpr unsigned int GRP_ETCA_CUTOUT_SLWT	=	30;	//ETCA_CUTOUT
inline constexpr unsigned int GRP_FWD_SRB_THRUST_FITTINGS_SLWT	=	31;	//FWD_SRB_THRUST_FITTINGS
inline constexpr unsigned int GRP_GH2_PRESS_LINE_SLWT	=	32;	//GH2_PRESS_LINE
inline constexpr unsigned int GRP_GH2_PRESS_LINE_FAIRING_SLWT	=	33;	//GH2_PRESS_LINE_FAIRING
inline constexpr unsigned int GRP_GOX_PRESS_LINE_SLWT	=	34;	//GOX_PRESS_LINE
inline constexpr unsigned int GRP_GOX_PRESS_LINE_BRACKETS_SLWT	=	35;	//GOX_PRESS_LINE_BRACKETS
inline constexpr unsigned int GRP_AFT_LOWER_SRB_ATTACHMENTS_SLWT	=	36;	//AFT_LOWER_SRB_ATTACHMENTS
inline constexpr unsigned int GRP_INTERTANK_SLWT	=	37;	//INTERTANK
inline constexpr unsigned int GRP_INTERTANK_ACCESS_DOOR_SLWT	=	38;	//INTERTANK_ACCESS_DOOR
inline constexpr unsigned int GRP_INTERTANK_STRINGERS_SLWT	=	39;	//INTERTANK_STRINGERS
inline constexpr unsigned int GRP_LH2_CABLE_TRAYS_SLWT	=	40;	//LH2_CABLE_TRAYS
inline constexpr unsigned int GRP_LH2_DISCONNECT_PLATE_SLWT	=	41;	//LH2_DISCONNECT_PLATE
inline constexpr unsigned int GRP_LH2_RECIRC_LINE_SLWT	=	42;	//LH2_RECIRC_LINE
inline constexpr unsigned int GRP_LIGHTNING_SPIKE_SLWT	=	43;	//LIGHTNING_SPIKE
inline constexpr unsigned int GRP_INTERTANK_THRUSTPANELS_SLWT	=	44;	//INTERTANK_THRUSTPANELS
inline constexpr unsigned int GRP_INTERTANK_THRUSTPANELS_RINGS_SLWT	=	45;	//INTERTANK_THRUSTPANELS_RINGS
inline constexpr unsigned int GRP_LOX_NOSECAP_FAIRING_SLWT	=	46;	//LOX_NOSECAP_FAIRING
inline constexpr unsigned int GRP_LOX_CABLE_TRAY_SLWT	=	47;	//LOX_CABLE_TRAY
inline constexpr unsigned int GRP_LOX_DISCONNECT_PLATE_SLWT	=	48;	//LOX_DISCONNECT_PLATE
inline constexpr unsigned int GRP_LOX_TANK_SLWT	=	49;	//LOX_TANK
inline constexpr unsigned int GRP_INTERTANK_IFRS_SLWT	=	50;	//INTERTANK_IFRS
inline constexpr unsigned int GRP_LOX_DISCONNECT_VALVE_SLWT	=	51;	//LOX_DISCONNECT_VALVE
inline constexpr unsigned int GRP_LH2_DISCONNECT_VALVE_SLWT	=	52;	//LH2_DISCONNECT_VALVE
inline constexpr unsigned int GRP_SRB_PAL_RAMPS_SLWT	=	53;	//SRB_PAL_RAMPS
inline constexpr unsigned int GRP_MSH_OBJECT_56_SLWT	=	54;	//MSH_object_56
inline constexpr unsigned int GRP_MSH_OBJECT_57_SLWT	=	55;	//MSH_object_57
inline constexpr unsigned int GRP_MSH_OBJECT_58_SLWT	=	56;	//MSH_object_58
inline constexpr unsigned int GRP_MSH_OBJECT_59_SLWT	=	57;	//MSH_object_59
inline constexpr unsigned int GRP_MSH_OBJECT_60_SLWT	=	58;	//MSH_object_60
inline constexpr unsigned int GRP_LH2_FEEDLINE_SLWT	=	59;	//LH2_FEEDLINE
inline constexpr unsigned int GRP_LH2_FEEDLINE_AFT_DOME_ISLAND_SLWT	=	60;	//LH2_FEEDLINE_AFT_DOME_ISLAND
inline constexpr unsigned int GRP_17_LOX_FEEDLINE_SLWT	=	61;	//17_LOX_FEEDLINE
inline constexpr unsigned int GRP_LEFT_SRB_DIAGONAL_STRUT_SLWT	=	62;	//LEFT_SRB_DIAGONAL_STRUT
inline constexpr unsigned int GRP_LEFT_SRB_LOWER_STRUT_SLWT	=	63;	//LEFT_SRB_LOWER_STRUT
inline constexpr unsigned int GRP_LEFT_SRB_UPPER_STRUT_SLWT	=	64;	//LEFT_SRB_UPPER_STRUT
inline constexpr unsigned int GRP_LEFT_SRB_MILK_CAN_SLWT	=	65;	//LEFT_SRB_MILK_CAN
inline constexpr unsigned int GRP_RIGHT_SRB_DIAGONAL_STRUT_SLWT	=	66;	//RIGHT_SRB_DIAGONAL_STRUT
inline constexpr unsigned int GRP_RIGHT_SRB_LOWER_STRUT_SLWT	=	67;	//RIGHT_SRB_LOWER_STRUT
inline constexpr unsigned int GRP_RIGHT_SRB_UPPER_STRUT_SLWT	=	68;	//RIGHT_SRB_UPPER_STRUT
inline constexpr unsigned int GRP_RIGHT_SRB_MILK_CAN_SLWT	=	69;	//RIGHT_SRB_MILK_CAN

#endif// _MESH_SLWT_H_
