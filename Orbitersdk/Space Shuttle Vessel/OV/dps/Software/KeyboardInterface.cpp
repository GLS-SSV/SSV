#include "KeyboardInterface.h"
#include "ICC_Interface.h"
#include "SimpleFCOS_IO.h"
#include "BusDefs.h"
#include "../SimpleGPCSystem.h"


namespace dps
{
	KeyboardInterface::KeyboardInterface( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "KeyboardInterface" ),
		DMIB_ERR_MSG(0), DMMV_MF_NEW{0,0,0,0}, DMMV_BYPASS(0), DMMB_MF_TIMING(0), DMMB_MF_TIMR{0,0,0,0}, DMMV_NEW_FRZ(0), DMMV_OLD_FRZ(0)
	{
		return;
	}

	KeyboardInterface::~KeyboardInterface( void )
	{
		return;
	}

	bool KeyboardInterface::OnParseLine( const char* keyword, const char* value )
	{
		if (!_stricmp( keyword, "DMIB_ERR_MSG" ))
		{
			sscanf_s( value, "%hu", &DMIB_ERR_MSG );
			return true;
		}
		else if (!_stricmp( keyword, "DMMV_MF_NEW" ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &DMMV_MF_NEW[0], &DMMV_MF_NEW[1], &DMMV_MF_NEW[2], &DMMV_MF_NEW[3] );
			return true;
		}
		else if (!_stricmp( keyword, "DMMV_BYPASS" ))
		{
			sscanf_s( value, "%hu", &DMMV_BYPASS );
			return true;
		}
		else if (!_stricmp( keyword, "DMMB_MF_TIMING" ))
		{
			sscanf_s( value, "%hu", &DMMB_MF_TIMING );
			return true;
		}
		else if (!_stricmp( keyword, "DMMB_MF_TIMR" ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &DMMB_MF_TIMR[0], &DMMB_MF_TIMR[1], &DMMB_MF_TIMR[2], &DMMB_MF_TIMR[3] );
			return true;
		}
		else if (!_stricmp( keyword, "DMMV_NEW_FRZ" ))
		{
			sscanf_s( value, "%hu", &DMMV_NEW_FRZ );
			return true;
		}
		else if (!_stricmp( keyword, "DMMV_OLD_FRZ" ))
		{
			sscanf_s( value, "%hu", &DMMV_OLD_FRZ );
			return true;
		}
		return false;
	}

