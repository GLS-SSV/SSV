/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/06/16   GLS
2021/08/24   GLS
********************************************/
#include "LambertBurnTargeting.h"
#include "MathSSV.h"
#include <EngConst.h>

LambertBurnTargeting::LambertBurnTargeting()
	: currentState(CONVERGED)
{
	N_MAX = 10;
	N_MIN = 3;
	DU = 0.00001*RAD; //TBD
	EP_TRANSFER = 8.0*RAD;
	EPS_U = 1.e-6; //TBD
	EARTH_MU = 0.3986012e15; //TBD
	CONE = 8.0*RAD;
	R_TOL = 250.0*0.3048;

	step = -1;
}

LambertBurnTargeting::~LambertBurnTargeting()
{
}

void LambertBurnTargeting::SetTargetingData(const VECTOR3& _RS_T1TIG, const VECTOR3& _VS_T1TIG, const VECTOR3& _RS_T2TIG, double _T1_TIG, double _T2_TIG, double vesselMass, int _GMD, int _GMO)
{
	RS_T1TIG = _RS_T1TIG;
	VS_T1TIG = _VS_T1TIG;
	RS_T2TIG = _RS_T2TIG;
	T1_TIG = _T1_TIG;
	T2_TIG = _T2_TIG;
	step = 0;
	currentState = RUNNING;
	GMD = _GMD;
	GMO = _GMO;

	R_MISS = _V(1, 0, 0)*999999999.0; //Just some high number
	VS_REQUIRED = _V(0, 0, 0);
}

void LambertBurnTargeting::Step()
{
	if (currentState != RUNNING) return;

	switch (step)
	{
	case 0:
		//Set or initialize variables that are used in the iteration to find the required velocity
		ALARM = 0;
		DEL_T_TRAN = T2_TIG - T1_TIG;
		R_OFFSET = RS_T2TIG;
		T_OFFSET = T2_TIG;
		N = 0;
		VG = _V(0, 0, 0);
		VG_MAG = 0.0;
		ALPHA = 2.0 / length(RS_T1TIG) - dotp(VS_T1TIG, VS_T1TIG) / EARTH_MU;
		ORB_RATE = ALPHA * sqrt(ALPHA*EARTH_MU);
		S_ROTATE = 1;
		UN_REF = unit(crossp(RS_T1TIG, VS_T1TIG));
		RS_REF = RS_T1TIG;
		ACC = 100000.0; //THRUST / STS()->getmass;
		step++;
		break;
	case 1:
		N++;
		RS_IP0 = RS_REF;
		if (S_ROTATE != 0)
		{
			UN = crossp(RS_IP0, R_OFFSET);
			if (dotp(UN, UN_REF) >= 0.0)
			{
				S_ROTATE = 1;
			}
			else
			{
				S_ROTATE = -1;
			}
			SBETA = length(UN)*(double)S_ROTATE;
			CBETA = dotp(RS_IP0, R_OFFSET);
			BBEF = PI + atan2(-SBETA, -CBETA);
			BAFT = BBEF - ORB_RATE * VG_MAG / ACC;
			if (BBEF < PI - CONE || BAFT > PI + CONE)
			{
				UN = UN / SBETA;
			}
			else
			{
				N = 0;
				S_ROTATE = 0;
				UN = UN_REF;
				R_OFFSET = R_OFFSET - UN * dotp(R_OFFSET, UN);
			}
		}
		LAMBERT(RS_IP0, R_OFFSET, UN, DEL_T_TRAN, VS_REQUIRED);
		if (ALARM)
		{
			currentState = ERR;
			return;
		}
		VG = VS_REQUIRED - VS_T1TIG;
		VG_MAG = length(VG);
		step++;
		break;
	case 2:
		propagator.ONORBIT_PREDICT(RS_IP0, VS_REQUIRED, T1_TIG, T2_TIG, GMO, GMD, false, false, 0, RS_TERMINAL, VS_TERMINAL);
		step++;
		break;
	case 3:
		R_MISS = RS_TERMINAL - RS_T2TIG;
		if (S_ROTATE == 0)
		{
			R_MISS = R_MISS - UN * dotp(R_MISS, UN);
		}
		R_OFFSET = R_OFFSET - R_MISS;
		if (N > N_MAX)
		{
			ALARM = 6;
			currentState = ERR;
			return;
		}
		//End condition
		if (N >= N_MIN && length(R_MISS) < R_TOL)
		{
			//End
			currentState = CONVERGED;
		}
		else
		{
			//Continue
			step = 1;
		}
		break;
	}
}

LambertBurnTargeting::RESULT LambertBurnTargeting::CurrentState() const
{
	return currentState;
}

void LambertBurnTargeting::GetData(VECTOR3& _VS_REQUIRED, VECTOR3& _R_OFFSET, double &_T_OFFSET, int &_S_ROTATE, double &_MissDistance, int &_ALARM) const
{
	_VS_REQUIRED = VS_REQUIRED;
	_R_OFFSET = R_OFFSET;
	_T_OFFSET = T_OFFSET;
	_S_ROTATE = S_ROTATE;
	_MissDistance = length(R_MISS);
	_ALARM = ALARM;
}

