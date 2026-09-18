#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif// _CRT_SECURE_NO_WARNINGS

#include "MC_3.h"
#include "GNC/GNC3_OPS.h"
#include "GNC/IMU_ALIGN_SPEC.h"
#include "GNC/S_TRK_COAS_CNTL_SPEC.h"
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
#include "GNC/ADTA_RM.h"
#include "GNC/ADTA_SOP.h"
#include "GNC/RA_SOP.h"
#include "GNC/ENT_AREA_NAV.h"
#include "GNC/ENT_SITE_LOOKUP.h"
#include "GNC/ATT_PROC.h"
#include "GNC/H_HDOT_ACCVERT.h"
#include "GNC/GUIDECOMP.h"
#include "GNC/Entry_UPP.h"
#include "GNC/TAEM_UPP.h"
#include "GNC/AL_UPP.h"
#include "GNC/EntryGuidance.h"
#include "GNC/TAEMGuidance.h"
#include "GNC/AutolandGuidance.h"
#include "GNC/HYD_SYS_SOP.h"
#include "GNC/AerojetDAP.h"
#include "GNC/MPS_ATVC_CMD_SOP.h"
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
#include "GNC/JetSelectionLogic.h"
#include "GNC/PriorityRateLimiting.h"
#include "GNC/Aero_Act_SOP.h"
#include "GNC/DAPLightsDriver.h"
#include "GNC/VentCntlSeq.h"
#include "GNC/GAX.h"
#include "GNC/AMI_PROC.h"
#include "GNC/EL_ADI_PROC.h"
#include "GNC/AVVI_PROC.h"
#include "GNC/HSI_PROC.h"
#include "GNC/HUD_PROC.h"
#include "GNC/LAMP_PROC.h"
#include "GNC/RCS_ACT_LT.h"
#include "GNC/SPI_PROC.h"
#include "GNC/ENT_DIP.h"
#include "GNC/VERT_SIT_DIP.h"
#include "GNC/MEDSFCGNCXFER.h"
#include "GNC/GNCUtilities.h"


namespace dps
{
	MC_3::MC_3( SimpleGPCSystem* pGPC ):MemoryConfiguration( pGPC, 3 )
	{
		// load AMT
		{
			SCP_MF CDAV_MF;
			// PL
			CDAV_MF.CDAV_MF_NOPS = 0;
			CDAV_MF.CDAV_MF_FOPS = 0;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 1, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
			// GNC
			CDAV_MF.CDAV_MF_NOPS = 1;
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
			// G3
			CDAV_OPS.CDAV_OP_OPSID = 3;
			CDAV_OPS.CDAV_OP_NMODES = 5;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 10;
			CDAV_OPS.CDAV_OP_NSPEC = 7;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 1, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "GNC3_OPS" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 1, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
		}
		{
			SCP_SPEC CDAV_SPEC;
			SCP_SPNAME CDAV_SPNAME;
			// IMU ALIGN
			CDAV_SPEC.CDAV_SP_ID = 21;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 1, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "IMU_ALIGN_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 1, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// S TRK/COAS CNTL
			CDAV_SPEC.CDAV_SP_ID = 22;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 2, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "S_TRK_COAS_CNTL_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 2, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// RCS
			CDAV_SPEC.CDAV_SP_ID = 23;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 3, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RCS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 3, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// HORIZ SIT
			CDAV_SPEC.CDAV_SP_ID = 50;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 4, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "HORIZ_SIT_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 4, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// OVERRIDE
			CDAV_SPEC.CDAV_SP_ID = 51;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 5, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "OVERRIDE_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 5, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// CONTROLS
			CDAV_SPEC.CDAV_SP_ID = 53;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 6, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "CONTROLS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 6, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GPC STATUS
			CDAV_SPEC.CDAV_SP_ID = 55;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 7, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GPS_STATUS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 7, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
		}
		return;
	}

