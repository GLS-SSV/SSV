/******* SSV File Modification Notice *******
Date         Developer
2020/05/01   GLS
2020/05/10   GLS
2020/05/17   GLS
2020/05/23   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/08/24   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/02/21   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
********************************************/
#include "DragChute.h"
#include "Atlantis.h"
#include "ParameterValues.h"
#include "..\CommonDefs.h"
#include <MathSSV.h>
#include <EngConst.h>


constexpr double DC_MASS = 246.0 * LBM2KG;// [kg]


constexpr double CHUTE_DEPLOY_TIME = 2.5;
// Time from chute deploy command to deployment of chute (s)
constexpr double CHUTE_INFLATE_TIME = 6.3;
// Time from chute deploy command to full inflation of chute (s)
constexpr double CHUTE_DEPLOY_RATE = 0.25;
// Rate at which chute deploys to reefed state (1/s)
constexpr double CHUTE_INFLATE_RATE = 1.0;
// Rate at which chute inflates (1/s)
constexpr double CHUTE_SPIN_RATE = 0.5;
// Rate at which chute spins (1/s)
constexpr double CHUTE_DEPLOY_SPEED = 165.0/MPS2KTS;
// Speed at which chute is deployed (m/s)
constexpr double CHUTE_JETTISON_SPEED = 60.0/MPS2KTS;
// Speed at which chute is jettisoned (m/s)
constexpr double CHUTE_FAIL_SPEED = 230.0/MPS2KTS;
// Lowest speed at which chute breaks off if deployed (m/s)

inline constexpr VECTOR3 CHUTE_ATTACH_POINT = { 0.0, 3.15401, -14.4542 };

inline constexpr double DRAG_CHUTE_SCALE_FACTOR = 55.0;// chosen to fit AIAA 2001-2051


DragChute::DragChute( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "DragChute" )
{
	mesh_index = MESH_UNDEFINED;
	hMesh = oapiLoadMeshGlobal( MESHNAME_CHUTE );

	DragChuteState = STOWED;
	DragChuteSize = 0.0;
	as_spin.Set( AnimState::OPENING, 0.0 );
	return;
}

DragChute::~DragChute()
{
	return;
}

void DragChute::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "DRAG_CHUTE", 16 );
	DragChuteARM[0].Connect( pBundle, 0 );
	DragChuteARM[1].Connect( pBundle, 1 );
	DragChuteDPY[0].Connect( pBundle, 2 );
	DragChuteDPY[1].Connect( pBundle, 3 );
	DragChuteJETT[0].Connect( pBundle, 4 );
	DragChuteJETT[1].Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "ACA2_1", 16 );
	DragChuteDPY2LT[1].Connect( pBundle, 6 );
	DragChuteARM2LT[1].Connect( pBundle, 10 );
	DragChuteJETT2LT[1].Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ACA2_2", 16 );
	DragChuteARM2LT[0].Connect( pBundle, 4 );
	DragChuteDPY2LT[0].Connect( pBundle, 8 );
	DragChuteJETT2LT[0].Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "ACA3_1", 16 );
	DragChuteJETT1LT[0].Connect( pBundle, 4 );
	DragChuteDPY1LT[0].Connect( pBundle, 8 );
	DragChuteARM1LT[0].Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "ACA3_5", 16 );
	DragChuteARM1LT[1].Connect( pBundle, 2 );
	DragChuteJETT1LT[1].Connect( pBundle, 10 );
	DragChuteDPY1LT[1].Connect( pBundle, 14 );

	AddMesh();
	DefineAnimations();
	return;
}

