#include "SimpleMDM_OF1.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_OF1::SimpleMDM_OF1( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_OF1" ),
		powered(true)
	{
	}

	SimpleMDM_OF1::~SimpleMDM_OF1()
	{
	}

	void SimpleMDM_OF1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 12 );
		Power2.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 10 );
		dipIOM14[0][1].Connect( pBundle, 5 );// 1-PL3_1B_LAT
		dipIOM14[0][0].Connect( pBundle, 6 );// 0-PL3_1B_REL
		dipIOM14[0][2].Connect( pBundle, 7 );// 2-PL3_1B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
		dipIOM4[1][1].Connect( pBundle, 5 );// 4-PL2_2B_LAT
		dipIOM14[0][3].Connect( pBundle, 6 );// 3-PL2_2B_REL
		dipIOM14[0][5].Connect( pBundle, 7 );// 5-PL2_2B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 10 );
		dipIOM14[0][7].Connect( pBundle, 5 );// 7-PL3_2B_LAT
		dipIOM14[0][6].Connect( pBundle, 6 );// 6-PL3_2B_REL
		dipIOM14[0][8].Connect( pBundle, 7 );// 8-PL3_2B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
		dipIOM14[0][10].Connect( pBundle, 5 );// 10-PL2_3B_LAT
		dipIOM14[0][9].Connect( pBundle, 6 );// 9-PL2_3B_REL
		dipIOM14[0][11].Connect( pBundle, 7 );// 11-PL2_3B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
		dipIOM14[0][13].Connect( pBundle, 5 );// 13-PL3_3B_LAT
		dipIOM14[0][12].Connect( pBundle, 6 );// 12-PL3_3B_REL
		dipIOM14[0][14].Connect( pBundle, 7 );// 14-PL3_3B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 10 );
		dipIOM14[1][1].Connect( pBundle, 5 );// 1-PL2_4B_LAT
		dipIOM14[1][0].Connect( pBundle, 6 );// 0-PL2_4B_REL
		dipIOM14[1][2].Connect( pBundle, 7 );// 2-PL2_4B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
		dipIOM6[1][0].Connect( pBundle, 5 );// 4-PL3_4B_LAT
		dipIOM4[2][0].Connect( pBundle, 6 );// 3-PL3_4B_REL
		dipIOM14[1][5].Connect( pBundle, 7 );// 5-PL3_4B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 10 );
		dipIOM14[1][7].Connect( pBundle, 5 );// 7-PL2_5B_LAT
		dipIOM14[1][6].Connect( pBundle, 6 );// 6-PL2_5B_REL
		dipIOM14[1][8].Connect( pBundle, 7 );// 8-PL2_5B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
		dipIOM4[1][0].Connect( pBundle, 5 );// 10-PL3_5B_LAT
		dipIOM14[1][9].Connect( pBundle, 6 );// 9-PL3_5B_REL
		dipIOM14[1][11].Connect( pBundle, 7 );// 11-PL3_5B_RDY
		return;
	}

	void SimpleMDM_OF1::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_OF1::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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
					case 0b0000:// IOM 0 SIO
						break;
					case 0b0001:// IOM 1 AIS
						break;
					case 0b0010:// IOM 2 DIL
						break;
					case 0b0011:// IOM 3 AIS
						break;
					case 0b0100:// IOM 4 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM4 );
						break;
					case 0b0101:// IOM 5 AIS
						break;
					case 0b0110:// IOM 6 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM6 );
						break;
					case 0b0111:// IOM 7 AIS
						break;
					case 0b1000:// IOM 8 AID
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIL
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM12 );
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM14 );
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 SIO
						break;
					case 0b0001:// IOM 1 AIS
						break;
					case 0b0010:// IOM 2 DIL
						break;
					case 0b0011:// IOM 3 AIS
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
					case 0b0101:// IOM 5 AIS
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
					case 0b0111:// IOM 7 AIS
						break;
					case 0b1000:// IOM 8 AID
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIL
						break;
					case 0b1011:// IOM 11 AIS
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
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM14 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				break;
		}
		return;
	}

	void SimpleMDM_OF1::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power1.IsSet() && !Power2.IsSet())
		{
			if (powered)
			{
				// TODO power loss -> set outputs to 0
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
