#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif// _CRT_SECURE_NO_WARNINGS

#include "MC_8.h"
#include "GNC/GNC8_OPS.h"
#include "GNC/RCS_SPEC.h"
#include "GNC/SENSOR_TEST_SPEC.h"
#include "GNC/RGA_ADTA_RCS_SPEC.h"
#include "GNC/SWITCH_SURF_SPEC.h"
#include "GNC/CONTROLLERS_SPEC.h"
#include "GNC/SWITCHES_SPEC.h"
#include "GNC/NWS_CHECK_SPEC.h"
#include "GNC/GPS_STATUS_SPEC.h"
#include "GNC/GNC_HFE.h"
#include "GNC/MSC.h"
#include "GNC/SF.h"
#include "GNC/Elevon_PFB_SOP.h"
#include "GNC/BodyFlap_PFB_SOP.h"
#include "GNC/Rudder_PFB_SOP.h"
#include "GNC/Speedbrake_PFB_SOP.h"
#include "GNC/NW_POSN_SOP.h"
#include "GNC/RA_SOP.h"
#include "GNC/ATT_PROC_ORBIT.h"
#include "GNC/MM801.h"
#include "GNC/SBTC_SOP.h"
#include "GNC/Switch_RM.h"
#include "GNC/THC_SOP.h"
#include "GNC/OMS_TVC_Feedback_SOP.h"
#include "GNC/Aero_Act_SOP.h"
#include "GNC/GAX.h"
#include "GNC/DAPLightsDriver.h"
#include "GNC/ORB_ADI_PROC.h"
#include "GNC/RCS_ACT_LT.h"
#include "GNC/MEDSFCGNCXFER.h"
#include "GNC/GNCUtilities.h"


namespace dps
{
	MC_8::MC_8( SimpleGPCSystem* pGPC ):MemoryConfiguration( pGPC, 8 )
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
			// G8
			CDAV_OPS.CDAV_OP_OPSID = 8;
			CDAV_OPS.CDAV_OP_NMODES = 1;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 18;
			CDAV_OPS.CDAV_OP_NSPEC = 8;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 1, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "GNC8_OPS" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 1, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
		}
		{
			SCP_SPEC CDAV_SPEC;
			SCP_SPNAME CDAV_SPNAME;
			// RCS
			CDAV_SPEC.CDAV_SP_ID = 23;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 1, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RCS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 1, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// SENSOR TEST
			CDAV_SPEC.CDAV_SP_ID = 40;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 2, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "SENSOR_TEST_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 2, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// RGA/ADTA/RCS
			CDAV_SPEC.CDAV_SP_ID = 41;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 3, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RGA_ADTA_RCS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 3, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// SWITCH/SURF
			CDAV_SPEC.CDAV_SP_ID = 42;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 4, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "SWITCH_SURF_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 4, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// CONTROLLERS
			CDAV_SPEC.CDAV_SP_ID = 43;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 5, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "CONTROLLERS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 5, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// SWITCHES
			CDAV_SPEC.CDAV_SP_ID = 44;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 6, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "SWITCHES_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 6, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// NWS CHECK
			CDAV_SPEC.CDAV_SP_ID = 45;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 7, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "NWS_CHECK_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 7, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// GPS STATUS
			CDAV_SPEC.CDAV_SP_ID = 55;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 8, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "GPS_STATUS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 8, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
		}
		return;
	}

	void MC_8::Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB )
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

		vDFB.push_back( 8011 );
		vDFB.push_back( 18 );
		vDFB.push_back( 19 );
		vDFB.push_back( 23 );
		vDFB.push_back( 40 );
		vDFB.push_back( 41 );
		vDFB.push_back( 42 );
		vDFB.push_back( 43 );
		vDFB.push_back( 44 );
		vDFB.push_back( 45 );
		vDFB.push_back( 55 );
		return;
	}

	bool MC_8::ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name )
	{
		// OPS
		if (!strcmp( name.c_str(), "GNC8_OPS" ))
		{
			vPROGRAM.push_back( new GNC8_OPS( pGPC ) );
		}
		// SPECs
		else if (!strcmp( name.c_str(), "RCS_SPEC" ))
		{
			vPROGRAM.push_back( new RCS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SENSOR_TEST_SPEC" ))
		{
			vPROGRAM.push_back( new SENSOR_TEST_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RGA_ADTA_RCS_SPEC" ))
		{
			vPROGRAM.push_back( new RGA_ADTA_RCS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SWITCH_SURF_SPEC" ))
		{
			vPROGRAM.push_back( new SWITCH_SURF_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "CONTROLLERS_SPEC" ))
		{
			vPROGRAM.push_back( new CONTROLLERS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SWITCHES_SPEC" ))
		{
			vPROGRAM.push_back( new SWITCHES_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "NWS_CHECK_SPEC" ))
		{
			vPROGRAM.push_back( new NWS_CHECK_SPEC( pGPC ) );
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
		else if (!strcmp( name.c_str(), "RA_SOP" ))
		{
			vPROGRAM.push_back( new RA_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "ATT_PROC_ORBIT" ))
		{
			vPROGRAM.push_back( new ATT_PROC_ORBIT( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MM801" ))
		{
			vPROGRAM.push_back( new MM801( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SBTC_SOP" ))
		{
			vPROGRAM.push_back( new SBTC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Switch_RM" ))
		{
			vPROGRAM.push_back( new Switch_RM( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "THC_SOP" ))
		{
			vPROGRAM.push_back( new THC_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "OMS_TVC_Feedback_SOP" ))// TODO fix naming
		{
			vPROGRAM.push_back( new OMSTVCFDBK_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "Aero_Act_SOP" ))
		{
			vPROGRAM.push_back( new Aero_Act_SOP( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "GAX" ))
		{
			vPROGRAM.push_back( new GAX( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "DAPLightsDriver" ))
		{
			vPROGRAM.push_back( new DAPLightsDriver( pGPC ) );
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

	bool MC_8::OnParseLine( const char* keyword, const char* value )
	{
		unsigned short ustmp = 0;

		if (!_strnicmp( keyword, "MM_801_FROM_MM_201", 18 ))
		{
			sscanf_s( value, "%hu", &ustmp );
			if (ustmp <= 1) pGPC->WriteCOMPOOL_IS( SCP_MM_801_FROM_MM_201, ustmp );
		}
		else return false;

		return true;
	}

	void MC_8::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "MM_801_FROM_MM_201", pGPC->ReadCOMPOOL_IS( SCP_MM_801_FROM_MM_201 ) );
		return;
	}
}
