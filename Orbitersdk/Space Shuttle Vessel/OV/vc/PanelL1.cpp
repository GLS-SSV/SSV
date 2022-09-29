/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelL1.h"
#include "StandardSwitchCover.h"
#include "PushButtonIndicator.h"
#include "StandardLight.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_l1.h"


namespace vc
{
	PanelL1::PanelL1( Atlantis *_sts ):AtlantisPanel( _sts, "L1" )
	{
		DefineMesh( MESHNAME_PANELL1 );

		Add( pFireSuppressionAvBayAgentDischCover[0] = new StandardSwitchCover( _sts, "FIRE SUPPRESSION AV BAY 1 AGENT DISCH COVER" ) );
		Add( pFireSuppressionAvBayAgentDischCover[1] = new StandardSwitchCover( _sts, "FIRE SUPPRESSION AV BAY 2 AGENT DISCH COVER" ) );
		Add( pFireSuppressionAvBayAgentDischCover[2] = new StandardSwitchCover( _sts, "FIRE SUPPRESSION AV BAY 3 AGENT DISCH COVER" ) );

		Add( pFireSuppressionAvBayAgentDisch[0] = new PushButtonIndicatorSingleLight( _sts, "FIRE SUPPRESSION AV BAY 1 AGENT DISCH" ) );
		Add( pFireSuppressionAvBayAgentDisch[1] = new PushButtonIndicatorSingleLight( _sts, "FIRE SUPPRESSION AV BAY 2 AGENT DISCH" ) );
		Add( pFireSuppressionAvBayAgentDisch[2] = new PushButtonIndicatorSingleLight( _sts, "FIRE SUPPRESSION AV BAY 3 AGENT DISCH" ) );

		Add( pSmokeDetectionA_Cabin = new StandardSingleLight( _sts, "SMOKE DETECTION A CABIN" ) );
		Add( pSmokeDetectionA_LFltDeck = new StandardSingleLight( _sts, "SMOKE DETECTION A L FLT DECK" ) );
		Add( pSmokeDetectionA_AvBay1 = new StandardSingleLight( _sts, "SMOKE DETECTION A AV BAY 1" ) );
		Add( pSmokeDetectionA_AvBay2 = new StandardSingleLight( _sts, "SMOKE DETECTION A AV BAY 2" ) );
		Add( pSmokeDetectionA_AvBay3 = new StandardSingleLight( _sts, "SMOKE DETECTION A AV BAY 3" ) );

		Add( pSmokeDetectionB_Payload = new StandardSingleLight( _sts, "SMOKE DETECTION B PAYLOAD" ) );
		Add( pSmokeDetectionB_RFltDeck = new StandardSingleLight( _sts, "SMOKE DETECTION B R FLT DECK" ) );
		Add( pSmokeDetectionB_AvBay1 = new StandardSingleLight( _sts, "SMOKE DETECTION B AV BAY 1" ) );
		Add( pSmokeDetectionB_AvBay2 = new StandardSingleLight( _sts, "SMOKE DETECTION B AV BAY 2" ) );
		Add( pSmokeDetectionB_AvBay3 = new StandardSingleLight( _sts, "SMOKE DETECTION B AV BAY 3" ) );
	}

	PanelL1::~PanelL1()
	{
	}

