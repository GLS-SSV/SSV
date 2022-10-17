/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/21   GLS
2020/03/24   GLS
2020/03/25   GLS
2020/03/26   GLS
2020/03/28   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/04/28   GLS
2020/05/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/24   GLS
2021/06/18   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/25   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "AerodynamicData.h"
#include "ParameterValues.h"
#include "Atlantis.h"
#include <MathSSV.h>


/* Data in file:
[dummy]
[Mach,Alpha
[CL]
[CD]
[CM]]
*/
const char* LongitudinalBasicFile = "Config\\SSV_Aero_Longitudinal_Basic.csv";

/* Data in file:
[dE]
[Mach,Alpha
[DCLE]
[DCDE]
[DCME]]
*/
const char* LongitudinalElevatorFile = "Config\\SSV_Aero_Longitudinal_Elevator.csv";

/* Data in file:
[dSB]
[Mach,Alpha
[DCLSB]
[DCDSB]
[DCMSB]]
*/
const char* LongitudinalSpeedbrakeFile = "Config\\SSV_Aero_Longitudinal_Speedbrake.csv";

/* Data in file:
[dSB]
[Mach,Alpha
[DCLBF]
[DCDBF]
[DCMBF]]
*/
const char* LongitudinalBodyflapFile = "Config\\SSV_Aero_Longitudinal_Bodyflap.csv";

/* Data in file:
[dummy]
[Theta,Alpha
[DCLLG]
[DCDLG]
[DCMLG]]
*/
const char* LongitudinalLandinggearFile = "Config\\SSV_Aero_Longitudinal_Landinggear.csv";

/* Data in file:
[h/b]
[dE,Alpha
[DCNGE]
[DCAGE]
[DCMGE]]
*/
const char* LongitudinalGroundeffectFile = "Config\\SSV_Aero_Longitudinal_Groundeffect.csv";

/* Data in file:
[h/b]
[dBF,Alpha
[DCNBFGE]
[DCABFGE]
[DCMBFGE]]
*/
const char* LongitudinalBodyflapGroundeffectFile = "Config\\SSV_Aero_Longitudinal_BodyflapGroundeffect.csv";

/* Data in file:
[Beta]
[Mach,Alpha
[CY]
[CLN]
[CLL]]
*/
const char* LateralBasicFile = "Config\\SSV_Aero_Lateral_Basic.csv";

/* Data in file:
[dE]
[Mach,Alpha
[DCYBE]
[DCLNBE]
[DCLLBE]]

(missing dE=-2 data @ M0.950 and M0.980)
*/
const char* LateralElevatorFile = "Config\\SSV_Aero_Lateral_Elevator.csv";

/* Data in file:
[dE]
[Mach,Alpha
[CYDA]
[CLNDA]
[CLLDA]]
*/
const char* LateralAileronFile = "Config\\SSV_Aero_Lateral_Aileron.csv";

/* Data in file:
[dSB]
[Mach,Alpha
[CYDR]
[CLNDR]
[CLLDR]]
*/
const char* LateralRudderFile = "Config\\SSV_Aero_Lateral_Rudder.csv";

/* Data in file:
[dSB]
[Mach,Alpha
[DCYBSB]
[DCLNBSB]
[DCLLBSB]]
*/
const char* LateralSpeedbrakeFile = "Config\\SSV_Aero_Lateral_Speedbrake.csv";


Aerodynamics::ThreeDLookup LongitudinalBasicLookup;
Aerodynamics::ThreeDLookup LongitudinalElevatorLookup;
Aerodynamics::ThreeDLookup LongitudinalSpeedbrakeLookup;
Aerodynamics::ThreeDLookup LongitudinalBodyflapLookup;
Aerodynamics::ThreeDLookup LongitudinalLandinggearLookup;
Aerodynamics::ThreeDLookup LongitudinalGroundeffectLookup;
Aerodynamics::ThreeDLookup LongitudinalBodyflapGroundeffectLookup;

