#include "SPDS.h"
#include "../CommonDefs.h"
#include "Atlantis.h"
#include <MathSSV.h>
#include <EngConst.h>


const static char* MESHNAME = "SSV\\SPDS_Port";

const VECTOR3 MESH_OFFSET = _V( 0.0, 0.0, 0.0 );

constexpr double MASS = 180.0 * LBM2KG;// [kg]

//const VECTOR3 ATTACHMENT_POS = _V( 2.6618946, 0.480061, 1.09833 );// Xo+911.05, Yo-104.799, Zo+435.715
const VECTOR3 ATTACHMENT_POS = _V( 2.6618946, 0.480061, 0.0 );// rotation point (Yo-97.0, Zo+426.0)
const VECTOR3 ATTACHMENT_DIR = _V( 0.333478, 0.942758, 0.0 );
const VECTOR3 ATTACHMENT_ROT = _V( 0.0, 1.0, 0.0 );


const VECTOR3 Zo_TRANSLATION = _V( 0.0, 2.0, 0.0 ) * IN2M;

constexpr double Yo_MOTOR_SPEED = 0.00625;// single motor time (160.0sec) [1/sec]
constexpr float Yo_RESTOW = static_cast<float>(-2.0 * IN2M);// distance from inboard position to restow position [m]
constexpr float Yo_OUTBD = static_cast<float>(3.0 * IN2M);// distance from inboard position to outboard position [m]
constexpr float Yo_RANGE = Yo_OUTBD - Yo_RESTOW;// full Yo translation range [m]
constexpr float Yo_POS_INBD = (0.0f - Yo_RESTOW) / Yo_RANGE;// Yo animation at inboard position [1]
const VECTOR3 Yo_TRANSLATION = _V( Yo_RANGE, 0.0, 0.0 );

const float RDU_MIN = static_cast<float>(-9.0 * RAD);// angle from stow position to reberth position [rad]
const float RDU_MAX = static_cast<float>(114.0 * RAD);// angle from stow position to deploy position [rad]
const float RDU_RANGE = RDU_MAX - RDU_MIN;// full (powered) RDU rotation range [rad]
const float RDU_POS_STOW = static_cast<float>((0.0 - RDU_MIN) / RDU_RANGE);// RDU animation at stow position [1]
constexpr double RDU_MOTOR_SPEED = 0.00308943;// single motor time (323.684sec) [1/sec]
const VECTOR3 RDU_POS = _V( 0.0, 0.0, 0.0 );// TODO
const VECTOR3 RDU_AXIS = _V( 0.0, 0.0, 1.0 );

SPDS::SPDS( AtlantisSubsystemDirector *_director, const mission::MissionSPDS& spds, bool portside ) : AtlantisSubsystem( _director, "SPDS" ), MPM_Base( true ),
	hAttach(NULL), mesh_index_SPDS(MESH_UNDEFINED), attach_pos(ATTACHMENT_POS), attach_dir(ATTACHMENT_DIR),
	motorYo(0.0), posZo(0.0), motorRDU(0.0), RDU_PRI_PED_ENGAGED(true), RDU_SEC_PED_ENGAGED(false), PAYLOAD_RELEASED(false), spds(spds)
{
	// PRLA pos (5)
	// attach (longeron) PRLA

	hMesh_SPDS = oapiLoadMeshGlobal( MESHNAME );
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

	AddMesh();
	DefineAnimations();
	SetIndications();
	SetAnimations();
	
	// TODO init PAYLOAD_RELEASED
	return;
}

void SPDS::AddMesh( void )
{
	// TODO add SPDS meshes
	VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + MESH_OFFSET;
	mesh_index_SPDS = STS()->AddMesh( hMesh_SPDS, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index_SPDS, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	// TODO add PRLA meshes
	return;
}

void SPDS::DefineAnimations( void )
{
	// SPDS animations
	static UINT ZoTRANS_Grp[1] = {0};// TODO
	MGROUP_TRANSLATE* ZoTRANS = new MGROUP_TRANSLATE( mesh_index_SPDS, ZoTRANS_Grp, 1, Zo_TRANSLATION );
	anim_Zo = STS()->CreateAnimation( 0.0 );
	ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( anim_Zo, 0.0, 1.0, ZoTRANS );
	SaveAnimation( ZoTRANS );

	static UINT YoTRANS_Grp[1] = {0};// TODO
	MGROUP_TRANSLATE* YoTRANS = new MGROUP_TRANSLATE( mesh_index_SPDS, YoTRANS_Grp, 1, Yo_TRANSLATION );
	anim_Yo = STS()->CreateAnimation( Yo_POS_INBD );
	parent = STS()->AddAnimationComponent( anim_Yo, 0.0, 1.0, YoTRANS, parent );
	SaveAnimation( YoTRANS );
	
	static UINT RDU_GRP[1] = {0};// TODO
	MGROUP_ROTATE* RDU = new MGROUP_ROTATE( mesh_index_SPDS, RDU_GRP, 1, RDU_POS, RDU_AXIS, RDU_RANGE );
	anim_RDU = STS()->CreateAnimation( RDU_POS_STOW );
	STS()->AddAnimationComponent( anim_RDU, 0.0, 1.0, RDU, parent );
	SaveAnimation( RDU );

	// TODO PRLA animations
	return;
}

void SPDS::CreateAttachment( void )
{
	if (!hAttach) hAttach = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + ATTACHMENT_POS, ATTACHMENT_DIR, ATTACHMENT_ROT, "SPDS" );
	return;
}

