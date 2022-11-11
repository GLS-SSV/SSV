// ======================================================
// Created by ssvmeshc 1.2
// Input file: panelO6.msh
// ======================================================

#ifndef _MESH_PANELO6_H_
#define _MESH_PANELO6_H_

inline constexpr unsigned int NUMGRP_O6_VC = 84;

inline constexpr unsigned int GRP_PANEL_O6_VC	=	0;	//panel
inline constexpr unsigned int GRP_GUARDS_O6_VC	=	1;	//guards
inline constexpr unsigned int GRP_COVER2_O6_VC	=	2;	//cover2
inline constexpr unsigned int GRP_COVER3_O6_VC	=	3;	//cover3
inline constexpr unsigned int GRP_COVER30_O6_VC	=	4;	//cover30
inline constexpr unsigned int GRP_COVER31_O6_VC	=	5;	//cover31
inline constexpr unsigned int GRP_COVER32_O6_VC	=	6;	//cover32
inline constexpr unsigned int GRP_COVER33_O6_VC	=	7;	//cover33
inline constexpr unsigned int GRP_COVER34_O6_VC	=	8;	//cover34
inline constexpr unsigned int GRP_COVER35_O6_VC	=	9;	//cover35
inline constexpr unsigned int GRP_COVER36_O6_VC	=	10;	//cover36
inline constexpr unsigned int GRP_COVER37_O6_VC	=	11;	//cover37
inline constexpr unsigned int GRP_COVER38_O6_VC	=	12;	//cover38
inline constexpr unsigned int GRP_COVER39_O6_VC	=	13;	//cover39
inline constexpr unsigned int GRP_S1_O6_VC	=	14;	//S1
inline constexpr unsigned int GRP_S2_O6_VC	=	15;	//S2
inline constexpr unsigned int GRP_S3_O6_VC	=	16;	//S3
inline constexpr unsigned int GRP_S4_O6_VC	=	17;	//S4
inline constexpr unsigned int GRP_S5_O6_VC	=	18;	//S5
inline constexpr unsigned int GRP_S6_O6_VC	=	19;	//S6
inline constexpr unsigned int GRP_S7_O6_VC	=	20;	//S7
inline constexpr unsigned int GRP_S9_O6_VC	=	21;	//S9
inline constexpr unsigned int GRP_S10_O6_VC	=	22;	//S10
inline constexpr unsigned int GRP_S12_O6_VC	=	23;	//S12
inline constexpr unsigned int GRP_S13_O6_VC	=	24;	//S13
inline constexpr unsigned int GRP_S14_O6_VC	=	25;	//S14
inline constexpr unsigned int GRP_S15_O6_VC	=	26;	//S15
inline constexpr unsigned int GRP_S16_O6_VC	=	27;	//S16
inline constexpr unsigned int GRP_S17_O6_VC	=	28;	//S17
inline constexpr unsigned int GRP_S18_O6_VC	=	29;	//S18
inline constexpr unsigned int GRP_S19_O6_VC	=	30;	//S19
inline constexpr unsigned int GRP_S20_O6_VC	=	31;	//S20
inline constexpr unsigned int GRP_S21_O6_VC	=	32;	//S21
inline constexpr unsigned int GRP_S22_O6_VC	=	33;	//S22
inline constexpr unsigned int GRP_S23_O6_VC	=	34;	//S23
inline constexpr unsigned int GRP_S24_O6_VC	=	35;	//S24
inline constexpr unsigned int GRP_S25_O6_VC	=	36;	//S25
inline constexpr unsigned int GRP_S26_O6_VC	=	37;	//S26
inline constexpr unsigned int GRP_S27_O6_VC	=	38;	//S27
inline constexpr unsigned int GRP_S28_O6_VC	=	39;	//S28
inline constexpr unsigned int GRP_S29_O6_VC	=	40;	//S29
inline constexpr unsigned int GRP_S30_O6_VC	=	41;	//S30
inline constexpr unsigned int GRP_S31_O6_VC	=	42;	//S31
inline constexpr unsigned int GRP_S32_O6_VC	=	43;	//S32
inline constexpr unsigned int GRP_S33_O6_VC	=	44;	//S33
inline constexpr unsigned int GRP_S34_O6_VC	=	45;	//S34
inline constexpr unsigned int GRP_S35_O6_VC	=	46;	//S35
inline constexpr unsigned int GRP_S36_O6_VC	=	47;	//S36
inline constexpr unsigned int GRP_S37_O6_VC	=	48;	//S37
inline constexpr unsigned int GRP_S38_O6_VC	=	49;	//S38
inline constexpr unsigned int GRP_S39_O6_VC	=	50;	//S39
inline constexpr unsigned int GRP_S45_O6_VC	=	51;	//S45
inline constexpr unsigned int GRP_S51_O6_VC	=	52;	//S51
inline constexpr unsigned int GRP_S52_O6_VC	=	53;	//S52
inline constexpr unsigned int GRP_S46_O6_VC	=	54;	//S46
inline constexpr unsigned int GRP_S47_O6_VC	=	55;	//S47
inline constexpr unsigned int GRP_S48_O6_VC	=	56;	//S48
inline constexpr unsigned int GRP_S49_O6_VC	=	57;	//S49
inline constexpr unsigned int GRP_S50_O6_VC	=	58;	//S50
inline constexpr unsigned int GRP_R1_O6_VC	=	59;	//R1
inline constexpr unsigned int GRP_R2_O6_VC	=	60;	//R2
inline constexpr unsigned int GRP_R3_O6_VC	=	61;	//R3
inline constexpr unsigned int GRP_R4_O6_VC	=	62;	//R4
inline constexpr unsigned int GRP_R5_O6_VC	=	63;	//R5
inline constexpr unsigned int GRP_R6_O6_VC	=	64;	//R6
inline constexpr unsigned int GRP_R7_O6_VC	=	65;	//R7
inline constexpr unsigned int GRP_S8_O6_VC	=	66;	//S8
inline constexpr unsigned int GRP_DS1_O6_VC	=	67;	//DS1
inline constexpr unsigned int GRP_DS2_O6_VC	=	68;	//DS2
inline constexpr unsigned int GRP_DS3_U_O6_VC	=	69;	//DS3_U
inline constexpr unsigned int GRP_DS3_L_O6_VC	=	70;	//DS3_L
inline constexpr unsigned int GRP_DS4_U_O6_VC	=	71;	//DS4_U
inline constexpr unsigned int GRP_DS4_L_O6_VC	=	72;	//DS4_L
inline constexpr unsigned int GRP_DS5_U_O6_VC	=	73;	//DS5_U
inline constexpr unsigned int GRP_DS5_L_O6_VC	=	74;	//DS5_L
inline constexpr unsigned int GRP_DS6_U_O6_VC	=	75;	//DS6_U
inline constexpr unsigned int GRP_DS6_L_O6_VC	=	76;	//DS6_L
inline constexpr unsigned int GRP_DS7_U_O6_VC	=	77;	//DS7_U
inline constexpr unsigned int GRP_DS7_L_O6_VC	=	78;	//DS7_L
inline constexpr unsigned int GRP_DS8_O6_VC	=	79;	//DS8
inline constexpr unsigned int GRP_DS9_O6_VC	=	80;	//DS9
inline constexpr unsigned int GRP_DS10_O6_VC	=	81;	//DS10
inline constexpr unsigned int GRP_DS11_O6_VC	=	82;	//DS11
inline constexpr unsigned int GRP_DS12_O6_VC	=	83;	//DS12

#endif// _MESH_PANELO6_H_
