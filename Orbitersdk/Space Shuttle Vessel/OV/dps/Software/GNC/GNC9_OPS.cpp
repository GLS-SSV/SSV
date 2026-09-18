#include "GNC9_OPS.h"


// GNC9_OPS
namespace dps
{
	GNC9_OPS_Mode_1_Block_1::GNC9_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 9011 )
	{
		return;
	}

	void GNC9_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC9_OPS_Mode_1_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC9_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC9_OPS_Mode_1::GNC9_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC9_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC9_OPS_Mode_1::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_901, 1 );
		return;
	}

	void GNC9_OPS_Mode_1::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_901, 0 );
		return;
	}


	GNC9_OPS::GNC9_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "GNC9_OPS" )
	{
		Modes.push_back( new GNC9_OPS_Mode_1( pGPC, this ) );
		return;
	}

	void GNC9_OPS::Init( void )
	{
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 0, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 0, 3, 2 );

		SCHEDULE( "GNC_HFE" );
		SCHEDULE( "MSC" );
		SCHEDULE( "SF" );
		SCHEDULE( "MPS_ATVC_CMD_SOP" );
		SCHEDULE( "Switch_RM" );
		SCHEDULE( "OMS_TVC_Feedback_SOP" );
		SCHEDULE( "GAX" );
		SCHEDULE( "MEDSFCGNCXFER" );
		return;
	}

	void GNC9_OPS::CleanUp( void )
	{
		CANCEL( "GNC_HFE" );
		CANCEL( "MSC" );
		CANCEL( "SF" );
		CANCEL( "MPS_ATVC_CMD_SOP" );
		CANCEL( "Switch_RM" );
		CANCEL( "OMS_TVC_Feedback_SOP" );
		CANCEL( "GAX" );
		CANCEL( "MEDSFCGNCXFER" );
		return;
	}

	bool GNC9_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void GNC9_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
