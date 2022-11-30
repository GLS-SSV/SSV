#include "SSO_SP_DATA_OUT.h"


namespace dps
{
	// SSB applicable bit masks
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_1 = 0x01FF;
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_2 = 0x03FF;
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_3 = 0x033F;
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_4 = 0x01FF;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_1 = 0x01FF;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_2 = 0x03FF;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_3 = 0x00FF;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_4 = 0x0002;


	SSO_SP_DATA_OUT::SSO_SP_DATA_OUT( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SSO_SP_DATA_OUT" ),
		PF01_OUTPUT_1(0), PF01_OUTPUT_2(0), PF01_OUTPUT_3(0), PF01_OUTPUT_4(0),
		PF02_OUTPUT_1(0), PF02_OUTPUT_2(0), PF02_OUTPUT_3(0), PF02_OUTPUT_4(0)
	{
		return;
	}

	SSO_SP_DATA_OUT::~SSO_SP_DATA_OUT( void )
	{
		return;
	}

	bool SSO_SP_DATA_OUT::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void SSO_SP_DATA_OUT::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void SSO_SP_DATA_OUT::OnPostStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_CSBB_PBD_OUTPUT_INDICATOR ) == 1)
		{
			unsigned short SetMask;
			unsigned short ResetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF01_OUTPUT_1 );
			ResetMask = ~SetMask & SBB_ABM_PF01_OUTPUT_1;
			PF01_OUTPUT_1 &= ~ResetMask;
			PF01_OUTPUT_1 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF01_OUTPUT_2 );
			ResetMask = ~SetMask & SBB_ABM_PF01_OUTPUT_2;
			PF01_OUTPUT_2 &= ~ResetMask;
			PF01_OUTPUT_2 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF01_OUTPUT_3 );
			ResetMask = ~SetMask & SBB_ABM_PF01_OUTPUT_3;
			PF01_OUTPUT_3 &= ~ResetMask;
			PF01_OUTPUT_3 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF01_OUTPUT_4 );
			ResetMask = ~SetMask & SBB_ABM_PF01_OUTPUT_4;
			PF01_OUTPUT_4 &= ~ResetMask;
			PF01_OUTPUT_4 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF02_OUTPUT_1 );
			ResetMask = ~SetMask & SBB_ABM_PF02_OUTPUT_1;
			PF02_OUTPUT_1 &= ~ResetMask;
			PF02_OUTPUT_1 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF02_OUTPUT_2 );
			ResetMask = ~SetMask & SBB_ABM_PF02_OUTPUT_2;
			PF02_OUTPUT_2 &= ~ResetMask;
			PF02_OUTPUT_2 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF02_OUTPUT_3 );
			ResetMask = ~SetMask & SBB_ABM_PF02_OUTPUT_3;
			PF02_OUTPUT_3 &= ~ResetMask;
			PF02_OUTPUT_3 |= SetMask;

			SetMask = ReadCOMPOOL_IS( SCP_CSBB_PF02_OUTPUT_4 );
			ResetMask = ~SetMask & SBB_ABM_PF02_OUTPUT_4;
			PF02_OUTPUT_4 &= ~ResetMask;
			PF02_OUTPUT_4 |= SetMask;
		}
		else
		{
			// TODO
		}

		unsigned short CUR_ANN = ReadCOMPOOL_IS( SCP_CSSB_CUR_ANN );
		unsigned short PREV_ANN = ReadCOMPOOL_IS( SCP_CSSB_PREV_ANN );
		if (CUR_ANN != PREV_ANN)
		{
			if (((CUR_ANN & 0x0001) != 0) && ((PREV_ANN & 0x0001) == 0))
			{
				// TODO fault message annunciation
			}
			if (((CUR_ANN & 0x0002) != 0) && ((PREV_ANN & 0x0002) == 0))
			{
				// TODO fault message annunciation
			}

			PREV_ANN = CUR_ANN;
		}

		// output to PF MDMs
		WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, PF01_OUTPUT_1 );
		WriteCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA, PF01_OUTPUT_2 );
		WriteCOMPOOL_IS( SCP_PF1_IOM14_CH0_DATA, PF01_OUTPUT_3 );
		WriteCOMPOOL_IS( SCP_PF1_IOM14_CH2_DATA, PF01_OUTPUT_4 );

		WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, PF02_OUTPUT_1 );
		WriteCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA, PF02_OUTPUT_2 );
		WriteCOMPOOL_IS( SCP_PF2_IOM14_CH0_DATA, PF02_OUTPUT_3 );
		WriteCOMPOOL_IS( SCP_PF2_IOM14_CH2_DATA, PF02_OUTPUT_4 );
		return;
	}

	bool SSO_SP_DATA_OUT::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 201:
			case 202:
				return true;
			default:
				return false;
		}
	}
}
