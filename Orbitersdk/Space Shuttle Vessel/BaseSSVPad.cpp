/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/05/07   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/24   GLS
2021/06/14   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/08/05   GLS
********************************************/
#include "BaseSSVPad.h"
#include <MathSSV.h>


constexpr double GVA_RATE_RETRACT = 0.025;// 40 seconds [1/sec]
constexpr double GVA_RATE_EXTEND = 0.0155;// 65 seconds [1/sec]
constexpr double GVA_VENT_HOOD_RATE = 0.04166667;// 24 seconds [1/sec]
constexpr double ETVAS_RATE = 0.666667;// 1.5 seconds [1/sec]
constexpr double IAA_RATE = 0.0047619;// 210 seconds [1/sec]


VECTOR3 PAD_LIGHT_GLARE_COLOR = { 1.0, 1.0, 1.0 };


BaseSSVPad::BaseSSVPad(OBJHANDLE hVessel, int flightmodel, double WaterTankCap, double PreLOWaterFlowRate, double PostLOWaterFlowRate )
: VESSEL4(hVessel, flightmodel)
{
	bLightsOn = false;

	fNextLightUpdate = -20.0;

	oaa_mode = OAA_RATE_NORMAL;

	fSSMESteamLevel = 0.0;
	fSRBSteamLevel = 0.0;

	this->WaterTankCap = WaterTankCap;
	WaterTank = WaterTankCap;
	this->PreLOWaterFlowRate = PreLOWaterFlowRate;
	this->PostLOWaterFlowRate = PostLOWaterFlowRate;

	PreLOWaterOn = false;
	PreLOWaterLevel = 0.0;

	PostLOWaterOn = false;
	PostLOWaterLevel = 0.0;

	FirexOn_OrbiterSSMEWaterDelugeSystem = false;
	FirexOn_LH2LO2T0WaterDelugeSystem = false;
	FirexOn_OrbiterSkinSpraySystem = false;
	FirexLevel_OrbiterSSMEWaterDelugeSystem = 0.0;
	FirexLevel_LH2LO2T0WaterDelugeSystem = 0.0;
	FirexLevel_OrbiterSkinSpraySystem = 0.0;
}

BaseSSVPad::~BaseSSVPad()
{
	for(unsigned int i=0;i<vpAnimations.size();i++) delete vpAnimations.at(i);
}

void BaseSSVPad::CreateLights(VECTOR3* positions, unsigned int count)
{
	lights.resize(count); // set size of vector

	for(unsigned int i = 0; i<count; i++)
	{
		lights[i].duration = 0.1;
		lights[i].period = 2;
		lights[i].pos = &positions[i];
		lights[i].col = &PAD_LIGHT_GLARE_COLOR;
		lights[i].size = 1;
		lights[i].shape = BEACONSHAPE_STAR;
		lights[i].falloff = 0.4;
		lights[i].active = false;

		AddBeacon(&lights[i]);
	}
	ToggleLights(bLightsOn); // make sure lights initially have correct state
}

void BaseSSVPad::CreateStadiumLights(const VECTOR3* positions, const VECTOR3* dir, unsigned int count, double range, double att0, double att1, double att2, double umbra, double penumbra, const COLOUR4& diffuse, const COLOUR4& specular, const COLOUR4& ambient)
{
	// set size of vectors
	stadium_lights.resize(count);
	pStadiumLights.resize(count);

	for(unsigned int i=0;i<count;i++)
	{
		pStadiumLights[i] = AddSpotLight(positions[i], dir[i], range, att0, att1, att2, umbra, penumbra, diffuse, specular, ambient);

		// add beacons for glare effect
		stadium_lights[i].duration = 0;
		stadium_lights[i].period = 0;
		stadium_lights[i].pos = (VECTOR3*)&positions[i];
		stadium_lights[i].col = &PAD_LIGHT_GLARE_COLOR;
		stadium_lights[i].size = 3.0;
		stadium_lights[i].shape = BEACONSHAPE_DIFFUSE;
		stadium_lights[i].falloff = 0.25;
		stadium_lights[i].active = true;
		AddBeacon(&stadium_lights[i]);
	}
	ToggleLights(bLightsOn); // make sure lights initially have correct state
}

