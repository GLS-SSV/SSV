/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/29   GLS
2022/05/13   GLS
2022/05/19   GLS
2022/05/29   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/07/02   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/09   GLS
2022/10/20   GLS
2022/10/25   GLS
2022/10/27   GLS
2022/11/15   GLS
2022/12/23   GLS
2023/05/14   GLS
********************************************/
#include "SimpleFCOS_IO.h"
#include "../SimpleGPCSystem.h"


namespace dps
{
	constexpr unsigned short WordWrapPattern = 0b10110001110010;// HACK no clue of actual value, or if dynamic


	static void AnnounceIOError( SimpleGPCSystem* pGPC, const char* minorfield )
	{
		char cbuf[32];
		sprintf_s( cbuf, "    I/O ERROR  %s", minorfield );
		unsigned int j = pGPC->ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
		if (j < 5)
		{
			pGPC->WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, cbuf, 5, 19 );
			pGPC->WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
			pGPC->WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
		}
		return;
	}

	SimpleFCOS_IO::SimpleFCOS_IO( SimpleGPCSystem* _gpc )
	{
		pGPC = _gpc;
	}

	SimpleFCOS_IO::~SimpleFCOS_IO()
	{
	}

	void SimpleFCOS_IO::MDMReturnWord( unsigned short addr, unsigned short commfault_word, unsigned short commfault_counter, unsigned int commfault_word_mask, const char* minorfield, BUS_ID busid )
	{
		unsigned int data[2];
		memset( data, 0, 2 * sizeof(unsigned int) );
		pGPC->WriteBufferAddress = SCP_MDM_RETURN;
		pGPC->WriteBufferLength = 1;
		pGPC->SubSystemAddress = addr;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= ModeControl_MDM_ReturnWord << 15;// mode control
		data[0] |= WordWrapPattern << 1;// wrap word pattern
		data[0] |= (~CalcParity( data[0] )) & 1;// parity

		pGPC->SimpleCOMPOOL[SCP_MDM_RETURN] = 0;
		pGPC->_Tx( busid, data, 1 );

		unsigned int counter = pGPC->ReadCOMPOOL_ID( commfault_counter );

		// check return
		if (pGPC->SimpleCOMPOOL[SCP_MDM_RETURN] != ((WordWrapPattern & 0b00111111111111) << 2))
		{
			if ((counter & commfault_word_mask) != 0)
			{
				// 2º strike
				unsigned int cfw = pGPC->ReadCOMPOOL_ID( commfault_word );
				cfw |= commfault_word_mask;
				pGPC->WriteCOMPOOL_ID( commfault_word, cfw );
				AnnounceIOError( pGPC, minorfield );
			}
			else
			{
				// 1º strike
				counter |= commfault_word_mask;
				pGPC->WriteCOMPOOL_ID( commfault_counter, counter );
			}
		}
		else
		{
			// reset counter
			counter |= !commfault_word_mask;
			pGPC->WriteCOMPOOL_ID( commfault_counter, counter );
		}
		return;
	}

	void SimpleFCOS_IO::InputMDM( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr, BUS_ID busid )
	{
		unsigned int data[2];
		memset( data, 0, 2 * sizeof(unsigned int) );
		pGPC->WriteBufferAddress = memoryaddr;
		pGPC->WriteBufferLength = 1;
		pGPC->SubSystemAddress = addr;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= mode << 15;// mode control
		data[0] |= moduleaddr << 11;// IOM address
		data[0] |= modulech << 6;// channel address
		data[0] |= (1 - 1) << 1;// number of words
		data[0] |= (~CalcParity( data[0] )) & 1;// parity

		pGPC->_Tx( busid, data, 1 );
		return;
	}

	void SimpleFCOS_IO::OutputMDM( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr, BUS_ID busid )
	{
		unsigned int data[2];
		memset( data, 0, 2 * sizeof(unsigned int) );
		pGPC->WriteBufferAddress = memoryaddr;
		pGPC->WriteBufferLength = 1;
		pGPC->SubSystemAddress = addr;

		// build command word
		data[0] |= addr << 20;// MIA address
		data[0] |= mode << 15;// mode control
		data[0] |= moduleaddr << 11;// IOM address
		data[0] |= modulech << 6;// channel address
		data[0] |= (1 - 1) << 1;// number of words
		data[0] |= (~CalcParity( data[0] )) & 1;// parity

		// build command data word
		data[1] |= addr << 20;// MIA address
		data[1] |= pGPC->SimpleCOMPOOL[memoryaddr] << 4;// data
		data[1] |= 0b101 << 1;// SEV
		data[1] |= (~CalcParity( data[1] )) & 1;// parity

		pGPC->_Tx( busid, data, 2 );

		// reset memory location
		pGPC->SimpleCOMPOOL[memoryaddr] = 0;
		return;
	}
}
