/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/05/08   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/16   GLS
2021/06/18   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/02   GLS
2022/04/17   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/05/01   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/08/15   GLS
2022/09/29   GLS
2022/11/15   GLS
2022/12/17   GLS
2022/12/23   GLS
2025/12/27   indy91
2025/12/31   indy91
2026/01/06   indy91
********************************************/
#include "AscentDAP.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>
#include "SSME_SOP.h"
#include "SSME_Operations.h"
#include "MPS_ATVC_CMD_SOP.h"
#include "SRBSepSequence.h"
#include "RHC_SOP.h"
#include "SBTC_SOP.h"
#include "../../IDP.h"
#include "../../../mission/Mission.h"
#include <cassert>
#include <EngConst.h>
#include "GNCUtilities.h"
#include "StateVectorSoftware.h"

namespace dps
{
	constexpr unsigned int STAGE1_GUIDANCE_TABLE_SIZE = 30;
	constexpr double DEFAULT_STAGE1_GUIDANCE_TABLE_VEL[STAGE1_GUIDANCE_TABLE_SIZE] = {0, 127/MPS2FPS, 341/MPS2FPS, 414/MPS2FPS, 493/MPS2FPS, 571/MPS2FPS, 678/MPS2FPS, 747/MPS2FPS, 846/MPS2FPS, 932/MPS2FPS, 1068/MPS2FPS, 1149/MPS2FPS, 1304/MPS2FPS, 1382/MPS2FPS, 1463/MPS2FPS, 1550/MPS2FPS, 1693/MPS2FPS, 1797/MPS2FPS, 2027/MPS2FPS, 2154/MPS2FPS, 2286/MPS2FPS, 2353/MPS2FPS, 2421/MPS2FPS, 2746/MPS2FPS, 3019/MPS2FPS, 3157/MPS2FPS, 3350/MPS2FPS, 3573/MPS2FPS, 3950/MPS2FPS, 5000/MPS2FPS};
	constexpr double DEFAULT_STAGE1_GUIDANCE_TABLE_PITCH[STAGE1_GUIDANCE_TABLE_SIZE] = {90.0, 70.5, 70.1, 70.0, 69.7, 69.4, 68.6, 67.8, 66.2, 64.4, 62.1, 61.1, 59.0, 58.2, 57.8, 57.1, 54.7, 52.9, 48.7, 46.4, 43.0, 42.0, 41.6, 38.6, 36.3, 35.3, 33.9, 32.4, 29.8, 22.6};

	constexpr double ASCENT_MAJOR_CYCLE = 1.0000; // time (seconds) between guidance major cycles
	constexpr double PEG_STOP_TIME = 7.000; // time (seconds) before expected MECO to stop PEG calculations and hold constant attitude (in real life, PEG ends 40 s before MECO, but active attitude control continues)

	constexpr double SSME_TAILOFF_DV_67 = 90;// fps
	constexpr double SSME_TAILOFF_DV_91_1EO = 75;// fps
	constexpr double SSME_TAILOFF_DV_91_2EO = 35;// fps

	AscentGuidance::AscentGuidance()
	{
		RDMAG = 0.0;
		VDMAG = 0.0;
		GAMD = 0.0;
		IYD = _V(0, 0, 0);

		DVGO = _V(0, 0, 0);
		DVS = _V(0, 0, 0);
		IX = _V(0, 0, 0);
		IY = _V(0, 0, 0);
		LAM = _V(0, 0, 0);
		LAMC = _V(0, 0, 0);
		LAMD = _V(0, 0, 0);
		OMEGA = _V(0, 0, 0);
		RBIAS = _V(0, 0, 0);
		RD = _V(0, 0, 0);
		RGD = _V(0, 0, 0);
		RGRAV = _V(0, 0, 0);
		RGO = _V(0, 0, 0);
		RP = _V(0, 0, 0);
		RTHRUST = _V(0, 0, 0);
		VD = _V(0, 0, 0);
		VGD = _V(0, 0, 0);
		VGO = _V(0, 0, 0);
		VMISS = _V(0, 0, 0);
		VP = _V(0, 0, 0);
		VTHRUST = _V(0, 0, 0);

		ATR = 0.0;
		DT_LIMIT = 0.0;
		EMISS = 0.0;
		FT = 0.0;
		IF_MAG_I = 0.0;
		LA[0] = LA[1] = LA[2] = 0.0;
		SA[0] = SA[1] = SA[2] = 0.0;
		QA[0] = QA[1] = QA[2] = 0.0;
		LAMDMAG = 0.0;
		M = 0.0;
		PHI = 0.0;
		RMAG = 0.0;
		TAU[0] = TAU[1] = TAU[2] = 0.0;
		TB[0] = TB[1] = TB[2] = 0.0;
		TFAIL = 0.0;
		TGD = 0.0;
		TGO = 0.0;
		TGOA[0] = TGOA[1] = TGOA[2] = 0.0;
		TGOP = 0.0;
		TI = 0.0;
		TLAM = 0.0;
		TP = 0.0;
		TPREV = 0.0;
		TPRIME = 0.0;
		VEX = 0.0;
		VEXA[0] = VEXA[1] = VEXA[2] = 0.0;
		VGOMAG = 0.0;

		QPRIME = L = J = S = JOL = 0.0;

		KPHASE = 0;
		N = 0;
		N_CYCLE = 0;

		SALT = false;
		SCONV = false;
		SINIT = false;
		SPLANE = false;

		// Temporary
		T_GMTLO = 0.0;
	}

	void AscentGuidance::Init(double t_GMTLO, double r_D, double v_D, double gamma_D, VECTOR3 IY_M50)
	{
		// Inputs in metric

		RDMAG = r_D * MPS2FPS;
		VDMAG = v_D * MPS2FPS;
		GAMD = gamma_D;
		IYD = unit(IY_M50); // TBD: Unit vector for safety, for now
		T_GMTLO = t_GMTLO;

		SINIT = true;
		SCONV = false;
		TFAIL = 0.0; // TBD: Implement this
		DT_LIMIT = DTMAX;
	}

	void AscentGuidance::Cycle(VECTOR3 R, VECTOR3 V, double T, int K_CMD, int N_SSME, int N_OMS, double mass, VECTOR3 DV, VECTOR3& U_STEER)
	{
		// INPUTS:
		// R = Current position vector in M50 coordinates, meters
		// V = Current velocity vector in M50 coordinates, meters per second
		// T = Current GMT clock time, seconds
		// K_CMD = Commanded SSME throttle setting, percent
		// N_SSME = Number of active SSME engines
		// N_OMS = Number of active OMS engines
		// mass = Current mass, kg
		// DV = Change in accumulated velocity over the past guidance cycle, meters per second
		// OUTPUTS:
		// U_STEER = Desired thrust direction in M50 coordinates

		// Assign to Shuttle variables
		RGD = R * MPS2FPS;
		VGD = V * MPS2FPS;
		TGD = T;
		M = mass * KG2LBM / G_2_FPS2;
		DVS = DV * MPS2FPS;

		// TBD: These are I-loads
		double FT_SSME = 2090664.159 / LBF;
		double VEX_SSME = 453.0 * 9.80665 * MPS2FPS;
		double MDOT_SSME = FT_SSME / VEX_SSME;

		// TBD: THRST PRM TSK
		FT = 0.01 * (double)(K_CMD * N_SSME) * FT_SSME + (double)(N_OMS) * FT_OMS;
		double MDOT = 0.01 * (double)(K_CMD * N_SSME) * MDOT_SSME + (double)(N_OMS)*MDOT_OMS;
		VEX = FT / MDOT;

		AscentGuidanceTask();

		//Desired thrust direction
		U_STEER = unit(LAMC - LAMD * JOL);
	}

	void AscentGuidance::UpdateVDMAG(double v)
	{
		// Input in m/s
		VDMAG = v * MPS2FPS;
	}

	VECTOR3 AscentGuidance::CalculateEFIYVector(double Incl, double Lat, double Lng, bool north, double dt_bias) const
	{
		// Calculate insertion orbital plane (IY) in Earth-fixed coordinates, taking into account Earth rotation
		// INPUTS:
		// Incl = Desired inclination, radians
		// Lat = Launch or present latitude, radians
		// Lng = Launch or present longitude, radians
		// north = launch heading is northerly, true = north, false = south
		// dt_bias = Time bias for rotating Earth. Length of time before the target orbit plane is over the landing site, seconds

		double bias, arg, beta, dlng, h;

		const double w_E = 7.292114942213369e-05;

		bias = w_E * dt_bias;
		arg = cos(Incl) / cos(Lat);

		//Limit to 1.0
		if (abs(arg) > 1.0)
		{
			if (arg > 0.0)
			{
				beta = PI05;
			}
			else
			{
				beta = -PI05;
			}
		}
		else
		{
			beta = asin(arg);
		}
		if (north == false)
		{
			beta = PI - beta;
		}
		dlng = atan2(sin(Lat), cos(beta) / sin(beta));
		if (dlng < 0)
		{
			dlng = dlng + PI2;
		}
		if (PI - beta < 0.0)
		{
			dlng = PI + dlng;
		}
		h = Lng - dlng + bias;
		if (h < 0)
		{
			h = h + PI2;
		}

		return -_V(sin(Incl) * sin(h), -sin(Incl) * cos(h), cos(Incl));
	}

