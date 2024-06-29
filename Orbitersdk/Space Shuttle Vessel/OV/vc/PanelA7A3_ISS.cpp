#include "PanelA7A3_ISS.h"
#include "CircuitBreaker.h"
#include "StandardSwitch.h"
#include "Talkback.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "vc_defs.h"
#include "../meshres_vc_a7a3_iss.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\PanelA7A3_ISS";
	constexpr VECTOR3 OFFSET_PANEL = {0.263602, 2.223683, 12.487856};


	PanelA7A3_ISS::PanelA7A3_ISS( Atlantis* _sts ) : AtlantisPanel( _sts, "A6L" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		Add( pESS_1BC_SYS_PWR_CNTL_SYS_1 = new CircuitBreaker( _sts, "ESS 1BC SYS PWR CNTL SYS 1" ) );
		Add( pESS_1BC_DEPRESS_SYS_1_VENT_ISOL = new CircuitBreaker( _sts, "ESS 1BC DEPRESS SYS 1 VENT ISOL" ) );
		Add( pMAIN_A_DEPRESS_SYS_1_VENT = new CircuitBreaker( _sts, "MAIN A DEPRESS SYS 1 VENT" ) );
		Add( pMAIN_A_DOCK_LIGHT_TRUSS_FWD = new CircuitBreaker( _sts, "MAIN A DOCK LIGHT TRUSS FWD" ) );
		Add( pMAIN_A_DOCK_LIGHT_VEST_PORT = new CircuitBreaker( _sts, "MAIN A DOCK LIGHT VEST PORT" ) );

		Add( pESS_2CA_SYS_PWR_CNTL_SYS_2 = new CircuitBreaker( _sts, "ESS 2CA SYS PWR CNTL SYS 2" ) );
		Add( pESS_2CA_DEPRESS_SYS_2_VENT_ISOL = new CircuitBreaker( _sts, "ESS 2CA DEPRESS SYS 2 VENT ISOL" ) );
		Add( pMAIN_B_DEPRESS_SYS_2_VENT = new CircuitBreaker( _sts, "MAIN B DEPRESS SYS 2 VENT" ) );
		Add( pMAIN_B_DOCK_LIGHT_TRUSS_AFT = new CircuitBreaker( _sts, "MAIN B DOCK LIGHT TRUSS AFT" ) );
		Add( pMAIN_B_DOCK_LIGHT_VEST_STBD = new CircuitBreaker( _sts, "MAIN B DOCK LIGHT VEST STBD" ) );

		Add( pMAIN_A_LOGIC_3 = new CircuitBreaker( _sts, "MAIN A LOGIC 3" ) );
		Add( pMAIN_A_LOGIC_1 = new CircuitBreaker( _sts, "MAIN A LOGIC 1" ) );
		Add( pMAIN_B_LOGIC_1 = new CircuitBreaker( _sts, "MAIN B LOGIC 1" ) );
		Add( pMAIN_B_LOGIC_2 = new CircuitBreaker( _sts, "MAIN B LOGIC 2" ) );
		Add( pMAIN_C_LOGIC_2 = new CircuitBreaker( _sts, "MAIN C LOGIC 2" ) );
		Add( pMAIN_C_LOGIC_3 = new CircuitBreaker( _sts, "MAIN C LOGIC 3" ) );

		Add( pPMA_2_3_GRP_1_HOOKS_SYS_A_OPEN = new CircuitBreaker( _sts, "PMA 2/3 GRP 1 HOOKS SYS A OPEN" ) );
		Add( pPMA_2_3_GRP_1_HOOKS_SYS_A_CLOSE = new CircuitBreaker( _sts, "PMA 2/3 GRP 1 HOOKS SYS A CLOSE" ) );
		Add( pPMA_2_3_GRP_1_HOOKS_SYS_B_OPEN = new CircuitBreaker( _sts, "PMA 2/3 GRP 1 HOOKS SYS B OPEN" ) );
		Add( pPMA_2_3_GRP_1_HOOKS_SYS_B_CLOSE = new CircuitBreaker( _sts, "PMA 2/3 GRP 1 HOOKS SYS B CLOSE" ) );

		Add( pPMA_2_3_GRP_2_HOOKS_SYS_A_OPEN = new CircuitBreaker( _sts, "PMA 2/3 GRP 2 HOOKS SYS A OPEN" ) );
		Add( pPMA_2_3_GRP_2_HOOKS_SYS_A_CLOSE = new CircuitBreaker( _sts, "PMA 2/3 GRP 2 HOOKS SYS A CLOSE" ) );
		Add( pPMA_2_3_GRP_2_HOOKS_SYS_B_OPEN = new CircuitBreaker( _sts, "PMA 2/3 GRP 2 HOOKS SYS B OPEN" ) );
		Add( pPMA_2_3_GRP_2_HOOKS_SYS_B_CLOSE = new CircuitBreaker( _sts, "PMA 2/3 GRP 2 HOOKS SYS B CLOSE" ) );


		Add( pSYSTEM_POWER_SYS_1 = new StandardTalkback2( _sts, "Zo EXTEND PRIMARY EXTEND" ) );
		Add( pSYSTEM_POWER_SYS_2 = new StandardTalkback2( _sts, "Zo EXTEND SECONDARY EXTEND" ) );

		Add( pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL_TB = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER PRI PED SYS A" ) );
		Add( pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_TB = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER PRI PED SYS B" ) );
		Add( pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL_TB = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER SEC PED SYS A" ) );
		Add( pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_TB = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER SEC PED SYS B" ) );

		Add( pPMA_2_3_HOOKS_GROUP_1 = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER SEC PED SYS A" ) );
		Add( pPMA_2_3_HOOKS_GROUP_2 = new StandardTalkback3( _sts, "PEDESTAL DRIVE XFER SEC PED SYS B" ) );


		Add( pSYSTEM_POWER_MN_A = new StdSwitch3( _sts, "SYSTEM POWER MN A" ) );
		pSYSTEM_POWER_MN_A->SetLabel( 0, "OFF" );
		pSYSTEM_POWER_MN_A->SetLabel( 2, "ON" );
		Add( pSYSTEM_POWER_MN_B = new StdSwitch3( _sts, "SYSTEM POWER MN B" ) );
		pSYSTEM_POWER_MN_B->SetLabel( 0, "OFF" );
		pSYSTEM_POWER_MN_B->SetLabel( 2, "ON" );


		Add( pPYRO_POWER_MN_A = new StdSwitch2( _sts, "PYRO POWER MN A" ) );
		pPYRO_POWER_MN_A->SetLabel( 0, "OFF" );
		pPYRO_POWER_MN_A->SetLabel( 1, "ON" );
		Add( pPYRO_POWER_MN_B = new StdSwitch2( _sts, "PYRO POWER MN B" ) );
		pPYRO_POWER_MN_B->SetLabel( 0, "OFF" );
		pPYRO_POWER_MN_B->SetLabel( 1, "ON" );


		Add( pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL = new StdSwitch3( _sts, "VESTIBULE DEPRESS VALVE SYS 1 VENT ISOL" ) );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetLabel( 0, "CLOSE" );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetLabel( 2, "OPEN" );
		Add( pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT = new StdSwitch3( _sts, "VESTIBULE DEPRESS VALVE SYS 1 VENT" ) );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetLabel( 0, "CLOSE" );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetLabel( 2, "OPEN" );
		Add( pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL = new StdSwitch3( _sts, "VESTIBULE DEPRESS VALVE SYS 2 VENT ISOL" ) );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetLabel( 0, "CLOSE" );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetLabel( 2, "OPEN" );
		Add( pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT = new StdSwitch3( _sts, "VESTIBULE DEPRESS VALVE SYS 2 VENT" ) );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetLabel( 0, "CLOSE" );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetLabel( 2, "OPEN" );


		Add( pPSU_POWER_MN_A = new StdSwitch2( _sts, "PSU POWER MN A" ) );
		pPSU_POWER_MN_A->SetLabel( 0, "OFF" );
		pPSU_POWER_MN_A->SetLabel( 1, "ON" );
		Add( pPSU_POWER_MN_B = new StdSwitch2( _sts, "PSU POWER MN B" ) );
		pPSU_POWER_MN_B->SetLabel( 0, "OFF" );
		pPSU_POWER_MN_B->SetLabel( 1, "ON" );


		Add( pLIGHTS_TRUSS_FWD = new StdSwitch2( _sts, "LIGHTS TRUSS FWD" ) );
		pLIGHTS_TRUSS_FWD->SetLabel( 0, "OFF" );
		pLIGHTS_TRUSS_FWD->SetLabel( 1, "ON" );
		Add( pLIGHTS_TRUSS_AFT = new StdSwitch2( _sts, "LIGHTS TRUSS AFT" ) );
		pLIGHTS_TRUSS_AFT->SetLabel( 0, "OFF" );
		pLIGHTS_TRUSS_AFT->SetLabel( 1, "ON" );
		Add( pLIGHTS_VESTIBULE_PORT = new StdSwitch2( _sts, "LIGHTS VESTIBULE PORT" ) );
		pLIGHTS_VESTIBULE_PORT->SetLabel( 0, "OFF" );
		pLIGHTS_VESTIBULE_PORT->SetLabel( 1, "ON" );
		Add( pLIGHTS_VESTIBULE_STBD = new StdSwitch2( _sts, "LIGHTS VESTIBULE STBD" ) );
		pLIGHTS_VESTIBULE_STBD->SetLabel( 0, "OFF" );
		pLIGHTS_VESTIBULE_STBD->SetLabel( 1, "ON" );


		Add( pPMA_2_3_HOOKS_SYS_A = new StdSwitch3( _sts, "PMA 2/3 HOOKS SYS A" ) );
		pPMA_2_3_HOOKS_SYS_A->SetLabel( 0, "CLOSE" );
		pPMA_2_3_HOOKS_SYS_A->SetLabel( 1, "OFF" );
		pPMA_2_3_HOOKS_SYS_A->SetLabel( 2, "OPEN" );
		Add( pPMA_2_3_HOOKS_SYS_B = new StdSwitch3( _sts, "PMA 2/3 HOOKS SYS B" ) );
		pPMA_2_3_HOOKS_SYS_B->SetLabel( 0, "CLOSE" );
		pPMA_2_3_HOOKS_SYS_B->SetLabel( 1, "OFF" );
		pPMA_2_3_HOOKS_SYS_B->SetLabel( 2, "OPEN" );
		return;
	}

	PanelA7A3_ISS::~PanelA7A3_ISS( void )
	{
		return;
	}

	void PanelA7A3_ISS::DefineVC( void )
	{
		const VECTOR3 switch_rot =  _V( -1.0, 0.0, 0.0 );
		const VECTOR3 pull_dir = _V( 0.0, 0.3126, 0.9499 );

		AddAIDToMouseEventList( AID_A7A3_ISS );

		pESS_1BC_SYS_PWR_CNTL_SYS_1->SetInitialAnimState( 1.0f );
		pESS_1BC_SYS_PWR_CNTL_SYS_1->DefineGroup( GRP_CB1_A7A3_ISS_VC );
		pESS_1BC_SYS_PWR_CNTL_SYS_1->SetDirection( pull_dir );
		pESS_1BC_SYS_PWR_CNTL_SYS_1->SetMouseRegion( AID_A7A3_ISS, 0.074539f, 0.172111f, 0.111908f, 0.243852f );

		pESS_1BC_DEPRESS_SYS_1_VENT_ISOL->SetInitialAnimState( 1.0f );
		pESS_1BC_DEPRESS_SYS_1_VENT_ISOL->DefineGroup( GRP_CB2_A7A3_ISS_VC );
		pESS_1BC_DEPRESS_SYS_1_VENT_ISOL->SetDirection( pull_dir );
		pESS_1BC_DEPRESS_SYS_1_VENT_ISOL->SetMouseRegion( AID_A7A3_ISS, 0.124718f, 0.172111f, 0.178118f, 0.243852f );

		pMAIN_A_DEPRESS_SYS_1_VENT->SetInitialAnimState( 1.0f );
		pMAIN_A_DEPRESS_SYS_1_VENT->DefineGroup( GRP_CB3_A7A3_ISS_VC );
		pMAIN_A_DEPRESS_SYS_1_VENT->SetDirection( pull_dir );
		pMAIN_A_DEPRESS_SYS_1_VENT->SetMouseRegion( AID_A7A3_ISS, 0.191597f, 0.172111f, 0.227216f, 0.243852f );

		pMAIN_A_DOCK_LIGHT_TRUSS_FWD->SetInitialAnimState( 1.0f );
		pMAIN_A_DOCK_LIGHT_TRUSS_FWD->DefineGroup( GRP_CB4_A7A3_ISS_VC );
		pMAIN_A_DOCK_LIGHT_TRUSS_FWD->SetDirection( pull_dir );
		pMAIN_A_DOCK_LIGHT_TRUSS_FWD->SetMouseRegion( AID_A7A3_ISS, 0.240988f, 0.172111f, 0.293839f, 0.243852f );

		pMAIN_A_DOCK_LIGHT_VEST_PORT->SetInitialAnimState( 1.0f );
		pMAIN_A_DOCK_LIGHT_VEST_PORT->DefineGroup( GRP_CB5_A7A3_ISS_VC );
		pMAIN_A_DOCK_LIGHT_VEST_PORT->SetDirection( pull_dir );
		pMAIN_A_DOCK_LIGHT_VEST_PORT->SetMouseRegion( AID_A7A3_ISS, 0.305934f, 0.172111f, 0.342248f, 0.243852f );


		pESS_2CA_SYS_PWR_CNTL_SYS_2->SetInitialAnimState( 1.0f );
		pESS_2CA_SYS_PWR_CNTL_SYS_2->DefineGroup( GRP_CB6_A7A3_ISS_VC );
		pESS_2CA_SYS_PWR_CNTL_SYS_2->SetDirection( pull_dir );
		pESS_2CA_SYS_PWR_CNTL_SYS_2->SetMouseRegion( AID_A7A3_ISS, 0.074539f, 0.361000f, 0.111908f, 0.433171f );

		pESS_2CA_DEPRESS_SYS_2_VENT_ISOL->SetInitialAnimState( 1.0f );
		pESS_2CA_DEPRESS_SYS_2_VENT_ISOL->DefineGroup( GRP_CB7_A7A3_ISS_VC );
		pESS_2CA_DEPRESS_SYS_2_VENT_ISOL->SetDirection( pull_dir );
		pESS_2CA_DEPRESS_SYS_2_VENT_ISOL->SetMouseRegion( AID_A7A3_ISS, 0.124718f, 0.361000f, 0.178118f, 0.433171f );

		pMAIN_B_DEPRESS_SYS_2_VENT->SetInitialAnimState( 1.0f );
		pMAIN_B_DEPRESS_SYS_2_VENT->DefineGroup( GRP_CB8_A7A3_ISS_VC );
		pMAIN_B_DEPRESS_SYS_2_VENT->SetDirection( pull_dir );
		pMAIN_B_DEPRESS_SYS_2_VENT->SetMouseRegion( AID_A7A3_ISS, 0.191597f, 0.361000f, 0.227216f, 0.433171f );

		pMAIN_B_DOCK_LIGHT_TRUSS_AFT->SetInitialAnimState( 1.0f );
		pMAIN_B_DOCK_LIGHT_TRUSS_AFT->DefineGroup( GRP_CB9_A7A3_ISS_VC );
		pMAIN_B_DOCK_LIGHT_TRUSS_AFT->SetDirection( pull_dir );
		pMAIN_B_DOCK_LIGHT_TRUSS_AFT->SetMouseRegion( AID_A7A3_ISS, 0.240988f, 0.361000f, 0.293839f, 0.433171f );

		pMAIN_B_DOCK_LIGHT_VEST_STBD->SetInitialAnimState( 1.0f );
		pMAIN_B_DOCK_LIGHT_VEST_STBD->DefineGroup( GRP_CB10_A7A3_ISS_VC );
		pMAIN_B_DOCK_LIGHT_VEST_STBD->SetDirection( pull_dir );
		pMAIN_B_DOCK_LIGHT_VEST_STBD->SetMouseRegion( AID_A7A3_ISS, 0.305934f, 0.361000f, 0.342248f, 0.433171f );


		pMAIN_A_LOGIC_3->SetInitialAnimState( 1.0f );
		pMAIN_A_LOGIC_3->DefineGroup( GRP_CB11_A7A3_ISS_VC );
		pMAIN_A_LOGIC_3->SetDirection( pull_dir );
		pMAIN_A_LOGIC_3->SetMouseRegion( AID_A7A3_ISS, 0.076074f, 0.512758f, 0.111628f, 0.584401f );

		pMAIN_A_LOGIC_1->SetInitialAnimState( 1.0f );
		pMAIN_A_LOGIC_1->DefineGroup( GRP_CB12_A7A3_ISS_VC );
		pMAIN_A_LOGIC_1->SetDirection( pull_dir );
		pMAIN_A_LOGIC_1->SetMouseRegion( AID_A7A3_ISS, 0.126012f, 0.512758f, 0.178303f, 0.584401f );

		pMAIN_B_LOGIC_1->SetInitialAnimState( 1.0f );
		pMAIN_B_LOGIC_1->DefineGroup( GRP_CB13_A7A3_ISS_VC );
		pMAIN_B_LOGIC_1->SetDirection( pull_dir );
		pMAIN_B_LOGIC_1->SetMouseRegion( AID_A7A3_ISS, 0.191501f, 0.512758f, 0.228366f, 0.584401f );

		pMAIN_B_LOGIC_2->SetInitialAnimState( 1.0f );
		pMAIN_B_LOGIC_2->DefineGroup( GRP_CB14_A7A3_ISS_VC );
		pMAIN_B_LOGIC_2->SetDirection( pull_dir );
		pMAIN_B_LOGIC_2->SetMouseRegion( AID_A7A3_ISS, 0.242908f, 0.512758f, 0.292007f, 0.584401f );

		pMAIN_C_LOGIC_2->SetInitialAnimState( 1.0f );
		pMAIN_C_LOGIC_2->DefineGroup( GRP_CB15_A7A3_ISS_VC );
		pMAIN_C_LOGIC_2->SetDirection( pull_dir );
		pMAIN_C_LOGIC_2->SetMouseRegion( AID_A7A3_ISS, 0.306032f, 0.512758f, 0.343544f, 0.584401f );

		pMAIN_C_LOGIC_3->SetInitialAnimState( 1.0f );
		pMAIN_C_LOGIC_3->DefineGroup( GRP_CB16_A7A3_ISS_VC );
		pMAIN_C_LOGIC_3->SetDirection( pull_dir );
		pMAIN_C_LOGIC_3->SetMouseRegion( AID_A7A3_ISS, 0.362677f, 0.512758f, 0.402118f, 0.584401f );


		pPMA_2_3_GRP_1_HOOKS_SYS_A_OPEN->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_1_HOOKS_SYS_A_OPEN->DefineGroup( GRP_CB_A_A7A3_ISS_VC );
		pPMA_2_3_GRP_1_HOOKS_SYS_A_OPEN->SetDirection( pull_dir );
		pPMA_2_3_GRP_1_HOOKS_SYS_A_OPEN->SetMouseRegion( AID_A7A3_ISS, 0.076121f, 0.681084f, 0.113621f, 0.749643f );

		pPMA_2_3_GRP_1_HOOKS_SYS_A_CLOSE->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_1_HOOKS_SYS_A_CLOSE->DefineGroup( GRP_CB_B_A7A3_ISS_VC );
		pPMA_2_3_GRP_1_HOOKS_SYS_A_CLOSE->SetDirection( pull_dir );
		pPMA_2_3_GRP_1_HOOKS_SYS_A_CLOSE->SetMouseRegion( AID_A7A3_ISS, 0.126999f, 0.681084f, 0.177457f, 0.749643f );

		pPMA_2_3_GRP_1_HOOKS_SYS_B_OPEN->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_1_HOOKS_SYS_B_OPEN->DefineGroup( GRP_CB_C_A7A3_ISS_VC );
		pPMA_2_3_GRP_1_HOOKS_SYS_B_OPEN->SetDirection( pull_dir );
		pPMA_2_3_GRP_1_HOOKS_SYS_B_OPEN->SetMouseRegion( AID_A7A3_ISS, 0.191648f, 0.681084f, 0.228777f, 0.749643f );

		pPMA_2_3_GRP_1_HOOKS_SYS_B_CLOSE->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_1_HOOKS_SYS_B_CLOSE->DefineGroup( GRP_CB_D_A7A3_ISS_VC );
		pPMA_2_3_GRP_1_HOOKS_SYS_B_CLOSE->SetDirection( pull_dir );
		pPMA_2_3_GRP_1_HOOKS_SYS_B_CLOSE->SetMouseRegion( AID_A7A3_ISS, 0.247434f, 0.681084f, 0.287087f, 0.749643f );


		pPMA_2_3_GRP_2_HOOKS_SYS_A_OPEN->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_2_HOOKS_SYS_A_OPEN->DefineGroup( GRP_CB_E_A7A3_ISS_VC );
		pPMA_2_3_GRP_2_HOOKS_SYS_A_OPEN->SetDirection( pull_dir );
		pPMA_2_3_GRP_2_HOOKS_SYS_A_OPEN->SetMouseRegion( AID_A7A3_ISS, 0.076121f, 0.846996f, 0.113621f, 0.913138f );

		pPMA_2_3_GRP_2_HOOKS_SYS_A_CLOSE->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_2_HOOKS_SYS_A_CLOSE->DefineGroup( GRP_CB_F_A7A3_ISS_VC );
		pPMA_2_3_GRP_2_HOOKS_SYS_A_CLOSE->SetDirection( pull_dir );
		pPMA_2_3_GRP_2_HOOKS_SYS_A_CLOSE->SetMouseRegion( AID_A7A3_ISS, 0.126999f, 0.846996f, 0.177457f, 0.913138f );

		pPMA_2_3_GRP_2_HOOKS_SYS_B_OPEN->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_2_HOOKS_SYS_B_OPEN->DefineGroup( GRP_CB_G_A7A3_ISS_VC );
		pPMA_2_3_GRP_2_HOOKS_SYS_B_OPEN->SetDirection( pull_dir );
		pPMA_2_3_GRP_2_HOOKS_SYS_B_OPEN->SetMouseRegion( AID_A7A3_ISS, 0.191648f, 0.846996f, 0.228777f, 0.913138f );

		pPMA_2_3_GRP_2_HOOKS_SYS_B_CLOSE->SetInitialAnimState( 1.0f );
		pPMA_2_3_GRP_2_HOOKS_SYS_B_CLOSE->DefineGroup( GRP_CB_H_A7A3_ISS_VC );
		pPMA_2_3_GRP_2_HOOKS_SYS_B_CLOSE->SetDirection( pull_dir );
		pPMA_2_3_GRP_2_HOOKS_SYS_B_CLOSE->SetMouseRegion( AID_A7A3_ISS, 0.247434f, 0.846996f, 0.287087f, 0.913138f );

		
		pSYSTEM_POWER_SYS_1->DefineMeshGroups( GetVCMeshIndex(), GRP_DS1_U_A7A3_ISS_VC, GRP_DS1_L_A7A3_ISS_VC );
		pSYSTEM_POWER_SYS_1->SetInactiveSegment( TB_OFF );
		pSYSTEM_POWER_SYS_2->DefineMeshGroups( GetVCMeshIndex(), GRP_DS2_U_A7A3_ISS_VC, GRP_DS2_L_A7A3_ISS_VC );
		pSYSTEM_POWER_SYS_2->SetInactiveSegment( TB_OFF );

		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS_A_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS_B_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS_C_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_TB->DefineMeshGroup( GetVCMeshIndex(), GRP_DS_D_A7A3_ISS_VC );

		pPMA_2_3_HOOKS_GROUP_1->DefineMeshGroup( GetVCMeshIndex(), GRP_DS_E_A7A3_ISS_VC );
		pPMA_2_3_HOOKS_GROUP_2->DefineMeshGroup( GetVCMeshIndex(), GRP_DS_F_A7A3_ISS_VC );


		pSYSTEM_POWER_MN_A->SetInitialAnimState( 0.5 );
		pSYSTEM_POWER_MN_A->DefineGroup( GRP_S1_A7A3_ISS_VC );
		pSYSTEM_POWER_MN_A->SetMouseRegion( AID_A7A3_ISS, 0.436342f, 0.305825f, 0.474539f, 0.375368f );
		pSYSTEM_POWER_MN_A->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );
		pSYSTEM_POWER_MN_A->SetSpringLoaded( true, 0 );
		pSYSTEM_POWER_MN_A->SetSpringLoaded( true, 2 );

		pSYSTEM_POWER_MN_B->SetInitialAnimState( 0.5 );
		pSYSTEM_POWER_MN_B->DefineGroup( GRP_S2_A7A3_ISS_VC );
		pSYSTEM_POWER_MN_B->SetMouseRegion( AID_A7A3_ISS, 0.492299f, 0.305825f, 0.531886f, 0.375368f );
		pSYSTEM_POWER_MN_B->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );
		pSYSTEM_POWER_MN_B->SetSpringLoaded( true, 0 );
		pSYSTEM_POWER_MN_B->SetSpringLoaded( true, 2 );


		pPYRO_POWER_MN_A->SetInitialAnimState( 0.5 );
		pPYRO_POWER_MN_A->DefineGroup( GRP_S_A_A7A3_ISS_VC );
		pPYRO_POWER_MN_A->SetMouseRegion( AID_A7A3_ISS, 0.567988f, 0.305825f, 0.606737f, 0.375368f );
		pPYRO_POWER_MN_A->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );

		pPYRO_POWER_MN_B->SetInitialAnimState( 0.5 );
		pPYRO_POWER_MN_B->DefineGroup( GRP_S_B_A7A3_ISS_VC );
		pPYRO_POWER_MN_B->SetMouseRegion( AID_A7A3_ISS, 0.641234f, 0.305825f, 0.678256f, 0.375368f );
		pPYRO_POWER_MN_B->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );


		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetInitialAnimState( 0.5 );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->DefineGroup( GRP_S5_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetMouseRegion( AID_A7A3_ISS, 0.710351f, 0.305825f, 0.748641f, 0.375368f );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetSpringLoaded( true, 0 );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT_ISOL->SetSpringLoaded( true, 2 );

		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetInitialAnimState( 0.5 );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->DefineGroup( GRP_S6_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetMouseRegion( AID_A7A3_ISS, 0.770587f, 0.305825f, 0.808803f, 0.375368f );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetSpringLoaded( true, 0 );
		pVESTIBULE_DEPRESS_VALVE_SYS_1_VENT->SetSpringLoaded( true, 2 );

		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetInitialAnimState( 0.5 );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->DefineGroup( GRP_S7_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetMouseRegion( AID_A7A3_ISS, 0.827618f, 0.305825f, 0.864364f, 0.375368f );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetSpringLoaded( true, 0 );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT_ISOL->SetSpringLoaded( true, 2 );

		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetInitialAnimState( 0.5 );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->DefineGroup( GRP_S8_A7A3_ISS_VC );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetMouseRegion( AID_A7A3_ISS, 0.884092f, 0.305825f, 0.921721f, 0.375368f );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetReference( _V( 0.0, 0.187235, -0.059609 ), switch_rot );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetSpringLoaded( true, 0 );
		pVESTIBULE_DEPRESS_VALVE_SYS_2_VENT->SetSpringLoaded( true, 2 );


		pPSU_POWER_MN_A->SetInitialAnimState( 0.5 );
		pPSU_POWER_MN_A->DefineGroup( GRP_S_C_A7A3_ISS_VC );
		pPSU_POWER_MN_A->SetMouseRegion( AID_A7A3_ISS, 0.671940f, 0.510852f, 0.710054f, 0.580149f );
		pPSU_POWER_MN_A->SetReference( _V( 0.0, 0.129417, -0.04105 ), switch_rot );

		pPSU_POWER_MN_B->SetInitialAnimState( 0.5 );
		pPSU_POWER_MN_B->DefineGroup( GRP_S_D_A7A3_ISS_VC );
		pPSU_POWER_MN_B->SetMouseRegion( AID_A7A3_ISS, 0.743869f, 0.510852f, 0.782465f, 0.580149f );
		pPSU_POWER_MN_B->SetReference( _V( 0.0, 0.129417, -0.04105 ), switch_rot );


		pLIGHTS_TRUSS_FWD->SetInitialAnimState( 0.5 );
		pLIGHTS_TRUSS_FWD->DefineGroup( GRP_S13_A7A3_ISS_VC );
		pLIGHTS_TRUSS_FWD->SetMouseRegion( AID_A7A3_ISS, 0.828757f, 0.510852f, 0.867478f, 0.580149f );
		pLIGHTS_TRUSS_FWD->SetReference( _V( 0.0, 0.129417, -0.04105 ), switch_rot );

		pLIGHTS_TRUSS_AFT->SetInitialAnimState( 0.5 );
		pLIGHTS_TRUSS_AFT->DefineGroup( GRP_S14_A7A3_ISS_VC );
		pLIGHTS_TRUSS_AFT->SetMouseRegion( AID_A7A3_ISS, 0.884786f, 0.510852f, 0.923958f, 0.580149f );
		pLIGHTS_TRUSS_AFT->SetReference( _V( 0.0, 0.129417, -0.04105 ), switch_rot );

		pLIGHTS_VESTIBULE_PORT->SetInitialAnimState( 0.5 );
		pLIGHTS_VESTIBULE_PORT->DefineGroup( GRP_S17_A7A3_ISS_VC );
		pLIGHTS_VESTIBULE_PORT->SetMouseRegion( AID_A7A3_ISS, 0.828188f, 0.718059f, 0.866548f, 0.785176f );
		pLIGHTS_VESTIBULE_PORT->SetReference( _V( 0.0, 0.070632, -0.02218 ), switch_rot );

		pLIGHTS_VESTIBULE_STBD->SetInitialAnimState( 0.5 );
		pLIGHTS_VESTIBULE_STBD->DefineGroup( GRP_S18_A7A3_ISS_VC );
		pLIGHTS_VESTIBULE_STBD->SetMouseRegion( AID_A7A3_ISS, 0.884061f, 0.718059f, 0.922615f, 0.785176f );
		pLIGHTS_VESTIBULE_STBD->SetReference( _V( 0.0, 0.070632, -0.02218 ), switch_rot );


		pPMA_2_3_HOOKS_SYS_A->SetInitialAnimState( 0.5 );
		pPMA_2_3_HOOKS_SYS_A->DefineGroup( GRP_S_E_A7A3_ISS_VC );
		pPMA_2_3_HOOKS_SYS_A->SetMouseRegion( AID_A7A3_ISS, 0.458634f, 0.715647f, 0.497254f, 0.785284f );
		pPMA_2_3_HOOKS_SYS_A->SetReference( _V( 0.0, 0.071559, -0.022478 ), switch_rot );

		pPMA_2_3_HOOKS_SYS_B->SetInitialAnimState( 0.5 );
		pPMA_2_3_HOOKS_SYS_B->DefineGroup( GRP_S_F_A7A3_ISS_VC );
		pPMA_2_3_HOOKS_SYS_B->SetMouseRegion( AID_A7A3_ISS, 0.530351f, 0.715647f, 0.568390f, 0.785284f );
		pPMA_2_3_HOOKS_SYS_B->SetReference( _V( 0.0, 0.071559, -0.022478 ), switch_rot );
		return;
	}

	void PanelA7A3_ISS::RegisterVC( void )
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_A7A3_ISS, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_A7A3_ISS,
			_V( 0.52714, 0.282907, -0.088956 ) + ofs, _V( 0.0, 0.282907, -0.088956 ) + ofs,
			_V( 0.52714, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.0 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelA7A3_ISS::Realize( void )
	{
		AtlantisPanel::Realize();

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "A7A3_ISS_internal_1", 16 );
		pMAIN_A_LOGIC_3->Connect( pBundle, 0 );
		pMAIN_A_LOGIC_1->Connect( pBundle, 1 );
		pMAIN_B_LOGIC_1->Connect( pBundle, 2 );
		pMAIN_B_LOGIC_2->Connect( pBundle, 3 );
		pMAIN_C_LOGIC_2->Connect( pBundle, 4 );
		pMAIN_C_LOGIC_3->Connect( pBundle, 5 );
		pPSU_POWER_MN_A->ConnectPort( 1, pBundle, 6 );
		pPSU_POWER_MN_B->ConnectPort( 1, pBundle, 7 );
		pMAIN_A_DOCK_LIGHT_TRUSS_FWD->Connect( pBundle, 8 );
		pMAIN_B_DOCK_LIGHT_TRUSS_AFT->Connect( pBundle, 9 );
		pMAIN_A_DOCK_LIGHT_VEST_PORT->Connect( pBundle, 10 );
		pMAIN_B_DOCK_LIGHT_VEST_STBD->Connect( pBundle, 11 );
		pLIGHTS_TRUSS_FWD->ConnectPort( 1, pBundle, 12 );
		pLIGHTS_TRUSS_AFT->ConnectPort( 1, pBundle, 13 );
		pLIGHTS_VESTIBULE_PORT->ConnectPort( 1, pBundle, 14 );
		pLIGHTS_VESTIBULE_STBD->ConnectPort( 1, pBundle, 15 );

		dipMAIN_A_LOGIC_3.Connect( pBundle, 0 );
		dipMAIN_A_LOGIC_1.Connect( pBundle, 1 );
		dipMAIN_B_LOGIC_1.Connect( pBundle, 2 );
		dipMAIN_B_LOGIC_2.Connect( pBundle, 3 );
		dipMAIN_C_LOGIC_2.Connect( pBundle, 4 );
		dipMAIN_C_LOGIC_3.Connect( pBundle, 5 );
		dipPSU_POWER_MN_A.Connect( pBundle, 6 );
		dipPSU_POWER_MN_B.Connect( pBundle, 7 );
		dipMAIN_A_DOCK_LIGHT_TRUSS_FWD.Connect( pBundle, 8 );
		dipMAIN_B_DOCK_LIGHT_TRUSS_AFT.Connect( pBundle, 9 );
		dipMAIN_A_DOCK_LIGHT_VEST_PORT.Connect( pBundle, 10 );
		dipMAIN_B_DOCK_LIGHT_VEST_STBD.Connect( pBundle, 11 );
		dipLIGHTS_TRUSS_FWD.Connect( pBundle, 12 );
		dipLIGHTS_TRUSS_AFT.Connect( pBundle, 13 );
		dipLIGHTS_VESTIBULE_PORT.Connect( pBundle, 14 );
		dipLIGHTS_VESTIBULE_STBD.Connect( pBundle, 15 );

		pBundle = STS()->BundleManager()->CreateBundle( "A7A3_ISS_internal_2", 16 );
		pSYSTEM_POWER_MN_A->ConnectPort( 2, pBundle, 0 );
		pSYSTEM_POWER_MN_A->ConnectPort( 0, pBundle, 1 );
		pSYSTEM_POWER_MN_B->ConnectPort( 2, pBundle, 2 );
		pSYSTEM_POWER_MN_B->ConnectPort( 0, pBundle, 3 );
		pESS_1BC_SYS_PWR_CNTL_SYS_1->Connect( pBundle, 4 );
		pESS_2CA_SYS_PWR_CNTL_SYS_2->Connect( pBundle, 5 );

		dipSYSTEM_POWER_MN_A_ON.Connect( pBundle, 0 );
		dipSYSTEM_POWER_MN_A_OFF.Connect( pBundle, 1 );
		dipSYSTEM_POWER_MN_B_ON.Connect( pBundle, 2 );
		dipSYSTEM_POWER_MN_B_OFF.Connect( pBundle, 3 );
		dipESS_1BC_SYS_PWR_CNTL_SYS_1.Connect( pBundle, 4 );
		dipESS_2CA_SYS_PWR_CNTL_SYS_2.Connect( pBundle, 5 );

		pBundle = STS()->BundleManager()->CreateBundle( "ODS_POWER", 16 );
		dopPNL_LOGIC_A.Connect( pBundle, 0 );
		dopPNL_LOGIC_B.Connect( pBundle, 1 );
		dopPNL_LOGIC_C.Connect( pBundle, 2 );
		dopCW1.Connect( pBundle, 7 );
		dopCW2.Connect( pBundle, 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "MPC_ODS_POWER", 16 );
		dopSYSTEM_POWER_MN_A_ON.Connect( pBundle, 0 );
		dopSYSTEM_POWER_MN_A_OFF.Connect( pBundle, 1 );
		dopSYSTEM_POWER_MN_B_ON.Connect( pBundle, 2 );
		dopSYSTEM_POWER_MN_B_OFF.Connect( pBundle, 3 );
		pSYSTEM_POWER_SYS_1->SetInput( pBundle, 4, TB_ON );
		pMAIN_A_DOCK_LIGHT_TRUSS_FWD->ConnectInput( pBundle, 4 );
		pSYSTEM_POWER_SYS_2->SetInput( pBundle, 5, TB_ON );
		pMAIN_B_DOCK_LIGHT_TRUSS_AFT->ConnectInput( pBundle, 5 );
		pMAIN_A_LOGIC_3->ConnectInput( pBundle, 6 );
		pMAIN_A_LOGIC_1->ConnectInput( pBundle, 7 );
		pMAIN_B_LOGIC_1->ConnectInput( pBundle, 8 );
		pMAIN_B_LOGIC_2->ConnectInput( pBundle, 9 );
		pMAIN_C_LOGIC_2->ConnectInput( pBundle, 10 );
		pMAIN_C_LOGIC_3->ConnectInput( pBundle, 11 );
		pMAIN_A_DOCK_LIGHT_VEST_PORT->ConnectInput( pBundle, 12 );
		pMAIN_B_DOCK_LIGHT_VEST_STBD->ConnectInput( pBundle, 13 );

		pBundle = STS()->BundleManager()->CreateBundle( "ODS_LIGHTS", 16 );
		dopLIGHT_TRUSS_FWD.Connect( pBundle, 0 );
		dopLIGHT_TRUSS_AFT.Connect( pBundle, 1 );
		dopLIGHT_VEST_PORT.Connect( pBundle, 2 );
		dopLIGHT_VEST_STBD.Connect( pBundle, 3 );

		RunSignals();
		return;
	}

	void PanelA7A3_ISS::OnPreStep( double simt, double simdt, double mjd )
	{
		AtlantisPanel::OnPreStep( simt, simdt, mjd );

		RunSignals();
		return;
	}

	void PanelA7A3_ISS::RunSignals( void )
	{
		if (dipMAIN_A_LOGIC_1 || dipMAIN_B_LOGIC_1)
		{
			dopPNL_LOGIC_A.SetLine();
		}
		else
		{
			dopPNL_LOGIC_A.ResetLine();
		}

		if (dipMAIN_B_LOGIC_2 || dipMAIN_C_LOGIC_2)
		{
			dopPNL_LOGIC_B.SetLine();
		}
		else
		{
			dopPNL_LOGIC_B.ResetLine();
		}

		if (dipMAIN_A_LOGIC_3 || dipMAIN_C_LOGIC_3)
		{
			dopPNL_LOGIC_C.SetLine();
		}
		else
		{
			dopPNL_LOGIC_C.ResetLine();
		}


		if (dipPSU_POWER_MN_A)
		{
			dopCW1.SetLine();
		}
		else
		{
			dopCW1.ResetLine();
		}

		if (dipPSU_POWER_MN_B)
		{
			dopCW2.SetLine();
		}
		else
		{
			dopCW2.ResetLine();
		}


		if (dipMAIN_A_DOCK_LIGHT_TRUSS_FWD && dipLIGHTS_TRUSS_FWD)
		{
			dopLIGHT_TRUSS_FWD.SetLine();
		}
		else
		{
			dopLIGHT_TRUSS_FWD.ResetLine();
		}

		if (dipMAIN_B_DOCK_LIGHT_TRUSS_AFT && dipLIGHTS_TRUSS_AFT)
		{
			dopLIGHT_TRUSS_AFT.SetLine();
		}
		else
		{
			dopLIGHT_TRUSS_AFT.ResetLine();
		}

		if (dipMAIN_A_DOCK_LIGHT_VEST_PORT && dipLIGHTS_VESTIBULE_PORT)
		{
			dopLIGHT_VEST_PORT.SetLine();
		}
		else
		{
			dopLIGHT_VEST_PORT.ResetLine();
		}

		if (dipMAIN_B_DOCK_LIGHT_VEST_STBD && dipLIGHTS_VESTIBULE_STBD)
		{
			dopLIGHT_VEST_STBD.SetLine();
		}
		else
		{
			dopLIGHT_VEST_STBD.ResetLine();
		}

		if (dipESS_1BC_SYS_PWR_CNTL_SYS_1 && dipSYSTEM_POWER_MN_A_ON)
		{
			dopSYSTEM_POWER_MN_A_ON.SetLine();
		}
		else
		{
			dopSYSTEM_POWER_MN_A_ON.ResetLine();
		}
		if (dipESS_1BC_SYS_PWR_CNTL_SYS_1 && dipSYSTEM_POWER_MN_A_OFF)
		{
			dopSYSTEM_POWER_MN_A_OFF.SetLine();
		}
		else
		{
			dopSYSTEM_POWER_MN_A_OFF.ResetLine();
		}

		if (dipESS_2CA_SYS_PWR_CNTL_SYS_2 && dipSYSTEM_POWER_MN_B_ON)
		{
			dopSYSTEM_POWER_MN_B_ON.SetLine();
		}
		else
		{
			dopSYSTEM_POWER_MN_B_ON.ResetLine();
		}
		if (dipESS_2CA_SYS_PWR_CNTL_SYS_2 && dipSYSTEM_POWER_MN_B_OFF)
		{
			dopSYSTEM_POWER_MN_B_OFF.SetLine();
		}
		else
		{
			dopSYSTEM_POWER_MN_B_OFF.ResetLine();
		}
		return;
	}
}
