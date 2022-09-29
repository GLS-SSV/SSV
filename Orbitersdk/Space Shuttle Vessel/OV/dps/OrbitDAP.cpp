/******* SSV File Modification Notice *******
Date         Developer
2020/04/07   GLS
2020/05/08   GLS
2020/05/17   GLS
2020/05/23   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/26   GLS
2022/02/17   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/05/02   GLS
2022/06/10   GLS
2022/06/23   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "OrbitDAP.h"
#include "IDP.h"
#include "../vc/MDU.h"
#include <MathSSV.h>
#include "../ParameterValues.h"
#include "RHC_SOP.h"
#include "THC_SOP.h"
#include "OMS_TVC_Command_SOP.h"
#include "StateVectorSoftware.h"
#include "../Atlantis.h"


namespace dps
{
	//Post Contact Thrusting
	constexpr double PCT_STAGE1 = 0.56;
	//period (s) for initial jet firing
	constexpr double PCT_STAGE2 = 1.52;
	//period (s) between jet firings
	constexpr double PCT_STAGE3 = 2.40;
	//period (s) for second jet firing

	constexpr int NoseRotThrusters[6] = {0, 3, 6, 8, 10, 13};
	constexpr int NosePitchThrusters[2] = {0, 3};
	constexpr int NoseYawThrusters[2] = {6, 8};
	//constexpr int NoseRollThrusters[2] = {10, 13};
	constexpr int AftRotThrusters[10] = {1, 2, 4, 5, 7, 9, 11, 12, 14, 15};
	constexpr int AftPitchThrusters[4] = {1, 2, 4, 5};
	constexpr int AftYawThrusters[2] = {7, 9};
	//constexpr int AftRollThrusters[4] = {11, 12, 14, 15};
	//RCS Thruster Groups

static void SaveAttManeuver(FILEHANDLE scn, char* item, const AttManeuver& maneuver)
{
	char cbuf[255];
	VECTOR3 eulerAngles = GetYZX_PYRAnglesFromMatrix(maneuver.tgtMatrix);
	sprintf_s(cbuf, 255, "%d %f %f %f", maneuver.Type, eulerAngles.data[PITCH], eulerAngles.data[YAW], eulerAngles.data[ROLL]);
	oapiWriteScenario_string(scn, item, cbuf);
}

static void LoadAttManeuver(const char* value, AttManeuver& maneuver)
{
	int nTemp;
	VECTOR3 vTemp;
	sscanf_s(value, "%d%lf%lf%lf", &nTemp, &vTemp.data[PITCH], &vTemp.data[YAW], &vTemp.data[ROLL]);

	if(nTemp == AttManeuver::MNVR || nTemp == AttManeuver::TRK) {
		maneuver.IsValid = true;
		maneuver.Type = static_cast<AttManeuver::TYPE>(nTemp);
		maneuver.tgtMatrix = GetRotationMatrixYZX(_V(vTemp.data[ROLL], vTemp.data[PITCH], vTemp.data[YAW]));
	}
}

OrbitDAP::OrbitDAP(SimpleGPCSystem* pGPC)
: SimpleGPCSoftware(pGPC, "OrbitDAP"),
OMSTVCControlP(5.0, 0.0, 0.5, -6.0, 6.0 ), OMSTVCControlY( 4.0, 0.0, 0.75, -7.0, 7.0 ), OMSTVCControlR(5.0, 0.0, 0.5, -6.0, 6.0 ),
ControlMode(RCS),
DAPMode(PRI), DAPSelect(A), DAPControlMode(INRTL), editDAP(-1),
ManeuverStatus(MNVR_OFF),
bFirstStep(true), lastStepdt(1.0),
PCTArmed(false), PCTActive(false),
pStateVector(NULL)
{
	OMSTrim = _V(0.0, 0.0, 0.0);
	degReqdRates = _V(0.0, 0.0, 0.0);
	TransPulseDV = _V(0.0, 0.0, 0.0);
	ATT_ERR = _V(0.0, 0.0, 0.0);
	REQD_ATT = _V(0.0, 0.0, 0.0);

	for(unsigned int i=0;i<4;i++) START_TIME[i] = 0;
	MNVR_OPTION = _V(0.0, 0.0, 0.0);
	TGT_ID=2;
	BODY_VECT=1;
	P=0;
	Y=0;
	OM=-1;
	RA = 0.0;
	DEC = 0.0;
	LAT = 0.0;
	LON = 0.0;
	_ALT = 0.0;

	ActiveManeuver.IsValid = false;
	CurManeuver.IsValid = false;
	FutManeuver.IsValid = false;

	Torque.data[PITCH]=ORBITER_PITCH_TORQUE;
	Torque.data[YAW]=ORBITER_YAW_TORQUE;
	Torque.data[ROLL]=ORBITER_ROLL_TORQUE;

	// DAP A (numbers for typical ISS DAP A1 - NOM)
	RotMode[0] = DISC_RATE;
	TransMode[0] = NORM;
	RotPulseInProg[0] = false;
	TransPulseInProg[0] = false;
	RotatingAxis[0] = false;
	NullingRates[0] = false;
	DAPConfiguration[0].PRI_ROT_RATE = 0.2;
	DAPConfiguration[0].PRI_ATT_DB = 5.0;
	DAPConfiguration[0].PRI_RATE_DB = 0.2;
	DAPConfiguration[0].PRI_ROT_PLS = 0.1;
	DAPConfiguration[0].PRI_COMP = 0.0;
	DAPConfiguration[0].PRI_P_OPTION = 0;
	DAPConfiguration[0].PRI_Y_OPTION = 0;
	DAPConfiguration[0].PRI_TRAN_PLS = 0.1;
	DAPConfiguration[0].ALT_RATE_DB = 0.2;
	DAPConfiguration[0].ALT_ON_TIME = 0.08;
	DAPConfiguration[0].ALT_DELAY = 0.0;
	DAPConfiguration[0].ALT_JET_OPT = 0;
	DAPConfiguration[0].ALT_JETS = 2;
	DAPConfiguration[0].VERN_ROT_RATE = 0.2;
	DAPConfiguration[0].VERN_ATT_DB = 1.0;
	DAPConfiguration[0].VERN_RATE_DB = 0.020;
	DAPConfiguration[0].VERN_ROT_PLS = 0.01;
	DAPConfiguration[0].VERN_COMP = 0.0;
	DAPConfiguration[0].VERN_CNTL_ACC = 0;

	// DAP B (numbers for typical ISS DAP B10 - Docking)
	RotMode[1] = DISC_RATE;
	TransMode[1] = NORM;
	RotPulseInProg[1] = false;
	TransPulseInProg[1] = false;
	RotatingAxis[1] = false;
	NullingRates[1] = false;
	DAPConfiguration[1].PRI_ROT_RATE = 0.05;
	DAPConfiguration[1].PRI_ATT_DB = 0.6;
	DAPConfiguration[1].PRI_RATE_DB = 0.1;
	DAPConfiguration[1].PRI_ROT_PLS = 0.04;
	DAPConfiguration[1].PRI_COMP = 0.0;
	DAPConfiguration[1].PRI_P_OPTION = 2;
	DAPConfiguration[1].PRI_Y_OPTION = 2;
	DAPConfiguration[1].PRI_TRAN_PLS = 0.01;
	DAPConfiguration[1].ALT_RATE_DB = 0.1;
	DAPConfiguration[1].ALT_ON_TIME = 0.08;
	DAPConfiguration[1].ALT_DELAY = 0.0;
	DAPConfiguration[1].ALT_JET_OPT = 2;
	DAPConfiguration[1].ALT_JETS = 2;
	DAPConfiguration[1].VERN_ROT_RATE = 0.05;
	DAPConfiguration[1].VERN_ATT_DB = 0.5;
	DAPConfiguration[1].VERN_RATE_DB = 0.020;
	DAPConfiguration[1].VERN_ROT_PLS = 0.02;
	DAPConfiguration[1].VERN_COMP = 0.0;
	DAPConfiguration[1].VERN_CNTL_ACC = 0;

	// edit DAP
	RotMode[2] = DISC_RATE;
	TransMode[2] = NORM;
	RotPulseInProg[2] = false;
	TransPulseInProg[2] = false;
	RotatingAxis[2] = false;
	NullingRates[2] = false;
	DAPConfiguration[2].PRI_ROT_RATE = 2.0;
	DAPConfiguration[2].PRI_ATT_DB = 5.0;
	DAPConfiguration[2].PRI_RATE_DB = 0.2;
	DAPConfiguration[2].PRI_ROT_PLS = 0.1;
	DAPConfiguration[2].PRI_COMP = 0.0;
	DAPConfiguration[2].PRI_P_OPTION = 0;
	DAPConfiguration[2].PRI_Y_OPTION = 0;
	DAPConfiguration[2].PRI_TRAN_PLS = 0.1;
	DAPConfiguration[2].ALT_RATE_DB = 0.2;
	DAPConfiguration[2].ALT_ON_TIME = 0.08;
	DAPConfiguration[2].ALT_DELAY = 0.0;
	DAPConfiguration[2].ALT_JET_OPT = 0;
	DAPConfiguration[2].ALT_JETS = 2;
	DAPConfiguration[2].VERN_ROT_RATE = 0.1;
	DAPConfiguration[2].VERN_ATT_DB = 1.0;
	DAPConfiguration[2].VERN_RATE_DB = 0.020;
	DAPConfiguration[2].VERN_ROT_PLS = 0.01;
	DAPConfiguration[2].VERN_COMP = 0.0;
	DAPConfiguration[2].VERN_CNTL_ACC = 0;

	ERRTOT = true;

	RA_DEC_flash = false;
	LAT_LON_ALT_flash = false;
	P_Y_flash = false;
}

OrbitDAP::~OrbitDAP()
{
}

void OrbitDAP::InitOMSTVC( const VECTOR3& Trim, CONTROL_MODE Mode )
{
	OMSTVCControlP.Reset();
	OMSTVCControlY.Reset();
	OMSTVCControlR.Reset();
	OMSTrim = Trim;
	OMSAttBias = _V( 0.0, 0.0, 0.0 );
	// initial gimbal command
	if (Mode != RIGHT_OMS)
	{
		pOMSTVCCMD_SOP->SetPitch( LEFT, OMSTrim.data[0] );
		pOMSTVCCMD_SOP->SetYaw( LEFT, OMSTrim.data[1] );
	}
	if (Mode != LEFT_OMS)
	{
		pOMSTVCCMD_SOP->SetPitch( RIGHT, OMSTrim.data[0] );
		pOMSTVCCMD_SOP->SetYaw( RIGHT, OMSTrim.data[2] );
	}
	return;
}

void OrbitDAP::UseOMSTVC( CONTROL_MODE Mode )
{
	if(Mode != RCS) ControlMode = Mode;
	return;
}

void OrbitDAP::UseRCS()
{
	ControlMode = RCS;
}

OrbitDAP::DAP_CONTROL_MODE OrbitDAP::GetDAPMode() const
{
	return DAPControlMode;
}

/*void OrbitDAP::ManeuverToLVLHAttitude(const VECTOR3& degLVLHAtt)
{
	LoadCurLVLHManeuver(degLVLHAtt*RAD);
}*/

void OrbitDAP::ManeuverToINRTLAttitude(const VECTOR3& degINRTLAtt)
{
	//VECTOR3 radOrbiterAtt = ConvertAnglesBetweenM50AndOrbiter(degINRTLAtt*RAD, true);
	MATRIX3 OrbiterAtt = GetRotationMatrixYZX(_V(degINRTLAtt.data[ROLL], degINRTLAtt.data[PITCH], degINRTLAtt.data[YAW])*RAD);
	LoadCurINRTLManeuver(OrbiterAtt);
}

void OrbitDAP::LoadCurLVLHManeuver(const MATRIX3& tgtMatrixLVLH)
{
	CurManeuver.IsValid = true;
	CurManeuver.tgtMatrix = tgtMatrixLVLH;
	CurManeuver.Type = AttManeuver::TRK;
	if(DAPControlMode == AUTO) StartCurManeuver();
}

void OrbitDAP::LoadFutLVLHManeuver(const MATRIX3& tgtMatrixLVLH)
{
	FutManeuver.IsValid = true;
	FutManeuver.tgtMatrix = tgtMatrixLVLH;
	FutManeuver.Type = AttManeuver::TRK;
}

void OrbitDAP::LoadCurINRTLManeuver(const MATRIX3& tgtMatrixM50)
{
	CurManeuver.IsValid = true;
	CurManeuver.tgtMatrix = tgtMatrixM50;
	CurManeuver.Type = AttManeuver::MNVR;
	if(DAPControlMode == AUTO) StartCurManeuver();
}

void OrbitDAP::LoadFutINRTLManeuver(const MATRIX3& tgtMatrixM50)
{
	FutManeuver.IsValid = true;
	FutManeuver.tgtMatrix = tgtMatrixM50;
	FutManeuver.Type = AttManeuver::MNVR;
}

void OrbitDAP::StartCurManeuver()
{
	if(CurManeuver.IsValid) {
		//if(CurManeuver.Type == AttManeuver::MNVR) StartINRTLManeuver(CurManeuver.radTargetAttOrbiter);
		//else if(CurManeuver.Type == AttManeuver::TRK) StartLVLHManeuver(CurManeuver.radTargetLVLHAtt);
		StartManeuver(CurManeuver.tgtMatrix, CurManeuver.Type);
	}
}