	double AscentGuidance::GetTimeRemaining() const
	{
		return TGO;
	}

	VECTOR3 AscentGuidance::GetIYVector() const
	{
		return IYD;
	}

	double AscentGuidance::GetVDMAG() const
	{
		// Output in metric
		return VDMAG * FPS2MS;
	}

	void AscentGuidance::AscentGuidanceTask()
	{
		// Estimate of acceleration based on curent mass
		ATR = FT_FACTOR * FT / M;
		// Cycle through PEG task
		N_CYCLE = 0;
		do
		{
			PEGTask();
			N_CYCLE++;
		} while (SCONV == false && N_CYCLE < N_MAX);
	}

	void AscentGuidance::PEGTask()
	{
		// Magnitude of the current position vector
		PositionMagnitudeSubTask();
		// Initialization?
		if (SINIT == false)
		{
			VGOUpdateSubtask();
		}
		else
		{
			ModeIndependentInit();
			StandardAscentModeInit();
		}
		TGOSubtask();
		ThrustIntegralsSubtask();
		ReferenceThrustVectorSubtask();
		RangeToGoSubtask();
		TurningRateVectorSubtask();
		SteeringInputsUpdateSubtask();

		BurnoutStateVectorPredictionSubtask();
		DesiredOrbitPlaneCorrectionSubtask();

		DesiredPositionAscentRTLSSubtask();
		DesiredVelocitySubtask();

		VGOCorrectionSubtask();
		ConvergenceCheckSubtask();

		CutoffPositionConstraintReleaseSubtask();
	}

	void AscentGuidance::PositionMagnitudeSubTask()
	{
		// Magnitude of the current position vector
		RMAG = length(RGD);
	}

	void AscentGuidance::VGOUpdateSubtask()
	{
		// Update velocity-to-be-gained (VGO) by decrementing it by the sensed velocity change (DVS)
		VGO = VGO - DVS;
		// If the burn time of the current guidance phase has elapsed, incremeent the guidance phase counter KPHASE
		// And set the current guidance phase burn time (TB) and accumulated burn time for this guidance phase (TGOA) to zero
		if ((TB[KPHASE - 1] - (TGD - TPRIME) <= 0) && KPHASE < N)
		{
			TB[KPHASE - 1] = 0.0;
			TGOA[KPHASE - 1] = 0.0;
			KPHASE++;
		}
		// Save value of current time for next pass
		TPRIME = TGD;
	}

	void AscentGuidance::ModeIndependentInit()
	{
		// The following parameters are required to be initialized as indicated for all guidance modes
		double B;

		KPHASE = 1;
		RBIAS = _V(0, 0, 0);
		PHI = 0.0;
		TPRIME = TGD;
		TGO = 1.0;
		OMEGA = _V(0, 0, 0);
		B = EARTH_MU / pow(RMAG, 3);
		RGRAV = -RGD * 0.5 * B;
		SINIT = false;
		TPREV = 0.0;
	}

	void AscentGuidance::StandardAscentModeInit()
	{
		// Enable plane and altitude constrained flags
		SPLANE = true;
		SALT = true;
		// If trajectory lofting is desired (TFAIL is not zero), then TFAIL is converted from MET to GMT and the number of thrust phases is set to 3
		if (TFAIL != 0.0)
		{
			TFAIL = TFAIL + T_GMTLO;
			N = 3;
		}
		else
		{
			N = 2;
		}
		// TBD: In the future, there is some AOA/ATO logic here for the IY vector
		IY = IYD;
		// Initialize the predicted cutoff position and velocity and VGO as follows:
		RP = RGD;
		VP = VGD;
		VGO = _V(0, 0, 0);
		// Perform the following subtasks for standard ascent:
		DesiredOrbitPlaneCorrectionSubtask();
		DesiredPositionAscentRTLSSubtask();
		DesiredVelocitySubtask();
		VGOCorrectionSubtask();
		ConvergenceCheckSubtask();
	}

	void AscentGuidance::DesiredOrbitPlaneCorrectionSubtask()
	{
		// The purpose of this subtask is to constrain the position (RD) to be in a desired orbit plane whenever
		// SPLANE = ON or to allow the position to remain in the predicted cutoff orbit plane whenever SPLANE = OFF.

		if (SPLANE)
		{
			RD = RP - IY * dotp(RP, IY);
		}
		else
		{
			RD = RP;
		}
	}

	void AscentGuidance::DesiredPositionAscentRTLSSubtask()
	{
		// The purpose of this subtask is to correct the magnitude of the burnout position vector when cutoff altitude is being controlled
		// (SALT = ON) for the standard ascent mode and to compute a unit vector of the burnout position vector in either case.

		IX = unit(RD);
		if (SALT)
		{
			RD = IX * RDMAG;
		}
	}

	void AscentGuidance::DesiredVelocitySubtask()
	{
		// The desired velocity vector is calculated from the following equation:
		VD = (IX * sin(GAMD) + unit(crossp(IX, IY)) * cos(GAMD)) * VDMAG;
		// If SPLANE = OFF, IY is recomputed as follows:
		if (SPLANE == false)
		{
			IY = unit(crossp(VD, RD));
		}
	}

	void AscentGuidance::VGOCorrectionSubtask()
	{
		// The purpose of this subtask is to calculate a miss in velocity, VMISS, and a delta VGO vector (DVGO), and to correct the VGO vector(VGO).

		// The velocity miss vector is computed as follows:
		VMISS = VP - VD;
		// The delta VGO vector for all PEG modes except RTLS is computed as follows:
		DVGO = -VMISS * RHOMAG;
		// The VGO vector, VGO, is corrected as follows:
		VGO = VGO + DVGO;
	}

	void AscentGuidance::ConvergenceCheckSubtask()
	{
		// Compute the magnitude of VGO and the convergence criterion as follows:
		VGOMAG = length(VGO);
		EMISS = KMISS * VGOMAG;
		// Determine whether or not VGO is converged.
		if (length(VMISS) > EMISS)
		{
			SCONV = false;
		}
	}

	void AscentGuidance::TGOSubtask()
	{
		// The purpose of this subtask is to calculate the total time–to–go until the end of the maneuver TGO,
		// and the intermediate time–to–go for each guidance phase for use in the thrust integrals.

		double LREM;
		int I;

		VGOMAG = length(VGO);
		TAU[KPHASE - 1] = VEX / ATR;
		VEXA[KPHASE - 1] = VEX;

		if (KPHASE == 1 && N == 3)
		{
			TB[0] = TFAIL - TGD;
			LA[0] = -VEX * log(1.0 - TB[0] / TAU[0]);
			TAU[1] = 0.0; //TBD: TFAIL logic
			VEXA[1] = VEX;
			LREM = VGOMAG - LA[0];
		}
		else
		{
			LREM = VGOMAG;
		}
		if (KPHASE < N)
		{
			I = N - 1;
		}
		else
		{
			I = N;
		}
		TB[N - 2] = TAU[I - 1] - VEX / AL;
		if (TB[N - 2] <= ETB)
		{
			TB[N - 2] = 0.0;
			LA[N - 2] = 0.0;
			KPHASE = N;
			TGOA[N - 2] = 0.0;
		}
		else
		{
			LA[N - 2] = -VEX * log(1.0 - TB[N - 2] / TAU[I - 1]);
			if (KPHASE == N)
			{
				KPHASE = N - 1;
				TAU[N - 2] = TAU[N - 1];
			}
		}
		if (LREM <= LA[N - 2])
		{
			LA[N - 1] = 0.0;
			TB[N - 1] = 0.0;
			LA[N - 2] = LREM;
			TB[N - 2] = TAU[I - 1] * (1.0 - exp(-LA[N - 2] / VEX));
		}
		else
		{
			LA[N - 1] = LREM - LA[N - 2];
			TB[N - 1] = LA[N - 1] / AL;
		}

		for (I = KPHASE; I <= N; I++)
		{
			TGOA[I - 1] = 0.0;
			for (int JJ = KPHASE; JJ <= I; JJ++)
			{
				TGOA[I - 1] = TGOA[I - 1] + TB[JJ - 1];
			}
		}
		TGOP = TGO;
		TGO = TGOA[N - 1];
		TP = TGD + TGO;
	}

