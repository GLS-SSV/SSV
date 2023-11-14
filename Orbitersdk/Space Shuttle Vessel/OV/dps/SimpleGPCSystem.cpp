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
2022/12/15   indy91
2022/12/18   indy91
2022/12/18   GLS
2022/12/21   GLS
2022/12/23   GLS
2023/01/01   GLS
2023/01/07   GLS
2023/04/28   GLS
2023/05/07   GLS
2023/05/14   GLS
2023/05/27   GLS
2023/06/14   GLS
2023/10/29   GLS
2023/11/04   GLS
********************************************/
#include <cassert>
#include "SimpleGPCSystem.h"
#include "Software/SimpleGPCSoftware.h"
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
#include "Software/GNC/OMS_RM.h"
#include "Software/GNC/ADTA_SOP.h"
#include "Software/GNC/RA_SOP.h"
#include "Software/GNC/Entry_UPP.h"
#include "Software/GNC/TAEM_UPP.h"
#include "Software/GNC/AL_UPP.h"
#include "Software/GNC/EntryGuidance.h"
#include "Software/GNC/TAEMGuidance.h"
#include "Software/GNC/AutolandGuidance.h"
#include "Software/GNC/ENT_AREA_NAV.h"
#include "Software/GNC/ENT_SITE_LOOKUP.h"
#include "Software/GNC/RCS_ACT_LT.h"
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
#include "Software/GNC/ATT_PROC.h"
#include "Software/GNC/AMI_PROC.h"
#include "Software/GNC/ASC_ADI_PROC.h"
#include "Software/GNC/ORB_ADI_PROC.h"
#include "Software/GNC/EL_ADI_PROC.h"
#include "Software/GNC/AVVI_PROC.h"
#include "Software/GNC/HSI_PROC.h"
#include "Software/GNC/HUD_PROC.h"
#include "Software/GNC/LAMP_PROC.h"
#include "Software/GNC/SPI_PROC.h"
#include "Software/GNC/MEDSFCGNCXFER.h"
#include "Software/GNC/HYD_SYS_SOP.h"
#include "Software/GNC/HORIZ_SIT_SPEC.h"
#include "Software/FCOS.h"
#include "Software/KeyboardInterface.h"
#include "Software/UserInterfaceControl.h"
#include "Software/GNC/GNCUtilities.h"
#include "Software/SM/SystemsServicesAnnunciation.h"
#include "Software/SM/SSB_PL_BAY_DOORS.h"
#include "Software/SM/SSO_SP_DATA_OUT.h"
#include "../Atlantis.h"
#include "../vc/MDU.h"


namespace dps
{
SimpleGPCSystem::SimpleGPCSystem( AtlantisSubsystemDirector* _director, const string& _ident, bool _GNC, BusManager* pBusManager ) : AtlantisSubsystem( _director, _ident ), BusTerminal( pBusManager ),
rcvr(false),GNC(_GNC)
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
	pKeyboardInterface = new KeyboardInterface( this );
	pUserInterfaceControl = new UserInterfaceControl( this );

