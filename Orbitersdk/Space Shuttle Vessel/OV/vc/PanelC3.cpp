/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/01   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/06/11   GLS
2021/06/18   GLS
2021/06/28   GLS
2021/06/30   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/01   GLS
2022/01/07   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/08/21   GLS
2022/09/29   GLS
********************************************/
#include "PanelC3.h"
#include "StandardSwitch.h"
#include "PushButtonIndicator.h"
#include "PushButton.h"
#include "StandardSwitchCover.h"
#include "vc_defs.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "../meshres_vc_c3.h"


namespace vc
{
	PanelC3::PanelC3( Atlantis *_sts, const std::string &orbiter ):AtlantisPanel(_sts, "C3"),
	hOV102Texture(NULL)
	{
		DefineMesh( MESHNAME_PANELC3 );

		if (orbiter == "Columbia") OV102 = true;
		else OV102 = false;

		char cbuf[5];

		for(int i=0;i<24;i++) {
			sprintf_s(cbuf, 5, "%d", i+1);
			std::string name="C3_PBI";
			name+=cbuf;
			Add(pPBIs[i]=new PushButtonIndicatorSingleLight(_sts, name));
		}

		Add(pOMSArm[LEFT] = new LockableLever3(_sts, "OMS ENG LEFT"));
		Add(pOMSArm[RIGHT] = new LockableLever3(_sts, "OMS ENG RIGHT"));

		Add( pBFCCRTDisplay = new StdSwitch2( _sts, "BFC CRT DISPLAY" ) );
		pBFCCRTDisplay->SetLabel( 0, "OFF" );
		pBFCCRTDisplay->SetLabel( 1, "ON" );

		Add( pBFCCRTSelect = new StdSwitch3( _sts, "BFC CRT SELECT" ) );
		pBFCCRTSelect->SetLabel( 0, "3+1" );
		pBFCCRTSelect->SetLabel( 1, "2+3" );
		pBFCCRTSelect->SetLabel( 2, "1+2" );

		Add(pAirDataProbeStow[LEFT] = new StdSwitch2(_sts, "AIR DATA PROBE STOW LEFT"));
		Add(pAirDataProbeStow[RIGHT] = new StdSwitch2(_sts, "AIR DATA PROBE STOW RIGHT"));
		Add(pAirDataProbe[LEFT] = new LockableLever3(_sts, "AIR DATA PROBE LEFT"));
		Add(pAirDataProbe[RIGHT] = new LockableLever3(_sts, "AIR DATA PROBE RIGHT"));

		for(int i=0;i<2;i++) {
			pOMSArm[i]->SetLabel(0, "OFF");
			pOMSArm[i]->SetLabel(1, "ARM/PRESS");
			pOMSArm[i]->SetLabel(2, "ARM");

			pAirDataProbeStow[i]->SetLabel(0, "INHIBIT");
			pAirDataProbeStow[i]->SetLabel(1, "ENABLE");

			pAirDataProbe[i]->SetLabel(0, "STOW");
			pAirDataProbe[i]->SetLabel(1, "DEPLOY");
			pAirDataProbe[i]->SetLabel(2, "DEPLOY/HEAT");
		}

		Add(pSSMELimitShutDn = new StdSwitch3(_sts, "MAIN ENGINE LIMIT SHUT DN"));
		pSSMELimitShutDn->SetLabel(0, "INHIBIT");
		pSSMELimitShutDn->SetLabel(1, "AUTO");
		pSSMELimitShutDn->SetLabel(2, "ENABLE");

		Add( pSSMESDPBCover[0] = new StandardSwitchCover( _sts, "MAIN ENGINE SHUT DOWN LEFT COVER" ) );
		Add( pSSMESDPBCover[1] = new StandardSwitchCover( _sts, "MAIN ENGINE SHUT DOWN CTR COVER" ) );
		Add( pSSMESDPBCover[2] = new StandardSwitchCover( _sts, "MAIN ENGINE SHUT DOWN RIGHT COVER" ) );
		Add( pSSMESDPB[0] = new PushButton( _sts, "MAIN ENGINE SHUT DOWN LEFT" ) );
		Add( pSSMESDPB[1] = new PushButton( _sts, "MAIN ENGINE SHUT DOWN CTR" ) );
		Add( pSSMESDPB[2] = new PushButton( _sts, "MAIN ENGINE SHUT DOWN RIGHT" ) );

		Add( pSRBSEPSW = new StdSwitch2( _sts, "SRB SEPARATION" ) );
		pSRBSEPSW->SetLabel( 0, "AUTO" );
		pSRBSEPSW->SetLabel( 1, "MAN/AUTO" );
		Add( pSRBSEPCover = new StandardSwitchCover( _sts, "SRB SEPARATION SEP COVER" ) );
		Add( pSRBSEPPB = new PushButton( _sts, "SRB SEPARATION SEP" ) );

		Add( pETSEPSW = new LockableLever2( _sts, "ET SEPARATION" ) );
		pETSEPSW->SetLabel( 0, "AUTO" );
		pETSEPSW->SetLabel( 1, "MAN" );
		Add( pETSEPCover = new StandardSwitchCover( _sts, "ET SEPARATION SEP COVER" ) );
		Add( pETSEPPB = new PushButton( _sts, "ET SEPARATION SEP" ) );

		Add( pBodyFlap = new LockableLever3( _sts, "BODY FLAP" ) );
		pBodyFlap->SetLabel( 0, "DOWN" );
		pBodyFlap->SetLabel( 1, "AUTO/OFF" );
		pBodyFlap->SetLabel( 2, "UP" );

		Add( pPitchTrim = new StdSwitch3( _sts, "PITCH TRIM" ) );
		pPitchTrim->SetLabel( 0, "DOWN" );
		pPitchTrim->SetLabel( 2, "UP" );

		Add( pRollTrim = new StdSwitch3( _sts, "ROLL TRIM" ) );
		pRollTrim->SetLabel( 0, "L" );
		pRollTrim->SetLabel( 2, "R" );

		Add( pYawTrim = new StdSwitch3( _sts, "YAW TRIM" ) );
		pYawTrim->SetLabel( 0, "L" );
		pYawTrim->SetLabel( 2, "R" );
	}

