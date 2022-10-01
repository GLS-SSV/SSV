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
********************************************/
#include "SSME_Operations.h"
#include "..\Atlantis.h"
#include "SSME_SOP.h"
#include "IO_Control.h"
#include <cassert>


namespace dps
{
	// HACK only know the first 2 for sure, the rest is guess
	constexpr double NOM_LO2_LOW_LVL_TIME_DELAY_L = 0.358;// sec
	constexpr double TWOENG_LO2_LOW_LVL_TIME_DELAY_L = 0;// sec
	constexpr double ONEENG_LO2_LOW_LVL_TIME_DELAY_L = 0;// sec

	constexpr double NOM_LH2_LOW_LVL_TIME_DELAY_L = 0;// sec
	constexpr double TWOENG_LH2_LOW_LVL_TIME_DELAY_L = 0;// sec
	constexpr double ONEENG_LH2_LOW_LVL_TIME_DELAY_L = 0;// sec

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

		LowLevelSensorArm = false;
		LO2LowLevelSensorDryFlag[0] = false;
		LO2LowLevelSensorDryFlag[1] = false;
		LO2LowLevelSensorDryFlag[2] = false;
		LO2LowLevelSensorDryFlag[3] = false;
		LH2LowLevelSensorDryFlag[0] = false;
		LH2LowLevelSensorDryFlag[1] = false;
		LH2LowLevelSensorDryFlag[2] = false;
		LH2LowLevelSensorDryFlag[3] = false;
		LO2LowLevelSensorDsblFlag[0] = false;
		LO2LowLevelSensorDsblFlag[1] = false;
		LO2LowLevelSensorDsblFlag[2] = false;
		LO2LowLevelSensorDsblFlag[3] = false;
		LH2LowLevelSensorDsblFlag[0] = false;
		LH2LowLevelSensorDsblFlag[1] = false;
		LH2LowLevelSensorDsblFlag[2] = false;
		LH2LowLevelSensorDsblFlag[3] = false;
		LowLevel1stRun = true;
		LowLevelLO2timer = -1;
		LowLevelLH2timer = -1;

		ZeroThrust = false;

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
						pIO_Control->SetCommand( ME1_LOX_PVLV_CL_A + i, false );
						pIO_Control->SetCommand( ME1_LOX_PVLV_CL_B + i, false );
						pIO_Control->SetCommand( ME1_LH2_PVLV_CL + i, false );

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
							pIO_Control->SetCommand( ME1_LOX_PVLV_OP_A + i, false );
							pIO_Control->SetCommand( ME1_LOX_PVLV_OP_B + i, false );
							pIO_Control->SetCommand( ME1_LOX_PVLV_CL_A + i, true );
							pIO_Control->SetCommand( ME1_LOX_PVLV_CL_B + i, true );

							if (timerLH2PVLV[i] == -1)
							{
								timerLH2PVLV[i] = simt + TIME_DELAY_LH2_PVLV_CL;
							}

