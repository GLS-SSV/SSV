/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/14   GLS
2020/05/25   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/19   GLS
2020/08/20   GLS
2021/01/20   GLS
2021/06/28   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/09   GLS
2021/12/10   GLS
2021/12/11   GLS
2021/12/23   GLS
2021/12/24   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/04/26   GLS
2022/08/05   GLS
2023/09/14   GLS
********************************************/
#define ORBITER_MODULE


#include "Centaur.h"
#include "Centaur_MFD.h"
#include "meshres_Centaur_G.h"
#include "meshres_Centaur_GPrime.h"
#include <MathSSV.h>
#include <UtilsSSV.h>


const static char* MESHNAME_G = "SSV\\Centaur\\CentaurG";
const static char* MESHNAME_GPRIME = "SSV\\Centaur\\CentaurG_Prime";

constexpr const VECTOR3 ATTACHMENT_CISS_POS_G = { 0.0, 0.0, -2.87686 };
constexpr const VECTOR3 ATTACHMENT_CISS_POS_GPRIME = { 0.0, 0.0, -2.87686 };

constexpr const VECTOR3 ATTACHMENT_PL_POS_G = { 0.0, 0.0, 0.771692 };
constexpr const VECTOR3 ATTACHMENT_PL_POS_GPRIME = { 0.0, 0.0, 3.69447 };

