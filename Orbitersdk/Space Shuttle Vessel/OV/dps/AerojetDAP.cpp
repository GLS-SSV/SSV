/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/04/15   GLS
2020/05/10   GLS
2020/05/28   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/07   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/03/29   GLS
2022/04/02   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/05/01   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/09/13   GLS
2022/09/14   GLS
2022/09/29   GLS
2022/10/12   GLS
2022/10/21   GLS
2022/12/01   indy91
2022/12/17   GLS
********************************************/
#include "AerojetDAP.h"
#include "../Atlantis.h"
#include "RHC_SOP.h"
#include "RPTA_SOP.h"
#include "SBTC_SOP.h"
#include <MathSSV.h>
#include <FILT1.h>
#include <FILT2.h>
#include <HYST.h>
#include <SignalSampler.h>
#include <FADER.h>
#include <cassert>


namespace dps
{
	//constexpr double RCSMNT1 = 0.08;// minimum RCS ON time above RCSMXH2 [s]
	//constexpr double RCSMNT2 = 0.32;// minimum RCS ON time below RCSMXH2 [s]
	//constexpr double RCSMXH2 = 125000.0;// maximum altitude to use RCSMNT2 [ft]

	constexpr double DEMAX = 23.0;// [deg]

	constexpr double YADB = 0.33;// [deg/s]
	constexpr double YBDB = 0.35;// [deg/s]

	constexpr double GRCSA = -2.0;
	constexpr double GBETA = 0.5;
	constexpr double WJETHYST = 0.02;// [deg/s]
	constexpr short WJNR1_LOWQ = 2;
	constexpr short WJNR2_LOWQ = 2;
	constexpr short WJNR3_LOWQ = 2;
	constexpr short WJNR4_LOWQ = 2;
	constexpr short WJNR1_HIGHQ = 2;
	constexpr short WJNR2_HIGHQ = 2;
	constexpr short WJNR3_HIGHQ = 3;
	constexpr short WJNR4_HIGHQ = 4;

	constexpr double GDRC_MIN = 1.2;// GRDC lower limit [deg/(deg/s)]
	constexpr double GDRC_MAX = 15.0;// GRDC upper limit [deg/(deg/s)]

	constexpr double DRMAX = 22.5;// [deg]

	constexpr double PE_CUTOFF = 0.5;
	constexpr short NP_HIGH = 4;
	constexpr short NP_LOW = 2;
	constexpr double RADB = 0.33;// [deg/s]
	constexpr double RBDB = 0.35;// [deg/s]

	constexpr double GALRE = 1.0;// [1]

	constexpr double RTHL = 2.0;// roll rate gain logic

	constexpr double GDA_MIN = 0.1;// GDA lower limit [deg/deg/s]
	constexpr double GDA_MAX = 2.0;// GDA upper limit [deg/deg/s]

	constexpr double XKQO = 0.0484;// [deg/deg^2]

	constexpr double DBFRET = 0.0;// retracted body flap position [deg]
	constexpr double GBFMAN = /*1000.0*/100.0;// body flap manual gain (HACK decreased to avoid quick saturation)

	constexpr double GDRTI = 0.02;

	constexpr double GRR = 1.0;
	constexpr double DNWR = 4.0;
	constexpr double KNWMLIN = 0.025;
	constexpr double KNWPAR = 0.0;
	constexpr double GNYR = 1.0;
	constexpr double GNYNWS = 12.0;

	constexpr double GPPANT = 2.0;
	constexpr double GRPANT = 0.5;

	constexpr double GRRCHT = 0.5;// roll RHC trim integrator gain

