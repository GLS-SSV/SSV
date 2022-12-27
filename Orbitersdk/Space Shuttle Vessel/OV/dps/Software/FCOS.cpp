#include "FCOS.h"
#include "../MasterTimingUnit.h"
#include "../../Atlantis.h"
#include "MathSSV.h"

namespace dps
{
	FCOS::FCOS(SimpleGPCSystem * _gpc) : SimpleGPCSoftware(_gpc, "FCOS")
	{

	}

	FCOS::~FCOS()
	{

	}

	void FCOS::Realize()
	{
		//Calculate GMT and then also get MET from the MTU and store the difference as the MET reference time
		UpdateClock();

		double met = STS()->MTU()->GetMETDay(0)*86400.0 + STS()->MTU()->GetMETHour(0)*3600.0 + STS()->MTU()->GetMETMin(0)*60.0 + STS()->MTU()->GetMETSec(0) + STS()->MTU()->GetMETMilli(0) / 1000.0;
		WriteCOMPOOL_SD(SCP_T_MET_REF, ReadCOMPOOL_SD(SCP_CLOCK) - met);
	}

	bool FCOS::OnMajorModeChange(unsigned int newMajorMode)
	{
		return true;
	}

	void FCOS::OnPreStep(double simt, double simdt, double mjd)
	{
		UpdateClock();

		//Monitor for liftoff. Seems inefficient to do this on every timestep?
		if (ReadCOMPOOL_IS(SCP_STORE_MET_REF) == 1)
		{
			WriteCOMPOOL_SD(SCP_T_MET_REF, ReadCOMPOOL_SD(SCP_CLOCK));
			WriteCOMPOOL_IS(SCP_STORE_MET_REF, 0);
		}

		//TBD: Also handle CRT timer here?
	}

	void FCOS::UpdateClock()
	{
		WriteCOMPOOL_SD(SCP_CLOCK, STS()->MTU()->GetGMTDay(0)*86400.0 + STS()->MTU()->GetGMTHour(0)*3600.0 + STS()->MTU()->GetGMTMin(0)*60.0 + STS()->MTU()->GetGMTSec(0) + STS()->MTU()->GetGMTMilli(0) / 1000.0);
	}
}