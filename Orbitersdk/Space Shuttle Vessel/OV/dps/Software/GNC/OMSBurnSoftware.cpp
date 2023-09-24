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
2022/09/29   GLS
2022/11/11   indy91
2022/12/13   GLS
2022/12/21   indy91
2022/12/23   GLS
2022/12/28   indy91
2022/12/28   GLS
2022/12/29   GLS
2023/01/01   GLS
2023/01/10   GLS
2023/02/08   indy91
2023/02/10   indy91
2023/02/16   indy91
2023/02/25   indy91
2023/04/16   GLS
2023/05/27   GLS
2023/09/24   GLS
********************************************/
#include "OMSBurnSoftware.h"
#include "OrbitDAP.h"
#include "../../../Atlantis.h"
#include "../../../ParameterValues.h"
#include <MathSSV.h>
#include "../../IDP.h"
#include "../../../vc/MDU.h"
#include "StateVectorSoftware.h"
#include "GNCUtilities.h"
#include <EngConst.h>


namespace dps
{
	//Burn enable window (sec)
	const double BURN_ENABLE_WINDOW = -15.0;
	//Tolerance on burn attitude
	const float CBETA_EPS = 0.999848f;
	//Maximum difference in apogee and perigee for orbit to be considered circular (NM)
	const float DELT_H_CIRC = 5.0f;
	//Maximum time step in extrapolation to entry interface (s)
	const float DT_EI = 600.0f;
	//Time interval step size (s)
	const float DT_RNG = 2.0f;
	//Convergence tolerance for entry interface (ft)
	const float EPS_H_MISS = 50.0f;
	//Vacuum thrust of two OMS, one OMS and primary RCS jets (lbf)
	const float FT[3] = { 1.2174e4f, 6.087e3f, 3.509e3f }; //TBD: This is only used in OPS3, OPS2 value would be 1.78e3
	//Maximum perigee height for which range to landing site is calculated (NM)
	const float HP_MAX = 55.0f;
	//Entry interface altitude (ft)
	const float H_TARGET = 400000.0f;
	//Maximum number of cycles in range to LS task
	const int MAX_RNG = 10;
	//Maximum number of iterations allowed for PEG convergence for initial MNVR DIP
	const int NMAX_DIP = 10;
	//OMS engine pitch trim angle to thrust through CG (DEG)
	float ONE_ENG_OMS_PITCH_TRIM = -0.1f; //TBD: This is only used in OPS2, OPS1 value would be +0.4, OPS3 value -0.31
	//OMS engine yaw trim angle to thrust through CG (DEG)
	float ONE_ENG_OMS_YAW_TRIM[2] = { 5.21f, -5.21f };
	//Constant OMS engine electrical pitch trim angle (RAD)
	const float PITCH_BIAS = 2.76053e-1f;
	//Radial velocity boundary used in determining a time step for extrapolation to EI (ft/s)
	const float R_DOT_MAX = -100.0f;
	//RCS thrust direction
	const VECTOR3 THRUST_BODY_RCS_X = _V(0.9848078, 0.0, 0.1736482);
	//Exhaust velocity of of two OMS, one OMS and primary RCS jets (ft/s)
	const float VEX[3] = { 1.01368e4f, 1.01368e4f, 8.2327e3f };
	//Constant OMS engine electrical yaw trim angle (RAD)
	const float YAW_BIAS = 1.13446e-1f;

	//Minimum time-to-go to command thrust terminate (sec)
	const float TGO_MIN = 6.0f;
	//OMS cutoff time bias (sec)
	const float TCO_BIAS = 0.0f; //TBD: Should be 0.398

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
MnvrLoad(false), EXEC_CMD(false), MnvrToBurnAtt(false),
ST_CRT_TIMER(false), AlternatePass(true), bBurnMode(false),
bCalculatingPEG4Burn(false),
lastUpdateSimTime(-100.0),
pOrbitDAP(NULL), pStateVector(NULL)
{
	TIG[0]=TIG[1]=TIG[2]=TIG[3]=0.0;
	OMS = 0;
	EXT_DV_LVLH = _V(0.0, 0.0, 0.0);
	VGO_LVLH = _V(0.0, 0.0, 0.0);
	Trim = _V(0.4, -5.7, 5.7); //K-loaded
	TGO = 0.0;
	C1_DISP = 0.0;
	C2_DISP = 0.0;
	HTGT_DISP = 0.0;
	THETA_DISP = 0.0;
	REI_LS = 0.0;
	MNVR_TITLE_IND = 11; //MM202
	BurnAtt = _V(0, 0, 0);
	VGO = _V(0, 0, 0);
	VGO_DISP = _V(0.0, 0.0, 0.0);
	DV_TOT = 0.0;
	PROP_DEP = 0.0f;

	TXX_FLAG = 4;
	TXX = -1.0;
	X_FLAG = true;
	PEG_MODE_4 = false;

	CUR_HA = CUR_HP = TGT_HA = TGT_HP = 0.0;
	PROP_FLAG = PROP_FLAG_GUID = PROP_FLAG_OFS = PROP_FLAG_OFS_P = 0;
	SSTEER = true;

	SCO = false;
	T_CUTOFF = 0.0;
	RGD = VGD = _V(0.0, 0.0, 0.0);
	TGD = 0.0;
	VS = VSP = _V(0.0, 0.0, 0.0);

	T_GMT = 0.0;

	// I-LOADs init
	TVR_ROLL = 180;

	//OMS-1
	HTGT_OMS[0] = 729134.0f; //120 NM
	THETA_OMS[0] = 2.32129f; //133°
	C1_OMS[0] = 0.0f;
	C2_OMS[0] = 0.0f;
	DTIG_OMS[0] = 102.0f; //2 mins since MECO

	//OMS-2
	HTGT_OMS[1] = 674449.0f; //111 NM
	THETA_OMS[1] = 5.49779f; //315°
	C1_OMS[1] = 0.0f;
	C2_OMS[1] = 0.0f;
	DTIG_OMS[1] = 1740.0f; //29 mins since ET sep

	//ATO or AOA
	HTGT_OMS[2] = 0.0f;
	THETA_OMS[2] = 0.0f;
	C1_OMS[2] = 0.0f;
	C2_OMS[2] = 0.0f;
	DTIG_OMS[2] = 0.0f;
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
	pGNCUtilities = dynamic_cast<GNCUtilities*>(FindSoftware("GNCUtilities"));
	assert((pGNCUtilities != NULL) && "OMSBurnSoftware::Realize.pGNCUtilities");

	peg4Targeting.SetPlanetParameters(EARTH_MU);

	if(MnvrLoad) {
		tig = ConvertDDHHMMSSToSeconds(TIG) + ReadCOMPOOL_SD(SCP_T_MET_REF);
		if(MnvrToBurnAtt) pOrbitDAP->ManeuverToINRTLAttitude(BurnAtt);
	}
}

void OMSBurnSoftware::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	GetValILOAD("TVR_ROLL", ILOADs, TVR_ROLL);
	GetValILOAD("DTIG_OMS", ILOADs, 2, DTIG_OMS);
	GetValILOAD("HTGT_OMS", ILOADs, 2, HTGT_OMS);
	GetValILOAD("THETA_OMS", ILOADs, 2, THETA_OMS);
	GetValILOAD("C1_OMS", ILOADs, 2, C1_OMS);
	GetValILOAD("C2_OMS", ILOADs, 2, C2_OMS);
	return;
}

