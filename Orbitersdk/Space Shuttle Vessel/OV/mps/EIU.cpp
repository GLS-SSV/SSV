/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/21   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/06   GLS
2023/05/12   GLS
2023/05/14   GLS
********************************************/
#include "EIU.h"
#include "../Atlantis.h"
#include "SSME.h"
#include "SSMEController.h"
#include "MPSdefs.h"
#include "../SSVOptions.h"
#include <cassert>
#include <Orbitersdk.h>


namespace mps
{
	constexpr unsigned short EIU_FC_ADDR[3] = {
		17,
		23,
		24
	};


	bool ValidateDataWord( const unsigned int dataword, const unsigned short address )
	{
		// check parity
		if (CalcParity( dataword ) == 0) return false;

		// check address
		int dataaddr = (dataword >> 20) & 0b11111;
		if (address != dataaddr) return false;

		// check SEV
		unsigned short SEV = (dataword >> 1) & 0b111;
		if (SEV != 0b101) return false;

		return true;
	}


	EIU::EIU( AtlantisSubsystemDirector* _director, const string& _ident, int ID, SSME* eng, BusManager* pBusManager ):AtlantisSubsystem( _director, _ident ), BusTerminal( pBusManager ),
		DataRecorderOn(false)
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " EIU::EIU in || name:%s|ID:%d", _ident.c_str(), ID );
#endif// _MPSDEBUG

		this->ID = ID;
		this->eng = eng;

		// zeroing
		memset( StatusRegisterA, 0, 32 * sizeof(unsigned short) );
		memset( StatusRegisterB, 0, 32 * sizeof(unsigned short) );

		// give ref
		eng->Controller->GetEIURef( this );

#ifdef _MPSDEBUG
		oapiWriteLog( " EIU::EIU out" );