							if (timerLH2PVLV[i] <= simt)
							{
								pIO_Control->SetCommand( ME1_LH2_PVLV_OP + i, false );
								pIO_Control->SetCommand( ME1_LH2_PVLV_CL + i, true );

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
								pSSME_SOP->SetLimitInhibitCommandFlag( otherSSMEs[i][0] + 1 );
								pSSME_SOP->SetLimitInhibitCommandFlag( otherSSMEs[i][1] + 1 );

								counter_DFH[i]++;
							}
						}
						else
						{
							if (counter_CEG[i] < 3)
							{
								// ENA me
								pSSME_SOP->SetLimitEnableCommandFlag( i + 1 );

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
						pSSME_SOP->SetLimitEnableCommandFlag( 1 );
						pSSME_SOP->SetLimitEnableCommandFlag( 2 );
						pSSME_SOP->SetLimitEnableCommandFlag( 3 );

						counter_A++;
					}
				}
				else
				{
					// INH
					counter_A = 0;

					if (counter_B < 3)
					{
						if (ManualShutdownFlag[0] == false) pSSME_SOP->SetLimitInhibitCommandFlag( 1 );
						if (ManualShutdownFlag[1] == false) pSSME_SOP->SetLimitInhibitCommandFlag( 2 );
						if (ManualShutdownFlag[2] == false) pSSME_SOP->SetLimitInhibitCommandFlag( 3 );

						counter_B++;
					}
				}
			}

			// F
		}

		// G

		if ((LowLevelSensorArm == true) && (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0))
		{
			if (LowLevel1stRun == false)
			{
				// 2 dry -> MECO
				int LO2count = 0;
				int LH2count = 0;

				for (int i = 0; i < 4; i++)
				{
					// LOX
					if (dipLO2LowLevelSensor[i].IsSet( 0.3f ) == false) LO2LowLevelSensorDryFlag[i] = true;
					if ((LO2LowLevelSensorDryFlag[i] == true) && (LO2LowLevelSensorDsblFlag[i] == false)) LO2count++;

					// LH2
					if (dipLH2LowLevelSensor[i].IsSet( 0.3f ) == false) LH2LowLevelSensorDryFlag[i] = true;
					if ((LH2LowLevelSensorDryFlag[i] == true) && (LH2LowLevelSensorDsblFlag[i] == false)) LH2count++;
				}

				if ((LO2count >= 2) && (LowLevelLO2timer == -1))
				{
					switch (ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) + ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) + ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ))
					{
						case 0:
							LowLevelLO2timer = simt + NOM_LO2_LOW_LVL_TIME_DELAY_L;
							break;
						case 1:
							LowLevelLO2timer = simt + TWOENG_LO2_LOW_LVL_TIME_DELAY_L;
							break;
						case 2:
							LowLevelLO2timer = simt + ONEENG_LO2_LOW_LVL_TIME_DELAY_L;
							break;
					}
				}
				if ((LowLevelLO2timer <= simt) && (LowLevelLO2timer != -1))
				{
					WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );

					oapiWriteLogV( "MECO LOX Low Level Cutoff @ MET %.2f", STS()->GetMET() );
				}

				if ((LH2count >= 2) && (LowLevelLH2timer == -1))
				{
					switch (ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) + ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) + ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ))
					{
						case 0:
							LowLevelLH2timer = simt + NOM_LH2_LOW_LVL_TIME_DELAY_L;
							break;
						case 1:
							LowLevelLH2timer = simt + TWOENG_LH2_LOW_LVL_TIME_DELAY_L;
							break;
						case 2:
							LowLevelLH2timer = simt + ONEENG_LH2_LOW_LVL_TIME_DELAY_L;
							break;
					}
				}
				if ((LowLevelLH2timer <= simt) && (LowLevelLH2timer != -1))
				{
					WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );

					oapiWriteLogV( "MECO LH2 Low Level Cutoff @ MET %.2f", STS()->GetMET() );
				}
			}
			else
			{
				// 1st run, disable 1 dry (failed) sensor (if any)
				oapiWriteLogV( "Low Level Sensors Arm @ MET %.2f", STS()->GetMET() );

				// LOX
				for (int i = 0; i < 4; i++)
				{
					if (dipLO2LowLevelSensor[i].IsSet( 0.3f ) == false)
					{
						LO2LowLevelSensorDsblFlag[i] = true;

						oapiWriteLogV( "LOX Low Level Sensor %d disabled", i + 1 );
						break;
					}
				}

				// LH2
				for (int i = 0; i < 4; i++)
				{
					if (dipLH2LowLevelSensor[i].IsSet( 0.3f ) == false)
					{
						LH2LowLevelSensorDsblFlag[i] = true;

						oapiWriteLogV( "LH2 Low Level Sensor %d disabled", i + 1 );
						break;
					}
				}

				LowLevel1stRun = false;
			}
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
							pSSME_SOP->SetShutdownCommandFlag( i + 1 );
							//ShutdownFlag_A[i] = false;
							ShutdownCommandIssued[i] = true;
						}
					}
					else
					{
						pSSME_SOP->SetShutdownEnableCommandFlag( i + 1 );
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

			pIO_Control->SetCommand( PNEU_L_HE_XOVR_OP, true );// open LV10

			WriteCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA ) | 0x0001 );// reset event timer

			oapiWriteLogV( "MECO Confirmed (PB) @ MET %.2f @ %.2f%% Prop", STS()->GetMET(), STS()->GetETPropellant_B() );
		}

		// K
		if ((ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0) && (
			((pSSME_SOP->GetPercentChamberPressVal( 1 ) < 30) && (pSSME_SOP->GetPercentChamberPressVal( 2 ) < 30) && (pSSME_SOP->GetPercentChamberPressVal( 3 ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 0)) ||
			((ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 1) && (pSSME_SOP->GetPercentChamberPressVal( 2 ) < 30) && (pSSME_SOP->GetPercentChamberPressVal( 3 ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 0)) ||
			((pSSME_SOP->GetPercentChamberPressVal( 1 ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 1) && (pSSME_SOP->GetPercentChamberPressVal( 3 ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 0)) ||
			((pSSME_SOP->GetPercentChamberPressVal( 1 ) < 30) && (pSSME_SOP->GetPercentChamberPressVal( 2 ) < 30) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) == 1) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ) == 0) && (ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ) == 0)) ||
			(GetMajorMode() == 104)))
		{
			WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );
			WriteCOMPOOL_IS( SCP_MECO_CONFIRMED, 1 );
			timerMECOConfirmed = simt + TIME_TO_ZERO_THRUST;

			pIO_Control->SetCommand( PNEU_L_HE_XOVR_OP, true );// open LV10

			WriteCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM5_CH1_DATA ) | 0x0001 );// reset event timer

			oapiWriteLogV( "MECO Confirmed @ MET %.2f @ %.2f%% Prop", STS()->GetMET(), STS()->GetETPropellant_B() );
		}

		if ((timerMECOConfirmed <= simt) && (ZeroThrust == false))
		{
			ZeroThrust = true;

			oapiWriteLogV( "Zero Thrust @ MET %.2f", STS()->GetMET() );
		}

		// HACK makeshift DSC for FCV operation (no capability yet to reasign ullage sensors)
		if ((dipLO2UllagePressureSensor[0].GetVoltage() * 10) < 34.7) pIO_Control->SetCommand( GOX_FCV_1, true );
		else if ((dipLO2UllagePressureSensor[0].GetVoltage() * 10) > 39.7) pIO_Control->SetCommand( GOX_FCV_1, false );

		if ((dipLO2UllagePressureSensor[1].GetVoltage() * 10) < 34.7) pIO_Control->SetCommand( GOX_FCV_2, true );
		else if ((dipLO2UllagePressureSensor[1].GetVoltage() * 10) > 39.7) pIO_Control->SetCommand( GOX_FCV_2, false );

		if ((dipLO2UllagePressureSensor[2].GetVoltage() * 10) < 34.7) pIO_Control->SetCommand( GOX_FCV_3, true );
		else if ((dipLO2UllagePressureSensor[2].GetVoltage() * 10) > 39.7) pIO_Control->SetCommand( GOX_FCV_3, false );

		if (((dipLH2UllagePressureSensor[0].GetVoltage() * 8) + 12) < 32.6) pIO_Control->SetCommand( GH2_FCV_1, true );
		else if (((dipLH2UllagePressureSensor[0].GetVoltage() * 8) + 12) > 33.4) pIO_Control->SetCommand( GH2_FCV_1, false );

		if (((dipLH2UllagePressureSensor[1].GetVoltage() * 8) + 12) < 32.6) pIO_Control->SetCommand( GH2_FCV_2, true );
		else if (((dipLH2UllagePressureSensor[1].GetVoltage() * 8) + 12) > 33.4) pIO_Control->SetCommand( GH2_FCV_2, false );

		if (((dipLH2UllagePressureSensor[2].GetVoltage() * 8) + 12) < 32.6) pIO_Control->SetCommand( GH2_FCV_3, true );
		else if (((dipLH2UllagePressureSensor[2].GetVoltage() * 8) + 12) > 33.4) pIO_Control->SetCommand( GH2_FCV_3, false );

		return;
	}

	void SSME_Operations::Realize( void )
	{
		DiscreteBundle *pBundle = BundleManager()->CreateBundle( "ET_LOX_SENSORS", 16 );
		dipLO2LowLevelSensor[0].Connect( pBundle, 0 );
		dipLO2LowLevelSensor[1].Connect( pBundle, 1 );
		dipLO2LowLevelSensor[2].Connect( pBundle, 2 );
		dipLO2LowLevelSensor[3].Connect( pBundle, 3 );
		dipLO2UllagePressureSensor[0].Connect( pBundle, 12 );
		dipLO2UllagePressureSensor[1].Connect( pBundle, 13 );
		dipLO2UllagePressureSensor[2].Connect( pBundle, 14 );
		dipLO2UllagePressureSensor[3].Connect( pBundle, 15 );

		pBundle = BundleManager()->CreateBundle( "ET_LH2_SENSORS", 16 );
		dipLH2LowLevelSensor[0].Connect( pBundle, 0 );
		dipLH2LowLevelSensor[1].Connect( pBundle, 1 );
		dipLH2LowLevelSensor[2].Connect( pBundle, 2 );
		dipLH2LowLevelSensor[3].Connect( pBundle, 3 );
		dipLH2UllagePressureSensor[0].Connect( pBundle, 12 );
		dipLH2UllagePressureSensor[1].Connect( pBundle, 13 );
		dipLH2UllagePressureSensor[2].Connect( pBundle, 14 );
		dipLH2UllagePressureSensor[3].Connect( pBundle, 15 );

		pSSME_SOP = dynamic_cast<SSME_SOP*> (FindSoftware( "SSME_SOP" ));
		assert( (pSSME_SOP != NULL) && "SSME_Operations::Realize.pSSME_SOP" );
		pIO_Control = dynamic_cast<IO_Control*> (FindSoftware( "IO_Control" ));
		assert( (pIO_Control != NULL) && "SSME_Operations::Realize.pIO_Control" );
		return;
	}

	/*bool SSME_Operations::OnParseLine( const char* keyword, const char* value )
	{
		int config = 0;

		if (!_stricmp( keyword, "ZeroThrust" ))
		{
			sscanf_s( value, "%d", &config );
			ZeroThrust = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LowLevelSensorArm" ))
		{
			sscanf_s( value, "%d", &config );
			LowLevelSensorArm = (config != 0);
			return true;
		}
		else if (!_stricmp( keyword, "LO2LowLevelSensorDsblFlag_1" ))
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
		oapiWriteScenario_int( scn, "ZeroThrust", (int)ZeroThrust );

		oapiWriteScenario_int( scn, "LowLevelSensorArm", (int)LowLevelSensorArm );

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

	bool SSME_Operations::OnMajorModeChange( unsigned int newMajorMode )
	{
		switch (newMajorMode)
		{
			case 102:
			case 103:
			case 104:
			case 601:
				return true;
			default:
				return false;
		}
	}


	void SSME_Operations::SetLowLevelSensorArmFlag( void )
	{
		LowLevelSensorArm = true;
		return;
	}

	void SSME_Operations::SetLO2LowLevelSensorDsblFlag( int num )
	{
		assert( (num >= 1) && (num <= 4) && "SSME_Operations::SetLO2LowLevelSensorDsblFlag.num" );
		LO2LowLevelSensorDsblFlag[num - 1] = true;
		return;
	}

	void SSME_Operations::SetLH2LowLevelSensorDsblFlag( int num )
	{
		assert( (num >= 1) && (num <= 4) && "SSME_Operations::SetLH2LowLevelSensorDsblFlag.num" );
		LH2LowLevelSensorDsblFlag[num - 1] = true;
		return;
	}

	bool SSME_Operations::GetMECOConfirmedFlag( void ) const// HACK for IDP only
	{
		return (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 1);
	}

	bool SSME_Operations::GetZeroThrustFlag( void ) const
	{
		return ZeroThrust;
	}
}