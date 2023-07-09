#include "SPDS.h"
#include "meshres_SPDS.h"
#include "../CommonDefs.h"
#include "Atlantis.h"
#include "PRLA_defs.h"
#include <MathSSV.h>
#include <EngConst.h>


const static char* MESHNAME = "SSV\\OV\\SPDS_Port";

const VECTOR3 MESH_OFFSET = _V( 0.0, 0.0, 0.0 );

constexpr double MASS = 180.0 * LBM2KG;// [kg]

constexpr double PL_SEP_SPEED = 0.3;// TODO [m/s]

const VECTOR3 Zo_TRANSLATION = _V( 0.0, 2.0, 0.0 ) * IN2M;// 2'' [m]
constexpr double Zo_SPEED = 0.5;// (2.0 s)  [1/s]

constexpr double Yo_MOTOR_SPEED = 0.00625;// single motor time (160.0s) [1/s]
constexpr float Yo_RESTOW = 10.666667f;// distance from inboard position to restow position (2'') [deg]
constexpr float Yo_OUTBD = 16.0f;// distance from inboard position to outboard position (3'') [deg]
const VECTOR3 SUPPORT_ASSEMBLY_OUTBOARD_BOTTOM_AXIS_POS = _V( -2.446838, -0.1364045864, 0.0 );
const VECTOR3 SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS = _V( -2.381561, -0.1364045864, 0.0 );
const VECTOR3 SUPPORT_ASSEMBLY_OUTBOARD_TOP_AXIS_POS = _V( -2.408738, 0.134691, 0.0 );
const VECTOR3 SUPPORT_ASSEMBLY_INBOARD_TOP_AXIS_POS = _V( -2.343461, 0.134691, 0.0 );
const VECTOR3 SUPPORT_ASSEMBLY_AXIS_DIR = _V( 0.0, 0.0, 1.0 );
const float SUPPORT_ASSEMBLY_ANGLE = static_cast<float>((Yo_RESTOW + Yo_OUTBD)* RAD);// [rad]
constexpr float Yo_POS_INBD = Yo_RESTOW / (Yo_RESTOW + Yo_OUTBD);// Yo animation at inboard position [1]
const double Yo_POS_MARGIN = 0.005;

const VECTOR3 Zo_SPRING_BASE = _V( 0.0, -0.039828, 0.0 );
const VECTOR3 Zo_SPRING_SCALE = _V( 1.0, 0.1135/*spring length*/ / (0.1135/*spring length*/ - 0.0508/*2''*/), 1.0 );

const float RDU_MIN = static_cast<float>(-9.0 * RAD);// angle from stow position to reberth position [rad]
const float RDU_MAX = static_cast<float>(114.0 * RAD);// angle from stow position to deploy position [rad]
const float RDU_RANGE = RDU_MAX - RDU_MIN;// full (powered) RDU rotation range [rad]
const float RDU_POS_STOW = static_cast<float>((0.0 - RDU_MIN) / RDU_RANGE);// RDU animation at stow position [1]
constexpr double RDU_MOTOR_SPEED = 0.00154472;// single motor time (647.368s) [1/s]
const VECTOR3 RDU_POS = _V( -2.3876, 0.2333, 0.0 );// TODO
const VECTOR3 RDU_AXIS = _V( 0.0, 0.0, 1.0 );
const double RDU_POS_MARGIN = 0.001;

constexpr double EJECTION_PISTON_LENGTH = 1.75 * IN2M;// [m]
const VECTOR3 EJECTION_PISTON_TRANSLATION = _V( EJECTION_PISTON_LENGTH, 0.0, 0.0 );// [m]
constexpr double EJECTION_PISTON_SPEED = PL_SEP_SPEED / EJECTION_PISTON_LENGTH;// [1/s]

constexpr unsigned int PLID_OFFSET = 5;
constexpr unsigned int PLID_OFFSET_REVERSED = 3;


SPDS::SPDS( AtlantisSubsystemDirector *_director, const mission::MissionSPDS& spds, bool portside ) : AtlantisSubsystem( _director, "SPDS" ), MPM_Base( true ),
mesh_idx_SPDS{MESH_UNDEFINED, MESH_UNDEFINED}, anim_Zo(0), anim_Yo(0), anim_RDU{0,0}, anim_EjectionPiston(0), hAttach(NULL),  attachpos(ACTIVE_CL_FWD_POS),
motorYo(0.0), posZo(0.0), motorRDU{0.0, 0.0}, posEjectionPiston(0.0), RDU_PRI_PED_ENGAGED(true), RDU_SEC_PED_ENGAGED(false), PAYLOAD_RELEASED(false), unlockZo(false), LatchState{0.0, 0.0, 0.0, 0.0, 0.0}, spds(spds)
{

	return;
}

SPDS::~SPDS( void )
{
	return;
}

