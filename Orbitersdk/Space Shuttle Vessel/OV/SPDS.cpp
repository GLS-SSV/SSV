#include "SPDS.h"
#include "meshres_SPDS.h"
#include "meshres_MPM_Port.h"
#include "../CommonDefs.h"
#include "Atlantis.h"
#include "PRLA_defs.h"
#include <MathSSV.h>
#include <EngConst.h>


const static char* MESHNAME = "SSV\\OV\\SPDS_Port";

const VECTOR3 MESH_OFFSET = _V( 0.0, 0.0, 0.0 );

constexpr double MASS = 180.0 * LBM2KG;// [kg]
const VECTOR3 BASE_CG = _V( -2.4257, 0.0555, 0.0 );// (approx) Yo-95.5 Zo+419.0

const VECTOR3 PORT_ATTACH_POS = _V( -2.276994, 0.1825, 0.0 );// Yo-89.645433, Zo+424.0
const VECTOR3 PORT_ATTACH_DIR = _V( 1.0, 0.0, 0.0 );
const VECTOR3 PORT_ATTACH_ROT = _V( 0.0, 1.0, 0.0 );

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
const VECTOR3 RDU_AXIS_POS = _V( -2.3876, 0.2333, 0.0 );
const VECTOR3 RDU_AXIS_DIR = _V( 0.0, 0.0, 1.0 );
const double RDU_POS_MARGIN = 0.001;

constexpr double EJECTION_PISTON_LENGTH = 1.75 * IN2M;// [m]
const VECTOR3 EJECTION_PISTON_TRANSLATION = _V( EJECTION_PISTON_LENGTH, 0.0, 0.0 );// [m]
constexpr double EJECTION_PISTON_SPEED = PL_SEP_SPEED / EJECTION_PISTON_LENGTH;// [1/s]

const double MPM_TORQUE_TUBE_OFFSET = -0.275;// [m]
const double MPM_TORQUE_TUBE_LENGTH = 0.01;// [m]
const double MPM_TORQUE_TUBE_FWD_END = 6.82236;// [m]

constexpr unsigned int PLID_OFFSET = 5;
constexpr unsigned int PLID_OFFSET_REVERSED = 3;

constexpr double RELEASE_PRLA_LIMIT = 0.75;// PRLA position above which PL is released
constexpr double PRLA_RDY_Zo_LIMIT = 0.5;// Zo position below which PRLA RDY is set


const double TX_Zo = 10.0;// oscillation duration [s]
const double T1_Zo = 4.6;// controls exponential decay (final amplitude = ~1%)
const double T2_Zo = 5.0;// number of oscillations

static double osc( const double TX, const double T1, const double T2, const double t, const double tf )
{
	double tm = ((tf - t) - TX) / TX;
	if (tm < -1.0) return 0.0;

	double e = exp( tm * T1 );
	double o = -((cos( tm * 2 * 3.1415 * T2 ) * 0.5) - 0.5);
	return e * o;
}


SPDS::SPDS( AtlantisSubsystemDirector *_director, const mission::MissionSPDS& spds, bool portside ) : AtlantisSubsystem( _director, "SPDS" ), MPM_Base( true ),
mesh_idx_SPDS{MESH_UNDEFINED, MESH_UNDEFINED}, anim_Zo(0), anim_Yo(0), anim_RDU{0,0}, anim_EjectionPiston(0), hAttach(NULL),  attachpos(ACTIVE_CL_FWD_POS), pedestal_xpos{0.0, 0.0},
motorYo(0.0), posZo(0.0), motorRDU{0.0, 0.0}, posEjectionPiston(0.0), RDU_PRI_PED_ENGAGED(true), RDU_SEC_PED_ENGAGED(false), PAYLOAD_RELEASED(false), unlockZo(false), LatchState{0.0, 0.0, 0.0, 0.0, 0.0},
tfZo(0.0), staticposZo(0.0),
spds(spds)
{
	// average pedestal location for c.g Xo position 
	double XoP = PLID_Xo[spds.PLID[0] - PLID_Xo_base];
	double XoS = PLID_Xo[spds.PLID[1] - PLID_Xo_base];
	CG = BASE_CG + _V( 0.0, 0.0, 24.239 - ((XoP + XoS) * 0.5 * IN2M) );
	return;
}

SPDS::~SPDS( void )
{
	return;
}

