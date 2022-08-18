#ifndef _COMPOOL_H_
#define _COMPOOL_H_

// ----------------------------------------------------------------
// SSV COMPOOL definition
// ----------------------------------------------------------------
// SINGLE => 16b
// DOUBLE => 32b

// INFO: SCALAR should always be DOUBLE, and implemented in C with a 32b float

// current major mode
inline constexpr unsigned int SCP_MM = 0x00000;// INTEGER SINGLE
// new major mode
inline constexpr unsigned int SCP_NEW_MM = 0x00001;// INTEGER SINGLE

// Fault input buffer
inline constexpr unsigned int SCP_FAULT_IN_IDX = 0x00002;// INTEGER SINGLE
inline constexpr unsigned int SCP_FAULT_IN_CWCLASS = 0x00003;// ARRAY(5) INTEGER SINGLE
inline constexpr unsigned int SCP_FAULT_IN_MSG = 0x00008;// ARRAY(5) CHARACTER(19)
// Fault display buffer
inline constexpr unsigned int SCP_FAULT_DISPBUF = 0x00067;// ARRAY(15) CHARACTER(43)
inline constexpr unsigned int SCP_FAULT_DISPBUF_CNT = 0x002ec;// INTEGER SINGLE
// Fault message buffer indicator
inline constexpr unsigned int SCP_FAULT_MSG_BUF_IND = 0x002ed;// INTEGER SINGLE
// Fault message line buffer
inline constexpr unsigned int SCP_FAULT_MSG_LINE = 0x002ee;// CHARACTER(43)
// Fault message line state (0 = empty, 1 = flashing, 2 = static)
inline constexpr unsigned int SCP_FAULT_MSG_LINE_STATE = 0x00319;// INTEGER SINGLE
// Illegal Entry indication for each CRT
inline constexpr unsigned int SCP_ILLEGAL_ENTRY_FAULT = 0x0031a;// INTEGER SINGLE

inline constexpr unsigned int SCP_ACK_KEY = 0x0031b;// INTEGER SINGLE
inline constexpr unsigned int SCP_MSGRESET_KEY = 0x0031c;// INTEGER SINGLE

// duration of SM tone [s]
inline constexpr unsigned int SCP_SM_TONE_DURATION = 0x0031d;// INTEGER SINGLE

// outputs to EIUs
inline constexpr unsigned int SCP_EIU_1_CMD = 0x0031e;// INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_2_CMD = 0x0031f;// INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_3_CMD = 0x00320;// INTEGER SINGLE

// inputs from EIUs
inline constexpr unsigned int SCP_EIU_1_PRIDATA = 0x00321;// ARRAY(32) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_2_PRIDATA = 0x00341;// ARRAY(32) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_3_PRIDATA = 0x00361;// ARRAY(32) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_1_SECDATA = 0x00381;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_2_SECDATA = 0x00387;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_EIU_3_SECDATA = 0x0038d;// ARRAY(6) INTEGER SINGLE

// output to DDU-1
inline constexpr unsigned int SCP_DDU1_ADI = 0x00393;// ARRAY(14) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU1_HSI = 0x003a1;// ARRAY(10) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU1_AVVI = 0x003ab;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU1_AMI = 0x003b1;// ARRAY(6) INTEGER SINGLE

// output to DDU-2
inline constexpr unsigned int SCP_DDU2_ADI = 0x003b7;// ARRAY(14) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU2_HSI = 0x003c5;// ARRAY(10) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU2_AVVI = 0x003cf;// ARRAY(6) INTEGER SINGLE
inline constexpr unsigned int SCP_DDU2_AMI = 0x003d5;// ARRAY(6) INTEGER SINGLE

// output to HUD-1
inline constexpr unsigned int SCP_HUD1_MSG1 = 0x003db;// ARRAY(31) INTEGER SINGLE
inline constexpr unsigned int SCP_HUD1_MSG2 = 0x003fa;// ARRAY(12) INTEGER SINGLE

// output to HUD-2
inline constexpr unsigned int SCP_HUD2_MSG1 = 0x00406;// ARRAY(31) INTEGER SINGLE
inline constexpr unsigned int SCP_HUD2_MSG2 = 0x00425;// ARRAY(12) INTEGER SINGLE

// MDM FF1 input
// Radar Altimeter 1 data
inline constexpr unsigned int SCP_FF1_IOM0_CH4_DATA = 0x00431;// INTEGER SINGLE
// 3-LH_BODY_FLAP_UP_A
// 4-LH_BODY_FLAP_DOWN_A
// 5-MPS ME-1 SHUTDOWN CMD A
inline constexpr unsigned int SCP_FF1_IOM4_CH0_DATA = 0x00432;// INTEGER SINGLE
// 10-FCS LH PITCH AUTO MODE A
// 11-FCS LH PITCH CSS MODE A
// 13-FCS LH R-Y AUTO MODE A
// 14-FCS LH R-Y CSS MODE A
// 15-LH BODY FLAP AUTO/MANUAL A
inline constexpr unsigned int SCP_FF1_IOM4_CH1_DATA = 0x00433;// INTEGER SINGLE
// 0-LH SPD BK/THROT AUTO/MAN A
// 3-ENTRY ROLL MODE NO Y JET A
inline constexpr unsigned int SCP_FF1_IOM4_CH2_DATA = 0x00434;// INTEGER SINGLE
// 7-FWD THC POS X OUTPUT - A
// 8-FWD THC NEG X OUTPUT - A
// 9-FWD THC POS Y OUTPUT - A
// 10-FWD THC NEG Y OUTPUT - A
// 11-FWD THC POS Z OUTPUT - A
// 12-FWD THC NEG Z OUTPUT - A
// 13-LH SBTC TAKEOVER - A
inline constexpr unsigned int SCP_FF1_IOM6_CH0_DATA = 0x00435;// INTEGER SINGLE
// 1-LH_RHC_PLUS_PITCH_TRIM_A
// 2-LH_RHC_MINUS_PITCH_TRIM_A
// 3-LH_RHC_PLUS_ROLL_TRIM_A
// 4-LH_RHC_MINUS_ROLL_TRIM_A
// 5-SRB SEPARATION AUTO A CMD
// 6-SRB SEPN MANUAL/AUTO ENABLE A CMD
// 7-SRB SEPARATION INITIATE A CMD
inline constexpr unsigned int SCP_FF1_IOM6_CH1_DATA = 0x00436;// INTEGER SINGLE
// 4-FWD DAP SELECT A - A
// 5-FWD DAP SELECT B - A
// 6-AFT DAP SELECT A - C
// 7-AFT DAP SELECT B - C
// 8-FWD DAP AUTO A
// 9-FWD DAP MAN A
// 10-AFT DAP AUTO C
// 11-AFT DAP MAN C
inline constexpr unsigned int SCP_FF1_IOM9_CH0_DATA = 0x00437;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF1_IOM9_CH1_DATA = 0x00438;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF1_IOM9_CH2_DATA = 0x00439;// INTEGER SINGLE
// 1-LH_PLUS_PITCH_TRIM_A
// 2-LH_MINUS_PITCH_TRIM_A
// 3-LH_PLUS_ROLL_TRIM_A
// 4-LH_MINUS_ROLL_TRIM_A
// 5-LH_PLUS_YAW_TRIM_A
// 6-LH_MINUS_YAW_TRIM_A
// 13-CDR RDR ALTM SEL 1
inline constexpr unsigned int SCP_FF1_IOM12_CH0_DATA = 0x0043a;// INTEGER SINGLE
// 8-LH_RHC_TRIM_INHIBIT_A
inline constexpr unsigned int SCP_FF1_IOM12_CH1_DATA = 0x0043b;// INTEGER SINGLE
// 14-AFT RCS OPTIONS NORM C
// 15-AFT RCS OPTIONS VERNIER C
inline constexpr unsigned int SCP_FF1_IOM12_CH2_DATA = 0x0043c;// INTEGER SINGLE
// 7-AFT THC POS X OUTPUT - A
// 8-AFT THC NEG X OUTPUT - A
// 9-AFT THC POS Y OUTPUT - A
// 10-AFT THC NEG Y OUTPUT - A
// 11-AFT THC POS Z OUTPUT - A
// 12-AFT THC NEG Z OUTPUT - A
inline constexpr unsigned int SCP_FF1_IOM15_CH0_DATA = 0x0043d;// INTEGER SINGLE
// 5-ET SEPARATION MANUAL ENABLE A CMD
// 6-ET SEPARATION INITIATE A CMD
// 7-ET SEPARATION AUTO A CMD
inline constexpr unsigned int SCP_FF1_IOM15_CH1_DATA = 0x0043e;// INTEGER SINGLE

