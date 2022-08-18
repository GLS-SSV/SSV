/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/06/16   GLS
2021/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/20   GLS
2022/04/26   GLS
2022/05/01   GLS
2022/05/07   GLS
2022/06/13   GLS
2022/08/05   GLS
********************************************/
#include "OMSBurnSoftware.h"
#include "OrbitDAP.h"
#include "../Atlantis.h"
#include "..\ParameterValues.h"
#include <MathSSV.h>
//#include <Stopwatch.h>
#include "IDP.h"
#include "..\vc\MDU.h"
#include <kost_elements.h>
#include "StateVectorSoftware.h"
#include "OMS_TVC_Command_SOP.h"
#include "OMS_TVC_Feedback_SOP.h"
#include <EngConst.h>


namespace dps
{
	const double EI_ALT = 400e3/MPS2FPS; // 400,000 feet

void ConvertEquToEcl(OBJHANDLE hPlanet, const VECTOR3& equPos, const VECTOR3& equVel, VECTOR3& eclPos, VECTOR3& eclVel)
{
	MATRIX3 obliquityMatrix;
	oapiGetPlanetObliquityMatrix(hPlanet, &obliquityMatrix);
	eclPos=mul(obliquityMatrix, equPos);
	eclVel=mul(obliquityMatrix, equVel);
}

/**
 * Converts LVLH angles (in radians) to M50 angles (in radians)
 * \param equPos position in right-handed equatorial frame (i.e. frame returned by StateVectorSoftware, converted to RH)
 * \param equVel velocity in right-handed equatorial frame (i.e. frame returned by StateVectorSoftware, converted to RH)
 */
VECTOR3 ConvertLVLHMatrixToM50Angles(const MATRIX3& tgtLVLHMatrix, const VECTOR3& equPos, const VECTOR3& equVel)
{
	MATRIX3 LVLHMatrix = Transpose(GetGlobalToLVLHMatrix(equPos, equVel));
	MATRIX3 M50Matrix = mul(LVLHMatrix, tgtLVLHMatrix);
	return GetYZX_PYRAnglesFromMatrix(M50Matrix);
}

OMSBurnSoftware::OMSBurnSoftware(SimpleGPCSystem* _gpc)
: SimpleGPCSoftware(_gpc, "OMSBurnSoftware"),
BurnInProg(false), BurnCompleted(false),
MnvrLoad(false), MnvrExecute(false), MnvrToBurnAtt(false),
bShowTimer(false),
bCalculatingPEG4Burn(false),
lastUpdateSimTime(-100.0), lastMET(0.0),
//propagatedState(0.05, 20, 3600.0),
propagator(0.2, 50, 7200.0),
pOrbitDAP(NULL), pStateVector(NULL)
{
	TIG[0]=TIG[1]=TIG[2]=TIG[3]=0.0;
	OMS = 0;
	PEG7 = _V(0.0, 0.0, 0.0);
	Trim = _V(0.0, 0.0, 0.0);

	C1 = 0.0;
	C2 = 0.0;
	HT = 0.0;
	ThetaT = 0.0;

	VGO = _V(0.0, 0.0, 0.0);
	DeltaVTot = 0.0;

	hEarth = NULL;

	OMSGimbalActr[0] = 1;
	OMSGimbalActr[1] = 1;

	// I-LOADs init
	TVR_ROLL = 180;
}

OMSBurnSoftware::~OMSBurnSoftware()
{
}

void OMSBurnSoftware::Realize()
{
	DiscreteBundle* pBundle = BundleManager()->CreateBundle("LOMS", 4);
	omsEngineCommand[LEFT].Connect(pBundle, 2);
	pBundle = BundleManager()->CreateBundle("ROMS", 4);
	omsEngineCommand[RIGHT].Connect(pBundle, 2);

	pOrbitDAP = dynamic_cast<OrbitDAP*>(FindSoftware("OrbitDAP"));
	assert( (pOrbitDAP != NULL) && "OMSBurnSoftware::Realize.pOrbitDAP" );
	pStateVector = dynamic_cast<StateVectorSoftware*>(FindSoftware("StateVectorSoftware"));
	assert( (pStateVector != NULL) && "OMSBurnSoftware::Realize.pStateVector" );
	pOMSTVCCMD_SOP = dynamic_cast<OMSTVCCMD_SOP*>(FindSoftware( "OMS_TVC_Command_SOP" ));
	assert( (pOMSTVCCMD_SOP != NULL) && "OMSBurnSoftware::Realize.pOMSTVCCMD_SOP" );
	pOMSTVCFDBK_SOP = dynamic_cast<OMSTVCFDBK_SOP*>(FindSoftware( "OMS_TVC_Feedback_SOP" ));
	assert( (pOMSTVCFDBK_SOP != NULL) && "OMSBurnSoftware::Realize.pOMSTVCFDBK_SOP" );

	hEarth = STS()->GetGravityRef();
	double J2 = 0;
	if(STS()->NonsphericalGravityEnabled()) J2 = oapiGetPlanetJCoeff(hEarth, 0);
	peg4Targeting.SetPlanetParameters(oapiGetMass(hEarth), oapiGetSize(hEarth), J2);
	propagator.SetParameters(STS()->GetMass(), oapiGetMass(hEarth), oapiGetSize(hEarth), J2);

	if(MnvrLoad) {
		LoadManeuver(false); // BurnAtt should have been loaded from scenario; don't have state vectors, so it can't be calculated here
		if(MnvrToBurnAtt) pOrbitDAP->ManeuverToINRTLAttitude(BurnAtt);
	}
}

void OMSBurnSoftware::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	GetValILOAD( "TVR_ROLL", ILOADs, TVR_ROLL );
	return;
}

