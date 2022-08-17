/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/02   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
#include "PanelO8.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_o8.h"


namespace vc
{
	PanelO8::PanelO8( Atlantis* psts ):AtlantisPanel( psts, "O8" )
	{
		DefineMesh( MESHNAME_PANELO8 );

		Add( pRadarAltimeter[0] = new StdSwitch2( psts, "RADAR ALTIMETER 1" ) );
		pRadarAltimeter[0]->SetLabel( 0, "OFF" );
		pRadarAltimeter[0]->SetLabel( 1, "ON" );

		Add( pRadarAltimeter[1] = new StdSwitch2( psts, "RADAR ALTIMETER 2" ) );
		pRadarAltimeter[1]->SetLabel( 0, "OFF" );
		pRadarAltimeter[1]->SetLabel( 1, "ON" );

		Add( pAnnunciatorLampTest = new StdSwitch3( psts, "ANNUNCIATOR LAMP TEST" ) );

		Add( pOMSKitHePressVaporIsolA = new StdSwitch3( psts, "OMS Kit He Press/Vapor Isol A" ) );
		pOMSKitHePressVaporIsolA->SetLabel( 0, "CLOSE" );
		pOMSKitHePressVaporIsolA->SetLabel( 1, "GPC" );
		pOMSKitHePressVaporIsolA->SetLabel( 2, "OPEN" );

		Add( pOMSKitHePressVaporIsolB = new StdSwitch3( psts, "OMS Kit He Press/Vapor Isol B" ) );
		pOMSKitHePressVaporIsolB->SetLabel( 0, "CLOSE" );
		pOMSKitHePressVaporIsolB->SetLabel( 1, "GPC" );
		pOMSKitHePressVaporIsolB->SetLabel( 2, "OPEN" );

		Add( pOMSKitTankIsolationA = new StdSwitch3( psts, "OMS Kit Tank Isolation A" ) );
		pOMSKitTankIsolationA->SetLabel( 0, "CLOSE" );
		pOMSKitTankIsolationA->SetLabel( 1, "GPC" );
		pOMSKitTankIsolationA->SetLabel( 2, "OPEN" );

		Add( pOMSKitTankIsolationB = new StdSwitch3( psts, "OMS Kit Tank Isolation B" ) );
		pOMSKitTankIsolationB->SetLabel( 0, "CLOSE" );
		pOMSKitTankIsolationB->SetLabel( 1, "GPC" );
		pOMSKitTankIsolationB->SetLabel( 2, "OPEN" );

		Add( pLeftOMSHePressVaporIsolA = new StdSwitch3( psts, "Left OMS He Press/Vapor Isol A" ) );
		pLeftOMSHePressVaporIsolA->SetLabel( 0, "CLOSE" );
		pLeftOMSHePressVaporIsolA->SetLabel( 1, "GPC" );
		pLeftOMSHePressVaporIsolA->SetLabel( 2, "OPEN" );

		Add( pLeftOMSHePressVaporIsolB = new StdSwitch3( psts, "Left OMS He Press/Vapor Isol B" ) );
		pLeftOMSHePressVaporIsolB->SetLabel( 0, "CLOSE" );
		pLeftOMSHePressVaporIsolB->SetLabel( 1, "GPC" );
		pLeftOMSHePressVaporIsolB->SetLabel( 2, "OPEN" );

		Add( pLeftOMSTankIsolationA = new StdSwitch3( psts, "Left OMS Tank Isolation A" ) );
		pLeftOMSTankIsolationA->SetLabel( 0, "CLOSE" );
		pLeftOMSTankIsolationA->SetLabel( 1, "GPC" );
		pLeftOMSTankIsolationA->SetLabel( 2, "OPEN" );

		Add( pLeftOMSTankIsolationB = new StdSwitch3( psts, "Left OMS Tank Isolation B" ) );
		pLeftOMSTankIsolationB->SetLabel( 0, "CLOSE" );
		pLeftOMSTankIsolationB->SetLabel( 1, "GPC" );
		pLeftOMSTankIsolationB->SetLabel( 2, "OPEN" );

		Add( pRightOMSHePressVaporIsolA = new StdSwitch3( psts, "Right OMS He Press/Vapor Isol A" ) );
		pRightOMSHePressVaporIsolA->SetLabel( 0, "CLOSE" );
		pRightOMSHePressVaporIsolA->SetLabel( 1, "GPC" );
		pRightOMSHePressVaporIsolA->SetLabel( 2, "OPEN" );

		Add( pRightOMSHePressVaporIsolB = new StdSwitch3( psts, "Right OMS He Press/Vapor Isol B" ) );
		pRightOMSHePressVaporIsolB->SetLabel( 0, "CLOSE" );
		pRightOMSHePressVaporIsolB->SetLabel( 1, "GPC" );
		pRightOMSHePressVaporIsolB->SetLabel( 2, "OPEN" );

		Add( pRightOMSTankIsolationA = new StdSwitch3( psts, "Right OMS Tank Isolation A" ) );
		pRightOMSTankIsolationA->SetLabel( 0, "CLOSE" );
		pRightOMSTankIsolationA->SetLabel( 1, "GPC" );
		pRightOMSTankIsolationA->SetLabel( 2, "OPEN" );

		Add( pRightOMSTankIsolationB = new StdSwitch3( psts, "Right OMS Tank Isolation B" ) );
		pRightOMSTankIsolationB->SetLabel( 0, "CLOSE" );
		pRightOMSTankIsolationB->SetLabel( 1, "GPC" );
		pRightOMSTankIsolationB->SetLabel( 2, "OPEN" );

		Add( pLeftOMSCrossfeedA = new StdSwitch3( psts, "Left OMS Crossfeed A" ) );
		pLeftOMSCrossfeedA->SetLabel( 0, "CLOSE" );
		pLeftOMSCrossfeedA->SetLabel( 1, "GPC" );
		pLeftOMSCrossfeedA->SetLabel( 2, "OPEN" );

		Add( pLeftOMSCrossfeedB = new StdSwitch3( psts, "Left OMS Crossfeed B" ) );
		pLeftOMSCrossfeedB->SetLabel( 0, "CLOSE" );
		pLeftOMSCrossfeedB->SetLabel( 1, "GPC" );
		pLeftOMSCrossfeedB->SetLabel( 2, "OPEN" );

		Add( pRightOMSCrossfeedA = new StdSwitch3( psts, "Right OMS Crossfeed A" ) );
		pRightOMSCrossfeedA->SetLabel( 0, "CLOSE" );
		pRightOMSCrossfeedA->SetLabel( 1, "GPC" );
		pRightOMSCrossfeedA->SetLabel( 2, "OPEN" );

		Add( pRightOMSCrossfeedB = new StdSwitch3( psts, "Right OMS Crossfeed B" ) );
		pRightOMSCrossfeedB->SetLabel( 0, "CLOSE" );
		pRightOMSCrossfeedB->SetLabel( 1, "GPC" );
		pRightOMSCrossfeedB->SetLabel( 2, "OPEN" );

		Add( pFwdRCSHePressA = new StdSwitch3( psts, "Fwd RCS He Press A" ) );
		pFwdRCSHePressA->SetLabel( 0, "CLOSE" );
		pFwdRCSHePressA->SetLabel( 1, "GPC" );
		pFwdRCSHePressA->SetLabel( 2, "OPEN" );

		Add( pFwdRCSHePressB = new StdSwitch3( psts, "Fwd RCS He Press B" ) );
		pFwdRCSHePressB->SetLabel( 0, "CLOSE" );
		pFwdRCSHePressB->SetLabel( 1, "GPC" );
		pFwdRCSHePressB->SetLabel( 2, "OPEN" );

		Add( pFwdRCSTankIsolation12 = new StdSwitch3( psts, "Fwd RCS Tank Isolation 1/2" ) );
		pFwdRCSTankIsolation12->SetLabel( 0, "CLOSE" );
		pFwdRCSTankIsolation12->SetLabel( 1, "GPC" );
		pFwdRCSTankIsolation12->SetLabel( 2, "OPEN" );

		Add( pFwdRCSTankIsolation345 = new StdSwitch3( psts, "Fwd RCS Tank Isolation 3/4/5" ) );
		pFwdRCSTankIsolation345->SetLabel( 0, "CLOSE" );
		pFwdRCSTankIsolation345->SetLabel( 1, "GPC" );
		pFwdRCSTankIsolation345->SetLabel( 2, "OPEN" );

		Add( pFwdRCSManifoldIsolation1 = new StdSwitch3( psts, "Fwd RCS Manifold Isolation 1" ) );
		pFwdRCSManifoldIsolation1->SetLabel( 0, "CLOSE" );
		pFwdRCSManifoldIsolation1->SetLabel( 1, "GPC" );
		pFwdRCSManifoldIsolation1->SetLabel( 2, "OPEN" );

		Add( pFwdRCSManifoldIsolation2 = new StdSwitch3( psts, "Fwd RCS Manifold Isolation 2" ) );
		pFwdRCSManifoldIsolation2->SetLabel( 0, "CLOSE" );
		pFwdRCSManifoldIsolation2->SetLabel( 1, "GPC" );
		pFwdRCSManifoldIsolation2->SetLabel( 2, "OPEN" );

		Add( pFwdRCSManifoldIsolation3 = new StdSwitch3( psts, "Fwd RCS Manifold Isolation 3" ) );
		pFwdRCSManifoldIsolation3->SetLabel( 0, "CLOSE" );
		pFwdRCSManifoldIsolation3->SetLabel( 1, "GPC" );
		pFwdRCSManifoldIsolation3->SetLabel( 2, "OPEN" );

		Add( pFwdRCSManifoldIsolation4 = new StdSwitch3( psts, "Fwd RCS Manifold Isolation 4" ) );
		pFwdRCSManifoldIsolation4->SetLabel( 0, "CLOSE" );
		pFwdRCSManifoldIsolation4->SetLabel( 1, "GPC" );
		pFwdRCSManifoldIsolation4->SetLabel( 2, "OPEN" );

		Add( pFwdRCSManifoldIsolation5 = new StdSwitch3( psts, "Fwd RCS Manifold Isolation 5" ) );
		pFwdRCSManifoldIsolation5->SetLabel( 0, "CLOSE" );
		pFwdRCSManifoldIsolation5->SetLabel( 1, "GPC" );
		pFwdRCSManifoldIsolation5->SetLabel( 2, "OPEN" );

		Add( pOMSKitTankIsolationA_TB = new StandardTalkback3( psts, "OMS Kit Tank Isolation A TB" ) );
		Add( pOMSKitTankIsolationB_TB = new StandardTalkback3( psts, "OMS Kit Tank Isolation B TB" ) );
		Add( pLeftOMSTankIsolationA_TB = new StandardTalkback3( psts, "Left OMS Tank Isolation A TB" ) );
		Add( pLeftOMSTankIsolationB_TB = new StandardTalkback3( psts, "Left OMS Tank Isolation B TB" ) );
		Add( pRightOMSTankIsolationA_TB = new StandardTalkback3( psts, "Right OMS Tank Isolation A TB" ) );
		Add( pRightOMSTankIsolationB_TB = new StandardTalkback3( psts, "Right OMS Tank Isolation B TB" ) );
		Add( pLeftOMSCrossfeedA_TB = new StandardTalkback3( psts, "Left OMS Crossfeed A TB" ) );
		Add( pLeftOMSCrossfeedB_TB = new StandardTalkback3( psts, "Left OMS Crossfeed B TB" ) );
		Add( pRightOMSCrossfeedA_TB = new StandardTalkback3( psts, "Right OMS Crossfeed A TB" ) );
		Add( pRightOMSCrossfeedB_TB = new StandardTalkback3( psts, "Right OMS Crossfeed B TB" ) );
		Add( pFwdRCSHePressA_TB = new StandardTalkback3( psts, "Fwd RCS He Press A TB" ) );
		Add( pFwdRCSHePressB_TB = new StandardTalkback3( psts, "Fwd RCS He Press B TB" ) );
		Add( pFwdRCSTankIsolation12_TB = new StandardTalkback3( psts, "Fwd RCS Tank Isolation 1/2 TB" ) );
		Add( pFwdRCSTankIsolation345_TB = new StandardTalkback3( psts, "Fwd RCS Tank Isolation 3/4/5 TB" ) );
		Add( pFwdRCSManifoldIsolation1_TB = new StandardTalkback3( psts, "Fwd RCS Manifold Isolation 1 TB" ) );
		Add( pFwdRCSManifoldIsolation2_TB = new StandardTalkback3( psts, "Fwd RCS Manifold Isolation 2 TB" ) );
		Add( pFwdRCSManifoldIsolation3_TB = new StandardTalkback3( psts, "Fwd RCS Manifold Isolation 3 TB" ) );
		Add( pFwdRCSManifoldIsolation4_TB = new StandardTalkback3( psts, "Fwd RCS Manifold Isolation 4 TB" ) );
		Add( pFwdRCSManifoldIsolation5_TB = new StandardTalkback3( psts, "Fwd RCS Manifold Isolation 5 TB" ) );
	}

