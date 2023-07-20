/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/08/24   GLS
2021/06/16   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/09/30   GLS
2022/12/21   indy91
2023/02/10   indy91
********************************************/
#include <PEG4Targeting.h>
#include <MathSSV.h>

void LTVC_TSK(double C1, double C2, double EARTH_MU, double EP_TRANSFER, VECTOR3 IY, VECTOR3 RP, VECTOR3 RT, bool &FLAG, VECTOR3 &VD, double &THETA)
{
	double R0_MAG, R1_MAG, K, Z;

	//Compute the predicted thrust burnout and target position magnitudes
	R0_MAG = length(RP);
	R1_MAG = length(RT);
	//Compute the normalized delta altitude
	K = (R1_MAG - R0_MAG) / R0_MAG;
	//Compute the transfer angle from burnout to target
	Z = R0_MAG * R1_MAG - dotp(RP, RT);
	//Check if the angle between the desired thrust cutoff position vector and plane–projected target vector is too small
	if (Z > R0_MAG*R1_MAG*EP_TRANSFER)
	{
		double W, A, B, C, D;

		//Calculate the cotangent of half the transfer angle, THETA
		W = dotp(crossp(RT, RP), IY) / Z;
		//Calculate the transfer angle
		THETA = PI + atan2(-2.0*W, 1.0 - W * W);
		//Normalized constants for the velocity calculations
		A = K * (1.0 + W * W) + 2.0*(1.0 - C2 * W);
		B = C1 * W;
		C = 2.0*EARTH_MU / R1_MAG;
		D = B * B + A * C;
		//If D is less than zero, no solution exists
		if (D >= 0.0)
		{
			double VH1, VR1;

			//Calcuate required horizontal and radial velocity components
			VH1 = C / (sqrt(D) - B);
			VR1 = C1 + C2 * VH1;
			//Calculate desired burnout inertial velocity vector
			VD = (RP*(K*W*VH1 - VR1) + crossp(RP, IY)*(1.0 + K)*VH1) / R0_MAG;
			FLAG = false;
		}
		else
		{
			FLAG = true;
		}
	}
	else
	{
		FLAG = true;
	}
}

PEG4Targeting::PEG4Targeting()
: currentState(ERR)
{
}

PEG4Targeting::~PEG4Targeting()
{
}

void PEG4Targeting::SetPlanetParameters(double mu)
{
	EARTH_MU = mu;
}

void PEG4Targeting::SetPEG4Targets(double C1, double C2, const VECTOR3& _RGD, const VECTOR3& _VGD, double _TGD, const VECTOR3 &_RT, double _FT, double _VEX, float _M, float _MBO, int _SFUELD, int _NMAX)
{
	this->C1 = C1;
	this->C2 = C2;
	RGD = _RGD;
	VGD = _VGD;
	TGD = _TGD;
	RT = _RT;
	FT = _FT;
	VEX = _VEX;
	M = _M;
	MBO = _MBO;
	SFUELD = _SFUELD;
	NMAX = _NMAX;

	RP = RGD;
	VP = VGD;
	TP = _TGD;
	THETA_DOT = sqrt(EARTH_MU / pow(length(RGD), 3));
	LAMDXZ = 0.0;
	TGO = 0.0;
	VGO = _V(0, 0, 0);

	if (VelocityToBeGainedSubtask())
	{
		currentState = ERR;
		return;
	}

	ATR = FT / M;

	iterationCounter = 0;
	currentState = BURN_PROP;
}

bool PEG4Targeting::PEG_TSK()
{
	if (currentState == BURN_PROP)
	{
		VGOMAG = length(VGO);
		TimeToGoSubtask();
		ThrustIntegralSubtask();
		ReferenceThrustVectorsSubtask();
		BurnoutStateVectorPredictionSubtask();

		currentState = COAST_PROP;
	}
	else if (currentState == COAST_PROP)
	{
		if (VelocityToBeGainedSubtask())
		{
			currentState = ERR;
		}
		else
		{
			VelocityToBeGainedFuelDepletionSubtask();
			ConvergenceCheckSubtask();
			if (SCONV)
			{
				currentState = COMPLETE;
			}
			else
			{
				iterationCounter++;
				if (iterationCounter >= NMAX)
				{
					//Stop iterations
					currentState = ERR;
				}
				else
				{
					//Continue
					currentState = BURN_PROP;
				}
			}
		}
	}

	return (currentState >= COMPLETE);
}

VECTOR3 PEG4Targeting::GetDeltaV() const
{
	return VGO;
}

void PEG4Targeting::GetStateVectors(VECTOR3 &_RP, VECTOR3 &_VD, VECTOR3 &_RC1, VECTOR3 &_VC1, VECTOR3 &_RC2, VECTOR3 &_VC2) const
{
	_RP = RP;
	_VD = VD;
	_RC1 = RC1;
	_VC1 = VC1;
	_RC2 = RC2;
	_VC2 = VC2;
}

bool PEG4Targeting::Converged() const
{
	return currentState == COMPLETE;
}

