/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/08/05   GLS
********************************************/
#include "AutolandGuidance.h"
#include <MathSSV.h>
#include <EngConst.h>
#include <FILT1.h>


namespace dps
{
	/////// Autoland (from JSC-23266, and AIAA 82-1604-CP, and AIAA-92-1273) ///////
	/**/constexpr double H_FF = 80.0;// [ft]

	/**/constexpr double H_MIN = 30.0;// [ft]

	/**/constexpr double K_HDOT_TC = 0.012;// [g.s/ft]

	/**/constexpr double K_HDOT_SGS = 0.012;// [g.s/ft]

	// altitude error limit in Trajectory capture and Steep glide slope
	/**/constexpr double H_ERROR_MAX = 300.0;// [ft]

	/**/constexpr double K_H_TC = 0.0024;// [g/ft]

	/**/constexpr double K_H_SGS = 0.0024;// [g/ft]

	// altitude error limit for integration in Steep glide slope
	/**/constexpr double H_INTMX = 50.0;// [ft]

	/**/constexpr double K_HINT1 = 0.00012;// [g/ft.s]

	/**/constexpr double K_HDOT_FSGS = 0.012;// [g.s/ft]

	/**/constexpr double K_H_FSGS = 0.0024;// [g.ft]

	/**/constexpr double K_INT = 0.05;// [s^-1]

	/**/constexpr double A13 = 1.0;// [rad/s]

	/**/constexpr double A40 = 1.0;// [rad/s]

	/**/constexpr double TAU_GAMMA = 2.0;// [s]

	/**/constexpr double H_TD1_DOT = 8.0;// [fps]

	/**/constexpr double TAU_TD1 = 5.0;// [s]

	/**/constexpr double K_FLR = 0.025;// [g.s^2/ft]

	/**/constexpr double H_NO_ACC = 2.0;// [ft]

	/**/constexpr double TAU_TD2 = 5.0;// [s]

	/**/constexpr double H_TD2_DOT = -3.0;// [fps]

	/**/constexpr double A3 = 10.0;// [rad/s]

	/**/constexpr double K_HDOT = 0.012;// [g.s/ft]

	// not used due to stability
	/**/constexpr double K_IFLR = 0.0;// [s^-1]

	/**/constexpr double K_YDOT = 10.0;// [s]

	/**/constexpr double K_Y1 = 0.07;// [deg/ft.s]

	/**/constexpr double Y_LIMIT = 1000.0;// [ft]

	/**/constexpr double H_WL = 7500.0;// [ft]

	// roll limit for altitudes above H_WL in AUTO
	/**/constexpr double PHI_M1 = 45.0;// [deg]

	// roll limit for altitudes below H_WL in AUTO
	/**/constexpr double PHI_M2 = 20.0;// [deg]

	// roll limit in CSS
	/**/constexpr double PHI_M3 = 90.0;// [deg]

	/**/constexpr double K_R2 = 0.15;// (exact value can't be read in AIAA-92-1273, so using lower gain value in AIAA 82-1604-CP) [s^1]

	/**/constexpr double NZC_LIM = 1.0;// [g]

	constexpr double A14 = 1.0;// [rad/s]

	constexpr double K_SB = 2.0;// [deg/fps]

	constexpr double SB_REF = 65.0;// [deg]

	// altitude to start SB_MODE phase 2
	constexpr double H_SB2 = 3000.0;// [ft]

	// altitude to start SB_MODE phase 3
	constexpr double H_SB3 = 500.0;// [ft]

	// maximum speedbrake in SB_MODE = 2 except for TAL
	constexpr double SB_MAX = 98.6;// [deg]

	// maximum speedbrake in SB_MODE = 2 except for TAL
	constexpr double SB_LIM2_NOM = 80.0;// [deg]

	// maximum speedbrake in SB_MODE = 3 for nominal speedbrake logic
	constexpr double SB_LIM3_NOM = 50.0;// [deg]

	// maximum speedbrake in SB_MODE = 3 for short-field or ELS speedbrake logic
	constexpr double SB_LIM3_SHRTELS = 80.0;// [deg]

	constexpr double SA1962_Altitude[7] = {-1000.0, 0.0, 1000.0, 2000.0, 3000.0, 4000.0, 5000.0};// [ft]
	constexpr double SA1962_Sigma[7] = {1.0295704, 1.0, 0.971070, 0.942781, 0.915130, 0.888108, 0.861706};// [1]


