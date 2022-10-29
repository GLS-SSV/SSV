// ======================================================
// Created by ssvmeshc 1.2
// Input file: panelA8A3.msh
// ======================================================

#ifndef _MESH_PANELA8A3_H_
#define _MESH_PANELA8A3_H_

inline constexpr unsigned int NUMGRP_A8A3_VC = 57;

inline constexpr unsigned int GRP_OPEN_HOOKS_A8A3_VC	=	0;	//OPEN_Hooks
inline constexpr unsigned int GRP_OPEN_LATCHES_A8A3_VC	=	1;	//OPEN_Latches
inline constexpr unsigned int GRP_UNDOCKING_A8A3_VC	=	2;	//Undocking
inline constexpr unsigned int GRP_ACT_HOOKS_FIRING_A8A3_VC	=	3;	//Act_Hooks_Firing
inline constexpr unsigned int GRP_PAS_HOOKS_FIRING_A8A3_VC	=	4;	//Pas_Hooks_Firing
inline constexpr unsigned int GRP_PYRO_CIRC_PROT_ON_A8A3_VC	=	5;	//Pyro_Circ_Prot_ON
inline constexpr unsigned int GRP_PYRO_CIRC_PROT_OFF_A8A3_VC	=	6;	//Pyro_Circ_Prot_OFF
inline constexpr unsigned int GRP_S1_A8A3_VC	=	7;	//S1
inline constexpr unsigned int GRP_S2_A8A3_VC	=	8;	//S2
inline constexpr unsigned int GRP_S3_A8A3_VC	=	9;	//S3
inline constexpr unsigned int GRP_S6_A8A3_VC	=	10;	//S6
inline constexpr unsigned int GRP_S5_A8A3_VC	=	11;	//S5
inline constexpr unsigned int GRP_S4_A8A3_VC	=	12;	//S4
inline constexpr unsigned int GRP_S7_A8A3_VC	=	13;	//S7
inline constexpr unsigned int GRP_S8_A8A3_VC	=	14;	//S8
inline constexpr unsigned int GRP_S9_A8A3_VC	=	15;	//S9
inline constexpr unsigned int GRP_S12_A8A3_VC	=	16;	//S12
inline constexpr unsigned int GRP_S11_A8A3_VC	=	17;	//S11
inline constexpr unsigned int GRP_S10_A8A3_VC	=	18;	//S10
inline constexpr unsigned int GRP_POWER_ON_A8A3_VC	=	19;	//Power_ON
inline constexpr unsigned int GRP_APDS_CIRC_PROT_OFF_A8A3_VC	=	20;	//APDS_Circ_Prot_OFF
inline constexpr unsigned int GRP_RING_INITIAL_POS_A8A3_VC	=	21;	//Ring_Initial_Pos
inline constexpr unsigned int GRP_RING_ALIGNED_A8A3_VC	=	22;	//Ring_Aligned
inline constexpr unsigned int GRP_FIXERS_OFF_A8A3_VC	=	23;	//Fixers_OFF
inline constexpr unsigned int GRP_HOOKS1_OPEN_A8A3_VC	=	24;	//Hooks1_OPEN
inline constexpr unsigned int GRP_LATCHES_CLOSED_A8A3_VC	=	25;	//Latches_CLOSED
inline constexpr unsigned int GRP_HOOKS2_OPEN_A8A3_VC	=	26;	//Hooks2_OPEN
inline constexpr unsigned int GRP_UNDOCK_COMPLET_A8A3_VC	=	27;	//Undock_Complet
inline constexpr unsigned int GRP_RING_FINAL_POS_A8A3_VC	=	28;	//Ring_Final_Pos
inline constexpr unsigned int GRP_HOOKS2_CLOSED_A8A3_VC	=	29;	//Hooks2_CLOSED
inline constexpr unsigned int GRP_LATCHES_OPEN_A8A3_VC	=	30;	//Latches_OPEN
inline constexpr unsigned int GRP_HOOKS1_CLOSED_A8A3_VC	=	31;	//Hooks1_CLOSED
inline constexpr unsigned int GRP_INTERF_SEALED_A8A3_VC	=	32;	//Interf_Sealed
inline constexpr unsigned int GRP_RING_FORWARD_POS_A8A3_VC	=	33;	//Ring_Forward_Pos
inline constexpr unsigned int GRP_READY_TO_HOOK_A8A3_VC	=	34;	//READY_To_Hook
inline constexpr unsigned int GRP_CAPTURE_A8A3_VC	=	35;	//CAPTURE
inline constexpr unsigned int GRP_INITIAL_CONTACT_A8A3_VC	=	36;	//Initial_Contact
inline constexpr unsigned int GRP_APDSCC_POWERON_A8A3_VC	=	37;	//APDSCC_PowerOn
inline constexpr unsigned int GRP_APDSCC_POWEROFF_A8A3_VC	=	38;	//APDSCC_PowerOff
inline constexpr unsigned int GRP_APDSCC_RINGOUT_A8A3_VC	=	39;	//APDSCC_RingOut
inline constexpr unsigned int GRP_APDSCC_RINGIN_A8A3_VC	=	40;	//APDSCC_RingIn
inline constexpr unsigned int GRP_APDSCC_FIXEROFF_A8A3_VC	=	41;	//APDSCC_FixerOff
inline constexpr unsigned int GRP_APDSCC_CLOSELATCHES_A8A3_VC	=	42;	//APDSCC_CloseLatches
inline constexpr unsigned int GRP_APDSCC_CLOSEHOOKS_A8A3_VC	=	43;	//APDSCC_CloseHooks
inline constexpr unsigned int GRP_APDSCC_APDS_CIRC_PROT_OFF_A8A3_VC	=	44;	//APDSCC_APDS_Circ_Prot_OFF
inline constexpr unsigned int GRP_ADS_A8A3_VC	=	45;	//A/DS
inline constexpr unsigned int GRP_BDS_A8A3_VC	=	46;	//B/DS
inline constexpr unsigned int GRP_CDS_A8A3_VC	=	47;	//C/DS
inline constexpr unsigned int GRP_AP_A8A3_VC	=	48;	//A/P
inline constexpr unsigned int GRP_BP_A8A3_VC	=	49;	//B/P
inline constexpr unsigned int GRP_CP_A8A3_VC	=	50;	//C/P
inline constexpr unsigned int GRP_PYROPROTECTCIRCUITOFF_A8A3_VC	=	51;	//PyroProtectCircuitOff
inline constexpr unsigned int GRP_LAMPTEST_A8A3_VC	=	52;	//LampTest
inline constexpr unsigned int GRP_RUSSIANGUARDS_A8A3_VC	=	53;	//russianguards
inline constexpr unsigned int GRP_PLATEGUARD2_A8A3_VC	=	54;	//plateguard2
inline constexpr unsigned int GRP_PLATEGUARD1_A8A3_VC	=	55;	//plateguard1
inline constexpr unsigned int GRP_PANEL_A8A3_VC	=	56;	//panel

#endif// _MESH_PANELA8A3_H_
