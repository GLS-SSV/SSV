/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/01   GLS
2020/05/10   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/28   GLS
2021/06/26   GLS
2021/06/28   GLS
2021/07/31   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/02   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/06/03   GLS
2022/08/05   GLS
2022/08/10   GLS
2022/08/13   GLS
2022/08/20   GLS
********************************************/
#include <cassert>
#include "SimpleGPCSystem.h"
#include "SimpleGPCSoftware.h"
#include "SimpleShuttleBus.h"
#include "SimpleFCOS_IO.h"
#include "AscentDAP.h"
#include "OrbitDAP.h"
#include "OMSBurnSoftware.h"
#include "StateVectorSoftware.h"
#include "OrbitTgtSoftware.h"
#include "AerojetDAP.h"
#include "SSME_SOP.h"
#include "SSME_Operations.h"
#include "RSLS.h"
#include "MPS_Dedicated_Display_Driver.h"
#include "MPS_Dump.h"
#include "MM801.h"
#include "IO_Control.h"
#include "TransitionDAP.h"
#include "ETSepSequence.h"
#include "SRBSepSequence.h"
#include "MPS_ATVC_CMD_SOP.h"
#include "SRB_ATVC_CMD_SOP.h"
#include "GeneralDisplays.h"
#include "MEC_SOP.h"
#include "RHC_RM.h"
#include "THC_RM.h"
#include "RPTA_RM.h"
#include "SBTC_RM.h"
#include "RHC_SOP.h"
#include "THC_SOP.h"
#include "RPTA_SOP.h"
#include "SBTC_SOP.h"
#include "Switch_RM.h"
#include "TrimStationSelect.h"
#include "BF_Slew_SOP.h"
#include "Landing_SOP.h"
#include "OMS_TVC_Command_SOP.h"
#include "OMS_TVC_Feedback_SOP.h"
#include "DedicatedDisplay_SOP.h"
#include "RadarAltimeter_SOP.h"
#include "Entry_UPP.h"
#include "TAEM_UPP.h"
#include "AL_UPP.h"
#include "EGRT.h"
#include "EntryGuidance.h"
#include "TAEMGuidance.h"
#include "AutolandGuidance.h"
#include "LandingSite.h"
#include "RCSActivityLights.h"
#include "JetSelectionLogic.h"
#include "PriorityRateLimiting.h"
#include "Aero_Act_SOP.h"
#include "NW_POSN_SOP.h"
#include "Elevon_PFB_SOP.h"
#include "BodyFlap_PFB_SOP.h"
#include "Rudder_PFB_SOP.h"
#include "Speedbrake_PFB_SOP.h"
#include "DAPLightsDriver.h"
#include "VentCntlSeq.h"
#include "../Atlantis.h"

