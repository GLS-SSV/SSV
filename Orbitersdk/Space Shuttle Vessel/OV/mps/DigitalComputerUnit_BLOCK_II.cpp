/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "DigitalComputerUnit_BLOCK_II.h"
#include "SSMEController.h"
#include "PowerSupplyElectronics.h"
#include "ComputerInterfaceElectronics.h"
#include "SSMEControllerSW.h"
#include "MPSdefs.h"


namespace mps
{
	DigitalComputerUnit_BLOCK_II::DigitalComputerUnit_BLOCK_II( int ch, const std::string& sw, SSMEController* Controller ):DigitalComputerUnit( ch, RAMSIZE_DCU_BII, sw, Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " DigitalComputerUnit_BLOCK_II::DigitalComputerUnit_BLOCK_II in || ch:%d|sw:%s", ch, sw.c_str() );
#endif// _MPSDEBUG

		funct = &SSMEControllerSW::Executive;

#ifdef _MPSDEBUG
		oapiWriteLog( " DigitalComputerUnit_BLOCK_II::DigitalComputerUnit_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	DigitalComputerUnit_BLOCK_II::~DigitalComputerUnit_BLOCK_II( void )
	{
		return;
	}

	void DigitalComputerUnit_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		DigitalComputerUnit::OnSaveState( scn );
		return;
	}

	bool DigitalComputerUnit_BLOCK_II::OnParseLine( const char* line )
	{
		return DigitalComputerUnit::OnParseLine( line );
	}

	void DigitalComputerUnit_BLOCK_II::tmestp( double time, double tmestp )
	{
		this->time = time;
		this->dt = tmestp;

		// check power supply
		if (PSE->Power() == true)
		{
			if (funct == nullptr)
			{
				PROM();// run PROM
			}
			else
			{
				(sw->*funct)();// run SW
			}
		}
		else
		{
			// do nothing
			// set funcptr to PROM, so it's ready when power on
			funct = nullptr;
		}
		return;
	}

	void DigitalComputerUnit_BLOCK_II::PROM( void )
	{
		// set phase/mode
		RAM[RAM_PROM_BII_ESW] = ESW_PROM + ESW_Standby;

		// get commands
		RAM[RAM_PROM_BII_CMD1] = DIO_in( DEV_CIE_VIE_CMD1 );
		RAM[RAM_PROM_BII_CMD2] = DIO_in( DEV_CIE_VIE_CMD2 );
		RAM[RAM_PROM_BII_CMD3] = DIO_in( DEV_CIE_VIE_CMD3 );

		if (RAM[RAM_PROM_BII_CMD1] == RAM[RAM_PROM_BII_CMD2])
		{
			if (RAM[RAM_PROM_BII_CMD2] == RAM[RAM_PROM_BII_CMD3])
			{
				// 1 good
				// 2 good
				// 3 good
				RAM[RAM_PROM_BII_VALIDCMD] = RAM[RAM_PROM_BII_CMD3];
			}
			else
			{
				// 1 good
				// 2 good
				// 3 bad
				RAM[RAM_PROM_BII_VALIDCMD] = RAM[RAM_PROM_BII_CMD2];
			}
		}
		else
		{
			if (RAM[RAM_PROM_BII_CMD2] == RAM[RAM_PROM_BII_CMD3])
			{
				// 1 bad
				// 2 good
				// 3 good
				RAM[RAM_PROM_BII_VALIDCMD] = RAM[RAM_PROM_BII_CMD3];
			}
			else
			{
				if (RAM[RAM_PROM_BII_CMD1] == RAM[RAM_PROM_BII_CMD3])
				{
					// 1 good
					// 2 bad
					// 3 good
					RAM[RAM_PROM_BII_VALIDCMD] = RAM[RAM_PROM_BII_CMD3];
				}
				else
				{
					// 1 bad
					// 2 bad
					// 3 bad
					RAM[RAM_PROM_BII_VALIDCMD] = NOP;
					RAM[RAM_PROM_BII_ESW] += ESW_CommandRejected_A;
				}
			}
		}

		switch (RAM[RAM_PROM_BII_VALIDCMD])
		{
			case NOP:// do nothing
				break;
			case RVRC:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				CIE->RestoreVRC();
				break;
			case SVRC:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				CIE->SwitchVRC();
				break;
			case XFRT:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case MLDA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				CIE->InitializeWDT( 0 );
				CIE->InitializeWDT( 1 );
				break;
			case MLDB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case RSCA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case RSCB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case HELA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case HELB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case PSCA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case PSCB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case IOHA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case IOHB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case IOLA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case IOLB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case IOSA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case IOSB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case ENFA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case ENFB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case ROFA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case ROFB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case RWRA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case RWRB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case RSKA:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case RSKB:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case EXPM:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				funct = &SSMEControllerSW::Executive;
				break;
			case MRC1:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			case MRC2:
				RAM[RAM_PROM_BII_PRVCMD] = RAM[RAM_PROM_BII_CURCMD];
				RAM[RAM_PROM_BII_CURCMD] = RAM[RAM_PROM_BII_VALIDCMD];
				RAM[RAM_PROM_BII_ESW] += ESW_Accepted;
				break;
			default:
				RAM[RAM_PROM_BII_ESW] += ESW_CommandRejected_B;
				break;
		}

		// reset own WDT
		CIE->ResetWDT( 0 );
		CIE->ResetWDT( 1 );

		memset( &RAM[RAM_PROM_BII_DVDT_1], 0, 128 * sizeof(unsigned short) );// zeroing

		// check other channel
		RAM[32] = CIE->CheckWDTOpposite( 0 );
		RAM[33] = CIE->CheckWDTOpposite( 1 );

		// check own channel while we're at it
		RAM[30] = CIE->CheckWDTOwn( 0 );
		RAM[31] = CIE->CheckWDTOwn( 1 );

		RAM[26] = RAM[RAM_PROM_BII_CMD1];
		RAM[27] = RAM[RAM_PROM_BII_CMD2];
		RAM[28] = RAM[RAM_PROM_BII_CMD3];
		RAM[29] = RAM[RAM_PROM_BII_VALIDCMD];

		// update TREF 1
		RAM[RAM_PROM_BII_DVDT_1] = (unsigned short)(time * 100);

		// write ch
		RAM[RAM_PROM_BII_DVDT_2] = ch;

		// built DVDT
		// this is from Phase II PROM, not sure if changed since
		//RAM[RAM_PROM_BII_DVDT_1] = 1;// ID word 1
		//RAM[RAM_PROM_BII_DVDT_2] = 2;// ID word 2
		RAM[RAM_PROM_BII_DVDT_3] = RAM[RAM_PROM_BII_ESW];// Engine Status Word
		RAM[RAM_PROM_BII_DVDT_5] = 5;// FID/Delimiter
		RAM[RAM_PROM_BII_DVDT_90] = 90;// Inhibit Counter/PROM Rev.
		RAM[RAM_PROM_BII_DVDT_98] = RAM[RAM_PROM_BII_CURCMD];// Current Command
		RAM[RAM_PROM_BII_DVDT_99] = RAM[RAM_PROM_BII_PRVCMD];// Previous Command
		RAM[RAM_PROM_BII_DVDT_100] = 100;// FID/Delimiter
		RAM[RAM_PROM_BII_DVDT_103] = 103;// Parameter

		// output DVDT
		DMA_read( 1, RAM_PROM_BII_DVDT_1, 128 );
		DMA_read( 2, RAM_PROM_BII_DVDT_1, 128 );
		return;
	}
}