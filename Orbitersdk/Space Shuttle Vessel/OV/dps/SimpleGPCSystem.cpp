/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
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
2022/05/19   GLS
2022/05/29   GLS
2022/06/03   GLS
2022/07/17   GLS
2022/07/24   GLS
2022/08/05   GLS
2022/08/10   GLS
2022/08/13   GLS
2022/08/15   GLS
2022/08/17   GLS
2022/08/18   GLS
2022/08/20   GLS
2022/09/14   GLS
2022/09/15   GLS
2022/09/17   GLS
2022/09/29   GLS
2022/10/25   GLS
2022/10/27   GLS
2022/11/05   GLS
2022/11/06   GLS
2022/11/30   GLS
2022/12/01   indy91
2022/12/02   indy91
2022/12/03   GLS
2022/12/05   GLS
2022/12/18   GLS
2022/12/21   GLS
2022/12/23   GLS
********************************************/
#include <cassert>
#include "SimpleGPCSystem.h"
#include "Software/SimpleGPCSoftware.h"
#include "SimpleShuttleBus.h"
#include "Software/GNC/SimpleFCOS_IO_GNC.h"
#include "Software/SM/SimpleFCOS_IO_SM.h"
#include "Software/GNC/AscentDAP.h"
#include "Software/GNC/OrbitDAP.h"
#include "Software/GNC/OMSBurnSoftware.h"
#include "Software/GNC/StateVectorSoftware.h"
#include "Software/GNC/OrbitTgtSoftware.h"
#include "Software/GNC/AerojetDAP.h"
#include "Software/GNC/SSME_SOP.h"
#include "Software/GNC/SSME_Operations.h"
#include "Software/GNC/RSLS.h"
#include "Software/GNC/MPS_Dedicated_Display_Driver.h"
#include "Software/GNC/MPS_Dump.h"
#include "Software/GNC/MM801.h"
#include "Software/GNC/IO_Control.h"
#include "Software/GNC/TransitionDAP.h"
#include "Software/GNC/ETSepSequence.h"
#include "Software/GNC/SRBSepSequence.h"
#include "Software/GNC/MPS_ATVC_CMD_SOP.h"
#include "Software/GNC/SRB_ATVC_CMD_SOP.h"
#include "Software/SystemDisplays.h"
#include "Software/GNC/GNCDisplays.h"
#include "Software/SM/SMDisplays.h"
#include "Software/GNC/MEC_SOP.h"
#include "Software/GNC/RHC_RM.h"
#include "Software/GNC/THC_RM.h"
#include "Software/GNC/RPTA_RM.h"
#include "Software/GNC/SBTC_RM.h"
#include "Software/GNC/RHC_SOP.h"
#include "Software/GNC/THC_SOP.h"
#include "Software/GNC/RPTA_SOP.h"
#include "Software/GNC/SBTC_SOP.h"
#include "Software/GNC/Switch_RM.h"
#include "Software/GNC/TrimStationSelect.h"
#include "Software/GNC/BF_Slew_SOP.h"
#include "Software/GNC/Landing_SOP.h"
#include "Software/GNC/OMS_TVC_Command_SOP.h"
#include "Software/GNC/OMS_TVC_Feedback_SOP.h"
#include "Software/GNC/DedicatedDisplay_SOP.h"
#include "Software/GNC/RadarAltimeter_SOP.h"
#include "Software/GNC/Entry_UPP.h"
#include "Software/GNC/TAEM_UPP.h"
#include "Software/GNC/AL_UPP.h"
#include "Software/GNC/EGRT.h"
#include "Software/GNC/EntryGuidance.h"
#include "Software/GNC/TAEMGuidance.h"
#include "Software/GNC/AutolandGuidance.h"
#include "Software/GNC/LandingSite.h"
#include "Software/GNC/RCSActivityLights.h"
#include "Software/GNC/JetSelectionLogic.h"
#include "Software/GNC/PriorityRateLimiting.h"
#include "Software/GNC/Aero_Act_SOP.h"
#include "Software/GNC/NW_POSN_SOP.h"
#include "Software/GNC/Elevon_PFB_SOP.h"
#include "Software/GNC/BodyFlap_PFB_SOP.h"
#include "Software/GNC/Rudder_PFB_SOP.h"
#include "Software/GNC/Speedbrake_PFB_SOP.h"
#include "Software/GNC/DAPLightsDriver.h"
#include "Software/GNC/VentCntlSeq.h"
#include "Software/GNC/GAX.h"
#include "Software/GNC/AnnunciationSupport.h"
#include "Software/SM/SystemsServicesAnnunciation.h"
#include "Software/SM/SSB_PL_BAY_DOORS.h"
#include "Software/SM/SSO_SP_DATA_OUT.h"
#include "../Atlantis.h"