// MDM FF2 input
// Radar Altimeter 2 data
inline constexpr unsigned int SCP_FF2_IOM0_CH4_DATA = 0x0043f;// INTEGER SINGLE
// 2-ENTRY ROLL MODE NO Y JET B
// 3-LH_BODY_FLAP_UP_B
// 4-LH_BODY_FLAP_DOWN_B
// 5-MPS ME-1 SHUTDOWN CMD B
inline constexpr unsigned int SCP_FF2_IOM4_CH0_DATA = 0x00440;// INTEGER SINGLE
// 10-FCS LH PITCH AUTO MODE B
// 11-FCS LH PITCH CSS MODE B
// 13-FCS LH R-Y AUTO MODE B
// 14-FCS LH R-Y CSS MODE B
// 15-LH BODY FLAP AUTO/MANUAL B
inline constexpr unsigned int SCP_FF2_IOM4_CH1_DATA = 0x00441;// INTEGER SINGLE
// 0-LH SPD BK/THROT AUTO/MAN B
// 1-MPS ENG LIMIT CONTROL NO. 1 ENABLE
// 2-MPS ENG LIMIT CONTROL NO. 1 INHIBIT
// 3-MPS ENG LIMIT CONTROL NO. 1 AUTO
inline constexpr unsigned int SCP_FF2_IOM4_CH2_DATA = 0x00442;// INTEGER SINGLE
// 7-FWD THC POS X OUTPUT - B
// 8-FWD THC NEG X OUTPUT - B
// 9-FWD THC POS Y OUTPUT - B
// 10-FWD THC NEG Y OUTPUT - B
// 11-FWD THC POS Z OUTPUT - B
// 12-FWD THC NEG Z OUTPUT - B
// 13-LH SBTC TAKEOVER - B
inline constexpr unsigned int SCP_FF2_IOM6_CH0_DATA = 0x00443;// INTEGER SINGLE
// 1-LH_RHC_PLUS_PITCH_TRIM_B
// 2-LH_RHC_MINUS_PITCH_TRIM_B
// 3-LH_RHC_PLUS_ROLL_TRIM_B
// 4-LH_RHC_MINUS_ROLL_TRIM_B
inline constexpr unsigned int SCP_FF2_IOM6_CH1_DATA = 0x00444;// INTEGER SINGLE
// 4-FWD DAP SELECT A - B
// 5-FWD DAP SELECT B - B
// 8-FWD DAP AUTO B
// 9-FWD DAP MAN B
inline constexpr unsigned int SCP_FF2_IOM9_CH0_DATA = 0x00445;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF2_IOM9_CH1_DATA = 0x00446;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF2_IOM9_CH2_DATA = 0x00447;// INTEGER SINGLE
// 1-LH_PLUS_PITCH_TRIM_B
// 2-LH_MINUS_PITCH_TRIM_B
// 3-LH_PLUS_ROLL_TRIM_B
// 4-LH_MINUS_ROLL_TRIM_B
// 5-LH_PLUS_YAW_TRIM_B
// 6-LH_MINUS_YAW_TRIM_B
// 13-PLT RDR ALTM SEL 1
inline constexpr unsigned int SCP_FF2_IOM12_CH0_DATA = 0x00448;// INTEGER SINGLE
// 8-LH_RHC_TRIM_INHIBIT_B
// 10-FCS RH PITCH AUTO MODE A
// 11-FCS RH PITCH CSS MODE A
// 13-FCS RH R-Y AUTO MODE A
// 14-FCS RH R-Y CSS MODE A
// 15-RH BODY FLAP AUTO/MANUAL A
inline constexpr unsigned int SCP_FF2_IOM12_CH1_DATA = 0x00449;// INTEGER SINGLE
// 0-RH SPD BK/THROT AUTO/MAN A
inline constexpr unsigned int SCP_FF2_IOM12_CH2_DATA = 0x0044a;// INTEGER SINGLE
// 7-AFT THC POS X OUTPUT - B
// 8-AFT THC NEG X OUTPUT - B
// 9-AFT THC POS Y OUTPUT - B
// 10-AFT THC NEG Y OUTPUT - B
// 11-AFT THC POS Z OUTPUT - B
// 12-AFT THC NEG Z OUTPUT - B
// 13-RH SBTC TAKEOVER - A
inline constexpr unsigned int SCP_FF2_IOM15_CH0_DATA = 0x0044b;// INTEGER SINGLE

// MDM FF3 input
// 3-RH_BODY_FLAP_UP_A
// 4-RH_BODY_FLAP_DOWN_A
// 5-MPS ME-3 SHUTDOWN CMD A
inline constexpr unsigned int SCP_FF3_IOM4_CH0_DATA = 0x0044c;// INTEGER SINGLE
// 10-FCS LH PITCH AUTO MODE C
// 11-FCS LH PITCH CSS MODE C
// 13-FCS LH R-Y AUTO MODE C
// 14-FCS LH R-Y CSS MODE C
// 15-LH BODY FLAP AUTO/MANUAL C
inline constexpr unsigned int SCP_FF3_IOM4_CH1_DATA = 0x0044d;// INTEGER SINGLE
// 0-LH SPD BK/THROT AUTO/MAN C
// 1-MPS ENG LIMIT CONTROL NO. 2 ENABLE
// 2-MPS ENG LIMIT CONTROL NO. 2 INHIBIT
// 3-MPS ENG LIMIT CONTROL NO. 2 AUTO
inline constexpr unsigned int SCP_FF3_IOM4_CH2_DATA = 0x0044e;// INTEGER SINGLE
// 7-FWD THC POS X OUTPUT - C
// 8-FWD THC NEG X OUTPUT - C
// 9-FWD THC POS Y OUTPUT - C
// 10-FWD THC NEG Y OUTPUT - C
// 11-FWD THC POS Z OUTPUT - C
// 12-FWD THC NEG Z OUTPUT - C
// 13-LH SBTC TAKEOVER - C
inline constexpr unsigned int SCP_FF3_IOM6_CH0_DATA = 0x0044f;// INTEGER SINGLE
// 5-SRB SEPARATION AUTO C CMD
// 6-SRB SEPN MANUAL/AUTO ENABLE C CMD
// 7-SRB SEPARATION INITIATE C CMD
inline constexpr unsigned int SCP_FF3_IOM6_CH1_DATA = 0x00450;// INTEGER SINGLE
// 4-AFT DAP SELECT A - A
// 5-AFT DAP SELECT B - A
// 6-FWD DAP SELECT A - C
// 7-FWD DAP SELECT B - C
// 8-AFT DAP AUTO A
// 9-AFT DAP MAN A
// 10-FWD DAP AUTO C
// 11-FWD DAP MAN C
inline constexpr unsigned int SCP_FF3_IOM9_CH0_DATA = 0x00451;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF3_IOM9_CH1_DATA = 0x00452;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF3_IOM9_CH2_DATA = 0x00453;// INTEGER SINGLE
// 1-RH_PLUS_PITCH_TRIM_A
// 2-RH_MINUS_PITCH_TRIM_A
// 3-RH_PLUS_ROLL_TRIM_A
// 4-RH_MINUS_ROLL_TRIM_A
// 5-RH_PLUS_YAW_TRIM_A
// 6-RH_MINUS_YAW_TRIM_A
inline constexpr unsigned int SCP_FF3_IOM12_CH0_DATA = 0x00454;// INTEGER SINGLE
// 2-ENTRY ROLL MODE NO Y JET C
// 8-RH_RHC_TRIM_INHIBIT_A
// 10-FCS RH PITCH AUTO MODE B
// 11-FCS RH PITCH CSS MODE B
// 13-FCS RH R-Y AUTO MODE B
// 14-FCS RH R-Y CSS MODE B
// 15-RH BODY FLAP AUTO/MANUAL B
inline constexpr unsigned int SCP_FF3_IOM12_CH1_DATA = 0x00455;// INTEGER SINGLE
// 0-RH SPD BK/THROT AUTO/MAN B
// 14-FWD RCS OPTIONS NORM C
// 15-FWD RCS OPTIONS VERNIER C
inline constexpr unsigned int SCP_FF3_IOM12_CH2_DATA = 0x00456;// INTEGER SINGLE
// 7-AFT THC POS X OUTPUT - C
// 8-AFT THC NEG X OUTPUT - C
// 9-AFT THC POS Y OUTPUT - C
// 10-AFT THC NEG Y OUTPUT - C
// 11-AFT THC POS Z OUTPUT - C
// 12-AFT THC NEG Z OUTPUT - C
// 13-RH SBTC TAKEOVER - B
inline constexpr unsigned int SCP_FF3_IOM15_CH0_DATA = 0x00457;// INTEGER SINGLE
// 1-RH_RHC_PLUS_PITCH_TRIM_A
// 2-RH_RHC_MINUS_PITCH_TRIM_A
// 3-RH_RHC_PLUS_ROLL_TRIM_A
// 4-RH_RHC_MINUS_ROLL_TRIM_A
// 5-ET SEPARATION MANUAL ENABLE C CMD
// 6-ET SEPARATION INITIATE C CMD
// 7-ET SEPARATION AUTO C CMD
inline constexpr unsigned int SCP_FF3_IOM15_CH1_DATA = 0x00458;// INTEGER SINGLE

