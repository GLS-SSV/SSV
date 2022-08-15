/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/02/15   GLS
2021/02/16   GLS
2021/04/15   GLS
2021/05/30   GLS
2021/06/09   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/06/12   GLS
2021/06/13   GLS
2021/07/09   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
#include "ETUmbilicalDoors.h"
#include "Atlantis.h"
#include "meshres.h"
#include <MathSSV.h>


constexpr double DOOR_OPERATING_SPEED = 0.0208333;// single motor time (48 sec) [1/sec]
constexpr double DOOR_LATCH_OPERATING_SPEED = 0.0833333;// single motor time (12 sec) [1/sec]
constexpr double CL_LATCH_OPERATING_SPEED = 0.0833333;// single motor time (12 sec) [1/sec]

const VECTOR3 ETUMB_L_AXIS = _V( 0.0, -0.0174524, 0.999848 );
const VECTOR3 ETUMB_L_DOOR = _V( -1.408, -3.923235, -9.700069 );// door/hinge axis
const VECTOR3 ETUMB_L_DOORHINGE = _V( -1.323, -3.923235, -9.700069 );// hinge/fuselage axis

const VECTOR3 ETUMB_R_AXIS = _V( 0.0, 0.0174524, -0.999848 );
const VECTOR3 ETUMB_R_DOOR = _V( 1.408, -3.923235, -9.700069 );// door/hinge axis
const VECTOR3 ETUMB_R_DOORHINGE = _V( 1.323, -3.923235, -9.700069 );// hinge/fuselage axis

const float ETUMB_CL_ANGLE_ROT_1 = static_cast<float>(25.0 * RAD);// rotation and translation [rad]
const float ETUMB_CL_ANGLE_ROT_2 = static_cast<float>(33.75 * RAD);// rotation only [rad]
const VECTOR3 ETUMB_CL_1_AXIS = _V( 0.0, 0.999962, 0.00872654 );
const VECTOR3 ETUMB_CL_1_POS = _V( 0.0, -4.033836, -9.236473 );
const VECTOR3 ETUMB_CL_1_TRANS = _V( 0.0, -0.0923055, -0.000805538 );// 0.092309
const VECTOR3 ETUMB_CL_2_AXIS = _V( 0.0, 0.999048, 0.0436194 );
const VECTOR3 ETUMB_CL_2_POS = _V( 0.0, -4.043183, -10.161034 );
const VECTOR3 ETUMB_CL_2_TRANS = _V( 0.0, -0.0836123, -0.00365059 );// 0.083692


ETUmbilicalDoors::ETUmbilicalDoors( AtlantisSubsystemDirector* _director ):AtlantisSubsystem( _director, "ETUmbilicalDoors" ),
posleftdoor(0.0),
posleftdoorlatch(0.0),
posrightdoor(0.0),
posrightdoorlatch(0.0),
poscllatch1(0.0),
poscllatch2(0.0)
{
}

ETUmbilicalDoors::~ETUmbilicalDoors()
{
}

