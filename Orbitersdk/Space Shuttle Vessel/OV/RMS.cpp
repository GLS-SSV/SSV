/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/06   GLS
2020/05/07   GLS
2020/05/13   GLS
2020/05/14   GLS
2020/05/15   GLS
2020/05/17   GLS
2020/05/18   GLS
2020/05/21   GLS
2020/05/23   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/24   GLS
2020/09/02   GLS
2020/10/10   GLS
2021/06/16   GLS
2021/06/28   GLS
2021/07/02   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/12   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/01   GLS
2022/01/02   GLS
2022/01/03   GLS
2022/01/04   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/01/15   GLS
2022/02/19   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/04/09   GLS
2022/05/07   GLS
2022/05/16   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/30   GLS
2022/11/01   GLS
2022/11/02   GLS
2022/11/09   GLS
2022/11/12   GLS
2022/11/13   GLS
2023/01/15   GLS
2023/02/12   GLS
2023/02/13   GLS
2023/02/16   GLS
********************************************/
#include "RMS.h"
#include "ParameterValues.h"
#include "meshres_RMS_Port.h"
#include "../CommonDefs.h"
#include <MathSSV.h>
#include "../SSVSound.h"
#include "Atlantis.h"
#include "ExternalLight.h"
#include <CCTVCamera.h>
#include <CCTVCameraPTU.h>
#include "RemoteVideoSwitcher.h"
#include "VideoControlUnit.h"
#include <EngConst.h>


const static char* MESHNAME_RMS = "SSV\\RMS_Port";
const static char* MESHNAME_UPPER_PEDESTAL_PORT = "SSV\\MPMUpperPedestal_Port";
const static char* MESHNAME_UPPER_PEDESTAL_STBD = "SSV\\MPMUpperPedestal_Starboard";

constexpr double RMS_ROLLOUT_ANGLE = 19.48;// angle between RMS and vertical when RMS is deployed (in degrees)

const VECTOR3 RMS_MESH_OFFSET = _V( 0.0, 0.0, 0.0 );

// RMS joint positions (stowed, MPM deployed)
const VECTOR3 RMS_SY_JOINT = _V( -2.641549, 0.422581, 6.9797 );// Xo+679.5, Yo-103.998, Zo+433.452
const VECTOR3 RMS_SP_JOINT = _V( -2.7432, 0.709931, 6.9797 );// Xo+679.5, Yo-108.0, Zo+444.765
const VECTOR3 RMS_EP_JOINT = _V( -2.692375, 0.566243, 0.60303 );// Xo+930.55, Yo-105.999, Zo+439.108
const VECTOR3 RMS_WP_JOINT = _V( -2.7432, 0.709931, -6.4569 );// Xo+1208.5, Yo-108.0, Zo+444.765
const VECTOR3 RMS_WY_JOINT = _V( -2.7432, 0.709931, -6.9141 );// Xo+1226.5, Yo-108.0, Zo+444.765
const VECTOR3 RMS_EE_POS = _V( -2.7432, 0.709931, -8.3365 );// Xo+1282.5, Yo-108.0, Zo+444.765

const VECTOR3 RMS_SY_AXIS = _V( -0.333478, 0.942758, 0.0 );
const VECTOR3 RMS_SP_AXIS = _V( 0.942758, 0.333478, 0.0 );
const VECTOR3 RMS_EP_AXIS = RMS_SP_AXIS;
const VECTOR3 RMS_WP_AXIS = RMS_SP_AXIS;
const VECTOR3 RMS_WY_AXIS = RMS_SY_AXIS;
const VECTOR3 RMS_WR_AXIS = _V( 0.0, 0.0, 1.0 );

const VECTOR3 RMS_EE_ROT = _V( 0.0, 1.0, 0.0 );

const double RMS_SP_EP_DIST = length(RMS_EP_JOINT-RMS_SP_JOINT);// distance (metres) from SP joint to EP joint
const double RMS_EP_WP_DIST = length(RMS_WP_JOINT-RMS_EP_JOINT);// distance (metres) from EP joint to WP joint
const double RMS_WP_WY_DIST = length(RMS_WY_JOINT-RMS_WP_JOINT);// distance (metres) from WP joint to WY joint
const double RMS_WY_EE_DIST = length(RMS_WY_JOINT-RMS_EE_POS);// distance (metres) from WY joint to EE
const double RMS_SP_NULL_ANGLE = DEG * acos((RMS_SP_JOINT.z-RMS_EP_JOINT.z)/RMS_SP_EP_DIST);// effective angle (degrees) of shoulder boom in null position
const double RMS_EP_NULL_ANGLE = DEG * acos((RMS_EP_JOINT.z-RMS_WP_JOINT.z)/RMS_EP_WP_DIST);// effective angle (degrees) of elbow boom in null position

constexpr double RMS_JOINT_LIMITS[2][6] = {{-180.0, -2.0, -161.0, -121.4, -121.3, -447.0},
					{+180.0, +145.0, +2.4, +121.4, +121.3, +447.0}};
constexpr double RMS_JOINT_SOFTSTOPS[2][6] = {{-177.4, +0.6, -157.6, -116.4, -116.6, -442.0},
					{+177.4, +142.4, -0.4, +116.4, +116.6, +442.0}};
constexpr double RMS_JOINT_REACHLIMITS[2][6] = {{-175.4, +2.6, -155.6, -114.4, -114.6, -440.0},
					{+175.4, +140.4, -2.4, +114.4, +114.6, +440.0}};

//const double RMS_JOINT_ROTATION_SPEED = 1.5;
constexpr double RMS_JOINT_MAX_ROTATION_SPEED[6] = {40.0, 40.0, 40.0, 40.0, 40.0, 40.0}; // mechanical limits; numbers are made up
constexpr double RMS_JOINT_COARSE_ROTATION_SPEEDS[6] = {1.27, 1.27, 1.78, 2.64, 2.64, 2.64}; // software limits; from PL ID 0
constexpr double RMS_JOINT_VERN_ROTATION_SPEEDS[6] = {0.42, 0.42, 0.59, 0.88, 0.88, 0.88}; // software limits; from PL ID 0

// max unloaded rotation/translation speeds from STS-125 PDRS Flight Supplement (PL ID 0)
// RMS arm joint rotation speed (deg/sec)
const double RMS_EE_COARSE_ROTATION_SPEED = 4.76*RAD;
const double RMS_EE_VERN_ROTATION_SPEED = 4.76*RAD;
// RMS IK rotation speed (rad/sec)
constexpr double RMS_EE_COARSE_TRANSLATION_SPEED = 2.0 * FPS2MS;
constexpr double RMS_EE_VERN_TRANSLATION_SPEED = 0.61 * FPS2MS;
// RMS IK translation speed (m/s)

constexpr double RMS_GRAPPLE_SPEED = 0.4;// Time to fully grapple an object (1/s)
const double RMS_RIGID_SPEED = 0.25;// Time to regidize/derigidize arm (1/s)
const double RMS_EXTEND_SPEED = 0.142857;// Time to extend/retract EE (1/s)

constexpr double SHOULDER_BRACE_SPEED = 0.11765;// shoulder brace speed (8.5 seconds)

const VECTOR3 RMS_ELBOW_PTU_POS = _V( -2.554986, 1.311276, -0.032038 );// Xo+953.03, Yo-100.59, Zo+468.44
const VECTOR3 RMS_ELBOW_PTU_PAN_AXIS = _V( 0.422618, 0.906308, 0.0 );// 25º tilt inboard
const VECTOR3 RMS_ELBOW_PTU_TILT_AXIS = _V( 0.906308, -0.422618, 0.0 );// 25º tilt inboard
const VECTOR3 RMS_ELBOW_CAM_DIR = _V( 0.0, 0.0, -1.0 );
const VECTOR3 RMS_ELBOW_CAM_ROT = _V( 0.422618, 0.906308, 0.0 );// 25º tilt inboard

const VECTOR3 RMS_EE_CAM_POS = _V( -2.7432, 0.995681, -7.7269 );// Xo+1258.5, Yo-108.0, Zo+456.015 (FOV source)
const VECTOR3 RMS_EE_LIGHT_POS = _V( -2.7432, 1.141731, -7.7142 - 0.068725 );// Xo+1258.0 (center of box, plus offset for box surface), Yo-108.0, Zo+461.765

const VECTOR3 RMS_Z_AXIS = _V( 0.0, 1.0, 0.0 ); // axis along which RMS EE camera & light are mounted
const double RMS_Z_AXIS_ANGLE = RMS_ROLLOUT_ANGLE * RAD; // angle between RMS Z axis and Z axis of IK frame

