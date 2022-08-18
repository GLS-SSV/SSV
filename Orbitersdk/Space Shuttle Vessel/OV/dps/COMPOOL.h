#ifndef _COMPOOL_H_
#define _COMPOOL_H_

// ----------------------------------------------------------------
// SSV COMPOOL definition
// ----------------------------------------------------------------
// SINGLE => 16b
// DOUBLE => 32b

// INFO: SCALAR should always be DOUBLE, and implemented in C with a 32b float

// memory configuration
inline constexpr unsigned int SCP_MC = 0x00000;// INTEGER SINGLE
// current major mode
inline constexpr unsigned int SCP_MM = 0x00001;// INTEGER SINGLE
// new major mode
inline constexpr unsigned int SCP_NEW_MM = 0x00002;// INTEGER SINGLE

// outputs to EIUs
inline constexpr unsigned int SCP_EIU_1_CMD = 0x00003;// INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_2_CMD = 0x00004;// INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_3_CMD = 0x00005;// INTEGER SINGLE

// inputs from EIUs
inline constexpr unsigned int SCP_EIU_1_PRIDATA = 0x00006;// ARRAY(32) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_2_PRIDATA = 0x00026;// ARRAY(32) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_3_PRIDATA = 0x00046;// ARRAY(32) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_1_SECDATA = 0x00066;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_2_SECDATA = 0x0006c;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_3_SECDATA = 0x00072;// ARRAY(6) INTEGER SINGLE

// output to DDU-1
inline constexpr unsigned int SCP_DDU1_ADI = 0x00078;// ARRAY(14) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU1_HSI = 0x00086;// ARRAY(10) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU1_AVVI = 0x00090;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU1_AMI = 0x00096;// ARRAY(6) INTEGER SINGLE

// output to DDU-2
inline constexpr unsigned int SCP_DDU2_ADI = 0x0009c;// ARRAY(14) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU2_HSI = 0x000aa;// ARRAY(10) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU2_AVVI = 0x000b4;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU2_AMI = 0x000ba;// ARRAY(6) INTEGER SINGLE

// output to HUD-1
inline constexpr unsigned int SCP_HUD1_MSG1 = 0x000c0;// ARRAY(31) INTEGER SINGLE
inline constexpr unsigned int SCP_HUD1_MSG2 = 0x000df;// ARRAY(12) INTEGER SINGLE

// output to HUD-2
inline constexpr unsigned int SCP_HUD2_MSG1 = 0x000eb;// ARRAY(31) INTEGER SINGLE
inline constexpr unsigned int SCP_HUD2_MSG2 = 0x0010a;// ARRAY(12) INTEGER SINGLE

// MDM FF1 input
// Radar Altimeter 1 data
inline constexpr unsigned int SCP_FF1_IOM0_CH4_DATA = 0x00116;// INTEGER SINGLE
// 3-LH_BODY_FLAP_UP_A
// 4-LH_BODY_FLAP_DOWN_A
// 5-MPS ME-1 SHUTDOWN CMD A
inline constexpr unsigned int SCP_FF1_IOM4_CH0_DATA = 0x00117;// INTEGER SINGLE
// 10-FCS LH PITCH AUTO MODE A
// 11-FCS LH PITCH CSS MODE A
// 13-FCS LH R-Y AUTO MODE A
// 14-FCS LH R-Y CSS MODE A
// 15-LH BODY FLAP AUTO/MANUAL A
inline constexpr unsigned int SCP_FF1_IOM4_CH1_DATA = 0x00118;// INTEGER SINGLE
// 0-LH SPD BK/THROT AUTO/MAN A
// 3-ENTRY ROLL MODE NO Y JET A
inline constexpr unsigned int SCP_FF1_IOM4_CH2_DATA = 0x00119;// INTEGER SINGLE
// 7-FWD THC POS X OUTPUT - A
// 8-FWD THC NEG X OUTPUT - A
// 9-FWD THC POS Y OUTPUT - A
// 10-FWD THC NEG Y OUTPUT - A
// 11-FWD THC POS Z OUTPUT - A
// 12-FWD THC NEG Z OUTPUT - A
// 13-LH SBTC TAKEOVER - A
inline constexpr unsigned int SCP_FF1_IOM6_CH0_DATA = 0x0011a;// INTEGER SINGLE
// 1-LH_RHC_PLUS_PITCH_TRIM_A
// 2-LH_RHC_MINUS_PITCH_TRIM_A
// 3-LH_RHC_PLUS_ROLL_TRIM_A
// 4-LH_RHC_MINUS_ROLL_TRIM_A
// 5-SRB SEPARATION AUTO A CMD
// 6-SRB SEPN MANUAL/AUTO ENABLE A CMD
// 7-SRB SEPARATION INITIATE A CMD
inline constexpr unsigned int SCP_FF1_IOM6_CH1_DATA = 0x0011b;// INTEGER SINGLE
// 4-FWD DAP SELECT A - A
// 5-FWD DAP SELECT B - A
// 6-AFT DAP SELECT A - C
// 7-AFT DAP SELECT B - C
// 8-FWD DAP AUTO A
// 9-FWD DAP MAN A
// 10-AFT DAP AUTO C
// 11-AFT DAP MAN C
inline constexpr unsigned int SCP_FF1_IOM9_CH0_DATA = 0x0011c;// INTEGER SINGLE
// 1-SENSE SW -Z CON A
// 2-SENSE SW -X CON A
// 3-ENTRY ROLL MODE L GAIN - A
// 4-FWD ROTATION ROLL DISC RATE A
// 5-FWD ROTATION ROLL ACCEL A
// 6-FWD ROTATION ROLL PULSE A
// 7-FWD ROTATION PITCH DISC RATE A
// 8-FWD ROTATION PITCH ACCEL A
// 9-FWD ROTATION PITCH PULSE A
// 10-FWD ROTATION YAW DISC RATE A
// 11-FWD ROTATION YAW ACCEL A
// 12-FWD ROTATION YAW PULSE A
// 13-FWD RCS JETS NORM A
// 14-FWD RCS JETS VERNIER A
// 15-FWD TRANSLATION X NORM A
inline constexpr unsigned int SCP_FF1_IOM9_CH1_DATA = 0x0011d;// INTEGER SINGLE
// 0-FWD TRANSLATION X PULSE A
// 1-FWD TRANSLATION X LVLH A
// 2-FWD TRANSLATION Y NORM A
// 3-FWD TRANSLATION Y PULSE A
// 4-FWD TRANSLATION Y LOW Z A
// 5-FWD TRANSLATION Z NORM A
// 6-FWD TRANSLATION Z PULSE A
// 7-FWD TRANSLATION Z HIGH A
// 8-MPS PRPLT DUMP SEQUENCE START A
// 9-MPS PRPLT DUMP SEQUENCE STOP A
inline constexpr unsigned int SCP_FF1_IOM9_CH2_DATA = 0x0011e;// INTEGER SINGLE
// 1-LH_PLUS_PITCH_TRIM_A
// 2-LH_MINUS_PITCH_TRIM_A
// 3-LH_PLUS_ROLL_TRIM_A
// 4-LH_MINUS_ROLL_TRIM_A
// 5-LH_PLUS_YAW_TRIM_A
// 6-LH_MINUS_YAW_TRIM_A
// 13-CDR RDR ALTM SEL 1
inline constexpr unsigned int SCP_FF1_IOM12_CH0_DATA = 0x0011f;// INTEGER SINGLE
// 8-LH_RHC_TRIM_INHIBIT_A
inline constexpr unsigned int SCP_FF1_IOM12_CH1_DATA = 0x00120;// INTEGER SINGLE
// 14-AFT RCS OPTIONS NORM C
// 15-AFT RCS OPTIONS VERNIER C
inline constexpr unsigned int SCP_FF1_IOM12_CH2_DATA = 0x00121;// INTEGER SINGLE
// 7-AFT THC POS X OUTPUT - A
// 8-AFT THC NEG X OUTPUT - A
// 9-AFT THC POS Y OUTPUT - A
// 10-AFT THC NEG Y OUTPUT - A
// 11-AFT THC POS Z OUTPUT - A
// 12-AFT THC NEG Z OUTPUT - A
inline constexpr unsigned int SCP_FF1_IOM15_CH0_DATA = 0x00122;// INTEGER SINGLE
// 5-ET SEPARATION MANUAL ENABLE A CMD
// 6-ET SEPARATION INITIATE A CMD
// 7-ET SEPARATION AUTO A CMD
inline constexpr unsigned int SCP_FF1_IOM15_CH1_DATA = 0x00123;// INTEGER SINGLE

