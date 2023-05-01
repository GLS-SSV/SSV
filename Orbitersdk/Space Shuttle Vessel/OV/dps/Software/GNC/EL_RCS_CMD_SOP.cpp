#include "EL_RCS_CMD_SOP.h"


namespace dps
{
	constexpr double FRCS_DUMP_START_VEL = 26000.0;// HACK I-LOAD no source (V99U9599C) [fps]

	unsigned short RCS_CYC1 = 4;// RCS DELAY 1 CYCLE COUNTER (V97U6214C) [1]
	unsigned short RCS_CYC2 = 6;// RCS DELAY 2 CYCLE COUNTER (V97U6215C) [1]


	EL_RCS_CMD_SOP::EL_RCS_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "EL_RCS_CMD_SOP" ),
		step40ms(0.0), step80ms(0.0)
	{
		
		for (int i = 0; i < 44; i++) RCS_ON[i] = false;

		DUMP0 = false;
		DUMP1 = false;
		DUMP2 = false;
		DELAY1 = false;
		DELAY2 = false;
		return;
	}

	EL_RCS_CMD_SOP::~EL_RCS_CMD_SOP( void )
	{
		return;
	}

	void EL_RCS_CMD_SOP::FRCS( double dt )
	{
		float FWD_RCS_TTG_SF = 0.0;

		RCS_ON[3] = false;// F1L
		RCS_ON[4] = false;// F3L
		RCS_ON[5] = false;// F2R
		RCS_ON[6] = false;// F4R

		if ((ReadCOMPOOL_SS( SCP_VE ) <= FRCS_DUMP_START_VEL) && (ReadCOMPOOL_IS( SCP_FWD_RCS_DUMP_ENABLE ) == 1))
		{
			float FWD_RCS_DUMP_CNTR = ReadCOMPOOL_SS( SCP_FWD_RCS_DUMP_CNTR );
			if ((FWD_RCS_DUMP_CNTR <= ReadCOMPOOL_SS( SCP_FWD_RCS_DUMP_DURATION )) && (ReadCOMPOOL_IS( SCP_MM ) == 304))
			{
				// dump
				double timer_dt = 0.0;

				unsigned short JETGD[4];// Jet-good discrete array (F1L, F3L, F2R, F4R)
				JETGD[0] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_FWD, 2, 16 );
				JETGD[1] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_FWD, 14, 16 );
				JETGD[2] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_FWD, 6, 16 );
				JETGD[3] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_FWD, 9, 16 );

				if ((JETGD[0] == 0) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 1))
				{
					RCS_ON[4] = true;// F3L
					RCS_ON[5] = true;// F2R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 1) && (JETGD[1] == 0) && (JETGD[2] == 1) && (JETGD[3] == 1))
				{
					RCS_ON[3] = true;// F1L
					RCS_ON[5] = true;// F2R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 1) && (JETGD[1] == 1) && (JETGD[2] == 0) && (JETGD[3] == 1))
				{
					RCS_ON[3] = true;// F1L
					RCS_ON[6] = true;// F4R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 1) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 0))
				{
					RCS_ON[3] = true;// F1L
					RCS_ON[5] = true;// F2R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 0) && (JETGD[1] == 1) && (JETGD[2] == 0) && (JETGD[3] == 1))
				{
					RCS_ON[4] = true;// F3L
					RCS_ON[6] = true;// F4R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 0) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 0))
				{
					RCS_ON[4] = true;// F3L
					RCS_ON[5] = true;// F2R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 1) && (JETGD[1] == 0) && (JETGD[2] == 0) && (JETGD[3] == 1))
				{
					RCS_ON[3] = true;// F1L
					RCS_ON[6] = true;// F4R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 1) && (JETGD[1] == 0) && (JETGD[2] == 1) && (JETGD[3] == 0))
				{
					RCS_ON[3] = true;// F1L
					RCS_ON[5] = true;// F2R
					timer_dt = dt * 0.5;
					FWD_RCS_TTG_SF = 0.5;
				}
				else if ((JETGD[0] == 1) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 1))
				{
					RCS_ON[3] = true;// F1L
					RCS_ON[4] = true;// F3L
					RCS_ON[5] = true;// F2R
					RCS_ON[6] = true;// F4R
					timer_dt = dt;
					FWD_RCS_TTG_SF = 1.0;
				}

				FWD_RCS_DUMP_CNTR += static_cast<float>(timer_dt);

				WriteCOMPOOL_SS( SCP_FWD_RCS_DUMP_CNTR, FWD_RCS_DUMP_CNTR );
			}
			else
			{
				// auto dump end
				WriteCOMPOOL_IS( SCP_FWD_RCS_DUMP_ENABLE, 0 );
			}
		}
		WriteCOMPOOL_SS( SCP_FWD_RCS_TTG_SF, FWD_RCS_TTG_SF );
		return;
	}

	void EL_RCS_CMD_SOP::OnPostStep( double simt, double simdt, double mjd )
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

		bool RCS_ON_A[44];
		bool RCS_ON_B[44];

		// fwd rcs
		if (run80ms) FRCS( step80ms );

		// aft rcs
		if (run40ms)
		{
			// get DAP commands
			bool NEW_JON[44];
			for (auto& x : NEW_JON) x = false;
			NEW_JON[18] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 23, 28 );// L4L_ON
			NEW_JON[19] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 17, 28 );// L2L_ON
			NEW_JON[20] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 10, 28 );// L3L_ON
			NEW_JON[21] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 2, 28 );// L1L_ON
			NEW_JON[22] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 26, 28 );// R4R_ON
			NEW_JON[23] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 20, 28 );// R2R_ON
			NEW_JON[24] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 13, 28 );// R3R_ON
			NEW_JON[25] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 5, 28 );// R1R_ON
			NEW_JON[26] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 24, 28 );// L4U_ON
			NEW_JON[27] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 18, 28 );// L2U_ON
			NEW_JON[28] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 3, 28 );// L1U_ON
			NEW_JON[29] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 27, 28 );// R4U_ON
			NEW_JON[30] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 21, 28 );// R2U_ON
			NEW_JON[31] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 6, 28 );// R1U_ON
			NEW_JON[32] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 25, 28 );// L4D_ON
			NEW_JON[33] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 19, 28 );// L2D_ON
			NEW_JON[34] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 11, 28 );// L3D_ON
			NEW_JON[35] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 28, 28 );// R4D_ON
			NEW_JON[36] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 22, 28 );// R2D_ON
			NEW_JON[37] = ReadCOMPOOL_AIS( SCP_NEW_JONLIST_AFT, 14, 28 );// R3D_ON


			// TODO get values
			bool S_RCS_IGN = false;// ABORT RCS +X ON CMD (V90X8314X) [1]
			bool S_RCS_NULL20 = false;// 20 RCS NULL JETS ON CMD (V90X8317X) [1]
			bool AFT_MANIFOLD_12_JET_INH_FLAG = false;// (V90X8285X) [1]
			bool AFT_MANIFOLD_345_JET_INH_FLAG = false;// (V90X8286X) [1]
			bool IC_CPLT = false;// OMS/RCS_INTERCONNECT_COMPLETE_FLAG (V90X8282X) [1]
			bool RCS_12_ALL_JET_INHIBIT_FLAG = false;// (V90X8290X) [1]
			bool RCS_345_ALL_JET_INHIBIT_FLAG = false;// (V90X8291X) [1]
			if (S_RCS_IGN || S_RCS_NULL20 || DUMP0 || DUMP1 || DUMP2 || DELAY2)
			{
				// abort and DAP cmds

				// TODO
				// 123 361

				// C
				// inhibits RCS for I/C setup
				if (!RCS_12_ALL_JET_INHIBIT_FLAG || !RCS_345_ALL_JET_INHIBIT_FLAG)
				{
					// all avail 4.58-1a
				}
				else if (RCS_12_ALL_JET_INHIBIT_FLAG || RCS_345_ALL_JET_INHIBIT_FLAG)
				{
					//  4.58-1c
				
					// ALL_JET_INHIBIT_FLAG
					// OMS/RCS_INTERCONNECT_COMPLETE_FLAG
				}

				// D
				// inhibits RCS dumps, but to I/C failure
				if (!(RCS_12_ALL_JET_INHIBIT_FLAG && RCS_345_ALL_JET_INHIBIT_FLAG))
				{
					if (!AFT_MANIFOLD_12_JET_INH_FLAG || !AFT_MANIFOLD_345_JET_INH_FLAG)
					{
						// all avail 4.58-1b
					}
					else if (AFT_MANIFOLD_12_JET_INH_FLAG || AFT_MANIFOLD_345_JET_INH_FLAG)
					{
						//  4.58-1d
						//  4.58-1e
					}
				}

				// E
				// TODO +X (same as below?)
			
				// F
				// TODO ABT_20NULL (same as below?)








				bool ABT_JETS = S_RCS_NULL20;
				bool ABT_20NULL = S_RCS_NULL20;
				bool ABTXON = S_RCS_IGN;

				N_CYCLE( ABT_JETS, RCS_CYC1, OLDABT_JETS, NCYC1, DELAY1 );
				N_CYCLE( ABT_JETS, RCS_CYC2, OLDDELAY1, NCYC2, DELAY2 );

				// TODO detect startup
				if (0)
				{
					DUMP0 = S_RCS_IGN;
					DUMP1 = ABT_20NULL && DELAY1;
					DUMP2 = ABT_20NULL && DELAY2;
				}
				// TODO detect shutdown
				if (0)
				{
					DUMP0 = ((OLD20NULL && DELAY2) && OLLDXNULL) || ABTXON;// HACK docs not clear
					DUMP1 = OLD20NULL && DELAY1;
					DUMP2 = false;
				}

				// abort + DAP outputs
				//for (int i = 1; i <= 14; i++) RCS_ON[i - 1] = NEW_JON[i - 1];
				for (int i = 15; i <= 18; i++) RCS_ON[i - 1] = NEW_JON[i - 1] || DUMP0;
				for (int i = 19; i <= 26; i++) RCS_ON[i - 1] = NEW_JON[i - 1] || DUMP1;
				for (int i = 27; i <= 38; i++) RCS_ON[i - 1] = NEW_JON[i - 1] || DUMP2;
				// mirror DAP yaw cmds
				for (int i = 19; i <= 22; i++) if (NEW_JON[i - 1]) RCS_ON[i + 4 - 1] = 0;
				for (int i = 23; i <= 26; i++) if (NEW_JON[i - 1]) RCS_ON[i - 4 - 1] = 0;
				// mirror DAP roll/pitch cmds
				for (int i = 27; i <= 32; i++) if (NEW_JON[i - 1]) RCS_ON[i + 6 - 1] = 0;
				for (int i = 33; i <= 38; i++) if (NEW_JON[i - 1]) RCS_ON[i - 6 - 1] = 0;
			}
			else
			{
				// DAP cmds
				for (int i = 18; i <= 37; i++)
				{
					RCS_ON[i] = NEW_JON[i];
				}
			}

			// save flags for next cycle
			ABT_X_ON_LAST_PASS = S_RCS_IGN;
			ABT_20_NULL_LAST_PASS = S_RCS_NULL20;
			AFT_MANIFOLD_12_JET_INH_FLAG_LAST_PASS = AFT_MANIFOLD_12_JET_INH_FLAG;
			AFT_MANIFOLD_345_JET_INH_FLAG_LAST_PASS = AFT_MANIFOLD_345_JET_INH_FLAG;
			IC_CPT_LAST = IC_CPLT;
			RCS_12_ALL_JET_INHIBIT_FLAG_LAST_PASS = RCS_12_ALL_JET_INHIBIT_FLAG;
			RCS_345_ALL_JET_INHIBIT_FLAG_LAST_PASS = RCS_345_ALL_JET_INHIBIT_FLAG;
		}

		// output
		// TODO handle cmd output logic


		// generate A & B cmds
		for (int i = 0; i < 44; i++)
		{
			RCS_ON_A[i] = RCS_ON[i];
			RCS_ON_B[i] = RCS_ON[i];
		}

		// TODO save in COMPOOL

		// output to RJDs
		unsigned short wrd = 0;
		unsigned short cmd = 0;
		if (RCS_ON_A[3]) cmd |= 0x0002;// F1L A
		wrd = ReadCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[3]) cmd |= 0x0002;// F1L B
		wrd = ReadCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[5]) cmd |= 0x0002;// F2R A
		wrd = ReadCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[5]) cmd |= 0x0002;// F2R B
		wrd = ReadCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[6]) cmd |= 0x0001;// F4R A
		wrd = ReadCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[6]) cmd |= 0x0001;// F4R B
		wrd = ReadCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[4]) cmd |= 0x0002;// F3L A
		wrd = ReadCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[4]) cmd |= 0x0002;// F3L B
		wrd = ReadCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA ) & 0x000F;
		WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[17]) cmd |= 0x0001;// L1A A
		if (RCS_ON_A[21]) cmd |= 0x0002;// L1L A
		if (RCS_ON_A[28]) cmd |= 0x0004;// L1U A
		if (RCS_ON_A[15]) cmd |= 0x0008;// R1A A
		if (RCS_ON_A[25]) cmd |= 0x0010;// R1R A
		if (RCS_ON_A[31]) cmd |= 0x0020;// R1U A
		wrd = ReadCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA ) & 0x00FF;
		WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[17]) cmd |= 0x0001;// L1A B
		if (RCS_ON_B[21]) cmd |= 0x0002;// L1L B
		if (RCS_ON_B[28]) cmd |= 0x0004;// L1U B
		if (RCS_ON_B[15]) cmd |= 0x0008;// R1A B
		if (RCS_ON_B[25]) cmd |= 0x0010;// R1R B
		if (RCS_ON_B[31]) cmd |= 0x0020;// R1U B
		wrd = ReadCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA ) & 0x00FF;
		WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[16]) cmd |= 0x0001;// L3A A
		if (RCS_ON_A[20]) cmd |= 0x0002;// L3L A
		if (RCS_ON_A[34]) cmd |= 0x0004;// L3D A
		if (RCS_ON_A[14]) cmd |= 0x0008;// R3A A
		if (RCS_ON_A[24]) cmd |= 0x0010;// R3R A
		if (RCS_ON_A[37]) cmd |= 0x0020;// R3D A
		wrd = ReadCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA ) & 0x00FF;
		WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[16]) cmd |= 0x0001;// L3A B
		if (RCS_ON_B[20]) cmd |= 0x0002;// L3L B
		if (RCS_ON_B[34]) cmd |= 0x0004;// L3D B
		if (RCS_ON_B[14]) cmd |= 0x0008;// R3A B
		if (RCS_ON_B[24]) cmd |= 0x0010;// R3R B
		if (RCS_ON_B[37]) cmd |= 0x0020;// R3D B
		wrd = ReadCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA ) & 0x00FF;
		WriteCOMPOOL_IS( SCP_FA2_IOM10_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[19]) cmd |= 0x0001;// L2L A
		if (RCS_ON_A[27]) cmd |= 0x0002;// L2U A
		if (RCS_ON_A[33]) cmd |= 0x0004;// L2D A
		if (RCS_ON_A[23]) cmd |= 0x0008;// R2R A
		if (RCS_ON_A[30]) cmd |= 0x0010;// R2U A
		if (RCS_ON_A[36]) cmd |= 0x0020;// R2D A
		wrd = ReadCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA ) & 0x003F;
		WriteCOMPOOL_IS( SCP_FA3_IOM2_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[19]) cmd |= 0x0001;// L2L B
		if (RCS_ON_B[27]) cmd |= 0x0002;// L2U B
		if (RCS_ON_B[33]) cmd |= 0x0004;// L2D B
		if (RCS_ON_B[23]) cmd |= 0x0008;// R2R B
		if (RCS_ON_B[30]) cmd |= 0x0010;// R2U B
		if (RCS_ON_B[36]) cmd |= 0x0020;// R2D B
		wrd = ReadCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA ) & 0x003F;
		WriteCOMPOOL_IS( SCP_FA3_IOM10_CH0_DATA, cmd | wrd );

		cmd = 0;
		if (RCS_ON_A[18]) cmd |= 0x0001;// L4L A
		if (RCS_ON_A[26]) cmd |= 0x0002;// L4U A
		if (RCS_ON_A[32]) cmd |= 0x0004;// L4D A
		if (RCS_ON_A[22]) cmd |= 0x0008;// R4R A
		if (RCS_ON_A[29]) cmd |= 0x0010;// R4U A
		if (RCS_ON_A[35]) cmd |= 0x0020;// R4D A
		wrd = ReadCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA ) & 0x003F;
		WriteCOMPOOL_IS( SCP_FA4_IOM2_CH0_DATA, cmd | wrd );
		cmd = 0;
		if (RCS_ON_B[18]) cmd |= 0x0001;// L4L B
		if (RCS_ON_B[26]) cmd |= 0x0002;// L4U B
		if (RCS_ON_B[32]) cmd |= 0x0004;// L4D B
		if (RCS_ON_B[22]) cmd |= 0x0008;// R4R B
		if (RCS_ON_B[29]) cmd |= 0x0010;// R4U B
		if (RCS_ON_B[35]) cmd |= 0x0020;// R4D B
		wrd = ReadCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA ) & 0x003F;
		WriteCOMPOOL_IS( SCP_FA4_IOM10_CH0_DATA, cmd | wrd );


		for (int i = 0; i < 44; i++)
		{
			WriteCOMPOOL_AIS( SCP_RCS_ON_A, i + 1, RCS_ON_A[i], 44 );
			WriteCOMPOOL_AIS( SCP_RCS_ON_B, i + 1, RCS_ON_B[i], 44 );
		}


		// reset
		if (run40ms)
		{
			step40ms = 0.0;
			if (run80ms) step80ms = 0.0;
		}
		return;
	}

	void EL_RCS_CMD_SOP::N_CYCLE( const bool INPUT, const unsigned short NN, bool& LASTIN, unsigned short& N, bool& OUTPUT )
	{
		if (INPUT != LASTIN)
		{
			N = N + 1;

			if (N < NN)
			{
				// maintain previous state
				OUTPUT = LASTIN;
			}
			else
			{
				// change state
				OUTPUT = INPUT;
				LASTIN = INPUT;
				N = 0;
			}
		}
		return;
	}

	bool EL_RCS_CMD_SOP::OnParseLine( const char* keyword, const char* value )
	{
		return false;
	}

	void EL_RCS_CMD_SOP::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool EL_RCS_CMD_SOP::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 304:
			case 305:
				return true;
		}
		return false;
	}
}
