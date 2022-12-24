#include "SystemsServicesAnnunciation.h"
#include "../../../Atlantis.h"


constexpr double CW_B_TIME = 0.32;// BU CW B on time (0.15-0.5s) [s]

namespace dps
{
	SystemsServicesAnnunciation::SystemsServicesAnnunciation( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SystemsServicesAnnunciation" ),
		SMlight(false), SMtone(false), SMtonetime(0.0), CWalertA(false), CWalertB(false), CWtimerB(CW_B_TIME), lastmsgtime(-999.0)
	{
		// init array index
		WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, 1 );
		return;
	}

	SystemsServicesAnnunciation::~SystemsServicesAnnunciation( void )
	{
		return;
	}

	bool SystemsServicesAnnunciation::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "SMlight", 7 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			SMlight = (tmp == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "SMtone", 6 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			SMtone = (tmp == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "SMtonetime", 10 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			SMtonetime = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CWalertA", 8 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			CWalertA = (tmp == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "CWalertB", 8 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			CWalertB = (tmp == 1);
			return true;
		}
		else if (!_strnicmp( keyword, "CWtimerB", 8 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CWtimerB = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "lastmsgtime", 11 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			lastmsgtime = tmp;
			return true;
		}
		else return false;
	}

	void SystemsServicesAnnunciation::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "SMlight", SMlight ? 1 : 0 );
		oapiWriteScenario_int( scn, "SMtone", SMtone ? 1 : 0 );
		oapiWriteScenario_float( scn, "SMtonetime", SMtonetime );
		oapiWriteScenario_int( scn, "CWalertA", CWalertA ? 1 : 0 );
		oapiWriteScenario_int( scn, "CWalertB", CWalertB ? 1 : 0 );
		oapiWriteScenario_float( scn, "CWtimerB", CWtimerB );
		oapiWriteScenario_float( scn, "lastmsgtime", lastmsgtime );
		return;
	}

	void SystemsServicesAnnunciation::SetClass2Alarm( void )
	{
		unsigned short PF1_IOM2_CH0 = CWalertB ? 0x1000 : 0x0000;
		unsigned short PF2_IOM2_CH0 = CWalertA ? 0x1000 : 0x0000;
		WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA ) | PF1_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA ) | PF2_IOM2_CH0 );
		return;
	}

	void SystemsServicesAnnunciation::SetClass3Alarm( void )
	{
		unsigned short PF1_IOM2_CH0 = (SMlight ? 0x4000 : 0x0000) | (SMtone ? 0x2000 : 0x0000);
		unsigned short PF2_IOM2_CH0 = (SMlight ? 0x4000 : 0x0000) | (SMtone ? 0x2000 : 0x0000);
		WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA ) | PF1_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA ) | PF2_IOM2_CH0 );
		return;
	}

	void SystemsServicesAnnunciation::OnPostStep( double simt, double simdt, double mjd )
	{
		// handle alert duration and msg ack and clear keys
		if (CWalertB)
		{
			CWtimerB -= simdt;
			if (CWtimerB <= 0.0)
			{
				CWalertB = false;
			}
		}

		if (SMtone)
		{
			SMtonetime -= simdt;
			if (SMtonetime <= 0.0)
			{
				SMtone = false;
			}
		}

		if (ReadCOMPOOL_IS( SCP_ACK_KEY ))
		{
			// reset outputs
			SMlight = false;
			SMtone = false;
			// stop flashing
			unsigned int state = ReadCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE );
			if (state == 1) WriteCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE, 2 );
			else if (state == 2)
			{
				// decrement indicator
				unsigned short ind = ReadCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND );
				if (ind > 0)
				{
					ind--;
					WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, ind );

					// load next msg
					char msg[64];
					memset( msg, 0, 32 );
					ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, ind + 1, msg, 15, 43 );
					WriteCOMPOOL_C( SCP_FAULT_MSG_LINE, msg, 43 );
				}
			}
		}
		if (ReadCOMPOOL_IS( SCP_MSGRESET_KEY ))
		{
			// reset outputs
			SMlight = false;
			SMtone = false;
			CWalertA = false;
			CWalertB = false;
			// clear fault msg line
			WriteCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE, 0 );
			WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, 0 );
		}

		// clear list
		if (ReadCOMPOOL_IS( SCP_FAULT_DISPBUF_CLEAR ) == 1)
		{
			// clear fault msg list
			WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT, 0 );

			// clear fault msg line
			WriteCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE, 0 );
			WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, 0 );

			// reset clear indication
			WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CLEAR, 0 );
		}

		// update list
		unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
		for (unsigned int i = 1; i < j; i++)
		{
			unsigned int cw = ReadCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, i, 5 );
			if (cw == 2) 
			{
				CWalertA = true;
				CWalertB = true;
				CWtimerB = CW_B_TIME;
				SaveMsg( i, 2 );
			}
			else// if (cw == 3)
			{
				SMlight = true;
				SMtonetime = ReadCOMPOOL_IS( SCP_SM_TONE_DURATION );
				if (SMtonetime != 0.0) SMtone = true;// no duration = no tone
				else SMtone = false;
				SaveMsg( i, 3 );
			}
		}
		// reset buffer
		WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, 1 );

		// output to CW
		if (SMtone || SMlight) SetClass3Alarm();
		if (CWalertA || CWalertB) SetClass2Alarm();
		return;
	}

	void SystemsServicesAnnunciation::SaveMsg( unsigned int idx, unsigned int cwclass )
	{
		// build msg
		char msg[64];
		char fault[32];
		char cbuf[64];
		unsigned short j = ReadCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT );
		unsigned short usDay, usHour, usMinute, usSecond;
		STS()->GetGPCMET( 1, usDay, usHour, usMinute, usSecond );// TODO get MET the right way

		memset( fault, 0, 32 );
		ReadCOMPOOL_AC( SCP_FAULT_IN_MSG, idx, fault, 5, 19 );
		sprintf_s( msg, "%s  %c    2    %03d/%02d:%02d:%02d", fault, (cwclass == 2) ? '*' : ' ', usDay, usHour, usMinute, usSecond );

		// filter msgs with same fields and within 4.8s of the last one
		double msgtime = (usDay * 86400.0) + (usHour * 3600.0) + (usMinute * 60.0) + usSecond;
		if ((msgtime - lastmsgtime) <= 4.8)
		{
			if (j > 0)
			{
				memset( cbuf, 0, 64 );
				ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, 1, cbuf, 15, 43 );
				if (memcmp( cbuf, fault, 19 ) == 0)
				{
					oapiWriteLogV( "(SSV_OV) [INFO] repeated CW msg: %s", msg );
					return;
				}
			}
		}
		lastmsgtime = msgtime;
		oapiWriteLogV( "(SSV_OV) [INFO] CW msg: %s", msg );

		// shift existing msgs
		for (unsigned int i = min(j, 14); i != 0; i--)
		{
			memset( cbuf, 0, 64 );
			ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, i, cbuf, 15, 43 );
			WriteCOMPOOL_AC( SCP_FAULT_DISPBUF, i + 1, cbuf, 15, 43 );
		}

		// add to top
		if (j < 15) j++;
		WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT, j );
		WriteCOMPOOL_AC( SCP_FAULT_DISPBUF, 1, msg, 15, 43 );

		// if no current msg, output to fault msg line, if not then increment msg indicator
		if (ReadCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE ) == 0)
		{
			// show
			WriteCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE, 1 );
			WriteCOMPOOL_AC( SCP_FAULT_MSG_LINE, 1, msg, 15, 43 );
			WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, 0 );
		}
		else
		{
			// increment indicator
			unsigned short ind = ReadCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND );
			if (ind < 99)
			{
				ind++;
				WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, ind );
			}
		}

		// clear any illegal entry indications
		WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, 0 );
		return;
	}

	bool SystemsServicesAnnunciation::OnMajorModeChange( unsigned int newMajorMode )
	{
		return true;
	}
}