	AutolandGuidance::AutolandGuidance( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "AutolandGuidance" )
	{
		RESET = 1;

		PMODE = 1;
		FMODE = 1;
		TGMER = 0.0;
		TTD1I = 0.0;
		GAMMA_C3 = 0.0;
		NZCP = 0.0;
		RC = 0.0;

		SB_FIRSTPASS = 1;
		SB_SEL = 1;
		SB_MODE = 1;
		DSBC_SMART = 0.0;
		TDX_1 = 0.0;
		TDX_2 = 0.0;
		TDX_3 = 0.0;
		TDX_4 = 0.0;
		TDX_5 = 0.0;
		TDX_6 = 0.0;

		fltrNZ_C2I_12 = new FILT1();
		fltrNZ_C2I_3 = new FILT1();
		fltrNZ_C1I = new FILT1();
		fltrGAMMA_C3 = new FILT1();
		fltrTTD1I = new FILT1();
		fltrA3_ALGNCZ = new FILT1();
		fltrA13 = new FILT1();
		fltrA14 = new FILT1();
		fltrA40 = new FILT1();
		fltrA14_WINDSPEED = new FILT1();
		intWINDSPEED = new FILT1();

		step = 0.16;

		V_REF = 506.3;
		return;
	}

	AutolandGuidance::~AutolandGuidance( void )
	{
		delete fltrNZ_C2I_12;
		delete fltrNZ_C2I_3;
		delete fltrNZ_C1I;
		delete fltrGAMMA_C3;
		delete fltrTTD1I;
		delete fltrA3_ALGNCZ;
		delete fltrA13;
		delete fltrA14;
		delete fltrA40;
		delete fltrA14_WINDSPEED;
		delete intWINDSPEED;
		return;
	}