	void AscentGuidance::ThrustIntegralsSubtask()
	{
		// The purpose of this subtask is to evaluate various time integrals of	force over mass.

		double Q, TGOB;
		int I;

		L = S = JOL = J = Q = 0.0;

		for (I = KPHASE; I <= N; I++)
		{
			if (I == 1)
			{
				TGOB = 0.0;
			}
			else
			{
				TGOB = TGOA[I - 2];
			}
			if (I < N)
			{
				SA[I - 1] = -LA[I - 1] * (TAU[I - 1] - TB[I - 1]) + VEXA[I - 1] * TB[I - 1];
				QA[I - 1] = SA[I - 1] * (TAU[I - 1] + TGOB) - 0.5 * VEXA[I - 1] * TB[I - 1] * TB[I - 1];
			}
			else
			{
				SA[I - 1] = 0.5 * LA[I - 1] * TB[I - 1];
				QA[I - 1] = SA[I - 1] * (TGOB + TB[I - 1] / 3.0);
				//TBD: Something with N_SSME == 0
			}
			S = S + SA[I - 1] + L * TB[I - 1];
			Q = Q + QA[I - 1] + J * TB[I - 1];
			L = L + LA[I - 1];
			J = J + LA[I - 1] * TGOA[I - 1] - SA[I - 1];
		}
		if (L == 0) return;
		JOL = J / L;
		QPRIME = Q - S * JOL;
		TLAM = TGD + JOL;
	}

	void AscentGuidance::ReferenceThrustVectorSubtask()
	{
		// The purpose of this subtask is to determine a reference thrust vector, LAM, for all guidance modes.
		// This vector is a unit vector in the direction of VGO

		if (VGOMAG != 0.0)
		{
			LAM = VGO / VGOMAG;
		}
		else
		{
			// TBD: Exit PEG?
		}
	}

	void AscentGuidance::RangeToGoSubtask()
	{
		// The purpose of this subtask is to compute the position–to–be–gained vector, RGO.

		VECTOR3 RGOPRIME, RGOXY, IZ;
		double RGOX, RGOY, RGOZ;

		RGRAV = RGRAV * pow(TGO / TGOP, 2);
		RGO = RD - (RGD + VGD * TGO + RGRAV) + RBIAS;
		RGOPRIME = crossp(OMEGA, LAM) * QPRIME + LAM * S;
		if (SALT)
		{
			RGOX = dotp(RGO, IX);
		}
		else
		{
			RGOX = dotp(RGOPRIME, IX);
		}
		if (SPLANE)
		{
			RGOY = dotp(RGO, IY);
		}
		else
		{
			RGOY = dotp(RGOPRIME, IY);
		}
		RGOXY = IX * RGOX + IY * RGOY;
		IZ = crossp(IX, IY);
		RGOZ = (S - dotp(LAM, RGOXY)) / dotp(LAM, IZ);
		RGO = RGOXY + IZ * RGOZ;
	}

	void AscentGuidance::TurningRateVectorSubtask()
	{
		// The purpose of this subtask is the calculation of thrust turning rate, LAMD, from RGO and previously calculated integrals.

		double EL_LIMIT, DTA_LIMIT, LAMDMAX;

		LAMD = (RGO - LAM * S) / QPRIME;
		LAMDMAG = length(LAMD);

		EL_LIMIT = sqrt(1.0 / pow(dotp(LAM, IX), 2) - 1.0) / JOL;

		DTA_LIMIT = (0.5 + PHI) / JOL;
		if (LAMDMAG > PHIDOT_MAX || LAMDMAG > DTA_LIMIT)
		{
			SCONV = false;
		}
		else
		{
			SCONV = true;
		}
		/*if (LAMDMAG > EL_LIMIT)
		{
			S_LOW_TW = true;
		}
		else
		{
			S_LOW_TW = false;
		}*/
		LAMDMAX = min(PHIDOT_MAX, min(DTA_LIMIT, EL_LIMIT));

		if (LAMDMAG > LAMDMAX)
		{
			LAMDMAG = LAMDMAX;
			LAMD = unit(LAMD) * LAMDMAG;
			RGO = LAM * S + LAMD * QPRIME;
		}
		PHI = JOL * LAMDMAG;
	}

	void AscentGuidance::SteeringInputsUpdateSubtask()
	{
		// The purpose of this subtask is to provide new steering inputs to the G/C steering interface principal function.

		//TBD: More output to do for other modes
		LAMC = LAM;
		TPREV = TP;
	}

	void AscentGuidance::BurnoutStateVectorPredictionSubtask()
	{
		// The purpose of this sub–task is to calculate the first integral of thrust and first and second time integrals of gravity
		// as required in the prediction of the burnout state vector.

		VECTOR3 R_INIT, V_INIT, R_FINAL, V_FINAL, VGRAV;
		double DT_MAX;

		int JJ;

		RTHRUST = _V(0, 0, 0);
		VTHRUST = _V(0, 0, 0);
		TI = -JOL;
		IF_MAG_I = sqrt(1.0 + LAMDMAG * LAMDMAG * TI * TI);
		if (LA[N - 1] != 0.0)
		{
			JJ = N;
		}
		else
		{
			JJ = N - 1;
		}
		for (int I = KPHASE; I <= JJ; I++)
		{
			ThrustTimeIntegralsLogic(I);
		}
		RBIAS = RGO - RTHRUST;
		R_INIT = RGD - RTHRUST * 0.1 - VTHRUST * TGO / 30.0;
		V_INIT = VGD + RTHRUST * 1.2 / TGO - VTHRUST * 0.1;
		DT_MAX = midval(DT_LIMIT, DTMIN, TGO / NSEG);
		ASC_PREC_PRED(R_INIT, V_INIT, TGD, TP, 0, 0, DT_MAX, R_FINAL, V_FINAL);
		VGRAV = V_FINAL - V_INIT;
		RGRAV = R_FINAL - R_INIT - V_INIT * TGO;
		RP = RGD + VGD * TGO + RGRAV + RTHRUST;
		VP = VGD + VGRAV + VTHRUST;
	}

	void AscentGuidance::ThrustTimeIntegralsLogic(int I)
	{
		double TF, IF_MAG_F;

		TF = TI + TB[I - 1];
		IF_MAG_F = sqrt(1.0 + LAMDMAG * LAMDMAG * TF * TF);
		RTHRUST = RTHRUST + VTHRUST * TB[I - 1];
		if (LAMDMAG * TB[I - 1] < 0.09)
		{
			double TFMEANSQ = abs(TF * TF + TI * TF + TI * TI) / 3.0;
			double SMA_GAIN = 1.0 / sqrt(1.0 + TFMEANSQ * LAMDMAG * LAMDMAG);
			RTHRUST = RTHRUST + (LAM * SA[I - 1] + LAMD * (QA[I - 1] - SA[I - 1] * JOL)) * SMA_GAIN;
			VTHRUST = VTHRUST + (LAM * LA[I - 1] + LAMD * (LA[I - 1] * TGOA[I - 1] - SA[I - 1] - LA[I - 1] * JOL)) * SMA_GAIN;
		}
		else
		{
			double A, B, C, Y[5], M[3];

			if (I == N)
			{
				A = AL;
				B = C = 0.0;
			}
			else
			{
				C = 60.0 * (0.5 * pow(TB[I - 1], 2) * LA[I - 1] + 3.0 * TI * SA[I - 1] - 3.0 * (QA[I - 1] - SA[I - 1] * JOL)) / pow(TB[I - 1], 5);
				B = 12.0 * (0.5 * TB[I - 1] * LA[I - 1] - SA[I - 1]) / pow(TB[I - 1], 3) - C * (TF + TI);
				A = LA[I - 1] / TB[I - 1] - 0.5 * B * (TF + TI) - C * (pow(TB[I - 1], 2) / 3.0 + TI * TF);
			}
			Y[0] = log(abs((TF * LAMDMAG + IF_MAG_F) / (TI * LAMDMAG + IF_MAG_I))) / LAMDMAG;
			Y[1] = (TF * TF - TI * TI) / (IF_MAG_I + IF_MAG_F);
			for (int X = 1; X <= 3; X++)
			{
				Y[X + 1] = (IF_MAG_F * pow(TF, X) - IF_MAG_I * pow(TI, X) - (double)X * Y[X - 1]) / (LAMDMAG * LAMDMAG * (double)(X + 1));
				M[X - 1] = A * Y[X - 1] + B * Y[X] + C * Y[X + 1];
			}
			RTHRUST = RTHRUST + LAM * (TF * M[0] - M[1]) + LAMD * (TF * M[1] - M[2]);
			VTHRUST = VTHRUST + LAM * M[0] + LAMD * M[1];
		}
		TI = TF;
		IF_MAG_I = IF_MAG_F;
	}