	PanelC3::~PanelC3()
	{
		if (hOV102Texture) oapiReleaseTexture( hOV102Texture );
	}

	void PanelC3::RegisterVC()
	{
		//oapiWriteLog("Registering Panel C3");
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_C3_HI_1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_HI_2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_HI_3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_HI_4, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_4, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_5, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_6, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		//oapiVCRegisterArea( AID_C3_LO_7, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCRegisterArea( AID_C3_LO_8, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_HI_1,// A1 bottom center
			_V( -0.070189, 1.755206, 14.237542 ) + ofs, _V( 0.035453, 1.755206, 14.237542 ) + ofs,
			_V( -0.070189, 1.747687, 14.166249 ) + ofs, _V( 0.035453, 1.747687, 14.166249 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_HI_2,// A6
			_V( -0.260118, 1.746585, 14.1557 ) + ofs, _V( -0.049054, 1.746585, 14.1557 ) + ofs,
			_V( -0.260118, 1.724292, 13.943507 ) + ofs, _V( -0.049054, 1.724292, 13.943507 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_HI_3,// A7 SRB PB
			_V( 0.015283, 1.744737, 14.138138 ) + ofs, _V( 0.046753, 1.744737, 14.138138 ) + ofs,
			_V( 0.015283, 1.738598, 14.079697 ) + ofs, _V( 0.046753, 1.738598, 14.079697 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_HI_4,// A7 ET PB
			_V( 0.102901, 1.744737, 14.138138 ) + ofs, _V( 0.134511, 1.744737, 14.138138 ) + ofs,
			_V( 0.102901, 1.738598, 14.079697 ) + ofs, _V( 0.134511, 1.738598, 14.079697 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_1,// A1 top half
			_V( -0.260118, 1.741757, 14.370776 ) + ofs, _V( 0.168355, 1.741757, 14.370776 ) + ofs,
			_V( -0.260118, 1.730074, 14.259899 ) + ofs, _V( 0.168355, 1.730074, 14.259899 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_2,// A1 bottom left
			_V( -0.236096, 1.727169, 14.2324 ) + ofs, _V( -0.077394, 1.727169, 14.2324 ) + ofs,
			_V( -0.236096, 1.722124, 14.18445 ) + ofs, _V( -0.077394, 1.722124, 14.18445 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_3,// A1 bottom right
			_V( 0.052127, 1.727129, 14.2322 ) + ofs, _V( 0.142307, 1.727129, 14.2322 ) + ofs,
			_V( 0.052127, 1.722179, 14.1849 ) + ofs, _V( 0.142307, 1.722179, 14.1849 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_4,// A7 SRB SW
			_V( -0.020578, 1.71674, 14.132641 ) + ofs, _V( 0.005583, 1.71674, 14.132641 ) + ofs,
			_V( -0.020578, 1.711311, 14.081262 ) + ofs, _V( 0.005583, 1.711311, 14.081262 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_5,// A7 ET SW
			_V( 0.069115, 1.71674, 14.132641 ) + ofs, _V( 0.097001, 1.71674, 14.132641 ) + ofs,
			_V( 0.069115, 1.70853, 14.055056 ) + ofs, _V( 0.097001, 1.70853, 14.055056 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_6,// A7 top right
			_V( 0.174504, 1.711389, 14.0824 ) + ofs, _V( 0.221737, 1.711389, 14.0824 ) + ofs,
			_V( 0.174504, 1.708229, 14.0522 ) + ofs, _V( 0.221737, 1.708229, 14.0522 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		/*oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_7,// A7 bottom
			_V( -0.019446, 1.705429, 14.025701 ) + ofs, _V( 0.223501, 1.705429, 14.025701 ) + ofs,
			_V( -0.019446, 1.699939, 13.9734 ) + ofs, _V( 0.223501, 1.699939, 13.9734 ) + _V( 0.001, 0.001, 0.001 ) + ofs );*/

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3_LO_8,// A5
			_V( -0.232258, 1.694329, 13.92 ) + ofs, _V( 0.225643, 1.694329, 13.92 ) + ofs,
			_V( -0.232258, 1.680539, 13.7888 ) + ofs, _V( 0.225643, 1.680539, 13.7888 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelC3::DefineVC()
	{
		const VECTOR3 switch_rot = _V( 1.0, 0.0, 0.0 );
		const VECTOR3 switch_rotV = _V( 0.0, 0.104528, 0.994522 );
		const VECTOR3 pull_dir = _V( 0.0, 0.994522, -0.104528 );
		const VECTOR3 push_dir = -pull_dir;

		//oapiWriteLog("PanelC3: DefineVC called");

		AddAIDToMouseEventList( AID_C3_HI_1 );
		AddAIDToMouseEventList( AID_C3_HI_2 );
		AddAIDToMouseEventList( AID_C3_HI_3 );
		AddAIDToMouseEventList( AID_C3_HI_4 );
		AddAIDToMouseEventList( AID_C3_LO_1 );
		AddAIDToMouseEventList( AID_C3_LO_2 );
		AddAIDToMouseEventList( AID_C3_LO_3 );
		AddAIDToMouseEventList( AID_C3_LO_4 );
		AddAIDToMouseEventList( AID_C3_LO_5 );
		AddAIDToMouseEventList( AID_C3_LO_6 );
		//AddAIDToMouseEventList( AID_C3_LO_7 );
		AddAIDToMouseEventList( AID_C3_LO_8 );

		for (int i = 0; i < 24; i++)
		{
			pPBIs[i]->SetStateOffset( 1, 0.0f, 0.488281f );
			pPBIs[i]->SetDirection( push_dir );
		}

		// switch number: original name (current name)
		pPBIs[0]->SetMouseRegion( AID_C3_HI_2, 0.130531f, 0.157721f, 0.236533f, 0.259544f );// S1: SELECT - A (SELECT - A)
		pPBIs[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S1_C3_VC );

		pPBIs[1]->SetMouseRegion( AID_C3_HI_2, 0.265553f, 0.157721f, 0.371038f, 0.259544f );// S2: SELECT - B (SELECT - B)
		pPBIs[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S2_C3_VC );

		pPBIs[2]->SetMouseRegion( AID_C3_HI_2, 0.404487f, 0.157721f, 0.508553f, 0.259544f );// S3: CONTROL - AUTO (CONTROL - AUTO)
		pPBIs[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S3_C3_VC );

		pPBIs[3]->SetMouseRegion( AID_C3_HI_2, 0.534905f, 0.157721f, 0.642836f, 0.259544f );// S4: CONTROL - MAN (CONTROL - INRTL)
		pPBIs[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S4_C3_VC );

		pPBIs[4]->SetMouseRegion( AID_C3_HI_2, 0.675070f, 0.157721f, 0.780736f, 0.259544f );// S5: RCS JETS - NORM (CONTROL - LVLH)
		pPBIs[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S5_C3_VC );

		pPBIs[5]->SetMouseRegion( AID_C3_HI_2, 0.807275f, 0.157721f, 0.913137f, 0.259544f );// S6: RCS JETS - VERN (CONTROL - FREE)
		pPBIs[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S6_C3_VC );

		pPBIs[6]->SetMouseRegion( AID_C3_HI_2, 0.130531f, 0.459441f, 0.236533f, 0.562329f );// S16: TRANSLATION X - HIGH ()
		pPBIs[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S16_C3_VC );

		pPBIs[7]->SetMouseRegion( AID_C3_HI_2, 0.265553f, 0.459441f, 0.371038f, 0.562329f );// S17: TRANSLATION Y - HIGH (TRANSLATION Y - LOW Z)
		pPBIs[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S17_C3_VC );

		pPBIs[8]->SetMouseRegion( AID_C3_HI_2, 0.404487f, 0.459441f, 0.508553f, 0.562329f );// S18: TRANSLATION Z - HIGH (TRANSLATION Z - HIGH Z)
		pPBIs[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S18_C3_VC );

		pPBIs[9]->SetMouseRegion( AID_C3_HI_2, 0.534905f, 0.459441f, 0.642836f, 0.562329f );// S7: ROTATION ROLL - DISC RATE (ROTATION ROLL - PRI)
		pPBIs[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S7_C3_VC );

		pPBIs[10]->SetMouseRegion( AID_C3_HI_2, 0.675070f, 0.459441f, 0.780736f, 0.562329f );// S8: ROTATION PITCH - DISC RATE (ROTATION PITCH - ALT)
		pPBIs[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S8_C3_VC );

		pPBIs[11]->SetMouseRegion( AID_C3_HI_2, 0.807275f, 0.459441f, 0.913137f, 0.562329f );// S9: ROTATION YAW - DISC RATE (ROTATION YAW - VERN)
		pPBIs[11]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S9_C3_VC );

		pPBIs[12]->SetMouseRegion( AID_C3_HI_2, 0.130531f, 0.611581f, 0.236533f, 0.715951f );// S19: TRANSLATION X - NORM (TRANSLATION X - NORM)
		pPBIs[12]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S19_C3_VC );

		pPBIs[13]->SetMouseRegion( AID_C3_HI_2, 0.265553f, 0.611581f, 0.371038f, 0.715951f );// S20: TRANSLATION Y - NORM (TRANSLATION Y - NORM)
		pPBIs[13]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S20_C3_VC );

		pPBIs[14]->SetMouseRegion( AID_C3_HI_2, 0.404487f, 0.611581f, 0.508553f, 0.715951f );// S21: TRANSLATION Z - NORM (TRANSLATION Z - NORM)
		pPBIs[14]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S21_C3_VC );

		pPBIs[15]->SetMouseRegion( AID_C3_HI_2, 0.534905f, 0.611581f, 0.642836f, 0.715951f );// S10: ROTATION ROLL - ACCEL (ROTATION ROLL - DISC RATE)
		pPBIs[15]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S10_C3_VC );

		pPBIs[16]->SetMouseRegion( AID_C3_HI_2, 0.675070f, 0.611581f, 0.780736f, 0.715951f );// S11: ROTATION PITCH - ACCEL (ROTATION PITCH - DISC RATE)
		pPBIs[16]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S11_C3_VC );

		pPBIs[17]->SetMouseRegion( AID_C3_HI_2, 0.807275f, 0.611581f, 0.913137f, 0.715951f );// S12: ROTATION YAW - ACCEL (ROTATION YAW - DISC RATE)
		pPBIs[17]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S12_C3_VC );

		pPBIs[18]->SetMouseRegion( AID_C3_HI_2, 0.130531f, 0.756921f, 0.236533f, 0.860500f );// S22: TRANSLATION X - PULSE (TRANSLATION X - PULSE)
		pPBIs[18]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S22_C3_VC );

		pPBIs[19]->SetMouseRegion( AID_C3_HI_2, 0.265553f, 0.756921f, 0.371038f, 0.860500f );// S23: TRANSLATION Y - PULSE (TRANSLATION Y - PULSE)
		pPBIs[19]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S23_C3_VC );

		pPBIs[20]->SetMouseRegion( AID_C3_HI_2, 0.404487f, 0.756921f, 0.508553f, 0.860500f );// S24: TRANSLATION Z - PULSE (TRANSLATION Z - PULSE)
		pPBIs[20]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S24_C3_VC );

		pPBIs[21]->SetMouseRegion( AID_C3_HI_2, 0.534905f, 0.756921f, 0.642836f, 0.860500f );// S13: ROTATION ROLL - PULSE (ROTATION ROLL - PULSE)
		pPBIs[21]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S13_C3_VC );

		pPBIs[22]->SetMouseRegion( AID_C3_HI_2, 0.675070f, 0.756921f, 0.780736f, 0.860500f );// S14: ROTATION PITCH - PULSE (ROTATION PITCH - PULSE)
		pPBIs[22]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S14_C3_VC );

		pPBIs[23]->SetMouseRegion( AID_C3_HI_2, 0.807275f, 0.756921f, 0.913137f, 0.860500f );// S15: ROTATION YAW - PULSE (ROTATION YAW - PULSE)
		pPBIs[23]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S15_C3_VC );

