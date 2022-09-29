/******* SSV File Modification Notice *******
Date         Developer
2020/05/07   GLS
2020/06/20   GLS
2020/07/08   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "APU.h"
#include "Atlantis.h"
#include "../SSVSound.h"


APU::APU(AtlantisSubsystemDirector *_director, const std::string &_ident, int _ID)
	: AtlantisSubsystem(_director, _ident), ID(_ID)
{
	State=OFF;
	FuelMass[0]=FuelMass[1] = APU_FUEL_TANK_MASS;
	HydraulicPressure[0]=HydraulicPressure[1]=0.0;
	APUSpeed[0]=APUSpeed[1]=0.0;
	FuelPress[0]=FuelPress[1]=0.0;
}

APU::~APU()
{
}

double APU::GetHydraulicPressure() const
{
	return HydraulicPressure[0];
}

double APU::GetFuelPressure() const
{
	// GLS: the "FUEL P" measurement in CRTMFD is tank pressure not pump outlet pressure
	// as this function returns. I will not update the code in OnPreStep (at least not now)
	// because probably the calculated FuelPress is needed for other things. Instead I just
	// replaced the returned value of this function with a simple formula calculating tank
	// pressure from quantity (it's the other way around in reality).
	return (FuelMass[0] / APU_FUEL_TANK_MASS) * 365;// psia
	//return FuelPress[0];
}

double APU::GetFuelLevel() const
{
	return FuelMass[0];
}

double APU::GetAPUSpeed() const
{
	return APUSpeed[0];
}

double APU::GetSubsystemMass() const
{
	return FuelMass[0] * LBM2KG;
}

void APU::Realize()
{
	std::string name="R2_To_"+GetIdentifier();
	DiscreteBundle *pBundle=BundleManager()->CreateBundle(name, 16);

	APU_Run.Connect(pBundle, 0);
	APU_CntlrPwr.Connect(pBundle, 1);
	APU_FuelTankValves.Connect(pBundle, 2);
	APU_HydPumpPress.Connect(pBundle, 3);
	APU_HydraulicPress.Connect(pBundle, 4);
	APU_ReadyToStart.Connect(pBundle, 5);

	char cbuf[255];
	sprintf_s(cbuf, 255, "WSB%d", ID);
	pBundle=BundleManager()->CreateBundle(cbuf, 16);
	WSB_Ready.Connect(pBundle, 0);
}

void APU::OnPreStep(double simt, double simdt, double mjd)
{
	switch(State) {
		case SHUTDOWN:
			// sound only plays in external view, so keep calling PlayVesselWave to make sure sound plays if we switch to external view
			if(STS()->GetSoundID()!=-1 && IsPlaying(STS()->GetSoundID(), APU_1_SHUTDOWN + ID - 1)) {
				StopVesselWave( STS()->GetSoundID(), APU_1_START + ID - 1 );
				StopVesselWave( STS()->GetSoundID(), APU_1_RUNNING + ID - 1 );
				PlayVesselWave(STS()->GetSoundID(), APU_1_SHUTDOWN + ID - 1, NOLOOP);
			}
		case OFF:
			if(APUSpeed[1]>5) APUSpeed[1]=max(APUSpeed[1]-15.0*simdt, 0.0);
			else {
				APUSpeed[1]=0.0;
				State=OFF;
			}
			if(FuelPress[1]>25) FuelPress[1] -= 200*simdt;
			else FuelPress[1] = 0.0;
			if(HydraulicPressure[1]>50) HydraulicPressure[1] -= 200*simdt;
			else HydraulicPressure[1] = 0.0;

			if(ReadyToStart()) {
				APU_ReadyToStart.SetLine();
				if(APU_Run) {
					State=START;
					if(STS()->GetSoundID()!=-1) PlayVesselWave(STS()->GetSoundID(), APU_1_START + ID - 1, NOLOOP);
				}
			}
			else APU_ReadyToStart.ResetLine();

			break;
		case START:
		case ON:
			// sound only plays in external view, so keep calling PlayVesselWave to make sure sound plays if we switch to external view
			if(STS()->GetSoundID()!=-1) {
				if(State==START && IsPlaying(STS()->GetSoundID(), APU_1_START + ID - 1)) PlayVesselWave(STS()->GetSoundID(), APU_1_START + ID - 1, NOLOOP);
				else PlayVesselWave(STS()->GetSoundID(), APU_1_RUNNING + ID - 1, LOOP);
			}

			if ((FuelMass[0]<=0.0) || (!APU_CntlrPwr) || (!APU_FuelTankValves)) State=SHUTDOWN;
			if(!APU_Run) {
				State=SHUTDOWN;
				if(STS()->GetSoundID()!=-1) PlayVesselWave(STS()->GetSoundID(), APU_1_SHUTDOWN + ID - 1, NOLOOP);
			}

			if(APU_HydPumpPress)
				FuelMass[1]-=APU_FUEL_TANK_FLOWRATE[0]*simdt;
			else FuelMass[1]-=APU_FUEL_TANK_FLOWRATE[1]*simdt;
			if (FuelMass[1] < 0) FuelMass[1] = 0;

			if(State==START) {
				if(APUSpeed[1]>=95.0) {
					APUSpeed[1]=103.0+(oapiRand()-0.5);
					State=ON;
				}
				else {
					APUSpeed[1]+=15.0*simdt;
				}

				APU_ReadyToStart.SetLine(); //in START sequence, RTS talkback is still gray
			}
			else {
				APUSpeed[1]+=0.75*(oapiRand()-0.5);

				APU_ReadyToStart.ResetLine(); //if APU is on, RTS talkback displays barberpole
			}

			if(FuelPress[1]<1400) FuelPress[1]+=200*simdt;
			else if(FuelPress[1]>1500) FuelPress[1]-=200*simdt;
			else if(FuelPress[1]<1425 || FuelPress[1]>1480)
				FuelPress[1]=1455 - 10.0 * oapiRand();
			else FuelPress[1] += (2.0 * oapiRand() - 1.0);

			if(APU_HydPumpPress) {
				if(HydraulicPressure[1]<2950) {
					if(HydraulicPressure[1]>2900)
						HydraulicPressure[1]=3000-(10*oapiRand());
					else
						HydraulicPressure[1]+=200*simdt;
				}
				else if(HydraulicPressure[1]>3050)
					HydraulicPressure[1]-=200*simdt;
				else
					HydraulicPressure[1]+=2.0 * oapiRand() - 1.0;
			}
			else {
				if(HydraulicPressure[1]<850) {
					if(HydraulicPressure[1]>800)
						HydraulicPressure[1]=900-10*oapiRand();
					else HydraulicPressure[1]+=200*simdt;
				}
				else if(HydraulicPressure[1]>950)
					HydraulicPressure[1]-=200*simdt;
				else {
					HydraulicPressure[1]+=(2.0*oapiRand() - 1.0);
				}
			}

			break;
	}
}

void APU::OnPropagate(double simt, double simdt, double mjd)
{
	FuelMass[0]=FuelMass[1];
	FuelPress[0]=FuelPress[1];
	HydraulicPressure[0]=HydraulicPressure[1];
	APUSpeed[0]=APUSpeed[1];
}

void APU::OnPostStep(double simt, double simdt, double mjd)
{
	APU_HydraulicPress.SetLine((float)(HydraulicPressure[0]/1000.0));
}

void APU::OnSaveState(FILEHANDLE scn) const
{
	oapiWriteScenario_int( scn, "State", State );
	oapiWriteScenario_float( scn, "FuelMass", FuelMass[0] );
	oapiWriteScenario_float( scn, "FuelPress", FuelPress[0] );
	oapiWriteScenario_float( scn, "HydPress", HydraulicPressure[0] );
	oapiWriteScenario_float( scn, "Speed", APUSpeed[0] );
}

bool APU::OnParseLine(const char *line)
{
	if (!_strnicmp( line, "State", 5 ))
	{
		sscanf_s( line + 5, "%d", &State );
		return true;
	}
	else if (!_strnicmp( line, "FuelMass", 8 ))
	{
		sscanf_s( line + 8, "%lf", &FuelMass[0] );
		if (FuelMass[0] > APU_FUEL_TANK_MASS) FuelMass[0] = APU_FUEL_TANK_MASS;
		else if (FuelMass[0] < 0.0) FuelMass[0] = 0.0;
		FuelMass[1]=FuelMass[0];
		return true;
	}
	else if (!_strnicmp( line, "FuelPress", 9 ))
	{
		sscanf_s( line + 9, "%lf", &FuelPress[0] );
		FuelPress[1]=FuelPress[0];
		return true;
	}
	else if (!_strnicmp( line, "HydPress", 8 ))
	{
		sscanf_s( line + 8, "%lf", &HydraulicPressure[0] );
		HydraulicPressure[1]=HydraulicPressure[0];
		return true;
	}
	else if (!_strnicmp( line, "Speed", 5 ))
	{
		sscanf_s( line + 5, "%lf", &APUSpeed[0] );
		APUSpeed[1]=APUSpeed[0];
		return true;
	}
	return false;
}

bool APU::ReadyToStart() const
{
	return (FuelMass[0]>0.0 && APU_CntlrPwr && APU_FuelTankValves && !APU_HydPumpPress && WSB_Ready);
}
