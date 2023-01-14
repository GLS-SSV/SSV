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
2023/01/14   GLS
********************************************/
#include "ExtAirlock.h"
#include "../Atlantis.h"
#include "../ExternalLight.h"
#include "../meshres_ExtAL.h"
#include "../../CommonDefs.h"
#include <Orbitersdk.h>


namespace eva_docking
{
	const static char* MESHNAME_EXTAL = "SSV\\OV\\ExtAL";

	constexpr VECTOR3 EXTERNAL_AIRLOCK_MESH_OFFSET = {0.0, -1.49644, 7.7544};// [m]
	constexpr VECTOR3 EXTERNAL_AIRLOCK_MESH_AFT_OFFSET = {0.0, -1.49644, 5.65636};// [m]

	// light positions (aft position)
	const VECTOR3 LIGHT_TRUSS_FWD_POS = _V( 0.452628, 0.060834, 6.764816 );// Xo+687.96, Yo+17.82, Zo+419.21
	const VECTOR3 LIGHT_TRUSS_AFT_POS = _V( 1.204722, 0.060834, 4.669062 );// Xo+770.47, Yo+47.43, Zo+419.21
	
	const VECTOR3 LIGHT_DIR = _V( 0.0, 1.0, 0.0 );
	
	constexpr double LIGHT_RANGE = 20.0;// [m]
	const double LIGHT_UMBRA_ANGLE = 40.0 * RAD;// [rad]
	const double LIGHT_PENUMBRA_ANGLE = LIGHT_UMBRA_ANGLE + (20.0 * RAD);// [rad]

	constexpr double LIGHT_ATT0 = 0.4;// [1]
	constexpr double LIGHT_ATT1 = 0.3;// [1]
	constexpr double LIGHT_ATT2 = 0.03;// [1]


	ExtAirlock::ExtAirlock( AtlantisSubsystemDirector* _director, const std::string &_ident, bool aftlocation, bool HideTopCover ):AtlantisSubsystem( _director, _ident ),
	aft(aftlocation), fHatchState(0.0), HideTopCover(HideTopCover)
	{
		mesh_extal = MESH_UNDEFINED;
		hExtALMesh = oapiLoadMeshGlobal( MESHNAME_EXTAL );
		oapiWriteLog( "(SSV_OV) [INFO] ExtAL mesh loaded" );

		// lights
		lights[0] = new ExternalLight( STS(), LIGHT_TRUSS_FWD_POS + (aft ? _V( 0.0, 0.0, 0.0) : _V( 0.0, 0.0, EXTERNAL_AIRLOCK_MESH_OFFSET.z - EXTERNAL_AIRLOCK_MESH_AFT_OFFSET.z )), LIGHT_DIR, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, true );
		lights[1] = new ExternalLight( STS(), LIGHT_TRUSS_AFT_POS + (aft ? _V( 0.0, 0.0, 0.0) : _V( 0.0, 0.0, EXTERNAL_AIRLOCK_MESH_OFFSET.z - EXTERNAL_AIRLOCK_MESH_AFT_OFFSET.z )), LIGHT_DIR, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, true );
	}

	ExtAirlock::~ExtAirlock()
	{
		delete lights[0];
		delete lights[1];
	}

	void ExtAirlock::Realize( void )
	{
		AddMesh();

		DiscreteBundle* pBundle = BundleManager()->CreateBundle( "ODS_LIGHTS", 16 );
		lights[0]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 0 );
		lights[0]->DefineMeshGroup( mesh_extal, GRP_AIRLOCK_TRUSS_FWD_LIGHT_ExtAL );
		lights[1]->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 1 );
		lights[1]->DefineMeshGroup( mesh_extal, GRP_AIRLOCK_TRUSS_AFT_LIGHT_ExtAL );
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

		// update UV in lights
		lights[0]->VisualCreated();
		lights[1]->VisualCreated();
		return;
	}

	void ExtAirlock::OnPostStep( double simt, double simdt, double mjd )
	{
		RunLights( simdt );
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

	void ExtAirlock::RunLights( double simdt )
	{
		lights[0]->TimeStep( simdt );
		lights[1]->TimeStep( simdt );
		return;
	}

	void ExtAirlock::UpdateLights( void )
	{
		lights[0]->ShiftLightPosition( STS()->GetOrbiterCoGOffset() );
		lights[1]->ShiftLightPosition( STS()->GetOrbiterCoGOffset() );
		return;
	}
}
