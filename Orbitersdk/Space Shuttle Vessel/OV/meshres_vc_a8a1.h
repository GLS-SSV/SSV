// ======================================================
// Created by ssvmeshc 1.2
// Input file: panelA8A1.msh
// ======================================================

#ifndef _MESH_PANELA8A1_H_
#define _MESH_PANELA8A1_H_

inline constexpr unsigned int NUMGRP_A8A1_VC = 83;

inline constexpr unsigned int GRP_PANEL_A8A1_VC	=	0;	//panel
inline constexpr unsigned int GRP_GUARDS_A8A1_VC	=	1;	//guards
inline constexpr unsigned int GRP_S2_A8A1_VC	=	2;	//S2
inline constexpr unsigned int GRP_S5_A8A1_VC	=	3;	//S5
inline constexpr unsigned int GRP_S7_A8A1_VC	=	4;	//S7
inline constexpr unsigned int GRP_S8_A8A1_VC	=	5;	//S8
inline constexpr unsigned int GRP_S13_A8A1_VC	=	6;	//S13
inline constexpr unsigned int GRP_S14_A8A1_VC	=	7;	//S14
inline constexpr unsigned int GRP_S15_A8A1_VC	=	8;	//S15
inline constexpr unsigned int GRP_S3_A8A1_VC	=	9;	//S3
inline constexpr unsigned int GRP_S9_A8A1_VC	=	10;	//S9
inline constexpr unsigned int GRP_S10_A8A1_VC	=	11;	//S10
inline constexpr unsigned int GRP_S11_A8A1_VC	=	12;	//S11
inline constexpr unsigned int GRP_R1_A8A1_VC	=	13;	//R1
inline constexpr unsigned int GRP_R2_A8A1_VC	=	14;	//R2
inline constexpr unsigned int GRP_S1_A8A1_VC	=	15;	//S1
inline constexpr unsigned int GRP_S12_A8A1_VC	=	16;	//S12
inline constexpr unsigned int GRP_S16_A8A1_VC	=	17;	//S16
inline constexpr unsigned int GRP_S6_A8A1_VC	=	18;	//S6
inline constexpr unsigned int GRP_DS3_U_A8A1_VC	=	19;	//DS3_U
inline constexpr unsigned int GRP_DS3_L_A8A1_VC	=	20;	//DS3_L
inline constexpr unsigned int GRP_DS4_U_A8A1_VC	=	21;	//DS4_U
inline constexpr unsigned int GRP_DS4_L_A8A1_VC	=	22;	//DS4_L
inline constexpr unsigned int GRP_DS7_U_A8A1_VC	=	23;	//DS7_U
inline constexpr unsigned int GRP_DS7_L_A8A1_VC	=	24;	//DS7_L
inline constexpr unsigned int GRP_DS8_U_A8A1_VC	=	25;	//DS8_U
inline constexpr unsigned int GRP_DS8_L_A8A1_VC	=	26;	//DS8_L
inline constexpr unsigned int GRP_DS9_U_A8A1_VC	=	27;	//DS9_U
inline constexpr unsigned int GRP_DS9_L_A8A1_VC	=	28;	//DS9_L
inline constexpr unsigned int GRP_DS10_U_A8A1_VC	=	29;	//DS10_U
inline constexpr unsigned int GRP_DS10_L_A8A1_VC	=	30;	//DS10_L
inline constexpr unsigned int GRP_DS11_U_A8A1_VC	=	31;	//DS11_U
inline constexpr unsigned int GRP_DS11_L_A8A1_VC	=	32;	//DS11_L
inline constexpr unsigned int GRP_DS12_U_A8A1_VC	=	33;	//DS12_U
inline constexpr unsigned int GRP_DS12_L_A8A1_VC	=	34;	//DS12_L
inline constexpr unsigned int GRP_DS13_U_A8A1_VC	=	35;	//DS13_U
inline constexpr unsigned int GRP_DS13_L_A8A1_VC	=	36;	//DS13_L
inline constexpr unsigned int GRP_XDS1_DIRECT_A8A1_VC	=	37;	//XDS1_DIRECT
inline constexpr unsigned int GRP_XDS1_TEST_A8A1_VC	=	38;	//XDS1_TEST
inline constexpr unsigned int GRP_XDS1_SINGLE_A8A1_VC	=	39;	//XDS1_SINGLE
inline constexpr unsigned int GRP_XDS1_OPRCMD_A8A1_VC	=	40;	//XDS1_OPRCMD
inline constexpr unsigned int GRP_XDS1_PAYLOAD_A8A1_VC	=	41;	//XDS1_PAYLOAD
inline constexpr unsigned int GRP_XDS1_AUTO4_A8A1_VC	=	42;	//XDS1_AUTO4
inline constexpr unsigned int GRP_XDS1_ORBLD_A8A1_VC	=	43;	//XDS1_ORBLD
inline constexpr unsigned int GRP_XDS1_AUTO3_A8A1_VC	=	44;	//XDS1_AUTO3
inline constexpr unsigned int GRP_XDS1_ENDEFF_A8A1_VC	=	45;	//XDS1_ENDEFF
inline constexpr unsigned int GRP_XDS1_AUTO2_A8A1_VC	=	46;	//XDS1_AUTO2
inline constexpr unsigned int GRP_XDS1_ORBUNL_A8A1_VC	=	47;	//XDS1_ORBUNL
inline constexpr unsigned int GRP_XDS1_AUTO1_A8A1_VC	=	48;	//XDS1_AUTO1
inline constexpr unsigned int GRP_XDS2_PORTTEMP_A8A1_VC	=	49;	//XDS2_PORTTEMP
inline constexpr unsigned int GRP_XDS2_STBDTEMP_A8A1_VC	=	50;	//XDS2_STBDTEMP
inline constexpr unsigned int GRP_XDS2_REACHLIM_A8A1_VC	=	51;	//XDS2_REACHLIM
inline constexpr unsigned int GRP_XDS2_CONTRERR_A8A1_VC	=	52;	//XDS2_CONTRERR
inline constexpr unsigned int GRP_XDS2_CHECKCRT_A8A1_VC	=	53;	//XDS2_CHECKCRT
inline constexpr unsigned int GRP_XDS2_SINGULAR_A8A1_VC	=	54;	//XDS2_SINGULAR
inline constexpr unsigned int GRP_XDS2_EMPTY_A8A1_VC	=	55;	//XDS2_EMPTY
inline constexpr unsigned int GRP_XDS2_GPCDATA_A8A1_VC	=	56;	//XDS2_GPCDATA
inline constexpr unsigned int GRP_XDS2_RELEASE_A8A1_VC	=	57;	//XDS2_RELEASE
inline constexpr unsigned int GRP_XDS2_ABE_A8A1_VC	=	58;	//XDS2_ABE
inline constexpr unsigned int GRP_XDS2_DERIGIDIZE_A8A1_VC	=	59;	//XDS2_DERIGIDIZE
inline constexpr unsigned int GRP_XDS2_MCIU_A8A1_VC	=	60;	//XDS2_MCIU
inline constexpr unsigned int GRP_XDS3_READY_A8A1_VC	=	61;	//XDS3_READY
inline constexpr unsigned int GRP_XDS3_INPROG_A8A1_VC	=	62;	//XDS3_INPROG
inline constexpr unsigned int GRP_M2_SIGN_A8A1_VC	=	63;	//M2_SIGN
inline constexpr unsigned int GRP_M2_4_A8A1_VC	=	64;	//M2_4
inline constexpr unsigned int GRP_M2_3_A8A1_VC	=	65;	//M2_3
inline constexpr unsigned int GRP_M2_2_A8A1_VC	=	66;	//M2_2
inline constexpr unsigned int GRP_M2_1_A8A1_VC	=	67;	//M2_1
inline constexpr unsigned int GRP_M3_SIGN_A8A1_VC	=	68;	//M3_SIGN
inline constexpr unsigned int GRP_M3_4_A8A1_VC	=	69;	//M3_4
inline constexpr unsigned int GRP_M3_3_A8A1_VC	=	70;	//M3_3
inline constexpr unsigned int GRP_M3_2_A8A1_VC	=	71;	//M3_2
inline constexpr unsigned int GRP_M3_1_A8A1_VC	=	72;	//M3_1
inline constexpr unsigned int GRP_M4_SIGN_A8A1_VC	=	73;	//M4_SIGN
inline constexpr unsigned int GRP_M4_4_A8A1_VC	=	74;	//M4_4
inline constexpr unsigned int GRP_M4_3_A8A1_VC	=	75;	//M4_3
inline constexpr unsigned int GRP_M4_2_A8A1_VC	=	76;	//M4_2
inline constexpr unsigned int GRP_M4_1_A8A1_VC	=	77;	//M4_1
inline constexpr unsigned int GRP_THC_BOOT_A8A1_VC	=	78;	//THC_boot
inline constexpr unsigned int GRP_THC_A8A1_VC	=	79;	//THC
inline constexpr unsigned int GRP_THC_GUARD_A8A1_VC	=	80;	//THC_guard
inline constexpr unsigned int GRP_THC_BASE_A8A1_VC	=	81;	//THC_base
inline constexpr unsigned int GRP_RHC_A8A1_VC	=	82;	//RHC

#endif// _MESH_PANELA8A1_H_
