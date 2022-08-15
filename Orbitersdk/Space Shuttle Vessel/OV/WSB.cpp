/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "WSB.h"

WSB::WSB(AtlantisSubsystemDirector *_director, const std::string &_ident, unsigned short _ID)
	: AtlantisSubsystem(_director, _ident), usID(_ID)
{
	waterMass[0] = waterMass[1] = 0.0;
}

WSB::~WSB()
{
}

void WSB::Realize()
{
	DiscreteBundle* pBundle=BundleManager()->CreateBundle(GetIdentifier(), 16);
	Ready.Connect(pBundle, 0);
	Power.Connect(pBundle, 1);
	ControllerA.Connect(pBundle, 2);
	ControllerB.Connect(pBundle, 3);
	BoilerN2Supply.Connect(pBundle, 4);
}

void WSB::OnPreStep(double simt, double simdt, double mjd)
{
	// indicate if WSB is ready for APU start
	if(Power && BoilerN2Supply && (ControllerA || ControllerB)) {
		Ready.SetLine();
	}
	else {
		Ready.ResetLine();
	}
}

void WSB::OnPostStep(double simt, double simdt, double mjd)
{
}

void WSB::OnPropagate(double simt, double simdt, double mjd)
{
}

void WSB::OnSaveState(FILEHANDLE scn) const
{
}

bool WSB::OnParseLine(const char* keyword, const char* line)
{
	return AtlantisSubsystem::OnParseLine(keyword, line);
}