// MDM FF2 input
// Radar Altimeter 2 data
inline constexpr unsigned int SCP_FF2_IOM0_CH4_DATA = 0x00124;// INTEGER SINGLE
// 2-ENTRY ROLL MODE NO Y JET B
// 3-LH_BODY_FLAP_UP_B
// 4-LH_BODY_FLAP_DOWN_B
// 5-MPS ME-1 SHUTDOWN CMD B
inline constexpr unsigned int SCP_FF2_IOM4_CH0_DATA = 0x00125;// INTEGER SINGLE
// 10-FCS LH PITCH AUTO MODE B
// 11-FCS LH PITCH CSS MODE B
// 13-FCS LH R-Y AUTO MODE B
// 14-FCS LH R-Y CSS MODE B
// 15-LH BODY FLAP AUTO/MANUAL B
inline constexpr unsigned int SCP_FF2_IOM4_CH1_DATA = 0x00126;// INTEGER SINGLE
// 0-LH SPD BK/THROT AUTO/MAN B
// 1-MPS ENG LIMIT CONTROL NO. 1 ENABLE
// 2-MPS ENG LIMIT CONTROL NO. 1 INHIBIT
// 3-MPS ENG LIMIT CONTROL NO. 1 AUTO
inline constexpr unsigned int SCP_FF2_IOM4_CH2_DATA = 0x00127;// INTEGER SINGLE
// 7-FWD THC POS X OUTPUT - B
// 8-FWD THC NEG X OUTPUT - B
// 9-FWD THC POS Y OUTPUT - B
// 10-FWD THC NEG Y OUTPUT - B
// 11-FWD THC POS Z OUTPUT - B
// 12-FWD THC NEG Z OUTPUT - B
// 13-LH SBTC TAKEOVER - B
inline constexpr unsigned int SCP_FF2_IOM6_CH0_DATA = 0x00128;// INTEGER SINGLE
// 1-LH_RHC_PLUS_PITCH_TRIM_B
// 2-LH_RHC_MINUS_PITCH_TRIM_B
// 3-LH_RHC_PLUS_ROLL_TRIM_B
// 4-LH_RHC_MINUS_ROLL_TRIM_B
inline constexpr unsigned int SCP_FF2_IOM6_CH1_DATA = 0x00129;// INTEGER SINGLE
// 4-FWD DAP SELECT A - B
// 5-FWD DAP SELECT B - B
// 8-FWD DAP AUTO B
// 9-FWD DAP MAN B
inline constexpr unsigned int SCP_FF2_IOM9_CH0_DATA = 0x0012a;// INTEGER SINGLE
// 0-MPS ME-2 SHUTDOWN CMD A
// 1-SENSE SW -Z CON B
// 2-SENSE SW -X CON B
// 3-ENTRY ROLL MODE L GAIN - B
// 4-FWD ROTATION ROLL DISC RATE B
// 5-FWD ROTATION ROLL ACCEL B
// 6-FWD ROTATION ROLL PULSE B
// 7-FWD ROTATION PITCH DISC RATE B
// 8-FWD ROTATION PITCH ACCEL B
// 9-FWD ROTATION PITCH PULSE B
// 10-FWD ROTATION YAW DISC RATE B
// 11-FWD ROTATION YAW ACCEL B
// 12-FWD ROTATION YAW PULSE B
// 13-FWD RCS JETS NORM B
// 14-FWD RCS JETS VERNIER B
// 15-FWD TRANSLATION X NORM B
inline constexpr unsigned int SCP_FF2_IOM9_CH1_DATA = 0x0012b;// INTEGER SINGLE
// 0-FWD TRANSLATION X PULSE B
// 1-FWD TRANSLATION X LVLH B
// 2-FWD TRANSLATION Y NORM B
// 3-FWD TRANSLATION Y PULSE B
// 4-FWD TRANSLATION Y LOW Z B
// 5-FWD TRANSLATION Z NORM B
// 6-FWD TRANSLATION Z PULSE B
// 7-FWD TRANSLATION Z HIGH B
// 8-MPS PRPLT DUMP SEQUENCE START B
// 9-MPS PRPLT DUMP SEQUENCE STOP B
inline constexpr unsigned int SCP_FF2_IOM9_CH2_DATA = 0x0012c;// INTEGER SINGLE
// 1-LH_PLUS_PITCH_TRIM_B
// 2-LH_MINUS_PITCH_TRIM_B
// 3-LH_PLUS_ROLL_TRIM_B
// 4-LH_MINUS_ROLL_TRIM_B
// 5-LH_PLUS_YAW_TRIM_B
// 6-LH_MINUS_YAW_TRIM_B
// 13-PLT RDR ALTM SEL 1
inline constexpr unsigned int SCP_FF2_IOM12_CH0_DATA = 0x0012d;// INTEGER SINGLE
// 8-LH_RHC_TRIM_INHIBIT_B
// 10-FCS RH PITCH AUTO MODE A
// 11-FCS RH PITCH CSS MODE A
// 13-FCS RH R-Y AUTO MODE A
// 14-FCS RH R-Y CSS MODE A
// 15-RH BODY FLAP AUTO/MANUAL A
inline constexpr unsigned int SCP_FF2_IOM12_CH1_DATA = 0x0012e;// INTEGER SINGLE
// 0-RH SPD BK/THROT AUTO/MAN A
inline constexpr unsigned int SCP_FF2_IOM12_CH2_DATA = 0x0012f;// INTEGER SINGLE
// 7-AFT THC POS X OUTPUT - B
// 8-AFT THC NEG X OUTPUT - B
// 9-AFT THC POS Y OUTPUT - B
// 10-AFT THC NEG Y OUTPUT - B
// 11-AFT THC POS Z OUTPUT - B
// 12-AFT THC NEG Z OUTPUT - B
// 13-RH SBTC TAKEOVER - A
inline constexpr unsigned int SCP_FF2_IOM15_CH0_DATA = 0x00130;// INTEGER SINGLE

// MDM FF3 input
// 3-RH_BODY_FLAP_UP_A
// 4-RH_BODY_FLAP_DOWN_A
// 5-MPS ME-3 SHUTDOWN CMD A
inline constexpr unsigned int SCP_FF3_IOM4_CH0_DATA = 0x00131;// INTEGER SINGLE
// 10-FCS LH PITCH AUTO MODE C
// 11-FCS LH PITCH CSS MODE C
// 13-FCS LH R-Y AUTO MODE C
// 14-FCS LH R-Y CSS MODE C
// 15-LH BODY FLAP AUTO/MANUAL C
inline constexpr unsigned int SCP_FF3_IOM4_CH1_DATA = 0x00132;// INTEGER SINGLE
// 0-LH SPD BK/THROT AUTO/MAN C
// 1-MPS ENG LIMIT CONTROL NO. 2 ENABLE
// 2-MPS ENG LIMIT CONTROL NO. 2 INHIBIT
// 3-MPS ENG LIMIT CONTROL NO. 2 AUTO
inline constexpr unsigned int SCP_FF3_IOM4_CH2_DATA = 0x00133;// INTEGER SINGLE
// 7-FWD THC POS X OUTPUT - C
// 8-FWD THC NEG X OUTPUT - C
// 9-FWD THC POS Y OUTPUT - C
// 10-FWD THC NEG Y OUTPUT - C
// 11-FWD THC POS Z OUTPUT - C
// 12-FWD THC NEG Z OUTPUT - C
// 13-LH SBTC TAKEOVER - C
inline constexpr unsigned int SCP_FF3_IOM6_CH0_DATA = 0x00134;// INTEGER SINGLE
// 5-SRB SEPARATION AUTO C CMD
// 6-SRB SEPN MANUAL/AUTO ENABLE C CMD
// 7-SRB SEPARATION INITIATE C CMD
inline constexpr unsigned int SCP_FF3_IOM6_CH1_DATA = 0x00135;// INTEGER SINGLE
// 4-AFT DAP SELECT A - A
// 5-AFT DAP SELECT B - A
// 6-FWD DAP SELECT A - C
// 7-FWD DAP SELECT B - C
// 8-AFT DAP AUTO A
// 9-AFT DAP MAN A
// 10-FWD DAP AUTO C
// 11-FWD DAP MAN C
inline constexpr unsigned int SCP_FF3_IOM9_CH0_DATA = 0x00136;// INTEGER SINGLE
// 0-MPS ME-2 SHUTDOWN CMD B
// 1-SENSE SW -Z CON C
// 2-SENSE SW -X CON C
// 3-ENTRY ROLL MODE L GAIN - C
// 4-AFT ROTATION ROLL DISC RATE A
// 5-AFT ROTATION ROLL ACCEL A
// 6-AFT ROTATION ROLL PULSE A
// 7-AFT ROTATION PITCH DISC RATE A
// 8-AFT ROTATION PITCH ACCEL A
// 9-AFT ROTATION PITCH PULSE A
// 10-AFT ROTATION YAW DISC RATE A
// 11-AFT ROTATION YAW ACCEL A
// 12-AFT ROTATION YAW PULSE A
// 13-AFT RCS JETS NORM A
// 14-AFT RCS JETS VERNIER A
// 15-AFT TRANSLATION X NORM A
inline constexpr unsigned int SCP_FF3_IOM9_CH1_DATA = 0x00137;// INTEGER SINGLE
// 0-AFT TRANSLATION X PULSE A
// 1-AFT TRANSLATION X LVLH A
// 2-AFT TRANSLATION Y NORM A
// 3-AFT TRANSLATION Y PULSE A
// 4-AFT TRANSLATION Y LOW Z A
// 5-AFT TRANSLATION Z NORM A
// 6-AFT TRANSLATION Z PULSE A
// 7-AFT TRANSLATION Z HIGH A
// 8-MPS BACKUP LH2 PRPLT DUMP START A
// 9-MPS BACKUP LH2 PRPLT DUMP STOP A
inline constexpr unsigned int SCP_FF3_IOM9_CH2_DATA = 0x00138;// INTEGER SINGLE
// 1-RH_PLUS_PITCH_TRIM_A
// 2-RH_MINUS_PITCH_TRIM_A
// 3-RH_PLUS_ROLL_TRIM_A
// 4-RH_MINUS_ROLL_TRIM_A
// 5-RH_PLUS_YAW_TRIM_A
// 6-RH_MINUS_YAW_TRIM_A
inline constexpr unsigned int SCP_FF3_IOM12_CH0_DATA = 0x00139;// INTEGER SINGLE
// 2-ENTRY ROLL MODE NO Y JET C
// 8-RH_RHC_TRIM_INHIBIT_A
// 10-FCS RH PITCH AUTO MODE B
// 11-FCS RH PITCH CSS MODE B
// 13-FCS RH R-Y AUTO MODE B
// 14-FCS RH R-Y CSS MODE B
// 15-RH BODY FLAP AUTO/MANUAL B
inline constexpr unsigned int SCP_FF3_IOM12_CH1_DATA = 0x0013a;// INTEGER SINGLE
// 0-RH SPD BK/THROT AUTO/MAN B
// 14-FWD RCS OPTIONS NORM C
// 15-FWD RCS OPTIONS VERNIER C
inline constexpr unsigned int SCP_FF3_IOM12_CH2_DATA = 0x0013b;// INTEGER SINGLE
// 7-AFT THC POS X OUTPUT - C
// 8-AFT THC NEG X OUTPUT - C
// 9-AFT THC POS Y OUTPUT - C
// 10-AFT THC NEG Y OUTPUT - C
// 11-AFT THC POS Z OUTPUT - C
// 12-AFT THC NEG Z OUTPUT - C
// 13-RH SBTC TAKEOVER - B
inline constexpr unsigned int SCP_FF3_IOM15_CH0_DATA = 0x0013c;// INTEGER SINGLE
// 1-RH_RHC_PLUS_PITCH_TRIM_A
// 2-RH_RHC_MINUS_PITCH_TRIM_A
// 3-RH_RHC_PLUS_ROLL_TRIM_A
// 4-RH_RHC_MINUS_ROLL_TRIM_A
// 5-ET SEPARATION MANUAL ENABLE C CMD
// 6-ET SEPARATION INITIATE C CMD
// 7-ET SEPARATION AUTO C CMD
inline constexpr unsigned int SCP_FF3_IOM15_CH1_DATA = 0x0013d;// INTEGER SINGLE

