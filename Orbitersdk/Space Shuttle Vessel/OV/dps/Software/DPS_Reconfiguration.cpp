#include "DPS_Reconfiguration.h"


namespace dps
{
	DPS_Reconfiguration::DPS_Reconfiguration( SimpleGPCSystem* pGPC ):SimpleGPCSoftware( pGPC, "DPS_Reconfiguration" ),
		ARDVL_CRT(0), ARDVL_MF(0), ARDVL_CMDR_SET(0), ARDVL_NEW_CMDR(0), ARDVL_CURR_CMDR(0), ARDVL_CRT_FLG{0,0,0,0}, ARDVL_RUN(0), ARDVL_STBY(0), ARDVL_ZERO(0), ARDVL_BUS(0),
		ARDVL_MF_FLAG(false), STAT(false)
	{
		return;
	}

	DPS_Reconfiguration::~DPS_Reconfiguration( void )
	{
		return;
	}

	void DPS_Reconfiguration::ARD_BUS_CHG( unsigned short B, unsigned short I )
	{
		SCP_ICC_BUF buf;
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, B, &buf, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
		unsigned short Input_Message_Type = (buf.CZ2V_ICC_MSG_BUF[I - 1 + 1] & 0xE000) >> 12;

		switch (Input_Message_Type)
		{
			case 0:// MF Change
				Major_Function_Switch_Change_Processing( buf.CZ2V_ICC_MSG_BUF[I - 1 + 1] );
				break;
			case 1:// GPC/CRT
				CMPTR_CRT_Key_Processing();
				break;
			case 2:// CMPTR/BUS (ALT only)
				break;
			case 3:// OPS Initiate
				OPS_Initiate_Processing();
				break;
			case 4:// Fail To Sync
				Fail_To_Sync_Processing();
				break;
			case 5:// Force OPS 0
				Force_OPS_0_Processing();
				break;
		}
		return;
	}

	void DPS_Reconfiguration::Major_Function_Switch_Change_Processing( unsigned short iccmsg )
	{
		{
			ARDVL_CRT = (iccmsg & 0x001C) >> 2;
			ARDVL_MF = (iccmsg & 0x0003) + 1;

			unsigned short GPC_ID = ReadCOMPOOL_IS( SCP_TFCMID );

			if (GPC_ID == 1)
			{
				// GNC
				if (ARDVL_MF == 2) ARDVL_NEW_CMDR = 1;
				else ARDVL_NEW_CMDR = 2;

			}
			else
			{
				// SM
				if (ARDVL_MF == 3) ARDVL_NEW_CMDR = 2;
				else ARDVL_NEW_CMDR = 1;
			}

			WriteCOMPOOL_AIS( SCP_CZ2V_MF_OLD, ARDVL_CRT, ARDVL_MF - 1, 4 );

			SCP_GST gst;
			ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, GPC_ID, &gst, sizes_GST, pos_GST, cnt_GST, 5 );
			if (ARDVL_NEW_CMDR == GPC_ID)
			{
				gst.CZ2B_ACT_XMITR1 |= (0x0040 << (4 - ARDVL_CRT));
				gst.CZ2B_ACT_RECVR |= (0x00400000 << (4 - ARDVL_CRT));
			}
			else
			{
				gst.CZ2B_ACT_XMITR1 &= ~(0x0040 << (4 - ARDVL_CRT));
				gst.CZ2B_ACT_RECVR &= ~(0x00400000 << (4 - ARDVL_CRT));
			}
			WriteCOMPOOL_ASTRUCT( SCP_CZ2V_GST, GPC_ID, &gst, sizes_GST, pos_GST, cnt_GST, 5 );

			SCP_DIT dit;
			ReadCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ARDVL_CRT, &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );

			dit.CZ1V_D_DIT_KYBD_MSG[0] = 0x20;// DEU_GPC_KEY_CODE_MFSWITCH
			dit.CZ1V_D_DIT_KYBD_MSG[1] = (GPC_ID == ARDVL_NEW_CMDR) ? 0 : 1;
			dit.CZ1V_D_NUMOFKEYS = 2;

			WriteCOMPOOL_ASTRUCT( SCP_CZ1V_D_DIT, ARDVL_CRT, &dit, sizes_DIT, pos_DIT, cnt_DIT, 4 );

			WriteCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY, ReadCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY ) | (0x1000 >> (ARDVL_CRT - 1)) );
			WriteCOMPOOL_IS( SCP_CZ1E_D_MCDS_EVENT, 1 );
			return;
		}
		// NBAT
		// GRT - GPC Reconfiguration Table
		// BAT - Bus Assignment Table

		// see section 3.5.000
		// item 1-6 = GRT
		// 1 - G1
		// 2 - G2
		// 3 - G3
		// 4 - SM2
		// 5 - (SM4)
		// 6 - PL9
		// 7 - (n/a)
		// 8 - G8
		// 9 - G9


		ARDVL_CRT = (iccmsg & 0x000C) >> 2;
		ARDVL_MF = (iccmsg & 0x0003) + 1;

		ARDVL_CMDR_SET = 0;

		SCP_GST gst[5];
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, 1, &gst[0], sizes_GST, pos_GST, cnt_GST, 5 );
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, 2, &gst[1], sizes_GST, pos_GST, cnt_GST, 5 );
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, 3, &gst[2], sizes_GST, pos_GST, cnt_GST, 5 );
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, 4, &gst[3], sizes_GST, pos_GST, cnt_GST, 5 );
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, 5, &gst[4], sizes_GST, pos_GST, cnt_GST, 5 );

		if (ARDVL_CRT_FLG[ARDVL_CRT - 1] != 0)
		{
			ARDVL_NEW_CMDR = ARDVL_CRT_FLG[ARDVL_CRT - 1];
			ARDVL_CRT_FLG[ARDVL_CRT - 1] = 0;
		}
		else
		{
			SCP_CCATS ccats;
			ReadCOMPOOL_ASTRUCT( SCP_CZ2V_CCATS, ARDVL_MF, &ccats, sizes_CCATS, pos_CCATS, cnt_CCATS, 3 );

			if ((ccats.CZ2V_CCAT[ARDVL_CRT - 1] != 0) && (gst[ccats.CZ2V_CCAT[ARDVL_CRT - 1] - 1].CZ2V_CURRENT_OPS[ARDVL_MF - 1] != 0))
			{
				ARDVL_NEW_CMDR = ccats.CZ2V_CCAT[ARDVL_CRT - 1];
			}
			else
			{
				ARDVL_NEW_CMDR = 0;
				ARDVL_RUN = 0;
				ARDVL_STBY = 0;
				ARDVL_ZERO = 0;

				unsigned short GPC_ID = ReadCOMPOOL_IS( SCP_TFCMID );
				for (int GPC = 5; GPC >= 1; GPC--)
				{
					if ((GPC == GPC_ID) || ((1 << (5 - GPC)) & gst[GPC_ID - 1].CZ2B_CS))
					{
						if (gst[GPC - 1].CZ2V_CURRENT_OPS[ARDVL_MF - 1] != 0)
						{
							if (gst[GPC - 1].CZ2B_RS != 0)
							{
								ARDVL_NEW_CMDR = ReadCOMPOOL_IS( SCP_CZ2V_GPC_P );
								break;
							}
							else
							{
								unsigned short Discrete_Bit_Run_Mode = (0x2000 & ReadCOMPOOL_IS( SCP_CZ2B_DIA1 )) >> 13;
								if (Discrete_Bit_Run_Mode == 1)
								{
									ARDVL_RUN = GPC;
								}
								else
								{
									ARDVL_STBY = GPC;
								}
							}
						}

						if ((gst[GPC - 1].CZ2V_CURRENT_OPS[0] == 0) && (gst[GPC - 1].CZ2V_CURRENT_OPS[1] == 0) && (gst[GPC - 1].CZ2V_CURRENT_OPS[2] == 0))
						{
							ARDVL_ZERO = GPC;
						}
					}
				}

				if (ARDVL_NEW_CMDR == 0)
				{
					Major_Function_Hierarchy();
				}
			}
		}

		if ((gst[ARDVL_NEW_CMDR - 1].CZ2V_CURRENT_OPS[0] == 0) && (gst[ARDVL_NEW_CMDR - 1].CZ2V_CURRENT_OPS[1] == 0) && (gst[ARDVL_NEW_CMDR - 1].CZ2V_CURRENT_OPS[2] == 0))
		{
			ARDVL_CMDR_SET = 0x0010 >> (ARDVL_NEW_CMDR - 1);
		}
		else
		{
			ARDVL_CMDR_SET = gst[ARDVL_NEW_CMDR - 1].CZ2B_RS;
			ARDVL_CMDR_SET += 0x0010 >> (ARDVL_NEW_CMDR - 1);
		}

		ARDVL_MF_FLAG = true;

		Assign_DEU_Processor();

		ARDVL_MF_FLAG = false;
		return;
	}

	void DPS_Reconfiguration::CMPTR_CRT_Key_Processing( void )
	{
		// TODO
		return;
	}

	void DPS_Reconfiguration::OPS_Initiate_Processing( void )
	{
		// TODO
		return;
	}

	void DPS_Reconfiguration::Fail_To_Sync_Processing( void )
	{
		// TODO
		return;
	}

	void DPS_Reconfiguration::Force_OPS_0_Processing( void )
	{
		// TODO
		return;
	}

	void DPS_Reconfiguration::Major_Function_Hierarchy( void )
	{
		if (ARDVL_RUN != 0)
		{
			ARDVL_NEW_CMDR = ARDVL_RUN;
		}
		else
		{
			if (ARDVL_STBY != 0)
			{
				ARDVL_NEW_CMDR = ARDVL_STBY;
			}
			else
			{
				if (ARDVL_ZERO != 0)
				{
					ARDVL_NEW_CMDR = ARDVL_ZERO;
				}
				else
				{
					for (unsigned short GPC = 1; GPC <= 5; GPC++)
					{
						SCP_GST gst;
						ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, GPC, &gst, sizes_GST, pos_GST, cnt_GST, 5 );
						if (gst.CZ2B_ACT_XMITR1 & (0x0040 << (4 - ARDVL_CRT)))
						{
							ARDVL_NEW_CMDR = ARDVL_CURR_CMDR;
							break;
						}
					}
				}
			}
		}
		return;
	}

	void DPS_Reconfiguration::Assign_DEU_Processor( void )
	{
		ARDVL_BUS = ARDVL_CRT + 5;

		ARDVL_CURR_CMDR = 0;

		for (unsigned short GPC = 1; GPC <= 5; GPC++)
		{
			SCP_GST gst;
			ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, GPC, &gst, sizes_GST, pos_GST, cnt_GST, 5 );
			if (gst.CZ2B_ACT_XMITR1 & (0x8000 >> ARDVL_BUS))
			{
				ARDVL_CURR_CMDR = GPC;
				break;
			}
		}

		Bus_Handover_Cooperation();

		if (STAT)
		{
			unsigned short GPC_ID = ReadCOMPOOL_IS( SCP_TFCMID );

			if (ARDVL_MF_FLAG)
			{
				if (0)
				{
					if ((GPC_ID & ARDVL_CMDR_SET) == 0)// TODO bit vs num
					{
						//[2] = 1;// MF not supported
					}
					else
					{
						//[2] = 0;// MF supported
					}

					WriteCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY, ReadCOMPOOL_IS( SCP_CZ1B_D_DIT_MSG_READY ) | (0x1000 >> (ARDVL_CRT - 1)) );
					WriteCOMPOOL_IS( SCP_CZ1E_D_MCDS_EVENT, 1 );
				}
			}

			if (ARDVL_NEW_CMDR == GPC_ID)
			{
				//BUS_PARAMS_TYPE_IND = ASGN_BUS;
			}
			else
			{
				if (GPC_ID & ARDVL_CMDR_SET)// TODO bit vs num
				{
					if (GPC_ID == ARDVL_CURR_CMDR)
					{
						//BUS_PARAMS_TYPE_IND = REL_BUS;
					}
					else
					{
						//BUS_PARAMS_TYPE_IND = LSTN_BUS;
					}
				}
				else
				{
					//BUS_PARAMS_TYPE_IND = DIS_BUS;
					//SET SVC DEU_Shared_Event
				}
			}

			//BUS_PARAMS_VAR_DATA1 = Bus_Number;
			// issue RECONFIG SVC
		}
		else
		{
			// TODO error mesage
		}
		return;
	}

	void DPS_Reconfiguration::Bus_Handover_Cooperation( void )
	{
		STAT = false;

		unsigned short GPC_ID = ReadCOMPOOL_IS( SCP_TFCMID );
		unsigned short CZ2B_FAIL_SYNC_SET = ReadCOMPOOL_IS( SCP_CZ2B_FAIL_SYNC_SET );
		SCP_GST gst;
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_GST, GPC_ID, &gst, sizes_GST, pos_GST, cnt_GST, 5 );
		if ((gst.CZ2B_CS == 0) && (GPC_ID & CZ2B_FAIL_SYNC_SET))
		{
			if ((ARDVL_CURR_CMDR != GPC_ID) && (ARDVL_NEW_CMDR != GPC_ID))
			{
				STAT = true;
			}
		}
		else
		{
			if ((ARDVL_NEW_CMDR == 0) || (ARDVL_NEW_CMDR == GPC_ID) || (ARDVL_NEW_CMDR & gst.CZ2B_CS))// TODO bitmap vs num: ARDVL_NEW_CMDR & gst.CZ2B_CS
			{
				if ((ARDVL_CURR_CMDR != 0) && (ARDVL_CURR_CMDR != GPC_ID))
				{
					if ((ARDVL_CURR_CMDR & gst.CZ2B_CS) == 0)
					{
						if (6)// 6) Current_Bus_Commander Sync codes == 000
						{
							STAT = true;

							if (ARDVL_BUS != 0)// 7
							{
								//[Current_Bus_Commander]IOP_Transmitter_State[ARDVL_BUS] = 1
							}
						}
					}
					else
					{
						STAT = true;
					}
				}
				else
				{
					STAT = true;
				}
			}
		}
		return;
	}
}