namespace dps
{

SimpleGPCSystem::SimpleGPCSystem( AtlantisSubsystemDirector* _director, const string& _ident ) : AtlantisSubsystem( _director, _ident )
{
	pFCOS_IO = new SimpleFCOS_IO( this );
	memset( SimpleCOMPOOL, 0, sizeof(unsigned short) * SIMPLECOMPOOL_SIZE );
	WriteBufferAddress = 0;
	WriteBufferLength = 0;
	SubSystemAddress = 0;

	WriteCOMPOOL_IS( SCP_MM, 101 );
	WriteCOMPOOL_IS( SCP_NEW_MM, static_cast<unsigned short>(-1) );

	vSoftware.push_back( new Elevon_PFB_SOP( this ) );
	vSoftware.push_back( new BodyFlap_PFB_SOP( this ) );
	vSoftware.push_back( new Rudder_PFB_SOP( this ) );
	vSoftware.push_back( new Speedbrake_PFB_SOP( this ) );
	vSoftware.push_back( new NW_POSN_SOP( this ) );
	vSoftware.push_back( new MPS_Dump( this ) );
	vSoftware.push_back( new MPS_Dedicated_Display_Driver( this ) );
	vSoftware.push_back( new SSME_Operations( this ) );
	vSoftware.push_back( new SSME_SOP( this ) );
	vSoftware.push_back( new RSLS( this ) );
	vSoftware.push_back( new AscentDAP( this ) );
	vSoftware.push_back( new OrbitDAP( this ) );
	vSoftware.push_back( new StateVectorSoftware( this ) );
	vSoftware.push_back( new OMSBurnSoftware( this ) );
	vSoftware.push_back( new OrbitTgtSoftware( this ) );
	vSoftware.push_back( new RadarAltimeter_SOP( this ) );
	vSoftware.push_back( new LandingSite( this ) );
	vSoftware.push_back( new Entry_UPP( this ) );
	vSoftware.push_back( new TAEM_UPP( this ) );
	vSoftware.push_back( new AL_UPP( this ) );
	vSoftware.push_back( new EGRT( this ) );
	vSoftware.push_back( new EntryGuidance( this ) );
	vSoftware.push_back( new TAEMGuidance( this ) );
	vSoftware.push_back( new AutolandGuidance( this ) );
	vSoftware.push_back( new AerojetDAP( this ) );
	vSoftware.push_back( new MM801( this ) );
	vSoftware.push_back( new IO_Control( this ) );
	vSoftware.push_back( new TransitionDAP( this ) );
	vSoftware.push_back( new ETSepSequence( this ) );
	vSoftware.push_back( new SRBSepSequence( this ) );
	vSoftware.push_back( new MPS_ATVC_CMD_SOP( this ) );
	vSoftware.push_back( new SRB_ATVC_CMD_SOP( this ) );
	vSoftware.push_back( new GeneralDisplays( this ) );
	vSoftware.push_back( new MEC_SOP( this ) );
	vSoftware.push_back( new RHC_RM( this ) );
	vSoftware.push_back( new THC_RM( this ) );
	vSoftware.push_back( new RPTA_RM( this ) );
	vSoftware.push_back( new SBTC_RM( this ) );
	vSoftware.push_back( new RHC_SOP( this ) );
	vSoftware.push_back( new THC_SOP( this ) );
	vSoftware.push_back( new RPTA_SOP( this ) );
	vSoftware.push_back( new SBTC_SOP( this ) );
	vSoftware.push_back( new Switch_RM( this ) );
	vSoftware.push_back( new TrimStationSelect( this ) );
	vSoftware.push_back( new BF_Slew_SOP( this ) );
	vSoftware.push_back( new Landing_SOP( this ) );
	vSoftware.push_back( new OMSTVCCMD_SOP( this ) );
	vSoftware.push_back( new OMSTVCFDBK_SOP( this ) );
	vSoftware.push_back( new DedicatedDisplay_SOP( this ) );
	vSoftware.push_back( new RCSActivityLights( this ) );
	vSoftware.push_back( new JetSelectionLogic( this ) );
	vSoftware.push_back( new PriorityRateLimiting( this ) );
	vSoftware.push_back( new Aero_Act_SOP( this ) );
	vSoftware.push_back( new DAPLightsDriver( this ) );
	vSoftware.push_back( new VentCntlSeq( this ) );

	// I-LOADs init
	WriteCOMPOOL_IS( SCP_KMIN, 67 );
	WriteCOMPOOL_IS( SCP_OVHD, 1 );
	WriteCOMPOOL_IS( SCP_IGS, 1 );
	WriteCOMPOOL_IS( SCP_IGI, 1 );
	WriteCOMPOOL_IS( SCP_RWID, 1 );
	WriteCOMPOOL_IS( SCP_LSID, 1 );
	WriteCOMPOOL_M( SCP_AL_R, 1, 1, 25896.8f, 2, 2 );
	WriteCOMPOOL_M( SCP_AL_R, 2, 1, 26409.5f, 2, 2 );
	WriteCOMPOOL_M( SCP_AL_R, 1, 2, 32218.9f, 2, 2 );
	WriteCOMPOOL_M( SCP_AL_R, 2, 2, 32860.9f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 1, 1, -3313.48f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 2, 1, -2138.13f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 1, 2, -2775.87f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 2, 2, -1577.49f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 1, 1, 26035.03f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 2, 1, 26516.81f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 1, 2, 32341.99f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 2, 2, 32952.57f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 1, 1, -4901.98f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 2, 1, -3757.87f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 1, 2, -4533.71f, 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 2, 2, -3374.8f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 1, 1, 32.45f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 2, 1, 32.44f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 1, 2, 26.18f, 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 2, 2, 26.3f, 2, 2 );
	WriteCOMPOOL_SD( SCP_SIGMA, 920.0 );
	WriteCOMPOOL_V( SCP_GAMMA_REF_1, 1, -20.0, 2 );
	WriteCOMPOOL_V( SCP_GAMMA_REF_1, 2, -18.0, 2 );
	WriteCOMPOOL_SD( SCP_GAMMA_REF_2, -1.5 );
	WriteCOMPOOL_V( SCP_X_ZERO, 1, -7500.0, 2 );
	WriteCOMPOOL_V( SCP_X_ZERO, 2, -6500.0, 2 );
	WriteCOMPOOL_SD( SCP_X_AIM, 1000.0 );
	WriteCOMPOOL_SD( SCP_H_FLARE, 2000.0 );
	WriteCOMPOOL_SD( SCP_H_CLOOP, 1700.0 );
	WriteCOMPOOL_IS( SCP_SB_SEL, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, 1 );
	WriteCOMPOOL_IS( SCP_WOWLON, 0 );
	WriteCOMPOOL_IS( SCP_FLATTURN, 0 );
	WriteCOMPOOL_IS( SCP_ROLLOUT, 0 );
	WriteCOMPOOL_IS( SCP_GSENBL, 0 );
	WriteCOMPOOL_IS( SCP_HUD_WOWLON, 0 );
	WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, 0 );
	WriteCOMPOOL_IS( SCP_PMODE, 1 );
	WriteCOMPOOL_IS( SCP_FMODE, 1 );
	WriteCOMPOOL_IS( SCP_IPHASE, 1 );
	WriteCOMPOOL_IS( SCP_TG_END, 0 );
	WriteCOMPOOL_SD( SCP_WT_GS1, 6837.808943f );
	WriteCOMPOOL_SD( SCP_RF0, 14000.0 );
	WriteCOMPOOL_SD( SCP_R1, 0.0 );
	WriteCOMPOOL_SD( SCP_R2, 0.093f );
	WriteCOMPOOL_SD( SCP_PSHARS, 270.0 );
	WriteCOMPOOL_SD( SCP_RMOH, 273500.0 );
	WriteCOMPOOL_SD( SCP_HUDMAXDECEL, 16.0 );
	WriteCOMPOOL_SD( SCP_RWTOGO, 1000.0 );
	WriteCOMPOOL_SD( SCP_SBDMN, 950.0 );
	WriteCOMPOOL_SD( SCP_SBDMX, 9800.0 );
	WriteCOMPOOL_SD( SCP_SBDLIM, 20.0 );
	WriteCOMPOOL_IS( SCP_WRAP, 1 );
}

