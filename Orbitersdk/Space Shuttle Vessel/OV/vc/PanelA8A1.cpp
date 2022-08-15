/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel 36V73A8A1 implementation



  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/05/06   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/08/24   GLS
2020/09/02   GLS
2021/06/03   GLS
2021/06/28   GLS
2021/07/02   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2022/01/07   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/03/22   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/19   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel A8 VC implementation



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#include "PanelA8A1.h"
#include "StandardSwitch.h"
#include "StandardRotarySwitch.h"
#include "Talkback.h"
#include "StandardLight.h"
#include "PushButtonIndicator.h"
#include "7SegDisp_RMS.h"
#include "..\meshres_vc_a8a1.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\Atlantis.h"


namespace vc
{
	PanelA8A1::PanelA8A1( Atlantis* _sts ):AtlantisPanel( _sts, "A8A1" )
	{
		DefineMesh( MESHNAME_PANELA8A1 );

		Add( pRMSMode = new RotaryDemuxSwitch( _sts, "MODE", 12 ) );
		pRMSMode->SetLabel( 0, "OPR CMD" );
		pRMSMode->SetLabel( 1, "AUTO 1" );
		pRMSMode->SetLabel( 2, "AUTO 2" );
		pRMSMode->SetLabel( 3, "AUTO 3" );
		pRMSMode->SetLabel( 4, "AUTO 4" );
		pRMSMode->SetLabel( 5, "ORB UNL" );
		pRMSMode->SetLabel( 6, "END EFF" );
		pRMSMode->SetLabel( 7, "ORB LD" );
		pRMSMode->SetLabel( 8, "PL" );
		pRMSMode->SetLabel( 9, "SINGLE" );
		pRMSMode->SetLabel( 10, "DIRECT" );
		pRMSMode->SetLabel( 11, "TEST" );

		Add( pEEMode = new StdSwitch3( _sts, "END EFFECTOR MODE" ) );
		pEEMode->SetLabel( 2, "AUTO" );
		pEEMode->SetLabel( 1, "OFF" );
		pEEMode->SetLabel( 0, "MAN" );

		Add( pEEManContr = new StdSwitch3( _sts, "END EFFECTOR MAN CONTR" ) );

		Add( pSoftStopTB = new StandardTalkback2( _sts, "SOFTWARE STOP" ) );

		Add( pRateMinTB = new StandardTalkback2( _sts, "RATE MIN" ) );

		Add( pEECapture = new StandardTalkback2( _sts, "END EFFECTOR CAPTURE" ) );
		Add( pEEExtend = new StandardTalkback2( _sts, "END EFFECTOR EXTEND" ) );
		Add( pEEClose = new StandardTalkback2( _sts, "END EFFECTOR CLOSE" ) );
		Add( pEEOpen = new StandardTalkback2( _sts, "END EFFECTOR OPEN" ) );
		Add( pEERigid = new StandardTalkback2( _sts, "END EFFECTOR RIGID" ) );
		Add( pEEDerigid = new StandardTalkback2( _sts, "END EFFECTOR DERIGID" ) );

		Add( pShoulderBraceTb = new StandardTalkback2( _sts, "SHOULDER BRACE RELEASE TB" ) );

		Add( pLEDParameter = new RotaryDemuxSwitch( _sts, "PARAMETER", 8 ) );
		pLEDParameter->SetLabel( 0, "TEST" );
		pLEDParameter->SetLabel( 1, "POSITION X/Y/Z" );
		pLEDParameter->SetLabel( 2, "ATTITUDE P/Y/R" );
		pLEDParameter->SetLabel( 3, "JOINT ANGLE" );
		pLEDParameter->SetLabel( 4, "VEL X/Y/Z" );
		pLEDParameter->SetLabel( 5, "RATE P/Y/R" );
		pLEDParameter->SetLabel( 6, "PORT TEMP LED/ABE/ID" );
		pLEDParameter->SetLabel( 7, "STBD TEMP LED/ABE/ID" );
		pLEDParameter->SetInitialPosition( 6 );

		Add( pLEDJoint = new RotaryDemuxSwitch( _sts, "JOINT", 8 ) );
		pLEDJoint->SetLabel( 0, "SHOULDER YAW" );
		pLEDJoint->SetLabel( 1, "SHOULDER PITCH" );
		pLEDJoint->SetLabel( 2, "ELBOW" );
		pLEDJoint->SetLabel( 3, "WRIST PITCH" );
		pLEDJoint->SetLabel( 4, "WRIST YAW" );
		pLEDJoint->SetLabel( 5, "WRIST ROLL" );
		pLEDJoint->SetLabel( 6, "END EFF TEMP" );
		pLEDJoint->SetLabel( 7, "CRIT TEMP" );

		Add( pShoulderBrace = new LockableLever3( _sts, "SHOULDER BRACE RELEASE" ) );
		Add( pSingleDirectDrive = new StdSwitch3( _sts, "SINGLE/DIRECT DRIVE" ) );

		Add( pModeLights[0] = new StandardSingleLight( _sts, "OPR CMD" ) );
		Add( pModeLights[1] = new StandardSingleLight( _sts, "AUTO 1" ) );
		Add( pModeLights[2] = new StandardSingleLight( _sts, "AUTO 2" ) );
		Add( pModeLights[3] = new StandardSingleLight( _sts, "AUTO 3" ) );
		Add( pModeLights[4] = new StandardSingleLight( _sts, "AUTO 4" ) );
		Add( pModeLights[5] = new StandardSingleLight( _sts, "ORB UNL" ) );
		Add( pModeLights[6] = new StandardSingleLight( _sts, "END EFF" ) );
		Add( pModeLights[7] = new StandardSingleLight( _sts, "ORB LD" ) );
		Add( pModeLights[8] = new StandardSingleLight( _sts, "PL" ) );
		Add( pModeLights[9] = new StandardSingleLight( _sts, "SINGLE" ) );
		Add( pModeLights[10] = new StandardSingleLight( _sts, "DIRECT" ) );
		Add( pModeLights[11] = new StandardSingleLight( _sts, "TEST" ) );

		Add( pCWLights[0] = new StandardSingleLight( _sts, "MCIU" ) );
		Add( pCWLights[1] = new StandardSingleLight( _sts, "ABE" ) );
		Add( pCWLights[2] = new StandardSingleLight( _sts, "GPC DATA" ) );
		Add( pCWLights[3] = new StandardSingleLight( _sts, "SINGULAR" ) );
		Add( pCWLights[4] = new StandardSingleLight( _sts, "CONTR ERR" ) );
		Add( pCWLights[5] = new StandardSingleLight( _sts, "STBD TEMP" ) );
		Add( pCWLights[6] = new StandardSingleLight( _sts, "DERIZIDIZE" ) );
		Add( pCWLights[7] = new StandardSingleLight( _sts, "RELEASE" ) );
		Add( pCWLights[8] = new StandardSingleLight( _sts, "CHECK CRT" ) );
		Add( pCWLights[9] = new StandardSingleLight( _sts, "REACH LIM" ) );
		Add( pCWLights[10] = new StandardSingleLight( _sts, "PORT TEMP" ) );

		Add( pSequenceLights[0] = new StandardSingleLight( _sts, "READY" ) );
		Add( pSequenceLights[1] = new StandardSingleLight( _sts, "IN PROG" ) );

		Add( pMasterAlarm = new PushButtonIndicatorSingleLight( _sts, "MASTER ALARM" ) );

		Add( pRMS = new _7SegDisp_RMS( _sts, "RMS" ) );
	}

