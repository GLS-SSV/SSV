/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/17   GLS
2020/08/19   GLS
2020/08/21   GLS
2020/08/24   GLS
2020/08/25   GLS
2020/08/27   GLS
2020/09/01   GLS
2020/09/04   GLS
2020/09/12   GLS
2020/10/07   GLS
2021/01/19   GLS
2021/01/20   GLS
2021/06/16   GLS
2021/06/18   GLS
2021/06/30   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2021/12/31   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/04/29   GLS
2022/08/05   GLS
2023/02/06   GLS
2023/06/25   GLS
********************************************/
#include "CISS.h"
#include "Atlantis.h"
#include "meshres_CISS_Common.h"
#include "PRLA_defs.h"
#include <MathSSV.h>


const static char* MESHNAME_CISS = "SSV\\OV\\CISS_Common";
const static char* MESHNAME_CISS_G = "SSV\\OV\\CISS_CentaurG";
const static char* MESHNAME_CISS_GPRIME = "SSV\\OV\\CISS_CentaurG_Prime";
const static char* MESHNAME_CISS_MISSION_KIT = "SSV\\OV\\Centaur_Mission_Kit_plumbing";


constexpr double CISS_G_EMPTY_MASS = 3832.856;// Kg
constexpr double CISS_GPRIME_EMPTY_MASS = 4036.972;// Kg

constexpr VECTOR3 CISS_OFFSET = { 0.0, -0.4271, -7.1935 };
constexpr VECTOR3 CISS_MISSION_KIT_OFFSET = { 0.0, 0.0, 0.0 };

const VECTOR3 CENTAUR_ATTACHMENT_OFFSET = _V( 0.0, 0.0, 0.80737 )/*in mesh*/ + CISS_OFFSET;
constexpr VECTOR3 CENTAUR_ATTACHMENT_DIR = { 0.0, 0.0, 1.0 };
constexpr VECTOR3 CENTAUR_ATTACHMENT_ROT = { 0.0, 1.0, 0.0 };

constexpr VECTOR3 CISS_ROTATION_AXIS = { -1.0, 0.0, 0.0 };

constexpr VECTOR3 CISS_P1 = { 0.0, 0.0, 0.0 };// DA rotation axis
constexpr VECTOR3 CISS_P2 = { 0.0, 1.16475, -0.1403 };// motor crank rotation axis
constexpr VECTOR3 CISS_P3 = { 0.0, 1.07494, -0.60239 };// motor crank/link rotation axis
constexpr VECTOR3 CISS_P4 = { 0.0, 0.77744, -1.16606 };// link rotation axis
constexpr VECTOR3 CISS_P5 = { 0.0, 0.796885, 0.63045 };// LOX first bellow (from disconnect)
constexpr VECTOR3 CISS_P6 = { 0.0, 0.796885, -0.03369 };// LOX second bellow (from disconnect)
constexpr VECTOR3 CISS_P7 = { 0.0, -0.870386, -0.020695 };// LOX third bellow (from disconnect)
constexpr VECTOR3 CISS_P8 = { 0.0, 0.610955, 0.63045 };// GOX first bellow (from disconnect)
constexpr VECTOR3 CISS_P9 = { 0.0, 0.610955, -0.02585 };// GOX second bellow (from disconnect)
constexpr VECTOR3 CISS_P10 = { 0.0, -0.553796, 0.030035 };// GOX third bellow (from disconnect)
constexpr VECTOR3 CISS_P11 = { 0.0, 0.796885, 0.63045 };// LH2 first bellow (from disconnect)
constexpr VECTOR3 CISS_P12 = { 0.0, 0.796885, -0.03369 };// LH2 second bellow (from disconnect)
constexpr VECTOR3 CISS_P13 = { 0.0, -0.870386, -0.020695 };// LH2 third bellow (from disconnect)
constexpr VECTOR3 CISS_P14 = { 0.0, 0.610955, 0.63045 };// GH2 first bellow (from disconnect)
constexpr VECTOR3 CISS_P15 = { 0.0, 0.610955, -0.02585 };// GH2 second bellow (from disconnect)
constexpr VECTOR3 CISS_P16 = { 0.0, -0.553796, 0.030035 };// GH2 third bellow (from disconnect)

constexpr double CISS_MOTOR_ROTATION_RATE = 0.00333333;// motor rotation rate [1/s]
const double CISS_MOTOR_ROTATION_RANGE = 190.0 * RAD;// range of motor rotation [rad]


constexpr unsigned int BELLOW_nVTX = 72;// full group count
constexpr unsigned int BELLOW_FACE_nVTX = 36;// half of BELLOW_nVTX
constexpr unsigned int BELLOW_FACE_1_VTX[BELLOW_FACE_nVTX] = {
	0, 2, 4, 5, 6, 7, 9, 10, 13, 16,
	17, 19, 22, 25, 27, 29, 32, 35, 36, 39,
	42, 44, 46, 49, 52, 54, 55, 58, 61, 62,
	64, 65, 66, 67, 69, 71};// list of bellow face vertexes (order has to be the same for all bellows)
constexpr unsigned int BELLOW_FACE_2_VTX[BELLOW_FACE_nVTX] = {
	1, 3, 8, 11, 12, 14, 15, 18, 20, 21,
	23, 24, 26, 28, 30, 31, 33, 34, 37, 38,
	40, 41, 43, 45, 47, 48, 50, 51, 53, 56,
	57, 59, 60, 63, 68, 70};// list of bellow face vertexes (order has to be the same for all bellows)



constexpr VECTOR3 LATCHES_G_POS = { 0.0, 0.0, 24.239 - (1065.07 * IN2M) };
constexpr VECTOR3 LATCHES_GPRIME_POS = { 0.0, 0.0, 24.239 - (950.5 * IN2M) };