Aerodynamics::ThreeDLookup LateralBasicLookup;
Aerodynamics::ThreeDLookup LateralElevatorLookup;
Aerodynamics::ThreeDLookup LateralAileronLookup;
Aerodynamics::ThreeDLookup LateralRudderLookup;
Aerodynamics::ThreeDLookup LateralSpeedbrakeLookup;


static void GetVerticalAeroCoefficients( double mach, double degAOA, double altitude, double theta, const VECTOR3& cgofs, const AerosurfacePositions* aerosurfaces, double* cl, double* cm, double* cd )
{
	double CL = 0.0;
	double CD = 0.0;
	double CM = 0.0;
	double DCLE = 0.0;
	double DCDE = 0.0;
	double DCME = 0.0;
	double DCLSB = 0.0;
	double DCDSB = 0.0;
	double DCMSB = 0.0;
	double DCLBF = 0.0;
	double DCDBF = 0.0;
	double DCMBF = 0.0;
	double DCLLG = 0.0;
	double DCDLG = 0.0;
	double DCMLG = 0.0;
	double DCLSILTSPOD = 0.0;
	double DCDSILTSPOD = 0.0;
	double DCMSILTSPOD = 0.0;
	double DCLGE = 0.0;
	double DCDGE = 0.0;
	double DCMGE = 0.0;
	double DCLBFGE = 0.0;
	double DCDBFGE = 0.0;
	double DCMBFGE = 0.0;

	LongitudinalBasicLookup.GetValues( mach, degAOA, 1.0, CL, CD, CM );
	LongitudinalElevatorLookup.GetValues( mach, degAOA, aerosurfaces->Elevator, DCLE, DCDE, DCME );
	LongitudinalSpeedbrakeLookup.GetValues( mach, degAOA, aerosurfaces->Speedbrake, DCLSB, DCDSB, DCMSB );
	LongitudinalBodyflapLookup.GetValues( mach, degAOA, aerosurfaces->BodyFlap, DCLBF, DCDBF, DCMBF );
	LongitudinalLandinggearLookup.GetValues( aerosurfaces->LandingGear, degAOA, 1.0, DCLLG, DCDLG, DCMLG );

	VECTOR3 GROUND_EFFECT_REF = _V( 0.0, -3.406266, -14.034736 ) + cgofs;// location of reference point for computing altitude (for ground effect calculations)
	VECTOR3 groundEffectOffset = RotateVectorX( GROUND_EFFECT_REF, theta );
	double groundEffectHeight = altitude + groundEffectOffset.y;
	double heightOverSpan = groundEffectHeight / ORBITER_SPAN;
	if (heightOverSpan < 1.5)
	{
		heightOverSpan = max(0.0, heightOverSpan);
		LongitudinalGroundeffectLookup.GetValues( aerosurfaces->Elevator, degAOA, heightOverSpan, DCLGE, DCDGE, DCMGE );
		LongitudinalBodyflapGroundeffectLookup.GetValues( aerosurfaces->BodyFlap, degAOA, heightOverSpan, DCLBFGE, DCDBFGE, DCMBFGE );
	}

	if ((aerosurfaces->SILTSPOD) && (mach <= 6.0))
	{
		DCLSILTSPOD = 0.0018229 - (0.0019876 - 0.000431427 * mach) * mach;
		DCDSILTSPOD = -0.00046471 + (0.000790212 - 0.000125976 * mach) * mach;
		DCMSILTSPOD = -0.000635152 + (0.000881151 - 0.000173119 * mach) * mach;
	}

	CL = CL + DCLE + DCLBF + DCLSB + DCLLG + DCLSILTSPOD + DCLGE + DCLBFGE;
	CD = CD + DCDE + DCDBF + DCDSB + DCDLG + DCDSILTSPOD + DCDGE + DCDBFGE;
	CM = CM + DCME + DCMBF + DCMSB + DCMLG + DCMSILTSPOD + DCMGE + DCMBFGE;

	*cl = CL;
	*cd = CD;
	*cm = CM;
	return;
}

