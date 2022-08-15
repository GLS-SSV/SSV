/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "OutputElectronics_BLOCK_II.h"
#include "SSMEController.h"
#include "PowerSupplyElectronics.h"
#include "ComputerInterfaceElectronics.h"
#include "DigitalComputerUnit.h"
#include "SSME.h"
#include "SolenoidValve.h"
#include "HydraulicActuatedValve.h"
#include "PressureActuatedValve.h"
#include "MPSdefs.h"
#include <MathSSV.h>


namespace mps
{
	OutputElectronics_BLOCK_II::OutputElectronics_BLOCK_II( int ch, SSME* eng, SSMEController* Controller ):OutputElectronics( ch, eng, Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " OutputElectronics_BLOCK_II::OutputElectronics_BLOCK_II in || ch:%d", ch );
#endif// _MPSDEBUG

#ifdef _MPSDEBUG
		oapiWriteLog( " OutputElectronics_BLOCK_II::OutputElectronics_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	OutputElectronics_BLOCK_II::~OutputElectronics_BLOCK_II( void )
	{
		return;
	}

	void OutputElectronics_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		OutputElectronics::OnSaveState( scn );
		return;
	}

	bool OutputElectronics_BLOCK_II::OnParseLine( const char* line )
	{
		return OutputElectronics::OnParseLine( line );
	}

