/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/01   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2020/08/24   GLS
2020/09/09   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/09   GLS
2022/08/05   GLS
2022/08/07   GLS
********************************************/
#define ORBITER_MODULE

#include "XenonLights.h"
#include "meshres_xenon.h"
#include <MathSSV.h>


static const char* MESHNAME_XENON_TRAILER = "SSV\\XenonLights\\KSC_xenon_lights_trailer";
static const char* SHUTTLE_CLASS_NAME = "SSV_OV";
static const char* CRAWLER_CLASS_NAME = "SSV_CT";
static const char* CRAWLER_1980_CLASS_NAME = "SSV_CT_1980";

constexpr double CRAWLER_HEIGHT_OFFSET = 50.0;
constexpr double PAD_HEIGHT_OFFSET = 60.0;

constexpr double MAX_TARGET_RANGE = 1000.0; // max distance from light to shuttle
const double PAN_RANGE = 360.0*RAD;
const double TILT_RANGE = 90.0*RAD;

VECTOR3 LIGHT_POS[2] = { _V( -2.39706, 1.66544, 0.478418 ), _V( 2.39706, 1.66544, 0.478418 )};

VECTOR3 VERTICAL_AXIS1 = _V( -2.397059, 0.0, 0.0 );
VECTOR3 VERTICAL_AXIS2 = _V( 2.397059, 0.0, 0.0 );

VECTOR3 HORIZONTAL_AXIS1 = _V( -2.397059, 1.66544, 0.0 );
VECTOR3 HORIZONTAL_AXIS2 = _V( 2.397059, 1.66544, 0.0 );


const COLOUR4 LIGHT_DIFFUSE = {0.32f, 0.3f, 0.3f, 0};//const COLOUR4 LIGHT_DIFFUSE = {1.0f, 0.9f, 0.9f, 0};
const COLOUR4 LIGHT_SPECULAR = {0, 0, 0, 0};
const COLOUR4 LIGHT_AMBIENT = {1.0f, 1.0f, 1.0f, 0.0f};
const double LIGHT_RANGE = 3000.0;
const double LIGHT_ATT0 = 1e-3;
const double LIGHT_ATT1 = 0;
const double LIGHT_ATT2 = 0.0000065;
VECTOR3 GLARE_COLOR = { 1.0, 1.0, 1.0 };


XenonLights::XenonLights( OBJHANDLE hVessel, int fmodel ) : VESSEL4( hVessel, fmodel ),
bLightsOn(false),
bFoundTarget(false), hTarget(NULL),
updateClock(-0.1), locked(false)
{
	pLights[0] = pLights[1] = NULL;

	lightDir = _V( 0.0, 0.0, 1.0 );
	lightPosition[0] = LIGHT_POS[0];
	lightPosition[1] = LIGHT_POS[1];
}

XenonLights::~XenonLights()
{
	for(unsigned int i=0;i<vpAnimations.size();i++)
		delete vpAnimations[i];
}

void XenonLights::clbkSetClassCaps(FILEHANDLE cfg)
{
	try
	{
		meshIndex = AddMesh( MESHNAME_XENON_TRAILER );
		DefineAnimations();
		CreateLights();
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkSetClassCaps" );
		abort();
	}
}