	constexpr double KDAB_AUTO = 2.0;// TODO
	constexpr double KDAB_CSS = 2.0;// TODO


AerojetDAP::AerojetDAP(SimpleGPCSystem* _gpc) : SimpleGPCSoftware(_gpc, "AerojetDAP")
{
	ALFERR_FDC = 0.0;
	NZERR = 0.0;

	DNWC = 0.0;
	DBF = 0.0;

	DECC = 0.0;
	DBFRC = 0.0;
	DAC = 0.0;
	DRC = 0.0;
	DSBC = 0.0;

	UXCMD = 0;
	UYCMD = 0;
	UZCMD = 0;

	DETM_RHC = 0;
	DATM_RHC = 0;
	DETM_PAN = 0;
	DATM_PAN = 0;
	DRT = 0;

	DETRIM = 0.0;
	ETRIM = 0.0;
	ELFBK = 0.0;

	DBFOFB = 0.0;
	DSBFB = 0.0;
	DSBPC = 0.0;
	DEFB = 0.0;

	DRRCJF = 0.0;
	DAY = 0.0;
	BETAF = 0.0;
	DRPRM = 0.0;

	PC = 0.0;
	PCOR = 0.0;

	DRPHI = 0.0;

	DATRIM = 0.0;
	DRTRIM = 0.0;
	DRTI = 0.0;

	DBF_MAN = 0;

	BANKERR = 0.0;

	P_STAB = 0.0;
	R_STAB = 0.0;

	fltrETRIM = new FILT1( -33.0, 18.0 );
	fltrELFBK = new FILT1( -33.0, 18.0 );
	NZ_FILTER = new FILT1();
	PITCH_SHAPING_FILTER = new FILT1();
	ALFERR_FILT = new FILT1();
	RHC_INT = new FILT1();
	BETA_FILTER = new FILT1();
	fltrGRH = new FILT1();
	fltrDRTRIM = new FILT1( -6.0, 6.0 );
	NY_COMP = new FILT1();
	fltrDATRIM = new FILT1();
	fltrDRTI = new FILT1( -0.1, 0.1 );
	fltrDETR = new FILT1( -1.5, 1.5 );
	fltrDATR = new FILT1( -2.5, 2.5 );
	fltrDBFD = new FILT1( -11.7, 22.55 );
	DNYP_COMP = new FILT2();
	fltrNYBF = new FILT2();

	PITCH_JET_HYSTERESIS = new HYST();
	BF_HYSTER = new HYST( 0.75, 1.0 );
	BF_RATE_CMD = new HYST( 0.9, 1.0 );
	ROLL_JET_HYSTERESIS = new HYST();
	YAW_JET_HYSTERESIS = new HYST();

	BF_DEF_CMD = new SignalSampler( 0.16 );

	TRWY_FADE = new FADER( 100.0 );
	TNWFADE = new FADER( 2.0 );

	LOWQ = true;
	LOWMIDQ = false;
	HIGHQ = false;

	BodyFlapPBIpressed = false;

	// I-LOADs init
	WGT_SD = 6030.0;
	EAS_SD = 180.0;
	LD_REL_BIAS = 10.0;
	NWS_LIM = 9.0;
	ENT_SB_1 = 0.0;
	ENT_SB_2 = 80.0;
	ENT_SB_3 = 65.0;
	ENT_SB_VS = 3200.0;
	ENT_SB_C1 = 800.0;
	ENT_SB_C2 = -0.08;
	ENT_SB_C3 = 11.4285;
	ENT_SB_C4 = 0.0214286;
	DSB_MAX = 98.6;
	MACH_SBH = 10000.0;
	DSB_CLOSED = -9.9;
	DSB_BIAS_U = 0.0;
	DSB_MIN_L = -9.9;
	DSB_MIN_U = 15.0;
	DSB_MIN_M = 25.0;
	ALFERR_LIM = 2.0;
	GQALR = 0.33;
	DPJET_CUTOFF = 1.0;
	PADB = 0.245;
	PBDB = 0.25;
	VCO = 549.125;
	GDQ_MIN = 0.2;
	GDQ_MAX = 5.0;
	MACH_RRXF = 600.0;
	QBARLOWQ = 2.0;
	QBARLOWMIDQ = 10.0;
	QBARHIGHQ = 40.0;
	SBDMN = 950.0;
	SBDMX = 9800.0;
	SBDLIM = 20.0;
}

AerojetDAP::~AerojetDAP()
{
	delete fltrETRIM;
	delete fltrELFBK;
	delete NZ_FILTER;
	delete PITCH_SHAPING_FILTER;
	delete ALFERR_FILT;
	delete RHC_INT;
	delete BETA_FILTER;
	delete fltrGRH;
	delete fltrDRTRIM;
	delete NY_COMP;
	delete fltrDATRIM;
	delete fltrDRTI;
	delete fltrDETR;
	delete fltrDBFD;
	delete fltrDATR;
	delete DNYP_COMP;
	delete fltrNYBF;

	delete PITCH_JET_HYSTERESIS;
	delete BF_HYSTER;
	delete BF_RATE_CMD;
	delete ROLL_JET_HYSTERESIS;
	delete YAW_JET_HYSTERESIS;
}

bool AerojetDAP::OnParseLine( const char* keyword, const char* value )
{
	if (!_strnicmp( keyword, "fltrETRIM", 9 ))
	{
		fltrETRIM->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrELFBK", 9 ))
	{
		fltrELFBK->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "NZ_FILTER", 9 ))
	{
		NZ_FILTER->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "PITCH_SHAPING_FILTER", 20 ))
	{
		PITCH_SHAPING_FILTER->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "ALFERR_FILT", 11 ))
	{
		ALFERR_FILT->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "RHC_INT", 7 ))
	{
		RHC_INT->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "BETA_FILTER", 11 ))
	{
		BETA_FILTER->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrGRH", 7 ))
	{
		fltrGRH->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrDRTRIM", 10 ))
	{
		fltrDRTRIM->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "NY_COMP", 7 ))
	{
		NY_COMP->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrDATRIM", 10 ))
	{
		fltrDATRIM->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrDRTI", 8 ))
	{
		fltrDRTI->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrDETR", 8 ))
	{
		fltrDETR->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrDATR", 8 ))
	{
		fltrDATR->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrDBFD", 8 ))
	{
		fltrDBFD->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "DNYP_COMP", 9 ))
	{
		DNYP_COMP->LoadState( value );
		return true;
	}
	else if (!_strnicmp( keyword, "fltrNYBF", 8 ))
	{
		fltrNYBF->LoadState( value );
		return true;
	}
	else if  (!_strnicmp( keyword, "LOWQ", 4 ))
	{
		int tmp = 0;
		sscanf_s( value, "%d", &tmp );
		LOWQ = (tmp != 0);
		return true;
	}
	else if  (!_strnicmp( keyword, "LOWMIDQ", 7 ))
	{
		int tmp = 0;
		sscanf_s( value, "%d", &tmp );
		LOWMIDQ = (tmp != 0);
		return true;
	}
	else if  (!_strnicmp( keyword, "HIGHQ", 5 ))
	{
		int tmp = 0;
		sscanf_s( value, "%d", &tmp );
		HIGHQ = (tmp != 0);
		return true;
	}
	else return false;
}

void AerojetDAP::OnSaveState( FILEHANDLE scn ) const
{
	char cbuf[256];

	fltrETRIM->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrETRIM", cbuf );

	fltrELFBK->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrELFBK", cbuf );

	NZ_FILTER->SaveState( cbuf );
	oapiWriteScenario_string( scn, "NZ_FILTER", cbuf );

	PITCH_SHAPING_FILTER->SaveState( cbuf );
	oapiWriteScenario_string( scn, "PITCH_SHAPING_FILTER", cbuf );

	ALFERR_FILT->SaveState( cbuf );
	oapiWriteScenario_string( scn, "ALFERR_FILT", cbuf );

	RHC_INT->SaveState( cbuf );
	oapiWriteScenario_string( scn, "RHC_INT", cbuf );

	BETA_FILTER->SaveState( cbuf );
	oapiWriteScenario_string( scn, "BETA_FILTER", cbuf );

	fltrGRH->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrGRH", cbuf );

	fltrDRTRIM->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrDRTRIM", cbuf );

	NY_COMP->SaveState( cbuf );
	oapiWriteScenario_string( scn, "NY_COMP", cbuf );

	fltrDRTI->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrDRTI", cbuf );

	fltrDETR->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrDETR", cbuf );

	fltrDATR->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrDATR", cbuf );

	fltrDBFD->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrDBFD", cbuf );

	DNYP_COMP->SaveState( cbuf );
	oapiWriteScenario_string( scn, "DNYP_COMP", cbuf );

	fltrNYBF->SaveState( cbuf );
	oapiWriteScenario_string( scn, "fltrNYBF", cbuf );

	oapiWriteScenario_int( scn, "LOWQ", LOWQ ? 1 : 0 );
	oapiWriteScenario_int( scn, "LOWMIDQ", LOWMIDQ ? 1 : 0 );
	oapiWriteScenario_int( scn, "HIGHQ", HIGHQ ? 1 : 0 );
	return;
}

void AerojetDAP::Realize()
{
	pRHC_SOP = dynamic_cast<RHC_SOP*> (FindSoftware( "RHC_SOP" ));
	assert( (pRHC_SOP != NULL) && "AerojetDAP::Realize.pRHC_SOP" );

	pRPTA_SOP = dynamic_cast<RPTA_SOP*> (FindSoftware( "RPTA_SOP" ));
	assert( (pRPTA_SOP != NULL) && "AerojetDAP::Realize.pRPTA_SOP" );

	pSBTC_SOP = dynamic_cast<SBTC_SOP*> (FindSoftware( "SBTC_SOP" ));
	assert( (pSBTC_SOP != NULL) && "AerojetDAP::Realize.pSBTC_SOP" );
	return;
}

void AerojetDAP::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	GetValILOAD( "WGT_SD", ILOADs, WGT_SD );
	GetValILOAD( "EAS_SD", ILOADs, EAS_SD );
	GetValILOAD( "LD_REL_BIAS", ILOADs, LD_REL_BIAS );
	GetValILOAD( "NWS_LIM", ILOADs, NWS_LIM );
	GetValILOAD( "ENT_SB_1", ILOADs, ENT_SB_1 );
	GetValILOAD( "ENT_SB_2", ILOADs, ENT_SB_2 );
	GetValILOAD( "ENT_SB_3", ILOADs, ENT_SB_3 );
	GetValILOAD( "ENT_SB_VS", ILOADs, ENT_SB_VS );
	GetValILOAD( "ENT_SB_C1", ILOADs, ENT_SB_C1 );
	GetValILOAD( "ENT_SB_C2", ILOADs, ENT_SB_C2 );
	GetValILOAD( "ENT_SB_C3", ILOADs, ENT_SB_C3 );
	GetValILOAD( "ENT_SB_C4", ILOADs, ENT_SB_C4 );
	GetValILOAD( "DSB_MAX", ILOADs, DSB_MAX );
	GetValILOAD( "MACH_SBH", ILOADs, MACH_SBH );
	GetValILOAD( "DSB_CLOSED", ILOADs, DSB_CLOSED );
	GetValILOAD( "DSB_BIAS_U", ILOADs, DSB_BIAS_U );
	GetValILOAD( "DSB_MIN_L", ILOADs, DSB_MIN_L );
	GetValILOAD( "DSB_MIN_U", ILOADs, DSB_MIN_U );
	GetValILOAD( "DSB_MIN_M", ILOADs, DSB_MIN_M );
	GetValILOAD( "ALFERR_LIM", ILOADs, ALFERR_LIM );
	GetValILOAD( "GQALR", ILOADs, GQALR );
	GetValILOAD( "DPJET_CUTOFF", ILOADs, DPJET_CUTOFF );
	GetValILOAD( "PADB", ILOADs, PADB );
	GetValILOAD( "PBDB", ILOADs, PBDB );
	GetValILOAD( "VCO", ILOADs, VCO );
	GetValILOAD( "GDQ_MIN", ILOADs, GDQ_MIN );
	GetValILOAD( "GDQ_MAX", ILOADs, GDQ_MAX );
	GetValILOAD( "MACH_RRXF", ILOADs, MACH_RRXF );
	GetValILOAD( "QBARLOWQ", ILOADs, QBARLOWQ );
	GetValILOAD( "QBARLOWMIDQ", ILOADs, QBARLOWMIDQ );
	GetValILOAD( "QBARHIGHQ", ILOADs, QBARHIGHQ );
	GetValILOAD( "SBDMN", ILOADs, SBDMN );
	GetValILOAD( "SBDMX", ILOADs, SBDMX );
	GetValILOAD( "SBDLIM", ILOADs, SBDLIM );

	PITCH_JET_HYSTERESIS->SetLimits( PADB, PBDB );
	ROLL_JET_HYSTERESIS->SetLimits( RADB, RBDB );
	YAW_JET_HYSTERESIS->SetLimits( YADB, YBDB );
	return;
}

void AerojetDAP::OnPreStep(double simt, double simdt, double mjd)
{
	SelectFCS();

	VE = ReadCOMPOOL_SS( SCP_VE );
	PHI = ReadCOMPOOL_SS( SCP_PHI );
	QBAR = ReadCOMPOOL_SS( SCP_QBAR );
	Q = ReadCOMPOOL_SS( SCP_Q );
	P = ReadCOMPOOL_SS( SCP_P );
	R = ReadCOMPOOL_SS( SCP_R );
	THETA = ReadCOMPOOL_SS( SCP_THETA );
	ALPHA = ReadCOMPOOL_SS( SCP_ALPHA );
	BETA = ReadCOMPOOL_SS( SCP_BETA );
	COSALF = ReadCOMPOOL_SS( SCP_COSALF );
	SINALF = ReadCOMPOOL_SS( SCP_SINALF );
	COSPHI = ReadCOMPOOL_SS( SCP_COSPHI );
	SINPHI = ReadCOMPOOL_SS( SCP_SINPHI );
	TANPHI = ReadCOMPOOL_SS( SCP_TANPHI );
	COSTH = ReadCOMPOOL_SS( SCP_COSTH );
	SINTH = ReadCOMPOOL_SS( SCP_SINTH );
	TAS = ReadCOMPOOL_SS( SCP_V_T );
	NY = ReadCOMPOOL_SS( SCP_NY );
	RC = ReadCOMPOOL_SS( SCP_RC );
	TG_END = ReadCOMPOOL_IS( SCP_TG_END );
	WRAP = ReadCOMPOOL_IS( SCP_WRAP );
	DEFB = ReadCOMPOOL_SS( SCP_DEFB );
	DBFOFB = ReadCOMPOOL_SS( SCP_DBFOFB );
	DSBFB = ReadCOMPOOL_SS( SCP_DSBFB_DEG );
	DSBPC = ReadCOMPOOL_SS( SCP_DSBPC );
	DEMAN = pRHC_SOP->GetPitchCommand();
	DAMAN = pRHC_SOP->GetRollCommand();
	DRMAN = pRPTA_SOP->GetYawCommand();
	WOWLON = ReadCOMPOOL_IS( SCP_WOWLON );
	ROLLOUT = ReadCOMPOOL_IS( SCP_ROLLOUT );
	FLATTURN = ReadCOMPOOL_IS( SCP_FLATTURN );
	FCS_PITCH = ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH );
	FCS_ROLL = ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL );
	DETM_RHC = ReadCOMPOOL_IS( SCP_DETM_RHC );
	DATM_RHC = ReadCOMPOOL_IS( SCP_DATM_RHC );
	DETM_PAN = ReadCOMPOOL_IS( SCP_DETM_PAN );
	DATM_PAN = ReadCOMPOOL_IS( SCP_DATM_PAN );
	DRT = ReadCOMPOOL_IS( SCP_DRT );
	DBF_MAN = ReadCOMPOOL_IS( SCP_DBFMAN );
	SEL_L_GAIN = ReadCOMPOOL_IS( SCP_SEL_L_GAIN );
	SEL_NO_Y_JET = ReadCOMPOOL_IS( SCP_SEL_NO_Y_JET );

	if (SEL_L_GAIN == 1) LOWGAIN = 0.5;
	else LOWGAIN = 1.0;

	RECON();

	////// SPEEDBRAKE //////
	SpeedbrakeChannel();

	////// PITCH //////
	PitchChannel( simdt );

	////// BODY FLAP //////
	BodyFlapChannel( simdt );

	////// ROLL //////
	RollChannel( simdt );

	////// YAW //////
	YawChannel( simdt );

	////// NWS //////
	NosewheelChannel( simdt );


	WriteCOMPOOL_IS( SCP_UXCMD, UXCMD );
	WriteCOMPOOL_IS( SCP_UYCMD, UYCMD );
	WriteCOMPOOL_IS( SCP_UZCMD, UZCMD );
	WriteCOMPOOL_SS( SCP_DECC, static_cast<float>(DECC) );
	WriteCOMPOOL_SS( SCP_DBFRC, static_cast<float>(DBFRC) );
	WriteCOMPOOL_SS( SCP_DAC, static_cast<float>(DAC) );
	WriteCOMPOOL_SS( SCP_DRC, static_cast<float>(DRC) );
	WriteCOMPOOL_SS( SCP_DSBC, static_cast<float>(DSBC) );
	WriteCOMPOOL_SS( SCP_DNWC, static_cast<float>(DNWC) );
	WriteCOMPOOL_SS( SCP_DATRIM, static_cast<float>(DATRIM) );
	WriteCOMPOOL_SS( SCP_DRTRIM, static_cast<float>(DRTRIM) );
	WriteCOMPOOL_SS( SCP_DRTI, static_cast<float>(DRTI) );
	WriteCOMPOOL_SS( SCP_NZERR, static_cast<float>(NZERR) );
	WriteCOMPOOL_SS( SCP_BANKERR, static_cast<float>(BANKERR) );
	WriteCOMPOOL_IS( SCP_WRAP, WRAP );


	// speedbrake out-of-position indication
	if (simt > 0.5)// HACK don't run on first step as DSBFB isn't written yet
	{
		bool spdbrk_pos_int = false;
		if ((VE <= SBDMX) && (VE >= SBDMN))
		{
			if (fabs( DSBFB - ReadCOMPOOL_SS( SCP_SB_AUTO_CMD ) ) > SBDLIM) spdbrk_pos_int = true;
		}
		WriteCOMPOOL_IS( SCP_SPEEDBRAKE_POS_CREW_ALERT, spdbrk_pos_int ? 1 : 0 );
	}


	if (GetMajorMode() == 304)
	{
		if (ReadCOMPOOL_IS( SCP_EG_END ) == 1) SetMajorMode( 305 );
	}
	return;
}

bool AerojetDAP::OnMajorModeChange(unsigned int newMajorMode)
{
	if(newMajorMode == 304 || newMajorMode == 305) {
		// set Translation Commands to 0.0 during entry and landing
		/*DiscreteBundle* pBundle = BundleManager()->CreateBundle("THRUSTER_CMD", 16);
		DiscOutPort port;
		for(int i=0;i<3;i++) {
			port.Connect(pBundle, i+3);
			port.ResetLine();
		}*/

		if(newMajorMode == 304)
		{
			// when entering MM304 from MM303 init FCS to AUTO, otherwise it's a scenario start so leave it to the scenario data
			if (GetMajorMode() == 303)
			{
				WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 1 );
				WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, 1 );
				WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 1 );
				WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, 1 );
			}
		}
		ControlFCSLights();
		return true;
	}
	return false;
}