SimpleGPCSystem::~SimpleGPCSystem()
{
	for(unsigned int i=0;i<vSoftware.size();i++)
		delete vSoftware[i];
}

void SimpleGPCSystem::busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
{
	GetBus()->SendCommand( cw, cdw );
	return;
}

void SimpleGPCSystem::busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
{
	if (cdw == NULL) return;
	pFCOS_IO->busRead( cdw );
	return;
}

void SimpleGPCSystem::SetMajorMode( unsigned short newMM )
{
	// check if valid
	switch (newMM)
	{
		case 0:
		case 101:
		case 102:
		case 103:
		case 104:
		case 105:
		case 106:
		case 201:
		case 202:
		case 301:
		case 302:
		case 303:
		case 304:
		case 305:
		case 401:
		case 402:
		case 601:
		case 602:
		case 603:
		case 801:
		case 901:
			WriteCOMPOOL_IS( SCP_NEW_MM, newMM );
	}
	return;
}

bool SimpleGPCSystem::IsValidMajorModeTransition( unsigned short newMajorMode ) const
{
	unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
	switch (newMajorMode)
	{
		case 0:
			return (MM == 201 || MM == 901);
		case 101:
			return MM == 901;
		/*case 102:
			return MM == 101;
		case 103:
			return MM == 102;*/
		case 104:
			return MM == 103;
		case 105:
			return MM == 104;
		case 106:
			return MM == 105;
		case 201:
			return (MM == 0 || MM == 106 || MM == 202 || MM == 301 || MM == 801);
		case 202:
			return MM == 201;
		case 301:
			return (MM == 0 || MM == 104 || MM == 105 || MM == 106 || MM == 201 || MM == 302 || MM == 801);
		case 302:
			return MM == 301;
		case 303:
			return MM == 302;
		case 304:
			return MM == 303;
		case 305:
			return MM == 304;
		/*case 601:
			return (MM == 102 || MM == 103);
		case 602:
			return (MM == 104 || MM == 601);
		case 603:
			return MM == 602;*/
		case 801:
			return MM == 201;
		case 901:
			return (MM == 0 || MM == 101 || MM == 305 || MM == 603);
		default:
			return false;
	}
}

bool SimpleGPCSystem::IsValidSPEC( unsigned short spec ) const
{
	// PASS system
	switch (spec)
	{
		case 0:// GPC MEMORY
		case 1:// DPS UTILITY
			return true;
		case 2:// TIME
			switch (ReadCOMPOOL_IS( SCP_MM ) / 100)// GNC
			{
				case 1:
				case 3:
				case 6:
					return false;
				default:
					return true;
			}
	}

	// PASS GNC
	switch (spec)
	{
		case 20:// DAP CONFIG
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
			else return false;
		case 21:// IMU ALIGN
			switch (ReadCOMPOOL_IS( SCP_MM ) / 100)
			{
				case 2:
				case 3:
					return true;
				default:
					return false;
			}
		case 22:// S TRK/COAS CNTL
			switch (ReadCOMPOOL_IS( SCP_MM ))
			{
				case 201:
				case 202:
				case 301:
					return true;
				default:
					return false;
			}
		case 23:// RCS
			switch (ReadCOMPOOL_IS( SCP_MM ) / 100)
			{
				case 1:
				case 2:
				case 3:
				case 6:
				case 8:
					return true;
				default:
					return false;
			}
		case 25:// RM ORBIT
		case 33:// REL NAV
		case 34:// ORBIT TGT
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
			else return false;
		case 40:// SENSOR TEST
		case 41:// RGA/ADTA/RCS
		case 42:// SWITCH/SURF
		case 43:// CONTROLLERS
		case 44:// SWITCHES
		case 45:// NWS CHECK
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 8) return true;
			else return false;
		case 50:// HORIZ SIT
		case 51:// OVERRIDE
		case 53:// CONTROLS
			switch (ReadCOMPOOL_IS( SCP_MM ) / 100)
			{
				case 1:
				case 3:
				case 6:
					return true;
				default:
					return false;
			}
		case 55:// GPS STATUS
			switch (ReadCOMPOOL_IS( SCP_MM ) / 100)
			{
				case 1:
				case 2:
				case 3:
				case 6:
				case 8:
				case 9:
					return true;
				default:
					return false;
			}
		case 62:// PCMMU/PL COMM
		case 100:// GTS DISPLAY
		case 101:// SENSOR SELF-TEST
		case 102:// RCS/RGA/ADTA TEST
		case 104:// GND IMU CNTL/MON
		case 105:// TCS CONTROL
		case 112:// GPC/BTU I/F
		case 113:// ACTUATOR CONTROL
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 9) return true;
			else return false;
	}

	// PASS SM
	switch (spec)
	{
		case 60:// SM TABLE MAINT
		case 62:// PCMMU/PL COMM
		case 64:// SM GROUND CHECKOUT
		case 85:// MASS MEMORY R/W
		case 90:// PCS CONTROL
		case 94:// PDRS CONTROL
		case 95:// PDRS OVERRIDE
			return true;
	}

	// PASS PL
	switch (spec)
	{
		case 100:// GTS DISPLAY
		case 111:// SL MEMORY DUMP
			return true;
	}

	// BFS GNC
	switch (spec)
	{
		case 50:// HORIZ SIT
		case 51:// OVERRIDE
		case 55:// GPS STATUS
			return true;
	}

	// BFS SM
	switch (spec)
	{
		case 63:// PL BAY DOORS
			return true;
	}
	return false;
}

