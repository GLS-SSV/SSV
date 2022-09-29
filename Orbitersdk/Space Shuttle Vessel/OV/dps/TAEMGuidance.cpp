/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/29   GLS
2022/04/01   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "TAEMGuidance.h"
#include <MathSSV.h>
#include <EngConst.h>


namespace dps
{
	/////// TAEM (from 80-FM-29, JSC-16522) ///////
	// roll fader time constant
	constexpr double RFTC = 5.0;// [s]

	// range breakpoint for QBREF
	constexpr double PBRCQ[2] = {89971.082, 89971.082};// [ft] TBD

	// QBREF lower limit
	constexpr double QBRLL[2] = {180.0, 180.0};// [psf] TBD

	// QBREF middle limit
	constexpr double QBRML[2] = {220.0, 220.0};// [psf] TBD

	// QBREF upper limit
	constexpr double QBRUL[2] = {285.0, 285.0};// [psf] TBD

	// slope of QBREF for DRPRED > PBRCQ
	constexpr double QBC1[2] = {3.6086999e-4, 3.6086999e-4};// [psf/ft] TBD

	// slope of QBREF for DRPRED < PBRCQ
	constexpr double QBC2[2] = {-1.1613301e-3, -1.1613301e-3};// [psf/ft] TBD

	// GDH lower limit
	constexpr double GDHLL = 0.3;// [1]

	// GDH upper limit
	constexpr double GDHUL = 1.0;// [1]

	// constant for computing GDH
	constexpr double GDHC = 2.0;// [1]

	// slope for computing GDH
	constexpr double GDHS = 7.0e-5;// [ft^-1]

	// gain used to compute DNZC
	constexpr double DNZCG = 0.01;// [g/s]

	// gain used to compute HDREQ
	constexpr double HDREQG = 0.1;// [1]

	// Mach breakpoint for MXQBWT
	constexpr double QMACH1 = 0.89;// [1]

	// Mach breakpoint for MXQBWT
	constexpr double QMACH2 = 1.15;// [1]

	// constant for computing QBLL
	constexpr double QBWT1 = 0.0233521;// [psf/slug]

	// constant for computing QBLL
	constexpr double QBWT2 = 0.01902763;// [psf/slug]

	// constant for computing QBLL
	constexpr double QBWT3 = 0.03113613;// [psf/slug]

	// slope of MXQBWT with Mach
	constexpr double QBMSL1 = -0.0288355;// [psf/slug]

	// slope of MXQBWT with Mach
	constexpr double QBMSL2 = 0.00570829;// [psf/slug]

	// minimum value COSPHI
	constexpr double CPMIN = 0.707;// [1]

	// Mach breakpoint for computing QBMXNZ
	constexpr double QBM1 = 1.05;// [1]

	// Mach breakpoint for computing QBMXNZ
	constexpr double QBM2 = 1.7;// [1]

	// constant for computing QBMXNZ
	constexpr double QBMX1 = 340.0;// [psf]

	// constant for computing QBMXNZ
	constexpr double QBMX2 = 300.;// [psf]

	// constant for computing QBMXNZ
	constexpr double QBMX3 = 300.0;// [psf]

	// slope of QBMXNZ with Mach < QBM1
	constexpr double QBMXS1 = -400.0;// [psf]

	// slope of QBMXNZ with Mach > QBM2
	constexpr double QBMXS2 = 0.0;// [psf]

	// QBREF at R2MAX
	constexpr double QBREF2[2] = {185.0, 185.0};// [psf]

	// lower EOW of region for OVHD that QBMXNZ is lowered
	constexpr double EQLOWL = 60000.0;// [ft]

	// upper EOW of region for OVHD that QBMXNZ is lowered
	constexpr double EQLOWU = 85000.0;// [ft]

	// minimum PSHA for which QBMXNZ is lowered
	constexpr double PSOHQB = 0.0;// [deg]

	// partial of QBAR with respect to range with constraints of E = EN and MACH = PHIM
	constexpr double PQBWRR = 0.006;// [psf/ft]

	// partial of EN with respect to range at R2MAX
	constexpr double PEWRR = 0.52;// [1]

	// gain used to compute QBNZUL and QBNZLL
	constexpr double QBG1 = 0.075;// [s^-1]

	// gain used to compute QBNZUL and QBNZLL
	constexpr double QBG2 = 0.0625;// [s-g/psf]

	// energy delta from the nominal energy line slope for the S-turn
	constexpr double EDELNZ[2] = {4000.0, 4000.0};// [ft] TBD

	// constant used in computing E max
	constexpr double DEL_R_EMAX[2] = {54000.0, 54000.0};// [ft] TBD

	// constant used in determination of EMAX
	constexpr double EDELC1 = 1.0;// [1]

	// constant used in determination of EMAX
	constexpr double EDELC2 = 1.0;// [1]

	// gain used in computing of EOWNZUL
	constexpr double GEUL = 0.1;// [s^-1]

	// gain used in computing of EOWNZLL
	constexpr double GELL = 0.1;// [s^-1]

	// gain used in computing of EOWNZUL
	constexpr double GEHDUL = 0.01;// [g/fps]

	// gain used in computing of EOWNZLL
	constexpr double GEHDLL = 0.01;// [g/fps]

	// NZC rate limit
	constexpr double DNZCDL = 0.1;// [g/s]

	// Mach at which speedbrake modulation begins
	constexpr double DSBCM = 0.95;// [1]

	// supersonic fixed speedbrake deflection
	constexpr double DSBSUP = 65.0;// [deg]

