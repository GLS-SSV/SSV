/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/07/02   GLS
2022/07/17   GLS
2022/07/24   GLS
2022/08/05   GLS
********************************************/
#include "PanelF7.h"
#include "MDU.h"
#include "StandardSwitch.h"
#include "StandardLight.h"
#include "7SegDisp_EventTime.h"
#include <discsignals.h>
#include "../Atlantis.h"
#include "../meshres_vc.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_f7.h"


namespace vc {

	PanelF7::PanelF7(Atlantis* _sts)
		: AtlantisPanel(_sts, "F7")
	{
		DefineMesh( MESHNAME_PANELF7 );

		Add(pCRT1 = new MDU(_sts, "CRT1", MDUID_CRT1));
		Add(pCRT2 = new MDU(_sts, "CRT2", MDUID_CRT2));
		Add(pCRT3 = new MDU(_sts, "CRT3", MDUID_CRT3));
		Add(pMFD1 = new MDU(_sts, "MFD1", MDUID_MFD1));
		Add(pMFD2 = new MDU(_sts, "MFD2", MDUID_MFD2));

		Add( pEventTime = new _7SegDisp_EventTime( _sts, "EVENT TIME" ) );

		Add( pCWLight[0] = new StandardSingleLight( _sts, "CW O2 PRESS" ) );
		Add( pCWLight[1] = new StandardSingleLight( _sts, "CW CABIN ATM" ) );
		Add( pCWLight[2] = new StandardSingleLight( _sts, "CW FREON LOOP" ) );
		Add( pCWLight[3] = new StandardSingleLight( _sts, "CW H2O LOOP" ) );
		Add( pCWLight[4] = new StandardSingleLight( _sts, "CW SPARE 5A" ) );
		Add( pCWLight[5] = new StandardSingleLight( _sts, "CW PAYLOAD WARNING" ) );
		Add( pCWLight[6] = new StandardSingleLight( _sts, "CW PAYLOAD CAUTION" ) );
		Add( pCWLight[7] = new StandardSingleLight( _sts, "CW BACKUP C/W ALARM" ) );

		Add( pCWLight[8] = new StandardSingleLight( _sts, "CW H2 PRESS" ) );
		Add( pCWLight[9] = new StandardSingleLight( _sts, "CW O2 HEATER TEMP" ) );
		Add( pCWLight[10] = new StandardSingleLight( _sts, "CW AV BAY/CABIN AIR" ) );
		Add( pCWLight[11] = new StandardSingleLight( _sts, "CW RGA/ACCEL" ) );
		Add( pCWLight[12] = new StandardSingleLight( _sts, "CW LEFT RHC" ) );
		Add( pCWLight[13] = new StandardSingleLight( _sts, "CW GPC" ) );
		Add( pCWLight[14] = new StandardSingleLight( _sts, "CW PRIMARY C/W" ) );
		Add( pCWLight[15] = new StandardSingleLight( _sts, "CW APU TEMP" ) );

		Add( pCWLight[16] = new StandardSingleLight( _sts, "CW FUEL CELL REAC" ) );
		Add( pCWLight[17] = new StandardSingleLight( _sts, "CW MAIN BUS UNDERVOLT" ) );
		Add( pCWLight[18] = new StandardSingleLight( _sts, "CW IMU" ) );
		Add( pCWLight[19] = new StandardSingleLight( _sts, "CW AIR DATA" ) );
		Add( pCWLight[20] = new StandardSingleLight( _sts, "CW RIGHT/AFT RHC" ) );
		Add( pCWLight[21] = new StandardSingleLight( _sts, "CW FCS SATURATION" ) );
		Add( pCWLight[22] = new StandardSingleLight( _sts, "CW FCS CHANNEL" ) );
		Add( pCWLight[23] = new StandardSingleLight( _sts, "CW APU OVERSPEED" ) );

		Add( pCWLight[24] = new StandardSingleLight( _sts, "CW FUEL CELL STACK TEMP" ) );
		Add( pCWLight[25] = new StandardSingleLight( _sts, "CW AC VOLTAGE" ) );
		Add( pCWLight[26] = new StandardSingleLight( _sts, "CW FWD RCS" ) );
		Add( pCWLight[27] = new StandardSingleLight( _sts, "CW LEFT RCS" ) );
		Add( pCWLight[28] = new StandardSingleLight( _sts, "CW LEFT OMS" ) );
		Add( pCWLight[29] = new StandardSingleLight( _sts, "CW OMS KIT" ) );
		Add( pCWLight[30] = new StandardSingleLight( _sts, "CW MPS" ) );
		Add( pCWLight[31] = new StandardSingleLight( _sts, "CW APU UNDERSPEED" ) );

		Add( pCWLight[32] = new StandardSingleLight( _sts, "CW FUEL CELL PUMP" ) );
		Add( pCWLight[33] = new StandardSingleLight( _sts, "CW AC OVERLOAD" ) );
		Add( pCWLight[34] = new StandardSingleLight( _sts, "CW RCS JET" ) );
		Add( pCWLight[35] = new StandardSingleLight( _sts, "CW RIGHT RCS" ) );
		Add( pCWLight[36] = new StandardSingleLight( _sts, "CW RIGHT OMS" ) );
		Add( pCWLight[37] = new StandardSingleLight( _sts, "CW OMS TVC" ) );
		Add( pCWLight[38] = new StandardSingleLight( _sts, "CW SPARE 7E" ) );
		Add( pCWLight[39] = new StandardSingleLight( _sts, "CW HYD PRESS" ) );

		Add( pMainEngStatus[0] = new StandardDoubleLight( _sts, "MAIN ENGINE STATUS CTR" ) );
		Add( pMainEngStatus[1] = new StandardDoubleLight( _sts, "MAIN ENGINE STATUS LEFT" ) );
		Add( pMainEngStatus[2] = new StandardDoubleLight( _sts, "MAIN ENGINE STATUS RIGHT" ) );

		Add( pSMAlert = new StandardSingleLight( _sts, "SM ALERT" ) );
	}