double AerojetDAP::GetdeltaAZLimit( void ) const
{
	if ((GetMajorMode() == 304) && (ReadCOMPOOL_IS( SCP_ISLECT ) != 1)) return ReadCOMPOOL_SS( SCP_YL ) * DEG;
	else return 999.9;// no limits in MM305
}

bool AerojetDAP::GetAutoPitchState( void ) const
{
	return ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH ) == 1;
}

bool AerojetDAP::GetAutoRollYawState( void ) const
{
	return ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL ) == 1;
}

bool AerojetDAP::GetAutoSpeedbrakeState( void ) const
{
	return ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) == 1;
}

void AerojetDAP::GetSelectedRunway( char* rw ) const
{
	if (ReadCOMPOOL_IS( SCP_RWID ) == 1) ReadCOMPOOL_C( SCP_PRI_ID, rw, 5 );
	else ReadCOMPOOL_C( SCP_SEC_ID, rw, 5 );
	rw[5] = 0;
	return;
}

double AerojetDAP::GetdeltaAZ( void ) const
{
	if (GetMajorMode() == 304) return ReadCOMPOOL_SS( SCP_DELAZ ) * DEG;
	else return ReadCOMPOOL_SS( SCP_DPSAC );
}

bool AerojetDAP::GetOnHACState( void ) const
{
	return ReadCOMPOOL_IS( SCP_IPHASE ) >= 2;
}

bool AerojetDAP::GetPrefinalState( void ) const
{
	return ReadCOMPOOL_IS( SCP_IPHASE ) >= 3;
}

bool AerojetDAP::GetApproachAndLandState( void ) const
{
	return TG_END == 1;
}

double AerojetDAP::GetVacc( void ) const
{
	// code below is heavily based on Hielor's post (http://www.orbiter-forum.com/showthread.php?t=5072)

	VECTOR3 force_vec, acc_vec, spd_vec;

	// Get the vectors we need
	STS()->GetAirspeedVector( FRAME_LOCAL, spd_vec );
	STS()->GetForceVector(force_vec);

	// Normalize the speed vector
	spd_vec = spd_vec / length(spd_vec);

	// Calculate the acceleration vector
	acc_vec = force_vec / STS()->GetMass();

	double vacc, lon, lat, radius, mag;
	VECTOR3 horacc_vec;
	VECTOR3 spd_vec2, glob_vpos, glob_rvel, loc_rvel;

	// VACC
	STS()->HorizonRot(acc_vec, horacc_vec);
	vacc = horacc_vec.y;

	// Account for "centrifugal acceleration"
	// Get the relative velocity in the local frame
	STS()->GetGlobalPos(glob_vpos);
	STS()->GetRelativeVel(STS()->GetSurfaceRef(), glob_rvel);
	STS()->Global2Local((glob_rvel + glob_vpos), loc_rvel);

	// Transform to horizon reference frame
	STS()->HorizonRot(loc_rvel, spd_vec2);

	STS()->GetEquPos(lon, lat, radius);

	// Determine the centrifugal acceleration
	spd_vec2.y = 0;
	mag = length(spd_vec2);
	vacc += mag * mag / radius;
	return vacc * MPS2FPS;
}

VECTOR3 AerojetDAP::GetAttitudeErrors( void ) const
{
	if (GetMajorMode() == 304) return _V( ALFERR_FDC, -BETA, -BANKERR );
	else if (WOWLON == 0) return _V( NZERR, -BETA, -BANKERR );
	else return _V( QFDC, -BETA, -BANKERR );
}

VECTOR3 AerojetDAP::GetRates( void ) const
{
	return -_V( Q, R_STAB, P_STAB );
}

double AerojetDAP::GetYRunwayPositionError( void ) const
{
	return ReadCOMPOOL_SS( SCP_Y );
}

double AerojetDAP::GetTimeToHAC( void ) const
{
	return ReadCOMPOOL_SS( SCP_P2TRNT ) * ReadCOMPOOL_SS( SCP_YSGN );
}

double AerojetDAP::GetHACRadialError( void ) const
{
	return (ReadCOMPOOL_SS( SCP_RCIR ) - ReadCOMPOOL_SS( SCP_RTURN )) * ReadCOMPOOL_SS( SCP_YSGN );
}

double AerojetDAP::GetNZError( void ) const
{
	return NZERR;
}

double AerojetDAP::GetHTA( void ) const
{
	return ReadCOMPOOL_SS( SCP_PSHA );
}

double AerojetDAP::GetGlideSlopeDistance( void ) const
{
	return ((TG_END == 1) ? ReadCOMPOOL_SS( SCP_HERR ) : ReadCOMPOOL_SS( SCP_HERROR ));
}

double AerojetDAP::GetNZ( void ) const
{
	return ReadCOMPOOL_SS( SCP_NZ );
}

double AerojetDAP::GetSelectedRunwayHeading( void ) const
{
	if (ReadCOMPOOL_IS( SCP_RWID ) == 1) return ReadCOMPOOL_SS( SCP_PRI_HDG );
	else return ReadCOMPOOL_SS( SCP_SEC_HDG );
}

double AerojetDAP::GetAltitude( void ) const
{
	return ReadCOMPOOL_SD( SCP_H );
}

double AerojetDAP::GetAltitudeRate( void ) const
{
	return ReadCOMPOOL_SS( SCP_HDOT );
}

double AerojetDAP::GetVrel( void ) const
{
	return VE;
}

