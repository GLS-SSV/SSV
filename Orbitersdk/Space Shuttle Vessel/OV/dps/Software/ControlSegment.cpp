#include "ControlSegment.h"


namespace dps
{
	CS_Block::CS_Block( SimpleGPCSystem* pGPC, ControlSegment* pCS, const unsigned short DisplayNumber ):
		pGPC(pGPC), pCS(pCS), DisplayNumber(DisplayNumber), init(false)
	{
		return;
	}

	CS_Block::~CS_Block( void )
	{
		return;
	}

	void CS_Block::Init( void )
	{
		return;
	}

	void CS_Block::Input( void )
	{
		return;
	}

	void CS_Block::CleanUp( void )
	{
		return;
	}

	void CS_Block::Run( void )
	{
		if (!init)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] CS_Block::Init" );
#endif// _DEBUG
			Init();// derived

			init = true;
		}

		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();

		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		if (CZ1V_D_MACT.CZ1E_D_KYBD_MSG_EVT == 1)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] CS_Block::Input" );
#endif// _DEBUG
			// cycle thru key inputs, update "MACRO"s below and then call Input() on each input
			SCP_DIT dit;
			pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, pGPC->ReadCOMPOOL_IS( SCP_DMC_DIT_INDEX ), &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );
			key = dit.CZ1V_D_DIT_KYBD_MSG[0];
			// process item
			if (key == ITEM())
			{
				item_i = 0;
				item_s = 0;

				unsigned short idx = 1;
				item_no = dit.CZ1V_D_DIT_KYBD_MSG[idx++];
				unsigned short k = dit.CZ1V_D_DIT_KYBD_MSG[idx++];
				if (k <= /*DEU_GPC_KEY_CODE_9*/0x09)
				{
					item_no = (item_no * 10) + k;

					// read another so k contains delimiter or exec
					k = dit.CZ1V_D_DIT_KYBD_MSG[idx++];
				}

				// single item, no data
				if (k == /*DEU_GPC_KEY_CODE_EXEC*/0x1E)
				{
					// pass to CS
					Input();// derived
				}
				else
				{
					std::string data = "";
					while ((idx < 40) && (k != /*DEU_GPC_KEY_CODE_EXEC*/0x1E))
					{
						// save delimiter
						if (k == /*DEU_GPC_KEY_CODE_MINUS*/0x15) data = '-';
						else /*if (k == DEU_GPC_KEY_CODE_PLUS 0x16)*/ data = '+';

						// read data until delimiter or exec
						k = dit.CZ1V_D_DIT_KYBD_MSG[idx++];
						while ((idx < 30) && (k != /*DEU_GPC_KEY_CODE_MINUS*/0x15) && (k != /*DEU_GPC_KEY_CODE_PLUS*/0x16) && (k != /*DEU_GPC_KEY_CODE_EXEC*/0x1E))
						{
							// save data
							if (k <= /*DEU_GPC_KEY_CODE_9*/0x09) data += static_cast<char>(k + 48);
							else if (k <= /*DEU_GPC_KEY_CODE_F*/0x0F) data += static_cast<char>(k + 55);
							else if (k == /*DEU_GPC_KEY_CODE_DOT*/0x17) data += ".";

							// read next
							k = dit.CZ1V_D_DIT_KYBD_MSG[idx++];
						}

						if (data.length() > 1)// more than just the delimiter
						{
							// convert to numbers
							item_i = std::stoi( data );
							item_s = std::stod( data );

							// pass to CS
							Input();// derived
						}

						// next item
						item_no++;
					}
				}

				
			}
			else Input();// derived
		}

		DISPLAY( DisplayNumber );

		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		if (CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x8000)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] CS_Block::CleanUp" );