bool SimpleGPCSystem::IsValidDISP( unsigned short disp ) const
{
	// PASS system
	switch (disp)
	{
		case 6:// GPC/BUS STATUS
		case 99:// FAULT
			return true;
	}

	// PASS GNC
	switch (disp)
	{
		case 18:// GNC SYS SUMM 1
			return true;
		case 19:// GNC SYS SUMM 2
			switch (ReadCOMPOOL_IS( SCP_MM ) / 100)
			{
				case 2:
				case 8:
					return true;
				default:
					return false;
			}
		case 106:// MANUAL CONTROLS
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 9) return true;
			else return false;
	}

	// PASS SM
	switch (disp)
	{
		case 66:// ENVIRONMENT
		case 67:// ELECTRIC
		case 68:// CRYO SYSTEM
		case 69:// FUEL CELLS
		case 76:// COMMUNICATIONS
		case 77:// EVA-MMU/FSS
		case 78:// SM SYS SUMM 1
		case 79:// SM SYS SUMM 2
		case 86:// APU/HYD
		case 87:// HYD THERMAL
		case 88:// APU/ENVIRON THERM
		case 89:// PRPLT THERMAL
		case 96:// PDRS FAULTS
		case 97:// PL RETENTION
			return true;
		case 167:// DOCKING STATUS
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
			else return false;
		case 168:// CARGO LOOP
		case 169:// PDRS STATUS
			return true;
		case 177:// EXTERNAL AIRLOCK
		case 179:// POWER TRANSFER
			if ((ReadCOMPOOL_IS( SCP_MM ) / 100) == 2) return true;
			else return false;
	}

	// BFS system
	switch (disp)
	{
		case 99:// FAULT
			return true;
	}

	// BFS GNC
	switch (disp)
	{
		case 6:// GPC/BUS STATUS
		case 18:// GNC SYS SUMM 1
		case 19:// GNC SYS SUMM 2
			return true;
	}

	// BFS SM
	switch (disp)
	{
		case 78:// SM SYS SUMM 1
		case 79:// SM SYS SUMM 2
		case 168:// CRYO PALLET/CARGO
			return true;
	}
	return false;
}

void SimpleGPCSystem::Realize()
{
	for(unsigned int i=0;i<vSoftware.size();i++)
		vSoftware[i]->Realize();
}

void SimpleGPCSystem::OnPreStep(double simt, double simdt, double mjd)
{
	// if major mode changed sometime in the last timestep, update major mode
	if (ReadCOMPOOL_IS( SCP_NEW_MM ) != static_cast<unsigned short>(-1))
	{
		vActiveSoftware.clear();
		for (unsigned int i = 0; i < vSoftware.size(); i++)
		{
			if (vSoftware[i]->OnMajorModeChange( ReadCOMPOOL_IS( SCP_NEW_MM ) ))
				vActiveSoftware.push_back( vSoftware[i] );
		}
		WriteCOMPOOL_IS( SCP_MM, ReadCOMPOOL_IS( SCP_NEW_MM ) );
		WriteCOMPOOL_IS( SCP_NEW_MM, static_cast<unsigned short>(-1) );
	}

	pFCOS_IO->input();// input data from subsystems

	for (unsigned int i = 0; i < vActiveSoftware.size(); i++)
		vActiveSoftware[i]->OnPreStep( simt, simdt, mjd );
}

void SimpleGPCSystem::OnPostStep(double simt, double simdt, double mjd)
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++)
		vActiveSoftware[i]->OnPostStep(simt, simdt, mjd);

	pFCOS_IO->output();// output commands to subsystems
}

void SimpleGPCSystem::OnPropagate(double simt, double simdt, double mjd)
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++)
		vActiveSoftware[i]->OnPropagate(simt, simdt, mjd);
}