void ETUmbilicalDoors::Realize()
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_CL_FMC", 16 );
	CL_LATCH_1_STOW_1.Connect( pBundle, 0 );
	CL_LATCH_1_STOW_2.Connect( pBundle, 1 );
	CL_LATCH_1_DEPLOY_1.Connect( pBundle, 2 );
	CL_LATCH_1_DEPLOY_2.Connect( pBundle, 3 );
	CL_1_MOTOR_1_PWR.Connect( pBundle, 4 );
	CL_1_MOTOR_2_PWR.Connect( pBundle, 5 );
	CL_LATCH_2_STOW_1.Connect( pBundle, 6 );
	CL_LATCH_2_STOW_2.Connect( pBundle, 7 );
	CL_LATCH_2_DEPLOY_1.Connect( pBundle, 8 );
	CL_LATCH_2_DEPLOY_2.Connect( pBundle, 9 );
	CL_2_MOTOR_1_PWR.Connect( pBundle, 10 );
	CL_2_MOTOR_2_PWR.Connect( pBundle, 11 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_LEFT_FMC", 16 );
	LEFT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	LEFT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	LEFT_DOOR_OPEN_1.Connect( pBundle, 2 );
	LEFT_DOOR_OPEN_2.Connect( pBundle, 3 );
	LEFT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	LEFT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	LEFT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	LEFT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	LEFT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	LEFT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	LEFT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	LEFT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	LEFT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	LEFT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	LEFT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_RIGHT_FMC", 16 );
	RIGHT_DOOR_CLOSE_1.Connect( pBundle, 0 );
	RIGHT_DOOR_CLOSE_2.Connect( pBundle, 1 );
	RIGHT_DOOR_OPEN_1.Connect( pBundle, 2 );
	RIGHT_DOOR_OPEN_2.Connect( pBundle, 3 );
	RIGHT_DOOR_RDY_TO_LCH_1.Connect( pBundle, 4 );
	RIGHT_DOOR_RDY_TO_LCH_2.Connect( pBundle, 5 );
	RIGHT_DOOR_RDY_TO_LCH_3.Connect( pBundle, 6 );
	RIGHT_DOOR_MOTOR_1_PWR.Connect( pBundle, 7 );
	RIGHT_DOOR_MOTOR_2_PWR.Connect( pBundle, 8 );
	RIGHT_DOOR_LATCH_REL_1.Connect( pBundle, 9 );
	RIGHT_DOOR_LATCH_REL_2.Connect( pBundle, 10 );
	RIGHT_DOOR_LATCH_LAT_1.Connect( pBundle, 11 );
	RIGHT_DOOR_LATCH_LAT_2.Connect( pBundle, 12 );
	RIGHT_DOOR_LATCH_MOTOR_1_PWR.Connect( pBundle, 13 );
	RIGHT_DOOR_LATCH_MOTOR_2_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "ET_UMBILICAL_DOORS_POWER", 16 );
	//ET_UMBILICAL_DOOR_CENTERLINE_LATCH_STOW.Connect( pBundle, 0 );
	//ET_UMBILICAL_DOOR_LEFT_CLOSE.Connect( pBundle, 1 );
	//ET_UMBILICAL_DOOR_LEFT_OPEN.Connect( pBundle, 2 );
	ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH.Connect( pBundle, 3 );
	//ET_UMBILICAL_DOOR_LEFT_LATCH_RELEASE.Connect( pBundle, 4 );
	//ET_UMBILICAL_DOOR_RIGHT_CLOSE.Connect( pBundle, 5 );
	//ET_UMBILICAL_DOOR_RIGHT_OPEN.Connect( pBundle, 6 );
	ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH.Connect( pBundle, 7 );
	//ET_UMBILICAL_DOOR_RIGHT_LATCH_RELEASE.Connect( pBundle, 8 );

	AddAnimation();
	return;
}