constexpr const VECTOR3 RL10_C1_POS_G = { 0.0, 0.67, -4.74 };
constexpr const VECTOR3 RL10_C1_POS_GPRIME = { 0.0, 0.67, -4.74 };
constexpr const VECTOR3 RL10_C1_DIR = { 0.0, 0.0, 1.0 };
constexpr const VECTOR3 RL10_C2_POS_G = { 0.0, -0.67, -4.74 };
constexpr const VECTOR3 RL10_C2_POS_GPRIME = { 0.0, -0.67, -4.74 };
constexpr const VECTOR3 RL10_C2_DIR = { 0.0, 0.0, 1.0 };
// quad I
constexpr const VECTOR3 ACS_P1_POS_G = { 0.9524, 1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P1_POS_GPRIME = { 0.9524, 1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P1_DIR = { 0.0, -1.0, 0.0 };
constexpr const VECTOR3 ACS_Y1_POS_G = { 1.0825, 0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y1_POS_GPRIME = { 1.0825, 0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y1_DIR = { -1.0, 0.0, 0.0 };
// quad II
constexpr const VECTOR3 ACS_Y2_POS_G = { 1.0825, -0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y2_POS_GPRIME = { 1.0825, -0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y2_DIR = { -1.0, 0.0, 0.0 };
constexpr const VECTOR3 ACS_S2A_POS_G = { 1.0038, -1.0122, -3.0622 };
constexpr const VECTOR3 ACS_S2A_POS_GPRIME = { 1.0038, -1.0122, -3.0622 };
constexpr const VECTOR3 ACS_S2A_DIR = { 0.0, 0.0, 1.0 };
constexpr const VECTOR3 ACS_S2B_POS_G = { 0.9732, -1.0422, -3.0622 };
constexpr const VECTOR3 ACS_S2B_POS_GPRIME = { 0.9732, -1.0422, -3.0622 };
constexpr const VECTOR3 ACS_S2B_DIR = { 0.0, 0.0, 1.0 };
constexpr const VECTOR3 ACS_P2_POS_G = { 0.9524, -1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P2_POS_GPRIME = { 0.9524, -1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P2_DIR = { 0.0, 1.0, 0.0 };
// quad III
constexpr const VECTOR3 ACS_P3_POS_G = { -0.9524, -1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P3_POS_GPRIME = { -0.9524, -1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P3_DIR = { 0.0, 1.0, 0.0 };
constexpr const VECTOR3 ACS_Y3_POS_G = { -1.0825, -0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y3_POS_GPRIME = { -1.0825, -0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y3_DIR = { 1.0, 0.0, 0.0 };
// quad IV
constexpr const VECTOR3 ACS_Y4_POS_G = { -1.0825, 0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y4_POS_GPRIME = { -1.0825, 0.9864, -2.9863 };
constexpr const VECTOR3 ACS_Y4_DIR = { 1.0, 0.0, 0.0 };
constexpr const VECTOR3 ACS_S4A_POS_G = { -1.0038, 1.0122, -3.0622 };
constexpr const VECTOR3 ACS_S4A_POS_GPRIME = { -1.0038, 1.0122, -3.0622 };
constexpr const VECTOR3 ACS_S4A_DIR = { 0.0, 0.0, 1.0 };
constexpr const VECTOR3 ACS_S4B_POS_G = { -0.9732, 1.0422, -3.0622 };
constexpr const VECTOR3 ACS_S4B_POS_GPRIME = { -0.9732, 1.0422, -3.0622 };
constexpr const VECTOR3 ACS_S4B_DIR = { 0.0, 0.0, 1.0 };
constexpr const VECTOR3 ACS_P4_POS_G = { -0.9524, 1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P4_POS_GPRIME = { -0.9524, 1.1165, -2.9863 };
constexpr const VECTOR3 ACS_P4_DIR = { 0.0, -1.0, 0.0 };

constexpr double G_EMPTY_MASS = 3243.185;// Kg
constexpr double G_RL10_PROPELLANT_MASS = 14560.32;// Kg
constexpr double G_ACS_PROPELLANT_MASS = 90.71847;// Kg
constexpr double GPRIME_EMPTY_MASS = 2948.35;// Kg
constexpr double GPRIME_RL10_PROPELLANT_MASS = 20411.66;// Kg
constexpr double GPRIME_ACS_PROPELLANT_MASS = 113.3981;// Kg
constexpr double RL10A33A_THRUST_VAC = 73309.5;// N
const double RL10A33A_ISP_VAC = 446.6 * G;// m/s
constexpr double RL10A33B_THRUST_VAC = 66723.32;// N
const double RL10A33B_ISP_VAC = 436.0 * G;// m/s
constexpr double ACS_THRUST_VAC = 26.64;// N
const double ACS_ISP_VAC = 324.0 * G;// m/s
constexpr double GHe_MASS = 2.0;// Kg

constexpr double ANTENNA_DEPLOY_RATE = 2.0;// 1/s
constexpr double ANTENNA_DEPLOY_DELAY = 60.0;// s
constexpr double ANTENNA_ANIM_START = ANTENNA_DEPLOY_DELAY / (ANTENNA_DEPLOY_DELAY + (1.0 / ANTENNA_DEPLOY_RATE));
constexpr double ANTENNA_ANIM_RATE = 1.0 / (ANTENNA_DEPLOY_DELAY + (1.0 / ANTENNA_DEPLOY_RATE));

constexpr double VEHICLE_MAX_RATE_CMD = 5.0;// deg/s
constexpr double RL10_MAX_GIMBAL_RATE = 2.0;// deg/s
constexpr double RL10_GIMBAL_RANGE = 4.0;// deg


DLLCLBK VESSEL *ovcInit( OBJHANDLE vessel, int flightmodel )
{
	try
	{
		return new Centaur( vessel );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit( VESSEL *vessel )
{
	try
	{
		if (vessel) delete static_cast<Centaur*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}


Centaur::Centaur( OBJHANDLE hVessel ):VESSEL4( hVessel ),
isGPrime(true)
{
	ctrlRL10_P.SetGains( 0.1, 0.01, 0 );
	ctrlRL10_Y.SetGains( 0.1, 0.01, 0 );
	ctrlRL10_R.SetGains( 0.4, 0.05, 0 );
	RL10_P = 0;
	RL10_Y = 0;
	RL10_R = 0;
	manP = 0;
	manY = 0;
	manR = 0;

	separated = false;
	timer_ACS_ENA = -1.0;
	ACS_ENA = false;
	timer_RL10_ENA = -1.0;
	RL10_ENA = false;
	timer_RL10_startseq = -1.0;
	RL10_startseq = false;
	RL10_chill = 0;

	AdapterOffset = 0;
	AdapterMass = 0;

	static char *name = "SSV_Centaur";
	MFDMODESPECEX spec;
	spec.name = name;
	spec.key = OAPI_KEY_T;
	spec.context = NULL;
	spec.msgproc = Centaur_MFD::MsgProc;
	mfdID = RegisterMFDMode( spec );
	return;
}

Centaur::~Centaur( void )
{
	UnregisterMFDMode( mfdID );

	if (ANTENNA1) delete ANTENNA1;
	if (ANTENNA2) delete ANTENNA2;
	return;
}

void Centaur::clbkSetClassCaps( FILEHANDLE cfg )
{
	try
	{
		char pszBuffer[255];
		bool bFoundData = oapiReadItem_string( cfg, "Type", pszBuffer );
		static PARTICLESTREAMSPEC pssRL10_chill = {
			0,
			0.4,
			50,
			5,
			0,
			0.5,
			1,
			0.5,
			PARTICLESTREAMSPEC::DIFFUSE,
			PARTICLESTREAMSPEC::LVL_FLAT,
			1, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0
		};

		if ((bFoundData == true) && (_strnicmp( pszBuffer, "G", 2 ) == 0))
		{
			// set G
			isGPrime = false;
			SetEmptyMass( G_EMPTY_MASS );
			phTank = CreatePropellantResource( G_RL10_PROPELLANT_MASS );
			// RL-10
			thRL10[0] = CreateThruster( RL10_C1_POS_G, RL10_C1_DIR, RL10A33B_THRUST_VAC, phTank, RL10A33B_ISP_VAC );
			thRL10[1] = CreateThruster( RL10_C2_POS_G, RL10_C2_DIR, RL10A33B_THRUST_VAC, phTank, RL10A33B_ISP_VAC );

			AddParticleStream( &pssRL10_chill, RL10_C1_POS_G, -RL10_C1_DIR, &RL10_chill );
			AddParticleStream( &pssRL10_chill, RL10_C2_POS_G, -RL10_C2_DIR, &RL10_chill );

			phACS = CreatePropellantResource( G_ACS_PROPELLANT_MASS );
			// quad I
			thACS[0] = CreateThruster( ACS_P1_POS_G, ACS_P1_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[1] = CreateThruster( ACS_Y1_POS_G, ACS_Y1_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			// quad II
			thACS[2] = CreateThruster( ACS_Y2_POS_G, ACS_Y2_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[3] = CreateThruster( ACS_S2A_POS_G, ACS_S2A_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[4] = CreateThruster( ACS_S2B_POS_G, ACS_S2B_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[5] = CreateThruster( ACS_P2_POS_G, ACS_P2_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			// quad III
			thACS[6] = CreateThruster( ACS_P3_POS_G, ACS_P3_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[7] = CreateThruster( ACS_Y3_POS_G, ACS_Y3_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			// quad IV
			thACS[8] = CreateThruster( ACS_Y4_POS_G, ACS_Y4_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[9] = CreateThruster( ACS_S4A_POS_G, ACS_S4A_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[10] = CreateThruster( ACS_S4B_POS_G, ACS_S4B_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[11] = CreateThruster( ACS_P4_POS_G, ACS_P4_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );

			hMesh = oapiLoadMeshGlobal( MESHNAME_G );
			mesh_idx = AddMesh( hMesh );
			SetMeshVisibilityMode( mesh_idx, MESHVIS_ALWAYS );
			SetSize( 20 );
			SetCrossSections( _V( 19.49, 18.88, 15.71 ) );
			SetPMI( _V( 4.32, 4.35, 2.69 ) );
			SetCameraOffset( _V( 0, 2.4, 1.9 ) );

			ahToPayload = CreateAttachment( false, ATTACHMENT_PL_POS_G, _V( 0.0, 0.0, 1.0 ), _V( -1.0, 0.0, 0.0 ), "SSV_CPL" );
			ahToCISS = CreateAttachment( true, ATTACHMENT_CISS_POS_G, _V( 0.0, 0.0, -1.0 ), _V( 1.0, 0.0, 0.0 ), "SSV_CG" );

			DefineGAnimations();
		}
		else// pszBuffer = "GPrime"
		{
			// set GPrime
			// default
			isGPrime = true;
			SetEmptyMass( GPRIME_EMPTY_MASS );
			phTank = CreatePropellantResource( GPRIME_RL10_PROPELLANT_MASS );
			// RL-10
			thRL10[0] = CreateThruster( RL10_C1_POS_GPRIME, RL10_C1_DIR, RL10A33A_THRUST_VAC, phTank, RL10A33A_ISP_VAC );
			thRL10[1] = CreateThruster( RL10_C2_POS_GPRIME, RL10_C2_DIR, RL10A33A_THRUST_VAC, phTank, RL10A33A_ISP_VAC );

			AddParticleStream( &pssRL10_chill, RL10_C1_POS_GPRIME, -RL10_C1_DIR, &RL10_chill );
			AddParticleStream( &pssRL10_chill, RL10_C2_POS_GPRIME, -RL10_C2_DIR, &RL10_chill );

			phACS = CreatePropellantResource( GPRIME_ACS_PROPELLANT_MASS );
			// quad I
			thACS[0] = CreateThruster( ACS_P1_POS_GPRIME, ACS_P1_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[1] = CreateThruster( ACS_Y1_POS_GPRIME, ACS_Y1_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			// quad II
			thACS[2] = CreateThruster( ACS_Y2_POS_GPRIME, ACS_Y2_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[3] = CreateThruster( ACS_S2A_POS_GPRIME, ACS_S2A_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[4] = CreateThruster( ACS_S2B_POS_GPRIME, ACS_S2B_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[5] = CreateThruster( ACS_P2_POS_GPRIME, ACS_P2_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			// quad III
			thACS[6] = CreateThruster( ACS_P3_POS_GPRIME, ACS_P3_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[7] = CreateThruster( ACS_Y3_POS_GPRIME, ACS_Y3_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			// quad IV
			thACS[8] = CreateThruster( ACS_Y4_POS_GPRIME, ACS_Y4_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[9] = CreateThruster( ACS_S4A_POS_GPRIME, ACS_S4A_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[10] = CreateThruster( ACS_S4B_POS_GPRIME, ACS_S4B_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );
			thACS[11] = CreateThruster( ACS_P4_POS_GPRIME, ACS_P4_DIR, ACS_THRUST_VAC, phACS, ACS_ISP_VAC );

			hMesh = oapiLoadMeshGlobal( MESHNAME_GPRIME );
			mesh_idx = AddMesh( hMesh );
			SetMeshVisibilityMode( mesh_idx, MESHVIS_ALWAYS );
			SetSize( 25 );
			SetCrossSections( _V( 30.00, 29.39, 15.07 ) );
			SetPMI( _V( 3.94, 3.94, 2.16 ) );
			SetCameraOffset( _V( 0, 2.4, 1.2 ) );

			ahToPayload = CreateAttachment( false, ATTACHMENT_PL_POS_GPRIME, _V( 0.0, 0.0, 1.0 ), _V( -1.0, 0.0, 0.0 ), "SSV_CPL" );
			ahToCISS = CreateAttachment( true, ATTACHMENT_CISS_POS_GPRIME, _V( 0.0, 0.0, -1.0 ), _V( 1.0, 0.0, 0.0 ), "SSV_CGP" );

			DefineGPrimeAnimations();
		}

		PARTICLESTREAMSPEC psRL10 = {
			0,
			0.4,
			25,
			50,
			0.5,
			0.12,
			22,
			5,
			PARTICLESTREAMSPEC::EMISSIVE,
			PARTICLESTREAMSPEC::LVL_SQRT,
			0, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0};
		psRL10.tex = oapiRegisterParticleTexture( "Contrail1a" );
		AddExhaustStream( thRL10[0], &psRL10 );
		AddExhaust( thRL10[0], 3, 0.6, 0.5 );
		AddExhaustStream( thRL10[1], &psRL10 );
		AddExhaust( thRL10[1], 3, 0.6, 0.5 );

		PARTICLESTREAMSPEC psACS = {
			0,
			0.01,
			100,
			3,
			0,
			0.1,
			1.5,
			10,
			PARTICLESTREAMSPEC::DIFFUSE,
			PARTICLESTREAMSPEC::LVL_SQRT,
			0, 1,
			PARTICLESTREAMSPEC::ATM_FLAT,
			1, 1,
			0};
		AddExhaust( thACS[0], 0.5, 0.05 );
		AddExhaustStream( thACS[0], &psACS );
		AddExhaust( thACS[1], 0.5, 0.05 );
		AddExhaustStream( thACS[1], &psACS );
		AddExhaust( thACS[2], 0.5, 0.05 );
		AddExhaustStream( thACS[2], &psACS );
		AddExhaust( thACS[3], 0.5, 0.05 );
		AddExhaustStream( thACS[3], &psACS );
		AddExhaust( thACS[4], 0.5, 0.05 );
		AddExhaustStream( thACS[4], &psACS );
		AddExhaust( thACS[5], 0.5, 0.05 );
		AddExhaustStream( thACS[5], &psACS );
		AddExhaust( thACS[6], 0.5, 0.05 );
		AddExhaustStream( thACS[6], &psACS );
		AddExhaust( thACS[7], 0.5, 0.05 );
		AddExhaustStream( thACS[7], &psACS );
		AddExhaust( thACS[8], 0.5, 0.05 );
		AddExhaustStream( thACS[8], &psACS );
		AddExhaust( thACS[9], 0.5, 0.05 );
		AddExhaustStream( thACS[9], &psACS );
		AddExhaust( thACS[10], 0.5, 0.05 );
		AddExhaustStream( thACS[10], &psACS );
		AddExhaust( thACS[11], 0.5, 0.05 );
		AddExhaustStream( thACS[11], &psACS );

		COLOUR4 col_diff = { 0.6f, 0.8f, 1.0f, 0.0f };
		COLOUR4 col_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
		COLOUR4 col_ambient = { 0.6f, 0.8f, 1.0f, 0.0f };
		RL10light[0] = AddPointLight( _V( RL10_C1_POS_GPRIME.x, RL10_C1_POS_GPRIME.y, RL10_C1_POS_GPRIME.z - 2.0 ), 20.0, 1.0, 0.3, 0.01, col_diff, col_zero, col_ambient );
		RL10light[1] = AddPointLight( _V( RL10_C2_POS_GPRIME.x, RL10_C2_POS_GPRIME.y, RL10_C2_POS_GPRIME.z - 2.0 ), 20.0, 1.0, 0.3, 0.01, col_diff, col_zero, col_ambient );
		RL10light[0]->Activate( false );
		RL10light[1]->Activate( false );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkSetClassCaps" );
		abort();
	}
}

void Centaur::clbkPostCreation( void )
{
	try
	{
		if (GetAttachmentStatus( ahToCISS ) == NULL)
		{
			// if it starts sim separated from CISS, assume it separated a long time ago and enable all engines without delay and deploy antennas
			EnableACS();
			ACS_ENA = true;
			RL10_ENA = true;

			asANTENNA.pos = 1.0;

			separated = true;

			// add payload mass to centaur dry mass
			OBJHANDLE ohPL = GetAttachmentStatus( ahToPayload );
			if (ohPL)
			{
				VECTOR3 cg;
				double mass = GetMassAndCoGOfAttachedObject( this, ahToPayload, cg );
				SetEmptyMass( GetEmptyMass() + mass );
			}

			// deploy antennas
			asANTENNA.action = AnimState::OPEN;
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkPostCreation" );
		abort();
	}
}

void Centaur::clbkPreStep( double simt, double simdt, double mjd )
{
	try
	{
		if ((!ACS_ENA) && (timer_ACS_ENA != -1.0))
		{
			timer_ACS_ENA += simdt;
			if (timer_ACS_ENA >= ACS_ENA_DELAY)
			{
				EnableACS();
				ACS_ENA = true;
			}
		}

		if ((!RL10_ENA) && (timer_RL10_ENA != -1.0))
		{
			timer_RL10_ENA += simdt;
			if (timer_RL10_ENA >= RL10_ENA_DELAY)
			{
				RL10_ENA = true;
			}
		}

		if (separated == false)
		{
			if (GetAttachmentStatus( ahToCISS ) == NULL)
			{
				oapiWriteLog( "(SSV_Centaur) [INFO] separated" );

				timer_ACS_ENA = 0.0;
				timer_RL10_ENA = 0.0;

				separated = true;

				// add payload mass to centaur dry mass
				OBJHANDLE ohPL = GetAttachmentStatus( ahToPayload );
				if (ohPL)
				{
					VECTOR3 cg;
					double mass = GetMassAndCoGOfAttachedObject( this, ahToPayload, cg );
					SetEmptyMass( GetEmptyMass() + mass );
				}

				// deploy antennas
				asANTENNA.action = AnimState::OPENING;
			}
		}

		// RL10 start sequence
		if (RL10_startseq)
		{
			if (GetThrusterLevel( thRL10[0] ) == 0.0)
			{
				if (GetPropellantMass( phTank ) == 0.0)
				{
					RL10light[0]->Activate( false );
					RL10light[1]->Activate( false );
					RL10_startseq = false;
					EnablePitchYawRollACS();
				}
				else
				{
					timer_RL10_startseq += simdt;
					if (timer_RL10_startseq > RL10_START_SEQ)// prop settling time
					{
						SetThrusterLevel( thRL10[0], 1 );
						SetThrusterLevel( thRL10[1], 1 );
						RL10light[0]->Activate( true );
						RL10light[1]->Activate( true );
						SetThrusterGroupLevel( THGROUP_ATT_FORWARD, 0.0 );
						RL10_chill = 0;
						InhibitPitchYawRollACS();
					}
				}
			}
			else
			{
				// engine TVC (rate command)
				VECTOR3 avel;
				GetAngularVel( avel );

				// pitch
				// command rate
				double newP = ctrlRL10_P.Step( (avel.x * DEG) - manP, simdt );
				// nozzle rate limit
				if ((newP - RL10_P) > RL10_MAX_GIMBAL_RATE) newP = RL10_P + RL10_MAX_GIMBAL_RATE;
				else if ((newP - RL10_P) < -RL10_MAX_GIMBAL_RATE) newP = RL10_P - RL10_MAX_GIMBAL_RATE;
				RL10_P = newP;

				// yaw
				// command rate
				double newY = ctrlRL10_Y.Step( (avel.y * DEG) - manY, simdt );
				//nozzle rate limit
				if ((newY - RL10_Y) > RL10_MAX_GIMBAL_RATE) newY = RL10_Y + RL10_MAX_GIMBAL_RATE;
				else if ((newY - RL10_Y) < -RL10_MAX_GIMBAL_RATE) newY = RL10_Y - RL10_MAX_GIMBAL_RATE;
				RL10_Y = newY;


				// roll
				// command rate
				double newR = ctrlRL10_R.Step( (avel.z * DEG) - manR, simdt );
				//nozzle rate limit
				if ((newR - RL10_R) > RL10_MAX_GIMBAL_RATE) newR = RL10_R + RL10_MAX_GIMBAL_RATE;
				else if ((newR - RL10_R) < -RL10_MAX_GIMBAL_RATE) newR = RL10_R - RL10_MAX_GIMBAL_RATE;
				RL10_R = newR;

				// output
				VECTOR3 tv0 = _V( -sin( range( -RL10_GIMBAL_RANGE, RL10_Y + RL10_R, RL10_GIMBAL_RANGE ) * RAD ), sin( range( -RL10_GIMBAL_RANGE, RL10_P, RL10_GIMBAL_RANGE ) * RAD ), 1.0 );
				VECTOR3 tv1 = _V( -sin( range( -RL10_GIMBAL_RANGE, RL10_Y - RL10_R, RL10_GIMBAL_RANGE ) * RAD ), sin( range( -RL10_GIMBAL_RANGE, RL10_P, RL10_GIMBAL_RANGE ) * RAD ), 1.0 );
				normalise( tv0 );
				normalise( tv1 );
				SetThrusterDir( thRL10[0], tv0 );
				SetThrusterDir( thRL10[1], tv1 );
			}
		}

		if (asANTENNA.Opening())
		{
			asANTENNA.Move( simdt * ANTENNA_ANIM_RATE );
			SetAnimation( anim_ANTENNA, asANTENNA.pos );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkPreStep" );
		abort();
	}
}

void Centaur::DefineGAnimations( void )
{
	static UINT ANTENNA1Grp[1] = {GRP_QUAD1_ANTENNA_G};
	ANTENNA1 = new MGROUP_ROTATE( mesh_idx, ANTENNA1Grp, 1, _V( -0.068663, 2.1282, 0.0 ), _V( 0.0, 0.0, 1.0 ), static_cast<float>(PI05) );
	anim_ANTENNA = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_ANTENNA, ANTENNA_ANIM_START, 1.0, ANTENNA1 );

	static UINT ANTENNA2Grp[1] = {GRP_QUAD2_ANTENNA_G};
	ANTENNA2 = new MGROUP_ROTATE( mesh_idx, ANTENNA2Grp, 1, _V( -0.068663, -2.1282, 0.0 ), _V( 0.0, 0.0, -1.0 ), static_cast<float>(PI05) );
	AddAnimationComponent( anim_ANTENNA, ANTENNA_ANIM_START, 1.0, ANTENNA2 );

	asANTENNA.Set( AnimState::CLOSED, 0.0 );
	return;
}

void Centaur::DefineGPrimeAnimations( void )
{
	static UINT ANTENNA1Grp[1] = {GRP_QUAD1_ANTENNA_GPRIME};
	ANTENNA1 = new MGROUP_ROTATE( mesh_idx, ANTENNA1Grp, 1, _V( -0.068663, 2.1217, 0.0 ), _V( 0.0, 0.0, 1.0 ), static_cast<float>(PI05) );
	anim_ANTENNA = CreateAnimation( 0.0 );
	AddAnimationComponent( anim_ANTENNA, ANTENNA_ANIM_START, 1.0, ANTENNA1 );

	static UINT ANTENNA2Grp[1] = {GRP_QUAD2_ANTENNA_GPRIME};
	ANTENNA2 = new MGROUP_ROTATE( mesh_idx, ANTENNA2Grp, 1, _V( -0.068663, -2.1217, 0.0 ), _V( 0.0, 0.0, -1.0 ), static_cast<float>(PI05) );
	AddAnimationComponent( anim_ANTENNA, ANTENNA_ANIM_START, 1.0, ANTENNA2 );

	asANTENNA.Set( AnimState::CLOSED, 0.0 );
	return;
}

int Centaur::clbkConsumeBufferedKey( DWORD key, bool down, char* kstate )
{
	try
	{
		if (!down)
		{
			// man gimbal
			if (key == OAPI_KEY_NUMPAD2)
			{
				manP -= VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD8)
			{
				manP -= -VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD1)
			{
				manY -= VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD3)
			{
				manY -= -VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD6)
			{
				manR -= VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			else if (key == OAPI_KEY_NUMPAD4)
			{
				manR -= -VEHICLE_MAX_RATE_CMD;
				return 1;
			}
			return 0;
		}

		// man gimbal
		if (key == OAPI_KEY_NUMPAD2)
		{
			manP += VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD8)
		{
			manP += -VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD1)
		{
			manY += VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD3)
		{
			manY += -VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD6)
		{
			manR += VEHICLE_MAX_RATE_CMD;
			return 1;
		}
		else if (key == OAPI_KEY_NUMPAD4)
		{
			manR += -VEHICLE_MAX_RATE_CMD;
			return 1;
		}

		if ((KEYMOD_SHIFT( kstate ) == false) && (KEYMOD_CONTROL( kstate ) == true) && (KEYMOD_ALT( kstate ) == false))// only CTRL key modifier
		{
			if ((GetThrusterLevel( thRL10[0] ) != 0) || GetAttachmentStatus( ahToCISS ) || !RL10_ENA) return 0;// no separations while engines are firing or still attached to CISS or nearby OV

			if (key == OAPI_KEY_J)
			{
				// remove payload mass from centaur dry mass
				OBJHANDLE ohPL = GetAttachmentStatus( ahToPayload );
				if (ohPL)
				{
					VECTOR3 cg;
					double mass = GetMassAndCoGOfAttachedObject( this, ahToPayload, cg );
					SetEmptyMass( GetEmptyMass() - mass );
				}
				// separate payload
				DetachChild( ahToPayload, 0.3 );
				return 1;
			}
			else if ((key >= OAPI_KEY_1) && (key <= OAPI_KEY_8))
			{
				OBJHANDLE ohPL = GetAttachmentStatus( ahToPayload );
				if (ohPL)
				{
					VESSEL* vPL = oapiGetVesselInterface( ohPL );
					if (vPL->Version() >= 2)
						((VESSEL3*)vPL)->clbkGeneric( VMSG_USER + 0x0101, key - 1, NULL );
				}
				return 1;
			}
		}

		if ((KEYMOD_SHIFT( kstate ) == false) && (KEYMOD_CONTROL( kstate ) == false) && (KEYMOD_ALT( kstate ) == false))// no key modifiers
		{
			if (key == OAPI_KEY_ADD)// check for start
			{
				if (!RL10_startseq && RL10_ENA && (GetPropellantMass( phTank ) != 0.0))
				{
					timer_RL10_startseq = 0.0;
					RL10_startseq = true;
					// start prop settling
					SetThrusterGroupLevel( THGROUP_ATT_FORWARD, 1.0 );
					// start chilldown
					RL10_chill = 1.0;
					return 1;
				}
			}
			else if (key == OAPI_KEY_SUBTRACT)// check for shutdown
			{
				if (RL10_startseq)
				{
					timer_RL10_startseq = -1.0;
					RL10_startseq = false;
					// stop engines
					SetThrusterLevel( thRL10[0], 0.0 );
					SetThrusterLevel( thRL10[1], 0.0 );
					RL10light[0]->Activate( false );
					RL10light[1]->Activate( false );
					SetThrusterGroupLevel( THGROUP_ATT_FORWARD, 0.0 );
					RL10_chill = 0.0;
					EnablePitchYawRollACS();
					return 1;
				}
			}
		}
		return 0;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkConsumeBufferedKey: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkConsumeBufferedKey" );
		abort();
	}
}

void Centaur::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		SetAnimation( anim_ANTENNA, asANTENNA.pos );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkVisualCreated" );
		abort();
	}
}

void Centaur::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		if (strMission.length() > 0) oapiWriteScenario_string( scn, "MISSION", (char*)strMission.c_str() );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkSaveState" );
		abort();
	}
}

void Centaur::clbkLoadStateEx( FILEHANDLE scn, void *status )
{
	try
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "MISSION", 7 ))
			{
				strMission = line + 8;
				LoadMissionFile();
				AddPayloadAdapter();
			}
			else ParseScenarioLineEx( line, status );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_Centaur) [FATAL ERROR] Exception in Centaur::clbkLoadStateEx" );
		abort();
	}
}

void Centaur::EnableACS( void ) const
{
	THRUSTER_HANDLE thTEMP[4];
	thTEMP[0] = thACS[3];// S2A
	thTEMP[1] = thACS[4];// S2B
	thTEMP[2] = thACS[9];// S4A
	thTEMP[3] = thACS[10];// S4B
	CreateThrusterGroup( thTEMP, 4, THGROUP_ATT_FORWARD );

	EnablePitchYawRollACS();
	return;
}

void Centaur::EnablePitchYawRollACS( void ) const
{
	THRUSTER_HANDLE thTEMP[4];
	thTEMP[0] = thACS[0];// P1
	thTEMP[1] = thACS[11];// P4
	CreateThrusterGroup( thTEMP, 2, THGROUP_ATT_PITCHUP );
	thTEMP[0] = thACS[5];// P2
	thTEMP[1] = thACS[6];// P3
	CreateThrusterGroup( thTEMP, 2, THGROUP_ATT_PITCHDOWN );
	thTEMP[0] = thACS[7];// Y3
	thTEMP[1] = thACS[8];// Y4
	CreateThrusterGroup( thTEMP, 2, THGROUP_ATT_YAWLEFT );
	thTEMP[0] = thACS[1];// Y1
	thTEMP[1] = thACS[2];// Y2
	CreateThrusterGroup( thTEMP, 2, THGROUP_ATT_YAWRIGHT );
	thTEMP[0] = thACS[1];// Y1
	thTEMP[1] = thACS[5];// P2
	thTEMP[2] = thACS[7];// Y3
	thTEMP[3] = thACS[11];// P4
	CreateThrusterGroup( thTEMP, 4, THGROUP_ATT_BANKLEFT );
	thTEMP[0] = thACS[0];// P1
	thTEMP[1] = thACS[2];// Y2
	thTEMP[2] = thACS[6];// P3
	thTEMP[3] = thACS[8];// Y4
	CreateThrusterGroup( thTEMP, 4, THGROUP_ATT_BANKRIGHT );
	return;
}

void Centaur::InhibitPitchYawRollACS( void ) const
{
	DelThrusterGroup( THGROUP_ATT_PITCHUP );
	DelThrusterGroup( THGROUP_ATT_PITCHDOWN );
	DelThrusterGroup( THGROUP_ATT_YAWLEFT );
	DelThrusterGroup( THGROUP_ATT_YAWRIGHT );
	DelThrusterGroup( THGROUP_ATT_BANKLEFT );
	DelThrusterGroup( THGROUP_ATT_BANKRIGHT );
	return;
}

void Centaur::LoadMissionFile( void )
{
	std::string filename;
	filename = "Missions\\SSV\\" + strMission + ".json";

	FILE* hF = fopen( filename.c_str(), "r" );
	if (hF == NULL)
	{
		oapiWriteLogV( "(SSV_Centaur) [ERROR] Can't open mission file %s", strMission.c_str() );
		return;
	}

	oapiWriteLogV( "(SSV_Centaur) [INFO] Loading mission file %s", strMission.c_str() );

	fseek( hF, 0, SEEK_END );
	long filesize = ftell( hF );
	if (filesize < 0)
	{
		fclose( hF );
		return;
	}

	char* missionfilestr = new char[filesize];
	rewind( hF );
	fread( missionfilestr, sizeof(char), filesize, hF );
	fclose( hF );

	cJSON* root = cJSON_Parse( missionfilestr );
	if (!root)
	{
		oapiWriteLog( "(SSV_Centaur) [ERROR] Error parsing mission file version" );
		delete[] missionfilestr;
		return;
	}

	cJSON* version = cJSON_GetObjectItemCaseSensitive( root, "Version" );
	switch (version->valueint)
	{
		case 2:// unchanged from V1
			LoadMissionV1( root );
			break;
		default:
			oapiWriteLogV( "(SSV_Centaur) [ERROR] Unknown mission file version %d", version->valueint );
			break;
	}

	cJSON_Delete( root );
	delete[] missionfilestr;
	return;
}

void Centaur::LoadMissionV1( cJSON* root )
{
	// read UpperStages
	cJSON* us = cJSON_GetObjectItemCaseSensitive( root, "Upper Stages" );
	for (int i = 0; i < cJSON_GetArraySize( us ); i++)
	{
		// find correct item
		cJSON* usi = cJSON_GetArrayItem( us, i );
		if (usi)
		{
			cJSON* name = cJSON_GetObjectItemCaseSensitive( usi, "Name" );
			cJSON* usown = cJSON_GetObjectItemCaseSensitive( usi, isGPrime ? "Centaur G-Prime" : "Centaur G" );
			if ((name) && (usown))
			{
				if (!strcmp( GetName(), name->valuestring ))
				{
					// read own params
					// none

					// read payload adapter params
					cJSON* adapter = cJSON_GetObjectItemCaseSensitive( usi, "Adapter" );
					if (adapter)
					{
						cJSON* tmp = cJSON_GetObjectItemCaseSensitive( adapter, "Mesh" );
						AdapterMeshName = tmp->valuestring;

						tmp = cJSON_GetObjectItemCaseSensitive( adapter, "Offset" );
						AdapterOffset = tmp->valuedouble;

						tmp = cJSON_GetObjectItemCaseSensitive( adapter, "Mass" );
						AdapterMass = tmp->valuedouble;
					}
					break;
				}
			}
		}
	}
	return;
}

void Centaur::AddPayloadAdapter( void )
{
	// small sanity checks
	if (AdapterMeshName.length())
	{
		if (AdapterOffset <= 0.0)
		{
			oapiWriteLog( "(SSV_Centaur) [ERROR] AdapterOffset was not specified or isn't greater than 0" );
			return;
		}

		if (AdapterMass <= 0.0)
		{
			oapiWriteLog( "(SSV_Centaur) [ERROR] AdapterMass was not specified or isn't greater than 0" );
			return;
		}
	}
	else return;

	VECTOR3 pos;
	VECTOR3 dir;
	VECTOR3 rot;
	GetAttachmentParams( ahToPayload, pos, dir, rot );

	// add mesh
	MESHHANDLE hAdapterMesh = oapiLoadMeshGlobal( AdapterMeshName.c_str() );
	if (hAdapterMesh == NULL)
	{
		oapiWriteLog( "(SSV_Centaur) [ERROR] AdapterMesh file not found" );
		return;
	}
	SetMeshVisibilityMode( AddMesh( hAdapterMesh, &pos ), MESHVIS_ALWAYS );

	// correct spacecraft attachment
	pos.z += AdapterOffset;
	SetAttachmentParams( ahToPayload, pos, dir, rot );

	// correct mass
	SetEmptyMass( GetEmptyMass() + AdapterMass );

	oapiWriteLogV( "(SSV_Centaur) [INFO] Added payload adapter: mesh:%s|height:%lf|mass:%lf", AdapterMeshName.c_str(), AdapterOffset, AdapterMass );
	return;
}
