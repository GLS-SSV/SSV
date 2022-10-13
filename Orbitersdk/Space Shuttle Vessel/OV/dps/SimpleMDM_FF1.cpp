/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/07/11   GLS
2021/01/20   GLS
2021/02/16   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/28   GLS
2022/05/24   GLS
2022/05/29   GLS
2022/06/03   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/07/02   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/09   GLS
2022/10/11   GLS
2022/10/12   GLS
2022/10/13   GLS
********************************************/
#include "SimpleMDM_FF1.h"
#include "SimpleShuttleBus.h"
#include "../gnc/RA.h"
#include <cassert>


namespace dps
{
	SimpleMDM_FF1::SimpleMDM_FF1( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_FF1" ),
		powered(true)
	{
	}

	SimpleMDM_FF1::~SimpleMDM_FF1()
	{
	}

	void SimpleMDM_FF1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 0 );
		Power2.Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "RDRALTM", 16 );
		dipIOM12[0][13].Connect( pBundle, 0 );// RADAR ALTM LH DISPLAY SEL NO. 1
		// TODO RADAR ALTM LH DISPLAY SEL NO. 2

		pBundle = BundleManager()->CreateBundle( "CDR_TRIM_BF_EM", 16 );
		dipIOM12[1][8].Connect( pBundle, 0 );// 0: F3 CDR TRIM RHC/PNL inh
		dipIOM12[0][1].Connect( pBundle, 2 );// 2: L2 CDR PITCH TRIM up
		dipIOM12[0][2].Connect( pBundle, 3 );// 3: L2 CDR PITCH TRIM down
		dipIOM12[0][3].Connect( pBundle, 4 );// 4: L2 CDR ROLL TRIM right
		dipIOM12[0][4].Connect( pBundle, 5 );// 5: L2 CDR ROLL TRIM left
		dipIOM12[0][5].Connect( pBundle, 6 );// 6: L2 CDR YAW TRIM right
		dipIOM12[0][6].Connect( pBundle, 7 );// 7: L2 CDR YAW TRIM left
		dipIOM4[0][4].Connect( pBundle, 8 );// 8: L2 CDR BODY FLAP down
		dipIOM4[0][3].Connect( pBundle, 9 );// 9: L2 CDR BODY FLAP up
		dipIOM4[2][3].Connect( pBundle, 10 );// 10: L2 ENTRY MODE no y jet
		dipIOM9[1][3].Connect( pBundle, 11 );// 11: L2 ENTRY MODE lo gain

		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_A", 16 );
		dipIOM6[1][1].Connect( pBundle, 9 );// LH_RHC_PLUS_PITCH_TRIM_A
		dipIOM6[1][2].Connect( pBundle, 11 );// LH_RHC_MINUS_PITCH_TRIM_A
		dipIOM6[1][3].Connect( pBundle, 13 );// LH_RHC_PLUS_ROLL_TRIM_A
		dipIOM6[1][4].Connect( pBundle, 15 );// LH_RHC_MINUS_ROLL_TRIM_A

		pBundle = BundleManager()->CreateBundle( "C3_LIMITS_SSMEPB", 6 );
		dipIOM4[0][5].Connect( pBundle, 4 );// 5-MPS ME-1 SHUTDOWN CMD A

		pBundle = BundleManager()->CreateBundle( "C3_SEP", 6 );
		dipIOM6[1][5].Connect( pBundle, 0 );// AUTO
		dipIOM6[1][6].Connect( pBundle, 1 );// MAN/AUTO
		dipIOM6[1][7].Connect( pBundle, 2 );// SEP
		dipIOM15[1][7].Connect( pBundle, 3 );// AUTO
		dipIOM15[1][5].Connect( pBundle, 4 );// MAN
		dipIOM15[1][6].Connect( pBundle, 5 );// SEP

		pBundle = BundleManager()->CreateBundle( "MPSDUMP_LH2UP_R2_SWITCHES", 5 );
		dipIOM9[2][8].Connect( pBundle, 1 );// MPS PRPLT DUMP SEQUENCE START A
		dipIOM9[2][9].Connect( pBundle, 0 );// MPS PRPLT DUMP SEQUENCE STOP A

		pBundle = BundleManager()->CreateBundle( "FwdEventTimer_A", 16 );
		dopIOM5[1][0].Connect( pBundle, 6 );// 0-FWD EVENT TIMER: ABORT TIMER_RESET

		pBundle = BundleManager()->CreateBundle( "ACA1_1", 16 );
		dopIOM2[2][3].Connect( pBundle, 2 );// 3-C3 LIGHT: FWD DAP CONTROL "MAN"
		dopIOM2[1][15].Connect( pBundle, 6 );// 15-C3 LIGHT: FWD DAP RCS JETS "NORM"
		dopIOM2[2][5].Connect( pBundle, 10 );// 5-C3 LIGHT: FWD DAP RCS JETS "VERN"

		pBundle = BundleManager()->CreateBundle( "ACA1_2", 16 );
		dopIOM10[1][1].Connect( pBundle, 2 );// 1-C3 LIGHT: FWD MAN ROT ROLL "DISC RT"
		dopIOM10[1][4].Connect( pBundle, 6 );// 4-C3 LIGHT: FWD MAN ROT PITCH "DISC RT"
		dopIOM10[0][6].Connect( pBundle, 8 );// 6-F2 LIGHT: LH FCS PITCH "AUTO"
		dopIOM10[1][7].Connect( pBundle, 10 );// 7-C3 LIGHT: FWD MAN ROT YAW "DISC RT"

		pBundle = BundleManager()->CreateBundle( "ACA1_3", 16 );
		dopIOM10[1][2].Connect( pBundle, 2 );// 2-C3 LIGHT: FWD MAN ROT ROLL "ACCEL"
		dopIOM10[1][5].Connect( pBundle, 6 );// 5-C3 LIGHT: FWD MAN ROT PITCH "ACCEL"
		dopIOM10[0][7].Connect( pBundle, 4 );// 7-F2 LIGHT: LH FCS ROLL/YAW "AUTO"
		dopIOM10[1][8].Connect( pBundle, 10 );// 8-C3 LIGHT: FWD MAN ROT YAW "ACCEL"

		pBundle = BundleManager()->CreateBundle( "ACA1_4", 16 );
		dopIOM10[0][5].Connect( pBundle, 0 );// 5-F2 LIGHT: LH FCS SPEED BK "AUTO"
		dopIOM10[1][3].Connect( pBundle, 2 );// 3-C3 LIGHT: FWD MAN ROT ROLL "PULSE"
		dopIOM10[1][6].Connect( pBundle, 6 );// 6-C3 LIGHT: FWD MAN ROT PITCH "PULSE"
		dopIOM10[0][4].Connect( pBundle, 8 );// 4-F2 LIGHT: LH FCS BODY FLAP "AUTO"
		dopIOM10[1][9].Connect( pBundle, 10 );// 9-C3 LIGHT: FWD MAN ROT YAW "PULSE"

		pBundle = BundleManager()->CreateBundle( "ACA3_1", 16 );
		dopIOM2[1][14].Connect( pBundle, 2 );// 14-C3 LIGHT: FWD DAP SELECT "A"
		dopIOM2[2][4].Connect( pBundle, 6 );// 4-C3 LIGHT: FWD DAP SELECT "B"
		dopIOM2[1][13].Connect( pBundle, 10 );// 13-C3 LIGHT: FWD DAP CONTROL "AUTO"
		dopIOM10[1][0].Connect( pBundle, 14 );// 0-F7 LIGHT: C MPS RED STATUS

		pBundle = BundleManager()->CreateBundle( "ACA3_2", 16 );
		dopIOM10[1][12].Connect( pBundle, 2 );// 12-C3 LIGHT: FWD MAN TRANS X "LVLH"
		dopIOM10[1][15].Connect( pBundle, 6 );// 15-C3 LIGHT: FWD MAN TRANS Y "LOW Z"
		dopIOM10[2][2].Connect( pBundle, 10 );// 2-C3 LIGHT: FWD MAN TRANS Z "HIGH"
		dopIOM2[1][0].Connect( pBundle, 14 );// 0-F7 LIGHT: C MPS AMBER STATUS

		pBundle = BundleManager()->CreateBundle( "ACA3_3", 16 );
		dopIOM2[1][7].Connect( pBundle, 0 );// 7-F6 LIGHT A: RCS CMD "ROLL LEFT"
		dopIOM10[1][10].Connect( pBundle, 2 );// 10-C3 LIGHT: FWD MAN TRANS X "NORM"
		dopIOM2[1][8].Connect( pBundle, 4 );// 8-F6 LIGHT A: RCS CMD "ROLL RIGHT"
		dopIOM10[1][13].Connect( pBundle, 6 );// 13-C3 LIGHT: FWD MAN TRANS Y "NORM"
		dopIOM2[1][11].Connect( pBundle, 8 );// 11-F6 LIGHT A: RCS CMD "PITCH UP"
		dopIOM10[2][0].Connect( pBundle, 10 );// 0-C3 LIGHT: FWD MAN TRANS Z "NORM"
		dopIOM2[1][12].Connect( pBundle, 12 );// 12-F6 LIGHT A: RCS CMD "PITCH DOWN"

		pBundle = BundleManager()->CreateBundle( "ACA3_4", 16 );
		dopIOM2[1][9].Connect( pBundle, 0 );// 9-F6 LIGHT A: RCS CMD "YAW LEFT"
		dopIOM10[1][11].Connect( pBundle, 2 );// 11-C3 LIGHT: FWD MAN TRANS X "PULSE"
		dopIOM2[1][10].Connect( pBundle, 4 );// 10-F6 LIGHT A: RCS CMD "YAW RIGHT"
		dopIOM10[1][14].Connect( pBundle, 6 );// 14-C3 LIGHT: FWD MAN TRANS Y "PULSE"
		dopIOM10[2][1].Connect( pBundle, 10 );// 1-C3 LIGHT: FWD MAN TRANS Z "PULSE"

		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_B", 16 );
		dipIOM6[0][7].Connect( pBundle, 14 );// 7-FWD THC POS X OUTPUT - A
		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_C", 16 );
		dipIOM6[0][8].Connect( pBundle, 1 );// 8-FWD THC NEG X OUTPUT - A
		dipIOM6[0][9].Connect( pBundle, 4 );// 9-FWD THC POS Y OUTPUT - A
		dipIOM6[0][10].Connect( pBundle, 7 );// 10-FWD THC NEG Y OUTPUT - A
		dipIOM6[0][11].Connect( pBundle, 10 );// 11-FWD THC POS Z OUTPUT - A
		dipIOM6[0][12].Connect( pBundle, 13 );// 12-FWD THC NEG Z OUTPUT - A

		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_B", 16 );
		dipIOM15[0][7].Connect( pBundle, 14 );// 7-AFT THC POS X OUTPUT - A
		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_C", 16 );
		dipIOM15[0][8].Connect( pBundle, 1 );// 8-AFT THC NEG X OUTPUT - A
		dipIOM15[0][9].Connect( pBundle, 4 );// 9-AFT THC POS Y OUTPUT - A
		dipIOM15[0][10].Connect( pBundle, 7 );// 10-AFT THC NEG Y OUTPUT - A
		dipIOM15[0][11].Connect( pBundle, 10 );// 11-AFT THC POS Z OUTPUT - A
		dipIOM15[0][12].Connect( pBundle, 13 );// 12-AFT THC NEG Z OUTPUT - A

		pBundle = BundleManager()->CreateBundle( "LeftSBTC", 16 );
		dipIOM6[0][13].Connect( pBundle, 3 );// 13-LH SBTC TAKEOVER - A

		pBundle = BundleManager()->CreateBundle( "ADI_Switches_A6U", 16 );
		dipIOM9[1][1].Connect( pBundle, 7 );// 1-SENSE SW -Z CON A
		dipIOM9[1][2].Connect( pBundle, 6 );// 2-SENSE SW -X CON A

		pBundle = BundleManager()->CreateBundle( "DAP_CH_CONTROLS", 16 );
		dipIOM4[1][10].Connect( pBundle, 0 );// 10-FCS LH PITCH AUTO MODE A
		dipIOM4[1][11].Connect( pBundle, 2 );// 11-FCS LH PITCH CSS MODE A
		dipIOM4[1][13].Connect( pBundle, 4 );// 13-FCS LH R-Y AUTO MODE A
		dipIOM4[1][14].Connect( pBundle, 6 );// 14-FCS LH R-Y CSS MODE A
		dipIOM4[2][0].Connect( pBundle, 8 );// 0-LH SPD BK/THROT AUTO/MAN A
		dipIOM4[1][15].Connect( pBundle, 10 );// 15-LH BODY FLAP AUTO/MANUAL A

		pBundle = BundleManager()->CreateBundle( "DAP_PBI_FWD_1", 16 );
		dipIOM9[0][4].Connect( pBundle, 0 );// 4-FWD DAP SELECT A - A
		dipIOM9[0][5].Connect( pBundle, 1 );// 5-FWD DAP SELECT B - A
		dipIOM9[0][8].Connect( pBundle, 2 );// 8-FWD DAP AUTO A
		dipIOM9[0][9].Connect( pBundle, 3 );// 9-FWD DAP MAN A
		dipIOM9[1][13].Connect( pBundle, 4 );// 13-FWD RCS JETS NORM A
		dipIOM9[1][14].Connect( pBundle, 5 );// 14-FWD RCS JETS VERNIER A
		dipIOM9[2][1].Connect( pBundle, 6 );// 1-FWD TRANSLATION X LVLH A
		dipIOM9[2][4].Connect( pBundle, 7 );// 4-FWD TRANSLATION Y LOW Z A
		dipIOM9[2][7].Connect( pBundle, 8 );// 7-FWD TRANSLATION Z HIGH A
		dipIOM9[1][4].Connect( pBundle, 9 );// 4-FWD ROTATION ROLL DISC RATE A
		dipIOM9[1][7].Connect( pBundle, 10 );// 7-FWD ROTATION PITCH DISC RATE A
		dipIOM9[1][10].Connect( pBundle, 11 );// 10-FWD ROTATION YAW DISC RATE A
		dipIOM9[1][15].Connect( pBundle, 12 );// 15-FWD TRANSLATION X NORM A
		dipIOM9[2][2].Connect( pBundle, 13 );// 2-FWD TRANSLATION Y NORM A
		dipIOM9[2][5].Connect( pBundle, 14 );// 5-FWD TRANSLATION Z NORM A
		dipIOM9[1][5].Connect( pBundle, 15 );// 5-FWD ROTATION ROLL ACCEL A
		pBundle = BundleManager()->CreateBundle( "DAP_PBI_FWD_2", 16 );
		dipIOM9[1][8].Connect( pBundle, 0 );// 8-FWD ROTATION PITCH ACCEL A
		dipIOM9[1][11].Connect( pBundle, 1 );// 11-FWD ROTATION YAW ACCEL A
		dipIOM9[2][0].Connect( pBundle, 2 );// 0-FWD TRANSLATION X PULSE A
		dipIOM9[2][3].Connect( pBundle, 3 );// 3-FWD TRANSLATION Y PULSE A
		dipIOM9[2][6].Connect( pBundle, 4 );// 6-FWD TRANSLATION Z PULSE A
		dipIOM9[1][6].Connect( pBundle, 5 );// 6-FWD ROTATION ROLL PULSE A
		dipIOM9[1][9].Connect( pBundle, 6 );// 9-FWD ROTATION PITCH PULSE A
		dipIOM9[1][12].Connect( pBundle, 7 );// 12-FWD ROTATION YAW PULSE A

		pBundle = BundleManager()->CreateBundle( "DAP_PBI_AFT_1", 16 );
		dipIOM9[0][6].Connect( pBundle, 0 );// 6-AFT DAP SELECT A - C
		dipIOM9[0][7].Connect( pBundle, 1 );// 7-AFT DAP SELECT B - C
		dipIOM9[0][10].Connect( pBundle, 2 );// 10-AFT DAP AUTO C
		dipIOM9[0][11].Connect( pBundle, 3 );// 11-AFT DAP MAN C
		dipIOM12[2][14].Connect( pBundle, 4 );// 14-AFT RCS OPTIONS NORM C
		dipIOM12[2][15].Connect( pBundle, 5 );// 15-AFT RCS OPTIONS VERNIER C

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
		dipIOM4[2][9].Connect( pBundle, 9 );// LH_VENT_6_CLOSE_1
		dipIOM4[2][10].Connect( pBundle, 10 );// LH_VENT_6_OPEN_1
		dipIOM4[2][11].Connect( pBundle, 11 );// LH_VENT_6_PURGE_1_IND_1
		dipIOM12[2][8].Connect( pBundle, 12 );// LH_VENT_6_PURGE_2_IND_1

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
		dipIOM4[2][6].Connect( pBundle, 0 );// R_VENTS_1_AND_2_CLOSE_1
		dipIOM4[2][7].Connect( pBundle, 1 );// R_VENTS_1_AND_2_OPEN_1
		dipIOM4[2][8].Connect( pBundle, 2 );// R_VENTS_1_AND_2_PURGE_1_IND_1
		dipIOM4[2][12].Connect( pBundle, 3 );// RH_VENT_3_CLOSE_1
		dipIOM4[2][13].Connect( pBundle, 4 );// RH_VENT_3_OPEN_1
		dipIOM4[2][14].Connect( pBundle, 7 );// RH_VENT_5_CLOSE_1
		dipIOM4[2][15].Connect( pBundle, 8 );// RH_VENT_5_OPEN_1

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
		dipIOM4[2][4].Connect( pBundle, 5 );// RH_VENTS_4_AND_7_CLOSE_2
		dipIOM4[2][5].Connect( pBundle, 6 );// RH_VENTS_4_AND_7_OPEN_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1A", 16 );
		dopIOM10[2][11].Connect( pBundle, 9 );// LH_VENT_6_MOTOR_1_OPEN_A
		dopIOM10[2][10].Connect( pBundle, 10 );// LH_VENT_6_MOTOR_1_CLOSE_A
		dopIOM10[2][12].Connect( pBundle, 11 );// LH_VENT_6_MOTOR_1_PRG_1_A
		dopIOM10[2][13].Connect( pBundle, 12 );// LH_VENT_6_MOTOR_1_PRG_2_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1B", 16 );
		dopIOM2[2][11].Connect( pBundle, 9 );// LH_VENT_6_MOTOR_1_OPEN_B
		dopIOM2[2][10].Connect( pBundle, 10 );// LH_VENT_6_MOTOR_1_CLOSE_B
		dopIOM2[2][12].Connect( pBundle, 11 );// LH_VENT_6_MOTOR_1_PRG_1_B
		dopIOM2[2][13].Connect( pBundle, 12 );// LH_VENT_6_MOTOR_1_PRG_2_B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1A", 16 );
		dopIOM10[0][1].Connect( pBundle, 0 );// RH_VENTS_1_2_MOTOR_1_OPEN_A
		dopIOM10[0][0].Connect( pBundle, 1 );// RH_VENTS_1_2_MOTOR_1_CLOSE_A
		dopIOM10[0][2].Connect( pBundle, 2 );// RH_VENTS_1_2_MOTOR_1_PURGE_A
		dopIOM10[2][9].Connect( pBundle, 3 );// RH_VENT_3_MOTOR_1_OPEN_A
		dopIOM10[2][8].Connect( pBundle, 4 );// RH_VENT_3_MOTOR_1_CLOSE_A
		dopIOM10[2][15].Connect( pBundle, 7 );// RH_VENT_5_MOTOR_1_OPEN_A
		dopIOM10[2][14].Connect( pBundle, 8 );// RH_VENT_5_MOTOR_1_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1B", 16 );
		dopIOM2[0][1].Connect( pBundle, 0 );// RH_VENTS_1_2_MOTOR_1_OPEN_B
		dopIOM2[0][0].Connect( pBundle, 1 );// RH_VENTS_1_2_MOTOR_1_CLOSE_B
		dopIOM2[0][2].Connect( pBundle, 2 );// RH_VENTS_1_2_MOTOR_1_PURGE_B
		dopIOM2[2][9].Connect( pBundle, 3 );// RH_VENT_3_MOTOR_1_OPEN_B
		dopIOM2[2][8].Connect( pBundle, 4 );// RH_VENT_3_MOTOR_1_CLOSE_B
		dopIOM2[2][15].Connect( pBundle, 7 );// RH_VENT_5_MOTOR_1_OPEN_B
		dopIOM2[2][14].Connect( pBundle, 8 );// RH_VENT_5_MOTOR_1_CLOSE_B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2A", 16 );
		dopIOM10[2][7].Connect( pBundle, 5 );// RH_VENTS_4_7_MOTOR_2_OPEN_A
		dopIOM10[2][6].Connect( pBundle, 6 );// RH_VENTS_4_7_MOTOR_2_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2B", 16 );
		dopIOM2[2][7].Connect( pBundle, 5 );// RH_VENTS_4_7_MOTOR_2_OPEN_B
		dopIOM2[0][11].Connect( pBundle, 6 );// RH_VENTS_4_7_MOTOR_2_CLOSE_B

		pBundle = BundleManager()->CreateBundle( "GPC_CW_CMD_A", 16 );
		dopIOM10[2][3].Connect( pBundle, 0 );// BU_CW_A_CMD_1
		dopIOM10[2][5].Connect( pBundle, 4 );// SM_LIGHT_A_CMD_1
		dopIOM10[2][4].Connect( pBundle, 8 );// SM_TONE_A_CMD_1

		pBundle = BundleManager()->CreateBundle( "GPC_CW_DATA", 16 );
		dopIOM5[1][11].Connect( pBundle, 11 );// 11-C&W MATRIX "LEFT RCS" (LEAK DETECT)

		pBundle = BundleManager()->CreateBundle( "SPI_DRIVE_SIGNALS", 16 );
		//dopIOM8_HI[7].Connect( pBundle, 7 );// Body Flap Position
		//dopIOM8_HI[8].Connect( pBundle, 8 );// Aileron Position
		dopIOM8_HI[7].Connect( pBundle, 2 );// Speed Brake Command Position
		dopIOM8_HI[8].Connect( pBundle, 0 );// Rudder Position
		dopIOM8_HI[9].Connect( pBundle, 1 );// Speed Brake Position
		dopIOM8_HI[10].Connect( pBundle, 3 );// Left Inboard Elevon Position
		dopIOM8_HI[11].Connect( pBundle, 4 );// Left Outboard Elevon Position
		dopIOM8_HI[12].Connect( pBundle, 5 );// Right Inboard Elevon Position
		dopIOM8_HI[13].Connect( pBundle, 6 );// Right Outboard Elevon Position

		pBundle = BundleManager()->CreateBundle( "MPS_ENGINE_PC", 3 );
		dopIOM8_HI[0].Connect( pBundle, 0 );// MPS Center Engine Chamber Pressure
		//dopIOM8_HI[0].Connect( pBundle, 1 );// MPS Left Engine Chamber Pressure
		//dopIOM8_HI[0].Connect( pBundle, 2 );// MPS Right Engine Chamber Pressure

		pRA1 = dynamic_cast<gnc::RadarAltimeter*>(director->GetSubsystemByName( "RA1" ));
		assert( (pRA1 != NULL) && "SimpleMDM_FF1::Realize.pRA1" );
		return;
	}

	void SimpleMDM_FF1::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_FF1::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		if (!ReadEna) return;
		if (cw.MIAaddr != GetAddr()) return;

		unsigned short modecontrol = (cw.payload >> 9) & 0xF;
		unsigned short IOMaddr = (cw.payload >> 5) & 0xF;
		unsigned short IOMch = cw.payload & 0x1F;
		unsigned short IOMdata = 0;
		switch (modecontrol)
		{
			case 0b1000:// direct mode output (GPC-to-MDM)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 TAC
						IOMdata = cdw[0].payload;
						IOM_TAC( 0b001, IOMch, IOMdata, pRA1 );
						break;
					case 0b0001:// IOM 1 AID
						break;
					case 0b0010:// IOM 2 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM2 );
						break;
					case 0b0011:// IOM 3 SIO
						break;
					case 0b0100:// IOM 4 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM4 );
						break;
					case 0b0101:// IOM 5 DOL
						IOMdata = cdw[0].payload;
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM5 );
						break;
					case 0b0110:// IOM 6 DIL
						IOMdata = cdw[0].payload;
						IOM_DIL( 0b001, IOMch, IOMdata, dipIOM6 );
						break;
					case 0b0111:// IOM 7 AIS
						break;
					case 0b1000:// IOM 8 AOD
						IOMdata = cdw[0].payload;
						IOM_AOD( 0b001, IOMch, IOMdata, dopIOM8_HI, dopIOM8_LO );
						break;
					case 0b1001:// IOM 9 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM9 );
						break;
					case 0b1010:// IOM 10 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM10 );
						break;
					case 0b1011:// IOM 11 SIO
						break;
					case 0b1100:// IOM 12 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM12 );
						break;
					case 0b1101:// IOM 13 DOL
						IOMdata = cdw[0].payload;
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM13 );
						break;
					case 0b1110:// IOM 14 AID
						break;
					case 0b1111:// IOM 15 DIL
						IOMdata = cdw[0].payload;
						IOM_DIL( 0b001, IOMch, IOMdata, dipIOM15 );
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 TAC
						{
							IOM_TAC( 0b000, IOMch, IOMdata, pRA1 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0001:// IOM 1 AID
						break;
					case 0b0010:// IOM 2 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM2 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0011:// IOM 3 SIO
						break;
					case 0b0100:// IOM 4 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM4 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0101:// IOM 5 DOL
						{
							IOM_DOL( 0b000, IOMch, IOMdata, dopIOM5 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0110:// IOM 6 DIL
						{
							IOM_DIL( 0b000, IOMch, IOMdata, dipIOM6 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0111:// IOM 7 AIS
						break;
					case 0b1000:// IOM 8 AOD
						{
							IOM_AOD( 0b000, IOMch, IOMdata, dopIOM8_HI, dopIOM8_LO );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1001:// IOM 9 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM9 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1010:// IOM 10 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM10 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1011:// IOM 11 SIO
						break;
					case 0b1100:// IOM 12 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM12 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1101:// IOM 13 DOL
						{
							IOM_DOL( 0b000, IOMch, IOMdata, dopIOM13 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1110:// IOM 14 AID
						break;
					case 0b1111:// IOM 15 DIL
						{
							IOM_DIL( 0b000, IOMch, IOMdata, dipIOM15 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
				}
				break;
		}
		return;
	}

	void SimpleMDM_FF1::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power1.IsSet() && !Power2.IsSet())
		{
			if (powered)
			{
				// power loss -> set outputs to 0
				for (int ch = 0; ch < 3; ch++)
				{
					for (int bt = 0; bt < 16; bt++)
					{
						dopIOM2[ch][bt].ResetLine();
						dopIOM5[ch][bt].ResetLine();
						dopIOM10[ch][bt].ResetLine();
						dopIOM13[ch][bt].ResetLine();
					}
				}

				for (int ch = 0; ch < 16; ch++)
				{
					dopIOM8_HI[ch].ResetLine();
					dopIOM8_LO[ch].ResetLine();
				}
			}
			powered  = false;
		}
		else
		{
			powered = true;
		}
		return;
	}
}