	// constant used to calculate DSBCLL
	constexpr double DSBLLS = 650.0;// [deg]

	// constant used to calculate DSBCUL
	constexpr double DSBULS = -336.0;// [deg]

	// maximum value of DSBC
	constexpr double DSBLIM = 98.6;// [deg]

	// speedbrake proportional gain on QBERR
	constexpr double GSBE = 1.5;// [deg/psf]

	// limit on DSBI
	constexpr double DSBIL = 20.0;// [deg]

	// gain on QBERR integral in computing speedbrake command
	constexpr double GSBI = 0.1;// [deg/psf^-1]

	// nominal speedbrake command
	constexpr double DSBNOM = 65.0;// [deg]

	// maximum EOW error for speedbrakes out
	constexpr double DEMXSB = 10000.0;// [ft]

	// heading error gain for computing PHIC
	constexpr double GPHI = 2.5;// [1]

	// limit of RERRC
	constexpr double RERRLM = 7000.0;// [ft]

	// gain on RCIR in computing HA roll angle command
	constexpr double GR = 0.005;// [deg/ft]

	// gain on dRCIR/dt in computing HA roll angle command
	constexpr double GRDOT = 0.2;// [deg/fps]


	double RES180( double v )
	{
		while (v > 180.0) v -= 360.0;
		while (v <= -180.0) v += 360.0;
		return v;
	}

	TAEMGuidance::TAEMGuidance( SimpleGPCSystem* _gpc ):SimpleGPCSoftware( _gpc, "TAEMGuidance" )
	{
		IRESET = 1;
		NZC = 0.0;
		PHI0 = 0.0;
		PHILIM = 0.0;
		DNZUL = 0.0;
		DNZLL = 0.0;
		QBARF = 0.0;
		QBD = 0.0;
		DSBI = 0.0;
		DSBC = 0.0;

		PSC = 0.0;

		step = 0.96;

		ISR = RFTC;

		// I-LOADs init
		HALI[0] = 10018.0;
		HALI[1] = 10018.0;
		HFTC[0] = 12018.0;
		HFTC[1] = 12018.0;
		HMEP[0] = 6000.0;
		HMEP[1] = 6000.0;
		PBHC[0] = 78161.826;
		PBHC[1] = 81000.0;
		PBGC[0] = 0.1112666;
		PBGC[1] = 0.1112666;
		PBRC[0] = 256527.82;
		PBRC[1] = 282035.6903;
		CUBIC_C3[0] = -1.64854e-07;
		CUBIC_C3[1] = -2.15359e-08;
		CUBIC_C4[0] = -8.51609e-13;
		CUBIC_C4[1] = -8.44417E-13;
		EOW_SPT[0] = 76068.0;
		EOW_SPT[1] = 76068.0;
		EN_C1[0][0] = 949.0;
		EN_C1[0][1] = 15360.0;
		EN_C1[1][0] = 949.0;
		EN_C1[1][1] = 15360.0;
		EN_C2[0][0] = 0.6005;
		EN_C2[0][1] = 0.46304;
		EN_C2[1][0] = 0.6005;
		EN_C2[1][1] = 0.46304;
		R2MAX = 115000.0;
		ESHFMX = 20000.0;
		ES1[0] = 4523.0;
		ES1[1] = 4523.0;
		EDRS[0] = 0.69946182;
		EDRS[1] = 0.69946182;
		EMEP_C1[0][0] = -3263.0;
		EMEP_C1[0][1] = 12088.0;
		EMEP_C1[1][0] = -3263.0;
		EMEP_C1[1][1] = 12088.0;
		EMEP_C2[0][0] = 0.51554944;
		EMEP_C2[0][1] = 0.265521;
		EMEP_C2[1][0] = 0.51554944;
		EMEP_C2[1][1] = 0.265521;
		EMOHC1[0] = -3894.0;
		EMOHC1[1] = -3894.0;
		EMOHC2[0] = 0.51464;
		EMOHC2[1] = 0.51464;
		YERRLM = 160.0;
		GY = 0.04;
		GYDOT = 0.4;
		DNZLC1 = -0.5;
		DNZLC2 = -0.5;
		DNZUC1 = 0.5;
		DNZUC2 = 0.5;
		DR3 = 5300.0;
		DR4 = 2000.0;
		RFMN = 5000.0;
		RFMX = 14000.0;
		PSRF = 90.0;
		DHOH1 = 0.11;
		DHOH2 = 35705.0;
		DHOH3 = 6000.0;
		DRFK = -3.0;
		PHAVGC = 63.33;
		PHAVGLL = 30.0;
		PHAVGS = 13.33;
		PHAVGUL = 50.0;
		PHILM0 = 50.0;
		PHILM1 = 50.0;
		PHILM2 = 60.0;
		PHILM3 = 30.0;
		PHILMSUP = 30.0;
		PHILS = -300.0;
		PHIM = 0.95;
		PHILMC = 100.0;
		PHILM4 = 60.0;
		QBARDL = 20.0;
		CQG = 0.5583958;
		CQDG = 0.31886857;
		CDEQD = 0.68113143;
		DEL_H1 = 0.19;
		DEL_H2 = 900.0;
		Y_RANGE1 = 0.18;
		Y_RANGE2 = 800.0;
		GAMMA_COEF1 = 0.0007;
		GAMMA_COEF2 = 3.0;
		QB_ERROR2 = 24.0;
		H_REF1 = 10000.0;
		H_REF2 = 5000.0;
		HMIN3 = 7000.0;
		P2TRNC1 = 1.1;
		ENBIAS = 10000.0;
		RMINST[0] = 122204.6;
		RMINST[1] = 122204.6;
		PSSTRN = 200.0;
		PSOHAL = 200.0;
		return;
	}

