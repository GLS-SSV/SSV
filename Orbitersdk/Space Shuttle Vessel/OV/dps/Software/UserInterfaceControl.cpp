#include "UserInterfaceControl.h"
#include "../SimpleGPCSystem.h"
#include "GeneralDisplays.h"


namespace dps
{
	constexpr unsigned char DEU_GPC_KEY_CODE_0 = 0x00;
	constexpr unsigned char DEU_GPC_KEY_CODE_1 = 0x01;
	constexpr unsigned char DEU_GPC_KEY_CODE_2 = 0x02;
	constexpr unsigned char DEU_GPC_KEY_CODE_3 = 0x03;
	constexpr unsigned char DEU_GPC_KEY_CODE_4 = 0x04;
	constexpr unsigned char DEU_GPC_KEY_CODE_5 = 0x05;
	constexpr unsigned char DEU_GPC_KEY_CODE_6 = 0x06;
	constexpr unsigned char DEU_GPC_KEY_CODE_7 = 0x07;
	constexpr unsigned char DEU_GPC_KEY_CODE_8 = 0x08;
	constexpr unsigned char DEU_GPC_KEY_CODE_9 = 0x09;
	constexpr unsigned char DEU_GPC_KEY_CODE_A = 0x0A;
	constexpr unsigned char DEU_GPC_KEY_CODE_B = 0x0B;
	constexpr unsigned char DEU_GPC_KEY_CODE_C = 0x0C;
	constexpr unsigned char DEU_GPC_KEY_CODE_D = 0x0D;
	constexpr unsigned char DEU_GPC_KEY_CODE_E = 0x0E;
	constexpr unsigned char DEU_GPC_KEY_CODE_F = 0x0F;
	constexpr unsigned char DEU_GPC_KEY_CODE_SYSSUMM = 0x10;
	constexpr unsigned char DEU_GPC_KEY_CODE_OPS = 0x11;
	constexpr unsigned char DEU_GPC_KEY_CODE_SPEC = 0x12;
	constexpr unsigned char DEU_GPC_KEY_CODE_FAULTSUMM = 0x13;
	constexpr unsigned char DEU_GPC_KEY_CODE_ITEM = 0x14;
	constexpr unsigned char DEU_GPC_KEY_CODE_MINUS = 0x15;
	constexpr unsigned char DEU_GPC_KEY_CODE_PLUS = 0x16;
	constexpr unsigned char DEU_GPC_KEY_CODE_DOT = 0x17;
	constexpr unsigned char DEU_GPC_KEY_CODE_IORESET = 0x18;
	constexpr unsigned char DEU_GPC_KEY_CODE_GPCCRT = 0x19;
	constexpr unsigned char DEU_GPC_KEY_CODE_CLEAR = 0x1A;
	constexpr unsigned char DEU_GPC_KEY_CODE_RESUME = 0x1B;
	constexpr unsigned char DEU_GPC_KEY_CODE_ACK = 0x1C;
	constexpr unsigned char DEU_GPC_KEY_CODE_MSGRESET = 0x1D;
	constexpr unsigned char DEU_GPC_KEY_CODE_EXEC = 0x1E;
	constexpr unsigned char DEU_GPC_KEY_CODE_PRO = 0x1F;


	UserInterfaceControl::UserInterfaceControl( SimpleGPCSystem* pGPC ):pGPC(pGPC)
	{
		return;
	}

	UserInterfaceControl::~UserInterfaceControl( void )
	{
		return;
	}

	void UserInterfaceControl::SetIllegalEntry( const unsigned short deu )
	{
		unsigned int illegalentryfault = pGPC->ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
		illegalentryfault |= (1 << (deu - 1));
		pGPC->WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
		return;
	}

	void UserInterfaceControl::DMC_SUPER( void )
	{
		for (int deu = 1; deu <= 4; deu++)
		{
			if ((pGPC->ReadCOMPOOL_AIS( SCP_CZ1B_D_DIT_MSG_READY, deu, 4 ) == 1) && (pGPC->ReadCOMPOOL_AIS( SCP_CZ1E_D_MCDS_EVENT, deu, 4 ) == 1))
			{
				DM1_KEYBOARD( deu );

				// HACK reset flags
				pGPC->WriteCOMPOOL_AIS( SCP_CZ1B_D_DIT_MSG_READY, deu, 0, 4 );
				pGPC->WriteCOMPOOL_AIS( SCP_CZ1E_D_MCDS_EVENT, deu, 0, 4 );
			}

		}
		return;
	}

