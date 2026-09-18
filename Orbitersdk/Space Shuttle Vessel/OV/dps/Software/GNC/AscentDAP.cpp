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
2023/06/14   GLS
2023/10/29   GLS
2023/11/26   GLS
2024/05/14   GLS
2025/07/20   GLS
2025/12/27   indy91
2025/12/31   indy91
2026/01/06   indy91
2026/01/22   indy91
2026/01/24   indy91
2026/09/18   GLS
********************************************/
#include "AscentDAP.h"
#include "../../../Atlantis.h"
#include <MathSSV.h>
#include "../../../mission/Mission.h"
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


	// K-Loads
	constexpr float DY1_GRAV = 0.0f;// NOZZLE GRAVITY POSITION (V96U7984C) [deg]
	constexpr float DY2_GRAV = 0.0f;// NOZZLE GRAVITY POSITION (V96U7985C) [deg]
	constexpr float DY3_GRAV = 0.0f;// NOZZLE GRAVITY POSITION (V96U7986C) [deg]
	constexpr float DZ2_GRAV = 0.0f;// NOZZLE GRAVITY POSITION (V96U7987C) [deg]
	constexpr float DZ3_GRAV = 0.0f;// NOZZLE GRAVITY POSITION (V96U7988C) [deg]
	constexpr float DY1_START = 0.0f;// ME1 PITCH DEFLN. FOR SSME START (V97U1782C) [deg]
	constexpr float DY2_START = 0.0f;// ME2 PITCH DEFLN. FOR SSME START (V97U1784C) [deg]
	constexpr float DY3_START = 0.0f;// ME3 PITCH DFLN FOR SSME START (V97U1786C) [deg]
	constexpr float DZ2_START = 0.0f;// ME2 YAW DFLN FOR SSME START (V97U1788C) [deg]
	constexpr float DZ3_START = 0.0f;// ME3 YAW DEFLN. FOR SSME START (V97U1790C) [deg]
	constexpr float ALIM_1 = 96.200405f/*92.0*/;// LOWER LIMIT FOR TERMINATING G-LIMITING (V97U4308C) [fps^2]// TODO correct value and usage
	constexpr float ALIM_2 = 96.522146f/*94.7*/;// LOWER LIMIT FOR INITIATING G-LIMITING (V97U4309C) [fps^2]// TODO correct value and usage
	static float PHI_CMD = 3.141593f;// COMMANDED ROLL ANGLE (V97U4481C) [rad]


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

	enaSERC = false;

	glimiting = false;
	dt_thrt_glim = 0;

	MEFail[0] = false;
	MEFail[1] = false;
	MEFail[2] = false;
	NSSME = 3;

	TgtSpd = 0.0;

	SSMETailoffDV[0] = SSME_TAILOFF_DV_91_2EO;
	SSMETailoffDV[1] = SSME_TAILOFF_DV_91_1EO;
	SSMETailoffDV[2] = SSME_TAILOFF_DV_67;

	J = 1;

	AGT_done = false;

	WriteCOMPOOL_IS( SCP_AUTO, 1 );

	VS = VSP = DVS = _V(0, 0, 0);

	// I-LOADs init
	OMSASS = 1;
	NOMTM = 59.0;

	STOW_SB = false;

	{
		DiscreteBundle* pBundle = BundleManager()->CreateBundle("LOMS", 4);
		/*OMSCommand[LEFT].Connect(pBundle, 2);
		pBundle = BundleManager()->CreateBundle("ROMS", 4);
		OMSCommand[RIGHT].Connect(pBundle, 2);*/

		pBundle = BundleManager()->CreateBundle( "THRUSTER_CMD", 16 );
		SERC.Connect( pBundle, 6 );
	}
}

AscentDAP::~AscentDAP()
{
}