	PanelF7::~PanelF7()
	{
	}

	void PanelF7::DefineVC()
	{
		AddAIDToMouseEventList(AID_F7);

		pCRT1->DefineVCGroup( GRP_CRT1_F7_VC );
		pCRT1->DefineMaterial( MAT_MDU_CRT1_F7_VC );
		pCRT1->SetMouseRegion( AID_F7, 0.0f, 0.0f, 0.324694f, 0.490948f );

		pCRT2->DefineVCGroup( GRP_CRT2_F7_VC );
		pCRT2->DefineMaterial( MAT_MDU_CRT2_F7_VC );
		pCRT2->SetMouseRegion( AID_F7, 0.675193f, 0.0f, 1.0f, 0.490948f );

		pCRT3->DefineVCGroup( GRP_CRT3_F7_VC );
		pCRT3->DefineMaterial( MAT_MDU_CRT3_F7_VC );
		pCRT3->SetMouseRegion( AID_F7, 0.337995f, 0.257779f, 0.663350f, 0.750545f );

		pMFD1->DefineVCGroup( GRP_MFD1_F7_VC );
		pMFD1->DefineMaterial( MAT_MDU_MFD1_F7_VC );
		pMFD1->SetMouseRegion( AID_F7, 0.0f, 0.510035f, 0.324694f, 1.0f );

		pMFD2->DefineVCGroup( GRP_MFD2_F7_VC );
		pMFD2->DefineMaterial( MAT_MDU_MFD2_F7_VC );
		pMFD2->SetMouseRegion( AID_F7, 0.675193f, 0.510035f, 1.0f, 1.0f );

		pEventTime->DefineMesh( GetVCMeshIndex() );
		pEventTime->DefineComponent( GRP_EVENT_S1_F7_VC, true, false, false, _7SD_STATE_NUM0 );
		pEventTime->DefineComponent( GRP_EVENT_S10_F7_VC, true, false, false, _7SD_STATE_NUM0 );
		pEventTime->DefineComponent( GRP_EVENT_M1_F7_VC, true, false, false, _7SD_STATE_NUM0 );
		pEventTime->DefineComponent( GRP_EVENT_M10_F7_VC, true, false, false, _7SD_STATE_NUM0 );

		pCWLight[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_O2_PRESS_F7_VC );
		pCWLight[0]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_CABIN_ATM_F7_VC );
		pCWLight[1]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FREON_LOOP_F7_VC );
		pCWLight[2]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_H2O_LOOP_F7_VC );
		pCWLight[3]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_BLANK_F7_VC );
		pCWLight[4]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_PAYLOAD_WARNING_F7_VC );
		pCWLight[5]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_PAYLOAD_CAUTION_F7_VC );
		pCWLight[6]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_BACKUP_CW_ALARM_F7_VC );
		pCWLight[7]->SetStateOffset( 1, 0.0f, 0.177246f );

		pCWLight[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_H2_PRESS_F7_VC );
		pCWLight[8]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_O2_HEATER_TEMP_F7_VC );
		pCWLight[9]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_AV_BAY_CABIN_AIR_F7_VC );
		pCWLight[10]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[11]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_RGA_ACCEL_F7_VC );
		pCWLight[11]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[12]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_LEFT_RHC_F7_VC );
		pCWLight[12]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[13]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_GPC_F7_VC );
		pCWLight[13]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[14]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_PRIMARY_CW_F7_VC );
		pCWLight[14]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[15]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_APU_TEMP_F7_VC );
		pCWLight[15]->SetStateOffset( 1, 0.0f, 0.177246f );

		pCWLight[16]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FUEL_CELL_REAC_F7_VC );
		pCWLight[16]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[17]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_MAIN_BUS_UNDERVOLT_F7_VC );
		pCWLight[17]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[18]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_IMU_F7_VC );
		pCWLight[18]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[19]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_AIR_DATA_F7_VC );
		pCWLight[19]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[20]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_RIGHT_AFT_RHC_F7_VC );
		pCWLight[20]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[21]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FCS_SATURATION_F7_VC );
		pCWLight[21]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[22]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FCS_CHANNEL_F7_VC );
		pCWLight[22]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[23]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_APU_OVERSPEED_F7_VC );
		pCWLight[23]->SetStateOffset( 1, 0.0f, 0.177246f );

		pCWLight[24]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FUEL_CELL_STACK_TEMP_F7_VC );
		pCWLight[24]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[25]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_AC_VOLTAGE_F7_VC );
		pCWLight[25]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[26]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FWD_RCS_F7_VC );
		pCWLight[26]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[27]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_LEFT_RCS_F7_VC );
		pCWLight[27]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[28]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_LEFT_OMS_F7_VC );
		pCWLight[28]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[29]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_OMS_KIT_F7_VC );
		pCWLight[29]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[30]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_MPS_F7_VC );
		pCWLight[30]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[31]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_APU_UNDERSPEED_F7_VC );
		pCWLight[31]->SetStateOffset( 1, 0.0f, 0.177246f );

		pCWLight[32]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_FUEL_CELL_PUMP_F7_VC );
		pCWLight[32]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[33]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_AC_OVERLOAD_F7_VC );
		pCWLight[33]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[34]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_RCS_JET_F7_VC );
		pCWLight[34]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[35]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_RIGHT_RCS_F7_VC );
		pCWLight[35]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[36]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_RIGHT_OMS_F7_VC );
		pCWLight[36]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[37]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_OMS_TVC_F7_VC );
		pCWLight[37]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[38]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_BLANK2_F7_VC );
		pCWLight[38]->SetStateOffset( 1, 0.0f, 0.177246f );
		pCWLight[39]->DefineMeshGroup( GetVCMeshIndex(), GRP_CW_HYD_PRESS_F7_VC );
		pCWLight[39]->SetStateOffset( 1, 0.0f, 0.177246f );

		pMainEngStatus[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_F7_VC );
		pMainEngStatus[0]->SetStateOffset( 1, 0.120117f, 0.344727f );// R
		pMainEngStatus[0]->SetStateOffset( 2, 0.120117f, 0.478516f );// Y
		pMainEngStatus[0]->SetStateOffset( 3, 0.120117f, 0.619141f );// RY

		pMainEngStatus[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_F7_VC );
		pMainEngStatus[1]->SetStateOffset( 1, 0.120117f, 0.344727f );// R
		pMainEngStatus[1]->SetStateOffset( 2, 0.120117f, 0.478516f );// Y
		pMainEngStatus[1]->SetStateOffset( 3, 0.120117f, 0.619141f );// RY

		pMainEngStatus[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS3_F7_VC );
		pMainEngStatus[2]->SetStateOffset( 1, 0.120117f, 0.344727f );// R
		pMainEngStatus[2]->SetStateOffset( 2, 0.120117f, 0.478516f );// Y
		pMainEngStatus[2]->SetStateOffset( 3, 0.120117f, 0.619141f );// RY

		pSMAlert->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS4_F7_VC );
		pSMAlert->SetStateOffset( 1, 0.120117f, 0.619141f );
		return;
	}

	void PanelF7::RegisterVC()
	{
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea(AID_F7, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED);

		oapiVCSetAreaClickmode_Quadrilateral( AID_F7,
			_V( -0.3879, 2.4088, 14.7837 ) + ofs, _V( 0.385, 2.4088, 14.7837 ) + ofs,
			_V( -0.3879, 1.9679, 14.6604 ) + ofs, _V( 0.385, 1.9679, 14.6604 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelF7::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "CW_ANNUNCIATOR_A", 16 );
		for (int i = 0; i < 16; i++) lightcmd[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_ANNUNCIATOR_B", 16 );
		for (int i = 16; i < 32; i++) lightcmd[i].Connect( pBundle, i - 16 );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_ANNUNCIATOR_C", 16 );
		for (int i = 32; i < 40; i++) lightcmd[i].Connect( pBundle, i - 32 );

		pBundle = STS()->BundleManager()->CreateBundle( "F7LIGHTS_A", 16 );
		for (int i = 0; i < 16; i++)
		{
			pCWLight[i]->ConnectLight( 0, pBundle, i );
			lightoutput[i].Connect( pBundle, i );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "F7LIGHTS_B", 16 );
		for (int i = 16; i < 32; i++)
		{
			pCWLight[i]->ConnectLight( 0, pBundle, i - 16 );
			lightoutput[i].Connect( pBundle, i - 16 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "F7LIGHTS_C", 16 );
		for (int i = 32; i < 40; i++)
		{
			pCWLight[i]->ConnectLight( 0, pBundle, i - 32 );
			lightoutput[i].Connect( pBundle, i - 32 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "ACA", 16 );
		lighttestleft[0].Connect( pBundle, 6 );
		lighttestright[0].Connect( pBundle, 7 );
		lighttestleft[1].Connect( pBundle, 8 );
		lighttestright[1].Connect( pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_1", 16 );
		pMainEngStatus[1]->ConnectLight( 0, pBundle, 15 );
		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_2", 16 );
		pMainEngStatus[1]->ConnectLight( 2, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_4", 16 );
		pSMAlert->ConnectLight( 0, pBundle, 9 );
		pMainEngStatus[2]->ConnectLight( 0, pBundle, 15 );
		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_5", 16 );
		pMainEngStatus[2]->ConnectLight( 2, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_1", 16 );
		pMainEngStatus[0]->ConnectLight( 0, pBundle, 15 );
		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_2", 16 );
		pMainEngStatus[0]->ConnectLight( 2, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_4", 16 );
		pSMAlert->ConnectLight( 1, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdEventTimer_A", 16 );
		pEventTime->Mode_Test.Connect( pBundle, 0 );
		pEventTime->Mode_Up.Connect( pBundle, 1 );
		pEventTime->Control_Stop.Connect( pBundle, 2 );
		pEventTime->Control_Start.Connect( pBundle, 3 );
		pEventTime->Timer_Reset.Connect( pBundle, 4 );
		pEventTime->Timer_Set.Connect( pBundle, 5 );
		pEventTime->AbortReset.Connect( pBundle, 6 );
		pEventTime->LiftoffStart.Connect( pBundle, 7 );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdEventTimer_B", 16 );
		pEventTime->Seconds_1.Connect( pBundle, 0 );
		pEventTime->Seconds_2.Connect( pBundle, 1 );
		pEventTime->Seconds_4.Connect( pBundle, 2 );
		pEventTime->Seconds_8.Connect( pBundle, 3 );
		pEventTime->Seconds_10.Connect( pBundle, 4 );
		pEventTime->Seconds_20.Connect( pBundle, 5 );
		pEventTime->Seconds_40.Connect( pBundle, 6 );
		pEventTime->Minutes_1.Connect( pBundle, 7 );
		pEventTime->Minutes_2.Connect( pBundle, 8 );
		pEventTime->Minutes_4.Connect( pBundle, 9 );
		pEventTime->Minutes_8.Connect( pBundle, 10 );
		pEventTime->Minutes_10.Connect( pBundle, 11 );
		pEventTime->Minutes_20.Connect( pBundle, 12 );
		pEventTime->Minutes_40.Connect( pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_SW_2", 16 );
		modeascent.Connect( pBundle, 6 );
		modenorm.Connect( pBundle, 7 );
		mar[0].Connect( pBundle, 9 );
		mar[1].Connect( pBundle, 10 );
		AtlantisPanel::Realize();
	}

	void PanelF7::OnPostStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPostStep( simt, simdt, mjd );

		bool power = mar[0] || mar[1] || modenorm || modeascent;// TODO O13 CB
		bool testleft = lighttestleft[0].IsSet() || lighttestleft[1].IsSet();
		bool testright = lighttestright[0].IsSet() || lighttestright[1].IsSet();

		for (int i = 0; i < 20; i++)
		{
			lightoutput[i].SetLine( (int)(power && (lightcmd[i].IsSet() || testleft)) * 5.0f );
		}
		for (int i = 20; i < 40; i++)
		{
			lightoutput[i].SetLine( (int)(power && (lightcmd[i].IsSet() || testright)) * 5.0f );
		}
		return;
	}
};