	void UserInterfaceControl::DM1_KEYBOARD( const unsigned char deu )
	{
		unsigned short key1 = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 1, 120 );
		if ((key1 >= DEU_GPC_KEY_CODE_SYSSUMM) && (key1 <= DEU_GPC_KEY_CODE_EXEC))// is first key valid
		{
			DM1_KEYSTROKE_PROC( deu );
		}
		else
		{
			// TODO error
		}
		return;
	}

	void UserInterfaceControl::DM1_KEYSTROKE_PROC( const unsigned char deu )
	{
		unsigned short key1 = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 1, 120 );

		switch (key1)
		{
			case DEU_GPC_KEY_CODE_OPS:
				DM6_OPS_PROC( deu );
				break;
			case DEU_GPC_KEY_CODE_ITEM:
				DM9_ITEM( deu );
				break;
			case DEU_GPC_KEY_CODE_IORESET:
				DIR_IORESET();
				break;
			case DEU_GPC_KEY_CODE_GPCCRT:
				break;
			case DEU_GPC_KEY_CODE_SPEC:
				DM8_SPEC_PROC( deu );
				break;
			case DEU_GPC_KEY_CODE_SYSSUMM:
				// TODO check if DISP valid in current OPS
				if (pGPC->GNC)
				{
					pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, deu, (pGPC->ReadCOMPOOL_AIS( SCP_CRT_DISP, deu, 4 ) == 18) ? 19 : 18, 4 );
				}
				else
				{
					pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, deu, (pGPC->ReadCOMPOOL_AIS( SCP_CRT_DISP, deu, 4 ) == 78) ? 79 : 78, 4 );
				}
				break;
			case DEU_GPC_KEY_CODE_FAULTSUMM:
				pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, deu, 99, 4 );
				break;
			case DEU_GPC_KEY_CODE_RESUME:
				if (pGPC->ReadCOMPOOL_AIS( SCP_CRT_DISP, deu, 4 ) != dps::MODE_UNDEFINED)
				{
					pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, deu, dps::MODE_UNDEFINED, 4 );
				}
				else if (pGPC->ReadCOMPOOL_AIS( SCP_CRT_SPEC, deu, 4 ) != dps::MODE_UNDEFINED)
				{
					pGPC->WriteCOMPOOL_AIS( SCP_CRT_SPEC, deu, dps::MODE_UNDEFINED, 4 );
				}
				break;
			case DEU_GPC_KEY_CODE_EXEC:
				pGPC->WriteCOMPOOL_IS( SCP_EXEC_KEY, 1 );
				break;
			default:
				break;
		}
		return;
	}

	void UserInterfaceControl::DM6_OPS_PROC( const unsigned char deu )
	{
		if (pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG_LEN, deu, 4 ) != 5)// is number of keystrokes valid?
		{
			// TODO set error condition
			return;
		}

		unsigned short MM_100 = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 2, 120 );
		unsigned short MM_10 = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 3, 120 );
		unsigned short MM_1 = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 4, 120 );

		unsigned int newMM = (MM_100 * 100) + (MM_10 * 10) + MM_1;

		if (!IsValidMajorModeTransition( newMM ))
		{
			// set illegal entry
			SetIllegalEntry( deu );
			return;
		}

		pGPC->WriteCOMPOOL_IS( SCP_NEW_MM, newMM );

		// if OPS transition, clear SPEC and DISP displays, reset commfault indications and counters
		if ((int)(newMM / 100) != (int)(pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100))
		{
			for (int i = 1; i <= 4; i++)
			{
				pGPC->WriteCOMPOOL_AIS( SCP_CRT_SPEC, i, dps::MODE_UNDEFINED, 4 );
				pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, i, dps::MODE_UNDEFINED, 4 );
			}

			DIR_IORESET();
		}
		return;
	}

	void UserInterfaceControl::DM8_SPEC_PROC( const unsigned char deu )
	{
		unsigned short nkey = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG_LEN, deu, 4 );
		if ((nkey < 3) || (nkey > 5))// is number of keystrokes valid?
		{
			// TODO set error condition
			return;
		}

		unsigned short spec = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 2, 120 );
		if (nkey > 3)
		{
			spec = (spec * 10) + pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 3, 120 );
			if (nkey > 4)
			{
				spec = (spec * 10) + pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + 4, 120 );
			}
		}

		if (IsValidSPEC( spec ))
		{
			pGPC->WriteCOMPOOL_AIS( SCP_CRT_SPEC, deu, spec, 4 );
			pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, deu, dps::MODE_UNDEFINED, 4 );
			return;
		}
		else if (IsValidDISP( spec ))
		{
			pGPC->WriteCOMPOOL_AIS( SCP_CRT_DISP, deu, spec, 4 );

			if (spec == 99) pGPC->WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CLEAR, 1 );
			return;
		}
		// set illegal entry
		SetIllegalEntry( deu );
		return;
	}

	void UserInterfaceControl::DM9_ITEM( const unsigned char deu )
	{
		if (pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG_LEN, deu, 4 ) < 3)// is number of keystrokes valid?
		{
			// TODO set error condition
			return;
		}

		// bypass if DISP is up
		int spec = pGPC->ReadCOMPOOL_AIS( SCP_CRT_DISP, deu, 4 );
		if (spec != dps::MODE_UNDEFINED)
		{
			SetIllegalEntry( deu );
			return;
		}
		else
		{
			spec = pGPC->ReadCOMPOOL_AIS( SCP_CRT_SPEC, deu, 4 );
		}

		// TODO handle letters
		unsigned short idx = 2;
		unsigned short item = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + idx++, 120 );
		unsigned short k = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + idx++, 120 );
		if (k <= DEU_GPC_KEY_CODE_9)
		{
			item = (item * 10) + k;

			// read another so k contains delimiter or exec
			k = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + idx++, 120 );
		}

		// single item, no data
		if (k == DEU_GPC_KEY_CODE_EXEC)
		{
			// send item and exit
			if (!pGPC->pSystemDisplays->ItemInput( spec, item, "" ))
			{
				if (!pGPC->pUserDisplays->ItemInput( spec, item, "" )) SetIllegalEntry( deu );
			}
			return;
		}

		// TODO handle letters
		std::string data = "";
		while ((idx < 30) && (k != DEU_GPC_KEY_CODE_EXEC))
		{
			// save delimiter
			if (k == DEU_GPC_KEY_CODE_MINUS) data = '-';
			else /*if (k == DEU_GPC_KEY_CODE_PLUS)*/ data = '+';

			// read data until delimiter or exec
			k = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + idx++, 120 );
			while ((idx < 30) && (k != DEU_GPC_KEY_CODE_MINUS) && (k != DEU_GPC_KEY_CODE_PLUS) && (k != DEU_GPC_KEY_CODE_EXEC))
			{
				// save data
				if (k <= DEU_GPC_KEY_CODE_9) data += static_cast<char>(k + 48);
				else if (k <= DEU_GPC_KEY_CODE_F) data += static_cast<char>(k + 65);
				else if (k == DEU_GPC_KEY_CODE_DOT) data += ".";

				// read next
				k = pGPC->ReadCOMPOOL_AIS( SCP_CZ1V_D_DIT_KYBD_MSG, ((deu - 1) * 30) + idx++, 120 );
			}

			if (data.length() > 1)// more than just the delimiter
			{
				// send item and data
				if (!pGPC->pSystemDisplays->ItemInput( spec, item, data.c_str() ))
			{
				if (!pGPC->pUserDisplays->ItemInput( spec, item, data.c_str() )) SetIllegalEntry( deu );
			}
			}

			// next item
			item++;
		}
		return;
	}

	void UserInterfaceControl::DIR_IORESET( void )
	{
		// reset all commfault words
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_0, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_1, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_2, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_3, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_4, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_5, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_6, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_7, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_8, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_9, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_10, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_0, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_1, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_2, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_3, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_4, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_5, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_6, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_7, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_8, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_9, 0 );
		pGPC->WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_10, 0 );
		return;
	}

	bool UserInterfaceControl::IsValidMajorModeTransition( unsigned short newMajorMode ) const
	{
		if (pGPC->GNC) return IsValidMajorModeTransition_GNC( newMajorMode );
		else return IsValidMajorModeTransition_SM( newMajorMode );
	}

	bool UserInterfaceControl::IsValidMajorModeTransition_GNC( unsigned short newMajorMode ) const
	{
		unsigned short MM = pGPC->ReadCOMPOOL_IS( SCP_MM );
		switch (newMajorMode)
		{
			case 0:
				return (MM == 201 || MM == 901);
			case 101:
				return MM == 901;
			/*case 102:
				return MM == 101;
			case 103:
				return MM == 102;*/
			case 104:
				return MM == 103;
			case 105:
				return MM == 104;
			case 106:
				return MM == 105;
			case 201:
				return (MM == 0 || MM == 106 || MM == 202 || MM == 301 || MM == 801);
			case 202:
				return MM == 201;
			case 301:
				return (MM == 0 || MM == 104 || MM == 105 || MM == 106 || MM == 201 || MM == 302 || MM == 801);
			case 302:
				return MM == 301;
			case 303:
				return MM == 302;
			case 304:
				return MM == 303;
			case 305:
				return MM == 304;
			/*case 601:
				return (MM == 102 || MM == 103);
			case 602:
				return (MM == 104 || MM == 601);
			case 603:
				return MM == 602;*/
			case 801:
				return MM == 201;
			case 901:
				return (MM == 0 || MM == 101 || MM == 305 || MM == 603);
			default:
				return false;
		}
	}

	bool UserInterfaceControl::IsValidMajorModeTransition_SM( unsigned short newMajorMode ) const
	{
		if (pGPC->ReadCOMPOOL_IS( SCP_CZ1E_OPS_MODE_INHIBIT ) != 0) return false;// don't allow changes if any inhibit event on

		unsigned short MM = pGPC->ReadCOMPOOL_IS( SCP_MM );
		switch (newMajorMode)
		{
			case 0:
				return (MM == 201 || MM == 202);
			case 201:
				return (MM == 0 || MM == 202);
			case 202:
				return (MM == 0 || MM == 201);
			default:
				return false;
		}
	}

	bool UserInterfaceControl::IsValidSPEC( unsigned short spec ) const
	{
		if (pGPC->GNC) return IsValidSPEC_GNC( spec );
		else return IsValidSPEC_SM( spec );
	}

	bool UserInterfaceControl::IsValidSPEC_GNC( unsigned short spec ) const
	{
		// PASS system
		switch (spec)
		{
			case 0:// GPC MEMORY
			case 1:// DPS UTILITY
				return true;
			case 2:// TIME
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100)// GNC
				{
					case 1:
					case 3:
					case 6:
						return false;
					default:
						return true;
				}
		}

		// PASS GNC
		switch (spec)
		{
			case 20:// DAP CONFIG
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
				else return false;
			case 21:// IMU ALIGN
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100)
				{
					case 2:
					case 3:
						return true;
					default:
						return false;
				}
			case 22:// S TRK/COAS CNTL
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ))
				{
					case 201:
					case 202:
					case 301:
						return true;
					default:
						return false;
				}
			case 23:// RCS
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100)
				{
					case 1:
					case 2:
					case 3:
					case 6:
					case 8:
						return true;
					default:
						return false;
				}
			case 25:// RM ORBIT
			case 33:// REL NAV
			case 34:// ORBIT TGT
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
				else return false;
			case 40:// SENSOR TEST
			case 41:// RGA/ADTA/RCS
			case 42:// SWITCH/SURF
			case 43:// CONTROLLERS
			case 44:// SWITCHES
			case 45:// NWS CHECK
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 8) return true;
				else return false;
			case 50:// HORIZ SIT
			case 51:// OVERRIDE
			case 53:// CONTROLS
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100)
				{
					case 1:
					case 3:
					case 6:
						return true;
					default:
						return false;
				}
			case 55:// GPS STATUS
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100)
				{
					case 1:
					case 2:
					case 3:
					case 6:
					case 8:
					case 9:
						return true;
					default:
						return false;
				}
			case 62:// PCMMU/PL COMM
			case 100:// GTS DISPLAY
			case 101:// SENSOR SELF-TEST
			case 102:// RCS/RGA/ADTA TEST
			case 104:// GND IMU CNTL/MON
			case 105:// TCS CONTROL
			case 112:// GPC/BTU I/F
			case 113:// ACTUATOR CONTROL
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 9) return true;
				else return false;
		}

		// PASS PL
		switch (spec)
		{
			case 100:// GTS DISPLAY
			case 111:// SL MEMORY DUMP
				return true;
		}

		// BFS GNC
		switch (spec)
		{
			case 50:// HORIZ SIT
			case 51:// OVERRIDE
			case 55:// GPS STATUS
				return true;
		}

		// BFS SM
		switch (spec)
		{
			case 63:// PL BAY DOORS
				return true;
		}
		return false;
	}

	bool UserInterfaceControl::IsValidSPEC_SM( unsigned short spec ) const
	{
		// PASS system
		switch (spec)
		{
			case 0:// GPC MEMORY
			case 1:// DPS UTILITY
			case 2:// TIME
				return true;
		}

		// PASS SM
		switch (spec)
		{
			case 60:// SM TABLE MAINT
			case 62:// PCMMU/PL COMM
			case 64:// SM GROUND CHECKOUT
			case 85:// MASS MEMORY R/W
			case 90:// PCS CONTROL
			case 94:// PDRS CONTROL
			case 95:// PDRS OVERRIDE
				return true;
		}
		return false;
	}

	bool UserInterfaceControl::IsValidDISP( unsigned short disp ) const
	{
		if (pGPC->GNC) return IsValidDISP_GNC( disp );
		else return IsValidDISP_SM( disp );
	}

	bool UserInterfaceControl::IsValidDISP_GNC( unsigned short disp ) const
	{
		// PASS system
		switch (disp)
		{
			case 6:// GPC/BUS STATUS
			case 99:// FAULT
				return true;
		}

		// PASS GNC
		switch (disp)
		{
			case 18:// GNC SYS SUMM 1
				return true;
			case 19:// GNC SYS SUMM 2
				switch (pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100)
				{
					case 2:
					case 8:
						return true;
					default:
						return false;
				}
			case 106:// MANUAL CONTROLS
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 9) return true;
				else return false;
		}

		// BFS system
		switch (disp)
		{
			case 99:// FAULT
				return true;
		}

		// BFS GNC
		switch (disp)
		{
			case 6:// GPC/BUS STATUS
			case 18:// GNC SYS SUMM 1
			case 19:// GNC SYS SUMM 2
				return true;
		}

		// BFS SM
		switch (disp)
		{
			case 78:// SM SYS SUMM 1
			case 79:// SM SYS SUMM 2
			case 168:// CRYO PALLET/CARGO
				return true;
		}
		return false;
	}

	bool UserInterfaceControl::IsValidDISP_SM( unsigned short disp ) const
	{
		// PASS system
		switch (disp)
		{
			case 6:// GPC/BUS STATUS
			case 99:// FAULT
				return true;
		}

		switch (disp)
		{
			case 66:// ENVIRONMENT
			case 67:// ELECTRIC
			case 68:// CRYO SYSTEM
			case 69:// FUEL CELLS
			case 76:// COMMUNICATIONS
			case 77:// EVA-MMU/FSS
			case 78:// SM SYS SUMM 1
			case 79:// SM SYS SUMM 2
			case 86:// APU/HYD
			case 87:// HYD THERMAL
			case 88:// APU/ENVIRON THERM
			case 89:// PRPLT THERMAL
			case 96:// PDRS FAULTS
			case 97:// PL RETENTION
				return true;
			case 167:// DOCKING STATUS
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
				else return false;
			case 168:// CARGO LOOP
			case 169:// PDRS STATUS
				return true;
			case 177:// EXTERNAL AIRLOCK
			case 179:// POWER TRANSFER
				if ((pGPC->ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
				else return false;
		}
		return false;
	}
}
