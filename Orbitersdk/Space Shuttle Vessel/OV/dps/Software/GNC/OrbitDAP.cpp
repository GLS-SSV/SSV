/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
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
2022/10/28   GLS
2022/12/17   GLS
2022/12/21   indy91
2022/12/23   GLS
2022/12/28   GLS
2022/12/31   GLS
2023/06/14   GLS
2023/09/24   GLS
2024/07/06   GLS
2025/07/20   GLS
2025/01/14   GLS
********************************************/
#include "OrbitDAP.h"
#include "../CRT_Interface.h"
#include <MathSSV.h>
#include "../../../ParameterValues.h"
#include "THC_SOP.h"
#include "StateVectorSoftware.h"
#include "GNCUtilities.h"
#include "../../../Atlantis.h"

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
		WriteCOMPOOL_ASS( SCP_OMSL_PITCH_YAW_CMD, 1, static_cast<float>(range( -5.0, OMSTrim.data[0], 5.0 )), 2 ); 
		WriteCOMPOOL_ASS( SCP_OMSL_PITCH_YAW_CMD, 2, static_cast<float>(range( -8.0, OMSTrim.data[1], 8.0 )), 2 ); 
	}
	if (Mode != LEFT_OMS)
	{
		WriteCOMPOOL_ASS( SCP_OMSR_PITCH_YAW_CMD, 1, static_cast<float>(range( -5.0, OMSTrim.data[0], 5.0 )), 2 ); 
		WriteCOMPOOL_ASS( SCP_OMSR_PITCH_YAW_CMD, 2, static_cast<float>(range( -8.0, OMSTrim.data[2], 8.0 )), 2 ); 
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
	RHC[0] = ReadCOMPOOL_SS( SCP_DEMAN );
	RHC[1] = ReadCOMPOOL_SS( SCP_DYMAN );
	RHC[2] = ReadCOMPOOL_SS( SCP_DAMAN );
	bool RHCdetent[3];
	RHCdetent[0] = ReadCOMPOOL_AIS( SCP_RHC_STATE, 2, 3 ) == 0;
	RHCdetent[1] = ReadCOMPOOL_AIS( SCP_RHC_STATE, 3, 3 ) == 0;
	RHCdetent[2] = ReadCOMPOOL_AIS( SCP_RHC_STATE, 1, 3 ) == 0;
	bool RHCpastsoftstop[3];
	RHCpastsoftstop[0] = ReadCOMPOOL_IS( SCP_PSS_EXCEED ) != 0;
	RHCpastsoftstop[1] = ReadCOMPOOL_IS( SCP_YSS_EXCEED ) != 0;
	RHCpastsoftstop[2] = ReadCOMPOOL_IS( SCP_RSS_EXCEED ) != 0;

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
	RHCdetent[0] = ReadCOMPOOL_AIS( SCP_RHC_STATE, 2, 3 ) != 0;
	RHCdetent[1] = ReadCOMPOOL_AIS( SCP_RHC_STATE, 3, 3 ) != 0;
	RHCdetent[2] = ReadCOMPOOL_AIS( SCP_RHC_STATE, 1, 3 ) != 0;

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

		WriteCOMPOOL_ASS( SCP_OMSL_PITCH_YAW_CMD, 1, static_cast<float>(range( -5.0, Pitch, 5.0 )), 2 ); 
		WriteCOMPOOL_ASS( SCP_OMSL_PITCH_YAW_CMD, 2, static_cast<float>(range( -8.0, Yaw, 8.0 )), 2 ); 
	}
	if(ControlMode!=LEFT_OMS) //right OMS engine burning
	{
		double Pitch = dPitch + OMSTrim.data[0], Yaw = dYaw + OMSTrim.data[2];
		if(ControlMode==BOTH_OMS) Pitch+=dRoll;

		Rtrim = dYaw;
		if (ControlMode == BOTH_OMS) Rtrim = -Rtrim;

		WriteCOMPOOL_ASS( SCP_OMSR_PITCH_YAW_CMD, 1, static_cast<float>(range( -5.0, Pitch, 5.0 )), 2 ); 
		WriteCOMPOOL_ASS( SCP_OMSR_PITCH_YAW_CMD, 2, static_cast<float>(range( -8.0, Yaw, 8.0 )), 2 ); 
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

	WriteCOMPOOL_VS( SCP_RATE_EST, _V( degAngularVelocity.z, degAngularVelocity.x, degAngularVelocity.y ) );

	STS()->GetRotationMatrix(curM50Matrix);
	curM50Matrix = ConvertOrbitersimRotationMatrixToM50(curM50Matrix);
	CUR_ATT = GetYZX_PYRAnglesFromMatrix(curM50Matrix)*DEG;
	// correct range
	if (CUR_ATT.x < 0.0) CUR_ATT.x += 360.0;
	if (CUR_ATT.y < 0.0) CUR_ATT.y += 360.0;
	if (CUR_ATT.z < 0.0) CUR_ATT.z += 360.0;

	VECTOR3 QV;
	double QS;
	MAT_TO_QUAT(Transpose(curM50Matrix), QS, QV);

	WriteCOMPOOL_VS(SCP_Q_B_I, 1, static_cast<float>(QS), 4);
	WriteCOMPOOL_VS(SCP_Q_B_I, 2, static_cast<float>(QV.x), 4);
	WriteCOMPOOL_VS(SCP_Q_B_I, 3, static_cast<float>(QV.y), 4);
	WriteCOMPOOL_VS(SCP_Q_B_I, 4, static_cast<float>(QV.z), 4);

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

	pTHC_SOP = dynamic_cast<THC_SOP*>(FindSoftware( "THC_SOP" ));
	assert( (pTHC_SOP != NULL) && "OrbitDAP::Realize.pTHC_SOP" );

	UpdateDAPParameters();
}