void OMSBurnSoftware::OnPreStep(double simt, double simdt, double mjd)
{
	//if((SimT-lastUpdateSimTime) > 10.0) {
	if((simt-lastUpdateSimTime) > 60.0) {
		UpdateOrbitData();
		// if burn has been loaded, calculate apogee/perigee at end of burn
		if(MnvrLoad && !(BurnInProg || BurnCompleted)) {
			UpdateBurnPropagator();
		}
		lastUpdateSimTime = simt;
	}
	/*else {
		//oparam.ApT-=simdt;
		//oparam.PeT-=simdt;
		ApT-=simdt;
		PeT-=simdt;
	}*/

	//Stopwatch st;
	//st.Start();
	//propagatedState.Step(STS()->GetMET(), simdt);
	//propagator.Step(STS()->GetMET(), simdt);
	//double propTime = st.Stop();
	//sprintf_s(oapiDebugString(), 256, "Propagation step Time: %f", propTime);

	double met = STS()->GetMET();
	if(bCalculatingPEG4Burn) {
		if(peg4Targeting.Step()) {
			bCalculatingPEG4Burn = false;
			if(peg4Targeting.Converged()) {
				VECTOR3 tigPos, tigVel;
				pStateVector->GetPropagatedStateVectors(ConvertDDHHMMSSToSeconds(TIG), tigPos, tigVel);
				MATRIX3 RotMatrix = GetGlobalToLVLHMatrix(tigPos, tigVel, true);
				VECTOR3 equDeltaV = peg4Targeting.GetDeltaV();
				PEG7 = mul(RotMatrix, equDeltaV)*MPS2FPS;
				LoadManeuver();
				//pOMSBurnSoftware->SetManeuverData(t1_tig, DeltaV);
			}
		}
	}

	if(MnvrLoad && !(BurnInProg || BurnCompleted)) propagator.Step(STS()->GetMET(), simdt);

	if(!MnvrLoad || met<tig) return; // no burn to perform, or we haven't reached TIG yet
	unsigned int majorMode = GetMajorMode();
	if(majorMode != 104 && majorMode != 105 && majorMode != 202 && majorMode != 302) return; // make sure we are in MM which allows burns

	// get VGO in orbitersim global frame; this vector will be updated every timestep
	// do this at TIG so we get correct vector in global frame
	if(lastMET < tig) {
		VECTOR3 pos, vel;
		// this gets Orbitersim state vectors
		// it would be more realistic to get vectors from StateVectorSoftware, but this would make local->global->LVLH_TIG coordinate transformations harder (no IMUs)
		STS()->GetRelativePos(hEarth, pos);
		STS()->GetRelativeVel(hEarth, vel);
		MATRIX3 GlobalToLVLH_TIG = GetGlobalToLVLHMatrix(pos, vel, true);
		VGO_Global = tmul(GlobalToLVLH_TIG, DeltaV);
		// convert VGO_Global to body coordinates (and to fps) for display
		MATRIX3 LocalToGlobal;
		STS()->GetRotationMatrix(LocalToGlobal);
		VGO = tmul(LocalToGlobal, VGO_Global);
		VGO = _V(VGO.z, VGO.x, -VGO.y)*MPS2FPS;
	}

	// update VGO values
	// we need to update global (orbitersim frame) VGO, then convert VGOs to shuttle body coordinates for display
	VECTOR3 ThrustVector;
	if(STS()->GetThrustVector(ThrustVector)) {
		MATRIX3 LocalToGlobal;
		STS()->GetRotationMatrix(LocalToGlobal);
		VECTOR3 GlobalThrust = mul(LocalToGlobal, ThrustVector);
		VGO_Global -= (GlobalThrust/STS()->GetMass())*simdt;
		// convert VGO_Global to body coordinates (and to fps) for display
		VGO = tmul(LocalToGlobal, VGO_Global);
		VGO = _V(VGO.z, VGO.x, -VGO.y)*MPS2FPS;
	}

	if(OMS != 4) { // start/stop OMS engines
		if(BurnInProg && MnvrExecute) // check if engines should be shut down
		{
			if(met>=(IgnitionTime+BurnTime)) TerminateBurn();
			UpdateOrbitData();
		}
		else if(!BurnInProg && !BurnCompleted && MnvrExecute) // check if burn should start
		{
			StartBurn();
		}
	}

	lastMET = met;
}

bool OMSBurnSoftware::OnMajorModeChange(unsigned int newMajorMode)
{
	// cancel any ongoing burn
	if(BurnInProg) {
		TerminateBurn();
	}
	if(newMajorMode == 104 || newMajorMode == 105 || newMajorMode == 106 ||
		newMajorMode == 202 ||
		newMajorMode == 301 || newMajorMode == 302 || newMajorMode == 303)
	{
		WT=STS()->GetMass()*KG2LBM;
		if(newMajorMode == 303) {
			CalculateEIMinus5Att(BurnAtt);
			MnvrToBurnAtt = false;
			metAt400KFeet = pStateVector->GetMETAtAltitude(EI_ALT);
			bShowTimer = false;
		}
		else if (newMajorMode == 105)
		{
			bShowTimer = false;
			MnvrLoad=false;
			MnvrExecute=false;
			MnvrToBurnAtt=false;
			// reset burn flags
			BurnInProg=false;
			BurnCompleted=false;
			// reset burn data (VGO, TGO, etc.) displayed on CRT screen
			VGO = _V(0, 0, 0);
			DeltaVTot = 0.0;
		}
		return true;
	}
	else {
		// when leaving OMS MNVR EXEC display, turn off timer and mnvr flags (so it will be disabled the next time we enter OMS MNVR EXEC)
		bShowTimer = false;
		MnvrLoad=false;
		MnvrExecute=false;
		MnvrToBurnAtt=false;
		// reset burn flags
		BurnInProg=false;
		BurnCompleted=false;
		// reset burn data (VGO, TGO, etc.) displayed on CRT screen
		VGO = _V(0, 0, 0);
		DeltaVTot = 0.0;
	}
	return false;
}