bool SimpleGPCSystem::OnReadState(FILEHANDLE scn)
{
	char* line;
	char pszKey[256];
	SimpleGPCSoftware* pCurrentSoftware = NULL;
	while(oapiReadScenario_nextline(scn, line)) {
		if(!_strnicmp(line, "@ENDSUBSYSTEM", 13)) {
			return true;
		} else {
			if(!_strnicmp(line, "@ENDSOFTWARE", 12)) {
				pCurrentSoftware = NULL;
			}
			else {
				unsigned long i = 0;
				while(*line != ' ' && *line != '\0') {
					pszKey[i++] = *line;
					line++;
				}
				pszKey[i++] = '\0';
				if(*line == ' ') line++;
				if(!_strnicmp(pszKey, "@BEGINSOFTWARE", 14)) {
					pCurrentSoftware = FindSoftware(line);
				}
				else if(pCurrentSoftware) {
					if(*line != '\0') {
						pCurrentSoftware->OnParseLine(pszKey, line);
					} else {
						pCurrentSoftware->OnParseLine(pszKey, NULL);
					}
				}
				else
				{
					// SimpleCOMPOOL vals
					if (!_strnicmp( pszKey, "MM", 2 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						SetMajorMode( tmp );
					}
					else if (!_strnicmp( pszKey, "OVHD", 4 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_OVHD, tmp );
					}
					else if (!_strnicmp( pszKey, "IGS", 3 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_IGS, tmp );
					}
					else if (!_strnicmp( pszKey, "IGI", 3 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_IGI, tmp );
					}
					else if (!_strnicmp( pszKey, "RWID0", 5 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_RWID0, tmp );
					}
					else if (!_strnicmp( pszKey, "RWID", 4 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_RWID, tmp );
					}
					else if (!_strnicmp( pszKey, "LSID", 4 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 45)) WriteCOMPOOL_IS( SCP_LSID, tmp );
					}
					else if (!_strnicmp( pszKey, "SB_SEL", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 3)) WriteCOMPOOL_IS( SCP_SB_SEL, tmp );
					}
					else if (!_strnicmp( pszKey, "AEROJET_FCS_PITCH", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, tmp );
					}
					else if (!_strnicmp( pszKey, "AEROJET_FCS_ROLL", 16 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, tmp );
					}
					else if (!_strnicmp( pszKey, "AEROJET_FCS_SB", 14 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 3)) WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, tmp );
					}
					else if (!_strnicmp( pszKey, "AEROJET_FCS_BF", 14 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, tmp );
					}
					else if (!_strnicmp( pszKey, "RETRACT_BF", 10 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_RETRACT_BF, tmp );
					}
					else if (!_strnicmp( pszKey, "WOWLON", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_WOWLON, tmp );
					}
					else if (!_strnicmp( pszKey, "FLATTURN", 8 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_FLATTURN, tmp );
					}
					else if (!_strnicmp( pszKey, "ROLLOUT", 7 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ROLLOUT, tmp );
					}
					else if (!_strnicmp( pszKey, "GSENBL", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_GSENBL, tmp );
					}
					else if (!_strnicmp( pszKey, "HUD_WOWLON", 10 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_HUD_WOWLON, tmp );
					}
					else if (!_strnicmp( pszKey, "HUD_ROLLOUT", 11 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, tmp );
					}
					else if (!_strnicmp( pszKey, "PMODE", 5 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 4)) WriteCOMPOOL_IS( SCP_PMODE, tmp );
					}
					else if (!_strnicmp( pszKey, "FMODE", 5 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 3)) WriteCOMPOOL_IS( SCP_FMODE, tmp );
					}
					else if (!_strnicmp( pszKey, "IPHASE", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 3) WriteCOMPOOL_IS( SCP_IPHASE, tmp );
					}
					else if (!_strnicmp( pszKey, "TG_END", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_TG_END, tmp );
					}
					else if (!_strnicmp( pszKey, "ISLECT", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 5)) WriteCOMPOOL_IS( SCP_ISLECT, tmp );
					}
					else if (!_strnicmp( pszKey, "DLRDOT", 6 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SD( SCP_DLRDOT, tmp );
					}
					else if (!_strnicmp( pszKey, "MEP", 3 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_MEP, tmp );
					}
					else if (!_strnicmp( pszKey, "YSGN", 4 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						if ((tmp == 1.0) || (tmp == -1.0)) WriteCOMPOOL_SD( SCP_YSGN, tmp );
					}
					else if (!_strnicmp( pszKey, "RF", 2 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SD( SCP_RF, tmp );
					}
					else if (!_strnicmp( pszKey, "PSHA", 4 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SD( SCP_PSHA, tmp );
					}
					else if (!_strnicmp( pszKey, "RTURN", 5 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SD( SCP_RTURN, tmp );
					}
					else if (!_strnicmp( pszKey, "XHAC", 4 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SD( SCP_XHAC, tmp );
					}
					else if (!_strnicmp( pszKey, "WRAP", 4 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 2) WriteCOMPOOL_IS( SCP_WRAP, tmp );
					}
					else if(*line != '\0') {
						this->OnParseLine(pszKey, line);
					} else {
						this->OnParseLine(pszKey, NULL);
					}
				}
			}
		}
	}

	return false;
}

void SimpleGPCSystem::OnSaveState(FILEHANDLE scn) const
{
	// SimpleCOMPOOL vals
	oapiWriteScenario_int( scn, "MM", ReadCOMPOOL_IS( SCP_MM ) );

	oapiWriteScenario_int( scn, "OVHD", ReadCOMPOOL_IS( SCP_OVHD ) );
	oapiWriteScenario_int( scn, "IGS", ReadCOMPOOL_IS( SCP_IGS ) );
	oapiWriteScenario_int( scn, "IGI", ReadCOMPOOL_IS( SCP_IGI ) );
	oapiWriteScenario_int( scn, "RWID", ReadCOMPOOL_IS( SCP_RWID ) );
	oapiWriteScenario_int( scn, "RWID0", ReadCOMPOOL_IS( SCP_RWID0 ) );
	oapiWriteScenario_int( scn, "LSID", ReadCOMPOOL_IS( SCP_LSID ) );

	oapiWriteScenario_int( scn, "SB_SEL", ReadCOMPOOL_IS( SCP_SB_SEL ) );

	oapiWriteScenario_int( scn, "AEROJET_FCS_PITCH", ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH ) );
	oapiWriteScenario_int( scn, "AEROJET_FCS_ROLL", ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL ) );
	oapiWriteScenario_int( scn, "AEROJET_FCS_SB", ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) );
	oapiWriteScenario_int( scn, "AEROJET_FCS_BF", ReadCOMPOOL_IS( SCP_AEROJET_FCS_BF ) );
	oapiWriteScenario_int( scn, "RETRACT_BF", ReadCOMPOOL_IS( SCP_RETRACT_BF ) );

	oapiWriteScenario_int( scn, "WOWLON", ReadCOMPOOL_IS( SCP_WOWLON ) );
	oapiWriteScenario_int( scn, "FLATTURN", ReadCOMPOOL_IS( SCP_FLATTURN ) );
	oapiWriteScenario_int( scn, "ROLLOUT", ReadCOMPOOL_IS( SCP_ROLLOUT ) );
	oapiWriteScenario_int( scn, "GSENBL", ReadCOMPOOL_IS( SCP_GSENBL ) );
	oapiWriteScenario_int( scn, "HUD_WOWLON", ReadCOMPOOL_IS( SCP_HUD_WOWLON ) );
	oapiWriteScenario_int( scn, "HUD_ROLLOUT", ReadCOMPOOL_IS( SCP_HUD_ROLLOUT ) );

	oapiWriteScenario_int( scn, "PMODE", ReadCOMPOOL_IS( SCP_PMODE ) );
	oapiWriteScenario_int( scn, "FMODE", ReadCOMPOOL_IS( SCP_FMODE ) );

	oapiWriteScenario_int( scn, "IPHASE", ReadCOMPOOL_IS( SCP_IPHASE ) );
	oapiWriteScenario_int( scn, "TG_END", ReadCOMPOOL_IS( SCP_TG_END ) );

	oapiWriteScenario_int( scn, "ISLECT", ReadCOMPOOL_IS( SCP_ISLECT ) );
	oapiWriteScenario_float( scn, "DLRDOT", ReadCOMPOOL_SD( SCP_DLRDOT ) );

	oapiWriteScenario_int( scn, "MEP", ReadCOMPOOL_IS( SCP_MEP ) );
	oapiWriteScenario_float( scn, "YSGN", ReadCOMPOOL_SD( SCP_YSGN ) );
	oapiWriteScenario_float( scn, "RF", ReadCOMPOOL_SD( SCP_RF ) );
	oapiWriteScenario_float( scn, "PSHA", ReadCOMPOOL_SD( SCP_PSHA ) );
	oapiWriteScenario_float( scn, "RTURN", ReadCOMPOOL_SD( SCP_RTURN ) );
	oapiWriteScenario_float( scn, "XHAC", ReadCOMPOOL_SD( SCP_XHAC ) );

	oapiWriteScenario_int( scn, "WRAP", ReadCOMPOOL_IS( SCP_WRAP ) );


	for(unsigned int i=0;i<vActiveSoftware.size();i++) {
		oapiWriteScenario_string(scn, "@BEGINSOFTWARE", const_cast<char*>(vActiveSoftware[i]->GetIdentifier().c_str()));
		vActiveSoftware[i]->OnSaveState(scn);
		oapiWriteLine( scn, "  @ENDSOFTWARE" );
	}
}