// MDM FF4 input
// 3-RH_BODY_FLAP_UP_B
// 4-RH_BODY_FLAP_DOWN_B
// 5-MPS ME-3 SHUTDOWN CMD B
inline constexpr unsigned int SCP_FF4_IOM4_CH0_DATA = 0x0013e;// INTEGER SINGLE
// 1-MPS ENG LIMIT CONTROL NO. 3 ENABLE
// 2-MPS ENG LIMIT CONTROL NO. 3 INHIBIT
// 3-MPS ENG LIMIT CONTROL NO. 3 AUTO
inline constexpr unsigned int SCP_FF4_IOM4_CH2_DATA = 0x0013f;// INTEGER SINGLE
// 5-SRB SEPARATION AUTO B CMD
// 6-SRB SEPN MANUAL/AUTO ENABLE B CMD
// 7-SRB SEPARATION INITIATE B CMD
inline constexpr unsigned int SCP_FF4_IOM6_CH1_DATA = 0x00140;// INTEGER SINGLE
// 4-AFT DAP SELECT A - B
// 5-AFT DAP SELECT B - B
// 8-AFT DAP AUTO B
// 9-AFT DAP MAN B
inline constexpr unsigned int SCP_FF4_IOM9_CH0_DATA = 0x00141;// INTEGER SINGLE
// 3-ENTRY ROLL MODE L GAIN - D
// 4-AFT ROTATION ROLL DISC RATE B
// 5-AFT ROTATION ROLL ACCEL B
// 6-AFT ROTATION ROLL PULSE B
// 7-AFT ROTATION PITCH DISC RATE B
// 8-AFT ROTATION PITCH ACCEL B
// 9-AFT ROTATION PITCH PULSE B
// 10-AFT ROTATION YAW DISC RATE B
// 11-AFT ROTATION YAW ACCEL B
// 12-AFT ROTATION YAW PULSE B
// 13-AFT RCS JETS NORM B
// 14-AFT RCS JETS VERNIER B
// 15-AFT TRANSLATION X NORM B
inline constexpr unsigned int SCP_FF4_IOM9_CH1_DATA = 0x00142;// INTEGER SINGLE
// 0-AFT TRANSLATION X PULSE B
// 1-AFT TRANSLATION X LVLH B
// 2-AFT TRANSLATION Y NORM B
// 3-AFT TRANSLATION Y PULSE B
// 4-AFT TRANSLATION Y LOW Z B
// 5-AFT TRANSLATION Z NORM B
// 6-AFT TRANSLATION Z PULSE B
// 7-AFT TRANSLATION Z HIGH B
// 8-MPS BACKUP LH2 PRPLT DUMP START B
// 9-MPS BACKUP LH2 PRPLT DUMP STOP B
inline constexpr unsigned int SCP_FF4_IOM9_CH2_DATA = 0x00143;// INTEGER SINGLE
// 1-RH_PLUS_PITCH_TRIM_B
// 2-RH_MINUS_PITCH_TRIM_B
// 3-RH_PLUS_ROLL_TRIM_B
// 4-RH_MINUS_ROLL_TRIM_B
// 5-RH_PLUS_YAW_TRIM_B
// 6-RH_MINUS_YAW_TRIM_B
inline constexpr unsigned int SCP_FF4_IOM12_CH0_DATA = 0x00144;// INTEGER SINGLE
// 8-RH_RHC_TRIM_INHIBIT_B
// 10-FCS RH PITCH AUTO MODE C
// 11-FCS RH PITCH CSS MODE C
// 13-FCS RH R-Y AUTO MODE C
// 14-FCS RH R-Y CSS MODE C
// 15-RH BODY FLAP AUTO/MANUAL C
inline constexpr unsigned int SCP_FF4_IOM12_CH1_DATA = 0x00145;// INTEGER SINGLE
// 0-RH SPD BK/THROT AUTO/MAN C
// 15-ENTRY ROLL MODE NO Y JET D
inline constexpr unsigned int SCP_FF4_IOM12_CH2_DATA = 0x00146;// INTEGER SINGLE
// 13-RH SBTC TAKEOVER - C
inline constexpr unsigned int SCP_FF4_IOM15_CH0_DATA = 0x00147;// INTEGER SINGLE
// 1-RH_RHC_PLUS_PITCH_TRIM_B
// 2-RH_RHC_MINUS_PITCH_TRIM_B
// 3-RH_RHC_PLUS_ROLL_TRIM_B
// 4-RH_RHC_MINUS_ROLL_TRIM_B
// 5-ET SEPARATION MANUAL ENABLE B CMD
// 6-ET SEPARATION INITIATE B CMD
// 7-ET SEPARATION AUTO B CMD
inline constexpr unsigned int SCP_FF4_IOM15_CH1_DATA = 0x00148;// INTEGER SINGLE