void SPDS::UpdateAttachment( void )
{
	if (hAttach) STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + ATTACHMENT_POS, ATTACHMENT_DIR, ATTACHMENT_ROT );// TODO
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
	else if (fabs( motorYo - Yo_POS_INBD ) <= 0.01)// inboard
	{// TODO margin
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

	// RDU
	if (motorRDU == 0.0)// reberth
	{
		if (PL2_2_IND_A || PL3_3_IND_A) PRI_RDU_SYS_A_REBERTH.SetLine();
		else PRI_RDU_SYS_A_REBERTH.ResetLine();
		if (PL2_2_IND_B || PL3_3_IND_B) PRI_RDU_SYS_B_REBERTH.SetLine();
		else PRI_RDU_SYS_B_REBERTH.ResetLine();
		PRI_RDU_SYS_A_STOW.ResetLine();
		PRI_RDU_SYS_B_STOW.ResetLine();
		PRI_RDU_SYS_A_DEPLOY.ResetLine();
		PRI_RDU_SYS_B_DEPLOY.ResetLine();
		if (PL3_3_IND_A) SEC_RDU_SYS_A_REBERTH.SetLine();
		else SEC_RDU_SYS_A_REBERTH.ResetLine();
		if (PL3_3_IND_B) SEC_RDU_SYS_B_REBERTH.SetLine();
		else SEC_RDU_SYS_B_REBERTH.ResetLine();
		SEC_RDU_SYS_A_STOW.ResetLine();
		SEC_RDU_SYS_B_STOW.ResetLine();
		SEC_RDU_SYS_A_DEPLOY.ResetLine();
		SEC_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else if (motorRDU == 1.0)// deploy
	{
		PRI_RDU_SYS_A_REBERTH.ResetLine();
		PRI_RDU_SYS_B_REBERTH.ResetLine();
		PRI_RDU_SYS_A_STOW.ResetLine();
		PRI_RDU_SYS_B_STOW.ResetLine();
		if (PL2_2_IND_A || PL3_3_IND_A) PRI_RDU_SYS_A_DEPLOY.SetLine();
		else PRI_RDU_SYS_A_DEPLOY.ResetLine();
		if (PL2_2_IND_B || PL3_3_IND_B) PRI_RDU_SYS_B_DEPLOY.SetLine();
		else PRI_RDU_SYS_B_DEPLOY.ResetLine();
		SEC_RDU_SYS_A_REBERTH.ResetLine();
		SEC_RDU_SYS_B_REBERTH.ResetLine();
		SEC_RDU_SYS_A_STOW.ResetLine();
		SEC_RDU_SYS_B_STOW.ResetLine();
		if (PL3_3_IND_A) SEC_RDU_SYS_A_DEPLOY.SetLine();
		else SEC_RDU_SYS_A_DEPLOY.ResetLine();
		if (PL3_3_IND_B) SEC_RDU_SYS_B_DEPLOY.SetLine();
		else SEC_RDU_SYS_B_DEPLOY.ResetLine();
	}
	else if (fabs( motorRDU - RDU_POS_STOW ) <= 0.01)// stow
	{// TODO margin
		PRI_RDU_SYS_A_REBERTH.ResetLine();
		PRI_RDU_SYS_B_REBERTH.ResetLine();
		if (PL2_2_IND_A || PL3_3_IND_A) PRI_RDU_SYS_A_STOW.SetLine();
		else PRI_RDU_SYS_A_STOW.ResetLine();
		if (PL2_2_IND_B || PL3_3_IND_B) PRI_RDU_SYS_B_STOW.SetLine();
		else PRI_RDU_SYS_B_STOW.ResetLine();
		PRI_RDU_SYS_A_DEPLOY.ResetLine();
		PRI_RDU_SYS_B_DEPLOY.ResetLine();
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
		PRI_RDU_SYS_A_REBERTH.ResetLine();
		PRI_RDU_SYS_B_REBERTH.ResetLine();
		PRI_RDU_SYS_A_STOW.ResetLine();
		PRI_RDU_SYS_B_STOW.ResetLine();
		PRI_RDU_SYS_A_DEPLOY.ResetLine();
		PRI_RDU_SYS_B_DEPLOY.ResetLine();
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
	if (PAYLOAD_RELEASED)
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
	STS()->SetAnimation( anim_RDU, motorRDU );
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

void SPDS::OnPostStep( double simt, double simdt, double mjd )
{
	// RDU pedestal drive select
	if ((PEDESTAL_DRIVE_XFER_SYS_A_ARM && PEDESTAL_DRIVE_XFER_SYS_A_FIRE) || (PEDESTAL_DRIVE_XFER_SYS_B_ARM && PEDESTAL_DRIVE_XFER_SYS_B_FIRE))
	{
		RDU_PRI_PED_ENGAGED = false;
		RDU_SEC_PED_ENGAGED = true;
	}

	// Yo motor
	int pwr_a = MotorPower3( Yo_MOTOR_A_MMC4_OUTBD_INBD.GetVoltage(), Yo_MOTOR_A_MMC1_OUTBD_INBD.GetVoltage(), Yo_MOTOR_A_MMC1_OUTBD_BERTH.GetVoltage() );
	int pwr_b = MotorPower3( Yo_MOTOR_B_MMC2_OUTBD_INBD.GetVoltage(), Yo_MOTOR_B_MMC3_OUTBD_INBD.GetVoltage(), Yo_MOTOR_B_MMC3_OUTBD_BERTH.GetVoltage() );
	motorYo = range( 0.0, motorYo + (simdt * Yo_MOTOR_SPEED * (pwr_a + pwr_b)), 1.0 );

	// RDU motor
	if (RDU_PRI_PED_ENGAGED)// primary pedestal
	{
		pwr_a = MotorPower3( PRI_RDU_MOTOR_A_MMC4_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_A_MMC1_DPY_REBERTH.GetVoltage(), PRI_RDU_MOTOR_A_MMC1_DPY_STO.GetVoltage() );
		pwr_b = MotorPower3( PRI_RDU_MOTOR_B_MMC2_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_B_MMC3_DPY_REBERTH.GetVoltage(), PRI_RDU_MOTOR_B_MMC3_DPY_STO.GetVoltage() );
	}
	if (RDU_SEC_PED_ENGAGED)// secondary pedestal
	{
		pwr_a = MotorPower2( SEC_RDU_MOTOR_A_MMC1_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_A_MMC1_DPY_STO.GetVoltage() );
		pwr_b = MotorPower2( SEC_RDU_MOTOR_B_MMC3_DPY_REBERTH.GetVoltage(), SEC_RDU_MOTOR_B_MMC3_DPY_STO.GetVoltage() );
	}
	motorRDU = range( 0.0, motorRDU + (simdt * RDU_MOTOR_SPEED * (pwr_a + pwr_b)), 1.0 );
	
	// payload release
	if ((PAYLOAD_RELEASED == false) && ((PAYLOAD_RELEASE_SYS_A_ARM && PAYLOAD_RELEASE_SYS_A_FIRE) || (PAYLOAD_RELEASE_SYS_B_ARM && PAYLOAD_RELEASE_SYS_B_FIRE)))
	{
		PAYLOAD_RELEASED = true;
		if (hAttach) STS()->DetachChild( hAttach, 0.3 );// TODO rel speed
	}

	SetIndications();
	SetAnimations();
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
	else if (!_strnicmp( line, "RDU", 4 ))
	{
		sscanf_s( (char*)(line + 3), "%lf", &motorRDU );
		motorRDU = range( 0.0, motorRDU, 1.0 );
		return true;
	}
	return false;
}

void SPDS::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_int( scn, "RDU_PRI_PED_ENGAGED", RDU_PRI_PED_ENGAGED );
	oapiWriteScenario_int( scn, "RDU_SEC_PED_ENGAGED", RDU_SEC_PED_ENGAGED );
	oapiWriteScenario_float( scn, "Yo", motorYo );
	oapiWriteScenario_float( scn, "RDU", motorRDU );
	return;
}