	void AscentGuidance::CutoffPositionConstraintReleaseSubtask()
	{
		// For reasons of flight control stability near cutoff, there is a guidance requirement to release position constraints at a fixed input TGO(DTRD).
		// Therefore, if either altitude (SALT = ON) or the orbital plane (SPLANE = ON) is being constrained and
		// if TGO is less than DTRD and VGO is converged (SCONV = ON), the position constraints are released.
		// If VGO is unconverged when TGO first becomes less than DTRD and remains unconverged on subsequent cycles, the position constraints will be released
		// when TGO becomes less than DTRD–6 and the PEG initialization discrete (SINIT) is OFF.

		if ((SALT || SPLANE) && ((SCONV && TGO < DTRD) || (TGO < DTRD - 6.0 && SINIT == false)))
		{
			OMEGA = crossp(LAM, LAMD);
			SALT = false;
			SPLANE = false;
		}
	}

	void AscentGuidance::CENTRAL(VECTOR3 R, VECTOR3& ACCEL, double& R_INV) const
	{
		// Calculate spherical acceleration term

		R_INV = 1.0 / length(R);
		ACCEL = -R * EARTH_MU * pow(R_INV, 3);
	}

	void AscentGuidance::ASC_PREC_PRED(VECTOR3 R_INIT, VECTOR3 V_INIT, double T_INIT, double T_FINAL, int GMD_PRED, int GMO_PRED, double DT_MAX, VECTOR3& R_FINAL, VECTOR3& V_FINAL) const
	{
		// Predict final state vector from initial state vector
		// TBD: Only spherical gravity model for now

		VECTOR3 G_PREVIOUS, G_FINAL;
		double STEP_SIZE, T, R_INV;
		int NUMBER_STEPS;

		R_FINAL = R_INIT;
		V_FINAL = V_INIT;

		NUMBER_STEPS = (int)max(round(abs(T_FINAL - T_INIT) / DT_MAX), 1.0);
		STEP_SIZE = (T_FINAL - T_INIT) / (double)(NUMBER_STEPS);
		T = T_INIT;

		if (GMD_PRED == 0)
		{
			CENTRAL(R_FINAL, G_PREVIOUS, R_INV);
		}
		else
		{
			//TBD
		}
		for (int I = 0; I < NUMBER_STEPS; I++)
		{
			T = T + STEP_SIZE;
			R_FINAL = R_FINAL + (V_FINAL + G_PREVIOUS * 0.5 * STEP_SIZE) * STEP_SIZE;
			if (GMD_PRED == 0)
			{
				CENTRAL(R_FINAL, G_FINAL, R_INV);
			}
			else
			{
				//TBD
			}
			V_FINAL = V_FINAL + (G_PREVIOUS + G_FINAL) * 0.5 * STEP_SIZE;
			R_FINAL = R_FINAL + (G_FINAL - G_PREVIOUS) / 6.0 * STEP_SIZE * STEP_SIZE;
			G_PREVIOUS = G_FINAL;
		}
	}


AscentDAP::AscentDAP(SimpleGPCSystem* _gpc)
: SimpleGPCSoftware(_gpc, "AscentDAP"),
  hEarth(NULL),
  stage1GuidanceVelTable(DEFAULT_STAGE1_GUIDANCE_TABLE_VEL, DEFAULT_STAGE1_GUIDANCE_TABLE_VEL+STAGE1_GUIDANCE_TABLE_SIZE),
  stage1GuidancePitchTable(DEFAULT_STAGE1_GUIDANCE_TABLE_PITCH, DEFAULT_STAGE1_GUIDANCE_TABLE_PITCH+STAGE1_GUIDANCE_TABLE_SIZE),
  tLastMajorCycle(-1.0)
{
	// set PID controller gains
	for(int i=0;i<2;i++) {
		SRBGimbal[i][PITCH].SetGains(-0.5, -0.05, 0.0);
		SRBGimbal[i][YAW].SetGains(-0.5, -0.05, 0.0);
	}
	SRBGimbal[0][ROLL].SetGains(0.75, 0.05, 0.0);
	SRBGimbal[1][ROLL].SetGains(-0.75, -0.05, 0.0);

	WriteCOMPOOL_IS( SCP_K_CMD, 100 );

	enaSERC = false;

	glimiting = false;
	dt_thrt_glim = 0;

	MEFail[0] = false;
	MEFail[1] = false;
	MEFail[2] = false;
	NSSME = 3;

	finecount = false;

	SSMETailoffDV[0] = SSME_TAILOFF_DV_91_2EO;
	SSMETailoffDV[1] = SSME_TAILOFF_DV_91_1EO;
	SSMETailoffDV[2] = SSME_TAILOFF_DV_67;

	J = 1;

	AGT_done = false;

	bNullSRBNozzles = false;

	EOVI[0] = 0;
	EOVI[1] = 0;

	AutoFCS = true;

	VS = VSP = DVS = _V(0, 0, 0);

	XTRK = 0.0;
	MEDS_D_INCL = 0.0;

	// I-LOADs init
	KMAX_NOM = 104;
	KMAX_ABORT = 104;
	KMAX_SECONDARY = 109;
	K_CO_MAX = 91;
	QPOLY[0] = 60.0;
	QPOLY[1] = 383.0;
	QPOLY[2] = 617.0;
	QPOLY[3] = 1397.0;
	THROT[0] = 104;
	THROT[1] = 104;
	THROT[2] = 72;
	THROT[3] = 104;
	TREF_ADJUST = 17.87;
	VREF_ADJUST = 368.0;
	OMSASS = 1;
	NOMTM = 59.0;
	MASS_LOW_LEVEL = 11500.0;
	ALIM_1 = 96.200405;
	ALIM_2 = 96.522146;
	PHI_CMD = 3.141596;
	PHI_2STG = 0.0;
	V_RHO_PHI = 12200.0;
}

AscentDAP::~AscentDAP()
{
}

void AscentDAP::Realize()
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle("LOMS", 4);
	OMSCommand[LEFT].Connect(pBundle, 2);
	pBundle = BundleManager()->CreateBundle("ROMS", 4);
	OMSCommand[RIGHT].Connect(pBundle, 2);

	pBundle = BundleManager()->CreateBundle( "THRUSTER_CMD", 16 );
	SERC.Connect( pBundle, 6 );

	pSSME_SOP = dynamic_cast<SSME_SOP*> (FindSoftware( "SSME_SOP" ));
	assert( (pSSME_SOP != NULL) && "AscentDAP::Realize.pSSME_SOP" );
	pSSME_Operations = dynamic_cast<SSME_Operations*> (FindSoftware( "SSME_Operations" ));
	assert( (pSSME_Operations != NULL) && "AscentDAP::Realize.pSSME_Operations" );
	pMPS_ATVC_CMD_SOP = dynamic_cast<MPS_ATVC_CMD_SOP*> (FindSoftware( "MPS_ATVC_CMD_SOP" ));
	assert( (pMPS_ATVC_CMD_SOP != NULL) && "AscentDAP::Realize.pMPS_ATVC_CMD_SOP" );
	pSRBSepSequence = dynamic_cast<SRBSepSequence*> (FindSoftware( "SRBSepSequence" ));
	assert( (pSRBSepSequence != NULL) && "AscentDAP::Realize.pSRBSepSequence" );
	pRHC_SOP = dynamic_cast<RHC_SOP*> (FindSoftware( "RHC_SOP" ));
	assert( (pRHC_SOP != NULL) && "AscentDAP::Realize.pRHC_SOP" );
	pSBTC_SOP = dynamic_cast<SBTC_SOP*> (FindSoftware( "SBTC_SOP" ));
	assert( (pSBTC_SOP != NULL) && "AscentDAP::Realize.pSBTC_SOP" );
	pGNCUtilities = dynamic_cast<GNCUtilities*>(FindSoftware("GNCUtilities"));
	assert((pGNCUtilities != NULL) && "OMSBurnSoftware::Realize.pGNCUtilities");
	pStateVectorSoftware = dynamic_cast<StateVectorSoftware*>(FindSoftware("StateVectorSoftware"));
	assert((pStateVectorSoftware != NULL) && "OMSBurnSoftware::Realize.pStateVectorSoftware");
}

void AscentDAP::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	GetValILOAD( "KMAX_NOM", ILOADs, KMAX_NOM );
	GetValILOAD( "KMAX_ABORT", ILOADs, KMAX_ABORT );
	GetValILOAD( "KMAX_SECONDARY", ILOADs, KMAX_SECONDARY );
	GetValILOAD( "K_CO_MAX", ILOADs, K_CO_MAX );
	GetValILOAD( "QPOLY", ILOADs, 4, QPOLY );
	GetValILOAD( "THROT", ILOADs, 4, THROT );
	GetValILOAD( "VREF_ADJUST", ILOADs, VREF_ADJUST );
	GetValILOAD( "TREF_ADJUST", ILOADs, TREF_ADJUST );
	GetValILOAD( "OMSASS", ILOADs, OMSASS );
	GetValILOAD( "NOMTM", ILOADs, NOMTM );
	GetValILOAD( "MASS_LOW_LEVEL", ILOADs, MASS_LOW_LEVEL );
	GetValILOAD( "ALIM_1", ILOADs, ALIM_1 );
	GetValILOAD( "ALIM_2", ILOADs, ALIM_2 );
	GetValILOAD( "PHI_CMD", ILOADs, PHI_CMD );
	GetValILOAD( "PHI_2STG", ILOADs, PHI_2STG );
	GetValILOAD( "V_RHO_PHI", ILOADs, V_RHO_PHI );
	return;
}