bool SimpleGPCSystem::ItemInput(int spec, int item, const char* Data)
{
	bool illegalentry = false;
	for(unsigned int i=0;i<vActiveSoftware.size();i++) {
		if(vActiveSoftware[i]->ItemInput(spec, item, Data, illegalentry ))
			break;
	}
	return !illegalentry;
}

bool SimpleGPCSystem::ExecPressed(int spec)
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++) {
		if(vActiveSoftware[i]->ExecPressed(spec))
			return true;
	}
	return false;
}

bool SimpleGPCSystem::OnPaint(int spec, vc::MDU* pMDU) const
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++) {
		if(vActiveSoftware[i]->OnPaint(spec, pMDU))
			return true;
	}
	return false;
}

SimpleGPCSoftware* SimpleGPCSystem::FindSoftware(const std::string& identifier) const
{
	for(unsigned int i=0;i<vSoftware.size();i++) {
		if(vSoftware[i]->GetIdentifier() == identifier) {
			return vSoftware[i];
		}
	}
	return NULL;
}

unsigned short SimpleGPCSystem::ReadCOMPOOL_IS( unsigned int addr ) const
{
	if (addr < SIMPLECOMPOOL_SIZE)
		return SimpleCOMPOOL[addr];
	return 0;
}

unsigned int SimpleGPCSystem::ReadCOMPOOL_ID( unsigned int addr ) const
{
	unsigned int tmp = 0;
	if (addr < SIMPLECOMPOOL_SIZE)
		memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
	return tmp;
}

float SimpleGPCSystem::ReadCOMPOOL_SD( unsigned int addr ) const
{
	float tmp = 0.0f;
	if (addr < (SIMPLECOMPOOL_SIZE - 1))
		memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
	return tmp;
}

MATRIX3 SimpleGPCSystem::ReadCOMPOOL_M( unsigned int addr ) const
{
	MATRIX3 m3 = _M( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
	float tmp = 0.0f;

	if (addr < (SIMPLECOMPOOL_SIZE - 17))
	{
		memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
		m3.m11 = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 2, 4 );
		m3.m12 = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 4, 4 );
		m3.m13 = tmp;

		memcpy( &tmp, SimpleCOMPOOL + addr + 6, 4 );
		m3.m21 = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 8, 4 );
		m3.m22 = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 10, 4 );
		m3.m23 = tmp;

		memcpy( &tmp, SimpleCOMPOOL + addr + 12, 4 );
		m3.m31 = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 14, 4 );
		m3.m32 = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 16, 4 );
		m3.m33 = tmp;
	}
	return m3;
}