	TAEMGuidance::~TAEMGuidance( void )
	{
		return;
	}

	bool TAEMGuidance::OnParseLine( const char* keyword, const char* value )
	{
		if (!_strnicmp( keyword, "IRESET", 6 ))
		{
			unsigned int tmp = 0;
			sscanf_s( value, "%u", &tmp );
			if (tmp <= 1) IRESET = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "NZC", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			NZC = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "PHILIM", 6 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			PHILIM = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DNZUL", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DNZUL = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DNZLL", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DNZLL = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "QBARF", 5 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			QBARF = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "QBD", 3 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			QBD = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DSBI", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DSBI = tmp;
			return true;
		}
		else if (!_strnicmp( keyword, "DSBC", 4 ))
		{
			double tmp = 0.0;
			sscanf_s( value, "%lf", &tmp );
			DSBC = tmp;
			return true;
		}
		else return false;
	}

	void TAEMGuidance::OnSaveState( FILEHANDLE scn ) const
	{
		oapiWriteScenario_int( scn, "IRESET", IRESET );
		oapiWriteScenario_float( scn, "NZC", NZC );
		oapiWriteScenario_float( scn, "PHI0", PHI0 );
		oapiWriteScenario_float( scn, "PHILIM", PHILIM );
		oapiWriteScenario_float( scn, "DNZUL", DNZUL );
		oapiWriteScenario_float( scn, "DNZLL", DNZLL );
		oapiWriteScenario_float( scn, "QBARF", QBARF );
		oapiWriteScenario_float( scn, "QBD", QBD );
		oapiWriteScenario_float( scn, "DSBI", DSBI );
		oapiWriteScenario_float( scn, "DSBC", DSBC );
		return;
	}

	void TAEMGuidance::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
	{
		double EN_C1[4];
		double EN_C2[4];
		double EMEP_C1[4];
		double EMEP_C2[4];
		GetValILOAD( "HALI", ILOADs, 2, HALI );
		GetValILOAD( "HFTC", ILOADs, 2, HFTC );
		GetValILOAD( "HMEP", ILOADs, 2, HMEP );
		GetValILOAD( "PBHC", ILOADs, 2, PBHC );
		GetValILOAD( "PBGC", ILOADs, 2, PBGC );
		GetValILOAD( "PBRC", ILOADs, 2, PBRC );
		GetValILOAD( "CUBIC_C3", ILOADs, 2, CUBIC_C3 );
		GetValILOAD( "CUBIC_C4", ILOADs, 2, CUBIC_C4 );
		GetValILOAD( "EOW_SPT", ILOADs, 2, EOW_SPT );
		GetValILOAD( "EN_C1", ILOADs, 4, EN_C1 );
		GetValILOAD( "EN_C2", ILOADs, 4, EN_C2 );
		GetValILOAD( "R2MAX", ILOADs, R2MAX );
		GetValILOAD( "ESHFMX", ILOADs, ESHFMX );
		GetValILOAD( "ES1", ILOADs, 2, ES1 );
		GetValILOAD( "EDRS", ILOADs, 2, EDRS );
		GetValILOAD( "EMEP_C1", ILOADs, 4, EMEP_C1 );
		GetValILOAD( "EMEP_C2", ILOADs, 4, EMEP_C2 );
		GetValILOAD( "EMOHC1", ILOADs, 2, EMOHC1 );
		GetValILOAD( "EMOHC2", ILOADs, 2, EMOHC2 );
		GetValILOAD( "YERRLM", ILOADs, YERRLM );
		GetValILOAD( "GY", ILOADs, GY );
		GetValILOAD( "GYDOT", ILOADs, GYDOT );
		GetValILOAD( "DNZLC1", ILOADs, DNZLC1 );
		GetValILOAD( "DNZLC2", ILOADs, DNZLC2 );
		GetValILOAD( "DNZUC1", ILOADs, DNZUC1 );
		GetValILOAD( "DNZUC2", ILOADs, DNZUC2 );
		GetValILOAD( "DR3", ILOADs, DR3 );
		GetValILOAD( "DR4", ILOADs, DR4 );
		GetValILOAD( "RFMN", ILOADs, RFMN );
		GetValILOAD( "RFMX", ILOADs, RFMX );
		GetValILOAD( "PSRF", ILOADs, PSRF );
		GetValILOAD( "DHOH1", ILOADs, DHOH1 );
		GetValILOAD( "DHOH2", ILOADs, DHOH2 );
		GetValILOAD( "DHOH3", ILOADs, DHOH3 );
		GetValILOAD( "DRFK", ILOADs, DRFK );
		GetValILOAD( "PHAVGC", ILOADs, PHAVGC );
		GetValILOAD( "PHAVGLL", ILOADs, PHAVGLL );
		GetValILOAD( "PHAVGS", ILOADs, PHAVGS );
		GetValILOAD( "PHAVGUL", ILOADs, PHAVGUL );
		GetValILOAD( "PHILM0", ILOADs, PHILM0 );
		GetValILOAD( "PHILM1", ILOADs, PHILM1 );
		GetValILOAD( "PHILM2", ILOADs, PHILM2 );
		GetValILOAD( "PHILM3", ILOADs, PHILM3 );
		GetValILOAD( "PHILMSUP", ILOADs, PHILMSUP );
		GetValILOAD( "PHILS", ILOADs, PHILS );
		GetValILOAD( "PHIM", ILOADs, PHIM );
		GetValILOAD( "PHILMC", ILOADs, PHILMC );
		GetValILOAD( "PHILM4", ILOADs, PHILM4 );
		GetValILOAD( "QBARDL", ILOADs, QBARDL );
		GetValILOAD( "CQG", ILOADs, CQG );
		GetValILOAD( "CQDG", ILOADs, CQDG );
		GetValILOAD( "CDEQD", ILOADs, CDEQD );
		GetValILOAD( "DEL_H1", ILOADs, DEL_H1 );
		GetValILOAD( "DEL_H2", ILOADs, DEL_H2 );
		GetValILOAD( "Y_RANGE1", ILOADs, Y_RANGE1 );
		GetValILOAD( "Y_RANGE2", ILOADs, Y_RANGE2 );
		GetValILOAD( "GAMMA_COEF1", ILOADs, GAMMA_COEF1 );
		GetValILOAD( "GAMMA_COEF2", ILOADs, GAMMA_COEF2 );
		GetValILOAD( "QB_ERROR2", ILOADs, QB_ERROR2 );
		GetValILOAD( "H_REF1", ILOADs, H_REF1 );
		GetValILOAD( "H_REF2", ILOADs, H_REF2 );
		GetValILOAD( "HMIN3", ILOADs, HMIN3 );
		GetValILOAD( "P2TRNC1", ILOADs, P2TRNC1 );
		GetValILOAD( "ENBIAS", ILOADs, ENBIAS );
		GetValILOAD( "RMINST", ILOADs, 2, RMINST );
		GetValILOAD( "PSSTRN", ILOADs, PSSTRN );
		GetValILOAD( "PSOHAL", ILOADs, PSOHAL );

		this->EN_C1[0][0] = EN_C1[0];
		this->EN_C1[0][1] = EN_C1[1];
		this->EN_C1[1][0] = EN_C1[2];
		this->EN_C1[1][1] = EN_C1[3];

		this->EN_C2[0][0] = EN_C2[0];
		this->EN_C2[0][1] = EN_C2[1];
		this->EN_C2[1][0] = EN_C2[2];
		this->EN_C2[1][1] = EN_C2[3];

		this->EMEP_C1[0][0] = EMEP_C1[0];
		this->EMEP_C1[0][1] = EMEP_C1[1];
		this->EMEP_C1[1][0] = EMEP_C1[2];
		this->EMEP_C1[1][1] = EMEP_C1[3];

		this->EMEP_C2[0][0] = EMEP_C2[0];
		this->EMEP_C2[0][1] = EMEP_C2[1];
		this->EMEP_C2[1][0] = EMEP_C2[2];
		this->EMEP_C2[1][1] = EMEP_C2[3];
		return;
	}

