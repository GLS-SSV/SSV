/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
********************************************/
#define ORBITER_MODULE
#include "VAB.h"
#include "meshres.h"

const UINT VAB_HIGHBAY1_GROUPS[11] = {
	GRP_HB1_HORIZONTAL_DOOR_L1_VAB, GRP_HB1_HORIZONTAL_DOOR_L2_VAB,
	GRP_HB1_HORIZONTAL_DOOR_R1_VAB, GRP_HB1_HORIZONTAL_DOOR_R2_VAB,
	GRP_HB1_VLD1_VAB, GRP_HB1_VLD2_VAB, GRP_HB1_VLD3_VAB,
	GRP_HB1_VLD4_VAB, GRP_HB1_VLD5_VAB, GRP_HB1_VLD6_VAB,
	GRP_HB1_VLD7_VAB
	};

const UINT VAB_HIGHBAY2_GROUPS[11] = {
	GRP_HB2_HORIZONTAL_DOOR_L1_VAB, GRP_HB2_HORIZONTAL_DOOR_L2_VAB,
	GRP_HB2_HORIZONTAL_DOOR_R1_VAB, GRP_HB2_HORIZONTAL_DOOR_R2_VAB,
	GRP_HB2_VLD1_VAB, GRP_HB2_VLD2_VAB, GRP_HB2_VLD3_VAB,
	GRP_HB2_VLD4_VAB, GRP_HB2_VLD5_VAB, GRP_HB2_VLD6_VAB,
	GRP_HB2_VLD7_VAB
	};


const UINT VAB_HIGHBAY3_GROUPS[11] = {
	GRP_HB3_HORIZONTAL_DOOR_L1_VAB, GRP_HB3_HORIZONTAL_DOOR_L2_VAB,
	GRP_HB3_HORIZONTAL_DOOR_R1_VAB, GRP_HB3_HORIZONTAL_DOOR_R2_VAB,
	GRP_HB3_VLD1_VAB, GRP_HB3_VLD2_VAB, GRP_HB3_VLD3_VAB,
	GRP_HB3_VLD4_VAB, GRP_HB3_VLD5_VAB, GRP_HB3_VLD6_VAB,
	GRP_HB3_VLD7_VAB
	};

const UINT VAB_HIGHBAY4_GROUPS[11] = {
	GRP_HB4_HORIZONTAL_DOOR_L1_VAB, GRP_HB4_HORIZONTAL_DOOR_L2_VAB,
	GRP_HB4_HORIZONTAL_DOOR_R1_VAB, GRP_HB4_HORIZONTAL_DOOR_R2_VAB,
	GRP_HB4_VLD1_VAB, GRP_HB4_VLD2_VAB, GRP_HB4_VLD3_VAB,
	GRP_HB4_VLD4_VAB, GRP_HB4_VLD5_VAB, GRP_HB4_VLD6_VAB,
	GRP_HB4_VLD7_VAB
	};


DLLCLBK VESSEL* ovcInit(OBJHANDLE vessel, int flightmodel)
{
	return new VAB(vessel, flightmodel);
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	if (vessel) delete static_cast<VAB*>(vessel);
}

VAB::VAB(OBJHANDLE hVessel, int iFlightModel)
: VESSEL4(hVessel, iFlightModel), midxExterior((UINT)(-1)),
	midxInterior((UINT)(-1))
{

}

VAB::~VAB()
{
}

int VAB::clbkGeneric(int msgid, int prm, void *context)
{
	switch(msgid)
	{
	case VMSG_LUAINTERPRETER:
		return Lua_InitInterpreter(context);
	case VMSG_LUAINSTANCE:
		return Lua_InitInstance(context);
	}
	return 0;
}

void VAB::clbkLoadStateEx(FILEHANDLE scn, void *status)
{
	char* line;
	while(oapiReadScenario_nextline(scn, line))
	{
		ParseScenarioLineEx(line, status);
	}
}

void VAB::clbkPostStep(double simt, double simdt, double mjd)
{
}

void VAB::clbkPreStep(double simt, double simdt, double mjd)
{
	for(unsigned int i = 0; i<4; i++)
		highbay[i].execute(simdt);
}

void VAB::clbkSaveState(FILEHANDLE scn)
{
	VESSEL3::clbkSaveState(scn);
}

void VAB::clbkSetClassCaps(FILEHANDLE cfg)
{
	//General parameters
	SetSize(50.0);
	SetEmptyMass(16500000);
	SetTouchdownPoints(_V(0.0, BUILDING_COG_BASE, 50.0), _V(-50.0, BUILDING_COG_BASE, -50.0),
		_V(50.0, BUILDING_COG_BASE, -50.0));

	//Create visual
	midxExterior = AddMesh(MESHNAME_EXTERIOR_1980);
	midxInterior = AddMesh(MESHNAME_INTERIOR);

	DefineDoorAnimations();
}

void VAB::DefineDoorAnimations(void)
{
	highbay[0].init(this, midxExterior, _V(1.0, 0.0, 0.0), VAB_HIGHBAY1_GROUPS);
	highbay[1].init(this, midxExterior, _V(1.0, 0.0, 0.0), VAB_HIGHBAY2_GROUPS);
	highbay[2].init(this, midxExterior, _V(-1.0, 0.0, 0.0), VAB_HIGHBAY3_GROUPS);
	highbay[3].init(this, midxExterior, _V(-1.0, 0.0, 0.0), VAB_HIGHBAY4_GROUPS);
}

void VAB::DefineLightBeacons(void)
{
}

void VAB::DefineLights(void)
{
}

bool VAB::openTo(unsigned int hb, unsigned int segpos)
{

	return false;
}