/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/07/08   GLS
2021/06/01   GLS
2021/06/02   GLS
2021/06/07   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/02   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "PanelO6.h"
#include "StandardSwitch.h"
#include "StandardSwitchCover.h"
#include "PushButton.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_o6.h"

namespace vc {

	PanelO6::PanelO6(Atlantis* _sts):AtlantisPanel(_sts, "O6")
	{
		//oapiWriteLog("(PanelO6::PanelO6) Enter constructor.");

		DefineMesh( MESHNAME_PANELO6 );

		/*Add(pLGlareShieldFlood	= new StdSwitch3(_sts, "L GLRSHLD FLOOD"));
		pLGlareShieldFlood->SetLabel(0, "OFF");
		pLGlareShieldFlood->SetLabel(1, "VAR");
		pLGlareShieldFlood->SetLabel(2, "BRIGHT");*/

		Add( pStarTrackerDoorPositionY = new StandardTalkback3( _sts, "STAR TRACKER DOOR POSITION -Y" ) );
		Add( pStarTrackerDoorPositionZ = new StandardTalkback3( _sts, "STAR TRACKER DOOR POSITION -Z" ) );

		Add( pStarTrackerDoorControlSys1Cover = new StandardSwitchCover( _sts, "STAR TRACKER DOOR CONTROL SYS 1 Cover" ) );
		Add( pStarTrackerDoorControlSys2Cover = new StandardSwitchCover( _sts, "STAR TRACKER DOOR CONTROL SYS 2 Cover" ) );

		Add( pStarTrackerDoorControlSys1 = new StdSwitch3( _sts, "STAR TRACKER DOOR CONTROL SYS 1" ) );
		pStarTrackerDoorControlSys1->SetLabel( 0, "CLOSE" );
		pStarTrackerDoorControlSys1->SetLabel( 1, "OFF" );
		pStarTrackerDoorControlSys1->SetLabel( 2, "OPEN" );

		Add( pStarTrackerDoorControlSys2 = new StdSwitch3( _sts, "STAR TRACKER DOOR CONTROL SYS 2" ) );
		pStarTrackerDoorControlSys2->SetLabel( 0, "CLOSE" );
		pStarTrackerDoorControlSys2->SetLabel( 1, "OFF" );
		pStarTrackerDoorControlSys2->SetLabel( 2, "OPEN" );

		Add( pStarTrackerPowerY = new StdSwitch2( _sts, "STAR TRACKER POWER -Y" ) );
		pStarTrackerPowerY->SetLabel( 0, "OFF" );
		pStarTrackerPowerY->SetLabel( 1, "ON" );

		Add( pStarTrackerPowerZ = new StdSwitch2( _sts, "STAR TRACKER POWER -Z" ) );
		pStarTrackerPowerZ->SetLabel( 0, "OFF" );
		pStarTrackerPowerZ->SetLabel( 1, "ON" );

		Add( pAnnunciatorLampTest = new StdSwitch3( _sts, "ANNUNCIATOR LAMP TEST" ) );

		Add( pAnnunciatorBusSelectACA1 = new StdSwitch3( _sts, "ANNUNCIATOR BUS SELECT ACA 1" ) );
		pAnnunciatorBusSelectACA1->SetLabel( 0, "MN B" );
		pAnnunciatorBusSelectACA1->SetLabel( 1, "OFF" );
		pAnnunciatorBusSelectACA1->SetLabel( 2, "MN A" );
		pAnnunciatorBusSelectACA1->SetInitialPosition( 2 );

		Add( pAnnunciatorBusSelectACA23 = new StdSwitch3( _sts, "ANNUNCIATOR BUS SELECT ACA 2/3" ) );
		pAnnunciatorBusSelectACA23->SetLabel( 0, "MN C" );
		pAnnunciatorBusSelectACA23->SetLabel( 1, "OFF" );
		pAnnunciatorBusSelectACA23->SetLabel( 2, "MN B" );
		pAnnunciatorBusSelectACA23->SetInitialPosition( 2 );

		/*
		StdSwitch3* pLeftSeatCenterFlood;
		StdSwitch2* pUHFXmitFreq;
		StdSwitch2* pUHFSPLXPowerAmp;
		StdSwitch2* pUHFSquelch;
		StdSwitch3* pMTU;
		StdSwitch2* pIDP1;
		StdSwitch2* pIDP2;
		StdSwitch2* pIDP3;
		StdSwitch2* pIDP4;*/

		Add( pMDMPL1 = new StdSwitch2( _sts, "MDM PL1" ) );
		pMDMPL1->SetLabel( 0, "OFF" );
		pMDMPL1->SetLabel( 1, "ON" );
		pMDMPL1->SetInitialPosition( 1 );

		Add( pMDMPL2 = new StdSwitch2( _sts, "MDM PL2" ) );
		pMDMPL2->SetLabel( 0, "OFF" );
		pMDMPL2->SetLabel( 1, "ON" );
		pMDMPL2->SetInitialPosition( 1 );

		Add( pMDMPL3 = new StdSwitch2( _sts, "MDM PL3" ) );
		pMDMPL3->SetLabel( 0, "OFF" );
		pMDMPL3->SetLabel( 1, "ON" );
		pMDMPL3->SetInitialPosition( 1 );

		Add( pMDMFA1 = new StdSwitch2( _sts, "MDM FA1" ) );
		pMDMFA1->SetLabel( 0, "OFF" );
		pMDMFA1->SetLabel( 1, "ON" );
		pMDMFA1->SetInitialPosition( 1 );

		Add( pMDMFA2 = new StdSwitch2( _sts, "MDM FA2" ) );
		pMDMFA2->SetLabel( 0, "OFF" );
		pMDMFA2->SetLabel( 1, "ON" );
		pMDMFA2->SetInitialPosition( 1 );

		Add( pMDMFA3 = new StdSwitch2( _sts, "MDM FA3" ) );
		pMDMFA3->SetLabel( 0, "OFF" );
		pMDMFA3->SetLabel( 1, "ON" );
		pMDMFA3->SetInitialPosition( 1 );

		Add( pMDMFA4 = new StdSwitch2( _sts, "MDM FA4" ) );
		pMDMFA4->SetLabel( 0, "OFF" );
		pMDMFA4->SetLabel( 1, "ON" );
		pMDMFA4->SetInitialPosition( 1 );

		Add( pMDMFF1 = new StdSwitch2( _sts, "MDM FF1" ) );
		pMDMFF1->SetLabel( 0, "OFF" );
		pMDMFF1->SetLabel( 1, "ON" );
		pMDMFF1->SetInitialPosition( 1 );

		Add( pMDMFF2 = new StdSwitch2( _sts, "MDM FF2" ) );
		pMDMFF2->SetLabel( 0, "OFF" );
		pMDMFF2->SetLabel( 1, "ON" );
		pMDMFF2->SetInitialPosition( 1 );

		Add( pMDMFF3 = new StdSwitch2( _sts, "MDM FF3" ) );
		pMDMFF3->SetLabel( 0, "OFF" );
		pMDMFF3->SetLabel( 1, "ON" );
		pMDMFF3->SetInitialPosition( 1 );

		Add( pMDMFF4 = new StdSwitch2( _sts, "MDM FF4" ) );
		pMDMFF4->SetLabel( 0, "OFF" );
		pMDMFF4->SetLabel( 1, "ON" );
		pMDMFF4->SetInitialPosition( 1 );

		Add(pGPCPowerCover[0] = new StandardSwitchCover(_sts, "GPC POWER 1 COVER"));

		Add(pGPCPowerCover[1] = new StandardSwitchCover(_sts, "GPC POWER 2 COVER"));

		Add(pGPCPowerCover[2] = new StandardSwitchCover(_sts, "GPC POWER 3 COVER"));

		Add(pGPCPowerCover[3] = new StandardSwitchCover(_sts, "GPC POWER 4 COVER"));

		Add(pGPCPowerCover[4] = new StandardSwitchCover(_sts, "GPC POWER 5 COVER"));

		Add(pGPC1Pwr = new StdSwitch2(_sts, "GPC POWER 1"));
		pGPC1Pwr->SetLabel(0, "OFF");
		pGPC1Pwr->SetLabel(1, "ON");

		Add(pGPC2Pwr = new StdSwitch2(_sts, "GPC POWER 2"));
		pGPC2Pwr->SetLabel(0, "OFF");
		pGPC2Pwr->SetLabel(1, "ON");

		Add(pGPC3Pwr = new StdSwitch2(_sts, "GPC POWER 3"));
		pGPC3Pwr->SetLabel(0, "OFF");
		pGPC3Pwr->SetLabel(1, "ON");

		Add(pGPC4Pwr = new StdSwitch2(_sts, "GPC POWER 4"));
		pGPC4Pwr->SetLabel(0, "OFF");
		pGPC4Pwr->SetLabel(1, "ON");

		Add(pGPC5Pwr = new StdSwitch2(_sts, "GPC POWER 5"));
		pGPC5Pwr->SetLabel(0, "OFF");
		pGPC5Pwr->SetLabel(1, "ON");

		Add( pGPCOutput[0] = new StandardTalkback2( _sts, "GPC Output 1 TB" ) );

		Add( pGPCOutput[1] = new StandardTalkback2( _sts, "GPC Output 2 TB" ) );

		Add( pGPCOutput[2] = new StandardTalkback2( _sts, "GPC Output 3 TB" ) );

		Add( pGPCOutput[3] = new StandardTalkback2( _sts, "GPC Output 4 TB" ) );

		Add( pGPCOutput[4] = new StandardTalkback2( _sts, "GPC Output 5 TB" ) );

		Add(pGPCOutputCover[0] = new StandardSwitchCover(_sts, "GPC OUTPUT 1 COVER"));

		Add(pGPCOutputCover[1] = new StandardSwitchCover(_sts, "GPC OUTPUT 2 COVER"));

		Add(pGPCOutputCover[2] = new StandardSwitchCover(_sts, "GPC OUTPUT 3 COVER"));

		Add(pGPCOutputCover[3] = new StandardSwitchCover(_sts, "GPC OUTPUT 4 COVER"));

		Add(pGPCOutputCover[4] = new StandardSwitchCover(_sts, "GPC OUTPUT 5 COVER"));

		Add(pGPC1Output = new StdSwitch3(_sts, "GPC OUTPUT 1"));
		pGPC1Output->SetLabel(0, "TERMINATE");
		pGPC1Output->SetLabel(1, "NORMAL");
		pGPC1Output->SetLabel(2, "BACKUP");

		Add(pGPC2Output = new StdSwitch3(_sts, "GPC OUTPUT 2"));
		pGPC2Output->SetLabel(0, "TERMINATE");
		pGPC2Output->SetLabel(1, "NORMAL");
		pGPC2Output->SetLabel(2, "BACKUP");

		Add(pGPC3Output = new StdSwitch3(_sts, "GPC OUTPUT 3"));
		pGPC3Output->SetLabel(0, "TERMINATE");
		pGPC3Output->SetLabel(1, "NORMAL");
		pGPC3Output->SetLabel(2, "BACKUP");

		Add(pGPC4Output = new StdSwitch3(_sts, "GPC OUTPUT 4"));
		pGPC4Output->SetLabel(0, "TERMINATE");
		pGPC4Output->SetLabel(1, "NORMAL");
		pGPC4Output->SetLabel(2, "BACKUP");

		Add(pGPC5Output = new StdSwitch3(_sts, "GPC OUTPUT 5"));
		pGPC5Output->SetLabel(0, "TERMINATE");
		pGPC5Output->SetLabel(1, "NORMAL");
		pGPC5Output->SetLabel(2, "BACKUP");

		Add(pIPLSource = new StdSwitch3(_sts, "IPL SOURCE"));
		pIPLSource->SetLabel(0, "MMU2");
		pIPLSource->SetLabel(1, "OFF");
		pIPLSource->SetLabel(2, "MMU1");

		Add(pIPL1 = new PushButton(_sts, "IPL1"));

		Add(pIPL2 = new PushButton(_sts, "IPL2"));

		Add(pIPL3 = new PushButton(_sts, "IPL3"));

		Add(pIPL4 = new PushButton(_sts, "IPL4"));

		Add(pIPL5 = new PushButton(_sts, "IPL5"));

		Add( pGPCMode[0] = new StandardTalkback3( _sts, "GPC MODE 1 TB" ) );

		Add( pGPCMode[1] = new StandardTalkback3( _sts, "GPC MODE 2 TB" ) );

		Add( pGPCMode[2] = new StandardTalkback3( _sts, "GPC MODE 3 TB" ) );

		Add( pGPCMode[3] = new StandardTalkback3( _sts, "GPC MODE 4 TB" ) );

		Add( pGPCMode[4] = new StandardTalkback3( _sts, "GPC MODE 5 TB" ) );

		Add(pGPC1Mode = new LockableLever3(_sts, "GPC MODE 1"));
		pGPC1Mode->SetLabel(0, "HALT");
		pGPC1Mode->SetLabel(1, "STBY");
		pGPC1Mode->SetLabel(2, "RUN");

		Add(pGPC2Mode = new LockableLever3(_sts, "GPC MODE 2"));
		pGPC2Mode->SetLabel(0, "HALT");
		pGPC2Mode->SetLabel(1, "STBY");
		pGPC2Mode->SetLabel(2, "RUN");

		Add(pGPC3Mode = new LockableLever3(_sts, "GPC MODE 3"));
		pGPC3Mode->SetLabel(0, "HALT");
		pGPC3Mode->SetLabel(1, "STBY");
		pGPC3Mode->SetLabel(2, "RUN");

		Add(pGPC4Mode = new LockableLever3(_sts, "GPC MODE 4"));
		pGPC4Mode->SetLabel(0, "HALT");
		pGPC4Mode->SetLabel(1, "STBY");
		pGPC4Mode->SetLabel(2, "RUN");

		Add(pGPC5Mode = new LockableLever3(_sts, "GPC MODE 5"));
		pGPC5Mode->SetLabel(0, "HALT");
		pGPC5Mode->SetLabel(1, "STBY");
		pGPC5Mode->SetLabel(2, "RUN");

		//oapiWriteLog("(PanelO6::PanelO6) Leave constructor.");
	}