void AerojetDAP::SelectFCS( void )
{
	bool downmode_alert = false;
	// check if AUTO or CSS
	// downmode to CSS if RHC is out of detent

	// pitch
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH ) == 1)
	{
		unsigned short CDRPitchCSS = ReadCOMPOOL_IS( SCP_FCS_LH_PITCH_CSS_MODE );
		unsigned short PLTPitchCSS = ReadCOMPOOL_IS( SCP_FCS_RH_PITCH_CSS_MODE );
		if ((CDRPitchCSS == 1) || (PLTPitchCSS == 1))
		{
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 2 );// go CSS
		}
		else if (pRHC_SOP->GetPitchManTakeOver() == true)
		{
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 2 );// go CSS
			if (VE > 2000.0) downmode_alert = true;// fault msg
		}
	}
	else
	{
		unsigned short CDRPitchAuto = ReadCOMPOOL_IS( SCP_FCS_LH_PITCH_AUTO_MODE );
		unsigned short PLTPitchAuto = ReadCOMPOOL_IS( SCP_FCS_RH_PITCH_AUTO_MODE );
		if ((CDRPitchAuto == 1) || (PLTPitchAuto == 1))
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_PITCH, 1 );// go AUTO
	}

	// roll
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL ) == 1)
	{
		unsigned short CDRRollYawCSS = ReadCOMPOOL_IS( SCP_FCS_LH_RY_CSS_MODE );
		unsigned short PLTRollYawCSS = ReadCOMPOOL_IS( SCP_FCS_RH_RY_CSS_MODE );
		if ((CDRRollYawCSS == 1) || (PLTRollYawCSS == 1) || (SEL_NO_Y_JET == 1))
		{
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, 2 );// go CSS
		}
		else if (pRHC_SOP->GetRollManTakeOver() == true)
		{
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, 2 );// go CSS
			if (VE > 2000.0) downmode_alert = true;// fault msg
		}
	}
	else
	{
		unsigned short CDRRollYawAuto = ReadCOMPOOL_IS( SCP_FCS_LH_RY_AUTO_MODE );
		unsigned short PLTRollYawAuto = ReadCOMPOOL_IS( SCP_FCS_RH_RY_AUTO_MODE );
		if ((CDRRollYawAuto == 1) || (PLTRollYawAuto == 1))
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_ROLL, 1 );// go AUTO
	}

	// speedbrake
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) == 1)
	{
		if (pSBTC_SOP->GetCDRTakeover() == true)
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 2 );// go CDR
		else if (pSBTC_SOP->GetPLTTakeover() == true)
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 3 );// go PLT
	}
	else
	{
		unsigned short CDR_SPDBK_THROT = ReadCOMPOOL_IS( SCP_LH_SPD_BK_THROT_AUTO_MAN );
		unsigned short PLT_SPDBK_THROT = ReadCOMPOOL_IS( SCP_RH_SPD_BK_THROT_AUTO_MAN );
		if ((CDR_SPDBK_THROT == 1) || (PLT_SPDBK_THROT == 1))
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 1 );// go AUTO
		else if (pSBTC_SOP->GetCDRTakeover() == true)
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 2 );// go CDR
		else if (pSBTC_SOP->GetPLTTakeover() == true)
			WriteCOMPOOL_IS( SCP_AEROJET_FCS_SB, 3 );// go PLT
	}

	// body flap
	unsigned short CDR_BODYFLAP = ReadCOMPOOL_IS( SCP_LH_BODY_FLAP_AUTO_MANUAL );
	unsigned short PLT_BODYFLAP = ReadCOMPOOL_IS( SCP_RH_BODY_FLAP_AUTO_MANUAL );
	if ((CDR_BODYFLAP == 1) || (PLT_BODYFLAP == 1))
	{
		if (!BodyFlapPBIpressed)
		{
			if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_BF ) == 1) WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, 2 );
			else WriteCOMPOOL_IS( SCP_AEROJET_FCS_BF, 1 );
			BodyFlapPBIpressed = true;
		}
	}
	else BodyFlapPBIpressed = false;

	ControlFCSLights();

	WriteCOMPOOL_IS( SCP_DAP_DNMODE_RHC_CREW_ALERT, downmode_alert ? 1 : 0 );
	return;
}

void AerojetDAP::ControlFCSLights( void )
{
	bool LAUTO_PLAMP = false;
	bool LCSS_PLAMP = false;
	bool LAUTO_RYLAMP = false;
	bool LCSS_RYLAMP = false;
	bool LAUTO_BFLAMP = false;
	bool LMNL_BFLAMP = false;
	bool LAUTO_SBLAMP = false;
	bool LMNL_SBLAMP = false;
	bool RAUTO_PLAMP = false;
	bool RCSS_PLAMP = false;
	bool RAUTO_RYLAMP = false;
	bool RCSS_RYLAMP = false;
	bool RAUTO_BFLAMP = false;
	bool RMNL_BFLAMP = false;
	bool RAUTO_SBLAMP = false;
	bool RMNL_SBLAMP = false;

	// pitch
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_PITCH ) == 1)
	{
		// AUTO
		LAUTO_PLAMP = true;
		RAUTO_PLAMP = true;
		LCSS_PLAMP = false;
		RCSS_PLAMP = false;
	}
	else
	{
		// CSS
		LAUTO_PLAMP = false;
		RAUTO_PLAMP = false;
		LCSS_PLAMP = true;
		RCSS_PLAMP = true;
	}

	// roll/yaw
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_ROLL ) == 1)
	{
		// AUTO
		LAUTO_RYLAMP = true;
		RAUTO_RYLAMP = true;
		LCSS_RYLAMP = false;
		RCSS_RYLAMP = false;
	}
	else
	{
		// CSS
		LAUTO_RYLAMP = false;
		RAUTO_RYLAMP = false;
		LCSS_RYLAMP = true;
		RCSS_RYLAMP = true;
	}

	// speedbrake
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) == 1)
	{
		// AUTO
		LAUTO_SBLAMP = true;
		RAUTO_SBLAMP = true;
		LMNL_SBLAMP = false;
		RMNL_SBLAMP = false;
	}
	else if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) == 2)
	{
		// MAN CDR
		LAUTO_SBLAMP = false;
		RAUTO_SBLAMP = false;
		LMNL_SBLAMP = true;
		RMNL_SBLAMP = false;
	}
	else
	{
		// MAN PLT
		LAUTO_SBLAMP = false;
		RAUTO_SBLAMP = false;
		LMNL_SBLAMP = false;
		RMNL_SBLAMP = true;
	}

	// body flap
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_BF ) == 1)
	{
		// AUTO
		LAUTO_BFLAMP = true;
		RAUTO_BFLAMP = true;
		LMNL_BFLAMP = false;
		RMNL_BFLAMP = false;
	}
	else
	{
		// MAN
		LAUTO_BFLAMP = false;
		RAUTO_BFLAMP = false;
		LMNL_BFLAMP = true;
		RMNL_BFLAMP = true;
	}

	// output to MDMs
	if (LAUTO_PLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0040 );
	if (LCSS_PLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0040 );
	if (LAUTO_RYLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0080 );
	if (LCSS_RYLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0080 );
	if (LAUTO_BFLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0010 );
	if (LMNL_BFLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0010 );
	if (LAUTO_SBLAMP) WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0020 );
	if (LMNL_SBLAMP) WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0020 );
	if (RAUTO_PLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0040 );
	if (RCSS_PLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0040 );
	if (RAUTO_RYLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0080 );
	if (RCSS_RYLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0080 );
	if (RAUTO_BFLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0010 );
	if (RMNL_BFLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0010 );
	if (RAUTO_SBLAMP) WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0020 );
	if (RMNL_SBLAMP) WriteCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF4_IOM10_CH0_DATA ) | 0x0020 );
	return;
}

void AerojetDAP::SpeedbrakeChannel( void )
{
	double DSBCOM = 0.0;// [deg]
	double DSB_ENT_SCHED = 0.0;// [deg]
	double DSBMAN = 0.0;// [deg]
	double DSB_BIAS = 0.0;// [deg]
	double DSB_MIN = 0.0;// [deg]

	DSB_ENT_SCHED = ENT_SB_SCHED();
	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_SB ) == 1)
	{
		// AUTO
		// HACK changed >0.95M check to MM304 as TAEM has (or had at some point) SB schedule
		//if (VI > 950.0)
		if (GetMajorMode() == 304) DSBCOM = DSB_ENT_SCHED;
		else
		{
			if (TG_END == 1) DSBCOM = ReadCOMPOOL_SS( SCP_DSBC_AL );
			else DSBCOM = ReadCOMPOOL_SS( SCP_DSBC_AT );
		}
	}
	else
	{
		DSBMAN = pSBTC_SOP->GetManSpeedbrakeCommand();// MAN (CDR or PLT)
		DSBCOM = DSBMAN;
	}

	SB_LIM_BIAS( DSB_BIAS, DSB_MIN );

	DSBC = midval( DSBCOM + DSB_BIAS, DSB_MIN, DSB_MAX );

	// HACK get AUTO command into COMPOOL
	double autoSBcmd;
	if (GetMajorMode() == 304) autoSBcmd = DSB_ENT_SCHED;
	else if (TG_END == 1) autoSBcmd = ReadCOMPOOL_SS( SCP_DSBC_AL );
	else autoSBcmd = ReadCOMPOOL_SS( SCP_DSBC_AT );
	WriteCOMPOOL_SS( SCP_SB_AUTO_CMD, static_cast<float>(autoSBcmd) );
	return;
}

double AerojetDAP::ENT_SB_SCHED( void ) const
{
	if (VE > ENT_SB_VS) return midval( ENT_SB_C1 + (VE * ENT_SB_C2), ENT_SB_1, ENT_SB_2 );
	else return midval( ENT_SB_C3 + (VE * ENT_SB_C4), ENT_SB_3, ENT_SB_2 );
}

void AerojetDAP::SB_LIM_BIAS( double &DSB_BIAS, double &DSB_MIN ) const
{
	unsigned short MACH_SB_REG = 0;// speedbrake regime

	if (WOWLON == 1) MACH_SB_REG = 1;// SB_LOW
	else if (VE < MACH_SBH) MACH_SB_REG = 2;// SB_MID
	else MACH_SB_REG = 3;// SB_HIGH

	if (MACH_SB_REG == 3)// SB_HIGH
	{
		DSB_BIAS = DSB_CLOSED;
		DSB_MIN = DSB_MIN_L;
	}
	else if (MACH_SB_REG == 2)// SB_MID
	{
		DSB_BIAS = DSB_BIAS_U;
		DSB_MIN = DSB_MIN_U;
	}
	else// SB_LOW
	{
		DSB_BIAS = DSB_BIAS_U;
		DSB_MIN = DSB_MIN_M;
	}
	return;
}