void ETUmbilicalDoors::OnPreStep( double simt, double simdt, double mjd )
{
	// motors
	posleftdoorlatch = range( 0.0, posleftdoorlatch + (simdt * DOOR_LATCH_OPERATING_SPEED * (LEFT_DOOR_LATCH_MOTOR_1_PWR.GetVoltage() + LEFT_DOOR_LATCH_MOTOR_2_PWR.GetVoltage())), 1.0 );
	posrightdoorlatch = range( 0.0, posrightdoorlatch + (simdt * DOOR_LATCH_OPERATING_SPEED * (RIGHT_DOOR_LATCH_MOTOR_1_PWR.GetVoltage() + RIGHT_DOOR_LATCH_MOTOR_2_PWR.GetVoltage())), 1.0 );
	poscllatch1 = range( 0.0, poscllatch1 + (simdt * CL_LATCH_OPERATING_SPEED * (CL_1_MOTOR_1_PWR.GetVoltage() + CL_1_MOTOR_2_PWR.GetVoltage())), 1.0 );
	poscllatch2 = range( 0.0, poscllatch2 + (simdt * CL_LATCH_OPERATING_SPEED * (CL_2_MOTOR_1_PWR.GetVoltage() + CL_2_MOTOR_2_PWR.GetVoltage())), 1.0 );

	if (((posleftdoor != 1.0) || ((poscllatch1 < 0.5) && (poscllatch2 < 0.5))) && ((posleftdoor != 0.0) || (posleftdoorlatch > 0.5)))// only run if unlatched
	{
		double min = 0.0;
		double max = 1.0;

		// limit range if latches are in the way
		if ((poscllatch1 > 0.5) || (poscllatch2 > 0.5)) max = 0.98;
		if (posleftdoorlatch < 0.5) min = 0.02;

		posleftdoor = range( min, posleftdoor + (simdt * DOOR_OPERATING_SPEED * (LEFT_DOOR_MOTOR_1_PWR.GetVoltage() + LEFT_DOOR_MOTOR_2_PWR.GetVoltage())), max );
	}

	if (((posrightdoor != 1.0) || ((poscllatch1 < 0.5) && (poscllatch2 < 0.5))) && ((posrightdoor != 0.0) || (posrightdoorlatch > 0.5)))// only run if unlatched
	{
		double min = 0.0;
		double max = 1.0;

		// limit range if latches are in the way
		if ((poscllatch1 > 0.5) || (poscllatch2 > 0.5)) max = 0.98;
		if (posrightdoorlatch < 0.5) min = 0.02;

		posrightdoor = range( min, posrightdoor + (simdt * DOOR_OPERATING_SPEED * (RIGHT_DOOR_MOTOR_1_PWR.GetVoltage() + RIGHT_DOOR_MOTOR_2_PWR.GetVoltage())), max );
	}

	// indications
	if (posleftdoor == 0.0)// CL
	{
		LEFT_DOOR_CLOSE_1.SetLine();
		LEFT_DOOR_CLOSE_2.SetLine();
		LEFT_DOOR_OPEN_1.ResetLine();
		LEFT_DOOR_OPEN_2.ResetLine();
	}
	else if (posleftdoor == 1.0)// OP
	{
		LEFT_DOOR_CLOSE_1.ResetLine();
		LEFT_DOOR_CLOSE_2.ResetLine();
		LEFT_DOOR_OPEN_1.SetLine();
		LEFT_DOOR_OPEN_2.SetLine();
	}
	else
	{
		LEFT_DOOR_CLOSE_1.ResetLine();
		LEFT_DOOR_CLOSE_2.ResetLine();
		LEFT_DOOR_OPEN_1.ResetLine();
		LEFT_DOOR_OPEN_2.ResetLine();
	}

	if (posleftdoor <= 0.01)// RTL
	{
		LEFT_DOOR_RDY_TO_LCH_1.SetLine();
		LEFT_DOOR_RDY_TO_LCH_2.SetLine();
		LEFT_DOOR_RDY_TO_LCH_3.SetLine();
	}
	else
	{
		LEFT_DOOR_RDY_TO_LCH_2.ResetLine();

		if (ET_UMBILICAL_DOOR_RIGHT_LATCH_LATCH)// opposite switch override
		{
			LEFT_DOOR_RDY_TO_LCH_1.SetLine();
			LEFT_DOOR_RDY_TO_LCH_3.SetLine();
		}
		else
		{
			LEFT_DOOR_RDY_TO_LCH_1.ResetLine();
			LEFT_DOOR_RDY_TO_LCH_3.ResetLine();
		}
	}

	if (posrightdoor == 0.0)// CL
	{
		RIGHT_DOOR_CLOSE_1.SetLine();
		RIGHT_DOOR_CLOSE_2.SetLine();
		RIGHT_DOOR_OPEN_1.ResetLine();
		RIGHT_DOOR_OPEN_2.ResetLine();
	}
	else if (posrightdoor == 1.0)// OP
	{
		RIGHT_DOOR_CLOSE_1.ResetLine();
		RIGHT_DOOR_CLOSE_2.ResetLine();
		RIGHT_DOOR_OPEN_1.SetLine();
		RIGHT_DOOR_OPEN_2.SetLine();
	}
	else
	{
		RIGHT_DOOR_CLOSE_1.ResetLine();
		RIGHT_DOOR_CLOSE_2.ResetLine();
		RIGHT_DOOR_OPEN_1.ResetLine();
		RIGHT_DOOR_OPEN_2.ResetLine();
	}

	if (posrightdoor <= 0.01)// RTL
	{
		RIGHT_DOOR_RDY_TO_LCH_1.SetLine();
		RIGHT_DOOR_RDY_TO_LCH_2.SetLine();
		RIGHT_DOOR_RDY_TO_LCH_3.SetLine();
	}
	else
	{
		RIGHT_DOOR_RDY_TO_LCH_2.ResetLine();

		if (ET_UMBILICAL_DOOR_LEFT_LATCH_LATCH)// opposite switch override
		{
			RIGHT_DOOR_RDY_TO_LCH_1.SetLine();
			RIGHT_DOOR_RDY_TO_LCH_3.SetLine();
		}
		else
		{
			RIGHT_DOOR_RDY_TO_LCH_1.ResetLine();
			RIGHT_DOOR_RDY_TO_LCH_3.ResetLine();
		}
	}

	if (posleftdoorlatch == 0.0)// LAT
	{
		LEFT_DOOR_LATCH_LAT_1.SetLine();
		LEFT_DOOR_LATCH_LAT_2.SetLine();
		LEFT_DOOR_LATCH_REL_1.ResetLine();
		LEFT_DOOR_LATCH_REL_2.ResetLine();
	}
	else if (posleftdoorlatch == 1.0)// REL
	{
		LEFT_DOOR_LATCH_LAT_1.ResetLine();
		LEFT_DOOR_LATCH_LAT_2.ResetLine();
		LEFT_DOOR_LATCH_REL_1.SetLine();
		LEFT_DOOR_LATCH_REL_2.SetLine();
	}
	else
	{
		LEFT_DOOR_LATCH_LAT_1.ResetLine();
		LEFT_DOOR_LATCH_LAT_2.ResetLine();
		LEFT_DOOR_LATCH_REL_1.ResetLine();
		LEFT_DOOR_LATCH_REL_2.ResetLine();
	}

	if (posrightdoorlatch == 0.0)// LAT
	{
		RIGHT_DOOR_LATCH_LAT_1.SetLine();
		RIGHT_DOOR_LATCH_LAT_2.SetLine();
		RIGHT_DOOR_LATCH_REL_1.ResetLine();
		RIGHT_DOOR_LATCH_REL_2.ResetLine();
	}
	else if (posrightdoorlatch == 1.0)// REL
	{
		RIGHT_DOOR_LATCH_LAT_1.ResetLine();
		RIGHT_DOOR_LATCH_LAT_2.ResetLine();
		RIGHT_DOOR_LATCH_REL_1.SetLine();
		RIGHT_DOOR_LATCH_REL_2.SetLine();
	}
	else
	{
		RIGHT_DOOR_LATCH_LAT_1.ResetLine();
		RIGHT_DOOR_LATCH_LAT_2.ResetLine();
		RIGHT_DOOR_LATCH_REL_1.ResetLine();
		RIGHT_DOOR_LATCH_REL_2.ResetLine();
	}

	if (poscllatch1 == 0.0)// STO
	{
		CL_LATCH_1_STOW_1.SetLine();
		CL_LATCH_1_STOW_2.SetLine();
		CL_LATCH_1_DEPLOY_1.ResetLine();
		CL_LATCH_1_DEPLOY_2.ResetLine();
	}
	else if (poscllatch1 == 1.0)// LAT
	{
		CL_LATCH_1_STOW_1.ResetLine();
		CL_LATCH_1_STOW_2.ResetLine();
		CL_LATCH_1_DEPLOY_1.SetLine();
		CL_LATCH_1_DEPLOY_2.SetLine();
	}
	else
	{
		CL_LATCH_1_STOW_1.ResetLine();
		CL_LATCH_1_STOW_2.ResetLine();
		CL_LATCH_1_DEPLOY_1.ResetLine();
		CL_LATCH_1_DEPLOY_2.ResetLine();
	}

	if (poscllatch2 == 0.0)// STO
	{
		CL_LATCH_2_STOW_1.SetLine();
		CL_LATCH_2_STOW_2.SetLine();
		CL_LATCH_2_DEPLOY_1.ResetLine();
		CL_LATCH_2_DEPLOY_2.ResetLine();
	}
	else if (poscllatch2 == 1.0)// LAT
	{
		CL_LATCH_2_STOW_1.ResetLine();
		CL_LATCH_2_STOW_2.ResetLine();
		CL_LATCH_2_DEPLOY_1.SetLine();
		CL_LATCH_2_DEPLOY_2.SetLine();
	}
	else
	{
		CL_LATCH_2_STOW_1.ResetLine();
		CL_LATCH_2_STOW_2.ResetLine();
		CL_LATCH_2_DEPLOY_1.ResetLine();
		CL_LATCH_2_DEPLOY_2.ResetLine();
	}

	// set animations
	STS()->SetAnimation( anim_doorleft, posleftdoor );
	STS()->SetAnimation( anim_doorhingeleft, posleftdoor );
	STS()->SetAnimation( anim_doorright, posrightdoor );
	STS()->SetAnimation( anim_doorhingeright, posrightdoor );
	STS()->SetAnimation( anim_cllatch1, poscllatch1 );
	STS()->SetAnimation( anim_cllatch2, poscllatch2 );
	return;
}