void LambertBurnTargeting::LAMBERT(VECTOR3 R0, VECTOR3 R1, VECTOR3 UN, double DEL_T_TRAN, VECTOR3 &VS_REQUIRED)
{
	double R0_MAG, R1_MAG, R_PARABOLA, V_PARABOLA, Z, VH, U_MIN, U_MAX, LAMBDA, U, T_TILDA_DESIRED, T_MIN, T_TILDA, S_TILDA;
	double F, G, W, X, Y, TEMP, T_TILDA_ERROR, U_STEP, VR, COEF;
	int N;

	//The alarm flag is set to the off position. The alarm flag is used to indicate when problems occur from input or from calculations
	ALARM = 0;
	//Calculate the magnitude of the initial vector and the final vector
	R0_MAG = length(R0);
	R1_MAG = length(R1);
	//Calculate the semiperimeter of the transfer triangle to be used as a normalizing constant
	R_PARABOLA = (R0_MAG + R1_MAG + length(R1 - R0)) / 2.0;
	//Calculate the parabolic velocity at perigee for R_PARABOLA for use as a normalizing factor
	V_PARABOLA = sqrt(2.0*EARTH_MU / R_PARABOLA);
	//Calculate the parameter Z
	Z = R0_MAG * R1_MAG - dotp(R0, R1);
	if (Z <= EP_TRANSFER * R0_MAG*R1_MAG)
	{
		ALARM = 2;
		return;
	}
	//Calculate the contant of theta/2
	Z = dotp(crossp(R0, R1), UN / Z);
	//Calculate the parameter VH
	VH = sqrt(R0_MAG*R1_MAG / (1.0 + Z * Z));
	//Set the intial value on the counter to count the number of iterations
	N = 0;
	//Set the upper and lower limits of the independent variable
	U_MAX = 1.0 - DU / 2.0;
	U_MIN = -1.0;
	//Calculate the constant parameter LAMBDA
	LAMBDA = (VH / R_PARABOLA)*Z;
	//Calculate the first guess for the independent variable. The first guess assumes a circular orbit
	U = LAMBDA / sqrt(1.0 + LAMBDA * LAMBDA);
	//Calculate the normalized transfer time
	T_TILDA_DESIRED = (V_PARABOLA / R_PARABOLA)*DEL_T_TRAN;
	//Determine a transfer time that is slightly greater than the parabolic transfer time
	T_MIN = (2.0 / 3.0)*(1.0 - pow(LAMBDA, 3)) + 0.4*(1.0 - pow(LAMBDA, 5))*DU;
	if (DEL_T_TRAN < 0.0 || DEL_T_TRAN <= T_MIN)
	{
		ALARM = 1;
		return;
	}
	bool done = false;
	do
	{
		//Increment counter
		N++;
		if (N >= N_MAX)
		{
			ALARM = 5;
			return;
		}
		W = sqrt(1.0 - U * U);
		X = LAMBDA * W;
		Y = sqrt(1.0 - X * X);
		F = W * Y - U * X;
		G = U * Y + W * X;
		//Current value of the transfer time
		TEMP = atan2(F, G);
		if (TEMP < 0.0)
		{
			TEMP += PI2;
		}
		//Current value of the transfer time
		T_TILDA = (TEMP - (U*W - X * Y)) / pow(W, 3);
		//Determine the slope of T_TILDA with respect to the independent variable U for use with the Newton-Raphson iteration
		S_TILDA = (3.0*U*T_TILDA - 2.0*(1.0 - U / Y * pow(LAMBDA, 3))) / pow(W, 2);
		//Determine the error in the current of T_TILDA and the desired value T_TILDA_DESIRED
		T_TILDA_ERROR = T_TILDA_DESIRED - T_TILDA;
		//Determine if the error in T_TILDA is small enough
		if (abs(T_TILDA_ERROR) > T_TILDA_DESIRED*EPS_U)
		{
			//Calculate a change in the current value of U
			U_STEP = T_TILDA_ERROR / S_TILDA;
			if (U_STEP > 0.0)
			{
				U_MIN = U;
				U = U + U_STEP;
				if (U > U_MAX)
				{
					U = (U_MIN + U_MAX) / 2.0;
				}
			}
			else
			{
				U_MAX = U;
				U = U + U_STEP;
				if (U < U_MIN)
				{
					U = (U_MIN + U_MAX) / 2.0;
				}
			}
		}
		else
		{
			done = true;
		}

	} while (N < N_MAX && done == false);

	//Calculate required initial velocity
	VH = VH / R0_MAG;
	VR = (R_PARABOLA / R0_MAG)*LAMBDA - G;
	COEF = V_PARABOLA / (Y - LAMBDA * U);
	VS_REQUIRED = (R0*VR + crossp(UN, R0)*VH)*COEF / R0_MAG;
}