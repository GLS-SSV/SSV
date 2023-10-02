/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/07/11   GLS
2021/06/13   GLS
2021/08/24   GLS
2022/01/28   GLS
2022/05/24   GLS
2022/07/01   GLS
2022/08/05   GLS
2022/10/25   GLS
2022/10/29   GLS
2022/11/15   GLS
2022/11/16   GLS
2022/12/27   GLS
2023/01/11   GLS
2023/05/14   GLS
2023/10/02   GLS
********************************************/
#include "SimpleMDM_FA1.h"


namespace dps
{
	SimpleMDM_FA1::SimpleMDM_FA1( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):SimpleMDM( _director, "SimpleMDM_FA1", pBusManager ),
		powered(true)
	{
		BusConnect( BUS_FC1 );
		BusConnect( BUS_FC5 );
		return;
	}

	SimpleMDM_FA1::~SimpleMDM_FA1()
	{
	}

	void SimpleMDM_FA1::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 4 );
		Power2.Connect( pBundle, 4 );

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_1", 16 );
		dipIOM11[0][13].Connect( pBundle, 13 );// LH_VENTS_8_AND_9_CLOSE_1
		dipIOM11[0][14].Connect( pBundle, 14 );// LH_VENTS_8_AND_9_OPEN_1
		dipIOM11[0][15].Connect( pBundle, 15 );// LH_VENTS_8_AND_9_PURGE_IND_1

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1A", 16 );
		dopIOM7[0][5].Connect( pBundle, 13 );// LH_VENTS_8_9_MOTOR_1_OPEN_A
		dopIOM7[0][4].Connect( pBundle, 14 );// LH_VENTS_8_9_MOTOR_1_CLOSE_A
		dopIOM7[0][6].Connect( pBundle, 15 );// LH_VENTS_8_9_MOTOR_1_PURGE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_1B", 16 );
		dopIOM15[0][4].Connect( pBundle, 13 );// LH_VENTS_8_9_MOTOR_1_OPEN_B
		dopIOM15[0][3].Connect( pBundle, 14 );// LH_VENTS_8_9_MOTOR_1_CLOSE_B
		dopIOM15[0][5].Connect( pBundle, 15 );// LH_VENTS_8_9_MOTOR_1_PURGE_B

		pBundle = BundleManager()->CreateBundle( "ET_LOX_SENSORS", 16 );
		dipIOM11[0][8].Connect( pBundle, 3 );
		dipIOM6[28].Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "ET_LH2_SENSORS", 16 );
		dipIOM3[0][9].Connect( pBundle, 3 );
		dipIOM6[27].Connect( pBundle, 12 );

		pBundle = BundleManager()->CreateBundle( "MPS_SENSORS", 2 );
		dipIOM14[22].Connect( pBundle, 1 );

		pBundle = BundleManager()->CreateBundle( "OMS_TVC_L", 16 );
		dopIOM4_HI[7].Connect( pBundle, 4 );// OMS TVC: L PRI P ACTR CMD ("ACTIVE")
		dopIOM4_HI[8].Connect( pBundle, 5 );// OMS TVC: L PRI Y ACTR CMD ("ACTIVE")
		dipIOM14[14].Connect( pBundle, 8 );// OMS - L ENG ACTV P ACTR POSN IN
		dipIOM14[15].Connect( pBundle, 9 );// OMS - L ENG ACTV Y ACTR POSN IN

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_A_LRCS", 14 );
		dopIOM2[0][0].Connect( pBundle, 1 );// RJDA 1B L RCS JET L1A CMD A
		dopIOM2[0][1].Connect( pBundle, 5 );// RJDA 1B L RCS JET L1L CMD A
		dopIOM2[0][2].Connect( pBundle, 8 );// RJDA 1B L RCS JET L1U CMD A
		dopIOM2[0][6].Connect( pBundle, 13 );// RJDA 1B VERN JET L5D CMD A
		dopIOM2[0][7].Connect( pBundle, 12 );// RJDA 1B VERN JET L5L CMD A

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_A_RRCS", 14 );
		dopIOM2[0][3].Connect( pBundle, 1 );// RJDA 1B R RCS JET R1A CMD A
		dopIOM2[0][4].Connect( pBundle, 5 );// RJDA 1B R RCS JET R1R CMD A
		dopIOM2[0][5].Connect( pBundle, 8 );// RJDA 1B R RCS JET R1U CMD A

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_B_LRCS", 14 );
		dopIOM10[0][0].Connect( pBundle, 1 );// RJDA 1B L RCS JET L1A CMD B
		dopIOM10[0][1].Connect( pBundle, 5 );// RJDA 1B L RCS JET L1L CMD B
		dopIOM10[0][2].Connect( pBundle, 8 );// RJDA 1B L RCS JET L1U CMD B
		dopIOM10[0][6].Connect( pBundle, 13 );// RJDA 1B VERN JET L5D CMD B
		dopIOM10[0][7].Connect( pBundle, 12 );// RJDA 1B VERN JET L5L CMD B

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_B_RRCS", 14 );
		dopIOM10[0][3].Connect( pBundle, 1 );// RJDA 1B R RCS JET R1A CMD B
		dopIOM10[0][4].Connect( pBundle, 5 );// RJDA 1B R RCS JET R1R CMD B
		dopIOM10[0][5].Connect( pBundle, 8 );// RJDA 1B R RCS JET R1U CMD B

		pBundle = BundleManager()->CreateBundle( "RCS_PC_EVT_LRCS", 14 );
		dipIOM5[0][0].Connect( pBundle, 1 );// RJDA 1 JET L1A CHMBR PRESS IND
		dipIOM5[0][1].Connect( pBundle, 5 );// RJDA 1 JET L1L CHMBR PRESS IND
		dipIOM5[0][2].Connect( pBundle, 8 );// RJDA 1 JET L1U CHMBR PRESS IND
		dipIOM5[0][6].Connect( pBundle, 13 );// RJDA 1 JET L5D CHMBR PRESS IND
		dipIOM5[0][7].Connect( pBundle, 12 );// RJDA 1 JET L5L CHMBR PRESS IND

		pBundle = BundleManager()->CreateBundle( "RCS_PC_EVT_RRCS", 14 );
		dipIOM5[0][3].Connect( pBundle, 1 );// RJDA 1 JET R1A CHMBR PRESS IND
		dipIOM5[0][4].Connect( pBundle, 5 );// RJDA 1 JET R1R CHMBR PRESS IND
		dipIOM5[0][5].Connect( pBundle, 8 );// RJDA 1 JET R1U CHMBR PRESS IND

		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_LRCS", 14 );
		dipIOM8[0][0].Connect( pBundle, 1 );// RJDA 1 JET L1A DRIVER
		dipIOM8[0][1].Connect( pBundle, 5 );// RJDA 1 JET L1L DRIVER
		dipIOM8[0][2].Connect( pBundle, 8 );// RJDA 1 JET L1U DRIVER
		dipIOM8[0][6].Connect( pBundle, 13 );// RJDA 1 JET L5D DRIVER
		dipIOM8[0][7].Connect( pBundle, 12 );// RJDA 1 JET L5L DRIVER

		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_RRCS", 14 );
		dipIOM8[0][3].Connect( pBundle, 1 );// RJDA 1 JET R1A DRIVER
		dipIOM8[0][4].Connect( pBundle, 5 );// RJDA 1 JET R1R DRIVER
		dipIOM8[0][5].Connect( pBundle, 8 );// RJDA 1 JET R1U DRIVER
		
		pBundle = BundleManager()->CreateBundle( "LRCS_HE_ISOL", 16 );
		dipIOM11[2][10].Connect( pBundle, 2 );// L_HE_FU_PRESS_V_A_OP
		dipIOM11[2][11].Connect( pBundle, 3 );// L_HE_FU_PRESS_V_A_CL
		dipIOM11[2][8].Connect( pBundle, 6 );// L_HE_OX_PRESS_V_A_OP
		dipIOM11[2][9].Connect( pBundle, 7 );// L_HE_OX_PRESS_V_A_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_TANK_ISOL_12", 10 );
		dipIOM11[2][6].Connect( pBundle, 2 );// L_FU_TK_ISO_V_12_OP
		dipIOM11[2][7].Connect( pBundle, 3 );// L_FU_TK_ISO_V_12_CL
		dipIOM11[2][4].Connect( pBundle, 6 );// L_OX_TK_ISO_V_12_OP
		dipIOM11[2][5].Connect( pBundle, 7 );// L_OX_TK_ISO_V_12_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_12_ISOL", 12 );
		dipIOM11[2][0].Connect( pBundle, 2 );// L_FU_MANF_ISOV_1_OP
		dipIOM11[2][1].Connect( pBundle, 3 );// L_FU_MANF_ISOV_1_CL
		dipIOM11[2][2].Connect( pBundle, 4 );// L_OX_MANF_ISOV_1_OP
		dipIOM11[2][3].Connect( pBundle, 5 );// L_OX_MANF_ISOV_1_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_5_ISOL", 8 );
		dipIOM11[2][13].Connect( pBundle, 4 );// L_FU_MANF_ISOV_5_OP
		dipIOM11[2][15].Connect( pBundle, 5 );// L_FU_MANF_ISOV_5_CL
		dipIOM11[2][12].Connect( pBundle, 6 );// L_OX_MANF_ISOV_5_OP
		dipIOM11[2][14].Connect( pBundle, 7 );// L_OX_MANF_ISOV_5_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_HE_ISOL", 16 );
		dipIOM3[2][10].Connect( pBundle, 2 );// R_HE_FU_PRESS_V_A_OP
		dipIOM3[2][11].Connect( pBundle, 3 );// R_HE_FU_PRESS_V_A_CL
		dipIOM3[2][8].Connect( pBundle, 6 );// R_HE_OX_PRESS_V_A_OP
		dipIOM3[2][9].Connect( pBundle, 7 );// R_HE_OX_PRESS_V_A_CL
		
		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_12_ISOL", 12 );
		dipIOM3[2][0].Connect( pBundle, 2 );// R_FU_MANF_ISOV_1_OP
		dipIOM3[2][1].Connect( pBundle, 3 );// R_FU_MANF_ISOV_1_CL
		dipIOM3[2][2].Connect( pBundle, 4 );// R_OX_MANF_ISOV_1_OP
		dipIOM3[2][3].Connect( pBundle, 5 );// R_OX_MANF_ISOV_1_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_XFD_345", 10 );
		dipIOM3[2][6].Connect( pBundle, 2 );// R_RCS_FU_XFD_345_OP
		dipIOM3[2][7].Connect( pBundle, 3 );// R_RCS_FU_XFD_345_CL
		dipIOM3[2][4].Connect( pBundle, 6 );// R_RCS_OX_XFD_345_OP
		dipIOM3[2][5].Connect( pBundle, 7 );// R_RCS_OX_XFD_345_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_TANK_ISOL_A", 10 );
		dipIOM3[1][2].Connect( pBundle, 2 );// L_OMS_FU_TK_ISOV_A_OP
		dipIOM3[1][3].Connect( pBundle, 3 );// L_OMS_FU_TK_ISOV_A_CL
		dipIOM11[1][2].Connect( pBundle, 6 );// L_OMS_OX_TK_ISOV_A_OP
		dipIOM11[1][3].Connect( pBundle, 7 );// L_OMS_OX_TK_ISOV_A_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_XFD_A", 10 );
		dipIOM11[1][8].Connect( pBundle, 2 );// L_OMS_FU_XFD_V_A_OP
		dipIOM11[1][9].Connect( pBundle, 3 );// L_OMS_FU_XFD_V_A_CL
		dipIOM11[1][6].Connect( pBundle, 6 );// L_OMS_OX_XFD_V_A_OP
		dipIOM11[1][7].Connect( pBundle, 7 );// L_OMS_OX_XFD_V_A_CL

		pBundle = BundleManager()->CreateBundle( "ROMS_XFD_A", 10 );
		dipIOM3[1][10].Connect( pBundle, 2 );// R_OMS_FU_XFD_V_A_OP
		dipIOM3[1][11].Connect( pBundle, 3 );// R_OMS_FU_XFD_V_A_CL
		dipIOM3[1][8].Connect( pBundle, 6 );// R_OMS_OX_XFD_V_A_OP
		dipIOM3[1][9].Connect( pBundle, 7 );// R_OMS_OX_XFD_V_A_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_HEISOL_TANKISOL_12_VLV_CMD", 10 );
		dopIOM7[2][9].Connect( pBundle, 0 );// L_HE_PRESS_V_A_OP_A
		dopIOM7[2][10].Connect( pBundle, 1 );// L_HE_PRESS_V_A_CL_A
		dopIOM7[2][3].Connect( pBundle, 4 );// L_FU_TK_ISOV_12_OP_B
		dopIOM7[2][2].Connect( pBundle, 5 );// L_FU_TK_ISOV_12_CL_B
		dopIOM7[2][5].Connect( pBundle, 6 );// L_OX_TK_ISOV_12_OP_B
		dopIOM7[2][4].Connect( pBundle, 7 );// L_OX_TK_ISOV_12_CL_B

		pBundle = BundleManager()->CreateBundle( "LRCS_MANIFISOL_1234_VLV_CMD", 12 );
		dopIOM7[2][6].Connect( pBundle, 0 );// L_MANF_ISOV_NO_1_OP
		dopIOM7[0][0].Connect( pBundle, 7 );// L_MANF_ISOV_NO_3_CL_A
		dopIOM15[2][8].Connect( pBundle, 8 );// L_MANF_ISOV_NO_3_CL_B

		pBundle = BundleManager()->CreateBundle( "LRCS_MANIFISOL_5_VLV_CMD", 6 );
		dopIOM7[2][11].Connect( pBundle, 0 );// L_MANF_ISO_5_OPEN_A

		pBundle = BundleManager()->CreateBundle( "RRCS_HEISOL_TANKISOL_12_VLV_CMD", 10 );
		dopIOM15[2][9].Connect( pBundle, 0 );// R_HE_PRESS_V_A_OP_A
		dopIOM15[2][10].Connect( pBundle, 1 );// R_HE_PRESS_V_A_CL_A
		dopIOM15[2][5].Connect( pBundle, 8 );// R_TK_ISOV_12_OP_A
		dopIOM15[2][4].Connect( pBundle, 9 );// R_TK_ISOV_12_CL_A

		pBundle = BundleManager()->CreateBundle( "RRCS_MANIFISOL_1234_VLV_CMD", 12 );
		dopIOM15[2][6].Connect( pBundle, 0 );// R_MANF_ISOV_NO_1_OP
		dopIOM15[0][1].Connect( pBundle, 7 );// R_MANF_ISOV_NO_3_CL_A
		dopIOM7[2][8].Connect( pBundle, 8 );// R_MANF_ISOV_NO_3_CL_B

		pBundle = BundleManager()->CreateBundle( "RRCS_MANIFISOL_5_VLV_CMD", 6 );
		dopIOM15[2][11].Connect( pBundle, 1 );// R_MANF_ISO_5_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "LRCS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[2][1].Connect( pBundle, 10 );// L_RCS_XFD_345_OP
		dopIOM7[2][0].Connect( pBundle, 11 );// L_RCS_XFD_345_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_CROSSFEED_VLV_CMD", 12 );
		dopIOM15[2][3].Connect( pBundle, 6 );// R_RCS_FU_XFD_345_OP
		dopIOM15[2][2].Connect( pBundle, 7 );// R_RCS_FU_XFD_345_CL
		dopIOM15[2][1].Connect( pBundle, 8 );// R_RCS_OX_XFD_345_OP
		dopIOM15[2][0].Connect( pBundle, 9 );// R_RCS_OX_XFD_345_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_TANKISOL_VLV_CMD", 12 );
		dopIOM7[1][3].Connect( pBundle, 0 );// L_OMS_FU_TK_ISOV_A_OP
		dopIOM7[1][4].Connect( pBundle, 1 );// L_OMS_FU_TK_ISOV_A_CL
		dopIOM7[1][5].Connect( pBundle, 2 );// L_OMS_OX_TK_ISOV_A_OP
		dopIOM7[1][6].Connect( pBundle, 3 );// L_OMS_OX_TK_ISOV_A_CL
		dopIOM15[1][5].Connect( pBundle, 10 );// L_OMS_TK_V_B_OP
		dopIOM15[1][6].Connect( pBundle, 11 );// L_OMS_TK_V_B_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[1][7].Connect( pBundle, 0 );// L_OMS_FU_XFD_V_A_OP
		dopIOM7[1][8].Connect( pBundle, 1 );// L_OMS_FU_XFD_V_A_CL
		dopIOM7[1][11].Connect( pBundle, 2 );// L_OMS_OX_XFD_V_A_OP
		dopIOM7[1][12].Connect( pBundle, 3 );// L_OMS_OX_XFD_V_A_CL
		dopIOM15[1][11].Connect( pBundle, 10 );// L_OMS_XFD_B_OP
		dopIOM15[1][12].Connect( pBundle, 11 );// L_OMS_XFD_B_CL

		pBundle = BundleManager()->CreateBundle( "ROMS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[1][9].Connect( pBundle, 0 );// R_OMS_FU_XFD_V_A_OP
		dopIOM7[1][10].Connect( pBundle, 1 );// R_OMS_FU_XFD_V_A_CL
		dopIOM7[1][13].Connect( pBundle, 2 );// R_OMS_OX_XFD_V_A_OP
		dopIOM7[1][14].Connect( pBundle, 3 );// R_OMS_OX_XFD_V_A_CL
		dopIOM15[1][13].Connect( pBundle, 10 );// R_OMS_XFD_B_OP
		dopIOM15[1][14].Connect( pBundle, 11 );// R_OMS_XFD_B_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_HE_VAPOR_ISOL_A", 8 );
		dipIOM11[1][4].Connect( pBundle, 1 );// L OMS HE ISOV A POSN OP
		dipIOM3[1][4].Connect( pBundle, 5 );// L OMS VAP ISOV 1 OP

		pBundle = BundleManager()->CreateBundle( "LOMS_ENGINE", 16 );
		dopIOM12[1][4].Connect( pBundle, 12 );// L OMS ENG PGE V1 OP
		dipIOM3[1][5].Connect( pBundle, 13 );// L OMS ENG PGE V1 POSN OP
		
		pBundle = BundleManager()->CreateBundle( "LOMS_GPC_CMD", 8 );
		dopIOM15[1][2].Connect( pBundle, 0 );// L_OMS_HE_ISOV_A_OP
		dopIOM7[1][2].Connect( pBundle, 2 );// L_OMS_VAP_ISOV_1_OP
		dopIOM15[1][1].Connect( pBundle, 6 );// L_OMS_VLV_1_COIL_2_CMD

		pBundle = BundleManager()->CreateBundle( "ROMS_GPC_CMD", 8 );
		dopIOM7[1][1].Connect( pBundle, 6 );// R_OMS_VLV_1_COIL_2_CMD

		pBundle = BundleManager()->CreateBundle( "OMS_ENGINE_SWITCHES", 6 );
		dipIOM3[1][7].Connect( pBundle, 0 );// L ARM 2
		dipIOM3[1][6].Connect( pBundle, 1 );// L ARM/PRESS 2
		return;
	}

	void SimpleMDM_FA1::Rx( const BUS_ID id, void* data, const unsigned short datalen )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;

		unsigned int* rcvd = static_cast<unsigned int*>(data);

		//// process command word
		{
			// check address
			int dataaddr = (rcvd[0] >> 20) & 0b11111;
			if (FAx_ADDR != dataaddr) return;
		}

		// check parity
		if (CalcParity( rcvd[0] ) == 0) return;

		unsigned short wdcount = ((rcvd[0] >> 1) & 0b11111) + 1;// data words (rcvd = 0b00000 => 1 word)
		unsigned short modecontrol = (rcvd[0] >> 15) & 0b1111;
		unsigned short IOMaddr = (rcvd[0] >> 11) & 0b1111;
		unsigned short IOMch = (rcvd[0] >> 6) & 0b11111;
		unsigned short IOMdata = 0;

		switch (modecontrol)
		{
			case 0b1000:// direct mode output (GPC-to-MDM)
				{
					if (datalen != (wdcount + 1)) return;

					// check parity
					if (CalcParity( rcvd[1] ) == 0) return;

					// check address
					int dataaddr = (rcvd[1] >> 20) & 0b11111;
					if (FAx_ADDR != dataaddr) return;

					// check SEV
					unsigned short SEV = (rcvd[1] >> 1) & 0b111;
					if (SEV != 0b101) return;
				}
				IOMdata = (rcvd[1] >> 4) & 0xFFFF;
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AOD
						break;
					case 0b0001:// IOM 1 AID
						break;
					case 0b0010:// IOM 2 DOL
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM2 );
						break;
					case 0b0011:// IOM 3 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM3 );
						break;
					case 0b0100:// IOM 4 AOD
						IOM_AOD( 0b001, IOMch, IOMdata, dopIOM4_HI, dopIOM4_LO );
						break;
					case 0b0101:// IOM 5 DIL
						IOM_DIL( 0b001, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						IOM_AIS( 0b001, IOMch, IOMdata, dipIOM6 );
						break;
					case 0b0111:// IOM 7 DOH
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM7 );
						break;
					case 0b1000:// IOM 8 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM8 );
						break;
					case 0b1001:// IOM 9 AID
						break;
					case 0b1010:// IOM 10 DOL
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM10 );
						break;
					case 0b1011:// IOM 11 DIH
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM11 );
						break;
					case 0b1100:// IOM 12 DOH
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM12 );
						break;
					case 0b1101:// IOM 13 DIL
						IOM_DIL( 0b001, IOMch, IOMdata, dipIOM13 );
						break;
					case 0b1110:// IOM 14 AIS
						IOM_AIS( 0b001, IOMch, IOMdata, dipIOM14 );
						break;
					case 0b1111:// IOM 15 DOH
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM15 );
						break;
				}
				break;
			case 0b1001:// direct mode input (MDM-to-GPC)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AOD
						break;
					case 0b0001:// IOM 1 AID
						break;
					case 0b0010:// IOM 2 DOL
						IOM_DOL( 0b000, IOMch, IOMdata, dopIOM2 );
						break;
					case 0b0011:// IOM 3 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM3 );
						break;
					case 0b0100:// IOM 4 AOD
						IOM_AOD( 0b000, IOMch, IOMdata, dopIOM4_HI, dopIOM4_LO );
						break;
					case 0b0101:// IOM 5 DIL
						IOM_DIL( 0b000, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						IOM_AIS( 0b000, IOMch, IOMdata, dipIOM6 );
						break;
					case 0b0111:// IOM 7 DOH
						IOM_DOH( 0b000, IOMch, IOMdata, dopIOM7 );
						break;
					case 0b1000:// IOM 8 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM8 );
						break;
					case 0b1001:// IOM 9 AID
						break;
					case 0b1010:// IOM 10 DOL
						IOM_DOL( 0b000, IOMch, IOMdata, dopIOM10 );
						break;
					case 0b1011:// IOM 11 DIH
						IOM_DIH( 0b000, IOMch, IOMdata, dipIOM11 );
						break;
					case 0b1100:// IOM 12 DOH
						IOM_DOH( 0b000, IOMch, IOMdata, dopIOM12 );
						break;
					case 0b1101:// IOM 13 DIL
						IOM_DIL( 0b000, IOMch, IOMdata, dipIOM13 );
						break;
					case 0b1110:// IOM 14 AIS
						IOM_AIS( 0b000, IOMch, IOMdata, dipIOM14 );
						break;
					case 0b1111:// IOM 15 DOH
						IOM_DOH( 0b000, IOMch, IOMdata, dopIOM15 );
						break;
				}
				{
					unsigned int outdata = 0;

					outdata |= FAx_ADDR << 20;
					outdata |= IOMdata << 4;
					outdata |= 0b101 << 1;// SEV
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
				}
				break;
			case 0b1100:// return the command word
				{
					unsigned short returnword = (rcvd[0] >> 1) & 0b11111111111111;
					returnword = (returnword & 0b00111111111111) << 2;

					unsigned int outdata = 0;

					outdata |= FAx_ADDR << 20;
					outdata |= 0b1100 << 15;// mode control
					outdata |= returnword << 1;// word wrap pattern
					outdata |= (~CalcParity( outdata )) & 1;// parity

					Tx( id, &outdata, 1 );
				}
				break;
		}
		return;
	}

	void SimpleMDM_FA1::OnPreStep( double simt, double simdt, double mjd )
	{
		if (!Power1.IsSet() && !Power2.IsSet())
		{
			if (powered)
			{
				// power loss -> set outputs to 0
				for (int ch = 0; ch < 3; ch++)
				{
					for (int bt = 0; bt < 16; bt++)
					{
						dopIOM2[ch][bt].ResetLine();
						dopIOM7[ch][bt].ResetLine();
						dopIOM10[ch][bt].ResetLine();
						dopIOM12[ch][bt].ResetLine();
						dopIOM15[ch][bt].ResetLine();
					}
				}

				for (int ch = 0; ch < 16; ch++)
				{
					dopIOM4_HI[ch].ResetLine();
					dopIOM4_LO[ch].ResetLine();
				}
			}
			powered = false;
		}
		else
		{
			powered = true;
		}
		return;
	}
}
