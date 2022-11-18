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

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
		dipIOM15[0][1].Connect( pBundle, 0 );// 1-PL2_2A_LAT
		dipIOM15[0][0].Connect( pBundle, 1 );// 0-PL2_2A_REL
		dipIOM15[0][2].Connect( pBundle, 2 );// 2-PL2_2A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
		dipIOM15[0][4].Connect( pBundle, 0 );// 4-PL2_3A_LAT
		dipIOM15[0][3].Connect( pBundle, 1 );// 3-PL2_3A_REL
		dipIOM15[0][5].Connect( pBundle, 2 );// 5-PL2_3A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_4", 10 );
		dipIOM15[0][7].Connect( pBundle, 0 );// 7-PL2_4A_LAT
		dipIOM15[0][6].Connect( pBundle, 1 );// 6-PL2_4A_REL
		dipIOM15[0][8].Connect( pBundle, 2 );// 8-PL2_4A_RDY

		pBundle = BundleManager()->CreateBundle( "PLD_SEL", 16 );
		dipIOM15[0][12].Connect( pBundle, 0 );// 12-PLD_SEL_POS_1
		dipIOM15[0][13].Connect( pBundle, 1 );// 13-PLD_SEL_POS_2
		dipIOM15[0][14].Connect( pBundle, 2 );// 14-PLD_SEL_POS_3
		dipIOM15[0][15].Connect( pBundle, 3 );// 15-PLD_SEL_MONITOR
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
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM15 );
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
						// 01 PORT_MPM_STOW CMD 1
						// 01 PORT MID RETNN R-F-L 1
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 DIH
						// 01 PORT MID MRL LATCH IND 1
						break;
					case 0b0101:// IOM 5 DIH
						// 02 PORT MID MRL RELEASE IND 1
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						// 00 PORT_MID_MECH_DEPLOY_IND_2
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						// 01 PORT_MID_MECH_STOW_IND_2
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						break;
					case 0b1101:// IOM 13 DIH
						// 01 PORT MRL LATCH CMD 1
						break;
					case 0b1110:// IOM 14 AIS
						break;
					case 0b1111:// IOM 15 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM15 );

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

	void SimpleMDM_OF4::OnPreStep( double simt, double simdt, double mjd )
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