namespace dps
{

SimpleGPCSystem::SimpleGPCSystem( AtlantisSubsystemDirector* _director, const string& _ident, bool _GNC ) : AtlantisSubsystem( _director, _ident ),
GNC(_GNC)
{
	memset( SimpleCOMPOOL, 0, sizeof(unsigned short) * SIMPLECOMPOOL_SIZE );
	WriteBufferAddress = 0;
	WriteBufferLength = 0;
	SubSystemAddress = 0;

	WriteCOMPOOL_IS( SCP_MC, GNC ? 1 : 2 );// HACK GNC = MC 1, SM = MC 2
	WriteCOMPOOL_IS( SCP_MM, 0 );
	WriteCOMPOOL_IS( SCP_NEW_MM, static_cast<unsigned short>(-1) );
	WriteCOMPOOL_IS( SCP_SM_TONE_DURATION, 1 );

	// load system sw
	vSoftware.push_back( pSystemDisplays = new SystemDisplays( this ) );

	if (GNC)
	{
		pFCOS_IO = new SimpleFCOS_IO_GNC( this );

		// load GNC sw
		vSoftware.push_back( new GAX( this ) );
		vSoftware.push_back( new AnnunciationSupport( this ) );

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
		vSoftware.push_back( pUserDisplays = new GNCDisplays( this ) );
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
	}
	else
	{
		pFCOS_IO = new SimpleFCOS_IO_SM( this );

		// load SM sw
		vSoftware.push_back( new SystemsServicesAnnunciation( this ) );

		vSoftware.push_back( new SSB_PL_BAY_DOORS( this ) );
		vSoftware.push_back( new SSO_SP_DATA_OUT( this ) );
		vSoftware.push_back( pUserDisplays = new SMDisplays( this ) );
	}

	// I-LOADs init
	WriteCOMPOOL_IS( SCP_KMIN, 67 );
	WriteCOMPOOL_IS( SCP_OVHD, 1 );
	WriteCOMPOOL_IS( SCP_IGS, 1 );
	WriteCOMPOOL_IS( SCP_IGI, 1 );
	WriteCOMPOOL_IS( SCP_RWID, 1 );
	WriteCOMPOOL_IS( SCP_LSID, 1 );
	WriteCOMPOOL_MS( SCP_AL_R, 1, 1, 25896.8f, 2, 2 );
	WriteCOMPOOL_MS( SCP_AL_R, 2, 1, 26409.5f, 2, 2 );
	WriteCOMPOOL_MS( SCP_AL_R, 1, 2, 32218.9f, 2, 2 );
	WriteCOMPOOL_MS( SCP_AL_R, 2, 2, 32860.9f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 1, 1, -3313.48f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 2, 1, -2138.13f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 1, 2, -2775.87f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 2, 2, -1577.49f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 1, 1, 26035.03f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 2, 1, 26516.81f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 1, 2, 32341.99f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 2, 2, 32952.57f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 1, 1, -4901.98f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 2, 1, -3757.87f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 1, 2, -4533.71f, 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 2, 2, -3374.8f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 1, 32.45f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 1, 32.44f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 2, 26.18f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 2, 26.3f, 2, 2 );
	WriteCOMPOOL_SS( SCP_SIGMA, 920.0 );
	WriteCOMPOOL_VS( SCP_GAMMA_REF_1, 1, -20.0, 2 );
	WriteCOMPOOL_VS( SCP_GAMMA_REF_1, 2, -18.0, 2 );
	WriteCOMPOOL_SS( SCP_GAMMA_REF_2, -1.5 );
	WriteCOMPOOL_VS( SCP_X_ZERO, 1, -7500.0, 2 );
	WriteCOMPOOL_VS( SCP_X_ZERO, 2, -6500.0, 2 );
	WriteCOMPOOL_SS( SCP_X_AIM, 1000.0 );
	WriteCOMPOOL_SS( SCP_H_FLARE, 2000.0 );
	WriteCOMPOOL_SS( SCP_H_CLOOP, 1700.0 );
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
	WriteCOMPOOL_IS( SCP_PMODE, 0 );
	WriteCOMPOOL_IS( SCP_FMODE, 1 );
	WriteCOMPOOL_IS( SCP_IPHASE, 1 );
	WriteCOMPOOL_IS( SCP_TG_END, 0 );
	WriteCOMPOOL_SS( SCP_WT_GS1, 6837.808943f );
	WriteCOMPOOL_SS( SCP_RF0, 14000.0 );
	WriteCOMPOOL_SS( SCP_R1, 0.0 );
	WriteCOMPOOL_SS( SCP_R2, 0.093f );
	WriteCOMPOOL_SS( SCP_PSHARS, 270.0 );
	WriteCOMPOOL_SS( SCP_RMOH, 273500.0 );
	WriteCOMPOOL_SS( SCP_HUDMAXDECEL, 16.0 );
	WriteCOMPOOL_SS( SCP_RWTOGO, 1000.0 );
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

unsigned short SimpleGPCSystem::SetSPECDISP( unsigned short spec, unsigned short crt )
{
	if (IsValidSPEC( spec ))
	{
		return 1;
	}
	else if (IsValidDISP( spec ))
	{
		// HACK indicate "SPEC 99 PRO"
		if (spec == 99) WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CLEAR, 1 );
		return 2;
	}
	// set illegal entry
	unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
	illegalentryfault |= (1 << (crt - 1));
	WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
	return 0;
}

bool SimpleGPCSystem::SetMajorModeKB( unsigned short newMM, unsigned short crt )
{
	if (!IsValidMajorModeTransition( newMM ))
	{
		// set illegal entry
		unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
		illegalentryfault |= (1 << (crt - 1));
		WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
		return false;
	}

	WriteCOMPOOL_IS( SCP_NEW_MM, newMM );
	return true;
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
	if (GNC) return IsValidMajorModeTransition_GNC( newMajorMode );
	else return IsValidMajorModeTransition_SM( newMajorMode );
}

bool SimpleGPCSystem::IsValidMajorModeTransition_GNC( unsigned short newMajorMode ) const
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

bool SimpleGPCSystem::IsValidMajorModeTransition_SM( unsigned short newMajorMode ) const
{
	if (ReadCOMPOOL_IS( SCP_CZ1E_OPS_MODE_INHIBIT ) != 0) return false;// don't allow changes if any inhibit event on

	unsigned short MM = ReadCOMPOOL_IS( SCP_MM );
	switch (newMajorMode)
	{
		case 0:
			return (MM == 201 || MM == 202);
		case 201:
			return (MM == 0 || MM == 202);
		case 202:
			return (MM == 0 || MM == 201);
		default:
			return false;
	}
}

bool SimpleGPCSystem::IsValidSPEC( unsigned short spec ) const
{
	if (GNC) return IsValidSPEC_GNC( spec );
	else return IsValidSPEC_SM( spec );
}

bool SimpleGPCSystem::IsValidSPEC_GNC( unsigned short spec ) const
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

bool SimpleGPCSystem::IsValidSPEC_SM( unsigned short spec ) const
{
	// PASS system
	switch (spec)
	{
		case 0:// GPC MEMORY
		case 1:// DPS UTILITY
		case 2:// TIME
			return true;
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
	return false;
}

bool SimpleGPCSystem::IsValidDISP( unsigned short disp ) const
{
	if (GNC) return IsValidDISP_GNC( disp );
	else return IsValidDISP_SM( disp );
}

bool SimpleGPCSystem::IsValidDISP_GNC( unsigned short disp ) const
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

bool SimpleGPCSystem::IsValidDISP_SM( unsigned short disp ) const
{
	// PASS system
	switch (disp)
	{
		case 6:// GPC/BUS STATUS
		case 99:// FAULT
			return true;
	}

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

		// reset commfault indications and counters on OPS change
		if (((ReadCOMPOOL_IS( SCP_NEW_MM ) / 100) != (ReadCOMPOOL_IS( SCP_MM ) / 100)) && (ReadCOMPOOL_IS( SCP_MM ) != 0)) IORESET();

		WriteCOMPOOL_IS( SCP_MM, ReadCOMPOOL_IS( SCP_NEW_MM ) );
		WriteCOMPOOL_IS( SCP_NEW_MM, static_cast<unsigned short>(-1) );
	}

	pFCOS_IO->input();// input data from subsystems

	for (unsigned int i = 0; i < vActiveSoftware.size(); i++)
		vActiveSoftware[i]->OnPreStep( simt, simdt, mjd );
	return;
}

void SimpleGPCSystem::OnPostStep(double simt, double simdt, double mjd)
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++)
		vActiveSoftware[i]->OnPostStep(simt, simdt, mjd);

	pFCOS_IO->output();// output commands to subsystems

	// reset keys
	WriteCOMPOOL_IS( SCP_ACK_KEY, 0 );
	WriteCOMPOOL_IS( SCP_MSGRESET_KEY, 0 );
	return;
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
					else if (!_strnicmp( pszKey, "SM_TONE_DURATION", 16 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 99) WriteCOMPOOL_IS( SCP_SM_TONE_DURATION, tmp );
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
						if (tmp <= 4) WriteCOMPOOL_IS( SCP_PMODE, tmp );
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
						WriteCOMPOOL_SS( SCP_DLRDOT, tmp );
					}
					else if (!_strnicmp( pszKey, "MEP", 4 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_MEP, tmp );
					}
					else if (!_strnicmp( pszKey, "YSGN", 4 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						if ((tmp == 1.0) || (tmp == -1.0)) WriteCOMPOOL_SS( SCP_YSGN, tmp );
					}
					else if (!_strnicmp( pszKey, "RF", 2 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_RF, tmp );
					}
					else if (!_strnicmp( pszKey, "PSHA", 4 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_PSHA, tmp );
					}
					else if (!_strnicmp( pszKey, "RTURN", 5 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_RTURN, tmp );
					}
					else if (!_strnicmp( pszKey, "XHAC", 4 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_XHAC, tmp );
					}
					else if (!_strnicmp( pszKey, "WRAP", 4 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 2) WriteCOMPOOL_IS( SCP_WRAP, tmp );
					}
					else if (!_strnicmp( pszKey, "VENT_DOOR_SEQ_INIT", 19 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, tmp );
					}
					else if (!_strnicmp( pszKey, "ALL_VENT_CLOSE_CMD", 18 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD, tmp );
					}
					else if (!_strnicmp( pszKey, "ME_CMD_PATH_FAIL", 16 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "ME_ELEC_LOCKUP", 14 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "ME_FLT_DATA_PATH_FAIL", 21 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "ME_HYD_LOCKUP", 13 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "ME_LIM_EX", 9 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_ME_LIM_EX, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_ME_LIM_EX, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_ME_LIM_EX, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "ME_READY", 8 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_ME_READY, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_ME_READY, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_ME_READY, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "MEPSTSHDN", 9 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_MEPSTSHDN, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_MEPSTSHDN, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_MEPSTSHDN, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "MESHDN", 3 ))
					{
						unsigned int tmp1 = 0;
						unsigned int tmp2 = 0;
						unsigned int tmp3 = 0;
						sscanf_s( line, "%u %u %u", &tmp1, &tmp2, &tmp3 );
						if (tmp1 <= 1) WriteCOMPOOL_AIS( SCP_MESHDN, 1, tmp1, 3 );
						if (tmp2 <= 1) WriteCOMPOOL_AIS( SCP_MESHDN, 2, tmp2, 3 );
						if (tmp3 <= 1) WriteCOMPOOL_AIS( SCP_MESHDN, 3, tmp3, 3 );
					}
					else if (!_strnicmp( pszKey, "ME1_FAIL_SHUTDOWN", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN, tmp );
					}
					else if (!_strnicmp( pszKey, "ME2_FAIL_SHUTDOWN", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN, tmp );
					}
					else if (!_strnicmp( pszKey, "ME3_FAIL_SHUTDOWN", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN, tmp );
					}
					else if (!_strnicmp( pszKey, "MECO_CMD", 8 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_MECO_CMD, tmp );
					}
					else if (!_strnicmp( pszKey, "MECO_CONFIRMED", 14 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_MECO_CONFIRMED, tmp );
					}
					else if (!_strnicmp( pszKey, "FAULT_DISPBUF_CNT", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT, tmp );
					}
					else if (!_strnicmp( pszKey, "FAULT_DISPBUF_", 14 ))
					{
						unsigned int tmp = 0;
						sscanf_s( pszKey + 14, "%u", &tmp );
						WriteCOMPOOL_AC( SCP_FAULT_DISPBUF, tmp, line, 15, 43 );
					}
					else if (!_strnicmp( pszKey, "FAULT_MSG_LINE_STATE", 20 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE, tmp );
					}
					else if (!_strnicmp( pszKey, "FAULT_MSG_LINE", 14 ))
					{
						WriteCOMPOOL_AC( SCP_FAULT_MSG_LINE, 1, line, 15, 43 );
					}
					else if (!_strnicmp( pszKey, "FAULT_MSG_BUF_IND", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_AUTO_MODE_ITEM", 19 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_AUTO_MODE_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_MANUAL_MODE_ITEM", 21 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_MANUAL_MODE_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_POWER_ON_OFF_ITEM", 22 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_POWER_ON_OFF_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_SWITCH_BYPASS_ITEM", 23 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_SWITCH_BYPASS_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_PBD_OPEN_ITEM", 18 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_PBD_OPEN_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_PBD_STOP_ITEM", 18 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_PBD_STOP_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_PBD_CLOSE_ITEM", 19 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_PBD_CLOSE_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_OPEN_FAIL_INDICATOR", 24 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_OPEN_FAIL_INDICATOR, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_CLOSE_FAIL_INDICATOR", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_CLOSE_FAIL_INDICATOR, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_AUTO_MODE_FLAG", 19 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_AUTO_MODE_FLAG, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_MANUAL_MODE_FLAG", 21 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_CSBB_MANUAL_MODE_FLAG, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_0", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_0, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_1", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_1, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_2", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_2, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_3", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_3, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_4", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_4, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_5", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_5, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_6", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_6, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_7", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_7, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_8", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_8, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_9", 17 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_9, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_10", 18 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_10, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_0", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_0, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_1", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_1, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_2", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_2, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_3", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_3, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_4", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_4, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_5", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_5, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_6", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_6, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_7", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_7, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_8", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_8, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_9", 25 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_9, tmp );
					}
					else if (!_strnicmp( pszKey, "COMMFAULT_WORD_COUNTER_10", 26 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_10, tmp );
					}
					else if (*line != '\0')
					{
						this->OnParseLine( pszKey, line );
					} else
					{
						this->OnParseLine( pszKey, NULL );
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
	char cbuf[256];
	oapiWriteScenario_int( scn, "MM", ReadCOMPOOL_IS( SCP_MM ) );
	oapiWriteScenario_int( scn, "SM_TONE_DURATION", ReadCOMPOOL_IS( SCP_SM_TONE_DURATION ) );

	if (GNC)
	{
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
		oapiWriteScenario_float( scn, "DLRDOT", ReadCOMPOOL_SS( SCP_DLRDOT ) );

		oapiWriteScenario_int( scn, "MEP", ReadCOMPOOL_IS( SCP_MEP ) );
		oapiWriteScenario_float( scn, "YSGN", ReadCOMPOOL_SS( SCP_YSGN ) );
		oapiWriteScenario_float( scn, "RF", ReadCOMPOOL_SS( SCP_RF ) );
		oapiWriteScenario_float( scn, "PSHA", ReadCOMPOOL_SS( SCP_PSHA ) );
		oapiWriteScenario_float( scn, "RTURN", ReadCOMPOOL_SS( SCP_RTURN ) );
		oapiWriteScenario_float( scn, "XHAC", ReadCOMPOOL_SS( SCP_XHAC ) );

		oapiWriteScenario_int( scn, "VENT_DOOR_SEQ_INIT", ReadCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT ) );
		oapiWriteScenario_int( scn, "ALL_VENT_CLOSE_CMD", ReadCOMPOOL_IS( SCP_ALL_VENT_CLOSE_CMD ) );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 1, 3 ), ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 2, 3 ), ReadCOMPOOL_AIS( SCP_ME_CMD_PATH_FAIL, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_CMD_PATH_FAIL", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 1, 3 ), ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 2, 3 ), ReadCOMPOOL_AIS( SCP_ME_ELEC_LOCKUP, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_ELEC_LOCKUP", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 1, 3 ), ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 2, 3 ), ReadCOMPOOL_AIS( SCP_ME_FLT_DATA_PATH_FAIL, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_FLT_DATA_PATH_FAIL", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 1, 3 ), ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 2, 3 ), ReadCOMPOOL_AIS( SCP_ME_HYD_LOCKUP, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_HYD_LOCKUP", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_ME_LIM_EX, 1, 3 ), ReadCOMPOOL_AIS( SCP_ME_LIM_EX, 2, 3 ), ReadCOMPOOL_AIS( SCP_ME_LIM_EX, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_LIM_EX", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_ME_READY, 1, 3 ), ReadCOMPOOL_AIS( SCP_ME_READY, 2, 3 ), ReadCOMPOOL_AIS( SCP_ME_READY, 3, 3 ) );
		oapiWriteScenario_string( scn, "ME_READY", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 1, 3 ), ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 2, 3 ), ReadCOMPOOL_AIS( SCP_MEPSTSHDN, 3, 3 ) );
		oapiWriteScenario_string( scn, "MEPSTSHDN", cbuf );

		sprintf_s( cbuf, 256, "%hu %hu %hu", ReadCOMPOOL_AIS( SCP_MESHDN, 1, 3 ), ReadCOMPOOL_AIS( SCP_MESHDN, 2, 3 ), ReadCOMPOOL_AIS( SCP_MESHDN, 3, 3 ) );
		oapiWriteScenario_string( scn, "MESHDN", cbuf );

		oapiWriteScenario_int( scn, "ME1_FAIL_SHUTDOWN", ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) );
		oapiWriteScenario_int( scn, "ME2_FAIL_SHUTDOWN", ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) );
		oapiWriteScenario_int( scn, "ME3_FAIL_SHUTDOWN", ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) );

		oapiWriteScenario_int( scn, "MECO_CMD", ReadCOMPOOL_IS( SCP_MECO_CMD ) );
		oapiWriteScenario_int( scn, "MECO_CONFIRMED", ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) );

		{
			char cbuf2[32];
			unsigned short j = ReadCOMPOOL_IS( SCP_FAULT_DISPBUF_CNT );
			oapiWriteScenario_int( scn, "FAULT_DISPBUF_CNT", j );
			for (unsigned int i = 1; i <= j; i++)
			{
				memset( cbuf, 0, 256 );
				ReadCOMPOOL_AC( SCP_FAULT_DISPBUF, i, cbuf, 15, 43 );
				sprintf_s( cbuf2, "FAULT_DISPBUF_%d", i );
				oapiWriteScenario_string( scn, cbuf2, cbuf );
			}

			j = ReadCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE );
			oapiWriteScenario_int( scn, "FAULT_MSG_LINE_STATE", j );
			if (j != 0)
			{
				ReadCOMPOOL_AC( SCP_FAULT_MSG_LINE, 1, cbuf, 15, 43 );
				oapiWriteScenario_string( scn, "FAULT_MSG_LINE", cbuf );
			}
			oapiWriteScenario_int( scn, "FAULT_MSG_BUF_IND", ReadCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND ) );
		}
	}
	else
	{
		oapiWriteScenario_int( scn, "CSBB_AUTO_MODE_ITEM", ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_MANUAL_MODE_ITEM", ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_POWER_ON_OFF_ITEM", ReadCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_SWITCH_BYPASS_ITEM", ReadCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_PBD_OPEN_ITEM", ReadCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_PBD_STOP_ITEM", ReadCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_PBD_CLOSE_ITEM", ReadCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM ) );
		oapiWriteScenario_int( scn, "CSBB_OPEN_FAIL_INDICATOR", ReadCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR ) );
		oapiWriteScenario_int( scn, "CSBB_CLOSE_FAIL_INDICATOR", ReadCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR ) );
		oapiWriteScenario_int( scn, "CSBB_AUTO_MODE_FLAG", ReadCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG ) );
		oapiWriteScenario_int( scn, "CSBB_MANUAL_MODE_FLAG", ReadCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG ) );
	}

	oapiWriteScenario_int( scn, "COMMFAULT_WORD_0", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_0 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_1", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_1 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_2", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_2 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_3", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_3 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_4", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_4 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_5", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_5 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_6", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_6 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_7", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_7 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_8", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_8 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_9", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_9 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_10", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_10 ) );

	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_0", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_0 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_1", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_1 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_2", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_2 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_3", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_3 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_4", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_4 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_5", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_5 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_6", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_6 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_7", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_7 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_8", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_8 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_9", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_9 ) );
	oapiWriteScenario_int( scn, "COMMFAULT_WORD_COUNTER_10", ReadCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_10 ) );


	for(unsigned int i=0;i<vActiveSoftware.size();i++) {
		oapiWriteScenario_string(scn, "@BEGINSOFTWARE", const_cast<char*>(vActiveSoftware[i]->GetIdentifier().c_str()));
		vActiveSoftware[i]->OnSaveState(scn);
		oapiWriteLine( scn, "  @ENDSOFTWARE" );
	}
}

