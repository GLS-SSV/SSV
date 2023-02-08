#include "PanelA7A3_SPDS.h"
#include "CircuitBreaker.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a7a3_spds.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA7A3_SPDS";
	constexpr VECTOR3 OFFSET_PANEL = {0.256958, 2.22934, 12.4852};


	PanelA7A3_SPDS::PanelA7A3_SPDS( Atlantis* _sts ) : AtlantisPanel( _sts, "A7A3_SPDS" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );
		
		Add( pPAYLOAD_RELEASE_MN_A = new CircuitBreaker( _sts, "PAYLOAD RELEASE MN A" ) );
		Add( pPAYLOAD_RELEASE_MN_B = new CircuitBreaker( _sts, "PAYLOAD RELEASE MN B" ) );

		Add( pPEDESTAL_DRIVE_XFER_MN_A = new CircuitBreaker( _sts, "PEDESTAL DRIVE XFER MN A" ) );
		Add( pPEDESTAL_DRIVE_XFER_MN_B = new CircuitBreaker( _sts, "PEDESTAL DRIVE XFER MN B" ) );

		Add( pPAYLOAD_RELEASE_SYS_A_ARM = new LockableLever2( _sts, "PAYLOAD RELEASE SYS A ARM" ) );
		pPAYLOAD_RELEASE_SYS_A_ARM->SetLabel( 0, "OFF" );
		pPAYLOAD_RELEASE_SYS_A_ARM->SetLabel( 1, "ARM" );
		Add( pPAYLOAD_RELEASE_SYS_B_ARM = new LockableLever2( _sts, "PAYLOAD RELEASE SYS B ARM" ) );
		pPAYLOAD_RELEASE_SYS_B_ARM->SetLabel( 0, "OFF" );
		pPAYLOAD_RELEASE_SYS_B_ARM->SetLabel( 1, "ARM" );

		Add( pPAYLOAD_RELEASE_SYS_A_FIRE = new LockableLever2( _sts, "PAYLOAD RELEASE SYS A FIRE" ) );
		pPAYLOAD_RELEASE_SYS_A_FIRE->SetLabel( 0, "OFF" );
		pPAYLOAD_RELEASE_SYS_A_FIRE->SetLabel( 1, "FIRE" );
		Add( pPAYLOAD_RELEASE_SYS_B_FIRE = new LockableLever2( _sts, "PAYLOAD RELEASE SYS B FIRE" ) );
		pPAYLOAD_RELEASE_SYS_B_FIRE->SetLabel( 0, "OFF" );
		pPAYLOAD_RELEASE_SYS_B_FIRE->SetLabel( 1, "FIRE" );

		Add( pPEDESTAL_DRIVE_XFER_SYS_A_ARM = new LockableLever2( _sts, "PEDESTAL DRIVE XFER SYS A ARM" ) );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->SetLabel( 0, "OFF" );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->SetLabel( 1, "ARM" );
		Add( pPEDESTAL_DRIVE_XFER_SYS_B_ARM = new LockableLever2( _sts, "PEDESTAL DRIVE XFER SYS B ARM" ) );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->SetLabel( 0, "OFF" );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->SetLabel( 1, "ARM" );

		Add( pPEDESTAL_DRIVE_XFER_SYS_A_FIRE = new LockableLever2( _sts, "PEDESTAL DRIVE XFER SYS A FIRE" ) );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->SetLabel( 0, "OFF" );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->SetLabel( 1, "FIRE" );
		Add( pPEDESTAL_DRIVE_XFER_SYS_B_FIRE = new LockableLever2( _sts, "PEDESTAL DRIVE XFER SYS B FIRE" ) );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->SetLabel( 0, "OFF" );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->SetLabel( 1, "FIRE" );

		Add( pPAYLOAD_RELEASE_PRI_PED_SYS_A = new StandardTalkback3( _sts, "PAYLOAD RELEASE PRI PED SYS A" ) );
		Add( pPAYLOAD_RELEASE_PRI_PED_SYS_B = new StandardTalkback3( _sts, "PAYLOAD RELEASE PRI PED SYS B" ) );

		Add( pPAYLOAD_RELEASE_SEC_PED_SYS_A = new StandardTalkback3( _sts, "PAYLOAD RELEASE SEC PED SYS A" ) );
		Add( pPAYLOAD_RELEASE_SEC_PED_SYS_B = new StandardTalkback3( _sts, "PAYLOAD RELEASE SEC PED SYS B" ) );

		Add( pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_A = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER PRI PED SYS A" ) );
		Add( pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_B = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER PRI PED SYS B" ) );

		Add( pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_A = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER SEC PED SYS A" ) );
		Add( pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_B = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER SEC PED SYS B" ) );

		Add( pZo_EXTEND_PRIMARY_EXTEND = new StandardTalkback2( _sts, "Zo EXTEND PRIMARY EXTEND" ) );
		Add( pZo_EXTEND_SECONDARY_EXTEND = new StandardTalkback2( _sts, "Zo EXTEND SECONDARY EXTEND" ) );

		Add( pYo_DRIVE_POS_PRIMARY_INBD = new StandardTalkback2( _sts, "Yo DRIVE POS PRIMARY INBD" ) );
		Add( pYo_DRIVE_POS_PRIMARY_BERTHED = new StandardTalkback2( _sts, "Yo DRIVE POS PRIMARY BERTHED" ) );
		Add( pYo_DRIVE_POS_PRIMARY_OUTBD = new StandardTalkback2( _sts, "Yo DRIVE POS PRIMARY OUTBD" ) );

		Add( pYo_DRIVE_POS_SECONDARY_INBD = new StandardTalkback2( _sts, "Yo DRIVE POS SECONDARY INBD" ) );
		Add( pYo_DRIVE_POS_SECONDARY_BERTHED = new StandardTalkback2( _sts, "Yo DRIVE POS SECONDARY BERTHED" ) );
		Add( pYo_DRIVE_POS_SECONDARY_OUTBD = new StandardTalkback2( _sts, "Yo DRIVE POS SECONDARY OUTBD" ) );

		Add( pRDU_PRIMARY_REBERTH = new StandardTalkback2( _sts, "RDU PRIMARY REBERTH" ) );
		Add( pRDU_PRIMARY_STOW = new StandardTalkback2( _sts, "RDU PRIMARY STOW" ) );
		Add( pRDU_PRIMARY_DEPLOY = new StandardTalkback2( _sts, "RDU PRIMARY DEPLOY" ) );

		Add( pRDU_SECONDARY_REBERTH = new StandardTalkback2( _sts, "RDU SECONDARY REBERTH" ) );
		Add( pRDU_SECONDARY_STOW = new StandardTalkback2( _sts, "RDU SECONDARY STOW" ) );
		Add( pRDU_SECONDARY_DEPLOY = new StandardTalkback2( _sts, "RDU SECONDARY DEPLOY" ) );
		return;
	}

	PanelA7A3_SPDS::~PanelA7A3_SPDS( void )
	{
		return;
	}

	void PanelA7A3_SPDS::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.3126, 0.9499 );

		AddAIDToMouseEventList( AID_A7A3_SPDS );

		pPAYLOAD_RELEASE_MN_A->SetInitialAnimState( 1.0f );
		pPAYLOAD_RELEASE_MN_A->DefineGroup( GRP_CB1_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_MN_A->SetDirection( pull_dir );
		pPAYLOAD_RELEASE_MN_A->SetMouseRegion( AID_A7A3_SPDS, 0.093850f, 0.208096f, 0.137848f, 0.288757f );

		pPAYLOAD_RELEASE_MN_B->SetInitialAnimState( 1.0f );
		pPAYLOAD_RELEASE_MN_B->DefineGroup( GRP_CB2_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_MN_B->SetDirection( pull_dir );
		pPAYLOAD_RELEASE_MN_B->SetMouseRegion( AID_A7A3_SPDS, 0.093850f, 0.718736f, 0.137848f, 0.801004f );

		pPEDESTAL_DRIVE_XFER_MN_A->SetInitialAnimState( 1.0f );
		pPEDESTAL_DRIVE_XFER_MN_A->DefineGroup( GRP_CB3_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_MN_A->SetDirection( pull_dir );
		pPEDESTAL_DRIVE_XFER_MN_A->SetMouseRegion( AID_A7A3_SPDS, 0.432739f, 0.208096f, 0.477910f, 0.288757f );

		pPEDESTAL_DRIVE_XFER_MN_B->SetInitialAnimState( 1.0f );
		pPEDESTAL_DRIVE_XFER_MN_B->DefineGroup( GRP_CB4_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_MN_B->SetDirection( pull_dir );
		pPEDESTAL_DRIVE_XFER_MN_B->SetMouseRegion( AID_A7A3_SPDS, 0.432739f, 0.718736f, 0.477910f, 0.801004f );

		pPAYLOAD_RELEASE_SYS_A_ARM->DefineGroup( GRP_S1_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_SYS_A_ARM->SetInitialAnimState( 0.5 );
		pPAYLOAD_RELEASE_SYS_A_ARM->SetReference(_V( 0.0, 0.207143, -0.065178 ), switch_rot );
		pPAYLOAD_RELEASE_SYS_A_ARM->SetMouseRegion( AID_A7A3_SPDS, 0.188285f, 0.208096f, 0.232014f, 0.288757f );
		pPAYLOAD_RELEASE_SYS_A_ARM->SetPullDirection( pull_dir );

		pPAYLOAD_RELEASE_SYS_B_ARM->DefineGroup( GRP_S2_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_SYS_B_ARM->SetInitialAnimState( 0.5 );
		pPAYLOAD_RELEASE_SYS_B_ARM->SetReference(_V( 0.0, 0.066487, -0.020964 ), switch_rot );
		pPAYLOAD_RELEASE_SYS_B_ARM->SetMouseRegion( AID_A7A3_SPDS, 0.188285f, 0.718736f, 0.232014f, 0.801004f );
		pPAYLOAD_RELEASE_SYS_B_ARM->SetPullDirection( pull_dir );

		pPAYLOAD_RELEASE_SYS_A_FIRE->DefineGroup( GRP_S3_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_SYS_A_FIRE->SetInitialAnimState( 0.5 );
		pPAYLOAD_RELEASE_SYS_A_FIRE->SetReference(_V( 0.0, 0.207143, -0.065178 ), switch_rot );
		pPAYLOAD_RELEASE_SYS_A_FIRE->SetMouseRegion( AID_A7A3_SPDS, 0.282465f, 0.208096f, 0.326732f, 0.288757f );
		pPAYLOAD_RELEASE_SYS_A_FIRE->SetPullDirection( pull_dir );

		pPAYLOAD_RELEASE_SYS_B_FIRE->DefineGroup( GRP_S4_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_SYS_B_FIRE->SetInitialAnimState( 0.5 );
		pPAYLOAD_RELEASE_SYS_B_FIRE->SetReference(_V( 0.0, 0.066487, -0.020964 ), switch_rot );
		pPAYLOAD_RELEASE_SYS_B_FIRE->SetMouseRegion( AID_A7A3_SPDS, 0.282465f, 0.718736f, 0.326732f, 0.801004f );
		pPAYLOAD_RELEASE_SYS_B_FIRE->SetPullDirection( pull_dir );

		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->DefineGroup( GRP_S5_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->SetInitialAnimState( 0.5 );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->SetReference(_V( 0.0, 0.207143, -0.065178 ), switch_rot );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->SetMouseRegion( AID_A7A3_SPDS, 0.526752f, 0.208096f, 0.572004f, 0.288757f );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->SetPullDirection( pull_dir );

		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->DefineGroup( GRP_S6_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->SetInitialAnimState( 0.5 );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->SetReference(_V( 0.0, 0.066487, -0.020964 ), switch_rot );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->SetMouseRegion( AID_A7A3_SPDS, 0.526752f, 0.718736f, 0.572004f, 0.801004f );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->SetPullDirection( pull_dir );

		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->DefineGroup( GRP_S7_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->SetInitialAnimState( 0.5 );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->SetReference(_V( 0.0, 0.207143, -0.065178 ), switch_rot );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->SetMouseRegion( AID_A7A3_SPDS, 0.621128f, 0.208096f, 0.666291f, 0.288757f );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->SetPullDirection( pull_dir );

		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->DefineGroup( GRP_S8_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->SetInitialAnimState( 0.5 );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->SetReference(_V( 0.0, 0.066487, -0.020964 ), switch_rot );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->SetMouseRegion( AID_A7A3_SPDS, 0.621128f, 0.718736f, 0.666291f, 0.801004f );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->SetPullDirection( pull_dir );

		pPAYLOAD_RELEASE_PRI_PED_SYS_A->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_PRI_PED_SYS_B->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_SEC_PED_SYS_A->DefineMeshGroup( GetVCMeshIndex(), GRP_DS3_A7A3_SPDS_VC );
		pPAYLOAD_RELEASE_SEC_PED_SYS_B->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_A->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_B->DefineMeshGroup( GetVCMeshIndex(), GRP_DS6_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_A->DefineMeshGroup( GetVCMeshIndex(), GRP_DS7_A7A3_SPDS_VC );
		pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_B->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_A7A3_SPDS_VC );

		pZo_EXTEND_PRIMARY_EXTEND->DefineMeshGroups( GetVCMeshIndex(), GRP_DS9_U_A7A3_SPDS_VC, GRP_DS9_L_A7A3_SPDS_VC );
		pZo_EXTEND_SECONDARY_EXTEND->DefineMeshGroups( GetVCMeshIndex(), GRP_DS10_U_A7A3_SPDS_VC, GRP_DS10_L_A7A3_SPDS_VC );
		pYo_DRIVE_POS_PRIMARY_INBD->DefineMeshGroups( GetVCMeshIndex(), GRP_DS11_U_A7A3_SPDS_VC, GRP_DS11_L_A7A3_SPDS_VC );
		pYo_DRIVE_POS_PRIMARY_BERTHED->DefineMeshGroups( GetVCMeshIndex(), GRP_DS12_U_A7A3_SPDS_VC, GRP_DS12_L_A7A3_SPDS_VC );
		pYo_DRIVE_POS_PRIMARY_OUTBD->DefineMeshGroups( GetVCMeshIndex(), GRP_DS13_U_A7A3_SPDS_VC, GRP_DS13_L_A7A3_SPDS_VC );
		pYo_DRIVE_POS_SECONDARY_INBD->DefineMeshGroups( GetVCMeshIndex(), GRP_DS14_U_A7A3_SPDS_VC, GRP_DS14_L_A7A3_SPDS_VC );
		pYo_DRIVE_POS_SECONDARY_BERTHED->DefineMeshGroups( GetVCMeshIndex(), GRP_DS15_U_A7A3_SPDS_VC, GRP_DS15_L_A7A3_SPDS_VC );
		pYo_DRIVE_POS_SECONDARY_OUTBD->DefineMeshGroups( GetVCMeshIndex(), GRP_DS16_U_A7A3_SPDS_VC, GRP_DS16_L_A7A3_SPDS_VC );
		pRDU_PRIMARY_REBERTH->DefineMeshGroups( GetVCMeshIndex(), GRP_DS17_U_A7A3_SPDS_VC, GRP_DS17_L_A7A3_SPDS_VC );
		pRDU_PRIMARY_STOW->DefineMeshGroups( GetVCMeshIndex(), GRP_DS18_U_A7A3_SPDS_VC, GRP_DS18_L_A7A3_SPDS_VC );
		pRDU_PRIMARY_DEPLOY->DefineMeshGroups( GetVCMeshIndex(), GRP_DS19_U_A7A3_SPDS_VC, GRP_DS19_L_A7A3_SPDS_VC );
		pRDU_SECONDARY_REBERTH->DefineMeshGroups( GetVCMeshIndex(), GRP_DS20_U_A7A3_SPDS_VC, GRP_DS20_L_A7A3_SPDS_VC );
		pRDU_SECONDARY_STOW->DefineMeshGroups( GetVCMeshIndex(), GRP_DS21_U_A7A3_SPDS_VC, GRP_DS21_L_A7A3_SPDS_VC );
		pRDU_SECONDARY_DEPLOY->DefineMeshGroups( GetVCMeshIndex(), GRP_DS22_U_A7A3_SPDS_VC, GRP_DS22_L_A7A3_SPDS_VC );
		return;
	}

	void PanelA7A3_SPDS::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A7A3_SPDS, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A7A3_SPDS,
			_V( 0.0, 0.274498, -0.086286 ) + ofs, _V( -0.520441, 0.274498, -0.086286 ) + ofs,
			_V( 0.0, 0.0, 0.0 ) + ofs, _V( -0.520441, 0.0, 0.0 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA7A3_SPDS::Realize( void )
	{
		AtlantisPanel::Realize();

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "A7A3_SPDS_internal", 16 );
		pPAYLOAD_RELEASE_MN_A->Connect( pBundle, 0 );
		pPAYLOAD_RELEASE_MN_B->Connect( pBundle, 1 );
		pPAYLOAD_RELEASE_SYS_A_ARM->ConnectPort( 1, pBundle, 2 );
		pPAYLOAD_RELEASE_SYS_B_ARM->ConnectPort( 1, pBundle, 3 );
		pPAYLOAD_RELEASE_SYS_A_FIRE->ConnectPort( 1, pBundle, 4 );
		pPAYLOAD_RELEASE_SYS_B_FIRE->ConnectPort( 1, pBundle, 5 );
		pPEDESTAL_DRIVE_XFER_MN_A->Connect( pBundle, 6 );
		pPEDESTAL_DRIVE_XFER_MN_B->Connect( pBundle, 7 );
		pPEDESTAL_DRIVE_XFER_SYS_A_ARM->ConnectPort( 1, pBundle, 8 );
		pPEDESTAL_DRIVE_XFER_SYS_B_ARM->ConnectPort( 1, pBundle, 9 );
		pPEDESTAL_DRIVE_XFER_SYS_A_FIRE->ConnectPort( 1, pBundle, 10 );
		pPEDESTAL_DRIVE_XFER_SYS_B_FIRE->ConnectPort( 1, pBundle, 11 );

		dipPAYLOAD_RELEASE_MN_A.Connect( pBundle, 0 );
		dipPAYLOAD_RELEASE_MN_B.Connect( pBundle, 1 );
		dipPAYLOAD_RELEASE_SYS_A_ARM.Connect( pBundle, 2 );
		dipPAYLOAD_RELEASE_SYS_B_ARM.Connect( pBundle, 3 );
		dipPAYLOAD_RELEASE_SYS_A_FIRE.Connect( pBundle, 4 );
		dipPAYLOAD_RELEASE_SYS_B_FIRE.Connect( pBundle, 5 );
		dipPEDESTAL_DRIVE_XFER_MN_A.Connect( pBundle, 6 );
		dipPEDESTAL_DRIVE_XFER_MN_B.Connect( pBundle, 7 );
		dipPEDESTAL_DRIVE_XFER_SYS_A_ARM.Connect( pBundle, 8 );
		dipPEDESTAL_DRIVE_XFER_SYS_B_ARM.Connect( pBundle, 9 );
		dipPEDESTAL_DRIVE_XFER_SYS_A_FIRE.Connect( pBundle, 10 );
		dipPEDESTAL_DRIVE_XFER_SYS_B_FIRE.Connect( pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "SPDS_Pyros", 16 );
		dopPAYLOAD_RELEASE_SYS_A_ARM.Connect( pBundle, 0 );
		dopPAYLOAD_RELEASE_SYS_B_ARM.Connect( pBundle, 1 );
		dopPAYLOAD_RELEASE_SYS_A_FIRE.Connect( pBundle, 2 );
		dopPAYLOAD_RELEASE_SYS_B_FIRE.Connect( pBundle, 3 );
		dopPEDESTAL_DRIVE_XFER_SYS_A_ARM.Connect( pBundle, 4 );
		dopPEDESTAL_DRIVE_XFER_SYS_B_ARM.Connect( pBundle, 5 );
		dopPEDESTAL_DRIVE_XFER_SYS_A_FIRE.Connect( pBundle, 6 );
		dopPEDESTAL_DRIVE_XFER_SYS_B_FIRE.Connect( pBundle, 7 );

		pBundle = STS()->BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
		pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_B->SetInput( 0, pBundle, 1, TB_DIS );
		pPAYLOAD_RELEASE_SEC_PED_SYS_A->SetInput( 1, pBundle, 3, TB_REL );
		pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_B->SetInput( 1, pBundle, 5, TB_ENG );
		pPAYLOAD_RELEASE_SEC_PED_SYS_A->SetInput( 0, pBundle, 7, TB_LAT );
		pPAYLOAD_RELEASE_PRI_PED_SYS_A->SetInput( 1, pBundle, 9, TB_REL );
		pPAYLOAD_RELEASE_SEC_PED_SYS_B->SetInput( 1, pBundle, 11, TB_REL );
		pPAYLOAD_RELEASE_PRI_PED_SYS_A->SetInput( 0, pBundle, 13, TB_LAT );
		pPAYLOAD_RELEASE_SEC_PED_SYS_B->SetInput( 0, pBundle, 15, TB_LAT );

		pBundle = STS()->BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
		pPAYLOAD_RELEASE_PRI_PED_SYS_B->SetInput( 0, pBundle, 4, TB_LAT );
		pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_A->SetInput( 0, pBundle, 5, TB_DIS );

		pBundle = STS()->BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
		pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_B->SetInput( 1, pBundle, 0, TB_ENG );
		pPAYLOAD_RELEASE_PRI_PED_SYS_B->SetInput( 1, pBundle, 1, TB_REL );
		pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_A->SetInput( 1, pBundle, 2, TB_ENG );
		pPEDESTAL_DRIVE_XFER_PRI_PED_SYS_A->SetInput( 1, pBundle, 3, TB_ENG );
		pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_B->SetInput( 0, pBundle, 4, TB_DIS );
		pPEDESTAL_DRIVE_XFER_SEC_PED_SYS_A->SetInput( 0, pBundle, 5, TB_DIS );

		pBundle = STS()->BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
		pZo_EXTEND_SECONDARY_EXTEND->SetInput( pBundle, 2, TB_GRAY );
		pZo_EXTEND_PRIMARY_EXTEND->SetInput( pBundle, 6, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
		pYo_DRIVE_POS_PRIMARY_BERTHED->SetInput( pBundle, 0, TB_GRAY );
		pYo_DRIVE_POS_PRIMARY_INBD->SetInput( pBundle, 1, TB_GRAY );
		pYo_DRIVE_POS_PRIMARY_OUTBD->SetInput( pBundle, 4, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
		pYo_DRIVE_POS_SECONDARY_BERTHED->SetInput( pBundle, 0, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
		pYo_DRIVE_POS_SECONDARY_INBD->SetInput( pBundle, 0, TB_GRAY );
		pYo_DRIVE_POS_SECONDARY_OUTBD->SetInput( pBundle, 1, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
		pRDU_PRIMARY_REBERTH->SetInput( pBundle, 2, TB_GRAY );
		pRDU_PRIMARY_DEPLOY->SetInput( pBundle, 3, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
		pRDU_PRIMARY_STOW->SetInput( pBundle, 0, TB_GRAY );

		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
		pRDU_SECONDARY_REBERTH->SetInput( pBundle, 0, TB_GRAY );
		pBundle = STS()->BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
		pRDU_SECONDARY_STOW->SetInput( pBundle, 0, TB_GRAY );
		pRDU_SECONDARY_DEPLOY->SetInput( pBundle, 1, TB_GRAY );
		return;
	}
	
	void PanelA7A3_SPDS::OnPreStep( double simt, double simdt, double mjd )
	{
		if (dipPAYLOAD_RELEASE_MN_A && dipPAYLOAD_RELEASE_SYS_A_ARM)
		{
			dopPAYLOAD_RELEASE_SYS_A_ARM.SetLine();
			if (dipPAYLOAD_RELEASE_SYS_A_FIRE) dopPAYLOAD_RELEASE_SYS_A_FIRE.SetLine();
			else dopPAYLOAD_RELEASE_SYS_A_FIRE.ResetLine();
		}
		else
		{
			dopPAYLOAD_RELEASE_SYS_A_ARM.ResetLine();
			dopPAYLOAD_RELEASE_SYS_A_FIRE.ResetLine();
		}
		if (dipPAYLOAD_RELEASE_MN_B && dipPAYLOAD_RELEASE_SYS_B_ARM)
		{
			dopPAYLOAD_RELEASE_SYS_B_ARM.SetLine();
			if (dipPAYLOAD_RELEASE_SYS_B_FIRE) dopPAYLOAD_RELEASE_SYS_B_FIRE.SetLine();
			else dopPAYLOAD_RELEASE_SYS_B_FIRE.ResetLine();
		}
		else
		{
			dopPAYLOAD_RELEASE_SYS_B_ARM.ResetLine();
			dopPAYLOAD_RELEASE_SYS_B_FIRE.ResetLine();
		}

		if (dipPEDESTAL_DRIVE_XFER_MN_A && dipPEDESTAL_DRIVE_XFER_SYS_A_ARM)
		{
			dopPEDESTAL_DRIVE_XFER_SYS_A_ARM.SetLine();
			if (dipPEDESTAL_DRIVE_XFER_SYS_A_FIRE) dopPEDESTAL_DRIVE_XFER_SYS_A_FIRE.SetLine();
			else dopPEDESTAL_DRIVE_XFER_SYS_A_FIRE.ResetLine();
		}
		else
		{
			dopPEDESTAL_DRIVE_XFER_SYS_A_ARM.ResetLine();
			dopPEDESTAL_DRIVE_XFER_SYS_A_FIRE.ResetLine();
		}
		if (dipPEDESTAL_DRIVE_XFER_MN_B && dipPEDESTAL_DRIVE_XFER_SYS_B_ARM)
		{
			dopPEDESTAL_DRIVE_XFER_SYS_B_ARM.SetLine();
			if (dipPEDESTAL_DRIVE_XFER_SYS_B_FIRE) dopPEDESTAL_DRIVE_XFER_SYS_B_FIRE.SetLine();
			else dopPEDESTAL_DRIVE_XFER_SYS_B_FIRE.ResetLine();
		}
		else
		{
			dopPEDESTAL_DRIVE_XFER_SYS_B_ARM.ResetLine();
			dopPEDESTAL_DRIVE_XFER_SYS_B_FIRE.ResetLine();
		}
		return;
	}
}
