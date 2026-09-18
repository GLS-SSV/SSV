#include "SSO_SP_DATA_OUT.h"
#include "../SimpleFCOS_IO.h"


namespace dps
{
/*
Some of the standard Orbiter SM Special Processes require outputs (ID
48) through the PL MDMs. These outputs are requested by SSO_SP_DATA_OUT
which is called by SSP_EXEC every other major cycle. The discrete out-
puts are stored and updated by the controlling processes in the CSS_SPOB
compool. At the time of output, the stored output card image is
inverted and "logical AND'ed" with an applicable bit mask to create the
reset mask, with the original stored form representing the set mask. The
set and reset masks for each parent word are output to FCOS via SVC
request by SSO. This system of applicable bit masks (a modification of
the whole word complementing system) allows SM to assure positive con-
trol of bits applicable to SM and to leave alone bits not used by SM. A
small number of analog outputs are also SVC'ed from this compool to
drive Auxiliary Power Unit (APU) fuel and hydraulic H2O boiler quantity
meters with SM-computed values. If a PL bay door sequence or operation
is in progress (MM 202), SSO may additionally be called by
SSB_PL_BAY_DOORS (the PL Bay Door Special Process) if a PL bay door
"STOP" is sensed in the high-rate inputs. This feature is required to
ensure a timely stop of door or latch motion if the crew sees something
going wrong by having to run SSO at a faster rate than 0.52 Hz.
*/

	// major field = 3 + 1(space) + 10 + 1(space)
	// minor field = 4
	const char* CRTMSG_PBDSEQFAIL = "    PBD SEQ FAIL   ";
	const char* CRTMSG_PBDCONFIG = "    PBD CONFIG     ";


	// SSB applicable bit masks
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_1 = 0xFF80;
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_2 = 0xFFC0;
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_3 = 0xFCC0;
	constexpr unsigned short SBB_ABM_PF01_OUTPUT_4 = 0xFF80;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_1 = 0xFF80;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_2 = 0xFFC0;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_3 = 0xFF00;
	constexpr unsigned short SBB_ABM_PF02_OUTPUT_4 = 0x4000;


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

	void SSO_SP_DATA_OUT::Call( void )
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


		BUS_ID bus;
		// MDM PF 1
		bus = BUS_PL1;
		GetFCOS_IO()->OutputMDM( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF1_IOM2_CH0_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_PF1_IOM7_CH0_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_0, SCP_PF1_IOM14_CH0_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF1_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_2, SCP_PF1_IOM14_CH2_DATA, bus );

		// MDM PF 2
		bus = BUS_PL2;
		GetFCOS_IO()->OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM2, ChannelAddress_0, SCP_PF2_IOM2_CH0_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM7, ChannelAddress_0, SCP_PF2_IOM7_CH0_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM10, ChannelAddress_2, SCP_PF2_IOM10_CH2_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_0, SCP_PF2_IOM14_CH0_DATA, bus );
		GetFCOS_IO()->OutputMDM( MDM_PF2_Address, ModeControl_MDM_Receive, ModuleAddress_IOM14, ChannelAddress_2, SCP_PF2_IOM14_CH2_DATA, bus );
		return;
	}
}
