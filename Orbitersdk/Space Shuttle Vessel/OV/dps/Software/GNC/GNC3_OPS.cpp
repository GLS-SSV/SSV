#include "GNC3_OPS.h"


// GNC3_OPS
namespace dps
{
	GNC3_OPS_Mode_1_Block_1::GNC3_OPS_Mode_1_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 3011 )
	{
		return;
	}

	void GNC3_OPS_Mode_1_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_1_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_1_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC3_OPS_Mode_1::GNC3_OPS_Mode_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0/*TODO*/ )
	{
		Blocks.push_back( new GNC3_OPS_Mode_1_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC3_OPS_Mode_1::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_301, 1 );

		pGPC->SCHEDULE( "THREE_AX_RHC_SOP" );
		pGPC->SCHEDULE( "OMS_TVC_Feedback_SOP" );
		pGPC->SCHEDULE( "OMS_RM" );
		pGPC->SCHEDULE( "OMS_TVC_Command_SOP" );
		pGPC->SCHEDULE( "DAPLightsDriver" );
		pGPC->SCHEDULE( "EL_ADI_PROC" );
		return;
	}

	void GNC3_OPS_Mode_1::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_301, 0 );
		return;
	}


	GNC3_OPS_Mode_2_Block_1::GNC3_OPS_Mode_2_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 3021 )
	{
		return;
	}

	void GNC3_OPS_Mode_2_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_2_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_2_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC3_OPS_Mode_2::GNC3_OPS_Mode_2( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0/*TODO*/ )
	{
		Blocks.push_back( new GNC3_OPS_Mode_2_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC3_OPS_Mode_2::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_302, 1 );
		return;
	}

	void GNC3_OPS_Mode_2::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_302, 0 );
		return;
	}


	GNC3_OPS_Mode_3_Block_1::GNC3_OPS_Mode_3_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 3031 )
	{
		return;
	}

	void GNC3_OPS_Mode_3_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_3_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_3_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC3_OPS_Mode_3::GNC3_OPS_Mode_3( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0/*TODO*/ )
	{
		Blocks.push_back( new GNC3_OPS_Mode_3_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC3_OPS_Mode_3::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_303, 1 );
		return;
	}

	void GNC3_OPS_Mode_3::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_303, 0 );

		pGPC->CANCEL( "THREE_AX_RHC_SOP" );
		pGPC->CANCEL( "OMS_TVC_Feedback_SOP" );
		pGPC->CANCEL( "DAPLightsDriver" );
		return;
	}


	GNC3_OPS_Mode_4_Block_1::GNC3_OPS_Mode_4_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 3041 )
	{
		return;
	}

	void GNC3_OPS_Mode_4_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_4_Block_1::Input( void )
	{
		if (KEY() == ITEM())
		{
			switch (ITEM_NO())
			{
				case 1:
					if ((ITEM_I() >= -10) && (ITEM_I() <= 10))
					{
						pGPC->WriteCOMPOOL_IS( SCP_BIAS_ITEM, ITEM_I() );
					}
					else return;
					break;
				case 2:
					pGPC->WriteCOMPOOL_SS( SCP_DLRDOT, 0.0 );
					break;
				/*case 3:
					break;*/
				default:
					return;
			}
		}
		return;
	}

	void GNC3_OPS_Mode_4_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC3_OPS_Mode_4::GNC3_OPS_Mode_4( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, SCP_EG_END )
	{
		Blocks.push_back( new GNC3_OPS_Mode_4_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC3_OPS_Mode_4::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_304, 1 );

		pGPC->SCHEDULE( "ADTA_RM" );
		pGPC->SCHEDULE( "LAMP_PROC" );
		pGPC->SCHEDULE( "H_HDOT_ACCVERT" );
		pGPC->SCHEDULE( "GUIDECOMP" );
		pGPC->SCHEDULE( "Entry_UPP" );
		pGPC->SCHEDULE( "EntryGuidance" );
		pGPC->SCHEDULE( "TWO_AX_RHC_SOP" );
		pGPC->SCHEDULE( "AerojetDAP" );
		pGPC->SCHEDULE( "MPS_ATVC_CMD_SOP" );
		pGPC->SCHEDULE( "RPTA_SOP" );
		pGPC->SCHEDULE( "SBTC_SOP" );
		pGPC->SCHEDULE( "BF_Slew_SOP" );
		pGPC->SCHEDULE( "JetSelectionLogic" );
		pGPC->SCHEDULE( "PriorityRateLimiting" );
		pGPC->SCHEDULE( "Aero_Act_SOP" );
		pGPC->SCHEDULE( "AMI_PROC" );
		pGPC->SCHEDULE( "AVVI_PROC" );
		pGPC->SCHEDULE( "HSI_PROC" );
		pGPC->SCHEDULE( "HUD_PROC" );
		pGPC->SCHEDULE( "ENT_DIP" );
		return;
	}

	void GNC3_OPS_Mode_4::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_304, 0 );

		pGPC->CANCEL( "Entry_UPP" );
		pGPC->CANCEL( "EntryGuidance" );
		pGPC->CANCEL( "ENT_DIP" );
		pGPC->CANCEL( "OMS_RM" );
		pGPC->CANCEL( "OMS_TVC_Command_SOP" );
		return;
	}


	GNC3_OPS_Mode_5_Block_1::GNC3_OPS_Mode_5_Block_1( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Block( pGPC, pCS, 3051 )
	{
		return;
	}

	void GNC3_OPS_Mode_5_Block_1::Init( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_5_Block_1::Input( void )
	{
		// TODO
		return;
	}

	void GNC3_OPS_Mode_5_Block_1::CleanUp( void )
	{
		// TODO
		return;
	}


	GNC3_OPS_Mode_5::GNC3_OPS_Mode_5( SimpleGPCSystem* pGPC, ControlSegment* pCS ):CS_Mode( pGPC, pCS, 0 )
	{
		Blocks.push_back( new GNC3_OPS_Mode_5_Block_1( pGPC, pCS ) );
		return;
	}

	void GNC3_OPS_Mode_5::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_305, 1 );

		pGPC->SCHEDULE( "NW_POSN_SOP" );
		pGPC->SCHEDULE( "RA_SOP" );
		pGPC->SCHEDULE( "TAEM_UPP" );
		pGPC->SCHEDULE( "AL_UPP" );
		pGPC->SCHEDULE( "TAEMGuidance" );
		pGPC->SCHEDULE( "AutolandGuidance" );
		pGPC->SCHEDULE( "Landing_SOP" );
		pGPC->SCHEDULE( "VERT_SIT_DIP" );
		return;
	}

	void GNC3_OPS_Mode_5::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_305, 0 );

		pGPC->CANCEL( "NW_POSN_SOP" );
		pGPC->CANCEL( "ADTA_RM" );
		pGPC->CANCEL( "RA_SOP" );
		pGPC->CANCEL( "AerojetDAP" );
		pGPC->CANCEL( "RPTA_SOP" );
		pGPC->CANCEL( "SBTC_SOP" );
		pGPC->CANCEL( "BF_Slew_SOP" );
		pGPC->CANCEL( "H_HDOT_ACCVERT" );
		pGPC->CANCEL( "GUIDECOMP" );
		pGPC->CANCEL( "TAEM_UPP" );
		pGPC->CANCEL( "AL_UPP" );
		pGPC->CANCEL( "TWO_AX_RHC_SOP" );
		pGPC->CANCEL( "AutolandGuidance" );
		pGPC->CANCEL( "AutolandGuidance" );
		pGPC->CANCEL( "Landing_SOP" );
		pGPC->CANCEL( "JetSelectionLogic" );
		pGPC->CANCEL( "PriorityRateLimiting" );
		pGPC->CANCEL( "Aero_Act_SOP" );
		pGPC->CANCEL( "EL_ADI_PROC" );
		pGPC->CANCEL( "LAMP_PROC" );
		pGPC->CANCEL( "VERT_SIT_DIP" );
		return;
	}


	GNC3_OPS::GNC3_OPS( SimpleGPCSystem* pGPC ):ControlSegmentOPS( pGPC, "GNC3_OPS" )
	{
		Modes.push_back( new GNC3_OPS_Mode_1( pGPC, this ) );
		Modes.push_back( new GNC3_OPS_Mode_2( pGPC, this ) );
		Modes.push_back( new GNC3_OPS_Mode_3( pGPC, this ) );
		Modes.push_back( new GNC3_OPS_Mode_4( pGPC, this ) );
		Modes.push_back( new GNC3_OPS_Mode_5( pGPC, this ) );
		return;
	}

	void GNC3_OPS::Init( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS3_INDICATOR, 1 );

		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 1, 18, 3, 2 );
		pGPC->WriteCOMPOOL_A2IS( SCP_CZ1V_SYSUM_PAGE, 1, 2, 0, 3, 2 );

		// handle WRAP_MODE (not sure where it should be)
		if ((pGPC->ReadCOMPOOL_IS( SCP_WRAP_MODE_INIT ) == 1) && (pGPC->ReadCOMPOOL_IS( SCP_TAL_ABORT_DECLARED ) == 0))
		{
			pGPC->WriteCOMPOOL_IS( SCP_WRAP_MODE, 1 );
		}
		else
		{
			pGPC->WriteCOMPOOL_IS( SCP_WRAP_MODE, 0 );
		}

		SCHEDULE( "GNC_HFE" );
		SCHEDULE( "MSC" );
		SCHEDULE( "SF" );
		SCHEDULE( "Elevon_PFB_SOP" );
		SCHEDULE( "BodyFlap_PFB_SOP" );
		SCHEDULE( "Rudder_PFB_SOP" );
		SCHEDULE( "Speedbrake_PFB_SOP" );
		SCHEDULE( "ADTA_SOP" );
		SCHEDULE( "ENT_AREA_NAV" );
		SCHEDULE( "ENT_SITE_LOOKUP" );
		SCHEDULE( "ATT_PROC" );
		SCHEDULE( "HYD_SYS_SOP" );
		SCHEDULE( "Switch_RM" );
		SCHEDULE( "VentCntlSeq" );
		SCHEDULE( "GAX" );
		SCHEDULE( "RCS_ACT_LT" );
		SCHEDULE( "SPI_PROC" );
		SCHEDULE( "MEDSFCGNCXFER" );
		return;
	}

	void GNC3_OPS::CleanUp( void )
	{
		pGPC->WriteCOMPOOL_IS( SCP_OPS3_INDICATOR, 0 );

		CANCEL( "GNC_HFE" );
		CANCEL( "MSC" );
		CANCEL( "SF" );
		CANCEL( "Elevon_PFB_SOP" );
		CANCEL( "BodyFlap_PFB_SOP" );
		CANCEL( "Rudder_PFB_SOP" );
		CANCEL( "Speedbrake_PFB_SOP" );
		CANCEL( "ADTA_SOP" );
		CANCEL( "ENT_AREA_NAV" );
		CANCEL( "ENT_SITE_LOOKUP" );
		CANCEL( "ATT_PROC" );
		CANCEL( "HYD_SYS_SOP" );
		CANCEL( "MPS_ATVC_CMD_SOP" );
		CANCEL( "VentCntlSeq" );
		CANCEL( "GAX" );
		CANCEL( "AMI_PROC" );
		CANCEL( "AVVI_PROC" );
		CANCEL( "HSI_PROC" );
		CANCEL( "HUD_PROC" );
		CANCEL( "Switch_RM" );
		CANCEL( "RCS_ACT_LT" );
		CANCEL( "SPI_PROC" );
		CANCEL( "MEDSFCGNCXFER" );
		return;
	}

	bool GNC3_OPS::OnParseLine( const char* keyword, const char* value )
	{
		return ControlSegmentOPS::OnParseLine( keyword, value );
	}

	void GNC3_OPS::OnSaveState( FILEHANDLE scn ) const
	{
		ControlSegmentOPS::OnSaveState( scn );
		return;
	}
}
