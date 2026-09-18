#include "DIS_PLAY.h"
#include "../SimpleGPCSystem.h"


namespace dps
{
	static void Display_Event_Check( SCP_MACT& CZ1V_D_MACT, SimpleGPCSystem* pGPC )
	{
		if (CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT == 1)
		{
			CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 0;
		}
		else
		{
			CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x8000;// enabled

			if (0/*TODO OPS_Advance_Event*/)
			{
				CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// enabled

				CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x2000;// enabled
			}

			if (CZ1V_D_MACT.CZ1E_D_MOD_ADV_EVT != 0)// HACK check if address is set first
			{
				if (pGPC->ReadCOMPOOL_IS( CZ1V_D_MACT.CZ1E_D_MOD_ADV_EVT ) == 1)
				{
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// enabled
				}
			}
		}
		return;
	}

	static void Mode_Transaction_Check( SCP_MACT& CZ1V_D_MACT )
	{
		if (static_cast<short>(CZ1V_D_MACT.CZ1V_D_NEW_BLK) > 0)
		{
			if (static_cast<short>(CZ1V_D_MACT.CZ1V_D_MOD) >= 0)
			{
				CZ1V_D_MACT.CZ1V_D_NEW_MOD = (CZ1V_D_MACT.CZ1V_D_NEW_BLK % 1000) / 10;

				if (CZ1V_D_MACT.CZ1V_D_NEW_MOD != CZ1V_D_MACT.CZ1V_D_MOD)
				{
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// enabled
				}
			}

			CZ1V_D_MACT.CZ1V_D_NEW_BLK = CZ1V_D_MACT.CZ1V_D_NEW_BLK % 10;
		}
		return;
	}

	static void Program_Control( SCP_MACT& CZ1V_D_MACT, const unsigned short DIS_FLAG_APP_SERVICE_EVT, const unsigned short DIS_MACT_INDEX, SimpleGPCSystem* pGPC )
	{
		/*if (Keyboard_Message_ID is ITEM or ITEM_EXEC)
		{
			CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x0400;// enabled

			pGPC->WriteCOMPOOL_IS( SCP_CDME_APP_SERVICE, 1 );// enabled
		}*/

		if (DIS_FLAG_APP_SERVICE_EVT == 1)// enabled
		{
			pGPC->WriteCOMPOOL_AIS( SCP_CZ1E_D_MACT_EVTS, DIS_MACT_INDEX, 1, 4 );

			pGPC->WriteCOMPOOL_IS( SCP_CDME_APP_SERVICE, 1 );
		}

		//Keyboard_Message_ID = 0;

		if ((CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT == 1) || (0/*TODO OPS_Advance_Event*/) || (0/*TODO Block_Advance_Event*/))
		{
			Display_Event_Check( CZ1V_D_MACT, pGPC );
		}
		else if (CZ1V_D_MACT.CZ1E_D_MOD_ADV_EVT != 0)// HACK check if address is set first
		{
			if (pGPC->ReadCOMPOOL_IS( CZ1V_D_MACT.CZ1E_D_MOD_ADV_EVT ) == 1)
			{
				Display_Event_Check( CZ1V_D_MACT, pGPC );
			}
		}
		return;
	}

	void DIS_PLAY( const unsigned short DIS_DISPLAY_NUM, const unsigned short DIS_MACT_INDEX, SimpleGPCSystem* pGPC )
	{
		unsigned short DIS_FLAG_APP_SERVICE_EVT/*Application_Service_Event_Flag*/ = 0;// disabled

		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

		if (CZ1V_D_MACT.CZ1B_D_FLAGS & 0x0080)// enabled
		{
			CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x0080;// disabled

			CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x0020;

			if (DIS_DISPLAY_NUM != CZ1V_D_MACT.CZ1V_D_DISP)
			{
				CZ1V_D_MACT.CZ1B_D_FLAGS |= 0x4000;

				CZ1V_D_MACT.CZ1V_D_NEW_DISP = DIS_DISPLAY_NUM;

				DIS_FLAG_APP_SERVICE_EVT = 1;// enabled
			}
		}
		else
		{
			//if (static_cast<short>(CZ1V_D_MACT.CZ1V_D_NEW_BLK) >= 0)// HACK changed test to avoid killing block when keyboard input arrives
			if (static_cast<short>(CZ1V_D_MACT.CZ1V_D_NEW_BLK) > 0)
			{
				CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x8000;// enabled

				Mode_Transaction_Check( CZ1V_D_MACT );

				pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				return;
			}
		}

		Program_Control( CZ1V_D_MACT, DIS_FLAG_APP_SERVICE_EVT, DIS_MACT_INDEX, pGPC );

		pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return;
	}
}