void SimpleGPCSystem::ItemInput( int spec, int item, const char* Data, unsigned short crt )
{
	bool illegalentry = false;

	// check spec isn't a disp
	if (IsValidDISP( spec ))
	{
		illegalentry = true;
	}
	else
	{
		if (!pSystemDisplays->ItemInput( spec, item, Data )) illegalentry = !pUserDisplays->ItemInput( spec, item, Data );
	}
	// set illegal entry
	if (illegalentry)
	{
		unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
		illegalentryfault |= (1 << (crt - 1));
		WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
	}
	return;
}

void SimpleGPCSystem::IORESET( void )
{
	// reset all commfault words
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_0, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_1, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_2, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_3, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_4, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_5, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_6, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_7, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_8, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_9, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_10, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_0, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_1, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_2, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_3, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_4, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_5, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_6, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_7, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_8, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_9, 0 );
	WriteCOMPOOL_ID( SCP_COMMFAULT_WORD_COUNTER_10, 0 );
	return;
}

bool SimpleGPCSystem::ExecPressed(int spec)
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++) {
		if(vActiveSoftware[i]->ExecPressed(spec))
			return true;
	}
	return false;
}

void SimpleGPCSystem::AckPressed( void )
{
	WriteCOMPOOL_IS( SCP_ACK_KEY, 1 );
	return;
}

