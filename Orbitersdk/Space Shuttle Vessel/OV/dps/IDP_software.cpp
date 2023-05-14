#include "IDP_software.h"
#include "IDP.h"


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
		ProcessKeyboard();

		// data input
		// ADC 1
		pIDP->MEDStransaction( (pIDP->usIDPID <= 2) ? 5 : 6, 1, 0b00010, pIDP->ADCdata[0], 32 );
		// ADC 2
		pIDP->MEDStransaction( (pIDP->usIDPID <= 2) ? 8 : 9, 1, 0b00010, pIDP->ADCdata[1], 32 );
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
					pIDP->GPCkeybuff[pIDP->GPCkeybufflen++] = key;
					continue;
				}

				// is single key?
				if ((key == DEU_GPC_KEY_CODE_SYSSUMM) ||
					(key == DEU_GPC_KEY_CODE_FAULTSUMM) ||
					(key == DEU_GPC_KEY_CODE_RESUME) ||
					((key == DEU_GPC_KEY_CODE_EXEC) && (pIDP->SPLkeyslen == 0)))
				{
					// clear SPL
					pIDP->SPLkeyslen = 0;
					// write key in SPL
					pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;
					// clear error
					pIDP->SPLerror = false;
					continue;
				}

				// only continue processing key if no ERR
				if (pIDP->SPLerror) continue;

				// TODO handle line complete

				// continue existing key sequence?
				if (pIDP->SPLkeyslen != 0)
				{
					// write key in SPL
					pIDP->SPLkeys[pIDP->SPLkeyslen++] = key;

					// check SPL start to pick processing
					if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_OPS)
					{
						if (((pIDP->SPLkeyslen == 5) && (key != DEU_GPC_KEY_CODE_PRO)) ||
							((pIDP->SPLkeyslen <= 4) && (key > DEU_GPC_KEY_CODE_9)))
						{
							pIDP->SPLerror = true;
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
									// TODO copy to GPC buff
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
									// TODO copy to GPC buff
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
									//ITEMstate[SPLkeyslen - 1] = 4;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// TODO copy to GPC buff
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
									// TODO copy to GPC buff
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
									//ITEMstate[SPLkeyslen - 1] = 6;
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
									//ITEMstate[SPLkeyslen - 1] = 7;
								}
								else if ((key == DEU_GPC_KEY_CODE_MINUS) || (key == DEU_GPC_KEY_CODE_PLUS))
								{
									pIDP->ITEMstate[pIDP->SPLkeyslen - 1] = 6;
								}
								else if (key == DEU_GPC_KEY_CODE_EXEC)
								{
									// TODO copy to GPC buff
								}
								else
								{
									pIDP->SPLerror = true;
								}
								break;
						}

						// TODO check size
					}
					else if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_IORESET)
					{
						if (key != DEU_GPC_KEY_CODE_EXEC)
						{
							pIDP->SPLerror = true;
						}
					}
					else if (pIDP->SPLkeys[0] == DEU_GPC_KEY_CODE_GPCCRT)
					{
						if (((pIDP->SPLkeyslen == 4) && (key != DEU_GPC_KEY_CODE_EXEC)) ||
							((pIDP->SPLkeyslen <= 3) && (key > DEU_GPC_KEY_CODE_9)))
						{
							pIDP->SPLerror = true;
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
					AddSPLatt( strlen( pIDP->SPL ), 3, dps::DEUATT_FLASHING );
					strcat_s( pIDP->SPL, "OPS " );
					break;
				case DEU_GPC_KEY_CODE_SPEC:
					AddSPLatt( strlen( pIDP->SPL ), 4, dps::DEUATT_FLASHING );
					strcat_s( pIDP->SPL, "SPEC " );
					break;
				case DEU_GPC_KEY_CODE_FAULTSUMM:
					strcat_s( pIDP->SPL, "FAULT SUMM" );
					break;
				case DEU_GPC_KEY_CODE_ITEM:
					AddSPLatt( strlen( pIDP->SPL ), 4, dps::DEUATT_FLASHING );
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
					AddSPLatt( strlen( pIDP->SPL ), 9, dps::DEUATT_FLASHING );
					strcat_s( pIDP->SPL, "I/O RESET" );
					break;
				case DEU_GPC_KEY_CODE_GPCCRT:
					AddSPLatt( strlen( pIDP->SPL ), 7, dps::DEUATT_FLASHING );
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
		unsigned short SPL_max_size = 39;// TODO max is 29 with POLL FAIL
		if (((strlen( pIDP->SPL ) > SPL_max_size) && (pIDP->SPLkeys[pIDP->SPLkeyslen - 1] != DEU_GPC_KEY_CODE_EXEC)) || (pIDP->SPLerror == true))
		{
			pIDP->SPLerror = true;
			AddSPLatt( 1, 9, 0 );// clear initiator flash
			AddSPLatt( strlen( pIDP->SPL ), 5, dps::DEUATT_FLASHING );
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
}
