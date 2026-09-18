#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif// _CRT_SECURE_NO_WARNINGS

#include "MC_1.h"
#include "DGO_LDB_COORD.h"
#include "GNC/GNC1_OPS.h"
#include "GNC/GNC6_OPS.h"
#include "GNC/XXXXXX_TRAJ_DIP.h"
#include "GNC/RCS_SPEC.h"
#include "GNC/HORIZ_SIT_SPEC.h"
#include "GNC/HORIZ_SIT_SPEC_FUNC.h"
#include "GNC/OVERRIDE_SPEC.h"
#include "GNC/OVERRIDE_SPEC_FUNC.h"
#include "GNC/CONTROLS_SPEC.h"
#include "GNC/GPS_STATUS_SPEC.h"
#include "GNC/GNC_HFE.h"
#include "GNC/MSC.h"
#include "GNC/SF.h"
#include "GNC/Elevon_PFB_SOP.h"
#include "GNC/BodyFlap_PFB_SOP.h"
#include "GNC/Rudder_PFB_SOP.h"
#include "GNC/Speedbrake_PFB_SOP.h"
#include "GNC/NW_POSN_SOP.h"
#include "GNC/MPS_Dump.h"
#include "GNC/MPS_Dedicated_Display_Driver.h"
#include "GNC/SSME_SOP.h"
#include "GNC/RSLS.h"
#include "GNC/AscentDAP.h"
#include "GNC/ORB_ACTR_SLEW.h"
#include "GNC/SSME_Operations.h"
#include "GNC/ADTA_RM.h"
#include "GNC/ADTA_SOP.h"
#include "GNC/RA_SOP.h"
#include "GNC/ENT_AREA_NAV.h"
#include "GNC/ASC_SITE_LOOKUP.h"
#include "GNC/ASCENT_UPP.h"
#include "GNC/ATT_PROC.h"
#include "GNC/HYD_SYS_SOP.h"
#include "GNC/TransitionDAP.h"
#include "GNC/ETSepSequence.h"
#include "GNC/SRBSepSequence.h"
#include "GNC/MPS_ATVC_CMD_SOP.h"
#include "GNC/SRB_ATVC_CMD_SOP.h"
#include "GNC/MEC_SOP.h"
#include "GNC/RPTA_SOP.h"
#include "GNC/SBTC_SOP.h"
#include "GNC/Switch_RM.h"
#include "GNC/THREE_AX_RHC_SOP.h"
#include "GNC/TWO_AX_RHC_SOP.h"
#include "GNC/BF_Slew_SOP.h"
#include "GNC/Landing_SOP.h"
#include "GNC/OMS_TVC_Feedback_SOP.h"
#include "GNC/OMS_RM.h"
#include "GNC/OMS_TVC_Command_SOP.h"
#include "GNC/PriorityRateLimiting.h"
#include "GNC/Aero_Act_SOP.h"
#include "GNC/DAPLightsDriver.h"
#include "GNC/VentCntlSeq.h"
#include "GNC/GAX.h"
#include "GNC/AMI_PROC.h"
#include "GNC/ASC_ADI_PROC.h"
#include "GNC/EL_ADI_PROC.h"
#include "GNC/AVVI_PROC.h"
#include "GNC/HSI_PROC.h"
#include "GNC/HUD_PROC.h"
#include "GNC/LAMP_PROC.h"
#include "GNC/RCS_ACT_LT.h"
#include "GNC/SPI_PROC.h"
#include "GNC/VERT_SIT_DIP.h"
#include "GNC/MEDSFCGNCXFER.h"
#include "GNC/GNCUtilities.h"


namespace dps
{
	MC_1::MC_1( SimpleGPCSystem* pGPC ):MemoryConfiguration( pGPC, 1 )
	{
		// load AMT
		{
			SCP_MF CDAV_MF;
			// PL
			CDAV_MF.CDAV_MF_NOPS = 0;
			CDAV_MF.CDAV_MF_FOPS = 0;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 1, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
			// GNC
			CDAV_MF.CDAV_MF_NOPS = 2;
			CDAV_MF.CDAV_MF_FOPS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 2, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
			// SM
			CDAV_MF.CDAV_MF_NOPS = 0;
			CDAV_MF.CDAV_MF_FOPS = 0;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 3, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
		}
		{
			SCP_OPS CDAV_OPS;
			SCP_OPNAME CDAV_OPNAME;
			// G1
			CDAV_OPS.CDAV_OP_OPSID = 1;
			CDAV_OPS.CDAV_OP_NMODES = 6;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 2;
			CDAV_OPS.CDAV_OP_NSPEC = 5;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 1, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "GNC1_OPS" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 1, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
			// G6
			CDAV_OPS.CDAV_OP_OPSID = 6;
			CDAV_OPS.CDAV_OP_NMODES = 3;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 15;
			CDAV_OPS.CDAV_OP_NSPEC = 5;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 2, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "GNC6_OPS" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 2, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
		}
		{
			SCP_SPEC CDAV_SPEC;
			SCP_SPNAME CDAV_SPNAME;
			/// G1/G6
			// RCS
			CDAV_SPEC.CDAV_SP_ID = 23;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 1, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RCS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 1, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// HORIZ SIT
			CDAV_SPEC.CDAV_SP_ID = 50;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 2, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "HORIZ_SIT_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 2, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// OVERRIDE
			CDAV_SPEC.CDAV_SP_ID = 51;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 3, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "OVERRIDE_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 3, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// CONTROLS
			CDAV_SPEC.CDAV_SP_ID = 53;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 4, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "CONTROLS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 4, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GPC STATUS
			CDAV_SPEC.CDAV_SP_ID = 55;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 5, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GPS_STATUS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 5, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
		}
		return;
	}

