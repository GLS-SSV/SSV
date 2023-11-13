/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/08/24   GLS
2021/05/26   GLS
2021/06/02   GLS
2021/06/11   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/07/23   GLS
2023/11/11   GLS
********************************************/
#include "PanelR2.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include <MathSSV.h>
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_r2.h"


namespace vc
{
	PanelR2::PanelR2(Atlantis* psts): AtlantisPanel(psts, "R2")
	{
		DefineMesh( MESHNAME_PANELR2 );

		Add( pMPSPRPLTDumpSequence = new StdSwitch3( psts, "MPS PRPLT DUMP SEQUENCE" ) );
		Add( pMPSPRPLTBackupLH2vlv = new StdSwitch3( psts, "MPS PRPLT BACKUP LH2 VLV" ) );

		Add(pMPSPower[0][0] = new StdSwitch2(psts, "MPS ENGINE POWER LEFT AC2"));
		Add(pMPSPower[0][1] = new StdSwitch2(psts, "MPS ENGINE POWER CTR AC1"));
		Add(pMPSPower[0][2] = new StdSwitch2(psts, "MPS ENGINE POWER RIGHT AC3"));
		Add(pMPSPower[1][0] = new StdSwitch2(psts, "MPS ENGINE POWER LEFT AC3"));
		Add(pMPSPower[1][1] = new StdSwitch2(psts, "MPS ENGINE POWER CTR AC2"));
		Add(pMPSPower[1][2] = new StdSwitch2(psts, "MPS ENGINE POWER RIGHT AC1"));

		Add(pMPSHeIsolA[0] = new StdSwitch3(psts, "MPS He ISOLATION A LEFT"));
		Add(pMPSHeIsolA[1] = new StdSwitch3(psts, "MPS He ISOLATION A CTR"));
		Add(pMPSHeIsolA[2] = new StdSwitch3(psts, "MPS He ISOLATION A RIGHT"));
		Add(pMPSHeIsolB[0] = new StdSwitch3(psts, "MPS He ISOLATION B LEFT"));
		Add(pMPSHeIsolB[1] = new StdSwitch3(psts, "MPS He ISOLATION B CTR"));
		Add(pMPSHeIsolB[2] = new StdSwitch3(psts, "MPS He ISOLATION B RIGHT"));

		Add( pPneuLEngHeXOVR = new StdSwitch3( psts, "MPS PNEUMATICS L ENG He XOVR" ) );
		Add( pPneuHeIsol = new StdSwitch3( psts, "MPS PNEUMATICS He ISOL" ) );

		Add( pHeInterconnect[0] = new StdSwitch3( psts, "MPS He INTERCONNECT LEFT" ) );
		Add( pHeInterconnect[1] = new StdSwitch3( psts, "MPS He INTERCONNECT CTR" ) );
		Add( pHeInterconnect[2] = new StdSwitch3( psts, "MPS He INTERCONNECT RIGHT" ) );

		Add( pLH2UllagePress = new LockableLever2( psts, "MPS LH2 ULLAGE PRESS" ) );

		Add( pAPUReadyToStart[0] = new StandardTalkback2( psts, "APU/HYD READY TO START 1" ) );
		Add( pAPUReadyToStart[1] = new StandardTalkback2( psts, "APU/HYD READY TO START 2" ) );
		Add( pAPUReadyToStart[2] = new StandardTalkback2( psts, "APU/HYD READY TO START 3" ) );

		Add(pAPUOperate[0] = new LockableLever3(psts, "APU OPERATE 1"));
		Add(pAPUOperate[1] = new LockableLever3(psts, "APU OPERATE 2"));
		Add(pAPUOperate[2] = new LockableLever3(psts, "APU OPERATE 3"));

		Add(pHydPumpPress[0] = new LockableLever2(psts, "HYD MAIN PUMP PRESS 1"));
		Add(pHydPumpPress[1] = new LockableLever2(psts, "HYD MAIN PUMP PRESS 2"));
		Add(pHydPumpPress[2] = new LockableLever2(psts, "HYD MAIN PUMP PRESS 3"));

		Add(pAPUCntlrPwr[0] = new LockableLever2(psts, "APU CNTLR PWR 1"));
		Add(pAPUCntlrPwr[1] = new LockableLever2(psts, "APU CNTLR PWR 2"));
		Add(pAPUCntlrPwr[2] = new LockableLever2(psts, "APU CNTLR PWR 3"));

		Add(pAPUFuelTkVlv[0] = new LockableLever2(psts, "APU FUEL TK VLV 1"));
		Add(pAPUFuelTkVlv[1] = new LockableLever2(psts, "APU FUEL TK VLV 2"));
		Add(pAPUFuelTkVlv[2] = new LockableLever2(psts, "APU FUEL TK VLV 3"));

		Add(pBlrCntlrHtr[0] = new StdSwitch3(psts, "BOILER CNTLR/HTR 1"));
		Add(pBlrCntlrHtr[1] = new StdSwitch3(psts, "BOILER CNTLR/HTR 2"));
		Add(pBlrCntlrHtr[2] = new StdSwitch3(psts, "BOILER CNTLR/HTR 3"));

		Add(pBlrPower[0] = new StdSwitch2(psts, "BOILER PWR 1"));
		Add(pBlrPower[1] = new StdSwitch2(psts, "BOILER PWR 2"));
		Add(pBlrPower[2] = new StdSwitch2(psts, "BOILER PWR 3"));

		Add(pBlrN2Supply[0] = new StdSwitch2(psts, "BOILER N2 SUPPLY 1"));
		Add(pBlrN2Supply[1] = new StdSwitch2(psts, "BOILER N2 SUPPLY 2"));
		Add(pBlrN2Supply[2] = new StdSwitch2(psts, "BOILER N2 SUPPLY 3"));

		Add( pETUmbDoorMode = new LockableLever2( psts, "ET UMBILICAL DOOR MODE" ) );
		Add( pETUmbDoorCenterlineLatch = new StdSwitch2( psts, "ET UMBILICAL DOOR CENTERLINE LATCH" ) );
		Add( pETUmbDoorLeft = new StdSwitch3( psts, "ET UMBILICAL DOOR LEFT DOOR" ) );
		Add( pETUmbDoorLeftLatch = new StdSwitch3( psts, "ET UMBILICAL DOOR LEFT LATCH" ) );
		Add( pETUmbDoorRight = new StdSwitch3( psts, "ET UMBILICAL DOOR RIGHT DOOR" ) );
		Add( pETUmbDoorRightLatch = new StdSwitch3( psts, "ET UMBILICAL DOOR RIGHT LATCH" ) );

		Add( pETUmbDoorCLLatch = new StandardTalkback3( psts, "ET UMBILICAL DOOR CENTERLINE LATCH TB" ) );
		Add( pETUmbLDoor = new StandardTalkback3( psts, "ET UMBILICAL DOOR LEFT DOOR TB" ) );
		Add( pETUmbLLatch = new StandardTalkback3( psts, "ET UMBILICAL DOOR LEFT LATCH TB" ) );
		Add( pETUmbRDoor = new StandardTalkback3( psts, "ET UMBILICAL DOOR RIGHT DOOR TB" ) );
		Add( pETUmbRLatch = new StandardTalkback3( psts, "ET UMBILICAL DOOR RIGHT LATCH TB" ) );

		for(int i=0;i<3;i++) {
			pAPUOperate[i]->SetLabel(0, "INJECTOR COOL");
			pAPUOperate[i]->SetLabel(1, "OFF");
			pAPUOperate[i]->SetLabel(2, "START/RUN");
			pHydPumpPress[i]->SetLabel(0, "LOW");
			pHydPumpPress[i]->SetLabel(1, "NORM");
			pAPUCntlrPwr[i]->SetLabel(0, "OFF");
			pAPUCntlrPwr[i]->SetLabel(1, "ON");
			pAPUFuelTkVlv[i]->SetLabel(0, "CLOSE");
			pAPUFuelTkVlv[i]->SetLabel(1, "OPEN");

			pMPSHeIsolA[i]->SetLabel(0, "CLOSE");
			pMPSHeIsolA[i]->SetLabel(1, "GPC");
			pMPSHeIsolA[i]->SetLabel(2, "OPEN");
			pMPSHeIsolB[i]->SetLabel(0, "CLOSE");
			pMPSHeIsolB[i]->SetLabel(1, "GPC");
			pMPSHeIsolB[i]->SetLabel(2, "OPEN");

			pBlrCntlrHtr[i]->SetLabel(2, "A");
			pBlrCntlrHtr[i]->SetLabel(1, "OFF");
			pBlrCntlrHtr[i]->SetLabel(0, "B");
			pBlrPower[i]->SetLabel(1, "ON");
			pBlrPower[i]->SetLabel(0, "OFF");
			pBlrN2Supply[i]->SetLabel(1, "ON");
			pBlrN2Supply[i]->SetLabel(0, "OFF");

			pHeInterconnect[i]->SetLabel(0, "OUT OPEN");
			pHeInterconnect[i]->SetLabel(1, "GPC");
			pHeInterconnect[i]->SetLabel(2, "IN OPEN");

			pMPSPower[0][i]->SetLabel( 1, "ON" );
			pMPSPower[0][i]->SetLabel( 0, "OFF" );
			pMPSPower[1][i]->SetLabel( 1, "ON" );
			pMPSPower[1][i]->SetLabel( 0, "OFF" );
		}

		pETUmbDoorMode->SetLabel( 0, "GPC/MAN" );
		pETUmbDoorMode->SetLabel( 1, "GPC" );

		pETUmbDoorCenterlineLatch->SetLabel(0, "STOW");
		pETUmbDoorCenterlineLatch->SetLabel(1, "GND");
		pETUmbDoorCenterlineLatch->SetInitialPosition(1);

		pETUmbDoorLeft->SetLabel(0, "CLOSE");
		pETUmbDoorLeft->SetLabel(1, "OFF");
		pETUmbDoorLeft->SetLabel(2, "OPEN");
		pETUmbDoorLeftLatch->SetLabel(0, "LATCH");
		pETUmbDoorLeftLatch->SetLabel(1, "OFF");
		pETUmbDoorLeftLatch->SetLabel(2, "RELEASE");

		pETUmbDoorRight->SetLabel(0, "CLOSE");
		pETUmbDoorRight->SetLabel(1, "OFF");
		pETUmbDoorRight->SetLabel(2, "OPEN");
		pETUmbDoorRightLatch->SetLabel(0, "LATCH");
		pETUmbDoorRightLatch->SetLabel(1, "OFF");
		pETUmbDoorRightLatch->SetLabel(2, "RELEASE");

		pMPSPRPLTDumpSequence->SetLabel( 0, "STOP" );
		pMPSPRPLTDumpSequence->SetLabel( 1, "GPC" );
		pMPSPRPLTDumpSequence->SetLabel( 2, "START" );

		pMPSPRPLTBackupLH2vlv->SetLabel( 0, "CLOSE" );
		pMPSPRPLTBackupLH2vlv->SetLabel( 1, "GPC" );
		pMPSPRPLTBackupLH2vlv->SetLabel( 2, "OPEN" );

		pPneuLEngHeXOVR->SetLabel( 0, "CLOSE" );
		pPneuLEngHeXOVR->SetLabel( 1, "GPC" );
		pPneuLEngHeXOVR->SetLabel( 2, "OPEN" );

		pPneuHeIsol->SetLabel( 0, "CLOSE" );
		pPneuHeIsol->SetLabel( 1, "GPC" );
		pPneuHeIsol->SetLabel( 2, "OPEN" );

		pLH2UllagePress->SetLabel( 0, "OPEN" );
		pLH2UllagePress->SetLabel( 1, "AUTO" );
	}

