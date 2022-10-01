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
********************************************/
#include "AscentDAP.h"
#include "../Atlantis.h"
#include <MathSSV.h>
#include "SSME_SOP.h"
#include "SSME_Operations.h"
#include "MPS_ATVC_CMD_SOP.h"
#include "SRBSepSequence.h"
#include "RHC_SOP.h"
#include "SBTC_SOP.h"
#include "IDP.h"
#include "..\mission\Mission.h"
#include <cassert>
#include <EngConst.h>


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

	K_CMD = 100;

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

	dogleg = false;

	AutoFCS = true;

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
	return;
}

void AscentDAP::SecondStageGuidance( double dt )
{
	Navigate();// update speed post MECO

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
	mission::Mission* pMission = STS()->GetMissionData();
	TgtInc=pMission->GetMECOInc()*DEG;
	TgtFPA=pMission->GetMECOFPA()*DEG;
	TgtAlt=pMission->GetMECOAlt();
	TgtSpd=pMission->GetMECOVel() - (SSMETailoffDV[2] / MPS2FPS);

	hEarth = STS()->GetSurfaceRef();
	//calculate heading
	double latitude, longitude;
	STS()->GetEquPos(longitude, latitude, EarthRadius);
	if(abs(cos(TgtInc*RAD))>abs(cos(latitude))) {
		radTargetHeading=PI05;
		//TgtInc = latitude*DEG;
		dogleg = true;
	}
	else {
		// there are two possible launch headings: going north and going south
		// for TgtInc < 65 deg (KSC launches) we want northerly heading; max. inclination of KSC launch was 62 degrees (with dog-leg)
		// for TgtInc > 65 deg (VAFB) we want southerly heading
		double InHeading = asin(cos(TgtInc*RAD)/cos(latitude));
		double xVel, yVel;
		xVel = TgtSpd*cos(TgtFPA*RAD)*sin(InHeading)-464.581*cos(latitude);
		yVel = TgtSpd*cos(TgtFPA*RAD)*cos(InHeading);
		radTargetHeading=atan2(xVel, yVel); // northerly heading
		if(TgtInc > 65.0) radTargetHeading = PI - radTargetHeading; // if heading is negative, this is retrograde inclination; use southerly heading
	}

	mu=GGRAV*oapiGetMass(hEarth);
	SidDay = oapiGetPlanetPeriod(hEarth);
	//calculate apogee/perigee
	EarthRadius = oapiGetSize(hEarth);
	TgtRad = TgtAlt+EarthRadius;
	double C = (2*mu)/(TgtRad*TgtSpd*TgtSpd);
	double det = C*C + (4*(1-C)*pow(cos(TgtFPA*RAD), 2));
	double root1 = (-C-sqrt(det))/(2*(1-C));
	double root2 = (-C+sqrt(det))/(2*(1-C));
	if(root1>root2) {
		TAp=root1*TgtRad;
		TPe=root2*TgtRad;
	}
	else {
		TAp=root2*TgtRad;
		TPe=root1*TgtRad;
	}
	//calclate Ecc
	TEcc= (2*TAp)/(TPe+TAp) - 1.0;
	//TPe-=Radius;
	//TAp-=Radius;
	//calculate TrA
	double h = TgtRad*TgtSpd*sin((90+TgtFPA)*RAD);
	TTrA=asin((h*TgtSpd*sin(TgtFPA*RAD))/(mu*TEcc)); //angle in Rad
	//Calculate orbit parameters for this ta
	//aOrbit=TPe/(1-TEcc);
	//p=aOrbit*(1-TEcc*TEcc);

	//PEG
	STS()->GetRelativePos(hEarth,rh0);
	rh0=rh0*(1/length(rh0));
	A=0.0;
	//B=0.0;
	C=0.0;
	//D=0.0;
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
			K_CMD = ReadCOMPOOL_IS( SCP_KMAX );// throttle to mission power level

			// update MECO targets
			if (NSSME > 0) TgtSpd = STS()->GetMissionData()->GetMECOVel() - (SSMETailoffDV[NSSME - 1] / MPS2FPS);
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
			K_CMD = THROT[J - 1];
			J = J + 1;
		}
	}

	if (pSBTC_SOP->GetManThrottle() == false) pSSME_SOP->SetThrottlePercent( K_CMD );
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
			K_CMD = ReadCOMPOOL_IS( SCP_KMAX );// throttle to mission power level

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
	if ((STS()->GetMass() * KG2LBM * LBS2SL) < MASS_LOW_LEVEL) pSSME_Operations->SetLowLevelSensorArmFlag();

	// check for MECO
	if ((inertialVelocity >= TgtSpd) && (pSBTC_SOP->GetManThrottle() == false))
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
		if (K_CMD != KMIN)// if at MPL can't do more
		{
			if (dt_thrt_glim >= 0.1)// wait while throttling (10%/sec throttle change = 0.1s delay)
			{
				K_CMD--;// throttle back 1%
				if (K_CMD < KMIN) K_CMD = KMIN;// don't go below MPL
				dt_thrt_glim = 0;// reset
			}
			else dt_thrt_glim += dt;
		}
	}

	// fine count
	// HACK only throttle back, no real count for now
	if ((timeRemaining <= 6) && (finecount == false))
	{
		if (NSSME == 3 ) K_CMD = ReadCOMPOOL_IS( SCP_KMIN );
		else K_CMD = K_CO_MAX;
		finecount = true;
		oapiWriteLogV( "Fine Count (throttle to %d%%) @ MET %.2f", K_CMD, STS()->GetMET() );
	}

	if (pSBTC_SOP->GetManThrottle() == false) pSSME_SOP->SetThrottlePercent( K_CMD );
	//else pSBTC_SOP->GetManThrottleCommand();
	return;
}