// MDM FF4 input
// 3-RH_BODY_FLAP_UP_B
// 4-RH_BODY_FLAP_DOWN_B
// 5-MPS ME-3 SHUTDOWN CMD B
inline constexpr unsigned int SCP_FF4_IOM4_CH0_DATA = 0x00459;// INTEGER SINGLE
// 1-MPS ENG LIMIT CONTROL NO. 3 ENABLE
// 2-MPS ENG LIMIT CONTROL NO. 3 INHIBIT
// 3-MPS ENG LIMIT CONTROL NO. 3 AUTO
inline constexpr unsigned int SCP_FF4_IOM4_CH2_DATA = 0x0045a;// INTEGER SINGLE
// 5-SRB SEPARATION AUTO B CMD
// 6-SRB SEPN MANUAL/AUTO ENABLE B CMD
// 7-SRB SEPARATION INITIATE B CMD
inline constexpr unsigned int SCP_FF4_IOM6_CH1_DATA = 0x0045b;// INTEGER SINGLE
// 4-AFT DAP SELECT A - B
// 5-AFT DAP SELECT B - B
// 8-AFT DAP AUTO B
// 9-AFT DAP MAN B
inline constexpr unsigned int SCP_FF4_IOM9_CH0_DATA = 0x0045c;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF4_IOM9_CH1_DATA = 0x0045d;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF4_IOM9_CH2_DATA = 0x0045e;// INTEGER SINGLE
// 1-RH_PLUS_PITCH_TRIM_B
// 2-RH_MINUS_PITCH_TRIM_B
// 3-RH_PLUS_ROLL_TRIM_B
// 4-RH_MINUS_ROLL_TRIM_B
// 5-RH_PLUS_YAW_TRIM_B
// 6-RH_MINUS_YAW_TRIM_B
inline constexpr unsigned int SCP_FF4_IOM12_CH0_DATA = 0x0045f;// INTEGER SINGLE
// 8-RH_RHC_TRIM_INHIBIT_B
// 10-FCS RH PITCH AUTO MODE C
// 11-FCS RH PITCH CSS MODE C
// 13-FCS RH R-Y AUTO MODE C
// 14-FCS RH R-Y CSS MODE C
// 15-RH BODY FLAP AUTO/MANUAL C
inline constexpr unsigned int SCP_FF4_IOM12_CH1_DATA = 0x00460;// INTEGER SINGLE
// 0-RH SPD BK/THROT AUTO/MAN C
// 15-ENTRY ROLL MODE NO Y JET D
inline constexpr unsigned int SCP_FF4_IOM12_CH2_DATA = 0x00461;// INTEGER SINGLE
// 13-RH SBTC TAKEOVER - C
inline constexpr unsigned int SCP_FF4_IOM15_CH0_DATA = 0x00462;// INTEGER SINGLE
// 1-RH_RHC_PLUS_PITCH_TRIM_B
// 2-RH_RHC_MINUS_PITCH_TRIM_B
// 3-RH_RHC_PLUS_ROLL_TRIM_B
// 4-RH_RHC_MINUS_ROLL_TRIM_B
// 5-ET SEPARATION MANUAL ENABLE B CMD
// 6-ET SEPARATION INITIATE B CMD
// 7-ET SEPARATION AUTO B CMD
inline constexpr unsigned int SCP_FF4_IOM15_CH1_DATA = 0x00463;// INTEGER SINGLE

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
inline constexpr unsigned int SCP_FF1_IOM2_CH1_DATA = 0x00464;// INTEGER SINGLE
// 3-C3 LIGHT: FWD DAP CONTROL "MAN"
// 4-C3 LIGHT: FWD DAP SELECT "B"
// 5-C3 LIGHT: FWD DAP RCS JETS "VERN"
inline constexpr unsigned int SCP_FF1_IOM2_CH2_DATA = 0x00465;// INTEGER SINGLE
// 0-FWD EVENT TIMER: ABORT TIMER_RESET
// 11-C&W MATRIX "LEFT RCS" (LEAK DETECT)
inline constexpr unsigned int SCP_FF1_IOM5_CH1_DATA = 0x00466;// INTEGER SINGLE
// 4-F2 LIGHT: LH FCS BODY FLAP "AUTO"
// 5-F2 LIGHT: LH FCS SPEED BK "AUTO"
// 6-F2 LIGHT: LH FCS PITCH "AUTO"
// 7-F2 LIGHT: LH FCS ROLL/YAW "AUTO"
inline constexpr unsigned int SCP_FF1_IOM10_CH0_DATA = 0x00467;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF1_IOM10_CH1_DATA = 0x00468;// INTEGER SINGLE
// 0-C3 LIGHT: FWD MAN TRANS Z "NORM"
// 1-C3 LIGHT: FWD MAN TRANS Z "PULSE"
// 2-C3 LIGHT: FWD MAN TRANS Z "HIGH"
// 3-C&W MATRIX "BACKUP C/W ALARM"
// 4-SM ALERT: TONE A CMD 1
// 5-SM ALERT: LIGHT A CMD 1
inline constexpr unsigned int SCP_FF1_IOM10_CH2_DATA = 0x00469;// INTEGER SINGLE