void AscentDAP::OnPreStep( double simt, double simdt, double mjd )
{
	if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0)
	{
		// check if AUTO or CSS
		if (ReadCOMPOOL_IS( SCP_AUTO ) == 1)
		{
			if ((ReadCOMPOOL_IS( SCP_CSSP ) == 1) || (ReadCOMPOOL_IS( SCP_CSSRY ) == 1))
			{
				// to CSS
				WriteCOMPOOL_IS( SCP_AUTO, 0 );
			}
		}
		else
		{
			if ((ReadCOMPOOL_IS( SCP_AUTOP ) == 1) || (ReadCOMPOOL_IS( SCP_AUTORY ) == 1))
			{
				// to AUTO
				WriteCOMPOOL_IS( SCP_AUTO, 1 );
			}
		}

		// HACK save VI on EO
		if (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1)
		{
			if ((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1))
			{
				if (ReadCOMPOOL_SS( SCP_FIRST_EO_VI ) == 0.0) WriteCOMPOOL_SS( SCP_FIRST_EO_VI, ReadCOMPOOL_SS( SCP_V_INERTIAL_MAG ) );
			}

			if ((ReadCOMPOOL_IS( SCP_SSME_FAILS ) > 3) && (ReadCOMPOOL_IS( SCP_SSME_FAILS ) < 7))
			{
				if (ReadCOMPOOL_SS( SCP_SECOND_EO_VI ) == 0.0) WriteCOMPOOL_SS( SCP_SECOND_EO_VI, ReadCOMPOOL_SS( SCP_V_INERTIAL_MAG ) );
			}
		}
		else if (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1)
		{
			if ((ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN ) == 1) || (ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN ) == 1))
			{
				if (ReadCOMPOOL_SS( SCP_FIRST_EO_VI ) == 0.0) WriteCOMPOOL_SS( SCP_FIRST_EO_VI, ReadCOMPOOL_SS( SCP_V_INERTIAL_MAG ) );
			}

			if ((ReadCOMPOOL_IS( SCP_AUTO_2ND_OUT ) == 1) || ((ReadCOMPOOL_IS( SCP_SSME_FAILS ) > 3) && (ReadCOMPOOL_IS( SCP_SSME_FAILS ) < 7)))
			{
				if (ReadCOMPOOL_SS( SCP_SECOND_EO_VI ) == 0.0) WriteCOMPOOL_SS( SCP_SECOND_EO_VI, ReadCOMPOOL_SS( SCP_V_INERTIAL_MAG ) );
			}
		}
	}

	VECTOR3 degReqdRates;
	VECTOR3 AngularVelocity;
	STS()->GetAngularVel( AngularVelocity );
	AngularVelocity *= DEG;

	// handle KMAX
	if (ReadCOMPOOL_IS( SCP_NOM_THROT_CMD ) == 1) WriteCOMPOOL_IS( SCP_KMAX, ReadCOMPOOL_IS( SCP_KMAX_NOM ) );
	if (ReadCOMPOOL_IS( SCP_ABT_THROT_CMD ) == 1) WriteCOMPOOL_IS( SCP_KMAX, ReadCOMPOOL_IS( SCP_KMAX_ABT ) );
	if (ReadCOMPOOL_IS( SCP_MAX_THROT_CMD ) == 1) WriteCOMPOOL_IS( SCP_KMAX, ReadCOMPOOL_IS( SCP_KMAX_SECONDARY ) );

	if (ReadCOMPOOL_IS( SCP_MM_CODE_101 ) == 1)
	{
		// HACK to handle MPS slew and start position cmd
		unsigned short MPS_SLEW_COMPLETE = ReadCOMPOOL_IS( SCP_MPS_SLEW_COMPLETE );

		// slew
		float SF_MPS_SLEW = 0.0f;
		if (MPS_SLEW_COMPLETE == 0)
		{
			SF_MPS_SLEW = ReadCOMPOOL_SS( SCP_SF_MPS_SLEW_NOM );
		}
		float slew = SF_MPS_SLEW * ReadCOMPOOL_SS( SCP_MPS_SLEW_CMD );

		// bias
		float DY1_BIAS = DY1_GRAV;
		float DY2_BIAS = DY2_GRAV;
		float DZ2_BIAS = DY3_GRAV;
		float DY3_BIAS = DZ2_GRAV;
		float DZ3_BIAS = DZ3_GRAV;

		unsigned short ME_RESTART_POS = ReadCOMPOOL_IS( SCP_RETURN_SSME_TO_START_POS );
		unsigned short SSME_LCH_POS = ReadCOMPOOL_IS( SCP_PREP_SSMES );
		unsigned short SSME_START_POS = (ME_RESTART_POS == 1) && (SSME_LCH_POS == 0) ? 1 : 0;
		if (SSME_START_POS == 1)
		{
			DY1_BIAS = DY1_START;
			DY2_BIAS = DY2_START;
			DY3_BIAS = DY3_START;
		}

		if (SSME_START_POS == 1)
		{
			DZ2_BIAS = DZ2_START;
			DZ3_BIAS = DZ3_START;
		}
		else if (SSME_LCH_POS == 1)
		{
			DZ2_BIAS = -ReadCOMPOOL_SS( SCP_YAW_BIAS_NOM );
			DZ3_BIAS = ReadCOMPOOL_SS( SCP_YAW_BIAS_NOM );
		}

		float DYC1 = slew + DY1_BIAS;
		float DZC1 = slew;
		float DYC2 = slew + DY2_BIAS;
		float DZC2 = slew + DZ2_BIAS;
		float DYC3 = slew + DY3_BIAS;
		float DZC3 = slew + DZ3_BIAS;

		WriteCOMPOOL_SS( SCP_DYC1, DYC1 );
		WriteCOMPOOL_SS( SCP_DZC1, DZC1 );
		WriteCOMPOOL_SS( SCP_DYC2, DYC2 );
		WriteCOMPOOL_SS( SCP_DZC2, DZC2 );
		WriteCOMPOOL_SS( SCP_DYC3, DYC3 );
		WriteCOMPOOL_SS( SCP_DZC3, DZC3 );
	}
	else if (ReadCOMPOOL_IS( SCP_MM_CODE_102 ) == 1)
	{
		// use hEarth as switch to init autopilot
		if (hEarth == NULL) InitializeAutopilot();


		FirstStageGuidance( simdt );
		if (ReadCOMPOOL_IS( SCP_AUTO ) == 1) degReqdRates = degReqdRatesGuidance;// AUTO
		else
		{
			// CSS
			// TODO when RHCs in detent, hold attitude when rates fall below 3º/s
			degReqdRates = _V( range( -12, ReadCOMPOOL_SS( SCP_DEMAN ) * 0.5, 12 ), -range( -6, ReadCOMPOOL_SS( SCP_DYMAN ) * 0.5, 6 ), range( -12, ReadCOMPOOL_SS( SCP_DAMAN ) * 0.5, 12 ) );
		}

		if (ReadCOMPOOL_IS( SCP_SRB_MODING_SEP ) == 1)
		{
			STS()->SetSRBGimbalAngles( static_cast<SIDE> (0), 0, 0 );
			STS()->SetSRBGimbalAngles( static_cast<SIDE> (1), 0, 0 );
		}
		else GimbalSRBs( simdt, degReqdRates, AngularVelocity );
		GimbalSSMEs( simdt, degReqdRates, AngularVelocity );
	}
	else if (ReadCOMPOOL_IS( SCP_MM_CODE_103 ) == 1)
	{
		SecondStageGuidance( simdt );
		if (ReadCOMPOOL_IS( SCP_MECO_CMD ) == 0)
		{
			if (ReadCOMPOOL_IS( SCP_AUTO ) == 1) degReqdRates = degReqdRatesGuidance;// AUTO
			else
			{
				// CSS
				// TODO when RHCs in detent, hold attitude when rates fall below 3º/s
				degReqdRates = _V( range( -12, ReadCOMPOOL_SS( SCP_DEMAN ) * 0.5, 12 ), -range( -6, ReadCOMPOOL_SS( SCP_DYMAN ) * 0.5, 6 ), range( -12, ReadCOMPOOL_SS( SCP_DAMAN ) * 0.5, 12 ) );
			}
		}
		else
		{
			degReqdRates = _V( 0.0, 0.0, 0.0 );// hold attitude post-MECO

			if (ReadCOMPOOL_IS( SCP_ME_ZERO ) == 1)
			{
				// stop any SERC firing, TransDAP takes over now
				SERC.ResetLine();
			}
		}

		GimbalSSMEs( simdt, degReqdRates, AngularVelocity );
	}


	unsigned short ME1_FAIL_SHUTDOWN = ReadCOMPOOL_IS( SCP_ME1_FAIL_SHUTDOWN );
	unsigned short ME2_FAIL_SHUTDOWN = ReadCOMPOOL_IS( SCP_ME2_FAIL_SHUTDOWN );
	unsigned short ME3_FAIL_SHUTDOWN = ReadCOMPOOL_IS( SCP_ME3_FAIL_SHUTDOWN );
	unsigned short MECO_CMD = ReadCOMPOOL_IS( SCP_MECO_CMD );
	unsigned short SRB_IGN_CMD = ReadCOMPOOL_IS( SCP_SRB_IGNITION_CMD );

	if (MECO_CMD == 0)
	{
		if (ME1_FAIL_SHUTDOWN == 1)
		{
			if (ME2_FAIL_SHUTDOWN == 1)
			{
				if (ME3_FAIL_SHUTDOWN == 1)
				{
					WriteCOMPOOL_IS( SCP_SSME_FAILS, 7 );
				}
				else
				{
					WriteCOMPOOL_IS( SCP_SSME_FAILS, 4 );
				}
			}
			else
			{
				if (ME3_FAIL_SHUTDOWN == 1)
				{
					WriteCOMPOOL_IS( SCP_SSME_FAILS, 5 );
				}
				else
				{
					if (SRB_IGN_CMD == 1)
					{
						WriteCOMPOOL_IS( SCP_SSME_FAILS, 1 );
					}
					else
					{
						WriteCOMPOOL_IS( SCP_SSME_FAILS, 0 );
					}
				}
			}
		}
		else
		{
			if (ME2_FAIL_SHUTDOWN == 1)
			{
				if (ME3_FAIL_SHUTDOWN == 1)
				{
					WriteCOMPOOL_IS( SCP_SSME_FAILS, 6 );
				}
				else
				{
					if (SRB_IGN_CMD == 1)
					{
						WriteCOMPOOL_IS( SCP_SSME_FAILS, 2 );
					}
					else
					{
						WriteCOMPOOL_IS( SCP_SSME_FAILS, 0 );
					}
				}
			}
			else
			{
				if (ME3_FAIL_SHUTDOWN == 1)
				{
					if (SRB_IGN_CMD == 1)
					{
						WriteCOMPOOL_IS( SCP_SSME_FAILS, 3 );
					}
					else
					{
						WriteCOMPOOL_IS( SCP_SSME_FAILS, 0 );
					}
				}
				else
				{
					WriteCOMPOOL_IS( SCP_SSME_FAILS, 0 );
				}
			}
		}
	}
	else
	{
		WriteCOMPOOL_IS( SCP_SSME_FAILS, 0 );
	}


	if ((ReadCOMPOOL_IS( SCP_RS_AUTO_SEQ_START ) == 1) && (ReadCOMPOOL_IS( SCP_RECYCLE_COUNT ) == 0)) STOW_SB = true;
	else STOW_SB = false;

	AEROSURFACE_CONTROL();


	// DAP lights
	if (ReadCOMPOOL_IS( SCP_MECO_CONFIRMED ) == 0)
	{
		if (ReadCOMPOOL_IS( SCP_AUTO ) == 1)
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

	// HACK should be turned on at MM101_INIT
	RAUTO_BFLAMP = true;
	LAUTO_BFLAMP = true;
	if (ReadCOMPOOL_IS( SCP_MPS_LO2_DUMP_STOP ) == 1)
	{
		RAUTO_BFLAMP = false;
		LAUTO_BFLAMP = false;
	}
	RMNL_BFLAMP = false;
	LMNL_BFLAMP = false;

	// output to MDMs
	if (LAUTO_PLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0200 );
	else WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) & ~0x0200 );
	if (LCSS_PLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0200 );
	else WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) & ~0x0200 );
	if (LAUTO_RYLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0100 );
	else WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) & ~0x0100 );
	if (LCSS_RYLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0100 );
	else WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) & ~0x0100 );
	if (LAUTO_BFLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0800 );
	else WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) & ~0x0800 );
	if (LMNL_BFLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0800 );
	else WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) & ~0x0800 );
	if (RAUTO_PLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0200 );
	else WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) & ~0x0200 );
	if (RCSS_PLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0200 );
	else WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) & ~0x0200 );
	if (RAUTO_RYLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0100 );
	else WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) & ~0x0100 );
	if (RCSS_RYLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0100 );
	else WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) & ~0x0100 );
	if (RAUTO_BFLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0800 );
	else WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) & ~0x0800 );
	if (RMNL_BFLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0800 );
	else WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) & ~0x0800 );

	WriteCOMPOOL_IS( SCP_LCSS_PLAMP, LCSS_PLAMP ? 1 : 0 );
	return;
}

