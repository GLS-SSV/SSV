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
********************************************/
#include "PanelC3.h"
#include "StandardSwitch.h"
#include "PushButtonIndicator.h"
#include "PushButton.h"
#include "StandardSwitchCover.h"
#include "vc_defs.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "..\meshres_vc_c3.h"


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
		oapiVCRegisterArea (AID_C3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED);

		oapiVCSetAreaClickmode_Quadrilateral( AID_C3,
			_V( -0.2732771, 1.770285, 14.383267 ) + ofs, _V( 0.2732771, 1.770285, 14.383267 ) + ofs,
			_V( -0.2732771, 1.705345, 13.762267 ) + ofs, _V( 0.2732771, 1.705345, 13.762267 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelC3::DefineVC()
	{
		const VECTOR3 switch_rot = _V(1, 0, 0);
		const VECTOR3 switch_rotV = _V( 0.0, 0.104528, 0.994522 );
		const VECTOR3 pull_dir = _V( 0, 0.994522, -0.104528 );
		const VECTOR3 push_dir = -pull_dir;

		//oapiWriteLog("PanelC3: DefineVC called");

		AddAIDToMouseEventList(AID_C3);

		for (int i = 0; i < 24; i++)
		{
			pPBIs[i]->SetStateOffset( 1, 0.0f, 0.488281f );
			pPBIs[i]->SetDirection( push_dir );
		}

		// switch number: original name (current name)
		pPBIs[0]->SetMouseRegion( AID_C3, 0.076792f, 0.420048f, 0.115283f, 0.455242f );// S1: SELECT - A (SELECT - A)
		pPBIs[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S1_C3_VC );

		pPBIs[1]->SetMouseRegion( AID_C3, 0.126949f, 0.421518f, 0.166340f, 0.455293f );// S2: SELECT - B (SELECT - B)
		pPBIs[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S2_C3_VC );

		pPBIs[2]->SetMouseRegion( AID_C3, 0.181124f, 0.421175f, 0.219444f, 0.455331f );// S3: CONTROL - AUTO (CONTROL - AUTO)
		pPBIs[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S3_C3_VC );

		pPBIs[3]->SetMouseRegion( AID_C3, 0.231705f, 0.420583f, 0.271740f, 0.454928f );// S4: CONTROL - MAN (CONTROL - INRTL)
		pPBIs[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S4_C3_VC );

		pPBIs[4]->SetMouseRegion( AID_C3, 0.284360f, 0.420678f, 0.325547f, 0.455212f );// S5: RCS JETS - NORM (CONTROL - LVLH)
		pPBIs[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S5_C3_VC );

		pPBIs[5]->SetMouseRegion( AID_C3, 0.335767f, 0.420633f, 0.374571f, 0.455531f );// S6: RCS JETS - VERN (CONTROL - FREE)
		pPBIs[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S6_C3_VC );

		pPBIs[6]->SetMouseRegion( AID_C3, 0.076832f, 0.524369f, 0.115813f, 0.558626f );// S16: TRANSLATION X - HIGH ()
		pPBIs[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S16_C3_VC );

		pPBIs[7]->SetMouseRegion( AID_C3, 0.126628f, 0.523217f, 0.166078f, 0.558785f );// S17: TRANSLATION Y - HIGH (TRANSLATION Y - LOW Z)
		pPBIs[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S17_C3_VC );

		pPBIs[8]->SetMouseRegion( AID_C3, 0.178143f, 0.523321f, 0.218689f, 0.558025f );// S18: TRANSLATION Z - HIGH (TRANSLATION Z - HIGH Z)
		pPBIs[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S18_C3_VC );

		pPBIs[9]->SetMouseRegion( AID_C3, 0.233175f, 0.523569f, 0.273972f, 0.558653f );// S7: ROTATION ROLL - DISC RATE (ROTATION ROLL - PRI)
		pPBIs[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S7_C3_VC );

		pPBIs[10]->SetMouseRegion( AID_C3, 0.285445f, 0.523146f, 0.325593f, 0.558556f );// S8: ROTATION PITCH - DISC RATE (ROTATION PITCH - ALT)
		pPBIs[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S8_C3_VC );

		pPBIs[11]->SetMouseRegion( AID_C3, 0.336362f, 0.524081f, 0.376589f, 0.558426f );// S9: ROTATION YAW - DISC RATE (ROTATION YAW - VERN)
		pPBIs[11]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S9_C3_VC );

		pPBIs[12]->SetMouseRegion( AID_C3, 0.074573f, 0.576707f, 0.115387f, 0.612468f );// S19: TRANSLATION X - NORM (TRANSLATION X - NORM)
		pPBIs[12]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S19_C3_VC );

		pPBIs[13]->SetMouseRegion( AID_C3, 0.126687f, 0.577016f, 0.165797f, 0.611745f );// S20: TRANSLATION Y - NORM (TRANSLATION Y - NORM)
		pPBIs[13]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S20_C3_VC );

		pPBIs[14]->SetMouseRegion( AID_C3, 0.178360f, 0.576320f, 0.218115f, 0.611317f );// S21: TRANSLATION Z - NORM (TRANSLATION Z - NORM)
		pPBIs[14]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S21_C3_VC );

		pPBIs[15]->SetMouseRegion( AID_C3, 0.234408f, 0.576546f, 0.273775f, 0.611331f );// S10: ROTATION ROLL - ACCEL (ROTATION ROLL - DISC RATE)
		pPBIs[15]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S10_C3_VC );

		pPBIs[16]->SetMouseRegion( AID_C3, 0.284538f, 0.575901f, 0.324818f, 0.611630f );// S11: ROTATION PITCH - ACCEL (ROTATION PITCH - DISC RATE)
		pPBIs[16]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S11_C3_VC );

		pPBIs[17]->SetMouseRegion( AID_C3, 0.335612f, 0.576493f, 0.377545f, 0.611941f );// S12: ROTATION YAW - ACCEL (ROTATION YAW - DISC RATE)
		pPBIs[17]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S12_C3_VC );

		pPBIs[18]->SetMouseRegion( AID_C3, 0.074080f, 0.625474f, 0.115904f, 0.660760f );// S22: TRANSLATION X - PULSE (TRANSLATION X - PULSE)
		pPBIs[18]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S22_C3_VC );

		pPBIs[19]->SetMouseRegion( AID_C3, 0.127879f, 0.625166f, 0.166948f, 0.661009f );// S23: TRANSLATION Y - PULSE (TRANSLATION Y - PULSE)
		pPBIs[19]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S23_C3_VC );

		pPBIs[20]->SetMouseRegion( AID_C3, 0.177976f, 0.626219f, 0.218171f, 0.660640f );// S24: TRANSLATION Z - PULSE (TRANSLATION Z - PULSE)
		pPBIs[20]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S24_C3_VC );

		pPBIs[21]->SetMouseRegion( AID_C3, 0.233390f, 0.625540f, 0.274357f, 0.660435f );// S13: ROTATION ROLL - PULSE (ROTATION ROLL - PULSE)
		pPBIs[21]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S13_C3_VC );

		pPBIs[22]->SetMouseRegion( AID_C3, 0.284311f, 0.625695f, 0.324971f, 0.660364f );// S14: ROTATION PITCH - PULSE (ROTATION PITCH - PULSE)
		pPBIs[22]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S14_C3_VC );

		pPBIs[23]->SetMouseRegion( AID_C3, 0.336204f, 0.625340f, 0.376533f, 0.660289f );// S15: ROTATION YAW - PULSE (ROTATION YAW - PULSE)
		pPBIs[23]->DefineMeshGroup( GetVCMeshIndex(), GRP_A6_S15_C3_VC );

		pOMSArm[LEFT]->SetMouseRegion( AID_C3, 0.063487f, 0.070910f, 0.117992f, 0.173581f);
		pOMSArm[LEFT]->SetReference(_V( -0.2114868, 1.731335, 14.310857 ), switch_rot);
		pOMSArm[LEFT]->SetPullDirection(pull_dir);
		pOMSArm[LEFT]->DefineGroup( GRP_A1_S1_C3_VC );
		pOMSArm[LEFT]->SetInitialAnimState(0.5f);

		pOMSArm[RIGHT]->SetMouseRegion( AID_C3, 0.117992f, 0.070910f, 0.179360f, 0.173581f);
		pOMSArm[RIGHT]->SetReference(_V( -0.1716415, 1.731335, 14.310857 ), switch_rot);
		pOMSArm[RIGHT]->SetPullDirection(pull_dir);
		pOMSArm[RIGHT]->DefineGroup( GRP_A1_S2_C3_VC );
		pOMSArm[RIGHT]->SetInitialAnimState(0.5f);

		pBFCCRTDisplay->SetMouseRegion( AID_C3, 0.204959f, 0.071767f, 0.231104f, 0.138565f );
		pBFCCRTDisplay->SetReference( _V( -0.153415, 1.740035, 14.323057 ), switch_rot );
		pBFCCRTDisplay->DefineGroup( GRP_A1_S17_C3_VC );
		pBFCCRTDisplay->SetInitialAnimState( 0.5f );

		pBFCCRTSelect->SetMouseRegion( AID_C3, 0.250595f, 0.071845f, 0.286626f, 0.133207f );
		pBFCCRTSelect->SetReference( _V( -0.124915, 1.740035, 14.322157 ), switch_rot );
		pBFCCRTSelect->DefineGroup( GRP_A1_S18_C3_VC );
		pBFCCRTSelect->SetInitialAnimState( 0.5f );

		pAirDataProbeStow[LEFT]->SetMouseRegion( AID_C3, 0.063720f, 0.255919f, 0.126235f, 0.321174f);
		pAirDataProbeStow[LEFT]->SetReference(_V( -0.2114868, 1.727635, 14.206857 ), switch_rot);
		pAirDataProbeStow[LEFT]->DefineGroup( GRP_A1_S19_C3_VC );
		pAirDataProbeStow[LEFT]->SetInitialAnimState(0.5f);

		pAirDataProbeStow[RIGHT]->SetMouseRegion( AID_C3, 0.126235f, 0.255919f, 0.189637f, 0.321174f);
		pAirDataProbeStow[RIGHT]->SetReference(_V( -0.1716415, 1.727635, 14.206857 ), switch_rot);
		pAirDataProbeStow[RIGHT]->DefineGroup( GRP_A1_S20_C3_VC );
		pAirDataProbeStow[RIGHT]->SetInitialAnimState(0.5f);

		pAirDataProbe[LEFT]->SetMouseRegion( AID_C3, 0.080556f, 0.753680f, 0.148883f, 0.864232f);
		pAirDataProbe[LEFT]->SetReference(_V( -0.2114868, 1.689961, 13.881657 ), switch_rot);
		pAirDataProbe[LEFT]->SetPullDirection(pull_dir);
		pAirDataProbe[LEFT]->DefineGroup( GRP_A5_S8_C3_VC );
		pAirDataProbe[LEFT]->SetInitialAnimState(0.5f);

		pAirDataProbe[RIGHT]->SetMouseRegion( AID_C3, 0.148883f, 0.753680f, 0.208679f, 0.864232f);
		pAirDataProbe[RIGHT]->SetReference(_V( -0.1716415, 1.689961, 13.881657 ), switch_rot);
		pAirDataProbe[RIGHT]->SetPullDirection(pull_dir);
		pAirDataProbe[RIGHT]->DefineGroup( GRP_A5_S9_C3_VC );
		pAirDataProbe[RIGHT]->SetInitialAnimState(0.5f);

		pSSMELimitShutDn->SetMouseRegion( AID_C3, 0.302924f, 0.241994f, 0.357174f, 0.322577f);
		pSSMELimitShutDn->SetReference(_V( -0.4785, 1.727335, 14.207757 ), switch_rot);
		pSSMELimitShutDn->DefineGroup( GRP_A1_S11_C3_VC );
		pSSMELimitShutDn->SetInitialAnimState(0.5f);

		pSSMESDPBCover[0]->SetMouseRegion( AID_C3, 0, 0.374513f, 0.282742f, 0.428198f, 0.344442f );
		pSSMESDPBCover[0]->SetMouseRegion( AID_C3, 1, 0.368484f, 0.236416f, 0.423421f, 0.272399f );
		pSSMESDPBCover[0]->SetReference( _V( -0.0545, 1.756435, 14.210357 ), switch_rot );
		pSSMESDPBCover[0]->DefineGroup( GRP_A1_COVER12_C3_VC );

		pSSMESDPBCover[1]->SetMouseRegion( AID_C3, 0, 0.441879f, 0.260643f, 0.496332f, 0.321328f );
		pSSMESDPBCover[1]->SetMouseRegion( AID_C3, 1, 0.440854f, 0.217779f, 0.493692f, 0.257521f );
		pSSMESDPBCover[1]->SetReference( _V( -0.0174, 1.756435, 14.222157 ), switch_rot );
		pSSMESDPBCover[1]->DefineGroup( GRP_A1_COVER13_C3_VC );

		pSSMESDPBCover[2]->SetMouseRegion( AID_C3, 0, 0.511570f, 0.281802f, 0.563658f, 0.340997f );
		pSSMESDPBCover[2]->SetMouseRegion( AID_C3, 1, 0.514202f, 0.240377f, 0.563319f, 0.277074f );
		pSSMESDPBCover[2]->SetReference( _V( 0.0197, 1.756435, 14.209357 ), switch_rot );
		pSSMESDPBCover[2]->DefineGroup( GRP_A1_COVER14_C3_VC );

		pSSMESDPB[0]->SetMouseRegion( AID_C3, 0.380817f, 0.295599f, 0.420386f, 0.331035f );
		pSSMESDPB[0]->SetDirection( push_dir );
		pSSMESDPB[0]->DefineGroup( GRP_A1_S12_C3_VC );

		pSSMESDPB[1]->SetMouseRegion( AID_C3, 0.448899f, 0.276360f, 0.488503f, 0.310700f );
		pSSMESDPB[1]->SetDirection( push_dir );
		pSSMESDPB[1]->DefineGroup( GRP_A1_S13_C3_VC );

		pSSMESDPB[2]->SetMouseRegion( AID_C3, 0.515987f, 0.296511f, 0.556983f, 0.331199f );
		pSSMESDPB[2]->SetDirection( push_dir );
		pSSMESDPB[2]->DefineGroup( GRP_A1_S14_C3_VC );

		pSRBSEPSW->SetMouseRegion( AID_C3, 0.462571f, 0.414336f, 0.509469f, 0.491312f );
		pSRBSEPSW->SetReference( _V( 0.00608, 1.717295, 14.105857 ), switch_rot );
		pSRBSEPSW->DefineGroup( GRP_A7_S1_C3_VC );
		pSRBSEPSW->SetInitialAnimState( 0.5f );

		pSRBSEPCover->SetMouseRegion( AID_C3, 0, 0.533090f, 0.424105f, 0.586752f, 0.485038f );
		pSRBSEPCover->SetMouseRegion( AID_C3, 1, 0.532972f, 0.381586f, 0.579912f, 0.430505f );
		pSRBSEPCover->SetReference( _V( -0.031, 1.743835, 14.122757 ), switch_rot );
		pSRBSEPCover->DefineGroup( GRP_A7_COVER2_C3_VC );

		pSRBSEPPB->SetMouseRegion( AID_C3, 0.537215f, 0.435073f, 0.574794f, 0.470203f );
		pSRBSEPPB->SetDirection( push_dir );
		pSRBSEPPB->DefineGroup( GRP_A7_S2_C3_VC );

		pETSEPSW->SetMouseRegion( AID_C3, 0.629313f, 0.420718f, 0.675625f, 0.520487f );
		pETSEPSW->SetReference( _V( -0.08218, 1.709385, 14.091887 ), switch_rot );
		pETSEPSW->SetPullDirection( pull_dir );
		pETSEPSW->DefineGroup( GRP_A7_S3_C3_VC );
		pETSEPSW->SetInitialAnimState( 0.5f );

		pETSEPCover->SetMouseRegion( AID_C3, 0, 0.691866f, 0.422427f, 0.745989f, 0.482821f );
		pETSEPCover->SetMouseRegion( AID_C3, 1, 0.703331f, 0.380311f, 0.735696f, 0.423886f );
		pETSEPCover->SetReference( _V( -0.119, 1.743835, 14.122757 ), switch_rot );
		pETSEPCover->DefineGroup( GRP_A7_COVER4_C3_VC );

		pETSEPPB->SetMouseRegion( AID_C3, 0.698907f, 0.432862f, 0.731796f, 0.463562f );
		pETSEPPB->SetDirection( push_dir );
		pETSEPPB->DefineGroup( GRP_A7_S4_C3_VC );

		pBodyFlap->SetMouseRegion( AID_C3, 0.722860f, 0.096072f, 0.767030f, 0.196518f );
		pBodyFlap->SetReference( _V( 0.13094, 1.728715, 14.295157 ), switch_rot );
		pBodyFlap->SetPullDirection( pull_dir );
		pBodyFlap->DefineGroup( GRP_A1_S10_C3_VC );
		pBodyFlap->SetInitialAnimState( 0.5f );
		pBodyFlap->SetSpringLoaded( true, 0 );
		pBodyFlap->SetSpringLoaded( true, 2 );

		pPitchTrim->DefineGroup( GRP_A1_S16_C3_VC );
		pPitchTrim->SetInitialAnimState( 0.5f );
		pPitchTrim->SetReference( _V( 0.134438, 1.727655, 14.208557 ), switch_rot );
		pPitchTrim->SetMouseRegion( AID_C3, 0.724580f, 0.249894f, 0.765330f, 0.317102f );
		pPitchTrim->SetSpringLoaded( true, 0 );
		pPitchTrim->SetSpringLoaded( true, 2 );

		pRollTrim->DefineGroup( GRP_A1_S15_C3_VC );
		pRollTrim->SetInitialAnimState( 0.5f );
		pRollTrim->SetReference( _V( 0.076424, 1.726905, 14.194157 ), switch_rotV );
		pRollTrim->SetMouseRegion( AID_C3, 0.614689f, 0.271682f, 0.688049f, 0.321754f );
		pRollTrim->SetOrientation( true );
		pRollTrim->SetSpringLoaded( true, 0 );
		pRollTrim->SetSpringLoaded( true, 2 );

		pYawTrim->DefineGroup( GRP_A7_S5_C3_VC );
		pYawTrim->SetInitialAnimState( 0.5f );
		pYawTrim->SetReference( _V( 0.198376, 1.712275, 14.062357 ), switch_rotV );
		pYawTrim->SetMouseRegion( AID_C3, 0.837379f, 0.493350f, 0.908091f, 0.523183f );
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
};
