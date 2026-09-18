#include "UserInterfaceControl.h"
#include "../SimpleGPCSystem.h"
#include "GeneralDisplays.h"
#include "CRT_Interface.h"


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
	constexpr unsigned char DEU_GPC_KEY_CODE_MFSWITCH = 0x20;


	//constexpr unsigned short DMCV_SYS_SPEC[2];// System_SPEC_Verification_Data
	constexpr unsigned short DMCV_SYS_ID[2] = {1, 2};// System_SPEC_Verification_Data.System_SPEC_ID
	constexpr unsigned short DMCV_SYS_BLOCKS[2] = {1, 1};// System_SPEC_Verification_Data.System_SPEC_Block

	//constexpr unsigned short DMCVL_SYS_SPEC_NAME[2];// System_SPEC_Names_Table
	std::string DMCV_SYS_SPNAME[2] = {"DPS_UTILITY"/*HACK no idea of actual name*/, "ASC_TIME_MGMT"};// System_SPEC_Names_Table.System_SPEC_Program_Name

	// manual OPS transition table
	constexpr unsigned int DM6V_TR_TAB[21] = {
		// OPS 0
		0x81403800,
		// G1
		0x00002000,
		0x00020000,
		0x08020000,
		0x04410000,
		0x02400000,
		0x01400000,
		// G2
		0x81C04000,
		0x01000000,
		// G3
		0x01600000,
		0x00500000,
		0x00480000,
		0x00040000,
		0x00002000,
		// G6
		0x00010000,
		0x00008000,
		0x00002000,
		// G8
		0x01404000,
		// G9
		0xC0002000,
		// S2
		0x80000800,
		0x80001000,
		};


	UserInterfaceControl::UserInterfaceControl( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "UserInterfaceControl" ),
		pGPC(pGPC)
	{
		DMC_REC_IN_PROGRESS = 0;
		DMC_SAVE = 0;

		DMC_MFI = pGPC->ReadCOMPOOL_IS( SCP_TFCMID ) + 1;// HACK

		DMC_SPECID[0] = 500;
		DMC_SPECID[1] = 500;
		DMC_SPECID[2] = 500;
		DMC_SPECID[3] = 500;

		DMC_MINXTS[0] = 0;
		DMC_MINXTS[1] = 0;
		DMC_MINXTS[2] = 0;
		DMC_MINXTS[3] = 0;

		DMC_AINXTS[0] = 0;
		DMC_AINXTS[1] = 0;
		DMC_AINXTS[2] = 0;
		DMC_AINXTS[3] = 0;

		DMC_AMTVALID = 1;


		// DMC_SUPER init
		SCP_REQBLK DMCV_REQBLK;
		DMCV_REQBLK.DMCV_RQWTC = 1;
		DMCV_REQBLK.DMCV_RQPROC_TY = 3;
		DMCV_REQBLK.DMCV_RQAMT_IN = 0;
		DMCV_REQBLK.DMCV_XXMACT_I = 1;
		DMCV_REQBLK.DMCV_RQOSNBR = 0;
		DMCV_REQBLK.DMCV_RQMODE = 1;
		DMCV_REQBLK.DMCV_RQMACT_IN[0] = 1;
		DMCV_REQBLK.DMCV_RQMACT_IN[1] = 0;
		DMCV_REQBLK.DMCV_RQMACT_IN[2] = 0;
		DMCV_REQBLK.DMCV_RQMACT_IN[3] = 0;
		DMCV_REQBLK.DMCV_RQMACT_IN[4] = 0;
		WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

		DMCV_DEU_MACT[0] = 0;
		DMCV_DEU_MACT[1] = 0;
		DMCV_DEU_MACT[2] = 0;
		DMCV_DEU_MACT[3] = 0;

		DMC_INITIAL = 0;

		DMC_REC_IN_PROGRESS = 0;
		DMC_REC_IP2 = 0;
		// TODO MM/DFT_IO_Completion_Flag = 0;
		// TODO Blank_Scratch_Pad_Line_Flag = 0;// ?
		return;
	}

	UserInterfaceControl::~UserInterfaceControl( void )
	{
		return;
	}

	bool UserInterfaceControl::OnParseLine( const char* keyword, const char* value )
	{
		if (!_stricmp( keyword, "DMC_CASE" ))
		{
			sscanf_s( value, "%hu", &DMC_CASE );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_K" ))
		{
			sscanf_s( value, "%hu", &DMC_K );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_PROCTYPE" ))
		{
			sscanf_s( value, "%hu", &DMC_PROCTYPE );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TVAL" ))
		{
			sscanf_s( value, "%hu", &DMC_TVAL );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TVAL1" ))
		{
			sscanf_s( value, "%hu", &DMC_TVAL1 );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TVAL_2" ))
		{
			sscanf_s( value, "%hu", &DMC_TVAL_2 );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TVAL_3" ))
		{
			sscanf_s( value, "%hu", &DMC_TVAL_3 );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TVAL_4" ))
		{
			sscanf_s( value, "%hu", &DMC_TVAL_4 );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_REC_IN_PROGRESS" ))
		{
			sscanf_s( value, "%hu", &DMC_REC_IN_PROGRESS );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TERMI" ))
		{
			sscanf_s( value, "%hu", &DMC_TERMI );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TINDX" ))
		{
			sscanf_s( value, "%hu", &DMC_TINDX );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_SZFMACT" ))
		{
			sscanf_s( value, "%hu", &DMC_SZFMACT );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_REQOSNBR" ))
		{
			sscanf_s( value, "%hu", &DMC_REQOSNBR );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_AMT_I" ))
		{
			sscanf_s( value, "%hd", &DMC_AMT_I );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_MACT_I" ))
		{
			sscanf_s( value, "%hu", &DMC_MACT_I );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_CUR_OP" ))
		{
			sscanf_s( value, "%hu", &DMC_CUR_OP );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_SEQVAL" ))
		{
			sscanf_s( value, "%hu", &DMC_SEQVAL );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_WTCT" ))
		{
			sscanf_s( value, "%hu", &DMC_WTCT );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_SAVE" ))
		{
			sscanf_s( value, "%hu", &DMC_SAVE );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_REQMODE" ))
		{
			sscanf_s( value, "%hd", &DMC_REQMODE );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_SPECID" ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &DMC_SPECID[0], &DMC_SPECID[1], &DMC_SPECID[2], &DMC_SPECID[3] );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_MINXTS" ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &DMC_MINXTS[0], &DMC_MINXTS[1], &DMC_MINXTS[2], &DMC_MINXTS[3] );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_AINXTS" ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &DMC_AINXTS[0], &DMC_AINXTS[1], &DMC_AINXTS[2], &DMC_AINXTS[3] );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_FOUND" ))
		{
			sscanf_s( value, "%hu", &DMC_FOUND );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_GRTIX" ))
		{
			sscanf_s( value, "%hu", &DMC_GRTIX );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_UNDX" ))
		{
			sscanf_s( value, "%hu", &DMC_UNDX );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_GPCZ" ))
		{
			sscanf_s( value, "%hu", &DMC_GPCZ );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_TYPE" ))
		{
			sscanf_s( value, "%hu", &DMC_TYPE );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_PROG_NAME" ))
		{
			DMC_PROG_NAME = value;
			return true;
		}
		else if (!_stricmp( keyword, "DMC_INITIAL" ))
		{
			sscanf_s( value, "%hu", &DMC_INITIAL );
			return true;
		}
		else if (!_stricmp( keyword, "DMC_MACT_INDEX" ))
		{
			sscanf_s( value, "%hu", &DMC_MACT_INDEX );
			return true;
		}
		else if (!_stricmp( keyword, "DMCV_DEU_MACT" ))
		{
			sscanf_s( value, "%hu %hu %hu %hu", &DMCV_DEU_MACT[0], &DMCV_DEU_MACT[1], &DMCV_DEU_MACT[2], &DMCV_DEU_MACT[3] );
			return true;
		}
		return false;
	}

	void UserInterfaceControl::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "DMC_CASE", DMC_CASE );
		oapiWriteScenario_int( scn, "DMC_K", DMC_K );
		oapiWriteScenario_int( scn, "DMC_PROCTYPE", DMC_PROCTYPE );
		oapiWriteScenario_int( scn, "DMC_TVAL", DMC_TVAL );
		oapiWriteScenario_int( scn, "DMC_TVAL1", DMC_TVAL1 );
		oapiWriteScenario_int( scn, "DMC_TVAL_2", DMC_TVAL_2 );
		oapiWriteScenario_int( scn, "DMC_TVAL_3", DMC_TVAL_3 );
		oapiWriteScenario_int( scn, "DMC_TVAL_4", DMC_TVAL_4 );
		oapiWriteScenario_int( scn, "DMC_REC_IN_PROGRESS", DMC_REC_IN_PROGRESS );
		oapiWriteScenario_int( scn, "DMC_TERMI", DMC_TERMI );
		oapiWriteScenario_int( scn, "DMC_TINDX", DMC_TINDX );
		oapiWriteScenario_int( scn, "DMC_SZFMACT", DMC_SZFMACT );
		oapiWriteScenario_int( scn, "DMC_REQOSNBR", DMC_REQOSNBR );
		oapiWriteScenario_int( scn, "DMC_AMT_I", DMC_AMT_I );
		oapiWriteScenario_int( scn, "DMC_MACT_I", DMC_MACT_I );
		oapiWriteScenario_int( scn, "DMC_CUR_OP", DMC_CUR_OP );
		oapiWriteScenario_int( scn, "DMC_SEQVAL", DMC_SEQVAL );
		oapiWriteScenario_int( scn, "DMC_WTCT", DMC_WTCT );
		oapiWriteScenario_int( scn, "DMC_SAVE", DMC_SAVE );
		oapiWriteScenario_int( scn, "DMC_REQMODE", DMC_REQMODE );
		char tmp[256];
		sprintf_s( tmp, 255, "%hu %hu %hu %hu", DMC_SPECID[0], DMC_SPECID[1], DMC_SPECID[2], DMC_SPECID[3] );
		oapiWriteScenario_string( scn, "DMC_SPECID", tmp );
		sprintf_s( tmp, 255, "%hu %hu %hu %hu", DMC_MINXTS[0], DMC_MINXTS[1], DMC_MINXTS[2], DMC_MINXTS[3] );
		oapiWriteScenario_string( scn, "DMC_MINXTS", tmp );
		sprintf_s( tmp, 255, "%hu %hu %hu %hu", DMC_AINXTS[0], DMC_AINXTS[1], DMC_AINXTS[2], DMC_AINXTS[3] );
		oapiWriteScenario_string( scn, "DMC_AINXTS", tmp );
		oapiWriteScenario_int( scn, "DMC_FOUND", DMC_FOUND );
		oapiWriteScenario_int( scn, "DMC_GRTIX", DMC_GRTIX );
		oapiWriteScenario_int( scn, "DMC_UNDX", DMC_UNDX );
		oapiWriteScenario_int( scn, "DMC_GPCZ", DMC_GPCZ );
		oapiWriteScenario_int( scn, "DMC_TYPE", DMC_TYPE );
		oapiWriteScenario_string( scn, "DMC_PROG_NAME", const_cast<char*>(DMC_PROG_NAME.c_str()) );
		oapiWriteScenario_int( scn, "DMC_INITIAL", DMC_INITIAL );
		oapiWriteScenario_int( scn, "DMC_MACT_INDEX", DMC_MACT_INDEX );
		sprintf_s( tmp, 255, "%hu %hu %hu %hu", DMCV_DEU_MACT[0], DMCV_DEU_MACT[1], DMCV_DEU_MACT[2], DMCV_DEU_MACT[3] );
		oapiWriteScenario_string( scn, "DMCV_DEU_MACT", tmp );
		return;
	}

	void UserInterfaceControl::SetIllegalEntry( const unsigned short deu )
	{
		unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
		illegalentryfault |= (1 << (deu - 1));
		WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
		return;
	}

	unsigned short UserInterfaceControl::GetIdx( const unsigned short ops, const unsigned short mode ) const
	{
		if (ops == 0) return 1;

		SCP_MF CDAV_MF;
		ReadCOMPOOL_ASTRUCT( SCP_CDAV_MF, DMC_MFI, &CDAV_MF, sizes_SPEC, pos_SPEC, cnt_SPEC, 3 );

		int start = CDAV_MF.CDAV_MF_FOPS;
		int end = start + CDAV_MF.CDAV_MF_NOPS - 1;

		for (int i = start; i <= end; i++)
		{
			SCP_OPS CDAV_OPS;
			ReadCOMPOOL_ASTRUCT( SCP_CDAV_OPS, i, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			if ((CDAV_OPS.CDAV_OP_OPSID == ops) && (CDAV_OPS.CDAV_OP_NMODES >= mode))
			{
				return CDAV_OPS.CDAV_OP_MODXXFR_ST + mode - 1;
			}
		}
		return 0;
	}

	void UserInterfaceControl::OnPreStep( double simt, double simdt, double mjd )
	{
		DMC_SUPER();
		return;
	}

	void UserInterfaceControl::DMC_SUPER( void )
	{
		if (ReadCOMPOOL_IS( SCP_CZ1E_D_MCDS_EVENT ) == 1)
		{
			WriteCOMPOOL_IS( SCP_CZ1E_D_MCDS_EVENT, 0 );

			DM1_KEYBOARD();
		}
		else if (ReadCOMPOOL_IS( SCP_CDME_APP_SERVICE ) == 1)
		{
			WriteCOMPOOL_IS( SCP_CDME_APP_SERVICE, 0 );

			DMC_CASE = 11;

			DMC_FUNCTIONS();
		}
		else if (false)
		{
			// TODO MM event
		}
		return;
	}

	void UserInterfaceControl::DMC_FUNCTIONS( void )
	{
		// HACK reworked case numbers to fit current key IDs

		//ID_GPC/*DMC_GPCID L190*/ = ReadCOMPOOL_IS( SCP_TFCMID );
		//Annunciation_Error_ID = -1;

		// HACK assignment below is 3 in the text, 2 in the diagram. using 2, as 3 caused SPECs to be diplayed as DISPs
		DMCVL_D_LVLN = 2;

		// ICC_Status_Word = 0;

		if (DMC_CASE > 11)
		{
			Keyboard_Input_Initialization();
		}

		switch (DMC_CASE - 9/*DMC_CASE_OFFSET*/)
		{
			case 1:
				// TODO MM
				break;
			case 2:
				Application_Interface();
				break;
			case 3:
				// HACK moved to 23
				break;
			case 4:
				// TODO 505.5
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				// sys summ
				{
					// check if defined
					if (ReadCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 3, 2 ) == 0)
					{
						SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
						break;
					}

					SCP_MAT mat;
					ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

					// check if should call first or second
					if (ReadCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 3, 2 ) != mat.CDMV_MAT_DISP_NUMBER[2])
					{
						// call first
						DMCVL_D_DISP = ReadCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 3, 2 );
					}
					else if (ReadCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 3, 2 ) != 0)
					{
						// call second
						DMCVL_D_DISP = ReadCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 3, 2 );
					}

					DMCVL_D_LVLN = 3;

					mat.CDMV_MAT_LEVEL = 0;
					WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

					DMC_DISPLAY();
				}
				break;
			case 8:
				// HACK added mode transition enable/inhibit
				if (ReadCOMPOOL_IS( SCP_CZ1E_OPS_MODE_INHIBIT ) != 0)
				{
					SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
					break;
				}
				// HACK added manual transition validity check
				{
					/*int src_idx = 0;
					int tgt_idx = 0;

					// find current OPS MACT
					SCP_REQBLK DMCV_REQBLK;
					ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

					SCP_MACT CZ1V_D_MACT;
					ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1], &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 7 );

					// get current index
					src_idx = GetIdx( CZ1V_D_MACT.CZ1V_D_OPS, CZ1V_D_MACT.CZ1V_D_MOD );
					if (src_idx == 0)
					{
						SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
						break;
					}

					// get target index
					SCP_DIT dit;
					ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );
					tgt_idx = GetIdx( dit.CZ1V_D_DIT_KYBD_MSG[1], (10 * dit.CZ1V_D_DIT_KYBD_MSG[2]) + dit.CZ1V_D_DIT_KYBD_MSG[3] );
					if (tgt_idx == 0)
					{
						SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
						break;
					}

					if (DM6V_TR_TAB[src_idx - 1] & (0x80000000 >> (tgt_idx - 1)))*/
					{
						DMC_SEQ_REQ_PROC( DMC_CASE );
					}
					/*else
					{
						SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
					}*/
				}
				break;
			case 9:
				{
					SCP_DIT dit;
					ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );
					if ((dit.CZ1V_D_NUMOFKEYS < 3) || (dit.CZ1V_D_NUMOFKEYS > 5))// is number of keystrokes valid?
					{
						// TODO set error condition
						break;
					}
					else
					{
						// calculate page number
						unsigned short page = dit.CZ1V_D_DIT_KYBD_MSG[1];
						if (dit.CZ1V_D_NUMOFKEYS > 3)
						{
							page = (page * 10) + dit.CZ1V_D_DIT_KYBD_MSG[2];
							if (dit.CZ1V_D_NUMOFKEYS > 4)
							{
								page = (page * 10) + dit.CZ1V_D_DIT_KYBD_MSG[3];
							}
						}

						// is request for SPEC?
						if ((page % 10) <= 5)
						{
							DMC_SEQ_REQ_PROC( DMC_CASE );
						}
						else
						{
							 // HACK filter displays
							DFB_Search( page );
							if (DMC_FOUND == 0)
							{
								SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
								break;
							}

							// is request fault summary page? (DISP 99)
							if (page == 99)
							{
								// TODO que error annunciator FMPT_UI_OPERR to clear FSP
								// TODO Annunciation_Error_ID = 0;
								WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CLEAR, 1 );
							}

							DMCVL_D_LVLN = 3;
							DMCVL_D_DISP = page;

							// HACK added level 0 to force update
							SCP_MAT mat;
							ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );
							mat.CDMV_MAT_LEVEL = 0;
							WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

							DMC_DISPLAY();
						}
					}
				}
				break;
			case 10:
				// fault summ
				{
					SCP_MAT mat;
					ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

					DMCVL_D_DISP = 99;
					DMCVL_D_LVLN = 3;

					mat.CDMV_MAT_LEVEL = 0;
					WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

					DMC_DISPLAY();
				}
				break;
			case 11:
				DM9_ITEM();
				break;
			case 12:
				break;
			case 13:
				// TODO MSG RESET
				break;
			case 14:
				break;
			case 15:
				DIR_IORESET();
				break;
			case 16:
				// TODO 505.7
				break;
			case 17:
				break;
			case 18:
				DMR_RESUME();
				break;
			case 19:
				// TODO ACK
				break;
			case 20:
				break;
			case 21:
				// TODO 505.10
				break;
			case 22:
				// TODO 505.10
				break;
			case 23:
				MF_Change();
				break;
		}

		MCDS_Function_Clean_Up();
		return;
	}

	void UserInterfaceControl::Keyboard_Input_Initialization( void )
	{
		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

		if (DMCV_REQBLK.DMCV_RQMACT_IN[1 + ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] != 0)
		{
			DMC_MACT_INDEX = DMCV_REQBLK.DMCV_RQMACT_IN[1 + ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1];// SPEC
		}
		else
		{
			DMC_MACT_INDEX = DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1];// OPS
		}

		//DEU_No = DEU_Number;// DIT Index

		//Keyboard_Next_Input[DEU] = Keyboard_Next_Input + 1;
		return;
	}

	void UserInterfaceControl::MCDS_Function_Clean_Up( void )
	{
		if (DMC_CASE > 11)
		{
			//DEU_Number (DFT_Index) = DEU_No;

			WriteCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY, ReadCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY ) & ~(0x1000 >> (ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1)) );

			if (DMC_REC_IN_PROGRESS == 0)// Disabled
			{
				//DEU_Poll_Flags = 1;// Enabled
			}
		}
		return;
	}

	void UserInterfaceControl::Application_Interface( void )
	{
		for (unsigned int DMC_I = 1; DMC_I <= 4; DMC_I++)
		{
			if (ReadCOMPOOL_AIS( SCP_CZ1E_D_MACT_EVTS, DMC_I, 4 ) == 1)
			{
				WriteCOMPOOL_AIS( SCP_CZ1E_D_MACT_EVTS, DMC_I, 0, 4 );

				//Major_Function_ID (local) = Major_Function_ID (cs);
				//CZ1V_D_MF_ID/*J040.35*/;

				WriteCOMPOOL_IS( SCP_DMC_DIT_INDEX, DMCV_DEU_MACT[DMC_I - 1] );

				DMC_MACT_INDEX = DMC_I;

				SCP_MACT CZ1V_D_MACT;
				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				if (CZ1V_D_MACT.CZ1B_D_FLAGS & 0x4000)// enabled
				{
					CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x4000;
					WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

					if (ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) == 0)
					{
						DMCVL_D_LVLN = 1;
					}

					DMCVL_D_DISP = CZ1V_D_MACT.CZ1V_D_NEW_DISP;

					DMC_DISPLAY();

					ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
					CZ1V_D_MACT.CZ1V_D_NEW_DISP = 0;
					WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				}

				if (CZ1V_D_MACT.CZ1B_D_FLAGS & 0x0400)
				{
					CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x0400;// Disabled
					WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

					DMC_CASE = 0;

					if (DMC_I == 1)
					{
						//Major_Function_ID = MAT_Major_Function_Setting;
					}

					// TODO CALL 510

					DMC_CASE = 11;
				}

				if (CZ1V_D_MACT.CZ1B_D_FLAGS & 0x0100)
				{
					CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x0100;
					WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

					DMC_SEQ_REQ_PROC( 0 );
				}

				//if (DMC_I == 1)// HACK disabled test so transitions can be called from all DEUs
				{
					if (CZ1V_D_MACT.CZ1B_D_FLAGS & 0x0010)
					{
						CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x0010;
						WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

						DMC_SEQ_REQ_PROC( 1 );
					}

					if (CZ1V_D_MACT.CZ1B_D_FLAGS & 0x0008)
					{
						CZ1V_D_MACT.CZ1B_D_FLAGS &= ~0x0008;
						WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

						DMC_SEQ_REQ_PROC( 2 );
					}
				}
			}
		}
		return;
	}

	void UserInterfaceControl::MF_Change( void )
	{
		SCP_MAT mat;
		ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

		mat.CDMV_MAT_LEVEL = 0;

		mat.CDMV_MAT_DISP_NUMBER[0] = 0;
		mat.CDMV_MAT_DISP_NUMBER[1] = 0;
		mat.CDMV_MAT_DISP_NUMBER[2] = 0;

		// HACK MF set to unsupported
		mat.CDMV_MAT_MF = 1;//CZ1V_D_MACT.CZ1V_D_MF_ID;

		mat.CDMB_MAT_CRT_STAT &= ~0x1000;

		WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

		SCP_DIT dit;
		ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );

		if (dit.CZ1V_D_DIT_KYBD_MSG[1] == 0)
		{
			// HACK set correct MF
			mat.CDMV_MAT_MF = DMC_MFI;
			WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

			SCP_MACT CZ1V_D_MACT;
			ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
			DMCVL_D_DISP = CZ1V_D_MACT.CZ1V_D_DISP;

			SCP_REQBLK DMCV_REQBLK;
			ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

			if ((DMC_MACT_INDEX != DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1]) || (DMCV_REQBLK.DMCV_RQMACT_IN[1 + ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] == 1))
			{
				DMC_DISPLAY();
				DMC_MACT_INDEX = DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1];

				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				DMCVL_D_DISP = CZ1V_D_MACT.CZ1V_D_DISP;
			}

			DMCVL_D_LVLN = 1;// OPS
			DMC_DISPLAY();
		}

		DMC_REC_IP2 = 0;
		return;
	}

	void UserInterfaceControl::DMR_RESUME( void )
	{
		SCP_MAT mat;
		ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

		if (mat.CDMV_MAT_DISP_NUMBER[3 - 1] != 0)
		{
			// resume from DISP
			mat.CDMV_MAT_LEVEL = 0;

			mat.CDMV_MAT_DISP_NUMBER[3 - 1] = 0;
			WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

			// HACK load requested display info for DMC_DISPLAY
			DMCVL_D_LVLN = 2;
			DMCVL_D_DISP = mat.CDMV_MAT_DISP_NUMBER[2 - 1];

			if (mat.CDMV_MAT_DISP_NUMBER[2 - 1] == 0)
			{
				DMCVL_D_LVLN = 1;

				// HACK load requested display info for DMC_DISPLAY
				DMCVL_D_DISP = mat.CDMV_MAT_DISP_NUMBER[1 - 1];
			}

			DMC_DISPLAY();
		}
		else
		{
			if (mat.CDMV_MAT_DISP_NUMBER[2 - 1] != 0)
			{
				// resume from SPEC
				mat.CDMV_MAT_LEVEL = 0;// HACK this should also be done when resuming from SPEC.... right?

				// HACK reset number
				mat.CDMV_MAT_DISP_NUMBER[2 - 1] = 0;
				WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

				if (DMC_MACT_INDEX == 1)
				{
					DMC_SEQ_REQ_PROC( 0 );// terminate SPEC 00
				}
				else
				{
					//Keyboard_Message_ID/*CZ1V_D_KEY_ID J040.49*/ = MCDS_Function/*DMC_CASE L219*/;

					SCP_MACT CZ1V_D_MACT;
					ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x8000;// block termination request
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// mode termination request
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x2000;// control segment termination request
					CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 1;
					WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				}
			}
			else
			{
				// resume from OPS
				//Annunciation_Error_ID/*DMC_FMPT_ERR L286*/ = 43;// DU011
				// set illegal entry
				SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
			}
		}
		return;
	}


	void UserInterfaceControl::DMC_DISPLAY( void )
	{
		// 1 - keyboard inputs
		// 2 - MF switch changes at a DEU
		// 3 - status changes of a DEU (FREEZE)
		// 4 - requests via initiated control segments

		/*
		If found, the MCDS Allocation Table (MAT) is updated and the background
		is output via New_Display_Processor. If not found in one of the five
		DFBs, the DMMD is searched to determine if the required display is
		available on the MM. If found, the necessary I/O is initiated to obtain
		the DFT for the requested display...
		*/
		no_name();

		///////////////
		/*DFB_Max_Size[1] = 3500;
		DFB_Max_Size[2] = 21000;
		DFB_Max_Size[3] = 7000;
		DFB_Max_Size[4] = 2048;
		DFB_Max_Size[5] = 2048;


		DFB_Offset_Index = 1;

		if (DFB_Index > 3) DFB_Offset_Index = 3;

		Display_Found_ID = 0;
		Number_Of_DFTs = 0;

		while (Display_Found_ID == 0)
		{
			Number_Of_Displays = DFB_Names[DFB_Index, DFB_Offset_Index] & 0x000F;

			if ((Number_Of_Displays == 15) || (Number_Of_DFTs > 14) || (DFB_Offset_Index > DFB_Max_Size[DFB_Index]))
			{
				Display_Found_ID = 1;// TODO wa??
			}
			else
			{
				//DFT_Length = DFB_Names[DFB_Index, DFB_Offset_Index];
				DFT_Length = DFB_Names[DFB_Index, DFB_Offset_Index + 2];

				if (DFT_Length < 0)
				{
					Display_Found_ID = -1;
				}

				for (Index_J = 1; (Index_J <= Number_Of_Displays) && (Display_Found_ID == -1); Index_J++)
				{
					Bit_Value = DFB_Names[DFB_Index, DFB_Offset_Index + 4 + J_Index];

					DFT_MF = (Bit_Value & 0xC000) >> 14;

					DFT_Display = Bit_Value & 0x3FFF;

					if ((DFT_Display == Display_Request_Number) && ((DFT_MF == 0) || (DFT_MF == Major_Function_ID)))
					{
						Display_Found_ID = DFB_Offset_Index;
					}
				}

				if (Display_Found_ID == 0)
				{
					DFB_Offset_Index = DFB_Offset_Index + DFT_Length;// TODO wa???

					Number_Of_DFTs = Number_Of_DFTs + 1;
				}
			}
		}*/
		return;
	}

	void UserInterfaceControl::DEU_Find( void )
	{
		// TODO wrong condition?
		//if ((DMCVL_D_LVLN == 2) && (ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) == 0))
		if ((DMCVL_D_LVLN == 1) && (ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) == 0))
		{
			DMC_SDEU = 1;
			DMC_EDEU = 4;
		}
		else
		{
			DMC_SDEU = ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX );
			DMC_EDEU = ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX );
		}

		for (int i = DMC_SDEU; i <= DMC_EDEU; i++)
		{
			SCP_MAT mat;
			ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, i, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

			//if (mat.CDMV_MAT_MF == Major_Function_ID)
			{
				//Valid_DEU = DMC_K;
			}
		}

		return;
	}

	void UserInterfaceControl::no_name( void )
	{
		DEU_Find();

		if (DMCVL_D_LVLN < 3)
		{
			//KVT_Clear();
		}

		if (DMC_REC_IN_PROGRESS != 0)
		{
			//DFB_Buffer_Number = 1;
			//DFB_Number = 1;

			//DFB_Search();

			//if (DMC_FOUND > 0)
			//{
				Display_Processor();
			//}
			//else
			//{
				//FMPT_Error_ID = 40;
				//Display_Request_Status = 7;
			//}
		}
		else
		{
			//DFB_Number = 0;

			//for (int DFB_Index = 1; (DFB_Index <= 5) && (DFB_Number == 0); DFB_Index++)
			//{
			//	if (((DMC_AMTVALID == 0) && ((DFB_Index == 2) || (DFB_Index == 3))) || ((DFB_Index > 3) && (Display_Buffer_Allocation_Indication[DFB_Index - 3]/*CZ2V_RBUF_P I600.02*/ != 0)))
			//	{
			//		DMC_FOUND = -1;
			//	}
			//	else
			//	{
			//		DFB_Search();
			//	}

			//	if (DMC_FOUND > 0)
			//	{
			//		DFB_Number = DFB_Index;
			//	}
			//}

			//if (DFB_Number > 0)
			//{
				Display_Processor();
			//}
			//else
			//{
			//	DMMD_Display_Processor();
			//}
		}

		return;
	}

	void UserInterfaceControl::DFB_Search( const unsigned short disp )
	{
		// HACK simplified version to verify DISP is legal
		DMC_FOUND = 0;

		for (const auto& x : pGPC->vDFB)
		{
			if (disp == x)
			{
				DMC_FOUND = 1;
				break;
			}
		}
		return;
	}

	void UserInterfaceControl::Display_Processor( void )
	{
		if (DMCVL_D_LVLN < 3)
		{
			SCP_MACT CZ1V_D_MACT;
			ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
			CZ1V_D_MACT.CZ1V_D_DISP = DMCVL_D_DISP;
			WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		}

		//Bits 1 To 2 Of Bit_Value = Major_Function_ID Bits;
		//3 To 16 Of Bit_Value = DMCVL_D_DISP;

		for (DMC_K = DMC_SDEU; DMC_K <= DMC_EDEU; DMC_K++)
		{
			SCP_MAT mat;
			ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, DMC_K, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

			if (mat.CDMV_MAT_MF == DMC_MFI)
			{
				// WAIT FOR NOT Cyclic_In_Process_Event

				//DFB_Number_For_Processing_Display = DFB_Number;

				mat.CDMV_MAT_DISP_NUMBER[DMCVL_D_LVLN - 1] = DMCVL_D_DISP;

				//Processing_Display_DFB_Index[DMC_K;DMCVL_D_LVLN] = DFB_Offset_Index;

				//mat.CDMB_MAT_CRT_STAT |= 0x0000;// TODO which flag????
				//SET CRT_Status_Flags[DMC_K] = 1;// Enabled

				WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, DMC_K, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

				// TODO wrong condition?
				oapiWriteLogV( "(SSV_OV) [DEBUG] DMC_MFI=%d  DMC_K=%d  DMCVL_D_LVLN=%d  DMCVL_D_DISP=%d  mat.CDMV_MAT_LEVEL=%d", DMC_MFI, DMC_K, DMCVL_D_LVLN, DMCVL_D_DISP, mat.CDMV_MAT_LEVEL );
				if (((DMCVL_D_LVLN == mat.CDMV_MAT_LEVEL) || (mat.CDMV_MAT_LEVEL == 0)) && ((mat.CDMB_MAT_CRT_STAT & 0xC000) == 0)/*Disabled*/)
				//if ((mat.CDMB_MAT_CRT_STAT & 0xC000) == 0)/*Disabled*/
				//if ((DMCVL_D_LVLN == mat.CDMV_MAT_LEVEL) && ((mat.CDMB_MAT_CRT_STAT & 0xC000) == 0)/*Disabled*/)
				{
					New_Display_Call();
				}
			}
		}
		return;
	}

	void UserInterfaceControl::New_Display_Call( void )
	{
		SCP_MAT mat;
		ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, DMC_K, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );
		//mat.CDMV_MAT_LEVEL = 0;// HACK saving level as this needs to happen somewhere
		mat.CDMV_MAT_LEVEL = DMCVL_D_LVLN;
		WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, DMC_K, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );

		WriteCOMPOOL_IS( SCP_DMC_STATUS, 0 );

		//Keyboard_Verification_Table_Data[DMC_K] = 0x0000;

		WriteCOMPOOL_IS( SCP_DMC_DIT_INDEX, DMC_K );

		pGPC->pCRT_Interface->DMC_NEW_DISPLAY();

		if (ReadCOMPOOL_IS( SCP_DMC_STATUS ) == 0)
		{
			//Display_Number_With_Major_Function_Setting[DMC_K] = Bit_Value;

			//ICC_Status_Flags[3;DMC_K + 6] = 1;// Enabled
			//WriteCOMPOOL_AIS( SCP_CZ2B_ICC_FLAG, 3, ReadCOMPOOL_AIS( SCP_CZ2B_ICC_FLAG, 3, 3 ) | 0x0400 TODO, 3 );

			/*if (DMCVL_D_LVLN != 3)
			{
				DFT_Length = Display_Buffer_Name[DFB_Number;DFB_Offset_Index + 2];

				Display_Found_ID = DFT_Length + DFB_Offset_Index;

				Keyboard_Verification_Table_Data[DMC_K] = Display_Buffer_Name[DFB_Offset_Index;Display_Found_ID];

				Scalar_Limits_Offset[DMC_K] = Display_Buffer_Name[DFB_Offset_Index;Display_Found_ID + 1] + DFB_Offset_Index;

				General_Limits_Offset[DMC_K] = Display_Buffer_Name[DFB_Offset_Index;Display_Found_ID + 2) + DFB_Offset_Index;

				Item_Start_Offset = Display_Found_ID + 3;
			}*/
		}
		else
		{
			//FMPT_Error_ID = 5;
		}
		return;
	}


	void UserInterfaceControl::DM1_KEYBOARD( void )
	{
		for (int i/*DMC_DIT_INDEX*/ = 1; i/*DMC_DIT_INDEX*/ <= 4; i/*DMC_DIT_INDEX*/++)
		{
			if (ReadCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY ) & 0x1000 >> (i/*DMC_DIT_INDEX*/ - 1))
			{
				WriteCOMPOOL_IS( SCP_DMC_DIT_INDEX, i );// HACK easier loop

				SCP_DIT dit;
				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, i/*DMC_DIT_INDEX*/, &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );
				unsigned short key1 = dit.CZ1V_D_DIT_KYBD_MSG[0];
				if (((key1 >= DEU_GPC_KEY_CODE_SYSSUMM) && (key1 <= DEU_GPC_KEY_CODE_EXEC)) || (key1 == DEU_GPC_KEY_CODE_MFSWITCH))// is first key valid
				{
					//DMC_MF/*MCDS_Major_Function*/ = ((dit.CZ1B_D_DIT_MSG_HEADR & 0x00C0) >> 6)/*DEU_MF_Switch_Setting*//*J060.11*/ + 1;
					DMC_CASE = key1;
					DMC_FUNCTIONS();
				}
				else
				{
					// TODO error
				}
			}
		}
		return;
	}

	void UserInterfaceControl::DM9_ITEM( void )
	{
		SCP_DIT dit;
		ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );

		if (dit.CZ1V_D_NUMOFKEYS < 3)// is number of keystrokes valid?
		{
			SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
			return;
		}

		// bypass if DISP is up
		SCP_MAT mat;
		ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );
		if (mat.CDMV_MAT_LEVEL == 3)
		{
			SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
			return;
		}

		SCP_MACT CZ1V_D_MACT;
		ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 1;
		WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return;
	}

	void UserInterfaceControl::DIR_IORESET( void )
	{
		// reset all commfault words
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_0, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_1, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_2, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_3, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_4, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_5, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_6, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_7, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_8, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_9, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_10, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_0, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_1, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_2, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_3, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_4, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_5, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_6, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_7, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_8, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_9, 0 );
		WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_10, 0 );
		return;
	}



	void UserInterfaceControl::DMC_SEQ_REQ_PROC( unsigned short DMC_TYPE/*Action_Type*/ )
	{
		this->DMC_TYPE = DMC_TYPE;

		if (DMC_TYPE == 0)// Control segment terminated
		{
			Termination_Processor();
		}
		else
		{
			if (DMC_TYPE == 2)
			{
				Secondary_Reconfiguration_Processor();
			}
			else
			{
				if (DMC_TYPE == 1)// reconfiguration complete
				{
					Reconfiguration_Complete_Processor();
				}
				else
				{
					Keyboard_Processor();
				}

				SCP_REQBLK DMCV_REQBLK;
				ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

				if ((DMC_REC_IN_PROGRESS != 0) || (DMCV_REQBLK.DMCV_RQPROC_TY == 1))
				{
					// TODO error DU028
					SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
				}
				else
				{
					if (DMC_TVAL1 == 17)// OPS
					{
						DMC_CUR_OP = DMCV_REQBLK.DMCV_RQOSNBR;// current active OPS

						if (DMC_REQOSNBR == 0)
						{
							OPS_Zero_Processor();
						}
						else
						{
							OPS_Non_Zero_Processor();
						}
					}
					else
					{
						SPEC_Validity_Processor();

						if (DMC_PROCTYPE != 0)
						{
							SPEC_Processor();
						}
					}
				}
			}
		}
		return;
	}

	void UserInterfaceControl::Termination_Processor( void )
	{
		//DMC_MFI = MCDS_Major_Function/*DMC_MF L192*/;

		//DMC_PROCTYPE[DMC_MFI];// TODO what???

		DMC_TERMI = 0;

		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

		for (DMC_TINDX = 1; (DMC_TINDX <= 5) && (DMC_TERMI == 0); DMC_TINDX++)
		{
			if (DMCV_REQBLK.DMCV_RQMACT_IN[DMC_TINDX - 1] == DMC_MACT_INDEX)
			{
				DMC_TERMI = DMC_TINDX;

				DMCV_REQBLK.DMCV_RQWTC = DMCV_REQBLK.DMCV_RQWTC - 1;

				DMCV_REQBLK.DMCV_RQMACT_IN[DMC_TINDX - 1] = 0;
				WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

				if (DMC_TERMI > 1)// SPEC
				{
					WriteCOMPOOL_IS( SCP_DMC_DIT_INDEX, DMC_TERMI - 1 );

					if (DMC_MACT_INDEX == 1)
					{
						DMCV_DEU_MACT[DMC_SZFMACT - 1] = 0;

						DMC_SZFMACT = 0;
					}
					else
					{
						DMCV_DEU_MACT[DMC_MACT_INDEX - 1] = 0;
					}
				}
			}
		}

		if (DMC_PROCTYPE == 1)// OPS transition
		{
			if (DMCV_REQBLK.DMCV_RQWTC == 0)
			{
				DMC_AMT_I = DMCV_REQBLK.DMCV_RQAMT_IN;

				DMC_MACT_I = DMCV_REQBLK.DMCV_XXMACT_I;

				Control_Segment_Scheduler();

				if (DMC_REC_IN_PROGRESS != 0)
				{
					Sequence_Reconfiguration_Processor();
				}
			}
		}
		else
		{
			if (DMC_TERMI == 1)// OPS terminated
			{
				DMC_AMT_I = 0;
				DMC_REQOSNBR = 0;

				DMC_MACT_I = 1;
				DMC_REQMODE = 1;

				Control_Segment_Terminator();

				ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
				if (DMCV_REQBLK.DMCV_RQWTC == 0)
				{
					Control_Segment_Scheduler();
				}
			}
			else
			{
				DMC_REQOSNBR = DMC_SPECID[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1];

				if (DMC_REQOSNBR != 500)
				{
					DMC_AMT_I = DMC_AINXTS[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1];

					DMC_MACT_I = DMC_MINXTS[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1];

					DMC_REQMODE = -1;

					Control_Segment_Scheduler();
				}
				else
				{
					DMCVL_D_LVLN = 1;

					DMC_MACT_INDEX = DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1];

					SCP_MACT CZ1V_D_MACT;
					ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
					DMCVL_D_DISP = CZ1V_D_MACT.CZ1V_D_DISP;

					DMC_DISPLAY();
				}
			}
		}
		return;
	}

	void UserInterfaceControl::Secondary_Reconfiguration_Processor( void )
	{
		return;
	}

	void UserInterfaceControl::Reconfiguration_Complete_Processor( void )
	{
		DMC_REC_IN_PROGRESS = 0;// not in progress

		DMC_REC_IP2 = 0;// not in initialization

		DMC_TVAL1 = ReadCOMPOOL_IS( SCP_CZ2V_REC_XERR );

		DMC_REQOSNBR = ReadCOMPOOL_IS( SCP_CZ2V_REC_OPS );

		if (DMC_TVAL1 >= 100)// Reconfiguration with overlay
		{
			if (DMC_TVAL1 == 101)// error
			{
				DMC_AMTVALID = 0;// AMT is not valid

				DMC_TVAL1 = 1;
			}
			else
			{
				DMC_AMTVALID = 1;// AMT is valid

				DMC_TVAL1 = 0;
			}
		}

		//System_Spec_ID(1) = -1;// remove SPEC 02 from legal system SPECs

		/*if (DMC_REQOSNBR == 2)
		{
			DMC_OZPAGE_VAL = 0;// OPS 0-00 page not valid
		}
		else
		{
			DMC_OZPAGE_VAL = 1;
		}*/

		Buffer_Address_Mover();

		if (DMC_TVAL1 == 0)// successful reconfiguration
		{
			//if (DMC_OZPAGE_VAL != 0)// OPS 0-00 page valid
			{
				//Display_Buffer_Name(1,6) = 0x3FFF;// remove blank OPS 0-00 page from DFB 1

				DMC_MACT_INDEX = 1;
				DMCVL_D_LVLN = 1;
				DMCVL_D_DISP = 1;

				//for (MF = 1:3)
				{
					WriteCOMPOOL_IS( SCP_DMC_DIT_INDEX, 0 );

					DMC_DISPLAY();
				}
			}

			DMC_TVAL1 = 17;// OPS

			DMC_REQMODE = ReadCOMPOOL_IS( SCP_CZ2V_REC_MODE );
		}
		else
		{
			DMC_TVAL1 = 18;// SPEC

			DMC_REQOSNBR = 0;// SPEC 00
		}

		/*DEU_Number = Reconfiguration_DEU_Source;

		MCDS_Major_Function = ReadCOMPOOL_IS( SCP_CZ2V_REC_MF );*/
		return;
	}

	void UserInterfaceControl::Keyboard_Processor( void )
	{
		SCP_DIT dit;
		ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );

		DMC_GPCZ = dit.CZ1V_D_NUMOFKEYS;

		DMC_TVAL1 = dit.CZ1V_D_DIT_KYBD_MSG[1 - 1];

		DMC_REQOSNBR = dit.CZ1V_D_DIT_KYBD_MSG[2 - 1];

		DMC_UNDX = dit.CZ1V_D_DIT_KYBD_MSG[3 - 1];

		if (DMC_TVAL1 == 17)
		{
			DMC_REQMODE = (DMC_UNDX * 10) + dit.CZ1V_D_DIT_KYBD_MSG[4 - 1];// mode number
		}
		else
		{
			//DMC_REQOSNBR = (DMC_REQOSNBR * 10) + DMC_UNDX;// SPEC id
			// HACK updated to allow 1-, 2- and 3-digit SPECs
			if (DMC_GPCZ == 4)
			{
				DMC_REQOSNBR = (DMC_REQOSNBR * 10) + DMC_UNDX;
			}
			else if (DMC_GPCZ == 5)
			{
				DMC_REQOSNBR = (DMC_REQOSNBR * 100) + (DMC_UNDX * 10) + dit.CZ1V_D_DIT_KYBD_MSG[4 - 1];
			}
		}
		return;
	}

	void UserInterfaceControl::OPS_Zero_Processor( void )
	{
		if (DMC_REQMODE == 0)
		{
			DMC_AMT_I = 0;

			DMC_MACT_I = 1;
			DMC_REQMODE = 1;

			if (DMC_GPCZ > 5)// GPC OPS 0-00 request
			{
				if (DMC_INITIAL == 0)
				{
					DMC_SZFMACT = 0;

					Buffer_Address_Mover();

					Control_Segment_Scheduler();
				}
				else
				{
					Control_Segment_Terminator();

					SCP_REQBLK DMCV_REQBLK;
					ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
					if (DMCV_REQBLK.DMCV_RQWTC == 0)
					{
						Control_Segment_Scheduler();
					}
				}
			}
			else
			{
				if (DMC_CUR_OP == 0)
				{
					Mode_To_Mode_Processor();
				}
				else
				{
					Control_Segment_Terminator();
				}
			}

			DMC_CUR_OP = DMC_REQOSNBR;// HACK update DMC_CUR_OP following OPS change
		}
		else
		{
			// TODO error OT010
			SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
		}
		return;
	}

	void UserInterfaceControl::OPS_Non_Zero_Processor( void )
	{
		if (DMC_REQMODE != 0)
		{
			if (DMC_CUR_OP == DMC_REQOSNBR)
			{
				// mode-to-mode
				SCP_REQBLK DMCV_REQBLK;
				ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

				DMC_MACT_I = DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1];// OPS MACT

				DMC_AMT_I = DMCV_REQBLK.DMCV_RQAMT_IN;

				SCP_OPS CDAV_OPS;
				ReadCOMPOOL_ASTRUCT( SCP_CDAV_OPS, DMC_AMT_I, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
				if (DMC_REQMODE <= CDAV_OPS.CDAV_OP_NMODES)
				{
					Mode_To_Mode_Processor();
				}
				else
				{
					// TODO error OT010
					SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
				}

			}
			else
			{
				// new OPS
				DMC_MACT_I = 2;

				AMT_GRT_Search_Processor();

				if (DMC_PROCTYPE == 1)// OPS transition no reconfiguration
				{
					Control_Segment_Terminator();

					SCP_REQBLK DMCV_REQBLK;
					ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
					if (DMCV_REQBLK.DMCV_RQWTC == 0)
					{
						Control_Segment_Scheduler();
					}

					DMC_CUR_OP = DMC_REQOSNBR;// HACK update DMC_CUR_OP following OPS change
				}
				else
				{
					if (DMC_PROCTYPE == 7)// reconfiguration required
					{
						WriteCOMPOOL_IS( SCP_CZ2V_REC_DEU, ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );

						WriteCOMPOOL_IS( SCP_CZ2V_REC_OPS, DMC_REQOSNBR );

						WriteCOMPOOL_IS( SCP_CZ2V_REC_MODE, DMC_REQMODE );

						WriteCOMPOOL_IS( SCP_CZ2V_REC_GRT_INDEX, DMC_GRTIX );

						WriteCOMPOOL_IS( SCP_CZ2V_REC_MF, DMC_MFI );
						DMC_REC_IN_PROGRESS = DMC_MFI;
						DMC_REC_IP2 = DMC_MFI;

						Sequence_Reconfiguration_Pre_Processor();

						Sequence_Reconfiguration_Processor();
					}
				}
			}
		}
		else
		{
			// TODO error OT010
			SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
		}
		return;
	}

	void UserInterfaceControl::SPEC_Validity_Processor( void )
	{
		DMC_REQMODE = -1;// SPEC

		DMC_TINDX = 3;// SPEC MACT Copy to Test

		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMC_MACT_I = DMCV_REQBLK.DMCV_RQMACT_IN[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) + 1 - 1];// MACT for SPEC on DEU Number 1

		for (int I = DMC_TINDX; (I <= (DMC_TINDX + 1)) && (DMC_MACT_I == 0); I++)
		{
			if (DMCV_DEU_MACT[I - 1] == 0)// MACT not being used
			{
				DMC_MACT_I = I + 100;
			}
		}

		if (DMC_MACT_I == 0)// SPECs active
		{
			// TODO error DU026
			DMC_PROCTYPE = 0;
			SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
		}
		else
		{
			if (DMC_REQOSNBR == 0)
			{
				DMC_AMT_I = 0;// SPEC 00
				// HACK added result
				DMC_PROCTYPE = 6;
			}
			else
			{
				DMC_AMT_I = -1;

				for (DMC_TINDX = 1; DMC_TINDX <= 2; DMC_TINDX++)
				{
					if (DMCV_SYS_ID[DMC_TINDX - 1] == DMC_REQOSNBR)
					{
						DMC_AMT_I = DMC_TINDX;

						//DMC_TVAL1 = 1;// start of active search loop

						//DMC_TVAL_4 = 3;// end of active earch loop
					}
				}

				// HACK changed logic below to allow system SPECs in OPS 0
				if ((DMC_AMT_I == -1) && (DMC_CUR_OP != 0))// not a system spec and not OPS 0-00
				{
					SPEC_Search_OPS_Type();
				}

				if (DMC_AMT_I >= 0)
				{
					SPEC_Active_Search();

					if (DMC_AMT_I == -1)// This SPEC is active
					{
						// TODO error DU007
						DMC_PROCTYPE = 0;
						SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
					}
					else
					{
						// HACK changed assignment below from 26 to 6 (Cancel Old SPEC & Start New SPEC)
						DMC_PROCTYPE = 6;// SPEC legal
					}
				}
				else
				{
					// TODO error DU012
					DMC_PROCTYPE = 0;
					SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
				}
			}
		}
		return;
	}

	void UserInterfaceControl::SPEC_Search_OPS_Type( void )
	{
		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMC_TVAL_3 = DMCV_REQBLK.DMCV_RQAMT_IN;

		SCP_OPS CDAV_OPS;
		ReadCOMPOOL_ASTRUCT( SCP_CDAV_OPS, DMC_TVAL_3, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
		DMC_TVAL = CDAV_OPS.CDAV_OP_SPEC_ST;// loop start value

		DMC_TVAL_2 = DMC_SEQVAL + CDAV_OPS.CDAV_OP_NSPEC + 1;// loop end value

		for (DMC_TINDX = DMC_TVAL; (DMC_TINDX <= DMC_TVAL_2) && (DMC_AMT_I == -1); DMC_TINDX++)
		{
			SCP_SPEC CDAV_SPEC;
			ReadCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, DMC_TINDX, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			if (CDAV_SPEC.CDAV_SP_ID == DMC_REQOSNBR)
			{
				DMC_AMT_I = DMC_TINDX + 100;// AMT for OPS/SPEC

				//DMC_TVAL1 = DMC_MFI;// start of active search loop
				//DMC_TVAL_4 = DMC_MFI;// end of active search loop
			}
		}
		return;
	}

	void UserInterfaceControl::SPEC_Active_Search( void )
	{
		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		for (unsigned short J = 2; J <= 5; J++)// loop thru SPEC's MACTs
		{
			DMC_TVAL_3 = DMCV_REQBLK.DMCV_RQMACT_IN[J - 1];

			if (DMC_TVAL_3 != 0)// MACT has a SPEC active
			{
				SCP_MACT CZ1V_D_MACT;
				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_TVAL_3, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

				if (CZ1V_D_MACT.CZ1V_D_OPS == DMC_REQOSNBR)
				{
					DMC_AMT_I = -1;// this SPEC active
				}
			}
		}
		return;
	}

	void UserInterfaceControl::SPEC_Processor( void )
	{
		if (DMC_MACT_I < 100)// this DEU is active with another SPEC
		{
			if (DMC_MACT_I == 1)// the other SPEC is SPEC 00
			{
				DMC_MACT_I = DMC_SZFMACT;

				DMCV_DEU_MACT[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] = 0;
				DMC_SZFMACT = 0;

				Control_Segment_Scheduler();
			}
			else
			{
				DMC_MINXTS[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] = DMC_MACT_I;

				DMC_AINXTS[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] = DMC_AMT_I;

				DMC_SPECID[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] = DMC_REQOSNBR;

				SCP_MACT CZ1V_D_MACT;
				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x8000;// block termination request
				CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// mode termination request
				CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x2000;// control segment termination request
				CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 1;
				WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
			}
		}
		else
		{
			DMC_MACT_I = DMC_MACT_I - 100;

			Control_Segment_Scheduler();
		}
		return;
	}

	void UserInterfaceControl::Control_Segment_Scheduler( void )
	{
		DMC_SEQVAL = DMC_AMT_I;

		DMC_PROCTYPE = 3;// schedule

		DMCVL_D_DISP = 1;

		DMCVL_D_LVLN = 0;

		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMC_WTCT = DMCV_REQBLK.DMCV_RQWTC;

		if (DMC_REQMODE == -1)// SPEC
		{
			SPEC_Control_Processor();
		}
		else
		{
			OPS_Control_Processor();
		}

		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMCV_REQBLK.DMCV_RQWTC = DMC_WTCT;
		WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

		for (DMC_TINDX = DMC_TVAL; DMC_TINDX <= DMC_TVAL1; DMC_TINDX++)// loop thru all DEU's if OPS and 1 DEU for SPECs
		{
			SCP_MAT mat;
			ReadCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, DMC_TINDX, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );
			// HACK skip this check as only one MF runs in each GPC
			//if (mat.CDMV_MAT_MF == DMC_MFI)
			{
				mat.CDMV_MAT_LEVEL = 0;

				// clear SPEC and DISP displays
				mat.CDMV_MAT_DISP_NUMBER[2 - 1] = 0;
				mat.CDMV_MAT_DISP_NUMBER[3 - 1] = 0;
				WriteCOMPOOL_ASTRUCT( SCP_CDMV_MAT_TABLE, DMC_TINDX, &mat, sizes_MAT, pos_MAT, cnt_MAT, 4 );
			}
		}

		//CDMV_MACT_INDEX = DMC_MACT_I;
		WriteCOMPOOL_IS( SCP_CZ1V_D_MACT_INDEX, DMC_MACT_I );
		DMC_MACT_INDEX = DMC_MACT_I;

		if (DMCVL_D_LVLN != 0)
		{
			DMC_DISPLAY();
		}
		else
		{
			//Keyboard_Input_DEU_Number = ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX );

			SCP_MACT CZ1V_D_MACT;
			ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
			CZ1V_D_MACT.CZ1V_D_SEQUENCE_INFO = DMC_SEQVAL;
			CZ1V_D_MACT.CZ1V_D_NEW_OPS = DMC_REQOSNBR;
			CZ1V_D_MACT.CZ1V_D_NEW_MOD = DMC_REQMODE;
			WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

			//MACT_Index_Event = 0;

			pGPC->SCHEDULE( DMC_PROG_NAME );// Schedule OPS/SPEC Control Segment
		}
		return;
	}

	void UserInterfaceControl::SPEC_Control_Processor( void )
	{
		DMCV_DEU_MACT[DMC_MACT_I - 1] = ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX );
		DMC_TVAL = ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX );
		DMC_TVAL1 = ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX );

		if (DMC_REQOSNBR == 0)
		{
			DMCVL_D_LVLN = 2;// Display Only

			DMC_SZFMACT = DMC_MACT_I;

			DMC_MACT_I = 1;
		}
		else
		{
			if (DMC_AMT_I > 100)// An OPS SPEC
			{
				DMC_AMT_I = DMC_AMT_I - 100;

				SCP_SPEC CDAV_SPEC;
				ReadCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, DMC_AMT_I, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
				DMC_SEQVAL = CDAV_SPEC.CDAV_SP_BLOCKS;// Number Blocks This SPEC

				SCP_SPNAME CDAV_SPNAME;
				ReadCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, DMC_AMT_I, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
				DMC_PROG_NAME = CDAV_SPNAME.CDAV_SP_SPECNM;
			}
			else
			{
				DMC_SEQVAL = DMCV_SYS_BLOCKS[DMC_AMT_I - 1];

				DMC_PROG_NAME = DMCV_SYS_SPNAME[DMC_AMT_I - 1];
			}
		}

		DMC_WTCT = DMC_WTCT + 1;

		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMCV_REQBLK.DMCV_RQMACT_IN[1 + ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] = DMC_MACT_I;
		WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

		DMC_SPECID[ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) - 1] = 500;// Make Next SPEC Not Waiting To Be Scheduled
		return;
	}

	void UserInterfaceControl::OPS_Control_Processor( void )
	{
		DMC_TVAL = 1;// start of loop for setting DEU levels to zero

		DMC_TVAL1 = 4;// end of loop for setting DEU levels to zero

		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMCV_REQBLK.DMCV_RQMACT_IN[1 - 1] = DMC_MACT_I;

		DMCV_REQBLK.DMCV_RQPROC_TY = 3;// schedule
		WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

		DMC_REQOSNBR = DMCV_REQBLK.DMCV_RQOSNBR;

		if (DMC_REQOSNBR != DMC_SAVE)
		{
			//Current_OPS/*SCP_GST.CZ2V_CURRENT_OPS*/[DMC_MFI] = DMC_REQOSNBR;// TODO

			WriteCOMPOOL_AIS( SCP_CZ2B_ICC_FLAG, 1, ReadCOMPOOL_AIS( SCP_CZ2B_ICC_FLAG, 1, 3 ) | 0x0400, 3 );// ICC data
		}

		if (DMC_AMT_I == 0)// OPS 0-00
		{
			if (DMC_INITIAL == 0)// must schedule OPS 0-00
			{
				DMC_PROG_NAME = "ARB_IDLE_OPS";

				DMC_INITIAL = 1;
			}
			else
			{
				DMCVL_D_LVLN = 1;

				WriteCOMPOOL_IS( SCP_DMC_DIT_INDEX, 0 );// update all DEU's for this major function

				if (DMC_SAVE != 0)
				{
					/*SVC OPSCANCL;// 110

					if ((Active_Control_Segment_MACT_Index[all MFs] == 1) && (Redundant_Set_Mask[GPC_ID] != 0x0000))// are in a redundant set
					{
						Last_MF[1] = -1;
						Last_MF[2] = -1;
						Last_MF[3] = -1;
						Last_MF[4] = -1;

						WAIT 0.6;

						Redundant_Set_Mask[GPC_ID] = 0x0000;

						WriteCOMPOOL_AIS( SCP_CZ2B_ICC_FLAG, 1, ReadCOMPOOL_AIS( SCP_CZ2B_ICC_FLAG, 1, 3 ) | 0x0100, 3 );// ICC data

						SVC SMR;// 390
					}*/
				}

				DMC_WTCT = DMC_WTCT + 1;
			}
		}
		else
		{
			DMC_WTCT = DMC_WTCT + 1;

			//OPS_Transition_Parameters = Update_OPS_Transition_Parameters;

			SCP_OPNAME CDAV_OPNAME;
			ReadCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, DMC_AMT_I, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
			DMC_PROG_NAME = CDAV_OPNAME.CDAV_OP_PROGNM;
		}
		return;
	}

	void UserInterfaceControl::Control_Segment_Terminator( void )
	{
		//DMC_NRQBLK = Name Control_Segment_Request_Block[DMC_MFI];// TODO

		SCP_REQBLK DMCV_REQBLK;
		ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		DMC_SAVE = DMCV_REQBLK.DMCV_RQOSNBR;

		// OPS transition
		DMCV_REQBLK.DMCV_RQPROC_TY = 1;
		DMC_PROCTYPE = 1;

		DMCV_REQBLK.DMCV_XXMACT_I = DMC_MACT_I;

		DMCV_REQBLK.DMCV_RQAMT_IN = DMC_AMT_I;

		DMCV_REQBLK.DMCV_RQMODE = DMC_REQMODE;

		DMCV_REQBLK.DMCV_RQOSNBR = DMC_REQOSNBR;

		DMC_WTCT = 0;

		for (unsigned short DMC_UNDX = 1; DMC_UNDX <= 5; DMC_UNDX++)
		{
			DMC_TINDX = DMCV_REQBLK.DMCV_RQMACT_IN[DMC_UNDX - 1];

			if (DMC_TINDX != 0)// control segment active
			{
				SCP_MACT CZ1V_D_MACT;
				ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_TINDX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
				CZ1V_D_MACT.CZ1V_D_NEW_OPS = DMC_REQOSNBR;
				CZ1V_D_MACT.CZ1V_D_NEW_MOD = DMC_REQMODE;

				if (DMC_TINDX == 1)// OPS/SPEC 0
				{
					if (DMC_UNDX > 1)// SPEC 00
					{
						DMCV_DEU_MACT[DMC_SZFMACT - 1] = 0;

						DMC_SZFMACT = 0;

						DMCV_REQBLK.DMCV_RQMACT_IN[DMC_UNDX - 1] = 0;
					}
				}
				else
				{
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x8000;// block termination request
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// mode termination request
					CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x2000;// control segment termination request
					CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 1;

					DMC_WTCT = DMC_WTCT + 1;
				}

				WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_TINDX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
			}
		}

		DMCV_REQBLK.DMCV_RQWTC = DMC_WTCT;
		WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
		return;
	}

	void UserInterfaceControl::Sequence_Reconfiguration_Pre_Processor( void )
	{
		//Display_Buffer_Name(1,6) = 0x0001;// load blank OPS-000 Page_ID Into DFT 1 of DFB 1

		DMC_MACT_I = 1;// OPS 0-00 MACT

		DMC_AMT_I = 0;// OPS 0-00 AMT

		//for (MF = 1:3)
		{
			//if ((DMC_MFI != DMC_REC_IN_PROGRESS) || (Memory_Source == 0/*access from MMU*/))
			{
				//DMC_REQOSNBR = 0;// tell active control segment it's going to OPS 0-00

				//DMC_REQMODE = 1;
			}
			//else
			{
				DMC_REQOSNBR = ReadCOMPOOL_IS( SCP_CZ2V_REC_OPS );// tell active control segment it's going to requested OPS

				DMC_REQMODE = ReadCOMPOOL_IS( SCP_CZ2V_REC_MODE );
			}

			Control_Segment_Terminator();

			SCP_REQBLK DMCV_REQBLK;
			ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
			DMCV_REQBLK.DMCV_RQOSNBR = 0;// always go to OPS 0-00 first

			DMCV_REQBLK.DMCV_RQMODE = 1;

			//DMCV_REQBLK.DMCV_RQWTC = 0;// HACK assume all control segments will finish in the next timestep
			WriteCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );

			if (DMC_MFI == DMC_REC_IN_PROGRESS)
			{
				DMC_SAVE = 0;// so Control_Segment_Scheduler will not break redundant set when going to OPS 0-00
			}

			if (DMCV_REQBLK.DMCV_RQWTC == 0)// all control segments terminated
			{
				Control_Segment_Scheduler();
			}
		}
		return;
	}

	void UserInterfaceControl::Sequence_Reconfiguration_Processor( void )
	{
		DMC_TVAL_3 = 1;// HACK was 3

		//for (DMC_TINDX = 1:3)
		{
			SCP_REQBLK DMCV_REQBLK;
			ReadCOMPOOL_STRUCT( SCP_DMCV_REQBLK, &DMCV_REQBLK, sizes_REQBLK, pos_REQBLK, cnt_REQBLK );
			if ((DMCV_REQBLK.DMCV_RQMACT_IN[0] == 1) && (DMCV_REQBLK.DMCV_RQMACT_IN[1] == 0) && (DMCV_REQBLK.DMCV_RQMACT_IN[2] == 0) && (DMCV_REQBLK.DMCV_RQMACT_IN[3] == 0) && (DMCV_REQBLK.DMCV_RQMACT_IN[4] == 0))// this major function is in OPS0-00 only
			{
				DMC_TVAL_3 = DMC_TVAL_3 - 1;
			}
		}

		if (DMC_TVAL_3 == 0)// all major functions are in OPS 0-00 only
		{
			/*WAIT for NOT (620) not active

			CRT_Status_Flag 2(1 to 3) = 1;// i/o suppressed on all DEUs

			//Downlist_Formatter_Enabled_Flag = 0;// downlist formatter off

			//ICC_GST_Status = 1;// to cause ICC

			//DEU_Poll_Flags = 0x0000;// turn polling off all DEUs
			*/
			if (DMC_REC_IN_PROGRESS < 0)// secondary reconfiguration
			{
				//Sequence_Secondary_ICC_Message(2) = Reconfiguration_Status;

				//Sequence_Secondary_ICC_Message(3) = GPC_ID;

				//while (Sequence_ICC_Message_Status = 0x00)// good status returned
				//{
					//Sequence_Assign_Value = ICC_Message_Collector( Sequence_Secondary_ICC_Message);
				//}
			}
			else
			{
				pGPC->SCHEDULE( "GPC_RECONFIG" );
			}
		}
		return;
	}

	void UserInterfaceControl::AMT_GRT_Search_Processor( void )
	{
		DMC_FOUND = 1;// set no mode error present

		IN_Core_Tester();

		Overlay_Allowed_Tester();

		if (DMC_FOUND != 0)
		{
			if (DMC_GRTIX == 0)// overlay not allowed
			{
				if (DMC_AMT_I != 0)// in core
				{
					DMC_PROCTYPE = 1;// OPS transition no reconfiguration
				}
				else
				{
					// TODO error OT001
					SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
				}
			}
			else
			{
				/*if (Discrete_Bit_Standby == 1)// self in standby
				{
					if ((DMC_AMT_I == 0) || ((DMC_TYPE > 1) && Memory_Source == 0))
					{
						DMC_PROCTYPE = 7;// reconfiguration

						WriteCOMPOOL_IS( SCP_CZ2V_REC_XERR, 3 );// standby reconfiguration
					}
					else
					{
						DMC_PROCTYPE = 1;
					}
				}
				else*/
				{
					/*if (ReadCOMPOOL_AIS( SCP_CZ2V_GRT_GPC_SET, DMC_GRTIX, 10 ) == 0x0000)
					{
						// TODO error OT003
						SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
					}
					else*/
					{
						/*for (int I = 1; I <= 5; I++)
						{
							if ((((ReadCOMPOOL_AIS( SCP_CZ2V_GRT_GPC_SET, DMC_GRTIX, 10 ) >> (16 - I)) & 1) == 1) &&// this GPC required in redundant set
								(Discretes_Bit_Run_Mode == 1))// GPC in run
							{
								Sequence_Run_Bits[I] = 1;// found GPC in run
							}
						}

						if (Sequence_Run_Bits == 0x0000)
						{
							// TODO error OT005
							SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
						}
						else*/
						{
							/*if ((DMC_TYPE > 1) && (Sequence_Run_Bits != GPC_Set))
							{
								// TODO error OT004
								SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
							}*/

							if ((DMC_AMT_I == 0) /*|| (Sequence_Run_Bits != Redundant_Set_Mask) || ((DMC_TYPE > 1) && (Memory_Source == 0))*/)
							{
								DMC_PROCTYPE = 7;// reconfiguration required

								WriteCOMPOOL_IS( SCP_CZ2V_REC_XERR, 0 );// not standby
							}
							else
							{
								DMC_PROCTYPE = 1;// OPS transition no reconfiguration
							}
						}
					}
				}
			}
		}
		else
		{
			// TODO error OT010
			SetIllegalEntry( ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ) );
		}
		return;
	}

	void UserInterfaceControl::IN_Core_Tester( void )
	{
		DMC_AMT_I = 0;

		SCP_MF CDAV_MF;
		ReadCOMPOOL_ASTRUCT( SCP_CDAV_MF, DMC_MFI, &CDAV_MF, sizes_SPEC, pos_SPEC, cnt_SPEC, 3 );

		DMC_TVAL_3 = CDAV_MF.CDAV_MF_FOPS;// start copy for search

		DMC_TVAL_4 = DMC_TVAL_3 + CDAV_MF.CDAV_MF_NOPS - 1;// number of copies to search

		if ((DMC_TVAL_3 > 0) && (DMC_TVAL_4 > 0) && (DMC_AMTVALID != 0))
		{
			for (DMC_TINDX = DMC_TVAL_3; DMC_TINDX <= DMC_TVAL_4; DMC_TINDX++)
			{
				SCP_OPS CDAV_OPS;
				ReadCOMPOOL_ASTRUCT( SCP_CDAV_OPS, DMC_TINDX, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
				if (CDAV_OPS.CDAV_OP_OPSID == DMC_REQOSNBR)
				{
					DMC_AMT_I = DMC_TINDX;

					if (CDAV_OPS.CDAV_OP_NMODES < DMC_REQMODE)
					{
						DMC_FOUND = 0;// mode error
					}
				}
			}
		}
		return;
	}

	void UserInterfaceControl::Overlay_Allowed_Tester( void )
	{
		DMC_GRTIX = 0;

		for (DMC_TVAL_2 = 1; DMC_TVAL_2 <= 10; DMC_TVAL_2++)
		{
			SCP_GRT_TAB CZ2V_GRT_TAB;
			ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GRT_TAB, DMC_TVAL_2, &CZ2V_GRT_TAB, sizes_GRT_TAB, pos_GRT_TAB, cnt_GRT_TAB, 10 );

			if ((CZ2V_GRT_TAB.CZ2V_GRT_MF_VALUE == DMC_MFI) && (CZ2V_GRT_TAB.CZ2V_GRT_OPS_NBR == DMC_REQOSNBR))
			{
				DMC_GRTIX = DMC_TVAL_2;

				if (CZ2V_GRT_TAB.CZ2V_GRT_MAX_MODE < DMC_REQMODE)
				{
					DMC_FOUND = 0;// mode error
				}
			}
		}
		return;
	}

	void UserInterfaceControl::Mode_To_Mode_Processor( void )
	{
		SCP_MACT CZ1V_D_MACT;
		ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		CZ1V_D_MACT.CZ1V_D_NEW_MOD = DMC_REQMODE;
		CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x8000;// request block termination
		CZ1V_D_MACT.CZ1B_D_FLAG2 |= 0x4000;// request mode termination
		CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT = 1;
		WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DMC_MACT_I, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

		DMC_PROCTYPE = 2;// mode to mode transfer
		return;
	}

	void UserInterfaceControl::Buffer_Address_Mover( void )
	{
		//if (DMC_AMTVALID != 0)// valid
		//{
		//	Display_Buffer_Name_Table/*TODO DMC_BUFNAMES L178*/ = AMT_Buffer_Name_Table/*TODO CDAV_BNAME A010*/;

		//	DFB_Name_Structure/*CDMV_B_NAMES B100*/ = AMT_Buffer_Name_Table/*TODO CDAV_BNAME A010*/;
		//}
		return;
	}
}