void AerojetDAP::PitchChannel( double dt )
{
	double QFDBK = 0.0;// [deg/s]
	double QC = 0.0;// [deg/s]
	double QCC = 0.0;
	double QC_RHC = 0.0;// [deg/s]
	double DETP = 0.0;
	double RTANPHI = 0.0;// [deg/s]
	double DECPP = 0.0;// [deg/s]
	double PKQ = 0.0;// [deg/deg^2]
	double ALFERR = 0.0;// [deg]
	double GQAL = 0.0;// angle of attack error gain [(deg/s)/deg]
	double QCJET = 0.0;
	double DPJET = 0.0;
	short NQ = 0;
	double NZSS = 0.0;
	double GQN = 0.0;// [(deg/s)/g]
	double DECF = 0.0;
	double DCSL = 0.0;
	double DECP = 0.0;
	double DECUL = 0.0;
	double GDQ = 0.0;// forward loop gain [deg/deg/s]
	double GTRE = 0.0;// elevator trim gain [(deg/s)/deg]
	double GJET = 0.0;// pitch RCS-to-elevator interconnect gain
	double UYGJET = 0.0;
	double DQCT = 0.0;
	double GTREDQCT = 0.0;
	double ESHAPE = 0.0;
	double GPRHC = 0.0;
	double GDSB = 0.0;
	double DSBXTR = 0.0;
	double DSBXTRS = 0.0;
	double GPX = 0.0;
	double DETR;// pitch RHC trim integrator value [deg/s]


	if (FCS_PITCH == 1)
	{
		QC_RHC = 0;

		// reset RHC trim integrator
		fltrDETR->LoadState( "0 0" );
	}
	else
	{
		// stick shaping
		// TODO PIO_ON
		PKQ = XKQO;
		ESHAPE = range( -DEMAX, (0.36 + (PKQ * fabs( DEMAN ))) * DEMAN, DEMAX );
		if (WOWLON == 0) GPX = 1.0;
		else GPX = 0.5;

		GPRHC = GPRHC_COMP();
		QC_RHC = GPRHC * ESHAPE * GPX;

		// roll rate trim (RHC)
		fltrDETR->SetGains( dt * 0.5, dt * 0.5, -1.0 );
		DETR = fltrDETR->GetValue( DETM_RHC * 0.6 );

		QC_RHC += DETR;
	}

	DETP = DETM_PAN * GPPANT;

	QFDBK = Q * LOWGAIN;

	UYCMD = 0;
	if (GetMajorMode() == 304)
	{
		// alpha command
		ALFERR_FDC = ALPHA - ReadCOMPOOL_SS( SCP_ALPCMD );

		// filter ALFERR_FILT_NYJET
		ALFERR_FILT->SetGains( (2.0 + (0.3 * dt)) / (2.0 + (0.1 * dt)), ((0.3 * dt) - 2.0) / (2.0 + (0.1 * dt)), ((0.1 * dt) - 2.0) / (2.0 + (0.1 * dt)) );
		ALFERR = 0.333333 * ALFERR_FILT->GetValue( ALFERR_FDC );
		ALFERR = range( -ALFERR_LIM, ALFERR, ALFERR_LIM );

		// scheduled gains
		// TODO TAL
		if (WRAP == 2) GQAL = GQAL_COMP_NYJET();
		else GQAL = GQAL_COMP();
		QC = ALFERR * GQAL;


		RTANPHI = 0.0;


		// RCS
		if (HIGHQ == false)
		{
			if (FCS_PITCH == 1)
			{
				QCJET = ALFERR * GQALR;
				DPJET = -Q - QCJET;
			}
			else DPJET = -Q + QC_RHC;

			// TODO bending filter: UYBB

			// pitch jet hysteresis
			if (fabs( DPJET ) <= DPJET_CUTOFF) NQ = 2;
			else NQ = 4;

			UYCMD = NQ * PITCH_JET_HYSTERESIS->GetValue( DPJET );
		}
	}
	else
	{
		// NZ command
		NZSS = -ReadCOMPOOL_SS( SCP_COSTH ) / max(0.5, ReadCOMPOOL_SS( SCP_COSPHI ));
		NZERR = ReadCOMPOOL_SS( SCP_NZ ) - (1.0 + (VCO / TAS)) * (TG_END ? ReadCOMPOOL_SS( SCP_NZ_CMD ) : ReadCOMPOOL_SS( SCP_NZC )) + NZSS;

		// NZ gain and filter
		if (TG_END) GQN = 4.2;
		else
		{
			GQN = 3.36;
			NZ_FILTER->SetGains( (0.2 + dt) / (1.0 + dt), -(0.2 - dt) / (1.0 + dt), -(1.0 - dt) / (1.0 + dt) );
			NZERR = NZ_FILTER->GetValue( NZERR );
		}
		QC = NZERR * GQN;

		if (FLATTURN == 0) RTANPHI = DRPHI * range( -1.0, SINPHI / COSPHI, 1.0 );
		else RTANPHI = 0.0;
	}

	if (FCS_PITCH == 1) QCC = QC;
	else QCC = -QC_RHC;

	if (LOWQ == false)
	{
		DECPP = QFDBK + QCC - RTANPHI;

		// TODO bending filter
		DECF = DECPP;

		if (GetMajorMode() == 305)
		{
			// shaping filter
			PITCH_SHAPING_FILTER->SetGains( (3.4 + dt) / (2.4 + dt), (dt - 3.4) / (2.4 + dt), (dt - 2.4) / (2.4 + dt) );
			DCSL = PITCH_SHAPING_FILTER->GetValue( DECF );
		}
		else DCSL = DECF;

		if ((FCS_PITCH == 2) && (WOWLON == 1))
		{
			double QFDC_RHC = DCSL * /*"replacement" GDQ*/range( 2.0, 800.0 / QBAR, 8.0 ) * LOWGAIN;
			RHC_INT->SetGains( dt * 0.5, dt * 0.5, -1.0 );
			DECP = QFDC_RHC + 0.1 * RHC_INT->GetValue( QFDC_RHC );// HACK added gain to increase stability
		}
		else
		{
			// forward loop gain
			GDQ = GDQ_COMP();
			DECP = DCSL * GDQ * LOWGAIN;
		}
	}
	else DECP = 0.0;

	// elevator trim logic, integrator/filter and limit
	GTRE = GTRE_COMP();

	// integrator ETRIM
	if (FCS_PITCH == 1)
	{
		if (LOWQ == false) DQCT = QCC;// TODO gain?
		else DQCT = 0.0;
	}
	else DQCT = DECP;
	GTREDQCT = GTRE * DQCT;

	GJET = GJET_COMP();
	UYGJET = UYCMD * GJET;

	fltrETRIM->SetGains( dt * 0.5, dt * 0.5, -1.0 );
	ETRIM = fltrETRIM->GetValue( (GTREDQCT - DETP) - UYGJET );


	// integrator ELFBK
	GDSB = GDSB_COMP();
	DSBXTR = DSBPC * GDSB;

	if (DSBFB >= 30.0) DSBXTRS = DSBXTR * (1.0 / dt);
	else DSBXTRS = DSBXTR * (0.4 / dt);

	// integrator/lag filter
	double tmp = 2.0 / (GTRE * dt);
	fltrELFBK->SetGains( 1.0 / (tmp + 1.0), 1.0 / (tmp + 1.0), (1.0 - tmp) / (1.0 + tmp) );
	ELFBK = fltrELFBK->GetValue( ((DSBXTRS - DETP) / GTRE) + DEFB );


	if (HIGHQ == false) DETRIM = ETRIM;
	else DETRIM = ELFBK;


	if (WOWLON == 1) QFDC = GD_COMP( QFDBK );
	else QFDC = 0.0;

	if (FCS_PITCH == 1)
	{
		if (ROLLOUT == 1)
		{
			// load relief
			DECP = LD_REL_BIAS;
		}
		else if (WOWLON == 1)
		{
			// slapdown
			DECP = QFDC;
		}
	}

	DECUL = DECP + ((ROLLOUT == 1) ? 0.0 : DETRIM);

	// position limiting
	DECC = range( -33.0, DECUL, 18.0 );

	//sprintf_s( oapiDebugString(), 256, "DECC%+.2f DETP%+.2f DECP%+.2f DETRIM%+.2f DECPP%+.2f QC%+.2f QCC%+.2f RTANPHI%+.2f UYGJET%+.2f DQCT%+.2f", DECC, DETP, DECP, DETRIM, DECPP, QC, QCC, RTANPHI, UYGJET, DQCT );
	//sprintf_s( oapiDebugString(), 256, "P%+.2f Q%+.2f R%+.2f UYCMD%d LOWQ%d HIGHQ%d", P, Q, R, UYCMD, LOWQ, HIGHQ );
	//sprintf_s( oapiDebugString(), 256, "NZERR%+.2f NZC%+.2f NZSS%+.2f NZ%+.2f DECC%+.2f DECP%.2f DETRIM%+.2f Q%.2f QCC%.2f RTANPHI%.2f", NZERR, TG_END ? ReadCOMPOOL_SS( SCP_NZ_CMD ) : ReadCOMPOOL_SS( SCP_NZC ), NZSS, ReadCOMPOOL_SS( SCP_NZ ), DECC, DECP, DETRIM, Q, QCC, RTANPHI );
	return;
}

double AerojetDAP::GQAL_COMP( void ) const
{
	return range( 0.33, 8.84 - (0.00037 * VE), 0.7 );// TODO GRTLS
}

double AerojetDAP::GQAL_COMP_NYJET( void ) const
{
	if (VE > 22000.0) return range( 0.33, 8.84 - (0.00037 * VE), 0.7 );
	else return range( 0.7, 7.0 - (0.00035 * VE), 1.05 );
}

double AerojetDAP::GDQ_COMP( void ) const
{
	double KPIT = 0.0;

	if (VE > 2400.0) KPIT = range( 45.0, (-0.02 * VE) + 155.0, 65.0 );
	else
	{
		if (FCS_PITCH == 1) KPIT = range( 20.0, (0.0375 * VE) - 25.0, 65.0 );
		else
		{
			if (VE > 450.0) KPIT = range( 12.5, (0.04375 * VE) - 40.0, 65.0 );
			else KPIT = range( 12.5, (-0.0233333 * VE) + 23.0, 16.0 );
		}
	}

	return range( GDQ_MIN, KPIT / sqrt( QBAR/*QBARFC*/ + 4 ), GDQ_MAX );
}

double AerojetDAP::GJET_COMP( void ) const
{
	if ((QBAR >= 0.5) && (QBAR <= 8.0)) return 4.0;
	else return 0.0;
}

double AerojetDAP::GTRE_COMP( void ) const
{
	if ((FCS_PITCH == 2) && (WOWLON == 0)) return range( 1.0, (-0.001 * VE) + 4.5, 1.5 );// CSS
	else return range( 0.3, (-0.00015 * VE) + 2.1, 0.6 );// AUTO
}

