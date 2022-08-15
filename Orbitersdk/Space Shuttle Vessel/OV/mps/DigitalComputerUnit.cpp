/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "DigitalComputerUnit.h"
#include "SSMEController.h"
#include "PowerSupplyElectronics.h"
#include "ComputerInterfaceElectronics.h"
#include "SSMEControllerSW_AD08.h"
#include "MPSdefs.h"


namespace mps
{
	DigitalComputerUnit::DigitalComputerUnit( int ch, int ramsize, const std::string& sw, SSMEController* Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " DigitalComputerUnit::DigitalComputerUnit in || ch:%d|ramsize:%d|sw:%s", ch, ramsize, sw.c_str() );
#endif// _MPSDEBUG

		funct = NULL;
		this->ramsize = ramsize;
		RAM = new unsigned short[ramsize]();

		this->ch = ch;
		this->Controller = Controller;

		/*if (!strcmp( sw.c_str(), "AD06" ))
		this->sw = new SSMEControllerSW_AD08( this );
		else if (!strcmp( sw.c_str(), "AD07" ))
		this->sw = new SSMEControllerSW_AD08( this );
		else if (!strcmp( sw.c_str(), "AD08" ))
		this->sw = new SSMEControllerSW_AD08( this );
		else*/
		this->sw = new SSMEControllerSW_AD08( this );

#ifdef _MPSDEBUG
		oapiWriteLog( " DigitalComputerUnit::DigitalComputerUnit out" );
#endif// _MPSDEBUG
		return;
	}

	DigitalComputerUnit::~DigitalComputerUnit( void )
	{
		delete[] RAM;
		delete sw;
		return;
	}

	void DigitalComputerUnit::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[32];
		int config = 0;

		if (funct != nullptr) config = sw->GetConfig();

		sprintf_s( cbuf, 32, "DCU_ch%c config", ch + 65 );
		oapiWriteScenario_int( scn, cbuf, config );
		return;
	}

	bool DigitalComputerUnit::OnParseLine( const char* line )
	{
		int read_i = 0;
		char cbuf_ch[16];

		sprintf_s( cbuf_ch, 16, "DCU_ch%c", ch + 65 );

		if (!_strnicmp( line, cbuf_ch, 7 ))
		{
			if (!_strnicmp( line + 8, "config", 6 ))
			{
				sscanf_s( line + 14, "%d", &read_i );

				if (read_i == 0)
				{
					funct = NULL;// PROM
				}
				else
				{
					funct = &SSMEControllerSW::Executive;
					sw->SetConfig( read_i );
				}
#ifdef _MPSDEBUG
				oapiWriteLogV( " DigitalComputerUnit::OnParseLine || %s config:%d", cbuf_ch, read_i );
#endif// _MPSDEBUG
				return true;
			}
		}

		return false;
	}

	void DigitalComputerUnit::Realize( void )
	{
		PSE = Controller->PSE[ch];
		CIE = Controller->CIE[ch];
		return;
	}

	unsigned short DigitalComputerUnit::DIO_in( unsigned short device )
	{
		return CIE->DIO( device /*+ 0x0000*/, 0 );
	}

	void DigitalComputerUnit::DIO_out( unsigned short device, unsigned short data )
	{
		CIE->DIO( device + 0x8000, data );
		return;
	}

	void DigitalComputerUnit::DMA_write( unsigned short selectcontrol, unsigned short writeaddress, unsigned short writelength )
	{
		CIE->DMA_ch3( selectcontrol, writeaddress, writelength );
		return;
	}

	void DigitalComputerUnit::DMA_read( unsigned short selectcontrol, unsigned short readaddress, unsigned short readlength )
	{
		if (selectcontrol == 1)// assume it's 1 or 2 only
		{
			CIE->DMA_ch1( readaddress, readlength );
		}
		else
		{
			CIE->DMA_ch2( readaddress, readlength );
		}
		return;
	}

	void DigitalComputerUnit::PowerFailureSense( void )// TODO INT_PRI
	{
		if (sw != NULL) sw->Interrupt( INT_PFI );// TODO if NULL use PROM
		return;
	}

	void DigitalComputerUnit::Interrupt( int num )
	{
		if (sw != NULL) sw->Interrupt( num );// TODO if NULL use PROM
		return;
	}
}