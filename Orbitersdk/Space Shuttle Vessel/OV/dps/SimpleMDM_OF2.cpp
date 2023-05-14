#include "SimpleMDM_OF2.h"


namespace dps
{
	SimpleMDM_OF2::SimpleMDM_OF2( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):SimpleMDM( _director, "SimpleMDM_OF2", pBusManager ),
		powered(true)
	{
		// HACK no PCMMU yet, so connect to PL busses
		BusConnect( BUS_PL1 );
		BusConnect( BUS_PL2 );
		return;
	}

	SimpleMDM_OF2::~SimpleMDM_OF2()
	{
	}

	void SimpleMDM_OF2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 12 );
		Power2.Connect( pBundle, 14 );

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_1", 10 );
		dipIOM14[0][1].Connect( pBundle, 0 );// 1-PL3_1A_LAT
		dipIOM14[0][0].Connect( pBundle, 1 );// 0-PL3_1A_REL
		dipIOM14[0][2].Connect( pBundle, 2 );// 2-PL3_1A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_1", 10 );
		dipIOM14[0][4].Connect( pBundle, 5 );// 4-PL1_1B_LAT
		dipIOM14[0][3].Connect( pBundle, 6 );// 3-PL1_1B_REL
		dipIOM14[0][5].Connect( pBundle, 7 );// 5-PL1_1B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
		dipIOM14[0][7].Connect( pBundle, 5 );// 7-PL2_1B_LAT
		dipIOM14[0][6].Connect( pBundle, 6 );// 6-PL2_1B_REL
		dipIOM14[0][8].Connect( pBundle, 7 );// 8-PL2_1B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_2", 10 );
		dipIOM14[0][10].Connect( pBundle, 0 );// 10-PL3_2A_LAT
		dipIOM14[0][9].Connect( pBundle, 1 );// 9-PL3_2A_REL
		dipIOM14[0][11].Connect( pBundle, 2 );// 11-PL3_2A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_2", 10 );
		dipIOM14[0][13].Connect( pBundle, 5 );// 13-PL1_2B_LAT
		dipIOM14[0][12].Connect( pBundle, 6 );// 12-PL1_2B_REL
		dipIOM14[0][14].Connect( pBundle, 7 );// 14-PL1_2B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
		dipIOM14[1][1].Connect( pBundle, 0 );// 1-PL3_3A_LAT
		dipIOM14[1][0].Connect( pBundle, 1 );// 0-PL3_3A_REL
		dipIOM14[1][2].Connect( pBundle, 2 );// 2-PL3_3A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_3", 10 );
		dipIOM14[1][4].Connect( pBundle, 5 );// 4-PL1_3B_LAT
		dipIOM14[1][3].Connect( pBundle, 6 );// 3-PL1_3B_REL
		dipIOM14[1][5].Connect( pBundle, 7 );// 5-PL1_3B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
		dipIOM14[1][7].Connect( pBundle, 0 );// 7-PL3_4A_LAT
		dipIOM14[1][6].Connect( pBundle, 1 );// 6-PL3_4A_REL
		dipIOM14[1][8].Connect( pBundle, 2 );// 8-PL3_4A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_4", 10 );
		dipIOM14[1][10].Connect( pBundle, 5 );// 10-PL1_4B_LAT
		dipIOM14[1][9].Connect( pBundle, 6 );// 9-PL1_4B_REL
		dipIOM14[1][11].Connect( pBundle, 7 );// 11-PL1_4B_RDY

		pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_5", 10 );
		dipIOM14[1][13].Connect( pBundle, 0 );// 13-PL2_5A_LAT
		dipIOM14[1][12].Connect( pBundle, 1 );// 12-PL2_5A_REL
		dipIOM14[1][14].Connect( pBundle, 2 );// 14-PL2_5A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
		dipIOM14[2][1].Connect( pBundle, 0 );// 1-PL3_5A_LAT
		dipIOM14[2][0].Connect( pBundle, 1 );// 0-PL3_5A_REL
		dipIOM14[2][2].Connect( pBundle, 2 );// 2-PL3_5A_RDY

		pBundle = BundleManager()->CreateBundle( "PL_1_SEL_LATCH_5", 10 );
		dipIOM14[2][4].Connect( pBundle, 5 );// 4-PL1_5B_LAT
		dipIOM14[2][3].Connect( pBundle, 6 );// 3-PL1_5B_REL
		dipIOM14[2][5].Connect( pBundle, 7 );// 5-PL1_5B_RDY
		return;
	}

	void SimpleMDM_OF2::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (OF2_ADDR != dataaddr) return;
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
					if (OF2_ADDR != dataaddr) return;

					// check SEV
					unsigned short SEV = (rcvd[1] >> 1) & 0b111;
					if (SEV != 0b101) return;
				}
				IOMdata = (rcvd[1] >> 4) & 0xFFFF;
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
						break;
					case 0b0101:// IOM 5 AIS
						break;
					case 0b0110:// IOM 6 DIH
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
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIH
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
						// 00 MID MCA 3 OPER STATUS 5
						// 00 MID MCA 3 OPER STATUS 6
						break;
					case 0b0101:// IOM 5 AIS
						break;
					case 0b0110:// IOM 6 DIH
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
						break;
					case 0b1101:// IOM 13 AIS
						break;
					case 0b1110:// IOM 14 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM14 );
						break;
					case 0b1111:// IOM 15 AIS
						break;
				}
				{
					unsigned int outdata = 0;

					outdata |= OF2_ADDR << 20;
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

					outdata |= OF2_ADDR << 20;
					outdata |= 0b1100 << 15;// mode control
					outdata |= returnword << 1;// word wrap pattern
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
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