void OrbitDAP::StartManeuver(const MATRIX3& tgtAtt, AttManeuver::TYPE type)
{
	ActiveManeuver.tgtMatrix = tgtAtt;
	ActiveManeuver.Type = type;
	ActiveManeuver.IsValid = true;

	ManeuverStatus = MNVR_IN_PROGRESS;

	if(ActiveManeuver.Type == AttManeuver::MNVR) {
		degNullRates = _V(0, 0, 0);
		// calculate M50 target att
		REQD_ATT = GetYZX_PYRAnglesFromMatrix(ActiveManeuver.tgtMatrix)*DEG;
		// correct range
		if (REQD_ATT.x < 0.0) REQD_ATT.x += 360.0;
		if (REQD_ATT.y < 0.0) REQD_ATT.y += 360.0;
		if (REQD_ATT.z < 0.0) REQD_ATT.z += 360.0;

		// calculate time to reach target attitude
		VECTOR3 Axis;
		MATRIX3 AttError = GetRotationErrorMatrix(curM50Matrix, tgtAtt);
		double Angle = CalcEulerAngle(AttError, Axis);
		mnvrCompletionMET = STS()->GetMET() + (Angle*DEG)/degRotRate;
		lastUpdateTime = 0.0;
	}
	else {
		mnvrCompletionMET = STS()->GetMET();
		lastUpdateTime = -100.0;
	}
}

bool OrbitDAP::GetRHCRequiredRates()
{
	bool outOfDetent = false;
	double RHC[3];
	RHC[0] = pRHC_SOP->GetPitchCommand();
	RHC[1] = pRHC_SOP->GetYawCommand();
	RHC[2] = pRHC_SOP->GetRollCommand();
	bool RHCdetent[3];
	RHCdetent[0] = pRHC_SOP->GetPitchDetent();
	RHCdetent[1] = pRHC_SOP->GetYawDetent();
	RHCdetent[2] = pRHC_SOP->GetRollDetent();
	bool RHCpastsoftstop[3];
	RHCpastsoftstop[0] = pRHC_SOP->GetPitchPastSoftStop();
	RHCpastsoftstop[1] = pRHC_SOP->GetYawPastSoftStop();
	RHCpastsoftstop[2] = pRHC_SOP->GetRollPastSoftStop();

	for(unsigned int i=0;i<3;i++) {
		if (RHCdetent[i] == false)
		{
			outOfDetent = true;
			if (RHCpastsoftstop[i] == false)
			{
				if(RotMode[i]==DISC_RATE) { // DISC RATE
					// if RHC was pushed past soft stop previously (high rotation rates), maintain high rotation rate; otherwise rotate at specified rate
					degReqdRates.data[i] = max(degRotRate, abs(degAngularVelocity.data[i]))*sign( RHC[i] );
				}
				else if(!RotPulseInProg[i]) { // PULSE
					degReqdRates.data[i] = degReqdRates.data[i]+degRotPulse*sign( RHC[i] );
					RotPulseInProg[i]=true;
				}
			}
			else {
				degReqdRates.data[i] = 1000*sign( RHC[i] );
			}
		}
	}
	return outOfDetent;
}

void OrbitDAP::HandleTHCInput(double simdt)
{
	int THC[3];
	THC[0] = pTHC_SOP->GetXCommand();
	THC[1] = pTHC_SOP->GetYCommand();
	THC[2] = pTHC_SOP->GetZCommand();

	for(int i=0;i<3;i++) {
		if (THC[i] != 0)
		{
			if(TransMode[i]==NORM) {
				TransThrusterCommands[i].SetLine(static_cast<float>( sign( THC[i] ) ));
			}
			else if(TransMode[i]==TRANS_PULSE && !TransPulseInProg[i]) {
				TransPulseInProg[i]=true;
				TransPulseDV.data[i] = TransPulse*sign( THC[i] );
			}
			else {
				TransThrusterCommands[i].ResetLine();
			}
		}
		else {
			TransThrusterCommands[i].ResetLine();
		}

		if(TransPulseInProg[i]) {
			if(!Eq(TransPulseDV.data[i], 0.0, 0.001)) {
				TransThrusterCommands[i].SetLine(static_cast<float>( sign(TransPulseDV.data[i]) ));
				// calculate DV so far
				VECTOR3 ThrustVector;
				STS()->GetThrustVector(ThrustVector);
				ThrustVector = _V(ThrustVector.z, ThrustVector.x, -ThrustVector.y); // convert from Orbiter frame to shuttle frame
				double acc = (ThrustVector.data[i]/OrbiterMass)*simdt;
				if(abs(TransPulseDV.data[i]) <= abs(acc/2.0)) { //minimize error
					TransPulseDV.data[i]=0.000;
				}
				else {
					TransPulseDV.data[i] -= acc;
				}
			}
			else {
				//if THC is in detent and pulse is complete, allow further pulses
				if (THC[i] == 0) TransPulseInProg[i]=false;
				TransThrusterCommands[i].ResetLine();
			}
		}
	}
}

void OrbitDAP::CalcEulerAxisRates()
{
	double timeAcc = max(1.0, oapiGetTimeAcceleration());

	VECTOR3 RotationAxis;
	double RotationAngle=CalcEulerAngle(attErrorMatrix, RotationAxis);
	//Rates=RotationAxis*-RotRate;
	RotationAxis = _V(RotationAxis.y, RotationAxis.z, RotationAxis.x); // change rotation axis so PYR axes are mapped correctly
	for(unsigned int i=0;i<3;i++) {
		if(DAPControlMode==AUTO || RotMode[i]==DISC_RATE) {
			degReqdRates.data[i]=RotationAxis.data[i]*degRotRate;
			if(abs(ATT_ERR.data[i]) <= NullStartAngle(abs(radAngularVelocity.data[i]), OrbiterMass, PMI.data[i], Torque.data[i]/timeAcc)) {
				degReqdRates.data[i] = 0.0;
				RotatingAxis[i] = false;
				NullingRates[i] = true;
			}
			else RotatingAxis[i] = true;
		}
		else { // PULSE mode; maintain current rate
			degReqdRates.data[i] = degAngularVelocity.data[i];
		}
	}
}

void OrbitDAP::CalcMultiAxisRates(const VECTOR3& degNullRatesLocal)
{
	double timeAcc = max(1.0, oapiGetTimeAcceleration());

	for(unsigned int i=0;i<3;i++) {
		if(DAPControlMode==AUTO || RotMode[i]==DISC_RATE) {
			degReqdRates.data[i]=0.0;
			if((RotatingAxis[i] || abs(ATT_ERR.data[i])>degAttDeadband)) {
				if(abs(ATT_ERR.data[i])<0.05) {
					RotatingAxis[i]=false;
					NullingRates[i] = true;
				}
				else {
					RotatingAxis[i]=true;
					if(abs(ATT_ERR.data[i]) <= NullStartAngle(abs(radAngularVelocity.data[i]), OrbiterMass, PMI.data[i], Torque.data[i]/timeAcc)) {
						degReqdRates.data[i] = 0.0;
					}
					else {
						degReqdRates.data[i] = sign(ATT_ERR.data[i])*range(0.05*degRotRate, abs(ATT_ERR.data[i])/5.0, 0.1*degRotRate);
					}
				}
			}
		}
		else { // PULSE mode; maintain current rate
			degReqdRates.data[i] = degAngularVelocity.data[i];
		}
	}

	// add null rates to maintain attitude in rotation frame
	for(int i=0;i<3;i++) {
		if(DAPControlMode==AUTO || RotMode[i]==DISC_RATE) degReqdRates.data[i]+=degNullRatesLocal.data[i];
	}
}

void OrbitDAP::UpdateNullRates()
{
	ELEMENTS el;
	ORBITPARAM param;
	STS()->GetElements(STS()->GetGravityRef(), el, &param);
	double orb_rad = 360.0/param.T;

	VECTOR3 tgtLVLHAtt = GetYZX_PYRAnglesFromMatrix(ActiveManeuver.tgtMatrix);
	degNullRates.data[ROLL] = -orb_rad*sin(tgtLVLHAtt.data[YAW]);
	degNullRates.data[PITCH] = -orb_rad*cos(tgtLVLHAtt.data[YAW])*cos(tgtLVLHAtt.data[ROLL]);
	degNullRates.data[YAW] = orb_rad*cos(tgtLVLHAtt.data[YAW])*sin(tgtLVLHAtt.data[ROLL]);
}

void OrbitDAP::SetRates(const VECTOR3 &degRates, double simdt)
{
	const VECTOR3 PRI_LIMITS = _V(0.005, 0.005, 0.005);
	const VECTOR3 VERN_LIMITS = _V(0.0015, 0.0015, 0.0015);
	//static char buf[100];


	//double dDiff;
	VECTOR3 Error = degRates-degAngularVelocity;
	/*Error.data[YAW] = Error.data[YAW]; // temporary
	Error.data[ROLL] = Error.data[ROLL];*/



	VECTOR3 Limits;
	double MaxThrusterLevel;
	double timeAcc = max(1.0, oapiGetTimeAcceleration());
	if(DAPMode != VERN) { // PRI/ALT
		for(unsigned int i=0;i<3;i++) {
			//if(RotatingAxis[i] || NullingRates[i]) Limits.data[i] = max(PRI_LIMITS.data[i], 0.5*RotationRateChange(OrbiterMass, PMI.data[i], Torque.data[i]/timeAcc, simdt));
			if(RotatingAxis[i]) Limits.data[i] = max(2.0*PRI_LIMITS.data[i], 0.5*RotationRateChange(OrbiterMass, PMI.data[i], Torque.data[i]/timeAcc, simdt));
			else if(NullingRates[i] || RotPulseInProg[i]) Limits.data[i] = max(PRI_LIMITS.data[i], 0.5*RotationRateChange(OrbiterMass, PMI.data[i], Torque.data[i]/timeAcc, simdt));
			else Limits.data[i] = degRateDeadband;
		}
		MaxThrusterLevel = 1.0/timeAcc;
	}
	else { // VERN
		for(unsigned int i=0;i<3;i++) {
			if(RotatingAxis[i] || NullingRates[i]) Limits.data[i] = max(VERN_LIMITS.data[i], 0.5*RotationRateChange(OrbiterMass, PMI.data[i], 0.1*Torque.data[i]/timeAcc, simdt));
			else Limits.data[i] = degRateDeadband;
		}
		MaxThrusterLevel = 0.1/timeAcc;
	}
	//if(ManeuverStatus==MNVR_IN_PROGRESS) Limits=Limits*5.0;

	bool RHCdetent[3];
	RHCdetent[0] = pRHC_SOP->GetPitchDetent();
	RHCdetent[1] = pRHC_SOP->GetYawDetent();
	RHCdetent[2] = pRHC_SOP->GetRollDetent();

	for(unsigned int i=0;i<3;i++) {
		if(abs(Error.data[i])>Limits.data[i]) {
			//RotThrusterCommands[i].SetLine(static_cast<float>(MaxThrusterLevel*sign(Error.data[i])));
			double thrusterLevel = MaxThrusterLevel;
			if(DAPMode != VERN) { // for PRI/ALT, there are multiple thrusters in each direction, and we don't need to fire all of them
				double scale = abs(Error.data[i])/Limits.data[i];
				if(scale < 2) thrusterLevel = MaxThrusterLevel/3.0;
				else if(scale < 5) thrusterLevel = MaxThrusterLevel*(0.667);
			}
			RotThrusterCommands[i].SetLine(static_cast<float>(thrusterLevel*sign(Error.data[i])));
		}
		else {
			RotThrusterCommands[i].ResetLine();
			NullingRates[i] = false;
			//If RHC is out of detent, pretend pulse is still in progress
			if (RHCdetent[i] == true) RotPulseInProg[i]=false;
		}
	}




}