void AscentDAP::OnPreStep( double simt, double simdt, double mjd )
{
	if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0)
	{
		// check if AUTO or CSS
		if (AutoFCS == true)
		{
			unsigned short CDRPitchCSS = ReadCOMPOOL_IS( SCP_FCS_LH_PITCH_CSS_MODE );
			unsigned short CDRRollYawCSS = ReadCOMPOOL_IS( SCP_FCS_LH_RY_CSS_MODE );
			unsigned short PLTPitchCSS = ReadCOMPOOL_IS( SCP_FCS_RH_PITCH_CSS_MODE );
			unsigned short PLTRollYawCSS = ReadCOMPOOL_IS( SCP_FCS_RH_RY_CSS_MODE );
			if ((CDRPitchCSS == 1) || (CDRRollYawCSS == 1) || (PLTPitchCSS == 1) || (PLTRollYawCSS == 1))
			{
				// to CSS
				AutoFCS = false;
			}
		}
		else
		{
			unsigned short CDRPitchAuto = ReadCOMPOOL_IS( SCP_FCS_LH_PITCH_AUTO_MODE );
			unsigned short CDRRollYawAuto = ReadCOMPOOL_IS( SCP_FCS_LH_RY_AUTO_MODE );
			unsigned short PLTPitchAuto = ReadCOMPOOL_IS( SCP_FCS_RH_PITCH_AUTO_MODE );
			unsigned short PLTRollYawAuto = ReadCOMPOOL_IS( SCP_FCS_RH_RY_AUTO_MODE );
			if ((CDRPitchAuto == 1) || (CDRRollYawAuto == 1) || (PLTPitchAuto == 1) || (PLTRollYawAuto == 1))
			{
				// to AUTO
				AutoFCS = true;
			}
		}
	}

	VECTOR3 degReqdRates;
	VECTOR3 AngularVelocity;
	STS()->GetAngularVel( AngularVelocity );
	AngularVelocity *= DEG;

	// handle KMAX
	unsigned short kmaxsel = ReadCOMPOOL_IS( SCP_KMAX_SEL );
	if (kmaxsel == 1) WriteCOMPOOL_IS( SCP_KMAX, KMAX_SECONDARY );
	else if (kmaxsel == 2) WriteCOMPOOL_IS( SCP_KMAX, KMAX_ABORT );
	else if (kmaxsel == 0) WriteCOMPOOL_IS( SCP_KMAX, KMAX_NOM );

	switch (GetMajorMode())
	{
		case 102:
			FirstStageGuidance( simdt );
			if (AutoFCS == true) degReqdRates = degReqdRatesGuidance;// AUTO
			else
			{
				// CSS
				// TODO when RHCs in detent, hold attitude when rates fall below 3º/s
				degReqdRates = _V( range( -12, pRHC_SOP->GetPitchCommand() * 0.5, 12 ), -range( -6, pRHC_SOP->GetYawCommand() * 0.5, 6 ), range( -12, pRHC_SOP->GetRollCommand() * 0.5, 12 ) );
			}

			if (bNullSRBNozzles == true)
			{
				STS()->SetSRBGimbalAngles( static_cast<SIDE> (0), 0, 0 );
				STS()->SetSRBGimbalAngles( static_cast<SIDE> (1), 0, 0 );
			}
			else GimbalSRBs( simdt, degReqdRates, AngularVelocity );
			GimbalSSMEs( simdt, degReqdRates, AngularVelocity );
			break;
		case 103:
			SecondStageGuidance( simdt );
			if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0)
			{
				if (AutoFCS == true) degReqdRates = degReqdRatesGuidance;// AUTO
				else
				{
					// CSS
					// TODO when RHCs in detent, hold attitude when rates fall below 3º/s
					degReqdRates = _V( range( -12, pRHC_SOP->GetPitchCommand() * 0.5, 12 ), -range( -6, pRHC_SOP->GetYawCommand() * 0.5, 6 ), range( -12, pRHC_SOP->GetRollCommand() * 0.5, 12 ) );
				}

				// OMS Assist
				if (OMSASS == 1)
				{
					if ((STS()->GetMET() >= (tSRBSep + 10)) && (STS()->GetMET() < (tSRBSep + 10 + NOMTM)))
					{
						OMSCommand[LEFT].SetLine();
						OMSCommand[RIGHT].SetLine();
					}
					else
					{
						OMSCommand[LEFT].ResetLine();
						OMSCommand[RIGHT].ResetLine();
					}
				}
			}
			else
			{
				degReqdRates = _V( 0.0, 0.0, 0.0 );// hold attitude post-MECO

				// stop any existing OMS dump
				OMSCommand[LEFT].ResetLine();
				OMSCommand[RIGHT].ResetLine();

				if (pSSME_Operations->GetZeroThrustFlag() == true)
				{
					// stop any SERC firing, TransDAP takes over now
					SERC.ResetLine();
				}
			}

			GimbalSSMEs( simdt, degReqdRates, AngularVelocity );
			break;
	}


	// DAP lights
	if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0)
	{
		if (AutoFCS == true)
		{
			LAUTO_PLAMP = true;
			LCSS_PLAMP = false;
			LAUTO_RYLAMP = true;
			LCSS_RYLAMP = false;
			RAUTO_PLAMP = true;
			RCSS_PLAMP = false;
			RAUTO_RYLAMP = true;
			RCSS_RYLAMP = false;
		}
		else
		{
			LAUTO_PLAMP = false;
			LCSS_PLAMP = true;
			LAUTO_RYLAMP = false;
			LCSS_RYLAMP = true;
			RAUTO_PLAMP = false;
			RCSS_PLAMP = true;
			RAUTO_RYLAMP = false;
			RCSS_RYLAMP = true;
		}
	}
	else
	{
		LAUTO_PLAMP = false;
		LCSS_PLAMP = false;
		LAUTO_RYLAMP = false;
		LCSS_RYLAMP = false;
		RAUTO_PLAMP = false;
		RCSS_PLAMP = false;
		RAUTO_RYLAMP = false;
		RCSS_RYLAMP = false;
	}

	if (ReadCOMPOOL_IS( SCP_MPS_LO2_DUMP_STOP ) == 0)// HACK this flag is only used here during TAL, NOM uses SSME_STOW_COMPLETE flag
	{
		RAUTO_BFLAMP = true;
		LAUTO_BFLAMP = true;
	}
	else
	{
		RAUTO_BFLAMP = false;
		LAUTO_BFLAMP = false;
	}
	RMNL_BFLAMP = false;
	LMNL_BFLAMP = false;

	// output to MDMs
	if (LAUTO_PLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0040 );
	if (LCSS_PLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0040 );
	if (LAUTO_RYLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0080 );
	if (LCSS_RYLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0080 );
	if (LAUTO_BFLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0010 );
	if (LMNL_BFLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0010 );
	if (RAUTO_PLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0040 );
	if (RCSS_PLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0040 );
	if (RAUTO_RYLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0080 );
	if (RCSS_RYLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0080 );
	if (RAUTO_BFLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0010 );
	if (RMNL_BFLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0010 );
	return;
}

bool AscentDAP::OnMajorModeChange(unsigned int newMajorMode)
{
	if ((newMajorMode == 101) || (newMajorMode == 102) || (newMajorMode == 103) || (newMajorMode == 104))
	{
		if (newMajorMode == 102)
		{
			WriteCOMPOOL_IS( SCP_KMAX, KMAX_NOM );
			InitializeAutopilot();
		}
		else if (newMajorMode == 103) tSRBSep = STS()->GetMET();
		return true;
	}
	return false;
}

bool AscentDAP::OnParseLine(const char* keyword, const char* value)
{
	if (!_strnicmp( keyword, "FCS", 3 ))
	{
		if (!_strnicmp( value, "CSS", 3 )) AutoFCS = false;
		else AutoFCS = true;
		return true;
	}
	return false;
}

void AscentDAP::OnSaveState(FILEHANDLE scn) const
{
	oapiWriteScenario_string( scn, "FCS", AutoFCS ? "AUTO" : "CSS" );
	return;
}

