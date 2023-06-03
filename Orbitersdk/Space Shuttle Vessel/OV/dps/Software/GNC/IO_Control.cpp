/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/29   GLS
2022/06/11   GLS
2022/08/05   GLS
2023/06/03   GLS
********************************************/
#include "IO_Control.h"
#include <cassert>


namespace dps
{
	IO_Control::IO_Control( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "IO_Control" )
	{
		CMD[LH2_INBD_BU_DV_OP] = false;
		CMD[LH2_OTBD_BU_DV_OP] = false;
		CMD[PNEU_L_HE_XOVR_OP] = false;
		CMD[PNEU_HE_ISOL_1_OP] = true;
		CMD[PNEU_HE_ISOL_2_OP] = true;
		CMD[HE_ISOL_A_CTR_OP] = true;
		CMD[HE_ISOL_A_LEFT_OP] = true;
		CMD[HE_ISOL_A_RIGHT_OP] = true;
		CMD[HE_ISOL_B_CTR_OP] = true;
		CMD[HE_ISOL_B_LEFT_OP] = true;
		CMD[HE_ISOL_B_RIGHT_OP] = true;
		CMD[HE_IC_CTR_IN_OP] = false;
		CMD[HE_IC_LEFT_IN_OP] = false;
		CMD[HE_IC_RIGHT_IN_OP] = false;
		CMD[HE_IC_CTR_OUT_OP] = false;
		CMD[HE_IC_LEFT_OUT_OP] = false;
		CMD[HE_IC_RIGHT_OUT_OP] = false;
		CMD[LOX_OVBD_BV] = false;
		CMD[ME1_LOX_PVLV_CL_A] = false;
		CMD[ME2_LOX_PVLV_CL_A] = false;
		CMD[ME3_LOX_PVLV_CL_A] = false;
		CMD[ME1_LOX_PVLV_CL_B] = false;
		CMD[ME2_LOX_PVLV_CL_B] = false;
		CMD[ME3_LOX_PVLV_CL_B] = false;
		CMD[ME1_LOX_PVLV_OP_A] = true;
		CMD[ME2_LOX_PVLV_OP_A] = true;
		CMD[ME3_LOX_PVLV_OP_A] = true;
		CMD[ME1_LOX_PVLV_OP_B] = true;
		CMD[ME2_LOX_PVLV_OP_B] = true;
		CMD[ME3_LOX_PVLV_OP_B] = true;
		CMD[ME1_LH2_PVLV_CL] = false;
		CMD[ME2_LH2_PVLV_CL] = false;
		CMD[ME3_LH2_PVLV_CL] = false;
		CMD[ME1_LH2_PVLV_OP] = false;
		CMD[ME2_LH2_PVLV_OP] = false;
		CMD[ME3_LH2_PVLV_OP] = false;
		CMD[LOX_POGO_RECIRC_1] = true;
		CMD[LOX_POGO_RECIRC_2] = true;
		CMD[LOX_OTBD_FD_VLV_CL] = false;
		CMD[LOX_OTBD_FD_VLV_OP] = false;
		CMD[LOX_INBD_FD_VLV_CL] = false;
		CMD[LOX_INBD_FD_VLV_OP] = false;
		CMD[LH2_OTBD_FD_VLV_CL] = false;
		CMD[LH2_OTBD_FD_VLV_OP] = false;
		CMD[LH2_INBD_FD_VLV_CL] = false;
		CMD[LH2_INBD_FD_VLV_OP] = false;
		CMD[LH2_TOPPING_VLV_OP] = false;
		CMD[LOX_REPRESS_1_OP] = false;
		CMD[LOX_REPRESS_2_OP] = false;
		CMD[LH2_REPRESS_1_OP] = false;
		CMD[LH2_REPRESS_2_OP] = false;
		CMD[LO2_FEEDLINE_RLF_ISOL_CL] = true;
		CMD[LH2_FEEDLINE_RLF_ISOL_CL] = true;
		CMD[GOX_FCV_1] = false;
		CMD[GOX_FCV_2] = false;
		CMD[GOX_FCV_3] = false;
		CMD[GH2_FCV_1] = false;
		CMD[GH2_FCV_2] = false;
		CMD[GH2_FCV_3] = false;
		return;
	}