bool AscentDAP::OnParseLine(const char* keyword, const char* value)
{
	return false;
}

void AscentDAP::OnSaveState(FILEHANDLE scn) const
{
	return;
}

void AscentDAP::FirstStageGuidance( double dt )
{
	STS()->CalcSSMEThrustAngles(0, ThrAngleP, ThrAngleY);
	FirstStageThrottle( dt );
	FirstStageRateCommand();
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
	}
	return;
}

void AscentDAP::InitializeAutopilot()
{
	VECTOR3 IYD;
	double TgtAlt, TgtInc, TgtFPA, VDMAG, EarthRadius, NODE_SLOPE, T_GMTLO_REF;
	bool EF_PLANE_SW;

	mission::Mission* pMission = STS()->GetMissionData();
	TgtInc=pMission->GetMECOInc();
	TgtFPA=pMission->GetMECOFPA();
	TgtAlt=pMission->GetMECOAlt();
	VDMAG = pMission->GetMECOVel();
	TgtSpd = VDMAG - (SSMETailoffDV[2] / MPS2FPS);
	IYD = pMission->GetIYD();
	EF_PLANE_SW = pMission->GetEFPLANESW();
	NODE_SLOPE = pMission->GetNODESLOPE();
	T_GMTLO_REF = pMission->GetTGMTLOREF();
	GNCUtilities* pGNCUtilities = dynamic_cast<GNCUtilities*>(GetCOMSUB( "GNCUtilities" ));

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
		// Is it Earth-fixed?
		if (EF_PLANE_SW)
		{
			// Yes
			// Convert to M50 coordinates
			IY_M50 = mul(pGNCUtilities->EARTH_FIXED_TO_M50_COORD(PRED_GMT_LO), IYD);
		}
		else
		{
			// No
			MATRIX3 M_NODE_ADJ;
			double DELTA_NODE, CNODE, SNODE;

			// Node adjustment to the orbit plane to account for nodal regression and orbit phase angle changes between in-plane and actual launch times
			DELTA_NODE = NODE_SLOPE * (PRED_GMT_LO - T_GMTLO_REF);

			// TBD: Second phase window
			/*
			if (PRED_GMT_LO > T_GMTLO_PHASE)
			{
				DELTA_NODE = DELTA_NODE + DELTA_NODE_PHASE;
			}
			*/

			// Compute node adjustment matrix and unit vector normal to orbit plane :
			CNODE = cos(DELTA_NODE);
			SNODE = sin(DELTA_NODE);
			M_NODE_ADJ = _M(CNODE, SNODE, 0.0, -SNODE, CNODE, 0.0, 0.0, 0.0, 1.0);
			IY_M50 = mul(M_NODE_ADJ, IYD);
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
	guid.Init(PRED_GMT_LO, TgtRad, VDMAG, TgtFPA, IY_M50);

	// HACK save to COMPOOL (should be I-Load)
	WriteCOMPOOL_VD( SCP_IYD, IY_M50/*IYD*/ );

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
			yawGimbal[0] = range(-8.0, degRateError.data[YAW], 8.0) + range(-8.0, 0.75*degRateError.data[ROLL], 8.0);
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0) + range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[1] = range(-8.0, degRateError.data[YAW], 8.0);
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0) - range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[2] = range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;
			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += ThrAngleY - 3.5;
			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += ThrAngleY + 3.5;

			WriteCOMPOOL_SS( SCP_DYC1, static_cast<float>(pitchGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DZC1, static_cast<float>(yawGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DYC2, static_cast<float>(pitchGimbal[1]) );
			WriteCOMPOOL_SS( SCP_DZC2, static_cast<float>(yawGimbal[1]) );
			WriteCOMPOOL_SS( SCP_DYC3, static_cast<float>(pitchGimbal[2]) );
			WriteCOMPOOL_SS( SCP_DZC3, static_cast<float>(yawGimbal[2]) );
			break;
		case 1:// C out
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0) + range(-7.0, 1.5*degRateError.data[ROLL], 7.0);
			yawGimbal[1] = range(-8.0, degRateError.data[YAW], 8.0);
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0) - range(-7.0, 1.5*degRateError.data[ROLL], 7.0);
			yawGimbal[2] = range(-8.0, degRateError.data[YAW], 8.0);

			STS()->CalcSSMEThrustAngles( 2, ThrAngleP, ThrAngleY );
			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] -= 3.5;

			STS()->CalcSSMEThrustAngles( 3, ThrAngleP, ThrAngleY );
			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += 3.5;

			WriteCOMPOOL_SS( SCP_DYC2, static_cast<float>(pitchGimbal[1]) );
			WriteCOMPOOL_SS( SCP_DZC2, static_cast<float>(yawGimbal[1]) );
			WriteCOMPOOL_SS( SCP_DYC3, static_cast<float>(pitchGimbal[2]) );
			WriteCOMPOOL_SS( SCP_DZC3, static_cast<float>(yawGimbal[2]) );
			break;
		case 2:// L out
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = range(-8.0, degRateError.data[YAW], 8.0) + range(-8.0, 0.75*degRateError.data[ROLL], 8.0);
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0) - range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[2] = range(-8.0, degRateError.data[YAW], 8.0);

			STS()->CalcSSMEThrustAngles( 1, ThrAngleP, ThrAngleY );
			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;

			STS()->CalcSSMEThrustAngles( 3, ThrAngleP, ThrAngleY );
			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += ThrAngleY + 3.5;

			WriteCOMPOOL_SS( SCP_DYC1, static_cast<float>(pitchGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DZC1, static_cast<float>(yawGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DYC3, static_cast<float>(pitchGimbal[2]) );
			WriteCOMPOOL_SS( SCP_DZC3, static_cast<float>(yawGimbal[2]) );
			break;
		case 3:// C, L out
			pitchGimbal[2] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[2] = range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[2] += ThrAngleP + 10;
			yawGimbal[2] += ThrAngleY + 3.5;

			WriteCOMPOOL_SS( SCP_DYC3, static_cast<float>(-pitchGimbal[2]) );
			WriteCOMPOOL_SS( SCP_DZC3, static_cast<float>(-yawGimbal[2]) );
			break;
		case 4:// R out
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = range(-8.0, degRateError.data[YAW], 8.0) + range(-8.0, 0.75*degRateError.data[ROLL], 8.0);
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0) + range(-7.0, 2.5*degRateError.data[ROLL], 7.0);
			yawGimbal[1] = range(-8.0, degRateError.data[YAW], 8.0);

			STS()->CalcSSMEThrustAngles( 1, ThrAngleP, ThrAngleY );
			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;

			STS()->CalcSSMEThrustAngles( 2, ThrAngleP, ThrAngleY );
			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += ThrAngleY - 3.5;

			WriteCOMPOOL_SS( SCP_DYC1, static_cast<float>(pitchGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DZC1, static_cast<float>(yawGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DYC2, static_cast<float>(pitchGimbal[1]) );
			WriteCOMPOOL_SS( SCP_DZC2, static_cast<float>(yawGimbal[1]) );
			break;
		case 5:// C, R out
			pitchGimbal[1] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[1] = range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[1] += ThrAngleP + 10;
			yawGimbal[1] += ThrAngleY - 3.5;

			WriteCOMPOOL_SS( SCP_DYC2, static_cast<float>(pitchGimbal[1]) );
			WriteCOMPOOL_SS( SCP_DZC2, static_cast<float>(yawGimbal[1]) );
			break;
		case 6:// L, R out
			pitchGimbal[0] = -range(-8.0, degRateError.data[PITCH], 8.0);
			yawGimbal[0] = range(-8.0, degRateError.data[YAW], 8.0);

			pitchGimbal[0] += ThrAngleP + 16;
			yawGimbal[0] += ThrAngleY;

			WriteCOMPOOL_SS( SCP_DYC1, static_cast<float>(pitchGimbal[0]) );
			WriteCOMPOOL_SS( SCP_DZC1, static_cast<float>(yawGimbal[0]) );
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
	if (ReadCOMPOOL_IS( SCP_GUIDANCE_INITIATE ) == 0)
	{
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

			if (V_RHO_MAG > ReadCOMPOOL_SS( SCP_V_RHO_PHI )) PHI_CMD = ReadCOMPOOL_SS( SCP_PHI_2STG );

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

			AGT_done = true;// don't do AGT
			J = 5;// bypass throttle table
			if (ReadCOMPOOL_IS( SCP_S_MAN_THROT ) == 0) WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_KMAX ) );// throttle to mission power level

			// update MECO targets
			if (NSSME > 0) TgtSpd = STS()->GetMissionData()->GetMECOVel() - (SSMETailoffDV[NSSME - 1] / MPS2FPS);
		}
	}

	// SERC
	if ((NSSME == 1) && (ReadCOMPOOL_IS( SCP_LH_RH_SRB_PC_50_PSI_FLAG ) == 1))// enable SERC in MM102 only at SRB tailoff
	{
		enaSERC = true;
	}

	// calc and set SSME throttle
	AdaptiveGuidanceThrottling();

	if (ReadCOMPOOL_IS( SCP_S_MAN_THROT ) == 0)
	{
		if (J < 5)
		{
			if ((STS()->GetAirspeed() * MPS2FPS) >= ReadCOMPOOL_ASS( SCP_QPOLY, J, 4 ))
			{
				WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_AIS( SCP_THROT, J, 4 ) );
				J = J + 1;
			}
		}
	}
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

			glimiting = false;// reset g-limiting
			dt_thrt_glim = -2;// HACK delay g-limiting action by 2sec (if it re-triggers) to account for failed engine tailoff thrust
			if (ReadCOMPOOL_IS( SCP_S_MAN_THROT ) == 0) WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_KMAX ) );// throttle to mission power level

			// update MECO targets
			if (NSSME > 0) TgtSpd = STS()->GetMissionData()->GetMECOVel() - (SSMETailoffDV[NSSME - 1] / MPS2FPS);
		}
	}

	// SERC
	if (NSSME == 1)// enable SERC automatically in MM103
	{// TODO enable SERC when "sensed acceleration falls below a predefined limit"
		enaSERC = true;
	}

	// low-level sensor arm
	if ((STS()->GetMass() * KG2LBM * LBS2SL) < ReadCOMPOOL_SS( SCP_MASS_LOW_LEVEL )) WriteCOMPOOL_IS( SCP_S_LOW_LEVEL, 1 );

	if (ReadCOMPOOL_IS( SCP_S_MECO ) == 1)
	{
		// MPS Guidance Cutoff Task

		double VGO_FCD;

		// Velocity-to-go
		VGO_FCD = TgtSpd - inertialVelocity;
		// Time-to-go
		timeRemaining = VGO_FCD / thrustAcceleration;
		WriteCOMPOOL_SS( SCP_TGO, static_cast<float>(timeRemaining) );
		WriteCOMPOOL_SS( SCP_TMET_MECO, static_cast<float>(STS()->GetMET() + timeRemaining) );

		// check for MECO
		if ((inertialVelocity >= TgtSpd) && (ReadCOMPOOL_IS( SCP_S_MAN_THROT ) == 0))
		{
			//reached target speed
			WriteCOMPOOL_IS(SCP_MECO_CMD, 1);

			oapiWriteLogV("MECO @ MET %.2f", STS()->GetMET());
			return;
		}
	}

	// calc and set SSME throttle
	if (ReadCOMPOOL_IS( SCP_S_MAN_THROT ) == 0)
	{
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
		if ((timeRemaining <= 6) && (ReadCOMPOOL_IS( SCP_S_MECO ) == 0))
		{
			if (NSSME == 3 ) WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_KMIN ) );
			else WriteCOMPOOL_IS( SCP_K_CMD, ReadCOMPOOL_IS( SCP_K_CO_MAX ) );
			WriteCOMPOOL_IS( SCP_S_MECO, 1 );
			oapiWriteLogV( "Fine Count (throttle to %d%%) @ MET %.2f", ReadCOMPOOL_IS( SCP_K_CMD ), STS()->GetMET() );
		}
	}
	return;
}

