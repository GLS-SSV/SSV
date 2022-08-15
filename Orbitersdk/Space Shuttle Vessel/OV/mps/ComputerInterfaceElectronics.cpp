/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "ComputerInterfaceElectronics.h"
#include "VehicleInterfaceElectronics.h"
#include "PowerSupplyElectronics.h"
#include "DigitalComputerUnit.h"
#include "InputElectronics.h"
#include "OutputElectronics.h"
#include "SSMEController.h"
#include "MPSdefs.h"


namespace mps
{
	ComputerInterfaceElectronics::ComputerInterfaceElectronics( int ch, SSMEController* Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " ComputerInterfaceElectronics::ComputerInterfaceElectronics in || ch:%d", ch );
#endif// _MPSDEBUG

		this->ch = ch;
		this->Controller = Controller;

		dWDT[0] = 0;
		dWDT[1] = 0;
		bWDT[0] = true;// start timed out
		bWDT[1] = true;

#ifdef _MPSDEBUG
		oapiWriteLog( " ComputerInterfaceElectronics::ComputerInterfaceElectronics out" );
#endif// _MPSDEBUG
		return;
	}

	ComputerInterfaceElectronics::~ComputerInterfaceElectronics( void )
	{
		return;
	}

	void ComputerInterfaceElectronics::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[32];
		int config = 1;

		if (bWDT[0] == true) config = 2;

		sprintf_s( cbuf, 32, "CIE_ch%c config", ch + 65 );
		oapiWriteScenario_int( scn, cbuf, config );
		return;
	}

	bool ComputerInterfaceElectronics::OnParseLine( const char* line )
	{
		int read_i = 0;
		char cbuf_ch[16];

		sprintf_s( cbuf_ch, 16, "CIE_ch%c", ch + 65 );

		if (!_strnicmp( line, cbuf_ch, 7 ))
		{
			if (!_strnicmp( line + 8, "config", 6 ))
			{
				sscanf_s( line + 14, "%d", &read_i );
				if (read_i == 1)
				{
					bWDT[0] = false;
					bWDT[1] = false;
				}
				else
				{
					bWDT[0] = true;
					bWDT[1] = true;
				}
#ifdef _MPSDEBUG
				oapiWriteLogV( " ComputerInterfaceElectronics::OnParseLine || %s config:%d", cbuf_ch, read_i );
#endif// _MPSDEBUG
				return true;
			}
		}

		return false;
	}

	void ComputerInterfaceElectronics::tmestp( double time, double dt )
	{
		this->time = time;
		this->dt = dt;
		return;
	}

	void ComputerInterfaceElectronics::Realize( void )
	{
		PSE = Controller->PSE[ch];
		DCU = Controller->DCU[ch];
		VIE = Controller->VIE;
		IE[chA] = Controller->IE[chA];
		IE[chB] = Controller->IE[chB];
		OE[chA] = Controller->OE[chA];
		OE[chB] = Controller->OE[chB];
		if (ch == chA) CIEOpposite = Controller->CIE[chB];
		else CIEOpposite = Controller->CIE[chA];
		return;
	}

	void ComputerInterfaceElectronics::DMA_ch1( unsigned short readaddress, unsigned short readlength )
	{
		// read data to VIE
		// data recorder A
		unsigned short data[128];
		int count = 0;

		while (readlength > 0)// HACK assume readlength is always 128
		{
			data[count] = DCU->RAM[readaddress];
			readlength--;
			readaddress++;
			count++;
		}
		VIE->RecorderDataConverter_chA( data, ch );
		return;
	}

	void ComputerInterfaceElectronics::DMA_ch2( unsigned short readaddress, unsigned short readlength )
	{
		// read data to VIE
		// data recorder B
		unsigned short data[128];
		int count = 0;

		while (readlength > 0)// HACK assume readlength is always 128
		{
			data[count] = DCU->RAM[readaddress];
			readlength--;
			readaddress++;
			count++;
		}
		VIE->RecorderDataConverter_chB( data, ch );
		return;
	}

	void ComputerInterfaceElectronics::DMA_ch3( unsigned short selectcontrol, unsigned short writeaddress, unsigned short writelength )
	{
		// write data from IE
		unsigned short data = 0;
		int IEch = GetMaskVal( selectcontrol, 0xF000 ) >> 13;

		assert( (IEch >= 0) && (IEch <= 1) && "ComputerInterfaceElectronics::DMA_ch3.IEch" );

		while (writelength > 0)
		{
			IE[IEch]->GetData( selectcontrol, &data );
			DCU->RAM[writeaddress] = data;
			writelength--;
			writeaddress++;
			selectcontrol++;
		}
		return;
	}

	unsigned short ComputerInterfaceElectronics::DIO( unsigned short control, unsigned short data )
	{
		switch (GetMaskVal( control, 0x8000 ))
		{
			case DIO_DEV_INPUT:
				switch (GetMaskVal( control, 0x7000 ))
				{
					case DIO_DEV_OEchA:
						switch (GetMaskVal( control, 0x0F00 ))
						{
							case DIO_DEV_OE_STORAGE_REG:
								return OE[chA]->StorageRegister_read();
							case DIO_DEV_OE_ONOFF_REG_1:
								return OE[chA]->ONOFFCommandRegister_read( 1 );
							case DIO_DEV_OE_ONOFF_REG_2:
								return OE[chA]->ONOFFCommandRegister_read( 2 );
							default:
								oapiWriteLogV( " ComputerInterfaceElectronics::DIO || DIO_DEV_OEchA || %d %d", control, data );
						}
						break;
					case DIO_DEV_OEchB:
						switch (GetMaskVal( control, 0x0F00 ))
						{
							case DIO_DEV_OE_STORAGE_REG:
								return OE[chB]->StorageRegister_read();
							case DIO_DEV_OE_ONOFF_REG_1:
								return OE[chB]->ONOFFCommandRegister_read( 1 );
							case DIO_DEV_OE_ONOFF_REG_2:
								return OE[chB]->ONOFFCommandRegister_read( 2 );
							default:
								oapiWriteLogV( " ComputerInterfaceElectronics::DIO || DIO_DEV_OEchB || %d %d", control, data );
						}
						break;
					case DIO_DEV_VIE:
						switch (GetMaskVal( control, 0x0F00 ))
						{
							case DIO_DEV_VIE_CMD1:
								return VIE->CommandDataConverter_read( chA );
							case DIO_DEV_VIE_CMD2:
								return VIE->CommandDataConverter_read( chB );
							case DIO_DEV_VIE_CMD3:
								return VIE->CommandDataConverter_read( chC );
							default:
								oapiWriteLogV( " ComputerInterfaceElectronics::DIO || DIO_DEV_VIE || %d %d", control, data );
						}
						break;
					default:
						oapiWriteLogV( " ComputerInterfaceElectronics::DIO || DIO_DEV_INPUT || %d %d", control, data );
				}
				break;
			case DIO_DEV_OUTPUT:
				switch (GetMaskVal( control, 0x7000 ))
				{
					case DIO_DEV_OEchA:
						OE[chA]->StorageRegister_write( data, ch );
						break;
					case DIO_DEV_OEchB:
						OE[chB]->StorageRegister_write( data, ch );
						break;
					default:
						oapiWriteLogV( " ComputerInterfaceElectronics::DIO || DIO_DEV_OUTPUT || %d %d", control, data );
				}
				break;
			default:
				oapiWriteLogV( " ComputerInterfaceElectronics::DIO || %d %d", control, data );
		}
		return 0;
	}

	void ComputerInterfaceElectronics::InitializeWDT( int nWDT )
	{
		// TODO use both DCU and OE
		assert( (nWDT >= 0) && (nWDT <= 1) && "ComputerInterfaceElectronics::InitializeWDT.nWDT" );

		bWDT[nWDT] = false;
		dWDT[nWDT] = time;
		return;
	}

	void ComputerInterfaceElectronics::ResetWDT( int nWDT )
	{
		assert( (nWDT >= 0) && (nWDT <= 1) && "ComputerInterfaceElectronics::ResetWDT.nWDT" );

		dWDT[nWDT] = time;
		return;
	}

	bool ComputerInterfaceElectronics::CheckWDTOwn( int nWDT )// TODO improve WDTs
	{
		assert( (nWDT >= 0) && (nWDT <= 1) && "ComputerInterfaceElectronics::CheckWDTOwn.nWDT" );

		if (bWDT[nWDT] == false)
		{
			if (time == dWDT[nWDT])
			{
				return false;
			}
			else
			{
				bWDT[nWDT] = true;
				return true;
			}
		}
		return true;
	}

	bool ComputerInterfaceElectronics::CheckWDTOpposite( int nWDT )
	{
		assert( (nWDT >= 0) && (nWDT <= 1) && "ComputerInterfaceElectronics::CheckWDTOpposite.nWDT" );

		if (ch == chA)
		{
			if (CIEOpposite->bWDT[nWDT] == false)
			{
				if ((time - CIEOpposite->dWDT[nWDT]) > (dt + 0.00001))// add something due to uncertainties
				{
					CIEOpposite->bWDT[nWDT] = true;
					return true;
				}
				else
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			if (CIEOpposite->bWDT[nWDT] == false)
			{
				if ((CIEOpposite->dWDT[nWDT] - time) > (0 + 0.00001))// add something due to uncertainties
				{
					CIEOpposite->bWDT[nWDT] = true;
					return true;
				}
				else
				{
					return false;
				}
			}
			return true;
		}
	}

	void ComputerInterfaceElectronics::Interrupt( int num )
	{
		DCU->Interrupt( num );
		return;
	}

	void ComputerInterfaceElectronics::PowerBusDown( void )
	{
		DCU->Interrupt( INT_PBDI );
		return;
	}

	void ComputerInterfaceElectronics::SwitchVRC( void )
	{
		VIE->SwitchVRC();
		return;
	}

	void ComputerInterfaceElectronics::RestoreVRC( void )
	{
		VIE->RestoreVRC();
		return;
	}
}