#endif// _MPSDEBUG

		if (STS()->GetOptions()->EIUDataRecorder())
		{
			char fname[32];
			sprintf_s( fname, 32, "EIU_data_ch%d.txt", ID );
			if (fopen_s( &fp, fname, "w" ) == 0) DataRecorderOn = true;
			else oapiWriteLogV( "(SSV_OV) [ERROR] Failed to open file %s", fname );
		}

		// HACK so ESW isn't 0 when read by the GPCs at first time step
		StatusRegisterA[2] = 27264;
		StatusRegisterB[2] = 27264;

		BusConnect( BUS_FC5 );
		BusConnect( BUS_FC6 );
		BusConnect( BUS_FC7 );
		BusConnect( BUS_FC8 );
		return;
	}

	EIU::~EIU( void )
	{
		if (DataRecorderOn) fclose( fp );
		return;
	}

	void EIU::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (Power() == false) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (EIU_FC_ADDR[ID - 1] != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned short wdcount = ((rcvd[0] >> 1) & 0b11111) + 1;// data words (rcvd = 0b00000 => 1 word)

		unsigned short modecontrol = (rcvd[0] >> 15) & 0b11111;


		// determine MIA receiving data
		unsigned short MIA;
		if (ID == 1)
		{
			if (id == BUS_FC5) MIA = 1;
			else if (id == BUS_FC6) MIA = 2;
			else if (id == BUS_FC7) MIA = 3;
			else /*if (id == BUS_FC8)*/ MIA = 4;
		}
		else if (ID == 2)
		{
			if (id == BUS_FC5) MIA = 3;
			else if (id == BUS_FC6) MIA = 1;
			else if (id == BUS_FC7) MIA = 2;
			else /*if (id == BUS_FC8)*/ MIA = 4;
		}
		else// if (ID == 3)
		{
			if (id == BUS_FC5) MIA = 2;
			else if (id == BUS_FC6) MIA = 3;
			else if (id == BUS_FC7) MIA = 1;
			else /*if (id == BUS_FC8)*/ MIA = 4;
		}

		//// process command data words
		switch (modecontrol)
		{
			case 0b00001:// return contents of status register
				{
					unsigned int outdata[32];
					memset( outdata, 0, 32 * sizeof(unsigned int) );

					unsigned short* reg = (MIA == 4) ? StatusRegisterB : StatusRegisterA;
					for (unsigned int i = 0; i < wdcount; i++)
					{
						outdata[i] |= EIU_FC_ADDR[ID - 1] << 20;
						outdata[i] |= reg[i] << 4;
						outdata[i] |= 0b101 << 1;// SEV
						outdata[i] |= (~CalcParity( outdata[i] )) & 1;// parity
					}

					Tx( id, outdata, wdcount );
				}
				break;
			case 0b00010:// return EIU GPC BITE register
				break;
			case 0b00111:// return received command word
				break;
			case 0b01000:// select secondary status channel as OI data source
				break;
			case 0b01011:// master reset, set GPC and OI BITE to 0, return to primary OI status channel
				break;
			case 0b10011:// transfer next 2 incoming words to ME controller
				{
					// HACK only using 1 data word
					if (wdcount != 1) break;// check word count
					if (datalen != 2) break;// check received words
					if (ValidateDataWord( rcvd[1], EIU_FC_ADDR[ID - 1] ) == false) break;

					unsigned short cmd = (rcvd[1] >> 4) & 0xFFFF;

					if (MIA == 1) eng->Controller->VIE_CommandDataConverter_write( chA, cmd );
					else if (MIA == 2) eng->Controller->VIE_CommandDataConverter_write( chB, cmd );
					else eng->Controller->VIE_CommandDataConverter_write( chC, cmd );// HACK change implementation so only one command is sent
				}
				break;
		}
		return;
	}

	void EIU::CIA( int num, unsigned short* data )
	{
		assert( (num >= 1) && (num <= 2) && "EIU::CIA.num" );
		// TODO create Status Override Switch and CIAs
		// output to OPS Recorder, FM Signal Processor and T-0 Umbilical
		if (num == 1)
		{
			// pri data
			memcpy( StatusRegisterA, data, 32 * sizeof(unsigned short) );// partial data for GPCs

			if (DataRecorderOn) DataRecorder( data, "PRI" );// save all telemetry
		}
		else
		{
			// sec data
			memcpy( StatusRegisterB, data, 32 * sizeof(unsigned short) );// partial data for GPCs

			if (DataRecorderOn) DataRecorder( data, "SEC" );// save all telemetry
		}
		return;
	}

	void EIU::Realize( void )
	{
		// connect to panel O17 EIU power switches
		DiscreteBundle* O17_to_EIU = BundleManager()->CreateBundle( "O17_to_EIU", 3 );

		switch (ID)
		{
			case 1:
				// C
				// MNA APC4 / MNB APC5
				power1.Connect( O17_to_EIU, 0 );
				power2.Connect( O17_to_EIU, 1 );
				break;
			case 2:
				// L
				// MNB APC5 / MNC APC6
				power1.Connect( O17_to_EIU, 1 );
				power2.Connect( O17_to_EIU, 2 );
				break;
			case 3:
				// R
				// MNC APC6 / MNA APC4
				power1.Connect( O17_to_EIU, 2 );
				power2.Connect( O17_to_EIU, 0 );
				break;
		}
		return;
	}

	bool EIU::OnParseLine( const char* line )
	{
		return false;
	}

	void EIU::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void EIU::OnPostStep( double simt, double simdt, double mjd )
	{
		return;
	}

	/*
	FR A5-107
	(...) One example of a transient failure is an EIU power-on-reset failure. A power-on-reset failure causes the
	temporary loss of a single power supply in an EIU. Since the EIU MIA ports 1 and 3 are on the same
	power source (MIA ports 2 and 4 are on another), this failure will cause the temporary loss of command
	and data transfer capability on two MIA ports (ground data only shows the status of MIA ports 1 and 4;
	therefore, MIA ports 3 and 2 are assumed bypassed with ports 1 and 4, respectively). After this failure has
	occurred, the command transfer capability will be regained automatically while the data transfer
	capability will be regained via an I/O Reset. The following scenario is an example of the concern that this
	failure raises: If an engine has a command channel B failure and a power-on-reset failure on MIA ports 1
	and 3, the engine will be considered to have suspect command capability even if the engine responds to
	throttle commands and will be shut down pre-MECO.
	*/

	void EIU::command( unsigned short cmd )// only PSN4 command arrives here
	{// HACK just one cmd arrives at the moment
		if (Power() == false) return;

		eng->Controller->VIE_CommandDataConverter_write( chA, cmd );
		eng->Controller->VIE_CommandDataConverter_write( chB, cmd );
		eng->Controller->VIE_CommandDataConverter_write( chC, cmd );
		return;
	}

	void EIU::DataRecorder( unsigned short* data, char* type )
	{
		int count = 0;

		fprintf( fp, "%s,", type );
		while (count < 128)
		{
			fprintf( fp, "%d,", data[count] );
			count++;
		}
		fprintf( fp, "\n" );
		return;
	}

	bool EIU::Power( void ) const// TODO internal power supply A, B and C
	{
		return power1.IsSet() | power2.IsSet();
	}
}