/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/06/18   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/03/21   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelF2.h"
#include "PushButtonIndicator.h"
#include "StandardLight.h"
#include "StandardSwitch.h"
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_f2.h"


namespace vc
{
	PanelF2::PanelF2(Atlantis* _sts, bool HasDragChute)
		: AtlantisPanel(_sts, "F2")
	{
		DefineMesh( MESHNAME_PANELF2 );

		this->HasDragChute = HasDragChute;

		Add( pMasterAlarm = new PushButtonIndicatorSingleLight( _sts, "MASTER ALARM" ) );

		Add( pPitchAuto = new PushButtonIndicatorSingleLight( _sts, "PITCH AUTO" ) );
		Add( pPitchCSS = new PushButtonIndicatorSingleLight( _sts, "PITCH CSS" ) );
		Add( pRollYawAuto = new PushButtonIndicatorSingleLight( _sts, "ROLL/YAW AUTO" ) );
		Add( pRollYawCSS = new PushButtonIndicatorSingleLight( _sts, "ROLL/YAW CSS" ) );

		Add( pSbdbkThrot = new PushButtonIndicatorDoubleLight( _sts, "SPD BK/THROT" ) );
		Add( pBodyFlap = new PushButtonIndicatorDoubleLight( _sts, "BODY FLAP" ) );

		Add( pBFC = new StandardSingleLight( _sts, "BFC" ) );

		if (HasDragChute)
		{
			Add( pDragChuteARMCover = new StandardSwitchCover( _sts, "DRAG CHUTE ARM COVER" ) );
			Add( pDragChuteDPYCover = new StandardSwitchCover( _sts, "DRAG CHUTE DPY COVER" ) );

			Add( pDragChuteARM = new PushButtonIndicatorDoubleLight( _sts, "DRAG CHUTE ARM" ) );
			Add( pDragChuteDPY = new PushButtonIndicatorDoubleLight( _sts, "DRAG CHUTE DPY" ) );
		}
		else
		{
			pDragChuteARMCover = NULL;
			pDragChuteDPYCover = NULL;
			pDragChuteARM = NULL;
			pDragChuteDPY = NULL;
		}
	}

	PanelF2::~PanelF2()
	{
	}

