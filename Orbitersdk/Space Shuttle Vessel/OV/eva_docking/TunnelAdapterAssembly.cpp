/******* SSV File Modification Notice *******
Date         Developer
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/17   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/08/24   GLS
2021/11/14   GLS
2022/01/01   GLS
2022/03/24   GLS
2022/03/26   GLS
********************************************/
#include "TunnelAdapterAssembly.h"
#include "..\Atlantis.h"
#include "..\meshres_TAA.h"
#include "..\..\CommonDefs.h"


namespace eva_docking
{
	const static char* MESHNAME_TAA = "SSV\\OV\\TAA";

	constexpr VECTOR3 TAA_POS = {0.0, -1.49644, 8.5418};// [m]
	constexpr VECTOR3 TAA_AFT_POS = {0.0, -1.49644, 5.328702};// [m]

	constexpr double TAA_MASS = 200.0;// [kg]
	constexpr double TAA_AFT_POS_MASS = 200.0;// [kg]
	constexpr VECTOR3 TAA_CG = {0.0, -1.49644, 8.5418};// (center of TAA) Xo+618.0 Yo+0.0 Zo+357.9
	constexpr VECTOR3 TAA_AFT_POS_CG = {0.0, -1.49644, 5.3287};// (center of TAA, should be higher due to truss) Xo+744.5 Yo+0.0 Zo+357.9


	TunnelAdapterAssembly::TunnelAdapterAssembly( AtlantisSubsystemDirector* _director, bool aftlocation, bool extal ):AtlantisSubsystem( _director, "TunnelAdapterAssembly" ),
	aft(aftlocation), extal(extal)
	{
		mesh_idx = MESH_UNDEFINED;

		hMesh = oapiLoadMeshGlobal( MESHNAME_TAA );
		oapiWriteLog( "TAA mesh loaded" );
		return;
	}

	TunnelAdapterAssembly::~TunnelAdapterAssembly( void )
	{
	}

	double TunnelAdapterAssembly::GetSubsystemMass( void ) const
	{
		return aft ? TAA_AFT_POS_MASS : TAA_MASS;
	}

	bool TunnelAdapterAssembly::GetSubsystemCoG( VECTOR3& CoG ) const
	{
		CoG = aft ? TAA_AFT_POS_CG : TAA_CG;
		return true;
	}

	void TunnelAdapterAssembly::Realize( void )
	{
		AddMesh();
		return;
	}

	void TunnelAdapterAssembly::AddMesh( void )
	{
		if (mesh_idx == MESH_UNDEFINED)
		{
			VECTOR3 pos = aft ? TAA_AFT_POS : TAA_POS;
			mesh_idx = STS()->AddMesh( hMesh, &pos );
			oapiWriteLog( "TAA mesh added" );
		}
		STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
		return;
	}

	void TunnelAdapterAssembly::VisualCreated( VISHANDLE vis )
	{
		DEVMESHHANDLE hTAADevMesh = STS()->GetDevMesh( vis, mesh_idx );
		GROUPEDITSPEC grpSpec;
		grpSpec.flags = GRPEDIT_SETUSERFLAG;
		grpSpec.UsrFlag = 3;

		// hide unneeded parts based on TAA position
		if (aft)
		{
			// hide tunnel forward extension
			oapiEditMeshGroup( hTAADevMesh, GRP_FORWARD_EXTENSION_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_TUNNEL_FORWARD_EXTENSION_HANDRAIL_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_EXTENSION_FLEX_SECTION_TAA, &grpSpec );
		}
		else
		{
			// hide truss
			oapiEditMeshGroup( hTAADevMesh, GRP_TRUNNIONS_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_TRUSS_CRADLE_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_FORWARD_FLEX_SECTION_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_FORWARD_TUNNEL_STRUCTURE_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_FORWARD_TUNNEL_BLANKETS_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_AFT_FLEX_SECTION_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_AFT_TUNNEL_STRUCTURE_TAA, &grpSpec );
			oapiEditMeshGroup( hTAADevMesh, GRP_AFT_TUNNEL_BLANKETS_TAA, &grpSpec );

			if (extal)
			{
				// hide aft hatch
				oapiEditMeshGroup( hTAADevMesh, GRP_AFT_HATCH_FRAME_TAA, &grpSpec );
				oapiEditMeshGroup( hTAADevMesh, GRP_AFT_HATCH_TAA, &grpSpec );
				oapiEditMeshGroup( hTAADevMesh, GRP_AFT_HATCH_EQUIPMENT_INSIDE_TAA, &grpSpec );
				oapiEditMeshGroup( hTAADevMesh, GRP_AFT_HATCH_EQUIPMENT_OUTSIDE_TAA, &grpSpec );
				oapiEditMeshGroup( hTAADevMesh, GRP_AFT_HATCH_HINGE_ARMS_TAA, &grpSpec );

				// hide tunnel forward extension
				oapiEditMeshGroup( hTAADevMesh, GRP_FORWARD_EXTENSION_TAA, &grpSpec );
				oapiEditMeshGroup( hTAADevMesh, GRP_TUNNEL_FORWARD_EXTENSION_HANDRAIL_TAA, &grpSpec );
				oapiEditMeshGroup( hTAADevMesh, GRP_EXTENSION_FLEX_SECTION_TAA, &grpSpec );
			}
		}
		return;
	}

	void TunnelAdapterAssembly::GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_keel, bool& Reversed_longeron1, bool& Reversed_longeron2 ) const
	{
		if (aft)
		{
			PLID_longeron1 = 177;
			PLID_longeron2 = 200;
			PLID_keel = 200;
		}
		else
		{
			PLID_longeron1 = 0;
			PLID_longeron2 = 0;
			PLID_keel = 0;
		}

		Reversed_longeron1 = false;
		Reversed_longeron2 = false;
		return;
	}
};