void AscentDAP::FirstStageGuidance( double dt )
{
	STS()->CalcSSMEThrustAngles(0, ThrAngleP, ThrAngleY);
	FirstStageThrottle( dt );
	FirstStageRateCommand();
	AscentUPP();
	return;
}

void AscentDAP::SecondStageGuidance( double dt )
{
	Navigate(dt);// update speed post MECO

	if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0)
	{
		STS()->CalcSSMEThrustAngles(0, ThrAngleP, ThrAngleY);
		//Navigate();
		if(STS()->GetMET() >= (tLastMajorCycle + ASCENT_MAJOR_CYCLE)) {
			MajorCycle();
			tLastMajorCycle = STS()->GetMET();
		}
		SecondStageRateCommand();
		SecondStageThrottle( dt );
		AscentUPP();
	}
	return;
}

void AscentDAP::InitializeAutopilot()
{
	VECTOR3 IYD;
	double TgtAlt, TgtInc, TgtFPA, TgtSpd, EarthRadius;
	bool EF_PLANE_SW;

	mission::Mission* pMission = STS()->GetMissionData();
	TgtInc=pMission->GetMECOInc();
	TgtFPA=pMission->GetMECOFPA();
	TgtAlt=pMission->GetMECOAlt();
	TgtSpd=pMission->GetMECOVel() - (SSMETailoffDV[2] / MPS2FPS);
	IYD = pMission->GetIYD();
	EF_PLANE_SW = pMission->GetEFPLANESW();

	// FIRST STAGE GUIDANCE

	hEarth = STS()->GetSurfaceRef();
	//calculate heading
	double latitude, longitude;
	STS()->GetEquPos(longitude, latitude, EarthRadius);
	if(abs(cos(TgtInc))>abs(cos(latitude))) {
		radTargetHeading=PI05;
		//TgtInc = latitude;
	}
	else {
		// there are two possible launch headings: going north and going south
		// for TgtInc < 65 deg (KSC launches) we want northerly heading; max. inclination of KSC launch was 62 degrees (with dog-leg)
		// for TgtInc > 65 deg (VAFB) we want southerly heading
		double InHeading = asin(cos(TgtInc)/cos(latitude));
		double xVel, yVel;
		xVel = TgtSpd*cos(TgtFPA)*sin(InHeading)-464.581*cos(latitude);
		yVel = TgtSpd*cos(TgtFPA)*cos(InHeading);
		radTargetHeading=atan2(xVel, yVel); // northerly heading
		if(TgtInc > 65.0*RAD) radTargetHeading = PI - radTargetHeading; // if heading is negative, this is retrograde inclination; use southerly heading
	}

	// SECOND STAGE GUIDANCE

	VECTOR3 IY_M50;
	double PRED_GMT_LO;

	// Get GMT of liftoff. TBD: Is PRED_GMT_LO set in RSLS?
	PRED_GMT_LO = ReadClock();

	// Is an IY vector available from the mission data?
	if (length(IYD) != 0.0)
	{
		// Yes
		if (EF_PLANE_SW)
		{
			// Convert to M50 coordinates
			IY_M50 = mul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(PRED_GMT_LO), IYD);
		}
		else
		{
			// Use vector as-is
			// TBD: NODE_SLOPE etc.
			IY_M50 = IYD;
		}
	}
	else
	{
		// No
		// Calculate IY vector in Earth-fixed coordinates
		VECTOR3 IY_EF = guid.CalculateEFIYVector(TgtInc, latitude, longitude, TgtInc < 65.0 * RAD, 300.0);
		// Convert to M50 coordinates
		IY_M50 = mul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(PRED_GMT_LO), IY_EF);
	}

	// Calculate target radius
	EarthRadius = oapiGetSize(hEarth);
	double TgtRad = TgtAlt + EarthRadius;

	// Initialize ascent guidance
	guid.Init(PRED_GMT_LO, TgtRad, TgtSpd, TgtFPA, IY_M50);

	// sprintf_s(oapiDebugString(), 128, "PRED_GMT_LO %lf TgtInc %lf EF_PLANE_SW %d IYD %lf %lf %lf IY_M50 %lf %lf %lf", PRED_GMT_LO, TgtInc*DEG, EF_PLANE_SW, IYD.x, IYD.y, IYD.z, IY_M50.x, IY_M50.y, IY_M50.z);
}

double AscentDAP::GetCurrentHeading() const
{
	double Heading;
	if(STS()->GetPitch()*DEG>=88.0)
	{
		VECTOR3 wingBody=_V(1,0,0);
		VECTOR3 wingHorizon;
		STS()->HorizonRot(wingBody,wingHorizon);
		Heading=atan2(wingHorizon.x,wingHorizon.z)+PI05;
		if(Heading >= PI2)
			Heading -= PI2;
	}
	else
	{
		oapiGetHeading(STS()->GetHandle(), &Heading);
	}
	return Heading;
}

void AscentDAP::GimbalSRBs( double simdt, const VECTOR3& degReqdRates, const VECTOR3& AngularVelocity )
{
	VECTOR3 degRateError = degReqdRates - AngularVelocity;

	for(int i=0;i<2;i++) {
		double pitchGimbal = SRBGimbal[i][PITCH].Step(degRateError.data[PITCH], simdt);
		double yawGimbal = SRBGimbal[i][YAW].Step(degRateError.data[YAW], simdt);
		double rollGimbal = SRBGimbal[i][ROLL].Step(degRateError.data[ROLL], simdt);
		STS()->SetSRBGimbalAngles(static_cast<SIDE>(i), pitchGimbal+rollGimbal, yawGimbal);
		//pMPS_ATVC_CMD_SOP->SetSRBActPos( i, pitchGimbal+rollGimbal, yawGimbal );
	}
}

void AscentDAP::GimbalSSMEs( double simdt, const VECTOR3& degReqdRates, const VECTOR3& AngularVelocity )
{
	VECTOR3 degRateError = degReqdRates - AngularVelocity;

	// see Section 5.4.3.4 of Ascent Guidance & Flight Control Workbook for more information on how roll is added to SSME gimbal angles
	// TODO: handle engine failures
	double pitchGimbal[3], yawGimbal[3];

	switch ((ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) * 4) + (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) * 2) + ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ))
	{
		case 0:// nom
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = -range(-8.0, degRateError.data[YAW], 8.0) - range(-8.0, 0.75*degRateError.data[ROLL], 8.0);
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0) + range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[1] = -range(-8.0, degRateError.data[YAW], 8.0);
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0) - range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[2] = -range(-8.0, degRateError.data[YAW], 8.0);

			// In this case ME-2 and 3 not pointing thru c.g. in yaw, instead pointing strait forward.
			// Need hard data to be sure, but looks like it's this way in reality.
			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;
			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += ThrAngleY + 3.5;
			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += ThrAngleY - 3.5;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 0, -pitchGimbal[0], -yawGimbal[0] );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, -pitchGimbal[1], -yawGimbal[1] );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, -pitchGimbal[2], -yawGimbal[2] );
			break;
		case 1:// C out
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0) + range(-7.0, 1.5*degRateError.data[ROLL], 7.0);
			yawGimbal[1] = -range(-8.0, degRateError.data[YAW], 8.0);
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0) - range(-7.0, 1.5*degRateError.data[ROLL], 7.0);
			yawGimbal[2] = -range(-8.0, degRateError.data[YAW], 8.0);

			STS()->CalcSSMEThrustAngles( 2, ThrAngleP, ThrAngleY );
			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += 3.5;

			STS()->CalcSSMEThrustAngles( 3, ThrAngleP, ThrAngleY );
			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] -= 3.5;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, -pitchGimbal[1], -yawGimbal[1] );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, -pitchGimbal[2], -yawGimbal[2] );
			break;
		case 2:// L out
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = -range(-8.0, degRateError.data[YAW], 8.0) - range(-8.0, 0.75*degRateError.data[ROLL], 8.0);
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0) - range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[2] = -range(-8.0, degRateError.data[YAW], 8.0);

			STS()->CalcSSMEThrustAngles( 1, ThrAngleP, ThrAngleY );
			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;

			STS()->CalcSSMEThrustAngles( 3, ThrAngleP, ThrAngleY );
			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += ThrAngleY - 3.5;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 0, -pitchGimbal[0], -yawGimbal[0] );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, -pitchGimbal[2], -yawGimbal[2] );
			break;
		case 3:// C, L out
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[2] = -range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += ThrAngleY - 3.5;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 2, -pitchGimbal[2], -yawGimbal[2] );
			break;
		case 4:// R out
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = -range(-8.0, degRateError.data[YAW], 8.0) - range(-8.0, 0.75*degRateError.data[ROLL], 8.0);
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0) + range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[1] = -range(-8.0, degRateError.data[YAW], 8.0);

			STS()->CalcSSMEThrustAngles( 1, ThrAngleP, ThrAngleY );
			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;

			STS()->CalcSSMEThrustAngles( 2, ThrAngleP, ThrAngleY );
			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += ThrAngleY + 3.5;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 0, -pitchGimbal[0], -yawGimbal[0] );
			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, -pitchGimbal[1], -yawGimbal[1] );
			break;
		case 5:// C, R out
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[1] = -range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += ThrAngleY + 3.5;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 1, -pitchGimbal[1], -yawGimbal[1] );
			break;
		case 6:// L, R out
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = -range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;

			pMPS_ATVC_CMD_SOP->SetSSMEActPos( 0, -pitchGimbal[0], -yawGimbal[0] );
			break;
	}

	// SERC
	if (enaSERC == true)
	{
		if (abs( degRateError.data[ROLL] ) < 0.1) SERC.ResetLine();
		else SERC.SetLine( static_cast<float>(-range( -1, 0.5 * degRateError.data[ROLL], 1 )) );
	}
}
void AscentDAP::FirstStageRateCommand()
{
	if(STS()->GetAirspeed()<stage1GuidanceVelTable[1]) {
		degReqdRatesGuidance.data[PITCH] = 0.0;
		degReqdRatesGuidance.data[YAW] = 0.0;
		degReqdRatesGuidance.data[ROLL] = 0.0;
	}
	else {
		double degTargetPitch=listerp(stage1GuidanceVelTable, stage1GuidancePitchTable, STS()->GetAirspeed());
		double radHeading = GetCurrentHeading();

		double degPitch = STS()->GetPitch()*DEG;
		double degBank = STS()->GetBank()*DEG;
		if(degPitch>=88.5) { // roll to correct heading
			degReqdRatesGuidance.data[PITCH] = range(-10.0, 0.48*(degPitch-degTargetPitch), 10.0);
			degReqdRatesGuidance.data[YAW]=0.0;
			if((radHeading-radTargetHeading)>RAD) degReqdRatesGuidance.data[ROLL]=8.0;
			else if((radHeading-radTargetHeading)<-RAD) degReqdRatesGuidance.data[ROLL]=-8.0;
			else degReqdRatesGuidance.data[ROLL]=0.0;
			degReqdRatesGuidance=RotateVectorZ(degReqdRatesGuidance, (radTargetHeading-radHeading)*DEG);
		}
		else {
			degReqdRatesGuidance.data[PITCH] = range(-2.5, 0.48*(degTargetPitch-degPitch), 2.5);

			if(degPitch>60.0) {
				degReqdRatesGuidance.data[YAW] = range(-8.0, 0.25*DEG*(radHeading-radTargetHeading), 8.0);
			}
			else {
				degReqdRatesGuidance.data[YAW] = 0.0;
			}
			if(degBank>0.0) degReqdRatesGuidance.data[ROLL]=0.5*(degBank-180.0);
			else degReqdRatesGuidance.data[ROLL]=0.5*(degBank+180.0);
			degReqdRatesGuidance=RotateVectorZ(degReqdRatesGuidance, -degBank);
			degReqdRatesGuidance.data[ROLL] = range(-12.0, degReqdRatesGuidance.data[ROLL], 12.0);
		}
	}
}