	void PanelF2::Realize()
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "DAP_CH_CONTROLS", 16 );
		pPitchAuto->ConnectPushButton( pBundle, 0 );
		pPitchCSS->ConnectPushButton( pBundle, 2 );
		pRollYawAuto->ConnectPushButton( pBundle, 4 );
		pRollYawCSS->ConnectPushButton( pBundle, 6 );
		pSbdbkThrot->ConnectPushButton( pBundle, 8 );
		pBodyFlap->ConnectPushButton( pBundle, 10 );

		if (HasDragChute)
		{
			pBundle = STS()->BundleManager()->CreateBundle( "DRAG_CHUTE", 16 );
			pDragChuteARM->output.Connect( pBundle, 0 );// arm pb (F2)
			//pDragChuteARM->output.Connect( pBundle, 1 );// arm pb (F3)
			pDragChuteDPY->output.Connect( pBundle, 2 );// dpy pb (F2)
			//pDragChuteDPY->output.Connect( pBundle, 3 );// dpy pb (F3)
			//pDragChuteJETT->output.Connect( pBundle, 4 );// jett pb (F3)
			//pDragChuteJETT->output.Connect( pBundle, 5 );// jett pb (F4)
		}

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_2", 16 );
		pBodyFlap->ConnectLight( 2, pBundle, 5 );
		pPitchAuto->ConnectLight( 0, pBundle, 9 );
		pPitchCSS->ConnectLight( 0, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_3", 16 );
		pRollYawAuto->ConnectLight( 0, pBundle, 5 );
		pRollYawCSS->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_4", 16 );
		pSbdbkThrot->ConnectLight( 0, pBundle, 1 );
		pSbdbkThrot->ConnectLight( 2, pBundle, 5 );
		pBodyFlap->ConnectLight( 0, pBundle, 9 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_5", 16 );
		pMasterAlarm->ConnectLight( 0, pBundle, 1 );
		pBFC->ConnectLight( 0, pBundle, 9 );

		if (HasDragChute)
		{
			pBundle = STS()->BundleManager()->CreateBundle( "ACA2_2", 16 );
			pDragChuteARM->ConnectLight( 2, pBundle, 5 );
			pDragChuteDPY->ConnectLight( 2, pBundle, 9 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_5", 16 );
		pMasterAlarm->ConnectLight( 1, pBundle, 1 );

		if (HasDragChute)
		{
			pBundle = STS()->BundleManager()->CreateBundle( "ACA3_1", 16 );
			pDragChuteDPY->ConnectLight( 0, pBundle, 9 );
			pDragChuteARM->ConnectLight( 0, pBundle, 13 );
		}

		AtlantisPanel::Realize();
	}

	void PanelF2::DefineVC()
	{
		VECTOR3 push_dir = _V( 0.0, -0.269911, 0.962885 );

		AddAIDToMouseEventList(AID_F2);

		pMasterAlarm->SetStateOffset( 1, 0.139648f, 0.0f );
		pMasterAlarm->SetDirection( push_dir );
		pMasterAlarm->SetMouseRegion( AID_F2, 0.547658f, 0.269709f, 0.599607f, 0.342875f );
		pMasterAlarm->DefineMeshGroup( GetVCMeshIndex(), GRP_S1_F2_VC );

		pPitchAuto->SetStateOffset( 1, 0.0f, 0.488281f );
		pPitchAuto->SetDirection( push_dir );
		pPitchAuto->SetMouseRegion( AID_F2, 0.423229f, 0.345204f, 0.455615f, 0.413250f );
		pPitchAuto->DefineMeshGroup( GetVCMeshIndex(), GRP_S2_F2_VC );

		pPitchCSS->SetStateOffset( 1, 0.0f, 0.488281f );
		pPitchCSS->SetDirection( push_dir );
		pPitchCSS->SetMouseRegion( AID_F2, 0.371251f, 0.406804f, 0.405170f, 0.469908f );
		pPitchCSS->DefineMeshGroup( GetVCMeshIndex(), GRP_S3_F2_VC );

		pRollYawAuto->SetStateOffset( 1, 0.0f, 0.488281f );
		pRollYawAuto->SetDirection( push_dir );
		pRollYawAuto->SetMouseRegion( AID_F2, 0.447410f, 0.430849f, 0.481545f, 0.497045f );
		pRollYawAuto->DefineMeshGroup( GetVCMeshIndex(), GRP_S5_F2_VC );

		pRollYawCSS->SetStateOffset( 1, 0.0f, 0.488281f );
		pRollYawCSS->SetDirection( push_dir );
		pRollYawCSS->SetMouseRegion( AID_F2, 0.394850f, 0.489301f, 0.428580f, 0.556178f );
		pRollYawCSS->DefineMeshGroup( GetVCMeshIndex(), GRP_S6_F2_VC );

		pSbdbkThrot->SetStateOffset( 1, 0.0f, 0.488281f );// AUTO
		pSbdbkThrot->SetStateOffset( 2, 0.146484f, 0.488281f );// MAN
		pSbdbkThrot->SetStateOffset( 3, 0.146484f, 0.0f );// AUTO/MAN
		pSbdbkThrot->SetDirection( push_dir );
		pSbdbkThrot->SetMouseRegion( AID_F2, 0.187106f, 0.618308f, 0.221076f, 0.681222f );
		pSbdbkThrot->DefineMeshGroup( GetVCMeshIndex(), GRP_S8_F2_VC );

		pBodyFlap->SetStateOffset( 1, 0.0f, 0.488281f );// AUTO
		pBodyFlap->SetStateOffset( 2, 0.146484f, 0.488281f );// MAN
		pBodyFlap->SetStateOffset( 3, 0.146484f, 0.0f );// AUTO/MAN
		pBodyFlap->SetDirection( push_dir );
		pBodyFlap->SetMouseRegion( AID_F2, 0.133054f, 0.680736f, 0.167659f, 0.742256f );
		pBodyFlap->DefineMeshGroup( GetVCMeshIndex(), GRP_S9_F2_VC );

		if (HasDragChute)
		{
			pDragChuteARM->SetStateOffset( 1, 0.0f, 0.488281f );// 1
			pDragChuteARM->SetStateOffset( 2, 0.146484f, 0.488281f );// 2
			pDragChuteARM->SetStateOffset( 3, 0.146484f, 0.0f );// 12
			pDragChuteARM->SetDirection( push_dir );
			pDragChuteARM->SetMouseRegion( AID_F2, 0.591878f, 0.054978f, 0.630076f, 0.128218f );
			pDragChuteARM->DefineMeshGroup( GetVCMeshIndex(), GRP_S10_F2_VC );

			pDragChuteDPY->SetStateOffset( 1, 0.0f, 0.488281f );// 1
			pDragChuteDPY->SetStateOffset( 2, 0.146484f, 0.488281f );// 2
			pDragChuteDPY->SetStateOffset( 3, 0.146484f, 0.0f );// 12
			pDragChuteDPY->SetDirection( push_dir );
			pDragChuteDPY->SetMouseRegion( AID_F2, 0.648582f, 0.054299f, 0.686353f, 0.127821f );
			pDragChuteDPY->DefineMeshGroup( GetVCMeshIndex(), GRP_S11_F2_VC );

			pDragChuteARMCover->SetMouseRegion( AID_F2, 0, 0.585063f, 0.040947f, 0.633282f, 0.150854f );
			pDragChuteARMCover->SetMouseRegion( AID_F2, 1, 0.583068f, 0.0f, 0.629692f, 0.027156f );
			pDragChuteARMCover->SetReference( _V( -0.5320, 2.5288, 14.6101 ), _V( 1, 0, 0 ) );
			pDragChuteARMCover->DefineGroup( GRP_COVER10_F2_VC );

			pDragChuteDPYCover->SetMouseRegion( AID_F2, 0, 0.642587f, 0.041293f, 0.690531f, 0.154314f );
			pDragChuteDPYCover->SetMouseRegion( AID_F2, 1, 0.642025f, 0.0f, 0.689314f, 0.027156f );
			pDragChuteDPYCover->SetReference( _V( -0.5320, 2.5288, 14.6101 ), _V( 1, 0, 0 ) );
			pDragChuteDPYCover->DefineGroup( GRP_COVER11_F2_VC );
		}

		pBFC->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS3_F2_VC );
		pBFC->SetStateOffset( 1, 0.139648f, 0.0f );
	}

	void PanelF2::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs=STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea(AID_F2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP);
		oapiVCSetAreaClickmode_Quadrilateral(AID_F2,
			_V(-1.154, 2.535, 14.612)+ofs, _V(-0.5808, 2.535, 14.612)+ofs,
			_V(-1.154, 2.25, 14.533)+ofs, _V(-0.5808, 2.25, 14.533) + _V( 0.001, 0.001, 0.001 )+ofs);

		return;
	}

	void PanelF2::VisualCreated( void )
	{
		if (!HasDragChute)
		{
			// hide drag chute stuff
			DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 3;
			oapiEditMeshGroup( hDevMesh, GRP_S10_F2_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_S11_F2_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_COVER10_F2_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_COVER11_F2_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_PANEL_DRAGCHUTE1_F2_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_PANEL_DRAGCHUTE2_F2_VC, &grpSpec );
		}

		AtlantisPanel::VisualCreated();
		return;
	}
};
