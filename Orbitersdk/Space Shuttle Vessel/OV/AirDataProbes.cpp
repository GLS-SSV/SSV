/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2020/10/11   GLS
2020/11/10   GLS
2021/01/24   GLS
2021/02/07   GLS
2021/04/15   GLS
2021/05/30   GLS
2021/06/07   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/06/13   GLS
2021/07/14   GLS
2021/08/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
#include "AirDataProbes.h"
#include "Atlantis.h"
#include "meshres.h"
#include <MathSSV.h>


constexpr double PROBE_SPEED = 0.0333333;// single motor time (30sec) [1/sec]

const VECTOR3 PROBE_REF_LEFT = _V( -1.203364, -2.382218, 16.659451 );
const VECTOR3 PROBE_REF_RIGHT = _V( 1.203364, -2.382218, 16.659451 );

const VECTOR3 PROBE_AXIS_LEFT = _V( -0.096587, 0.97248, 0.21204 );
const VECTOR3 PROBE_AXIS_RIGHT = _V( -0.096587, -0.97248, -0.21204 );


AirDataProbes::AirDataProbes( AtlantisSubsystemDirector* _director ) : AtlantisSubsystem( _director, "AirDataProbes" ),
posleft(0.0),
posright(0.0)
{
}

AirDataProbes::~AirDataProbes()
{
}

void AirDataProbes::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "AIR_DATA_PROBES_FMC", 16 );
	L_ADP_STOW_1.Connect( pBundle, 0 );
	L_ADP_STOW_2.Connect( pBundle, 1 );
	L_ADP_DEPLOY_1.Connect( pBundle, 2 );
	L_ADP_DEPLOY_2.Connect( pBundle, 3 );
	LEFT_PROBE_MOTOR_1_PWR.Connect( pBundle, 4 );
	LEFT_PROBE_MOTOR_2_PWR.Connect( pBundle, 5 );
	R_ADP_STOW_1.Connect( pBundle, 6 );
	R_ADP_STOW_2.Connect( pBundle, 7 );
	R_ADP_DEPLOY_1.Connect( pBundle, 8 );
	R_ADP_DEPLOY_2.Connect( pBundle, 9 );
	RIGHT_PROBE_MOTOR_1_PWR.Connect( pBundle, 10 );
	RIGHT_PROBE_MOTOR_2_PWR.Connect( pBundle, 11 );

	AddAnimation();
	return;
}

void AirDataProbes::AddAnimation( void )
{
	static UINT ADPL_Grp[3] = {GRP_ADP_BASE_LEFT_EXTERIOR, GRP_ADP_BASE_LEFT_INTERIOR, GRP_ADP_LEFT};
	MGROUP_ROTATE* ADPL_Deploy = new MGROUP_ROTATE( STS()->OVmesh(), ADPL_Grp, 3, PROBE_REF_LEFT, PROBE_AXIS_LEFT, (float)(180.0 * RAD) );
	animleft = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( animleft, 0.0, 1.0, ADPL_Deploy );
	STS()->SetAnimation( animleft, posleft );
	SaveAnimation( ADPL_Deploy );

	static UINT ADPR_Grp[3] = {GRP_ADP_BASE_RIGHT_EXTERIOR, GRP_ADP_BASE_RIGHT_INTERIOR, GRP_ADP_RIGHT};
	MGROUP_ROTATE* ADPR_Deploy = new MGROUP_ROTATE( STS()->OVmesh(), ADPR_Grp, 3, PROBE_REF_RIGHT, PROBE_AXIS_RIGHT, (float)(180.0 * RAD) );
	animright = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( animright, 0.0, 1.0, ADPR_Deploy );
	STS()->SetAnimation( animright, posright );
	SaveAnimation( ADPR_Deploy );
	return;
}

void AirDataProbes::OnPreStep( double simt, double simdt, double mjd )
{
	// motors
	posleft = range( 0.0, posleft + (simdt * PROBE_SPEED * (LEFT_PROBE_MOTOR_1_PWR.GetVoltage() + LEFT_PROBE_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posright = range( 0.0, posright + (simdt * PROBE_SPEED * (RIGHT_PROBE_MOTOR_1_PWR.GetVoltage() + RIGHT_PROBE_MOTOR_2_PWR.GetVoltage())), 1.0 );

	// indications
	if (posleft == 0.0)// CL
	{
		L_ADP_STOW_1.SetLine();
		L_ADP_STOW_2.SetLine();
		L_ADP_DEPLOY_1.ResetLine();
		L_ADP_DEPLOY_2.ResetLine();
	}
	else if (posleft == 1.0)// OP
	{
		L_ADP_STOW_1.ResetLine();
		L_ADP_STOW_2.ResetLine();
		L_ADP_DEPLOY_1.SetLine();
		L_ADP_DEPLOY_2.SetLine();
	}
	else
	{
		L_ADP_STOW_1.ResetLine();
		L_ADP_STOW_2.ResetLine();
		L_ADP_DEPLOY_1.ResetLine();
		L_ADP_DEPLOY_2.ResetLine();
	}

	if (posright == 0.0)// CL
	{
		R_ADP_STOW_1.SetLine();
		R_ADP_STOW_2.SetLine();
		R_ADP_DEPLOY_1.ResetLine();
		R_ADP_DEPLOY_2.ResetLine();
	}
	else if (posright == 1.0)// OP
	{
		R_ADP_STOW_1.ResetLine();
		R_ADP_STOW_2.ResetLine();
		R_ADP_DEPLOY_1.SetLine();
		R_ADP_DEPLOY_2.SetLine();
	}
	else
	{
		R_ADP_STOW_1.ResetLine();
		R_ADP_STOW_2.ResetLine();
		R_ADP_DEPLOY_1.ResetLine();
		R_ADP_DEPLOY_2.ResetLine();
	}

	// set animations
	STS()->SetAnimation( animleft, posleft );
	STS()->SetAnimation( animright, posright );
	return;
}

bool AirDataProbes::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "LEFT", 4 ))
	{
		sscanf_s( line + 4, "%lf", &posleft );
		posleft = range( 0.0, posleft, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RIGHT", 5 ))
	{
		sscanf_s( line + 5, "%lf", &posright );
		posright = range( 0.0, posright, 1.0 );
		return true;
	}
	return false;
}

void AirDataProbes::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "LEFT", posleft );
	oapiWriteScenario_float( scn, "RIGHT", posright );
	return;
}
