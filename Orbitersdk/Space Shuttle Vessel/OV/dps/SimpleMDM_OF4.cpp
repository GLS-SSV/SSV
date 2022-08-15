#include "SimpleMDM_OF4.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_OF4::SimpleMDM_OF4( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_OF4" ),
		powered(true)
	{
	}

	SimpleMDM_OF4::~SimpleMDM_OF4()
	{
	}

	void SimpleMDM_OF4::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 13 );
		Power2.Connect( pBundle, 15 );
		return;
	}

	void SimpleMDM_OF4::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_OF4::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
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
					case 0b0000:// IOM 0 DIL
						break;
					case 0b0001:// IOM 1 AIS
						break;
					case 0b0010:// IOM 2 DIH
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 DIH
						break;
					case 0b0101:// IOM 5 DIH
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						break;
					case 0b1101:// IOM 13 DIH
						break;
					case 0b1110:// IOM 14 AIS
						break;
					case 0b1111:// IOM 15 DIH
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 DIL
						break;
					case 0b0001:// IOM 1 AIS
						break;
					case 0b0010:// IOM 2 DIH
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 DIH
						break;
					case 0b0101:// IOM 5 DIH
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						break;
					case 0b1101:// IOM 13 DIH
						break;
					case 0b1110:// IOM 14 AIS
						break;
					case 0b1111:// IOM 15 DIH
						break;
				}
				break;
		}
		return;
	}

	void SimpleMDM_OF4::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power1.IsSet() && !Power2.IsSet())
		{
			if (powered)
			{
				// TODO power loss -> set outputs to 0
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
