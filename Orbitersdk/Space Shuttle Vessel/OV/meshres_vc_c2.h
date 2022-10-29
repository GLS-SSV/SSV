// ======================================================
// Created by ssvmeshc 1.2
// Input file: panelC2.msh
// ======================================================

#ifndef _MESH_PANELC2_H_
#define _MESH_PANELC2_H_

inline constexpr unsigned int NUMGRP_C2_VC = 98;

inline constexpr unsigned int GRP_PANEL_C2_VC	=	0;	//panel
inline constexpr unsigned int GRP_PANEL2_C2_VC	=	1;	//panel2
inline constexpr unsigned int GRP_GUARDS_C2_VC	=	2;	//guards
inline constexpr unsigned int GRP_S1_C2_VC	=	3;	//S1
inline constexpr unsigned int GRP_S2_C2_VC	=	4;	//S2
inline constexpr unsigned int GRP_S3_C2_VC	=	5;	//S3
inline constexpr unsigned int GRP_S4_C2_VC	=	6;	//S4
inline constexpr unsigned int GRP_S5_C2_VC	=	7;	//S5
inline constexpr unsigned int GRP_S6_C2_VC	=	8;	//S6
inline constexpr unsigned int GRP_S7_C2_VC	=	9;	//S7
inline constexpr unsigned int GRP_S8_C2_VC	=	10;	//S8
inline constexpr unsigned int GRP_S9_C2_VC	=	11;	//S9
inline constexpr unsigned int GRP_S10_C2_VC	=	12;	//S10
inline constexpr unsigned int GRP_S12_C2_VC	=	13;	//S12
inline constexpr unsigned int GRP_LEFT_KEYBOARD_FRAME_C2_VC	=	14;	//LEFT_KEYBOARD_FRAME
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_FRAME_C2_VC	=	15;	//RIGHT_KEYBOARD_FRAME
inline constexpr unsigned int GRP_LEFT_KEYBOARD_FAULTSUMM_C2_VC	=	16;	//LEFT_KEYBOARD_FAULTSUMM
inline constexpr unsigned int GRP_LEFT_KEYBOARD_SYSSUMM_C2_VC	=	17;	//LEFT_KEYBOARD_SYSSUMM
inline constexpr unsigned int GRP_LEFT_KEYBOARD_MSGRESET_C2_VC	=	18;	//LEFT_KEYBOARD_MSGRESET
inline constexpr unsigned int GRP_LEFT_KEYBOARD_ACK_C2_VC	=	19;	//LEFT_KEYBOARD_ACK
inline constexpr unsigned int GRP_LEFT_KEYBOARD_GPCCRT_C2_VC	=	20;	//LEFT_KEYBOARD_GPCCRT
inline constexpr unsigned int GRP_LEFT_KEYBOARD_A_C2_VC	=	21;	//LEFT_KEYBOARD_A
inline constexpr unsigned int GRP_LEFT_KEYBOARD_B_C2_VC	=	22;	//LEFT_KEYBOARD_B
inline constexpr unsigned int GRP_LEFT_KEYBOARD_C_C2_VC	=	23;	//LEFT_KEYBOARD_C
inline constexpr unsigned int GRP_LEFT_KEYBOARD_IORESET_C2_VC	=	24;	//LEFT_KEYBOARD_IORESET
inline constexpr unsigned int GRP_LEFT_KEYBOARD_D_C2_VC	=	25;	//LEFT_KEYBOARD_D
inline constexpr unsigned int GRP_LEFT_KEYBOARD_E_C2_VC	=	26;	//LEFT_KEYBOARD_E
inline constexpr unsigned int GRP_LEFT_KEYBOARD_F_C2_VC	=	27;	//LEFT_KEYBOARD_F
inline constexpr unsigned int GRP_LEFT_KEYBOARD_ITEM_C2_VC	=	28;	//LEFT_KEYBOARD_ITEM
inline constexpr unsigned int GRP_LEFT_KEYBOARD_1_C2_VC	=	29;	//LEFT_KEYBOARD_1
inline constexpr unsigned int GRP_LEFT_KEYBOARD_2_C2_VC	=	30;	//LEFT_KEYBOARD_2
inline constexpr unsigned int GRP_LEFT_KEYBOARD_3_C2_VC	=	31;	//LEFT_KEYBOARD_3
inline constexpr unsigned int GRP_LEFT_KEYBOARD_EXEC_C2_VC	=	32;	//LEFT_KEYBOARD_EXEC
inline constexpr unsigned int GRP_LEFT_KEYBOARD_4_C2_VC	=	33;	//LEFT_KEYBOARD_4
inline constexpr unsigned int GRP_LEFT_KEYBOARD_5_C2_VC	=	34;	//LEFT_KEYBOARD_5
inline constexpr unsigned int GRP_LEFT_KEYBOARD_6_C2_VC	=	35;	//LEFT_KEYBOARD_6
inline constexpr unsigned int GRP_LEFT_KEYBOARD_OPS_C2_VC	=	36;	//LEFT_KEYBOARD_OPS
inline constexpr unsigned int GRP_LEFT_KEYBOARD_7_C2_VC	=	37;	//LEFT_KEYBOARD_7
inline constexpr unsigned int GRP_LEFT_KEYBOARD_8_C2_VC	=	38;	//LEFT_KEYBOARD_8
inline constexpr unsigned int GRP_LEFT_KEYBOARD_9_C2_VC	=	39;	//LEFT_KEYBOARD_9
inline constexpr unsigned int GRP_LEFT_KEYBOARD_SPEC_C2_VC	=	40;	//LEFT_KEYBOARD_SPEC
inline constexpr unsigned int GRP_LEFT_KEYBOARD_MINUS_C2_VC	=	41;	//LEFT_KEYBOARD_MINUS
inline constexpr unsigned int GRP_LEFT_KEYBOARD_0_C2_VC	=	42;	//LEFT_KEYBOARD_0
inline constexpr unsigned int GRP_LEFT_KEYBOARD_PLUS_C2_VC	=	43;	//LEFT_KEYBOARD_PLUS
inline constexpr unsigned int GRP_LEFT_KEYBOARD_RESUME_C2_VC	=	44;	//LEFT_KEYBOARD_RESUME
inline constexpr unsigned int GRP_LEFT_KEYBOARD_CLEAR_C2_VC	=	45;	//LEFT_KEYBOARD_CLEAR
inline constexpr unsigned int GRP_LEFT_KEYBOARD_DOT_C2_VC	=	46;	//LEFT_KEYBOARD_DOT
inline constexpr unsigned int GRP_LEFT_KEYBOARD_PRO_C2_VC	=	47;	//LEFT_KEYBOARD_PRO
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_FAULTSUMM_C2_VC	=	48;	//RIGHT_KEYBOARD_FAULTSUMM
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_SYSSUMM_C2_VC	=	49;	//RIGHT_KEYBOARD_SYSSUMM
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_MSGRESET_C2_VC	=	50;	//RIGHT_KEYBOARD_MSGRESET
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_ACK_C2_VC	=	51;	//RIGHT_KEYBOARD_ACK
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_GPCCRT_C2_VC	=	52;	//RIGHT_KEYBOARD_GPCCRT
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_A_C2_VC	=	53;	//RIGHT_KEYBOARD_A
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_B_C2_VC	=	54;	//RIGHT_KEYBOARD_B
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_C_C2_VC	=	55;	//RIGHT_KEYBOARD_C
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_IORESET_C2_VC	=	56;	//RIGHT_KEYBOARD_IORESET
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_D_C2_VC	=	57;	//RIGHT_KEYBOARD_D
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_E_C2_VC	=	58;	//RIGHT_KEYBOARD_E
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_F_C2_VC	=	59;	//RIGHT_KEYBOARD_F
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_ITEM_C2_VC	=	60;	//RIGHT_KEYBOARD_ITEM
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_1_C2_VC	=	61;	//RIGHT_KEYBOARD_1
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_2_C2_VC	=	62;	//RIGHT_KEYBOARD_2
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_3_C2_VC	=	63;	//RIGHT_KEYBOARD_3
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_EXEC_C2_VC	=	64;	//RIGHT_KEYBOARD_EXEC
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_4_C2_VC	=	65;	//RIGHT_KEYBOARD_4
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_5_C2_VC	=	66;	//RIGHT_KEYBOARD_5
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_6_C2_VC	=	67;	//RIGHT_KEYBOARD_6
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_OPS_C2_VC	=	68;	//RIGHT_KEYBOARD_OPS
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_7_C2_VC	=	69;	//RIGHT_KEYBOARD_7
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_8_C2_VC	=	70;	//RIGHT_KEYBOARD_8
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_9_C2_VC	=	71;	//RIGHT_KEYBOARD_9
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_SPEC_C2_VC	=	72;	//RIGHT_KEYBOARD_SPEC
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_MINUS_C2_VC	=	73;	//RIGHT_KEYBOARD_MINUS
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_0_C2_VC	=	74;	//RIGHT_KEYBOARD_0
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_PLUS_C2_VC	=	75;	//RIGHT_KEYBOARD_PLUS
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_RESUME_C2_VC	=	76;	//RIGHT_KEYBOARD_RESUME
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_CLEAR_C2_VC	=	77;	//RIGHT_KEYBOARD_CLEAR
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_DOT_C2_VC	=	78;	//RIGHT_KEYBOARD_DOT
inline constexpr unsigned int GRP_RIGHT_KEYBOARD_PRO_C2_VC	=	79;	//RIGHT_KEYBOARD_PRO
inline constexpr unsigned int GRP_S11_PUSHWHEEL_10M_C2_VC	=	80;	//S11_pushwheel_10m
inline constexpr unsigned int GRP_S11_PUSHWHEEL_10S_C2_VC	=	81;	//S11_pushwheel_10s
inline constexpr unsigned int GRP_S11_PUSHWHEEL_1M_C2_VC	=	82;	//S11_pushwheel_1m
inline constexpr unsigned int GRP_S11_PUSHWHEEL_1S_C2_VC	=	83;	//S11_pushwheel_1s
inline constexpr unsigned int GRP_S11_PUSHWHEEL_CASE_C2_VC	=	84;	//S11_pushwheel_case
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_10M_C2_VC	=	85;	//S11_pushwheel_pushbutton_down_10m
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_10S_C2_VC	=	86;	//S11_pushwheel_pushbutton_down_10s
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_1M_C2_VC	=	87;	//S11_pushwheel_pushbutton_down_1m
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_DOWN_1S_C2_VC	=	88;	//S11_pushwheel_pushbutton_down_1s
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_10M_C2_VC	=	89;	//S11_pushwheel_pushbutton_up_10m
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_10S_C2_VC	=	90;	//S11_pushwheel_pushbutton_up_10s
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_1M_C2_VC	=	91;	//S11_pushwheel_pushbutton_up_1m
inline constexpr unsigned int GRP_S11_PUSHWHEEL_PUSHBUTTON_UP_1S_C2_VC	=	92;	//S11_pushwheel_pushbutton_up_1s
inline constexpr unsigned int GRP_S11_THUMBWHEEL_10M_C2_VC	=	93;	//S11_thumbwheel_10m
inline constexpr unsigned int GRP_S11_THUMBWHEEL_10S_C2_VC	=	94;	//S11_thumbwheel_10s
inline constexpr unsigned int GRP_S11_THUMBWHEEL_1M_C2_VC	=	95;	//S11_thumbwheel_1m
inline constexpr unsigned int GRP_S11_THUMBWHEEL_1S_C2_VC	=	96;	//S11_thumbwheel_1s
inline constexpr unsigned int GRP_S11_THUMBWHEEL_CASE_C2_VC	=	97;	//S11_thumbwheel_case

#endif// _MESH_PANELC2_H_