CISS::CISS( AtlantisSubsystemDirector* _director, bool isGPrime, const struct mission::Latches* latches ):AtlantisSubsystem( _director, "CISS" )
{
	this->isGPrime = isGPrime;
	memcpy( &this->latches, latches, sizeof(struct mission::Latches) * 3 );

	bMECH_PRI_PWR = false;
	bMECH_BKUP_PWR = false;
	bDA_PRI_UP = false;
	bDA_PRI_DN = false;
	bDA_BKUP_UP = false;
	bDA_BKUP_DN = false;
	bSUPER_ZIP_FIRE = false;

	LatchState[0] = 0.0;
	LatchState[1] = 0.0;
	LatchState[2] = 0.0;

	grs[0].nVtx = 0;
	posDAold = -1.0;

	posDA = 0.0;
	posmotorcrank = 0.0;
	poslink = 0.0;
	poslox_a = 0.0;
	poslox_b = 0.0;
	posgox_a = 0.0;
	posgox_b = 0.0;
	poslh2_a = 0.0;
	poslh2_b = 0.0;
	posgh2_a = 0.0;
	posgh2_b = 0.0;

	hMesh = oapiLoadMeshGlobal( MESHNAME_CISS );
	hMesh_Specific = oapiLoadMeshGlobal( isGPrime ? MESHNAME_CISS_GPRIME : MESHNAME_CISS_G );
	hMesh_MK = oapiLoadMeshGlobal( MESHNAME_CISS_MISSION_KIT );
	hMesh_Latches[0] = oapiLoadMeshGlobal( MESHNAME_PRLA_STBD_ACTIVE );
	hMesh_Latches[1] = oapiLoadMeshGlobal( MESHNAME_PRLA_PORT_ACTIVE );
	hMesh_Latches[2] = oapiLoadMeshGlobal( MESHNAME_AKA_FWD );

	r1 = sqrt( pow( CISS_P4.z - CISS_P1.z, 2 ) + pow( CISS_P4.y - CISS_P1.y, 2 ) );
	theta1o = atan2( CISS_P4.y - CISS_P1.y, CISS_P1.z - CISS_P4.z );
	double r2 = sqrt( pow( CISS_P2.z - CISS_P1.z, 2 ) + pow( CISS_P2.y - CISS_P1.y, 2 ) );
	double theta2 = atan2( CISS_P2.y - CISS_P1.y, CISS_P1.z - CISS_P2.z );
	x2 = r2 * cos( theta2 );
	y2 = r2 * sin( theta2 );
	r3 = sqrt( pow( CISS_P3.z - CISS_P2.z, 2 ) + pow( CISS_P3.y - CISS_P2.y, 2 ) );
	theta3o = atan2( CISS_P3.y - CISS_P2.y, CISS_P2.z - CISS_P3.z );
	r4 = sqrt( pow( CISS_P4.z - CISS_P3.z, 2 ) + pow( CISS_P4.y - CISS_P3.y, 2 ) );
	theta4o = atan2( CISS_P4.y - CISS_P3.y, CISS_P3.z - CISS_P4.z ) + PI;

	double r7 = sqrt( pow( CISS_P7.z - CISS_P1.z, 2 ) + pow( CISS_P7.y - CISS_P1.y, 2 ) );
	double theta7 = atan2( CISS_P7.y - CISS_P1.y, CISS_P1.z - CISS_P7.z );
	x7 = r7 * cos( theta7 );
	y7 = r7 * sin( theta7 );
	r2_5 = sqrt( pow( CISS_P5.z - CISS_P1.z, 2 ) + pow( CISS_P5.y - CISS_P1.y, 2 ) );
	theta2_5o = atan2( CISS_P5.y - CISS_P1.y, CISS_P1.z - CISS_P5.z );
	r5 = sqrt( pow( CISS_P6.z - CISS_P5.z, 2 ) + pow( CISS_P6.y - CISS_P5.y, 2 ) );
	theta5o = atan2( CISS_P6.y - CISS_P5.y, CISS_P5.z - CISS_P6.z );
	r6 = sqrt( pow( CISS_P6.z - CISS_P7.z, 2 ) + pow( CISS_P6.y - CISS_P7.y, 2 ) );
	theta6o = atan2( CISS_P6.y - CISS_P7.y, CISS_P7.z - CISS_P6.z );

	double r10 = sqrt( pow( CISS_P10.z - CISS_P1.z, 2 ) + pow( CISS_P10.y - CISS_P1.y, 2 ) );
	double theta10 = atan2( CISS_P10.y - CISS_P1.y, CISS_P1.z - CISS_P10.z );
	x10 = r10 * cos( theta10 );
	y10 = r10 * sin( theta10 );
	r2_8 = sqrt( pow( CISS_P8.z - CISS_P1.z, 2 ) + pow( CISS_P8.y - CISS_P1.y, 2 ) );
	theta2_8o = atan2( CISS_P8.y - CISS_P1.y, CISS_P1.z - CISS_P8.z );
	r8 = sqrt( pow( CISS_P9.z - CISS_P8.z, 2 ) + pow( CISS_P9.y - CISS_P8.y, 2 ) );
	theta8o = atan2( CISS_P9.y - CISS_P8.y, CISS_P8.z - CISS_P9.z );
	r9 = sqrt( pow( CISS_P9.z - CISS_P10.z, 2 ) + pow( CISS_P9.y - CISS_P10.y, 2 ) );
	theta9o = atan2( CISS_P9.y - CISS_P10.y, CISS_P10.z - CISS_P9.z );

	double r13 = sqrt( pow( CISS_P13.z - CISS_P1.z, 2 ) + pow( CISS_P13.y - CISS_P1.y, 2 ) );
	double theta13 = atan2( CISS_P13.y - CISS_P1.y, CISS_P1.z - CISS_P13.z );
	x13 = r13 * cos( theta13 );
	y13 = r13 * sin( theta13 );
	r2_11 = sqrt( pow( CISS_P11.z - CISS_P1.z, 2 ) + pow( CISS_P11.y - CISS_P1.y, 2 ) );
	theta2_11o = atan2( CISS_P11.y - CISS_P1.y, CISS_P1.z - CISS_P11.z );
	r11 = sqrt( pow( CISS_P12.z - CISS_P11.z, 2 ) + pow( CISS_P12.y - CISS_P11.y, 2 ) );
	theta11o = atan2( CISS_P12.y - CISS_P11.y, CISS_P11.z - CISS_P12.z );
	r12 = sqrt( pow( CISS_P12.z - CISS_P13.z, 2 ) + pow( CISS_P12.y - CISS_P13.y, 2 ) );
	theta12o = atan2( CISS_P12.y - CISS_P13.y, CISS_P13.z - CISS_P12.z );

	double r16 = sqrt( pow( CISS_P16.z - CISS_P1.z, 2 ) + pow( CISS_P16.y - CISS_P1.y, 2 ) );
	double theta16 = atan2( CISS_P16.y - CISS_P1.y, CISS_P1.z - CISS_P16.z );
	x16 = r16 * cos( theta16 );
	y16 = r16 * sin( theta16 );
	r2_14 = sqrt( pow( CISS_P14.z - CISS_P1.z, 2 ) + pow( CISS_P14.y - CISS_P1.y, 2 ) );
	theta2_14o = atan2( CISS_P14.y - CISS_P1.y, CISS_P1.z - CISS_P14.z );
	r14 = sqrt( pow( CISS_P15.z - CISS_P14.z, 2 ) + pow( CISS_P15.y - CISS_P14.y, 2 ) );
	theta14o = atan2( CISS_P15.y - CISS_P14.y, CISS_P14.z - CISS_P15.z );
	r15 = sqrt( pow( CISS_P15.z - CISS_P16.z, 2 ) + pow( CISS_P15.y - CISS_P16.y, 2 ) );
	theta15o = atan2( CISS_P15.y - CISS_P16.y, CISS_P16.z - CISS_P15.z );

	ahToCentaur = NULL;
}

