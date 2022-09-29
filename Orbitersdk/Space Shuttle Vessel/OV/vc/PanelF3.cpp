/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/03   GLS
2021/06/18   GLS
2021/08/24   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/03/21   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/27   GLS
2022/09/29   GLS
********************************************/
#include "PanelF3.h"
#include "PushButtonIndicator.h"
#include "StandardLight.h"
#include "StandardSwitch.h"
#include "StandardSwitchCover.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_f3.h"


namespace vc
{
	PanelF3::PanelF3( Atlantis* _sts, bool HasDragChute ):AtlantisPanel( _sts, "F3" )
	{
		DefineMesh( MESHNAME_PANELF3 );

		this->HasDragChute = HasDragChute;

		Add( pNWSFail = new StandardSingleLight( _sts, "NWS FAIL" ) );
		Add( pAntiSkidFail = new StandardSingleLight( _sts, "ANTI SKID FAIL" ) );

		Add( pCDRTRIMRHCPNL = new StdSwitch2( _sts, "TRIM RHC/PNL CDR" ) );
		pCDRTRIMRHCPNL->SetLabel( 0, "INHIBIT" );
		pCDRTRIMRHCPNL->SetLabel( 1, "ENABLE" );

		Add( pCDRTRIMPANEL = new StdSwitch2( _sts, "TRIM PANEL CDR" ) );
		pCDRTRIMPANEL->SetLabel( 0, "OFF" );
		pCDRTRIMPANEL->SetLabel( 1, "ON" );

		Add( pPLTTRIMRHCPNL = new StdSwitch2( _sts, "TRIM RHC/PNL PLT" ) );
		pPLTTRIMRHCPNL->SetLabel( 0, "INHIBIT" );
		pPLTTRIMRHCPNL->SetLabel( 1, "ENABLE" );

		Add( pPLTTRIMPANEL = new StdSwitch2( _sts, "TRIM PANEL PLT" ) );
		pPLTTRIMPANEL->SetLabel( 0, "OFF" );
		pPLTTRIMPANEL->SetLabel( 1, "ON" );

		Add( pHUDPower[0] = new StdSwitch2( _sts, "HUD POWER CDR" ) );
		Add( pHUDPower[1] = new StdSwitch2( _sts, "HUD POWER PLT" ) );
		pHUDPower[0]->SetLabel( 0, "OFF" );
		pHUDPower[0]->SetLabel( 1, "ON" );
		pHUDPower[1]->SetLabel( 0, "OFF" );
		pHUDPower[1]->SetLabel( 1, "ON" );

		if (HasDragChute)
		{
			Add( pDragChuteARMCover = new StandardSwitchCover( _sts, "DRAG CHUTE ARM COVER" ) );
			Add( pDragChuteDPYCover = new StandardSwitchCover( _sts, "DRAG CHUTE DPY COVER" ) );
			Add( pDragChuteJETTCover = new StandardSwitchCover( _sts, "DRAG CHUTE JETT COVER" ) );

			Add( pDragChuteARM = new PushButtonIndicatorDoubleLight( _sts, "DRAG CHUTE ARM" ) );
			Add( pDragChuteDPY = new PushButtonIndicatorDoubleLight( _sts, "DRAG CHUTE DPY" ) );
			Add( pDragChuteJETT = new PushButtonIndicatorDoubleLight( _sts, "DRAG CHUTE JETT" ) );
		}
		else
		{
			pDragChuteARMCover = NULL;
			pDragChuteDPYCover = NULL;
			pDragChuteJETTCover = NULL;
			pDragChuteARM = NULL;
			pDragChuteDPY = NULL;
			pDragChuteJETT = NULL;
		}
	}

	PanelF3::~PanelF3()
	{
	}