void BaseSSVPad::ToggleLights(bool enable)
{
	bLightsOn = enable;

	for(unsigned int i = 0; i<lights.size(); i++) {
		lights[i].active = enable;
	}

	for(unsigned int i=0;i<pStadiumLights.size();i++) {
		pStadiumLights[i]->Activate(enable);
		stadium_lights[i].active = enable;
	}
}

bool BaseSSVPad::IsNight() const
{
	OBJHANDLE Sun=NULL;
	int count=(int)oapiGetGbodyCount();
	for(int i=0;i<count;i++) {
		Sun=oapiGetGbodyByIndex(i);
		if(oapiGetObjectType(Sun)==OBJTP_STAR) break;
	}
	if(Sun) {
		VECTOR3 SunPosGlobal, SunPos;
		oapiGetGlobalPos(Sun, &SunPosGlobal);
		Global2Local(SunPosGlobal, SunPos);
		double angle=acos(SunPos.y/length(SunPos))*DEG;
		if(angle>80.0)
			return true;
	}
	return false;
}

void BaseSSVPad::clbkPreStep(double simt, double simdt, double mjd)
{
	VESSEL4::clbkPreStep(simt, simdt, mjd);

	if (simt > fNextLightUpdate)
	{
		fNextLightUpdate = simt + 300.0;

		if (bLightsOn && !IsNight())
		{
			ToggleLights(false);
		}
		else if (!bLightsOn && IsNight())
		{
			ToggleLights(true);
		}
	}

	if (OAA_State.Moving())
	{
		OAA_State.Move(simdt*orbiter_access_arm_rate[oaa_mode]);
		SetAnimation(anim_OAA, OAA_State.pos);
	}

	// INFO wrong order when extending GVA and lowering hood
	if (GOXVentHood_State.Moving())
	{
		GOXVentHood_State.Move(simdt*GVA_VENT_HOOD_RATE);
		SetAnimation(anim_GOXVentHood, GOXVentHood_State.pos);
	}
	else if (GVA_State.Moving())
	{
		if (GVA_State.Closing()) GVA_State.Move(simdt*GVA_RATE_RETRACT);
		else GVA_State.Move(simdt*GVA_RATE_EXTEND);
		SetAnimation(anim_GVA, GVA_State.pos);
	}

	if (ETVAS_State.Moving())
	{
		ETVAS_State.Move(simdt*ETVAS_RATE);
		SetAnimation(anim_ETVAS, ETVAS_State.pos);
	}

	if (IAA_State.Moving())
	{
		IAA_State.Move(simdt*IAA_RATE);
		SetAnimation(anim_IAA, IAA_State.pos);
	}

	// Pre L/O Water operation
	if (PreLOWaterOn)
	{
		WaterTank -= PreLOWaterFlowRate * simdt;// from 41-D abort
		if (WaterTank <= 0.0)
		{
			PreLOWaterOn = false;
			PreLOWaterLevel = 0.0;
			fSSMESteamLevel = 0.0;
			fSRBSteamLevel = 0.0;
			WaterTank = 0.0;
		}
		else
		{
			PreLOWaterLevel = 1.0;
			CalculateSteamProduction( simt, simdt );
		}
	}
	else
	{
		PreLOWaterLevel = 0.0;
		fSSMESteamLevel = 0.0;
		fSRBSteamLevel = 0.0;
	}

	// Post L/O Water operation
	if (PostLOWaterOn)
	{
		WaterTank -= PostLOWaterFlowRate * simdt;
		if (WaterTank <= 0.0)
		{
			PostLOWaterOn = false;
			PostLOWaterLevel = 0.0;
			WaterTank = 0.0;
		}
		else PostLOWaterLevel = 1.0;
	}
	else PostLOWaterLevel = 0.0;

	// Firex operation
	if (FirexOn_OrbiterSSMEWaterDelugeSystem) FirexLevel_OrbiterSSMEWaterDelugeSystem = 1.0;
	else FirexLevel_OrbiterSSMEWaterDelugeSystem = 0.0;

	if (FirexOn_LH2LO2T0WaterDelugeSystem) FirexLevel_LH2LO2T0WaterDelugeSystem = 1.0;
	else FirexLevel_LH2LO2T0WaterDelugeSystem = 0.0;

	if (FirexOn_OrbiterSkinSpraySystem) FirexLevel_OrbiterSkinSpraySystem = 1.0;
	else FirexLevel_OrbiterSkinSpraySystem = 0.0;

	if (GOXVentHood_State.Open() && GVA_State.Open()) GOXVentLevel = 1.0;
	else GOXVentLevel = 0.0;
	return;
}