void OMSBurnSoftware::OnPreStep(double simt, double simdt, double mjd)
{
	T_GMT = ReadClock(); //This is used often enough to warrent updating it every timestep

	// EXEC key processing
	if ((ReadCOMPOOL_IS( SCP_EXEC_KEY ) == 1) && bBurnMode && MnvrLoad && !EXEC_CMD && ((T_GMT - tig) >= BURN_ENABLE_WINDOW))
	{
		EXEC_CMD = true;

		OrbitDAP::CONTROL_MODE mode = OrbitDAP::BOTH_OMS;
		if (OMS == 1) mode = OrbitDAP::LEFT_OMS;
		else if (OMS == 2) mode = OrbitDAP::RIGHT_OMS;
		pOrbitDAP->InitOMSTVC(Trim, mode);// command OMS gimbal angles to trim angles
	}

	if((simt-lastUpdateSimTime) > 0.96)
	{
		//Guidance
		if (bBurnMode && MnvrLoad && T_GMT - tig >= BURN_ENABLE_WINDOW)
		{
			ON_ORB_GUID_SEQ();
		}

		//Display
		if (bBurnMode && MnvrLoad) VGO_DISP_TSK();
		if (AlternatePass) CUR_ORBIT_TSK();
		AlternatePass = !AlternatePass;
		lastUpdateSimTime = simt;
	}

	if(bCalculatingPEG4Burn) {
		if(peg4Targeting.PEG_TSK()) {
			bCalculatingPEG4Burn = false;
			if(peg4Targeting.Converged()) {
				VGO = peg4Targeting.GetDeltaV();
				PRE_MAN_DISP_SUPT_TSK2();
			}
		}
	}

	if (!bBurnMode) return; // make sure we are in MM which allows burns
	if(!MnvrLoad || T_GMT < tig) return; // no burn to perform, or we haven't reached TIG yet

	// update VGO values. TBD: This should be in an IMU class
	// we need to update global (orbitersim frame) VGO, then convert VGOs to shuttle body coordinates for display
	VECTOR3 ThrustVector;
	if(STS()->GetThrustVector(ThrustVector)) {
		MATRIX3 LocalToGlobal;
		STS()->GetRotationMatrix(LocalToGlobal);
		VECTOR3 GlobalThrust = mul(LocalToGlobal, ThrustVector);
		GlobalThrust = mul(M_J2000_to_M50, _V(GlobalThrust.x, GlobalThrust.z, GlobalThrust.y));
		VS += (GlobalThrust / STS()->GetMass())*simdt*MPS2FPS;
	}

	if(OMS != 4) { // start/stop OMS engines
		if(BurnInProg && EXEC_CMD) // check if engines should be shut down
		{
			if (SCO && T_GMT >= T_CUTOFF) TerminateBurn();
		}
		else if(!BurnInProg && !BurnCompleted && EXEC_CMD) // check if burn should start
		{
			StartBurn();
		}
	}
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
		//Update mass on mode transition and scenario load for now
		WT_DISP = (float)(STS()->GetMass()*KG2LBM);
		M = WT_DISP / G_2_FPS2;

		//Set a flag to show if the major mode allows burns
		if (newMajorMode == 106 || newMajorMode == 301 || newMajorMode == 303)
		{
			bBurnMode = false;
		}
		else
		{
			bBurnMode = true;
		}

		if (GetMajorMode() != 0)
		{
			//Actual mode transitions

			//TBD: This should happen at guidance initiate before a burn
			VS = VSP = _V(0.0, 0.0, 0.0);

			//OPS1
			if (newMajorMode == 104 || newMajorMode == 105 || newMajorMode == 106)
			{
				OPS1_INIT(newMajorMode);
			}
			//OPS2
			else if (newMajorMode == 202)
			{
				OPS2_INIT();
			}
			//OPS3
			else
			{
				OPS3_INIT(newMajorMode);
			}
		}

		return true;
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
			WT_DISP = (float)num;
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
		if (GetMajorMode() != 202)
		{
			int num;
			if (GetIntegerUnsigned( Data, num ))
			{
				if (num <= 99999)
				{
					C1_DISP = num;
					VGO_LVLH = _V(0, 0, 0);
					PEG_MODE_4 = true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 15)
	{
		if (GetMajorMode() != 202)
		{
			if (GetDoubleSigned( Data, dNew ))
			{
				if (fabs(dNew) < 10.0)
				{
					C2_DISP = dNew;
					VGO_LVLH = _V(0, 0, 0);
					PEG_MODE_4 = true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 16)
	{
		if (GetMajorMode() != 202)
		{
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew <= 999.999)
				{
					HTGT_DISP = dNew;
					VGO_LVLH = _V(0, 0, 0);
					PEG_MODE_4 = true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 17)
	{
		if (GetMajorMode() != 202)
		{
			if (GetDoubleUnsigned( Data, dNew ))
			{
				if (dNew <= 540.0)
				{
					THETA_DISP = dNew;
					VGO_LVLH = _V(0, 0, 0);
					PEG_MODE_4 = true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (item == 18)
	{
		if (GetMajorMode() == 301 || GetMajorMode() == 302)
		{
			if (GetDoubleSigned(Data, dNew))
			{
				if (abs(dNew) <= 99999.0)
				{
					PROP_DEP = (float)dNew;
					VGO_LVLH = _V(0, 0, 0);
					PEG_MODE_4 = true;
				}
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
			if ((item == 19 && fabs(dNew) <= 9999.9) || (item != 19 && fabs(dNew) <= 999.9))
			{
				EXT_DV_LVLH.data[item - 19] = dNew;
				PEG_MODE_4 = false;
			}
			else return false;
		}
		else return false;
	}
	else if(item==22)
	{
		if (strlen( Data ) == 0)
		{
			if(GetMajorMode() != 303) {
				if (PRE_MAN_DISP_SUPT_TSK1())
				{
					return false;
				}
			}
			else return false;
		}
		else return false;
	}
	else if(item==23)
	{
		if (strlen( Data ) == 0)
		{
			if(MnvrLoad) ST_CRT_TIMER = true;
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
			WriteCOMPOOL_IS( SCP_OMSL_ACT_SEL, 0 );
			WriteCOMPOOL_IS( SCP_ZAP_CMD, 1 );
		}
		else return false;
	}
	else if (item == 29)
	{
		if (strlen( Data ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMSR_ACT_SEL, 0 );
			WriteCOMPOOL_IS( SCP_ZAP_CMD, 1 );
		}
		else return false;
	}
	else if (item == 30)
	{
		if (strlen( Data ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMSL_ACT_SEL, 1 );
			WriteCOMPOOL_IS( SCP_ZAP_CMD, 1 );
		}
		else return false;
	}
	else if (item == 31)
	{
		if (strlen( Data ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMSR_ACT_SEL, 1 );
			WriteCOMPOOL_IS( SCP_ZAP_CMD, 1 );
		}
		else return false;
	}
	else if (item == 32)
	{
		if (strlen( Data ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMSL_ACT_SEL, 2 );
		}
		else return false;
	}
	else if (item == 33)
	{
		if (strlen( Data ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMSR_ACT_SEL, 2 );
		}
		else return false;
	}
	else if (item == 34)
	{
		if (strlen( Data ) == 0)
		{
			WriteCOMPOOL_IS( SCP_OMS_CK_ENA_CMD, 1 );
		}
		else return false;
	}
	else return false;
	return true;
}

void OMSBurnSoftware::OnPaint( vc::MDU* pMDU ) const
{
	int minutes, seconds;
	int TIMER[4];
	char cbuf[255];

	switch(MNVR_TITLE_IND) {
	case 1:
		PrintCommonHeader("OMS 1 MNVR EXEC", pMDU);
		break;
	case 2:
		PrintCommonHeader("ATO 1 MNVR EXEC", pMDU);
		break;
	case 3:
		PrintCommonHeader("AOA 1 MNVR EXEC", pMDU);
		break;
	case 4:
		PrintCommonHeader("OMS 2 MNVR EXEC", pMDU);
		break;
	case 5:
		PrintCommonHeader("ATO 2 MNVR EXEC", pMDU);
		break;
	case 6:
		PrintCommonHeader("  AOA MNVR TRANS", pMDU);
		break;
	case 7:
		PrintCommonHeader("OMS 2 MNVR COAST", pMDU);
		break;
	case 8:
		PrintCommonHeader("ATO 2 MNVR COAST", pMDU);
		break;
	case 9:
		PrintCommonHeader("DEORB MNVR COAST", pMDU);
		break;
	case 10:
		PrintCommonHeader("DEORB MNVR EXEC", pMDU);
		break;
	case 11:
		PrintCommonHeader("ORBIT MNVR EXEC", pMDU);
		break;
	default:
		PrintCommonHeader("????? MNVR ?????", pMDU);
		break;
	}

	switch (TXX_FLAG)
	{
	case 0:
		sprintf_s(cbuf, 255, "TFF");
		break;
	case 1:
		sprintf_s(cbuf, 255, "TTA");
		break;
	case 2:
		sprintf_s(cbuf, 255, "TTP");
		break;
	case 3:
		sprintf_s(cbuf, 255, "TTC   :");
		break;
	default:
		sprintf_s(cbuf, 255, "T??   :");
		break;
	}

	pMDU->mvprint(20, 9, cbuf);

	if (TXX_FLAG >= 0 && TXX_FLAG <= 2)
	{ 
		//If TXX was reset to negative, then it is blanked
		if (TXX >= 0)
		{
			//Special MM 303 logic. This is how the BFS works, PFS would use the CRT timer
			double tempt;
			if (GetMajorMode() == 303)
			{
				tempt = TXX - ReadCOMPOOL_SD(SCP_CLOCK);
			}
			else
			{
				tempt = TXX;
			}

			minutes = (int)(abs(tempt) / 60);
			seconds = (int)(abs(tempt) - (60 * minutes));

			sprintf_s(cbuf, 255, "%.2d:%.2d", minutes, seconds);
			pMDU->mvprint(24, 9, cbuf);
		}
	}

	int timeDiff = max(0, static_cast<int>(tig - ReadCOMPOOL_SD(SCP_CLOCK) + 1.0));
	if(ST_CRT_TIMER) {
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
	sprintf_s(cbuf, 255, "9 WT %6.0f", WT_DISP);
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
	if (PEG_MODE_4)
	{
		sprintf_s(cbuf, 255, "%5.0f", C1_DISP);
		pMDU->mvprint(12, 14, cbuf);
	}
	pMDU->Underline( 12, 14 );
	pMDU->Underline( 13, 14 );
	pMDU->Underline( 14, 14 );
	pMDU->Underline( 15, 14 );
	pMDU->Underline( 16, 14 );
	pMDU->mvprint(2, 15, "15 C2");
	if (PEG_MODE_4)
	{
		sprintf_s(cbuf, 255, "%6.4f", fabs(C2_DISP));
		pMDU->mvprint(11, 15, cbuf);
		pMDU->NumberSignBracket(10, 15, C2_DISP);
	}
	else
	{
		pMDU->NumberSignBracket(10, 15, 0.0);
	}
	pMDU->Underline( 11, 15 );
	pMDU->Underline( 12, 15 );
	pMDU->Underline( 13, 15 );
	pMDU->Underline( 14, 15 );
	pMDU->Underline( 15, 15 );
	pMDU->Underline( 16, 15 );
	pMDU->mvprint(2, 16, "16 HT");
	if (PEG_MODE_4)
	{
		sprintf_s(cbuf, 255, "%7.3f", HTGT_DISP);
		pMDU->mvprint(10, 16, cbuf);
	}
	pMDU->Underline( 10, 16 );
	pMDU->Underline( 11, 16 );
	pMDU->Underline( 12, 16 );
	pMDU->Underline( 13, 16 );
	pMDU->Underline( 14, 16 );
	pMDU->Underline( 15, 16 );
	pMDU->Underline( 16, 16 );
	pMDU->mvprint(2, 17, "17  T");
	pMDU->Theta(5, 17);
	if (PEG_MODE_4)
	{
		sprintf_s(cbuf, 255, "%7.3f", THETA_DISP);
		pMDU->mvprint(10, 17, cbuf);
	}
	pMDU->Underline( 10, 17 );
	pMDU->Underline( 11, 17 );
	pMDU->Underline( 12, 17 );
	pMDU->Underline( 13, 17 );
	pMDU->Underline( 14, 17 );
	pMDU->Underline( 15, 17 );
	pMDU->Underline( 16, 17 );
	pMDU->mvprint(2, 18, "18 PRPLT");
	if (PEG_MODE_4)
	{
		sprintf_s(cbuf, 255, "%5.0f", fabs(PROP_DEP));
		pMDU->mvprint(12, 18, cbuf);
		pMDU->NumberSignBracket(11, 18, PROP_DEP);
	}
	else
	{
		pMDU->NumberSignBracket(11, 18, 0.0);
	}
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
	if (PEG_MODE_4)
	{
		if (VGO_LVLH.x != 0.0 || VGO_LVLH.y != 0.0 || VGO_LVLH.z != 0.0) {
			sprintf_s(cbuf, 255, "%6.1f", min(9999.9, fabs(VGO_LVLH.x)));
			pMDU->mvprint(10, 20, cbuf);
			pMDU->NumberSignBracket(9, 20, VGO_LVLH.x);
			sprintf_s(cbuf, 255, "%5.1f", min(999.9, fabs(VGO_LVLH.y)));
			pMDU->mvprint(11, 21, cbuf);
			pMDU->NumberSignBracket(10, 21, VGO_LVLH.y);
			sprintf_s(cbuf, 255, "%5.1f", min(999.9, fabs(VGO_LVLH.z)));
			pMDU->mvprint(11, 22, cbuf);
			pMDU->NumberSignBracket(10, 22, VGO_LVLH.z);
		}
		else
		{
			pMDU->mvprint(14, 20, ".");
			pMDU->NumberSignBracket(9, 20, 0.0);
			pMDU->mvprint(14, 21, ".");
			pMDU->NumberSignBracket(10, 21, 0.0);
			pMDU->mvprint(14, 22, ".");
			pMDU->NumberSignBracket(10, 22, 0.0);
		}
	}
	else
	{
		sprintf_s(cbuf, 255, "%6.1f", min(9999.9, fabs(EXT_DV_LVLH.x)));
		pMDU->mvprint(10, 20, cbuf);
		pMDU->NumberSignBracket(9, 20, EXT_DV_LVLH.x);
		sprintf_s(cbuf, 255, "%5.1f", min(999.9, fabs(EXT_DV_LVLH.y)));
		pMDU->mvprint(11, 21, cbuf);
		pMDU->NumberSignBracket(10, 21, EXT_DV_LVLH.y);
		sprintf_s(cbuf, 255, "%5.1f", min(999.9, fabs(EXT_DV_LVLH.z)));
		pMDU->mvprint(11, 22, cbuf);
		pMDU->NumberSignBracket(10, 22, EXT_DV_LVLH.z);
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
		pMDU->mvprint(1, 23, "LOAD");

		if(bBurnMode)
		{
			if (!EXEC_CMD && timeDiff <= -BURN_ENABLE_WINDOW) pMDU->mvprint(46, 2, "EXEC", dps::DEUATT_FLASHING + dps::DEUATT_OVERBRIGHT);
		}
	}
	else pMDU->mvprint(1, 23, "LOAD", dps::DEUATT_FLASHING);

	pMDU->mvprint(6, 23, "22/TIMER 23");

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

	if (GetMajorMode() >= 301 && REI_LS != 0)
	{
		sprintf_s(cbuf, 255, "%.0f", abs(REI_LS));
		pMDU->mvprint(24, 8, cbuf);
	}

	pMDU->mvprint(25, 10, "GMBL");
	pMDU->mvprint(24, 11, "L");
	pMDU->mvprint(30, 11, "R");
	pMDU->mvprint( 20, 12, "P" );
	pMDU->mvprint( 20, 13, "Y" );

	if (ReadCOMPOOL_IS( SCP_OMSL_PITCH_STATUS ) == 1) pMDU->mvprint( 26, 12, "M", dps::DEUATT_OVERBRIGHT );
	else if (ReadCOMPOOL_IS( SCP_OMSL_PITCH_STATUS ) == 2) pMDU->DownArrow( 26, 12, dps::DEUATT_OVERBRIGHT );

	if (ReadCOMPOOL_IS( SCP_OMSL_YAW_STATUS ) == 1) pMDU->mvprint( 26, 13, "M", dps::DEUATT_OVERBRIGHT );
	else if (ReadCOMPOOL_IS( SCP_OMSL_YAW_STATUS ) == 2) pMDU->DownArrow( 26, 13, dps::DEUATT_OVERBRIGHT );

	if (ReadCOMPOOL_IS( SCP_OMSR_PITCH_STATUS ) == 1) pMDU->mvprint( 32, 12, "M", dps::DEUATT_OVERBRIGHT );
	else if (ReadCOMPOOL_IS( SCP_OMSR_PITCH_STATUS ) == 2) pMDU->DownArrow( 32, 12, dps::DEUATT_OVERBRIGHT );

	if (ReadCOMPOOL_IS( SCP_OMSR_YAW_STATUS ) == 1) pMDU->mvprint( 32, 13, "M", dps::DEUATT_OVERBRIGHT );
	else if (ReadCOMPOOL_IS( SCP_OMSR_YAW_STATUS ) == 2) pMDU->DownArrow( 32, 13, dps::DEUATT_OVERBRIGHT );
	
	if (ReadCOMPOOL_IS( SCP_OMSL_PITCH_STATUS ) != 1)
	{
		sprintf_s( cbuf, 255, "%+02.1f", ReadCOMPOOL_SS( SCP_SOMSLPFDBK ) );
		pMDU->mvprint( 22, 12, cbuf );
	}
	if (ReadCOMPOOL_IS( SCP_OMSL_YAW_STATUS ) != 1)
	{
		sprintf_s( cbuf, 255, "%+02.1f", ReadCOMPOOL_SS( SCP_SOMSLYFDBK ) );
		pMDU->mvprint( 22, 13, cbuf );
	}
	if (ReadCOMPOOL_IS( SCP_OMSR_PITCH_STATUS ) != 1)
	{
		sprintf_s( cbuf, 255, "%+02.1f", ReadCOMPOOL_SS( SCP_SOMSRPFDBK ) );
		pMDU->mvprint( 28, 12, cbuf );
	}
	if (ReadCOMPOOL_IS( SCP_OMSR_YAW_STATUS ) != 1)
	{
		sprintf_s( cbuf, 255, "%+02.1f", ReadCOMPOOL_SS( SCP_SOMSRYFDBK ) );
		pMDU->mvprint( 28, 13, cbuf );
	}

	pMDU->mvprint(20, 15, "PRI 28   29");
	pMDU->mvprint(20, 16, "SEC 30   31");
	pMDU->mvprint(20, 17, "OFF 32   33");
	int y = 17;
	if (ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL ) == 0) y = 15;
	else if (ReadCOMPOOL_IS( SCP_OMSL_ACT_SEL ) == 1) y = 16;
	pMDU->mvprint( 26, y, "*");

	y = 17;
	if (ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL ) == 0) y = 15;
	else if (ReadCOMPOOL_IS( SCP_OMSR_ACT_SEL ) == 1) y = 16;
	pMDU->mvprint( 31, y, "*");

	pMDU->mvprint(20, 19, "GMBL CK  34");
	if (ReadCOMPOOL_IS( SCP_DRIVE_OMS ) == 1) pMDU->mvprint( 31, 19, "*" );

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
		int BurnTime[2];
		sprintf_s(cbuf, 255, "%6.1f", min(9999.9, DV_TOT));
		pMDU->mvprint(44, 3, cbuf);

		BurnTime[0]=(int)(TGO /60);
		BurnTime[1]=(int)(TGO -(BurnTime[0]*60));

		sprintf_s(cbuf, 255, "%2d:%.2d", BurnTime[0], BurnTime[1]);
		pMDU->mvprint(45, 4, cbuf);

		sprintf_s(cbuf, 255, "%7.2f", min(9999.99,fabs(VGO_DISP.x )));
		pMDU->mvprint(43, 6, cbuf);
		pMDU->NumberSign( 42, 6, VGO_DISP.x );
		sprintf_s(cbuf, 255, "%6.2f", min(999.99,fabs(VGO_DISP.y )));
		pMDU->mvprint(44, 7, cbuf);
		pMDU->NumberSign( 43, 7, VGO_DISP.y );
		sprintf_s(cbuf, 255, "%6.2f", min(999.99,fabs(VGO_DISP.z )));
		pMDU->mvprint(44, 8, cbuf);
		pMDU->NumberSign( 43, 8, VGO_DISP.z );
	}

	pMDU->mvprint(41, 10, "HA    HP");
	if(MnvrLoad && !Eq(TGT_HA, 0.0)) {
		double _ap = TGT_HA;
		double _pe = TGT_HP;
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
		double _ap = CUR_HA;
		double _pe = CUR_HP;
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
		sscanf_s(value, "%lf%lf%lf", &EXT_DV_LVLH.x, &EXT_DV_LVLH.y, &EXT_DV_LVLH.z);
		return true;
	}
	else if(!_strnicmp(keyword, "PEG4", 4)) {
		sscanf_s(value, "%lf%lf%lf%lf", &C1_DISP, &C2_DISP, &HTGT_DISP, &THETA_DISP);
		PEG_MODE_4 = true;
		return true;
	}
	else if (!_strnicmp(keyword, "VGO_LVLH", 8)) {
		sscanf_s(value, "%lf%lf%lf", &VGO_LVLH.x, &VGO_LVLH.y, &VGO_LVLH.z);
		return true;
	}
	else if(!_strnicmp(keyword, "Trim", 4)) {
		sscanf_s(value, "%lf%lf%lf", &Trim.x, &Trim.y, &Trim.z);
		return true;
	}
	else if(!_strnicmp(keyword, "BURN_ATT", 8)) {
		int iTemp = 1;
		sscanf_s(value, "%lf%lf%lf%d", &BurnAtt.x, &BurnAtt.y, &BurnAtt.z, &iTemp);
		X_FLAG = (iTemp != 0);
		return true;
	}
	else if(!_strnicmp(keyword, "WT", 2)) {
		sscanf_s(value, "%f", &WT_DISP);
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
	else if(!_strnicmp(keyword, "MNVR", 5)) {
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
		ST_CRT_TIMER = true;
		return true;
	}
	else if (!_strnicmp(keyword, "VGO", 3)) {
		sscanf_s(value, "%lf%lf%lf", &VGO.x, &VGO.y, &VGO.z);
		return true;
	}
	else if (!_strnicmp(keyword, "APS", 3)) {
		sscanf_s(value, "%lf%lf%lf%lf", &CUR_HA, &CUR_HP, &TGT_HA, &TGT_HP);
		return true;
	}
	else if (!_strnicmp(keyword, "REI_LS", 6)) {
		sscanf_s(value, "%f", &REI_LS);
		return true;
	}
	else if (!_strnicmp(keyword, "TGO", 3)) {
		sscanf_s(value, "%lf", &TGO);
		return true;
	}
	else if (!_strnicmp(keyword, "TXX", 3)) {
		sscanf_s(value, "%d%lf", &TXX_FLAG, &TXX);
		return true;
	}
	else if (!_strnicmp(keyword, "THRUST_BODY", 11)) {
		sscanf_s(value, "%lf%lf%lf", &THRUST_BODY.x, &THRUST_BODY.y, &THRUST_BODY.z);
		return true;
	}
	else if (!_strnicmp(keyword, "GUIDANCEFLAGS", 13)) {
		int steertemp = 1;
		sscanf_s(value, "%d%d%d%d%d", &PROP_FLAG, &PROP_FLAG_GUID, &PROP_FLAG_OFS, &PROP_FLAG_OFS_P, &steertemp);
		SSTEER = (steertemp != 0);
		return true;
	}
	else if (!_strnicmp(keyword, "MNVR_TITLE_IND", 14)) {
		sscanf_s(value, "%d", &MNVR_TITLE_IND);
		return true;
	}
	else if (!_strnicmp(keyword, "T_ET_SEP", 8)) {
		double temp;
		sscanf_s(value, "%lf", &temp);
		WriteCOMPOOL_SD(SCP_T_ET_SEP, temp);
		return true;
	}
	return false;
}

void OMSBurnSoftware::OnSaveState(FILEHANDLE scn) const
{
	char cbuf[255];
	oapiWriteScenario_int(scn, "OMS", OMS);
	oapiWriteScenario_vec(scn, "PEG7", EXT_DV_LVLH);
	if(PEG_MODE_4) { // save PEG4 targets
		sprintf_s(cbuf, 255, "%f %f %f %f", C1_DISP, C2_DISP, HTGT_DISP, THETA_DISP);
		oapiWriteScenario_string(scn, "PEG4", cbuf);
		oapiWriteScenario_vec(scn, "VGO_LVLH", VGO_LVLH);
	}
	oapiWriteScenario_vec(scn, "Trim", Trim);
	sprintf_s(cbuf, 255, "%f %f %f %d", BurnAtt.x, BurnAtt.y, BurnAtt.z, X_FLAG);
	oapiWriteScenario_string(scn, "BURN_ATT", cbuf);
	oapiWriteScenario_float(scn, "WT", WT_DISP);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", TIG[0], TIG[1], TIG[2], TIG[3]);
	oapiWriteScenario_string(scn, "TIG", cbuf);
	oapiWriteScenario_int(scn, "TV_ROLL", TVR_ROLL);
	sprintf_s(cbuf, 255, "%d %d %d", MnvrLoad, MnvrToBurnAtt, BurnCompleted);
	oapiWriteScenario_string(scn, "MNVR", cbuf);
	if(ST_CRT_TIMER) oapiWriteScenario_string(scn, "TIMER", "");
	oapiWriteScenario_vec(scn, "VGO", VGO);
	sprintf_s(cbuf, 255, "%f %f %f %f", CUR_HA, CUR_HP, TGT_HA, TGT_HP);
	oapiWriteScenario_string(scn, "APS", cbuf);
	oapiWriteScenario_float(scn, "REI_LS", REI_LS);
	oapiWriteScenario_float(scn, "TGO", TGO);
	sprintf_s(cbuf, 255, "%d %f", TXX_FLAG, TXX);
	oapiWriteScenario_string(scn, "TXX", cbuf);
	if (MnvrLoad)
	{
		oapiWriteScenario_vec(scn, "THRUST_BODY", THRUST_BODY);
		sprintf_s(cbuf, 255, "%d %d %d %d %d", PROP_FLAG, PROP_FLAG_GUID, PROP_FLAG_OFS, PROP_FLAG_OFS_P, SSTEER);
		oapiWriteScenario_string(scn, "GUIDANCEFLAGS", cbuf);
	}
	oapiWriteScenario_int(scn, "MNVR_TITLE_IND", MNVR_TITLE_IND);
	if (GetMajorMode() < 200)
	{
		oapiWriteScenario_float(scn, "T_ET_SEP", ReadCOMPOOL_SD(SCP_T_ET_SEP));
	}
}

void OMSBurnSoftware::SetManeuverData(double maneuverTIG, const VECTOR3& maneuverDV)
{
	ConvertSecondsToDDHHMMSS(maneuverTIG, TIG);
	EXT_DV_LVLH = maneuverDV;
}

void OMSBurnSoftware::StartBurn()
{
	BurnInProg=true;
	IgnitionTime = T_GMT;
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
		float Lp = ReadCOMPOOL_SS( SCP_SOMSLPFDBK );
		float Rp = ReadCOMPOOL_SS( SCP_SOMSRPFDBK );
		Trim.data[0] = (Rp + Lp) * 0.5;// HACK no clue how to handle this one
		Trim.data[1] = ReadCOMPOOL_SS( SCP_SOMSLYFDBK );
		Trim.data[2] = ReadCOMPOOL_SS( SCP_SOMSRYFDBK );
	}
	else if (OMS == 1)
	{
		Trim.data[0] = ReadCOMPOOL_SS( SCP_SOMSLPFDBK );
		Trim.data[1] = ReadCOMPOOL_SS( SCP_SOMSLYFDBK );
	}
	else if (OMS == 2)
	{
		Trim.data[0] = ReadCOMPOOL_SS( SCP_SOMSRPFDBK );
		Trim.data[2] = ReadCOMPOOL_SS( SCP_SOMSRYFDBK );
	}
}

void OMSBurnSoftware::OPS1_INIT(int mm)
{	
	if (mm == 104 || mm == 105)
	{
		//DISP_MONIT_TSK init pass
		ST_CRT_TIMER = false;
		MnvrLoad = false;
		EXEC_CMD = false;

		//Guidance init
		SCO = false;

		//Reset burn data (VGO, TGO, etc.) displayed on CRT screen
		VGO_LVLH = _V(0, 0, 0);
		VGO_DISP = _V(0, 0, 0);
		DV_TOT = 0.0;

		//Reset burn flags
		MnvrToBurnAtt = false;
		BurnInProg = false;
		BurnCompleted = false;
	}

	//TBD: This should probably be somewhere else
	if (mm == 104)
	{
		double T_ET_SEP = ReadClock() - 4.0; //Just a rough estimate for now
		WriteCOMPOOL_SD(SCP_T_ET_SEP, T_ET_SEP);
	}

	//DISP_INIT_TSK
	PEG_MODE_4 = true;
	int I = 0;

	if (mm == 104)
	{
		MNVR_TITLE_IND = 1;
		I = 1;
	}
	else if (mm == 105)
	{
		MNVR_TITLE_IND = 4;
		I = 2;
	}
	else
	{
		MNVR_TITLE_IND = 7;
	}

	if (false) //TBD: Check on AOA flag
	{
		MNVR_TITLE_IND += 2;
		I = 3;
	}
	else if (false) //TBD: Check on ATO flag
	{
		MNVR_TITLE_IND += 1;
		I = 3;
	}

	//Load PEG-4 targets
	if (I > 0)
	{
		HTGT_DISP = HTGT_OMS[I - 1] * NAUTMI_PER_FT;
		THETA_DISP = THETA_OMS[I - 1] / RAD_PER_DEG;
		C1_DISP = C1_OMS[I - 1];
		C2_DISP = C2_OMS[I - 1];

		tig = ReadCOMPOOL_SD(SCP_T_ET_SEP) + DTIG_OMS[I - 1];
		tig = tig - ReadCOMPOOL_SD(SCP_T_MET_REF);
		ConvertSecondsToDDHHMMSS(tig, TIG);
	}
}

void OMSBurnSoftware::OPS2_INIT()
{
	//DISP_MONIT_TSK init pass
	MnvrLoad = false;
	EXEC_CMD = false;
	ST_CRT_TIMER = false;

	//Guidance init
	SCO = false;

	//Reset burn data (VGO, TGO, etc.) displayed on CRT screen
	VGO_DISP = _V(0, 0, 0);
	DV_TOT = 0.0;
	PEG_MODE_4 = false;

	//Reset burn flags
	MnvrToBurnAtt = false;
	BurnInProg = false;
	BurnCompleted = false;

	//DISP_INIT_TSK
	MNVR_TITLE_IND = 11;
}

void OMSBurnSoftware::OPS3_INIT(int mm)
{
	if (mm == 301)
	{
		//DISP_MONIT_TSK init pass
		ST_CRT_TIMER = false;
		MnvrLoad = false;
		EXEC_CMD = false;

		//TBD: This shouldn't be here. It can not be changed by keyboard in OPS 3, only by uplink.
		//It could be changed in OPS 2 before transitioning to OPS 3
		TVR_ROLL = 180;

		//Reset burn data (VGO, TGO, etc.) displayed on CRT screen
		REI_LS = 0.0;
		TXX = -1.0;
		VGO_LVLH = _V(0, 0, 0);
		VGO_DISP = _V(0, 0, 0);
		DV_TOT = 0.0;

		//Reset burn flags
		MnvrToBurnAtt = false;
		BurnInProg = false;
		BurnCompleted = false;
	}
	else if (mm == 302)
	{
		//Guidance init
		SCO = false;
	}
	else if (mm == 303)
	{
		PRE_ENT_COAST_TSK();
		MnvrToBurnAtt = false;

		//TBD: Only the BFS counts down the TTF, the PFS would use the CRT timer. Reset this for now.
		ST_CRT_TIMER = false;
	}

	//DISP_INIT_TSK
	if (mm == 302)
	{
		MNVR_TITLE_IND = 10;
	}
	else
	{
		MNVR_TITLE_IND = 9;
	}
	TXX_FLAG = 0;
}

bool OMSBurnSoftware::PRE_MAN_DISP_SUPT_TSK1()
{
	double T_GMT, T_GMTLO;

	//Get some COMPOOL stuff
	T_GMT = ReadCOMPOOL_SD(SCP_CLOCK);
	T_GMTLO = ReadCOMPOOL_SD(SCP_T_MET_REF);

	//Calculate tig in GMT
	tig = ConvertDDHHMMSSToSeconds(TIG) + T_GMTLO;

	//Check for illegal TIG
	if (tig - T_GMT < -300.0 || tig - T_GMT > 43200.0)
	{
		return true;
	}

	//Propagate state vector to TIG
	VECTOR3 RNAV, VNAV;
	double TNAV;

	RNAV = ReadCOMPOOL_VD(SCP_R_AVGG);
	VNAV = ReadCOMPOOL_VD(SCP_V_AVGG);
	TNAV = ReadCOMPOOL_SD(SCP_T_STATE);

	pStateVector->ONORBIT_PREDICT(RNAV, VNAV, TNAV, tig, 4, 4, true, true, 1, 300.0, RGD, VGD);
	TGD = tig;

	M = WT_DISP / G_2_FPS2;

	//Update guidance flags
	if (OMS == 0)
	{
		PROP_FLAG_GUID = 1;
		PROP_FLAG_OFS = 1;
	}
	else if (OMS == 1)
	{
		PROP_FLAG_GUID = 2;
		PROP_FLAG_OFS = 2;
	}
	else if (OMS == 2)
	{
		PROP_FLAG_GUID = 2;
		PROP_FLAG_OFS = 3;
	}
	else
	{
		PROP_FLAG_GUID = 3;
		PROP_FLAG_OFS = 4;
	}
	PROP_FLAG_OFS_P = 0;
	PROP_FLAG = PROP_FLAG_GUID;

	if (PEG_MODE_4)
	{
		VECTOR3 RT;
		float MBO;
		int SFUELD;

		double THETA = THETA_DISP * RAD_PER_DEG;

		// calculate target position
		VECTOR3 IR = unit(RGD);

		if (GetMajorMode() < 200)
		{
			//OPS1
			VECTOR3 RLS_M50 = pStateVector->GetPositionAtT0();
			VECTOR3 IDR = unit(crossp(RGD, crossp(VGD, RGD)));
			double THETA_LS = atan2(dotp(-RLS_M50, IDR), dotp(RLS_M50, IR));
			if (THETA_LS < 0)
			{
				THETA_LS += PI2;
			}
			double DTHETA = THETA - THETA_LS;
			VECTOR3 IRT = IR * cos(DTHETA) + IDR * sin(DTHETA);
			RT = IRT * (EARTH_RADIUS_EQUATOR + HTGT_DISP / NAUTMI_PER_FT);

			MBO = 0.0f;
			SFUELD = 0;
		}
		else
		{
			//OPS3
			VECTOR3 IYO = unit(crossp(VGD, IR));
			VECTOR3 IDR = crossp(IR, IYO);
			VECTOR3 IRT = IR * cos(THETA) + IDR * sin(THETA);
			double RTMAG = HTGT_DISP / NAUTMI_PER_FT - pGNCUtilities->H_ELLIPSOID(IRT);
			RT = IRT * RTMAG;

			MBO = M - abs(PROP_DEP) / G_2_FPS2;
			if (PROP_DEP > 0)
			{
				SFUELD = 1;
			}
			else if (PROP_DEP < 0)
			{
				SFUELD = -1;
			}
			else
			{
				SFUELD = 0;
			}
		}

		peg4Targeting.SetPEG4Targets(C1_DISP, C2_DISP, RGD, VGD, tig, RT, FT[PROP_FLAG - 1], VEX[PROP_FLAG - 1], M, MBO, SFUELD, NMAX_DIP);
		oapiWriteLogV("PEG4 Initial state: %f %f %f %f %f %f", RGD.x, RGD.y, RGD.z, VGD.x, VGD.y, VGD.z);

		bCalculatingPEG4Burn = true;
	}
	else
	{
		VECTOR3 Q_I_LVLHV;
		double Q_I_LVLHS;

		RV_TO_QLVLH(RGD, VGD, Q_I_LVLHS, Q_I_LVLHV);
		VGO = QUAT_XFORM(Q_I_LVLHS, Q_I_LVLHV, EXT_DV_LVLH);

		PRE_MAN_DISP_SUPT_TSK2();
	}

	return false;
}

void OMSBurnSoftware::PRE_MAN_DISP_SUPT_TSK2()
{
	if (PEG_MODE_4)
	{
		//Convert inertial VGO to VGO_LVLH
		VECTOR3 Q_I_LVLH_V;
		double Q_I_LVLH_S;

		RV_TO_QLVLH(RGD, VGD, Q_I_LVLH_S, Q_I_LVLH_V);
		VGO_LVLH = QUAT_XFORM(-Q_I_LVLH_S, Q_I_LVLH_V, VGO);
	}

	//Calculate burn parameters
	SSTEER = true;
	GUID_TSK();
	CMD_BDY_ATT_TSK();

	VECTOR3 RP, VD;

	//Predict cutoff state
	if (PEG_MODE_4 == false)
	{
		RP = RGD - VGO * 0.5*TGO;
		VD = VGD + VGO;
	}
	else
	{
		VECTOR3 RC1, VC1, RC2, VC2, RC3, VC3, VJ2, RJ2;

		peg4Targeting.GetStateVectors(RP, VD, RC1, VC1, RC2, VC2);

		pStateVector->ENTRY_PRECISE_PREDICTOR(RC1, VC1, tig, TGO + tig, 2, 0, DT_RNG, RC3, VC3);

		VJ2 = VC3 - VC2;
		RJ2 = RC3 - RC2;
		RP = RP + RJ2;
		VD = VD + VJ2;
	}

	//Use the simpler OPS3 function as we don't need the time to the next apsis
	OPS3_ORB_ALT_TSK(RP, VD, TGT_HA, TGT_HP);
	//In OPS3 calculate range to landing site and time to EI
	if (GetMajorMode() / 100 == 3)
	{
		RNG_TO_LS_TSK(RP, VD, tig, TGT_HP, false);
		if (PEG_MODE_4 == false) TXX = TXX - TGO;
	}

	MnvrLoad = true;
}

void OMSBurnSoftware::CUR_ORBIT_TSK()
{
	VECTOR3 RNAV, VNAV;

	//Get UPP state vector
	RNAV = ReadCOMPOOL_VD(SCP_R_AVGG);
	VNAV = ReadCOMPOOL_VD(SCP_V_AVGG);

	//If we are in OPS 3 then the time-to-next-apsis does not have to be calculated, so use the simple OPS 3 version of the ORB ALT TSK
	if (GetMajorMode() > 300)
	{
		OPS3_ORB_ALT_TSK(RNAV, VNAV, CUR_HA, CUR_HP);
	}
	else
	{
		OPS2_ORB_ALT_TSK(RNAV, VNAV, CUR_HA, CUR_HP, TXX, TXX_FLAG);
	}
}

void OMSBurnSoftware::PRE_ENT_COAST_TSK()
{
	VECTOR3 RNAV, VNAV;
	double TNAV;

	//Get UPP state vector from COMPOOL
	RNAV = ReadCOMPOOL_VD(SCP_R_AVGG);
	VNAV = ReadCOMPOOL_VD(SCP_V_AVGG);
	TNAV = ReadCOMPOOL_SD(SCP_T_STATE);

	//Calculate range to landing site and time to entry interface
	RNG_TO_LS_TSK(RNAV, VNAV, TNAV, CUR_HP, true);

	//Unrealistic code to calculate EI-5m attitude
	VECTOR3 R_FINAL, V_FINAL;
	pStateVector->ENTRY_PRECISE_PREDICTOR(RNAV, VNAV, TNAV, TXX - 300.0, 4, 4, 2.0, R_FINAL, V_FINAL);
	const MATRIX3 EI_ATT = GetRotationMatrixYZX(_V(0.0, 40.0*RAD, 0.0));
	BurnAtt = ConvertLVLHMatrixToM50Angles(EI_ATT, R_FINAL, V_FINAL)*DEG;
}

void OMSBurnSoftware::RNG_TO_LS_TSK(VECTOR3 R1, VECTOR3 V1, double T1, double H_PERIGEE, bool showTimer)
{
	VECTOR3 UN_R, R2, V2;
	double T_INIT_LS, R_DOT, H, H_MISS, DT, T2;
	int COUNT_RNG;

	//Initialize variables
	T_INIT_LS = T1;
	TXX = 0.0;
	REI_LS = 0.0;
	COUNT_RNG = 0;

	//If perigee altitude is greater than specified, exit the task
	if (H_PERIGEE > HP_MAX) return; //TBD: TAL

	//Iterate on entry iterface time
	do
	{
		//Calculate height difference between current estimate and desired
		UN_R = unit(R1);
		R_DOT = dotp(V1, UN_R);
		H = pGNCUtilities->H_ELLIPSOID(R1);
		H_MISS = H - H_TARGET;

		//If miss distance is within tolerance, stop iteration
		if (abs(H_MISS) < EPS_H_MISS)
		{
			break;
		}
		//Increment iteration counter
		COUNT_RNG++;

		//Limit coast time
		if (R_DOT > R_DOT_MAX)
		{
			DT = sign(H_MISS)*DT_EI;
		}
		else
		{
			DT = midval(DT_EI, -H_MISS / R_DOT, -DT_EI);
		}

		//Improve estimate of time to entry interface
		T2 = T1 + DT;
		//Propagate to new time estimate
		pStateVector->ENTRY_PRECISE_PREDICTOR(R1, V1, T1, T2, 2, 0, DT_RNG, R2, V2);
		//The input state is set equal to the propagated state
		R1 = R2;
		V1 = V2;
		T1 = T2;
	} while (COUNT_RNG < MAX_RNG);

	if (COUNT_RNG >= MAX_RNG) return;

	MATRIX3 M_EF_M50;
	VECTOR3 R_LS_M50;
	double ANG;

	//Convert landing site position vector to M50 at EI time
	M_EF_M50 = pGNCUtilities->EARTH_FIXED_TO_M50_COORD(T1);
	R_LS_M50 = mul(M_EF_M50, ReadCOMPOOL_VD(SCP_R_LS_EF));
	//Calculate angle between landing site and EI position vector
	ANG = acos(dotp(UN_R, unit(R_LS_M50)));
	//Calculate range to LS and time to EI
	REI_LS = (float)(ANG * EARTH_RADIUS_EQUATOR)*NAUTMI_PER_FT;
	TXX = T1 - T_INIT_LS;

	//TBD: In MM 303 show time to EI with CRT timer. For now do it like the BFS
	if (showTimer)
	{
		TXX = T1;
	}
}

void OMSBurnSoftware::OPS2_ORB_ALT_TSK(VECTOR3 R, VECTOR3 V, double &HA, double &HP, double &TT_X, int &TXX_FL)
{
	VECTOR3 R_UNIT;
	double RMAG, RDOT, AM, P, K, MM, NN, S_INC, NU, M, N, E, DELTA;

	//Calculate the magnitude of the radius vector (RMAG), the vertical velocity magnitude (RDOT), and the unit radius vector (R_UNIT)
	RMAG = length(R);
	R_UNIT = R / RMAG;
	RDOT = dotp(V, R_UNIT);

	//Calulate the two Keplerian elements, the semimajor axis (AM) and the semilatus rectum (P)
	AM = EARTH_MU * RMAG / (2.0*EARTH_MU - RMAG * dotp(V, V));
	P = RMAG * (2.0 - RMAG / AM - RMAG * RDOT*RDOT / EARTH_MU);

	//Compute a term to be used repeatedly in subsequent calculations
	K = pGNCUtilities->GetJ2()*pow(EARTH_RADIUS_EQUATOR, 2) / (4.0*P);

	//Compute three quantities to be used in later computations
	MM = dotp(ReadCOMPOOL_VD(SCP_EARTH_POLE), R_UNIT);
	NN = dotp(unit(V - R_UNIT * RDOT), ReadCOMPOOL_VD(SCP_EARTH_POLE));
	S_INC = pow(MM, 2) + pow(NN, 2);

	//Compute the mean semimajor axis (AM) and the inverse of the mean orbital rate (NU)
	AM = AM - (pGNCUtilities->GetJ2()*pow(EARTH_RADIUS_EQUATOR, 2)*pow(AM, 2) / pow(RMAG, 3))*(1.0 - 3.0*pow(MM, 2));
	NU = AM * sqrt(AM / EARTH_MU);

	//Compute the adjusted elements: radius (RMAG), vertical velocity (RDOT), and semimajor axis (AM)
	RMAG = RMAG + K * (pow(MM, 2) - pow(NN, 2));
	RDOT = RDOT + 4.0*K*MM*NN / NU;
	AM = AM - K * (2.0 - 3.0*S_INC);

	//Compute two quantities to be used in later computations – the product of the eccentricity and	the sine of the eccentric anomaly (M)
	//and the product of the eccentricity and the cosine of the eccentric anomaly (N)
	M = RMAG * RDOT / sqrt(EARTH_MU*AM);
	N = 1.0 - RMAG / AM;

	//Compute the eccentricity
	E = sqrt(pow(M, 2) + pow(N, 2));

	//Compute a term (DELTA) to be applied to correct the apogee and perigee altitudes
	DELTA = K * (pow(NN, 2) - pow(MM, 2));

	//Check the difference in apogee and perigee radii (2*AM*E) to determine if the orbit is near circular
	if (2.0*AM*E*NAUTMI_PER_FT < DELT_H_CIRC)
	{
		//Near circular orbit
		TXX_FL = 3;
		TT_X = 0.0;
	}
	else
	{
		double KK;

		//Compute the time-to-next apsis (TT_X) and compute the sine of the true anomaly (M) and the cosine of the true anomaly (N)
		TT_X = ((1.0 + sign(RDOT))*PI05 + M - atan2(M, N))*NU;
		M = sqrt(1.0 - pow(E, 2))*M / (E*(1.0 - N));
		N = (N - pow(E, 2)) / (E*(1.0 - N));

		//Test the sign of RDOT to determine if the next apsis is to be apogee (TXX_FLAG = 1) or perigee (TXX_FLAG = 2), and set the TXX_FLAG to the proper value
		if (RDOT >= 0)
		{
			TXX_FL = 1;
		}
		else
		{
			TXX_FL = 2;
		}
		//Recompute the correction to apogee and perigee (DELTA) to include a true anomaly factor
		DELTA = DELTA * (pow(N, 2) - pow(M, 2)) + 4.0*M*MM*N*NN*K;

		//Compute a term (KK) to correct the time–to–next–apsis (TT_X)
		KK = (AM*AM*E) / (4.0*P);

		// To prevent numerical problems in applying this correction term (KK), a check is performed to	ensure that it is in the allowable range(if KK > K S_INC)
		if (KK > K*S_INC)
		{
			double DELTB;

			DELTB = 2.0*K*(M*N*(MM*MM - NN * NN) - MM * NN*(M*M - N * N));
			if (DELTB != 0)
			{
				//For a nonzero value of DELTB, compute the time correction term (KK) and the time–to–next–apsis (TT_X)
				KK = -(sign(RDOT)*KK + DELTA) / DELTB;
				TT_X = TT_X + (1.0 + 2.0*sign(RDOT)*E)*NU / (KK + sign(KK)*sqrt(KK*KK + 2.0));

				//If the time–to–next–apsis (TT_X) is negative add half the period to this time and update the TXX_FLAG
				if (TT_X < 0)
				{
					TT_X = TT_X + PI * NU;
					TXX_FL = 1 + (TXX_FL % 2);
				}
			}
		}
	}

	//Compute the altitudes of apogee (HA) and perigee (HP) above a spherical earth
	HA = (AM*(1.0 + E) + DELTA - EARTH_RADIUS_EQUATOR)*NAUTMI_PER_FT;
	HP = (AM*(1.0 - E) + DELTA - EARTH_RADIUS_EQUATOR)*NAUTMI_PER_FT;
}

void OMSBurnSoftware::OPS3_ORB_ALT_TSK(VECTOR3 R, VECTOR3 V, double &HA, double &HP)
{
	VECTOR3 R_UNIT;
	double RMAG, RDOT, AM, P, K, MM, NN, NU, M, N, E, DELTA;

	RMAG = length(R);
	R_UNIT = R / RMAG;
	RDOT = dotp(V, R_UNIT);
	AM = EARTH_MU * RMAG / (2.0*EARTH_MU - RMAG * dotp(V, V));
	P = RMAG * (2.0 - RMAG / AM - RMAG * RDOT*RDOT / EARTH_MU);
	K = pGNCUtilities->GetJ2()*pow(EARTH_RADIUS_EQUATOR, 2) / (4.0*P);
	MM = dotp(ReadCOMPOOL_VD(SCP_EARTH_POLE), R_UNIT);
	NN = dotp(unit(V - R_UNIT * RDOT), ReadCOMPOOL_VD(SCP_EARTH_POLE));
	AM = AM - (pGNCUtilities->GetJ2()*pow(EARTH_RADIUS_EQUATOR, 2)*pow(AM, 2) / pow(RMAG, 3))*(1.0 - 3.0*pow(MM, 2));
	NU = AM * sqrt(AM / EARTH_MU);
	RMAG = RMAG + K * (pow(MM, 2) - pow(NN, 2));
	RDOT = RDOT + 4.0*K*MM*NN / NU;
	AM = AM - K * (2.0 - 3.0*(pow(MM, 2) + pow(NN, 2)));

	M = RMAG * RDOT / sqrt(EARTH_MU*AM);
	N = 1.0 - RMAG / AM;
	E = sqrt(pow(M, 2) + pow(N, 2));

	if (2.0*AM*E*NAUTMI_PER_FT < DELT_H_CIRC)
	{
		M = 0.0;
		N = 1.0;
	}
	else
	{
		M = sqrt(1.0 - pow(E, 2))*M / (E*(1.0 - N));
		N = (N - pow(E, 2)) / (E*(1.0 - N));
	}
	DELTA = K * ((pow(MM, 2) - pow(NN, 2))*(pow(M, 2) - pow(N, 2)) + 4.0*M*MM*N*NN) - EARTH_RADIUS_EQUATOR;
	HA = (AM*(1.0 + E) + DELTA)*NAUTMI_PER_FT;
	HP = (AM*(1.0 - E) + DELTA)*NAUTMI_PER_FT;
}

void OMSBurnSoftware::VGO_DISP_TSK()
{
	//Get attitude quaternion
	double Q_B_I_S = ReadCOMPOOL_VS(SCP_Q_B_I, 1, 4);
	VECTOR3 Q_B_I_V = ReadCOMPOOL_VS(SCP_Q_B_I + 2);

	//Calculate VGO in body coordinates
	VGO_DISP = QUAT_XFORM(Q_B_I_S, Q_B_I_V, VGO);

	if (AlternatePass)
	{
		if (PEG_MODE_4 && T_GMT >= tig)
		{
			//TBD: This should be in the attitude processor
			VECTOR3 Q_I_LVLHV;
			double Q_I_LVLHS;

			RV_TO_QLVLH(RGD, VGD, Q_I_LVLHS, Q_I_LVLHV);

			VGO_LVLH = QUAT_XFORM(-Q_I_LVLHS, Q_I_LVLHV, VGO);
		}

		//Every second pass update displayed total DV and weight
		DV_TOT = length(VGO_DISP);
		WT_DISP = M * G_2_FPS2;
	}
}

void OMSBurnSoftware::CMD_BDY_ATT_TSK()
{
	//Only update body fixed thrust direction in case of engine reconfiguration
	if (PROP_FLAG_OFS != PROP_FLAG_OFS_P)
	{
		//OMS engine configuration?
		if (PROP_FLAG_OFS < 4)
		{
			//OMS
			VECTOR3 THRUST_BODY_OMS[2];
			float YAW_TRIM[2], PITCH_TRIM, OMS_YAW_BODY[2], OMS_PITCH_BODY, C_YAW;
			int J1, J2;

			//Premaneuver calculations or engine failure?
			if (PROP_FLAG_OFS_P == 0)
			{
				//Premaneuver
				YAW_TRIM[0] = (float)Trim.y;
				YAW_TRIM[1] = (float)Trim.z;
				PITCH_TRIM = (float)Trim.x;
			}
			else
			{
				//Engine failure
				YAW_TRIM[0] = ONE_ENG_OMS_YAW_TRIM[0];
				YAW_TRIM[1] = ONE_ENG_OMS_YAW_TRIM[1];
				PITCH_TRIM = ONE_ENG_OMS_PITCH_TRIM;
			}

			//Compute the OMS yaw body angle
			OMS_YAW_BODY[0] = YAW_TRIM[0] * RAD_PER_DEG + YAW_BIAS;
			OMS_YAW_BODY[1] = YAW_TRIM[1] * RAD_PER_DEG - YAW_BIAS;

			//Set subscript limits J1 and J2
			J1 = 1;
			J2 = 2;

			if (PROP_FLAG_OFS == 3)
			{
				J1 = 2;
			}
			else if (PROP_FLAG_OFS == 2)
			{
				J2 = 1;
			}

			//Convert pitch trim to body reference
			OMS_PITCH_BODY = PITCH_BIAS - PITCH_TRIM * RAD_PER_DEG;

			//Compute OMS thrust body vector
			THRUST_BODY_OMS[0] = THRUST_BODY_OMS[1] = _V(0, 0, 0);
			for (int J = J1 - 1; J <= J2 - 1; J++)
			{
				C_YAW = cos(OMS_YAW_BODY[J]);
				THRUST_BODY_OMS[J] = _V(cos(OMS_PITCH_BODY)*C_YAW, sin(OMS_YAW_BODY[J]), sin(OMS_PITCH_BODY)*C_YAW);
			}
			THRUST_BODY = unit(THRUST_BODY_OMS[0] * (float)(2 - J1) + THRUST_BODY_OMS[1] * (float)(J2 - 1));
		}
		else
		{
			//RCS
			THRUST_BODY = THRUST_BODY_RCS_X;
		}
		PROP_FLAG_OFS_P = PROP_FLAG_OFS;
	}

	//Calculate burn attitude
	double Q_CB_M50_S, Q_CB_ADI_S, PTCHSINE, PTCHCOS, YAWSINE, YAWCOS, ROLLSINE, ROLLCOS;
	VECTOR3 UF, Q_CB_M50_V, Q_CB_ADI_V, YN;

	UF = unit(VGO);

	if (TGD <= tig)
	{
		//If current time is less than or equal to time of ignition, perform premaneuver calculations

		MATRIX3 MTP;
		VECTOR3 ROLL_REF, YT;
		double CBETA;

		//Calculate roll reference vector
		ROLL_REF = unit(RGD);
		//If desired thrust vector is within a tolerance of the radial direction, use a different roll reference vector to avoid attitude singularity
		CBETA = dotp(ROLL_REF, UF);
		if (abs(CBETA) > CBETA_EPS)
		{
			if (CBETA > 0)
			{
				ROLL_REF = -VGD;
			}
			else
			{
				ROLL_REF = VGD;
			}
		}
		//Calculate attitude matrix from M50 to body coordinates
		YN = unit(_V(THRUST_BODY.z, 0, -THRUST_BODY.x));
		YT = unit(crossp(UF, ROLL_REF))*sin(TVR_ROLL*RAD_PER_DEG) - crossp(UF, unit(crossp(UF, ROLL_REF)))*cos(TVR_ROLL*RAD_PER_DEG);
		MTP = MATRIX(THRUST_BODY, crossp(THRUST_BODY, YN), -YN);
		MTP = mul(Transpose(MTP), MATRIX(UF, crossp(UF, YT), -YT));
		//Convert the matrix to a quaternion
		MAT_TO_QUAT(MTP, Q_CB_M50_S, Q_CB_M50_V);
	}
	else
	{
		VECTOR3 Q_B_I_V, UFB, Q_CB_B_V, SRA;
		double Q_B_I_S, Q_CB_B_S;

		//Get current attitude quaternion
		Q_B_I_S = ReadCOMPOOL_VS(SCP_Q_B_I, 1, 4);
		Q_B_I_V = ReadCOMPOOL_VS(SCP_Q_B_I + 2);
		//Transform commanded unit thrust vector into current body coordinates
		UFB = QUAT_XFORM(Q_B_I_S, Q_B_I_V, UF);
		//Obtain difference between nominal and current thrust direction
		YN = UFB - THRUST_BODY;
		//If difference is less than 0.001, no attitude change is required. Set body-to-commanded-body quaternion to identity
		if (length(YN) < 0.001)
		{
			Q_CB_B_S = 1.0;
			Q_CB_B_V = _V(0, 0, 0);
		}
		else
		{
			VECTOR3 ATB, B;

			//Construct the single rotation axis
			SRA = unit(_V(0.0, YN.z, -YN.y));
			if (dotp(SRA, UFB) < 0)
			{
				SRA = -SRA;
			}
			//Compute the body-to-commanded-body quaternion
			ATB = crossp(crossp(SRA, THRUST_BODY), SRA);
			B = unit(ATB + YN * 0.5);
			ATB = unit(ATB);

			Q_CB_B_S = dotp(B, ATB);
			Q_CB_B_V = SRA * dotp(crossp(B, ATB), SRA);
		}
		//Compute the M50-to-commanded-body quaternion
		QUAT_MULT(Q_CB_B_S, Q_CB_B_V, Q_B_I_S, Q_B_I_V, Q_CB_M50_S, Q_CB_M50_V);
	}

	//Obtain the ADI inertial to commanded body quaternion from the M50-to-commanded body quaternion
	QUAT_MULT(Q_CB_M50_S, Q_CB_M50_V, 1.0, _V(0, 0, 0), Q_CB_ADI_S, Q_CB_ADI_V);
	//Calculate sines and cosines of Euler angles
	QUAT_TO_ADI_ANG(Q_CB_ADI_S, Q_CB_ADI_V, PTCHSINE, PTCHCOS, YAWSINE, YAWCOS, ROLLSINE, ROLLCOS, X_FLAG);

	if (X_FLAG)
	{
		//No attitude singularity, compute burn attitude
		BurnAtt.data[PITCH] = atan2(-PTCHSINE, -PTCHCOS) / RAD_PER_DEG + 180.0;
		BurnAtt.data[YAW] = atan2(-YAWSINE, -YAWCOS) / RAD_PER_DEG + 180.0;
		BurnAtt.data[ROLL] = atan2(-ROLLSINE, -ROLLCOS) / RAD_PER_DEG + 180.0;
	}
	else
	{
		//BurnAtt should only be for display, but right now it is being sent to the Orbit DAP. To get the correct attitude, do this calculation for now
		ROLLSINE = 0.0;
		ROLLCOS = 0.0;
		PTCHSINE = 2.0*(Q_CB_ADI_V.x*Q_CB_ADI_V.z - Q_CB_ADI_V.y*Q_CB_ADI_S);
		PTCHCOS = 1.0 - 2.0*(pow(Q_CB_ADI_V.x, 2) + pow(Q_CB_ADI_V.y, 2));

		BurnAtt.data[PITCH] = atan2(-PTCHSINE, -PTCHCOS)*DEG + 180.0;
		BurnAtt.data[YAW] = atan2(-YAWSINE, -YAWCOS)*DEG + 180.0;
		BurnAtt.data[ROLL] = atan2(-ROLLSINE, -ROLLCOS)*DEG + 180.0;

		/*if (YAWSINE >= 0)
		{
			BurnAtt.data[YAW] = 90.0;
		}
		else
		{
			BurnAtt.data[YAW] = 270.0;
		}*/
	}
}

void OMSBurnSoftware::ON_ORB_GUID_SEQ()
{
	GUID_INP_TSK();
	GUID_TSK();
	CMD_BDY_ATT_TSK();
	if (TGD >= tig && SCO == false)
	{
		OMS_TSK();
	}
}

void OMSBurnSoftware::GUID_INP_TSK()
{
	VECTOR3 DVS;

	//Obtain velocity change since last guidance pass
	DVS = VS - VSP;
	//Update velocity-to-go
	VGO = VGO - DVS;
	//Save current accumulated velocity for next pass
	VSP = VS;

	//Get UPP state vector
	RGD = ReadCOMPOOL_VD(SCP_R_AVGG);
	VGD = ReadCOMPOOL_VD(SCP_V_AVGG);
	TGD = ReadCOMPOOL_SD(SCP_T_STATE);

	//TBD: Handle engine failures

	//Update current orbiter mass
	if (TGD >= tig && TGO > 0.0)
	{
		M = M * exp(-(float)length(DVS) / VEX[PROP_FLAG - 1]);
	}
}

void OMSBurnSoftware::GUID_TSK()
{
	double VGOMAG, ATR, VRATIO;

	//Calculate velocity-to-go magnitude
	VGOMAG = length(VGO);
	//Calculate nominal acceleration
	ATR = FT[PROP_FLAG - 1] / M;
	//Update time-to-go
	VRATIO = VGOMAG / (6.0*VEX[PROP_FLAG - 1]);
	TGO = VGOMAG / (ATR*(1.0 + 3.0*VRATIO + 3.0*VRATIO*VRATIO));

	if (SSTEER)
	{
		WriteCOMPOOL_VS(SCP_LAMC, VGO / VGOMAG);
	}
}

void OMSBurnSoftware::OMS_TSK()
{
	VECTOR3 Q_B_I_V, THRUST_M50;
	double Q_B_I_S, TGO_CUTOFF;

	//Get attitude quaternion
	Q_B_I_S = ReadCOMPOOL_VS(SCP_Q_B_I, 1, 4);
	Q_B_I_V = ReadCOMPOOL_VS(SCP_Q_B_I + 2);

	//Calculate thrust direction in inertial coordinates
	THRUST_M50 = QUAT_XFORM(-Q_B_I_S, Q_B_I_V, THRUST_BODY);

	//Calculate time-to-go projected into thrust direction
	TGO_CUTOFF = TGO * dotp(THRUST_M50, VGO) / length(VGO);

	//If time to cutoff (TGO_CUTOFF) is less than or equal to TGO_MIN, then a cutoff time corrected for thrust tailoff is computed
	if (TGO_CUTOFF <= TGO_MIN)
	{
		T_CUTOFF = TGD + TGO_CUTOFF - TCO_BIAS;
		SCO = true;
		SSTEER = false;
	}
}

VECTOR3 OMSBurnSoftware::GetAttitudeCommandErrors() const
{
	if ((BurnInProg == false) || (OMS != 3)) return pOrbitDAP->GetAttitudeErrors(); // OMS || no burn
	else return VGO_DISP;// RCS
}
}
