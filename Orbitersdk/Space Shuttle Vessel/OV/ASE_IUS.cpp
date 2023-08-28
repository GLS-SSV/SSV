/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/17   GLS
2020/08/21   GLS
2020/08/24   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/01/20   GLS
2021/06/15   GLS
2021/06/16   GLS
2021/06/20   GLS
2021/06/30   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/04/29   GLS
2022/08/05   GLS
2023/02/06   GLS
2023/06/25   GLS
2023/07/25   GLS
********************************************/
#include "ASE_IUS.h"
#include "meshres_IUS_ASE.h"
#include "Atlantis.h"
#include "PRLA_defs.h"
#include <MathSSV.h>


const static char* MESHNAME_ASE_IUS = "SSV\\OV\\IUS_ASE";

constexpr VECTOR3 ASE_IUS_OFFSET_AFT_LOCATION = { 0.0, -0.4271, -7.4094 };// pins: Xo1116.2     Xo1210.60  Xo1281.40
constexpr VECTOR3 ASE_IUS_OFFSET_FORWARD_LOCATION = { 0.0, -0.4271, -6.010622 };// pins: Xo1061.13     Xo1155.53  Xo1226.33

const VECTOR3 IUS_ATTACHMENT_OFFSET_AFT_LOCATION = ASE_IUS_OFFSET_AFT_LOCATION + _V( 0.0, 0.0, 0.188582 );
const VECTOR3 IUS_ATTACHMENT_OFFSET_FORWARD_LOCATION = ASE_IUS_OFFSET_FORWARD_LOCATION + _V( 0.0, 0.0, 0.188582 );
constexpr VECTOR3 IUS_ATTACHMENT_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 IUS_ATTACHMENT_ROT = { 0.0, 1.0, 0.0 };

constexpr VECTOR3 IUS_ROTATION_AXIS = { -1.0, 0.0, 0.0 };

constexpr VECTOR3 ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS = { 0.0, 0.355599, 0.0 };
constexpr VECTOR3 ASE_IUS_UMBILICAL_ROTATION_AXIS_POS = { 0.469211, -1.32077, 0.720224 };

constexpr double ASE_IUS_TILT_TABLE_SPEED = 0.001493;// s^-1 (= 0.1º/s)
constexpr double ASE_IUS_MASS = 3684.213;// kg
constexpr double IUS_JETTISON_VELOCITY = 0.12192;// m/s

// animation position for ASE angle
constexpr double ASE_IUS_TILT_TABLE_POS_61 = 1.0;
constexpr double ASE_IUS_TILT_TABLE_POS_595 = 0.977612;
constexpr double ASE_IUS_TILT_TABLE_POS_58 = 0.955224;
constexpr double ASE_IUS_TILT_TABLE_POS_57 = 0.940299;
constexpr double ASE_IUS_TILT_TABLE_POS_30 = 0.537313;
constexpr double ASE_IUS_TILT_TABLE_POS_295 = 0.529851;
constexpr double ASE_IUS_TILT_TABLE_POS_28 = 0.507463;
constexpr double ASE_IUS_TILT_TABLE_POS_265 = 0.485075;
constexpr double ASE_IUS_TILT_TABLE_POS_0 = 0.089552;
constexpr double ASE_IUS_TILT_TABLE_POS_06 = 0.0;
// 0.5º delta position window
constexpr double ASE_IUS_TILT_TABLE_DP = 0.007463;


constexpr VECTOR3 PRLA_PORT_FWD_POS = { (94.0 - 56.69) * IN2M, -14.0 * IN2M, 24.239 - (1061.13 * IN2M) };
constexpr VECTOR3 PRLA_STBD_FWD_POS = { (-94.0 + 56.69) * IN2M, -14.0 * IN2M, 24.239 - (1061.13 * IN2M) };

constexpr VECTOR3 PRLA_PORT_AFT_POS = { (94.0 - 56.69) * IN2M, -14.0 * IN2M, 24.239 - (1116.2 * IN2M) };
constexpr VECTOR3 PRLA_STBD_AFT_POS = { (-94.0 + 56.69) * IN2M, -14.0 * IN2M, 24.239 - (1116.2 * IN2M) };