void SPDS::Realize( void )
{
	discsignals::DiscreteBundle* pBundle = BundleManager()->CreateBundle( "PORT_MPM_IND", 16 );
	//PORT_SHLD_MECH_STOW_IND_1.Connect( pBundle, 0 );
	PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_DIS.Connect( pBundle, 1 );
	SEC_Zo_SYS_A_EXTEND.Connect( pBundle, 2 );
	PAYLOAD_RELEASE_SEC_PED_SYS_A_REL.Connect( pBundle, 3 );
	//PORT_SHLD_MECH_DEPLOY_IND_1.Connect( pBundle, 4 );
	PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_ENG.Connect( pBundle, 5 );
	PRI_Zo_SYS_A_EXTEND.Connect( pBundle, 6 );
	PAYLOAD_RELEASE_SEC_PED_SYS_A_LAT.Connect( pBundle, 7 );
	//PORT_SHLD_MECH_STOW_IND_2.Connect( pBundle, 8 );
	PAYLOAD_RELEASE_PRI_PED_SYS_A_REL.Connect( pBundle, 9 );
	SEC_Zo_SYS_B_EXTEND.Connect( pBundle, 10 );
	PAYLOAD_RELEASE_SEC_PED_SYS_B_REL.Connect( pBundle, 11 );
	//PORT_SHLD_MECH_DEPLOY_IND_2.Connect( pBundle, 12 );
	PAYLOAD_RELEASE_PRI_PED_SYS_A_LAT.Connect( pBundle, 13 );
	PRI_Zo_SYS_B_EXTEND.Connect( pBundle, 14 );
	PAYLOAD_RELEASE_SEC_PED_SYS_B_LAT.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_PWR", 16 );
	Yo_MOTOR_A_MMC4_OUTBD_INBD.Connect( pBundle, 0 );
	Yo_MOTOR_B_MMC2_OUTBD_INBD.Connect( pBundle, 1 );
	//PORT_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 2 );
	//PORT_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 3 );
	//PORT_MPM_FWD_1_IND_PWR.Connect( pBundle, 4 );
	//PORT_MPM_FWD_2_IND_PWR.Connect( pBundle, 5 );
	//PORT_MPM_MID_1_IND_PWR.Connect( pBundle, 6 );
	//PORT_MPM_MID_2_IND_PWR.Connect( pBundle, 7 );
	//PORT_MPM_AFT_1_IND_PWR.Connect( pBundle, 8 );
	//PORT_MPM_AFT_2_IND_PWR.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_IND", 16 );
	PRI_RDU_SYS_B_REBERTH.Connect( pBundle, 0 );
	PRI_RDU_SYS_B_DEPLOY.Connect( pBundle, 1 );
	PRI_RDU_SYS_A_REBERTH.Connect( pBundle, 2 );
	PRI_RDU_SYS_A_DEPLOY.Connect( pBundle, 3 );
	PAYLOAD_RELEASE_PRI_PED_SYS_B_LAT.Connect( pBundle, 4 );
	PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_DIS.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "MID_MRL_IND", 16 );
	PRI_Yo_SYS_A_BERTH.Connect( pBundle, 0 );
	PRI_Yo_SYS_A_INBD.Connect( pBundle, 1 );
	PRI_Yo_SYS_B_BERTH.Connect( pBundle, 2 );
	PRI_Yo_SYS_B_INBD.Connect( pBundle, 3 );
	PRI_Yo_SYS_A_OUTBD.Connect( pBundle, 4 );
	PRI_Yo_SYS_B_OUTBD.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "AFT_MRL_IND", 16 );
	PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_ENG.Connect( pBundle, 0 );
	PAYLOAD_RELEASE_PRI_PED_SYS_B_REL.Connect( pBundle, 1 );
	PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_ENG.Connect( pBundle, 2 );
	PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_ENG.Connect( pBundle, 3 );
	PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_DIS.Connect( pBundle, 4 );
	PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_DIS.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "FWD_MRL_PWR", 16 );
	PRI_RDU_MOTOR_B_MMC2_DPY_REBERTH.Connect( pBundle, 0 );
	PRI_RDU_MOTOR_A_MMC4_DPY_REBERTH.Connect( pBundle, 1 );
	//PORT_FWD_MRL_IND_1_PWR.Connect( pBundle, 2 );
	//PORT_FWD_MRL_IND_2_PWR.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 5 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 10 );
	SEC_Yo_SYS_A_BERTH.Connect( pBundle, 0 );
	//PL2_1_REL_A.Connect( pBundle, 1 );
	//PL2_1_RDY_A.Connect( pBundle, 2 );
	Yo_MOTOR_A_MMC1_OUTBD_BERTH.Connect( pBundle, 3 );
	//PL2_1_IND_A.Connect( pBundle, 4 );
	SEC_Yo_SYS_B_BERTH.Connect( pBundle, 5 );
	//PL2_1_REL_B.Connect( pBundle, 6 );
	//PL2_1_RDY_B.Connect( pBundle, 7 );
	Yo_MOTOR_B_MMC3_OUTBD_BERTH.Connect( pBundle, 8 );
	//PL2_1_IND_B.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 10 );
	PRI_RDU_SYS_A_STOW.Connect( pBundle, 0 );
	//PL2_2_REL_A.Connect( pBundle, 1 );
	//PL2_2_RDY_A.Connect( pBundle, 2 );
	PRI_RDU_MOTOR_A_MMC1_DPY_STO.Connect( pBundle, 3 );
	PL2_2_IND_A.Connect( pBundle, 4 );
	PRI_RDU_SYS_B_STOW.Connect( pBundle, 5 );
	//PL2_2_REL_B.Connect( pBundle, 6 );
	//PL2_2_RDY_B.Connect( pBundle, 7 );
	PRI_RDU_MOTOR_B_MMC3_DPY_STO.Connect( pBundle, 8 );
	PL2_2_IND_B.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 10 );
	//PL2_3_LAT_A.Connect( pBundle, 0 );
	//PL2_3_REL_A.Connect( pBundle, 1 );
	//PL2_3_RDY_A.Connect( pBundle, 2 );
	PRI_RDU_MOTOR_A_MMC1_DPY_REBERTH.Connect( pBundle, 3 );
	//PL2_3_IND_A.Connect( pBundle, 4 );
	//PL2_3_LAT_B.Connect( pBundle, 5 );
	//PL2_3_REL_B.Connect( pBundle, 6 );
	//PL2_3_RDY_B.Connect( pBundle, 7 );
	PRI_RDU_MOTOR_B_MMC3_DPY_REBERTH.Connect( pBundle, 8 );
	//PL2_3_IND_B.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 10 );
	SEC_RDU_SYS_A_REBERTH.Connect( pBundle, 0 );
	//PL3_3_REL_A.Connect( pBundle, 1 );
	//PL3_3_RDY_A.Connect( pBundle, 2 );
	SEC_RDU_MOTOR_A_MMC1_DPY_REBERTH.Connect( pBundle, 3 );
	PL3_3_IND_A.Connect( pBundle, 4 );
	SEC_RDU_SYS_B_REBERTH.Connect( pBundle, 5 );
	//PL3_3_REL_B.Connect( pBundle, 6 );
	//PL3_3_RDY_B.Connect( pBundle, 7 );
	SEC_RDU_MOTOR_B_MMC3_DPY_REBERTH.Connect( pBundle, 8 );
	PL3_3_IND_B.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 10 );
	SEC_RDU_SYS_A_STOW.Connect( pBundle, 0 );
	SEC_RDU_SYS_A_DEPLOY.Connect( pBundle, 1 );
	//PL3_4_RDY_A.Connect( pBundle, 2 );
	SEC_RDU_MOTOR_A_MMC1_DPY_STO.Connect( pBundle, 3 );
	//PL3_4_IND_A.Connect( pBundle, 4 );
	SEC_RDU_SYS_B_STOW.Connect( pBundle, 5 );
	SEC_RDU_SYS_B_DEPLOY.Connect( pBundle, 6 );
	//PL3_4_RDY_B.Connect( pBundle, 7 );
	SEC_RDU_MOTOR_B_MMC3_DPY_STO.Connect( pBundle, 8 );
	//PL3_4_IND_B.Connect( pBundle, 9 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 10 );
	SEC_Yo_SYS_A_INBD.Connect( pBundle, 0 );
	SEC_Yo_SYS_A_OUTBD.Connect( pBundle, 1 );
	//PL3_5_RDY_A.Connect( pBundle, 2 );
	Yo_MOTOR_A_MMC1_OUTBD_INBD.Connect( pBundle, 3 );
	PL3_5_IND_A.Connect( pBundle, 4 );
	SEC_Yo_SYS_B_INBD.Connect( pBundle, 5 );
	SEC_Yo_SYS_B_OUTBD.Connect( pBundle, 6 );
	//PL3_5_RDY_B.Connect( pBundle, 7 );
	Yo_MOTOR_B_MMC3_OUTBD_INBD.Connect( pBundle, 8 );
	PL3_5_IND_B.Connect( pBundle, 9 );

	pBundle = STS()->BundleManager()->CreateBundle( "SPDS_Pyros", 16 );
	PAYLOAD_RELEASE_SYS_A_ARM.Connect( pBundle, 0 );
	PAYLOAD_RELEASE_SYS_B_ARM.Connect( pBundle, 1 );
	PAYLOAD_RELEASE_SYS_A_FIRE.Connect( pBundle, 2 );
	PAYLOAD_RELEASE_SYS_B_FIRE.Connect( pBundle, 3 );
	PEDESTAL_DRIVE_XFER_SYS_A_ARM.Connect( pBundle, 4 );
	PEDESTAL_DRIVE_XFER_SYS_B_ARM.Connect( pBundle, 5 );
	PEDESTAL_DRIVE_XFER_SYS_A_FIRE.Connect( pBundle, 6 );
	PEDESTAL_DRIVE_XFER_SYS_B_FIRE.Connect( pBundle, 7 );

	for (int i = 0; i < 5; i++)
	{
		string str = "PL_1_SEL_LATCH_" + std::to_string( i + 1 );
		DiscreteBundle* pBundle = BundleManager()->CreateBundle( str, 10 );
		LatchLAT_A[i].Connect( pBundle, 0 );
		LatchREL_A[i].Connect( pBundle, 1 );
		LatchRDY_A[i].Connect( pBundle, 2 );
		LatchMOTOR_1_PWR[i].Connect( pBundle, 3 );
		LatchIND_A[i].Connect( pBundle, 4 );
		LatchLAT_B[i].Connect( pBundle, 5 );
		LatchREL_B[i].Connect( pBundle, 6 );
		LatchRDY_B[i].Connect( pBundle, 7 );
		LatchMOTOR_2_PWR[i].Connect( pBundle, 8 );
		LatchIND_B[i].Connect( pBundle, 9 );
	}

	AddMesh();
	DefineAnimations();
	LoadLatches();
	SetIndications();
	SetAnimations();

	// TODO init PAYLOAD_RELEASED
	return;
}

