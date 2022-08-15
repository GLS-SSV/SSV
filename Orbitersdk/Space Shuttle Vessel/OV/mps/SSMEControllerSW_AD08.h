/****************************************************************************
  This file is part of Space Shuttle Vessel

  Space Shuttle Main Engine Controller Software version AD08 definition


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
/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/05/26   GLS
2021/07/03   GLS
2021/08/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Space Shuttle Main Engine Controller Software version AD08 definition



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
#ifndef _mps_AD08_H_
#define _mps_AD08_H_


#include "SSMEControllerSW.h"


namespace mps
{
	// sw version AD08
	// for SSME Controller Block II
	// used in mission STS-125

	// commands
	inline constexpr unsigned short NOP = 0x0000;
	inline constexpr unsigned short SDCA = 0x0400;
	inline constexpr unsigned short SDCB = 0x0800;
	inline constexpr unsigned short EGND = 0x0C00;
	inline constexpr unsigned short EFLT = 0x1000;
	inline constexpr unsigned short EFRT = 0x1400;
	inline constexpr unsigned short ETWO = 0x1800;
	inline constexpr unsigned short RVRC = 0x1C00;
	inline constexpr unsigned short SVRC = 0x2000;
	inline constexpr unsigned short AFRT = 0x2400;
	inline constexpr unsigned short XFRT = 0x2800;
	inline constexpr unsigned short HYDC = 0x2C00;
	inline constexpr unsigned short ERCK = 0x3000;
	inline constexpr unsigned short RSYS = 0x3400;
	inline constexpr unsigned short RESM = 0x3800;
	inline constexpr unsigned short RSCT = 0x3C00;
	inline constexpr unsigned short MLDA = 0x4000;
	inline constexpr unsigned short MLDB = 0x4400;
	inline constexpr unsigned short RSCA = 0x4800;
	inline constexpr unsigned short RSCB = 0x4C00;
	inline constexpr unsigned short HELA = 0x5000;
	inline constexpr unsigned short HELB = 0x5400;
	inline constexpr unsigned short PSCA = 0x5800;
	inline constexpr unsigned short PSCB = 0x5C00;
	inline constexpr unsigned short IOHA = 0x6000;
	inline constexpr unsigned short IOHB = 0x6400;
	inline constexpr unsigned short IOLA = 0x6800;
	inline constexpr unsigned short IOLB = 0x6C00;
	inline constexpr unsigned short IOSA = 0x7000;
	inline constexpr unsigned short IOSB = 0x7400;
	inline constexpr unsigned short ENFA = 0x7800;
	inline constexpr unsigned short ENFB = 0x7C00;
	inline constexpr unsigned short ROFA = 0x8000;
	inline constexpr unsigned short ROFB = 0x8400;
	inline constexpr unsigned short RWRA = 0x8800;
	inline constexpr unsigned short RWRB = 0x8C00;
	inline constexpr unsigned short RSKA = 0x9000;
	inline constexpr unsigned short RSKB = 0x9400;
	inline constexpr unsigned short EXPM = 0x9800;
	inline constexpr unsigned short MRC1 = 0x9C00;
	inline constexpr unsigned short MRC2 = 0xA000;
	inline constexpr unsigned short LOXD = 0xA400;
	inline constexpr unsigned short APOW = 0xA800;
	inline constexpr unsigned short XPOW = 0xAC00;
	inline constexpr unsigned short PSN1 = 0xB000;
	inline constexpr unsigned short PSN2 = 0xB400;
	inline constexpr unsigned short PSN3 = 0xB800;
	inline constexpr unsigned short PSN4 = 0xBC00;
	inline constexpr unsigned short STEN = 0xC000;
	inline constexpr unsigned short IGNT = 0xC400;
	inline constexpr unsigned short SDEN = 0xC800;
	inline constexpr unsigned short STDN = 0xCC00;
	inline constexpr unsigned short TMSQ = 0xD000;
	inline constexpr unsigned short THRT = 0xD400;
	inline constexpr unsigned short COSY = 0xD800;
	inline constexpr unsigned short DAVL = 0xDC00;
	inline constexpr unsigned short ENLS = 0xE000;
	inline constexpr unsigned short INLS = 0xE400;
	inline constexpr unsigned short INFA = 0xE800;
	inline constexpr unsigned short INFB = 0xEC00;


	inline constexpr double PC_100 = 2746.788990825688073394495412844;
	inline constexpr double PC_100_B = 274.6788990825688073394495412844; // /10
	inline constexpr double PC_100_C = 27.46788990825688073394495412844; // /100
	inline constexpr unsigned short PC_100_D = 2747; // round

	inline constexpr int MPL = 65;
	inline constexpr int FPL = 109;

	inline constexpr double SINGLE_CH_STDN_TIMER = 512.86;// seconds

	// ESW
	// Self-Test Status
	inline constexpr unsigned short ESW_EngineOK = 1;
	inline constexpr unsigned short ESW_MCF = 2;
	inline constexpr unsigned short ESW_LimitExceeded = 3;

	// Mode (Checkout)
	inline constexpr unsigned short ESW_Checkout_HydraulicConditioning = 0;
	inline constexpr unsigned short ESW_Checkout_Standby = 1;
	inline constexpr unsigned short ESW_Checkout_ActuatorCheckout = 2;
	inline constexpr unsigned short ESW_Checkout_EngineLeakDetection = 3;
	inline constexpr unsigned short ESW_Checkout_IgniterCheckout = 4;
	inline constexpr unsigned short ESW_Checkout_PneumaticCheckout = 5;
	inline constexpr unsigned short ESW_Checkout_SensorCheckout = 6;
	inline constexpr unsigned short ESW_Checkout_ControllerCheckout = 7;

	// Mode (Start Prep)
	inline constexpr unsigned short ESW_StartPrep_PSN1 = 1;
	inline constexpr unsigned short ESW_StartPrep_PSN2 = 2;
	inline constexpr unsigned short ESW_StartPrep_PSN3 = 3;
	inline constexpr unsigned short ESW_StartPrep_PSN4 = 4;
	inline constexpr unsigned short ESW_StartPrep_EngineReady = 5;

	// Mode (Start)
	inline constexpr unsigned short ESW_Start_StartInitiation = 1;
	inline constexpr unsigned short ESW_Start_ThrustBuildup = 2;

	// Mode (Mainstage)
	inline constexpr unsigned short ESW_Mainstage_NormalControl = 1;
	inline constexpr unsigned short ESW_Mainstage_FixedDensity = 2;
	inline constexpr unsigned short ESW_Mainstage_ThrustLimiting = 3;
	inline constexpr unsigned short ESW_Mainstage_HydraulicLockup = 4;
	inline constexpr unsigned short ESW_Mainstage_ElectricalLockup = 5;

	// Mode (Shutdown)
	inline constexpr unsigned short ESW_Shutdown_ThrottleTo0 = 1;
	inline constexpr unsigned short ESW_Shutdown_PropellantValvesClosed = 2;
	inline constexpr unsigned short ESW_Shutdown_FailSafePneumatic = 3;

	// Mode (Post-Shutdown)
	inline constexpr unsigned short ESW_PostShutdown_Standby = 1;
	inline constexpr unsigned short ESW_PostShutdown_OxidizerDump = 2;
	inline constexpr unsigned short ESW_PostShutdown_TerminateSequence = 3;

	// Phase
	inline constexpr unsigned short ESW_Checkout = 1;
	inline constexpr unsigned short ESW_StartPrep = 2;
	inline constexpr unsigned short ESW_Start = 3;
	inline constexpr unsigned short ESW_Mainstage = 4;
	inline constexpr unsigned short ESW_Shutdown = 5;
	inline constexpr unsigned short ESW_PostShutdown = 6;

	// Limit Control Status
	inline constexpr unsigned short ESW_Inhibit = 0;
	inline constexpr unsigned short ESW_Enable = 1;

	// FRT Status
	inline constexpr unsigned short ESW_NormOperation = 0;
	inline constexpr unsigned short ESW_FRT = 1;

	// Channel Status
	inline constexpr unsigned short ESW_OK = 0;
	inline constexpr unsigned short ESW_CHA_ERROR = 1;
	inline constexpr unsigned short ESW_CHB_ERROR = 2;
	inline constexpr unsigned short ESW_CHA_CHB_ERROR = 3;
	inline constexpr unsigned short ESW_CHC_ERROR = 4;
	inline constexpr unsigned short ESW_CHA_CHC_ERROR = 5;
	inline constexpr unsigned short ESW_CHB_CHC_ERROR = 6;
	inline constexpr unsigned short ESW_CHA_CHB_CHC_ERROR = 7;

	// Command Status
	inline constexpr unsigned short ESW_NoCommand = 0;
	inline constexpr unsigned short ESW_CommandRejected_A = 1;
	inline constexpr unsigned short ESW_CommandRejected_B = 2;
	inline constexpr unsigned short ESW_Accepted = 3;

	// Load Mode
	inline constexpr unsigned short ESW_No = 0;

	// FID list
	inline constexpr unsigned short FID_LossOfControllerRedundancy = 1;
	inline constexpr unsigned short FID_RedlineExceeded = 13;
	inline constexpr unsigned short FID_SensorDesqualified = 111;

	// Delimiter list
	inline constexpr unsigned short Delimiter_DCUA = 1;
	inline constexpr unsigned short Delimiter_DCUB = 2;
	inline constexpr unsigned short Delimiter_IEA = 3;
	inline constexpr unsigned short Delimiter_IEB = 4;
	inline constexpr unsigned short Delimiter_OEA = 5;
	inline constexpr unsigned short Delimiter_OEB = 6;
	inline constexpr unsigned short Delimiter_CCVSEIIA = 7;
	inline constexpr unsigned short Delimiter_CCVSEIIB = 8;
	inline constexpr unsigned short Delimiter_MFVSEIIA = 9;
	inline constexpr unsigned short Delimiter_MFVSEIIB = 10;
	inline constexpr unsigned short Delimiter_MOVSEIIA = 11;
	inline constexpr unsigned short Delimiter_MOVSEIIB = 12;
	inline constexpr unsigned short Delimiter_FPOVSEIIA = 13;
	inline constexpr unsigned short Delimiter_FPOVSEIIB = 14;
	inline constexpr unsigned short Delimiter_OPOVSEIIA = 15;
	inline constexpr unsigned short Delimiter_OPOVSEIIB = 16;

	inline constexpr unsigned short Delimiter_HPFTDischargeTemperature = 1;
	inline constexpr unsigned short Delimiter_HPOTDischargeTemperature = 2;
	inline constexpr unsigned short Delimiter_HPOTPIntermediateSealPressure = 3;
	inline constexpr unsigned short Delimiter_MCCPC = 4;
	inline constexpr unsigned short Delimiter_OPBPurgePressure = 414;

	inline constexpr unsigned short Delimiter_FuelFlowrateIntraChannelTestChannelA = 101;

	// RAM addresses
	inline constexpr int RAM_AD08_CH = 0;
	inline constexpr int RAM_AD08_TREF1 = 1;
	inline constexpr int RAM_AD08_TREF2 = 2;

	inline constexpr int RAM_AD08_ESW = 3;

	inline constexpr int RAM_AD08_CMD_RCVD = 4;
	inline constexpr int RAM_AD08_VALIDCMD = 5;
	inline constexpr int RAM_AD08_CMD1 = 6;
	inline constexpr int RAM_AD08_CMD2 = 7;
	inline constexpr int RAM_AD08_CMD3 = 8;

	inline constexpr int RAM_AD08_CURCMD = 9;
	inline constexpr int RAM_AD08_PRVCMD = 10;

	inline constexpr int RAM_AD08_PC_CMD = 12;
	inline constexpr int RAM_AD08_PC_REF = 13;

	inline constexpr int RAM_AD08_TIME_ESC = 15;
	inline constexpr int RAM_AD08_TIME_STDN = 16;

	inline constexpr int RAM_AD08_START_ENA = 18;
	inline constexpr int RAM_AD08_SHUTDOWN_ENA = 19;

	inline constexpr int RAM_AD08_DCU_A_STATUS = 26;
	inline constexpr int RAM_AD08_DCU_B_STATUS = 27;
	inline constexpr int RAM_AD08_IE_A_STATUS = 28;
	inline constexpr int RAM_AD08_IE_B_STATUS = 29;
	inline constexpr int RAM_AD08_OE_A_STATUS = 30;
	inline constexpr int RAM_AD08_OE_B_STATUS = 31;

	inline constexpr int RAM_AD08_FID_BUFFER = 33;

	inline constexpr int RAM_AD08_WDT1 = 42;
	inline constexpr int RAM_AD08_WDT2 = 43;

	inline constexpr int RAM_AD08_NXT_PHASE = 45;
	inline constexpr int RAM_AD08_NXT_MODE = 46;


	inline constexpr int RAM_AD08_SENSOR_A = 180;
	inline constexpr int RAM_AD08_SENSOR_B = 270;

	inline constexpr int RAM_AD08_CCV_POS = 360;
	inline constexpr int RAM_AD08_MFV_POS = 361;
	inline constexpr int RAM_AD08_MOV_POS = 362;
	inline constexpr int RAM_AD08_FPOV_POS = 363;
	inline constexpr int RAM_AD08_OPOV_POS = 364;
	inline constexpr int RAM_AD08_FBV_POS = 365;
	inline constexpr int RAM_AD08_OBV_POS = 366;
	inline constexpr int RAM_AD08_AFV_POS = 367;
	inline constexpr int RAM_AD08_RIV_POS = 368;
	inline constexpr int RAM_AD08_CCV_SH = 369;
	inline constexpr int RAM_AD08_MFV_SH = 370;
	inline constexpr int RAM_AD08_MOV_SH = 371;
	inline constexpr int RAM_AD08_FPOV_SH = 372;
	inline constexpr int RAM_AD08_OPOV_SH = 373;

	inline constexpr int RAM_AD08_OE_A_ONOFF_REG_1 = 375;
	inline constexpr int RAM_AD08_OE_A_ONOFF_REG_2 = 376;
	inline constexpr int RAM_AD08_OE_B_ONOFF_REG_1 = 377;
	inline constexpr int RAM_AD08_OE_B_ONOFF_REG_2 = 378;

	inline constexpr int RAM_AD08_CCV_SEII_A_STATUS = 380;
	inline constexpr int RAM_AD08_CCV_SEII_B_STATUS = 381;
	inline constexpr int RAM_AD08_MFV_SEII_A_STATUS = 382;
	inline constexpr int RAM_AD08_MFV_SEII_B_STATUS = 383;
	inline constexpr int RAM_AD08_MOV_SEII_A_STATUS = 384;
	inline constexpr int RAM_AD08_MOV_SEII_B_STATUS = 385;
	inline constexpr int RAM_AD08_FPOV_SEII_A_STATUS = 386;
	inline constexpr int RAM_AD08_FPOV_SEII_B_STATUS = 387;
	inline constexpr int RAM_AD08_OPOV_SEII_A_STATUS = 388;
	inline constexpr int RAM_AD08_OPOV_SEII_B_STATUS = 389;

	inline constexpr int RAM_AD08_MCC_PC_QUAL_AVGR = 400;

	/*INFO Each controller normally requires two of three valid command paths
	from the GPC’s to control the SSME (start commands require three of three functional command
	paths). SSME controller software change RCN 4354 implemented in version OI-6 and subs added the
	capability for the engine to accept a shutdown enable/shutdown command pair on a single channel
	under special circumstances: an internal timer has expired (currently set at 512.86 seconds from engine
	start); limits have never been inhibited; the shutdown enable/shutdown command pair come in on the
	same channel, sequentially (with no other command in-between); and a valid command is not
	concurrently being received on the other two channels.*/
	inline constexpr int RAM_AD08_IGNT_TIME1 = 430;
	inline constexpr int RAM_AD08_IGNT_TIME2 = 431;
	inline constexpr int RAM_AD08_LIMITSINHIBITED = 432;
	inline constexpr int RAM_AD08_STEN_STDN_CH = 433;

	inline constexpr int RAM_AD08_CCV_CMD = 450;
	inline constexpr int RAM_AD08_MFV_CMD = 451;
	inline constexpr int RAM_AD08_MOV_CMD = 452;
	inline constexpr int RAM_AD08_FPOV_CMD = 453;
	inline constexpr int RAM_AD08_OPOV_CMD = 454;

	inline constexpr int RAM_AD08_MCC_IGNITER_CMD = 456;
	inline constexpr int RAM_AD08_FPB_IGNITER_CMD = 457;
	inline constexpr int RAM_AD08_OPB_IGNITER_CMD = 458;
	inline constexpr int RAM_AD08_FUELSYSTEMPURGE_CMD = 459;
	inline constexpr int RAM_AD08_BLEEDVALVESCONTROL_CMD = 460;
	inline constexpr int RAM_AD08_EMERGENCYSHUTDOWN_CMD = 461;
	inline constexpr int RAM_AD08_SHUTDOWNPURGE_CMD = 462;
	inline constexpr int RAM_AD08_HPOTPISPURGE_CMD = 463;
	inline constexpr int RAM_AD08_AFV_CMD = 464;
	inline constexpr int RAM_AD08_HPV_CMD = 465;

	inline constexpr int RAM_AD08_CCV_FO_SS_CMD = 470;
	inline constexpr int RAM_AD08_MFV_FO_SS_CMD = 471;
	inline constexpr int RAM_AD08_MOV_FO_SS_CMD = 472;
	inline constexpr int RAM_AD08_FPOV_FO_SS_CMD = 473;
	inline constexpr int RAM_AD08_OPOV_FO_SS_CMD = 474;
	inline constexpr int RAM_AD08_CCV_FS_SS_CMD = 475;
	inline constexpr int RAM_AD08_MFV_FS_SS_CMD = 476;
	inline constexpr int RAM_AD08_MOV_FS_SS_CMD = 477;
	inline constexpr int RAM_AD08_FPOV_FS_SS_CMD = 478;
	inline constexpr int RAM_AD08_OPOV_FS_SS_CMD = 479;

	inline constexpr int RAM_AD08_IGNT_CCV_POS = 500;
	inline constexpr int RAM_AD08_IGNT_MFV_POS = 548;
	inline constexpr int RAM_AD08_IGNT_MOV_POS = 596;
	inline constexpr int RAM_AD08_IGNT_FPOV_POS = 644;
	inline constexpr int RAM_AD08_IGNT_OPOV_POS = 692;
	inline constexpr int RAM_AD08_STDN_CCV_POS = 740;
	inline constexpr int RAM_AD08_STDN_MFV_POS = 788;
	inline constexpr int RAM_AD08_STDN_MOV_POS = 836;
	inline constexpr int RAM_AD08_STDN_FPOV_POS = 884;
	inline constexpr int RAM_AD08_STDN_OPOV_POS = 932;


	inline constexpr int RAM_AD08_VRC_1 = 50;
	inline constexpr int RAM_AD08_VRC_2 = 51;
	inline constexpr int RAM_AD08_VRC_3 = 52;
	inline constexpr int RAM_AD08_VRC_4 = 53;
	inline constexpr int RAM_AD08_VRC_5 = 54;
	inline constexpr int RAM_AD08_VRC_6 = 55;
	inline constexpr int RAM_AD08_VRC_7 = 56;
	inline constexpr int RAM_AD08_VRC_8 = 57;
	inline constexpr int RAM_AD08_VRC_9 = 58;
	inline constexpr int RAM_AD08_VRC_10 = 59;
	inline constexpr int RAM_AD08_VRC_11 = 60;
	inline constexpr int RAM_AD08_VRC_12 = 61;
	inline constexpr int RAM_AD08_VRC_13 = 62;
	inline constexpr int RAM_AD08_VRC_14 = 63;
	inline constexpr int RAM_AD08_VRC_15 = 64;
	inline constexpr int RAM_AD08_VRC_16 = 65;
	inline constexpr int RAM_AD08_VRC_17 = 66;
	inline constexpr int RAM_AD08_VRC_18 = 67;
	inline constexpr int RAM_AD08_VRC_19 = 68;
	inline constexpr int RAM_AD08_VRC_20 = 69;
	inline constexpr int RAM_AD08_VRC_21 = 70;
	inline constexpr int RAM_AD08_VRC_22 = 71;
	inline constexpr int RAM_AD08_VRC_23 = 72;
	inline constexpr int RAM_AD08_VRC_24 = 73;
	inline constexpr int RAM_AD08_VRC_25 = 74;
	inline constexpr int RAM_AD08_VRC_26 = 75;
	inline constexpr int RAM_AD08_VRC_27 = 76;
	inline constexpr int RAM_AD08_VRC_28 = 77;
	inline constexpr int RAM_AD08_VRC_29 = 78;
	inline constexpr int RAM_AD08_VRC_30 = 79;
	inline constexpr int RAM_AD08_VRC_31 = 80;
	inline constexpr int RAM_AD08_VRC_32 = 81;
	inline constexpr int RAM_AD08_VRC_33 = 82;
	inline constexpr int RAM_AD08_VRC_34 = 83;
	inline constexpr int RAM_AD08_VRC_35 = 84;
	inline constexpr int RAM_AD08_VRC_36 = 85;
	inline constexpr int RAM_AD08_VRC_37 = 86;
	inline constexpr int RAM_AD08_VRC_38 = 87;
	inline constexpr int RAM_AD08_VRC_39 = 88;
	inline constexpr int RAM_AD08_VRC_40 = 89;
	inline constexpr int RAM_AD08_VRC_41 = 90;
	inline constexpr int RAM_AD08_VRC_42 = 91;
	inline constexpr int RAM_AD08_VRC_43 = 92;
	inline constexpr int RAM_AD08_VRC_44 = 93;
	inline constexpr int RAM_AD08_VRC_45 = 94;
	inline constexpr int RAM_AD08_VRC_46 = 95;
	inline constexpr int RAM_AD08_VRC_47 = 96;
	inline constexpr int RAM_AD08_VRC_48 = 97;
	inline constexpr int RAM_AD08_VRC_49 = 98;
	inline constexpr int RAM_AD08_VRC_50 = 99;
	inline constexpr int RAM_AD08_VRC_51 = 100;
	inline constexpr int RAM_AD08_VRC_52 = 101;
	inline constexpr int RAM_AD08_VRC_53 = 102;
	inline constexpr int RAM_AD08_VRC_54 = 103;
	inline constexpr int RAM_AD08_VRC_55 = 104;
	inline constexpr int RAM_AD08_VRC_56 = 105;
	inline constexpr int RAM_AD08_VRC_57 = 106;
	inline constexpr int RAM_AD08_VRC_58 = 107;
	inline constexpr int RAM_AD08_VRC_59 = 108;
	inline constexpr int RAM_AD08_VRC_60 = 109;
	inline constexpr int RAM_AD08_VRC_61 = 110;
	inline constexpr int RAM_AD08_VRC_62 = 111;
	inline constexpr int RAM_AD08_VRC_63 = 112;
	inline constexpr int RAM_AD08_VRC_64 = 113;
	inline constexpr int RAM_AD08_VRC_65 = 114;
	inline constexpr int RAM_AD08_VRC_66 = 115;
	inline constexpr int RAM_AD08_VRC_67 = 116;
	inline constexpr int RAM_AD08_VRC_68 = 117;
	inline constexpr int RAM_AD08_VRC_69 = 118;
	inline constexpr int RAM_AD08_VRC_70 = 119;
	inline constexpr int RAM_AD08_VRC_71 = 120;
	inline constexpr int RAM_AD08_VRC_72 = 121;
	inline constexpr int RAM_AD08_VRC_73 = 122;
	inline constexpr int RAM_AD08_VRC_74 = 123;
	inline constexpr int RAM_AD08_VRC_75 = 124;
	inline constexpr int RAM_AD08_VRC_76 = 125;
	inline constexpr int RAM_AD08_VRC_77 = 126;
	inline constexpr int RAM_AD08_VRC_78 = 127;
	inline constexpr int RAM_AD08_VRC_79 = 128;
	inline constexpr int RAM_AD08_VRC_80 = 129;
	inline constexpr int RAM_AD08_VRC_81 = 130;
	inline constexpr int RAM_AD08_VRC_82 = 131;
	inline constexpr int RAM_AD08_VRC_83 = 132;
	inline constexpr int RAM_AD08_VRC_84 = 133;
	inline constexpr int RAM_AD08_VRC_85 = 134;
	inline constexpr int RAM_AD08_VRC_86 = 135;
	inline constexpr int RAM_AD08_VRC_87 = 136;
	inline constexpr int RAM_AD08_VRC_88 = 137;
	inline constexpr int RAM_AD08_VRC_89 = 138;
	inline constexpr int RAM_AD08_VRC_90 = 139;
	inline constexpr int RAM_AD08_VRC_91 = 140;
	inline constexpr int RAM_AD08_VRC_92 = 141;
	inline constexpr int RAM_AD08_VRC_93 = 142;
	inline constexpr int RAM_AD08_VRC_94 = 143;
	inline constexpr int RAM_AD08_VRC_95 = 144;
	inline constexpr int RAM_AD08_VRC_96 = 145;
	inline constexpr int RAM_AD08_VRC_97 = 146;
	inline constexpr int RAM_AD08_VRC_98 = 147;
	inline constexpr int RAM_AD08_VRC_99 = 148;
	inline constexpr int RAM_AD08_VRC_100 = 149;
	inline constexpr int RAM_AD08_VRC_101 = 150;
	inline constexpr int RAM_AD08_VRC_102 = 151;
	inline constexpr int RAM_AD08_VRC_103 = 152;
	inline constexpr int RAM_AD08_VRC_104 = 153;
	inline constexpr int RAM_AD08_VRC_105 = 154;
	inline constexpr int RAM_AD08_VRC_106 = 155;
	inline constexpr int RAM_AD08_VRC_107 = 156;
	inline constexpr int RAM_AD08_VRC_108 = 157;
	inline constexpr int RAM_AD08_VRC_109 = 158;
	inline constexpr int RAM_AD08_VRC_110 = 159;
	inline constexpr int RAM_AD08_VRC_111 = 160;
	inline constexpr int RAM_AD08_VRC_112 = 161;
	inline constexpr int RAM_AD08_VRC_113 = 162;
	inline constexpr int RAM_AD08_VRC_114 = 163;
	inline constexpr int RAM_AD08_VRC_115 = 164;
	inline constexpr int RAM_AD08_VRC_116 = 165;
	inline constexpr int RAM_AD08_VRC_117 = 166;
	inline constexpr int RAM_AD08_VRC_118 = 167;
	inline constexpr int RAM_AD08_VRC_119 = 168;
	inline constexpr int RAM_AD08_VRC_120 = 169;
	inline constexpr int RAM_AD08_VRC_121 = 170;
	inline constexpr int RAM_AD08_VRC_122 = 171;
	inline constexpr int RAM_AD08_VRC_123 = 172;
	inline constexpr int RAM_AD08_VRC_124 = 173;
	inline constexpr int RAM_AD08_VRC_125 = 174;
	inline constexpr int RAM_AD08_VRC_126 = 175;
	inline constexpr int RAM_AD08_VRC_127 = 176;
	inline constexpr int RAM_AD08_VRC_128 = 177;

	//////

	inline constexpr int SENSOR_COUNT = 30;

	// must match engine model sensor output
	inline constexpr unsigned short FPB_PP_IEA = 0x1F00;// 0001 1111 0000 0000
	inline constexpr unsigned short OPB_PP_IEA = 0x1F01;// 0001 1111 0000 0001
	inline constexpr unsigned short FPB_PP_IEB = 0x2F00;// 0010 1111 0000 0000
	inline constexpr unsigned short OPB_PP_IEB = 0x2F01;// 0010 1111 0000 0001
	inline constexpr unsigned short LPOT_DP_A = 0x1F02;// 0001 1111 0000 0010
	inline constexpr unsigned short LPOT_DP_B = 0x2F02;// 0010 1111 0000 0010
	inline constexpr unsigned short LPFT_DP_A = 0x1F03;// 0001 1111 0000 0011
	inline constexpr unsigned short LPFT_DP_B = 0x2F03;// 0010 1111 0000 0011
	inline constexpr unsigned short HPOTP_DP_A = 0x1F04;// 0001 1111 0000 0100
	inline constexpr unsigned short HPOTP_DP_B = 0x2F04;// 0010 1111 0000 0100
	inline constexpr unsigned short HPFTP_DP_A = 0x1F05;// 0001 1111 0000 0101
	inline constexpr unsigned short HPFTP_DP_B = 0x2F05;// 0010 1111 0000 0101
	inline constexpr unsigned short HPOTPBP_DP_A = 0x1F06;// 0001 1111 0000 0110
	inline constexpr unsigned short HPOTPBP_DP_B = 0x2F06;// 0010 1111 0000 0110
	inline constexpr unsigned short FS_PP_A = 0x1F07;// 0001 1111 0000 0111
	inline constexpr unsigned short FS_PP_B = 0x2F07;// 0010 1111 0000 0111
	inline constexpr unsigned short MCC_P_A1 = 0x1F08;// 0001 1111 0000 1000
	inline constexpr unsigned short MCC_P_B1 = 0x2F08;// 0010 1111 0000 1000
	inline constexpr unsigned short MCC_P_A2 = 0x1F09;// 0001 1111 0000 1001
	inline constexpr unsigned short MCC_P_B2 = 0x2F09;// 0010 1111 0000 1001
	inline constexpr unsigned short HPOTP_IS_A = 0x1F0A;// 0001 1111 0000 1010
	inline constexpr unsigned short HPOTP_IS_B = 0x2F0A;// 0010 1111 0000 1010
	inline constexpr unsigned short HPFT_DT_A2 = 0x1F0F;// 0001 1111 0000 1111
	inline constexpr unsigned short HPFT_DT_B2 = 0x2F0F;// 0010 1111 0000 1111
	inline constexpr unsigned short HPFT_DT_A3 = 0x1F10;// 0001 1111 0001 0000
	inline constexpr unsigned short HPFT_DT_B3 = 0x2F10;// 0010 1111 0001 0000
	inline constexpr unsigned short HPOT_DT_A2 = 0x1F11;// 0001 1111 0001 0001
	inline constexpr unsigned short HPOT_DT_B2 = 0x2F11;// 0010 1111 0001 0001
	inline constexpr unsigned short HPOT_DT_A3 = 0x1F12;// 0001 1111 0001 0010
	inline constexpr unsigned short HPOT_DT_B3 = 0x2F12;// 0010 1111 0001 0010
	inline constexpr unsigned short PBP_DT_A = 0x1F13;// 0001 1111 0001 0011
	inline constexpr unsigned short PBP_DT_B = 0x2F13;// 0010 1111 0001 0011
	inline constexpr unsigned short LPFP_DT_A = 0x1F14;// 0001 1111 0001 0100
	inline constexpr unsigned short LPFP_DT_B = 0x2F14;// 0010 1111 0001 0100
	inline constexpr unsigned short MOV_HT_A = 0x1F15;// 0001 1111 0001 0101
	inline constexpr unsigned short MOV_HT_B = 0x2F15;// 0010 1111 0001 0101
	inline constexpr unsigned short MFV_HT_A = 0x1F16;// 0001 1111 0001 0110
	inline constexpr unsigned short MFV_HT_B = 0x2F16;// 0010 1111 0001 0110
	inline constexpr unsigned short FF_A1 = 0x1000;// 0001 0000 0000 0000
	inline constexpr unsigned short FF_B1 = 0x2000;// 0010 0000 0000 0000
	inline constexpr unsigned short FF_A2 = 0x1001;// 0001 0001 0000 0000
	inline constexpr unsigned short FF_B2 = 0x2001;// 0010 0001 0000 0000
	inline constexpr unsigned short LPFTP_SS_A = 0x1004;// 0001 0100 0000 0000
	inline constexpr unsigned short LPFTP_SS_B = 0x2004;// 0010 0100 0000 0000
	inline constexpr unsigned short HPFTP_SS_A = 0x1005;// 0001 0101 0000 0000
	inline constexpr unsigned short HPFTP_SS_B = 0x2005;// 0010 0101 0000 0000


	class DigitalComputerUnit;

	class SSMEControllerSW_AD08:public SSMEControllerSW
	{
		private:
			unsigned short (SSMEControllerSW_AD08::*fptrSensorInput)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrSensorScale)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrVehicleCommands)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrMonitorSDLimits)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrEngineOperations)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrCommandActuators)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrCommandONOFFDevices)( void );

			unsigned short (SSMEControllerSW_AD08::*fptrOutputVDT)( void );
		public:
			explicit SSMEControllerSW_AD08( DigitalComputerUnit* DCU );
			~SSMEControllerSW_AD08( void );

			int GetConfig( void ) override;
			void SetConfig( int config ) override;

			void Executive( void ) override;

			unsigned short SelfTest( void );

			void ChangePhaseMode( void );

			unsigned short SensorInput( void );

			unsigned short SensorScale( void );
			void SensorQualification_Upper( unsigned short addr_snsr, unsigned short qual_limit_upper );
			void SensorQualification_Lower( unsigned short addr_snsr, unsigned short qual_limit_lower );
			void SensorQualification_UpperLower( unsigned short addr_snsr, unsigned short qual_limit_upper, unsigned short qual_limit_lower );
			void SensorsDesqualifyAll( int ch );
			//unsigned short CalcSensorAverage2( unsigned short addr_snsr_A, unsigned short addr_snsr_B );
			unsigned short CalcSensorAverage4( unsigned short addr_snsr_A, unsigned short addr_snsr_B, unsigned short addr_snsr_C, unsigned short addr_snsr_D );

			unsigned short VehicleCommands_Checkout_Standby( void );
			unsigned short VehicleCommands_StartPrep_PSN1( void );
			unsigned short VehicleCommands_StartPrep_PSN2( void );
			unsigned short VehicleCommands_StartPrep_PSN3( void );
			unsigned short VehicleCommands_StartPrep_PSN4( void );
			unsigned short VehicleCommands_StartPrep_EngineReady( void );
			unsigned short VehicleCommands_Start_StartInitiation( void );
			unsigned short VehicleCommands_Start_ThrustBuildup( void );
			unsigned short VehicleCommands_Mainstage_NormalControl( void );
			unsigned short VehicleCommands_Mainstage_FixedDensity( void );
			unsigned short VehicleCommands_Mainstage_ThrustLimiting( void );
			unsigned short VehicleCommands_Mainstage_HydraulicLockup( void );
			unsigned short VehicleCommands_Mainstage_ElectricalLockup( void );
			unsigned short VehicleCommands_Shutdown_ThrottleTo0( void );
			unsigned short VehicleCommands_Shutdown_PropellantValvesClosed( void );
			unsigned short VehicleCommands_Shutdown_FailSafePneumatic( void );
			unsigned short VehicleCommands_PostShutdown_Standby( void );
			unsigned short VehicleCommands_PostShutdown_OxidizerDump( void );
			unsigned short VehicleCommands_PostShutdown_TerminateSequence( void );

			unsigned short MonitorSDLimits_Mainstage_NormalControl( void );
			unsigned short MonitorSDLimits_Mainstage_HydraulicLockup( void );

			unsigned short EngineOperations_Checkout_Standby( void );
			unsigned short EngineOperations_StartPrep_PSN1( void );
			unsigned short EngineOperations_StartPrep_PSN2( void );
			unsigned short EngineOperations_StartPrep_PSN3( void );
			unsigned short EngineOperations_StartPrep_PSN4( void );
			unsigned short EngineOperations_StartPrep_EngineReady( void );
			unsigned short EngineOperations_Start_StartInitiation( void );
			unsigned short EngineOperations_Start_ThrustBuildup( void );
			unsigned short EngineOperations_Mainstage_NormalControl( void );
			unsigned short EngineOperations_Mainstage_FixedDensity( void );
			unsigned short EngineOperations_Mainstage_ThrustLimiting( void );
			unsigned short EngineOperations_Mainstage_HydraulicLockup( void );
			unsigned short EngineOperations_Mainstage_ElectricalLockup( void );
			unsigned short EngineOperations_Shutdown_ThrottleTo0( void );
			unsigned short EngineOperations_Shutdown_PropellantValvesClosed( void );
			unsigned short EngineOperations_Shutdown_FailSafePneumatic( void );
			unsigned short EngineOperations_PostShutdown_Standby( void );
			unsigned short EngineOperations_PostShutdown_OxidizerDump( void );
			unsigned short EngineOperations_PostShutdown_TerminateSequence( void );

			unsigned short CommandActuators( void );

			unsigned short CommandONOFFDevices( void );

			unsigned short OutputVDT( void );


			void Set_ESW_SelfTestStatus( unsigned short SelfTestStatus );
			unsigned short Get_ESW_SelfTestStatus( void ) const;
			void Set_ESW_Mode( unsigned short Mode );
			unsigned short Get_ESW_Mode( void ) const;
			void Set_ESW_Phase( unsigned short Phase );
			unsigned short Get_ESW_Phase( void ) const;
			void Set_ESW_LimitControlStatus( unsigned short LimitControlStatus );
			unsigned short Get_ESW_LimitControlStatus( void ) const;
			void Set_ESW_FRTStatus( unsigned short FRTStatus );
			unsigned short Get_ESW_FRTStatus( void ) const;
			void Set_ESW_ChannelStatus( unsigned short ChannelStatus );
			unsigned short Get_ESW_ChannelStatus( void ) const;
			void Set_ESW_CommandStatus( unsigned short CommandStatus );
			unsigned short Get_ESW_CommandStatus( void ) const;

			////////////////////////////////////////////////


			void GetTime( void );
			void RotateCommand( void );
			void AddFID( unsigned short FID, unsigned short Delimiter );
			unsigned short GetFID( void );
			unsigned short CommandVoting( void );

			void ValveSchedule( int tableaddr, int cmdaddr, int timeaddr, int currentposaddr );

			void LoadStartValveSchedule( void );
			void LoadShutdownValveSchedule( void );
			void UpdateShutdownValveSchedule( double dPC );

			void Interrupt( int num ) override;
	};
}


#endif// _mps_AD08_H_