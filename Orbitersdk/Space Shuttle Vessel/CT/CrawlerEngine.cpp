/******* SSV File Modification Notice *******
Date         Developer
2020/05/07   GLS
2020/06/14   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/05/07   GLS
2022/08/05   GLS
********************************************/
#include "CrawlerEngine.h"
#include "Crawler.h"
#include <EngConst.h>
#include <MathSSV.h>
#include "..\SSVSound.h"


CrawlerEngine::CrawlerEngine(SubsystemDirector<Crawler>* _director)
: Subsystem(_director, "Engine"),
engineDirection(NEUT), engineState(OFF)
{
	//targetSpeed = 0.0;
	currentAcceleration = 0.0;
	enginePower = 0.0;
	//maxSpeed = MAX_UNLOADED_SPEED;
	bReverse = false;

	//increaseTgtSpeed = false;
	//decreaseTgtSpeed = false;
}

CrawlerEngine::~CrawlerEngine()
{
}

double CrawlerEngine::GetAcceleration() const
{
	return currentAcceleration;
}

/*void CrawlerEngine::SetMaxSpeed(double speed)
{
	maxSpeed = speed;
}

void CrawlerEngine::IncreaseTgtSpeed(bool _inc)
{
	increaseTgtSpeed=_inc;
	decreaseTgtSpeed=false;
}

void CrawlerEngine::DecreaseTgtSpeed(bool _dec)
{
	decreaseTgtSpeed=_dec;
	increaseTgtSpeed=false;
}*/

void CrawlerEngine::Realize()
{
	DiscreteBundle* pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_SPEED_FWD", 16 );
	currentSpeedFwd.Connect(pBundle, 0);
	tgtSpeedFwd.Connect(pBundle, 1);
	pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_SPEED_AFT", 16 );
	currentSpeedAft.Connect(pBundle, 0);
	tgtSpeedAft.Connect(pBundle, 1);

	pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_ENGINE_FWD", 16 );
	commandVoltageFwd.Connect( pBundle, 0 );
	NeutPBIFwd.Connect( pBundle, 1 );
	FwdPBIFwd.Connect( pBundle, 2 );
	RevPBIFwd.Connect( pBundle, 3 );
	NeutLightFwd.Connect( pBundle, 4 );
	FwdLightFwd.Connect( pBundle, 5 );
	RevLightFwd.Connect( pBundle, 6 );
	//commandVoltage.SetLine(0.0f);

	pBundle = V()->BundleManager()->CreateBundle( "CRAWLER_ENGINE_AFT", 16 );
	commandVoltageAft.Connect( pBundle, 0 );
	NeutPBIAft.Connect( pBundle, 1 );
	FwdPBIAft.Connect( pBundle, 2 );
	RevPBIAft.Connect( pBundle, 3 );
	NeutLightAft.Connect( pBundle, 4 );
	FwdLightAft.Connect( pBundle, 5 );
	RevLightAft.Connect( pBundle, 6 );
	return;
}