	void TAEMGuidance::OnPreStep( double simt, double simdt, double mjd )
	{
		TG_END = ReadCOMPOOL_IS( SCP_TG_END );
		if (TG_END == 1) return;

		step += simdt;
		if (step < 0.96) return;

		// read inputs
		IPHASE = ReadCOMPOOL_IS( SCP_IPHASE );
		H = ReadCOMPOOL_SD( SCP_H );
		HDOT = ReadCOMPOOL_SD( SCP_HDOT );
		IGS = ReadCOMPOOL_IS( SCP_IGS );
		IGI = ReadCOMPOOL_IS( SCP_IGI );
		OVHD = ReadCOMPOOL_IS( SCP_OVHD );
		RWID = ReadCOMPOOL_IS( SCP_RWID );
		RWID0 = ReadCOMPOOL_IS( SCP_RWID0 );
		MEP = ReadCOMPOOL_IS( SCP_MEP );
		X = ReadCOMPOOL_SD( SCP_X );
		Y = ReadCOMPOOL_SD( SCP_Y );
		XDOT = ReadCOMPOOL_SD( SCP_XDOT );
		YDOT = ReadCOMPOOL_SD( SCP_YDOT );
		COSPHI = ReadCOMPOOL_SD( SCP_COSPHI );
		PSD = ReadCOMPOOL_SD( SCP_PSD );
		GAMMA = ReadCOMPOOL_SD( SCP_GAMMA );
		QBAR = ReadCOMPOOL_SD( SCP_QBAR );
		WEIGHT = ReadCOMPOOL_SD( SCP_WEIGHT );
		WT_GS1 = ReadCOMPOOL_SD( SCP_WT_GS1 );
		MACH = ReadCOMPOOL_SD( SCP_MACH );
		V = ReadCOMPOOL_SD( SCP_VE );
		VH = ReadCOMPOOL_SD( SCP_VG );// INFO VH is the same as VG
		XA = ReadCOMPOOL_V( SCP_X_ZERO, IGI, 2 );// INFO XA is the same as X_ZERO
		GAMSGS = ReadCOMPOOL_V( SCP_GAMMA_REF_1, IGS, 2 );
		TGGS = tan( GAMSGS * RAD );// INFO TGGS calculated at runtime from GAMMA_REF_1
		RTURN = ReadCOMPOOL_SD( SCP_RTURN );
		PSHA = ReadCOMPOOL_SD( SCP_PSHA );
		YSGN = ReadCOMPOOL_SD( SCP_YSGN );
		RF = ReadCOMPOOL_SD( SCP_RF );
		PSHARS = ReadCOMPOOL_SD( SCP_PSHARS );
		RF0 = ReadCOMPOOL_SD( SCP_RF0 );
		R1 = ReadCOMPOOL_SD( SCP_R1 );
		R2 = ReadCOMPOOL_SD( SCP_R2 );
		RMOH = ReadCOMPOOL_SD( SCP_RMOH );

		TGEXEC( step/*simdt*/ );

		//sprintf_s( oapiDebugString(), 256, "DSBC_AT%.2f NZC%.2f PHIC_AT%.2f DPSAC%.2f RPRED%.2f DRPRED%.2f DELRNG%.2f EAS_CMD%.2f HERROR%.2f", DSBC_AT, NZC, PHIC_AT, DPSAC, RPRED, DRPRED, DELRNG, EAS_CMD, HERROR );
		//sprintf_s( oapiDebugString(), 256, "PSHA%.2f RTURN%.2f NZC%.2f PHIC_AT%.2f RPRED%.2f RPRED2:%.2f RPRED3:%.2f DRPRED%.2f DELRNG%.2f HERROR%.2f", PSHA, RTURN, NZC, PHIC_AT, RPRED, RPRED2, RPRED3, DRPRED, DELRNG, HERROR );
		//sprintf_s( oapiDebugString(), 256, "EN-EOW%.2f QBAR%.2f QBARF%.2f QBREF%.2f QBERR%.2f GAMMA%.2f tg-1(DHDRRF)%.2f HERROR%.2f", EN - EOW, QBAR, QBARF, QBREF, QBERR, GAMMA, atan( DHDRRF ) * DEG, HERROR );

		// write outputs
		WriteCOMPOOL_IS( SCP_IGS, IGS );
		//WriteCOMPOOL_IS( SCP_OVHD, OVHD );
		WriteCOMPOOL_IS( SCP_RWID0, RWID0 );
		WriteCOMPOOL_IS( SCP_IPHASE, IPHASE );
		WriteCOMPOOL_IS( SCP_TG_END, TG_END );
		WriteCOMPOOL_IS( SCP_MEP, MEP );
		WriteCOMPOOL_SD( SCP_DSBC_AT, static_cast<float>(DSBC_AT) );
		WriteCOMPOOL_SD( SCP_NZC, static_cast<float>(NZC) );
		WriteCOMPOOL_SD( SCP_PHIC_AT, static_cast<float>(PHIC_AT) );
		WriteCOMPOOL_SD( SCP_DPSAC, static_cast<float>(DPSAC) );
		WriteCOMPOOL_SD( SCP_RPRED, static_cast<float>(RPRED) );
		WriteCOMPOOL_SD( SCP_RF, static_cast<float>(RF) );
		WriteCOMPOOL_SD( SCP_XHAC, static_cast<float>(XHAC) );
		WriteCOMPOOL_SD( SCP_RTURN, static_cast<float>(RTURN) );
		WriteCOMPOOL_SD( SCP_YSGN, static_cast<float>(YSGN) );
		WriteCOMPOOL_SD( SCP_PSHA, static_cast<float>(PSHA) );
		WriteCOMPOOL_SD( SCP_RCIR, static_cast<float>(RCIR) );
		WriteCOMPOOL_SD( SCP_EOW, static_cast<float>(EOW) );
		WriteCOMPOOL_SD( SCP_EN, static_cast<float>(EN) );
		WriteCOMPOOL_SD( SCP_ES, static_cast<float>(ES) );
		WriteCOMPOOL_SD( SCP_EMEP, static_cast<float>(EMEP) );
		WriteCOMPOOL_SD( SCP_EMOH, static_cast<float>(EMOH) );
		WriteCOMPOOL_SD( SCP_HERROR, static_cast<float>(HERROR) );
		WriteCOMPOOL_SD( SCP_PSC, static_cast<float>(PSC) );

		step = 0.0;
		return;
	}