void BaseSSVPad::SaveState( FILEHANDLE scn )
{
	try
	{
		if ((WaterTank / WaterTankCap) < 1.0) oapiWriteScenario_float( scn, "WATERTANKLEVEL", WaterTank / WaterTankCap );
		if (PreLOWaterOn) oapiWriteScenario_string( scn, "PRELOWATER", "ON" );
		if (PostLOWaterOn) oapiWriteScenario_string( scn, "POSTLOWATER", "ON" );

		int firex = 0;
		firex += ((int)FirexOn_OrbiterSSMEWaterDelugeSystem * 1) + ((int)FirexOn_LH2LO2T0WaterDelugeSystem * 2) + ((int)FirexOn_OrbiterSkinSpraySystem * 4);
		if (firex > 0) oapiWriteScenario_int( scn, "FIREX", firex );

		WriteScenario_state( scn, "OAA", OAA_State );
		WriteScenario_state( scn, "GVA", GVA_State );
		WriteScenario_state( scn, "VENT_HOOD", GOXVentHood_State );
		WriteScenario_state( scn, "ETVAS", ETVAS_State );
		WriteScenario_state( scn, "IAA", IAA_State );
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(BaseSSVPad) [FATAL ERROR] Exception in BaseSSVPad::SaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(BaseSSVPad) [FATAL ERROR] Exception in BaseSSVPad::SaveState" );
		abort();
	}
}

bool BaseSSVPad::LoadState( const char* line )
{
	try
	{
		if (!_strnicmp( line, "WATERTANKLEVEL", 14 ))
		{
			double tmp = 0.0;
			sscanf_s( line + 14, "%lf", &tmp );
			if ((tmp >= 0.0) && (tmp <= 1.0)) WaterTank = WaterTankCap * tmp;
		}
		else if (!_strnicmp( line, "PRELOWATER", 10 ))
		{
			if (!_strnicmp( line + 11, "ON", 3 )) PreLOWaterOn = true;
		}
		else if (!_strnicmp( line, "POSTLOWATER", 11 ))
		{
			if (!_strnicmp( line + 12, "ON", 3 )) PreLOWaterOn = true;
		}
		else if (!_strnicmp( line, "FIREX", 5 ))
		{
			int firex = 0;
			sscanf_s( line + 5, "%d", &firex );
			if (firex & 1) FirexOn_OrbiterSSMEWaterDelugeSystem = true;
			if (firex & 2) FirexOn_LH2LO2T0WaterDelugeSystem = true;
			if (firex & 4) FirexOn_OrbiterSkinSpraySystem = true;
		}
		else if (!_strnicmp( line, "OAA", 3 ))
		{
			sscan_state( (char*)line + 3, OAA_State);
			SetAnimation( anim_OAA, OAA_State.pos );
		}
		else if (!_strnicmp( line, "GVA", 3))
		{
			sscan_state( (char*)line + 3, GVA_State );
			SetAnimation( anim_GVA, GVA_State.pos );
		}
		else if (!_strnicmp( line, "VENT_HOOD", 9 ))
		{
			sscan_state( (char*)line + 9, GOXVentHood_State );
			SetAnimation( anim_GOXVentHood, GOXVentHood_State.pos );
		}
		else if (!_strnicmp( line, "ETVAS", 5 ))
		{
			sscan_state( (char*)line + 5, ETVAS_State );
			SetAnimation( anim_ETVAS, ETVAS_State.pos );
		}
		else if (!_strnicmp( line, "IAA", 3 ))
		{
			sscan_state( (char*)line + 3, IAA_State );
			SetAnimation( anim_IAA, IAA_State.pos );
		}
		else return false;
		return true;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(BaseSSVPad) [FATAL ERROR] Exception in BaseSSVPad::LoadState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLogV( "(BaseSSVPad) [FATAL ERROR] Exception in BaseSSVPad::LoadState" );
		abort();
	}
}