	PanelO6::~PanelO6()
	{
	}

	void PanelO6::DefineVC()
	{
		//oapiWriteLog("(PanelO6::Define VC)");

		VECTOR3 switch_rot = _V( 1, 0, 0 );
		VECTOR3 SWITCH_VERTICAL = _V( 1.0, 0.0, 0.0 );

		AddAIDToMouseEventList(AID_O6);

		pStarTrackerDoorPositionY->DefineMeshGroup( GetVCMeshIndex(), GRP_DS1_O6_VC );

		pStarTrackerDoorPositionZ->DefineMeshGroup( GetVCMeshIndex(), GRP_DS2_O6_VC );

		pStarTrackerDoorControlSys1Cover->SetMouseRegion( AID_O6, 0, 0.64f, 0.175973f, 0.7078f, 0.2315f );
		pStarTrackerDoorControlSys1Cover->SetMouseRegion( AID_O6, 1, 0.656091f, 0.236236f, 0.700474f, 0.251363f );
		pStarTrackerDoorControlSys1Cover->DefineGroup( GRP_COVER2_O6_VC );
		pStarTrackerDoorControlSys1Cover->SetReference( _V( -0.3814, 3.1445, 13.7718 ), -SWITCH_VERTICAL );

		pStarTrackerDoorControlSys2Cover->SetMouseRegion( AID_O6, 0, 0.724671f, 0.175973f, 0.7706f, 0.2315f );
		pStarTrackerDoorControlSys2Cover->SetMouseRegion( AID_O6, 1, 0.724671f, 0.236236f, 0.764189f, 0.251363f );
		pStarTrackerDoorControlSys2Cover->DefineGroup( GRP_COVER3_O6_VC );
		pStarTrackerDoorControlSys2Cover->SetReference( _V( -0.3814, 3.1445, 13.7718 ), -SWITCH_VERTICAL );

		pStarTrackerDoorControlSys1->DefineGroup( GRP_S2_O6_VC );
		pStarTrackerDoorControlSys1->SetMouseRegion( AID_O6, 0.656091f, 0.1767f, 0.700474f, 0.227679f );
		pStarTrackerDoorControlSys1->SetReference( _V( -0.3818, 3.1533, 13.7537 ), SWITCH_VERTICAL );
		pStarTrackerDoorControlSys1->SetInitialAnimState( 0.5f );

		pStarTrackerDoorControlSys2->DefineGroup( GRP_S3_O6_VC );
		pStarTrackerDoorControlSys2->SetMouseRegion( AID_O6, 0.7267f, 0.1767f, 0.764189f, 0.227679f );
		pStarTrackerDoorControlSys2->SetReference( _V( -0.3818, 3.1533, 13.7537 ), SWITCH_VERTICAL );
		pStarTrackerDoorControlSys2->SetInitialAnimState( 0.5f );

		pStarTrackerPowerY->DefineGroup( GRP_S4_O6_VC );
		pStarTrackerPowerY->SetMouseRegion( AID_O6, 0.821986f, 0.179938f, 0.863477f, 0.215327f );
		pStarTrackerPowerY->SetReference( _V( -0.3818, 3.1533, 13.7537 ), SWITCH_VERTICAL );
		pStarTrackerPowerY->SetInitialAnimState( 0.5f );

		pStarTrackerPowerZ->DefineGroup( GRP_S5_O6_VC );
		pStarTrackerPowerZ->SetMouseRegion( AID_O6, 0.874427f, 0.179938f, 0.920179f, 0.215327f );
		pStarTrackerPowerZ->SetReference( _V( -0.3818, 3.1533, 13.7537 ), SWITCH_VERTICAL );
		pStarTrackerPowerZ->SetInitialAnimState( 0.5f );

		pAnnunciatorLampTest->SetInitialAnimState( 0.5f );
		pAnnunciatorLampTest->DefineGroup( GRP_S14_O6_VC );
		pAnnunciatorLampTest->SetReference( _V( -0.6506, 3.0979, 13.9709 ), switch_rot );
		pAnnunciatorLampTest->SetMouseRegion( AID_O6, 0.109378f, 0.497310f, 0.155600f, 0.532509f );
		pAnnunciatorLampTest->SetSpringLoaded( true, 0 );
		pAnnunciatorLampTest->SetSpringLoaded( true, 2 );

		pAnnunciatorBusSelectACA1->SetInitialAnimState( 0.5f );
		pAnnunciatorBusSelectACA1->DefineGroup( GRP_S12_O6_VC );
		pAnnunciatorBusSelectACA1->SetReference( _V( -0.6506, 3.0979, 13.9709 ), switch_rot );
		pAnnunciatorBusSelectACA1->SetMouseRegion( AID_O6, 0.228373f, 0.496051f, 0.271396f, 0.531983f );

		pAnnunciatorBusSelectACA23->SetInitialAnimState( 0.5f );
		pAnnunciatorBusSelectACA23->DefineGroup( GRP_S13_O6_VC );
		pAnnunciatorBusSelectACA23->SetReference( _V( -0.6506, 3.0979, 13.9709 ), switch_rot );
		pAnnunciatorBusSelectACA23->SetMouseRegion( AID_O6, 0.292820f, 0.496975f, 0.334038f, 0.531239f );

		pMDMPL1->SetInitialAnimState( 0.5f );
		pMDMPL1->DefineGroup( GRP_S52_O6_VC );
		pMDMPL1->SetReference( _V( -0.664953, 3.06445, 14.1091 ), switch_rot );
		pMDMPL1->SetMouseRegion( AID_O6, 0.110233f, 0.692774f, 0.157230f, 0.728264f );

		pMDMPL2->SetInitialAnimState( 0.5f );
		pMDMPL2->DefineGroup( GRP_S20_O6_VC );
		pMDMPL2->SetReference( _V( -0.663594, 3.04795, 14.176 ), switch_rot );
		pMDMPL2->SetMouseRegion( AID_O6, 0.112582f, 0.787610f, 0.159599f, 0.822547f );

		pMDMPL3->SetInitialAnimState( 0.5f );
		pMDMPL3->DefineGroup( GRP_S25_O6_VC );
		pMDMPL3->SetReference( _V( -0.663355, 3.03285, 14.2362 ), switch_rot );
		pMDMPL3->SetMouseRegion( AID_O6, 0.112744f, 0.874348f, 0.159690f, 0.909208f );

		pMDMFA1->SetInitialAnimState( 0.5f );
		pMDMFA1->DefineGroup( GRP_S21_O6_VC );
		pMDMFA1->SetReference( _V( -0.663594, 3.04795, 14.176 ), switch_rot );
		pMDMFA1->SetMouseRegion( AID_O6, 0.170660f, 0.787373f, 0.231717f, 0.823308f );

		pMDMFA2->SetInitialAnimState( 0.5f );
		pMDMFA2->DefineGroup( GRP_S22_O6_VC );
		pMDMFA2->SetReference( _V( -0.663594, 3.04795, 14.176 ), switch_rot );
		pMDMFA2->SetMouseRegion( AID_O6, 0.241833f, 0.788584f, 0.288492f, 0.822108f );

		pMDMFA3->SetInitialAnimState( 0.5f );
		pMDMFA3->DefineGroup( GRP_S23_O6_VC );
		pMDMFA3->SetReference( _V( -0.663594, 3.04795, 14.176 ), switch_rot );
		pMDMFA3->SetMouseRegion( AID_O6, 0.299948f, 0.788957f, 0.359566f, 0.824127f );

		pMDMFA4->SetInitialAnimState( 0.5f );
		pMDMFA4->DefineGroup( GRP_S24_O6_VC );
		pMDMFA4->SetReference( _V( -0.663594, 3.04795, 14.176 ), switch_rot );
		pMDMFA4->SetMouseRegion( AID_O6, 0.371258f, 0.789677f, 0.417264f, 0.823747f );

		pMDMFF1->SetInitialAnimState( 0.5f );
		pMDMFF1->DefineGroup( GRP_S26_O6_VC );
		pMDMFF1->SetReference( _V( -0.663355, 3.03285, 14.2362 ), switch_rot );
		pMDMFF1->SetMouseRegion( AID_O6, 0.170239f, 0.875223f, 0.232148f, 0.910472f );

		pMDMFF2->SetInitialAnimState( 0.5f );
		pMDMFF2->DefineGroup( GRP_S27_O6_VC );
		pMDMFF2->SetReference( _V( -0.663355, 3.03285, 14.2362 ), switch_rot );
		pMDMFF2->SetMouseRegion( AID_O6, 0.243269f, 0.874417f, 0.290890f, 0.908527f );

		pMDMFF3->SetInitialAnimState( 0.5f );
		pMDMFF3->DefineGroup( GRP_S28_O6_VC );
		pMDMFF3->SetReference( _V( -0.663355, 3.03285, 14.2362 ), switch_rot );
		pMDMFF3->SetMouseRegion( AID_O6, 0.300806f, 0.874671f, 0.360112f, 0.910632f );

		pMDMFF4->SetInitialAnimState( 0.5f );
		pMDMFF4->DefineGroup( GRP_S29_O6_VC );
		pMDMFF4->SetReference( _V( -0.663355, 3.03285, 14.2362 ), switch_rot );
		pMDMFF4->SetMouseRegion( AID_O6, 0.373120f, 0.876466f, 0.418497f, 0.909114f );

		pGPCPowerCover[0]->SetMouseRegion( AID_O6, 0, 0.4798f, 0.5008f, 0.5473f, 0.5570f);
		pGPCPowerCover[0]->SetMouseRegion( AID_O6, 1, 0.483795f, 0.561731f, 0.535098f, 0.576666f);
		pGPCPowerCover[0]->DefineGroup( GRP_COVER30_O6_VC );
		pGPCPowerCover[0]->SetReference(_V( -0.4652, 3.0908, 13.9972 ), -SWITCH_VERTICAL);

		pGPCPowerCover[1]->SetMouseRegion( AID_O6, 0, 0.5587f, 0.5008f, 0.6032f, 0.5570f);
		pGPCPowerCover[1]->SetMouseRegion( AID_O6, 1, 0.551317f, 0.561731f, 0.606547f, 0.576666f);
		pGPCPowerCover[1]->DefineGroup( GRP_COVER31_O6_VC );
		pGPCPowerCover[1]->SetReference(_V( -0.4652, 3.0908, 13.9972 ), -SWITCH_VERTICAL);

		pGPCPowerCover[2]->SetMouseRegion( AID_O6, 0, 0.6212f, 0.5008f, 0.6657f, 0.5570f);
		pGPCPowerCover[2]->SetMouseRegion( AID_O6, 1, 0.619886f, 0.561731f, 0.675091f, 0.576666f);
		pGPCPowerCover[2]->DefineGroup( GRP_COVER32_O6_VC );
		pGPCPowerCover[2]->SetReference(_V( -0.4652, 3.0908, 13.9972 ), -SWITCH_VERTICAL);

		pGPCPowerCover[3]->SetMouseRegion( AID_O6, 0, 0.6828f, 0.5008f, 0.7375f, 0.5570f);
		pGPCPowerCover[3]->SetMouseRegion( AID_O6, 1, 0.688901f, 0.561731f, 0.743673f, 0.576666f);
		pGPCPowerCover[3]->DefineGroup( GRP_COVER33_O6_VC );
		pGPCPowerCover[3]->SetReference(_V( -0.4652, 3.0908, 13.9972 ), -SWITCH_VERTICAL);

		pGPCPowerCover[4]->SetMouseRegion( AID_O6, 0, 0.7538f, 0.5008f, 0.8021f, 0.5570f);
		pGPCPowerCover[4]->SetMouseRegion( AID_O6, 1, 0.759426f, 0.561731f, 0.811709f, 0.576666f);
		pGPCPowerCover[4]->DefineGroup( GRP_COVER34_O6_VC );
		pGPCPowerCover[4]->SetReference(_V( -0.4652, 3.0908, 13.9972 ), -SWITCH_VERTICAL);

		pGPC1Pwr->SetMouseRegion( AID_O6, 0.4798f, 0.5008f, 0.5473f, 0.5570f);
		pGPC1Pwr->DefineGroup( GRP_S30_O6_VC );
		pGPC1Pwr->SetReference(_V(0.0, 3.09556, 13.98215), SWITCH_VERTICAL);
		pGPC1Pwr->SetInitialAnimState(0.5f);

		pGPC2Pwr->SetMouseRegion( AID_O6, 0.5587f, 0.5008f, 0.6032f, 0.5570f);
		pGPC2Pwr->DefineGroup( GRP_S31_O6_VC );
		pGPC2Pwr->SetReference(_V(0.0, 3.09556, 13.98215), SWITCH_VERTICAL);
		pGPC2Pwr->SetInitialAnimState(0.5f);

		pGPC3Pwr->SetMouseRegion( AID_O6, 0.6212f, 0.5008f, 0.6657f, 0.5570f);
		pGPC3Pwr->DefineGroup( GRP_S32_O6_VC );
		pGPC3Pwr->SetReference(_V(0.0, 3.09556, 13.98215), SWITCH_VERTICAL);
		pGPC3Pwr->SetInitialAnimState(0.5f);

		pGPC4Pwr->SetMouseRegion( AID_O6, 0.6828f, 0.5008f, 0.7375f, 0.5570f);
		pGPC4Pwr->DefineGroup( GRP_S33_O6_VC );
		pGPC4Pwr->SetReference(_V(0.0, 3.09556, 13.98215), SWITCH_VERTICAL);
		pGPC4Pwr->SetInitialAnimState(0.5f);

		pGPC5Pwr->SetMouseRegion( AID_O6, 0.7538f, 0.5008f, 0.8021f, 0.5570f);
		pGPC5Pwr->DefineGroup( GRP_S34_O6_VC );
		pGPC5Pwr->SetReference(_V(0.0, 3.09556, 13.98215), SWITCH_VERTICAL);
		pGPC5Pwr->SetInitialAnimState(0.5f);

		pGPCOutput[0]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS3_U_O6_VC, GRP_DS3_L_O6_VC );