void XenonLights::DefineAnimations()
{
	static UINT LeftPanGrp[2] = {GRP_HFRAME2_XENON, GRP_HORIZONTAL_AXIS2_XENON};
	MGROUP_ROTATE* pLeftPan = new MGROUP_ROTATE(meshIndex, LeftPanGrp, 2, VERTICAL_AXIS1, _V(0, 1, 0), static_cast<float>(PAN_RANGE));
	vpAnimations.push_back(pLeftPan);
	anim_pan[0] = CreateAnimation(0.0);
	ANIMATIONCOMPONENT_HANDLE parent = AddAnimationComponent(anim_pan[0], 0.0, 1.0, pLeftPan);

	static UINT LeftTiltGrp[2] = {GRP_LIGHTBOX2_XENON, GRP_LIGHTFRAME2_XENON};
	MGROUP_ROTATE* pLeftTilt = new MGROUP_ROTATE(meshIndex, LeftTiltGrp, 2, HORIZONTAL_AXIS1, _V(-1, 0, 0), static_cast<float>(TILT_RANGE));
	vpAnimations.push_back(pLeftTilt);
	anim_tilt[0] = CreateAnimation(0.0);
	parent = AddAnimationComponent(anim_tilt[0], 0.0, 1.0, pLeftTilt, parent);

	MGROUP_ROTATE* pLeftPos = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(lightPosition), 1, LIGHT_POS[0], _V(0, 0, 1), 0.0f);
	vpAnimations.push_back(pLeftPos);
	UINT pos_anim = CreateAnimation(0.0);
	AddAnimationComponent(pos_anim, 0.0, 1.0, pLeftPos, parent);

	static UINT RightPanGrp[2] = {GRP_HFRAME1_XENON, GRP_HORIZONTAL_AXIS1_XENON};
	MGROUP_ROTATE* pRightPan = new MGROUP_ROTATE(meshIndex, RightPanGrp, 2, VERTICAL_AXIS2, _V(0, 1, 0), static_cast<float>(PAN_RANGE));
	vpAnimations.push_back(pRightPan);
	anim_pan[1] = CreateAnimation(0.0);
	parent = AddAnimationComponent(anim_pan[1], 0.0, 1.0, pRightPan);

	static UINT RightTiltGrp[2] = {GRP_LIGHTBOX1_XENON, GRP_LIGHTFRAME1_XENON};
	MGROUP_ROTATE* pRightTilt = new MGROUP_ROTATE(meshIndex, RightTiltGrp, 2, HORIZONTAL_AXIS2, _V(-1, 0, 0), static_cast<float>(TILT_RANGE));
	vpAnimations.push_back(pRightTilt);
	anim_tilt[1] = CreateAnimation(0.0);
	parent = AddAnimationComponent(anim_tilt[1], 0.0, 1.0, pRightTilt, parent);

	MGROUP_ROTATE* pRightPos = new MGROUP_ROTATE(LOCALVERTEXLIST, MAKEGROUPARRAY(&lightPosition[1]), 1, LIGHT_POS[1], _V(0, 0, 1), 0.0f);
	vpAnimations.push_back(pRightPos);
	pos_anim = CreateAnimation(0.0);
	AddAnimationComponent(pos_anim, 0.0, 1.0, pRightPos, parent);
}

void XenonLights::CreateLights()
{
	for (int i = 0; i < 2; i++)
	{
		pLights[i] = AddSpotLight( LIGHT_POS[i], _V(0, 0, 1), LIGHT_RANGE, LIGHT_ATT0, LIGHT_ATT1, LIGHT_ATT2, 7.8 * RAD, 15.6 * RAD, LIGHT_DIFFUSE, LIGHT_SPECULAR, LIGHT_AMBIENT );
		pLights[i]->SetVisibility( LightEmitter::VIS_ALWAYS );

		// add beacons for glare effect
		pLightsGlare[i].duration = 0;
		pLightsGlare[i].period = 0;
		pLightsGlare[i].pos = &LIGHT_POS[i];
		pLightsGlare[i].col = &GLARE_COLOR;
		pLightsGlare[i].size = 2.0;
		pLightsGlare[i].shape = BEACONSHAPE_DIFFUSE;
		pLightsGlare[i].falloff = 0.4;
		pLightsGlare[i].active = false;
		AddBeacon( &pLightsGlare[i] );
	}
}

void XenonLights::clbkPreStep(double simT, double simDT, double mjd)
{
	try
	{
		updateClock -= simDT;
		if(updateClock < 0.0) {
			updateClock = 60.0;

			if (!locked)// if not locked search target, if locked just use position from scenario
			{
				// if target has not been found previously, try again
				if(bFoundTarget || FindTarget()) {
					// make sure target is still within range
					VECTOR3 relPos;
					GetRelativePos(hTarget, relPos);
					if(length(relPos) > MAX_TARGET_RANGE) {
						bFoundTarget = false;
						hTarget = NULL;
					}
					else {
						MATRIX3 RotMatrix;
						GetRotationMatrix(RotMatrix);
						VECTOR3 pos = tmul(RotMatrix, -relPos);
						pos.y = heightOffset;
						lightDir=pos/length(pos);
					}
				}
			}
			SetDirection(lightDir);

			bool day = IsDay();
			if(!day && !bLightsOn) SetLightState(true);
			else if(day && bLightsOn) SetLightState(false);
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkPreStep" );
		abort();
	}
}

void XenonLights::clbkLoadStateEx( FILEHANDLE scn, void *status )
{
	try
	{
		char *line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			if (!_strnicmp( line, "PAN_TILT", 8 ))
			{
				double pan = 0.0;
				double tilt = 0.0;

				// read
				sscanf_s( line + 9, "%lf %lf", &pan, &tilt );

				// convert to RAD and limit to range
				pan = range( 0.0, pan * RAD, PAN_RANGE );
				tilt = range( 0.0, tilt * RAD, TILT_RANGE );

				// convert to direction
				lightDir = _V( sin( pan ), sin( tilt ), cos( pan ) );

				locked = true;
			}
			else ParseScenarioLineEx( line, status );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkLoadStateEx" );
		abort();
	}
}

void XenonLights::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState(scn);

		if (locked)
		{
			char cbuf[32];
			double pan = atan2( lightDir.x, lightDir.z );
			// make sure pan is from 0 to 2pi radians
			if (pan < 0.0) pan += 2.0 * PI;
			else if (pan > (2.0 * PI)) pan -= 2.0 * PI;
			pan *= DEG;

			double tilt = asin(lightDir.y) * DEG;
			// make sure result is between 0 and 90 degrees
			tilt = range(0.0, tilt, TILT_RANGE);

			sprintf_s( cbuf, 32, "%.2f %.2f", pan, tilt );
			oapiWriteScenario_string( scn, "PAN_TILT", cbuf );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_XenonLights) [FATAL ERROR] Exception in XenonLights::clbkSaveState" );
		abort();
	}
}

