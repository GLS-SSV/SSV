// ======================================================
// Created by ssvmeshc 1.2
// Input file: panelF7.msh
// ======================================================

#ifndef _MESH_PANELF7_H_
#define _MESH_PANELF7_H_

inline constexpr unsigned int NUMGRP_F7_VC = 57;
inline constexpr unsigned int NUMMAT_F7_VC = 8;

inline constexpr unsigned int GRP_PANEL_CW_F7_VC	=	0;	//panel_cw
inline constexpr unsigned int GRP_PANEL_MDU1_F7_VC	=	1;	//panel_mdu1
inline constexpr unsigned int GRP_PANEL_MDU2_F7_VC	=	2;	//panel_mdu2
inline constexpr unsigned int GRP_PANEL_EVENTTIMER_F7_VC	=	3;	//panel_eventtimer
inline constexpr unsigned int GRP_EVENT_M10_F7_VC	=	4;	//Event_M10
inline constexpr unsigned int GRP_EVENT_M1_F7_VC	=	5;	//Event_M1
inline constexpr unsigned int GRP_EVENT_S10_F7_VC	=	6;	//Event_S10
inline constexpr unsigned int GRP_EVENT_S1_F7_VC	=	7;	//Event_S1
inline constexpr unsigned int GRP_XDS1_F7_VC	=	8;	//XDS1
inline constexpr unsigned int GRP_XDS2_F7_VC	=	9;	//XDS2
inline constexpr unsigned int GRP_XDS3_F7_VC	=	10;	//XDS3
inline constexpr unsigned int GRP_XDS4_F7_VC	=	11;	//XDS4
inline constexpr unsigned int GRP_CW_AC_OVERLOAD_F7_VC	=	12;	//CW_AC_OVERLOAD
inline constexpr unsigned int GRP_CW_AC_VOLTAGE_F7_VC	=	13;	//CW_AC_VOLTAGE
inline constexpr unsigned int GRP_CW_AIR_DATA_F7_VC	=	14;	//CW_AIR_DATA
inline constexpr unsigned int GRP_CW_APU_OVERSPEED_F7_VC	=	15;	//CW_APU_OVERSPEED
inline constexpr unsigned int GRP_CW_APU_TEMP_F7_VC	=	16;	//CW_APU_TEMP
inline constexpr unsigned int GRP_CW_APU_UNDERSPEED_F7_VC	=	17;	//CW_APU_UNDERSPEED
inline constexpr unsigned int GRP_CW_AV_BAY_CABIN_AIR_F7_VC	=	18;	//CW_AV_BAY_CABIN_AIR
inline constexpr unsigned int GRP_CW_BACKUP_CW_ALARM_F7_VC	=	19;	//CW_BACKUP_CW_ALARM
inline constexpr unsigned int GRP_CW_BLANK_F7_VC	=	20;	//CW_BLANK
inline constexpr unsigned int GRP_CW_BLANK2_F7_VC	=	21;	//CW_BLANK2
inline constexpr unsigned int GRP_CW_CABIN_ATM_F7_VC	=	22;	//CW_CABIN_ATM
inline constexpr unsigned int GRP_CW_FCS_CHANNEL_F7_VC	=	23;	//CW_FCS_CHANNEL
inline constexpr unsigned int GRP_CW_FCS_SATURATION_F7_VC	=	24;	//CW_FCS_SATURATION
inline constexpr unsigned int GRP_CW_FREON_LOOP_F7_VC	=	25;	//CW_FREON_LOOP
inline constexpr unsigned int GRP_CW_FUEL_CELL_PUMP_F7_VC	=	26;	//CW_FUEL_CELL_PUMP
inline constexpr unsigned int GRP_CW_FUEL_CELL_REAC_F7_VC	=	27;	//CW_FUEL_CELL_REAC
inline constexpr unsigned int GRP_CW_FUEL_CELL_STACK_TEMP_F7_VC	=	28;	//CW_FUEL_CELL_STACK_TEMP
inline constexpr unsigned int GRP_CW_FWD_RCS_F7_VC	=	29;	//CW_FWD_RCS
inline constexpr unsigned int GRP_CW_GPC_F7_VC	=	30;	//CW_GPC
inline constexpr unsigned int GRP_CW_H2O_LOOP_F7_VC	=	31;	//CW_H2O_LOOP
inline constexpr unsigned int GRP_CW_H2_PRESS_F7_VC	=	32;	//CW_H2_PRESS
inline constexpr unsigned int GRP_CW_HYD_PRESS_F7_VC	=	33;	//CW_HYD_PRESS
inline constexpr unsigned int GRP_CW_IMU_F7_VC	=	34;	//CW_IMU
inline constexpr unsigned int GRP_CW_LEFT_OMS_F7_VC	=	35;	//CW_LEFT_OMS
inline constexpr unsigned int GRP_CW_LEFT_RCS_F7_VC	=	36;	//CW_LEFT_RCS
inline constexpr unsigned int GRP_CW_LEFT_RHC_F7_VC	=	37;	//CW_LEFT_RHC
inline constexpr unsigned int GRP_CW_MAIN_BUS_UNDERVOLT_F7_VC	=	38;	//CW_MAIN_BUS_UNDERVOLT
inline constexpr unsigned int GRP_CW_MPS_F7_VC	=	39;	//CW_MPS
inline constexpr unsigned int GRP_CW_O2_HEATER_TEMP_F7_VC	=	40;	//CW_O2_HEATER_TEMP
inline constexpr unsigned int GRP_CW_O2_PRESS_F7_VC	=	41;	//CW_O2_PRESS
inline constexpr unsigned int GRP_CW_OMS_KIT_F7_VC	=	42;	//CW_OMS_KIT
inline constexpr unsigned int GRP_CW_OMS_TVC_F7_VC	=	43;	//CW_OMS_TVC
inline constexpr unsigned int GRP_CW_PAYLOAD_CAUTION_F7_VC	=	44;	//CW_PAYLOAD_CAUTION
inline constexpr unsigned int GRP_CW_PAYLOAD_WARNING_F7_VC	=	45;	//CW_PAYLOAD_WARNING
inline constexpr unsigned int GRP_CW_PRIMARY_CW_F7_VC	=	46;	//CW_PRIMARY_CW
inline constexpr unsigned int GRP_CW_RCS_JET_F7_VC	=	47;	//CW_RCS_JET
inline constexpr unsigned int GRP_CW_RGA_ACCEL_F7_VC	=	48;	//CW_RGA_ACCEL
inline constexpr unsigned int GRP_CW_RIGHT_AFT_RHC_F7_VC	=	49;	//CW_RIGHT_AFT_RHC
inline constexpr unsigned int GRP_CW_RIGHT_OMS_F7_VC	=	50;	//CW_RIGHT_OMS
inline constexpr unsigned int GRP_CW_RIGHT_RCS_F7_VC	=	51;	//CW_RIGHT_RCS
inline constexpr unsigned int GRP_CRT1_F7_VC	=	52;	//CRT1
inline constexpr unsigned int GRP_CRT2_F7_VC	=	53;	//CRT2
inline constexpr unsigned int GRP_CRT3_F7_VC	=	54;	//CRT3
inline constexpr unsigned int GRP_MFD1_F7_VC	=	55;	//MFD1
inline constexpr unsigned int GRP_MFD2_F7_VC	=	56;	//MFD2

inline constexpr unsigned int MAT_PANELS_F7_VC	=	0;	//panels
inline constexpr unsigned int MAT_SEVENSEGDISP_F7_VC	=	1;	//sevensegdisp
inline constexpr unsigned int MAT_LIGHTS_F7_VC	=	2;	//lights
inline constexpr unsigned int MAT_MDU_CRT1_F7_VC	=	3;	//MDU_CRT1
inline constexpr unsigned int MAT_MDU_CRT2_F7_VC	=	4;	//MDU_CRT2
inline constexpr unsigned int MAT_MDU_CRT3_F7_VC	=	5;	//MDU_CRT3
inline constexpr unsigned int MAT_MDU_MFD1_F7_VC	=	6;	//MDU_MFD1
inline constexpr unsigned int MAT_MDU_MFD2_F7_VC	=	7;	//MDU_MFD2

#endif// _MESH_PANELF7_H_