	IO_Control::~IO_Control( void )
	{
		return;
	}

	void IO_Control::OnPreStep( double simt, double simdt, double mjd )
	{
		return;
	}

	void IO_Control::OnPostStep( double simt, double simdt, double mjd )
	{
		// BACKUPLH2VLV
		if (CMD[LH2_INBD_BU_DV_OP] == true) dspOUTPUT[LH2_INBD_BU_DV_OP].SetLine();
		else dspOUTPUT[LH2_INBD_BU_DV_OP].ResetLine();

		if (CMD[LH2_OTBD_BU_DV_OP] == true) dspOUTPUT[LH2_OTBD_BU_DV_OP].SetLine();
		else dspOUTPUT[LH2_OTBD_BU_DV_OP].ResetLine();

		// SW_PNEU_L_HE_XOVR
		if (dspINPUT_2[SW_PNEU_L_HE_XOVR].IsSet() == true)
		{
			dspOUTPUT[PNEU_L_HE_XOVR_OP].ResetLine();
		}
		else if (dspINPUT_1[SW_PNEU_L_HE_XOVR].IsSet() == true)
		{
			dspOUTPUT[PNEU_L_HE_XOVR_OP].SetLine();
		}
		else
		{
			if (CMD[PNEU_L_HE_XOVR_OP] == true) dspOUTPUT[PNEU_L_HE_XOVR_OP].SetLine();
			else dspOUTPUT[PNEU_L_HE_XOVR_OP].ResetLine();
		}

		// SW_PNEU_HE_ISOL
		if (dspINPUT_2[SW_PNEU_HE_ISOL].IsSet() == true)
		{
			dspOUTPUT[PNEU_HE_ISOL_1_OP].ResetLine();
			dspOUTPUT[PNEU_HE_ISOL_2_OP].ResetLine();
		}
		else if (dspINPUT_1[SW_PNEU_HE_ISOL].IsSet() == true)
		{
			dspOUTPUT[PNEU_HE_ISOL_1_OP].SetLine();
			dspOUTPUT[PNEU_HE_ISOL_2_OP].SetLine();
		}
		else
		{
			if (CMD[PNEU_HE_ISOL_1_OP] == true) dspOUTPUT[PNEU_HE_ISOL_1_OP].SetLine();
			else dspOUTPUT[PNEU_HE_ISOL_1_OP].ResetLine();

			if (CMD[PNEU_HE_ISOL_2_OP] == true) dspOUTPUT[PNEU_HE_ISOL_2_OP].SetLine();
			else dspOUTPUT[PNEU_HE_ISOL_2_OP].ResetLine();
		}

		for (int i = 0; i < 3; i++)
		{
			// SW_HE_ISOL_A_X
			if (dspINPUT_2[SW_HE_ISOL_A_CTR + i].IsSet() == true)
			{
				dspOUTPUT[HE_ISOL_A_CTR_OP + i].ResetLine();
			}
			else if (dspINPUT_1[SW_HE_ISOL_A_CTR + i].IsSet() == true)
			{
				dspOUTPUT[HE_ISOL_A_CTR_OP + i].SetLine();
			}
			else
			{
				if (CMD[HE_ISOL_A_CTR_OP + i] == true) dspOUTPUT[HE_ISOL_A_CTR_OP + i].SetLine();
				else dspOUTPUT[HE_ISOL_A_CTR_OP + i].ResetLine();
			}

			// SW_HE_ISOL_B_X
			if (dspINPUT_2[SW_HE_ISOL_B_CTR + i].IsSet() == true)
			{
				dspOUTPUT[HE_ISOL_B_CTR_OP + i].ResetLine();
			}
			else if (dspINPUT_1[SW_HE_ISOL_B_CTR + i].IsSet() == true)
			{
				dspOUTPUT[HE_ISOL_B_CTR_OP + i].SetLine();
			}
			else
			{
				if (CMD[HE_ISOL_B_CTR_OP + i] == true) dspOUTPUT[HE_ISOL_B_CTR_OP + i].SetLine();
				else dspOUTPUT[HE_ISOL_B_CTR_OP + i].ResetLine();
			}

			// SW_HE_IC_X
			if (dspINPUT_2[SW_HE_IC_CTR + i].IsSet() == true)
			{
				dspOUTPUT[HE_IC_CTR_IN_OP + i].ResetLine();
				dspOUTPUT[HE_IC_CTR_OUT_OP + i].SetLine();
			}
			else if (dspINPUT_1[SW_HE_IC_CTR + i].IsSet() == true)
			{
				dspOUTPUT[HE_IC_CTR_IN_OP + i].SetLine();
				dspOUTPUT[HE_IC_CTR_OUT_OP + i].ResetLine();
			}
			else
			{// HACK not sure if this is entirely correct (possible to open both at the same time?)
				if (CMD[HE_IC_CTR_IN_OP + i] == true) dspOUTPUT[HE_IC_CTR_IN_OP + i].SetLine();
				else dspOUTPUT[HE_IC_CTR_IN_OP + i].ResetLine();

				if (CMD[HE_IC_CTR_OUT_OP + i] == true) dspOUTPUT[HE_IC_CTR_OUT_OP + i].SetLine();
				else dspOUTPUT[HE_IC_CTR_OUT_OP + i].ResetLine();
			}

			// TODO add the switches and logic for the PVs below (still missing panel R4)
			// LOX_PVLV_CL_A
			if (CMD[ME1_LOX_PVLV_CL_A + i] == true) dspOUTPUT[ME1_LOX_PVLV_CL_A + i].SetLine();
			else dspOUTPUT[ME1_LOX_PVLV_CL_A + i].ResetLine();

			// LOX_PVLV_CL_B
			if (CMD[ME1_LOX_PVLV_CL_B + i] == true) dspOUTPUT[ME1_LOX_PVLV_CL_B + i].SetLine();
			else dspOUTPUT[ME1_LOX_PVLV_CL_B + i].ResetLine();

			// LOX_PVLV_OP_A
			if (CMD[ME1_LOX_PVLV_OP_A + i] == true) dspOUTPUT[ME1_LOX_PVLV_OP_A + i].SetLine();
			else dspOUTPUT[ME1_LOX_PVLV_OP_A + i].ResetLine();

			// LOX_PVLV_OP_B
			if (CMD[ME1_LOX_PVLV_OP_B + i] == true) dspOUTPUT[ME1_LOX_PVLV_OP_B + i].SetLine();
			else dspOUTPUT[ME1_LOX_PVLV_OP_B + i].ResetLine();

			// LH2_PVLV_CL
			if (CMD[ME1_LH2_PVLV_CL + i] == true) dspOUTPUT[ME1_LH2_PVLV_CL + i].SetLine();
			else dspOUTPUT[ME1_LH2_PVLV_CL + i].ResetLine();

			// LH2_PVLV_OP
			if (CMD[ME1_LH2_PVLV_OP + i] == true) dspOUTPUT[ME1_LH2_PVLV_OP + i].SetLine();
			else dspOUTPUT[ME1_LH2_PVLV_OP + i].ResetLine();
		}

		// LOX_OTBD_BV
		if (CMD[LOX_OVBD_BV] == true) dspOUTPUT[LOX_OVBD_BV].SetLine();
		else dspOUTPUT[LOX_OVBD_BV].ResetLine();

		// LOX_POGO_RECIRC_1
		if (CMD[LOX_POGO_RECIRC_1] == true) dspOUTPUT[LOX_POGO_RECIRC_1].SetLine();
		else dspOUTPUT[LOX_POGO_RECIRC_1].ResetLine();

		// LOX_POGO_RECIRC_2
		if (CMD[LOX_POGO_RECIRC_2] == true) dspOUTPUT[LOX_POGO_RECIRC_2].SetLine();
		else dspOUTPUT[LOX_POGO_RECIRC_2].ResetLine();

		// LOX_POGO_RECIRC_2
		if (CMD[LOX_POGO_RECIRC_2] == true) dspOUTPUT[LOX_POGO_RECIRC_2].SetLine();
		else dspOUTPUT[LOX_POGO_RECIRC_2].ResetLine();

		// TODO add the switches and logic for the F/Ds (and SOVs) below (still missing panel R4)
		// LOX_OTBD_FD_VLV_CL
		if (CMD[LOX_OTBD_FD_VLV_CL] == true) dspOUTPUT[LOX_OTBD_FD_VLV_CL].SetLine();
		else dspOUTPUT[LOX_OTBD_FD_VLV_CL].ResetLine();

		// LOX_OTBD_FD_VLV_OP
		if (CMD[LOX_OTBD_FD_VLV_OP] == true) dspOUTPUT[LOX_OTBD_FD_VLV_OP].SetLine();
		else dspOUTPUT[LOX_OTBD_FD_VLV_OP].ResetLine();

		// LOX_INBD_FD_VLV_CL
		if (CMD[LOX_INBD_FD_VLV_CL] == true) dspOUTPUT[LOX_INBD_FD_VLV_CL].SetLine();
		else dspOUTPUT[LOX_INBD_FD_VLV_CL].ResetLine();

		// LOX_INBD_FD_VLV_OP
		if (CMD[LOX_INBD_FD_VLV_OP] == true) dspOUTPUT[LOX_INBD_FD_VLV_OP].SetLine();
		else dspOUTPUT[LOX_INBD_FD_VLV_OP].ResetLine();

		// LH2_OTBD_FD_VLV_CL
		if (CMD[LH2_OTBD_FD_VLV_CL] == true) dspOUTPUT[LH2_OTBD_FD_VLV_CL].SetLine();
		else dspOUTPUT[LH2_OTBD_FD_VLV_CL].ResetLine();

		// LH2_OTBD_FD_VLV_OP
		if (CMD[LH2_OTBD_FD_VLV_OP] == true) dspOUTPUT[LH2_OTBD_FD_VLV_OP].SetLine();
		else dspOUTPUT[LH2_OTBD_FD_VLV_OP].ResetLine();

		// LH2_INBD_FD_VLV_CL
		if (CMD[LH2_INBD_FD_VLV_CL] == true) dspOUTPUT[LH2_INBD_FD_VLV_CL].SetLine();
		else dspOUTPUT[LH2_INBD_FD_VLV_CL].ResetLine();

		// LH2_INBD_FD_VLV_OP
		if (CMD[LH2_INBD_FD_VLV_OP] == true) dspOUTPUT[LH2_INBD_FD_VLV_OP].SetLine();
		else dspOUTPUT[LH2_INBD_FD_VLV_OP].ResetLine();

		// LH2_TOPPING_VLV_OP
		if (CMD[LH2_TOPPING_VLV_OP] == true) dspOUTPUT[LH2_TOPPING_VLV_OP].SetLine();
		else dspOUTPUT[LH2_TOPPING_VLV_OP].ResetLine();

		// LOX_REPRESS_1_OP
		if (CMD[LOX_REPRESS_1_OP] == true) dspOUTPUT[LOX_REPRESS_1_OP].SetLine();
		else dspOUTPUT[LOX_REPRESS_1_OP].ResetLine();

		// LOX_REPRESS_2_OP
		if (CMD[LOX_REPRESS_2_OP] == true) dspOUTPUT[LOX_REPRESS_2_OP].SetLine();
		else dspOUTPUT[LOX_REPRESS_2_OP].ResetLine();

		// LH2_REPRESS_1_OP
		if (CMD[LH2_REPRESS_1_OP] == true) dspOUTPUT[LH2_REPRESS_1_OP].SetLine();
		else dspOUTPUT[LH2_REPRESS_1_OP].ResetLine();

		// LH2_REPRESS_2_OP
		if (CMD[LH2_REPRESS_2_OP] == true) dspOUTPUT[LH2_REPRESS_2_OP].SetLine();
		else dspOUTPUT[LH2_REPRESS_2_OP].ResetLine();

		// LO2_FEEDLINE_RLF_ISOL_CL
		if (CMD[LO2_FEEDLINE_RLF_ISOL_CL] == true) dspOUTPUT[LO2_FEEDLINE_RLF_ISOL_CL].SetLine();
		else dspOUTPUT[LO2_FEEDLINE_RLF_ISOL_CL].ResetLine();

		// LH2_FEEDLINE_RLF_ISOL_CL
		if (CMD[LH2_FEEDLINE_RLF_ISOL_CL] == true) dspOUTPUT[LH2_FEEDLINE_RLF_ISOL_CL].SetLine();
		else dspOUTPUT[LH2_FEEDLINE_RLF_ISOL_CL].ResetLine();

		// GOX_FCV_1
		if (CMD[GOX_FCV_1] == true) dspOUTPUT[GOX_FCV_1].ResetLine();
		else dspOUTPUT[GOX_FCV_1].SetLine();

		// GOX_FCV_2
		if (CMD[GOX_FCV_2] == true) dspOUTPUT[GOX_FCV_2].ResetLine();
		else dspOUTPUT[GOX_FCV_2].SetLine();

		// GOX_FCV_3
		if (CMD[GOX_FCV_3] == true) dspOUTPUT[GOX_FCV_3].ResetLine();
		else dspOUTPUT[GOX_FCV_3].SetLine();

		// GH2 FCVs
		if (dspINPUT_1[SW_LH2ULLAGEPRESS].IsSet() == false)
		{
			// MAN (open)
			dspOUTPUT[GH2_FCV_1].ResetLine();
			dspOUTPUT[GH2_FCV_2].ResetLine();
			dspOUTPUT[GH2_FCV_3].ResetLine();
		}
		else
		{
			// AUTO
			if (CMD[GH2_FCV_1] == true) dspOUTPUT[GH2_FCV_1].ResetLine();
			else dspOUTPUT[GH2_FCV_1].SetLine();

			if (CMD[GH2_FCV_2] == true) dspOUTPUT[GH2_FCV_2].ResetLine();
			else dspOUTPUT[GH2_FCV_2].SetLine();

			if (CMD[GH2_FCV_3] == true) dspOUTPUT[GH2_FCV_3].ResetLine();
			else dspOUTPUT[GH2_FCV_3].SetLine();
		}
		return;
	}