void DragChute::OnPreStep( double simt, double simdt, double mjd )
{
	double airspeed = STS()->GetAirspeed();
	double groundspeed = STS()->GetGroundspeed();

	switch (DragChuteState)
	{
		case STOWED:
			if ((((airspeed <= CHUTE_DEPLOY_SPEED) && (airspeed > CHUTE_JETTISON_SPEED) && STS()->GroundContact()) ||
				DragChuteARM[0].IsSet() || DragChuteARM[1].IsSet() || DragChuteDPY[0].IsSet() || DragChuteDPY[1].IsSet()))
			{
				STS()->SetAnimation( anim_deploy, 1.0 );
				STS()->SetMeshVisibilityMode( mesh_index, MESHVIS_EXTERNAL );

				DragChuteSize = 0.0;
				DragChuteDeployTime = simt;

				DragChuteARM1LT[0].SetLine();
				DragChuteARM1LT[1].SetLine();
				DragChuteARM2LT[0].SetLine();
				DragChuteARM2LT[1].SetLine();
				DragChuteDPY1LT[0].SetLine();
				DragChuteDPY1LT[1].SetLine();
				DragChuteDPY2LT[0].SetLine();
				DragChuteDPY2LT[1].SetLine();

				DragChuteState = DEPLOYING;
			}
			break;
		case DEPLOYING:
			if ((simt - DragChuteDeployTime) > CHUTE_DEPLOY_TIME)
			{
				DragChuteSize = min( 0.4, DragChuteSize + CHUTE_DEPLOY_RATE * simdt );
				STS()->SetAnimation( anim_deploy, 1 - DragChuteSize );
				SpinChute( simdt );

				if (Eq( DragChuteSize, 0.4, 0.001 )) DragChuteState = REEFED;
			}
			break;
		case REEFED:
			SpinChute( simdt );
			if ((simt - DragChuteDeployTime) > CHUTE_INFLATE_TIME) DragChuteState = INFLATED;
			break;
		case INFLATED:
			if ((groundspeed < CHUTE_JETTISON_SPEED) || (airspeed > CHUTE_FAIL_SPEED) || DragChuteJETT[0].IsSet() || DragChuteJETT[1].IsSet())
			{
				STS()->SetMeshVisibilityMode( mesh_index, MESHVIS_NEVER );

				DragChuteState = JETTISONED;
				DragChuteSize = 0.0;

				//add chute vessel
				VESSELSTATUS2 vs;
				vs.version = 2;
				vs.flag = 0;
				vs.rbody = 0;
				vs.base = 0;
				vs.port = 0;
				vs.status = 0;
				vs.rpos = _V( 0.0, 0.0, 0.0 );
				vs.rvel = _V( 0.0, 0.0, 0.0 );
				vs.vrot = _V( 0.0, 0.0, 0.0 );
				vs.arot = _V( 0.0, 0.0, 0.0 );
				vs.surf_lng = 0;
				vs.surf_lat = 0;
				vs.surf_hdg = 0;
				vs.nfuel = 0;
				vs.fuel = 0;
				vs.nthruster = 0;
				vs.thruster = 0;
				vs.ndockinfo = 0;
				vs.dockinfo = 0;
				vs.xpdr = 0;
				STS()->GetStatusEx( &vs );
				vs.status = 0;
				VECTOR3 chute_ofs;
				STS()->Local2Rel( STS()->GetOrbiterCoGOffset() + CHUTE_ATTACH_POINT, chute_ofs );
				vs.rpos = chute_ofs;
				char name[255];
				strcpy_s( name, STS()->GetName() );
				strcat_s( name, "-DragChute" );
				oapiCreateVesselEx( name, "SSV_DragChute", &vs );

				// HACK the light shouldn't turn on when drag chute fails, but only when the JETT PBI is used
				DragChuteJETT1LT[0].SetLine();
				DragChuteJETT1LT[1].SetLine();
				DragChuteJETT2LT[0].SetLine();
				DragChuteJETT2LT[1].SetLine();
			}
			else
			{
				if (DragChuteSize < 1.0)
				{
					DragChuteSize = min( 1.0, DragChuteSize + CHUTE_INFLATE_RATE * simdt );
					STS()->SetAnimation( anim_deploy, 1 - DragChuteSize );
				}
				SpinChute( simdt );
			}
			break;
		/*case JETTISONED:
			break;*/
	}
	return;
}

bool DragChute::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "JETTISONED", 10 ))
	{
		DragChuteState = JETTISONED;
		DragChuteSize = 0.0;
		DragChuteARM1LT[0].SetLine();
		DragChuteARM1LT[1].SetLine();
		DragChuteARM2LT[0].SetLine();
		DragChuteARM2LT[1].SetLine();
		DragChuteDPY1LT[0].SetLine();
		DragChuteDPY1LT[1].SetLine();
		DragChuteDPY2LT[0].SetLine();
		DragChuteDPY2LT[1].SetLine();
		DragChuteJETT1LT[0].SetLine();
		DragChuteJETT1LT[1].SetLine();
		DragChuteJETT2LT[0].SetLine();
		DragChuteJETT2LT[1].SetLine();
		return true;
	}
	else return false;
}

