#include "DGI_LDB_IO.h"
#include "SimpleFCOS_IO.h"
#include "BusDefs.h"


namespace dps
{
	constexpr unsigned short DGI_ERR_MASK = 0x0820;// Error_Mask

	// LDB_IRW values
	constexpr unsigned short LDB_IRW_SEND_DATA = 0b1011;// Send Data
	constexpr unsigned short LDB_IRW_HAVE_DATA = 0b0110;// Have Data
	constexpr unsigned short LDB_IRW_NONEEDFORBUS = 0b0011;// No Need For Bus

	// CDVV_LDB_STAT values (all values made up)
	constexpr unsigned short LDB_STAT_OK = 0x0000;// OK
	constexpr unsigned short LDB_STAT_INV_OP_CODE = 0x0820;// Invalid Op Code
	constexpr unsigned short LDB_STAT_SUM_ERR = 0x0020;// Sumcheck Error
	constexpr unsigned short LDB_STAT_IO_ERR = 0x0800;// IO Error


	DGI_LDB_IO::DGI_LDB_IO( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "DGI_LDB_IO" )
	{
		return;
	}

	DGI_LDB_IO::~DGI_LDB_IO( void )
	{
		return;
	}

	void DGI_LDB_IO::OnPreStep( double simt, double simdt, double mjd )
	{
		WriteCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW, 0 );

		//if (ReadCOMPOOL_IS( SCP_CZ1B_V_VALID_OPS ) == 1)// true
		//{
			//WriteCOMPOOL_IS( SCP_DGI_IBUF_ADDR, Address );// VCO_Input_Buffer

			//WriteCOMPOOL_IS( SCP_DGI_IOERR_CODE, Address );// VCO_Transaction_Status_Word
		//}
		//else
		{
			WriteCOMPOOL_IS( SCP_DGI_IBUF_ADDR, SCP_CDVV_LDB_IRW );// LDB_Input_Buffer

			WriteCOMPOOL_IS( SCP_DGI_IOERR_CODE, SCP_CDVV_LDB_IRW_TSW );// LDB_Transaction_Status_Word
		}

		if (ReadCOMPOOL_IS( SCP_CDVB_XMIT_FLAG ) == 1)// true
		{
			// HACK removed checksum word
			WriteCOMPOOL_IS( SCP_DGI_IWD_PARMS_DDCNT, ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG ) /*- 1*/ );

			GetFCOS_IO()->IO_LDB( 2 );

