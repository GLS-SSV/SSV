/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2022/08/26   indy91
2022/09/09   indy91
2022/09/29   GLS
2022/10/17   indy91
2022/11/11   indy91
2022/11/12   indy91
2022/11/19   indy91
2022/11/28   GLS
2022/11/29   GLS
2022/11/30   GLS
2022/11/30   indy91
2022/12/13   GLS
2022/12/14   GLS
********************************************/
#include "OrbitTgtSoftware.h"
#include "../Atlantis.h"
#include "../vc/MDU.h"
#include <MathSSV.h>
//#include <Stopwatch.h>
#include "OMSBurnSoftware.h"
#include "StateVectorSoftware.h"
#include "IDP.h"
#include <EngConst.h>

#define LOAD_V3(KEY,DATA) if (!strcmp (keyword, KEY)) { sscanf_s(value,"%lf %lf %lf",&DATA.x,&DATA.y,&DATA.z); }
#define LOAD_DOUBLE(KEY,DATA) if (!strcmp (keyword, KEY)){ sscanf_s(value,"%lf",&DATA); }

namespace dps
{

OrbitTgtSoftware::OrbitTgtSoftware(SimpleGPCSystem * _gpc)
: SimpleGPCSoftware(_gpc, "OrbitTgtSoftware"),
pOMSBurnSoftware(NULL), pStateVectorSoftware(NULL)
{
	for(int i=0;i<4;i++) {
		DISP_T1_TIG[i] = 0;
		DISP_T2_TIG[i] = 0;
		PROX_BASE[i] = 0;
		DISP_TMAN[i] = 0;
	}
	for (int i = 0; i < 40; i++)
	{
		T1_ILOAD_ARRAY[i] = 0.0;
		DT_ILOAD_ARRAY[i] = 0.0;
		EL_ILOAD_ARRAY[i] = 0.0;
		XOFF_ILOAD_ARRAY[i] = 0.0;
		YOFF_ILOAD_ARRAY[i] = 0.0;
		ZOFF_ILOAD_ARRAY[i] = 0.0;
		LAMB_ILOAD[i] = 1;
	}
	
	BASE_START[0] = 1;
	BASE_START[1] = 18;
	BASE_START[2] = 0;
	BASE_START[3] = 0;

	PROX_T1_STAR_STATUS = false;
	PROX_T2_STAR_STATUS = false;
	PROX_PAST_STATUS = false;
	PROX_LOAD_FLASH = false;
	PROX_ITEM_1_STATUS = false;
	PROX_ITEM_2TO20_STATUS = false;
	PROX_ITEM_21TO24_STATUS = false;
	PROX_ITEM_25_STATUS = false;
	PROX_ITEM_26_STATUS = false;
	PROX_ITEM_28_STATUS = false;
	PROX_ITEM_29_STATUS = false;
	PROX_LOAD_FLASH = false;
	USE_OMEGA_DT = false;
	USE_DISP_REL_STATE = false;
	ALARM_KILL = false;
	BACKGROUND_CALC = false;
	START_BACKGROUND = false;
	LAMB = false;
	GUID_FLAG = false;
	PROX_FIRST_PASS_STATUS = true;

	PROX_TGT_SET_NO = 0;
	MAN_TGT = 0;
	S_ROTATE = 0;
	ALARM_A = false;
	ALARM_B = false;
	ALARM_C = false;
	ALARM_D = false;

	DISP_PROX_DT = 0.0;
	DISP_EL_ANG = 0.0;
	PROX_BASE_TIME = 0.0;
	DISP_DV_MAG = 0.0;
	DISP_TMAN_TIME = 0.0;
	T1_TIG = 0.0;
	T2_TIG = 0.0;
	PROX_T_CURRENT = 0.0;
	COMP_PROX_DT = 0.0;
	TIME_PROX = 0.0;
	OMEGA_PROX = 0.0;
	EL_ANG = 0.0;
	T_MAN = 0.0;
	DSP_MISS = 0.0;
	T_OFFSET = 0.0;
	
	DISP_T1_X = _V(0, 0, 0);
	DISP_T1_XD = _V(0, 0, 0);
	DISP_T2_OFF = _V(0, 0, 0);
	DISP_DV = _V(0, 0, 0);
	COMP_T2_OFF = _V(0, 0, 0);
	DV_LVLH = _V(0, 0, 0);
	COMP_X = _V(0, 0, 0);
	COMP_XD = _V(0, 0, 0);
	R_OFFSET = _V(0, 0, 0);

	//I-Loads
	//Default target sets (Optimized R-Bar Targeted Rendezvous, 210NM)
	//NCC
	T1_ILOAD_ARRAY[8] = -57.7;
	DT_ILOAD_ARRAY[8] = 57.7;
	EL_ILOAD_ARRAY[8] = 0.0;
	XOFF_ILOAD_ARRAY[8] = -48600.0;
	YOFF_ILOAD_ARRAY[8] = 0.0;
	ZOFF_ILOAD_ARRAY[8] = 1200.0;
	LAMB_ILOAD[8] = 1;
	//Ti
	T1_ILOAD_ARRAY[9] = 0.0;
	DT_ILOAD_ARRAY[9] = 76.9;
	EL_ILOAD_ARRAY[9] = 0.0;
	XOFF_ILOAD_ARRAY[9] = -900.0;
	YOFF_ILOAD_ARRAY[9] = 0.0;
	ZOFF_ILOAD_ARRAY[9] = 1800.0;
	LAMB_ILOAD[9] = 1;
	//MC1
	T1_ILOAD_ARRAY[10] = 20.0;
	DT_ILOAD_ARRAY[10] = 56.9;
	EL_ILOAD_ARRAY[10] = 0.0;
	XOFF_ILOAD_ARRAY[10] = -900.0;
	YOFF_ILOAD_ARRAY[10] = 0.0;
	ZOFF_ILOAD_ARRAY[10] = 1800.0;
	LAMB_ILOAD[10] = 1;
	//MC2
	T1_ILOAD_ARRAY[11] = 49.9;
	DT_ILOAD_ARRAY[11] = 27.0;
	EL_ILOAD_ARRAY[11] = 29.07 * RAD;
	XOFF_ILOAD_ARRAY[11] = -900.0;
	YOFF_ILOAD_ARRAY[11] = 0.0;
	ZOFF_ILOAD_ARRAY[11] = 1800.0;
	LAMB_ILOAD[11] = 1;
	//MC3
	T1_ILOAD_ARRAY[12] = 17.0;
	DT_ILOAD_ARRAY[12] = 10.0;
	EL_ILOAD_ARRAY[12] = 0.0;
	XOFF_ILOAD_ARRAY[12] = -900.0;
	YOFF_ILOAD_ARRAY[12] = 0.0;
	ZOFF_ILOAD_ARRAY[12] = 1800.0;
	LAMB_ILOAD[12] = 1;
	//MC4
	T1_ILOAD_ARRAY[13] = 27.0;
	DT_ILOAD_ARRAY[13] = 13.0;
	EL_ILOAD_ARRAY[13] = 0.0;
	XOFF_ILOAD_ARRAY[13] = 0.0;
	YOFF_ILOAD_ARRAY[13] = 0.0;
	ZOFF_ILOAD_ARRAY[13] = 600.0;
	LAMB_ILOAD[13] = 1;
	//MC2 on time
	T1_ILOAD_ARRAY[18] = 0.0;
	DT_ILOAD_ARRAY[18] = 27.0;
	EL_ILOAD_ARRAY[18] = 0.0;
	XOFF_ILOAD_ARRAY[18] = -900.0;
	YOFF_ILOAD_ARRAY[18] = 0.0;
	ZOFF_ILOAD_ARRAY[18] = 1800.0;
	LAMB_ILOAD[18] = 1;

	EL_TOL = 0.005; //About 0.3°
	EL_DH_TOL = 10.0;
	DEL_X_GUESS[0] = 100.0;
	DEL_X_GUESS[1] = 60.0;
	DEL_X_TOL[0] = 0.0;
	DEL_X_TOL[1] = 0.0002;
	IC_MAX = 20;
	DEL_T_MAX = 900.0;
	PROX_DT_MIN = 60.0;
	PROX_DTMIN_LAMB = 60.0;
	EARTH_MU = 1.40764487566e16; //ft^3/sec^2
	EP_TRANSFER = 8.0*RAD;
	CONE = 8.0*RAD;
	DU = 0.00001*RAD; //TBD
	N_MIN = 3;
	N_MAX_ITER = 10;
	EPS_U = 1.e-6; //TBD
	R_TOL = 250.0;
	R_TOL_CW = 0.0001; //TBD
	DTMIN_I = 180.0;
	GMD_I = 4;
	GMO_I = 0; //Should be 4 but Orbiter doesn't support it
	ATM_I[0] = 1;
	ATM_I[1] = 2;
	DMP_I[0] = true;
	DMP_I[1] = true;
	VMP_I[0] = false;
	VMP_I[1] = false;

	CalculationTimer = 0.0;
}

OrbitTgtSoftware::~OrbitTgtSoftware()
{
}

void OrbitTgtSoftware::Realize()
{
	pOMSBurnSoftware = dynamic_cast<OMSBurnSoftware*>(FindSoftware("OMSBurnSoftware"));
	assert( (pOMSBurnSoftware != NULL) && "OrbitTgtSoftware::Realize.pOMSBurnSoftware" );
	pStateVectorSoftware = dynamic_cast<StateVectorSoftware*>(FindSoftware("StateVectorSoftware"));
	assert( (pStateVectorSoftware != NULL) && "OrbitTgtSoftware::Realize.pStateVectorSoftware" );

	//Calculate some display values here to save on scenario saving
	DISP_DV = DV_LVLH;
	DISP_DV_MAG = length(DISP_DV);
	DISP_TMAN_TIME = ConvertDDHHMMSSToSeconds(DISP_TMAN);
}

void OrbitTgtSoftware::ReadILOADs( const std::map<std::string,std::string>& ILOADs )
{
	unsigned short tmp[2];
	GetValILOAD( "T1_ILOAD_ARRAY", ILOADs, 40, T1_ILOAD_ARRAY );
	GetValILOAD( "DT_ILOAD_ARRAY", ILOADs, 40, DT_ILOAD_ARRAY );
	GetValILOAD( "EL_ILOAD_ARRAY", ILOADs, 40, EL_ILOAD_ARRAY );
	GetValILOAD( "XOFF_ILOAD_ARRAY", ILOADs, 40, XOFF_ILOAD_ARRAY );
	GetValILOAD( "YOFF_ILOAD_ARRAY", ILOADs, 40, YOFF_ILOAD_ARRAY );
	GetValILOAD( "ZOFF_ILOAD_ARRAY", ILOADs, 40, ZOFF_ILOAD_ARRAY );
	GetValILOAD( "PROX_DTMIN", ILOADs, PROX_DT_MIN );
	GetValILOAD( "PROX_DTMIN_LAMB", ILOADs, PROX_DTMIN_LAMB );
	GetValILOAD( "BASE_START_DAY", ILOADs, BASE_START[0] );
	GetValILOAD( "BASE_START_HR", ILOADs, BASE_START[1] );
	GetValILOAD( "BASE_START_MIN", ILOADs, BASE_START[2] );
	GetValILOAD( "BASE_START_SEC", ILOADs, BASE_START[3] );
	GetValILOAD( "EL_TOL", ILOADs, EL_TOL );
	GetValILOAD( "LAMB_ILOAD", ILOADs, 40, LAMB_ILOAD );
	GetValILOAD( "EL_DH_TOL", ILOADs, EL_DH_TOL );
	GetValILOAD( "R_TOL", ILOADs, R_TOL );
	GetValILOAD( "N_MAX_ITER", ILOADs, N_MAX_ITER );
	GetValILOAD( "CONE", ILOADs, CONE );
	GetValILOAD( "DEL_T_MAX", ILOADs, DEL_T_MAX );
	GetValILOAD( "DU", ILOADs, DU );
	GetValILOAD( "EP_TRANSFER", ILOADs, EP_TRANSFER );
	GetValILOAD( "EPS_U", ILOADs, EPS_U );
	GetValILOAD( "N_MIN", ILOADs, N_MIN );
	GetValILOAD( "DEL_X_GUESS", ILOADs, 2, DEL_X_GUESS );
	GetValILOAD( "IC_MAX", ILOADs, IC_MAX );
	GetValILOAD( "DEL_X_TOL", ILOADs, 2, DEL_X_TOL );
	GetValILOAD( "GMD_I", ILOADs, GMD_I );
	GetValILOAD( "GMO_I", ILOADs, GMO_I );
	GetValILOAD( "ATM_I", ILOADs, 2, ATM_I );
	GetValILOAD( "DTMIN_I", ILOADs, DTMIN_I );
	GetValILOAD( "DMP_I", ILOADs, 2, tmp );
	DMP_I[0] = (tmp[0] == 1);
	DMP_I[1] = (tmp[1] == 1);
	GetValILOAD( "VMP_I", ILOADs, 2, tmp );
	VMP_I[0] = (tmp[0] == 1);
	VMP_I[1] = (tmp[1] == 1);
	GetValILOAD( "R_TOL_CW", ILOADs, R_TOL_CW );
	return;
}

void OrbitTgtSoftware::OnPreStep(double simt, double simdt, double mjd)
{
	//Simulate calculation running
	if (START_BACKGROUND) //TBD: Load flash condition
	{
		CalculationTimer += simdt;

		if (CalculationTimer > 5.0)
		{
			//Background calculations are scheduled to begin
			BACKGROUND_CALC = true;
			START_BACKGROUND = false;
			CalculationTimer = 0.0;
		}
	}
	//Do actual calculation
	else if (BACKGROUND_CALC)
	{
		//Retrieve the current Orbiter and target state vectors from ON_ORB_UPP
		TIME_PROX = STS()->GetMET();
		pStateVectorSoftware->GetPropagatedStateVectors(TIME_PROX, RS_M50_PROX, VS_M50_PROX);
		pStateVectorSoftware->GetTargetStateVectors(TIME_PROX, RT_M50_PROX, VT_M50_PROX);
		RS_M50_PROX = ConvertBetweenLHAndRHFrames(RS_M50_PROX)*MPS2FPS;
		VS_M50_PROX = ConvertBetweenLHAndRHFrames(VS_M50_PROX)*MPS2FPS;
		RT_M50_PROX = ConvertBetweenLHAndRHFrames(RT_M50_PROX)*MPS2FPS;
		VT_M50_PROX = ConvertBetweenLHAndRHFrames(VT_M50_PROX)*MPS2FPS;
		//Convert the orbital angular rate from the target inertial velocity vector
		double RT_MAG = length(RT_M50_PROX);
		VECTOR3 VTAN = VT_M50_PROX - unit(RT_M50_PROX)*dotp(RT_M50_PROX, VT_M50_PROX) / RT_MAG;
		OMEGA_PROX = length(VTAN) / RT_MAG;
		ALARM_KILL = false;
		//Determine whether a Lambert or a CW calculation will be performed and call the appropiate targeting supervisory logic
		if (LAMB)
		{
			PROX_TGT_SUP_LAMB();
		}
		else
		{
			PROX_TGT_SUP();
		}
		if (ALARM_KILL)
		{
			PROX_T1_STAR_STATUS = PROX_T2_STAR_STATUS = false;
			DSP_MISS = 999999.0;
			BACKGROUND_CALC = false;
			return;
		}
		//Check again if maneuver is in the past
		PROX_STAT();
		//Call the prox ops targeting output display load to transfer the computed output data to the display buffers.
		PROX_DISP_LOAD();
		//Set the status flags off
		PROX_T1_STAR_STATUS = PROX_T2_STAR_STATUS = false;
		//Call the prox ops targeting start timer task and compute the time to the upcoming maneuver and place it in the time management buffer
		PROX_STIME();
		//Transfer the manuever execution data to the guidance buffer or array. This transfer is performed by the proximity operation guidance quantity transfer task
		PROX_TRANS();
		BACKGROUND_CALC = false;
	}
	else
	{
		//Run executive on a 1.04 Hz cycle
		CalculationTimer += simdt;

		if (CalculationTimer > 0.96)
		{
			CalculationTimer = 0.0;
			PROX_EXEC();

			//Display alarms
			if (ALARM_A || ALARM_C)
			{
				WriteCOMPOOL_IS(SCP_TGT_ITER_CREW_ALERT, 1);
			}
			else
			{
				WriteCOMPOOL_IS(SCP_TGT_ITER_CREW_ALERT, 0);
			}
			if (ALARM_B)
			{
				WriteCOMPOOL_IS(SCP_TGT_EL_ANG_CREW_ALERT, 1);
			}
			else
			{
				WriteCOMPOOL_IS(SCP_TGT_EL_ANG_CREW_ALERT, 0);
			}
			if (ALARM_D)
			{
				WriteCOMPOOL_IS(SCP_TGT_DELTA_T_CREW_ALERT, 1);
			}
			else
			{
				WriteCOMPOOL_IS(SCP_TGT_DELTA_T_CREW_ALERT, 0);
			}
		}
	}
}

bool OrbitTgtSoftware::OnMajorModeChange(unsigned int newMajorMode)
{
	if(newMajorMode == 201 || newMajorMode == 202) return true;
	return false;
}

bool OrbitTgtSoftware::ItemInput(int spec, int item, const char* Data, bool &IllegalEntry )
{
	if(spec != 34) return false;

	if (PROX_T1_STAR_STATUS || PROX_T2_STAR_STATUS)
	{
		IllegalEntry = true;
		return true;
	}

	int nValue;
	double dValue;
	switch(item) {
	case 1:
		if (GetIntegerUnsigned(Data, nValue))
		{
			if (nValue >= 1 && nValue <= 40)
			{
				PROX_TGT_SET_NO = nValue;
				PROX_ITEM_1_STATUS = true;
				PROX_ITEM_2TO20_STATUS = false;
				PROX_ITEM_21TO24_STATUS = false;
			}
			else IllegalEntry = true;
		}
		else IllegalEntry = true;
		return true;
	case 2:
	case 3:
	case 4:
	case 5:
		if (PROX_TGT_SET_NO != 0 && GetIntegerUnsigned( Data, nValue ))
		{
			if (((item == 2) && (nValue < 366)) || ((item == 3) && (nValue < 24)) || ((item == 4) && (nValue < 60)) || ((item == 5) && (nValue < 60)))
			{
				DISP_T1_TIG[item-2] = nValue;
				PROX_ITEM_2TO20_STATUS = true;
				PROX_ITEM_21TO24_STATUS = false;
			}
			else IllegalEntry = true;
		}
		else IllegalEntry = true;
		return true;
	case 6:
		if (PROX_TGT_SET_NO != 0 && GetDoubleUnsigned(Data, dValue))
		{
			if (dValue <= 359.99)
			{
				DISP_EL_ANG = dValue;
				PROX_ITEM_2TO20_STATUS = true;
				PROX_ITEM_21TO24_STATUS = false;
			}
			else IllegalEntry = true;
		}
		else IllegalEntry = true;
		return true;
	case 7:
	case 8:
	case 9:
		if (PROX_TGT_SET_NO != 0 && GetDoubleSigned(Data, dValue))
		{
			DISP_T1_X.data[item - 7] = dValue;
			PROX_ITEM_2TO20_STATUS = true;
			PROX_ITEM_21TO24_STATUS = false;
		}
		else IllegalEntry = true;
		return true;
	case 10:
	case 11:
	case 12:
		if (PROX_TGT_SET_NO != 0 && GetDoubleSigned(Data, dValue))
		{
			DISP_T1_XD.data[item - 10] = dValue;
			PROX_ITEM_2TO20_STATUS = true;
			PROX_ITEM_21TO24_STATUS = false;
		}
		else IllegalEntry = true;
		return true;
	case 13:
	case 14:
	case 15:
	case 16:
		if (PROX_TGT_SET_NO != 0 && GetIntegerUnsigned( Data, nValue ))
		{
			if (((item == 13) && (nValue < 366)) || ((item == 14) && (nValue < 24)) || ((item == 15) && (nValue < 60)) || ((item == 16) && (nValue < 60)))
			{
				DISP_T2_TIG[item-13] = nValue;
				PROX_ITEM_2TO20_STATUS = true;
				PROX_ITEM_21TO24_STATUS = false;
			}
			else IllegalEntry = true;
		}
		else IllegalEntry = true;
		return true;
	case 17:
		if (PROX_TGT_SET_NO != 0 && GetDoubleSigned( Data, dValue ))
		{
			DISP_PROX_DT = COMP_PROX_DT = dValue;
			PROX_ITEM_2TO20_STATUS = true;
			PROX_ITEM_21TO24_STATUS = false;
		}
		else IllegalEntry = true;
		return true;
	case 18:
	case 19:
	case 20:
		if (PROX_TGT_SET_NO != 0 && GetDoubleSigned( Data, dValue ))
		{
			DISP_T2_OFF.data[item-18] = dValue;
			PROX_ITEM_2TO20_STATUS = true;
			PROX_ITEM_21TO24_STATUS = false;
		}
		else IllegalEntry = true;
		return true;
	case 21:
	case 22:
	case 23:
	case 24:
		if (GetIntegerUnsigned( Data, nValue ))
		{
			if (((item == 21) && (nValue < 366)) || ((item == 22) && (nValue < 24)) || ((item == 23) && (nValue < 60)) || ((item == 24) && (nValue < 60)))
			{
				PROX_BASE[item-21] = nValue;
				PROX_ITEM_2TO20_STATUS = false;
				PROX_ITEM_21TO24_STATUS = true;
			}
			else IllegalEntry = true;
		}
		else IllegalEntry = true;
		return true;
	case 25:
		if (strlen(Data) == 0)
		{
			PROX_ITEM_25_STATUS = true;
		}
		else IllegalEntry = true;
		return true;
	case 26:
		if ((PROX_TGT_SET_NO != 0 || PROX_ITEM_21TO24_STATUS) && strlen(Data) == 0)
		{
			PROX_ITEM_26_STATUS = true;
		}
		else IllegalEntry = true;
		return true;
	case 28:
		if (strlen( Data ) == 0)
		{
			PROX_ITEM_28_STATUS = true;
		}
		else IllegalEntry = true;
		return true;
	case 29:
		if (strlen(Data) == 0)
		{
			PROX_ITEM_29_STATUS = true;
		}
		else IllegalEntry = true;
		return true;
	}

	return false;
}

bool OrbitTgtSoftware::OnPaint(int spec, vc::MDU* pMDU) const
{
	if (spec != 34) return false;

	char cbuf[51];

	PrintCommonHeader("   ORBIT TGT", pMDU);

	if (PROX_PAST_STATUS == false && T_MAN > 0.0)
	{
		int timeDiff = max(0, static_cast<int>(DISP_TMAN_TIME - STS()->GetMET() + 1));
		int TIMER[4];

		TIMER[0] = timeDiff / 86400;
		TIMER[1] = (timeDiff - TIMER[0] * 86400) / 3600;
		TIMER[2] = (timeDiff - TIMER[0] * 86400 - TIMER[1] * 3600) / 60;
		TIMER[3] = timeDiff - TIMER[0] * 86400 - TIMER[1] * 3600 - TIMER[2] * 60;
		sprintf_s(cbuf, 51, "%03d/%02d:%02d:%02d", abs(TIMER[0]), abs(TIMER[1]), abs(TIMER[2]), abs(TIMER[3]));
		pMDU->mvprint(38, 1, cbuf);
	}

	pMDU->mvprint(1, 2, "MNVR");
	pMDU->mvprint(11, 2, "TIG");
	pMDU->Delta(22, 2);
	pMDU->mvprint(23, 2, "VX");
	pMDU->Delta(29, 2);
	pMDU->mvprint(30, 2, "VY");
	pMDU->Delta(36, 2);
	pMDU->mvprint(37, 2, "VZ");
	pMDU->Delta(44, 2);
	pMDU->mvprint(45, 2, "VT");
	pMDU->mvprint(25, 4, "PRED MATCH=");

	sprintf_s(cbuf, 51, "%02d", MAN_TGT);
	pMDU->mvprint(1, 3, cbuf);

	if (PROX_PAST_STATUS) pMDU->mvprint(4, 3, "*");
	sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_TMAN[0], DISP_TMAN[1], DISP_TMAN[2], DISP_TMAN[3]);
	pMDU->mvprint(6, 3, cbuf);
	sprintf_s(cbuf, 51, "%5.1f", min(999.9,fabs(DISP_DV.x)));
	pMDU->mvprint(21, 3, cbuf);
	pMDU->NumberSign(20, 3, DISP_DV.x);
	sprintf_s(cbuf, 51, "%4.1f", min(99.9,fabs(DISP_DV.y)));
	pMDU->mvprint(29, 3, cbuf);
	pMDU->NumberSign(28, 3, DISP_DV.y);
	sprintf_s(cbuf, 51, "%4.1f", min(99.9,fabs(DISP_DV.z)));
	pMDU->mvprint(36, 3, cbuf);
	pMDU->NumberSign(35, 3, DISP_DV.z);
	sprintf_s(cbuf, 51, "%5.1f", min(999.9,fabs(DISP_DV_MAG)));
	pMDU->mvprint(43, 3, cbuf);
	pMDU->NumberSign(42, 3, DISP_DV_MAG);