void SimpleGPCSystem::MsgResetPressed( unsigned short crt )
{
	WriteCOMPOOL_IS( SCP_MSGRESET_KEY, 1 );
	// reset illegal entry
	unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
	illegalentryfault &= ~(1 << (crt - 1));
	WriteCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT, illegalentryfault );
	return;
}

void SimpleGPCSystem::GetFaultMsg( char* msg, bool& flash, unsigned short crt ) const
{
	// if no fault msg, check for illegal entry in this CRT, if none show fault msg
	unsigned int illegalentryfault = ReadCOMPOOL_IS( SCP_ILLEGAL_ENTRY_FAULT );
	if (illegalentryfault & (1 << (crt - 1)))
	{
		strcpy_s( msg, 64, "ILLEGAL ENTRY" );
		flash = true;
	}
	else
	{
		unsigned int state = ReadCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE );
		if (state != 0)
		{
			// assemble msg
			char tmp[64];
			memset( tmp, 0, 64 );
			ReadCOMPOOL_C( SCP_FAULT_MSG_LINE, tmp, 43 );
			memset( tmp + 31, 20, 4 );// HACK remove days from time field
			unsigned short ind = ReadCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND );
			if (ind != 0) sprintf_s( msg, 64, "%s (%02hu)", tmp, ind );
			else sprintf_s( msg, 64, "%s", tmp );

			flash = (state == 1);
		}
	}
	return;
}

