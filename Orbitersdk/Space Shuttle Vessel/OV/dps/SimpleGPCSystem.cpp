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
2024/06/16   GLS
2024/07/06   GLS
2025/01/23   GLS
2025/07/20   GLS
2025/01/14   GLS
********************************************/
#include "SimpleGPCSystem.h"
#include "Software/SimpleGPCSoftware.h"
#include "Software/GNC/SimpleFCOS_IO_GNC.h"
#include "Software/SM/SimpleFCOS_IO_SM.h"
#include "Software/GNC/SF.h"
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
#include "Software/GNC/TWO_AX_RHC_SOP.h"
#include "Software/GNC/THREE_AX_RHC_SOP.h"
#include "Software/GNC/ORB_THREE_AX_RHC_SOP.h"
#include "Software/GNC/THC_SOP.h"
#include "Software/GNC/RPTA_SOP.h"
#include "Software/GNC/SBTC_SOP.h"
#include "Software/GNC/Switch_RM.h"
#include "Software/GNC/BF_Slew_SOP.h"
#include "Software/GNC/Landing_SOP.h"
#include "Software/GNC/OMS_TVC_Command_SOP.h"
#include "Software/GNC/OMS_TVC_Feedback_SOP.h"
#include "Software/GNC/OMS_RM.h"
#include "Software/GNC/ADTA_RM.h"
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
#include "Software/GNC/ENT_DIP.h"
#include "Software/GNC/VERT_SIT_DIP.h"
#include "Software/GNC/HORIZ_SIT_SPEC.h"
#include "Software/FCOS.h"
#include "Software/KeyboardInterface.h"
#include "Software/UserInterfaceControl.h"
#include "Software/CRT_Interface.h"
#include "Software/ICC_Interface.h"
#include "Software/DPS_Reconfiguration.h"
#include "Software/GNC/GNCUtilities.h"
#include "Software/SM/SystemsServicesAnnunciation.h"
#include "Software/SM/SSB_PL_BAY_DOORS.h"
#include "Software/SM/SSO_SP_DATA_OUT.h"
#include "../Atlantis.h"
#include "../vc/MDU.h"


#if _DEBUG
#define CHECKS_ADDR
#define CHECKS_TYPE
#endif// _DEBUG


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
	pICC_Interface = new ICC_Interface( this );
	pDPS_Reconfiguration = new DPS_Reconfiguration( this );

	if (GNC)
	{
		pFCOS_IO = new SimpleFCOS_IO_GNC( this );

		// load GNC sw
		vSoftware.push_back( new GAX( this ) );
		vSoftware.push_back( new AnnunciationSupport( this ) );

		vSoftware.push_back( new FCOS(this));
		vSoftware.push_back( new GNCUtilities(this));
		vSoftware.push_back( new SF( this ) );
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
		vSoftware.push_back( new ADTA_RM( this ) );
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
		vSoftware.push_back( new TWO_AX_RHC_SOP( this ) );
		vSoftware.push_back( new THREE_AX_RHC_SOP( this ) );
		vSoftware.push_back( new ORB_THREE_AX_RHC_SOP( this ) );
		vSoftware.push_back( new THC_SOP( this ) );
		vSoftware.push_back( new RPTA_SOP( this ) );
		vSoftware.push_back( new SBTC_SOP( this ) );
		vSoftware.push_back( new Switch_RM( this ) );
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
		vSoftware.push_back( new ENT_DIP( this ) );
		vSoftware.push_back( new VERT_SIT_DIP( this ) );
		vSoftware.push_back( new HORIZ_SIT_SPEC( this ) );
	}
	else
	{
		pFCOS_IO = new SimpleFCOS_IO_SM( this );

		// load SM sw
		vSoftware.push_back( new FCOS( this ) );
		vSoftware.push_back( new SystemsServicesAnnunciation( this ) );

		vSoftware.push_back( new SSB_PL_BAY_DOORS( this ) );
		vSoftware.push_back( new SSO_SP_DATA_OUT( this ) );
		vSoftware.push_back( pUserDisplays = new SMDisplays( this ) );
	}

	pCRT_Interface = new CRT_Interface( this, pSystemDisplays, pUserDisplays );

	// I-LOADs init
	WriteCOMPOOL_IS( SCP_OVHD, 1 );
	WriteCOMPOOL_IS( SCP_IGS, 1 );
	WriteCOMPOOL_IS( SCP_IGI, 1 );
	WriteCOMPOOL_IS( SCP_GI_CHANGE, 0 );
	WriteCOMPOOL_IS( SCP_ENT_PT_SW, 0 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 1, 1, 32.45f, 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 2, 1, 32.44f, 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 1, 2, 26.18f, 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 2, 2, 26.3f, 2, 2 );
	WriteCOMPOOL_IS( SCP_P_MODE, 0 );
	WriteCOMPOOL_IS( SCP_IPHASE, 1 );
	WriteCOMPOOL_IS( SCP_TG_END, 0 );

	// init displays
	for (int i = 1; i <= 4; i++)
	{
		WriteCOMPOOL_AIS( SCP_CRT_SPEC, i, dps::MODE_UNDEFINED, 4 );
		WriteCOMPOOL_AIS( SCP_CRT_DISP, i, dps::MODE_UNDEFINED, 4 );
	}

	// connect to busses
	BusConnect( BUS_IC1 );
	BusConnect( BUS_IC2 );
	BusConnect( BUS_IC3 );
	BusConnect( BUS_IC4 );
	BusConnect( BUS_IC5 );
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
	switch (id)
	{
		case BUS_IC1:
		case BUS_IC2:
		case BUS_IC3:
		case BUS_IC4:
		case BUS_IC5:
			Rx_IC( id, data, datalen );
			break;
		case BUS_DK1:
		case BUS_DK2:
		case BUS_DK3:
		case BUS_DK4:
			if (!rcvr) return;
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
			if (!rcvr) return;
			Rx_FC( id, data, datalen );
			break;
		default:
			oapiWriteLogV( "(SSV_OV) [ERROR] unknown bus=%d", id );
			break;
	}
	return;
}

void SimpleGPCSystem::Rx_FC( const BUS_ID id, void* data, const unsigned short datalen )
{
	unsigned int* rcvd = static_cast<unsigned int*>(data);

	if (datalen != WriteBufferLength)
	{
		oapiWriteLogV( "(SSV_OV) [ERROR] bus=%d datalen != WriteBufferLength %d %d", id, datalen, WriteBufferLength );
		return;
	}

	// save data from subsystem
	for (unsigned short i = 0; i < WriteBufferLength; i++)
	{
		// check parity
		if (CalcParity( rcvd[i] ) == 0)
		{
			oapiWriteLogV( "(SSV_OV) [ERROR] bus=%d CalcParity", id );
			return;
		}

		// TODO check SEV

		// check addr
		unsigned char MIAaddr = (rcvd[i] >> 20) & 0b11111;
		if (MIAaddr != SubSystemAddress)// check if addr matches subsystem we're waiting data from
		{
			oapiWriteLogV( "(SSV_OV) [ERROR] bus=%d MIAaddr != SubSystemAddress %d %d", id, MIAaddr, SubSystemAddress );
			return;
		}

		// if MDM return word, save different location
		if (WriteBufferAddress == SCP_MDM_RETURN) SimpleCOMPOOL[WriteBufferAddress + i] = (rcvd[i] >> 1) & 0x3FFF;
		else SimpleCOMPOOL[WriteBufferAddress + i] = (rcvd[i] >> 4) & 0xFFFF;
	}
	return;
}

void SimpleGPCSystem::Rx_DK( const BUS_ID id, void* data, const unsigned short datalen )
{
	unsigned int* rcvd = static_cast<unsigned int*>(data);

	//// parse data word 1
	// check parity
	if (CalcParity( rcvd[0] ) == 0)
	{
		oapiWriteLogV( "(SSV_OV) [ERROR] bus=%d CalcParity", id );
		return;
	}

	// TODO check SEV

	unsigned short msgtype = (rcvd[0] >> 17) & 0b1111;
	if (msgtype == 0b0000)// poll response
	{
		// confirm received data len
		if (datalen != 16)
		{
			oapiWriteLogV( "(SSV_OV) [ERROR] bus=%d datalen=%d", id, datalen );
			return;
		}

		// save data words
		for (unsigned short i = 0; i < 16; i++)
		{
			// check parity
			if (CalcParity( rcvd[i] ) == 0)
			{
				oapiWriteLogV( "(SSV_OV) [ERROR] bus=%d CalcParity", id );
				return;
			}

			// TODO check SEV

			SimpleCOMPOOL[WriteBufferAddress + i] = (rcvd[i] >> 4) & 0xFFFF;
		}
	}
	return;
}

void SimpleGPCSystem::Rx_IC( const BUS_ID id, void* data, const unsigned short datalen )
{
	if (datalen != 124)
	{
		// TODO log error
		return;
	}

	unsigned short* rcvd = static_cast<unsigned short*>(data);

	unsigned short idx;
	if (id == BUS_IC1) idx = 1;
	else if (id == BUS_IC2) idx = 2;
	else if (id == BUS_IC3) idx = 3;
	else if (id == BUS_IC4) idx = 4;
	else /*if (id == BUS_IC5)*/ idx = 5;

	SCP_ICC_BUF CZ2V_ICC_BUF;
	ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, idx, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );

	CZ2V_ICC_BUF.CZ2B_OVERRUN_IND = rcvd[0];
	CZ2V_ICC_BUF.CZ2B_STATUS = rcvd[1];
	memcpy( &CZ2V_ICC_BUF.CZ2V_DUTY_CYCLE, &rcvd[2], 4 );
	memcpy( &CZ2V_ICC_BUF.CZ2V_SUM_WD, &rcvd[4], 4 );
	CZ2V_ICC_BUF.CZ2V_SSW_SUMWORD = rcvd[6];
	CZ2V_ICC_BUF.CZ2V_VAR_BUF_LENGTH = rcvd[7];
	CZ2V_ICC_BUF.CZ2B_DIA1 = rcvd[8];
	CZ2V_ICC_BUF.CZ2B_DIA2 = rcvd[9];
	CZ2V_ICC_BUF.CZ2B_DIB1 = rcvd[10];
	CZ2V_ICC_BUF.CZ2B_DIB2 = rcvd[11];
	memcpy( &CZ2V_ICC_BUF.CZ2B_GPC_MT, &rcvd[12], 4 );
	CZ2V_ICC_BUF.CZ2B_GPC_MT2 = rcvd[14];
	CZ2V_ICC_BUF.CZ2B_DK_GSE_DP = rcvd[15];
	memcpy( &CZ2V_ICC_BUF.CZ2V_MF_DPS, &rcvd[16], 4 );
	memcpy( &CZ2V_ICC_BUF.CZ2B_OPS_DPS, &rcvd[18], 4 );
	memcpy( &CZ2V_ICC_BUF.CZ2B_DP_DISP, &rcvd[20], 4 );
	memcpy( &CZ2V_ICC_BUF.CZ2B_NSP_BUFFER, &rcvd[22], 2 * 36 );
	memcpy( &CZ2V_ICC_BUF.CZ2B_MTU_BUFFER, &rcvd[58], 2 * 14 );
	CZ2V_ICC_BUF.CZ2B_ICC_ERROR_BUS_MSK = rcvd[72];
	memcpy( &CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF, &rcvd[73], 2 * 50 );
	CZ2V_ICC_BUF.CZ2V_ICC_CKSUM = rcvd[123];

	WriteCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, idx, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
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