void SPDS::Realize( void )
{
	discsignals::DiscreteBundle* pBundle = BundleManager()->CreateBundle( "A7A3_SPDS_TB_1", 16 );
	PRI_Zo_SYS_A_EXTEND_TB.Connect( pBundle, 0 );
	PRI_Yo_INBD_IND_A_TB.Connect( pBundle, 1 );
	PRI_Yo_BERTH_IND_A_TB.Connect( pBundle, 2 );
	PRI_Yo_OUTBD_IND_A_TB.Connect( pBundle, 3 );
	PRI_RDU_REBERTH_IND_A_TB1.Connect( pBundle, 4 );
	PRI_RDU_STOW_IND_A_TB1.Connect( pBundle, 5 );
	PRI_RDU_DEPLOY_IND_A_TB1.Connect( pBundle, 6 );
	SEC_Zo_SYS_A_EXTEND_TB.Connect( pBundle, 7 );
	SEC_Yo_INBD_IND_A_TB1.Connect( pBundle, 8 );
	SEC_Yo_BERTH_IND_A_TB1.Connect( pBundle, 9 );
	SEC_Yo_OUTBD_IND_A_TB1.Connect( pBundle, 10 );
	SEC_RDU_REBERTH_IND_A_TB1.Connect( pBundle, 11 );
	SEC_RDU_STOW_IND_A_TB1.Connect( pBundle, 12 );
	SEC_RDU_DEPLOY_IND_A_TB1.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "A7A3_SPDS_TB_2", 16 );
	SPDS_PED_DRV_XFR_PRI_A_DIS_TB.Connect( pBundle, 0 );
	SPDS_PED_DRV_XFR_PRI_A_ENG_TB.Connect( pBundle, 1 );
	SPDS_PED_DRV_XFR_PRI_B_DIS_TB.Connect( pBundle, 2 );
	SPDS_PED_DRV_XFR_PRI_B_ENG_TB.Connect( pBundle, 3 );
	SPDS_PED_DRV_XFR_SEC_A_DIS_TB.Connect( pBundle, 4 );
	SPDS_PED_DRV_XFR_SEC_A_ENG_TB.Connect( pBundle, 5 );
	SPDS_PED_DRV_XFR_SEC_B_DIS_TB.Connect( pBundle, 6 );
	SPDS_PED_DRV_XFR_SEC_B_ENG_TB.Connect( pBundle, 7 );
	SPDS_PL_REL_PRI_PED_A_LAT_TB.Connect( pBundle, 8 );
	SPDS_PL_REL_PRI_PED_A_REL_TB.Connect( pBundle, 9 );
	SPDS_PL_REL_PRI_PED_B_LAT_TB.Connect( pBundle, 10 );
	SPDS_PL_REL_PRI_PED_B_REL_TB.Connect( pBundle, 11 );
	SPDS_PL_REL_SEC_PED_A_LAT_TB.Connect( pBundle, 12 );
	SPDS_PL_REL_SEC_PED_A_REL_TB.Connect( pBundle, 13 );
	SPDS_PL_REL_SEC_PED_B_LAT_TB.Connect( pBundle, 14 );
	SPDS_PL_REL_SEC_PED_B_REL_TB.Connect( pBundle, 15 );


	pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM1_CH1", 16 );
	PRI_Zo_SYS_A_EXTEND_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH0", 16 );
	PRI_Zo_SYS_B_EXTEND_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM5_CH1", 16 );
	SEC_Zo_SYS_A_EXTEND_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM10_CH1", 16 );
	SEC_Zo_SYS_B_EXTEND_TM.Connect( pBundle, 0 );


	pBundle = BundleManager()->CreateBundle( "PORT_MPM_CTRL_1", 16 );
	SEC_Yo_INBD_IND_A1.Connect( pBundle, 0 );
	//PORT_SHLD_MECH_STOW_IND_1_TB.Connect( pBundle, 1 );
	//PORT_FWD_MECH_STOW_IND_1_TB.Connect( pBundle, 2 );
	//PORT_MID_MECH_STOW_IND_1_TB.Connect( pBundle, 3 );
	//PORT_AFT_MECH_STOW_IND_1_TB.Connect( pBundle, 4 );
	SEC_Yo_OUTBD_IND_A1.Connect( pBundle, 5 );
	//PORT_SHLD_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 6 );
	//PORT_FWD_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 7 );
	//PORT_MID_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 8 );
	//PORT_AFT_MECH_DEPLOY_IND_1_TB.Connect( pBundle, 9 );
	Yo_MOTOR_A1.Connect( pBundle, 10 );
	//PORT_MPM_SHOULDER_1_IND_PWR.Connect( pBundle, 11 );
	//PORT_MPM_FWD_1_IND_PWR.Connect( pBundle, 12 );
	//PORT_MPM_MID_1_IND_PWR.Connect( pBundle, 13 );
	//PORT_MPM_AFT_1_IND_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "PORT_MPM_CTRL_2", 16 );
	SEC_Yo_INBD_IND_B1.Connect( pBundle, 0 );
	//PORT_SHLD_MECH_STOW_IND_2_TB.Connect( pBundle, 1 );
	//PORT_FWD_MECH_STOW_IND_2_TB.Connect( pBundle, 2 );
	//PORT_MID_MECH_STOW_IND_2_TB.Connect( pBundle, 3 );
	//PORT_AFT_MECH_STOW_IND_2_TB.Connect( pBundle, 4 );
	SEC_Yo_OUTBD_IND_B1.Connect( pBundle, 5 );
	//PORT_SHLD_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 6 );
	//PORT_FWD_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 7 );
	//PORT_MID_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 8 );
	//PORT_AFT_MECH_DEPLOY_IND_2_TB.Connect( pBundle, 9 );
	Yo_MOTOR_B1.Connect( pBundle, 10 );
	//PORT_MPM_SHOULDER_2_IND_PWR.Connect( pBundle, 11 );
	//PORT_MPM_FWD_2_IND_PWR.Connect( pBundle, 12 );
	//PORT_MPM_MID_2_IND_PWR.Connect( pBundle, 13 );
	//PORT_MPM_AFT_2_IND_PWR.Connect( pBundle, 14 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_1", 16 );
	SEC_Yo_BERTH_IND_A.Connect( pBundle, 0 );
	SEC_Yo_OUTBD_IND_A2.Connect( pBundle, 1 );
	Yo_MOTOR_A2.Connect( pBundle, 2 );
	Yo_IND_PWR_2A.Connect( pBundle, 3 );
	SEC_Yo_BERTH_IND_B.Connect( pBundle, 4 );
	SEC_Yo_OUTBD_IND_B2.Connect( pBundle, 5 );
	Yo_MOTOR_B2.Connect( pBundle, 6 );
	Yo_IND_PWR_2B.Connect( pBundle, 7 );
	SEC_Yo_BERTH_IND_A_TB2.Connect( pBundle, 8 );
	SEC_Yo_OUTBD_IND_A_TB2.Connect( pBundle, 9 );
	//PL_2_RDY_1A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_5", 16 );
	SEC_Yo_INBD_IND_A3.Connect( pBundle, 0 );
	SEC_Yo_OUTBD_IND_A3.Connect( pBundle, 1 );
	Yo_MOTOR_A3.Connect( pBundle, 2 );
	Yo_IND_PWR_3A.Connect( pBundle, 3 );
	SEC_Yo_INBD_IND_B3.Connect( pBundle, 4 );
	SEC_Yo_OUTBD_IND_B3.Connect( pBundle, 5 );
	Yo_MOTOR_B3.Connect( pBundle, 6 );
	Yo_IND_PWR_3B.Connect( pBundle, 7 );
	SEC_Yo_INBD_IND_A_TB2.Connect( pBundle, 8 );
	SEC_Yo_OUTBD_IND_A_TB3.Connect( pBundle, 9 );
	//PL_3_RDY_5A_TB.Connect( pBundle, 10 );
	
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM2_CH1", 16 );
	PRI_Yo_OUTBD_IND_A_TM.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM7_CH1", 16 );
	PRI_Yo_OUTBD_IND_B_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH1", 16 );
	SEC_Yo_OUTBD_IND_A_TM1.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
	SEC_Yo_OUTBD_IND_A_TM2.Connect( pBundle, 3 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
	SEC_Yo_OUTBD_IND_A_TM3.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
	SEC_Yo_OUTBD_IND_B_TM1.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
	SEC_Yo_OUTBD_IND_B_TM2.Connect( pBundle, 6 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
	SEC_Yo_OUTBD_IND_B_TM3.Connect( pBundle, 9 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM4_CH1", 16 );
	PRI_Yo_BERTH_IND_A_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM10_CH1", 16 );
	PRI_Yo_BERTH_IND_B_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH2", 16 );
	SEC_Yo_BERTH_IND_A_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH2", 16 );
	SEC_Yo_BERTH_IND_B_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM5_CH2", 16 );
	PRI_Yo_INBD_IND_A_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA1_IOM12_CH0", 16 );
	PRI_Yo_INBD_IND_B_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM5_CH0", 16 );
	SEC_Yo_INBD_IND_A_TM1.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH2", 16 );
	SEC_Yo_INBD_IND_A_TM3.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM7_CH2", 16 );
	SEC_Yo_INBD_IND_B_TM1.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
	SEC_Yo_INBD_IND_B_TM3.Connect( pBundle, 0 );


	pBundle = BundleManager()->CreateBundle( "PORT_FWD_MRL_CTRL", 16 );
	PRI_RDU_REBERTH_IND_B1.Connect( pBundle, 0 );
	PRI_RDU_DEPLOY_IND_B1.Connect( pBundle, 1 );
	PRI_RDU_MOTOR_B1.Connect( pBundle, 2 );
	//PORT_FWD_MRL_IND_1_PWR.Connect( pBundle, 3 );
	//PORT_FWD_RETNN_RFL_1_PWR.Connect( pBundle, 4 );
	//PORT_FWD_MRL_LATCH_IND_1_TB.Connect( pBundle, 5 );
	//PORT_FWD_MRL_RELEASE_IND_1_TB.Connect( pBundle, 6 );
	//PORT_FWD_RETNN_RFL_1_TB.Connect( pBundle, 7 );
	PRI_RDU_REBERTH_IND_A1.Connect( pBundle, 8 );
	PRI_RDU_DEPLOY_IND_A1.Connect( pBundle, 9 );
	PRI_RDU_MOTOR_A1.Connect( pBundle, 10 );
	//PORT_FWD_MRL_IND_2_PWR.Connect( pBundle, 11 );
	//PORT_FWD_RETNN_RFL_2_PWR.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_2", 16 );
	PRI_RDU_STOW_IND_A2.Connect( pBundle, 0 );
	PRI_RDU_DEPLOY_IND_A2.Connect( pBundle, 1 );
	PRI_RDU_MOTOR_A2.Connect( pBundle, 2 );
	RDU_IND_PWR_2A.Connect( pBundle, 3 );
	PRI_RDU_STOW_IND_B2.Connect( pBundle, 4 );
	PRI_RDU_DEPLOY_IND_B2.Connect( pBundle, 5 );
	PRI_RDU_MOTOR_B2.Connect( pBundle, 6 );
	RDU_IND_PWR_2B.Connect( pBundle, 7 );
	PRI_RDU_STOW_IND_A_TB2.Connect( pBundle, 8 );
	PRI_RDU_DEPLOY_IND_A_TB2.Connect( pBundle, 9 );
	//PL_2_RDY_2A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_2_SEL_LATCH_3", 16 );
	PRI_RDU_REBERTH_IND_A3.Connect( pBundle, 0 );
	PRI_RDU_DEPLOY_IND_A3.Connect( pBundle, 1 );
	PRI_RDU_MOTOR_A3.Connect( pBundle, 2 );
	//IND_2A_3.Connect( pBundle, 3 );
	PRI_RDU_REBERTH_IND_B3.Connect( pBundle, 4 );
	PRI_RDU_DEPLOY_IND_B3.Connect( pBundle, 5 );
	PRI_RDU_MOTOR_B3.Connect( pBundle, 6 );
	//IND_2B_3.Connect( pBundle, 7 );
	PRI_RDU_REBERTH_IND_A_TB3.Connect( pBundle, 8 );
	PRI_RDU_DEPLOY_IND_A_TB3.Connect( pBundle, 9 );
	//PL_2_RDY_3A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_3", 16 );
	SEC_RDU_REBERTH_IND_A3.Connect( pBundle, 0 );
	SEC_RDU_DEPLOY_IND_A3.Connect( pBundle, 1 );
	SEC_RDU_MOTOR_A3.Connect( pBundle, 2 );
	RDU_IND_PWR_3A.Connect( pBundle, 3 );
	SEC_RDU_REBERTH_IND_B3.Connect( pBundle, 4 );
	SEC_RDU_DEPLOY_IND_B3.Connect( pBundle, 5 );
	SEC_RDU_MOTOR_B3.Connect( pBundle, 6 );
	RDU_IND_PWR_3B.Connect( pBundle, 7 );
	SEC_RDU_REBERTH_IND_A_TB3.Connect( pBundle, 8 );
	SEC_RDU_DEPLOY_IND_A_TB3.Connect( pBundle, 9 );
	//PL_3_RDY_3A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "PL_3_SEL_LATCH_4", 16 );
	SEC_RDU_STOW_IND_A4.Connect( pBundle, 0 );
	SEC_RDU_DEPLOY_IND_A4.Connect( pBundle, 1 );
	SEC_RDU_MOTOR_A4.Connect( pBundle, 2 );
	//IND_3A_4.Connect( pBundle, 3 );
	SEC_RDU_STOW_IND_B4.Connect( pBundle, 4 );
	SEC_RDU_DEPLOY_IND_B4.Connect( pBundle, 5 );
	SEC_RDU_MOTOR_B4.Connect( pBundle, 6 );
	//IND_3B_4.Connect( pBundle, 7 );
	SEC_RDU_STOW_IND_A_TB4.Connect( pBundle, 8 );
	SEC_RDU_DEPLOY_IND_A_TB4.Connect( pBundle, 9 );
	//PL_3_RDY_4A_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH2", 16 );
	PRI_RDU_REBERTH_IND_A_TM1.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH0", 16 );
	PRI_RDU_REBERTH_IND_A_TM3.Connect( pBundle, 4 );
	PRI_RDU_DEPLOY_IND_A_TM2.Connect( pBundle, 0 );
	PRI_RDU_DEPLOY_IND_A_TM3.Connect( pBundle, 3 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM5_CH2", 16 );
	PRI_RDU_REBERTH_IND_B_TM1.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH0", 16 );
	PRI_RDU_REBERTH_IND_B_TM3.Connect( pBundle, 10 );
	SEC_RDU_REBERTH_IND_B_TM3.Connect( pBundle, 13 );
	PRI_RDU_DEPLOY_IND_B_TM2.Connect( pBundle, 3 );
	PRI_RDU_DEPLOY_IND_B_TM3.Connect( pBundle, 9 );
	SEC_RDU_DEPLOY_IND_B_TM3.Connect( pBundle, 12 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH1", 16 );
	SEC_RDU_REBERTH_IND_A_TM3.Connect( pBundle, 2 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH2", 16 );
	PRI_RDU_STOW_IND_A_TM2.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
	PRI_RDU_STOW_IND_B_TM2.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM6_CH2", 16 );
	SEC_RDU_STOW_IND_A_TM4.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH1", 16 );
	SEC_RDU_STOW_IND_B_TM4.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM7_CH2", 16 );
	PRI_RDU_DEPLOY_IND_A_TM1.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM1_CH2", 16 );
	PRI_RDU_DEPLOY_IND_B_TM1.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
	SEC_RDU_DEPLOY_IND_A_TM3.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH1", 16 );
	SEC_RDU_DEPLOY_IND_A_TM4.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH2", 16 );
	SEC_RDU_DEPLOY_IND_B_TM4.Connect( pBundle, 0 );


	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM12_CH0", 16 );
	SPDS_PED_DRV_XFR_PRI_A_DIS_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM12_CH0", 16 );
	SPDS_PED_DRV_XFR_PRI_A_ENG_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM12_CH2", 16 );
	SPDS_PED_DRV_XFR_PRI_B_DIS_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
	SPDS_PED_DRV_XFR_PRI_B_ENG_TM.Connect( pBundle, 2 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH2", 16 );
	SPDS_PED_DRV_XFR_SEC_A_DIS_TM.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH2", 16 );
	SPDS_PED_DRV_XFR_SEC_A_ENG_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH2", 16 );
	SPDS_PED_DRV_XFR_SEC_B_DIS_TM.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH0", 16 );
	SPDS_PED_DRV_XFR_SEC_B_ENG_TM.Connect( pBundle, 0 );

	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM5_CH1", 16 );
	SPDS_PL_REL_PRI_PED_A_LAT_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
	SPDS_PL_REL_PRI_PED_A_REL_TM.Connect( pBundle, 9 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA2_IOM10_CH2", 16 );
	SPDS_PL_REL_PRI_PED_B_LAT_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM10_CH2", 16 );
	SPDS_PL_REL_PRI_PED_B_REL_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH1", 16 );
	SPDS_PL_REL_SEC_PED_A_LAT_TM.Connect( pBundle, 1 );
	pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
	SPDS_PL_REL_SEC_PED_A_REL_TM.Connect( pBundle, 3 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH1", 16 );
	SPDS_PL_REL_SEC_PED_B_LAT_TM.Connect( pBundle, 0 );
	pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM7_CH2", 16 );
	SPDS_PL_REL_SEC_PED_B_REL_TM.Connect( pBundle, 0 );


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
		pBundle = BundleManager()->CreateBundle( str, 16 );
		LatchLAT_A[i].Connect( pBundle, 0 );
		LatchREL_A[i].Connect( pBundle, 1 );
		LatchMOTOR_1_PWR[i].Connect( pBundle, 2 );
		LatchIND_A[i].Connect( pBundle, 3 );
		LatchLAT_B[i].Connect( pBundle, 4 );
		LatchREL_B[i].Connect( pBundle, 5 );
		LatchMOTOR_2_PWR[i].Connect( pBundle, 6 );
		LatchIND_B[i].Connect( pBundle, 7 );
		LatchLAT_A_TB[i].Connect( pBundle, 8 );
		LatchREL_A_TB[i].Connect( pBundle, 9 );
		LatchRDY_A_TB[i].Connect( pBundle, 10 );

		if (i == 0)
		{
			pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
			LatchREL_A_TM[i].Connect( pBundle, 0 );
			LatchLAT_A_TM[i].Connect( pBundle, 1 );
			LatchRDY_A_TM[i].Connect( pBundle, 2 );

			pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
			LatchREL_B_TM[i].Connect( pBundle, 3 );
			LatchLAT_B_TM[i].Connect( pBundle, 4 );
			LatchRDY_B_TM[i].Connect( pBundle, 5 );
		}
		else if (i == 1)
		{
			pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
			LatchREL_A_TM[i].Connect( pBundle, 6 );
			LatchLAT_A_TM[i].Connect( pBundle, 7 );
			LatchRDY_A_TM[i].Connect( pBundle, 8 );

			pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
			LatchREL_B_TM[i].Connect( pBundle, 12 );
			LatchLAT_B_TM[i].Connect( pBundle, 13 );
			LatchRDY_B_TM[i].Connect( pBundle, 14 );
		}
		else if (i == 2)
		{
			pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
			LatchREL_A_TM[i].Connect( pBundle, 0 );
			LatchLAT_A_TM[i].Connect( pBundle, 1 );
			LatchRDY_A_TM[i].Connect( pBundle, 2 );

			pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
			LatchREL_B_TM[i].Connect( pBundle, 3 );
			LatchLAT_B_TM[i].Connect( pBundle, 4 );
			LatchRDY_B_TM[i].Connect( pBundle, 5 );
		}
		else if (i == 3)
		{
			pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
			LatchREL_A_TM[i].Connect( pBundle, 3 );
			LatchLAT_A_TM[i].Connect( pBundle, 4 );
			LatchRDY_A_TM[i].Connect( pBundle, 5 );

			pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
			LatchREL_B_TM[i].Connect( pBundle, 9 );
			LatchLAT_B_TM[i].Connect( pBundle, 10 );
			LatchRDY_B_TM[i].Connect( pBundle, 11 );
		}
		else// if (i == 4)
		{
			pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
			LatchREL_A_TM[i].Connect( pBundle, 6 );
			LatchLAT_A_TM[i].Connect( pBundle, 7 );
			LatchRDY_A_TM[i].Connect( pBundle, 8 );

			pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH2", 16 );
			LatchREL_B_TM[i].Connect( pBundle, 3 );
			LatchLAT_B_TM[i].Connect( pBundle, 4 );
			LatchRDY_B_TM[i].Connect( pBundle, 5 );
		}
	}

	AddMesh();
	DefineAnimations();
	LoadLatches();
	SetIndications();
	SetAnimations();
	UpdateAttachment();

	// init PAYLOAD_RELEASED
	if (STS()->GetAttachmentStatus( hAttach ) == NULL)
	{
		PAYLOAD_RELEASED = true;
		posEjectionPiston = 1.0;
	}
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

		// set attachment location
		attachpos = PORT_ATTACH_POS + pos;

		// save position for MPM torque tube
		pedestal_xpos[0] = MESH_OFFSET.z + pos.z + MPM_TORQUE_TUBE_OFFSET;
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

		// save position for MPM torque tube
		pedestal_xpos[1] = MESH_OFFSET.z + pos.z + MPM_TORQUE_TUBE_OFFSET;
	}
	else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: 1", spds.PLID[1] );

	// add MPM
	MPM_Base::AddMesh( STS() );
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
	MGROUP_ROTATE* RDU_1 = new MGROUP_ROTATE( mesh_idx_SPDS[0], RDU_GRP, 7, RDU_AXIS_POS, RDU_AXIS_DIR, RDU_RANGE );
	MGROUP_ROTATE* RDU_2 = new MGROUP_ROTATE( mesh_idx_SPDS[1], RDU_GRP, 7, RDU_AXIS_POS, RDU_AXIS_DIR, RDU_RANGE );
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

	// MPM torque tube
	static UINT MPMTT_Grp[1] = {GRP_MPM_TORQUE_TUBE_SPDS};
	MGROUP_SCALE* MPMTT_1 = new MGROUP_SCALE( mesh_idx_SPDS[0], MPMTT_Grp, 1, _V( 0.0, 0.0, MPM_TORQUE_TUBE_OFFSET ),  _V( 1.0, 1.0, (MPM_TORQUE_TUBE_FWD_END - pedestal_xpos[0]) / MPM_TORQUE_TUBE_LENGTH ) );
	MGROUP_SCALE* MPMTT_2 = new MGROUP_SCALE( mesh_idx_SPDS[1], MPMTT_Grp, 1, _V( 0.0, 0.0, MPM_TORQUE_TUBE_OFFSET ),  _V( 1.0, 1.0, (pedestal_xpos[0] - pedestal_xpos[1]) / MPM_TORQUE_TUBE_LENGTH ) );
	UINT anim_MPM_TT = STS()->CreateAnimation( 0.0 );
	STS()->AddAnimationComponent( anim_MPM_TT, 0.0, 1.0, MPMTT_1 );
	STS()->AddAnimationComponent( anim_MPM_TT, 0.0, 1.0, MPMTT_2 );
	SaveAnimation( MPMTT_1 );
	SaveAnimation( MPMTT_2 );
	STS()->SetAnimation( anim_MPM_TT, 1.0 );
	return;
}

void SPDS::LoadLatches( void )
{
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
				UINT mesh_idx = STS()->AddMesh( spds.Reversed[j] ? MESHNAME_PRLA_STBD_ACTIVE : MESHNAME_PRLA_PORT_ACTIVE, &pos );
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
				UINT mesh_idx = STS()->AddMesh( spds.Reversed[j] ? MESHNAME_PRLA_PORT_ACTIVE : MESHNAME_PRLA_STBD_ACTIVE, &pos );
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
			UINT mesh_idx = STS()->AddMesh( fwd ? MESHNAME_AKA_FWD : MESHNAME_AKA_AFT, &posmesh );
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
		}
		else oapiWriteLogV( "(SSV_OV) [ERROR] Invalid PLID %d in SPDS: 4", spds.PLID[4] );
	}
	return;
}

void SPDS::CreateAttachment( void )
{
	if (!hAttach) hAttach = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + attachpos + MESH_OFFSET, PORT_ATTACH_DIR, PORT_ATTACH_ROT, "SPDS" );
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
		VECTOR3 posrdu = mul( mrot, RDU_AXIS_POS - SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS ) + SUPPORT_ASSEMBLY_INBOARD_BOTTOM_AXIS_POS;

		mrot = rotm( -SUPPORT_ASSEMBLY_AXIS_DIR, (motorYo * SUPPORT_ASSEMBLY_ANGLE) - (Yo_RESTOW * RAD) );
		posPL = mul( mrot, posPL - postop ) + postop;
		posrdu = mul( mrot, posrdu - postop ) + postop;

		// Zo
		posPL += (Zo_TRANSLATION * posZo);

		// RDU
		mrot = rotm( RDU_AXIS_DIR, (motorRDU[0] * RDU_RANGE) + RDU_MIN );// both RDUs should be in sync
		posPL = mul( mrot, posPL - posrdu ) + posrdu;
		VECTOR3 dirPL = mul( mrot, PORT_ATTACH_DIR );
		VECTOR3 rotPL = mul( mrot, PORT_ATTACH_ROT );

		STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + posPL + MESH_OFFSET, dirPL, rotPL );
	}
	return;
}

void SPDS::SetIndications( void )
{
	// Yo
	if (motorYo == 0.0)// berth
	{
		PRI_Yo_OUTBD_IND_A_TB.ResetLine();
		PRI_Yo_OUTBD_IND_A_TM.ResetLine();
		PRI_Yo_OUTBD_IND_B_TM.ResetLine();
		PRI_Yo_BERTH_IND_A_TB.SetLine();
		PRI_Yo_BERTH_IND_A_TM.SetLine();
		PRI_Yo_BERTH_IND_B_TM.SetLine();
		PRI_Yo_INBD_IND_A_TB.ResetLine();
		PRI_Yo_INBD_IND_A_TM.ResetLine();
		PRI_Yo_INBD_IND_B_TM.ResetLine();

		SEC_Yo_OUTBD_IND_A1.ResetLine();
		SEC_Yo_OUTBD_IND_A2.ResetLine();
		SEC_Yo_OUTBD_IND_A3.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB1.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB2.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB3.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM1.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM2.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM3.ResetLine();
		SEC_Yo_OUTBD_IND_B1.ResetLine();
		SEC_Yo_OUTBD_IND_B2.ResetLine();
		SEC_Yo_OUTBD_IND_B3.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM1.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM2.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM3.ResetLine();
		if (Yo_IND_PWR_2A || Yo_IND_PWR_3A)
		{
			SEC_Yo_BERTH_IND_A.SetLine();
			SEC_Yo_BERTH_IND_A_TB1.SetLine();
			SEC_Yo_BERTH_IND_A_TB2.SetLine();
			SEC_Yo_BERTH_IND_A_TM.SetLine();
		}
		else
		{
			SEC_Yo_BERTH_IND_A.ResetLine();
			SEC_Yo_BERTH_IND_A_TB1.ResetLine();
			SEC_Yo_BERTH_IND_A_TB2.ResetLine();
			SEC_Yo_BERTH_IND_A_TM.ResetLine();
		}
		if (Yo_IND_PWR_2B || Yo_IND_PWR_3B)
		{
			SEC_Yo_BERTH_IND_B.SetLine();
			SEC_Yo_BERTH_IND_B_TM.SetLine();
		}
		else
		{
			SEC_Yo_BERTH_IND_B.ResetLine();
			SEC_Yo_BERTH_IND_B_TM.ResetLine();
		}
		SEC_Yo_INBD_IND_A1.ResetLine();
		SEC_Yo_INBD_IND_A3.ResetLine();
		SEC_Yo_INBD_IND_A_TB1.ResetLine();
		SEC_Yo_INBD_IND_A_TB2.ResetLine();
		SEC_Yo_INBD_IND_A_TM1.ResetLine();
		SEC_Yo_INBD_IND_A_TM3.ResetLine();
		SEC_Yo_INBD_IND_B1.ResetLine();
		SEC_Yo_INBD_IND_B3.ResetLine();
		SEC_Yo_INBD_IND_B_TM1.ResetLine();
		SEC_Yo_INBD_IND_B_TM3.ResetLine();
	}
	else if (motorYo == 1.0)// outboard
	{
		PRI_Yo_OUTBD_IND_A_TB.SetLine();
		PRI_Yo_OUTBD_IND_A_TM.SetLine();
		PRI_Yo_OUTBD_IND_B_TM.SetLine();
		PRI_Yo_BERTH_IND_A_TB.ResetLine();
		PRI_Yo_BERTH_IND_A_TM.ResetLine();
		PRI_Yo_BERTH_IND_B_TM.ResetLine();
		PRI_Yo_INBD_IND_A_TB.ResetLine();
		PRI_Yo_INBD_IND_A_TM.ResetLine();
		PRI_Yo_INBD_IND_B_TM.ResetLine();

		if (Yo_IND_PWR_2A || Yo_IND_PWR_3A)
		{
			SEC_Yo_OUTBD_IND_A1.SetLine();
			SEC_Yo_OUTBD_IND_A2.SetLine();
			SEC_Yo_OUTBD_IND_A3.SetLine();
			SEC_Yo_OUTBD_IND_A_TB1.SetLine();
			SEC_Yo_OUTBD_IND_A_TB2.SetLine();
			SEC_Yo_OUTBD_IND_A_TB3.SetLine();
			SEC_Yo_OUTBD_IND_A_TM1.SetLine();
			SEC_Yo_OUTBD_IND_A_TM2.SetLine();
			SEC_Yo_OUTBD_IND_A_TM3.SetLine();
		}
		else
		{
			SEC_Yo_OUTBD_IND_A1.ResetLine();
			SEC_Yo_OUTBD_IND_A2.ResetLine();
			SEC_Yo_OUTBD_IND_A3.ResetLine();
			SEC_Yo_OUTBD_IND_A_TB1.ResetLine();
			SEC_Yo_OUTBD_IND_A_TB2.ResetLine();
			SEC_Yo_OUTBD_IND_A_TB3.ResetLine();
			SEC_Yo_OUTBD_IND_A_TM1.ResetLine();
			SEC_Yo_OUTBD_IND_A_TM2.ResetLine();
			SEC_Yo_OUTBD_IND_A_TM3.ResetLine();
		}
		if (Yo_IND_PWR_2B || Yo_IND_PWR_3B)
		{
			SEC_Yo_OUTBD_IND_B1.SetLine();
			SEC_Yo_OUTBD_IND_B2.SetLine();
			SEC_Yo_OUTBD_IND_B3.SetLine();
			SEC_Yo_OUTBD_IND_B_TM1.SetLine();
			SEC_Yo_OUTBD_IND_B_TM2.SetLine();
			SEC_Yo_OUTBD_IND_B_TM3.SetLine();
		}
		else
		{
			SEC_Yo_OUTBD_IND_B1.ResetLine();
			SEC_Yo_OUTBD_IND_B2.ResetLine();
			SEC_Yo_OUTBD_IND_B3.ResetLine();
			SEC_Yo_OUTBD_IND_B_TM1.ResetLine();
			SEC_Yo_OUTBD_IND_B_TM2.ResetLine();
			SEC_Yo_OUTBD_IND_B_TM3.ResetLine();
		}
		SEC_Yo_BERTH_IND_A.ResetLine();
		SEC_Yo_BERTH_IND_A_TB1.ResetLine();
		SEC_Yo_BERTH_IND_A_TB2.ResetLine();
		SEC_Yo_BERTH_IND_A_TM.ResetLine();
		SEC_Yo_BERTH_IND_B.ResetLine();
		SEC_Yo_BERTH_IND_B_TM.ResetLine();
		SEC_Yo_INBD_IND_A1.ResetLine();
		SEC_Yo_INBD_IND_A3.ResetLine();
		SEC_Yo_INBD_IND_A_TB1.ResetLine();
		SEC_Yo_INBD_IND_A_TB2.ResetLine();
		SEC_Yo_INBD_IND_A_TM1.ResetLine();
		SEC_Yo_INBD_IND_A_TM3.ResetLine();
		SEC_Yo_INBD_IND_B1.ResetLine();
		SEC_Yo_INBD_IND_B3.ResetLine();
		SEC_Yo_INBD_IND_B_TM1.ResetLine();
		SEC_Yo_INBD_IND_B_TM3.ResetLine();
	}
	else if (fabs( motorYo - Yo_POS_INBD ) <= Yo_POS_MARGIN)// inboard
	{
		PRI_Yo_OUTBD_IND_A_TB.ResetLine();
		PRI_Yo_OUTBD_IND_A_TM.ResetLine();
		PRI_Yo_OUTBD_IND_B_TM.ResetLine();
		PRI_Yo_BERTH_IND_A_TB.ResetLine();
		PRI_Yo_BERTH_IND_A_TM.ResetLine();
		PRI_Yo_BERTH_IND_B_TM.ResetLine();
		PRI_Yo_INBD_IND_A_TB.SetLine();
		PRI_Yo_INBD_IND_A_TM.SetLine();
		PRI_Yo_INBD_IND_B_TM.SetLine();

		SEC_Yo_OUTBD_IND_A1.ResetLine();
		SEC_Yo_OUTBD_IND_A2.ResetLine();
		SEC_Yo_OUTBD_IND_A3.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB1.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB2.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB3.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM1.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM2.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM3.ResetLine();
		SEC_Yo_OUTBD_IND_B1.ResetLine();
		SEC_Yo_OUTBD_IND_B2.ResetLine();
		SEC_Yo_OUTBD_IND_B3.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM1.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM2.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM3.ResetLine();
		SEC_Yo_BERTH_IND_A.ResetLine();
		SEC_Yo_BERTH_IND_A_TB1.ResetLine();
		SEC_Yo_BERTH_IND_A_TB2.ResetLine();
		SEC_Yo_BERTH_IND_A_TM.ResetLine();
		SEC_Yo_BERTH_IND_B.ResetLine();
		SEC_Yo_BERTH_IND_B_TM.ResetLine();
		if (Yo_IND_PWR_2A || Yo_IND_PWR_3A)
		{
			SEC_Yo_INBD_IND_A1.SetLine();
			SEC_Yo_INBD_IND_A3.SetLine();
			SEC_Yo_INBD_IND_A_TB1.SetLine();
			SEC_Yo_INBD_IND_A_TB2.SetLine();
			SEC_Yo_INBD_IND_A_TM1.SetLine();
			SEC_Yo_INBD_IND_A_TM3.SetLine();
		}
		else
		{
			SEC_Yo_INBD_IND_A1.ResetLine();
			SEC_Yo_INBD_IND_A3.ResetLine();
			SEC_Yo_INBD_IND_A_TB1.ResetLine();
			SEC_Yo_INBD_IND_A_TB2.ResetLine();
			SEC_Yo_INBD_IND_A_TM1.ResetLine();
			SEC_Yo_INBD_IND_A_TM3.ResetLine();
		}
		if (Yo_IND_PWR_2B || Yo_IND_PWR_3B)
		{
			SEC_Yo_INBD_IND_B1.SetLine();
			SEC_Yo_INBD_IND_B3.SetLine();
			SEC_Yo_INBD_IND_B_TM1.SetLine();
			SEC_Yo_INBD_IND_B_TM3.SetLine();
		}
		else
		{
			SEC_Yo_INBD_IND_B1.ResetLine();
			SEC_Yo_INBD_IND_B3.ResetLine();
			SEC_Yo_INBD_IND_B_TM1.ResetLine();
			SEC_Yo_INBD_IND_B_TM3.ResetLine();
		}
	}
	else
	{
		PRI_Yo_OUTBD_IND_A_TB.ResetLine();
		PRI_Yo_OUTBD_IND_A_TM.ResetLine();
		PRI_Yo_OUTBD_IND_B_TM.ResetLine();
		PRI_Yo_BERTH_IND_A_TB.ResetLine();
		PRI_Yo_BERTH_IND_A_TM.ResetLine();
		PRI_Yo_BERTH_IND_B_TM.ResetLine();
		PRI_Yo_INBD_IND_A_TB.ResetLine();
		PRI_Yo_INBD_IND_A_TM.ResetLine();
		PRI_Yo_INBD_IND_B_TM.ResetLine();

		SEC_Yo_OUTBD_IND_A1.ResetLine();
		SEC_Yo_OUTBD_IND_A2.ResetLine();
		SEC_Yo_OUTBD_IND_A3.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB1.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB2.ResetLine();
		SEC_Yo_OUTBD_IND_A_TB3.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM1.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM2.ResetLine();
		SEC_Yo_OUTBD_IND_A_TM3.ResetLine();
		SEC_Yo_OUTBD_IND_B1.ResetLine();
		SEC_Yo_OUTBD_IND_B2.ResetLine();
		SEC_Yo_OUTBD_IND_B3.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM1.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM2.ResetLine();
		SEC_Yo_OUTBD_IND_B_TM3.ResetLine();
		SEC_Yo_BERTH_IND_A.ResetLine();
		SEC_Yo_BERTH_IND_A_TB1.ResetLine();
		SEC_Yo_BERTH_IND_A_TB2.ResetLine();
		SEC_Yo_BERTH_IND_A_TM.ResetLine();
		SEC_Yo_BERTH_IND_B.ResetLine();
		SEC_Yo_BERTH_IND_B_TM.ResetLine();
		SEC_Yo_INBD_IND_A1.ResetLine();
		SEC_Yo_INBD_IND_A3.ResetLine();
		SEC_Yo_INBD_IND_A_TB1.ResetLine();
		SEC_Yo_INBD_IND_A_TB2.ResetLine();
		SEC_Yo_INBD_IND_A_TM1.ResetLine();
		SEC_Yo_INBD_IND_A_TM3.ResetLine();
		SEC_Yo_INBD_IND_B1.ResetLine();
		SEC_Yo_INBD_IND_B3.ResetLine();
		SEC_Yo_INBD_IND_B_TM1.ResetLine();
		SEC_Yo_INBD_IND_B_TM3.ResetLine();
	}

	// Zo
	if (posZo >= 0.9)
	{
		PRI_Zo_SYS_A_EXTEND_TB.SetLine();
		PRI_Zo_SYS_A_EXTEND_TM.SetLine();
		PRI_Zo_SYS_B_EXTEND_TM.SetLine();
		SEC_Zo_SYS_A_EXTEND_TB.SetLine();
		SEC_Zo_SYS_A_EXTEND_TM.SetLine();
		SEC_Zo_SYS_B_EXTEND_TM.SetLine();
	}
	else
	{
		PRI_Zo_SYS_A_EXTEND_TB.ResetLine();
		PRI_Zo_SYS_A_EXTEND_TM.ResetLine();
		PRI_Zo_SYS_B_EXTEND_TM.ResetLine();
		SEC_Zo_SYS_A_EXTEND_TB.ResetLine();
		SEC_Zo_SYS_A_EXTEND_TM.ResetLine();
		SEC_Zo_SYS_B_EXTEND_TM.ResetLine();
	}

	// primary RDU
	if (motorRDU[0] == 0.0)// reberth
	{
		if (RDU_IND_PWR_2A || RDU_IND_PWR_3A)
		{
			PRI_RDU_REBERTH_IND_A1.SetLine();
			PRI_RDU_REBERTH_IND_A3.SetLine();
			PRI_RDU_REBERTH_IND_A_TB1.SetLine();
			PRI_RDU_REBERTH_IND_A_TB3.SetLine();
			PRI_RDU_REBERTH_IND_A_TM1.SetLine();
			PRI_RDU_REBERTH_IND_A_TM3.SetLine();
		}
		else
		{
			PRI_RDU_REBERTH_IND_A1.ResetLine();
			PRI_RDU_REBERTH_IND_A3.ResetLine();
			PRI_RDU_REBERTH_IND_A_TB1.ResetLine();
			PRI_RDU_REBERTH_IND_A_TB3.ResetLine();
			PRI_RDU_REBERTH_IND_A_TM1.ResetLine();
			PRI_RDU_REBERTH_IND_A_TM3.ResetLine();
		}
		if (RDU_IND_PWR_2B || RDU_IND_PWR_3B)
		{
			PRI_RDU_REBERTH_IND_B1.SetLine();
			PRI_RDU_REBERTH_IND_B3.SetLine();
			PRI_RDU_REBERTH_IND_B_TM1.SetLine();
			PRI_RDU_REBERTH_IND_B_TM3.SetLine();
		}
		else
		{
			PRI_RDU_REBERTH_IND_B1.ResetLine();
			PRI_RDU_REBERTH_IND_B3.ResetLine();
			PRI_RDU_REBERTH_IND_B_TM1.ResetLine();
			PRI_RDU_REBERTH_IND_B_TM3.ResetLine();
		}
		PRI_RDU_STOW_IND_A2.ResetLine();
		PRI_RDU_STOW_IND_A_TB1.ResetLine();
		PRI_RDU_STOW_IND_A_TB2.ResetLine();
		PRI_RDU_STOW_IND_A_TM2.ResetLine();
		PRI_RDU_STOW_IND_B2.ResetLine();
		PRI_RDU_STOW_IND_B_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_A1.ResetLine();
		PRI_RDU_DEPLOY_IND_A2.ResetLine();
		PRI_RDU_DEPLOY_IND_A3.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB1.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB2.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB3.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM1.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM3.ResetLine();
		PRI_RDU_DEPLOY_IND_B1.ResetLine();
		PRI_RDU_DEPLOY_IND_B2.ResetLine();
		PRI_RDU_DEPLOY_IND_B3.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM1.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM3.ResetLine();
	}
	else if (motorRDU[0] == 1.0)// deploy
	{
		PRI_RDU_REBERTH_IND_A1.ResetLine();
		PRI_RDU_REBERTH_IND_A3.ResetLine();
		PRI_RDU_REBERTH_IND_A_TB1.ResetLine();
		PRI_RDU_REBERTH_IND_A_TB3.ResetLine();
		PRI_RDU_REBERTH_IND_A_TM1.ResetLine();
		PRI_RDU_REBERTH_IND_A_TM3.ResetLine();
		PRI_RDU_REBERTH_IND_B1.ResetLine();
		PRI_RDU_REBERTH_IND_B3.ResetLine();
		PRI_RDU_REBERTH_IND_B_TM1.ResetLine();
		PRI_RDU_REBERTH_IND_B_TM3.ResetLine();
		PRI_RDU_STOW_IND_A2.ResetLine();
		PRI_RDU_STOW_IND_A_TB1.ResetLine();
		PRI_RDU_STOW_IND_A_TB2.ResetLine();
		PRI_RDU_STOW_IND_A_TM2.ResetLine();
		PRI_RDU_STOW_IND_B2.ResetLine();
		PRI_RDU_STOW_IND_B_TM2.ResetLine();
		if (RDU_IND_PWR_2A || RDU_IND_PWR_3A)
		{
			PRI_RDU_DEPLOY_IND_A1.SetLine();
			PRI_RDU_DEPLOY_IND_A2.SetLine();
			PRI_RDU_DEPLOY_IND_A3.SetLine();
			PRI_RDU_DEPLOY_IND_A_TB1.SetLine();
			PRI_RDU_DEPLOY_IND_A_TB2.SetLine();
			PRI_RDU_DEPLOY_IND_A_TB3.SetLine();
			PRI_RDU_DEPLOY_IND_A_TM1.SetLine();
			PRI_RDU_DEPLOY_IND_A_TM2.SetLine();
			PRI_RDU_DEPLOY_IND_A_TM3.SetLine();
		}
		else
		{
			PRI_RDU_DEPLOY_IND_A1.ResetLine();
			PRI_RDU_DEPLOY_IND_A2.ResetLine();
			PRI_RDU_DEPLOY_IND_A3.ResetLine();
			PRI_RDU_DEPLOY_IND_A_TB1.ResetLine();
			PRI_RDU_DEPLOY_IND_A_TB2.ResetLine();
			PRI_RDU_DEPLOY_IND_A_TB3.ResetLine();
			PRI_RDU_DEPLOY_IND_A_TM1.ResetLine();
			PRI_RDU_DEPLOY_IND_A_TM2.ResetLine();
			PRI_RDU_DEPLOY_IND_A_TM3.ResetLine();
		}
		if (RDU_IND_PWR_2B || RDU_IND_PWR_3B)
		{
			PRI_RDU_DEPLOY_IND_B1.SetLine();
			PRI_RDU_DEPLOY_IND_B2.SetLine();
			PRI_RDU_DEPLOY_IND_B3.SetLine();
			PRI_RDU_DEPLOY_IND_B_TM1.SetLine();
			PRI_RDU_DEPLOY_IND_B_TM2.SetLine();
			PRI_RDU_DEPLOY_IND_B_TM3.SetLine();
		}
		else
		{
			PRI_RDU_DEPLOY_IND_B1.ResetLine();
			PRI_RDU_DEPLOY_IND_B2.ResetLine();
			PRI_RDU_DEPLOY_IND_B3.ResetLine();
			PRI_RDU_DEPLOY_IND_B_TM1.ResetLine();
			PRI_RDU_DEPLOY_IND_B_TM2.ResetLine();
			PRI_RDU_DEPLOY_IND_B_TM3.ResetLine();
		}
	}
	else if (fabs( motorRDU[0] - RDU_POS_STOW ) <= RDU_POS_MARGIN)// stow
	{
		PRI_RDU_REBERTH_IND_A1.ResetLine();
		PRI_RDU_REBERTH_IND_A3.ResetLine();
		PRI_RDU_REBERTH_IND_A_TB1.ResetLine();
		PRI_RDU_REBERTH_IND_A_TB3.ResetLine();
		PRI_RDU_REBERTH_IND_A_TM1.ResetLine();
		PRI_RDU_REBERTH_IND_A_TM3.ResetLine();
		PRI_RDU_REBERTH_IND_B1.ResetLine();
		PRI_RDU_REBERTH_IND_B3.ResetLine();
		PRI_RDU_REBERTH_IND_B_TM1.ResetLine();
		PRI_RDU_REBERTH_IND_B_TM3.ResetLine();
		if (RDU_IND_PWR_2A || RDU_IND_PWR_3A)
		{
			PRI_RDU_STOW_IND_A2.SetLine();
			PRI_RDU_STOW_IND_A_TB1.SetLine();
			PRI_RDU_STOW_IND_A_TB2.SetLine();
			PRI_RDU_STOW_IND_A_TM2.SetLine();
		}
		else
		{
			PRI_RDU_STOW_IND_A2.ResetLine();
			PRI_RDU_STOW_IND_A_TB1.ResetLine();
			PRI_RDU_STOW_IND_A_TB2.ResetLine();
			PRI_RDU_STOW_IND_A_TM2.ResetLine();
		}
		if (RDU_IND_PWR_2B || RDU_IND_PWR_3B)
		{
			PRI_RDU_STOW_IND_B2.SetLine();
			PRI_RDU_STOW_IND_B_TM2.SetLine();
		}
		else
		{
			PRI_RDU_STOW_IND_B2.ResetLine();
			PRI_RDU_STOW_IND_B_TM2.ResetLine();
		}
		PRI_RDU_DEPLOY_IND_A1.ResetLine();
		PRI_RDU_DEPLOY_IND_A2.ResetLine();
		PRI_RDU_DEPLOY_IND_A3.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB1.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB2.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB3.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM1.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM3.ResetLine();
		PRI_RDU_DEPLOY_IND_B1.ResetLine();
		PRI_RDU_DEPLOY_IND_B2.ResetLine();
		PRI_RDU_DEPLOY_IND_B3.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM1.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM3.ResetLine();
	}
	else
	{
		PRI_RDU_REBERTH_IND_A1.ResetLine();
		PRI_RDU_REBERTH_IND_A3.ResetLine();
		PRI_RDU_REBERTH_IND_A_TB1.ResetLine();
		PRI_RDU_REBERTH_IND_A_TB3.ResetLine();
		PRI_RDU_REBERTH_IND_A_TM1.ResetLine();
		PRI_RDU_REBERTH_IND_A_TM3.ResetLine();
		PRI_RDU_REBERTH_IND_B1.ResetLine();
		PRI_RDU_REBERTH_IND_B3.ResetLine();
		PRI_RDU_REBERTH_IND_B_TM1.ResetLine();
		PRI_RDU_REBERTH_IND_B_TM3.ResetLine();
		PRI_RDU_STOW_IND_A2.ResetLine();
		PRI_RDU_STOW_IND_A_TB1.ResetLine();
		PRI_RDU_STOW_IND_A_TB2.ResetLine();
		PRI_RDU_STOW_IND_A_TM2.ResetLine();
		PRI_RDU_STOW_IND_B2.ResetLine();
		PRI_RDU_STOW_IND_B_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_A1.ResetLine();
		PRI_RDU_DEPLOY_IND_A2.ResetLine();
		PRI_RDU_DEPLOY_IND_A3.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB1.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB2.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TB3.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM1.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_A_TM3.ResetLine();
		PRI_RDU_DEPLOY_IND_B1.ResetLine();
		PRI_RDU_DEPLOY_IND_B2.ResetLine();
		PRI_RDU_DEPLOY_IND_B3.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM1.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM2.ResetLine();
		PRI_RDU_DEPLOY_IND_B_TM3.ResetLine();
	}

	// secondary RDU
	if (motorRDU[1] == 0.0)// reberth
	{
		if (RDU_IND_PWR_3A)
		{
			SEC_RDU_REBERTH_IND_A3.SetLine();
			SEC_RDU_REBERTH_IND_A_TB1.SetLine();
			SEC_RDU_REBERTH_IND_A_TB3.SetLine();
			SEC_RDU_REBERTH_IND_A_TM3.SetLine();
		}
		else
		{
			SEC_RDU_REBERTH_IND_A3.ResetLine();
			SEC_RDU_REBERTH_IND_A_TB1.ResetLine();
			SEC_RDU_REBERTH_IND_A_TB3.ResetLine();
			SEC_RDU_REBERTH_IND_A_TM3.ResetLine();
		}
		if (RDU_IND_PWR_3B)
		{
			SEC_RDU_REBERTH_IND_B3.SetLine();
			SEC_RDU_REBERTH_IND_B_TM3.SetLine();
		}
		else
		{
			SEC_RDU_REBERTH_IND_B3.ResetLine();
			SEC_RDU_REBERTH_IND_B_TM3.ResetLine();
		}
		SEC_RDU_STOW_IND_A4.ResetLine();
		SEC_RDU_STOW_IND_A_TB1.ResetLine();
		SEC_RDU_STOW_IND_A_TB4.ResetLine();
		SEC_RDU_STOW_IND_A_TM4.ResetLine();
		SEC_RDU_STOW_IND_B4.ResetLine();
		SEC_RDU_STOW_IND_B_TM4.ResetLine();
		SEC_RDU_DEPLOY_IND_A3.ResetLine();
		SEC_RDU_DEPLOY_IND_A4.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB1.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB3.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB4.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TM3.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TM4.ResetLine();
		SEC_RDU_DEPLOY_IND_B3.ResetLine();
		SEC_RDU_DEPLOY_IND_B4.ResetLine();
		SEC_RDU_DEPLOY_IND_B_TM3.ResetLine();
		SEC_RDU_DEPLOY_IND_B_TM4.ResetLine();
	}
	else if (motorRDU[1] == 1.0)// deploy
	{
		SEC_RDU_REBERTH_IND_A3.ResetLine();
		SEC_RDU_REBERTH_IND_A_TB1.ResetLine();
		SEC_RDU_REBERTH_IND_A_TB3.ResetLine();
		SEC_RDU_REBERTH_IND_A_TM3.ResetLine();
		SEC_RDU_REBERTH_IND_B3.ResetLine();
		SEC_RDU_REBERTH_IND_B_TM3.ResetLine();
		SEC_RDU_STOW_IND_A4.ResetLine();
		SEC_RDU_STOW_IND_A_TB1.ResetLine();
		SEC_RDU_STOW_IND_A_TB4.ResetLine();
		SEC_RDU_STOW_IND_A_TM4.ResetLine();
		SEC_RDU_STOW_IND_B4.ResetLine();
		SEC_RDU_STOW_IND_B_TM4.ResetLine();
		if (RDU_IND_PWR_3A)
		{
			SEC_RDU_DEPLOY_IND_A3.SetLine();
			SEC_RDU_DEPLOY_IND_A4.SetLine();
			SEC_RDU_DEPLOY_IND_A_TB1.SetLine();
			SEC_RDU_DEPLOY_IND_A_TB3.SetLine();
			SEC_RDU_DEPLOY_IND_A_TB4.SetLine();
			SEC_RDU_DEPLOY_IND_A_TM3.SetLine();
			SEC_RDU_DEPLOY_IND_A_TM4.SetLine();
		}
		else
		{
			SEC_RDU_DEPLOY_IND_A3.ResetLine();
			SEC_RDU_DEPLOY_IND_A4.ResetLine();
			SEC_RDU_DEPLOY_IND_A_TB1.ResetLine();
			SEC_RDU_DEPLOY_IND_A_TB3.ResetLine();
			SEC_RDU_DEPLOY_IND_A_TB4.ResetLine();
			SEC_RDU_DEPLOY_IND_A_TM3.ResetLine();
			SEC_RDU_DEPLOY_IND_A_TM4.ResetLine();
		}
		if (RDU_IND_PWR_3B)
		{
			SEC_RDU_DEPLOY_IND_B3.SetLine();
			SEC_RDU_DEPLOY_IND_B4.SetLine();
			SEC_RDU_DEPLOY_IND_B_TM3.SetLine();
			SEC_RDU_DEPLOY_IND_B_TM4.SetLine();
		}
		else
		{
			SEC_RDU_DEPLOY_IND_B3.ResetLine();
			SEC_RDU_DEPLOY_IND_B4.ResetLine();
			SEC_RDU_DEPLOY_IND_B_TM3.ResetLine();
			SEC_RDU_DEPLOY_IND_B_TM4.ResetLine();
		}
	}
	else if (fabs( motorRDU[1] - RDU_POS_STOW ) <= RDU_POS_MARGIN)// stow
	{
		SEC_RDU_REBERTH_IND_A3.ResetLine();
		SEC_RDU_REBERTH_IND_A_TB1.ResetLine();
		SEC_RDU_REBERTH_IND_A_TB3.ResetLine();
		SEC_RDU_REBERTH_IND_A_TM3.ResetLine();
		SEC_RDU_REBERTH_IND_B3.ResetLine();
		SEC_RDU_REBERTH_IND_B_TM3.ResetLine();
		if (RDU_IND_PWR_3A)
		{
			SEC_RDU_STOW_IND_A4.SetLine();
			SEC_RDU_STOW_IND_A_TB1.SetLine();
			SEC_RDU_STOW_IND_A_TB4.SetLine();
			SEC_RDU_STOW_IND_A_TM4.SetLine();
		}
		else
		{
			SEC_RDU_STOW_IND_A4.ResetLine();
			SEC_RDU_STOW_IND_A_TB1.ResetLine();
			SEC_RDU_STOW_IND_A_TB4.ResetLine();
			SEC_RDU_STOW_IND_A_TM4.ResetLine();
		}
		if (RDU_IND_PWR_3B)
		{
			SEC_RDU_STOW_IND_B4.SetLine();
			SEC_RDU_STOW_IND_B_TM4.SetLine();
		}
		else
		{
			SEC_RDU_STOW_IND_B4.ResetLine();
			SEC_RDU_STOW_IND_B_TM4.ResetLine();
		}
		SEC_RDU_DEPLOY_IND_A3.ResetLine();
		SEC_RDU_DEPLOY_IND_A4.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB1.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB3.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB4.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TM3.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TM4.ResetLine();
		SEC_RDU_DEPLOY_IND_B3.ResetLine();
		SEC_RDU_DEPLOY_IND_B4.ResetLine();
		SEC_RDU_DEPLOY_IND_B_TM3.ResetLine();
		SEC_RDU_DEPLOY_IND_B_TM4.ResetLine();
	}
	else
	{
		SEC_RDU_REBERTH_IND_A3.ResetLine();
		SEC_RDU_REBERTH_IND_A_TB1.ResetLine();
		SEC_RDU_REBERTH_IND_A_TB3.ResetLine();
		SEC_RDU_REBERTH_IND_A_TM3.ResetLine();
		SEC_RDU_REBERTH_IND_B3.ResetLine();
		SEC_RDU_REBERTH_IND_B_TM3.ResetLine();
		SEC_RDU_STOW_IND_A4.ResetLine();
		SEC_RDU_STOW_IND_A_TB1.ResetLine();
		SEC_RDU_STOW_IND_A_TB4.ResetLine();
		SEC_RDU_STOW_IND_A_TM4.ResetLine();
		SEC_RDU_STOW_IND_B4.ResetLine();
		SEC_RDU_STOW_IND_B_TM4.ResetLine();
		SEC_RDU_DEPLOY_IND_A3.ResetLine();
		SEC_RDU_DEPLOY_IND_A4.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB1.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB3.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TB4.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TM3.ResetLine();
		SEC_RDU_DEPLOY_IND_A_TM4.ResetLine();
		SEC_RDU_DEPLOY_IND_B3.ResetLine();
		SEC_RDU_DEPLOY_IND_B4.ResetLine();
		SEC_RDU_DEPLOY_IND_B_TM3.ResetLine();
		SEC_RDU_DEPLOY_IND_B_TM4.ResetLine();
	}

	// RDU pedestal drive
	if (RDU_PRI_PED_ENGAGED)
	{
		SPDS_PED_DRV_XFR_PRI_A_DIS_TB.ResetLine();
		SPDS_PED_DRV_XFR_PRI_A_DIS_TM.ResetLine();
		SPDS_PED_DRV_XFR_PRI_A_ENG_TB.SetLine();
		SPDS_PED_DRV_XFR_PRI_A_ENG_TM.SetLine();
		SPDS_PED_DRV_XFR_PRI_B_DIS_TB.ResetLine();
		SPDS_PED_DRV_XFR_PRI_B_DIS_TM.ResetLine();
		SPDS_PED_DRV_XFR_PRI_B_ENG_TB.SetLine();
		SPDS_PED_DRV_XFR_PRI_B_ENG_TM.SetLine();
	}
	else
	{
		SPDS_PED_DRV_XFR_PRI_A_DIS_TB.SetLine();
		SPDS_PED_DRV_XFR_PRI_A_DIS_TM.SetLine();
		SPDS_PED_DRV_XFR_PRI_A_ENG_TB.ResetLine();
		SPDS_PED_DRV_XFR_PRI_A_ENG_TM.ResetLine();
		SPDS_PED_DRV_XFR_PRI_B_DIS_TB.SetLine();
		SPDS_PED_DRV_XFR_PRI_B_DIS_TM.SetLine();
		SPDS_PED_DRV_XFR_PRI_B_ENG_TB.ResetLine();
		SPDS_PED_DRV_XFR_PRI_B_ENG_TM.ResetLine();
	}
	if (RDU_SEC_PED_ENGAGED)
	{
		SPDS_PED_DRV_XFR_SEC_A_DIS_TB.ResetLine();
		SPDS_PED_DRV_XFR_SEC_A_DIS_TM.ResetLine();
		SPDS_PED_DRV_XFR_SEC_A_ENG_TB.SetLine();
		SPDS_PED_DRV_XFR_SEC_A_ENG_TM.SetLine();
		SPDS_PED_DRV_XFR_SEC_B_DIS_TB.ResetLine();
		SPDS_PED_DRV_XFR_SEC_B_DIS_TM.ResetLine();
		SPDS_PED_DRV_XFR_SEC_B_ENG_TB.SetLine();
		SPDS_PED_DRV_XFR_SEC_B_ENG_TM.SetLine();
	}
	else
	{
		SPDS_PED_DRV_XFR_SEC_A_DIS_TB.SetLine();
		SPDS_PED_DRV_XFR_SEC_A_DIS_TM.SetLine();
		SPDS_PED_DRV_XFR_SEC_A_ENG_TB.ResetLine();
		SPDS_PED_DRV_XFR_SEC_A_ENG_TM.ResetLine();
		SPDS_PED_DRV_XFR_SEC_B_DIS_TB.SetLine();
		SPDS_PED_DRV_XFR_SEC_B_DIS_TM.SetLine();
		SPDS_PED_DRV_XFR_SEC_B_ENG_TB.ResetLine();
		SPDS_PED_DRV_XFR_SEC_B_ENG_TM.ResetLine();
	}

	// payload release
	if (posEjectionPiston)
	{
		SPDS_PL_REL_PRI_PED_A_LAT_TB.ResetLine();
		SPDS_PL_REL_PRI_PED_A_LAT_TM.ResetLine();
		SPDS_PL_REL_PRI_PED_A_REL_TB.SetLine();
		SPDS_PL_REL_PRI_PED_A_REL_TM.SetLine();
		SPDS_PL_REL_PRI_PED_B_LAT_TB.ResetLine();
		SPDS_PL_REL_PRI_PED_B_LAT_TM.ResetLine();
		SPDS_PL_REL_PRI_PED_B_REL_TB.SetLine();
		SPDS_PL_REL_PRI_PED_B_REL_TM.SetLine();
		SPDS_PL_REL_SEC_PED_A_LAT_TB.ResetLine();
		SPDS_PL_REL_SEC_PED_A_LAT_TM.ResetLine();
		SPDS_PL_REL_SEC_PED_A_REL_TB.SetLine();
		SPDS_PL_REL_SEC_PED_A_REL_TM.SetLine();
		SPDS_PL_REL_SEC_PED_B_LAT_TB.ResetLine();
		SPDS_PL_REL_SEC_PED_B_LAT_TM.ResetLine();
		SPDS_PL_REL_SEC_PED_B_REL_TB.SetLine();
		SPDS_PL_REL_SEC_PED_B_REL_TM.SetLine();
	}
	else
	{
		SPDS_PL_REL_PRI_PED_A_LAT_TB.SetLine();
		SPDS_PL_REL_PRI_PED_A_LAT_TM.SetLine();
		SPDS_PL_REL_PRI_PED_A_REL_TB.ResetLine();
		SPDS_PL_REL_PRI_PED_A_REL_TM.ResetLine();
		SPDS_PL_REL_PRI_PED_B_LAT_TB.SetLine();
		SPDS_PL_REL_PRI_PED_B_LAT_TM.SetLine();
		SPDS_PL_REL_PRI_PED_B_REL_TB.ResetLine();
		SPDS_PL_REL_PRI_PED_B_REL_TM.ResetLine();
		SPDS_PL_REL_SEC_PED_A_LAT_TB.SetLine();
		SPDS_PL_REL_SEC_PED_A_LAT_TM.SetLine();
		SPDS_PL_REL_SEC_PED_A_REL_TB.ResetLine();
		SPDS_PL_REL_SEC_PED_A_REL_TM.ResetLine();
		SPDS_PL_REL_SEC_PED_B_LAT_TB.SetLine();
		SPDS_PL_REL_SEC_PED_B_LAT_TM.SetLine();
		SPDS_PL_REL_SEC_PED_B_REL_TB.ResetLine();
		SPDS_PL_REL_SEC_PED_B_REL_TM.ResetLine();
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
	double oldmotorYo = motorYo;
	double oldposZo = posZo;
	double oldmotorRDU0 = motorRDU[0];

	// RDU pedestal drive transfer
	if ((PEDESTAL_DRIVE_XFER_SYS_A_ARM && PEDESTAL_DRIVE_XFER_SYS_A_FIRE) || (PEDESTAL_DRIVE_XFER_SYS_B_ARM && PEDESTAL_DRIVE_XFER_SYS_B_FIRE))
	{
		RDU_PRI_PED_ENGAGED = false;
		RDU_SEC_PED_ENGAGED = true;
	}

	// Yo motor
	int yo_pwr_a = MotorPower3( Yo_MOTOR_A1.GetVoltage(), Yo_MOTOR_A2.GetVoltage(), Yo_MOTOR_A3.GetVoltage() );
	int yo_pwr_b = MotorPower3( Yo_MOTOR_B1.GetVoltage(), Yo_MOTOR_B2.GetVoltage(), Yo_MOTOR_B3.GetVoltage() );
	motorYo = range( 0.0, motorYo + (simdt * Yo_MOTOR_SPEED * (yo_pwr_a + yo_pwr_b)), 1.0 );

	// Zo
	if ((LatchState[0] > RELEASE_PRLA_LIMIT) && (LatchState[1] > RELEASE_PRLA_LIMIT) && (LatchState[2] > RELEASE_PRLA_LIMIT) && (LatchState[3] > RELEASE_PRLA_LIMIT) && (LatchState[4] > RELEASE_PRLA_LIMIT))
	{
		unlockZo = true;
	}
	if (unlockZo)
	{
		double oldstaticposZo = staticposZo;
		staticposZo = min(staticposZo + (simdt * Zo_SPEED), 1.0);

		if ((staticposZo != oldstaticposZo) && (staticposZo == 1.0)) tfZo = simt + TX_Zo;
		posZo = staticposZo - (0.5 * osc( TX_Zo, T1_Zo, T2_Zo, simt, tfZo ));
	}

	// RDU motor
	int rdu_pri_pwr_a = MotorPower3( PRI_RDU_MOTOR_A1.GetVoltage(), PRI_RDU_MOTOR_A2.GetVoltage(), PRI_RDU_MOTOR_A3.GetVoltage() );
	int rdu_pri_pwr_b = MotorPower3( PRI_RDU_MOTOR_B1.GetVoltage(), PRI_RDU_MOTOR_B2.GetVoltage(), PRI_RDU_MOTOR_B3.GetVoltage() );
	int rdu_sec_pwr_a = MotorPower2( SEC_RDU_MOTOR_A3.GetVoltage(), SEC_RDU_MOTOR_A4.GetVoltage() );
	int rdu_sec_pwr_b = MotorPower2( SEC_RDU_MOTOR_B3.GetVoltage(), SEC_RDU_MOTOR_B4.GetVoltage() );
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
	bool rdy[5];
	rdy[0] = false;
	rdy[1] = false;
	rdy[2] = false;
	rdy[3] = false;
	rdy[4] = false;
	if (posZo < PRLA_RDY_Zo_LIMIT)
	{
		rdy[0] = true;
		rdy[1] = true;
		rdy[2] = true;
		rdy[3] = true;
		rdy[4] = true;
	}
	// TODO stow

	for (unsigned short i = 0; i < 5; i++)
	{
		LatchState[i] = range( 0.0, LatchState[i] + (simdt * PL_LATCH_RATE * (LatchMOTOR_1_PWR[i].GetVoltage() + LatchMOTOR_2_PWR[i].GetVoltage())), 1.0 );

		// animation
		STS()->SetAnimation( anim_Latch[i], LatchState[i] );

		// indications
		if (LatchIND_A[i])
		{
			if (LatchState[i] == 0.0)
			{
				LatchLAT_A[i].SetLine();
				LatchLAT_A_TB[i].SetLine();
				LatchLAT_A_TM[i].SetLine();
				LatchREL_A[i].ResetLine();
				LatchREL_A_TB[i].ResetLine();
				LatchREL_A_TM[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LatchLAT_A[i].ResetLine();
				LatchLAT_A_TB[i].ResetLine();
				LatchLAT_A_TM[i].ResetLine();
				LatchREL_A[i].SetLine();
				LatchREL_A_TB[i].SetLine();
				LatchREL_A_TM[i].SetLine();
			}
			else
			{
				LatchLAT_A[i].ResetLine();
				LatchLAT_A_TB[i].ResetLine();
				LatchLAT_A_TM[i].ResetLine();
				LatchREL_A[i].ResetLine();
				LatchREL_A_TB[i].ResetLine();
				LatchREL_A_TM[i].ResetLine();
			}

			if (rdy[i])
			{
				LatchRDY_A_TB[i].SetLine();
				LatchRDY_A_TM[i].SetLine();
			}
			else
			{
				LatchRDY_A_TB[i].ResetLine();
				LatchRDY_A_TM[i].ResetLine();
			}
		}
		else
		{
			LatchLAT_A[i].ResetLine();
			LatchLAT_A_TB[i].ResetLine();
			LatchLAT_A_TM[i].ResetLine();
			LatchREL_A[i].ResetLine();
			LatchREL_A_TB[i].ResetLine();
			LatchREL_A_TM[i].ResetLine();
			LatchRDY_A_TB[i].ResetLine();
			LatchRDY_A_TM[i].ResetLine();
		}

		if (LatchIND_B[i])
		{
			if (LatchState[i] == 0.0)
			{
				LatchLAT_B[i].SetLine();
				LatchLAT_B_TM[i].SetLine();
				LatchREL_B[i].ResetLine();
				LatchREL_B_TM[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LatchLAT_B[i].ResetLine();
				LatchLAT_B_TM[i].ResetLine();
				LatchREL_B[i].SetLine();
				LatchREL_B_TM[i].SetLine();
			}
			else
			{
				LatchLAT_B[i].ResetLine();
				LatchLAT_B_TM[i].ResetLine();
				LatchREL_B[i].ResetLine();
				LatchREL_B_TM[i].ResetLine();
			}

			if (rdy[i]) LatchRDY_B_TM[i].SetLine();
			else LatchRDY_B_TM[i].ResetLine();
		}
		else
		{
			LatchLAT_B[i].ResetLine();
			LatchLAT_B_TM[i].ResetLine();
			LatchREL_B[i].ResetLine();
			LatchREL_B_TM[i].ResetLine();
			LatchRDY_B_TM[i].ResetLine();
		}
	}

	if ((oldmotorYo != motorYo) || (oldposZo != posZo) || (oldmotorRDU0 != motorRDU[0]))
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
		sscanf_s( (char*)(line + 2), "%lf", &staticposZo );
		staticposZo = range( 0.0, staticposZo, 1.0 );
		posZo = staticposZo;
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
	oapiWriteScenario_float( scn, "Zo", staticposZo );

	char cbuf[64];
	sprintf_s( cbuf, 64, "%lf %lf", motorRDU[0], motorRDU[1] );
	oapiWriteScenario_string( scn, "RDU", cbuf );

	sprintf_s( cbuf, 64, "%lf %lf %lf %lf %lf", LatchState[0], LatchState[1], LatchState[2], LatchState[3], LatchState[4] );
	oapiWriteScenario_string( scn, "LATCHES", cbuf );
	return;
}

void SPDS::VisualCreated( VISHANDLE vis )
{
	DEVMESHHANDLE hMPMDevMesh = STS()->GetDevMesh( vis, mesh_index_MPM );
	GROUPEDITSPEC grpSpec;
	grpSpec.flags = GRPEDIT_SETUSERFLAG;
	grpSpec.UsrFlag = 3;

	// hide unused MPM parts
	//oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_SHOULDER_MPM_Port, &grpSpec );
	oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_SHOULDER_MPM_Port, &grpSpec );

	oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_FORWARD_MPM_Port, &grpSpec );
	oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_FORWARD_MPM_Port, &grpSpec );

	oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_MID_MPM_Port, &grpSpec );
	oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_MID_MPM_Port, &grpSpec );

	oapiEditMeshGroup( hMPMDevMesh, GRP_BASE_AFT_MPM_Port, &grpSpec );
	oapiEditMeshGroup( hMPMDevMesh, GRP_LOWER_PEDESTAL_AFT_MPM_Port, &grpSpec );
	return;
}

double SPDS::GetSubsystemMass( void ) const
{
	return MASS;
}

bool SPDS::GetSubsystemCoG( VECTOR3& CoG ) const
{
	CoG = CG;
	return true;
}