			if (ReadCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW ) == 0)
			{
				if (((ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0xF000) >> 12) == LDB_IRW_SEND_DATA)
				{
					Transmit_Sequence_Process();
				}
				else
				{
					if (((ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0xF000) >> 12) == LDB_IRW_HAVE_DATA)
					{
						Receive_Sequence_Process();
					}
					else
					{
						if (((ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0xF000) >> 12) != LDB_IRW_NONEEDFORBUS)
						{
							CDVV_LDB_STAT = LDB_STAT_INV_OP_CODE;

							WriteCOMPOOL_IS( SCP_DGI_STAT_PARMS_DDMASK, CDVV_LDB_STAT );

							GetFCOS_IO()->IO_LDB( 6 );
						}
					}
				}
			}
			else
			{
				LDB_Error_Processor();
			}
		}
		else
		{
			GetFCOS_IO()->IO_LDB( 1 );

			if (ReadCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW ) == 0)
			{
				if (((ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0xF000) >> 12) == LDB_IRW_HAVE_DATA)
				{
					Receive_Sequence_Process();
				}
				else
				{
					if (((ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0xF000) >> 12) != LDB_IRW_NONEEDFORBUS)
					{
						CDVV_LDB_STAT = LDB_STAT_INV_OP_CODE;

						WriteCOMPOOL_IS( SCP_DGI_STAT_PARMS_DDMASK, CDVV_LDB_STAT );

						GetFCOS_IO()->IO_LDB( 6 );
					}
				}
			}
			else
			{
				LDB_Error_Processor();
			}
		}
		return;
	}

	void DGI_LDB_IO::Transmit_Sequence_Process( void )
	{
		//if (ReadCOMPOOL_IS( SCP_CZ1B_V_VALID_OPS ) == 1)// true
		//{
			//VCO_Send_Word_Count = ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG );

			//VCO_Send_NZB_Count = ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG ) - 1;

			//Zero Retransmit(5) in VCO_Send_Word_Count

			//GetFCOS_IO()->IO_LDB( 4 );
		//}
		//else
		{
			// HACK using CDVV_OUT_MSG_LENG instead of LDB_Send_Word_Count
			//LDB_Send_Word_Count = ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG );

			// TODO LDB_Send_NZB_Count = ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG ) - 1;

			// TODO LDB_Send_Word_Count &= 0xF7FF;

			GetFCOS_IO()->IO_LDB( 4 );
		}

		WriteCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW, 0 );

		//Interrogate_Error_Pointer /*CDVV_LDB_IRW_IERR*/ = 0;

		GetFCOS_IO()->IO_LDB( 5 );

		//if (CDVV_LDB_IRW_TSW == 0)
		if (ReadCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW ) != 0)// HACK corrected test
		{
			/*if (Interrogate_Error_Pointer != 0)
			{
				Interrogate_Error_Pointer = Interrogate_Error_Pointer + 2;

				Error_Data_Structure = Interrogate_Error_Pointer;

				if (Error_Data_Pointer(26) == 1)
				{
					WriteCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG, ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG ) | 0x0800 );
				}
			}*/

			/*if (ReadCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW ) & 0x1000)
			{
				WriteCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG, ReadCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG ) | 0x0800 );
			}*/

			LDB_Error_Processor();
		}
		else
		{
			CDVV_ERR_COUNT = 0;

			WriteCOMPOOL_IS( SCP_CDVB_XMIT_FLAG, 0 );

			WriteCOMPOOL_IS( SCP_CDVV_OUT_MSG_LENG, 0 );

			WriteCOMPOOL_IS( SCP_CDVE_LDB_ACTV, 0 );// false
		}
		return;
	}

	void DGI_LDB_IO::Receive_Sequence_Process( void )
	{
		CDVV_LDB_STAT = 0;

		WriteCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW, 0 );

		// HACK removed checksum word
		//CDVV_IN_WDCOUNT = (ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0x0FFF) + 1;
		CDVV_IN_WDCOUNT = ReadCOMPOOL_IS( SCP_CDVV_LDB_IRW ) & 0x0FFF;

		//if (ReadCOMPOOL_IS( SCP_CZ1B_V_VALID_OPS ) == 1)
		//{
			//VCO_Receive_Word_Count = CDVV_IN_WDCOUNT;

			//GetFCOS_IO()->IO_LDB( 3 );
		//}
		//else
		{
			WriteCOMPOOL_IS( SCP_DGI_GO_PARMS_DWDCT, CDVV_IN_WDCOUNT );

			WriteCOMPOOL_IS( SCP_DGI_IBUF_ADDR, SCP_CDVV_LDB_FWD_IBUF );// HACK set input destination to CDVV_LDB_FWD_IBUF

			GetFCOS_IO()->IO_LDB( 3 );
		}

		if (ReadCOMPOOL_ID( SCP_CDVV_LDB_IRW_TSW ) == 0)
		{
			//if (ReadCOMPOOL_IS( SCP_CZ1B_V_VALID_OPS ) == 1)
			//{
				//DGI_TEMP_SUMCHECK = input checksum;

				//set End_Message_Pointer = end of VCO Message

				//DGI_CURR_TRANSACT = Input_Transaction_ID;

				//DGI_FUNC_DEST = Input_Destination;

				//DGI_DEU_ID = LDB_DEU_Number;

				//DGI_SUMCHECK_COUNT = CDVV_IN_WDCOUNT - 1;

				//Checksum_Generation();// 291
			//}
			//else
			{
				//DGI_TEMP_SUMCHECK = input checksum;

				//set End_Message_Pointer = end of LDB Message

				DGI_CURR_TRANSACT = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 1, 134 ) & 0x07FF;

				DGI_FUNC_DEST = (ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 1, 134 ) & 0xF800) >> 11;

				DGI_DEU_ID = (ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 2, 134 ) & 0x0700) >> 8;

				// HACK removed checksum word
				//DGI_SUMCHECK_COUNT = CDVV_IN_WDCOUNT - 1;

				//Checksum_Generation();// 291
			}

			//if (Computed Checksum == DGI_TEMP_SUMCHECK)
			{
				Message_Validition_Process();
			}
			/*else
			{
				CDVV_LDB_STAT = LDB_STAT_SUM_ERR;
			}*/
		}
		else
		{
			CDVV_LDB_STAT = LDB_STAT_IO_ERR;
		}

		WriteCOMPOOL_IS( SCP_DGI_STAT_PARMS_DDMASK, CDVV_LDB_STAT );

		GetFCOS_IO()->IO_LDB( 6 );

		DGI_ERR_TEST = CDVV_LDB_STAT & DGI_ERR_MASK;

		if (DGI_ERR_TEST != 0)
		{
			LDB_Error_Processor();
		}
		else
		{
			CDVV_ERR_COUNT = 0;

			if (CDVV_LDB_STAT == 0)
			{
				CDVV_OLD_TRANSACT = DGI_CURR_TRANSACT;

				if (DGI_FUNC_DEST > 6)
				{
					TCSS_Interface_Check_Process();
				}

				LDB_Message_Router_Process();
			}
		}
		return;
	}

	void DGI_LDB_IO::LDB_Error_Processor( void )
	{
		CDVV_ERR_COUNT = CDVV_ERR_COUNT + 1;

		if (CDVV_ERR_COUNT == 3)
		{
			CDVV_ERR_COUNT = 0;

			// TODO bus swap
			/*if (GPC_ID == GPC_Prime)
			{
				if (IOP_Transmitter_State(22) == 1)
				{
					LDB_Command_Bus = 23;
				}
				else
				{
					LDB_Command_Bus = 22;
				}

				// issue reconfig SVC
			}
			else
			{
				if (IOP_Transmitter_State(22) == 1)
				{
					LDB_Listen_Bus = 23;
				}
				else
				{
					LDB_Listen_Bus = 22;
				}

				LDB_Prime_ID = GPC_Prime_ID;

				// issue reconfig SVC
			}*/
		}
		return;
	}

	void DGI_LDB_IO::Message_Validition_Process( void )
	{
		return;
	}

	void DGI_LDB_IO::TCSS_Interface_Check_Process( void )
	{
		return;
	}

	void DGI_LDB_IO::LDB_Message_Router_Process( void )
	{
		// TODO just write RSLS (and etc) vars to memory as they arrive
		double GMTLO;
		uint64_t gmtlo64;
		gmtlo64 = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 7, 134 );
		gmtlo64 = (gmtlo64 << 16) | ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 6, 134 );
		gmtlo64 = (gmtlo64 << 16) | ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 5, 134 );
		gmtlo64 = (gmtlo64 << 16) | ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 4, 134 );
		memcpy( &GMTLO, &gmtlo64, 8 );
		unsigned short GMTLOSetCommand = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 8, 134 );
		unsigned short LPSCountdownHold = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 9, 134 );
		unsigned short LPSGoForAutoSequenceStart = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 10, 134 );
		unsigned short LPSGoForEngineStart = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 11, 134 );
		unsigned short ResumeCountCommand = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 12, 134 );
		unsigned short MPS_Slew = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 13, 134 );
		unsigned short Aero_Slew = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 14, 134 );
		unsigned short SRB_Slew = ReadCOMPOOL_AIS( SCP_CDVV_LDB_FWD_IBUF, 15, 134 );

		oapiWriteLogV( "GMTLO=%lf", GMTLO );
		oapiWriteLogV( "GMTLOSetCommand=%d", GMTLOSetCommand );
		oapiWriteLogV( "LPSCountdownHold=%d", LPSCountdownHold );
		oapiWriteLogV( "LPSGoForAutoSequenceStart=%d", LPSGoForAutoSequenceStart );
		oapiWriteLogV( "LPSGoForEngineStart=%d", LPSGoForEngineStart );
		oapiWriteLogV( "ResumeCountCommand=%d", ResumeCountCommand );
		oapiWriteLogV( "MPS_Slew=%d", MPS_Slew );
		oapiWriteLogV( "Aero_Slew=%d", Aero_Slew );
		oapiWriteLogV( "SRB_Slew=%d", SRB_Slew );

		WriteCOMPOOL_SD( SCP_PRED_GMT_LO, GMTLO );
		WriteCOMPOOL_IS( SCP_GMTLO_SET, GMTLOSetCommand );
		WriteCOMPOOL_IS( SCP_LPS_COUNTDOWN_HOLD, LPSCountdownHold );
		WriteCOMPOOL_IS( SCP_RS_AUTO_SEQ_START, LPSGoForAutoSequenceStart );
		WriteCOMPOOL_IS( SCP_LPS_GO_FOR_ENGINE_START, LPSGoForEngineStart );
		WriteCOMPOOL_IS( SCP_RESUME_COUNT, ResumeCountCommand );
		WriteCOMPOOL_IS( SCP_MPS_SLEW, MPS_Slew );
		WriteCOMPOOL_IS( SCP_AERO_SLEW, Aero_Slew );
		WriteCOMPOOL_IS( SCP_SRB_SLEW, SRB_Slew );
		return;
	}
}