	bool TAEMGuidance::OnMajorModeChange( unsigned int newMajorMode )
	{
		if (newMajorMode == 305) return true;
		else return false;
	}

	void TAEMGuidance::TGEXEC( double dt )
	{
		if ((IRESET == 1) || (RWID != RWID0)) TGINIT();
		TGXHAC();
		GTP();
		TGCOMP( dt );
		TGTRAN();
		TGNZC( dt );
		TGSBC( dt );
		TGPHIC( dt );
		return;
	}

	void TAEMGuidance::TGINIT( void )
	{
		//if (IRESET == 1) RWID0 = RWID;
		ISR = RFTC/* / DTG*/;// HACK subtract dt in TGPHIC
		MEP = 0;
		RF = RF0;
		DSBI = 0.0;
		//OHALRT = 0;
		PHILIM = PHILM1;
		DNZUL = DNZUC1;
		DNZLL = DNZLC1;
		QBARF = QBAR;
		QBD = 0.0;
		IPHASE = 1;
		TG_END = 0;
		IRESET = 0;

		RTURN = /*ReadCOMPOOL_SD( SCP_RTURN );*/RF0;// HACK should come from EGRT?
		return;
	}

	void TAEMGuidance::TGXHAC( void )
	{
		double XFTC = 0.0;
		double XMEP = 0.0;

		/*if (V <= VTOGL)
		{
			if (OVHD == 1) OVHD = 0;
			else
			{
				OVHD = 1;
				YSGN = -sign( Y );
			}
			PSHA = PSHARS;
			VTOGL = 0.0;
		}*/

		if (RWID != RWID0)
		{
			PSHA = PSHARS;
			if (OVHD == 1) YSGN = -sign( Y );
		}

		RWID0 = RWID;

		/*if ((OHALRT == 1) && (ORAHAC[RWID - 1] == 0) && (OVHD == 1))
		{
			OVHD = 0;
			PSHA = PSHARS;
		}*/

		if ((OVHD == 0) && (IPHASE < 2)) YSGN = sign( Y );

		if (WEIGHT > WT_GS1) IGS = 2;
		else IGS = 1;

		// HACK currently changing IGI directly in SPEC 50
		/*if (GI_CHANGE == 1) IGI = 2;
		else IGI = 1;*/

		XFTC = XA + (HFTC[IGS - 1] / TGGS);
		XALI = XA + (HALI[IGS - 1] / TGGS);
		XMEP = XA + (HMEP[IGS - 1] / TGGS);

		if (MEP == 1) XHAC = XMEP;
		else XHAC = XFTC;

		RPRED3 = -XHAC + DR3;
		return;
	}

