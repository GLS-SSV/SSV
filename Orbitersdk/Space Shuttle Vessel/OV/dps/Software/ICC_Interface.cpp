#include "ICC_Interface.h"
#include "SimpleGPCSoftware.h"
#include "DPS_Reconfiguration.h"
#include "../SimpleGPCSystem.h"


// INFO updated logic to 5 GPCs and 40 HWD buffer

namespace dps
{
	ICC_Interface::ICC_Interface( SimpleGPCSystem* pGPC ):pGPC(pGPC),
		DIN_BUF_POINTER(0), DINB_BITVAL(0), DIN_MSG_SIZE(0), DIN_MSG_INDEX(0),
		DME_A(0), DME_B(0), DME_I(0), DME_FILX(0), DME_GPCI(0), DME_MSGHEAD(0), DME_MSGS(0), DME_RCODE(0), DME_PROCV(0), DME_IMTI(0), DME_MSGTABV(0), DME_NBR_UNIQ{0,0,0,0},
		DME_MSG_VAL{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
	{
		// HACK init buffer
		pGPC->WriteCOMPOOL_IS( SCP_CZ2V_ICC_BUF_POINT, 1 );// start of buffer

		for (int i = 1; i <= 5; i++)
		{
			SCP_ICC_BUF CZ2V_ICC_BUF;
			pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, i, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
			CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[0] = 0xFFFF;// buffer trailer record
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, i, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
		}
		return;
	}

	ICC_Interface::~ICC_Interface( void )
	{
		return;
	}

	void ICC_Interface::DIM_ICC_COLLECTOR( unsigned short* DIN_ARRAY/*Passed_Array*/ )
	{
		DIN_BUF_POINTER = pGPC->ReadCOMPOOL_IS( SCP_CZ2V_ICC_BUF_POINT );
		DINB_BITVAL = DIN_ARRAY[0];
		DIN_MSG_SIZE = DINB_BITVAL & 0x007F;

		if ((DIN_BUF_POINTER + DIN_MSG_SIZE) < 40)
		{
			DIN_MSG_INDEX = (DINB_BITVAL & 0xFF00) >> 8;

			if ((DIN_MSG_INDEX == 0) || (DIN_MSG_INDEX > 28) || (DIN_MSG_SIZE == 0))
			{
				// TODO bad params
			}
			else
			{
				Message_Processing( DIN_ARRAY );

				pGPC->WriteCOMPOOL_IS( SCP_CZ2V_ICC_BUF_POINT, DIN_BUF_POINTER );

				SCP_ICC_BUF CZ2V_ICC_BUF;
				pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, DME_GPCI, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
				CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[DIN_BUF_POINTER - 1] = 0xFFFF;// buffer trailer record
				pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, DME_GPCI, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
			}
		}
		else
		{
			// TODO no fit
		}
		return;
	}

	void ICC_Interface::Message_Processing( unsigned short* DIN_ARRAY/*Passed_Array*/ )
	{
		SCP_ICC_BUF CZ2V_ICC_BUF;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, DME_GPCI, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );

		DME_RCODE = (pGPC->ReadCOMPOOL_AIS( SCP_CZ2V_ICC_MSG_TAB, DIN_MSG_INDEX, 28 ) & 0xF000) >> 12;

		if (DME_RCODE < 14)
		{
			for (int i = 1; i <= DIN_MSG_SIZE; i++)
			{
				CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[DIN_BUF_POINTER - 1]/*GPC_ICC_Buffer_Name[DIN_BUF_POINTER - 1]*/ = DIN_ARRAY[i - 1];

				DIN_BUF_POINTER = DIN_BUF_POINTER + 1;
			}
		}

		// TODO remote data, DME_RCODE == 14 || 15
		/*GPC_ICC_Buffer_Name[DIN_BUF_POINTER - 1] = DINB_BITVAL;

		DIN_BUF_POINTER = DIN_BUF_POINTER + 1;

		DIN_MSG_SIZE = DIN_MSG_SIZE - 1;

		if (DME_RCODE == 15)
		{
			GPC_ICC_Buffer_Name[DIN_BUF_POINTER - 1] = DIN_ARRAY[2 - 1];

			DIN_BUF_POINTER = DIN_BUF_POINTER + 1;

			DIN_MSG_SIZE = DIN_MSG_SIZE - 1;
		}

		Address_Index = DIN_ARRAY[2 - 1];// DIN_ADRINX

		Address_Name = ICC_Address_Name[Address];// DIN_Q

		for (int i = 1; i <= DIN_MSG_SIZE; i++)
		{
			GPC_ICC_Buffer_Name[DIN_BUF_POINTER - 1] = Address_Name(1);
			DIN_BUF_POINTER = DIN_BUF_POINTER + 1;
		}*/
		pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, DME_GPCI, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
		return;
	}

	void ICC_Interface::Processing_Initialization( void )
	{
		DME_GPCI = pGPC->ReadCOMPOOL_IS( SCP_TFCMID );

		DME_FILX = 0x0380;

		// TODO

		for (int i = 0; i < 4; i++) DME_NBR_UNIQ[i] = 0;
		return;
	}