	void KeyboardInterface::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "DMIB_ERR_MSG", DMIB_ERR_MSG );
		char tmp[256];
		sprintf_s( tmp, 255, "%hu %hu %hu %hu", DMMV_MF_NEW[0], DMMV_MF_NEW[1], DMMV_MF_NEW[2], DMMV_MF_NEW[3] );
		oapiWriteScenario_string( scn, "DMMV_MF_NEW", tmp );
		oapiWriteScenario_int( scn, "DMMV_BYPASS", DMMV_BYPASS );
		oapiWriteScenario_int( scn, "DMMB_MF_TIMING", DMMB_MF_TIMING );
		sprintf_s( tmp, 255, "%hu %hu %hu %hu", DMMB_MF_TIMR[0], DMMB_MF_TIMR[1], DMMB_MF_TIMR[2], DMMB_MF_TIMR[3] );
		oapiWriteScenario_string( scn, "DMMB_MF_TIMR", tmp );
		oapiWriteScenario_int( scn, "DMMV_NEW_FRZ", DMMV_NEW_FRZ );
		oapiWriteScenario_int( scn, "DMMV_OLD_FRZ", DMMV_OLD_FRZ );
		return;
	}

	void KeyboardInterface::OnPreStep( double simt, double simdt, double mjd )
	{
		DMI_MCDS_IN();
		return;
	}

	void KeyboardInterface::DMI_MCDS_IN( void )
	{
		const BUS_ID busid[4] = {BUS_DK1, BUS_DK2, BUS_DK3, BUS_DK4};
		// TODO 2.08Hz (480ms)
		SCP_GST gst;
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, ReadCOMPOOL_IS( SCP_TFCMID ), &gst, sizes_GST, pos_GST, cnt_GST, 5 );

		// handle mission time and crt timer
		long long mt;
		if (ReadCOMPOOL_IS( SCP_T_GMT_MET ) == 1)
		{
			mt = static_cast<long long>(ReadCOMPOOL_SD( SCP_CLOCK ) / 0.008);
		}
		else
		{
			mt = static_cast<long long>((ReadCOMPOOL_SD( SCP_CLOCK ) - ReadCOMPOOL_SD( SCP_T_MET_REF )) / 0.008);
		}
		long long et = (ReadCOMPOOL_SD( SCP_CLOCK ) - ReadCOMPOOL_SD( SCP_T_MET_REF )) / 0.008;// TODO
		unsigned short timefill[7];
		timefill[0] = (mt >> 32) & 0xFFFF;
		timefill[1] = (mt >> 16) & 0xFFFF;
		timefill[2] = (mt >> 0) & 0xFFFF;
		timefill[3] = (et >> 32) & 0xFFFF;
		timefill[4] = (et >> 16) & 0xFFFF;
		timefill[5] = (et >> 0) & 0xFFFF;
		timefill[6] = (0/*mt_dec*/ << 9) | (0/*mt_stop*/ << 8) | (0/*et_dec*/ << 1) | (0/*et_stop*/ << 0);// TODO

		for (unsigned char deu = 1; deu <= 4; deu++)
		{
			if (gst.CZ2B_ACT_RECVR & (0x04000000 >> deu))
			{
				// TODO DEU Poll Flag (CZ2B_D_DEU_POLL_FLAG)

				// request DEU time fill
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 1, timefill[0], 511 );
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 2, timefill[1], 511 );
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 3, timefill[2], 511 );
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 4, timefill[3], 511 );
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 5, timefill[4], 511 );
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 6, timefill[5], 511 );
				WriteCOMPOOL_AIS( SCP_DMC_DEU_BUF, 7, timefill[6], 511 );
				GetFCOS_IO()->OutputDEU( DEU_MSGFIELDS_TIME_FILL, SCP_DMC_DEU_BUF/*timefill*/, 7, busid[deu - 1] );

				// request DEU poll
				GetFCOS_IO()->InputDEU( DEU_MSGFIELDS_MCDS_STATUS_REQUEST, SCP_DEU_POLL_MSG + (16 * (deu - 1)), 16, busid[deu - 1] );


				if (0/*IO error*/)
				{
					// TODO errors
				}
				else
				{
					unsigned short WD_1 = ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), 64 );

					if ((WD_1 & 0x0008) || (WD_1 & 0x0002))// keyboard message or critical BITE present
					{
						// calc checksum 
						unsigned int checksum = 0;
						for (int i = 1; i < 16; i++) checksum += ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, i + ((deu - 1) * 16), 64 );
						checksum = ((~checksum) + 1) & 0xFFFF;
						if (checksum != ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 16 + ((deu - 1) * 16), 64 ))
						{
							if (((DMIB_ERR_MSG >> (9 - deu)) & 1) == 0)// not announced before
							{
								DMIB_ERR_MSG |= 1 << (9 - deu);
								// TODO I/O ERROR deu X
								oapiWriteLogV( "(SSV_OV) [INFO] I/O ERROR CRT %d", deu );
								// reset kybd msg present bit
								WD_1 &= ~(1 << 3);
								WriteCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), WD_1, 64 );
							}
						}
						else
						{
							DMIB_ERR_MSG &= ~(1 << (9 - deu));
						}

						unsigned short WD_2 = ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 2 + ((deu - 1) * 16), 64 );
						if ((WD_1 & 0x0008) && ((WD_2 & 0x001F) == 0))// keyboard message present and key count is 0
						{
							// TODO log GPC error
							// reset kybd msg present bit
							WD_1 &= ~(1 << 3);
							WriteCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), WD_1, 64 );
						}
					}

					DMM_MCDS_PROCESS( deu );
				}
			}
		}
		return;
	}

	void KeyboardInterface::DMM_MCDS_PROCESS( unsigned char deu )
	{
		unsigned short WD_1 = ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 1 + ((deu - 1) * 16), 64 );
		unsigned short WD_2 = ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, 2 + ((deu - 1) * 16), 64 );

		if ((WD_1 & 0xF000) == 0)// msg type
		{
			// DEU Poll response

			// TODO BITE

			DMMV_MF_NEW[deu - 1] = (WD_1 & 0x00C0) >> 6;

			DMMV_BYPASS = 1;

			if (DMMV_MF_NEW[deu - 1] != 3)
			{
				MF_Process( deu );

				if (DMMV_BYPASS == 0)
				{
					DMMV_NEW_FRZ = (WD_1 & 0x0010) >> 4;

					if (DMMV_NEW_FRZ != DMMV_OLD_FRZ)
					{
						// TODO 405.6
					}

					if ((WD_1 & 0x0008) == 0)// keyboard message not present
					{
						if (WD_1 & 0x0020)// ACK request
						{
							WriteCOMPOOL_IS( SCP_ACK_KEY, 1 );
						}
						else if (WD_1 & 0x0800)// MSG RESET request
						{
							WriteCOMPOOL_IS( SCP_MSGRESET_KEY, 1 );
							// reset illegal entry
							unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
							illegalentryfault &= ~(1 << (deu - 1));
							WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
						}

						// TODO DEU poll flag = 1

						return;
					}
				}
				else
				{
					if ((DMMB_MF_TIMING & (1 << (deu - 1))) || (DMMV_MF_NEW[deu - 1] == 3))
					{
						// TODO DEU poll flag = 1
					}

					return;
				}
			}
			else
			{
				// TODO DEU poll flag = 1

				return;
			}
		}
		else
		{
			// DEU Equivalent
			if (((WD_1 >> 5) & 1) == 1)// ACK request
			{
				WriteCOMPOOL_IS( SCP_ACK_KEY, 1 );

				// TODO DEU poll flag = 1
			}
			else if (((WD_1 >> 11) & 1) == 1)// MSG RESET request
			{
				WriteCOMPOOL_IS( SCP_MSGRESET_KEY, 1 );
				// reset illegal entry
				unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
				illegalentryfault &= ~(1 << (deu - 1));
				WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );

				// TODO DEU poll flag = 1
			}
		}

		if (WD_1 & 0x0008)// keyboard message present
		{
			// copy keys
			SCP_DIT dit;
			ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, deu, &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );
			for (unsigned int i = 3, k = 0; i < 12; i++)
			{
				unsigned short WD_i = ReadCOMPOOL_AIS( SCP_DEU_POLL_MSG, i + ((deu - 1) * 16), 64 );

				dit.CZ1V_D_DIT_KYBD_MSG[k++] = (WD_i >> 11) & 0b11111;
				dit.CZ1V_D_DIT_KYBD_MSG[k++] = (WD_i >> 6) & 0b11111;
				dit.CZ1V_D_DIT_KYBD_MSG[k++] = (WD_i >> 1) & 0b11111;
			}

			dit.CZ1V_D_NUMOFKEYS = WD_2 & 0x001F;
			WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, deu, &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );

			WriteCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY, ReadCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY ) | (0x1000 >> (deu - 1)) );
			WriteCOMPOOL_IS( SCP_CZ1E_D_MCDS_EVENT, 1 );