// MDM FF1 output
// 0-F7 LIGHT: C MPS AMBER STATUS
// 7-F6 LIGHT A: RCS CMD "ROLL LEFT"
// 8-F6 LIGHT A: RCS CMD "ROLL RIGHT"
// 9-F6 LIGHT A: RCS CMD "YAW LEFT"
// 10-F6 LIGHT A: RCS CMD "YAW RIGHT"
// 11-F6 LIGHT A: RCS CMD "PITCH UP"
// 12-F6 LIGHT A: RCS CMD "PITCH DOWN"
// 13-C3 LIGHT: FWD DAP CONTROL "AUTO"
// 14-C3 LIGHT: FWD DAP SELECT "A"
// 15-C3 LIGHT: FWD DAP RCS JETS "NORM"
inline constexpr unsigned int SCP_FF1_IOM2_CH1_DATA = 0x00149;// INTEGER SINGLE
// 3-C3 LIGHT: FWD DAP CONTROL "MAN"
// 4-C3 LIGHT: FWD DAP SELECT "B"
// 5-C3 LIGHT: FWD DAP RCS JETS "VERN"
inline constexpr unsigned int SCP_FF1_IOM2_CH2_DATA = 0x0014a;// INTEGER SINGLE
// 0-FWD EVENT TIMER: ABORT TIMER_RESET
inline constexpr unsigned int SCP_FF1_IOM5_CH1_DATA = 0x0014b;// INTEGER SINGLE
// 4-F2 LIGHT: LH FCS BODY FLAP "AUTO"
// 5-F2 LIGHT: LH FCS SPEED BK "AUTO"
// 6-F2 LIGHT: LH FCS PITCH "AUTO"
// 7-F2 LIGHT: LH FCS ROLL/YAW "AUTO"
inline constexpr unsigned int SCP_FF1_IOM10_CH0_DATA = 0x0014c;// INTEGER SINGLE
// 0-F7 LIGHT: C MPS RED STATUS
// 1-C3 LIGHT: FWD MAN ROT ROLL "DISC RT"
// 2-C3 LIGHT: FWD MAN ROT ROLL "ACCEL"
// 3-C3 LIGHT: FWD MAN ROT ROLL "PULSE"
// 4-C3 LIGHT: FWD MAN ROT PITCH "DISC RT"
// 5-C3 LIGHT: FWD MAN ROT PITCH "ACCEL"
// 6-C3 LIGHT: FWD MAN ROT PITCH "PULSE"
// 7-C3 LIGHT: FWD MAN ROT YAW "DISC RT"
// 8-C3 LIGHT: FWD MAN ROT YAW "ACCEL"
// 9-C3 LIGHT: FWD MAN ROT YAW "PULSE"
// 10-C3 LIGHT: FWD MAN TRANS X "NORM"
// 11-C3 LIGHT: FWD MAN TRANS X "PULSE"
// 12-C3 LIGHT: FWD MAN TRANS X "LVLH"
// 13-C3 LIGHT: FWD MAN TRANS Y "NORM"
// 14-C3 LIGHT: FWD MAN TRANS Y "PULSE"
// 15-C3 LIGHT: FWD MAN TRANS Y "LOW Z"
inline constexpr unsigned int SCP_FF1_IOM10_CH1_DATA = 0x0014d;// INTEGER SINGLE
// 0-C3 LIGHT: FWD MAN TRANS Z "NORM"
// 1-C3 LIGHT: FWD MAN TRANS Z "PULSE"
// 2-C3 LIGHT: FWD MAN TRANS Z "HIGH"
inline constexpr unsigned int SCP_FF1_IOM10_CH2_DATA = 0x0014e;// INTEGER SINGLE

// MDM FF2 output
// 0-F7 LIGHT: L MPS AMBER STATUS
inline constexpr unsigned int SCP_FF2_IOM2_CH1_DATA = 0x0014f;// INTEGER SINGLE
// 4-F2 LIGHT: LH FCS BODY FLAP "MAN"
// 5-F2 LIGHT: LH FCS SPEED BK "MAN"
// 6-F2 LIGHT: LH FCS PITCH "CSS"
// 7-F2 LIGHT: LH FCS ROLL/YAW "CSS"
inline constexpr unsigned int SCP_FF2_IOM10_CH0_DATA = 0x00150;// INTEGER SINGLE
// 0-F7 LIGHT: L MPS RED STATUS
inline constexpr unsigned int SCP_FF2_IOM10_CH1_DATA = 0x00151;// INTEGER SINGLE

// MDM FF3 output
// 0-F7 LIGHT: R MPS AMBER STATUS
// 7-F6 LIGHT B: RCS CMD "ROLL LEFT"
// 8-F6 LIGHT B: RCS CMD "ROLL RIGHT"
// 9-F6 LIGHT B: RCS CMD "YAW LEFT"
// 10-F6 LIGHT B: RCS CMD "YAW RIGHT"
// 11-F6 LIGHT B: RCS CMD "PITCH UP"
// 12-F6 LIGHT B: RCS CMD "PITCH DOWN"
// 13-A6 LIGHT: AFT DAP CONTROL "AUTO"
// 14-A6 LIGHT: AFT DAP SELECT "A"
// 15-A6 LIGHT: AFT DAP RCS JETS "NORM"
inline constexpr unsigned int SCP_FF3_IOM2_CH1_DATA = 0x00152;// INTEGER SINGLE
// 3-A6 LIGHT: AFT DAP CONTROL "MAN"
// 4-A6 LIGHT: AFT DAP SELECT "B"
// 5-A6 LIGHT: AFT DAP RCS JETS "VERN"
inline constexpr unsigned int SCP_FF3_IOM2_CH2_DATA = 0x00153;// INTEGER SINGLE
// 4-F4 LIGHT: RH FCS BODY FLAP "AUTO"
// 5-F4 LIGHT: RH FCS SPEED BK "AUTO"
// 6-F4 LIGHT: RH FCS PITCH "AUTO"
// 7-F4 LIGHT: RH FCS ROLL/YAW "AUTO"
inline constexpr unsigned int SCP_FF3_IOM10_CH0_DATA = 0x00154;// INTEGER SINGLE
// 0-F7 LIGHT: R MPS RED STATUS
// 1-A6 LIGHT: AFT MAN ROT ROLL "DISC RT"
// 2-A6 LIGHT: AFT MAN ROT ROLL "ACCEL"
// 3-A6 LIGHT: AFT MAN ROT ROLL "PULSE"
// 4-A6 LIGHT: AFT MAN ROT PITCH "DISC RT"
// 5-A6 LIGHT: AFT MAN ROT PITCH "ACCEL"
// 6-A6 LIGHT: AFT MAN ROT PITCH "PULSE"
// 7-A6 LIGHT: AFT MAN ROT YAW "DISC RT"
// 8-A6 LIGHT: AFT MAN ROT YAW "ACCEL"
// 9-A6 LIGHT: AFT MAN ROT YAW "PULSE"
// 10-A6 LIGHT: AFT MAN TRANS X "NORM"
// 11-A6 LIGHT: AFT MAN TRANS X "PULSE"
// 12-A6 LIGHT: AFT MAN TRANS X "LVLH"
// 13-A6 LIGHT: AFT MAN TRANS Y "NORM"
// 14-A6 LIGHT: AFT MAN TRANS Y "PULSE"
// 15-A6 LIGHT: AFT MAN TRANS Y "LOW Z"
inline constexpr unsigned int SCP_FF3_IOM10_CH1_DATA = 0x00155;// INTEGER SINGLE
// 0-A6 LIGHT: AFT MAN TRANS Z "NORM"
// 1-A6 LIGHT: AFT MAN TRANS Z "PULSE"
// 2-A6 LIGHT: AFT MAN TRANS Z "HIGH"
inline constexpr unsigned int SCP_FF3_IOM10_CH2_DATA = 0x00156;// INTEGER SINGLE

// MDM FF4 output
// 0-FWD EVENT TIMER: LIFT OFF TIMER_RESET
inline constexpr unsigned int SCP_FF4_IOM5_CH1_DATA = 0x00157;// INTEGER SINGLE
// 4-F4 LIGHT: RH FCS BODY FLAP "MAN"
// 5-F4 LIGHT: RH FCS SPEED BK "MAN"
// 6-F4 LIGHT: RH FCS PITCH "CSS"
// 7-F4 LIGHT: RH FCS ROLL/YAW "CSS"
inline constexpr unsigned int SCP_FF4_IOM10_CH0_DATA = 0x00158;// INTEGER SINGLE

// Radar Altimeter
inline constexpr unsigned int SCP_RA_DATA_CDR_SEL = 0x00159;// INTEGER SINGLE
inline constexpr unsigned int SCP_RA_VALIDITY_CDR_SEL = 0x0015a;// INTEGER SINGLE
inline constexpr unsigned int SCP_RA_DATA_PLT_SEL = 0x0015b;// INTEGER SINGLE
inline constexpr unsigned int SCP_RA_VALIDITY_PLT_SEL = 0x0015c;// INTEGER SINGLE

// DAP PBIs light command
// forward
inline constexpr unsigned int SCP_FWD_DAP_SELECT_A_LT = 0x0015d;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_SELECT_B_LT = 0x0015e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_AUTO_LT = 0x0015f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN_INRTL_LT = 0x00160;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN_LVLH_LT = 0x00161;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN_FREE_DFT_LT = 0x00162;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_BLANK_LT = 0x00163;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_X_NORM_LT = 0x00164;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_X_PULSE_LT = 0x00165;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_LOW_Z_LT = 0x00166;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Y_NORM_LT = 0x00167;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Y_PULSE_LT = 0x00168;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Z_HIGH_LT = 0x00169;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Z_NORM_LT = 0x0016a;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Z_PULSE_LT = 0x0016b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_JETS_NORM_LT = 0x0016c;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_ROLL_DISC_LT = 0x0016d;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_ROLL_PULSE_LT = 0x0016e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ALT_PRCS_MODE_LT = 0x0016f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_PITCH_DISC_LT = 0x00170;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_PITCH_PULSE_LT = 0x00171;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_JETS_VERN_LT = 0x00172;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_YAW_DISC_LT = 0x00173;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_YAW_PULSE_LT = 0x00174;// INTEGER SINGLE
// aft
inline constexpr unsigned int SCP_AFT_DAP_SELECT_A_LT = 0x00175;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_SELECT_B_LT = 0x00176;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_AUTO_LT = 0x00177;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN_INRTL_LT = 0x00178;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN_LVLH_LT = 0x00179;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN_FREE_DFT_LT = 0x0017a;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_BLANK_LT = 0x0017b;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_X_NORM_LT = 0x0017c;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_X_PULSE_LT = 0x0017d;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_LOW_Z_LT = 0x0017e;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Y_NORM_LT = 0x0017f;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Y_PULSE_LT = 0x00180;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Z_HIGH_LT = 0x00181;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Z_NORM_LT = 0x00182;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Z_PULSE_LT = 0x00183;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_JETS_NORM_LT = 0x00184;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_ROLL_DISC_LT = 0x00185;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_ROLL_PULSE_LT = 0x00186;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ALT_PRCS_MODE_LT = 0x00187;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_PITCH_DISC_LT = 0x00188;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_PITCH_PULSE_LT = 0x00189;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_JETS_VERN_LT = 0x0018a;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_YAW_DISC_LT = 0x0018b;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_YAW_PULSE_LT = 0x0018c;// INTEGER SINGLE