void SimpleGPCSystem::UpdateProcessQueue( void )
{
	unsigned short mm = ReadCOMPOOL_IS( SCP_MM );

	vActiveSoftware.clear();
	for (unsigned int i = 0; i < vSoftware.size(); i++)
	{
		if (vSoftware[i]->OnMajorModeChange( mm ))
			vActiveSoftware.push_back( vSoftware[i] );
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
	pFCOS_IO->input();// input data from subsystems

	pICC_Interface->DME_ICC_ROUT();
	pKeyboardInterface->DMI_MCDS_IN();
	pUserInterfaceControl->DMC_SUPER();
	pCRT_Interface->DCICYC( simdt );

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

	// send ICC messages
	if (ReadCOMPOOL_IS( SCP_CZ2V_ICC_BUF_POINT ) != 1)
	{
		unsigned short data[124];
		SCP_ICC_BUF CZ2V_ICC_BUF;
		ReadCOMPOOL_ASTRUCT( SCP_CZ2V_ICC_BUF, GNC ? 1 : 2, &CZ2V_ICC_BUF, sizes_ICC_BUF, pos_ICC_BUF, cnt_ICC_BUF, 5 );
		data[0] = CZ2V_ICC_BUF.CZ2B_OVERRUN_IND;
		data[1] = CZ2V_ICC_BUF.CZ2B_STATUS;
		memcpy( &data[2], &CZ2V_ICC_BUF.CZ2V_DUTY_CYCLE, 4 );
		memcpy( &data[4], &CZ2V_ICC_BUF.CZ2V_SUM_WD, 4 );
		data[6] = CZ2V_ICC_BUF.CZ2V_SSW_SUMWORD;
		data[7] = CZ2V_ICC_BUF.CZ2V_VAR_BUF_LENGTH;
		data[8] = CZ2V_ICC_BUF.CZ2B_DIA1;
		data[9] = CZ2V_ICC_BUF.CZ2B_DIA2;
		data[10] = CZ2V_ICC_BUF.CZ2B_DIB1;
		data[11] = CZ2V_ICC_BUF.CZ2B_DIB2;
		memcpy( &data[12], &CZ2V_ICC_BUF.CZ2B_GPC_MT, 4 );
		data[14] = CZ2V_ICC_BUF.CZ2B_GPC_MT2;
		data[15] = CZ2V_ICC_BUF.CZ2B_DK_GSE_DP;
		memcpy( &data[16], &CZ2V_ICC_BUF.CZ2V_MF_DPS, 4 );
		memcpy( &data[18], &CZ2V_ICC_BUF.CZ2B_OPS_DPS, 4 );
		memcpy( &data[20], &CZ2V_ICC_BUF.CZ2B_DP_DISP, 4 );
		memcpy( &data[22], &CZ2V_ICC_BUF.CZ2B_NSP_BUFFER, 2 * 36 );
		memcpy( &data[58], &CZ2V_ICC_BUF.CZ2B_MTU_BUFFER, 2 * 14 );
		data[72] = CZ2V_ICC_BUF.CZ2B_ICC_ERROR_BUS_MSK;
		memcpy( &data[73], &CZ2V_ICC_BUF.CZ2V_ICC_MSG_BUF, 2 * 50 );
		data[123] = CZ2V_ICC_BUF.CZ2V_ICC_CKSUM;

		if (GNC) Tx( BUS_IC1, data, 124 );
		else Tx( BUS_IC2, data, 124 );
	}
	return;
}

void SimpleGPCSystem::OnPropagate(double simt, double simdt, double mjd)
{
	for(unsigned int i=0;i<vActiveSoftware.size();i++)
		vActiveSoftware[i]->OnPropagate(simt, simdt, mjd);
}

bool SimpleGPCSystem::OnReadState( FILEHANDLE scn )
{
	char* line;
	char pszKey[256];
	SimpleGPCSoftware* pCurrentSoftware = NULL;
	while (oapiReadScenario_nextline( scn, line ))
	{
		if (!_strnicmp( line, "@ENDSUBSYSTEM", 13 ))
		{
			return true;
		}
		else
		{
			if (!_strnicmp( line, "@ENDSOFTWARE", 12 ))
			{
				pCurrentSoftware = NULL;
			}
			else
			{
				unsigned long i = 0;
				while (*line != ' ' && *line != '\0')
				{
					pszKey[i++] = *line;
					line++;
				}
				pszKey[i++] = '\0';
				if (*line == ' ') line++;
				if (!_strnicmp( pszKey, "@BEGINSOFTWARE", 14 ))
				{
					pCurrentSoftware = FindSoftware( line );
				}
				else if (pCurrentSoftware)
				{
					if (*line != '\0')
					{
						pCurrentSoftware->OnParseLine( pszKey, line );
					}
					else
					{
						pCurrentSoftware->OnParseLine( pszKey, NULL );
					}
				}
				else
				{
					// SimpleCOMPOOL vals
					if (!_strnicmp( pszKey, "MM", 2 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_MM, tmp );
						UpdateProcessQueue();
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
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 99) WriteCOMPOOL_IS( SCP_SM_TONE_DURATION, tmp );
					}
					else if (!_strnicmp( pszKey, "AREA_SEL", 8 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if ((tmp >= 1) && (tmp <= 45)) WriteCOMPOOL_IS( SCP_AREA_SEL, tmp );
					}
					else if (!_strnicmp( pszKey, "OVHD", 4 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_OVHD, tmp );
					}
					else if (!_strnicmp( pszKey, "IGS", 3 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_IGS, tmp );
					}
					else if (!_strnicmp( pszKey, "IGI", 3 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if ((tmp >= 1) && (tmp <= 2)) WriteCOMPOOL_IS( SCP_IGI, tmp );
					}
					else if (!_strnicmp( pszKey, "RUNWAY_NAME_PSL", 15 ))
					{
						WriteCOMPOOL_C( SCP_RUNWAY_NAME_PSL, line, 5 );
					}
					else if (!_strnicmp( pszKey, "RUNWAY_NAME_SSL", 15 ))
					{
						WriteCOMPOOL_C( SCP_RUNWAY_NAME_SSL, line, 5 );
					}
					else if (!_strnicmp( pszKey, "RW_SELECT", 9 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_RW_SELECT, tmp );
					}
					else if (!_strnicmp( pszKey, "RW_NAME", 7 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if ((tmp >= 1) && (tmp <= 90)) WriteCOMPOOL_IS( SCP_RW_NAME, tmp );
					}
					else if (!_strnicmp( pszKey, "SEL_SITE_ID", 11 ))
					{
						WriteCOMPOOL_C( SCP_SEL_SITE_ID, line, 5 );
					}
					else if (!_strnicmp( pszKey, "ALT_RW", 6 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_ALT_RW, tmp );
					}
					else if (!_strnicmp( pszKey, "AZIMUTH_RW", 10 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_AZIMUTH_RW, tmp );
					}
					else if (!_strnicmp( pszKey, "HUD_RW_LENGTH", 13 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_HUD_RW_LENGTH, tmp );
					}
					else if (!_strnicmp( pszKey, "DELH_MSL_ELLIPSOID_RW", 21 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW, tmp );
					}
					else if (!_strnicmp( pszKey, "ANGLE_CORR_TNTOMAG_RW", 21 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW, tmp );
					}
					else if (!_strnicmp( pszKey, "M_EFTORW", 8 ))
					{
						MATRIX3 mtmp;
						sscanf_s( line, "%lf%lf%lf%lf%lf%lf%lf%lf%lf", &mtmp.m11, &mtmp.m12, &mtmp.m13, &mtmp.m21, &mtmp.m22, &mtmp.m23, &mtmp.m31, &mtmp.m32, &mtmp.m33 );
						WriteCOMPOOL_MS( SCP_M_EFTORW, mtmp );
					}
					else if (!_strnicmp( pszKey, "R_LS_EF", 7 ))
					{
						VECTOR3 vtmp;
						sscanf_s( line, "%lf%lf%lf", &vtmp.x, &vtmp.y, &vtmp.z );
						WriteCOMPOOL_VD( SCP_R_LS_EF, vtmp );
					}
					else if (!_strnicmp( pszKey, "M_EFTOTD_RW", 11 ))
					{
						MATRIX3 mtmp;
						sscanf_s( line, "%lf%lf%lf%lf%lf%lf%lf%lf%lf", &mtmp.m11, &mtmp.m12, &mtmp.m13, &mtmp.m21, &mtmp.m22, &mtmp.m23, &mtmp.m31, &mtmp.m32, &mtmp.m33 );
						WriteCOMPOOL_MS( SCP_M_EFTOTD_RW, mtmp );
					}
					else if (!_strnicmp( pszKey, "R_CC_L_PRI", 10 ))
					{
						VECTOR3 vtmp;
						sscanf_s( line, "%lf%lf%lf", &vtmp.x, &vtmp.y, &vtmp.z );
						WriteCOMPOOL_VS( SCP_R_CC_L_PRI, vtmp );
					}
					else if (!_strnicmp( pszKey, "R_CC_R_PRI", 10 ))
					{
						VECTOR3 vtmp;
						sscanf_s( line, "%lf%lf%lf", &vtmp.x, &vtmp.y, &vtmp.z );
						WriteCOMPOOL_VS( SCP_R_CC_R_PRI, vtmp );
					}
					else if (!_strnicmp( pszKey, "R_CC_LMAG_PRI", 13 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_R_CC_LMAG_PRI, tmp );
					}
					else if (!_strnicmp( pszKey, "R_CC_RMAG_PRI", 13 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_R_CC_RMAG_PRI, tmp );
					}
					
					else if (!_strnicmp( pszKey, "RW_ID_UPP", 9 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_RW_ID_UPP, tmp );
					}
					else if (!_strnicmp( pszKey, "R_NEP", 5 ))
					{
						float tmp = 0.0f;
						sscanf_s( line, "%f", &tmp );
						WriteCOMPOOL_SS( SCP_R_NEP, tmp );
					}
					else if (!_strnicmp( pszKey, "RETRACT_BF", 10 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_RETRACT_BF, tmp );
					}
					else if (!_strnicmp( pszKey, "WOWLON_IND", 10 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_WOWLON_IND, tmp );
					}
					else if (!_strnicmp( pszKey, "FLATTURN_CMD", 12 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_FLATTURN_CMD, tmp );
					}
					else if (!_strnicmp( pszKey, "ROLLOUT_IND", 11 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ROLLOUT_IND, tmp );
					}
					else if (!_strnicmp( pszKey, "GSENBL", 6 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_GSENBL, tmp );
					}
					else if (!_strnicmp( pszKey, "HUD_WOWLON", 10 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_HUD_WOWLON, tmp );
					}
					else if (!_strnicmp( pszKey, "HUD_ROLLOUT", 11 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_HUD_ROLLOUT, tmp );
					}
					else if (!_strnicmp( pszKey, "P_MODE", 6 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 4) WriteCOMPOOL_IS( SCP_P_MODE, tmp );
					}
					else if (!_strnicmp( pszKey, "IPHASE", 6 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 3) WriteCOMPOOL_IS( SCP_IPHASE, tmp );
					}
					else if (!_strnicmp( pszKey, "TG_END", 6 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_TG_END, tmp );
					}
					else if (!_strnicmp( pszKey, "ISLECT", 6 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
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
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
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
					else if (!_strnicmp( pszKey, "WRAP_MODE", 9 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_WRAP_MODE, tmp );
					}
					else if (!_strnicmp( pszKey, "VENT_DOOR_SEQ_INIT", 19 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_VENT_DOOR_SEQ_INIT, tmp );
					}
					else if (!_strnicmp( pszKey, "ALL_VENT_CLOSE_CMD", 18 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
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
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN, tmp );
					}
					else if (!_strnicmp( pszKey, "ME2_FAIL_SHUTDOWN", 17 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN, tmp );
					}
					else if (!_strnicmp( pszKey, "ME3_FAIL_SHUTDOWN", 17 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN, tmp );
					}
					else if (!_strnicmp( pszKey, "MECO_CMD", 8 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_MECO_CMD, tmp );
					}
					else if (!_strnicmp( pszKey, "MECO_CONFIRMED", 14 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						if (tmp <= 1) WriteCOMPOOL_IS( SCP_MECO_CONFIRMED, tmp );
					}
					else if (!_strnicmp( pszKey, "FAULT_DISPBUF_CNT", 17 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
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
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_FAULT_MSG_LINE_STATE, tmp );
					}
					else if (!_strnicmp( pszKey, "FAULT_MSG_LINE", 14 ))
					{
						WriteCOMPOOL_AC( SCP_FAULT_MSG_LINE, 1, line, 15, 43 );
					}
					else if (!_strnicmp( pszKey, "FAULT_MSG_BUF_IND", 17 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_FAULT_MSG_BUF_IND, tmp );
					}
					else if (!_strnicmp( pszKey, "OMSL_ACT_SEL", 12 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_OMSL_ACT_SEL, tmp );
					}
					else if (!_strnicmp( pszKey, "OMSR_ACT_SEL", 12 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_OMSR_ACT_SEL, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_AUTO_MODE_ITEM", 19 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_MANUAL_MODE_ITEM", 21 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_POWER_ON_OFF_ITEM", 22 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_POWER_ON_OFF_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_SWITCH_BYPASS_ITEM", 23 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_SWITCH_BYPASS_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_PBD_OPEN_ITEM", 18 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_OPEN_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_PBD_STOP_ITEM", 18 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_STOP_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_PBD_CLOSE_ITEM", 19 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_PBD_CLOSE_ITEM, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_OPEN_FAIL_INDICATOR", 24 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_OPEN_FAIL_INDICATOR, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_CLOSE_FAIL_INDICATOR", 25 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_CLOSE_FAIL_INDICATOR, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_AUTO_MODE_FLAG", 19 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_AUTO_MODE_FLAG, tmp );
					}
					else if (!_strnicmp( pszKey, "CSBB_MANUAL_MODE_FLAG", 21 ))
					{
						unsigned short tmp = 0;
						sscanf_s( line, "%hu", &tmp );
						WriteCOMPOOL_IS( SCP_CSBB_MANUAL_MODE_FLAG, tmp );
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
					}
					else
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
		oapiWriteScenario_int( scn, "AREA_SEL", ReadCOMPOOL_IS( SCP_AREA_SEL ) );
		oapiWriteScenario_int( scn, "OVHD", ReadCOMPOOL_IS( SCP_OVHD ) );
		oapiWriteScenario_int( scn, "IGS", ReadCOMPOOL_IS( SCP_IGS ) );
		oapiWriteScenario_int( scn, "IGI", ReadCOMPOOL_IS( SCP_IGI ) );

		memset( cbuf, 0, 6 );
		ReadCOMPOOL_C( SCP_RUNWAY_NAME_PSL, cbuf, 5 );
		oapiWriteScenario_string( scn, "RUNWAY_NAME_PSL", cbuf );

		memset( cbuf, 0, 6 );
		ReadCOMPOOL_C( SCP_RUNWAY_NAME_SSL, cbuf, 5 );
		oapiWriteScenario_string( scn, "RUNWAY_NAME_SSL", cbuf );

		oapiWriteScenario_int( scn, "RW_SELECT", ReadCOMPOOL_IS( SCP_RW_SELECT ) );
		oapiWriteScenario_int( scn, "RW_NAME", ReadCOMPOOL_IS( SCP_RW_NAME ) );

		memset( cbuf, 0, 6 );
		ReadCOMPOOL_C( SCP_SEL_SITE_ID, cbuf, 5 );
		oapiWriteScenario_string( scn, "SEL_SITE_ID", cbuf );

		oapiWriteScenario_float( scn, "ALT_RW", ReadCOMPOOL_SS( SCP_ALT_RW ) );
		oapiWriteScenario_float( scn, "AZIMUTH_RW", ReadCOMPOOL_SS( SCP_AZIMUTH_RW ) );
		oapiWriteScenario_int( scn, "HUD_RW_LENGTH", ReadCOMPOOL_IS( SCP_HUD_RW_LENGTH ) );
		oapiWriteScenario_float( scn, "DELH_MSL_ELLIPSOID_RW", ReadCOMPOOL_SS( SCP_DELH_MSL_ELLIPSOID_RW ) );
		oapiWriteScenario_float( scn, "ANGLE_CORR_TNTOMAG_RW", ReadCOMPOOL_SS( SCP_ANGLE_CORR_TNTOMAG_RW ) );

		MATRIX3 mtmp = ReadCOMPOOL_MS( SCP_M_EFTORW );
		sprintf_s( cbuf, 256, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", mtmp.m11, mtmp.m12, mtmp.m13, mtmp.m21, mtmp.m22, mtmp.m23, mtmp.m31, mtmp.m32, mtmp.m33 );
		oapiWriteScenario_string( scn, "M_EFTORW", cbuf );

		oapiWriteScenario_vec( scn, "R_LS_EF", ReadCOMPOOL_VD( SCP_R_LS_EF ) );

		mtmp = ReadCOMPOOL_MS( SCP_M_EFTOTD_RW );
		sprintf_s( cbuf, 256, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", mtmp.m11, mtmp.m12, mtmp.m13, mtmp.m21, mtmp.m22, mtmp.m23, mtmp.m31, mtmp.m32, mtmp.m33 );
		oapiWriteScenario_string( scn, "M_EFTOTD_RW", cbuf );

		oapiWriteScenario_vec( scn, "R_CC_L_PRI", ReadCOMPOOL_VS( SCP_R_CC_L_PRI ) );
		oapiWriteScenario_vec( scn, "R_CC_R_PRI", ReadCOMPOOL_VS( SCP_R_CC_R_PRI ) );

		oapiWriteScenario_float( scn, "R_CC_LMAG_PRI", ReadCOMPOOL_SS( SCP_R_CC_LMAG_PRI ) );
		oapiWriteScenario_float( scn, "R_CC_RMAG_PRI", ReadCOMPOOL_SS( SCP_R_CC_RMAG_PRI ) );

		oapiWriteScenario_int( scn, "RW_ID_UPP", ReadCOMPOOL_IS( SCP_RW_ID_UPP ) );
		oapiWriteScenario_float( scn, "R_NEP", ReadCOMPOOL_SS( SCP_R_NEP ) );

		oapiWriteScenario_int( scn, "RETRACT_BF", ReadCOMPOOL_IS( SCP_RETRACT_BF ) );

		oapiWriteScenario_int( scn, "WOWLON_IND", ReadCOMPOOL_IS( SCP_WOWLON_IND ) );
		oapiWriteScenario_int( scn, "FLATTURN_CMD", ReadCOMPOOL_IS( SCP_FLATTURN_CMD ) );
		oapiWriteScenario_int( scn, "ROLLOUT_IND", ReadCOMPOOL_IS( SCP_ROLLOUT_IND ) );
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

		oapiWriteScenario_int( scn, "WRAP_MODE", ReadCOMPOOL_IS( SCP_WRAP_MODE ) );

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

SimpleGPCSoftware* SimpleGPCSystem::FindSoftware(const std::string& identifier) const
{
	for(unsigned int i=0;i<vSoftware.size();i++) {
		if(vSoftware[i]->GetIdentifier() == identifier) {
			return vSoftware[i];
		}
	}
	return NULL;
}

float SimpleGPCSystem::ReadCOMPOOL_SS( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_SS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 2) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_SS ((addr + 2) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_SS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_SS)
		throw std::exception( std::string( "ReadCOMPOOL_SS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;
	memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
	return tmp;
}

double SimpleGPCSystem::ReadCOMPOOL_SD( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_SD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 4) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_SD ((addr + 4) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_SD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_SD)
		throw std::exception( std::string( "ReadCOMPOOL_SD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	double tmp = 0.0;
	memcpy( &tmp, SimpleCOMPOOL + addr, 8 );
	return tmp;
}

unsigned short SimpleGPCSystem::ReadCOMPOOL_IS( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_IS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 1) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_IS ((addr + 1) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_IS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_IS)
		throw std::exception( std::string( "ReadCOMPOOL_IS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	return SimpleCOMPOOL[addr];
}

unsigned int SimpleGPCSystem::ReadCOMPOOL_ID( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 2) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ID ((addr + 2) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_ID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ID)
		throw std::exception( std::string( "ReadCOMPOOL_ID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	unsigned int tmp = 0;
	memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
	return tmp;
}

void SimpleGPCSystem::ReadCOMPOOL_C( const unsigned int addr, char* val, const unsigned short size ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (size == 0)
		throw std::exception( std::string( "ReadCOMPOOL_C (size == 0) " + std::to_string( addr ) ).c_str() );
	if (size > 255)
		throw std::exception( std::string( "ReadCOMPOOL_C (size > 255) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_C (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + ((size + 1) / 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_C ((addr + ((size + 1) / 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_C type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_C)
		throw std::exception( std::string( "ReadCOMPOOL_C wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( val, (const char*)SimpleCOMPOOL + (addr * 2), size );
	return;
}

float SimpleGPCSystem::ReadCOMPOOL_VS( const unsigned int addr, const unsigned short n, const unsigned short nsize ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "ReadCOMPOOL_VS (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "ReadCOMPOOL_VS (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "ReadCOMPOOL_VS (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "ReadCOMPOOL_VS (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VS ((addr + (nsize * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_VS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VS)
		throw std::exception( std::string( "ReadCOMPOOL_VS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((n - 1) * 2), 4 );
	return tmp;
}

VECTOR3 SimpleGPCSystem::ReadCOMPOOL_VS( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 6) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VS ((addr + 6) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_VS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VS)
		throw std::exception( std::string( "ReadCOMPOOL_VS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	VECTOR3 v3 = _V( 0.0, 0.0, 0.0 );
	float tmp = 0.0f;

	memcpy( &tmp, SimpleCOMPOOL + addr, 4 );
	v3.x = tmp;
	memcpy( &tmp, SimpleCOMPOOL + addr + 2, 4 );
	v3.y = tmp;
	memcpy( &tmp, SimpleCOMPOOL + addr + 4, 4 );
	v3.z = tmp;
	return v3;
}

double SimpleGPCSystem::ReadCOMPOOL_VD( const unsigned int addr, const unsigned short n, const unsigned short nsize ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "ReadCOMPOOL_VD (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "ReadCOMPOOL_VD (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "ReadCOMPOOL_VD (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "ReadCOMPOOL_VD (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VD ((addr + (nsize * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_VD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VD)
		throw std::exception( std::string( "ReadCOMPOOL_VD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	double tmp = 0.0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((n - 1) * 4), 8 );
	return tmp;
}

VECTOR3 SimpleGPCSystem::ReadCOMPOOL_VD( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 12) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_VD ((addr + 12) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_VD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VD)
		throw std::exception( std::string( "ReadCOMPOOL_VD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	VECTOR3 v3 = _V( 0.0, 0.0, 0.0 );

	memcpy( &v3.x, SimpleCOMPOOL + addr, 8 );
	memcpy( &v3.y, SimpleCOMPOOL + addr + 4, 8 );
	memcpy( &v3.z, SimpleCOMPOOL + addr + 8, 8 );
	return v3;
}

float SimpleGPCSystem::ReadCOMPOOL_MS( const unsigned int addr, const unsigned short m, const unsigned short n, const unsigned short msize, const unsigned short nsize ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "ReadCOMPOOL_MS (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "ReadCOMPOOL_MS (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "ReadCOMPOOL_MS (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "ReadCOMPOOL_MS (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (m == 0)
		throw std::exception( std::string( "ReadCOMPOOL_MS (m == 0) " + std::to_string( addr ) ).c_str() );
	if (msize < 2)
		throw std::exception( std::string( "ReadCOMPOOL_MS (msize < 2) " + std::to_string( addr ) ).c_str() );
	if (msize > 64)
		throw std::exception( std::string( "ReadCOMPOOL_MS (msize > 64) " + std::to_string( addr ) ).c_str() );
	if (m > msize)
		throw std::exception( std::string( "ReadCOMPOOL_MS (m > msize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * msize * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MS ((addr + (nsize * msize * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_MS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MS)
		throw std::exception( std::string( "ReadCOMPOOL_MS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((m - 1) * nsize) + (n - 1)) * 2), 4 );
	return tmp;
}

MATRIX3 SimpleGPCSystem::ReadCOMPOOL_MS( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 18) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MS ((addr + 18) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_MS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MS)
		throw std::exception( std::string( "ReadCOMPOOL_MS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	MATRIX3 m3 = _M( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
	float tmp = 0.0f;

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
	return m3;
}

double SimpleGPCSystem::ReadCOMPOOL_MD( const unsigned int addr, const unsigned short m, const unsigned short n, const unsigned short msize, const unsigned short nsize ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "ReadCOMPOOL_MD (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "ReadCOMPOOL_MD (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "ReadCOMPOOL_MD (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "ReadCOMPOOL_MD (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (m == 0)
		throw std::exception( std::string( "ReadCOMPOOL_MD (m == 0) " + std::to_string( addr ) ).c_str() );
	if (msize < 2)
		throw std::exception( std::string( "ReadCOMPOOL_MD (msize < 2) " + std::to_string( addr ) ).c_str() );
	if (msize > 64)
		throw std::exception( std::string( "ReadCOMPOOL_MD (msize > 64) " + std::to_string( addr ) ).c_str() );
	if (m > msize)
		throw std::exception( std::string( "ReadCOMPOOL_MD (m > msize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * msize * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MD ((addr + (nsize * msize * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_MD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MD)
		throw std::exception( std::string( "ReadCOMPOOL_MD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	double tmp = 0.0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((m - 1) * nsize) + (n - 1)) * 4), 8 );
	return tmp;
}

MATRIX3 SimpleGPCSystem::ReadCOMPOOL_MD( const unsigned int addr ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 36) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_MD ((addr + 36) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_MD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MD)
		throw std::exception( std::string( "ReadCOMPOOL_MD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	MATRIX3 m3 = _M( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );

	memcpy( &m3.m11, SimpleCOMPOOL + addr, 8 );
	memcpy( &m3.m12, SimpleCOMPOOL + addr + 4, 8 );
	memcpy( &m3.m13, SimpleCOMPOOL + addr + 8, 8 );

	memcpy( &m3.m21, SimpleCOMPOOL + addr + 12, 8 );
	memcpy( &m3.m22, SimpleCOMPOOL + addr + 16, 8 );
	memcpy( &m3.m23, SimpleCOMPOOL + addr + 20, 8 );

	memcpy( &m3.m31, SimpleCOMPOOL + addr + 24, 8 );
	memcpy( &m3.m32, SimpleCOMPOOL + addr + 28, 8 );
	memcpy( &m3.m33, SimpleCOMPOOL + addr + 32, 8 );
	return m3;
}

void SimpleGPCSystem::ReadCOMPOOL_STRUCT( const unsigned int addr, void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (strct == 0)
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT (strct == 0) " + std::to_string( addr ) ).c_str() );
	if (sizes == 0)
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT (sizes == 0) " + std::to_string( addr ) ).c_str() );
	if (pos == 0)
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT (pos == 0) " + std::to_string( addr ) ).c_str() );
	if (elcnt == 0)
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT (elcnt == 0) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_STRUCT)
		throw std::exception( std::string( "ReadCOMPOOL_STRUCT wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	int offset = 0;// [byte]

	for (unsigned short i = 0; i < elcnt; i++)
	{
		memcpy( (char*)strct + pos[i], (const char*)SimpleCOMPOOL + (addr * 2) + offset, sizes[i] );

		offset += sizes[i];
	}
	return;
}

float SimpleGPCSystem::ReadCOMPOOL_ASS( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASS (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "ReadCOMPOOL_ASS (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_ASS (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "ReadCOMPOOL_ASS (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ASS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ASS ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_ASS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ASS)
		throw std::exception( std::string( "ReadCOMPOOL_ASS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((idx - 1) * 2), 4 );
	return tmp;
}

double SimpleGPCSystem::ReadCOMPOOL_ASD( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASD (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "ReadCOMPOOL_ASD (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_ASD (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "ReadCOMPOOL_ASD (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ASD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ASD ((addr + (size * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_ASD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ASD)
		throw std::exception( std::string( "ReadCOMPOOL_ASD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	double tmp = 0.0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((idx - 1) * 4), 8 );
	return tmp;
}

unsigned short SimpleGPCSystem::ReadCOMPOOL_AIS( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "ReadCOMPOOL_AIS (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "ReadCOMPOOL_AIS (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_AIS (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "ReadCOMPOOL_AIS (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_AIS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + size) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_AIS ((addr + size) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_AIS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_AIS)
		throw std::exception( std::string( "ReadCOMPOOL_AIS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	return SimpleCOMPOOL[addr + idx - 1];
}

unsigned int SimpleGPCSystem::ReadCOMPOOL_AID( const unsigned int addr, const unsigned short idx, const unsigned short size ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "ReadCOMPOOL_AID (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "ReadCOMPOOL_AID (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_AID (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "ReadCOMPOOL_AID (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_AID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_AID ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_AID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_AID)
		throw std::exception( std::string( "ReadCOMPOOL_AID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	unsigned int tmp = 0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((idx - 1) * 2), 4 );
	return tmp;
}

void SimpleGPCSystem::ReadCOMPOOL_AC( const unsigned int addr, const unsigned short idx, char* val, const unsigned short size_a, const unsigned short size_c ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "ReadCOMPOOL_AC (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size_c == 0)
		throw std::exception( std::string( "ReadCOMPOOL_AC (size_c == 0) " + std::to_string( addr ) ).c_str() );
	if (size_c > 255)
		throw std::exception( std::string( "ReadCOMPOOL_AC (size_c > 255) " + std::to_string( addr ) ).c_str() );
	if (size_a < 2)
		throw std::exception( std::string( "ReadCOMPOOL_AC (size_a < 2) " + std::to_string( addr ) ).c_str() );
	if (size_a > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_AC (size_a > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size_a)
		throw std::exception( std::string( "ReadCOMPOOL_AC (idx > size_a) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_AC (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size_a * ((size_c + 1) / 2))) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_AC ((addr + (size_a * ((size_c + 1) / 2))) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_AC type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_AC)
		throw std::exception( std::string( "ReadCOMPOOL_AC wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( val, (const char*)SimpleCOMPOOL + (addr * 2) + ((idx - 1) * size_c), size_c );
	return;
}

// TODO AVS

// TODO AVD

// TODO AMS

// TODO AMD

void SimpleGPCSystem::ReadCOMPOOL_ASTRUCT( const unsigned int addr, const unsigned short idx, void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt, const unsigned short size ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (idx > size) " + std::to_string( addr ) ).c_str() );
	if (strct == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (strct == 0) " + std::to_string( addr ) ).c_str() );
	if (sizes == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (sizes == 0) " + std::to_string( addr ) ).c_str() );
	if (pos == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (pos == 0) " + std::to_string( addr ) ).c_str() );
	if (elcnt == 0)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (elcnt == 0) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ASTRUCT)
		throw std::exception( std::string( "ReadCOMPOOL_ASTRUCT wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	int sum = 0;
	for (unsigned int i = 0; i < elcnt; i++) sum += sizes[i];
	int itempos = sum * (idx - 1);

	int offset = 0;// [byte]

	for (size_t i = 0; i < elcnt; i++)
	{
		memcpy( (char*)strct + pos[i], (const char*)SimpleCOMPOOL + (addr * 2) + offset + itempos, sizes[i] );

		offset += sizes[i];
	}
	return;
}

float SimpleGPCSystem::ReadCOMPOOL_A2SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A2SS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2SS)
		throw std::exception( std::string( "ReadCOMPOOL_A2SS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((idx1 - 1) * size2) + (idx2 - 1)) * 2), 4 );
	return tmp;
}

double SimpleGPCSystem::ReadCOMPOOL_A2SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD ((addr + (size1 * size2 * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A2SD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2SD)
		throw std::exception( std::string( "ReadCOMPOOL_A2SD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	double tmp = 0.0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((idx1 - 1) * size2) + (idx2 - 1)) * 4), 8 );
	return tmp;
}

unsigned short SimpleGPCSystem::ReadCOMPOOL_A2IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS ((addr + (size1 * size2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A2IS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2IS)
		throw std::exception( std::string( "ReadCOMPOOL_A2IS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	return SimpleCOMPOOL[addr + ((idx1 - 1) * size2) + (idx2 - 1)];
}

unsigned int SimpleGPCSystem::ReadCOMPOOL_A2ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short size1, const unsigned short size2 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A2ID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2ID)
		throw std::exception( std::string( "ReadCOMPOOL_A2ID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	unsigned int tmp = 0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((idx1 - 1) * size2) + (idx2 - 1)) * 2), 4 );
	return tmp;
}

// TODO AC2

// TODO AVS2

// TODO AVD2

// TODO AMS2

// TODO AMD2

// TODO ASTRUCT2

float SimpleGPCSystem::ReadCOMPOOL_A3SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A3SS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3SS)
		throw std::exception( std::string( "ReadCOMPOOL_A3SS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)) * 2), 4 );
	return tmp;
}

double SimpleGPCSystem::ReadCOMPOOL_A3SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3 * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD ((addr + (size1 * size2 * size3 * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A3SD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3SD)
		throw std::exception( std::string( "ReadCOMPOOL_A3SD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	double tmp = 0.0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)) * 4), 8 );
	return tmp;
}

unsigned short SimpleGPCSystem::ReadCOMPOOL_A3IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS ((addr + (size1 * size2 * size3)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A3IS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3IS)
		throw std::exception( std::string( "ReadCOMPOOL_A3IS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	return SimpleCOMPOOL[addr + ((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)];
}

unsigned int SimpleGPCSystem::ReadCOMPOOL_A3ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short size1, const unsigned short size2, const unsigned short size3 ) const
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "ReadCOMPOOL_A3ID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3ID)
		throw std::exception( std::string( "ReadCOMPOOL_A3ID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	unsigned int tmp = 0;
	memcpy( &tmp, SimpleCOMPOOL + addr + ((((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)) * 2), 4 );
	return tmp;
}

// TODO AC3

// TODO AVS3

// TODO AVD3

// TODO AMS3

// TODO AMD3

// TODO ASTRUCT3

void SimpleGPCSystem::WriteCOMPOOL_SS( const unsigned int addr, const float val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_SS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 2) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_SS ((addr + 2) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_SS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_SS)
		throw std::exception( std::string( "WriteCOMPOOL_SS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr, &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_SD( const unsigned int addr, const double val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_SD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 4) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_SD ((addr + 4) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_SD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_SD)
		throw std::exception( std::string( "WriteCOMPOOL_SD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr, &val, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_IS( const unsigned int addr, const unsigned short val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_IS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 1) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_IS ((addr + 1) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_IS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_IS)
		throw std::exception( std::string( "WriteCOMPOOL_IS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	SimpleCOMPOOL[addr] = val;
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_ID( const unsigned int addr, const unsigned int val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 2) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ID ((addr + 2) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_ID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ID)
		throw std::exception( std::string( "WriteCOMPOOL_ID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr, &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_C( const unsigned int addr, const char* val, const unsigned short size )
{
#ifdef CHECKS_ADDR
	// address checks
	if (size == 0)
		throw std::exception( std::string( "WriteCOMPOOL_C (size == 0) " + std::to_string( addr ) ).c_str() );
	if (size > 255)
		throw std::exception( std::string( "WriteCOMPOOL_C (size > 255) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_C (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + ((size + 1) / 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_C ((addr + ((size + 1) / 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_C type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_C)
		throw std::exception( std::string( "WriteCOMPOOL_C wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	size_t sz = min(strlen( val ), size);
	memcpy( (char*)SimpleCOMPOOL + (addr * 2), val, sz );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_VS( const unsigned int addr, const unsigned short n, const float val, const unsigned short nsize )
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "WriteCOMPOOL_VS (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "WriteCOMPOOL_VS (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "WriteCOMPOOL_VS (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "WriteCOMPOOL_VS (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VS ((addr + (nsize * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_VS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VS)
		throw std::exception( std::string( "WriteCOMPOOL_VS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((n - 1) * 2), &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_VS( const unsigned int addr, const VECTOR3& val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 6) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VS ((addr + 6) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_VS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VS)
		throw std::exception( std::string( "WriteCOMPOOL_VS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;

	tmp = static_cast<float>(val.x);
	memcpy( SimpleCOMPOOL + addr, &tmp, 4 );
	tmp = static_cast<float>(val.y);
	memcpy( SimpleCOMPOOL + addr + 2, &tmp, 4 );
	tmp = static_cast<float>(val.z);
	memcpy( SimpleCOMPOOL + addr + 4, &tmp, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_VD( const unsigned int addr, const unsigned short n, const double val, const unsigned short nsize )
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "WriteCOMPOOL_VD (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "WriteCOMPOOL_VD (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "WriteCOMPOOL_VD (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "WriteCOMPOOL_VD (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VD ((addr + (nsize * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_VD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VD)
		throw std::exception( std::string( "WriteCOMPOOL_VD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((n - 1) * 4), &val, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_VD( const unsigned int addr, const VECTOR3& val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 12) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_VD ((addr + 12) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_VD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_VD)
		throw std::exception( std::string( "WriteCOMPOOL_VD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr, &val.x, 8 );
	memcpy( SimpleCOMPOOL + addr + 4, &val.y, 8 );
	memcpy( SimpleCOMPOOL + addr + 8, &val.z, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_MS( const unsigned int addr, const unsigned short m, const unsigned short n, const float val, const unsigned short msize, const unsigned short nsize )
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "WriteCOMPOOL_MS (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "WriteCOMPOOL_MS (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "WriteCOMPOOL_MS (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "WriteCOMPOOL_MS (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (m == 0)
		throw std::exception( std::string( "WriteCOMPOOL_MS (m == 0) " + std::to_string( addr ) ).c_str() );
	if (msize < 2)
		throw std::exception( std::string( "WriteCOMPOOL_MS (msize < 2) " + std::to_string( addr ) ).c_str() );
	if (msize > 64)
		throw std::exception( std::string( "WriteCOMPOOL_MS (msize > 64) " + std::to_string( addr ) ).c_str() );
	if (m > msize)
		throw std::exception( std::string( "WriteCOMPOOL_MS (m > msize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * msize * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MS ((addr + (nsize * msize * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_MS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MS)
		throw std::exception( std::string( "WriteCOMPOOL_MS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((m - 1) * nsize) + (n - 1)) * 2), &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_MS( const unsigned int addr, const MATRIX3& val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 18) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MS ((addr + 18) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_MS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MS)
		throw std::exception( std::string( "WriteCOMPOOL_MS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	float tmp = 0.0f;

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
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_MD( const unsigned int addr, const unsigned short m, const unsigned short n, const double val, const unsigned short msize, const unsigned short nsize )
{
#ifdef CHECKS_ADDR
	// address checks
	if (n == 0)
		throw std::exception( std::string( "WriteCOMPOOL_MD (n == 0) " + std::to_string( addr ) ).c_str() );
	if (nsize < 2)
		throw std::exception( std::string( "WriteCOMPOOL_MD (nsize < 2) " + std::to_string( addr ) ).c_str() );
	if (nsize > 64)
		throw std::exception( std::string( "WriteCOMPOOL_MD (nsize > 64) " + std::to_string( addr ) ).c_str() );
	if (n > nsize)
		throw std::exception( std::string( "WriteCOMPOOL_MD (n > nsize) " + std::to_string( addr ) ).c_str() );
	if (m == 0)
		throw std::exception( std::string( "WriteCOMPOOL_MD (m == 0) " + std::to_string( addr ) ).c_str() );
	if (msize < 2)
		throw std::exception( std::string( "WriteCOMPOOL_MD (msize < 2) " + std::to_string( addr ) ).c_str() );
	if (msize > 64)
		throw std::exception( std::string( "WriteCOMPOOL_MD (msize > 64) " + std::to_string( addr ) ).c_str() );
	if (m > msize)
		throw std::exception( std::string( "WriteCOMPOOL_MD (m > msize) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (nsize * msize * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MD ((addr + (nsize * msize * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_MD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MD)
		throw std::exception( std::string( "WriteCOMPOOL_MD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((m - 1) * nsize) + (n - 1)) * 4), &val, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_MD( const unsigned int addr, const MATRIX3& val )
{
#ifdef CHECKS_ADDR
	// address checks
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + 36) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_MD ((addr + 36) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_MD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_MD)
		throw std::exception( std::string( "WriteCOMPOOL_MD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr, &val.m11, 8 );
	memcpy( SimpleCOMPOOL + addr + 4, &val.m12, 8 );
	memcpy( SimpleCOMPOOL + addr + 8, &val.m13, 8 );

	memcpy( SimpleCOMPOOL + addr + 12, &val.m21, 8 );
	memcpy( SimpleCOMPOOL + addr + 16, &val.m22, 8 );
	memcpy( SimpleCOMPOOL + addr + 20, &val.m23, 8 );

	memcpy( SimpleCOMPOOL + addr + 24, &val.m31, 8 );
	memcpy( SimpleCOMPOOL + addr + 28, &val.m32, 8 );
	memcpy( SimpleCOMPOOL + addr + 32, &val.m33, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_STRUCT( const unsigned int addr, const void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt )
{
#ifdef CHECKS_ADDR
	// address checks
	if (strct == 0)
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT (strct == 0) " + std::to_string( addr ) ).c_str() );
	if (sizes == 0)
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT (sizes == 0) " + std::to_string( addr ) ).c_str() );
	if (pos == 0)
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT (pos == 0) " + std::to_string( addr ) ).c_str() );
	if (elcnt == 0)
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT (elcnt == 0) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_STRUCT)
		throw std::exception( std::string( "WriteCOMPOOL_STRUCT wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	int offset = 0;// [byte]

	for (unsigned short i = 0; i < elcnt; i++)
	{
		memcpy( (char*)SimpleCOMPOOL + (addr * 2) + offset, (const char*)strct + pos[i], sizes[i] );

		offset += sizes[i];
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_ASS( const unsigned int addr, const unsigned short idx, float val, const unsigned short size )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASS (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "WriteCOMPOOL_ASS (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_ASS (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "WriteCOMPOOL_ASS (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ASS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ASS ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_ASS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ASS)
		throw std::exception( std::string( "WriteCOMPOOL_ASS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((idx - 1) * 2), &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_ASD( const unsigned int addr, const unsigned short idx, const double val, const unsigned short size )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASD (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "WriteCOMPOOL_ASD (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_ASD (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "WriteCOMPOOL_ASD (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ASD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ASD ((addr + (size * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_ASD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ASD)
		throw std::exception( std::string( "WriteCOMPOOL_ASD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((idx - 1) * 4), &val, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_AIS( const unsigned int addr, const unsigned short idx, const unsigned short val, const unsigned short size )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "WriteCOMPOOL_AIS (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "WriteCOMPOOL_AIS (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_AIS (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "WriteCOMPOOL_AIS (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_AIS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + size) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_AIS ((addr + size) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_AIS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_AIS)
		throw std::exception( std::string( "WriteCOMPOOL_AIS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + idx - 1, &val, 2 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_AID( const unsigned int addr, const unsigned short idx, const unsigned int val, const unsigned short size )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "WriteCOMPOOL_AID (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "WriteCOMPOOL_AID (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_AID (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "WriteCOMPOOL_AID (idx > size) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_AID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_AID ((addr + (size * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_AID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_AID)
		throw std::exception( std::string( "WriteCOMPOOL_AID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((idx - 1) * 2), &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_AC( const unsigned int addr, const unsigned short idx, const char* val, const unsigned short size_a, const unsigned short size_c )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "WriteCOMPOOL_AC (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size_c == 0)
		throw std::exception( std::string( "WriteCOMPOOL_AC (size_c == 0) " + std::to_string( addr ) ).c_str() );
	if (size_c > 255)
		throw std::exception( std::string( "WriteCOMPOOL_AC (size_c > 255) " + std::to_string( addr ) ).c_str() );
	if (size_a < 2)
		throw std::exception( std::string( "WriteCOMPOOL_AC (size_a < 2) " + std::to_string( addr ) ).c_str() );
	if (size_a > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_AC (size_a > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size_a)
		throw std::exception( std::string( "WriteCOMPOOL_AC (idx > size_a) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_AC (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size_a * ((size_c + 1) / 2))) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_AC ((addr + (size_a * ((size_c + 1) / 2))) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_AC type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_AC)
		throw std::exception( std::string( "WriteCOMPOOL_AC wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	size_t sz = min(strlen( val ), size_c);
	memcpy( (char*)SimpleCOMPOOL + (addr * 2) + ((idx - 1) * size_c), val, sz );
	return;
}

// TODO AVS

// TODO AVD

// TODO AMS

// TODO AMD

void SimpleGPCSystem::WriteCOMPOOL_ASTRUCT( const unsigned int addr, const unsigned short idx, const void* strct, const unsigned int* sizes, const unsigned int* pos, const unsigned short elcnt, const unsigned short size )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (idx == 0) " + std::to_string( addr ) ).c_str() );
	if (size < 2)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (size < 2) " + std::to_string( addr ) ).c_str() );
	if (size > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (size > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx > size)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (idx > size) " + std::to_string( addr ) ).c_str() );
	if (strct == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (strct == 0) " + std::to_string( addr ) ).c_str() );
	if (sizes == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (sizes == 0) " + std::to_string( addr ) ).c_str() );
	if (pos == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (pos == 0) " + std::to_string( addr ) ).c_str() );
	if (elcnt == 0)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (elcnt == 0) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_ASTRUCT)
		throw std::exception( std::string( "WriteCOMPOOL_ASTRUCT wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	int sum = 0;
	for (unsigned int i = 0; i < elcnt; i++) sum += sizes[i];
	int itempos = sum * (idx - 1);

	int offset = 0;// [byte]

	for (size_t i = 0; i < elcnt; i++)
	{
		memcpy( (char*)SimpleCOMPOOL + (addr * 2) + offset + itempos, (const char*)strct + pos[i], sizes[i] );

		offset += sizes[i];
	}
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A2SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const float val, const unsigned short size1, const unsigned short size2 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A2SS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2SS)
		throw std::exception( std::string( "WriteCOMPOOL_A2SS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((idx1 - 1) * size2) + (idx2 - 1)) * 2), &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A2SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const double val, const unsigned short size1, const unsigned short size2 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD ((addr + (size1 * size2 * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A2SD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2SD)
		throw std::exception( std::string( "WriteCOMPOOL_A2SD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((idx1 - 1) * size2) + (idx2 - 1)) * 4), &val, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A2IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short val, const unsigned short size1, const unsigned short size2 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS ((addr + (size1 * size2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A2IS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2IS)
		throw std::exception( std::string( "WriteCOMPOOL_A2IS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((idx1 - 1) * size2) + (idx2 - 1), &val, 2 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A2ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned int val, const unsigned short size1, const unsigned short size2 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID ((addr + (size1 * size2 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A2ID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A2ID)
		throw std::exception( std::string( "WriteCOMPOOL_A2ID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((idx1 - 1) * size2) + (idx2 - 1)) * 2), &val, 4 );
	return;
}

// TODO AC2

// TODO AVS2

// TODO AVD2

// TODO AMS2

// TODO AMD2

// TODO ASTRUCT2

void SimpleGPCSystem::WriteCOMPOOL_A3SS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const float val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A3SS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3SS)
		throw std::exception( std::string( "WriteCOMPOOL_A3SS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)) * 2), &val, 4 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A3SD( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const double val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3 * 4)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD ((addr + (size1 * size2 * size3 * 4)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A3SD type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3SD)
		throw std::exception( std::string( "WriteCOMPOOL_A3SD wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)) * 4), &val, 8 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A3IS( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned short val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS ((addr + (size1 * size2 * size3)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A3IS type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3IS)
		throw std::exception( std::string( "WriteCOMPOOL_A3IS wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1), &val, 2 );
	return;
}

void SimpleGPCSystem::WriteCOMPOOL_A3ID( const unsigned int addr, const unsigned short idx1, const unsigned short idx2, const unsigned short idx3, const unsigned int val, const unsigned short size1, const unsigned short size2, const unsigned short size3 )
{
#ifdef CHECKS_ADDR
	// address checks
	if (idx1 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (idx1 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx2 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (idx2 == 0) " + std::to_string( addr ) ).c_str() );
	if (idx3 == 0)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (idx3 == 0) " + std::to_string( addr ) ).c_str() );
	if (size1 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (size1 < 2) " + std::to_string( addr ) ).c_str() );
	if (size2 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (size2 < 2) " + std::to_string( addr ) ).c_str() );
	if (size3 < 2)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (size3 < 2) " + std::to_string( addr ) ).c_str() );
	if (size1 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (size1 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size2 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (size2 > 32767) " + std::to_string( addr ) ).c_str() );
	if (size3 > 32767)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (size3 > 32767) " + std::to_string( addr ) ).c_str() );
	if (idx1 > size1)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (idx1 > size1) " + std::to_string( addr ) ).c_str() );
	if (idx2 > size2)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (idx2 > size2) " + std::to_string( addr ) ).c_str() );
	if (idx3 > size3)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (idx3 > size3) " + std::to_string( addr ) ).c_str() );
	if (addr >= SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID (addr >= SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
	if ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID ((addr + (size1 * size2 * size3 * 2)) > SIMPLECOMPOOL_SIZE) " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_ADDR
#ifdef CHECKS_TYPE
	// type checks
	map<unsigned int, unsigned short>::const_iterator it = SCP_TYPE_CHECK_LIST.find( addr );
	if (it == SCP_TYPE_CHECK_LIST.end())
		throw std::exception( std::string( "WriteCOMPOOL_A3ID type not found " + std::to_string( addr ) ).c_str() );
	if (it->second != SCP_TYPE_A3ID)
		throw std::exception( std::string( "WriteCOMPOOL_A3ID wrong type " + std::to_string( addr ) ).c_str() );
#endif// CHECKS_TYPE

	memcpy( SimpleCOMPOOL + addr + ((((idx1 - 1) * size2 * size3) + ((idx2 - 1) * size3) + (idx3 - 1)) * 2), &val, 4 );
	return;
}

// TODO AC3

// TODO AVS3

// TODO AVD3

// TODO AMS3

// TODO AMD3

// TODO ASTRUCT3


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
	unsigned short itmp1 = 0;
	unsigned short itmp[16];
	double dtmp1 = 0;
	double dtmp[64];
	char ctmp[16];
	SCP_DISPCHAR dctmp[20];

	SimpleGPCSoftware::GetValILOAD( "H_DECAY", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 2, 1, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 1, 2, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_DECAY, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );


	/////////////////////////////////////////////////////////////

	SimpleGPCSoftware::GetValILOAD( "TVR_ROLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TVR_ROLL, static_cast<float>(dtmp1) );



	SimpleGPCSoftware::GetValILOAD( "H_K2", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_H_K2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_K2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_K2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_K2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "GR_DPY_ALT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GR_DPY_ALT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "V1_DASH_LINE", ILOADs, 2 * 4, dtmp );
	for (int i = 0; i < (2 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_V1_DASH_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 2, 4 );
	}

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
	WriteCOMPOOL_ASS( SCP_HMEP, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_HMEP, 2, static_cast<float>(dtmp[1]), 2 );

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
	WriteCOMPOOL_ASS( SCP_QBREF2, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_QBREF2, 2, static_cast<float>(dtmp[1]), 2 );

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
	WriteCOMPOOL_ASS( SCP_EMOHC1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_EMOHC1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "EMOHC2", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_EMOHC2, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_EMOHC2, 2, static_cast<float>(dtmp[1]), 2 );

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

	SimpleGPCSoftware::GetValILOAD( "K_CO_MAX", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_K_CO_MAX, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "EAS_SD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EAS_SD, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "WGT_SD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_WGT_SD, static_cast<float>(dtmp1) );



	SimpleGPCSoftware::GetValILOAD( "ACN1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ACN1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "AK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_AK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "AK1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_AK1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALFM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALFM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALMN1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALMN1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALMN2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALMN2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALMN3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALMN3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALMN4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALMN4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ASTART", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ASTART, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT6", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT6, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT7", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT7, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT8", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT8, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDDOT9", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDDOT9, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CDEQD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CDEQD, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CPMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CPMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CQDG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CQDG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CQG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CQG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CT16", ILOADs, 3, dtmp );
	WriteCOMPOOL_ASS( SCP_CT16, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_CT16, 2, static_cast<float>(dtmp[1]), 3 );
	WriteCOMPOOL_ASS( SCP_CT16, 3, static_cast<float>(dtmp[2]), 3 );

	SimpleGPCSoftware::GetValILOAD( "CT16MN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CT16MN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CT16MX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CT16MX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CT17", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_CT17, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_CT17, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "CT17MN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CT17MN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CT17MX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CT17MX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CUBIC_C3", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_CUBIC_C3, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_CUBIC_C3, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "CUBIC_C4", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_CUBIC_C4, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_CUBIC_C4, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "CY0", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CY0, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CY1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CY1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DDLIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DDLIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DEL_H1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DEL_H1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DEL_H2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DEL_H2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DEL_R_EMAX", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_DEL_R_EMAX, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_DEL_R_EMAX, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "DELV", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DELV, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DF, static_cast<float>(dtmp1) );

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

	SimpleGPCSoftware::GetValILOAD( "DRDDL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DRDDL, static_cast<float>(dtmp1) );

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

	SimpleGPCSoftware::GetValILOAD( "DT2MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DT2MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "D230", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_D230, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EDELC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EDELC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EDELC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EDELC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EDELNZ", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_EDELNZ, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_EDELNZ, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "EDRS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_EDRS, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_EDRS, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "EEF4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_EEF4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "EMEP_C1", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_EMEP_C1, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EMEP_C1, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EMEP_C1, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EMEP_C1, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EMEP_C2", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_EMEP_C2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EMEP_C2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EMEP_C2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EMEP_C2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EN_C1", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_EN_C1, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EN_C1, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EN_C1, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EN_C1, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EN_C2", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_EN_C2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EN_C2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EN_C2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_EN_C2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "EOW_SPT", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_EOW_SPT, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_EOW_SPT, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "ES1", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_ES1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_ES1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "ETRAN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ETRAN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_COEF1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GAMMA_COEF1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_COEF2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GAMMA_COEF2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GAMMA_REF_1", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_GAMMA_REF_1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_GAMMA_REF_1, 2, static_cast<float>(dtmp[1]), 2 );

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

	SimpleGPCSoftware::GetValILOAD( "GS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GS2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GS2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GS3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GS3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GS4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GS4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GYDOT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GYDOT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_CLOOP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_CLOOP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_ERROR_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_ERROR_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_FF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_FF, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_FLARE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_FLARE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_H_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_K, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_K, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_H_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "H_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_NO_ACC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_NO_ACC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_REF1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_REF1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_REF2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_REF2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_TD2_DOT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_TD2_DOT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_WL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_WL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HALI", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_HALI, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_HALI, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "HDREQG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HDREQG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HFTC", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_HFTC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_HFTC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "HSMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HSMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS01", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS01, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS02", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS02, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS03", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS03, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS11", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS11, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HS13", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HS13, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "LODMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LODMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PBGC", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_PBGC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_PBGC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBHC", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_PBHC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_PBHC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBRC", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_PBRC, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_PBRC, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "PBRCQ", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_PBRCQ, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_PBRCQ, 2, static_cast<float>(dtmp[1]), 2 );

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

	SimpleGPCSoftware::GetValILOAD( "PREBNK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PREBNK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "P2TRNC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_P2TRNC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QB_ERROR2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QB_ERROR2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBARDL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBARDL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBC1", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_QBC1, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_QBC1, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBC2", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_QBC2, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_QBC2, 2, static_cast<float>(dtmp[1]), 2 );

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
	WriteCOMPOOL_ASS( SCP_QBRLL, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_QBRLL, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBRML", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_QBRML, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_QBRML, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "QBRUL", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_QBRUL, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_QBRUL, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "R", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_R_AL, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_R_AL, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_R_AL, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_R_AL, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "RERRLM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RERRLM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RFTC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RFTC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RMEPMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RMEPMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RMINST", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_RMINST, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_RMINST, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "RPT1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RPT1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SIGMA", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_SIGMA, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_SIGMA, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "TGGS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_TGGS, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_TGGS, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "V_REF", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_V_REF, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_V_REF, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "VA", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VA, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VA1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VA1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VA2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VA2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VB1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VB1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VC16", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VC16, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VELMN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VELMN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VEROLC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VEROLC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VHS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VHS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VHS2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VHS2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VQ", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VQ, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VRDT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VRDT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VTRAN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VTRAN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VYLMAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VYLMAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "WT_GS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_WT_GS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_AIM_PT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_AIM_PT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_EXP", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_X_EXP, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_X_EXP, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_X_EXP, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_X_EXP, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_K", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_X_K, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_X_K, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_X_K, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_X_K, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "X_ZERO", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_X_ZERO, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_X_ZERO, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "XA", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_XA, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_XA, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "Y_LIMIT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y_LIMIT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y_RANGE1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y_RANGE1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y_RANGE2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y_RANGE2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YERRLM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YERRLM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YLMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YLMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YLMN2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YLMN2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ZK1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ZK1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RLMC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RLMC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RLMC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RLMC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RLMC3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RLMC3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RLMC4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RLMC4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RLMC5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RLMC5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RLMC6", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RLMC6, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VRLMC", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VRLMC, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DLRDTM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DLRDTM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "Y3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_Y3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CRDEAF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CRDEAF, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C17MP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C17MP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CT17M2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CT17M2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DLALLM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DLALLM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DLAPLM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DLAPLM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C21", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C21, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C22", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C22, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C23", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C23, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C24", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C24, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C25", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C25, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "C27", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_C27, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VALMOD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VALMOD, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VC20", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VC20, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VNOALP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VNOALP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DDMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DDMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RDMAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RDMAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBAR_WRAP_LOW", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_WRAP_LOW, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBAR_WRAP_HIGH", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_WRAP_HIGH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "KMAX_ABT", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_KMAX_ABT, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "KMAX_NOM", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_KMAX_NOM, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "DNWC_LIM", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DNWC_LIM, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DSB_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DSB_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GDQ_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GDQ_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GDQ_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GDQ_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "LOAD_RELIEF_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LOAD_RELIEF_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TDSBCOM", ILOADs, 8, dtmp );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 1, 1, static_cast<float>(dtmp[0]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 1, 2, static_cast<float>(dtmp[1]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 2, 1, static_cast<float>(dtmp[2]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 2, 2, static_cast<float>(dtmp[3]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 3, 1, static_cast<float>(dtmp[4]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 3, 2, static_cast<float>(dtmp[5]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 4, 1, static_cast<float>(dtmp[6]), 4, 2 );
	WriteCOMPOOL_A2SS( SCP_TDSBCOM, 4, 2, static_cast<float>(dtmp[7]), 4, 2 );

	SimpleGPCSoftware::GetValILOAD( "TIDELAY", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_TIDELAY, itmp1 );

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

	SimpleGPCSoftware::GetValILOAD( "TIDELAY5", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_TIDELAY5, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "PERR_DB5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PERR_DB5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GP_INTUP5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GP_INTUP5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "GP_INTDN5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_GP_INTDN5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PINT_LIM5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PINT_LIM5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TIDELAYC", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_TIDELAYC, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "ALT_HEAT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALT_HEAT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MET_HEAT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MET_HEAT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DOWN_DELAY", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_DOWN_DELAY, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "DB1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DB1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DB2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DB2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DPHYS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DPHYS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DPHYS2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DPHYS2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DRHYS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DRHYS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DRHYS2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DRHYS2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DYHYS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DYHYS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DYHYS2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DYHYS2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DB3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DB3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RHC_PTCH_DNMD_THLD_LREL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RHC_PTCH_DNMD_THLD_LREL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RHC_PTCH_DNMD_THLD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RHC_PTCH_DNMD_THLD, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RHC_RY_DNMD_THLD", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RHC_RY_DNMD_THLD, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CPRESS", ILOADs, 3, dtmp );
	WriteCOMPOOL_ASS( SCP_CPRESS, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_CPRESS, 2, static_cast<float>(dtmp[1]), 3 );
	WriteCOMPOOL_ASS( SCP_CPRESS, 3, static_cast<float>(dtmp[2]), 3 );

	SimpleGPCSoftware::GetValILOAD( "C1_OMS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_C1_OMS, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_C1_OMS, 2, static_cast<float>(dtmp[1]), 3 );
	// idx 3 not I-Load

	SimpleGPCSoftware::GetValILOAD( "C2_OMS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_C2_OMS, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_C2_OMS, 2, static_cast<float>(dtmp[1]), 3 );
	// idx 3 not I-Load

	SimpleGPCSoftware::GetValILOAD( "DTIG_OMS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_DTIG_OMS, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_DTIG_OMS, 2, static_cast<float>(dtmp[1]), 3 );
	// idx 3 not I-Load

	SimpleGPCSoftware::GetValILOAD( "HTGT_OMS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_HTGT_OMS, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_HTGT_OMS, 2, static_cast<float>(dtmp[1]), 3 );
	// idx 3 not I-Load

	SimpleGPCSoftware::GetValILOAD( "KMIN", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_KMIN, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "MASS_LOW_LEVEL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MASS_LOW_LEVEL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PHI_2STG", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PHI_2STG, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QPOLY", ILOADs, 4, dtmp );
	WriteCOMPOOL_ASS( SCP_QPOLY, 1, static_cast<float>(dtmp[0]), 4 );
	WriteCOMPOOL_ASS( SCP_QPOLY, 2, static_cast<float>(dtmp[1]), 4 );
	WriteCOMPOOL_ASS( SCP_QPOLY, 3, static_cast<float>(dtmp[2]), 4 );
	WriteCOMPOOL_ASS( SCP_QPOLY, 4, static_cast<float>(dtmp[3]), 4 );

	SimpleGPCSoftware::GetValILOAD( "THETA_OMS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_THETA_OMS, 1, static_cast<float>(dtmp[0]), 3 );
	WriteCOMPOOL_ASS( SCP_THETA_OMS, 2, static_cast<float>(dtmp[1]), 3 );
	// idx 3 not I-Load

	SimpleGPCSoftware::GetValILOAD( "THROT", ILOADs, 4, itmp );
	WriteCOMPOOL_AIS( SCP_THROT, 1, itmp[0], 4 );
	WriteCOMPOOL_AIS( SCP_THROT, 2, itmp[1], 4 );
	WriteCOMPOOL_AIS( SCP_THROT, 3, itmp[2], 4 );
	WriteCOMPOOL_AIS( SCP_THROT, 4, itmp[3], 4 );

	SimpleGPCSoftware::GetValILOAD( "V_RHO_PHI", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_V_RHO_PHI, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "X_NEP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_X_NEP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_BLANK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_BLANK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HERROR_NO_DIV", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_HERROR_NO_DIV, itmp1 );

	memset( ctmp, 0, 16 );
	SimpleGPCSoftware::GetValILOAD( "HERROR_SC1_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_HERROR_SC1_LABEL, ctmp, 4 );

	memset( ctmp, 0, 16 );
	SimpleGPCSoftware::GetValILOAD( "HERROR_SC2_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_HERROR_SC2_LABEL, ctmp, 4 );

	SimpleGPCSoftware::GetValILOAD( "HIGH_RATE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HIGH_RATE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HIGH_RATE_305603", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HIGH_RATE_305603, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLL_STOW_DELAY_TIME", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_ROLL_STOW_DELAY_TIME, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "UNSTOW_DELAY_TIME", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_UNSTOW_DELAY_TIME, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "LOW_RATE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LOW_RATE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "LOW_RATE_305603", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LOW_RATE_305603, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MED_RATE", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MED_RATE, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TGO_DISPLAY_CHAR", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TGO_DISPLAY_CHAR, static_cast<float>(dtmp1) );

	memset( ctmp, 0, 16 );
	SimpleGPCSoftware::GetValILOAD( "TGO_LABEL", ILOADs, 5, ctmp );
	WriteCOMPOOL_C( SCP_TGO_LABEL, ctmp, 5 );

	SimpleGPCSoftware::GetValILOAD( "TGO_TICK_MARK", ILOADs, 5, dtmp );
	WriteCOMPOOL_ASS( SCP_TGO_TICK_MARK, 1, static_cast<float>(dtmp[0]), 5 );
	WriteCOMPOOL_ASS( SCP_TGO_TICK_MARK, 2, static_cast<float>(dtmp[1]), 5 );
	WriteCOMPOOL_ASS( SCP_TGO_TICK_MARK, 3, static_cast<float>(dtmp[2]), 5 );
	WriteCOMPOOL_ASS( SCP_TGO_TICK_MARK, 4, static_cast<float>(dtmp[3]), 5 );
	WriteCOMPOOL_ASS( SCP_TGO_TICK_MARK, 5, static_cast<float>(dtmp[4]), 5 );

	memset( ctmp, 0, 16 );
	SimpleGPCSoftware::GetValILOAD( "RERRC_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_RERRC_LABEL, ctmp, 4 );

	memset( ctmp, 0, 16 );
	SimpleGPCSoftware::GetValILOAD( "YSC_LABEL", ILOADs, 4, ctmp );
	WriteCOMPOOL_C( SCP_YSC_LABEL, ctmp, 4 );

	SimpleGPCSoftware::GetValILOAD( "DISPLAY_OPTION", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_DISPLAY_OPTION, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "XTRACK_NO_DIV", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_XTRACK_NO_DIV, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "AL_SCALE_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_AL_SCALE_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_H_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_H_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_H_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_H_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_V_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_V_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_V_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_V_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_X_BIAS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_X_BIAS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_X_SC_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_X_SC_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_Y_BIAS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_Y_BIAS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A1_Y_SC_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A1_Y_SC_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_H_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_H_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_H_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_H_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_V_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_V_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_V_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_V_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_VI_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_VI_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_VI_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_VI_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_X_BIAS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_X_BIAS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_X_SC_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_X_SC_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_X2_BIAS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_X2_BIAS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_X2_SC_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_X2_SC_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_Y_BIAS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_Y_BIAS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "A2_Y_SC_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_A2_Y_SC_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "D_SCALE_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_D_SCALE_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DXS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DXS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DYS", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DYS, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "E_G_X_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_E_G_X_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "E_G_X_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_E_G_X_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "E_G_Y_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_E_G_Y_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "E_S_Y_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_E_S_Y_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "E_S_Y_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_E_S_Y_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HBIAS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_HBIAS, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_HBIAS, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "HC0", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_HC0, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

	SimpleGPCSoftware::GetValILOAD( "HC1", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_HC1, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

	SimpleGPCSoftware::GetValILOAD( "HC2", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_HC2, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

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

	SimpleGPCSoftware::GetValILOAD( "HSWITCH", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HSWITCH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "INIT_AL_VAL", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_INIT_AL_VAL, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

	SimpleGPCSoftware::GetValILOAD( "NUM_MAX", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_NUM_MAX, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "QBAR_PITCH", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_PITCH, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBAR_ROLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_ROLL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "QBAR_SAT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_QBAR_SAT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RBIAS", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_RBIAS, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_RBIAS, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "RT1_ALT_VS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RT1_ALT_VS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "RT1_RNG_VS1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RT1_RNG_VS1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SCALE_LEN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_SCALE_LEN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VC0", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_VC0, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

	SimpleGPCSoftware::GetValILOAD( "VS_X_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VS_X_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VS_Y_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VS_Y_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "XSCALE", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_XSCALE, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_XSCALE, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "YSCALE", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_YSCALE, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_YSCALE, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "RMINST_DIP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RMINST_DIP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YMAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YMAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YMEP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YMEP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "YMIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_YMIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HSWITCH2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_HSWITCH2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "PH_SCALE_FACT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_PH_SCALE_FACT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "P_S_X_MIN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_P_S_X_MIN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "P_S_X_MAX", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_P_S_X_MAX, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VC1", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_VC1, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

	SimpleGPCSoftware::GetValILOAD( "VC2", ILOADs, 5, dtmp );
	for (int i = 0; i < 5; i++)
	{
		WriteCOMPOOL_ASS( SCP_VC2, i + 1, static_cast<float>(dtmp[i]), 5 );
	}

	SimpleGPCSoftware::GetValILOAD( "VROLF1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VROLF1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VROLF2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VROLF2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VROLF3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VROLF3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF6", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF6, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF7", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF7, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ROLRF8", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ROLRF8, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VC1_PHU", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VC1_PHU, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VC2_PHU", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VC2_PHU, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DC1", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DC1, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DC2", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DC2, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DC3", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DC3, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DC4", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DC4, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DC5", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DC5, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "V_TEST", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_V_TEST, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "H_SCAL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_H_SCAL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "K16", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_K16, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "K17", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_K17, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "I_TRAN", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_I_TRAN, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "A1_CHAR_STRING", ILOADs, 8, dctmp );
	for (int i = 0; i < 8; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_A1_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 8 );
	}

	SimpleGPCSoftware::GetValILOAD( "A1_SOLID_LINE", ILOADs, 7 * 4, dtmp );
	for (int i = 0; i < (7 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_A1_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 7, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "A2_CHAR_STRING", ILOADs, 7, dctmp );
	for (int i = 0; i < 7; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_A2_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 7 );
	}

	SimpleGPCSoftware::GetValILOAD( "A2_SOLID_LINE", ILOADs, 13 * 4, dtmp );
	for (int i = 0; i < (13 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_A2_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 13, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "WRAP_MODE_INIT", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_WRAP_MODE_INIT, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "E1_CHAR_STRING", ILOADs, 17, dctmp );
	for (int i = 0; i < 17; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_E1_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 17 );
	}

	SimpleGPCSoftware::GetValILOAD( "E1_DASH_LINE", ILOADs, 14 * 4, dtmp );
	for (int i = 0; i < (14 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E1_DASH_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 14, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E1_SOLID_LINE", ILOADs, 12 * 4, dtmp );
	for (int i = 0; i < (12 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E1_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 12, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E2_CHAR_STRING", ILOADs, 15, dctmp );
	for (int i = 0; i < 15; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_E2_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 15 );
	}

	SimpleGPCSoftware::GetValILOAD( "E2_DASH_LINE", ILOADs, 6 * 4, dtmp );
	for (int i = 0; i < (6 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E2_DASH_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 6, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E2_SOLID_LINE", ILOADs, 9 * 4, dtmp );
	for (int i = 0; i < (9 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E2_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 9, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E3_CHAR_STRING", ILOADs, 13, dctmp );
	for (int i = 0; i < 13; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_E3_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 13 );
	}

	SimpleGPCSoftware::GetValILOAD( "E3_DASH_LINE", ILOADs, 3 * 4, dtmp );
	for (int i = 0; i < (3 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E3_DASH_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 3, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E3_SOLID_LINE", ILOADs, 9 * 4, dtmp );
	for (int i = 0; i < (9 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E3_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 9, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E4_CHAR_STRING", ILOADs, 13, dctmp );
	for (int i = 0; i < 13; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_E4_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 13 );
	}

	SimpleGPCSoftware::GetValILOAD( "E4_DASH_LINE", ILOADs, 10 * 4, dtmp );
	for (int i = 0; i < (10 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E4_DASH_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 10, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E4_SOLID_LINE", ILOADs, 9 * 4, dtmp );
	for (int i = 0; i < (9 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E4_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 9, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E5_CHAR_STRING", ILOADs, 14, dctmp );
	for (int i = 0; i < 14; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_E5_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 14 );
	}

	SimpleGPCSoftware::GetValILOAD( "E5_DASH_LINE", ILOADs, 10 * 4, dtmp );
	for (int i = 0; i < (10 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E5_DASH_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 10, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "E5_SOLID_LINE", ILOADs, 14 * 4, dtmp );
	for (int i = 0; i < (14 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_E5_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 14, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "V1_CHAR_STRING", ILOADs, 7, dctmp );
	for (int i = 0; i < 7; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_V1_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 7 );
	}

	SimpleGPCSoftware::GetValILOAD( "V1_SOLID_LINE", ILOADs, 10 * 4, dtmp );
	for (int i = 0; i < (10 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_V1_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 10, 4 );
	}

	SimpleGPCSoftware::GetValILOAD( "V2_CHAR_STRING", ILOADs, 7, dctmp );
	for (int i = 0; i < 7; i++)
	{
		WriteCOMPOOL_ASTRUCT( SCP_V2_CHAR_STRING, i + 1, &dctmp[i], sizes_DISPCHAR, pos_DISPCHAR, cnt_DISPCHAR, 7 );
	}

	SimpleGPCSoftware::GetValILOAD( "V2_SOLID_LINE", ILOADs, 6 * 4, dtmp );
	for (int i = 0; i < (6 * 4); i++)
	{
		WriteCOMPOOL_A2SS( SCP_V2_SOLID_LINE, (i / 4) + 1, (i % 4) + 1, static_cast<float>(dtmp[i]), 6, 4 );
	}

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

	SimpleGPCSoftware::GetValILOAD( "LPS_GO_FOR_AUTO_SEQ_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_LPS_GO_FOR_AUTO_SEQ_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SRB_IGN_ARM_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_SRB_IGN_ARM_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SRB_PIC_VOLTS_CHK_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_SRB_PIC_VOLTS_CHK_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "IMU_TO_INERTIAL_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_IMU_TO_INERTIAL_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "AUTO_RECYCLE_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_AUTO_RECYCLE_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "OPN_LO2_POGO_RECRC_VLV_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_OPN_LO2_POGO_RECRC_VLV_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "NAV_INIT_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_NAV_INIT_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CONFIG_VNT_DRS_FOR_LCH_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CONFIG_VNT_DRS_FOR_LCH_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CHK_MPS_VLVS_POS_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CHK_MPS_VLVS_POS_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CLSE_LO2_OVBD_BV_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CLSE_LO2_OVBD_BV_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "CHK_PREVLVS_OPN_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_CHK_PREVLVS_OPN_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "START_SSMES_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_START_SSMES_T, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ALL_ENG_PERCENT_CHB_PRS_CHK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ALL_ENG_PERCENT_CHB_PRS_CHK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ENG_PERCENT_CHB_PRS_FOR_GO", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ENG_PERCENT_CHB_PRS_FOR_GO, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ENG_TIMER_FOR_THRUST_OK", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ENG_TIMER_FOR_THRUST_OK, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VERIFY_ALL_ENG_SHTDN_TIMER", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VERIFY_ALL_ENG_SHTDN_TIMER, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ME1_LOX_PREVLV_CLSE_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ME1_LOX_PREVLV_CLSE_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ME2_LOX_PREVLV_CLSE_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ME2_LOX_PREVLV_CLSE_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ME3_LOX_PREVLV_CLSE_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_ME3_LOX_PREVLV_CLSE_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "SRB_IGN_TIME_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_SRB_IGN_TIME_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ME1_LH2_PREVLV_CLSE_T_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_ME1_LH2_PREVLV_CLSE_T_DELAY, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "ME2_LH2_PREVLV_CLSE_T_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_ME2_LH2_PREVLV_CLSE_T_DELAY, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "ME3_LH2_PREVLV_CLSE_T_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_ME3_LH2_PREVLV_CLSE_T_DELAY, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "SRB_SEP_BACKUP_CUE_T", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SRB_SEP_BACKUP_CUE_T, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "SRB_SEP_MODING_T_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SRB_SEP_MODING_T_DELAY, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "SRB_SEP_COMMAND_T_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_SRB_SEP_COMMAND_T_DELAY, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "BP_ROLL_RATE_LMT_CONSTANT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_BP_ROLL_RATE_LMT_CONSTANT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "BQ_PITCH_RATE_LMT_CONSTANT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_BQ_PITCH_RATE_LMT_CONSTANT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "BR_YAW_RATE_LMT_CONSTANT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_BR_YAW_RATE_LMT_CONSTANT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "DYNAMIC_PRS_LMT", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_DYNAMIC_PRS_LMT, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MAX_SRB_SEP_CUE_DIFRNTL", ILOADs, dtmp1 );
	WriteCOMPOOL_SD( SCP_MAX_SRB_SEP_CUE_DIFRNTL, dtmp1 );

	SimpleGPCSoftware::GetValILOAD( "SRB_IGN_PIC_LEVEL", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_SRB_IGN_PIC_LEVEL, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "FRF_CUTOFF_TIME_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_FRF_CUTOFF_TIME_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "FLT_CNTL_TVC_INIT_TIME_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_FLT_CNTL_TVC_INIT_TIME_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "FRF_THROTTLE_TO_92_TIME_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_FRF_THROTTLE_TO_92_TIME_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "FRF_THROTTLE_TO_100_TIME_DELAY", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_FRF_THROTTLE_TO_100_TIME_DELAY, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "FRF_TEST_FLAG", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_FRF_TEST_FLAG, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "MIN_ROLL_AZ_WARN", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MIN_ROLL_AZ_WARN, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "ENABLE_MEDS_DATA_TRANSFER", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_ENABLE_MEDS_DATA_TRANSFER, itmp1 );


	SimpleGPCSoftware::GetValILOAD( "TRANS_ROLL", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TRANS_ROLL, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "TRANS_YAW", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TRANS_YAW, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "MACH_RRXF", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_MACH_RRXF, static_cast<float>(dtmp1) );


	SimpleGPCSoftware::GetValILOAD( "RADIUS_EP", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_RADIUS_EP, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "KMAX_SECONDARY", ILOADs, itmp1 );
	WriteCOMPOOL_IS( SCP_KMAX_SECONDARY, itmp1 );

	SimpleGPCSoftware::GetValILOAD( "TAU_TD2F", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TAU_TD2F, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "HCLOOP2", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_HCLOOP2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HCLOOP2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HCLOOP2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HCLOOP2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "HDECAY2", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_HDECAY2, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HDECAY2, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HDECAY2, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HDECAY2, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "HEXP", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_HEXP, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HEXP, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HEXP, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_HEXP, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "XDECAY", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_XDECAY, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_XDECAY, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_XDECAY, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_XDECAY, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "RH", ILOADs, 4, dtmp );
	WriteCOMPOOL_A2SS( SCP_RH, 1, 1, static_cast<float>(dtmp[0]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_RH, 1, 2, static_cast<float>(dtmp[1]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_RH, 2, 1, static_cast<float>(dtmp[2]), 2, 2 );
	WriteCOMPOOL_A2SS( SCP_RH, 2, 2, static_cast<float>(dtmp[3]), 2, 2 );

	SimpleGPCSoftware::GetValILOAD( "SIGMAH", ILOADs, 2, dtmp );
	WriteCOMPOOL_ASS( SCP_SIGMAH, 1, static_cast<float>(dtmp[0]), 2 );
	WriteCOMPOOL_ASS( SCP_SIGMAH, 2, static_cast<float>(dtmp[1]), 2 );

	SimpleGPCSoftware::GetValILOAD( "TREF_ADJUST", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_TREF_ADJUST, static_cast<float>(dtmp1) );

	SimpleGPCSoftware::GetValILOAD( "VREF_ADJUST", ILOADs, dtmp1 );
	WriteCOMPOOL_SS( SCP_VREF_ADJUST, static_cast<float>(dtmp1) );

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