void AscentDAP::MajorCycle()
{
	radTargetHeading = CalculateAzimuth();
	Estimate();
	Guide();
}

double AscentDAP::CalculateAzimuth()
{
	double true_azimuth=0;
	double latitude, longitude;
	double azimuth/*,equator_v/*,target_radius*/;
	double tgt_orbit_v[2],lnch_v[2],current_vel[2]; //vectors
	VECTOR3 vel, horizonvel;
	double temp;

	STS()->GetEquPos(longitude, latitude, temp);
	STS()->GetRelativeVel(hEarth, vel);
	MATRIX3 rot;
	STS()->GetRotationMatrix(rot);
	vel = tmul(rot, vel);
	STS()->HorizonRot(vel, horizonvel);
	current_vel[1] = horizonvel.data[0]; //East
	current_vel[0] = horizonvel.data[2];  // North

	if (latitude > (TgtInc * RAD)) azimuth = PI05;
	else azimuth = asin(range(-1, cos(TgtInc*RAD)/cos(latitude), 1));  // this equ doesn't take rotation into accout
	//equator_v=EarthRadius*(PI2/SidDay);   //equator velocity
	if ((dogleg == true) && (latitude < (TgtInc * RAD))) tgt_orbit_v[0]=-TgtSpd*cos(TgtFPA*RAD)*cos(azimuth);
	else tgt_orbit_v[0]=TgtSpd*cos(TgtFPA*RAD)*cos(azimuth) * sign( 65 - TgtInc ); // northern velocity
	tgt_orbit_v[1]=TgtSpd*cos(TgtFPA*RAD)*sin(azimuth); // eastern velocity
	//lnch_v[0]= abs(tgt_orbit_v[0]) - abs(current_vel[0]); // taking current velocity into accout for CC (North); assume both values have same sign
	//lnch_v[1]= abs(tgt_orbit_v[1]) - abs(current_vel[1]); // taking current velocity into accout for CC (East); assume both values have same sign
	lnch_v[0]= fabs( tgt_orbit_v[0] - current_vel[0] );
	lnch_v[1]= fabs( tgt_orbit_v[1] - current_vel[1] );

	//if (lnch_v[0]==0) lnch_v[0]=0.01; //div by zero protection
	/*if(lnch_v[0]==0.0) { //div by zero protection
		if(lnch_v[1]>0) true_azimuth=PI05;
		else true_azimuth=-PI05;
	}*/
	//else true_azimuth = atan(lnch_v[1]/lnch_v[0]); // tan(azimuth) = eastern_vel / northern_vel
	true_azimuth = atan2(lnch_v[1], lnch_v[0]); // tan(azimuth) = eastern_vel / northern_vel
	if ((current_vel[0] < 0.0) && (TgtInc > 65)) true_azimuth = PI + true_azimuth;
	if ((tgt_orbit_v[1] > 0.0) && (TgtInc > 65)) true_azimuth = PI2 - true_azimuth;
	//if(current_vel[0] < 0.0) true_azimuth = PI - true_azimuth; // we are heading south, so need to use southerly heading
	//if(current_vel[1] < 0.0) true_azimuth = PI2 - true_azimuth; // retrograde inclination

	if ((dogleg == true) && (latitude < (TgtInc * RAD))) true_azimuth = PI - true_azimuth;

	return true_azimuth;
}

