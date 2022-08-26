/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/07   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
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

#define LOAD_V3(KEY,DATA) if(_strnicmp(keyword,KEY,strlen(KEY))==0){ sscanf_s(value,"%lf %lf %lf",&DATA.x,&DATA.y,&DATA.z); }
#define LOAD_DOUBLE(KEY,DATA) if(_strnicmp(keyword,KEY,strlen(KEY))==0){ sscanf_s(value,"%lf",&DATA); }

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
	for (int i = 0;i < 40;i++)
	{
		targetData[i].elevation = 0.0;
		targetData[i].finalOffset = _V(0, 0, 0);
		targetData[i].T1_TIG = 0.0;
		targetData[i].transferTime = 0.0;
	}

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

	PROX_TGT_SET_NO = 1;
	MAN_TGT = 1;
	ALARM = 0;

	DISP_PROX_DT = 0.0;
	DISP_EL_ANG = 0.0;
	PROX_BASE_TIME = 0.0;
	DISP_DV_MAG = 0.0;
	DISP_TMAN_TIME = 0.0;
	T1_TIG = 0.0;
	T2_TIG = 0.0;
	PROX_T_CURRENT = 0.0;
	PROX_BASE_TIME = 0.0;
	COMP_PROX_DT = 0.0;
	TIME_PROX = 0.0;
	OMEGA_PROX = 0.0;
	EL_ANG = 0.0;
	T_MAN = 0.0;
	
	DISP_T1_X = _V(0, 0, 0);
	DISP_T1_XD = _V(0, 0, 0);
	DISP_T2_OFF = _V(0, 0, 0);
	DISP_DV = _V(0, 0, 0);
	COMP_T2_OFF = _V(0, 0, 0);
	DV_LVLH = _V(0, 0, 0);
	COMP_X = _V(0, 0, 0);
	COMP_XD = _V(0, 0, 0);
	DISP_PRED_MATCH = 0.0;

	//I-Loads
	EL_TOL = 0.005; //About 0.3°
	EL_DH_TOL = 10.0;
	DEL_X_GUESS = 60.0;
	DEL_X_TOL = 0.0002;
	IC_MAX = 20;
	DEL_T_MAX = 900.0;
	NLAMB = 40;
	PROX_DT_MIN = 60.0;
	PROX_DTMIN_LAMB = 60.0;
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
	DISP_DV = DV_LVLH * MPS2FPS;
	DISP_DV_MAG = length(DISP_DV);
	DISP_TMAN_TIME = ConvertDDHHMMSSToSeconds(DISP_TMAN);
}