CISS::~CISS( void )
{
	if (grs[0].nVtx != 0)
		for (int i = 0; i < 12; i++)
			delete[] grs[i].Vtx;
	return;
}

void CISS::Realize( void )
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle( "L12UtoCISS_PRI", 16 );
	pSUPER_ZIP_PRI_FIRE.Connect( pBundle, 0 );
	pSUPER_ZIP_PRI_ARM_ARM.Connect( pBundle, 1 );
	pSUPER_ZIP_PRI_ARM_TB.Connect( pBundle, 2 );
	pDA_PRI_ROT_DN.Connect( pBundle, 3 );
	pDA_PRI_ROT_UP.Connect( pBundle, 4 );
	pPosition_PRI_TB.Connect( pBundle, 5 );
	pLOGIC_PRI_PWR_ON.Connect( pBundle, 6 );
	pSSP_PRI_PWR_ON.Connect( pBundle, 7 );
	pMECH_PRI_PWR_OFF.Connect( pBundle, 8 );
	pMECH_PRI_PWR_ON.Connect( pBundle, 9 );
	pMECH_PRI_PWR_TB.Connect( pBundle, 10 );

	pBundle = BundleManager()->CreateBundle( "L12UtoCISS_BKUP", 16 );
	pSUPER_ZIP_BKUP_FIRE.Connect( pBundle, 0 );
	pSUPER_ZIP_BKUP_ARM_ARM.Connect( pBundle, 1 );
	pSUPER_ZIP_BKUP_ARM_TB.Connect( pBundle, 2 );
	pDA_BKUP_ROT_DN.Connect( pBundle, 3 );
	pDA_BKUP_ROT_UP.Connect( pBundle, 4 );
	pPosition_BKUP_TB.Connect( pBundle, 5 );
	pLOGIC_BKUP_PWR_ON.Connect( pBundle, 6 );
	pSSP_BKUP_PWR_ON.Connect( pBundle, 7 );
	pMECH_BKUP_PWR_OFF.Connect( pBundle, 8 );
	pMECH_BKUP_PWR_ON.Connect( pBundle, 9 );
	pMECH_BKUP_PWR_TB.Connect( pBundle, 10 );

	for (int i = 0; i < 3; i++)
	{
		string str = "PL_" + std::to_string( latches[i].PL ) + "_SEL_LATCH_" + std::to_string( latches[i].Latch );
		pBundle = BundleManager()->CreateBundle( str, 10 );
		LAT_A[i].Connect( pBundle, 0 );
		REL_A[i].Connect( pBundle, 1 );
		RDY_A[i].Connect( pBundle, 2 );
		MOTOR_1_PWR[i].Connect( pBundle, 3 );
		IND_A[i].Connect( pBundle, 4 );
		LAT_B[i].Connect( pBundle, 5 );
		REL_B[i].Connect( pBundle, 6 );
		RDY_B[i].Connect( pBundle, 7 );
		MOTOR_2_PWR[i].Connect( pBundle, 8 );
		IND_B[i].Connect( pBundle, 9 );
	}

	AddMesh();
	CalcAnimation();// update animation positions with scenario values
	DefineAnimations();
	DefineLatchAnimations();

	STS()->RegisterAnimation();
	return;
}

