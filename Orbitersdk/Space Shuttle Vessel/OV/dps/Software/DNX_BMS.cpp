#include "DNX_BMS.h"
#include "../SimpleGPCSystem.h"


namespace dps
{
	static void Moding_Initializer( unsigned short& DIS_MACT_INDEX, SimpleGPCSystem* pGPC )
	{
		DIS_MACT_INDEX = pGPC->ReadCOMPOOL_IS( SCP_CZ1V_D_MACT_INDEX );// HACK replaced internal var UI with CZ1 var
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

		CZ1V_D_MACT.CZ1V_D_OPS = CZ1V_D_MACT.CZ1V_D_NEW_OPS;
		// HACK go to new mode after init, allowing to enter OPS in modes other then 1
		//CZ1V_D_MACT.CZ1V_D_MOD = CZ1V_D_MACT.CZ1V_D_NEW_MOD - 1;
		CZ1V_D_MACT.CZ1V_D_MOD = 0;

		CZ1V_D_MACT.CZ1V_D_DISP = 0;
		CZ1V_D_MACT.CZ1V_D_BLK = 0;
		CZ1V_D_MACT.CZ1V_D_NEW_OPS = 0;
		//CZ1V_D_MACT.CZ1V_D_NEW_MOD = 0;// HACK go to new mode after init, allowing to enter OPS in modes other then 1
		CZ1V_D_MACT.CZ1V_D_NEW_BLK = 0;
		CZ1V_D_MACT.CZ1B_D_FLAGS = 0;
		CZ1V_D_MACT.CZ1B_D_FLAG2 = 0;

		CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x0080;// HACK set first display request

		//Name_Of_Keyboard_Message_Event = Keyboard_Message_Ready_Event_Array[DIS_MACT_INDEX];

		pGPC->WriteCOMPOOL_AIS( SCP_CZ1E_D_MACT_EVTS, DIS_MACT_INDEX, 0, 4 );

		//MACT_Index_Event = 1;

		pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return;
	}

	static void Mode_Level_Case( SCP_MACT& CZ1V_D_MACT, SimpleGPCSystem* pGPC )
	{
		CZ1V_D_MACT.CZ1B_D_FLAG2 &= ~0x4000;// disabled

		CZ1V_D_MACT.CZ1V_D_BLK = 0;

		CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x0020;// disabled

		if (CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x2000)// enabled
		{
			SCP_OPS CDAV_OPS;
			pGPC->ReadCOMPOOL_ASTRUCT( SCP_CDAV_OPS, CZ1V_D_MACT.CZ1V_D_SEQUENCE_INFO, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			CZ1V_D_MACT.CZ1V_D_MOD = 1 + CDAV_OPS.CDAV_OP_NMODES;
		}
		else
		{
			if (CZ1V_D_MACT.CZ1V_D_NEW_MOD == 0)
			{
				CZ1V_D_MACT.CZ1V_D_MOD = CZ1V_D_MACT.CZ1V_D_MOD + 1;
			}
			else
			{
				CZ1V_D_MACT.CZ1V_D_MOD = CZ1V_D_MACT.CZ1V_D_NEW_MOD;

				CZ1V_D_MACT.CZ1V_D_NEW_MOD = 0;
			}
		}
		return;
	}

	static void Block_Level_Case( SCP_MACT& CZ1V_D_MACT )
	{
		CZ1V_D_MACT.CZ1B_D_FLAG2 &= ~0x8000;// disabled

		CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x0080;// enabled

		CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 0;

		if ((CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x4000) || (CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x2000))
		{
			if (CZ1V_D_MACT.CZ1V_D_MOD < 0)
			{
				// SPEC termination
				CZ1V_D_MACT.CZ1V_D_BLK = CZ1V_D_MACT.CZ1V_D_SEQUENCE_INFO + 1;
			}
			else
			{
				// mode termination
				//Block_Index = Mode_Data_Array_Pointer[CZ1V_D_MACT.CZ1V_D_SEQUENCE_INFO + CZ1V_D_MACT.CZ1V_D_MOD - 1] & 0x000F;

				//CZ1V_D_MACT.CZ1V_D_BLK = OPS_Moding_Data[Block_Index] + 1;
			}
		}
		else
		{
			if (static_cast<short>(CZ1V_D_MACT.CZ1V_D_BLK) <= 0)
			{
				CZ1V_D_MACT.CZ1V_D_BLK = CZ1V_D_MACT.CZ1V_D_BLK + 1;
			}
			else
			{
				CZ1V_D_MACT.CZ1V_D_BLK = CZ1V_D_MACT.CZ1V_D_NEW_BLK + 1;
			}

			CZ1V_D_MACT.CZ1V_D_NEW_BLK = -1;
		}
		return;
	}

	void DNX_BMS( const unsigned short DNX_LEVEL, unsigned short& DIS_MACT_INDEX, SimpleGPCSystem* pGPC )
	{
		if (DIS_MACT_INDEX == 0)
		{
			Moding_Initializer( DIS_MACT_INDEX, pGPC );
		}

		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		switch (DNX_LEVEL)
		{
			case 1:
				CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x0100;// enabled

				CZ1V_D_MACT.CZ1B_D_FLAG2 &= ~0x2000;// disabled
				pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

				pGPC->WriteCOMPOOL_AIS( SCP_CZ1E_D_MACT_EVTS, DIS_MACT_INDEX, 1, 4 );
				DIS_MACT_INDEX = 0;// disabled

				pGPC->WriteCOMPOOL_IS( SCP_CDME_APP_SERVICE, 1 );
				break;
			case 2:
				Mode_Level_Case( CZ1V_D_MACT, pGPC );
				pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				break;
			case 3:
				Block_Level_Case( CZ1V_D_MACT );
				pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				break;
		}
		return;
	}
}