	void MC_1::Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB )
	{
		// fill COMSUB
		vCOMSUB.push_back( new DGO_LDB_COORD( pGPC ) );
		vCOMSUB.push_back( new GNCUtilities( pGPC ) );

		// fill fake DFB
		vDFB.clear();
		vDFB.push_back( 0001 );
		vDFB.push_back( 10 );
		//vDFB.push_back( 20 );
		vDFB.push_back( 60 );
		vDFB.push_back( 990 );

		vDFB.push_back( 1011 );
		vDFB.push_back( 1021 );
		vDFB.push_back( 1031 );
		vDFB.push_back( 1041 );
		vDFB.push_back( 1051 );
		vDFB.push_back( 1061 );
		vDFB.push_back( 6011 );
		vDFB.push_back( 6021 );
		vDFB.push_back( 6031 );
		vDFB.push_back( 18 );
		vDFB.push_back( 23 );
		vDFB.push_back( 50 );
		vDFB.push_back( 51 );
		vDFB.push_back( 53 );
		vDFB.push_back( 55 );
		return;
	}

	bool MC_1::ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name )
	{
		// OPS
		if (!strcmp( name.c_str(), "GNC1_OPS" ))
		{
			vPROGRAM.push_back( new GNC1_OPS( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GNC6_OPS" ))
		{
			vPROGRAM.push_back( new GNC6_OPS( pGPC ) );
		}
		// SPECs
		else if (!strcmp( name.c_str(), "RCS_SPEC" ))
		{
			vPROGRAM.push_back( new RCS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "HORIZ_SIT_SPEC" ))
		{
			vPROGRAM.push_back( new HORIZ_SIT_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OVERRIDE_SPEC" ))
		{
			vPROGRAM.push_back( new OVERRIDE_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "CONTROLS_SPEC" ))
		{
			vPROGRAM.push_back( new CONTROLS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GPS_STATUS_SPEC" ))
		{
			vPROGRAM.push_back( new GPS_STATUS_SPEC( pGPC ) );
		}
		// processes
		else if (!strcmp( name.c_str(), "GNC_HFE" ))
		{
			vPROGRAM.push_back( new GNC_HFE( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MSC" ))
		{
			vPROGRAM.push_back( new MSC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SF" ))
		{
			vPROGRAM.push_back( new SF( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Elevon_PFB_SOP" ))
		{
			vPROGRAM.push_back( new Elevon_PFB_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "BodyFlap_PFB_SOP" ))
		{
			vPROGRAM.push_back( new BodyFlap_PFB_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Rudder_PFB_SOP" ))
		{
			vPROGRAM.push_back( new Rudder_PFB_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Speedbrake_PFB_SOP" ))
		{
			vPROGRAM.push_back( new Speedbrake_PFB_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "NW_POSN_SOP" ))
		{
			vPROGRAM.push_back( new NW_POSN_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MPS_Dump" ))
		{
			vPROGRAM.push_back( new MPS_Dump( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MPS_Dedicated_Display_Driver" ))
		{
			vPROGRAM.push_back( new MPS_Dedicated_Display_Driver( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SSME_Operations" ))
		{
			vPROGRAM.push_back( new SSME_Operations( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RSLS" ))
		{
			vPROGRAM.push_back( new RSLS( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AscentDAP" ))
		{
			vPROGRAM.push_back( new AscentDAP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ORB_ACTR_SLEW" ))
		{
			vPROGRAM.push_back( new ORB_ACTR_SLEW( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SSME_SOP" ))
		{
			vPROGRAM.push_back( new SSME_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ADTA_RM" ))
		{
			vPROGRAM.push_back( new ADTA_RM( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ADTA_SOP" ))
		{
			vPROGRAM.push_back( new ADTA_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RA_SOP" ))
		{
			vPROGRAM.push_back( new RA_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ENT_AREA_NAV" ))
		{
			vPROGRAM.push_back( new ENT_AREA_NAV( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ASC_SITE_LOOKUP" ))
		{
			vPROGRAM.push_back( new ASC_SITE_LOOKUP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ASCENT_UPP" ))
		{
			vPROGRAM.push_back( new ASCENT_UPP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ATT_PROC" ))
		{
			vPROGRAM.push_back( new ATT_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "HYD_SYS_SOP" ))
		{
			vPROGRAM.push_back( new HYD_SYS_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "TransitionDAP" ))
		{
			vPROGRAM.push_back( new TransitionDAP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ETSepSequence" ))
		{
			vPROGRAM.push_back( new ETSepSequence( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SRBSepSequence" ))
		{
			vPROGRAM.push_back( new SRBSepSequence( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MPS_ATVC_CMD_SOP" ))
		{
			vPROGRAM.push_back( new MPS_ATVC_CMD_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SRB_ATVC_CMD_SOP" ))
		{
			vPROGRAM.push_back( new SRB_ATVC_CMD_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MEC_SOP" ))
		{
			vPROGRAM.push_back( new MEC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Landing_SOP" ))
		{
			vPROGRAM.push_back( new Landing_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OMS_TVC_Feedback_SOP" ))// TODO fix naming
		{
			vPROGRAM.push_back( new OMSTVCFDBK_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OMS_RM" ))
		{
			vPROGRAM.push_back( new OMS_RM( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OMS_TVC_Command_SOP" ))// TODO fix naming
		{
			vPROGRAM.push_back( new OMSTVCCMD_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "PriorityRateLimiting" ))
		{
			vPROGRAM.push_back( new PriorityRateLimiting( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Aero_Act_SOP" ))
		{
			vPROGRAM.push_back( new Aero_Act_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RPTA_SOP" ))
		{
			vPROGRAM.push_back( new RPTA_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SBTC_SOP" ))
		{
			vPROGRAM.push_back( new SBTC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Switch_RM" ))
		{
			vPROGRAM.push_back( new Switch_RM( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "THREE_AX_RHC_SOP" ))
		{
			vPROGRAM.push_back( new THREE_AX_RHC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "TWO_AX_RHC_SOP" ))
		{
			vPROGRAM.push_back( new TWO_AX_RHC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "BF_Slew_SOP" ))
		{
			vPROGRAM.push_back( new BF_Slew_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "DAPLightsDriver" ))
		{
			vPROGRAM.push_back( new DAPLightsDriver( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "VentCntlSeq" ))
		{
			vPROGRAM.push_back( new VentCntlSeq( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "XXXXXX_TRAJ_DIP" ))
		{
			vPROGRAM.push_back( new XXXXXX_TRAJ_DIP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "HORIZ_SIT_SPEC_FUNC" ))
		{
			vPROGRAM.push_back( new HORIZ_SIT_SPEC_FUNC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OVERRIDE_SPEC_FUNC" ))
		{
			vPROGRAM.push_back( new OVERRIDE_SPEC_FUNC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GAX" ))
		{
			vPROGRAM.push_back( new GAX( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AMI_PROC" ))
		{
			vPROGRAM.push_back( new AMI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ASC_ADI_PROC" ))
		{
			vPROGRAM.push_back( new ASC_ADI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "EL_ADI_PROC" ))
		{
			vPROGRAM.push_back( new EL_ADI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AVVI_PROC" ))
		{
			vPROGRAM.push_back( new AVVI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "HSI_PROC" ))
		{
			vPROGRAM.push_back( new HSI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "HUD_PROC" ))
		{
			vPROGRAM.push_back( new HUD_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "LAMP_PROC" ))
		{
			vPROGRAM.push_back( new LAMP_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RCS_ACT_LT" ))
		{
			vPROGRAM.push_back( new RCS_ACT_LT( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SPI_PROC" ))
		{
			vPROGRAM.push_back( new SPI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "VERT_SIT_DIP" ))
		{
			vPROGRAM.push_back( new VERT_SIT_DIP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MEDSFCGNCXFER" ))
		{
			vPROGRAM.push_back( new MEDSFCGNCXFER( pGPC ) );
		}
		else return false;

		return true;
	}

	bool MC_1::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short ustmp = 0;
		unsigned short ustmp2 = 0;
		unsigned short ustmp3 = 0;
		float ftmp = 0.0f;

		if (!_strnicmp( keyword, "MM_CODE_101", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_101, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_102", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_102, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_103", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_103, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_104", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_104, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_105", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_105, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_106", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_106, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_601", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_601, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_602", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_602, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_603", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_603, ustmp );
		}
		else if (!_strnicmp( keyword, "OPS1_INDICATOR", 14 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_OPS1_INDICATOR, ustmp );
		}
		else if (!_strnicmp( keyword, "OPS_6_INDICATOR", 15 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_OPS_6_INDICATOR, ustmp );
		}
		else if (!_strnicmp( keyword, "AREA_SEL", 8 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if ((ustmp >= 1) && (ustmp <= 45)) pGPC->WriteCOMPOOL_IS( SCP_AREA_SEL, ustmp );
		}
		else if (!_strnicmp( keyword, "OVHD", 4 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_OVHD, ustmp );
		}
		else if (!_strnicmp( keyword, "IGS", 3 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if ((ustmp >= 1) && (ustmp <= 2)) pGPC->WriteCOMPOOL_IS( SCP_IGS, ustmp );
		}
		else if (!_strnicmp( keyword, "IGI", 3 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if ((ustmp >= 1) && (ustmp <= 2)) pGPC->WriteCOMPOOL_IS( SCP_IGI, ustmp );
		}
		else if (!_strnicmp( keyword, "RUNWAY_NAME_PSL", 15 ))
		{
			pGPC->WriteCOMPOOL_C( SCP_RUNWAY_NAME_PSL, value, 5 );
		}
		else if (!_strnicmp( keyword, "RUNWAY_NAME_SSL", 15 ))
		{
			pGPC->WriteCOMPOOL_C( SCP_RUNWAY_NAME_SSL, value, 5 );
		}
		else if (!_strnicmp( keyword, "RW_SELECT", 9 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_RW_SELECT, ustmp );
		}
		else if (!_strnicmp( keyword, "RW_NAME", 7 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if ((ustmp >= 1) && (ustmp <= 90)) pGPC->WriteCOMPOOL_IS( SCP_RW_NAME, ustmp );
		}
		else if (!_strnicmp( keyword, "SEL_SITE_ID", 11 ))
		{
			pGPC->WriteCOMPOOL_C( SCP_SEL_SITE_ID, value, 5 );
		}
		else if (!_strnicmp( keyword, "ALT_RW", 6 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_ALT_RW, ftmp );
		}
		else if (!_strnicmp( keyword, "AZIMUTH_RW", 10 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_AZIMUTH_RW, ftmp );
		}
		else if (!_strnicmp( keyword, "HUD_RW_LENGTH", 13 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			pGPC->WriteCOMPOOL_IS( SCP_HUD_RW_LENGTH, ustmp );
		}
		else if (!_strnicmp( keyword, "DELH_MSL_ELLIPSOID_RW", 21 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW, ftmp );
		}
		else if (!_strnicmp( keyword, "ANGLE_CORR_TNTOMAG_RW", 21 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW, ftmp );
		}
		else if (!_strnicmp( keyword, "M_EFTORW", 8 ))
		{
			MATRIX3 mtmp;
			sscanf_s( value, "%lf%lf%lf%lf%lf%lf%lf%lf%lf", &mtmp.m11, &mtmp.m12, &mtmp.m13, &mtmp.m21, &mtmp.m22, &mtmp.m23, &mtmp.m31, &mtmp.m32, &mtmp.m33 );
			pGPC->WriteCOMPOOL_MS( SCP_M_EFTORW, mtmp );
		}
		else if (!_strnicmp( keyword, "R_LS_EF", 7 ))
		{
			VECTOR3 vtmp;
			sscanf_s( value, "%lf%lf%lf", &vtmp.x, &vtmp.y, &vtmp.z );
			pGPC->WriteCOMPOOL_VD( SCP_R_LS_EF, vtmp );
		}
		else if (!_strnicmp( keyword, "M_EFTOTD_RW", 11 ))
		{
			MATRIX3 mtmp;
			sscanf_s( value, "%lf%lf%lf%lf%lf%lf%lf%lf%lf", &mtmp.m11, &mtmp.m12, &mtmp.m13, &mtmp.m21, &mtmp.m22, &mtmp.m23, &mtmp.m31, &mtmp.m32, &mtmp.m33 );
			pGPC->WriteCOMPOOL_MS( SCP_M_EFTOTD_RW, mtmp );
		}
		else if (!_strnicmp( keyword, "R_CC_L_PRI", 10 ))
		{
			VECTOR3 vtmp;
			sscanf_s( value, "%lf%lf%lf", &vtmp.x, &vtmp.y, &vtmp.z );
			pGPC->WriteCOMPOOL_VS( SCP_R_CC_L_PRI, vtmp );
		}
		else if (!_strnicmp( keyword, "R_CC_R_PRI", 10 ))
		{
			VECTOR3 vtmp;
			sscanf_s( value, "%lf%lf%lf", &vtmp.x, &vtmp.y, &vtmp.z );
			pGPC->WriteCOMPOOL_VS( SCP_R_CC_R_PRI, vtmp );
		}
		else if (!_strnicmp( keyword, "R_CC_LMAG_PRI", 13 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_R_CC_LMAG_PRI, ftmp );
		}
		else if (!_strnicmp( keyword, "R_CC_RMAG_PRI", 13 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_R_CC_RMAG_PRI, ftmp );
		}
		else if (!_strnicmp( keyword, "RW_ID_UPP", 9 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			pGPC->WriteCOMPOOL_IS( SCP_RW_ID_UPP, ustmp );
		}
		else if (!_strnicmp( keyword, "R_NEP", 5 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_R_NEP, ftmp );
		}
		else if (!_strnicmp( keyword, "RETRACT_BF", 10 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_RETRACT_BF, ustmp );
		}
		else if (!_strnicmp( keyword, "WOWLON_IND", 10 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_WOWLON_IND, ustmp );
		}
		else if (!_strnicmp( keyword, "FLATTURN_CMD", 12 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_FLATTURN_CMD, ustmp );
		}
		else if (!_strnicmp( keyword, "ROLLOUT_IND", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_ROLLOUT_IND, ustmp );
		}
		else if (!_strnicmp( keyword, "GSENBL", 6 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_GSENBL, ustmp );
		}
		else if (!_strnicmp( keyword, "HUD_WOWLON", 10 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_HUD_WOWLON, ustmp );
		}
		else if (!_strnicmp( keyword, "HUD_ROLLOUT", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, ustmp );
		}
		else if (!_strnicmp( keyword, "P_MODE", 6 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 4) pGPC->WriteCOMPOOL_IS( SCP_P_MODE, ustmp );
		}
		else if (!_strnicmp( keyword, "IPHASE", 6 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 3) pGPC->WriteCOMPOOL_IS( SCP_IPHASE, ustmp );
		}
		else if (!_strnicmp( keyword, "TG_END", 6 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_TG_END, ustmp );
		}
		else if (!_strnicmp( keyword, "ISLECT", 6 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if ((ustmp >= 1) && (ustmp <= 5)) pGPC->WriteCOMPOOL_IS( SCP_ISLECT, ustmp );
		}
		else if (!_strnicmp( keyword, "DLRDOT", 6 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_DLRDOT, ftmp );
		}
		else if (!_strnicmp( keyword, "NEP_FB", 6 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_NEP_FB, ustmp );
		}
		else if (!_strnicmp( keyword, "YSGNP", 5 ))
		{
			sscanf_s( value, "%f", &ftmp );
			if ((ftmp == 1.0) || (ftmp == -1.0)) pGPC->WriteCOMPOOL_SS( SCP_YSGNP, ftmp );
		}
		else if (!_strnicmp( keyword, "RF", 2 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_RF, ftmp );
		}
		else if (!_strnicmp( keyword, "PSHA", 4 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_PSHA, ftmp );
		}
		else if (!_strnicmp( keyword, "RTURN", 5 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_RTURN, ftmp );
		}
		else if (!_strnicmp( keyword, "XHAC", 4 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_XHAC, ftmp );
		}
		else if (!_strnicmp( keyword, "WRAP_MODE", 9 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_WRAP_MODE, ustmp );
		}
		else if (!_strnicmp( keyword, "VENT_DOOR_SEQ_INIT", 19 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, ustmp );
		}
		else if (!_strnicmp( keyword, "ALL_VENT_CLOSE_CMD", 18 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, ustmp );
		}
		else if (!_strnicmp( keyword, "VENT_CMDS_TIME_DELAY", 20 ))
		{
			double tmp = 0;
			sscanf_s( value, "%lf", &tmp );
			pGPC->WriteCOMPOOL_SD( SCP_VENT_CMDS_TIME_DELAY, tmp );
		}
		else if (!_strnicmp( keyword, "ME_CMD_PATH_FAIL", 16 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "ME_ELEC_LOCKUP", 14 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "ME_FLT_DATA_PATH_FAIL", 21 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "ME_HYD_LOCKUP", 13 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "ME_LIM_EX", 9 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_LIM_EX, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_LIM_EX, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_LIM_EX, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "ME_READY", 8 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_READY, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_READY, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_ME_READY, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "MEPSTSHDN", 9 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_MEPSTSHDN, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_MEPSTSHDN, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_MEPSTSHDN, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "MESHDN", 3 ))
		{
			sscanf_s( value, "%hu %hu %hu", &ustmp, &ustmp2, &ustmp3 );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_AIS( SCP_MESHDN, 1, ustmp, 3 );
			if (ustmp2 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_MESHDN, 2, ustmp2, 3 );
			if (ustmp3 <= 1) pGPC->WriteCOMPOOL_AIS( SCP_MESHDN, 3, ustmp3, 3 );
		}
		else if (!_strnicmp( keyword, "ME1_FAIL_SHUTDOWN", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN, ustmp );
		}
		else if (!_strnicmp( keyword, "ME2_FAIL_SHUTDOWN", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN, ustmp );
		}
		else if (!_strnicmp( keyword, "ME3_FAIL_SHUTDOWN", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN, ustmp );
		}
		else if (!_strnicmp( keyword, "MECO_CMD", 8 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MECO_CMD, ustmp );
		}
		else if (!_strnicmp( keyword, "MECO_CONFIRMED", 14 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MECO_CONFIRMED, ustmp );
		}
		else if (!_strnicmp( keyword, "OMSL_ACT_SEL", 12 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			pGPC->WriteCOMPOOL_IS( SCP_OMSL_ACT_SEL, ustmp );
		}
		else if (!_strnicmp( keyword, "OMSR_ACT_SEL", 12 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			pGPC->WriteCOMPOOL_IS( SCP_OMSR_ACT_SEL, ustmp );
		}
		else if (!_strnicmp( keyword, "PRED_GMT_LO", 11 ))
		{
			double tmp = 0;
			sscanf_s( value, "%lf", &tmp );
			pGPC->WriteCOMPOOL_SD( SCP_PRED_GMT_LO, tmp );
		}
		else if (!_strnicmp( keyword, "ABT_THROT_CMD", 13 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_ABT_THROT_CMD, ustmp );
		}
		else if (!_strnicmp( keyword, "NOM_THROT_CMD", 13 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_NOM_THROT_CMD, ustmp );
		}
		else if (!_strnicmp( keyword, "MAX_THROT_CMD", 13 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MAX_THROT_CMD, ustmp );
		}
		else if (!_strnicmp( keyword, "RETURN_SSME_TO_START_POS", 24 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS, ustmp );
		}
		else if (!_strnicmp( keyword, "PREP_SSMES", 10 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_PREP_SSMES, ustmp );
		}
		else if (!_strnicmp( keyword, "AERO_SLEW_CMPL", 14 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_AERO_SLEW_CMPL, ustmp );
		}
		else if (!_strnicmp( keyword, "MPS_SLEW_COMPLETE", 17 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE, ustmp );
		}
		else if (!_strnicmp( keyword, "SCP_AERO_SLEW_CMD", 17 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_AERO_SLEW_CMD, ftmp );
		}
		else if (!_strnicmp( keyword, "MPS_SLEW_CMD", 12 ))
		{
			sscanf_s( value, "%f", &ftmp );
			pGPC->WriteCOMPOOL_SS( SCP_MPS_SLEW_CMD, ftmp );
		}
		else return false;

		return true;
	}

	void MC_1::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[256];

		oapiWriteScenario_int( scn, "MM_CODE_101", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_101 ) );
		oapiWriteScenario_int( scn, "MM_CODE_102", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_102 ) );
		oapiWriteScenario_int( scn, "MM_CODE_103", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_103 ) );
		oapiWriteScenario_int( scn, "MM_CODE_104", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_104 ) );
		oapiWriteScenario_int( scn, "MM_CODE_105", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_105 ) );
		oapiWriteScenario_int( scn, "MM_CODE_106", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_106 ) );
		oapiWriteScenario_int( scn, "MM_CODE_601", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_601 ) );
		oapiWriteScenario_int( scn, "MM_CODE_602", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_602 ) );
		oapiWriteScenario_int( scn, "MM_CODE_603", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_603 ) );
		oapiWriteScenario_int( scn, "OPS1_INDICATOR", pGPC->ReadCOMPOOL_IS( SCP_OPS1_INDICATOR ) );
		oapiWriteScenario_int( scn, "OPS_6_INDICATOR", pGPC->ReadCOMPOOL_IS( SCP_OPS_6_INDICATOR ) );

		oapiWriteScenario_int( scn, "OVHD", pGPC->ReadCOMPOOL_IS( SCP_OVHD ) );
		oapiWriteScenario_int( scn, "IGS", pGPC->ReadCOMPOOL_IS( SCP_IGS ) );
		oapiWriteScenario_int( scn, "IGI", pGPC->ReadCOMPOOL_IS( SCP_IGI ) );

		oapiWriteScenario_int( scn, "AREA_SEL", pGPC->ReadCOMPOOL_IS( SCP_AREA_SEL ) );

		memset( cbuf, 0, 6 );
		pGPC->ReadCOMPOOL_C( SCP_RUNWAY_NAME_PSL, cbuf, 5 );
		oapiWriteScenario_string( scn, "RUNWAY_NAME_PSL", cbuf );

		memset( cbuf, 0, 6 );
		pGPC->ReadCOMPOOL_C( SCP_RUNWAY_NAME_SSL, cbuf, 5 );
		oapiWriteScenario_string( scn, "RUNWAY_NAME_SSL", cbuf );

		oapiWriteScenario_int( scn, "RW_SELECT", pGPC->ReadCOMPOOL_IS( SCP_RW_SELECT ) );
		oapiWriteScenario_int( scn, "RW_NAME", pGPC->ReadCOMPOOL_IS( SCP_RW_NAME ) );

		memset( cbuf, 0, 6 );
		pGPC->ReadCOMPOOL_C( SCP_SEL_SITE_ID, cbuf, 5 );
		oapiWriteScenario_string( scn, "SEL_SITE_ID", cbuf );

		oapiWriteScenario_float( scn, "ALT_RW", pGPC->ReadCOMPOOL_SS( SCP_ALT_RW ) );
		oapiWriteScenario_float( scn, "AZIMUTH_RW", pGPC->ReadCOMPOOL_SS( SCP_AZIMUTH_RW ) );
		oapiWriteScenario_int( scn, "HUD_RW_LENGTH", pGPC->ReadCOMPOOL_IS( SCP_HUD_RW_LENGTH ) );
		oapiWriteScenario_float( scn, "DELH_MSL_ELLIPSOID_RW", pGPC->ReadCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW ) );
		oapiWriteScenario_float( scn, "ANGLE_CORR_TNTOMAG_RW", pGPC->ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW ) );

		MATRIX3 mtmp = pGPC->ReadCOMPOOL_MS( SCP_M_EFTORW );
		sprintf_s( cbuf, 256, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", mtmp.m11, mtmp.m12, mtmp.m13, mtmp.m21, mtmp.m22, mtmp.m23, mtmp.m31, mtmp.m32, mtmp.m33 );
		oapiWriteScenario_string( scn, "M_EFTORW", cbuf );

		oapiWriteScenario_vec( scn, "R_LS_EF", pGPC->ReadCOMPOOL_VD( SCP_R_LS_EF ) );

		mtmp = pGPC->ReadCOMPOOL_MS( SCP_M_EFTOTD_RW );
		sprintf_s( cbuf, 256, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", mtmp.m11, mtmp.m12, mtmp.m13, mtmp.m21, mtmp.m22, mtmp.m23, mtmp.m31, mtmp.m32, mtmp.m33 );
		oapiWriteScenario_string( scn, "M_EFTOTD_RW", cbuf );

		oapiWriteScenario_vec( scn, "R_CC_L_PRI", pGPC->ReadCOMPOOL_VS( SCP_R_CC_L_PRI ) );
		oapiWriteScenario_vec( scn, "R_CC_R_PRI", pGPC->ReadCOMPOOL_VS( SCP_R_CC_R_PRI ) );

		oapiWriteScenario_float( scn, "R_CC_LMAG_PRI", pGPC->ReadCOMPOOL_SS( SCP_R_CC_LMAG_PRI ) );
		oapiWriteScenario_float( scn, "R_CC_RMAG_PRI", pGPC->ReadCOMPOOL_SS( SCP_R_CC_RMAG_PRI ) );

		oapiWriteScenario_int( scn, "RW_ID_UPP", pGPC->ReadCOMPOOL_IS( SCP_RW_ID_UPP ) );
		oapiWriteScenario_float( scn, "R_NEP", pGPC->ReadCOMPOOL_SS( SCP_R_NEP ) );

		oapiWriteScenario_int( scn, "RETRACT_BF", pGPC->ReadCOMPOOL_IS( SCP_RETRACT_BF ) );

		oapiWriteScenario_int( scn, "WOWLON_IND", pGPC->ReadCOMPOOL_IS( SCP_WOWLON_IND ) );
		oapiWriteScenario_int( scn, "FLATTURN_CMD", pGPC->ReadCOMPOOL_IS( SCP_FLATTURN_CMD ) );
		oapiWriteScenario_int( scn, "ROLLOUT_IND", pGPC->ReadCOMPOOL_IS( SCP_ROLLOUT_IND ) );
		oapiWriteScenario_int( scn, "GSENBL", pGPC->ReadCOMPOOL_IS( SCP_GSENBL ) );
		oapiWriteScenario_int( scn, "HUD_WOWLON", pGPC->ReadCOMPOOL_IS( SCP_HUD_WOWLON ) );
		oapiWriteScenario_int( scn, "HUD_ROLLOUT", pGPC->ReadCOMPOOL_IS( SCP_HUD_ROLLOUT ) );

		oapiWriteScenario_int( scn, "P_MODE", pGPC->ReadCOMPOOL_IS( SCP_P_MODE ) );

		oapiWriteScenario_int( scn, "IPHASE", pGPC->ReadCOMPOOL_IS( SCP_IPHASE ) );
		oapiWriteScenario_int( scn, "TG_END", pGPC->ReadCOMPOOL_IS( SCP_TG_END ) );

		oapiWriteScenario_int( scn, "ISLECT", pGPC->ReadCOMPOOL_IS( SCP_ISLECT ) );
		oapiWriteScenario_float( scn, "DLRDOT", pGPC->ReadCOMPOOL_SS( SCP_DLRDOT ) );

		oapiWriteScenario_int( scn, "NEP_FB", pGPC->ReadCOMPOOL_IS( SCP_NEP_FB ) );
		oapiWriteScenario_float( scn, "YSGNP", pGPC->ReadCOMPOOL_SS( SCP_YSGNP ) );
		oapiWriteScenario_float( scn, "RF", pGPC->ReadCOMPOOL_SS( SCP_RF ) );
		oapiWriteScenario_float( scn, "PSHA", pGPC->ReadCOMPOOL_SS( SCP_PSHA ) );
		oapiWriteScenario_float( scn, "RTURN", pGPC->ReadCOMPOOL_SS( SCP_RTURN ) );
		oapiWriteScenario_float( scn, "XHAC", pGPC->ReadCOMPOOL_SS( SCP_XHAC ) );

		oapiWriteScenario_int( scn, "WRAP_MODE", pGPC->ReadCOMPOOL_IS( SCP_WRAP_MODE ) );

		oapiWriteScenario_int( scn, "VENT_DOOR_SEQ_INIT", pGPC->ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) );
		oapiWriteScenario_int( scn, "ALL_VENT_CLOSE_CMD", pGPC->ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) );
		oapiWriteScenario_float( scn, "VENT_CMDS_TIME_DELAY", pGPC->ReadCOMPOOL_SD( SCP_VENT_CMDS_TIME_DELAY ) );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_CMD_PATH_FAIL", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_ELEC_LOCKUP", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_FLT_DATA_PATH_FAIL", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_HYD_LOCKUP", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_ME_LIM_EX, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_LIM_EX, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_LIM_EX, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_LIM_EX", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_ME_READY, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_READY, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_ME_READY, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_READY", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 3, 3 ) );
		oapiWriteScenario_string( scn, "MEPSTSHDN", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", pGPC->ReadCOMPOOL_AIS( SCP_MESHDN, 1, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_MESHDN, 2, 3 ), pGPC->ReadCOMPOOL_AIS( SCP_MESHDN, 3, 3 ) );
		oapiWriteScenario_string( scn, "MESHDN", cbuf );

		oapiWriteScenario_int( scn, "ME1_FAIL_SHUTDOWN", pGPC->ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) );
		oapiWriteScenario_int( scn, "ME2_FAIL_SHUTDOWN", pGPC->ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) );
		oapiWriteScenario_int( scn, "ME3_FAIL_SHUTDOWN", pGPC->ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) );

		oapiWriteScenario_int( scn, "MECO_CMD", pGPC->ReadCOMPOOL_IS( SCP_MECO_CMD ) );
		oapiWriteScenario_int( scn, "MECO_CONFIRMED", pGPC->ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) );

		oapiWriteScenario_int( scn, "OMSL_ACT_SEL", pGPC->ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL ) );
		oapiWriteScenario_int( scn, "OMSR_ACT_SEL", pGPC->ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL ) );

		oapiWriteScenario_float( scn, "PRED_GMT_LO", pGPC->ReadCOMPOOL_SD( SCP_PRED_GMT_LO ) );
		
		oapiWriteScenario_int( scn, "ABT_THROT_CMD", pGPC->ReadCOMPOOL_IS( SCP_ABT_THROT_CMD ) );
		oapiWriteScenario_int( scn, "NOM_THROT_CMD", pGPC->ReadCOMPOOL_IS( SCP_NOM_THROT_CMD ) );
		oapiWriteScenario_int( scn, "MAX_THROT_CMD", pGPC->ReadCOMPOOL_IS( SCP_MAX_THROT_CMD ) );

		oapiWriteScenario_int( scn, "RETURN_SSME_TO_START_POS", pGPC->ReadCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS ) );
		oapiWriteScenario_int( scn, "PREP_SSMES", pGPC->ReadCOMPOOL_IS( SCP_PREP_SSMES ) );
		oapiWriteScenario_int( scn, "AERO_SLEW_CMPL", pGPC->ReadCOMPOOL_IS( SCP_AERO_SLEW_CMPL ) );
		oapiWriteScenario_int( scn, "MPS_SLEW_COMPLETE", pGPC->ReadCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE ) );
		oapiWriteScenario_float( scn, "AERO_SLEW_CMD", pGPC->ReadCOMPOOL_SS( SCP_AERO_SLEW_CMD ) );
		oapiWriteScenario_float( scn, "MPS_SLEW_CMD", pGPC->ReadCOMPOOL_SS( SCP_MPS_SLEW_CMD ) );
		return;
	}
}
