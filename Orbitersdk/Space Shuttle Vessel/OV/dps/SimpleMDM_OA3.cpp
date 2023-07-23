#include "SimpleMDM_OA3.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_OA3::SimpleMDM_OA3( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_OA3" ),
		powered(true)
	{
	}

	SimpleMDM_OA3::~SimpleMDM_OA3()
	{
	}

	void SimpleMDM_OA3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 11 );
		Power2.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 10 );
		dipIOM12[0][1].Connect( pBundle, 0 );// 1-PL1_1A_LAT
		dipIOM12[0][0].Connect( pBundle, 1 );// 0-PL1_1A_REL
		dipIOM12[0][2].Connect( pBundle, 2 );// 2-PL1_1A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
		dipIOM1[2][0].Connect( pBundle, 0 );// 4-PL2_1A_LAT
		dipIOM12[0][3].Connect( pBundle, 1 );// 3-PL2_1A_REL
		dipIOM12[0][5].Connect( pBundle, 2 );// 5-PL2_1A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 10 );
		dipIOM12[0][7].Connect( pBundle, 0 );// 7-PL1_2A_LAT
		dipIOM12[0][6].Connect( pBundle, 1 );// 6-PL1_2A_REL
		dipIOM12[0][8].Connect( pBundle, 2 );// 8-PL1_2A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 10 );
		dipIOM12[1][1].Connect( pBundle, 0 );// 1-PL1_3A_LAT
		dipIOM12[1][0].Connect( pBundle, 1 );// 0-PL1_3A_REL
		dipIOM12[1][2].Connect( pBundle, 2 );// 2-PL1_3A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 10 );
		dipIOM12[1][4].Connect( pBundle, 0 );// 4-PL1_4A_LAT
		dipIOM12[1][3].Connect( pBundle, 1 );// 3-PL1_4A_REL
		dipIOM12[1][5].Connect( pBundle, 2 );// 5-PL1_4A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 10 );
		dipIOM12[1][7].Connect( pBundle, 0 );// 7-PL1_5A_LAT
		dipIOM12[1][6].Connect( pBundle, 1 );// 6-PL1_5A_REL
		dipIOM12[1][8].Connect( pBundle, 2 );// 8-PL1_5A_RDY
		return;
	}

	void SimpleMDM_OA3::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_OA3::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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
					case 0b0000:// IOM 0 AIS
						break;
					case 0b0001:// IOM 1 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM1 );
						break;
					case 0b0010:// IOM 2 AIS
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 AIS
						break;
					case 0b0101:// IOM 5 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM7 );
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM10 );
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM12 );
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIL
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AIS
						break;
					case 0b0001:// IOM 1 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM1 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0010:// IOM 2 AIS
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 AIS
						break;
					case 0b0101:// IOM 5 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM5 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM7 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM10 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
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
					case 0b1110:// IOM 14 DIL
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				break;
		}
		return;
	}

	void SimpleMDM_OA3::OnPreStep( double simt, double simdt, double mjd )
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