void SPDS::AddMesh( void )
{
	// add SPDS meshes
	MESHHANDLE hMesh_SPDS = oapiLoadMeshGlobal( MESHNAME );

	// find PRLA Xo position
	double Xo = PLID_Xo[spds.PLID[0] - PLID_Xo_base + (spds.Reversed[0] ? PLID_OFFSET_REVERSED : PLID_OFFSET)];
	if (Xo > 0.0)
	{
		// convert to z position
		VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + MESH_OFFSET + pos;
		mesh_idx_SPDS[0] = STS()->AddMesh( hMesh_SPDS, &ofs );
		STS()->SetMeshVisibilityMode( mesh_idx_SPDS[0], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}
	else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: 0", spds.PLID[0] );


	// find PRLA Xo position
	Xo = PLID_Xo[spds.PLID[1] - PLID_Xo_base + (spds.Reversed[1] ? PLID_OFFSET_REVERSED : PLID_OFFSET)];
	if (Xo > 0.0)
	{
		// convert to z position
		VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );
		VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + MESH_OFFSET + pos;
		mesh_idx_SPDS[1] = STS()->AddMesh( hMesh_SPDS, &ofs );
		STS()->SetMeshVisibilityMode( mesh_idx_SPDS[1], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	}
	else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: 1", spds.PLID[1] );
	return;
}

void SPDS::GetPLBInfo( unsigned short& PLID_longeron_port1, unsigned short& PLID_longeron_port2, unsigned short& PLID_longeron_stbd1, unsigned short& PLID_longeron_stbd2, unsigned short& PLID_keel ) const
{
	PLID_longeron_port1 = spds.PLID[0];
	PLID_longeron_port2 = spds.PLID[1];
	PLID_longeron_stbd1 = spds.PLID[2];
	PLID_longeron_stbd2 = spds.PLID[3];
	PLID_keel = spds.PLID[4];
	return;
}

void SPDS::DefineAnimations( void )
{
	// SPDS animations
	// Yo motion
	static UINT SUPPORT_IN_Grp[1] = {GRP_SUPPORT_ASSEMBLY_INBOARD_SPDS};
	MGROUP_ROTATE* SUPPORT_IN_1 = new MGROUP_ROTATE( mesh_idx_SPDS[0], SUPPORT_IN_Grp, 1, SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS, SUPPORT_ASSEMBLY_AXIS_DIR, SUPPORT_ASSEMBLY_ANGLE );
	MGROUP_ROTATE* SUPPORT_IN_2 = new MGROUP_ROTATE( mesh_idx_SPDS[1], SUPPORT_IN_Grp, 1, SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS, SUPPORT_ASSEMBLY_AXIS_DIR, SUPPORT_ASSEMBLY_ANGLE );
	static UINT SUPPORT_OUT_Grp[1] = {GRP_SUPPORT_ASSEMBLY_OUTBOARD_SPDS};
	MGROUP_ROTATE* SUPPORT_OUT_1 = new MGROUP_ROTATE( mesh_idx_SPDS[0], SUPPORT_OUT_Grp, 1, SUPPORT_ASSEMBLY_OUTBOARD_BOTTOM_AXIS_POS, SUPPORT_ASSEMBLY_AXIS_DIR, SUPPORT_ASSEMBLY_ANGLE );
	MGROUP_ROTATE* SUPPORT_OUT_2 = new MGROUP_ROTATE( mesh_idx_SPDS[1], SUPPORT_OUT_Grp, 1, SUPPORT_ASSEMBLY_OUTBOARD_BOTTOM_AXIS_POS, SUPPORT_ASSEMBLY_AXIS_DIR, SUPPORT_ASSEMBLY_ANGLE );
	anim_Yo = STS()->CreateAnimation( Yo_POS_INBD );
	ANIMATIONCOMPONENT_HANDLE parent_1 = STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, SUPPORT_IN_1 );
	ANIMATIONCOMPONENT_HANDLE parent_2 = STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, SUPPORT_IN_2 );
	STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, SUPPORT_OUT_1 );
	STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, SUPPORT_OUT_2 );
	SaveAnimation( SUPPORT_IN_1 );
	SaveAnimation( SUPPORT_IN_2 );
	SaveAnimation( SUPPORT_OUT_1 );
	SaveAnimation( SUPPORT_OUT_2 );

	static UINT SUPPORT_TOP_Grp[1] = {GRP_ZO_BASE_STRUCTURE_SPDS};
	MGROUP_ROTATE* SUPPORT_TOP_1 = new MGROUP_ROTATE( mesh_idx_SPDS[0], SUPPORT_TOP_Grp, 1, SUPPORT_ASSEMBLY_INBOARD_TOP_AXIS_POS, -SUPPORT_ASSEMBLY_AXIS_DIR, SUPPORT_ASSEMBLY_ANGLE );
	MGROUP_ROTATE* SUPPORT_TOP_2 = new MGROUP_ROTATE( mesh_idx_SPDS[1], SUPPORT_TOP_Grp, 1, SUPPORT_ASSEMBLY_INBOARD_TOP_AXIS_POS, -SUPPORT_ASSEMBLY_AXIS_DIR, SUPPORT_ASSEMBLY_ANGLE );
	parent_1 = STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, SUPPORT_TOP_1, parent_1 );
	parent_2 = STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, SUPPORT_TOP_2, parent_2 );
	SaveAnimation( SUPPORT_TOP_1 );
	SaveAnimation( SUPPORT_TOP_2 );

	// Zo motion
	static UINT ZoSPRING_Grp[1] = {GRP_ZO_SPRINGS_SPDS};
	MGROUP_SCALE* ZoSPRING_1 = new MGROUP_SCALE( mesh_idx_SPDS[0], ZoSPRING_Grp, 1, Zo_SPRING_BASE, Zo_SPRING_SCALE );
	MGROUP_SCALE* ZoSPRING_2 = new MGROUP_SCALE( mesh_idx_SPDS[1], ZoSPRING_Grp, 1, Zo_SPRING_BASE, Zo_SPRING_SCALE );
	static UINT ZoTRANS_Grp[14] = {GRP_ZO_ELEVATOR_SPDS, GRP_DEPLOY_SWITCH_SPDS, GRP_DAMPER_SPDS, GRP_ROTARY_ACTUATOR_PYRO_CARTRIDGE_SPDS, GRP_THRUSTER_SPDS, GRP_HEAD_AXIS_SPDS, GRP_ZO_INDICATION_SWITCH_SPDS,
		GRP_COUPLE_TRANSFER_SWITCH_SPDS, GRP_PAYLOAD_ROTARY_ACTUATOR_DRIVE_SPDS, GRP_PAYLOAD_ROTARY_ACTUATOR_DRIVE_MOTORS_SPDS, GRP_STOW_AND_REBIRTH_SWITCH_ASSEMBLY_SPDS, GRP_ROLLER_BEARINGS_SPDS,
		GRP_SUPPORT_ASSEMBLY_CABLES_SPDS, GRP_SUPPORT_ASSEMBLY_CABLE_BRACKETS_SPDS};
	MGROUP_TRANSLATE* ZoTRANS_1 = new MGROUP_TRANSLATE( mesh_idx_SPDS[0], ZoTRANS_Grp, 14, Zo_TRANSLATION );
	MGROUP_TRANSLATE* ZoTRANS_2 = new MGROUP_TRANSLATE( mesh_idx_SPDS[1], ZoTRANS_Grp, 14, Zo_TRANSLATION );
	anim_Zo = STS()->CreateAnimation( 1.0 );
	STS()->AddAnimationComponent( anim_Zo, 0.0, 1.0, ZoSPRING_1, parent_1 );
	STS()->AddAnimationComponent( anim_Zo, 0.0, 1.0, ZoSPRING_2, parent_2 );
	parent_1 = STS()->AddAnimationComponent( anim_Zo, 0.0, 1.0, ZoTRANS_1, parent_1 );
	parent_2 = STS()->AddAnimationComponent( anim_Zo, 0.0, 1.0, ZoTRANS_2, parent_2 );
	SaveAnimation( ZoSPRING_1 );
	SaveAnimation( ZoSPRING_2 );
	SaveAnimation( ZoTRANS_1 );
	SaveAnimation( ZoTRANS_2 );

	// RDU motion
	static UINT RDU_GRP[7] = {GRP_RELEASE_HEAD_SPDS, GRP_SEPARATION_PYRO_CARTRIDGE_SPDS, GRP_RETRACTOR_SPDS, GRP_DISCONNECT_ASSEMBLY_SPDS, GRP_PAYLOAD_SEPARATION_SWITCH_SPDS,
		GRP_RELEASE_HEAD_CABLES_SPDS, GRP_RELEASE_HEAD_CABLE_BRACKETS_SPDS};
	MGROUP_ROTATE* RDU_1 = new MGROUP_ROTATE( mesh_idx_SPDS[0], RDU_GRP, 7, RDU_POS, RDU_AXIS, RDU_RANGE );
	MGROUP_ROTATE* RDU_2 = new MGROUP_ROTATE( mesh_idx_SPDS[1], RDU_GRP, 7, RDU_POS, RDU_AXIS, RDU_RANGE );
	anim_RDU[0] = STS()->CreateAnimation( RDU_POS_STOW );
	anim_RDU[1] = STS()->CreateAnimation( RDU_POS_STOW );
	parent_1 = STS()->AddAnimationComponent( anim_RDU[0], 0.0, 1.0, RDU_1, parent_1 );
	parent_2 = STS()->AddAnimationComponent( anim_RDU[1], 0.0, 1.0, RDU_2, parent_2 );
	SaveAnimation( RDU_1 );
	SaveAnimation( RDU_2 );

	// separation piston
	static UINT EJECTION_PISTON_Grp[1] = {GRP_EJECTION_PISTON_SPDS};
	MGROUP_TRANSLATE* EJECTION_PISTON_1 = new MGROUP_TRANSLATE( mesh_idx_SPDS[0], EJECTION_PISTON_Grp, 1, EJECTION_PISTON_TRANSLATION );
	MGROUP_TRANSLATE* EJECTION_PISTON_2 = new MGROUP_TRANSLATE( mesh_idx_SPDS[1], EJECTION_PISTON_Grp, 1, EJECTION_PISTON_TRANSLATION );
	anim_EjectionPiston = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_EjectionPiston, 0.0, 1.0, EJECTION_PISTON_1, parent_1 );
	STS()->AddAnimationComponent( anim_EjectionPiston, 0.0, 1.0, EJECTION_PISTON_2, parent_2 );
	SaveAnimation( EJECTION_PISTON_1 );
	SaveAnimation( EJECTION_PISTON_2 );
	return;
}