constexpr double MAX_GRAPPLING_DIST = 0.1016;// [m] max distance between RMS tip and grappling point for successful grappling (4'', not considering longitudinal position)
const double MAX_GRAPPLING_ANGLE = 10.0 * RAD;// [rad] max angle between EE and grapple for successful grappling (limited by max roll error)
constexpr double MRL_MAX_ANGLE_ERROR = 0.1;// [deg] max angular misalignment between MPM and RMS to allow latching


constexpr double LIGHT_RANGE = 20.0;// [m]
const double LIGHT_UMBRA_ANGLE = 40.0 * RAD;// [rad]
const double LIGHT_PENUMBRA_ANGLE = LIGHT_UMBRA_ANGLE + (20.0 * RAD);// [rad]

constexpr double LIGHT_ATT0 = 0.5;// [1]
constexpr double LIGHT_ATT1 = 0.0;// [1]
constexpr double LIGHT_ATT2 = 0.05;// [1]


RMS::RMS( AtlantisSubsystemDirector *_director, const std::string& _ident, bool portside )
	: MPM( _director, _ident, "GF", portside, MAX_GRAPPLING_DIST, MAX_GRAPPLING_ANGLE ), bFirstStep(true), stowed_and_latched(true)
{
	joint_angle[SHOULDER_YAW] = 0.0;
	joint_angle[SHOULDER_PITCH] = 0.0;
	joint_angle[ELBOW_PITCH] = 0.0;
	joint_angle[WRIST_PITCH] = 0.0;
	joint_angle[WRIST_YAW] = 0.0;
	joint_angle[WRIST_ROLL] = 0.0;

	posEE = RMS_EE_POS;
	dirEE = -RMS_WR_AXIS;
	rotEE = RMS_EE_ROT;
	rotEEik = RMS_SY_AXIS;

	posCCTVEE = RMS_EE_CAM_POS;
	posCCTVElbow = RMS_ELBOW_PTU_POS;
	dirCCTVElbow = RMS_ELBOW_CAM_DIR;
	rotCCTVElbow = RMS_ELBOW_CAM_ROT;

	posLight = RMS_EE_LIGHT_POS + RMS_MESH_OFFSET;

	arm_ik_pos = _V(RMS_SP_JOINT.z - RMS_EE_POS.z, 0.0, 0.0);
	arm_ik_dir = _V(1.0, 0.0, 0.0);
	arm_ik_rot = _V(0.0, 0.0, 1.0);
	arm_ee_angles = _V(0.0, 0.0, 0.0);

	// default EE to grapple open and derigidized
	Grapple_State.Set(AnimState::OPEN, 1);
	Rigid_State.Set(AnimState::OPEN, 1);
	Extend_State.Set(AnimState::OPEN, 1);

	bAutoGrapple=false;
	bAutoRelease=false;

	shoulder_brace=0.0; // released

	arm_moved=false;
	update_vectors=false;
	update_angles=false;
	for(int i=0;i<6;i++) joint_motion[i]=0;
	for(int i=0;i<3;i++) ee_translation[i]=0;

	bSoftStop = false;

	bEECapture = false;
	bEEExtended = false;
	bEEOpened = false;
	bEEClosed = false;
	bEERigidized = false;
	bEEDerigidized = false;

	MasterAlarmOn = false;
	ReachLimit = false;

	mesh_index_RMS = MESH_UNDEFINED;
	mesh_index_pedestal_forward = MESH_UNDEFINED;
	mesh_index_pedestal_mid = MESH_UNDEFINED;
	mesh_index_pedestal_aft = MESH_UNDEFINED;

	hMesh_RMS = oapiLoadMeshGlobal( MESHNAME_RMS );
	hMesh_Pedestal = oapiLoadMeshGlobal( MESHNAME_UPPER_PEDESTAL_PORT );

	light = new ExternalLight( STS(), posLight, dirEE, 0.0f, 0.0f, LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, LIGHT_UMBRA_ANGLE, LIGHT_PENUMBRA_ANGLE, true );

	cameraElbow = new CCTVCameraPTU( STS(), RMS_ELBOW_PTU_POS, NULL );
	cameraWrist = new CCTVCamera( STS(), RMS_EE_CAM_POS, NULL );
	videoswitcher = new RemoteVideoSwitcher( portside, cameraElbow, cameraWrist, STS() );
}

RMS::~RMS()
{
	delete cameraElbow;
	delete cameraWrist;
	delete videoswitcher;
}

void RMS::Realize()
{
	MPM::Realize();

	DiscreteBundle* pBundle=BundleManager()->CreateBundle("RMS_EE", 16);
	EEGrapple.Connect(pBundle, 0);
	EERelease.Connect(pBundle, 1);
	EEAuto.Connect(pBundle, 2);
	EEMan.Connect(pBundle, 3);
	EERigid.Connect(pBundle, 4);
	EEDerigid.Connect(pBundle, 5);
	EECapture.Connect(pBundle, 6);
	EEExtended.Connect(pBundle, 7);
	EEClosed.Connect(pBundle, 8);
	EEOpened.Connect(pBundle, 9);
	EERigidized.Connect(pBundle, 10);
	EEDerigidized.Connect(pBundle, 11);

	pBundle=BundleManager()->CreateBundle("RMS", 16);
	ShoulderBrace.Connect(pBundle, 4);
	ShoulderBraceReleased.Connect(pBundle, 5);
	RMSSelect.Connect(pBundle, 6);
	MasterAlarmPBI.Connect( pBundle, 7 );

	pBundle=BundleManager()->CreateBundle("RMS_DATA", 16);
	for(int i=0;i<6;i++) JointAngles[i].Connect(pBundle, i);
	for(int i=0;i<3;i++) {
		EEPosition[i].Connect(pBundle, i+6);
		EEAttitude[i].Connect(pBundle, i+9);
	}

	pBundle=BundleManager()->CreateBundle("RMS_HC_INPUT", 16);
	for(int i=0;i<3;i++) {
		RHCInput[i].Connect(pBundle, i);
		THCInput[i].Connect(pBundle, i+3);
	}

	pBundle=BundleManager()->CreateBundle("RMS_SINGLE_JOINT", 16);
	for(int i=0;i<6;i++) {
		JointSelect[i].Connect(pBundle, i);
	}
	// indexes 6 and 7 and used for temps
	DirectDrivePlus.Connect(pBundle, 8);
	DirectDriveMinus.Connect(pBundle, 9);

	pBundle = BundleManager()->CreateBundle( "RMS_MODE", 16 );
	for (int i = 0; i < 12; i++) RMSMode[i].Connect( pBundle, i );
	RMSCoarseRateCMD.Connect( pBundle, 12 );

	pBundle = BundleManager()->CreateBundle( "RMS_CWLIGHTS_TB", 16 );
	for (int i = 0; i < 12; i++) CWLights[i].Connect( pBundle, i );
	SoftStopTB.Connect( pBundle, 12 );
	RateMinTB.Connect( pBundle, 13 );

	pBundle = BundleManager()->CreateBundle( "RMS_MODELIGHTS", 16 );
	for (int i = 0; i < 12; i++) ModeLights[i].Connect( pBundle, i );

	{
		VideoControlUnit* pVCU = static_cast<VideoControlUnit*>(director->GetSubsystemByName( "VideoControlUnit" ));
		pVCU->AddCamera( videoswitcher, portside ? IN_PORT_RMS : IN_STBD_RMS );

		pBundle = BundleManager()->CreateBundle( "VCU_input_3", 16 );
		videoswitcher->ConnectSelSwitch( pBundle, 13 );// TODO handle stbd switch

		pBundle = BundleManager()->CreateBundle( "VCU_output", 16 );
		videoswitcher->ConnectPowerOnOff( pBundle, portside ? 9 : 8 );

		pBundle = STS()->BundleManager()->CreateBundle( "CAMERA_POWER", 16 );
		cameraElbow->ConnectPowerCameraPTU( pBundle, portside ? 12 : 9 );
		cameraElbow->ConnectPowerHeater( pBundle, portside ? 13 : 10 );
		cameraElbow->ConnectPowerPTUHeater( pBundle, portside ? 14 : 11 );

		cameraWrist->ConnectPowerCameraPTU( pBundle, portside ? 12 : 9 );
		cameraWrist->ConnectPowerHeater( pBundle, portside ? 13 : 10 );
	}

	AddMesh();
	DefineAnimations();

	// add end effector light
	pBundle = BundleManager()->CreateBundle( "PLB_LIGHTS", 16 );
	light->DefineMeshGroup( mesh_index_RMS, GRP_LIGHT_RMS_Port );
	light->DefineState( 1, 0.5f, 0.0f, 1.0f, pBundle, 9 );
	return;
}

