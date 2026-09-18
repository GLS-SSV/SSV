/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/09/29   GLS
2022/10/12   GLS
2022/11/15   GLS
2022/11/16   GLS
2022/11/17   GLS
2022/12/23   GLS
2023/11/26   GLS
2026/09/18   GLS
********************************************/
#include "SSME_Operations.h"
#include "../../../Atlantis.h"
#include <cassert>


namespace dps
{
	constexpr double TIME_DELAY_ADG = 4.5;// sec
	constexpr double TIME_DELAY_CFI = 2;// sec
	constexpr double TIME_DELAY_LH2_PVLV_CL = 4.9;// sec
	constexpr double TIME_TO_ZERO_THRUST = 3.75;// sec, I-load


	SSME_Operations::SSME_Operations( SimpleGPCSystem *_gpc ):SimpleGPCSoftware( _gpc, "SSME_Operations" )
	{
		for (int i = 0; i < 3; i++)
		{
			ManualShutdownFlag[i] = false;
			ShutdownCommandIssued[i] = false;
			ShutdownFlag_A[i] = false;
			PVLV_CL_CMD[i] = false;
			PVLV_CL_CMD_removed[i] = false;

			counter_CEG[i] = 3;
			counter_DFH[i] = 0;

			timerADG[i] = -1;
			timerCFI[i] = -1;
			timerLH2PVLV[i] = -1;
		}

		counter_A = 0;
		counter_B = 0;

		LO2_SENSOR_1_DRY_FLAG = false;
		LO2_SENSOR_2_DRY_FLAG = false;
		LO2_SENSOR_3_DRY_FLAG = false;
		LO2_SENSOR_4_DRY_FLAG = false;
		LH2_SENSOR_1_DRY_FLAG = false;
		LH2_SENSOR_2_DRY_FLAG = false;
		LH2_SENSOR_3_DRY_FLAG = false;
		LH2_SENSOR_4_DRY_FLAG = false;
		MPS_LOX_LO_LVL_LIQ_SES1_DSBL_FLG = false;
		MPS_LOX_LO_LVL_LIQ_SES2_DSBL_FLG = false;
		MPS_LOX_LO_LVL_LIQ_SES3_DSBL_FLG = false;
		MPS_LOX_LO_LVL_LIQ_SES4_DSBL_FLG = false;
		ET_LH2_LO_LVL_LIQ_SES1_DSBL_FLG = false;
		ET_LH2_LO_LVL_LIQ_SES2_DSBL_FLG = false;
		ET_LH2_LO_LVL_LIQ_SES3_DSBL_FLG = false;
		ET_LH2_LO_LVL_LIQ_SES4_DSBL_FLG = false;
		LowLevel1stRun = true;
		LowLevelLO2timer = -1;
		LowLevelLH2timer = -1;

		timerMECOConfirmed = 999999;

		LimitSwitch = 1;

		otherSSMEs[0][0] = 1;
		otherSSMEs[0][1] = 2;

		otherSSMEs[1][0] = 0;
		otherSSMEs[1][1] = 2;

		otherSSMEs[2][0] = 0;
		otherSSMEs[2][1] = 1;
		return;
	}

	SSME_Operations::~SSME_Operations( void )
	{
		return;
	}