ASE_IUS::ASE_IUS( AtlantisSubsystemDirector* _director, bool AftLocation, const struct mission::Latches* latches ):AtlantisSubsystem( _director, "ASE_IUS" ),
AftLocation(AftLocation)
{
	memcpy( &this->latches, latches, sizeof(struct mission::Latches) * 2 );

	PyroBusPri = false;
	PyroBusAlt = false;
	UmbilicalsEnaPri = false;
	UmbilicalsEnaAlt = false;
	IUSDeploymentEnaPri = false;
	IUSDeploymentEnaAlt = false;
	TiltTableActuatorMotionPri1Lower = false;
	TiltTableActuatorMotionPri1Raise = false;
	TiltTableActuatorMotionAlt2Lower = false;
	TiltTableActuatorMotionAlt2Raise = false;

	hIUSattach = NULL;

	LatchState[0] = 0.0;
	LatchState[1] = 0.0;

	posTiltTable = ASE_IUS_TILT_TABLE_POS_0;// 0º position
	posUmbilical = 0.066667;
	oldposition = ASE_IUS_TILT_TABLE_POS_0;

	umbilicalreleased = false;

	if (AftLocation == true)
	{
		ASEoffset = ASE_IUS_OFFSET_AFT_LOCATION;
		IUSattachoffset = IUS_ATTACHMENT_OFFSET_AFT_LOCATION;
	}
	else
	{
		ASEoffset = ASE_IUS_OFFSET_FORWARD_LOCATION;
		IUSattachoffset = IUS_ATTACHMENT_OFFSET_FORWARD_LOCATION;
	}

	hMesh = oapiLoadMeshGlobal( MESHNAME_ASE_IUS );
	hMesh_Latches[0] = oapiLoadMeshGlobal( MESHNAME_PRLA_PORT_ACTIVE );
	hMesh_Latches[1] = oapiLoadMeshGlobal( MESHNAME_PRLA_STBD_ACTIVE );
	return;
}

ASE_IUS::~ASE_IUS()
{
	return;
}