void CrawlerEngine::OnPreStep(double simt, double SimDT, double mjd)
{
	unsigned short CabInControl = V()->GetCabInControl();

	// engine commanding logic
	if (CabInControl == 1)
	{
		if (NeutPBIFwd.IsSet()) engineDirection = NEUT;
		else if (FwdPBIFwd.IsSet()) engineDirection = FWD;
		else if (RevPBIFwd.IsSet()) engineDirection = REV;
	}
	else if (CabInControl == 2)
	{
		if (NeutPBIAft.IsSet()) engineDirection = NEUT;
		else if (FwdPBIAft.IsSet()) engineDirection = REV;
		else if (RevPBIAft.IsSet()) engineDirection = FWD;
	}
	//else engineDirection = NEUT;// go idle if no cab is in control?

	// set target speed
	/*if(increaseTgtSpeed) {
		double dv = SimDT*0.1;
		targetSpeed = range(0.0, targetSpeed+dv, maxSpeed);
	}
	else if(decreaseTgtSpeed) {
		double dv = SimDT*-0.1;
		targetSpeed = range(0.0, targetSpeed+dv, maxSpeed);
	}*/

	// use FWD/NEUT/REV PBIs to start/shutdown engine and play correct sounds
	// use startup/shutdown sound length to determine when startup or shutdown is complete
	if(engineDirection == FWD || engineDirection == REV) {
		if(engineState==OFF || engineState==SHUTDOWN) {
			engineState = STARTING;
			PlayVesselWave(V()->GetSoundID(), ENGINE_START_SOUND_ID);
		}
		else if(engineState==STARTING && !IsPlaying(V()->GetSoundID(), ENGINE_START_SOUND_ID)) {
			engineState = ON;
		}
		else if(engineState==ON) {
			PlayVesselWave(V()->GetSoundID(), ENGINE_SOUND_ID, LOOP);
		}
	}
	else { // NEUT
		if(engineState==ON || engineState==STARTING) {
			engineState = SHUTDOWN;
			PlayVesselWave(V()->GetSoundID(), ENGINE_STOP_SOUND_ID);
			StopVesselWave(V()->GetSoundID(), ENGINE_SOUND_ID);
		}
		else if(engineState==SHUTDOWN && !IsPlaying(V()->GetSoundID(), ENGINE_STOP_SOUND_ID)) {
			engineState = OFF;
		}
	}

	// simplistic implementation of engine: acc is proportional to engine power
	if(engineState==ON) {
		// calculate throttle setting
		double dPower;
		double tgtPower;
		double actualSpeed = 0.0;
		double targetSpeed = 0.0;

		if (CabInControl == 1)
		{
			actualSpeed = currentSpeedFwd.GetVoltage();
			targetSpeed = tgtSpeedFwd.GetVoltage();
		}
		else if (CabInControl == 2)
		{
			actualSpeed = -currentSpeedAft.GetVoltage();
			targetSpeed = tgtSpeedAft.GetVoltage();
		}

		enginePower = fabs(enginePower); // for calculations, use positive power
		if(!Eq(targetSpeed, 0.0, 0.01)) {
			double err=0.0;
			if(engineDirection == FWD) err=targetSpeed-actualSpeed;
			else err=-targetSpeed-actualSpeed;
			if(fabs(err) > 0.005) {
				tgtPower = range(0.30, fabs(err)*10.0, 1.0);
				if((actualSpeed>0.0 && err<0.0) || (actualSpeed<0.0 && err>0.0)) {
					tgtPower = (1.0-tgtPower)*(0.20/0.70);
				}
				if(fabs(err)<0.01 && oapiGetTimeAcceleration()>20.0) {
					tgtPower = 0.25;
				}
				dPower = range(-0.05, tgtPower-enginePower, 0.05);
			}
			else { // hold speed
				dPower = range(-0.05, 0.25-enginePower, 0.05);
				tgtPower = 0.25;
			}
		}
		else { // shutdown engine
			dPower = -0.05;
			tgtPower = 0.0;
		}
		dPower*=SimDT;
		if(abs(dPower) > abs(tgtPower-enginePower)) enginePower = tgtPower;
		else enginePower = range(0.0, enginePower+dPower, 1.0);
		// correct sign of enginePower
		if(engineDirection == REV) enginePower = -enginePower;

		//sprintf_s(oapiDebugString(), 256, "Target Speed: %f", targetSpeed*MPS2MPH);
	}
	else {
		enginePower = 0.0;
	}
	currentAcceleration = enginePower*0.01;
	commandVoltageFwd.SetLine(static_cast<float>(enginePower));
	commandVoltageAft.SetLine(static_cast<float>(enginePower));

	if (engineDirection == NEUT)
	{
		NeutLightFwd.SetLine();
		NeutLightAft.SetLine();
		FwdLightFwd.ResetLine();
		FwdLightAft.ResetLine();
		RevLightFwd.ResetLine();
		RevLightAft.ResetLine();
	}
	else if (engineDirection == FWD)
	{
		NeutLightFwd.ResetLine();
		NeutLightAft.ResetLine();
		FwdLightFwd.SetLine();
		FwdLightAft.ResetLine();
		RevLightFwd.ResetLine();
		RevLightAft.SetLine();
	}
	else //if (engineDirection == AFT)
	{
		NeutLightFwd.ResetLine();
		NeutLightAft.ResetLine();
		FwdLightFwd.ResetLine();
		FwdLightAft.SetLine();
		RevLightFwd.SetLine();
		RevLightAft.ResetLine();
	}

	return;
}

bool CrawlerEngine::OnParseLine(const char* keyword, const char* line)
{
	std::string strKey = keyword;
	/*if(strKey == "TGT_VELOCITY") {
		sscanf_s(line, "%lf", &targetSpeed);
		return true;
	}*/
	if(strKey == "ENGINE_POWER") {
		sscanf_s(line, "%lf", &enginePower);
		return true;
	}
	else if(strKey == "ENGINE_STATE") {
		int temp;
		sscanf_s(line, "%d", &temp);
		engineState = static_cast<ENGINE_STATE>(temp);
		return true;
	}
	else if (strKey == "ENGINE_DIRECTION")
	{
		int temp;
		sscanf_s( line, "%d", &temp );
		engineDirection = static_cast<ENGINE_DIRECTION>(temp);
		return true;
	}
	return false;
}

void CrawlerEngine::OnSaveState(FILEHANDLE scn) const
{
	//oapiWriteScenario_float(scn, "VELOCITY", actualSpeed);
	//oapiWriteScenario_float(scn, "TGT_VELOCITY", targetSpeed);
	oapiWriteScenario_float(scn, "ENGINE_POWER", enginePower);
	oapiWriteScenario_int(scn, "ENGINE_STATE", engineState);
	oapiWriteScenario_int(scn, "ENGINE_DIRECTION", engineDirection );
	return;
}