void AscentDAP::MajorCycle()
{
	VECTOR3 pos, vel, U_STEER;
	GNCUtilities* pGNCUtilities = dynamic_cast<GNCUtilities*>(GetCOMSUB( "GNCUtilities" ));

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
	WriteCOMPOOL_SS( SCP_TGO, static_cast<float>(timeRemaining) );
	WriteCOMPOOL_SS( SCP_TMET_MECO, static_cast<float>(STS()->GetMET() + timeRemaining) );

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
		if ((STS()->GetAirspeed() * MPS2FPS) > ReadCOMPOOL_SS( SCP_VREF_ADJUST ))
		{
			double TDEL_adjust = STS()->GetMET() - ReadCOMPOOL_SS( SCP_TREF_ADJUST );// STS-117 data: between -0.21 and 0.21 is nominal
			// HACK using -0.2 to +0.2 for nominal, and maximum adjust if outside -1 to +1
			// TODO should be using ILOAD tables
			// TODO should also change QPOLY and pitch profile
			if (TDEL_adjust < -1)// hot
			{
				WriteCOMPOOL_AIS( SCP_THROT, 2, Round( ReadCOMPOOL_AIS( SCP_THROT, 2, 4 ) - 21.5 ), 4 );
			}
			else if (TDEL_adjust < -0.2)// hot
			{
				WriteCOMPOOL_AIS( SCP_THROT, 2, Round( ReadCOMPOOL_AIS( SCP_THROT, 2, 4 ) + ((26.25 * TDEL_adjust) + 4.75) ), 4 );
			}
			else if (TDEL_adjust > 1)// cold
			{
				WriteCOMPOOL_AIS( SCP_THROT, 3, ReadCOMPOOL_AIS( SCP_THROT, 3, 4 ) + 8, 4 );
			}
			else if (TDEL_adjust > 0.2)// cold
			{
				WriteCOMPOOL_AIS( SCP_THROT, 3, ReadCOMPOOL_AIS( SCP_THROT, 3, 4 ) + Round( (7.5 * TDEL_adjust) + 0.5 ), 4 );
			}

			AGT_done = true;

			oapiWriteLogV( "TDEL_adjust:%.2f THROT2:%d THROT3:%d", TDEL_adjust, ReadCOMPOOL_AIS( SCP_THROT, 2, 4 ), ReadCOMPOOL_AIS( SCP_THROT, 3, 4 ) );
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

VECTOR3 AscentDAP::GetAttitudeErrors( void ) const
{
	// HACK this is not the the attitude error (but it's better than nothing...?)
	return _V( -degReqdRatesGuidance.x, degReqdRatesGuidance.y, -degReqdRatesGuidance.z );
}

double AscentDAP::GetTgtSpd( void ) const
{
	return TgtSpd;
}

double AscentDAP::GetThrustAcceleration( void ) const
{
	return thrustAcceleration;
}


void AscentDAP::AEROSURFACE_CONTROL( void )
{
	if (ReadCOMPOOL_IS( SCP_SRB_IGNITION_CMD ) == 0)
	{
		RUD_SB_CMD();
		ELEVON_SLAVING();
	}
	else
	{
		if (0/*TODO ELEV_LR*/)
		{
			ELEVON_LOAD_RELIEF();
			ELEVON_SLAVING();
		}
	}

	BODY_FLAP_CONTROL();
	return;
}

void AscentDAP::BODY_FLAP_CONTROL( void )
{
	float DBFE = ReadCOMPOOL_SS( SCP_AERO_SLEW_CMD ) * ReadCOMPOOL_SS( SCP_SF_BF_SLEW_NOM ) - ReadCOMPOOL_SS( SCP_DBFOFB );

	float DBFRC = ReadCOMPOOL_SS( SCP_DBFRC );

	if (((fabs( DBFE ) > ReadCOMPOOL_SS( SCP_DBFE_OUTER )) || (DBFRC == sign( DBFE ))) && (fabs( DBFE ) > ReadCOMPOOL_SS( SCP_DBFE_INNER ))) DBFRC = static_cast<float>(sign( DBFE ));
	else DBFRC = 0.0f;

	WriteCOMPOOL_SS( SCP_DBFRC, DBFRC );
	return;
}

void AscentDAP::RUD_SB_CMD( void )
{
	float DSBPC = 0.0f;
	if (STOW_SB == false) DSBPC = (ReadCOMPOOL_SS( SCP_AERO_SLEW_CMD ) * ReadCOMPOOL_SS( SCP_SF_SB_SLEW_NOM )) + ReadCOMPOOL_SS( SCP_DSB_BIAS_SLEW );
	else DSBPC = ReadCOMPOOL_SS( SCP_DSB_CLOSED );
	// TODO NFADE_DSBCLOSE
	WriteCOMPOOL_SS( SCP_DSBPC, DSBPC );

	float DRPC = ReadCOMPOOL_SS( SCP_AERO_SLEW_CMD ) * ReadCOMPOOL_SS( SCP_SF_RUD_SLEW_NOM );
	WriteCOMPOOL_SS( SCP_DRPC, DRPC );
	return;
}

void AscentDAP::ELEVON_LOAD_RELIEF( void )
{
	// TODO

	//FADER* FADE_ELEVON_IN = new FADER( NFADE_ELEVON_IN );
	return;
}

void AscentDAP::ELEVON_SLAVING( void )
{
	float pos = 0.0f;
	if (ReadCOMPOOL_IS( SCP_AERO_SLEW ) == 1) pos = ReadCOMPOOL_SS( SCP_AERO_SLEW_CMD ) * ReadCOMPOOL_SS( SCP_SF_ELVN_SLEW_NOM );
	else pos = 0.0f;// TODO

	// TODO FADE_ELEVON_IN
	// TODO FADE_ELEVON_OUT

	/*DLIBPC = FADE_ELEVON_IN->Fade( dt );
	DRIBPC = DLIBPC;

	DLOBPC = FADE_ELEVON_OUT->Fade( dt );
	DROBPC = DLOBPC;*/

	WriteCOMPOOL_SS( SCP_DLIBPC, pos );
	WriteCOMPOOL_SS( SCP_DRIBPC, pos );
	WriteCOMPOOL_SS( SCP_DLOBPC, pos );
	WriteCOMPOOL_SS( SCP_DROBPC, pos );
	return;
}

}