void OrbitTgtSoftware::OnPreStep(double simt, double simdt, double mjd)
{
	//Run executive
	PROX_EXEC();
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
		if (GetIntegerUnsigned( Data, nValue ))
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
		if (GetDoubleUnsigned(Data, dValue))
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
		if (GetDoubleSigned(Data, dValue))
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
		if (GetDoubleSigned(Data, dValue))
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
		if (GetIntegerUnsigned( Data, nValue ))
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
		if (GetDoubleSigned( Data, dValue ))
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
		if (GetDoubleSigned( Data, dValue ))
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
		if (strlen(Data) == 0 && (PROX_ITEM_2TO20_STATUS || PROX_ITEM_21TO24_STATUS))
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

	if (T_MAN > 0.0)
	{
		sprintf_s(cbuf, 51, "%02d", MAN_TGT);
		pMDU->mvprint(1, 3, cbuf);

		if (PROX_PAST_STATUS) pMDU->mvprint(4, 3, "*");
		sprintf_s(cbuf, 51, "%03.0f/%02.0f:%02.0f:%02.0f", DISP_TMAN[0], DISP_TMAN[1], DISP_TMAN[2], DISP_TMAN[3]);
		pMDU->mvprint(6, 3, cbuf);
		sprintf_s(cbuf, 51, "%5.1f", fabs(DISP_DV.x));
		pMDU->mvprint(21, 3, cbuf);
		pMDU->NumberSign(20, 3, DISP_DV.x);
		sprintf_s(cbuf, 51, "%4.1f", fabs(DISP_DV.y));
		pMDU->mvprint(29, 3, cbuf);
		pMDU->NumberSign(28, 3, DISP_DV.y);
		sprintf_s(cbuf, 51, "%4.1f", fabs(DISP_DV.z));
		pMDU->mvprint(36, 3, cbuf);
		pMDU->NumberSign(35, 3, DISP_DV.z);
		sprintf_s(cbuf, 51, "%5.1f", fabs(DISP_DV_MAG));
		pMDU->mvprint(43, 3, cbuf);
		pMDU->NumberSign(42, 3, DISP_DV_MAG);

		sprintf_s(cbuf, 51, "%7.0f", DISP_PRED_MATCH);
		pMDU->mvprint(37, 4, cbuf);
	}

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
		int itemp[13];
		sscanf_s(value, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &itemp[0], &itemp[1], &itemp[2], &itemp[3], &itemp[4], &itemp[5],
			&itemp[6], &itemp[7], &itemp[8], &itemp[9], &itemp[10], &itemp[11], &itemp[12]);
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
		USE_OMEGA_DT = (itemp[11] != 0);
		USE_DISP_REL_STATE = (itemp[12] != 0);
		return true;
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
		sscanf_s(value, "%d %d %d", &PROX_TGT_SET_NO, &MAN_TGT, &ALARM);
		return true;
	}
	else if (!_strnicmp(keyword, "TARGETDATA", 10)) {
		BurnTargetingData cfg;
		unsigned int i;
		LoadTargetData(value, cfg, i);
		targetData[i] = cfg;
		return true;
	}

	LOAD_DOUBLE("DISP_PROX_DT", DISP_PROX_DT);
	LOAD_DOUBLE("DISP_EL_ANG", DISP_EL_ANG);
	LOAD_DOUBLE("DISP_PRED_MATCH", DISP_PRED_MATCH);
	LOAD_DOUBLE("T1_TIG", T1_TIG);
	LOAD_DOUBLE("T2_TIG", T2_TIG);
	LOAD_DOUBLE("PROX_BASE_TIME", PROX_BASE_TIME);
	LOAD_DOUBLE("COMP_PROX_DT", COMP_PROX_DT);
	LOAD_DOUBLE("TIME_PROX", TIME_PROX);
	LOAD_DOUBLE("EL_ANG", EL_ANG);
	LOAD_DOUBLE("T_MAN", T_MAN);
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
	sprintf_s(cbuf, 255, "%d %d %d %d %d %d %d %d %d %d %d %d %d", PROX_T1_STAR_STATUS, PROX_T2_STAR_STATUS, PROX_PAST_STATUS, PROX_ITEM_1_STATUS, PROX_ITEM_2TO20_STATUS, PROX_ITEM_21TO24_STATUS,
		PROX_ITEM_25_STATUS, PROX_ITEM_26_STATUS, PROX_ITEM_28_STATUS, PROX_ITEM_29_STATUS, PROX_LOAD_FLASH, USE_OMEGA_DT, USE_DISP_REL_STATE);
	oapiWriteScenario_string(scn, "DISPLAY_FLAGS", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", DISP_T1_TIG[0], DISP_T1_TIG[1], DISP_T1_TIG[2], DISP_T1_TIG[3]);
	oapiWriteScenario_string(scn, "DISP_T1_TIG", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", DISP_T2_TIG[0], DISP_T2_TIG[1], DISP_T2_TIG[2], DISP_T2_TIG[3]);
	oapiWriteScenario_string(scn, "DISP_T2_TIG", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", PROX_BASE[0], PROX_BASE[1], PROX_BASE[2], PROX_BASE[3]);
	oapiWriteScenario_string(scn, "BASE_TIME", cbuf);
	sprintf_s(cbuf, 255, "%0.0f %0.0f %0.0f %0.1f", DISP_TMAN[0], DISP_TMAN[1], DISP_TMAN[2], DISP_TMAN[3]);
	oapiWriteScenario_string(scn, "DISP_TMAN", cbuf);
	sprintf_s(cbuf, 255, "%d %d %d", PROX_TGT_SET_NO, MAN_TGT, ALARM);
	oapiWriteScenario_string(scn, "INTS", cbuf);

	oapiWriteScenario_float(scn, "DISP_PROX_DT", DISP_PROX_DT);
	oapiWriteScenario_float(scn, "DISP_EL_ANG", DISP_EL_ANG);
	oapiWriteScenario_float(scn, "DISP_PRED_MATCH", DISP_PRED_MATCH);
	oapiWriteScenario_float(scn, "T1_TIG", T1_TIG);
	oapiWriteScenario_float(scn, "T2_TIG", T2_TIG);
	oapiWriteScenario_float(scn, "PROX_BASE_TIME", PROX_BASE_TIME);
	oapiWriteScenario_float(scn, "COMP_PROX_DT", COMP_PROX_DT);
	oapiWriteScenario_float(scn, "TIME_PROX", TIME_PROX);
	oapiWriteScenario_float(scn, "EL_ANG", EL_ANG);
	oapiWriteScenario_float(scn, "T_MAN", T_MAN);

	oapiWriteScenario_vec(scn, "DISP_T1_X", DISP_T1_X);
	oapiWriteScenario_vec(scn, "DISP_T1_XD", DISP_T1_XD);
	oapiWriteScenario_vec(scn, "DISP_T2_OFF", DISP_T2_OFF);
	oapiWriteScenario_vec(scn, "DV_LVLH", DV_LVLH);
	oapiWriteScenario_vec(scn, "COMP_T2_OFF", COMP_T2_OFF);
	oapiWriteScenario_vec(scn, "COMP_X", COMP_X);
	oapiWriteScenario_vec(scn, "COMP_XD", COMP_XD);

	for (unsigned int i = 0;i < 40;i++)
	{
		SaveTargetData(cbuf, targetData[i], i);
		oapiWriteScenario_string(scn, "TARGETDATA", cbuf);
	}
}

void OrbitTgtSoftware::SaveTargetData(char *buf, BurnTargetingData cfg, unsigned int i) const
{
	sprintf_s(buf, 256, "%d %lf %lf %lf %lf %lf %lf", i, cfg.T1_TIG, cfg.elevation, cfg.finalOffset.x, cfg.finalOffset.y, cfg.finalOffset.z, cfg.transferTime);
}

void OrbitTgtSoftware::LoadTargetData(const char *val, BurnTargetingData &cfg, unsigned int &i)
{
	sscanf_s(val, "%d %lf %lf %lf %lf %lf %lf", &i, &cfg.T1_TIG, &cfg.elevation, &cfg.finalOffset.x, &cfg.finalOffset.y, &cfg.finalOffset.z, &cfg.transferTime);
}

void OrbitTgtSoftware::PROX_EXEC()
{
	//TBD: First pass
	//Perform a logic test to determine if the crew made and entry to items 21-24
	if (PROX_ITEM_21TO24_STATUS)
	{
		PROX_LOAD_FLASH = true;
	}

	//Call the proximity operations targeting status task to set the maneuver status flag to on or off position if the maneuver TIG time is prior to or past current time.
	PROX_STAT();
	//Perofrm a logic test to determine if the crew has made an entry to item 1
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
		//Set the compute T1 star status flag to on
		PROX_T1_STAR_STATUS = true;
		//Perform a logic test to see if all of the display buffers for T1 relative state are blank (items 7-12), or if the T1 maneuver time is in the past (T1_TIG < PROX_T_CURRENT)
		if ((DISP_T1_X.x == 0.0 && DISP_T1_X.y == 0.0 && DISP_T1_X.z == 0.0 && DISP_T1_XD.x == 0.0 && DISP_T1_XD.y == 0.0 && DISP_T1_XD.z == 0.0) || T1_TIG < PROX_T_CURRENT)
		{
			USE_DISP_REL_STATE = false;
		}
		else
		{
			USE_DISP_REL_STATE = true;
		}
		//Set the item 29 status to off
		PROX_ITEM_28_STATUS = false;
	}
	//Perform a logical test to determine if the crew executed item 29
	if (PROX_ITEM_29_STATUS)
	{
		//Set the compute T2 star status flaf to on
		PROX_T2_STAR_STATUS = true;
		//Set the use relative display to off
		USE_DISP_REL_STATE = false;
		//Set the item 29 status to off
		PROX_ITEM_29_STATUS = false;
	}
	//Perform a logic test to determine if the compute T1 or compute T2 solutions were requested
	if (PROX_T1_STAR_STATUS || PROX_T2_STAR_STATUS)
	{
		//Retrieve the current Orbiter and target state vectors from ON_ORB_UPP
		TIME_PROX = STS()->GetMET();
		pStateVectorSoftware->GetPropagatedStateVectors(TIME_PROX, RS_M50_PROX, VS_M50_PROX);
		pStateVectorSoftware->GetTargetStateVectors(TIME_PROX, RT_M50_PROX, VT_M50_PROX);
		RS_M50_PROX = ConvertBetweenLHAndRHFrames(RS_M50_PROX);
		VS_M50_PROX = ConvertBetweenLHAndRHFrames(VS_M50_PROX);
		RT_M50_PROX = ConvertBetweenLHAndRHFrames(RT_M50_PROX);
		VT_M50_PROX = ConvertBetweenLHAndRHFrames(VT_M50_PROX);
		//Convert the orbital angular rate from the target inertial velocity vector
		double RT_MAG = length(RT_M50_PROX);
		VECTOR3 VTAN = VT_M50_PROX - unit(RT_M50_PROX)*dotp(RT_M50_PROX, VT_M50_PROX) / RT_MAG;
		OMEGA_PROX = length(VTAN) / RT_MAG;
		//Determine whether a Lambert or a CW calculation will be performed and call the appropiate targeting supervisory logic
		if (PROX_TGT_SET_NO <= NLAMB)
		{
			PROX_TGT_SUP_LAMB();
		}
		else
		{
			PROX_TGT_SUP();
			DISP_PRED_MATCH = 0.0;
		}
		//Call the prox ops targeting output display load to transfer the computed output data to the display buffers.
		PROX_DISP_LOAD();
		//Set the status flags off
		PROX_T1_STAR_STATUS = PROX_T2_STAR_STATUS = false;
		//Call the prox ops targeting start timer task and compute the time to the upcoming maneuver and place it in the time management buffer
		PROX_STIME();
		//Transfer the manuever execution data to the guidance buffer or array. This transfer is performed by the proximity operation guidance quantity transfer task
		PROX_TRANS();
	}
}

void OrbitTgtSoftware::PROX_STAT()
{
	//Get current time
	PROX_T_CURRENT = STS()->GetMET();
	//Perform a logic test to determine if the maneuver exists and if it is in the past
	if (T_MAN > 0 && PROX_T_CURRENT > T_MAN)
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
	T1_TIG = PROX_BASE_TIME + targetData[I_INDEX].T1_TIG * 60.0;
	COMP_PROX_DT = targetData[I_INDEX].transferTime;
	EL_ANG = targetData[I_INDEX].elevation*RAD;
	COMP_T2_OFF = targetData[I_INDEX].finalOffset* 1e3 / MPS2FPS;

	//Load the display buffers for T1 relative position and T2 time with blanks
	DISP_T2_TIG[0] = DISP_T2_TIG[1] = DISP_T2_TIG[2] = DISP_T2_TIG[3] = 0.0;
	DISP_T1_X = _V(0, 0, 0);
	DISP_T1_XD = _V(0, 0, 0);
	//Convert the computational T1 maneuver time (which is in MET) to days, hours, minutes and seconds
	ConvertSecondsToDDHHMMSS(T1_TIG, DISP_T1_TIG);
	//Load the display data buffers
	DISP_PROX_DT = targetData[I_INDEX].transferTime;
	DISP_EL_ANG = targetData[I_INDEX].elevation;
	DISP_T2_OFF = targetData[I_INDEX].finalOffset;
}

void OrbitTgtSoftware::PROX_INIT()
{
	//Did crew request a change to the base time (PROX_ITEM_21T024_STATUS = ON)? If so, put the displayed base time into the computational buffer
	if (PROX_ITEM_21TO24_STATUS && PROX_ITEM_2TO20_STATUS == false)
	{
		PROX_BASE_TIME = ConvertDDHHMMSSToSeconds(PROX_BASE);
	}
	if (PROX_ITEM_2TO20_STATUS && PROX_ITEM_21TO24_STATUS == false)
	{
		//Load the offset position and delta-t computation buffers and I-load buffers. The I-load buffers index value is determined by the selected
		//target set(I INDEX = PROX_TGT_SET NO)
		int I_INDEX = PROX_TGT_SET_NO - 1;
		COMP_T2_OFF = DISP_T2_OFF * 1e3 / MPS2FPS;
		COMP_PROX_DT = DISP_PROX_DT;
		EL_ANG = DISP_EL_ANG * RAD;
		targetData[I_INDEX].finalOffset = DISP_T2_OFF;
		targetData[I_INDEX].transferTime = DISP_PROX_DT;
		targetData[I_INDEX].elevation = DISP_EL_ANG;
		//Load the computation relative position and velocity buffers
		COMP_X = DISP_T1_X * 1e3 / MPS2FPS;
		COMP_XD = DISP_T1_XD / MPS2FPS;
		//Convert the display T1 time and display T2 time and load the computation and I-load buffers
		T1_TIG = ConvertDDHHMMSSToSeconds(DISP_T1_TIG);
		targetData[I_INDEX].T1_TIG = (T1_TIG - PROX_BASE_TIME) / 60.0;
		TIME_PROX = T1_TIG;
		T2_TIG = ConvertDDHHMMSSToSeconds(DISP_T2_TIG);
	}
}

void OrbitTgtSoftware::PROX_TRANS()
{
	if (PROX_PAST_STATUS == false)
	{
		//TBD: Guidance flag
		pOMSBurnSoftware->SetManeuverData(DISP_TMAN_TIME, DV_LVLH);
	}
}

void OrbitTgtSoftware::PROX_TGT_SUP()
{
	double TIG_MIN;

	//Is the USE_DISP_REL_STATE flag off?
	if (USE_DISP_REL_STATE == false)
	{
		REL_COMP(true, RT_M50_PROX, VT_M50_PROX, RS_M50_PROX, VS_M50_PROX, COMP_X, COMP_XD);
	}
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
		double DTIME;
		VECTOR3 X2, XD2;

		DTIME = T2_TIG - TIME_PROX;
		REL_PRED(COMP_X, COMP_XD, DTIME, X2, XD2);
		COMP_X = X2;
		COMP_XD = XD2;
		TIME_PROX = TIME_PROX + DTIME;
		//Null the relative rate
		DV_LVLH = -COMP_XD;
		T_MAN = T2_TIG;
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
		if (USE_DISP_REL_STATE == false)
		{
			//Update the present relative state to T1_TIG
			double DTIME;
			VECTOR3 X2, XD2;

			DTIME = T2_TIG - TIME_PROX;
			REL_PRED(COMP_X, COMP_XD, DTIME, X2, XD2);
			COMP_X = X2;
			COMP_XD = XD2;
			//Display the expected state at T1_TIG
			DISP_T1_X = COMP_X * MPS2FPS / 1000.0;
			DISP_T1_XD = COMP_XD * MPS2FPS;
		}
		if (USE_OMEGA_DT)
		{
			//Compute this information instead by use of the WT-calculation
			OMEGA_DT_COMP();
			//Compute T2_TIG
			T2_TIG = T1_TIG + 60.0*COMP_PROX_DT;
		}
		DV_LVLH = OFFSET_TGT(COMP_X, COMP_XD, COMP_T2_OFF, COMP_PROX_DT);
		T_MAN = T1_TIG;
	}
	GUID_FLAG = 0;
}