		pOMSArm[LEFT]->SetMouseRegion( AID_C3_LO_1, 0.065761f, 0.193718f, 0.130265f, 0.852035f );
		pOMSArm[LEFT]->SetReference( _V( -0.2114868, 1.731335, 14.310857 ), switch_rot );
		pOMSArm[LEFT]->SetPullDirection( pull_dir );
		pOMSArm[LEFT]->DefineGroup( GRP_A1_S1_C3_VC );
		pOMSArm[LEFT]->SetInitialAnimState( 0.5f );

		pOMSArm[RIGHT]->SetMouseRegion( AID_C3_LO_1, 0.130265f, 0.193718f, 0.193410f, 0.852035f );
		pOMSArm[RIGHT]->SetReference( _V( -0.1716415, 1.731335, 14.310857 ), switch_rot );
		pOMSArm[RIGHT]->SetPullDirection( pull_dir );
		pOMSArm[RIGHT]->DefineGroup( GRP_A1_S2_C3_VC );
		pOMSArm[RIGHT]->SetInitialAnimState( 0.5f );

		pBFCCRTDisplay->SetMouseRegion( AID_C3_LO_1, 0.235637f, 0.192722f, 0.298614f, 0.611758f );
		pBFCCRTDisplay->SetReference( _V( -0.153415, 1.740035, 14.323057 ), switch_rot );
		pBFCCRTDisplay->DefineGroup( GRP_A1_S17_C3_VC );
		pBFCCRTDisplay->SetInitialAnimState( 0.5f );

