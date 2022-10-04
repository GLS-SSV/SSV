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
********************************************/
#include "EntryGuidance.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	/////// Entry (from 80-FM-24, JSC-16516) ///////

	// convertion factor from feet to nautical miles
	constexpr double CNMFS = 1.645788e-4;// [NM/ft]


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
		ASTART = 4.25;
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
		VNOALP = 23000.0;
		VALMOD = 23000.0;
		VC20 = 2500.0;
		DLAPLM = 2.0;
		DDMIN = 0.15;
		RDMAX = 12.0;
		CRDEAF = 4.0;
		DLALLM = 43.0;
		ACLAM1 = 9.352966;
		ACLAM2 = 0.003058794;
		ACLIM1 = 37.0;
		ACLIM2 = 0.0;
		ACLIM3 = 7.6666667;
		ACLIM4 = 0.00223333;
		Y1 = 0.1832595;
		Y2 = 0.1745329;
		Y3 = 0.3054325;
		CY0 = -0.2181662;
		CY1 = 0.0001309;
		DLRDLM = 150.0;
		VHS1 = 12310.0;
		VHS2 = 19675.5;
		HS01 = 18075.0;
		HS02 = 27000.0;
		HS03 = 45583.5;
		HS11 = 0.725;
		HS13 = -0.9445;
		HSMIN = 20500.0;
		ALFM = 33.0;
		DELV = 2300.0;
		VTRAN = 10500.0;
		VQ = 5000.0;
		ETRAN = 6.002262e7;
		EEF4 = 2.0e6;
		DF = 21.0;
		RPT1 = 22.4;
		VSAT = 25766.2;
		VS1 = 23283.5;
		D230 = 19.8;
		VB1 = 19000.0;
		VA = 27637.0;
		VA1 = 22000.0;
		VA2 = 27637.0;
		AK = -3.4573;
		AK1 = -4.76;
		LODMIN = 0.5;
		DT2MIN = 0.008;
		E1 = 0.01;
		GS1 = 0.02;
		GS2 = 0.02;
		GS3 = 0.03767;
		GS4 = 0.03;
		DRDDL = -1.5;
		ALIM = 70.84;
		CT16[0] = 0.1354;
		CT16[1] = -0.1;
		CT16[2] = 0.006;
		VC16 = 23000.0;
		CT16MN = 0.025;
		CT16MX = 0.35;
		CT17MN = 0.0025;
		CT17MX = 0.014;
		CT17M2 = 0.00133;
		CT17[0] = 1.537e-2;
		CT17[1] = -5.8146e-1;
		C17MP = 0.75;
		C21 = 0.06;
		C22 = -0.001;
		C23 = 4.25e-6;
		C24 = 0.01;
		C25 = 0.0;
		C27 = 0.0;
		CDDOT1 = 1500.0;
		CDDOT2 = 2000.0;
		CDDOT3 = 0.15;
		CDDOT4 = 0.0783;
		CDDOT5 = -8.165e-3;
		CDDOT6 = 6.833e-4;
		CDDOT7 = 7.5e-5;
		CDDOT8 = 13.666e-4;
		CDDOT9 = -8.165e-3;
		VRDT = 23000.0;
		DDLIM = 2.0;
		ZK1 = 1.0;
		ALMN1 = 0.7986355;
		ALMN2 = 0.9659258;
		ALMN3 = 0.93969;
		ALMN4 = 1.0;
		YLMIN = 0.03;
		YLMN2 = 0.07;
		VYLMAX = 23000.0;
		VELMN = 8000.0;
		ACN1 = 50.0;
		VRLMC = 2500.0;
		RLMC1 = 70.0;
		RLMC2 = 70.0;
		RLMC3 = 0.0;
		RLMC4 = 70.0;
		RLMC5 = 0.0;
		RLMC6 = 70.0;
		VEROLC = 8000.0;
		V_TAEM = 2500.0;
		PREBNK = 0;
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
		GetValILOAD( "ASTART", ILOADs, ASTART );
		GetValILOAD( "CALP0", ILOADs, 10, CALP0 );
		GetValILOAD( "CALP1", ILOADs, 10, CALP1 );
		GetValILOAD( "CALP2", ILOADs, 10, CALP2 );
		GetValILOAD( "VALP", ILOADs, 9, VALP );
		GetValILOAD( "NALP", ILOADs, NALP );
		GetValILOAD( "VNOALP", ILOADs, VNOALP );
		GetValILOAD( "VALMOD", ILOADs, VALMOD );
		GetValILOAD( "VC20", ILOADs, VC20 );
		GetValILOAD( "DLAPLM", ILOADs, DLAPLM );
		GetValILOAD( "DDMIN", ILOADs, DDMIN );
		GetValILOAD( "RDMAX", ILOADs, RDMAX );
		GetValILOAD( "CRDEAF", ILOADs, CRDEAF );
		GetValILOAD( "DLALLM", ILOADs, DLALLM );
		GetValILOAD( "ACLAM1", ILOADs, ACLAM1 );
		GetValILOAD( "ACLAM2", ILOADs, ACLAM2 );
		GetValILOAD( "ACLIM1", ILOADs, ACLIM1 );
		GetValILOAD( "ACLIM2", ILOADs, ACLIM2 );
		GetValILOAD( "ACLIM3", ILOADs, ACLIM3 );
		GetValILOAD( "ACLIM4", ILOADs, ACLIM4 );
		GetValILOAD( "Y1", ILOADs, Y1 );
		GetValILOAD( "Y2", ILOADs, Y2 );
		GetValILOAD( "Y3", ILOADs, Y3 );
		GetValILOAD( "CY0", ILOADs, CY0 );
		GetValILOAD( "CY1", ILOADs, CY1 );
		GetValILOAD( "DLRDLM", ILOADs, DLRDLM );
		GetValILOAD( "VHS1", ILOADs, VHS1 );
		GetValILOAD( "VHS2", ILOADs, VHS2 );
		GetValILOAD( "HS01", ILOADs, HS01 );
		GetValILOAD( "HS02", ILOADs, HS02 );
		GetValILOAD( "HS03", ILOADs, HS03 );
		GetValILOAD( "HS11", ILOADs, HS11 );
		GetValILOAD( "HS13", ILOADs, HS13 );
		GetValILOAD( "HSMIN", ILOADs, HSMIN );
		GetValILOAD( "ALFM", ILOADs, ALFM );
		GetValILOAD( "DELV", ILOADs, DELV );
		GetValILOAD( "VTRAN", ILOADs, VTRAN );
		GetValILOAD( "VQ", ILOADs, VQ );
		GetValILOAD( "ETRAN", ILOADs, ETRAN );
		GetValILOAD( "EEF4", ILOADs, EEF4 );
		GetValILOAD( "DF", ILOADs, DF );
		GetValILOAD( "RPT1", ILOADs, RPT1 );
		GetValILOAD( "VSAT", ILOADs, VSAT );
		GetValILOAD( "VS1", ILOADs, VS1 );
		GetValILOAD( "D230", ILOADs, D230 );
		GetValILOAD( "VB1", ILOADs, VB1 );
		GetValILOAD( "VA", ILOADs, VA );
		GetValILOAD( "VA1", ILOADs, VA1 );
		GetValILOAD( "VA2", ILOADs, VA2 );
		GetValILOAD( "AK", ILOADs, AK );
		GetValILOAD( "AK1", ILOADs, AK1 );
		GetValILOAD( "LODMIN", ILOADs, LODMIN );
		GetValILOAD( "DT2MIN", ILOADs, DT2MIN );
		GetValILOAD( "E1", ILOADs, E1 );
		GetValILOAD( "GS1", ILOADs, GS1 );
		GetValILOAD( "GS2", ILOADs, GS2 );
		GetValILOAD( "GS3", ILOADs, GS3 );
		GetValILOAD( "GS4", ILOADs, GS4 );
		GetValILOAD( "DRDDL", ILOADs, DRDDL );
		GetValILOAD( "ALIM", ILOADs, ALIM );
		GetValILOAD( "CT16", ILOADs, 3, CT16 );
		GetValILOAD( "VC16", ILOADs, VC16 );
		GetValILOAD( "CT16MN", ILOADs, CT16MN );
		GetValILOAD( "CT16MX", ILOADs, CT16MX );
		GetValILOAD( "CT17MN", ILOADs, CT17MN );
		GetValILOAD( "CT17MX", ILOADs, CT17MX );
		GetValILOAD( "CT17M2", ILOADs, CT17M2 );
		GetValILOAD( "CT17", ILOADs, 2, CT17 );
		GetValILOAD( "C17MP", ILOADs, C17MP );
		GetValILOAD( "C21", ILOADs, C21 );
		GetValILOAD( "C22", ILOADs, C22 );
		GetValILOAD( "C23", ILOADs, C23 );
		GetValILOAD( "C24", ILOADs, C24 );
		GetValILOAD( "C25", ILOADs, C25 );
		GetValILOAD( "C27", ILOADs, C27 );
		GetValILOAD( "CDDOT1", ILOADs, CDDOT1 );
		GetValILOAD( "CDDOT2", ILOADs, CDDOT2 );
		GetValILOAD( "CDDOT3", ILOADs, CDDOT3 );
		GetValILOAD( "CDDOT4", ILOADs, CDDOT4 );
		GetValILOAD( "CDDOT5", ILOADs, CDDOT5 );
		GetValILOAD( "CDDOT6", ILOADs, CDDOT6 );
		GetValILOAD( "CDDOT7", ILOADs, CDDOT7 );
		GetValILOAD( "CDDOT8", ILOADs, CDDOT8 );
		GetValILOAD( "CDDOT9", ILOADs, CDDOT9 );
		GetValILOAD( "VRDT", ILOADs, VRDT );
		GetValILOAD( "DDLIM", ILOADs, DDLIM );
		GetValILOAD( "ZK1", ILOADs, ZK1 );
		GetValILOAD( "ALMN1", ILOADs, ALMN1 );
		GetValILOAD( "ALMN2", ILOADs, ALMN2 );
		GetValILOAD( "ALMN3", ILOADs, ALMN3 );
		GetValILOAD( "ALMN4", ILOADs, ALMN4 );
		GetValILOAD( "YLMIN", ILOADs, YLMIN );
		GetValILOAD( "YLMN2", ILOADs, YLMN2 );
		GetValILOAD( "VYLMAX", ILOADs, VYLMAX );
		GetValILOAD( "VELMN", ILOADs, VELMN );
		GetValILOAD( "ACN1", ILOADs, ACN1 );
		GetValILOAD( "VRLMC", ILOADs, VRLMC );
		GetValILOAD( "RLMC1", ILOADs, RLMC1 );
		GetValILOAD( "RLMC2", ILOADs, RLMC2 );
		GetValILOAD( "RLMC3", ILOADs, RLMC3 );
		GetValILOAD( "RLMC4", ILOADs, RLMC4 );
		GetValILOAD( "RLMC5", ILOADs, RLMC5 );
		GetValILOAD( "RLMC6", ILOADs, RLMC6 );
		GetValILOAD( "VEROLC", ILOADs, VEROLC );
		GetValILOAD( "V_TAEM", ILOADs, V_TAEM );
		GetValILOAD( "PREBNK", ILOADs, PREBNK );
		return;
	}

	void EntryGuidance::OnPreStep( double simt, double simdt, double mjd )
	{
		step += simdt;
		if (step < 1.92) return;

		ALPHA = ReadCOMPOOL_SD( SCP_ALPHA );
		ROLL = ReadCOMPOOL_SD( SCP_PHI );
		TRANGE = ReadCOMPOOL_SD( SCP_TRANG );
		VE = ReadCOMPOOL_SD( SCP_VE );
		VI = ReadCOMPOOL_SD( SCP_VI );
		XLFAC = ReadCOMPOOL_SD( SCP_XLFAC );
		DRAG = ReadCOMPOOL_SD( SCP_DRAG );
		DELAZ = ReadCOMPOOL_SD( SCP_DELAZ );
		HLS = ReadCOMPOOL_SD( SCP_H );
		LOD = ReadCOMPOOL_SD( SCP_LOD );
		RDOT = ReadCOMPOOL_SD( SCP_HDOT );
		DLRDOT = ReadCOMPOOL_SD( SCP_DLRDOT );
		ISLECT = ReadCOMPOOL_IS( SCP_ISLECT );

		EGEXEC( step/*simdt*/ );

		//sprintf_s( oapiDebugString(), 256, "ISLECT%d (DRAG - DREFP)%.3f DRAG%.3f DREFP%.3f ACLAM%.3f ACLIM%.3f ACMD1%.3f ALPCMD%.3f", ISLECT, DRAG - DREFP, DRAG, DREFP, ACLAM, ACLIM, ACMD1, ALPCMD );

		// ROLL REF status
		double ROLLREFLIM = 0.0;
		if (VE >= 9500.0) ROLLREFLIM = 37.0;
		else if (VE >= 4000.0) ROLLREFLIM = 20.0;
		else  ROLLREFLIM = -5.0;
		WriteCOMPOOL_IS( SCP_ROLL_REF_CREW_ALERT, (fabs( ROLLC[2] ) < ROLLREFLIM) ? 1 : 0 );


		WriteCOMPOOL_SD( SCP_ALPCMD, static_cast<float>(ALPCMD) );
		WriteCOMPOOL_SD( SCP_DREFP, static_cast<float>(DREFP) );
		WriteCOMPOOL_SD( SCP_ROLLCMD, static_cast<float>(ROLLC[0]) );
		WriteCOMPOOL_SD( SCP_ROLLREF, static_cast<float>(ROLLC[2]) );
		WriteCOMPOOL_SD( SCP_RDTREF, static_cast<float>(RDTREF) );
		WriteCOMPOOL_SD( SCP_DRDD, static_cast<float>(DRDD) );
		WriteCOMPOOL_SD( SCP_DLRDOT, static_cast<float>(DLRDOT) );
		WriteCOMPOOL_SD( SCP_YL, static_cast<float>(YL) );
		WriteCOMPOOL_SD( SCP_ACMD1, static_cast<float>(ACMD1) );
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
		if ((ISLECT == 1) && (XLFAC >= ASTART))
		{
			ISLECT = 2;
			//DTEGD = 1.92;// HACK replaced fixed cycle length for dt
			if (VE < VTRAN) ISLECT = 5;
		}

		if ((ISLECT == 2) && (VE < VB1)) ISLECT = 3;

		if (((ISLECT == 2) || (ISLECT == 3)) && (T2 > ALFM)) ISLECT = 4;

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
				if ((VE < VA) && (DREFP < DREFP3)) ISLECT = 3;
				if ((VE < (VCG + DELV)) && (DREFP > DREFP4)) ISLECT = 4;
				break;
			case 3:
				if ((VE < (VCG + DELV)) && (DREFP > DREFP4)) ISLECT = 4;
				if ((VE < (VTRAN + DELV)) && (DREFP > DREFP5) && (VCG < VTRAN)) ISLECT = 5;
				break;
			case 4:
				if ((VE < (VTRAN + DELV)) && (DREFP > DREFP5)) ISLECT = 5;
				break;
			/*case 5:
				break;*/
		}
		return;
	}

	void EntryGuidance::EGSCALHT( void )
	{
		// compute altitude scale height (HS)
		if (VE < VHS1) HS = HS01 + (HS11 * VE);
		else
		{
			if (VE < VHS2) HS = HS02;
			else HS = HS03 + (HS13 * VE);
		}

		if (HS < HSMIN) HS = HSMIN;
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
		VQ2 = VQ * VQ;
		RK2ROL = -sign( DELAZ );
		DLRDOT = 0.0;
		LMFLG = 0;
		VTRB = 60000.0;
		DDP = 0.0;
		RK2RLP = RK2ROL;

		// compute desired transition range (RPT)
		RPT = (-(((ETRAN - EEF4) * log( DF / ALFM ) / (ALFM - DF)) + (((VTRAN * VTRAN) - VQ2) / (2.0 * ALFM))) * CNMFS) + RPT1;

		VSAT2 = VSAT * VSAT;
		VSIT2 = VS1 * VS1;
		VCG = VQ;
		D23 = D230;
		DX[0] = 1.0;

		V0[0] = VB1;
		VX[0] = VA;
		VF[0] = VA1;
		A[0] = AK;
		V0[1] = VA1;
		VX[1] = VA2;
		A[1] = AK1;
		VB2 = VB1 * VB1;

		// compute component of constant drag phase range (RCG)
		RCG1 = CNMFS * (VSIT2 - VQ2) / (2.0 * ALFM);

		IALP = NALP;
		START = 1;
		return;
	}

	void EntryGuidance::EGCOMN( double dt )
	{
		double RDTRFT = 0.0;// [fps]

		// compute common variables
		XLOD = max(LOD, LODMIN);
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

			if (VE < (VTRAN + DELV))
			{
				C1 = (T2 - DF) / (ETRAN - EEF4);
				RDTRFT = -((C1 * (((G * MPS2FPS) * HLS) - EEF4)) + DF) * 2.0 * VE * HS / CAG;
				DREFP5 = DF + ((EEF - EEF4) * C1) + (GS4 * (RDTREF - RDTRFT));
			}
		}
		return;
	}

	void EntryGuidance::EGPEP( void )
	{
		// compute vertical L/D during preentry phase
		LODX = XLOD * cos( PREBNK * RAD );
		LODV = LODX;
		return;
	}

	void EntryGuidance::EGRP( void )
	{
		unsigned short K = 0;
		double D23L = 0.0;// [fps^2]
		double R23 = 0.0;// [NM]

		// compute reference parameters for temperature control and equilibrium glide phases (ISLECT = 2 or 3)
		if (VE > VA1)
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
				if (i == 1) DX[1] = CQ1[0] + (VA1 * (CQ2[0] + (CQ3[0] * VA1)));

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
		if ((T2DOT > DT2MIN) || (VE > (VCG + DELV)))
		{
			if (VE < VB1) VB2 = VE2;

			VCG = VQ;
			D23L = ALFM * (VSIT2 - VB2) / (VSIT2 - VQ2);

			if (D23 > D23L) VCG = sqrt( VSIT2 - (D23L * (VSIT2 - VQ2) / D23) );
			else D23 = D23L;

			A2 = CNMFS * (VSIT2 - VB2) / 2.0;
			REQ1 = A2 * log( ALFM / D23 );
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
		if (VE > VB1)
		{
			for (unsigned short i = 1; i <= N; i++)
			{
				DREF[i - 1] = CQ1[i - 1] + (VE * (CQ2[i - 1] + (CQ3[i - 1] * VE)));
				HDTRF[i - 1] = -HS * ((2.0 * DREF[i - 1] / VE) - CQ2[i - 1] - (2.0 * CQ3[i - 1] * VE));
			}

			if (VE > VA1)
			{
				DRF = DREF[1] - DREF[0];
				DRF = DRF * (DRF + ((HDTRF[0] - HDTRF[1]) * GS1));

				if (DRF < 0.0) N = 1;
			}

			DREFP = D23 * DREF[N - 1];
			RDTREF = D23 * HDTRF[N - 1];
			C2 = CQ2[N - 1] * D23;
		}

		// during equilibrium glide phase
		if (VE < VA)
		{
			ALDCO = (1.0 - (VB2 / VSIT2)) / D23;
			DREFP1 = (1.0 - (VE2 / VSIT2)) / ALDCO;
			RDTRF1 = (-2.0 * HS) / (VE * ALDCO);
			DREFP3 = DREFP1 + (GS2 * (RDTREF - RDTRF1));

			if ((DREFP3 > DREFP) || (VE < VB1))
			{
				DREFP = DREFP1;
				RDTREF = RDTRF1;
				C2 = 0.0;
			}
		}

		// compute test value for DREFP for transition to constant drag phase (ISLECT = 4)
		DREFP4 = (GS3 * (RDTREF + (2.0 * HS * T2 / VE))) + T2;
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
			DREFP = ALFM;
			ITRAN = true;
		}

		DREFPT = DREFP - DF;

		if (fabs( DREFP ) < E1) DREFP = DF + (E1 * sign( DREFPT ));

		if (DREFP < E1) DREFP = E1;

		DREFPT = DREFP - DF;
		C1 = DREFPT / (EEF - EEF4);
		RER1 = CNMFS * log( DREFP / DF ) / C1;
		DRDD = min((CNMFS / (C1 * DREFP)) - (RER1 / DREFPT), DRDDL);
		DREFP = DREFP + ((TRANGE - RER1 - RPT1) / DRDD);
		DLIM = ALIM * DRAG / XLFAC;

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
		C16 = CT16[0] * pow( DRAG, CT16[1] );

		if (VE < VC16) C16 = C16 + (CT16[2] * (DRAG - DREFP));

		C16 = midval( C16, CT16MN, CT16MX );

		if (ICT == 1) CT17MN = CT17M2;

		C17 = midval( CT17[0] * pow( DRAG, CT17[1] ), CT17MN, CT17MX );

		if (ICT == 1) C17 = C17MP * C17;
		return;
	}

	void EntryGuidance::EGLODVCMD( void )
	{
		double A44 = 0.0;// [1]
		double CDCAL = 0.0;// [1]
		double CDDOTC = 0.0;
		double RDTRF = 0.0;// [fps]

		// compute vertical L/D command (LODV)
		A44 = exp( -(VE - CDDOT1) / CDDOT2 );
		CDCAL = CDDOT4 + (ALPCMD * (CDDOT5 + (CDDOT6 * ALPCMD))) + (CDDOT3 * A44);
		CDDOTC = (CDDOT7 * (DRAG + (G * MPS2FPS * RDOT / VE)) * A44) + (ALPDOT * ((CDDOT8 * ALPCMD) + CDDOT9));
		C4 = HS * CDDOTC / CDCAL;

		if (VE < VNOALP)
		{
			if ((DRAG >= DREFP) || (VE < VALMOD) || (ICT == 1))
			{
				ICT = 1;
				C20 = midval( C21, C22 + (C23 * VE), C24 );

				if (VE < VC20) C20 = max(C25 + (C20 * VE), C27);

				DELALP = midval( CDCAL * ((DREFP / DRAG) - 1.0) / C20, DLAPLM, -DLAPLM );

				if (fabs( DRAG - DREFP ) < DDMIN) DELALP = 0.0;
			}
		}

		if (ISLECT == 5) T1 = G * MPS2FPS * (1.0 - (VE2 / VSAT2));

		ALDREF = (T1 / DREFP) + (((2.0 * RDTREF) + (C2 * HS)) / VE);
		RDTRF = RDTREF + C4;
		DD = DRAG - DREFP;

		if (VE < VRDT)
		{
			DDS = midval( DD, -DDLIM, DDLIM );
			ZK = ZK1;

			if ((RK2RLP * RK2ROL) < 0.0) VTRB = VE - (ACN1 * DREFP);

			if ((fabs( DD ) <= fabs( DDP )) || (VE > VTRB) || (LMFLG > 0)) ZK = 0.0;
			DLRDOT = midval( DLRDOT + (ZK * DDS), -DLRDLM, DLRDLM );
		}

		DDP = DD;
		RK2RLP = RK2ROL;
		LODX = ALDREF + (C16 * DD) + (C17 * (RDTRF + DLRDOT - RDOT));
		LODV = LODX;
		YL = midval( CY0 + (CY1 * VE), Y1, Y2 );
		LMN = ALMN2;
		DZSGN = fabs( DELAZ ) - fabs( DZOLD );
		DZOLD = DELAZ;

		if (DZSGN > 0.0)
		{
			if ((YL - YLMIN) < fabs( DELAZ )) LMN = ALMN1;
		}
		else
		{
			if ((YL - YLMN2) < fabs( DELAZ )) LMN = ALMN1;
		}

		if (VE > VYLMAX) LMN = ALMN4;

		if (VE < VELMN) LMN = ALMN3;

		if (VE < VYLMAX) RK2ROL = sign( ROLL );

		LMN = XLOD * LMN;
		DLZRL = DELAZ * RK2ROL;

		if (((RK2ROL * RK2RLP) > 0.0) && (IDBCHG == 1)) Y1 = Y3;

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
			RDEALF = midval( CRDEAF * DELALF, RDMAX, -RDMAX );
			ALMNXD = acos( LMN / XLOD ) / /*DTR*/RAD;
			ROLLC[0] = midval( fabs( ROLLC[1] ) + RDEALF, ALMNXD, 180.0 - ALMNXD ) * RK2ROL;
			ACLAM = min(DLALLM, ACLAM1 + (ACLAM2 * VE));
			ACLIM = min(ACLIM1 + (ACLIM2 * VE), ACLIM3 + (ACLIM4 * VE));

			ALPCMD = midval( ACLAM, ALPHA + DELALP, ACLIM );
		}

		// limit roll command
		if (VE > VRLMC) RLM = min(RLMC1, RLMC2 + (RLMC3 * VE));
		else RLM = max(RLMC6, RLMC4 + (RLMC5 * VE));

		if ((fabs( ROLLC[0] ) > RLM) && (VE < VEROLC)) ROLLC[0] = RLM * sign( ROLLC[0] );

		// HACK don't convert to RAD
		//ROLLC[0] *= RAD;
		//ALPCMD *= RAD;

		//if ((ISLECT == 2) && (ISLECP == 1)) RC176G = ROLLC[0];// * DEG;

		//ISLECP = ISLECT;
		return;
	}
}
