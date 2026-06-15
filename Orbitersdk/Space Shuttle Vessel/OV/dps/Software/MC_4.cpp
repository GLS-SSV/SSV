#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif// _CRT_SECURE_NO_WARNINGS

#include "MC_4.h"
#include "SM/SM2_OPS.h"
#include "SM/SSP_EXEC.h"
#include "SM/SSD_SP_DATA_ACQ.h"
#include "SM/SSB_PL_BAY_DOORS.h"
#include "SM/SSO_SP_DATA_OUT.h"
#include "SM/RMC_SPEC.h"


namespace dps
{
	MC_4::MC_4( SimpleGPCSystem* pGPC ):MemoryConfiguration( pGPC, 4 )
	{
		// load AMT
		{
			SCP_MF CDAV_MF;
			// PL
			CDAV_MF.CDAV_MF_NOPS = 0;
			CDAV_MF.CDAV_MF_FOPS = 0;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 1, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
			// GNC
			CDAV_MF.CDAV_MF_NOPS = 0;
			CDAV_MF.CDAV_MF_FOPS = 0;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 2, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
			// SM
			CDAV_MF.CDAV_MF_NOPS = 1;
			CDAV_MF.CDAV_MF_FOPS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_MF, 3, &CDAV_MF, sizes_MF, pos_MF, cnt_MF, 3 );
		}
		{
			SCP_OPS CDAV_OPS;
			SCP_OPNAME CDAV_OPNAME;
			// S2
			CDAV_OPS.CDAV_OP_OPSID = 2;
			CDAV_OPS.CDAV_OP_NMODES = 2;
			CDAV_OPS.CDAV_OP_MODXXFR_ST = 20;
			CDAV_OPS.CDAV_OP_NSPEC = 7;
			CDAV_OPS.CDAV_OP_SPEC_ST = 1;
			CDAV_OPS.CDAV_OP_XFR = 1;//////////
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPS, 1, &CDAV_OPS, sizes_OPS, pos_OPS, cnt_OPS, 6 );
			strcpy( CDAV_OPNAME.CDAV_OP_PROGNM, "SM2_OPS" );// HACK unknown name
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_OPNAME, 1, &CDAV_OPNAME, sizes_OPNAME, pos_OPNAME, cnt_OPNAME, 6 );
		}
		{
			SCP_SPEC CDAV_SPEC;
			SCP_SPNAME CDAV_SPNAME;
			// SM TABLE MAINT
			CDAV_SPEC.CDAV_SP_ID = 60;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 1, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "STS_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 1, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// PCMMU/PL COMM
			CDAV_SPEC.CDAV_SP_ID = 62;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 2, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "PCMMU_PL_COMM_SPEC" );// HACK unknown name
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 2, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// SM GROUND CHECKOUT
			CDAV_SPEC.CDAV_SP_ID = 64;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 3, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "SM_GROUND_CHECKOUT_SPEC" );// HACK unknown name
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 3, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// MASS MEMORY R/W
			CDAV_SPEC.CDAV_SP_ID = 85;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 4, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "MASS_MEMORY_RW_SPEC" );// HACK unknown name
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 4, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// PCS CONTROL
			CDAV_SPEC.CDAV_SP_ID = 90;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 5, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "PCS_CONTROL_SPEC" );// HACK unknown name
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 5, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// PDRS CONTROL
			CDAV_SPEC.CDAV_SP_ID = 94;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 6, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "RMC_SPEC" );
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 6, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );
			// PDRS OVERRIDE
			CDAV_SPEC.CDAV_SP_ID = 95;
			CDAV_SPEC.CDAV_SP_BLOCKS = 1;
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPEC, 7, &CDAV_SPEC, sizes_SPEC, pos_SPEC, cnt_SPEC, 12 );
			strcpy( CDAV_SPNAME.CDAV_SP_SPECNM, "PDRS_OVERRIDE_SPEC" );// HACK unknown name
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CDAV_SPNAME, 7, &CDAV_SPNAME, sizes_SPNAME, pos_SPNAME, cnt_SPNAME, 12 );

			// TODO
			/*
			200	PL (SPEC 1)	IUS
			201	PL (SPEC 2)	PAM DEPLOY
			202	PL (SPEC 3)	PAM DEPLOY
			203	PL (SPEC 4)	PAM DEPLOY
			204	PL (SPEC 5)	PAM DEPLOY
			205	PL (SPEC 6)	HST SYS
			210	PL (SPEC 7)	PAM CONTROL
			211	PL (SPEC 8)	PAM CONTROL
			212	PL (SPEC 9)	PAM CONTROL
			213	PL (SPEC 10)	PAM CONTROL
			214	PL (SPEC 11)
			215	PL (SPEC 12)
			220	PL (SPEC 13)
			221	PL (SPEC 14)
			222	PL (SPEC 15)
			223	PL (SPEC 16)
			224	PL (SPEC 17)
			225	PL (SPEC 18)
			*/
		}
		return;
	}

	void MC_4::Init( std::vector<SimpleGPCSoftware*>& vCOMSUB, std::vector<unsigned short>& vDFB )
	{
		// fill COMSUB
		vCOMSUB.push_back( new SSD_SP_DATA_ACQ( pGPC ) );
		vCOMSUB.push_back( new SSO_SP_DATA_OUT( pGPC ) );
		vCOMSUB.push_back( new SSB_PL_BAY_DOORS( pGPC ) );

		// fill fake DFB
		vDFB.clear();
		vDFB.push_back( 0001 );
		vDFB.push_back( 1 );
		vDFB.push_back( 2 );
		vDFB.push_back( 6 );
		vDFB.push_back( 99 );

		vDFB.push_back( 2011 );
		vDFB.push_back( 2021 );
		vDFB.push_back( 60 );
		vDFB.push_back( 62 );
		vDFB.push_back( 64 );
		vDFB.push_back( 66 );
		vDFB.push_back( 67 );
		vDFB.push_back( 68 );
		vDFB.push_back( 69 );
		vDFB.push_back( 76 );
		vDFB.push_back( 78 );
		vDFB.push_back( 79 );
		vDFB.push_back( 85 );
		vDFB.push_back( 86 );
		vDFB.push_back( 87 );
		vDFB.push_back( 88 );
		vDFB.push_back( 89 );
		vDFB.push_back( 90 );
		vDFB.push_back( 94 );
		vDFB.push_back( 95 );
		vDFB.push_back( 96 );
		vDFB.push_back( 97 );
		vDFB.push_back( 98 );
		vDFB.push_back( 167 );
		vDFB.push_back( 168 );
		vDFB.push_back( 169 );
		vDFB.push_back( 177 );
		vDFB.push_back( 179 );
		return;
	}

	bool MC_4::ScheduleProgram( std::vector<SimpleGPCSoftware*>& vPROGRAM, const std::string& name )
	{
		// OPS
		if (!strcmp( name.c_str(), "SM2_OPS" ))
		{
			vPROGRAM.push_back( new SM2_OPS( pGPC ) );
		}
		// SPECs
		else if (!strcmp( name.c_str(), "STS_SPEC" ))
		{
			//vPROGRAM.push_back( new STS_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "PCMMU_PL_COMM_SPEC" ))
		{
			//vPROGRAM.push_back( new PCMMU_PL_COMM_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "SM_GROUND_CHECKOUT_SPEC" ))
		{
			//vPROGRAM.push_back( new SM_GROUND_CHECKOUT_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "MASS_MEMORY_RW_SPEC" ))
		{
			//vPROGRAM.push_back( new MASS_MEMORY_RW_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "PCS_CONTROL_SPEC" ))
		{
			//vPROGRAM.push_back( new PCS_CONTROL_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "RMC_SPEC" ))
		{
			vPROGRAM.push_back( new RMC_SPEC( pGPC ) );
		}
		else if (!strcmp( name.c_str(), "PDRS_OVERRIDE_SPEC" ))
		{
			//vPROGRAM.push_back( new PDRS_OVERRIDE_SPEC( pGPC ) );
		}
		// processes
		else if (!strcmp( name.c_str(), "SSP_EXEC" ))
		{
			vPROGRAM.push_back( new SSP_EXEC( pGPC ) );
		}
		else return false;

		return true;
	}

	bool MC_4::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "CSBB_AUTO_MODE_ITEM", 19 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_MANUAL_MODE_ITEMS", 21 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_POWER_ON_OFF_ITEM", 22 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_SWITCH_BYPASS_ITEM", 23 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_PBD_OPEN_ITEM", 18 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_PBD_STOP_ITEM", 18 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_PBD_CLOSE_ITEM", 19 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_OPEN_FAIL_INDICATOR", 24 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_CLOSE_FAIL_INDICATOR", 25 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_AUTO_MODE_FLAG", 19 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, tmp );
		}
		else if (!_strnicmp( keyword, "CSBB_MANUAL_MODE_FLAG", 21 ))
		{
			unsigned short tmp = 0;
			sscanf_s( value, "%hu", &tmp );
			pGPC->WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG, tmp );
		}
		return false;
	}

	void MC_4::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "CSBB_AUTO_MODE_ITEM", pGPC->ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_MANUAL_MODE_ITEMS", pGPC->ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEMS ) );
		oapiWriteScenario_int( scn, "CSBB_POWER_ON_OFF_ITEM", pGPC->ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_SWITCH_BYPASS_ITEM", pGPC->ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_PBD_OPEN_ITEM", pGPC->ReadCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_PBD_STOP_ITEM", pGPC->ReadCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_PBD_CLOSE_ITEM", pGPC->ReadCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_OPEN_FAIL_INDICATOR", pGPC->ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) );
		oapiWriteScenario_int( scn, "CSBB_CLOSE_FAIL_INDICATOR", pGPC->ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) );
		oapiWriteScenario_int( scn, "CSBB_AUTO_MODE_FLAG", pGPC->ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG ) );
		oapiWriteScenario_int( scn, "CSBB_MANUAL_MODE_FLAG", pGPC->ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG ) );
		return;
	}
}
