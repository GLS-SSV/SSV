/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/24   GLS
2021/12/19   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/02   GLS
2022/04/26   GLS
2022/08/05   GLS
********************************************/
#include "SSMEControllerSW_AD08.h"
#include "DigitalComputerUnit.h"
#include "ComputerInterfaceElectronics.h"
#include <MathSSV.h>
#include "MPSdefs.h"


namespace mps
{
	// AD08
	// SSME Controller Block II
	// STS-125
	SSMEControllerSW_AD08::SSMEControllerSW_AD08( DigitalComputerUnit* DCU ):SSMEControllerSW( DCU )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEControllerSW_AD08::SSMEControllerSW_AD08 in" );
#endif// _MPSDEBUG

		LoadStartValveSchedule();
		LoadShutdownValveSchedule();

		fptrSensorInput = &SSMEControllerSW_AD08::SensorInput;
		fptrSensorScale = &SSMEControllerSW_AD08::SensorScale;
		fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_EngineReady;
		fptrMonitorSDLimits = NULL;
		fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_EngineReady;
		fptrCommandActuators = &SSMEControllerSW_AD08::CommandActuators;
		fptrCommandONOFFDevices = &SSMEControllerSW_AD08::CommandONOFFDevices;
		fptrOutputVDT = &SSMEControllerSW_AD08::OutputVDT;
		Set_ESW_SelfTestStatus( ESW_EngineOK );
		Set_ESW_Mode( ESW_StartPrep_EngineReady );
		Set_ESW_Phase( ESW_StartPrep );
		Set_ESW_LimitControlStatus( ESW_Enable );
		DCU->RAM[RAM_AD08_CCV_CMD] = 4095;
		DCU->RAM[RAM_AD08_MFV_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_CMD] = 0;
		DCU->RAM[RAM_AD08_TIME_ESC] = 0;
		DCU->RAM[RAM_AD08_TIME_STDN] = 0;
		DCU->RAM[RAM_AD08_CH] = DCU->ch;

		DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 1;
		DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 1;
		DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 1;
		DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 1;
		DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 1;

#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEControllerSW_AD08::SSMEControllerSW_AD08 out" );
#endif// _MPSDEBUG
		return;
	}

	SSMEControllerSW_AD08::~SSMEControllerSW_AD08( void )
	{
		return;
	}

	int SSMEControllerSW_AD08::GetConfig( void )
	{
		if (fptrVehicleCommands == &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN3) return 1;
		if (fptrVehicleCommands == &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN4) return 2;
		if (fptrVehicleCommands == &SSMEControllerSW_AD08::VehicleCommands_StartPrep_EngineReady) return 3;
		if (fptrVehicleCommands == &SSMEControllerSW_AD08::VehicleCommands_PostShutdown_Standby) return 4;
		return 4;// default to post-shutdown standby
	}

	void SSMEControllerSW_AD08::SetConfig( int config )
	{
		switch (config)
		{
			case 1:
				fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN3;
				fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN3;
				Set_ESW_Mode( ESW_StartPrep_PSN3 );
				Set_ESW_Phase( ESW_StartPrep );
				DCU->RAM[RAM_AD08_CCV_CMD] = 0;
				DCU->RAM[RAM_AD08_MFV_CMD] = 0;
				DCU->RAM[RAM_AD08_MOV_CMD] = 0;
				DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
				DCU->RAM[RAM_AD08_OPOV_CMD] = 0;

				DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;
				break;
			case 2:
				fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN4;
				fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN4;
				Set_ESW_Mode( ESW_StartPrep_PSN4 );
				Set_ESW_Phase( ESW_StartPrep );
				DCU->RAM[RAM_AD08_CCV_CMD] = 4095;
				DCU->RAM[RAM_AD08_MFV_CMD] = 0;
				DCU->RAM[RAM_AD08_MOV_CMD] = 0;
				DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
				DCU->RAM[RAM_AD08_OPOV_CMD] = 0;
				break;
			case 3:
				fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_EngineReady;
				fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_EngineReady;
				Set_ESW_Mode( ESW_StartPrep_EngineReady );
				Set_ESW_Phase( ESW_StartPrep );
				DCU->RAM[RAM_AD08_CCV_CMD] = 4095;
				DCU->RAM[RAM_AD08_MFV_CMD] = 0;
				DCU->RAM[RAM_AD08_MOV_CMD] = 0;
				DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
				DCU->RAM[RAM_AD08_OPOV_CMD] = 0;
				break;
			case 4:
				fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_PostShutdown_Standby;
				fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_PostShutdown_Standby;
				Set_ESW_Mode( ESW_PostShutdown_Standby );
				Set_ESW_Phase( ESW_PostShutdown );
				DCU->RAM[RAM_AD08_CCV_CMD] = 0;
				DCU->RAM[RAM_AD08_MFV_CMD] = 0;
				DCU->RAM[RAM_AD08_MOV_CMD] = 0;
				DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
				DCU->RAM[RAM_AD08_OPOV_CMD] = 0;
				break;
		}
		return;
	}

	void SSMEControllerSW_AD08::GetTime( void )
	{
		DCU->RAM[RAM_AD08_TREF1] = (unsigned short)DCU->time;
		DCU->RAM[RAM_AD08_TREF2] = (unsigned short)((DCU->time - DCU->RAM[RAM_AD08_TREF1]) * 10000);
		return;
	}

	void SSMEControllerSW_AD08::AddFID( unsigned short FID, unsigned short Delimiter )
	{
		int count = 0;
		while (count < 8)
		{
			if (DCU->RAM[RAM_AD08_FID_BUFFER + count] == 0)
			{
				DCU->RAM[RAM_AD08_FID_BUFFER + count] = (FID << 9) + Delimiter;
				return;
			}
			count++;
		}
		return;
	}

	unsigned short SSMEControllerSW_AD08::GetFID( void )
	{
		int count = 0;
		while (count < 8)
		{
			if (DCU->RAM[RAM_AD08_FID_BUFFER + count] != 0)
			{
				unsigned short FID = DCU->RAM[RAM_AD08_FID_BUFFER + count];
				DCU->RAM[RAM_AD08_FID_BUFFER + count] = 0;
				return FID;
			}
			count++;
		}
		return 0;
	}

	void SSMEControllerSW_AD08::RotateCommand( void )
	{
		DCU->RAM[RAM_AD08_PRVCMD] = DCU->RAM[RAM_AD08_CURCMD];
		DCU->RAM[RAM_AD08_CURCMD] = DCU->RAM[RAM_AD08_VALIDCMD];
		return;
	}

	void SSMEControllerSW_AD08::ValveSchedule( int tableaddr, int cmdaddr, int timeaddr, int currentposaddr )
	{
		int count = tableaddr;

		while (count <= tableaddr + 48)
		{
			if ((DCU->RAM[count] <= DCU->RAM[timeaddr]) && (DCU->RAM[count + 3] > DCU->RAM[timeaddr])) break;
			count += 3;
		}

		DCU->RAM[cmdaddr] = DCU->RAM[currentposaddr];
		if (DCU->RAM[count + 2] > DCU->RAM[timeaddr])
		{
			if (DCU->RAM[currentposaddr] < DCU->RAM[count + 1])// open
			{
				DCU->RAM[cmdaddr] += (unsigned short)Round( DCU->dt * 10000 * ((double)(DCU->RAM[count + 1] - DCU->RAM[currentposaddr]) / (DCU->RAM[count + 2] - DCU->RAM[timeaddr])) );
				if (DCU->RAM[cmdaddr] > DCU->RAM[count + 1]) DCU->RAM[cmdaddr] = DCU->RAM[count + 1];
			}
			if (DCU->RAM[currentposaddr] > DCU->RAM[count + 1])// close
			{
				DCU->RAM[cmdaddr] -= (unsigned short)Round( DCU->dt * 10000 * ((double)(DCU->RAM[currentposaddr] - DCU->RAM[count + 1]) / (DCU->RAM[count + 2] - DCU->RAM[timeaddr])) );
				if ((signed short)DCU->RAM[cmdaddr] < DCU->RAM[count + 1]) DCU->RAM[cmdaddr] = DCU->RAM[count + 1];
			}
		}
		else
		{
			DCU->RAM[cmdaddr] = DCU->RAM[count + 1];
		}

		if (DCU->RAM[cmdaddr] > 4095) DCU->RAM[cmdaddr] = 4095;
		return;
	}

	void SSMEControllerSW_AD08::LoadStartValveSchedule( void )
	{
		// HACK "load" ignition valve commands
		// space for 16 cmds per vlv
		// cmd time (from ESC, sec * 10000) / cmd pos / time to be at pos (from ESC, sec * 10000)

		// CCV
		DCU->RAM[RAM_AD08_IGNT_CCV_POS] = 0;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 1] = 4095;// 100 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 2] = 1;

		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 3] = 14600;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 4] = 2867;// 70 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 5] = 17800;

		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 6] = 24000;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 7] = 2088;// 51 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 8] = 26000;

		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 9] = 28500;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 10] = 4095;// 100 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 11] = 37200;

		DCU->RAM[RAM_AD08_IGNT_CCV_POS + 12] = 65535;// final (max) time

		// MFV
		DCU->RAM[RAM_AD08_IGNT_MFV_POS] = 0;
		DCU->RAM[RAM_AD08_IGNT_MFV_POS + 1] = 4095;// 100 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_MFV_POS + 2] = 7100;

		DCU->RAM[RAM_AD08_IGNT_MFV_POS + 3] = 65535;

		// MOV
		DCU->RAM[RAM_AD08_IGNT_MOV_POS] = 0;
		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 1] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 2] = 1;

		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 3] = 2000;
		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 4] = 2416;// 59 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 5] = 12900;

		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 6] = 24900;
		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 7] = 4095;// 100 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 8] = 39400;

		DCU->RAM[RAM_AD08_IGNT_MOV_POS + 9] = 65535;

		// FPOV
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS] = 0;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 1] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 2] = 1;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 3] = 1000;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 4] = 2293;// 56 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 5] = 4290;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 6] = 7200;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 7] = 1925;// 47 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 8] = 7900;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 9] = 7900;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 10] = 2211;// 54 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 11] = 9500;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 12] = 11500;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 13] = 2088;// 51 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 14] = 12100;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 15] = 15200;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 16] = 1966;// 48 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 17] = 17700;// ?????

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 18] = 17700;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 19] = 2170;// 53 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 20] = 19300;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 21] = 20500;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 22] = 2048;// 50 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 23] = 21400;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 24] = 24200;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 25] = 2318;// 56.6 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 26] = 24800;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 27] = 24800;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 28] = 2375;// 58 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 29] = 27700;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 30] = 27700;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 31] = 2744;// 67 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 32] = 33800;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 33] = 33800;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 34] = 3112;// 76 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 35] = 37500;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 36] = 37500;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 37] = 3206;// 78.298 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 38] = 43000;

		DCU->RAM[RAM_AD08_IGNT_FPOV_POS + 39] = 65535;

		// OPOV
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS] = 0;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 1] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 2] = 1;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 3] = 1200;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 4] = 1147;// 28 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 5] = 3000;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 6] = 3000;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 7] = 1556;// 38 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 8] = 7400;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 9] = 7400;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 10] = 2150;// 52.5 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 11] = 9000;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 12] = 10800;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 13] = 1720;// 42 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 14] = 11600;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 15] = 11600;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 16] = 1638;// 40 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 17] = 15500;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 18] = 15500;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 19] = 1536;// 37.5 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 20] = 16000;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 21] = 17700;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 22] = 1392;// 34 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 23] = 20900;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 24] = 20900;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 25] = 1802;// 44 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 26] = 21800;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 27] = 24000;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 28] = 1966;// 48 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 29] = 24600;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 30] = 24600;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 31] = 2048;// 50 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 32] = 28400;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 33] = 28400;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 34] = 2334;// 57 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 35] = 33700;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 36] = 33700;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 37] = 2580;// 63 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 38] = 37900;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 39] = 37900;
		//DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 40] = 2612;// 63.797 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 40] = 2630;// 64.234 * 40.95;
		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 41] = 42900;

		DCU->RAM[RAM_AD08_IGNT_OPOV_POS + 42] = 65535;
		return;
	}

	void SSMEControllerSW_AD08::LoadShutdownValveSchedule( void )
	{
		// HACK "load" shutdown valve commands (from 100%)
		// space for 16 cmds per vlv
		// cmd time (from STDN, sec * 10000) / cmd pos / time to be at pos (from STDN, sec * 10000)

		// CCV
		DCU->RAM[RAM_AD08_STDN_CCV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 1] = 2848;// 69.545 * 40.95;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 2] = 3260;

		DCU->RAM[RAM_AD08_STDN_CCV_POS + 3] = 6050;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 4] = 3065;// 74.848 * 40.95;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 5] = 7090;

		DCU->RAM[RAM_AD08_STDN_CCV_POS + 6] = 45930;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 7] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 8] = 53140;

		DCU->RAM[RAM_AD08_STDN_CCV_POS + 9] = 65535;// final (max) time

		// MFV
		DCU->RAM[RAM_AD08_STDN_MFV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 1] = 4095;// 100 * 40.95;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 2] = 1;

		DCU->RAM[RAM_AD08_STDN_MFV_POS + 3] = 13290;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 4] = 2515;// 61.406 * 40.95;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 5] = 35180;

		DCU->RAM[RAM_AD08_STDN_MFV_POS + 6] = 45590;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 7] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 8] = 54000;

		DCU->RAM[RAM_AD08_STDN_MFV_POS + 9] = 65535;// final (max) time

		// MOV
		DCU->RAM[RAM_AD08_STDN_MOV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 1] = 3852;// 94.063 * 40.95;
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 2] = 3680;

		DCU->RAM[RAM_AD08_STDN_MOV_POS + 3] = 3680;
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 4] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 5] = 27200;

		DCU->RAM[RAM_AD08_STDN_MOV_POS + 6] = 65535;// final (max) time

		// FPOV
		DCU->RAM[RAM_AD08_STDN_FPOV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 1] = 2438;// 59.545 * 40.95;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 2] = 7130;

		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 3] = 7130;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 4] = 1576;// 38.485 * 40.95;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 5] = 18620;

		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 6] = 18620;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 7] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 8] = 23620;

		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 9] = 65535;// final (max) time

		// OPOV
		DCU->RAM[RAM_AD08_STDN_OPOV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 1] = 2091;// 51.06 * 40.95;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 2] = 2990;

		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 3] = 2990;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 4] = 695;// 16.97 * 40.95;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 5] = 14250;

		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 6] = 14250;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 7] = 0;// 0 * 40.95;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 8] = 15060;

		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 9] = 65535;// final (max) time
		return;
	}

	void SSMEControllerSW_AD08::UpdateShutdownValveSchedule( double dPC )
	{
		if (dPC > (PC_100 - (PC_100 * MPL / 100)))
		{
			// below MPL use "shifted" MPL profile
			double temp = (PC_100 - dPC) / PC_100_C;
			if (temp >= 39)
			{
				DCU->RAM[RAM_AD08_TIME_STDN] = (unsigned short)((100 - temp) / 0.0122);
			}
			else
			{
				if (temp >= 8)
				{
					DCU->RAM[RAM_AD08_TIME_STDN] = (unsigned short)(((50.92 - temp) * 2.6) / 0.0062);
				}
				else
				{
					if (temp >= 0.9538)
					{
						DCU->RAM[RAM_AD08_TIME_STDN] = (unsigned short)(((11.43 - temp) * 4.2) / 0.0008);
					}
					else
					{
						DCU->RAM[RAM_AD08_TIME_STDN] = 55000;
					}
				}
			}

			dPC = PC_100 - (PC_100 * MPL / 100);
		}

		// CCV
		//DCU->RAM[RAM_AD08_STDN_CCV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 1] -= (unsigned short)Round( 0.55825 * dPC );// TODO only do this under 100%
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 2] -= (unsigned short)Round( 1.42094 * dPC );

		DCU->RAM[RAM_AD08_STDN_CCV_POS + 3] -= (unsigned short)Round( 2.72494 * dPC );
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 4] += (unsigned short)Round( 0.00687 * dPC );
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 5] -= (unsigned short)Round( 1.19147 * dPC );

		DCU->RAM[RAM_AD08_STDN_CCV_POS + 6] -= (unsigned short)Round( 2.96765 * dPC );
		//DCU->RAM[RAM_AD08_STDN_CCV_POS + 7] = 0;
		DCU->RAM[RAM_AD08_STDN_CCV_POS + 8] -= (unsigned short)Round( 2.86836 * dPC );

		//DCU->RAM[RAM_AD08_STDN_CCV_POS + 9] = 65535;

		// MFV
		//DCU->RAM[RAM_AD08_STDN_MFV_POS] = 0;
		//DCU->RAM[RAM_AD08_STDN_MFV_POS + 1] = 4095;
		//DCU->RAM[RAM_AD08_STDN_MFV_POS + 2] = 1;

		DCU->RAM[RAM_AD08_STDN_MFV_POS + 3] += (unsigned short)Round( 0.69503 * dPC );
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 4] += (unsigned short)Round( 0.00709 * dPC );
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 5] -= (unsigned short)Round( 13.47015 * dPC );

		DCU->RAM[RAM_AD08_STDN_MFV_POS + 6] -= (unsigned short)Round( 2.43811 * dPC );
		//DCU->RAM[RAM_AD08_STDN_MFV_POS + 7] = 0;
		DCU->RAM[RAM_AD08_STDN_MFV_POS + 8] -= (unsigned short)Round( 2.92352 * dPC );

		//DCU->RAM[RAM_AD08_STDN_MFV_POS + 9] = 65535;

		// MOV
		//DCU->RAM[RAM_AD08_STDN_MOV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 1] += (unsigned short)Round( 0.0141 * dPC );
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 2] -= (unsigned short)Round( 1.22457 * dPC );

		DCU->RAM[RAM_AD08_STDN_MOV_POS + 3] -= (unsigned short)Round( 1.22457 * dPC );
		//DCU->RAM[RAM_AD08_STDN_MOV_POS + 4] = 0;
		DCU->RAM[RAM_AD08_STDN_MOV_POS + 5] += (unsigned short)Round( 0.08605 * dPC );

		//DCU->RAM[RAM_AD08_STDN_MOV_POS + 6] = 65535;

		// FPOV
		//DCU->RAM[RAM_AD08_STDN_FPOV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 1] += (unsigned short)Round( 0.04174 * dPC );
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 2] -= (unsigned short)Round( 5.18512 * dPC );

		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 3] -= (unsigned short)Round( 5.18512 * dPC );
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 4] += (unsigned short)Round( 0.02611 * dPC );
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 5] -= (unsigned short)Round( 5.33957 * dPC );

		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 6] -= (unsigned short)Round( 5.33957 * dPC );
		//DCU->RAM[RAM_AD08_STDN_FPOV_POS + 7] = 0;
		DCU->RAM[RAM_AD08_STDN_FPOV_POS + 8] -= (unsigned short)Round( 5.48299 * dPC );

		//DCU->RAM[RAM_AD08_STDN_FPOV_POS + 9] = 65535;

		// OPOV
		//DCU->RAM[RAM_AD08_STDN_OPOV_POS] = 0;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 1] -= (unsigned short)Round( 0.28285 * dPC );
		//DCU->RAM[RAM_AD08_STDN_OPOV_POS + 2] = 2990;

		//DCU->RAM[RAM_AD08_STDN_OPOV_POS + 3] = 2990;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 4] -= (unsigned short)Round( 0.31488 * dPC );
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 5] -= (unsigned short)Round( 0.51851 * dPC );

		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 6] -= (unsigned short)Round( 0.51851 * dPC );
		//DCU->RAM[RAM_AD08_STDN_OPOV_POS + 7] = 0;
		DCU->RAM[RAM_AD08_STDN_OPOV_POS + 8] -= (unsigned short)Round( 0.81638 * dPC );

		//DCU->RAM[RAM_AD08_STDN_OPOV_POS + 9] = 65535;
		return;
	}

	void SSMEControllerSW_AD08::Interrupt( int num )
	{
		switch (num)
		{
			case INT_PFI:
				return;
			case INT_PRI:
				return;
			case INT_PBDI:
				// desqualify other channel's DCU, IE and OE
				if (DCU->RAM[RAM_AD08_CH] == chA)
				{
					DCU->RAM[RAM_AD08_DCU_B_STATUS] = 1;
					DCU->RAM[RAM_AD08_IE_B_STATUS] = 1;
					DCU->RAM[RAM_AD08_OE_B_STATUS] = 1;
					AddFID( FID_LossOfControllerRedundancy, Delimiter_DCUB );
					AddFID( FID_LossOfControllerRedundancy, Delimiter_IEB );
					AddFID( FID_LossOfControllerRedundancy, Delimiter_OEB );
					SensorsDesqualifyAll( RAM_AD08_SENSOR_B );
				}
				else
				{
					DCU->RAM[RAM_AD08_DCU_A_STATUS] = 1;
					DCU->RAM[RAM_AD08_IE_A_STATUS] = 1;
					DCU->RAM[RAM_AD08_OE_A_STATUS] = 1;
					AddFID( FID_LossOfControllerRedundancy, Delimiter_DCUA );
					AddFID( FID_LossOfControllerRedundancy, Delimiter_IEA );
					AddFID( FID_LossOfControllerRedundancy, Delimiter_OEA );
					SensorsDesqualifyAll( RAM_AD08_SENSOR_A );
					// chB hyd act take over
					DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 1;
					DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 1;
					DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 1;
					DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 1;
					DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 1;
				}
				return;
			case INT_CCVSVAFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_CCV_SEII_A_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_CCVSEIIA );
				DCU->RAM[RAM_AD08_CCV_SEII_A_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
				{
					// if working, switch this valve to OEchB
					DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 1;
				}
				else if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_CCVSVBFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_CCV_SEII_B_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_CCVSEIIB );
				DCU->RAM[RAM_AD08_CCV_SEII_B_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] == 0) return;// chA in control, do nothing

				if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_MFVSVAFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_MFV_SEII_A_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_MFVSEIIA );
				DCU->RAM[RAM_AD08_MFV_SEII_A_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
				{
					// if working, switch this valve to OEchB
					DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 1;
				}
				else if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_MFVSVBFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_MFV_SEII_B_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_MFVSEIIB );
				DCU->RAM[RAM_AD08_MFV_SEII_B_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] == 0) return;// chA in control, do nothing

				if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_MOVSVAFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_MOV_SEII_A_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_MOVSEIIA );
				DCU->RAM[RAM_AD08_MOV_SEII_A_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
				{
					// if working, switch this valve to OEchB
					DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 1;
				}
				else if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else if (Get_ESW_Phase() == ESW_PostShutdown)
				{
					// HACK go to terminate sequence?
					DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;// let go of these 2, so the valve closes
					DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_MOVSVBFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_MOV_SEII_B_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_MOVSEIIB );
				DCU->RAM[RAM_AD08_MOV_SEII_B_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] == 0) return;// chA in control, do nothing

				if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else if (Get_ESW_Phase() == ESW_PostShutdown)
				{
					// HACK go to terminate sequence?
					DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;// let go of these 2, so the valve closes
					DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_FPOVSVAFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_FPOV_SEII_A_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_FPOVSEIIA );
				DCU->RAM[RAM_AD08_FPOV_SEII_A_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
				{
					// if working, switch this valve to OEchB
					DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 1;
				}
				else if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_FPOVSVBFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_FPOV_SEII_B_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_FPOVSEIIB );
				DCU->RAM[RAM_AD08_FPOV_SEII_B_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] == 0) return;// chA in control, do nothing

				if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_OPOVSVAFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_OPOV_SEII_A_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_OPOVSEIIA );
				DCU->RAM[RAM_AD08_OPOV_SEII_A_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
				{
					// if working, switch this valve to OEchB
					DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 1;
				}
				else if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_OPOVSVBFI:
				if ((Get_ESW_Phase() == ESW_Shutdown) && (Get_ESW_Mode() == ESW_Shutdown_FailSafePneumatic)) return;// ignore errors during Pneu S/D

				if (DCU->RAM[RAM_AD08_OPOV_SEII_B_STATUS] == 1) return;// act on the first only
				AddFID( FID_LossOfControllerRedundancy, Delimiter_OPOVSEIIB );
				DCU->RAM[RAM_AD08_OPOV_SEII_B_STATUS] = 1;

				if (DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] == 0) return;// chA in control, do nothing

				if (Get_ESW_Phase() == ESW_Mainstage)
				{
					// hyd lockup
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_HydraulicLockup;
					ChangePhaseMode();// phase/mode change
				}
				else
				{
					// pneu S/D
					DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
					DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
					ChangePhaseMode();// phase/mode change
					DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				}
				return;
			case INT_CMD_RCVD:
				DCU->RAM[RAM_AD08_CMD_RCVD] = 1;
				return;
			default:
				return;
		}
	}

	void SSMEControllerSW_AD08::Executive( void )
	{
		// TODO on first run goto pnumatic s/d, then post s/d stby
		unsigned short retval = 0;

		GetTime();

		// TODO reset own WDTs ONLY when all is working well in this channel
		DCU->CIE->ResetWDT( 0 );
		DCU->CIE->ResetWDT( 1 );

		retval = SelfTest();
		if (retval == 0)
		{
			Set_ESW_SelfTestStatus( ESW_EngineOK );
		}
		else if (retval == 1)
		{
			Set_ESW_SelfTestStatus( ESW_MCF );
		}
		else// assume retval = 2
		{
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
			ChangePhaseMode();// phase/mode change
			DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
		}

		if (fptrSensorInput != NULL) retval = (this->*fptrSensorInput)();

		retval = 0;
		if (fptrSensorScale != NULL) retval = (this->*fptrSensorScale)();
		if (retval != 0)
		{
			// MCF
		}

		if (fptrVehicleCommands != NULL)
		{
			if (DCU->RAM[RAM_AD08_CMD_RCVD] == 1)
			{
				retval = (this->*fptrVehicleCommands)();
				Set_ESW_CommandStatus( retval );
				if (retval == 3)
				{
					// good
					ChangePhaseMode();// phase/mode change
					// execute cmd, change phase/mode as necessary
				}
				DCU->RAM[RAM_AD08_CMD_RCVD] = 0;
			}
			else
			{
				Set_ESW_CommandStatus( ESW_NoCommand );
				Set_ESW_ChannelStatus( ESW_OK );
			}
		}

		if (fptrMonitorSDLimits != NULL)
		{
			retval = (this->*fptrMonitorSDLimits)();
			if (retval != 0)
			{
				Set_ESW_SelfTestStatus( ESW_LimitExceeded );// set Limit Exceeded

				// if limits ena -> sd
				if (Get_ESW_LimitControlStatus() == ESW_Enable)
				{
					if (retval == 1)
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
						ChangePhaseMode();// phase/mode change
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
					}
					else// assume retval = 2
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
						ChangePhaseMode();// phase/mode change
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
					}
				}
			}
		}


		retval = 0;
		if (fptrEngineOperations != NULL) retval = (this->*fptrEngineOperations)();
		if (retval != 0) ChangePhaseMode();// phase/mode change

		retval = 0;
		if (fptrCommandActuators != NULL) retval = (this->*fptrCommandActuators)();
		if (retval == 1)
		{
			// OE chA fail
			DCU->RAM[RAM_AD08_OE_A_STATUS] = 1;
			Set_ESW_SelfTestStatus( ESW_MCF );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEA );
		}
		else if (retval == 2)
		{
			// OE chB fail
			DCU->RAM[RAM_AD08_OE_B_STATUS] = 1;
			Set_ESW_SelfTestStatus( ESW_MCF );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEB );
		}
		else if (retval == 3)
		{
			// both OEs fail
			DCU->RAM[RAM_AD08_OE_A_STATUS] = 1;
			DCU->RAM[RAM_AD08_OE_B_STATUS] = 1;
			Set_ESW_SelfTestStatus( ESW_MCF );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEA );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEB );

			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
			ChangePhaseMode();// phase/mode change
			DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
		}

		retval = 0;
		if (fptrCommandONOFFDevices != NULL) retval = (this->*fptrCommandONOFFDevices)();
		if (retval == 1)
		{
			// OE chA fail
			DCU->RAM[RAM_AD08_OE_A_STATUS] = 1;
			Set_ESW_SelfTestStatus( ESW_MCF );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEA );
		}
		else if (retval == 2)
		{
			// OE chB fail
			DCU->RAM[RAM_AD08_OE_B_STATUS] = 1;
			Set_ESW_SelfTestStatus( ESW_MCF );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEB );
		}
		else if (retval == 3)
		{
			// both OEs fail
			DCU->RAM[RAM_AD08_OE_A_STATUS] = 1;
			DCU->RAM[RAM_AD08_OE_B_STATUS] = 1;
			Set_ESW_SelfTestStatus( ESW_MCF );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEA );
			AddFID( FID_LossOfControllerRedundancy, Delimiter_OEB );

			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
			ChangePhaseMode();// phase/mode change
			DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
		}

		retval = 0;
		if (fptrOutputVDT != NULL) retval = (this->*fptrOutputVDT)();
		/*
		sensor input
		scale sensors

		compare rvdts

		check interupts*

		ie, oe seft test*

		vehicle commands*

		monitor s/d limit params*
		monitor mcc pc
		monitor fuel density
		monitor on/off registers
		monitor thermocouples
		monitor purge & anc
		monitor accels

		engine operations*

		command actuators
		command on/off registers

		esw
		output vdt
		*/
		return;
	}

	unsigned short SSMEControllerSW_AD08::SelfTest( void )
	{
		unsigned short retval = 0;

		// check other channel
		DCU->RAM[RAM_AD08_WDT1] = DCU->CIE->CheckWDTOpposite( 0 );
		DCU->RAM[RAM_AD08_WDT2] = DCU->CIE->CheckWDTOpposite( 1 );

		if ((DCU->RAM[RAM_AD08_WDT1] + DCU->RAM[RAM_AD08_WDT2]) != 0)
		{
			retval = 1;
			if (DCU->RAM[RAM_AD08_CH] == chA)
			{
				if (DCU->RAM[RAM_AD08_DCU_B_STATUS] == 0)// failure detected now, add FID
				{
					DCU->RAM[RAM_AD08_DCU_B_STATUS] = 1;
					AddFID( FID_LossOfControllerRedundancy, Delimiter_DCUB );
				}
			}
			else
			{
				if (DCU->RAM[RAM_AD08_DCU_A_STATUS] == 0)// failure detected now, add FID
				{
					DCU->RAM[RAM_AD08_DCU_A_STATUS] = 1;
					AddFID( FID_LossOfControllerRedundancy, Delimiter_DCUA );
				}
			}
		}

		// TODO test IE and OE
		if (DCU->RAM[RAM_AD08_IE_B_STATUS] == 1)
		{
			retval = 1;
		}

		if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 1)
		{
			retval = 1;
		}

		if (DCU->RAM[RAM_AD08_IE_A_STATUS] == 1)
		{
			retval = 1;
		}

		if (DCU->RAM[RAM_AD08_OE_A_STATUS] == 1)
		{
			retval = 1;
		}
		return retval;
	}

	void SSMEControllerSW_AD08::ChangePhaseMode( void )
	{
		switch (DCU->RAM[RAM_AD08_NXT_PHASE])// phase
		{
			case ESW_Checkout:
				switch (DCU->RAM[RAM_AD08_NXT_MODE])// mode
				{
					case ESW_Checkout_HydraulicConditioning:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_HydraulicConditioning );
						break;
					case ESW_Checkout_Standby:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Checkout_Standby;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Checkout_Standby;
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_Standby );
						break;
					case ESW_Checkout_ActuatorCheckout:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_ActuatorCheckout );
						break;
					case ESW_Checkout_EngineLeakDetection:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_EngineLeakDetection );
						break;
					case ESW_Checkout_IgniterCheckout:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_IgniterCheckout );
						break;
					case ESW_Checkout_PneumaticCheckout:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_PneumaticCheckout );
						break;
					case ESW_Checkout_SensorCheckout:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_SensorCheckout );
						break;
					case ESW_Checkout_ControllerCheckout:
						Set_ESW_Phase( ESW_Checkout );
						Set_ESW_Mode( ESW_Checkout_ControllerCheckout );
						break;
					default:
						break;
				}
				break;
			case ESW_StartPrep:
				switch (DCU->RAM[RAM_AD08_NXT_MODE])// mode
				{
					case ESW_StartPrep_PSN1:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN1;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN1;
						Set_ESW_Phase( ESW_StartPrep );
						Set_ESW_Mode( ESW_StartPrep_PSN1 );
						break;
					case ESW_StartPrep_PSN2:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN2;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN2;
						Set_ESW_Phase( ESW_StartPrep );
						Set_ESW_Mode( ESW_StartPrep_PSN2 );
						break;
					case ESW_StartPrep_PSN3:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN3;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN3;
						Set_ESW_Phase( ESW_StartPrep );
						Set_ESW_Mode( ESW_StartPrep_PSN3 );
						break;
					case ESW_StartPrep_PSN4:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN4;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN4;
						Set_ESW_Phase( ESW_StartPrep );
						Set_ESW_Mode( ESW_StartPrep_PSN4 );
						break;
					case ESW_StartPrep_EngineReady:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_StartPrep_EngineReady;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_StartPrep_EngineReady;
						Set_ESW_Phase( ESW_StartPrep );
						Set_ESW_Mode( ESW_StartPrep_EngineReady );
						break;
					default:
						break;
				}
				break;
			case ESW_Start:
				switch (DCU->RAM[RAM_AD08_NXT_MODE])// mode
				{
					case ESW_Start_StartInitiation:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Start_StartInitiation;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Start_StartInitiation;
						Set_ESW_Phase( ESW_Start );
						Set_ESW_Mode( ESW_Start_StartInitiation );
						break;
					case ESW_Start_ThrustBuildup:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Start_ThrustBuildup;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Start_ThrustBuildup;
						Set_ESW_Phase( ESW_Start );
						Set_ESW_Mode( ESW_Start_ThrustBuildup );
						break;
					default:
						break;
				}
				break;
			case ESW_Mainstage:
				switch (DCU->RAM[RAM_AD08_NXT_MODE])// mode
				{
					case ESW_Mainstage_NormalControl:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Mainstage_NormalControl;
						fptrMonitorSDLimits = &SSMEControllerSW_AD08::MonitorSDLimits_Mainstage_NormalControl;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Mainstage_NormalControl;
						Set_ESW_Phase( ESW_Mainstage );
						Set_ESW_Mode( ESW_Mainstage_NormalControl );
						break;
					case ESW_Mainstage_FixedDensity:
						Set_ESW_Phase( ESW_Mainstage );
						Set_ESW_Mode( ESW_Mainstage_FixedDensity );
						break;
					case ESW_Mainstage_ThrustLimiting:
						Set_ESW_Phase( ESW_Mainstage );
						Set_ESW_Mode( ESW_Mainstage_ThrustLimiting );
						break;
					case ESW_Mainstage_HydraulicLockup:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Mainstage_HydraulicLockup;
						fptrMonitorSDLimits = &SSMEControllerSW_AD08::MonitorSDLimits_Mainstage_HydraulicLockup;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Mainstage_HydraulicLockup;
						Set_ESW_Phase( ESW_Mainstage );
						Set_ESW_Mode( ESW_Mainstage_HydraulicLockup );
						break;
					case ESW_Mainstage_ElectricalLockup:
						Set_ESW_Phase( ESW_Mainstage );
						Set_ESW_Mode( ESW_Mainstage_ElectricalLockup );
						break;
					default:
						break;
				}
				break;
			case ESW_Shutdown:
				switch (DCU->RAM[RAM_AD08_NXT_MODE])// mode
				{
					case ESW_Shutdown_ThrottleTo0:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Shutdown_ThrottleTo0;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Shutdown_ThrottleTo0;
						Set_ESW_Phase( ESW_Shutdown );
						Set_ESW_Mode( ESW_Shutdown_ThrottleTo0 );
						break;
					case ESW_Shutdown_PropellantValvesClosed:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Shutdown_PropellantValvesClosed;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Shutdown_PropellantValvesClosed;
						Set_ESW_Phase( ESW_Shutdown );
						Set_ESW_Mode( ESW_Shutdown_PropellantValvesClosed );
						break;
					case ESW_Shutdown_FailSafePneumatic:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_Shutdown_FailSafePneumatic;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_Shutdown_FailSafePneumatic;
						Set_ESW_Phase( ESW_Shutdown );
						Set_ESW_Mode( ESW_Shutdown_FailSafePneumatic );
						break;
					default:
						break;
				}
				break;
			case ESW_PostShutdown:
				switch (DCU->RAM[RAM_AD08_NXT_MODE])// mode
				{
					case ESW_PostShutdown_Standby:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_PostShutdown_Standby;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_PostShutdown_Standby;
						Set_ESW_Phase( ESW_PostShutdown );
						Set_ESW_Mode( ESW_PostShutdown_Standby );
						break;
					case ESW_PostShutdown_OxidizerDump:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_PostShutdown_OxidizerDump;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_PostShutdown_OxidizerDump;
						Set_ESW_Phase( ESW_PostShutdown );
						Set_ESW_Mode( ESW_PostShutdown_OxidizerDump );
						break;
					case ESW_PostShutdown_TerminateSequence:
						fptrVehicleCommands = &SSMEControllerSW_AD08::VehicleCommands_PostShutdown_TerminateSequence;
						fptrMonitorSDLimits = NULL;
						fptrEngineOperations = &SSMEControllerSW_AD08::EngineOperations_PostShutdown_TerminateSequence;
						Set_ESW_Phase( ESW_PostShutdown );
						Set_ESW_Mode( ESW_PostShutdown_TerminateSequence );
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		return;
	}

	unsigned short SSMEControllerSW_AD08::SensorInput( void )
	{
		// first sensor is enough, it's all sequencial
		// IE chA
		DCU->DMA_write( 0x1F00, RAM_AD08_SENSOR_A, 15 );// press
		DCU->DMA_write( 0x1F0F, RAM_AD08_SENSOR_A + 15, 8 );// temp
		DCU->DMA_write( 0x1000, RAM_AD08_SENSOR_A + 23, 4 );// flow
		DCU->DMA_write( 0x1004, RAM_AD08_SENSOR_A + 27, 3 );// speed

		// IE chB
		DCU->DMA_write( 0x2F00, RAM_AD08_SENSOR_B, 15 );// press
		DCU->DMA_write( 0x2F0F, RAM_AD08_SENSOR_B + 15, 8 );// temp
		DCU->DMA_write( 0x2000, RAM_AD08_SENSOR_B + 23, 4 );// flow
		DCU->DMA_write( 0x2004, RAM_AD08_SENSOR_B + 27, 3 );// speed

		if (DCU->RAM[RAM_AD08_OE_A_STATUS] == 0)
		{
			// read a
			DCU->DMA_write( 0x1F17, RAM_AD08_CCV_POS, 9 );// actuator position
			DCU->DMA_write( 0x1F20, RAM_AD08_CCV_SH, 5 );// sample & hold
		}
		else
		{
			if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
			{
				// read b
				DCU->DMA_write( 0x2F17, RAM_AD08_CCV_POS, 9 );// actuator position
				DCU->DMA_write( 0x2F20, RAM_AD08_CCV_SH, 5 );// sample & hold
			}
		}

		return 0;
	}

	unsigned short SSMEControllerSW_AD08::SensorScale( void )
	{
		// TODO desqualification of all redline sensors gives MCF

		// qualify sensors

		// HPFT DT A2
		SensorQualification_Upper( RAM_AD08_SENSOR_A + 15, 2650 );

		// HPFT DT A3
		SensorQualification_Upper( RAM_AD08_SENSOR_A + 16, 2650 );

		// HPFT DT B2
		SensorQualification_Upper( RAM_AD08_SENSOR_B + 15, 2650 );

		// HPFT DT B3
		SensorQualification_Upper( RAM_AD08_SENSOR_B + 16, 2650 );

		// HPOT DT A2
		SensorQualification_Upper( RAM_AD08_SENSOR_A + 17, 2650 );

		// HPOT DT A3
		SensorQualification_Upper( RAM_AD08_SENSOR_A + 18, 2650 );

		// HPOT DT B2
		SensorQualification_Upper( RAM_AD08_SENSOR_B + 17, 2650 );

		// HPOT DT B3
		SensorQualification_Upper( RAM_AD08_SENSOR_B + 18, 2650 );

		// HPOTP Intermediate Seal A
		SensorQualification_UpperLower( RAM_AD08_SENSOR_A + 10, 650, 0 );

		// HPOTP Intermediate Seal B
		SensorQualification_UpperLower( RAM_AD08_SENSOR_B + 10, 650, 0 );

		// calculate averages

		// HACK using just sensor X1 below to keep track of strike counts
		// |A1 - A2|
		if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			if (abs( DCU->RAM[RAM_AD08_SENSOR_A + 8] - DCU->RAM[RAM_AD08_SENSOR_A + 9] ) > 125)
			{
				// add strike
				DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] += 0x4000;
				if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
			}
			else
			{
				unsigned short temp = (unsigned short)((DCU->RAM[RAM_AD08_SENSOR_A + 8] + DCU->RAM[RAM_AD08_SENSOR_A + 9]) / 2);
				if ((temp < 1000) || (temp > 3500))
				{
					// add strike
					DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] += 0x4000;
					if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
				}
				else
				{
					// clear qualifying strikes
					DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] = DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x3FFF;
				}
			}
		}

		// |B1 - B2|
		if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			if (abs( DCU->RAM[RAM_AD08_SENSOR_B + 8] - DCU->RAM[RAM_AD08_SENSOR_B + 9] ) > 125)
			{
				// add strike
				DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] += 0x4000;
				if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
			}
			else
			{
				unsigned short temp = (unsigned short)((DCU->RAM[RAM_AD08_SENSOR_B + 8] + DCU->RAM[RAM_AD08_SENSOR_B + 9]) / 2);
				if ((temp < 1000) || (temp > 3500))
				{
					// add strike
					DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] += 0x4000;
					if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
				}
				else
				{
					// clear qualifying strikes
					DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] = DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x3FFF;
				}
			}
		}

		// MCC PC
		DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] = CalcSensorAverage4( RAM_AD08_SENSOR_A + 8, RAM_AD08_SENSOR_A + 9, RAM_AD08_SENSOR_B + 8, RAM_AD08_SENSOR_B + 9 );
		return 0;
	}

	void SSMEControllerSW_AD08::SensorQualification_Upper( unsigned short addr_snsr, unsigned short qual_limit_upper )
	{
		if ((DCU->RAM[addr_snsr + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			if (DCU->RAM[addr_snsr] > qual_limit_upper)
			{
				// add strike
				DCU->RAM[addr_snsr + SENSOR_COUNT] += 0x4000;
				if ((DCU->RAM[addr_snsr + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[addr_snsr + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
			}
			else
			{
				// clear qualifying strikes
				DCU->RAM[addr_snsr + SENSOR_COUNT] = DCU->RAM[addr_snsr + SENSOR_COUNT] & 0x3FFF;
			}
		}
		return;
	}

	void SSMEControllerSW_AD08::SensorQualification_Lower( unsigned short addr_snsr, unsigned short qual_limit_lower )
	{
		if ((DCU->RAM[addr_snsr + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			if (DCU->RAM[addr_snsr] < qual_limit_lower)
			{
				// add strike
				DCU->RAM[addr_snsr + SENSOR_COUNT] += 0x4000;
				if ((DCU->RAM[addr_snsr + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[addr_snsr + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
			}
			else
			{
				// clear qualifying strikes
				DCU->RAM[addr_snsr + SENSOR_COUNT] = DCU->RAM[addr_snsr + SENSOR_COUNT] & 0x3FFF;
			}
		}
		return;
	}

	void SSMEControllerSW_AD08::SensorQualification_UpperLower( unsigned short addr_snsr, unsigned short qual_limit_upper, unsigned short qual_limit_lower )
	{
		if ((DCU->RAM[addr_snsr + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			if ((DCU->RAM[addr_snsr] < qual_limit_lower) || (DCU->RAM[addr_snsr] > qual_limit_upper))
			{
				// add strike
				DCU->RAM[addr_snsr + SENSOR_COUNT] += 0x4000;
				if ((DCU->RAM[addr_snsr + SENSOR_COUNT] & 0xC000) == 0xC000) DCU->RAM[addr_snsr + SENSOR_COUNT] = 0xC000;// desqualified, clear all other strikes
			}
			else
			{
				// clear qualifying strikes
				DCU->RAM[addr_snsr + SENSOR_COUNT] = DCU->RAM[addr_snsr + SENSOR_COUNT] & 0x3FFF;
			}
		}
		return;
	}

	void SSMEControllerSW_AD08::SensorsDesqualifyAll( int ch )
	{
		int count = 0;

		while (count < SENSOR_COUNT)
		{
			DCU->RAM[ch + count + SENSOR_COUNT] = 0xC000;
			count++;
		}
		return;
	}

	//unsigned short SSMEControllerSW_AD08::CalcSensorAverage2( unsigned short addr_snsr_A, unsigned short addr_snsr_B )
	//{
	//	if (DCU->RAM[addr_snsr_A + SENSOR_COUNT] < 3)
	//	{
	//		if (DCU->RAM[addr_snsr_B + SENSOR_COUNT] < 3)
	//		{
	//			// A + B
	//			return (unsigned short)round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_B]) / 2 );
	//		}
	//		else
	//		{
	//			// A
	//			return DCU->RAM[addr_snsr_A];
	//		}
	//	}
	//	else
	//	{
	//		if (DCU->RAM[addr_snsr_B + SENSOR_COUNT] < 3)
	//		{
	//			// B
	//			return DCU->RAM[addr_snsr_B];
	//		}
	//		else
	//		{
	//			// nothing ???
	//			return 0;
	//		}
	//	}
	//}

	unsigned short SSMEControllerSW_AD08::CalcSensorAverage4( unsigned short addr_snsr_A, unsigned short addr_snsr_B, unsigned short addr_snsr_C, unsigned short addr_snsr_D )
	{
		if ((DCU->RAM[addr_snsr_A + SENSOR_COUNT] & 0xC000) != 0xC000)
		{
			if ((DCU->RAM[addr_snsr_B + SENSOR_COUNT] & 0xC000) != 0xC000)
			{
				if ((DCU->RAM[addr_snsr_C + SENSOR_COUNT] & 0xC000) != 0xC000)
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// A + B + C + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_B] + DCU->RAM[addr_snsr_C] + DCU->RAM[addr_snsr_D]) / 4 );
					}
					else
					{
						// A + B + C
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_B] + DCU->RAM[addr_snsr_C]) / 3 );
					}
				}
				else
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// A + B + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_B] + DCU->RAM[addr_snsr_D]) / 3 );
					}
					else
					{
						// A + B
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_B]) / 2 );
					}
				}
			}
			else
			{
				if ((DCU->RAM[addr_snsr_C + SENSOR_COUNT] & 0xC000) != 0xC000)
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// A + C + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_C] + DCU->RAM[addr_snsr_D]) / 3 );
					}
					else
					{
						// A + C
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_C]) / 2 );
					}
				}
				else
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// A + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_A] + DCU->RAM[addr_snsr_D]) / 2 );
					}
					else
					{
						// A
						return DCU->RAM[addr_snsr_A];
					}
				}
			}
		}
		else
		{
			if ((DCU->RAM[addr_snsr_B + SENSOR_COUNT] & 0xC000) != 0xC000)
			{
				if ((DCU->RAM[addr_snsr_C + SENSOR_COUNT] & 0xC000) != 0xC000)
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// B + C + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_B] + DCU->RAM[addr_snsr_C] + DCU->RAM[addr_snsr_D]) / 3 );
					}
					else
					{
						// B + C
						return (unsigned short)Round( (DCU->RAM[addr_snsr_B] + DCU->RAM[addr_snsr_C]) / 2 );
					}
				}
				else
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// B + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_B] + DCU->RAM[addr_snsr_D]) / 2 );
					}
					else
					{
						// B
						return DCU->RAM[addr_snsr_B];
					}
				}
			}
			else
			{
				if ((DCU->RAM[addr_snsr_C + SENSOR_COUNT] & 0xC000) != 0xC000)
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// C + D
						return (unsigned short)Round( (DCU->RAM[addr_snsr_C] + DCU->RAM[addr_snsr_D]) / 2 );
					}
					else
					{
						// C
						return DCU->RAM[addr_snsr_C];
					}
				}
				else
				{
					if ((DCU->RAM[addr_snsr_D + SENSOR_COUNT] & 0xC000) != 0xC000)
					{
						// D
						return DCU->RAM[addr_snsr_D];
					}
					else
					{
						// nothing
						return 0;
					}
				}
			}
		}
	}


	unsigned short SSMEControllerSW_AD08::VehicleCommands_Checkout_Standby( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case EGND:
			case EFLT:
			case EFRT:
			case ETWO:
				RotateCommand();
				return ESW_Accepted;
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case AFRT:
			case XFRT:
			case HYDC:
			case ERCK:
			case RSCT:
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case PSN1:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_PSN1;
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case DAVL:
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN1( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RESM:
			case RSCT:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case PSN2:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_PSN2;
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case COSY:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN2( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RESM:
			case RSCT:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case PSN1:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_PSN1;
				RotateCommand();
				return ESW_Accepted;
			case PSN3:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_PSN3;
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case COSY:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN3( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RESM:
			case RSCT:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case PSN4:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_PSN4;
				DCU->RAM[17] = DCU->RAM[RAM_AD08_TREF1];// setup
				DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 1;
				DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 1;
				DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 1;
				DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 1;
				DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 0;
				DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 1;
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case COSY:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_StartPrep_PSN4( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RESM:
			case RSCT:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case PSN3:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_PSN3;
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case COSY:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_StartPrep_EngineReady( void )
	{
		// validation -> voting and agreement with mode
		int votes = CommandVoting();
		if (votes < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RESM:
			case RSCT:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case STEN:
				if (votes != 3) return ESW_CommandRejected_A;// requires 3 of 3
				DCU->RAM[RAM_AD08_START_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case IGNT:
				if (votes != 3) return ESW_CommandRejected_A;// requires 3 of 3
				if (DCU->RAM[RAM_AD08_START_ENA] != 1) return ESW_CommandRejected_B;// needs STEN

				// TODO start inhibit protection with:
				// HPOTP IMSL
				// POGO Precharge Pressure
				// MCC Press???
				// AFV pos
				// OBV pos
				// FBV pos
				// RIV pos
				// HPFT discharge temp (also LCC?)
				// HPOT discharge temp (also LCC?)
				// HPFTP Coolant Linear Press*
				// HPOTP Sec Seal*
				// *) not on AD08
				/*
				Engine controller monitors HPOTP Intermediate Seal purge pressure
				(E41P1014B, etc). If pressure is below 175 psia for HPOTP or 164 psia
				for HPOTP/AT, engine start is inhibited (reference SSID: SSME-10). After
				engine start, the HPOTP redline limit is 170 psia. HPOTP/AT redline limit
				is 159 psia after engine start and 140 psia after engine cutoff.
				*/

				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Start;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Start_StartInitiation;
				DCU->RAM[RAM_AD08_TIME_ESC] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case THRT:
				{
					double pl = MPL + GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0x03FF );
					if (pl > FPL) return ESW_CommandRejected_B;
					if (pl == 104) pl += 0.5;// bias 104% to 104.5%
					DCU->RAM[RAM_AD08_PC_CMD] = (unsigned short)Round( pl * PC_100_C );
					RotateCommand();
					return ESW_Accepted;
				}
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case COSY:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Start_StartInitiation( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				// TODO should go to pneu shtdwn?
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Start_ThrustBuildup( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				// TODO should go to pneu shtdwn?
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Mainstage_NormalControl( void )
	{
		// validation -> voting and agreement with mode

		int votes = CommandVoting();
		if (votes == 0) return ESW_CommandRejected_A;

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				if (votes == 1)
				{
					double temp = (DCU->RAM[RAM_AD08_TREF1] + (DCU->RAM[RAM_AD08_TREF2] / 10000)) - (DCU->RAM[RAM_AD08_IGNT_TIME1] + (DCU->RAM[RAM_AD08_IGNT_TIME2] / 10000));
					if (temp >= SINGLE_CH_STDN_TIMER)
					{
						if (DCU->RAM[RAM_AD08_LIMITSINHIBITED] == 0)
						{
							DCU->RAM[RAM_AD08_STEN_STDN_CH] = Get_ESW_ChannelStatus();// easier to save failed
							DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
							RotateCommand();
							return ESW_Accepted;
						}
						else return ESW_CommandRejected_A;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				if (votes == 1)
				{
					if (DCU->RAM[RAM_AD08_STEN_STDN_CH] == Get_ESW_ChannelStatus())
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
						RotateCommand();
						return ESW_Accepted;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case THRT:
				{
					if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
					double pl = MPL + GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0x03FF );
					if (pl > FPL) return ESW_CommandRejected_B;
					if (pl == 104) pl += 0.5;// bias 104% to 104.5%
					DCU->RAM[RAM_AD08_PC_CMD] = (unsigned short)Round( pl * PC_100_C );
					RotateCommand();
					return ESW_Accepted;
				}
			case ENLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Enable );
				RotateCommand();
				return ESW_Accepted;
			case INLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Inhibit );
				DCU->RAM[RAM_AD08_LIMITSINHIBITED] = 1;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Mainstage_FixedDensity( void )
	{
		// validation -> voting and agreement with mode

		int votes = CommandVoting();
		if (votes == 0) return ESW_CommandRejected_A;

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				if (votes == 1)
				{
					double temp = (DCU->RAM[RAM_AD08_TREF1] + (DCU->RAM[RAM_AD08_TREF2] / 10000)) - (DCU->RAM[RAM_AD08_IGNT_TIME1] + (DCU->RAM[RAM_AD08_IGNT_TIME2] / 10000));
					if (temp >= SINGLE_CH_STDN_TIMER)
					{
						if (DCU->RAM[RAM_AD08_LIMITSINHIBITED] == 0)
						{
							DCU->RAM[RAM_AD08_STEN_STDN_CH] = Get_ESW_ChannelStatus();// easier to save failed
							DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
							RotateCommand();
							return ESW_Accepted;
						}
						else return ESW_CommandRejected_A;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				if (votes == 1)
				{
					if (DCU->RAM[RAM_AD08_STEN_STDN_CH] == Get_ESW_ChannelStatus())
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
						RotateCommand();
						return ESW_Accepted;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case ENLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Enable );
				RotateCommand();
				return ESW_Accepted;
			case INLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Inhibit );
				DCU->RAM[RAM_AD08_LIMITSINHIBITED] = 1;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Mainstage_ThrustLimiting( void )
	{
		// validation -> voting and agreement with mode

		int votes = CommandVoting();
		if (votes == 0) return ESW_CommandRejected_A;

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				if (votes == 1)
				{
					double temp = (DCU->RAM[RAM_AD08_TREF1] + (DCU->RAM[RAM_AD08_TREF2] / 10000)) - (DCU->RAM[RAM_AD08_IGNT_TIME1] + (DCU->RAM[RAM_AD08_IGNT_TIME2] / 10000));
					if (temp >= SINGLE_CH_STDN_TIMER)
					{
						if (DCU->RAM[RAM_AD08_LIMITSINHIBITED] == 0)
						{
							DCU->RAM[RAM_AD08_STEN_STDN_CH] = Get_ESW_ChannelStatus();// easier to save failed
							DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
							RotateCommand();
							return ESW_Accepted;
						}
						else return ESW_CommandRejected_A;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				if (votes == 1)
				{
					if (DCU->RAM[RAM_AD08_STEN_STDN_CH] == Get_ESW_ChannelStatus())
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
						RotateCommand();
						return ESW_Accepted;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case ENLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Enable );
				RotateCommand();
				return ESW_Accepted;
			case INLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Inhibit );
				DCU->RAM[RAM_AD08_LIMITSINHIBITED] = 1;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Mainstage_HydraulicLockup( void )
	{
		// validation -> voting and agreement with mode

		int votes = CommandVoting();
		if (votes == 0) return ESW_CommandRejected_A;

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				if (votes == 1)
				{
					double temp = (DCU->RAM[RAM_AD08_TREF1] + (DCU->RAM[RAM_AD08_TREF2] / 10000)) - (DCU->RAM[RAM_AD08_IGNT_TIME1] + (DCU->RAM[RAM_AD08_IGNT_TIME2] / 10000));
					if (temp >= SINGLE_CH_STDN_TIMER)
					{
						if (DCU->RAM[RAM_AD08_LIMITSINHIBITED] == 0)
						{
							DCU->RAM[RAM_AD08_STEN_STDN_CH] = Get_ESW_ChannelStatus();// easier to save failed
							DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
							RotateCommand();
							return ESW_Accepted;
						}
						else return ESW_CommandRejected_A;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				if (votes == 1)
				{
					if (DCU->RAM[RAM_AD08_STEN_STDN_CH] == Get_ESW_ChannelStatus())
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
						RotateCommand();
						return ESW_Accepted;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_FailSafePneumatic;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case ENLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Enable );
				RotateCommand();
				return ESW_Accepted;
			case INLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Inhibit );
				DCU->RAM[RAM_AD08_LIMITSINHIBITED] = 1;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Mainstage_ElectricalLockup( void )
	{
		// validation -> voting and agreement with mode

		int votes = CommandVoting();
		if (votes == 0) return ESW_CommandRejected_A;

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				RotateCommand();
				return ESW_Accepted;
			case SDEN:
				if (votes == 1)
				{
					double temp = (DCU->RAM[RAM_AD08_TREF1] + (DCU->RAM[RAM_AD08_TREF2] / 10000)) - (DCU->RAM[RAM_AD08_IGNT_TIME1] + (DCU->RAM[RAM_AD08_IGNT_TIME2] / 10000));
					if (temp >= SINGLE_CH_STDN_TIMER)
					{
						if (DCU->RAM[RAM_AD08_LIMITSINHIBITED] == 0)
						{
							DCU->RAM[RAM_AD08_STEN_STDN_CH] = Get_ESW_ChannelStatus();// easier to save failed
							DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
							RotateCommand();
							return ESW_Accepted;
						}
						else return ESW_CommandRejected_A;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_SHUTDOWN_ENA] = 1;
				RotateCommand();
				return ESW_Accepted;
			case STDN:
				if (DCU->RAM[RAM_AD08_SHUTDOWN_ENA] != 1) return ESW_CommandRejected_B;// needs SDEN
				if (votes == 1)
				{
					if (DCU->RAM[RAM_AD08_STEN_STDN_CH] == Get_ESW_ChannelStatus())
					{
						DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
						DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
						DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
						RotateCommand();
						return ESW_Accepted;
					}
					else return ESW_CommandRejected_A;
				}
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_ThrottleTo0;
				DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;// setup
				RotateCommand();
				return ESW_Accepted;
			case ENLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Enable );
				RotateCommand();
				return ESW_Accepted;
			case INLS:
				if (votes < 2) return ESW_CommandRejected_A;// requires (at least) 2 of 3
				Set_ESW_LimitControlStatus( ESW_Inhibit );
				DCU->RAM[RAM_AD08_LIMITSINHIBITED] = 1;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Shutdown_ThrottleTo0( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Shutdown_PropellantValvesClosed( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_Shutdown_FailSafePneumatic( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_PostShutdown_Standby( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCT:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case LOXD:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_OxidizerDump;
				RotateCommand();
				return ESW_Accepted;
			case XPOW:
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			case COSY:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Checkout;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Checkout_Standby;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_PostShutdown_OxidizerDump( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			case TMSQ:
				DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
				DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_TerminateSequence;
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::VehicleCommands_PostShutdown_TerminateSequence( void )
	{
		// validation -> voting and agreement with mode

		if (CommandVoting() < 2) return ESW_CommandRejected_A;// all cmds in this mode require (at least) 2 of 3

		switch (GetMaskVal( DCU->RAM[RAM_AD08_VALIDCMD], 0xFC00 ))
		{
			case RVRC:
				DCU->CIE->RestoreVRC();
				RotateCommand();
				return ESW_Accepted;
			case SVRC:
				DCU->CIE->SwitchVRC();
				RotateCommand();
				return ESW_Accepted;
			case XFRT:
			case RSCT:
			case RSCA:
			case RSCB:
			case IOHA:
			case IOHB:
			case IOLA:
			case IOLB:
			case IOSA:
			case IOSB:
			case MRC1:
			case MRC2:
				RotateCommand();
				return ESW_Accepted;
			default:
				return ESW_CommandRejected_B;
		}
	}

	unsigned short SSMEControllerSW_AD08::CommandVoting( void )
	{
		DCU->RAM[RAM_AD08_CMD1] = DCU->DIO_in( DEV_CIE_VIE_CMD1 );
		DCU->RAM[RAM_AD08_CMD2] = DCU->DIO_in( DEV_CIE_VIE_CMD2 );
		DCU->RAM[RAM_AD08_CMD3] = DCU->DIO_in( DEV_CIE_VIE_CMD3 );

		if (DCU->RAM[RAM_AD08_CMD1] == DCU->RAM[RAM_AD08_CMD2])
		{
			if (DCU->RAM[RAM_AD08_CMD2] == DCU->RAM[RAM_AD08_CMD3])
			{
				// all equal
				if (DCU->RAM[RAM_AD08_CMD1] == NOP)// valid != NOP
				{
					DCU->RAM[RAM_AD08_VALIDCMD] = NOP;
					Set_ESW_ChannelStatus( ESW_CHA_CHB_CHC_ERROR );
					return 0;
				}
				DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD3];
				Set_ESW_ChannelStatus( ESW_OK );
				return 3;
			}
			else
			{
				// 1 & 2 equal
				if (DCU->RAM[RAM_AD08_CMD1] == NOP)// valid != NOP
				{
					DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD3];
					Set_ESW_ChannelStatus( ESW_CHA_CHB_ERROR );
					return 1;
				}
				DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD2];
				Set_ESW_ChannelStatus( ESW_CHC_ERROR );
				return 2;
			}
		}
		else
		{
			if (DCU->RAM[RAM_AD08_CMD2] == DCU->RAM[RAM_AD08_CMD3])
			{
				// 2 & 3 equal
				if (DCU->RAM[RAM_AD08_CMD2] == NOP)// valid != NOP
				{
					DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD1];
					Set_ESW_ChannelStatus( ESW_CHB_CHC_ERROR );
					return 1;
				}
				DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD3];
				Set_ESW_ChannelStatus( ESW_CHA_ERROR );
				return 2;
			}
			else
			{
				if (DCU->RAM[RAM_AD08_CMD1] == DCU->RAM[RAM_AD08_CMD3])
				{
					// 1 & 3 equal
					if (DCU->RAM[RAM_AD08_CMD1] == NOP)// valid != NOP
					{
						DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD2];
						Set_ESW_ChannelStatus( ESW_CHA_CHC_ERROR );
						return 1;
					}
					DCU->RAM[RAM_AD08_VALIDCMD] = DCU->RAM[RAM_AD08_CMD3];
					Set_ESW_ChannelStatus( ESW_CHB_ERROR );
					return 2;
				}
				else
				{
					// all different
					DCU->RAM[RAM_AD08_VALIDCMD] = NOP;
					Set_ESW_ChannelStatus( ESW_CHA_CHB_CHC_ERROR );
					return 0;
				}
			}
		}
	}

	unsigned short SSMEControllerSW_AD08::MonitorSDLimits_Mainstage_NormalControl( void )
	{
		unsigned short retval = 0;
		int count = 0;
		/*
		HPFT TURBINE DISCHARGE TEMPERATURE
		>1860 R
		*/
		// HPFT Discharge Temperature A2
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_A + 15] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureA2 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		//// HPFT Discharge Temperature A3
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_A + 16] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureA3 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		//// HPFT Discharge Temperature B2
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_B + 15] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureB2 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		//// HPFT Discharge Temperature B3
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_B + 16] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureB3 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		///*
		//HPOT TURBINE DISCHARGE TEMPERATURE
		//>1660 R
		//<720 R
		//*/
		//// HPOT Discharge Temperature A2
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_A + 17] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_A + 17] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureA2 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		//// HPOT Discharge Temperature A3
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_A + 18] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_A + 18] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureA3 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		//// HPOT Discharge Temperature B2
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_B + 17] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_B + 17] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureB2 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		//// HPOT Discharge Temperature B3
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_B + 18] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_B + 18] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureB3 );
		//			retval = 1;// hyd shutdown
		//		}
		//	}
		//}

		/*
		MCC PC SENSOR AVERAGE
		PC CHANNEL AVG <
		PC REF - 200 PSI (STEADY STATE)
		AND
		PC REF - 400 PSI (DURING THROTTLING OR WHEN < 75% RPL)
		*/
		// HACK using just sensor X1 below to keep track of strike counts
		// MCC PC A1/A2
		count = 0;
		if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			unsigned short temp = (unsigned short)((DCU->RAM[RAM_AD08_SENSOR_A + 8] + DCU->RAM[RAM_AD08_SENSOR_A + 9]) / 2);
			if ((abs( DCU->RAM[RAM_AD08_PC_REF] - DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] ) < 30) && (DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] >= (0.75 * PC_100)))// HACK considering throttling as +/-1% diff
			{
				// PC REF - 200 PSI (STEADY STATE)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 200))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
			else
			{
				// PC REF - 400 PSI (DURING THROTTLING OR WHEN < 75% RPL)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 400))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
		}
		//MCC PC B1/B2
		if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			unsigned short temp = (unsigned short)((DCU->RAM[RAM_AD08_SENSOR_B + 8] + DCU->RAM[RAM_AD08_SENSOR_B + 9]) / 2);
			if ((abs( DCU->RAM[RAM_AD08_PC_REF] - DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] ) < 30) && (DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] >= (0.75 * PC_100)))// HACK considering throttling as +/-1% diff
			{
				// PC REF - 200 PSI (STEADY STATE)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 200))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
			else
			{
				// PC REF - 400 PSI (DURING THROTTLING OR WHEN < 75% RPL)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 400))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
		}

		if (count > 0)
		{
			if (((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x0003) + (DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x0003)) == (count * 3))
			{
				// redline exceeded, take action
				AddFID( FID_RedlineExceeded, Delimiter_MCCPC );
				retval = 1;// hyd shutdown
			}
		}

		/*
		HPOTP INTERMEDIATE SEAL PRESSURE
		<159 PSIA
		*/
		// HPOTP Intermediate Seal A
		count = 0;
		if ((DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			if (DCU->RAM[RAM_AD08_SENSOR_A + 10] < 159)// check redline
			{
				// redline exceeded, add strike
				if ((DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT]++;
			}
			else
			{
				// clear redline strikes
				DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] &= 0xFFFC;
			}
		}
		// HPOTP Intermediate Seal B
		if ((DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			if (DCU->RAM[RAM_AD08_SENSOR_B + 10] < 159)// check redline
			{
				// redline exceeded, add strike
				if ((DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT]++;
			}
			else
			{
				// clear redline strikes
				DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] &= 0xFFFC;
			}
		}

		if (count > 0)
		{
			if (((DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] & 0x0003) + (DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] & 0x0003)) == (count * 3))
			{
				// redline exceeded, take action
				AddFID( FID_RedlineExceeded, Delimiter_HPOTPIntermediateSealPressure );
				// TODO regular S/D, but open ESD solenoid
				retval = 1;// hyd shutdown
			}
		}

		return retval;
	}

	unsigned short SSMEControllerSW_AD08::MonitorSDLimits_Mainstage_HydraulicLockup( void )
	{
		unsigned short retval = 0;
		int count = 0;
		/*
		HPFT TURBINE DISCHARGE TEMPERATURE
		>1860 R
		*/
		// HPFT Discharge Temperature A2
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_A + 15] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 15 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureA2 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		//// HPFT Discharge Temperature A3
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_A + 16] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 16 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureA3 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		//// HPFT Discharge Temperature B2
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_B + 15] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 15 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureB2 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		//// HPFT Discharge Temperature B3
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if (DCU->RAM[RAM_AD08_SENSOR_B + 16] <= 1860)// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 16 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPFTDischargeTemperatureB3 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		///*
		//HPOT TURBINE DISCHARGE TEMPERATURE
		//>1660 R
		//<720 R
		//*/
		//// HPOT Discharge Temperature A2
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_A + 17] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_A + 17] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 17 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureA2 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		//// HPOT Discharge Temperature A3
		//if ((DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_A + 18] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_A + 18] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_A + 18 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureA3 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		//// HPOT Discharge Temperature B2
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_B + 17] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_B + 17] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 17 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureB2 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		//// HPOT Discharge Temperature B3
		//if ((DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30] & 0x8000) == 0)// check if qualified
		//{
		//	if ((DCU->RAM[RAM_AD08_SENSOR_B + 18] >= 720) && (DCU->RAM[RAM_AD08_SENSOR_B + 18] <= 1660))// check redline
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30] = 0;
		//	}
		//	else
		//	{
		//		DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30]++;
		//		if (DCU->RAM[RAM_AD08_SENSOR_B + 18 + 30] >= 3)
		//		{
		//			// redline exceeded
		//			AddFID( FID_RedlineExceeded, Delimiter_HPOTDischargeTemperatureB3 );
		//			retval = 2;// pneumatic shutdown
		//		}
		//	}
		//}

		/*
		MCC PC SENSOR AVERAGE
		PC CHANNEL AVG <
		PC REF - 200 PSI (STEADY STATE)
		AND
		PC REF - 400 PSI (DURING THROTTLING OR WHEN < 75% RPL)
		*/
		// HACK using just sensor X1 below to keep track of strike counts
		// MCC PC A1/A2
		count = 0;
		if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			unsigned short temp = (unsigned short)((DCU->RAM[RAM_AD08_SENSOR_A + 8] + DCU->RAM[RAM_AD08_SENSOR_A + 9]) / 2);
			if ((abs( DCU->RAM[RAM_AD08_PC_REF] - DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] ) < 30) && (DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] >= (0.75 * PC_100)))// HACK considering throttling as +/-1% diff
			{
				// PC REF - 200 PSI (STEADY STATE)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 200))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
			else
			{
				// PC REF - 400 PSI (DURING THROTTLING OR WHEN < 75% RPL)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 400))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
		}
		//MCC PC B1/B2
		if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			unsigned short temp = (unsigned short)((DCU->RAM[RAM_AD08_SENSOR_B + 8] + DCU->RAM[RAM_AD08_SENSOR_B + 9]) / 2);
			if ((abs( DCU->RAM[RAM_AD08_PC_REF] - DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] ) < 30) && (DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] >= (0.75 * PC_100)))// HACK considering throttling as +/-1% diff
			{
				// PC REF - 200 PSI (STEADY STATE)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 200))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
			else
			{
				// PC REF - 400 PSI (DURING THROTTLING OR WHEN < 75% RPL)
				if (temp < (DCU->RAM[RAM_AD08_PC_REF] - 400))// check redline
				{
					// redline exceeded, add strike
					if ((DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT]++;
				}
				else
				{
					// clear redline strikes
					DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] &= 0xFFFC;
				}
			}
		}

		if (count > 0)
		{
			if (((DCU->RAM[RAM_AD08_SENSOR_A + 8 + SENSOR_COUNT] & 0x0003) + (DCU->RAM[RAM_AD08_SENSOR_B + 8 + SENSOR_COUNT] & 0x0003)) == (count * 3))
			{
				// redline exceeded, take action
				AddFID( FID_RedlineExceeded, Delimiter_MCCPC );
				retval = 2;// pneumatic shutdown
			}
		}

		/*
		HPOTP INTERMEDIATE SEAL PRESSURE
		<159 PSIA
		*/
		// HPOTP Intermediate Seal A
		count = 0;
		if ((DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			if (DCU->RAM[RAM_AD08_SENSOR_A + 10] < 159)// check redline
			{
				// redline exceeded, add strike
				if ((DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT]++;
			}
			else
			{
				// clear redline strikes
				DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] &= 0xFFFC;
			}
		}
		// HPOTP Intermediate Seal B
		if ((DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] & 0xC000) != 0xC000)// check if qualified
		{
			count++;
			if (DCU->RAM[RAM_AD08_SENSOR_B + 10] < 159)// check redline
			{
				// redline exceeded, add strike
				if ((DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] & 0x0003) < 3) DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT]++;
			}
			else
			{
				// clear redline strikes
				DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] &= 0xFFFC;
			}
		}

		if (count > 0)
		{
			if (((DCU->RAM[RAM_AD08_SENSOR_A + 10 + SENSOR_COUNT] & 0x0003) + (DCU->RAM[RAM_AD08_SENSOR_B + 10 + SENSOR_COUNT] & 0x0003)) == (count * 3))
			{
				// redline exceeded, take action
				AddFID( FID_RedlineExceeded, Delimiter_HPOTPIntermediateSealPressure );
				// TODO regular S/D, but open ESD solenoid
				retval = 1;// hyd shutdown
			}
		}

		return retval;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Checkout_Standby( void )
	{
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN1( void )
	{
		// purge Oxidizer System and intermediate seal with GSE N2 press

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN2( void )
	{
		// purge Fuel System + PSN1

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN3( void )
	{// TODO learn from LCC SSME-10
		// propellant recirculation

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 1;// looks like it stays on for BLOCK II engine (only)
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 1;// open bleed vlvs
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_StartPrep_PSN4( void )
	{// TODO learn from LCC SSME-10
		// purge Fuel System after propellant drop
		// TODO fuel sys purge for 180sec every 60min

		// open CCV now
		DCU->RAM[RAM_AD08_CCV_CMD] = 4095;

		// TODO
		// i-seal he purge psn4+120
		// HPOTP  Minimum Redline: 175, Maximum Redline: 225
		// HPOTP/AT  Minimum Redline: 164, Maximum Redline: 225

		// TODO when ready go to Engine Ready
		/*
		All ENGINE READY parameters must be within limits for two continuous
		seconds to obtain ENGINE READY mode. After ENGINE READY is achieved, no
		ENGINE READY parameter may leave the redline envelope for more than one
		continuous second.
		*/

		// PSN4 + 10sec to STEN

		// LPFP Disch Press Ch A&B  Min: 53 Max: 60
		// LPFP Disch Temp Ch A&B  Min: 37 Max: 42
		// LPOT Disch Press Ch A&B  Min: 95
		// PBP Disch Temp Ch A&B  Max: 186.5
		// Oxid Prebnr Pge Press  Max: 50
		// Fuel Prebnr Pge Press  Max: 50
		// Emerg Sht Dn Press Ch A&B  Max: 50
		// MFV Hyd Temp Ch A&B  Min: 490
		// MOV Hyd Temp Ch A&B  Min: 490

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 1;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;

		// HACK for now stay 180s in PSN4 and then goto engine ready
		if (DCU->RAM[RAM_AD08_TREF1] - DCU->RAM[17] >= 180)
		{
			// engine ready
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_StartPrep;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_StartPrep_EngineReady;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_StartPrep_EngineReady( void )
	{
		// TODO if needed go back to psn4

		DCU->RAM[RAM_AD08_CCV_CMD] = 4095;

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		if (DCU->RAM[RAM_AD08_START_ENA] == 1)
		{
			DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;// stop fuel system purge after STEN cmd
			DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;// close bleed valves after STEN cmd
		}
		else
		{
			DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 1;
			DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 1;// TODO check: Was 20% open at 2 seconds, changed to 30% open (on 26R)
		}
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Start_StartInitiation( void )
	{
		if (DCU->RAM[RAM_AD08_TIME_ESC] != 0xFFFF)
		{
			DCU->RAM[RAM_AD08_TIME_ESC] += (unsigned short)Round( DCU->dt * 10000 );// increment time from ESC
		}
		else
		{
			DCU->RAM[RAM_AD08_TIME_ESC] = 0;
			DCU->RAM[RAM_AD08_IGNT_TIME1] = DCU->RAM[RAM_AD08_TREF1];
			DCU->RAM[RAM_AD08_IGNT_TIME2] = DCU->RAM[RAM_AD08_TREF2];
		}

		// run valve ignition schedules
		ValveSchedule( RAM_AD08_IGNT_CCV_POS, RAM_AD08_CCV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_CCV_POS );
		ValveSchedule( RAM_AD08_IGNT_MFV_POS, RAM_AD08_MFV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_MFV_POS );
		ValveSchedule( RAM_AD08_IGNT_MOV_POS, RAM_AD08_MOV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_MOV_POS );
		ValveSchedule( RAM_AD08_IGNT_FPOV_POS, RAM_AD08_FPOV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_FPOV_POS );
		ValveSchedule( RAM_AD08_IGNT_OPOV_POS, RAM_AD08_OPOV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_OPOV_POS );

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 1;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 1;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 1;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 1;

		// TODO check ignition confirmed vals with:
		// MCC press
		// HPFTP speed
		// AFV pos
		// Preburner s/d purge press (both?)
		// ESW not in hyd lockup
		// HPFT disch temp
		// HPOT disch temp

		// check of (at least) HPFTP speed at IGNT+1.25s
		// checks (of what?) at IGNT+1.3s and IGNT+2.3s

		/*if ((DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR] > ) &&
			() &&
			(DCU->RAM[RAM_AD08_AFV_POS] == 0) &&
			(DCU->RAM[RAM_AD08_SENSOR_A] < 50) &&// 50psia
			(DCU->RAM[RAM_AD08_SENSOR_A + 1] < 50) &&// 50psia
			() &&
			() &&
			())*/
		if (DCU->RAM[RAM_AD08_TIME_ESC] > 24000)
		{// HACK for now stay here for 2.4 sec ???
			// go to Start phase ThrustBuildup mode
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Start;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Start_ThrustBuildup;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Start_ThrustBuildup( void )
	{
		// 3.8 CL mix control (FPOV)
		// use PC_REF to reach PC_CMD
		// check when PC_CMD achieved then go to mainstage

		DCU->RAM[RAM_AD08_TIME_ESC] += (unsigned short)Round( DCU->dt * 10000 );// increment time from ESC

		// run valve ignition schedules
		ValveSchedule( RAM_AD08_IGNT_CCV_POS, RAM_AD08_CCV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_CCV_POS );
		ValveSchedule( RAM_AD08_IGNT_MFV_POS, RAM_AD08_MFV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_MFV_POS );
		ValveSchedule( RAM_AD08_IGNT_MOV_POS, RAM_AD08_MOV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_MOV_POS );
		ValveSchedule( RAM_AD08_IGNT_FPOV_POS, RAM_AD08_FPOV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_FPOV_POS );
		ValveSchedule( RAM_AD08_IGNT_OPOV_POS, RAM_AD08_OPOV_CMD, RAM_AD08_TIME_ESC, RAM_AD08_OPOV_POS );

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 1;// igniters stay on for 4.4s
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 1;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 1;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 1;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;

		if (DCU->RAM[RAM_AD08_TIME_ESC] > 44000)// stay here until esc + 4.4 sec ???
		{
			DCU->RAM[RAM_AD08_PC_REF] = PC_100_D;// HACK use this here

			// go to Mainstage phase NormalControl mode
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Mainstage;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Mainstage_NormalControl;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Mainstage_NormalControl( void )
	{
		double temp;
		double tempB;
		// rate limit
		// HACK using 10%/sec instead of 480lbs/msec
		// TODO update this so PC_REF takes into account the delay in the engine response
		if (DCU->RAM[RAM_AD08_PC_CMD] > DCU->RAM[RAM_AD08_PC_REF])// throttle up
		{
			tempB = DCU->dt * PC_100_B;
			tempB = DCU->RAM[RAM_AD08_PC_REF] + tempB;
			if (tempB > DCU->RAM[RAM_AD08_PC_CMD]) tempB = DCU->RAM[RAM_AD08_PC_CMD];
			DCU->RAM[RAM_AD08_PC_REF] = (unsigned short)Round( tempB );
		}
		else if (DCU->RAM[RAM_AD08_PC_CMD] < DCU->RAM[RAM_AD08_PC_REF])// throttle down
		{
			tempB = DCU->dt * PC_100_B;
			tempB = DCU->RAM[RAM_AD08_PC_REF] - tempB;
			if (tempB < DCU->RAM[RAM_AD08_PC_CMD]) tempB = DCU->RAM[RAM_AD08_PC_CMD];
			DCU->RAM[RAM_AD08_PC_REF] = (unsigned short)Round( tempB );
		}

		// CCV thrust command to position schedule
		if (DCU->RAM[RAM_AD08_PC_REF] >= PC_100)// 100%
		{
			if (DCU->RAM[RAM_AD08_CCV_CMD] < 4095)// open
			{
				tempB = DCU->dt * 393.3657;
				tempB = DCU->RAM[RAM_AD08_CCV_CMD] + tempB;
				if (tempB > 4095) tempB = 4095;
				DCU->RAM[RAM_AD08_CCV_CMD] = (unsigned short)Round( tempB );
			}
		}
		else
		{
			temp = (((31.7 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) + 130) / 33) * 40.95;
			if (DCU->RAM[RAM_AD08_CCV_CMD] < temp)// open
			{
				tempB = DCU->dt * 393.3657;
				tempB = DCU->RAM[RAM_AD08_CCV_CMD] + tempB;
				if (tempB > temp) tempB = temp;
				DCU->RAM[RAM_AD08_CCV_CMD] = (unsigned short)Round( tempB );
			}
			else if (DCU->RAM[RAM_AD08_CCV_CMD] > temp)// close
			{
				tempB = DCU->dt * 393.3657;
				tempB = DCU->RAM[RAM_AD08_CCV_CMD] - tempB;
				if (tempB < temp) tempB = temp;
				DCU->RAM[RAM_AD08_CCV_CMD] = (unsigned short)Round( tempB );
			}
		}

		DCU->RAM[RAM_AD08_MFV_CMD] = 4095;

		DCU->RAM[RAM_AD08_MOV_CMD] = 4095;

		temp = ((0.0035 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C) * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) - (0.3168 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) + 74.978) * 40.95;
		if (DCU->RAM[RAM_AD08_FPOV_CMD] < temp)// open
		{
			tempB = DCU->dt * 4095 * ((0.007 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) - 0.3168);
			tempB = DCU->RAM[RAM_AD08_FPOV_CMD] + tempB;
			if (tempB > temp) tempB = temp;
			DCU->RAM[RAM_AD08_FPOV_CMD] = (unsigned short)Round( tempB );
		}
		else if (DCU->RAM[RAM_AD08_FPOV_CMD] > temp)// close
		{
			tempB = DCU->dt * 4095 * ((0.007 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) - 0.3168);
			tempB = DCU->RAM[RAM_AD08_FPOV_CMD] - tempB;
			if (tempB < temp) tempB = temp;
			DCU->RAM[RAM_AD08_FPOV_CMD] = (unsigned short)Round( tempB );
		}

		temp = DCU->RAM[RAM_AD08_PC_REF] / PC_100_C;
		temp = ((0.004 * temp * temp) - (0.3679 * temp) + 61.024) * 40.95;
		if (DCU->RAM[RAM_AD08_OPOV_CMD] < temp)// open
		{
			tempB = DCU->dt * 4095 * ((0.008 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) - 0.3679);
			tempB = DCU->RAM[RAM_AD08_OPOV_CMD] + tempB;
			if (tempB > temp) tempB = temp;
			DCU->RAM[RAM_AD08_OPOV_CMD] = (unsigned short)Round( tempB );
		}
		else if (DCU->RAM[RAM_AD08_OPOV_CMD] > temp)// close
		{
			tempB = DCU->dt * 4095 * ((0.008 * (DCU->RAM[RAM_AD08_PC_REF] / PC_100_C)) - 0.3679);
			tempB = DCU->RAM[RAM_AD08_OPOV_CMD] - tempB;
			if (tempB < temp) tempB = temp;
			DCU->RAM[RAM_AD08_OPOV_CMD] = (unsigned short)Round( tempB );
		}

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 1;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;

		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Mainstage_FixedDensity( void )
	{
		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 1;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Mainstage_ThrustLimiting( void )
	{
		// TODO OPOV cmd limit
		// Mode initiated whenever OPOV position command is limited for at least 3 consecutive major cycles.
		// Control loop computations, Shutdown Limit Monitoring and sensor monitoring are retained.

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 1;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Mainstage_HydraulicLockup( void )
	{
		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 1;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Mainstage_ElectricalLockup( void )
	{
		// TODO if all MCC pc sensors are desqualified come to here

		// using PC_REF in VDT

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 1;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Shutdown_ThrottleTo0( void )
	{
		if (DCU->RAM[RAM_AD08_TIME_STDN] != 0xFFFF)
		{
			DCU->RAM[RAM_AD08_TIME_STDN] += (unsigned short)Round( DCU->dt * 10000 );// increment time from STDN
		}
		else
		{
			DCU->RAM[RAM_AD08_PC_CMD] = 0;
			DCU->RAM[RAM_AD08_TIME_STDN] = 0;
			UpdateShutdownValveSchedule( PC_100 - DCU->RAM[RAM_AD08_PC_REF] );
		}

		ValveSchedule( RAM_AD08_STDN_CCV_POS, RAM_AD08_CCV_CMD, RAM_AD08_TIME_STDN, RAM_AD08_CCV_POS );
		ValveSchedule( RAM_AD08_STDN_MFV_POS, RAM_AD08_MFV_CMD, RAM_AD08_TIME_STDN, RAM_AD08_MFV_POS );
		ValveSchedule( RAM_AD08_STDN_MOV_POS, RAM_AD08_MOV_CMD, RAM_AD08_TIME_STDN, RAM_AD08_MOV_POS );
		ValveSchedule( RAM_AD08_STDN_FPOV_POS, RAM_AD08_FPOV_CMD, RAM_AD08_TIME_STDN, RAM_AD08_FPOV_POS );
		ValveSchedule( RAM_AD08_STDN_OPOV_POS, RAM_AD08_OPOV_CMD, RAM_AD08_TIME_STDN, RAM_AD08_OPOV_POS );

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		if (DCU->RAM[RAM_AD08_TIME_STDN] < 20000)// 2sec POGO post-charge
		{
			DCU->RAM[RAM_AD08_HPV_CMD] = 1;
		}
		else
		{
			DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		}

		if (DCU->RAM[RAM_AD08_CCV_POS] + DCU->RAM[RAM_AD08_MFV_POS] + DCU->RAM[RAM_AD08_MOV_POS] + DCU->RAM[RAM_AD08_FPOV_POS] + DCU->RAM[RAM_AD08_OPOV_POS] == 0)
		{
			// go to shutdown prop vlv closed
			DCU->RAM[RAM_AD08_CCV_CMD] = 0;
			DCU->RAM[RAM_AD08_MFV_CMD] = 0;
			DCU->RAM[RAM_AD08_MOV_CMD] = 0;
			DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
			DCU->RAM[RAM_AD08_OPOV_CMD] = 0;

			DCU->RAM[RAM_AD08_TIME_STDN] = 0xFFFF;

			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_Shutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_Shutdown_PropellantValvesClosed;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Shutdown_PropellantValvesClosed( void )
	{
		if (DCU->RAM[RAM_AD08_TIME_STDN] != 0xFFFF)
		{
			DCU->RAM[RAM_AD08_TIME_STDN] += (unsigned short)Round( DCU->dt * 1000 );// increment time
		}
		else
		{
			DCU->RAM[RAM_AD08_TIME_STDN] = 0;
		}

		// go to p/s stby after purges (16sec)

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 1;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;

		if (DCU->RAM[RAM_AD08_TIME_STDN] >= 10000)// HACK stay here for 10s
		{
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_Standby;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_Shutdown_FailSafePneumatic( void )
	{
		if (DCU->RAM[RAM_AD08_TIME_STDN] != 0xFFFF)
		{
			DCU->RAM[RAM_AD08_TIME_STDN] += (unsigned short)Round( DCU->dt * 1000 );// increment time from STDN
		}
		else
		{
			DCU->RAM[RAM_AD08_PC_CMD] = 0;
			DCU->RAM[RAM_AD08_TIME_STDN] = 0;
		}

		DCU->RAM[RAM_AD08_CCV_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_CMD] = 0;

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		if (DCU->RAM[RAM_AD08_TIME_STDN] < 2000)// 2sec POGO post-charge
		{
			DCU->RAM[RAM_AD08_HPV_CMD] = 1;
		}
		else
		{
			DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		}
		DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;

		// HACK go to Post-Shutdown Standby after 16sec
		if (DCU->RAM[RAM_AD08_TIME_STDN] > 16000)
		{
			// go to shutdown
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_Standby;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_PostShutdown_Standby( void )
	{
		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 1;// FBV opens at S/D + 16
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;// TODO make the conditional cmds for solenoids
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;

		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_PostShutdown_OxidizerDump( void )
	{
		// open MOV
		DCU->RAM[RAM_AD08_MOV_CMD] = 4095;

		// on/off devs
		DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
		DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 1;
		DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 1;
		DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
		DCU->RAM[RAM_AD08_AFV_CMD] = 0;
		DCU->RAM[RAM_AD08_HPV_CMD] = 0;
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::EngineOperations_PostShutdown_TerminateSequence( void )
	{
		// All valves are being closed while a purge or dump sequence is being terminated. All solenoid and servoswitch valves are then deenergized.

		// close any open vlvs
		DCU->RAM[RAM_AD08_CCV_CMD] = 0;
		DCU->RAM[RAM_AD08_MFV_CMD] = 0;
		DCU->RAM[RAM_AD08_MOV_CMD] = 0;
		DCU->RAM[RAM_AD08_FPOV_CMD] = 0;
		DCU->RAM[RAM_AD08_OPOV_CMD] = 0;

		if (DCU->RAM[RAM_AD08_CCV_POS] + DCU->RAM[RAM_AD08_MFV_POS] + DCU->RAM[RAM_AD08_MOV_POS] + DCU->RAM[RAM_AD08_FPOV_POS] + DCU->RAM[RAM_AD08_OPOV_POS] == 0)
		{
			// on/off devs
			DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] = 0;
			DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] = 0;
			DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] = 0;
			DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] = 0;
			DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] = 0;
			DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] = 0;
			DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] = 0;
			DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] = 0;
			DCU->RAM[RAM_AD08_AFV_CMD] = 0;
			DCU->RAM[RAM_AD08_HPV_CMD] = 0;
			DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] = 0;
			DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] = 0;

			// go to p/s stby
			DCU->RAM[RAM_AD08_NXT_PHASE] = ESW_PostShutdown;
			DCU->RAM[RAM_AD08_NXT_MODE] = ESW_PostShutdown_Standby;
			return 1;
		}
		return 0;
	}

	unsigned short SSMEControllerSW_AD08::CommandActuators( void )
	{
		if ((DCU->RAM[RAM_AD08_CH] == chB) && (DCU->RAM[RAM_AD08_DCU_A_STATUS] == 0)) return 0;// if chB, and chA is working, don't bother

		unsigned short retval = 0;
		int cmdCCV = (DCU->RAM[RAM_AD08_CCV_CMD] << 4) + DEV_OE_CCV;
		int cmdMFV = (DCU->RAM[RAM_AD08_MFV_CMD] << 4) + DEV_OE_MFV;
		int cmdMOV = (DCU->RAM[RAM_AD08_MOV_CMD] << 4) + DEV_OE_MOV;
		int cmdFPOV = (DCU->RAM[RAM_AD08_FPOV_CMD] << 4) + DEV_OE_FPOV;
		int cmdOPOV = (DCU->RAM[RAM_AD08_OPOV_CMD] << 4) + DEV_OE_OPOV;

		// OE chA output and test
		if (DCU->RAM[RAM_AD08_OE_A_STATUS] == 0)
		{
			// command
			DCU->DIO_out( DEV_CIE_OEchA, cmdCCV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_OE_STORAGE_REG ) != cmdCCV) retval = 1;

			// command
			DCU->DIO_out( DEV_CIE_OEchA, cmdMFV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_OE_STORAGE_REG ) != cmdMFV) retval = 1;

			// command
			DCU->DIO_out( DEV_CIE_OEchA, cmdMOV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_OE_STORAGE_REG ) != cmdMOV) retval = 1;

			// command
			DCU->DIO_out( DEV_CIE_OEchA, cmdFPOV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_OE_STORAGE_REG ) != cmdFPOV) retval = 1;

			// command
			DCU->DIO_out( DEV_CIE_OEchA, cmdOPOV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_OE_STORAGE_REG ) != cmdOPOV) retval = 1;
		}

		// OE chB output and test
		if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
		{
			// command
			DCU->DIO_out( DEV_CIE_OEchB, cmdCCV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_OE_STORAGE_REG ) != cmdCCV) retval |= 2;

			// command
			DCU->DIO_out( DEV_CIE_OEchB, cmdMFV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_OE_STORAGE_REG ) != cmdMFV) retval |= 2;

			// command
			DCU->DIO_out( DEV_CIE_OEchB, cmdMOV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_OE_STORAGE_REG ) != cmdMOV) retval |= 2;

			// command
			DCU->DIO_out( DEV_CIE_OEchB, cmdFPOV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_OE_STORAGE_REG ) != cmdFPOV) retval |= 2;

			// command
			DCU->DIO_out( DEV_CIE_OEchB, cmdOPOV );
			// read back and check if match
			if (DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_OE_STORAGE_REG ) != cmdOPOV) retval |= 2;
		}
		return retval;
	}

	unsigned short SSMEControllerSW_AD08::CommandONOFFDevices( void )
	{
		if ((DCU->RAM[RAM_AD08_CH] == chB) && (DCU->RAM[RAM_AD08_DCU_A_STATUS] == 0)) return 0;// if chB, and chA is working, don't bother

		unsigned short cmd1 = (DCU->RAM[RAM_AD08_HPOTPISPURGE_CMD] << 4) +
			(DCU->RAM[RAM_AD08_EMERGENCYSHUTDOWN_CMD] << 5) +
			(DCU->RAM[RAM_AD08_SHUTDOWNPURGE_CMD] << 6) +
			(DCU->RAM[RAM_AD08_FUELSYSTEMPURGE_CMD] << 8) +
			(DCU->RAM[RAM_AD08_BLEEDVALVESCONTROL_CMD] << 9) +
			(DCU->RAM[RAM_AD08_AFV_CMD] << 10) +
			(DCU->RAM[RAM_AD08_HPV_CMD] << 11) +
			(DCU->RAM[RAM_AD08_MCC_IGNITER_CMD] << 13) +
			(DCU->RAM[RAM_AD08_OPB_IGNITER_CMD] << 14) +
			(DCU->RAM[RAM_AD08_FPB_IGNITER_CMD] << 15);

		unsigned short cmd2 = (DCU->RAM[RAM_AD08_CCV_FO_SS_CMD] << 4) +
			(DCU->RAM[RAM_AD08_MFV_FO_SS_CMD] << 5) +
			(DCU->RAM[RAM_AD08_MOV_FO_SS_CMD] << 6) +
			(DCU->RAM[RAM_AD08_FPOV_FO_SS_CMD] << 7) +
			(DCU->RAM[RAM_AD08_OPOV_FO_SS_CMD] << 8) +
			(DCU->RAM[RAM_AD08_CCV_FS_SS_CMD] << 9) +
			(DCU->RAM[RAM_AD08_MFV_FS_SS_CMD] << 10) +
			(DCU->RAM[RAM_AD08_MOV_FS_SS_CMD] << 11) +
			(DCU->RAM[RAM_AD08_FPOV_FS_SS_CMD] << 12) +
			(DCU->RAM[RAM_AD08_OPOV_FS_SS_CMD] << 13);

		unsigned short retval = 0;

		// OE chA output and test
		if (DCU->RAM[RAM_AD08_OE_A_STATUS] == 0)
		{
			// command
			DCU->DIO_out( DEV_CIE_OEchA, cmd1 + DEV_OE_ON_OFF_1 );
			DCU->DIO_out( DEV_CIE_OEchA, cmd2 + DEV_OE_ON_OFF_2 );
			// read back
			DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_1] = DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_ONOFF_REG_1 );
			DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_2] = DCU->DIO_in( DIO_DEV_OEchA + DEV_CIE_ONOFF_REG_2 );
			// check if match
			if ((DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_1] != cmd1) || (DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_2] != cmd2)) retval = 1;
		}

		// OE chB output and test
		if (DCU->RAM[RAM_AD08_OE_B_STATUS] == 0)
		{
			// command
			DCU->DIO_out( DEV_CIE_OEchB, cmd1 + DEV_OE_ON_OFF_1 );
			DCU->DIO_out( DEV_CIE_OEchB, cmd2 + DEV_OE_ON_OFF_2 );
			// read back
			DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_1] = DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_ONOFF_REG_1 );
			DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_2] = DCU->DIO_in( DIO_DEV_OEchB + DEV_CIE_ONOFF_REG_2 );
			// check if match
			if ((DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_1] != cmd1) || (DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_2] != cmd2)) retval |= 2;
		}
		return retval;
	}

	unsigned short SSMEControllerSW_AD08::OutputVDT( void )
	{
		memset( &DCU->RAM[RAM_AD08_VRC_1], 0, 128 * sizeof(unsigned short) );// zeroing

		DCU->RAM[RAM_AD08_VRC_1] = DCU->RAM[RAM_AD08_TREF1];// TREF Word 1
		DCU->RAM[RAM_AD08_VRC_2] = DCU->RAM[RAM_AD08_TREF2];// TREF Word 2
		DCU->RAM[RAM_AD08_VRC_3] = DCU->RAM[RAM_AD08_ESW];// Engine Status Word
		DCU->RAM[RAM_AD08_VRC_4] = DCU->RAM[RAM_AD08_CH];// ID
		DCU->RAM[RAM_AD08_VRC_5] = GetFID();// FID Word
		if ((Get_ESW_Phase() == ESW_Mainstage) && (Get_ESW_Mode() == ESW_Mainstage_ElectricalLockup)) DCU->RAM[RAM_AD08_VRC_6] = DCU->RAM[RAM_AD08_PC_REF];
		else DCU->RAM[RAM_AD08_VRC_6] = DCU->RAM[RAM_AD08_MCC_PC_QUAL_AVGR];
		DCU->RAM[RAM_AD08_VRC_7] = 7;// Fuel Flowmeter (qualified average)
		//////////////////////////////////////////////////////////////////////////////////////////
		///
		DCU->RAM[RAM_AD08_VRC_9] = DCU->RAM[RAM_AD08_PC_CMD];
		DCU->RAM[RAM_AD08_VRC_10] = DCU->RAM[RAM_AD08_PC_REF];
		///
		//////////////////////////////////////////////////////////////////////////////////////////
		DCU->RAM[RAM_AD08_VRC_11] = DCU->RAM[RAM_AD08_SENSOR_A + 19];// PBP Disch Temp Ch A
		//////////////////////////////////////////////////////////////////////////////////////////
		///
		DCU->RAM[RAM_AD08_VRC_14] = DCU->RAM[RAM_AD08_CCV_CMD];// CCV Actuator cmd
		DCU->RAM[RAM_AD08_VRC_15] = DCU->RAM[RAM_AD08_MFV_CMD];// MFV Actuator cmd
		DCU->RAM[RAM_AD08_VRC_16] = DCU->RAM[RAM_AD08_MOV_CMD];// MOV Actuator cmd
		DCU->RAM[RAM_AD08_VRC_17] = DCU->RAM[RAM_AD08_FPOV_CMD];// FPOV Actuator cmd
		DCU->RAM[RAM_AD08_VRC_18] = DCU->RAM[RAM_AD08_OPOV_CMD];// OPOV Actuator cmd
		///
		//////////////////////////////////////////////////////////////////////////////////////////
		DCU->RAM[RAM_AD08_VRC_20] = DCU->RAM[RAM_AD08_SENSOR_A + 10];// HPOT I-Seal Purge Press Ch A
		DCU->RAM[RAM_AD08_VRC_21] = DCU->RAM[RAM_AD08_SENSOR_B + 10];// HPOT I-Seal Purge Press Ch B

		DCU->RAM[RAM_AD08_VRC_24] = DCU->RAM[RAM_AD08_CCV_POS];// CCV Actuator Pos
		DCU->RAM[RAM_AD08_VRC_25] = DCU->RAM[RAM_AD08_MFV_POS];// MFV Actuator Pos
		DCU->RAM[RAM_AD08_VRC_26] = DCU->RAM[RAM_AD08_MOV_POS];// MOV Actuator Pos
		DCU->RAM[RAM_AD08_VRC_27] = DCU->RAM[RAM_AD08_FPOV_POS];// FPOV Actuator Pos
		DCU->RAM[RAM_AD08_VRC_28] = DCU->RAM[RAM_AD08_OPOV_POS];// OPOV Actuator Pos
		DCU->RAM[RAM_AD08_VRC_29] = DCU->RAM[RAM_AD08_SENSOR_A + 5];// HPFTP Disch Press Ch A
		DCU->RAM[RAM_AD08_VRC_30] = DCU->RAM[RAM_AD08_SENSOR_A + 4];// HPOTP Disch Press Ch A
		//////////////////////////////////////////////////////////////////////////////////////////
		///
		DCU->RAM[RAM_AD08_VRC_31] = DCU->RAM[RAM_AD08_TIME_ESC];// HACK IGNT+T
		DCU->RAM[RAM_AD08_VRC_32] = DCU->RAM[RAM_AD08_TIME_STDN];// HACK STDN+T
		///
		//////////////////////////////////////////////////////////////////////////////////////////
		DCU->RAM[RAM_AD08_VRC_33] = DCU->RAM[RAM_AD08_SENSOR_B + 6];// HPOTP Boost Pump Disch Press Ch B
		DCU->RAM[RAM_AD08_VRC_34] = DCU->RAM[RAM_AD08_SENSOR_A + 23];// Fuel Flowrate Ch A1
		//////////////////////////////////////////////////////////////////////////////////////////
		///
		DCU->RAM[RAM_AD08_VRC_36] = DCU->RAM[RAM_AD08_CCV_SH];// CCV Actuator cmd s&h
		DCU->RAM[RAM_AD08_VRC_37] = DCU->RAM[RAM_AD08_MFV_SH];// MFV Actuator cmd s&h
		DCU->RAM[RAM_AD08_VRC_38] = DCU->RAM[RAM_AD08_MOV_SH];// MOV Actuator cmd s&h
		DCU->RAM[RAM_AD08_VRC_39] = DCU->RAM[RAM_AD08_FPOV_SH];// FPOV Actuator cmd s&h
		DCU->RAM[RAM_AD08_VRC_40] = DCU->RAM[RAM_AD08_OPOV_SH];// OPOV Actuator cmd s&h
		///
		//////////////////////////////////////////////////////////////////////////////////////////
		DCU->RAM[RAM_AD08_VRC_41] = DCU->RAM[RAM_AD08_SENSOR_A + 8];// MCC Press Ch A1
		DCU->RAM[RAM_AD08_VRC_42] = DCU->RAM[RAM_AD08_SENSOR_A + 9];// MCC Press Ch A2
		DCU->RAM[RAM_AD08_VRC_43] = DCU->RAM[RAM_AD08_SENSOR_B + 8];// MCC Press Ch B1
		DCU->RAM[RAM_AD08_VRC_44] = DCU->RAM[RAM_AD08_SENSOR_B + 9];// MCC Press Ch B2
		DCU->RAM[RAM_AD08_VRC_45] = DCU->RAM[RAM_AD08_SENSOR_A + 15];// HPFT Disch Temp Ch A2
		DCU->RAM[RAM_AD08_VRC_46] = DCU->RAM[RAM_AD08_SENSOR_B + 15];// HPFT Disch Temp Ch B2
		DCU->RAM[RAM_AD08_VRC_47] = DCU->RAM[RAM_AD08_SENSOR_A + 17];// HPOT Disch Temp Ch A2
		DCU->RAM[RAM_AD08_VRC_48] = DCU->RAM[RAM_AD08_SENSOR_B + 17];// HPOT Disch Temp Ch B2

		DCU->RAM[RAM_AD08_VRC_53] = DCU->RAM[RAM_AD08_SENSOR_A + 7];// Fuel Sys Purge Press Ch A
		DCU->RAM[RAM_AD08_VRC_54] = DCU->RAM[RAM_AD08_SENSOR_B + 7];// Fuel Sys Purge Press Ch B
		DCU->RAM[RAM_AD08_VRC_55] = DCU->RAM[RAM_AD08_SENSOR_B + 19];// PBP Disch Temp Ch B

		DCU->RAM[RAM_AD08_VRC_59] = DCU->RAM[RAM_AD08_SENSOR_A + 21];// MOV Hyd Temp Ch A
		DCU->RAM[RAM_AD08_VRC_60] = DCU->RAM[RAM_AD08_SENSOR_B + 21];// MOV Hyd Temp Ch B
		DCU->RAM[RAM_AD08_VRC_61] = DCU->RAM[RAM_AD08_SENSOR_A + 22];// MFV Hyd Temp Ch A
		DCU->RAM[RAM_AD08_VRC_62] = DCU->RAM[RAM_AD08_SENSOR_B + 22];// MFV Hyd Temp Ch B
		DCU->RAM[RAM_AD08_VRC_63] = (unsigned short)(DCU->RAM[RAM_AD08_RIV_POS] / 40.95);// POGO Recirn Isln V Pos
		DCU->RAM[RAM_AD08_VRC_64] = DCU->RAM[RAM_AD08_SENSOR_A + 16];// HPFT Disch Temp Ch A3
		DCU->RAM[RAM_AD08_VRC_65] = ((unsigned short)(DCU->RAM[RAM_AD08_OBV_POS] / 40.95) << 8) + (unsigned short)(DCU->RAM[RAM_AD08_FBV_POS] / 40.95);// OBV | FBV

		// TODO fix channels
		DCU->RAM[RAM_AD08_VRC_68] = (DCU->RAM[RAM_AD08_AFV_CMD] << 8) + (unsigned short)(DCU->RAM[RAM_AD08_AFV_POS] / 40.95);// AFV chA | AFV chB
		DCU->RAM[RAM_AD08_VRC_69] = DCU->RAM[RAM_AD08_SENSOR_B + 16];// HPFT Disch Temp Ch B3
		DCU->RAM[RAM_AD08_VRC_70] = DCU->RAM[RAM_AD08_SENSOR_A + 2];// LPOT Disch Press Ch A
		DCU->RAM[RAM_AD08_VRC_71] = DCU->RAM[RAM_AD08_SENSOR_B + 2];// LPOT Disch Press Ch B
		DCU->RAM[RAM_AD08_VRC_72] = DCU->RAM[RAM_AD08_SENSOR_A + 11];// Emerg Sht Dn Press Ch A
		DCU->RAM[RAM_AD08_VRC_73] = DCU->RAM[RAM_AD08_SENSOR_B + 11];// Emerg Sht Dn Press Ch B
		if (DCU->RAM[RAM_AD08_IE_A_STATUS] == 0)// HACK use chB if IEchA is dead (doesn't work because for now IEchB doesn't receive these sensors...)
		{
			DCU->RAM[RAM_AD08_VRC_74] = DCU->RAM[RAM_AD08_SENSOR_A];// FPB Purge Press
			DCU->RAM[RAM_AD08_VRC_75] = DCU->RAM[RAM_AD08_SENSOR_A + 1];// OPB Purge Press
		}
		else
		{
			DCU->RAM[RAM_AD08_VRC_74] = DCU->RAM[RAM_AD08_SENSOR_B];// FPB Purge Press
			DCU->RAM[RAM_AD08_VRC_75] = DCU->RAM[RAM_AD08_SENSOR_B + 1];// OPB Purge Press
		}

		DCU->RAM[RAM_AD08_VRC_82] = DCU->RAM[RAM_AD08_SENSOR_A + 27];// LPFTP Shaft Speed Ch A

		DCU->RAM[RAM_AD08_VRC_89] = DCU->RAM[RAM_AD08_SENSOR_B + 23];// Fuel Flowrate Ch B1
		DCU->RAM[RAM_AD08_VRC_90] = 90;// Inhibit Counter/PROM Rev.

		DCU->RAM[RAM_AD08_VRC_92] = DCU->RAM[RAM_AD08_SENSOR_A + 3];// LPFP Disch Press Ch A
		DCU->RAM[RAM_AD08_VRC_93] = DCU->RAM[RAM_AD08_SENSOR_A + 20];// LPFP Disch Temp Ch A

		DCU->RAM[RAM_AD08_VRC_96] = DCU->RAM[RAM_AD08_SENSOR_A + 28];// HPFTP Shaft Speed Ch A

		DCU->RAM[RAM_AD08_VRC_98] = DCU->RAM[RAM_AD08_CURCMD];// Current Command
		DCU->RAM[RAM_AD08_VRC_99] = DCU->RAM[RAM_AD08_PRVCMD];// Previous Command
		DCU->RAM[RAM_AD08_VRC_100] = 100;// FID/Delimiter

		DCU->RAM[RAM_AD08_VRC_103] = 103;// Parameter

		DCU->RAM[RAM_AD08_VRC_104] = DCU->RAM[RAM_AD08_DCU_A_STATUS];// HACK
		DCU->RAM[RAM_AD08_VRC_105] = DCU->RAM[RAM_AD08_DCU_B_STATUS];
		DCU->RAM[RAM_AD08_VRC_106] = DCU->RAM[RAM_AD08_IE_A_STATUS];
		DCU->RAM[RAM_AD08_VRC_107] = DCU->RAM[RAM_AD08_IE_B_STATUS];
		DCU->RAM[RAM_AD08_VRC_108] = DCU->RAM[RAM_AD08_OE_A_STATUS];
		DCU->RAM[RAM_AD08_VRC_109] = DCU->RAM[RAM_AD08_OE_B_STATUS];

		DCU->RAM[RAM_AD08_VRC_111] = ((DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_1] & 0x03F0) << 6) +
			((DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_1] & 0xE000) >> 11);
		DCU->RAM[RAM_AD08_VRC_112] = ((DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_1] & 0x03F0) << 6) +
			((DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_1] & 0xE000) >> 11);
		if (DCU->RAM[RAM_AD08_OE_A_STATUS] == 0)
		{
			DCU->RAM[RAM_AD08_VRC_113] = (DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_2] & 0x01F0) << 7;
		}
		else
		{
			DCU->RAM[RAM_AD08_VRC_113] = (DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_2] & 0x01F0) << 7;
		}
		DCU->RAM[RAM_AD08_VRC_114] = ((DCU->RAM[RAM_AD08_OE_B_ONOFF_REG_2] & 0x3E00) >> 3) +
			((DCU->RAM[RAM_AD08_OE_A_ONOFF_REG_2] & 0x3E00) << 2);

		DCU->RAM[RAM_AD08_VRC_122] = DCU->RAM[RAM_AD08_SENSOR_A + 18];// HPOT Disch Temp Ch A3
		DCU->RAM[RAM_AD08_VRC_123] = DCU->RAM[RAM_AD08_SENSOR_B + 18];// HPOT Disch Temp Ch B3
		DCU->RAM[RAM_AD08_VRC_124] = DCU->RAM[RAM_AD08_SENSOR_A + 24];// Fuel Flowrate Ch A2
		DCU->RAM[RAM_AD08_VRC_125] = DCU->RAM[RAM_AD08_SENSOR_B + 24];// Fuel Flowrate Ch B2

		DCU->RAM[RAM_AD08_VRC_127] = DCU->RAM[RAM_AD08_SENSOR_B + 3];// LPFP Disch Press Ch B
		DCU->RAM[RAM_AD08_VRC_128] = DCU->RAM[RAM_AD08_SENSOR_B + 20];// LPFP Disch Temp Ch B

		// output
		DCU->DMA_read( 1, RAM_AD08_VRC_1, 128 );
		DCU->DMA_read( 2, RAM_AD08_VRC_1, 128 );

		return 0;
	}

	void SSMEControllerSW_AD08::Set_ESW_SelfTestStatus( unsigned short SelfTestStatus )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0x3FFF;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((SelfTestStatus << 14) & 0xC000);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_SelfTestStatus( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0xC000) >> 14);
	}

	void SSMEControllerSW_AD08::Set_ESW_Mode( unsigned short Mode )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0xC7FF;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((Mode << 11) & 0x3800);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_Mode( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0x3800) >> 11);
	}

	void SSMEControllerSW_AD08::Set_ESW_Phase( unsigned short Phase )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0xF8FF;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((Phase << 8) & 0x0700);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_Phase( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0x0700) >> 8);
	}

	void SSMEControllerSW_AD08::Set_ESW_LimitControlStatus( unsigned short LimitControlStatus )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0xFF7F;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((LimitControlStatus << 7) & 0x0080);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_LimitControlStatus( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0x0080) >> 7);
	}

	void SSMEControllerSW_AD08::Set_ESW_FRTStatus( unsigned short FRTStatus )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0xFFBF;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((FRTStatus << 6) & 0x0040);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_FRTStatus( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0x0040) >> 6);
	}

	void SSMEControllerSW_AD08::Set_ESW_ChannelStatus( unsigned short ChannelStatus )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0xFFC7;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((ChannelStatus << 3) & 0x0038);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_ChannelStatus( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0x0038) >> 3);
	}

	void SSMEControllerSW_AD08::Set_ESW_CommandStatus( unsigned short CommandStatus )
	{
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] & 0xFFF9;
		DCU->RAM[RAM_AD08_ESW] = DCU->RAM[RAM_AD08_ESW] | ((CommandStatus << 1) & 0x0006);
		return;
	}

	unsigned short SSMEControllerSW_AD08::Get_ESW_CommandStatus( void ) const
	{
		return ((DCU->RAM[RAM_AD08_ESW] & 0x0006) >> 1);
	}
}