		pBFCCRTSelect->SetMouseRegion( AID_C3_LO_1, 0.305018f, 0.196042f, 0.364991f, 0.611758f );
		pBFCCRTSelect->SetReference( _V( -0.124915, 1.740035, 14.322157 ), switch_rot );
		pBFCCRTSelect->DefineGroup( GRP_A1_S18_C3_VC );
		pBFCCRTSelect->SetInitialAnimState( 0.5f );

		pAirDataProbeStow[LEFT]->SetMouseRegion( AID_C3_LO_2, 0.0f, 0.0f, 0.232493f, 1.0f );
		pAirDataProbeStow[LEFT]->SetReference( _V( -0.2114868, 1.727635, 14.206857 ), switch_rot );
		pAirDataProbeStow[LEFT]->DefineGroup( GRP_A1_S19_C3_VC );
		pAirDataProbeStow[LEFT]->SetInitialAnimState( 0.5f );

		pAirDataProbeStow[RIGHT]->SetMouseRegion( AID_C3_LO_2, 0.232493f, 0.0f, 0.454066f, 1.0f );
		pAirDataProbeStow[RIGHT]->SetReference( _V( -0.1716415, 1.727635, 14.206857 ), switch_rot );
		pAirDataProbeStow[RIGHT]->DefineGroup( GRP_A1_S20_C3_VC );
		pAirDataProbeStow[RIGHT]->SetInitialAnimState( 0.5f );

		pAirDataProbe[LEFT]->SetMouseRegion( AID_C3_LO_8, 0.0f, 0.0f, 0.089090f, 0.550908f );
		pAirDataProbe[LEFT]->SetReference( _V( -0.2114868, 1.689961, 13.881657 ), switch_rot );
		pAirDataProbe[LEFT]->SetPullDirection( pull_dir );
		pAirDataProbe[LEFT]->DefineGroup( GRP_A5_S8_C3_VC );
		pAirDataProbe[LEFT]->SetInitialAnimState( 0.5f );