	sprintf_s(cbuf, 51, "%7.0f", DSP_MISS);
	pMDU->mvprint(37, 4, cbuf);

	pMDU->mvprint(1, 6, "INPUTS");
	pMDU->mvprint(1, 7, "1 TGT NO");
	sprintf_s(cbuf, 51, "%02d", PROX_TGT_SET_NO);
	pMDU->mvprint(23, 7, cbuf);
	pMDU->mvprint(1, 8, "2 T1 TIG");
	sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_T1_TIG[0], DISP_T1_TIG[1], DISP_T1_TIG[2], DISP_T1_TIG[3]);
	pMDU->mvprint(13, 8, cbuf);
	pMDU->Underline(13, 8);
	pMDU->Underline(14, 8);
	pMDU->Underline(15, 8);
	pMDU->Underline(17, 8);
	pMDU->Underline(18, 8);
	pMDU->Underline(20, 8);
	pMDU->Underline(21, 8);
	pMDU->Underline(23, 8);
	pMDU->Underline(24, 8);
	pMDU->mvprint(1, 9, "6   EL");
	sprintf_s(cbuf, 51, "%06.2f", DISP_EL_ANG);
	pMDU->mvprint(19, 9, cbuf);
	pMDU->mvprint(1, 10, "7    X/DNRN");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T1_X.x));
	pMDU->mvprint(19, 10, cbuf);
	pMDU->NumberSignBracket(18, 10, DISP_T1_X.x);
	pMDU->mvprint(1, 11, "8    Y");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T1_X.y));
	pMDU->mvprint(19, 11, cbuf);
	pMDU->NumberSignBracket(18, 11, DISP_T1_X.y);
	pMDU->mvprint(1, 12, "9    Z/ H");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T1_X.z));
	pMDU->mvprint(19, 12, cbuf);
	pMDU->NumberSignBracket(18, 12, DISP_T1_X.z);
	pMDU->Delta(8, 12);
	for (int y = 13;y <= 15;y++) pMDU->DotCharacter(6, y);
	pMDU->mvprint(0, 13, "10    X");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T1_XD.x));
	pMDU->mvprint(19, 13, cbuf);
	pMDU->NumberSignBracket(18, 13, DISP_T1_XD.x);
	pMDU->mvprint(0, 14, "11    Y");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T1_XD.y));
	pMDU->mvprint(19, 14, cbuf);
	pMDU->NumberSignBracket(18, 14, DISP_T1_XD.y);
	pMDU->mvprint(0, 15, "12    Z");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T1_XD.z));
	pMDU->mvprint(19, 15, cbuf);
	pMDU->NumberSignBracket(18, 15, DISP_T1_XD.z);
	for (int y = 10;y <= 15;y++) pMDU->Delta(5, y);
	pMDU->mvprint(0, 16, "13 T2 TIG");
	sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_T2_TIG[0], DISP_T2_TIG[1], DISP_T2_TIG[2], DISP_T2_TIG[3]);
	pMDU->mvprint(13, 16, cbuf);
	pMDU->Underline(13, 16);
	pMDU->Underline(14, 16);
	pMDU->Underline(15, 16);
	pMDU->Underline(17, 16);
	pMDU->Underline(18, 16);
	pMDU->Underline(20, 16);
	pMDU->Underline(21, 16);
	pMDU->Underline(23, 16);
	pMDU->Underline(24, 16);
	pMDU->mvprint(0, 17, "17    T");
	sprintf_s(cbuf, 51, "%5.1f", fabs(DISP_PROX_DT));
	pMDU->mvprint(19, 17, cbuf);
	pMDU->NumberSignBracket(18, 17, DISP_PROX_DT);
	pMDU->Underline(19, 17);
	pMDU->Underline(20, 17);
	pMDU->Underline(21, 17);
	pMDU->Underline(22, 17);
	pMDU->Underline(23, 17);
	pMDU->mvprint(0, 18, "18    X");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T2_OFF.x));
	pMDU->mvprint(19, 18, cbuf);
	pMDU->NumberSignBracket(18, 18, DISP_T2_OFF.x);
	pMDU->Underline(19, 18);
	pMDU->Underline(20, 18);
	pMDU->Underline(21, 18);
	pMDU->Underline(22, 18);
	pMDU->Underline(23, 18);
	pMDU->Underline(24, 18);
	pMDU->mvprint(0, 19, "19    Y");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T2_OFF.y));
	pMDU->mvprint(19, 19, cbuf);
	pMDU->NumberSignBracket(18, 19, DISP_T2_OFF.y);
	pMDU->mvprint(0, 20, "20    Z");
	sprintf_s(cbuf, 51, "%6.2f", fabs(DISP_T2_OFF.z));
	pMDU->mvprint(19, 20, cbuf);
	pMDU->NumberSignBracket(18, 20, DISP_T2_OFF.z);
	for (int y = 17;y <= 20;y++) pMDU->Delta(5, y);
	pMDU->mvprint(0, 21, "21 BASE TIME");
	sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", PROX_BASE[0], PROX_BASE[1], PROX_BASE[2], PROX_BASE[3]);
	pMDU->mvprint(13, 21, cbuf);
	pMDU->Underline(13, 21);
	pMDU->Underline(14, 21);
	pMDU->Underline(15, 21);
	pMDU->Underline(17, 21);
	pMDU->Underline(18, 21);
	pMDU->Underline(20, 21);
	pMDU->Underline(21, 21);
	pMDU->Underline(23, 21);
	pMDU->Underline(24, 21);

	pMDU->mvprint(37, 6, "CONTROLS");
	pMDU->mvprint(38, 7, "T2 TO T1  25");
	if (PROX_LOAD_FLASH)
	{
		pMDU->mvprint(38, 8, "LOAD", dps::DEUATT_FLASHING);
	}
	else
	{
		pMDU->mvprint(38, 8, "LOAD");
	}
	pMDU->mvprint(48, 8, "26");
	pMDU->mvprint(37, 9, "COMPUTE T1 28");
	if (PROX_T1_STAR_STATUS) pMDU->mvprint(50, 9, "*");
	pMDU->mvprint(37, 10, "COMPUTE T2 29");
	if (PROX_T2_STAR_STATUS) pMDU->mvprint(50, 10, "*");
	return true;
}