bool SimpleGPCSystem::OnPaint( int spec, vc::MDU* pMDU ) const
{
	if (pSystemDisplays->OnPaint( spec, pMDU )) return true;
	return pUserDisplays->OnPaint( spec, pMDU );
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

float SimpleGPCSystem::ReadCOMPOOL_SS( unsigned int addr ) const
{
	float tmp = 0.0f;
	if (addr < (SIMPLECOMPOOL_SIZE - 1))
		memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
	return tmp;
}

double SimpleGPCSystem::ReadCOMPOOL_SD(unsigned int addr) const
{
	double tmp = 0.0;
	if (addr < (SIMPLECOMPOOL_SIZE - 3))
		memcpy(&tmp, SimpleCOMPOOL + addr, 8);
	return tmp;
}

MATRIX3 SimpleGPCSystem::ReadCOMPOOL_MS( unsigned int addr ) const
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

MATRIX3 SimpleGPCSystem::ReadCOMPOOL_MD(unsigned int addr) const
{
	MATRIX3 m3 = _M(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	if (addr < (SIMPLECOMPOOL_SIZE - 35))
	{
		memcpy(&m3.m11, SimpleCOMPOOL + addr, 8);
		memcpy(&m3.m12, SimpleCOMPOOL + addr + 4, 8);
		memcpy(&m3.m13, SimpleCOMPOOL + addr + 8, 8);

		memcpy(&m3.m21, SimpleCOMPOOL + addr + 12, 8);
		memcpy(&m3.m22, SimpleCOMPOOL + addr + 16, 8);
		memcpy(&m3.m23, SimpleCOMPOOL + addr + 20, 8);

		memcpy(&m3.m31, SimpleCOMPOOL + addr + 24, 8);
		memcpy(&m3.m32, SimpleCOMPOOL + addr + 28, 8);
		memcpy(&m3.m33, SimpleCOMPOOL + addr + 32, 8);
	}
	return m3;
}

float SimpleGPCSystem::ReadCOMPOOL_MS( unsigned int addr, unsigned int m, unsigned int n, unsigned int msize, unsigned int nsize ) const
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

VECTOR3 SimpleGPCSystem::ReadCOMPOOL_VS( unsigned int addr ) const
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

VECTOR3 SimpleGPCSystem::ReadCOMPOOL_VD(unsigned int addr) const
{
	VECTOR3 v3 = _V(0.0, 0.0, 0.0);

	if (addr < (SIMPLECOMPOOL_SIZE - 11))
	{
		memcpy(&v3.x, SimpleCOMPOOL + addr, 8);
		memcpy(&v3.y, SimpleCOMPOOL + addr + 4, 8);
		memcpy(&v3.z, SimpleCOMPOOL + addr + 8, 8);
	}
	return v3;
}

float SimpleGPCSystem::ReadCOMPOOL_VS( unsigned int addr, unsigned int n, unsigned int nsize ) const
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
	if (addr <= (SIMPLECOMPOOL_SIZE - size))
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
		if (addr <= (SIMPLECOMPOOL_SIZE - size - 1))
		{
			return SimpleCOMPOOL[addr + idx - 1];
		}
	}
	return 0;
}

