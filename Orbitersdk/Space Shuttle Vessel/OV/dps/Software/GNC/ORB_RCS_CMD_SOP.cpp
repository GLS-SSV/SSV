#include "ORB_RCS_CMD_SOP.h"


namespace dps
{
	ORB_RCS_CMD_SOP::ORB_RCS_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "ORB_RCS_CMD_SOP" ),
		step40ms(0.0), step80ms(0.0)
	{
		for (int i = 0; i < 44; i++) OLD_JON[i] = 0;
		return;
	}

	ORB_RCS_CMD_SOP::~ORB_RCS_CMD_SOP( void )
	{
		return;
	}

	void ORB_RCS_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
	{
		bool run40ms = false;
		bool run80ms = false;

		step40ms += simdt;
		if (step40ms >= 0.04)
		{
			// enable 40ms/25Hz logic
			run40ms = true;

			step80ms += step40ms;
			if (step80ms >= 0.08)
			{
				// enable 80ms/12.5Hz logic
				run80ms = true;
			}
		}

		if (run40ms)
		{
			unsigned short RCS_ON_A[44];
			unsigned short RCS_ON_B[44];

			// output for RJDs and RCS FDI
			unsigned short NEW_JON[44];
			NEW_JON[0] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 5, 16 );// F2F_ON
			NEW_JON[1] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 13, 16 );// F3F_ON
			NEW_JON[2] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 1, 16 );// F1F_ON
			NEW_JON[3] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 2, 16 );// F1L_ON
			NEW_JON[4] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 14, 16 );// F3L_ON
			NEW_JON[5] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 6, 16 );// F2R_ON
			NEW_JON[6] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 9, 16 );// F4R_ON
			NEW_JON[7] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 7, 16 );// F2U_ON
			NEW_JON[8] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 16, 16 );// F3U_ON
			NEW_JON[9] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 3, 16 );// F1U_ON
			NEW_JON[10] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 8, 16 );// F2D_ON
			NEW_JON[11] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 4, 16 );// F1D_ON
			NEW_JON[12] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 10, 16 );// F4D_ON
			NEW_JON[13] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 16, 16 );// F3D_ON
			NEW_JON[14] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 12, 28 );// R3A_ON
			NEW_JON[15] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 4, 28 );// R1A_ON
			NEW_JON[16] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 9, 28 );// L3A_ON
			NEW_JON[17] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 1, 28 );// L1A_ON
			NEW_JON[18] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 23, 28 );// L4L_ON
			NEW_JON[19] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 17, 28 );// L2L_ON
			NEW_JON[20] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 10, 28 );// L3L_ON
			NEW_JON[21] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 2, 28 );// L1L_ON
			NEW_JON[22] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 26, 28 );// R4R_ON
			NEW_JON[23] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 20, 28 );// R2R_ON
			NEW_JON[24] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 13, 28 );// R3R_ON
			NEW_JON[25] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 5, 28 );// R1R_ON
			NEW_JON[26] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 24, 28 );// L4U_ON
			NEW_JON[27] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 18, 28 );// L2U_ON
			NEW_JON[28] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 3, 28 );// L1U_ON
			NEW_JON[29] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 27, 28 );// R4U_ON
			NEW_JON[30] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 21, 28 );// R2U_ON
			NEW_JON[31] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 6, 28 );// R1U_ON
			NEW_JON[32] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 25, 28 );// L4D_ON
			NEW_JON[33] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 19, 28 );// L2D_ON
			NEW_JON[34] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 11, 28 );// L3D_ON
			NEW_JON[35] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 28, 28 );// R4D_ON
			NEW_JON[36] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 22, 28 );// R2D_ON
			NEW_JON[37] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 14, 28 );// R3D_ON
			NEW_JON[38] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 11, 16 );// F5L_ON
			NEW_JON[39] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_FWD, 12, 16 );// F5R_ON
			NEW_JON[40] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 8, 28 );// L5L_ON
			NEW_JON[41] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 15, 28 );// R5R_ON
			NEW_JON[42] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 7, 28 );// L5D_ON
			NEW_JON[43] = ReadCOMPOOL_AIS( SCP_NEW_JONLST_AFT, 16, 28 );// R5D_ON

			for (int i = 0; i < 44; i++)
			{
				RCS_ON_B[i] = NEW_JON[i];

				if (NEW_JON[i] == 0)
				{
					// off
					RCS_ON_A[i] = 1;
				}
				else
				{
					// on
					RCS_ON_A[i] = (ReadCOMPOOL_AIS( SCP_RCS_ON_A, i + 1, 44 ) == 0) ? 1 : 0;
				}


				WriteCOMPOOL_AIS( SCP_RCS_ON_A, i + 1, RCS_ON_A[i], 44 );
				WriteCOMPOOL_AIS( SCP_RCS_ON_B, i + 1, RCS_ON_B[i], 44 );
			}


			// output to RJDs
			unsigned short wrd = 0;
			unsigned short cmd = 0;
			cmd |= RCS_ON_A[2] << 0;// F1F A
			cmd |= RCS_ON_A[3] << 1;// F1L A
			cmd |= RCS_ON_A[9] << 2;// F1U A
			cmd |= RCS_ON_A[11] << 3;// F1D A
			wrd = ReadCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[2] << 0;// F1F B
			cmd |= RCS_ON_B[3] << 1;// F1L B
			cmd |= RCS_ON_B[9] << 2;// F1U B
			cmd |= RCS_ON_B[11] << 3;// F1D B
			wrd = ReadCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[0] << 0;// F2F A
			cmd |= RCS_ON_A[5] << 1;// F2R A
			cmd |= RCS_ON_A[7] << 2;// F2U A
			cmd |= RCS_ON_A[10] << 3;// F2D A
			wrd = ReadCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[0] << 0;// F2F B
			cmd |= RCS_ON_B[5] << 1;// F2R B
			cmd |= RCS_ON_B[7] << 2;// F2U B
			cmd |= RCS_ON_B[10] << 3;// F2D B
			wrd = ReadCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[6] << 0;// F4R A
			cmd |= RCS_ON_A[12] << 1;// F4D A
			cmd |= RCS_ON_A[38] << 2;// F5L A
			cmd |= RCS_ON_A[39] << 3;// F5R A
			wrd = ReadCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[6] << 0;// F4R B
			cmd |= RCS_ON_B[12] << 1;// F4D B
			cmd |= RCS_ON_B[38] << 2;// F5L B
			cmd |= RCS_ON_B[39] << 3;// F5R B
			wrd = ReadCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[1] << 0;// F3F A
			cmd |= RCS_ON_A[4] << 1;// F3L A
			cmd |= RCS_ON_A[8] << 2;// F3U A
			cmd |= RCS_ON_A[13] << 3;// F3D A
			wrd = ReadCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[1] << 0;// F3F B
			cmd |= RCS_ON_B[4] << 1;// F3L B
			cmd |= RCS_ON_B[8] << 2;// F3U B
			cmd |= RCS_ON_B[13] << 3;// F3D B
			wrd = ReadCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA ) & 0xFFF0;
			WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[17] << 0;// L1A A
			cmd |= RCS_ON_A[21] << 1;// L1L A
			cmd |= RCS_ON_A[28] << 2;// L1U A
			cmd |= RCS_ON_A[15] << 3;// R1A A
			cmd |= RCS_ON_A[25] << 4;// R1R A
			cmd |= RCS_ON_A[31] << 5;// R1U A
			cmd |= RCS_ON_A[42] << 6;// L5D A
			cmd |= RCS_ON_A[40] << 7;// L5L A
			wrd = ReadCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA ) & 0xFF00;
			WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[17] << 0;// L1A B
			cmd |= RCS_ON_B[21] << 1;// L1L B
			cmd |= RCS_ON_B[28] << 2;// L1U B
			cmd |= RCS_ON_B[15] << 3;// R1A B
			cmd |= RCS_ON_B[25] << 4;// R1R B
			cmd |= RCS_ON_B[31] << 5;// R1U B
			cmd |= RCS_ON_B[42] << 6;// L5D B
			cmd |= RCS_ON_B[40] << 7;// L5L B
			wrd = ReadCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA ) & 0xFF00;
			WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[16] << 0;// L3A A
			cmd |= RCS_ON_A[20] << 1;// L3L A
			cmd |= RCS_ON_A[34] << 2;// L3D A
			cmd |= RCS_ON_A[14] << 3;// R3A A
			cmd |= RCS_ON_A[24] << 4;// R3R A
			cmd |= RCS_ON_A[37] << 5;// R3D A
			cmd |= RCS_ON_A[41] << 6;// R5R A
			cmd |= RCS_ON_A[43] << 7;// R5D A
			wrd = ReadCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA ) & 0xFF00;
			WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[16] << 0;// L3A B
			cmd |= RCS_ON_B[20] << 1;// L3L B
			cmd |= RCS_ON_B[34] << 2;// L3D B
			cmd |= RCS_ON_B[14] << 3;// R3A B
			cmd |= RCS_ON_B[24] << 4;// R3R B
			cmd |= RCS_ON_B[37] << 5;// R3D B
			cmd |= RCS_ON_B[41] << 6;// R5R B
			cmd |= RCS_ON_B[43] << 7;// R5D B
			wrd = ReadCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA ) & 0xFF00;
			WriteCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[19] << 0;// L2L A
			cmd |= RCS_ON_A[27] << 1;// L2U A
			cmd |= RCS_ON_A[33] << 2;// L2D A
			cmd |= RCS_ON_A[23] << 3;// R2R A
			cmd |= RCS_ON_A[30] << 4;// R2U A
			cmd |= RCS_ON_A[36] << 5;// R2D A
			wrd = ReadCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA ) & 0xFFC0;
			WriteCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[19] << 0;// L2L B
			cmd |= RCS_ON_B[27] << 1;// L2U B
			cmd |= RCS_ON_B[33] << 2;// L2D B
			cmd |= RCS_ON_B[23] << 3;// R2R B
			cmd |= RCS_ON_B[30] << 4;// R2U B
			cmd |= RCS_ON_B[36] << 5;// R2D B
			wrd = ReadCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA ) & 0xFFC0;
			WriteCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA, cmd | wrd );

			cmd = 0;
			cmd |= RCS_ON_A[18] << 0;// L4L A
			cmd |= RCS_ON_A[26] << 1;// L4U A
			cmd |= RCS_ON_A[32] << 2;// L4D A
			cmd |= RCS_ON_A[22] << 3;// R4R A
			cmd |= RCS_ON_A[29] << 4;// R4U A
			cmd |= RCS_ON_A[35] << 5;// R4D A
			wrd = ReadCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA ) & 0xFFC0;
			WriteCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA, cmd | wrd );
			cmd = 0;
			cmd |= RCS_ON_B[18] << 0;// L4L B
			cmd |= RCS_ON_B[26] << 1;// L4U B
			cmd |= RCS_ON_B[32] << 2;// L4D B
			cmd |= RCS_ON_B[22] << 3;// R4R B
			cmd |= RCS_ON_B[29] << 4;// R4U B
			cmd |= RCS_ON_B[35] << 5;// R4D B
			wrd = ReadCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA ) & 0xFFC0;
			WriteCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA, cmd | wrd );

			step40ms = 0.0;


			if (run80ms)
			{
				// jet counters for orbit RMS/RCS CONN
				if ((ReadCOMPOOL_IS( SCP_LOMS_TO_AFT_RCS_PRESS_ENA ) == 0) && (ReadCOMPOOL_IS( SCP_ROMS_TO_AFT_RCS_PRESS_ENA ) == 0))
				{
					WriteCOMPOOL_IS( SCP_RCS_AFT_MN, 0 );
					WriteCOMPOOL_IS( SCP_RCS_AFT_VR, 0 );
					WriteCOMPOOL_IS( SCP_RCS_AFT_MN_ST, 0 );
				}
				else
				{
					for (int i = 15; i <= 38; i++)
					{
						if (!OLD_JON[i - 1] && NEW_JON[i - 1])
						{
							WriteCOMPOOL_IS( SCP_RCS_AFT_MN_ST, ReadCOMPOOL_IS( SCP_RCS_AFT_MN_ST ) + 1 );
							//WriteCOMPOOL_IS( SCP_RCS_AFT_MN, ReadCOMPOOL_IS( SCP_RCS_AFT_MN ) + 1 );// INFO repeated below
						}

						OLD_JON[i - 1] = NEW_JON[i - 1];
						WriteCOMPOOL_IS( SCP_RCS_AFT_MN, ReadCOMPOOL_IS( SCP_RCS_AFT_MN ) + NEW_JON[i - 1] );
					}

					for (int i = 41; i <= 44; i++)
					{
						WriteCOMPOOL_IS( SCP_RCS_AFT_VR, ReadCOMPOOL_IS( SCP_RCS_AFT_VR ) + NEW_JON[i - 1] );
					}
				}

				step80ms = 0.0;
			}
		}
		return;
	}

	bool ORB_RCS_CMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void ORB_RCS_CMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool ORB_RCS_CMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 201:
			case 202:
			case 801:
				return true;
		}
		return false;
	}
}