void OrbitTgtSoftware::PROX_TGT_SUP_LAMB()
{
	VECTOR3 R_S_INER, V_S_INER, R_T_INER, V_T_INER, R_REL, V_REL;
	double TIG_MIN;

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
		UPDATVP(1, RS_M50_PROX, VS_M50_PROX, TIME_PROX, T2_TIG, R_S_INER, V_S_INER);
		UPDATVP(2, RT_M50_PROX, VT_M50_PROX, TIME_PROX, T2_TIG, R_T_INER, V_T_INER);
		//Convert to a target-centerd curvilinear state
		REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
		//NULL relative velocity. Determine maneuver time. Set guidance flag for external DV.
		DV_LVLH = -V_REL;
		T_MAN = T2_TIG;
		GUID_FLAG = 0;
	}
	else
	{
		VECTOR3 RS_T1TIG, VS_T1TIG, RS_T2TIG, RT_T1TIG, VT_T1TIG;

		//Compute the T1 maneuver
		if (EL_ANG != 0.0)
		{
			//Compute time of elevation angle
			T1_TIG = TELEV(EL_ANG, R_S_INER, V_S_INER, R_T_INER, V_T_INER);
			RS_T1TIG = R_S_INER;
			VS_T1TIG = V_S_INER;
			//Find relative state
			REL_COMP(true, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
			//Display relative state
			DISP_T1_X = R_REL * MPS2FPS / 1000.0;
			DISP_T1_XD = V_REL * MPS2FPS;
			//Change base time in display and computational buffer, change I-load
			targetData[PROX_TGT_SET_NO - 1].T1_TIG = 0.0;
			PROX_BASE_TIME = T1_TIG;
			ConvertSecondsToDDHHMMSS(PROX_BASE_TIME, PROX_BASE);
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
			RT_T1TIG = R_T_INER;
			VT_T1TIG = V_T_INER;
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
				DISP_T1_X = R_REL * MPS2FPS / 1000.0;
				DISP_T1_XD = V_REL * MPS2FPS;
			}
		}
		//Compute T2_TIG and COMP_PROX_DT from the T1_TIG being used
		DT_COMP(T1_TIG, T2_TIG, COMP_PROX_DT);
		//Check the USE_OMEGA_DT flag. If it is on, there is insufficient information to determine T2_TIG and COMP_PROX_DT.
		if (USE_OMEGA_DT)
		{
			//Compute this information instead by use of the WT-calculation
			OMEGA_DT_COMP();
			//Compute T2_TIG
			T2_TIG = T1_TIG + 60.0*COMP_PROX_DT;
		}
		//Update the target inertial state from T1_TIG to T2_TIG
		UPDATVP(2, R_T_INER, V_T_INER, T1_TIG, T2_TIG, R_T_INER, V_T_INER);
		//Compute the Shuttle inertial state at T2
		R_REL = COMP_T2_OFF;
		V_REL = _V(0, 0, 0);
		REL_COMP(false, R_T_INER, V_T_INER, R_S_INER, V_S_INER, R_REL, V_REL);
		RS_T2TIG = R_S_INER;

		//Solve the Lambert problem using the precision velocity required routine
		VECTOR3 VS_REQUIRED = PREVR(T1_TIG, T2_TIG, RS_T1TIG, VS_T1TIG, RS_T2TIG);

		//Compute the LVLH Shuttle-centered relative state at T1 before the maneuver
		VECTOR3 RSLV, VSLV, V_LVLH;
		ORBLV(RS_T1TIG, VS_T1TIG, RT_T1TIG, VT_T1TIG, RSLV, VSLV);
		V_LVLH = VSLV;
		//Compute the LVLH Shuttle-centered relative state at T1 after the impulsive maneuver
		ORBLV(RS_T1TIG, VS_REQUIRED, RT_T1TIG, VT_T1TIG, RSLV, VSLV);
		//Compute the LVLH Shuttle-centered maneuver required at T2
		DV_LVLH = V_LVLH - VSLV;
		T_MAN = T1_TIG;
		GUID_FLAG = 1;
	}
}