double AerojetDAP::GPRHC_COMP( void ) const
{
	return range( 0.125, (-0.00055 * VE) + 1.5, 0.4 );
}

double AerojetDAP::QC_NOM_COMP( void ) const
{
	return range( -4.0, (THETA * 0.6) - 2.2, -1.0 );
}

double AerojetDAP::QC_ALT_COMP( void ) const
{
	return range( -6.0, (THETA * 0.833333) - 3.5, -1.0 );
}

double AerojetDAP::GDSB_COMP( void ) const
{
	return range( 0.1, (0.0001 * VE) - 0.05, 0.25 );
}

double AerojetDAP::GD_COMP( double QFDBK ) const
{
	if (ReadCOMPOOL_SS( SCP_KEAS ) <= EAS_SD)// HACK should be latched once true
	{
		if (ReadCOMPOOL_SS( SCP_WEIGHT ) <= WGT_SD)// TODO RTLS
		{
			double QC_NOM = QC_NOM_COMP();
			return QFDBK - QC_NOM;
		}
		else
		{
			double QC_ALT = QC_ALT_COMP();
			return QFDBK - QC_ALT;
		}
	}
	else return QFDBK;
}

void AerojetDAP::BodyFlapChannel( double dt )
{
	double DBFRCS = 0.0;
	double DBFDC = 0.0;
	double GBFR = 0.0;
	double DETD = 0.0;
	double DETBIAS = 0.0;
	double GBFMACH = 0.0;
	double GBFAUTO = 0.0;
	double AUTO_BF = 0.0;
	double MAN_BF = 0.0;
	double DBFPC = 0.0;

	if (ReadCOMPOOL_IS( SCP_AEROJET_FCS_BF ) == 1)
	{
		if (LOWQ == false)
		{
			// BF_RATE_CMD
			if (GetMajorMode() == 304)
			{
				GBFMACH = GBFMACH_SCHED();
				GBFAUTO = GBFAUTO_MOD();

				DETBIAS = GBFMACH * GBFAUTO;
			}
			else DETBIAS = 0.0;

			DETD = DETD_SCHED_MID();

			DBFDC = BF_RATE_CMD->GetValue( DETRIM - DETD - DETBIAS );

			GBFR = GBFR_SCHED();

			AUTO_BF = DBFDC * GBFR;
		}
		else AUTO_BF = 0.0;

		DBFRCS = AUTO_BF;
	}
	else
	{
		MAN_BF = DBF_MAN * GBFMAN;

		DBFRCS = MAN_BF;
	}

	// BF_DEF_CMD
	double tsDBFRCS = BF_DEF_CMD->GetValue( dt, DBFRCS );
	fltrDBFD->SetGains( dt * 0.5, dt * 0.5, -1.0 );
	DBFPC = fltrDBFD->GetValue( tsDBFRCS );

	if ((ReadCOMPOOL_IS( SCP_RETRACT_BF ) == 1) && (ReadCOMPOOL_IS( SCP_AEROJET_FCS_BF ) == 1)) DBFPC = DBFRET;

	DBFRC = BF_HYSTER->GetValue( DBFPC - DBFOFB );

	/*sprintf_s( oapiDebugString(), 256, "DBFOFB%+.2f DBFRC%+.2f DBFPC%+.2f DBFRCS%+.2f GBFR%+.2f DBFDC%+.2f DETRIM%+.2f DETD%+.2f DETBIAS%+.2f DETRIM-DETD%+.2f",
		DBFOFB, DBFRC, DBFPC, DBFRCS, GBFR, DBFDC, DETRIM, DETD, DETBIAS, DETRIM - DETD );*/
	return;
}

double AerojetDAP::GBFR_SCHED( void ) const
{
	if (VE > 1500.0) return range( 0.15, (0.0003 * VE) - 0.3, 0.3 );
	else return range( 0.15, (-0.00283333 * VE) + 2.7, 1.0 );
}

double AerojetDAP::DETD_SCHED_FWD( void ) const
{
	if (VE > 11000.0) return range( -7.0, (0.0008 * VE) - 15.8, -3.0 );
	else if (VE > 4000.0) return range( -7.0, (-0.001 * VE) + 2.0, -2.0 );
	else return range( -2.0, (-0.00666667 * VE) + 8.0, 2.0 );
}

double AerojetDAP::DETD_SCHED_MID( void ) const
{
	if (VE > 11000.0) return range( -1.0, (0.0006 * VE) - 7.6, 2.0 );
	else if (VE > 5000.0) return range( -1.0, (-0.00075 * VE) + 5.75, 2.0 );
	else if (VE > 2000.0) return range( 0.0, (0.002 * VE) - 4.0, 2.0 );
	else return range( 0.0, (-0.005 * VE) + 7.5, 3.0 );
}

double AerojetDAP::DETD_SCHED_AFT( void ) const
{
	if (VE > 11000.0) return range( 4.0, (0.0006 * VE) - 2.6, 7.0 );
	else if (VE > 6000.0) return range( 4.0, (-0.000333333 * VE) + 7.0, 5.0 );
	else if (VE > 2000.0) return range( 2.0, (0.003 * VE) - 4.0, 5.0 );
	else return range( 2.0, (-0.00333333 * VE) + 7.0, 4.0 );
}

double AerojetDAP::GBFMACH_SCHED( void ) const
{
	if (VE > 9000.0) return range( 1.0, (-0.00005 * VE) + 1.8, 1.2 );
	else return range( 0.6, (0.0002 * VE) - 0.6, 1.2 );
}

double AerojetDAP::GBFAUTO_MOD( void ) const
{
	if (DBFOFB > 11.0) return range( -2.0, (1.75 * DBFOFB) - 21.25, 5.0 );
	else return range( -5.0, (0.272727 * DBFOFB) - 5.0, -2.0 );
}

void AerojetDAP::RollChannel( double dt )
{
	double DATP = 0.0;
	double KDAMLIN = 0.0;
	double KDAMPAR = 0.0;
	double DAMAX = 0.0;
	double PHIC = 0.0;// [deg]
	double BKERR = 0.0;// [deg]
	double GPBANK = 0.0;// [(deg/s)/deg]
	double PCLIM = 0.0;// [deg/s]
	double DNYP = 0.0;
	double GALR = 0.0;// roll axis gain
	double GTRA = 0.0;// aileron trim integrator gain [(deg/s)/deg]
	double GTRIMB = 0.0;
	double DRR_LIM = 0.0;
	double DATSUM = 0.0;
	double DATRIM_LIM_S = 0.0;// aileron trim integrator limit [deg]
	double PEUF = 0.0;
	double PEX = 0.0;
	double DCSP = 0.0;// roll error signal
	double GDA = 0.0;// aileron forward loop gain
	double GBAY = 0.0;
	double GPAY = 0.0;
	double PERJ = 0.0;
	double DELTA_AB = 0.0;
	double DATR;// roll RHC trim integrator value [deg/s]
	short NP = 0;

	DATP = DATM_PAN * GRPANT;

	if (GetMajorMode() == 304) PHIC = ReadCOMPOOL_SS( SCP_ROLLCMD );
	else if (TG_END == 0) PHIC = ReadCOMPOOL_SS( SCP_PHIC_AT );
	else PHIC = ReadCOMPOOL_SS( SCP_PHIC_AL );
	BANKERR = PHIC - PHI;

	if (FCS_ROLL == 1)
	{
		// AUTO
		if (TG_END == 0)// HACK disabled threshold for A/L, as lateral control is much more stable without it
		{
			if (WRAP == 2) BKERR = BANKERR_THRESH_NYJET( BANKERR );
			else BKERR = BANKERR_THRESH( BANKERR );
		}
		else BKERR = BANKERR;

		GPBANK = GPBANK_COMP();
		PCLIM = PCLIM_COMP();

		PC = range( -PCLIM, BKERR * GPBANK, PCLIM );

		// reset RHC trim integrator
		fltrDATR->LoadState( "0 0" );
	}
	else
	{
		// CSS
		// roll rate trim (RHC)
		fltrDATR->SetGains( dt * 0.5, dt * 0.5, -1.0 );
		DATR = fltrDATR->GetValue( DATM_RHC * GRRCHT );

		KDAMLIN = KDAMLIN_COMP();
		KDAMPAR = KDAMPAR_COMP();
		DAMAX = DAMAX_COMP();

		// TODO lag filter
		PC = range( -DAMAX, (KDAMLIN + (KDAMPAR * fabs( DAMAN ))) * DAMAN, DAMAX ) + DATR;
	}

	// turn coordination logic
	if (FLATTURN == 0) PCOR = (/*57.3*/DEG * MPS2FPS * G * TANPHI * fabs( SINTH )) / TAS;
	else PCOR = 0.0;

	PCOR = P + PCOR;

	P_STAB = (R * SINALF) + (PCOR * COSALF);
	R_STAB = (DRPRM * COSALF) - (P * SINALF);


	if ((WRAP == 2) || (SEL_NO_Y_JET == 1)) GALR = GALRD_COMP();
	else GALR = GALRT_COMP();

	if (HIGHQ == true)
	{
		if ((WRAP == 2) || (SEL_NO_Y_JET == 1))
		{
			// wraparound or NO Y JET
			GBAY = GBAY_COMP();

			DNYP_COMP->SetGains(
				(40.0 * dt) / ((dt * (dt + 41.6)) + 64.0),
				0.0,
				-(40.0 * dt) / ((dt * (dt + 41.6)) + 64.0),
				(2.0 * ((dt * dt) - 64.0)) / ((dt * (dt + 41.6)) + 64.0),
				((dt * (dt - 41.6)) + 64.0) / ((dt * (dt + 41.6)) + 64.0)
			);
			DNYP = GBAY * DNYP_COMP->GetValue( NY );
		}
		else
		{
			// baseline
			GPAY = GPAY_COMP();
			DNYP = DAY * RTHL * GPAY * SINALF;
		}
	}

	PEUF = ((((ALPHA == 0) ? 0.0 : (DRPRM * cot( ALPHA * RAD ) * GALR)) + (PC * COSALF * (1.0 - GALR))) + DNYP - (BETAF * SINALF)) - PCOR;

	UXCMD = 0;
	if ((LOWQ == true) || (LOWMIDQ == true))
	{
		// TODO bending filter ROLLJET_BBF
		PERJ = PEUF;

		if (fabs( PERJ ) <= PE_CUTOFF) NP = NP_LOW;
		else NP = NP_HIGH;

		UXCMD = NP * ROLL_JET_HYSTERESIS->GetValue( PERJ );
	}

	if (LOWQ == false)
	{
		// TODO bending filters
		PEX = PEUF;

		PEX *= LOWGAIN;

		// aileron forward loop gain
		GDA = GDA_COMP();
		DCSP = PEX * GDA;

		if (VE < 3500.0)
		{
			if (FLATTURN == 0)
			{
				GTRA = GTRA_COMP();
				DATSUM = DCSP * GTRA;
			}
			else DATSUM = 0.0;
		}
		else
		{
			// TODO GRTLS limits and gains
			if (WRAP == 2)
			{
				// wrap
				DRR_LIM = 0.7;
				GTRIMB = 0.1;
			}
			else
			{
				// baseline
				DRR_LIM = 0.175;
				GTRIMB = 0.1;
			}
			DATSUM = range( -DRR_LIM, DRRCJF + (LOWMIDQ ? PEX : 0.0), DRR_LIM ) * GTRIMB;
		}

		if ((FLATTURN == 1) && (FCS_ROLL == 1)) DATSUM = 0.0;
		else DATSUM += DATP;

		// TODO GRTLS limits
		if (WRAP == 2) DATRIM_LIM_S = 5.0;// wrap
		else DATRIM_LIM_S = 3.0;// baseline

		fltrDATRIM->SetLimits( -DATRIM_LIM_S, DATRIM_LIM_S );

		fltrDATRIM->SetGains( dt * 0.5, dt * 0.5, -1.0 );
		DATRIM = fltrDATRIM->GetValue( DATSUM );
		if ((ROLLOUT == 1) && (FCS_ROLL == 1)) DATRIM = 0.0;

		// load balancing (incomplete)
		if (FLATTURN == 1)
		{
			if (ROLLOUT == 0)
			{
				// post WOWLON
				double DAB = ((NY * MPS2FPS * G) / ReadCOMPOOL_SS( SCP_V_T )) - R;

				if (FCS_ROLL == 1) DELTA_AB = DAB * KDAB_AUTO;
				else DELTA_AB = DAB * KDAB_CSS;

				TRWY_FADE->SetValue( DELTA_AB );
			}
			else DELTA_AB = TRWY_FADE->Fade( dt );// rollout
		}
		else DELTA_AB = 0.0;

		// limiter
		DAC = range( -10.0, DCSP + DATRIM + DELTA_AB, 10.0 );
	}
	else DAC = 0.0;

	/*sprintf_s( oapiDebugString(), 256, "DAC%+.2f DATRIM%+.2f DATSUM%.2f DCSP%+.2f PEX%.2f DRRCJF%.2f GDA%.2f GALR%.2f BETAF%.2f DAY%.2f PC%.2f DRPRM%.2f DNYP%.2f PCOR%.2f R%.2f P%.2f DAMAN%.2f",
		DAC, DATRIM, DATSUM, DCSP, PEX, DRRCJF, GDA, GALR, BETAF, DAY, PC, DRPRM, DNYP, PCOR, R, P, DAMAN );*/
	/*sprintf_s( oapiDebugString(), 256, "DAC%+.2f DATRIM%+.2f DATSUM%+.2f DCSP%+.2f BETA%+.2f R%+.2f NY%+.2f DELTA_AB%+.2f",
		DAC, DATRIM, DATSUM, DCSP, BETA, R, NY, DELTA_AB );*/
	return;
}