#endif// _DEBUG
			CleanUp();// derived

			DNX_BMS( 3, DIS_MACT_INDEX, pGPC );

			init = false;
		}
		return;
	}

	void CS_Block::DISPLAY( unsigned int display_num )
	{
		DIS_PLAY( display_num, pCS->GetDIS_MACT_INDEX(), pGPC );
		return;
	}

	unsigned short CS_Block::KEY( void ) const
	{
		return key;
	}

	unsigned short CS_Block::ITEM( void ) const
	{
		return /*DEU_GPC_KEY_CODE_ITEM*/0x14;
	}

	unsigned short CS_Block::EXEC( void ) const
	{
		return /*DEU_GPC_KEY_CODE_EXEC*/0x1E;
	}

	unsigned short CS_Block::ITEM_NO( void ) const
	{
		return item_no;
	}

	double CS_Block::ITEM_S( void ) const
	{
		return item_s;
	}

	int CS_Block::ITEM_I( void ) const
	{
		return item_i;
	}

	unsigned short CS_Block::D_OPS_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_OPS;
	}

	unsigned short CS_Block::D_MODE_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_MOD;
	}

	unsigned short CS_Block::D_SPEC_NUMBER( void ) const
	{
		// TODO
		return 0;
	}

	unsigned short CS_Block::D_BLOCK_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_BLK;
	}

	unsigned short CS_Block::D_NEW_OPS_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_NEW_OPS;
	}

	unsigned short CS_Block::D_NEW_MODE_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_NEW_MOD;
	}

	unsigned short CS_Block::D_DEU_NUMBER( void ) const
	{
		// TODO
		return 0;
	}

	////////////////////////////////////////////////////////////////

	CS_Mode::CS_Mode( SimpleGPCSystem* pGPC, ControlSegment* pCS, const unsigned int Advance_Event ):
		pGPC(pGPC), pCS(pCS), Advance_Event(Advance_Event)
	{
		return;
	}

	void CS_Mode::Init( void )
	{
		return;
	}

	void CS_Mode::CleanUp( void )
	{
		return;
	}

	void CS_Mode::Run( void )
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();

		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

		if (CZ1V_D_MACT.CZ1V_D_BLK == 0)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] CS_Mode::Init" );
#endif// _DEBUG
			Init();// derived

			CZ1V_D_MACT.CZ1E_D_MOD_ADV_EVT = Advance_Event;
			CZ1V_D_MACT.CZ1V_D_BLK = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		}

		Blocks[CZ1V_D_MACT.CZ1V_D_BLK - 1]->Run();

		if (CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x4000)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] CS_Mode::CleanUp" );
#endif// _DEBUG
			CleanUp();// derived

			DNX_BMS( 2, DIS_MACT_INDEX, pGPC );
		}
		return;
	}

	unsigned short CS_Mode::D_OPS_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_OPS;
	}

	unsigned short CS_Mode::D_MODE_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_MOD;
	}

	unsigned short CS_Mode::D_SPEC_NUMBER( void ) const
	{
		// TODO
		return 0;
	}

	unsigned short CS_Mode::D_NEW_OPS_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_NEW_OPS;
	}

	unsigned short CS_Mode::D_NEW_MODE_NUMBER( void ) const
	{
		unsigned short DIS_MACT_INDEX = pCS->GetDIS_MACT_INDEX();
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_NEW_MOD;
	}

	unsigned short CS_Mode::D_DEU_NUMBER( void ) const
	{
		// TODO
		return 0;
	}

	////////////////////////////////////////////////////////////////

	ControlSegment::ControlSegment( SimpleGPCSystem* pGPC, const std::string& _ident ):SimpleGPCSoftware( pGPC, _ident ),
		pGPC(pGPC), DIS_MACT_INDEX(0)
	{
		return;
	}

	ControlSegment::~ControlSegment( void )
	{
		return;
	}

	unsigned short ControlSegment::GetDIS_MACT_INDEX( void ) const
	{
		return DIS_MACT_INDEX;
	}

	void ControlSegment::Init( void )
	{
		return;
	}

	void ControlSegment::CleanUp( void )
	{
		return;
	}

	void ControlSegment::OnPreStep( double simt, double simdt, double mjd )
	{
		Run();
		return;
	}

	bool ControlSegment::OnParseLine( const char* keyword, const char* value )
	{
		// TODO if DIS_MACT_INDEX, then go to mode/block and set init true, or add state load/save to modes/blocks?
		if (!_strnicmp( keyword, "DIS_MACT_INDEX", 15 ))
		{
			sscanf_s( value, "%hu", &DIS_MACT_INDEX );
		}
		else return false;
		return true;
	}

	void ControlSegment::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "DIS_MACT_INDEX", DIS_MACT_INDEX );
		return;
	}

	unsigned short ControlSegment::D_OPS_NUMBER( void ) const
	{
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_OPS;
	}

	unsigned short ControlSegment::D_MODE_NUMBER( void ) const
	{
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_MOD;
	}

	unsigned short ControlSegment::D_SPEC_NUMBER( void ) const
	{
		// TODO
		return 0;
	}

	unsigned short ControlSegment::D_NEW_OPS_NUMBER( void ) const
	{
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_NEW_OPS;
	}

	unsigned short ControlSegment::D_NEW_MODE_NUMBER( void ) const
	{
		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		return CZ1V_D_MACT.CZ1V_D_NEW_MOD;
	}

	unsigned short ControlSegment::D_DEU_NUMBER( void ) const
	{
		// TODO
		return 0;
	}

	////////////////////////////////////////////////////////////////

	ControlSegmentOPS::ControlSegmentOPS( SimpleGPCSystem* pGPC, const std::string& _ident ):ControlSegment( pGPC, _ident )
	{
		return;
	}

	ControlSegmentOPS::~ControlSegmentOPS( void )
	{
		return;
	}

	void ControlSegmentOPS::Run( void )
	{
		if (DIS_MACT_INDEX == 0)
		{
			DNX_BMS( 0, DIS_MACT_INDEX, pGPC );
		}

		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

		if (CZ1V_D_MACT.CZ1V_D_MOD == 0)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] ControlSegmentOPS::Init" );