void ETUmbilicalDoors::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "LEFT_DOOR", posleftdoor );
	oapiWriteScenario_float( scn, "LEFT_DOOR_LATCH", posleftdoorlatch );

	oapiWriteScenario_float( scn, "RIGHT_DOOR", posrightdoor );
	oapiWriteScenario_float( scn, "RIGHT_DOOR_LATCH", posrightdoorlatch );

	oapiWriteScenario_float( scn, "CL_LATCH_1", poscllatch1 );
	oapiWriteScenario_float( scn, "CL_LATCH_2", poscllatch2 );
	return;
}

bool ETUmbilicalDoors::OnParseLine( const char *keyword, const char *line )
{
	if (!strncmp( keyword, "LEFT_DOOR", 10 ))
	{
		sscanf_s( line, "%lf", &posleftdoor );
		posleftdoor = range( 0.0, posleftdoor, 1.0 );
		return true;
	}
	else if (!strncmp( keyword, "LEFT_DOOR_LATCH", 16 ))
	{
		sscanf_s( line, "%lf", &posleftdoorlatch );
		posleftdoorlatch = range( 0.0, posleftdoorlatch, 1.0 );
		return true;
	}
	else if (!strncmp( keyword, "RIGHT_DOOR", 11 ))
	{
		sscanf_s( line, "%lf", &posrightdoor );
		posrightdoor = range( 0.0, posrightdoor, 1.0 );
		return true;
	}
	else if (!strncmp( keyword, "RIGHT_DOOR_LATCH", 17 ))
	{
		sscanf_s( line, "%lf", &posrightdoorlatch );
		posrightdoorlatch = range( 0.0, posrightdoorlatch, 1.0 );
		return true;
	}
	else if (!strncmp( keyword, "CL_LATCH_1", 11 ))
	{
		sscanf_s( line, "%lf", &poscllatch1 );
		poscllatch1 = range( 0.0, poscllatch1, 1.0 );
		return true;
	}
	else if (!strncmp( keyword, "CL_LATCH_2", 11 ))
	{
		sscanf_s( line, "%lf", &poscllatch2 );
		poscllatch2 = range( 0.0, poscllatch2, 1.0 );
		return true;
	}
	return false;
}
void ETUmbilicalDoors::AddAnimation( void )
{
	MGROUP_ROTATE* ETUmbLDoorHinge = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, ETUMB_L_DOORHINGE, ETUMB_L_AXIS, (float)(110.0 * RAD) );
	anim_doorhingeleft = STS()->CreateAnimation( 0.0 );
	ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( anim_doorhingeleft, 0.0, 1.0, ETUmbLDoorHinge );
	SaveAnimation( ETUmbLDoorHinge );

	static UINT ETUmbLDoorGrp[2] = {GRP_ET_DOOR_LEFT_EXTERIOR, GRP_ET_DOOR_LEFT_INTERIOR};
	MGROUP_ROTATE* ETUmbLDoor = new MGROUP_ROTATE( STS()->OVmesh(), ETUmbLDoorGrp, 2, ETUMB_L_DOOR, ETUMB_L_AXIS, (float)(72.5 * RAD) );
	anim_doorleft = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_doorleft, 0.3, 1.0, ETUmbLDoor, parent );
	SaveAnimation( ETUmbLDoor );


	MGROUP_ROTATE* ETUmbRDoorHinge = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, ETUMB_R_DOORHINGE, ETUMB_R_AXIS, (float)(110.0 * RAD) );
	anim_doorhingeright = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_doorhingeright, 0.0, 1.0, ETUmbRDoorHinge );
	SaveAnimation( ETUmbRDoorHinge );

	static UINT ETUmbRDoorGrp[2] = {GRP_ET_DOOR_RIGHT_EXTERIOR, GRP_ET_DOOR_RIGHT_INTERIOR};
	MGROUP_ROTATE* ETUmbRDoor = new MGROUP_ROTATE( STS()->OVmesh(), ETUmbRDoorGrp, 2, ETUMB_R_DOOR, ETUMB_R_AXIS, (float)(72.5 * RAD) );
	anim_doorright = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_doorright, 0.3, 1.0, ETUmbRDoor, parent );
	SaveAnimation( ETUmbRDoor );

	static UINT ETUmbCL1Grp[1] = {GRP_ET_DOOR_CL_LATCH_1};
	MGROUP_TRANSLATE* ETUmbCL1Trans = new MGROUP_TRANSLATE( LOCALVERTEXLIST, NULL, 0, ETUMB_CL_1_TRANS );
	MGROUP_ROTATE* ETUmbCL1Rot1 = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, ETUMB_CL_1_POS, ETUMB_CL_1_AXIS, ETUMB_CL_ANGLE_ROT_1 );
	MGROUP_ROTATE* ETUmbCL1Rot2 = new MGROUP_ROTATE( STS()->OVmesh(), ETUmbCL1Grp, 1, ETUMB_CL_1_POS, ETUMB_CL_1_AXIS, ETUMB_CL_ANGLE_ROT_2 );
	anim_cllatch1 = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_cllatch1, 0.0, 0.77, ETUmbCL1Trans );
	parent = STS()->AddAnimationComponent( anim_cllatch1, 0.0, 0.77, ETUmbCL1Rot1, parent );
	STS()->AddAnimationComponent( anim_cllatch1, 0.77, 1.0, ETUmbCL1Rot2, parent );
	SaveAnimation( ETUmbCL1Trans );
	SaveAnimation( ETUmbCL1Rot1 );
	SaveAnimation( ETUmbCL1Rot2 );

	static UINT ETUmbCL2Grp[1] = {GRP_ET_DOOR_CL_LATCH_2};
	MGROUP_TRANSLATE* ETUmbCL2Trans = new MGROUP_TRANSLATE( LOCALVERTEXLIST, NULL, 0, ETUMB_CL_2_TRANS );
	MGROUP_ROTATE* ETUmbCL2Rot1 = new MGROUP_ROTATE( LOCALVERTEXLIST, NULL, 0, ETUMB_CL_2_POS, ETUMB_CL_2_AXIS, ETUMB_CL_ANGLE_ROT_1 );
	MGROUP_ROTATE* ETUmbCL2Rot2 = new MGROUP_ROTATE( STS()->OVmesh(), ETUmbCL2Grp, 1, ETUMB_CL_2_POS, ETUMB_CL_2_AXIS, ETUMB_CL_ANGLE_ROT_2 );
	anim_cllatch2 = STS()->CreateAnimation( 0.0 );
	parent = STS()->AddAnimationComponent( anim_cllatch2, 0.0, 0.5, ETUmbCL2Trans );
	parent = STS()->AddAnimationComponent( anim_cllatch2, 0.0, 0.77, ETUmbCL2Rot1, parent );
	STS()->AddAnimationComponent( anim_cllatch2, 0.77, 1.0, ETUmbCL2Rot2, parent );
	SaveAnimation( ETUmbCL2Trans );
	SaveAnimation( ETUmbCL2Rot1 );
	SaveAnimation( ETUmbCL2Rot2 );
	return;
}