// TAEM parameters
// maximum shuttle orbiter weight [slugs]
inline constexpr unsigned int SCP_WT_GS1 = 0x0018d;// SCALAR DOUBLE
// minimum RPRED to issue OHALRT [ft]
inline constexpr unsigned int SCP_RMOH = 0x0018f;// SCALAR DOUBLE
// HAC turn angle [deg]
inline constexpr unsigned int SCP_PSHA = 0x00191;// SCALAR DOUBLE
// HAC radius [ft]
inline constexpr unsigned int SCP_RTURN = 0x00193;// SCALAR DOUBLE
// R/L cone indicator [1]
inline constexpr unsigned int SCP_YSGN = 0x00195;// SCALAR DOUBLE
// PSHA reset value [deg]
inline constexpr unsigned int SCP_PSHARS = 0x00197;// SCALAR DOUBLE
// initial HAC spiral turn radius on final [ft]
inline constexpr unsigned int SCP_RF0 = 0x00199;// SCALAR DOUBLE
// linear term in spiral radius eqn. [ft/deg]
inline constexpr unsigned int SCP_R1 = 0x0019b;// SCALAR DOUBLE
// quadratic term in spiral radius eqn. [ft/deg]
inline constexpr unsigned int SCP_R2 = 0x0019d;// SCALAR DOUBLE

// Autoland parameters
// pullup circle radius (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_AL_R = 0x0019f;// MATRIX(2,2) DOUBLE
// pullup circle center (x) (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_X_K = 0x001a7;// MATRIX(2,2) DOUBLE
// pullup circle center (h) (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_H_K = 0x001af;// MATRIX(2,2) DOUBLE
// exponential/circle tangency range (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_X_EXP = 0x001b7;// MATRIX(2,2) DOUBLE
// exponential decay (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_H_DECAY = 0x001bf;// MATRIX(2,2) DOUBLE
// exponential decay factor [1]
inline constexpr unsigned int SCP_SIGMA = 0x001c7;// SCALAR DOUBLE
// steep glideslop angle (indexed by IGS) [deg]
inline constexpr unsigned int SCP_GAMMA_REF_1 = 0x001c9;// VECTOR(2) DOUBLE
// shallow glideslop angle [deg]
inline constexpr unsigned int SCP_GAMMA_REF_2 = 0x001cd;// SCALAR DOUBLE
// steep glide slope aim point (indexed by IGI) [ft]
inline constexpr unsigned int SCP_X_ZERO = 0x001cf;// VECTOR(2) DOUBLE
// shallow glide slope aim point [ft]
inline constexpr unsigned int SCP_X_AIM = 0x001d3;// SCALAR DOUBLE
// open-loop pull-up altitude [ft]
inline constexpr unsigned int SCP_H_FLARE = 0x001d5;// SCALAR DOUBLE
// closed-loop pull-up altitude [ft]
inline constexpr unsigned int SCP_H_CLOOP = 0x001d7;// SCALAR DOUBLE

// runway approach mode (1-overhead; 2-strait-in)
inline constexpr unsigned int SCP_OVHD = 0x001d9;// INTEGER SINGLE
// glide slope (1-light; 2-heavy)
inline constexpr unsigned int SCP_IGS = 0x001da;// INTEGER SINGLE
// aimpoint (1-nom; 2-close-in)
inline constexpr unsigned int SCP_IGI = 0x001db;// INTEGER SINGLE
// runway ID (1-pri; 2-sec)
inline constexpr unsigned int SCP_RWID = 0x001dc;// INTEGER SINGLE
// previous runway ID (1-pri; 2-sec)
inline constexpr unsigned int SCP_RWID0 = 0x001dd;// INTEGER SINGLE
// landing site ID [1,45]
inline constexpr unsigned int SCP_LSID = 0x001de;// INTEGER SINGLE

// speedbrake logic select (1-nom; 2-short; 3-ELS)
inline constexpr unsigned int SCP_SB_SEL = 0x001df;// INTEGER SINGLE

// pri runway name
inline constexpr unsigned int SCP_PRI_ID = 0x001e0;// CHARACTER(5)
// pri runway heading [deg]
inline constexpr unsigned int SCP_PRI_HDG = 0x001e5;// SCALAR DOUBLE
// pri runway pos (greenwich=ECEF) [ft]
inline constexpr unsigned int SCP_PRI_POS = 0x001e7;// VECTOR(3) DOUBLE
// pri greenwich(=ECEF)-to-runway matrix [ft]
inline constexpr unsigned int SCP_PRI_G2R = 0x001ed;// MATRIX(3,3) DOUBLE
// pri runway length [ft]
inline constexpr unsigned int SCP_PRI_LEN = 0x001ff;// INTEGER SINGLE
// sec runway name
inline constexpr unsigned int SCP_SEC_ID = 0x00200;// CHARACTER(5)
// sec runway heading [deg]
inline constexpr unsigned int SCP_SEC_HDG = 0x00205;// SCALAR DOUBLE
// sec runway pos (greenwich=ECEF) [ft]
inline constexpr unsigned int SCP_SEC_POS = 0x00207;// VECTOR(3) DOUBLE
// sec greenwich(=ECEF)-to-runway matrix [ft]
inline constexpr unsigned int SCP_SEC_G2R = 0x0020d;// MATRIX(3,3) DOUBLE
// sec runway length [ft]
inline constexpr unsigned int SCP_SEC_LEN = 0x0021f;// INTEGER SINGLE

// Landing SOP
inline constexpr unsigned int SCP_WOWLON = 0x00220;// INTEGER SINGLE
inline constexpr unsigned int SCP_FLATTURN = 0x00221;// INTEGER SINGLE
inline constexpr unsigned int SCP_ROLLOUT = 0x00222;// INTEGER SINGLE
inline constexpr unsigned int SCP_GSENBL = 0x00223;// INTEGER SINGLE
inline constexpr unsigned int SCP_HUD_WOWLON = 0x00224;// INTEGER SINGLE
inline constexpr unsigned int SCP_HUD_ROLLOUT = 0x00225;// INTEGER SINGLE

// Aerojet DAP FCS
// AerojetDAP FCS pitch control (1-AUTO; 2-CSS)
inline constexpr unsigned int SCP_AEROJET_FCS_PITCH = 0x00226;// INTEGER SINGLE
// AerojetDAP FCS roll control (1-AUTO; 2-CSS)
inline constexpr unsigned int SCP_AEROJET_FCS_ROLL = 0x00227;// INTEGER SINGLE
// AerojetDAP FCS speedbrake control (1-AUTO; 2-CDR; 3-PLT)
inline constexpr unsigned int SCP_AEROJET_FCS_SB = 0x00228;// INTEGER SINGLE
// AerojetDAP body flap control (1-AUTO; 2-CSS)
inline constexpr unsigned int SCP_AEROJET_FCS_BF = 0x00229;// INTEGER SINGLE
// number of RCS roll jets to fire (+right, -left) [1]
inline constexpr unsigned int SCP_UXCMD = 0x0022a;// INTEGER SINGLE
// number of RCS pitch jets to fire (+up, -down) [1]
inline constexpr unsigned int SCP_UYCMD = 0x0022b;// INTEGER SINGLE
// number of RCS yaw jets to fire (+right, -left) [1]
inline constexpr unsigned int SCP_UZCMD = 0x0022c;// INTEGER SINGLE
// aileron trim [deg]
inline constexpr unsigned int SCP_DATRIM = 0x0022d;// SCALAR DOUBLE
// rudder trim [deg]
inline constexpr unsigned int SCP_DRTRIM = 0x0022f;// SCALAR DOUBLE
// NY trim [g]
inline constexpr unsigned int SCP_DRTI = 0x00231;// SCALAR DOUBLE
// NZ error [g]
inline constexpr unsigned int SCP_NZERR = 0x00233;// SCALAR DOUBLE
// bank error [deg]
inline constexpr unsigned int SCP_BANKERR = 0x00235;// SCALAR DOUBLE
// wraparound DAP mode (0=INH, 1=ENA, 2=ACT)
inline constexpr unsigned int SCP_WRAP = 0x00237;// INTEGER SINGLE
// elevator command [deg]
inline constexpr unsigned int SCP_DECC = 0x00238;// SCALAR DOUBLE
// aileron command [deg]
inline constexpr unsigned int SCP_DAC = 0x0023a;// SCALAR DOUBLE
// rudder command [deg]
inline constexpr unsigned int SCP_DRC = 0x0023c;// SCALAR DOUBLE
// speedbrake command [deg]
inline constexpr unsigned int SCP_DSBC = 0x0023e;// SCALAR DOUBLE
// NWS command [deg]
inline constexpr unsigned int SCP_DNWC = 0x00240;// SCALAR DOUBLE
// Entry Mode switch "Low Gain" selected
inline constexpr unsigned int SCP_SEL_L_GAIN = 0x00242;// INTEGER SINGLE
// Entry Mode switch "No Yaw Jet" selected
inline constexpr unsigned int SCP_SEL_NO_Y_JET = 0x00243;// INTEGER SINGLE
// Entry Mode switch override
inline constexpr unsigned int SCP_ENTRY_SW_OVERRIDE = 0x00244;// INTEGER SINGLE

