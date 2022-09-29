/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/20   GLS
2022/04/28   GLS
2022/08/05   GLS
2022/09/06   GLS
2022/09/07   GLS
2022/09/10   GLS
2022/09/29   GLS
********************************************/
#include "PanelR13U.h"
#include "../Atlantis.h"
#include "../ParameterValues.h"
#include "ThumbWheel.h"
#include "PushWheel.h"
#include "vc_defs.h"
#include "../meshres_vc_r13u.h"


namespace vc
{
	const static char* MESHNAME_PANEL = "SSV\\OV\\panelR13U";
	constexpr VECTOR3 OFFSET_PANEL = {1.30501, 2.28002, 12.561};


	PanelR13U::PanelR13U( Atlantis* _sts, const std::string &orbiter ):AtlantisPanel( _sts, "R13U" )
	{
		DefineMesh( MESHNAME_PANEL, OFFSET_PANEL );

		if ((orbiter == "Discovery") || (orbiter == "Endeavour")) thumbwheels = false;
		else thumbwheels = true;

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
	}

	PanelR13U::~PanelR13U()
	{
	}

	void PanelR13U::DefineVC()
	{
		const VECTOR3 switch_rot = _V( 0.0, 0.0, -1.0 );

		AddAIDToMouseEventList( AID_R13U );

		
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
		/*DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "?????", 16 );
		pParameterSelect100->Connect( pBundle, 0, 0 );

		pParameterSelect10->Connect( pBundle, 1, 0 );
		pParameterSelect10->Connect( pBundle, 2, 1 );
		pParameterSelect10->Connect( pBundle, 3, 2 );
		pParameterSelect10->Connect( pBundle, 4, 3 );

		pParameterSelect1->Connect( pBundle, 5, 0 );
		pParameterSelect1->Connect( pBundle, 6, 1 );
		pParameterSelect1->Connect( pBundle, 7, 2 );
		pParameterSelect1->Connect( pBundle, 8, 3 );

		pLimitSetValue1->Connect( pBundle, 8, 0 );
		pLimitSetValue1->Connect( pBundle, 9, 1 );
		pLimitSetValue1->Connect( pBundle, 10, 2 );

		pLimitSetValue01->Connect( pBundle, 11, 0 );
		pLimitSetValue01->Connect( pBundle, 12, 1 );
		pLimitSetValue01->Connect( pBundle, 13, 2 );
		pLimitSetValue01->Connect( pBundle, 14, 3 );

		pLimitSetValue005->Connect( pBundle, 15, 0 );*/

		AtlantisPanel::Realize();
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