	void TAEMGuidance::GTP( void )
	{
		double SIGNY = 0.0;// sign of vehicle Y position in runway coordinates [1]
		double RTAN = 0.0;// straight line distance to WP1 [ft]
		double PST = 0.0;// heading to WP1 [deg]
		double PSHAN = 0.0;// new PSHA [deg]
		double PHAVG = 0.0;// average PHI turning to WP1 [deg]
		double RTAC = 0.0;// acquisition turn radius [ft]
		double ARCAC = 0.0;// acquisition turn arc length [ft]
		double A = 0.0;
		double B = 0.0;
		double RC = 0.0;// range from end of acquisition turn to WP1 [ft]

		XCIR = XHAC - X;
		/*if ((IPHASE == 3) && (XCIR < DR4))
		{
			RPRED = sqrt( (X * X) + (Y * Y) );
			return;
		}*/

		// eq set 1
		SIGNY = sign( Y );
		YCIR = (YSGN * RF) - Y;
		RCIR = sqrt( (XCIR * XCIR) + (YCIR * YCIR) );
		if (RCIR > RTURN)
		{
			RTAN = sqrt( (RCIR * RCIR) - (RTURN * RTURN) );

			// HACK estimate time to HAC
			double RTANTRN = sqrt( ((RTURN * P2TRNC1) * (RTURN * P2TRNC1)) - (RTURN * RTURN) );// [ft]
			double P2TRNT = max(0.0,(RTAN - RTANTRN) / VH);// [sec]
			WriteCOMPOOL_SD( SCP_P2TRNT, static_cast<float>(P2TRNT) );
		}
		else RTAN = 0.0;

		// eq set 2
		PSC = atan2( YCIR, XCIR ) * DEG;
		PST = PSC - (YSGN * atan2( RTURN, RTAN ) * DEG);
		PST = RES180( PST );
		DPSAC = RES180( PST - PSD );
		PSHAN = -PST * YSGN;
		if (((PSHA > (PSHARS + 1.0)) || (PSHAN < -1.0) || (YSGN != SIGNY)) && (PSHA > 90.0)) PSHAN += 360.0;
		PSHA = PSHAN;
		RTURN = RF + ((R1 + (R2 * PSHA)) * PSHA);
		RPRED2 = ((RF + ((0.5 * R1) + (0.333333 * R2 * PSHA)) * PSHA) * PSHA * RAD/*DTR*/) - XHAC;

		// delayed this check so PSC and DPSAC is calculated in IPHASE = 3
		if ((IPHASE == 3) && (XCIR < DR4))
		{
			RPRED = sqrt( (X * X) + (Y * Y) );
			return;
		}

		if (IPHASE < 2)
		{
			// eq set 3
			PHAVG = PHAVGC - PHAVGS * MACH;
			PHAVG = range( PHAVGLL, PHAVG, PHAVGUL );
			RTAC = (V * VH) / (G * MPS2FPS * tan( PHAVG * RAD/*DTR*/ ) );
			ARCAC = RTAC * fabs( DPSAC ) * RAD/*DTR*/;

			// eq set 4
			A = RTAC * (1.0 - cos( DPSAC * RAD ));
			B = RTAN - (RTAC * fabs( sin( DPSAC * RAD ) ));
			RC = sqrt( (A * A) + (B * B) );
			RTAN = ARCAC + RC;
		}

		RPRED = RPRED2 + RTAN;
		return;
	}

	void TAEMGuidance::TGCOMP( double dt )
	{
		// eq set 1
		DRPRED = RPRED + XALI;
		EOW = H + ((V * V) / (2.0 * G * MPS2FPS));

		// eq set 2
		if (DRPRED < EOW_SPT[IGS - 1]) IEL = 2;
		else IEL = 1;

		EN = EN_C1[IGS - 1][IEL - 1] + (DRPRED * EN_C2[IGS - 1][IEL - 1]) - range( 0.0, EN_C2[IGS - 1][0] * (RPRED2 - R2MAX), ESHFMX );

		// eq set 4
		double HREF = 0.0;

		if (DRPRED > PBRC[IGS - 1]) HREF = PBHC[IGS - 1] + (PBGC[IGS - 1] * (DRPRED - PBRC[IGS - 1]));
		else
		{
			HREF = HALI[IGS - 1] - (TGGS * DRPRED);
			if (DRPRED > 0.0) HREF += (DRPRED * DRPRED) * (CUBIC_C3[IGS - 1] + (DRPRED * CUBIC_C4[IGS - 1]));
		}

		// eq set 5
		double HREFOH = 0.0;// altitude below which RF is adjusted if PSHA > PSRF [ft]
		double DRF = 0.0;// RF adjustment

		if (DRPRED > PBRCQ[IGS - 1]) QBREF = range( QBRLL[IGS - 1], QBRLL[IGS - 1] + (QBC1[IGS - 1] * (DRPRED - PBRCQ[IGS - 1])), QBRML[IGS - 1] );
		else QBREF = range( QBRLL[IGS - 1], QBRUL[IGS - 1] + (QBC2[IGS - 1] * DRPRED), QBRUL[IGS - 1] );
		if ((IPHASE == 2) && (PSHA > PSRF))
		{
			HREFOH = HREF - range( 0.0, DHOH1 * (DRPRED - DHOH2), DHOH3 );
			DRF = (DRFK * (HREFOH - H)) / (PSHA * RAD/*DTR*/);
			RF = range( RFMN, RF + DRF, RFMX );
		}
		HERROR = HREF - H;
		if (DRPRED > PBRC[IGS - 1]) DHDRRF = -PBGC[IGS - 1];
		else DHDRRF = -range( PBGC[IGS - 1], -TGGS + (DRPRED * (2 * CUBIC_C3[IGS - 1] + (3 * CUBIC_C4[IGS - 1] * DRPRED))), -TGGS );
		DELRNG = HERROR / DHDRRF;

		// eq set 6
		double QBARD = 0.0;
		QBARD = range( -QBARDL, CQG * (QBAR - QBARF), QBARDL );
		QBARF += QBARD * dt/*DTG*/;// HACK replaced fixed cycle length for dt
		QBD = (CDEQD * QBD) + (CQDG * QBARD);
		QBERR = QBREF - QBARF;
		//EAS_CMD = 17.1865 * sqrt( QBREF );
		return;
	}

