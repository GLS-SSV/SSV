#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 
#endif// _CRT_SECURE_NO_WARNINGS

#include "SSB_PL_BAY_DOORS.h"


constexpr float SSB_TIMER_CONSTANTS_ARRAY[6] = {40.0, 40.0, 60.0, 126.0, 60.0, 126.0};// single motor times [s]


namespace dps
{
	SSB_PL_BAY_DOORS::SSB_PL_BAY_DOORS( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SSB_PL_BAY_DOORS" ),
		SSB_PBD_MORE_WORK_IND(true), SSB_LATCH_DOOR_EXPIR_TIME(0.0), SSB_OPEN_CLOSE_FEEDBACK_INDIC(false), SSB_PREVIOUS_SWITCH_POS(0), SSB_OPEN_CLOSE_COMPLETE(0), SSB_CURRENT_LATCH_DOOR_POINTER(0)
	{
		SSB_COMMANDS_ENABLED_ARRAY[0][0] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[0][1] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[1][0] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[1][1] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[2][0] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[2][1] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[3][0] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[3][1] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[4][0] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[4][1] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[5][0] = 0;
		SSB_COMMANDS_ENABLED_ARRAY[5][1] = 0;

		CSBB_PF01_OUTPUT_1 = 0;
		CSBB_PF01_OUTPUT_2 = 0;
		CSBB_PF01_OUTPUT_3 = 0;
		CSBB_PF01_OUTPUT_4 = 0;
		CSBB_PF02_OUTPUT_1 = 0;
		CSBB_PF02_OUTPUT_2 = 0;
		CSBB_PF02_OUTPUT_3 = 0;
		CSBB_PF02_OUTPUT_4 = 0;
		return;
	}

	SSB_PL_BAY_DOORS::~SSB_PL_BAY_DOORS( void )
	{
		return;
	}

	bool SSB_PL_BAY_DOORS::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void SSB_PL_BAY_DOORS::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	void SSB_PL_BAY_DOORS::OnPostStep( double simt, double simdt, double mjd )
	{
		PF1_IOM3_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM3_CH0_DATA );
		PF1_IOM6_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM6_CH0_DATA );
		PF1_IOM9_CH0 = ReadCOMPOOL_IS( SCP_PF1_IOM9_CH0_DATA );
		PF2_IOM3_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM3_CH0_DATA );
		PF2_IOM6_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM6_CH0_DATA );
		PF2_IOM9_CH0 = ReadCOMPOOL_IS( SCP_PF2_IOM9_CH0_DATA );

		//// power on/off processing
		if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG ) == 1)
		{
			WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_FLAG, 0 );
			//CSBB_PBD_OUTPUT_INDICATOR = 1;
			if (ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) == 0x0001)
			{
				// power on
				CSBB_PF01_OUTPUT_1 |= 0x01C0;
				CSBB_PF01_OUTPUT_3 |= 0x0180;
				CSBB_PF01_OUTPUT_4 |= 0x0080;
				CSBB_PF02_OUTPUT_1 |= 0x01C0;
				CSBB_PF02_OUTPUT_3 |= 0x00C0;
				CSBB_PF02_OUTPUT_4 |= 0x0002;
			}
			else
			{
				// power off
				CSBB_PF01_OUTPUT_1 &= !0x01C0;
				CSBB_PF01_OUTPUT_3 &= !0x0180;
				CSBB_PF01_OUTPUT_4 &= !0x0080;
				CSBB_PF02_OUTPUT_1 &= !0x01C0;
				CSBB_PF02_OUTPUT_3 &= !0x00C0;
				CSBB_PF02_OUTPUT_4 &= !0x0002;
			}
		}

		//// control switch position determination
		{
			bool A = ((PF1_IOM3_CH0 & 0x0080) != 0);// V72K3222Y OPEN C
			bool B = ((PF1_IOM6_CH0 & 0x0080) != 0);// V72K3221Y OPEN B
			bool C = ((PF2_IOM6_CH0 & 0x0080) != 0);// V72K3223Y OPEN D
			bool D = ((PF2_IOM3_CH0 & 0x0080) != 0);// V72K3220Y OPEN A
			bool E = ((PF1_IOM3_CH0 & 0x0100) != 0);// V72K3232Y CLOSE C
			bool F = ((PF1_IOM6_CH0 & 0x0100) != 0);// V72K3231Y CLOSE B
			bool G = ((PF2_IOM6_CH0 & 0x0100) != 0);// V72K3233Y CLOSE D
			bool H = ((PF2_IOM3_CH0 & 0x0100) != 0);// V72K3230Y CLOSE A

			bool SSB_SWITCH_OPEN_INDICATOR = ((A && B) || (A && C) || (A && D) || (B && D) || (C && D)) && ((!E && !F) || (!E && !G) || (!E && !H) || (!F && !H) || (!G && !H));
			bool SSB_SWITCH_CLOSE_INDICATOR = ((!A && !B) || (!A && !C) || (!A && !D) || (!B && !D) || (!C && !D)) && ((E && F) || (E && G) || (E && H) || (F && H) || (G && H));

			if (SSB_SWITCH_OPEN_INDICATOR)
			{
				if (SSB_SWITCH_CLOSE_INDICATOR)
				{
					WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 0 );
					WriteCOMPOOL_C( SCP_CSBB_PBD_SWITCH_IND_TEXT, "FAIL", 4 );
				}
				else
				{
					WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 1 );
					WriteCOMPOOL_C( SCP_CSBB_PBD_SWITCH_IND_TEXT, "OP", 4 );
				}
			}
			else
			{
				if (SSB_SWITCH_CLOSE_INDICATOR)
				{
					WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 2 );
					WriteCOMPOOL_C( SCP_CSBB_PBD_SWITCH_IND_TEXT, "CL", 4 );
				}
				else
				{
					WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 0 );
					WriteCOMPOOL_C( SCP_CSBB_PBD_SWITCH_IND_TEXT, "STOP", 4 );
				}
			}

			if (ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) == 1)
			{
				if (ReadCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM ) == 1)
				{
					WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 0 );
				}
				else
				{
					if (ReadCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM ) == 1)
					{
						WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 1 );
					}
					else
					{
						WriteCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC, 2 );
					}
				}
			}
			// TODO switch validity
		}

		bool CSSB_FULL_EX_FLAG = true;// TODO
		if ((ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) != SSB_PREVIOUS_SWITCH_POS) || (CSSB_FULL_EX_FLAG))
		{
			//// CRT feedback display
			char cl_5_8_str[4];
			char cl_9_12_str[4];
			char cl_1_4_str[4];
			char cl_13_16_str[4];
			char r_fwd_bhd_str[4];
			char r_aft_bhd_str[4];
			char r_door_str[4];
			char l_fwd_bhd_str[4];
			char l_aft_bhd_str[4];
			char l_door_str[4];
			{
				bool p1;
				bool p2;
				bool p3;
				bool p4;

				// CL 5-8
				p1 = ((PF1_IOM9_CH0 & 0x0010) != 0);// V37X3390Y REL 1
				p2 = ((PF2_IOM9_CH0 & 0x0010) != 0);// V37X3391Y REL 2
				p3 = ((PF1_IOM9_CH0 & 0x0020) != 0);// V37X3395Y LAT 1
				p4 = ((PF2_IOM9_CH0 & 0x0020) != 0);// V37X3396Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, cl_5_8_str );
				WriteCOMPOOL_C( SCP_CSBB_C_LCH_5_8_TEXT, cl_5_8_str, 2 );

				// CL 9-12
				p1 = ((PF1_IOM9_CH0 & 0x0080) != 0);// V37X3405Y REL 1
				p2 = ((PF2_IOM9_CH0 & 0x0080) != 0);// V37X3406Y REL 2
				p3 = ((PF1_IOM9_CH0 & 0x0040) != 0);// V37X3400Y LAT 1
				p4 = ((PF2_IOM9_CH0 & 0x0040) != 0);// V37X3401Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, cl_9_12_str );
				WriteCOMPOOL_C( SCP_CSBB_C_LCH_9_12_TEXT, cl_9_12_str, 2 );

				// CL 1-4
				p1 = ((PF1_IOM9_CH0 & 0x0004) != 0);// V37X3380Y REL 1
				p2 = ((PF2_IOM9_CH0 & 0x0004) != 0);// V37X3381Y REL 2
				p3 = ((PF1_IOM9_CH0 & 0x0008) != 0);// V37X3385Y LAT 1
				p4 = ((PF2_IOM9_CH0 & 0x0008) != 0);// V37X3386Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, cl_1_4_str );
				WriteCOMPOOL_C( SCP_CSBB_C_LCH_1_4_TEXT, cl_1_4_str, 2 );

				// CL 13-16
				p1 = ((PF2_IOM9_CH0 & 0x0200) != 0);// V37X3415Y REL 1
				p2 = ((PF1_IOM9_CH0 & 0x0200) != 0);// V37X3416Y REL 2
				p3 = ((PF2_IOM9_CH0 & 0x0100) != 0);// V37X3410Y LAT 1
				p4 = ((PF1_IOM9_CH0 & 0x0100) != 0);// V37X3411Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, cl_13_16_str );
				WriteCOMPOOL_C( SCP_CSBB_C_LCH_13_16_TEXT, cl_13_16_str, 2 );

				// right fwd bhd
				p1 = ((PF1_IOM3_CH0 & 0x0004) != 0);// V37X3430Y REL 1
				p2 = ((PF2_IOM3_CH0 & 0x0004) != 0);// V37X3431Y REL 2
				p3 = ((PF1_IOM3_CH0 & 0x0008) != 0);// V37X3440Y LAT 1
				p4 = ((PF2_IOM3_CH0 & 0x0008) != 0);// V37X3441Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, r_fwd_bhd_str );
				WriteCOMPOOL_C( SCP_CSBB_R_FWD_BHD_TEXT, r_fwd_bhd_str, 2 );

				// right aft bhd
				p1 = ((PF2_IOM3_CH0 & 0x0010) != 0);// V37X3450Y REL 1
				p2 = ((PF1_IOM3_CH0 & 0x0010) != 0);// V37X3451Y REL 2
				p3 = ((PF2_IOM3_CH0 & 0x0020) != 0);// V37X3460Y LAT 1
				p4 = ((PF1_IOM3_CH0 & 0x0020) != 0);// V37X3461Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, r_aft_bhd_str );
				WriteCOMPOOL_C( SCP_CSBB_R_AFT_BHD_TEXT, r_aft_bhd_str, 2 );

				// right door
				bool E = ((PF1_IOM3_CH0 & 0x0040) != 0);// V37X3300Y OPN 1
				bool F = ((PF2_IOM3_CH0 & 0x0040) != 0);// V37X3301Y OPN 2
				bool G = ((PF1_IOM3_CH0 & 0x0001) != 0);// V37X3435Y FWD RDY 1
				bool H = ((PF2_IOM3_CH0 & 0x0001) != 0);// V37X3436Y FWD RDY 2
				bool I = ((PF2_IOM9_CH0 & 0x0001) != 0);// V37X3437Y FWD RDY 3
				bool J = ((PF1_IOM3_CH0 & 0x0002) != 0);// V37X3455Y AFT RDY 1
				bool K = ((PF2_IOM3_CH0 & 0x0002) != 0);// V37X3456Y AFT RDY 2
				bool L = ((PF2_IOM9_CH0 & 0x0002) != 0);// V37X3457Y AFT RDY 3
				bool M = ((PF1_IOM3_CH0 & 0x0400) != 0);// V37X3302Y CLS 1
				bool N = ((PF2_IOM3_CH0 & 0x0400) != 0);// V37X3303Y CLS 2
				p1 = E && F;
				p2 = (G && H) || (H && I) || (G && I);
				p3 = (J && K) || (K && L) || (J && L);
				p4 = M && N;
				PBD_DOOR_STATUS( p1, p2, p3, p4, r_door_str );
				WriteCOMPOOL_C( SCP_CSBB_L_DOOR_TEXT, r_door_str, 3 );

				// left fwd bhd
				p1 = ((PF1_IOM6_CH0 & 0x0004) != 0);// V37X3320Y REL 1
				p2 = ((PF2_IOM6_CH0 & 0x0004) != 0);// V37X3321Y REL 2
				p3 = ((PF1_IOM6_CH0 & 0x0008) != 0);// V37X3330Y LAT 1
				p4 = ((PF2_IOM6_CH0 & 0x0008) != 0);// V37X3331Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, l_fwd_bhd_str );
				WriteCOMPOOL_C( SCP_CSBB_L_FWD_BHD_TEXT, l_fwd_bhd_str, 2 );

				// left aft bhd
				p1 = ((PF1_IOM6_CH0 & 0x0010) != 0);// V37X3350Y REL 1
				p2 = ((PF2_IOM6_CH0 & 0x0010) != 0);// V37X3351Y REL 2
				p3 = ((PF1_IOM6_CH0 & 0x0020) != 0);// V37X3360Y LAT 1
				p4 = ((PF2_IOM6_CH0 & 0x0020) != 0);// V37X3361Y LAT 2
				PBD_LATCH_STATUS( p1, p2, p3, p4, l_aft_bhd_str );
				WriteCOMPOOL_C( SCP_CSBB_L_AFT_BHD_TEXT, l_aft_bhd_str, 2 );

				// left door
				E = ((PF2_IOM6_CH0 & 0x0040) != 0);// V37X3305Y OPN 1
				F = ((PF1_IOM6_CH0 & 0x0040) != 0);// V37X3306Y OPN 2
				G = ((PF1_IOM6_CH0 & 0x0001) != 0);// V37X3325Y FWD RDY 1
				H = ((PF1_IOM9_CH0 & 0x0001) != 0);// V37X3326Y FWD RDY 2
				I = ((PF2_IOM6_CH0 & 0x0001) != 0);// V37X3327Y FWD RDY 3
				J = ((PF1_IOM6_CH0 & 0x0002) != 0);// V37X3355Y AFT RDY 1
				K = ((PF1_IOM9_CH0 & 0x0002) != 0);// V37X3356Y AFT RDY 2
				L = ((PF2_IOM6_CH0 & 0x0002) != 0);// V37X3357Y AFT RDY 3
				M = ((PF2_IOM6_CH0 & 0x0800) != 0);// V37X3307Y CLS 1
				N = ((PF1_IOM6_CH0 & 0x0800) != 0);// V37X3308Y CLS 2
				p1 = E && F;
				p2 = (G && H) || (H && I) || (G && I);
				p3 = (J && K) || (K && L) || (J && L);
				p4 = M && N;
				PBD_DOOR_STATUS( p1, p2, p3, p4, l_door_str );
				WriteCOMPOOL_C( SCP_CSBB_R_DOOR_TEXT, l_door_str, 3 );
			}

			// TODO latch validity

			//// PBD talkback
			SSB_OPEN_CLOSE_COMPLETE = 0;
			if (!strcmp( cl_5_8_str, "OP" ) && !strcmp( cl_9_12_str, "OP" ) && !strcmp( cl_1_4_str, "OP" ) && !strcmp( cl_13_16_str, "OP" ) &&
				!strcmp( r_fwd_bhd_str, "OP" ) && !strcmp( r_aft_bhd_str, "OP" ) && !strcmp( l_fwd_bhd_str, "OP" ) && !strcmp( l_aft_bhd_str, "OP" ) &&
				!strcmp( r_door_str, " OP" ) && !strcmp( l_door_str, " OP" ))
			{
				SSB_OPEN_CLOSE_COMPLETE |= 1;

				if (SSB_OPEN_CLOSE_COMPLETE != 1)
				{
					//CSBB_PBD_OUTPUT_INDICATOR = 1;
				}

				SSB_OPEN_CLOSE_COMPLETE = 1;
			}
			else
			{
				if (!strcmp( cl_5_8_str, "CL" ) && !strcmp( cl_9_12_str, "CL" ) && !strcmp( cl_1_4_str, "CL" ) && !strcmp( cl_13_16_str, "CL" ) &&
					!strcmp( r_fwd_bhd_str, "CL" ) && !strcmp( r_aft_bhd_str, "CL" ) && !strcmp( l_fwd_bhd_str, "CL" ) && !strcmp( l_aft_bhd_str, "CL" ) &&
					!strcmp( r_door_str, " CL" ) && !strcmp( l_door_str, " CL" ))
				{
					SSB_OPEN_CLOSE_COMPLETE |= 2;

					if (SSB_OPEN_CLOSE_COMPLETE != 2)
					{
						//CSBB_PBD_OUTPUT_INDICATOR = 1;
					}

					SSB_OPEN_CLOSE_COMPLETE = 2;
				}
				else
				{
					if (SSB_OPEN_CLOSE_COMPLETE != 0)
					{
						//CSBB_PBD_OUTPUT_INDICATOR = 1;
					}
				}
			}

			if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 0)
			{
				// TODO allow OPS/Mode transitions
				MODE_SELECTION();
			}
			else
			{
				// TODO inhibit OPS/Mode transitions

				if ((ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG ) == 1) && (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) == 1))
				{
					SSB_PREVIOUS_SWITCH_POS = ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC );

					// auto open/close sequence
					do
					{
						SSB_PBD_MORE_WORK_IND = false;

						if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
						{
							// open feedback
							if (SSB_CURRENT_LATCH_DOOR_POINTER == 0)
							{
								SSB_CURRENT_LATCH_DOOR_POINTER = 1;
							}

							bool A;
							bool B;
							bool C;
							bool D;
							switch (SSB_CURRENT_LATCH_DOOR_POINTER)
							{
								case 1:// CL 5-8, 9-12
									A = ((PF1_IOM9_CH0 & 0x0010) != 0);// V37X3390Y REL 1
									B = ((PF2_IOM9_CH0 & 0x0010) != 0);// V37X3391Y REL 2
									C = ((PF1_IOM9_CH0 & 0x0080) != 0);// V37X3405Y REL 1
									D = ((PF2_IOM9_CH0 & 0x0080) != 0);// V37X3406Y REL 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 2:// CL 1-4, 13-16
									A = ((PF1_IOM9_CH0 & 0x0004) != 0);// V37X3380Y REL 1
									B = ((PF2_IOM9_CH0 & 0x0004) != 0);// V37X3381Y REL 2
									C = ((PF2_IOM9_CH0 & 0x0200) != 0);// V37X3415Y REL 1
									D = ((PF1_IOM9_CH0 & 0x0200) != 0);// V37X3416Y REL 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 3:// R FWD BHD, R AFT BHD
									A = ((PF1_IOM3_CH0 & 0x0004) != 0);// V37X3430Y REL 1
									B = ((PF2_IOM3_CH0 & 0x0004) != 0);// V37X3431Y REL 2
									C = ((PF2_IOM3_CH0 & 0x0010) != 0);// V37X3450Y REL 1
									D = ((PF1_IOM3_CH0 & 0x0010) != 0);// V37X3451Y REL 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 4:// R DOOR
									A = ((PF1_IOM3_CH0 & 0x0040) != 0);// V37X3300Y OPN 1
									B = ((PF2_IOM3_CH0 & 0x0040) != 0);// V37X3301Y OPN 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = A && B;
									break;
								case 5:// L FWD BHD, L AFT BHD
									A = ((PF1_IOM6_CH0 & 0x0004) != 0);// V37X3320Y REL 1
									B = ((PF2_IOM6_CH0 & 0x0004) != 0);// V37X3321Y REL 2
									C = ((PF1_IOM6_CH0 & 0x0010) != 0);// V37X3350Y REL 1
									D = ((PF2_IOM6_CH0 & 0x0010) != 0);// V37X3351Y REL 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 6:// L DOOR
									A = ((PF2_IOM6_CH0 & 0x0040) != 0);// V37X3305Y OPN 1
									B = ((PF1_IOM6_CH0 & 0x0040) != 0);// V37X3306Y OPN 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = A && B;
									break;
							}
						}
						else
						{
							// close feedback
							if (SSB_CURRENT_LATCH_DOOR_POINTER == 0)
							{
								SSB_CURRENT_LATCH_DOOR_POINTER = 6;
							}

							bool A;
							bool B;
							bool C;
							bool D;
							bool E;
							bool F;
							switch (SSB_CURRENT_LATCH_DOOR_POINTER)
							{
								case 1:// CL 5-8, 9-12
									A = ((PF1_IOM9_CH0 & 0x0020) != 0);// V37X3395Y LAT 1
									B = ((PF2_IOM9_CH0 & 0x0020) != 0);// V37X3396Y LAT 2
									C = ((PF1_IOM9_CH0 & 0x0040) != 0);// V37X3400Y LAT 1
									D = ((PF2_IOM9_CH0 & 0x0040) != 0);// V37X3401Y LAT 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 2:// CL 1-4, 13-16
									A = ((PF1_IOM9_CH0 & 0x0008) != 0);// V37X3385Y LAT 1
									B = ((PF2_IOM9_CH0 & 0x0008) != 0);// V37X3386Y LAT 2
									C = ((PF2_IOM9_CH0 & 0x0100) != 0);// V37X3410Y LAT 1
									D = ((PF1_IOM9_CH0 & 0x0100) != 0);// V37X3411Y LAT 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 3:// R FWD BHD, R AFT BHD
									A = ((PF1_IOM3_CH0 & 0x0008) != 0);// V37X3440Y LAT 1
									B = ((PF2_IOM3_CH0 & 0x0008) != 0);// V37X3441Y LAT 2
									C = ((PF2_IOM3_CH0 & 0x0020) != 0);// V37X3460Y LAT 1
									D = ((PF1_IOM3_CH0 & 0x0020) != 0);// V37X3461Y LAT 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 4:// R DOOR
									A = ((PF1_IOM3_CH0 & 0x0001) != 0);// V37X3435Y FWD RDY 1
									B = ((PF2_IOM3_CH0 & 0x0001) != 0);// V37X3436Y FWD RDY 2
									C = ((PF2_IOM9_CH0 & 0x0001) != 0);// V37X3437Y FWD RDY 3
									D = ((PF1_IOM3_CH0 & 0x0002) != 0);// V37X3455Y AFT RDY 1
									E = ((PF2_IOM3_CH0 & 0x0002) != 0);// V37X3456Y AFT RDY 2
									F = ((PF2_IOM9_CH0 & 0x0002) != 0);// V37X3457Y AFT RDY 3
									//G = ((PF1_IOM3_CH0 & 0x0400) != 0);// V37X3302Y CLS 1
									//H = ((PF2_IOM3_CH0 & 0x0400) != 0);// V37X3303Y CLS 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = ((A && B) || (A && C) || (B && C)) && ((D && E) || (D && F) || (E && F)) /*&& (G && H)*/;
									break;
								case 5:// L FWD BHD, L AFT BHD
									A = ((PF1_IOM6_CH0 & 0x0008) != 0);// V37X3330Y LAT 1
									B = ((PF2_IOM6_CH0 & 0x0008) != 0);// V37X3331Y LAT 2
									C = ((PF1_IOM6_CH0 & 0x0020) != 0);// V37X3360Y LAT 1
									D = ((PF2_IOM6_CH0 & 0x0020) != 0);// V37X3361Y LAT 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = (A && B) && (C && D);
									break;
								case 6:// L DOOR
									A = ((PF1_IOM6_CH0 & 0x0001) != 0);// V37X3325Y FWD RDY 1
									B = ((PF1_IOM9_CH0 & 0x0001) != 0);// V37X3326Y FWD RDY 2
									C = ((PF2_IOM6_CH0 & 0x0001) != 0);// V37X3327Y FWD RDY 3
									D = ((PF1_IOM6_CH0 & 0x0002) != 0);// V37X3355Y AFT RDY 1
									E = ((PF1_IOM9_CH0 & 0x0002) != 0);// V37X3356Y AFT RDY 2
									F = ((PF2_IOM6_CH0 & 0x0002) != 0);// V37X3357Y AFT RDY 3
									//G = ((PF2_IOM6_CH0 & 0x0800) != 0);// V37X3307Y CLS 1
									//H = ((PF1_IOM6_CH0 & 0x0800) != 0);// V37X3308Y CLS 2
									SSB_OPEN_CLOSE_FEEDBACK_INDIC = ((A && B) || (A && C) || (B && C)) && ((D && E) || (D && F) || (E && F)) /*&& (G && H)*/;
									break;
							}
						}

						if (SSB_OPEN_CLOSE_FEEDBACK_INDIC)
						{
							if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
							{
								if (SSB_CURRENT_LATCH_DOOR_POINTER == 6)// auto open complete
								{
									DISABLE_COMMANDS();
									WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, 0 );
									WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
									// TODO pbd display update indicator on
								}
								else
								{
									SSB_CURRENT_LATCH_DOOR_POINTER++;
									SSB_PBD_MORE_WORK_IND = true;
								}
							}
							else
							{
								if (SSB_CURRENT_LATCH_DOOR_POINTER == 1)// auto close complete
								{
									DISABLE_COMMANDS();
									WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, 0 );
									WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, 0 );
									// TODO pbd display update indicator on
								}
								else
								{
									SSB_CURRENT_LATCH_DOOR_POINTER--;
									SSB_PBD_MORE_WORK_IND = true;
								}
							}
						}
						else
						{
							if (SSB_COMMANDS_ENABLED_ARRAY[SSB_CURRENT_LATCH_DOOR_POINTER - 1][ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) - 1] == 0)// commands enabled array
							{
								if (1)// TODO commcn pbd fail not on
								{
									// enable commands
									switch (SSB_CURRENT_LATCH_DOOR_POINTER)
									{
										case 1:// CL 5-8, 9-12
											if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
											{
												CSBB_PF01_OUTPUT_2 &= !0x0020;// 5-8 CL 1
												CSBB_PF02_OUTPUT_2 &= !0x0020;// 5-8 CL 2
												CSBB_PF01_OUTPUT_2 &= !0x0080;// 9-12 CL 1
												CSBB_PF02_OUTPUT_2 &= !0x0080;// 9-12 CL 2
												CSBB_PF01_OUTPUT_2 |= 0x0010;// 5-8 OP 1
												CSBB_PF02_OUTPUT_2 |= 0x0010;// 5-8 OP 2
												CSBB_PF01_OUTPUT_2 |= 0x0040;// 9-12 OP 1
												CSBB_PF02_OUTPUT_2 |= 0x0040;// 9-12 OP 2
											}
											else
											{
												CSBB_PF01_OUTPUT_2 &= !0x0010;// 5-8 OP 1
												CSBB_PF02_OUTPUT_2 &= !0x0010;// 5-8 OP 2
												CSBB_PF01_OUTPUT_2 &= !0x0040;// 9-12 OP 1
												CSBB_PF02_OUTPUT_2 &= !0x0040;// 9-12 OP 2
												CSBB_PF01_OUTPUT_2 |= 0x0020;// 5-8 CL 1
												CSBB_PF02_OUTPUT_2 |= 0x0020;// 5-8 CL 2
												CSBB_PF01_OUTPUT_2 |= 0x0080;// 9-12 CL 1
												CSBB_PF02_OUTPUT_2 |= 0x0080;// 9-12 CL 2
											}
											break;
										case 2:// CL 1-4, 13-16
											if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
											{
												CSBB_PF01_OUTPUT_2 &= !0x0008;// 1-4 CL 1
												CSBB_PF02_OUTPUT_2 &= !0x0008;// 1-4 CL 2
												CSBB_PF02_OUTPUT_2 &= !0x0200;// 13-16 CL 1
												CSBB_PF01_OUTPUT_2 &= !0x0200;// 13-16 CL 2
												CSBB_PF01_OUTPUT_2 |= 0x0004;// 1-4 OP 1
												CSBB_PF02_OUTPUT_2 |= 0x0004;// 1-4 OP 2
												CSBB_PF02_OUTPUT_2 |= 0x0100;// 13-16 OP 1
												CSBB_PF01_OUTPUT_2 |= 0x0100;// 13-16 OP 2
											}
											else
											{
												CSBB_PF01_OUTPUT_2 &= !0x0004;// 1-4 OP 1
												CSBB_PF02_OUTPUT_2 &= !0x0004;// 1-4 OP 2
												CSBB_PF02_OUTPUT_2 &= !0x0100;// 13-16 OP 1
												CSBB_PF01_OUTPUT_2 &= !0x0100;// 13-16 OP 2
												CSBB_PF01_OUTPUT_2 |= 0x0008;// 1-4 CL 1
												CSBB_PF02_OUTPUT_2 |= 0x0008;// 1-4 CL 2
												CSBB_PF02_OUTPUT_2 |= 0x0200;// 13-16 CL 1
												CSBB_PF01_OUTPUT_2 |= 0x0200;// 13-16 CL 2
											}
											break;
										case 3:// R FWD BHD, R AFT BHD
											if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
											{
												CSBB_PF01_OUTPUT_1 &= !0x0008;// R FWD CL 1
												CSBB_PF02_OUTPUT_1 &= !0x0008;// R FWD CL 2
												CSBB_PF02_OUTPUT_1 &= !0x0020;// R AFT CL 1
												CSBB_PF01_OUTPUT_1 &= !0x0020;// R AFT CL 2
												CSBB_PF01_OUTPUT_1 |= 0x0004;// R FWD OP 1
												CSBB_PF02_OUTPUT_1 |= 0x0004;// R FWD OP 2
												CSBB_PF02_OUTPUT_1 |= 0x0010;// R AFT OP 1
												CSBB_PF01_OUTPUT_1 |= 0x0010;// R AFT OP 2
											}
											else
											{
												CSBB_PF01_OUTPUT_1 &= !0x0004;// R FWD OP 1
												CSBB_PF02_OUTPUT_1 &= !0x0004;// R FWD OP 2
												CSBB_PF02_OUTPUT_1 &= !0x0010;// R AFT OP 1
												CSBB_PF01_OUTPUT_1 &= !0x0010;// R AFT OP 2
												CSBB_PF01_OUTPUT_1 |= 0x0008;// R FWD CL 1
												CSBB_PF02_OUTPUT_1 |= 0x0008;// R FWD CL 2
												CSBB_PF02_OUTPUT_1 |= 0x0020;// R AFT CL 1
												CSBB_PF01_OUTPUT_1 |= 0x0020;// R AFT CL 2
											}
											break;
										case 4:// R DOOR
											if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
											{
												CSBB_PF01_OUTPUT_1 &= !0x0002;// R CL 1
												CSBB_PF02_OUTPUT_1 &= !0x0002;// R CL 2
												CSBB_PF01_OUTPUT_1 |= 0x0001;// R OP 1
												CSBB_PF02_OUTPUT_1 |= 0x0001;// R OP 2
											}
											else
											{
												CSBB_PF01_OUTPUT_1 &= !0x0001;// R OP 1
												CSBB_PF02_OUTPUT_1 &= !0x0001;// R OP 2
												CSBB_PF01_OUTPUT_1 |= 0x0002;// R CL 1
												CSBB_PF02_OUTPUT_1 |= 0x0002;// R CL 2
											}
											break;
										case 5:// L FWD BHD, L AFT BHD
											if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
											{
												CSBB_PF01_OUTPUT_3 &= !0x0008;// L FWD CL 1
												CSBB_PF02_OUTPUT_3 &= !0x0008;// L FWD CL 2
												CSBB_PF01_OUTPUT_3 &= !0x0020;// L AFT CL 1
												CSBB_PF02_OUTPUT_3 &= !0x0020;// L AFT CL 2
												CSBB_PF01_OUTPUT_3 |= 0x0004;// L FWD OP 1
												CSBB_PF02_OUTPUT_3 |= 0x0004;// L FWD OP 2
												CSBB_PF01_OUTPUT_3 |= 0x0010;// L AFT OP 1
												CSBB_PF02_OUTPUT_3 |= 0x0010;// L AFT OP 2
											}
											else
											{
												CSBB_PF01_OUTPUT_3 &= !0x0004;// L FWD OP 1
												CSBB_PF02_OUTPUT_3 &= !0x0004;// L FWD OP 2
												CSBB_PF01_OUTPUT_3 &= !0x0010;// L AFT OP 1
												CSBB_PF02_OUTPUT_3 &= !0x0010;// L AFT OP 2
												CSBB_PF01_OUTPUT_3 |= 0x0008;// L FWD CL 1
												CSBB_PF02_OUTPUT_3 |= 0x0008;// L FWD CL 2
												CSBB_PF01_OUTPUT_3 |= 0x0020;// L AFT CL 1
												CSBB_PF02_OUTPUT_3 |= 0x0020;// L AFT CL 2
											}
											break;
										case 6:// L DOOR
											if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
											{
												CSBB_PF02_OUTPUT_3 &= !0x0002;// L CL 1
												CSBB_PF01_OUTPUT_3 &= !0x0002;// L CL 2
												CSBB_PF02_OUTPUT_3 |= 0x0001;// L OP 1
												CSBB_PF01_OUTPUT_3 |= 0x0001;// L OP 2
											}
											else
											{
												CSBB_PF02_OUTPUT_3 &= !0x0001;// L OP 1
												CSBB_PF01_OUTPUT_3 &= !0x0001;// L OP 2
												CSBB_PF02_OUTPUT_3 |= 0x0002;// L CL 1
												CSBB_PF01_OUTPUT_3 |= 0x0002;// L CL 2
											}
											break;
									}

									if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
									{
										SSB_COMMANDS_ENABLED_ARRAY[SSB_CURRENT_LATCH_DOOR_POINTER - 1][0] = 1;
										SSB_COMMANDS_ENABLED_ARRAY[SSB_CURRENT_LATCH_DOOR_POINTER - 1][1] = 0;
									}
									else
									{
										SSB_COMMANDS_ENABLED_ARRAY[SSB_CURRENT_LATCH_DOOR_POINTER - 1][0] = 0;
										SSB_COMMANDS_ENABLED_ARRAY[SSB_CURRENT_LATCH_DOOR_POINTER - 1][1] = 1;
									}

									SSB_LATCH_DOOR_EXPIR_TIME = simt + SSB_TIMER_CONSTANTS_ARRAY[SSB_CURRENT_LATCH_DOOR_POINTER - 1];// TODO confirm logic
									//CSBB_PBD_OUTPUT_INDICATOR = 1;
								}
							}
							else
							{
								if (simt >= SSB_LATCH_DOOR_EXPIR_TIME)// fail condition
								{
									bool A;
									bool B;
									bool C;
									bool D;
									if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
									{
										// set open fail indicators
										switch (SSB_CURRENT_LATCH_DOOR_POINTER)
										{
											case 1:// CL 5-8, 9-12
												A = ((PF1_IOM9_CH0 & 0x0010) != 0);// V37X3390Y REL 1
												B = ((PF2_IOM9_CH0 & 0x0010) != 0);// V37X3391Y REL 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0001 );
												}

												C = ((PF1_IOM9_CH0 & 0x0080) != 0);// V37X3405Y REL 1
												D = ((PF2_IOM9_CH0 & 0x0080) != 0);// V37X3406Y REL 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0002 );
												}
												break;
											case 2:// CL 1-4, 13-16
												A = ((PF1_IOM9_CH0 & 0x0004) != 0);// V37X3380Y REL 1
												B = ((PF2_IOM9_CH0 & 0x0004) != 0);// V37X3381Y REL 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0004 );
												}

												C = ((PF2_IOM9_CH0 & 0x0200) != 0);// V37X3415Y REL 1
												D = ((PF1_IOM9_CH0 & 0x0200) != 0);// V37X3416Y REL 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0008 );
												}
												break;
											case 3:// R FWD BHD, R AFT BHD
												A = ((PF1_IOM3_CH0 & 0x0004) != 0);// V37X3430Y REL 1
												B = ((PF2_IOM3_CH0 & 0x0004) != 0);// V37X3431Y REL 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0010 );
												}

												C = ((PF2_IOM3_CH0 & 0x0010) != 0);// V37X3450Y REL 1
												D = ((PF1_IOM3_CH0 & 0x0010) != 0);// V37X3451Y REL 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0020 );
												}
												break;
											case 4:// R DOOR
												WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0040 );
												break;
											case 5:// L FWD BHD, L AFT BHD
												A = ((PF1_IOM6_CH0 & 0x0004) != 0);// V37X3320Y REL 1
												B = ((PF2_IOM6_CH0 & 0x0004) != 0);// V37X3321Y REL 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0080 );
												}

												C = ((PF1_IOM6_CH0 & 0x0010) != 0);// V37X3350Y REL 1
												D = ((PF2_IOM6_CH0 & 0x0010) != 0);// V37X3351Y REL 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0100 );
												}
												break;
											case 6:// L DOOR
												WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) | 0x0200 );
												break;
										}
									}
									else
									{
										// set close fail indicators
										switch (SSB_CURRENT_LATCH_DOOR_POINTER)
										{
											case 1:// CL 5-8, 9-12
												A = ((PF1_IOM9_CH0 & 0x0020) != 0);// V37X3395Y LAT 1
												B = ((PF2_IOM9_CH0 & 0x0020) != 0);// V37X3396Y LAT 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0001 );
												}

												C = ((PF1_IOM9_CH0 & 0x0040) != 0);// V37X3400Y LAT 1
												D = ((PF2_IOM9_CH0 & 0x0040) != 0);// V37X3401Y LAT 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0002 );
												}
												break;
											case 2:// CL 1-4, 13-16
												A = ((PF1_IOM9_CH0 & 0x0008) != 0);// V37X3385Y LAT 1
												B = ((PF2_IOM9_CH0 & 0x0008) != 0);// V37X3386Y LAT 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0004 );
												}

												C = ((PF2_IOM9_CH0 & 0x0100) != 0);// V37X3410Y LAT 1
												D = ((PF1_IOM9_CH0 & 0x0100) != 0);// V37X3411Y LAT 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0008 );
												}
												break;
											case 3:// R FWD BHD, R AFT BHD
												A = ((PF1_IOM3_CH0 & 0x0008) != 0);// V37X3440Y LAT 1
												B = ((PF2_IOM3_CH0 & 0x0008) != 0);// V37X3441Y LAT 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0010 );
												}

												C = ((PF2_IOM3_CH0 & 0x0020) != 0);// V37X3460Y LAT 1
												D = ((PF1_IOM3_CH0 & 0x0020) != 0);// V37X3461Y LAT 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0020 );
												}
												break;
											case 4:// R DOOR
												WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0040 );
												break;
											case 5:// L FWD BHD, L AFT BHD
												A = ((PF1_IOM6_CH0 & 0x0008) != 0);// V37X3330Y LAT 1
												B = ((PF2_IOM6_CH0 & 0x0008) != 0);// V37X3331Y LAT 2
												if (!(A && B))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0080 );
												}

												C = ((PF1_IOM6_CH0 & 0x0020) != 0);// V37X3360Y LAT 1
												D = ((PF2_IOM6_CH0 & 0x0020) != 0);// V37X3361Y LAT 2
												if (!(C && D))
												{
													WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0100 );
												}
												break;
											case 6:// L DOOR
												WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) | 0x0200 );
												break;
										}
									}
									// TODO enable common pdb fail ind for annun
									DISABLE_UNVERIFIED_COMMANDS();
								}
							}
						}
					} while (SSB_PBD_MORE_WORK_IND);
				}
				else
				{
					if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG ) == 1) && (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) != 0))
					{
						// manual sequence
						if (ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC ) == 1)
						{
							// manual open
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0008) != 0)
							{
								// TODO disable close and ena open CL 5-8
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0010) != 0)
							{
								// TODO disable close and ena open CL 9-12
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0020) != 0)
							{
								// TODO disable close and ena open CL 1-4
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0040) != 0)
							{
								// TODO disable close and ena open CL 13-16
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0080) != 0)
							{
								// TODO disable close and ena open R FWD BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0100) != 0)
							{
								// TODO disable close and ena open R AFT BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0200) != 0)
							{
								// TODO disable close and ena open R DOOR
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0400) != 0)
							{
								// TODO disable close and ena open L FWD BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0800) != 0)
							{
								// TODO disable close and ena open L AFT BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x1000) != 0)
							{
								// TODO disable close and ena open L DOOR
							}
						}
						else
						{
							// manual close
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0008) != 0)
							{
								// TODO disable open and ena close CL 5-8
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0010) != 0)
							{
								// TODO disable open and ena close CL 9-12
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0020) != 0)
							{
								// TODO disable open and ena close CL 1-4
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0040) != 0)
							{
								// TODO disable open and ena close CL 13-16
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0080) != 0)
							{
								// TODO disable open and ena close R FWD BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0100) != 0)
							{
								// TODO disable open and ena close R AFT BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0200) != 0)
							{
								// TODO disable open and ena close R DOOR
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0400) != 0)
							{
								// TODO disable open and ena close L FWD BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x0800) != 0)
							{
								// TODO disable open and ena close L AFT BHD
							}
							if ((ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) & 0x1000) != 0)
							{
								// TODO disable open and ena close L DOOR
							}
						}

						SSB_PREVIOUS_SWITCH_POS = ReadCOMPOOL_IS( SCP_CSBB_CONTROL_SWITCH_POS_INDIC );
						//CSBB_PBD_OUTPUT_INDICATOR = 1;
					}
					else
					{
						MODE_SELECTION();
					}
				}
			}

			CSSB_FULL_EX_FLAG = false;
		}

		// TODO outputs
		//if (CSBB_PBD_OUTPUT_INDICATOR == 1)
		{
			if (SSB_OPEN_CLOSE_COMPLETE & 1)
			{
				WriteCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA ) | 0x0001 );
				WriteCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA ) | 0x0001 );
			}
			if (SSB_OPEN_CLOSE_COMPLETE & 2)
			{
				WriteCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA ) | 0x0002 );
				WriteCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA ) | 0x0002 );
			}

			WriteCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM2_CH0_DATA ) | CSBB_PF01_OUTPUT_1 );
			WriteCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM7_CH0_DATA ) | CSBB_PF01_OUTPUT_2 );
			WriteCOMPOOL_IS( SCP_PF1_IOM14_CH0_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM14_CH0_DATA ) | CSBB_PF01_OUTPUT_3 );
			WriteCOMPOOL_IS( SCP_PF1_IOM14_CH2_DATA, ReadCOMPOOL_IS( SCP_PF1_IOM14_CH2_DATA ) | CSBB_PF01_OUTPUT_4 );

			WriteCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM2_CH0_DATA ) | CSBB_PF02_OUTPUT_1 );
			WriteCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM7_CH0_DATA ) | CSBB_PF02_OUTPUT_2 );
			WriteCOMPOOL_IS( SCP_PF2_IOM14_CH0_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM14_CH0_DATA ) | CSBB_PF02_OUTPUT_3 );
			WriteCOMPOOL_IS( SCP_PF2_IOM14_CH2_DATA, ReadCOMPOOL_IS( SCP_PF2_IOM14_CH2_DATA ) | CSBB_PF02_OUTPUT_4 );

			//CSBB_PBD_OUTPUT_INDICATOR = 0;
		}
		return;
	}

	void SSB_PL_BAY_DOORS::PBD_LATCH_STATUS( const bool p1, const bool p2, const bool p3, const bool p4, char* computedvalue ) const
	{
		strcpy( computedvalue, "?" );

		if (p1)
		{
			if (p2)
			{
				if (!p3 && !p4)
				{
					strcpy( computedvalue, "OP" );
				}
			}
			else
			{
				if (!p3 && !p4)
				{
					strcpy( computedvalue, "  " );
				}
			}
		}
		else
		{
			if (p2)
			{
				if (!p3 && !p4)
				{
					strcpy( computedvalue, "  " );
				}
			}
			else
			{
				if (p3)
				{
					if (p4)
					{
						strcpy( computedvalue, "CL" );
					}
					else
					{
						strcpy( computedvalue, "  " );
					}
				}
				else
				{
					strcpy( computedvalue, "  " );
				}
			}
		}
		return;
	}

	void SSB_PL_BAY_DOORS::PBD_DOOR_STATUS( const bool p1, const bool p2, const bool p3, const bool p4, char* computedvalue ) const
	{
		strcpy( computedvalue, " ?" );

		if (p1)
		{
			if (!p2 && !p3 && !p4)
			{
				strcpy( computedvalue, " OP" );
			}
		}
		else
		{
			if (p2)
			{
				if (p3)
				{
					if (p4)
					{
						strcpy( computedvalue, " CL" );
					}
					else
					{
						strcpy( computedvalue, "RDY" );
					}
				}
				else
				{
					if (!p4)
					{
						strcpy( computedvalue, "   " );
					}
				}
			}
			else
			{
				if (!p4)
				{
					strcpy( computedvalue, "   " );
				}
			}
		}
		return;
	}

	void SSB_PL_BAY_DOORS::MODE_SELECTION( void )
	{
		if (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) == 1)
		{
			// auto mode select
			if (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG ) == 1)
			{
				if ((SSB_CURRENT_LATCH_DOOR_POINTER != 0) && (SSB_PREVIOUS_SWITCH_POS != 0))// auto sequence has been initiated and previous switch position is not stop
				{
					DISABLE_UNVERIFIED_COMMANDS();
				}
			}
			else
			{
				if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG ) == 1)
				{
					DISABLE_COMMANDS();
					WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG, 0 );
				}

				WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, 1 );
				WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, 0 );
				// TODO set com pbd fail ind off
				SSB_CURRENT_LATCH_DOOR_POINTER = 0;
				//CSBB_PBD_OUTPUT_INDICATOR = 1;
			}
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) != 0)
			{
				// manual mode select
				if (ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG ) == 1)
				{
					if (SSB_PREVIOUS_SWITCH_POS != 0)
					{
						DISABLE_COMMANDS();
					}
				}
				else
				{
					if (ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG ) == 1)
					{
						DISABLE_COMMANDS();
						WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, 0 );
					}

					WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG, 1 );
					WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, 0 );
					WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, 0 );
					// TODO set com pbd fail ind off
					//CSBB_PBD_OUTPUT_INDICATOR = 1;
				}
			}
		}

		SSB_PREVIOUS_SWITCH_POS = 0;
		return;
	}

	void SSB_PL_BAY_DOORS::DISABLE_COMMANDS( void )
	{
		// TODO disable all cmds lch grp/door
		// TODO set cmd array 0
		//CSBB_PBD_OUTPUT_INDICATOR = 1;
		return;
	}

	void SSB_PL_BAY_DOORS::DISABLE_UNVERIFIED_COMMANDS( void )
	{
		bool A;
		bool B;
		bool C;
		bool D;
		if (SSB_PREVIOUS_SWITCH_POS == 1)
		{
			// disable unverified open commands
			switch (SSB_CURRENT_LATCH_DOOR_POINTER)
			{
				case 1:// CL 5-8, 9-12
					A = ((PF1_IOM9_CH0 & 0x0010) != 0);// V37X3390Y REL 1
					B = ((PF2_IOM9_CH0 & 0x0010) != 0);// V37X3391Y REL 2
					if (!(A && B))
					{
						// TODO disable open cmds CL 5-8
					}

					C = ((PF1_IOM9_CH0 & 0x0080) != 0);// V37X3405Y REL 1
					D = ((PF2_IOM9_CH0 & 0x0080) != 0);// V37X3406Y REL 2
					if (!(C && D))
					{
						// TODO disable open cmds CL 9-12
					}
					break;
				case 2:// CL 1-4, 13-16
					A = ((PF1_IOM9_CH0 & 0x0004) != 0);// V37X3380Y REL 1
					B = ((PF2_IOM9_CH0 & 0x0004) != 0);// V37X3381Y REL 2
					if (!(A && B))
					{
						// TODO disable open cmds CL 1-4
					}

					C = ((PF2_IOM9_CH0 & 0x0200) != 0);// V37X3415Y REL 1
					D = ((PF1_IOM9_CH0 & 0x0200) != 0);// V37X3416Y REL 2
					if (!(C && D))
					{
						// TODO disable open cmds CL 13-16
					}
					break;
				case 3:// R FWD BHD, R AFT BHD
					A = ((PF1_IOM3_CH0 & 0x0004) != 0);// V37X3430Y REL 1
					B = ((PF2_IOM3_CH0 & 0x0004) != 0);// V37X3431Y REL 2
					if (!(A && B))
					{
						// TODO disable open cmds R FWD BHD
					}

					C = ((PF2_IOM3_CH0 & 0x0010) != 0);// V37X3450Y REL 1
					D = ((PF1_IOM3_CH0 & 0x0010) != 0);// V37X3451Y REL 2
					if (!(C && D))
					{
						// TODO disable open cmds R AFT BHD
					}
					break;
				case 4:// R DOOR
					// TODO disable open cmds R DOOR
					break;
				case 5:// L FWD BHD, L AFT BHD
					A = ((PF1_IOM6_CH0 & 0x0004) != 0);// V37X3320Y REL 1
					B = ((PF2_IOM6_CH0 & 0x0004) != 0);// V37X3321Y REL 2
					if (!(A && B))
					{
						// TODO disable open cmds L FWD BHD
					}

					C = ((PF1_IOM6_CH0 & 0x0010) != 0);// V37X3350Y REL 1
					D = ((PF2_IOM6_CH0 & 0x0010) != 0);// V37X3351Y REL 2
					if (!(C && D))
					{
						// TODO disable open cmds L AFT BHD
					}
					break;
				case 6:// L DOOR
					// TODO disable open cmds L DOOR
					break;
			}
		}
		else
		{
			// disable unverified close commands
			switch (SSB_CURRENT_LATCH_DOOR_POINTER)
			{
				case 1:// CL 5-8, 9-12
					A = ((PF1_IOM9_CH0 & 0x0020) != 0);// V37X3395Y LAT 1
					B = ((PF2_IOM9_CH0 & 0x0020) != 0);// V37X3396Y LAT 2
					if (!(A && B))
					{
						// TODO disable close cmds CL 5-8
					}

					C = ((PF1_IOM9_CH0 & 0x0040) != 0);// V37X3400Y LAT 1
					D = ((PF2_IOM9_CH0 & 0x0040) != 0);// V37X3401Y LAT 2
					if (!(C && D))
					{
						// TODO disable close cmds CL 9-12
					}
					break;
				case 2:// CL 1-4, 13-16
					A = ((PF1_IOM9_CH0 & 0x0008) != 0);// V37X3385Y LAT 1
					B = ((PF2_IOM9_CH0 & 0x0008) != 0);// V37X3386Y LAT 2
					if (!(A && B))
					{
						// TODO disable close cmds CL 1-4
					}

					C = ((PF2_IOM9_CH0 & 0x0100) != 0);// V37X3410Y LAT 1
					D = ((PF1_IOM9_CH0 & 0x0100) != 0);// V37X3411Y LAT 2
					if (!(C && D))
					{
						// TODO disable close cmds CL 13-16
					}
					break;
				case 3:// R FWD BHD, R AFT BHD
					A = ((PF1_IOM3_CH0 & 0x0008) != 0);// V37X3440Y LAT 1
					B = ((PF2_IOM3_CH0 & 0x0008) != 0);// V37X3441Y LAT 2
					if (!(A && B))
					{
						// TODO disable close cmds R FWD BHD
					}

					C = ((PF2_IOM3_CH0 & 0x0020) != 0);// V37X3460Y LAT 1
					D = ((PF1_IOM3_CH0 & 0x0020) != 0);// V37X3461Y LAT 2
					if (!(C && D))
					{
						// TODO disable close cmds R AFT BHD
					}
					break;
				case 4:// R DOOR
					// TODO disable close cmds R DOOR
					break;
				case 5:// L FWD BHD, L AFT BHD
					A = ((PF1_IOM6_CH0 & 0x0008) != 0);// V37X3330Y LAT 1
					B = ((PF2_IOM6_CH0 & 0x0008) != 0);// V37X3331Y LAT 2
					if (!(A && B))
					{
						// TODO disable close cmds L FWD BHD
					}

					C = ((PF1_IOM6_CH0 & 0x0020) != 0);// V37X3360Y LAT 1
					D = ((PF2_IOM6_CH0 & 0x0020) != 0);// V37X3361Y LAT 2
					if (!(C && D))
					{
						// TODO disable close cmds L AFT BHD
					}
					break;
				case 6:// L DOOR
					// TODO disable close cmds L DOOR
					break;
			}
		}

		// TODO set cmds array off
		
		//CSBB_PBD_OUTPUT_INDICATOR = 1;
		return;
	}

	bool SSB_PL_BAY_DOORS::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 202:
				WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x0002 );
				WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, 0 );
				WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, 0 );
				return true;
			default:
				WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, 0x0002 );
				return false;
		}
	}
}