float SimpleGPCSystem::ReadCOMPOOL_M( unsigned int addr, unsigned int m, unsigned int n, unsigned int msize, unsigned int nsize ) const
{
	float tmp = 0.0f;
	if ((n > 0) && (n <= nsize) && (m > 0) && (m <= msize))
	{
		if (addr < (SIMPLECOMPOOL_SIZE - ((nsize * msize * 2) - 1)))
		{
			memcpy( &tmp, SimpleCOMPOOL + addr + ((((m - 1) * nsize) + (n - 1)) * 2), 4 );
		}
	}
	return tmp;
}

VECTOR3 SimpleGPCSystem::ReadCOMPOOL_V( unsigned int addr ) const
{
	VECTOR3 v3 = _V( 0.0, 0.0, 0.0 );
	float tmp = 0.0f;

	if (addr < (SIMPLECOMPOOL_SIZE - 5))
	{
		memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
		v3.x = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 2, 4 );
		v3.y = tmp;
		memcpy( &tmp, SimpleCOMPOOL + addr + 4, 4 );
		v3.z = tmp;
	}
	return v3;
}

float SimpleGPCSystem::ReadCOMPOOL_V( unsigned int addr, unsigned int n, unsigned int nsize ) const
{
	float tmp = 0.0f;
	if ((n > 0) && (n <= nsize))
	{
		if (addr < (SIMPLECOMPOOL_SIZE - ((nsize * 2) - 1)))
		{
			memcpy( &tmp, SimpleCOMPOOL + addr + ((n - 1) * 2), 4 );
		}
	}
	return tmp;
}

void SimpleGPCSystem::ReadCOMPOOL_C( unsigned int addr, char* val, unsigned int size ) const
{
	if (addr < (SIMPLECOMPOOL_SIZE - size - 1))
	{
		for (unsigned int i = 0; i < size; i++)
		{
			val[i] = static_cast<char>(SimpleCOMPOOL[addr + i]);
			if (SimpleCOMPOOL[addr + i] == 0) break;
		}
	}
	return;
}

unsigned short SimpleGPCSystem::ReadCOMPOOL_AIS( unsigned int addr, unsigned int idx, unsigned int size ) const
{
	if ((idx > 0) && (idx <= size))
	{
		if (addr < (SIMPLECOMPOOL_SIZE - size - 1))
		{
			return SimpleCOMPOOL[addr + idx - 1];
		}
	}
	return 0;
}