void CISS::OnPreStep( double simt, double simdt, double mjd )
{
	// inputs
	if (pSSP_PRI_PWR_ON.IsSet())
	{
		bMECH_PRI_PWR = pMECH_PRI_PWR_ON.IsSet() || (bMECH_PRI_PWR && !pMECH_PRI_PWR_OFF.IsSet());

		bDA_PRI_UP = (pDA_PRI_ROT_UP.IsSet() || bDA_PRI_UP) && (pLOGIC_PRI_PWR_ON.IsSet() && bMECH_PRI_PWR);
		bDA_PRI_DN = (pDA_PRI_ROT_DN.IsSet() || bDA_PRI_DN) && (pLOGIC_PRI_PWR_ON.IsSet() && bMECH_PRI_PWR);

		bSUPER_ZIP_FIRE = bSUPER_ZIP_FIRE || (pSUPER_ZIP_PRI_FIRE.IsSet() & pSUPER_ZIP_PRI_ARM_ARM.IsSet());
	}
	if (pSSP_BKUP_PWR_ON.IsSet())
	{
		bMECH_BKUP_PWR = pMECH_BKUP_PWR_ON.IsSet() || (bMECH_BKUP_PWR && !pMECH_BKUP_PWR_OFF.IsSet());

		bDA_BKUP_UP = (pDA_BKUP_ROT_UP.IsSet() || bDA_BKUP_UP) && (pLOGIC_BKUP_PWR_ON.IsSet() && bMECH_BKUP_PWR);
		bDA_BKUP_DN = (pDA_BKUP_ROT_DN.IsSet() || bDA_BKUP_DN) && (pLOGIC_BKUP_PWR_ON.IsSet() && bMECH_BKUP_PWR);

		bSUPER_ZIP_FIRE = bSUPER_ZIP_FIRE || (pSUPER_ZIP_BKUP_FIRE.IsSet() && pSUPER_ZIP_BKUP_ARM_ARM.IsSet());
	}

	bool rdy = (posmotorcrank == 0.0) && IsCentaurAttached();

	// run latches
	for (int i = 0; i < 3; i++)
	{
		LatchState[i] = range( 0.0, LatchState[i] + (simdt * PL_LATCH_RATE * (MOTOR_1_PWR[i].GetVoltage() + MOTOR_2_PWR[i].GetVoltage())), 1.0 );

		// animation
		STS()->SetAnimation( animLatches[i], LatchState[i] );

		// indications
		if (IND_A[i])
		{
			if (LatchState[i] == 0.0)
			{
				LAT_A[i].SetLine();
				REL_A[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LAT_A[i].ResetLine();
				REL_A[i].SetLine();
			}
			else
			{
				LAT_A[i].ResetLine();
				REL_A[i].ResetLine();
			}

			if (rdy) RDY_A[i].SetLine();
			else RDY_A[i].ResetLine();
		}
		else
		{
			LAT_A[i].ResetLine();
			REL_A[i].ResetLine();
			RDY_A[i].ResetLine();
		}

		if (IND_B[i])
		{
			if (LatchState[i] == 0.0)
			{
				LAT_B[i].SetLine();
				REL_B[i].ResetLine();
			}
			else if (LatchState[i] == 1.0)
			{
				LAT_B[i].ResetLine();
				REL_B[i].SetLine();
			}
			else
			{
				LAT_B[i].ResetLine();
				REL_B[i].ResetLine();
			}

			if (rdy) RDY_B[i].SetLine();
			else RDY_B[i].ResetLine();
		}
		else
		{
			LAT_B[i].ResetLine();
			REL_B[i].ResetLine();
			RDY_B[i].ResetLine();
		}
	}

	// table rotation
	double da = simdt * CISS_MOTOR_ROTATION_RATE * ((int)(bDA_PRI_UP | bDA_BKUP_UP) - (int)(bDA_PRI_DN | bDA_BKUP_DN));
	if (da > 0.0)
	{
		if ((posmotorcrank != 0.0) || ((LatchState[0] + LatchState[1] + LatchState[2]) == 3.0) || !IsCentaurAttached())// when closed, no motion with latches closed
		{
			posmotorcrank = min(1.0, posmotorcrank + da);
			CalcAnimation();
			RunAnimation();

			if (posmotorcrank == 1.0)
			{
				bDA_PRI_UP = false;
				bDA_BKUP_UP = false;
			}
		}
	}
	else if (da < 0.0)
	{
		posmotorcrank = max(0.0, posmotorcrank + da);
		CalcAnimation();
		RunAnimation();

		if (posmotorcrank == 0.0)
		{
			bDA_PRI_DN = false;
			bDA_BKUP_DN = false;
		}
	}

	// release
	if (bSUPER_ZIP_FIRE) STS()->DetachChild( ahToCentaur, 0.3 );

	// outputs
	if (pSSP_PRI_PWR_ON.IsSet())
	{
		pSUPER_ZIP_PRI_ARM_TB.SetLine( (int)pSUPER_ZIP_PRI_ARM_ARM * 5.0f );
		if ((posmotorcrank == 1) || (posmotorcrank == 0)) pPosition_PRI_TB.SetLine();
		else pPosition_PRI_TB.ResetLine();
		pMECH_PRI_PWR_TB.SetLine( (int)bMECH_PRI_PWR * 5.0f );
	}
	else
	{
		pSUPER_ZIP_PRI_ARM_TB.ResetLine();
		pPosition_PRI_TB.ResetLine();
		pMECH_PRI_PWR_TB.ResetLine();
	}
	if (pSSP_BKUP_PWR_ON.IsSet())
	{
		pSUPER_ZIP_BKUP_ARM_TB.SetLine( (int)pSUPER_ZIP_BKUP_ARM_ARM * 5.0f );
		if ((posmotorcrank == 1) || (posmotorcrank == 0)) pPosition_BKUP_TB.SetLine();
		else pPosition_BKUP_TB.ResetLine();
		pMECH_BKUP_PWR_TB.SetLine( (int)bMECH_BKUP_PWR * 5.0f );
	}
	else
	{
		pSUPER_ZIP_BKUP_ARM_TB.ResetLine();
		pPosition_BKUP_TB.ResetLine();
		pMECH_BKUP_PWR_TB.ResetLine();
	}
	return;
}

bool CISS::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "MOTOR", 5 ))
	{
		sscanf_s( (char*)(line + 5), "%lf", &posmotorcrank );
		return true;
	}
	else if (!_strnicmp( line, "LATCHES", 7 ))
	{
		sscanf_s( line + 7, "%lf %lf %lf", &LatchState[0], &LatchState[1], &LatchState[2] );
		return true;
	}
	else return false;
}

void CISS::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float(scn, "MOTOR", posmotorcrank);

	char cbuf[64];
	sprintf_s( cbuf, 64, "%lf %lf %lf", LatchState[0], LatchState[1], LatchState[2] );
	oapiWriteScenario_string( scn, "LATCHES", cbuf );
	return;
}

double CISS::GetSubsystemMass( void ) const
{
	if (isGPrime) return CISS_GPRIME_EMPTY_MASS;
	else return CISS_G_EMPTY_MASS;
}