void ASE_IUS::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "L10toASE_G", 16 );
	pTiltTableActuatorDriveEnablePri1Intermediate.Connect( pBundle, 12 );
	pTiltTableActuatorDriveEnablePri1Maximum.Connect( pBundle, 13 );
	pTiltTableActuatorDriveEnableAlt2Intermediate.Connect( pBundle, 14 );
	pTiltTableActuatorDriveEnableAlt2Maximum.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "L10toASE_H", 16 );
	pTiltTableActuatorMotionPri1Lower.Connect( pBundle, 0 );
	pTiltTableActuatorMotionPri1Raise.Connect( pBundle, 1 );
	pTiltTableActuatorMotionAlt2Lower.Connect( pBundle, 2 );
	pTiltTableActuatorMotionAlt2Raise.Connect( pBundle, 3 );
	pTiltTableActuatorMotionPri1TB.Connect( pBundle, 4 );
	pTiltTableActuatorMotionAlt2TB.Connect( pBundle, 5 );
	pTiltTableActuatorPositionPri1TB.Connect( pBundle, 6 );
	pTiltTableActuatorPositionAlt2TB.Connect( pBundle, 7 );
	// tb
	// tb
	//pTiltTableActuatorAltDrAct1->ConnectPort( 1, pBundle, 10 );

	pPyroBusPriOff.Connect( pBundle, 13 );
	pPyroBusPriOn.Connect( pBundle, 14 );
	pPyroBusPriTB.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "L10toASE_I", 16 );
	pPyroBusAltOff.Connect( pBundle, 0 );
	pPyroBusAltOn.Connect( pBundle, 1 );
	pPyroBusAltTB.Connect( pBundle, 2 );
	pUmbilicalsEnaPriOff.Connect( pBundle, 3 );
	pUmbilicalsEnaPriEnable.Connect( pBundle, 4 );
	pUmbilicalsEnaPriTB.Connect( pBundle, 5 );
	pUmbilicalsEnaAltOff.Connect( pBundle, 6 );
	pUmbilicalsEnaAltEnable.Connect( pBundle, 7 );
	pUmbilicalsEnaAltTB.Connect( pBundle, 8 );
	pUmbilicalsRelPriRelease.Connect( pBundle, 9 );
	pUmbilicalsRelPriTB.Connect( pBundle, 10 );
	pUmbilicalsRelAltRelease.Connect( pBundle, 11 );
	pUmbilicalsRelAltTB.Connect( pBundle, 12 );
	pIUSDeploymentEnaPriOff.Connect( pBundle, 13 );
	pIUSDeploymentEnaPriEnable.Connect( pBundle, 14 );
	pIUSDeploymentEnaPriTB.Connect( pBundle, 15 );

	pBundle = BundleManager()->CreateBundle( "L10toASE_J", 16 );
	pIUSDeploymentEnaAltOff.Connect( pBundle, 0 );
	pIUSDeploymentEnaAltEnable.Connect( pBundle, 1 );
	pIUSDeploymentEnaAltTB.Connect( pBundle, 2 );
	pIUSDeploymentDpyPriDeploy.Connect( pBundle, 3 );
	pIUSDeploymentDpyAltDeploy.Connect( pBundle, 4 );

	for (int i = 0; i < 2; i++)
	{
		string str = "PL_" + std::to_string( latches[i].PL ) + "_SEL_LATCH_" + std::to_string( latches[i].Latch );
		pBundle = BundleManager()->CreateBundle( str, 16 );
		LAT_A[i].Connect( pBundle, 0 );
		REL_A[i].Connect( pBundle, 1 );
		MOTOR_1_PWR[i].Connect( pBundle, 2 );
		IND_A[i].Connect( pBundle, 3 );
		LAT_B[i].Connect( pBundle, 4 );
		REL_B[i].Connect( pBundle, 5 );
		MOTOR_2_PWR[i].Connect( pBundle, 6 );
		IND_B[i].Connect( pBundle, 7 );
		LAT_A_TB[i].Connect( pBundle, 8 );
		REL_A_TB[i].Connect( pBundle, 9 );
		RDY_A_TB[i].Connect( pBundle, 10 );


		if (latches[i].PL == 1)
		{
			if (latches[i].Latch == 1)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 0 );
				LAT_A_TM[i].Connect( pBundle, 1 );
				RDY_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 3 );
				LAT_B_TM[i].Connect( pBundle, 4 );
				RDY_B_TM[i].Connect( pBundle, 5 );
			}
			else if (latches[i].Latch == 2)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 6 );
				LAT_A_TM[i].Connect( pBundle, 7 );
				RDY_A_TM[i].Connect( pBundle, 8 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 12 );
				LAT_B_TM[i].Connect( pBundle, 13 );
				RDY_B_TM[i].Connect( pBundle, 14 );
			}
			else if (latches[i].Latch == 3)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 0 );
				LAT_A_TM[i].Connect( pBundle, 1 );
				RDY_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
				REL_B_TM[i].Connect( pBundle, 3 );
				LAT_B_TM[i].Connect( pBundle, 4 );
				RDY_B_TM[i].Connect( pBundle, 5 );
			}
			else if (latches[i].Latch == 4)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 3 );
				LAT_A_TM[i].Connect( pBundle, 4 );
				RDY_A_TM[i].Connect( pBundle, 5 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
				REL_B_TM[i].Connect( pBundle, 9 );
				LAT_B_TM[i].Connect( pBundle, 10 );
				RDY_B_TM[i].Connect( pBundle, 11 );
			}
			else// if (latches[i].Latch == 5)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 6 );
				LAT_A_TM[i].Connect( pBundle, 7 );
				RDY_A_TM[i].Connect( pBundle, 8 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH2", 16 );
				REL_B_TM[i].Connect( pBundle, 3 );
				LAT_B_TM[i].Connect( pBundle, 4 );
				RDY_B_TM[i].Connect( pBundle, 5 );
			}
		}
		else if (latches[i].PL == 2)
		{
			if (latches[i].Latch == 1)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM12_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 3 );
				RDY_A_TM[i].Connect( pBundle, 5 );

				pBundle = BundleManager()->CreateBundle( "MDM_OA3_IOM1_CH2", 16 );
				LAT_A_TM[i].Connect( pBundle, 0 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 6 );
				RDY_B_TM[i].Connect( pBundle, 8 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH2", 16 );
				LAT_B_TM[i].Connect( pBundle, 0 );
			}
			else if (latches[i].Latch == 2)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 0 );
				RDY_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM7_CH2", 16 );
				LAT_A_TM[i].Connect( pBundle, 0 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 3 );
				RDY_B_TM[i].Connect( pBundle, 5 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
				LAT_B_TM[i].Connect( pBundle, 1 );
			}
			else if (latches[i].Latch == 3)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 3 );
				LAT_A_TM[i].Connect( pBundle, 4 );
				RDY_A_TM[i].Connect( pBundle, 5 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 9 );
				LAT_B_TM[i].Connect( pBundle, 10 );
				RDY_B_TM[i].Connect( pBundle, 11 );
			}
			else if (latches[i].Latch == 4)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF4_IOM15_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 6 );
				LAT_A_TM[i].Connect( pBundle, 7 );
				RDY_A_TM[i].Connect( pBundle, 8 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
				REL_B_TM[i].Connect( pBundle, 0 );
				LAT_B_TM[i].Connect( pBundle, 1 );
				RDY_B_TM[i].Connect( pBundle, 2 );
			}
			else// if (latches[i].Latch == 5)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 12 );
				LAT_A_TM[i].Connect( pBundle, 13 );
				RDY_A_TM[i].Connect( pBundle, 14 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
				REL_B_TM[i].Connect( pBundle, 6 );
				LAT_B_TM[i].Connect( pBundle, 7 );
				RDY_B_TM[i].Connect( pBundle, 8 );
			}
		}
		else// if (latches[i].PL == 3)
		{
			if (latches[i].Latch == 1)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 0 );
				LAT_A_TM[i].Connect( pBundle, 1 );
				RDY_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 0 );
				LAT_B_TM[i].Connect( pBundle, 1 );
				RDY_B_TM[i].Connect( pBundle, 2 );
			}
			else if (latches[i].Latch == 2)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH0", 16 );
				REL_A_TM[i].Connect( pBundle, 9 );
				LAT_A_TM[i].Connect( pBundle, 10 );
				RDY_A_TM[i].Connect( pBundle, 11 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 6 );
				LAT_B_TM[i].Connect( pBundle, 7 );
				RDY_B_TM[i].Connect( pBundle, 8 );
			}
			else if (latches[i].Latch == 3)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 0 );
				RDY_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM12_CH1", 16 );
				LAT_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH0", 16 );
				REL_B_TM[i].Connect( pBundle, 12 );
				LAT_B_TM[i].Connect( pBundle, 13 );
				RDY_B_TM[i].Connect( pBundle, 14 );
			}
			else if (latches[i].Latch == 4)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 1 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM6_CH2", 16 );
				LAT_A_TM[i].Connect( pBundle, 0 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
				RDY_A_TM[i].Connect( pBundle, 8 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH2", 16 );
				REL_B_TM[i].Connect( pBundle, 0 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM6_CH1", 16 );
				LAT_B_TM[i].Connect( pBundle, 0 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
				RDY_B_TM[i].Connect( pBundle, 5 );
			}
			else// if (latches[i].Latch == 5)
			{
				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH1", 16 );
				REL_A_TM[i].Connect( pBundle, 1 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM4_CH2", 16 );
				LAT_A_TM[i].Connect( pBundle, 0 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF2_IOM14_CH2", 16 );
				RDY_A_TM[i].Connect( pBundle, 2 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM14_CH1", 16 );
				REL_B_TM[i].Connect( pBundle, 9 );
				RDY_B_TM[i].Connect( pBundle, 11 );

				pBundle = BundleManager()->CreateBundle( "MDM_OF1_IOM4_CH1", 16 );
				LAT_B_TM[i].Connect( pBundle, 0 );
			}
		}
	}

	AddMesh();
	CalcUmbilicalAnimation();// update animation positions with scenario values
	DefineAnimations();
	DefineLatchAnimations();
	return;
}

void ASE_IUS::GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_longeron3, unsigned short& PLID_keel, bool& aftlocation, bool& Reversed_longeron1, bool& Reversed_longeron2, bool& Reversed_longeron3 ) const
{
	if (AftLocation)
	{
		PLID_longeron1 = 283;
		PLID_longeron2 = 307;
		PLID_longeron3 = 325;
		PLID_keel = 283;
		Reversed_longeron3 = true;
	}
	else
	{
		PLID_longeron1 = 269;
		PLID_longeron2 = 293;
		PLID_longeron3 = 311;
		PLID_keel = 269;
		Reversed_longeron3 = false;
	}

	aftlocation = AftLocation;

	Reversed_longeron1 = false;
	Reversed_longeron2 = false;
	return;
}

void ASE_IUS::OnPreStep( double simt, double simdt, double mjd )
{
	// panel inputs
	PyroBusPri = pPyroBusPriOn.IsSet() || (PyroBusPri && !pPyroBusPriOff.IsSet());
	PyroBusAlt = pPyroBusAltOn.IsSet() || (PyroBusAlt && !pPyroBusAltOff.IsSet());
	UmbilicalsEnaPri = pUmbilicalsEnaPriEnable.IsSet() || (UmbilicalsEnaPri && !pUmbilicalsEnaPriOff.IsSet());
	UmbilicalsEnaAlt = pUmbilicalsEnaAltEnable.IsSet() || (UmbilicalsEnaAlt && !pUmbilicalsEnaAltOff.IsSet());
	IUSDeploymentEnaPri = (pIUSDeploymentEnaPriEnable.IsSet() || (IUSDeploymentEnaPri && !pIUSDeploymentEnaPriOff.IsSet())) && PyroBusPri;
	IUSDeploymentEnaAlt = (pIUSDeploymentEnaAltEnable.IsSet() || (IUSDeploymentEnaAlt && !pIUSDeploymentEnaAltOff.IsSet())) && PyroBusAlt;

	TiltTableActuatorMotionPri1Lower = (pTiltTableActuatorMotionPri1Lower.IsSet() || TiltTableActuatorMotionPri1Lower) && (pTiltTableActuatorDriveEnablePri1Maximum.IsSet() || pTiltTableActuatorDriveEnablePri1Intermediate.IsSet());
	TiltTableActuatorMotionPri1Raise = (pTiltTableActuatorMotionPri1Raise.IsSet() || TiltTableActuatorMotionPri1Raise) && (pTiltTableActuatorDriveEnablePri1Maximum.IsSet() || pTiltTableActuatorDriveEnablePri1Intermediate.IsSet());
	TiltTableActuatorMotionAlt2Lower = (pTiltTableActuatorMotionAlt2Lower.IsSet() || TiltTableActuatorMotionAlt2Lower) && (pTiltTableActuatorDriveEnableAlt2Maximum.IsSet() || pTiltTableActuatorDriveEnableAlt2Intermediate.IsSet());
	TiltTableActuatorMotionAlt2Raise = (pTiltTableActuatorMotionAlt2Raise.IsSet() || TiltTableActuatorMotionAlt2Raise) && (pTiltTableActuatorDriveEnableAlt2Maximum.IsSet() || pTiltTableActuatorDriveEnableAlt2Intermediate.IsSet());

	bool rdy = (posTiltTable == ASE_IUS_TILT_TABLE_POS_0) && IsIUSAttached();
	// run latches
	for (int i = 0; i < 2; i++)
	{
		LatchState[i] = range( 0.0, LatchState[i] + (simdt * PL_LATCH_RATE * (MOTOR_1_PWR[i].GetVoltage() + MOTOR_2_PWR[i].GetVoltage())), 1.0 );

		// animation
		STS()->SetAnimation( animPRLAHook[i], LatchState[i] );

		// indications
		if (IND_A[i])
		{
			if (LatchState[i] == 0.0)
			{
				LAT_A[i].SetLine();
				LAT_A_TB[i].SetLine();
				LAT_A_TM[i].SetLine();
				REL_A[i].ResetLine();
				REL_A_TB[i].ResetLine();
				REL_A_TM[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LAT_A[i].ResetLine();
				LAT_A_TB[i].ResetLine();
				LAT_A_TM[i].ResetLine();
				REL_A[i].SetLine();
				REL_A_TB[i].SetLine();
				REL_A_TM[i].SetLine();
			}
			else
			{
				LAT_A[i].ResetLine();
				LAT_A_TB[i].ResetLine();
				LAT_A_TM[i].ResetLine();
				REL_A[i].ResetLine();
				REL_A_TB[i].ResetLine();
				REL_A_TM[i].ResetLine();
			}

			if (rdy)
			{
				RDY_A_TB[i].SetLine();
				RDY_A_TM[i].SetLine();
			}
			else
			{
				RDY_A_TB[i].ResetLine();
				RDY_A_TM[i].ResetLine();
			}
		}
		else
		{
			LAT_A[i].ResetLine();
			LAT_A_TB[i].ResetLine();
			LAT_A_TM[i].ResetLine();
			REL_A[i].ResetLine();
			REL_A_TB[i].ResetLine();
			REL_A_TM[i].ResetLine();
			RDY_A_TB[i].ResetLine();
			RDY_A_TM[i].ResetLine();
		}

		if (IND_B[i])
		{
			if (LatchState[i] == 0.0)
			{
				LAT_B[i].SetLine();
				LAT_B_TM[i].SetLine();
				REL_B[i].ResetLine();
				REL_B_TM[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LAT_B[i].ResetLine();
				LAT_B_TM[i].ResetLine();
				REL_B[i].SetLine();
				REL_B_TM[i].SetLine();
			}
			else
			{
				LAT_B[i].ResetLine();
				LAT_B_TM[i].ResetLine();
				REL_B[i].ResetLine();
				REL_B_TM[i].ResetLine();
			}

			if (rdy) RDY_B_TM[i].SetLine();
			else RDY_B_TM[i].ResetLine();
		}
		else
		{
			LAT_B[i].ResetLine();
			LAT_B_TM[i].ResetLine();
			REL_B[i].ResetLine();
			REL_B_TM[i].ResetLine();
			RDY_B_TM[i].ResetLine();
		}
	}

	// release umbilical
	if ((pUmbilicalsRelPriRelease.IsSet() & UmbilicalsEnaPri) | (pUmbilicalsRelAltRelease.IsSet() & UmbilicalsEnaAlt))
	{
		if (!umbilicalreleased)
		{
			posUmbilical = 0.122222;// back off 5º (+6º)
			RunAnimation();
			umbilicalreleased = true;
		}
	}

	// move tilt table
	double da = simdt * ASE_IUS_TILT_TABLE_SPEED * (
		(int)(TiltTableActuatorMotionPri1Raise | TiltTableActuatorMotionAlt2Raise) -
		(int)(TiltTableActuatorMotionPri1Lower | TiltTableActuatorMotionAlt2Lower));

	if (da > 0.0) // raise
	{
		if ((posTiltTable != ASE_IUS_TILT_TABLE_POS_0) || ((LatchState[0] + LatchState[1]) == 2.0) || !IsIUSAttached())// when closed, no motion with latches closed
		{
			posTiltTable = min(1.0, posTiltTable + da);
			CalcUmbilicalAnimation();
			RunAnimation();
		}
	}
	else if (da < 0.0)// lower
	{
		da = -da;
		if ((IsIUSAttached() == true) && ((posTiltTable - da) < ASE_IUS_TILT_TABLE_POS_0)) da = posTiltTable - ASE_IUS_TILT_TABLE_POS_0;// limit motion if IUS still attached
		posTiltTable = max(0.0, posTiltTable - da);
		CalcUmbilicalAnimation();
		RunAnimation();
	}

	// deploy IUS
	if ((pIUSDeploymentDpyPriDeploy.IsSet() & IUSDeploymentEnaPri) | (pIUSDeploymentDpyAltDeploy.IsSet() & IUSDeploymentEnaAlt))
	{
		// deploy ius
		STS()->DetachChild( hIUSattach, IUS_JETTISON_VELOCITY );
	}


	// check for actuator stop
	if (pTiltTableActuatorDriveEnablePri1Intermediate.IsSet())
	{
		if ((((posTiltTable >= ASE_IUS_TILT_TABLE_POS_28) && (oldposition < ASE_IUS_TILT_TABLE_POS_28)) ||
			((posTiltTable >= ASE_IUS_TILT_TABLE_POS_58) && (oldposition < ASE_IUS_TILT_TABLE_POS_58))) &&
			(TiltTableActuatorMotionPri1Raise)) TiltTableActuatorMotionPri1Raise = false;
		if ((oldposition >= ASE_IUS_TILT_TABLE_POS_28) && (posTiltTable < ASE_IUS_TILT_TABLE_POS_28) && (TiltTableActuatorMotionPri1Lower))
			TiltTableActuatorMotionPri1Lower = false;
	}
	if (pTiltTableActuatorDriveEnableAlt2Intermediate.IsSet())
	{
		if ((posTiltTable >= ASE_IUS_TILT_TABLE_POS_30) && (oldposition < ASE_IUS_TILT_TABLE_POS_30) && (TiltTableActuatorMotionAlt2Raise))
			TiltTableActuatorMotionAlt2Raise = false;
		if ((oldposition >= ASE_IUS_TILT_TABLE_POS_30) && (posTiltTable < ASE_IUS_TILT_TABLE_POS_30) && (TiltTableActuatorMotionAlt2Lower))
			TiltTableActuatorMotionAlt2Lower = false;
	}
	if ((posTiltTable == ASE_IUS_TILT_TABLE_POS_06) || (posTiltTable == ASE_IUS_TILT_TABLE_POS_61))
	{
		TiltTableActuatorMotionPri1Lower = false;
		TiltTableActuatorMotionPri1Raise = false;
		TiltTableActuatorMotionAlt2Lower = false;
		TiltTableActuatorMotionAlt2Raise = false;
	}
	oldposition = posTiltTable;


	// panel outputs
	pPyroBusPriTB.SetLine( (int)PyroBusPri * 5.0f );
	pPyroBusAltTB.SetLine( (int)PyroBusAlt * 5.0f );

	pUmbilicalsEnaPriTB.SetLine( (int)UmbilicalsEnaPri * 5.0f );
	pUmbilicalsEnaAltTB.SetLine( (int)UmbilicalsEnaAlt * 5.0f );

	pUmbilicalsRelPriTB.SetLine( (int)(umbilicalreleased & UmbilicalsEnaPri) * 5.0f );
	pUmbilicalsRelAltTB.SetLine( (int)(umbilicalreleased & UmbilicalsEnaAlt) * 5.0f );

	pIUSDeploymentEnaPriTB.SetLine( (int)IUSDeploymentEnaPri * 5.0f );
	pIUSDeploymentEnaAltTB.SetLine( (int)IUSDeploymentEnaAlt * 5.0f );

	pTiltTableActuatorMotionPri1TB.SetLine( (int)(TiltTableActuatorMotionPri1Lower | TiltTableActuatorMotionPri1Raise) * 5.0f );
	pTiltTableActuatorMotionAlt2TB.SetLine( (int)(TiltTableActuatorMotionAlt2Lower | TiltTableActuatorMotionAlt2Raise) * 5.0f );

	pTiltTableActuatorPositionPri1TB.SetLine( (int)(Eq( posTiltTable, ASE_IUS_TILT_TABLE_POS_0, 0.001 ) | Eq( posTiltTable, ASE_IUS_TILT_TABLE_POS_265, ASE_IUS_TILT_TABLE_DP ) | Eq( posTiltTable, ASE_IUS_TILT_TABLE_POS_57, ASE_IUS_TILT_TABLE_DP )) * 5.0f );
	pTiltTableActuatorPositionAlt2TB.SetLine( (int)(Eq( posTiltTable, ASE_IUS_TILT_TABLE_POS_0, 0.001 ) | Eq( posTiltTable, ASE_IUS_TILT_TABLE_POS_295, ASE_IUS_TILT_TABLE_DP ) | Eq( posTiltTable, ASE_IUS_TILT_TABLE_POS_595, ASE_IUS_TILT_TABLE_DP )) * 5.0f );
	return;
}

bool ASE_IUS::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "TILT_TABLE", 10 ))
	{
		sscanf_s( (char*)(line + 10), "%lf", &posTiltTable );
		posTiltTable = range( 0.0, posTiltTable, 1.0 );
		oldposition = posTiltTable;
		return true;
	}
	else if (!_strnicmp( line, "UMBILICAL", 9 ))
	{
		int tmp = 0;
		sscanf_s( (char*)(line + 9), "%d", &tmp );
		if (tmp == 0) umbilicalreleased = true;
		return true;
	}
	else if (!_strnicmp( line, "LATCHES", 7 ))
	{
		sscanf_s( line + 7, "%lf %lf", &LatchState[0], &LatchState[1] );
		return true;
	}
	else return false;
}

void ASE_IUS::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, "TILT_TABLE", posTiltTable );
	oapiWriteScenario_int( scn, "UMBILICAL", umbilicalreleased ? 0 : 1 );

	char cbuf[64];
	sprintf_s( cbuf, 64, "%lf %lf", LatchState[0], LatchState[1] );
	oapiWriteScenario_string( scn, "LATCHES", cbuf );
	return;
}