#ifdef _DEBUG
			// dump keyboard msgs to log
			std::string cbuf;
			for (int i = 1; i <= (WD_2 & 0x001F); i++)
			{
				unsigned short k = dit.CZ1V_D_DIT_KYBD_MSG[i - 1];
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
			oapiWriteLogV( "(SSV_OV) [INFO] DK %d -> GPC %d: %s", deu, ReadCOMPOOL_IS( SCP_TFCMID ), cbuf.c_str() );
#endif// _DEBUG
		}

		return;
	}

	void KeyboardInterface::MF_Process( unsigned char deu )
	{
		if (DMMV_MF_NEW[deu - 1] != ReadCOMPOOL_AIS( SCP_CZ2V_MF_OLD, deu, 4 ))
		{
			DMMB_MF_TIMING |= (1 << (deu - 1));

			DMMB_MF_TIMR[deu - 1] = 1;

			WriteCOMPOOL_AIS( SCP_CZ2V_MF_OLD, deu, DMMV_MF_NEW[deu - 1], 4 );
		}
		else
		{
			if (DMMB_MF_TIMING & (1 << (deu - 1)))
			{
				DMMB_MF_TIMR[deu - 1]++;

				if (DMMB_MF_TIMR[deu - 1] == 3)
				{
					// TODO
					//CZ1V_D_DIT_NUMOFKEYS = 2;
					//CZ1V_D_DIT_KYBD_MSG = 12;

					unsigned short ICC_Message[2];
					ICC_Message[0] = 2;// msg size
					ICC_Message[0] |= 24 << 8;// msg index
					ICC_Message[1] = DMMV_MF_NEW[deu - 1];// MF
					ICC_Message[1] |= deu << 2;// DEU
					// TODO loop
					ICC_Interface* pICC = dynamic_cast<ICC_Interface*>(GetCOMSUB( "ICC_Interface" ));
					pICC->DIM_ICC_COLLECTOR( ICC_Message );

					WriteCOMPOOL_AIS( SCP_CZ2V_DEU_MF, deu, DMMV_MF_NEW[deu - 1], 4 );

					// TODO
					// set so ICC msg with new deu mf is sent
					//CZ2B_ICC_FLAG = 1;

					DMMB_MF_TIMING &= ~(1 << (deu - 1));
				}
			}
			else
			{
				DMMV_BYPASS = 0;
			}
		}
		return;
	}
}