void CISS::Animate( void )
{
	if (posDA == posDAold) return;// only run when needed
	posDAold = posDA;

	VECTOR3 v;
	VECTOR3 n;
	int k = 0;
	DEVMESHHANDLE hDevMesh = STS()->GetDevMesh( STS()->Get_vis(), mesh_idx );

	if (grs[0].nVtx == 0)// first run only
	{
		// save (original) group data
		for (int i = 0; i < 12; i++)
		{
			grs[i].nVtx = BELLOW_nVTX;
			grs[i].Vtx = new NTVERTEX[BELLOW_nVTX];
			grs[i].nIdx = 0;
			grs[i].Idx = NULL;
			grs[i].VtxPerm = NULL;
			grs[i].IdxPerm = NULL;
			grs[i].TexIdx = 0;
		}
		oapiGetMeshGroup( hDevMesh, GRP_LOX_DUCT_BELLOW3_CISS, &grs[0] );
		oapiGetMeshGroup( hDevMesh, GRP_LOX_DUCT_BELLOW2_CISS, &grs[1] );
		oapiGetMeshGroup( hDevMesh, GRP_LOX_DUCT_BELLOW1_CISS, &grs[2] );
		oapiGetMeshGroup( hDevMesh, GRP_GOX_DUCT_BELLOW3_CISS, &grs[3] );
		oapiGetMeshGroup( hDevMesh, GRP_GOX_DUCT_BELLOW2_CISS, &grs[4] );
		oapiGetMeshGroup( hDevMesh, GRP_GOX_DUCT_BELLOW1_CISS, &grs[5] );
		oapiGetMeshGroup( hDevMesh, GRP_LH2_DUCT_BELLOW3_CISS, &grs[6] );
		oapiGetMeshGroup( hDevMesh, GRP_LH2_DUCT_BELLOW2_CISS, &grs[7] );
		oapiGetMeshGroup( hDevMesh, GRP_LH2_DUCT_BELLOW1_CISS, &grs[8] );
		oapiGetMeshGroup( hDevMesh, GRP_GH2_DUCT_BELLOW3_CISS, &grs[9] );
		oapiGetMeshGroup( hDevMesh, GRP_GH2_DUCT_BELLOW2_CISS, &grs[10] );
		oapiGetMeshGroup( hDevMesh, GRP_GH2_DUCT_BELLOW1_CISS, &grs[11] );
	}

	GROUPEDITSPEC ges;
	ges.flags = GRPEDIT_VTXCRD | GRPEDIT_VTXNML;
	ges.vIdx = NULL;
	ges.Vtx = new NTVERTEX[BELLOW_nVTX];
	ges.nVtx = BELLOW_nVTX;

	MATRIX3 mrotP1 = rotm( _V( -1.0, 0.0, 0.0 ), posDA * PI2 );
	MATRIX3 mrotP5 = rotm( _V( 1.0, 0.0, 0.0 ), poslox_a * PI2 );
	MATRIX3 mrotP6 = rotm( _V( -1.0, 0.0, 0.0 ), (poslox_a + poslox_b - posDA) * PI2 );
	MATRIX3 mrotP7 = rotm( _V( -1.0, 0.0, 0.0 ), poslox_b * PI2 * 0.5 );
	MATRIX3 mrotP8 = rotm( _V( 1.0, 0.0, 0.0 ), posgox_a * PI2 );
	MATRIX3 mrotP9 = rotm( _V( -1.0, 0.0, 0.0 ), (posgox_a + posgox_b - posDA) * PI2 );
	MATRIX3 mrotP10 = rotm( _V( -1.0, 0.0, 0.0 ), posgox_b * PI2 * 0.5 );
	MATRIX3 mrotP11 = rotm( _V( 1.0, 0.0, 0.0 ), poslh2_a * PI2 );
	MATRIX3 mrotP12 = rotm( _V( -1.0, 0.0, 0.0 ), (poslh2_a + poslh2_b - posDA) * PI2 );
	MATRIX3 mrotP13 = rotm( _V( -1.0, 0.0, 0.0 ), poslh2_b * PI2 * 0.5 );
	MATRIX3 mrotP14 = rotm( _V( 1.0, 0.0, 0.0 ), posgh2_a * PI2 );
	MATRIX3 mrotP15 = rotm( _V( -1.0, 0.0, 0.0 ), (posgh2_a + posgh2_b - posDA) * PI2 );
	MATRIX3 mrotP16 = rotm( _V( -1.0, 0.0, 0.0 ), posgh2_b * PI2 * 0.5 );

	/////// LOX first bellow ///////
	// rot P1
	memcpy( ges.Vtx, grs[0].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P5
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP5, v - CISS_P5 ) + CISS_P5;
		n = mul( mrotP5, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_LOX_DUCT_BELLOW3_CISS, &ges );


	/////// LOX second bellow ///////
	// rot P1
	// rot P5
	memcpy( ges.Vtx, grs[1].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP5, v - CISS_P5 ) + CISS_P5;
		n = mul( mrotP5, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P5
	// rot P6
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP6, v - CISS_P6 ) + CISS_P6;
		n = mul( mrotP6, n );

		v = mul( mrotP5, v - CISS_P5 ) + CISS_P5;
		n = mul( mrotP5, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_LOX_DUCT_BELLOW2_CISS, &ges );


	/////// LOX third bellow ///////
	// rot P7 (0.5)
	memcpy( ges.Vtx, grs[2].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP7, v - CISS_P7 ) + CISS_P7;
		n = mul( mrotP7, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_LOX_DUCT_BELLOW1_CISS, &ges );


	/////// GOX first bellow ///////
	// rot P1
	memcpy( ges.Vtx, grs[3].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P8
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP8, v - CISS_P8 ) + CISS_P8;
		n = mul( mrotP8, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_GOX_DUCT_BELLOW3_CISS, &ges );


	/////// GOX second bellow ///////
	// rot P1
	// rot P8
	memcpy( ges.Vtx, grs[4].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP8, v - CISS_P8 ) + CISS_P8;
		n = mul( mrotP8, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P8
	// rot P9
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP9, v - CISS_P9 ) + CISS_P9;
		n = mul( mrotP9, n );

		v = mul( mrotP8, v - CISS_P8 ) + CISS_P8;
		n = mul( mrotP8, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_GOX_DUCT_BELLOW2_CISS, &ges );


	/////// GOX third bellow ///////
	// rot P10 (0.5)
	memcpy( ges.Vtx, grs[5].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP10, v - CISS_P10 ) + CISS_P10;
		n = mul( mrotP10, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_GOX_DUCT_BELLOW1_CISS, &ges );


	/////// LH2 first bellow ///////
	// rot P1
	memcpy( ges.Vtx, grs[6].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P11
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP11, v - CISS_P11 ) + CISS_P11;
		n = mul( mrotP11, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_LH2_DUCT_BELLOW3_CISS, &ges );


	/////// LH2 second bellow ///////
	// rot P1
	// rot P11
	memcpy( ges.Vtx, grs[7].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP11, v - CISS_P11 ) + CISS_P11;
		n = mul( mrotP11, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P11
	// rot P12
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP12, v - CISS_P12 ) + CISS_P12;
		n = mul( mrotP12, n );

		v = mul( mrotP11, v - CISS_P11 ) + CISS_P11;
		n = mul( mrotP11, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_LH2_DUCT_BELLOW2_CISS, &ges );


	/////// LH2 third bellow ///////
	// rot P13 half
	memcpy( ges.Vtx, grs[8].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP13, v - CISS_P13 ) + CISS_P13;
		n = mul( mrotP13, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_LH2_DUCT_BELLOW1_CISS, &ges );


	/////// GH2 first bellow ///////
	// rot P1
	memcpy( ges.Vtx, grs[9].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P14
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP14, v - CISS_P14 ) + CISS_P14;
		n = mul( mrotP14, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_GH2_DUCT_BELLOW3_CISS, &ges );


	/////// GH2 second bellow ///////
	// rot P1
	// rot P14
	memcpy( ges.Vtx, grs[10].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP14, v - CISS_P14 ) + CISS_P14;
		n = mul( mrotP14, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	// rot P1
	// rot P14
	// rot P15
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_2_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP15, v - CISS_P15 ) + CISS_P15;
		n = mul( mrotP15, n );

		v = mul( mrotP14, v - CISS_P14 ) + CISS_P14;
		n = mul( mrotP14, n );

		v = mul( mrotP1, v - CISS_P1 ) + CISS_P1;
		n = mul( mrotP1, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_GH2_DUCT_BELLOW2_CISS, &ges );


	/////// GH2 third bellow ///////
	// rot P16 (0.5)
	memcpy( ges.Vtx, grs[11].Vtx, sizeof(NTVERTEX) * ges.nVtx );
	for (unsigned int i = 0; i < BELLOW_FACE_nVTX; i++)
	{
		k = BELLOW_FACE_1_VTX[i];
		v = _V( ges.Vtx[k].x, ges.Vtx[k].y, ges.Vtx[k].z );
		n = _V( ges.Vtx[k].nx, ges.Vtx[k].ny, ges.Vtx[k].nz );

		v = mul( mrotP16, v - CISS_P16 ) + CISS_P16;
		n = mul( mrotP16, n );

		ges.Vtx[k].x = static_cast<float>(v.x);
		ges.Vtx[k].y = static_cast<float>(v.y);
		ges.Vtx[k].z = static_cast<float>(v.z);

		ges.Vtx[k].nx = static_cast<float>(n.x);
		ges.Vtx[k].ny = static_cast<float>(n.y);
		ges.Vtx[k].nz = static_cast<float>(n.z);
	}
	oapiEditMeshGroup( hDevMesh, GRP_GH2_DUCT_BELLOW1_CISS, &ges );

	delete[] ges.Vtx;
	return;
}

