#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif// _CRT_SECURE_NO_WARNINGS

#include "MC_2.h"
#include "GNC/GNC2_OPS.h"
#include "GNC/DAP_CONFIG_SPEC.h"
#include "GNC/IMU_ALIGN_SPEC.h"
#include "GNC/S_TRK_COAS_CNTL_SPEC.h"
#include "GNC/RCS_SPEC.h"
#include "GNC/RM_ORBIT_SPEC.h"
#include "GNC/REL_NAV_SPEC.h"
#include "GNC/ORBIT_TGT_SPEC.h"
#include "GNC/GPS_STATUS_SPEC.h"
#include "GNC/GNC_HFE.h"
#include "GNC/MSC.h"
#include "GNC/SF.h"
#include "GNC/ATT_PROC_ORBIT.h"
#include "GNC/Switch_RM.h"
#include "GNC/THC_SOP.h"
#include "GNC/ORB_THREE_AX_RHC_SOP.h"
#include "GNC/OMS_TVC_Feedback_SOP.h"
#include "GNC/OMS_RM.h"
#include "GNC/OMS_TVC_Command_SOP.h"
#include "GNC/DAPLightsDriver.h"
#include "GNC/GAX.h"
#include "GNC/ORB_ADI_PROC.h"
#include "GNC/RCS_ACT_LT.h"
#include "GNC/MEDSFCGNCXFER.h"
#include "GNC/GNCUtilities.h"


namespace dps
{
	MC_2::MC_2( SimpleGPCSystem* pGPC ):MemoryConfiguration( pGPC, 2 )
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
			// G2
			CDAV_OPS.CDAV_OP_OPSID = 2;
			CDAV_OPS.CDAV_OP_NMODES = 2;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 8;
			CDAV_OPS.CDAV_OP_NSPEC = 8;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 1, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "GNC2_OPS" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 1, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
		}
		{
			SCP_SPEC CDAV_SPEC;
			SCP_SPNAME CDAV_SPNAME;
			// DAP CONFIG
			CDAV_SPEC.CDAV_SP_ID = 20;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 1, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "DAP_CONFIG_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 1, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// IMU ALIGN
			CDAV_SPEC.CDAV_SP_ID = 21;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 2, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "IMU_ALIGN_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 2, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// S TRK/COAS CNTL
			CDAV_SPEC.CDAV_SP_ID = 22;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 3, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "S_TRK_COAS_CNTL_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 3, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// RCS
			CDAV_SPEC.CDAV_SP_ID = 23;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 4, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RCS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 4, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// RM ORBIT
			CDAV_SPEC.CDAV_SP_ID = 25;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 5, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RM_ORBIT_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 5, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// REL NAV
			CDAV_SPEC.CDAV_SP_ID = 33;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 6, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "REL_NAV_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 6, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// ORBIT TGT
			CDAV_SPEC.CDAV_SP_ID = 34;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 7, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "ORBIT_TGT_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 7, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GPC STATUS
			CDAV_SPEC.CDAV_SP_ID = 55;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 8, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GPS_STATUS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 8, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
		}
		return;
	}

	void MC_2::Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB )
	{
		// fill COMSUB
		vCOMSUB.push_back( new GNCUtilities( pGPC ) );

		// fill fake DFB
		vDFB.clear();
		vDFB.push_back( 0001 );
		vDFB.push_back( 10 );
		vDFB.push_back( 20 );
		vDFB.push_back( 60 );
		vDFB.push_back( 990 );

		vDFB.push_back( 2011 );
		vDFB.push_back( 2021 );
		vDFB.push_back( 18 );
		vDFB.push_back( 19 );
		vDFB.push_back( 20 );
		vDFB.push_back( 21 );
		vDFB.push_back( 22 );
		vDFB.push_back( 23 );
		vDFB.push_back( 25 );
		vDFB.push_back( 33 );
		vDFB.push_back( 34 );
		vDFB.push_back( 55 );
		return;
	}

	bool MC_2::ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name )
	{
		// OPS
		if (!strcmp( name.c_str(), "GNC2_OPS" ))
		{
			vPROGRAM.push_back( new GNC2_OPS( pGPC ) );
		}
		// SPECs
		else if (!strcmp( name.c_str(), "DAP_CONFIG_SPEC" ))
		{
			vPROGRAM.push_back( new DAP_CONFIG_SPEC( pGPC ) );
		}
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
		else if (!strcmp( name.c_str(), "RM_ORBIT_SPEC" ))
		{
			vPROGRAM.push_back( new RM_ORBIT_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "REL_NAV_SPEC" ))
		{
			vPROGRAM.push_back( new REL_NAV_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ORBIT_TGT_SPEC" ))
		{
			vPROGRAM.push_back( new ORBIT_TGT_SPEC( pGPC ) );
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
		else if (!strcmp( name.c_str(), "ATT_PROC_ORBIT" ))
		{
			vPROGRAM.push_back( new ATT_PROC_ORBIT( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Switch_RM" ))
		{
			vPROGRAM.push_back( new Switch_RM( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "THC_SOP" ))
		{
			vPROGRAM.push_back( new THC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ORB_THREE_AX_RHC_SOP" ))
		{
			vPROGRAM.push_back( new ORB_THREE_AX_RHC_SOP( pGPC ) );
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
		else if (!strcmp( name.c_str(), "DAPLightsDriver" ))
		{
			vPROGRAM.push_back( new DAPLightsDriver( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GAX" ))
		{
			vPROGRAM.push_back( new GAX( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ORB_ADI_PROC" ))
		{
			vPROGRAM.push_back( new ORB_ADI_PROC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RCS_ACT_LT" ))
		{
			vPROGRAM.push_back( new RCS_ACT_LT( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MEDSFCGNCXFER" ))
		{
			vPROGRAM.push_back( new MEDSFCGNCXFER( pGPC ) );
		}
		else return false;

		return true;
	}

	bool MC_2::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short ustmp = 0;

		if (!_strnicmp( keyword, "MM_CODE_201", 11 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_CODE_201, ustmp );
		}
		else if (!_strnicmp( keyword, "MM_202_FROM_MM_201_FLAG", 23 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_202_FROM_MM_201_FLAG, ustmp );
		}
		else if (!_strnicmp( keyword, "OPS_2_INDICATOR", 15 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_OPS_2_INDICATOR, ustmp );
		}
		else return false;

		return true;
	}

	void MC_2::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "MM_CODE_201", pGPC->ReadCOMPOOL_IS( SCP_MM_CODE_201 ) );
		oapiWriteScenario_int( scn, "MM_202_FROM_MM_201_FLAG", pGPC->ReadCOMPOOL_IS( SCP_MM_202_FROM_MM_201_FLAG ) );
		oapiWriteScenario_int( scn, "OPS_2_INDICATOR", pGPC->ReadCOMPOOL_IS( SCP_OPS_2_INDICATOR ) );
		return;
	}
}
