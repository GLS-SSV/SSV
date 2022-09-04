/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/07/11   GLS
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
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/08/05   GLS
********************************************/
#include "SimpleMDM_FF2.h"
#include "SimpleShuttleBus.h"
#include <cassert>


namespace dps
{
	SimpleMDM_FF2::SimpleMDM_FF2( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_FF2" ),
		powered(true)
	{
	}

	SimpleMDM_FF2::~SimpleMDM_FF2()
	{
	}

	void SimpleMDM_FF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 1 );
		Power2.Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "RDRALTM", 16 );
		dipIOM12[0][13].Connect( pBundle, 1 );// RADAR ALTM RH DISPLAY SEL NO. 1
		// TODO RADAR ALTM HH DISPLAY SEL NO. 2

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
		dipIOM4[0][2].Connect( pBundle, 10 );// 10: L2 ENTRY MODE no y jet
		dipIOM9[1][3].Connect( pBundle, 11 );// 11: L2 ENTRY MODE lo gain

		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_A", 16 );
		dipIOM6[1][1].Connect( pBundle, 10 );// LH_RHC_PLUS_PITCH_TRIM_B
		dipIOM6[1][2].Connect( pBundle, 12 );// LH_RHC_MINUS_PITCH_TRIM_B
		dipIOM6[1][3].Connect( pBundle, 14 );// LH_RHC_PLUS_ROLL_TRIM_B
		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_B", 16 );
		dipIOM6[1][4].Connect( pBundle, 0 );// LH_RHC_MINUS_ROLL_TRIM_B

		pBundle = BundleManager()->CreateBundle( "C3_LIMITS_SSMEPB", 6 );
		dipIOM4[2][3].Connect( pBundle, 0 );// 3-MPS ENG LIMIT CONTROL NO. 1 AUTO
		dipIOM4[2][2].Connect( pBundle, 1 );// 2-MPS ENG LIMIT CONTROL NO. 1 INHIBIT
		dipIOM4[2][1].Connect( pBundle, 2 );// 1-MPS ENG LIMIT CONTROL NO. 1 ENABLE
		dipIOM9[1][0].Connect( pBundle, 3 );// 0-MPS ME-2 SHUTDOWN CMD A
		dipIOM4[0][5].Connect( pBundle, 4 );// 5-MPS ME-1 SHUTDOWN CMD B

		pBundle = BundleManager()->CreateBundle( "MPSDUMP_LH2UP_R2_SWITCHES", 5 );
		dipIOM9[2][8].Connect( pBundle, 1 );// MPS PRPLT DUMP SEQUENCE START B
		dipIOM9[2][9].Connect( pBundle, 0 );// MPS PRPLT DUMP SEQUENCE STOP B

		pBundle = BundleManager()->CreateBundle( "ACA1_1", 16 );
		dopIOM10[1][0].Connect( pBundle, 14 );// 0-F7 LIGHT: L MPS RED STATUS

		pBundle = BundleManager()->CreateBundle( "ACA1_2", 16 );
		dopIOM10[0][4].Connect( pBundle, 4 );// 4-F2 LIGHT: LH FCS BODY FLAP "MAN"
		dopIOM10[0][6].Connect( pBundle, 12 );// 6-F2 LIGHT: LH FCS PITCH "CSS"
		dopIOM2[1][0].Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "ACA1_3", 16 );
		dopIOM10[0][7].Connect( pBundle, 8 );// 7-F2 LIGHT: LH FCS ROLL/YAW "CSS"

		pBundle = BundleManager()->CreateBundle( "ACA1_4", 16 );
		dopIOM10[0][5].Connect( pBundle, 4 );// 5-F2 LIGHT: LH FCS SPEED BK "MAN"

		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_B", 16 );
		dipIOM6[0][7].Connect( pBundle, 15 );// 7-FWD THC POS X OUTPUT - B
		pBundle = BundleManager()->CreateBundle( "LeftRHCTHC_C", 16 );
		dipIOM6[0][8].Connect( pBundle, 2 );// 8-FWD THC NEG X OUTPUT - B
		dipIOM6[0][9].Connect( pBundle, 5 );// 9-FWD THC POS Y OUTPUT - B
		dipIOM6[0][10].Connect( pBundle, 8 );// 10-FWD THC NEG Y OUTPUT - B
		dipIOM6[0][11].Connect( pBundle, 11 );// 11-FWD THC POS Z OUTPUT - B
		dipIOM6[0][12].Connect( pBundle, 14 );// 12-FWD THC NEG Z OUTPUT - B

		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_B", 16 );
		dipIOM15[0][7].Connect( pBundle, 15 );// 7-AFT THC POS X OUTPUT - B
		pBundle = BundleManager()->CreateBundle( "AftRHCTHC_C", 16 );
		dipIOM15[0][8].Connect( pBundle, 2 );// 8-AFT THC NEG X OUTPUT - B
		dipIOM15[0][9].Connect( pBundle, 5 );// 9-AFT THC POS Y OUTPUT - B
		dipIOM15[0][10].Connect( pBundle, 8 );// 10-AFT THC NEG Y OUTPUT - B
		dipIOM15[0][11].Connect( pBundle, 11 );// 11-AFT THC POS Z OUTPUT - B
		dipIOM15[0][12].Connect( pBundle, 14 );// 12-AFT THC NEG Z OUTPUT - B

		pBundle = BundleManager()->CreateBundle( "LeftSBTC", 16 );
		dipIOM6[0][13].Connect( pBundle, 4 );// 13-LH SBTC TAKEOVER - B
		pBundle = BundleManager()->CreateBundle( "RightSBTC", 16 );
		dipIOM15[0][13].Connect( pBundle, 3 );// 13-RH SBTC TAKEOVER - A

		pBundle = BundleManager()->CreateBundle( "ADI_Switches_A6U", 16 );
		dipIOM9[1][1].Connect( pBundle, 7 );// 1-SENSE SW -Z CON B
		dipIOM9[1][2].Connect( pBundle, 6 );// 2-SENSE SW -X CON B

		pBundle = BundleManager()->CreateBundle( "DAP_CH_CONTROLS", 16 );
		dipIOM4[1][10].Connect( pBundle, 0 );// 10-FCS LH PITCH AUTO MODE B
		dipIOM12[1][10].Connect( pBundle, 1 );// 10-FCS RH PITCH AUTO MODE A
		dipIOM4[1][11].Connect( pBundle, 2 );// 11-FCS LH PITCH CSS MODE B
		dipIOM12[1][11].Connect( pBundle, 3 );// 11-FCS RH PITCH CSS MODE A
		dipIOM4[1][13].Connect( pBundle, 4 );// 13-FCS LH R-Y AUTO MODE B
		dipIOM12[1][13].Connect( pBundle, 5 );// 13-FCS RH R-Y AUTO MODE A
		dipIOM4[1][14].Connect( pBundle, 6 );// 14-FCS LH R-Y CSS MODE B
		dipIOM12[1][14].Connect( pBundle, 7 );// 14-FCS RH R-Y CSS MODE A
		dipIOM4[2][0].Connect( pBundle, 8 );// 0-LH SPD BK/THROT AUTO/MAN B
		dipIOM12[2][0].Connect( pBundle, 9 );// 15-RH BODY FLAP AUTO/MANUAL A
		dipIOM4[1][15].Connect( pBundle, 10 );// 15-LH BODY FLAP AUTO/MANUAL B
		dipIOM12[1][15].Connect( pBundle, 11 );// 0-RH SPD BK/THROT AUTO/MAN A

		pBundle = BundleManager()->CreateBundle( "DAP_PBI_FWD_1", 16 );
		dipIOM9[0][4].Connect( pBundle, 0 );// 4-FWD DAP SELECT A - B
		dipIOM9[0][5].Connect( pBundle, 1 );// 5-FWD DAP SELECT B - B
		dipIOM9[0][8].Connect( pBundle, 2 );// 8-FWD DAP AUTO B
		dipIOM9[0][9].Connect( pBundle, 3 );// 9-FWD DAP MAN B
		dipIOM9[1][13].Connect( pBundle, 4 );// 13-FWD RCS JETS NORM B
		dipIOM9[1][14].Connect( pBundle, 5 );// 14-FWD RCS JETS VERNIER B
		dipIOM9[2][1].Connect( pBundle, 6 );// 1-FWD TRANSLATION X LVLH B
		dipIOM9[2][4].Connect( pBundle, 7 );// 4-FWD TRANSLATION Y LOW Z B
		dipIOM9[2][7].Connect( pBundle, 8 );// 7-FWD TRANSLATION Z HIGH B
		dipIOM9[1][4].Connect( pBundle, 9 );// 4-FWD ROTATION ROLL DISC RATE B
		dipIOM9[1][7].Connect( pBundle, 10 );// 7-FWD ROTATION PITCH DISC RATE B
		dipIOM9[1][10].Connect( pBundle, 11 );// 10-FWD ROTATION YAW DISC RATE B
		dipIOM9[1][15].Connect( pBundle, 12 );// 15-FWD TRANSLATION X NORM B
		dipIOM9[2][2].Connect( pBundle, 13 );// 2-FWD TRANSLATION Y NORM B
		dipIOM9[2][5].Connect( pBundle, 14 );// 5-FWD TRANSLATION Z NORM B
		dipIOM9[1][5].Connect( pBundle, 15 );// 5-FWD ROTATION ROLL ACCEL B
		pBundle = BundleManager()->CreateBundle( "DAP_PBI_FWD_2", 16 );
		dipIOM9[1][8].Connect( pBundle, 0 );// 8-FWD ROTATION PITCH ACCEL B
		dipIOM9[1][11].Connect( pBundle, 1 );// 11-FWD ROTATION YAW ACCEL B
		dipIOM9[2][0].Connect( pBundle, 2 );// 0-FWD TRANSLATION X PULSE B
		dipIOM9[2][3].Connect( pBundle, 3 );// 3-FWD TRANSLATION Y PULSE B
		dipIOM9[2][6].Connect( pBundle, 4 );// 6-FWD TRANSLATION Z PULSE B
		dipIOM9[1][6].Connect( pBundle, 5 );// 6-FWD ROTATION ROLL PULSE B
		dipIOM9[1][9].Connect( pBundle, 6 );// 9-FWD ROTATION PITCH PULSE B
		dipIOM9[1][12].Connect( pBundle, 7 );// 12-FWD ROTATION YAW PULSE B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
		dipIOM4[2][6].Connect( pBundle, 0 );// L_VENTS_1_AND_2_CLOSE_2
		dipIOM4[2][7].Connect( pBundle, 1 );// L_VENTS_1_AND_2_OPEN_2
		dipIOM4[2][8].Connect( pBundle, 2 );// L_VENTS_1_AND_2_PURGE_1_IND_2
		dipIOM4[2][4].Connect( pBundle, 3 );// LH_VENT_3_CLOSE_2
		dipIOM4[2][5].Connect( pBundle, 4 );// LH_VENT_3_OPEN_2
		dipIOM4[2][12].Connect( pBundle, 5 );// LH_VENTS_4_AND_7_CLOSE_2
		dipIOM4[2][13].Connect( pBundle, 6 );// LH_VENTS_4_AND_7_OPEN_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
		dipIOM4[2][14].Connect( pBundle, 7 );// RH_VENT_5_CLOSE_2
		dipIOM4[2][15].Connect( pBundle, 8 );// RH_VENT_5_OPEN_2
		dipIOM4[2][9].Connect( pBundle, 9 );// RH_VENT_6_CLOSE_2
		dipIOM4[2][10].Connect( pBundle, 10 );// RH_VENT_6_OPEN_2
		dipIOM4[2][11].Connect( pBundle, 11 );// RH_VENT_6_PURGE_1_IND_2
		dipIOM12[2][8].Connect( pBundle, 12 );// RH_VENT_6_PURGE_2_IND_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2A", 16 );
		dopIOM10[0][1].Connect( pBundle, 0 );// LH_VENTS_1_2_MOTOR_2_OPEN_A
		dopIOM10[0][0].Connect( pBundle, 1 );// LH_VENTS_1_2_MOTOR_2_CLOSE_A
		dopIOM10[0][2].Connect( pBundle, 2 );// LH_VENTS_1_2_MOTOR_2_PURGE_A
		dopIOM10[2][7].Connect( pBundle, 3 );// LH_VENT_3_MOTOR_2_OPEN_A
		dopIOM10[2][6].Connect( pBundle, 4 );// LH_VENT_3_MOTOR_2_CLOSE_A
		dopIOM10[2][9].Connect( pBundle, 5 );// LH_VENTS_4_7_MOTOR_2_OPEN_A
		dopIOM10[2][8].Connect( pBundle, 6 );// LH_VENTS_4_7_MOTOR_2_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2B", 16 );
		dopIOM2[0][1].Connect( pBundle, 0 );// LH_VENTS_1_2_MOTOR_2_OPEN_B
		dopIOM2[0][0].Connect( pBundle, 1 );// LH_VENTS_1_2_MOTOR_2_CLOSE_B
		dopIOM2[0][2].Connect( pBundle, 2 );// LH_VENTS_1_2_MOTOR_2_PURGE_B
		dopIOM2[2][7].Connect( pBundle, 3 );// LH_VENT_3_MOTOR_2_OPEN_B
		dopIOM2[2][6].Connect( pBundle, 4 );// LH_VENT_3_MOTOR_2_CLOSE_B
		dopIOM2[2][9].Connect( pBundle, 5 );// LH_VENTS_4_7_MOTOR_2_OPEN_B
		dopIOM2[2][8].Connect( pBundle, 6 );// LH_VENTS_4_7_MOTOR_2_CLOSE_B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2A", 16 );
		dopIOM10[2][15].Connect( pBundle, 7 );// RH_VENT_5_MOTOR_2_OPEN_A
		dopIOM10[2][14].Connect( pBundle, 8 );// RH_VENT_5_MOTOR_2_CLOSE_A
		dopIOM10[2][11].Connect( pBundle, 9 );// RH_VENT_6_MOTOR_2_OPEN_A
		dopIOM10[2][10].Connect( pBundle, 10 );// RH_VENT_6_MOTOR_2_CLOSE_A
		dopIOM10[2][12].Connect( pBundle, 11 );// RH_VENT_6_MOTOR_2_PRG_1_A
		dopIOM10[2][13].Connect( pBundle, 12 );// RH_VENT_6_MOTOR_2_PRG_2_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2B", 16 );
		dopIOM2[2][15].Connect( pBundle, 7 );// RH_VENT_5_MOTOR_2_OPEN_B
		dopIOM2[1][6].Connect( pBundle, 8 );// RH_VENT_5_MOTOR_2_CLOSE_B
		dopIOM2[2][11].Connect( pBundle, 9 );// RH_VENT_6_MOTOR_2_OPEN_B
		dopIOM2[2][10].Connect( pBundle, 10 );// RH_VENT_6_MOTOR_2_CLOSE_B
		dopIOM2[2][12].Connect( pBundle, 11 );// RH_VENT_6_MOTOR_2_PRG_1_B
		dopIOM2[2][13].Connect( pBundle, 12 );// RH_VENT_6_MOTOR_2_PRG_2_B

		pRA2 = dynamic_cast<gnc::RadarAltimeter*>(director->GetSubsystemByName( "RA2" ));
		assert( (pRA2 != NULL) && "SimpleMDM_FF2::Realize.pRA2" );
		return;
	}

	void SimpleMDM_FF2::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_FF2::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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
						IOM_TAC( 0b001, IOMch, IOMdata, pRA2 );
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
					case 0b0000:// IOM 0 TAC
						{
							IOM_TAC( 0b000, IOMch, IOMdata, pRA2 );

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

	void SimpleMDM_FF2::OnPreStep( double simt, double simdt, double mjd )
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