void OrbitDAP::OMSTVC(const VECTOR3 &AttErr, double SimDT)
{
	VECTOR3 biasedAttErr = AttErr + OMSAttBias;

	double pitchDelta = (biasedAttErr.data[PITCH] * 0.1) - degAngularVelocity.data[PITCH]; //if positive, vessel is pitching down
	double yawDelta = (biasedAttErr.data[YAW] * 0.1) - degAngularVelocity.data[YAW]; //if positive, vessel is rotating to right
	double rollDelta = (biasedAttErr.data[ROLL] * 0.1) - degAngularVelocity.data[ROLL]; //if positive, vessel is rolling to left

	bool RCSWraparound_Pitch = (fabs( biasedAttErr.data[PITCH] ) > 10.0);
	bool RCSWraparound_Yaw = (fabs( biasedAttErr.data[YAW] ) > 10.0);
	bool RCSWraparound_Roll = (fabs( biasedAttErr.data[ROLL] ) > 5.0);

	double dPitch = OMSTVCControlP.Step( -pitchDelta, SimDT );
	double dYaw = OMSTVCControlY.Step( -yawDelta, SimDT );
	double dRoll = OMSTVCControlR.Step( -rollDelta, SimDT );

	double Ltrim = 0.0;
	double Rtrim = 0.0;
	if(ControlMode!=RIGHT_OMS) //left OMS engine burning
	{
		double Pitch = dPitch + OMSTrim.data[0], Yaw = dYaw + OMSTrim.data[1];
		if(ControlMode==BOTH_OMS) Pitch-=dRoll;

		Ltrim = - dYaw;

		pOMSTVCCMD_SOP->SetPitch( LEFT, Pitch );
		pOMSTVCCMD_SOP->SetYaw( LEFT, Yaw );
	}
	if(ControlMode!=LEFT_OMS) //right OMS engine burning
	{
		double Pitch = dPitch + OMSTrim.data[0], Yaw = dYaw + OMSTrim.data[2];
		if(ControlMode==BOTH_OMS) Pitch+=dRoll;

		Rtrim = dYaw;
		if (ControlMode == BOTH_OMS) Rtrim = -Rtrim;

		pOMSTVCCMD_SOP->SetPitch( RIGHT, Pitch );
		pOMSTVCCMD_SOP->SetYaw( RIGHT, Yaw );
	}

	OMSAttBias = _V( -dPitch, Ltrim - Rtrim, -dRoll );// for next step

	double RCSpitch = 0.0;
	double RCSyaw = 0.0;
	double RCSroll = 0.0;

	if (RCSWraparound_Pitch) RCSpitch = biasedAttErr.data[PITCH] * 0.1;
	if (RCSWraparound_Yaw) RCSyaw = biasedAttErr.data[YAW] * 0.1;
	if ((ControlMode != BOTH_OMS) || (RCSWraparound_Roll)) RCSroll = biasedAttErr.data[ROLL] * 0.1;// for single-engine burns, use RCS for roll control

	// only fire the needed axis
	SetRates( _V( RCSpitch, RCSyaw, RCSroll ), SimDT );
	if (RCSpitch == 0.0) RotThrusterCommands[0].ResetLine();
	if (RCSyaw == 0.0) RotThrusterCommands[1].ResetLine();
	if (RCSroll == 0.0) RotThrusterCommands[2].ResetLine();
	return;
}

void OrbitDAP::GetAttitudeData()
{
	STS()->GetAngularVel(radAngularVelocity);
	radAngularVelocity = _V(radAngularVelocity.x, -radAngularVelocity.y, radAngularVelocity.z); // convert from Orbitersim to body axis frame
	degAngularVelocity = radAngularVelocity*DEG;

	STS()->GetRotationMatrix(curM50Matrix);
	curM50Matrix = ConvertOrbitersimRotationMatrixToM50(curM50Matrix);
	CUR_ATT = GetYZX_PYRAnglesFromMatrix(curM50Matrix)*DEG;
	// correct range
	if (CUR_ATT.x < 0.0) CUR_ATT.x += 360.0;
	if (CUR_ATT.y < 0.0) CUR_ATT.y += 360.0;
	if (CUR_ATT.z < 0.0) CUR_ATT.z += 360.0;

	OrbiterMass = STS()->GetMass();
	STS()->GetPMI(PMI);
}

void OrbitDAP::Realize()
{
	DiscreteBundle* pBundle=BundleManager()->CreateBundle("THRUSTER_CMD", 16);
	for(unsigned int i=0;i<3;i++) {
		RotThrusterCommands[i].Connect(pBundle, i);
		TransThrusterCommands[i].Connect(pBundle, i+3);
	}

	pStateVector = dynamic_cast<StateVectorSoftware*>(FindSoftware("StateVectorSoftware"));
	assert( (pStateVector != NULL) && "OrbitDAP::Realize.pStateVector" );
	pRHC_SOP = dynamic_cast<RHC_SOP*>(FindSoftware( "RHC_SOP" ));
	assert( (pRHC_SOP != NULL) && "OrbitDAP::Realize.pRHC_SOP" );
	pTHC_SOP = dynamic_cast<THC_SOP*>(FindSoftware( "THC_SOP" ));
	assert( (pTHC_SOP != NULL) && "OrbitDAP::Realize.pTHC_SOP" );
	pOMSTVCCMD_SOP = dynamic_cast<OMSTVCCMD_SOP*>(FindSoftware( "OMS_TVC_Command_SOP" ));
	assert( (pOMSTVCCMD_SOP != NULL) && "OrbitDAP::Realize.pOMSTVCCMD_SOP" );

	UpdateDAPParameters();
}

void OrbitDAP::OnPreStep(double simt, double simdt, double mjd)
{
	unsigned short CDR_SPDBK_THROT = ReadCOMPOOL_IS( SCP_LH_SPD_BK_THROT_AUTO_MAN );
	unsigned short PLT_SPDBK_THROT = ReadCOMPOOL_IS( SCP_RH_SPD_BK_THROT_AUTO_MAN );
	unsigned short CDR_BodyFlap = ReadCOMPOOL_IS( SCP_LH_BODY_FLAP_AUTO_MANUAL );
	unsigned short blank_pbi_fwd = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_X_LVLH );
	unsigned short blank_pbi_aft = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_X_LVLH );
	cdrspdbkthrot.Set( CDR_SPDBK_THROT == 1 );
	pltspdbkthrot.Set( PLT_SPDBK_THROT == 1 );
	cdrbodyflap.Set( CDR_BodyFlap == 1 );
	sparepbi.Set( (blank_pbi_fwd == 1) || (blank_pbi_aft == 1) );

	GetAttitudeData();

	// PBI input
	DAP_PBI_Press();

	// DAP lights command
	CommandDAPLights();

	// PCT status lights
	if (PCTArmed)
	{
		// both SPD BK AUTO LTs on
		WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0020 );
		WriteCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF3_IOM10_CH0_DATA ) | 0x0020 );

		if (PCTActive)
		{
			// CDR Body Flap and spare DAP LTs on
			WriteCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF1_IOM10_CH0_DATA ) | 0x0010 );
			WriteCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA, ReadCOMPOOL_IS( SCP_FF2_IOM10_CH0_DATA ) | 0x0010 );
			// spare DAP done in CommandDAPLights()
		}
	}

	// in AUTO, INRTL or LVLH modes, start maneuver
	if(bFirstStep) {
		if(DAPControlMode == AUTO) {
			if(CurManeuver.IsValid) StartCurManeuver();
		}
		else if(DAPControlMode == INRTL) {
			StartManeuver(curM50Matrix, AttManeuver::MNVR);
		}
		else if(DAPControlMode == LVLH) {
			StartManeuver(GetCurrentLVLHAttMatrix(), AttManeuver::TRK);
		}
		bFirstStep = false;
	}

	// monitor future loaded maneuver
	if(FutManeuver.IsValid) {
		if(FutMnvrStartTime<=STS()->GetMET()) {
			CurManeuver = FutManeuver;
			if(DAPControlMode == AUTO) StartCurManeuver();
			FutManeuver.IsValid = false;
		}
	}

	// PCT
	if ((GetMajorMode() / 100) == 2)
	{
		if (PCTArmed)
		{
			if (PCTActive)
			{
				// active
				if (cdrspdbkthrot.Get() || pltspdbkthrot.Get())
				{
					DisarmPCT();
					StopPCT();
				}
				else
				{
					bool RHCdetent = pRHC_SOP->GetPitchDetent() &&
						pRHC_SOP->GetYawDetent() &&
						pRHC_SOP->GetRollDetent();

					bool THCdetent = (pTHC_SOP->GetXCommand() == 0) &&
						(pTHC_SOP->GetYCommand() == 0) &&
						(pTHC_SOP->GetZCommand() == 0);

					unsigned short FWD_DAP_FREE = ReadCOMPOOL_IS( SCP_FWD_RCS_OPTIONS_VERNIER );
					unsigned short AFT_DAP_FREE = ReadCOMPOOL_IS( SCP_AFT_RCS_OPTIONS_VERNIER );
					if (cdrbodyflap.Get() || sparepbi.Get() || (FWD_DAP_FREE == 1) || (AFT_DAP_FREE == 1) || !RHCdetent || !THCdetent) StopPCT();
				}
			}
			else
			{
				// armed
				if (cdrspdbkthrot.Get() || pltspdbkthrot.Get()) DisarmPCT();
				else if (cdrbodyflap.Get() || sparepbi.Get()) StartPCT();
			}
		}
		else
		{
			// disarmed
			if (cdrspdbkthrot.Get() || pltspdbkthrot.Get()) ArmPCT();
		}

		if (PCTActive == true) PCTControl( simt );
		else HandleTHCInput( simdt );
	}
	else HandleTHCInput(simdt);

	if(GetRHCRequiredRates()) {
		if(DAPControlMode == AUTO) {
			DAPControlMode = INRTL;
			StartManeuver(curM50Matrix, AttManeuver::MNVR);
		}
		else if(DAPControlMode == INRTL) {
			StartManeuver(curM50Matrix, AttManeuver::MNVR);
		}
		else if(DAPControlMode == LVLH) {
			StartManeuver(GetCurrentLVLHAttMatrix(), AttManeuver::TRK);
		}
		ATT_ERR = _V(0.0, 0.0, 0.0);
	}
	else if(DAPControlMode != FREE) { // if DAP is in FREE, we only care about RHC input; otherwise, we want to maintain target attitude
		MATRIX3 tgtM50Matrix;  // target M50 attitude for this timestep
		if(ActiveManeuver.Type == AttManeuver::TRK) { // get (instantaneous) target M50 attitude
			MATRIX3 curLVLHMatrix = GetCurrentLVLHRefMatrix();
			tgtM50Matrix = mul(curLVLHMatrix, ActiveManeuver.tgtMatrix);
			REQD_ATT = GetYZX_PYRAnglesFromMatrix(tgtM50Matrix)*DEG;
			// correct range
			if (REQD_ATT.x < 0.0) REQD_ATT.x += 360.0;
			if (REQD_ATT.y < 0.0) REQD_ATT.y += 360.0;
			if (REQD_ATT.z < 0.0) REQD_ATT.z += 360.0;

			if((STS()->GetMET()-lastUpdateTime) > 60.0) {
				UpdateNullRates();
				if(ManeuverStatus < MNVR_COMPLETE) mnvrCompletionMET = STS()->GetMET() + CalcManeuverCompletionTime(curM50Matrix, ActiveManeuver.tgtMatrix, curLVLHMatrix, length(degNullRates));
				lastUpdateTime = STS()->GetMET();
			}
			if(ManeuverStatus == MNVR_IN_PROGRESS) {
				// calculate M50 matrix corresponding to target attitude at end of maneuver
				double rotationAngle = RAD*length(degNullRates)*(mnvrCompletionMET-STS()->GetMET());
				MATRIX3 LVLHRotation;
				GetRotMatrixY(-rotationAngle, LVLHRotation);
				tgtM50Matrix = mul(mul(curLVLHMatrix, LVLHRotation), ActiveManeuver.tgtMatrix);
			}
		}
		else {
			tgtM50Matrix = ActiveManeuver.tgtMatrix;

			if (((STS()->GetMET()-lastUpdateTime) > 10.0) && (ManeuverStatus < MNVR_COMPLETE))
			{
				// recalculate time to reach target attitude
				VECTOR3 Axis;
				MATRIX3 AttError = GetRotationErrorMatrix(curM50Matrix, ActiveManeuver.tgtMatrix);
				double Angle = CalcEulerAngle(AttError, Axis);
				mnvrCompletionMET = STS()->GetMET() + (Angle*DEG)/degRotRate;
				lastUpdateTime = STS()->GetMET();
			}
		}

		attErrorMatrix = GetRotationErrorMatrix(curM50Matrix, tgtM50Matrix);
		ATT_ERR=GetYZX_PYRAnglesFromMatrix(attErrorMatrix)*DEG;
		if(ManeuverStatus == MNVR_COMPLETE) {
			CalcMultiAxisRates(degNullRates);
		}
		else if(ManeuverStatus == MNVR_IN_PROGRESS) {
			CalcEulerAxisRates();
			if(!RotatingAxis[PITCH] && !RotatingAxis[YAW] && !RotatingAxis[ROLL]) {
				ManeuverStatus=MNVR_COMPLETE; //now maintaining targ. attitude
			}
		}
		else { // MNVR_STARTING
			degReqdRates = _V(0.0, 0.0, 0.0);
		}
	}
	else { // FREE
		degReqdRates = degAngularVelocity;
	}
	if(ControlMode == RCS) SetRates(degReqdRates, simdt);
	else OMSTVC(ATT_ERR, simdt);

	lastStepdt = simdt;
}

bool OrbitDAP::OnMajorModeChange(unsigned int newMajorMode)
{
	if ((newMajorMode >= 104) && (newMajorMode <= 303))
	{
		return true;
	}
	return false;
}

