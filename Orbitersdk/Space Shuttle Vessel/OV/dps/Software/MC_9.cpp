#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif// _CRT_SECURE_NO_WARNINGS

#include "MC_9.h"
#include "GNC/GPS_STATUS_SPEC.h"
#include "DGO_LDB_COORD.h"
#include "GNC/GNC9_OPS.h"
#include "GNC/MSC.h"
#include "GNC/SF.h"
#include "GNC/MPS_ATVC_CMD_SOP.h"
#include "GNC/Switch_RM.h"
#include "GNC/OMS_TVC_Feedback_SOP.h"
#include "GNC/GNC_HFE.h"
#include "GNC/GAX.h"
#include "GNC/MEDSFCGNCXFER.h"
#include "GNC/GNCUtilities.h"


namespace dps
{
	MC_9::MC_9( SimpleGPCSystem* pGPC ):MemoryConfiguration( pGPC, 9 )
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
			// G9
			CDAV_OPS.CDAV_OP_OPSID = 9;
			CDAV_OPS.CDAV_OP_NMODES = 1;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 19;
			CDAV_OPS.CDAV_OP_NSPEC = 8;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 1, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "GNC9_OPS" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 1, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
		}
		{
			SCP_SPEC CDAV_SPEC;
			SCP_SPNAME CDAV_SPNAME;
			// GPS STATUS
			CDAV_SPEC.CDAV_SP_ID = 55;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 1, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GPS_STATUS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 1, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GTS DISPLAY
			CDAV_SPEC.CDAV_SP_ID = 100;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 2, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GTS_DISPLAY_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 2, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// SENSOR SELF-TEST
			CDAV_SPEC.CDAV_SP_ID = 101;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 3, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "SENSOR_SELF_TEST_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 3, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// RCS/RGA/ADTA TEST
			CDAV_SPEC.CDAV_SP_ID = 102;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 4, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RCS_RGA_ADTA_TEST_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 4, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GND IMU CNTL/MON
			CDAV_SPEC.CDAV_SP_ID = 104;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 5, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GND_IMU_CNTL_MON_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 5, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// TCS CONTROL
			CDAV_SPEC.CDAV_SP_ID = 105;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 6, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "TCS_CONTROL_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 6, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GPC/BUT I/F
			CDAV_SPEC.CDAV_SP_ID = 112;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 7, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GPC_BUT_IF_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 7, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// ACTUATOR CONTROL
			CDAV_SPEC.CDAV_SP_ID = 113;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 8, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "ACTUATOR_CONTROL_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 8, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
		}
		return;
	}

	void MC_9::Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB )
	{
		// fill COMSUB
		vCOMSUB.push_back( new DGO_LDB_COORD( pGPC ) );
		vCOMSUB.push_back( new GNCUtilities( pGPC ) );

		// fill fake DFB
		vDFB.clear();
		vDFB.push_back( 0001 );
		vDFB.push_back( 10 );
		vDFB.push_back( 20 );
		vDFB.push_back( 60 );
		vDFB.push_back( 990 );

		vDFB.push_back( 9011 );
		vDFB.push_back( 55 );
		vDFB.push_back( 62 );
		vDFB.push_back( 100 );
		vDFB.push_back( 101 );
		vDFB.push_back( 102 );
		vDFB.push_back( 104 );
		vDFB.push_back( 105 );
		vDFB.push_back( 106 );
		vDFB.push_back( 110 );
		vDFB.push_back( 112 );
		vDFB.push_back( 113 );
		return;
	}

	bool MC_9::ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name )
	{
		// OPS
		if (!strcmp( name.c_str(), "GNC9_OPS" ))
		{
			vPROGRAM.push_back( new GNC9_OPS( pGPC ) );
		}
		// SPECs
		else if (!strcmp( name.c_str(), "GPS_STATUS_SPEC" ))
		{
			vPROGRAM.push_back( new GPS_STATUS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GTS_DISPLAY_SPEC" ))
		{
			//vPROGRAM.push_back( new GTS_DISPLAY_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SENSOR_SELF_TEST_SPEC" ))
		{
			//vPROGRAM.push_back( new SENSOR_SELF_TEST_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RCS_RGA_ADTA_TEST_SPEC" ))
		{
			//vPROGRAM.push_back( new RCS_RGA_ADTA_TEST_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GND_IMU_CNTL_MON_SPEC" ))
		{
			//vPROGRAM.push_back( new GND_IMU_CNTL_MON_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "TCS_CONTROL_SPEC" ))
		{
			//vPROGRAM.push_back( new TCS_CONTROL_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GPC_BUT_IF_SPEC" ))
		{
			//vPROGRAM.push_back( new GPC_BUT_IF_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ACTUATOR_CONTROL_SPEC" ))
		{
			//vPROGRAM.push_back( new ACTUATOR_CONTROL_SPEC( pGPC ) );
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
		else if (!strcmp( name.c_str(), "MPS_ATVC_CMD_SOP" ))
		{
			vPROGRAM.push_back( new MPS_ATVC_CMD_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Switch_RM" ))
		{
			vPROGRAM.push_back( new Switch_RM( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OMS_TVC_Feedback_SOP" ))// TODO fix naming
		{
			vPROGRAM.push_back( new OMSTVCFDBK_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GAX" ))
		{
			vPROGRAM.push_back( new GAX( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MEDSFCGNCXFER" ))
		{
			vPROGRAM.push_back( new MEDSFCGNCXFER( pGPC ) );
		}
		else return false;

		return true;
	}

	bool MC_9::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void MC_9::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}