// MDM FF2 output
// 0-F7 LIGHT: L MPS AMBER STATUS
inline constexpr unsigned int SCP_FF2_IOM2_CH1_DATA = 0x0046a;// INTEGER SINGLE
// 4-F2 LIGHT: LH FCS BODY FLAP "MAN"
// 5-F2 LIGHT: LH FCS SPEED BK "MAN"
// 6-F2 LIGHT: LH FCS PITCH "CSS"
// 7-F2 LIGHT: LH FCS ROLL/YAW "CSS"
inline constexpr unsigned int SCP_FF2_IOM10_CH0_DATA = 0x0046b;// INTEGER SINGLE
// 0-F7 LIGHT: L MPS RED STATUS
inline constexpr unsigned int SCP_FF2_IOM10_CH1_DATA = 0x0046c;// INTEGER SINGLE
// 3-C&W MATRIX "BACKUP C/W ALARM"
// 4-SM ALERT: TONE A CMD 2
// 5-SM ALERT: LIGHT A CMD 2
inline constexpr unsigned int SCP_FF2_IOM10_CH2_DATA = 0x0046d;// INTEGER SINGLE

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
inline constexpr unsigned int SCP_FF3_IOM2_CH1_DATA = 0x0046e;// INTEGER SINGLE
// 3-A6 LIGHT: AFT DAP CONTROL "MAN"
// 4-A6 LIGHT: AFT DAP SELECT "B"
// 5-A6 LIGHT: AFT DAP RCS JETS "VERN"
inline constexpr unsigned int SCP_FF3_IOM2_CH2_DATA = 0x0046f;// INTEGER SINGLE
// 0-C&W MATRIX "RCS JET"
// 1-C&W MATRIX "OMS TVC"
// 2-C&W MATRIX "LEFT OMS"
// 3-C&W MATRIX "RIGHT OMS"
// 4-C&W MATRIX "FCS CHANNEL"
// 5-C&W MATRIX "FCS SATURATION"
// 6-C&W MATRIX "IMU"
// 7-C&W MATRIX "RIGHT/AFT RHC"
// 8-C&W MATRIX "LEFT RHC"
// 9-C&W MATRIX "AIR DATA"
// 10-C&W MATRIX "RGA/ACCEL"
// 11-C&W MATRIX "RIGHT RCS" (LEAK DETECT)
// 12-C&W MATRIX "FWD RCS" (LEAK DETECT)
inline constexpr unsigned int SCP_FF3_IOM5_CH1_DATA = 0x00470;// INTEGER SINGLE
// 4-F4 LIGHT: RH FCS BODY FLAP "AUTO"
// 5-F4 LIGHT: RH FCS SPEED BK "AUTO"
// 6-F4 LIGHT: RH FCS PITCH "AUTO"
// 7-F4 LIGHT: RH FCS ROLL/YAW "AUTO"
inline constexpr unsigned int SCP_FF3_IOM10_CH0_DATA = 0x00471;// INTEGER SINGLE
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
inline constexpr unsigned int SCP_FF3_IOM10_CH1_DATA = 0x00472;// INTEGER SINGLE
// 0-A6 LIGHT: AFT MAN TRANS Z "NORM"
// 1-A6 LIGHT: AFT MAN TRANS Z "PULSE"
// 2-A6 LIGHT: AFT MAN TRANS Z "HIGH"
// 3-C&W MATRIX "BACKUP C/W ALARM"
// 4-SM ALERT: TONE A CMD 3
// 5-SM ALERT: LIGHT A CMD 3
inline constexpr unsigned int SCP_FF3_IOM10_CH2_DATA = 0x00473;// INTEGER SINGLE

// MDM FF4 output
// 0-FWD EVENT TIMER: LIFT OFF TIMER_RESET
inline constexpr unsigned int SCP_FF4_IOM5_CH1_DATA = 0x00474;// INTEGER SINGLE
// 4-F4 LIGHT: RH FCS BODY FLAP "MAN"
// 5-F4 LIGHT: RH FCS SPEED BK "MAN"
// 6-F4 LIGHT: RH FCS PITCH "CSS"
// 7-F4 LIGHT: RH FCS ROLL/YAW "CSS"
inline constexpr unsigned int SCP_FF4_IOM10_CH0_DATA = 0x00475;// INTEGER SINGLE
// 3-C&W MATRIX "BACKUP C/W ALARM"
// 4-SM ALERT: TONE A CMD 4
// 5-SM ALERT: LIGHT A CMD 4
inline constexpr unsigned int SCP_FF4_IOM10_CH2_DATA = 0x00476;// INTEGER SINGLE

// MDM PF1 output
// 12-C&W MATRIX "BACKUP C/W ALARM"
// 13-SM ALERT: TONE B CMD 1
// 14-SM ALERT: LIGHT B CMD 1
inline constexpr unsigned int SCP_PF1_IOM2_CH0_DATA = 0x00477;// INTEGER SINGLE

// MDM PF2 output
// 12-C&W MATRIX "BACKUP C/W ALARM"
// 13-SM ALERT: TONE B CMD 2
// 14-SM ALERT: LIGHT B CMD 2
inline constexpr unsigned int SCP_PF2_IOM2_CH0_DATA = 0x00478;// INTEGER SINGLE
// 2-C&W MATRIX "PAYLOAD WARNING"
inline constexpr unsigned int SCP_PF2_IOM10_CH2_DATA = 0x00479;// INTEGER SINGLE

// Radar Altimeter
inline constexpr unsigned int SCP_RA_DATA_CDR_SEL = 0x0047a;// INTEGER SINGLE
inline constexpr unsigned int SCP_RA_VALIDITY_CDR_SEL = 0x0047b;// INTEGER SINGLE
inline constexpr unsigned int SCP_RA_DATA_PLT_SEL = 0x0047c;// INTEGER SINGLE
inline constexpr unsigned int SCP_RA_VALIDITY_PLT_SEL = 0x0047d;// INTEGER SINGLE

// DAP PBIs light command
// forward
inline constexpr unsigned int SCP_FWD_DAP_SELECT_A_LT = 0x0047e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_SELECT_B_LT = 0x0047f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_AUTO_LT = 0x00480;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN_INRTL_LT = 0x00481;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN_LVLH_LT = 0x00482;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN_FREE_DFT_LT = 0x00483;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_BLANK_LT = 0x00484;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_X_NORM_LT = 0x00485;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_X_PULSE_LT = 0x00486;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_LOW_Z_LT = 0x00487;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Y_NORM_LT = 0x00488;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Y_PULSE_LT = 0x00489;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Z_HIGH_LT = 0x0048a;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Z_NORM_LT = 0x0048b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSL_Z_PULSE_LT = 0x0048c;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_JETS_NORM_LT = 0x0048d;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_ROLL_DISC_LT = 0x0048e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_ROLL_PULSE_LT = 0x0048f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ALT_PRCS_MODE_LT = 0x00490;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_PITCH_DISC_LT = 0x00491;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_PITCH_PULSE_LT = 0x00492;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_JETS_VERN_LT = 0x00493;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_YAW_DISC_LT = 0x00494;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROT_YAW_PULSE_LT = 0x00495;// INTEGER SINGLE
// aft
inline constexpr unsigned int SCP_AFT_DAP_SELECT_A_LT = 0x00496;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_SELECT_B_LT = 0x00497;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_AUTO_LT = 0x00498;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN_INRTL_LT = 0x00499;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN_LVLH_LT = 0x0049a;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN_FREE_DFT_LT = 0x0049b;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_BLANK_LT = 0x0049c;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_X_NORM_LT = 0x0049d;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_X_PULSE_LT = 0x0049e;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_LOW_Z_LT = 0x0049f;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Y_NORM_LT = 0x004a0;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Y_PULSE_LT = 0x004a1;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Z_HIGH_LT = 0x004a2;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Z_NORM_LT = 0x004a3;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSL_Z_PULSE_LT = 0x004a4;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_JETS_NORM_LT = 0x004a5;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_ROLL_DISC_LT = 0x004a6;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_ROLL_PULSE_LT = 0x004a7;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ALT_PRCS_MODE_LT = 0x004a8;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_PITCH_DISC_LT = 0x004a9;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_PITCH_PULSE_LT = 0x004aa;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_JETS_VERN_LT = 0x004ab;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_YAW_DISC_LT = 0x004ac;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROT_YAW_PULSE_LT = 0x004ad;// INTEGER SINGLE

// TAEM parameters
// maximum shuttle orbiter weight [slugs]
inline constexpr unsigned int SCP_WT_GS1 = 0x004ae;// SCALAR DOUBLE
// minimum RPRED to issue OHALRT [ft]
inline constexpr unsigned int SCP_RMOH = 0x004b0;// SCALAR DOUBLE
// HAC turn angle [deg]
inline constexpr unsigned int SCP_PSHA = 0x004b2;// SCALAR DOUBLE
// HAC radius [ft]
inline constexpr unsigned int SCP_RTURN = 0x004b4;// SCALAR DOUBLE
// R/L cone indicator [1]
inline constexpr unsigned int SCP_YSGN = 0x004b6;// SCALAR DOUBLE
// PSHA reset value [deg]
inline constexpr unsigned int SCP_PSHARS = 0x004b8;// SCALAR DOUBLE
// initial HAC spiral turn radius on final [ft]
inline constexpr unsigned int SCP_RF0 = 0x004ba;// SCALAR DOUBLE
// linear term in spiral radius eqn. [ft/deg]
inline constexpr unsigned int SCP_R1 = 0x004bc;// SCALAR DOUBLE
// quadratic term in spiral radius eqn. [ft/deg]
inline constexpr unsigned int SCP_R2 = 0x004be;// SCALAR DOUBLE

