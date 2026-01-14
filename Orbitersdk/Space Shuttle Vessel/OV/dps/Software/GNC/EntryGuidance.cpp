/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/06/26   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/02   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/09/14   GLS
2022/09/29   GLS
2022/12/01   indy91
2023/01/02   GLS
2025/07/20   GLS
2025/01/14   GLS
********************************************/
#include "EntryGuidance.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	/////// Entry (from 80-FM-24, JSC-16516) ///////

	// convertion factor from feet to nautical miles
	constexpr double CNMFS = 1.645788e-4;// [NM/ft]


	// K-Loads
	constexpr double E1 = 0.01;// Minimum value of D23 (V97U0228C) [fps^2]
	constexpr double V_TAEM = 2500.0;// Reference velocity at entry–TAEM interface (V97U0420C) [fps]
	constexpr double VSAT = 25766.2;// Local circular orbit velocity (V97U0439C) [fp]

	EntryGuidance::EntryGuidance( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "EntryGuidance" )
	{
		START = 0;
		EG_END = 0;
		RDTREF = 0.0;
		ACMD1 = 0.0;
		DZOLD = 0.0;
		ALDREF = 0.0;
		DRDD = 0.0;
		step = 1.92;
		YL = 0.0;

		// I-LOADs init
		CALP0[0] = 5.034479;
		CALP0[1] = -13.81545;
		CALP0[2] = 40.0;
		CALP0[3] = 40.0;
		CALP0[4] = 40.0;
		CALP0[5] = 40.0;
		CALP0[6] = 40.0;
		CALP0[7] = 40.0;
		CALP0[8] = 40.0;
		CALP0[9] = 40.0;
		CALP1[0] = 0.003586207;
		CALP1[1] = 0.008786196;
		CALP1[2] = 0.0;
		CALP1[3] = 0.0;
		CALP1[4] = 0.0;
		CALP1[5] = 0.0;
		CALP1[6] = 0.0;
		CALP1[7] = 0.0;
		CALP1[8] = 0.0;
		CALP1[9] = 0.0;
		CALP2[0] = 0.0;
		CALP2[1] = -3.586207e-7;
		CALP2[2] = 0.0;
		CALP2[3] = 0.0;
		CALP2[4] = 0.0;
		CALP2[5] = 0.0;
		CALP2[6] = 0.0;
		CALP2[7] = 0.0;
		CALP2[8] = 0.0;
		CALP2[9] = 0.0;
		VALP[0] = 7250.0;
		VALP[1] = 12250.0;
		VALP[2] = 14500.0;
		VALP[3] = 14500.0;
		VALP[4] = 14500.0;
		VALP[5] = 14500.0;
		VALP[6] = 14500.0;
		VALP[7] = 14500.0;
		VALP[8] = 14500.0;
		NALP = 9;
		ACLAM1 = 9.352966;
		ACLAM2 = 0.003058794;
		ACLIM1 = 37.0;
		ACLIM2 = 0.0;
		ACLIM3 = 7.6666667;
		ACLIM4 = 0.00223333;
		return;
	}

	EntryGuidance::~EntryGuidance( void )
	{
		return;
	}

	bool EntryGuidance::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "START", 5 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 2) START = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "IDBCHG", 6 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) IDBCHG = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "RPT", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			RPT = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "IALP", 4 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			IALP = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "ITRAN", 5 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			ITRAN = (tmp != 0);
			return true;
		}
		else if (!_strnicmp( keyword, "ICT", 3 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			ICT = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "T2", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			T2 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "T2OLD", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			T2OLD = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DREFP", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DREFP = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VQ2", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VQ2 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "RK2ROL", 6 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			RK2ROL = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "RK2RLP", 6 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			RK2RLP = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "LMFLG", 5 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			LMFLG = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VTRB", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VTRB = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DDP", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DDP = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VSAT2", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VSAT2 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VSIT2", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VSIT2 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VCG", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VCG = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "D23", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			D23 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DX_0", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DX[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DX_1", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DX[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "V0_0", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			V0[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "V0_1", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			V0[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VX_0", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VX[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VX_1", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VX[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VF_0", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VF[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "A_0", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			A[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "A_1", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			A[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CQ1_0", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CQ1[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CQ1_1", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CQ1[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CQ2_0", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CQ2[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CQ2_1", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CQ2[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CQ3_0", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CQ3[0] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "CQ3_1", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			CQ3[1] = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "VB2", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			VB2 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "RCG1", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			RCG1 = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DZOLD", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DZOLD = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "ACMD1", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			ACMD1 = tmp;
			return true;
		}
		else return false;
	}

	void EntryGuidance::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "START", START );
		oapiWriteScenario_int( scn, "IDBCHG", IDBCHG );
		oapiWriteScenario_float( scn, "RPT", RPT );
		oapiWriteScenario_int( scn, "IALP", IALP );
		oapiWriteScenario_int( scn, "ITRAN", ITRAN ? 1 : 0 );
		oapiWriteScenario_int( scn, "ICT", ICT );
		oapiWriteScenario_float( scn, "T2", T2 );
		oapiWriteScenario_float( scn, "T2OLD", T2OLD );
		oapiWriteScenario_float( scn, "DREFP", DREFP );
		oapiWriteScenario_float( scn, "VQ2", VQ2 );
		oapiWriteScenario_float( scn, "RK2ROL", RK2ROL );
		oapiWriteScenario_float( scn, "RK2RLP", RK2RLP );
		oapiWriteScenario_int( scn, "LMFLG", LMFLG );
		oapiWriteScenario_float( scn, "VTRB", VTRB );
		oapiWriteScenario_float( scn, "DDP", DDP );
		oapiWriteScenario_float( scn, "VSAT2", VSAT2 );
		oapiWriteScenario_float( scn, "VSIT2", VSIT2 );
		oapiWriteScenario_float( scn, "VCG", VCG );
		oapiWriteScenario_float( scn, "D23", D23 );
		oapiWriteScenario_float( scn, "DX_0", DX[0] );
		oapiWriteScenario_float( scn, "DX_1", DX[1] );
		oapiWriteScenario_float( scn, "V0_0", V0[0] );
		oapiWriteScenario_float( scn, "V0_1", V0[1] );
		oapiWriteScenario_float( scn, "VX_0", VX[0] );
		oapiWriteScenario_float( scn, "VX_1", VX[1] );
		oapiWriteScenario_float( scn, "VF_0", VF[0] );
		oapiWriteScenario_float( scn, "A_0", A[0] );
		oapiWriteScenario_float( scn, "A_1", A[1] );
		oapiWriteScenario_float( scn, "CQ1_0", CQ1[0] );
		oapiWriteScenario_float( scn, "CQ1_1", CQ1[1] );
		oapiWriteScenario_float( scn, "CQ2_0", CQ2[0] );
		oapiWriteScenario_float( scn, "CQ2_1", CQ2[1] );
		oapiWriteScenario_float( scn, "CQ3_0", CQ3[0] );
		oapiWriteScenario_float( scn, "CQ3_1", CQ3[1] );
		oapiWriteScenario_float( scn, "VB2", VB2 );
		oapiWriteScenario_float( scn, "RCG1", RCG1 );
		oapiWriteScenario_float( scn, "DZOLD", DZOLD );
		oapiWriteScenario_float( scn, "ACMD1", ACMD1 );
		return;
	}

	void EntryGuidance::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "CALP0", ILOADs, 10, CALP0 );
		GetValILOAD( "CALP1", ILOADs, 10, CALP1 );
		GetValILOAD( "CALP2", ILOADs, 10, CALP2 );
		GetValILOAD( "VALP", ILOADs, 9, VALP );
		GetValILOAD( "NALP", ILOADs, NALP );
		GetValILOAD( "ACLAM1", ILOADs, ACLAM1 );
		GetValILOAD( "ACLAM2", ILOADs, ACLAM2 );
		GetValILOAD( "ACLIM1", ILOADs, ACLIM1 );
		GetValILOAD( "ACLIM2", ILOADs, ACLIM2 );
		GetValILOAD( "ACLIM3", ILOADs, ACLIM3 );
		GetValILOAD( "ACLIM4", ILOADs, ACLIM4 );
		return;
	}

	void EntryGuidance::OnPreStep( double simt, double simdt, double mjd )
	{
		step += simdt;
		if (step < 1.92) return;

		ALPHA = ReadCOMPOOL_SS( SCP_ALPHA_N );
		ROLL = ReadCOMPOOL_SS( SCP_PHI );
		TRANGE = ReadCOMPOOL_SS( SCP_RNG_TO_RW_THRESH );
		VE = ReadCOMPOOL_SS( SCP_REL_VEL_MAG );
		VI = ReadCOMPOOL_SS( SCP_V_MAG );
		XLFAC = ReadCOMPOOL_SS( SCP_LOAD_TOTAL );
		DRAG = ReadCOMPOOL_SS( SCP_ACC_DRAG );
		DELAZ = ReadCOMPOOL_SS( SCP_DELAZ );
		HLS = ReadCOMPOOL_SD( SCP_ALT_WHEELS );
		LOD = ReadCOMPOOL_SS( SCP_LOD );
		RDOT = ReadCOMPOOL_SS( SCP_H_DOT_ELLIPSOID );
		DLRDOT = ReadCOMPOOL_SS( SCP_DLRDOT );
		ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );

		EGEXEC( step/*simdt*/ );

		//sprintf_s( oapiDebugString(), 256, "ISLECT%d (DRAG - DREFP)%.3f DRAG%.3f DREFP%.3f ACLAM%.3f ACLIM%.3f ACMD1%.3f ALPCMD%.3f", ISLECT, DRAG - DREFP, DRAG, DREFP, ACLAM, ACLIM, ACMD1, ALPCMD );

		// ROLL REF status
		double ROLLREFLIM = 0.0;
		if (VE >= 9500.0) ROLLREFLIM = 37.0;
		else if (VE >= 4000.0) ROLLREFLIM = 20.0;
		else  ROLLREFLIM = -5.0;
		WriteCOMPOOL_IS( SCP_REF_ROL_STAT, (fabs( ROLLC[2] ) < ROLLREFLIM) ? 1 : 0 );


		WriteCOMPOOL_SS( SCP_ALPCMD, static_cast<float>(ALPCMD) );
		WriteCOMPOOL_SS( SCP_DREFP, static_cast<float>(DREFP) );
		WriteCOMPOOL_SS( SCP_ROLLCMD, static_cast<float>(ROLLC[0]) );
		WriteCOMPOOL_SS( SCP_ROLLREF, static_cast<float>(ROLLC[2]) );
		WriteCOMPOOL_SS( SCP_RDTREF, static_cast<float>(RDTREF) );
		WriteCOMPOOL_SS( SCP_DRDD, static_cast<float>(DRDD) );
		WriteCOMPOOL_SS( SCP_DLRDOT, static_cast<float>(DLRDOT) );
		WriteCOMPOOL_SS( SCP_YL, static_cast<float>(YL) );
		WriteCOMPOOL_SS( SCP_ACMD1, static_cast<float>(ACMD1) );
		WriteCOMPOOL_IS( SCP_ISLECT, ISLECT );
		WriteCOMPOOL_IS( SCP_EG_END, EG_END );

		step = 0.0;
		return;
	}

	bool EntryGuidance::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 304) return true;
		else return false;
	}

	void EntryGuidance::EGEXEC( double dt )
	{
		EGSCALHT();

		if (START == 0) EGINIT();

		EGCOMN( dt );

		// make transition tests
		if ((ISLECT == 1) && (XLFAC >= ReadCOMPOOL_SS( SCP_ASTART )))
		{
			ISLECT = 2;
			//DTEGD = 1.92;// HACK replaced fixed cycle length for dt
			if (VE < ReadCOMPOOL_SS( SCP_VTRAN )) ISLECT = 5;
		}

		if ((ISLECT == 2) && (VE < ReadCOMPOOL_SS( SCP_VB1 ))) ISLECT = 3;

		if (((ISLECT == 2) || (ISLECT == 3)) && (T2 > ReadCOMPOOL_SS( SCP_ALFM ))) ISLECT = 4;

		if ((ISLECT != 1) && (VE < V_TAEM)) EG_END = 1;

		switch (ISLECT)
		{
			case 1:
				// compute vertica (L/D) during preentry phase
				EGPEP();
				break;
			case 2:
				// compute reference parameters during temperature control phase
				EGRP();
				EGREF();
				break;
			case 3:
				// compute reference parameters during equilibrium glide phase
				EGRP();
				EGREF();
				break;
			case 4:
				// compute reference parameters during constant drag phase
				EGREF4();
				break;
			case 5:
				// compute reference parameters during transition phase
				EGTRAN();
				break;
		}

		// compute angle of attack command
		EGALPCMD( dt );

		// compute vertical L/D command following preentry phase
		if (ISLECT > 1)
		{
			EGGNSLCT();
			EGLODVCMD();
		}

		// compute roll command
		EGROLCMD();

		// make transition tests
		switch (ISLECT)
		{
			case 1:
				break;
			case 2:
				if ((VE < ReadCOMPOOL_SS( SCP_VA )) && (DREFP < DREFP3)) ISLECT = 3;
				if ((VE < (VCG + ReadCOMPOOL_SS( SCP_DELV ))) && (DREFP > DREFP4)) ISLECT = 4;
				break;
			case 3:
				if ((VE < (VCG + ReadCOMPOOL_SS( SCP_DELV ))) && (DREFP > DREFP4)) ISLECT = 4;
				if ((VE < (ReadCOMPOOL_SS( SCP_VTRAN ) + ReadCOMPOOL_SS( SCP_DELV ))) && (DREFP > DREFP5) && (VCG < ReadCOMPOOL_SS( SCP_VTRAN ))) ISLECT = 5;
				break;
			case 4:
				if ((VE < (ReadCOMPOOL_SS( SCP_VTRAN ) + ReadCOMPOOL_SS( SCP_DELV ))) && (DREFP > DREFP5)) ISLECT = 5;
				break;
			/*case 5:
				break;*/
		}
		return;
	}

	void EntryGuidance::EGSCALHT( void )
	{
		// compute altitude scale height (HS)
		if (VE < ReadCOMPOOL_SS( SCP_VHS1 )) HS = ReadCOMPOOL_SS( SCP_HS01 ) + (ReadCOMPOOL_SS( SCP_HS11 ) * VE);
		else
		{
			if (VE < ReadCOMPOOL_SS( SCP_VHS2 )) HS = ReadCOMPOOL_SS( SCP_HS02 );
			else HS = ReadCOMPOOL_SS( SCP_HS03 ) + (ReadCOMPOOL_SS( SCP_HS13 ) * VE);
		}

		if (HS < ReadCOMPOOL_SS( SCP_HSMIN )) HS = ReadCOMPOOL_SS( SCP_HSMIN );
		return;
	}

	void EntryGuidance::EGINIT( void )
	{
		// initialize variables and flags
		//CZOLD = 0.0;
		//IVRR = 0;
		ITRAN = false;
		ISLECT = 1;
		ICT = 0;
		IDBCHG = 0;
		T2 = 0.0;
		DREFP = 0.0;
		VQ2 = ReadCOMPOOL_SS( SCP_VQ ) * ReadCOMPOOL_SS( SCP_VQ );
		RK2ROL = -sign( DELAZ );
		DLRDOT = 0.0;
		LMFLG = 0;
		VTRB = 60000.0;
		DDP = 0.0;
		RK2RLP = RK2ROL;

		// compute desired transition range (RPT)
		RPT = (-(((ReadCOMPOOL_SS( SCP_ETRAN ) - ReadCOMPOOL_SS( SCP_EEF4 )) * log( ReadCOMPOOL_SS( SCP_DF ) / ReadCOMPOOL_SS( SCP_ALFM ) ) / (ReadCOMPOOL_SS( SCP_ALFM ) - ReadCOMPOOL_SS( SCP_DF ))) + (((ReadCOMPOOL_SS( SCP_VTRAN ) * ReadCOMPOOL_SS( SCP_VTRAN )) - VQ2) / (2.0 * ReadCOMPOOL_SS( SCP_ALFM )))) * CNMFS) + ReadCOMPOOL_SS( SCP_RPT1 );

		VSAT2 = VSAT * VSAT;
		VSIT2 = ReadCOMPOOL_SS( SCP_VS1 ) * ReadCOMPOOL_SS( SCP_VS1 );
		VCG = ReadCOMPOOL_SS( SCP_VQ );
		D23 = ReadCOMPOOL_SS( SCP_D230 );
		DX[0] = 1.0;

		V0[0] = ReadCOMPOOL_SS( SCP_VB1 );
		VX[0] = ReadCOMPOOL_SS( SCP_VA );
		VF[0] = ReadCOMPOOL_SS( SCP_VA1 );
		A[0] = ReadCOMPOOL_SS( SCP_AK );
		V0[1] = ReadCOMPOOL_SS( SCP_VA1 );
		VX[1] = ReadCOMPOOL_SS( SCP_VA2 );
		A[1] = ReadCOMPOOL_SS( SCP_AK1 );
		VB2 = ReadCOMPOOL_SS( SCP_VB1 ) * ReadCOMPOOL_SS( SCP_VB1 );

		// compute component of constant drag phase range (RCG)
		RCG1 = CNMFS * (VSIT2 - VQ2) / (2.0 * ReadCOMPOOL_SS( SCP_ALFM ));

		IALP = NALP;
		START = 1;
		return;
	}

	void EntryGuidance::EGCOMN( double dt )
	{
		double RDTRFT = 0.0;// [fps]

		// compute common variables
		XLOD = max(LOD, ReadCOMPOOL_SS( SCP_LODMIN ));
		T1 = (G * MPS2FPS) * (1.0 - ((VI * VI) / VSAT2));
		T2OLD = T2;
		VE2 = VE * VE;
		EEF = ((G * MPS2FPS) * HLS) + (VE2 / 2.0);
		EOWD = EEF / (G * MPS2FPS);
		CAG = (2.0 * (G * MPS2FPS) * HS) + VE2;

		if (ISLECT < 5)
		{
			T2 = CNMFS * (VE2 - VQ2) / (2.0 * (TRANGE - RPT));
			T2DOT = (T2 - T2OLD) / dt/*DTEGD*/;// HACK replaced fixed cycle length for dt

			if (VE < (ReadCOMPOOL_SS( SCP_VTRAN ) + ReadCOMPOOL_SS( SCP_DELV )))
			{
				C1 = (T2 - ReadCOMPOOL_SS( SCP_DF )) / (ReadCOMPOOL_SS( SCP_ETRAN ) - ReadCOMPOOL_SS( SCP_EEF4 ));
				RDTRFT = -((C1 * (((G * MPS2FPS) * HLS) - ReadCOMPOOL_SS( SCP_EEF4 ))) + ReadCOMPOOL_SS( SCP_DF )) * 2.0 * VE * HS / CAG;
				DREFP5 = ReadCOMPOOL_SS( SCP_DF ) + ((EEF - ReadCOMPOOL_SS( SCP_EEF4 )) * C1) + (ReadCOMPOOL_SS( SCP_GS4 ) * (RDTREF - RDTRFT));
			}
		}
		return;
	}

	void EntryGuidance::EGPEP( void )
	{
		// compute vertical L/D during preentry phase
		LODX = XLOD * cos( ReadCOMPOOL_SS( SCP_PREBNK ) * RAD );
		LODV = LODX;
		return;
	}

	void EntryGuidance::EGRP( void )
	{
		unsigned short K = 0;
		double D23L = 0.0;// [fps^2]
		double R23 = 0.0;// [NM]

		// compute reference parameters for temperature control and equilibrium glide phases (ISLECT = 2 or 3)
		if (VE > ReadCOMPOOL_SS( SCP_VA1 ))
		{
			K = 2;
			N = 2;
		}
		else
		{
			K = 1;
			N = 1;
			RF[1] = 0.0;
		}

		VF[N - 1] = VE;

		if (START == 1)
		{
			K = 1;
			START = 2;

			for (unsigned short i = 0; i <= 1; i++)
			{
				if (i == 1) DX[1] = CQ1[0] + (ReadCOMPOOL_SS( SCP_VA1 ) * (CQ2[0] + (CQ3[0] * ReadCOMPOOL_SS( SCP_VA1 ))));

				CQ3[i] = -A[i] * DX[i] / (2.0 * (VX[i] - V0[i]) * V0[i]);
				CQ2[i] = -2.0 * VX[i] * CQ3[i];
				CQ1[i] = DX[i] - (V0[i] * (CQ2[i] + (CQ3[i] * V0[i])));
			}
		}

		for (unsigned short i = K; i <= N; i++)
		{
			if (VE < V0[i - 1]) RF[i - 1] = 0.0;
			else
			{
				V[0] = ((8.0 * V0[i - 1]) + VF[i - 1]) / 9.0;
				V[1] = (V0[i - 1] + VF[i - 1]) / 2.0;
				V[2] = V0[i - 1] + VF[i - 1] - V[0];

				for (unsigned short j = 0; j <= 2; j++) Q[j] = (CQ1[i - 1] / V[j]) + CQ2[i - 1] + (CQ3[i - 1] * V[j]);

				RF[i - 1] = ((27.0 / Q[0]) + (44.0 / Q[1]) + (27.0 / Q[2])) * (VF[i - 1] - V0[i - 1]) / 98.0;
			}
		}

		RFF1 = CNMFS * (RF[0] + RF[1]);

		// update reference drag level (D23) at VB1
		if ((T2DOT > ReadCOMPOOL_SS( SCP_DT2MIN )) || (VE > (VCG + ReadCOMPOOL_SS( SCP_DELV ))))
		{
			if (VE < ReadCOMPOOL_SS( SCP_VB1 )) VB2 = VE2;

			VCG = ReadCOMPOOL_SS( SCP_VQ );
			D23L = ReadCOMPOOL_SS( SCP_ALFM ) * (VSIT2 - VB2) / (VSIT2 - VQ2);

			if (D23 > D23L) VCG = sqrt( VSIT2 - (D23L * (VSIT2 - VQ2) / D23) );
			else D23 = D23L;

			A2 = CNMFS * (VSIT2 - VB2) / 2.0;
			REQ1 = A2 * log( ReadCOMPOOL_SS( SCP_ALFM ) / D23 );
			RCG = RCG1 - (A2 / D23);
			R231 = RFF1 + REQ1;
			R23 = TRANGE - RCG - RPT;
			D231 = R231 / R23;
			DRDD = -R23 / D231;

			if (D231 >= D23L) D23 = D231 + (A2 * pow( 1.0 - (D23 / D231), 2.0 ) / (2.0 * R23));
			else D23 = max(D231, E1);
		}
		return;
	}

	void EntryGuidance::EGREF( void )
	{
		// compute reference parameters for temperature control and equilibrium glide phases (ISLECT = 2 or 3)

		// during temperature control phase
		if (VE > ReadCOMPOOL_SS( SCP_VB1 ))
		{
			for (unsigned short i = 1; i <= N; i++)
			{
				DREF[i - 1] = CQ1[i - 1] + (VE * (CQ2[i - 1] + (CQ3[i - 1] * VE)));
				HDTRF[i - 1] = -HS * ((2.0 * DREF[i - 1] / VE) - CQ2[i - 1] - (2.0 * CQ3[i - 1] * VE));
			}

			if (VE > ReadCOMPOOL_SS( SCP_VA1 ))
			{
				DRF = DREF[1] - DREF[0];
				DRF = DRF * (DRF + ((HDTRF[0] - HDTRF[1]) * ReadCOMPOOL_SS( SCP_GS1 )));

				if (DRF < 0.0) N = 1;
			}

			DREFP = D23 * DREF[N - 1];
			RDTREF = D23 * HDTRF[N - 1];
			C2 = CQ2[N - 1] * D23;
		}

		// during equilibrium glide phase
		if (VE < ReadCOMPOOL_SS( SCP_VA ))
		{
			ALDCO = (1.0 - (VB2 / VSIT2)) / D23;
			DREFP1 = (1.0 - (VE2 / VSIT2)) / ALDCO;
			RDTRF1 = (-2.0 * HS) / (VE * ALDCO);
			DREFP3 = DREFP1 + (ReadCOMPOOL_SS( SCP_GS2 ) * (RDTREF - RDTRF1));

			if ((DREFP3 > DREFP) || (VE < ReadCOMPOOL_SS( SCP_VB1 )))
			{
				DREFP = DREFP1;
				RDTREF = RDTRF1;
				C2 = 0.0;
			}
		}

		// compute test value for DREFP for transition to constant drag phase (ISLECT = 4)
		DREFP4 = (ReadCOMPOOL_SS( SCP_GS3 ) * (RDTREF + (2.0 * HS * T2 / VE))) + T2;
		ITRAN = true;
		return;
	}

	void EntryGuidance::EGREF4( void )
	{
		// compute reference parameters during constant drag phase
		DREFP = T2;
		RDTREF = -2.0 * HS * T2 / VE;
		DRDD = -(TRANGE - RPT) / T2;
		C2 = 0.0;
		ITRAN = true;
		return;
	}

	void EntryGuidance::EGTRAN( void )
	{
		// compute reference parameters during transition phase
		if (ITRAN == false)
		{
			DREFP = ReadCOMPOOL_SS( SCP_ALFM );
			ITRAN = true;
		}

		DREFPT = DREFP - ReadCOMPOOL_SS( SCP_DF );

		if (fabs( DREFP ) < E1) DREFP = ReadCOMPOOL_SS( SCP_DF ) + (E1 * sign( DREFPT ));

		if (DREFP < E1) DREFP = E1;

		DREFPT = DREFP - ReadCOMPOOL_SS( SCP_DF );
		C1 = DREFPT / (EEF - ReadCOMPOOL_SS( SCP_EEF4 ));
		RER1 = CNMFS * log( DREFP / ReadCOMPOOL_SS( SCP_DF ) ) / C1;
		DRDD = min((CNMFS / (C1 * DREFP)) - (RER1 / DREFPT), ReadCOMPOOL_SS( SCP_DRDDL ));
		DREFP = DREFP + ((TRANGE - RER1 - ReadCOMPOOL_SS( SCP_RPT1 )) / DRDD);
		DLIM = ReadCOMPOOL_SS( SCP_ALIM ) * DRAG / XLFAC;

		if (DREFP > DLIM)
		{
			DREFP = DLIM;
			C1 = 0.0;
		}

		if (DREFP < E1) DREFP = E1;

		RDTREF = -HS * VE * ((2.0 * DREFP) - (C1 * VE2)) / CAG;
		C2 = 4.0 * VE * DREFP * (1.0 - pow( VE2 / CAG, 2.0 )) / CAG;
		return;
	}

	void EntryGuidance::EGALPCMD( double dt )
	{
		unsigned short J = 0;

		// compute angle of attack command
		while ((VE < VALP[IALP - 1]) && (IALP > 0)) IALP -= 1;

		J = IALP + 1;
		ALPCMD = CALP0[J - 1] + (VE * (CALP1[J - 1] + (CALP2[J - 1] * VE)));

		ALPDOT = (ALPCMD - ACMD1) / dt;
		ACMD1 = ALPCMD;
		return;
	}

	void EntryGuidance::EGGNSLCT( void )
	{
		// compute controller gains
		C16 = ReadCOMPOOL_ASS( SCP_CT16, 1, 3 ) * pow( DRAG, ReadCOMPOOL_ASS( SCP_CT16, 2, 3 ) );

		if (VE < ReadCOMPOOL_SS( SCP_VC16 )) C16 = C16 + (ReadCOMPOOL_ASS( SCP_CT16, 3, 3 ) * (DRAG - DREFP));

		C16 = midval( C16, ReadCOMPOOL_SS( SCP_CT16MN ), ReadCOMPOOL_SS( SCP_CT16MX ) );

		if (ICT == 1) WriteCOMPOOL_SS( SCP_CT17MN, ReadCOMPOOL_SS( SCP_CT17M2 ) );

		C17 = midval( ReadCOMPOOL_ASS( SCP_CT17, 1, 2 ) * pow( DRAG, ReadCOMPOOL_ASS( SCP_CT17, 2, 2 ) ), ReadCOMPOOL_SS( SCP_CT17MN ), ReadCOMPOOL_SS( SCP_CT17MX ) );

		if (ICT == 1) C17 = ReadCOMPOOL_SS( SCP_C17MP ) * C17;
		return;
	}

	void EntryGuidance::EGLODVCMD( void )
	{
		double A44 = 0.0;// [1]
		double CDCAL = 0.0;// [1]
		double CDDOTC = 0.0;
		double RDTRF = 0.0;// [fps]

		// compute vertical L/D command (LODV)
		A44 = exp( -(VE - ReadCOMPOOL_SS( SCP_CDDOT1 )) / ReadCOMPOOL_SS( SCP_CDDOT2 ) );
		CDCAL = ReadCOMPOOL_SS( SCP_CDDOT4 ) + (ALPCMD * (ReadCOMPOOL_SS( SCP_CDDOT5 ) + (ReadCOMPOOL_SS( SCP_CDDOT6 ) * ALPCMD))) + (ReadCOMPOOL_SS( SCP_CDDOT3 ) * A44);
		CDDOTC = (ReadCOMPOOL_SS( SCP_CDDOT7 ) * (DRAG + (G * MPS2FPS * RDOT / VE)) * A44) + (ALPDOT * ((ReadCOMPOOL_SS( SCP_CDDOT8 ) * ALPCMD) + ReadCOMPOOL_SS( SCP_CDDOT9 )));
		C4 = HS * CDDOTC / CDCAL;

		if (VE < ReadCOMPOOL_SS( SCP_VNOALP ))
		{
			if ((DRAG >= DREFP) || (VE < ReadCOMPOOL_SS( SCP_VALMOD )) || (ICT == 1))
			{
				ICT = 1;
				C20 = midval( ReadCOMPOOL_SS( SCP_C21 ), ReadCOMPOOL_SS( SCP_C22 ) + (ReadCOMPOOL_SS( SCP_C23 ) * VE), ReadCOMPOOL_SS( SCP_C24 ) );

				if (VE < ReadCOMPOOL_SS( SCP_VC20 )) C20 = max(ReadCOMPOOL_SS( SCP_C25 ) + (C20 * VE), ReadCOMPOOL_SS( SCP_C27 ));

				DELALP = midval( CDCAL * ((DREFP / DRAG) - 1.0) / C20, ReadCOMPOOL_SS( SCP_DLAPLM ), -ReadCOMPOOL_SS( SCP_DLAPLM ) );

				if (fabs( DRAG - DREFP ) < ReadCOMPOOL_SS( SCP_DDMIN )) DELALP = 0.0;
			}
		}

		if (ISLECT == 5) T1 = G * MPS2FPS * (1.0 - (VE2 / VSAT2));

		ALDREF = (T1 / DREFP) + (((2.0 * RDTREF) + (C2 * HS)) / VE);
		RDTRF = RDTREF + C4;
		DD = DRAG - DREFP;

		if (VE < ReadCOMPOOL_SS( SCP_VRDT ))
		{
			DDS = midval( DD, -ReadCOMPOOL_SS( SCP_DDLIM ), ReadCOMPOOL_SS( SCP_DDLIM ) );
			ZK = ReadCOMPOOL_SS( SCP_ZK1 );

			if ((RK2RLP * RK2ROL) < 0.0) VTRB = VE - (ReadCOMPOOL_SS( SCP_ACN1 ) * DREFP);

			if ((fabs( DD ) <= fabs( DDP )) || (VE > VTRB) || (LMFLG > 0)) ZK = 0.0;
			DLRDOT = midval( DLRDOT + (ZK * DDS), -ReadCOMPOOL_SS( SCP_DLRDTM ), ReadCOMPOOL_SS( SCP_DLRDTM ) );
		}

		DDP = DD;
		RK2RLP = RK2ROL;
		LODX = ALDREF + (C16 * DD) + (C17 * (RDTRF + DLRDOT - RDOT));
		LODV = LODX;
		YL = midval( ReadCOMPOOL_SS( SCP_CY0 ) + (ReadCOMPOOL_SS( SCP_CY1 ) * VE), ReadCOMPOOL_SS( SCP_Y1 ), ReadCOMPOOL_SS( SCP_Y2 ) );
		LMN = ReadCOMPOOL_SS( SCP_ALMN2 );
		DZSGN = fabs( DELAZ ) - fabs( DZOLD );
		DZOLD = DELAZ;

		if (DZSGN > 0.0)
		{
			if ((YL - ReadCOMPOOL_SS( SCP_YLMIN )) < fabs( DELAZ )) LMN = ReadCOMPOOL_SS( SCP_ALMN1 );
		}
		else
		{
			if ((YL - ReadCOMPOOL_SS( SCP_YLMN2 )) < fabs( DELAZ )) LMN = ReadCOMPOOL_SS( SCP_ALMN1 );
		}

		if (VE > ReadCOMPOOL_SS( SCP_VYLMAX )) LMN = ReadCOMPOOL_SS( SCP_ALMN4 );

		if (VE < ReadCOMPOOL_SS( SCP_VELMN )) LMN = ReadCOMPOOL_SS( SCP_ALMN3 );

		if (VE < ReadCOMPOOL_SS( SCP_VYLMAX )) RK2ROL = sign( ROLL );

		LMN = XLOD * LMN;
		DLZRL = DELAZ * RK2ROL;

		if (((RK2ROL * RK2RLP) > 0.0) && (IDBCHG == 1)) WriteCOMPOOL_SS( SCP_Y1, ReadCOMPOOL_SS( SCP_Y3 ) );

		if ((fabs( LODV ) >= LMN) && (DLZRL <= 0.0))
		{
			LMFLG = 1;
			LODV = LMN * sign( LODV );
		}
		else
		{
			LMFLG = 0;
			LMN = XLOD;
			if (DLZRL >= YL)
			{
				RK2ROL = -RK2ROL;
				IDBCHG = 1;
			}
		}
		return;
	}

	void EntryGuidance::EGROLCMD( void )
	{
		double RLM = 0.0;// roll limit [deg]
		double RDEALF = 0.0;// [deg]
		double ALMNXD = 0.0;// [deg]

		// compute roll commands and reference angles
		/*if (((RK2ROL * RK2RLP) < 0.0) && (IVRR == 0))
		{
			VRR = VE;
			IVRR = 1;
		}*/

		ARG[0] = LODV / XLOD;
		ARG[1] = LODX / XLOD;
		ARG[2] = ALDREF / XLOD;

		for (unsigned short i = 0; i <= 2; i++)
		{
			if (fabs( ARG[i] ) >= 1.0) ARG[i] = sign( ARG[i] * XLOD );

			ROLLC[i] = RK2ROL * acos( ARG[i] ) * DEG;
		}

		if (ICT == 1)
		{
			DELALF = ALPHA - ACMD1;
			RDEALF = midval( ReadCOMPOOL_SS( SCP_CRDEAF ) * DELALF, ReadCOMPOOL_SS( SCP_RDMAX ), -ReadCOMPOOL_SS( SCP_RDMAX ) );
			ALMNXD = acos( LMN / XLOD ) / /*DTR*/RAD;
			ROLLC[0] = midval( fabs( ROLLC[1] ) + RDEALF, ALMNXD, 180.0 - ALMNXD ) * RK2ROL;
			ACLAM = min(ReadCOMPOOL_SS( SCP_DLALLM ), ACLAM1 + (ACLAM2 * VE));
			ACLIM = min(ACLIM1 + (ACLIM2 * VE), ACLIM3 + (ACLIM4 * VE));

			ALPCMD = midval( ACLAM, ALPHA + DELALP, ACLIM );
		}

		// limit roll command
		if (VE > ReadCOMPOOL_SS( SCP_VRLMC )) RLM = min(ReadCOMPOOL_SS( SCP_RLMC1 ), ReadCOMPOOL_SS( SCP_RLMC2 ) + (ReadCOMPOOL_SS( SCP_RLMC3 ) * VE));
		else RLM = max(ReadCOMPOOL_SS( SCP_RLMC6 ), ReadCOMPOOL_SS( SCP_RLMC4 ) + (ReadCOMPOOL_SS( SCP_RLMC5 ) * VE));

		if ((fabs( ROLLC[0] ) > RLM) && (VE < ReadCOMPOOL_SS( SCP_VEROLC ))) ROLLC[0] = RLM * sign( ROLLC[0] );

		// HACK don't convert to RAD
		//ROLLC[0] *= RAD;
		//ALPCMD *= RAD;

		//if ((ISLECT == 2) && (ISLECP == 1)) RC176G = ROLLC[0];// * DEG;

		//ISLECP = ISLECT;
		return;
	}
}