void CISS::AddMesh( void )
{
	VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + CISS_OFFSET;
	mesh_idx = STS()->AddMesh( hMesh, &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	mesh_idx_specific = STS()->AddMesh( hMesh_Specific, &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_specific, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + CISS_MISSION_KIT_OFFSET;
	mesh_idx_MK = STS()->AddMesh( hMesh_MK, &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_MK, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	ofs = STS()->GetOrbiterCoGOffset() + (isGPrime ? LATCHES_GPRIME_POS : LATCHES_G_POS);
	mesh_idx_Latches[0] = STS()->AddMesh( hMesh_Latches[0], &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_Latches[0], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	mesh_idx_Latches[1] = STS()->AddMesh( hMesh_Latches[1], &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_Latches[1], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );

	mesh_idx_Latches[2] = STS()->AddMesh( hMesh_Latches[2], &ofs );
	STS()->SetMeshVisibilityMode( mesh_idx_Latches[2], MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void CISS::GetPLBInfo( unsigned short& PLID_longeron1, unsigned short& PLID_longeron2, unsigned short& PLID_keel, unsigned short& bay, bool& Reversed_longeron1, bool& Reversed_longeron2 ) const
{
	PLID_longeron2 = 323;
	PLID_keel = 311;

	if (isGPrime)
	{
		PLID_longeron1 = 297;
		bay = 7;
	}
	else
	{
		PLID_longeron1 = 305;
		bay = 9;
	}

	Reversed_longeron1 = true;
	Reversed_longeron2 = false;
	return;
}

void CISS::DefineAnimations( void )
{
	/////// tilt table ///////
	static UINT DA_GRP[10] = {GRP_DEPLOYMENT_ADAPTER_CISS,
		GRP_PROPELLANT_DISCONNECT_PANELS_CISS,
		GRP_LH2_PROPELLANT_DISCONNECT_CISS,
		GRP_GH2_PROPELLANT_DISCONNECT_CISS,
		GRP_LOX_PROPELLANT_DISCONNECT_CISS,
		GRP_GOX_PROPELLANT_DISCONNECT_CISS,
		GRP_LH2_FILL_DRAIN_SEGMENT3_CISS,
		GRP_GH2_VENT_SEGMENT3_CISS,
		GRP_LOX_FILL_DRAIN_SEGMENT3_CISS,
		GRP_GOX_VENT_SEGMENT3_CISS};
	anim_rotate = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* DA = new MGROUP_ROTATE( mesh_idx, DA_GRP, 10, CISS_P1, CISS_ROTATION_AXIS, static_cast<float>(PI2) );
	ANIMATIONCOMPONENT_HANDLE parent = STS()->AddAnimationComponent( anim_rotate, 0, 1, DA );
	SaveAnimation( DA );

	/////// motor crank ///////
	static UINT MOTORCRANK_GRP[1] = {GRP_DA_ROTATION_ARM_CISS};
	anim_motorcrank = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* MOTORCRANK = new MGROUP_ROTATE( mesh_idx, MOTORCRANK_GRP, 1, CISS_P2, _V( 1, 0, 0 ), static_cast<float>(CISS_MOTOR_ROTATION_RANGE) );
	STS()->AddAnimationComponent( anim_motorcrank, 0, 1, MOTORCRANK, parent );
	STS()->SetAnimation( anim_motorcrank, posmotorcrank );
	SaveAnimation( MOTORCRANK );

	/////// link ///////
	static UINT LINK_GRP[1] = {GRP_DA_ROTATION_LINK_CISS};
	anim_link = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* LINK = new MGROUP_ROTATE( mesh_idx, LINK_GRP, 1, CISS_P4, _V( -1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_link, 0, 1, LINK );
	STS()->SetAnimation( anim_link, poslink );
	SaveAnimation( LINK );

	/////// LOX A ///////
	static UINT LOX_A_GRP[1] = {GRP_LOX_FILL_DRAIN_SEGMENT2_CISS};
	anim_lox_a = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* LOX_A = new MGROUP_ROTATE( mesh_idx, LOX_A_GRP, 1, CISS_P5, _V( 1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_lox_a, 0, 1, LOX_A, parent );
	STS()->SetAnimation( anim_lox_a, poslox_a );
	SaveAnimation( LOX_A );

	/////// LOX B ///////
	static UINT LOX_B_GRP[1] = {GRP_LOX_FILL_DRAIN_SEGMENT1_CISS};
	anim_lox_b = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* LOX_B = new MGROUP_ROTATE( mesh_idx, LOX_B_GRP, 1, CISS_P7, _V( -1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_lox_b, 0, 1, LOX_B );
	STS()->SetAnimation( anim_lox_b, poslox_b );
	SaveAnimation( LOX_B );

	/////// GOX A ///////
	static UINT GOX_A_GRP[1] = {GRP_GOX_VENT_SEGMENT2_CISS};
	anim_gox_a = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* GOX_A = new MGROUP_ROTATE( mesh_idx, GOX_A_GRP, 1, CISS_P8, _V( 1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_gox_a, 0, 1, GOX_A, parent );
	STS()->SetAnimation( anim_gox_a, posgox_a );
	SaveAnimation( GOX_A );

	/////// GOX B ///////
	static UINT GOX_B_GRP[1] = {GRP_GOX_VENT_SEGMENT1_CISS};
	anim_gox_b = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* GOX_B = new MGROUP_ROTATE( mesh_idx, GOX_B_GRP, 1, CISS_P10, _V( -1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_gox_b, 0, 1, GOX_B );
	STS()->SetAnimation( anim_gox_b, posgox_b );
	SaveAnimation( GOX_B );

	/////// LH2 A ///////
	static UINT LH2_A_GRP[1] = {GRP_LH2_FILL_DRAIN_SEGMENT2_CISS};
	anim_lh2_a = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* LH2_A = new MGROUP_ROTATE( mesh_idx, LH2_A_GRP, 1, CISS_P11, _V( 1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_lh2_a, 0, 1, LH2_A, parent );
	STS()->SetAnimation( anim_lh2_a, poslh2_a );
	SaveAnimation( LH2_A );

	/////// LH2 B ///////
	static UINT LH2_B_GRP[1] = {GRP_LH2_FILL_DRAIN_SEGMENT1_CISS};
	anim_lh2_b = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* LH2_B = new MGROUP_ROTATE( mesh_idx, LH2_B_GRP, 1, CISS_P13, _V( -1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_lh2_b, 0, 1, LH2_B );
	STS()->SetAnimation( anim_lh2_b, poslh2_b );
	SaveAnimation( LH2_B );

	/////// GH2 A ///////
	static UINT GH2_A_GRP[1] = {GRP_GH2_VENT_SEGMENT2_CISS};
	anim_gh2_a = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* GH2_A = new MGROUP_ROTATE( mesh_idx, GH2_A_GRP, 1, CISS_P14, _V( 1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_gh2_a, 0, 1, GH2_A, parent );
	STS()->SetAnimation( anim_gh2_a, posgh2_a );
	SaveAnimation( GH2_A );

	/////// GH2 B ///////
	static UINT GH2_B_GRP[1] = {GRP_GH2_VENT_SEGMENT1_CISS};
	anim_gh2_b = STS()->CreateAnimation( 0.0 );
	MGROUP_ROTATE* GH2_B = new MGROUP_ROTATE( mesh_idx, GH2_B_GRP, 1, CISS_P16, _V( -1, 0, 0 ), static_cast<float>(PI2) );
	STS()->AddAnimationComponent( anim_gh2_b, 0, 1, GH2_B );
	STS()->SetAnimation( anim_gh2_b, posgh2_b );
	SaveAnimation( GH2_B );

	return;
}

void CISS::DefineLatchAnimations( void )
{
	ANIMATIONCOMPONENT_HANDLE parent = NULL;

	// port
	static UINT PRLAPort_Grp = {1};
	MGROUP_ROTATE* PRLAPort = new MGROUP_ROTATE( mesh_idx_Latches[0], &PRLAPort_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
	UINT animPRLAport = STS()->CreateAnimation( 0.0 );
	STS()->SetAnimation( animPRLAport, 1.0 );
	parent = STS()->AddAnimationComponent( animPRLAport, 0.0, 1.0, PRLAPort );
	SaveAnimation( PRLAPort );

	static UINT HookPort_Grp = {0};
	MGROUP_ROTATE* PRLAPortHook = new MGROUP_ROTATE( mesh_idx_Latches[0], &HookPort_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
	animLatches[0] = STS()->CreateAnimation( 0.0 );// closed position
	STS()->SetAnimation( animLatches[0], LatchState[0] );// loaded position from scenario
	STS()->AddAnimationComponent( animLatches[0], 0.0, 1.0, PRLAPortHook, parent );
	SaveAnimation( PRLAPortHook );

	// starboard
	static UINT PRLAStbd_Grp = {1};
	MGROUP_ROTATE* PRLAStbd = new MGROUP_ROTATE( mesh_idx_Latches[1], &PRLAStbd_Grp, 1, _V( 0.0, 0.0, 0.0 ), _V( 0.0, 1.0, 0.0 ), static_cast<float>(PI) );
	UINT animPRLAstbd = STS()->CreateAnimation( 0.0 );
	STS()->SetAnimation( animPRLAstbd, 1.0 );
	parent = STS()->AddAnimationComponent( animPRLAstbd, 0.0, 1.0, PRLAStbd );
	SaveAnimation( PRLAStbd );

	static UINT HookStbd_Grp = {0};
	MGROUP_ROTATE* PRLAStbdHook = new MGROUP_ROTATE( mesh_idx_Latches[1], &HookStbd_Grp, 1, PRLA_HOOK_HINGE_POS, PRLA_HOOK_HINGE_DIR, static_cast<float>(PRLA_HOOK_HINGE_ANG) );
	animLatches[1] = STS()->CreateAnimation( 0.0 );// closed position
	STS()->SetAnimation( animLatches[1], LatchState[1] );// loaded position from scenario
	STS()->AddAnimationComponent( animLatches[1], 0.0, 1.0, PRLAStbdHook, parent );
	SaveAnimation( PRLAStbdHook );

	// keel
	static UINT AKADynamic_Grp = {0};
	static UINT AKAStatic_Grp = {1};
	MGROUP_TRANSLATE* AKADynamic = new MGROUP_TRANSLATE( mesh_idx_Latches[2], &AKADynamic_Grp, 1, AKA_FWD_DYNAMIC_LATCH_OPEN_TRANSLATION );
	MGROUP_TRANSLATE* AKAStatic = new MGROUP_TRANSLATE( mesh_idx_Latches[2], &AKAStatic_Grp, 1, AKA_FWD_STATIC_LATCH_OPEN_TRANSLATION );
	animLatches[2] = STS()->CreateAnimation( 0.0 );// closed position
	STS()->SetAnimation( animLatches[2], LatchState[2] );// loaded position from scenario
	STS()->AddAnimationComponent( animLatches[2], 0.0, 1.0, AKADynamic );
	STS()->AddAnimationComponent( animLatches[2], 0.0, 1.0, AKAStatic );
	SaveAnimation( AKADynamic );
	SaveAnimation( AKAStatic );
	return;
}

void CISS::CreateAttachment( void )
{
	if (ahToCentaur == NULL)
	{
		if (isGPrime) ahToCentaur = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + CENTAUR_ATTACHMENT_OFFSET, CENTAUR_ATTACHMENT_DIR, CENTAUR_ATTACHMENT_ROT, "SSV_CGP" );
		else ahToCentaur = STS()->CreateAttachment( false, STS()->GetOrbiterCoGOffset() + CENTAUR_ATTACHMENT_OFFSET, CENTAUR_ATTACHMENT_DIR, CENTAUR_ATTACHMENT_ROT, "SSV_CG" );
	}
	return;
}

void CISS::UpdateAttachment( void )
{
	CalcAnimation();
	RunAnimation();
	return;
}

bool CISS::IsCentaurAttached( void ) const
{
	return (STS()->GetAttachmentStatus( ahToCentaur ) != NULL);
}

void CISS::RunAnimation( void )
{
	STS()->SetAnimation( anim_rotate, posDA );
	STS()->SetAnimation( anim_motorcrank, posmotorcrank );
	STS()->SetAnimation( anim_link, poslink );
	STS()->SetAnimation( anim_lox_a, poslox_a );
	STS()->SetAnimation( anim_lox_b, poslox_b );
	STS()->SetAnimation( anim_gox_a, posgox_a );
	STS()->SetAnimation( anim_gox_b, posgox_b );
	STS()->SetAnimation( anim_lh2_a, poslh2_a );
	STS()->SetAnimation( anim_lh2_b, poslh2_b );
	STS()->SetAnimation( anim_gh2_a, posgh2_a );
	STS()->SetAnimation( anim_gh2_b, posgh2_b );

	// calc attachment data
	MATRIX3 mrot = rotm( CISS_ROTATION_AXIS, posDA * PI2 );
	VECTOR3 attpos = mul( mrot, CENTAUR_ATTACHMENT_OFFSET - (CISS_P1 + CISS_OFFSET) ) + (CISS_P1 + CISS_OFFSET);
	VECTOR3 attdir = mul( mrot, CENTAUR_ATTACHMENT_DIR );
	VECTOR3 attrot = mul( mrot, CENTAUR_ATTACHMENT_ROT );
	STS()->SetAttachmentParams( ahToCentaur, attpos + STS()->GetOrbiterCoGOffset(), attdir, attrot );
	return;
}

void CISS::CalcAnimation( void )
{
	// motor crank/link/DA
	double theta3 = (posmotorcrank * CISS_MOTOR_ROTATION_RANGE) + theta3o;
	double xa = x2 + r3 * cos( theta3 );
	double ya = y2 + r3 * sin( theta3 );
	double theta4 = atan2( ya, xa ) + acos( (pow( xa, 2 ) + pow( ya, 2 ) + pow( r4, 2 ) - pow( r1, 2 )) / (2 * r4 * sqrt( pow( xa, 2 ) + pow( ya, 2 ) )) );
	double theta1 = atan2( (ya - (r4 * sin( theta4 ))) / r1, (xa - (r4 * cos( theta4 ))) / r1 );

	posDA = max(0.0, (theta1 - theta1o) / PI2);
	poslink = -((theta4 - theta4o - (theta1 - theta1o)) / PI2);
	if (poslink < 0.0) poslink += 1.0;

	// LOX
	double theta2_5 = theta2_5o - (posDA * PI2);
	xa = x7 - r2_5 * cos( theta2_5 );
	ya = y7 - r2_5 * sin( theta2_5 );
	double theta6 = atan2( ya, xa ) + acos( (pow( xa, 2 ) + pow( ya, 2 ) + pow( r6, 2 ) - pow( r5, 2 )) / (2 * (-r6) * sqrt( pow( xa, 2 ) + pow( ya, 2 ) )) );
	double theta5 = atan2( (ya + (r6 * sin( theta6 ))) / r5, (xa + (r6 * cos( theta6 ))) / r5 );
	poslox_a = (theta5 - theta5o + (theta2_5o - theta2_5)) / PI2;
	poslox_b = (theta6o - theta6) / PI2;

	// GOX
	double theta2_8 = theta2_8o - (posDA * PI2);
	xa = x10 - r2_8 * cos( theta2_8 );
	ya = y10 - r2_8 * sin( theta2_8 );
	double theta9 = atan2( ya, xa ) + acos( (pow( xa, 2 ) + pow( ya, 2 ) + pow( r9, 2 ) - pow( r8, 2 )) / (2 * (-r9) * sqrt( pow( xa, 2 ) + pow( ya, 2 ) )) );
	double theta8 = atan2( (ya + (r9 * sin( theta9 ))) / r8, (xa + (r9 * cos( theta9 ))) / r8 );
	posgox_a = (theta8 - theta8o + (theta2_8o - theta2_8)) / PI2;
	posgox_b = (theta9o - theta9) / PI2;

	// LH2
	double theta2_11 = theta2_11o - (posDA * PI2);
	xa = x13 - r2_11 * cos( theta2_11 );
	ya = y13 - r2_11 * sin( theta2_11 );
	double theta12 = atan2( ya, xa ) + acos( (pow( xa, 2 ) + pow( ya, 2 ) + pow( r12, 2 ) - pow( r11, 2 )) / (2 * (-r12) * sqrt( pow( xa, 2 ) + pow( ya, 2 ) )) );
	double theta11 = atan2( (ya + (r12 * sin( theta12 ))) / r11, (xa + (r12 * cos( theta12 ))) / r11 );
	poslh2_a = (theta11 - theta11o + (theta2_11o - theta2_11)) / PI2;
	poslh2_b = (theta12o - theta12) / PI2;

	// GH2
	double theta2_14 = theta2_14o - (posDA * PI2);
	xa = x16 - r2_14 * cos( theta2_14 );
	ya = y16 - r2_14 * sin( theta2_14 );
	double theta15 = atan2( ya, xa ) + acos( (pow( xa, 2 ) + pow( ya, 2 ) + pow( r15, 2 ) - pow( r14, 2 )) / (2 * (-r15) * sqrt( pow( xa, 2 ) + pow( ya, 2 ) )) );
	double theta14 = atan2( (ya + (r15 * sin( theta15 ))) / r14, (xa + (r15 * cos( theta15 ))) / r14 );
	posgh2_a = (theta14 - theta14o + (theta2_14o - theta2_14)) / PI2;
	posgh2_b = (theta15o - theta15) / PI2;
	return;
}