void OrbitTgtSoftware::PROX_STIME()
{
	/*if (PROX_PAST_STATUS)
	{
		CRT_TIME = false;
	}
	else
	{

	}*/
}

void OrbitTgtSoftware::ORBLV(VECTOR3 RS, VECTOR3 VS, VECTOR3 RT, VECTOR3 VT, VECTOR3 &RSLV, VECTOR3 &VSLV)
{
	//The Orbiter LVLH transformation task determines the position and velocity of the target as seen from an Orbiter-centered LVLH frame starting with Orbiter and target M50 inertial vectors.

	//INPUT:
	//RS: Input inertial position of Shuttle
	//VS: Input inertial velocity of Shuttle
	//RT: Input inertial position of target
	//VT: Input inertial velocity of target
	//OUTPUT:
	//RSLV: Shuttle-centered LVLH relative position of target
	//VSLV: Shuttle-centered LVLH relative velocity of target

	MATRIX3 MAT_M50_MVIR;
	VECTOR3 VTAN, OMEGA_LV_PROX, RST_M50, VST_M50, RST_LVIR, VST_LVIR;
	double RS_MAG;

	//Find the magnitude of the Shuttle inertial vector
	RS_MAG = length(RS);
	//Compute the transformation matrix from M50 inertial frame to the local vertical inertial Shuttle-centered rectangular coordinate frame
	MAT_M50_MVIR = LVLHMatrix(RS, VS);
	//Determine the orbital angular rate vector
	VTAN = VS - unit(RS)*dotp(RS, VS) / RS_MAG;
	OMEGA_LV_PROX = _V(0.0, -1.0, 0.0)*length(VTAN) / RS_MAG;
	//Compute the relative M50 state of the target with respect to the Shuttle
	RST_M50 = RT - RS;
	VST_M50 = VT - VS;
	//Convert to a Shuttle-centered LV inertial rectangular frame
	RST_LVIR = mul(MAT_M50_MVIR, RST_M50);
	VST_LVIR = mul(MAT_M50_MVIR, VST_M50);
	//Convert to a Shuttle-centered LVLH frame
	RSLV = RST_LVIR;
	VSLV = VST_LVIR - crossp(OMEGA_LV_PROX, RST_LVIR);
}