void AscentDAP::SecondStageRateCommand()
{
	if(STS()->GetMET()<=(tSRBSep+4.0)) {
		degReqdRatesGuidance.data[PITCH]=0.0;
		degReqdRatesGuidance.data[YAW]=0.0;
		degReqdRatesGuidance.data[ROLL]=0.0;
	}
	else {
		if(timeRemaining>PEG_STOP_TIME)
		{
			double radHeading = GetCurrentHeading();
			double degBank = STS()->GetBank()*DEG;

			degReqdRatesGuidance.data[PITCH] = CmdPDot;
			degReqdRatesGuidance.data[YAW] = range(-2.5, 0.5*(DEG*(radHeading-radTargetHeading) - (sign( cos( degBank ) ) * ThrAngleY)), 2.5);
			// applied the "- (sign( cos( degBank ) ) * ThrAngleY)" factor to correct for "sideways" thrust (ME-2 or 3 out/low thrust)

			// roll target
			VECTOR3 ECEF_vel = GetVelocity_ECEF( STS(), hEarth );
			double V_RHO_MAG = length( ECEF_vel ) * MPS2FPS;

			if (V_RHO_MAG > V_RHO_PHI) PHI_CMD = PHI_2STG;

			degReqdRatesGuidance.data[ROLL] = 2.5 * (degBank - ((PHI_CMD * DEG) * sign( degBank )));
			degReqdRatesGuidance.data[ROLL] = range( -5.0, 0.5 * degReqdRatesGuidance.data[ROLL], 5.0 );


			degReqdRatesGuidance=RotateVectorZ(degReqdRatesGuidance, -degBank);
		}
		else {
			degReqdRatesGuidance.data[PITCH] = 0.0;
			degReqdRatesGuidance.data[YAW] = 0.0;
			degReqdRatesGuidance.data[ROLL] = 0.0;
		}
	}
}

void AscentDAP::FirstStageThrottle( double dt )
{
	// detect EO
	bool fail = 0;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
				fail = (ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1);
				break;
			case 1:
				fail = (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1);
				break;
			case 2:
				fail = (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1);
				break;
		}

		if (MEFail[i] != fail)
		{
			MEFail[i] = true;
			NSSME--;
			// record EO VI
			VECTOR3 v3vi;
			STS()->GetRelativeVel( STS()->GetSurfaceRef(), v3vi );
			double vi = length( v3vi ) * MPS2FPS;
			if (NSSME == 2) EOVI[0] = vi;
			else if (NSSME == 1) EOVI[1] = vi;

			AGT_done = true;// don't do AGT
			J = 5;// bypass throttle table
			WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_KMAX ) );// throttle to mission power level

			// update MECO targets
			if (NSSME > 0) guid.UpdateVDMAG(STS()->GetMissionData()->GetMECOVel() - (SSMETailoffDV[NSSME - 1] / MPS2FPS));
		}
	}

	// SERC
	if ((NSSME == 1) && (pSRBSepSequence->GetLHRHSRBPC50PSIFlag() == true))// enable SERC in MM102 only at SRB tailoff
	{
		enaSERC = true;
	}

	// calc and set SSME throttle
	AdaptiveGuidanceThrottling();

	if (J < 5)
	{
		if ((STS()->GetAirspeed() * MPS2FPS) >= QPOLY[J - 1])
		{
			WriteCOMPOOL_IS( SCP_K_CMD, THROT[J - 1] );
			J = J + 1;
		}
	}

	if (pSBTC_SOP->GetManThrottle() == false) pSSME_SOP->SetThrottlePercent( ReadCOMPOOL_IS( SCP_K_CMD ) );
	return;
}

void AscentDAP::SecondStageThrottle( double dt )
{
	// detect EO
	bool fail = 0;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
				fail = (ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1);
				break;
			case 1:
				fail = (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1);
				break;
			case 2:
				fail = (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1);
				break;
		}

		if (MEFail[i] != fail)
		{
			MEFail[i] = true;
			NSSME--;
			// record EO VI
			VECTOR3 v3vi;
			STS()->GetRelativeVel( STS()->GetSurfaceRef(), v3vi );
			double vi = length( v3vi ) * MPS2FPS;
			if (NSSME == 2) EOVI[0] = vi;
			else if (NSSME == 1) EOVI[1] = vi;

			glimiting = false;// reset g-limiting
			dt_thrt_glim = -2;// HACK delay g-limiting action by 2sec (if it re-triggers) to account for failed engine tailoff thrust
			WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_KMAX ) );// throttle to mission power level

			// update MECO targets
			if (NSSME > 0) guid.UpdateVDMAG(STS()->GetMissionData()->GetMECOVel() - (SSMETailoffDV[NSSME - 1] / MPS2FPS));
		}
	}

	// SERC
	if (NSSME == 1)// enable SERC automatically in MM103
	{// TODO enable SERC when "sensed acceleration falls below a predefined limit"
		enaSERC = true;
	}

	// low-level sensor arm
	if ((STS()->GetMass() * KG2LBM * LBS2SL) < MASS_LOW_LEVEL) pSSME_Operations->SetLowLevelSensorArmFlag();

	// check for MECO
	if ((inertialVelocity >= guid.GetVDMAG()) && (pSBTC_SOP->GetManThrottle() == false))
	{
		//reached target speed
		WriteCOMPOOL_IS( SCP_MECO_CMD, 1 );

		oapiWriteLogV( "MECO @ MET %.2f", STS()->GetMET() );
		return;
	}

	// calc and set SSME throttle
	// g limiting
	if ((thrustAcceleration * MPS2FPS) > ALIM_2) glimiting = true;
	if ((glimiting == true) && ((thrustAcceleration * MPS2FPS) > ALIM_1))
	{
		unsigned short KMIN = ReadCOMPOOL_IS( SCP_KMIN );
		if (ReadCOMPOOL_IS( SCP_K_CMD ) != KMIN)// if at MPL can't do more
		{
			if (dt_thrt_glim >= 0.1)// wait while throttling (10%/sec throttle change = 0.1s delay)
			{
				WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_K_CMD ) - 1 );// throttle back 1%
				if (ReadCOMPOOL_IS( SCP_K_CMD ) < KMIN) WriteCOMPOOL_IS( SCP_K_CMD, KMIN );// don't go below MPL
				dt_thrt_glim = 0;// reset
			}
			else dt_thrt_glim += dt;
		}
	}

	// fine count
	// HACK only throttle back, no real count for now
	if ((timeRemaining <= 6) && (finecount == false))
	{
		if (NSSME == 3 ) WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_KMIN ) );
		else WriteCOMPOOL_IS( SCP_K_CMD,  K_CO_MAX );
		finecount = true;
		oapiWriteLogV( "Fine Count (throttle to %d%%) @ MET %.2f", ReadCOMPOOL_IS( SCP_K_CMD ), STS()->GetMET() );
	}

	if (pSBTC_SOP->GetManThrottle() == false) pSSME_SOP->SetThrottlePercent( ReadCOMPOOL_IS( SCP_K_CMD ) );
	//else pSBTC_SOP->GetManThrottleCommand();
	return;
}

