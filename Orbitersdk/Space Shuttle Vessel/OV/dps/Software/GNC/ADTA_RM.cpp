#include "ADTA_RM.h"


namespace dps
{
	ADTA_RM::ADTA_RM( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ADTA_RM" )
	{
		return;
	}

	ADTA_RM::~ADTA_RM( void )
	{
		return;
	}

	void ADTA_RM::OnPreStep( double simt, double simdt, double mjd )
	{
		unsigned short FF1_IOM9_CH2_DATA = ReadCOMPOOL_IS( SCP_FF1_IOM9_CH2_DATA );
		unsigned short FF2_IOM9_CH2_DATA = ReadCOMPOOL_IS( SCP_FF2_IOM9_CH2_DATA );
		unsigned short FF3_IOM9_CH2_DATA = ReadCOMPOOL_IS( SCP_FF3_IOM9_CH2_DATA );
		unsigned short FF4_IOM9_CH2_DATA = ReadCOMPOOL_IS( SCP_FF4_IOM9_CH2_DATA );

		unsigned short L_D1 = (FF1_IOM9_CH2_DATA & 0x0400) >> 10;
		unsigned short L_S1 = (FF1_IOM9_CH2_DATA & 0x0800) >> 11;
		unsigned short L_D2 = (FF2_IOM9_CH2_DATA & 0x0400) >> 10;
		unsigned short L_S2 = (FF2_IOM9_CH2_DATA & 0x0800) >> 11;
		unsigned short R_D1 = (FF3_IOM9_CH2_DATA & 0x0400) >> 10;
		unsigned short R_S1 = (FF3_IOM9_CH2_DATA & 0x0800) >> 11;
		unsigned short R_D2 = (FF4_IOM9_CH2_DATA & 0x0400) >> 10;
		unsigned short R_S2 = (FF4_IOM9_CH2_DATA & 0x0800) >> 11;

		unsigned short L_D1_CF = 0;// TODO
		unsigned short L_S1_CF = 0;// TODO
		unsigned short L_D2_CF = 0;// TODO
		unsigned short L_S2_CF = 0;// TODO
		unsigned short R_D1_CF = 0;// TODO
		unsigned short R_S1_CF = 0;// TODO
		unsigned short R_D2_CF = 0;// TODO
		unsigned short R_S2_CF = 0;// TODO

		unsigned short L_PROBE_DEPLOY = ((L_D1 & !L_D1_CF & !L_S1 & !L_S1_CF) | (L_D2 & !L_D2_CF & !L_S2 & !L_S2_CF)) & 0x1;
		unsigned short R_PROBE_DEPLOY = ((R_D1 & !R_D1_CF & !R_S1 & !R_S1_CF) | (R_D2 & !R_D2_CF & !R_S2 & !R_S2_CF)) & 0x1;

		WriteCOMPOOL_IS( SCP_L_PROBE_DEPLOY, L_PROBE_DEPLOY );
		WriteCOMPOOL_IS( SCP_R_PROBE_DEPLOY, R_PROBE_DEPLOY );
		return;
	}

	bool ADTA_RM::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 304:
			case 305:
			case 602:
			case 603:
				return true;
			default:
				return false;
		}
	}

	bool ADTA_RM::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ADTA_RM::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}
}
