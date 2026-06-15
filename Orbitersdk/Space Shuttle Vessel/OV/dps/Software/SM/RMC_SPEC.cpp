#include "RMC_SPEC.h"
#include "../../SimpleGPCSystem.h"


// SPEC 94 (PDRS CONTROL)
namespace dps
{
	RMC_SPEC_Block_1::RMC_SPEC_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 94 )
	{
		return;
	}

	void RMC_SPEC_Block_1::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] RMC_SPEC_Block_1::Init" );
#endif// _DEBUG
		// TODO
		return;
	}

	void RMC_SPEC_Block_1::Input( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] RMC_SPEC_Block_1::Input" );
#endif// _DEBUG

		// TODO move to RUD_KYBD
		if (KEY() == ITEM())
		{
			switch (ITEM_NO())
			{
				case 1:
					pGPC->WriteCOMPOOL_IS( SCP_CRGV_ARM_INIT_DISP, 1 );
					break;
				case 2:
					pGPC->WriteCOMPOOL_IS( SCP_CRGV_ARM_INIT_DISP, 2 );
					break;
			}
		}
		return;
	}

	void RMC_SPEC_Block_1::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] RMC_SPEC_Block_1::CleanUp" );
#endif// _DEBUG
		// TODO
		return;
	}



	RMC_SPEC::RMC_SPEC( SimpleGPCSystem* pGPC ):ControlSegmentSPEC( pGPC, "RMC_SPEC" )
	{
		Blocks.push_back( new RMC_SPEC_Block_1( pGPC, this ) );
		return;
	}

	void RMC_SPEC::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] RMC_SPEC::Init" );
#endif// _DEBUG

		pGPC->WriteCOMPOOL_IS( SCP_CRGV_ARM_INIT_DISP, 1 );// HACK

		/*if (ReadCOMPOOL_IS( SCP_CRAB_RMS_SPEC_INIT ) == 0)
		{
			WriteCOMPOOL_IS( SCP_CRAB_RMS_SPEC_INIT, 1 );

			pGPC->SCHEDULE( "REX_RMSEXEC" );
		}*/
		return;
	}

	void RMC_SPEC::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] RMC_SPEC::CleanUp" );
#endif// _DEBUG
		return;
	}

	bool RMC_SPEC::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentSPEC::OnParseLine( keyword, value );
	}

	void RMC_SPEC::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentSPEC::OnSaveState( scn );
		return;
	}
}
