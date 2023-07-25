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

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM2_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM2[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM2_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM2[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM2_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM2[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM4_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM4[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM4_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM4[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM4_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM4[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM5_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM5[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM5_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM5[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM5_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM5[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM7[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM7[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM7[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM10[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM10[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM10[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM13_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM13[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM13_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM13[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM13_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM13[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM15[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM15[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM15[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
		dipIOM10[1][0].Connect( pBundle, 10 );// PORT MID MECH STOW IND 2
		dipIOM7[0][0].Connect( pBundle, 14 );// PORT MID MECH DEPLOY IND 2

		pBundle = BundleManager()->CreateBundle( "STBD_MPM_IND", 16 );
		dipIOM10[1][1].Connect( pBundle, 10 );// STBD MID MECH STOW IND 2
		dipIOM7[0][1].Connect( pBundle, 14 );// STBD MID MECH DEPLOY IND 2

		pBundle = BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
		dipIOM4[1][0].Connect( pBundle, 0 );// PORT MID MRL LATCH IND 1
		dipIOM5[2][0].Connect( pBundle, 1 );// PORT MID MRL RELEASE IND 1
		dipIOM2[1][1].Connect( pBundle, 4 );// PORT MID RETNN R-F-L 1
		dipIOM4[1][1].Connect( pBundle, 6 );// STBD MID MRL LATCH IND 1
		dipIOM5[2][1].Connect( pBundle, 7 );// STBD MID MRL RELEASE IND 1
		dipIOM2[1][2].Connect( pBundle, 10 );// STBD MID RETNN R-F-L 1
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
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM2 );
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM4 );
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
						break;
					case 0b1101:// IOM 13 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM13 );
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
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM2 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0011:// IOM 3 DIL
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
						break;
					case 0b1101:// IOM 13 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM13 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
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
