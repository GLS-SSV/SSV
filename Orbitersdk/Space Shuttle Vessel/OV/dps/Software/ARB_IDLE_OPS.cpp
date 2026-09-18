#include "ARB_IDLE_OPS.h"


// OPS000
namespace dps
{
	OPS000_Mode_0_Block_1::OPS000_Mode_0_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1 )
	{
		return;
	}

	void OPS000_Mode_0_Block_1::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] OPS000_Mode_0_Block_1::Init" );
#endif// _DEBUG
		// TODO
		return;
	}

	void OPS000_Mode_0_Block_1::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] OPS000_Mode_0_Block_1::CleanUp" );
#endif// _DEBUG
		// TODO
		return;
	}


	OPS000_Mode_0::OPS000_Mode_0( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new OPS000_Mode_0_Block_1( pGPC, pCS ) );
		return;
	}

	void OPS000_Mode_0::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] OPS000_Mode_0::Init" );
#endif// _DEBUG
		// TODO
		return;
	}

	void OPS000_Mode_0::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] OPS000_Mode_0::CleanUp" );
#endif// _DEBUG
		// TODO
		return;
	}


	ARB_IDLE_OPS::ARB_IDLE_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "ARB_IDLE_OPS" )
	{
		Modes.push_back( new OPS000_Mode_0( pGPC, this ) );
		return;
	}

	void ARB_IDLE_OPS::Init( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ARB_IDLE_OPS::Init" );
#endif// _DEBUG
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 0, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 0, 3, 2 );
		return;
	}

	void ARB_IDLE_OPS::CleanUp( void )
	{
#ifdef _DEBUG
		oapiWriteLogV( "(SSV_OV) [DEBUG] ARB_IDLE_OPS::CleanUp" );
#endif// _DEBUG
		// TODO
		return;
	}

	bool ARB_IDLE_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void ARB_IDLE_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
