#include "DGO_LDB_COORD.h"


namespace dps
{
	DGO_LDB_COORD::DGO_LDB_COORD( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "DGO_LDB_COORD" )
	{
		return;
	}

	DGO_LDB_COORD::~DGO_LDB_COORD( void )
	{
		return;
	}

	void DGO_LDB_COORD::Call( const unsigned short DGO_BUFFER_ID, const unsigned short DGO_WDCOUNT )
	{
		if (ReadCOMPOOL_IS( SCP_CDVE_LDB_ACTV ) == 1)
		{
			// HACK ignore further messages after first
			return;
		}

		WriteCOMPOOL_IS( SCP_CDVE_LDB_ACTV, 1 );

		switch (DGO_BUFFER_ID)
		{
			case 1:
				// move data from TCS_Input_Buffer to VCO_Output_Buffer
				break;
			case 2:
				// move data from TCS_Input_Buffer to VCO_Output_Buffer
				break;
			case 3:
				// move data from SACS_Response to LDB_Output_Buffer
				// HACK using SACS buffer for RSLS->LPS data
				for (int i = 1; i <= DGO_WDCOUNT; i++)
				{
					WriteCOMPOOL_AIS( SCP_CDVV_LDB_OUT_DATA, i, ReadCOMPOOL_AIS( SCP_CVAV_RESPONSE_DATA, i, 7 ), 137 );
				}
				break;
			case 4:
				// move data from Waveform_Generator_Error_Response to VCO_Output_Buffer
				break;
			case 5:
				// move first 7 words from MM_Response to VCO_Output_Buffer
				/*if (output_word_count > 7)
				{
					if (MM_Request == "MM_Read")
					{
						MM_Output_Block_Index = MM_Input_Block_ID + 1;
						// move 512 words from MM_Read_Write_Buffer to VCO_Output_Buffer
					}
					else
					{
						// move 512 words from MM_Read_Write_Buffer to VCO_Output_Buffer
					}
				}*/
				break;
			case 7:
				// move data from TCS_Input_Buffer to VCO_Output_Buffer
				break;
			case 8:
				// move data from Ramp_Error_Response to VCO_Output_Buffer
				break;
		}

		//if (ReadCOMPOOL_IS( SCP_CZ1B_V_VALID_OPS ) == 1)
		//{
			//FIOCGR();// Checksum VCO_Output_Buffer
		//}
		//else
		{
			// TODO FIOCGR();// Checksum LDB_Output_Buffer
		}

		// HACK removed checksum word
		WriteCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG, DGO_WDCOUNT /*+ 1*/ );

		WriteCOMPOOL_IS( SCP_CDVB_XMIT_FLAG, 1 );
		return;
	}
}