#endif// _DEBUG
			Init();// derived

			// HACK go to new mode after init, allowing to enter OPS in modes other then 1
			//CZ1V_D_MACT.CZ1V_D_MOD = 1;
			CZ1V_D_MACT.CZ1V_D_MOD = CZ1V_D_MACT.CZ1V_D_NEW_MOD;
			CZ1V_D_MACT.CZ1V_D_NEW_MOD = 0;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		}

		Modes[CZ1V_D_MACT.CZ1V_D_MOD - 1]->Run();

		if (CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x2000)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] ControlSegmentOPS::CleanUp" );
#endif// _DEBUG
			CleanUp();// derived

			DNX_BMS( 1, DIS_MACT_INDEX, pGPC );

			pGPC->CANCEL( GetIdentifier() );
		}
		return;
	}

	////////////////////////////////////////////////////////////////

	ControlSegmentSPEC::ControlSegmentSPEC( SimpleGPCSystem* pGPC, const std::string& _ident ):ControlSegment( pGPC, _ident )
	{
		return;
	}

	ControlSegmentSPEC::~ControlSegmentSPEC( void )
	{
		return;
	}

	void ControlSegmentSPEC::Run( void )
	{
		if (DIS_MACT_INDEX == 0)
		{
			DNX_BMS( 0, DIS_MACT_INDEX, pGPC );
		}

		SCP_MACT CZ1V_D_MACT;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );

		if (CZ1V_D_MACT.CZ1V_D_BLK == 0)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] ControlSegmentSPEC::Init" );
#endif// _DEBUG
			Init();// derived

			CZ1V_D_MACT.CZ1V_D_BLK = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_MACT, DIS_MACT_INDEX, &CZ1V_D_MACT, sizes_MACT, pos_MACT, cnt_MACT, 4 );
		}

		Blocks[CZ1V_D_MACT.CZ1V_D_BLK - 1]->Run();

		if (CZ1V_D_MACT.CZ1B_D_FLAG2 & 0x2000)
		{
#ifdef _DEBUG
			oapiWriteLogV( "(SSV_OV) [DEBUG] ControlSegmentSPEC::CleanUp" );
#endif// _DEBUG
			CleanUp();// derived

			DNX_BMS( 1, DIS_MACT_INDEX, pGPC );

			pGPC->CANCEL( GetIdentifier() );
		}
		return;
	}
}