	void SSME_Operations::OnPreStep( double simt, double simdt, double mjd )
	{
		bool ME_STDN_PB[3];
		ME_STDN_PB[0] = (ReadCOMPOOL_IS( SCP_MPS_ME_1_SHUTDOWN_CMD ) != 0);
		ME_STDN_PB[1] = (ReadCOMPOOL_IS( SCP_MPS_ME_2_SHUTDOWN_CMD ) != 0);
		ME_STDN_PB[2] = (ReadCOMPOOL_IS( SCP_MPS_ME_3_SHUTDOWN_CMD ) != 0);

		// INFO check 20030005845_2002110399 for new vlv timing data
		for (int i = 0; i < 3; i++)
		{
			if (PVLV_CL_CMD[i] == true)
			{
				if (PVLV_CL_CMD_removed[i] == false)
				{
					if (timerCFI[i] <= simt)
					{
						switch (i)
						{
							case 0:
								// reset engine 1 prevalves close
								WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0080 );// C LO2 CL A
								WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0080 );// C LO2 CL B
								WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0080 );// C LO2 CL C
								WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) & ~0x0040 );// C LO2 CL D

								WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0020 );// C LH2 CL A
								WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0020 );// C LH2 CL B
								WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0020 );// C LH2 CL C
								break;
							case 1:
								// reset engine 2 prevalves close
								WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0080 );// L LO2 CL A
								WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0080 );// L LO2 CL B
								WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) & ~0x0080 );// L LO2 CL C
								WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) & ~0x0008 );// L LO2 CL D

								WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0020 );// L LH2 CL A
								WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0020 );// L LH2 CL B
								WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) & ~0x0020 );// L LH2 CL C
								break;
							case 2:
								// reset engine 3 prevalves close
								WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0080 );// R LO2 CL A
								WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0080 );// R LO2 CL B
								WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0080 );// R LO2 CL C
								WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA ) & ~0x0040 );// R LO2 CL D

								WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0020 );// R LH2 CL A
								WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0020 );// R LH2 CL B
								WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0020 );// R LH2 CL C
								break;
						}

						PVLV_CL_CMD_removed[i] = true;
					}
				}
			}
			else
			{
				// TODO missing safing cmd (is it really needed?)
				if (((ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i + 1, 3 ) == 1) && (ShutdownCommandIssued[i] == true)) ||
					((ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i + 1, 3 ) == 0) && ((ReadCOMPOOL_AIS( SCP_MESHDN, i + 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, i + 1, 3 ) == 1))))
				{
					switch (i)
					{
						case 0:
							WriteCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN, 1 );
							break;
						case 1:
							WriteCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN, 1 );
							break;
						case 2:
							WriteCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN, 1 );
							break;
					}

					if (timerADG[i] != -1)
					{
						if (timerADG[i] <= simt)
						{
							switch (i)
							{
								case 0:
									// open engine 1 LO2 prevalve
									WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0100 );// C LO2 OP A
									WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0100 );// C LO2 OP B
									WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0100 );// C LO2 OP C
									WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) & ~0x0080 );// C LO2 OP D
									WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) | 0x0080 );// C LO2 CL A
									WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) | 0x0080 );// C LO2 CL B
									WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) | 0x0080 );// C LO2 CL C
									WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) | 0x0040 );// C LO2 CL D
									break;
								case 1:
									// open engine 2 LO2 prevalve
									WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0100 );// L LO2 OP A
									WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0100 );// L LO2 OP B
									WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) & ~0x0100 );// L LO2 OP C
									WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) & ~0x0010 );// L LO2 OP D
									WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) | 0x0080 );// L LO2 CL A
									WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) | 0x0080 );// L LO2 CL B
									WriteCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM15_CH0_DATA ) | 0x0080 );// L LO2 CL C
									WriteCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM7_CH1_DATA ) | 0x0008 );// L LO2 CL D
									break;
								case 2:
									// open engine 3 LO2 prevalve
									WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0100 );// R LO2 OP A
									WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0100 );// R LO2 OP B
									WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0100 );// R LO2 OP C
									WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA ) & ~0x0080 );// R LO2 OP D
									WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0080 );// R LO2 CL A
									WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) | 0x0080 );// R LO2 CL B
									WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) | 0x0080 );// R LO2 CL C
									WriteCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH1_DATA ) | 0x0040 );// R LO2 CL D
									break;
							}

							if (timerLH2PVLV[i] == -1)
							{
								timerLH2PVLV[i] = simt + TIME_DELAY_LH2_PVLV_CL;
							}

							if (timerLH2PVLV[i] <= simt)
							{
								switch (i)
								{
									case 0:
										// close engine 1 LH2 prevalve
										WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) & ~0x0040 );// C LH2 OP A
										WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) & ~0x0040 );// C LH2 OP B
										WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) & ~0x0040 );// C LH2 OP C
										WriteCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA3_IOM7_CH0_DATA ) | 0x0020 );// C LH2 CL A
										WriteCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM7_CH0_DATA ) | 0x0020 );// C LH2 CL B
										WriteCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM7_CH0_DATA ) | 0x0020 );// C LH2 CL C
										break;
									case 1:
										// close engine 2 LH2 prevalve
										WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) & ~0x0040 );// L LH2 OP A
										WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) & ~0x0040 );// L LH2 OP B
										WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) & ~0x0040 );// L LH2 OP C
										WriteCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM15_CH0_DATA ) | 0x0020 );// L LH2 CL A
										WriteCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM15_CH0_DATA ) | 0x0020 );// L LH2 CL B
										WriteCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM15_CH0_DATA ) | 0x0020 );// L LH2 CL C
										break;
									case 2:
										// close engine 3 LH2 prevalve
										WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) & ~0x0040 );// R LH2 OP A
										WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) & ~0x0040 );// R LH2 OP B
										WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) & ~0x0040 );// R LH2 OP C
										WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0020 );// R LH2 CL A
										WriteCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA4_IOM12_CH0_DATA ) | 0x0020 );// R LH2 CL B
										WriteCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA1_IOM12_CH0_DATA ) | 0x0020 );// R LH2 CL C
										break;
								}

								PVLV_CL_CMD[i] = true;

								timerCFI[i] = simt + TIME_DELAY_CFI;
							}
						}
					}
					else
					{
						timerADG[i] = simt + TIME_DELAY_ADG;
					}
				}
			}

			if (ME_STDN_PB[i])
			{
				if (ManualShutdownFlag[i] == false)// only log first PB use
				{
					oapiWriteLogV( "ME-%d PB Pressed @ MET %.2f", i + 1, STS()->GetMET() );
				}
				ManualShutdownFlag[i] = true;
			}
		}

		if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 1)
		{
			// ...
			// go to G
		}
		else
		{
			if (ReadCOMPOOL_IS( SCP_MPS_ENG_LIMIT_CONTROL_AUTO ))
			{
				// AUTO
				counter_A = 0;
				counter_B = 0;
				for (int i = 0; i < 3; i++)
				{
					// HACK replaced line below so it also works on 2EO
					if (ManualShutdownFlag[i] == false)
					//if ((ManualShutdownFlag[otherSSMEs[i][0]] == false) && (ManualShutdownFlag[otherSSMEs[i][1]] == false))
					{
						if ((ReadCOMPOOL_AIS( SCP_MESHDN, i + 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, i + 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, i + 1, 3 ) == 1))
						{
							if (counter_DFH[i] < 3)
							{
								// INH all others
								WriteCOMPOOL_AIS( SCP_MPS_INH, otherSSMEs[i][0] + 1, 1, 3 );
								WriteCOMPOOL_AIS( SCP_MPS_INH, otherSSMEs[i][1] + 1, 1, 3 );

								counter_DFH[i]++;
							}
						}
						else
						{
							if (counter_CEG[i] < 3)
							{
								// ENA me
								WriteCOMPOOL_AIS( SCP_MPS_ENA, i + 1, 1, 3 );

								counter_CEG[i]++;
							}
						}
					}
				}
			}
			else
			{
				counter_CEG[0] = 0;
				counter_CEG[1] = 0;
				counter_CEG[2] = 0;
				counter_DFH[0] = 0;
				counter_DFH[1] = 0;
				counter_DFH[2] = 0;
				if (ReadCOMPOOL_IS( SCP_MPS_ENG_LIMIT_CONTROL_ENABLE ))
				{
					// ENA
					counter_B = 0;

					if (counter_A < 3)
					{
						// ENA all
						WriteCOMPOOL_AIS( SCP_MPS_ENA, 1, 1, 3 );
						WriteCOMPOOL_AIS( SCP_MPS_ENA, 2, 1, 3 );
						WriteCOMPOOL_AIS( SCP_MPS_ENA, 3, 1, 3 );

						counter_A++;
					}
				}
				else
				{
					// INH
					counter_A = 0;

					if (counter_B < 3)
					{
						if (ManualShutdownFlag[0] == false) WriteCOMPOOL_AIS( SCP_MPS_INH, 1, 1, 3 );
						if (ManualShutdownFlag[1] == false) WriteCOMPOOL_AIS( SCP_MPS_INH, 2, 1, 3 );
						if (ManualShutdownFlag[2] == false) WriteCOMPOOL_AIS( SCP_MPS_INH, 3, 1, 3 );

						counter_B++;
					}
				}
			}

			// F
		}

		// G

		if ((ReadCOMPOOL_IS( SCP_S_LOW_LEVEL ) == 1) && (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0))
		{
			unsigned int COMMFAULT_WORD_1 = ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 );
			bool commfaultFA1 = (COMMFAULT_WORD_1 & 0x00001000) != 0;
			bool commfaultFA2 = (COMMFAULT_WORD_1 & 0x00002000) != 0;
			bool commfaultFA3 = (COMMFAULT_WORD_1 & 0x00004000) != 0;
			bool commfaultFA4 = (COMMFAULT_WORD_1 & 0x00008000) != 0;

			bool LO2_DISABLE_LIMIT_FLAG = false;

			if ((ReadCOMPOOL_IS( SCP_FA3_IOM11_CH0_DATA ) & 0x0080) != 0)// ET - LO2 ECO SENSOR NO. 1
			{
				if (!commfaultFA3)
				{
					if (LowLevel1stRun)
					{
						MPS_LOX_LO_LVL_LIQ_SES1_DSBL_FLG = true;
						LO2_DISABLE_LIMIT_FLAG = true;
					}
					else
					{
						if (!MPS_LOX_LO_LVL_LIQ_SES1_DSBL_FLG)
						{
							LO2_SENSOR_1_DRY_FLAG = true;
						}
					}
				}
			}

			if ((ReadCOMPOOL_IS( SCP_FA2_IOM11_CH0_DATA ) & 0x0080) != 0)// ET - LO2 ECO SENSOR NO. 2
			{
				if (!commfaultFA2)
				{
					if (LowLevel1stRun)
					{
						if (!LO2_DISABLE_LIMIT_FLAG)
						{
							MPS_LOX_LO_LVL_LIQ_SES2_DSBL_FLG = true;
							LO2_DISABLE_LIMIT_FLAG = true;
						}
					}
					else
					{
						if (!MPS_LOX_LO_LVL_LIQ_SES2_DSBL_FLG)
						{
							LO2_SENSOR_2_DRY_FLAG = true;
						}
					}
				}
			}

			if ((ReadCOMPOOL_IS( SCP_FA4_IOM11_CH0_DATA ) & 0x0080) != 0)// ET - LO2 ECO SENSOR NO. 3
			{
				if (!commfaultFA4)
				{
					if (LowLevel1stRun)
					{
						if (!LO2_DISABLE_LIMIT_FLAG)
						{
							MPS_LOX_LO_LVL_LIQ_SES3_DSBL_FLG = true;
							LO2_DISABLE_LIMIT_FLAG = true;
						}
					}
					else
					{
						if (!MPS_LOX_LO_LVL_LIQ_SES3_DSBL_FLG)
						{
							LO2_SENSOR_3_DRY_FLAG = true;
						}
					}
				}
			}

			if ((ReadCOMPOOL_IS( SCP_FA1_IOM11_CH0_DATA ) & 0x0080) != 0)// ET - LO2 ECO SENSOR NO. 4
			{
				if (!commfaultFA1)
				{
					if (LowLevel1stRun)
					{
						if (!LO2_DISABLE_LIMIT_FLAG)
						{
							MPS_LOX_LO_LVL_LIQ_SES4_DSBL_FLG = true;
							LO2_DISABLE_LIMIT_FLAG = true;
						}
					}
					else
					{
						if (!MPS_LOX_LO_LVL_LIQ_SES4_DSBL_FLG)
						{
							LO2_SENSOR_4_DRY_FLAG = true;
						}
					}
				}
			}

			if ((LO2_SENSOR_1_DRY_FLAG && LO2_SENSOR_2_DRY_FLAG) ||
				(LO2_SENSOR_1_DRY_FLAG && LO2_SENSOR_3_DRY_FLAG) ||
				(LO2_SENSOR_1_DRY_FLAG && LO2_SENSOR_4_DRY_FLAG) ||
				(LO2_SENSOR_2_DRY_FLAG && LO2_SENSOR_3_DRY_FLAG) ||
				(LO2_SENSOR_2_DRY_FLAG && LO2_SENSOR_4_DRY_FLAG) ||
				(LO2_SENSOR_3_DRY_FLAG && LO2_SENSOR_4_DRY_FLAG))
			{
				if (LowLevelLO2timer == -1)// HACK first pass check
				{
					if (((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) && (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1)) ||
						((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) && (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1)) ||
						((ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1) && (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1)))
					{
						WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
						oapiWriteLogV( "MECO LOX Low Level Cutoff @ MET %.2f", STS()->GetMET() );
					}
					else
					{
						if (ReadCOMPOOL_IS( SCP_K_CMD ) > 67)
						{
							WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
							oapiWriteLogV( "MECO LOX Low Level Cutoff @ MET %.2f", STS()->GetMET() );
						}
						else
						{
							// TODO stuck check
							if ((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1))
							{
								// TODO set NOM timer
								LowLevelLO2timer = simt + ReadCOMPOOL_SD( SCP_NOM_LO2_LL_T_DELAY_L );
							}
							else
							{
								// TODO RTLS check
								if ((ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) >= 68) || (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) >= 68) || (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) >= 68))
								{
									WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
									oapiWriteLogV( "MECO LOX Low Level Cutoff @ MET %.2f", STS()->GetMET() );
								}
								else
								{
									if (((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) && (ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) > 5)) ||
										((ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1) && (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) > 5)) ||
										((ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1) && (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) > 5)))
									{
										WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
										oapiWriteLogV( "MECO LOX Low Level Cutoff @ MET %.2f", STS()->GetMET() );
									}
									else
									{
										// TODO set PTM timer
										LowLevelLO2timer = simt + ReadCOMPOOL_SD( SCP_PTM_LO2_LL_T_DELAY_N );
									}
								}
							}
						}
					}
				}
				else
				{
					if (LowLevelLO2timer <= simt)
					{
						WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
						oapiWriteLogV( "MECO LOX Low Level Cutoff @ MET %.2f", STS()->GetMET() );
					}
				}
			}

			if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0)// HACK to bypass LH2 checks if MECO has been set above
			{
				bool LH2_DISABLE_LIMIT_FLAG = false;

				if ((ReadCOMPOOL_IS( SCP_FA3_IOM3_CH0_DATA ) & 0x0040) != 0)// ET - LH2 LOW LEVEL LIQ SENSOR NO. 1
				{
					if (!commfaultFA3)
					{
						if (LowLevel1stRun)
						{
							ET_LH2_LO_LVL_LIQ_SES1_DSBL_FLG = true;
							LH2_DISABLE_LIMIT_FLAG = true;
						}
						else
						{
							if (!ET_LH2_LO_LVL_LIQ_SES1_DSBL_FLG)
							{
								LH2_SENSOR_1_DRY_FLAG = true;
							}
						}
					}
				}

				if ((ReadCOMPOOL_IS( SCP_FA2_IOM3_CH0_DATA ) & 0x0040) != 0)// ET - LH2 LOW LEVEL LIQ SENSOR NO. 2
				{
					if (!commfaultFA2)
					{
						if (LowLevel1stRun)
						{
							if (!LH2_DISABLE_LIMIT_FLAG)
							{
								ET_LH2_LO_LVL_LIQ_SES2_DSBL_FLG = true;
								LH2_DISABLE_LIMIT_FLAG = true;
							}
						}
						else
						{
							if (!ET_LH2_LO_LVL_LIQ_SES2_DSBL_FLG)
							{
								LH2_SENSOR_2_DRY_FLAG = true;
							}
						}
					}
				}

				if ((ReadCOMPOOL_IS( SCP_FA4_IOM3_CH0_DATA ) & 0x0040) != 0)// ET - LH2 LOW LEVEL LIQ SENSOR NO. 3
				{
					if (!commfaultFA4)
					{
						if (LowLevel1stRun)
						{
							if (!LH2_DISABLE_LIMIT_FLAG)
							{
								ET_LH2_LO_LVL_LIQ_SES3_DSBL_FLG = true;
								LH2_DISABLE_LIMIT_FLAG = true;
							}
						}
						else
						{
							if (!ET_LH2_LO_LVL_LIQ_SES3_DSBL_FLG)
							{
								LH2_SENSOR_3_DRY_FLAG = true;
							}
						}
					}
				}

				if ((ReadCOMPOOL_IS( SCP_FA1_IOM3_CH0_DATA ) & 0x0040) != 0)// ET - LH2 LOW LEVEL LIQ SENSOR NO. 4
				{
					if (!commfaultFA1)
					{
						if (LowLevel1stRun)
						{
							if (!LH2_DISABLE_LIMIT_FLAG)
							{
								ET_LH2_LO_LVL_LIQ_SES4_DSBL_FLG = true;
								LH2_DISABLE_LIMIT_FLAG = true;
							}
						}
						else
						{
							if (!ET_LH2_LO_LVL_LIQ_SES4_DSBL_FLG)
							{
								LH2_SENSOR_4_DRY_FLAG = true;
							}
						}
					}
				}

				if ((LH2_SENSOR_1_DRY_FLAG && LH2_SENSOR_2_DRY_FLAG) ||
					(LH2_SENSOR_1_DRY_FLAG && LH2_SENSOR_3_DRY_FLAG) ||
					(LH2_SENSOR_1_DRY_FLAG && LH2_SENSOR_4_DRY_FLAG) ||
					(LH2_SENSOR_2_DRY_FLAG && LH2_SENSOR_3_DRY_FLAG) ||
					(LH2_SENSOR_2_DRY_FLAG && LH2_SENSOR_4_DRY_FLAG) ||
					(LH2_SENSOR_3_DRY_FLAG && LH2_SENSOR_4_DRY_FLAG))
				{
					if (LowLevelLH2timer == -1)// HACK first pass check
					{
						if ((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1))
						{
							// TODO RTLS check
							LowLevelLH2timer = simt + ReadCOMPOOL_SD( SCP_RTLS_LH2_LL_TIME_DELAY_P );
						}
						else
						{
							LowLevelLH2timer = simt + ReadCOMPOOL_SD( SCP_LH2_LL_TIME_DELAY_Q );
						}
					}
					else
					{
						if (LowLevelLH2timer <= simt)
						{
							WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
							oapiWriteLogV( "MECO LH2 Low Level Cutoff @ MET %.2f", STS()->GetMET() );
						}
					}
				}
			}

			LowLevel1stRun = false;
		}

		// H
		for (int i = 0; i < 3; i++)
		{
			if ((ManualShutdownFlag[i] == true) || (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 1))
			{
				if ((ReadCOMPOOL_AIS( SCP_MESHDN, i + 1, 3 ) == 1) || (ReadCOMPOOL_AIS( SCP_MEPSTSHDN, i + 1, 3 ) == 1))
				{
					ShutdownCommandIssued[i] = true;
				}
				else
				{
					if (ShutdownFlag_A[i] == true)
					{
						// HACK added if and commented below to compensate delays in getting engine data
						if (ShutdownCommandIssued[i] == false)
						{
							WriteCOMPOOL_AIS( SCP_MESHDNCMD, i + 1, 1, 3 );
							//ShutdownFlag_A[i] = false;
							ShutdownCommandIssued[i] = true;
						}
					}
					else
					{
						WriteCOMPOOL_AIS( SCP_MESHDNENA, i + 1, 1, 3 );
						ShutdownFlag_A[i] = true;
					}
				}
			}
		}

		// step 30
		if ((ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0) && (ManualShutdownFlag[0] == true) && (ManualShutdownFlag[1] == true) && (ManualShutdownFlag[2] == true))
		{
			WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
			WriteCOMPOOL_IS( SCP_MECO_CONFIRMED, 1 );
			timerMECOConfirmed = simt + TIME_TO_ZERO_THRUST;

			// open LV10
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0004 );// L He XOVR OP

			WriteCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA ) | 0x8000 );// reset event timer

			oapiWriteLogV( "MECO Confirmed (PB) @ MET %.2f @ %.2f%% Prop", STS()->GetMET(), STS()->GetETPropellant_B() );
		}

		// K
		if ((ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0) && (
			((ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 0)) ||
			((ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 1) && (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 0)) ||
			((ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 1) && (ReadCOMPOOL_IS( SCP_ME3_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 0)) ||
			((ReadCOMPOOL_IS( SCP_ME1_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_IS( SCP_ME2_CH_PRESS_FDBK ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 0)) ||
			(ReadCOMPOOL_IS( SCP_MM_CODE_104 ) == 1)))
		{
			WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
			WriteCOMPOOL_IS( SCP_MECO_CONFIRMED, 1 );
			timerMECOConfirmed = simt + TIME_TO_ZERO_THRUST;

			// open LV10
			WriteCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA, ReadCOMPOOL_IS( SCP_FA2_IOM12_CH0_DATA ) | 0x0004 );// L He XOVR OP

			WriteCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA ) | 0x8000 );// reset event timer

			oapiWriteLogV( "MECO Confirmed @ MET %.2f @ %.2f%% Prop", STS()->GetMET(), STS()->GetETPropellant_B() );
		}

		if ((timerMECOConfirmed <= simt) && (ReadCOMPOOL_IS( SCP_ME_ZERO ) == 0))
		{
			WriteCOMPOOL_IS( SCP_ME_ZERO, 1 );

			oapiWriteLogV( "Zero Thrust @ MET %.2f", STS()->GetMET() );
		}
		return;
	}

	/*bool SSME_Operations::OnParseLine( const char* keyword, const char* value )
	{
		int config = 0;

		if (!_stricmp( keyword, "LO2LowLevelSensorDsblFlag_1" ))
		{
			sscanf_s( value, "%d", &config );
			LO2LowLevelSensorDsblFlag[0] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LO2LowLevelSensorDsblFlag_2" ))
		{
			sscanf_s( value, "%d", &config );
			LO2LowLevelSensorDsblFlag[1] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LO2LowLevelSensorDsblFlag_3" ))
		{
			sscanf_s( value, "%d", &config );
			LO2LowLevelSensorDsblFlag[2] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LO2LowLevelSensorDsblFlag_4" ))
		{
			sscanf_s( value, "%d", &config );
			LO2LowLevelSensorDsblFlag[3] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LH2LowLevelSensorDsblFlag_1" ))
		{
			sscanf_s( value, "%d", &config );
			LH2LowLevelSensorDsblFlag[0] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LH2LowLevelSensorDsblFlag_2" ))
		{
			sscanf_s( value, "%d", &config );
			LH2LowLevelSensorDsblFlag[1] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LH2LowLevelSensorDsblFlag_3" ))
		{
			sscanf_s( value, "%d", &config );
			LH2LowLevelSensorDsblFlag[2] = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LH2LowLevelSensorDsblFlag_4" ))
		{
			sscanf_s( value, "%d", &config );
			LH2LowLevelSensorDsblFlag[3] = (config != 0);
			return true;
		}
		return false;
	}

	void SSME_Operations::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "LO2LowLevelSensorDsblFlag_1", (int)LO2LowLevelSensorDsblFlag[0] );
		oapiWriteScenario_int( scn, "LO2LowLevelSensorDsblFlag_2", (int)LO2LowLevelSensorDsblFlag[1] );
		oapiWriteScenario_int( scn, "LO2LowLevelSensorDsblFlag_3", (int)LO2LowLevelSensorDsblFlag[2] );
		oapiWriteScenario_int( scn, "LO2LowLevelSensorDsblFlag_4", (int)LO2LowLevelSensorDsblFlag[3] );

		oapiWriteScenario_int( scn, "LH2LowLevelSensorDsblFlag_1", (int)LH2LowLevelSensorDsblFlag[0] );
		oapiWriteScenario_int( scn, "LH2LowLevelSensorDsblFlag_2", (int)LH2LowLevelSensorDsblFlag[1] );
		oapiWriteScenario_int( scn, "LH2LowLevelSensorDsblFlag_3", (int)LH2LowLevelSensorDsblFlag[2] );
		oapiWriteScenario_int( scn, "LH2LowLevelSensorDsblFlag_4", (int)LH2LowLevelSensorDsblFlag[3] );
		return;
	}*/
}