	void OutputElectronics_BLOCK_II::tmestp( double time, double tmestp )
	{
		// check power supply and at least one good DCU
		if ((PSE->Power() == false) || ((CIE[chA]->CheckWDTOwn( 0 ) || CIE[chA]->CheckWDTOwn( 1 )) && (CIE[chB]->CheckWDTOwn( 0 ) || CIE[chB]->CheckWDTOwn( 1 ))))
		{
			HPOTPISPurge_SV.ResetLine();
			EmergencyShutdown_SV.ResetLine();
			ShutdownPurge_SV.ResetLine();
			FuelSystemPurge_SV.ResetLine();
			BleedValvesControl_SV.ResetLine();
			AFV_SV.ResetLine();
			HPV_SV.ResetLine();
			eng->Igniter_MCC[ch] = false;
			eng->Igniter_OPB[ch] = false;
			eng->Igniter_FPB[ch] = false;
			FO_SS[0].ResetLine();
			FO_SS[1].ResetLine();
			FO_SS[2].ResetLine();
			FO_SS[3].ResetLine();
			FO_SS[4].ResetLine();
			FS_SS[0].ResetLine();
			FS_SS[1].ResetLine();
			FS_SS[2].ResetLine();
			FS_SS[3].ResetLine();
			FS_SS[4].ResetLine();

			ONOFFCommandRegister[0] = 0;
			ONOFFCommandRegister[1] = 0;
			return;
		}

		this->time = time;

		// "issue" on/off cmds
		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], SV_HPOTPISPURGE ) >> 4 ) == true) HPOTPISPurge_SV.SetLine();
		else HPOTPISPurge_SV.ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], SV_EMERGENCYSHUTDOWN ) >> 5 ) == true) EmergencyShutdown_SV.SetLine();
		else EmergencyShutdown_SV.ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], SV_SHUTDOWNPURGE ) >> 6 ) == true) ShutdownPurge_SV.SetLine();
		else ShutdownPurge_SV.ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], SV_FUELSYSTEMPURGE ) >> 8 ) == true) FuelSystemPurge_SV.SetLine();
		else FuelSystemPurge_SV.ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], SV_BLEEDVALVESCONTROL ) >> 9 ) == true) BleedValvesControl_SV.SetLine();
		else BleedValvesControl_SV.ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], AFV ) >> 10 ) == true) AFV_SV.SetLine();
		else AFV_SV.ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], HPV ) >> 11 ) == true) HPV_SV.SetLine();
		else HPV_SV.ResetLine();

		eng->Igniter_MCC[ch] = GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], IGNITER_MCC ) >> 13 );
		eng->Igniter_OPB[ch] = GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], IGNITER_OPB ) >> 14 );
		eng->Igniter_FPB[ch] = GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[0], IGNITER_FPB ) >> 15 );

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_CCV_FO ) >> 4 ) == true) FO_SS[0].SetLine();
		else FO_SS[0].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_MFV_FO ) >> 5 ) == true) FO_SS[1].SetLine();
		else FO_SS[1].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_MOV_FO ) >> 6 ) == true) FO_SS[2].SetLine();
		else FO_SS[2].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_FPOV_FO ) >> 7 ) == true) FO_SS[3].SetLine();
		else FO_SS[3].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_OPOV_FO ) >> 8 ) == true) FO_SS[4].SetLine();
		else FO_SS[4].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_CCV_FS ) >> 9 ) == true) FS_SS[0].SetLine();
		else FS_SS[0].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_MFV_FS ) >> 10 ) == true) FS_SS[1].SetLine();
		else FS_SS[1].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_MOV_FS ) >> 11 ) == true) FS_SS[2].SetLine();
		else FS_SS[2].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_FPOV_FS ) >> 12 ) == true) FS_SS[3].SetLine();
		else FS_SS[3].ResetLine();

		if (GetBoolFromInt( GetMaskVal( ONOFFCommandRegister[1], SS_OPOV_FS ) >> 13 ) == true) FS_SS[4].SetLine();
		else FS_SS[4].ResetLine();

		// TODO monitor igniters

		// get valve position
		POS[0] = eng->ptrCCV->GetPos();
		POS[1] = eng->ptrMFV->GetPos();
		POS[2] = eng->ptrMOV->GetPos();
		POS[3] = eng->ptrFPOV->GetPos();
		POS[4] = eng->ptrOPOV->GetPos();
		/*POS[5] = eng->ptrFBV->GetPos();
		POS[6] = eng->ptrOBV->GetPos();
		POS[7] = eng->ptrAFV->GetPos();
		POS[8] = eng->ptrRIV->GetPos();*/

		// TODO servovalve drivers and models


		// SV model
		// propagate model
		if ((SVmodel_tgt[0] - SVmodel_cur[0]) > 0)
		{
			SVmodel_cur[0] += (MAX_RATE_CCV / 100) * tmestp;
			if (SVmodel_cur[0] > SVmodel_tgt[0]) SVmodel_cur[0] = SVmodel_tgt[0];
		}
		if ((SVmodel_tgt[0] - SVmodel_cur[0]) < 0)
		{
			SVmodel_cur[0] -= (MAX_RATE_CCV / 100) * tmestp;
			if (SVmodel_cur[0] < SVmodel_tgt[0]) SVmodel_cur[0] = SVmodel_tgt[0];
		}

		if ((SVmodel_tgt[1] - SVmodel_cur[1]) > 0)
		{
			SVmodel_cur[1] += (MAX_RATE_MFV / 100) * tmestp;
			if (SVmodel_cur[1] > SVmodel_tgt[1]) SVmodel_cur[1] = SVmodel_tgt[1];
		}
		if ((SVmodel_tgt[1] - SVmodel_cur[1]) < 0)
		{
			SVmodel_cur[1] -= (MAX_RATE_MFV / 100) * tmestp;
			if (SVmodel_cur[1] < SVmodel_tgt[1]) SVmodel_cur[1] = SVmodel_tgt[1];
		}

		if ((SVmodel_tgt[2] - SVmodel_cur[2]) > 0)
		{
			SVmodel_cur[2] += (MAX_RATE_MOV / 100) * tmestp;
			if (SVmodel_cur[2] > SVmodel_tgt[2]) SVmodel_cur[2] = SVmodel_tgt[2];
		}
		if ((SVmodel_tgt[2] - SVmodel_cur[2]) < 0)
		{
			SVmodel_cur[2] -= (MAX_RATE_MOV / 100) * tmestp;
			if (SVmodel_cur[2] < SVmodel_tgt[2]) SVmodel_cur[2] = SVmodel_tgt[2];
		}

		if ((SVmodel_tgt[3] - SVmodel_cur[3]) > 0)
		{
			SVmodel_cur[3] += (MAX_RATE_FPOV / 100) * tmestp;
			if (SVmodel_cur[3] > SVmodel_tgt[3]) SVmodel_cur[3] = SVmodel_tgt[3];
		}
		if ((SVmodel_tgt[3] - SVmodel_cur[3]) < 0)
		{
			SVmodel_cur[3] -= (MAX_RATE_FPOV / 100) * tmestp;
			if (SVmodel_cur[3] < SVmodel_tgt[3]) SVmodel_cur[3] = SVmodel_tgt[3];
		}

		if ((SVmodel_tgt[4] - SVmodel_cur[4]) > 0)
		{
			SVmodel_cur[4] += (MAX_RATE_OPOV / 100) * tmestp;
			if (SVmodel_cur[4] > SVmodel_tgt[4]) SVmodel_cur[4] = SVmodel_tgt[4];
		}
		if ((SVmodel_tgt[4] - SVmodel_cur[4]) < 0)
		{
			SVmodel_cur[4] -= (MAX_RATE_OPOV / 100) * tmestp;
			if (SVmodel_cur[4] < SVmodel_tgt[4]) SVmodel_cur[4] = SVmodel_tgt[4];
		}
		// check differences
		if (abs(SVmodel_cur[0] - POS[0]) > triplevel[ch])
		{
			// interrupt
			CIE[chA]->Interrupt( INT_CCVSVAFI + ch );
			CIE[chB]->Interrupt( INT_CCVSVAFI + ch );
		}
		if (abs(SVmodel_cur[1] - POS[1]) > triplevel[ch])
		{
			// interrupt
			CIE[chA]->Interrupt( INT_MFVSVAFI + ch );
			CIE[chB]->Interrupt( INT_MFVSVAFI + ch );
		}
		if (abs(SVmodel_cur[2] - POS[2]) > triplevel[ch])
		{
			// interrupt
			CIE[chA]->Interrupt( INT_MOVSVAFI + ch );
			CIE[chB]->Interrupt( INT_MOVSVAFI + ch );
		}
		if (abs(SVmodel_cur[3] - POS[3]) > triplevel[ch])
		{
			// interrupt
			CIE[chA]->Interrupt( INT_FPOVSVAFI + ch );
			CIE[chB]->Interrupt( INT_FPOVSVAFI + ch );
		}
		if (abs(SVmodel_cur[4] - POS[4]) > triplevel[ch])
		{
			// interrupt
			CIE[chA]->Interrupt( INT_OPOVSVAFI + ch );
			CIE[chB]->Interrupt( INT_OPOVSVAFI + ch );
		}
		SVmodel_tgt[0] = SH[0];
		SVmodel_tgt[1] = SH[1];
		SVmodel_tgt[2] = SH[2];
		SVmodel_tgt[3] = SH[3];
		SVmodel_tgt[4] = SH[4];

		// actuate valves
		HSV_pos[0].SetLine( static_cast<float>(SH[0] * 5.0) );
		HSV_pos[1].SetLine( static_cast<float>(SH[1] * 5.0) );
		HSV_pos[2].SetLine( static_cast<float>(SH[2] * 5.0) );
		HSV_pos[3].SetLine( static_cast<float>(SH[3] * 5.0) );
		HSV_pos[4].SetLine( static_cast<float>(SH[4] * 5.0) );
		return;
	}

	void OutputElectronics_BLOCK_II::StorageRegister_write( unsigned short data, int ch )
	{
		if (PSE->Power() == false) return;
		// check WDT, listen to who is working
		if (!CIE[chA]->CheckWDTOwn( 0 ) && !CIE[chA]->CheckWDTOwn( 1 ))
		{
			// do chA
			if (ch == chA)
			{
				StorageRegister = data;
				CommandDecoder();
			}
		}
		else
		{
			if (!CIE[chB]->CheckWDTOwn( 0 ) && !CIE[chB]->CheckWDTOwn( 1 ))
			{
				// do chB
				if (ch == chB)
				{
					StorageRegister = data;
					CommandDecoder();
				}
			}
		}
		return;
	}

	unsigned short OutputElectronics_BLOCK_II::StorageRegister_read( void ) const
	{
		if (PSE->Power() == false) return 0;
		return StorageRegister;
	}

	unsigned short OutputElectronics_BLOCK_II::ONOFFCommandRegister_read( int num ) const
	{
		assert( (num >= 1) && (num <= 2) && "OutputElectronics_BLOCK_II::ONOFFCommandRegister_read.num" );
		if (PSE->Power() == false) return 0;
		return ONOFFCommandRegister[num - 1];
	}

	void OutputElectronics_BLOCK_II::CommandDecoder( void )
	{
		switch (GetMaskVal( StorageRegister, 0x000F ))
		{
			case CD_ONOFF_1:// ON/OFF 1
				ONOFFCommandRegister[0] = GetMaskVal( StorageRegister, 0xFFF0 );
				break;
			case CD_ONOFF_2:// ON/OFF 2
				ONOFFCommandRegister[1] = GetMaskVal( StorageRegister, 0xFFF0 );
				break;
			case CD_CCV:// CCV
				SH[0] = (double)(GetMaskVal( StorageRegister, 0xFFF0 ) >> 4) / 4095;
				break;
			case CD_MFV:// MFV
				SH[1] = (double)(GetMaskVal( StorageRegister, 0xFFF0 ) >> 4) / 4095;
				break;
			case CD_MOV:// MOV
				SH[2] = (double)(GetMaskVal( StorageRegister, 0xFFF0 ) >> 4) / 4095;
				break;
			case CD_FPOV:// FPOV
				SH[3] = (double)(GetMaskVal( StorageRegister, 0xFFF0 ) >> 4) / 4095;
				break;
			case CD_OPOV:// OPOV
				SH[4] = (double)(GetMaskVal( StorageRegister, 0xFFF0 ) >> 4) / 4095;
				break;
			default:
				oapiWriteLogV( " OutputElectronics_BLOCK_II::CommandDecoder || %d", StorageRegister );
		}
		return;
	}

	void OutputElectronics_BLOCK_II::GetSH( double* data )
	{
		if (PSE->Power() == false) return;
		memcpy( data, SH, 5 * sizeof(double) );
		return;
	}

	void OutputElectronics_BLOCK_II::GetPOS( double* data )
	{
		if (PSE->Power() == false) return;
		// HACK fix the delay on vlv pos
		// get valve position
		POS[0] = eng->ptrCCV->GetPos();
		POS[1] = eng->ptrMFV->GetPos();
		POS[2] = eng->ptrMOV->GetPos();
		POS[3] = eng->ptrFPOV->GetPos();
		POS[4] = eng->ptrOPOV->GetPos();
		POS[5] = eng->ptrFBV->GetPos();
		POS[6] = eng->ptrOBV->GetPos();
		POS[7] = eng->ptrAFV->GetPos();
		POS[8] = eng->ptrRIV->GetPos();

		memcpy( data, POS, 9 * sizeof(double) );
		return;
	}
}