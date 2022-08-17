/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/08/05   GLS
********************************************/
#include "PanelO7.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_o7.h"


namespace vc
{
	PanelO7::PanelO7( Atlantis* _sts ):AtlantisPanel( _sts, "O7" )
	{
		DefineMesh( MESHNAME_PANELO7 );

		Add( pAftLeftRCSHePressA = new StdSwitch3( _sts, "Aft Left RCS He Press A" ) );
		pAftLeftRCSHePressA->SetLabel( 0, "CLOSE" );
		pAftLeftRCSHePressA->SetLabel( 1, "GPC" );
		pAftLeftRCSHePressA->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSHePressB = new StdSwitch3( _sts, "Aft Left RCS He Press B" ) );
		pAftLeftRCSHePressB->SetLabel( 0, "CLOSE" );
		pAftLeftRCSHePressB->SetLabel( 1, "GPC" );
		pAftLeftRCSHePressB->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSTankIsolation12 = new StdSwitch3( _sts, "Aft Left RCS Tank Isolation 1/2" ) );
		pAftLeftRCSTankIsolation12->SetLabel( 0, "CLOSE" );
		pAftLeftRCSTankIsolation12->SetLabel( 1, "GPC" );
		pAftLeftRCSTankIsolation12->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSTankIsolation345A = new StdSwitch3( _sts, "Aft Left RCS Tank Isolation 3/4/5 A" ) );
		pAftLeftRCSTankIsolation345A->SetLabel( 0, "CLOSE" );
		pAftLeftRCSTankIsolation345A->SetLabel( 1, "GPC" );
		pAftLeftRCSTankIsolation345A->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSTankIsolation345B = new StdSwitch3( _sts, "Aft Left RCS Tank Isolation 3/4/5 B" ) );
		pAftLeftRCSTankIsolation345B->SetLabel( 0, "CLOSE" );
		pAftLeftRCSTankIsolation345B->SetLabel( 1, "GPC" );
		pAftLeftRCSTankIsolation345B->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSManifoldIsolation1 = new StdSwitch3( _sts, "Aft Left RCS Manifold Isolation 1" ) );
		pAftLeftRCSManifoldIsolation1->SetLabel( 0, "CLOSE" );
		pAftLeftRCSManifoldIsolation1->SetLabel( 1, "GPC" );
		pAftLeftRCSManifoldIsolation1->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSManifoldIsolation2 = new StdSwitch3( _sts, "Aft Left RCS Manifold Isolation 2" ) );
		pAftLeftRCSManifoldIsolation2->SetLabel( 0, "CLOSE" );
		pAftLeftRCSManifoldIsolation2->SetLabel( 1, "GPC" );
		pAftLeftRCSManifoldIsolation2->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSManifoldIsolation3 = new StdSwitch3( _sts, "Aft Left RCS Manifold Isolation 3" ) );
		pAftLeftRCSManifoldIsolation3->SetLabel( 0, "CLOSE" );
		pAftLeftRCSManifoldIsolation3->SetLabel( 1, "GPC" );
		pAftLeftRCSManifoldIsolation3->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSManifoldIsolation4 = new StdSwitch3( _sts, "Aft Left RCS Manifold Isolation 4" ) );
		pAftLeftRCSManifoldIsolation4->SetLabel( 0, "CLOSE" );
		pAftLeftRCSManifoldIsolation4->SetLabel( 1, "GPC" );
		pAftLeftRCSManifoldIsolation4->SetLabel( 2, "OPEN" );

		Add( pAftLeftRCSManifoldIsolation5 = new StdSwitch3( _sts, "Aft Left RCS Manifold Isolation 5" ) );
		pAftLeftRCSManifoldIsolation5->SetLabel( 0, "CLOSE" );
		pAftLeftRCSManifoldIsolation5->SetLabel( 1, "GPC" );
		pAftLeftRCSManifoldIsolation5->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSHePressA = new StdSwitch3( _sts, "Aft Right RCS He Press A" ) );
		pAftRightRCSHePressA->SetLabel( 0, "CLOSE" );
		pAftRightRCSHePressA->SetLabel( 1, "GPC" );
		pAftRightRCSHePressA->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSHePressB = new StdSwitch3( _sts, "Aft Right RCS He Press B" ) );
		pAftRightRCSHePressB->SetLabel( 0, "CLOSE" );
		pAftRightRCSHePressB->SetLabel( 1, "GPC" );
		pAftRightRCSHePressB->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSTankIsolation12 = new StdSwitch3( _sts, "Aft Right RCS Tank Isolation 1/2" ) );
		pAftRightRCSTankIsolation12->SetLabel( 0, "CLOSE" );
		pAftRightRCSTankIsolation12->SetLabel( 1, "GPC" );
		pAftRightRCSTankIsolation12->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSTankIsolation345A = new StdSwitch3( _sts, "Aft Right RCS Tank Isolation 3/4/5 A" ) );
		pAftRightRCSTankIsolation345A->SetLabel( 0, "CLOSE" );
		pAftRightRCSTankIsolation345A->SetLabel( 1, "GPC" );
		pAftRightRCSTankIsolation345A->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSTankIsolation345B = new StdSwitch3( _sts, "Aft Right RCS Tank Isolation 3/4/5 B" ) );
		pAftRightRCSTankIsolation345B->SetLabel( 0, "CLOSE" );
		pAftRightRCSTankIsolation345B->SetLabel( 1, "GPC" );
		pAftRightRCSTankIsolation345B->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSManifoldIsolation1 = new StdSwitch3( _sts, "Aft Right RCS Manifold Isolation 1" ) );
		pAftRightRCSManifoldIsolation1->SetLabel( 0, "CLOSE" );
		pAftRightRCSManifoldIsolation1->SetLabel( 1, "GPC" );
		pAftRightRCSManifoldIsolation1->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSManifoldIsolation2 = new StdSwitch3( _sts, "Aft Right RCS Manifold Isolation 2" ) );
		pAftRightRCSManifoldIsolation2->SetLabel( 0, "CLOSE" );
		pAftRightRCSManifoldIsolation2->SetLabel( 1, "GPC" );
		pAftRightRCSManifoldIsolation2->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSManifoldIsolation3 = new StdSwitch3( _sts, "Aft Right RCS Manifold Isolation 3" ) );
		pAftRightRCSManifoldIsolation3->SetLabel( 0, "CLOSE" );
		pAftRightRCSManifoldIsolation3->SetLabel( 1, "GPC" );
		pAftRightRCSManifoldIsolation3->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSManifoldIsolation4 = new StdSwitch3( _sts, "Aft Right RCS Manifold Isolation 4" ) );
		pAftRightRCSManifoldIsolation4->SetLabel( 0, "CLOSE" );
		pAftRightRCSManifoldIsolation4->SetLabel( 1, "GPC" );
		pAftRightRCSManifoldIsolation4->SetLabel( 2, "OPEN" );

		Add( pAftRightRCSManifoldIsolation5 = new StdSwitch3( _sts, "Aft Right RCS Manifold Isolation 5" ) );
		pAftRightRCSManifoldIsolation5->SetLabel( 0, "CLOSE" );
		pAftRightRCSManifoldIsolation5->SetLabel( 1, "GPC" );
		pAftRightRCSManifoldIsolation5->SetLabel( 2, "OPEN" );

		Add( pLeftRCSCrossfeed12 = new StdSwitch3( _sts, "Left RCS Crossfeed 1/2" ) );
		pLeftRCSCrossfeed12->SetLabel( 0, "CLOSE" );
		pLeftRCSCrossfeed12->SetLabel( 1, "GPC" );
		pLeftRCSCrossfeed12->SetLabel( 2, "OPEN" );

		Add( pLeftRCSCrossfeed345 = new StdSwitch3( _sts, "Left RCS Crossfeed 3/4/5" ) );
		pLeftRCSCrossfeed345->SetLabel( 0, "CLOSE" );
		pLeftRCSCrossfeed345->SetLabel( 1, "GPC" );
		pLeftRCSCrossfeed345->SetLabel( 2, "OPEN" );

		Add( pRightRCSCrossfeed12 = new StdSwitch3( _sts, "Right RCS Crossfeed 1/2" ) );
		pRightRCSCrossfeed12->SetLabel( 0, "CLOSE" );
		pRightRCSCrossfeed12->SetLabel( 1, "GPC" );
		pRightRCSCrossfeed12->SetLabel( 2, "OPEN" );

		Add( pRightRCSCrossfeed345 = new StdSwitch3( _sts, "Right RCS Crossfeed 3/4/5" ) );
		pRightRCSCrossfeed345->SetLabel( 0, "CLOSE" );
		pRightRCSCrossfeed345->SetLabel( 1, "GPC" );
		pRightRCSCrossfeed345->SetLabel( 2, "OPEN" );

		Add( MasterRCSCrossfeed = new LockableLever3( _sts, "Master RCS Crossfeed" ) );
		MasterRCSCrossfeed->SetLabel( 0, "FEED_FROM_RIGHT" );
		MasterRCSCrossfeed->SetLabel( 1, "OFF" );
		MasterRCSCrossfeed->SetLabel( 2, "FEED_FROM_LEFT" );

		Add( pAftLeftRCSHePressA_TB = new StandardTalkback3( _sts, "Aft Left RCS He Press A TB" ) );
		Add( pAftLeftRCSHePressB_TB = new StandardTalkback3( _sts, "Aft Left RCS He Press B TB" ) );
		Add( pAftLeftRCSTankIsolation12_TB = new StandardTalkback3( _sts, "Aft Left RCS Tank Isolation 1/2 TB" ) );
		Add( pAftLeftRCSTankIsolation345A_TB = new StandardTalkback3( _sts, "Aft Left RCS Tank Isolation 3/4/5 A TB" ) );
		Add( pAftLeftRCSTankIsolation345B_TB = new StandardTalkback3( _sts, "Aft Left RCS Tank Isolation 3/4/5 B TB" ) );
		Add( pAftLeftRCSManifoldIsolation1_TB = new StandardTalkback3( _sts, "Aft Left RCS Manifold Isolation 1 TB" ) );
		Add( pAftLeftRCSManifoldIsolation2_TB = new StandardTalkback3( _sts, "Aft Left RCS Manifold Isolation 2 TB" ) );
		Add( pAftLeftRCSManifoldIsolation3_TB = new StandardTalkback3( _sts, "Aft Left RCS Manifold Isolation 3 TB" ) );
		Add( pAftLeftRCSManifoldIsolation4_TB = new StandardTalkback3( _sts, "Aft Left RCS Manifold Isolation 4 TB" ) );
		Add( pAftLeftRCSManifoldIsolation5_TB = new StandardTalkback3( _sts, "Aft Left RCS Manifold Isolation 5 TB" ) );
		Add( pAftRightRCSHePressA_TB = new StandardTalkback3( _sts, "Aft Right RCS He Press A TB" ) );
		Add( pAftRightRCSHePressB_TB = new StandardTalkback3( _sts, "Aft Right RCS He Press B TB" ) );
		Add( pAftRightRCSTankIsolation12_TB = new StandardTalkback3( _sts, "Aft Right RCS Tank Isolation 1/2 TB" ) );
		Add( pAftRightRCSTankIsolation345A_TB = new StandardTalkback3( _sts, "Aft Right RCS Tank Isolation 3/4/5 A TB" ) );
		Add( pAftRightRCSTankIsolation345B_TB = new StandardTalkback3( _sts, "Aft Right RCS Tank Isolation 3/4/5 B TB" ) );
		Add( pAftRightRCSManifoldIsolation1_TB = new StandardTalkback3( _sts, "Aft Right RCS Manifold Isolation 1 TB" ) );
		Add( pAftRightRCSManifoldIsolation2_TB = new StandardTalkback3( _sts, "Aft Right RCS Manifold Isolation 2 TB" ) );
		Add( pAftRightRCSManifoldIsolation3_TB = new StandardTalkback3( _sts, "Aft Right RCS Manifold Isolation 3 TB" ) );
		Add( pAftRightRCSManifoldIsolation4_TB = new StandardTalkback3( _sts, "Aft Right RCS Manifold Isolation 4 TB" ) );
		Add( pAftRightRCSManifoldIsolation5_TB = new StandardTalkback3( _sts, "Aft Right RCS Manifold Isolation 5 TB" ) );
		Add( pLeftRCSCrossfeed12_TB = new StandardTalkback3( _sts, "Left RCS Crossfeed 1/2 TB" ) );
		Add( pLeftRCSCrossfeed345_TB = new StandardTalkback3( _sts, "Left RCS Crossfeed 3/4/5 TB" ) );
		Add( pRightRCSCrossfeed12_TB = new StandardTalkback3( _sts, "Right RCS Crossfeed 1/2 TB" ) );
		Add( pRightRCSCrossfeed345_TB = new StandardTalkback3( _sts, "Right RCS Crossfeed 3/4/5 TB" ) );
	}

	PanelO7::~PanelO7()
	{
	}

	void PanelO7::DefineVC()
	{
		VECTOR3 switch_rot_horiz = _V( 1.0, 0.0, 0.0 );
		VECTOR3 switch_rot_vert = _V( 0.0, 0.235651, -0.971838 );
		VECTOR3 pull_dir = _V( 0.0, -0.971838, -0.235651 );

		AddAIDToMouseEventList( AID_O7 );

		pAftLeftRCSHePressA->SetInitialAnimState( 0.5f );
		pAftLeftRCSHePressA->DefineGroup( GRP_S10_O7_VC );
		pAftLeftRCSHePressA->SetReference( _V( -0.154462, 3.12216, 13.87245 ), switch_rot_horiz );
		pAftLeftRCSHePressA->SetMouseRegion( AID_O7, 0.140171f, 0.360183f, 0.197005f, 0.392066f );

		pAftLeftRCSHePressB->SetInitialAnimState( 0.5f );
		pAftLeftRCSHePressB->DefineGroup( GRP_S11_O7_VC );
		pAftLeftRCSHePressB->SetReference( _V( -0.154462, 3.12216, 13.87245 ), switch_rot_horiz );
		pAftLeftRCSHePressB->SetMouseRegion( AID_O7, 0.291188f, 0.360183f, 0.348573f, 0.392066f );

		pAftLeftRCSTankIsolation12->SetInitialAnimState( 0.5f );
		pAftLeftRCSTankIsolation12->DefineGroup( GRP_S16_O7_VC );
		pAftLeftRCSTankIsolation12->SetReference( _V( -0.155858, 3.09493, 13.98455 ), switch_rot_horiz );
		pAftLeftRCSTankIsolation12->SetMouseRegion( AID_O7, 0.135592f, 0.518592f, 0.193928f, 0.553144f );

		pAftLeftRCSTankIsolation345A->SetInitialAnimState( 0.5f );
		pAftLeftRCSTankIsolation345A->DefineGroup( GRP_S17_O7_VC );
		pAftLeftRCSTankIsolation345A->SetReference( _V( -0.155858, 3.09493, 13.98455 ), switch_rot_horiz );
		pAftLeftRCSTankIsolation345A->SetMouseRegion( AID_O7, 0.286117f, 0.518592f, 0.342784f, 0.553144f );

		pAftLeftRCSTankIsolation345B->SetInitialAnimState( 0.5f );
		pAftLeftRCSTankIsolation345B->DefineGroup( GRP_S18_O7_VC );
		pAftLeftRCSTankIsolation345B->SetReference( _V( -0.155858, 3.09493, 13.98455 ), switch_rot_horiz );
		pAftLeftRCSTankIsolation345B->SetMouseRegion( AID_O7, 0.363307f, 0.518592f, 0.421768f, 0.553144f );

		pAftLeftRCSManifoldIsolation1->SetInitialAnimState( 0.5f );
		pAftLeftRCSManifoldIsolation1->DefineGroup( GRP_S22_O7_VC );
		pAftLeftRCSManifoldIsolation1->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftLeftRCSManifoldIsolation1->SetMouseRegion( AID_O7, 0.098384f, 0.637725f, 0.157725f, 0.671919f );
		
		pAftLeftRCSManifoldIsolation2->SetInitialAnimState( 0.5f );
		pAftLeftRCSManifoldIsolation2->DefineGroup( GRP_S23_O7_VC );
		pAftLeftRCSManifoldIsolation2->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftLeftRCSManifoldIsolation2->SetMouseRegion( AID_O7, 0.177685f, 0.637725f, 0.236576f, 0.671919f );

		pAftLeftRCSManifoldIsolation3->SetInitialAnimState( 0.5f );
		pAftLeftRCSManifoldIsolation3->DefineGroup( GRP_S24_O7_VC );
		pAftLeftRCSManifoldIsolation3->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftLeftRCSManifoldIsolation3->SetMouseRegion( AID_O7, 0.250809f, 0.637725f, 0.309853f, 0.671919f );

		pAftLeftRCSManifoldIsolation4->SetInitialAnimState( 0.5f );
		pAftLeftRCSManifoldIsolation4->DefineGroup( GRP_S25_O7_VC );
		pAftLeftRCSManifoldIsolation4->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftLeftRCSManifoldIsolation4->SetMouseRegion( AID_O7, 0.325026f, 0.637725f, 0.383502f, 0.671919f );

		pAftLeftRCSManifoldIsolation5->SetInitialAnimState( 0.5f );
		pAftLeftRCSManifoldIsolation5->DefineGroup( GRP_S26_O7_VC );
		pAftLeftRCSManifoldIsolation5->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftLeftRCSManifoldIsolation5->SetMouseRegion( AID_O7, 0.400060f, 0.637725f, 0.456608f, 0.671919f );

		pAftRightRCSHePressA->SetInitialAnimState( 0.5f );
		pAftRightRCSHePressA->DefineGroup( GRP_S13_O7_VC );
		pAftRightRCSHePressA->SetReference( _V( -0.154462, 3.12216, 13.87245 ), switch_rot_horiz );
		pAftRightRCSHePressA->SetMouseRegion( AID_O7, 0.586058f, 0.360183f, 0.645939f, 0.392066f );

		pAftRightRCSHePressB->SetInitialAnimState( 0.5f );
		pAftRightRCSHePressB->DefineGroup( GRP_S14_O7_VC );
		pAftRightRCSHePressB->SetReference( _V( -0.154462, 3.12216, 13.87245 ), switch_rot_horiz );
		pAftRightRCSHePressB->SetMouseRegion( AID_O7, 0.734887f, 0.360183f, 0.792860f, 0.392066f );
		
		pAftRightRCSTankIsolation12->SetInitialAnimState( 0.5f );
		pAftRightRCSTankIsolation12->DefineGroup( GRP_S19_O7_VC );
		pAftRightRCSTankIsolation12->SetReference( _V( -0.155858, 3.09493, 13.98455 ), switch_rot_horiz );
		pAftRightRCSTankIsolation12->SetMouseRegion( AID_O7, 0.582453f, 0.518592f, 0.641027f, 0.553144f );

		pAftRightRCSTankIsolation345A->SetInitialAnimState( 0.5f );
		pAftRightRCSTankIsolation345A->DefineGroup( GRP_S20_O7_VC );
		pAftRightRCSTankIsolation345A->SetReference( _V( -0.155858, 3.09493, 13.98455 ), switch_rot_horiz );
		pAftRightRCSTankIsolation345A->SetMouseRegion( AID_O7, 0.732710f, 0.518592f, 0.791552f, 0.553144f );

		pAftRightRCSTankIsolation345B->SetInitialAnimState( 0.5f );
		pAftRightRCSTankIsolation345B->DefineGroup( GRP_S21_O7_VC );
		pAftRightRCSTankIsolation345B->SetReference( _V( -0.155858, 3.09493, 13.98455 ), switch_rot_horiz );
		pAftRightRCSTankIsolation345B->SetMouseRegion( AID_O7, 0.809440f, 0.518592f, 0.870444f, 0.553144f );

		pAftRightRCSManifoldIsolation1->SetInitialAnimState( 0.5f );
		pAftRightRCSManifoldIsolation1->DefineGroup( GRP_S27_O7_VC );
		pAftRightRCSManifoldIsolation1->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftRightRCSManifoldIsolation1->SetMouseRegion( AID_O7, 0.545931f, 0.637725f, 0.603932f, 0.671919f );

		pAftRightRCSManifoldIsolation2->SetInitialAnimState( 0.5f );
		pAftRightRCSManifoldIsolation2->DefineGroup( GRP_S28_O7_VC );
		pAftRightRCSManifoldIsolation2->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftRightRCSManifoldIsolation2->SetMouseRegion( AID_O7, 0.623333f, 0.637725f, 0.683999f, 0.671919f );

		pAftRightRCSManifoldIsolation3->SetInitialAnimState( 0.5f );
		pAftRightRCSManifoldIsolation3->DefineGroup( GRP_S29_O7_VC );
		pAftRightRCSManifoldIsolation3->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftRightRCSManifoldIsolation3->SetMouseRegion( AID_O7, 0.697731f, 0.637725f, 0.756796f, 0.671919f );
		
		pAftRightRCSManifoldIsolation4->SetInitialAnimState( 0.5f );
		pAftRightRCSManifoldIsolation4->DefineGroup( GRP_S30_O7_VC );
		pAftRightRCSManifoldIsolation4->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftRightRCSManifoldIsolation4->SetMouseRegion( AID_O7, 0.774223f, 0.637725f, 0.834145f, 0.671919f );

		pAftRightRCSManifoldIsolation5->SetInitialAnimState( 0.5f );
		pAftRightRCSManifoldIsolation5->DefineGroup( GRP_S31_O7_VC );
		pAftRightRCSManifoldIsolation5->SetReference( _V( -0.170258, 3.074, 14.070351 ), switch_rot_horiz );
		pAftRightRCSManifoldIsolation5->SetMouseRegion( AID_O7, 0.846488f, 0.637725f, 0.906143f, 0.671919f );

		pLeftRCSCrossfeed12->SetInitialAnimState( 0.5f );
		pLeftRCSCrossfeed12->DefineGroup( GRP_S32_O7_VC );
		pLeftRCSCrossfeed12->SetReference( _V( -0.139703, 3.05228, 14.15895 ), switch_rot_horiz );
		pLeftRCSCrossfeed12->SetMouseRegion( AID_O7, 0.171492f, 0.767038f, 0.231432f, 0.800024f );

		pLeftRCSCrossfeed345->SetInitialAnimState( 0.5f );
		pLeftRCSCrossfeed345->DefineGroup( GRP_S33_O7_VC );
		pLeftRCSCrossfeed345->SetReference( _V( -0.139703, 3.05228, 14.15895 ), switch_rot_horiz );
		pLeftRCSCrossfeed345->SetMouseRegion( AID_O7, 0.321980f, 0.767038f, 0.381836f, 0.800024f );

		pRightRCSCrossfeed12->SetInitialAnimState( 0.5f );
		pRightRCSCrossfeed12->DefineGroup( GRP_S34_O7_VC );
		pRightRCSCrossfeed12->SetReference( _V( -0.139703, 3.05228, 14.15895 ), switch_rot_horiz );
		pRightRCSCrossfeed12->SetMouseRegion( AID_O7, 0.621948f, 0.767038f, 0.682284f, 0.800024f );

		pRightRCSCrossfeed345->SetInitialAnimState( 0.5f );
		pRightRCSCrossfeed345->DefineGroup( GRP_S35_O7_VC );
		pRightRCSCrossfeed345->SetReference( _V( -0.139703, 3.05228, 14.15895 ), switch_rot_horiz );
		pRightRCSCrossfeed345->SetMouseRegion( AID_O7, 0.771669f, 0.767038f, 0.827681f, 0.800024f );
		
		MasterRCSCrossfeed->SetInitialAnimState( 0.5f );
		MasterRCSCrossfeed->DefineGroup( GRP_S36_O7_VC );
		MasterRCSCrossfeed->SetReference( _V( -0.006087, 3.048326, 14.158267 ), switch_rot_vert );
		MasterRCSCrossfeed->SetMouseRegion( AID_O7, 0.470791f, 0.766193f, 0.535210f, 0.799454f );
		MasterRCSCrossfeed->SetPullDirection( pull_dir );
		MasterRCSCrossfeed->SetOrientation( true );

		pAftLeftRCSHePressA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_O7_VC );
		pAftLeftRCSHePressB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_O7_VC );
		pAftLeftRCSTankIsolation12_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS7_O7_VC );
		pAftLeftRCSTankIsolation345A_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_O7_VC );
		pAftLeftRCSTankIsolation345B_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS9_O7_VC );
		pAftLeftRCSManifoldIsolation1_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS13_O7_VC );
		pAftLeftRCSManifoldIsolation2_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS14_O7_VC );
		pAftLeftRCSManifoldIsolation3_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS15_O7_VC );
		pAftLeftRCSManifoldIsolation4_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS16_O7_VC );
		pAftLeftRCSManifoldIsolation5_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS17_O7_VC );
		pAftRightRCSHePressA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_O7_VC );
		pAftRightRCSHePressB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_O7_VC );
		pAftRightRCSTankIsolation12_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS10_O7_VC );
		pAftRightRCSTankIsolation345A_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS11_O7_VC );
		pAftRightRCSTankIsolation345B_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS12_O7_VC );
		pAftRightRCSManifoldIsolation1_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS18_O7_VC );
		pAftRightRCSManifoldIsolation2_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS19_O7_VC );
		pAftRightRCSManifoldIsolation3_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS20_O7_VC );
		pAftRightRCSManifoldIsolation4_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS21_O7_VC );
		pAftRightRCSManifoldIsolation5_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS22_O7_VC );
		pLeftRCSCrossfeed12_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS23_O7_VC );
		pLeftRCSCrossfeed345_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS24_O7_VC );
		pRightRCSCrossfeed12_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS25_O7_VC );
		pRightRCSCrossfeed345_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS26_O7_VC );
		return;
	}

	void PanelO7::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O7, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O7,
			_V( -0.217782, 3.1858, 13.6081 ) + ofs, _V( 0.202397, 3.1858, 13.6081 ) + ofs,
			_V( -0.217782, 3.01494, 14.3132 ) + ofs, _V( 0.202397, 3.01485, 14.3131 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelO7::Realize()
	{
		discsignals::DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_SW", 16 );
		pAftLeftRCSHePressA->ConnectPort( 2, pBundle, 0 );// OP
		pAftLeftRCSHePressA->ConnectPort( 0, pBundle, 1 );// CL
		pAftLeftRCSHePressB->ConnectPort( 2, pBundle, 2 );// OP
		pAftLeftRCSHePressB->ConnectPort( 0, pBundle, 3 );// CL
		pAftLeftRCSTankIsolation12->ConnectPort( 2, pBundle, 4 );// OP
		pAftLeftRCSTankIsolation12->ConnectPort( 0, pBundle, 5 );// CL
		pAftLeftRCSTankIsolation345A->ConnectPort( 2, pBundle, 6 );// OP
		pAftLeftRCSTankIsolation345A->ConnectPort( 0, pBundle, 7 );// CL
		pAftLeftRCSTankIsolation345B->ConnectPort( 2, pBundle, 8 );// OP
		pAftLeftRCSTankIsolation345B->ConnectPort( 0, pBundle, 9 );// CL

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_HePress_TankIsol_TB", 16 );
		pAftLeftRCSHePressA_TB->SetInput( 0, pBundle, 0, TB_OP );
		pAftLeftRCSHePressA_TB->SetInput( 1, pBundle, 1, TB_CL );
		pAftLeftRCSHePressB_TB->SetInput( 0, pBundle, 2, TB_OP );
		pAftLeftRCSHePressB_TB->SetInput( 1, pBundle, 3, TB_CL );
		pAftLeftRCSTankIsolation12_TB->SetInput( 0, pBundle, 4, TB_OP );
		pAftLeftRCSTankIsolation12_TB->SetInput( 1, pBundle, 5, TB_CL );
		pAftLeftRCSTankIsolation345A_TB->SetInput( 0, pBundle, 6, TB_OP );
		pAftLeftRCSTankIsolation345A_TB->SetInput( 1, pBundle, 7, TB_CL );
		pAftLeftRCSTankIsolation345B_TB->SetInput( 0, pBundle, 8, TB_OP );
		pAftLeftRCSTankIsolation345B_TB->SetInput( 1, pBundle, 9, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_ManifIsol_SW", 16 );
		pAftLeftRCSManifoldIsolation1->ConnectPort( 2, pBundle, 0 );// OP
		pAftLeftRCSManifoldIsolation1->ConnectPort( 0, pBundle, 1 );// CL
		pAftLeftRCSManifoldIsolation2->ConnectPort( 2, pBundle, 2 );// OP
		pAftLeftRCSManifoldIsolation2->ConnectPort( 0, pBundle, 3 );// CL
		pAftLeftRCSManifoldIsolation3->ConnectPort( 2, pBundle, 4 );// OP
		pAftLeftRCSManifoldIsolation3->ConnectPort( 0, pBundle, 5 );// CL
		pAftLeftRCSManifoldIsolation4->ConnectPort( 2, pBundle, 6 );// OP
		pAftLeftRCSManifoldIsolation4->ConnectPort( 0, pBundle, 7 );// CL
		pAftLeftRCSManifoldIsolation5->ConnectPort( 2, pBundle, 8 );// OP
		pAftLeftRCSManifoldIsolation5->ConnectPort( 0, pBundle, 9 );// CL

		pBundle = STS()->BundleManager()->CreateBundle( "LeftRCS_ManifIsol_TB", 16 );
		pAftLeftRCSManifoldIsolation1_TB->SetInput( 0, pBundle, 0, TB_OP );
		pAftLeftRCSManifoldIsolation1_TB->SetInput( 1, pBundle, 1, TB_CL );
		pAftLeftRCSManifoldIsolation2_TB->SetInput( 0, pBundle, 2, TB_OP );
		pAftLeftRCSManifoldIsolation2_TB->SetInput( 1, pBundle, 3, TB_CL );
		pAftLeftRCSManifoldIsolation3_TB->SetInput( 0, pBundle, 4, TB_OP );
		pAftLeftRCSManifoldIsolation3_TB->SetInput( 1, pBundle, 5, TB_CL );
		pAftLeftRCSManifoldIsolation4_TB->SetInput( 0, pBundle, 6, TB_OP );
		pAftLeftRCSManifoldIsolation4_TB->SetInput( 1, pBundle, 7, TB_CL );
		pAftLeftRCSManifoldIsolation5_TB->SetInput( 0, pBundle, 8, TB_OP );
		pAftLeftRCSManifoldIsolation5_TB->SetInput( 1, pBundle, 9, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_SW", 16 );
		pAftRightRCSHePressA->ConnectPort( 2, pBundle, 0 );// OP
		pAftRightRCSHePressA->ConnectPort( 0, pBundle, 1 );// CL
		pAftRightRCSHePressB->ConnectPort( 2, pBundle, 2 );// OP
		pAftRightRCSHePressB->ConnectPort( 0, pBundle, 3 );// CL
		pAftRightRCSTankIsolation12->ConnectPort( 2, pBundle, 4 );// OP
		pAftRightRCSTankIsolation12->ConnectPort( 0, pBundle, 5 );// CL
		pAftRightRCSTankIsolation345A->ConnectPort( 2, pBundle, 6 );// OP
		pAftRightRCSTankIsolation345A->ConnectPort( 0, pBundle, 7 );// CL
		pAftRightRCSTankIsolation345B->ConnectPort( 2, pBundle, 8 );// OP
		pAftRightRCSTankIsolation345B->ConnectPort( 0, pBundle, 9 );// CL

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_HePress_TankIsol_TB", 16 );
		pAftRightRCSHePressA_TB->SetInput( 0, pBundle, 0, TB_OP );
		pAftRightRCSHePressA_TB->SetInput( 1, pBundle, 1, TB_CL );
		pAftRightRCSHePressB_TB->SetInput( 0, pBundle, 2, TB_OP );
		pAftRightRCSHePressB_TB->SetInput( 1, pBundle, 3, TB_CL );
		pAftRightRCSTankIsolation12_TB->SetInput( 0, pBundle, 4, TB_OP );
		pAftRightRCSTankIsolation12_TB->SetInput( 1, pBundle, 5, TB_CL );
		pAftRightRCSTankIsolation345A_TB->SetInput( 0, pBundle, 6, TB_OP );
		pAftRightRCSTankIsolation345A_TB->SetInput( 1, pBundle, 7, TB_CL );
		pAftRightRCSTankIsolation345B_TB->SetInput( 0, pBundle, 8, TB_OP );
		pAftRightRCSTankIsolation345B_TB->SetInput( 1, pBundle, 9, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_ManifIsol_SW", 16 );
		pAftRightRCSManifoldIsolation1->ConnectPort( 2, pBundle, 0 );// OP
		pAftRightRCSManifoldIsolation1->ConnectPort( 0, pBundle, 1 );// CL
		pAftRightRCSManifoldIsolation2->ConnectPort( 2, pBundle, 2 );// OP
		pAftRightRCSManifoldIsolation2->ConnectPort( 0, pBundle, 3 );// CL
		pAftRightRCSManifoldIsolation3->ConnectPort( 2, pBundle, 4 );// OP
		pAftRightRCSManifoldIsolation3->ConnectPort( 0, pBundle, 5 );// CL
		pAftRightRCSManifoldIsolation4->ConnectPort( 2, pBundle, 6 );// OP
		pAftRightRCSManifoldIsolation4->ConnectPort( 0, pBundle, 7 );// CL
		pAftRightRCSManifoldIsolation5->ConnectPort( 2, pBundle, 8 );// OP
		pAftRightRCSManifoldIsolation5->ConnectPort( 0, pBundle, 9 );// CL

		pBundle = STS()->BundleManager()->CreateBundle( "RightRCS_ManifIsol_TB", 16 );
		pAftRightRCSManifoldIsolation1_TB->SetInput( 0, pBundle, 0, TB_OP );
		pAftRightRCSManifoldIsolation1_TB->SetInput( 1, pBundle, 1, TB_CL );
		pAftRightRCSManifoldIsolation2_TB->SetInput( 0, pBundle, 2, TB_OP );
		pAftRightRCSManifoldIsolation2_TB->SetInput( 1, pBundle, 3, TB_CL );
		pAftRightRCSManifoldIsolation3_TB->SetInput( 0, pBundle, 4, TB_OP );
		pAftRightRCSManifoldIsolation3_TB->SetInput( 1, pBundle, 5, TB_CL );
		pAftRightRCSManifoldIsolation4_TB->SetInput( 0, pBundle, 6, TB_OP );
		pAftRightRCSManifoldIsolation4_TB->SetInput( 1, pBundle, 7, TB_CL );
		pAftRightRCSManifoldIsolation5_TB->SetInput( 0, pBundle, 8, TB_OP );
		pAftRightRCSManifoldIsolation5_TB->SetInput( 1, pBundle, 9, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "RCS_Crossfeed_SW", 16 );
		pLeftRCSCrossfeed12->ConnectPort( 2, pBundle, 0 );// OP
		pLeftRCSCrossfeed12->ConnectPort( 0, pBundle, 1 );// CL
		pLeftRCSCrossfeed345->ConnectPort( 2, pBundle, 2 );// OP
		pLeftRCSCrossfeed345->ConnectPort( 0, pBundle, 3 );// CL
		pRightRCSCrossfeed12->ConnectPort( 2, pBundle, 4 );// OP
		pRightRCSCrossfeed12->ConnectPort( 0, pBundle, 5 );// CL
		pRightRCSCrossfeed345->ConnectPort( 2, pBundle, 6 );// OP
		pRightRCSCrossfeed345->ConnectPort( 0, pBundle, 7 );// CL
		MasterRCSCrossfeed->ConnectPort( 0, pBundle, 8 );// Right
		MasterRCSCrossfeed->ConnectPort( 2, pBundle, 9 );// Left

		pBundle = STS()->BundleManager()->CreateBundle( "RCS_Crossfeed_TB", 16 );
		pLeftRCSCrossfeed12_TB->SetInput( 0, pBundle, 0, TB_OP );
		pLeftRCSCrossfeed12_TB->SetInput( 1, pBundle, 1, TB_CL );
		pLeftRCSCrossfeed345_TB->SetInput( 0, pBundle, 2, TB_OP );
		pLeftRCSCrossfeed345_TB->SetInput( 1, pBundle, 3, TB_CL );
		pRightRCSCrossfeed12_TB->SetInput( 0, pBundle, 4, TB_OP );
		pRightRCSCrossfeed12_TB->SetInput( 1, pBundle, 5, TB_CL );
		pRightRCSCrossfeed345_TB->SetInput( 0, pBundle, 6, TB_OP );
		pRightRCSCrossfeed345_TB->SetInput( 1, pBundle, 7, TB_CL );

		AtlantisPanel::Realize();
		return;
	}
};