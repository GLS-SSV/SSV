/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/05/23   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/17   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/29   GLS
********************************************/
#include "ExtAirlock.h"
#include "../Atlantis.h"
#include "../meshres_ExtAL.h"
#include "../../CommonDefs.h"
#include <Orbitersdk.h>


namespace eva_docking
{
	const static char* MESHNAME_EXTAL = "SSV\\OV\\ExtAL";

	constexpr VECTOR3 EXTERNAL_AIRLOCK_MESH_OFFSET = {0.0, -1.49644, 7.7544};// [m]
	constexpr VECTOR3 EXTERNAL_AIRLOCK_MESH_AFT_OFFSET = {0.0, -1.49644, 5.65636};// [m]


	ExtAirlock::ExtAirlock( AtlantisSubsystemDirector* _director, const std::string &_ident, bool aftlocation, bool HideTopCover ):AtlantisSubsystem( _director, _ident ),
	aft(aftlocation), fHatchState(0.0), HideTopCover(HideTopCover)
	{
		mesh_extal = MESH_UNDEFINED;
		hExtALMesh = oapiLoadMeshGlobal( MESHNAME_EXTAL );
		oapiWriteLog( "(SSV_OV) [INFO] ExtAL mesh loaded" );
	}

	ExtAirlock::~ExtAirlock()
	{
	}

	void ExtAirlock::Realize( void )
	{
		AddMesh();
		return;
	}

	void ExtAirlock::AddMesh( void )
	{
		if (mesh_extal == MESH_UNDEFINED)
		{
			VECTOR3 pos = aft ? EXTERNAL_AIRLOCK_MESH_AFT_OFFSET : EXTERNAL_AIRLOCK_MESH_OFFSET;
			mesh_extal = STS()->AddMesh( hExtALMesh, &pos );
			oapiWriteLog( "(SSV_OV) [INFO] ExtAL mesh added" );
		}
		STS()->SetMeshVisibilityMode( mesh_extal, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
		return;
	}

	void ExtAirlock::VisualCreated( VISHANDLE vis )
	{
		if (HideTopCover == true)
		{
			DEVMESHHANDLE hExtALDevMesh = STS()->GetDevMesh( vis, mesh_extal );

			GROUPEDITSPEC grpSpec;
			grpSpec.flags = GRPEDIT_SETUSERFLAG;
			grpSpec.UsrFlag = 3;

			oapiWriteLog( "(SSV_OV) [INFO] Hiding ExtAL top hatch cover" );
			oapiEditMeshGroup( hExtALDevMesh, GRP_UPPER_HATCH_THERMAL_COVER_ExtAL, &grpSpec );
		}
		return;
	}

	void ExtAirlock::GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_keel, bool& Reversed_longeron1, bool& Reversed_longeron2 ) const
	{
		if (aft)
		{
			PLID_longeron1 = 177;
			PLID_longeron2 = 188;
			PLID_keel = 187;
		}
		else
		{
			PLID_longeron1 = 156;
			PLID_longeron2 = 167;
			PLID_keel = 166;
		}

		Reversed_longeron1 = false;
		Reversed_longeron2 = true;
		return;
	}

	double ExtAirlock::GetZPos( void ) const
	{
		return aft ? EXTERNAL_AIRLOCK_MESH_AFT_OFFSET.z : EXTERNAL_AIRLOCK_MESH_OFFSET.z;
	}
}
