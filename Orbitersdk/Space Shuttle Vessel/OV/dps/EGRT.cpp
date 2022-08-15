/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2020/08/24   GLS
2021/01/19   GLS
2021/06/16   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/04/20   GLS
2022/04/26   GLS
********************************************/
#include "EGRT.h"
#include <MathSSV.h>



namespace dps
{
	/////// EGRT (from 80-FM-24, JSC-16516) ///////
	// velocity limit for midpoint targeting
	//const double VMIDPT = 0.0;// [fps] TBD

	// initial HAC radius
	constexpr double RI = 20000.0;// [ft]

	// HAC turn angle tolerance value (units in document are probably wrong, so set here to [rad])
	constexpr double A3TOL = -0.003;// [rad]

	// convertion factor from feet to nautical miles
	constexpr double CNMFS = 1.645788e-4;// [NM/ft]


	constexpr double MCRT01 = 1.0;// extracted from code in 80-FM-23
	constexpr double MCRT02 = 0.5;// extracted from code in 80-FM-23
	constexpr double MCRT03 = 0.5;// extracted from code in 80-FM-23


	EGRT::EGRT( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "EGRT" )
	{
		IFP = 0;

		step = 1.92;

		// I-LOADs init
		XHACL = -40519.2;
		XHACH = -44487.6;
		return;
	}

	EGRT::~EGRT( void )
	{
		return;
	}