	PanelR2::~PanelR2()
	{
	}

	void PanelR2::RegisterVC()
	{
		//oapiWriteLog("Registering PanelR2");
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea (AID_R2, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBPRESSED | PANEL_MOUSE_LBUP);
		oapiVCSetAreaClickmode_Quadrilateral (AID_R2, _V(0.9524, 1.8417, 14.6602)+ofs, _V(1.4477, 1.9868, 14.6602)+ofs,
			_V(.9524, 1.7286, 13.8048)+ofs, _V(1.4477, 1.8755, 13.8048) + _V( 0.001, 0.001, 0.001 )+ofs);

		return;
	}

	void PanelR2::DefineVC()
	{
		const static VECTOR3 switch_rot = _V(0.95, 0.31225, 0.0);
		const static VECTOR3 switch_pull = Normalize(crossp(_V(0, 0, 1), switch_rot));

		AddAIDToMouseEventList(AID_R2);

		/**** APU 1 ****/
		pAPUOperate[0]->SetMouseRegion( AID_R2, 0.347421f, 0.382021f, 0.412748f, 0.424506f);
		pAPUOperate[0]->SetReference(_V(1.1416, 1.8473, 14.307), switch_rot);
		pAPUOperate[0]->SetPullDirection(switch_pull);
		pAPUOperate[0]->DefineGroup( GRP_S16_R2_VC );
		pAPUOperate[0]->SetInitialAnimState(0.5f);

		pHydPumpPress[0]->SetMouseRegion( AID_R2, 0.364955f, 0.534468f, 0.454298f, 0.568684f);
		pHydPumpPress[0]->SetReference(_V(1.1496, 1.8333, 14.184), switch_rot);
		pHydPumpPress[0]->SetPullDirection(switch_pull);
		pHydPumpPress[0]->DefineGroup( GRP_S26_R2_VC );
		pHydPumpPress[0]->SetInitialAnimState(0.5f);

		pAPUCntlrPwr[0]->SetMouseRegion( AID_R2, 0.495306f, 0.606395f, 0.553809f, 0.649438f);
		pAPUCntlrPwr[0]->SetReference(_V(1.2106, 1.8433, 14.122), switch_rot);
		pAPUCntlrPwr[0]->SetPullDirection(switch_pull);
		pAPUCntlrPwr[0]->DefineGroup( GRP_S32_R2_VC );
		pAPUCntlrPwr[0]->SetInitialAnimState(0.5f);

		pAPUFuelTkVlv[0]->SetMouseRegion( AID_R2, 0.226394f, 0.675783f, 0.271294f, 0.707931f);
		pAPUFuelTkVlv[0]->SetReference(_V(1.0712, 1.7933, 14.0694), switch_rot);
		pAPUFuelTkVlv[0]->SetPullDirection(switch_pull);
		pAPUFuelTkVlv[0]->DefineGroup( GRP_S35_R2_VC );
		pAPUFuelTkVlv[0]->SetInitialAnimState(0.5f);

		/**** APU 2 ****/
		pAPUOperate[1]->SetMouseRegion( AID_R2, 0.412748f, 0.382021f, 0.472092f, 0.424506f);
		pAPUOperate[1]->SetReference(_V(1.1706, 1.8563, 14.306), switch_rot);
		pAPUOperate[1]->SetPullDirection(switch_pull);
		pAPUOperate[1]->DefineGroup( GRP_S17_R2_VC );
		pAPUOperate[1]->SetInitialAnimState(0.5f);

		pHydPumpPress[1]->SetMouseRegion( AID_R2, 0.454298f, 0.534468f, 0.549506f, 0.568684f);
		pHydPumpPress[1]->SetReference(_V(1.1986, 1.8473, 14.182), switch_rot);
		pHydPumpPress[1]->SetPullDirection(switch_pull);
		pHydPumpPress[1]->DefineGroup( GRP_S27_R2_VC );
		pHydPumpPress[1]->SetInitialAnimState(0.5f);

		pAPUCntlrPwr[1]->SetMouseRegion( AID_R2, 0.553809f, 0.606395f, 0.617025f, 0.649438f);
		pAPUCntlrPwr[1]->SetReference(_V(1.2416, 1.8523, 14.121), switch_rot);
		pAPUCntlrPwr[1]->SetPullDirection(switch_pull);
		pAPUCntlrPwr[1]->DefineGroup( GRP_S33_R2_VC );
		pAPUCntlrPwr[1]->SetInitialAnimState(0.5f);

		pAPUFuelTkVlv[1]->SetMouseRegion( AID_R2, 0.318000f, 0.677248f, 0.363841f, 0.707553f);
		pAPUFuelTkVlv[1]->SetReference(_V(1.1164, 1.8064, 14.0684), switch_rot);
		pAPUFuelTkVlv[1]->SetPullDirection(switch_pull);
		pAPUFuelTkVlv[1]->DefineGroup( GRP_S36_R2_VC );
		pAPUFuelTkVlv[1]->SetInitialAnimState(0.5f);

		/**** APU 3 ****/
		pAPUOperate[2]->SetMouseRegion( AID_R2, 0.472092f, 0.382021f, 0.535220f, 0.424506f);
		pAPUOperate[2]->SetReference(_V(1.2006, 1.8643, 14.305), switch_rot);
		pAPUOperate[2]->SetPullDirection(switch_pull);
		pAPUOperate[2]->DefineGroup( GRP_S18_R2_VC );
		pAPUOperate[2]->SetInitialAnimState(0.5f);

		pHydPumpPress[2]->SetMouseRegion( AID_R2, 0.549506f, 0.534468f, 0.625087f, 0.568684f);
		pHydPumpPress[2]->SetReference(_V(1.2446, 1.8613, 14.181), switch_rot);
		pHydPumpPress[2]->SetPullDirection(switch_pull);
		pHydPumpPress[2]->DefineGroup( GRP_S28_R2_VC );
		pHydPumpPress[2]->SetInitialAnimState(0.5f);

		pAPUCntlrPwr[2]->SetMouseRegion( AID_R2, 0.617025f, 0.606395f, 0.682484f, 0.649438f);
		pAPUCntlrPwr[2]->SetReference(_V(1.2726, 1.8613, 14.12), switch_rot);
		pAPUCntlrPwr[2]->SetPullDirection(switch_pull);
		pAPUCntlrPwr[2]->DefineGroup( GRP_S34_R2_VC );
		pAPUCntlrPwr[2]->SetInitialAnimState(0.5f);

		pAPUFuelTkVlv[2]->SetMouseRegion( AID_R2, 0.406730f, 0.679643f, 0.451296f, 0.710359f);
		pAPUFuelTkVlv[2]->SetReference(_V(1.1611, 1.8193, 14.0668), switch_rot);
		pAPUFuelTkVlv[2]->SetPullDirection(switch_pull);
		pAPUFuelTkVlv[2]->DefineGroup( GRP_S37_R2_VC );
		pAPUFuelTkVlv[2]->SetInitialAnimState(0.5f);

		pAPUReadyToStart[0]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS1_U_R2_VC, GRP_DS1_L_R2_VC );
		pAPUReadyToStart[1]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS2_U_R2_VC, GRP_DS2_L_R2_VC );
		pAPUReadyToStart[2]->DefineMeshGroups( GetVCMeshIndex(), GRP_DS3_U_R2_VC, GRP_DS3_L_R2_VC );

		/**** ET Umbilical Doors ****/
		pETUmbDoorMode->SetMouseRegion( AID_R2, 0.100789f, 0.886443f, 0.149363f, 0.915395f );
		pETUmbDoorMode->SetReference(_V( 1.014175, 1.75821, 13.889999 ), switch_rot );
		pETUmbDoorMode->SetPullDirection( switch_pull );
		pETUmbDoorMode->DefineGroup( GRP_S47_R2_VC );
		pETUmbDoorMode->SetInitialAnimState( 0.5f );

		pETUmbDoorCenterlineLatch->SetMouseRegion( AID_R2, 0.193928f, 0.884566f, 0.253453f, 0.916514f);
		pETUmbDoorCenterlineLatch->SetReference(_V(1.062, 1.773, 13.888), switch_rot);
		pETUmbDoorCenterlineLatch->DefineGroup( GRP_S48_R2_VC );
		pETUmbDoorCenterlineLatch->SetInitialAnimState(0.5f);

		pETUmbDoorLeft->SetMouseRegion( AID_R2, 0.292763f, 0.885751f, 0.351700f, 0.920420f);
		pETUmbDoorLeft->SetReference(_V(1.11, 1.787, 13.885), switch_rot);
		pETUmbDoorLeft->DefineGroup( GRP_S49_R2_VC );
		pETUmbDoorLeft->SetInitialAnimState(0.5f);

		pETUmbDoorLeftLatch->SetMouseRegion( AID_R2, 0.375219f, 0.887672f, 0.433632f, 0.922404f);
		pETUmbDoorLeftLatch->SetReference(_V(1.151, 1.799, 13.884), switch_rot);
		pETUmbDoorLeftLatch->DefineGroup( GRP_S50_R2_VC );
		pETUmbDoorLeftLatch->SetInitialAnimState(0.5f);

		pETUmbDoorRight->SetMouseRegion( AID_R2, 0.455335f, 0.889641f, 0.513106f, 0.923580f);
		pETUmbDoorRight->SetReference(_V(1.19, 1.811, 13.883), switch_rot);
		pETUmbDoorRight->DefineGroup( GRP_S51_R2_VC );
		pETUmbDoorRight->SetInitialAnimState(0.5f);

		pETUmbDoorRightLatch->SetMouseRegion( AID_R2, 0.53287f, 0.890511f, 0.590665f, 0.925481f);
		pETUmbDoorRightLatch->SetReference(_V(1.228, 1.822, 13.881), switch_rot);
		pETUmbDoorRightLatch->DefineGroup( GRP_S52_R2_VC );
		pETUmbDoorRightLatch->SetInitialAnimState(0.5f);

		pETUmbDoorCLLatch->DefineMeshGroup( GetVCMeshIndex(), GRP_DS4_R2_VC );

		pETUmbLDoor->DefineMeshGroup( GetVCMeshIndex(), GRP_DS5_R2_VC );

		pETUmbLLatch->DefineMeshGroup( GetVCMeshIndex(), GRP_DS6_R2_VC );

		pETUmbRDoor->DefineMeshGroup( GetVCMeshIndex(), GRP_DS7_R2_VC );

		pETUmbRLatch->DefineMeshGroup( GetVCMeshIndex(), GRP_DS8_R2_VC );

		/**** MPS He Isol A ****/
		pMPSHeIsolA[0]->SetMouseRegion( AID_R2, 0.081538f, 0.322382f, 0.157321f, 0.352672f);
		pMPSHeIsolA[0]->SetReference(_V(1.008, 1.822, 14.372), switch_rot);
		pMPSHeIsolA[0]->DefineGroup( GRP_S56_R2_VC );
		pMPSHeIsolA[0]->SetInitialAnimState(0.5f);

		pMPSHeIsolA[1]->SetMouseRegion( AID_R2, 0.157321f, 0.323196f, 0.239897f, 0.354704f);
		pMPSHeIsolA[1]->SetReference(_V(1.049, 1.834, 14.371), switch_rot);
		pMPSHeIsolA[1]->DefineGroup( GRP_S55_R2_VC );
		pMPSHeIsolA[1]->SetInitialAnimState(0.5f);

		pMPSHeIsolA[2]->SetMouseRegion( AID_R2, 0.239897f, 0.323704f, 0.312041f, 0.354271f);
		pMPSHeIsolA[2]->SetReference(_V(1.089, 1.845, 14.37), switch_rot);
		pMPSHeIsolA[2]->DefineGroup( GRP_S57_R2_VC );
		pMPSHeIsolA[2]->SetInitialAnimState(0.5f);

		/**** MPS He Isol B ****/
		pMPSHeIsolB[0]->SetMouseRegion( AID_R2, 0.085931f, 0.391285f, 0.159351f, 0.422357f);
		pMPSHeIsolB[0]->SetReference(_V(1.008, 1.814, 14.313), switch_rot);
		pMPSHeIsolB[0]->DefineGroup( GRP_S13_R2_VC );
		pMPSHeIsolB[0]->SetInitialAnimState(0.5f);

		pMPSHeIsolB[1]->SetMouseRegion( AID_R2, 0.159351f, 0.389469f, 0.238773f, 0.424157f);
		pMPSHeIsolB[1]->SetReference(_V(1.048, 1.825, 14.312), switch_rot);
		pMPSHeIsolB[1]->DefineGroup( GRP_S12_R2_VC );
		pMPSHeIsolB[1]->SetInitialAnimState(0.5f);

		pMPSHeIsolB[2]->SetMouseRegion( AID_R2, 0.238773f, 0.390728f, 0.310743f, 0.425303f);
		pMPSHeIsolB[2]->SetReference(_V(1.088, 1.837, 14.31), switch_rot);
		pMPSHeIsolB[2]->DefineGroup( GRP_S14_R2_VC );
		pMPSHeIsolB[2]->SetInitialAnimState(0.5f);

		/**** MPS Engine Power ****/
		pMPSPower[0][0]->SetMouseRegion( AID_R2, 0.091011f, 0.177120f, 0.159388f, 0.207124f);
		pMPSPower[0][0]->SetReference(_V(1.009, 1.838, 14.495), switch_rot);
		pMPSPower[0][0]->DefineGroup( GRP_S4_R2_VC );
		pMPSPower[0][0]->SetInitialAnimState(0.5f);

		pMPSPower[0][1]->SetMouseRegion( AID_R2, 0.159388f, 0.178765f, 0.239655f, 0.208946f);
		pMPSPower[0][1]->SetReference(_V(1.05, 1.85, 14.494), switch_rot);
		pMPSPower[0][1]->DefineGroup( GRP_S3_R2_VC );
		pMPSPower[0][1]->SetInitialAnimState(0.5f);

		pMPSPower[0][2]->SetMouseRegion( AID_R2, 0.239655f, 0.179134f, 0.313464f, 0.208574f);
		pMPSPower[0][2]->SetReference(_V(1.088, 1.861, 14.493), switch_rot);
		pMPSPower[0][2]->DefineGroup( GRP_S5_R2_VC );
		pMPSPower[0][2]->SetInitialAnimState(0.5f);

		pMPSPower[1][0]->SetMouseRegion( AID_R2, 0.089520f, 0.244445f, 0.159198f, 0.272745f);
		pMPSPower[1][0]->SetReference(_V(1.008, 1.83, 14.439), switch_rot);
		pMPSPower[1][0]->DefineGroup( GRP_S7_R2_VC );
		pMPSPower[1][0]->SetInitialAnimState(0.5f);

		pMPSPower[1][1]->SetMouseRegion( AID_R2, 0.159198f, 0.246158f, 0.240562f, 0.276445f);
		pMPSPower[1][1]->SetReference(_V(1.05, 1.843, 14.437), switch_rot);
		pMPSPower[1][1]->DefineGroup( GRP_S6_R2_VC );
		pMPSPower[1][1]->SetInitialAnimState(0.5f);

		pMPSPower[1][2]->SetMouseRegion( AID_R2, 0.240562f, 0.247841f, 0.316475f, 0.276847f);
		pMPSPower[1][2]->SetReference(_V(1.091, 1.855, 14.435), switch_rot);
		pMPSPower[1][2]->DefineGroup( GRP_S8_R2_VC );
		pMPSPower[1][2]->SetInitialAnimState(0.5f);

		pMPSPRPLTDumpSequence->SetMouseRegion( AID_R2, 0.089324f, 0.098690f, 0.150280f, 0.130199f );
		pMPSPRPLTDumpSequence->SetReference( _V( 1.0107, 1.8482, 14.5611 ), switch_rot );
		pMPSPRPLTDumpSequence->DefineGroup( GRP_S1_R2_VC );
		pMPSPRPLTDumpSequence->SetInitialAnimState( 0.5f );

		pMPSPRPLTBackupLH2vlv->SetMouseRegion( AID_R2, 0.163286f, 0.101039f, 0.222317f, 0.132316f );
		pMPSPRPLTBackupLH2vlv->SetReference( _V( 1.0475, 1.859, 14.5595 ), switch_rot );
		pMPSPRPLTBackupLH2vlv->DefineGroup( GRP_S2_R2_VC );
		pMPSPRPLTBackupLH2vlv->SetInitialAnimState( 0.5f );

		pPneuLEngHeXOVR->SetMouseRegion( AID_R2, 0.083889f, 0.460774f, 0.151326f, 0.493669f );
		pPneuLEngHeXOVR->SetReference( _V( 1.009, 1.8065, 14.2516 ), switch_rot );
		pPneuLEngHeXOVR->DefineGroup( GRP_S54_R2_VC );
		pPneuLEngHeXOVR->SetInitialAnimState( 0.5f );

		pPneuHeIsol->SetMouseRegion( AID_R2, 0.183902f, 0.463183f, 0.250303f, 0.495449f );
		pPneuHeIsol->SetReference( _V( 1.058, 1.821, 14.2497 ), switch_rot );
		pPneuHeIsol->DefineGroup( GRP_S15_R2_VC );
		pPneuHeIsol->SetInitialAnimState( 0.5f );

		pHeInterconnect[0]->SetMouseRegion( AID_R2, 0.086966f, 0.535918f, 0.150105f, 0.566381f );
		pHeInterconnect[0]->SetReference( _V( 1.0114, 1.7986, 14.187 ), switch_rot );
		pHeInterconnect[0]->DefineGroup( GRP_S10_R2_VC );
		pHeInterconnect[0]->SetInitialAnimState( 0.5f );

		pHeInterconnect[1]->SetMouseRegion( AID_R2, 0.190284f, 0.539667f, 0.237936f, 0.567023f );
		pHeInterconnect[1]->SetReference( _V( 1.0574, 1.8125, 14.1854 ), switch_rot );
		pHeInterconnect[1]->DefineGroup( GRP_S9_R2_VC );
		pHeInterconnect[1]->SetInitialAnimState( 0.5f );

		pHeInterconnect[2]->SetMouseRegion( AID_R2, 0.271724f, 0.542303f, 0.316761f, 0.568987f );
		pHeInterconnect[2]->SetReference( _V( 1.0967, 1.8236, 14.1845 ), switch_rot );
		pHeInterconnect[2]->DefineGroup( GRP_S11_R2_VC );
		pHeInterconnect[2]->SetInitialAnimState( 0.5f );

		pLH2UllagePress->SetMouseRegion( AID_R2, 0.285254f, 0.465080f, 0.334198f, 0.496738f );
		pLH2UllagePress->SetReference( _V( 1.1025, 1.8270, 14.2502 ), switch_rot );
		pLH2UllagePress->SetPullDirection( switch_pull );
		pLH2UllagePress->DefineGroup( GRP_S53_R2_VC );
		pLH2UllagePress->SetInitialAnimState( 0.5f );

		/**** WSB 1 ****/
		pBlrCntlrHtr[0]->SetMouseRegion( AID_R2, 0.547575f, 0.754219f, 0.625464f, 0.788508f);
		pBlrCntlrHtr[0]->SetReference(_V(1.237, 1.84, 13.998), switch_rot);
		pBlrCntlrHtr[0]->DefineGroup( GRP_S41_R2_VC );
		pBlrCntlrHtr[0]->SetInitialAnimState(0.5f);

		pBlrPower[0]->SetMouseRegion( AID_R2, 0.633620f, 0.821740f, 0.697079f, 0.862008f);
		pBlrPower[0]->SetReference(_V(1.281, 1.845, 13.938), switch_rot);
		pBlrPower[0]->DefineGroup( GRP_S38_R2_VC );
		pBlrPower[0]->SetInitialAnimState(0.5f);

		pBlrN2Supply[0]->SetMouseRegion( AID_R2, 0.671214f, 0.890886f, 0.741418f, 0.934839f);
		pBlrN2Supply[0]->SetReference(_V(1.303, 1.844, 13.88), switch_rot);
		pBlrN2Supply[0]->DefineGroup( GRP_S44_R2_VC );
		pBlrN2Supply[0]->SetInitialAnimState(0.5f);

		/**** WSB 2 ****/
		pBlrCntlrHtr[1]->SetMouseRegion( AID_R2, 0.625464f, 0.754219f, 0.693698f, 0.788508f);
		pBlrCntlrHtr[1]->SetReference(_V(1.276, 1.851, 13.997), switch_rot);
		pBlrCntlrHtr[1]->DefineGroup( GRP_S42_R2_VC );
		pBlrCntlrHtr[1]->SetInitialAnimState(0.5f);

		pBlrPower[1]->SetMouseRegion( AID_R2, 0.697079f, 0.821740f, 0.755268f, 0.862008f);
		pBlrPower[1]->SetReference(_V(1.308, 1.853, 13.937), switch_rot);
		pBlrPower[1]->DefineGroup( GRP_S39_R2_VC );
		pBlrPower[1]->SetInitialAnimState(0.5f);

		pBlrN2Supply[1]->SetMouseRegion( AID_R2, 0.741418f, 0.890886f, 0.798522f, 0.934839f);
		pBlrN2Supply[1]->SetReference(_V(1.33, 1.851, 13.878), switch_rot);
		pBlrN2Supply[1]->DefineGroup( GRP_S45_R2_VC );
		pBlrN2Supply[1]->SetInitialAnimState(0.5f);

		/**** WSB 3 ****/
		pBlrCntlrHtr[2]->SetMouseRegion( AID_R2, 0.693698f, 0.754219f, 0.769339f, 0.788508f);
		pBlrCntlrHtr[2]->SetReference(_V(1.314, 1.862, 13.997), switch_rot);
		pBlrCntlrHtr[2]->DefineGroup( GRP_S43_R2_VC );
		pBlrCntlrHtr[2]->SetInitialAnimState(0.5f);

		pBlrPower[2]->SetMouseRegion( AID_R2, 0.755268f, 0.821740f, 0.816670f, 0.862008f);
		pBlrPower[2]->SetReference(_V(1.337, 1.861, 13.936), switch_rot);
		pBlrPower[2]->DefineGroup( GRP_S40_R2_VC );
		pBlrPower[2]->SetInitialAnimState(0.5f);

		pBlrN2Supply[2]->SetMouseRegion( AID_R2, 0.798522f, 0.890886f, 0.875479f, 0.934839f);
		pBlrN2Supply[2]->SetReference(_V(1.358, 1.86, 13.877), switch_rot);
		pBlrN2Supply[2]->DefineGroup( GRP_S46_R2_VC );
		pBlrN2Supply[2]->SetInitialAnimState(0.5f);
	}

	void PanelR2::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		if (dipETUmbDoorMode_GPC.IsSet())
		{
			dopETUmbDoorCenterlineLatch_STOW.ResetLine();
			dopETUmbDoorLeft_CL.ResetLine();
			dopETUmbDoorLeft_OP.ResetLine();
			dopETUmbDoorLeftLatch_LAT.ResetLine();
			dopETUmbDoorLeftLatch_REL.ResetLine();
			dopETUmbDoorRight_CL.ResetLine();
			dopETUmbDoorRight_OP.ResetLine();
			dopETUmbDoorRightLatch_LAT.ResetLine();
			dopETUmbDoorRightLatch_REL.ResetLine();
		}
		else
		{
			if (dipETUmbDoorCenterlineLatch_STOW.IsSet()) dopETUmbDoorCenterlineLatch_STOW.SetLine();
			else dopETUmbDoorCenterlineLatch_STOW.ResetLine();

			if (dipETUmbDoorLeft_CL.IsSet()) dopETUmbDoorLeft_CL.SetLine();
			else dopETUmbDoorLeft_CL.ResetLine();

			if (dipETUmbDoorLeft_OP.IsSet()) dopETUmbDoorLeft_OP.SetLine();
			else dopETUmbDoorLeft_OP.ResetLine();

			if (dipETUmbDoorLeftLatch_LAT.IsSet()) dopETUmbDoorLeftLatch_LAT.SetLine();
			else dopETUmbDoorLeftLatch_LAT.ResetLine();

			if (dipETUmbDoorLeftLatch_REL.IsSet()) dopETUmbDoorLeftLatch_REL.SetLine();
			else dopETUmbDoorLeftLatch_REL.ResetLine();

			if (dipETUmbDoorRight_CL.IsSet()) dopETUmbDoorRight_CL.SetLine();
			else dopETUmbDoorRight_CL.ResetLine();

			if (dipETUmbDoorRight_OP.IsSet()) dopETUmbDoorRight_OP.SetLine();
			else dopETUmbDoorRight_OP.ResetLine();

			if (dipETUmbDoorRightLatch_LAT.IsSet()) dopETUmbDoorRightLatch_LAT.SetLine();
			else dopETUmbDoorRightLatch_LAT.ResetLine();

			if (dipETUmbDoorRightLatch_REL.IsSet()) dopETUmbDoorRightLatch_REL.SetLine();
			else dopETUmbDoorRightLatch_REL.ResetLine();
		}

		if ((CL_LATCH_1_STOW_1.IsSet() && CL_LATCH_2_STOW_1.IsSet()) ||
			(CL_LATCH_1_STOW_2.IsSet() && CL_LATCH_2_STOW_2.IsSet())) dopETUmbDoorCLLatch_STOW.SetLine();
		else dopETUmbDoorCLLatch_STOW.ResetLine();

		if ((LEFT_DOOR_RDY_TO_LCH_1.IsSet() && LEFT_DOOR_RDY_TO_LCH_3.IsSet()) ||
			(LEFT_DOOR_RDY_TO_LCH_2.IsSet() && LEFT_DOOR_RDY_TO_LCH_3.IsSet()) ||
			(LEFT_DOOR_RDY_TO_LCH_1.IsSet() && LEFT_DOOR_RDY_TO_LCH_2.IsSet())) dopETUmbLDoor_CL.SetLine();
		else dopETUmbLDoor_CL.ResetLine();

		if (LEFT_DOOR_OPEN_1.IsSet() || LEFT_DOOR_OPEN_2.IsSet()) dopETUmbLDoor_OP.SetLine();
		else dopETUmbLDoor_OP.ResetLine();

		if (LEFT_DOOR_LATCH_LAT_1.IsSet() || LEFT_DOOR_LATCH_LAT_2.IsSet()) dopETUmbLLatch_LAT.SetLine();
		else dopETUmbLLatch_LAT.ResetLine();

		if (LEFT_DOOR_LATCH_REL_1.IsSet() || LEFT_DOOR_LATCH_REL_2.IsSet()) dopETUmbLLatch_REL.SetLine();
		else dopETUmbLLatch_REL.ResetLine();

		if ((RIGHT_DOOR_RDY_TO_LCH_1.IsSet() && RIGHT_DOOR_RDY_TO_LCH_3.IsSet()) ||
			(RIGHT_DOOR_RDY_TO_LCH_2.IsSet() && RIGHT_DOOR_RDY_TO_LCH_3.IsSet()) ||
			(RIGHT_DOOR_RDY_TO_LCH_1.IsSet() && RIGHT_DOOR_RDY_TO_LCH_2.IsSet())) dopETUmbRDoor_CL.SetLine();
		else dopETUmbRDoor_CL.ResetLine();

		if (RIGHT_DOOR_OPEN_1.IsSet() || RIGHT_DOOR_OPEN_2.IsSet()) dopETUmbRDoor_OP.SetLine();
		else dopETUmbRDoor_OP.ResetLine();

		if (RIGHT_DOOR_LATCH_LAT_1.IsSet() || RIGHT_DOOR_LATCH_LAT_2.IsSet()) dopETUmbRLatch_LAT.SetLine();
		else dopETUmbRLatch_LAT.ResetLine();

		if (RIGHT_DOOR_LATCH_REL_1.IsSet() || RIGHT_DOOR_LATCH_REL_2.IsSet()) dopETUmbRLatch_REL.SetLine();
		else dopETUmbRLatch_REL.ResetLine();
		return;
	}

	void PanelR2::Realize()
	{
		char cbuf[255];

		for(int i=0;i<3;i++) {
			sprintf_s(cbuf, 255, "R2_To_APU%d", i+1);
			DiscreteBundle *pBundle=STS()->BundleManager()->CreateBundle(cbuf, 16);

			pAPUOperate[i]->ConnectPort(0, pBundle, 0);
			pAPUOperate[i]->ConnectPort(2, pBundle, 0); // temporary; THIS IS NOT CORRECT
			pAPUCntlrPwr[i]->ConnectPort(1, pBundle, 1);
			pAPUFuelTkVlv[i]->ConnectPort(1, pBundle, 2);
			pHydPumpPress[i]->ConnectPort(1, pBundle, 3);
			APU_HydraulicPress[i].Connect(pBundle, 4);
			pAPUReadyToStart[i]->SetInput( pBundle, 5, TB_GRAY );

			sprintf_s(cbuf, 255, "WSB%d", i+1);
			pBundle=STS()->BundleManager()->CreateBundle(cbuf, 16);
			pBlrPower[i]->ConnectPort( 1, pBundle, 1);
			pBlrCntlrHtr[i]->ConnectPort( 0, pBundle, 2);
			pBlrCntlrHtr[i]->ConnectPort( 2, pBundle, 3);
			pBlrN2Supply[i]->ConnectPort( 1, pBundle, 4);
		}

		DiscreteBundle* pBundleR2 = STS()->BundleManager()->CreateBundle( "R2_INTERNAL_1", 16 );
		dipETUmbDoorMode_GPC.Connect( pBundleR2, 0 );
		dipETUmbDoorCenterlineLatch_STOW.Connect( pBundleR2, 1 );
		dipETUmbDoorLeft_CL.Connect( pBundleR2, 2 );
		dipETUmbDoorLeft_OP.Connect( pBundleR2, 3 );
		dipETUmbDoorLeftLatch_LAT.Connect( pBundleR2, 4 );
		dipETUmbDoorLeftLatch_REL.Connect( pBundleR2, 5 );
		dipETUmbDoorRight_CL.Connect( pBundleR2, 6 );
		dipETUmbDoorRight_OP.Connect( pBundleR2, 7 );
		dipETUmbDoorRightLatch_LAT.Connect( pBundleR2, 8 );
		dipETUmbDoorRightLatch_REL.Connect( pBundleR2, 9 );

		pETUmbDoorMode->ConnectPort( 1, pBundleR2, 0 );
		pETUmbDoorCenterlineLatch->ConnectPort( 0, pBundleR2, 1 );// stow
		pETUmbDoorLeft->ConnectPort( 0, pBundleR2, 2 );// close door
		pETUmbDoorLeft->ConnectPort( 2, pBundleR2, 3 );// open door
		pETUmbDoorLeftLatch->ConnectPort( 0, pBundleR2, 4 ); // latch
		pETUmbDoorLeftLatch->ConnectPort( 2, pBundleR2, 5 ); // release
		pETUmbDoorRight->ConnectPort( 0, pBundleR2, 6 );// close door
		pETUmbDoorRight->ConnectPort( 2, pBundleR2, 7 );// open door
		pETUmbDoorRightLatch->ConnectPort( 0, pBundleR2, 8 );// latch
		pETUmbDoorRightLatch->ConnectPort( 2, pBundleR2, 9 );// release

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_POWER", 16 );
		dopETUmbDoorCenterlineLatch_STOW.Connect( pBundle, 0 );// stow
		dopETUmbDoorLeft_CL.Connect( pBundle, 1 );// close door
		dopETUmbDoorLeft_OP.Connect( pBundle, 2 );// open door
		dopETUmbDoorLeftLatch_LAT.Connect( pBundle, 3 );// latch
		dopETUmbDoorLeftLatch_REL.Connect( pBundle, 4 );// release
		dopETUmbDoorRight_CL.Connect( pBundle, 5 );// close door
		dopETUmbDoorRight_OP.Connect( pBundle, 6 );// open door
		dopETUmbDoorRightLatch_LAT.Connect( pBundle, 7 );// latch
		dopETUmbDoorRightLatch_REL.Connect( pBundle, 8 );// release

		pBundleR2 = STS()->BundleManager()->CreateBundle( "R2_INTERNAL_2", 16 );
		pETUmbDoorCLLatch->SetInput( 0, pBundleR2, 0, TB_STO );
		pETUmbLDoor->SetInput( 0, pBundleR2, 1, TB_CL );
		pETUmbLDoor->SetInput( 1, pBundleR2, 2, TB_OP );
		pETUmbLLatch->SetInput( 0, pBundleR2, 3, TB_LAT );
		pETUmbLLatch->SetInput( 1, pBundleR2, 4, TB_REL );
		pETUmbRDoor->SetInput( 0, pBundleR2, 5, TB_CL );
		pETUmbRDoor->SetInput( 1, pBundleR2, 6, TB_OP );
		pETUmbRLatch->SetInput( 0, pBundleR2, 7, TB_LAT );
		pETUmbRLatch->SetInput( 1, pBundleR2, 8, TB_REL );

		dopETUmbDoorCLLatch_STOW.Connect( pBundleR2, 0 );
		dopETUmbLDoor_CL.Connect( pBundleR2, 1 );
		dopETUmbLDoor_OP.Connect( pBundleR2, 2 );
		dopETUmbLLatch_LAT.Connect( pBundleR2, 3 );
		dopETUmbLLatch_REL.Connect( pBundleR2, 4 );
		dopETUmbRDoor_CL.Connect( pBundleR2, 5 );
		dopETUmbRDoor_OP.Connect( pBundleR2, 6 );
		dopETUmbRLatch_LAT.Connect( pBundleR2, 7 );
		dopETUmbRLatch_REL.Connect( pBundleR2, 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_AMC", 16 );
		CL_LATCH_1_STOW_1.Connect( pBundle, 0 );
		CL_LATCH_1_STOW_2.Connect( pBundle, 1 );
		//CL_LATCH_1_DEPLOY_1.Connect( pBundle, 2 );
		//CL_LATCH_1_DEPLOY_2.Connect( pBundle, 3 );
		//CL_1_MOTOR_1_PWR.Connect( pBundle, 4 );
		//CL_1_MOTOR_2_PWR.Connect( pBundle, 5 );
		CL_LATCH_2_STOW_1.Connect( pBundle, 6 );
		CL_LATCH_2_STOW_2.Connect( pBundle, 7 );
		//CL_LATCH_2_DEPLOY_1.Connect( pBundle, 8 );
		//CL_LATCH_2_DEPLOY_2.Connect( pBundle, 9 );
		//CL_2_MOTOR_1_PWR.Connect( pBundle, 10 );
		//CL_2_MOTOR_2_PWR.Connect( pBundle, 11 );

		pBundle = STS()->BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_AMC", 16 );
		//LEFT_DOOR_CLOSE_1.Connect( pBundle, 0 );
		//LEFT_DOOR_CLOSE_2.Connect( pBundle, 1 );
		LEFT_DOOR_OPEN_1.Connect( pBundle, 2 );
		LEFT_DOOR_OPEN_2.Connect( pBundle, 3 );
		LEFT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
		LEFT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
		LEFT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
		//LEFT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
		//LEFT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
		LEFT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
		LEFT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
		LEFT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
		LEFT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
		//LEFT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
		//LEFT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

		pBundle = STS()->BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_RIGHT_AMC", 16 );
		//RIGHT_DOOR_CLOSE_1.Connect( pBundle, 0 );
		//RIGHT_DOOR_CLOSE_2.Connect( pBundle, 1 );
		RIGHT_DOOR_OPEN_1.Connect( pBundle, 2 );
		RIGHT_DOOR_OPEN_2.Connect( pBundle, 3 );
		RIGHT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
		RIGHT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
		RIGHT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
		//RIGHT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
		//RIGHT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
		RIGHT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
		RIGHT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
		RIGHT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
		RIGHT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
		//RIGHT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
		//RIGHT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

		pBundle=STS()->BundleManager()->CreateBundle("SSMEC_R2_SWITCHES", 8);
		pMPSPower[0][1]->ConnectPort( 1, pBundle, 0);
		pMPSPower[1][1]->ConnectPort( 1, pBundle, 1);
		pMPSHeIsolA[1]->ConnectPort( 0, pBundle, 2);// CL
		pMPSHeIsolA[1]->ConnectPort( 2, pBundle, 3);// OP
		pMPSHeIsolB[1]->ConnectPort( 0, pBundle, 4);// CL
		pMPSHeIsolB[1]->ConnectPort( 2, pBundle, 5);// OP
		pHeInterconnect[1]->ConnectPort( 0, pBundle, 6);// OUT OPEN
		pHeInterconnect[1]->ConnectPort( 2, pBundle, 7);// IN OPEN

		pBundle=STS()->BundleManager()->CreateBundle("SSMEL_R2_SWITCHES", 8);
		pMPSPower[0][0]->ConnectPort( 1, pBundle, 0);
		pMPSPower[1][0]->ConnectPort( 1, pBundle, 1);
		pMPSHeIsolA[0]->ConnectPort( 0, pBundle, 2);// CL
		pMPSHeIsolA[0]->ConnectPort( 2, pBundle, 3);// OP
		pMPSHeIsolB[0]->ConnectPort( 0, pBundle, 4);// CL
		pMPSHeIsolB[0]->ConnectPort( 2, pBundle, 5);// OP
		pHeInterconnect[0]->ConnectPort( 0, pBundle, 6);// OUT OPEN
		pHeInterconnect[0]->ConnectPort( 2, pBundle, 7);// IN OPEN

		pBundle=STS()->BundleManager()->CreateBundle("SSMER_R2_SWITCHES", 8);
		pMPSPower[0][2]->ConnectPort( 1, pBundle, 0);
		pMPSPower[1][2]->ConnectPort( 1, pBundle, 1);
		pMPSHeIsolA[2]->ConnectPort( 0, pBundle, 2);// CL
		pMPSHeIsolA[2]->ConnectPort( 2, pBundle, 3);// OP
		pMPSHeIsolB[2]->ConnectPort( 0, pBundle, 4);// CL
		pMPSHeIsolB[2]->ConnectPort( 2, pBundle, 5);// OP
		pHeInterconnect[2]->ConnectPort( 0, pBundle, 6);// OUT OPEN
		pHeInterconnect[2]->ConnectPort( 2, pBundle, 7);// IN OPEN

		pBundle=STS()->BundleManager()->CreateBundle( "PNEU_R2_SWITCHES", 4 );
		pPneuLEngHeXOVR->ConnectPort( 0, pBundle, 0 );// CLOSE
		pPneuLEngHeXOVR->ConnectPort( 2, pBundle, 1 );// OPEN
		pPneuHeIsol->ConnectPort( 0, pBundle, 2 );// CLOSE
		pPneuHeIsol->ConnectPort( 2, pBundle, 3 );// OPEN

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF1_IOM9_CH2", 16 );
		pMPSPRPLTDumpSequence->ConnectPort( 2, 0, pBundle, 8 );// START A
		pMPSPRPLTDumpSequence->ConnectPort( 0, 0, pBundle, 9 );// STOP A

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF2_IOM9_CH2", 16 );
		pMPSPRPLTDumpSequence->ConnectPort( 2, 1, pBundle, 8 );// START B
		pMPSPRPLTDumpSequence->ConnectPort( 0, 1, pBundle, 9 );// STOP B

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF3_IOM9_CH2", 16 );
		pMPSPRPLTBackupLH2vlv->ConnectPort( 2, 0, pBundle, 8 );// OPEN A
		pMPSPRPLTBackupLH2vlv->ConnectPort( 0, 0, pBundle, 9 );// CLOSE A

		pBundle = STS()->BundleManager()->CreateBundle( "MDM_FF4_IOM9_CH2", 16 );
		pMPSPRPLTBackupLH2vlv->ConnectPort( 2, 1, pBundle, 8 );// OPEN B
		pMPSPRPLTBackupLH2vlv->ConnectPort( 0, 1, pBundle, 9 );// CLOSE B

		pBundle = STS()->BundleManager()->CreateBundle( "MPSDUMP_LH2UP_R2_SWITCHES", 5 );
		pLH2UllagePress->ConnectPort( 1, pBundle, 4 );// AUTO

		AtlantisPanel::Realize();
	}
}
