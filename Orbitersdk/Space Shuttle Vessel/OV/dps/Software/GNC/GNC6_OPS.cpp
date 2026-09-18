#include "GNC6_OPS.h"


// GNC6_OPS
namespace dps
{
	GNC6_OPS_Mode_1_Block_1::GNC6_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 6011 )
	{
		return;
	}

	void GNC6_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC6_OPS_Mode_1_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC6_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC6_OPS_Mode_1::GNC6_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, SCP_SEP_COMPLETE )
	{
		Blocks.push_back( new GNC6_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC6_OPS_Mode_1::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_601, 1 );

		pGPC->SCHEDULE( "DAPLightsDriver" );
		return;
	}

	void GNC6_OPS_Mode_1::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_601, 0 );

		pGPC->CANCEL( "SSME_Operations" );
		pGPC->CANCEL( "AscentDAP" );
		pGPC->CANCEL( "MPS_Dedicated_Display_Driver" );
		pGPC->CANCEL( "ETSepSequence" );
		pGPC->CANCEL( "MEC_SOP" );
		pGPC->CANCEL( "THREE_AX_RHC_SOP" );
		pGPC->CANCEL( "OMS_TVC_Feedback_SOP" );
		pGPC->CANCEL( "DAPLightsDriver" );
		pGPC->CANCEL( "ASC_ADI_PROC" );
		pGPC->CANCEL( "XXXXXX_TRAJ_DIP" );
		return;
	}


	GNC6_OPS_Mode_2_Block_1::GNC6_OPS_Mode_2_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 6021 )
	{
		return;
	}

	void GNC6_OPS_Mode_2_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC6_OPS_Mode_2_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC6_OPS_Mode_2_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC6_OPS_Mode_2::GNC6_OPS_Mode_2( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0/*TODO*/ )
	{
		Blocks.push_back( new GNC6_OPS_Mode_2_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC6_OPS_Mode_2::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_602, 1 );
		
		pGPC->SCHEDULE( "Elevon_PFB_SOP" );
		pGPC->SCHEDULE( "BodyFlap_PFB_SOP" );
		pGPC->SCHEDULE( "Rudder_PFB_SOP" );
		pGPC->SCHEDULE( "Speedbrake_PFB_SOP" );
		pGPC->SCHEDULE( "ADTA_RM" );
		pGPC->SCHEDULE( "ADTA_SOP" );
		pGPC->SCHEDULE( "ENT_AREA_NAV" );
		pGPC->SCHEDULE( "TWO_AX_RHC_SOP" );
		pGPC->SCHEDULE( "RPTA_SOP" );
		pGPC->SCHEDULE( "BF_Slew_SOP" );
		pGPC->SCHEDULE( "PriorityRateLimiting" );
		pGPC->SCHEDULE( "EL_ADI_PROC" );
		pGPC->SCHEDULE( "HUD_PROC" );
		pGPC->SCHEDULE( "LAMP_PROC" );
		pGPC->SCHEDULE( "RCS_ACT_LT" );
		pGPC->SCHEDULE( "VERT_SIT_DIP" );
		return;
	}

	void GNC6_OPS_Mode_2::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_602, 0 );

		pGPC->CANCEL( "OMS_TVC_Command_SOP" );
		return;
	}


	GNC6_OPS_Mode_3_Block_1::GNC6_OPS_Mode_3_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 6031 )
	{
		return;
	}

	void GNC6_OPS_Mode_3_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC6_OPS_Mode_3_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC6_OPS_Mode_3_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC6_OPS_Mode_3::GNC6_OPS_Mode_3( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC6_OPS_Mode_3_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC6_OPS_Mode_3::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_603, 1 );

		pGPC->SCHEDULE( "NW_POSN_SOP" );
		pGPC->SCHEDULE( "RA_SOP" );
		pGPC->SCHEDULE( "Landing_SOP" );
		return;
	}

	void GNC6_OPS_Mode_3::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_603, 0 );

		pGPC->CANCEL( "SSME_SOP" );
		pGPC->CANCEL( "NW_POSN_SOP" );
		pGPC->CANCEL( "ADTA_RM" );
		pGPC->CANCEL( "ADTA_SOP" );
		pGPC->CANCEL( "RA_SOP" );
		pGPC->CANCEL( "ENT_AREA_NAV" );
		pGPC->CANCEL( "TWO_AX_RHC_SOP" );
		pGPC->CANCEL( "RPTA_SOP" );
		pGPC->CANCEL( "BF_Slew_SOP" );
		pGPC->CANCEL( "Landing_SOP" );
		pGPC->CANCEL( "PriorityRateLimiting" );
		pGPC->CANCEL( "EL_ADI_PROC" );
		pGPC->CANCEL( "LAMP_PROC" );
		pGPC->CANCEL( "VERT_SIT_DIP" );
		return;
	}


	GNC6_OPS::GNC6_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "GNC6_OPS" )
	{
		Modes.push_back( new GNC6_OPS_Mode_1( pGPC, this ) );
		Modes.push_back( new GNC6_OPS_Mode_2( pGPC, this ) );
		Modes.push_back( new GNC6_OPS_Mode_3( pGPC, this ) );
		return;
	}

	void GNC6_OPS::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS_6_INDICATOR, 1 );

		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 18, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 0, 3, 2 );

		SCHEDULE( "SPI_PROC" );
		return;
	}

	void GNC6_OPS::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS_6_INDICATOR, 0 );

		CANCEL( "GNC_HFE" );
		CANCEL( "MSC" );
		CANCEL( "SF" );
		CANCEL( "MPS_Dump" );
		CANCEL( "Elevon_PFB_SOP" );
		CANCEL( "BodyFlap_PFB_SOP" );
		CANCEL( "Rudder_PFB_SOP" );
		CANCEL( "Speedbrake_PFB_SOP" );
		CANCEL( "ASC_SITE_LOOKUP" );
		CANCEL( "ATT_PROC" );
		CANCEL( "HYD_SYS_SOP" );
		CANCEL( "MPS_ATVC_CMD_SOP" );
		CANCEL( "SBTC_SOP" );
		CANCEL( "Switch_RM" );
		CANCEL( "Aero_Act_SOP" );
		CANCEL( "VentCntlSeq" );
		CANCEL( "GAX" );
		CANCEL( "AMI_PROC" );
		CANCEL( "AVVI_PROC" );
		CANCEL( "HSI_PROC" );
		CANCEL( "HUD_PROC" );
		CANCEL( "RCS_ACT_LT" );
		CANCEL( "SPI_PROC" );
		CANCEL( "MEDSFCGNCXFER" );
		return;
	}

	bool GNC6_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void GNC6_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