bool OrbitDAP::ItemInput(int spec, int item, const char* Data, bool &IllegalEntry )
{
	if(spec==dps::MODE_UNDEFINED) {
		if(GetMajorMode()!=201) return false;

		if(item>=1 && item<=4) {
			int nNew = 0;
			if (GetIntegerUnsigned( Data, nNew ))
			{
				if((item==1 && nNew<365) || (item==2 && nNew<24) || (item>2 && nNew<60)) START_TIME[item-1]=nNew;
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==5 || item==6) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew<359.99)
				{
					if(item==5) MNVR_OPTION.data[ROLL]=dNew;
					else MNVR_OPTION.data[PITCH]=dNew;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==7) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if ((dNew<=90.0) || (dNew>=270.0 && dNew<359.99)) MNVR_OPTION.data[YAW]=dNew;
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==8) {
			int nNew;
			if (GetIntegerUnsigned( Data, nNew ))
			{
				/*if (nNew == 1)// Orbiting vehicle
				{
					TGT_ID = nNew;
					RA_DEC_flash = false;
					LAT_LON_ALT_flash = false;
				}
				else*/ if (nNew == 2)// Center of Earth
				{
					TGT_ID = nNew;
					RA_DEC_flash = false;
					LAT_LON_ALT_flash = false;
				}
				/*else if (nNew == 3)// Earth relative target
				{
					TGT_ID = nNew;
					RA_DEC_flash = false;
					LAT_LON_ALT_flash = true;
				}
				else if (nNew == 4)// Center of Sun
				{
					TGT_ID = nNew;
					RA_DEC_flash = false;
					LAT_LON_ALT_flash = false;
				}
				else if (nNew == 5)// Celestial target
				{
					TGT_ID = nNew;
					RA_DEC_flash = true;
					LAT_LON_ALT_flash = false;
				}
				else if ((nNew >= 11) && (nNew <= 60))// Navigation stars, OPS 2, 3, and 8
				{
					TGT_ID = nNew;
					RA_DEC_flash = false;
					LAT_LON_ALT_flash = false;
				}
				else if ((nNew >= 61) && (nNew <= 110))// Navigation stars, OPS 2 and 8
				{
					TGT_ID = nNew;
					RA_DEC_flash = false;
					LAT_LON_ALT_flash = false;
				}*/
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if (item == 9)
		{
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if ((dNew <= 359.999) && (TGT_ID == 5))
				{
					RA = dNew;
					RA_DEC_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if (item == 10)
		{
			double dNew;
			if (GetDoubleSigned( Data, dNew ))
			{
				if ((dNew >= -90.0) && (dNew <= 90.0) && (TGT_ID == 5))
				{
					DEC = dNew;
					RA_DEC_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if (item == 11)
		{
			double dNew;
			if (GetDoubleSigned( Data, dNew ))
			{
				if ((dNew >= -90.0) && (dNew <= 90.0) && (TGT_ID == 3))
				{
					LAT = dNew;
					LAT_LON_ALT_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if (item == 12)
		{
			double dNew;
			if (GetDoubleSigned( Data, dNew ))
			{
				if ((dNew >= -180.0) && (dNew <= 180.0) && (TGT_ID == 3))
				{
					LON = dNew;
					LAT_LON_ALT_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if (item == 13)
		{
			double dNew;
			if (GetDoubleSigned( Data, dNew ))
			{
				if ((dNew >= -3444.0) && (dNew <= 20000.0) && (TGT_ID == 3))
				{
					_ALT = dNew;
					LAT_LON_ALT_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==14) {
			int nNew;
			if (GetIntegerUnsigned( Data, nNew ))
			{
				if(nNew>=1 && nNew<=5)
				{
					BODY_VECT=nNew;
					P_Y_flash = false;
					if(BODY_VECT==1) {
						P=0.0;
						Y=0.0;
					}
					else if(BODY_VECT==2) {
						P=180.0;
						Y=0.0;
					}
					else if(BODY_VECT==3) {
						P=90.0;
						Y=0.0;
					}
					else if(BODY_VECT==4) {
						P=0.0;
						Y=280.57;
					}
					else P_Y_flash = true;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==15) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if ((dNew < 359.99) && (BODY_VECT == 5))
				{
					P=dNew;
					P_Y_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==16) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (((dNew <= 90.0) || ((dNew >= 270.0) && (dNew < 359.99))) && (BODY_VECT == 5))
				{
					Y=dNew;
					P_Y_flash = false;
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==17) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew<359.99) OM=dNew;
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==18) {
			if (strlen( Data ) == 0)
			{
				//VECTOR3 radTargetAtt = ConvertAnglesBetweenM50AndOrbiter(MNVR_OPTION*RAD, true);
				MATRIX3 tgtAtt = GetRotationMatrixYZX(_V(MNVR_OPTION.data[ROLL], MNVR_OPTION.data[PITCH], MNVR_OPTION.data[YAW])*RAD);
				double startTime = START_TIME[0]*86400.0+ START_TIME[1]*3600.0 + START_TIME[2]*60.0 + START_TIME[3];
				if(startTime <= STS()->GetMET()) {
					LoadCurINRTLManeuver(tgtAtt);
				}
				else {
					FutMnvrStartTime = startTime;
					LoadFutINRTLManeuver(tgtAtt);
				}

				RA_DEC_flash = false;
				LAT_LON_ALT_flash = false;
				P_Y_flash = false;
			}
			else IllegalEntry = true;
		}
		else if(item==19) {
			if (strlen( Data ) == 0)
			{
				if (TGT_ID == 2)
				{
					MATRIX3 tgtAtt = ConvertPYOMToLVLH(P*RAD, Y*RAD, OM*RAD);
					double startTime = START_TIME[0]*86400.0 + START_TIME[1]*3600.0 + START_TIME[2]*60.0 + START_TIME[3];
					if (startTime <= STS()->GetMET()) LoadCurLVLHManeuver(tgtAtt);
					else
					{
						FutMnvrStartTime = startTime;
						LoadFutLVLHManeuver(tgtAtt);
					}
				}
				else if (TGT_ID == 3)
				{
					// TODO LAT, LON, ALT
				}
				else if (TGT_ID == 5)
				{
					// TODO RA, DEC
				}

				RA_DEC_flash = false;
				LAT_LON_ALT_flash = false;
				P_Y_flash = false;
			}
			else IllegalEntry = true;
		}
		/*else if(item==20) {
			LoadRotationManeuver();
			RA_DEC_flash = false;
			LAT_LON_ALT_flash = false;
			P_Y_flash = false;
		}*/
		else if(item==21) {
			if (strlen( Data ) == 0)
			{
				CurManeuver.IsValid = false;
				FutManeuver.IsValid = false;
				RotatingAxis[YAW]=false;
				RotatingAxis[PITCH]=false;
				RotatingAxis[ROLL]=false;

				DAPControlMode=INRTL;
				//StartINRTLManeuver(radCurrentOrbiterAtt);
				StartManeuver(curM50Matrix, AttManeuver::MNVR);
			}
			else IllegalEntry = true;
		}
		else if (item == 23)
		{
			if (strlen( Data ) == 0) ERRTOT = true;// ERR TOT
			else IllegalEntry = true;
		}
		else if (item == 24)
		{
			if (strlen( Data ) == 0) ERRTOT = false;// ERR DAP
			else IllegalEntry = true;
		}
		return true;
	}
	else if(spec==20) {
		if(item==3 || item==4) {
			int num;
			if (GetIntegerUnsigned( Data, num ))
			{
				if (num <= 15)
				{
					// TODO use num
					editDAP=item-3;
					DAPConfiguration[2]=DAPConfiguration[editDAP];
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==5) {
			if (strlen( Data ) == 0)
			{
				if(editDAP != -1) DAPConfiguration[editDAP]=DAPConfiguration[2];
				editDAP=-1;
			}
			else IllegalEntry = true;
		}
		if(item==10 || item==30 || item==50) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.05 && dNew<=2.0) {
					DAPConfiguration[convert[item]].PRI_ROT_RATE=dNew;
					if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==11 || item==31 || item==51) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>0.10 && dNew<=40.0) {
					DAPConfiguration[convert[item]].PRI_ATT_DB=dNew;
					if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==12 || item==32 || item==52) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.10 && dNew<=5.0) {
					DAPConfiguration[convert[item]].PRI_RATE_DB=dNew;
					if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==13 || item==33 || item==53) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.04 && dNew<=1.0) {
					DAPConfiguration[convert[item]].PRI_ROT_PLS=dNew;
					if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==14 || item==34 || item==54) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew<=0.999) {
					DAPConfiguration[convert[item]].PRI_COMP=dNew;
					if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==15 || item==35 || item==55) {
			if (strlen( Data ) == 0)
			{
				if(DAPConfiguration[convert[item]].PRI_P_OPTION<2) {
					DAPConfiguration[convert[item]].PRI_P_OPTION++;
					if(DAPMode==PRI) {
						if(DAPConfiguration[DAPSelect].PRI_P_OPTION==1) {
							STS()->DisableThrusters(AftPitchThrusters, 4);
							UpdateDAPParameters();
						}
						else if(DAPConfiguration[DAPSelect].PRI_P_OPTION==2) {
							STS()->EnableThrusters(AftPitchThrusters, 4);
							STS()->DisableThrusters(NosePitchThrusters, 2);
							UpdateDAPParameters();
						}
					}
				}
				else {
					DAPConfiguration[convert[item]].PRI_P_OPTION=0;
					if(DAPConfiguration[DAPSelect].PRI_P_OPTION==0) {
						STS()->EnableThrusters(NosePitchThrusters, 2);
						UpdateDAPParameters();
					}
				}
			}
			else IllegalEntry = true;
		}
		else if(item==16 || item==36 || item==56) {
			if (strlen( Data ) == 0)
			{
				if(DAPConfiguration[convert[item]].PRI_Y_OPTION<2) {
					DAPConfiguration[convert[item]].PRI_Y_OPTION++;
					if(DAPMode==PRI) {
						if(DAPConfiguration[DAPSelect].PRI_Y_OPTION==1) {
							STS()->DisableThrusters(AftYawThrusters, 2);
							UpdateDAPParameters();
						}
						else if(DAPConfiguration[DAPSelect].PRI_Y_OPTION==2) {
							STS()->EnableThrusters(AftYawThrusters, 2);
							STS()->DisableThrusters(NoseYawThrusters, 2);
							UpdateDAPParameters();
						}
					}
				}
				else {
					DAPConfiguration[convert[item]].PRI_Y_OPTION=0;
					if(DAPConfiguration[DAPSelect].PRI_Y_OPTION==0) {
						STS()->EnableThrusters(NoseYawThrusters, 2);
						UpdateDAPParameters();
					}
				}
			}
			else IllegalEntry = true;
		}
		else if(item==17 || item==37 || item==57) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.01 && dNew<=5.0) {
					DAPConfiguration[convert[item]].PRI_TRAN_PLS=dNew;
					if(convert[item]== DAPSelect && DAPMode==PRI) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==18 || item==38 || item==58) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.05 && dNew<=5.0) {
					DAPConfiguration[convert[item]].ALT_RATE_DB=dNew;
					if(convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==19 || item==39 || item==59) {
			if (strlen( Data ) == 0)
			{
				if(DAPConfiguration[convert[item]].ALT_JET_OPT==0) {
					DAPConfiguration[convert[item]].ALT_JET_OPT=2;
					if(DAPMode==ALT) {
						if(DAPConfiguration[DAPSelect].ALT_JET_OPT==2) {
							STS()->DisableThrusters(NoseRotThrusters, 6);
							STS()->EnableThrusters(AftRotThrusters, 10);
							UpdateDAPParameters();
						}
					}
				}
				else {
					DAPConfiguration[convert[item]].ALT_JET_OPT=0;
					if(DAPMode==ALT) {
						if(DAPConfiguration[DAPSelect].ALT_JET_OPT==0) {
							STS()->EnableThrusters(NoseRotThrusters, 6);
							UpdateDAPParameters();
						}
					}
				}
			}
			else IllegalEntry = true;
		}
		else if(item==20 || item==40 || item==60) {
			int nNew;
			if (GetIntegerUnsigned( Data, nNew ))
			{
				if(nNew>=1 && nNew<=3) {
					DAPConfiguration[convert[item]].ALT_JETS=nNew;
					if(convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==21 || item==41 || item==61) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.08 && dNew<=9.99) {
					DAPConfiguration[convert[item]].ALT_ON_TIME=dNew;
					if(convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==22 || item==42 || item==62) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew<=99.99) {
					DAPConfiguration[convert[item]].ALT_DELAY=dNew;
					if(convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==23 || item==43 || item==63) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.002 && dNew<=1.0) {
					DAPConfiguration[convert[item]].VERN_ROT_RATE=dNew;
					if(convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==24 || item==44 || item==64) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.01 && dNew<=40.0) {
					DAPConfiguration[convert[item]].VERN_ATT_DB=dNew;
					if(convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==25 || item==45 || item==65) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.01 && dNew<=0.5) {
					DAPConfiguration[convert[item]].VERN_RATE_DB=dNew;
					if(convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==26 || item==46 || item==66) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if(dNew>=0.001 && dNew<=0.5) {
					DAPConfiguration[convert[item]].VERN_ROT_PLS=dNew;
					if(convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==27 || item==47 || item==67) {
			double dNew;
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew<=0.999) {
					DAPConfiguration[convert[item]].VERN_COMP=dNew;
					if(convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		else if(item==28 || item==48 || item==68) {
			int nNew;
			if (GetIntegerUnsigned( Data, nNew ))
			{
				if (nNew<=9) {
					DAPConfiguration[convert[item]].VERN_CNTL_ACC=nNew;
					if(convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
				}
				else IllegalEntry = true;
			}
			else IllegalEntry = true;
		}
		return true;
	}
	return false;
}

bool OrbitDAP::OnPaint(int spec, vc::MDU* pMDU) const
{
	if(spec==dps::MODE_UNDEFINED && GetMajorMode()==201) {
		PaintUNIVPTGDisplay(pMDU);
		return true;
	}
	else if(spec==20) {
		PaintDAPCONFIGDisplay(pMDU);
		return true;
	}
	return false;
}

void OrbitDAP::PaintUNIVPTGDisplay(vc::MDU* pMDU) const
{
	char cbuf[255];
	PrintCommonHeader("    UNIV PTG", pMDU);

	double CUR_MNVR_COMPL[4];
	if(DAPControlMode == INRTL || DAPControlMode == FREE) ConvertSecondsToDDHHMMSS(STS()->GetMET(), CUR_MNVR_COMPL);
	else ConvertSecondsToDDHHMMSS(mnvrCompletionMET, CUR_MNVR_COMPL);
	pMDU->mvprint(3, 1, "CUR MNVR COMPL");
	sprintf_s(cbuf, 255, "%.2d:%.2d:%.2d", static_cast<int>(CUR_MNVR_COMPL[1]), static_cast<int>(CUR_MNVR_COMPL[2]), static_cast<int>(CUR_MNVR_COMPL[3]));
	pMDU->mvprint(18, 1, cbuf);
	sprintf_s(cbuf, 255, "1 START TIME %.3d/%.2d:%.2d:%.2d",
		START_TIME[0], START_TIME[1], START_TIME[2], START_TIME[3]);
	pMDU->mvprint(1, 2, cbuf);
	pMDU->Underline( 14, 2 );
	pMDU->Underline( 15, 2 );
	pMDU->Underline( 16, 2 );
	pMDU->Underline( 18, 2 );
	pMDU->Underline( 19, 2 );
	pMDU->Underline( 21, 2 );
	pMDU->Underline( 22, 2 );
	pMDU->Underline( 24, 2 );
	pMDU->Underline( 25, 2 );

	pMDU->mvprint(0, 4, "MNVR OPTION");
	sprintf_s(cbuf, 255, "5 R %6.2f", MNVR_OPTION.data[ROLL]);
	pMDU->mvprint(1, 5, cbuf);
	pMDU->Underline( 5, 5 );
	pMDU->Underline( 6, 5 );
	pMDU->Underline( 7, 5 );
	pMDU->Underline( 8, 5 );
	pMDU->Underline( 9, 5 );
	pMDU->Underline( 10, 5 );
	sprintf_s(cbuf, 255, "6 P %6.2f", MNVR_OPTION.data[PITCH]);
	pMDU->mvprint(1, 6, cbuf);
	sprintf_s(cbuf, 255, "7 Y %6.2f", MNVR_OPTION.data[YAW]);
	pMDU->mvprint(1, 7, cbuf);

	pMDU->mvprint(0, 9, "TRK/ROT OPTIONS");
	sprintf_s(cbuf, 255, "8 TGT ID %3d", TGT_ID);
	pMDU->mvprint(1, 10, cbuf);
	pMDU->Underline( 10, 10 );
	pMDU->Underline( 11, 10 );
	pMDU->Underline( 12, 10 );

	pMDU->mvprint(1, 12, "9  RA");
	sprintf_s( cbuf, 255, "%7.3f", RA );
	pMDU->mvprint( 9, 12, cbuf, RA_DEC_flash ? DEUATT_FLASHING : 0 );
	pMDU->Underline( 9, 12 );
	pMDU->Underline( 10, 12 );
	pMDU->Underline( 11, 12 );
	pMDU->Underline( 12, 12 );
	pMDU->Underline( 13, 12 );
	pMDU->Underline( 14, 12 );
	pMDU->Underline( 15, 12 );
	pMDU->mvprint(1, 13, "10 DEC");
	pMDU->NumberSignBracket( 9, 13, DEC );// TODO should brackets flash with sign?
	sprintf_s( cbuf, 255, "%6.3f", fabs( DEC ) );
	pMDU->mvprint( 10, 13, cbuf, RA_DEC_flash ? DEUATT_FLASHING : 0 );
	pMDU->Underline( 10, 13 );
	pMDU->Underline( 11, 13 );
	pMDU->Underline( 12, 13 );
	pMDU->Underline( 13, 13 );
	pMDU->Underline( 14, 13 );
	pMDU->Underline( 15, 13 );
	pMDU->mvprint(1, 14, "11 LAT");
	pMDU->NumberSignBracket( 9, 14, LAT );// TODO should brackets flash with sign?
	sprintf_s( cbuf, 255, "%6.3f", fabs( LAT ) );
	pMDU->mvprint( 10, 14, cbuf, LAT_LON_ALT_flash ? DEUATT_FLASHING : 0 );
	pMDU->Underline( 10, 14 );
	pMDU->Underline( 11, 14 );
	pMDU->Underline( 12, 14 );
	pMDU->Underline( 13, 14 );
	pMDU->Underline( 14, 14 );
	pMDU->Underline( 15, 14 );
	pMDU->mvprint(1, 15, "12 LON");
	pMDU->NumberSignBracket( 8, 15, LON );// TODO should brackets flash with sign?
	sprintf_s( cbuf, 255, "%7.3f", fabs( LON ) );
	pMDU->mvprint( 9, 15, cbuf, LAT_LON_ALT_flash ? DEUATT_FLASHING : 0 );
	pMDU->Underline( 9, 15 );
	pMDU->Underline( 10, 15 );
	pMDU->Underline( 11, 15 );
	pMDU->Underline( 12, 15 );
	pMDU->Underline( 13, 15 );
	pMDU->Underline( 14, 15 );
	pMDU->Underline( 15, 15 );
	pMDU->mvprint(1, 16, "13 ALT");
	pMDU->NumberSignBracket( 8, 16, _ALT );// TODO should brackets flash with sign?
	sprintf_s( cbuf, 255, "%7.1f", fabs( _ALT ) );
	pMDU->mvprint( 9, 16, cbuf, LAT_LON_ALT_flash ? DEUATT_FLASHING : 0 );
	pMDU->Underline( 9, 16 );
	pMDU->Underline( 10, 16 );
	pMDU->Underline( 11, 16 );
	pMDU->Underline( 12, 16 );
	pMDU->Underline( 13, 16 );
	pMDU->Underline( 14, 16 );
	pMDU->Underline( 15, 16 );

	sprintf_s(cbuf, 255, "14 BODY VECT %d", BODY_VECT);
	pMDU->mvprint(1, 18, cbuf);
	pMDU->mvprint( 1, 20, "15 P" );
	sprintf_s( cbuf, 255, "%6.2f", P );
	pMDU->mvprint( 7, 20, cbuf, P_Y_flash ? DEUATT_FLASHING : 0 );
	pMDU->Underline( 7, 20 );
	pMDU->Underline( 8, 20 );
	pMDU->Underline( 9, 20 );
	pMDU->Underline( 10, 20 );
	pMDU->Underline( 11, 20 );
	pMDU->Underline( 12, 20 );
	pMDU->mvprint( 1, 21, "16 Y" );
	sprintf_s( cbuf, 255, "%6.2f", Y );
	pMDU->mvprint( 7, 21, cbuf, P_Y_flash ? DEUATT_FLASHING : 0 );
	if(OM>=0.0) {
		sprintf_s(cbuf, 255, "17 OM %6.2f", OM);
		pMDU->mvprint(1, 22, cbuf);
	}
	else pMDU->mvprint(1, 22, "17 OM");

	pMDU->mvprint(15, 4, "START MNVR 18");
	pMDU->mvprint(21, 5, "TRK  19");
	pMDU->mvprint(21, 6, "ROT  20");
	pMDU->mvprint(20, 7, "CNCL  21");
	pMDU->mvprint(28, 3, "CUR");
	pMDU->mvprint(32, 3, "FUT");
	if(CurManeuver.IsValid) {
		if(CurManeuver.Type == AttManeuver::MNVR) {
			pMDU->mvprint(29, 4, "*");
		}
		else if(CurManeuver.Type == AttManeuver::TRK) {
			pMDU->mvprint(29, 5, "*");
		}
		else {
			pMDU->mvprint(29, 6, "*");
		}
	}
	if(FutManeuver.IsValid) {
		if(FutManeuver.Type == AttManeuver::MNVR) {
			pMDU->mvprint(33, 4, "*");
		}
		else if(FutManeuver.Type == AttManeuver::TRK) {
			pMDU->mvprint(33, 5, "*");
		}
		else {
			pMDU->mvprint(33, 6, "*");
		}
	}

	pMDU->mvprint(20, 9, "ATT MON");
	pMDU->mvprint(21, 10, "22 MON AXIS");
	pMDU->mvprint(21, 11, "ERR TOT 23");
	pMDU->mvprint(21, 12, "ERR DAP 24");
	if (ERRTOT == true) pMDU->mvprint( 31, 11, "*" );// ERR TOT
	else pMDU->mvprint( 31, 12, "*" );// ERR DAP

	pMDU->mvprint(27, 14, "ROLL   PITCH    YAW");
	sprintf_s(cbuf, 255, "CUR   %6.2f  %6.2f  %6.2f", CUR_ATT.data[ROLL], CUR_ATT.data[PITCH], CUR_ATT.data[YAW]);
	pMDU->mvprint(20, 15, cbuf);
	sprintf_s(cbuf, 255, "REQD  %6.2f  %6.2f  %6.2f", REQD_ATT.data[ROLL], REQD_ATT.data[PITCH], REQD_ATT.data[YAW]);
	pMDU->mvprint(20, 16, cbuf);
	sprintf_s(cbuf, 255, "ERR   %6.2f  %6.2f  %6.2f", fabs( ATT_ERR.data[ROLL] ), fabs( ATT_ERR.data[PITCH] ), fabs( ATT_ERR.data[YAW] ));
	pMDU->mvprint(20, 17, cbuf);
	pMDU->NumberSign( 25, 17, ATT_ERR.data[ROLL] );
	pMDU->NumberSign( 33, 17, ATT_ERR.data[PITCH] );
	pMDU->NumberSign( 41, 17, ATT_ERR.data[YAW] );
	sprintf_s(cbuf, 255, "RATE  %6.3f  %6.3f  %6.3f", fabs( degAngularVelocity.data[ROLL] ), fabs( degAngularVelocity.data[PITCH] ), fabs( degAngularVelocity.data[YAW] ));
	pMDU->mvprint(20, 18, cbuf);
	pMDU->NumberSign( 25, 18, degAngularVelocity.data[ROLL] );
	pMDU->NumberSign( 33, 18, degAngularVelocity.data[PITCH] );
	pMDU->NumberSign( 41, 18, degAngularVelocity.data[YAW] );
}

void OrbitDAP::PaintDAPCONFIGDisplay(vc::MDU* pMDU) const
{
	char *strings[3]={" ALL", "NOSE", "TAIL"};
	char cbuf[255];
	int lim[3]={3, 5, 5};
	int i, n;

	PrintCommonHeader("   DAP CONFIG", pMDU);

	pMDU->mvprint(4, 2, "PRI");
	pMDU->mvprint(9, 2, "1 DAP A");
	pMDU->mvprint(20, 2, "2 DAP B");
	pMDU->mvprint(33, 2, "PRI");
	pMDU->mvprint(0, 3, "ROT RATE");
	pMDU->mvprint(0, 4, "ATT DB");
	pMDU->mvprint(0, 5, "RATE DB");
	pMDU->mvprint(0, 6, "ROT PLS");
	pMDU->mvprint(0, 7, "COMP");
	pMDU->mvprint(0, 8, "P OPTION");
	pMDU->mvprint(0, 9, "Y OPTION");
	pMDU->mvprint(0, 10, "TRAN PLS");

	pMDU->mvprint(4, 11, "ALT");
	pMDU->mvprint(33, 11, "ALT");
	pMDU->mvprint(0, 12, "RATE DB");
	pMDU->mvprint(0, 13, "JET OPT");
	pMDU->mvprint(0, 14, "# JETS");
	pMDU->mvprint(0, 15, "ON TIME");
	pMDU->mvprint(0, 16, "DELAY");

	pMDU->mvprint(4, 17, "VERN");
	pMDU->mvprint(33, 17, "VERN");
	pMDU->mvprint(0, 18, "ROT RATE");
	pMDU->mvprint(0, 19, "ATT DB");
	pMDU->mvprint(0, 20, "RATE DB");
	pMDU->mvprint(0, 21, "ROT PLS");
	pMDU->mvprint(0, 22, "COMP");
	pMDU->mvprint(0, 23, "CNTL ACC");

	pMDU->mvprint( 16, 2, "01" );
	pMDU->Underline( 16, 2 );
	pMDU->Underline( 17, 2 );
	pMDU->mvprint( 27, 2, "02" );
	pMDU->Underline( 27, 2 );
	pMDU->Underline( 28, 2 );

	int edit=2; //temporary
	for(n=1, i=0;n<=lim[edit];n+=2, i++) {
		sprintf_s(cbuf, 255, "%d %.4f", 10*n, DAPConfiguration[i].PRI_ROT_RATE);
		pMDU->mvprint(9+11*i, 3, cbuf);
		pMDU->Underline( 12 + 11 * i, 3 );
		pMDU->Underline( 13 + 11 * i, 3 );
		pMDU->Underline( 14 + 11 * i, 3 );
		pMDU->Underline( 15 + 11 * i, 3 );
		pMDU->Underline( 16 + 11 * i, 3 );
		pMDU->Underline( 17 + 11 * i, 3 );
		sprintf_s(cbuf, 255, "%d  %05.2f", 10*n+1, DAPConfiguration[i].PRI_ATT_DB);
		pMDU->mvprint(9+11*i, 4, cbuf);
		pMDU->Underline( 13 + 11 * i, 4 );
		pMDU->Underline( 14 + 11 * i, 4 );
		pMDU->Underline( 15 + 11 * i, 4 );
		pMDU->Underline( 16 + 11 * i, 4 );
		pMDU->Underline( 17 + 11 * i, 4 );
		sprintf_s(cbuf, 255, "%d   %.2f", 10*n+2, DAPConfiguration[i].PRI_RATE_DB);
		pMDU->mvprint(9+11*i, 5, cbuf);
		pMDU->Underline( 14 + 11 * i, 5 );
		pMDU->Underline( 15 + 11 * i, 5 );
		pMDU->Underline( 16 + 11 * i, 5 );
		pMDU->Underline( 17 + 11 * i, 5 );
		sprintf_s(cbuf, 255, "%d  %.3f", 10*n+3, DAPConfiguration[i].PRI_ROT_PLS);
		pMDU->mvprint(9+11*i, 6, cbuf);
		pMDU->Underline( 13 + 11 * i, 6 );
		pMDU->Underline( 14 + 11 * i, 6 );
		pMDU->Underline( 15 + 11 * i, 6 );
		pMDU->Underline( 16 + 11 * i, 6 );
		pMDU->Underline( 17 + 11 * i, 6 );
		sprintf_s(cbuf, 255, "%d  %.3f", 10*n+4, DAPConfiguration[i].PRI_COMP);
		pMDU->mvprint(9+11*i, 7, cbuf);
		pMDU->mvprint( 13 + 11 * i, 7, " " );
		pMDU->Underline( 14 + 11 * i, 7 );
		pMDU->Underline( 15 + 11 * i, 7 );
		pMDU->Underline( 16 + 11 * i, 7 );
		pMDU->Underline( 17 + 11 * i, 7 );
		sprintf_s(cbuf, 255, "%d   %s", 10*n+5, strings[DAPConfiguration[i].PRI_P_OPTION]);
		pMDU->mvprint(9+11*i, 8, cbuf);
		sprintf_s(cbuf, 255, "%d   %s", 10*n+6, strings[DAPConfiguration[i].PRI_Y_OPTION]);
		pMDU->mvprint(9+11*i, 9, cbuf);
		sprintf_s(cbuf, 255, "%d  %.3f", 10*n+7, DAPConfiguration[i].PRI_TRAN_PLS);
		pMDU->mvprint(9+11*i, 10, cbuf);
		pMDU->Underline( 13 + 11 * i, 10 );
		pMDU->Underline( 14 + 11 * i, 10 );
		pMDU->Underline( 15 + 11 * i, 10 );
		pMDU->Underline( 16 + 11 * i, 10 );
		pMDU->Underline( 17 + 11 * i, 10 );

		sprintf_s(cbuf, 255, "%d  %.3f", 10*n+8, DAPConfiguration[i].ALT_RATE_DB);
		pMDU->mvprint(9+11*i, 12, cbuf);
		pMDU->Underline( 13 + 11 * i, 12 );
		pMDU->Underline( 14 + 11 * i, 12 );
		pMDU->Underline( 15 + 11 * i, 12 );
		pMDU->Underline( 16 + 11 * i, 12 );
		pMDU->Underline( 17 + 11 * i, 12 );
		sprintf_s(cbuf, 255, "%d   %s", 10*n+9, strings[DAPConfiguration[i].ALT_JET_OPT]);
		pMDU->mvprint(9+11*i, 13, cbuf);
		sprintf_s(cbuf, 255, "%d      %d", 10*n+10, DAPConfiguration[i].ALT_JETS);
		pMDU->mvprint(9+11*i, 14, cbuf);
		pMDU->Underline( 17 + 11 * i, 14 );
		sprintf_s(cbuf, 255, "%d   %.2f", 10*n+11, DAPConfiguration[i].ALT_ON_TIME);
		pMDU->mvprint(9+11*i, 15, cbuf);
		pMDU->Underline( 14 + 11 * i, 15 );
		pMDU->Underline( 15 + 11 * i, 15 );
		pMDU->Underline( 16 + 11 * i, 15 );
		pMDU->Underline( 17 + 11 * i, 15 );
		sprintf_s(cbuf, 255, "%d  %05.2f", 10*n+12, DAPConfiguration[i].ALT_DELAY);
		pMDU->mvprint(9+11*i, 16, cbuf);
		pMDU->Underline( 13 + 11 * i, 16 );
		pMDU->Underline( 14 + 11 * i, 16 );
		pMDU->Underline( 15 + 11 * i, 16 );
		pMDU->Underline( 16 + 11 * i, 16 );
		pMDU->Underline( 17 + 11 * i, 16 );

		sprintf_s(cbuf, 255, "%d %.4f", 10*n+13, DAPConfiguration[i].VERN_ROT_RATE);
		pMDU->mvprint(9+11*i, 18, cbuf);
		pMDU->Underline( 12 + 11 * i, 18 );
		pMDU->Underline( 13 + 11 * i, 18 );
		pMDU->Underline( 14 + 11 * i, 18 );
		pMDU->Underline( 15 + 11 * i, 18 );
		pMDU->Underline( 16 + 11 * i, 18 );
		pMDU->Underline( 17 + 11 * i, 18 );
		sprintf_s(cbuf, 255, "%d %06.3f", 10*n+14, DAPConfiguration[i].VERN_ATT_DB);
		pMDU->mvprint(9+11*i, 19, cbuf);
		pMDU->Underline( 12 + 11 * i, 19 );
		pMDU->Underline( 13 + 11 * i, 19 );
		pMDU->Underline( 14 + 11 * i, 19 );
		pMDU->Underline( 15 + 11 * i, 19 );
		pMDU->Underline( 16 + 11 * i, 19 );
		pMDU->Underline( 17 + 11 * i, 19 );
		sprintf_s(cbuf, 255, "%d  %.3f", 10*n+15, DAPConfiguration[i].VERN_RATE_DB);
		pMDU->mvprint(9+11*i, 20, cbuf);
		pMDU->mvprint( 13 + 11 * i, 20, " " );
		pMDU->Underline( 14 + 11 * i, 20 );
		pMDU->Underline( 15 + 11 * i, 20 );
		pMDU->Underline( 16 + 11 * i, 20 );
		pMDU->Underline( 17 + 11 * i, 20 );
		sprintf_s(cbuf, 255, "%d  %05.3f", 10*n+16, DAPConfiguration[i].VERN_ROT_PLS);
		pMDU->mvprint(9+11*i, 21, cbuf);
		pMDU->Underline( 13 + 11 * i, 21 );
		pMDU->Underline( 14 + 11 * i, 21 );
		pMDU->Underline( 15 + 11 * i, 21 );
		pMDU->Underline( 16 + 11 * i, 21 );
		pMDU->Underline( 17 + 11 * i, 21 );
		sprintf_s(cbuf, 255, "%d  %.3f", 10*n+17, DAPConfiguration[i].VERN_COMP);
		pMDU->mvprint(9+11*i, 22, cbuf);
		pMDU->mvprint( 13 + 11 * i, 22, " " );
		pMDU->Underline( 14 + 11 * i, 22 );
		pMDU->Underline( 15 + 11 * i, 22 );
		pMDU->Underline( 16 + 11 * i, 22 );
		pMDU->Underline( 17 + 11 * i, 22 );
		sprintf_s(cbuf, 255, "%d      %d", 10*n+18, DAPConfiguration[i].VERN_CNTL_ACC);
		pMDU->mvprint(9+11*i, 23, cbuf);
		pMDU->Underline( 17 + 11 * i, 23 );
	}

	pMDU->mvprint( 41, 2, "DAP EDIT" );
	pMDU->mvprint( 41, 3, "3 DAP A" );
	pMDU->mvprint( 41, 4, "4 DAP B" );
	pMDU->mvprint( 41, 5, "5" );

	pMDU->Line( 190, 28, 190, 336 );
	pMDU->Line( 300, 28, 300, 336 );
	pMDU->Line( 410, 112, 410, 336 );
	pMDU->Line( 410, 112, 510, 112 );

	pMDU->mvprint( 41, 9, "NOTCH FLTR" );
	pMDU->mvprint( 43, 10, "ENA  6" );

	pMDU->mvprint( 42, 12, "XJETS ROT" );
	pMDU->mvprint( 44, 13, "ENA  7" );

	pMDU->mvprint( 42, 15, "REBOOST" );
	pMDU->mvprint( 43, 16, "8 CFG" );
	pMDU->mvprint( 43, 17, "9 INTVL" );
}

bool OrbitDAP::OnParseLine(const char* keyword, const char* value)
{
	if(!_strnicmp(keyword, "TGT_ID", 6)) {
		sscanf_s(value, "%d", &TGT_ID);
		return true;
	}
	/*else if (!_strnicmp( keyword, "RA_ANGLE", 8 ))
	{
		sscanf_s( value, "%lf", &RA );
		return true;
	}
	else if (!_strnicmp( keyword, "DEC_ANGLE", 9 ))
	{
		sscanf_s( value, "%lf", &DEC );
		return true;
	}
	else if (!_strnicmp( keyword, "LAT_ANGLE", 9 ))
	{
		sscanf_s( value, "%lf", &LAT );
		return true;
	}
	else if (!_strnicmp( keyword, "LON_ANGLE", 9 ))
	{
		sscanf_s( value, "%lf", &LON );
		return true;
	}
	else if (!_strnicmp( keyword, "ALT_ANGLE", 9 ))
	{
		sscanf_s( value, "%lf", &_ALT );
		return true;
	}*/
	else if(!_strnicmp(keyword, "BODY_VECT", 9)) {
		sscanf_s(value, "%d", &BODY_VECT);
		return true;
	}
	else if(!_strnicmp(keyword, "P_ANGLE", 7)) {
		sscanf_s(value, "%lf", &P);
		return true;
	}
	else if(!_strnicmp(keyword, "Y_ANGLE", 7)) {
		sscanf_s(value, "%lf", &Y);
		return true;
	}
	else if(!_strnicmp(keyword, "OM_ANGLE", 8)) {
		sscanf_s(value, "%lf", &OM);
		return true;
	}
	else if(!_strnicmp(keyword, "ROLL", 4)) {
		sscanf_s(value, "%lf", &MNVR_OPTION.data[ROLL]);
		return true;
	}
	else if(!_strnicmp(keyword, "PITCH", 5)) {
		sscanf_s(value, "%lf", &MNVR_OPTION.data[PITCH]);
		return true;
	}
	else if(!_strnicmp(keyword, "YAW", 3)) {
		sscanf_s(value, "%lf", &MNVR_OPTION.data[YAW]);
		return true;
	}
	else if(!_strnicmp(keyword, "DAP_MODE", 8)) {
		int nTemp1, nTemp2;
		sscanf_s(value, "%d %d", &nTemp1, &nTemp2);
		DAPSelect = static_cast<DAP_SELECT>(nTemp1);
		DAPMode = static_cast<DAP_MODE>(nTemp2);
		return true;
	}
	else if(!_strnicmp(keyword, "ROT_MODE", 8)) {
		int nTemp[3];
		sscanf_s(value, "%d %d %d", &nTemp[0], &nTemp[1], &nTemp[2]);
		for(int i=0;i<3;i++) RotMode[i] = static_cast<ROT_MODE>(nTemp[i]);
		return true;
	}
	else if(!_strnicmp(keyword, "TRANS_MODE", 10)) {
		int nTemp[3];
		sscanf_s(value, "%d %d %d", &nTemp[0], &nTemp[1], &nTemp[2]);
		for(int i=0;i<3;i++) TransMode[i] = static_cast<TRANS_MODE>(nTemp[i]);
		return true;
	}
	else if(!_strnicmp(keyword, "CONTROL_MODE", 12)) {
		//sscanf(value, "%d", &ControlMode);
		int nTemp;
		sscanf_s(value, "%d", &nTemp);
		if(nTemp==0) DAPControlMode=AUTO;
		else if(nTemp==1) DAPControlMode=INRTL;
		else if(nTemp==2) DAPControlMode=LVLH;
		else if(nTemp==3) {
			DAPControlMode=FREE;
			for(unsigned int i=0;i<3;i++) {
				RotMode[i]=ROT_PULSE;
				RotPulseInProg[i]=false;
			}
		}
		return true;
	}
	else if(!_strnicmp (keyword, "CUR_MNVR", 8)) {
		LoadAttManeuver(value, CurManeuver);
		return true;
	}
	else if(!_strnicmp (keyword, "FUT_MNVR", 8)) {
		LoadAttManeuver(value, FutManeuver);
		return true;
	}
	else if(!_strnicmp (keyword, "FUT_START_TIME", 14)) {
		sscanf_s(value, "%lf", &FutMnvrStartTime);
		return true;
	}

	return false;
}

void OrbitDAP::OnSaveState(FILEHANDLE scn) const
{
	char cbuf[256];
	oapiWriteScenario_int (scn, "TGT_ID", TGT_ID);
	oapiWriteScenario_int (scn, "BODY_VECT", BODY_VECT);
	oapiWriteScenario_float (scn, "ROLL", MNVR_OPTION.data[ROLL]);
	oapiWriteScenario_float (scn, "PITCH", MNVR_OPTION.data[PITCH]);
	oapiWriteScenario_float (scn, "YAW", MNVR_OPTION.data[YAW]);
	/*oapiWriteScenario_float( scn, "RA_ANGLE", RA );
	oapiWriteScenario_float( scn, "DEC_ANGLE", DEC );
	oapiWriteScenario_float( scn, "LAT_ANGLE", LAT );
	oapiWriteScenario_float( scn, "LON_ANGLE", LON );
	oapiWriteScenario_float( scn, "ALT_ANGLE", _ALT );*/
	oapiWriteScenario_float (scn, "P_ANGLE", P);
	oapiWriteScenario_float (scn, "Y_ANGLE", Y);
	oapiWriteScenario_float (scn, "OM_ANGLE", OM);
	sprintf_s(cbuf, 256, "%d %d", DAPSelect, DAPMode);
	oapiWriteScenario_string (scn, "DAP_MODE", cbuf);
	sprintf_s(cbuf, 256, "%d %d %d", RotMode[0], RotMode[1], RotMode[2]);
	oapiWriteScenario_string (scn, "ROT_MODE", cbuf);
	sprintf_s(cbuf, 256, "%d %d %d", TransMode[0], TransMode[1], TransMode[2]);
	oapiWriteScenario_string (scn, "TRANS_MODE", cbuf);
	sprintf_s(cbuf, 256, "%d", DAPControlMode);
	oapiWriteScenario_string (scn, "CONTROL_MODE", cbuf);
	if(CurManeuver.IsValid) SaveAttManeuver(scn, "CUR_MNVR", CurManeuver);
	if(FutManeuver.IsValid) {
		SaveAttManeuver(scn, "FUT_MNVR", FutManeuver);
		oapiWriteScenario_float(scn, "FUT_START_TIME", FutMnvrStartTime);
	}
}

void OrbitDAP::CommandDAPLights( void )
{
	if (DAPSelect == A)
	{
		WriteCOMPOOL_IS( SCP_FWD_DAP_SELECT_A_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_SELECT_A_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_SELECT_B_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_SELECT_B_LT, 0 );
	}
	else// if (DAPSelect == B)
	{
		WriteCOMPOOL_IS( SCP_FWD_DAP_SELECT_A_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_SELECT_A_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_SELECT_B_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_SELECT_B_LT, 1 );
	}

	if (DAPControlMode == AUTO)
	{
		WriteCOMPOOL_IS( SCP_FWD_DAP_AUTO_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_AUTO_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_INRTL_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_INRTL_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_LVLH_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_LVLH_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_FREE_DFT_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_FREE_DFT_LT, 0 );
	}
	else if (DAPControlMode == INRTL)
	{
		WriteCOMPOOL_IS( SCP_FWD_DAP_AUTO_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_AUTO_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_INRTL_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_INRTL_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_LVLH_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_LVLH_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_FREE_DFT_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_FREE_DFT_LT, 0 );
	}
	else if (DAPControlMode == LVLH)
	{
		WriteCOMPOOL_IS( SCP_FWD_DAP_AUTO_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_AUTO_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_INRTL_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_INRTL_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_LVLH_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_LVLH_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_FREE_DFT_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_FREE_DFT_LT, 0 );
	}
	else// if (DAPControlMode == FREE)
	{
		WriteCOMPOOL_IS( SCP_FWD_DAP_AUTO_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_AUTO_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_INRTL_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_INRTL_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_LVLH_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_LVLH_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_DAP_MAN_FREE_DFT_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_DAP_MAN_FREE_DFT_LT, 1 );
	}

	if (PCTActive)
	{
		WriteCOMPOOL_IS( SCP_FWD_BLANK_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_BLANK_LT, 1 );
	}
	else
	{
		WriteCOMPOOL_IS( SCP_FWD_BLANK_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_BLANK_LT, 0 );
	}

	// TODO LOW Z
	WriteCOMPOOL_IS( SCP_FWD_TRANSL_LOW_Z_LT, 0 );
	WriteCOMPOOL_IS( SCP_AFT_TRANSL_LOW_Z_LT, 0 );

	// TODO HIGH Z
	WriteCOMPOOL_IS( SCP_FWD_TRANSL_Z_HIGH_LT, 0 );
	WriteCOMPOOL_IS( SCP_AFT_TRANSL_Z_HIGH_LT, 0 );

	if (DAPMode == PRI)
	{
		WriteCOMPOOL_IS( SCP_FWD_RCS_JETS_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_RCS_JETS_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_ALT_PRCS_MODE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ALT_PRCS_MODE_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_RCS_JETS_VERN_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_RCS_JETS_VERN_LT, 0 );
	}
	else if (DAPMode == ALT)
	{
		WriteCOMPOOL_IS( SCP_FWD_RCS_JETS_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_RCS_JETS_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_ALT_PRCS_MODE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ALT_PRCS_MODE_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_RCS_JETS_VERN_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_RCS_JETS_VERN_LT, 0 );
	}
	else// if (DAPMode == VERN)
	{
		WriteCOMPOOL_IS( SCP_FWD_RCS_JETS_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_RCS_JETS_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_ALT_PRCS_MODE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ALT_PRCS_MODE_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_RCS_JETS_VERN_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_RCS_JETS_VERN_LT, 1 );
	}

	if (TransMode[0] == NORM)
	{
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_X_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_X_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_X_PULSE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_X_PULSE_LT, 0 );
	}
	else// if (TransMode[0] == TRANS_PULSE)
	{
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_X_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_X_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_X_PULSE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_X_PULSE_LT, 1 );
	}

	if (TransMode[1] == NORM)
	{
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Y_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Y_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Y_PULSE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Y_PULSE_LT, 0 );
	}
	else// if (TransMode[1] == TRANS_PULSE)
	{
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Y_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Y_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Y_PULSE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Y_PULSE_LT, 1 );
	}

	if (TransMode[2] == NORM)
	{
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Z_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Z_NORM_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Z_PULSE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Z_PULSE_LT, 0 );
	}
	else// if (TransMode[2] == TRANS_PULSE)
	{
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Z_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Z_NORM_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_TRANSL_Z_PULSE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_TRANSL_Z_PULSE_LT, 1 );
	}

	if (RotMode[ROLL] == DISC_RATE)
	{
		WriteCOMPOOL_IS( SCP_FWD_ROT_ROLL_DISC_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_ROLL_DISC_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_ROT_ROLL_PULSE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_ROLL_PULSE_LT, 0 );
	}
	else// if (RotMode[ROLL] == ROT_PULSE)
	{
		WriteCOMPOOL_IS( SCP_FWD_ROT_ROLL_DISC_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_ROLL_DISC_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_ROT_ROLL_PULSE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_ROLL_PULSE_LT, 1 );
	}

	if (RotMode[PITCH] == DISC_RATE)
	{
		WriteCOMPOOL_IS( SCP_FWD_ROT_PITCH_DISC_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_PITCH_DISC_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_ROT_PITCH_PULSE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_PITCH_PULSE_LT, 0 );
	}
	else// if (RotMode[PITCH] == ROT_PULSE)
	{
		WriteCOMPOOL_IS( SCP_FWD_ROT_PITCH_DISC_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_PITCH_DISC_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_ROT_PITCH_PULSE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_PITCH_PULSE_LT, 1 );
	}

	if (RotMode[YAW] == DISC_RATE)
	{
		WriteCOMPOOL_IS( SCP_FWD_ROT_YAW_DISC_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_YAW_DISC_LT, 1 );
		WriteCOMPOOL_IS( SCP_FWD_ROT_YAW_PULSE_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_YAW_PULSE_LT, 0 );
	}
	else// if (RotMode[YAW] == ROT_PULSE)
	{
		WriteCOMPOOL_IS( SCP_FWD_ROT_YAW_DISC_LT, 0 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_YAW_DISC_LT, 0 );
		WriteCOMPOOL_IS( SCP_FWD_ROT_YAW_PULSE_LT, 1 );
		WriteCOMPOOL_IS( SCP_AFT_ROT_YAW_PULSE_LT, 1 );
	}

	return;
}

void OrbitDAP::DAP_PBI_Press( void )
{
	// A
	unsigned short FWD_DAP_SELECT_A = ReadCOMPOOL_IS( SCP_FWD_DAP_SELECT_A );
	unsigned short AFT_DAP_SELECT_A = ReadCOMPOOL_IS( SCP_AFT_DAP_SELECT_A );
	if ((FWD_DAP_SELECT_A == 1) || (AFT_DAP_SELECT_A == 1))
	{
		if (DAPSelect != A)
		{
			DAPSelect = A;
			UpdateDAPParameters();
		}
	}

	// B
	unsigned short FWD_DAP_SELECT_B = ReadCOMPOOL_IS( SCP_FWD_DAP_SELECT_B );
	unsigned short AFT_DAP_SELECT_B = ReadCOMPOOL_IS( SCP_AFT_DAP_SELECT_B );
	if ((FWD_DAP_SELECT_B == 1) || (AFT_DAP_SELECT_B == 1))
	{
		if (DAPSelect != B)
		{
			DAPSelect = B;
			UpdateDAPParameters();
		}
	}

	// AUTO
	unsigned short FWD_DAP_AUTO = ReadCOMPOOL_IS( SCP_FWD_DAP_AUTO );
	unsigned short AFT_DAP_AUTO = ReadCOMPOOL_IS( SCP_AFT_DAP_AUTO );
	if ((FWD_DAP_AUTO == 1) || (AFT_DAP_AUTO == 1))
	{
		if (DAPControlMode != AUTO)
		{
			DAPControlMode = AUTO;
			if(CurManeuver.IsValid) StartCurManeuver();
		}
	}

	// INRTL
	unsigned short FWD_DAP_INRTL = ReadCOMPOOL_IS( SCP_FWD_DAP_MAN );
	unsigned short AFT_DAP_INRTL = ReadCOMPOOL_IS( SCP_AFT_DAP_MAN );
	if ((FWD_DAP_INRTL == 1) || (AFT_DAP_INRTL == 1))
	{
		if (DAPControlMode != INRTL)
		{
			DAPControlMode = INRTL;
			StartManeuver(curM50Matrix, AttManeuver::MNVR);
		}
	}

	// LVLH
	unsigned short FWD_DAP_LVLH = ReadCOMPOOL_IS( SCP_FWD_RCS_OPTIONS_NORM );
	unsigned short AFT_DAP_LVLH = ReadCOMPOOL_IS( SCP_AFT_RCS_OPTIONS_NORM );
	if ((FWD_DAP_LVLH == 1) || (AFT_DAP_LVLH == 1))
	{
		if (DAPControlMode != LVLH)
		{
			DAPControlMode = LVLH;
			StartManeuver(GetCurrentLVLHAttMatrix(), AttManeuver::TRK);
		}
	}

	// FREE
	unsigned short FWD_DAP_FREE = ReadCOMPOOL_IS( SCP_FWD_RCS_OPTIONS_VERNIER );
	unsigned short AFT_DAP_FREE = ReadCOMPOOL_IS( SCP_AFT_RCS_OPTIONS_VERNIER );
	if ((FWD_DAP_FREE == 1) || (AFT_DAP_FREE == 1))
	{
		if (DAPControlMode != FREE)
		{
			DAPControlMode = FREE;
			for(unsigned int i=0;i<3;i++) {
				RotMode[i]=ROT_PULSE;
				RotPulseInProg[i]=false;
			}
		}
	}

	// (blank)
	// LOW Z
	// HIGH Z

	// PRI
	unsigned short FWD_RCS_PRI = ReadCOMPOOL_IS( SCP_FWD_ROTATION_ROLL_DISC_RATE );
	unsigned short AFT_RCS_PRI = ReadCOMPOOL_IS( SCP_AFT_ROTATION_ROLL_DISC_RATE );
	if ((FWD_RCS_PRI == 1) || (AFT_RCS_PRI == 1))
	{
		if (DAPMode != PRI)
		{
			DAPMode = PRI;
			UpdateDAPParameters();
		}
	}

	// ALT
	unsigned short FWD_RCS_ALT = ReadCOMPOOL_IS( SCP_FWD_ROTATION_PITCH_DISC_RATE );
	unsigned short AFT_RCS_ALT = ReadCOMPOOL_IS( SCP_AFT_ROTATION_PITCH_DISC_RATE );
	if ((FWD_RCS_ALT == 1) || (AFT_RCS_ALT == 1))
	{
		if (DAPMode != ALT)
		{
			DAPMode = ALT;
			UpdateDAPParameters();
		}
	}

	// VERN
	unsigned short FWD_RCS_VERN = ReadCOMPOOL_IS( SCP_FWD_ROTATION_YAW_DISC_RATE );
	unsigned short AFT_RCS_VERN = ReadCOMPOOL_IS( SCP_AFT_ROTATION_YAW_DISC_RATE );
	if ((FWD_RCS_VERN == 1) || (AFT_RCS_VERN == 1))
	{
		if (DAPMode != VERN)
		{
			DAPMode = VERN;
			UpdateDAPParameters();
		}
	}

	// TRANS X NORM
	unsigned short FWD_TRANSLATION_X_NORM = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_X_NORM );
	unsigned short AFT_TRANSLATION_X_NORM = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_X_NORM );
	if ((FWD_TRANSLATION_X_NORM == 1) || (AFT_TRANSLATION_X_NORM == 1))
	{
		if (TransMode[0] != NORM)
		{
			TransMode[0]=NORM;
			TransPulseInProg[0]=false;
			TransPulseDV.x=0.0;
		}
	}

	// TRANS Y NORM
	unsigned short FWD_TRANSLATION_Y_NORM = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_Y_NORM );
	unsigned short AFT_TRANSLATION_Y_NORM = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_Y_NORM );
	if ((FWD_TRANSLATION_Y_NORM == 1) || (AFT_TRANSLATION_Y_NORM == 1))
	{
		if (TransMode[1] != NORM)
		{
			TransMode[1]=NORM;
			TransPulseInProg[1]=false;
			TransPulseDV.y=0.0;
		}
	}

	// TRANS Z NORM
	unsigned short FWD_TRANSLATION_Z_NORM = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_Z_NORM );
	unsigned short AFT_TRANSLATION_Z_NORM = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_Z_NORM );
	if ((FWD_TRANSLATION_Z_NORM == 1) || (AFT_TRANSLATION_Z_NORM == 1))
	{
		if (TransMode[2] != NORM)
		{
			TransMode[2]=NORM;
			TransPulseInProg[2]=false;
			TransPulseDV.z=0.0;
		}
	}

	// ROLL DISC RATE
	unsigned short FWD_ROTATION_ROLL_ACCEL = ReadCOMPOOL_IS( SCP_FWD_ROTATION_ROLL_ACCEL );
	unsigned short AFT_ROTATION_ROLL_ACCEL = ReadCOMPOOL_IS( SCP_AFT_ROTATION_ROLL_ACCEL );
	if ((FWD_ROTATION_ROLL_ACCEL == 1) || (AFT_ROTATION_ROLL_ACCEL == 1))
	{
		if (RotMode[ROLL] != DISC_RATE)
		{
			RotMode[ROLL]=DISC_RATE;
			RotPulseInProg[ROLL]=false;
		}
	}

	// PITCH DISC RATE
	unsigned short FWD_ROTATION_PITCH_ACCEL = ReadCOMPOOL_IS( SCP_FWD_ROTATION_PITCH_ACCEL );
	unsigned short AFT_ROTATION_PITCH_ACCEL = ReadCOMPOOL_IS( SCP_AFT_ROTATION_PITCH_ACCEL );
	if ((FWD_ROTATION_PITCH_ACCEL == 1) || (AFT_ROTATION_PITCH_ACCEL == 1))
	{
		if (RotMode[PITCH] != DISC_RATE)
		{
			RotMode[PITCH]=DISC_RATE;
			RotPulseInProg[PITCH]=false;
		}
	}

	// YAW DISC RATE
	unsigned short FWD_ROTATION_YAW_ACCEL = ReadCOMPOOL_IS( SCP_FWD_ROTATION_YAW_ACCEL );
	unsigned short AFT_ROTATION_YAW_ACCEL = ReadCOMPOOL_IS( SCP_AFT_ROTATION_YAW_ACCEL );
	if ((FWD_ROTATION_YAW_ACCEL == 1) || (AFT_ROTATION_YAW_ACCEL == 1))
	{
		if (RotMode[YAW] != DISC_RATE)
		{
			RotMode[YAW]=DISC_RATE;
			RotPulseInProg[YAW]=false;
		}
	}

	// TRANS X PULSE
	unsigned short FWD_TRANSLATION_X_PULSE = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_X_PULSE );
	unsigned short AFT_TRANSLATION_X_PULSE = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_X_PULSE );
	if ((FWD_TRANSLATION_X_PULSE == 1) || (AFT_TRANSLATION_X_PULSE == 1))
	{
		if ((TransMode[0] != TRANS_PULSE) && ((GetMajorMode() == 201) || (GetMajorMode() == 202)))
		{
			TransMode[0]=TRANS_PULSE;
			TransPulseInProg[0]=false;
			TransPulseDV.x=0.0;
		}
	}

	// TRANS Y PULSE
	unsigned short FWD_TRANSLATION_Y_PULSE = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_Y_PULSE );
	unsigned short AFT_TRANSLATION_Y_PULSE = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_Y_PULSE );
	if ((FWD_TRANSLATION_Y_PULSE == 1) || (AFT_TRANSLATION_Y_PULSE == 1))
	{
		if ((TransMode[1] != TRANS_PULSE) && ((GetMajorMode() == 201) || (GetMajorMode() == 202)))
		{
			TransMode[1]=TRANS_PULSE;
			TransPulseInProg[1]=false;
			TransPulseDV.y=0.0;
		}
	}

	// TRANS Z PULSE
	unsigned short FWD_TRANSLATION_Z_PULSE = ReadCOMPOOL_IS( SCP_FWD_TRANSLATION_Z_PULSE );
	unsigned short AFT_TRANSLATION_Z_PULSE = ReadCOMPOOL_IS( SCP_AFT_TRANSLATION_Z_PULSE );
	if ((FWD_TRANSLATION_Z_PULSE == 1) || (AFT_TRANSLATION_Z_PULSE == 1))
	{
		if ((TransMode[2] != TRANS_PULSE) && ((GetMajorMode() == 201) || (GetMajorMode() == 202)))
		{
			TransMode[2]=TRANS_PULSE;
			TransPulseInProg[2]=false;
			TransPulseDV.z=0.0;
		}
	}

	// ROLL PULSE
	unsigned short FWD_ROTATION_ROLL_PULSE = ReadCOMPOOL_IS( SCP_FWD_ROTATION_ROLL_PULSE );
	unsigned short AFT_ROTATION_ROLL_PULSE = ReadCOMPOOL_IS( SCP_AFT_ROTATION_ROLL_PULSE );
	if ((FWD_ROTATION_ROLL_PULSE == 1) || (AFT_ROTATION_ROLL_PULSE == 1))
	{
		if (RotMode[ROLL] != ROT_PULSE)
		{
			RotMode[ROLL]=ROT_PULSE;
			RotPulseInProg[ROLL] = false;
		}
	}

	// PITCH PULSE
	unsigned short FWD_ROTATION_PITCH_PULSE = ReadCOMPOOL_IS( SCP_FWD_ROTATION_PITCH_PULSE );
	unsigned short AFT_ROTATION_PITCH_PULSE = ReadCOMPOOL_IS( SCP_AFT_ROTATION_PITCH_PULSE );
	if ((FWD_ROTATION_PITCH_PULSE == 1) || (AFT_ROTATION_PITCH_PULSE == 1))
	{
		if (RotMode[PITCH] != ROT_PULSE)
		{
			RotMode[PITCH]=ROT_PULSE;
			RotPulseInProg[PITCH] = false;
		}
	}

	// YAW PULSE
	unsigned short FWD_ROTATION_YAW_PULSE = ReadCOMPOOL_IS( SCP_FWD_ROTATION_YAW_PULSE );
	unsigned short AFT_ROTATION_YAW_PULSE = ReadCOMPOOL_IS( SCP_AFT_ROTATION_YAW_PULSE );
	if ((FWD_ROTATION_YAW_PULSE == 1) || (AFT_ROTATION_YAW_PULSE == 1))
	{
		if (RotMode[YAW] != ROT_PULSE)
		{
			RotMode[YAW]=ROT_PULSE;
			RotPulseInProg[YAW] = false;
		}
	}
	return;
}

void OrbitDAP::ArmPCT( void )
{
	PCTArmed = true;
	return;
}

void OrbitDAP::DisarmPCT( void )
{
	PCTArmed = false;
	return;
}

void OrbitDAP::StartPCT()
{
	PCTActive = true;
	PCTStartTime = oapiGetSimTime();
	DAPMode = PRI;
	DAPControlMode = FREE;
	return;
}

void OrbitDAP::StopPCT()
{
	PCTActive = false;
	DAPSelect = A;
	DAPMode = VERN;
	// TODO: mode to A9/B9 DAP CONFIGs

	// TODO stop firing RCS jets
	return;
}

void OrbitDAP::PCTControl(double simt)
{
	double dT=simt-PCTStartTime;

	//prevent translation thrusters except (up group) from firing
	TransThrusterCommands[0].ResetLine();
	TransThrusterCommands[1].ResetLine();

	//fire thrusters as appropriate
	if(dT<=PCT_STAGE1) TransThrusterCommands[2].SetLine(-0.5f);
	else if(dT<=PCT_STAGE2) TransThrusterCommands[2].ResetLine();
	else if(dT<=PCT_STAGE3) TransThrusterCommands[2].SetLine(-0.5f);
	else {
		TransThrusterCommands[2].ResetLine();
		StopPCT();
	}
}

void OrbitDAP::UpdateDAPParameters()
{
	TransPulse=DAPConfiguration[DAPSelect].PRI_TRAN_PLS * FPS2MS; //same for all modes
	if(DAPMode==PRI) {
		degRotRate=DAPConfiguration[DAPSelect].PRI_ROT_RATE;
		degAttDeadband=DAPConfiguration[DAPSelect].PRI_ATT_DB;
		degRateDeadband=DAPConfiguration[DAPSelect].PRI_RATE_DB;
		degRotPulse=DAPConfiguration[DAPSelect].PRI_ROT_PLS;

		if(DAPConfiguration[DAPSelect].PRI_P_OPTION!=0)
			Torque.data[PITCH]=0.5*ORBITER_PITCH_TORQUE;
		else Torque.data[PITCH]=ORBITER_PITCH_TORQUE;
		if(DAPConfiguration[DAPSelect].PRI_Y_OPTION!=0)
			Torque.data[YAW]=0.5*ORBITER_YAW_TORQUE;
		else Torque.data[YAW]=ORBITER_YAW_TORQUE;
		Torque.data[ROLL]=ORBITER_ROLL_TORQUE;
	}
	else if(DAPMode==ALT) {
		degRotRate=DAPConfiguration[DAPSelect].PRI_ROT_RATE;
		degAttDeadband=DAPConfiguration[DAPSelect].PRI_ATT_DB;
		degRateDeadband=DAPConfiguration[DAPSelect].ALT_RATE_DB;
		degRotPulse=DAPConfiguration[DAPSelect].PRI_ROT_PLS;
		if(DAPConfiguration[DAPSelect].ALT_JET_OPT==2) {
			Torque.data[PITCH]=0.5*ORBITER_PITCH_TORQUE;
			Torque.data[YAW]=0.5*ORBITER_YAW_TORQUE;
			Torque.data[ROLL]=0.5*ORBITER_ROLL_TORQUE;
		}
		else {
			Torque.data[PITCH]=ORBITER_PITCH_TORQUE;
			Torque.data[YAW]=ORBITER_YAW_TORQUE;
			Torque.data[ROLL]=ORBITER_ROLL_TORQUE;
		}
	}
	else if(DAPMode==VERN) {
		degRotRate=DAPConfiguration[DAPSelect].VERN_ROT_RATE;
		degAttDeadband=DAPConfiguration[DAPSelect].VERN_ATT_DB;
		degRateDeadband=DAPConfiguration[DAPSelect].VERN_RATE_DB;
		degRotPulse=DAPConfiguration[DAPSelect].VERN_ROT_PLS;
		Torque.data[PITCH]=0.1*ORBITER_PITCH_TORQUE;
		Torque.data[YAW]=0.1*ORBITER_YAW_TORQUE;
		Torque.data[ROLL]=0.1*ORBITER_ROLL_TORQUE;
	}
}

double OrbitDAP::CalcManeuverCompletionTime(const MATRIX3& curM50Matrix, const MATRIX3& tgtLVLHMatrix, const MATRIX3& curLVLHMatrix, double degOrbitalRate) const
{
	double mnvrTime = 0.0;
	double lastMnvrTime = 0.0;
	int counter = 0;
	VECTOR3 Axis;
	MATRIX3 PYR;
	do {
		counter++;
		lastMnvrTime=mnvrTime;
		if(mnvrTime < 0) {
			mnvrTime=0.0;
		}

		double rotationAngle = degOrbitalRate*mnvrTime;
		MATRIX3 LVLHRotation;
		GetRotMatrixY(-rotationAngle*RAD, LVLHRotation);
		MATRIX3 tgtM50Matrix = mul(mul(curLVLHMatrix, LVLHRotation), tgtLVLHMatrix);

		PYR = GetRotationErrorMatrix(curM50Matrix, tgtM50Matrix);
		double Angle=CalcEulerAngle(PYR, Axis);
		mnvrTime=(Angle*DEG)/degRotRate;
	} while(abs(mnvrTime-lastMnvrTime)>0.05 && counter<50);
	return max(mnvrTime, 0.0);
}

MATRIX3 OrbitDAP::GetCurrentLVLHRefMatrix() const
{
	VECTOR3 pos, vel;
	pStateVector->GetCurrentStateVectorsM50(pos, vel);
	return Transpose(GetGlobalToLVLHMatrix(pos, vel));
}

MATRIX3 OrbitDAP::GetCurrentLVLHAttMatrix() const
{
	return GetRotationErrorMatrix(GetCurrentLVLHRefMatrix(), curM50Matrix);
}

VECTOR3 OrbitDAP::GetAttitudeErrors( void ) const
{
	return ATT_ERR;
}

bool OrbitDAP::GetTimeToAttitude( double& time ) const
{
	if (ManeuverStatus != MNVR_IN_PROGRESS) return false;
	time = max( mnvrCompletionMET - STS()->GetMET(), 0 );
	return true;
}

}
