#include "GNC2_OPS.h"


// GNC2_OPS
namespace dps
{
	GNC2_OPS_Mode_1_Block_1::GNC2_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 2011 )
	{
		return;
	}

	void GNC2_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC2_OPS_Mode_1_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC2_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC2_OPS_Mode_1::GNC2_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC2_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC2_OPS_Mode_1::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_201, 1 );
		return;
	}

	void GNC2_OPS_Mode_1::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_201, 0 );
		return;
	}


	GNC2_OPS_Mode_2_Block_1::GNC2_OPS_Mode_2_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 2021 )
	{
		return;
	}

	void GNC2_OPS_Mode_2_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC2_OPS_Mode_2_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC2_OPS_Mode_2_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC2_OPS_Mode_2::GNC2_OPS_Mode_2( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC2_OPS_Mode_2_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC2_OPS_Mode_2::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_202_FROM_MM_201_FLAG, 1 );

		pGPC->SCHEDULE( "OMS_TVC_Feedback_SOP" );
		pGPC->SCHEDULE( "OMS_RM" );
		pGPC->SCHEDULE( "OMS_TVC_Command_SOP" );
		return;
	}

	void GNC2_OPS_Mode_2::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_202_FROM_MM_201_FLAG, 0 );

		pGPC->CANCEL( "OMS_TVC_Feedback_SOP" );
		pGPC->CANCEL( "OMS_RM" );
		pGPC->CANCEL( "OMS_TVC_Command_SOP" );
		return;
	}


	GNC2_OPS::GNC2_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "GNC2_OPS" )
	{
		Modes.push_back( new GNC2_OPS_Mode_1( pGPC, this ) );
		Modes.push_back( new GNC2_OPS_Mode_2( pGPC, this ) );
		return;
	}

	void GNC2_OPS::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS_2_INDICATOR, 1 );

		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 18, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 19, 3, 2 );

		SCHEDULE( "GNC_HFE" );
		SCHEDULE( "MSC" );
		SCHEDULE( "ATT_PROC_ORBIT" );
		SCHEDULE( "Switch_RM" );
		SCHEDULE( "THC_SOP" );
		SCHEDULE( "ORB_THREE_AX_RHC_SOP" );
		SCHEDULE( "GAX" );
		SCHEDULE( "DAPLightsDriver" );
		SCHEDULE( "ORB_ADI_PROC" );
		SCHEDULE( "RCS_ACT_LT" );
		SCHEDULE( "MEDSFCGNCXFER" );
		return;
	}

	void GNC2_OPS::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS_2_INDICATOR, 0 );

		CANCEL( "GNC_HFE" );
		CANCEL( "MSC" );
		CANCEL( "ATT_PROC_ORBIT" );
		CANCEL( "Switch_RM" );
		CANCEL( "THC_SOP" );
		CANCEL( "ORB_THREE_AX_RHC_SOP" );
		CANCEL( "GAX" );
		CANCEL( "DAPLightsDriver" );
		CANCEL( "ORB_ADI_PROC" );
		CANCEL( "RCS_ACT_LT" );
		CANCEL( "MEDSFCGNCXFER" );
		return;
	}

	bool GNC2_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void GNC2_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