	bool EGRT::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "IFP", 3 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) IFP = tmp;
			return true;
		}
		else return false;
	}

	void EGRT::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "IFP", IFP );
		return;
	}

	void EGRT::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		GetValILOAD( "XHACL", ILOADs, XHACL );
		GetValILOAD( "XHACH", ILOADs, XHACH );
		return;
	}

	void EGRT::OnPreStep( double simt, double simdt, double mjd )
	{
		step += simdt;
		if (step < 1.92) return;

		OVHD = ReadCOMPOOL_IS( SCP_OVHD );
		RWID = ReadCOMPOOL_IS( SCP_RWID );
		RWID0 = ReadCOMPOOL_IS( SCP_RWID0 );
		RTURN = ReadCOMPOOL_SD( SCP_RTURN );
		PSHA = ReadCOMPOOL_SD( SCP_PSHA );
		YSGN = ReadCOMPOOL_SD( SCP_YSGN );
		PSHARS = ReadCOMPOOL_SD( SCP_PSHARS );
		RF0 = ReadCOMPOOL_SD( SCP_RF0 );
		R1 = ReadCOMPOOL_SD( SCP_R1 );
		R2 = ReadCOMPOOL_SD( SCP_R2 );
		if (RWID == 1)
		{
			RAZ = ReadCOMPOOL_SD( SCP_PRI_HDG ) * RAD;
			RLS = ReadCOMPOOL_V( SCP_PRI_POS );
			REC = ReadCOMPOOL_M( SCP_PRI_G2R );
		}
		else
		{
			RAZ = ReadCOMPOOL_SD( SCP_SEC_HDG ) * RAD;
			RLS = ReadCOMPOOL_V( SCP_SEC_POS );
			REC = ReadCOMPOOL_M( SCP_SEC_G2R );
		}
		WTGS1 = ReadCOMPOOL_SD( SCP_WT_GS1 );
		XYZE = ReadCOMPOOL_V( SCP_ECEF_POS );
		XYZED = ReadCOMPOOL_V( SCP_ECEF_VEL );
		M = ReadCOMPOOL_SD( SCP_WEIGHT );

		EXEC();

		WriteCOMPOOL_IS( SCP_RWID0, RWID0 );
		WriteCOMPOOL_SD( SCP_RTURN, static_cast<float>(RTURN) );
		WriteCOMPOOL_SD( SCP_YSGN, static_cast<float>(YSGN) );
		WriteCOMPOOL_SD( SCP_PSHA, static_cast<float>(PSHA) );
		WriteCOMPOOL_SD( SCP_DELAZ, static_cast<float>(DELAZ) );
		WriteCOMPOOL_SD( SCP_TRANG, static_cast<float>(TRANG) );
		WriteCOMPOOL_SD( SCP_XHAC, static_cast<float>(RC.data[0]) );

		step = 0.0;
		return;
	}

	bool EGRT::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 304) return true;
		else return false;
	}

	void EGRT::EXEC( void )
	{
		if (IFP == 0) RWID0 = RWID;

		if (RWID != RWID0) IRED = 1;
		else IRED = 0;

		RWID0 = RWID;

		//IMID = 0;

		//if (VE > VMIDPT) IMID = 1;

		// moved this selection to OnPreStep() for data input
		//if (RWID == 1) RAZ = AZRW;
		//else RAZ = SRAZ;

		//VE = length( XYZED );

		SEQ();

		/*if (IMID == 1)
		{
			SEQ();

			DELAZ = (DELAZ + SDELAZ) / 2.0;
			TRANG = (TRANG + STRANG) / 2.0;
		}*/

		//YSGNT = YSGN;
		//PSHAT = PSHA;
		//RTURNT = RTURN;

		IFP = 1;
		return;
	}

	void EGRT::SEQ( void )
	{
		VECTOR3 RGEF = _V( 0.0, 0.0, 0.0 );
		VECTOR3 RG = _V( 0.0, 0.0, 0.0 );

		for (unsigned short i = 0; i <= 2; i++) RGEF.data[i] = XYZE.data[i] - RLS.data[i];

		RG = mul( REC, RGEF );
		SIGNY = sign( RG.data[1] );

		//if (VE <= VTOGL)
		//{
		//	if (OVHD == 1) OVHD = 0;
		//	else
		//	{
		//		OVHD = 1;
		//		YSGN = -SIGNY;
		//	}
		//
		//	PSHA = PSHARS;
		//	VTOGL = 0.0;
		//}

		if ((IFP == 0) || ((IRED == 1)/* && (IMID == 0)*/))
		{
			PSHA = PSHARS;
			RTURN = RI;

			if (OVHD == 1) YSGN = -SIGNY;
		}

		if (OVHD == 0) YSGN = SIGNY;

		CHACRC();

		CHACEFC();

		BV();

		BVCHAC();

		COSTHETA();

		DWP1();

		DVNEP();

		DELAZ_();
		return;
	}

	void EGRT::CHACRC( void )
	{
		if (M < WTGS1) RC.data[0] = XHACL;
		else RC.data[0] = XHACH;

		RC.data[1] = YSGN * RF0;
		RC.data[2] = 0.0;
		return;
	}

	void EGRT::CHACEFC( void )
	{
		HACEF = mul( Inverse( REC ), RC );
		return;
	}

	void EGRT::BV( void )
	{
		double T3 = 0.0;
		double T4 = 0.0;

		for (unsigned short i = 0; i <= 2; i++) RCCEF[i] = RLS.data[i] + HACEF.data[i];

		VNORM[0] = (XYZE.data[1] * RCCEF[2]) - (XYZE.data[2] * RCCEF[1]);
		VNORM[1] = (XYZE.data[2] * RCCEF[0]) - (XYZE.data[0] * RCCEF[2]);
		VNORM[2] = (XYZE.data[0] * RCCEF[1]) - (XYZE.data[1] * RCCEF[0]);
		RVEHMG = sqrt( (XYZE.data[0] * XYZE.data[0]) + (XYZE.data[1] * XYZE.data[1]) + (XYZE.data[2] * XYZE.data[2]) );
		T3 = VNORM[2] * RVEHMG;
		T4 = (VNORM[0] * XYZE.data[1]) - (VNORM[1] * XYZE.data[0]);
		BARVEH = atan2( T3, T4 );
		RCHMAG = sqrt( (RCCEF[0] * RCCEF[0]) + (RCCEF[1] * RCCEF[1]) + (RCCEF[2] * RCCEF[2]) );
		SINB = RTURN / RCHMAG;
		return;
	}

	void EGRT::BVCHAC( void )
	{
		double T5 = 0.0;
		double T6 = 0.0;

		T5 = VNORM[2] * RCHMAG;
		T6 = (RCCEF[1] * VNORM[0]) - (VNORM[1] * RCCEF[0]);
		BARCC = atan2( T5, T6 );

		if (BARCC < 0.0) BARCC += PI2;
		return;
	}

	void EGRT::COSTHETA( void )
	{
		double T7 = 0.0;

		for (unsigned short i = 0; i <= 2; i++) T7 += XYZE.data[i] * RCCEF[i];

		CTHVC = T7 / (RVEHMG * RCHMAG);
		return;
	}

	void EGRT::DWP1( void )
	{
		double STHVC = 0.0;
		double CTVWP1 = 0.0;
		double TEMP = 0.0;

		STHVC = sqrt( MCRT01 - (CTHVC * CTHVC) );
		CTVWP1 = CTHVC + (MCRT02 * CTHVC * SINB * SINB);
		SBARCR = SINB / STHVC;
		TEMP = CTVWP1 * SBARCR;
		TEMP = min(1.0, max(TEMP, -1.0));
		A2 = acos( TEMP );
		TEMP = CTVWP1;
		TEMP = min(1.0, max(TEMP, -1.0));
		DVEWP1 = acos( TEMP ) * RCHMAG;
		return;
	}

	void EGRT::DVNEP( void )
	{
		double TEMP = 0.0;
		double T8 = 0.0;// [rad]
		double A3 = 0.0;// new PSHA [rad]

		TEMP = SBARCR;
		TEMP = min(1.0, max(TEMP, -1.0));
		T8 = asin( TEMP );
		BARWP1 = BARVEH - (YSGN * T8);
		A3 = (MCRT03 * PI) - A2 + (YSGN * (RAZ - BARCC));

		if (fabs( A3 ) > PI) A3 -= PI2 * sign( A3 );

		if ((PSHA > PSHARS + 1.0) || (A3 < A3TOL) || (YSGN != SIGNY)) A3 += PI2;

		PSHA = A3 * DEG;
		RTURN = RF0 + ((R1 + (R2 * PSHA)) * PSHA);
		DARC = (RF0 + ((0.5 * R1) + (0.3333333 * R2 * PSHA)) * PSHA) * PSHA * RAD;

		TRANG = CNMFS * (DVEWP1 + DARC - RC.data[0]);
		return;
	}

	void EGRT::DELAZ_( void )
	{
		VECTOR3 H = crossp( XYZE, XYZED );
		RVEHMG = length( XYZE );
		PSI = atan2( RVEHMG * H.data[2], (XYZE.data[1] * H.data[0]) - (XYZE.data[0] * H.data[1]) );

		DELAZ = PSI - BARWP1;

		if (fabs( DELAZ ) > PI) DELAZ -= PI2 * sign( DELAZ );
		return;
	}
};
