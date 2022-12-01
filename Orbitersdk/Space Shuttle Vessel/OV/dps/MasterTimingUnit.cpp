/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/05/28   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/11/25   GLS
********************************************/
// MasterTimingUnit.cpp: Implementierung der Klasse MasterTimingUnit.
//
//////////////////////////////////////////////////////////////////////

#include "MasterTimingUnit.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace dps {

MasterTimingUnit::MasterTimingUnit(AtlantisSubsystemDirector* _director)
: AtlantisSubsystem(_director, "MTU")
{
	int i;
	char pszBuffer[400];
	memset(pszBuffer, 0, 400);

	double mjd = oapiGetSimMJD();

	// Calculate GMT since midnight January 1st
	double mmjd = mjd - 15019.0;// Days since December 31, 1899
	double T1900 = mmjd / 365.25;// Years since then
	int Yr = 1900 + static_cast<int>(T1900);// Current year
	int LeapYears = (Yr - 1901) / 4;// Number of leap years since 1900
	double Days = mmjd - static_cast<double>((Yr - 1900) * 365 + LeapYears);// Days in year
	if (Days < 1.0)
	{
		// Special case for December 31.
		Yr--;
		LeapYears = (Yr - 1901) / 4;
		Days = mmjd - static_cast<double>((Yr - 1900) * 365 + LeapYears);
	}
	double fSimGMT = Days * 86400.0;// valid from 1900 to 2100

	for(i=0;i<3; i++)
	{
		fGMT[i][0] = fSimGMT;
		fGMT[i][1] = fSimGMT;
		fMET[i][0] = 0.0;
		fMET[i][1] = 0.0;
	}
	bMETCounting[1] = false;
	bMETCounting[0] = false;
}

MasterTimingUnit::~MasterTimingUnit()
{

}

short MasterTimingUnit::GetMETMilli(MTU_ACCU_INDEX accu_index) const
{
	return sMETMillis[accu_index];
}

short MasterTimingUnit::GetMETSec(MTU_ACCU_INDEX accu_index) const
{
	return sMETSeconds[accu_index];
}

short MasterTimingUnit::GetMETMin(MTU_ACCU_INDEX accu_index) const
{
	return sMETMinutes[accu_index];
}

short MasterTimingUnit::GetMETHour(MTU_ACCU_INDEX accu_index) const
{
	return sMETHours[accu_index];
}

short MasterTimingUnit::GetMETDay(MTU_ACCU_INDEX accu_index) const
{
	return sMETDays[accu_index];
}

void MasterTimingUnit::ResetMET()
{
	fMET[0][1] = 0;
	fMET[1][1] = 0;
	fMET[2][1] = 0;
}

void MasterTimingUnit::StartMET()
{
	bMETCounting[1] = true;
}

short MasterTimingUnit::GetGMTMilli(MTU_ACCU_INDEX accu_index) const
{
	return sGMTMillis[accu_index];
}

short MasterTimingUnit::GetGMTSec(MTU_ACCU_INDEX accu_index) const
{
	return sGMTSeconds[accu_index];
}

short MasterTimingUnit::GetGMTMin(MTU_ACCU_INDEX accu_index) const
{
	return sGMTMinutes[accu_index];
}

short MasterTimingUnit::GetGMTHour(MTU_ACCU_INDEX accu_index) const
{
	return sGMTHours[accu_index];
}

short MasterTimingUnit::GetGMTDay(MTU_ACCU_INDEX accu_index) const
{
	return sGMTDays[accu_index];
}

void MasterTimingUnit::OnPreStep(double simt, double simdt, double mjd)
{
	int timer;

	for(timer=0; timer<3; timer++)
	{
		fGMT[timer][1] = fGMT[timer][0] + simdt;

		if(fGMT[timer][1] > 34560000.0) {
			fGMT[timer][1] -= 34560000.0;
		}


		if(bMETCounting[0])
		{
			fMET[timer][1] = fMET[timer][0] + simdt;
			if(fMET[timer][0] > 34560000.0) {
				fMET[timer][1] -= 34560000.0;
			}
		}






	}
}

void MasterTimingUnit::OnPropagate(double simt, double simdt, double mjd)
{
	int timer;
	long lTime;

	for(timer = 0; timer<3; timer++)
	{
		fGMT[timer][0] = fGMT[timer][1];
		fMET[timer][0] = fMET[timer][1];

		//Update cache variables

		sGMTMillis[timer] = (short)fmod(fGMT[timer][0] * 1000.0, 1000.0);

		lTime = (long)fGMT[timer][0];
		sGMTSeconds[timer] = lTime%60;
		lTime/=60;
		sGMTMinutes[timer] = lTime%60;
		lTime/=60;
		sGMTHours[timer] = lTime%24;
		lTime/=24;
		sGMTDays[timer] = lTime%400;


		sMETMillis[timer] = (short)fmod(fMET[timer][0] * 1000.0, 1000.0);

		lTime = (long)fMET[timer][0];
		sMETSeconds[timer] = lTime%60;
		lTime/=60;
		sMETMinutes[timer] = lTime%60;
		lTime/=60;
		sMETHours[timer] = lTime%24;
		lTime/=24;
		sMETDays[timer] = lTime%400;
	}

	bMETCounting[0] = bMETCounting[1];
}

void MasterTimingUnit::Realize()
{
	// make sure data loaded from scenario file is propagated for first timestep
	OnPropagate(0.0, 0.0, oapiGetSimMJD());
}

void MasterTimingUnit::OnSaveState(FILEHANDLE scn) const
{
	char pszBuffer[128];
	int i;

	oapiWriteScenario_int(scn, "MET_RUNNING", bMETCounting[0]?1:0);


	for(i = 0; i<3; i++)
	{
		sprintf_s(pszBuffer, "MET%01d", i);
		oapiWriteScenario_float(scn, pszBuffer, fMET[i][0]);
	}
}

bool MasterTimingUnit::OnParseLine(const char* keyword, const char* line)
{
	int iTmpA = 0;
	float fTmpA = 0.0;

	if(!_stricmp(keyword, "RUNNING")) {

		sscanf_s(line, "%d", &iTmpA);

		bMETCounting[0] = bMETCounting[1] = (iTmpA != 0);


		return true;
	} else if(!_strnicmp(keyword, "MET", 3)) {
		sscanf_s(keyword+3, "%d", &iTmpA);
		sscanf_s(line, "%f", &fTmpA);
		if(iTmpA >=0 && iTmpA < 3)
		{
			fMET[iTmpA][1] = fMET[iTmpA][0] = fTmpA;
		}
		return true;
	}
	return false;
}

}
