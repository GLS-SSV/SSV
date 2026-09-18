#include "GNC8_OPS.h"


// GNC8_OPS
namespace dps
{
	GNC8_OPS_Mode_1_Block_1::GNC8_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 8011 )
	{
		return;
	}

	void GNC8_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC8_OPS_Mode_1_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC8_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC8_OPS_Mode_1::GNC8_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC8_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC8_OPS_Mode_1::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_801_FROM_MM_201, 1 );
		return;
	}

	void GNC8_OPS_Mode_1::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_801_FROM_MM_201, 0 );
		return;
	}


	GNC8_OPS::GNC8_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "GNC8_OPS" )
	{
		Modes.push_back( new GNC8_OPS_Mode_1( pGPC, this ) );
		return;
	}

	void GNC8_OPS::Init( void )
	{
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 18, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 19, 3, 2 );

		SCHEDULE( "GNC_HFE" );
		SCHEDULE( "MSC" );
		SCHEDULE( "SF" );
		SCHEDULE( "Elevon_PFB_SOP" );
		SCHEDULE( "BodyFlap_PFB_SOP" );
		SCHEDULE( "Rudder_PFB_SOP" );
		SCHEDULE( "Speedbrake_PFB_SOP" );
		SCHEDULE( "RA_SOP" );
		SCHEDULE( "ATT_PROC_ORBIT" );
		SCHEDULE( "MM801" );
		SCHEDULE( "SBTC_SOP" );
		SCHEDULE( "Switch_RM" );
		SCHEDULE( "THC_SOP" );
		SCHEDULE( "OMS_TVC_Feedback_SOP" );
		SCHEDULE( "Aero_Act_SOP" );
		SCHEDULE( "GAX" );
		SCHEDULE( "DAPLightsDriver" );
		SCHEDULE( "ORB_ADI_PROC" );
		SCHEDULE( "RCS_ACT_LT" );
		SCHEDULE( "MEDSFCGNCXFER" );
		return;
	}

	void GNC8_OPS::CleanUp( void )
	{
		CANCEL( "GNC_HFE" );
		CANCEL( "MSC" );
		CANCEL( "SF" );
		CANCEL( "Elevon_PFB_SOP" );
		CANCEL( "BodyFlap_PFB_SOP" );
		CANCEL( "Rudder_PFB_SOP" );
		CANCEL( "Speedbrake_PFB_SOP" );
		CANCEL( "RA_SOP" );
		CANCEL( "ATT_PROC_ORBIT" );
		CANCEL( "MM801" );
		CANCEL( "SBTC_SOP" );
		CANCEL( "Switch_RM" );
		CANCEL( "THC_SOP" );
		CANCEL( "OMS_TVC_Feedback_SOP" );
		CANCEL( "Aero_Act_SOP" );
		CANCEL( "GAX" );
		CANCEL( "DAPLightsDriver" );
		CANCEL( "ORB_ADI_PROC" );
		CANCEL( "RCS_ACT_LT" );
		CANCEL( "MEDSFCGNCXFER" );
		return;
	}

	bool GNC8_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void GNC8_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