void RMS::AddMesh( void )
{
	VECTOR3 ofs = STS()->GetOrbiterCoGOffset();
	mesh_index_RMS = STS()->AddMesh( hMesh_RMS, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index_RMS, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + PEDESTAL_OFFSET_PORT_FORWARD;
	mesh_index_pedestal_forward = STS()->AddMesh( hMesh_Pedestal, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index_pedestal_forward, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + PEDESTAL_OFFSET_PORT_MID;
	mesh_index_pedestal_mid = STS()->AddMesh( hMesh_Pedestal, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index_pedestal_mid, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + PEDESTAL_OFFSET_PORT_AFT;
	mesh_index_pedestal_aft = STS()->AddMesh( hMesh_Pedestal, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index_pedestal_aft, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void RMS::DefineAnimations( void )
{
	const VECTOR3 PitchAxis = RotateVectorZ( _V( 1.0, 0.0, 0.0 ), RMS_ROLLOUT_ANGLE );
	const VECTOR3 YawAxis = RotateVectorZ( _V( 0.0, 1.0, 0.0 ), RMS_ROLLOUT_ANGLE );

	// upper pedestals
	static UINT BaseGrp = GRP_BASE_RMS_Port;
	MGROUP_TRANSFORM* pBaseAnim = new MGROUP_TRANSFORM( mesh_index_RMS, &BaseGrp, 1 );
	STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pBaseAnim, mpmparent );
	SaveAnimation( pBaseAnim );

	MGROUP_TRANSFORM* pUpperPedestalFWDAnim = new MGROUP_TRANSFORM( mesh_index_pedestal_forward, NULL, 0 );
	STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestalFWDAnim, mpmparent );
	SaveAnimation( pUpperPedestalFWDAnim );
	MGROUP_TRANSFORM* pUpperPedestalMIDAnim = new MGROUP_TRANSFORM( mesh_index_pedestal_mid, NULL, 0 );
	STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestalMIDAnim, mpmparent );
	SaveAnimation( pUpperPedestalMIDAnim );
	MGROUP_TRANSFORM* pUpperPedestalAFTAnim = new MGROUP_TRANSFORM( mesh_index_pedestal_aft, NULL, 0 );
	STS()->AddAnimationComponent( anim_mpm, 0.0, 1.0, pUpperPedestalAFTAnim, mpmparent );
	SaveAnimation( pUpperPedestalAFTAnim );

	// shoulder yaw
	static UINT RMSShoulderYawGrp[2] = {GRP_SHOULDER_YAW_RMS_Port, GRP_SHOULDER_CABLE_HARNESS_RMS_Port};
	MGROUP_ROTATE* pRMS_sy_anim = new MGROUP_ROTATE( mesh_index_RMS, RMSShoulderYawGrp, 2, RMS_SY_JOINT, YawAxis, static_cast<float>(-360.0 * RAD) );// [-180.0,+180.0]
	anim_joint[SHOULDER_YAW] = STS()->CreateAnimation( 0.5 );
	ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( anim_joint[SHOULDER_YAW], 0.0, 1.0, pRMS_sy_anim, mpmparent );
	SaveAnimation( pRMS_sy_anim );

	// shoulder pitch
	static UINT RMSShoulderPitchGrp[2] = {GRP_UPPER_ARM_BOOM_RMS_Port, GRP_MPM_RETENTION_MECHANISM_UPPER_ARM_BOOM_RMS_Port};
	MGROUP_ROTATE* pRMS_sp_anim = new MGROUP_ROTATE( mesh_index_RMS, RMSShoulderPitchGrp, 2, RMS_SP_JOINT, PitchAxis, static_cast<float>(147.0 * RAD) );// [-2.0,+145.0]
	anim_joint[SHOULDER_PITCH] = STS()->CreateAnimation( 2.0 / 147.0 );
	parent = STS()->AddAnimationComponent( anim_joint[SHOULDER_PITCH], 0.0, 1.0, pRMS_sp_anim, parent );
	SaveAnimation( pRMS_sp_anim );

	// elbow pitch
	static UINT RMSElbowPitchGrp[3] = {GRP_LOWER_ARM_BOOM_RMS_Port, GRP_ELBOW_CAMERA_BASE_FOIL_RMS_Port, GRP_MPM_RETENTION_MECHANISM_LOWER_ARM_BOOM_RMS_Port};
	MGROUP_ROTATE* pRMS_ep_anim = new MGROUP_ROTATE( mesh_index_RMS, RMSElbowPitchGrp, 3, RMS_EP_JOINT, PitchAxis, static_cast<float>(163.4 * RAD) );// [-161.0,+2.4]
	anim_joint[ELBOW_PITCH] = STS()->CreateAnimation( 161.0 / 163.4 );
	parent = STS()->AddAnimationComponent( anim_joint[ELBOW_PITCH], 0.0, 1.0, pRMS_ep_anim, parent );
	SaveAnimation( pRMS_ep_anim );

	// RMS elbow camera
	static UINT RMSElbowCamPanGrp[1] = {GRP_CCTV_PTU_CAM_RMS_ELBOW_RMS_Port};
	MGROUP_ROTATE* pRMSElbowCamPan = new MGROUP_ROTATE( mesh_index_RMS, RMSElbowCamPanGrp, 1, RMS_ELBOW_PTU_POS, RMS_ELBOW_PTU_PAN_AXIS, static_cast<float>((PLB_CAM_PAN_MAX - PLB_CAM_PAN_MIN) * RAD) );
	UINT anim_CamElbowPan = STS()->CreateAnimation( 0.5 );
	ANIMATIONCOMPONENT_HANDLE parent2 = STS()->AddAnimationComponent( anim_CamElbowPan, 0.0, 1.0, pRMSElbowCamPan, parent );
	SaveAnimation( pRMSElbowCamPan );

	static UINT RMSElbowCamTiltGrp[1] = {GRP_CCTV_CAM_RMS_ELBOW_RMS_Port};
	MGROUP_ROTATE* pRMSElbowCamTilt = new MGROUP_ROTATE( mesh_index_RMS, RMSElbowCamTiltGrp, 1, RMS_ELBOW_PTU_POS, RMS_ELBOW_PTU_TILT_AXIS, static_cast<float>((PLB_CAM_TILT_MAX - PLB_CAM_TILT_MIN) * RAD) );
	UINT anim_CamElbowTilt = STS()->CreateAnimation( PLB_CAM_TILT_MIN / (PLB_CAM_TILT_MIN - PLB_CAM_TILT_MAX) );
	STS()->AddAnimationComponent( anim_CamElbowTilt, 0.0, 1.0, pRMSElbowCamTilt, parent2 );
	SaveAnimation( pRMSElbowCamTilt );

	cameraElbow->DefineAnimations( 0.0, -25.0, anim_CamElbowPan, anim_CamElbowTilt );

	// wrist pitch
	static UINT RMSWristPitchGrp[1] = {GRP_WRIST_PITCH_RMS_Port};
	MGROUP_ROTATE* pRMS_wp_anim = new MGROUP_ROTATE( mesh_index_RMS, RMSWristPitchGrp, 1, RMS_WP_JOINT, PitchAxis, static_cast<float>(242.8 * RAD) );// [-121.4,+121.4]
	anim_joint[WRIST_PITCH] = STS()->CreateAnimation( 0.5 );
	parent = STS()->AddAnimationComponent( anim_joint[WRIST_PITCH], 0.0, 1.0, pRMS_wp_anim, parent );
	SaveAnimation( pRMS_wp_anim );

	// wrist yaw
	static UINT RMSWristYawGrp[1] = {GRP_WRIST_YAW_RMS_Port};
	MGROUP_ROTATE* pRMS_wy_anim = new MGROUP_ROTATE( mesh_index_RMS, RMSWristYawGrp, 1, RMS_WY_JOINT, YawAxis, static_cast<float>(242.6 * RAD) );// [-121.3,+121.3]
	anim_joint[WRIST_YAW] = STS()->CreateAnimation( 0.5 );
	parent = STS()->AddAnimationComponent( anim_joint[WRIST_YAW], 0.0, 1.0, pRMS_wy_anim, parent );
	SaveAnimation( pRMS_wy_anim );

	// wrist roll
	static UINT RMSEndEffectorGrp[7] = {GRP_WRIST_ROLL_RMS_Port, GRP_CAMERA_LIGHT_BRACKET_RMS_Port, GRP_WRIST_CAMERA_RMS_Port, GRP_LIGHT_RMS_Port, GRP_LIGHT_HOUSING_RMS_Port, GRP_STANDARD_END_EFFECTOR_RMS_Port, GRP_MPM_RETENTION_MECHANISM_END_EFFECTOR_RMS_Port};
	MGROUP_ROTATE* pRMS_wr_anim = new MGROUP_ROTATE( mesh_index_RMS, RMSEndEffectorGrp, 7, RMS_EE_POS, _V( 0.0, 0.0, 1.0 ), static_cast<float>(894.0 * RAD) );// [-447.0,+447.0]
	anim_joint[WRIST_ROLL] = STS()->CreateAnimation( 0.5 );
	STS()->AddAnimationComponent( anim_joint[WRIST_ROLL], 0.0, 1.0, pRMS_wr_anim, parent );
	SaveAnimation( pRMS_wr_anim );

	//if joint angles were loaded from scenario file,
	if(arm_moved)
	{
		SetJointAngle( SHOULDER_YAW, joint_angle[SHOULDER_YAW] );
		SetJointAngle( SHOULDER_PITCH, joint_angle[SHOULDER_PITCH] );
		SetJointAngle( ELBOW_PITCH, joint_angle[ELBOW_PITCH] );
		SetJointAngle( WRIST_PITCH, joint_angle[WRIST_PITCH] );
		SetJointAngle( WRIST_YAW, joint_angle[WRIST_YAW] );
		SetJointAngle( WRIST_ROLL, joint_angle[WRIST_ROLL] );
		CalcVectors();
	}
	return;
}

void RMS::CreateAttachment()
{
	if(!hAttach)
		hAttach=STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + posEE+RMS_MESH_OFFSET, dirEE, RMS_EE_ROT, "SSV_GF" );
}

void RMS::UpdateAttachment( void )
{
	if (hAttach) STS()->SetAttachmentParams( hAttach, STS()->GetOrbiterCoGOffset() + posEE + RMS_MESH_OFFSET, dirEE, rotEE );

	// also update light and camera position
	UpdateEELight();
	return;
}

void RMS::ShiftCG( const VECTOR3& shift )
{
	UpdateEELight();
	return;
}

bool RMS::Movable( void ) const
{
	return (RMSSelect && Eq( shoulder_brace, 0.0, 0.01 ) && !stowed_and_latched)
		&& (hPayloadAttachment == NULL || (!doubleAttached && PayloadIsFree()));
}

void RMS::OnPreStep(double simt, double simdt, double mjd)
{
	MPM::OnPreStep(simt, simdt, mjd);

	// update light
	light->TimeStep( simdt );
	videoswitcher->TimeStep();
	cameraElbow->TimeStep( simdt );
	cameraWrist->TimeStep( simdt );

	if (bFirstStep) CheckRFL();

	// make sure RMS is powered and can be operated
	if(!RMSSelect) return;

	//rotate joints
	if(Movable()) {
		// single joint rotation
		if(RMSMode[9] || RMSMode[10]) { // make sure RMS is in SINGLE or DIRECT mode
			if(DirectDrivePlus) {
				int joint=GetSelectedJoint();
				if(joint!=-1) {
					if (joint == 0)
					{
						// HACK fix the wrong sign in the shoulder yaw joint (without touching the IK part)
						// a fix for the display angle exists in 7SegDisp_RMS.cpp:425
						if (RMSCoarseRateCMD) SetJointAngle(SHOULDER_YAW, joint_angle[0]-RMS_JOINT_COARSE_ROTATION_SPEEDS[0]*simdt);
						else SetJointAngle(SHOULDER_YAW, joint_angle[0]-RMS_JOINT_VERN_ROTATION_SPEEDS[0]*simdt);
					}
					else
					{
						if (RMSCoarseRateCMD) SetJointAngle((RMS_JOINT)joint, joint_angle[joint]+RMS_JOINT_COARSE_ROTATION_SPEEDS[joint]*simdt);
						else SetJointAngle((RMS_JOINT)joint, joint_angle[joint]+RMS_JOINT_VERN_ROTATION_SPEEDS[joint]*simdt);
					}
				}
				update_vectors=true;
			}
			else if(DirectDriveMinus) {
				int joint=GetSelectedJoint();
				if(joint!=-1) {
					if (joint == 0)
					{
						// HACK fix the wrong sign in the shoulder yaw joint (without touching the IK part)
						// a fix for the display angle exists in PanelA8.cpp:214
						if (RMSCoarseRateCMD) SetJointAngle(SHOULDER_YAW, joint_angle[0]+RMS_JOINT_COARSE_ROTATION_SPEEDS[0]*simdt);
						else SetJointAngle(SHOULDER_YAW, joint_angle[0]+RMS_JOINT_VERN_ROTATION_SPEEDS[0]*simdt);
					}
					else
					{
						if (RMSCoarseRateCMD) SetJointAngle((RMS_JOINT)joint, joint_angle[joint]-RMS_JOINT_COARSE_ROTATION_SPEEDS[joint]*simdt);
						else SetJointAngle((RMS_JOINT)joint, joint_angle[joint]-RMS_JOINT_VERN_ROTATION_SPEEDS[joint]*simdt);
					}
				}
				update_vectors=true;
			}
		}
		else { // not in single joint mode
			VECTOR3 newPos = arm_ik_pos;
			VECTOR3 newDir = arm_ik_dir;
			VECTOR3 newRot = arm_ik_rot;
			bool rotateEE=false, translateEE=false;

			// EE rotation
			VECTOR3 change=_V(0.0, 0.0, 0.0);
			for(int i=0;i<3;i++) {
				if(!Eq(RHCInput[i].GetVoltage(), 0.0, 0.05)) {
					if (RMSCoarseRateCMD) change.data[i]+=(RHCInput[i].GetVoltage()/5.0)*simdt*RMS_EE_COARSE_ROTATION_SPEED;
					else change.data[i]+=(RHCInput[i].GetVoltage()/5.0)*simdt*RMS_EE_VERN_ROTATION_SPEED;
					rotateEE=true;
				}
			}
			if(rotateEE) Rotate(change, newDir, newRot);

			// EE translation
			change=_V(0.0, 0.0, 0.0);
			for(int i=0;i<3;i++) {
				if(!Eq(THCInput[i].GetVoltage(), 0.0, 0.05)) {
					if (RMSCoarseRateCMD) change.data[i]+=(THCInput[i].GetVoltage()/5.0)*simdt*RMS_EE_COARSE_TRANSLATION_SPEED;
					else change.data[i]+=(THCInput[i].GetVoltage()/5.0)*simdt*RMS_EE_VERN_TRANSLATION_SPEED;
					translateEE=true;
				}
				else if(ee_translation[i]!=0) {
					if (RMSCoarseRateCMD) change.data[i]+=ee_translation[i]*simdt*RMS_EE_COARSE_TRANSLATION_SPEED;
					else change.data[i]+=ee_translation[i]*simdt*RMS_EE_VERN_TRANSLATION_SPEED;
					ee_translation[i]=0;
					translateEE=true;
				}
			}
			if(translateEE) Translate(change, newPos);

			if(translateEE || rotateEE) MoveEE(newPos, newDir, newRot, simdt);
		}
	}

	CheckSoftwareStop();

	if(EEAuto || EEMan) {
		if(Grapple_State.Moving()) {
			Grapple_State.Move(simdt*RMS_GRAPPLE_SPEED);

			if(Grapple_State.Closed()) {
				if(!STS()->GetAttachmentStatus(hAttach)) AttachPayload();
				bEEClosed = true;
				if(EEAuto) AutoGrappleSequence();
			}
			else if(Grapple_State.Open()) {
				bEEOpened = true;
				if(EEAuto) AutoReleaseSequence();
			}
			else {
				if(IsLatched()) DetachPayload();
				bEEClosed = false;
				bEEOpened = false;
			}
		}
		if(Extend_State.Moving()) {
			Extend_State.Move(simdt*RMS_EXTEND_SPEED);
			if(Extend_State.Open()) {
				bEEExtended = true;
				if(EEAuto) AutoReleaseSequence();
			}
			else if(Extend_State.Closed() && EEAuto) AutoGrappleSequence();
			else bEEExtended = false;
		}
		if(Rigid_State.Moving()) {
			Rigid_State.Move(simdt*RMS_RIGID_SPEED);
			if(Rigid_State.Open()) {
				bEEDerigidized = true;
				if(EEAuto) AutoReleaseSequence();
			}
			else if(Rigid_State.Closed()) {
				bEERigidized = true;
				if(EEAuto) AutoGrappleSequence();
			}
			else {
				bEEDerigidized = false;
				bEERigidized = false;
			}
		}

		if(EEAuto) {
			if(EEGrapple) {
				bAutoGrapple=true;
				bAutoRelease=false;
				AutoGrappleSequence();
			}
			else if(EERelease) {
				bAutoRelease=true;
				bAutoGrapple=false;
				AutoReleaseSequence();
			}
		}
		else { //EEMan must be set
			if(EEGrapple) Grapple_State.action=AnimState::CLOSING;
			else if(EERelease) Grapple_State.action=AnimState::OPENING;
			else if(Grapple_State.Moving()) Grapple_State.action=AnimState::STOPPED;

			if(EERigid) {
				if(!Extend_State.Closed()) Extend_State.action=AnimState::CLOSING;
				else if(!Rigid_State.Closed()) Rigid_State.action=AnimState::CLOSING;
			}
			else if(EEDerigid) {
				if(!Rigid_State.Open()) Rigid_State.action=AnimState::OPENING;
				else if(!Extend_State.Open()) Extend_State.action=AnimState::OPENING;
			}
			else {
				if(Extend_State.Moving()) Extend_State.action=AnimState::STOPPED;
				if(Rigid_State.Moving()) Rigid_State.action=AnimState::STOPPED;
			}
		}
	}
	else {
		if(Grapple_State.Moving()) Grapple_State.action=AnimState::STOPPED;
		if(Extend_State.Moving()) Extend_State.action=AnimState::STOPPED;
		if(Rigid_State.Moving()) Rigid_State.action=AnimState::STOPPED;
	}

	if(ShoulderBrace) {
		if(shoulder_brace>0.0) {
			shoulder_brace=max(shoulder_brace-simdt*SHOULDER_BRACE_SPEED, 0.0);
		}
	}

	if (MasterAlarmPBI.IsSet())
	{
		MasterAlarmOn = false;
		StopVesselWave( STS()->GetSoundID(), CW_TONE_RMS_SOUND );
	}

	if (bFirstStep)
	{
		// set lines
		if(IsLatched()) bEECapture = true;
		if(Extend_State.Open()) bEEExtended = true;
		if(Grapple_State.Open()) bEEOpened = true;
		else if(Grapple_State.Closed()) bEEClosed = true;
		if(Rigid_State.Closed()) bEERigidized = true;
		else if(Rigid_State.Open()) bEEDerigidized = true;

		SoftStopTB.SetLine( (int)bSoftStop * 5.0f );
		RateMinTB.SetLine( (int)RMSCoarseRateCMD * 5.0f );

		EECapture.SetLine( (int)bEECapture * 5.0f );
		EEExtended.SetLine( (int)bEEExtended * 5.0f );
		EEClosed.SetLine( (int)bEEClosed * 5.0f );
		EEOpened.SetLine( (int)bEEOpened * 5.0f );
		EERigidized.SetLine( (int)bEERigidized * 5.0f );
		EEDerigidized.SetLine( (int)bEEDerigidized * 5.0f );

		if(Eq(shoulder_brace, 0.0, 0.01)) ShoulderBraceReleased.SetLine();
	}
}

void RMS::OnPostStep(double simt, double simdt, double mjd)
{
	MPM::OnPostStep(simt, simdt, mjd);

	// update end effector light position/direction
	if (arm_moved || mpm_moved)
	{
		CalcVectors();
		UpdateEELight();

		cameraElbow->SetPhysicalParams( posCCTVElbow, dirCCTVElbow, rotCCTVElbow );
		cameraWrist->SetPhysicalParams( posCCTVEE, dirEE, rotEE );

		// if arm was moved, update attachment position and IK vectors/angles
		// due to bug in orbiter_ng/D3D9 client, this needs to be done on second timestep
		if(hAttach) STS()->SetAttachmentParams(hAttach, STS()->GetOrbiterCoGOffset()+posEE+RMS_MESH_OFFSET, dirEE, rotEE);

		CheckRFL();

		/*** Update output lines to LEDs ***/
		// calculate position
		VECTOR3 ee_pos_output = (posEE - RMS_SP_JOINT) / IN2M;
		ee_pos_output = _V(ee_pos_output.z, ee_pos_output.x, -ee_pos_output.y) + _V( -679.5, -108.0, -444.77 );

		// calculate attitude
		VECTOR3 ee_frame_x, ee_frame_y, ee_frame_z; // reference frame define by EE direction
		ee_frame_x=ConvertVectorToRMSFrame( dirEE );
		ee_frame_z=ConvertVectorToRMSFrame( -rotEE );
		ee_frame_y=crossp(ee_frame_z, ee_frame_x);
		MATRIX3 ee_frame_mat = _M(ee_frame_x.x, ee_frame_y.x, ee_frame_z.x,
								  ee_frame_x.y, ee_frame_y.y, ee_frame_z.y,
								  ee_frame_x.z, ee_frame_y.z, ee_frame_z.z);
		VECTOR3 ee_att_output = GetYZX_PYRAnglesFromMatrix(ee_frame_mat);
		for(int i=0;i<3;i++) {
			if(ee_att_output.data[i]<0.0) ee_att_output.data[i]+=PI2;

			EEPosition[i].SetLine((float)(ee_pos_output.data[i]/2000.0));
			EEAttitude[i].SetLine((float)(DEG*ee_att_output.data[i]/2000.0));
		}
		if(update_angles) {
			arm_ee_angles=ee_att_output;
			if(!bFirstStep) update_angles=false;
		}

		if(update_vectors) {
			arm_ik_dir=RotateVectorZ( dirEE, -RMS_ROLLOUT_ANGLE );
			arm_ik_dir=ConvertVectorToRMSFrame( arm_ik_dir );

			arm_ik_rot=RotateVectorZ( rotEEik, -RMS_ROLLOUT_ANGLE );
			arm_ik_rot=ConvertVectorToRMSFrame( arm_ik_rot );

			arm_ik_pos=RotateVectorZ( posEE - RMS_SP_JOINT, -RMS_ROLLOUT_ANGLE );
			arm_ik_pos=ConvertVectorToRMSFrame( arm_ik_pos );

			if(!bFirstStep) update_vectors=false;
		}

		if(!bFirstStep) arm_moved=false;
	}

	if(bFirstStep) {
		bFirstStep = false;
	}

	// handle light and talkback outputs
	// HACK most things here should be powered by the RMS Power and not the RMS Select switch
	if (RMSSelect)
	{
		if(Eq(shoulder_brace, 0.0, 0.01)) ShoulderBraceReleased.SetLine();

		// check reach limits
		bool tmp = false;
		for (int i = SHOULDER_YAW; i <= WRIST_ROLL; i++)
		{
			if ((joint_angle[i] < RMS_JOINT_REACHLIMITS[0][i]) || (joint_angle[i] > RMS_JOINT_REACHLIMITS[1][i]))
			{
				tmp = true;
				break;
			}
		}

		if ((tmp == true) && (ReachLimit == false))
		{
			PlayVesselWave( STS()->GetSoundID(), CW_TONE_RMS_SOUND, LOOP );
			MasterAlarmOn = true;
		}
		ReachLimit = tmp;

		CWLights[9].SetLine( (int)ReachLimit * 5.0f );// reach lim light
		CWLights[11].SetLine( (int)MasterAlarmOn * 5.0f );// master alarm light

		for (int i = 0; i < 12; i++) ModeLights[i].SetLine( (int)RMSMode[i] * 5.0f );

		SoftStopTB.SetLine( (int)bSoftStop * 5.0f );
		RateMinTB.SetLine( (int)!RMSCoarseRateCMD * 5.0f );

		EECapture.SetLine( (int)bEECapture * 5.0f );
		EEExtended.SetLine( (int)bEEExtended * 5.0f );
		EEClosed.SetLine( (int)bEEClosed * 5.0f );
		EEOpened.SetLine( (int)bEEOpened * 5.0f );
		EERigidized.SetLine( (int)bEERigidized * 5.0f );
		EEDerigidized.SetLine( (int)bEEDerigidized * 5.0f );
	}
	else
	{
		ShoulderBraceReleased.ResetLine();

		for (int i = 0; i < 12; i++)
		{
			ModeLights[i].ResetLine();
			CWLights[i].ResetLine();
		}

		SoftStopTB.ResetLine();
		RateMinTB.ResetLine();

		EECapture.ResetLine();
		EEExtended.ResetLine();
		EEClosed.ResetLine();
		EEOpened.ResetLine();
		EERigidized.ResetLine();
		EEDerigidized.ResetLine();

		StopVesselWave( STS()->GetSoundID(), CW_TONE_RMS_SOUND );
	}
}

bool RMS::OnParseLine(const char* line)
{
	if (!_strnicmp( line, "ANGLES", 6 ))
	{
		sscanf_s( line + 6, "%lf %lf %lf %lf %lf %lf",
			&joint_angle[SHOULDER_YAW], &joint_angle[SHOULDER_PITCH],
			&joint_angle[ELBOW_PITCH],
			&joint_angle[WRIST_PITCH], &joint_angle[WRIST_YAW], &joint_angle[WRIST_ROLL] );


		joint_angle[SHOULDER_YAW] = -joint_angle[SHOULDER_YAW];// HACK fix the wrong sign in the shoulder yaw joint (without touching the IK part)
		arm_moved=true;
		update_vectors=true;
		update_angles=true;
		return true;
	}
	else if (!_strnicmp( line, "ELBOW_CAM", 9 ))
	{
		cameraElbow->LoadState( line + 9 );
		return true;
	}
	else if (!_strnicmp( line, "WRIST_CAM", 9 ))
	{
		cameraWrist->LoadState( line + 9 );
		return true;
	}
	else if(!_strnicmp(line, "GRAPPLE", 7)) {
		sscan_state((char*)line+7, Grapple_State);
		return true;
	}
	else if(!_strnicmp(line, "RIGIDIZE", 8)) {
		sscan_state((char*)line+8, Rigid_State);
		return true;
	}
	else if(!_strnicmp(line, "EXTEND", 6)) {
		sscan_state((char*)line+6, Extend_State);
		return true;
	}
	else if(!_strnicmp(line, "SHOULDER_BRACE", 14)) {
		sscanf_s(line+14, "%lf", &shoulder_brace);
		return true;
	}

	return MPM::OnParseLine(line);
}

void RMS::OnSaveState(FILEHANDLE scn) const
{
	char cbuf[256];

	sprintf_s( cbuf, 256, "%lf %lf %lf %lf %lf %lf",
		-joint_angle[SHOULDER_YAW]/*HACK fix the wrong sign in the shoulder yaw joint (without touching the IK part)*/, joint_angle[SHOULDER_PITCH],
		joint_angle[ELBOW_PITCH],
		joint_angle[WRIST_PITCH], joint_angle[WRIST_YAW], joint_angle[WRIST_ROLL] );
	oapiWriteScenario_string( scn, "ANGLES", cbuf );
	oapiWriteScenario_float(scn, "SHOULDER_BRACE", shoulder_brace);
	WriteScenario_state(scn, "GRAPPLE", Grapple_State);
	WriteScenario_state(scn, "RIGIDIZE", Rigid_State);
	WriteScenario_state(scn, "EXTEND", Extend_State);
	cameraElbow->SaveState( cbuf );
	oapiWriteScenario_string( scn, "ELBOW_CAM", cbuf );
	cameraWrist->SaveState( cbuf );
	oapiWriteScenario_string( scn, "WRIST_CAM", cbuf );

	MPM::OnSaveState(scn);
	return;
}

void RMS::VisualCreated( VISHANDLE vis )
{
	// update UV in light
	light->VisualCreated();
	return;
}

void RMS::Translate(const VECTOR3 &dPos, VECTOR3& newPos)
{
	if (RMSMode[6].IsSet())// END EFF
	{
		// Reference Frame:
		// X: in direction of EE Z: opposite to camera direction Y: completes RH frame
		VECTOR3 y_axis = crossp(arm_ik_rot, arm_ik_dir);
		// create rotation matrix to convert vector from EE frame to Orbiter body frame
		MATRIX3 EERotMatrix = _M(arm_ik_dir.x, y_axis.x, arm_ik_rot.x,
							   arm_ik_dir.y, y_axis.y, arm_ik_rot.y,
							   arm_ik_dir.z, y_axis.z, arm_ik_rot.z);
		// matrix to convert vector from EE frame to IK frame
		MATRIX3 IKRotMatrix = mul(EERotMatrix, Transpose(GetRotationMatrix(_V(1, 0, 0), RMS_Z_AXIS_ANGLE)));
		newPos = arm_ik_pos+mul(IKRotMatrix, dPos);
	}
	else if (RMSMode[5].IsSet() || RMSMode[7].IsSet())// ORB UNL or ORB LD
	{
		newPos = arm_ik_pos+RotateVectorX(dPos, RMS_ROLLOUT_ANGLE);
	}
	return;
}

void RMS::Rotate(const VECTOR3 &dAngles, VECTOR3& newDir, VECTOR3& newRot)
{
	if (RMSMode[6].IsSet())// END EFF mode
	{
		// NOTE: EE mode rotates relative to camera orientation
		// we do not need to compensate for angle with RMS and shuttle frames
		// in EE mode, Z-axis is in opposited direction to arm_ee_rot
		VECTOR3 y_axis = crossp(arm_ik_rot, arm_ik_dir);
		// create rotation matrix corresponding to current orientation
		MATRIX3 RotMatrix = _M(arm_ik_dir.x, y_axis.x, arm_ik_rot.x,
							   arm_ik_dir.y, y_axis.y, arm_ik_rot.y,
							   arm_ik_dir.z, y_axis.z, arm_ik_rot.z);
		// convert rotation matrix from IK frame to EE frame
		RotMatrix = mul(RotMatrix, GetRotationMatrix(_V(1, 0, 0), -RMS_Z_AXIS_ANGLE));
		// update rotation matrix to adjust for new angles
		MATRIX3 RotMatrixRoll, RotMatrixPitch, RotMatrixYaw;
		GetRotMatrixX(dAngles.data[ROLL], RotMatrixRoll);
		GetRotMatrixY(dAngles.data[PITCH], RotMatrixPitch);
		GetRotMatrixZ(dAngles.data[YAW], RotMatrixYaw);
		RotMatrix = mul(RotMatrix, RotMatrixPitch);
		RotMatrix = mul(RotMatrix, RotMatrixYaw);
		RotMatrix = mul(RotMatrix, RotMatrixRoll);
		// convert rotation matrix from EE frame to IK frame
		RotMatrix = mul(RotMatrix, GetRotationMatrix(_V(1, 0, 0), RMS_Z_AXIS_ANGLE));

		newDir = _V(RotMatrix.m11, RotMatrix.m21, RotMatrix.m31);
		newRot = _V(RotMatrix.m13, RotMatrix.m23, RotMatrix.m33);

		update_angles=true;
	}
	else if (RMSMode[5].IsSet() || RMSMode[7].IsSet())// ORB UNL or ORB LD
	{
		newDir=RotateVectorX(arm_ik_dir, -RMS_ROLLOUT_ANGLE);
		newRot=RotateVectorX(arm_ik_rot, -RMS_ROLLOUT_ANGLE);
		RotateVector(newDir, _V(dAngles.data[ROLL], dAngles.data[PITCH], dAngles.data[YAW]), newDir);
		RotateVector(newRot, _V(dAngles.data[ROLL], dAngles.data[PITCH], dAngles.data[YAW]), newRot);
		newDir=RotateVectorX(newDir, RMS_ROLLOUT_ANGLE);
		newRot=RotateVectorX(newRot, RMS_ROLLOUT_ANGLE);

		update_angles=true;
	}
	return;
}

bool RMS::MoveEE(const VECTOR3 &newPos, const VECTOR3 &newDir, const VECTOR3 &newRot, double simdt)
{
	// NOTE: for cross products, |a x b|=|a||b|sin(theta)
	// all vectors obtained as cross products should be normalized

	double new_joint_angles[6]; // angles in degrees

	VECTOR3 arm_wy_cpos=newPos-newDir*RMS_WY_EE_DIST;
	double yaw_angle=atan2(arm_wy_cpos.y, arm_wy_cpos.x);

	VECTOR3 boom_plane=_V(cos(yaw_angle), sin(yaw_angle), 0.0);
	//find vector in XY plane and perpendicular to arm booms
	VECTOR3 normal=crossp(boom_plane, _V(0.0, 0.0, 1.0));
	normal/=length(normal);

	if((newDir.z>normal.z && newDir.z<boom_plane.z) || (newDir.z<normal.z && newDir.z>boom_plane.z))
		new_joint_angles[WRIST_YAW] = -DEG*acos(dotp(normal, newDir))+90.0;
	else new_joint_angles[WRIST_YAW] = -90.0+DEG*acos(dotp(normal, newDir));

	double phi;
	//find vector in same plane as arm booms and perpendicular to EE direction
	VECTOR3 wp_normal=crossp(normal, newDir);
	if(Eq(length(wp_normal), 0.0, 0.001)) //check if newAtt is perpendicular to arm booms
	{
		// use same phi angle as for previous position
		phi=joint_angle[SHOULDER_PITCH]+joint_angle[ELBOW_PITCH]+joint_angle[WRIST_PITCH];
		wp_normal=RotateVectorZ(boom_plane, phi+90.0);
	}
	else {
		wp_normal/=length(wp_normal);
		phi=DEG*acos(wp_normal.z);
		if(newDir.z>0.0) phi=-phi;
	}

	new_joint_angles[WRIST_ROLL]=-acos(dotp(wp_normal, newRot))*DEG;

	VECTOR3 cross_product=crossp(wp_normal, newRot);
	if(Eq(1.0, dotp(cross_product/length(cross_product), newDir), 0.05))
		new_joint_angles[WRIST_ROLL]=-new_joint_angles[WRIST_ROLL];

	VECTOR3 arm_wp_dir=crossp(wp_normal, normal); // wp_normal and normal vectors are perpendicular
	VECTOR3 arm_wp_cpos=arm_wy_cpos-arm_wp_dir*RMS_WP_WY_DIST;
	double r=length(arm_wp_cpos);

	new_joint_angles[SHOULDER_YAW] = -DEG*yaw_angle;
	double rho=sqrt(arm_wp_cpos.x*arm_wp_cpos.x+arm_wp_cpos.y*arm_wp_cpos.y);
	double cos_phibar_e=(r*r-RMS_SP_EP_DIST*RMS_SP_EP_DIST-RMS_EP_WP_DIST*RMS_EP_WP_DIST)/(-2*RMS_SP_EP_DIST*RMS_EP_WP_DIST);
	if (fabs(cos_phibar_e)>1) return false;//Can't reach new point with the elbow
	new_joint_angles[ELBOW_PITCH]=DEG*acos(cos_phibar_e)-180.0-RMS_EP_NULL_ANGLE-RMS_SP_NULL_ANGLE;
	double cos_phi_s2=(RMS_EP_WP_DIST*RMS_EP_WP_DIST-RMS_SP_EP_DIST*RMS_SP_EP_DIST-r*r)/(-2*RMS_SP_EP_DIST*r);
	if(fabs(cos_phi_s2)>1) return false; //Can't reach with shoulder
	new_joint_angles[SHOULDER_PITCH]=DEG*(-atan2(arm_wp_cpos.z,rho)+acos(cos_phi_s2))+RMS_SP_NULL_ANGLE;

	new_joint_angles[WRIST_PITCH]=phi-new_joint_angles[SHOULDER_PITCH]-new_joint_angles[ELBOW_PITCH];


	// allow use of full motion range of the wrist roll joint
	if ((joint_angle[WRIST_ROLL] - new_joint_angles[WRIST_ROLL]) > 180.0)
	{
		new_joint_angles[WRIST_ROLL] += 360.0;
	}
	else if ((joint_angle[WRIST_ROLL] - new_joint_angles[WRIST_ROLL]) < -180.0)
	{
		new_joint_angles[WRIST_ROLL] -= 360.0;
	}

	// check values are within bounds
	// make sure speed of each joint is within limits
	bool move = true;
	for(int i=SHOULDER_YAW;i<=WRIST_ROLL;i++)
	{
		if (bSoftStop) move = false;

		double speed = abs(new_joint_angles[i]-joint_angle[i])/simdt;
		if (speed > RMS_JOINT_MAX_ROTATION_SPEED[i])
		{
			sprintf_s(oapiDebugString(), 256, "Error: joint %d reached speed limit %f", i, speed);
			move = false;
		}
	}
	if (move == false) return false;

	for(int i=SHOULDER_YAW;i<=WRIST_ROLL;i++) {
		SetJointAngle(static_cast<RMS_JOINT>(i), new_joint_angles[i]);
	}

	arm_ik_pos=newPos;
	arm_ik_dir=newDir;
	arm_ik_rot=newRot;

	return true;
}

void RMS::SetJointAngle(RMS_JOINT joint, double angle)
{
	double pos=linterp(RMS_JOINT_LIMITS[0][joint], 0.0, RMS_JOINT_LIMITS[1][joint], 1.0, angle);
	if (pos>=0.0 && pos<=1.0)
	{
		STS()->SetAnimation(anim_joint[joint], pos);
		joint_angle[joint]=angle;
		JointAngles[joint].SetLine(static_cast<float>(5.0*joint_angle[joint]/9999.0));
		arm_moved=true;
	}
}

int RMS::GetSelectedJoint() const
{
	for(int i=0;i<6;i++) {
		if(JointSelect[i]) return i;
	}
	return -1;
}

void RMS::OnMRLLatched( void )
{
	// if RMS is in stowed position when MRL latches close, set joints to 0 and hold it
	if (ArmStowed())
	{
		for (int i = 0; i < 6; i++) SetJointAngle( (RMS_JOINT)i, 0.0 );
		stowed_and_latched = true;
	}
	return;
}

void RMS::OnMRLReleased( void )
{
	stowed_and_latched = false;
	return;
}

void RMS::OnAttach( void )
{
	MPM::OnAttach();
	bEECapture = true;
	return;
}

void RMS::OnDetach( void )
{
	MPM::OnDetach();
	bEECapture = false;
	return;
}

bool RMS::ArmStowed( void ) const
{
	if(!Eq(joint_angle[SHOULDER_YAW], 0.0, MRL_MAX_ANGLE_ERROR)) return false;
	if(!Eq(joint_angle[SHOULDER_PITCH], 0.0, MRL_MAX_ANGLE_ERROR)) return false;
	if(!Eq(joint_angle[ELBOW_PITCH], 0.0, MRL_MAX_ANGLE_ERROR)) return false;
	if(!Eq(joint_angle[WRIST_PITCH], 0.0, MRL_MAX_ANGLE_ERROR)) return false;
	if(!Eq(joint_angle[WRIST_YAW], 0.0, MRL_MAX_ANGLE_ERROR)) return false;
	if(!Eq(joint_angle[WRIST_ROLL], 0.0, MRL_MAX_ANGLE_ERROR)) return false;
	return true;
}

void RMS::UpdateEELight( void )
{
	light->UpdateLightPosition( STS()->GetOrbiterCoGOffset() + posLight + RMS_MESH_OFFSET );
	light->UpdateLightDirection( dirEE );
	return;
}

void RMS::AutoGrappleSequence()
{
	if(bAutoGrapple) {
		if(!Grapple_State.Closed()) {
			Grapple_State.action=AnimState::CLOSING;
			if(Extend_State.Moving()) Extend_State.action=AnimState::STOPPED;
			if(Rigid_State.Moving()) Rigid_State.action=AnimState::STOPPED;
		}
		else if(!Extend_State.Closed()) {
			Extend_State.action=AnimState::CLOSING;
			if(Rigid_State.Moving()) Rigid_State.action=AnimState::STOPPED;
		}
		else if(!Rigid_State.Closed()) Rigid_State.action=AnimState::CLOSING;
		else bAutoGrapple=false;
	}
}

void RMS::AutoReleaseSequence()
{
	if(bAutoRelease) {
		if(!Rigid_State.Open()) {
			Rigid_State.action=AnimState::OPENING;
			if(Grapple_State.Moving()) Grapple_State.action=AnimState::STOPPED;
			if(Extend_State.Moving()) Extend_State.action=AnimState::STOPPED;
		}
		else if(!Grapple_State.Open()) {
			Grapple_State.action=AnimState::OPENING;
			if(Extend_State.Moving()) Extend_State.action=AnimState::STOPPED;
		}
		else if(!Extend_State.Open()) Extend_State.action=AnimState::OPENING;
		else bAutoRelease=false;
	}
}

void RMS::CheckSoftwareStop( void )
{
	bSoftStop = false;

	for (int i = SHOULDER_YAW; i <= WRIST_ROLL; i++)
	{
		if ((joint_angle[i] < RMS_JOINT_SOFTSTOPS[0][i]) || (joint_angle[i] > RMS_JOINT_SOFTSTOPS[1][i]))
		{
			bSoftStop = true;
			return;
		}
	}
	return;
}

void RMS::CheckRFL( void )
{
	bool fwd = false;
	bool mid = false;
	bool aft = false;

	if (Eq( joint_angle[SHOULDER_YAW], 0.0, MRL_MAX_ANGLE_ERROR ) && Eq( joint_angle[SHOULDER_PITCH], 0.0, MRL_MAX_ANGLE_ERROR ) && ((MRL[0] > 0.5) || stowed_and_latched))
	{
		fwd = true;

		if (Eq( joint_angle[ELBOW_PITCH], 0.0, MRL_MAX_ANGLE_ERROR ) && ((MRL[1] > 0.5) || stowed_and_latched))
		{
			mid = true;

			if (Eq( joint_angle[WRIST_PITCH], 0.0, MRL_MAX_ANGLE_ERROR ) && Eq( joint_angle[WRIST_YAW], 0.0, MRL_MAX_ANGLE_ERROR ) && Eq( joint_angle[WRIST_ROLL], 0.0, MRL_MAX_ANGLE_ERROR ) && ((MRL[2] > 0.5) || stowed_and_latched))
			{
				aft = true;
			}
		}
	}

	SetRFL( fwd, mid, aft );
	return;
}

void RMS::CalcVectors( void )
{
	// MPM rotation
	MATRIX3 mrotMPM = rotm( MPM_DEPLOY_AXIS_PORT, (Rollout - 1.0) * MPM_DEPLOY_ANGLE_PORT );

	VECTOR3 posSY = mul( mrotMPM, RMS_SY_JOINT - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	VECTOR3 axisSY = mul( mrotMPM, RMS_SY_AXIS );

	VECTOR3 posSP = mul( mrotMPM, RMS_SP_JOINT - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	VECTOR3 axisSP = mul( mrotMPM, RMS_SP_AXIS );

	VECTOR3 posEP = mul( mrotMPM, RMS_EP_JOINT - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	VECTOR3 axisEP = mul( mrotMPM, RMS_EP_AXIS );

	posCCTVElbow = mul( mrotMPM, RMS_ELBOW_PTU_POS - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	dirCCTVElbow = mul( mrotMPM, RMS_ELBOW_CAM_DIR );
	rotCCTVElbow = mul( mrotMPM, RMS_ELBOW_CAM_ROT );

	VECTOR3 posWP = mul( mrotMPM, RMS_WP_JOINT - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	VECTOR3 axisWP = mul( mrotMPM, RMS_WP_AXIS );

	VECTOR3 posWY = mul( mrotMPM, RMS_WY_JOINT - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	VECTOR3 axisWY = mul( mrotMPM, RMS_WY_AXIS );

	VECTOR3 posWR = mul( mrotMPM, RMS_WY_JOINT - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	VECTOR3 axisWR = mul( mrotMPM, RMS_WR_AXIS );

	posEE = mul( mrotMPM, RMS_EE_POS - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	rotEE = mul( mrotMPM, RMS_EE_ROT );
	posCCTVEE = mul( mrotMPM, RMS_EE_CAM_POS - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;
	posLight = mul( mrotMPM, RMS_EE_LIGHT_POS - MPM_DEPLOY_REF_PORT ) + MPM_DEPLOY_REF_PORT;


	// SY rotation
	MATRIX3 mrotSY = rotm( axisSY, -joint_angle[SHOULDER_YAW] * RAD );// HACK fix wrong angle sign

	posSP = mul( mrotSY, posSP - posSY ) + posSY;
	axisSP = mul( mrotSY, axisSP );

	posEP = mul( mrotSY, posEP - posSY ) + posSY;
	axisEP = mul( mrotSY, axisEP );

	posCCTVElbow = mul( mrotSY, posCCTVElbow - posSY ) + posSY;
	dirCCTVElbow = mul( mrotSY, dirCCTVElbow );
	rotCCTVElbow = mul( mrotSY, rotCCTVElbow );

	posWP = mul( mrotSY, posWP - posSY ) + posSY;
	axisWP = mul( mrotSY, axisWP );

	posWY = mul( mrotSY, posWY - posSY ) + posSY;
	axisWY = mul( mrotSY, axisWY );

	posWR = mul( mrotSY, posWR - posSY ) + posSY;
	axisWR = mul( mrotSY, axisWR );

	posEE = mul( mrotSY, posEE - posSY ) + posSY;
	rotEE = mul( mrotSY, rotEE );
	posCCTVEE = mul( mrotSY, posCCTVEE - posSY ) + posSY;
	posLight = mul( mrotSY, posLight - posSY ) + posSY;


	// SP rotation
	MATRIX3 mrotSP = rotm( axisSP, joint_angle[SHOULDER_PITCH] * RAD );

	posEP = mul( mrotSP, posEP - posSP ) + posSP;
	axisEP = mul( mrotSP, axisEP );

	posCCTVElbow = mul( mrotSP, posCCTVElbow - posSP ) + posSP;
	dirCCTVElbow = mul( mrotSP, dirCCTVElbow );
	rotCCTVElbow = mul( mrotSP, rotCCTVElbow );

	posWP = mul( mrotSP, posWP - posSP ) + posSP;
	axisWP = mul( mrotSP, axisWP );

	posWY = mul( mrotSP, posWY - posSP ) + posSP;
	axisWY = mul( mrotSP, axisWY );

	posWR = mul( mrotSP, posWR - posSP ) + posSP;
	axisWR = mul( mrotSP, axisWR );

	posEE = mul( mrotSP, posEE - posSP ) + posSP;
	rotEE = mul( mrotSP, rotEE );
	posCCTVEE = mul( mrotSP, posCCTVEE - posSP ) + posSP;
	posLight = mul( mrotSP, posLight - posSP ) + posSP;


	// EP rotation
	// CCTV
	MATRIX3 mrotEP = rotm( axisEP, joint_angle[ELBOW_PITCH] * RAD );

	posCCTVElbow = mul( mrotEP, posCCTVElbow - posEP ) + posEP;
	dirCCTVElbow = mul( mrotEP, dirCCTVElbow );
	rotCCTVElbow = mul( mrotEP, rotCCTVElbow );

	posWP = mul( mrotEP, posWP - posEP ) + posEP;
	axisWP = mul( mrotEP, axisWP );

	posWY = mul( mrotEP, posWY - posEP ) + posEP;
	axisWY = mul( mrotEP, axisWY );

	posWR = mul( mrotEP, posWR - posEP ) + posEP;
	axisWR = mul( mrotEP, axisWR );

	posEE = mul( mrotEP, posEE - posEP ) + posEP;
	rotEE = mul( mrotEP, rotEE );
	posCCTVEE = mul( mrotEP, posCCTVEE - posEP ) + posEP;
	posLight = mul( mrotEP, posLight - posEP ) + posEP;


	// WP rotation
	MATRIX3 mrotWP = rotm( axisWP, joint_angle[WRIST_PITCH] * RAD );

	posWY = mul( mrotWP, posWY - posWP ) + posWP;
	axisWY = mul( mrotWP, axisWY );

	posWR = mul( mrotWP, posWR - posWP ) + posWP;
	axisWR = mul( mrotWP, axisWR );

	posEE = mul( mrotWP, posEE - posWP ) + posWP;
	rotEE = mul( mrotWP, rotEE );
	posCCTVEE = mul( mrotWP, posCCTVEE - posWP ) + posWP;
	posLight = mul( mrotWP, posLight - posWP ) + posWP;


	// WY rotation
	MATRIX3 mrotWY = rotm( axisWY, joint_angle[WRIST_YAW] * RAD );

	posWR = mul( mrotWY, posWR - posWY ) + posWY;
	axisWR = mul( mrotWY, axisWR );

	posEE = mul( mrotWY, posEE - posWY ) + posWY;
	rotEE = mul( mrotWY, rotEE );
	posCCTVEE = mul( mrotWY, posCCTVEE - posWY ) + posWY;
	posLight = mul( mrotWY, posLight - posWY ) + posWY;


	// WR rotation
	// EE
	// CCTV
	// light
	MATRIX3 mrotWR = rotm( axisWR, joint_angle[WRIST_ROLL] * RAD );

	//posEE = mul( mrotWR, posEE - posWR ) + posWR;// no effect
	//dirEE = mul( mrotWR, dirEE );// no effect
	rotEE = mul( mrotWR, rotEE );
	{
		MATRIX3 mrotIK = rotm( axisWR, RMS_ROLLOUT_ANGLE * RAD );
		rotEEik = -mul( mrotIK, rotEE );
	}
	posCCTVEE = mul( mrotWR, posCCTVEE - posWR ) + posWR;
	posLight = mul( mrotWR, posLight - posWR ) + posWR;

	dirEE = -axisWR;
	return;
}