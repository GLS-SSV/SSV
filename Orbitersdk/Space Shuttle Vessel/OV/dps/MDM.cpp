#include "MDM.h"
#include "IOM.h"
#include "../gnc/RA.h"


namespace dps
{
	MDM::MDM( AtlantisSubsystemDirector* _director, const string& _ident, BusManager* pBusManager, const unsigned short BusAddr, const BUS_ID PriBus, const BUS_ID SecBus ):AtlantisSubsystem( _director, _ident ), BusTerminal( pBusManager ),
		powered(true), addr(BusAddr)
	{
		if (PriBus < ___LAST___BUS_ID_SIZE) BusConnect( PriBus );
		if (SecBus < ___LAST___BUS_ID_SIZE) BusConnect( SecBus );
		return;
	}

	MDM::~MDM()
	{
		return;
	}

	void MDM::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (addr != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned char wdcount = ((rcvd[0] >> 1) & 0b11111) + 1;// data words (rcvd = 0b00000 => 1 word)
		unsigned char modecontrol = (rcvd[0] >> 15) & 0b1111;
		unsigned char IOMaddr = (rcvd[0] >> 11) & 0b1111;
		unsigned char IOMch = (rcvd[0] >> 6) & 0b11111;
		unsigned short IOMdata = 0;

		switch (modecontrol)
		{
			case 0b0000:// (spare)
				break;
			case 0b0001:// BITE function (return)
				break;
			case 0b0010:// indirect mode
				break;
			case 0b0011:// (spare)
				break;
			case 0b0100:// SCU BITE test
				break;
			case 0b0101:// A/D BITE test
				break;
			case 0b0110:// power supply BITE test
				break;
			case 0b0111:// IOM BITE test
				break;
			case 0b1000:// direct mode output (GPC-to-MDM)
				{
					if (datalen != (wdcount + 1)) return;

					// check parity
					if (CalcParity( rcvd[1] ) == 0) return;

					// check address
					int dataaddr = (rcvd[1] >> 20) & 0b11111;
					if (addr != dataaddr) return;

					// check SEV
					unsigned short SEV = (rcvd[1] >> 1) & 0b111;
					if (SEV != 0b101) return;
				}
				IOMdata = (rcvd[1] >> 4) & 0xFFFF;
				
				iom[IOMaddr]->busSCU( IOMch, 0b001, IOMdata );
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				iom[IOMaddr]->busSCU( IOMch, 0b000, IOMdata );
				{
					unsigned int outdata = 0;

					outdata |= addr << 20;
					outdata |= IOMdata << 4;
					outdata |= 0b101 << 1;// SEV
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
				}
				break;
			case 0b1010:// return the contents of the MDM BITE status register and reset the register
				break;
			case 0b1011:// master reset
				for (auto x : iom) x->busSCU( 0, 0b010, IOMdata );
				break;
			case 0b1100:// return the command word
				{
					unsigned short returnword = (rcvd[0] >> 1) & 0b11111111111111;
					returnword = (returnword & 0b00111111111111) << 2;

					unsigned int outdata = 0;

					outdata |= addr << 20;
					outdata |= 0b1100 << 15;// mode control
					outdata |= returnword << 1;// word wrap pattern
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
				}
				break;
			case 0b1101:// (spare)
				break;
			case 0b1110:// BITE function (load)
				break;
			case 0b1111:// (spare)
				break;
		}
		return;
	}
	
	bool MDM::OnParseLine( const char* line )
	{
		for (auto x : iom) x->LoadState( line );
		return false;
	}

	void MDM::OnSaveState( FILEHANDLE scn ) const
	{
		for (const auto x : iom) x->SaveState( scn );
		return;
	}

	void MDM::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power1.IsSet() && !Power2.IsSet())
		{
			if (powered)
			{
				// power loss -> set outputs to 0
				for (auto x : iom) x->PowerLoss();
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