bool OrbitTgtSoftware::OnParseLine(const char* keyword, const char* value)
{
	if (!_strnicmp(keyword, "DISPLAY_FLAGS", 13)) {
		int itemp[12];
		sscanf_s(value, "%d %d %d %d %d %d %d %d %d %d %d %d", &itemp[0], &itemp[1], &itemp[2], &itemp[3], &itemp[4], &itemp[5], &itemp[6], &itemp[7], &itemp[8], &itemp[9], &itemp[10], &itemp[11]);
		PROX_T1_STAR_STATUS = (itemp[0] != 0);
		PROX_T2_STAR_STATUS = (itemp[1] != 0);
		PROX_PAST_STATUS = (itemp[2] != 0);
		PROX_ITEM_1_STATUS = (itemp[3] != 0);
		PROX_ITEM_2TO20_STATUS = (itemp[4] != 0);
		PROX_ITEM_21TO24_STATUS = (itemp[5] != 0);
		PROX_ITEM_25_STATUS = (itemp[6] != 0);
		PROX_ITEM_26_STATUS = (itemp[7] != 0);
		PROX_ITEM_28_STATUS = (itemp[8] != 0);
		PROX_ITEM_29_STATUS = (itemp[9] != 0);
		PROX_LOAD_FLASH = (itemp[10] != 0);
		PROX_FIRST_PASS_STATUS = (itemp[11] != 0);
		return true;
	}
	else if (!_strnicmp(keyword, "OTHER_FLAGS", 11)) {
		int itemp[9];
		sscanf_s(value, "%d %d %d %d %d %d %d %d %d", &itemp[0], &itemp[1], &itemp[2], &itemp[3], &itemp[4], &itemp[5], &itemp[6], &itemp[7], &itemp[8]);
		USE_OMEGA_DT = (itemp[0] != 0);
		USE_DISP_REL_STATE = (itemp[1] != 0);
		LAMB = (itemp[2] != 0);
		ALARM_A = (itemp[3] != 0);
		ALARM_B = (itemp[4] != 0);
		ALARM_C = (itemp[5] != 0);
		ALARM_D = (itemp[6] != 0);
		BACKGROUND_CALC = (itemp[7] != 0);
		START_BACKGROUND = (itemp[8] != 0);
	}
	else if(!_strnicmp(keyword, "DISP_T1_TIG", 11)) {
		sscanf_s(value, "%lf%lf%lf%lf", &DISP_T1_TIG[0], &DISP_T1_TIG[1], &DISP_T1_TIG[2], &DISP_T1_TIG[3]);
		return true;
	}
	else if (!_strnicmp(keyword, "DISP_T2_TIG", 11)) {
		sscanf_s(value, "%lf%lf%lf%lf", &DISP_T2_TIG[0], &DISP_T2_TIG[1], &DISP_T2_TIG[2], &DISP_T2_TIG[3]);
		return true;
	}
	else if (!_strnicmp(keyword, "BASE_TIME", 9)) {
		sscanf_s(value, "%lf%lf%lf%lf", &PROX_BASE[0], &PROX_BASE[1], &PROX_BASE[2], &PROX_BASE[3]);
		return true;
	}
	else if (!_strnicmp(keyword, "DISP_TMAN", 9)) {
		sscanf_s(value, "%lf%lf%lf%lf", &DISP_TMAN[0], &DISP_TMAN[1], &DISP_TMAN[2], &DISP_TMAN[3]);
		return true;
	}
	else if (!_strnicmp(keyword, "INTS", 4)) {
		sscanf_s(value, "%d %d", &PROX_TGT_SET_NO, &MAN_TGT);
		return true;
	}
	else if (!_strnicmp(keyword, "TARGETDATA", 10)) {
		LoadTargetData(value);
		return true;
	}

	LOAD_DOUBLE("DISP_PROX_DT", DISP_PROX_DT);
	LOAD_DOUBLE("DISP_EL_ANG", DISP_EL_ANG);
	LOAD_DOUBLE("DSP_MISS", DSP_MISS);
	LOAD_DOUBLE("T1_TIG", T1_TIG);
	LOAD_DOUBLE("T2_TIG", T2_TIG);
	LOAD_DOUBLE("PROX_BASE_TIME", PROX_BASE_TIME);
	LOAD_DOUBLE("COMP_PROX_DT", COMP_PROX_DT);
	LOAD_DOUBLE("TIME_PROX", TIME_PROX);
	LOAD_DOUBLE("EL_ANG", EL_ANG);
	LOAD_DOUBLE("T_MAN", T_MAN);
	LOAD_DOUBLE("CalculationTimer", CalculationTimer);
	LOAD_V3("DISP_T1_X", DISP_T1_X);
	LOAD_V3("DISP_T1_XD", DISP_T1_XD);
	LOAD_V3("DISP_T2_OFF", DISP_T2_OFF);
	LOAD_V3("DV_LVLH", DV_LVLH);
	LOAD_V3("COMP_T2_OFF", COMP_T2_OFF);
	LOAD_V3("COMP_X", COMP_X);
	LOAD_V3("COMP_XD", COMP_XD);
	return false;
}

