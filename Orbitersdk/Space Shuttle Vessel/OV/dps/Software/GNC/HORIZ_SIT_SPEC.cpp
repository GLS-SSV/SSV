#include "HORIZ_SIT_SPEC.h"


// SPEC 50 (HORIZ SIT)
namespace dps
{
	HORIZ_SIT_SPEC_Block_1::HORIZ_SIT_SPEC_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 50 )
	{
		return;
	}

	void HORIZ_SIT_SPEC_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void HORIZ_SIT_SPEC_Block_1::Input( void )
	{
		if (KEY() == ITEM())
		{
			switch (ITEM_NO())
			{
				case 3:
					pGPC->WriteCOMPOOL_IS( SCP_PRI_SEL, 1 );
					break;
				case 4:
					pGPC->WriteCOMPOOL_IS( SCP_SEC_SEL, 1 );
					break;
				case 6:
					{
						pGPC->WriteCOMPOOL_IS( SCP_TOGHAC, 1 );

						if ((pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) ||
							(pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_105 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_106 ) == 1))
						{
							pGPC->WriteCOMPOOL_IS( SCP_OVHD, 0 );
						}
						
					}
					break;
				case 7:
					pGPC->WriteCOMPOOL_IS( SCP_ENT_PT_SW, 1 );
					break;
				case 8:
					pGPC->WriteCOMPOOL_IS( SCP_GI_CHANGE, 1 );
					break;
				case 39:
					{
						unsigned short I_SHORT_RW = pGPC->ReadCOMPOOL_IS( SCP_I_SHORT_RW );
						I_SHORT_RW++;
						if (I_SHORT_RW > 2) I_SHORT_RW = 0;
						pGPC->WriteCOMPOOL_IS( SCP_I_SHORT_RW, I_SHORT_RW );
					}
					break;
				case 41:
					{
						if ((ITEM_I() > 0) && (ITEM_I() <= 45))
						{
							pGPC->WriteCOMPOOL_IS( SCP_NEW_AREA, 1 );
							pGPC->WriteCOMPOOL_IS( SCP_AREA_SEL, ITEM_I() );

							if ((pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1) ||
							(pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_105 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_106 ) == 1) || (pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_601 ) == 1))
							{
								pGPC->WriteCOMPOOL_IS( SCP_TOGHAC, 0 );
								pGPC->WriteCOMPOOL_IS( SCP_OVHD, 1 );
							}
						}
						//else return false;// TODO
					}
					break;
			}
		}
		return;
	}

	void HORIZ_SIT_SPEC_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}



	HORIZ_SIT_SPEC::HORIZ_SIT_SPEC( SimpleGPCSystem* pGPC ):ControlSegmentSPEC( pGPC, "HORIZ_SIT_SPEC" )
	{
		Blocks.push_back( new HORIZ_SIT_SPEC_Block_1( pGPC, this ) );
		return;
	}

	void HORIZ_SIT_SPEC::Init( void )
	{
		pGPC->SCHEDULE( "HORIZ_SIT_SPEC_FUNC" );
		return;
	}

	void HORIZ_SIT_SPEC::CleanUp( void )
	{
		pGPC->CANCEL( "HORIZ_SIT_SPEC_FUNC" );
		return;
	}

	bool HORIZ_SIT_SPEC::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentSPEC::OnParseLine( keyword, value );
	}

	void HORIZ_SIT_SPEC::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentSPEC::OnSaveState( scn );
		return;
	}
}
