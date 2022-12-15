#include "FCOS.h"
#include "MasterTimingUnit.h"
#include "../Atlantis.h"
#include "MathSSV.h"

namespace dps
{
	FCOS::FCOS(SimpleGPCSystem * _gpc) : SimpleGPCSoftware(_gpc, "FCOS")
	{
		GMTLO = 0.0;
	}

	FCOS::~FCOS()
	{

	}

	void FCOS::Realize()
	{
		UpdateClock();
		if (GMTLO == 0)
		{
			//For old scenarios
			double met = STS()->MTU()->GetMETDay(0)*86400.0 + STS()->MTU()->GetMETHour(0)*3600.0 + STS()->MTU()->GetMETMin(0)*60.0 + STS()->MTU()->GetMETSec(0) + STS()->MTU()->GetMETMilli(0) / 1000.0;
			GMTLO = ReadCOMPOOL_SD(SCP_CLOCK) - met;
		}
		WriteCOMPOOL_SD(SCP_T_MET_REF, GMTLO);
	}

	bool FCOS::OnMajorModeChange(unsigned int newMajorMode)
	{
		return true;
	}

	void FCOS::OnPreStep(double simt, double simdt, double mjd)
	{
		UpdateClock();

		//TBD: Also handle CRT timer here?
	}

	bool FCOS::OnParseLine(const char* keyword, const char* value)
	{
		if (!_strnicmp(keyword, "GMTLO", 5)) {
			sscanf_s(value, "%lf", &GMTLO);
			return true;
		}
		return false;
	}

	void FCOS::OnSaveState(FILEHANDLE scn) const
	{
		oapiWriteScenario_float(scn, "GMTLO", GMTLO);
	}

	void FCOS::UpdateClock()
	{
		WriteCOMPOOL_SD(SCP_CLOCK, STS()->MTU()->GetGMTDay(0)*86400.0 + STS()->MTU()->GetGMTHour(0)*3600.0 + STS()->MTU()->GetGMTMin(0)*60.0 + STS()->MTU()->GetGMTSec(0) + STS()->MTU()->GetGMTMilli(0) / 1000.0);
	}

	void FCOS::SetLiftoff()
	{
		GMTLO = ReadCOMPOOL_SD(SCP_CLOCK);
		WriteCOMPOOL_SD(SCP_T_MET_REF, GMTLO);
	}
}