double ASE_IUS::GetSubsystemMass( void ) const
{
	return ASE_IUS_MASS;
}

void ASE_IUS::AddMesh( void )
{
	VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + ASEoffset;
	mesh_index = STS()->AddMesh( hMesh, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + (AftLocation ? PRLA_PORT_AFT_POS : PRLA_PORT_FWD_POS);
	mesh_idx_Latches[0] = STS()->AddMesh( hMesh_Latches[0], &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_Latches[0], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + (AftLocation ? PRLA_STBD_AFT_POS : PRLA_STBD_FWD_POS);
	mesh_idx_Latches[1] = STS()->AddMesh( hMesh_Latches[1], &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_Latches[1], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void ASE_IUS::DefineAnimations( void )
{
	/////// tilt table ///////
	static UINT TiltTable[13] = {
		GRP_AFT_ASE_TILT_FRAME_IUS_ASE,
		GRP_IUS_FRAME_TUBE_IUS_ASE,
		GRP_POWER_CONTROL_UNIT_IUS_ASE,
		GRP_BATTERY_1_IUS_ASE,
		GRP_BATTERY_2_IUS_ASE,
		GRP_BATTERY_3_IUS_ASE,
		GRP_SPACECRAFT_CONVERTER_REGULATOR_UNIT_IUS_ASE,
		GRP_IUS_CONVERTER_REGULATOR_UNIT_IUS_ASE,
		GRP_ASE_CONVERTER_REGULATOR_UNIT_IUS_ASE,
		GRP_ASE_ACTUATOR_CONTROLLER_A_IUS_ASE,
		GRP_ASE_ACTUATOR_CONTROLLER_B_IUS_ASE,
		GRP_IUS_UMBILICAL_BOOM_FIXED_IUS_ASE,
		GRP_IUS_UMBILICAL_BOOM_PIVOT_CYLINDER_IUS_ASE
	};
	MGROUP_ROTATE* TiltTable_Rotate = new MGROUP_ROTATE( mesh_index, TiltTable, 13, ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS, IUS_ROTATION_AXIS, static_cast<float>(67.0 * RAD) );
	animTiltTable = STS()->CreateAnimation( ASE_IUS_TILT_TABLE_POS_0 );// 0º position
	ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( animTiltTable, 0, 1, TiltTable_Rotate );
	SaveAnimation( TiltTable_Rotate );

	/////// umbilical ///////
	static UINT Umbilical[4] = {
		GRP_IUS_UMBILICAL_BOOM_MOVING_IUS_ASE,
		GRP_IUS_UMBILICAL_BOOM_FOIL_IUS_ASE,
		GRP_IUS_UMBILICAL_BOOM_PLUG1_IUS_ASE,
		GRP_IUS_UMBILICAL_BOOM_PLUG2_IUS_ASE
	};
	MGROUP_ROTATE* Umbilical_Rotate = new MGROUP_ROTATE( mesh_index, Umbilical, 4, ASE_IUS_UMBILICAL_ROTATION_AXIS_POS, _V( 1, 0, 0 ), static_cast<float>(PI05) );
	animUmbilical = STS()->CreateAnimation( 0.066667 );
	STS()->AddAnimationComponent( animUmbilical, 0, 1, Umbilical_Rotate, parent );
	STS()->SetAnimation( animUmbilical, posUmbilical );
	SaveAnimation( Umbilical_Rotate );
	return;
}

void ASE_IUS::DefineLatchAnimations( void )
{
	// port
	static UINT HookPort_Grp = {0};
	MGROUP_ROTATE* PRLAPortHook = new MGROUP_ROTATE( mesh_idx_Latches[0], &HookPort_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
	animPRLAHook[0] = STS()->CreateAnimation( 0.0 );// closed position
	STS()->SetAnimation( animPRLAHook[0], LatchState[0] );// loaded position from scenario
	STS()->AddAnimationComponent( animPRLAHook[0], 0.0, 1.0, PRLAPortHook );
	SaveAnimation( PRLAPortHook );

	// starboard
	static UINT HookStbd_Grp = {0};
	MGROUP_ROTATE* PRLAStbdHook = new MGROUP_ROTATE( mesh_idx_Latches[1], &HookStbd_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
	animPRLAHook[1] = STS()->CreateAnimation( 0.0 );// closed position
	STS()->SetAnimation( animPRLAHook[1], LatchState[1] );// loaded position from scenario
	STS()->AddAnimationComponent( animPRLAHook[1], 0.0, 1.0, PRLAStbdHook );
	SaveAnimation( PRLAStbdHook );
	return;
}

void ASE_IUS::CreateAttachment( void )
{
	if (hIUSattach == NULL)
	{
		hIUSattach = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + IUSattachoffset, IUS_ATTACHMENT_DIR, IUS_ATTACHMENT_ROT, "SSV_ASE" );
	}
	return;
}

void ASE_IUS::UpdateAttachment( void )
{
	CalcUmbilicalAnimation();
	RunAnimation();
	return;
}

bool ASE_IUS::IsIUSAttached( void ) const
{
	return (STS()->GetAttachmentStatus( hIUSattach ) != NULL);
}

void ASE_IUS::CalcUmbilicalAnimation( void )
{
	if (umbilicalreleased)// "restrict" umbilical movement
	{
		if (posTiltTable < 0.17)
		{
			posUmbilical = posTiltTable * 0.744444;// 67/90
		}
		else if (posTiltTable > 0.548955)
		{
			const double yt = 1.35;
			const double lu = 1.5;
			const double ru = sqrt( pow( ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS.y - ASE_IUS_UMBILICAL_ROTATION_AXIS_POS.y, 2 ) + pow( ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS.z - ASE_IUS_UMBILICAL_ROTATION_AXIS_POS.z, 2 ) );
			const double ang0 = asin( (ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS.y - ASE_IUS_UMBILICAL_ROTATION_AXIS_POS.y) / ru );

			double angleTT = posTiltTable * 67.0;
			double yu = ru * sin( ang0 - (angleTT * RAD) );
			double angleUmb = asin( (yt - yu) / lu ) * DEG;
			posUmbilical = (angleUmb - 6.0) / 90.0;
		}
		else posUmbilical = 0.122222;// back off 5º (+6º)
	}
	else if (posTiltTable >= 0.548955)// forcefull umbilical release
	{
		posUmbilical = 0.122222;// back off 5º (+6º)
		umbilicalreleased = true;
	}
	return;
}

void ASE_IUS::RunAnimation( void )
{
	STS()->SetAnimation( animTiltTable, posTiltTable );
	STS()->SetAnimation( animUmbilical, posUmbilical );

	// calc attachment data
	MATRIX3 mrot = rotm( IUS_ROTATION_AXIS, (posTiltTable - ASE_IUS_TILT_TABLE_POS_0) * static_cast<float>(67.0 * RAD) );
	VECTOR3 attpos = mul( mrot, IUSattachoffset - (ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS + ASEoffset) ) + (ASE_IUS_TILT_TABLE_ROTATION_AXIS_POS + ASEoffset);
	VECTOR3 attdir = mul( mrot, IUS_ATTACHMENT_DIR );
	VECTOR3 attrot = mul( mrot, IUS_ATTACHMENT_ROT );
	STS()->SetAttachmentParams( hIUSattach, attpos + STS()->GetOrbiterCoGOffset(), attdir, attrot );
	return;
}