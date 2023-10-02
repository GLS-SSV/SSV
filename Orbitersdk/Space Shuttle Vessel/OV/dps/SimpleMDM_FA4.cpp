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
#include "SimpleMDM_FA4.h"


namespace dps
{
	SimpleMDM_FA4::SimpleMDM_FA4( AtlantisSubsystemDirector* _director, BusManager* pBusManager ):SimpleMDM( _director, "SimpleMDM_FA4", pBusManager ),
		powered(true)
	{
		BusConnect( BUS_FC4 );
		BusConnect( BUS_FC8 );
		return;
	}

	SimpleMDM_FA4::~SimpleMDM_FA4()
	{
	}

	void SimpleMDM_FA4::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 7 );
		Power2.Connect( pBundle, 7 );

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_LH_2", 16 );
		dipIOM11[0][13].Connect( pBundle, 13 );// LH_VENTS_8_AND_9_CLOSE_2
		dipIOM11[0][14].Connect( pBundle, 14 );// LH_VENTS_8_AND_9_OPEN_2
		dipIOM11[0][15].Connect( pBundle, 15 );// LH_VENTS_8_AND_9_PURGE_IND_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2A", 16 );
		dopIOM7[0][5].Connect( pBundle, 13 );// LH_VENTS_8_9_MOTOR_2_OPEN_A
		dopIOM7[0][4].Connect( pBundle, 14 );// LH_VENTS_8_9_MOTOR_2_CLOSE_A
		dopIOM7[0][6].Connect( pBundle, 15 );// LH_VENTS_8_9_MOTOR_2_PURGE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_LH_2B", 16 );
		dopIOM15[0][4].Connect( pBundle, 13 );// LH_VENTS_8_9_MOTOR_2_OPEN_B
		dopIOM15[0][3].Connect( pBundle, 14 );// LH_VENTS_8_9_MOTOR_2_CLOSE_B
		dopIOM15[0][5].Connect( pBundle, 15 );// LH_VENTS_8_9_MOTOR_2_PURGE_B

		pBundle = BundleManager()->CreateBundle( "ET_LOX_SENSORS", 16 );
		dipIOM11[0][8].Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "ET_LH2_SENSORS", 16 );
		dipIOM3[0][9].Connect( pBundle, 2 );

		pBundle = BundleManager()->CreateBundle( "OMS_TVC_R", 16 );
		dopIOM4_HI[7].Connect( pBundle, 4 );// OMS TVC: R PRI P ACTR CMD ("ACTIVE")
		dopIOM4_HI[8].Connect( pBundle, 5 );// OMS TVC: R PRI Y ACTR CMD ("ACTIVE")
		dipIOM14[14].Connect( pBundle, 8 );// OMS - R ENG ACTV P ACTR POSN IN
		dipIOM14[15].Connect( pBundle, 9 );// OMS - R ENG ACTV Y ACTR POSN IN

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_A_LRCS", 14 );
		dopIOM2[0][0].Connect( pBundle, 2 );// RJDA 2A L RCS JET L4L CMD A
		dopIOM2[0][1].Connect( pBundle, 6 );// RJDA 2A L RCS JET L4U CMD A
		dopIOM2[0][2].Connect( pBundle, 9 );// RJDA 2A L RCS JET L4D CMD A

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_A_RRCS", 14 );
		dopIOM2[0][3].Connect( pBundle, 2 );// RJDA 2A R RCS JET R4R CMD A
		dopIOM2[0][4].Connect( pBundle, 6 );// RJDA 2A R RCS JET R4U CMD A
		dopIOM2[0][5].Connect( pBundle, 9 );// RJDA 2A R RCS JET R4D CMD A

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_B_LRCS", 14 );
		dopIOM10[0][0].Connect( pBundle, 2 );// RJDA 2A L RCS JET L4L CMD B
		dopIOM10[0][1].Connect( pBundle, 6 );// RJDA 2A L RCS JET L4U CMD B
		dopIOM10[0][2].Connect( pBundle, 9 );// RJDA 2A L RCS JET L4D CMD B

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_B_RRCS", 14 );
		dopIOM10[0][3].Connect( pBundle, 2 );// RJDA 2A R RCS JET R4R CMD B
		dopIOM10[0][4].Connect( pBundle, 6 );// RJDA 2A R RCS JET R4U CMD B
		dopIOM10[0][5].Connect( pBundle, 9 );// RJDA 2A R RCS JET R4D CMD B

		pBundle = BundleManager()->CreateBundle( "RCS_PC_EVT_LRCS", 14 );
		dipIOM5[0][0].Connect( pBundle, 2 );// RJDA 2 JET L4L CHMBR PRESS IND
		dipIOM5[0][1].Connect( pBundle, 6 );// RJDA 2 JET L4U CHMBR PRESS IND
		dipIOM5[0][2].Connect( pBundle, 9 );// RJDA 2 JET L4D CHMBR PRESS IND

		pBundle = BundleManager()->CreateBundle( "RCS_PC_EVT_RRCS", 14 );
		dipIOM5[0][3].Connect( pBundle, 2 );// RJDA 2 JET R4R CHMBR PRESS IND
		dipIOM5[0][4].Connect( pBundle, 6 );// RJDA 2 JET R4U CHMBR PRESS IND
		dipIOM5[0][5].Connect( pBundle, 9 );// RJDA 2 JET R4D CHMBR PRESS IND

		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_LRCS", 14 );
		dipIOM8[0][0].Connect( pBundle, 2 );// RJDA 2 JET L4L DRIVER
		dipIOM8[0][1].Connect( pBundle, 6 );// RJDA 2 JET L4U DRIVER
		dipIOM8[0][2].Connect( pBundle, 9 );// RJDA 2 JET L4D DRIVER

		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_RRCS", 14 );
		dipIOM8[0][3].Connect( pBundle, 2 );// RJDA 2 JET R4R DRIVER
		dipIOM8[0][4].Connect( pBundle, 6 );// RJDA 2 JET R4U DRIVER
		dipIOM8[0][5].Connect( pBundle, 9 );// RJDA 2 JET R4D DRIVER

		pBundle = BundleManager()->CreateBundle( "LRCS_TANK_ISOL_345", 12 );
		dipIOM11[2][6].Connect( pBundle, 8 );// L_FU_TK_ISO_V_345_B_OP
		dipIOM11[2][7].Connect( pBundle, 9 );// L_FU_TK_ISO_V_345_B_CL
		dipIOM11[2][4].Connect( pBundle, 10 );// L_OX_TK_ISO_V_345_B_OP
		dipIOM11[2][5].Connect( pBundle, 11 );// L_OX_TK_ISO_V_345_B_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_34_ISOL", 12 );
		dipIOM11[2][0].Connect( pBundle, 8 );// L_FU_MANF_ISOV_4_OP
		dipIOM11[2][1].Connect( pBundle, 9 );// L_FU_MANF_ISOV_4_CL
		dipIOM11[2][2].Connect( pBundle, 10 );// L_OX_MANF_ISOV_4_OP
		dipIOM11[2][3].Connect( pBundle, 11 );// L_OX_MANF_ISOV_4_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_TANK_ISOL_345", 12 );
		dipIOM3[2][6].Connect( pBundle, 8 );// R_FU_TK_ISO_V_345_B_OP
		dipIOM3[2][7].Connect( pBundle, 9 );// R_FU_TK_ISO_V_345_B_CL
		dipIOM3[2][4].Connect( pBundle, 10 );// R_OX_TK_ISO_V_345_B_OP
		dipIOM3[2][5].Connect( pBundle, 11 );// R_OX_TK_ISO_V_345_B_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_34_ISOL", 12 );
		dipIOM3[2][0].Connect( pBundle, 8 );// R_FU_MANF_ISOV_4_OP
		dipIOM3[2][1].Connect( pBundle, 9 );// R_FU_MANF_ISOV_4_CL
		dipIOM3[2][2].Connect( pBundle, 10 );// R_OX_MANF_ISOV_4_OP
		dipIOM3[2][3].Connect( pBundle, 11 );// R_OX_MANF_ISOV_4_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_XFD_12", 10 );
		dipIOM11[2][10].Connect( pBundle, 2 );// R_RCS_FU_XFD_12_OP
		dipIOM11[2][11].Connect( pBundle, 3 );// R_RCS_FU_XFD_12_CL
		dipIOM11[2][8].Connect( pBundle, 6 );// R_RCS_OX_XFD_12_OP
		dipIOM11[2][9].Connect( pBundle, 7 );// R_RCS_OX_XFD_12_CL

		pBundle = BundleManager()->CreateBundle( "ROMS_TANK_ISOL_A", 10 );
		dipIOM3[1][2].Connect( pBundle, 2 );// R_OMS_FU_TK_ISOV_A_OP
		dipIOM3[1][3].Connect( pBundle, 3 );// R_OMS_FU_TK_ISOV_A_CL
		dipIOM11[1][2].Connect( pBundle, 6 );// R_OMS_OX_TK_ISOV_A_OP
		dipIOM11[1][3].Connect( pBundle, 7 );// R_OMS_OX_TK_ISOV_A_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_TANKISOL_345_VLV_CMD", 8 );
		dopIOM7[2][3].Connect( pBundle, 2 );// L_FU_TK_ISOV_345_B_OP
		dopIOM7[2][2].Connect( pBundle, 3 );// L_FU_TK_ISOV_345_B_CL
		dopIOM7[2][5].Connect( pBundle, 6 );// L_OX_TK_ISOV_345_B_OP
		dopIOM7[2][4].Connect( pBundle, 7 );// L_OX_TK_ISOV_345_B_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_MANIFISOL_1234_VLV_CMD", 12 );
		dopIOM7[0][0].Connect( pBundle, 4 );// L_MANF_ISOV_NO_2_CL_A
		dopIOM15[2][8].Connect( pBundle, 5 );// L_MANF_ISOV_NO_2_CL_B
		dopIOM7[2][6].Connect( pBundle, 9 );// L_MANF_ISOV_NO_4_OP

		pBundle = BundleManager()->CreateBundle( "LRCS_MANIFISOL_5_VLV_CMD", 6 );
		dopIOM7[2][9].Connect( pBundle, 4 );// L_MANF_ISO_5_OPEN_C
		dopIOM7[2][10].Connect( pBundle, 5 );// L_MANF_ISO_5_CLOSE_C

		pBundle = BundleManager()->CreateBundle( "RRCS_TANKISOL_345_VLV_CMD", 8 );
		dopIOM15[2][3].Connect( pBundle, 2 );// R_FU_TK_ISOV_345_B_OP
		dopIOM15[2][2].Connect( pBundle, 3 );// R_FU_TK_ISOV_345_B_CL
		dopIOM15[2][5].Connect( pBundle, 6 );// R_OX_TK_ISOV_345_B_OP
		dopIOM15[2][4].Connect( pBundle, 7 );// R_OX_TK_ISOV_345_B_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_MANIFISOL_1234_VLV_CMD", 12 );
		dopIOM15[0][1].Connect( pBundle, 4 );// R_MANF_ISOV_NO_2_CL_A
		dopIOM7[2][8].Connect( pBundle, 5 );// R_MANF_ISOV_NO_2_CL_B
		dopIOM15[2][6].Connect( pBundle, 9 );// R_MANF_ISOV_NO_4_OP

		pBundle = BundleManager()->CreateBundle( "RRCS_MANIFISOL_5_VLV_CMD", 6 );
		dopIOM7[2][11].Connect( pBundle, 4 );// R_MANF_ISO_5_OPEN_C
		dopIOM15[2][11].Connect( pBundle, 5 );// R_MANF_ISO_5_CLOSE_C

		pBundle = BundleManager()->CreateBundle( "LRCS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[2][1].Connect( pBundle, 4 );// L_RCS_XFD_12_OP
		dopIOM7[2][0].Connect( pBundle, 5 );// L_RCS_XFD_12_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_CROSSFEED_VLV_CMD", 12 );
		dopIOM15[2][10].Connect( pBundle, 0 );// R_RCS_FU_XFD_12_OP
		dopIOM15[2][9].Connect( pBundle, 1 );// R_RCS_FU_XFD_12_CL
		dopIOM15[2][1].Connect( pBundle, 2 );// R_RCS_OX_XFD_12_OP
		dopIOM15[2][0].Connect( pBundle, 3 );// R_RCS_OX_XFD_12_CL

		pBundle = BundleManager()->CreateBundle( "ROMS_TANKISOL_VLV_CMD", 12 );
		dopIOM7[1][3].Connect( pBundle, 0 );// R_OMS_FU_TK_ISOV_A_OP
		dopIOM7[1][4].Connect( pBundle, 1 );// R_OMS_FU_TK_ISOV_A_CL
		dopIOM7[1][5].Connect( pBundle, 2 );// R_OMS_OX_TK_ISOV_A_OP
		dopIOM7[1][6].Connect( pBundle, 3 );// R_OMS_OX_TK_ISOV_A_CL
		dopIOM15[1][5].Connect( pBundle, 10 );// R_OMS_TK_V_B_OP
		dopIOM15[1][6].Connect( pBundle, 11 );// R_OMS_TK_V_B_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_GPC_CMD", 8 );
		dopIOM15[1][1].Connect( pBundle, 4 );// L_OMS_VLV_1_COIL_1_CMD
		
		pBundle = BundleManager()->CreateBundle( "ROMS_HE_VAPOR_ISOL_A", 8 );
		dipIOM11[1][4].Connect( pBundle, 3 );// R OMS HE ISOV B POSN OP
		dipIOM3[1][4].Connect( pBundle, 7 );// R OMS VAP ISOV 2 OP

		pBundle = BundleManager()->CreateBundle( "ROMS_ENGINE", 16 );
		dipIOM11[1][5].Connect( pBundle, 2 );// R OMS ENG PRESS V OP
		//OMSEngineBipropellent1OPVlv.Connect( pBundle, 10 );
		//OMSEngineBipropellent2OPVlv.Connect( pBundle, 11 );
		dopIOM12[1][4].Connect( pBundle, 14 );// R OMS ENG PGE V2 OP
		dipIOM3[1][5].Connect( pBundle, 15 );// R OMS ENG PGE V2 POSN OP

		pBundle = BundleManager()->CreateBundle( "ROMS_GPC_CMD", 8 );
		dopIOM15[1][2].Connect( pBundle, 1 );// R_OMS_HE_ISOV_B_OP
		dopIOM7[1][2].Connect( pBundle, 3 );// R_OMS_VAP_ISOV_2_OP
		dopIOM7[1][1].Connect( pBundle, 5 );// R_OMS_VLV_2_COIL_1_CMD

		pBundle = BundleManager()->CreateBundle( "OMS_ENGINE_SWITCHES", 6 );
		dipIOM3[1][7].Connect( pBundle, 2 );// R ARM 1
		dipIOM3[1][6].Connect( pBundle, 3 );// R ARM/PRESS 1

		pBundle = BundleManager()->CreateBundle( "RCS_XFD_AMC_MDM", 4 );
		dipIOM11[1][14].Connect( pBundle, 0 );// L OXFU_XFD_VLV_12_OP
		dipIOM11[1][15].Connect( pBundle, 3 );// R OXFU_XFD_VLV_345_OP
		return;
	}

	void SimpleMDM_FA4::Rx( const BUS_ID id, void* data, const unsigned short datalen )
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
					case 0b0110:// IOM 6 AIS
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

	void SimpleMDM_FA4::OnPreStep( double simt, double simdt, double mjd )
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