	if (GNC)
	{
		pFCOS_IO = new SimpleFCOS_IO_GNC( this );

		// load GNC sw
		vSoftware.push_back( new GAX( this ) );
		vSoftware.push_back( new AnnunciationSupport( this ) );

		vSoftware.push_back( new FCOS(this));
		vSoftware.push_back( new GNCUtilities(this));
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
		vSoftware.push_back( new ADTA_SOP( this ) );
		vSoftware.push_back( new RA_SOP( this ) );
		vSoftware.push_back( new ENT_AREA_NAV( this ) );
		vSoftware.push_back( new ENT_SITE_LOOKUP( this ) );
		vSoftware.push_back( new ATT_PROC( this ) );
		vSoftware.push_back( new Entry_UPP( this ) );
		vSoftware.push_back( new TAEM_UPP( this ) );
		vSoftware.push_back( new AL_UPP( this ) );
		vSoftware.push_back( new EntryGuidance( this ) );
		vSoftware.push_back( new TAEMGuidance( this ) );
		vSoftware.push_back( new AutolandGuidance( this ) );
		vSoftware.push_back( new HYD_SYS_SOP( this ) );
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
		vSoftware.push_back( new OMSTVCFDBK_SOP( this ) );
		vSoftware.push_back( new OMS_RM( this ) );
		vSoftware.push_back( new OMSTVCCMD_SOP( this ) );
		vSoftware.push_back( new JetSelectionLogic( this ) );
		vSoftware.push_back( new PriorityRateLimiting( this ) );
		vSoftware.push_back( new Aero_Act_SOP( this ) );
		vSoftware.push_back( new DAPLightsDriver( this ) );
		vSoftware.push_back( new VentCntlSeq( this ) );
		vSoftware.push_back( new AMI_PROC( this ) );
		vSoftware.push_back( new ASC_ADI_PROC( this ) );
		vSoftware.push_back( new ORB_ADI_PROC( this ) );
		vSoftware.push_back( new EL_ADI_PROC( this ) );
		vSoftware.push_back( new AVVI_PROC( this ) );
		vSoftware.push_back( new HSI_PROC( this ) );
		vSoftware.push_back( new HUD_PROC( this ) );
		vSoftware.push_back( new LAMP_PROC( this ) );
		vSoftware.push_back( new RCS_ACT_LT( this ) );
		vSoftware.push_back( new SPI_PROC( this ) );
		vSoftware.push_back( new MEDSFCGNCXFER( this ) );
		vSoftware.push_back( new HORIZ_SIT_SPEC( this ) );
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
	WriteCOMPOOL_IS( SCP_GI_CHANGE, 0 );
	WriteCOMPOOL_IS( SCP_ENT_PT_SW, 0 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 1, 32.45f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 1, 32.44f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 2, 26.18f, 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 2, 26.3f, 2, 2 );
	//WriteCOMPOOL_IS( SCP_SB_SEL, 1 );
	/*WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 1 );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, 1 );*/
	WriteCOMPOOL_IS( SCP_P_MODE, 0 );
	WriteCOMPOOL_IS( SCP_IPHASE, 1 );
	WriteCOMPOOL_IS( SCP_TG_END, 0 );
	WriteCOMPOOL_SS( SCP_HUDMAXDECEL, 16.0 );
	WriteCOMPOOL_SS( SCP_RWTOGO, 1000.0 );
	WriteCOMPOOL_IS( SCP_WRAP, 1 );

	// init displays
	for (int i = 1; i <= 4; i++)
	{
		WriteCOMPOOL_AIS( SCP_CRT_SPEC, i, dps::MODE_UNDEFINED, 4 );
		WriteCOMPOOL_AIS( SCP_CRT_DISP, i, dps::MODE_UNDEFINED, 4 );
	}

	// connect to busses
	BusConnect( BUS_FC1 );
	BusConnect( BUS_FC2 );
	BusConnect( BUS_FC3 );
	BusConnect( BUS_FC4 );
	BusConnect( BUS_FC5 );
	BusConnect( BUS_FC6 );
	BusConnect( BUS_FC7 );
	BusConnect( BUS_FC8 );
	BusConnect( BUS_DK1 );
	BusConnect( BUS_DK2 );
	BusConnect( BUS_DK3 );
	BusConnect( BUS_DK4 );
	BusConnect( BUS_PL1 );
	BusConnect( BUS_PL2 );
	return;
}

SimpleGPCSystem::~SimpleGPCSystem()
{
	for(unsigned int i=0;i<vSoftware.size();i++)
		delete vSoftware[i];
}

void SimpleGPCSystem::_Tx( const BUS_ID id, void* data, const unsigned short datalen )
{
	rcvr = true;
	Tx( id, data, datalen );
	rcvr = false;
	return;
}

void SimpleGPCSystem::Rx( const BUS_ID id, void* data, const unsigned short datalen )
{
	if (!rcvr) return;

	switch (id)
	{
		case BUS_DK1:
		case BUS_DK2:
		case BUS_DK3:
		case BUS_DK4:
			Rx_DK( id, data, datalen );
			break;
		case BUS_FC1:
		case BUS_FC2:
		case BUS_FC3:
		case BUS_FC4:
		case BUS_FC5:
		case BUS_FC6:
		case BUS_FC7:
		case BUS_FC8:
		case BUS_PL1:
		case BUS_PL2:
			Rx_FC( id, data, datalen );
			break;
		default:
			break;
	}
	return;
}

void SimpleGPCSystem::Rx_FC( const BUS_ID id, void* data, const unsigned short datalen )
{
	unsigned int* rcvd = static_cast<unsigned int*>(data);

	if (datalen != WriteBufferLength) return;

	// save data from subsystem
	for (unsigned short i = 0; i < WriteBufferLength; i++)
	{
		// check parity
		if (CalcParity( rcvd[i] ) == 0) return;

		// TODO check SEV

		// check addr
		unsigned char MIAaddr = (rcvd[i] >> 20) & 0b11111;
		if (MIAaddr != SubSystemAddress) return;// check if addr matches subsystem we're waiting data from

		// if MDM return word, save different location
		if (WriteBufferAddress == SCP_MDM_RETURN) SimpleCOMPOOL[WriteBufferAddress + i] = (rcvd[i] >> 1) & 0x3FFF;
		else SimpleCOMPOOL[WriteBufferAddress + i] = (rcvd[i] >> 4) & 0xFFFF;
	}
	return;
}

void SimpleGPCSystem::Rx_DK( const BUS_ID id, void* data, const unsigned short datalen )
{
	unsigned int* rcvd = static_cast<unsigned int*>(data);

	unsigned short idx;
	if (id == BUS_DK1) idx = 0;
	else if (id == BUS_DK2) idx = 1;
	else if (id == BUS_DK3) idx = 2;
	else /*if (id == BUS_DK4)*/ idx = 3;

	//// parse data word 1
	// check parity
	if (CalcParity( rcvd[0] ) == 0) return;

	// TODO check SEV

	unsigned short msgtype = (rcvd[0] >> 17) & 0b1111;
	if (msgtype == 0b0000)// poll response
	{
		// confirm received data len
		if (datalen != 16) return;

		// save data words
		for (unsigned short i = 0; i < 16; i++)
		{
			// check parity
			if (CalcParity( rcvd[i] ) == 0) return;

			// TODO check SEV

			WriteCOMPOOL_AIS( SCP_DEU_POLL_MSG, i + 1 + (idx * 16), (rcvd[i] >> 4) & 0xFFFF, 64 );
		}
	}
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

	pKeyboardInterface->DMI_MCDS_IN();
	pUserInterfaceControl->DMC_SUPER();

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
	WriteCOMPOOL_IS( SCP_EXEC_KEY, 0 );
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
					else if (!_strnicmp( pszKey, "CRT_SPEC", 8 ))
					{
						unsigned short tmp1 = 0;
						unsigned short tmp2 = 0;
						unsigned short tmp3 = 0;
						unsigned short tmp4 = 0;
						sscanf_s( line, "%hu %hu %hu %hu", &tmp1, &tmp2, &tmp3, &tmp4 );
						WriteCOMPOOL_AIS( SCP_CRT_SPEC, 1, tmp1, 4 );
						WriteCOMPOOL_AIS( SCP_CRT_SPEC, 2, tmp2, 4 );
						WriteCOMPOOL_AIS( SCP_CRT_SPEC, 3, tmp3, 4 );
						WriteCOMPOOL_AIS( SCP_CRT_SPEC, 4, tmp4, 4 );
					}
					else if (!_strnicmp( pszKey, "CRT_DISP", 8 ))
					{
						unsigned short tmp1 = 0;
						unsigned short tmp2 = 0;
						unsigned short tmp3 = 0;
						unsigned short tmp4 = 0;
						sscanf_s( line, "%hu %hu %hu %hu", &tmp1, &tmp2, &tmp3, &tmp4 );
						WriteCOMPOOL_AIS( SCP_CRT_DISP, 1, tmp1, 4 );
						WriteCOMPOOL_AIS( SCP_CRT_DISP, 2, tmp2, 4 );
						WriteCOMPOOL_AIS( SCP_CRT_DISP, 3, tmp3, 4 );
						WriteCOMPOOL_AIS( SCP_CRT_DISP, 4, tmp4, 4 );
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
					/*else if (!_strnicmp( pszKey, "SB_SEL", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if ((tmp >= 1) && (tmp <= 3)) WriteCOMPOOL_IS( SCP_SB_SEL, tmp );
					}/*
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
					}*/
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
					else if (!_strnicmp( pszKey, "P_MODE", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 4) WriteCOMPOOL_IS( SCP_P_MODE, tmp );
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
					else if (!_strnicmp( pszKey, "NEP_FB", 6 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_NEP_FB, tmp );
					}
					else if (!_strnicmp( pszKey, "YSGNP", 5 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						if ((tmp == 1.0) || (tmp == -1.0)) WriteCOMPOOL_SS( SCP_YSGNP, tmp );
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
					else if (!_strnicmp( pszKey, "OMSL_ACT_SEL", 12 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_IS( SCP_OMSL_ACT_SEL, tmp );
					}
					else if (!_strnicmp( pszKey, "OMSR_ACT_SEL", 12 ))
					{
						unsigned int tmp = 0;
						sscanf_s( line, "%u", &tmp );
						WriteCOMPOOL_IS( SCP_OMSR_ACT_SEL, tmp );
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

	sprintf_s( cbuf, 256, "%hu %hu %hu %hu", ReadCOMPOOL_AIS( SCP_CRT_SPEC, 1, 4 ), ReadCOMPOOL_AIS( SCP_CRT_SPEC, 2, 4 ), ReadCOMPOOL_AIS( SCP_CRT_SPEC, 3, 4 ), ReadCOMPOOL_AIS( SCP_CRT_SPEC, 4, 4 ) );
	oapiWriteScenario_string( scn, "CRT_SPEC", cbuf );
	sprintf_s( cbuf, 256, "%hu %hu %hu %hu", ReadCOMPOOL_AIS( SCP_CRT_DISP, 1, 4 ), ReadCOMPOOL_AIS( SCP_CRT_DISP, 2, 4 ), ReadCOMPOOL_AIS( SCP_CRT_DISP, 3, 4 ), ReadCOMPOOL_AIS( SCP_CRT_DISP, 4, 4 ) );
	oapiWriteScenario_string( scn, "CRT_DISP", cbuf );

	if (GNC)
	{
		oapiWriteScenario_int( scn, "OVHD", ReadCOMPOOL_IS( SCP_OVHD ) );
		oapiWriteScenario_int( scn, "IGS", ReadCOMPOOL_IS( SCP_IGS ) );
		oapiWriteScenario_int( scn, "IGI", ReadCOMPOOL_IS( SCP_IGI ) );
		oapiWriteScenario_int( scn, "RWID", ReadCOMPOOL_IS( SCP_RWID ) );
		oapiWriteScenario_int( scn, "RWID0", ReadCOMPOOL_IS( SCP_RWID0 ) );

		//oapiWriteScenario_int( scn, "SB_SEL", ReadCOMPOOL_IS( SCP_SB_SEL ) );

		/*oapiWriteScenario_int( scn, "AEROJET_FCS_PITCH", ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH ) );
		oapiWriteScenario_int( scn, "AEROJET_FCS_ROLL", ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL ) );
		oapiWriteScenario_int( scn, "AEROJET_FCS_SB", ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) );
		oapiWriteScenario_int( scn, "AEROJET_FCS_BF", ReadCOMPOOL_IS( SCP_AEROJET_FCS_BF ) );*/
		oapiWriteScenario_int( scn, "RETRACT_BF", ReadCOMPOOL_IS( SCP_RETRACT_BF ) );

		oapiWriteScenario_int( scn, "WOWLON", ReadCOMPOOL_IS( SCP_WOWLON ) );
		oapiWriteScenario_int( scn, "FLATTURN", ReadCOMPOOL_IS( SCP_FLATTURN ) );
		oapiWriteScenario_int( scn, "ROLLOUT", ReadCOMPOOL_IS( SCP_ROLLOUT ) );
		oapiWriteScenario_int( scn, "GSENBL", ReadCOMPOOL_IS( SCP_GSENBL ) );
		oapiWriteScenario_int( scn, "HUD_WOWLON", ReadCOMPOOL_IS( SCP_HUD_WOWLON ) );
		oapiWriteScenario_int( scn, "HUD_ROLLOUT", ReadCOMPOOL_IS( SCP_HUD_ROLLOUT ) );

		oapiWriteScenario_int( scn, "P_MODE", ReadCOMPOOL_IS( SCP_P_MODE ) );

		oapiWriteScenario_int( scn, "IPHASE", ReadCOMPOOL_IS( SCP_IPHASE ) );
		oapiWriteScenario_int( scn, "TG_END", ReadCOMPOOL_IS( SCP_TG_END ) );

		oapiWriteScenario_int( scn, "ISLECT", ReadCOMPOOL_IS( SCP_ISLECT ) );
		oapiWriteScenario_float( scn, "DLRDOT", ReadCOMPOOL_SS( SCP_DLRDOT ) );

		oapiWriteScenario_int( scn, "NEP_FB", ReadCOMPOOL_IS( SCP_NEP_FB ) );
		oapiWriteScenario_float( scn, "YSGNP", ReadCOMPOOL_SS( SCP_YSGNP ) );
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

		oapiWriteScenario_int( scn, "OMSL_ACT_SEL", ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL ) );
		oapiWriteScenario_int( scn, "OMSR_ACT_SEL", ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL ) );
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

bool SimpleGPCSystem::OnPaint( int crt, vc::MDU* pMDU ) const
{
	int spec = ReadCOMPOOL_AIS( SCP_CRT_SPEC, crt, 4 );
	int disp = ReadCOMPOOL_AIS( SCP_CRT_DISP, crt, 4 );

	// HACK print header
	{
		char cbuf[52];
		char cspecbuf[4];
		char cdispbuf[4];
		char cUplink[3];
		unsigned short usDay, usHour, usMinute, usSecond;
		strcpy_s(cUplink, "  ");
		strcpy_s(cspecbuf, "   ");
		strcpy_s(cdispbuf, "   ");

		if(spec != dps::MODE_UNDEFINED)
		{
			sprintf_s(cspecbuf, 4, "%03d", spec);
		}
		if(disp != dps::MODE_UNDEFINED)
		{
			sprintf_s(cdispbuf, 4, "%03d", disp);
		}

		STS()->GetGPCMET(1, usDay, usHour, usMinute, usSecond);

		sprintf_s(cbuf, 52, "%03d1/%03s/%3s",
			GetMajorMode(),
			cspecbuf,
			cdispbuf);
		pMDU->mvprint( 1, 0, cbuf );

		sprintf_s(cbuf, 52, "%2s %1d %03d/%02d:%02d:%02d",
			cUplink,
			GetPhysicalID(),
			usDay, usHour, usMinute, usSecond);
		pMDU->mvprint( 33, 0, cbuf );
	}

	if (disp != dps::MODE_UNDEFINED) spec = disp;

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
	double dtmp[16];
	char ctmp[16];

	SimpleGPCSoftware::GetValILOAD( "KMIN", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_KMIN, itmp );

	SimpleGPCSoftware::GetValILOAD( "H_DECAY", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_DECAY, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	/*SimpleGPCSoftware::GetValILOAD( "SB_SEL", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_SB_SEL, itmp );*/

	/*SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_PITCH", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_ROLL", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_SB", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, itmp );

	SimpleGPCSoftware::GetValILOAD( "AEROJET_FCS_BF", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, itmp );*/

	SimpleGPCSoftware::GetValILOAD( "HUDMAXDECEL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HUDMAXDECEL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RWTOGO", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RWTOGO, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "WRAP", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_WRAP, itmp );


	/////////////////////////////////////////////////////////////


	SimpleGPCSoftware::GetValILOAD( "H_K2", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_H_K2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "GR_DPY_ALT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GR_DPY_ALT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RF0", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RF0, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_R1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_R2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_MIN_3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_MIN_3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DR4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DR4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HMEP", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_HMEP, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_HMEP, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "DHOH1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DHOH1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DHOH2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DHOH2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DHOH3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DHOH3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EQLOWU", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EQLOWU, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ESHFMX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ESHFMX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PEWRR", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PEWRR, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PQBWRR", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PQBWRR, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSHARS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PSHARS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSRF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PSRF, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSOHAL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PSOHAL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSOHQB", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PSOHQB, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PSSTRN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PSSTRN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBREF2", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_QBREF2, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_QBREF2, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBMSL1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMSL1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBMSL2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMSL2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBWT1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBWT1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBWT2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBWT2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBWT3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBWT3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QMACH1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QMACH1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QMACH2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QMACH2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RFMN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RFMN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RFMX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RFMX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DRFK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DRFK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSBLLS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSBLLS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSBULS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSBULS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EMOHC1", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_EMOHC1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_EMOHC1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "EMOHC2", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_EMOHC2, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_EMOHC2, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "ENBIAS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ENBIAS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EQLOWL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EQLOWL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RMOH", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RMOH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "R2MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_R2MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILM4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILM4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBMXS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMXS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_HAC_LOW_MASS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_HAC_LOW_MASS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_HAC_HIGH_MASS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_HAC_HIGH_MASS, static_cast<float>(dtmp1) );



	SimpleGPCSoftware::GetValILOAD( "CDEQD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDEQD, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CPMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CPMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CQDG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CQDG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CQG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CQG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CUBIC_C3", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_CUBIC_C3, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_CUBIC_C3, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "CUBIC_C4", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_CUBIC_C4, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_CUBIC_C4, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "DEL_H1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DEL_H1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DEL_H2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DEL_H2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DEL_R_EMAX", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_DEL_R_EMAX, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_DEL_R_EMAX, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "DNZCDL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNZCDL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DNZCG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNZCG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DNZLC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNZLC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DNZLC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNZLC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DNZUC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNZUC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DNZUC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNZUC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSBCM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSBCM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSBLIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSBLIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSBNOM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSBNOM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSBSUP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSBSUP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DR3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DR3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EDELC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EDELC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EDELC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EDELC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EDELNZ", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_EDELNZ, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_EDELNZ, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "EDRS", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_EDRS, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_EDRS, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "EMEP_C1", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_EMEP_C1, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EMEP_C1, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EMEP_C1, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EMEP_C1, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EMEP_C2", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_EMEP_C2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EMEP_C2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EMEP_C2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EMEP_C2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EN_C1", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_EN_C1, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EN_C1, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EN_C1, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EN_C1, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EN_C2", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_EN_C2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EN_C2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EN_C2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_EN_C2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EOW_SPT", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_EOW_SPT, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_EOW_SPT, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "ES1", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_ES1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_ES1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_COEF1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GAMMA_COEF1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_COEF2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GAMMA_COEF2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_1", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_GAMMA_REF_1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_GAMMA_REF_1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GAMMA_REF_2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GDHC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GDHC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GDHLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GDHLL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GDHS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GDHS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GDHUL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GDHUL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GEHDLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GEHDLL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GEHDUL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GEHDUL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GELL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GELL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GEUL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GEUL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GPHI", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GPHI, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GR", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GR, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GRDOT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GRDOT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GSBE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GSBE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GYDOT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GYDOT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_CLOOP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_CLOOP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_ERROR_MAXFF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_ERROR_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_FF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_FF, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_FLARE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_FLARE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_H_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_H_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "H_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_REF1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_REF1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_REF2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_REF2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_WL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_WL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HALI", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_HALI, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_HALI, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "HDREQG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HDREQG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HFTC", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_HFTC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_HFTC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBGC", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_PBGC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_PBGC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBHC", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_PBHC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_PBHC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBRC", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_PBRC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_PBRC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBRCQ", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_PBRCQ, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_PBRCQ, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PHAVGC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHAVGC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHAVGLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHAVGLL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHAVGS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHAVGS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHAVGUL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHAVGUL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHI_M1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHI_M1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHI_M2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHI_M2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHI_M3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHI_M3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILMSUP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILMSUP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILM0", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILM0, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILM1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILM1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILM2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILM2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHILM3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHILM3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "P2TRNC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_P2TRNC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QB_ERROR2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QB_ERROR2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBARDL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBARDL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBC1", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_QBC1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_QBC1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBC2", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_QBC2, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_QBC2, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBG1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBG1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBG2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBG2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBMXS2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMXS2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBMX1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMX1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBMX2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMX2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBMX3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBMX3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBM1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBM1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBM2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBM2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBRLL", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_QBRLL, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_QBRLL, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBRML", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_QBRML, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_QBRML, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBRUL", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_QBRUL, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_QBRUL, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "R", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_R_AL, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_R_AL, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_R_AL, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_R_AL, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "RERRLM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RERRLM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RFTC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RFTC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RMINST", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_RMINST, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_RMINST, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "SIGMA", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_SIGMA, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_SIGMA, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "TGGS", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_TGGS, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_TGGS, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "V_REF", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_V_REF, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_V_REF, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "WT_GS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_WT_GS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_AIM_PT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_AIM_PT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_EXP", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_X_EXP, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_EXP, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_X_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_X_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_ZERO", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_X_ZERO, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_X_ZERO, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "XA", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_XA, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_XA, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "Y_LIMIT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y_LIMIT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y_RANGE1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y_RANGE1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y_RANGE2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y_RANGE2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YERRLM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YERRLM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TIDELAY", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_TIDELAY, itmp );

	SimpleGPCSoftware::GetValILOAD( "RERR_DB", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RERR_DB, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GR_INTUP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GR_INTUP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GR_INTDN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GR_INTDN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RINT_LIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RINT_LIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PERR_DB", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PERR_DB, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GP_INTUP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GP_INTUP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GP_INTDN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GP_INTDN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PINT_LIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PINT_LIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TIDELAY5", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_TIDELAY5, itmp );

	SimpleGPCSoftware::GetValILOAD( "PERR_DB5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PERR_DB5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GP_INTUP5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GP_INTUP5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GP_INTDN5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GP_INTDN5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PINT_LIM5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PINT_LIM5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TIDELAYC", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_TIDELAYC, itmp );

	SimpleGPCSoftware::GetValILOAD( "ALT_HEAT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALT_HEAT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MET_HEAT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MET_HEAT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DOWN_DELAY", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_DOWN_DELAY, itmp );

	SimpleGPCSoftware::GetValILOAD( "X_NEP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_NEP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_BLANK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_BLANK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HERROR_NO_DIV", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_HERROR_NO_DIV, itmp );

	SimpleGPCSoftware::GetValILOAD( "HERROR_SC1_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_HERROR_SC1_LABEL, ctmp, 4 );

	SimpleGPCSoftware::GetValILOAD( "HERROR_SC2_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_HERROR_SC2_LABEL, ctmp, 4 );

	SimpleGPCSoftware::GetValILOAD( "HIGH_RATE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HIGH_RATE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HIGH_RATE_305603", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HIGH_RATE_305603, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLL_STOW_DELAY_TIME", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_ROLL_STOW_DELAY_TIME, itmp );

	SimpleGPCSoftware::GetValILOAD( "UNSTOW_DELAY_TIME", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_UNSTOW_DELAY_TIME, itmp );

	SimpleGPCSoftware::GetValILOAD( "LOW_RATE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LOW_RATE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "LOW_RATE_305603", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LOW_RATE_305603, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MED_RATE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MED_RATE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TGO_TICK_MARK", ILOADs, 5, dtmp );
	WriteCOMPOOL_VS( SCP_TGO_TICK_MARK, 1, static_cast<float>(dtmp[0]), 5 );
	WriteCOMPOOL_VS( SCP_TGO_TICK_MARK, 2, static_cast<float>(dtmp[1]), 5 );
	WriteCOMPOOL_VS( SCP_TGO_TICK_MARK, 3, static_cast<float>(dtmp[2]), 5 );
	WriteCOMPOOL_VS( SCP_TGO_TICK_MARK, 4, static_cast<float>(dtmp[3]), 5 );
	WriteCOMPOOL_VS( SCP_TGO_TICK_MARK, 5, static_cast<float>(dtmp[4]), 5 );

	SimpleGPCSoftware::GetValILOAD( "TGO_DISPLAY_CHAR", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TGO_DISPLAY_CHAR, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RERRC_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_RERRC_LABEL, ctmp, 4 );

	SimpleGPCSoftware::GetValILOAD( "YSC_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_YSC_LABEL, ctmp, 4 );

	SimpleGPCSoftware::GetValILOAD( "DISPLAY_OPTION", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_DISPLAY_OPTION, itmp );

	SimpleGPCSoftware::GetValILOAD( "XTRACK_NO_DIV", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_XTRACK_NO_DIV, itmp );

	SimpleGPCSoftware::GetValILOAD( "HDT1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HDT1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HDT2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HDT2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HDT3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HDT3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS_ALT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS_ALT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS_N_X", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS_N_X, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS_N_Y", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS_N_Y, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS_Y_RANGE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS_Y_RANGE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "NUM_MAX", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_NUM_MAX, itmp );

	SimpleGPCSoftware::GetValILOAD( "QBAR_PITCH", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_PITCH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBAR_ROLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_ROLL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBAR_SAT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_SAT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DPSACSC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DPSACSC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HERRSC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HERRSC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HERRSC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HERRSC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RERRCSC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RERRCSC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YSC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YSC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TGOSC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TGOSC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MIN_ROLL_AZ_WARN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MIN_ROLL_AZ_WARN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ENABLE_MEDS_DATA_TRANSFER", ILOADs, itmp );
	WriteCOMPOOL_IS( SCP_ENABLE_MEDS_DATA_TRANSFER, itmp );


	SimpleGPCSoftware::GetValILOAD( "TAU_TD2F", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TAU_TD2F, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RADIUS_EP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RADIUS_EP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HCLOOP2", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_HCLOOP2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HCLOOP2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HCLOOP2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HCLOOP2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "HDECAY2", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_HDECAY2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HDECAY2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HDECAY2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HDECAY2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "HEXP", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_HEXP, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HEXP, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HEXP, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_HEXP, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "RH", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_RH, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_RH, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_RH, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_RH, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "XDECAY", ILOADs, 4, dtmp );
	WriteCOMPOOL_MS( SCP_XDECAY, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_MS( SCP_XDECAY, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_MS( SCP_XDECAY, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_MS( SCP_XDECAY, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "SIGMAH", ILOADs, 2, dtmp );
	WriteCOMPOOL_VS( SCP_SIGMAH, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_VS( SCP_SIGMAH, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "RESELVE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RESELVE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HUD_NEP_PFNL_MIN_ALT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HUD_NEP_PFNL_MIN_ALT, static_cast<float>(dtmp1) );
	return;
}

unsigned short SimpleGPCSystem::GetPhysicalID( void ) const
{
	return (GNC ? 1 : 2);
}

}