void SimpleGPCSystem::WriteCOMPOOL_IS( unsigned int addr, unsigned short val )
{
	if (addr < SIMPLECOMPOOL_SIZE)
		SimpleCOMPOOL[addr] = val;
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_ID( unsigned int addr, unsigned int val )
{
	if (addr < SIMPLECOMPOOL_SIZE)
		memcpy( SimpleCOMPOOL + addr, &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_SD( unsigned int addr, float val )
{
	if (addr < (SIMPLECOMPOOL_SIZE - 1))
		memcpy( SimpleCOMPOOL + addr, &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_M( unsigned int addr, MATRIX3& val )
{
	float tmp = 0.0f;

	if (addr < (SIMPLECOMPOOL_SIZE - 17))
	{
		tmp = static_cast<float>(val.m11);
		memcpy( SimpleCOMPOOL + addr, &tmp, 4 );
		tmp = static_cast<float>(val.m12);
		memcpy( SimpleCOMPOOL + addr + 2, &tmp, 4 );
		tmp = static_cast<float>(val.m13);
		memcpy( SimpleCOMPOOL + addr + 4, &tmp, 4 );

		tmp = static_cast<float>(val.m21);
		memcpy( SimpleCOMPOOL + addr + 6, &tmp, 4 );
		tmp = static_cast<float>(val.m22);
		memcpy( SimpleCOMPOOL + addr + 8, &tmp, 4 );
		tmp = static_cast<float>(val.m23);
		memcpy( SimpleCOMPOOL + addr + 10, &tmp, 4 );

		tmp = static_cast<float>(val.m31);
		memcpy( SimpleCOMPOOL + addr + 12, &tmp, 4 );
		tmp = static_cast<float>(val.m32);
		memcpy( SimpleCOMPOOL + addr + 14, &tmp, 4 );
		tmp = static_cast<float>(val.m33);
		memcpy( SimpleCOMPOOL + addr + 16, &tmp, 4 );
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_M( unsigned int addr, unsigned int m, unsigned int n, float val, unsigned int msize, unsigned int nsize )
{
	if ((n > 0) && (n <= nsize) && (m > 0) && (m <= msize))
	{
		if (addr < (SIMPLECOMPOOL_SIZE - ((nsize * msize * 2) - 1)))
		{
			memcpy( SimpleCOMPOOL + addr + ((((m - 1) * nsize) + (n - 1)) * 2), &val, 4 );
		}
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_V( unsigned int addr, VECTOR3& val )
{
	float tmp = 0.0f;

	if (addr < (SIMPLECOMPOOL_SIZE - 5))
	{
		tmp = static_cast<float>(val.x);
		memcpy( SimpleCOMPOOL + addr, &tmp, 4 );
		tmp = static_cast<float>(val.y);
		memcpy( SimpleCOMPOOL + addr + 2, &tmp, 4 );
		tmp = static_cast<float>(val.z);
		memcpy( SimpleCOMPOOL + addr + 4, &tmp, 4 );
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_V( unsigned int addr, unsigned int n, float val, unsigned int nsize )
{
	if ((n > 0) && (n <= nsize))
	{
		if (addr < (SIMPLECOMPOOL_SIZE - ((nsize * 2) - 1)))
		{
			memcpy( SimpleCOMPOOL + addr + ((n - 1) * 2), &val, 4 );
		}
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_C( unsigned int addr, const char* val, unsigned int size )
{
	if (addr < (SIMPLECOMPOOL_SIZE - size - 1))
	{
		for (unsigned int i = 0; i < size; i++)
		{
			SimpleCOMPOOL[addr + i] = val[i];
			if (val[i] == 0) break;
		}
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_AIS( unsigned int addr, unsigned int idx, unsigned short val, unsigned int size )
{
	if ((idx > 0) && (idx <= size))
	{
		if (addr < (SIMPLECOMPOOL_SIZE - size - 1))
		{
			memcpy( SimpleCOMPOOL + addr + idx - 1, &val, 2 );
		}
	}
	return;
}

void SimpleGPCSystem::LoadILOADs( const std::map<std::string,std::string>& ILOADlist )
{
	// COMPOOL
	SimpleCOMPOOLReadILOADs( ILOADlist );

	// SimpleGPCSoftware
	for (unsigned int i = 0;i < vSoftware.size(); i++) vSoftware[i]->ReadILOADs( ILOADlist );
	return;
}

void SimpleGPCSystem::SimpleCOMPOOLReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	unsigned short itmp = 0;
	double dtmp1 = 0;
	double dtmp[4];

	SimpleGPCSoftware::GetValILOAD( "KMIN", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_KMIN, itmp );

	SimpleGPCSoftware::GetValILOAD( "OVHD", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_OVHD, itmp );

	SimpleGPCSoftware::GetValILOAD( "IGS", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_IGS, itmp );

	SimpleGPCSoftware::GetValILOAD( "IGI", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_IGI, itmp );

	SimpleGPCSoftware::GetValILOAD( "RWID", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_RWID, itmp );

	SimpleGPCSoftware::GetValILOAD( "LSID", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_LSID, itmp );

	SimpleGPCSoftware::GetValILOAD( "AL_R", ILOADs, 4, dtmp );
	WriteCOMPOOL_M( SCP_AL_R, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_M( SCP_AL_R, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_M( SCP_AL_R, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_M( SCP_AL_R, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_M( SCP_X_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_M( SCP_X_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "H_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_M( SCP_H_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_M( SCP_H_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_EXP", ILOADs, 4, dtmp );
	WriteCOMPOOL_M( SCP_X_EXP, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_M( SCP_X_EXP, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "H_DECAY", ILOADs, 4, dtmp );
	WriteCOMPOOL_M( SCP_H_DECAY, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_M( SCP_H_DECAY, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "SIGMA", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SIGMA, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_1", ILOADs, 2, dtmp );
	WriteCOMPOOL_V( SCP_GAMMA_REF_1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_V( SCP_GAMMA_REF_1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_2", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_GAMMA_REF_2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_ZERO", ILOADs, 2, dtmp );
	WriteCOMPOOL_V( SCP_X_ZERO, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_V( SCP_X_ZERO, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "X_AIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_X_AIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_FLARE", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_H_FLARE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_CLOOP", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_H_CLOOP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SB_SEL", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_SB_SEL, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_PITCH", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_ROLL", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_SB", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_BF", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, itmp );

	SimpleGPCSoftware::GetValILOAD( "WOWLON", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_WOWLON, itmp );

	SimpleGPCSoftware::GetValILOAD( "FLATTURN", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_FLATTURN, itmp );

	SimpleGPCSoftware::GetValILOAD( "ROLLOUT", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_ROLLOUT, itmp );

	SimpleGPCSoftware::GetValILOAD( "GSENBL", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_GSENBL, itmp );

	SimpleGPCSoftware::GetValILOAD( "HUD_WOWLON", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_HUD_WOWLON, itmp );

	SimpleGPCSoftware::GetValILOAD( "HUD_ROLLOUT", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, itmp );

	SimpleGPCSoftware::GetValILOAD( "PMODE", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_PMODE, itmp );

	SimpleGPCSoftware::GetValILOAD( "FMODE", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_FMODE, itmp );

	SimpleGPCSoftware::GetValILOAD( "IPHASE", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_IPHASE, itmp );

	SimpleGPCSoftware::GetValILOAD( "TG_END", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_TG_END, itmp );

	SimpleGPCSoftware::GetValILOAD( "WT_GS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_WT_GS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RF0", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_RF0, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R1", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_R1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R2", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_R2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSHARS", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_PSHARS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RMOH", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_RMOH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HUDMAXDECEL", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_HUDMAXDECEL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RWTOGO", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_RWTOGO, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SBDMN", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SBDMN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SBDMX", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SBDMX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SBDLIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SBDLIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "WRAP", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_WRAP, itmp );
	return;
}

};
