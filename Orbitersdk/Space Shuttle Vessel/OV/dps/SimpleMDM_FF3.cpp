/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/07/11   GLS
2021/06/13   GLS
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
2022/07/01   GLS
2022/08/05   GLS
********************************************/
#include "SimpleMDM_FF3.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_FF3::SimpleMDM_FF3( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_FF3" ),
		powered(true)
	{
	}

	SimpleMDM_FF3::~SimpleMDM_FF3()
	{
	}

	void SimpleMDM_FF3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 2 );
		Power2.Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "PLT_TRIM_BF", 16 );
		dipIOM12[1][8].Connect( pBundle, 0 );// 0: F3 PLT TRIM RHC/PNL inh
		dipIOM12[0][1].Connect( pBundle, 2 );// 2: C3 PLT PITCH TRIM up
		dipIOM12[0][2].Connect( pBundle, 3 );// 3: C3 PLT PITCH TRIM down
		dipIOM12[0][3].Connect( pBundle, 4 );// 4: C3 PLT ROLL TRIM right
		dipIOM12[0][4].Connect( pBundle, 5 );// 5: C3 PLT ROLL TRIM left
		dipIOM12[0][5].Connect( pBundle, 6 );// 6: C3 PLT YAW TRIM right
		dipIOM12[0][6].Connect( pBundle, 7 );// 7: C3 PLT YAW TRIM left
		dipIOM4[0][4].Connect( pBundle, 8 );// 8: C3 PLT BODY FLAP down
		dipIOM4[0][3].Connect( pBundle, 9 );// 9: C3 PLT BODY FLAP up

		pBundle = BundleManager()->CreateBundle( "RightRHC_A", 16 );
		dipIOM15[1][1].Connect( pBundle, 9 );// RH_RHC_PLUS_PITCH_TRIM_A
		dipIOM15[1][2].Connect( pBundle, 11 );// RH_RHC_MINUS_PITCH_TRIM_A
		dipIOM15[1][3].Connect( pBundle, 13 );// RH_RHC_PLUS_ROLL_TRIM_A
		dipIOM15[1][4].Connect( pBundle, 15 );// RH_RHC_MINUS_ROLL_TRIM_A

		pBundle = BundleManager()->CreateBundle( "C3_LIMITS_SSMEPB", 6 );
		dipIOM4[2][3].Connect( pBundle, 0 );// 3-MPS ENG LIMIT CONTROL NO. 2 AUTO
		dipIOM4[2][2].Connect( pBundle, 1 );// 2-MPS ENG LIMIT CONTROL NO. 2 INHIBIT
		dipIOM4[2][1].Connect( pBundle, 2 );// 1-MPS ENG LIMIT CONTROL NO. 2 ENABLE
		dipIOM9[1][0].Connect( pBundle, 3 );// 0-MPS ME-2 SHUTDOWN CMD B
		dipIOM4[0][5].Connect( pBundle, 5 );// 5-MPS ME-3 SHUTDOWN CMD A

		pBundle = BundleManager()->CreateBundle( "C3_SEP", 6 );
		dipIOM6[1][5].Connect( pBundle, 0 );// AUTO
		dipIOM6[1][6].Connect( pBundle, 1 );// MAN/AUTO
		dipIOM6[1][7].Connect( pBundle, 2 );// SEP
		dipIOM15[1][7].Connect( pBundle, 3 );// AUTO
		dipIOM15[1][5].Connect( pBundle, 4 );// MAN
		dipIOM15[1][6].Connect( pBundle, 5 );// SEP

		pBundle = BundleManager()->CreateBundle( "MPSDUMP_LH2UP_R2_SWITCHES", 5 );
		dipIOM9[2][8].Connect( pBundle, 3 );// MPS BACKUP LH2 PRPLT DUMP START A
		dipIOM9[2][9].Connect( pBundle, 2 );// MPS BACKUP LH2 PRPLT DUMP STOP A

		pBundle = BundleManager()->CreateBundle( "ACA2_2", 16 );
		dopIOM10[0][6].Connect( pBundle, 10 );// 6-F4 LIGHT: RH FCS PITCH "AUTO"

		pBundle = BundleManager()->CreateBundle( "ACA2_3", 16 );
		dopIOM2[1][7].Connect( pBundle, 0 );// 7-F6 LIGHT B: RCS CMD "ROLL LEFT"
		dopIOM2[1][8].Connect( pBundle, 4 );// 8-F6 LIGHT B: RCS CMD "ROLL RIGHT"
		dopIOM10[0][7].Connect( pBundle, 6 );// 7-F4 LIGHT: RH FCS ROLL/YAW "AUTO"
		dopIOM2[1][11].Connect( pBundle, 8 );// 11-F6 LIGHT B: RCS CMD "PITCH UP"
		dopIOM2[1][12].Connect( pBundle, 12 );// 12-F6 LIGHT B: RCS CMD "PITCH DOWN"

		pBundle = BundleManager()->CreateBundle( "ACA2_4", 16 );
		dopIOM2[1][9].Connect( pBundle, 0 );// 9-F6 LIGHT B: RCS CMD "YAW LEFT"
		dopIOM10[0][5].Connect( pBundle, 2 );// 5-F4 LIGHT: RH FCS SPEED BK "AUTO"
		dopIOM2[1][10].Connect( pBundle, 4 );// 10-F6 LIGHT B: RCS CMD "YAW RIGHT"
		dopIOM10[0][4].Connect( pBundle, 10 );// 4-F4 LIGHT: RH FCS BODY FLAP "AUTO"
		dopIOM10[1][0].Connect( pBundle, 14 );// 0-F7 LIGHT: R MPS RED STATUS

		pBundle = BundleManager()->CreateBundle( "ACA2_5", 16 );
		dopIOM2[1][0].Connect( pBundle, 10 );// 0-F7 LIGHT: R MPS AMBER STATUS

		pBundle = BundleManager()->CreateBundle( "ACA4_1", 16 );
		dopIOM2[1][14].Connect( pBundle, 0 );// 14-A6 LIGHT: AFT DAP SELECT "A"
		dopIOM2[2][4].Connect( pBundle, 4 );// 4-A6 LIGHT: AFT DAP SELECT "B"
		dopIOM2[1][13].Connect( pBundle, 8 );// 13-A6 LIGHT: AFT DAP CONTROL "AUTO"

		pBundle = BundleManager()->CreateBundle( "ACA4_2", 16 );
		dopIOM10[1][12].Connect( pBundle, 0 );// 12-A6 LIGHT: AFT MAN TRANS X "LVLH"
		dopIOM10[1][15].Connect( pBundle, 4 );// 15-A6 LIGHT: AFT MAN TRANS Y "LOW Z"
		dopIOM10[2][2].Connect( pBundle, 8 );// 2-A6 LIGHT: AFT MAN TRANS Z "HIGH"

		pBundle = BundleManager()->CreateBundle( "ACA4_3", 16 );
		dopIOM10[1][10].Connect( pBundle, 0 );// 10-A6 LIGHT: AFT MAN TRANS X "NORM"
		dopIOM10[1][13].Connect( pBundle, 4 );// 13-A6 LIGHT: AFT MAN TRANS Y "NORM"
		dopIOM10[2][0].Connect( pBundle, 8 );// 0-A6 LIGHT: AFT MAN TRANS Z "NORM"

		pBundle = BundleManager()->CreateBundle( "ACA4_4", 16 );
		dopIOM10[1][11].Connect( pBundle, 0 );// 11-A6 LIGHT: AFT MAN TRANS X "PULSE"
		dopIOM10[1][14].Connect( pBundle, 4 );// 14-A6 LIGHT: AFT MAN TRANS Y "PULSE"
		dopIOM10[2][1].Connect( pBundle, 8 );// 1-A6 LIGHT: AFT MAN TRANS Z "PULSE"

		pBundle = BundleManager()->CreateBundle( "ACA5_1", 16 );
		dopIOM2[2][3].Connect( pBundle, 0 );// 3-A6 LIGHT: AFT DAP CONTROL "MAN"
		dopIOM2[1][15].Connect( pBundle, 4 );// 15-A6 LIGHT: AFT DAP RCS JETS "NORM"
		dopIOM2[2][5].Connect( pBundle, 8 );// 5-A6 LIGHT: AFT DAP RCS JETS "VERN"

		pBundle = BundleManager()->CreateBundle( "ACA5_2", 16 );
		dopIOM10[1][1].Connect( pBundle, 0 );// 1-A6 LIGHT: AFT MAN ROT ROLL "DISC RT"
		dopIOM10[1][4].Connect( pBundle, 4 );// 4-A6 LIGHT: AFT MAN ROT PITCH "DISC RT"
		dopIOM10[1][7].Connect( pBundle, 8 );// 7-A6 LIGHT: AFT MAN ROT YAW "DISC RT"

		pBundle = BundleManager()->CreateBundle( "ACA5_3", 16 );
		dopIOM10[1][2].Connect( pBundle, 0 );// 2-A6 LIGHT: AFT MAN ROT ROLL "ACCEL"
		dopIOM10[1][5].Connect( pBundle, 4 );// 5-A6 LIGHT: AFT MAN ROT PITCH "ACCEL"
		dopIOM10[1][8].Connect( pBundle, 8 );// 8-A6 LIGHT: AFT MAN ROT YAW "ACCEL"

		pBundle = BundleManager()->CreateBundle( "ACA5_4", 16 );
		dopIOM10[1][3].Connect( pBundle, 0 );// 3-A6 LIGHT: AFT MAN ROT ROLL "PULSE"
		dopIOM10[1][6].Connect( pBundle, 4 );// 6-A6 LIGHT: AFT MAN ROT PITCH "PULSE"
		dopIOM10[1][9].Connect( pBundle, 8 );// 9-A6 LIGHT: AFT MAN ROT YAW "PULSE"

		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_C", 16 );
		dipIOM6[0][7].Connect( pBundle, 0 );// 7-FWD THC POS X OUTPUT - C
		dipIOM6[0][8].Connect( pBundle, 3 );// 8-FWD THC NEG X OUTPUT - C
		dipIOM6[0][9].Connect( pBundle, 6 );// 9-FWD THC POS Y OUTPUT - C
		dipIOM6[0][10].Connect( pBundle, 9 );// 10-FWD THC NEG Y OUTPUT - C
		dipIOM6[0][11].Connect( pBundle, 12 );// 11-FWD THC POS Z OUTPUT - C
		dipIOM6[0][12].Connect( pBundle, 15 );// 12-FWD THC NEG Z OUTPUT - C

		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_C", 16 );
		dipIOM15[0][7].Connect( pBundle, 0 );// 7-AFT THC POS X OUTPUT - C
		dipIOM15[0][8].Connect( pBundle, 3 );// 8-AFT THC NEG X OUTPUT - C
		dipIOM15[0][9].Connect( pBundle, 6 );// 9-AFT THC POS Y OUTPUT - C
		dipIOM15[0][10].Connect( pBundle, 9 );// 10-AFT THC NEG Y OUTPUT - C
		dipIOM15[0][11].Connect( pBundle, 12 );// 11-AFT THC POS Z OUTPUT - C
		dipIOM15[0][12].Connect( pBundle, 15 );// 12-AFT THC NEG Z OUTPUT - C

		pBundle = BundleManager()->CreateBundle( "LeftSBTC", 16 );
		dipIOM6[0][13].Connect( pBundle, 5 );// 13-LH SBTC TAKEOVER - C
		pBundle = BundleManager()->CreateBundle( "RightSBTC", 16 );
		dipIOM15[0][13].Connect( pBundle, 4 );// 13-RH SBTC TAKEOVER - B

		pBundle = BundleManager()->CreateBundle( "ADI_Switches_A6U", 16 );
		dipIOM9[1][1].Connect( pBundle, 7 );// 1-SENSE SW -Z CON C
		dipIOM9[1][2].Connect( pBundle, 6 );// 2-SENSE SW -X CON C

		pBundle = BundleManager()->CreateBundle( "CDR_TRIM_BF_EM", 16 );
		dipIOM12[1][2].Connect( pBundle, 10 );// 10: L2 ENTRY MODE no y jet
		dipIOM9[1][3].Connect( pBundle, 11 );// 11: L2 ENTRY MODE lo gain

		pBundle = BundleManager()->CreateBundle( "DAP_CH_CONTROLS", 16 );
		dipIOM4[1][10].Connect( pBundle, 0 );// 10-FCS LH PITCH AUTO MODE C
		dipIOM12[1][10].Connect( pBundle, 1 );// 10-FCS RH PITCH AUTO MODE B
		dipIOM4[1][11].Connect( pBundle, 2 );// 11-FCS LH PITCH CSS MODE C
		dipIOM12[1][11].Connect( pBundle, 3 );// 11-FCS RH PITCH CSS MODE B
		dipIOM4[1][13].Connect( pBundle, 4 );// 13-FCS LH R-Y AUTO MODE C
		dipIOM12[1][13].Connect( pBundle, 5 );// 13-FCS RH R-Y AUTO MODE B
		dipIOM4[1][14].Connect( pBundle, 6 );// 14-FCS LH R-Y CSS MODE C
		dipIOM12[1][14].Connect( pBundle, 7 );// 14-FCS RH R-Y CSS MODE B
		dipIOM4[2][0].Connect( pBundle, 8 );// 0-LH SPD BK/THROT AUTO/MAN C
		dipIOM12[2][0].Connect( pBundle, 9 );// 15-RH BODY FLAP AUTO/MANUAL B
		dipIOM4[1][15].Connect( pBundle, 10 );// 15-LH BODY FLAP AUTO/MANUAL C
		dipIOM12[1][15].Connect( pBundle, 11 );// 0-RH SPD BK/THROT AUTO/MAN B

		pBundle = BundleManager()->CreateBundle( "DAP_PBI_FWD_1", 16 );
		dipIOM9[0][6].Connect( pBundle, 0 );// 6-FWD DAP SELECT A - C
		dipIOM9[0][7].Connect( pBundle, 1 );// 7-FWD DAP SELECT B - C
		dipIOM9[0][10].Connect( pBundle, 2 );// 10-FWD DAP AUTO C
		dipIOM9[0][11].Connect( pBundle, 3 );// 11-FWD DAP MAN C
		dipIOM12[2][14].Connect( pBundle, 4 );// 14-FWD RCS OPTIONS NORM C
		dipIOM12[2][15].Connect( pBundle, 5 );// 15-FWD RCS OPTIONS VERNIER C

		pBundle = BundleManager()->CreateBundle( "DAP_PBI_AFT_1", 16 );
		dipIOM9[0][4].Connect( pBundle, 0 );// 4-AFT DAP SELECT A - A
		dipIOM9[0][5].Connect( pBundle, 1 );// 5-AFT DAP SELECT B - A
		dipIOM9[0][8].Connect( pBundle, 2 );// 8-AFT DAP AUTO A
		dipIOM9[0][9].Connect( pBundle, 3 );// 9-AFT DAP MAN A
		dipIOM9[1][13].Connect( pBundle, 4 );// 13-AFT RCS JETS NORM A
		dipIOM9[1][14].Connect( pBundle, 5 );// 14-AFT RCS JETS VERNIER A
		dipIOM9[2][1].Connect( pBundle, 6 );// 1-AFT TRANSLATION X LVLH A
		dipIOM9[2][4].Connect( pBundle, 7 );// 4-AFT TRANSLATION Y LOW Z A
		dipIOM9[2][7].Connect( pBundle, 8 );// 7-AFT TRANSLATION Z HIGH A
		dipIOM9[1][4].Connect( pBundle, 9 );// 4-AFT ROTATION ROLL DISC RATE A
		dipIOM9[1][7].Connect( pBundle, 10 );// 7-AFT ROTATION PITCH DISC RATE A
		dipIOM9[1][10].Connect( pBundle, 11 );// 10-AFT ROTATION YAW DISC RATE A
		dipIOM9[1][15].Connect( pBundle, 12 );// 15-AFT TRANSLATION X NORM A
		dipIOM9[2][2].Connect( pBundle, 13 );// 2-AFT TRANSLATION Y NORM A
		dipIOM9[2][5].Connect( pBundle, 14 );// 5-AFT TRANSLATION Z NORM A
		dipIOM9[1][5].Connect( pBundle, 15 );// 5-AFT ROTATION ROLL ACCEL A
		pBundle = BundleManager()->CreateBundle( "DAP_PBI_AFT_2", 16 );
		dipIOM9[1][8].Connect( pBundle, 0 );// 8-AFT ROTATION PITCH ACCEL A
		dipIOM9[1][11].Connect( pBundle, 1 );// 11-AFT ROTATION YAW ACCEL A
		dipIOM9[2][0].Connect( pBundle, 2 );// 0-AFT TRANSLATION X PULSE A
		dipIOM9[2][3].Connect( pBundle, 3 );// 3-AFT TRANSLATION Y PULSE A
		dipIOM9[2][6].Connect( pBundle, 4 );// 6-AFT TRANSLATION Z PULSE A
		dipIOM9[1][6].Connect( pBundle, 5 );// 6-AFT ROTATION ROLL PULSE A
		dipIOM9[1][9].Connect( pBundle, 6 );// 9-AFT ROTATION PITCH PULSE A
		dipIOM9[1][12].Connect( pBundle, 7 );// 12-AFT ROTATION YAW PULSE A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
		dipIOM4[2][6].Connect( pBundle, 0 );// L_VENTS_1_AND_2_CLOSE_1
		dipIOM4[2][7].Connect( pBundle, 1 );// L_VENTS_1_AND_2_OPEN_1
		dipIOM4[2][8].Connect( pBundle, 2 );// L_VENTS_1_AND_2_PURGE_1_IND_1
		dipIOM4[2][4].Connect( pBundle, 3 );// LH_VENT_3_CLOSE_1
		dipIOM4[2][5].Connect( pBundle, 4 );// LH_VENT_3_OPEN_1
		dipIOM4[2][12].Connect( pBundle, 5 );// LH_VENTS_4_AND_7_CLOSE_1
		dipIOM4[2][13].Connect( pBundle, 6 );// LH_VENTS_4_AND_7_OPEN_1
		dipIOM4[2][14].Connect( pBundle, 7 );// LH_VENT_5_CLOSE_1
		dipIOM4[2][15].Connect( pBundle, 8 );// LH_VENT_5_OPEN_1

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
		dipIOM4[2][9].Connect( pBundle, 9 );// RH_VENT_6_CLOSE_1
		dipIOM4[2][10].Connect( pBundle, 10 );// RH_VENT_6_OPEN_1
		dipIOM4[2][11].Connect( pBundle, 11 );// RH_VENT_6_PURGE_1_IND_1
		dipIOM12[2][8].Connect( pBundle, 12 );// RH_VENT_6_PURGE_2_IND_1

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1A", 16 );
		dopIOM10[0][1].Connect( pBundle, 0 );// LH_VENTS_1_2_MOTOR_1_OPEN_A
		dopIOM10[0][0].Connect( pBundle, 1 );// LH_VENTS_1_2_MOTOR_1_CLOSE_A
		dopIOM10[2][7].Connect( pBundle, 2 );// LH_VENTS_1_2_MOTOR_1_PURGE_A
		dopIOM10[0][2].Connect( pBundle, 3 );// LH_VENT_3_MOTOR_1_OPEN_A
		dopIOM10[2][6].Connect( pBundle, 4 );// LH_VENT_3_MOTOR_1_CLOSE_A
		dopIOM10[2][9].Connect( pBundle, 5 );// LH_VENTS_4_7_MOTOR_1_OPEN_A
		dopIOM10[2][8].Connect( pBundle, 6 );// LH_VENTS_4_7_MOTOR_1_CLOSE_A
		dopIOM10[2][15].Connect( pBundle, 7 );// LH_VENT_5_MOTOR_1_OPEN_A
		dopIOM10[2][14].Connect( pBundle, 8 );// LH_VENT_5_MOTOR_1_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1B", 16 );
		dopIOM2[0][1].Connect( pBundle, 0 );// LH_VENTS_1_2_MOTOR_1_OPEN_B
		dopIOM2[2][7].Connect( pBundle, 1 );// LH_VENTS_1_2_MOTOR_1_CLOSE_B
		dopIOM2[0][2].Connect( pBundle, 2 );// LH_VENTS_1_2_MOTOR_1_PURGE_B
		dopIOM2[0][0].Connect( pBundle, 3 );// LH_VENT_3_MOTOR_1_OPEN_B
		dopIOM2[2][6].Connect( pBundle, 4 );// LH_VENT_3_MOTOR_1_CLOSE_B
		dopIOM2[2][9].Connect( pBundle, 5 );// LH_VENTS_4_7_MOTOR_1_OPEN_B
		dopIOM2[1][6].Connect( pBundle, 6 );// LH_VENTS_4_7_MOTOR_1_CLOSE_B
		dopIOM2[2][15].Connect( pBundle, 7 );// LH_VENT_5_MOTOR_1_OPEN_B
		dopIOM2[2][14].Connect( pBundle, 8 );// LH_VENT_5_MOTOR_1_CLOSE_B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1A", 16 );
		dopIOM10[2][11].Connect( pBundle, 9 );// RH_VENT_6_MOTOR_1_OPEN_A
		dopIOM10[2][10].Connect( pBundle, 10 );// RH_VENT_6_MOTOR_1_CLOSE_A
		dopIOM10[2][12].Connect( pBundle, 11 );// RH_VENT_6_MOTOR_1_PRG_1_A
		dopIOM10[2][13].Connect( pBundle, 12 );// RH_VENT_6_MOTOR_1_PRG_2_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1B", 16 );
		dopIOM2[2][11].Connect( pBundle, 9 );// RH_VENT_6_MOTOR_1_OPEN_B
		dopIOM2[2][10].Connect( pBundle, 10 );// RH_VENT_6_MOTOR_1_CLOSE_B
		dopIOM2[2][12].Connect( pBundle, 11 );// RH_VENT_6_MOTOR_1_PRG_1_B
		dopIOM2[2][13].Connect( pBundle, 12 );// RH_VENT_6_MOTOR_1_PRG_2_B
		return;
	}

	void SimpleMDM_FF3::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_FF3::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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
					case 0b0000:// IOM 0 ???
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

	void SimpleMDM_FF3::OnPreStep( double simt, double simdt, double mjd )
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