	void ICC_Interface::Valid_Buffer_To_Process( void )
	{
		SCP_ICC_BUF CZ2V_ICC_BUF;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, DME_I, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
		DME_MSGHEAD = CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[DME_A - 1];

		if (DME_MSGHEAD == 0xFFFF)// buffer end
		{
			DME_B = 1;// end of buffer
		}
		else
		{
			DME_IMTI = (DME_MSGHEAD & 0xFF00) >> 8;

			DME_MSGS = DME_MSGHEAD & 0x007F;

			if ((DME_IMTI > 0) && (DME_IMTI <= 28))// valid index
			{
				Valid_IMT();
			}

			DME_A = DME_A + DME_MSGS;

			if (DME_A >= 51)// Max
			{
				DME_B = 1;// end of buffer
			}
		}
		return;
	}

	void ICC_Interface::Valid_IMT( void )
	{
		DME_MSGTABV = pGPC->ReadCOMPOOL_AIS( SCP_CZ2V_ICC_MSG_TAB, DME_IMTI, 28 );

		if ((DME_MSGTABV & 0x0001)/*Contention_Flag*/ == 0)// off
		{
			//Filter_Message_Match = 0;// no match

			if (DME_IMTI == 1)
			{
				Type_1();
			}
			else
			{
				if (DME_IMTI == 2)
				{
					Type_2();
				}
				else
				{
					if ((DME_IMTI >= 3) && (DME_IMTI <= 12))// HACK also allowing indexes 7, 8 and 9 (not used) so they are filtered by DME_FILX and not processed
					{
						if (((1 << DME_IMTI) & DME_FILX) == 0)
						{
							DME_FILX |= 1 << DME_IMTI;

							Routing_Code_Process();
						}
					}
					else
					{
						Type_20p();
					}
				}
			}
		}
		return;
	}

	void ICC_Interface::Type_1( void )
	{
		return;
	}

	void ICC_Interface::Type_2( void )
	{
		return;
	}

	void ICC_Interface::Type_20p( void )
	{
		if ((DME_IMTI == 20) || (DME_IMTI == 21) || (DME_IMTI == 22) || (DME_IMTI == 23))
		{
			unsigned short DME_YY1 = DME_IMTI - 19;// Structure_Copy_Number

			unsigned short DME_YY2 = DME_NBR_UNIQ[DME_YY1 - 1];// Save_Number_Of_Uniques
			
			unsigned short DME_MATCH = 0;// Filtered_Message_Match

			SCP_ICC_BUF CZ2V_ICC_BUF;
			pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, DME_I, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
			if (DME_YY2 != 0)
			{
				for (int i = 1; i <= DME_YY2; i++)
				{
					if (DME_MSG_VAL[DME_YY1 - 1][i - 1] == CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[DME_A - 1])
					{
						DME_MATCH = 1;
					}
				}
			}

			if (DME_MATCH == 0)// no match
			{
				if (DME_YY2 < 16)// HACK added overflow check
				{
					DME_YY2++;

					DME_NBR_UNIQ[DME_YY1 - 1] = DME_YY2;

					DME_MSG_VAL[DME_YY1 - 1][DME_YY2 - 1] = CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[DME_A - 1];
				}
				else
				{
					// TODO log overflow
				}

				Routing_Code_Process();
			}
		}
		else
		{
			// HACK not in diagram, only in text
			Routing_Code_Process();
		}
		return;
	}

	void ICC_Interface::Routing_Code_Process( void )
	{
		DME_RCODE = (DME_MSGTABV & 0xF000) >> 12;

		DME_PROCV = (DME_MSGTABV & 0x0F00) >> 8;

		if ((DME_RCODE == 3) || (DME_RCODE == 14))
		{
			switch (DME_PROCV)
			{
				case 1:
					// Reconfiguration_Message_Handler();// (870)
					break;
				case 2:
					// ICC_Idle_OPS_Processor();// (495)
					break;
				case 3:
					pGPC->pDPS_Reconfiguration->ARD_BUS_CHG( DME_I, DME_A );
					break;
			}
		}
		else
		{
			if (DME_RCODE == 15)
			{
				// Set DME_LOCI (Data_Move_Index) From ICC_Message

				// set DME_J (Get_Data_From_Index) From DME_A

				// Set DME_T (Data_Move_Length) From DME_MSGS

				// loop
			}
		}
		return;
	}

	void ICC_Interface::DME_ICC_ROUT( void )
	{
		Processing_Initialization();

		SCP_GST gst;
		pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, DME_GPCI, &gst, sizes_GST, pos_GST, cnt_GST, 5 );

		for (DME_I = 1; DME_I <= 5; DME_I++)
		{
			DME_A = 1;// first word of buffer

			DME_B = 1;// default to end indication

			unsigned short DME_C = 1 << (5 - DME_I);// Common_Set_Member

			if ((DME_GPCI == DME_I) || (DME_C & gst.CZ2B_CS))
			{
				DME_B = 0;// not end
			}

			while (DME_B == 0)// not end
			{
				Valid_Buffer_To_Process();
			}
		}

		if (0)
		{
			// TODO loop
		}

		pGPC->WriteCOMPOOL_IS( SCP_CZ2V_ICC_BUF_POINT, 1 );// start of buffer

		for (int i = 1; i <= 5; i++)
		{
			SCP_ICC_BUF CZ2V_ICC_BUF;
			pGPC->ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, i, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
			CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF[0] = 0xFFFF;// buffer trailer record
			pGPC->WriteCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, i, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
		}

		//WriteCOMPOOL_IS( SCP_CZ2V_ICC_BUF_FRZ, 0/*? (not frozen)*/ );
		return;
	}
}