	void IO_Control::Realize( void )
	{
		// for switch3 connect top position to dspINPUT_1, and bottom to dspINPUT_2
		// for switch2 connect only to dspINPUT_1
		/*
		B
		C

		A
		B
		C
		*/

		// INPUT
		DiscreteBundle *bundle = BundleManager()->CreateBundle( "MPSDUMP_LH2UP_R2_SWITCHES", 5 );
		dspINPUT_1[SW_LH2ULLAGEPRESS].Connect( bundle, 4 );// LH2UllagePress Auto

		bundle = BundleManager()->CreateBundle( "PNEU_R2_SWITCHES", 4 );
		dspINPUT_1[SW_PNEU_L_HE_XOVR].Connect( bundle, 1 );// LEngXOVR OPEN
		dspINPUT_2[SW_PNEU_L_HE_XOVR].Connect( bundle, 0 );// LEngXOVR CLOSE

		dspINPUT_1[SW_PNEU_HE_ISOL].Connect( bundle, 3 );// PneuISOL OPEN
		dspINPUT_2[SW_PNEU_HE_ISOL].Connect( bundle, 2 );// PneuISOL CLOSE


		bundle = BundleManager()->CreateBundle( "SSMEC_R2_SWITCHES", 8 );
		dspINPUT_1[SW_HE_ISOL_A_CTR].Connect( bundle, 3 );// HeISOL A CTR OP
		dspINPUT_2[SW_HE_ISOL_A_CTR].Connect( bundle, 2 );// HeISOL A CTR CL
		dspINPUT_1[SW_HE_ISOL_B_CTR].Connect( bundle, 5 );// HeISOL B CTR OP
		dspINPUT_2[SW_HE_ISOL_B_CTR].Connect( bundle, 4 );// HeISOL B CTR CL
		dspINPUT_1[SW_HE_IC_CTR].Connect( bundle, 7 );// IC CTR IN OPEN
		dspINPUT_2[SW_HE_IC_CTR].Connect( bundle, 6 );// IC CTR OUT OPEN

		bundle = BundleManager()->CreateBundle( "SSMEL_R2_SWITCHES", 8 );
		dspINPUT_1[SW_HE_ISOL_A_LEFT].Connect( bundle, 3 );// HeISOL A LEFT OP
		dspINPUT_2[SW_HE_ISOL_A_LEFT].Connect( bundle, 2 );// HeISOL A LEFT CL
		dspINPUT_1[SW_HE_ISOL_B_LEFT].Connect( bundle, 5 );// HeISOL B LEFT OP
		dspINPUT_2[SW_HE_ISOL_B_LEFT].Connect( bundle, 4 );// HeISOL B LEFT CL
		dspINPUT_1[SW_HE_IC_LEFT].Connect( bundle, 7 );// IC LEFT IN OPEN
		dspINPUT_2[SW_HE_IC_LEFT].Connect( bundle, 6 );// IC LEFT OUT OPEN

		bundle = BundleManager()->CreateBundle( "SSMER_R2_SWITCHES", 8 );
		dspINPUT_1[SW_HE_ISOL_A_RIGHT].Connect( bundle, 3 );// HeISOL A RIGHT OP
		dspINPUT_2[SW_HE_ISOL_A_RIGHT].Connect( bundle, 2 );// HeISOL A RIGHT CL
		dspINPUT_1[SW_HE_ISOL_B_RIGHT].Connect( bundle, 5 );// HeISOL B RIGHT OP
		dspINPUT_2[SW_HE_ISOL_B_RIGHT].Connect( bundle, 4 );// HeISOL B RIGHT CL
		dspINPUT_1[SW_HE_IC_RIGHT].Connect( bundle, 7 );// IC RIGHT IN OPEN
		dspINPUT_2[SW_HE_IC_RIGHT].Connect( bundle, 6 );// IC RIGHT OUT OPEN


		// OUTPUT
		bundle = BundleManager()->CreateBundle( "MPS_LV_A", 16 );// LV1 - LV16
		dspOUTPUT[HE_ISOL_A_CTR_OP].Connect( bundle, 0 );
		dspOUTPUT[HE_ISOL_B_CTR_OP].Connect( bundle, 1 );
		dspOUTPUT[HE_ISOL_A_LEFT_OP].Connect( bundle, 2 );
		dspOUTPUT[HE_ISOL_B_LEFT_OP].Connect( bundle, 3 );
		dspOUTPUT[HE_ISOL_A_RIGHT_OP].Connect( bundle, 4 );
		dspOUTPUT[HE_ISOL_B_RIGHT_OP].Connect( bundle, 5 );
		dspOUTPUT[PNEU_HE_ISOL_1_OP].Connect( bundle, 6 );
		dspOUTPUT[PNEU_HE_ISOL_2_OP].Connect( bundle, 7 );
		dspOUTPUT[PNEU_L_HE_XOVR_OP].Connect( bundle, 9 );
		dspOUTPUT[ME1_LOX_PVLV_OP_A].Connect( bundle, 11 );
		dspOUTPUT[ME1_LOX_PVLV_CL_A].Connect( bundle, 12 );
		dspOUTPUT[ME2_LOX_PVLV_OP_A].Connect( bundle, 13 );
		dspOUTPUT[ME2_LOX_PVLV_CL_A].Connect( bundle, 14 );
		dspOUTPUT[ME3_LOX_PVLV_OP_A].Connect( bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_B", 16 );// LV17 - LV32
		dspOUTPUT[ME3_LOX_PVLV_CL_A].Connect( bundle, 0 );
		dspOUTPUT[ME1_LH2_PVLV_OP].Connect( bundle, 1 );
		dspOUTPUT[ME1_LH2_PVLV_CL].Connect( bundle, 2 );
		dspOUTPUT[ME2_LH2_PVLV_OP].Connect( bundle, 3 );
		dspOUTPUT[ME2_LH2_PVLV_CL].Connect( bundle, 4 );
		dspOUTPUT[ME3_LH2_PVLV_OP].Connect( bundle, 5 );
		dspOUTPUT[ME3_LH2_PVLV_CL].Connect( bundle, 6 );
		dspOUTPUT[LO2_FEEDLINE_RLF_ISOL_CL].Connect( bundle, 7 );
		dspOUTPUT[LH2_FEEDLINE_RLF_ISOL_CL].Connect( bundle, 8 );
		dspOUTPUT[LOX_OTBD_FD_VLV_OP].Connect( bundle, 11 );
		dspOUTPUT[LOX_OTBD_FD_VLV_CL].Connect( bundle, 12 );
		dspOUTPUT[LOX_INBD_FD_VLV_OP].Connect( bundle, 13 );
		dspOUTPUT[LOX_INBD_FD_VLV_CL].Connect( bundle, 14 );
		dspOUTPUT[LH2_OTBD_FD_VLV_OP].Connect( bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_C", 16 );// LV33 - LV48
		dspOUTPUT[LH2_OTBD_FD_VLV_CL].Connect( bundle, 0 );
		dspOUTPUT[LH2_INBD_FD_VLV_OP].Connect( bundle, 1 );
		dspOUTPUT[LH2_INBD_FD_VLV_CL].Connect( bundle, 2 );
		dspOUTPUT[LH2_TOPPING_VLV_OP].Connect( bundle, 6 );
		dspOUTPUT[LOX_REPRESS_1_OP].Connect( bundle, 7 );
		dspOUTPUT[LOX_REPRESS_2_OP].Connect( bundle, 8 );
		dspOUTPUT[LH2_REPRESS_1_OP].Connect( bundle, 9 );
		dspOUTPUT[LH2_REPRESS_2_OP].Connect( bundle, 10 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_D", 16 );// LV49 - LV64
		dspOUTPUT[GOX_FCV_1].Connect( bundle, 4 );
		dspOUTPUT[GOX_FCV_2].Connect( bundle, 5 );
		dspOUTPUT[GOX_FCV_3].Connect( bundle, 6 );
		dspOUTPUT[GH2_FCV_1].Connect( bundle, 7 );
		dspOUTPUT[GH2_FCV_2].Connect( bundle, 8 );
		dspOUTPUT[GH2_FCV_3].Connect( bundle, 9 );
		dspOUTPUT[HE_IC_CTR_IN_OP].Connect( bundle, 10 );
		dspOUTPUT[HE_IC_CTR_OUT_OP].Connect( bundle, 11 );
		dspOUTPUT[HE_IC_LEFT_IN_OP].Connect( bundle, 12 );
		dspOUTPUT[HE_IC_LEFT_OUT_OP].Connect( bundle, 13 );
		dspOUTPUT[HE_IC_RIGHT_IN_OP].Connect( bundle, 14 );
		dspOUTPUT[HE_IC_RIGHT_OUT_OP].Connect( bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_E", 16 );// LV65 - LV80
		dspOUTPUT[LH2_INBD_BU_DV_OP].Connect( bundle, 7 );
		dspOUTPUT[LH2_OTBD_BU_DV_OP].Connect( bundle, 8 );
		dspOUTPUT[LOX_OVBD_BV].Connect( bundle, 11 );
		dspOUTPUT[ME1_LOX_PVLV_CL_B].Connect( bundle, 15 );

		bundle = BundleManager()->CreateBundle( "MPS_LV_F", 16 );// LV81 - LV85
		dspOUTPUT[ME2_LOX_PVLV_CL_B].Connect( bundle, 0 );
		dspOUTPUT[ME3_LOX_PVLV_CL_B].Connect( bundle, 1 );
		dspOUTPUT[ME1_LOX_PVLV_OP_B].Connect( bundle, 2 );
		dspOUTPUT[ME2_LOX_PVLV_OP_B].Connect( bundle, 3 );
		dspOUTPUT[ME3_LOX_PVLV_OP_B].Connect( bundle, 4 );

		return;
	}

	bool IO_Control::OnMajorModeChange( unsigned int newMajorMode )
	{
		return true;
	}

	int IO_Control::GetSWPos( int sw ) const
	{
		assert( (sw >= 0) && (sw < COUNT_INPUT) && "IO_Control::GetSWPos.sw" );
		if (dspINPUT_2[sw].IsSet() == true) return 0;
		else if (dspINPUT_1[sw].IsSet() == true) return 2;
		else return 1;
	}

	void IO_Control::SetCommand( int output, bool cmd )
	{
		assert( (output >= 0) && (output < COUNT_OUTPUT) && "IO_Control::SetCommand.output" );
		CMD[output] = cmd;
		return;
	}
}