void SimpleGPCSystem::ReadCOMPOOL_AC( unsigned int addr, unsigned int idx, char* val, unsigned int size_a, unsigned int size_c ) const
{
	if ((idx > 0) && (idx <= size_a))
	{
		if (addr <= (SIMPLECOMPOOL_SIZE - (idx * size_c) - 1))
		{
			for (unsigned int i = 0; i < size_c; i++)
			{
				val[i] = static_cast<char>(SimpleCOMPOOL[((idx - 1) * size_c) + addr + i]);
				if (SimpleCOMPOOL[((idx - 1) * size_c) + addr + i] == 0) break;
			}
		}
	}
	return;
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

void SimpleGPCSystem::WriteCOMPOOL_SS( unsigned int addr, float val )
{
	if (addr < (SIMPLECOMPOOL_SIZE - 1))
		memcpy( SimpleCOMPOOL + addr, &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_SD(unsigned int addr, double val)
{
	if (addr < (SIMPLECOMPOOL_SIZE - 3))
		memcpy(SimpleCOMPOOL + addr, &val, 8);
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_MS( unsigned int addr, MATRIX3& val )
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

void SimpleGPCSystem::WriteCOMPOOL_MD(unsigned int addr, MATRIX3& val)
{
	if (addr < (SIMPLECOMPOOL_SIZE - 35))
	{
		memcpy(SimpleCOMPOOL + addr, &val.m11, 8);
		memcpy(SimpleCOMPOOL + addr + 4, &val.m12, 8);
		memcpy(SimpleCOMPOOL + addr + 8, &val.m13, 8);

		memcpy(SimpleCOMPOOL + addr + 12, &val.m21, 8);
		memcpy(SimpleCOMPOOL + addr + 16, &val.m22, 8);
		memcpy(SimpleCOMPOOL + addr + 20, &val.m23, 8);

		memcpy(SimpleCOMPOOL + addr + 24, &val.m31, 8);
		memcpy(SimpleCOMPOOL + addr + 28, &val.m32, 8);
		memcpy(SimpleCOMPOOL + addr + 32, &val.m33, 8);
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_MS( unsigned int addr, unsigned int m, unsigned int n, float val, unsigned int msize, unsigned int nsize )
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

void SimpleGPCSystem::WriteCOMPOOL_VS( unsigned int addr, VECTOR3& val )
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

void SimpleGPCSystem::WriteCOMPOOL_VD(unsigned int addr, VECTOR3& val)
{
	if (addr < (SIMPLECOMPOOL_SIZE - 11))
	{
		memcpy(SimpleCOMPOOL + addr, &val.x, 8);
		memcpy(SimpleCOMPOOL + addr + 4, &val.y, 8);
		memcpy(SimpleCOMPOOL + addr + 8, &val.z, 8);
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_VS( unsigned int addr, unsigned int n, float val, unsigned int nsize )
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
	if (addr <= (SIMPLECOMPOOL_SIZE - size))
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
		if (addr <= (SIMPLECOMPOOL_SIZE - size - 1))
		{
			memcpy( SimpleCOMPOOL + addr + idx - 1, &val, 2 );
		}
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_AC( unsigned int addr, unsigned int idx, const char* val, unsigned int size_a, unsigned int size_c )
{
	if ((idx > 0) && (idx <= size_a))
	{
		if (addr <= (SIMPLECOMPOOL_SIZE - (idx * size_c) - 1))
		{
			for (unsigned int i = 0; i < size_c; i++)
			{
				SimpleCOMPOOL[((idx - 1) * size_c) + addr + i] = val[i];
				if (val[i] == 0) break;
			}
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
	WriteCOMPOOL_MS( SCP_AL_R, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_AL_R, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_AL_R, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_AL_R, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_X_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "H_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_H_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_EXP", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_X_EXP, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "H_DECAY", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "SIGMA", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_SIGMA, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_1", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_GAMMA_REF_1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_GAMMA_REF_1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GAMMA_REF_2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_ZERO", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_X_ZERO, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_X_ZERO, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "X_AIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_AIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_FLARE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_FLARE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_CLOOP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_CLOOP, static_cast<float>(dtmp1) );

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
	WriteCOMPOOL_SS( SCP_WT_GS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RF0", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RF0, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_R1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_R2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSHARS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PSHARS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RMOH", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RMOH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HUDMAXDECEL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HUDMAXDECEL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RWTOGO", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RWTOGO, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "WRAP", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_WRAP, itmp );
	return;
}

unsigned short SimpleGPCSystem::GetPhysicalID( void ) const
{
	return (GNC ? 1 : 2);
}

}