// A/L UPP
// geodetic altitude of vehicle center of mass above rw [ft]
inline constexpr unsigned int SCP_H = 0x00245;// SCALAR DOUBLE
// negative z component of velocity in topodetic coordinates [fps]
inline constexpr unsigned int SCP_HDOT = 0x00247;// SCALAR DOUBLE
// true airspeed [fps]
inline constexpr unsigned int SCP_V_T = 0x00249;// SCALAR DOUBLE
// equivalent? airspeed [fps]
inline constexpr unsigned int SCP_V_I = 0x0024b;// SCALAR DOUBLE
// equivalent airspeed [knots]
inline constexpr unsigned int SCP_KEAS = 0x0024d;// SCALAR DOUBLE
// topodetic horizontal component of earth relative velocity [fps]
inline constexpr unsigned int SCP_VG = 0x0024f;// SCALAR DOUBLE
// vehicle position in runway coordinates [ft]
inline constexpr unsigned int SCP_X = 0x00251;// SCALAR DOUBLE
inline constexpr unsigned int SCP_Y = 0x00253;// SCALAR DOUBLE
inline constexpr unsigned int SCP_Z = 0x00255;// SCALAR DOUBLE
// vehicle velocity in runway coordinates [fps]
inline constexpr unsigned int SCP_XDOT = 0x00257;// SCALAR DOUBLE
inline constexpr unsigned int SCP_YDOT = 0x00259;// SCALAR DOUBLE
// heading [deg]
inline constexpr unsigned int SCP_HDG = 0x0025b;// SCALAR DOUBLE
// topodetic earth relative flight-path angle [deg]
inline constexpr unsigned int SCP_GAMMA = 0x0025d;// SCALAR DOUBLE
// roll [deg]
inline constexpr unsigned int SCP_PHI = 0x0025f;// SCALAR DOUBLE
// cosine of body roll euler angle [1]
inline constexpr unsigned int SCP_COSPHI = 0x00261;// SCALAR DOUBLE
// sine of body roll euler angle [1]
inline constexpr unsigned int SCP_SINPHI = 0x00263;// SCALAR DOUBLE
// tangent of body roll euler angle [1]
inline constexpr unsigned int SCP_TANPHI = 0x00265;// SCALAR DOUBLE
// cosine of angle of attack [1]
inline constexpr unsigned int SCP_COSALF = 0x00267;// SCALAR DOUBLE
// sine of angle of attack [1]
inline constexpr unsigned int SCP_SINALF = 0x00269;// SCALAR DOUBLE
// pitch [deg]
inline constexpr unsigned int SCP_THETA = 0x0026b;// SCALAR DOUBLE
// cosine of theta [1]
inline constexpr unsigned int SCP_COSTH = 0x0026d;// SCALAR DOUBLE
// sine of theta [1]
inline constexpr unsigned int SCP_SINTH = 0x0026f;// SCALAR DOUBLE
// angle-of-attack [deg]
inline constexpr unsigned int SCP_ALPHA = 0x00271;// SCALAR DOUBLE
// sideslip [deg]
inline constexpr unsigned int SCP_BETA = 0x00273;// SCALAR DOUBLE
// dynamic pressure [psf]
inline constexpr unsigned int SCP_QBAR = 0x00275;// SCALAR DOUBLE
// lateral acceleration [g]
inline constexpr unsigned int SCP_NY = 0x00277;// SCALAR DOUBLE
// normal acceleration [g]
inline constexpr unsigned int SCP_NZ = 0x00279;// SCALAR DOUBLE
// orbiter mass [slugs]
inline constexpr unsigned int SCP_WEIGHT = 0x0027b;// SCALAR DOUBLE
// body roll rate [deg/s]
inline constexpr unsigned int SCP_P = 0x0027d;// SCALAR DOUBLE
// body pitch rate [deg/s]
inline constexpr unsigned int SCP_Q = 0x0027f;// SCALAR DOUBLE
// body yaw rate [deg/s]
inline constexpr unsigned int SCP_R = 0x00281;// SCALAR DOUBLE

// TAEM UPP
// mach number [1]
inline constexpr unsigned int SCP_MACH = 0x00283;// SCALAR DOUBLE
// course with respect to centerline [deg]
inline constexpr unsigned int SCP_PSD = 0x00285;// SCALAR DOUBLE

// Entry UPP
// vehicle position in ECEF [ft]
inline constexpr unsigned int SCP_ECEF_POS = 0x00287;// VECTOR(3) DOUBLE
// vehicle velocity in ECEF [fps]
inline constexpr unsigned int SCP_ECEF_VEL = 0x0028d;// VECTOR(3) DOUBLE
// current relative velocity [fps]
inline constexpr unsigned int SCP_VE = 0x00293;// SCALAR DOUBLE
// current inertial velocity [fps]
inline constexpr unsigned int SCP_VI = 0x00295;// SCALAR DOUBLE
// current drag acceleration [fps^2]
inline constexpr unsigned int SCP_DRAG = 0x00297;// SCALAR DOUBLE
// current lift/drag ratio [1]
inline constexpr unsigned int SCP_LOD = 0x00299;// SCALAR DOUBLE
// current load factor [fps^2]
inline constexpr unsigned int SCP_XLFAC = 0x0029b;// SCALAR DOUBLE

// EGRT output
// azimuth error [rad]
inline constexpr unsigned int SCP_DELAZ = 0x0029d;// SCALAR DOUBLE
// range to target [NM]
inline constexpr unsigned int SCP_TRANG = 0x0029f;// SCALAR DOUBLE

// Autoland guidance output
// autoland phase counter
inline constexpr unsigned int SCP_PMODE = 0x002a1;// INTEGER SINGLE
// FSGS phase counter
inline constexpr unsigned int SCP_FMODE = 0x002a2;// INTEGER SINGLE
// autoland NZ command [g]
inline constexpr unsigned int SCP_NZ_CMD = 0x002a3;// SCALAR DOUBLE
// autoland roll angle command [deg]
inline constexpr unsigned int SCP_PHIC_AL = 0x002a5;// SCALAR DOUBLE
// autoland yaw rate command post WOWLON
inline constexpr unsigned int SCP_RC = 0x002a7;// SCALAR DOUBLE
// autoland speedbrake command [deg]
inline constexpr unsigned int SCP_DSBC_AL = 0x002a9;// SCALAR DOUBLE
// body flap retract command
inline constexpr unsigned int SCP_RETRACT_BF = 0x002ab;// INTEGER SINGLE
// altitude error [ft]
inline constexpr unsigned int SCP_HERR = 0x002ac;// SCALAR DOUBLE

// TAEM guidance output
// heading error to HAC tangency [deg]
inline constexpr unsigned int SCP_DPSAC = 0x002ae;// SCALAR DOUBLE
// predicted range to rw [ft]
inline constexpr unsigned int SCP_RPRED = 0x002b0;// SCALAR DOUBLE
// commanded body normal load factor increment from equilibrium [g]
inline constexpr unsigned int SCP_NZC = 0x002b2;// SCALAR DOUBLE
// speedbrake angle command (hinge line) [deg]
inline constexpr unsigned int SCP_DSBC_AT = 0x002b4;// SCALAR DOUBLE
// roll angle command
inline constexpr unsigned int SCP_PHIC_AT = 0x002b6;// SCALAR DOUBLE
// minimum entry point flag
inline constexpr unsigned int SCP_MEP = 0x002b8;// INTEGER SINGLE
// TAEM phase counter [1]
inline constexpr unsigned int SCP_IPHASE = 0x002b9;// INTEGER SINGLE
// TAEM end flag
inline constexpr unsigned int SCP_TG_END = 0x002ba;// INTEGER SINGLE
// current HAC final size [ft]
inline constexpr unsigned int SCP_RF = 0x002bb;// SCALAR DOUBLE
// HAC X position [ft]
inline constexpr unsigned int SCP_XHAC = 0x002bd;// SCALAR DOUBLE
// distance from OV to HAC center [ft]
inline constexpr unsigned int SCP_RCIR = 0x002bf;// SCALAR DOUBLE
// energy per unit weight [ft]
inline constexpr unsigned int SCP_EOW = 0x002c1;// SCALAR DOUBLE
// reference energy [ft]
inline constexpr unsigned int SCP_EN = 0x002c3;// SCALAR DOUBLE
// E/W to start S-turn [ft]
inline constexpr unsigned int SCP_ES = 0x002c5;// SCALAR DOUBLE
// E/W to switch to MEP [ft]
inline constexpr unsigned int SCP_EMEP = 0x002c7;// SCALAR DOUBLE
// E/W to downmode to STRN [ft]
inline constexpr unsigned int SCP_EMOH = 0x002c9;// SCALAR DOUBLE
// altitude error from reference profile [ft]
inline constexpr unsigned int SCP_HERROR = 0x002cb;// SCALAR DOUBLE
// heading to HAC center [deg]
inline constexpr unsigned int SCP_PSC = 0x002cd;// SCALAR DOUBLE
// estimated time to HAC [sec]
inline constexpr unsigned int SCP_P2TRNT = 0x002cf;// SCALAR DOUBLE