	PanelO8::~PanelO8()
	{
	}

	void PanelO8::DefineVC()
	{
		VECTOR3 switch_rot = _V( 1.0, 0.0, 0.0 );

		AddAIDToMouseEventList( AID_O8 );

		pRadarAltimeter[0]->SetInitialAnimState( 0.5f );
		pRadarAltimeter[0]->DefineGroup( GRP_S4_O8_VC );
		pRadarAltimeter[0]->SetReference( _V( 0.2651, 3.1652, 13.6946 ), switch_rot );
		pRadarAltimeter[0]->SetMouseRegion( AID_O8, 0.089737f, 0.106703f, 0.135184f, 0.140805f );

		pRadarAltimeter[1]->SetInitialAnimState( 0.5f );
		pRadarAltimeter[1]->DefineGroup( GRP_S5_O8_VC );
		pRadarAltimeter[1]->SetReference( _V( 0.2651, 3.1652, 13.6946 ), switch_rot );
		pRadarAltimeter[1]->SetMouseRegion( AID_O8, 0.157729f, 0.106310f, 0.201778f, 0.140387f );

		pAnnunciatorLampTest->SetInitialAnimState( 0.5f );
		pAnnunciatorLampTest->DefineGroup( GRP_S18_O8_VC );
		pAnnunciatorLampTest->SetReference( _V( 0.6000, 3.0978, 13.9709 ), switch_rot );
		pAnnunciatorLampTest->SetMouseRegion( AID_O8, 0.775565f, 0.498687f, 0.814904f, 0.530986f );
		pAnnunciatorLampTest->SetSpringLoaded( true, 0 );
		pAnnunciatorLampTest->SetSpringLoaded( true, 2 );

		pOMSKitHePressVaporIsolA->SetInitialAnimState( 0.5f );
		pOMSKitHePressVaporIsolA->DefineGroup( GRP_S1_O8_VC );
		pOMSKitHePressVaporIsolA->SetReference( _V( 0.249854, 3.09883, 13.968451 ), switch_rot );
		pOMSKitHePressVaporIsolA->SetMouseRegion( AID_O8, 0.083326f, 0.495498f, 0.131041f, 0.527633f );

		pOMSKitHePressVaporIsolB->SetInitialAnimState( 0.5f );
		pOMSKitHePressVaporIsolB->DefineGroup( GRP_S2_O8_VC );
		pOMSKitHePressVaporIsolB->SetReference( _V( 0.249854, 3.09883, 13.968451 ), switch_rot );
		pOMSKitHePressVaporIsolB->SetMouseRegion( AID_O8, 0.155082f, 0.492018f, 0.199428f, 0.527935f );

		pOMSKitTankIsolationA->SetInitialAnimState( 0.5f );
		pOMSKitTankIsolationA->DefineGroup( GRP_S6_O8_VC );
		pOMSKitTankIsolationA->SetReference( _V( 0.250572, 3.05952, 14.127251 ), switch_rot );
		pOMSKitTankIsolationA->SetMouseRegion( AID_O8, 0.084916f, 0.720110f, 0.130453f, 0.752827f );
		
		pOMSKitTankIsolationB->SetInitialAnimState( 0.5f );
		pOMSKitTankIsolationB->DefineGroup( GRP_S7_O8_VC );
		pOMSKitTankIsolationB->SetReference( _V( 0.250572, 3.05952, 14.127251 ), switch_rot );
		pOMSKitTankIsolationB->SetMouseRegion( AID_O8, 0.152753f, 0.720423f, 0.200169f, 0.754202f );

		pLeftOMSHePressVaporIsolA->SetInitialAnimState( 0.5f );
		pLeftOMSHePressVaporIsolA->DefineGroup( GRP_S12_O8_VC );
		pLeftOMSHePressVaporIsolA->SetReference( _V( 0.249854, 3.09883, 13.968451 ), switch_rot );
		pLeftOMSHePressVaporIsolA->SetMouseRegion( AID_O8, 0.231398f, 0.493515f, 0.279281f, 0.528927f );

		pLeftOMSHePressVaporIsolB->SetInitialAnimState( 0.5f );
		pLeftOMSHePressVaporIsolB->DefineGroup( GRP_S13_O8_VC );
		pLeftOMSHePressVaporIsolB->SetReference( _V( 0.249854, 3.09883, 13.968451 ), switch_rot );
		pLeftOMSHePressVaporIsolB->SetMouseRegion( AID_O8, 0.303108f, 0.491144f, 0.348379f, 0.528686f );

		pLeftOMSTankIsolationA->SetInitialAnimState( 0.5f );
		pLeftOMSTankIsolationA->DefineGroup( GRP_S19_O8_VC );
		pLeftOMSTankIsolationA->SetReference( _V( 0.250572, 3.05952, 14.127251 ), switch_rot );
		pLeftOMSTankIsolationA->SetMouseRegion( AID_O8, 0.233072f, 0.721316f, 0.279586f, 0.754040f );

		pLeftOMSTankIsolationB->SetInitialAnimState( 0.5f );
		pLeftOMSTankIsolationB->DefineGroup( GRP_S20_O8_VC );
		pLeftOMSTankIsolationB->SetReference( _V( 0.250572, 3.05952, 14.127251 ), switch_rot );
		pLeftOMSTankIsolationB->SetMouseRegion( AID_O8, 0.299454f, 0.719025f, 0.346357f, 0.753286f );

		pRightOMSHePressVaporIsolA->SetInitialAnimState( 0.5f );
		pRightOMSHePressVaporIsolA->DefineGroup( GRP_S14_O8_VC );
		pRightOMSHePressVaporIsolA->SetReference( _V( 0.249854, 3.09883, 13.968451 ), switch_rot );
		pRightOMSHePressVaporIsolA->SetMouseRegion( AID_O8, 0.380875f, 0.493204f, 0.427438f, 0.528036f );

		pRightOMSHePressVaporIsolB->SetInitialAnimState( 0.5f );
		pRightOMSHePressVaporIsolB->DefineGroup( GRP_S15_O8_VC );
		pRightOMSHePressVaporIsolB->SetReference( _V( 0.249854, 3.09883, 13.968451 ), switch_rot );
		pRightOMSHePressVaporIsolB->SetMouseRegion( AID_O8, 0.448651f, 0.492422f, 0.496427f, 0.528892f );

		pRightOMSTankIsolationA->SetInitialAnimState( 0.5f );
		pRightOMSTankIsolationA->DefineGroup( GRP_S21_O8_VC );
		pRightOMSTankIsolationA->SetReference( _V( 0.250572, 3.05952, 14.127251 ), switch_rot );
		pRightOMSTankIsolationA->SetMouseRegion( AID_O8, 0.378236f, 0.722513f, 0.424956f, 0.755230f );

		pRightOMSTankIsolationB->SetInitialAnimState( 0.5f );
		pRightOMSTankIsolationB->DefineGroup( GRP_S22_O8_VC );
		pRightOMSTankIsolationB->SetReference( _V( 0.250572, 3.05952, 14.127251 ), switch_rot );
		pRightOMSTankIsolationB->SetMouseRegion( AID_O8, 0.444512f, 0.720742f, 0.487962f, 0.754465f );

		pLeftOMSCrossfeedA->SetInitialAnimState( 0.5f );
		pLeftOMSCrossfeedA->DefineGroup( GRP_S26_O8_VC );
		pLeftOMSCrossfeedA->SetReference( _V( 0.324825, 3.03576, 14.22775 ), switch_rot );
		pLeftOMSCrossfeedA->SetMouseRegion( AID_O8, 0.232717f, 0.864193f, 0.280008f, 0.896693f );

		pLeftOMSCrossfeedB->SetInitialAnimState( 0.5f );
		pLeftOMSCrossfeedB->DefineGroup( GRP_S27_O8_VC );
		pLeftOMSCrossfeedB->SetReference( _V( 0.324825, 3.03576, 14.22775 ), switch_rot );
		pLeftOMSCrossfeedB->SetMouseRegion( AID_O8, 0.300988f, 0.860912f, 0.347271f, 0.896729f );

		pRightOMSCrossfeedA->SetInitialAnimState( 0.5f );
		pRightOMSCrossfeedA->DefineGroup( GRP_S28_O8_VC );
		pRightOMSCrossfeedA->SetReference( _V( 0.324825, 3.03576, 14.22775 ), switch_rot );
		pRightOMSCrossfeedA->SetMouseRegion( AID_O8, 0.379780f, 0.862623f, 0.426042f, 0.897914f );

		pRightOMSCrossfeedB->SetInitialAnimState( 0.5f );
		pRightOMSCrossfeedB->DefineGroup( GRP_S29_O8_VC );
		pRightOMSCrossfeedB->SetReference( _V( 0.324825, 3.03576, 14.22775 ), switch_rot );
		pRightOMSCrossfeedB->SetMouseRegion( AID_O8, 0.449458f, 0.861556f, 0.494833f, 0.896838f );

		pFwdRCSHePressA->SetInitialAnimState( 0.5f );
		pFwdRCSHePressA->DefineGroup( GRP_S16_O8_VC );
		pFwdRCSHePressA->SetReference( _V( 0.485191, 3.08654, 14.016649 ), switch_rot );
		pFwdRCSHePressA->SetMouseRegion( AID_O8, 0.546266f, 0.561184f, 0.594842f, 0.597841f );

		pFwdRCSHePressB->SetInitialAnimState( 0.5f );
		pFwdRCSHePressB->DefineGroup( GRP_S17_O8_VC );
		pFwdRCSHePressB->SetReference( _V( 0.485191, 3.08654, 14.016649 ), switch_rot );
		pFwdRCSHePressB->SetMouseRegion( AID_O8, 0.677354f, 0.561184f, 0.725839f, 0.597841f );

		pFwdRCSTankIsolation12->SetInitialAnimState( 0.5f );
		pFwdRCSTankIsolation12->DefineGroup( GRP_S23_O8_VC );
		pFwdRCSTankIsolation12->SetReference( _V( 0.484743, 3.05952, 14.1297 ), switch_rot );
		pFwdRCSTankIsolation12->SetMouseRegion( AID_O8, 0.546266f, 0.722405f, 0.594842f, 0.758419f );

		pFwdRCSTankIsolation345->SetInitialAnimState( 0.5f );
		pFwdRCSTankIsolation345->DefineGroup( GRP_S24_O8_VC );
		pFwdRCSTankIsolation345->SetReference( _V( 0.484743, 3.05952, 14.1297 ), switch_rot );
		pFwdRCSTankIsolation345->SetMouseRegion( AID_O8, 0.677354f, 0.722405f, 0.725839f, 0.758419f );

		pFwdRCSManifoldIsolation1->SetInitialAnimState( 0.5f );
		pFwdRCSManifoldIsolation1->DefineGroup( GRP_S30_O8_VC );
		pFwdRCSManifoldIsolation1->SetReference( _V( 0.483999, 3.03512, 14.2299 ), switch_rot );
		pFwdRCSManifoldIsolation1->SetMouseRegion( AID_O8, 0.545887f, 0.864128f, 0.591088f, 0.900455f );

		pFwdRCSManifoldIsolation2->SetInitialAnimState( 0.5f );
		pFwdRCSManifoldIsolation2->DefineGroup( GRP_S31_O8_VC );
		pFwdRCSManifoldIsolation2->SetReference( _V( 0.483999, 3.03512, 14.2299 ), switch_rot );
		pFwdRCSManifoldIsolation2->SetMouseRegion( AID_O8, 0.613803f, 0.864128f, 0.664275f, 0.900455f );

		pFwdRCSManifoldIsolation3->SetInitialAnimState( 0.5f );
		pFwdRCSManifoldIsolation3->DefineGroup( GRP_S32_O8_VC );
		pFwdRCSManifoldIsolation3->SetReference( _V( 0.483999, 3.03512, 14.2299 ), switch_rot );
		pFwdRCSManifoldIsolation3->SetMouseRegion( AID_O8, 0.678171f, 0.864128f, 0.723977f, 0.900455f );

		pFwdRCSManifoldIsolation4->SetInitialAnimState( 0.5f );
		pFwdRCSManifoldIsolation4->DefineGroup( GRP_S33_O8_VC );
		pFwdRCSManifoldIsolation4->SetReference( _V( 0.483999, 3.03512, 14.2299 ), switch_rot );
		pFwdRCSManifoldIsolation4->SetMouseRegion( AID_O8, 0.738932f, 0.864128f, 0.798588f, 0.900455f );

		pFwdRCSManifoldIsolation5->SetInitialAnimState( 0.5f );
		pFwdRCSManifoldIsolation5->DefineGroup( GRP_S34_O8_VC );
		pFwdRCSManifoldIsolation5->SetReference( _V( 0.483999, 3.03512, 14.2299 ), switch_rot );
		pFwdRCSManifoldIsolation5->SetMouseRegion( AID_O8, 0.813011f, 0.864128f, 0.859909f, 0.900455f );
		
		pOMSKitTankIsolationA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_O8_VC );
		pOMSKitTankIsolationB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_O8_VC );
		pLeftOMSTankIsolationA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_O8_VC );
		pLeftOMSTankIsolationB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS6_O8_VC );
		pRightOMSTankIsolationA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS7_O8_VC );
		pRightOMSTankIsolationB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_O8_VC );
		pLeftOMSCrossfeedA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS12_O8_VC );
		pLeftOMSCrossfeedB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS13_O8_VC );
		pRightOMSCrossfeedA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS14_O8_VC );
		pRightOMSCrossfeedB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS15_O8_VC );
		pFwdRCSHePressA_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS3_O8_VC );
		pFwdRCSHePressB_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_O8_VC );
		pFwdRCSTankIsolation12_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS9_O8_VC );
		pFwdRCSTankIsolation345_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS10_O8_VC );
		pFwdRCSManifoldIsolation1_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS16_O8_VC );
		pFwdRCSManifoldIsolation2_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS17_O8_VC );
		pFwdRCSManifoldIsolation3_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS18_O8_VC );
		pFwdRCSManifoldIsolation4_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS19_O8_VC );
		pFwdRCSManifoldIsolation5_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS20_O8_VC );
		return;
	}

	void PanelO8::Realize()
	{
		discsignals::DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "RDR_ALT", 16 );
		pRadarAltimeter[0]->ConnectPort( 1, pBundle, 0 );
		pRadarAltimeter[1]->ConnectPort( 1, pBundle, 1 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA", 16 );
		pAnnunciatorLampTest->ConnectPort( 2, pBundle, 8 );
		pAnnunciatorLampTest->ConnectPort( 0, pBundle, 9 );


		pBundle = STS()->BundleManager()->CreateBundle( "OMSKit_DC", 16 );
		pOMSKitHePressVaporIsolA->ConnectPort( 2, pBundle, 0 );// OP
		pOMSKitHePressVaporIsolA->ConnectPort( 0, pBundle, 1 );// CL
		pOMSKitHePressVaporIsolB->ConnectPort( 2, pBundle, 2 );// OP
		pOMSKitHePressVaporIsolB->ConnectPort( 0, pBundle, 3 );// CL
		pOMSKitTankIsolationA->ConnectPort( 2, pBundle, 4 );// OP
		pOMSKitTankIsolationA->ConnectPort( 0, pBundle, 5 );// CL
		pOMSKitTankIsolationB->ConnectPort( 2, pBundle, 6 );// OP
		pOMSKitTankIsolationB->ConnectPort( 0, pBundle, 7 );// CL
		pOMSKitTankIsolationA_TB->SetInput( 0, pBundle, 8, TB_OP );
		pOMSKitTankIsolationA_TB->SetInput( 1, pBundle, 9, TB_CL );
		pOMSKitTankIsolationB_TB->SetInput( 0, pBundle, 10, TB_OP );
		pOMSKitTankIsolationB_TB->SetInput( 1, pBundle, 11, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "LeftOMS_DC", 16 );
		pLeftOMSHePressVaporIsolA->ConnectPort( 2, pBundle, 0 );// OP
		pLeftOMSHePressVaporIsolA->ConnectPort( 0, pBundle, 1 );// CL
		pLeftOMSHePressVaporIsolB->ConnectPort( 2, pBundle, 2 );// OP
		pLeftOMSHePressVaporIsolB->ConnectPort( 0, pBundle, 3 );// CL
		pLeftOMSTankIsolationA->ConnectPort( 2, pBundle, 4 );// OP
		pLeftOMSTankIsolationA->ConnectPort( 0, pBundle, 5 );// CL
		pLeftOMSTankIsolationB->ConnectPort( 2, pBundle, 6 );// OP
		pLeftOMSTankIsolationB->ConnectPort( 0, pBundle, 7 );// CL
		pLeftOMSTankIsolationA_TB->SetInput( 0, pBundle, 8, TB_OP );
		pLeftOMSTankIsolationA_TB->SetInput( 1, pBundle, 9, TB_CL );
		pLeftOMSTankIsolationB_TB->SetInput( 0, pBundle, 10, TB_OP );
		pLeftOMSTankIsolationB_TB->SetInput( 1, pBundle, 11, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "RightOMS_DC", 16 );
		pRightOMSHePressVaporIsolA->ConnectPort( 2, pBundle, 0 );// OP
		pRightOMSHePressVaporIsolA->ConnectPort( 0, pBundle, 1 );// CL
		pRightOMSHePressVaporIsolB->ConnectPort( 2, pBundle, 2 );// OP
		pRightOMSHePressVaporIsolB->ConnectPort( 0, pBundle, 3 );// CL
		pRightOMSTankIsolationA->ConnectPort( 2, pBundle, 4 );// OP
		pRightOMSTankIsolationA->ConnectPort( 0, pBundle, 5 );// CL
		pRightOMSTankIsolationB->ConnectPort( 2, pBundle, 6 );// OP
		pRightOMSTankIsolationB->ConnectPort( 0, pBundle, 7 );// CL
		pRightOMSTankIsolationA_TB->SetInput( 0, pBundle, 8, TB_OP );
		pRightOMSTankIsolationA_TB->SetInput( 1, pBundle, 9, TB_CL );
		pRightOMSTankIsolationB_TB->SetInput( 0, pBundle, 10, TB_OP );
		pRightOMSTankIsolationB_TB->SetInput( 1, pBundle, 11, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "OMS_Crossfeed_DC", 16 );
		pLeftOMSCrossfeedA->ConnectPort( 2, pBundle, 0 );// OP
		pLeftOMSCrossfeedA->ConnectPort( 0, pBundle, 1 );// CL
		pLeftOMSCrossfeedB->ConnectPort( 2, pBundle, 2 );// OP
		pLeftOMSCrossfeedB->ConnectPort( 0, pBundle, 3 );// CL
		pRightOMSCrossfeedA->ConnectPort( 2, pBundle, 4 );// OP
		pRightOMSCrossfeedA->ConnectPort( 0, pBundle, 5 );// CL
		pRightOMSCrossfeedB->ConnectPort( 2, pBundle, 6 );// OP
		pRightOMSCrossfeedB->ConnectPort( 0, pBundle, 7 );// CL
		pLeftOMSCrossfeedA_TB->SetInput( 0, pBundle, 8, TB_OP );
		pLeftOMSCrossfeedA_TB->SetInput( 1, pBundle, 9, TB_CL );
		pLeftOMSCrossfeedB_TB->SetInput( 0, pBundle, 10, TB_OP );
		pLeftOMSCrossfeedB_TB->SetInput( 1, pBundle, 11, TB_CL );
		pRightOMSCrossfeedA_TB->SetInput( 0, pBundle, 12, TB_OP );
		pRightOMSCrossfeedA_TB->SetInput( 1, pBundle, 13, TB_CL );
		pRightOMSCrossfeedB_TB->SetInput( 0, pBundle, 14, TB_OP );
		pRightOMSCrossfeedB_TB->SetInput( 1, pBundle, 15, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_HePress_TankIsol_SW", 16 );
		pFwdRCSHePressA->ConnectPort( 2, pBundle, 0 );// OP
		pFwdRCSHePressA->ConnectPort( 0, pBundle, 1 );// CL
		pFwdRCSHePressB->ConnectPort( 2, pBundle, 2 );// OP
		pFwdRCSHePressB->ConnectPort( 0, pBundle, 3 );// CL
		pFwdRCSTankIsolation12->ConnectPort( 2, pBundle, 4 );// OP
		pFwdRCSTankIsolation12->ConnectPort( 0, pBundle, 5 );// CL
		pFwdRCSTankIsolation345->ConnectPort( 2, pBundle, 6 );// OP
		pFwdRCSTankIsolation345->ConnectPort( 0, pBundle, 7 );// CL

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_HePress_TankIsol_TB", 16 );
		pFwdRCSHePressA_TB->SetInput( 0, pBundle, 0, TB_OP );
		pFwdRCSHePressA_TB->SetInput( 1, pBundle, 1, TB_CL );
		pFwdRCSHePressB_TB->SetInput( 0, pBundle, 2, TB_OP );
		pFwdRCSHePressB_TB->SetInput( 1, pBundle, 3, TB_CL );
		pFwdRCSTankIsolation12_TB->SetInput( 0, pBundle, 4, TB_OP );
		pFwdRCSTankIsolation12_TB->SetInput( 1, pBundle, 5, TB_CL );
		pFwdRCSTankIsolation345_TB->SetInput( 0, pBundle, 6, TB_OP );
		pFwdRCSTankIsolation345_TB->SetInput( 1, pBundle, 7, TB_CL );

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_ManifIsol_SW", 16 );
		pFwdRCSManifoldIsolation1->ConnectPort( 2, pBundle, 0 );// OP
		pFwdRCSManifoldIsolation1->ConnectPort( 0, pBundle, 1 );// CL
		pFwdRCSManifoldIsolation2->ConnectPort( 2, pBundle, 2 );// OP
		pFwdRCSManifoldIsolation2->ConnectPort( 0, pBundle, 3 );// CL
		pFwdRCSManifoldIsolation3->ConnectPort( 2, pBundle, 4 );// OP
		pFwdRCSManifoldIsolation3->ConnectPort( 0, pBundle, 5 );// CL
		pFwdRCSManifoldIsolation4->ConnectPort( 2, pBundle, 6 );// OP
		pFwdRCSManifoldIsolation4->ConnectPort( 0, pBundle, 7 );// CL
		pFwdRCSManifoldIsolation5->ConnectPort( 2, pBundle, 8 );// OP
		pFwdRCSManifoldIsolation5->ConnectPort( 0, pBundle, 9 );// CL

		pBundle = STS()->BundleManager()->CreateBundle( "FwdRCS_ManifIsol_TB", 16 );
		pFwdRCSManifoldIsolation1_TB->SetInput( 0, pBundle, 0, TB_OP );
		pFwdRCSManifoldIsolation1_TB->SetInput( 1, pBundle, 1, TB_CL );
		pFwdRCSManifoldIsolation2_TB->SetInput( 0, pBundle, 2, TB_OP );
		pFwdRCSManifoldIsolation2_TB->SetInput( 1, pBundle, 3, TB_CL );
		pFwdRCSManifoldIsolation3_TB->SetInput( 0, pBundle, 4, TB_OP );
		pFwdRCSManifoldIsolation3_TB->SetInput( 1, pBundle, 5, TB_CL );
		pFwdRCSManifoldIsolation4_TB->SetInput( 0, pBundle, 6, TB_OP );
		pFwdRCSManifoldIsolation4_TB->SetInput( 1, pBundle, 7, TB_CL );
		pFwdRCSManifoldIsolation5_TB->SetInput( 0, pBundle, 8, TB_OP );
		pFwdRCSManifoldIsolation5_TB->SetInput( 1, pBundle, 9, TB_CL );

		AtlantisPanel::Realize();
		return;
	}

	void PanelO8::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_O8, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_O8,
			_V( 0.202423, 3.1858, 13.6083 ) + ofs, _V( 0.710853, 3.1858, 13.6083 ) + ofs,
			_V( 0.202423, 3.01485, 14.3133 ) + ofs, _V( 0.710853, 3.01474, 14.3133 ) + _V( 0.001, 0.001, 0.001 ) + ofs );

		return;
	}

};
