#include "IDP_software.h"
#include "IDP.h"
#include "../vc/MDU.h"


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

	constexpr unsigned short DEU_KYBD_DEU_GPC_KEY_CODE_CONV[32] = {
		0xEFFC,// KEY_SWITCH_0
		0xFE7A,// KEY_SWITCH_1
		0xFEBA,// KEY_SWITCH_2
		0xFEFA,// KEY_SWITCH_3
		0xFBFB,// KEY_SWITCH_4
		0xFDFB,// KEY_SWITCH_5
		0xFFFB,// KEY_SWITCH_6
		0xF3FB,// KEY_SWITCH_7
		0xF5FB,// KEY_SWITCH_8
		0xF7FB,// KEY_SWITCH_9
		0xFFC9,// KEY_SWITCH_A
		0xFFD1,// KEY_SWITCH_B
		0xFFD9,// KEY_SWITCH_C
		0xFF7A,// KEY_SWITCH_D
		0xFFBA,// KEY_SWITCH_E
		0xFFFA,// KEY_SWITCH_F
		0xFFE9,// KEY_SWITCH_SYSSUMM
		0xF1FB,// KEY_SWITCH_OPS
		0xCFFC,// KEY_SWITCH_SPEC
		0xFFE1,// KEY_SWITCH_FAULTSUMM
		0xFE3A,// KEY_SWITCH_ITEM
		0xDFFC,// KEY_SWITCH_MINUS
		0xFFFC,// KEY_SWITCH_PLUS
		0xAFFC,// KEY_SWITCH_DOT
		0xFF3A,// KEY_SWITCH_IORESET
		0xFFC1,// KEY_SWITCH_GPCCRT
		0x9FFC,// KEY_SWITCH_CLEAR
		0x8FFC,// KEY_SWITCH_RESUME
		0xFFF9,// KEY_SWITCH_ACK
		0xFFF1,// KEY_SWITCH_MSGRESET
		0xF9FB,// KEY_SWITCH_EXEC
		0xBFFC,// KEY_SWITCH_PRO
	};

	const char* SPL_KEY_TEXT[32] = {
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		" SYS SUMM ",
		" OPS ",
		" SPEC ",
		" FAULT SUMM ",
		" ITEM ",
		"-",
		"+",
		".",
		" I/O RESET ",
		" GPC/CRT ",
		"",
		" RESUME ",
		"",
		"",
		" EXEC ",
		" PRO "
	};


	constexpr unsigned char ATT_GREEN = 0x00;
	constexpr unsigned char ATT_YELLOW = 0x01;
	constexpr unsigned char ATT_ORANGE = 0x02;
	constexpr unsigned char ATT_FLASH = 0x10;
	constexpr unsigned char ATT_DASHED = 0x20;
	constexpr unsigned char ATT_LARGE = 0x80;

	constexpr unsigned short DPS_CHAR_SIZE_X = 19;
	constexpr unsigned short DPS_CHAR_SIZE_Y = 27;
	constexpr short DPS_DISPLAY_X_OFFSET = 28;
	constexpr short DPS_DISPLAY_Y_OFFSET = 15;// HACK should be 14, but math doesn't add up


	constexpr double POLLFAIL_DT = 3.0;// [s]
	constexpr double FILLFAIL_DT = 3.0;// [s]


	IDP_software::IDP_software( IDP* pIDP ): pIDP(pIDP)
	{
		return;
	}

	IDP_software::~IDP_software( void )
	{
		return;
	}

	void IDP_software::RUN( const double dt )
	{
		DCP( dt );

		MEDS();
		return;
	}

	void IDP_software::DCP( const double dt )
	{
		// check for poll and fill fails
		// TODO check time fill gap < 5ms
		// TODO display not frozen
		if (pIDP->polllastrecv >= POLLFAIL_DT)
		{
			if (pIDP->pollfail == false)
			{
				// clear SPL
				pIDP->SPLkeyslen = 0;
			}
			pIDP->pollfail = true;
		}
		else
		{
			pIDP->pollfail = false;
		}
		pIDP->polllastrecv += dt;

		if (pIDP->filllastrecv >= FILLFAIL_DT)
		{
			pIDP->fillfail = true;
		}
		else
		{
			pIDP->fillfail = false;
		}
		pIDP->filllastrecv += dt;

		ProcessKeyboard();

		PackKeys();

		// update MF switch position
		unsigned char MF = 0;// default to PL
		if (pIDP->MajorFuncGNC && !pIDP->MajorFuncSM && !pIDP->MajorFuncPL) MF = 1;
		else if (!pIDP->MajorFuncGNC && pIDP->MajorFuncSM && !pIDP->MajorFuncPL) MF = 2;
		pIDP->PollResponseBuffer[0] &= ~(0b11 << 6);
		pIDP->PollResponseBuffer[0] |= MF << 6;
		return;
	}

	void IDP_software::MEDS( void )
	{
		// data input
		// ADC 1
		pIDP->MEDStransaction( (pIDP->usIDPID <= 2) ? 5 : 6, 1, 0b00010, pIDP->ADCdata[0], 32 );
		// ADC 2
		pIDP->MEDStransaction( (pIDP->usIDPID <= 2) ? 8 : 9, 1, 0b00010, pIDP->ADCdata[1], 32 );

		// TODO fetch MDU status
		// CDR 1
		pIDP->MEDStransaction( 26, 1, 0b00010, pIDP->MDUstatus[0], 32 );
		// CDR 2
		pIDP->MEDStransaction( 11, 1, 0b00010, pIDP->MDUstatus[1], 32 );
		// PLT 1
		pIDP->MEDStransaction( 28, 1, 0b00010, pIDP->MDUstatus[2], 32 );
		// PLT 2
		pIDP->MEDStransaction( 13, 1, 0b00010, pIDP->MDUstatus[3], 32 );
		// CRT 1
		pIDP->MEDStransaction( 22, 1, 0b00010, pIDP->MDUstatus[4], 32 );
		// CRT 2
		pIDP->MEDStransaction( 7, 1, 0b00010, pIDP->MDUstatus[5], 32 );
		// CRT 3
		pIDP->MEDStransaction( 21, 1, 0b00010, pIDP->MDUstatus[6], 32 );
		// CRT 4
		pIDP->MEDStransaction( 16, 1, 0b00010, pIDP->MDUstatus[7], 32 );
		// MFD 1
		pIDP->MEDStransaction( 14, 1, 0b00010, pIDP->MDUstatus[8], 32 );
		// MFD 2
		pIDP->MEDStransaction( 19, 1, 0b00010, pIDP->MDUstatus[9], 32 );
		// AFD 1
		pIDP->MEDStransaction( 25, 1, 0b00010, pIDP->MDUstatus[10], 32 );

		// TODO send MDU display data
		return;
	}

	void IDP_software::ProcessKeyboard( void )
	{
		unsigned char key;
		for (const auto& cKey : pIDP->KeyboardInput)
		{
			if (ConvertKeyCode( cKey, key ))
			{
				// is multi-key initiator?
				if ((key == DEU_GPC_KEY_CODE_OPS) ||
					(key == DEU_GPC_KEY_CODE_SPEC) ||
					(key == DEU_GPC_KEY_CODE_ITEM) ||
					(key == DEU_GPC_KEY_CODE_IORESET) ||
					(key == DEU_GPC_KEY_CODE_GPCCRT))
				{
					// clear SPL
					pIDP->SPLkeyslen = 0;
					// write key in SPL
					pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;
					// clear error
					pIDP->SPLerror = false;
					// reset item input state
					pIDP->ITEMstate[0] = 0;
					continue;
				}

				// is single key? (no GPC output)
				if (key == DEU_GPC_KEY_CODE_CLEAR)
				{
					// is SPL empty?
					if (pIDP->SPLkeyslen == 0) continue;
					// is SPL complete and no error?
					if (((pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_EXEC) || (pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_PRO)) && (pIDP->SPLerror == false))
					{
						// clear SPL
						pIDP->SPLkeyslen = 0;
					}
					else
					{
						// delete last key from SPL
						pIDP->SPLkeyslen--;
					}
					// clear error
					pIDP->SPLerror = false;
					continue;
				}

				// is single key? (no SPL output)
				if ((key == DEU_GPC_KEY_CODE_ACK) ||
					(key == DEU_GPC_KEY_CODE_MSGRESET))
				{
					// save key for GPC transmission
					pIDP->PollResponseBuffer[0] |= 1 << ((key == DEU_GPC_KEY_CODE_ACK) ? 5 : 11);
					continue;
				}

				// is single key?
				if ((key == DEU_GPC_KEY_CODE_SYSSUMM) ||
					(key == DEU_GPC_KEY_CODE_FAULTSUMM) ||
					(key == DEU_GPC_KEY_CODE_RESUME))
				{
					// clear SPL
					pIDP->SPLkeyslen = 0;
					// write key in SPL
					pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;
					// clear error
					pIDP->SPLerror = false;
					// save key for GPC transmission
					pIDP->GPCkeybuff[pIDP->GPCkeybufflen++] = key;
					continue;
				}

				// is single key? (exec)
				if ((key == DEU_GPC_KEY_CODE_EXEC) && ((pIDP->SPLkeyslen == 0) ||
					((pIDP->SPLkeyslen != 0) && ((pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_PRO) ||
					(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_EXEC) ||
					(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_FAULTSUMM) ||
					(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_SYSSUMM) ||
					(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_RESUME)))))
				{
					// clear SPL
					pIDP->SPLkeyslen = 0;
					// write key in SPL
					pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;
					// clear error
					pIDP->SPLerror = false;
					// save key for GPC transmission
					pIDP->GPCkeybuff[pIDP->GPCkeybufflen++] = key;
					continue;
				}

				// only continue processing key if no ERR
				if (pIDP->SPLerror) continue;

				// if input complete, clear it
				if (pIDP->SPLkeyslen != 0)
				{
					if ((pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_PRO) ||
						(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_EXEC) ||
						(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_FAULTSUMM) ||
						(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_SYSSUMM) ||
						(pIDP->SPLkeys[pIDP->SPLkeyslen - 1] == DEU_GPC_KEY_CODE_RESUME))
					{
						// clear SPL
						pIDP->SPLkeyslen = 0;
					}
				}

				// continue existing key sequence?
				if (pIDP->SPLkeyslen != 0)
				{
					// write key in SPL
					pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;

					// HACK? limit input to 30 keys for GPC transmission
					if (pIDP->SPLkeyslen > 30)
					{
						pIDP->SPLerror = true;
						continue;
					}

					// check SPL start to pick processing
					if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_OPS)
					{
						if (((pIDP->SPLkeyslen == 5) && (key != DEU_GPC_KEY_CODE_PRO)) ||
							((pIDP->SPLkeyslen <= 4) && (key > DEU_GPC_KEY_CODE_9)))
						{
							pIDP->SPLerror = true;
						}
						else if (key == DEU_GPC_KEY_CODE_PRO)
						{
							// save key for GPC transmission
							SaveKeys();
						}
					}
					else if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_SPEC)
					{
						if (((pIDP->SPLkeyslen == 5) && (key != DEU_GPC_KEY_CODE_PRO)) ||
							((pIDP->SPLkeyslen <= 4) && (key > DEU_GPC_KEY_CODE_9) && (key != DEU_GPC_KEY_CODE_PRO)) ||
							((pIDP->SPLkeyslen == 2) && (key > DEU_GPC_KEY_CODE_9)))
						{
							pIDP->SPLerror = true;
						}
						else if (key == DEU_GPC_KEY_CODE_PRO)
						{
							// save key for GPC transmission
							SaveKeys();
						}
					}
					else if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_ITEM)
					{
						switch (pIDP->ITEMstate[pIDP->SPLkeyslen - 2])
						{
							case 0:// ITEM
								// 1
								// 2
								if (key <= DEU_GPC_KEY_CODE_9)
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 2;
								}
								else if (key <= DEU_GPC_KEY_CODE_F)
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 1;
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 1:// letter
								// 3
								// EXEC
								if ((key == DEU_GPC_KEY_CODE_MINUS) || (key == DEU_GPC_KEY_CODE_PLUS))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 3;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// save key for GPC transmission
									SaveKeys();
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 2:// number
								// 5
								// 6
								// EXEC
								if (key <= DEU_GPC_KEY_CODE_9)
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 5;
								}
								else if ((key == DEU_GPC_KEY_CODE_MINUS) || (key == DEU_GPC_KEY_CODE_PLUS))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 6;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// save key for GPC transmission
									SaveKeys();
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 3:// letter delimiter
								// 4
								if ((key <= DEU_GPC_KEY_CODE_F) || (key == DEU_GPC_KEY_CODE_DOT))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 4;
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 4:// letter data
								// 4
								// EXEC
								if ((key <= DEU_GPC_KEY_CODE_F) || (key == DEU_GPC_KEY_CODE_DOT))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 4;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// save key for GPC transmission
									SaveKeys();
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 5:// 2º number
								// 6
								// EXEC
								if ((key == DEU_GPC_KEY_CODE_MINUS) || (key == DEU_GPC_KEY_CODE_PLUS))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 6;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// save key for GPC transmission
									SaveKeys();
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 6:// number delimiter
								// 6
								// 7
								if ((key <= DEU_GPC_KEY_CODE_F) || (key == DEU_GPC_KEY_CODE_DOT))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 7;
								}
								else if ((key == DEU_GPC_KEY_CODE_MINUS) || (key == DEU_GPC_KEY_CODE_PLUS))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 6;
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
							case 7:// number data
								// 7
								// 6
								// EXEC
								if ((key <= DEU_GPC_KEY_CODE_F) || (key == DEU_GPC_KEY_CODE_DOT))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 7;
								}
								else if ((key == DEU_GPC_KEY_CODE_MINUS) || (key == DEU_GPC_KEY_CODE_PLUS))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 6;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// save key for GPC transmission
									SaveKeys();
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
						}
					}
					else if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_IORESET)
					{
						if (key != DEU_GPC_KEY_CODE_EXEC)
						{
							pIDP->SPLerror = true;
						}
						else
						{
							// save key for GPC transmission
							SaveKeys();
						}
					}
					else if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_GPCCRT)
					{
						if (((pIDP->SPLkeyslen == 4) && (key != DEU_GPC_KEY_CODE_EXEC)) ||
							((pIDP->SPLkeyslen <= 3) && (key > DEU_GPC_KEY_CODE_9)))
						{
							pIDP->SPLerror = true;
						}
						else if (key == DEU_GPC_KEY_CODE_EXEC)
						{
							// save key for GPC transmission
							SaveKeys();
						}
					}
					continue;
				}

				// invalid key
				pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;
				// ERR
				pIDP->SPLerror = true;
			}
		}
		pIDP->KeyboardInput.clear();

		// expand SPL to string
		FormatSPL();
		return;
	}

	bool IDP_software::ConvertKeyCode( const unsigned short deu_kybd_key_code, unsigned char& deu_gpc_key_code )
	{
		for (int i = 0; i < 32; i++)
		{
			if (DEU_KYBD_DEU_GPC_KEY_CODE_CONV[i] == deu_kybd_key_code)
			{
				deu_gpc_key_code = i;
				return true;
			}
		}
		return false;
	}

	void IDP_software::FormatSPL( void )
	{
		bool firstdelimiter = true;
		bool isITEM = false;
		int item = 0;
		memset( pIDP->SPLatt, 0, 128 * sizeof(char) );

		// initial space
		strcpy_s( pIDP->SPL, " " );

		for (int i = 0; i < pIDP->SPLkeyslen; i++)
		{
			switch (pIDP->SPLkeys[i])
			{
				case DEU_GPC_KEY_CODE_0:
					strcat_s( pIDP->SPL, "0" );
					break;
				case DEU_GPC_KEY_CODE_1:
					strcat_s( pIDP->SPL, "1" );
					break;
				case DEU_GPC_KEY_CODE_2:
					strcat_s( pIDP->SPL, "2" );
					break;
				case DEU_GPC_KEY_CODE_3:
					strcat_s( pIDP->SPL, "3" );
					break;
				case DEU_GPC_KEY_CODE_4:
					strcat_s( pIDP->SPL, "4" );
					break;
				case DEU_GPC_KEY_CODE_5:
					strcat_s( pIDP->SPL, "5" );
					break;
				case DEU_GPC_KEY_CODE_6:
					strcat_s( pIDP->SPL, "6" );
					break;
				case DEU_GPC_KEY_CODE_7:
					strcat_s( pIDP->SPL, "7" );
					break;
				case DEU_GPC_KEY_CODE_8:
					strcat_s( pIDP->SPL, "8" );
					break;
				case DEU_GPC_KEY_CODE_9:
					strcat_s( pIDP->SPL, "9" );
					break;
				case DEU_GPC_KEY_CODE_A:
					strcat_s( pIDP->SPL, "A" );
					break;
				case DEU_GPC_KEY_CODE_B:
					strcat_s( pIDP->SPL, "B" );
					break;
				case DEU_GPC_KEY_CODE_C:
					strcat_s( pIDP->SPL, "C" );
					break;
				case DEU_GPC_KEY_CODE_D:
					strcat_s( pIDP->SPL, "D" );
					break;
				case DEU_GPC_KEY_CODE_E:
					strcat_s( pIDP->SPL, "E" );
					break;
				case DEU_GPC_KEY_CODE_F:
					strcat_s( pIDP->SPL, "F" );
					break;
				case DEU_GPC_KEY_CODE_SYSSUMM:
					strcat_s( pIDP->SPL, "SYS SUMM" );
					break;
				case DEU_GPC_KEY_CODE_OPS:
					AddSPLatt( strlen( pIDP->SPL ), 3, ATT_FLASH );
					strcat_s( pIDP->SPL, "OPS " );
					break;
				case DEU_GPC_KEY_CODE_SPEC:
					AddSPLatt( strlen( pIDP->SPL ), 4, ATT_FLASH );
					strcat_s( pIDP->SPL, "SPEC " );
					break;
				case DEU_GPC_KEY_CODE_FAULTSUMM:
					strcat_s( pIDP->SPL, "FAULT SUMM" );
					break;
				case DEU_GPC_KEY_CODE_ITEM:
					AddSPLatt( strlen( pIDP->SPL ), 4, ATT_FLASH );
					strcat_s( pIDP->SPL, "ITEM " );
					isITEM = true;
					break;
				case DEU_GPC_KEY_CODE_MINUS:
				case DEU_GPC_KEY_CODE_PLUS:
					{
						unsigned char delimiter = pIDP->SPLkeys[i];
						if (isITEM)
						{
							// handle parenthesis
							size_t len = strlen( pIDP->SPL );

							// TODO handle letters
							if (firstdelimiter)
							{
								firstdelimiter = false;

								// get item, skip if not valid
								if (pIDP->SPLkeys[i - 1] <= DEU_GPC_KEY_CODE_9)
								{
									item = pIDP->SPLkeys[i - 1];

									if (pIDP->SPLkeys[i - 2] <= DEU_GPC_KEY_CODE_9)
									{
										item += pIDP->SPLkeys[i - 2] * 10;
									}

									int offset = 1;// SPL end offset to (re)write item number
									if (item > 9) offset = 2;
									sprintf_s( pIDP->SPL + (len - offset), 128 - (len - offset), "(%02d)", item );
								}
							}
							else
							{
								// increment item
								if (item < 99) item++;

								int offset = 0;// SPL end offset to (re)write item number
								if ((pIDP->SPLkeys[i - 1] == DEU_GPC_KEY_CODE_MINUS) || (pIDP->SPLkeys[i - 1] == DEU_GPC_KEY_CODE_PLUS)) offset = 6;
								sprintf_s( pIDP->SPL + (len - offset), 128 - (len - offset), " (%02d)", item );
							}
						}
						if (delimiter == DEU_GPC_KEY_CODE_MINUS) strcat_s( pIDP->SPL, "-" );
						else strcat_s( pIDP->SPL, "+" );
					}
					break;
				case DEU_GPC_KEY_CODE_DOT:
					strcat_s( pIDP->SPL, "." );
					break;
				case DEU_GPC_KEY_CODE_IORESET:
					AddSPLatt( strlen( pIDP->SPL ), 9, ATT_FLASH );
					strcat_s( pIDP->SPL, "I/O RESET" );
					break;
				case DEU_GPC_KEY_CODE_GPCCRT:
					AddSPLatt( strlen( pIDP->SPL ), 7, ATT_FLASH );
					strcat_s( pIDP->SPL, "GPC/CRT " );
					break;
				case DEU_GPC_KEY_CODE_RESUME:
					strcat_s( pIDP->SPL, "RESUME" );
					break;
				case DEU_GPC_KEY_CODE_EXEC:
					if (pIDP->SPLkeyslen != 1)
					{
						AddSPLatt( 1, 9, 0 );// clear initiator flash
						strcat_s( pIDP->SPL, " " );
					}
					strcat_s( pIDP->SPL, "EXEC" );
					break;
				case DEU_GPC_KEY_CODE_PRO:
					AddSPLatt( 1, 9, 0 );// clear initiator flash
					strcat_s( pIDP->SPL, " PRO" );
					break;
				default:
					break;
			}
		}

		// handle existing input error and check for SPL overflow
		unsigned short SPL_max_size = pIDP->pollfail ? 29 : 39;
		if (((strlen( pIDP->SPL ) > SPL_max_size) && (pIDP->SPLkeys[pIDP->SPLkeyslen - 1] != DEU_GPC_KEY_CODE_EXEC)) || (pIDP->SPLerror == true))
		{
			pIDP->SPLerror = true;
			AddSPLatt( 1, 9, 0 );// clear initiator flash
			AddSPLatt( strlen( pIDP->SPL ), 5, ATT_FLASH );
			strcat_s( pIDP->SPL, " ERR " );
		}
		return;
	}

	void IDP_software::AddSPLatt( unsigned int start, unsigned int len, char att )
	{
		for (unsigned int i = 0; i < len; i++)
		{
			pIDP->SPLatt[start + i] = att;
		}
		return;
	}

	void IDP_software::SaveKeys( void )
	{
		// TODO don't save if POLL FAIL
		pIDP->GPCkeybufflen = (pIDP->SPLkeyslen > 30) ? 30 : pIDP->SPLkeyslen;
		memcpy( pIDP->GPCkeybuff, pIDP->SPLkeys, pIDP->GPCkeybufflen * sizeof(unsigned char) );
		return;
	}

	void IDP_software::PackKeys( void )
	{
		if (pIDP->GPCkeybufflen == 0) return;

		for (int key = 0, word = 1; key < pIDP->GPCkeybufflen; key++)
		{
			if ((key % 3) == 0)
			{
				word++;
				pIDP->PollResponseBuffer[word] = 0;
			}
			pIDP->PollResponseBuffer[word] |= (pIDP->GPCkeybuff[key] & 0b11111) << (((2 - (key % 3)) * 5) + 1);
		}
#ifdef _DEBUG
		// dump keyboard msgs to log
		std::string cbuf;
		for (int i = 0; i < pIDP->GPCkeybufflen; i++)
		{
			unsigned short k = pIDP->GPCkeybuff[i];
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
		oapiWriteLogV( "(SSV_OV) [INFO] DEU %d: %s", pIDP->usIDPID, cbuf.c_str() );
#endif// _DEBUG

		pIDP->PollResponseBuffer[0] |= 1 << 3;// keyboard msg present
		pIDP->PollResponseBuffer[1] |= pIDP->GPCkeybufflen << 0;// keystroke count

		pIDP->GPCkeybufflen = 0;
		return;
	}

	void IDP_software::OnPaint( vc::MDU* pMDU )
	{
		// TODO print header (always?)
		PrintClocks( pMDU );

		if (pIDP->pollfail)
		{
			PrintPollFail( pMDU );
		}
		if (pIDP->fillfail)
		{
			PrintBigX( pMDU );
		}
		//else
		{
			// print buffer
			PrintDisplay( pMDU );

			// print fault message line
			PrintMessageLine( pMDU );
		}

		// print Scratch Pad line
		PrintScratchPadLine( pMDU );
		return;
	}

	bool IDP_software::GetFlash( void ) const
	{
		double frac = 0.0;
		double intg = 0.0;
		frac = std::modf( oapiGetSimTime(), &intg );
		return frac > 0.6;// TODO find actual duty cycle
	}

	void IDP_software::CharMap( char* str ) const
	{
		constexpr unsigned char CHAR_MAP_CONV[128] = {
			0x00,
			0xA1,// 0x01
			0xA2,// 0x02
			0xA3,// 0x03
			0xA4,// 0x04
			0xA5,// 0x05
			0xA6,// 0x06
			0xA7,// 0x07
			0xA8,// 0x08
			0xA9,// 0x09
			0xAA,// 0x0A
			0xAB,// 0x0B
			0xAC,// 0x0C
			0xAD,// 0x0D
			0xAE,// 0x0E
			0xAF,// 0x0F

			0xB0,// 0x10
			0xB1,// 0x11
			0xB2,// 0x12
			0xB3,// 0x13
			0xB4,// 0x14
			0xB5,// 0x15
			0xB6,// 0x16
			0xB7,// 0x17
			0xB8,// 0x18
			0xB9,// 0x19
			0xBA,// 0x1A
			0xBB,// 0x1B
			0xBC,// 0x1C
			0xBD,// 0x1D
			0xBE,// 0x1E
			0xBF,// 0x1F

			0x20,
			0x21,
			0x22,
			0x23,
			0x24,
			0x25,
			0x26,
			0x27,
			0x28,
			0x29,
			0x2A,
			0x2B,
			0x2C,
			0x2D,
			0x2E,
			0x2F,

			0x30,
			0x31,
			0x32,
			0x33,
			0x34,
			0x35,
			0x36,
			0x37,
			0x38,
			0x39,
			0x3A,
			0x3B,
			0x3C,
			0x3D,
			0x3E,
			0x3F,

			0x40,
			0x41,
			0x42,
			0x43,
			0x44,
			0x45,
			0x46,
			0x47,
			0x48,
			0x49,
			0x4A,
			0x4B,
			0x4C,
			0x4D,
			0x4E,
			0x4F,

			0x50,
			0x51,
			0x52,
			0x53,
			0x54,
			0x55,
			0x56,
			0x57,
			0x58,
			0x59,
			0x5A,
			0x5B,
			0x5C,
			0x5D,
			0x5E,
			0x5F,

			0x60,
			0x61,
			0x62,
			0x63,
			0x64,
			0x65,
			0x66,
			0x67,
			0x68,
			0x69,
			0x6A,
			0x6B,
			0x6C,
			0x6D,
			0x6E,
			0x6F,

			0x70,
			0x71,
			0x72,
			0x73,
			0x74,
			0x75,
			0x76,
			0x77,
			0x78,
			0x79,
			0x7A,
			0x7B,
			0x7C,
			0x7D,
			0x7E,
			0xA0// 0x7F
			};

		for (size_t i = 0; i < strlen( str ); i++) str[i] = CHAR_MAP_CONV[0x7F & str[i]];
		return;
	}

	void IDP_software::ProcessFCW( const unsigned short* fcw_buff, unsigned short len, vc::MDU* pMDU ) const
	{
		// 16 feature control

		// [12 rotation control] (6 cos + 6 sin)
		// [11 position control] (6 x + 5 y)
		// 14 character control (7 + 7)
		// 10 circle gen control (radius)
		// 12 vector gen control
		// [11 x y translate control] (6 x + 5 y)
		// (9 analog control)
		// (11 repeat control)
		// 7 intensity control

/*				dec		hex
default green (color 40)	101 000		1000000
default yellow (color 54)	110 110		1010100
color 56			111 000		1010110
color 29	white		011 101		0101001
color 33			100 001		0110011
color 43			101 011		1000011
color 19	green?		010 011		0011001
color 21	yellow?		010 101		0100001
color 47	cyan		101 111		1000111
*/

/*
shaded circle (alternate character set symbol 14)
filled diamond (alternate character set symbol 15)
large cross (alternate character set symbol 16)
small cross (alternate character set symbol 17)
Shuttle planform symbol (alternate character set symbol 18)
Shuttle Symbol (alternate character set symbol 19)
*/
		const unsigned char FCW_EOR = 0b00;// end-of-record
		const unsigned char FCW_WORD1 = 0b01;
		const unsigned char FCW_WORD2 = 0b10;
		const unsigned char FCW_BASIC = 0b11;

		const unsigned char MODE_NOP = 0b000;
		const unsigned char MODE_SYMBOL = 0b001;
		const unsigned char MODE_ROTATE = 0b010;
		const unsigned char MODE_CIRCLE = 0b011;
		const unsigned char MODE_HIRES = 0b100;
		const unsigned char MODE_VECTOR = 0b101;

		unsigned char mode = MODE_NOP;
		bool large = false;
		bool flash = false;
		bool dash = false;
		bool intensity = false;
		bool orange = false;
		short posx = 1;
		short posy = 1;
		short posx2 = 1;
		short posy2 = 1;
		bool xcoord = true;
		unsigned char att = ATT_GREEN;
		bool flashhide = GetFlash();
		double rot = 0.0;

		for (int i = 0; i < len; i++)// limit to maximum buffer
		{
			unsigned short fcw = fcw_buff[i];
			unsigned short type = fcw & 0x0003;
			switch (type)
			{
				case FCW_EOR:
					return;
				case FCW_WORD1:
					if (mode == MODE_SYMBOL)
					{
						posx = (fcw & 0x00FC) >> 2;
						posy = (fcw & 0x1F00) >> 8;
					}
					else if (mode == MODE_ROTATE)
					{
						short isn = (fcw & 0x3F00) >> 8;
						short ics = (fcw & 0x00FC) >> 2;

						double sn = (isn & 0b11111) / 31.0;
						double cs = (ics & 0b11111) / 31.0;

						if (isn & 0b100000) sn = -sn;
						if (ics & 0b100000) cs = -cs;

						rot = atan2( sn, cs ) * DEG;
					}
					else if (mode == MODE_CIRCLE)
					{
						short pos = (fcw & 0x0FFC) >> 2;
						bool neg = (fcw & 0x1000) != 0;
						if (neg) pos = -pos;
						if (xcoord) posx = pos;
						else posy = pos;
						xcoord = !xcoord;
					}
					else if (mode == MODE_HIRES)
					{
						short pos = (fcw & 0x0FFC) >> 2;
						bool neg = (fcw & 0x1000) != 0;
						if (neg) pos = -pos;
						if (xcoord) posx = pos;
						else posy = pos;
						xcoord = !xcoord;
					}
					else if (mode == MODE_VECTOR)
					{
						short pos = (fcw & 0x0FFC) >> 2;
						bool neg = (fcw & 0x1000) != 0;
						if (neg) pos = -pos;
						if (xcoord) posx = pos;
						else posy = pos;
						xcoord = !xcoord;
					}
					else
					{
						oapiWriteLogV( "(SSV_OV) [ERROR] i=%d, FCW=%04X mode=%d", i, fcw, mode );
					}
					break;
				case FCW_WORD2:
					if (mode == MODE_SYMBOL)
					{
						if (flashhide && flash) break;
						char str[3];
						str[0] = (fcw & 0xFE00) >> 9;// char 1
						str[1] = (fcw & 0x01FC) >> 2;// char 2
						str[2] = 0;

						CharMap( str );

						TextGrid( pMDU, posx, posy, str, strlen( str ), att, 0.0 );

						// increment position by 1 grid position
						// TODO check overflow?
						if (str[0] != 0) posx++;
						if (str[1] != 0) posx++;
					}
					else if (mode == MODE_CIRCLE)
					{
						if (flashhide && flash) break;
						short r = (fcw & 0x0FFC) >> 2;

						Circle( pMDU, posx, posy, r, att );
					}
					else if (mode == MODE_HIRES)
					{
						if (flashhide && flash) break;
						char str[3];
						str[0] = (fcw & 0xFE00) >> 9;// char 1
						str[1] = (fcw & 0x01FC) >> 2;// char 2
						str[2] = 0;

						CharMap( str );

						Text( pMDU, posx, posy, str, strlen( str ), att, rot );

						// increment position by char width
						// TODO check overflow?
						if (str[0] != 0) posx += DPS_CHAR_SIZE_X;
						if (str[1] != 0) posx += DPS_CHAR_SIZE_X;
					}
					else if (mode == MODE_VECTOR)
					{
						short pos = (fcw & 0x0FFC) >> 2;
						bool neg = (fcw & 0x1000) != 0;
						if (neg) pos = -pos;
						if (xcoord)
						{
							posx2 = pos;
							xcoord = !xcoord;
							break;
						}
						else posy2 = pos;
						xcoord = !xcoord;

						if (flashhide && flash) break;

						Line( pMDU, posx, posy, posx2, posy2, att );

						// save last pos
						posx = posx2;
						posy = posy2;
					}
					else
					{
						// TODO error
						oapiWriteLogV( "(SSV_OV) [ERROR] i=%d, FCW=%04X mode=%d", i, fcw, mode );
					}
					break;
				case FCW_BASIC:
					mode = (fcw & 0x001C) >> 2;
					large = (fcw & 0x0020) != 0;
					flash = (fcw & 0x0040) != 0;
					dash = (fcw & 0x0080) != 0;
					intensity = (fcw & 0x0100) != 0;
					orange = (fcw & 0x0200) != 0;

					att = ATT_GREEN;
					if (large) att |= ATT_LARGE;
					if (dash) att |= ATT_DASHED;
					// only allow one color
					if (orange) att |= ATT_ORANGE;
					else if (intensity) att |= ATT_YELLOW;
					break;
			}
		}
		return;
	}

	void IDP_software::ConvertTime( const long long input, unsigned short& d, unsigned short& h, unsigned short& m, unsigned short& s ) const
	{
		constexpr unsigned int SECS_DAY = 60 * 60 * 24;
		constexpr unsigned short SECS_HOUR = 60 * 60;
		constexpr unsigned short SECS_MINUTE = 60;
		double tmp = input * 0.008;

		d = static_cast<unsigned short>(tmp / SECS_DAY);
		tmp -= d * SECS_DAY;

		h = static_cast<unsigned short>(tmp / SECS_HOUR);
		tmp -= h * SECS_HOUR;

		m = static_cast<unsigned short>(tmp / SECS_MINUTE);
		tmp -= m * SECS_MINUTE;

		s = static_cast<unsigned short>(tmp);
		return;
	}

	void IDP_software::PrintClocks( vc::MDU* pMDU )
	{
		unsigned short usDay;
		unsigned short usHour;
		unsigned short usMinute;
		unsigned short usSecond;
		char cbuf[16];

		// mission time
		ConvertTime( pIDP->mt, usDay, usHour, usMinute, usSecond );
		sprintf_s( cbuf, 16, "%03d/%02d:%02d:%02d", usDay, usHour, usMinute, usSecond );
		TextGrid( pMDU, 39, 1, cbuf, 12, ATT_GREEN, 0 );

		// event time
		ConvertTime( pIDP->et, usDay, usHour, usMinute, usSecond );
		sprintf_s( cbuf, 16, "%03d/%02d:%02d:%02d", usDay, usHour, usMinute, usSecond );
		TextGrid( pMDU, 39, 2, cbuf, 12, ATT_GREEN, 0 );
		return;
	}

	void IDP_software::PrintScratchPadLine( vc::MDU* pMDU ) const
	{
		size_t len = strlen( pIDP->SPL );
		char tmp[2];
		tmp[1] = 0;
		bool flashhide = GetFlash();
		for (unsigned int i = 0; i < len; i++)
		{
			if ((flashhide) && (pIDP->SPLatt[i] & ATT_FLASH)) continue;

			tmp[0] = pIDP->SPL[i];
			TextGrid( pMDU, i + 1, 26, tmp, strlen( tmp ), pIDP->SPLatt[i], 0 );
		}
		return;
	}

	void IDP_software::PrintDisplay( vc::MDU* pMDU ) const
	{
		ProcessFCW( pIDP->DisplayBuffer, 1527, pMDU );
		return;
	}

	void IDP_software::PrintMessageLine( vc::MDU* pMDU ) const
	{
		ProcessFCW( pIDP->MessageLineBuffer, 50, pMDU );
		return;
	}

	void IDP_software::PrintPollFail( vc::MDU* pMDU ) const
	{
		TextGrid( pMDU, 42, 26, "POLL FAIL", 9, ATT_ORANGE, 0 );
		return;
	}

	void IDP_software::PrintBigX( vc::MDU* pMDU ) const
	{
		Line( pMDU, 0, 0, 1024, 731, ATT_ORANGE );
		Line( pMDU, 1024, 0, 0, 731, ATT_ORANGE );
		return;
	}

	void IDP_software::TextGrid( vc::MDU* pMDU, const short x, const short y, const char* txt, const unsigned int len, const unsigned char attributes, const double rot ) const
	{
		pMDU->Text( ((x - 1) * DPS_CHAR_SIZE_X) + DPS_DISPLAY_X_OFFSET, ((y - 1) * DPS_CHAR_SIZE_Y) + DPS_DISPLAY_Y_OFFSET, txt, len, attributes, rot );
		return;
	}

	void IDP_software::Text( vc::MDU* pMDU, const short x, const short y, const char* txt, const unsigned int len, const unsigned char attributes, const double rot ) const
	{
		pMDU->Text( static_cast<short>(x - (DPS_CHAR_SIZE_X * 0.5)), static_cast<short>(y - (DPS_CHAR_SIZE_Y * 0.5)), txt, len, attributes, rot );
		return;
	}

	void IDP_software::Line( vc::MDU* pMDU, const short x1, const short y1, const short x2, const short y2, const unsigned char attributes ) const
	{
		pMDU->Line( x1, y1, x2, y2, attributes );
		return;
	}

	void IDP_software::Circle( vc::MDU* pMDU, const short x, const short y, const short radius, const unsigned char attributes ) const
	{
		pMDU->Circle( x, y, radius, attributes );
		return;
	}
}