// Entry guidance output
// angle-of-attack command [deg]
inline constexpr unsigned int SCP_ALPCMD = 0x002d1;// SCALAR DOUBLE
// drag reference [fps^2]
inline constexpr unsigned int SCP_DREFP = 0x002d3;// SCALAR DOUBLE
// roll angle command about body axis [deg]
inline constexpr unsigned int SCP_ROLLCMD = 0x002d5;// SCALAR DOUBLE
// roll ref [deg]
inline constexpr unsigned int SCP_ROLLREF = 0x002d7;// SCALAR DOUBLE
// altitude rate reference [fps]
inline constexpr unsigned int SCP_RDTREF = 0x002d9;// SCALAR DOUBLE
// derivative of range wrt drag [NM/fps^2]
inline constexpr unsigned int SCP_DRDD = 0x002db;// SCALAR DOUBLE
// Rdot feedback term [fps]
inline constexpr unsigned int SCP_DLRDOT = 0x002dd;// SCALAR DOUBLE
// maximum heading error absolute value [rad]
inline constexpr unsigned int SCP_YL = 0x002df;// SCALAR DOUBLE
// scheduled angle of attack [deg]
inline constexpr unsigned int SCP_ACMD1 = 0x002e1;// SCALAR DOUBLE
// entry guidance subphase counter
inline constexpr unsigned int SCP_ISLECT = 0x002e3;// INTEGER SINGLE
// Entry guidance end flag
inline constexpr unsigned int SCP_EG_END = 0x002e4;// INTEGER SINGLE

// aerosurface position feedback
// left outboard elevon pos [deg]
inline constexpr unsigned int SCP_LOB_ELVN_POS_FDBK = 0x002e5;// SCALAR DOUBLE
// left inboard elevon pos [deg]
inline constexpr unsigned int SCP_LIB_ELVN_POS_FDBK = 0x002e7;// SCALAR DOUBLE
// right inboard elevon pos [deg]
inline constexpr unsigned int SCP_RIB_ELVN_POS_FDBK = 0x002e9;// SCALAR DOUBLE
// right outboard elevon pos [deg]
inline constexpr unsigned int SCP_ROB_ELVN_POS_FDBK = 0x002eb;// SCALAR DOUBLE
// elevator pos [deg]
inline constexpr unsigned int SCP_DEFB = 0x002ed;// SCALAR DOUBLE
// aileron pos [deg]
inline constexpr unsigned int SCP_DAFB = 0x002ef;// SCALAR DOUBLE
// body flap pos [deg]
inline constexpr unsigned int SCP_DBFOFB = 0x002f1;// SCALAR DOUBLE
// rudder pos [deg]
inline constexpr unsigned int SCP_DRFB = 0x002f3;// SCALAR DOUBLE
// Speedbrake pos [deg]
inline constexpr unsigned int SCP_DSBFB_DEG = 0x002f5;// SCALAR DOUBLE
// Speedbrake pos [%]
inline constexpr unsigned int SCP_DSBFB_PCT = 0x002f7;// SCALAR DOUBLE
// speedbrake increment [deg]
inline constexpr unsigned int SCP_DSBPC = 0x002f9;// SCALAR DOUBLE

// Aerosurface command
// left outboard elevon command [deg]
inline constexpr unsigned int SCP_ELOC = 0x002fb;// SCALAR DOUBLE
// left inboard elevon command [deg]
inline constexpr unsigned int SCP_ELIC = 0x002fd;// SCALAR DOUBLE
// right inboard elevon command [deg]
inline constexpr unsigned int SCP_ERIC = 0x002ff;// SCALAR DOUBLE
// right outboard elevon command [deg]
inline constexpr unsigned int SCP_EROC = 0x00301;// SCALAR DOUBLE
// body flap command [deg]
inline constexpr unsigned int SCP_DBFRC = 0x00303;// SCALAR DOUBLE
// rudder command [deg]
inline constexpr unsigned int SCP_RUDDER_CMD = 0x00305;// SCALAR DOUBLE
// speedbrake command [deg]
inline constexpr unsigned int SCP_SPEED_BRAKE_CMD = 0x00307;// SCALAR DOUBLE

// Speedbrake AUTO command [deg]
inline constexpr unsigned int SCP_SB_AUTO_CMD = 0x00309;// SCALAR DOUBLE

// HUD
// runway to go [ft]
inline constexpr unsigned int SCP_RWTOGO = 0x0030b;// SCALAR DOUBLE
// max deceleration [fps^2]
inline constexpr unsigned int SCP_HUDMAXDECEL = 0x0030d;// SCALAR DOUBLE
// speedbrake delta minimum velocity [fps]
inline constexpr unsigned int SCP_SBDMN = 0x0030f;// SCALAR DOUBLE
// speedbrake delta maximum velocity [fps]
inline constexpr unsigned int SCP_SBDMX = 0x00311;// SCALAR DOUBLE
// speedbrake delta limit [deg]
inline constexpr unsigned int SCP_SBDLIM = 0x00313;// SCALAR DOUBLE

// Trim Switch positions
inline constexpr unsigned int SCP_LH_RHC_TRIM_INHIBIT = 0x00315;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_TRIM_INHIBIT = 0x00316;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_PLUS_PITCH_TRIM = 0x00317;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_MINUS_PITCH_TRIM = 0x00318;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_PLUS_ROLL_TRIM = 0x00319;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_MINUS_ROLL_TRIM = 0x0031a;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_PLUS_PITCH_TRIM = 0x0031b;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_MINUS_PITCH_TRIM = 0x0031c;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_PLUS_ROLL_TRIM = 0x0031d;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_MINUS_ROLL_TRIM = 0x0031e;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_PLUS_PITCH_TRIM = 0x0031f;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_MINUS_PITCH_TRIM = 0x00320;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_PLUS_ROLL_TRIM = 0x00321;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_MINUS_ROLL_TRIM = 0x00322;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_PLUS_YAW_TRIM = 0x00323;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_MINUS_YAW_TRIM = 0x00324;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_PLUS_PITCH_TRIM = 0x00325;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_MINUS_PITCH_TRIM = 0x00326;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_PLUS_ROLL_TRIM = 0x00327;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_MINUS_ROLL_TRIM = 0x00328;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_PLUS_YAW_TRIM = 0x00329;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_MINUS_YAW_TRIM = 0x0032a;// INTEGER SINGLE
inline constexpr unsigned int SCP_DETM_RHC = 0x0032b;// INTEGER SINGLE
inline constexpr unsigned int SCP_DATM_RHC = 0x0032c;// INTEGER SINGLE
inline constexpr unsigned int SCP_DETM_PAN = 0x0032d;// INTEGER SINGLE
inline constexpr unsigned int SCP_DATM_PAN = 0x0032e;// INTEGER SINGLE
inline constexpr unsigned int SCP_DRT = 0x0032f;// INTEGER SINGLE

// Body Flap Switch positions
inline constexpr unsigned int SCP_LH_BODY_FLAP_UP = 0x00330;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_BODY_FLAP_DOWN = 0x00331;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_BODY_FLAP_UP = 0x00332;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_BODY_FLAP_DOWN = 0x00333;// INTEGER SINGLE
inline constexpr unsigned int SCP_DBFMAN = 0x00334;// INTEGER SINGLE

// MPS switches
inline constexpr unsigned int SCP_MPS_BACKUP_LH2_PRPLT_DUMP_START = 0x00335;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_BACKUP_LH2_PRPLT_DUMP_STOP = 0x00336;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_PRPLT_DUMP_SEQUENCE_START = 0x00337;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_PRPLT_DUMP_SEQUENCE_STOP = 0x00338;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ENG_LIMIT_CONTROL_ENABLE = 0x00339;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ENG_LIMIT_CONTROL_INHIBIT = 0x0033a;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ENG_LIMIT_CONTROL_AUTO = 0x0033b;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ME_1_SHUTDOWN_CMD = 0x0033c;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ME_2_SHUTDOWN_CMD = 0x0033d;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ME_3_SHUTDOWN_CMD = 0x0033e;// INTEGER SINGLE

