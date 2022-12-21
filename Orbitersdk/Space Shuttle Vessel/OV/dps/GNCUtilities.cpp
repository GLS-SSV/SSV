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

	void MAT_TO_QUAT(MATRIX3 M, double &QS, VECTOR3 &QV)
	{
		double q[4], T, M2[3][3];
		int i, j, k, n;

		M2[0][0] = M.m11; M2[0][1] = M.m12; M2[0][2] = M.m13;
		M2[1][0] = M.m21; M2[1][1] = M.m22; M2[1][2] = M.m23;
		M2[2][0] = M.m31; M2[2][1] = M.m32; M2[2][2] = M.m33;

		i = n = 0;

		q[0] = T = M.m11 + M.m22 + M.m33;
		for (k = 1;k <= 3;k++)
		{
			if (M2[k - 1][k - 1] > q[0])
			{
				i = k;
				q[0] = M2[k - 1][k - 1];
			}
		}
		T = sqrt(1.0 + 2.0*q[0] - T);
		k = 2;
		do
		{
			n = n + 1;
			j = 6 - n - k;
			if (i*(n - i) == 0)
			{
				q[0] = q[n] = (M2[j - 1][k - 1] - M2[k - 1][j - 1]) / T;
			}
			else
			{
				q[j + k - i] = (M2[j - 1][k - 1] + M2[k - 1][j - 1]) / T;
			}

			if (k == 2)
			{
				k = 3;
			}
			else if (k == 3)
			{
				k = 1;
			}
			else
			{
				k = 4;
			}
		} while (k != 4);

		if (i == 0)
		{
			q[0] = T;
		}
		else
		{
			q[i] = T;
		}
		T = sign(q[0]) / 2.0;

		QS = T * q[0];
		QV = _V(q[1], q[2], q[3])*T;
	}

	void RV_TO_QLVLH(VECTOR3 XR, VECTOR3 XV, double &QS, VECTOR3 &QV)
	{
		MATRIX3 XM;
		VECTOR3 XX, XY, XZ;

		XZ = unit(-XR);
		XY = unit(crossp(XV, XR));
		XX = unit(crossp(XY, XZ));
		XM = Transpose(MATRIX(XX, XY, XZ));
		MAT_TO_QUAT(XM, QS, QV);
	}

	VECTOR3 QUAT_XFORM(double QBAS, VECTOR3 QBAV, VECTOR3 W_A)
	{
		VECTOR3 VT = crossp(QBAV, W_A);
		return W_A + (VT*QBAS + crossp(QBAV, VT))*2.0;
	}

	void QUAT_MULT(double Q1S, VECTOR3 Q1V, double Q2S, VECTOR3 Q2V, double &Q3S, VECTOR3 &Q3V)
	{
		Q3S = Q1S * Q2S - dotp(Q1V, Q2V);
		Q3V = Q2V * Q1S + Q1V * Q2S + crossp(Q1V, Q2V);
	}

	void QUAT_TO_ADI_ANG(double XQS, VECTOR3 XQV, double &XPITCHSINE, double &XPITCHCOS, double &XYAWSINE, double &XYAWCOS, double &XROLLSINE, double &XROLLCOS, bool &XFLAG)
	{
		XFLAG = true;
		XYAWSINE = 2.0*(XQV.x*XQV.y - XQS * XQV.z);
		XYAWCOS = sqrt(1.0 - pow(XYAWSINE, 2));
		if (XYAWCOS < 0.03)
		{
			XFLAG = false;
		}
		else
		{
			double XYAWSEC = 1.0 / XYAWCOS;

			XROLLSINE = -2.0*XYAWSEC*(XQV.y*XQV.z + XQS * XQV.x);
			XROLLCOS = XYAWSEC * (1.0 - 2.0*(pow(XQV.x, 2) + pow(XQV.z, 2)));
			XPITCHSINE = -2.0*XYAWSEC*(XQV.x*XQV.z + XQS * XQV.y);
			XPITCHCOS = XYAWSEC * (1.0 - 2.0*(pow(XQV.y, 2) + pow(XQV.z, 2)));
		}
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