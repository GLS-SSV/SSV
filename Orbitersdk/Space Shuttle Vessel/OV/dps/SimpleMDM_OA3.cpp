#include "SimpleMDM_OA3.h"


namespace dps
{
	SimpleMDM_OA3::SimpleMDM_OA3( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):SimpleMDM( _director, "SimpleMDM_OA3", pBusManager ),
		powered(true)
	{
		// HACK no PCMMU yet, so connect to PL busses
		BusConnect( BUS_PL1 );
		BusConnect( BUS_PL2 );
		return;
	}

	SimpleMDM_OA3::~SimpleMDM_OA3()
	{
	}

	void SimpleMDM_OA3::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 11 );
		Power2.Connect( pBundle, 11 );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM1[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM1[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM1[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM5[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM5[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM5[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM7_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM7[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM7_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM7[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM7_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM7[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM10_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM10[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM10_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM10[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM10_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM10[2][i].Connect( pBundle, i );

		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
		for (int i = 0; i < 16; i++) dipIOM12[0][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
		for (int i = 0; i < 16; i++) dipIOM12[1][i].Connect( pBundle, i );
		pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH2", 16 );
		for (int i = 0; i < 16; i++) dipIOM12[2][i].Connect( pBundle, i );
		return;
	}

	void SimpleMDM_OA3::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (OA3_ADDR != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned short wdcount = ((rcvd[0] >> 1) & 0b11111) + 1;// data words (rcvd = 0b00000 => 1 word)
		unsigned short modecontrol = (rcvd[0] >> 15) & 0b1111;
		unsigned short IOMaddr = (rcvd[0] >> 11) & 0b1111;
		unsigned short IOMch = (rcvd[0] >> 6) & 0b11111;
		unsigned short IOMdata = 0;

		switch (modecontrol)
		{
			case 0b1000:// direct mode output (GPC-to-MDM)
				{
					if (datalen != (wdcount + 1)) return;

					// check parity
					if (CalcParity( rcvd[1] ) == 0) return;

					// check address
					int dataaddr = (rcvd[1] >> 20) & 0b11111;
					if (OA3_ADDR != dataaddr) return;

					// check SEV
					unsigned short SEV = (rcvd[1] >> 1) & 0b111;
					if (SEV != 0b101) return;
				}
				IOMdata = (rcvd[1] >> 4) & 0xFFFF;
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AIS
						break;
					case 0b0001:// IOM 1 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM1 );
						break;
					case 0b0010:// IOM 2 AIS
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 AIS
						break;
					case 0b0101:// IOM 5 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM7 );
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM10 );
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
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
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM1 );
						break;
					case 0b0010:// IOM 2 AIS
						break;
					case 0b0011:// IOM 3 DIL
						break;
					case 0b0100:// IOM 4 AIS
						break;
					case 0b0101:// IOM 5 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						break;
					case 0b0111:// IOM 7 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM7 );
						break;
					case 0b1000:// IOM 8 DIL
						break;
					case 0b1001:// IOM 9 AIS
						break;
					case 0b1010:// IOM 10 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM10 );
						break;
					case 0b1011:// IOM 11 AIS
						break;
					case 0b1100:// IOM 12 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM12 );
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIL
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				{
					unsigned int outdata = 0;

					outdata |= OA3_ADDR << 20;
					outdata |= IOMdata << 4;
					outdata |= 0b101 << 1;// SEV
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
				}
				break;
			case 0b1100:// return the command word
				{
					unsigned short returnword = (rcvd[0] >> 1) & 0b11111111111111;
					returnword = (returnword & 0b00111111111111) << 2;

					unsigned int outdata = 0;

					outdata |= OA3_ADDR << 20;
					outdata |= 0b1100 << 15;// mode control
					outdata |= returnword << 1;// word wrap pattern
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
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
