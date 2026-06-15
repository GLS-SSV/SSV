#include "SM2_OPS.h"
#include "SSB_PL_BAY_DOORS.h"


// SM2_OPS
namespace dps
{
	bool SBD_ITEM( int ITEM, SimpleGPCSystem* pGPC )
	{
		if (ITEM > 17) return false;
		if (ITEM < 3)
		{
			if (ITEM == 1)
			{
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x8000 );
			}
			else
			{
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x4000 );
			}
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG, 1 );
		}
		else
		{
			if (ITEM < 14)
			{
				if (ITEM == 3)
				{
					if (pGPC->ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 0)
					{
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, pGPC->ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) ^ 1 );
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS, 0 );
					}
					else
					{
						return false;
					}
				}
				else
				{
					unsigned short itembit = 0x1000 >> (ITEM - 4);
					if (pGPC->ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 0)
					{
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS, pGPC->ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) ^ itembit );
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
					}
					else
					{
						if (((pGPC->ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & ~itembit) != 0) && ((pGPC->ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) & itembit) == 0))
						{
							pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS, pGPC->ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) | itembit );
							pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
						}
						else
						{
							return false;
						}
					}
				}
			}
			else
			{
				if (ITEM == 14)
				{
					if (pGPC->ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1)
					{
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 0 );
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
					}
					else
					{
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 1 );
						pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 1 );
					}
				}
				else
				{
					if (pGPC->ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1)
					{
						if (ITEM == 15)
						{
							pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 1 );
							pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
							pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
						}
						else
						{
							if (ITEM == 16)
							{
								pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 1 );
								pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
								pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
							}
							else
							{
								pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 1 );
								pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
								pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
							}
						}
					}
					else
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	void S2I_CLNUP( unsigned short S2I_ID, unsigned short S2I_DEU_NO, SimpleGPCSystem* pGPC )
	{
		switch (S2I_ID)
		{
			case 1:// OPS 2 Initialization
				// setup SM hybrid dispatcher table
				// HACK changed timing to 12 cycles of 0.16s each
				{
					SCP_HYB_DISPATCH SHD_HYB_DISPATCH;

					// Set Flag Cycle 1 (SSD)
					SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 14;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 1, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// Set Flag Cycle 7 (SSD)
					SHD_HYB_DISPATCH.PC = 7;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 14;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 2, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSD (202, 201)
					SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 1;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 3, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSD (201)
					SHD_HYB_DISPATCH.PC = 7;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 1;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 4, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// Set Flag Cycle 5 (SSB)
					SHD_HYB_DISPATCH.PC = 5;
					SHD_HYB_DISPATCH.FREQ = 0x800C;
					SHD_HYB_DISPATCH.CASENO = 14;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 5, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSB
					SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x8002;
					SHD_HYB_DISPATCH.CASENO = 10;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 6, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSA
					SHD_HYB_DISPATCH.PC = 2;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 2;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 7, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSF
					SHD_HYB_DISPATCH.PC = 2;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 3;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 8, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSN
					SHD_HYB_DISPATCH.PC = 4;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 5;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 9, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSW
					SHD_HYB_DISPATCH.PC = 4;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 6;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 10, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSS
					SHD_HYB_DISPATCH.PC = 4;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 11;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 11, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSH
					SHD_HYB_DISPATCH.PC = 8;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 9;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 12, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSR
					SHD_HYB_DISPATCH.PC = 8;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 8;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 13, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SST
					SHD_HYB_DISPATCH.PC = 8;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 7;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 14, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSC
					SHD_HYB_DISPATCH.PC = 10;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 4;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 15, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSM
					SHD_HYB_DISPATCH.PC = 12;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 12;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 16, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSO
					SHD_HYB_DISPATCH.PC = 12;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					SHD_HYB_DISPATCH.CASENO = 13;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 17, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
				}
				// TODO Basic SM
				// TODO Special Processes

				pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 78, 3, 2 );
				pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 79, 3, 2 );
				break;
			case 2:// Mode 201 Initialization
				// update SM hybrid dispatcher table
				{
					SCP_HYB_DISPATCH SHD_HYB_DISPATCH;

					// SSD (202, 201)
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 3, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					//SHD_HYB_DISPATCH.CASENO = 1;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 3, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSD (201)
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 4, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 7;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					//SHD_HYB_DISPATCH.CASENO = 1;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 4, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// Set Flag Cycle 5 (SSB)
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 5, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 5;
					SHD_HYB_DISPATCH.FREQ = 0x800C;
					//SHD_HYB_DISPATCH.CASENO = 14;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 5, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSB
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 6, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x8002;
					//SHD_HYB_DISPATCH.CASENO = 10;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 6, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

				}
				break;
			case 3:// Mode 201 Cleanup
				break;
			case 4:// Mode 202 Initialization
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x4000 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, 0 );
				// update SM hybrid dispatcher table
				{
					SCP_HYB_DISPATCH SHD_HYB_DISPATCH;

					// SSD (202, 201)
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 3, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x0002;
					//SHD_HYB_DISPATCH.CASENO = 1;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 3, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSD (201)
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 4, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 7;
					SHD_HYB_DISPATCH.FREQ = 0x800C;
					//SHD_HYB_DISPATCH.CASENO = 1;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 4, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// Set Flag Cycle 5 (SSB)
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 5, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 5;
					SHD_HYB_DISPATCH.FREQ = 0x000C;
					//SHD_HYB_DISPATCH.CASENO = 14;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 5, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

					// SSB
					pGPC->ReadCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 6, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );
					//SHD_HYB_DISPATCH.PC = 1;
					SHD_HYB_DISPATCH.FREQ = 0x0002;
					//SHD_HYB_DISPATCH.CASENO = 10;
					pGPC->WriteCOMPOOL_ASTRUCT( SCP_SHD_HYB_DISPATCH, 6, &SHD_HYB_DISPATCH, sizes_HYB_DISPATCH, pos_HYB_DISPATCH, cnt_HYB_DISPATCH, 32 );

				}
				break;
			case 5:// Mode 202 Cleanup
				if (pGPC->ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) != 2)// not in stop
				{
					pGPC->WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 0 );
					pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
					pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
					pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 1 );

					SSB_PL_BAY_DOORS* pSSB_PL_BAY_DOORS = dynamic_cast<SSB_PL_BAY_DOORS*>(pGPC->GetCOMSUB( "SSB_PL_BAY_DOORS" ));
					if (pSSB_PL_BAY_DOORS) pSSB_PL_BAY_DOORS->Call();
				}

				pGPC->WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_COMMON_PBD_FAIL_INDICATOR, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
				pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS, 0 );

				if (pGPC->ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) == 0x8000)
				{
					pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x4000 );
					pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG, 1 );

					SSB_PL_BAY_DOORS* pSSB_PL_BAY_DOORS = dynamic_cast<SSB_PL_BAY_DOORS*>(pGPC->GetCOMSUB( "SSB_PL_BAY_DOORS" ));
					if (pSSB_PL_BAY_DOORS) pSSB_PL_BAY_DOORS->Call();
				}
				break;
			case 6:// OPS 2 Cleanup
				// TODO Basic SM
				// TODO Special Processes
				break;
		}
		return;
	}


	SM2_OPS_Mode_1_Block_1::SM2_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 2011 )
	{
		return;
	}

	void SM2_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void SM2_OPS_Mode_1_Block_1::Input( void )
	{
		// TODO call SAM_ITEM();
		return;
	}

	void SM2_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	SM2_OPS_Mode_1::SM2_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new SM2_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void SM2_OPS_Mode_1::Init( void )
	{
		// init mode
		S2I_CLNUP( 2, 0, pGPC );
		return;
	}

	void SM2_OPS_Mode_1::CleanUp( void )
	{
		// cleanup mode
		S2I_CLNUP( 3, 0, pGPC );
		return;
	}



	SM2_OPS_Mode_2_Block_1::SM2_OPS_Mode_2_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 2021 )
	{
		return;
	}

	void SM2_OPS_Mode_2_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void SM2_OPS_Mode_2_Block_1::Input( void )
	{
		if (KEY() == ITEM())
		{
			SBD_ITEM( ITEM_NO(), pGPC );
		}
		return;
	}

	void SM2_OPS_Mode_2_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	SM2_OPS_Mode_2::SM2_OPS_Mode_2( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new SM2_OPS_Mode_2_Block_1( pGPC, pCS ) );
		return;
	}

	void SM2_OPS_Mode_2::Init( void )
	{
		// init mode
		S2I_CLNUP( 4, 0, pGPC );
		return;
	}

	void SM2_OPS_Mode_2::CleanUp( void )
	{
		// cleanup mode
		S2I_CLNUP( 5, 0, pGPC );
		return;
	}



	SM2_OPS::SM2_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "SM2_OPS" )
	{
		Modes.push_back( new SM2_OPS_Mode_1( pGPC, this ) );
		Modes.push_back( new SM2_OPS_Mode_2( pGPC, this ) );
		return;
	}

	void SM2_OPS::Init( void )
	{
		// init OPS
		S2I_CLNUP( 1, 0, pGPC );

		// TODO schedule Data Acquisition (5Hz)
		// TODO schedule Performance Monitor Control (1Hz)

		// schedule Special Processes Executive
		pGPC->SCHEDULE( "SSP_EXEC" );

		// TODO schedule Uplink Processor
		return;
	}

	void SM2_OPS::CleanUp( void )
	{
		// TODO cancel Data Acquisition

		// cancel Special Processes Executive
		pGPC->CANCEL( "SSP_EXEC" );

		// TODO cancel RMS Executive
		//pGPC->CANCEL( "REX_RMSEXEC" );

		// cleanup OPS
		S2I_CLNUP( 6, 0, pGPC );
		return;
	}

	bool SM2_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void SM2_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