void OrbitTgtSoftware::REL_PRED(VECTOR3 X, VECTOR3 XD, double DTIME, VECTOR3 &X2, VECTOR3 &XD2)
{
	double W, T, S, C, C1;

	W = OMEGA_PROX;
	T = DTIME;
	S = sin(W*T);
	C = cos(W*T);
	C1 = 1.0 - C;

	double MAT_PRED[6][6];

	MAT_PRED[0][0] = 1.0; MAT_PRED[0][1] = 0.0;		MAT_PRED[0][2] = 6.0*W*T - 6.0*S;	MAT_PRED[0][3] = 4.0*S / W - 3.0*T; MAT_PRED[0][4] = 0.0;	MAT_PRED[0][5] = 2.0*C1 / W;
	MAT_PRED[1][0] = 0.0; MAT_PRED[1][1] = C;		MAT_PRED[1][2] = 0.0;				MAT_PRED[1][3] = 0.0;				MAT_PRED[1][4] = S / W; MAT_PRED[1][5] = 0.0;
	MAT_PRED[2][0] = 0.0; MAT_PRED[2][1] = 0.0;		MAT_PRED[2][2] = 4.0 - 3.0*C;		MAT_PRED[2][3] = -2.0*C1 / W;		MAT_PRED[2][4] = 0.0;	MAT_PRED[2][5] = 2.0 / W;
	MAT_PRED[3][0] = 0.0; MAT_PRED[3][1] = 0.0;		MAT_PRED[3][2] = 6.0*W*C1;			MAT_PRED[3][3] = 4.0*C - 3.0;		MAT_PRED[3][4] = 0.0;	MAT_PRED[3][5] = 2.0*S;
	MAT_PRED[4][0] = 0.0; MAT_PRED[4][1] = -W * S;	MAT_PRED[4][2] = 0.0;				MAT_PRED[4][3] = 0.0;				MAT_PRED[4][4] = 0.0;	MAT_PRED[4][5] = 0.0;
	MAT_PRED[5][0] = 0.0; MAT_PRED[5][1] = 0.0;		MAT_PRED[5][2] = 3.0*W*S;			MAT_PRED[5][3] = -2.0*S;			MAT_PRED[5][4] = 0.0;	MAT_PRED[5][5] = C;

	double STATE1[6] = { X.x,X.y,X.z,XD.x,XD.y,XD.z };
	double STATE2[6] = { 0,0,0,0,0,0 };

	int i, j;
	for (i = 0;i < 6;i++)
	{
		for (j = 0;j < 6;j++)
		{
			STATE2[i] += MAT_PRED[i][j] * STATE1[j];
		}
	}
	X2 = _V(STATE2[0], STATE2[1], STATE2[2]);
	XD2 = _V(STATE2[3], STATE2[4], STATE2[5]);
}

