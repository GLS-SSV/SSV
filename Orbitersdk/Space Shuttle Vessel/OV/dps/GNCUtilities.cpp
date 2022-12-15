#include "GNCUtilities.h"
#include "MasterTimingUnit.h"
#include "../Atlantis.h"
#include "MathSSV.h"

namespace dps
{
	MATRIX3 MATRIX(VECTOR3 A, VECTOR3 B, VECTOR3 C)
	{
		return _M(A.x, A.y, A.z, B.x, B.y, B.z, C.x, C.y, C.z);
	}

	MATRIX3 EF_TO_TOPDET(double LAT_GEOD, double LON)
	{
		double CLON, SLON, CLAT, SLAT;

		CLON = cos(LON);
		SLON = sin(LON);
		CLAT = cos(LAT_GEOD);
		SLAT = sin(LAT_GEOD);

		return _M(-SLAT * CLON, -SLAT * SLON, CLAT, -SLON, CLON, 0, -CLAT * CLON, -CLAT * SLON, -SLAT);
	}

	MATRIX3 EF_TO_RUNWAY(double LAT_GEOD, double LON, double AZ)
	{
		double CAZ = cos(AZ);
		double SAZ = sin(AZ);
		return mul(_M(CAZ, SAZ, 0, -SAZ, CAZ, 0, 0, 0, 1), EF_TO_TOPDET(LAT_GEOD, LON));
	}

	MATRIX3 EF_TO_SCANNER(double LAT_GEOD, double LON, double AZ)
	{
		return mul(_M(1, 0, 0, 0, -1, 0, 0, 0, -1), EF_TO_RUNWAY(LAT_GEOD, LON, AZ));
	}

	void EF_TO_GEODETIC(VECTOR3 R_EF, double &LAT_GEOD, double &LON, double &ALT)
	{
		double FLATCON, A_O, R_XY, R, SIN_P, COS_P, RAD_P, DEL, DEL_LAT, PHI;

		FLATCON = 1.0 - pow(1.0 - ELLIPT, 2);
		A_O = 1.0 - FLATCON;
		R_XY = pow(R_EF.x, 2) + pow(R_EF.y, 2);
		R = sqrt(R_XY + pow(R_EF.z, 2));
		SIN_P = R_EF.z / R;
		COS_P = sqrt(R_XY) / R;
		RAD_P = EARTH_RADIUS_EQUATOR / sqrt(1.0 + FLATCON * pow(SIN_P, 2) / A_O);
		DEL = (FLATCON*SIN_P*COS_P) / (1.0 - FLATCON * pow(COS_P, 2));
		DEL_LAT = RAD_P * DEL / R;
		PHI = atan(SIN_P / COS_P);
		LAT_GEOD = PHI + DEL_LAT;
		LON = atan2(R_EF.y, R_EF.x);
		ALT = (R - RAD_P)*(1.0 - 0.5*DEL*DEL_LAT);
	}

	VECTOR3 GEODETIC_TO_EF(double LAT_GEOD, double LON, double ALT)
	{
		double CLAT, SLAT, DUM, DUM1, R_EF_EQUAT;

		CLAT = cos(LAT_GEOD);
		SLAT = sin(LAT_GEOD);
		DUM = pow(1.0 - ELLIPT, 2);
		DUM1 = EARTH_RADIUS_EQUATOR / sqrt(CLAT*CLAT + SLAT * SLAT*DUM);
		R_EF_EQUAT = (DUM1 + ALT)*CLAT;
		return _V(R_EF_EQUAT*cos(LON), R_EF_EQUAT*sin(LON), (DUM*DUM1 + ALT)*SLAT);
	}

	GNCUtilities::GNCUtilities(SimpleGPCSystem * _gpc) : SimpleGPCSoftware(_gpc, "GNCUtilities")
	{
		T_EPOCH = 0.0;
		M_M50TOEF_AT_EPOCH = _M(1, 0, 0, 0, 1, 0, 0, 0, 1);
		J2_GRAV = 0.0;
	}

	GNCUtilities::~GNCUtilities()
	{

	}

	void GNCUtilities::Realize()
	{
		//In the future this should only be called once in OPS9 or on request
		M50_TO_EF_AT_EPOCH();

		//Should J2 better go into the COMPOOL? It would be hardcoded, but can't be in SSV to support spherical gravity
		if (STS()->NonsphericalGravityEnabled())
		{
			J2_GRAV = 1.0826271e-3f;
		}
		else
		{
			J2_GRAV = 0.0f;
		}
	}

	void GNCUtilities::M50_TO_EF_AT_EPOCH()
	{
		//Store time in GMT
		T_EPOCH = GMTfromMJD(oapiGetSimMJD());

		//Get Earth rotation matrix (left-handed local to global) from Orbiter API
		MATRIX3 M_EF_to_J2000;
		oapiGetRotationMatrix(oapiGetObjectByName("Earth"), &M_EF_to_J2000);

		//Convert to right-handed
		M_EF_to_J2000 = MatrixRH_LH(M_EF_to_J2000);

		//Calculate M50 to Earth-fixed matrix
		M_M50TOEF_AT_EPOCH = Transpose(mul(M_J2000_to_M50, M_EF_to_J2000));

		//Save Earth pole unit vector
		WriteCOMPOOL_VD(SCP_EARTH_POLE, _V(M_M50TOEF_AT_EPOCH.m31, M_M50TOEF_AT_EPOCH.m32, M_M50TOEF_AT_EPOCH.m33));
	}

	MATRIX3 GNCUtilities::EARTH_FIXED_TO_M50_COORD(double TIME) const
	{
		double LAM, CLAM, SLAM;

		LAM = EARTH_RATE * (TIME - T_EPOCH);
		CLAM = cos(LAM);
		SLAM = sin(LAM);
		return mul(Transpose(M_M50TOEF_AT_EPOCH), _M(CLAM, -SLAM, 0, SLAM, CLAM, 0, 0, 0, 1));
	}

	double GNCUtilities::H_ELLIPSOID(VECTOR3 R) const
	{
		return length(R) - (1.0 - ELLIPT)*EARTH_RADIUS_EQUATOR / sqrt(1.0 + (pow(1.0 - ELLIPT, 2) - 1.0)*(1.0 - pow(dotp(unit(R), ReadCOMPOOL_VD(SCP_EARTH_POLE)), 2)));
	}

	VECTOR3 GNCUtilities::V_REL(VECTOR3 V, VECTOR3 R) const
	{
		return V - crossp(ReadCOMPOOL_VD(SCP_EARTH_POLE), R)*EARTH_RATE;
	}

	float GNCUtilities::GetJ2() const
	{
		return J2_GRAV;
	}
}