#include "GNC1_OPS.h"


// GNC1_OPS
namespace dps
{
	void XXXXXXTRAJ_ITEM( int ITEM, SimpleGPCSystem* pGPC )
	{
		if (ITEM == 6)// TODO not in 101
		{
			pGPC->WriteCOMPOOL_IS( SCP_CONT_SERC, (pGPC->ReadCOMPOOL_IS( SCP_CONT_SERC ) == 1) ? 0 : 1 );
		}
		return;
	}


	GNC1_OPS_Mode_1_Block_1::GNC1_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1011 )
	{
		return;
	}

	void GNC1_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_1_Block_1::Input( void )
	{
		XXXXXXTRAJ_ITEM( ITEM(), pGPC );
		return;
	}

	void GNC1_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC1_OPS_Mode_1::GNC1_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, SCP_SRB_IGNITION_CMD )
	{
		Blocks.push_back( new GNC1_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC1_OPS_Mode_1::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_101, 1 );

		pGPC->SCHEDULE( "MPS_Dedicated_Display_Driver" );
		pGPC->SCHEDULE( "SSME_SOP" );
		pGPC->SCHEDULE( "RSLS" );
		pGPC->SCHEDULE( "AscentDAP" );
		pGPC->SCHEDULE( "ORB_ACTR_SLEW" );
		pGPC->SCHEDULE( "NW_POSN_SOP" );
		return;
	}

	void GNC1_OPS_Mode_1::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_101, 0 );

		pGPC->CANCEL( "NW_POSN_SOP" );
		pGPC->CANCEL( "ORB_ACTR_SLEW" );
		return;
	}


	GNC1_OPS_Mode_2_Block_1::GNC1_OPS_Mode_2_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1021 )
	{
		return;
	}

	void GNC1_OPS_Mode_2_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_2_Block_1::Input( void )
	{
		XXXXXXTRAJ_ITEM( ITEM(), pGPC );
		return;
	}

	void GNC1_OPS_Mode_2_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC1_OPS_Mode_2::GNC1_OPS_Mode_2( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, SCP_SRB_SEP_CMD_FLAG )
	{
		Blocks.push_back( new GNC1_OPS_Mode_2_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC1_OPS_Mode_2::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_102, 1 );

		pGPC->SCHEDULE( "SSME_Operations" );
		pGPC->SCHEDULE( "THREE_AX_RHC_SOP" );
		pGPC->SCHEDULE( "AMI_PROC" );
		pGPC->SCHEDULE( "AVVI_PROC" );

		// HACK KMAX should be I-Load
		pGPC->WriteCOMPOOL_IS( SCP_KMAX, pGPC->ReadCOMPOOL_IS( SCP_KMAX_NOM ) );
		return;
	}

	void GNC1_OPS_Mode_2::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_102, 0 );
		
		pGPC->CANCEL( "Elevon_PFB_SOP" );
		pGPC->CANCEL( "BodyFlap_PFB_SOP" );
		pGPC->CANCEL( "Rudder_PFB_SOP" );
		pGPC->CANCEL( "Speedbrake_PFB_SOP" );
		pGPC->CANCEL( "SRB_ATVC_CMD_SOP" );
		return;
	}


	GNC1_OPS_Mode_3_Block_1::GNC1_OPS_Mode_3_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1031 )
	{
		return;
	}

	void GNC1_OPS_Mode_3_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_3_Block_1::Input( void )
	{
		XXXXXXTRAJ_ITEM( ITEM(), pGPC );
		return;
	}

	void GNC1_OPS_Mode_3_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC1_OPS_Mode_3::GNC1_OPS_Mode_3( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, SCP_SEP_COMPLETE )
	{
		Blocks.push_back( new GNC1_OPS_Mode_3_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC1_OPS_Mode_3::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_103, 1 );

		pGPC->SCHEDULE( "MPS_Dump" );
		pGPC->SCHEDULE( "TransitionDAP" );
		pGPC->SCHEDULE( "ETSepSequence" );
		pGPC->SCHEDULE( "DAPLightsDriver" );
		return;
	}

	void GNC1_OPS_Mode_3::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_103, 0 );

		if (D_NEW_OPS_NUMBER() != 6)
		{
			// cancel only if not going to OPS 6
			pGPC->CANCEL( "SBTC_SOP" );
			pGPC->CANCEL( "AscentDAP" );
			pGPC->CANCEL( "TransitionDAP" );
		}
		return;
	}


	GNC1_OPS_Mode_4_Block_1::GNC1_OPS_Mode_4_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1041 )
	{
		return;
	}

	void GNC1_OPS_Mode_4_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_4_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_4_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC1_OPS_Mode_4::GNC1_OPS_Mode_4( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC1_OPS_Mode_4_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC1_OPS_Mode_4::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_104, 1 );

		pGPC->SCHEDULE( "OMS_RM" );
		pGPC->SCHEDULE( "RCS_ACT_LT" );
		return;
	}

	void GNC1_OPS_Mode_4::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_104, 0 );

		pGPC->CANCEL( "SSME_SOP" );
		pGPC->CANCEL( "SSME_Operations" );
		pGPC->CANCEL( "MPS_Dedicated_Display_Driver" );
		pGPC->CANCEL( "ETSepSequence" );
		pGPC->CANCEL( "MPS_ATVC_CMD_SOP" );
		pGPC->CANCEL( "MEC_SOP" );
		pGPC->CANCEL( "XXXXXX_TRAJ_DIP" );
		pGPC->CANCEL( "AMI_PROC" );
		pGPC->CANCEL( "AVVI_PROC" );
		return;
	}


	GNC1_OPS_Mode_5_Block_1::GNC1_OPS_Mode_5_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1051 )
	{
		return;
	}

	void GNC1_OPS_Mode_5_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_5_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_5_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC1_OPS_Mode_5::GNC1_OPS_Mode_5( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC1_OPS_Mode_5_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC1_OPS_Mode_5::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_105, 1 );
		return;
	}

	void GNC1_OPS_Mode_5::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_105, 0 );
		return;
	}


	GNC1_OPS_Mode_6_Block_1::GNC1_OPS_Mode_6_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 1061 )
	{
		return;
	}

	void GNC1_OPS_Mode_6_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_6_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC1_OPS_Mode_6_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC1_OPS_Mode_6::GNC1_OPS_Mode_6( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC1_OPS_Mode_6_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC1_OPS_Mode_6::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_106, 1 );
		return;
	}

	void GNC1_OPS_Mode_6::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_106, 0 );

		pGPC->CANCEL( "DAPLightsDriver" );
		return;
	}


	GNC1_OPS::GNC1_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "GNC1_OPS" )
	{
		Modes.push_back( new GNC1_OPS_Mode_1( pGPC, this ) );
		Modes.push_back( new GNC1_OPS_Mode_2( pGPC, this ) );
		Modes.push_back( new GNC1_OPS_Mode_3( pGPC, this ) );
		Modes.push_back( new GNC1_OPS_Mode_4( pGPC, this ) );
		Modes.push_back( new GNC1_OPS_Mode_5( pGPC, this ) );
		Modes.push_back( new GNC1_OPS_Mode_6( pGPC, this ) );
		return;
	}

	void GNC1_OPS::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS1_INDICATOR, 1 );

		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 18, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 0, 3, 2 );

		SCHEDULE( "GNC_HFE" );
		SCHEDULE( "MSC" );
		SCHEDULE( "SF" );
		SCHEDULE( "Elevon_PFB_SOP" );
		SCHEDULE( "BodyFlap_PFB_SOP" );
		SCHEDULE( "Rudder_PFB_SOP" );
		SCHEDULE( "Speedbrake_PFB_SOP" );
		SCHEDULE( "ASC_SITE_LOOKUP" );
		SCHEDULE( "ASCENT_UPP" );
		SCHEDULE( "ATT_PROC" );
		SCHEDULE( "XXXXXX_TRAJ_DIP" );
		SCHEDULE( "HYD_SYS_SOP" );
		SCHEDULE( "MPS_ATVC_CMD_SOP" );
		SCHEDULE( "SRB_ATVC_CMD_SOP" );
		SCHEDULE( "MEC_SOP" );
		SCHEDULE( "SBTC_SOP" );
		SCHEDULE( "Switch_RM" );
		SCHEDULE( "OMS_TVC_Feedback_SOP" );
		SCHEDULE( "OMS_TVC_Command_SOP" );
		SCHEDULE( "Aero_Act_SOP" );
		SCHEDULE( "VentCntlSeq" );
		SCHEDULE( "GAX" );
		SCHEDULE( "ASC_ADI_PROC" );
		SCHEDULE( "HSI_PROC" );
		SCHEDULE( "MEDSFCGNCXFER" );
		return;
	}

	void GNC1_OPS::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS1_INDICATOR, 0 );

		if (D_NEW_OPS_NUMBER() != 6)
		{
			// cancel only if not going to OPS 6
			CANCEL( "GNC_HFE" );
			CANCEL( "MSC" );
			CANCEL( "SF" );
			CANCEL( "MPS_Dump" );
			CANCEL( "ASC_SITE_LOOKUP" );
			CANCEL( "ATT_PROC" );
			CANCEL( "HYD_SYS_SOP" );
			CANCEL( "ETSepSequence" );
			CANCEL( "MPS_ATVC_CMD_SOP" );
			CANCEL( "XXXXXX_TRAJ_DIP" );
			CANCEL( "Switch_RM" );
			CANCEL( "THREE_AX_RHC_SOP" );
			CANCEL( "OMS_TVC_Feedback_SOP" );
			CANCEL( "OMS_TVC_Command_SOP" );
			CANCEL( "Aero_Act_SOP" );
			CANCEL( "VentCntlSeq" );
			CANCEL( "GAX" );
			CANCEL( "AMI_PROC" );
			CANCEL( "ASC_ADI_PROC" );
			CANCEL( "AVVI_PROC" );
			CANCEL( "HSI_PROC" );
			CANCEL( "MEDSFCGNCXFER" );
		}
		CANCEL( "RSLS" );
		CANCEL( "OMS_RM" );
		CANCEL( "RCS_ACT_LT" );
		CANCEL( "ASCENT_UPP" );
		return;
	}

	bool GNC1_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void GNC1_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