void OrbitTgtSoftware::REL_COMP(bool INER_TO_LVC, VECTOR3 R_T_INER, VECTOR3 V_T_INER, VECTOR3 &R_S_INER, VECTOR3 &V_S_INER, VECTOR3 &R_REL, VECTOR3 &V_REL)
{
	//This task computes the state of the Orbiter in a target-centered local vertical
	//rotating curvilinear(LVC) coordinate system using the Earth - centered inertial
	//(M50) states of the Orbiter and the target, or performs the reverse transforma-
	//tion, depending on, an input flag.

	//INPUT:
	//

	MATRIX3 MAT_M50_LVIR;
	VECTOR3 OMEGA_LV_PROX, RTS_M50, VTS_M50, RTS_LVIR, VTS_LVIR, RTS_LV, VTS_LV;
	double RT_MAG, THETA, THETA_DOT, ZCON;

	RT_MAG = length(R_T_INER);
	MAT_M50_LVIR = LVLHMatrix(R_T_INER, V_T_INER);
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
		V_REL = _V(RT_MAG*THETA_DOT, VTS_LV.y, (VTS_LV.z - ZCON * THETA_DOT*tan(THETA)) / cos(THETA));
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
	DISP_DV = DV_LVLH * MPS2FPS;
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
	else
	{
		DISP_TMAN_TIME = T2_TIG;
		DISP_TMAN[0] = DISP_T2_TIG[0];
		DISP_TMAN[1] = DISP_T2_TIG[1];
		DISP_TMAN[2] = DISP_T2_TIG[2];
		DISP_TMAN[3] = DISP_T2_TIG[3];
	}
}