void AscentDAP::MajorCycle()
{
	VECTOR3 pos, vel, U_STEER;

	PFG_INP_TSK();

	// Get state vector in M50 coordinates
	STS()->GetRelativePos(STS()->GetSurfaceRef(), pos);
	STS()->GetRelativeVel(STS()->GetSurfaceRef(), vel);

	pos = ConvertBetweenLHAndRHFrames(pos);
	vel = ConvertBetweenLHAndRHFrames(vel);

	pos = mul(M_J2000_to_M50, pos);
	vel = mul(M_J2000_to_M50, vel);

	// Call guidance function
	guid.Cycle(pos, vel, ReadClock(), ReadCOMPOOL_IS(SCP_K_CMD), NSSME, 0, STS()->GetMass(), DVS, U_STEER);

	// Convert to old steering system
	MATRIX3 M_EF_M50;
	VECTOR3 u_up, R_EF, u_EF;
	double radPitch, radHeading;

	// Get Earth-fixed to M50 rotation matrix
	M_EF_M50 = pGNCUtilities->EARTH_FIXED_TO_M50_COORD(ReadClock());
	// Calculate unit vector of present position (in M50 coordinates)
	u_up = unit(pos);
	// Present position vector in Earth-fixed coordinates
	R_EF = unit(tmul(M_EF_M50, pos));
	// Desired thrust direction in Earth-fixed coordinates
	u_EF = unit(tmul(M_EF_M50, U_STEER));
	// Required pitch angle in radians
	radPitch = PI05 - acos(dotp(U_STEER, u_up));
	// Required heading angle in radians
	radHeading = atan2(R_EF.x * u_EF.y - R_EF.y * u_EF.x, u_EF.z - R_EF.z * dotp(R_EF, u_EF));
	if (radHeading < 0.0)
	{
		radHeading += PI2;
	}

	//sprintf_s(oapiDebugString(), 128, "Heading %lf deg, Pitch %lf deg", radHeading * DEG, radPitch * DEG);

	// Use outputs
	target_pitch = radPitch * DEG;
	radTargetHeading = radHeading;
	timeRemaining = guid.GetTimeRemaining();

	// From old Guide()
	CmdPDot = (target_pitch - ThrAngleP * cos(STS()->GetBank()) - STS()->GetPitch() * DEG) / (2 * ASCENT_MAJOR_CYCLE);
}

void AscentDAP::Navigate(double dt)
{
	VECTOR3 rv, vv;
	STS()->GetRelativePos(STS()->GetSurfaceRef(),rv);
	STS()->GetRelativeVel(STS()->GetSurfaceRef(),vv);
	inertialVelocity=length(vv);

	double F=STS()->CalcNetSSMEThrust();
	double m=STS()->GetMass();
	thrustAcceleration=F/m;

	// TBD: Temporary code for accumulated IMU velocity
	VECTOR3 ThrustVector;
	if (STS()->GetThrustVector(ThrustVector)) {
		MATRIX3 LocalToGlobal;
		STS()->GetRotationMatrix(LocalToGlobal);
		VECTOR3 GlobalThrust = mul(LocalToGlobal, ThrustVector);
		GlobalThrust = mul(M_J2000_to_M50, _V(GlobalThrust.x, GlobalThrust.z, GlobalThrust.y));
		VS += (GlobalThrust / m) * dt;
	}
}

void AscentDAP::AdaptiveGuidanceThrottling( void )
{
	/*char buffer[100];
	sprintf_s( buffer, 100, "MET%f|VREL%f", STS()->GetMET(), STS()->GetAirspeed() );
	oapiWriteLog( buffer );*/
	if (AGT_done == false)
	{
		if ((STS()->GetAirspeed() * MPS2FPS) > VREF_ADJUST)
		{
			double TDEL_adjust = STS()->GetMET() - TREF_ADJUST;// STS-117 data: between -0.21 and 0.21 is nominal
			// HACK using -0.2 to +0.2 for nominal, and maximum adjust if outside -1 to +1
			// TODO should be using ILOAD tables
			// TODO should also change QPOLY and pitch profile
			if (TDEL_adjust < -1)// hot
			{
				THROT[1] = Round( THROT[1] - 21.5 );
			}
			else if (TDEL_adjust < -0.2)// hot
			{
				THROT[1] = Round( THROT[1] + ((26.25 * TDEL_adjust) + 4.75) );
			}
			else if (TDEL_adjust > 1)// cold
			{
				THROT[2] += 8;
			}
			else if (TDEL_adjust > 0.2)// cold
			{
				THROT[2] += Round( (7.5 * TDEL_adjust) + 0.5 );
			}

			AGT_done = true;

			oapiWriteLogV( "TDEL_adjust:%.2f THROT2:%d THROT3:%d", TDEL_adjust, THROT[1], THROT[2] );
		}
	}
	return;
}

void AscentDAP::PFG_INP_TSK()
{
	// Calculate change in accumulated sensed velocity from previous value
	DVS = VS - VSP;
	// Save new value as previous value
	VSP = VS;
}

void AscentDAP::AscentUPP()
{
	// TBD: This should be Ascent UPP code
	VECTOR3 R_AVGG, V_AVGG, IYC, IY_XTRK, IYC_EF, IYT_EF;
	double T_STATE, INCL_TARGET;

	pStateVectorSoftware->GetCurrentStateVectorsM50(R_AVGG, V_AVGG);
	R_AVGG *= MPS2FPS;
	V_AVGG *= MPS2FPS;
	IY_XTRK = guid.GetIYVector();
	T_STATE = ReadClock();

	IYC = unit(crossp(V_AVGG, R_AVGG));

	XTRK = -dotp(R_AVGG, IY_XTRK) * NAUTMI_PER_FT;

	IYC_EF = tmul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T_STATE), IYC);
	IYT_EF = tmul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T_STATE), IY_XTRK);
	INCL_TARGET = acos(-IYT_EF.z);
	MEDS_D_INCL = INCL_TARGET - acos(-IYC_EF.z);
}

void AscentDAP::NullSRBNozzles( void )
{
	bNullSRBNozzles = true;
	return;
}

bool AscentDAP::GetAutoThrottleState( void ) const
{
	return !pSBTC_SOP->GetManThrottle();
}

VECTOR3 AscentDAP::GetAttitudeErrors( void ) const
{
	// HACK this is not the the attitude error (but it's better than nothing...?)
	return _V( -degReqdRatesGuidance.x, degReqdRatesGuidance.y, -degReqdRatesGuidance.z );
}

bool AscentDAP::SERCenabled( void ) const
{
	return enaSERC;
}

double AscentDAP::GetEOVI( int EO ) const
{
	assert( (EO >= 1) && (EO <= 2) && "AscentDAP::GetEOVI.EO" );
	return EOVI[EO - 1];
}

double AscentDAP::GetTgtSpd( void ) const
{
	return guid.GetVDMAG();
}

double AscentDAP::GetInertialVelocity( void ) const
{
	return inertialVelocity;
}

double AscentDAP::GetThrustAcceleration( void ) const
{
	return thrustAcceleration;
}

double AscentDAP::GetTimeRemaining( void ) const
{
	return timeRemaining;
}

double AscentDAP::GetCrossTrack(void) const
{
	return XTRK;
}

double AscentDAP::GetDeltaInclination(void) const
{
	return MEDS_D_INCL;
}

double AscentDAP::GetTargetHeading( void ) const
{
	return radTargetHeading;
}

bool AscentDAP::GetFCSmode( void ) const
{
	return AutoFCS;
}

}