void LoadAerodynamicData( void )
{
	LongitudinalBasicLookup.Init( LongitudinalBasicFile, true );
	LongitudinalElevatorLookup.Init( LongitudinalElevatorFile, true );
	LongitudinalSpeedbrakeLookup.Init( LongitudinalSpeedbrakeFile, true );
	LongitudinalBodyflapLookup.Init( LongitudinalBodyflapFile, true );
	LongitudinalLandinggearLookup.Init( LongitudinalLandinggearFile, true );
	LongitudinalGroundeffectLookup.Init( LongitudinalGroundeffectFile );
	LongitudinalBodyflapGroundeffectLookup.Init( LongitudinalBodyflapGroundeffectFile );

	LateralBasicLookup.Init( LateralBasicFile, true );
	LateralElevatorLookup.Init( LateralElevatorFile, true );
	LateralAileronLookup.Init( LateralAileronFile, true );
	LateralRudderLookup.Init( LateralRudderFile, true );
	LateralSpeedbrakeLookup.Init( LateralSpeedbrakeFile, true );
	return;
}

void AscentLiftCoeff( double aoa, double M, double Re, double* cl, double* cm, double* cd )
{
	try
	{
		// we don't have data for first stage aerodynamics
		// use entry model and modify coefficients to get realistic first stage performance
		VECTOR3 vofs = _V( 0.0, 0.0, 0.0 );
		AerosurfacePositions aero;
		aero.Aileron = 0.0;
		aero.BodyFlap = 0.0;
		aero.Elevator = 0.0;
		aero.LandingGear = 0.0;
		aero.Rudder = 0.0;
		aero.SILTSPOD = false;
		aero.Speedbrake = 0.0;
		GetVerticalAeroCoefficients(M, aoa*DEG, 1e3, 0.0, vofs, &aero, cl, cm, cd); // hardcode altitude to value large enough that shuttle is out of ground effect
		// scale coefficients to get accurate first stage performance
		*cl = 0.8*(*cl);
		*cm = 0.5*(*cm);
		*cd = 2.5*(*cd);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in AscentLiftCoeff: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in AscentLiftCoeff" );
		abort();
	}
}