void AscentDAP::Navigate()
{
	VECTOR3 rv, vv, hv;
	STS()->GetRelativePos(STS()->GetSurfaceRef(),rv);
	STS()->GetRelativeVel(STS()->GetSurfaceRef(),vv);
	radius=length(rv);
	inertialVelocity=length(vv);
	hv=crossp(rv,vv);
	h=length(hv);
	rh=rv*(1/radius);
	hh=hv*(1/h);
	thetah=crossp(hh,rh);
	vr=dotp(vv,rh);
	vtheta=dotp(vv,thetah);
	omega=vtheta/radius;
	//w=x/(radius*radius);
	//last_target_pitch=target_pitch;
	//last_target_yaw=target_yaw;
	//last_target_roll=target_roll;
	//oapiGetFocusPitch(&pitch);

	double F=STS()->CalcNetSSMEThrust();
	double m=STS()->GetMass();
	Isp=STS()->GetSSMEISP();
	thrustAcceleration=F/m;
	tau=Isp/thrustAcceleration;
	//theta=acos(dotp(rh0,rh));
	//phi=acos(dotp(rh,rmh));
	//VECTOR3 rhxrmh=crossp(rh,rmh);
	//if(rhxrmh.y>0)phi=PI2-phi;
}

void AscentDAP::Estimate()
{
	double rbar=(radius+TgtRad)/2;
	/*double num=mu/(rbar*rbar)-omega*omega*radius;
	double fr=A+num/a0;
	double fdotr=B+(num/a(T)-fr)/T;
	double fh=0; //No yaw guidance yet
	double fdoth=0;
	double ftheta=1-fr*fr/2-fh*fh/2;  //Small number approximation to hypot
	double fdottheta=-(fr*fdotr+fh*fdoth);
	double fdotdottheta=-(fdotr*fdotr+fdoth*fdoth)/2;*/

	//Estimate true anomaly at cutoff
	//double d3=h*vr/(radius*radius*radius);
	//double d4=(h*(TgtSpd*sin(TgtFPA*RAD))/(TgtRad*TgtRad*TgtRad)-d3)/T;
	//double simdtheta=(h/(radius*radius))*T+(ftheta*c0(T)+fdottheta*cn(T,1)+fdotdottheta*cn(T,2))/rbar-d3*T*T-d4*T*T*T/3.0;
	//thetaT=theta+simdtheta;
	double p=(TPe/(1-TEcc))*(1-TEcc*TEcc);
	//Estimate time of cutoff
	double hT=sqrt(mu*p);
	double deltah=hT-h;
	double deltav=deltah/rbar;
	timeRemaining=tau*(1-exp(-deltav/Isp));
	if(timeRemaining>1000) timeRemaining=1000;
	//Any comparison with NaN is false, so
	//invert these tests so it's true if NaN
	if(!(tau>timeRemaining) || !(0<timeRemaining)) timeRemaining=tau-10;
	//  if(!(tau>T)|!(0<T))T=T2;
	//metCutoff=timeRemaining + met;
}

void AscentDAP::Guide()
{
	//Calculate pitch steering coefficients
	double a=b0(timeRemaining);
	double b=bn(timeRemaining,1);
	double c=c0(timeRemaining);
	double d=cn(timeRemaining,1);
	double y1=TgtSpd*sin(TgtFPA*RAD)-vr;
	double y2=TgtRad-vr*timeRemaining-radius;
	double D=a*d-b*c;
	A=(d*y1-b*y2)/D;
	//B=(a*y2-c*y1)/D;

	//VECTOR3 ang_vel;
	C=(mu/(radius*radius)-(omega*omega*radius))/thrustAcceleration;
	//target_roll=0;
	//target_yaw=0;
	//fhdotrh=A+B*(met-TLastAB)+C;
	double fhdotrh=A+C;
	if(fabs(fhdotrh)>1) {
		//Commanded to do a cos(pitch) out of range
		target_pitch = STS()->GetPitch()*DEG;
	}
	else {
		target_pitch=(PI05-acos(fhdotrh))*DEG;
	}

	//target_pitch = target_pitch+ThrAngleP; //yaw angle ignored for now
	CmdPDot=(target_pitch-ThrAngleP*cos(STS()->GetBank())-STS()->GetPitch()*DEG)/(2*ASCENT_MAJOR_CYCLE);
	//CmdPDot=(target_pitch-ThrAngleP*cos(GetBank())-GetPitch()*DEG)/TMajorCycle;
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
	return degReqdRatesGuidance;
}

double AscentDAP::GetAutoThrottleCommand( void ) const
{
	return K_CMD;
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
	return TgtSpd;
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

double AscentDAP::GetTargetHeading( void ) const
{
	return radTargetHeading;
}

bool AscentDAP::GetFCSmode( void ) const
{
	return AutoFCS;
}
};