		pAirDataProbe[RIGHT]->SetMouseRegion( AID_C3_LO_8, 0.089090f, 0.0f, 0.167073f, 0.550908f );
		pAirDataProbe[RIGHT]->SetReference( _V( -0.1716415, 1.689961, 13.881657 ), switch_rot );
		pAirDataProbe[RIGHT]->SetPullDirection( pull_dir );
		pAirDataProbe[RIGHT]->DefineGroup( GRP_A5_S9_C3_VC );
		pAirDataProbe[RIGHT]->SetInitialAnimState( 0.5f );

		pSSMELimitShutDn->SetMouseRegion( AID_C3_LO_2, 0.818096f, 0.0f, 1.0f, 1.0f );
		pSSMELimitShutDn->SetReference( _V( -0.4785, 1.727335, 14.207757 ), switch_rot );
		pSSMELimitShutDn->DefineGroup( GRP_A1_S11_C3_VC );
		pSSMELimitShutDn->SetInitialAnimState( 0.5f );

		pSSMESDPBCover[0]->SetMouseRegion( AID_C3_HI_1, 0, 0.0f, 0.385422f, 0.294606f, 1.0f );
		pSSMESDPBCover[0]->SetMouseRegion( AID_C3_HI_1, 1, 0.0f, 0.177618f, 0.294606f, 0.385422f );
		pSSMESDPBCover[0]->SetReference( _V( -0.0545, 1.756435, 14.210357 ), switch_rot );
		pSSMESDPBCover[0]->DefineGroup( GRP_A1_COVER12_C3_VC );

		pSSMESDPBCover[1]->SetMouseRegion( AID_C3_HI_1, 0, 0.352651f, 0.207804f, 0.648538f, 0.817971f );
		pSSMESDPBCover[1]->SetMouseRegion( AID_C3_HI_1, 1, 0.352651f, 0.0f, 0.648538f, 0.207804f );
		pSSMESDPBCover[1]->SetReference( _V( -0.0174, 1.756435, 14.222157 ), switch_rot );
		pSSMESDPBCover[1]->DefineGroup( GRP_A1_COVER13_C3_VC );

		pSSMESDPBCover[2]->SetMouseRegion( AID_C3_HI_1, 0, 0.701482f, 0.385422f, 1.0f, 1.0f );
		pSSMESDPBCover[2]->SetMouseRegion( AID_C3_HI_1, 1, 0.701482f, 0.177618f, 1.0f, 0.385422f );
		pSSMESDPBCover[2]->SetReference( _V( 0.0197, 1.756435, 14.209357 ), switch_rot );
		pSSMESDPBCover[2]->DefineGroup( GRP_A1_COVER14_C3_VC );

		pSSMESDPB[0]->SetMouseRegion( AID_C3_HI_1, 0.048071f, 0.541476f, 0.251772f, 0.839993f );
		pSSMESDPB[0]->SetDirection( push_dir );
		pSSMESDPB[0]->DefineGroup( GRP_A1_S12_C3_VC );

		pSSMESDPB[1]->SetMouseRegion( AID_C3_HI_1, 0.407681f, 0.350393f, 0.607423f, 0.666636f );
		pSSMESDPB[1]->SetDirection( push_dir );
		pSSMESDPB[1]->DefineGroup( GRP_A1_S13_C3_VC );

		pSSMESDPB[2]->SetMouseRegion( AID_C3_HI_1, 0.748581f, 0.541476f, 0.958559f, 0.839993f );
		pSSMESDPB[2]->SetDirection( push_dir );
		pSSMESDPB[2]->DefineGroup( GRP_A1_S14_C3_VC );

		pSRBSEPSW->SetMouseRegion( AID_C3_LO_4, 0.0f, 0.0f, 1.0f, 1.0f );
		pSRBSEPSW->SetReference( _V( 0.00608, 1.717295, 14.105857 ), switch_rot );
		pSRBSEPSW->DefineGroup( GRP_A7_S1_C3_VC );
		pSRBSEPSW->SetInitialAnimState( 0.5f );

		pSRBSEPCover->SetMouseRegion( AID_C3_HI_3, 0, 0.0f, 0.249000f, 1.0f, 1.0f );
		pSRBSEPCover->SetMouseRegion( AID_C3_HI_3, 1, 0.0f, 0.0f, 1.0f, 0.249000f );
		pSRBSEPCover->SetReference( _V( -0.031, 1.743835, 14.122757 ), switch_rot );
		pSRBSEPCover->DefineGroup( GRP_A7_COVER2_C3_VC );

		pSRBSEPPB->SetMouseRegion( AID_C3_HI_3, 0.167579f, 0.447466f, 0.832967f, 0.829362f );
		pSRBSEPPB->SetDirection( push_dir );
		pSRBSEPPB->DefineGroup( GRP_A7_S2_C3_VC );

		pETSEPSW->SetMouseRegion( AID_C3_LO_5, 0.0f, 0.0f, 1.0f, 1.0f );
		pETSEPSW->SetReference( _V( -0.08218, 1.709385, 14.091887 ), switch_rot );
		pETSEPSW->SetPullDirection( pull_dir );
		pETSEPSW->DefineGroup( GRP_A7_S3_C3_VC );
		pETSEPSW->SetInitialAnimState( 0.5f );

		pETSEPCover->SetMouseRegion( AID_C3_HI_4, 0, 0.0f, 0.249000f, 1.0f, 1.0f );
		pETSEPCover->SetMouseRegion( AID_C3_HI_4, 1, 0.0f, 0.0f, 1.0f, 0.249000f );
		pETSEPCover->SetReference( _V( -0.119, 1.743835, 14.122757 ), switch_rot );
		pETSEPCover->DefineGroup( GRP_A7_COVER4_C3_VC );

