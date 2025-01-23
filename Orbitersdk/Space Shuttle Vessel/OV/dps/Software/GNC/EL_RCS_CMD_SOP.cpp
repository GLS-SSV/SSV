#include "EL_RCS_CMD_SOP.h"


namespace dps
{
	// TODO I-LOADs
	constexpr double FRCS_DUMP_START_VEL = 26000.0;// HACK no source (V99U9599C) [fps]

	// consts
	unsigned short RCS_CYC1 = 4;// RCS DELAY 1 CYCLE COUNTER (V97U6214C) [1]
	unsigned short RCS_CYC2 = 6;// RCS DELAY 2 CYCLE COUNTER (V97U6215C) [1]


	EL_RCS_CMD_SOP::EL_RCS_CMD_SOP( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "EL_RCS_CMD_SOP" ),
		step40ms(0.0), step80ms(0.0)
	{
		
		for (int i = 0; i < 44; i++) RCS_ON[i] = false;
		for (auto& x : availablejets) x = 1;
		for (auto& x : availablejetsdump) x = 1;

		DUMP0 = 0;
		DUMP1 = 0;
		DUMP2 = 0;
		DELAY1 = 0;
		DELAY2 = 0;

		counter_RCS_12_ALL_JET_INHIBIT = 0;
		counter_RCS_345_ALL_JET_INHIBIT = 0;
		counter_AFT_MANIFOLD_12_JET_INH_X = 0;
		counter_AFT_MANIFOLD_12_JET_INH_Y = 0;
		counter_AFT_MANIFOLD_345_JET_INH_X = 0;
		counter_AFT_MANIFOLD_345_JET_INH_Y = 0;
		ena_RCS_12_ALL_JET_INHIBIT = false;
		ena_RCS_345_ALL_JET_INHIBIT = false;
		ena_AFT_MANIFOLD_12_JET_INH_X = false;
		ena_AFT_MANIFOLD_12_JET_INH_Y = false;
		ena_AFT_MANIFOLD_345_JET_INH_X = false;
		ena_AFT_MANIFOLD_345_JET_INH_Y = false;
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

		if ((ReadCOMPOOL_SS( SCP_VE/*SCP_REL_VEL_MAG*/ ) <= FRCS_DUMP_START_VEL) && (ReadCOMPOOL_IS( SCP_FWD_RCS_DUMP_ENABLE ) == 1))
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

		unsigned short RCS_ON_A[44];
		unsigned short RCS_ON_B[44];

		// fwd rcs
		if (run80ms) FRCS( step80ms );

		// aft rcs
		if (run40ms)
		{
			// get DAP commands
			unsigned short NEW_JON[44];
			for (auto& x : NEW_JON) x = 0;
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


			unsigned short S_RCS_IGN = ReadCOMPOOL_IS( SCP_S_RCS_IGN );
			unsigned short S_RCS_NULL20 = ReadCOMPOOL_IS( SCP_S_RCS_NULL20 );
			unsigned short AFT_MANIFOLD_12_JET_INH_FLAG = ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_12_JET_INH_FLAG );
			unsigned short AFT_MANIFOLD_345_JET_INH_FLAG = ReadCOMPOOL_IS( SCP_AFT_MANIFOLD_345_JET_INH_FLAG );
			unsigned short IC_CPLT = ReadCOMPOOL_IS( SCP_OMSRCS_INTERCONNECT_COMPLETE_FLAG );
			unsigned short RCS_12_ALL_JET_INHIBIT_FLAG = ReadCOMPOOL_IS( SCP_RCS_12_ALL_JET_INHIBIT_FLAG );
			unsigned short RCS_345_ALL_JET_INHIBIT_FLAG = ReadCOMPOOL_IS( SCP_RCS_345_ALL_JET_INHIBIT_FLAG );
			if ((S_RCS_IGN == 1) || (S_RCS_NULL20 == 1) || (DUMP0 == 1) || (DUMP1 == 1) || (DUMP2 == 1) || (DELAY2 == 1))
			{
				//// abort and DAP cmds
				unsigned short ABT_X_ON = S_RCS_IGN;
				unsigned short ABT_20NULL = S_RCS_NULL20;

				/// C (inhibits RCS (dumps + DAP) for I/C setup)
				if (RCS_12_ALL_JET_INHIBIT_FLAG == 0)
				{
					availablejets[25] = 1;// R1R
					availablejets[23] = 1;// R2R
					availablejets[30] = 1;// R2U
					availablejets[31] = 1;// R1U
					availablejets[36] = 1;// R2D
					availablejets[15] = 1;// R1A
					availablejets[27] = 1;// L2U
					availablejets[28] = 1;// L1U
					availablejets[33] = 1;// L2D
					availablejets[21] = 1;// L1L
					availablejets[19] = 1;// L2L
					availablejets[17] = 1;// L1A
				}
				else
				{
					if ((IC_CPLT == 1) && (IC_CPLT_LAST == 0))
					{
						availablejets[25] = 0;// R1R
						availablejets[23] = 0;// R2R
						availablejets[30] = 0;// R2U
						availablejets[31] = 0;// R1U
						availablejets[36] = 0;// R2D
						availablejets[15] = 0;// R1A
						availablejets[27] = 0;// L2U
						availablejets[28] = 0;// L1U
						availablejets[33] = 0;// L2D
						availablejets[21] = 0;// L1L
						availablejets[19] = 0;// L2L
						availablejets[17] = 0;// L1A
					}
					else
					{
						/*
						A – Available. Begin counter for condition B.
						B – If RCS_CYC2 cycles have occurred since condition A, jets will be made unavailable. Otherwise, maintain previous cycle’s availability.
						*/
						if (RCS_12_ALL_JET_INHIBIT_FLAG_LAST_PASS == 0)
						{
							availablejets[25] = 1;// R1R
							availablejets[23] = 1;// R2R
							availablejets[30] = 1;// R2U
							availablejets[31] = 1;// R1U
							availablejets[36] = 1;// R2D
							availablejets[15] = 1;// R1A
							availablejets[27] = 1;// L2U
							availablejets[28] = 1;// L1U
							availablejets[33] = 1;// L2D
							availablejets[21] = 1;// L1L
							availablejets[19] = 1;// L2L
							availablejets[17] = 1;// L1A

							counter_RCS_12_ALL_JET_INHIBIT = 0;
							ena_RCS_12_ALL_JET_INHIBIT = true;
						}
						else
						{
							if (ena_RCS_12_ALL_JET_INHIBIT) counter_RCS_12_ALL_JET_INHIBIT++;

							if (counter_RCS_12_ALL_JET_INHIBIT >= RCS_CYC2)
							{
								availablejets[25] = 0;// R1R
								availablejets[23] = 0;// R2R
								availablejets[30] = 0;// R2U
								availablejets[31] = 0;// R1U
								availablejets[36] = 0;// R2D
								availablejets[15] = 0;// R1A
								availablejets[27] = 0;// L2U
								availablejets[28] = 0;// L1U
								availablejets[33] = 0;// L2D
								availablejets[21] = 0;// L1L
								availablejets[19] = 0;// L2L
								availablejets[17] = 0;// L1A

								counter_RCS_12_ALL_JET_INHIBIT = 0;
								ena_RCS_12_ALL_JET_INHIBIT = false;
							}
						}
					}
				}

				if (RCS_345_ALL_JET_INHIBIT_FLAG == 0)
				{
					availablejets[24] = 1;// R3R
					availablejets[22] = 1;// R4R
					availablejets[29] = 1;// R4U
					availablejets[37] = 1;// R3D
					availablejets[35] = 1;// R4D
					availablejets[14] = 1;// R3A
					availablejets[26] = 1;// L4U
					availablejets[34] = 1;// L3D
					availablejets[32] = 1;// L4D
					availablejets[20] = 1;// L3L
					availablejets[18] = 1;// L4L
					availablejets[16] = 1;// L3A
				}
				else
				{
					if ((IC_CPLT == 1) && (IC_CPLT_LAST == 0))
					{
						availablejets[24] = 0;// R3R
						availablejets[22] = 0;// R4R
						availablejets[29] = 0;// R4U
						availablejets[37] = 0;// R3D
						availablejets[35] = 0;// R4D
						availablejets[14] = 0;// R3A
						availablejets[26] = 0;// L4U
						availablejets[34] = 0;// L3D
						availablejets[32] = 0;// L4D
						availablejets[20] = 0;// L3L
						availablejets[18] = 0;// L4L
						availablejets[16] = 0;// L3A
					}
					else
					{
						if (RCS_345_ALL_JET_INHIBIT_FLAG_LAST_PASS == 0)
						{
							availablejets[24] = 1;// R3R
							availablejets[22] = 1;// R4R
							availablejets[29] = 1;// R4U
							availablejets[37] = 1;// R3D
							availablejets[35] = 1;// R4D
							availablejets[14] = 1;// R3A
							availablejets[26] = 1;// L4U
							availablejets[34] = 1;// L3D
							availablejets[32] = 1;// L4D
							availablejets[20] = 1;// L3L
							availablejets[18] = 1;// L4L
							availablejets[16] = 1;// L3A

							counter_RCS_345_ALL_JET_INHIBIT = 0;
							ena_RCS_345_ALL_JET_INHIBIT = true;
						}
						else
						{
							if (counter_RCS_345_ALL_JET_INHIBIT >= RCS_CYC2)// TODO count cycles
							{
								availablejets[24] = 0;// R3R
								availablejets[22] = 0;// R4R
								availablejets[29] = 0;// R4U
								availablejets[37] = 0;// R3D
								availablejets[35] = 0;// R4D
								availablejets[14] = 0;// R3A
								availablejets[26] = 0;// L4U
								availablejets[34] = 0;// L3D
								availablejets[32] = 0;// L4D
								availablejets[20] = 0;// L3L
								availablejets[18] = 0;// L4L
								availablejets[16] = 0;// L3A

								counter_RCS_345_ALL_JET_INHIBIT = 0;
								ena_RCS_345_ALL_JET_INHIBIT = false;
							}
						}
					}
				}

				/// D (inhibits RCS dumps due to I/C failure)
				if (RCS_12_ALL_JET_INHIBIT_FLAG == 0)
				{
					if (AFT_MANIFOLD_12_JET_INH_FLAG == 0)
					{
						availablejetsdump[25] = 1;// R1R
						availablejetsdump[23] = 1;// R2R
						availablejetsdump[30] = 1;// R2U
						availablejetsdump[31] = 1;// R1U
						availablejetsdump[37] = 1;// R3D (for balance)
						availablejetsdump[36] = 1;// R2D
						availablejetsdump[15] = 1;// R1A
						availablejetsdump[27] = 1;// L2U
						availablejetsdump[28] = 1;// L1U
						availablejetsdump[34] = 1;// L3D (for balance)
						availablejetsdump[33] = 1;// L2D
						availablejetsdump[21] = 1;// L1L
						availablejetsdump[19] = 1;// L2L
						availablejetsdump[17] = 1;// L1A
					}
					else
					{
						// X
						if ((ABT_X_ON == 1) && (ABT_X_ON_LAST_PASS == 0))
						{
							availablejetsdump[15] = 0;// R1A
							availablejetsdump[17] = 0;// L1A
						}
						else
						{
							if (AFT_MANIFOLD_12_JET_INH_FLAG_LAST_PASS == 0)
							{
								availablejetsdump[15] = 1;// R1A
								availablejetsdump[17] = 1;// L1A

								counter_AFT_MANIFOLD_12_JET_INH_X = 0;
								ena_AFT_MANIFOLD_12_JET_INH_X = true;
							}
							else
							{
								if (counter_AFT_MANIFOLD_12_JET_INH_X >= RCS_CYC2)// TODO count cycles
								{
									availablejetsdump[15] = 0;// R1A
									availablejetsdump[17] = 0;// L1A

									counter_AFT_MANIFOLD_12_JET_INH_X = 0;
									ena_AFT_MANIFOLD_12_JET_INH_X = false;
								}
							}
						}

						// Y
						if ((ABT_20NULL == 1) && (ABT_20_NULL_LAST_PASS == 0))
						{
							availablejetsdump[25] = 0;// R1R
							availablejetsdump[23] = 0;// R2R
							availablejetsdump[21] = 0;// L1L
							availablejetsdump[19] = 0;// L2L
						}
						else
						{
							if (AFT_MANIFOLD_12_JET_INH_FLAG_LAST_PASS == 0)
							{
								availablejetsdump[25] = 1;// R1R
								availablejetsdump[23] = 1;// R2R
								availablejetsdump[21] = 1;// L1L
								availablejetsdump[19] = 1;// L2L

								counter_AFT_MANIFOLD_12_JET_INH_Y = 0;
								ena_AFT_MANIFOLD_12_JET_INH_Y = true;
							}
							else
							{
								if (counter_AFT_MANIFOLD_12_JET_INH_Y >= RCS_CYC1)// TODO count cycles
								{
									availablejetsdump[25] = 0;// R1R
									availablejetsdump[23] = 0;// R2R
									availablejetsdump[21] = 0;// L1L
									availablejetsdump[19] = 0;// L2L

									counter_AFT_MANIFOLD_12_JET_INH_Y = 0;
									ena_AFT_MANIFOLD_12_JET_INH_Y = false;
								}
							}
						}

						// Z
						if ((ABT_20NULL == 1) || (ABT_20_NULL_LAST_PASS == 1))
						{
							availablejetsdump[30] = 0;// R2U
							availablejetsdump[31] = 0;// R1U
							//availablejetsdump[37] = 0;// R3D (for balance)
							availablejetsdump[36] = 0;// R2D
							availablejetsdump[27] = 0;// L2U
							availablejetsdump[28] = 0;// L1U
							//availablejetsdump[34] = 0;// L3D (for balance)
							availablejetsdump[33] = 0;// L2D
						}
					}
				}

				if (RCS_345_ALL_JET_INHIBIT_FLAG == 0)
				{
					if (AFT_MANIFOLD_345_JET_INH_FLAG == 0)
					{
						availablejetsdump[24] = 1;// R3R
						availablejetsdump[22] = 1;// R4R
						availablejetsdump[29] = 1;// R4U
						availablejetsdump[31] = 1;// R1U (for balance)
						availablejetsdump[37] = 1;// R3D
						availablejetsdump[35] = 1;// R4D
						availablejetsdump[14] = 1;// R3A
						availablejetsdump[26] = 1;// L4U
						availablejetsdump[28] = 1;// L1U (for balance)
						availablejetsdump[34] = 1;// L3D
						availablejetsdump[32] = 1;// L4D
						availablejetsdump[20] = 1;// L3L
						availablejetsdump[18] = 1;// L4L
						availablejetsdump[16] = 1;// L3A
					}
					else
					{
						// X
						if ((ABT_X_ON == 1) && (ABT_X_ON_LAST_PASS == 0))
						{
							availablejetsdump[14] = 0;// R3A
							availablejetsdump[16] = 0;// L3A
						}
						else
						{
							if (AFT_MANIFOLD_345_JET_INH_FLAG_LAST_PASS == 0)
							{
								availablejetsdump[14] = 1;// R3A
								availablejetsdump[16] = 1;// L3A

								counter_AFT_MANIFOLD_345_JET_INH_X = 0;
								ena_AFT_MANIFOLD_345_JET_INH_X = true;
							}
							else
							{
								if (counter_AFT_MANIFOLD_345_JET_INH_X >= RCS_CYC2)// TODO count cycles
								{
									availablejetsdump[14] = 0;// R3A
									availablejetsdump[16] = 0;// L3A

									counter_AFT_MANIFOLD_345_JET_INH_X = 0;
									ena_AFT_MANIFOLD_345_JET_INH_X = false;
								}
							}
						}

						// Y
						if ((ABT_20NULL == 1) && (ABT_20_NULL_LAST_PASS == 0))
						{
							availablejetsdump[24] = 0;// R3R
							availablejetsdump[22] = 0;// R4R
							availablejetsdump[20] = 0;// L3L
							availablejetsdump[18] = 0;// L4L
						}
						else
						{
							if (AFT_MANIFOLD_345_JET_INH_FLAG_LAST_PASS == 0)
							{
								availablejetsdump[24] = 1;// R3R
								availablejetsdump[22] = 1;// R4R
								availablejetsdump[20] = 1;// L3L
								availablejetsdump[18] = 1;// L4L

								counter_AFT_MANIFOLD_345_JET_INH_Y = 0;
								ena_AFT_MANIFOLD_345_JET_INH_Y = true;
							}
							else
							{
								if (counter_AFT_MANIFOLD_345_JET_INH_Y >= RCS_CYC1)// TODO count cycles
								{
									availablejetsdump[24] = 0;// R3R
									availablejetsdump[22] = 0;// R4R
									availablejetsdump[20] = 0;// L3L
									availablejetsdump[18] = 0;// L4L

									counter_AFT_MANIFOLD_345_JET_INH_Y = 0;
									ena_AFT_MANIFOLD_345_JET_INH_Y = false;
								}
							}
						}

						// Z
						if ((ABT_20NULL == 1) || (ABT_20_NULL_LAST_PASS == 1))
						{
							availablejetsdump[29] = 0;// R4U
							//availablejetsdump[31] = 0;// R1U (for balance)
							availablejetsdump[37] = 0;// R3D
							availablejetsdump[35] = 0;// R4D
							availablejetsdump[26] = 0;// L4U
							//availablejetsdump[28] = 0;// L1U (for balance)
							availablejetsdump[34] = 0;// L3D
							availablejetsdump[32] = 0;// L4D
						}
					}
				}

				/// E (+X)
				// part of this is implemented in block F
				if (ABT_20NULL == 0)
				{
					float AFT_RCS_TTG_SF = 1.0;

					unsigned short JETGD[4];// Jet-good discrete array (L3A, L1A, R1A, R3A)
					JETGD[0] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_AFT, 9, 28 );
					JETGD[1] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_AFT, 1, 28 );
					JETGD[2] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_AFT, 4, 28 );
					JETGD[3] = ReadCOMPOOL_AIS( SCP_AVAILABLE_JET_AFT, 12, 28 );