// Autoland parameters
// pullup circle radius (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_AL_R = 0x004c0;// MATRIX(2,2) DOUBLE
// pullup circle center (x) (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_X_K = 0x004c8;// MATRIX(2,2) DOUBLE
// pullup circle center (h) (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_H_K = 0x004d0;// MATRIX(2,2) DOUBLE
// exponential/circle tangency range (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_X_EXP = 0x004d8;// MATRIX(2,2) DOUBLE
// exponential decay (indexed by IGI,IGS) [ft]
inline constexpr unsigned int SCP_H_DECAY = 0x004e0;// MATRIX(2,2) DOUBLE
// exponential decay factor [1]
inline constexpr unsigned int SCP_SIGMA = 0x004e8;// SCALAR DOUBLE
// steep glideslop angle (indexed by IGS) [deg]
inline constexpr unsigned int SCP_GAMMA_REF_1 = 0x004ea;// VECTOR(2) DOUBLE
// shallow glideslop angle [deg]
inline constexpr unsigned int SCP_GAMMA_REF_2 = 0x004ee;// SCALAR DOUBLE
// steep glide slope aim point (indexed by IGI) [ft]
inline constexpr unsigned int SCP_X_ZERO = 0x004f0;// VECTOR(2) DOUBLE
// shallow glide slope aim point [ft]
inline constexpr unsigned int SCP_X_AIM = 0x004f4;// SCALAR DOUBLE
// open-loop pull-up altitude [ft]
inline constexpr unsigned int SCP_H_FLARE = 0x004f6;// SCALAR DOUBLE
// closed-loop pull-up altitude [ft]
inline constexpr unsigned int SCP_H_CLOOP = 0x004f8;// SCALAR DOUBLE

// runway approach mode (1-overhead; 2-strait-in)
inline constexpr unsigned int SCP_OVHD = 0x004fa;// INTEGER SINGLE
// glide slope (1-light; 2-heavy)
inline constexpr unsigned int SCP_IGS = 0x004fb;// INTEGER SINGLE
// aimpoint (1-nom; 2-close-in)
inline constexpr unsigned int SCP_IGI = 0x004fc;// INTEGER SINGLE
// runway ID (1-pri; 2-sec)
inline constexpr unsigned int SCP_RWID = 0x004fd;// INTEGER SINGLE
// previous runway ID (1-pri; 2-sec)
inline constexpr unsigned int SCP_RWID0 = 0x004fe;// INTEGER SINGLE
// landing site ID [1,45]
inline constexpr unsigned int SCP_LSID = 0x004ff;// INTEGER SINGLE

// speedbrake logic select (1-nom; 2-short; 3-ELS)
inline constexpr unsigned int SCP_SB_SEL = 0x00500;// INTEGER SINGLE

// pri runway name
inline constexpr unsigned int SCP_PRI_ID = 0x00501;// CHARACTER(5)
// pri runway heading [deg]
inline constexpr unsigned int SCP_PRI_HDG = 0x00506;// SCALAR DOUBLE
// pri runway pos (greenwich=ECEF) [ft]
inline constexpr unsigned int SCP_PRI_POS = 0x00508;// VECTOR(3) DOUBLE
// pri greenwich(=ECEF)-to-runway matrix [ft]
inline constexpr unsigned int SCP_PRI_G2R = 0x0050e;// MATRIX(3,3) DOUBLE
// pri runway length [ft]
inline constexpr unsigned int SCP_PRI_LEN = 0x00520;// INTEGER SINGLE
// sec runway name
inline constexpr unsigned int SCP_SEC_ID = 0x00521;// CHARACTER(5)
// sec runway heading [deg]
inline constexpr unsigned int SCP_SEC_HDG = 0x00526;// SCALAR DOUBLE
// sec runway pos (greenwich=ECEF) [ft]
inline constexpr unsigned int SCP_SEC_POS = 0x00528;// VECTOR(3) DOUBLE
// sec greenwich(=ECEF)-to-runway matrix [ft]
inline constexpr unsigned int SCP_SEC_G2R = 0x0052e;// MATRIX(3,3) DOUBLE
// sec runway length [ft]
inline constexpr unsigned int SCP_SEC_LEN = 0x00540;// INTEGER SINGLE

// Landing SOP
inline constexpr unsigned int SCP_WOWLON = 0x00541;// INTEGER SINGLE
inline constexpr unsigned int SCP_FLATTURN = 0x00542;// INTEGER SINGLE
inline constexpr unsigned int SCP_ROLLOUT = 0x00543;// INTEGER SINGLE
inline constexpr unsigned int SCP_GSENBL = 0x00544;// INTEGER SINGLE
inline constexpr unsigned int SCP_HUD_WOWLON = 0x00545;// INTEGER SINGLE
inline constexpr unsigned int SCP_HUD_ROLLOUT = 0x00546;// INTEGER SINGLE

// Aerojet DAP FCS
// AerojetDAP FCS pitch control (1-AUTO; 2-CSS)
inline constexpr unsigned int SCP_AEROJET_FCS_PITCH = 0x00547;// INTEGER SINGLE
// AerojetDAP FCS roll control (1-AUTO; 2-CSS)
inline constexpr unsigned int SCP_AEROJET_FCS_ROLL = 0x00548;// INTEGER SINGLE
// AerojetDAP FCS speedbrake control (1-AUTO; 2-CDR; 3-PLT)
inline constexpr unsigned int SCP_AEROJET_FCS_SB = 0x00549;// INTEGER SINGLE
// AerojetDAP body flap control (1-AUTO; 2-CSS)
inline constexpr unsigned int SCP_AEROJET_FCS_BF = 0x0054a;// INTEGER SINGLE
// number of RCS roll jets to fire (+right, -left) [1]
inline constexpr unsigned int SCP_UXCMD = 0x0054b;// INTEGER SINGLE
// number of RCS pitch jets to fire (+up, -down) [1]
inline constexpr unsigned int SCP_UYCMD = 0x0054c;// INTEGER SINGLE
// number of RCS yaw jets to fire (+right, -left) [1]
inline constexpr unsigned int SCP_UZCMD = 0x0054d;// INTEGER SINGLE
// aileron trim [deg]
inline constexpr unsigned int SCP_DATRIM = 0x0054e;// SCALAR DOUBLE
// rudder trim [deg]
inline constexpr unsigned int SCP_DRTRIM = 0x00550;// SCALAR DOUBLE
// NY trim [g]
inline constexpr unsigned int SCP_DRTI = 0x00552;// SCALAR DOUBLE
// NZ error [g]
inline constexpr unsigned int SCP_NZERR = 0x00554;// SCALAR DOUBLE
// bank error [deg]
inline constexpr unsigned int SCP_BANKERR = 0x00556;// SCALAR DOUBLE
// wraparound DAP mode (0=INH, 1=ENA, 2=ACT)
inline constexpr unsigned int SCP_WRAP = 0x00558;// INTEGER SINGLE
// elevator command [deg]
inline constexpr unsigned int SCP_DECC = 0x00559;// SCALAR DOUBLE
// aileron command [deg]
inline constexpr unsigned int SCP_DAC = 0x0055b;// SCALAR DOUBLE
// rudder command [deg]
inline constexpr unsigned int SCP_DRC = 0x0055d;// SCALAR DOUBLE
// speedbrake command [deg]
inline constexpr unsigned int SCP_DSBC = 0x0055f;// SCALAR DOUBLE
// NWS command [deg]
inline constexpr unsigned int SCP_DNWC = 0x00561;// SCALAR DOUBLE
// Entry Mode switch "Low Gain" selected
inline constexpr unsigned int SCP_SEL_L_GAIN = 0x00563;// INTEGER SINGLE
// Entry Mode switch "No Yaw Jet" selected
inline constexpr unsigned int SCP_SEL_NO_Y_JET = 0x00564;// INTEGER SINGLE
// Entry Mode switch override
inline constexpr unsigned int SCP_ENTRY_SW_OVERRIDE = 0x00565;// INTEGER SINGLE