double AerojetDAP::GALRT_COMP( void ) const
{
	if (QBAR < 10.0) return GALRE;
	else if (VE > 3000.0) return range( 0.55, (0.00055 * VE) - 1.1, 1.1 );
	else if (VE > 1500.0) return range( 0.25, (0.0006 * VE) - 0.65, 0.55 );
	else return range( 0.0, (0.025 * VE) - 22.25, 0.25 );
}

double AerojetDAP::GALRD_COMP( void ) const
{
	if (VE > 5500.0) return range( 1.4, (0.0002 * VE) + 0.3, 1.7 );
	else if (VE > 3500.0) return range( 0.55, (0.00113333 * VE) - 3.416667, 1.4 );
	else if (VE > 1500.0) return range( 0.25, (0.0006 * VE) - 0.65, 0.55 );
	else return range( 0.0, (0.025 * VE) - 22.25, 0.25 );
}

double AerojetDAP::BANKERR_THRESH( double _BANKERR )
{
	double tmp = fabs( _BANKERR );

	if (tmp < 0.5) return 0.0;
	else if (tmp < 5.0) return (0.444444 * _BANKERR) - (0.222222 * sign( _BANKERR ));
	else return _BANKERR - (3.0 * sign( _BANKERR ));
}

double AerojetDAP::BANKERR_THRESH_NYJET( double _BANKERR )
{
	double tmp = fabs( _BANKERR );

	if (tmp < 0.5) return 0.0;
	else if (tmp < 5.0) return (0.222222 * _BANKERR) - (0.111111 * sign( _BANKERR ));
	else return _BANKERR - (4.0 * sign( _BANKERR ));
}

double AerojetDAP::GPBANK_COMP( void ) const
{
	return range( 0.5, 1.9 - (0.00116667 * VE), 1.2 );
}

double AerojetDAP::PCLIM_COMP( void ) const
{
	if (VE > 23000.0) return range( 3.0, 97.0 - (0.004 * VE), 5.0 );
	else return range( 5.0, 30.0 - (0.0166667 * VE), 20.0 );
}

double AerojetDAP::GTRA_COMP( void ) const
{
	if (VE > 3500.0) return range( 0.0, 7.1 - (0.002 * VE), 0.1 );
	if (FCS_ROLL == 1) return range( 0.1, 19.0 - (0.015 * VE), 0.25 );
	else return range( 0.0, (0.01 * VE) - 12.5, 0.1 );
}

double AerojetDAP::GDA_COMP( void ) const
{
	// TODO GRTLS
	double KGDA = KGDA_COMP();

	return range( GDA_MIN, KGDA / (QBAR + 10.0), GDA_MAX );
}

double AerojetDAP::KGDA_COMP( void ) const
{
	if (VE > 5500.0) return range( 100.0, 496.666667 - (0.0466667 * VE), 240.0 );
	else if (VE > 3500.0) return range( 190.0, (0.1 * VE) - 160.0, 240.0 );
	else return range( 48.0, (0.322727 * VE) - 339.272727, 190.0 );
}

double AerojetDAP::KDAMLIN_COMP( void ) const
{
	return range( 0.2, (0.000813778 * VE) - 0.288267, 0.9324 );
}

double AerojetDAP::KDAMPAR_COMP( void ) const
{
	return range( 0.008, 0.0898333 - (5.45556e-5 * VE), 0.0571 );
}

double AerojetDAP::DAMAX_COMP( void ) const
{
	return range( 20.0, 25.0 - (0.003333333 * VE), 23.0 );
}

double AerojetDAP::GPAY_COMP( void ) const
{
	if (VE > 1200.0) return range( 0.333, (0.00222333 * VE) - 2.335, 1.0 );
	else return range( 0.0, (0.00111 * VE) - 0.999, 0.333 );
}

double AerojetDAP::GBAY_COMP( void ) const
{
	if (VE > 18000.0) return range( 5.0, (0.00375 * VE) - 62.5, 20.0 );
	else if (VE > 6000.0) return range( 5.0, 85.0 - (0.01 * VE), 25.0 );
	else if (VE > 3000.0) return range( 10.0, (0.015 * VE) - 35.0, 25.0 );
	else return range( 0.0, (0.0166667 * VE) - 15.0, 10.0 );
}