	void MC_3::Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB )
	{
		// fill COMSUB
		vCOMSUB.push_back( new GNCUtilities( pGPC ) );

		// fill fake DFB
		vDFB.clear();
		vDFB.push_back( 0001 );
		vDFB.push_back( 10 );
		//vDFB.push_back( 20 );
		vDFB.push_back( 60 );
		vDFB.push_back( 990 );

		vDFB.push_back( 3011 );
		vDFB.push_back( 3021 );
		vDFB.push_back( 3031 );
		vDFB.push_back( 3041 );
		vDFB.push_back( 3051 );
		vDFB.push_back( 18 );
		vDFB.push_back( 21 );
		vDFB.push_back( 22 );// 301
		vDFB.push_back( 23 );
		vDFB.push_back( 50 );
		vDFB.push_back( 51 );
		vDFB.push_back( 53 );
		vDFB.push_back( 55 );
		return;
	}

	bool MC_3::ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name )
	{
		// OPS
		if (!strcmp( name.c_str(), "GNC3_OPS" ))
		{
			vPROGRAM.push_back( new GNC3_OPS( pGPC ) );
		}
		// SPECs
		else if (!strcmp( name.c_str(), "IMU_ALIGN_SPEC" ))
		{
			vPROGRAM.push_back( new IMU_ALIGN_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "S_TRK_COAS_CNTL_SPEC" ))
		{
			vPROGRAM.push_back( new S_TRK_COAS_CNTL_SPEC( pGPC ) );
		}
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
		else if (!strcmp( name.c_str(), "ENT_SITE_LOOKUP" ))
		{
			vPROGRAM.push_back( new ENT_SITE_LOOKUP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ATT_PROC" ))
		{
			vPROGRAM.push_back( new ATT_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "H_HDOT_ACCVERT" ))
		{
			vPROGRAM.push_back( new H_HDOT_ACCVERT( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GUIDECOMP" ))
		{
			vPROGRAM.push_back( new GUIDECOMP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Entry_UPP" ))
		{
			vPROGRAM.push_back( new Entry_UPP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "TAEM_UPP" ))
		{
			vPROGRAM.push_back( new TAEM_UPP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AL_UPP" ))
		{
			vPROGRAM.push_back( new AL_UPP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "EntryGuidance" ))
		{
			vPROGRAM.push_back( new EntryGuidance( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "TAEMGuidance" ))
		{
			vPROGRAM.push_back( new TAEMGuidance( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AutolandGuidance" ))
		{
			vPROGRAM.push_back( new AutolandGuidance( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "HYD_SYS_SOP" ))
		{
			vPROGRAM.push_back( new HYD_SYS_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AerojetDAP" ))
		{
			vPROGRAM.push_back( new AerojetDAP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MPS_ATVC_CMD_SOP" ))
		{
			vPROGRAM.push_back( new MPS_ATVC_CMD_SOP( pGPC ) );
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
		else if (!strcmp( name.c_str(), "OMS_TVC_Command_SOP" ))
		{
			vPROGRAM.push_back( new OMSTVCCMD_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "JetSelectionLogic" ))
		{
			vPROGRAM.push_back( new JetSelectionLogic( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "PriorityRateLimiting" ))
		{
			vPROGRAM.push_back( new PriorityRateLimiting( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Aero_Act_SOP" ))
		{
			vPROGRAM.push_back( new Aero_Act_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "DAPLightsDriver" ))
		{
			vPROGRAM.push_back( new DAPLightsDriver( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "VentCntlSeq" ))
		{
			vPROGRAM.push_back( new VentCntlSeq( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GAX" ))
		{
			vPROGRAM.push_back( new GAX( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "AMI_PROC" ))
		{
			vPROGRAM.push_back( new AMI_PROC( pGPC ) );
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
		else if (!strcmp( name.c_str(), "HORIZ_SIT_SPEC_FUNC" ))
		{
			vPROGRAM.push_back( new HORIZ_SIT_SPEC_FUNC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OVERRIDE_SPEC_FUNC" ))
		{
			vPROGRAM.push_back( new OVERRIDE_SPEC_FUNC( pGPC ) );
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
		else if (!strcmp( name.c_str(), "ENT_DIP" ))
		{
			vPROGRAM.push_back( new ENT_DIP( pGPC ) );
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

	bool MC_3::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short ustmp = 0;
		unsigned short ustmp2 = 0;
		unsigned short ustmp3 = 0;
		float ftmp = 0.0f;

		if (!_strnicmp( keyword, "MM_CODE_301", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_301, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_302", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_302, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_303", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_303, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_304", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_304, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_CODE_305", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_305, ustmp );
		}
		else if (!_strnicmp( keyword, "OPS3_INDICATOR", 14 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_OPS3_INDICATOR, ustmp );
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
		else return false;

		return true;
	}

	void MC_3::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[256];

		oapiWriteScenario_int( scn, "MM_CODE_301", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_301 ) );
		oapiWriteScenario_int( scn, "MM_CODE_302", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_302 ) );
		oapiWriteScenario_int( scn, "MM_CODE_303", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_303 ) );
		oapiWriteScenario_int( scn, "MM_CODE_304", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_304 ) );
		oapiWriteScenario_int( scn, "MM_CODE_305", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_305 ) );
		oapiWriteScenario_int( scn, "OPS3_INDICATOR", pGPC->ReadCOMPOOL_IS( SCP_OPS3_INDICATOR ) );

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
		
		oapiWriteScenario_int( scn, "ABT_THROT_CMD", pGPC->ReadCOMPOOL_IS( SCP_ABT_THROT_CMD ) );
		oapiWriteScenario_int( scn, "NOM_THROT_CMD", pGPC->ReadCOMPOOL_IS( SCP_NOM_THROT_CMD ) );
		oapiWriteScenario_int( scn, "MAX_THROT_CMD", pGPC->ReadCOMPOOL_IS( SCP_MAX_THROT_CMD ) );
		return;
	}
}