	void TAEMGuidance::TGTRAN( void )
	{
		if (IPHASE == 3)
		{
			if (((fabs( HERROR ) < ((H * DEL_H1) - DEL_H2)) && (fabs( Y ) < ((H * Y_RANGE1) - Y_RANGE2)) &&
				(fabs( GAMMA - GAMSGS ) < ((H * GAMMA_COEF1) - GAMMA_COEF2)) && (fabs( QBERR ) < QB_ERROR2) && (H_REF1 > H))
				|| (H < H_REF2)) TG_END = 1;
		}
		else
		{
			if ((RPRED < RPRED3) || (H < HMIN3))
			{
				// eq set 1
				IPHASE = 3;
				PHI0 = PHIC;
				PHILIM = PHILM3;
				DNZUL = DNZUC2;
				DNZLL = DNZLC2;
			}
			else
			{
				// HACK moved ES and EMEP calc to here so they are available in IPHASE 0 and 2, for display in VERT SITs
				ES = ES1[IGS - 1] + (DRPRED * EDRS[IGS - 1]);
				EMEP = EMEP_C1[IGS - 1][IEL - 1] + (DRPRED * EMEP_C2[IGS - 1][IEL - 1]);
				switch (IPHASE)
				{
					case 0:
						if (EOW < (EN + ENBIAS))
						{
							// eq set 2
							IPHASE = 1;
							PHILIM = PHILM1;
						}
						break;
					case 1:
						if ((PSHA < PSSTRN) && (DRPRED > RMINST[IGS - 1]))
						{
							// eq set 3
							double SPSI = 0.0;

							//ES = ES1[IGS - 1] + (DRPRED * EDRS[IGS - 1]);
							if (EOW > ES)
							{
								IPHASE = 0;
								PHILIM = PHILM0;
								S = -YSGN;
								SPSI = S * PSD;
								if ((SPSI < 0.0) && (PSHA < 90.0)) S = -S;
							}
						}
						//EMEP = EMEP_C1[IGS - 1][IEL - 1] + (DRPRED * EMEP_C2[IGS - 1][IEL - 1]);// moved up
						EMOH = EMOHC1[IGS - 1] + (EMOHC2[IGS - 1] * DRPRED);
						if ((EOW < EMEP) && (MEP == 0))
						{
							// TODO SM alert "SW TO MEP"
							//MEP = 1;// disabled auto switching to MEP
						}
						if ((EOW < EMOH) && (PSHA > PSOHAL) && (RPRED > RMOH) && (OVHD == 1))// added OVHD check
						{
							// TODO SM alert "OTT ST IN"
							//OHALRT = 1;
						}
						if (RCIR < (P2TRNC1 * RTURN))
						{
							IPHASE = 2;
							PHILIM = PHILM2;
						}
						break;
					/*case 2:
						break;*/
				}
			}
		}
		return;
	}