void SPDS::LoadLatches( void )
{
	UINT mesh_idx;
	ANIMATIONCOMPONENT_HANDLE parent = NULL;

	// port longeron
	for (int j = 0; j < 2; j++)
	{
		if (spds.PLID[j] != 0)
		{
			// find PRLA Xo position
			double Xo = PLID_Xo[spds.PLID[j] - PLID_Xo_base];
			if (Xo > 0.0)
			{
				// convert to z position
				VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

				// add PRLA mesh instance
				mesh_idx = STS()->AddMesh( spds.Reversed[j] ? MESHNAME_PRLA_STBD_ACTIVE : MESHNAME_PRLA_PORT_ACTIVE, &pos );
				STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

				// add PRLA animation (for positioning)
				ANIMATIONCOMPONENT_HANDLE parent = NULL;
				if (spds.Reversed[j])
				{
					static UINT PRLA_Grp = {1};
					MGROUP_ROTATE* PRLA = new MGROUP_ROTATE( mesh_idx, &PRLA_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
					UINT animPRLA = STS()->CreateAnimation( 0.0 );
					STS()->SetAnimation( animPRLA, 1.0 );
					parent = STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA );
					SaveAnimation( PRLA );
				}

				// add PRLA hook animation
				static UINT Hook_Grp = {0};
				MGROUP_ROTATE* PRLAHook = new MGROUP_ROTATE( mesh_idx, &Hook_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
				anim_Latch[j] = STS()->CreateAnimation( 0.0 );// closed position
				STS()->SetAnimation( anim_Latch[j], LatchState[j] );// loaded position from scenario
				STS()->AddAnimationComponent( anim_Latch[j], 0.0, 1.0, PRLAHook, parent );
				SaveAnimation( PRLAHook );

				// set attachment location
				if (spds.IsAttachment[j])
					attachpos = ACTIVE_PORT_POS + pos;
			}
			else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: %d", spds.PLID[j], j );
		}
	}

	// starboard longeron
	for (int j = 2; j < 4; j++)
	{
		if (spds.PLID[j] != 0)
		{
			// find PRLA Xo position
			double Xo = PLID_Xo[spds.PLID[j] - PLID_Xo_base];
			if (Xo > 0.0)
			{
				// convert to z position
				VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

				// add PRLA mesh instance
				mesh_idx = STS()->AddMesh( spds.Reversed[j] ? MESHNAME_PRLA_PORT_ACTIVE : MESHNAME_PRLA_STBD_ACTIVE, &pos );
				STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

				// add PRLA animation (for positioning)
				ANIMATIONCOMPONENT_HANDLE parent = NULL;
				if (spds.Reversed[j])
				{
					static UINT PRLA_Grp = {1};
					MGROUP_ROTATE* PRLA = new MGROUP_ROTATE( mesh_idx, &PRLA_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
					UINT animPRLA = STS()->CreateAnimation( 0.0 );
					STS()->SetAnimation( animPRLA, 1.0 );
					parent = STS()->AddAnimationComponent( animPRLA, 0.0, 1.0, PRLA );
					SaveAnimation( PRLA );
				}

				// add PRLA hook animation
				static UINT Hook_Grp = {0};
				MGROUP_ROTATE* PRLAHook = new MGROUP_ROTATE( mesh_idx, &Hook_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
				anim_Latch[j] = STS()->CreateAnimation( 0.0 );// closed position
				STS()->SetAnimation( anim_Latch[j], LatchState[j] );// loaded position from scenario
				STS()->AddAnimationComponent( anim_Latch[j], 0.0, 1.0, PRLAHook, parent );
				SaveAnimation( PRLAHook );

				// set attachment location
				if (spds.IsAttachment[j])
					attachpos = ACTIVE_STBD_POS + pos;
			}
			else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: %d", spds.PLID[j], j );
		}
	}

	// keel
	{
		// find PRLA Xo position
		double Xo = PLID_Xo[spds.PLID[4] - PLID_Xo_base];
		if (Xo > 0.0)
		{
			// convert to z position
			VECTOR3 pos = _V( 0.0, 0.0, 24.239 - (Xo * IN2M) );

			// handle bay 12 vertical offset
			VECTOR3 posmesh = _V( 0.0, (Xo < 1191.0) ? 0.0 : (ACTIVE_CL_AFT_POS.y - ACTIVE_CL_FWD_POS.y), pos.z );

			// mesh instance
			bool fwd = PLID_AKA_FWD[spds.PLID[4] - PLID_Xo_base];
			mesh_idx = STS()->AddMesh( fwd ? MESHNAME_AKA_FWD : MESHNAME_AKA_AFT, &posmesh );
			STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

			// add animation
			bool onesided = PLID_AKA_onesided[spds.PLID[4] - PLID_Xo_base];
			static UINT AKADynamic_Grp = {0};
			static UINT AKAStatic_Grp = {1};
			MGROUP_TRANSLATE* AKADynamic = new MGROUP_TRANSLATE( mesh_idx, &AKADynamic_Grp, 1, (fwd ? AKA_FWD_DYNAMIC_LATCH_OPEN_TRANSLATION : AKA_AFT_DYNAMIC_LATCH_OPEN_TRANSLATION) * (onesided ? 2.0 : 1.0) );
			MGROUP_TRANSLATE* AKAStatic = new MGROUP_TRANSLATE( mesh_idx, &AKAStatic_Grp, 1, (fwd ? AKA_FWD_STATIC_LATCH_OPEN_TRANSLATION : AKA_AFT_STATIC_LATCH_OPEN_TRANSLATION) * (onesided ? 0.0 : 1.0) );
			anim_Latch[4] = STS()->CreateAnimation( 0.0 );// closed position
			STS()->SetAnimation( anim_Latch[4], LatchState[4] );// loaded position from scenario
			STS()->AddAnimationComponent( anim_Latch[4], 0.0, 1.0, AKADynamic );
			STS()->AddAnimationComponent( anim_Latch[4], 0.0, 1.0, AKAStatic );
			SaveAnimation( AKADynamic );
			SaveAnimation( AKAStatic );

			// set attachment location
			if (spds.IsAttachment[4])
				attachpos = ((Xo < 1191.0) ? ACTIVE_CL_FWD_POS : ACTIVE_CL_AFT_POS) + pos;
		}
		else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: 4", spds.PLID[4] );
	}
	return;
}

void SPDS::CreateAttachment( void )
{
	if (!hAttach) hAttach = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + attachpos + MESH_OFFSET, ACTIVE_DIR, ACTIVE_ROT, "SPDS" );
	return;
}

void SPDS::UpdateAttachment( void )
{
	if (hAttach)
	{
		// Yo
		MATRIX3 mrot = rotm( SUPPORT_ASSEMBLY_AXIS_DIR, (motorYo * SUPPORT_ASSEMBLY_ANGLE) - (Yo_RESTOW * RAD) );
		VECTOR3 posPL = mul( mrot, attachpos - SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS ) + SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS;
		VECTOR3 postop = mul( mrot, SUPPORT_ASSEMBLY_INBOARD_TOP_AXIS_POS - SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS ) + SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS;
		VECTOR3 posrdu = mul( mrot, RDU_POS - SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS ) + SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS;

		mrot = rotm( -SUPPORT_ASSEMBLY_AXIS_DIR, (motorYo * SUPPORT_ASSEMBLY_ANGLE) - (Yo_RESTOW * RAD) );
		posPL = mul( mrot, posPL - postop ) + postop;
		posrdu = mul( mrot, posrdu - postop ) + postop;

		// Zo
		posPL += (Zo_TRANSLATION * posZo);

		// RDU
		mrot = rotm( RDU_AXIS, (motorRDU[0] * RDU_RANGE) + RDU_MIN );// both RDUs should be in sync
		posPL = mul( mrot, posPL - posrdu ) + posrdu;
		VECTOR3 dirPL = mul( mrot, ACTIVE_DIR );
		VECTOR3 rotPL = mul( mrot, ACTIVE_ROT );

		STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + posPL + MESH_OFFSET, dirPL, rotPL );
	}
	return;
}

void SPDS::SetIndications( void )
{
	// Yo
	if (motorYo == 0.0)// berth
	{
		PRI_Yo_SYS_A_BERTH.SetLine();
		PRI_Yo_SYS_B_BERTH.SetLine();
		PRI_Yo_SYS_A_INBD.ResetLine();
		PRI_Yo_SYS_B_INBD.ResetLine();
		PRI_Yo_SYS_A_OUTBD.ResetLine();
		PRI_Yo_SYS_B_OUTBD.ResetLine();
		if (PL3_5_IND_A) SEC_Yo_SYS_A_BERTH.SetLine();
		else SEC_Yo_SYS_A_BERTH.ResetLine();
		if (PL3_5_IND_B) SEC_Yo_SYS_B_BERTH.SetLine();
		else SEC_Yo_SYS_B_BERTH.ResetLine();
		SEC_Yo_SYS_A_INBD.ResetLine();
		SEC_Yo_SYS_B_INBD.ResetLine();
		SEC_Yo_SYS_A_OUTBD.ResetLine();
		SEC_Yo_SYS_B_OUTBD.ResetLine();
	}
	else if (motorYo == 1.0)// outboard
	{
		PRI_Yo_SYS_A_BERTH.ResetLine();
		PRI_Yo_SYS_B_BERTH.ResetLine();
		PRI_Yo_SYS_A_INBD.ResetLine();
		PRI_Yo_SYS_B_INBD.ResetLine();
		PRI_Yo_SYS_A_OUTBD.SetLine();
		PRI_Yo_SYS_B_OUTBD.SetLine();
		SEC_Yo_SYS_A_BERTH.ResetLine();
		SEC_Yo_SYS_B_BERTH.ResetLine();
		SEC_Yo_SYS_A_INBD.ResetLine();
		SEC_Yo_SYS_B_INBD.ResetLine();
		if (PL3_5_IND_A) SEC_Yo_SYS_A_OUTBD.SetLine();
		else SEC_Yo_SYS_A_OUTBD.ResetLine();
		if (PL3_5_IND_B) SEC_Yo_SYS_B_OUTBD.SetLine();
		else SEC_Yo_SYS_B_OUTBD.ResetLine();
	}
	else if (fabs( motorYo - Yo_POS_INBD ) <= Yo_POS_MARGIN)// inboard
	{
		PRI_Yo_SYS_A_BERTH.ResetLine();
		PRI_Yo_SYS_B_BERTH.ResetLine();
		PRI_Yo_SYS_A_INBD.SetLine();
		PRI_Yo_SYS_B_INBD.SetLine();
		PRI_Yo_SYS_A_OUTBD.ResetLine();
		PRI_Yo_SYS_B_OUTBD.ResetLine();
		SEC_Yo_SYS_A_BERTH.ResetLine();
		SEC_Yo_SYS_B_BERTH.ResetLine();
		if (PL3_5_IND_A) SEC_Yo_SYS_A_INBD.SetLine();
		else SEC_Yo_SYS_A_INBD.ResetLine();
		if (PL3_5_IND_B) SEC_Yo_SYS_B_INBD.SetLine();
		else SEC_Yo_SYS_B_INBD.ResetLine();
		SEC_Yo_SYS_A_OUTBD.ResetLine();
		SEC_Yo_SYS_B_OUTBD.ResetLine();
	}
	else
	{
		PRI_Yo_SYS_A_BERTH.ResetLine();
		PRI_Yo_SYS_B_BERTH.ResetLine();
		PRI_Yo_SYS_A_INBD.ResetLine();
		PRI_Yo_SYS_B_INBD.ResetLine();
		PRI_Yo_SYS_A_OUTBD.ResetLine();
		PRI_Yo_SYS_B_OUTBD.ResetLine();
		SEC_Yo_SYS_A_BERTH.ResetLine();
		SEC_Yo_SYS_B_BERTH.ResetLine();
		SEC_Yo_SYS_A_INBD.ResetLine();
		SEC_Yo_SYS_B_INBD.ResetLine();
		SEC_Yo_SYS_A_OUTBD.ResetLine();
		SEC_Yo_SYS_B_OUTBD.ResetLine();
	}

	// Zo
	if (posZo == 1.0)
	{
		PRI_Zo_SYS_A_EXTEND.SetLine();
		PRI_Zo_SYS_B_EXTEND.SetLine();
		SEC_Zo_SYS_A_EXTEND.SetLine();
		SEC_Zo_SYS_B_EXTEND.SetLine();
	}
	else
	{
		PRI_Zo_SYS_A_EXTEND.ResetLine();
		PRI_Zo_SYS_B_EXTEND.ResetLine();
		SEC_Zo_SYS_A_EXTEND.ResetLine();
		SEC_Zo_SYS_B_EXTEND.ResetLine();
	}

	// primary RDU
	if (motorRDU[0] == 0.0)// reberth
	{
		if (PL2_2_IND_A || PL3_3_IND_A) PRI_RDU_SYS_A_REBERTH.SetLine();
		else PRI_RDU_SYS_A_REBERTH.ResetLine();
		if (PL2_2_IND_B || PL3_3_IND_B) PRI_RDU_SYS_B_REBERTH.SetLine();
		else PRI_RDU_SYS_B_REBERTH.ResetLine();
		PRI_RDU_SYS_A_STOW.ResetLine();
		PRI_RDU_SYS_B_STOW.ResetLine();
		PRI_RDU_SYS_A_DEPLOY.ResetLine();
		PRI_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else if (motorRDU[0] == 1.0)// deploy
	{
		PRI_RDU_SYS_A_REBERTH.ResetLine();
		PRI_RDU_SYS_B_REBERTH.ResetLine();
		PRI_RDU_SYS_A_STOW.ResetLine();
		PRI_RDU_SYS_B_STOW.ResetLine();
		if (PL2_2_IND_A || PL3_3_IND_A) PRI_RDU_SYS_A_DEPLOY.SetLine();
		else PRI_RDU_SYS_A_DEPLOY.ResetLine();
		if (PL2_2_IND_B || PL3_3_IND_B) PRI_RDU_SYS_B_DEPLOY.SetLine();
		else PRI_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else if (fabs( motorRDU[0] - RDU_POS_STOW ) <= RDU_POS_MARGIN)// stow
	{
		PRI_RDU_SYS_A_REBERTH.ResetLine();
		PRI_RDU_SYS_B_REBERTH.ResetLine();
		if (PL2_2_IND_A || PL3_3_IND_A) PRI_RDU_SYS_A_STOW.SetLine();
		else PRI_RDU_SYS_A_STOW.ResetLine();
		if (PL2_2_IND_B || PL3_3_IND_B) PRI_RDU_SYS_B_STOW.SetLine();
		else PRI_RDU_SYS_B_STOW.ResetLine();
		PRI_RDU_SYS_A_DEPLOY.ResetLine();
		PRI_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else
	{
		PRI_RDU_SYS_A_REBERTH.ResetLine();
		PRI_RDU_SYS_B_REBERTH.ResetLine();
		PRI_RDU_SYS_A_STOW.ResetLine();
		PRI_RDU_SYS_B_STOW.ResetLine();
		PRI_RDU_SYS_A_DEPLOY.ResetLine();
		PRI_RDU_SYS_B_DEPLOY.ResetLine();
	}

	// secondary RDU
	if (motorRDU[1] == 0.0)// reberth
	{
		if (PL3_3_IND_A) SEC_RDU_SYS_A_REBERTH.SetLine();
		else SEC_RDU_SYS_A_REBERTH.ResetLine();
		if (PL3_3_IND_B) SEC_RDU_SYS_B_REBERTH.SetLine();
		else SEC_RDU_SYS_B_REBERTH.ResetLine();
		SEC_RDU_SYS_A_STOW.ResetLine();
		SEC_RDU_SYS_B_STOW.ResetLine();
		SEC_RDU_SYS_A_DEPLOY.ResetLine();
		SEC_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else if (motorRDU[1] == 1.0)// deploy
	{
		SEC_RDU_SYS_A_REBERTH.ResetLine();
		SEC_RDU_SYS_B_REBERTH.ResetLine();
		SEC_RDU_SYS_A_STOW.ResetLine();
		SEC_RDU_SYS_B_STOW.ResetLine();
		if (PL3_3_IND_A) SEC_RDU_SYS_A_DEPLOY.SetLine();
		else SEC_RDU_SYS_A_DEPLOY.ResetLine();
		if (PL3_3_IND_B) SEC_RDU_SYS_B_DEPLOY.SetLine();
		else SEC_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else if (fabs( motorRDU[1] - RDU_POS_STOW ) <= RDU_POS_MARGIN)// stow
	{
		SEC_RDU_SYS_A_REBERTH.ResetLine();
		SEC_RDU_SYS_B_REBERTH.ResetLine();
		if (PL3_3_IND_A) SEC_RDU_SYS_A_STOW.SetLine();
		else SEC_RDU_SYS_A_STOW.ResetLine();
		if (PL3_3_IND_B) SEC_RDU_SYS_B_STOW.SetLine();
		else SEC_RDU_SYS_B_STOW.ResetLine();
		SEC_RDU_SYS_A_DEPLOY.ResetLine();
		SEC_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else
	{
		SEC_RDU_SYS_A_REBERTH.ResetLine();
		SEC_RDU_SYS_B_REBERTH.ResetLine();
		SEC_RDU_SYS_A_STOW.ResetLine();
		SEC_RDU_SYS_B_STOW.ResetLine();
		SEC_RDU_SYS_A_DEPLOY.ResetLine();
		SEC_RDU_SYS_B_DEPLOY.ResetLine();
	}

	// RDU pedestal drive
	if (RDU_PRI_PED_ENGAGED)
	{
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_DIS.ResetLine();
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_ENG.SetLine();
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_DIS.ResetLine();
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_ENG.SetLine();
	}
	else
	{
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_DIS.SetLine();
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_ENG.ResetLine();
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_DIS.SetLine();
		PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_ENG.ResetLine();
	}
	if (RDU_SEC_PED_ENGAGED)
	{
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_DIS.ResetLine();
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_ENG.SetLine();
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_DIS.ResetLine();
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_ENG.SetLine();
	}
	else
	{
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_DIS.SetLine();
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_ENG.ResetLine();
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_DIS.SetLine();
		PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_ENG.ResetLine();
	}

	// payload release
	if (posEjectionPiston)
	{
		PAYLOAD_RELEASE_PRI_PED_SYS_A_LAT.ResetLine();
		PAYLOAD_RELEASE_PRI_PED_SYS_A_REL.SetLine();
		PAYLOAD_RELEASE_PRI_PED_SYS_B_LAT.ResetLine();
		PAYLOAD_RELEASE_PRI_PED_SYS_B_REL.SetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_A_LAT.ResetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_A_REL.SetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_B_LAT.ResetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_B_REL.SetLine();
	}
	else
	{
		PAYLOAD_RELEASE_PRI_PED_SYS_A_LAT.SetLine();
		PAYLOAD_RELEASE_PRI_PED_SYS_A_REL.ResetLine();
		PAYLOAD_RELEASE_PRI_PED_SYS_B_LAT.SetLine();
		PAYLOAD_RELEASE_PRI_PED_SYS_B_REL.ResetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_A_LAT.SetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_A_REL.ResetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_B_LAT.SetLine();
		PAYLOAD_RELEASE_SEC_PED_SYS_B_REL.ResetLine();
	}
	return;
}

void SPDS::SetAnimations( void )
{
	STS()->SetAnimation( anim_Zo, posZo );
	STS()->SetAnimation( anim_Yo, motorYo );
	STS()->SetAnimation( anim_RDU[0], motorRDU[0] );
	STS()->SetAnimation( anim_RDU[1], motorRDU[1] );
	STS()->SetAnimation( anim_EjectionPiston, posEjectionPiston );
	return;
}

int SPDS::MotorPower3( double a, double b, double c ) const
{
	bool op = (a > 0.0) || (b > 0.0) || (c > 0.0);
	bool cl = (a < 0.0) || (b < 0.0) || (c < 0.0);

	if (op == cl) return 0;
	else if (op) return 1;
	else /*if (cl)*/ return -1;
}

int SPDS::MotorPower2( double a, double b ) const
{
	return MotorPower3( a, b, 0.0 );
}

void SPDS::OnPreStep( double simt, double simdt, double mjd )
{
	// RDU pedestal drive select
	if ((PEDESTAL_DRIVE_XFER_SYS_A_ARM && PEDESTAL_DRIVE_XFER_SYS_A_FIRE) || (PEDESTAL_DRIVE_XFER_SYS_B_ARM && PEDESTAL_DRIVE_XFER_SYS_B_FIRE))
	{
		RDU_PRI_PED_ENGAGED = false;
		RDU_SEC_PED_ENGAGED = true;
	}

	// Yo motor
	int yo_pwr_a = MotorPower3( Yo_MOTOR_A_MMC4_OUTBD_INBD.GetVoltage(), Yo_MOTOR_A_MMC1_OUTBD_INBD.GetVoltage(), Yo_MOTOR_A_MMC1_OUTBD_BERTH.GetVoltage() );
	int yo_pwr_b = MotorPower3( Yo_MOTOR_B_MMC2_OUTBD_INBD.GetVoltage(), Yo_MOTOR_B_MMC3_OUTBD_INBD.GetVoltage(), Yo_MOTOR_B_MMC3_OUTBD_BERTH.GetVoltage() );
	motorYo = range( 0.0, motorYo + (simdt * Yo_MOTOR_SPEED * (yo_pwr_a + yo_pwr_b)), 1.0 );

	// Zo
	if ((LatchState[0] + LatchState[1] + LatchState[2] + LatchState[3] + LatchState[4]) > 4.95)
	{
		unlockZo = true;
	}
	if (unlockZo)
	{
		posZo = min(posZo + (simdt * Zo_SPEED), 1.0);
	}

	// RDU motor
	int rdu_pri_pwr_a = MotorPower3( PRI_RDU_MOTOR_A_MMC4_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_A_MMC1_DPY_REBERTH.GetVoltage(), PRI_RDU_MOTOR_A_MMC1_DPY_STO.GetVoltage() );
	int rdu_pri_pwr_b = MotorPower3( PRI_RDU_MOTOR_B_MMC2_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_B_MMC3_DPY_REBERTH.GetVoltage(), PRI_RDU_MOTOR_B_MMC3_DPY_STO.GetVoltage() );
	int rdu_sec_pwr_a = MotorPower2( SEC_RDU_MOTOR_A_MMC1_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_A_MMC1_DPY_STO.GetVoltage() );
	int rdu_sec_pwr_b = MotorPower2( SEC_RDU_MOTOR_B_MMC3_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_B_MMC3_DPY_STO.GetVoltage() );
	if (RDU_PRI_PED_ENGAGED)
	{
		if (RDU_SEC_PED_ENGAGED)
		{
			// primary and secondary pedestals
			if (PAYLOAD_RELEASED == false)
			{
				// together
				motorRDU[0] = range( 0.0, motorRDU[0] + (simdt * RDU_MOTOR_SPEED * (rdu_pri_pwr_a + rdu_pri_pwr_b + rdu_sec_pwr_a + rdu_sec_pwr_b)), 1.0 );
				motorRDU[1] = motorRDU[0];
			}
			else
			{
				// separate
				motorRDU[0] = range( 0.0, motorRDU[0] + (simdt * RDU_MOTOR_SPEED * (rdu_pri_pwr_a + rdu_pri_pwr_b)), 1.0 );
				motorRDU[1] = range( 0.0, motorRDU[1] + (simdt * RDU_MOTOR_SPEED * (rdu_sec_pwr_a + rdu_sec_pwr_b)), 1.0 );
			}
		}
		else
		{
			// primary pedestal only
			motorRDU[0] = range( 0.0, motorRDU[0] + (simdt * RDU_MOTOR_SPEED * (rdu_pri_pwr_a + rdu_pri_pwr_b)), 1.0 );
			// if payload still attached, move secondary pedestal as well
			if (PAYLOAD_RELEASED == false) motorRDU[1] = motorRDU[0];
		}
	}
	else if (RDU_SEC_PED_ENGAGED)
	{
		// secondary pedestal only
		motorRDU[1] = range( 0.0, motorRDU[1] + (simdt * RDU_MOTOR_SPEED * (rdu_sec_pwr_a + rdu_sec_pwr_b)), 1.0 );
		// if payload still attached, move primary pedestal as well
		if (PAYLOAD_RELEASED == false) motorRDU[0] = motorRDU[1];
	}

	// payload release
	if ((PAYLOAD_RELEASED == false) && ((PAYLOAD_RELEASE_SYS_A_ARM && PAYLOAD_RELEASE_SYS_A_FIRE) || (PAYLOAD_RELEASE_SYS_B_ARM && PAYLOAD_RELEASE_SYS_B_FIRE)))
	{
		PAYLOAD_RELEASED = true;
		if (hAttach) STS()->DetachChild( hAttach, PL_SEP_SPEED );
	}

	// separation piston
	if (PAYLOAD_RELEASED)
	{
		posEjectionPiston = min(posEjectionPiston + (simdt * EJECTION_PISTON_SPEED), 1.0);
	}

	SetIndications();
	SetAnimations();

	// run latches
	for (unsigned short i = 0; i < 5; i++)
	{
		LatchState[i] = range( 0.0, LatchState[i] + (simdt * PL_LATCH_RATE * (LatchMOTOR_1_PWR[i].GetVoltage() + LatchMOTOR_2_PWR[i].GetVoltage())), 1.0 );

		// animation
		STS()->SetAnimation( anim_Latch[i], LatchState[i] );

		// indications
		bool rdy = true;// TODO

		if (LatchIND_A[i])
		{
			if (LatchState[i] == 0.0)
			{
				LatchLAT_A[i].SetLine();
				LatchREL_A[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LatchLAT_A[i].ResetLine();
				LatchREL_A[i].SetLine();
			}
			else
			{
				LatchLAT_A[i].ResetLine();
				LatchREL_A[i].ResetLine();
			}

			if (rdy) LatchRDY_A[i].SetLine();
			else LatchRDY_A[i].ResetLine();
		}
		else
		{
			LatchLAT_A[i].ResetLine();
			LatchREL_A[i].ResetLine();
			LatchRDY_A[i].ResetLine();
		}

		if (LatchIND_B[i])
		{
			if (LatchState[i] == 0.0)
			{
				LatchLAT_B[i].SetLine();
				LatchREL_B[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LatchLAT_B[i].ResetLine();
				LatchREL_B[i].SetLine();
			}
			else
			{
				LatchLAT_B[i].ResetLine();
				LatchREL_B[i].ResetLine();
			}

			if (rdy) LatchRDY_B[i].SetLine();
			else LatchRDY_B[i].ResetLine();
		}
		else
		{
			LatchLAT_B[i].ResetLine();
			LatchREL_B[i].ResetLine();
			LatchRDY_B[i].ResetLine();
		}
	}

	if (1)// TODO test motion
	{
		UpdateAttachment();
	}
	return;
}

bool SPDS::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "RDU_PRI_PED_ENGAGED", 19 ))
	{
		int tmp = 0;
		sscanf_s( (char*)(line + 19), "%d", &tmp );
		RDU_PRI_PED_ENGAGED = (tmp == 1);
		return true;
	}
	else if (!_strnicmp( line, "RDU_SEC_PED_ENGAGED", 19 ))
	{
		int tmp = 0;
		sscanf_s( (char*)(line + 19), "%d", &tmp );
		RDU_SEC_PED_ENGAGED = (tmp == 1);
		return true;
	}
	else if (!_strnicmp( line, "Yo", 2 ))
	{
		sscanf_s( (char*)(line + 2), "%lf", &motorYo );
		motorYo = range( 0.0, motorYo, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "Zo", 2 ))
	{
		sscanf_s( (char*)(line + 2), "%lf", &posZo );
		posZo = range( 0.0, posZo, 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "RDU", 3 ))
	{
		sscanf_s( (char*)(line + 3), "%lf %lf", &motorRDU[0], &motorRDU[1] );
		motorRDU[0] = range( 0.0, motorRDU[0], 1.0 );
		motorRDU[1] = range( 0.0, motorRDU[1], 1.0 );
		return true;
	}
	else if (!_strnicmp( line, "LATCHES", 7 ))
	{
		sscanf_s( line + 7, "%lf %lf %lf %lf %lf", &LatchState[0], &LatchState[1], &LatchState[2], &LatchState[3], &LatchState[4] );
		return true;
	}
	return false;
}

void SPDS::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_int( scn, "RDU_PRI_PED_ENGAGED", RDU_PRI_PED_ENGAGED );
	oapiWriteScenario_int( scn, "RDU_SEC_PED_ENGAGED", RDU_SEC_PED_ENGAGED );
	oapiWriteScenario_float( scn, "Yo", motorYo );
	oapiWriteScenario_float( scn, "Zo", posZo );

	char cbuf[64];
	sprintf_s( cbuf, 64, "%lf %lf", motorRDU[0], motorRDU[1] );
	oapiWriteScenario_string( scn, "RDU", cbuf );

	sprintf_s( cbuf, 64, "%lf %lf %lf %lf %lf", LatchState[0], LatchState[1], LatchState[2], LatchState[3], LatchState[4] );
	oapiWriteScenario_string( scn, "LATCHES", cbuf );
	return;
}