	void PanelL1::DefineVC( void )
	{
		VECTOR3 switch_rot = _V( 0.338809, 0.0217555, 0.940604 );
		VECTOR3 push_dir = _V( -0.916229, -0.227543, 0.329772 );

		AddAIDToMouseEventList( AID_L1 );

		pFireSuppressionAvBayAgentDischCover[0]->SetMouseRegion( AID_L1, 0, 0.816760f, 0.231591f, 0.845892f, 0.349546f );
		pFireSuppressionAvBayAgentDischCover[0]->SetMouseRegion( AID_L1, 1, 0.816760f, 0.231591f, 0.845892f, 0.250382f );
		pFireSuppressionAvBayAgentDischCover[0]->DefineGroup( GRP_A1_COVER4_L1_VC );
		pFireSuppressionAvBayAgentDischCover[0]->SetReference( _V( -1.2237, 2.1413, 14.5724 ), switch_rot );

		pFireSuppressionAvBayAgentDischCover[1]->SetMouseRegion( AID_L1, 0, 0.853003f, 0.231591f, 0.882802f, 0.349546f );
		pFireSuppressionAvBayAgentDischCover[1]->SetMouseRegion( AID_L1, 1, 0.853003f, 0.231591f, 0.882802f, 0.250382f );
		pFireSuppressionAvBayAgentDischCover[1]->DefineGroup( GRP_A1_COVER5_L1_VC );
		pFireSuppressionAvBayAgentDischCover[1]->SetReference( _V( -1.2237, 2.1413, 14.5724 ), switch_rot );

		pFireSuppressionAvBayAgentDischCover[2]->SetMouseRegion( AID_L1, 0, 0.889269f, 0.231591f, 0.920107f, 0.349546f );
		pFireSuppressionAvBayAgentDischCover[2]->SetMouseRegion( AID_L1, 1, 0.889269f, 0.231591f, 0.920107f, 0.250382f );
		pFireSuppressionAvBayAgentDischCover[2]->DefineGroup( GRP_A1_COVER6_L1_VC );
		pFireSuppressionAvBayAgentDischCover[2]->SetReference( _V( -1.2237, 2.1413, 14.5724 ), switch_rot );

		pFireSuppressionAvBayAgentDisch[0]->SetStateOffset( 1, 0.0f, 0.488281f );
		pFireSuppressionAvBayAgentDisch[0]->SetDirection( push_dir );
		pFireSuppressionAvBayAgentDisch[0]->SetMouseRegion( AID_L1, 0.820565f, 0.259112f, 0.841511f, 0.325636f );
		pFireSuppressionAvBayAgentDisch[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_S4_L1_VC );

		pFireSuppressionAvBayAgentDisch[1]->SetStateOffset( 1, 0.0f, 0.488281f );
		pFireSuppressionAvBayAgentDisch[1]->SetDirection( push_dir );
		pFireSuppressionAvBayAgentDisch[1]->SetMouseRegion( AID_L1, 0.856432f, 0.259112f, 0.878352f, 0.325636f );
		pFireSuppressionAvBayAgentDisch[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_S5_L1_VC );

		pFireSuppressionAvBayAgentDisch[2]->SetStateOffset( 1, 0.0f, 0.488281f );
		pFireSuppressionAvBayAgentDisch[2]->SetDirection( push_dir );
		pFireSuppressionAvBayAgentDisch[2]->SetMouseRegion( AID_L1, 0.893686f, 0.259112f, 0.916010f, 0.325636f );
		pFireSuppressionAvBayAgentDisch[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_S6_L1_VC );

		pSmokeDetectionA_Cabin->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_A_CABIN_L1_VC );
		pSmokeDetectionA_Cabin->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionA_LFltDeck->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_A_LFLTDECK_L1_VC );
		pSmokeDetectionA_LFltDeck->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionA_AvBay1->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_A_AVBAY1_L1_VC );
		pSmokeDetectionA_AvBay1->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionA_AvBay2->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_A_AVBAY2_L1_VC );
		pSmokeDetectionA_AvBay2->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionA_AvBay3->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_A_AVBAY3_L1_VC );
		pSmokeDetectionA_AvBay3->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionB_Payload->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_B_PAYLOAD_L1_VC );
		pSmokeDetectionB_Payload->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionB_RFltDeck->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_B_RFLTDECK_L1_VC );
		pSmokeDetectionB_RFltDeck->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionB_AvBay1->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_B_AVBAY1_L1_VC );
		pSmokeDetectionB_AvBay1->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionB_AvBay2->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_B_AVBAY2_L1_VC );
		pSmokeDetectionB_AvBay2->SetStateOffset( 1, 0.0f, -0.232910f );

		pSmokeDetectionB_AvBay3->DefineMeshGroup( GetVCMeshIndex(), GRP_A1_XDS1_B_AVBAY3_L1_VC );
		pSmokeDetectionB_AvBay3->SetStateOffset( 1, 0.0f, -0.232910f );
		return;
	}

	void PanelL1::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_L1, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_L1,
			_V( -1.5142, 2.20883, 13.8049 ) + ofs, _V( -1.18219, 2.21861, 14.7453 ) + ofs,
			_V( -1.43522, 1.87544, 13.8055 ) + ofs, _V( -1.12764, 1.88993, 14.66 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelL1::Realize( void )
	{
		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "ACA1_1", 16 );
		pSmokeDetectionA_Cabin->ConnectLight( 0, pBundle, 1 );
		pSmokeDetectionA_LFltDeck->ConnectLight( 0, pBundle, 5 );
		pSmokeDetectionA_AvBay1->ConnectLight( 0, pBundle, 9 );
		pSmokeDetectionA_AvBay2->ConnectLight( 0, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA1_2", 16 );
		pSmokeDetectionA_AvBay3->ConnectLight( 0, pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_1", 16 );
		pSmokeDetectionB_Payload->ConnectLight( 0, pBundle, 1 );
		pSmokeDetectionB_RFltDeck->ConnectLight( 0, pBundle, 5 );
		pSmokeDetectionB_AvBay1->ConnectLight( 0, pBundle, 9 );
		pSmokeDetectionB_AvBay2->ConnectLight( 0, pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA2_2", 16 );
		pSmokeDetectionB_AvBay3->ConnectLight( 0, pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA3_2", 16 );
		pFireSuppressionAvBayAgentDisch[0]->ConnectLight( 0, pBundle, 5 );
		pFireSuppressionAvBayAgentDisch[1]->ConnectLight( 0, pBundle, 9 );
		pFireSuppressionAvBayAgentDisch[2]->ConnectLight( 0, pBundle, 13 );

		AtlantisPanel::Realize();
		return;
	}
}