bool XenonLights::IsDay() const
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
		if(angle>85.0)
			return false;
	}
	return true;
}

bool XenonLights::FindTarget()
{
	DWORD vesselCount = oapiGetVesselCount();
	for(unsigned int i=0;i<vesselCount;i++) {
		OBJHANDLE hV = oapiGetVesselByIndex(i);
		VESSEL* v = oapiGetVesselInterface(hV);
		if(!_stricmp(v->GetClassName(), SHUTTLE_CLASS_NAME)) {
			OBJHANDLE hParent = GetAttachedParent(hV);
			while(hParent) {
				hV = hParent;
				hParent = GetAttachedParent(hV);
			}

			VECTOR3 relPos;
			GetRelativePos(hV, relPos);
			if(length(relPos) < MAX_TARGET_RANGE) {
				bFoundTarget = true;
				hTarget = hV;

				// set height offset; this is different between rollout and on pad
				VESSEL* pTarget = oapiGetVesselInterface(hTarget);
				if(!_stricmp(pTarget->GetClassName(), CRAWLER_CLASS_NAME) ||
					!_stricmp(pTarget->GetClassName(), CRAWLER_1980_CLASS_NAME)) {
						heightOffset = CRAWLER_HEIGHT_OFFSET;
				}
				else {
					heightOffset = PAD_HEIGHT_OFFSET;
				}
				heightOffset += (oapiRand() - 0.5) * 50;// point within 25m vertically of vehicle center
				return true;
			}
		}
	}
	return false;
}

OBJHANDLE XenonLights::GetAttachedParent(OBJHANDLE hVessel) const
{
	VESSEL* pVessel = oapiGetVesselInterface(hVessel);
	DWORD count = pVessel->AttachmentCount(true);
	for(DWORD i=0;i<count;i++) {
		ATTACHMENTHANDLE ah = pVessel->GetAttachmentHandle(true, i);
		OBJHANDLE hV = pVessel->GetAttachmentStatus(ah);
		if(hV) return hV;
	}
	return NULL;
}

void XenonLights::SetDirection(VECTOR3 dir)
{
	double pan = atan2(dir.x, dir.z);
	// make sure pan is from 0 to 2pi radians
	if(pan < 0.0) pan += 2.0*PI;
	else if (pan > 2.0*PI) pan -= 2.0*PI;

	double tilt = asin(dir.y);
	// make sure result is between 0 and 90 degrees
	tilt = range(0.0, tilt, TILT_RANGE);

	for(int i=0;i<2;i++) {
		SetAnimation(anim_pan[i], pan/PAN_RANGE);
		SetAnimation(anim_tilt[i], tilt/TILT_RANGE);

		pLights[i]->SetDirection(dir);
	}
}

void XenonLights::SetLightState(bool on)
{
	for (int i = 0; i < 2; i++)
	{
		pLights[i]->Activate( on );
		pLightsGlare[i].active = on;
	}
	bLightsOn = on;
}

//global functions
DLLCLBK void InitModule(HINSTANCE hDLL)
{
}

DLLCLBK void ExitModule(HINSTANCE hDLL)
{
}

DLLCLBK VESSEL* ovcInit(OBJHANDLE vessel, int flightmodel)
{
	try
	{
		return new XenonLights(vessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_XenonLights) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_XenonLights) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	try
	{
		if (vessel) delete static_cast<XenonLights*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_XenonLights) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_XenonLights) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}