void OrbitTgtSoftware::OnSaveState(FILEHANDLE scn) const
{
	char cbuf[256];
	sprintf_s(cbuf, 255, "%d %d %d %d %d %d %d %d %d %d %d %d", PROX_T1_STAR_STATUS, PROX_T2_STAR_STATUS, PROX_PAST_STATUS, PROX_ITEM_1_STATUS, PROX_ITEM_2TO20_STATUS,
		PROX_ITEM_21TO24_STATUS, PROX_ITEM_25_STATUS, PROX_ITEM_26_STATUS, PROX_ITEM_28_STATUS, PROX_ITEM_29_STATUS, PROX_LOAD_FLASH, PROX_FIRST_PASS_STATUS);
	oapiWriteScenario_string(scn, "DISPLAY_FLAGS", cbuf);
	sprintf_s(cbuf, 255, "%d %d %d %d %d %d %d %d %d", USE_OMEGA_DT, USE_DISP_REL_STATE, LAMB, ALARM_A, ALARM_B, ALARM_C, ALARM_D, BACKGROUND_CALC, START_BACKGROUND);
	oapiWriteScenario_string(scn, "OTHER_FLAGS", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", DISP_T1_TIG[0], DISP_T1_TIG[1], DISP_T1_TIG[2], DISP_T1_TIG[3]);
	oapiWriteScenario_string(scn, "DISP_T1_TIG", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", DISP_T2_TIG[0], DISP_T2_TIG[1], DISP_T2_TIG[2], DISP_T2_TIG[3]);
	oapiWriteScenario_string(scn, "DISP_T2_TIG", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", PROX_BASE[0], PROX_BASE[1], PROX_BASE[2], PROX_BASE[3]);
	oapiWriteScenario_string(scn, "BASE_TIME", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", DISP_TMAN[0], DISP_TMAN[1], DISP_TMAN[2], DISP_TMAN[3]);
	oapiWriteScenario_string(scn, "DISP_TMAN", cbuf);
	sprintf_s(cbuf, 255, "%d %d", PROX_TGT_SET_NO, MAN_TGT);
	oapiWriteScenario_string(scn, "INTS", cbuf);

	oapiWriteScenario_float(scn, "DISP_PROX_DT", DISP_PROX_DT);
	oapiWriteScenario_float(scn, "DISP_EL_ANG", DISP_EL_ANG);
	oapiWriteScenario_float(scn, "DSP_MISS", DSP_MISS);
	oapiWriteScenario_float(scn, "T1_TIG", T1_TIG);
	oapiWriteScenario_float(scn, "T2_TIG", T2_TIG);
	oapiWriteScenario_float(scn, "PROX_BASE_TIME", PROX_BASE_TIME);
	oapiWriteScenario_float(scn, "COMP_PROX_DT", COMP_PROX_DT);
	oapiWriteScenario_float(scn, "TIME_PROX", TIME_PROX);
	oapiWriteScenario_float(scn, "EL_ANG", EL_ANG);
	oapiWriteScenario_float(scn, "T_MAN", T_MAN);
	oapiWriteScenario_float(scn, "CalculationTimer", CalculationTimer);

	oapiWriteScenario_vec(scn, "DISP_T1_X", DISP_T1_X);
	oapiWriteScenario_vec(scn, "DISP_T1_XD", DISP_T1_XD);
	oapiWriteScenario_vec(scn, "DISP_T2_OFF", DISP_T2_OFF);
	oapiWriteScenario_vec(scn, "DV_LVLH", DV_LVLH);
	oapiWriteScenario_vec(scn, "COMP_T2_OFF", COMP_T2_OFF);
	oapiWriteScenario_vec(scn, "COMP_X", COMP_X);
	oapiWriteScenario_vec(scn, "COMP_XD", COMP_XD);

	for (unsigned int i = 0;i < 40;i++)
	{
		SaveTargetData(cbuf, i);
		oapiWriteScenario_string(scn, "TARGETDATA", cbuf);
	}
}

void OrbitTgtSoftware::SaveTargetData(char *buf, unsigned int i) const
{
	sprintf_s(buf, 256, "%d %lf %lf %lf %lf %lf %lf %d", i, T1_ILOAD_ARRAY[i], EL_ILOAD_ARRAY[i], XOFF_ILOAD_ARRAY[i], YOFF_ILOAD_ARRAY[i], ZOFF_ILOAD_ARRAY[i], DT_ILOAD_ARRAY[i], LAMB_ILOAD[i]);
}

void OrbitTgtSoftware::LoadTargetData(const char *val)
{
	unsigned int i = 0;
	double T1_TIG = 0.0;
	double elevation = 0.0;
	double finalOffsetX = 0.0;
	double finalOffsetY = 0.0;
	double finalOffsetZ = 0.0;
	double transferTime = 0.0;
	int itemp = true;
	sscanf_s(val, "%d %lf %lf %lf %lf %lf %lf %d", &i, &T1_TIG, &elevation, &finalOffsetX, &finalOffsetY, &finalOffsetZ, &transferTime, &itemp);

	T1_ILOAD_ARRAY[i] = T1_TIG;
	EL_ILOAD_ARRAY[i] = elevation;
	XOFF_ILOAD_ARRAY[i] = finalOffsetX;
	YOFF_ILOAD_ARRAY[i] = finalOffsetY;
	ZOFF_ILOAD_ARRAY[i] = finalOffsetZ;
	DT_ILOAD_ARRAY[i] = transferTime;
	LAMB_ILOAD[i] = (itemp == 0) ? 0 : 1;
}

void OrbitTgtSoftware::PROX_EXEC()
{
	//First pass
	if (PROX_FIRST_PASS_STATUS)
	{
		//Set the prox base time to the I–load values by setting up the inputs and calling the time conversion task
		PROX_BASE_TIME = ConvertDDHHMMSSToSeconds(BASE_START);
		//Put the base time into the display
		PROX_BASE[0] = BASE_START[0];
		PROX_BASE[1] = BASE_START[1];
		PROX_BASE[2] = BASE_START[2];
		PROX_BASE[3] = BASE_START[3];
		//Initialize T1_TIG and T2_TIG
		T1_TIG = 0.0;
		T2_TIG = 0.0;
		//Initialize the compute in progress status flags
		PROX_T1_STAR_STATUS = PROX_T2_STAR_STATUS = false;
		START_BACKGROUND = false;
		BACKGROUND_CALC = false;
		//Set the first pass status off
		PROX_FIRST_PASS_STATUS = false;
	}

	//Perform a logic test to determine if the crew made and entry to items 21-24
	if (PROX_ITEM_21TO24_STATUS)
	{
		PROX_LOAD_FLASH = true;
	}

	//Call the proximity operations targeting status task to set the maneuver status flag to on or off position if the maneuver TIG time is prior to or past current time.
	PROX_STAT();
	//Perform a logic test to determine if the crew has made an entry to item 1
	if (PROX_ITEM_1_STATUS)
	{
		PROX_TGT_SEL();
		PROX_ITEM_1_STATUS = false;
	}
	//Perform a logic test to determine if the crew executed item 25
	if (PROX_ITEM_25_STATUS)
	{
		//Transfer the T2 maneuver time data in the computation buffer to the T1 maneuver time computational buffer slots
		T1_TIG = T2_TIG;
		//Transfer the T2 maneuver time data in the computation buffer to the T1 maneuvder time display buffer slots
		ConvertSecondsToDDHHMMSS(T1_TIG, DISP_T1_TIG);
		//Set the status flag to off
		PROX_ITEM_25_STATUS = false;
	}
	//Perform a logic test to determine if the crew made any entries to items 2 through 20
	if (PROX_ITEM_2TO20_STATUS)
	{
		PROX_LOAD_FLASH = true;
	}
	//Perform a logic test to determine if the crew made any entries to item 26
	if (PROX_ITEM_26_STATUS)
	{
		//Convert the input data display buffer items and store in the computational data buffers and the I-load data buffers
		//The conversion is performed by the proximity operations targeting initialization task
		PROX_INIT();
		//Set status flags to off condition
		PROX_ITEM_2TO20_STATUS = PROX_ITEM_21TO24_STATUS = PROX_ITEM_26_STATUS = PROX_LOAD_FLASH = false;
	}
	//Perform a logic test to determine if the crew executed item 28
	if (PROX_ITEM_28_STATUS)
	{
		if (COMP_PROX_DT == 0 && T2_TIG == 0)
		{
			ALARM_D = true;
		}
		else
		{
			//Set the compute T1 star status flag to on
			PROX_T1_STAR_STATUS = true;
			//Perform a logic test to see if all of the display buffers for T1 relative state are blank (items 7-12), or if the T1 maneuver time is in the past (T1_TIG < PROX_T_CURRENT)
			if ((COMP_X.x == 0.0 && COMP_X.y == 0.0 && COMP_X.z == 0.0 && COMP_XD.x == 0.0 && COMP_XD.y == 0.0 && COMP_XD.z == 0.0) || T1_TIG < PROX_T_CURRENT)
			{
				USE_DISP_REL_STATE = false;
			}
			else
			{
				USE_DISP_REL_STATE = true;
			}
		}
		//Set the item 28 status to off
		PROX_ITEM_28_STATUS = false;
	}
	//Perform a logical test to determine if the crew executed item 29
	if (PROX_ITEM_29_STATUS)
	{
		//Set the compute T2 star status flag to on
		PROX_T2_STAR_STATUS = true;
		//Set the use relative display to off
		USE_DISP_REL_STATE = false;
		//Set the item 29 status to off
		PROX_ITEM_29_STATUS = false;
	}
	//Perform a logic test to determine if the compute T1 or compute T2 solutions were requested and if no targeting calculations are presently done
	if ((PROX_T1_STAR_STATUS || PROX_T2_STAR_STATUS) && BACKGROUND_CALC == false)
	{
		START_BACKGROUND = true;
	}
}

void OrbitTgtSoftware::PROX_STAT()
{
	//Get current time
	PROX_T_CURRENT = STS()->GetMET();
	//Perform a logic test to determine if the maneuver exists and if it is in the past
	if (T_MAN >= 0 && PROX_T_CURRENT > T_MAN)
	{
		PROX_PAST_STATUS = true;
	}
	else
	{
		PROX_PAST_STATUS = false;
	}
}

void OrbitTgtSoftware::PROX_TGT_SEL()
{
	//Load the computational data buffers
	int I_INDEX = PROX_TGT_SET_NO - 1;
	T1_TIG = PROX_BASE_TIME + T1_ILOAD_ARRAY[I_INDEX] * 60.0;
	COMP_PROX_DT = DT_ILOAD_ARRAY[I_INDEX];
	EL_ANG = EL_ILOAD_ARRAY[I_INDEX];
	COMP_T2_OFF.x = XOFF_ILOAD_ARRAY[I_INDEX];
	COMP_T2_OFF.y = YOFF_ILOAD_ARRAY[I_INDEX];
	COMP_T2_OFF.z = ZOFF_ILOAD_ARRAY[I_INDEX];
	LAMB = (LAMB_ILOAD[I_INDEX] == 1);

	//Load the display and computation buffers for T1 relative position and T2 time with blanks
	DISP_T2_TIG[0] = DISP_T2_TIG[1] = DISP_T2_TIG[2] = DISP_T2_TIG[3] = 0.0;
	DISP_T1_X = _V(0, 0, 0);
	DISP_T1_XD = _V(0, 0, 0);
	COMP_X = _V(0, 0, 0);
	COMP_XD = _V(0, 0, 0);
	//Convert the computational T1 maneuver time (which is in MET) to days, hours, minutes and seconds
	ConvertSecondsToDDHHMMSS(T1_TIG, DISP_T1_TIG);
	//Load the display data buffers
	DISP_PROX_DT = DT_ILOAD_ARRAY[I_INDEX];
	DISP_EL_ANG = EL_ILOAD_ARRAY[I_INDEX] * DEG;
	DISP_T2_OFF.x = XOFF_ILOAD_ARRAY[I_INDEX] / 1000.0;
	DISP_T2_OFF.y = YOFF_ILOAD_ARRAY[I_INDEX] / 1000.0;
	DISP_T2_OFF.z = ZOFF_ILOAD_ARRAY[I_INDEX] / 1000.0;
}

void OrbitTgtSoftware::PROX_INIT()
{
	//Did crew request a change to the base time (PROX_ITEM_21T024_STATUS = ON)? If so, put the displayed base time into the computational buffer
	if (PROX_ITEM_21TO24_STATUS || PROX_ITEM_2TO20_STATUS == false)
	{
		PROX_BASE_TIME = ConvertDDHHMMSSToSeconds(PROX_BASE);
	}
	if (PROX_ITEM_2TO20_STATUS || PROX_ITEM_21TO24_STATUS == false)
	{
		//Load the offset position and delta-t computation buffers and I-load buffers. The I-load buffers index value is determined by the selected
		//target set(I INDEX = PROX_TGT_SET NO)
		int I_INDEX = PROX_TGT_SET_NO - 1;
		COMP_T2_OFF = DISP_T2_OFF * 1e3;
		COMP_PROX_DT = DISP_PROX_DT;
		EL_ANG = DISP_EL_ANG * RAD;
		XOFF_ILOAD_ARRAY[I_INDEX] = DISP_T2_OFF.x * 1000.0;
		YOFF_ILOAD_ARRAY[I_INDEX] = DISP_T2_OFF.y * 1000.0;
		ZOFF_ILOAD_ARRAY[I_INDEX] = DISP_T2_OFF.z * 1000.0;
		DT_ILOAD_ARRAY[I_INDEX] = DISP_PROX_DT;
		EL_ILOAD_ARRAY[I_INDEX] = EL_ANG;
		//Load the computation relative position and velocity buffers
		COMP_X = DISP_T1_X * 1e3;
		COMP_XD = DISP_T1_XD;
		//Convert the display T1 time and display T2 time and load the computation and I-load buffers
		T1_TIG = ConvertDDHHMMSSToSeconds(DISP_T1_TIG);
		T1_ILOAD_ARRAY[I_INDEX] = (T1_TIG - PROX_BASE_TIME) / 60.0;
		TIME_PROX = T1_TIG;
		T2_TIG = ConvertDDHHMMSSToSeconds(DISP_T2_TIG);
	}
}

void OrbitTgtSoftware::PROX_TRANS()
{
	if (PROX_PAST_STATUS == false)
	{
		//TBD: Also transfer S_ROTATE, R_OFFSET and T_OFFSET if GUID_FLAG = ON
		pOMSBurnSoftware->SetManeuverData(DISP_TMAN_TIME, DV_LVLH);
	}
}

void OrbitTgtSoftware::PROX_TGT_SUP()
{
	double TIG_MIN;

	//Common
	//Differential drag acceleration magnitude
	double DIFF_DR;
	//LVLH curvilinear position vector from REL_COMP
	VECTOR3 R_REL;
	//LVLH curvilinear velocity vector from REL_COMP
	VECTOR3 V_REL;
	//Input Shuttle inertial position for REL_COMP
	VECTOR3 R_S_INER;
	//Input Shuttle inertial velocity for REL_COMP
	VECTOR3 V_S_INER;
	//Input target inertial position for REL_COMP
	VECTOR3 R_T_INER;
	//Input target inertial velocity for REL_COMP
	VECTOR3 V_T_INER;
	//Delta-velocity vector for OFFSET_TGT
	VECTOR3 DV;

	ALARM_C = false;
	ALARM_D = false;

	//Compute minimum time to ignition
	TIG_MIN = PROX_T_CURRENT + PROX_DT_MIN;
	//Did the crew request the compute T1 function?
	if (PROX_T1_STAR_STATUS == false)
	{
		//Compute the T2 maneuver
		if (T2_TIG < TIG_MIN)
		{
			T2_TIG = TIG_MIN;
		}
		//Update the present relative state to T2_TIG
		//S and T are inversed on purpose below!
		UPDATVP(1, RS_M50_PROX, VS_M50_PROX, TIME_PROX, T2_TIG, R_T_INER, V_T_INER);
		UPDATVP(2, RT_M50_PROX, VT_M50_PROX, TIME_PROX, T2_TIG, R_S_INER, V_S_INER);

		REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);

		DV_LVLH = V_REL;
		T_MAN = T2_TIG;
		DSP_MISS = 0.0;
	}
	else
	{
		//Compute T1 maneuver
		//Compute the transfer time and T2_TIG
		DT_COMP(T1_TIG, T2_TIG, COMP_PROX_DT);
		if (T1_TIG < TIG_MIN)
		{
			T1_TIG = TIG_MIN;
			if (USE_OMEGA_DT == false)
			{
				COMP_PROX_DT = (T2_TIG - T1_TIG) / 60.0;
			}
			USE_DISP_REL_STATE = false;
		}

		VECTOR3 DRAG_ACCEL_ORB, DRAG_ACCEL_TGT, R_ORB1, V_ORB1, R_TGT1, V_TGT1, R_TGT2, V_TGT2;

		//Propagate states inertially to T1_TIG and compute differential drag
		UPDATVP(1, RS_M50_PROX, VS_M50_PROX, TIME_PROX, T1_TIG, R_S_INER, V_S_INER);
		DRAG_ACCEL_ORB = _V(0, 0, 0); //TBD
		UPDATVP(2, RT_M50_PROX, VT_M50_PROX, TIME_PROX, T1_TIG, R_T_INER, V_T_INER);
		DRAG_ACCEL_TGT = _V(0, 0, 0); //TBD
		R_TGT1 = R_T_INER;
		V_TGT1 = V_T_INER;
		DIFF_DR = length(DRAG_ACCEL_TGT - DRAG_ACCEL_ORB);

		if (USE_DISP_REL_STATE == false)
		{
			REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
			COMP_X = R_REL;
			COMP_XD = V_REL;
		}
		else
		{
			R_REL = COMP_X;
			V_REL = COMP_XD;
			REL_COMP(false, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
		}

		//Display the expected state at T1_TIG
		DISP_T1_X = COMP_X / 1000.0;
		DISP_T1_XD = COMP_XD;

		R_ORB1 = R_S_INER;
		V_ORB1 = V_S_INER;

		if (USE_OMEGA_DT)
		{
			//Compute this information instead by use of the WT-calculation
			OMEGA_DT_COMP();
			if (ALARM_KILL == false)
			{
				//Compute T2_TIG
				T2_TIG = T1_TIG + 60.0*COMP_PROX_DT;
			}
		}

		if (ALARM_KILL)
		{
			GUID_FLAG = false;
			return;
		}

		//Target at T2
		UPDATVP(2, R_T_INER, V_T_INER, T1_TIG, T2_TIG, R_TGT2, V_TGT2);

		VECTOR3 DV_INER, DV_REQ_R, XD_OFF, X_OFF, X2_OFF, VS_REQ, ERR_Q;
		double D_MISS1, D_MISS2, DT_OFF, R_MAX, ERR, DV_MAG;
		int I_LOW, N;

		I_LOW = 0;
		N = 0;
		D_MISS1 = 1.0e6;
		D_MISS2 = 2.0e6;
		DV_REQ_R = _V(0, 0, 0);
		XD_OFF = COMP_XD;
		X_OFF = COMP_X;
		X2_OFF = COMP_T2_OFF;
		DT_OFF = COMP_PROX_DT;
		R_MAX = R_TOL_CW * length(X2_OFF);
		if (R_MAX > 1000.0)
		{
			R_MAX = 1000.0;
		}
		if (R_MAX < 1.0)
		{
			R_MAX = 1.0;
		}
		do
		{
			//Compute velocity required to get from X_OFF to X2_OFF in DT_OFF
			OFFSET_TGT(X_OFF, XD_OFF, X2_OFF, DT_OFF, DIFF_DR, DV);
			//If error, stop iterations
			if (ALARM_KILL)
			{
				GUID_FLAG = false;
				return;
			}
			DV_REQ_R = DV_REQ_R + DV;
			//Convert post-maneuver relative state to an orbiter inertial state
			V_REL = DV_REQ_R + COMP_XD;
			REL_COMP(false, R_TGT1, V_TGT1, R_S_INER, V_S_INER, COMP_X, V_REL);
			VS_REQ = V_S_INER;
			//Propagate orbiter state to T2_TIG
			UPDATVP(1, R_S_INER, V_S_INER, T1_TIG, T2_TIG, R_S_INER, V_S_INER);
			//Convert to a relative state centered at the target
			REL_COMP(true, R_TGT2, V_TGT2, R_S_INER, V_S_INER, R_REL, V_REL);
			//Compute the relative state miss vector and then the error magnitude
			ERR_Q = COMP_T2_OFF - R_REL;
			ERR = length(ERR_Q);
			DSP_MISS = ERR;
			//Check for divergence. Divergence is determined by two subsequently increasing miss distances.
			if (ERR > D_MISS1 && D_MISS1 > D_MISS2)
			{
				ALARM_C = true;
				break;
			}
			D_MISS2 = D_MISS1;
			D_MISS1 = ERR;
			//Check to see if the changes to the maneuver are small. Stop iterations if three consectuive iterations each change DV by less than 0.05 fps
			DV_MAG = length(DV);
			if (DV_MAG >= 0.05)
			{
				I_LOW = 0;
			}
			else
			{
				I_LOW++;
			}
			if (I_LOW >= 3)
			{
				break;
			}
			if (ERR > R_MAX && N < N_MAX_ITER)
			{
				X_OFF = _V(0, 0, 0);
				XD_OFF = _V(0, 0, 0);
				X2_OFF = ERR_Q;
				N++;
				DIFF_DR = 0.0;
			}
		} while (N < N_MAX_ITER && ERR > R_MAX);

		if (N >= N_MAX_ITER) ALARM_C = true;
		DV_INER = VS_REQ - V_ORB1;
		DV_LVLH = ORBLV(R_ORB1, V_ORB1, DV_INER);
		T_MAN = T1_TIG;
	}
	GUID_FLAG = false;
}

void OrbitTgtSoftware::PROX_TGT_SUP_LAMB()
{
	//Internal variables
	double TIG_MIN;
	//Common
	//Inertial position vector of Shuttle at T1_TIG for PREVR
	VECTOR3 RS_T1TIG;
	//Inertial position velocity of Shuttle at T1_TIG for PREVR
	VECTOR3 VS_T1TIG;
	//Inertial position vector of Shuttle at T2_TIG for PREVR
	VECTOR3 RS_T2TIG;
	//Predicted time of TPI (MET)
	double TTPI;
	//LVLH curvilinear position vector from REL_COMP
	VECTOR3 R_REL;
	//LVLH curvilinear velocity vector from REL_COMP
	VECTOR3 V_REL;
	//Input Shuttle inertial position for REL_COMP
	VECTOR3 R_S_INER;
	//Input Shuttle inertial velocity for REL_COMP
	VECTOR3 V_S_INER;
	//Input target inertial position for REL_COMP
	VECTOR3 R_T_INER;
	//Input target inertial velocity for REL_COMP
	VECTOR3 V_T_INER;

	ALARM_A = false;
	ALARM_B = false;
	ALARM_D = false;

	//Compute minimum time to ignition
	TIG_MIN = PROX_T_CURRENT + PROX_DTMIN_LAMB;
	//Check compute T1 flag
	if (PROX_T1_STAR_STATUS == false)
	{
		//Compute the T2 maneuver
		if (T2_TIG < TIG_MIN)
		{
			T2_TIG = TIG_MIN;
		}
		//Update Shuttle and target inertial states from the present time to T2_TIG
		//S and T are inversed on purpose below!
		UPDATVP(1, RS_M50_PROX, VS_M50_PROX, TIME_PROX, T2_TIG, R_T_INER, V_T_INER);
		UPDATVP(2, RT_M50_PROX, VT_M50_PROX, TIME_PROX, T2_TIG, R_S_INER, V_S_INER);
		//Convert to a target-centerd curvilinear state
		REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
		//NULL relative velocity. Determine maneuver time. Set guidance flag for external DV.
		DV_LVLH = V_REL;
		T_MAN = T2_TIG;
		DSP_MISS = 0.0;
		GUID_FLAG = false;
	}
	else
	{
		//Compute the T1 maneuver
		if (EL_ANG != 0.0 && T1_TIG > PROX_T_CURRENT)
		{
			//Compute time of elevation angle
			TELEV(EL_ANG, R_S_INER, V_S_INER, R_T_INER, V_T_INER, TTPI);
			RS_T1TIG = R_S_INER;
			VS_T1TIG = V_S_INER;
			T1_TIG = TTPI;
			//Find relative state
			REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
			COMP_X = R_REL;
			COMP_XD = V_REL;
			//Display relative state
			DISP_T1_X = R_REL / 1000.0;
			DISP_T1_XD = V_REL;
			//Change base time in display and computational buffer, change I-load
			T1_ILOAD_ARRAY[PROX_TGT_SET_NO - 1] = 0.0;
			PROX_BASE_TIME = T1_TIG;
			ConvertSecondsToDDHHMMSS(PROX_BASE_TIME, PROX_BASE);
			//Compute T2_TIG and COMP_PROX_DT from the T1_TIG being used
			DT_COMP(T1_TIG, T2_TIG, COMP_PROX_DT);
		}
		else
		{
			//Elevation angle = 0, use the T1 time given for the maneuver time
			//Given T1_TIG, compute T2_TIG and/or COMP_PROX_DT
			DT_COMP(T1_TIG, T2_TIG, COMP_PROX_DT);
			//Compare to the minimum time of ignition
			if (T1_TIG < TIG_MIN)
			{
				T1_TIG = TIG_MIN;
				if (USE_OMEGA_DT == false)
				{
					COMP_PROX_DT = (T2_TIG - T1_TIG) / 60.0;
				}
				USE_DISP_REL_STATE = false;
			}
			//Update target to T1_TIG
			UPDATVP(2, RT_M50_PROX, VT_M50_PROX, TIME_PROX, T1_TIG, R_T_INER, V_T_INER);
			//Check the USE_DISP_REL_STATE flag
			if (USE_DISP_REL_STATE)
			{
				//If on, compute the Shuttle inertial state at T1
				R_REL = COMP_X;
				V_REL = COMP_XD;
				REL_COMP(false, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
				RS_T1TIG = R_S_INER;
				VS_T1TIG = V_S_INER;
			}
			else
			{
				//If off, update the present Shuttle states at T1_TIG, convert to curvilinear coordnates and display
				UPDATVP(1, RS_M50_PROX, VS_M50_PROX, TIME_PROX, T1_TIG, R_S_INER, V_S_INER);
				RS_T1TIG = R_S_INER;
				VS_T1TIG = V_S_INER;
				REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
				COMP_X = R_REL;
				COMP_XD = V_REL;
				DISP_T1_X = R_REL / 1000.0;
				DISP_T1_XD = V_REL;
			}
		}
		//Check the USE_OMEGA_DT flag. If it is on, there is insufficient information to determine T2_TIG and COMP_PROX_DT.
		if (USE_OMEGA_DT)
		{
			//Compute this information instead by use of the WT-calculation
			OMEGA_DT_COMP();
			//Compute T2_TIG
			T2_TIG = T1_TIG + 60.0*COMP_PROX_DT;
		}
		if (ALARM_KILL) return;
		//Update the target inertial state from T1_TIG to T2_TIG
		UPDATVP(2, R_T_INER, V_T_INER, T1_TIG, T2_TIG, R_T_INER, V_T_INER);
		//Compute the Shuttle inertial state at T2
		R_REL = COMP_T2_OFF;
		V_REL = _V(0, 0, 0);
		REL_COMP(false, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
		RS_T2TIG = R_S_INER;

		//Solve the Lambert problem using the precision velocity required routine
		VECTOR3 VS_REQUIRED;
		PREVR(T1_TIG, T2_TIG, RS_T1TIG, VS_T1TIG, RS_T2TIG, VS_REQUIRED);

		if (ALARM_KILL) return;

		//Compute the burn
		DV_LVLH = ORBLV(RS_T1TIG, VS_T1TIG, VS_REQUIRED - VS_T1TIG);
		T_MAN = T1_TIG;
		GUID_FLAG = true;
		if (USE_DISP_REL_STATE)
		{
			GUID_FLAG = false;
		}
	}
}

void OrbitTgtSoftware::PROX_STIME()
{
	//TBD
}

VECTOR3 OrbitTgtSoftware::ORBLV(VECTOR3 RS, VECTOR3 VS, VECTOR3 DV_INER)
{
	//The Orbiter LVLH transformation task determines the position and velocity of the target as seen from an Orbiter-centered LVLH frame starting with Orbiter and target M50 inertial vectors.

	//INPUT:
	//RS: Input inertial position of Shuttle
	//VS: Input inertial velocity of Shuttle
	//DV_INER: Inertial maneuver
	//OUTPUT:
	//DV_LVLH: Shuttle-centered LVLH maneuver

	MATRIX3 MAT_M50_LVIR;

	//Compute the transformation matrix from M50 inertial frame to the local vertical inertial Shuttle-centered rectangular coordinate frame
	MAT_M50_LVIR = LVLHMatrix(RS, VS);
	//Convert to a Shuttle–centered LVLH frame
	return mul(MAT_M50_LVIR, DV_INER);
}

void OrbitTgtSoftware::REL_COMP(bool INER_TO_LVC, VECTOR3 R_T_INER, VECTOR3 V_T_INER, VECTOR3 &R_S_INER, VECTOR3 &V_S_INER, VECTOR3 &R_REL, VECTOR3 &V_REL)
{
	//This task computes the state of the Orbiter in a target-centered local vertical
	//rotating curvilinear(LVC) coordinate system using the Earth - centered inertial
	//(M50) states of the Orbiter and the target, or performs the reverse transforma-
	//tion, depending on, an input flag.

	//INPUT:
	//INER_TO_LVC: true = convert inertial to LVC, false = convert LVC to inertial
	//R_T_INER: Input target inertial position vector 
	//V_T_INER: Input target inertial velocity vector 

	//Internal variables
	MATRIX3 MAT_M50_LVIR;
	VECTOR3 OMEGA_LV_PROX, RTS_M50, VTS_M50, RTS_LVIR, VTS_LVIR, RTS_LV, VTS_LV, VTAN;
	double RT_MAG, OMEGA_PROX, THETA, THETA_DOT, ZCON;

	RT_MAG = length(R_T_INER);
	MAT_M50_LVIR = LVLHMatrix(R_T_INER, V_T_INER);
	VTAN = V_T_INER - unit(R_T_INER)*dotp(R_T_INER, V_T_INER) / RT_MAG;
	OMEGA_PROX = length(VTAN) / RT_MAG;
	OMEGA_LV_PROX = _V(0, -1, 0)*OMEGA_PROX;
	if (INER_TO_LVC)
	{
		RTS_M50 = R_S_INER - R_T_INER;
		VTS_M50 = V_S_INER - V_T_INER;
		RTS_LVIR = mul(MAT_M50_LVIR, RTS_M50);
		VTS_LVIR = mul(MAT_M50_LVIR, VTS_M50);
		RTS_LV = RTS_LVIR;
		VTS_LV = VTS_LVIR - crossp(OMEGA_LV_PROX, RTS_LVIR);
		ZCON = RT_MAG - RTS_LV.z;
		THETA = atan(RTS_LV.x / ZCON);
		R_REL = _V(RT_MAG*THETA, RTS_LV.y, RT_MAG - ZCON / cos(THETA));
		THETA_DOT = pow(cos(THETA), 2)*(VTS_LV.x*ZCON + RTS_LV.x*VTS_LV.z) / (pow(ZCON, 2));
		V_REL = _V(RT_MAG*THETA_DOT, VTS_LV.y, (VTS_LV.z - THETA_DOT*RTS_LV.x) / cos(THETA));
	}
	else
	{
		THETA = R_REL.x / RT_MAG;
		THETA_DOT = V_REL.x / RT_MAG;
		ZCON = RT_MAG - R_REL.z;
		RTS_LV = _V(ZCON*sin(THETA), R_REL.y, RT_MAG - ZCON * cos(THETA));
		VTS_LV = _V(ZCON*THETA_DOT*cos(THETA) - V_REL.z*sin(THETA), V_REL.y, RTS_LV.x*THETA_DOT + V_REL.z*cos(THETA));
		RTS_LVIR = RTS_LV;
		VTS_LVIR = VTS_LV + crossp(OMEGA_LV_PROX, RTS_LVIR);
		RTS_M50 = tmul(MAT_M50_LVIR, RTS_LVIR);
		VTS_M50 = tmul(MAT_M50_LVIR, VTS_LVIR);
		R_S_INER = R_T_INER + RTS_M50;
		V_S_INER = V_T_INER + VTS_M50;
	}
}

void OrbitTgtSoftware::PROX_DISP_LOAD()
{
	//Display the maneuver
	MAN_TGT = PROX_TGT_SET_NO;
	DISP_DV = DV_LVLH;
	DISP_DV_MAG = length(DISP_DV);
	//Convert T1_TIG and T2_TIG to display
	ConvertSecondsToDDHHMMSS(T1_TIG, DISP_T1_TIG);
	ConvertSecondsToDDHHMMSS(T2_TIG, DISP_T2_TIG);
	//Display the transfer time
	DISP_PROX_DT = COMP_PROX_DT;
	//Display the maneuver time
	if (Eq(T_MAN, T1_TIG))
	{
		DISP_TMAN_TIME = T1_TIG;
		DISP_TMAN[0] = DISP_T1_TIG[0];
		DISP_TMAN[1] = DISP_T1_TIG[1];
		DISP_TMAN[2] = DISP_T1_TIG[2];
		DISP_TMAN[3] = DISP_T1_TIG[3];
	}
	if (Eq(T_MAN, T2_TIG))
	{
		DISP_TMAN_TIME = T2_TIG;
		DISP_TMAN[0] = DISP_T2_TIG[0];
		DISP_TMAN[1] = DISP_T2_TIG[1];
		DISP_TMAN[2] = DISP_T2_TIG[2];
		DISP_TMAN[3] = DISP_T2_TIG[3];
	}
}

bool OrbitTgtSoftware::ITERV(int &IC, double X_DEP, double &X_DEP_PRIME, double &X_IND, double &X_IND_PRIME, double FIRST_JUMP, double DY_TOL)
{
	//INPUTS:
	//IC: Iteration counter
	//X_DEP: Dependent variable
	//X_IND: Independent variable
	//X_DEP_PRIME: Previous value of the dependent variable
	//X_IND_PRIME: Previous value of the independent variable
	//OUTPUTS:
	//IC: Iteration counter
	//X_IND: Independent variable
	//X_DEP_PRIME: Previous value of the dependent variable
	//X_IND_PRIME: Previous value of the independent variable

	bool SFAIL;
	double DEL_X_IND;

	//Perform a logic test to determine if it is the first pass through the function
	if (IC == 0)
	{
		//If it is the first pass (IC = 0), set the delta independent variable to a constant first guess
		DEL_X_IND = -FIRST_JUMP;
	}
	else
	{
		//If it is not the first guess (IC != 0), calculate the delta dependent variable from the current and previous values of the dependent variable.
		double DEL_X_DEP = X_DEP - X_DEP_PRIME;
		//Perform a logic test of DEL_X_DEP to see if it is less than a small tolerance
		if (abs(DEL_X_DEP) < DY_TOL)
		{
			//If it is, then
			DEL_X_IND = -FIRST_JUMP;
		}
		else
		{
			//If DEL_X_DEP is not less than DEL_X_TOL, then
			double SLOPE = (DEL_X_DEP) / (X_IND - X_IND_PRIME);
			DEL_X_IND = X_DEP / SLOPE;
		}
	}

	//Set the previous values of the dependent and independent variable to the current values
	//Calculate the new current values of the independent variable.
	//Add one to the iteration counter, and set an iteration failure flag to zero.
	SFAIL = false;
	IC = IC + 1;
	X_DEP_PRIME = X_DEP;
	X_IND_PRIME = X_IND;
	X_IND = X_IND - DEL_X_IND;

	//Perform a logic test to determine if the maximum number of iterations has been exceeded.
	if (IC >= IC_MAX)
	{
		//If the iteration exceeds the maximum, set the failure flag.
		SFAIL = true;
	}

	return SFAIL;
}

void OrbitTgtSoftware::ELITER(int &IC, double ERR, double &ERR_PRIME, double &TTPI, double &TTPI_PRIME, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT)
{
	//INPUTS:
	//IC: Iteration counter
	//ERR: Guess of the elevation angle
	//ERR_PRIME: Previous guess of the elevation angle
	//TTPI: Predicted time of TPI (MET)
	//TTPI_PRIME: Previous guess of the TPI time
	//RS_OUT: Shuttle position vector
	//VS_OUT: Shuttle velocity vector
	//RT_OUT: Target position vector
	//VT_OUT: Target velocity vector

	//OUTPUTS:
	//IC: Iteration counter
	//ERR_PRIME: Previous guess of the elevation angle
	//TTPI: Predicted time of TPI (MET)
	//TTPI_PRIME: Previous guess of the TPI time
	//RS_OUT: Shuttle position vector
	//VS_OUT: Shuttle velocity vector
	//RT_OUT: Target position vector
	//VT_OUT: Target velocity vector

	double X_DEP, X_IND, X_DEP_PRIME, X_IND_PRIME;
	bool SFAIL;

	//Calculate the new guess at the time of TPI. This is performed in the Newton-Raphson iteration task, with inputs of iteration counter,
	//current error in the elevation angle, current TPI time, previous error, and TPI time. The outputs are the 	new TPI time, new previous error
	//and TPI time, and an error flag that is set it the maximum number of iterations is exceeded.
	X_DEP = ERR;
	X_IND = TTPI;
	X_DEP_PRIME = ERR_PRIME;
	X_IND_PRIME = TTPI_PRIME;

	SFAIL = ITERV(IC, X_DEP, X_DEP_PRIME, X_IND, X_IND_PRIME, DEL_X_GUESS[1], DEL_X_TOL[1]);

	TTPI = X_IND;
	ERR_PRIME = X_DEP_PRIME;
	TTPI_PRIME = X_IND_PRIME;

	//Perform a logic test to determine if the maximum number of iterations has been exceeded.
	if (SFAIL)
	{
		//If the iteration maximum has been exceeded (SFAIL != 0), set an ALARM flag and terminate the elevation angle iterator task
		ALARM_B = true;
		return;
	}

	//If the maximum number of iterations has not been exceeded (SFAIL = 0), perform a logic test to determine if the current TPI time is greater
	//than some delta-t from the previous TPI time. If it is, set the current TPI time to the previous time plus the delta-t.
	if (abs(TTPI - TTPI_PRIME) > DEL_T_MAX)
	{
		TTPI = TTPI_PRIME + DEL_T_MAX * sign(TTPI - TTPI_PRIME);
	}

	//Advance both Shuttle and target to the current TPI time. The state vector upstate task performs the advancement with two calls, one for the Shuttle and the other for the target.
	//The inputs are position and velocity vectors and TPI time. The outputs are position and velocity vectors and time of TPI.
	UPDATVP(1, RS_OUT, VS_OUT, TTPI_PRIME, TTPI, RS_OUT, VS_OUT);
	UPDATVP(2, RT_OUT, VT_OUT, TTPI_PRIME, TTPI, RT_OUT, VT_OUT);
}

double OrbitTgtSoftware::COMELE(VECTOR3 RS_COM, VECTOR3 VS_COM, VECTOR3 RT_COM)
{
	//INPUTS:
	//RS_COM: Shuttle inertial position
	//VS_COM: Shuttle inertial velocity
	//RT_COM: Target inertial position
	
	//OUTPUTS:
	//EL_ANG_COM: Computed elevation angle

	double A, B, D, E, EL_ANG_COM;

	//Calculate intermediate variables used in the elevation angle computation
	A = dotp(RS_COM, RS_COM);
	B = dotp(RS_COM, RT_COM);
	D = dotp(RS_COM, VS_COM);
	E = dotp(RT_COM, VS_COM);

	//Calculate the elevation angle between two position vectors (RS_COM and RT_COM)
	EL_ANG_COM = PI + atan2(A - B, (sign(B*D - A * E))*length(crossp(RS_COM, RT_COM)));
	if (EL_ANG_COM >= PI2) EL_ANG_COM = 0;

	return EL_ANG_COM;
}

void OrbitTgtSoftware::DT_COMP(double T1_TIG, double &T2_TIG, double &COMP_RPOX_DT)
{
	//The delta-t compute task is called to determine the transfer time and/or the maneuver time of the second of two impulse maneuvers

	//INPUTS:
	//T1_TIG: T1 maneuver time (MET)
	//T2_TIG: T2 maneuver time (MET)
	//COMP_PROX_DT: Delta-t in computation buffer

	//OUTPUTS:
	//T2_TIG: T2 maneuver time (MET)
	//COMP_PROX_DT: Delta-t in computation buffer

	//Set USE_OMEGA_DT flag to off
	USE_OMEGA_DT = false;
	//Check the transfer time (COMP_PROX_DT)
	if (COMP_RPOX_DT > 0)
	{
		T2_TIG = T1_TIG + 60.0*COMP_RPOX_DT;
	}
	else if (COMP_RPOX_DT < 0)
	{
		USE_OMEGA_DT = true;
	}
	else
	{
		COMP_RPOX_DT = (T2_TIG - T1_TIG) / 60.0;
	}
}

void OrbitTgtSoftware::OFFSET_TGT(VECTOR3 X_OFFTGT, VECTOR3 XD_OFFTGT, VECTOR3 X2_OFFTGT, double DT_OFFTGT, double DIFF_DR, VECTOR3 &DV)
{
	//INPUTS:
	//X_OFFTGT: T1 relative position vector
	//XD_OFFTGT: T1 relative velocity vector
	//X2_OFFTGT: T2 relative position vector
	//DT_OFFTGT: Transfer time in minutes
	//DIFF_DR: Differential acceleration

	//OUTPUT:
	//DV: LVLH delta-v vector

	double MAT[3][7], STATE[7];
	VECTOR3 V_T1_NEED;
	double W, T, S, C, C1, K;

	//Compute the T1 maneuver delta velocity vector
	W = OMEGA_PROX;
	T = 60.0*DT_OFFTGT;
	S = sin(W*T);
	if (abs(S) < 1e-8)
	{
		S = 1e-8;
	}
	C = cos(W*T);
	C1 = 1.0 - C;
	K = W / (8.0 - 8.0*C - 3.0*S*W*T);

	if (abs(1.0 / K) < EP_TRANSFER)
	{
		ALARM_D = true;
		ALARM_KILL = true;
		return;
	}

	MAT[0][0] = -K * S; MAT[0][1] = 0.0; MAT[0][2] = K * (14.0*C1 - 6.0*W*T*S); MAT[0][3] = K * S; MAT[0][4] = 0.0; MAT[0][5] = -2.0*K*C1; MAT[0][6] = -T / 2.0;
	MAT[1][0] = 0.0; MAT[1][1] = -C * W / S; MAT[1][2] = 0.0; MAT[1][3] = 0.0; MAT[1][4] = W / S; MAT[1][5] = 0.0; MAT[1][6] = 0.0;
	MAT[2][0] = -2.0*K*C1; MAT[2][1] = 0.0; MAT[2][2] = K * (3.0*C*W*T - 4.0*S); MAT[2][3] = 2.0 * K*C1; MAT[2][4] = 0.0; MAT[2][5] = K * (4.0*S - 3.0*W*T); MAT[2][6] = (K*T / W * (8.0*S - 3.0*W*T*(1.0 + C)) - 2.0 / W);

	STATE[0] = X_OFFTGT.x; STATE[1] = X_OFFTGT.y; STATE[2] = X_OFFTGT.z; STATE[3] = X2_OFFTGT.x; STATE[4] = X2_OFFTGT.y; STATE[5] = X2_OFFTGT.z; STATE[6] = DIFF_DR;

	if (C1 < EP_TRANSFER || abs(S) < sin(CONE))
	{
		MAT[1][1] = 0.0;
		MAT[1][4] = 0.0;
	}

	//Multiply 7x3 MAT matrix with 7x1 STATE vector
	V_T1_NEED = _V(0, 0, 0);

	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 7;j++)
		{
			V_T1_NEED.data[i] += MAT[i][j] * STATE[j];
		}
	}

	DV = V_T1_NEED - XD_OFFTGT;
	if (abs(MAT[1][1]) < 1e-7)
	{
		DV.y = 0.0;
	}
}

void OrbitTgtSoftware::OMEGA_DT_COMP()
{
	//This task calculates the transfer time needed to go from the T1_TIG state to the T2_TIG state such that the
	//T2_TIG maneuver is perpendicular to the line of sight and intercepts the next target point at the appropriate time.

	//If the current target set number, PROX_TGT_SET_NO, is 40, then set COMP_PROX_DT equal to the absolute value of COMP_PROX_DT and exit this task.
	if (PROX_TGT_SET_NO == 40)
	{
		COMP_PROX_DT = abs(COMP_PROX_DT);
		return;
	}

	VECTOR3 X_OFFTGT, XD_OFFTGT, X2_OFFTGT, DV;
	double DT_OFFTGT;

	//Find the velocity required at the displayed T2 time to intercept the next target set
	DT_OFFTGT = DT_ILOAD_ARRAY[PROX_TGT_SET_NO];
	X_OFFTGT = COMP_T2_OFF;
	XD_OFFTGT = _V(0, 0, 0);
	X2_OFFTGT.x = XOFF_ILOAD_ARRAY[PROX_TGT_SET_NO];
	X2_OFFTGT.y = YOFF_ILOAD_ARRAY[PROX_TGT_SET_NO];
	X2_OFFTGT.z = ZOFF_ILOAD_ARRAY[PROX_TGT_SET_NO];
	OFFSET_TGT(X_OFFTGT, XD_OFFTGT, X2_OFFTGT, DT_OFFTGT, 0.0, DV);

	//If the stop computations flag is OFF, (ALARM_KILL = OFF), then define internal variables. Otherwise, exit this task.
	if (ALARM_KILL) return;

	double XD1, YD1, ZD1, W, X0, Y0, Z0, X1, Y1, Z1, ALPHA, A, B, C, D, E, F, G, H, I, J, L, M;
	XD1 = DV.x;
	YD1 = DV.y;
	ZD1 = DV.z;
	W = OMEGA_PROX;
	X0 = COMP_X.x;
	Y0 = COMP_X.y;
	Z0 = COMP_X.z;
	X1 = COMP_T2_OFF.x;
	Y1 = COMP_T2_OFF.y;
	Z1 = COMP_T2_OFF.z;
	ALPHA = (X1*XD1 + Y1 * YD1 + Z1 * ZD1) / W;
	A = 8.0*ALPHA - 12.0*X1*Z1 - 2.0*X0*Z1 + 2.0*X1*Z0;
	B = -A;
	C = X0 * X1 - X1 * X1 + 4.0*Z0*Z1 - 4.0*Z1*Z1 + 8.0*Y0*Y1;
	D = 3.0*(Y1*Y1 + Z1 * Z1);
	E = -3.0*ALPHA + 6.0*X1*Z1;
	F = 8.0*Y1*(Y0 + Y1);
	G = -8.0*Y0*Y1;
	H = -3.0*Y0*Y1;
	I = -3.0*Y1*Y1;
	J = -8.0*Y1*Y1;
	L = -3.0*Z0*Z1;
	M = -8.0*Y0*Y1;

	//Set up Newton-Raphson iteration
	double X_IND, X_IND_PRIME, X_DEP, X_DEP_PRIME, T, COS, SIN, TAN;
	int IC = 0;
	X_IND = -60.0*COMP_PROX_DT;
	do
	{
		T = W * X_IND;
		COS = cos(T);
		SIN = sin(T);
		TAN = SIN / COS;
		X_DEP = A + B * COS + C * SIN + D * T*COS + E * T*SIN + F * COS / TAN + G * COS*COS / TAN + H * T*COS*COS + I * T*SIN*SIN + J / TAN + L * T + M * COS*SIN;
		ITERV(IC, X_DEP, X_DEP_PRIME, X_IND, X_IND_PRIME,DEL_X_GUESS[0], DEL_X_TOL[0]);
	} while (IC < IC_MAX && abs(X_IND - X_IND_PRIME) >= 0.5);

	//If maximum iterations have occurred, (IC = IC_MAX), then set the alarm flags (ALARM_D = ON, and ALARM_KILL = ON) to indicate 
	//an error in determining the transfer time and exit. Otherwise, compute the transfer time(COMP_PROX_DT)
	if (IC == IC_MAX)
	{
		ALARM_D = true;
		ALARM_KILL = true;
	}
	else
	{
		COMP_PROX_DT = X_IND / 60.0;
	}
}

void OrbitTgtSoftware::TELEV(double EL_ANG, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT, double &TTPI)
{
	//The elevation angle search task determines the time a desired elevation angle exists between the Shuttle and the target.

	//INPUTS:
	//EL_ANG: Desired elevation angle

	//OUTPUTS:
	//RS_OUT: Orbiter position vector at EL_ANG
	//VS_OUT: Orbiter velocity vector at EL_ANG
	//RT_OUT: Target position vector at EL_ANG
	//VT_OUT: Target velocity vector at EL_ANG
	//TTPI: Time at which EL_ANG is achieved

	double DELTA_H, T_SAVE, ERR_EL, EL_ANG_COM, ERR_EL_PRIME, ERR_DH, ERR_DH_PRIME;
	bool NN;

	//Common
	//Previous value of the independent variable in search for elevation angle (MET)
	double TTPI_PRIME;
	//Iteration counter to ITERV
	int IC;

	//Set the iteration counter to zero, and initialize the previous pass differential altitude indicator to indicate inconsistency
	IC = 0;
	NN = false;
	ERR_DH_PRIME = 0.0;
	ERR_EL_PRIME = 0.0;

	//Advance both the Shuttle and the target to first-guess time where the desired elevation angle should exist
	//The advancement is performed in two calls to the state vector update task, with inputs of vehicle position and velocity vectors, first-guess time.
	//The outputs are the vehicle position and velocity vectors, and time at the first-guess time
	TTPI = T1_TIG;
	UPDATVP(1, RS_M50_PROX, VS_M50_PROX, TIME_PROX, TTPI, RS_OUT, VS_OUT);
	UPDATVP(2, RT_M50_PROX, VT_M50_PROX, TIME_PROX, TTPI, RT_OUT, VT_OUT);

	//Perform an iteration to find a time for which the desired elevation angle the delta-h at that line are consistent (-DELTA_H*(ELANG-PI) >= 0)
	//Execute the following code while the maximum number of iterations has not been reached (IC <= ICMAX) and while the delta-h and elevation angle are inconsistent (NN=0).
	//Note: Initially NN = 0, thus the loop will be entered at least once.
	while (IC <= IC_MAX && NN == false)
	{
		//Calculate the differential altitude
		DELTA_H = length(RT_OUT) - length(RS_OUT);
		//Test for consistency between the calculated delta-h and the desired elevation angle
		if (-DELTA_H * (EL_ANG - PI) >= 0)
		{
			//If the elevation angle and differential altitude are consistent, set the differential altitude consistency indicator to indicate consistency
			NN = true;
		}
		else
		{
			//If they are not consistent, compute a dependent variable (ERR_DH) with the differential altitude and incompatibility tolerance (EL_DH_TOL)
			ERR_DH = DELTA_H + EL_DH_TOL * sign(DELTA_H);
			//Calculate the new guess at the time of consistency and advance the Shuttle and target to the time
			//This is performed in the elevation angle iterator task, with inputs of Shuttle position and velocity vectors, iteration counter, 
			//error in the elevation angle, current TPI time, previous error, and previous time
			//The outputs are the Shuttle and target position and velocity vectors, time, iteration counter, the new time, the new values of the
			//previous error and time, and an error flag.
			ELITER(IC, ERR_DH, ERR_DH_PRIME, TTPI, TTPI_PRIME, RS_OUT, VS_OUT, RT_OUT, VT_OUT);
		}
	}

	//Determine the time that the desired elevation angle exists. Test to see if the delta-h iteration has failed (i.e., the consistency flag, NN, is still set to zero).
	if (NN == 0)
	{
		//If the delta-h iteration has failed (i.e; the consistency flag is set to OFF, NN = 0), then exit the routine, since there will be no
		//time for which the desired elevation angle will exist.
		ALARM_B = true;
		return;
	}
	//If the consistency flag is set to ON ( NN = 1), then find the time of	elevation angle.
	if (IC != 0)
	{
		//If iterations have occurred(IC != 0), compute a TPI time in the direction of the direction of difference between the current and
		//previous TPI time and set iteration counter(IC) to zero. This	is done to ensure that the first two iterations are consistent.
		T_SAVE = TTPI;
		TTPI = TTPI + 10.0*sign(TTPI - TTPI_PRIME);
		IC = 0;
		//Advance both the Shuttle and target to the time of TPI.This is performed by two calls to the state vector update task, with inputs
		//of Shuttle and target positions and velocity vectors, time, and TPI time. The outputs are position and velocity vectors, and time.
		UPDATVP(1, RS_OUT, VS_OUT, T_SAVE, TTPI, RS_OUT, VS_OUT);
		UPDATVP(2, RT_OUT, VT_OUT, T_SAVE, TTPI, RT_OUT, VT_OUT);
	}
	//Perform an iteration to field the time of elevation angle. Execute the following code as long as the maximum number of iterations has
	//not been reached and the current errors larger than the tolerance, or while the number of iterations is equal to zero.
	//(This condition forces at least one iteration.)
	while (IC <= IC_MAX)
	{
		//Calculate the elevation angle that currently exists between the two vehicles. The calculations are performed in the elevation
		//angle computation task, with inputs of the Shuttle position and velocity vectors, and target position vector. The output is the elevation angle.
		EL_ANG_COM = COMELE(RS_OUT, VS_OUT, RT_OUT);
		//Calculate the difference between the desired and computed elevation angles.
		ERR_EL = EL_ANG - EL_ANG_COM;
		DISP_EL_ANG = EL_ANG_COM * DEG;
		//Iteration is finished if the error is within tolerance
		if (abs(ERR_EL) < EL_TOL || ALARM_B) break;
		//Calculate the new guess at the time of TPI and advance the Shuttle and target to the time
		//This is performed in the elevation angle iterator task, with inputs of Shuttle position and velocity vectors, iteration counter,
		//error in the elevation angle, current TPI time, previous error, and TPI time. The outputs are the Shuttle and	target positions and velocity 
		//vectors, time, iteration counter, new TPI time, new values of the previous error and TPI time, and an error flag.
		ELITER(IC, ERR_EL, ERR_EL_PRIME, TTPI, TTPI_PRIME, RS_OUT, VS_OUT, RT_OUT, VT_OUT);
	}

	return;
}

void OrbitTgtSoftware::PREVR(double T1_TIG, double T2_TIG, VECTOR3 RS_T1TIG, VECTOR3 VS_T1TIG, VECTOR3 RS_T2TIG, VECTOR3 &VS_REQUIRED)
{
	VECTOR3 RS_IP0, UN;
	VECTOR3 VG, UN_REF, R_MISS, RS_TERMINAL, VS_TERMINAL;
	double VG_MAG, ALPHA, ORB_RATE, SBETA, CBETA, BBEF, BAFT, ACC;
	int N;

	//Common
	//Transfer time
	double DEL_T_TRAN;

	//Set or initialize variables that are used in the iteration to find the required velocity
	DEL_T_TRAN = T2_TIG - T1_TIG;
	R_OFFSET = RS_T2TIG;
	T_OFFSET = T2_TIG;
	N = 0;
	VG = _V(0, 0, 0);
	VG_MAG = 0.0;
	ALPHA = 2.0 / length(RS_T1TIG) - dotp(VS_T1TIG, VS_T1TIG) / EARTH_MU;
	ORB_RATE = ALPHA * sqrt(ALPHA*EARTH_MU);
	S_ROTATE = 1;
	UN_REF = unit(crossp(RS_T1TIG, VS_T1TIG));
	RS_IP0 = RS_T1TIG;
	ACC = 100000.0; //THRUST / STS()->getmass;
	R_MISS = _V(0, 0, 0);

	do
	{
		N++;
		R_OFFSET = R_OFFSET - R_MISS;
		UN = crossp(RS_IP0, R_OFFSET);
		if (dotp(UN, UN_REF) >= 0.0)
		{
			S_ROTATE = 1;
		}
		else
		{
			S_ROTATE = -1;
		}
		SBETA = length(UN)*(double)S_ROTATE;
		CBETA = dotp(RS_IP0, R_OFFSET);
		BBEF = PI + atan2(-SBETA, -CBETA);
		BAFT = BBEF - ORB_RATE * VG_MAG / ACC;
		if (BBEF < PI - CONE || BAFT > PI + CONE)
		{
			UN = UN / SBETA;
		}
		else
		{
			S_ROTATE = 0;
			UN = UN_REF;
			R_OFFSET = R_OFFSET - UN * dotp(R_OFFSET, UN);
		}
		LAMBERT(RS_IP0, R_OFFSET, UN, DEL_T_TRAN, VS_REQUIRED);
		if (ALARM_KILL) return;
		VG = VS_REQUIRED - VS_T1TIG;
		VG_MAG = length(VG);

		UPDATVP(1, RS_IP0, VS_REQUIRED, T1_TIG, T2_TIG, RS_TERMINAL, VS_TERMINAL);
		R_MISS = RS_TERMINAL - RS_T2TIG;
		if (S_ROTATE == 0)
		{
			R_MISS = R_MISS - UN * dotp(R_MISS, UN);
		}
		DSP_MISS = length(R_MISS);
		if (N >= N_MAX_ITER)
		{
			ALARM_A = true;
		}
	} while (N < N_MIN || (N < N_MAX_ITER && length(R_MISS) > R_TOL));
}

void OrbitTgtSoftware::UPDATVP(int S_OPTION, VECTOR3 R_IN, VECTOR3 V_IN, double T_IN, double T_OUT, VECTOR3 &R_OUT, VECTOR3 &V_OUT)
{
	if (S_OPTION != 1 && S_OPTION != 2) return;  //Error
	//The state vector update task calls for the precision onborbit predictor to update a state vector to a time

	//INPUTS:
	//S_OPTION: 1 for Shuttle, 2 = for target
	//T_OUT: Time of the output state
	
	//OUTPUTS:
	//R_OUT: Output inertial position vector
	//V_OUT: Output inertial velocity vector

	//double PRED_ORB_MASS, PRED_ORB_CD, PRED_ORB_AREA;
	
	//PRED_ORB_MASS = 1.0; //PRED_ORB_MASS_I[S_OPTION - 1];
	//PRED_ORB_CD = 2.0; //PRED_ORB_CD_I[S_OPTION - 1];
	//PRED_ORB_AREA = 0.0; //PRED_ORB_AREA_I[S_OPTION - 1];

	pStateVectorSoftware->newpropagator.ONORBIT_PREDICT(R_IN, V_IN, T_IN, T_OUT, GMO_I, GMD_I, DMP_I[S_OPTION - 1], VMP_I[S_OPTION - 1], ATM_I[S_OPTION - 1], DTMIN_I, R_OUT, V_OUT);
}

void OrbitTgtSoftware::LAMBERT(VECTOR3 R0, VECTOR3 R1, VECTOR3 UN, double DEL_T_TRAN, VECTOR3 &VS_REQUIRED)
{
	double R0_MAG, R1_MAG, R_PARABOLA, V_PARABOLA, Z, VH, U_MIN, U_MAX, LAMBDA, U, T_TILDA_DESIRED, T_MIN, T_TILDA, S_TILDA;
	double F, G1, W, X1, Y, TEMP, T_TILDA_ERROR, U_STEP, VR, COEF;
	int N;

	//Calculate the magnitude of the initial vector and the final vector
	R0_MAG = length(R0);
	R1_MAG = length(R1);
	//Calculate the semiperimeter of the transfer triangle to be used as a normalizing constant
	R_PARABOLA = (R0_MAG + R1_MAG + length(R1 - R0)) / 2.0;
	//Calculate the parabolic velocity at perigee for R_PARABOLA for use as a normalizing factor
	V_PARABOLA = sqrt(2.0*EARTH_MU / R_PARABOLA);
	//Calculate the parameter Z
	Z = R0_MAG * R1_MAG - dotp(R0, R1);
	if (Z <= EP_TRANSFER * R0_MAG*R1_MAG)
	{
		ALARM_D = true;
		ALARM_KILL = true;
		return;
	}
	//Calculate the contangent of theta/2
	Z = dotp(crossp(R0, R1), UN / Z);
	//Calculate the parameter VH
	VH = sqrt(R0_MAG*R1_MAG / (1.0 + Z * Z));
	//Set the intial value on the counter to count the number of iterations
	N = 0;
	//Set the upper and lower limits of the independent variable
	U_MAX = 1.0 - DU / 2.0;
	U_MIN = -1.0;
	//Calculate the constant parameter LAMBDA
	LAMBDA = (VH / R_PARABOLA)*Z;
	//Calculate the first guess for the independent variable. The first guess assumes a circular orbit
	U = LAMBDA / sqrt(1.0 + LAMBDA * LAMBDA);
	//Calculate the normalized transfer time
	T_TILDA_DESIRED = (V_PARABOLA / R_PARABOLA)*DEL_T_TRAN;
	//Determine a transfer time that is slightly greater than the parabolic transfer time
	T_MIN = (2.0 / 3.0)*(1.0 - pow(LAMBDA, 3)) + 0.4*(1.0 - pow(LAMBDA, 5))*DU;
	if (DEL_T_TRAN < 0.0 || DEL_T_TRAN <= T_MIN)
	{
		ALARM_D = true;
		ALARM_KILL = true;
		return;
	}
	do
	{
		//Increment counter
		N++;
		W = sqrt(1.0 - U * U);
		X1 = LAMBDA * W;
		Y = sqrt(1.0 - X1 * X1);
		F = W * Y - U * X1;
		G1 = U * Y + W * X1;
		//Current value of the transfer time
		TEMP = atan2(F, G1);
		if (TEMP < 0.0)
		{
			TEMP += PI2;
		}
		//Current value of the transfer time
		T_TILDA = (TEMP - (U*W - X1 * Y)) / pow(W, 3);
		//Determine the slope of T_TILDA with respect to the independent variable U for use with the Newton-Raphson iteration
		S_TILDA = (3.0*U*T_TILDA - 2.0*(1.0 - U / Y * pow(LAMBDA, 3))) / pow(W, 2);
		//Determine the error in the current of T_TILDA and the desired value T_TILDA_DESIRED
		T_TILDA_ERROR = T_TILDA_DESIRED - T_TILDA;
		//Determine if the error in T_TILDA is small enough
		if (abs(T_TILDA_ERROR) > T_TILDA_DESIRED*EPS_U)
		{
			//Calculate a change in the current value of U
			U_STEP = T_TILDA_ERROR / S_TILDA;
			if (N == N_MAX_ITER)
			{
				ALARM_A = true;
				ALARM_KILL = true;
				return;
			}
			if (U_STEP > 0.0)
			{
				U_MIN = U;
			}
			else
			{
				U_MAX = U;
			}
			U = U + U_STEP;
			if (U < U_MIN || U > U_MAX)
			{
				U = (U_MIN + U_MAX) / 2.0;
			}
		}
	} while (N < N_MAX_ITER && abs(T_TILDA_ERROR) >= T_TILDA_DESIRED*EPS_U);

	//Calculate required initial velocity
	if (abs(T_TILDA_ERROR) < T_TILDA_DESIRED*EPS_U)
	{
		VH = VH / R0_MAG;
		VR = (R_PARABOLA / R0_MAG)*LAMBDA - G1;
		COEF = V_PARABOLA / (Y - LAMBDA * U);
		VS_REQUIRED = (R0*VR + crossp(UN, R0)*VH)*COEF / R0_MAG;
	}
}

MATRIX3 OrbitTgtSoftware::LVLHMatrix(VECTOR3 R, VECTOR3 V)
{
	MATRIX3 Mat;
	VECTOR3 VecTemp;

	VecTemp = unit(crossp(crossp(R, V), R));
	Mat.m11 = VecTemp.x; Mat.m12 = VecTemp.y; Mat.m13 = VecTemp.z;
	VecTemp = -unit(crossp(R, V));
	Mat.m21 = VecTemp.x; Mat.m22 = VecTemp.y; Mat.m23 = VecTemp.z;
	VecTemp = -unit(R);
	Mat.m31 = VecTemp.x; Mat.m32 = VecTemp.y; Mat.m33 = VecTemp.z;
	return Mat;
}

}