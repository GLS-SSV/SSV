#include "VentCntlSeq.h"
#include "ETSepSequence.h"
#include "..\Atlantis.h"


namespace dps
{
	// K-LOADS
	constexpr double GROUND_REL_VEL_THRESHOLD = 2400.0;// [fps]
	constexpr double HE_PURGE_TIME = 650.0;// [s]
	constexpr double HE_PURGE_VEL = 4500.0;// [fps]

	VentCntlSeq::VentCntlSeq( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "VentCntlSeq" ),
		VENT_CMDS_TIME_DELAY(2.56),
		et_umb_dr_timer(-1.0), he_purge_timer(-1.0),
		timerA(-1.0), timerB(-1.0), timerC(-1.0), timerD(-1.0), timerE(-1.0), timerF(-1.0), timerG(-1.0), timerH(-1.0), timerJ(-1.0), timerK(-1.0), timerL(-1.0), timerM(-1.0), timerN(-1.0), timerP(-1.0), timerQ(-1.0),
		timera(-1.0), timerb(-1.0), timerc(-1.0), timerd(-1.0), timere(-1.0), timerf(-1.0), timerg(-1.0), timerh(-1.0), timerj(-1.0), timerk(-1.0), timerl(-1.0), timerm(-1.0),
		firstpass2(true), firstpass2a_1(true), firstpass2a_2(true), firstpass2a_3(true), firstpass2a_4(true), firstpass2a_5(true),
		firstpass3_1(true), firstpass3_2(true), firstpass4(true), firstpass5(true), firstpass6(true),
		firstpass8_1(true), firstpass8_2(true), firstpass8_3(true), firstpass8_4(true), firstpass8_5(true), firstpass8_6(true), firstpass8_7(true),
		firstpass9_1(true), firstpass9_2(true), firstpass9_3(true), firstpass9_4(true), firstpass9_5(true), firstpass9_6(true), firstpass9_7(true),
		LEFT_VENTS_1_AND_6_OPEN_FLAG(false),
		L_FWD_VENTS_12_OPEN_CMD(false), L_PB_VENT_3_OPEN_CMD(false), L_PB_VENT_5_OPEN_CMD(false), L_PBW_VENTS_47_OPEN_CMD(false), L_PB_VENT_6_OPEN_CMD(false), L_AFT_VENTS_89_OPEN_CMD(false),
		R_FWD_VENTS_12_OPEN_CMD(false), R_PB_VENT_3_OPEN_CMD(false), R_PB_VENT_5_OPEN_CMD(false), R_PBW_VENTS_47_OPEN_CMD(false), R_PB_VENT_6_OPEN_CMD(false), R_AFT_VENTS_89_OPEN_CMD(false),
		L_FWD_VENTS_12_CLOSE_CMD(false), L_PB_VENT_3_CLOSE_CMD(false), L_PB_VENT_5_CLOSE_CMD(false), L_PBW_VENTS_47_CLOSE_CMD(false), L_PB_VENT_6_CLOSE_CMD(false), L_AFT_VENTS_89_CLOSE_CMD(false),
		R_FWD_VENTS_12_CLOSE_CMD(false), R_PB_VENT_3_CLOSE_CMD(false), R_PB_VENT_5_CLOSE_CMD(false), R_PBW_VENTS_47_CLOSE_CMD(false), R_PB_VENT_6_CLOSE_CMD(false), R_AFT_VENTS_89_CLOSE_CMD(false)
	{
		// TODO VENT_CMDS_TIME_DELAY i-load
		return;
	}

	VentCntlSeq::~VentCntlSeq( void )
	{
		return;
	}

	void VentCntlSeq::Realize( void )
	{
		pETSepSequence = dynamic_cast<ETSepSequence*>(FindSoftware( "ETSepSequence" ));
		assert( (pETSepSequence != NULL) && "VentCntlSeq::Realize.pETSepSequence" );
		return;
	}

