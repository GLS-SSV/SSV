/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/01   GLS
2020/06/20   GLS
2020/06/21   GLS
2020/06/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
********************************************/
#include "DragChute.h"
#include "..\OV\ParameterValues.h"

#define ORBITER_MODULE

DragChute::DragChute(OBJHANDLE hVessel, int flightmodel)
	: VESSEL4(hVessel, flightmodel)
{
}

DragChute::~DragChute()
{
	delete collapse;
}

void DragChute::DefineAnimations()
{
	anim_collapse_state=1.0;
	anim_collapse=CreateAnimation(1.0);
	collapse = new MGROUP_SCALE(mesh_idx, NULL, 4, _V(0, 0, 0), _V(1, 100, 1));
	AddAnimationComponent(anim_collapse, 0, 1, collapse);
}

void DragChute::clbkSetClassCaps( FILEHANDLE cfg )
{
	try
	{
		VECTOR3 mesh_ofs= _V(0, 0, 0);

		mesh=oapiLoadMeshGlobal(MESHNAME_CHUTE);
		mesh_idx=AddMesh(mesh, &mesh_ofs);

		SetEmptyMass(10.0);
		SetCrossSections( _V( 0.000001, 0.000001, 0.000001 ) );// super small so it doesn't get dragged by the wind after it lands

		DWORD ntdvtx = 4;
		static TOUCHDOWNVTX tdvtx[4] = {
			{_V( 0, 0, 5 ), 1e3, 1e2, 1, 1},
			{_V( 5, 0, -5 ), 1e3, 1e2, 1, 1},
			{_V( -5, 0, -5 ), 1e3, 1e2, 1, 1},
			{_V( 0, 0.1, 0 ), 1e3, 1e2, 1}
		};
		SetTouchdownPoints( tdvtx, ntdvtx );

		DefineAnimations();
		CreateVariableDragElement(&anim_collapse_state, 45, _V(0, 0, 0));
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkSetClassCaps" );
		abort();
	}
}

void DragChute::clbkPreStep(double simt, double simdt, double mjd)
{
	try
	{
		if(anim_collapse_state>0.0) {
			anim_collapse_state=max(anim_collapse_state-simdt*CHUTE_DEFLATE_TIME, 0.0);
			SetAnimation(anim_collapse, anim_collapse_state);
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkPreStep: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkPreStep" );
		abort();
	}
}

void DragChute::clbkLoadStateEx(FILEHANDLE scn, void *status)
{
	try
	{
		char* line;

		while(oapiReadScenario_nextline(scn, line)) {
			if(!_strnicmp(line, "CHUTE_INFLATION", 15)) {
				sscanf_s(line+15, "%lf", &anim_collapse_state);
				SetAnimation(anim_collapse, anim_collapse_state);
			}
			else ParseScenarioLineEx(line, status);
		}
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkLoadStateEx" );
		abort();
	}
}

void DragChute::clbkSaveState(FILEHANDLE scn)
{
	try
	{
		VESSEL4::clbkSaveState(scn); //default parameters
		oapiWriteScenario_float(scn, "CHUTE_INFLATION", anim_collapse_state);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_DragChute) [FATAL ERROR] Exception in DragChute::clbkSaveState" );
		abort();
	}
}

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
		return new DragChute(vessel, flightmodel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_DragChute) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_DragChute) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit(VESSEL* vessel)
{
	try
	{
		if (vessel) delete static_cast<DragChute*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_DragChute) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_DragChute) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}
