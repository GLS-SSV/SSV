/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/04/21   GLS
2022/04/28   GLS
2022/07/02   GLS
2022/07/17   GLS
2022/07/18   GLS
2022/07/24   GLS
2022/08/05   GLS
2022/09/06   GLS
2022/09/07   GLS
2022/09/10   GLS
2022/09/11   GLS
********************************************/
#include "PanelR13U.h"
#include "StandardSwitch.h"
#include "StandardLight.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "ThumbWheel.h"
#include "PushWheel.h"
#include "vc_defs.h"
#include "..\meshres_vc_r13u.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelR13U";
	constexpr VECTOR3 OFFSET_PANEL = {1.30501, 2.28002, 12.561};


	PanelR13U::PanelR13U( Atlantis* _sts, const std::string &orbiter ):AtlantisPanel( _sts, "R13U" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		if ((orbiter == "Discovery") || (orbiter == "Endeavour")) thumbwheels = false;
		else thumbwheels = true;

		Add( pParamStatus = new StdSwitch3( _sts, "PARAM STATUS" ) );
		pParamStatus->SetLabel( 0, "INHIBITED" );
		pParamStatus->SetLabel( 1, "-" );
		pParamStatus->SetLabel( 2, "TRIPPED" );

		Add( pMemory = new StdSwitch3( _sts, "MEMORY" ) );
		pMemory->SetLabel( 0, "CLEAR" );
		pMemory->SetLabel( 1, "-" );
		pMemory->SetLabel( 2, "READ" );

		Add( pLampTest = new StdSwitch3( _sts, "LAMP TEST" ) );
		pLampTest->SetLabel( 0, "RIGHT" );
		pLampTest->SetLabel( 1, "-" );
		pLampTest->SetLabel( 2, "LEFT" );

		if (thumbwheels)
		{
			Add( pParameterSelect100 = new ThumbWheel( _sts, "PARAMETER SELECT 100" ) );
			Add( pParameterSelect10 = new ThumbWheel( _sts, "PARAMETER SELECT 10" ) );
			Add( pParameterSelect1 = new ThumbWheel( _sts, "PARAMETER SELECT 1" ) );

			Add( pLimitSetValue1 = new ThumbWheel( _sts, "LIMIT SET VALUE 1" ) );
			Add( pLimitSetValue01 = new ThumbWheel( _sts, "LIMIT SET VALUE 01" ) );
			Add( pLimitSetValue005 = new ThumbWheel( _sts, "LIMIT SET VALUE 005" ) );
		}
		else
		{
			Add( pParameterSelect100 = new PushWheel( _sts, "PARAMETER SELECT 100" ) );
			Add( pParameterSelect10 = new PushWheel( _sts, "PARAMETER SELECT 10" ) );
			Add( pParameterSelect1 = new PushWheel( _sts, "PARAMETER SELECT 1" ) );

			Add( pLimitSetValue1 = new PushWheel( _sts, "LIMIT SET VALUE 1" ) );
			Add( pLimitSetValue01 = new PushWheel( _sts, "LIMIT SET VALUE 01" ) );
			Add( pLimitSetValue005 = new PushWheel( _sts, "LIMIT SET VALUE 005" ) );
		}

		Add( pLimit = new StdSwitch2( _sts, "LIMIT" ) );
		pLimit->SetLabel( 0, "LOWER" );
		pLimit->SetLabel( 1, "UPPER" );

		Add( pFunc = new StdSwitch3( _sts, "FUNC" ) );
		pFunc->SetLabel( 0, "READ" );
		pFunc->SetLabel( 1, "-" );
		pFunc->SetLabel( 2, "SET" );

		Add( pParam = new StdSwitch3( _sts, "PARAM" ) );
		pParam->SetLabel( 0, "INHIBIT" );
		pParam->SetLabel( 1, "-" );
		pParam->SetLabel( 2, "ENABLE" );

		std::string tmp;
		for (int i = 0; i < 120; i++)
		{
			tmp = "CW MATRIX " + std::to_string( i );
			Add( pMatrix[i] = new StandardSingleLight( _sts, tmp.c_str() ) );
		}
	}

	PanelR13U::~PanelR13U()
	{
	}

	void PanelR13U::DefineVC()
	{
		const VECTOR3 switch_rot = _V( 0.0, 0.0, -1.0 );

		AddAIDToMouseEventList( AID_R13U );

		pParamStatus->SetInitialAnimState( 0.5f );
		pParamStatus->DefineGroup( GRP_S1_R13U_VC );
		pParamStatus->SetReference( _V( 0.16321, 0.108585, 0.0 ), switch_rot );
		pParamStatus->SetMouseRegion( AID_R13U, 0.615751f, 0.268867f, 0.679900f, 0.342053f );
		pParamStatus->SetSpringLoaded( true, 0 );
		pParamStatus->SetSpringLoaded( true, 2 );

		pMemory->SetInitialAnimState( 0.5f );
		pMemory->DefineGroup( GRP_S2_R13U_VC );
		pMemory->SetReference( _V( 0.16321, 0.108585, 0.0 ), switch_rot );
		pMemory->SetMouseRegion( AID_R13U, 0.704770f, 0.268867f, 0.785285f, 0.342053f );
		pMemory->SetSpringLoaded( true, 0 );
		pMemory->SetSpringLoaded( true, 2 );

		pLampTest->SetInitialAnimState( 0.5f );
		pLampTest->DefineGroup( GRP_S3_R13U_VC );
		pLampTest->SetReference( _V( 0.16321, 0.108585, 0.0 ), switch_rot );
		pLampTest->SetMouseRegion( AID_R13U, 0.807637f, 0.268867f, 0.869638f, 0.342053f );
		pLampTest->SetSpringLoaded( true, 0 );
		pLampTest->SetSpringLoaded( true, 2 );

		pParameterSelect100->DefineOutputs( 0, 0 );
		pParameterSelect100->DefineOutputs( 1, 1 );
		pParameterSelect100->DefineOutputs( 2, 0 );
		pParameterSelect100->DefineOutputs( 3, 1 );
		pParameterSelect100->DefineOutputs( 4, 0 );
		pParameterSelect100->DefineOutputs( 5, 1 );
		pParameterSelect100->DefineOutputs( 6, 0 );
		pParameterSelect100->DefineOutputs( 7, 1 );
		pParameterSelect100->DefineOutputs( 8, 0 );
		pParameterSelect100->DefineOutputs( 9, 1 );
		pLimitSetValue1->SetBounds( 0, 5 );
		pLimitSetValue005->DefineOutputs( 0, 0 );
		pLimitSetValue005->DefineOutputs( 1, 1 );
		pLimitSetValue005->DefineOutputs( 2, 0 );
		pLimitSetValue005->DefineOutputs( 3, 1 );
		pLimitSetValue005->DefineOutputs( 4, 0 );
		pLimitSetValue005->DefineOutputs( 5, 1 );
		pLimitSetValue005->DefineOutputs( 6, 0 );
		pLimitSetValue005->DefineOutputs( 7, 1 );
		pLimitSetValue005->DefineOutputs( 8, 0 );
		pLimitSetValue005->DefineOutputs( 9, 1 );
		if (thumbwheels)
		{
			const VECTOR3 posS4 = _V( 0.118205, 0.050817, 0.0 );
			const VECTOR3 posS6 = _V( 0.056855, 0.010507, 0.0 );

			pParameterSelect100->DefineWheelGroup( GRP_S4_THUMBWHEEL_100_R13U_VC );
			pParameterSelect100->SetReference( posS4, switch_rot );
			pParameterSelect100->SetMouseRegion( AID_R13U, 0.684645f, 0.505418f, 0.701706f, 0.604193f );

			pParameterSelect10->DefineWheelGroup( GRP_S4_THUMBWHEEL_10_R13U_VC );
			pParameterSelect10->SetReference( posS4, switch_rot );
			pParameterSelect10->SetMouseRegion( AID_R13U, 0.745898f, 0.505418f, 0.766596f, 0.604193f );

			pParameterSelect1->DefineWheelGroup( GRP_S4_THUMBWHEEL_1_R13U_VC );
			pParameterSelect1->SetReference( posS4, switch_rot );
			pParameterSelect1->SetMouseRegion( AID_R13U, 0.808695f, 0.505418f, 0.827349f, 0.604193f );


			pLimitSetValue1->DefineWheelGroup( GRP_S6_THUMBWHEEL_1_R13U_VC );
			pLimitSetValue1->SetReference( posS6, switch_rot );
			pLimitSetValue1->SetMouseRegion( AID_R13U, 0.355255f, 0.762237f, 0.373567f, 0.862757f );

			pLimitSetValue01->DefineWheelGroup( GRP_S6_THUMBWHEEL_01_R13U_VC );
			pLimitSetValue01->SetReference( posS6, switch_rot );
			pLimitSetValue01->SetMouseRegion( AID_R13U, 0.416871f, 0.762237f, 0.436303f, 0.862757f );

			pLimitSetValue005->DefineWheelGroup( GRP_S6_THUMBWHEEL_005_R13U_VC );
			pLimitSetValue005->SetReference( posS6, switch_rot );
			pLimitSetValue005->SetMouseRegion( AID_R13U, 0.478510f, 0.762237f, 0.498419f, 0.862757f );
		}
		else
		{
			const VECTOR3 pushbutton_dir = _V( 0.54928, -0.83564, 0.0 );
			const VECTOR3 posS4 = _V( 0.117232, 0.052298, 0.0 );
			const VECTOR3 posS6 = _V( 0.055882, 0.011988, 0.0 );

			pParameterSelect100->DefineWheelGroup( GRP_S4_PUSHWHEEL_100_R13U_VC );
			dynamic_cast<PushWheel*>(pParameterSelect100)->DefinePushButtonGroups( GRP_S4_PUSHWHEEL_PUSHBUTTON_UP_100_R13U_VC, -1 );
			dynamic_cast<PushWheel*>(pParameterSelect100)->DefinePushButtonDirection( pushbutton_dir );
			pParameterSelect100->SetReference( posS4, switch_rot );
			pParameterSelect100->SetMouseRegion( AID_R13U, 0.662234f, 0.482183f, 0.698912f, 0.620214f );

			pParameterSelect10->DefineWheelGroup( GRP_S4_PUSHWHEEL_10_R13U_VC );
			dynamic_cast<PushWheel*>(pParameterSelect10)->DefinePushButtonGroups( GRP_S4_PUSHWHEEL_PUSHBUTTON_UP_10_R13U_VC, GRP_S4_PUSHWHEEL_PUSHBUTTON_DOWN_10_R13U_VC );
			dynamic_cast<PushWheel*>(pParameterSelect10)->DefinePushButtonDirection( pushbutton_dir );
			pParameterSelect10->SetReference( posS4, switch_rot );
			pParameterSelect10->SetMouseRegion( AID_R13U, 0.723592f, 0.482183f, 0.763352f, 0.620214f );

			pParameterSelect1->DefineWheelGroup( GRP_S4_PUSHWHEEL_1_R13U_VC );
			dynamic_cast<PushWheel*>(pParameterSelect1)->DefinePushButtonGroups( GRP_S4_PUSHWHEEL_PUSHBUTTON_UP_1_R13U_VC, GRP_S4_PUSHWHEEL_PUSHBUTTON_DOWN_1_R13U_VC );
			dynamic_cast<PushWheel*>(pParameterSelect1)->DefinePushButtonDirection( pushbutton_dir );
			pParameterSelect1->SetReference( posS4, switch_rot );
			pParameterSelect1->SetMouseRegion( AID_R13U, 0.788281f, 0.482183f, 0.826377f, 0.620214f );


			pLimitSetValue1->DefineWheelGroup( GRP_S6_PUSHWHEEL_1_R13U_VC );
			dynamic_cast<PushWheel*>(pLimitSetValue1)->DefinePushButtonGroups( GRP_S6_PUSHWHEEL_PUSHBUTTON_UP_1_R13U_VC, GRP_S6_PUSHWHEEL_PUSHBUTTON_DOWN_1_R13U_VC );
			dynamic_cast<PushWheel*>(pLimitSetValue1)->DefinePushButtonDirection( pushbutton_dir );
			pLimitSetValue1->SetReference( posS6, switch_rot );
			pLimitSetValue1->SetMouseRegion( AID_R13U, 0.332048f, 0.743655f, 0.369610f, 0.878476f );

			pLimitSetValue01->DefineWheelGroup( GRP_S6_PUSHWHEEL_01_R13U_VC );
			dynamic_cast<PushWheel*>(pLimitSetValue01)->DefinePushButtonGroups( GRP_S6_PUSHWHEEL_PUSHBUTTON_UP_01_R13U_VC, GRP_S6_PUSHWHEEL_PUSHBUTTON_DOWN_01_R13U_VC );
			dynamic_cast<PushWheel*>(pLimitSetValue01)->DefinePushButtonDirection( pushbutton_dir );
			pLimitSetValue01->SetReference( posS6, switch_rot );
			pLimitSetValue01->SetMouseRegion( AID_R13U, 0.394124f, 0.743655f, 0.432249f, 0.878476f );

			pLimitSetValue005->DefineWheelGroup( GRP_S6_PUSHWHEEL_005_R13U_VC );
			dynamic_cast<PushWheel*>(pLimitSetValue005)->DefinePushButtonGroups( GRP_S6_PUSHWHEEL_PUSHBUTTON_UP_005_R13U_VC, -1 );
			dynamic_cast<PushWheel*>(pLimitSetValue005)->DefinePushButtonDirection( pushbutton_dir );
			pLimitSetValue005->SetReference( posS6, switch_rot );
			pLimitSetValue005->SetMouseRegion( AID_R13U, 0.457453f, 0.743655f, 0.494742f, 0.878476f );
		}

		pLimit->SetInitialAnimState( 0.5f );
		pLimit->DefineGroup( GRP_S7_R13U_VC );
		pLimit->SetReference( _V( 0.04286, 0.029915, 0.0 ), switch_rot );
		pLimit->SetMouseRegion( AID_R13U, 0.618767f, 0.780350f, 0.677145f, 0.852451f );

		pFunc->SetInitialAnimState( 0.5f );
		pFunc->DefineGroup( GRP_S8_R13U_VC );
		pFunc->SetReference( _V( 0.04286, 0.029915, 0.0 ), switch_rot );
		pFunc->SetMouseRegion( AID_R13U, 0.704619f, 0.780350f, 0.786034f, 0.852451f );
		pFunc->SetSpringLoaded( true, 0 );
		pFunc->SetSpringLoaded( true, 2 );

		pParam->SetInitialAnimState( 0.5f );
		pParam->DefineGroup( GRP_S9_R13U_VC );
		pParam->SetReference( _V( 0.04286, 0.029915, 0.0 ), switch_rot );
		pParam->SetMouseRegion( AID_R13U, 0.807603f, 0.780350f, 0.869640f, 0.852451f );
		pParam->SetSpringLoaded( true, 0 );
		pParam->SetSpringLoaded( true, 2 );

		for (int i = 0; i < 120; i++)
		{
			pMatrix[i]->DefineMeshGroup( GetVCMeshIndex(), GRP_XDS1_0_R13U_VC + i );
			pMatrix[i]->SetStateOffset( 1, 0.0f, 0.0683594f );// 70px
		}
		return;
	}

	void PanelR13U::RegisterVC()
	{
		AtlantisPanel::RegisterVC();

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET + OFFSET_PANEL;

		oapiVCRegisterArea( AID_R13U, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R13U,
			_V( 0.23624, 0.15522, 0.0 ) + ofs, _V( 0.23624, 0.15522, -0.3046 ) + ofs,
			_V( 0.0, 0.0, 0.0 ) + ofs, _V( 0.0, 0.0, 0.3046 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
		return;
	}

	void PanelR13U::Realize()
	{
		AtlantisPanel::Realize();

		DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "CW_SW_1", 16 );
		pParamStatus->ConnectPort( 0, pBundle, 0 );// INHIBITED
		pParamStatus->ConnectPort( 1, pBundle, 1 );// -
		pParamStatus->ConnectPort( 2, pBundle, 2 );// TRIPPED

		pMemory->ConnectPort( 0, pBundle, 3 );// CLEAR
		pMemory->ConnectPort( 1, pBundle, 4 );// -
		pMemory->ConnectPort( 2, pBundle, 5 );// READ

		pLampTest->ConnectPort( 0, pBundle, 6 );// RIGHT
		pLampTest->ConnectPort( 1, pBundle, 7 );// -
		pLampTest->ConnectPort( 2, pBundle, 8 );// LEFT

		pLimit->ConnectPort( 0, pBundle, 9 );// LOWER
		pLimit->ConnectPort( 1, pBundle, 10 );// UPPER

		pFunc->ConnectPort( 0, pBundle, 11 );// READ
		pFunc->ConnectPort( 1, pBundle, 12 );// -
		pFunc->ConnectPort( 2, pBundle, 13 );// SET

		pBundle = STS()->BundleManager()->CreateBundle( "CW_SW_2", 16 );
		pParam->ConnectPort( 0, pBundle, 0 );// INHIBIT
		pParam->ConnectPort( 1, pBundle, 1 );// -
		pParam->ConnectPort( 2, pBundle, 2 );// ENABLE

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_A", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_B", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i + 16]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_C", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i + 32]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_D", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i + 48]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_E", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i + 64]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_F", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i + 80]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_G", 16 );
		for (int i = 0; i < 16; i++) pMatrix[i + 96]->ConnectLight( 0, pBundle, i );

		pBundle = STS()->BundleManager()->CreateBundle( "CW_STATUS_MATRIX_H", 16 );
		for (int i = 0; i < 8; i++) pMatrix[i + 112]->ConnectLight( 0, pBundle, i );
		
		pBundle = STS()->BundleManager()->CreateBundle( "R13_PARAMETER_SELECT", 16 );
		pParameterSelect1->Connect( pBundle, 0, 0 );
		pParameterSelect1->Connect( pBundle, 1, 1 );
		pParameterSelect1->Connect( pBundle, 2, 2 );
		pParameterSelect1->Connect( pBundle, 3, 3 );
		pParameterSelect10->Connect( pBundle, 4, 0 );
		pParameterSelect10->Connect( pBundle, 5, 1 );
		pParameterSelect10->Connect( pBundle, 6, 2 );
		pParameterSelect10->Connect( pBundle, 7, 3 );
		pParameterSelect100->Connect( pBundle, 8, 0 );
		
		pBundle = STS()->BundleManager()->CreateBundle( "R13_LIMIT_SET_VALUE", 16 );
		pLimitSetValue005->Connect( pBundle, 0, 0 );
		pLimitSetValue01->Connect( pBundle, 1, 0 );
		pLimitSetValue01->Connect( pBundle, 2, 1 );
		pLimitSetValue01->Connect( pBundle, 3, 2 );
		pLimitSetValue01->Connect( pBundle, 4, 3 );
		pLimitSetValue1->Connect( pBundle, 5, 0 );
		pLimitSetValue1->Connect( pBundle, 6, 1 );
		pLimitSetValue1->Connect( pBundle, 7, 2 );
		pLimitSetValue1->Connect( pBundle, 8, 3 );
		return;
	}

	void PanelR13U::VisualCreated( void )
	{
		// hide thumbwheels or pushwheels
		DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), GetVCMeshIndex() );
		if (hDevMesh != NULL)
		{
			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 0x00000003;// hide group and shadow
			if (thumbwheels)
			{
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_10_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_100_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_CASE_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_PUSHBUTTON_DOWN_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_PUSHBUTTON_DOWN_10_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_PUSHBUTTON_UP_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_PUSHBUTTON_UP_10_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_PUSHWHEEL_PUSHBUTTON_UP_100_R13U_VC, &grpSpec );

				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_005_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_01_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_CASE_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_PUSHBUTTON_DOWN_01_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_PUSHBUTTON_DOWN_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_PUSHBUTTON_UP_005_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_PUSHBUTTON_UP_01_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_PUSHWHEEL_PUSHBUTTON_UP_1_R13U_VC, &grpSpec );
			}
			else
			{
				oapiEditMeshGroup( hDevMesh, GRP_S4_THUMBWHEEL_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_THUMBWHEEL_10_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_THUMBWHEEL_100_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S4_THUMBWHEEL_CASE_R13U_VC, &grpSpec );

				oapiEditMeshGroup( hDevMesh, GRP_S6_THUMBWHEEL_005_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_THUMBWHEEL_01_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_THUMBWHEEL_1_R13U_VC, &grpSpec );
				oapiEditMeshGroup( hDevMesh, GRP_S6_THUMBWHEEL_CASE_R13U_VC, &grpSpec );
			}
		}

		AtlantisPanel::VisualCreated();
		return;
	}
};