void DragChute::OnSaveState( FILEHANDLE scn ) const
{
	if (DragChuteState != STOWED) oapiWriteLine( scn, "JETTISONED" );// if deployed, assume jettisoned
	return;
}

double DragChute::GetSubsystemMass() const
{
	return DC_MASS;
}

void DragChute::AddMesh( void )
{
	VECTOR3 chute_ofs = CHUTE_ATTACH_POINT;
	mesh_index = STS()->AddMesh( hMesh, &chute_ofs );
	STS()->SetMeshVisibilityMode( mesh_index, MESHVIS_NEVER );
	return;
}

void DragChute::DefineAnimations( void )
{
	ANIMATIONCOMPONENT_HANDLE parent;

	static UINT ChuteCords[1] = { 0 };
	MGROUP_SCALE* ScaleCords = new MGROUP_SCALE( mesh_index, ChuteCords, 1, _V( 0.0, 0.0, -11.53 ), _V( 0.5, 0.5, 1.1 ) );
	static UINT Chute[3] = { 1, 2, 3 };
	MGROUP_SCALE* ScaleChute = new MGROUP_SCALE( mesh_index, Chute, 3, _V( 0.0, 0.0, -29.03 ), _V( 0.5, 0.5, 1.2 ) );
	static UINT DragChute[4] = { 0, 1, 2, 3 };
	MGROUP_SCALE* ScaleAll = new MGROUP_SCALE( mesh_index, DragChute, 4, _V( 0.0, 0.0, 0.0 ), _V( 0.01, 0.01, 0.01 ) );
	anim_deploy = STS()->CreateAnimation( 0.0 );

	STS()->AddAnimationComponent( anim_deploy, 0.0, 0.6, ScaleCords );
	SaveAnimation( ScaleCords );
	STS()->AddAnimationComponent( anim_deploy, 0.0, 0.6, ScaleChute );
	SaveAnimation( ScaleChute );
	parent = STS()->AddAnimationComponent( anim_deploy, 0.6, 0.9, ScaleAll );
	SaveAnimation( ScaleAll );
	anim_spin = STS()->CreateAnimation( 0.0 );

	MGROUP_ROTATE* SpinChute1 = new MGROUP_ROTATE( mesh_index, DragChute, 4, _V( 0, 0, 0 ), _V( 0.00609621, -0.0146035, -0.999875 ), (float)(400.0 * RAD) );
	STS()->AddAnimationComponent( anim_spin, 0.0, 0.5, SpinChute1, parent );
	SaveAnimation( SpinChute1 );
	MGROUP_ROTATE* SpinChute2 = new MGROUP_ROTATE( mesh_index, DragChute, 4, _V( 0, 0, 0 ), _V(-0.00965286, -0.00698363, -0.999929), (float)(400.0 * RAD) );
	STS()->AddAnimationComponent( anim_spin, 0.5, 1.0, SpinChute2, parent );
	SaveAnimation( SpinChute2 );
	return;
}

void DragChute::AddAero( void ) const
{
	STS()->CreateVariableDragElement( &DragChuteSize, DRAG_CHUTE_SCALE_FACTOR, CHUTE_ATTACH_POINT );
	return;
}

void DragChute::SpinChute( double simdt )
{
	if (as_spin.Opening())
	{
		as_spin.pos = min( 1.0, as_spin.pos + CHUTE_SPIN_RATE * simdt );
		if (Eq( as_spin.pos, 1.0, 0.01 )) as_spin.action = AnimState::CLOSING;
	}
	else
	{
		as_spin.pos = max( 0.0, as_spin.pos - CHUTE_SPIN_RATE * simdt );
		if (Eq( as_spin.pos, 0.0, 0.01 )) as_spin.action = AnimState::OPENING;
	}
	STS()->SetAnimation( anim_spin, as_spin.pos );
	return;
}