	PanelA8A1::~PanelA8A1()
	{
	}

	void PanelA8A1::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;
		oapiVCRegisterArea( AID_A8A1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A8A1,
			_V( -0.270182, 2.89189, 12.2793 ) + ofs, _V( -0.791144, 2.89189, 12.2793 ) + ofs,
			_V( -0.270182, 2.35742, 12.448 ) + ofs, _V( -0.791144, 2.35742, 12.448 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelA8A1::DefineVC()
	{
		const VECTOR3 switch_rot_vert = _V( -1.0, 0.0, 0.0 );
		const VECTOR3 switch_rot_horz = _V( 0.0, 0.9499, -0.3126 );
		const VECTOR3 rotary_switch_rot = _V( 0.0, 0.3126, 0.9499 );
		const VECTOR3 push_dir = -rotary_switch_rot;
		const VECTOR3 switch_pull = -push_dir;

		AddAIDToMouseEventList( AID_A8A1 );

		pRMSMode->SetMouseRegion( AID_A8A1, 0.122035f, 0.256069f, 0.207928f, 0.336938f );
		pRMSMode->SetReference( _V( -0.355812, 2.73386, 12.3317 ), rotary_switch_rot );
		pRMSMode->DefineGroup( GRP_S3_A8A1_VC );
		pRMSMode->SetInitialAnimState( 0.0f );
		pRMSMode->SetWraparound( true );
		pRMSMode->DefineRotationAngle( 330.0f );
		pRMSMode->SetOffset( -150.0f );

		pEEMode->SetMouseRegion( AID_A8A1, 0.659563f, 0.320469f, 0.695801f, 0.358964f );
		pEEMode->SetReference( _V( -0.627639, 2.710755, 12.3365 ), switch_rot_vert );
		pEEMode->DefineGroup( GRP_S7_A8A1_VC );
		pEEMode->SetInitialAnimState( 0.5f );

		pEEManContr->SetMouseRegion( AID_A8A1, 0.714175f, 0.319654f, 0.750223f, 0.358981f );
		pEEManContr->SetReference( _V( -0.645778, 2.711275, 12.3363 ), switch_rot_vert );
		pEEManContr->DefineGroup( GRP_S8_A8A1_VC );
		pEEManContr->SetInitialAnimState( 0.5f );
		pEEManContr->SetSpringLoaded( true );

		pLEDParameter->SetMouseRegion( AID_A8A1, 0.459145f, 0.635839f, 0.543631f, 0.715755f );
		pLEDParameter->SetReference( _V( -0.531502, 2.53192, 12.395451 ), rotary_switch_rot );
		pLEDParameter->DefineGroup( GRP_S10_A8A1_VC );
		pLEDParameter->SetInitialAnimState( 0.0f );
		pLEDParameter->DefineRotationAngle( 210.0f );
		pLEDParameter->SetOffset( -120.0f );

		pLEDJoint->SetMouseRegion( AID_A8A1, 0.779815f, 0.634613f, 0.865309f, 0.714121f );
		pLEDJoint->SetReference( _V( -0.698426, 2.53255, 12.39495 ), rotary_switch_rot );
		pLEDJoint->DefineGroup( GRP_S11_A8A1_VC );
		pLEDJoint->SetInitialAnimState( 0.0f );
		pLEDJoint->DefineRotationAngle( 210.0f );
		pLEDJoint->SetOffset( -60.0f );

		pSingleDirectDrive->SetMouseRegion( AID_A8A1, 0.803017f, 0.793282f, 0.840073f, 0.830263f );
		pSingleDirectDrive->SetReference( _V( -0.692281, 2.459125, 12.41595 ), switch_rot_vert );
		pSingleDirectDrive->DefineGroup( GRP_S15_A8A1_VC );
		pSingleDirectDrive->SetInitialAnimState( 0.5f );
		pSingleDirectDrive->SetSpringLoaded( true );

		pShoulderBrace->SetMouseRegion( AID_A8A1, 0.780295f, 0.896139f, 0.821326f, 0.934045f );
		pShoulderBrace->SetReference( _V( -0.687046, 2.40706, 12.4424 ), switch_rot_horz );
		pShoulderBrace->DefineGroup( GRP_S16_A8A1_VC );
		pShoulderBrace->SetInitialAnimState( 0.5f );
		pShoulderBrace->SetPullDirection( switch_pull );
		pShoulderBrace->SetOrientation( true );
		pShoulderBrace->SetSpringLoaded( true );

		pShoulderBraceTb->DefineMeshGroups( GetVCMeshIndex(), GRP_DS13_U_A8A1_VC, GRP_DS13_L_A8A1_VC );

		pEECapture->DefineMeshGroups( GetVCMeshIndex(), GRP_DS9_U_A8A1_VC, GRP_DS9_L_A8A1_VC );

		pEEExtend->DefineMeshGroups( GetVCMeshIndex(), GRP_DS12_U_A8A1_VC, GRP_DS12_L_A8A1_VC );

		pEEClose->DefineMeshGroups( GetVCMeshIndex(), GRP_DS8_U_A8A1_VC, GRP_DS8_L_A8A1_VC );

		pEEOpen->DefineMeshGroups( GetVCMeshIndex(), GRP_DS11_U_A8A1_VC, GRP_DS11_L_A8A1_VC );

		pEERigid->DefineMeshGroups( GetVCMeshIndex(), GRP_DS7_U_A8A1_VC, GRP_DS7_L_A8A1_VC );

		pEEDerigid->DefineMeshGroups( GetVCMeshIndex(), GRP_DS10_U_A8A1_VC, GRP_DS10_L_A8A1_VC );

		pSoftStopTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS3_U_A8A1_VC, GRP_DS3_L_A8A1_VC );

		pRateMinTB->DefineMeshGroups( GetVCMeshIndex(), GRP_DS4_U_A8A1_VC, GRP_DS4_L_A8A1_VC );
		pRateMinTB->SetInactiveSegment( TB_OFF );

		// lights
		pModeLights[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_OPRCMD_A8A1_VC );
		pModeLights[0]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_AUTO1_A8A1_VC );
		pModeLights[1]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_AUTO2_A8A1_VC );
		pModeLights[2]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_AUTO3_A8A1_VC );
		pModeLights[3]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_AUTO4_A8A1_VC );
		pModeLights[4]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_ORBUNL_A8A1_VC );
		pModeLights[5]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_ENDEFF_A8A1_VC );
		pModeLights[6]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_ORBLD_A8A1_VC );
		pModeLights[7]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_PAYLOAD_A8A1_VC );
		pModeLights[8]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_SINGLE_A8A1_VC );
		pModeLights[9]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_DIRECT_A8A1_VC );
		pModeLights[10]->SetStateOffset( 1, 0.0f, 0.390625f );

		pModeLights[11]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_TEST_A8A1_VC );
		pModeLights[11]->SetStateOffset( 1, 0.0f, 0.390625f );


		pCWLights[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_MCIU_A8A1_VC );
		pCWLights[0]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_ABE_A8A1_VC );
		pCWLights[1]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_GPCDATA_A8A1_VC );
		pCWLights[2]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_SINGULAR_A8A1_VC );
		pCWLights[3]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_CONTRERR_A8A1_VC );
		pCWLights[4]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[5]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_STBDTEMP_A8A1_VC );
		pCWLights[5]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[6]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_DERIGIDIZE_A8A1_VC );
		pCWLights[6]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[7]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_RELEASE_A8A1_VC );
		pCWLights[7]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[8]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_CHECKCRT_A8A1_VC );
		pCWLights[8]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[9]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_REACHLIM_A8A1_VC );
		pCWLights[9]->SetStateOffset( 1, 0.0f, 0.390625f );

		pCWLights[10]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS2_PORTTEMP_A8A1_VC );
		pCWLights[10]->SetStateOffset( 1, 0.0f, 0.390625f );


		pSequenceLights[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS3_READY_A8A1_VC );
		pSequenceLights[0]->SetStateOffset( 1, 0.0f, 0.158203f );

		pSequenceLights[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS3_INPROG_A8A1_VC );
		pSequenceLights[1]->SetStateOffset( 1, 0.0f, 0.158203f );

		pMasterAlarm->SetMouseRegion( AID_A8A1, 0.478764f, 0.325886f, 0.520315f, 0.354731f );
		pMasterAlarm->SetStateOffset( 1, 0.0f, 0.113281f );
		pMasterAlarm->DefineMeshGroup( GetVCMeshIndex(), GRP_S6_A8A1_VC );
		pMasterAlarm->SetDirection( push_dir );

		pRMS->DefineMesh( GetVCMeshIndex() );
		pRMS->DefineComponent( GRP_M2_1_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M2_2_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M2_3_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M2_4_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M2_SIGN_A8A1_VC, false, false, false, _7SD_STATE_SIGNOFF );
		pRMS->DefineComponent( GRP_M3_1_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M3_2_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M3_3_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M3_4_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M3_SIGN_A8A1_VC, false, false, false, _7SD_STATE_SIGNOFF );
		pRMS->DefineComponent( GRP_M4_1_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M4_2_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M4_3_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M4_4_A8A1_VC, true, true, false, _7SD_STATE_NUM0_DOTOFF );
		pRMS->DefineComponent( GRP_M4_SIGN_A8A1_VC, false, false, false, _7SD_STATE_SIGNOFF );
		return;
	}

	void PanelA8A1::Realize()
	{
		DiscreteBundle* pBundle=STS()->BundleManager()->CreateBundle( "RMS", 16 );
		pShoulderBrace->ConnectPort( 0, pBundle, 4 );
		pShoulderBraceTb->SetInput( pBundle, 5, TB_GRAY );
		pMasterAlarm->ConnectPushButton( pBundle, 7 );

		pBundle = STS()->BundleManager()->CreateBundle( "RMS_MODE", 16 );
		for (unsigned short i = 0; i < 12 ;i++) pRMSMode->ConnectOutputSignal( i, pBundle, i );

		pBundle=STS()->BundleManager()->CreateBundle("RMS_EE", 16);
		pEEMode->ConnectPort( 2, pBundle, 2 );
		pEEMode->ConnectPort( 0, pBundle, 3 );
		pEEManContr->ConnectPort( 2, pBundle, 4 );
		pEEManContr->ConnectPort( 0, pBundle, 5 );
		pEECapture->SetInput( pBundle, 6, TB_GRAY );
		pEEExtend->SetInput( pBundle, 7, TB_GRAY );
		pEEClose->SetInput( pBundle, 8, TB_GRAY );
		pEEOpen->SetInput( pBundle, 9, TB_GRAY );
		pEERigid->SetInput( pBundle, 10, TB_GRAY );
		pEEDerigid->SetInput( pBundle, 11, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "A8_LED", 16 );
		for (int i = 0; i < 8; i++) pLEDParameter->ConnectOutputSignal( i, pBundle, i );
		lighttest.Connect( pBundle, 0 );

		pBundle = STS()->BundleManager()->CreateBundle( "RMS_SINGLE_JOINT", 16 );
		for (int i = 0; i < 8; i++) pLEDJoint->ConnectOutputSignal( i, pBundle, i );
		pSingleDirectDrive->ConnectPort( 2, pBundle, 8 );
		pSingleDirectDrive->ConnectPort( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "RMS_MODELIGHTS", 16 );
		for (int i = 0; i < 12; i++) lightcmd[i].Connect( pBundle, i );

		pBundle=STS()->BundleManager()->CreateBundle( "RMS_CWLIGHTS_TB", 16 );
		for (int i = 14; i < 26; i++) lightcmd[i].Connect( pBundle, i - 14 );
		pSoftStopTB->SetInput( pBundle, 12, TB_GRAY );
		pRateMinTB->SetInput( pBundle, 13, TB_ON );

		pBundle = STS()->BundleManager()->CreateBundle( "A8LIGHTS_A", 16 );
		for (int i = 0; i < 12; i++) pModeLights[i]->ConnectLight( 0, pBundle, i );
		pSequenceLights[0]->ConnectLight( 0, pBundle, 12 );
		pSequenceLights[1]->ConnectLight( 0, pBundle, 13 );

		for (int i = 0; i < 14; i++) lightoutput[i].Connect( pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "A8LIGHTS_B", 16 );
		for (int i = 0; i < 11; i++) pCWLights[i]->ConnectLight( 0, pBundle, i );
		pMasterAlarm->ConnectLight( 0, pBundle, 11 );

		for (int i = 14; i < 26; i++) lightoutput[i].Connect( pBundle, i - 14 );

		AtlantisPanel::Realize();
		return;
	}

	void PanelA8A1::OnPostStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPostStep( simt, simdt, mjd );

		if (lighttest.IsSet())
		{
			for (int i = 0; i < 26; i++) lightoutput[i].SetLine();
		}
		else
		{
			for (int i = 0; i < 26; i++) lightoutput[i].SetLine( (int)lightcmd[i].IsSet() * 5.0f );
		}
		return;
	}
};
