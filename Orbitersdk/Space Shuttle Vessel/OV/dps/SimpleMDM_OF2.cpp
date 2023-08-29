#include "SimpleMDM_OF2.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_OF2::SimpleMDM_OF2( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_OF2" ),
		powered(true)
	{
	}

	SimpleMDM_OF2::~SimpleMDM_OF2()
	{
	}

	void SimpleMDM_OF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 12 );
		Power2.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM4[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM4[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM4[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM6_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM6[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM6_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM6[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM6_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM6[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM12[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM12[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM12[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM14[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM14[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM14[2][i].Connect( pBundle, i );
		return;
	}

	void SimpleMDM_OF2::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_OF2::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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

	void SimpleMDM_OF2::OnPreStep( double simt, double simdt, double mjd )
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
