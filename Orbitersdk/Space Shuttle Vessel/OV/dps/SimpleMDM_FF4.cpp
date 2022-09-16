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
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/07/01   GLS
2022/08/05   GLS
2022/08/16   GLS
********************************************/
#include "SimpleMDM_FF4.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_FF4::SimpleMDM_FF4( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_FF4" ),
		powered(true)
	{
	}

	SimpleMDM_FF4::~SimpleMDM_FF4()
	{
	}

	void SimpleMDM_FF4::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 3 );
		Power2.Connect( pBundle, 3 );

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
		dipIOM15[1][1].Connect( pBundle, 10 );// LH_RHC_PLUS_PITCH_TRIM_B
		dipIOM15[1][2].Connect( pBundle, 12 );// LH_RHC_MINUS_PITCH_TRIM_B
		dipIOM15[1][3].Connect( pBundle, 14 );// LH_RHC_PLUS_ROLL_TRIM_B
		pBundle = BundleManager()->CreateBundle( "RightRHC_B", 16 );
		dipIOM15[1][4].Connect( pBundle, 0 );// LH_RHC_MINUS_ROLL_TRIM_B

		pBundle = BundleManager()->CreateBundle( "C3_LIMITS_SSMEPB", 6 );
		dipIOM4[2][3].Connect( pBundle, 0 );// 3-MPS ENG LIMIT CONTROL NO. 3 AUTO
		dipIOM4[2][2].Connect( pBundle, 1 );// 2-MPS ENG LIMIT CONTROL NO. 3 INHIBIT
		dipIOM4[2][1].Connect( pBundle, 2 );// 1-MPS ENG LIMIT CONTROL NO. 3 ENABLE
		dipIOM4[0][5].Connect( pBundle, 5 );// 5-MPS ME-3 SHUTDOWN CMD B

		pBundle = BundleManager()->CreateBundle( "C3_SEP", 6 );
		dipIOM6[1][5].Connect( pBundle, 0 );// AUTO
		dipIOM6[1][6].Connect( pBundle, 1 );// MAN/AUTO
		dipIOM6[1][7].Connect( pBundle, 2 );// SEP
		dipIOM15[1][7].Connect( pBundle, 3 );// AUTO
		dipIOM15[1][5].Connect( pBundle, 4 );// MAN
		dipIOM15[1][6].Connect( pBundle, 5 );// SEP

		pBundle = BundleManager()->CreateBundle( "MPSDUMP_LH2UP_R2_SWITCHES", 5 );
		dipIOM9[2][8].Connect( pBundle, 3 );// MPS BACKUP LH2 PRPLT DUMP START B
		dipIOM9[2][9].Connect( pBundle, 2 );// MPS BACKUP LH2 PRPLT DUMP STOP B

		pBundle = BundleManager()->CreateBundle( "FwdEventTimer_A", 16 );
		dopIOM5[1][0].Connect( pBundle, 7 );// 0-FWD EVENT TIMER: LIFT OFF TIMER_RESET

		pBundle = BundleManager()->CreateBundle( "RightSBTC", 16 );
		dipIOM15[0][13].Connect( pBundle, 5 );// 13-RH SBTC TAKEOVER - C

		pBundle = BundleManager()->CreateBundle( "CDR_TRIM_BF_EM", 16 );
		dipIOM12[2][15].Connect( pBundle, 10 );// 10: L2 ENTRY MODE no y jet
		dipIOM9[1][3].Connect( pBundle, 11 );// 11: L2 ENTRY MODE lo gain

		pBundle = BundleManager()->CreateBundle( "ACA2_2", 16 );
		dopIOM10[0][6].Connect( pBundle, 14 );// 6-F4 LIGHT: RH FCS PITCH "CSS"

		pBundle = BundleManager()->CreateBundle( "ACA2_3", 16 );
		dopIOM10[0][7].Connect( pBundle, 10 );// 7-F4 LIGHT: RH FCS ROLL/YAW "CSS"

		pBundle = BundleManager()->CreateBundle( "ACA2_4", 16 );
		dopIOM10[0][5].Connect( pBundle, 6 );// 5-F4 LIGHT: RH FCS SPEED BK "MAN"

		pBundle = BundleManager()->CreateBundle( "ACA2_5", 16 );
		dopIOM10[0][4].Connect( pBundle, 2 );// 4-F4 LIGHT: RH FCS BODY FLAP "MAN"

		pBundle = BundleManager()->CreateBundle( "DAP_CH_CONTROLS", 16 );
		dipIOM12[1][10].Connect( pBundle, 1 );// 10-FCS RH PITCH AUTO MODE C
		dipIOM12[1][11].Connect( pBundle, 3 );// 11-FCS RH PITCH CSS MODE C
		dipIOM12[1][13].Connect( pBundle, 5 );// 13-FCS RH R-Y AUTO MODE C
		dipIOM12[1][14].Connect( pBundle, 7 );// 14-FCS RH R-Y CSS MODE C
		dipIOM12[2][0].Connect( pBundle, 9 );// 15-RH BODY FLAP AUTO/MANUAL C
		dipIOM12[1][15].Connect( pBundle, 11 );// 0-RH SPD BK/THROT AUTO/MAN C

		pBundle = BundleManager()->CreateBundle( "DAP_PBI_AFT_1", 16 );
		dipIOM9[0][4].Connect( pBundle, 0 );// 4-AFT DAP SELECT A - B
		dipIOM9[0][5].Connect( pBundle, 1 );// 5-AFT DAP SELECT B - B
		dipIOM9[0][8].Connect( pBundle, 2 );// 8-AFT DAP AUTO B
		dipIOM9[0][9].Connect( pBundle, 3 );// 9-AFT DAP MAN B
		dipIOM9[1][13].Connect( pBundle, 4 );// 13-AFT RCS JETS NORM B
		dipIOM9[1][14].Connect( pBundle, 5 );// 14-AFT RCS JETS VERNIER B
		dipIOM9[2][1].Connect( pBundle, 6 );// 1-AFT TRANSLATION X LVLH B
		dipIOM9[2][4].Connect( pBundle, 7 );// 4-AFT TRANSLATION Y LOW Z B
		dipIOM9[2][7].Connect( pBundle, 8 );// 7-AFT TRANSLATION Z HIGH B
		dipIOM9[1][4].Connect( pBundle, 9 );// 4-AFT ROTATION ROLL DISC RATE B
		dipIOM9[1][7].Connect( pBundle, 10 );// 7-AFT ROTATION PITCH DISC RATE B
		dipIOM9[1][10].Connect( pBundle, 11 );// 10-AFT ROTATION YAW DISC RATE B
		dipIOM9[1][15].Connect( pBundle, 12 );// 15-AFT TRANSLATION X NORM B
		dipIOM9[2][2].Connect( pBundle, 13 );// 2-AFT TRANSLATION Y NORM B
		dipIOM9[2][5].Connect( pBundle, 14 );// 5-AFT TRANSLATION Z NORM B
		dipIOM9[1][5].Connect( pBundle, 15 );// 5-AFT ROTATION ROLL ACCEL B
		pBundle = BundleManager()->CreateBundle( "DAP_PBI_AFT_2", 16 );
		dipIOM9[1][8].Connect( pBundle, 0 );// 8-AFT ROTATION PITCH ACCEL B
		dipIOM9[1][11].Connect( pBundle, 1 );// 11-AFT ROTATION YAW ACCEL B
		dipIOM9[2][0].Connect( pBundle, 2 );// 0-AFT TRANSLATION X PULSE B
		dipIOM9[2][3].Connect( pBundle, 3 );// 3-AFT TRANSLATION Y PULSE B
		dipIOM9[2][6].Connect( pBundle, 4 );// 6-AFT TRANSLATION Z PULSE B
		dipIOM9[1][6].Connect( pBundle, 5 );// 6-AFT ROTATION ROLL PULSE B
		dipIOM9[1][9].Connect( pBundle, 6 );// 9-AFT ROTATION PITCH PULSE B
		dipIOM9[1][12].Connect( pBundle, 7 );// 12-AFT ROTATION YAW PULSE B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
		dipIOM4[2][14].Connect( pBundle, 7 );// LH_VENT_5_CLOSE_2
		dipIOM4[2][15].Connect( pBundle, 8 );// LH_VENT_5_OPEN_2
		dipIOM4[2][9].Connect( pBundle, 9 );// LH_VENT_6_CLOSE_2
		dipIOM4[2][10].Connect( pBundle, 10 );// LH_VENT_6_OPEN_2
		dipIOM4[2][11].Connect( pBundle, 11 );// LH_VENT_6_PURGE_1_IND_2
		dipIOM12[2][8].Connect( pBundle, 12 );// LH_VENT_6_PURGE_2_IND_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_1", 16 );
		dipIOM4[2][12].Connect( pBundle, 5 );// RH_VENTS_4_AND_7_CLOSE_1
		dipIOM4[2][13].Connect( pBundle, 6 );// RH_VENTS_4_AND_7_OPEN_1

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
		dipIOM4[2][6].Connect( pBundle, 0 );// R_VENTS_1_AND_2_CLOSE_2
		dipIOM4[2][7].Connect( pBundle, 1 );// R_VENTS_1_AND_2_OPEN_2
		dipIOM4[2][8].Connect( pBundle, 2 );// R_VENTS_1_AND_2_PURGE_1_IND_2
		dipIOM4[2][4].Connect( pBundle, 3 );// RH_VENT_3_CLOSE_2
		dipIOM4[2][5].Connect( pBundle, 4 );// RH_VENT_3_OPEN_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2A", 16 );
		dopIOM10[2][15].Connect( pBundle, 7 );// LH_VENT_5_MOTOR_2_OPEN_A
		dopIOM10[2][14].Connect( pBundle, 8 );// LH_VENT_5_MOTOR_2_CLOSE_A
		dopIOM10[2][11].Connect( pBundle, 9 );// LH_VENT_6_MOTOR_2_OPEN_A
		dopIOM10[2][10].Connect( pBundle, 10 );// LH_VENT_6_MOTOR_2_CLOSE_A
		dopIOM10[2][12].Connect( pBundle, 11 );// LH_VENT_6_MOTOR_2_PRG_1_A
		dopIOM10[2][13].Connect( pBundle, 12 );// LH_VENT_6_MOTOR_2_PRG_2_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2B", 16 );
		dopIOM2[2][15].Connect( pBundle, 7 );// LH_VENT_5_MOTOR_2_OPEN_B
		dopIOM2[1][6].Connect( pBundle, 8 );// LH_VENT_5_MOTOR_2_CLOSE_B
		dopIOM2[2][11].Connect( pBundle, 9 );// LH_VENT_6_MOTOR_2_OPEN_B
		dopIOM2[2][10].Connect( pBundle, 10 );// LH_VENT_6_MOTOR_2_CLOSE_B
		dopIOM2[2][12].Connect( pBundle, 11 );// LH_VENT_6_MOTOR_2_PRG_1_B
		dopIOM2[2][13].Connect( pBundle, 12 );// LH_VENT_6_MOTOR_2_PRG_2_B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1A", 16 );
		dopIOM10[2][9].Connect( pBundle, 5 );// RH_VENTS_4_7_MOTOR_1_OPEN_A
		dopIOM10[2][8].Connect( pBundle, 6 );// RH_VENTS_4_7_MOTOR_1_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_1B", 16 );
		dopIOM2[2][9].Connect( pBundle, 5 );// RH_VENTS_4_7_MOTOR_1_OPEN_B
		dopIOM2[2][8].Connect( pBundle, 6 );// RH_VENTS_4_7_MOTOR_1_CLOSE_B

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2A", 16 );
		dopIOM10[0][1].Connect( pBundle, 0 );// RH_VENTS_1_2_MOTOR_2_OPEN_A
		dopIOM10[0][0].Connect( pBundle, 1 );// RH_VENTS_1_2_MOTOR_2_CLOSE_A
		dopIOM10[2][7].Connect( pBundle, 2 );// RH_VENTS_1_2_MOTOR_2_PURGE_A
		dopIOM10[0][2].Connect( pBundle, 3 );// RH_VENT_3_MOTOR_2_OPEN_A
		dopIOM10[2][6].Connect( pBundle, 4 );// RH_VENT_3_MOTOR_2_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2B", 16 );
		dopIOM2[0][1].Connect( pBundle, 0 );// RH_VENTS_1_2_MOTOR_2_OPEN_B
		dopIOM2[2][7].Connect( pBundle, 1 );// RH_VENTS_1_2_MOTOR_2_CLOSE_B
		dopIOM2[0][2].Connect( pBundle, 2 );// RH_VENTS_1_2_MOTOR_2_PURGE_B
		dopIOM2[0][0].Connect( pBundle, 3 );// RH_VENT_3_MOTOR_2_OPEN_B
		dopIOM2[2][6].Connect( pBundle, 4 );// RH_VENT_3_MOTOR_2_CLOSE_B
		return;
	}

	void SimpleMDM_FF4::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_FF4::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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

	void SimpleMDM_FF4::OnPreStep( double simt, double simdt, double mjd )
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