					if ((JETGD[0] == 0) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 1))
					{
						availablejets[17] = 0;// L3A
						availablejets[15] = 0;// R3A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 1) && (JETGD[1] == 0) && (JETGD[2] == 1) && (JETGD[3] == 1))
					{
						availablejets[18] = 0;// L1A
						availablejets[16] = 0;// R1A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 1) && (JETGD[1] == 1) && (JETGD[2] == 0) && (JETGD[3] == 1))
					{
						availablejets[18] = 0;// L1A
						availablejets[16] = 0;// R1A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 1) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 0))
					{
						availablejets[17] = 0;// L3A
						availablejets[15] = 0;// R3A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 0) && (JETGD[1] == 1) && (JETGD[2] == 0) && (JETGD[3] == 1))
					{
						availablejets[17] = 0;// L3A
						availablejets[16] = 0;// R1A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 0) && (JETGD[1] == 1) && (JETGD[2] == 1) && (JETGD[3] == 0))
					{
						availablejets[17] = 0;// L3A
						availablejets[15] = 0;// R3A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 1) && (JETGD[1] == 0) && (JETGD[2] == 0) && (JETGD[3] == 1))
					{
						availablejets[18] = 0;// L1A
						availablejets[16] = 0;// R1A
						AFT_RCS_TTG_SF = 0.5;
					}
					else if ((JETGD[0] == 1) && (JETGD[1] == 0) && (JETGD[2] == 1) && (JETGD[3] == 0))
					{
						availablejets[18] = 0;// L1A
						availablejets[15] = 0;// R3A
						AFT_RCS_TTG_SF = 0.5;
					}
					else
					{
						availablejets[17] &= JETGD[0];// L3A
						availablejets[18] &= JETGD[1];// L1A
						availablejets[16] &= JETGD[2];// R1A
						availablejets[15] &= JETGD[3];// R3A
					}

					WriteCOMPOOL_SS( SCP_AFT_RCS_TTG_SF, AFT_RCS_TTG_SF );
				}

				// turn off in MM305
				ABT_X_ON &= (ReadCOMPOOL_IS( SCP_MM ) != 305);


				/// F (ABT_20NULL)
				unsigned short ABT_JETS = S_RCS_NULL20;

				N_CYCLE( ABT_JETS, RCS_CYC1, OLDABT_JETS, NCYC1, DELAY1 );
				N_CYCLE( ABT_JETS, RCS_CYC2, OLDDELAY1, NCYC2, DELAY2 );

				if (ABT_JETS == 1)
				{
					DUMP0 = ABT_X_ON;
					DUMP1 = ABT_20NULL & DELAY1;
					DUMP2 = ABT_20NULL & DELAY2;
				}
				else //if (ABT_JETS == 0)
				{
					DUMP0 = ((OLD20NULL & DELAY2) & OLDXNULL) | ABT_X_ON;
					DUMP1 = OLD20NULL & DELAY1;
					DUMP2 = 0;
				}

				if (NCYC2 == 0)
				{
					OLD20NULL = ABT_20NULL;
					OLDXNULL = ABT_X_ON;
				}

				// abort + DAP outputs
				//for (int i = 1; i <= 14; i++) RCS_ON[i - 1] = NEW_JON[i - 1];
				for (int i = 15; i <= 18; i++) RCS_ON[i - 1] = (NEW_JON[i - 1] | (DUMP0 & availablejetsdump[i - 1])) & availablejets[i - 1];
				for (int i = 19; i <= 26; i++) RCS_ON[i - 1] = (NEW_JON[i - 1] | (DUMP1 & availablejetsdump[i - 1])) & availablejets[i - 1];
				for (int i = 27; i <= 38; i++) RCS_ON[i - 1] = (NEW_JON[i - 1] | (DUMP2 & availablejetsdump[i - 1])) & availablejets[i - 1];
				// mirror DAP yaw cmds
				for (int i = 19; i <= 22; i++) if (NEW_JON[i - 1]) RCS_ON[i + 4 - 1] = 0;
				for (int i = 23; i <= 26; i++) if (NEW_JON[i - 1]) RCS_ON[i - 4 - 1] = 0;
				// mirror DAP roll/pitch cmds
				for (int i = 27; i <= 32; i++) if (NEW_JON[i - 1]) RCS_ON[i + 6 - 1] = 0;
				for (int i = 33; i <= 38; i++) if (NEW_JON[i - 1]) RCS_ON[i - 6 - 1] = 0;
			}
			else
			{
				//// DAP cmds
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
			IC_CPLT_LAST = IC_CPLT;
			RCS_12_ALL_JET_INHIBIT_FLAG_LAST_PASS = RCS_12_ALL_JET_INHIBIT_FLAG;
			RCS_345_ALL_JET_INHIBIT_FLAG_LAST_PASS = RCS_345_ALL_JET_INHIBIT_FLAG;
		}

		// output
		// generate A & B cmds
		for (int i = 0; i < 44; i++)
		{
			RCS_ON_B[i] = RCS_ON[i];

			if (RCS_ON[i] == 0)
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
		cmd |= RCS_ON_A[3] << 1;// F1L A
		wrd = ReadCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF1_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		cmd |= RCS_ON_B[3] << 1;// F1L B
		wrd = ReadCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF1_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		cmd |= RCS_ON_A[5] << 1;// F2R A
		wrd = ReadCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF2_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		cmd |= RCS_ON_B[5] << 1;// F2R B
		wrd = ReadCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF2_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		cmd |= RCS_ON_A[6] << 0;// F4R A
		wrd = ReadCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF3_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		cmd |= RCS_ON_B[6] << 0;// F4R B
		wrd = ReadCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF3_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		cmd |= RCS_ON_A[4] << 1;// F3L A
		wrd = ReadCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF4_IOM5_CH0_DATA, cmd | wrd );
		cmd = 0;
		cmd |= RCS_ON_B[4] << 1;// F3L B
		wrd = ReadCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA ) & 0xFFF0;
		WriteCOMPOOL_IS( SCP_FF4_IOM13_CH0_DATA, cmd | wrd );

		cmd = 0;
		cmd |= RCS_ON_A[17] << 0;// L1A A
		cmd |= RCS_ON_A[21] << 1;// L1L A
		cmd |= RCS_ON_A[28] << 2;// L1U A
		cmd |= RCS_ON_A[15] << 3;// R1A A
		cmd |= RCS_ON_A[25] << 4;// R1R A
		cmd |= RCS_ON_A[31] << 5;// R1U A
		wrd = ReadCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA ) & 0xFF00;
		WriteCOMPOOL_IS( SCP_FA1_IOM2_CH0_DATA, cmd | wrd );
		cmd = 0;
		cmd |= RCS_ON_B[17] << 0;// L1A B
		cmd |= RCS_ON_B[21] << 1;// L1L B
		cmd |= RCS_ON_B[28] << 2;// L1U B
		cmd |= RCS_ON_B[15] << 3;// R1A B
		cmd |= RCS_ON_B[25] << 4;// R1R B
		cmd |= RCS_ON_B[31] << 5;// R1U B
		wrd = ReadCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA ) & 0xFF00;
		WriteCOMPOOL_IS( SCP_FA1_IOM10_CH0_DATA, cmd | wrd );

		cmd = 0;
		cmd |= RCS_ON_A[16] << 0;// L3A A
		cmd |= RCS_ON_A[20] << 1;// L3L A
		cmd |= RCS_ON_A[34] << 2;// L3D A
		cmd |= RCS_ON_A[14] << 3;// R3A A
		cmd |= RCS_ON_A[24] << 4;// R3R A
		cmd |= RCS_ON_A[37] << 5;// R3D A
		wrd = ReadCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA ) & 0xFF00;
		WriteCOMPOOL_IS( SCP_FA2_IOM2_CH0_DATA, cmd | wrd );
		cmd = 0;
		cmd |= RCS_ON_B[16] << 0;// L3A B
		cmd |= RCS_ON_B[20] << 1;// L3L B
		cmd |= RCS_ON_B[34] << 2;// L3D B
		cmd |= RCS_ON_B[14] << 3;// R3A B
		cmd |= RCS_ON_B[24] << 4;// R3R B
		cmd |= RCS_ON_B[37] << 5;// R3D B
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


		// reset
		if (run40ms)
		{
			step40ms = 0.0;
			if (run80ms) step80ms = 0.0;
		}
		return;
	}

	void EL_RCS_CMD_SOP::N_CYCLE( const unsigned short INPUT, const unsigned short NN, unsigned short& LASTIN, unsigned short& N, unsigned short& OUTPUT )
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