bool PEG4Targeting::VelocityToBeGainedSubtask()
{
	double DTCOAST, RHOMAG, THETA;
	bool FLAG;

	IY = unit(crossp(VP, RP));
	LTVC_TSK(C1, C2, EARTH_MU, EP_TRANSFER, IY, RP, RT, FLAG, VD, THETA);

	if (FLAG) return true; //Exit PEG task for LTVC error

	DTCOAST = THETA / THETA_DOT;
	RHOMAG = 1.0 / (1.0 + 0.75*TGO / DTCOAST);
	VMISS = VP - VD;
	VGO = VGO - VMISS * RHOMAG;

	return false;
}

void PEG4Targeting::VelocityToBeGainedFuelDepletionSubtask()
{
	VECTOR3 VGIP;

	VGIP = VGO - IY * dotp(VGO, IY);
	VGO = VGIP;

	if (SFUELD != 0)
	{
		double VGOYS, VGOD;

		if (M <= MBO)
		{
			VGOD = 0.0;
		}
		else
		{
			VGOD = VEX * log(M / MBO);
		}

		VGOYS = VGOD * VGOD - dotp(VGIP, VGIP);

		if (VGOYS > 0)
		{
			VGO = VGIP - IY * SFUELD * sqrt(VGOYS);
		}
	}
}

void PEG4Targeting::TimeToGoSubtask()
{
	VRATIO = VGOMAG / (6.0*VEX);
	TGO = VGOMAG / (ATR*(1.0 + 3.0*VRATIO + 3.0*pow(VRATIO, 2)));
	TP = TGD + TGO;
}

void PEG4Targeting::ThrustIntegralSubtask()
{
	JOL = 0.5*TGO*(1.0 + VRATIO);
	S = 0.5*VGOMAG*TGO*(1.0 - VRATIO);
	QPRIME = VGOMAG * TGO*TGO / 12.0;
}

void PEG4Targeting::ReferenceThrustVectorsSubtask()
{
	LAM = VGO / VGOMAG;
	LAMD = crossp(LAM, IY)*LAMDXZ;
}

void PEG4Targeting::BurnoutStateVectorPredictionSubtask()
{
	VECTOR3 RGO, RGRAV, VGRAV;
	double DTAVG;

	RGO = LAMD * QPRIME + LAM * S;
	RC1 = RGD - RGO / 10.0 - VGO * TGO / 30.0;
	VC1 = VGD + RGO / TGO * 6.0 / 5.0 - VGO / 10.0;
	DTAVG = 2.0; //TBD
	PREDICTOR(RC1, VC1, TGD, TP, DTAVG, RC2, VC2);
	VGRAV = VC2 - VC1;
	RGRAV = RC2 - RC1 - VC1 * TGO;
	RP = RGD + VGD * TGO + RGRAV + RGO;
	VP = VGD + VGRAV + VGO;
}

void PEG4Targeting::ConvergenceCheckSubtask()
{
	VGOMAG = length(VGO);
	if (length(VMISS) <= KMISS * VGOMAG)
	{
		SCONV = true;
	}
	else
	{
		SCONV = false;
	}
}

void PEG4Targeting::PREDICTOR(VECTOR3 R_INIT, VECTOR3 V_INIT, double T_INIT, double T_FINAL, double DT_MAX, VECTOR3 &R_FINAL, VECTOR3 &V_FINAL) const
{
	R_FINAL = R_INIT;
	V_FINAL = V_INIT;

	VECTOR3 G_PREVIOUS, G_FINAL;
	double STEP_SIZE, T, R_INV;
	int NUMBER_STEPS;

	//Establish the fixed integration STEP_SIZE by dividing the time interval into the smallest number(NUMBER_STEPS) of subintervals consistent with DT_MAX
	NUMBER_STEPS = (int)(max(round(abs(T_FINAL - T_INIT) / DT_MAX), 1));
	STEP_SIZE = (T_FINAL - T_INIT) / NUMBER_STEPS;
	T = T_INIT;

	//Check the input parameter GMD_PRED. If the value of this parameter is zero (a setting which indicates the user wants to use
	//a conic approximation), the acceleration vector G_PREVIOUS will contain only the central force term
	CENTRAL(R_FINAL, G_PREVIOUS, R_INV);

	for (int I = 0;I < NUMBER_STEPS;I++)
	{
		//Advance the time by an amount equal to STEP_SIZE
		T = T + STEP_SIZE;
		//Advance the position
		R_FINAL = R_FINAL + (V_FINAL + G_PREVIOUS * 0.5*STEP_SIZE)*STEP_SIZE;

		CENTRAL(R_FINAL, G_FINAL, R_INV);

		//Advance the velocity
		V_FINAL = V_FINAL + (G_PREVIOUS + G_FINAL)*0.5*STEP_SIZE;
		//Obtain a corrected value for the position
		R_FINAL = R_FINAL + (G_FINAL - G_PREVIOUS)*pow(STEP_SIZE, 2) / 6.0;
		//Save the value of G for the next cycle
		G_PREVIOUS = G_FINAL;
	}
}

void PEG4Targeting::CENTRAL(VECTOR3 R, VECTOR3 &ACCEL, double &R_INV) const
{
	R_INV = 1.0 / length(R);
	ACCEL = -R * EARTH_MU*pow(R_INV, 3);
}