// A/L UPP
// geodetic altitude of vehicle center of mass above rw [ft]
inline constexpr unsigned int SCP_H = 0x00566;// SCALAR DOUBLE
// negative z component of velocity in topodetic coordinates [fps]
inline constexpr unsigned int SCP_HDOT = 0x00568;// SCALAR DOUBLE
// true airspeed [fps]
inline constexpr unsigned int SCP_V_T = 0x0056a;// SCALAR DOUBLE
// equivalent? airspeed [fps]
inline constexpr unsigned int SCP_V_I = 0x0056c;// SCALAR DOUBLE
// equivalent airspeed [knots]
inline constexpr unsigned int SCP_KEAS = 0x0056e;// SCALAR DOUBLE
// topodetic horizontal component of earth relative velocity [fps]
inline constexpr unsigned int SCP_VG = 0x00570;// SCALAR DOUBLE
// vehicle position in runway coordinates [ft]
inline constexpr unsigned int SCP_X = 0x00572;// SCALAR DOUBLE
inline constexpr unsigned int SCP_Y = 0x00574;// SCALAR DOUBLE
inline constexpr unsigned int SCP_Z = 0x00576;// SCALAR DOUBLE
// vehicle velocity in runway coordinates [fps]
inline constexpr unsigned int SCP_XDOT = 0x00578;// SCALAR DOUBLE
inline constexpr unsigned int SCP_YDOT = 0x0057a;// SCALAR DOUBLE
// heading [deg]
inline constexpr unsigned int SCP_HDG = 0x0057c;// SCALAR DOUBLE
// topodetic earth relative flight-path angle [deg]
inline constexpr unsigned int SCP_GAMMA = 0x0057e;// SCALAR DOUBLE
// roll [deg]
inline constexpr unsigned int SCP_PHI = 0x00580;// SCALAR DOUBLE
// cosine of body roll euler angle [1]
inline constexpr unsigned int SCP_COSPHI = 0x00582;// SCALAR DOUBLE
// sine of body roll euler angle [1]
inline constexpr unsigned int SCP_SINPHI = 0x00584;// SCALAR DOUBLE
// tangent of body roll euler angle [1]
inline constexpr unsigned int SCP_TANPHI = 0x00586;// SCALAR DOUBLE
// cosine of angle of attack [1]
inline constexpr unsigned int SCP_COSALF = 0x00588;// SCALAR DOUBLE
// sine of angle of attack [1]
inline constexpr unsigned int SCP_SINALF = 0x0058a;// SCALAR DOUBLE
// pitch [deg]
inline constexpr unsigned int SCP_THETA = 0x0058c;// SCALAR DOUBLE
// cosine of theta [1]
inline constexpr unsigned int SCP_COSTH = 0x0058e;// SCALAR DOUBLE
// sine of theta [1]
inline constexpr unsigned int SCP_SINTH = 0x00590;// SCALAR DOUBLE
// angle-of-attack [deg]
inline constexpr unsigned int SCP_ALPHA = 0x00592;// SCALAR DOUBLE
// sideslip [deg]
inline constexpr unsigned int SCP_BETA = 0x00594;// SCALAR DOUBLE
// dynamic pressure [psf]
inline constexpr unsigned int SCP_QBAR = 0x00596;// SCALAR DOUBLE
// lateral acceleration [g]
inline constexpr unsigned int SCP_NY = 0x00598;// SCALAR DOUBLE
// normal acceleration [g]
inline constexpr unsigned int SCP_NZ = 0x0059a;// SCALAR DOUBLE
// orbiter mass [slugs]
inline constexpr unsigned int SCP_WEIGHT = 0x0059c;// SCALAR DOUBLE
// body roll rate [deg/s]
inline constexpr unsigned int SCP_P = 0x0059e;// SCALAR DOUBLE
// body pitch rate [deg/s]
inline constexpr unsigned int SCP_Q = 0x005a0;// SCALAR DOUBLE
// body yaw rate [deg/s]
inline constexpr unsigned int SCP_R = 0x005a2;// SCALAR DOUBLE

// TAEM UPP
// mach number [1]
inline constexpr unsigned int SCP_MACH = 0x005a4;// SCALAR DOUBLE
// course with respect to centerline [deg]
inline constexpr unsigned int SCP_PSD = 0x005a6;// SCALAR DOUBLE

// Entry UPP
// vehicle position in ECEF [ft]
inline constexpr unsigned int SCP_ECEF_POS = 0x005a8;// VECTOR(3) DOUBLE
// vehicle velocity in ECEF [fps]
inline constexpr unsigned int SCP_ECEF_VEL = 0x005ae;// VECTOR(3) DOUBLE
// current relative velocity [fps]
inline constexpr unsigned int SCP_VE = 0x005b4;// SCALAR DOUBLE
// current inertial velocity [fps]
inline constexpr unsigned int SCP_VI = 0x005b6;// SCALAR DOUBLE
// current drag acceleration [fps^2]
inline constexpr unsigned int SCP_DRAG = 0x005b8;// SCALAR DOUBLE
// current lift/drag ratio [1]
inline constexpr unsigned int SCP_LOD = 0x005ba;// SCALAR DOUBLE
// current load factor [fps^2]
inline constexpr unsigned int SCP_XLFAC = 0x005bc;// SCALAR DOUBLE

// EGRT output
// azimuth error [rad]
inline constexpr unsigned int SCP_DELAZ = 0x005be;// SCALAR DOUBLE
// range to target [NM]
inline constexpr unsigned int SCP_TRANG = 0x005c0;// SCALAR DOUBLE

// Autoland guidance output
// autoland phase counter
inline constexpr unsigned int SCP_PMODE = 0x005c2;// INTEGER SINGLE
// FSGS phase counter
inline constexpr unsigned int SCP_FMODE = 0x005c3;// INTEGER SINGLE
// autoland NZ command [g]
inline constexpr unsigned int SCP_NZ_CMD = 0x005c4;// SCALAR DOUBLE
// autoland roll angle command [deg]
inline constexpr unsigned int SCP_PHIC_AL = 0x005c6;// SCALAR DOUBLE
// autoland yaw rate command post WOWLON
inline constexpr unsigned int SCP_RC = 0x005c8;// SCALAR DOUBLE
// autoland speedbrake command [deg]
inline constexpr unsigned int SCP_DSBC_AL = 0x005ca;// SCALAR DOUBLE
// body flap retract command
inline constexpr unsigned int SCP_RETRACT_BF = 0x005cc;// INTEGER SINGLE
// altitude error [ft]
inline constexpr unsigned int SCP_HERR = 0x005cd;// SCALAR DOUBLE

// TAEM guidance output
// heading error to HAC tangency [deg]
inline constexpr unsigned int SCP_DPSAC = 0x005cf;// SCALAR DOUBLE
// predicted range to rw [ft]
inline constexpr unsigned int SCP_RPRED = 0x005d1;// SCALAR DOUBLE
// commanded body normal load factor increment from equilibrium [g]
inline constexpr unsigned int SCP_NZC = 0x005d3;// SCALAR DOUBLE
// speedbrake angle command (hinge line) [deg]
inline constexpr unsigned int SCP_DSBC_AT = 0x005d5;// SCALAR DOUBLE
// roll angle command
inline constexpr unsigned int SCP_PHIC_AT = 0x005d7;// SCALAR DOUBLE
// minimum entry point flag
inline constexpr unsigned int SCP_MEP = 0x005d9;// INTEGER SINGLE
// TAEM phase counter [1]
inline constexpr unsigned int SCP_IPHASE = 0x005da;// INTEGER SINGLE
// TAEM end flag
inline constexpr unsigned int SCP_TG_END = 0x005db;// INTEGER SINGLE
// current HAC final size [ft]
inline constexpr unsigned int SCP_RF = 0x005dc;// SCALAR DOUBLE
// HAC X position [ft]
inline constexpr unsigned int SCP_XHAC = 0x005de;// SCALAR DOUBLE
// distance from OV to HAC center [ft]
inline constexpr unsigned int SCP_RCIR = 0x005e0;// SCALAR DOUBLE
// energy per unit weight [ft]
inline constexpr unsigned int SCP_EOW = 0x005e2;// SCALAR DOUBLE
// reference energy [ft]
inline constexpr unsigned int SCP_EN = 0x005e4;// SCALAR DOUBLE
// E/W to start S-turn [ft]
inline constexpr unsigned int SCP_ES = 0x005e6;// SCALAR DOUBLE
// E/W to switch to MEP [ft]
inline constexpr unsigned int SCP_EMEP = 0x005e8;// SCALAR DOUBLE
// E/W to downmode to STRN [ft]
inline constexpr unsigned int SCP_EMOH = 0x005ea;// SCALAR DOUBLE
// altitude error from reference profile [ft]
inline constexpr unsigned int SCP_HERROR = 0x005ec;// SCALAR DOUBLE
// heading to HAC center [deg]
inline constexpr unsigned int SCP_PSC = 0x005ee;// SCALAR DOUBLE
// estimated time to HAC [sec]
inline constexpr unsigned int SCP_P2TRNT = 0x005f0;// SCALAR DOUBLE
// "OTT ST IN" indication
inline constexpr unsigned int SCP_OTT_ST_IN = 0x005f2;// INTEGER SINGLE
// "SW TO MEP" indication
inline constexpr unsigned int SCP_SW_TO_MEP = 0x005f3;// INTEGER SINGLE