// Separation switches
inline constexpr unsigned int SCP_SRB_SEPARATION_AUTO_CMD = 0x0033f;// INTEGER SINGLE
inline constexpr unsigned int SCP_SRB_SEPARATION_MANUAL_AUTO_ENABLE_CMD = 0x00340;// INTEGER SINGLE
inline constexpr unsigned int SCP_SRB_SEPARATION_INITIATE_CMD = 0x00341;// INTEGER SINGLE
inline constexpr unsigned int SCP_ET_SEPARATION_MANUAL_ENABLE_CMD = 0x00342;// INTEGER SINGLE
inline constexpr unsigned int SCP_ET_SEPARATION_INITIATE_CMD = 0x00343;// INTEGER SINGLE
inline constexpr unsigned int SCP_ET_SEPARATION_AUTO_CMD = 0x00344;// INTEGER SINGLE

// (0-"-Z"; 1-"-X")
inline constexpr unsigned int SCP_SENSE_SWITCH = 0x00345;// INTEGER SINGLE

// FCS PBIs
inline constexpr unsigned int SCP_FCS_LH_PITCH_AUTO_MODE = 0x00346;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_LH_PITCH_CSS_MODE = 0x00347;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_LH_RY_AUTO_MODE = 0x00348;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_LH_RY_CSS_MODE = 0x00349;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_BODY_FLAP_AUTO_MANUAL = 0x0034a;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_SPD_BK_THROT_AUTO_MAN = 0x0034b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_PITCH_AUTO_MODE = 0x0034c;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_PITCH_CSS_MODE = 0x0034d;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_RY_AUTO_MODE = 0x0034e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_RY_CSS_MODE = 0x0034f;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_BODY_FLAP_AUTO_MANUAL = 0x00350;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_SPD_BK_THROT_AUTO_MAN = 0x00351;// INTEGER SINGLE

// Orbit DAP PBIs
inline constexpr unsigned int SCP_FWD_DAP_SELECT_A = 0x00352;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_SELECT_B = 0x00353;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_AUTO = 0x00354;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN = 0x00355;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_OPTIONS_NORM = 0x00356;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_OPTIONS_VERNIER = 0x00357;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_ROLL_DISC_RATE = 0x00358;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_ROLL_ACCEL = 0x00359;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_ROLL_PULSE = 0x0035a;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_PITCH_DISC_RATE = 0x0035b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_PITCH_ACCEL = 0x0035c;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_PITCH_PULSE = 0x0035d;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_YAW_DISC_RATE = 0x0035e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_YAW_ACCEL = 0x0035f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_YAW_PULSE = 0x00360;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_X_NORM = 0x00361;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_X_PULSE = 0x00362;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_X_LVLH = 0x00363;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Y_NORM = 0x00364;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Y_PULSE = 0x00365;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Y_LOW_Z = 0x00366;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Z_NORM = 0x00367;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Z_PULSE = 0x00368;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Z_HIGH = 0x00369;// INTEGER SINGLE

inline constexpr unsigned int SCP_AFT_DAP_SELECT_A = 0x0036a;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_SELECT_B = 0x0036b;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_AUTO = 0x0036c;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN = 0x0036d;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_OPTIONS_NORM = 0x0036e;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_OPTIONS_VERNIER = 0x0036f;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_ROLL_DISC_RATE = 0x00370;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_ROLL_ACCEL = 0x00371;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_ROLL_PULSE = 0x00372;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_PITCH_DISC_RATE = 0x00373;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_PITCH_ACCEL = 0x00374;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_PITCH_PULSE = 0x00375;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_YAW_DISC_RATE = 0x00376;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_YAW_ACCEL = 0x00377;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_YAW_PULSE = 0x00378;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_X_NORM = 0x00379;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_X_PULSE = 0x0037a;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_X_LVLH = 0x0037b;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Y_NORM = 0x0037c;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Y_PULSE = 0x0037d;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Y_LOW_Z = 0x0037e;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Z_NORM = 0x0037f;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Z_PULSE = 0x00380;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Z_HIGH = 0x00381;// INTEGER SINGLE

// Ascent
inline constexpr unsigned int SCP_KMIN = 0x00382;// INTEGER SINGLE
inline constexpr unsigned int SCP_KMAX = 0x00383;// INTEGER SINGLE
// (0-KMAX_NOM; 1-KMAX_SECONDARY; 2-KMAX_ABORT)
inline constexpr unsigned int SCP_KMAX_SEL = 0x00384;// INTEGER SINGLE
// MPS dump complete flag
inline constexpr unsigned int SCP_MPS_LO2_DUMP_STOP = 0x00385;// INTEGER SINGLE

// --------------------------------
// temporary SM section
// --------------------------------

// MDM OF1 input
// 0-PL3_1B_REL
// 1-PL3_1B_LAT
// 2-PL3_1B_RDY
// 3-PL2_2B_REL
// 4-PL2_2B_LAT
// 5-PL2_2B_RDY
// 6-PL3_2B_REL
// 7-PL3_2B_LAT
// 8-PL3_2B_RDY
// 9-PL2_3B_REL
// 10-PL2_3B_LAT
// 11-PL2_3B_RDY
// 12-PL3_3B_REL
// 13-PL3_3B_LAT
// 14-PL3_3B_RDY
inline constexpr unsigned int SCP_OF1_IOM14_CH0_DATA = 0x00386;// INTEGER SINGLE
// 0-PL2_4B_REL
// 1-PL2_4B_LAT
// 2-PL2_4B_RDY
// 3-PL3_4B_REL
// 4-PL3_4B_LAT
// 5-PL3_4B_RDY
// 6-PL2_5B_REL
// 7-PL2_5B_LAT
// 8-PL2_5B_RDY
// 9-PL3_5B_REL
// 10-PL3_5B_LAT
// 11-PL3_5B_RDY
inline constexpr unsigned int SCP_OF1_IOM14_CH1_DATA = 0x00387;// INTEGER SINGLE

// MDM OF2 input
// 0-PL3_1A_REL
// 1-PL3_1A_LAT
// 2-PL3_1A_RDY
// 3-PL1_1B_REL
// 4-PL1_1B_LAT
// 5-PL1_1B_RDY
// 6-PL2_1B_REL
// 7-PL2_1B_LAT
// 8-PL2_1B_RDY
// 9-PL3_2A_REL
// 10-PL3_2A_LAT
// 11-PL3_2A_RDY
// 12-PL1_2B_REL
// 13-PL1_2B_LAT
// 14-PL1_2B_RDY
inline constexpr unsigned int SCP_OF2_IOM14_CH0_DATA = 0x00388;// INTEGER SINGLE
// 0-PL3_3A_REL
// 1-PL3_3A_LAT
// 2-PL3_3A_RDY
// 3-PL1_3B_REL
// 4-PL1_3B_LAT
// 5-PL1_3B_RDY
// 6-PL3_4A_REL
// 7-PL3_4A_LAT
// 8-PL3_4A_RDY
// 9-PL1_4B_REL
// 10-PL1_4B_LAT
// 11-PL1_4B_RDY
// 12-PL2_5A_REL
// 13-PL2_5A_LAT
// 14-PL2_5A_RDY
inline constexpr unsigned int SCP_OF2_IOM14_CH1_DATA = 0x00389;// INTEGER SINGLE
// 0-PL3_5A_REL
// 1-PL3_5A_LAT
// 2-PL3_5A_RDY
// 3-PL1_5B_REL
// 4-PL1_5B_LAT
// 5-PL1_5B_RDY
inline constexpr unsigned int SCP_OF2_IOM14_CH2_DATA = 0x0038a;// INTEGER SINGLE

// MDM OF4 input
// 0-PL2_2A_REL
// 1-PL2_2A_LAT
// 2-PL2_2A_RDY
// 3-PL2_3A_REL
// 4-PL2_3A_LAT
// 5-PL2_3A_RDY
// 6-PL2_4A_REL
// 7-PL2_4A_LAT
// 8-PL2_4A_RDY
// 12-PLD_SEL_POS_1
// 13-PLD_SEL_POS_2
// 14-PLD_SEL_POS_3
// 15-PLD_SEL_MONITOR
inline constexpr unsigned int SCP_OF4_IOM15_CH0_DATA = 0x0038b;// INTEGER SINGLE

// MDM OA3 input
// 0-PL1_1A_REL
// 1-PL1_1A_LAT
// 2-PL1_1A_RDY
// 3-PL2_1A_REL
// 4-PL2_1A_LAT
// 5-PL2_1A_RDY
// 6-PL1_2A_REL
// 7-PL1_2A_LAT
// 8-PL1_2A_RDY
inline constexpr unsigned int SCP_OA3_IOM12_CH0_DATA = 0x0038c;// INTEGER SINGLE
// 0-PL1_3A_REL
// 1-PL1_3A_LAT
// 2-PL1_3A_RDY
// 3-PL1_4A_REL
// 4-PL1_4A_LAT
// 5-PL1_4A_RDY
// 6-PL1_5A_REL
// 7-PL1_5A_LAT
// 8-PL1_5A_RDY
inline constexpr unsigned int SCP_OA3_IOM12_CH1_DATA = 0x0038d;// INTEGER SINGLE

inline constexpr unsigned int SIMPLECOMPOOL_SIZE = 910;

#endif// _COMPOOL_H_