bool OMSBurnSoftware::ItemInput( int item, const char* Data )
{
	double dNew;
	if(item>=1 && item<=4)
	{
		if (strlen( Data ) == 0)
		{
			OMS=item-1;
		}
		else return false;
	}
	else if (item==5)
	{
		if (GetMajorMode() == 202)
		{
			int num;
			if (GetIntegerUnsigned( Data, num ))
			{
				if (num <= 359) TVR_ROLL = num;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 6)
	{
		if (GetDoubleSigned( Data, dNew ))
		{
			if (fabs( dNew ) <= 6.0) Trim.data[0] = dNew;
			else return false;
		}
		else return false;
	}
	else if ((item >= 7) && (item <= 8))
	{
		if (GetDoubleSigned( Data, dNew ))
		{
			if (fabs( dNew ) <= 7.0) Trim.data[item - 6] = dNew;
			else return false;
		}
		else return false;
	}
	else if(item==9)
	{
		int num;
		if (GetIntegerUnsigned( Data, num ))
		{
			WT = num;
		}
		else return false;
	}
	else if(item>=10 && item<=12)
	{
		int num;
		if (GetIntegerUnsigned( Data, num ))
		{
			if (((item == 10) && (num < 365)) || ((item == 11) && (num < 24)) || ((item == 12) && (num < 60))) TIG[item - 10] = num;
			else return false;
		}
		else return false;
	}
	else if (item == 13)
	{
		if (GetDoubleUnsigned( Data, dNew ))
		{
			if (dNew < 60.0) TIG[3] = dNew;
			else return false;
		}
		else return false;
	}
	else if (item == 14)
	{
		if (GetMajorMode() == 202)
		{
			int num;
			if (GetIntegerUnsigned( Data, num ))
			{
				if (num <= 99999) C1 = num;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 15)
	{
		if (GetMajorMode() == 202)
		{
			if (GetDoubleSigned( Data, dNew ))
			{
				if(fabs(dNew)<10.0) C2=dNew;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 16)
	{
		if (GetMajorMode() == 202)
		{
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew <= 999.999) HT = dNew;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 17)
	{
		if (GetMajorMode() == 202)
		{
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew <= 540.0) ThetaT = dNew;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if(item>=19 && item<=21)
	{
		if (GetDoubleSigned( Data, dNew ))
		{
			if((item == 19 && fabs(dNew) <= 9999.9) || (item != 19 && fabs(dNew) <= 999.9)) PEG7.data[item-19]=dNew;
			else return false;
		}
		else return false;
	}
	else if(item==22)
	{
		if (strlen( Data ) == 0)
		{
			if(GetMajorMode() != 303) {
				// in OPS 1 & 3, use PEG4 targets if PEG4 values are nonzero
				// PEG 7 is always used in OPS 2
				if(GetMajorMode() != 202 && !Eq(ThetaT, 0.0, 0.001)) StartCalculatingPEG4Targets();
				else LoadManeuver();
			}
			else return false;
		}
		else return false;
	}
	else if(item==23)
	{
		if (strlen( Data ) == 0)
		{
			if(MnvrLoad) bShowTimer = true;
			else return false;
		}
		else return false;
	}
	else if(item==27)
{
		if (strlen( Data ) == 0)
		{
			if(!MnvrToBurnAtt) {
				//STS()->LoadBurnAttManeuver(BurnAtt);
				MnvrToBurnAtt = true;
				//pOrbitDAP->ManeuverToLVLHAttitude(BurnAtt);
				pOrbitDAP->ManeuverToINRTLAttitude(BurnAtt);
			}
			/*else {
				STS()->TerminateManeuver();
				MnvrToBurnAtt=false;
			}*/
		}
		else return false;
	}
	else if (item == 28)
	{
		if (strlen( Data ) == 0)
		{
			OMSGimbalActr[0] = 1;
		}
		else return false;
	}
	else if (item == 29)
	{
		if (strlen( Data ) == 0)
		{
			OMSGimbalActr[1] = 1;
		}
		else return false;
	}
	else if (item == 30)
	{
		if (strlen( Data ) == 0)
		{
			OMSGimbalActr[0] = 2;
		}
		else return false;
	}
	else if (item == 31)
	{
		if (strlen( Data ) == 0)
		{
			OMSGimbalActr[1] = 2;
		}
		else return false;
	}
	else if (item == 32)
	{
		if (strlen( Data ) == 0)
		{
			OMSGimbalActr[0] = 0;
		}
		else return false;
	}
	else if (item == 33)
	{
		if (strlen( Data ) == 0)
		{
			OMSGimbalActr[1] = 0;
		}
		else return false;
	}
	else if (item == 34)
	{
		if (strlen( Data ) == 0)
		{
			pOMSTVCCMD_SOP->SetGimbalCheckFlag();
		}
		else return false;
	}
	else return false;
	return true;
}

bool OMSBurnSoftware::ExecPressed(int spec)
{
	if(MnvrLoad && !MnvrExecute && tig-STS()->GetMET()<=15.0)
	{
		MnvrExecute=true;

		OrbitDAP::CONTROL_MODE mode = OrbitDAP::BOTH_OMS;
		if (OMS == 1) mode = OrbitDAP::LEFT_OMS;
		else if (OMS == 2) mode = OrbitDAP::RIGHT_OMS;
		pOrbitDAP->InitOMSTVC( Trim, mode );// command OMS gimbal angles to trim angles
	}
	return true;
}

void OMSBurnSoftware::OnPaint( vc::MDU* pMDU ) const
{
	int minutes, seconds;
	int TIMER[4];
	char cbuf[255];

	switch(GetMajorMode()) {
	case 104:
		PrintCommonHeader("OMS 1 MNVR EXEC", pMDU);
		break;
	case 105:
		PrintCommonHeader("OMS 2 MNVR EXEC", pMDU);
		break;
	case 106:
		PrintCommonHeader("OMS 2 MNVR COAST", pMDU);
		break;
	case 202:
		PrintCommonHeader("ORBIT MNVR EXEC", pMDU);
		break;
	case 301:
		PrintCommonHeader("DEORB MNVR COAST", pMDU);
		break;
	case 302:
		PrintCommonHeader("DEORB MNVR EXEC", pMDU);
		break;
	case 303:
		PrintCommonHeader("DEORB MNVR COAST", pMDU);
		break;
	}
	// print time to apogee/perigee
	// for OPS 3, this should be REI & TFF instead (see SCOM)
	/*if((oparam.PeT)<(oparam.ApT)) {
		minutes=(int)(oparam.PeT/60);
		seconds=(int)(oparam.PeT-(60*minutes));
		sprintf_s(cbuf, 255, "TTP %.2d:%.2d", minutes, seconds);
		pMDU->mvprint(20, 9, cbuf);
	}
	else {
		minutes=(int)(oparam.ApT/60);
		seconds=(int)(oparam.ApT-(60*minutes));
		sprintf_s(cbuf, 255, "TTA %.2d:%.2d", minutes, seconds);
		pMDU->mvprint(20, 9, cbuf);
	}*/
	if(GetMajorMode() == 303)
	{
		if (metAt400KFeet != 0.0)
		{
			double TFF = metAt400KFeet - STS()->GetMET();
			minutes=(int)(TFF/60);
			seconds=(int)(TFF-(60*minutes));
		}
		else
		{
			minutes = 0;
			seconds = 0;
		}
		sprintf_s(cbuf, 255, "TFF %.2d:%.2d", minutes, seconds);
		pMDU->mvprint(20, 9, cbuf);
	}
	else
	{
		if ((fabs( ApD - PeD ) < (5.0 * NM2M)) && (GetMajorMode() < 300))
		{
			pMDU->mvprint( 20, 9, "TTC   :" );
		}
		else if ((PeT<ApT && PeT>=STS()->GetMET()) || ((PeT > ApT) && (ApT < STS()->GetMET()))) {
			double TTP = PeT - STS()->GetMET();
			minutes=(int)(TTP/60);
			seconds=(int)(TTP-(60*minutes));
			sprintf_s(cbuf, 255, "TTP %.2d:%.2d", minutes, seconds);
			pMDU->mvprint(20, 9, cbuf);
		}
		else {
			double TTA = ApT - STS()->GetMET();
			minutes=(int)(TTA/60);
			seconds=(int)(TTA-(60*minutes));
			sprintf_s(cbuf, 255, "TTA %.2d:%.2d", minutes, seconds);
			pMDU->mvprint(20, 9, cbuf);
		}
	}

	int timeDiff=max(0, static_cast<int>(tig-STS()->GetMET()+1));
	if(bShowTimer) {
		TIMER[0]=timeDiff/86400;
		TIMER[1]=(timeDiff-TIMER[0]*86400)/3600;
		TIMER[2]=(timeDiff-TIMER[0]*86400-TIMER[1]*3600)/60;
		TIMER[3]=timeDiff-TIMER[0]*86400-TIMER[1]*3600-TIMER[2]*60;
		sprintf_s(cbuf, 255, "%03d/%02d:%02d:%02d", abs(TIMER[0]), abs(TIMER[1]), abs(TIMER[2]), abs(TIMER[3]));
		pMDU->mvprint(38, 1, cbuf);
	}

	pMDU->mvprint(1, 1, "OMS BOTH 1");
	pMDU->mvprint(8, 2, "L 2");
	pMDU->mvprint(8, 3, "R 3");
	pMDU->mvprint(1, 4, "RCS SEL  4");
	pMDU->mvprint(11, OMS+1, "*");

	sprintf_s(cbuf, 255, "5 TV ROLL %3d", TVR_ROLL );
	pMDU->mvprint(1, 5, cbuf);
	pMDU->Underline( 11, 5 );
	pMDU->Underline( 12, 5 );
	pMDU->Underline( 13, 5 );
	pMDU->mvprint(1, 6, "TRIM LOAD");
	sprintf_s(cbuf, 255, "6 P   %2.1f", fabs( Trim.data[0] ));
	pMDU->mvprint(2, 7, cbuf);
	pMDU->NumberSignBracket( 7, 7, Trim.data[0] );
	pMDU->Underline( 8, 7 );
	pMDU->Underline( 9, 7 );
	pMDU->Underline( 10, 7 );
	sprintf_s(cbuf, 255, "7 LY  %2.1f", fabs( Trim.data[1] ));
	pMDU->mvprint(2, 8, cbuf);
	pMDU->NumberSignBracket( 7, 8, Trim.data[1] );
	sprintf_s(cbuf, 255, "8 RY  %2.1f", fabs( Trim.data[2] ));
	pMDU->mvprint(2, 9, cbuf);
	pMDU->NumberSignBracket( 7, 9, Trim.data[2] );
	sprintf_s(cbuf, 255, "9 WT %6.0f", WT);
	pMDU->mvprint(1, 10, cbuf);
	pMDU->Underline( 6, 10 );
	pMDU->Underline( 7, 10 );
	pMDU->Underline( 8, 10 );
	pMDU->Underline( 9, 10 );
	pMDU->Underline( 10, 10 );
	pMDU->Underline( 11, 10 );
	pMDU->mvprint(0, 11, "10 TIG");
	sprintf_s(cbuf, 255, "%03.0f/%02.0f:%02.0f:%04.1f", TIG[0], TIG[1], TIG[2], TIG[3]);
	pMDU->mvprint(3, 12, cbuf);
	pMDU->Underline( 3, 12 );
	pMDU->Underline( 4, 12 );
	pMDU->Underline( 5, 12 );
	pMDU->Underline( 7, 12 );
	pMDU->Underline( 8, 12 );
	pMDU->Underline( 10, 12 );
	pMDU->Underline( 11, 12 );
	pMDU->Underline( 13, 12 );
	pMDU->Underline( 14, 12 );
	pMDU->Underline( 15, 12 );
	pMDU->Underline( 16, 12 );

	pMDU->mvprint(1, 13, "TGT PEG 4");
	pMDU->mvprint(2, 14, "14 C1");
	sprintf_s(cbuf, 255, "%5.0f", C1);
	pMDU->mvprint(12, 14, cbuf);
	pMDU->Underline( 12, 14 );
	pMDU->Underline( 13, 14 );
	pMDU->Underline( 14, 14 );
	pMDU->Underline( 15, 14 );
	pMDU->Underline( 16, 14 );
	pMDU->mvprint(2, 15, "15 C2");
	sprintf_s(cbuf, 255, "%6.4f", fabs( C2 ));
	pMDU->mvprint(11, 15, cbuf);
	pMDU->NumberSignBracket( 10, 15, C2 );
	pMDU->Underline( 11, 15 );
	pMDU->Underline( 12, 15 );
	pMDU->Underline( 13, 15 );
	pMDU->Underline( 14, 15 );
	pMDU->Underline( 15, 15 );
	pMDU->Underline( 16, 15 );
	pMDU->mvprint(2, 16, "16 HT");
	sprintf_s(cbuf, 255, "%7.3f", HT);
	pMDU->mvprint(10, 16, cbuf);
	pMDU->Underline( 10, 16 );
	pMDU->Underline( 11, 16 );
	pMDU->Underline( 12, 16 );
	pMDU->Underline( 13, 16 );
	pMDU->Underline( 14, 16 );
	pMDU->Underline( 15, 16 );
	pMDU->Underline( 16, 16 );
	pMDU->mvprint(2, 17, "17  T");
	pMDU->Theta(5, 17);
	sprintf_s(cbuf, 255, "%7.3f", ThetaT);
	pMDU->mvprint(10, 17, cbuf);
	pMDU->Underline( 10, 17 );
	pMDU->Underline( 11, 17 );
	pMDU->Underline( 12, 17 );
	pMDU->Underline( 13, 17 );
	pMDU->Underline( 14, 17 );
	pMDU->Underline( 15, 17 );
	pMDU->Underline( 16, 17 );
	pMDU->mvprint(2, 18, "18 PRPLT");
	sprintf_s( cbuf, 255, "%5.0f", fabs( 0.0 ) );
	pMDU->mvprint( 12, 18, cbuf );
	pMDU->NumberSignBracket( 11, 18, 0.0 );
	pMDU->Underline( 12, 18 );
	pMDU->Underline( 13, 18 );
	pMDU->Underline( 14, 18 );
	pMDU->Underline( 15, 18 );
	pMDU->Underline( 16, 18 );

	pMDU->mvprint(1, 19, "TGT PEG 7");
	pMDU->mvprint(2, 20, "19  VX");
	pMDU->mvprint(2, 21, "20  VY");
	pMDU->mvprint(2, 22, "21  VZ");
	for(int i=20;i<=22;i++) pMDU->Delta(5, i); // delta symbols for DV X/Y/Z
	if(PEG7.x!=0.0 || PEG7.y!=0.0 || PEG7.z!=0.0) {
		sprintf_s(cbuf, 255, "%6.1f", fabs( PEG7.x ));
		pMDU->mvprint(10, 20, cbuf);
		pMDU->NumberSignBracket( 9, 20, PEG7.x );
		sprintf_s(cbuf, 255, "%5.1f", fabs( PEG7.y ));
		pMDU->mvprint(11, 21, cbuf);
		pMDU->NumberSignBracket( 10, 21, PEG7.y );
		sprintf_s(cbuf, 255, "%5.1f", fabs( PEG7.z ));
		pMDU->mvprint(11, 22, cbuf);
		pMDU->NumberSignBracket( 10, 22, PEG7.z );
	}
	else
	{
		pMDU->mvprint( 14, 20, "." );
		pMDU->NumberSignBracket( 9, 20, 0.0 );
		pMDU->mvprint( 14, 21, "." );
		pMDU->NumberSignBracket( 10, 21, 0.0 );
		pMDU->mvprint( 14, 22, "." );
		pMDU->NumberSignBracket( 10, 22, 0.0 );
	}
	pMDU->Underline( 10, 20 );
	pMDU->Underline( 11, 20 );
	pMDU->Underline( 12, 20 );
	pMDU->Underline( 13, 20 );
	pMDU->Underline( 14, 20 );
	pMDU->Underline( 15, 20 );
	pMDU->Underline( 11, 21 );
	pMDU->Underline( 12, 21 );
	pMDU->Underline( 13, 21 );
	pMDU->Underline( 14, 21 );
	pMDU->Underline( 15, 21 );
	pMDU->Underline( 11, 22 );
	pMDU->Underline( 12, 22 );
	pMDU->Underline( 13, 22 );
	pMDU->Underline( 14, 22 );
	pMDU->Underline( 15, 22 );

	if(MnvrLoad || GetMajorMode()==303) {
		double tmp = BurnAtt.data[ROLL];
		if (tmp < 0) tmp += 360;
		sprintf_s(cbuf, 255, "24 R %03.0f", tmp);
		pMDU->mvprint(21, 3, cbuf);
		tmp = BurnAtt.data[PITCH];
		if (tmp < 0) tmp += 360;
		sprintf_s(cbuf, 255, "25 P %03.0f", tmp);
		pMDU->mvprint(21, 4, cbuf);
		tmp = BurnAtt.data[YAW];
		if (tmp < 0) tmp += 360;
		sprintf_s(cbuf, 255, "26 Y %03.0f", tmp);
		pMDU->mvprint(21, 5, cbuf);
	}
	else {
		pMDU->mvprint(21, 3, "24 R");
		pMDU->mvprint(21, 4, "25 P");
		pMDU->mvprint(21, 5, "26 Y");
	}
	pMDU->Underline( 26, 3 );
	pMDU->Underline( 27, 3 );
	pMDU->Underline( 28, 3 );

	if(MnvrLoad) {
		pMDU->mvprint(1, 23, "LOAD 22/TIMER 23");

		unsigned int majorMode = GetMajorMode();
		if(majorMode == 104 || majorMode == 105 || majorMode == 202 || majorMode == 302) {
			if(!MnvrExecute && timeDiff<=15.0) pMDU->mvprint(46, 2, "EXEC", dps::DEUATT_FLASHING + dps::DEUATT_OVERBRIGHT );
		}
	}
	else pMDU->mvprint(6, 23, "22/TIMER 23");

	OrbitDAP::DAP_CONTROL_MODE dapMode = pOrbitDAP->GetDAPMode();

	pMDU->mvprint(20, 2, "BURN ATT");
	pMDU->mvprint( 21, 7, "TTG" );
	if(!MnvrToBurnAtt) pMDU->mvprint(20, 6, "MNVR 27");
	else
	{
		pMDU->mvprint(20, 6, "MNVR 27*");
		double ttg;
		if ((dapMode == OrbitDAP::AUTO) && (BurnInProg == false) && (BurnCompleted == false) && (pOrbitDAP->GetTimeToAttitude( ttg ) == true))
		{
			char att = 0;
			if ((ttg > (timeDiff - 30)) || (((GetMajorMode() / 100) == 2) && (ttg > 3599))) att = dps::DEUATT_OVERBRIGHT;

			sprintf_s( cbuf, 255, "%02d:%02d", (int)ttg / 60, (int)ttg % 60 );
			pMDU->mvprint( 25, 7, cbuf, att );
		}
	}
	// display selected DAP mode
	std::string text;
	switch(dapMode) {
	case OrbitDAP::AUTO:
		text = "AUTO";
		break;
	case OrbitDAP::INRTL:
		text = "INRTL";
		break;
	case OrbitDAP::LVLH:
		text = "LVLH";
		break;
	case OrbitDAP::FREE:
		text = "FREE";
		break;
	}
	if(MnvrToBurnAtt && dapMode != OrbitDAP::AUTO) pMDU->mvprint(29, 6, text.c_str(), dps::DEUATT_OVERBRIGHT);
	else pMDU->mvprint(29, 6, text.c_str());


	pMDU->mvprint(20, 8, "REI");
	pMDU->mvprint(25, 10, "GMBL");
	pMDU->mvprint(24, 11, "L");
	pMDU->mvprint(30, 11, "R");
	pMDU->mvprint( 20, 12, "P" );
	pMDU->mvprint( 20, 13, "Y" );

	double pitch = 0.0;
	double yaw = 0.0;
	if (pOMSTVCFDBK_SOP->GetActrPos( 0, pitch, yaw ))
	{
		sprintf_s( cbuf, 255, "%+02.1f", pitch );
		pMDU->mvprint( 22, 12, cbuf );

		sprintf_s( cbuf, 255, "%+02.1f", yaw );
		pMDU->mvprint( 22, 13, cbuf );
	}

	pitch = 0.0;
	yaw = 0.0;
	if (pOMSTVCFDBK_SOP->GetActrPos( 1, pitch, yaw ))
	{
		sprintf_s( cbuf, 255, "%+02.1f", pitch );
		pMDU->mvprint( 28, 12, cbuf );

		sprintf_s( cbuf, 255, "%+02.1f", yaw );
		pMDU->mvprint( 28, 13, cbuf );
	}

	pMDU->mvprint(20, 15, "PRI 28   29");
	pMDU->mvprint(20, 16, "SEC 30   31");
	pMDU->mvprint(20, 17, "OFF 32   33");
	int y = 17;
	if (OMSGimbalActr[0] == 1) y = 15;
	else if (OMSGimbalActr[0] == 2) y = 16;
	pMDU->mvprint( 26, y, "*");

	y = 17;
	if (OMSGimbalActr[1] == 1) y = 15;
	else if (OMSGimbalActr[1] == 2) y = 16;
	pMDU->mvprint( 31, y, "*");

	pMDU->mvprint(20, 19, "GMBL CK  34");
	if (pOMSTVCCMD_SOP->GetGimbalCheckFlag()) pMDU->mvprint( 31, 19, "*" );

	pMDU->Line( 180, 14, 180, 336 );
	pMDU->Line( 350, 28, 350, 182 );
	pMDU->Line( 350, 182, 500, 182 );

	pMDU->Delta( 36, 3 );
	pMDU->mvprint( 37, 3, "VTOT" );
	pMDU->mvprint( 36, 4, "TGO" );
	pMDU->mvprint( 36, 6, "VGO X" );
	pMDU->mvprint( 40, 7, "Y" );
	pMDU->mvprint( 40, 8, "Z" );

	if (MnvrLoad)
	{
		int TGO[2];
		sprintf_s(cbuf, 255, "%6.2f", DeltaVTot);
		pMDU->mvprint(44, 3, cbuf);

		if (!BurnInProg && !BurnCompleted)
		{
			TGO[0]=(int)(BurnTime/60);
			TGO[1]=(int)(BurnTime-(TGO[0]*60));

			sprintf_s(cbuf, 255, "%2d:%.2d", TGO[0], TGO[1]);
			pMDU->mvprint(45, 4, cbuf);
		}
		else if (!BurnCompleted)
		{
			double btRemaining=IgnitionTime+BurnTime-STS()->GetMET();
			TGO[0]=max(0, (int)btRemaining/60);
			TGO[1]=max(0, (int)btRemaining%60);

			sprintf_s(cbuf, 255, "%2d:%.2d", TGO[0], TGO[1]);
			pMDU->mvprint(45, 4, cbuf);
		}
		else pMDU->mvprint( 46, 4, "0:00" );

		sprintf_s(cbuf, 255, "%7.2f", fabs( VGO.x ));
		pMDU->mvprint(43, 6, cbuf);
		pMDU->NumberSign( 42, 6, VGO.x );
		sprintf_s(cbuf, 255, "%6.2f", fabs( VGO.y ));
		pMDU->mvprint(44, 7, cbuf);
		pMDU->NumberSign( 43, 7, VGO.y );
		sprintf_s(cbuf, 255, "%6.2f", fabs( VGO.z ));
		pMDU->mvprint(44, 8, cbuf);
		pMDU->NumberSign( 43, 8, VGO.z );
	}

	pMDU->mvprint(41, 10, "HA    HP");
	double earthRadius = oapiGetSize(STS()->GetGravityRef());
	if(MnvrLoad && !Eq(tgtApD, 0.0)) {
		double _ap = (tgtApD-earthRadius) / NM2M;
		double _pe = (tgtPeD-earthRadius) / NM2M;
		unsigned short ap = min(999, Round( _ap ));
		unsigned short pe = min(999, abs( Round( _pe ) ));
		sprintf_s(cbuf, 255, "TGT %3hu    %3hu", ap, pe );
		pMDU->mvprint(36, 11, cbuf);
		pMDU->NumberSign( 46, 11, _pe );
	}
	else {
		pMDU->mvprint(36, 11, "TGT");
	}

	{
		double _ap = (ApD-earthRadius) / NM2M;
		double _pe = (PeD-earthRadius) / NM2M;
		unsigned short ap = min(999, Round( _ap ));
		unsigned short pe = min(999, abs( Round( _pe ) ));
		sprintf_s(cbuf, 255, "CUR %3hu    %3hu", ap, pe );
		pMDU->mvprint(36, 12, cbuf);
		pMDU->NumberSign( 46, 12, _pe );
	}

	pMDU->mvprint(35, 15, "35 ABORT TGT");
	pMDU->Underline( 48, 15 );
	pMDU->Underline( 49, 15 );

	pMDU->mvprint( 37, 17, "FWD RCS" );
	pMDU->mvprint( 39, 18, "ARM   36" );
	pMDU->mvprint( 39, 19, "DUMP  37" );
	pMDU->mvprint( 39, 20, "OFF   38" );

	pMDU->mvprint( 37, 21, "SURF DRIVE" );
	pMDU->mvprint( 39, 22, "ON    39" );
	pMDU->mvprint( 39, 23, "OFF   40" );

	return;
}

bool OMSBurnSoftware::OnParseLine(const char* keyword, const char* value)
{
	if(!_strnicmp(keyword, "OMS", 3)) {
		sscanf_s(value, "%d", &OMS);
		return true;
	}
	else if(!_strnicmp(keyword, "PEG7", 4)) {
		sscanf_s(value, "%lf%lf%lf", &PEG7.x, &PEG7.y, &PEG7.z);
		return true;
	}
	else if(!_strnicmp(keyword, "PEG4", 4)) {
		sscanf_s(value, "%lf%lf%lf%lf", &C1, &C2, &HT, &ThetaT);
		return true;
	}
	else if(!_strnicmp(keyword, "Trim", 4)) {
		sscanf_s(value, "%lf%lf%lf", &Trim.x, &Trim.y, &Trim.z);
		return true;
	}
	else if(!_strnicmp(keyword, "BURN_ATT", 8)) {
		sscanf_s(value, "%lf%lf%lf", &BurnAtt.x, &BurnAtt.y, &BurnAtt.z);
		return true;
	}
	else if(!_strnicmp(keyword, "WT", 2)) {
		sscanf_s(value, "%lf", &WT);
		return true;
	}
	else if(!_strnicmp(keyword, "TIG", 3)) {
		sscanf_s(value, "%lf%lf%lf%lf", &TIG[0], &TIG[1], &TIG[2], &TIG[3]);
		return true;
	}
	else if(!_strnicmp(keyword, "TV_ROLL", 7)) {
		sscanf_s(value, "%d", &TVR_ROLL);
		return true;
	}
	else if(!_strnicmp(keyword, "MNVR", 4)) {
		int ml = 0;
		int mb = 0;
		int bc = 0;
		sscanf_s(value, "%d %d %d", &ml, &mb, &bc );
		MnvrLoad = (ml != 0);
		MnvrToBurnAtt = (mb != 0);
		BurnCompleted = (bc != 0);
		return true;
	}
	else if(!_strnicmp(keyword, "TIMER", 5)) {
		bShowTimer = true;
		return true;
	}
	return false;
}

void OMSBurnSoftware::OnSaveState(FILEHANDLE scn) const
{
	char cbuf[255];
	oapiWriteScenario_int(scn, "OMS", OMS);
	oapiWriteScenario_vec(scn, "PEG7", PEG7);
	if(GetMajorMode() != 202 && !Eq(ThetaT, 0.0, 0.001)) { // save PEG4 targets
		sprintf_s(cbuf, 255, "%f %f %f %f", C1, C2, HT, ThetaT);
		oapiWriteScenario_string(scn, "PEG4", cbuf);
	}
	oapiWriteScenario_vec(scn, "Trim", Trim);
	oapiWriteScenario_vec(scn, "BURN_ATT", BurnAtt);
	oapiWriteScenario_float(scn, "WT", WT);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", TIG[0], TIG[1], TIG[2], TIG[3]);
	oapiWriteScenario_string(scn, "TIG", cbuf);
	oapiWriteScenario_int(scn, "TV_ROLL", TVR_ROLL);
	sprintf_s(cbuf, 255, "%d %d %d", MnvrLoad, MnvrToBurnAtt, BurnCompleted);
	oapiWriteScenario_string(scn, "MNVR", cbuf);
	if(bShowTimer) oapiWriteScenario_string(scn, "TIMER", "");
}

void OMSBurnSoftware::SetManeuverData(double maneuverTIG, const VECTOR3& maneuverDV)
{
	ConvertSecondsToDDHHMMSS(maneuverTIG, TIG);
	PEG7 = maneuverDV*MPS2FPS;
}

void OMSBurnSoftware::StartBurn()
{
	BurnInProg=true;
	IgnitionTime=STS()->GetMET();
	//ignite engines
	if(OMS==0) {
		omsEngineCommand[0].SetLine();
		omsEngineCommand[1].SetLine();
		pOrbitDAP->UseOMSTVC( OrbitDAP::BOTH_OMS );
	}
	else if(OMS==1) {
		omsEngineCommand[0].SetLine();
		pOrbitDAP->UseOMSTVC( OrbitDAP::LEFT_OMS );
	}
	else if(OMS==2) {
		omsEngineCommand[1].SetLine();
		pOrbitDAP->UseOMSTVC( OrbitDAP::RIGHT_OMS );
	}
}

void OMSBurnSoftware::TerminateBurn()
{
	omsEngineCommand[0].ResetLine();
	omsEngineCommand[1].ResetLine();
	BurnCompleted=true;
	BurnInProg=false;
	pOrbitDAP->UseRCS();

	// save trims
	if (OMS == 0)
	{
		double Lp = 0.0;
		double Ly = 0.0;
		double Rp = 0.0;
		double Ry = 0.0;
		pOMSTVCFDBK_SOP->GetActrPos( 0, Lp, Ly );
		pOMSTVCFDBK_SOP->GetActrPos( 1, Rp, Ry );
		Trim.data[0] = (Rp + Lp) * 0.5;// HACK no clue how to handle this one
		Trim.data[1] = Ly;
		Trim.data[2] = Ry;
	}
	else if (OMS == 1)
	{
		double Lp = 0.0;
		double Ly = 0.0;
		pOMSTVCFDBK_SOP->GetActrPos( 0, Lp, Ly );
		Trim.data[0] = Lp;
		Trim.data[1] = Ly;
	}
	else if (OMS == 2)
	{
		double Rp = 0.0;
		double Ry = 0.0;
		pOMSTVCFDBK_SOP->GetActrPos( 1, Rp, Ry );
		Trim.data[0] = Rp;
		Trim.data[2] = Ry;
	}
	//pStateVector->UpdatePropagatorStateVectors();
	//UpdateOrbitData();
	//lastUpdateSimTime = SimT; // force elements to be updated
}

void OMSBurnSoftware::StartCalculatingPEG4Targets()
{
	bCalculatingPEG4Burn = true;
	VECTOR3 initialPos, initialVel;
	pStateVector->GetPropagatedStateVectors(ConvertDDHHMMSSToSeconds(TIG), initialPos, initialVel);

	// calculate acceleration
	// assume single-OMS or 2-OMS burn (no RCS burns) for the moment
	double StartWeight = WT*LBM2KG;
	double thrust = OMS_THRUST;
	if(OMS == 0) thrust = OMS_THRUST*2;
	double acceleration = thrust/StartWeight;

	// for OPS 1 (OMS-1/2) burns, ThetaT value used in calculations (angle from TIG position to target point) is different from ThetaT entered on display (angle from launch site to target point)
	double correctedThetaT = ThetaT*RAD;
	if(GetMajorMode() < 200) {
		VECTOR3 launchSitePos = pStateVector->GetPositionAtT0();
		//double angleToLaunchSite = acos(dotp(launchSitePos/length(launchSitePos), initialPos/length(initialPos)));
		double angleToLaunchSite = SignedAngle(launchSitePos, initialPos, crossp(initialPos, initialVel));
		if(angleToLaunchSite < 0) angleToLaunchSite += PI2;
		correctedThetaT -= angleToLaunchSite;
	}

	peg4Targeting.SetPEG4Targets(C1/MPS2FPS, C2, HT * NM2M, correctedThetaT, initialPos, initialVel, acceleration);

	oapiWriteLogV( "PEG4 Initial state: %f %f %f %f %f %f", initialPos.x, initialPos.y, initialPos.z, initialVel.x, initialVel.y, initialVel.z );
}

void OMSBurnSoftware::LoadManeuver(bool calculateBurnAtt)
{
	int i;
	double StartWeight, EndWeight, /*EndWeightLast=0.0,*/ FuelRate, ThrustFactor=1.0;
	//VECTOR3 ThrustVector;
	MnvrLoad=true;
	tig = ConvertDDHHMMSSToSeconds(TIG);

	//dV
	for(i=0;i<3;i++) {
		DeltaV.data[i]=PEG7.data[i] * FPS2MS;
	}
	DeltaVTot=length(PEG7);
	double DeltaVTotms=length(DeltaV);

	VECTOR3 ThrustDir; //direction of net thrust (in Orbiter frame)
	if(OMS==0) {
		VECTOR3 temp1, temp2;
		temp1 = CalcOMSThrustDir(0, Trim.data[0], Trim.data[1]);
		temp2 = CalcOMSThrustDir(1, Trim.data[0], Trim.data[2]);
		ThrustDir=temp1+temp2;
		ThrustFactor=length(ThrustDir); //get thrust produced by engines
		ThrustDir=ThrustDir/ThrustFactor; //normalize vector
	}
	else if(OMS==1 || OMS==2) {
		ThrustDir = CalcOMSThrustDir(OMS-1, Trim.data[0], Trim.data[OMS]);
	}
	else {
		ThrustDir=_V(0.0, 0.0, 1.0); //+X RCS
	}

	//use rocket equation (TODO: Check math/formulas here)
	// NOTE: assume vacuum ISP and 1.0 efficiency for tank
	StartWeight=WT * LBM2KG;
	EndWeight=StartWeight/exp(DeltaVTotms/OMS_ISP0);
	FuelRate=OMS_THRUST/OMS_ISP0;
	FuelRate*=ThrustFactor; //if two-engine burn, compensate for # of engines; TODO: Make sure this is valid; we're calculating fuel, not thrust (SiameseCat)
	BurnTime=(StartWeight-EndWeight)/FuelRate;
	VGO.x=DeltaVTot*ThrustDir.z;
	VGO.y=DeltaVTot*ThrustDir.x;
	VGO.z=-DeltaVTot*ThrustDir.y;

	// setup propagator to calculate apogee/perigee at end of burn
	VECTOR3 equPos, equVel;
	pStateVector->GetPropagatedStateVectors(tig, equPos, equVel);
	VECTOR3 equDeltaV = tmul(GetGlobalToLVLHMatrix(equPos, equVel), DeltaV); // calculate DV in equatorial (inertial) frame
	double acceleration = (OMS_THRUST*ThrustFactor)/StartWeight;
	omsBurnPropagator.SetBurnData(tig, equDeltaV, acceleration);
	propagator.DefinePerturbations(&omsBurnPropagator);
	UpdateBurnPropagator();
	//tgtApD = tgtPeD = 0.0;
	// get initial value for target apogee/perigee by ignoring perturbations and assuming instantaneous burn
	kostStateVector postBurnState;
	kostElements elements;
	kostOrbitParam params;
	postBurnState.pos = ConvertBetweenLHAndRHFrames(equPos);
	postBurnState.vel = ConvertBetweenLHAndRHFrames(equVel + equDeltaV);
	double mu = GGRAV*(oapiGetMass(hEarth) + StartWeight);
	kostStateVector2Elements(mu, &postBurnState, &elements, &params);
	tgtApD = params.ApD;
	tgtPeD = params.PeD;

	if(calculateBurnAtt) {
		// calculate LVLH burn attitude
		MATRIX3 ThrustToBodyMatrix = Transpose(GetRotationMatrix(_V(ThrustDir.z, ThrustDir.x, -ThrustDir.y), 0.0));
		VECTOR3 DeltaVDir = PEG7/length(PEG7);
		MATRIX3 LVLHToDeltaVMatrix = GetRotationMatrix(DeltaVDir, RAD*TVR_ROLL);
		MATRIX3 LVLHToBurnAttMatrix = mul(LVLHToDeltaVMatrix, ThrustToBodyMatrix);

		// convert LVLH angles to inertial angles at TIG
		VECTOR3 rhEquPos = ConvertBetweenLHAndRHFrames(equPos);
		VECTOR3 rhEquVel = ConvertBetweenLHAndRHFrames(equVel);
		//MATRIX3 M50Matrix=ConvertLVLHAnglesToM50Matrix(radLVLHBurnAtt, eclPos, eclVel);
		BurnAtt = ConvertLVLHMatrixToM50Angles(LVLHToBurnAttMatrix, rhEquPos, rhEquVel)*DEG;
	}
}

void OMSBurnSoftware::CalculateEIMinus5Att(VECTOR3& degAtt) const
{
	double metAtEI = pStateVector->GetMETAtAltitude(EI_ALT);
	//VECTOR3 EIPos, EIVel, EIEclPos, EIEclVel;
	VECTOR3 EIPos, EIVel;
	pStateVector->GetPropagatedStateVectors(metAtEI-300.0, EIPos, EIVel);
	EIPos = ConvertBetweenLHAndRHFrames(EIPos);
	EIVel = ConvertBetweenLHAndRHFrames(EIVel);
	// TODO: move this into separate function
	//ConvertEquToEcl(STS()->GetGravityRef(), EIPos, EIVel, EIEclPos, EIEclVel);
	const MATRIX3 EI_ATT = GetRotationMatrixYZX(_V(0.0, 40.0*RAD, 0.0));
	//MATRIX3 M50Matrix=ConvertLVLHAnglesToM50Matrix(EI_ATT, EIEclPos, EIEclVel);
	//degAtt = GetYZXAnglesFromMatrix(M50Matrix)*DEG;
	degAtt = ConvertLVLHMatrixToM50Angles(EI_ATT, EIPos, EIVel)*DEG;
}

void OMSBurnSoftware::UpdateOrbitData()
{
	if(GetMajorMode() == 303) metAt400KFeet = pStateVector->GetMETAtAltitude(EI_ALT);
	else {
		pStateVector->GetApogeeData(ApD, ApT);
		pStateVector->GetPerigeeData(PeD, PeT);
	}
	if(MnvrLoad && !(BurnInProg || BurnCompleted)) {
		double tgtApT, tgtPeT;
		//propagator.GetApogeeData(STS()->GetMET(), tgtApD, tgtApT);
		//propagator.GetPerigeeData(STS()->GetMET(), tgtPeD, tgtPeT);
		propagator.GetApogeeData(tig+1000.0, tgtApD, tgtApT);
		propagator.GetPerigeeData(tig+1000.0, tgtPeD, tgtPeT);
		oapiWriteLogV( "MET: %f Tgt ApD: %f PeD: %f", STS()->GetMET(), tgtApD, tgtPeD );
	}
}

void OMSBurnSoftware::UpdateBurnPropagator()
{
	VECTOR3 pos, vel;
	pStateVector->GetPropagatedStateVectors(tig, pos, vel);

	propagator.UpdateVesselMass(STS()->GetMass());
	propagator.UpdateStateVector(pos, vel, tig);
}

VECTOR3 OMSBurnSoftware::GetAttitudeCommandErrors() const
{
	if ((BurnInProg == false) || (OMS != 3)) return pOrbitDAP->GetAttitudeErrors(); // OMS || no burn
	else return VGO;// RCS
}

unsigned int OMSBurnSoftware::GetOMSGimbalActrSel( unsigned int eng ) const
{
	assert( (eng < 2) && "OMSBurnSoftware::GetOMSGimbalActrSel.eng" );
	return OMSGimbalActr[eng];
}
};