// Entry guidance output
// angle-of-attack command [deg]
inline constexpr unsigned int SCP_ALPCMD = 0x005f4;// SCALAR DOUBLE
// drag reference [fps^2]
inline constexpr unsigned int SCP_DREFP = 0x005f6;// SCALAR DOUBLE
// roll angle command about body axis [deg]
inline constexpr unsigned int SCP_ROLLCMD = 0x005f8;// SCALAR DOUBLE
// roll ref [deg]
inline constexpr unsigned int SCP_ROLLREF = 0x005fa;// SCALAR DOUBLE
// altitude rate reference [fps]
inline constexpr unsigned int SCP_RDTREF = 0x005fc;// SCALAR DOUBLE
// derivative of range wrt drag [NM/fps^2]
inline constexpr unsigned int SCP_DRDD = 0x005fe;// SCALAR DOUBLE
// Rdot feedback term [fps]
inline constexpr unsigned int SCP_DLRDOT = 0x00600;// SCALAR DOUBLE
// maximum heading error absolute value [rad]
inline constexpr unsigned int SCP_YL = 0x00602;// SCALAR DOUBLE
// scheduled angle of attack [deg]
inline constexpr unsigned int SCP_ACMD1 = 0x00604;// SCALAR DOUBLE
// entry guidance subphase counter
inline constexpr unsigned int SCP_ISLECT = 0x00606;// INTEGER SINGLE
// Entry guidance end flag
inline constexpr unsigned int SCP_EG_END = 0x00607;// INTEGER SINGLE

// aerosurface position feedback
// left outboard elevon pos [deg]
inline constexpr unsigned int SCP_LOB_ELVN_POS_FDBK = 0x00608;// SCALAR DOUBLE
// left inboard elevon pos [deg]
inline constexpr unsigned int SCP_LIB_ELVN_POS_FDBK = 0x0060a;// SCALAR DOUBLE
// right inboard elevon pos [deg]
inline constexpr unsigned int SCP_RIB_ELVN_POS_FDBK = 0x0060c;// SCALAR DOUBLE
// right outboard elevon pos [deg]
inline constexpr unsigned int SCP_ROB_ELVN_POS_FDBK = 0x0060e;// SCALAR DOUBLE
// elevator pos [deg]
inline constexpr unsigned int SCP_DEFB = 0x00610;// SCALAR DOUBLE
// aileron pos [deg]
inline constexpr unsigned int SCP_DAFB = 0x00612;// SCALAR DOUBLE
// body flap pos [deg]
inline constexpr unsigned int SCP_DBFOFB = 0x00614;// SCALAR DOUBLE
// rudder pos [deg]
inline constexpr unsigned int SCP_DRFB = 0x00616;// SCALAR DOUBLE
// Speedbrake pos [deg]
inline constexpr unsigned int SCP_DSBFB_DEG = 0x00618;// SCALAR DOUBLE
// Speedbrake pos [%]
inline constexpr unsigned int SCP_DSBFB_PCT = 0x0061a;// SCALAR DOUBLE
// speedbrake increment [deg]
inline constexpr unsigned int SCP_DSBPC = 0x0061c;// SCALAR DOUBLE

// Aerosurface command
// left outboard elevon command [deg]
inline constexpr unsigned int SCP_ELOC = 0x0061e;// SCALAR DOUBLE
// left inboard elevon command [deg]
inline constexpr unsigned int SCP_ELIC = 0x00620;// SCALAR DOUBLE
// right inboard elevon command [deg]
inline constexpr unsigned int SCP_ERIC = 0x00622;// SCALAR DOUBLE
// right outboard elevon command [deg]
inline constexpr unsigned int SCP_EROC = 0x00624;// SCALAR DOUBLE
// body flap command [deg]
inline constexpr unsigned int SCP_DBFRC = 0x00626;// SCALAR DOUBLE
// rudder command [deg]
inline constexpr unsigned int SCP_RUDDER_CMD = 0x00628;// SCALAR DOUBLE
// speedbrake command [deg]
inline constexpr unsigned int SCP_SPEED_BRAKE_CMD = 0x0062a;// SCALAR DOUBLE

// Speedbrake AUTO command [deg]
inline constexpr unsigned int SCP_SB_AUTO_CMD = 0x0062c;// SCALAR DOUBLE

// HUD
// runway to go [ft]
inline constexpr unsigned int SCP_RWTOGO = 0x0062e;// SCALAR DOUBLE
// max deceleration [fps^2]
inline constexpr unsigned int SCP_HUDMAXDECEL = 0x00630;// SCALAR DOUBLE
// speedbrake delta minimum velocity [fps]
inline constexpr unsigned int SCP_SBDMN = 0x00632;// SCALAR DOUBLE
// speedbrake delta maximum velocity [fps]
inline constexpr unsigned int SCP_SBDMX = 0x00634;// SCALAR DOUBLE
// speedbrake delta limit [deg]
inline constexpr unsigned int SCP_SBDLIM = 0x00636;// SCALAR DOUBLE

// Trim Switch positions
inline constexpr unsigned int SCP_LH_RHC_TRIM_INHIBIT = 0x00638;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_TRIM_INHIBIT = 0x00639;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_PLUS_PITCH_TRIM = 0x0063a;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_MINUS_PITCH_TRIM = 0x0063b;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_PLUS_ROLL_TRIM = 0x0063c;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_RHC_MINUS_ROLL_TRIM = 0x0063d;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_PLUS_PITCH_TRIM = 0x0063e;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_MINUS_PITCH_TRIM = 0x0063f;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_PLUS_ROLL_TRIM = 0x00640;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_RHC_MINUS_ROLL_TRIM = 0x00641;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_PLUS_PITCH_TRIM = 0x00642;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_MINUS_PITCH_TRIM = 0x00643;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_PLUS_ROLL_TRIM = 0x00644;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_MINUS_ROLL_TRIM = 0x00645;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_PLUS_YAW_TRIM = 0x00646;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_MINUS_YAW_TRIM = 0x00647;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_PLUS_PITCH_TRIM = 0x00648;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_MINUS_PITCH_TRIM = 0x00649;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_PLUS_ROLL_TRIM = 0x0064a;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_MINUS_ROLL_TRIM = 0x0064b;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_PLUS_YAW_TRIM = 0x0064c;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_MINUS_YAW_TRIM = 0x0064d;// INTEGER SINGLE
inline constexpr unsigned int SCP_DETM_RHC = 0x0064e;// INTEGER SINGLE
inline constexpr unsigned int SCP_DATM_RHC = 0x0064f;// INTEGER SINGLE
inline constexpr unsigned int SCP_DETM_PAN = 0x00650;// INTEGER SINGLE
inline constexpr unsigned int SCP_DATM_PAN = 0x00651;// INTEGER SINGLE
inline constexpr unsigned int SCP_DRT = 0x00652;// INTEGER SINGLE

// Body Flap Switch positions
inline constexpr unsigned int SCP_LH_BODY_FLAP_UP = 0x00653;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_BODY_FLAP_DOWN = 0x00654;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_BODY_FLAP_UP = 0x00655;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_BODY_FLAP_DOWN = 0x00656;// INTEGER SINGLE
inline constexpr unsigned int SCP_DBFMAN = 0x00657;// INTEGER SINGLE