	bool VentCntlSeq::OnParseLine( const char* keyword, const char* value )
	{
		if (!_stricmp( keyword, "VENT_CMDS_TIME_DELAY" ))
		{
			sscanf_s( value, "%lf", &VENT_CMDS_TIME_DELAY );
			return true;
		}
		else if (!_stricmp( keyword, "et_umb_dr_timer" ))
		{
			sscanf_s( value, "%lf", &et_umb_dr_timer );
			return true;
		}
		else if (!_stricmp( keyword, "he_purge_timer" ))
		{
			sscanf_s( value, "%lf", &he_purge_timer );
			return true;
		}
		else if (!_stricmp( keyword, "timerA" ))
		{
			sscanf_s( value, "%lf", &timerA );
			return true;
		}
		else if (!_stricmp( keyword, "timera" ))
		{
			sscanf_s( value, "%lf", &timera );
			return true;
		}
		else if (!_stricmp( keyword, "timerB" ))
		{
			sscanf_s( value, "%lf", &timerB );
			return true;
		}
		else if (!_stricmp( keyword, "timerb" ))
		{
			sscanf_s( value, "%lf", &timerb );
			return true;
		}
		else if (!_stricmp( keyword, "timerC" ))
		{
			sscanf_s( value, "%lf", &timerC );
			return true;
		}
		else if (!_stricmp( keyword, "timerc" ))
		{
			sscanf_s( value, "%lf", &timerc );
			return true;
		}
		else if (!_stricmp( keyword, "timerD" ))
		{
			sscanf_s( value, "%lf", &timerD );
			return true;
		}
		else if (!_stricmp( keyword, "timerd" ))
		{
			sscanf_s( value, "%lf", &timerd );
			return true;
		}
		else if (!_stricmp( keyword, "timerE" ))
		{
			sscanf_s( value, "%lf", &timerE );
			return true;
		}
		else if (!_stricmp( keyword, "timere" ))
		{
			sscanf_s( value, "%lf", &timere );
			return true;
		}
		else if (!_stricmp( keyword, "timerF" ))
		{
			sscanf_s( value, "%lf", &timerF );
			return true;
		}
		else if (!_stricmp( keyword, "timerf" ))
		{
			sscanf_s( value, "%lf", &timerf );
			return true;
		}
		else if (!_stricmp( keyword, "timerG" ))
		{
			sscanf_s( value, "%lf", &timerG );
			return true;
		}
		else if (!_stricmp( keyword, "timerg" ))
		{
			sscanf_s( value, "%lf", &timerg );
			return true;
		}
		else if (!_stricmp( keyword, "timerH" ))
		{
			sscanf_s( value, "%lf", &timerH );
			return true;
		}
		else if (!_stricmp( keyword, "timerh" ))
		{
			sscanf_s( value, "%lf", &timerh );
			return true;
		}
		else if (!_stricmp( keyword, "timerJ" ))
		{
			sscanf_s( value, "%lf", &timerJ );
			return true;
		}
		else if (!_stricmp( keyword, "timerj" ))
		{
			sscanf_s( value, "%lf", &timerj );
			return true;
		}
		else if (!_stricmp( keyword, "timerK" ))
		{
			sscanf_s( value, "%lf", &timerK );
			return true;
		}
		else if (!_stricmp( keyword, "timerk" ))
		{
			sscanf_s( value, "%lf", &timerk );
			return true;
		}
		else if (!_stricmp( keyword, "timerL" ))
		{
			sscanf_s( value, "%lf", &timerL );
			return true;
		}
		else if (!_stricmp( keyword, "timerl" ))
		{
			sscanf_s( value, "%lf", &timerl );
			return true;
		}
		else if (!_stricmp( keyword, "timerM" ))
		{
			sscanf_s( value, "%lf", &timerM );
			return true;
		}
		else if (!_stricmp( keyword, "timerm" ))
		{
			sscanf_s( value, "%lf", &timerm );
			return true;
		}
		else if (!_stricmp( keyword, "timerN" ))
		{
			sscanf_s( value, "%lf", &timerN );
			return true;
		}
		else if (!_stricmp( keyword, "timerP" ))
		{
			sscanf_s( value, "%lf", &timerP );
			return true;
		}
		else if (!_stricmp( keyword, "timerQ" ))
		{
			sscanf_s( value, "%lf", &timerQ );
			return true;
		}
		else if (!_stricmp( keyword, "firstpass2" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass2 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass2a_1" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass2a_1 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass2a_2" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass2a_2 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass2a_3" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass2a_3 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass2a_4" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass2a_4 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass2a_5" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass2a_5 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass3_1" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass3_1 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass3_2" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass3_2 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass4" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass4 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass5" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass5 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass6" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass6 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_1" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_1 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_2" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_2 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_3" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_3 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_4" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_4 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_5" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_5 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_6" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_6 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass8_7" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass8_7 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_1" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_1 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_2" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_2 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_3" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_3 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_4" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_4 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_5" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_5 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_6" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_6 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "firstpass9_7" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			firstpass9_7 = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "LEFT_VENTS_1_AND_6_OPEN_FLAG" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			LEFT_VENTS_1_AND_6_OPEN_FLAG = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_FWD_VENTS_12_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_FWD_VENTS_12_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PB_VENT_3_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PB_VENT_3_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PB_VENT_5_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PB_VENT_5_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PBW_VENTS_47_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PBW_VENTS_47_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PB_VENT_6_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PB_VENT_6_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_AFT_VENTS_89_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_AFT_VENTS_89_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_FWD_VENTS_12_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_FWD_VENTS_12_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PB_VENT_3_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PB_VENT_3_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PB_VENT_5_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PB_VENT_5_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PBW_VENTS_47_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PBW_VENTS_47_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PB_VENT_6_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PB_VENT_6_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_AFT_VENTS_89_OPEN_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_AFT_VENTS_89_OPEN_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_FWD_VENTS_12_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_FWD_VENTS_12_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PB_VENT_3_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PB_VENT_3_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PB_VENT_5_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PB_VENT_5_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PBW_VENTS_47_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PBW_VENTS_47_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_PB_VENT_6_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_PB_VENT_6_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "L_AFT_VENTS_89_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			L_AFT_VENTS_89_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_FWD_VENTS_12_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_FWD_VENTS_12_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PB_VENT_3_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PB_VENT_3_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PB_VENT_5_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PB_VENT_5_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PBW_VENTS_47_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PBW_VENTS_47_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_PB_VENT_6_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_PB_VENT_6_CLOSE_CMD = (tmp == 1);
			return true;
		}
		else if (!_stricmp( keyword, "R_AFT_VENTS_89_CLOSE_CMD" ))
		{
			int tmp = 0;
			sscanf_s( value, "%d", &tmp );
			R_AFT_VENTS_89_CLOSE_CMD = (tmp == 1);
			return true;
		}
		return false;
	}

	void VentCntlSeq::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_float( scn, "VENT_CMDS_TIME_DELAY", VENT_CMDS_TIME_DELAY );
		oapiWriteScenario_float( scn, "et_umb_dr_timer", et_umb_dr_timer );
		oapiWriteScenario_float( scn, "he_purge_timer", he_purge_timer );
		oapiWriteScenario_float( scn, "timerA", timerA );
		oapiWriteScenario_float( scn, "timera", timera );
		oapiWriteScenario_float( scn, "timerB", timerB );
		oapiWriteScenario_float( scn, "timerb", timerb );
		oapiWriteScenario_float( scn, "timerC", timerC );
		oapiWriteScenario_float( scn, "timerc", timerc );
		oapiWriteScenario_float( scn, "timerD", timerD );
		oapiWriteScenario_float( scn, "timerd", timerd );
		oapiWriteScenario_float( scn, "timerE", timerE );
		oapiWriteScenario_float( scn, "timere", timere );
		oapiWriteScenario_float( scn, "timerF", timerF );
		oapiWriteScenario_float( scn, "timerf", timerf );
		oapiWriteScenario_float( scn, "timerG", timerG );
		oapiWriteScenario_float( scn, "timerg", timerg );
		oapiWriteScenario_float( scn, "timerH", timerH );
		oapiWriteScenario_float( scn, "timerh", timerh );
		oapiWriteScenario_float( scn, "timerJ", timerJ );
		oapiWriteScenario_float( scn, "timerj", timerj );
		oapiWriteScenario_float( scn, "timerK", timerK );
		oapiWriteScenario_float( scn, "timerk", timerk );
		oapiWriteScenario_float( scn, "timerL", timerL );
		oapiWriteScenario_float( scn, "timerl", timerl );
		oapiWriteScenario_float( scn, "timerM", timerM );
		oapiWriteScenario_float( scn, "timerm", timerm );
		oapiWriteScenario_float( scn, "timerN", timerN );
		oapiWriteScenario_float( scn, "timerP", timerP );
		oapiWriteScenario_float( scn, "timerQ", timerQ );
		oapiWriteScenario_int( scn, "firstpass2", firstpass2 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass2a_1", firstpass2a_1 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass2a_2", firstpass2a_2 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass2a_3", firstpass2a_3 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass2a_4", firstpass2a_4 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass2a_5", firstpass2a_5 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass3_1", firstpass3_1 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass3_2", firstpass3_2 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass4", firstpass4 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass5", firstpass5 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass6", firstpass6 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_1", firstpass8_1 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_2", firstpass8_2 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_3", firstpass8_3 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_4", firstpass8_4 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_5", firstpass8_5 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_6", firstpass8_6 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass8_7", firstpass8_7 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_1", firstpass9_1 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_2", firstpass9_2 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_3", firstpass9_3 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_4", firstpass9_4 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_5", firstpass9_5 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_6", firstpass9_6 ? 1 : 0 );
		oapiWriteScenario_int( scn, "firstpass9_7", firstpass9_7 ? 1 : 0 );
		oapiWriteScenario_int( scn, "LEFT_VENTS_1_AND_6_OPEN_FLAG", LEFT_VENTS_1_AND_6_OPEN_FLAG ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_FWD_VENTS_12_OPEN_CMD", L_FWD_VENTS_12_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PB_VENT_3_OPEN_CMD", L_PB_VENT_3_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PB_VENT_5_OPEN_CMD", L_PB_VENT_5_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PBW_VENTS_47_OPEN_CMD", L_PBW_VENTS_47_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PB_VENT_6_OPEN_CMD", L_PB_VENT_6_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_AFT_VENTS_89_OPEN_CMD", L_AFT_VENTS_89_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_FWD_VENTS_12_OPEN_CMD", R_FWD_VENTS_12_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PB_VENT_3_OPEN_CMD", R_PB_VENT_3_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PB_VENT_5_OPEN_CMD", R_PB_VENT_5_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PBW_VENTS_47_OPEN_CMD", R_PBW_VENTS_47_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PB_VENT_6_OPEN_CMD", R_PB_VENT_6_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_AFT_VENTS_89_OPEN_CMD", R_AFT_VENTS_89_OPEN_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_FWD_VENTS_12_CLOSE_CMD", L_FWD_VENTS_12_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PB_VENT_3_CLOSE_CMD", L_PB_VENT_3_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PB_VENT_5_CLOSE_CMD", L_PB_VENT_5_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PBW_VENTS_47_CLOSE_CMD", L_PBW_VENTS_47_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_PB_VENT_6_CLOSE_CMD", L_PB_VENT_6_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "L_AFT_VENTS_89_CLOSE_CMD", L_AFT_VENTS_89_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_FWD_VENTS_12_CLOSE_CMD", R_FWD_VENTS_12_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PB_VENT_3_CLOSE_CMD", R_PB_VENT_3_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PB_VENT_5_CLOSE_CMD", R_PB_VENT_5_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PBW_VENTS_47_CLOSE_CMD", R_PBW_VENTS_47_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_PB_VENT_6_CLOSE_CMD", R_PB_VENT_6_CLOSE_CMD ? 1 : 0 );
		oapiWriteScenario_int( scn, "R_AFT_VENTS_89_CLOSE_CMD", R_AFT_VENTS_89_CLOSE_CMD ? 1 : 0 );
		return;
	}

	void VentCntlSeq::OnPostStep( double simt, double simdt, double mjd )
	{
	//step1:
		if (GetMajorMode() == 101)// HACK should be "MET < 0.0"
		{
			if (ReadCOMPOOL_IS( SCP_CONF_VENT_DOORS ) == 1)
			{
				// set group 5 (vent 6) purge 1 & 2 "A" reset cmds = false
				if (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) != 0)// HACK added to run full open sequence once
					goto step9;
			}
			else goto rtrn;
		}
		else goto step2;

	step2:
		if (STS()->GetMET() > 100.0)
		{
			if (GetMajorMode() != 602)
			{
				if (1/*TODO TAL abort declared*/) goto step2a;
	
				if (pETSepSequence->GetETSEPCommandFlag() == false) goto step2a;
			}

			if (firstpass2)
			{
				firstpass2 = false;
				VENT_CMDS_TIME_DELAY = 0.48;
				goto step8;
			}
			else goto step2a;
		}
		else goto step2a;

	step2a:
		if ((GetMajorMode() == 304) && (0/*TODO TAL abort declared*/))
		{
			if (et_umb_dr_timer >= 0.0) et_umb_dr_timer += simdt;
			if (firstpass2a_1)
			{
				firstpass2a_1 = false;
				et_umb_dr_timer = 0.0;
				// TODO set true:
				// ET DR CL LCH 1B1/2B2 FA1 STOW CMD
				// ET DR CL LCH 1B2/2B1 FA1 STOW CMD
				// ET DR CL LCH 1B1/2B2 FA2 STOW CMD
				// ET DR CL LCH 1B2/2B1 FA2 STOW CMD
				// ET DR CL LCH 1B1/2B2 FA4 STOW CMD
				// ET DR CL LCH 1B2/2B1 FA4 STOW CMD
				// ET DR CL LCH 1B1/2B2 FA3 STOW CMD
				// ET DR CL LCH 1B2/2B1 FA3 STOW CMD
			}
			else if (et_umb_dr_timer >= 66.0)
			{
				if (firstpass2a_5)
				{
					firstpass2a_5 = false;
					// TODO set false:
					// ET DR DRV & CL LCH DC ARM AMCA 1/2
					// ET DR DRV & CL LCH DC ARM AMCA 1/3
					// ET DR DRV & CL LCH DC ARM AMCA 2/3
					// ET L UMB COUT DOOR LATCH FA1 CMD
					// ET R UMB COUT DOOR LATCH FA1 CMD
					// ET L UMB COUT DOOR LATCH FA4 CMD
					// ET R UMB COUT DOOR LATCH FA4 CMD
					// ET L UMB COUT DOOR LATCH FA3 CMD
					// ET R UMB COUT DOOR LATCH FA3 CMD
					// ET L UMB COUT DOOR LATCH FA2 CMD
					// ET R UMB COUT DOOR LATCH FA2 CMD
				}
			}
			else if (et_umb_dr_timer >= 54.0)
			{
				if (firstpass2a_4)
				{
					firstpass2a_4 = false;
					// TODO set false:
					// ET UMB DR L-B2/R-B1 CLOSE CMD
					// ET UMB DR R-B2 CLOSE CMD
					// ET UMB DR R-B1/B2 CLOSE CMD
					// ET UMB DR L-B1 CLOSE CMD
					// ET UMB DR L-B1/B2 CLOSE CMD

					// TODO set true:
					// ET L UMB COUT DOOR LATCH FA1 CMD
					// ET R UMB COUT DOOR LATCH FA1 CMD
					// ET L UMB COUT DOOR LATCH FA4 CMD
					// ET R UMB COUT DOOR LATCH FA4 CMD
					// ET L UMB COUT DOOR LATCH FA3 CMD
					// ET R UMB COUT DOOR LATCH FA3 CMD
					// ET L UMB COUT DOOR LATCH FA2 CMD
					// ET R UMB COUT DOOR LATCH FA2 CMD
				}
			}
			else if (et_umb_dr_timer >= 12.0)
			{
				if (firstpass2a_3)
				{
					firstpass2a_3 = false;
					// TODO set false:
					// ET DR CL LCH 1B1/2B2 FA1 STOW CMD
					// ET DR CL LCH 1B2/2B1 FA1 STOW CMD
					// ET DR CL LCH 1B1/2B2 FA2 STOW CMD
					// ET DR CL LCH 1B2/2B1 FA2 STOW CMD
					// ET DR CL LCH 1B1/2B2 FA4 STOW CMD
					// ET DR CL LCH 1B2/2B1 FA4 STOW CMD
					// ET DR CL LCH 1B1/2B2 FA3 STOW CMD
					// ET DR CL LCH 1B2/2B1 FA3 STOW CMD
				}
			}
			else if (et_umb_dr_timer >= 6.0)
			{
				if (firstpass2a_2)
				{
					firstpass2a_2 = false;
					// TODO set true:
					// ET DR DRV & CL LCH DC ARM AMCA 1/2
					// ET DR DRV & CL LCH DC ARM AMCA 1/3
					// ET DR DRV & CL LCH DC ARM AMCA 2/3
					// ET UMB DR L-B2/R-B1 CLOSE CMD
					// ET UMB DR R-B2 CLOSE CMD
					// ET UMB DR R-B1/B2 CLOSE CMD
					// ET UMB DR L-B1 CLOSE CMD
					// ET UMB DR L-B1/B2 CLOSE CMD
				}
			}
		}

		goto step3;

	step3:
		if (GetMajorMode() == 304)
		{
			if (firstpass3_1)
			{
				firstpass3_1 = false;
				// TODO set true
				// MPS PNEU VLV HE ISLN NO.1 OPEN CMD
				// MPS PNEU VLV HE ISLN NO.2 OPEN CMD
				// MPS L HE ISOV B OP CMD A
				// MPS L HE ISOV B OP CMD B
				// MPS LH2 OTBD FILL VALVE OPEN CMD
				// MPS LH2 INBD FILL VALVE OPEN CMD A
				// MPS LH2 INBD FILL VALVE OPEN CMD B
				// MPS LH2 TOPPING VALVE OPEN CMD
				// MPS E1 HE INTCON OUT/OPEN CMD A
				// MPS E3 HE INTCON OUT/OPEN CMD A
				// MPS PNEU CROSSOVER NO.2 OPEN CMD
				// MPS E2 HE INTCON IN/OPEN CMD A
				// MPS E2 HE INTCON IN/OPEN CMD A
				// MPS E-1 LH2 PREVALVE OPEN CMD A
				// MPS E-1 LH2 PREVALVE OPEN CMD B
				// MPS E-1 LH2 PREVALVE OPEN CMD C
				// MPS E-2 LH2 PREVALVE OPEN CMD A
				// MPS E-2 LH2 PREVALVE OPEN CMD B
				// MPS E-2 LH2 PREVALVE OPEN CMD C
				// MPS E-3 LH2 PREVALVE OPEN CMD A
				// MPS E-3 LH2 PREVALVE OPEN CMD B
				// MPS E-3 LH2 PREVALVE OPEN CMD C
				// MPS E-1 LO2 PREVALVE OPEN CMD A
				// MPS E-1 LO2 PREVALVE OPEN CMD B
				// MPS E-1 LO2 PREVALVE OPEN CMD C
				// MPS E-1 LO2 PREVALVE OPEN CMD D
				// MPS E-2 LO2 PREVALVE OPEN CMD A
				// MPS E-2 LO2 PREVALVE OPEN CMD B
				// MPS E-2 LO2 PREVALVE OPEN CMD C
				// MPS E-2 LO2 PREVALVE OPEN CMD D
				// MPS E-3 LO2 PREVALVE OPEN CMD A
				// MPS E-3 LO2 PREVALVE OPEN CMD B
				// MPS E-3 LO2 PREVALVE OPEN CMD C
				// MPS E-3 LO2 PREVALVE OPEN CMD D
				// MPS LH2 RTLS INBD D/V OPEN CMD A
				// MPS LH2 RTLS INBD D/V OPEN CMD B
				// MPS LH2 RTLS INBD D/V OPEN CMD C
				// MPS LH2 RTLS OTBD D/V OPEN CMD A
				// MPS LH2 RTLS OTBD D/V OPEN CMD B
				// MPS LH2 RTLS OTBD D/V OPEN CMD C

				// TODO generate:
				// ME-1 OXIDIZER DUMP CMD
				// ME-2 OXIDIZER DUMP CMD
				// ME-3 OXIDIZER DUMP CMD

				// TODO set false:
				// MPS LH2 OTBD FILL VALVE CLOSE CMD
				// MPS E-1 LO2 PREVALVE CLOSE CMD A
				// MPS E-1 LO2 PREVALVE CLOSE CMD B
				// MPS E-1 LO2 PREVALVE CLOSE CMD C
				// MPS E-1 LO2 PREVALVE CLOSE CMD D
				// MPS E-2 LO2 PREVALVE CLOSE CMD A
				// MPS E-2 LO2 PREVALVE CLOSE CMD B
				// MPS E-2 LO2 PREVALVE CLOSE CMD C
				// MPS E-2 LO2 PREVALVE CLOSE CMD D
				// MPS E-3 LO2 PREVALVE CLOSE CMD A
				// MPS E-3 LO2 PREVALVE CLOSE CMD B
				// MPS E-3 LO2 PREVALVE CLOSE CMD C
				// MPS E-3 LO2 PREVALVE CLOSE CMD D
				// MPS LH2 INBD FILL VALVE CLOSE CMD
				// MPS HE INTCON OUT/OPEN CMD A
			}

			if (ReadCOMPOOL_SD( SCP_VE ) <= 20000.0)
			{
				if (firstpass3_2)
				{
					firstpass3_2 = false;
					// TODO set true:
					// MPS LO2 OTBD FILL VALVE OPEN CMD
					// MPS LO2 INBD FILL VALVE OPEN CMD A
					// MPS LO2 INBD FILL VALVE OPEN CMD B

					//  TODO set false:
					// MPS LO2 OTBD FILL VALVE CLOSE CMD
					// MPS LO2 INBD FILL VALVE CLOSE CMD
				}
			}
		}

		goto step4;
		
	step4:
		if (ReadCOMPOOL_SD( SCP_VE ) <= HE_PURGE_VEL)
		{
			if ((GetMajorMode() == 304) || (GetMajorMode() == 305))
			{
				if (firstpass4)
				{
					firstpass4 = false;
					he_purge_timer = HE_PURGE_TIME;
					// TODO set true:
					// MPS HE SPLY BLOWDOWN NO. 1 OPEN CMD
					// MPS HE SPLY BLOWDOWN NO. 2 OPEN CMD
					// MPS LH2 OTBD FILL VALVE CLOSE CMD
					// MPS LH2 MANIF REPRESS NO. 1 OPEN CMD
					// MPS LH2 MANIF REPRESS NO. 2 OPEN CMD
					// MPS LO2 OTBD FILL VALVE CLOSE CMD
					// MPS LO2 MANIF REPRESS NO. 1 OPEN CMD
					// MPS LO2 MANIF REPRESS NO. 2 OPEN CMD
					// MPS E-1 LO2 PREVALVE CLOSE CMD A
					// MPS E-1 LO2 PREVALVE CLOSE CMD B
					// MPS E-1 LO2 PREVALVE CLOSE CMD C
					// MPS E-1 LO2 PREVALVE CLOSE CMD D
					// MPS E-2 LO2 PREVALVE CLOSE CMD A
					// MPS E-2 LO2 PREVALVE CLOSE CMD B
					// MPS E-2 LO2 PREVALVE CLOSE CMD C
					// MPS E-2 LO2 PREVALVE CLOSE CMD D
					// MPS E-3 LO2 PREVALVE CLOSE CMD A
					// MPS E-3 LO2 PREVALVE CLOSE CMD B
					// MPS E-3 LO2 PREVALVE CLOSE CMD C
					// MPS E-3 LO2 PREVALVE CLOSE CMD D

					// TODO set false:
					// MPS LH2 OTBD FILL VALVE OPEN CMD
					// MPS LO2 OTBD FILL VALVE OPEN CMD
					// MPS E-1 LO2 PREVALVE OPEN CMD A
					// MPS E-1 LO2 PREVALVE OPEN CMD B
					// MPS E-1 LO2 PREVALVE OPEN CMD C
					// MPS E-1 LO2 PREVALVE OPEN CMD D
					// MPS E-2 LO2 PREVALVE OPEN CMD A
					// MPS E-2 LO2 PREVALVE OPEN CMD B
					// MPS E-2 LO2 PREVALVE OPEN CMD C
					// MPS E-2 LO2 PREVALVE OPEN CMD D
					// MPS E-3 LO2 PREVALVE OPEN CMD A
					// MPS E-3 LO2 PREVALVE OPEN CMD B
					// MPS E-3 LO2 PREVALVE OPEN CMD C
					// MPS E-3 LO2 PREVALVE OPEN CMD D
					// MPS LH2 RTLS INBD D/V OPEN CMD A
					// MPS LH2 RTLS INBD D/V OPEN CMD B
					// MPS LH2 RTLS INBD D/V OPEN CMD C
					// MPS LH2 RTLS OTBD D/V OPEN CMD A
					// MPS LH2 RTLS OTBD D/V OPEN CMD B
					// MPS LH2 RTLS OTBD D/V OPEN CMD C

					// TODO terminate:
					// ME-1 OXIDIZER DUMP CMD
					// ME-2 OXIDIZER DUMP CMD
					// ME-3 OXIDIZER DUMP CMD

					// TODO generate:
					// ME-1 TERMINATE SEQUENCE CMD
					// ME-2 TERMINATE SEQUENCE CMD
					// ME-3 TERMINATE SEQUENCE CMD
				}
				else
				{
					he_purge_timer -= simdt;
					if (he_purge_timer <= 0.0)
					{
						// TODO set false:
						// MPS HE SPLY BLOWDOWN NO. 1 OPEN CMD
						// MPS HE SPLY BLOWDOWN NO. 2 OPEN CMD
					}
				}
			}
		}

		goto step5;

	step5:
		if (GetMajorMode() == 304)
		{
			if (ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 1)
			{
				if (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) == 0)
				{
					if (timerQ >= 0.0) timerQ -= simdt;
					if (firstpass5)
					{
						firstpass5 = false;
						// issue left G1 and G6 open
						L_FWD_VENTS_12_OPEN_CMD = true;
						L_AFT_VENTS_89_OPEN_CMD = true;
						timerQ = 10.0;
					}

					if (timerQ < 0.0)
					{
						// terminate left G1 and G6 open
						L_FWD_VENTS_12_OPEN_CMD = false;
						L_AFT_VENTS_89_OPEN_CMD = false;
						// set a & b open set cmds = false
						// set a & b open reset cmds = true
						// 3 minor cycles later: set a open reset cmd = false
						LEFT_VENTS_1_AND_6_OPEN_FLAG = true;
						WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 0 );// HACK added to stop sequence
						firstpass5 = true;// HACK reset first pass
					}
				}
			}
			else if (LEFT_VENTS_1_AND_6_OPEN_FLAG == false) goto step8;
		}

		goto step6;

	step6:
		if (ReadCOMPOOL_SD( SCP_VE ) <= GROUND_REL_VEL_THRESHOLD)
		{
			if ((GetMajorMode() == 304) || (GetMajorMode() == 305) || (GetMajorMode() == 602) || (GetMajorMode() == 603))
			{
				if (ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 0)
				{
					/* HACK
					replaced direct call to step 9 with one-time open request, to avoid doors being reopened automatically if they are (mannualy) closed in the MMs above
					this works as long as GROUND_REL_VEL_THRESHOLD is <2500fps, as step 7 does not open doors in MM 304*/
					if (firstpass6)
					{
						firstpass6 = false;
						WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 1 );
						WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, 0 );
					}
				}
			}
		}

		goto step7;

	step7:
		if (ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) == 1)
		{
			if (ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) == 1) goto step8;
			else if (GetMajorMode() != 304) goto step9;
		}

		goto rtrn;

	step8:
		if (timerA >= 0.0) timerA -= simdt;
		if (timera >= 0.0) timera -= simdt;
		if (firstpass8_1)
		{
			firstpass8_1 = false;
			// issue G1 close
			L_FWD_VENTS_12_CLOSE_CMD = true;
			R_FWD_VENTS_12_CLOSE_CMD = true;
			timerA = 10.0;
			timera = VENT_CMDS_TIME_DELAY;
			WriteCOMPOOL_IS( SCP_VENT_DOOR_POS_IND, 0 );// HACK to indicate status in SPEC 51
			goto rtrn;
		}

		if (timera <= 0.0)
		{
			if (timerB >= 0.0) timerB -= simdt;
			if (timerb >= 0.0) timerb -= simdt;
			if (firstpass8_2)
			{
				firstpass8_2 = false;
				// issue G2 close
				L_PB_VENT_3_CLOSE_CMD = true;
				R_PB_VENT_3_CLOSE_CMD = true;
				timerB = 10.0;
				timerb = VENT_CMDS_TIME_DELAY;
			}
			if (timerA <= 0.0)
			{
				// terminate G1 close
				L_FWD_VENTS_12_CLOSE_CMD = false;
				R_FWD_VENTS_12_CLOSE_CMD = false;
				// set a&b cl set cmds = false
				// set a&b cl reset cmds = true
				// 3 minor cycles later: cl reset cmd = dormante state
			}

			if (timerb <= 0.0)
			{
				if (timerC >= 0.0) timerC -= simdt;
				if (timerc >= 0.0) timerc -= simdt;
				if (firstpass8_3)
				{
					firstpass8_3 = false;
					// issue G3 close
					L_PB_VENT_5_CLOSE_CMD = true;
					R_PB_VENT_5_CLOSE_CMD = true;
					timerC = 10.0;
					timerc = VENT_CMDS_TIME_DELAY;
				}
				if (timerB <= 0.0)
				{
					// terminate G2 close
					L_PB_VENT_3_CLOSE_CMD = false;
					R_PB_VENT_3_CLOSE_CMD = false;
					// set a&b cl set cmds = false
					// set a&b cl reset cmds = true
					// 3 minor cycles later: cl reset cmd = dormante state
				}

				if (timerc <= 0.0)
				{
					if (timerD >= 0.0) timerD -= simdt;
					if (timerd >= 0.0) timerd -= simdt;
					if (firstpass8_4)
					{
						firstpass8_4 = false;
						// issue G4 close
						L_PBW_VENTS_47_CLOSE_CMD = true;
						R_PBW_VENTS_47_CLOSE_CMD = true;
						timerD = 10.0;
						timerd = VENT_CMDS_TIME_DELAY;
					}
					if (timerC <= 0.0)
					{
						// terminate G3 close
						L_PB_VENT_5_CLOSE_CMD = false;
						R_PB_VENT_5_CLOSE_CMD = false;
						// set a&b cl set cmds = false
						// set a&b cl reset cmds = true
						// 3 minor cycles later: cl reset cmd = dormante state
					}

					if (timerd <= 0.0)
					{
						if (timerE >= 0.0) timerE -= simdt;
						if (timere >= 0.0) timere -= simdt;
						if (firstpass8_5)
						{
							firstpass8_5 = false;
							// issue G5 close
							L_PB_VENT_6_CLOSE_CMD = true;
							R_PB_VENT_6_CLOSE_CMD = true;
							timerE = 10.0;
							timere = VENT_CMDS_TIME_DELAY;
						}
						if (timerD <= 0.0)
						{
							// terminate G4 close
							L_PBW_VENTS_47_CLOSE_CMD = false;
							R_PBW_VENTS_47_CLOSE_CMD = false;
							// set a&b cl set cmds = false
							// set a&b cl reset cmds = true
							// 3 minor cycles later: cl reset cmd = dormante state
						}

						if (timere <= 0.0)
						{
							if (timerF >= 0.0) timerF -= simdt;
							if (firstpass8_6)
							{
								firstpass8_6 = false;
								// issue G6 close
								L_AFT_VENTS_89_CLOSE_CMD = true;
								R_AFT_VENTS_89_CLOSE_CMD = true;
								timerF = 10.0;
							}
							if (timerE <= 0.0)
							{
								// terminate G5 close
								L_PB_VENT_6_CLOSE_CMD = false;
								R_PB_VENT_6_CLOSE_CMD = false;
								// set a&b cl set cmds = false
								// set a&b cl reset cmds = true
								// 3 minor cycles later: cl reset cmd = dormante state
							}

							if (timerF <= 0.0)
							{
								// terminate G6 close
								L_AFT_VENTS_89_CLOSE_CMD = false;
								R_AFT_VENTS_89_CLOSE_CMD = false;
								// set a&b cl set cmds = false
								// set a&b cl reset cmds = true
								// 3 minor cycles later: cl reset cmd = dormante state

								if (GetMajorMode() == 301)
								{
									if (timerG >= 0.0) timerG -= simdt;
									if (firstpass8_7)
									{
										firstpass8_7 = false;
										// issue left G1 and G6 open
										L_FWD_VENTS_12_OPEN_CMD = true;
										L_AFT_VENTS_89_OPEN_CMD = true;
										timerG = 10.0;
									}
									if (timerG <= 0.0)
									{
										// terminate left G1 and G6 open
										L_FWD_VENTS_12_OPEN_CMD = false;
										L_AFT_VENTS_89_OPEN_CMD = false;
										// set a&b op set cmds = false
										// set a&b op reset cmds = true
										// 3 minor cycles later: op reset cmd = false
										WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 0 );// HACK added to stop sequence
										firstpass8_1 = true;// HACK added reset to first pass flags
										firstpass8_2 = true;
										firstpass8_3 = true;
										firstpass8_4 = true;
										firstpass8_5 = true;
										firstpass8_6 = true;
										firstpass8_7 = true;
										WriteCOMPOOL_IS( SCP_VENT_DOOR_POS_IND, 2 );// HACK to indicate status in SPEC 51
									}

								}
								else
								{
									WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, 1 );
									WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 0 );// HACK added to stop sequence
									LEFT_VENTS_1_AND_6_OPEN_FLAG = true;// HACK to stop the auto close sequence after it runs in MM 304
									firstpass8_1 = true;// HACK added reset to first pass flags
									firstpass8_2 = true;
									firstpass8_3 = true;
									firstpass8_4 = true;
									firstpass8_5 = true;
									firstpass8_6 = true;
									firstpass8_7 = true;
									WriteCOMPOOL_IS( SCP_VENT_DOOR_POS_IND, 2 );// HACK to indicate status in SPEC 51
								}
							}
						}
					}
				}
			}
		}

		goto rtrn;

	step9:
		if (timerH >= 0.0) timerH -= simdt;
		if (timerh >= 0.0) timerh -= simdt;
		if (firstpass9_1)
		{
			firstpass9_1 = false;
			// issue G4 open
			L_PBW_VENTS_47_OPEN_CMD = true;
			R_PBW_VENTS_47_OPEN_CMD = true;
			timerH = 10.0;
			timerh = VENT_CMDS_TIME_DELAY;
			WriteCOMPOOL_IS( SCP_ORBITER_VENT_DOORS_STATUS_WORD, 0 );
			WriteCOMPOOL_IS( SCP_VENT_DOOR_POS_IND, 0 );// HACK to indicate status in SPEC 51
			goto rtrn;
		}

		if (timerh <= 0.0)
		{
			if (timerJ >= 0.0) timerJ -= simdt;
			if (timerj >= 0.0) timerj -= simdt;
			if (firstpass9_2)
			{
				firstpass9_2 = false;
				// issue G2 open
				L_PB_VENT_3_OPEN_CMD = true;
				R_PB_VENT_3_OPEN_CMD = true;
				timerJ = 10.0;
				timerj = VENT_CMDS_TIME_DELAY;
			}
			if (timerH <= 0.0)
			{
				// terminate G4 open
				L_PBW_VENTS_47_OPEN_CMD = false;
				R_PBW_VENTS_47_OPEN_CMD = false;
				// set a&b op set = false
				// set a&b op reset = true
				// 3 minor cycles later: a op reset = false
			}

			if (timerj <= 0.0)
			{
				if (timerK >= 0.0) timerK -= simdt;
				if (timerk >= 0.0) timerk -= simdt;
				if (firstpass9_3)
				{
					firstpass9_3 = false;
					// issue G5 open
					L_PB_VENT_6_OPEN_CMD = true;
					R_PB_VENT_6_OPEN_CMD = true;
					timerK = 10.0;
					timerk = VENT_CMDS_TIME_DELAY;
				}
				if (timerJ <= 0.0)
				{
					// terminate G2 open
					L_PB_VENT_3_OPEN_CMD = false;
					R_PB_VENT_3_OPEN_CMD = false;
					// set a&b op set = false
					// set a&b op reset = true
					// 3 minor cycles later: a op reset = false
				}

				if (timerk <= 0.0)
				{
					if (timerL >= 0.0) timerL -= simdt;
					if (timerl >= 0.0) timerl -= simdt;
					if (firstpass9_4)
					{
						firstpass9_4 = false;
						// issue G3 open
						L_PB_VENT_5_OPEN_CMD = true;
						R_PB_VENT_5_OPEN_CMD = true;
						timerL = 10.0;
						timerl = VENT_CMDS_TIME_DELAY;
					}
					if (timerK <= 0.0)
					{
						// terminate G5 open
						L_PB_VENT_6_OPEN_CMD = false;
						R_PB_VENT_6_OPEN_CMD = false;
						// set a&b op set = false
						// set a&b op reset = true
						// 3 minor cycles later: a op reset = false
					}

					if (timerl <= 0.0)
					{
						if (timerM >= 0.0) timerM -= simdt;
						if (timerm >= 0.0) timerm -= simdt;
						if (firstpass9_5)
						{
							firstpass9_5 = false;
							// issue G1 open
							L_FWD_VENTS_12_OPEN_CMD = true;
							R_FWD_VENTS_12_OPEN_CMD = true;
							timerM = 10.0;
							timerm = VENT_CMDS_TIME_DELAY;
						}
						if (timerL <= 0.0)
						{
							// terminate G3 open
							L_PB_VENT_5_OPEN_CMD = false;
							R_PB_VENT_5_OPEN_CMD = false;
							// set a&b op set = false
							// set a&b op reset = true
							// 3 minor cycles later: a op reset = false
						}

						if (timerm <= 0.0)
						{
							if (timerN >= 0.0) timerN -= simdt;
							if (timerP >= 0.0) timerP -= simdt;
							if (firstpass9_6)
							{
								firstpass9_6 = false;
								// issue G6 open
								L_AFT_VENTS_89_OPEN_CMD = true;
								R_AFT_VENTS_89_OPEN_CMD = true;
								timerN = 10.0;
								timerP = 5.0;
							}
							if (timerM <= 0.0)
							{
								// terminate G1 open
								L_FWD_VENTS_12_OPEN_CMD = false;
								R_FWD_VENTS_12_OPEN_CMD = false;
								// set a&b op set = false
								// set a&b op reset = true
								// 3 minor cycles later: a op reset = false
							}

							if (timerP <= 0.0)
							{
								// HACK disabled first pass check as it needs to run more times to pickup OP indication from last group
								//if (firstpass9_7)
								{
									//firstpass9_7 = false;
									// monitor vent door status and commfaults
									unsigned int stwd = 0;
									unsigned short FF1_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF1_IOM4_CH2_DATA );
									unsigned short FF2_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF2_IOM4_CH2_DATA );
									unsigned short FF3_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF3_IOM4_CH2_DATA );
									unsigned short FF4_IOM4_CH2 = ReadCOMPOOL_IS( SCP_FF4_IOM4_CH2_DATA );
									unsigned short FA1_IOM11_CH0 = ReadCOMPOOL_IS( SCP_FA1_IOM11_CH0_DATA );
									unsigned short FA2_IOM11_CH0 = ReadCOMPOOL_IS( SCP_FA2_IOM11_CH0_DATA );
									unsigned short FA3_IOM11_CH0 = ReadCOMPOOL_IS( SCP_FA3_IOM11_CH0_DATA );
									unsigned short FA4_IOM11_CH0 = ReadCOMPOOL_IS( SCP_FA4_IOM11_CH0_DATA );
									bool L_FWD_VENTS_12_OPEN_1 = ((FF3_IOM4_CH2 & 0x0080) != 0);
									bool L_FWD_VENTS_12_OPEN_2 = ((FF2_IOM4_CH2 & 0x0080) != 0);
									bool L_PB_VENT_3_OPEN_1 = ((FF3_IOM4_CH2 & 0x0020) != 0);
									bool L_PB_VENT_3_OPEN_2 = ((FF2_IOM4_CH2 & 0x0020) != 0);
									bool L_PB_VENT_5_OPEN_1 = ((FF3_IOM4_CH2 & 0x8000) != 0);
									bool L_PB_VENT_5_OPEN_2 = ((FF4_IOM4_CH2 & 0x8000) != 0);
									bool L_PBW_VENTS_47_OPEN_1 = ((FF3_IOM4_CH2 & 0x2000) != 0);
									bool L_PBW_VENTS_47_OPEN_2 = ((FF2_IOM4_CH2 & 0x2000) != 0);
									bool L_PB_VENT_6_OPEN_1 = ((FF1_IOM4_CH2 & 0x0400) != 0);
									bool L_PB_VENT_6_OPEN_2 = ((FF4_IOM4_CH2 & 0x0400) != 0);
									bool L_AFT_VENTS_89_OPEN_1 = ((FA1_IOM11_CH0 & 0x4000) != 0);
									bool L_AFT_VENTS_89_OPEN_2 = ((FA4_IOM11_CH0 & 0x4000) != 0);
									bool R_FWD_VENTS_12_OPEN_1 = ((FF1_IOM4_CH2 & 0x0080) != 0);
									bool R_FWD_VENTS_12_OPEN_2 = ((FF4_IOM4_CH2 & 0x0080) != 0);
									bool R_PB_VENT_3_OPEN_1 = ((FF1_IOM4_CH2 & 0x2000) != 0);
									bool R_PB_VENT_3_OPEN_2 = ((FF4_IOM4_CH2 & 0x0020) != 0);
									bool R_PB_VENT_5_OPEN_1 = ((FF1_IOM4_CH2 & 0x8000) != 0);
									bool R_PB_VENT_5_OPEN_2 = ((FF2_IOM4_CH2 & 0x8000) != 0);
									bool R_PBW_VENTS_47_OPEN_1 = ((FF4_IOM4_CH2 & 0x2000) != 0);
									bool R_PBW_VENTS_47_OPEN_2 = ((FF1_IOM4_CH2 & 0x0020) != 0);
									bool R_PB_VENT_6_OPEN_1 = ((FF3_IOM4_CH2 & 0x0400) != 0);
									bool R_PB_VENT_6_OPEN_2 = ((FF2_IOM4_CH2 & 0x0400) != 0);
									bool R_AFT_VENTS_89_OPEN_1 = ((FA3_IOM11_CH0 & 0x4000) != 0);
									bool R_AFT_VENTS_89_OPEN_2 = ((FA2_IOM11_CH0 & 0x4000) != 0);

									if (L_FWD_VENTS_12_OPEN_1) stwd |= 0x00000001;
									if (L_FWD_VENTS_12_OPEN_2) stwd |= 0x00000002;
									if (R_FWD_VENTS_12_OPEN_1) stwd |= 0x00000004;
									if (R_FWD_VENTS_12_OPEN_2) stwd |= 0x00000008;
									if (L_PB_VENT_3_OPEN_1) stwd |= 0x00000010;
									if (L_PB_VENT_3_OPEN_2) stwd |= 0x00000020;
									if (R_PB_VENT_3_OPEN_1) stwd |= 0x00000040;
									if (R_PB_VENT_3_OPEN_2) stwd |= 0x00000080;
									if (L_PB_VENT_5_OPEN_1) stwd |= 0x00000100;
									if (L_PB_VENT_5_OPEN_2) stwd |= 0x00000200;
									if (R_PB_VENT_5_OPEN_1) stwd |= 0x00000400;
									if (R_PB_VENT_5_OPEN_2) stwd |= 0x00000800;
									/*if (L_PBW_VENTS_47_OPEN_1*)*/ stwd |= 0x00001000;// HACK disabled reporting until solution is found for non-active 4-7 doors
									/*if (L_PBW_VENTS_47_OPEN_2)*/ stwd |= 0x00002000;
									/*if (R_PBW_VENTS_47_OPEN_1)*/ stwd |= 0x00004000;
									/*if (R_PBW_VENTS_47_OPEN_2)*/ stwd |= 0x00008000;
									if (L_PB_VENT_6_OPEN_1) stwd |= 0x00010000;
									if (L_PB_VENT_6_OPEN_2) stwd |= 0x00020000;
									if (R_PB_VENT_6_OPEN_1) stwd |= 0x00040000;
									if (R_PB_VENT_6_OPEN_2) stwd |= 0x00080000;
									if (L_AFT_VENTS_89_OPEN_1) stwd |= 0x00100000;
									if (L_AFT_VENTS_89_OPEN_2) stwd |= 0x00200000;
									if (R_AFT_VENTS_89_OPEN_1) stwd |= 0x00400000;
									if (R_AFT_VENTS_89_OPEN_2) stwd |= 0x00800000;
									WriteCOMPOOL_ID( SCP_ORBITER_VENT_DOORS_STATUS_WORD, stwd );
								}

								if (timerN <= 0.0)
								{
									// terminate G6 open
									L_AFT_VENTS_89_OPEN_CMD = false;
									R_AFT_VENTS_89_OPEN_CMD = false;
									// set a&b op set = false
									// set a&b op reset = true
									// 3 minor cycles later: a op reset = false
									WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, 0 ); 
									WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, 0 );// HACK added to stop sequence
									firstpass9_1 = true;// HACK added reset to first pass flags
									firstpass9_2 = true;
									firstpass9_3 = true;
									firstpass9_4 = true;
									firstpass9_5 = true;
									firstpass9_6 = true;
									firstpass9_7 = true;
									WriteCOMPOOL_IS( SCP_VENT_DOOR_POS_IND, 1 );// HACK to indicate status in SPEC 51
								}
							}
						}
					}
				}
			}
		}

	rtrn:
		sprintf_s( oapiDebugString(), 255, "%d/%d %d/%d %d/%d %d/%d %d/%d %d/%d   %d/%d %d/%d %d/%d %d/%d %d/%d %d/%d",
			L_FWD_VENTS_12_OPEN_CMD, L_FWD_VENTS_12_CLOSE_CMD,
			L_PB_VENT_3_OPEN_CMD, L_PB_VENT_3_CLOSE_CMD,
			L_PB_VENT_5_OPEN_CMD, L_PB_VENT_5_CLOSE_CMD,
			L_PBW_VENTS_47_OPEN_CMD, L_PBW_VENTS_47_CLOSE_CMD,
			L_PB_VENT_6_OPEN_CMD, L_PB_VENT_6_CLOSE_CMD,
			L_AFT_VENTS_89_OPEN_CMD, L_AFT_VENTS_89_CLOSE_CMD,
			R_FWD_VENTS_12_OPEN_CMD, R_FWD_VENTS_12_CLOSE_CMD,
			R_PB_VENT_3_OPEN_CMD, R_PB_VENT_3_CLOSE_CMD,
			R_PB_VENT_5_OPEN_CMD, R_PB_VENT_5_CLOSE_CMD,
			R_PBW_VENTS_47_OPEN_CMD, R_PBW_VENTS_47_CLOSE_CMD,
			R_PB_VENT_6_OPEN_CMD, R_PB_VENT_6_CLOSE_CMD,
			R_AFT_VENTS_89_OPEN_CMD, R_AFT_VENTS_89_CLOSE_CMD );

		// output commands
		unsigned short FF1_IOM2_CH0 = 0;
		if (R_FWD_VENTS_12_CLOSE_CMD) FF1_IOM2_CH0 |= 0x0001;
		if (R_FWD_VENTS_12_OPEN_CMD) FF1_IOM2_CH0 |= 0x0002;
		if (R_PBW_VENTS_47_CLOSE_CMD) FF1_IOM2_CH0 |= 0x0800;

		unsigned short FF1_IOM2_CH2 = 0;
		if (R_PBW_VENTS_47_OPEN_CMD) FF1_IOM2_CH2 |= 0x0080;
		if (R_PB_VENT_3_CLOSE_CMD) FF1_IOM2_CH2 |= 0x0100;
		if (R_PB_VENT_3_OPEN_CMD) FF1_IOM2_CH2 |= 0x0200;
		if (L_PB_VENT_6_CLOSE_CMD) FF1_IOM2_CH2 |= 0x0400;
		if (L_PB_VENT_6_OPEN_CMD) FF1_IOM2_CH2 |= 0x0800;
		if (R_PB_VENT_5_CLOSE_CMD) FF1_IOM2_CH2 |= 0x4000;
		if (R_PB_VENT_5_OPEN_CMD) FF1_IOM2_CH2 |= 0x8000;

		unsigned short FF1_IOM10_CH0 = 0;
		if (R_FWD_VENTS_12_CLOSE_CMD) FF1_IOM10_CH0 |= 0x0001;
		if (R_FWD_VENTS_12_OPEN_CMD) FF1_IOM10_CH0 |= 0x0002;

		unsigned short FF1_IOM10_CH2 = 0;
		if (R_PBW_VENTS_47_CLOSE_CMD) FF1_IOM10_CH2 |= 0x0040;
		if (R_PBW_VENTS_47_OPEN_CMD) FF1_IOM10_CH2 |= 0x0080;
		if (R_PB_VENT_3_CLOSE_CMD) FF1_IOM10_CH2 |= 0x0100;
		if (R_PB_VENT_3_OPEN_CMD) FF1_IOM10_CH2 |= 0x0200;
		if (L_PB_VENT_6_CLOSE_CMD) FF1_IOM10_CH2 |= 0x0400;
		if (L_PB_VENT_6_OPEN_CMD) FF1_IOM10_CH2 |= 0x0800;
		if (R_PB_VENT_5_CLOSE_CMD) FF1_IOM10_CH2 |= 0x4000;
		if (R_PB_VENT_5_OPEN_CMD) FF1_IOM10_CH2 |= 0x8000;


		unsigned short FF2_IOM2_CH0 = 0;
		if (L_FWD_VENTS_12_CLOSE_CMD) FF2_IOM2_CH0 |= 0x0001;
		if (L_FWD_VENTS_12_OPEN_CMD) FF2_IOM2_CH0 |= 0x0002;

		unsigned short FF2_IOM2_CH1 = 0;
		if (R_PB_VENT_5_CLOSE_CMD) FF2_IOM2_CH1 |= 0x0040;

		unsigned short FF2_IOM2_CH2 = 0;
		if (L_PB_VENT_3_CLOSE_CMD) FF2_IOM2_CH2 |= 0x0040;
		if (L_PB_VENT_3_OPEN_CMD) FF2_IOM2_CH2 |= 0x0080;
		if (L_PBW_VENTS_47_CLOSE_CMD) FF2_IOM2_CH2 |= 0x0100;
		if (L_PBW_VENTS_47_OPEN_CMD) FF2_IOM2_CH2 |= 0x0200;
		if (R_PB_VENT_6_CLOSE_CMD) FF2_IOM2_CH2 |= 0x0400;
		if (R_PB_VENT_6_OPEN_CMD) FF2_IOM2_CH2 |= 0x0800;
		if (R_PB_VENT_5_OPEN_CMD) FF2_IOM2_CH2 |= 0x8000;

		unsigned short FF2_IOM10_CH0 = 0;
		if (L_FWD_VENTS_12_CLOSE_CMD) FF2_IOM10_CH0 |= 0x0001;
		if (L_FWD_VENTS_12_OPEN_CMD) FF2_IOM10_CH0 |= 0x0002;

		unsigned short FF2_IOM10_CH2 = 0;
		if (L_PB_VENT_3_CLOSE_CMD) FF2_IOM10_CH2 |= 0x0040;
		if (L_PB_VENT_3_OPEN_CMD) FF2_IOM10_CH2 |= 0x0080;
		if (L_PBW_VENTS_47_CLOSE_CMD) FF2_IOM10_CH2 |= 0x0100;
		if (L_PBW_VENTS_47_OPEN_CMD) FF2_IOM10_CH2 |= 0x0200;
		if (R_PB_VENT_6_CLOSE_CMD) FF2_IOM10_CH2 |= 0x0400;
		if (R_PB_VENT_6_OPEN_CMD) FF2_IOM10_CH2 |= 0x0800;
		if (R_PB_VENT_5_CLOSE_CMD) FF2_IOM10_CH2 |= 0x4000;
		if (R_PB_VENT_5_OPEN_CMD) FF2_IOM10_CH2 |= 0x8000;


		unsigned short FF3_IOM2_CH0 = 0;
		if (L_PB_VENT_3_OPEN_CMD) FF3_IOM2_CH0 |= 0x0001;
		if (L_FWD_VENTS_12_OPEN_CMD) FF3_IOM2_CH0 |= 0x0002;

		unsigned short FF3_IOM2_CH1 = 0;
		if (L_PBW_VENTS_47_CLOSE_CMD) FF3_IOM2_CH1 |= 0x0040;

		unsigned short FF3_IOM2_CH2 = 0;
		if (L_PB_VENT_3_CLOSE_CMD) FF3_IOM2_CH2 |= 0x0040;
		if (L_FWD_VENTS_12_CLOSE_CMD) FF3_IOM2_CH2 |= 0x0080;
		if (L_PBW_VENTS_47_OPEN_CMD) FF3_IOM2_CH2 |= 0x0200;
		if (R_PB_VENT_6_CLOSE_CMD) FF3_IOM2_CH2 |= 0x0400;
		if (R_PB_VENT_6_OPEN_CMD) FF3_IOM2_CH2 |= 0x0800;
		if (L_PB_VENT_5_CLOSE_CMD) FF3_IOM2_CH2 |= 0x4000;
		if (L_PB_VENT_5_OPEN_CMD) FF3_IOM2_CH2 |= 0x8000;

		unsigned short FF3_IOM10_CH0 = 0;
		if (L_FWD_VENTS_12_CLOSE_CMD) FF3_IOM10_CH0 |= 0x0001;
		if (L_FWD_VENTS_12_OPEN_CMD) FF3_IOM10_CH0 |= 0x0002;
		if (L_PB_VENT_3_OPEN_CMD) FF3_IOM10_CH0 |= 0x0004;

		unsigned short FF3_IOM10_CH2 = 0;
		if (L_PB_VENT_3_CLOSE_CMD) FF3_IOM10_CH2 |= 0x0040;
		if (L_PBW_VENTS_47_CLOSE_CMD) FF3_IOM10_CH2 |= 0x0100;
		if (L_PBW_VENTS_47_OPEN_CMD) FF3_IOM10_CH2 |= 0x0200;
		if (R_PB_VENT_6_CLOSE_CMD) FF3_IOM10_CH2 |= 0x0400;
		if (R_PB_VENT_6_OPEN_CMD) FF3_IOM10_CH2 |= 0x0800;
		if (R_PB_VENT_5_CLOSE_CMD) FF3_IOM10_CH2 |= 0x4000;
		if (R_PB_VENT_5_OPEN_CMD) FF3_IOM10_CH2 |= 0x8000;


		unsigned short FF4_IOM2_CH0 = 0;
		if (R_PB_VENT_3_OPEN_CMD) FF4_IOM2_CH0 |= 0x0001;
		if (R_FWD_VENTS_12_OPEN_CMD) FF4_IOM2_CH0 |= 0x0002;

		unsigned short FF4_IOM2_CH1 = 0;
		if (L_PB_VENT_5_CLOSE_CMD) FF4_IOM2_CH1 |= 0x0040;

		unsigned short FF4_IOM2_CH2 = 0;
		if (R_PB_VENT_3_CLOSE_CMD) FF4_IOM2_CH2 |= 0x0040;
		if (R_FWD_VENTS_12_CLOSE_CMD) FF4_IOM2_CH2 |= 0x0080;
		if (R_PBW_VENTS_47_CLOSE_CMD) FF4_IOM2_CH2 |= 0x0100;
		if (R_PBW_VENTS_47_OPEN_CMD) FF4_IOM2_CH2 |= 0x0200;
		if (L_PB_VENT_6_CLOSE_CMD) FF4_IOM2_CH2 |= 0x0400;
		if (L_PB_VENT_6_OPEN_CMD) FF4_IOM2_CH2 |= 0x0800;
		if (L_PB_VENT_5_OPEN_CMD) FF4_IOM2_CH2 |= 0x8000;

		unsigned short FF4_IOM10_CH0 = 0;
		if (R_FWD_VENTS_12_CLOSE_CMD) FF4_IOM10_CH0 |= 0x0001;
		if (R_FWD_VENTS_12_OPEN_CMD) FF4_IOM10_CH0 |= 0x0002;
		if (R_PB_VENT_3_OPEN_CMD) FF4_IOM10_CH0 |= 0x0004;

		unsigned short FF4_IOM10_CH2 = 0;
		if (R_PB_VENT_3_CLOSE_CMD) FF4_IOM10_CH2 |= 0x0040;
		if (R_PBW_VENTS_47_CLOSE_CMD) FF4_IOM10_CH2 |= 0x0100;
		if (R_PBW_VENTS_47_OPEN_CMD) FF4_IOM10_CH2 |= 0x0200;
		if (L_PB_VENT_6_CLOSE_CMD) FF4_IOM10_CH2 |= 0x0400;
		if (L_PB_VENT_6_OPEN_CMD) FF4_IOM10_CH2 |= 0x0800;
		if (R_PB_VENT_5_CLOSE_CMD) FF4_IOM10_CH2 |= 0x4000;
		if (L_PB_VENT_5_OPEN_CMD) FF4_IOM10_CH2 |= 0x8000;


		unsigned short FA1_IOM7_CH0 = 0;
		if (L_AFT_VENTS_89_CLOSE_CMD) FA1_IOM7_CH0 |= 0x0010;
		if (L_AFT_VENTS_89_OPEN_CMD) FA1_IOM7_CH0 |= 0x0020;

		unsigned short FA1_IOM15_CH0 = 0;
		if (L_AFT_VENTS_89_CLOSE_CMD) FA1_IOM15_CH0 |= 0x0008;
		if (L_AFT_VENTS_89_OPEN_CMD) FA1_IOM15_CH0 |= 0x0010;


		unsigned short FA2_IOM7_CH0 = 0;
		if (R_AFT_VENTS_89_CLOSE_CMD) FA2_IOM7_CH0 |= 0x0010;
		if (R_AFT_VENTS_89_OPEN_CMD) FA2_IOM7_CH0 |= 0x0020;

		unsigned short FA2_IOM15_CH0 = 0;
		if (R_AFT_VENTS_89_CLOSE_CMD) FA2_IOM15_CH0 |= 0x0008;
		if (R_AFT_VENTS_89_OPEN_CMD) FA2_IOM15_CH0 |= 0x0010;


		unsigned short FA3_IOM7_CH0 = 0;
		if (R_AFT_VENTS_89_CLOSE_CMD) FA3_IOM7_CH0 |= 0x0010;
		if (R_AFT_VENTS_89_OPEN_CMD) FA3_IOM7_CH0 |= 0x0020;

		unsigned short FA3_IOM15_CH0 = 0;
		if (R_AFT_VENTS_89_CLOSE_CMD) FA3_IOM15_CH0 |= 0x0008;
		if (R_AFT_VENTS_89_OPEN_CMD) FA3_IOM15_CH0 |= 0x0010;


		unsigned short FA4_IOM7_CH0 = 0;
		if (L_AFT_VENTS_89_CLOSE_CMD) FA4_IOM7_CH0 |= 0x0010;
		if (L_AFT_VENTS_89_OPEN_CMD) FA4_IOM7_CH0 |= 0x0020;

		unsigned short FA4_IOM15_CH0 = 0;
		if (L_AFT_VENTS_89_CLOSE_CMD) FA4_IOM15_CH0 |= 0x0008;
		if (L_AFT_VENTS_89_OPEN_CMD) FA4_IOM15_CH0 |= 0x0010;


		// output to MDMs
		WriteCOMPOOL_IS( SCP_FF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH0_DATA ) | FF1_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_FF1_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM2_CH2_DATA ) | FF1_IOM2_CH2 );
		WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | FF1_IOM10_CH0 );
		WriteCOMPOOL_IS( SCP_FF1_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH2_DATA ) | FF1_IOM10_CH2 );

		WriteCOMPOOL_IS( SCP_FF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM2_CH0_DATA ) | FF2_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_FF2_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM2_CH1_DATA ) | FF2_IOM2_CH1 );
		WriteCOMPOOL_IS( SCP_FF2_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM2_CH2_DATA ) | FF2_IOM2_CH2 );
		WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | FF2_IOM10_CH0 );
		WriteCOMPOOL_IS( SCP_FF2_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH2_DATA ) | FF2_IOM10_CH2 );

		WriteCOMPOOL_IS( SCP_FF3_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH0_DATA ) | FF3_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH1_DATA ) | FF3_IOM2_CH1 );
		WriteCOMPOOL_IS( SCP_FF3_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM2_CH2_DATA ) | FF3_IOM2_CH2 );
		WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | FF3_IOM10_CH0 );
		WriteCOMPOOL_IS( SCP_FF3_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH2_DATA ) | FF3_IOM10_CH2 );

		WriteCOMPOOL_IS( SCP_FF4_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM2_CH0_DATA ) | FF4_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_FF4_IOM2_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM2_CH1_DATA ) | FF4_IOM2_CH1 );
		WriteCOMPOOL_IS( SCP_FF4_IOM2_CH2_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM2_CH2_DATA ) | FF4_IOM2_CH2 );
		WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | FF4_IOM10_CH0 );
		WriteCOMPOOL_IS( SCP_FF4_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH2_DATA ) | FF4_IOM10_CH2 );

		WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) | FA1_IOM7_CH0 );
		WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) | FA1_IOM15_CH0 );

		WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) | FA2_IOM7_CH0 );
		WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) | FA2_IOM15_CH0 );

		WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) | FA3_IOM7_CH0 );
		WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) | FA3_IOM15_CH0 );

		WriteCOMPOOL_IS( SCP_FA4_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH0_DATA ) | FA4_IOM7_CH0 );
		WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) | FA4_IOM15_CH0 );
		return;
	}

	bool VentCntlSeq::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 301:
			case 302:
			case 303:
			case 304:
			case 305:
			case 601:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}
}