	void TAEMGuidance::TGNZC( double dt )
	{
		// eq set 1
		double GDH = 0.0;// [1]
		double HDREF = 0.0;// HDOT reference [fps]
		double HDERR = 0.0;// HDOT error [fps]
		double DNZC = 0.0;// unlimited normal acceleration command [g]
		double MXQBWT = 0.0;// [psf/slug]
		double QBLL = 0.0;// [psf]
		double QBMNNZ = 0.0;// minimum dynamic pressure profile
		double QBMXNZ = 0.0;// maximum dynamic pressure profile

		GDH = midval( GDHC - (GDHS * H), GDHLL, GDHUL );
		HDREF = VH * DHDRRF;
		HDERR = HDREF - HDOT;
		DNZC = DNZCG * GDH * (HDERR + (HDREQG * GDH * HERROR));
		if (MACH < QMACH2) MXQBWT = midval( QBWT1 + (QBMSL1 * (MACH - QMACH1)), QBWT2, QBWT1 );
		else MXQBWT = midval( QBWT2 + (QBMSL2 * (MACH - QMACH2)), QBWT2, QBWT3 );
		QBLL = MXQBWT * WEIGHT;
		QBMNNZ = QBLL / max(COSPHI, CPMIN);
		if (MACH > QBM1) QBMXNZ = midval( QBMX2 + (QBMXS2 * (MACH - QBM2)), QBMX2, QBMX3 );
		else QBMXNZ = midval( QBMX2 + (QBMXS1 * (MACH - QBM1)), QBMX2, QBMX1 );
		if ((EQLOWL < EOW) && (EOW < EQLOWU) && (PSHA > PSOHQB))
			QBMXNZ = midval( QBREF2[IGS - 1] - (PQBWRR * (RPRED2 - R2MAX + ((EOW - EN) / PEWRR))), QBMNNZ, QBMXNZ );

		// eq set 2
		double QBNZUL = 0.0;// maximum dynamic pressure [psf]
		double QBNZLL = 0.0;// minimum dynamic pressure [psf]

		QBNZUL = -((QBG1 * (QBMNNZ - QBARF)) - QBD) * QBG2;
		QBNZLL = -((QBG1 * (QBMXNZ - QBARF)) - QBD) * QBG2;

		if (IPHASE == 3) NZC = midval( DNZC, QBNZLL, QBNZUL );
		else
		{
			// eq set 3
			double EMAX = 0.0;
			double EMIN = 0.0;
			double EOWNZUL = 0.0;
			double EOWNZLL = 0.0;
			double DNZCL = 0.0;
			double DNZCD = 0.0;

			EMAX = EN + (EDELNZ[IGS - 1] * midval( DRPRED / DEL_R_EMAX[IGS - 1], EDELC1, EDELC2 ));
			EMIN = EN - EDELNZ[IGS - 1];
			EOWNZUL = ((GEUL * GDH * (EMAX - EOW)) + HDERR) * GEHDUL * GDH;
			EOWNZLL = ((GELL * GDH * (EMIN - EOW)) + HDERR) * GEHDLL * GDH;
			DNZCL = midval( DNZC, EOWNZLL, EOWNZUL );
			DNZCL = midval( DNZCL, QBNZLL, QBNZUL );
			DNZCD = midval( (DNZCL - NZC) * CQG, -DNZCDL, DNZCDL );
			NZC = NZC + DNZCD * dt/*DTG*/;// HACK replaced fixed cycle length for dt
		}

		NZC = midval( NZC, DNZLL, DNZUL );
		return;
	}

	void TAEMGuidance::TGSBC( double dt )
	{
		if (MACH > DSBCM)
		{
			DSBC_AT = DSBSUP;
			return;
		}

		// eq set 1
		double DSBCLL = 0.0;// lower command limit
		double DSBCUL = 0.0;// upper command limit

		DSBCLL = range( 0.0, DSBSUP + DSBLLS * (MACH - DSBCM), DSBSUP );
		DSBCUL = range( DSBSUP, DSBSUP + DSBULS * (MACH - DSBCM), DSBLIM );

		// eq set 2
		double DSBE = 0.0;// [deg]

		if (IPHASE == 0) DSBC = DSBLIM;
		else
		{
			DSBE = GSBE * QBERR;
			if ((DSBC > DSBCLL) && (DSBC < DSBCUL))
			{
				DSBI = range( -DSBIL, DSBI + GSBI * QBERR * dt/*DTG*/, DSBIL );// HACK replaced fixed cycle length for dt
			}
			DSBC = DSBNOM - DSBE - DSBI;
			if ((EN - EOW) > DEMXSB) DSBC = 0.0;
		}

		// eq set 3
		DSBC_AT = range( DSBCLL, DSBC, DSBCUL );
		return;
	}

	void TAEMGuidance::TGPHIC( double dt )
	{
		double PHILIMIT = range( PHILMSUP, PHILMSUP + (PHILS * (MACH - PHIM)), PHILIM );

		switch (IPHASE)
		{
			case 0:
				// eq set 1
				PHIC = S * PHILIMIT;
				break;
			case 1:
				// eq set 2
				PHIC = GPHI * DPSAC;
				break;
			case 2:
				{
					// eq set 3
					double RERRC = 0.0;// vehicle radial error in HAC [ft]
					double RDOT = 0.0;// HAC radial rate [fps]
					double PHIP2C = 0.0;
					double RDOTRF = 0.0;// reference HAC radial rate [fps]

					RERRC = RCIR - RTURN;
					if (RERRC > RERRLM)
					{
						if (PHILIMIT > PHILM1) PHILIMIT = PHILM1;
						PHIC = GPHI * DPSAC;
					}
					else
					{
						RDOT = -((XCIR * XDOT) + (YCIR * YDOT)) / RCIR;
						PHIP2C = ((VH * VH) - (RDOT * RDOT)) * DEG/*RTD*/ / (G * MPS2FPS * RTURN);
						RDOTRF = -VH * (R1 + (2 * R2 * PSHA)) * DEG/*RTD*/ / RTURN;
						PHIC = YSGN * max(0.0, PHIP2C + (GR * RERRC) + (GRDOT * (RDOT - RDOTRF)));
					}
				}
				break;
			case 3:
				{
					// eq set 4
					double YERRC = 0.0;
					double DPHI = 0.0;

					YERRC = range( -YERRLM, -GY * Y, YERRLM );
					PHIC = YERRC - (GYDOT * YDOT);
					if (fabs( PHIC ) > PHILMC) PHILIMIT = PHILM4;
					if (ISR > 0.0)
					{
						DPHI = (PHIC - PHI0) / ISR;
						ISR -= dt/*1.0*/;// HACK subtract dt instead
						PHIC = PHI0 + DPHI;
						PHI0 = PHIC;
					}
				}
				break;
		}

		PHIC_AT = range( -PHILIMIT, PHIC, PHILIMIT );
		return;
	}
}
