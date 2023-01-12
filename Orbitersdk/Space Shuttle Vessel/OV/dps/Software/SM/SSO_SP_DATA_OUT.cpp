#include "SSO_SP_DATA_OUT.h"


namespace dps
{
	// major field = 3 + 1(space) + 10 + 1(space)
	// minor field = 4
	const char* CRTMSG_PBDSEQFAIL = "    PBD SEQ FAIL   ";
	const char* CRTMSG_PBDCONFIG = "    PBD CONFIG     ";


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

		// HACK ? move PBD fail indications to CSSB_CUR_ANN
		unsigned short CSSB_CUR_ANN = ReadCOMPOOL_IS( SCP_CSSB_CUR_ANN );
		unsigned short CSBB_COMMON_PBD_FAIL_INDICATOR = ReadCOMPOOL_IS( SCP_CSBB_COMMON_PBD_FAIL_INDICATOR );
		if (CSBB_COMMON_PBD_FAIL_INDICATOR)
		{
			CSSB_CUR_ANN |= 0x0040;
			WriteCOMPOOL_IS( SCP_CSSB_CUR_ANN, CSSB_CUR_ANN );
		}
		else
		{
			CSSB_CUR_ANN &= ~0x0040;
			WriteCOMPOOL_IS( SCP_CSSB_CUR_ANN, CSSB_CUR_ANN );
		}
		unsigned short CSBB_PBD_CONFIG_INDICATOR = ReadCOMPOOL_IS( SCP_CSBB_PBD_CONFIG_INDICATOR );
		if (CSBB_PBD_CONFIG_INDICATOR)
		{
			CSSB_CUR_ANN |= 0x0080;
			WriteCOMPOOL_IS( SCP_CSSB_CUR_ANN, CSSB_CUR_ANN );
		}
		else
		{
			CSSB_CUR_ANN &= ~0x0080;
			WriteCOMPOOL_IS( SCP_CSSB_CUR_ANN, CSSB_CUR_ANN );
		}


		unsigned short CSSB_PREV_ANN = ReadCOMPOOL_IS( SCP_CSSB_PREV_ANN );
		if (CSSB_CUR_ANN != CSSB_PREV_ANN)
		{
			if (((CSSB_CUR_ANN & 0x0040) != 0) && ((CSSB_PREV_ANN & 0x0040) == 0))
			{
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_PBDSEQFAIL, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}
			if (((CSSB_CUR_ANN & 0x0080) != 0) && ((CSSB_PREV_ANN & 0x0080) == 0))
			{
				unsigned int j = ReadCOMPOOL_IS( SCP_FAULT_IN_IDX );
				if (j < 5)
				{
					WriteCOMPOOL_AC( SCP_FAULT_IN_MSG, j, CRTMSG_PBDCONFIG, 5, 19 );
					WriteCOMPOOL_AIS( SCP_FAULT_IN_CWCLASS, j, 3, 5 );
					WriteCOMPOOL_IS( SCP_FAULT_IN_IDX, ++j );
				}
			}

			WriteCOMPOOL_IS( SCP_CSSB_PREV_ANN, CSSB_CUR_ANN );
		}

		// output to PF MDMs
		WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA ) | PF01_OUTPUT_1 );
		WriteCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA ) | PF01_OUTPUT_2 );
		WriteCOMPOOL_IS( SCP_PF1_IOM14_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM14_CH0_DATA ) | PF01_OUTPUT_3 );
		WriteCOMPOOL_IS( SCP_PF1_IOM14_CH2_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM14_CH2_DATA ) | PF01_OUTPUT_4 );

		WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA ) | PF02_OUTPUT_1 );
		WriteCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA ) | PF02_OUTPUT_2 );
		WriteCOMPOOL_IS( SCP_PF2_IOM14_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM14_CH0_DATA ) | PF02_OUTPUT_3 );
		WriteCOMPOOL_IS( SCP_PF2_IOM14_CH2_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM14_CH2_DATA ) | PF02_OUTPUT_4 );
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