	void PanelF3::Realize()
	{
		DiscreteBundle* pBundle;

		if (HasDragChute)
		{
			pBundle = STS()->BundleManager()->CreateBundle( "DRAG_CHUTE", 16 );
			//pDragChuteARM->output.Connect( pBundle, 0 );// arm pb (F2)
			pDragChuteARM->output.Connect( pBundle, 1 );// arm pb (F3)
			//pDragChuteDPY->output.Connect( pBundle, 2 );// dpy pb (F2)
			pDragChuteDPY->output.Connect( pBundle, 3 );// dpy pb (F3)
			pDragChuteJETT->output.Connect( pBundle, 4 );// jett pb (F3)
			//pDragChuteJETT->output.Connect( pBundle, 5 );// jett pb (F4)

			pBundle = STS()->BundleManager()->CreateBundle( "ACA2_1", 16 );
			pDragChuteDPY->ConnectLight( 2, pBundle, 7 );
			pDragChuteARM->ConnectLight( 2, pBundle, 11 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_2", 16 );
		pAntiSkidFail->ConnectLight( 0, pBundle, 7 );
		if (HasDragChute)
		{
			pDragChuteJETT->ConnectLight( 2, pBundle, 13 );

			pBundle = STS()->BundleManager()->CreateBundle( "ACA3_1", 16 );
			pDragChuteJETT->ConnectLight( 0, pBundle, 5 );
		}

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_5", 16 );
		if (HasDragChute) pDragChuteARM->ConnectLight( 0, pBundle, 3 );
		pNWSFail->ConnectLight( 0, pBundle, 5 );
		if (HasDragChute) pDragChuteDPY->ConnectLight( 0, pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "HUD_SWITCHES", 16 );
		pHUDPower[0]->ConnectPort( 1, pBundle, 0 );// power cdr
		pHUDPower[1]->ConnectPort( 1, pBundle, 8 );// power plt

		pBundle = STS()->BundleManager()->CreateBundle( "CDR_TRIM_BF_EM", 16 );
		pCDRTRIMRHCPNL->ConnectPort( 0, pBundle, 0 );// 0: F3 CDR TRIM RHC/PNL inh
		pCDRTRIMPANEL->ConnectPort( 1, pBundle, 1 );// 1: F3 CDR TRIM PANEL on

		pBundle = STS()->BundleManager()->CreateBundle( "PLT_TRIM_BF", 16 );
		pPLTTRIMRHCPNL->ConnectPort( 0, pBundle, 0 );// 0: F3 PLT TRIM RHC/PNL inh
		pPLTTRIMPANEL->ConnectPort( 1, pBundle, 1 );// 1: F3 PLT TRIM PANEL on

		AtlantisPanel::Realize();
	}

	void PanelF3::DefineVC()
	{
		VECTOR3 switch_rot = _V( 1, 0, 0 );
		VECTOR3 push_dir = _V( 0.0, -0.269911, 0.962885 );

		AddAIDToMouseEventList( AID_F3 );

		if (HasDragChute)
		{
			pDragChuteARM->SetStateOffset( 1, 0.0f, 0.488281f );// 1
			pDragChuteARM->SetStateOffset( 2, 0.146484f, 0.488281f );// 2
			pDragChuteARM->SetStateOffset( 3, 0.146484f, 0.0f );// 12
			pDragChuteARM->SetDirection( push_dir );
			pDragChuteARM->SetMouseRegion( AID_F3, 0.941485f, 0.155126f, 0.961229f, 0.349624f );
			pDragChuteARM->DefineMeshGroup( GetVCMeshIndex(), GRP_S8_F3_VC );

			pDragChuteDPY->SetStateOffset( 1, 0.0f, 0.488281f );// 1
			pDragChuteDPY->SetStateOffset( 2, 0.146484f, 0.488281f );// 2
			pDragChuteDPY->SetStateOffset( 3, 0.146484f, 0.0f );// 12
			pDragChuteDPY->SetDirection( push_dir );
			pDragChuteDPY->SetMouseRegion( AID_F3, 0.970976f, 0.154359f, 0.990583f, 0.348370f );
			pDragChuteDPY->DefineMeshGroup( GetVCMeshIndex(), GRP_S9_F3_VC );

			pDragChuteJETT->SetStateOffset( 1, 0.0f, 0.488281f );// 1
			pDragChuteJETT->SetStateOffset( 2, 0.146484f, 0.488281f );// 2
			pDragChuteJETT->SetStateOffset( 3, 0.146484f, 0.0f );// 12
			pDragChuteJETT->SetDirection( push_dir );
			pDragChuteJETT->SetMouseRegion( AID_F3, 0.028511f, 0.158667f, 0.048433f, 0.349924f );
			pDragChuteJETT->DefineMeshGroup( GetVCMeshIndex(), GRP_S7_F3_VC );

			pDragChuteARMCover->SetMouseRegion( AID_F3, 0, 0.938748f, 0.117915f, 0.963932f, 0.419314f );
			pDragChuteARMCover->SetMouseRegion( AID_F3, 1, 0.933402f, 0.0f, 0.952428f, 0.066717f );
			pDragChuteARMCover->SetReference( _V( -0.5320, 2.5288, 14.6101 ), switch_rot );
			pDragChuteARMCover->DefineGroup( GRP_COVER8_F3_VC );

			pDragChuteDPYCover->SetMouseRegion( AID_F3, 0, 0.968342f, 0.117915f, 0.992407f, 0.419314f );
			pDragChuteDPYCover->SetMouseRegion( AID_F3, 1, 0.961976f, 0.0f, 0.986786f, 0.066717f );
			pDragChuteDPYCover->SetReference( _V( -0.5320, 2.5288, 14.6101 ), switch_rot );
			pDragChuteDPYCover->DefineGroup( GRP_COVER9_F3_VC );

			pDragChuteJETTCover->SetMouseRegion( AID_F3, 0, 0.025776f, 0.120962f, 0.051179f, 0.428174f );
			pDragChuteJETTCover->SetMouseRegion( AID_F3, 1, 0.025775f, 0.0f, 0.052357f, 0.073427f );
			pDragChuteJETTCover->SetReference( _V( -0.5320, 2.5288, 14.6101 ), switch_rot );
			pDragChuteJETTCover->DefineGroup( GRP_COVER7_F3_VC );
		}

		pHUDPower[0]->DefineGroup( GRP_S1_F3_VC );
		pHUDPower[0]->SetInitialAnimState( 0.5 );
		pHUDPower[0]->SetReference( _V( 0.5358, 2.4529, 14.5890 ), switch_rot );
		pHUDPower[0]->SetMouseRegion( AID_F3, 0.021770f, 0.664091f, 0.044223f, 0.886290f );

		pHUDPower[1]->DefineGroup( GRP_S6_F3_VC );
		pHUDPower[1]->SetInitialAnimState( 0.5 );
		pHUDPower[1]->SetReference( _V( -0.5374, 2.4530, 14.5890 ), switch_rot );
		pHUDPower[1]->SetMouseRegion( AID_F3, 0.976221f, 0.664091f, 0.999793f, 0.886290f );

		pNWSFail->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS3_F3_VC );
		pNWSFail->SetStateOffset( 1, 0.139648f, 0.0f );

		pAntiSkidFail->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS4_F3_VC );
		pAntiSkidFail->SetStateOffset( 1, 0.139648f, 0.0f );

		pCDRTRIMRHCPNL->DefineGroup( GRP_S2_F3_VC );
		pCDRTRIMRHCPNL->SetInitialAnimState( 0.5f );
		pCDRTRIMRHCPNL->SetReference( _V( 0.466682, 2.45302, 14.589 ), switch_rot );
		pCDRTRIMRHCPNL->SetMouseRegion( AID_F3, 0.050759f, 0.664091f, 0.073170f, 0.886290f );

		pCDRTRIMPANEL->DefineGroup( GRP_S3_F3_VC );
		pCDRTRIMPANEL->SetInitialAnimState( 0.5f );
		pCDRTRIMPANEL->SetReference( _V( 0.466682, 2.45302, 14.589 ), switch_rot );
		pCDRTRIMPANEL->SetMouseRegion( AID_F3, 0.084153f, 0.664091f, 0.105775f, 0.886290f );

		pPLTTRIMRHCPNL->DefineGroup( GRP_S4_F3_VC );
		pPLTTRIMRHCPNL->SetInitialAnimState( 0.5f );
		pPLTTRIMRHCPNL->SetReference( _V( 0.466682, 2.45302, 14.589 ), switch_rot );
		pPLTTRIMRHCPNL->SetMouseRegion( AID_F3, 0.912835f, 0.664091f, 0.936261f, 0.886290f );

		pPLTTRIMPANEL->DefineGroup( GRP_S5_F3_VC );
		pPLTTRIMPANEL->SetInitialAnimState( 0.5f );
		pPLTTRIMPANEL->SetReference( _V( 0.494073, 2.45218, 14.589 ), switch_rot );
		pPLTTRIMPANEL->SetMouseRegion( AID_F3, 0.943151f, 0.664091f, 0.968712f, 0.886290f );
	}

	void PanelF3::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs=STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_F3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP );
		oapiVCSetAreaClickmode_Quadrilateral( AID_F3,
			_V( -0.5758, 2.5361, 14.6138 ) + ofs, _V( 0.5480, 2.5361, 14.6138 ) + ofs,
			_V( -0.5758, 2.4282, 14.5819 ) + ofs, _V( 0.5480, 2.4282, 14.5819 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

	void PanelF3::VisualCreated( void )
	{
		if (!HasDragChute)
		{
			// hide drag chute stuff
			DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 3;
			oapiEditMeshGroup( hDevMesh, GRP_S8_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_S9_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_S7_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_COVER8_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_COVER9_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_COVER7_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_PANEL_DRAGCHUTE1_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_PANEL_DRAGCHUTE2_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_PANEL_DRAGCHUTE3_F3_VC, &grpSpec );
			oapiEditMeshGroup( hDevMesh, GRP_PANEL_DRAGCHUTE4_F3_VC, &grpSpec );
		}

		AtlantisPanel::VisualCreated();
		return;
	}
}