void AerojetDAP::YawChannel( double dt )
{
	double DRMS = 0.0;// [deg]
	double DRTMS = 0.0;
	double GRAY = 0.0;// NY feedback gain
	double DAXFD = 0.0;
	double DAXFDC = 0.0;
	double RFILT = 0.0;
	double BCOSALF = 0.0;
	double GRH = 0.0;
	double DRRCUF = 0.0;
	double DRJETT = 0.0;
	double WJETDB0;// [deg/s]
	double WJETDB1;// [deg/s]
	double WJETDB2;// [deg/s]
	double WJETDB3;// [deg/s]
	double WJETDB4;// [deg/s]
	short WJNR1 = 0;
	short WJNR2 = 0;
	short WJNR3 = 0;
	short WJNR4 = 0;
	short NR = 0;
	double GDRC = 0.0;// rudder forward loop gain [deg/(deg/s)]
	double DRCPF = 0.0;
	double GTRR = 0.0;// rudder trim integrator gain [(deg/s)/deg]
	double TMP1 = 0.0;
	double GNYDRM = 0.0;

	// panel yaw trim
	fltrDRTI->SetGains( dt * 0.5, dt * 0.5, -1.0 );
	DRTI = fltrDRTI->GetValue( GDRTI * DRT );

	if (HIGHQ == true)
	{
		if ((VE <= 5000.0) && (FCS_ROLL == 2))
		{
			// RPTA shaping logic
			DRMS = range( -DRMAX, (0.131 + (0.042 * fabs( DRMAN ))) * DRMAN, DRMAX );

			// RPTA gain
			GNYDRM = GNYDRM_COMP();
			DRMS *= GNYDRM;
		}
		else DRMS = 0.0;

		DRTMS = ((FLATTURN == 0) ? NY : 0.0) - DRMS - DRTI;

		// filter and gain GRAY
		GRAY = GRAY_COMP();
		NY_COMP->SetGains( dt / (0.4 + dt), dt / (0.4 + dt), (dt - 0.4) / (0.4 + dt) );
		DAY = GRAY * NY_COMP->GetValue( DRTMS );
	}
	else DAY = 0.0;

	if (VE > MACH_RRXF) DAXFD = PC;
	else DAXFD = PCOR;

	DAXFDC = DAXFD * SINALF;

	if (LOWQ == true) BETAF = BETA;
	else if (HIGHQ == true) BETAF = 0.0;
	else
	{
		BETA_FILTER->SetGains( 2.0 / ((0.05 * dt) + 2.0), -(2.0 / ((0.05 * dt) + 2.0)), ((0.05 * dt) - 2.0) / ((0.05 * dt) + 2.0) );
		BETAF = BETA_FILTER->GetValue( BETA );
	}

	BCOSALF = BETAF * COSALF * GBETA;

	// TODO bending filters
	RFILT = R;

	// turn coordination logic
	if (FLATTURN == 0) DRPHI = (/*57.3*/DEG * MPS2FPS * G * SINPHI * COSTH) / TAS;
	else DRPHI = 0.0;
	DRPRM = RFILT - DRPHI;

	//DRPRM = RFILT;
	//DRPRM = (RFILT * COSALF) - (P * SINALF);

	TMP1 = (DRPRM - BCOSALF) - DAXFDC;

	// washout and gain
	fltrGRH->SetGains( 1.0 / (1.0 + dt), -(1.0 / (1.0 + dt)), (dt - 1.0) / (1.0 + dt) );
	GRH = GRH_COMP() * 2.0 * fltrGRH->GetValue( TMP1 );

	DRRCUF = GRH + (DAY * COSALF) + TMP1 - ((FCS_ROLL == 1) ? RC : 0.0);

	// TODO yaw RCS bending filters
	DRRCJF = DRRCUF;

	UZCMD = 0;
	if ((VE >= 1000.0) && (SEL_NO_Y_JET == 0))
	{
		DRJETT = GRCSA * DRRCJF;

		// yaw jets hysteresis
		if (WRAP == 2)
		{
			// wraparound
			// yaw RCS switching limits
			if (QBAR <= 30.0)
			{
				WJETDB1 = 0.35;
				WJETDB0 = WJETDB1 - WJETHYST;
				WJETDB2 = 1.5;
				WJETDB3 = 2.0;
				WJETDB4 = 2.5;
			}
			else if (QBAR >= 80.0)
			{
				WJETDB1 = 1.35;
				WJETDB0 = WJETDB1 - WJETHYST;
				WJETDB2 = 3.0;
				WJETDB3 = 4.0;
				WJETDB4 = 5.0;
			}
			else
			{
				double tmp = (QBAR - 30.0) / 50.0;
				WJETDB1 = 0.35 + tmp;
				WJETDB0 = WJETDB1 - WJETHYST;
				WJETDB2 = 1.5 + (tmp * 1.5);
				WJETDB3 = 2.0 + (tmp * 2.0);
				WJETDB4 = 2.5 + (tmp * 2.5);
			}

			// number of yaw jets to be fired
			if (HIGHQ == true)
			{
				WJNR1 = WJNR1_HIGHQ;
				WJNR2 = WJNR2_HIGHQ;
				WJNR3 = WJNR3_HIGHQ;
				WJNR4 = WJNR4_HIGHQ;
			}
			else
			{
				WJNR1 = WJNR1_LOWQ;
				WJNR2 = WJNR2_LOWQ;
				WJNR3 = WJNR3_LOWQ;
				WJNR4 = WJNR4_LOWQ;
			}

			if (DRJETT > WJETDB4) UZCMD = WJNR4;
			else if (DRJETT > WJETDB3) UZCMD = WJNR3;
			else if (DRJETT > WJETDB2) UZCMD = WJNR2;
			else if (DRJETT > WJETDB1) UZCMD = WJNR1;
			else if (DRJETT > WJETDB0);// UZCMD = UZCMD;
			else if (DRJETT > -WJETDB0) UZCMD = 0;
			else if (DRJETT > -WJETDB1);// UZCMD = UZCMD;
			else if (DRJETT > -WJETDB2) UZCMD = -WJNR1;
			else if (DRJETT > -WJETDB3) UZCMD = -WJNR2;
			else if (DRJETT > -WJETDB4) UZCMD = -WJNR3;
			else UZCMD = -WJNR4;
		}
		else
		{
			// baseline
			if (HIGHQ == false)
			{
				/*if (fabs( DRJETT ) > 0.5) NR = 2;
				else*/ NR = 2;
			}
			else
			{
				if (fabs( DRJETT ) > 1.5) NR = 4;
				else if (fabs( DRJETT ) > 1.0) NR = 3;
				//else if (fabs( DRJETT ) > 0.5) NR = 2;
				else NR = 2;
			}

			UZCMD = NR * YAW_JET_HYSTERESIS->GetValue( DRJETT );
		}
	}

	if (VE < 5000.0)
	{
		// TODO bending filters

		DRRCUF *= LOWGAIN;

		// rudder forward loop gain
		GDRC = GDRC_COMP();
		DRCPF = DRRCUF * GDRC;

		// rudder trim gain and integrator
		GTRR = GTRR_COMP();
		fltrDRTRIM->SetGains( dt * 0.5, dt * 0.5, -1.0 );
		DRTRIM = fltrDRTRIM->GetValue( GTRR * DRCPF );
		if ((FLATTURN == 1) && (FCS_ROLL == 1)) DRTRIM = 0.0;

		// limiting logic
		DRC = DRTRIM + DRCPF;
		if (ROLLOUT == 1) DRC = range( -27.1, DRC, 27.1 );
		else DRC = range( -24.1, DRC, 24.1 );
	}
	else DRC = 0.0;
	//sprintf_s( oapiDebugString(), 256, "VE%.2f DRPHI%.2f DRPRM%.2f R%.2f R_STAB%.2f P%.2f P_STAB%.2f", VE, DRPHI, DRPRM, R, R_STAB, P, P_STAB );
	/*sprintf_s( oapiDebugString(), 256, "DRC%+.2f DRTRIM%+.2f DRCPF%+.2f GDRC%.2f GTRR%.2f DRRCUF%.2f TMP1%.2f GRH%.2f BETA%.2f DAXFDC%.2f VE%.2f DRMS%.2f DRTMS%.2f PC%.2f PCOR%.2f DRJETT%.2f %d %d",
		DRC, DRTRIM, DRCPF, GDRC, GTRR, DRRCUF, TMP1, GRH, BETA, DAXFDC, VE, DRMS, DRTMS, PC, PCOR, DRJETT, HIGHQ, UZCMD );*/
	return;
}

double AerojetDAP::GRH_COMP( void ) const
{
	return range( 0.0, (0.025 * VE) - 22.5, 0.25 );
}

double AerojetDAP::GDRC_COMP( void ) const
{
	double KDRC = KDRC_COMP();

	return range( GDRC_MIN, KDRC / (QBAR + 10.0), GDRC_MAX );
}

double AerojetDAP::KDRC_COMP( void ) const
{
	if (VE > 3500.0) return range( 0.0, 2062.5 - (0.375 * VE), 750.0 );
	return range( 750.0, 2500.0 - (2.5 * VE), 1000.0 );
}

double AerojetDAP::GTRR_COMP( void ) const
{
	return range( 0.1, (0.0016 * VE) - 1.42, 0.5 );
}

double AerojetDAP::GRAY_COMP( void ) const
{
	if (VE > 5500.0) return range( 2.5, 17.5 - (0.0025 * VE), 3.75 );
	return range( 3.75, 5.579268 - (0.000609756 * VE), 5.0 );
}

double AerojetDAP::GNYDRM_COMP( void ) const
{
	return range( 0.015, 0.063461538 - (0.0000538462 * TAS), 0.05 );
}

void AerojetDAP::NosewheelChannel( double dt )
{
	double RCP = 0.0;
	double DRG = 0.0;
	double DRSHAP = 0.0;
	double DR_LIM = 0.0;
	double DWNCPP = 0.0;
	double DWNCP = 0.0;


	if (ReadCOMPOOL_IS( SCP_GSENBL ) == 1)
	{
		if (FCS_ROLL == 1)
		{
			if (TG_END == 1) RCP = RC;
			else RCP = 0.0;

			DRG = RCP - (R * GRR);

			DWNCP = DRG * DNWR * 1.0;
		}
		else
		{
			DRSHAP = (KNWMLIN + (KNWPAR * fabs( DRMAN ))) * DRMAN;

			DR_LIM = range( -0.5, DRSHAP, 0.5 );

			fltrNYBF->SetGains(
				1.0 - ((8.0 * dt) / ((dt * ((5.0 * dt) + 12.0) + 2.0))),
				((10.0 * dt * dt) - 4.0) / ((dt * ((5.0 * dt) + 12.0) + 2.0)),
				1.0 - ((16.0 * dt) / ((dt * ((5.0 * dt) + 12.0) + 2.0))),
				((10.0 * dt * dt) - 4.0) / ((dt * ((5.0 * dt) + 12.0) + 2.0)),
				1.0 - ((24.0 * dt) / ((dt * ((5.0 * dt) + 12.0) + 2.0)))
				);
			DWNCPP = DR_LIM - fltrNYBF->GetValue( GNYR * NY );
			DWNCP = DWNCPP * GNYNWS;
		}
	}
	else
	{
		DWNCP = 0.0;
		TNWFADE->SetValue( 1.0 );
	}

	DWNCP = (1.0 - TNWFADE->Fade( dt )) * DWNCP;// HACK using "indirect" fader from 1 to 0 instead feeding actual signal and initial NW position

	// command NWS
	DNWC = range( -NWS_LIM, DWNCP, NWS_LIM );
	return;
}

void AerojetDAP::RECON( void )
{
	if (QBAR >= QBARLOWQ)
	{
		if (LOWQ) LOWMIDQ = true;
		LOWQ = false;
	}
	if (QBAR >= QBARLOWMIDQ) LOWMIDQ = false;
	if (QBAR >= QBARHIGHQ) HIGHQ = true;

	if (WRAP == 1)
	{
		if ((QBAR > 10.0) && (VE > 1000.0)) WRAP = 2;
	}
	else if (WRAP == 2)
	{
		if (VE <= 1000.0) WRAP = 1;
	}
	return;
}
}