bool OrbitTgtSoftware::ITERV(int &IC, double X_DEP, double &X_DEP_PRIME, double &X_IND, double &X_IND_PRIME, double DEL_X_GUESS_TEMP, int ICMAX_TEMP, double DEL_X_TOL_TEMP)
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
		DEL_X_IND = DEL_X_GUESS_TEMP;
	}
	else
	{
		//If it is not the first guess (IC != 0), calculate the delta dependent variable from the current and previous values of the dependent variable.
		double DEL_X_DEP = X_DEP - X_DEP_PRIME;
		//Perform a logic test of DEL_X_DEP to see if it is less than a small tolerance
		if (abs(DEL_X_DEP) < DEL_X_TOL_TEMP)
		{
			//If it is, then
			DEL_X_IND = DEL_X_GUESS_TEMP;
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
	if (IC > ICMAX_TEMP)
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

	SFAIL = ITERV(IC, X_DEP, X_DEP_PRIME, X_IND, X_IND_PRIME, DEL_X_GUESS, IC_MAX, DEL_X_TOL);

	TTPI = X_IND;
	ERR_PRIME = X_DEP_PRIME;
	TTPI_PRIME = X_IND_PRIME;

	//Perform a logic test to determine if the maximum number of iterations has been exceeded.
	if (SFAIL)
	{
		//If the iteration maximum has been exceeded (SFAIL != 0), set an ALARM flag and terminate the elevation angle iterator task :
		ALARM = 7;
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

	double A, B, C, D, E, EL_ANG_COM;

	//Calculate intermediate variables used in the elevation angle computation
	A = dotp(RS_COM, RS_COM);
	B = dotp(RS_COM, RT_COM);
	C = dotp(RT_COM, RT_COM);
	D = dotp(RS_COM, VS_COM);
	E = dotp(RT_COM, VS_COM);

	//Calculate the elevation angle between two position vectors (RS_COM and RT_COM)
	if (A*C - B * B < 0)
	{
		EL_ANG_COM = PI + (sign(A - C))*PI05;
	}
	else
	{
		EL_ANG_COM = PI + atan2(A - B, (sign(B*D - A * E))*sqrt(A*C - B * B));
	}
	if (EL_ANG_COM >= PI2) EL_ANG_COM -= PI2;

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

VECTOR3 OrbitTgtSoftware::OFFSET_TGT(VECTOR3 X_OFFTGT, VECTOR3 XD_OFFTGT, VECTOR3 X2_OFFTGT, double DT_OFFTGT)
{
	MATRIX3 MAT1, MAT2;
	VECTOR3 V_T1_NEED;
	double W, T, S, C, C1, K;

	W = OMEGA_PROX;
	T = 60.0*DT_OFFTGT;
	S = sin(W*T);
	C = cos(W*T);
	C1 = 1.0 - C;
	K = W / (8.0 - 8.0*C + 3.0*S*W*T);

	MAT1 = _M(-K * S, 0.0, K*(13.0*C1 - 6.0*W*T*S), 0.0, -C * W / S, 0.0, -2.0*K*C1, 0.0, K*(3.0*C*W*T - 4.0*S));
	MAT2 = _M(K*S, 0.0, -2.0*K*C1, 0.0, W / S, 0.0, 2 * K*C1, 0.0, K*(4.0*S - 3.0*W*T));
	V_T1_NEED = mul(MAT1, X_OFFTGT) + mul(MAT2, X2_OFFTGT);
	return V_T1_NEED - XD_OFFTGT;
}

void OrbitTgtSoftware::OMEGA_DT_COMP()
{
	VECTOR3 X_OFFTGT, XD_OFFTGT, X2_OFFTGT, DV;
	double DT_OFFTGT;

	//TBD: This is unsafe if PROX_TGT_SET_NO is 40
	DT_OFFTGT = targetData[PROX_TGT_SET_NO].transferTime;
	X_OFFTGT = COMP_T2_OFF;
	XD_OFFTGT = _V(0, 0, 0);
	X2_OFFTGT = targetData[PROX_TGT_SET_NO].finalOffset;
	DV = OFFSET_TGT(X_OFFTGT, XD_OFFTGT, X2_OFFTGT, DT_OFFTGT);

	double XD1, YD1, ZD1, W, X0, Y0, Z0, X1, Y1, Z1, X2, Y2, Z2, ALPHA, A, B, C, D, E, F, G, H, I, J, L, M;
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
	X2 = X2_OFFTGT.x;
	Y2 = X2_OFFTGT.y;
	Z2 = X2_OFFTGT.z;
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
	double X_IND, X_IND_PRIME, X_DEP, X_DEP_PRIME, T, COS, SIN, TAN, DEL_X_GUESS_TEMP, DEL_X_TOL_TEMP;
	int IC, ICMAX_TEMP;
	bool SFAIL;
	IC = 0;
	ICMAX_TEMP = 10;
	DEL_X_TOL_TEMP = 0.0;
	X_IND = -60.0*COMP_PROX_DT;
	DEL_X_GUESS_TEMP = 100.0;
	do
	{
		T = W * X_IND;
		COS = cos(T);
		SIN = sin(T);
		TAN = SIN / COS;
		X_DEP = A + B * COS + C * SIN + D * T*COS + E * T*SIN + F * COS / TAN + G * COS*COS / TAN + H * T*COS*COS + I * T*SIN*SIN + J / TAN + L * T + M * COS*SIN;
		SFAIL = ITERV(IC, X_DEP, X_DEP_PRIME, X_IND, X_IND_PRIME, DEL_X_GUESS_TEMP, ICMAX_TEMP, DEL_X_TOL_TEMP);
	} while (IC <= ICMAX_TEMP && abs(X_IND - X_IND_PRIME) >= 0.5);
	//Compute the transfer time
	COMP_PROX_DT = X_IND / 60.0;
}

double OrbitTgtSoftware::TELEV(double EL_ANG, VECTOR3 &RS_OUT, VECTOR3 &VS_OUT, VECTOR3 &RT_OUT, VECTOR3 &VT_OUT)
{
	//The elevation angle search task determines the time a desired elevation angle exists between the Shuttle and the target.

	//INPUTS:

	//OUTPUTS:

	double DELTA_H, ERR_EL, EL_ANG_COM, ERR_EL_PRIME, TTPI, TTPI_PRIME, ERR_DH, ERR_DH_PRIME;
	int IC;
	bool NN;

	ERR_EL = 0.0;

	//Set the iteration counter to zero, and initialize the previous pass differential altitude indicator to indicate inconsistency
	IC = 0;
	NN = false;

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
		return TTPI;
	}
	//If the consistency flag is set to ON ( NN = 1), then find the time of	elevation angle.
	if (IC != 0)
	{
		//If iterations have occurred(IC != 0), compute a TPI time in the direction of the direction of difference between the current and
		//previous TPI time and set iteration counter(IC) to zero. This	is done to ensure that the first two iterations are consistent.
		TTPI = TTPI + 10.0*sign(TTPI - TTPI_PRIME);
		IC = 0;
		//Advance both the Shuttle and target to the time of TPI.This is performed by two calls to the state vector update task, with inputs
		//of Shuttle and target positions and velocity vectors, time, and TPI time. The outputs are position and velocity vectors, and time.
		UPDATVP(1, RS_OUT, VS_OUT, TTPI_PRIME, TTPI, RS_OUT, VS_OUT);
		UPDATVP(2, RT_OUT, VT_OUT, TTPI_PRIME, TTPI, RT_OUT, VT_OUT);
	}
	//Perform an iteration to field the time of elevation angle. Execute the following code as long as the maximum number of iterations has
	//not been reached and the current errors larger than the tolerance, or while the number of iterations is equal to zero.
	//(This condition forces at least one iteration.)
	while (((abs(ERR_EL) >= EL_TOL) && (IC <= IC_MAX)) || (IC == 0))
	{
		//Calculate the elevation angle that currently exists between the two vehicles. The calculations are performed in the elevation
		//angle computation task, with inputs of the Shuttle position and velocity vectors, and target position vector. The output is the elevation angle.
		EL_ANG_COM = COMELE(RS_OUT, VS_OUT, RT_OUT);
		//Calculate the difference between the desired and computed elevation angles.
		ERR_EL = EL_ANG - EL_ANG_COM;
		//Calculate the new guess at the time of TPI and advance the Shuttle and target to the time
		//This is performed in the elevation angle iterator task, with inputs of Shuttle position and velocity vectors, iteration counter,
		//error in the elevation angle, current TPI time, previous error, and TPI time. The outputs are the Shuttle and	target positions and velocity 
		//vectors, time, iteration counter, new TPI time, new values of the previous error and TPI time, and an error flag.
		ELITER(IC, ERR_EL, ERR_EL_PRIME, TTPI, TTPI_PRIME, RS_OUT, VS_OUT, RT_OUT, VT_OUT);
	}

	return TTPI;
}

VECTOR3 OrbitTgtSoftware::PREVR(double T1_TIG, double T2_TIG, VECTOR3 RS_T1TIG, VECTOR3 VS_T1TIG, VECTOR3 RS_T2TIG)
{
	VECTOR3 VS_REQUIRED, R_OFFSET;
	double T_OFFSET, MissDistance;
	int S_ROTATE, GMD_PRED, GMO_PRED;

	if (STS()->NonsphericalGravityEnabled())
	{
		GMD_PRED = 4;
		GMO_PRED = 0;//4; //Not supported by Orbiter
	}
	else
	{
		GMD_PRED = 0;
		GMO_PRED = 0;
	}

	burnTargeting.SetTargetingData(RS_T1TIG, VS_T1TIG, RS_T2TIG, T1_TIG, T2_TIG, STS()->GetMass(), GMD_PRED, GMO_PRED);

	int calc = 0;
	while (calc == 0)
	{
		burnTargeting.Step();
		LambertBurnTargeting::RESULT res = burnTargeting.CurrentState();
		if (res == LambertBurnTargeting::CONVERGED) {

			burnTargeting.GetData(VS_REQUIRED, R_OFFSET, T_OFFSET, S_ROTATE, MissDistance);
			calc = 1;
		}
		else if (res == LambertBurnTargeting::ERR) {
			calc = -1;
		}
	}
	DISP_PRED_MATCH = MissDistance*MPS2FPS;
	return VS_REQUIRED;
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

	double PRED_ORB_MASS, PRED_ORB_CD, PRED_ORB_AREA;
	int GMD_PRED, GMO_PRED, ATM;
	bool DMP, VMP;

	//GMD_PRED = GMD_I;
	//GMO_PRED = GMO_I;
	if (STS()->NonsphericalGravityEnabled())
	{
		GMD_PRED = 4;
		GMO_PRED = 0;//4; //Not supported by Orbiter
	}
	else
	{
		GMD_PRED = 0;
		GMO_PRED = 0;
	}
	
	ATM = 0;//ATM_I;
	DMP = false; //DMP_I[S_OPTION - 1];
	VMP = false, //VMP_I[S_OPTION - 1];
	PRED_ORB_MASS = 1.0; //PRED_ORB_MASS_I[S_OPTION - 1];
	PRED_ORB_CD = 2.0; //PRED_ORB_CD_I[S_OPTION - 1];
	PRED_ORB_AREA = 0.0; //PRED_ORB_AREA_I[S_OPTION - 1];

	pStateVectorSoftware->newpropagator.ONORBIT_PREDICT(R_IN, V_IN, T_IN, T_OUT, GMO_PRED, GMD_PRED, DMP, VMP, ATM, R_OUT, V_OUT);
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

};