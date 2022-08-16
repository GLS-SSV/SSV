/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/04/21   GLS
2022/07/02   GLS
2022/07/17   GLS
2022/07/18   GLS
2022/07/24   GLS
2022/08/05   GLS
********************************************/
#include "PanelR13U.h"
#include "StandardSwitch.h"
#include "StandardLight.h"
#include "..\Atlantis.h"
#include "..\ParameterValues.h"
#include "vc_defs.h"
#include "..\meshres_vc_r13u.h"


namespace vc
{
	PanelR13U::PanelR13U( Atlantis* _sts ):AtlantisPanel( _sts, "R13U" )
	{
		DefineMesh( MESHNAME_PANELR13U );

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
		const VECTOR3 SWITCH_ROT = _V( 0.0, 0.0, -1.0 );

		AddAIDToMouseEventList( AID_R13U );
		
		pParamStatus->SetInitialAnimState( 0.5f );
		pParamStatus->DefineGroup( GRP_S1_R13U_VC );
		pParamStatus->SetReference( _V( 1.46822, 2.38861, 12.3598 ), SWITCH_ROT );
		pParamStatus->SetMouseRegion( AID_R13U, 0.615751f, 0.268867f, 0.679900f, 0.342053f );
		pParamStatus->SetSpringLoaded( true, 0 );
		pParamStatus->SetSpringLoaded( true, 2 );

		pMemory->SetInitialAnimState( 0.5f );
		pMemory->DefineGroup( GRP_S2_R13U_VC );
		pMemory->SetReference( _V( 1.46822, 2.38861, 12.3598 ), SWITCH_ROT );
		pMemory->SetMouseRegion( AID_R13U, 0.704770f, 0.268867f, 0.785285f, 0.342053f );
		pMemory->SetSpringLoaded( true, 0 );
		pMemory->SetSpringLoaded( true, 2 );

		pLampTest->SetInitialAnimState( 0.5f );
		pLampTest->DefineGroup( GRP_S3_R13U_VC );
		pLampTest->SetReference( _V( 1.46822, 2.38861, 12.3598 ), SWITCH_ROT );
		pLampTest->SetMouseRegion( AID_R13U, 0.807637f, 0.268867f, 0.869638f, 0.342053f );
		pLampTest->SetSpringLoaded( true, 0 );
		pLampTest->SetSpringLoaded( true, 2 );

		pLimit->SetInitialAnimState( 0.5f );
		pLimit->DefineGroup( GRP_S7_R13U_VC );
		pLimit->SetReference( _V( 1.34787, 2.309935, 12.3598 ), SWITCH_ROT );
		pLimit->SetMouseRegion( AID_R13U, 0.618767f, 0.780350f, 0.677145f, 0.852451f );

		pFunc->SetInitialAnimState( 0.5f );
		pFunc->DefineGroup( GRP_S8_R13U_VC );
		pFunc->SetReference( _V( 1.34787, 2.309935, 12.3598 ), SWITCH_ROT );
		pFunc->SetMouseRegion( AID_R13U, 0.704619f, 0.780350f, 0.786034f, 0.852451f );
		pFunc->SetSpringLoaded( true, 0 );
		pFunc->SetSpringLoaded( true, 2 );

		pParam->SetInitialAnimState( 0.5f );
		pParam->DefineGroup( GRP_S9_R13U_VC );
		pParam->SetReference( _V( 1.34787, 2.309935, 12.3598 ), SWITCH_ROT );
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

		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + VC_OFFSET;

		oapiVCRegisterArea( AID_R13U, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP | PANEL_MOUSE_LBPRESSED );
		oapiVCSetAreaClickmode_Quadrilateral( AID_R13U,
			_V( 1.54125, 2.43524, 12.561 ) + ofs, _V( 1.54125, 2.43524, 12.2564 ) + ofs,
			_V( 1.30501, 2.28002, 12.561 ) + ofs, _V( 1.30501, 2.28002, 12.2564 ) + _V( 0.001, 0.001, 0.001 ) + ofs );
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
		
		/*pBundle = STS()->BundleManager()->CreateBundle( "R13_PARAMETER_SELECT", 16 );
		for (int i = 0; i < 9; i++) ParameterSelect[i].Connect( pBundle, i );
		
		pBundle = STS()->BundleManager()->CreateBundle( "R13_LIMIT_SET_VALUE", 16 );
		for (int i = 0; i < 8; i++) LimitValue[i].Connect( pBundle, i );*/
		return;
	}
};