		pETSEPPB->SetMouseRegion( AID_C3_HI_4, 0.108208f, 0.394301f, 0.799487f, 0.762508f );
		pETSEPPB->SetDirection( push_dir );
		pETSEPPB->DefineGroup( GRP_A7_S4_C3_VC );

		pBodyFlap->SetMouseRegion( AID_C3_LO_1, 0.878018f, 0.373431f, 0.940100f, 0.967761f );
		pBodyFlap->SetReference( _V( 0.13094, 1.728715, 14.295157 ), switch_rot );
		pBodyFlap->SetPullDirection( pull_dir );
		pBodyFlap->DefineGroup( GRP_A1_S10_C3_VC );
		pBodyFlap->SetInitialAnimState( 0.5f );
		pBodyFlap->SetSpringLoaded( true, 0 );
		pBodyFlap->SetSpringLoaded( true, 2 );

		pPitchTrim->DefineGroup( GRP_A1_S16_C3_VC );
		pPitchTrim->SetInitialAnimState( 0.5f );
		pPitchTrim->SetReference( _V( 0.134438, 1.727655, 14.208557 ), switch_rot );
		pPitchTrim->SetMouseRegion( AID_C3_LO_3, 0.706986f, 0.0f, 1.0f, 1.0f );
		pPitchTrim->SetSpringLoaded( true, 0 );
		pPitchTrim->SetSpringLoaded( true, 2 );

		pRollTrim->DefineGroup( GRP_A1_S15_C3_VC );
		pRollTrim->SetInitialAnimState( 0.5f );
		pRollTrim->SetReference( _V( 0.076424, 1.726905, 14.194157 ), switch_rotV );
		pRollTrim->SetMouseRegion( AID_C3_LO_3, 0.0f, 0.321917f, 0.516232f, 0.956090f );
		pRollTrim->SetOrientation( true );
		pRollTrim->SetSpringLoaded( true, 0 );
		pRollTrim->SetSpringLoaded( true, 2 );