void VLiftCoeff( VESSEL* v, double aoa, double M, double Re, void* lv, double* cl, double* cm, double* cd )
{
	try
	{
		aoa *= DEG;

		if ((v->GetAltitude() < 150e3) && (M > 0.05))// if we are above 150km or below M0.05 (~30knots), ignore aerodynamic forces
		{
			if (abs(aoa) > 90.0) aoa = 0.0; // handle Orbitersim bug which results in very large AOA at first timestep

			AerosurfacePositions* aerosurfaces = static_cast<AerosurfacePositions*>(lv);
			GetVerticalAeroCoefficients(M, aoa, v->GetAltitude( ALTMODE_GROUND ), v->GetPitch() * DEG, static_cast<Atlantis*>(v)->GetOrbiterCoGOffset(), aerosurfaces, cl, cm, cd);
		}
		else
		{
			*cl = 0.0;
			*cm = 0.0;
			*cd = 0.0;
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in VLiftCoeff: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in VLiftCoeff" );
		abort();
	}
}

void HLiftCoeff( VESSEL* v, double beta, double M, double Re, void* lv, double* cl, double* cm, double* cd )
{
	try
	{
		beta *= -DEG;// correct beta from Orbiter system to shuttle system (and convert to degrees)

		if ((v->GetAltitude() < 150e3) && (M > 0.05))// if we are above 150km or below M0.05 (~30knots), ignore aerodynamic forces
		{
			if (abs(beta) > 90.0) beta = 0.0; // handle Orbitersim bug which results in very large beta at first timestep

			double aoa = v->GetAOA()*DEG;
			if (abs(aoa) > 90.0) aoa = 0.0; // handle Orbitersim bug which results in very large AOA at first timestep

			AerosurfacePositions* aerosurfaces = static_cast<AerosurfacePositions*>(lv);
			double CY = 0.0;
			double CLN = 0.0;
			double CLL = 0.0;
			double DCYBE = 0.0;
			double DCLNBE = 0.0;
			double DCLLBE = 0.0;
			double CYDA = 0.0;
			double CLNDA = 0.0;
			double CLLDA = 0.0;
			double CYDR = 0.0;
			double CLNDR = 0.0;
			double CLLDR = 0.0;
			double DCYBSB = 0.0;
			double DCLNBSB = 0.0;
			double DCLLBSB = 0.0;
			double DCYSILTSPOD = 0.0;
			double DCLNSILTSPOD = 0.0;
			double DCLLSILTSPOD = 0.0;

			LateralBasicLookup.GetValues( M, aoa, fabs( beta ), CY, CLN, CLL );
			LateralElevatorLookup.GetValues( M, aoa, aerosurfaces->Elevator, DCYBE, DCLNBE, DCLLBE );
			LateralAileronLookup.GetValues( M, aoa, aerosurfaces->Elevator, CYDA, CLNDA, CLLDA );
			LateralRudderLookup.GetValues( M, aoa, aerosurfaces->Speedbrake, CYDR, CLNDR, CLLDR );
			LateralSpeedbrakeLookup.GetValues( M, aoa, aerosurfaces->Speedbrake, DCYBSB, DCLNBSB, DCLLBSB );
			if ((aerosurfaces->SILTSPOD) && (M <= 6.0))
			{
				double DCYBSILTSPOD = -0.0000258677 - (0.000131367 - 0.0000427817 * M) * M;
				double DCYDRSILTSPOD = 0.0000694244 - (0.0001976 - 0.000054135 * M) * M;

				double DCLNBSILTSPOD = 0.000081294 - (0.0000600923 - 0.0000112332 * M) * M;
				double DCLNDRSILTSPOD = 0.00021589 - (0.00023899 - 0.0000527934 * M) * M;

				double DCLLBSILTSPOD = -0.0000806963 + (0.0000446417 - 0.00000628417 * M) * M;
				double DCLLDRSILTSPOD = -0.000074168 + (0.000088076 - 0.000019544 * M) * M;

				DCYSILTSPOD = (DCYBSILTSPOD * beta) + (DCYDRSILTSPOD * aerosurfaces->Rudder);
				DCLNSILTSPOD = (DCLNBSILTSPOD * beta) + (DCLNDRSILTSPOD * aerosurfaces->Rudder);
				DCLLSILTSPOD = (DCLLBSILTSPOD * beta) + (DCLLDRSILTSPOD * aerosurfaces->Rudder);
			}

			CY = (CY * sign( beta )) + (DCYBE * beta) + (CYDA * aerosurfaces->Aileron) + (CYDR * aerosurfaces->Rudder) + (DCYBSB * beta) + DCYSILTSPOD;
			CLN = (CLN * sign( beta )) + (DCLNBE * beta) + (CLNDA * aerosurfaces->Aileron) + (DCLNBSB * beta) + (CLNDR * aerosurfaces->Rudder) + DCLNSILTSPOD;
			CLL = (CLL * sign( beta )) + (DCLLBE * beta) + (CLLDA * aerosurfaces->Aileron) + (CLLDR * aerosurfaces->Rudder) + (DCLLBSB * beta) + DCLLSILTSPOD;

			// convert CY from body axis to stability axis
			*cl = CY * cos( beta );// shuttle system matches Orbiter system
			*cm = -CLN;// shuttle system is symmetrical to Orbiter system
			*cd = fabs( CY * sin( beta ) );// should always be positive

			// apply roll moment
			double qbar = v->GetDynPressure();
			double L = qbar * ORBITER_WING_AREA * ORBITER_SPAN * CLL;
			v->AddForce( _V( 0.0, 0.5 * L, 0.0 ), _V( -1.0, 0.0, 0.0 ) );
			v->AddForce( _V( 0.0, -0.5 * L, 0.0 ), _V( 1.0, 0.0, 0.0 ) );
		}
		else
		{
			*cl = 0.0;
			*cm = 0.0;
			*cd = 0.0;
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in HLiftCoeff: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(SSV_OV) [FATAL ERROR] Exception in HLiftCoeff" );
		abort();
	}
}
