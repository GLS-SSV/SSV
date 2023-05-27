#include "KeyboardInterface.h"
#include "../SimpleGPCSystem.h"


namespace dps
{
	KeyboardInterface::KeyboardInterface( SimpleGPCSystem* pGPC ):pGPC(pGPC), DMIB_ERR_MSG(0)
	{
		return;
	}

	KeyboardInterface::~KeyboardInterface( void )
	{
		return;
	}

	void KeyboardInterface::DMI_MCDS_IN( void )
	{
		for (unsigned char deu = 1; deu <= 4; deu++)
		{
			unsigned short WD_1 = pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), 64 );

			// HACK filter DEU response processing according to MF
			unsigned short MF = (WD_1 >> 6) & 0b11;
			if (pGPC->GNC)
			{
				if (MF != 1) continue;
			}
			else
			{
				if (MF != 2) continue;
			}

			if (((WD_1 >> 3) & 1) == 1)// keyboard message present
			{
				// calc checksum
				unsigned int checksum = 0;
				for (int i = 1; i < 16; i++) checksum += pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, i + ((deu - 1) * 16), 64 );
				checksum = ((~checksum) + 1) & 0xFFFF;
				if (checksum != pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 16 + ((deu - 1) * 16), 64 ))
				{
					if (((DMIB_ERR_MSG >> (9 - deu)) & 1) == 0)// not announced before
					{
						DMIB_ERR_MSG |= 1 << (9 - deu);
						// TODO I/O ERROR deu X
						oapiWriteLogV( "I/O ERROR CRT %d", deu );
						// reset kybd msg present bit
						WD_1 &= ~(1 << 3);
						pGPC->WriteCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), WD_1, 64 );
					}
				}
				else
				{
					DMIB_ERR_MSG &= ~(1 << (9 - deu));
				}

				unsigned short WD_2 = pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 2 + ((deu - 1) * 16), 64 );
				if ((((WD_1 >> 3) & 1) == 1) && (((WD_2 >> 0) & 0b11111) == 0))// keyboard message present and key count is 0
				{
					// TODO log GPC error
					// reset kybd msg present bit
					WD_1 &= ~(1 << 3);
					pGPC->WriteCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), WD_1, 64 );
				}
			}

			DMM_MCDS_PROCESS( deu );
		}
		return;
	}

	void KeyboardInterface::DMM_MCDS_PROCESS( unsigned char deu )
	{
		unsigned short WD_1 = pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), 64 );
		unsigned short WD_2 = pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 2 + ((deu - 1) * 16), 64 );
		if (((WD_1 >> 3) & 1) == 1)// keyboard message present
		{
			// copy keys
			for (unsigned int i = 3, k = 1; i <= 12; i++)
			{
				unsigned short WD_x = pGPC->ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, i + ((deu - 1) * 16), 64 );

				pGPC->WriteCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + k++, (WD_x >> 11) & 0b11111, 120 );
				pGPC->WriteCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + k++, (WD_x >> 6) & 0b11111, 120 );
				pGPC->WriteCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + k++, (WD_x >> 1) & 0b11111, 120 );
			}

			pGPC->WriteCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG_LEN, deu, (WD_2 >> 0) & 0b11111, 4 );
			pGPC->WriteCOMPOOL_AIS( SCP_CZ1B_D_DIT_MSG_READY, deu, 1, 4 );
			pGPC->WriteCOMPOOL_AIS( SCP_CZ1E_D_MCDS_EVENT, deu, 1, 4 );

#ifdef _DEBUG
			// dump keyboard msgs to log
			std::string cbuf;
			for (int i = 1; i <= pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG_LEN, deu, 4 ); i++)
			{
				unsigned short k = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + i, 120 );
				if (k <= 9) cbuf += static_cast<char>(k + 48);
				else if (k <= 15) cbuf += static_cast<char>(k + 65);
				else if (k == 16) cbuf += "SS";
				else if (k == 17) cbuf += "O";
				else if (k == 18) cbuf += "S";
				else if (k == 19) cbuf += "FS";
				else if (k == 20) cbuf += "I";
				else if (k == 21) cbuf += "-";
				else if (k == 22) cbuf += "+";
				else if (k == 23) cbuf += ".";
				else if (k == 24) cbuf += "IO";
				else if (k == 25) cbuf += "GC";
				else if (k == 27) cbuf += "R";
				else if (k == 30) cbuf += "E";
				else if (k == 31) cbuf += "P";
				else cbuf += "?";
			}
			oapiWriteLogV( "DK %d -> GPC %d: %s", deu, pGPC->GNC ? 1 : 2, cbuf.c_str() );
#endif// _DEBUG
		}
		else
		{
			if (((WD_1 >> 5) & 1) == 1)// ACK request
			{
				pGPC->WriteCOMPOOL_IS( SCP_ACK_KEY, 1 );
			}
			else if (((WD_1 >> 11) & 1) == 1)// MSG RESET request
			{
				pGPC->WriteCOMPOOL_IS( SCP_MSGRESET_KEY, 1 );
				// reset illegal entry
				unsigned int illegalentryfault = pGPC->ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
				illegalentryfault &= ~(1 << (deu - 1));
				pGPC->WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
			}
		}
		return;
	}
}
