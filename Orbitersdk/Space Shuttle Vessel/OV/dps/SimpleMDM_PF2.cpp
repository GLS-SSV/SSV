#include "SimpleMDM_PF2.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_PF2::SimpleMDM_PF2( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_PF2" ),
		powered(true)
	{
	}

	SimpleMDM_PF2::~SimpleMDM_PF2()
	{
	}

	void SimpleMDM_PF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 9 );
		Power2.Connect( pBundle, 9 );

		pBundle = BundleManager()->CreateBundle( "GPC_CW_CMD_B", 16 );
		dopIOM2[0][12].Connect( pBundle, 1 );// BU_CW_B_CMD_2
		dopIOM2[0][14].Connect( pBundle, 3 );// SM_LIGHT_B_CMD_2
		dopIOM2[0][13].Connect( pBundle, 5 );// SM_TONE_B_CMD_2

		pBundle = BundleManager()->CreateBundle( "GPC_CW_DATA", 16 );
		dopIOM10[2][2].Connect( pBundle, 14 );// 2-C&W MATRIX "PAYLOAD WARNING"

		pBundle = BundleManager()->CreateBundle( "PBD_OPERATION_ENABLE", 16 );
		dopIOM2[0][6].Connect( pBundle, 2 );// PBD ENABLE CMD 2A (AC3 ARM 2-MTRS)
		dopIOM14[0][6].Connect( pBundle, 3 );// PBD ENABLE CMD 2B (AC3 ARM 2-MTRS)
		dopIOM2[0][7].Connect( pBundle, 8 );// PBD ENABLE CMD 5A (AC2 ARM 2-MTRS)
		dopIOM14[0][7].Connect( pBundle, 9 );// PBD ENABLE CMD 5B (AC2 ARM 2-MTRS)
		dopIOM2[0][8].Connect( pBundle, 10 );// PBD ENABLE CMD 6A (AC3 ARM 1&2-MTRS)
		dopIOM14[2][1].Connect( pBundle, 11 );// PBD ENABLE CMD 6B (AC3 ARM 1&2-MTRS)

		pBundle = BundleManager()->CreateBundle( "PayloadBayDoorControl", 16 );
		dipIOM3[0][8].Connect( pBundle, 2 );// CL A
		dipIOM6[0][8].Connect( pBundle, 2 );// CL D
		dipIOM3[0][7].Connect( pBundle, 3 );// OP A
		dipIOM6[0][7].Connect( pBundle, 3 );// OP D
		dopIOM7[0][0].Connect( pBundle, 5 );// R13 TB FLAG: PL BAY DOOR "OP" CMD 2
		dopIOM7[0][1].Connect( pBundle, 7 );// R13 TB FLAG: PL BAY DOOR "CL" CMD 2

		pBundle = BundleManager()->CreateBundle( "PLBD_PORT_PDU", 16 );
		dipIOM6[0][0].Connect( pBundle, 4 );// PLB LEFT FWD BHD READY FOR LCH 3
		dipIOM6[0][1].Connect( pBundle, 7 );// PLB LEFT AFT BHD READY FOR LCH 3
		dipIOM6[0][11].Connect( pBundle, 8 );// PLB LEFT CLOSE 1
		dipIOM6[0][6].Connect( pBundle, 10 );// PLB LEFT OPEN 1

		pBundle = BundleManager()->CreateBundle( "PLBD_STBD_PDU", 16 );
		dipIOM3[0][0].Connect( pBundle, 3 );// PLB RIGHT FWD BHD READY FOR LCH 2
		dipIOM9[0][0].Connect( pBundle, 4 );// PLB RIGHT FWD BHD READY FOR LCH 3
		dipIOM3[0][1].Connect( pBundle, 6 );// PLB RIGHT AFT BHD READY FOR LCH 2
		dipIOM9[0][1].Connect( pBundle, 7 );// PLB RIGHT AFT BHD READY FOR LCH 3
		dipIOM3[0][10].Connect( pBundle, 9 );// PLB RIGHT CLOSE 2
		dipIOM3[0][6].Connect( pBundle, 11 );// PLB RIGHT OPEN 2

		pBundle = BundleManager()->CreateBundle( "PLBD_CL_1", 16 );
		dipIOM9[0][8].Connect( pBundle, 10 );// PLB CENTERLINE LCH 13 - 16 LCH 1
		dipIOM9[0][9].Connect( pBundle, 11 );// PLB CENTERLINE LCH 13 - 16 REL 1

		pBundle = BundleManager()->CreateBundle( "PLBD_CL_2", 16 );
		dipIOM9[0][3].Connect( pBundle, 1 );// PLB CENTERLINE LCH 1 - 4 LCH 2
		dipIOM9[0][2].Connect( pBundle, 2 );// PLB CENTERLINE LCH 1 - 4 REL 2
		dipIOM9[0][5].Connect( pBundle, 4 );// PLB CENTERLINE LCH 5 - 8 LCH 2
		dipIOM9[0][4].Connect( pBundle, 5 );// PLB CENTERLINE LCH 5 - 8 REL 2
		dipIOM9[0][6].Connect( pBundle, 7 );// PLB CENTERLINE LCH 9 - 12 LCH 2
		dipIOM9[0][7].Connect( pBundle, 8 );// PLB CENTERLINE LCH 9 - 12 REL 2

		pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_1", 16 );
		dipIOM3[0][5].Connect( pBundle, 4 );// PLB RIGHT AFT BHD LATCH - LCH 1
		dipIOM3[0][4].Connect( pBundle, 5 );// PLB RIGHT AFT BHD LATCH - REL 1

		pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_2", 16 );
		dipIOM3[0][3].Connect( pBundle, 1 );// PLB RIGHT FWD BHD LATCH - LCH 2
		dipIOM3[0][2].Connect( pBundle, 2 );// PLB RIGHT FWD BHD LATCH - REL 2
		dipIOM6[0][3].Connect( pBundle, 7 );// PLB LEFT FWD BHD LATCH - LCH 2
		dipIOM6[0][2].Connect( pBundle, 8 );// PLB LEFT FWD BHD LATCH - REL 2
		dipIOM6[0][5].Connect( pBundle, 10 );// PLB LEFT AFT BHD LATCH - LCH 2
		dipIOM6[0][4].Connect( pBundle, 11 );// PLB LEFT AFT BHD LATCH - REL 2

		pBundle = BundleManager()->CreateBundle( "PLBD_PDU_CMD", 16 );
		dopIOM14[0][0].Connect( pBundle, 0 );// L PBD: DOOR DRIVE MOTOR 1/OPEN
		dopIOM14[0][1].Connect( pBundle, 1 );// L PBD: DOOR DRIVE MOTOR 1/CLOSE
		dopIOM2[0][0].Connect( pBundle, 6 );// R PBD: DOOR DRIVE MOTOR 2/OPEN
		dopIOM2[0][1].Connect( pBundle, 7 );// R PBD: DOOR DRIVE MOTOR 2/CLOSE

		pBundle = BundleManager()->CreateBundle( "PLBD_CL_CMD", 16 );
		dopIOM7[0][8].Connect( pBundle, 6 );// PBD: C/L LCH 13-16 MOTOR 1/RELEASE
		dopIOM7[0][9].Connect( pBundle, 7 );// PBD: C/L LCH 13-16 MOTOR 1/LATCH
		dopIOM7[0][2].Connect( pBundle, 8 );// PBD: C/L LCH 1-4 MOTOR 2/RELEASE
		dopIOM7[0][3].Connect( pBundle, 9 );// PBD: C/L LCH 1-4 MOTOR 2/LATCH
		dopIOM7[0][4].Connect( pBundle, 10 );// PBD: C/L LCH 5-8 MOTOR 2/RELEASE
		dopIOM7[0][5].Connect( pBundle, 11 );// PBD: C/L LCH 5-8 MOTOR 2/LATCH
		dopIOM7[0][6].Connect( pBundle, 12 );// PBD: C/L LCH 9-12 MOTOR 2/RELEASE
		dopIOM7[0][7].Connect( pBundle, 13 );// PBD: C/L LCH 9-12 MOTOR 2/LATCH

		pBundle = BundleManager()->CreateBundle( "PLBD_BLKHD_CMD", 16 );
		dopIOM14[0][2].Connect( pBundle, 4 );// L PBD: FWD BHD LCH MOTOR 2/RELEASE
		dopIOM14[0][3].Connect( pBundle, 5 );// L PBD: FWD BHD LCH MOTOR 2/LATCH
		dopIOM14[0][4].Connect( pBundle, 6 );// L PBD: AFT BHD LCH MOTOR 2/RELEASE
		dopIOM14[0][5].Connect( pBundle, 7 );// L PBD: AFT BHD LCH MOTOR 2/LATCH
		dopIOM2[0][4].Connect( pBundle, 10 );// R PBD: AFT BHD LCH MOTOR 1/RELEASE
		dopIOM2[0][5].Connect( pBundle, 11 );// R PBD: AFT BHD LCH MOTOR 1/LATCH
		dopIOM2[0][2].Connect( pBundle, 12 );// R PBD: FWD BHD LCH MOTOR 2/RELEASE
		dopIOM2[0][3].Connect( pBundle, 13 );// R PBD: FWD BHD LCH MOTOR 2/LATCH
		return;
	}

	void SimpleMDM_PF2::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_PF2::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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
					case 0b0000:// IOM 0 DOL
						break;
					case 0b0001:// IOM 1 AID
						break;
					case 0b0010:// IOM 2 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM2 );
						break;
					case 0b0011:// IOM 3 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM3 );
						break;
					case 0b0100:// IOM 4 AID
						break;
					case 0b0101:// IOM 5 DIL
						break;
					case 0b0110:// IOM 6 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM6 );
						break;
					case 0b0111:// IOM 7 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM7 );
						break;
					case 0b1000:// IOM 8 SIO
						break;
					case 0b1001:// IOM 9 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM9 );
						break;
					case 0b1010:// IOM 10 DOL
						IOMdata = cdw[0].payload;
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM10 );
						break;
					case 0b1011:// IOM 11 AID
						break;
					case 0b1100:// IOM 12 AOD
						break;
					case 0b1101:// IOM 13 DIL
						break;
					case 0b1110:// IOM 14 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM14 );
						break;
					case 0b1111:// IOM 15 SIO
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 DOL
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
					case 0b0011:// IOM 3 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM3 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0100:// IOM 4 AID
						break;
					case 0b0101:// IOM 5 DIL
						break;
					case 0b0110:// IOM 6 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM6 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0111:// IOM 7 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM7 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1000:// IOM 8 SIO
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
					case 0b1010:// IOM 10 DOL
						{
							IOM_DOL( 0b000, IOMch, IOMdata, dopIOM10 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1011:// IOM 11 AID
						break;
					case 0b1100:// IOM 12 AOD
						break;
					case 0b1101:// IOM 13 DIL
						break;
					case 0b1110:// IOM 14 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM14 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1111:// IOM 15 SIO
						break;
				}
				break;
		}
		return;
	}

	void SimpleMDM_PF2::OnPreStep( double simt, double simdt, double mjd )
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
						dopIOM7[ch][bt].ResetLine();
						dopIOM10[ch][bt].ResetLine();
						dopIOM14[ch][bt].ResetLine();
					}
				}
			}
			powered = false;
		}
		else
		{
			powered = true;
		}
		return;
	}
}