		pGPCOutput[1]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS4_U_O6_VC, GRP_DS4_L_O6_VC );

		pGPCOutput[2]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS5_U_O6_VC, GRP_DS5_L_O6_VC );

		pGPCOutput[3]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS6_U_O6_VC, GRP_DS6_L_O6_VC );

		pGPCOutput[4]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS7_U_O6_VC, GRP_DS7_L_O6_VC );

		pGPCOutputCover[0]->SetMouseRegion( AID_O6, 0, 0.4798f, 0.6438f, 0.5473f, 0.7007f);
		pGPCOutputCover[0]->SetMouseRegion( AID_O6, 1, 0.483795f, 0.705872f, 0.535098f, 0.723074f);
		pGPCOutputCover[0]->DefineGroup( GRP_COVER35_O6_VC );
		pGPCOutputCover[0]->SetReference(_V( -0.4653, 3.0668, 14.0986 ), -SWITCH_VERTICAL);

		pGPCOutputCover[1]->SetMouseRegion( AID_O6, 0, 0.5587f, 0.6438f, 0.6032f, 0.7007f);
		pGPCOutputCover[1]->SetMouseRegion( AID_O6, 1, 0.551317f, 0.705872f, 0.606547f, 0.723074f);
		pGPCOutputCover[1]->DefineGroup( GRP_COVER36_O6_VC );
		pGPCOutputCover[1]->SetReference(_V( -0.4653, 3.0668, 14.0986 ), -SWITCH_VERTICAL);

		pGPCOutputCover[2]->SetMouseRegion( AID_O6, 0, 0.6212f, 0.6438f, 0.6657f, 0.7007f);
		pGPCOutputCover[2]->SetMouseRegion( AID_O6, 1, 0.619886f, 0.705872f, 0.675091f, 0.723074f);
		pGPCOutputCover[2]->DefineGroup( GRP_COVER37_O6_VC );
		pGPCOutputCover[2]->SetReference(_V( -0.4653, 3.0668, 14.0986 ), -SWITCH_VERTICAL);

		pGPCOutputCover[3]->SetMouseRegion( AID_O6, 0, 0.6828f, 0.6438f, 0.7375f, 0.7007f);
		pGPCOutputCover[3]->SetMouseRegion( AID_O6, 1, 0.688901f, 0.705872f, 0.743673f, 0.723074f);
		pGPCOutputCover[3]->DefineGroup( GRP_COVER38_O6_VC );
		pGPCOutputCover[3]->SetReference(_V( -0.4653, 3.0668, 14.0986 ), -SWITCH_VERTICAL);

		pGPCOutputCover[4]->SetMouseRegion( AID_O6, 0, 0.7538f, 0.6438f, 0.8021f, 0.7007f);
		pGPCOutputCover[4]->SetMouseRegion( AID_O6, 1, 0.759426f, 0.705872f, 0.811709f, 0.723074f);
		pGPCOutputCover[4]->DefineGroup( GRP_COVER39_O6_VC );
		pGPCOutputCover[4]->SetReference(_V( -0.4653, 3.0668, 14.0986 ), -SWITCH_VERTICAL);

		pGPC1Output->SetMouseRegion( AID_O6, 0.4798f, 0.6438f, 0.5473f, 0.7007f);
		pGPC1Output->DefineGroup( GRP_S35_O6_VC );
		pGPC1Output->SetReference(_V(0.0,  3.07197,  14.08016), SWITCH_VERTICAL);
		pGPC1Output->SetInitialAnimState(0.5f);

		pGPC2Output->SetMouseRegion( AID_O6, 0.5587f, 0.6438f, 0.6032f, 0.7007f);
		pGPC2Output->DefineGroup( GRP_S36_O6_VC );
		pGPC2Output->SetReference(_V(0.0,  3.07197,  14.08016), SWITCH_VERTICAL);
		pGPC2Output->SetInitialAnimState(0.5f);

		pGPC3Output->SetMouseRegion( AID_O6, 0.6212f, 0.6438f, 0.6657f, 0.7007f);
		pGPC3Output->DefineGroup( GRP_S37_O6_VC );
		pGPC3Output->SetReference(_V(0.0,  3.07197,  14.08016), SWITCH_VERTICAL);
		pGPC3Output->SetInitialAnimState(0.5f);

		pGPC4Output->SetMouseRegion( AID_O6, 0.6828f, 0.6438f, 0.7375f, 0.7007f);
		pGPC4Output->DefineGroup( GRP_S38_O6_VC );
		pGPC4Output->SetReference(_V(0.0,  3.07197,  14.08016), SWITCH_VERTICAL);
		pGPC4Output->SetInitialAnimState(0.5f);

		pGPC5Output->SetMouseRegion( AID_O6, 0.7538f, 0.6438f, 0.8021f, 0.7007f);
		pGPC5Output->DefineGroup( GRP_S39_O6_VC );
		pGPC5Output->SetReference(_V(0.0,  3.07197,  14.08016), SWITCH_VERTICAL);
		pGPC5Output->SetInitialAnimState(0.5f);

		pIPLSource->SetMouseRegion( AID_O6, 0.8518f, 0.7391f, 0.8936f, 0.7720f);
		pIPLSource->DefineGroup( GRP_S45_O6_VC );
		pIPLSource->SetReference(_V(0.0, 3.056848, 14.14088), SWITCH_VERTICAL);
		pIPLSource->SetInitialAnimState( 0.5f );

		pIPL1->SetMouseRegion( AID_O6, 0.4949f, 0.7365f, 0.5439f, 0.7741f);

		pIPL2->SetMouseRegion( AID_O6, 0.5599f, 0.7365f, 0.6079f, 0.7741f);

		pIPL3->SetMouseRegion( AID_O6, 0.6268f, 0.7365f, 0.6727f, 0.7741f);

		pIPL4->SetMouseRegion( AID_O6, 0.6905f, 0.7365f, 0.7396f, 0.7741f);

		pIPL5->SetMouseRegion( AID_O6, 0.7554f, 0.7365f, 0.8026f, 0.7741f);

		pGPCMode[0]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_O6_VC );

		pGPCMode[1]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS9_O6_VC );

		pGPCMode[2]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS10_O6_VC );

		pGPCMode[3]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS11_O6_VC );

		pGPCMode[4]->DefineMeshGroup( GetVCMeshIndex(), GRP_DS12_O6_VC );

		pGPC1Mode->SetMouseRegion( AID_O6, 0.4798f, 0.8718f, 0.5473f, 0.9117f);
		pGPC1Mode->DefineGroup( GRP_S46_O6_VC );
		pGPC1Mode->SetReference(_V(0.0,  3.033531,  14.23673), SWITCH_VERTICAL);
		pGPC1Mode->SetPullDirection( _V( 0.0, -0.971961, -0.235142 ) );
		pGPC1Mode->SetInitialAnimState(0.5f);

		pGPC2Mode->SetMouseRegion( AID_O6, 0.5587f, 0.8718f, 0.6032f, 0.9117f);
		pGPC2Mode->DefineGroup( GRP_S47_O6_VC );
		pGPC2Mode->SetReference(_V(0.0,  3.033531,  14.23673), SWITCH_VERTICAL);
		pGPC2Mode->SetPullDirection( _V( 0.0, -0.971961, -0.235142 ) );
		pGPC2Mode->SetInitialAnimState(0.5f);

		pGPC3Mode->SetMouseRegion( AID_O6, 0.6212f, 0.8718f, 0.6657f, 0.9117f);
		pGPC3Mode->DefineGroup( GRP_S48_O6_VC );
		pGPC3Mode->SetReference(_V(0.0,  3.033531,  14.23673), SWITCH_VERTICAL);
		pGPC3Mode->SetPullDirection( _V( 0.0, -0.971961, -0.235142 ) );
		pGPC3Mode->SetInitialAnimState(0.5f);

		pGPC4Mode->SetMouseRegion( AID_O6, 0.6828f, 0.8718f, 0.7375f, 0.9117f);
		pGPC4Mode->DefineGroup( GRP_S49_O6_VC );
		pGPC4Mode->SetReference(_V(0.0,  3.033531,  14.23673), SWITCH_VERTICAL);
		pGPC4Mode->SetPullDirection( _V( 0.0, -0.971961, -0.235142 ) );
		pGPC4Mode->SetInitialAnimState(0.5f);

		pGPC5Mode->SetMouseRegion( AID_O6, 0.7538f, 0.8718f, 0.8021f, 0.9117f);
		pGPC5Mode->DefineGroup( GRP_S50_O6_VC );
		pGPC5Mode->SetReference(_V(0.0,  3.033531,  14.23673), SWITCH_VERTICAL);
		pGPC5Mode->SetPullDirection( _V( 0.0, -0.971961, -0.235142 ) );
		pGPC5Mode->SetInitialAnimState(0.5f);
		return;
	}

	void PanelO6::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		if (dipSTPowerZ && dipCBSTPowerZ) dopSTPowerZ.SetLine();
		else dopSTPowerZ.ResetLine();

		if (dipSTPowerY && dipCBSTPowerY) dopSTPowerY.SetLine();
		else dopSTPowerY.ResetLine();

		if (STAR_TRACKER_Y_DOOR_CLS_1 || STAR_TRACKER_Y_DOOR_CLS_2) dopSTDoorY_CL.SetLine();
		else dopSTDoorY_CL.ResetLine();

		if (STAR_TRACKER_Y_DOOR_OP_1 || STAR_TRACKER_Y_DOOR_OP_2) dopSTDoorY_OP.SetLine();
		else dopSTDoorY_OP.ResetLine();

		if (STAR_TRACKER_Z_DOOR_CLS_1 || STAR_TRACKER_Z_DOOR_CLS_2) dopSTDoorZ_CL.SetLine();
		else dopSTDoorZ_CL.ResetLine();

		if (STAR_TRACKER_Z_DOOR_OP_1 || STAR_TRACKER_Z_DOOR_OP_2) dopSTDoorZ_OP.SetLine();
		else dopSTDoorZ_OP.ResetLine();
		return;
	}

	void PanelO6::Realize()
	{
		DiscreteBundle* pBundleO6 = STS()->BundleManager()->CreateBundle( "O6_INTERNAL", 16 );
		pStarTrackerPowerZ->ConnectPort( 1, pBundleO6, 0 );
		pStarTrackerPowerY->ConnectPort( 1, pBundleO6, 1 );
		dipSTPowerZ.Connect( pBundleO6, 0 );
		dipSTPowerY.Connect( pBundleO6, 1 );

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "STAR_TRACKER_POWER", 16 );
		dipCBSTPowerZ.Connect( pBundle, 0 );
		dipCBSTPowerY.Connect( pBundle, 1 );
		dopSTPowerZ.Connect( pBundle, 2 );
		dopSTPowerY.Connect( pBundle, 3 );
		pStarTrackerDoorControlSys1->ConnectPort( 0, pBundle, 4 );// CLOSE
		pStarTrackerDoorControlSys1->ConnectPort( 2, pBundle, 5 );// OPEN
		pStarTrackerDoorControlSys2->ConnectPort( 0, pBundle, 6 );// CLOSE
		pStarTrackerDoorControlSys2->ConnectPort( 2, pBundle, 7 );// OPEN

		pBundle = STS()->BundleManager()->CreateBundle( "STAR_TRACKER_DOORS_FMC", 16 );
		STAR_TRACKER_Y_DOOR_CLS_1.Connect( pBundle, 0 );
		STAR_TRACKER_Y_DOOR_CLS_2.Connect( pBundle, 1 );
		STAR_TRACKER_Y_DOOR_OP_1.Connect( pBundle, 2 );
		STAR_TRACKER_Y_DOOR_OP_2.Connect( pBundle, 3 );
		//SYS_1_MOTOR_1_PWR.Connect( pBundle, 4 );
		//SYS_2_MOTOR_2_PWR.Connect( pBundle, 5 );
		STAR_TRACKER_Z_DOOR_CLS_1.Connect( pBundle, 6 );
		STAR_TRACKER_Z_DOOR_CLS_2.Connect( pBundle, 7 );
		STAR_TRACKER_Z_DOOR_OP_1.Connect( pBundle, 8 );
		STAR_TRACKER_Z_DOOR_OP_2.Connect( pBundle, 9 );
		//SYS_1_MOTOR_2_PWR.Connect( pBundle, 10 );
		//SYS_2_MOTOR_1_PWR.Connect( pBundle, 11 );

		pStarTrackerDoorPositionY->SetInput( 0, pBundleO6, 3, TB_CL );
		pStarTrackerDoorPositionY->SetInput( 1, pBundleO6, 4, TB_OP );
		pStarTrackerDoorPositionZ->SetInput( 0, pBundleO6, 5, TB_CL );
		pStarTrackerDoorPositionZ->SetInput( 1, pBundleO6, 6, TB_OP );
		dopSTDoorY_CL.Connect( pBundleO6, 3 );
		dopSTDoorY_OP.Connect( pBundleO6, 4 );
		dopSTDoorZ_CL.Connect( pBundleO6, 5 );
		dopSTDoorZ_OP.Connect( pBundleO6, 6 );

		pBundle = STS()->BundleManager()->CreateBundle( "ACA", 16 );
		pAnnunciatorBusSelectACA1->ConnectPort( 0, pBundle, 0 );
		pAnnunciatorBusSelectACA1->ConnectPort( 2, pBundle, 1 );
		pAnnunciatorBusSelectACA23->ConnectPort( 0, pBundle, 2 );
		pAnnunciatorBusSelectACA23->ConnectPort( 2, pBundle, 3 );
		pAnnunciatorLampTest->ConnectPort( 2, pBundle, 6 );
		pAnnunciatorLampTest->ConnectPort( 0, pBundle, 7 );

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_Power", 16 );
		pMDMFF1->ConnectPort( 1, pBundle, 0 );
		pMDMFF2->ConnectPort( 1, pBundle, 1 );
		pMDMFF3->ConnectPort( 1, pBundle, 2 );
		pMDMFF4->ConnectPort( 1, pBundle, 3 );
		pMDMFA1->ConnectPort( 1, pBundle, 4 );
		pMDMFA2->ConnectPort( 1, pBundle, 5 );
		pMDMFA3->ConnectPort( 1, pBundle, 6 );
		pMDMFA4->ConnectPort( 1, pBundle, 7 );
		pMDMPL1->ConnectPort( 1, pBundle, 8 );
		pMDMPL2->ConnectPort( 1, pBundle, 9 );
		pMDMPL3->ConnectPort( 1, pBundle, 10 );

		pBundle = STS()->BundleManager()->CreateBundle("O6_GPC1", 16);
		pGPC1Pwr->ConnectPort( 1, pBundle, 0 );
		pGPC1Output->ConnectPort( 0, pBundle, 1 );
		pGPC1Output->ConnectPort( 2, pBundle, 2 );
		pIPL1->output.Connect(pBundle, 3);
		pGPC1Mode->ConnectPort( 0, pBundle, 4 );
		pGPC1Mode->ConnectPort( 2, pBundle, 5 );
		pGPCOutput[0]->SetInput( pBundle, 6, TB_GRAY );
		pGPCMode[0]->SetInput( 0, pBundle, 7, TB_RUN );
		pGPCMode[0]->SetInput( 1, pBundle, 8, TB_IPL );

		pBundle = STS()->BundleManager()->CreateBundle("O6_GPC2", 16);
		pGPC2Pwr->ConnectPort( 1, pBundle, 0 );
		pGPC2Output->ConnectPort( 0, pBundle, 1 );
		pGPC2Output->ConnectPort( 2, pBundle, 2 );
		pIPL2->output.Connect(pBundle, 3);
		pGPC2Mode->ConnectPort( 0, pBundle, 4 );
		pGPC2Mode->ConnectPort( 2, pBundle, 5 );
		pGPCOutput[1]->SetInput( pBundle, 6, TB_GRAY );
		pGPCMode[1]->SetInput( 0, pBundle, 7, TB_RUN );
		pGPCMode[1]->SetInput( 1, pBundle, 8, TB_IPL );

		pBundle = STS()->BundleManager()->CreateBundle("O6_GPC3", 16);
		pGPC3Pwr->ConnectPort( 1, pBundle, 0 );
		pGPC3Output->ConnectPort( 0, pBundle, 1 );
		pGPC3Output->ConnectPort( 2, pBundle, 2 );
		pIPL3->output.Connect(pBundle, 3);
		pGPC3Mode->ConnectPort( 0, pBundle, 4 );
		pGPC3Mode->ConnectPort( 2, pBundle, 5 );
		pGPCOutput[2]->SetInput( pBundle, 6, TB_GRAY );
		pGPCMode[2]->SetInput( 0, pBundle, 7, TB_RUN );
		pGPCMode[2]->SetInput( 1, pBundle, 8, TB_IPL );

		pBundle = STS()->BundleManager()->CreateBundle("O6_GPC4", 16);
		pGPC4Pwr->ConnectPort( 1, pBundle, 0 );
		pGPC4Output->ConnectPort( 0, pBundle, 1 );
		pGPC4Output->ConnectPort( 2, pBundle, 2 );
		pIPL4->output.Connect(pBundle, 3);
		pGPC4Mode->ConnectPort( 0, pBundle, 4 );
		pGPC4Mode->ConnectPort( 2, pBundle, 5 );
		pGPCOutput[3]->SetInput( pBundle, 6, TB_GRAY );
		pGPCMode[3]->SetInput( 0, pBundle, 7, TB_RUN );
		pGPCMode[3]->SetInput( 1, pBundle, 8, TB_IPL );

		pBundle = STS()->BundleManager()->CreateBundle("O6_GPC5", 16);
		pGPC5Pwr->ConnectPort( 1, pBundle, 0 );
		pGPC5Output->ConnectPort( 0, pBundle, 1 );
		pGPC5Output->ConnectPort( 2, pBundle, 2 );
		pIPL5->output.Connect(pBundle, 3);
		pGPC5Mode->ConnectPort( 0, pBundle, 4 );
		pGPC5Mode->ConnectPort( 2, pBundle, 5 );
		pGPCOutput[4]->SetInput( pBundle, 6, TB_GRAY );
		pGPCMode[4]->SetInput( 0, pBundle, 7, TB_RUN );
		pGPCMode[4]->SetInput( 1, pBundle, 8, TB_IPL );

		pBundle = STS()->BundleManager()->CreateBundle("O6_IPL", 16);
		pIPLSource->ConnectPort( 0, pBundle, 0 );
		pIPLSource->ConnectPort( 2, pBundle, 1 );

		AtlantisPanel::Realize();
	}

	void PanelO6::RegisterVC()
	{
		//oapiWriteLog("(PanelO6::RegisterVC) Begin registration.");
		AtlantisPanel::RegisterVC();
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea(AID_O6, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral (AID_O6,
			_V(-0.726224, 3.18582, 13.6082)+ofs, _V(-0.217782, 3.18582, 13.6082)+ofs,
			_V(-0.726224, 3.01496, 14.3133) + ofs, _V(-0.217782, 3.01496, 14.3133) + _V( 0.001, 0.001, 0.001 )+ofs);
	}

};
