#include "AnnunciationSupport.h"
#include "..\Atlantis.h"


constexpr double CW_B_TIME = 0.32;// BU CW B on time (0.15-0.5s) [s]
constexpr double SM_TONE_DURATION = 1.0;// [s]

namespace dps
{
	AnnunciationSupport::AnnunciationSupport( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "AnnunciationSupport" ),
		SMlight(false), SMtone(false), SMtonetime(0.0), CWalertA(false), CWalertB(false), CWtimerB(CW_B_TIME)
	{
		// init array index
		WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, 1 );
		return;
	}

	AnnunciationSupport::~AnnunciationSupport( void )
	{
		return;
	}

	void AnnunciationSupport::SetClass2Alarm( void )
	{
		unsigned short FF1_IOM10_CH2 = CWalertB ? 0x0008 : 0x0000;
		unsigned short FF2_IOM10_CH2 = CWalertB ? 0x0008 : 0x0000;
		unsigned short FF3_IOM10_CH2 = CWalertA ? 0x0008 : 0x0000;
		unsigned short FF4_IOM10_CH2 = CWalertA ? 0x0008 : 0x0000;
		unsigned short PF1_IOM2_CH0 = CWalertB ? 0x1000 : 0x0000;
		unsigned short PF2_IOM2_CH0 = CWalertA ? 0x1000 : 0x0000;
		WriteCOMPOOL_IS( SCP_FF1_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH2_DATA ) | FF1_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_FF2_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH2_DATA ) | FF2_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_FF3_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH2_DATA ) | FF3_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_FF4_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH2_DATA ) | FF4_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA ) | PF1_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA ) | PF2_IOM2_CH0 );
		return;
	}

	void AnnunciationSupport::SetClass3Alarm( void )
	{
		unsigned short FF1_IOM10_CH2 = (SMlight ? 0x0020 : 0x0000) | (SMtone ? 0x0010 : 0x0000);
		unsigned short FF2_IOM10_CH2 = (SMlight ? 0x0020 : 0x0000) | (SMtone ? 0x0010 : 0x0000);
		unsigned short FF3_IOM10_CH2 = (SMlight ? 0x0020 : 0x0000) | (SMtone ? 0x0010 : 0x0000);
		unsigned short FF4_IOM10_CH2 = (SMlight ? 0x0020 : 0x0000) | (SMtone ? 0x0010 : 0x0000);
		unsigned short PF1_IOM2_CH0 = (SMlight ? 0x4000 : 0x0000) | (SMtone ? 0x2000 : 0x0000);
		unsigned short PF2_IOM2_CH0 = (SMlight ? 0x4000 : 0x0000) | (SMtone ? 0x2000 : 0x0000);
		WriteCOMPOOL_IS( SCP_FF1_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH2_DATA ) | FF1_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_FF2_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH2_DATA ) | FF2_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_FF3_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH2_DATA ) | FF3_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_FF4_IOM10_CH2_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH2_DATA ) | FF4_IOM10_CH2 );
		WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA ) | PF1_IOM2_CH0 );
		WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA ) | PF2_IOM2_CH0 );
		return;
	}

	void AnnunciationSupport::OnPostStep( double simt, double simdt, double mjd )
	{
		bool illegalentry = false;

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

		if (ReadCOMPOOL_IS( SCP_ACK_KEY ) || ReadCOMPOOL_IS( SCP_MSGRESET_KEY ))
		{
			SMlight = false;
			SMtone = false;
			CWalertA = false;
			CWalertB = false;
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
			else if (cw == 3)
			{
				SMlight = true;
				SMtone = true;
				SMtonetime = SM_TONE_DURATION;
				SaveMsg( i, 3 );
			}
			else
			{
				// TODO cw class 5
				illegalentry = true;
			}
		}
		// reset buffer
		WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, 1 );

		// TODO output to fault msg line
		//illegalentry;
		//unsigned short msgline;// 0 = empty, 1 = flash, 2 = static

		// output to CW
		if (SMtone || SMlight) SetClass3Alarm();
		if (CWalertA || CWalertB) SetClass2Alarm();
		return;
	}

	void AnnunciationSupport::SaveMsg( unsigned int idx, unsigned int cwclass )
	{
		// build msg
		char msg[64];
		char fault[32];

		unsigned short usDay, usHour, usMinute, usSecond;
		STS()->GetGPCMET( 1, usDay, usHour, usMinute, usSecond );// TODO get MET the right way

		memset( fault, 0, 32 );
		ReadCOMPOOL_AC( SCP_FAULT_IN_MSG, idx, fault, 5, 19 );
		sprintf_s( msg, "%s  %c   1234  %03d/%02d:%02d:%02d", fault, (cwclass == 2) ? '*' : ' ', usDay, usHour, usMinute, usSecond );
		oapiWriteLogV( "(SSV_OV) [INFO] CW msg: %s", msg );

		// shift existing msgs
		unsigned short j = ReadCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT );
		char cbuf[64];
		for (unsigned int i = min(j, 14); i != 0; i--)
		{
			ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, i, cbuf, 15, 43 );
			WriteCOMPOOL_AC( SCP_FAULT_DISPBUF, i + 1, cbuf, 15, 43 );
		}

		// add to top
		if (j < 15) j++;
		WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT, j );
		WriteCOMPOOL_AC( SCP_FAULT_DISPBUF, 1, msg, 15, 43 );
		return;
	}

	bool AnnunciationSupport::OnMajorModeChange( unsigned int newMajorMode )
	{
		return true;
	}
}