	bool AutolandGuidance::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "RESET", 5 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) RESET = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "SB_FIRSTPASS", 12 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) SB_FIRSTPASS = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "SB_MODE", 7 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if ((tmp >= 1) && (tmp <= 3)) SB_MODE = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "fltrA13", 7 ))
		{
			fltrA13->LoadState( value );
			return true;
		}
		else if (!_strnicmp( keyword, "DSBC_SMART", 10 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			if ((tmp >= 0.0) && (tmp <= 98.6)) DSBC_SMART = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "TDX", 3 ))
		{
			double tmp1 = 0.0;
			double tmp2 = 0.0;
			double tmp3 = 0.0;
			double tmp4 = 0.0;
			double tmp5 = 0.0;
			double tmp6 = 0.0;
			sscanf_s( value, "%lf %lf %lf %lf %lf %lf", &tmp1, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6 );
			TDX_1 = tmp1;
			TDX_2 = tmp2;
			TDX_3 = tmp3;
			TDX_4 = tmp4;
			TDX_5 = tmp5;
			TDX_6 = tmp6;
			return true;
		}
		else return false;
	}

	void AutolandGuidance::OnSaveState( FILEHANDLE scn ) const
	{
		char cbuf[256];

		oapiWriteScenario_int( scn, "RESET", RESET );

		oapiWriteScenario_int( scn, "SB_FIRSTPASS", SB_FIRSTPASS );
		oapiWriteScenario_int( scn, "SB_MODE", SB_MODE );

		fltrA13->SaveState( cbuf );
		oapiWriteScenario_string( scn, "fltrA13", cbuf );

		oapiWriteScenario_float( scn, "DSBC_SMART", DSBC_SMART );

		sprintf_s( cbuf, 255, "%f %f %f %f %f %f", TDX_1, TDX_2, TDX_3, TDX_4, TDX_5, TDX_6 );
		oapiWriteScenario_string( scn, "TDX", cbuf );
		return;
	}

	void AutolandGuidance::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "V_REF", ILOADs, V_REF );
		return;
	}

	void AutolandGuidance::OnPreStep( double simt, double simdt, double mjd )
	{
		if (ReadCOMPOOL_IS( SCP_TG_END ) == 0) return;

		step += simdt;
		if (step < 0.16) return;

		// read inputs
		PMODE = ReadCOMPOOL_IS( SCP_PMODE );
		FMODE = ReadCOMPOOL_IS( SCP_FMODE );
		H = ReadCOMPOOL_SD( SCP_H );
		H_DOT = ReadCOMPOOL_SD( SCP_HDOT );
		IGS = ReadCOMPOOL_IS( SCP_IGS );
		IGI = ReadCOMPOOL_IS( SCP_IGI );
		V_T = ReadCOMPOOL_SD( SCP_V_T );
		VI = ReadCOMPOOL_SD( SCP_V_I );
		VG = ReadCOMPOOL_SD( SCP_VG );
		X = ReadCOMPOOL_SD( SCP_X );
		Y = ReadCOMPOOL_SD( SCP_Y );
		Y_DOT = ReadCOMPOOL_SD( SCP_YDOT );
		GAMMA = ReadCOMPOOL_SD( SCP_GAMMA );
		FLATTURN = ReadCOMPOOL_IS( SCP_FLATTURN );
		WOWLON = ReadCOMPOOL_IS( SCP_WOWLON );
		FCS_PITCH = ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH );
		FCS_ROLL = ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL );
		WEIGHT = ReadCOMPOOL_SD( SCP_WEIGHT );

		R = ReadCOMPOOL_M( SCP_AL_R, IGI, IGS, 2, 2 );
		X_K = ReadCOMPOOL_M( SCP_X_K, IGI, IGS, 2, 2 );
		H_K = ReadCOMPOOL_M( SCP_H_K, IGI, IGS, 2, 2 );
		X_EXP = ReadCOMPOOL_M( SCP_X_EXP, IGI, IGS, 2, 2 );
		H_DECAY = ReadCOMPOOL_M( SCP_H_DECAY, IGI, IGS, 2, 2 );
		SIGMA = ReadCOMPOOL_SD( SCP_SIGMA );
		GAMMA_REF_1 = ReadCOMPOOL_V( SCP_GAMMA_REF_1, IGS, 2 );
		GAMMA_REF_2 = ReadCOMPOOL_SD( SCP_GAMMA_REF_2 );
		X_ZERO = ReadCOMPOOL_V( SCP_X_ZERO, IGI, 2 );
		X_AIM = ReadCOMPOOL_SD( SCP_X_AIM );
		H_FLARE = ReadCOMPOOL_SD( SCP_H_FLARE );
		H_CLOOP = ReadCOMPOOL_SD( SCP_H_CLOOP );

		ALGEXEC( step/*simdt*/ );

		// write outputs
		WriteCOMPOOL_IS( SCP_PMODE, PMODE );
		WriteCOMPOOL_IS( SCP_FMODE, FMODE );
		WriteCOMPOOL_SD( SCP_NZ_CMD, static_cast<float>(NZ_CMD) );
		WriteCOMPOOL_SD( SCP_PHIC_AL, static_cast<float>(PHIC_AL) );
		WriteCOMPOOL_SD( SCP_RC, static_cast<float>(RC) );
		WriteCOMPOOL_SD( SCP_DSBC_AL, static_cast<float>(DSBC_AL) );
		WriteCOMPOOL_SD( SCP_HERR, static_cast<float>(HERR) );

		step = 0.0;
		return;
	}

	bool AutolandGuidance::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 305) return true;
		else return false;
	}

	void AutolandGuidance::ALGEXEC( double dt )
	{
		if (RESET == 1) ALGINIT();

		ALGREF( dt );

		// transition tests
		switch (PMODE)
		{
			case 1:
				if (fabs( GAMERR ) < 2.0)
				{
					TGMER += dt;
					if ((TGMER >= 4.0) || (fabs( HERR ) < 50.0)) PMODE = 2;
				}
				else TGMER = 0.0;
				// disabled break so it is possible to enter PMODE 3 from PMODE 1
				//break;
			case 2:
				if (H <= H_FLARE) PMODE = 3;
				break;
			case 3:
				switch (FMODE)
				{
					case 1:
						if (H <= H_CLOOP) FMODE = 2;
						break;
					case 2:
						if (X > X_EXP) FMODE = 3;
						break;
					case 3:
						// HACK using newer transition test (no solid data), original test commented below
						//if (((H < H_FF) && (H < ((TAU_TD2 * (H_TD2_DOT - H_DOT)) + H_NO_ACC))) || (H < H_MIN)) PMODE = 4;
						if (((H < H_FF) && (H < ((-5.952308 * H_DOT) - 15.833333))) || (H < H_MIN)) PMODE = 4;
						break;
				}
				break;
		}

		ALGNCZ( dt );
		ALGSBC( dt );
		ALGPHIC();
		return;
	}

	void AutolandGuidance::ALGINIT( void )
	{
		PMODE = 1;
		FMODE = 1;

		RESET = 0;

		TGMER = 0.0;

		SB_FIRSTPASS = 1;

		WriteCOMPOOL_IS( SCP_RETRACT_BF, 1 );// command B/F to trail
		return;
	}

	void AutolandGuidance::ALGREF( double dt )
	{
		double RGA = 0.0;// horizontal distance to X_AIM? [ft]
		double X_0C = 0.0;
		double PSI_COR = 0.0;// angle between centerline and vehicle position, measured from X_AIM? [rad]
		double HERREXP = 0.0;

		switch (PMODE)
		{
			case 1:
				GAMERR = GAMMA_REF_1 - GAMMA;
			case 2:
				RGA = sqrt( pow( X - X_AIM, 2 ) + (Y * Y) );
				PSI_COR = atan2( fabs( Y ), fabs( X - X_AIM ) );
				X_0C = (-X_ZERO + X_AIM) * cos( PSI_COR );
				H_REF = (RGA - X_0C) * tan( -GAMMA_REF_1 * RAD );

				// in theory, the formula below should follow the glide slope
				// the official formulas above (which can't be fully read from documentation) give +/- the same result
				//H_REF = (X - X_ZERO) * tan( GAMMA_REF_1 * RAD );

				H_DOTREF = /*VI*/ReadCOMPOOL_SD( SCP_VE ) * sin( GAMMA_REF_1 * RAD );
				break;
			case 3:
				switch (FMODE)
				{
					case 1:
						// "no closed loop refs"
						return;
					case 2:
						H_REF = H_K - sqrt( (R * R) - pow( X - X_K, 2 ) );

						H_DOTREF = -VG * (X - X_K) / (H_REF - H_K);
						break;
					case 3:
						RGA = sqrt( pow( X - X_AIM, 2 ) + (Y * Y) );
						HERREXP = H_DECAY * exp( (X_EXP - X) / SIGMA );
						H_REF = (RGA * tan( -GAMMA_REF_2 * RAD )) + HERREXP;

						H_DOTREF = VG * tan( GAMMA_REF_2 * RAD ) - ((HERREXP * VG) / SIGMA);
						break;
				}
				break;
			case 4:
				// HDOT ref calculated in ALGNCZ
				break;
		}

		HERR = H_REF - H;
		HDOTER = H_DOTREF - H_DOT;
		//oapiWriteLogV( "%.2f,%d,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f", oapiGetSimTime(), PMODE, FMODE, H, H_REF, HERR, H_DOT, H_DOTREF, HDOTER );
		//sprintf_s( oapiDebugString(), 256, "%d %d  %.2f[%.2f](%.2f) %.2f[%.2f](%.2f)", PMODE, FMODE, H, H_REF, HERR, H_DOT, H_DOTREF, HDOTER );
		return;
	}

	void AutolandGuidance::ALGNCZ( double dt )
	{
		double NZ_C1 = 0.0;
		double NZ_C2H = 0.0;
		double HERRLM = 0.0;// limited HERR [ft]
		double HERILM = 0.0;// limited HERR for integration [ft]
		double NZC = 0.0;// unlimited NZ_CMD
		double V_T_FILT = 0.0;
		double NZ_C3 = 0.0;
		double NZ_C4 = 0.0;
		double GAMMA_AIRDOT_SYNC = 0.0;
		double TGM = 0.0;
		double NZMAX = 0.0;
		double GAMMA_DOT_MAX = 0.0;
		double GAMMA_DOT_LM = 0.0;// limited GAMMA_DOT
		double TTD1 = 0.0;
		double TTD2 = 0.0;// [fps]
		double H_REF_DOT = 0.0;
		double NZ_C1H = 0.0;
		double NZ_C2I = 0.0;// [g]
		double NZ_C1I = 0.0;

		fltrA13->SetGains( 1.0 / ((2.0 / (A13 * dt)) + 1.0), 1.0 / ((2.0 / (A13 * dt)) + 1.0), ((A13 * dt) - 2.0) / (2.0 + (A13 * dt)) );
		V_T_FILT = fltrA13->GetValue( V_T );

		switch (PMODE)
		{
			case 2:
				if (FCS_PITCH == 1)
				{
					HERILM = range( -H_INTMX, HERR, H_INTMX );
					fltrNZ_C2I_12->SetGains( dt * 0.5, dt * 0.5, -1.0 );
					NZ_C2I = fltrNZ_C2I_12->GetValue( HERILM * K_HINT1 );
				}
				else NZ_C2I = 0.0;
			case 1:
				NZ_C1 = HDOTER * (K_HDOT_TC + K_HDOT_SGS);

				HERRLM = range( -H_ERROR_MAX, HERR, H_ERROR_MAX );
				NZ_C2H = HERRLM * (K_H_TC + K_H_SGS);

				NZC = NZ_C1 + NZ_C2H + NZ_C2I;
				break;
			case 3:
				if (FMODE != 1)
				{
					NZ_C1 = HDOTER * K_HDOT_FSGS;

					NZ_C2H = HERR * K_H_FSGS;

					if (FCS_PITCH == 1)
					{
						fltrNZ_C2I_3->SetGains( dt * 0.5, dt * 0.5, -1.0 );
						NZ_C2I = fltrNZ_C2I_3->GetValue( NZ_C2H * K_INT );
					}
					else NZ_C2I = 0.0;

					NZ_C4 = NZ_C1 + NZ_C2H + NZ_C2I;
				}
				else NZ_C4 = 0.0;

				GAMMA_AIRDOT_SYNC = asin( H_DOT / V_T_FILT ) * DEG;

				// HACK disabled integrator feedback, as it tracks pull-up circle better without it
				TGM = (GAMMA_REF_2 - GAMMA_AIRDOT_SYNC/* - GAMMA_C3*/) / TAU_GAMMA;
				NZMAX = V_T_FILT * V_T_FILT / R;
				GAMMA_DOT_MAX = (NZMAX * /*57.3*/DEG) / V_T_FILT;
				GAMMA_DOT_LM = range( -GAMMA_DOT_MAX, TGM, GAMMA_DOT_MAX );

				fltrGAMMA_C3->SetGains( dt * 0.5, dt * 0.5, -1.0 );
				GAMMA_C3 = fltrGAMMA_C3->GetValue( GAMMA_DOT_LM );

				fltrA40->SetGains( 1.0 / ((2.0 / (A40 * dt)) + 1.0), 1.0 / ((2.0 / (A40 * dt)) + 1.0), ((A40 * dt) - 2.0) / (2.0 + (A40 * dt)) );
				NZ_C3 = fltrA40->GetValue( GAMMA_DOT_LM * (V_T_FILT / (/*57.3*/DEG * G * MPS2FPS)) );

				NZC = NZ_C3 + NZ_C4;

				fltrTTD1I->SetInitialValue( H_DOT );// set initial condition for FF

				/*sprintf_s( oapiDebugString(), 256, "%d %d  %.2f[%.2f](%.2f) %.2f[%.2f](%.2f)  %.2f %.2f %.2f %.2f %.2f %.2f  %.2f %.2f %.2f %.2f %.2f %.2f %.2f",
					PMODE, FMODE, H, H_REF, HERR, H_DOT, H_DOTREF, HDOTER, NZ_C1, NZ_C2H, NZ_C2I, NZ_C3, NZ_C4, NZC,
					GAMMA_REF_2, GAMMA_AIRDOT_SYNC, GAMMA_REF_2 - GAMMA_AIRDOT_SYNC, GAMMA_C3, NZMAX, GAMMA_DOT_MAX, GAMMA_DOT_LM );*/
				break;
			case 4:
				TTD1 = (H_TD1_DOT - TTD1I) / TAU_TD1;

				fltrTTD1I->SetGains( dt * 0.5, dt * 0.5, -1.0 );
				TTD1I = fltrTTD1I->GetValue( TTD1 );

				NZ_C3 = TTD1 * K_FLR;

				TTD2 = fabs( H - H_NO_ACC ) / TAU_TD2;

				fltrA3_ALGNCZ->SetGains( 1.0 / ((2.0 / (A3 * dt)) + 1.0), 1.0 / ((2.0 / (A3 * dt)) + 1.0), ((A3 * dt) - 2.0) / (2.0 + (A3 * dt)) );
				H_REF_DOT = fltrA3_ALGNCZ->GetValue( H_TD2_DOT - TTD2 );

				NZ_C1H = (H_REF_DOT - H_DOT) * K_HDOT;

				fltrNZ_C1I->SetGains( dt * 0.5, dt * 0.5, -1.0 );
				NZ_C1I = fltrNZ_C1I->GetValue( NZ_C1H * K_IFLR );

				NZC = NZ_C3 + NZ_C1H + NZ_C1I;
				break;
		}

		// TODO NZ predictor

		NZ_CMD = range( -NZC_LIM, NZC, NZC_LIM );
		return;
	}

	void AutolandGuidance::ALGSBC( double dt )
	{
		double DSBC = 0.0;// unlimited DSBC_AL [deg]
		double SBLIM = SB_MAX;// limit for DSBC [deg]
		double V_ERROR = 0.0;// EAS error [fps]
		double DELTA_SBE = 0.0;// [deg]
		double EAS_FILT = 0.0;// [fps]
		double TDX = 0.0;// predicted touchdown x position [ft]
		double WINDSPEED = 0.0;// filtered wind speed [kt]

		if (SB_FIRSTPASS == 1)
		{
			SB_MODE = 1;
			SB_SEL = ReadCOMPOOL_IS( SCP_SB_SEL );
			fltrA14->SetInitialValue( VI );
			fltrA14_WINDSPEED->SetInitialValue( ReadCOMPOOL_SD( SCP_VE ) - EAS_FILT );

			DSBC_SMART = 0.0;
			TDX_1 = 0.0;
			TDX_2 = 0.0;
			TDX_3 = 0.0;
			TDX_4 = 0.0;
			TDX_5 = 0.0;
			TDX_6 = 0.0;

			SB2_COUNT = 0;

			SB_FIRSTPASS = 0;
		}

		// filter EAS
		fltrA14->SetGains( 1.0 / ((2.0 / (A14 * dt)) + 1.0), 1.0 / ((2.0 / (A14 * dt)) + 1.0), ((A14 * dt) - 2.0) / (2.0 + (A14 * dt)) );
		EAS_FILT = fltrA14->GetValue( VI );

		// filter wind speed
		fltrA14_WINDSPEED->SetGains( 1.0 / ((2.0 / (A14 * dt)) + 1.0), 1.0 / ((2.0 / (A14 * dt)) + 1.0), ((A14 * dt) - 2.0) / (2.0 + (A14 * dt)) );
		WINDSPEED = fltrA14_WINDSPEED->GetValue( V_T - ReadCOMPOOL_SD( SCP_VE ) ) * (MPS2KTS / MPS2FPS);

		switch (SB_MODE)
		{
			case 1:// track V_REF
				V_ERROR = EAS_FILT - V_REF;

				// exit condition
				if (H <= H_SB2)
				{
					// calc predicted TD position
					// 1) wind speed
					TDX_1 = 85.714286 * WINDSPEED;

					// 2) velocity error
					TDX_2 = 74.074074 * V_ERROR * (MPS2KTS / MPS2FPS);

					// 3) density altitude
					double sigma = pow( EAS_FILT / V_T, 2 );
					double DensityAltitude = CalcDensityAltitude( sigma );
					TDX_3 = ((DensityAltitude - H) * 0.233333) - 466.666667;

					// 4) vehicle weight
					if (WEIGHT <= (200000.0 * LBS2SL)) TDX_4 = (WEIGHT * 0.045 / LBS2SL) - 8600.0;
					else if (WEIGHT <= (220000.0 * LBS2SL)) TDX_4 = (WEIGHT * 0.041 / LBS2SL) - 7800.0;
					else if (WEIGHT <= (240000.0 * LBS2SL)) TDX_4 = (WEIGHT * 0.035 / LBS2SL) - 7700.0;
					else /*if (WEIGHT <= 260000.0)*/ TDX_4 = (WEIGHT * 0.0275 / LBS2SL) - 5900.0;

					// 5) close-in aimpoint
					if (IGI == 2) TDX_5 = 1000.0;
					else TDX_5 = 0.0;

					// 6) SB option
					if (SB_SEL == 2) TDX_6 = 1000.0;
					else if (SB_SEL == 3) TDX_6 = 1500.0;
					else TDX_6 = 0.0;

					TDX = TDX_1 + TDX_2 + TDX_3 + TDX_4 + TDX_5 + TDX_6;

					// calc DSBC_SMART
					if (IGS == 1) DSBC_SMART = (TDX * 0.0124776) + 15.0;// light
					else DSBC_SMART = (TDX * 0.013376) + 15.0;// heavy

					DSBC = DSBC_SMART;
					if (1) SBLIM = SB_LIM2_NOM;// TODO TAL

					SB_MODE = 2;
				}
				else
				{
					// calc OGS SB position
					DELTA_SBE = K_SB * V_ERROR;
					DSBC = DELTA_SBE + SB_REF;
				}
				break;
			case 2:
				intWINDSPEED->SetGains( dt * 0.5, dt * 0.5, -1.0 );
				WINDSPEED = intWINDSPEED->GetValue( WINDSPEED );
				SB2_COUNT++;

				// exit condition
				if (H <= H_SB3)
				{
					// recalc TDX_1 and TDX_3
					TDX_1 = 85.714286 * (WINDSPEED / SB2_COUNT);

					double sigma = pow( EAS_FILT / V_T, 2 );
					double DensityAltitude = CalcDensityAltitude( sigma );
					TDX_3 = ((DensityAltitude - H) * 0.233333) - 466.666667;

					TDX = TDX_1 + TDX_2 + TDX_3 + TDX_4 + TDX_5 + TDX_6;

					if (IGS == 1) DSBC_SMART = (TDX * 0.0124776) + 15.0;// light
					else DSBC_SMART = (TDX * 0.013376) + 15.0;// heavy

					if (SB_SEL == 1) SBLIM = SB_LIM3_NOM;
					else SBLIM = SB_LIM3_SHRTELS;

					SB_MODE = 3;
				}
				else
				{
					if (1) SBLIM = SB_LIM2_NOM;// TODO TAL
				}

				DSBC = DSBC_SMART;
				break;
			case 3:
				if (WOWLON == 0)
				{
					// pre WOWLON
					DSBC = DSBC_SMART;

					if (SB_SEL == 1) SBLIM = SB_LIM3_NOM;
					else SBLIM = SB_LIM3_SHRTELS;
				}
				else
				{
					// post WOWLON
					DSBC = SB_MAX;
					SBLIM = SB_MAX;
				}
				break;
		}

		DSBC_AL = range( 0.0, DSBC, SBLIM );
		return;
	}

	void AutolandGuidance::ALGPHIC( void )
	{
		double PHI_FI = 0.0;// [deg]
		double Y_LM = 0.0;// limited Y [ft]
		double PHIC_UL = 0.0;// unlimited roll command [deg]
		double PHI_MAX = 0.0;// roll command limit [deg]
		double PHI_LM = 0.0;// limited roll command [deg]

		Y_LM = range( -Y_LIMIT, Y, Y_LIMIT );
		// HACK skipped integral loop (not used)
		PHI_FI = (-(Y_DOT * K_YDOT) - Y_LM) * K_Y1;
		PHIC_UL = PHI_FI;// HACK skipped fader (not used)

		if (FCS_ROLL == 2) PHI_MAX = PHI_M3;
		else if (H > H_WL) PHI_MAX = PHI_M1;
		else PHI_MAX = PHI_M2;
		PHI_LM = range( -PHI_MAX, PHIC_UL, PHI_MAX );

		if (FLATTURN == 0) PHIC_AL = PHI_LM;
		else PHIC_AL = 0.0;

		if (WOWLON == 1) RC = PHI_LM * K_R2;// HACK using only WOWLON logic
		else RC = 0.0;
		return;
	}

	double AutolandGuidance::CalcDensityAltitude( double sigma ) const
	{
		unsigned int idx = GetLowerIndex( SA1962_Sigma, 7, sigma );

		return linterp( SA1962_Sigma[idx], SA1962_Altitude[idx], SA1962_Sigma[idx + 1], SA1962_Altitude[idx + 1], sigma );
	}
};