int BaseSSVPad::clbkConsumeBufferedKey(DWORD key, bool down, char* keystate)
{
	if(!down) return 0; //only handle keydown events

	if (KEYMOD_CONTROL(keystate))
	{
		switch(key) {
			case OAPI_KEY_K:
				if(OAA_State.Open() || OAA_State.Opening()) RetractOAA();
				else ExtendOAA( OAA_RATE_NORMAL );
				return 1;
			case OAPI_KEY_G:
				if(GOXVentHood_State.Closed()) ExtendGVAandHood();
				else RetractGVAandHood();
				return 1;
			case OAPI_KEY_V:
				DetachETVAS();
				return 1;
			case OAPI_KEY_A:
				if(IAA_State.Open()) RetractIAA();
				else DeployIAA();
				return 1;
		}
	}
	return 0;
}

MGROUP_ROTATE* BaseSSVPad::DefineRotation(UINT mesh, UINT* grp, UINT ngrp, const VECTOR3& ref, const VECTOR3& axis, float angle)
{
	MGROUP_ROTATE* mgrp = new MGROUP_ROTATE(mesh, grp, ngrp, ref, axis, angle);
	vpAnimations.push_back(mgrp);
	return mgrp;
}

MGROUP_TRANSLATE* BaseSSVPad::DefineTranslation(UINT mesh, UINT* grp, UINT ngrp, const VECTOR3& shift)
{
	MGROUP_TRANSLATE* mgrp = new MGROUP_TRANSLATE(mesh, grp, ngrp, shift);
	vpAnimations.push_back(mgrp);
	return mgrp;
}

MGROUP_SCALE* BaseSSVPad::DefineScale(UINT mesh, UINT* grp, UINT ngrp, const VECTOR3& ref, const VECTOR3& scale)
{
	MGROUP_SCALE* mgrp = new MGROUP_SCALE(mesh, grp, ngrp, ref, scale);
	vpAnimations.push_back(mgrp);
	return mgrp;
}
void BaseSSVPad::SetOrbiterAccessArmRate(double rate, int mode)
{
	orbiter_access_arm_rate[mode] = rate;
}

void BaseSSVPad::ExtendOAA( int mode )
{
	oaa_mode = mode;
	OAA_State.action=AnimState::OPENING;
}

void BaseSSVPad::RetractOAA()
{
	oaa_mode = OAA_RATE_NORMAL;
	OAA_State.action=AnimState::CLOSING;
}

void BaseSSVPad::HaltOAA()
{
	if (OAA_State.Moving()) OAA_State.action=AnimState::STOPPED;
}

void BaseSSVPad::ExtendGVA()
{
	// only allow arm to move when hood is closed (retracted)
	if (GOXVentHood_State.Closed())
		GVA_State.action = AnimState::OPENING;
}

void BaseSSVPad::RetractGVA()
{
	// only allow arm to move when hood is closed (retracted)
	if (GOXVentHood_State.Closed())
		GVA_State.action = AnimState::CLOSING;
}

void BaseSSVPad::HaltGVA()
{
	if (GVA_State.Moving()) GVA_State.action=AnimState::STOPPED;
}

void BaseSSVPad::AttachETVAS()
{
	if (IAA_State.Open()) ETVAS_State.action=AnimState::OPENING;
}

void BaseSSVPad::DetachETVAS()
{
	ETVAS_State.action=AnimState::CLOSING;
}

void BaseSSVPad::RaiseGOXVentHood()
{
	// only allow vent hood to move when vent arm is fully extended or retracted
	if (GVA_State.Open() || GVA_State.Closed())
		GOXVentHood_State.action = AnimState::CLOSING;
}

void BaseSSVPad::LowerGOXVentHood()
{
	// only allow vent hood to move when vent arm is fully extended or retracted
	if (GVA_State.Open() || GVA_State.Closed())
		GOXVentHood_State.action = AnimState::OPENING;
}

void BaseSSVPad::HaltGOXVentHood()
{
	if (GOXVentHood_State.Moving()) GOXVentHood_State.action=AnimState::STOPPED;
}

void BaseSSVPad::ExtendGVAandHood()
{
	GVA_State.action = AnimState::OPENING;
	GOXVentHood_State.action = AnimState::OPENING;
}

void BaseSSVPad::RetractGVAandHood()
{
	GVA_State.action = AnimState::CLOSING;
	GOXVentHood_State.action = AnimState::CLOSING;
}

void BaseSSVPad::DeployIAA()
{
	IAA_State.action=AnimState::OPENING;
}

void BaseSSVPad::HaltIAA()
{
	if (IAA_State.Moving()) IAA_State.action=AnimState::STOPPED;
}

void BaseSSVPad::RetractIAA()
{
	IAA_State.action=AnimState::CLOSING;
}