		pYawTrim->DefineGroup( GRP_A7_S5_C3_VC );
		pYawTrim->SetInitialAnimState( 0.5f );
		pYawTrim->SetReference( _V( 0.198376, 1.712275, 14.062357 ), switch_rotV );
		pYawTrim->SetMouseRegion( AID_C3_LO_6, 0.0f, 0.0f, 1.0f, 1.0f );
		pYawTrim->SetOrientation( true );
		pYawTrim->SetSpringLoaded( true, 0 );
		pYawTrim->SetSpringLoaded( true, 2 );
	}

	void PanelC3::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		if (dipAIR_DATA_PROBE_LEFT_DEPLOYHEAT) dopAIR_DATA_PROBE_LEFT_DEPLOYHEAT.SetLine();
		else dopAIR_DATA_PROBE_LEFT_DEPLOYHEAT.ResetLine();

		if (dipAIR_DATA_PROBE_LEFT_DEPLOY) dopAIR_DATA_PROBE_LEFT_DEPLOY.SetLine();
		else dopAIR_DATA_PROBE_LEFT_DEPLOY.ResetLine();

		if (!dipAIR_DATA_PROBE_LEFT_DEPLOYHEAT && !dipAIR_DATA_PROBE_LEFT_DEPLOY) dopAIR_DATA_PROBE_LEFT_STOW.SetLine();
		else dopAIR_DATA_PROBE_LEFT_STOW.ResetLine();

		if (!dipAIR_DATA_PROBE_LEFT_DEPLOYHEAT && !dipAIR_DATA_PROBE_LEFT_DEPLOY && dipAIR_DATA_PROBE_STOW_LEFT_ENABLE) dopAIR_DATA_PROBE_STOW_LEFT_ENABLE.SetLine();
		else dopAIR_DATA_PROBE_STOW_LEFT_ENABLE.ResetLine();

		if (dipAIR_DATA_PROBE_RIGHT_DEPLOYHEAT) dopAIR_DATA_PROBE_RIGHT_DEPLOYHEAT.SetLine();
		else dopAIR_DATA_PROBE_RIGHT_DEPLOYHEAT.ResetLine();

		if (dipAIR_DATA_PROBE_RIGHT_DEPLOY) dopAIR_DATA_PROBE_RIGHT_DEPLOY.SetLine();
		else dopAIR_DATA_PROBE_RIGHT_DEPLOY.ResetLine();

		if (!dipAIR_DATA_PROBE_RIGHT_DEPLOYHEAT && !dipAIR_DATA_PROBE_RIGHT_DEPLOY) dopAIR_DATA_PROBE_RIGHT_STOW.SetLine();
		else dopAIR_DATA_PROBE_RIGHT_STOW.ResetLine();

		if (!dipAIR_DATA_PROBE_RIGHT_DEPLOYHEAT && !dipAIR_DATA_PROBE_RIGHT_DEPLOY && dipAIR_DATA_PROBE_STOW_RIGHT_ENABLE) dopAIR_DATA_PROBE_STOW_RIGHT_ENABLE.SetLine();
		else dopAIR_DATA_PROBE_STOW_RIGHT_ENABLE.ResetLine();

		if (dipTrimPanelOn)
		{
			// on
			if (dipUpPitchTrim) dopUpPitchTrim.SetLine();
			else dopUpPitchTrim.ResetLine();

			if (dipDownPitchTrim) dopDownPitchTrim.SetLine();
			else dopDownPitchTrim.ResetLine();

			if (dipRightRollTrim) dopRightRollTrim.SetLine();
			else dopRightRollTrim.ResetLine();

			if (dipLeftRollTrim) dopLeftRollTrim.SetLine();
			else dopLeftRollTrim.ResetLine();

			if (dipRightYawTrim) dopRightYawTrim.SetLine();
			else dopRightYawTrim.ResetLine();

			if (dipLeftYawTrim) dopLeftYawTrim.SetLine();
			else dopLeftYawTrim.ResetLine();
		}
		else
		{
			// off
			dopUpPitchTrim.ResetLine();
			dopDownPitchTrim.ResetLine();
			dopRightRollTrim.ResetLine();
			dopLeftRollTrim.ResetLine();
			dopRightYawTrim.ResetLine();
			dopLeftYawTrim.ResetLine();
		}

		if (dipSRBSEPSW_AUTOMAN && dipSRBSEP) dopSRBSEP.SetLine();
		else dopSRBSEP.ResetLine();

		if (dipETSEP && dipETSEPSW_MAN) dopETSEP.SetLine();
		else dopETSEP.ResetLine();
		return;
	}

	void PanelC3::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "DAP_PBI_FWD_1", 16 );
		for (int i = 0; i < 16; i++) pPBIs[i]->ConnectPushButton( pBundle, i );
		pBundle = STS()->BundleManager()->CreateBundle( "DAP_PBI_FWD_2", 16 );
		for (int i = 16; i < 24; i++) pPBIs[i]->ConnectPushButton( pBundle, i - 16 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_1", 16 );
		pPBIs[3]->ConnectLight( 0, pBundle, 3 );
		pPBIs[4]->ConnectLight( 0, pBundle, 7 );
		pPBIs[5]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_2", 16 );
		pPBIs[9]->ConnectLight( 0, pBundle, 3 );
		pPBIs[10]->ConnectLight( 0, pBundle, 7 );
		pPBIs[11]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_3", 16 );
		pPBIs[15]->ConnectLight( 0, pBundle, 3 );
		pPBIs[16]->ConnectLight( 0, pBundle, 7 );
		pPBIs[17]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_4", 16 );
		pPBIs[21]->ConnectLight( 0, pBundle, 3 );
		pPBIs[22]->ConnectLight( 0, pBundle, 7 );
		pPBIs[23]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_1", 16 );
		pPBIs[0]->ConnectLight( 0, pBundle, 3 );
		pPBIs[1]->ConnectLight( 0, pBundle, 7 );
		pPBIs[2]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_2", 16 );
		pPBIs[6]->ConnectLight( 0, pBundle, 3 );
		pPBIs[7]->ConnectLight( 0, pBundle, 7 );
		pPBIs[8]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_3", 16 );
		pPBIs[12]->ConnectLight( 0, pBundle, 3 );
		pPBIs[13]->ConnectLight( 0, pBundle, 7 );
		pPBIs[14]->ConnectLight( 0, pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_4", 16 );
		pPBIs[18]->ConnectLight( 0, pBundle, 3 );
		pPBIs[19]->ConnectLight( 0, pBundle, 7 );
		pPBIs[20]->ConnectLight( 0, pBundle, 11 );

		pBundle=STS()->BundleManager()->CreateBundle("LOMS", 4);
		pOMSArm[LEFT]->ConnectPort(2, pBundle, 0); // ARM
		pOMSArm[LEFT]->ConnectPort(1, pBundle, 1); // ARM/PRESS
		pBundle=STS()->BundleManager()->CreateBundle("ROMS", 4);
		pOMSArm[RIGHT]->ConnectPort(2, pBundle, 0); // ARM
		pOMSArm[RIGHT]->ConnectPort(1, pBundle, 1); // ARM/PRESS

		pBundle = STS()->BundleManager()->CreateBundle( "BFCCRT", 3 );
		pBFCCRTDisplay->ConnectPort( 1, pBundle, 0 );// ON
		pBFCCRTSelect->ConnectPort( 0, pBundle, 1 ); // 3+1
		pBFCCRTSelect->ConnectPort( 2, pBundle, 2 ); // 1+2

		DiscreteBundle* pBundleC3 = STS()->BundleManager()->CreateBundle( "C3_INTERNAL", 16 );
		pAirDataProbeStow[LEFT]->ConnectPort( 1, pBundleC3, 0 );
		pAirDataProbe[LEFT]->ConnectPort( 1, pBundleC3, 1 );// DEPLOY
		pAirDataProbe[LEFT]->ConnectPort( 2, pBundleC3, 2 );// DEPLOY/HEAT
		pAirDataProbeStow[RIGHT]->ConnectPort( 1, pBundleC3, 3 );
		pAirDataProbe[RIGHT]->ConnectPort( 1, pBundleC3, 4 );// DEPLOY
		pAirDataProbe[RIGHT]->ConnectPort( 2, pBundleC3, 5 );// DEPLOY/HEAT
		dipAIR_DATA_PROBE_STOW_LEFT_ENABLE.Connect( pBundleC3, 0 );
		dipAIR_DATA_PROBE_LEFT_DEPLOY.Connect( pBundleC3, 1 );
		dipAIR_DATA_PROBE_LEFT_DEPLOYHEAT.Connect( pBundleC3, 2 );
		dipAIR_DATA_PROBE_STOW_RIGHT_ENABLE.Connect( pBundleC3, 3 );
		dipAIR_DATA_PROBE_RIGHT_DEPLOY.Connect( pBundleC3, 4 );
		dipAIR_DATA_PROBE_RIGHT_DEPLOYHEAT.Connect( pBundleC3, 5 );
		pPitchTrim->ConnectPort( 0, pBundleC3, 6 );
		pPitchTrim->ConnectPort( 2, pBundleC3, 7 );
		pRollTrim->ConnectPort( 0, pBundleC3, 8 );
		pRollTrim->ConnectPort( 2, pBundleC3, 9 );
		pYawTrim->ConnectPort( 0, pBundleC3, 10 );
		pYawTrim->ConnectPort( 2, pBundleC3, 11 );
		dipUpPitchTrim.Connect( pBundleC3, 6 );
		dipDownPitchTrim.Connect( pBundleC3, 7 );
		dipRightRollTrim.Connect( pBundleC3, 8 );
		dipLeftRollTrim.Connect( pBundleC3, 9 );
		dipRightYawTrim.Connect( pBundleC3, 10 );
		dipLeftYawTrim.Connect( pBundleC3, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "AIR_DATA_PROBES_POWER", 16 );
		dopAIR_DATA_PROBE_LEFT_DEPLOYHEAT.Connect( pBundle, 0 );
		dopAIR_DATA_PROBE_LEFT_DEPLOY.Connect( pBundle, 1 );
		dopAIR_DATA_PROBE_LEFT_STOW.Connect( pBundle, 2 );
		dopAIR_DATA_PROBE_STOW_LEFT_ENABLE.Connect( pBundle, 3 );
		dopAIR_DATA_PROBE_RIGHT_DEPLOYHEAT.Connect( pBundle, 4 );
		dopAIR_DATA_PROBE_RIGHT_DEPLOY.Connect( pBundle, 5 );
		dopAIR_DATA_PROBE_RIGHT_STOW.Connect( pBundle, 6 );
		dopAIR_DATA_PROBE_STOW_RIGHT_ENABLE.Connect( pBundle, 7 );

		pBundle = STS()->BundleManager()->CreateBundle( "C3_LIMITS_SSMEPB", 6 );
		pSSMELimitShutDn->ConnectPort( 1, pBundle, 0 ); // AUTO
		pSSMELimitShutDn->ConnectPort( 0, pBundle, 1 ); // INHIBIT
		pSSMELimitShutDn->ConnectPort( 2, pBundle, 2 ); // ENABLE
		pSSMESDPB[0]->output.Connect( pBundle, 3 );// L
		pSSMESDPB[1]->output.Connect( pBundle, 4 );// C
		pSSMESDPB[2]->output.Connect( pBundle, 5 );// R

		pBundle = STS()->BundleManager()->CreateBundle( "C3_SEP", 6 );
		pSRBSEPSW->ConnectPort( 0, pBundle, 0 );// AUTO
		pSRBSEPSW->ConnectPort( 1, pBundle, 1 );// MAN/AUTO
		dopSRBSEP.Connect( pBundle, 2 );// SEP
		pETSEPSW->ConnectPort( 0, pBundle, 3 );// AUTO
		pETSEPSW->ConnectPort( 1, pBundle, 4 );// MAN
		dopETSEP.Connect( pBundle, 5 );// SEP
		pSRBSEPPB->output.Connect( pBundleC3, 12 );
		pETSEPPB->output.Connect( pBundleC3, 13 );
		dipSRBSEP.Connect( pBundleC3, 12 );
		dipETSEP.Connect( pBundleC3, 13 );
		dipSRBSEPSW_AUTOMAN.Connect( pBundle, 1 );
		dipETSEPSW_MAN.Connect( pBundle, 4 );

		pBundle = STS()->BundleManager()->CreateBundle( "PLT_TRIM_BF", 16 );
		// 0: F3 PLT TRIM RHC/PNL inh
		dipTrimPanelOn.Connect( pBundle, 1 );// 1: F3 PLT TRIM PANEL on
		dopUpPitchTrim.Connect( pBundle, 2 );// 2: C3 PLT PITCH TRIM up
		dopDownPitchTrim.Connect( pBundle, 3 );// 3: C3 PLT PITCH TRIM down
		dopRightRollTrim.Connect( pBundle, 4 );// 4: C3 PLT ROLL TRIM right
		dopLeftRollTrim.Connect( pBundle, 5 );// 5: C3 PLT ROLL TRIM left
		dopRightYawTrim.Connect( pBundle, 6 );// 6: C3 PLT YAW TRIM right
		dopLeftYawTrim.Connect( pBundle, 7 );// 7: C3 PLT YAW TRIM left
		pBodyFlap->ConnectPort( 0, pBundle, 8 );// 8: C3 PLT BODY FLAP down
		pBodyFlap->ConnectPort( 2, pBundle, 9 );// 9: C3 PLT BODY FLAP up

		// VC component DiscPorts need to be connected before Realize() is called
		AtlantisPanel::Realize();
	}

	void PanelC3::VisualCreated( void )
	{
		if (OV102)
		{
			// show switch
			DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
			if (hDevMesh != NULL)
			{
				GROUPEDITSPEC grpSpec;
				grpSpec.flags = GRPEDIT_SETUSERFLAG;
				grpSpec.UsrFlag = 0;
				oapiEditMeshGroup( hDevMesh, GRP_A1_S21_C3_VC, &grpSpec );

				// change texture
				if (hOV102Texture == NULL) hOV102Texture = oapiLoadTexture( "SSV\\OV\\panelC3_OV102.dds" );
				if (hOV102Texture == NULL) throw std::exception( "Could not load texture in panel C3" );
				else oapiSetTexture( hDevMesh, TEX_SSV_OV_PANELC3_C3_VC, hOV102Texture );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}
