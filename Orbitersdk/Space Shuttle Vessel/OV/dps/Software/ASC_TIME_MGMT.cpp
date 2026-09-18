#include "ASC_TIME_MGMT.h"


// SPEC 2 (TIME)
namespace dps
{
	ASC_TIME_MGMT_Block_1::ASC_TIME_MGMT_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 2 )
	{
		return;
	}

	void ASC_TIME_MGMT_Block_1::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ASC_TIME_MGMT_Block_1::Init" );
#endif// _DEBUG
		// TODO
		return;
	}

	void ASC_TIME_MGMT_Block_1::Input( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ASC_TIME_MGMT_Block_1::Input" );
#endif// _DEBUG
		if (KEY() == ITEM())
		{
			switch (ITEM_NO())
			{
				case 1:
					pGPC->WriteCOMPOOL_IS( SCP_T_GMT_MET, 1 );
					break;
				case 2:
					pGPC->WriteCOMPOOL_IS( SCP_T_GMT_MET, 0 );
					break;
				case 3:
					pGPC->WriteCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 3, ITEM_I(), 23 );
					break;
				case 6:
					{
						/*int nNew;
						if (GetIntegerUnsigned( Data, nNew ))
						{
							if (nNew <= 23)
							{
								CAAV_TM_ITEM_I[item - 1] = nNew;
								if (item < 6) timer1ena = true;
								else timer2ena = true;
							}
							else return false;
						}
						else return false;*/
						pGPC->WriteCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 6, ITEM_I(), 23 );
					}
					break;
				case 4:
					pGPC->WriteCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 4, ITEM_I(), 23 );
					break;
				case 5:
					pGPC->WriteCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 5, ITEM_I(), 23 );
					break;
				case 7:
					pGPC->WriteCOMPOOL_AIS( SCP_CAAV_TM_ITEM_I, 7, ITEM_I(), 23 );
					break;
				case 8:
					{
						/*int nNew;
						if (GetIntegerUnsigned( Data, nNew ))
						{
							if (nNew <= 59)
							{
								CAAV_TM_ITEM_I[item - 1] = nNew;
								if (item < 6) timer1ena = true;
								else timer2ena = true;
							}
							else return false;
						}
						else return false;*/
					}
					break;
				case 23:
					{
						/*int nNew;
						if (GetIntegerUnsigned( Data, nNew ))
						{
							if (nNew <= 99)
							{
								WriteCOMPOOL_IS( SCP_SM_TONE_DURATION, nNew );
							}
							else return false;
						}
						else return false;*/
					}
					break;
			}
		}
		return;
	}

	void ASC_TIME_MGMT_Block_1::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ASC_TIME_MGMT_Block_1::CleanUp" );
#endif// _DEBUG
		// TODO
		return;
	}



	ASC_TIME_MGMT::ASC_TIME_MGMT( SimpleGPCSystem* pGPC ):ControlSegmentSPEC( pGPC, "ASC_TIME_MGMT" )
	{
		Blocks.push_back( new ASC_TIME_MGMT_Block_1( pGPC, this ) );
		return;
	}

	void ASC_TIME_MGMT::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ASC_TIME_MGMT::Init" );
#endif// _DEBUG
		pGPC->SCHEDULE( "ASG_CYCLIC_UPDATE" );
		return;
	}

	void ASC_TIME_MGMT::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ASC_TIME_MGMT::CleanUp" );
#endif// _DEBUG
		pGPC->CANCEL( "ASG_CYCLIC_UPDATE" );
		return;
	}

	bool ASC_TIME_MGMT::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentSPEC::OnParseLine( keyword, value );
	}

	void ASC_TIME_MGMT::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentSPEC::OnSaveState( scn );
		return;
	}
}