void OrbitDAP::OnPreStep(double simt, double simdt, double mjd)
{
	unsigned short CDR_SPDBK_THROT = ReadCOMPOOL_IS( SCP_LH_AUTOSB );
	unsigned short PLT_SPDBK_THROT = ReadCOMPOOL_IS( SCP_RH_AUTOSB );
	unsigned short CDR_BodyFlap = ReadCOMPOOL_IS( SCP_LH_AUTMANBF );
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
					bool RHCdetent = (ReadCOMPOOL_AIS( SCP_RHC_STATE, 1, 3 ) != 0) &&
						(ReadCOMPOOL_AIS( SCP_RHC_STATE, 2, 3 ) != 0) &&
						(ReadCOMPOOL_AIS( SCP_RHC_STATE, 3, 3 ) != 0);

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

bool OrbitDAP::ItemInput_UNIVPTG( int item, const char* Data )
{
	switch (item)
	{
		case 1:
			{
				int nNew = 0;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if (nNew < 365) START_TIME[0] = nNew;
					else return false;
				}
				else return false;
			}
			break;
		case 2:
			{
				int nNew = 0;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if (nNew < 24) START_TIME[1] = nNew;
					else return false;
				}
				else return false;
			}
			break;
		case 3:
			{
				int nNew = 0;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if (nNew < 60) START_TIME[2] = nNew;
					else return false;
				}
				else return false;
			}
			break;
		case 4:
			{
				int nNew = 0;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if (nNew < 60) START_TIME[3] = nNew;
					else return false;
				}
				else return false;
			}
			break;
		case 5:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew < 359.99)
					{
						MNVR_OPTION.data[ROLL] = dNew;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 6:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew < 359.99)
					{
						MNVR_OPTION.data[PITCH] = dNew;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 7:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if ((dNew <= 90.0) || ((dNew >= 270.0) && (dNew < 359.99))) MNVR_OPTION.data[YAW] = dNew;
					else return false;
				}
				else return false;
			}
			break;
		case 8:
			{
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
					else return false;
				}
				else return false;
			}
			break;
		case 9:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if ((dNew <= 359.999) && (TGT_ID == 5))
					{
						RA = dNew;
						RA_DEC_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 10:
			{
				double dNew;
				if (GetDoubleSigned( Data, dNew ))
				{
					if ((dNew >= -90.0) && (dNew <= 90.0) && (TGT_ID == 5))
					{
						DEC = dNew;
						RA_DEC_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 11:
			{
				double dNew;
				if (GetDoubleSigned( Data, dNew ))
				{
					if ((dNew >= -90.0) && (dNew <= 90.0) && (TGT_ID == 3))
					{
						LAT = dNew;
						LAT_LON_ALT_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 12:
			{
				double dNew;
				if (GetDoubleSigned( Data, dNew ))
				{
					if ((dNew >= -180.0) && (dNew <= 180.0) && (TGT_ID == 3))
					{
						LON = dNew;
						LAT_LON_ALT_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 13:
			{
				double dNew;
				if (GetDoubleSigned( Data, dNew ))
				{
					if ((dNew >= -3444.0) && (dNew <= 20000.0) && (TGT_ID == 3))
					{
						_ALT = dNew;
						LAT_LON_ALT_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 14:
			{
				int nNew;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if ((nNew >= 1) && (nNew <= 5))
					{
						BODY_VECT = nNew;
						P_Y_flash = false;
						if (BODY_VECT == 1)
						{
							P = 0.0;
							Y = 0.0;
						}
						else if (BODY_VECT == 2)
						{
							P = 180.0;
							Y = 0.0;
						}
						else if (BODY_VECT == 3)
						{
							P = 90.0;
							Y = 0.0;
						}
						else if (BODY_VECT == 4)
						{
							P = 0.0;
							Y = 280.57;
						}
						else P_Y_flash = true;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 15:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if ((dNew < 359.99) && (BODY_VECT == 5))
					{
						P = dNew;
						P_Y_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 16:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (((dNew <= 90.0) || ((dNew >= 270.0) && (dNew < 359.99))) && (BODY_VECT == 5))
					{
						Y=dNew;
						P_Y_flash = false;
					}
					else return false;
				}
				else return false;
			}
			break;
		case 17:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew < 359.99) OM = dNew;
					else return false;
				}
				else return false;
			}
			break;
		case 18:
			{
				if (strlen( Data ) == 0)
				{
					//VECTOR3 radTargetAtt = ConvertAnglesBetweenM50AndOrbiter(MNVR_OPTION*RAD, true);
					MATRIX3 tgtAtt = GetRotationMatrixYZX(_V(MNVR_OPTION.data[ROLL], MNVR_OPTION.data[PITCH], MNVR_OPTION.data[YAW])*RAD);
					double startTime = START_TIME[0]*86400.0+ START_TIME[1]*3600.0 + START_TIME[2]*60.0 + START_TIME[3];
					if(startTime <= STS()->GetMET())
					{
						LoadCurINRTLManeuver(tgtAtt);
					}
					else
					{
						FutMnvrStartTime = startTime;
						LoadFutINRTLManeuver(tgtAtt);
					}

					RA_DEC_flash = false;
					LAT_LON_ALT_flash = false;
					P_Y_flash = false;
				}
				else return false;
			}
			break;
		case 19:
			{
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
				else return false;
			}
			break;
		/*case 20:
			{
				LoadRotationManeuver();
				RA_DEC_flash = false;
				LAT_LON_ALT_flash = false;
				P_Y_flash = false;
			}
			break;*/
		case 21:
			{
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
				else return false;
			}
			break;
		case 23:
			if (strlen( Data ) == 0) ERRTOT = true;// ERR TOT
			else return false;
			break;
		case 24:
			if (strlen( Data ) == 0) ERRTOT = false;// ERR DAP
			else return false;
			break;
		default:
			return false;
	}
	return true;
}

bool OrbitDAP::ItemInput_DAPCONFIG( int item, const char* Data )
{
	switch (item)
	{
		case 3:
		case 4:
			{
				int num;
				if (GetIntegerUnsigned( Data, num ))
				{
					if (num <= 15)
					{
						// TODO use num
						editDAP=item-3;
						DAPConfiguration[2]=DAPConfiguration[editDAP];
					}
					else return false;
				}
				else return false;
			}
			break;
		case 5:
			if (strlen( Data ) == 0)
			{
				if(editDAP != -1) DAPConfiguration[editDAP]=DAPConfiguration[2];
				editDAP=-1;
			}
			else return false;
			break;
		case 10:
		case 30:
		case 50:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if(dNew>=0.05 && dNew<=2.0)
					{
						DAPConfiguration[convert[item]].PRI_ROT_RATE=dNew;
						if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 11:
		case 31:
		case 51:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if(dNew>0.10 && dNew<=40.0)
					{
						DAPConfiguration[convert[item]].PRI_ATT_DB=dNew;
						if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 12:
		case 32:
		case 52:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if(dNew>=0.10 && dNew<=5.0)
					{
						DAPConfiguration[convert[item]].PRI_RATE_DB=dNew;
						if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 13:
		case 33:
		case 53:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if(dNew>=0.04 && dNew<=1.0)
					{
						DAPConfiguration[convert[item]].PRI_ROT_PLS=dNew;
						if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 14:
		case 34:
		case 54:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew<=0.999)
					{
						DAPConfiguration[convert[item]].PRI_COMP=dNew;
						if(convert[item]==DAPSelect && DAPMode==PRI) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 15:
		case 35:
		case 55:
			if (strlen( Data ) == 0)
			{
				if (DAPConfiguration[convert[item]].PRI_P_OPTION<2)
				{
					DAPConfiguration[convert[item]].PRI_P_OPTION++;
					if (DAPMode==PRI)
					{
						if (DAPConfiguration[DAPSelect].PRI_P_OPTION==1)
						{
							STS()->DisableThrusters(AftPitchThrusters, 2);
							UpdateDAPParameters();
						}
						else if (DAPConfiguration[DAPSelect].PRI_P_OPTION==2)
						{
							STS()->EnableThrusters(AftPitchThrusters, 2);
							STS()->DisableThrusters(NosePitchThrusters, 2);
							UpdateDAPParameters();
						}
					}
				}
				else
				{
					DAPConfiguration[convert[item]].PRI_P_OPTION=0;
					if (DAPConfiguration[DAPSelect].PRI_P_OPTION==0)
					{
						STS()->EnableThrusters(NosePitchThrusters, 2);
						UpdateDAPParameters();
					}
				}
			}
			else return false;
			break;
		case 16:
		case 36:
		case 56:
			if (strlen( Data ) == 0)
			{
				if (DAPConfiguration[convert[item]].PRI_Y_OPTION<2)
				{
					DAPConfiguration[convert[item]].PRI_Y_OPTION++;
					if (DAPMode==PRI)
					{
						if (DAPConfiguration[DAPSelect].PRI_Y_OPTION==1)
						{
							STS()->DisableThrusters(AftYawThrusters, 2);
							UpdateDAPParameters();
						}
						else if (DAPConfiguration[DAPSelect].PRI_Y_OPTION==2)
						{
							STS()->EnableThrusters(AftYawThrusters, 2);
							STS()->DisableThrusters(NoseYawThrusters, 2);
							UpdateDAPParameters();
						}
					}
				}
				else
				{
					DAPConfiguration[convert[item]].PRI_Y_OPTION=0;
					if (DAPConfiguration[DAPSelect].PRI_Y_OPTION==0)
					{
						STS()->EnableThrusters(NoseYawThrusters, 2);
						UpdateDAPParameters();
					}
				}
			}
			else return false;
			break;
		case 17:
		case 37:
		case 57:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.01 && dNew<=5.0)
					{
						DAPConfiguration[convert[item]].PRI_TRAN_PLS=dNew;
						if (convert[item]== DAPSelect && DAPMode==PRI) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 18:
		case 38:
		case 58:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.05 && dNew<=5.0)
					{
						DAPConfiguration[convert[item]].ALT_RATE_DB=dNew;
						if (convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 19:
		case 39:
		case 59:
			if (strlen( Data ) == 0)
			{
				if (DAPConfiguration[convert[item]].ALT_JET_OPT==0)
				{
					DAPConfiguration[convert[item]].ALT_JET_OPT=2;
					if (DAPMode==ALT)
					{
						if (DAPConfiguration[DAPSelect].ALT_JET_OPT==2)
						{
							STS()->DisableThrusters(NoseRotThrusters, 6);
							STS()->EnableThrusters(AftRotThrusters, 6);
							UpdateDAPParameters();
						}
					}
				}
				else
				{
					DAPConfiguration[convert[item]].ALT_JET_OPT=0;
					if (DAPMode==ALT)
					{
						if (DAPConfiguration[DAPSelect].ALT_JET_OPT==0)
						{
							STS()->EnableThrusters(NoseRotThrusters, 6);
							UpdateDAPParameters();
						}
					}
				}
			}
			else return false;
			break;
		case 20:
		case 40:
		case 60:
			{
				int nNew;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if (nNew>=1 && nNew<=3)
					{
						DAPConfiguration[convert[item]].ALT_JETS=nNew;
						if (convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 21:
		case 41:
		case 61:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.08 && dNew<=9.99)
					{
						DAPConfiguration[convert[item]].ALT_ON_TIME=dNew;
						if (convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 22:
		case 42:
		case 62:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew<=99.99)
					{
						DAPConfiguration[convert[item]].ALT_DELAY=dNew;
						if (convert[item]==DAPSelect && DAPMode==ALT) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 23:
		case 43:
		case 63:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.002 && dNew<=1.0)
					{
						DAPConfiguration[convert[item]].VERN_ROT_RATE=dNew;
						if (convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 24:
		case 44:
		case 64:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.01 && dNew<=40.0)
					{
						DAPConfiguration[convert[item]].VERN_ATT_DB=dNew;
						if (convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 25:
		case 45:
		case 65:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.01 && dNew<=0.5)
					{
						DAPConfiguration[convert[item]].VERN_RATE_DB=dNew;
						if (convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 26:
		case 46:
		case 66:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew>=0.001 && dNew<=0.5)
					{
						DAPConfiguration[convert[item]].VERN_ROT_PLS=dNew;
						if (convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 27:
		case 47:
		case 67:
			{
				double dNew;
				if (GetDoubleUnsigned( Data, dNew ))
				{
					if (dNew<=0.999)
					{
						DAPConfiguration[convert[item]].VERN_COMP=dNew;
						if (convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		case 28:
		case 48:
		case 68:
			{
				int nNew;
				if (GetIntegerUnsigned( Data, nNew ))
				{
					if (nNew<=9)
					{
						DAPConfiguration[convert[item]].VERN_CNTL_ACC=nNew;
						if (convert[item]==DAPSelect && DAPMode==VERN) UpdateDAPParameters();
					}
					else return false;
				}
				else return false;
			}
			break;
		default:
			return false;
	}
	return true;
}

void OrbitDAP::Paint_UNIVPTG( CRT_Interface* crt ) const
{
	char cbuf[255];
	double CUR_MNVR_COMPL[4];
	if ((DAPControlMode == INRTL) || (DAPControlMode == FREE)) ConvertSecondsToDDHHMMSS( STS()->GetMET(), CUR_MNVR_COMPL );
	else ConvertSecondsToDDHHMMSS( mnvrCompletionMET, CUR_MNVR_COMPL );
	sprintf_s( cbuf, 255, "%.2d:%.2d:%.2d", static_cast<int>(CUR_MNVR_COMPL[1]), static_cast<int>(CUR_MNVR_COMPL[2]), static_cast<int>(CUR_MNVR_COMPL[3]) );
	crt->TextGrid( 19, 2, cbuf );

	sprintf_s( cbuf, 255, "%.3d/%.2d:%.2d:%.2d", START_TIME[0], START_TIME[1], START_TIME[2], START_TIME[3] );
	crt->TextGrid( 15, 3, cbuf );

	crt->NumberGrid( 6, 6, MNVR_OPTION.data[PITCH], 3, 2 );
	crt->NumberGrid( 6, 7, MNVR_OPTION.data[ROLL], 3, 2 );
	crt->NumberGrid( 6, 8, MNVR_OPTION.data[YAW], 3, 2 );

	crt->NumberGrid( 11, 11, TGT_ID, 3 );

	unsigned char att = RA_DEC_flash ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL;
	crt->NumberGrid( 10, 13, RA, 3, 3, att );
	crt->NumberSignGrid( 10, 14, DEC, 2, 3, '+', '-', att );

	att = LAT_LON_ALT_flash ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL;
	crt->NumberSignGrid( 10, 15, LAT, 2, 3, '+', '-', att );
	crt->NumberSignGrid( 9, 16, LON, 3, 3, '+', '-', att );
	crt->NumberSignGrid( 9, 17, _ALT, 5, 1, '+', '-', att );

	crt->NumberGrid( 15, 19, BODY_VECT, 1 );

	att = P_Y_flash ? crt->DEUATT_FLASHING : crt->DEUATT_NORMAL;
	crt->NumberGrid( 8, 21, P, 3, 2, att );
	crt->NumberGrid( 8, 22, Y, 3, 2, att );

	if (OM >= 0.0)
	{
		crt->NumberGrid( 8, 23, OM, 3, 2 );
	}

	if (CurManeuver.IsValid)
	{
		if (CurManeuver.Type == AttManeuver::MNVR)
		{
			crt->TextGrid( 30, 5, "*" );
		}
		else if (CurManeuver.Type == AttManeuver::TRK)
		{
			crt->TextGrid( 30, 6, "*" );
		}
		else
		{
			crt->TextGrid( 30, 7, "*" );
		}
	}
	if (FutManeuver.IsValid)
	{
		if (FutManeuver.Type == AttManeuver::MNVR)
		{
			crt->TextGrid( 34, 5, "*" );
		}
		else if (FutManeuver.Type == AttManeuver::TRK)
		{
			crt->TextGrid( 34, 6, "*" );
		}
		else
		{
			crt->TextGrid( 34, 7, "*" );
		}
	}

	if (ERRTOT == true) crt->TextGrid( 32, 12, "*" );// ERR TOT
	else crt->TextGrid( 32, 13, "*" );// ERR DAP

	crt->NumberGrid( 27, 16, CUR_ATT.data[ROLL], 3, 2 );
	crt->NumberGrid( 35, 16, CUR_ATT.data[PITCH], 3, 2 );
	crt->NumberGrid( 43, 16, CUR_ATT.data[YAW], 3, 2 );

	crt->NumberGrid( 27, 17, REQD_ATT.data[ROLL], 3, 2 );
	crt->NumberGrid( 35, 17, REQD_ATT.data[PITCH], 3, 2 );
	crt->NumberGrid( 43, 17, REQD_ATT.data[YAW], 3, 2 );

	crt->NumberSignGrid( 26, 18, ATT_ERR.data[ROLL], 3, 2, '+', '-' );
	crt->NumberSignGrid( 34, 18, ATT_ERR.data[PITCH], 3, 2, '+', '-' );
	crt->NumberSignGrid( 42, 18, ATT_ERR.data[YAW], 3, 2, '+', '-' );

	crt->NumberSignGrid( 26, 19, degAngularVelocity.data[ROLL], 2, 3, '+', '-' );
	crt->NumberSignGrid( 34, 19, degAngularVelocity.data[PITCH], 2, 3, '+', '-' );
	crt->NumberSignGrid( 42, 19, degAngularVelocity.data[YAW], 2, 3, '+', '-' );
	return;
}

void OrbitDAP::Paint_DAPCONFIG( CRT_Interface* crt ) const
{
	char *strings[3] = {" ALL", "NOSE", "TAIL"};
	char cbuf[255];

	crt->TextGrid( 12, 3, "DAP A" );
	crt->TextGrid( 23, 3, "DAP B" );

	crt->TextGrid( 5, 3, "PRI" );
	crt->TextGrid( 5, 12, "ALT" );
	crt->TextGrid( 5, 18, "VERN" );

	crt->TextGrid( 17, 3, "01" );
	crt->TextGrid( 28, 3, "02" );

	int lim[3] = {3, 5, 5};
	int i, n;
	int edit = 2;// temporary
	for (n = 1, i = 0; n <= lim[edit]; n += 2, i++)
	{
		sprintf_s( cbuf, 255, "%.4f", DAPConfiguration[i].PRI_ROT_RATE );
		crt->TextGrid( 13 + (11 * i), 4, cbuf );
		sprintf_s( cbuf, 255, "%05.2f", DAPConfiguration[i].PRI_ATT_DB );
		crt->TextGrid( 14 + (11 * i), 5, cbuf );
		sprintf_s( cbuf, 255, "%.2f", DAPConfiguration[i].PRI_RATE_DB );
		crt->TextGrid( 15 + (11 * i), 6, cbuf );
		sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].PRI_ROT_PLS );
		crt->TextGrid( 14 + (11 * i), 7, cbuf );
		sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].PRI_COMP );
		crt->TextGrid( 14 + (11 * i), 8, cbuf );
		crt->TextGrid( 14 + (11 * i), 8, " " );// HACK
		crt->TextGrid( 15 + (11 * i), 9, strings[DAPConfiguration[i].PRI_P_OPTION] );
		crt->TextGrid( 15 + (11 * i), 10, strings[DAPConfiguration[i].PRI_Y_OPTION] );
		sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].PRI_TRAN_PLS );
		crt->TextGrid( 14 + (11 * i), 11, cbuf );

		sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].ALT_RATE_DB );
		crt->TextGrid( 14 + (11 * i), 13, cbuf );
		crt->TextGrid( 15 + (11 * i), 14, strings[DAPConfiguration[i].ALT_JET_OPT] );
		sprintf_s( cbuf, 255, "%d", DAPConfiguration[i].ALT_JETS );
		crt->TextGrid( 18 + (11 * i), 15, cbuf );
		sprintf_s( cbuf, 255, "%.2f", DAPConfiguration[i].ALT_ON_TIME );
		crt->TextGrid( 15 + (11 * i), 16, cbuf );
		sprintf_s( cbuf, 255, "%05.2f", DAPConfiguration[i].ALT_DELAY );
		crt->TextGrid( 14 + (11 * i), 17, cbuf );

		sprintf_s( cbuf, 255, "%.4f", DAPConfiguration[i].VERN_ROT_RATE );
		crt->TextGrid( 13 + (11 * i), 19, cbuf );
		sprintf_s( cbuf, 255, "%06.3f", DAPConfiguration[i].VERN_ATT_DB );
		crt->TextGrid( 13 + (11 * i), 20, cbuf );
		sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].VERN_RATE_DB );
		crt->TextGrid( 14 + (11 * i), 21, cbuf );
		crt->TextGrid( 14 + (11 * i), 21, " " );// HACK
		sprintf_s( cbuf, 255, "%05.3f", DAPConfiguration[i].VERN_ROT_PLS );
		crt->TextGrid( 14 + (11 * i), 22, cbuf );
		sprintf_s( cbuf, 255, "%.3f", DAPConfiguration[i].VERN_COMP );
		crt->TextGrid( 14 + (11 * i), 23, cbuf );
		crt->TextGrid( 14 + (11 * i), 23, " " );// HACK
		sprintf_s( cbuf, 255, "%d", DAPConfiguration[i].VERN_CNTL_ACC );
		crt->TextGrid( 18 + (11 * i), 24, cbuf );
	}
	return;
}

void OrbitDAP::BackgroundData_UNIVPTG( CRT_Interface* crt ) const
{
	// title
	crt->TextGrid( 20, 1, "UNIV PTG" );

	crt->TextGrid( 4, 2, "CUR MNVR COMPL" );
	crt->TextGrid( 2, 3, "1 START TIME" );

	crt->TextGrid( 15, 3, "\x7D\x7D\x7D" );
	crt->TextGrid( 19, 3, "\x7D\x7D" );
	crt->TextGrid( 22, 3, "\x7D\x7D" );
	crt->TextGrid( 25, 3, "\x7D\x7D" );

	crt->TextGrid( 1, 5, "MNVR" );
	crt->TextGrid( 6, 5, "OPTION" );
	crt->TextGrid( 2, 6, "5 R \x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 2, 7, "6 P" );
	crt->TextGrid( 2, 8, "7 Y" );

	crt->TextGrid( 1, 10, "TRK/ROT OPTIONS" );
	crt->TextGrid( 2, 11, "8 TGT ID \x7D\x7D\x7D" );

	crt->TextGrid( 2, 13, "9" );
	crt->TextGrid( 5, 13, "RA" );
	crt->TextGrid( 10, 13, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 2, 14, "10 DEC" );
	crt->TextGrid( 10, 14, "\x01" );
	crt->TextGrid( 10, 14, "\x02" );
	crt->TextGrid( 11, 14, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 2, 15, "11 LAT" );
	crt->TextGrid( 10, 15, "\x01" );
	crt->TextGrid( 10, 15, "\x02" );
	crt->TextGrid( 11, 15, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 2, 16, "12 LON" );
	crt->TextGrid( 9, 16, "\x01" );
	crt->TextGrid( 9, 16, "\x02" );
	crt->TextGrid( 10, 16, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 2, 17, "13 ALT" );
	crt->TextGrid( 9, 17, "\x01" );
	crt->TextGrid( 9, 17, "\x02" );
	crt->TextGrid( 10, 17, "\x7D\x7D\x7D\x7D\x7D\x7D\x7D" );

	crt->TextGrid( 2, 19, "14 BODY VECT" );
	crt->TextGrid( 15, 19, "\x7D" );

	crt->TextGrid( 2, 21, "15 P" );
	crt->TextGrid( 8, 21, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 2, 22, "16 Y" );
	crt->TextGrid( 2, 23, "17 OM" );

	crt->TextGrid( 16, 5, "START MNVR" );
	crt->TextGrid( 27, 5, "18" );
	crt->TextGrid( 22, 6, "TRK" );
	crt->TextGrid( 27, 6, "19" );
	crt->TextGrid( 22, 7, "ROT" );
	crt->TextGrid( 27, 7, "20" );
	crt->TextGrid( 21, 8, "CNCL" );
	crt->TextGrid( 27, 8, "21" );
	crt->TextGrid( 29, 4, "CUR" );
	crt->TextGrid( 33, 4, "FUT" );

	crt->TextGrid( 21, 10, "ATT MON" );
	crt->TextGrid( 22, 11, "22" );
	crt->TextGrid( 25, 11, "MON AXIS" );
	crt->TextGrid( 34, 11, "\x7D" );
	crt->TextGrid( 22, 12, "ERR TOT 23" );
	crt->TextGrid( 22, 13, "ERR DAP 24" );

	crt->TextGrid( 21, 16, "CUR" );
	crt->TextGrid( 21, 17, "REQD" );
	crt->TextGrid( 21, 18, "ERR" );
	crt->TextGrid( 21, 19, "RATE" );

	crt->TextGrid( 28, 15, "ROLL" );
	crt->TextGrid( 35, 15, "PITCH" );
	crt->TextGrid( 44, 15, "YAW" );

	crt->TextGrid( 44, 4, "CUR" );
	crt->TextGrid( 48, 4, "FUT" );
	crt->TextGrid( 37, 5, "RBST" );
	crt->TextGrid( 42, 5, "25" );
	crt->TextGrid( 37, 6, "CNCL" );
	crt->TextGrid( 42, 6, "26" );
	crt->TextGrid( 37, 7, "DURATION" );
	crt->TextGrid( 46, 7, "27" );
	crt->TextGrid( 38, 8, "\x7D\x7D" );
	crt->TextGrid( 41, 8, "\x7D\x7D" );
	crt->TextGrid( 44, 8, "\x7D\x7D\x7D\x7D\x7D" );
	return;
}

void OrbitDAP::BackgroundData_DAPCONFIG( CRT_Interface* crt ) const
{
	// title
	crt->TextGrid( 19, 1, "DAP CONFIG" );

	crt->TextGrid( 1, 4, "ROT RATE" );
	crt->TextGrid( 1, 5, "ATT DB" );
	crt->TextGrid( 1, 6, "RATE" );
	crt->TextGrid( 6, 6, "DB" );
	crt->TextGrid( 1, 7, "ROT PLS" );
	crt->TextGrid( 1, 8, "COMP" );
	crt->TextGrid( 1, 9, "P OPTION" );
	crt->TextGrid( 1, 10, "Y OPTION" );
	crt->TextGrid( 1, 11, "TRAN PLS" );

	crt->TextGrid( 1, 13, "RATE" );
	crt->TextGrid( 6, 13, "DB" );
	crt->TextGrid( 1, 14, "JET OPT" );
	crt->TextGrid( 1, 15, "# JETS" );
	crt->TextGrid( 1, 16, "ON" );
	crt->TextGrid( 4, 16, "TIME" );
	crt->TextGrid( 1, 17, "DELAY" );

	crt->TextGrid( 1, 19, "ROT RATE" );
	crt->TextGrid( 1, 20, "ATT DB" );
	crt->TextGrid( 1, 21, "RATE" );
	crt->TextGrid( 6, 21, "DB" );
	crt->TextGrid( 1, 22, "ROT PLS" );
	crt->TextGrid( 1, 23, "COMP" );
	crt->TextGrid( 1, 24, "CNTL ACC" );

	crt->TextGrid( 10, 3, "1" );
	crt->TextGrid( 17, 3, "\x7D\x7D" );

	crt->TextGrid( 10, 4, "10" );
	crt->TextGrid( 13, 4, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 5, "11" );
	crt->TextGrid( 14, 5, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 6, "12" );
	crt->TextGrid( 15, 6, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 7, "13" );
	crt->TextGrid( 14, 7, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 8, "14" );
	crt->TextGrid( 15, 8, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 9, "15" );
	crt->TextGrid( 10, 10, "15" );
	crt->TextGrid( 10, 11, "17" );
	crt->TextGrid( 14, 11, "\x7D\x7D\x7D\x7D\x7D" );
	
	crt->TextGrid( 10, 13, "18" );
	crt->TextGrid( 14, 13, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 14, "19" );
	crt->TextGrid( 10, 15, "20" );
	crt->TextGrid( 18, 15, "\x7D" );
	crt->TextGrid( 10, 16, "21" );
	crt->TextGrid( 15, 16, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 17, "22" );
	crt->TextGrid( 14, 17, "\x7D\x7D\x7D\x7D\x7D" );
	
	crt->TextGrid( 10, 19, "23" );
	crt->TextGrid( 13, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 20, "24" );
	crt->TextGrid( 13, 20, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 21, "25" );
	crt->TextGrid( 15, 21, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 22, "26" );
	crt->TextGrid( 14, 22, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 23, "27" );
	crt->TextGrid( 15, 23, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 10, 24, "28" );
	crt->TextGrid( 18, 24, "\x7D" );

	crt->TextGrid( 21, 3, "2" );
	crt->TextGrid( 28, 3, "\x7D\x7D" );

	crt->TextGrid( 21, 4, "30" );
	crt->TextGrid( 24, 4, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 5, "31" );
	crt->TextGrid( 25, 5, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 6, "32" );
	crt->TextGrid( 26, 6, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 7, "33" );
	crt->TextGrid( 25, 7, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 8, "34" );
	crt->TextGrid( 26, 8, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 9, "35" );
	crt->TextGrid( 21, 10, "36" );
	crt->TextGrid( 21, 11, "37" );
	crt->TextGrid( 25, 11, "\x7D\x7D\x7D\x7D\x7D" );

	crt->TextGrid( 21, 13, "38" );
	crt->TextGrid( 25, 13, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 14, "39" );
	crt->TextGrid( 21, 15, "40" );
	crt->TextGrid( 29, 15, "\x7D" );
	crt->TextGrid( 21, 16, "41" );
	crt->TextGrid( 26, 16, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 17, "42" );
	crt->TextGrid( 25, 17, "\x7D\x7D\x7D\x7D\x7D" );

	crt->TextGrid( 21, 19, "43" );
	crt->TextGrid( 24, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 20, "44" );
	crt->TextGrid( 24, 20, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 21, "45" );
	crt->TextGrid( 26, 21, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 22, "46" );
	crt->TextGrid( 25, 22, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 23, "47" );
	crt->TextGrid( 26, 23, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 21, 24, "48" );
	crt->TextGrid( 29, 24, "\x7D" );

	crt->TextGrid( 34, 3, "PRI" );
	crt->TextGrid( 32, 4, "50" );
	crt->TextGrid( 35, 4, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 5, "51" );
	crt->TextGrid( 36, 5, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 6, "52" );
	crt->TextGrid( 37, 6, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 7, "53" );
	crt->TextGrid( 36, 7, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 8, "54" );
	crt->TextGrid( 37, 8, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 9, "55" );
	crt->TextGrid( 32, 10, "56" );
	crt->TextGrid( 32, 11, "57" );
	crt->TextGrid( 36, 11, "\x7D\x7D\x7D\x7D\x7D" );

	crt->TextGrid( 34, 12, "ALT" );
	crt->TextGrid( 32, 13, "58" );
	crt->TextGrid( 36, 13, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 14, "59" );
	crt->TextGrid( 32, 15, "60" );
	crt->TextGrid( 40, 15, "\x7D" );
	crt->TextGrid( 32, 16, "61" );
	crt->TextGrid( 37, 16, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 17, "62" );
	crt->TextGrid( 36, 17, "\x7D\x7D\x7D\x7D\x7D" );

	crt->TextGrid( 34, 18, "VERN" );
	crt->TextGrid( 32, 19, "63" );
	crt->TextGrid( 35, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 20, "64" );
	crt->TextGrid( 35, 20, "\x7D\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 21, "65" );
	crt->TextGrid( 37, 21, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 22, "66" );
	crt->TextGrid( 36, 22, "\x7D\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 23, "67" );
	crt->TextGrid( 37, 23, "\x7D\x7D\x7D\x7D" );
	crt->TextGrid( 32, 24, "68" );
	crt->TextGrid( 40, 24, "\x7D" );

	crt->TextGrid( 42, 3, "DAP EDIT" );
	crt->TextGrid( 42, 4, "3 DAP A\x7D\x7D" );
	crt->TextGrid( 42, 5, "4 DAP B\x7D\x7D" );
	crt->TextGrid( 42, 6, "5" );

	crt->TextGrid( 42, 10, "NOTCH FLTR" );
	crt->TextGrid( 43, 11, "ENA 6" );

	crt->TextGrid( 42, 13, "XJETS ROT" );
	crt->TextGrid( 43, 14, "ENA 7" );

	crt->TextGrid( 42, 16, "REBOOST" );
	crt->TextGrid( 43, 17, "8 CFG" );
	crt->TextGrid( 43, 18, "9 INTVL" );
	crt->TextGrid( 45, 19, "\x7D\x7D\x7D\x7D\x7D\x7D" );

	// lines
	crt->Line( 380, 68, 380, 662 );
	crt->Line( 589, 68, 589, 662 );
	crt->Line( 798, 230, 798, 662 );

	crt->Line( 798, 230, 997, 230 );
	return;
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
	return -ATT_ERR;
}

bool OrbitDAP::GetTimeToAttitude( double& time ) const
{
	if (ManeuverStatus != MNVR_IN_PROGRESS) return false;
	time = max( mnvrCompletionMET - STS()->GetMET(), 0 );
	return true;
}

}