// MPS switches
inline constexpr unsigned int SCP_MPS_BACKUP_LH2_PRPLT_DUMP_START = 0x00658;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_BACKUP_LH2_PRPLT_DUMP_STOP = 0x00659;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_PRPLT_DUMP_SEQUENCE_START = 0x0065a;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_PRPLT_DUMP_SEQUENCE_STOP = 0x0065b;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ENG_LIMIT_CONTROL_ENABLE = 0x0065c;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ENG_LIMIT_CONTROL_INHIBIT = 0x0065d;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ENG_LIMIT_CONTROL_AUTO = 0x0065e;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ME_1_SHUTDOWN_CMD = 0x0065f;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ME_2_SHUTDOWN_CMD = 0x00660;// INTEGER SINGLE
inline constexpr unsigned int SCP_MPS_ME_3_SHUTDOWN_CMD = 0x00661;// INTEGER SINGLE

// Separation switches
inline constexpr unsigned int SCP_SRB_SEPARATION_AUTO_CMD = 0x00662;// INTEGER SINGLE
inline constexpr unsigned int SCP_SRB_SEPARATION_MANUAL_AUTO_ENABLE_CMD = 0x00663;// INTEGER SINGLE
inline constexpr unsigned int SCP_SRB_SEPARATION_INITIATE_CMD = 0x00664;// INTEGER SINGLE
inline constexpr unsigned int SCP_ET_SEPARATION_MANUAL_ENABLE_CMD = 0x00665;// INTEGER SINGLE
inline constexpr unsigned int SCP_ET_SEPARATION_INITIATE_CMD = 0x00666;// INTEGER SINGLE
inline constexpr unsigned int SCP_ET_SEPARATION_AUTO_CMD = 0x00667;// INTEGER SINGLE

// (0-"-Z"; 1-"-X")
inline constexpr unsigned int SCP_SENSE_SWITCH = 0x00668;// INTEGER SINGLE

// FCS PBIs
inline constexpr unsigned int SCP_FCS_LH_PITCH_AUTO_MODE = 0x00669;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_LH_PITCH_CSS_MODE = 0x0066a;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_LH_RY_AUTO_MODE = 0x0066b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_LH_RY_CSS_MODE = 0x0066c;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_BODY_FLAP_AUTO_MANUAL = 0x0066d;// INTEGER SINGLE
inline constexpr unsigned int SCP_LH_SPD_BK_THROT_AUTO_MAN = 0x0066e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_PITCH_AUTO_MODE = 0x0066f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_PITCH_CSS_MODE = 0x00670;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_RY_AUTO_MODE = 0x00671;// INTEGER SINGLE
inline constexpr unsigned int SCP_FCS_RH_RY_CSS_MODE = 0x00672;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_BODY_FLAP_AUTO_MANUAL = 0x00673;// INTEGER SINGLE
inline constexpr unsigned int SCP_RH_SPD_BK_THROT_AUTO_MAN = 0x00674;// INTEGER SINGLE

// Orbit DAP PBIs
inline constexpr unsigned int SCP_FWD_DAP_SELECT_A = 0x00675;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_SELECT_B = 0x00676;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_AUTO = 0x00677;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_DAP_MAN = 0x00678;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_OPTIONS_NORM = 0x00679;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_RCS_OPTIONS_VERNIER = 0x0067a;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_ROLL_DISC_RATE = 0x0067b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_ROLL_ACCEL = 0x0067c;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_ROLL_PULSE = 0x0067d;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_PITCH_DISC_RATE = 0x0067e;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_PITCH_ACCEL = 0x0067f;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_PITCH_PULSE = 0x00680;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_YAW_DISC_RATE = 0x00681;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_YAW_ACCEL = 0x00682;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_ROTATION_YAW_PULSE = 0x00683;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_X_NORM = 0x00684;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_X_PULSE = 0x00685;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_X_LVLH = 0x00686;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Y_NORM = 0x00687;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Y_PULSE = 0x00688;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Y_LOW_Z = 0x00689;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Z_NORM = 0x0068a;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Z_PULSE = 0x0068b;// INTEGER SINGLE
inline constexpr unsigned int SCP_FWD_TRANSLATION_Z_HIGH = 0x0068c;// INTEGER SINGLE

inline constexpr unsigned int SCP_AFT_DAP_SELECT_A = 0x0068d;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_SELECT_B = 0x0068e;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_AUTO = 0x0068f;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_DAP_MAN = 0x00690;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_OPTIONS_NORM = 0x00691;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_RCS_OPTIONS_VERNIER = 0x00692;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_ROLL_DISC_RATE = 0x00693;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_ROLL_ACCEL = 0x00694;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_ROLL_PULSE = 0x00695;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_PITCH_DISC_RATE = 0x00696;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_PITCH_ACCEL = 0x00697;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_PITCH_PULSE = 0x00698;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_YAW_DISC_RATE = 0x00699;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_YAW_ACCEL = 0x0069a;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_ROTATION_YAW_PULSE = 0x0069b;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_X_NORM = 0x0069c;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_X_PULSE = 0x0069d;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_X_LVLH = 0x0069e;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Y_NORM = 0x0069f;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Y_PULSE = 0x006a0;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Y_LOW_Z = 0x006a1;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Z_NORM = 0x006a2;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Z_PULSE = 0x006a3;// INTEGER SINGLE
inline constexpr unsigned int SCP_AFT_TRANSLATION_Z_HIGH = 0x006a4;// INTEGER SINGLE

// Ascent
inline constexpr unsigned int SCP_KMIN = 0x006a5;// INTEGER SINGLE
inline constexpr unsigned int SCP_KMAX = 0x006a6;// INTEGER SINGLE
// (0-KMAX_NOM; 1-KMAX_SECONDARY; 2-KMAX_ABORT)
inline constexpr unsigned int SCP_KMAX_SEL = 0x006a7;// INTEGER SINGLE
// MPS dump complete flag
inline constexpr unsigned int SCP_MPS_LO2_DUMP_STOP = 0x006a8;// INTEGER SINGLE

// SSME and MPS flags
// ME-x command path fail flag
inline constexpr unsigned int SCP_ME_CMD_PATH_FAIL = 0x006a9;// ARRAY(3) INTEGER SINGLE
// ME-x electronic lockup mode flag
inline constexpr unsigned int SCP_ME_ELEC_LOCKUP = 0x006ac;// ARRAY(3) INTEGER SINGLE
// ME-x flight data path fail flag
inline constexpr unsigned int SCP_ME_FLT_DATA_PATH_FAIL = 0x006af;// ARRAY(3) INTEGER SINGLE
// ME-x hydraulic lockup mode flag
inline constexpr unsigned int SCP_ME_HYD_LOCKUP = 0x006b2;// ARRAY(3) INTEGER SINGLE
// ME-x engine limit exceeded flag
inline constexpr unsigned int SCP_ME_LIM_EX = 0x006b5;// ARRAY(3) INTEGER SINGLE
// MPS E-x eng ready ind
inline constexpr unsigned int SCP_ME_READY = 0x006b8;// ARRAY(3) INTEGER SINGLE
// MPS E-x post-shutdown phase
inline constexpr unsigned int SCP_MEPSTSHDN = 0x006bb;// ARRAY(3) INTEGER SINGLE
// MPS E-x shutdown phase
inline constexpr unsigned int SCP_MESHDN = 0x006be;// ARRAY(3) INTEGER SINGLE
// MPS E1 fail flag
inline constexpr unsigned int SCP_ME1_FAIL_SHUTDOWN = 0x006c1;// INTEGER SINGLE
// MPS E2 fail flag
inline constexpr unsigned int SCP_ME2_FAIL_SHUTDOWN = 0x006c2;// INTEGER SINGLE
// MPS E3 fail flag
inline constexpr unsigned int SCP_ME3_FAIL_SHUTDOWN = 0x006c3;// INTEGER SINGLE
// MECO command flag
inline constexpr unsigned int SCP_MECO_CMD = 0x006c4;// INTEGER SINGLE
// MECO confirmed flag
inline constexpr unsigned int SCP_MECO_CONFIRMED = 0x006c5;// INTEGER SINGLE


inline constexpr unsigned int SCP_ET_AUTO_SEP_INHIBIT_CREW_ALERT = 0x006c6;// INTEGER SINGLE

inline constexpr unsigned int SIMPLECOMPOOL_SIZE = 1735;

#endif// _COMPOOL_H_
