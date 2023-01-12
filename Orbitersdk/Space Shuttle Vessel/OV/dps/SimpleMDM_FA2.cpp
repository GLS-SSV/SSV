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
********************************************/
#include "SimpleMDM_FA2.h"
#include "SimpleShuttleBus.h"


namespace dps
{
	SimpleMDM_FA2::SimpleMDM_FA2( AtlantisSubsystemDirector* _director ):SimpleMDM( _director, "SimpleMDM_FA2" ),
		powered(true)
	{
	}

	SimpleMDM_FA2::~SimpleMDM_FA2()
	{
	}

	void SimpleMDM_FA2::Realize( void )
	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "MDM_Power", 16 );
		Power1.Connect( pBundle, 5 );
		Power2.Connect( pBundle, 5 );

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_IND_RH_2", 16 );
		dipIOM11[0][13].Connect( pBundle, 13 );// RH_VENTS_8_AND_9_CLOSE_2
		dipIOM11[0][14].Connect( pBundle, 14 );// RH_VENTS_8_AND_9_OPEN_2
		dipIOM11[0][15].Connect( pBundle, 15 );// RH_VENTS_8_AND_9_PURGE_IND_2

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2A", 16 );
		dopIOM7[0][5].Connect( pBundle, 13 );// RH_VENTS_8_9_MOTOR_2_OPEN_A
		dopIOM7[0][4].Connect( pBundle, 14 );// RH_VENTS_8_9_MOTOR_2_CLOSE_A
		dopIOM7[0][6].Connect( pBundle, 15 );// RH_VENTS_8_9_MOTOR_2_PURGE_A

		pBundle = BundleManager()->CreateBundle( "VENTDOORS_CMD_RH_2B", 16 );
		dopIOM15[0][4].Connect( pBundle, 13 );// RH_VENTS_8_9_MOTOR_2_OPEN_B
		dopIOM15[0][3].Connect( pBundle, 14 );// RH_VENTS_8_9_MOTOR_2_CLOSE_B
		dopIOM15[0][5].Connect( pBundle, 15 );// RH_VENTS_8_9_MOTOR_2_PURGE_B

		pBundle = BundleManager()->CreateBundle( "ET_LOX_SENSORS", 16 );
		dipIOM11[0][8].Connect( pBundle, 1 );
		dipIOM6[28].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "ET_LH2_SENSORS", 16 );
		dipIOM3[0][9].Connect( pBundle, 1 );
		dipIOM6[27].Connect( pBundle, 13 );

		pBundle = BundleManager()->CreateBundle( "MPS_SENSORS", 2 );
		dipIOM14[22].Connect( pBundle, 0 );

		pBundle = BundleManager()->CreateBundle( "OMS_TVC_L", 16 );
		dopIOM4_HI[7].Connect( pBundle, 6 );// OMS TVC: L SEC P ACTR CMD ("STBY")
		dopIOM4_HI[8].Connect( pBundle, 7 );// OMS TVC: L SEC Y ACTR CMD ("STBY")
		dipIOM14[14].Connect( pBundle, 10 );// OMS - L ENG STBY P ACTR POSN IN
		dipIOM14[15].Connect( pBundle, 11 );// OMS - L ENG STBY Y ACTR POSN IN

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_A_LRCS", 14 );
		dopIOM2[0][0].Connect( pBundle, 0 );// RJDA 2B L RCS JET L3A CMD A
		dopIOM2[0][1].Connect( pBundle, 4 );// RJDA 2B L RCS JET L3L CMD A
		dopIOM2[0][2].Connect( pBundle, 11 );// RJDA 2B L RCS JET L3D CMD A

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_A_RRCS", 14 );
		dopIOM2[0][3].Connect( pBundle, 0 );// RJDA 2B R RCS JET R3A CMD A
		dopIOM2[0][4].Connect( pBundle, 4 );// RJDA 2B R RCS JET R3R CMD A
		dopIOM2[0][5].Connect( pBundle, 11 );// RJDA 2B R RCS JET R3D CMD A
		dopIOM2[0][6].Connect( pBundle, 13 );// RJDA 2B VERN JET R5R CMD A
		dopIOM2[0][7].Connect( pBundle, 12 );// RJDA 2B VERN JET R5D CMD A

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_B_LRCS", 14 );
		dopIOM10[0][0].Connect( pBundle, 0 );// RJDA 2B L RCS JET L3A CMD B
		dopIOM10[0][1].Connect( pBundle, 4 );// RJDA 2B L RCS JET L3L CMD B
		dopIOM10[0][2].Connect( pBundle, 11 );// RJDA 2B L RCS JET L3D CMD B

		pBundle = BundleManager()->CreateBundle( "RCS_CMD_B_RRCS", 14 );
		dopIOM10[0][3].Connect( pBundle, 0 );// RJDA 2B R RCS JET R3A CMD B
		dopIOM10[0][4].Connect( pBundle, 4 );// RJDA 2B R RCS JET R3R CMD B
		dopIOM10[0][5].Connect( pBundle, 11 );// RJDA 2B R RCS JET R3D CMD B
		dopIOM10[0][6].Connect( pBundle, 13 );// RJDA 2B VERN JET R5R CMD B
		dopIOM10[0][7].Connect( pBundle, 12 );// RJDA 2B VERN JET R5D CMD B

		pBundle = BundleManager()->CreateBundle( "RCS_PC_EVT_LRCS", 14 );
		dipIOM5[0][0].Connect( pBundle, 0 );// RJDA 2 JET L3A CHMBR PRESS IND
		dipIOM5[0][1].Connect( pBundle, 4 );// RJDA 2 JET L3L CHMBR PRESS IND
		dipIOM5[0][2].Connect( pBundle, 11 );// RJDA 2 JET L3D CHMBR PRESS IND

		pBundle = BundleManager()->CreateBundle( "RCS_PC_EVT_RRCS", 14 );
		dipIOM5[0][3].Connect( pBundle, 0 );// RJDA 2 JET R3A CHMBR PRESS IND
		dipIOM5[0][4].Connect( pBundle, 4 );// RJDA 2 JET R3R CHMBR PRESS IND
		dipIOM5[0][5].Connect( pBundle, 11 );// RJDA 2 JET R3D CHMBR PRESS IND
		dipIOM5[0][6].Connect( pBundle, 13 );// RJDA 2 JET R5R CHMBR PRESS IND
		dipIOM5[0][7].Connect( pBundle, 12 );// RJDA 2 JET R5D CHMBR PRESS IND

		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_LRCS", 14 );
		dipIOM8[0][0].Connect( pBundle, 0 );// RJDA 2 JET L3A DRIVER
		dipIOM8[0][1].Connect( pBundle, 4 );// RJDA 2 JET L3L DRIVER
		dipIOM8[0][2].Connect( pBundle, 11 );// RJDA 2 JET L3D DRIVER

		pBundle = BundleManager()->CreateBundle( "RCS_DRIVER_RRCS", 14 );
		dipIOM8[0][3].Connect( pBundle, 0 );// RJDA 2 JET R3A DRIVER
		dipIOM8[0][4].Connect( pBundle, 4 );// RJDA 2 JET R3R DRIVER
		dipIOM8[0][5].Connect( pBundle, 11 );// RJDA 2 JET R3D DRIVER
		dipIOM8[0][6].Connect( pBundle, 13 );// RJDA 2 JET R5R DRIVER
		dipIOM8[0][7].Connect( pBundle, 12 );// RJDA 2 JET R5D DRIVER

		pBundle = BundleManager()->CreateBundle( "LRCS_MANF_34_ISOL", 12 );
		dipIOM11[2][0].Connect( pBundle, 2 );// L_FU_MANF_ISOV_3_OP
		dipIOM11[2][1].Connect( pBundle, 3 );// L_FU_MANF_ISOV_3_CL
		dipIOM11[2][2].Connect( pBundle, 4 );// L_OX_MANF_ISOV_3_OP
		dipIOM11[2][3].Connect( pBundle, 5 );// L_OX_MANF_ISOV_3_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_HE_ISOL", 16 );
		dipIOM3[2][10].Connect( pBundle, 10 );// R_HE_FU_PRESS_V_B_OP
		dipIOM3[2][11].Connect( pBundle, 11 );// R_HE_FU_PRESS_V_B_CL
		dipIOM3[2][8].Connect( pBundle, 14 );// R_HE_OX_PRESS_V_B_OP
		dipIOM3[2][9].Connect( pBundle, 15 );// R_HE_OX_PRESS_V_B_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_TANK_ISOL_12", 10 );
		dipIOM3[2][6].Connect( pBundle, 2 );// R_FU_TK_ISO_V_12_OP
		dipIOM3[2][7].Connect( pBundle, 3 );// R_FU_TK_ISO_V_12_CL
		dipIOM3[2][4].Connect( pBundle, 6 );// R_OX_TK_ISO_V_12_OP
		dipIOM3[2][5].Connect( pBundle, 7 );// R_OX_TK_ISO_V_12_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_34_ISOL", 12 );
		dipIOM3[2][0].Connect( pBundle, 2 );// R_FU_MANF_ISOV_3_OP
		dipIOM3[2][1].Connect( pBundle, 3 );// R_FU_MANF_ISOV_3_CL
		dipIOM3[2][2].Connect( pBundle, 4 );// R_OX_MANF_ISOV_3_OP
		dipIOM3[2][3].Connect( pBundle, 5 );// R_OX_MANF_ISOV_3_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_MANF_5_ISOL", 8 );
		dipIOM3[2][13].Connect( pBundle, 4 );// R_FU_MANF_ISOV_5_OP
		dipIOM3[2][15].Connect( pBundle, 5 );// R_FU_MANF_ISOV_5_CL
		dipIOM3[2][12].Connect( pBundle, 6 );// R_OX_MANF_ISOV_5_OP
		dipIOM3[2][14].Connect( pBundle, 7 );// R_OX_MANF_ISOV_5_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_XFD_345", 10 );
		dipIOM11[2][6].Connect( pBundle, 2 );// L_RCS_FU_XFD_345_OP
		dipIOM11[2][7].Connect( pBundle, 3 );// L_RCS_FU_XFD_345_CL
		dipIOM11[2][4].Connect( pBundle, 6 );// L_RCS_OX_XFD_345_OP
		dipIOM11[2][5].Connect( pBundle, 7 );// L_RCS_OX_XFD_345_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_TANK_ISOL_B", 10 );
		dipIOM3[1][2].Connect( pBundle, 2 );// L_OMS_FU_TK_ISOV_B_OP
		dipIOM3[1][3].Connect( pBundle, 3 );// L_OMS_FU_TK_ISOV_B_CL
		dipIOM11[1][2].Connect( pBundle, 6 );// L_OMS_OX_TK_ISOV_B_OP
		dipIOM11[1][3].Connect( pBundle, 7 );// L_OMS_OX_TK_ISOV_B_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_XFD_B", 10 );
		dipIOM11[1][8].Connect( pBundle, 2 );// L_OMS_FU_XFD_V_B_OP
		dipIOM11[1][9].Connect( pBundle, 3 );// L_OMS_FU_XFD_V_B_CL
		dipIOM11[1][6].Connect( pBundle, 6 );// L_OMS_OX_XFD_V_B_OP
		dipIOM11[1][7].Connect( pBundle, 7 );// L_OMS_OX_XFD_V_B_CL

		pBundle = BundleManager()->CreateBundle( "ROMS_XFD_B", 10 );
		dipIOM3[1][10].Connect( pBundle, 2 );// R_OMS_FU_XFD_V_B_OP
		dipIOM3[1][11].Connect( pBundle, 3 );// R_OMS_FU_XFD_V_B_CL
		dipIOM3[1][8].Connect( pBundle, 6 );// R_OMS_OX_XFD_V_B_OP
		dipIOM3[1][9].Connect( pBundle, 7 );// R_OMS_OX_XFD_V_B_CL

		pBundle = BundleManager()->CreateBundle( "LRCS_HEISOL_TANKISOL_12_VLV_CMD", 10 );
		dopIOM7[2][9].Connect( pBundle, 2 );// L_HE_PRESS_V_B_OP_A
		dopIOM7[2][10].Connect( pBundle, 3 );// L_HE_PRESS_V_B_CL_A
		dopIOM7[2][5].Connect( pBundle, 8 );// L_TK_ISOV_12_OP_A
		dopIOM7[2][4].Connect( pBundle, 9 );// L_TK_ISOV_12_CL_A

		pBundle = BundleManager()->CreateBundle( "LRCS_MANIFISOL_1234_VLV_CMD", 12 );
		dopIOM7[0][0].Connect( pBundle, 1 );// L_MANF_ISOV_NO_1_CL_A
		dopIOM15[2][8].Connect( pBundle, 2 );// L_MANF_ISOV_NO_1_CL_B
		dopIOM7[2][6].Connect( pBundle, 6 );// L_MANF_ISOV_NO_3_OP

		pBundle = BundleManager()->CreateBundle( "LRCS_MANIFISOL_5_VLV_CMD", 6 );
		dopIOM7[2][11].Connect( pBundle, 1 );// L_MANF_ISO_5_CLOSE_A

		pBundle = BundleManager()->CreateBundle( "RRCS_HEISOL_TANKISOL_12_VLV_CMD", 10 );
		dopIOM15[2][9].Connect( pBundle, 2 );// R_HE_PRESS_V_B_OP_A
		dopIOM15[2][10].Connect( pBundle, 3 );// R_HE_PRESS_V_B_CL_A
		dopIOM15[2][3].Connect( pBundle, 4 );// R_FU_TK_ISOV_12_OP_B
		dopIOM15[2][2].Connect( pBundle, 5 );// R_FU_TK_ISOV_12_CL_B
		dopIOM15[2][5].Connect( pBundle, 6 );// R_OX_TK_ISOV_12_OP_B
		dopIOM15[2][4].Connect( pBundle, 7 );// R_OX_TK_ISOV_12_CL_B

		pBundle = BundleManager()->CreateBundle( "RRCS_MANIFISOL_1234_VLV_CMD", 12 );
		dopIOM15[0][1].Connect( pBundle, 1 );// R_MANF_ISOV_NO_1_CL_A
		dopIOM7[2][8].Connect( pBundle, 2 );// R_MANF_ISOV_NO_1_CL_B
		dopIOM15[2][6].Connect( pBundle, 6 );// R_MANF_ISOV_NO_3_OP

		pBundle = BundleManager()->CreateBundle( "RRCS_MANIFISOL_5_VLV_CMD", 6 );
		dopIOM15[2][11].Connect( pBundle, 0 );// R_MANF_ISO_5_OPEN_A

		pBundle = BundleManager()->CreateBundle( "LRCS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[2][3].Connect( pBundle, 6 );// L_RCS_FU_XFD_345_OP
		dopIOM7[2][2].Connect( pBundle, 7 );// L_RCS_FU_XFD_345_CL
		dopIOM7[2][1].Connect( pBundle, 8 );// L_RCS_OX_XFD_345_OP
		dopIOM7[2][0].Connect( pBundle, 9 );// L_RCS_OX_XFD_345_CL

		pBundle = BundleManager()->CreateBundle( "RRCS_CROSSFEED_VLV_CMD", 12 );
		dopIOM15[2][1].Connect( pBundle, 10 );// R_RCS_XFD_345_OP
		dopIOM15[2][0].Connect( pBundle, 11 );// R_RCS_XFD_345_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_TANKISOL_VLV_CMD", 12 );
		dopIOM7[1][5].Connect( pBundle, 4 );// L_OMS_TK_V_A_OP
		dopIOM7[1][6].Connect( pBundle, 5 );// L_OMS_TK_V_A_CL
		dopIOM15[1][3].Connect( pBundle, 6 );// L_OMS_FU_TK_ISOV_B_OP
		dopIOM15[1][4].Connect( pBundle, 7 );// L_OMS_FU_TK_ISOV_B_CL
		dopIOM15[1][5].Connect( pBundle, 8 );// L_OMS_OX_TK_ISOV_B_OP
		dopIOM15[1][6].Connect( pBundle, 9 );// L_OMS_OX_TK_ISOV_B_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[1][11].Connect( pBundle, 4 );// L_OMS_XFD_A_OP
		dopIOM7[1][12].Connect( pBundle, 5 );// L_OMS_XFD_A_CL
		dopIOM15[1][7].Connect( pBundle, 6 );// L_OMS_FU_XFD_V_B_OP
		dopIOM15[1][8].Connect( pBundle, 7 );// L_OMS_FU_XFD_V_B_CL
		dopIOM15[1][11].Connect( pBundle, 8 );// L_OMS_OX_XFD_V_B_OP
		dopIOM15[1][12].Connect( pBundle, 9 );// L_OMS_OX_XFD_V_B_CL

		pBundle = BundleManager()->CreateBundle( "ROMS_CROSSFEED_VLV_CMD", 12 );
		dopIOM7[1][13].Connect( pBundle, 4 );// R_OMS_XFD_A_OP
		dopIOM7[1][14].Connect( pBundle, 5 );// R_OMS_XFD_A_CL
		dopIOM15[1][9].Connect( pBundle, 6 );// R_OMS_FU_XFD_V_B_OP
		dopIOM15[1][10].Connect( pBundle, 7 );// R_OMS_FU_XFD_V_B_CL
		dopIOM15[1][13].Connect( pBundle, 8 );// R_OMS_OX_XFD_V_B_OP
		dopIOM15[1][14].Connect( pBundle, 9 );// R_OMS_OX_XFD_V_B_CL

		pBundle = BundleManager()->CreateBundle( "LOMS_HE_VAPOR_ISOL_A", 8 );
		dipIOM11[1][4].Connect( pBundle, 3 );// L OMS HE ISOV B POSN OP
		dipIOM3[1][4].Connect( pBundle, 7 );// L OMS VAP ISOV 2 OP

		pBundle = BundleManager()->CreateBundle( "LOMS_ENGINE", 16 );
		dopIOM12[1][4].Connect( pBundle, 14 );// L OMS ENG PGE V2 OP
		dipIOM3[1][5].Connect( pBundle, 15 );// L OMS ENG PGE V2 POSN OP

		pBundle = BundleManager()->CreateBundle( "LOMS_GPC_CMD", 8 );
		dopIOM15[1][2].Connect( pBundle, 1 );// L_OMS_HE_ISOV_B_OP
		dopIOM7[1][2].Connect( pBundle, 3 );// L_OMS_VAP_ISOV_2_OP
		dopIOM15[1][1].Connect( pBundle, 7 );// L_OMS_VLV_2_COIL_2_CMD

		pBundle = BundleManager()->CreateBundle( "ROMS_GPC_CMD", 8 );
		dopIOM7[1][1].Connect( pBundle, 7 );// R_OMS_VLV_2_COIL_2_CMD
		return;
	}

	void SimpleMDM_FA2::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		ReadEna = false;
		GetBus()->SendCommand( cw, cdw );
		ReadEna = true;
		return;
	}

	void SimpleMDM_FA2::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		if (!Power1.IsSet() && !Power2.IsSet()) return;
		if (!ReadEna) return;
		if (cw.MIAaddr != GetAddr()) return;

		unsigned short modecontrol = (cw.payload >> 9) & 0xF;
		unsigned short IOMaddr = (cw.payload >> 5) & 0xF;
		unsigned short IOMch = cw.payload & 0x1F;
		unsigned short IOMdata = 0;
		switch (modecontrol)
		{
			case 0b1000:// direct mode output (GPC-to-MDM)
				switch (IOMaddr)
				{
					case 0b0000:// IOM 0 AOD
						break;
					case 0b0001:// IOM 1 AID
						break;
					case 0b0010:// IOM 2 DOL
						IOMdata = cdw[0].payload;
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM2 );
						break;
					case 0b0011:// IOM 3 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM3 );
						break;
					case 0b0100:// IOM 4 AOD
						IOMdata = cdw[0].payload;
						IOM_AOD( 0b001, IOMch, IOMdata, dopIOM4_HI, dopIOM4_LO );
						break;
					case 0b0101:// IOM 5 DIL
						IOMdata = cdw[0].payload;
						IOM_DIL( 0b001, IOMch, IOMdata, dipIOM5 );
						break;
					case 0b0110:// IOM 6 AIS
						IOMdata = cdw[0].payload;
						IOM_AIS( 0b001, IOMch, IOMdata, dipIOM6 );
						break;
					case 0b0111:// IOM 7 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM7 );
						break;
					case 0b1000:// IOM 8 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM8 );
						break;
					case 0b1001:// IOM 9 AID
						break;
					case 0b1010:// IOM 10 DOL
						IOMdata = cdw[0].payload;
						IOM_DOL( 0b001, IOMch, IOMdata, dopIOM10 );
						break;
					case 0b1011:// IOM 11 DIH
						IOMdata = cdw[0].payload;
						IOM_DIH( 0b001, IOMch, IOMdata, dipIOM11 );
						break;
					case 0b1100:// IOM 12 DOH
						IOMdata = cdw[0].payload;
						IOM_DOH( 0b001, IOMch, IOMdata, dopIOM12 );
						break;
					case 0b1101:// IOM 13 DIL
						IOMdata = cdw[0].payload;
						IOM_DIL( 0b001, IOMch, IOMdata, dipIOM13 );
						break;
					case 0b1110:// IOM 14 AIS
						IOMdata = cdw[0].payload;
						IOM_AIS( 0b001, IOMch, IOMdata, dipIOM14 );
						break;
					case 0b1111:// IOM 15 DOH
						IOMdata = cdw[0].payload;
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
						{
							IOM_DOL( 0b000, IOMch, IOMdata, dopIOM2 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0011:// IOM 3 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM3 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0100:// IOM 4 AOD
						{
							IOM_AOD( 0b000, IOMch, IOMdata, dopIOM4_HI, dopIOM4_LO );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0101:// IOM 5 DIL
						{
							IOM_DIL( 0b000, IOMch, IOMdata, dipIOM5 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0110:// IOM 6 AIS
						{
							IOM_AIS( 0b000, IOMch, IOMdata, dipIOM6 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b0111:// IOM 7 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM7 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1000:// IOM 8 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM8 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1001:// IOM 9 AID
						break;
					case 0b1010:// IOM 10 DOL
						{
							IOM_DOL( 0b000, IOMch, IOMdata, dopIOM10 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1011:// IOM 11 DIH
						{
							IOM_DIH( 0b000, IOMch, IOMdata, dipIOM11 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1100:// IOM 12 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM12 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1101:// IOM 13 DIL
						{
							IOM_DIL( 0b000, IOMch, IOMdata, dipIOM13 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1110:// IOM 14 AIS
						{
							IOM_AIS( 0b000, IOMch, IOMdata, dipIOM14 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
					case 0b1111:// IOM 15 DOH
						{
							IOM_DOH( 0b000, IOMch, IOMdata, dopIOM15 );

							dps::SIMPLEBUS_COMMAND_WORD _cw;
							_cw.MIAaddr = 0;

							dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
							_cdw.MIAaddr = GetAddr();
							_cdw.payload = IOMdata;
							_cdw.SEV = 0b101;

							busCommand( _cw, &_cdw );
						}
						break;
				}
				break;
			case 0b1100:// return the command word
				{
					dps::SIMPLEBUS_COMMAND_WORD _cw;
					_cw.MIAaddr = 0;

					dps::SIMPLEBUS_COMMANDDATA_WORD _cdw;
					_cdw.MIAaddr = GetAddr();
					_cdw.payload = (((((cw.payload & 0b111111111) << 5) | cw.numwords) & 0b00111111111111) << 2);
					_cdw.SEV = 0b101;

					busCommand( _cw, &_cdw );
				}
				break;
		}
		return;
	}

	void SimpleMDM_FA2::OnPreStep( double simt, double simdt, double mjd )
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
