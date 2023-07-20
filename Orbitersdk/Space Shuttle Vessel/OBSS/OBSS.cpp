#define ORBITER_MODULE


#include "OBSS.h"
#include <EngConst.h>
#include "meshres_OBSS.h"


const static char* MESHNAME = "SSV\\OBSS\\OBSS";

const VECTOR3 MPM_ATTACH_POS = _V( -0.0813152, -0.229882, 0.0 );
const VECTOR3 MPM_ATTACH_DIR = _V( -0.333478, -0.942758, 0.0 );
const VECTOR3 MPM_ATTACH_ROT = _V(  0.0, 0.0, 1.0 );

const VECTOR3 GF_FWD_ATTACH_POS = _V( -0.042774, 0.230302, 5.88137 );
const VECTOR3 GF_FWD_ATTACH_DIR = _V( -0.182579, 0.983191, 0.0 );
const VECTOR3 GF_FWD_ATTACH_ROT = _V(  0.0, 0.0, -1.0 );

const VECTOR3 GF_MID_ATTACH_POS = _V( -0.042774, 0.230302, -0.2286 );
const VECTOR3 GF_MID_ATTACH_DIR = _V( -0.182579, 0.983191, 0.0 );
const VECTOR3 GF_MID_ATTACH_ROT = _V(  0.0, 0.0, -1.0 );

const VECTOR3 PWP_ATTACH_POS = _V( -0.0813152, -0.229882, -8.77443 );
const VECTOR3 PWP_ATTACH_DIR = _V( -0.333478, -0.942758, 0.0 );
const VECTOR3 PWP_ATTACH_ROT = _V( 0.0, 0.0, 1.0 );

constexpr double MASS = 540.0 * LBM2KG;// [kg]


DLLCLBK VESSEL *ovcInit( OBJHANDLE vessel, int flightmodel )
{
	try
	{
		return new OBSS( vessel );
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in ovcInit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in ovcInit" );
		abort();
	}
}

DLLCLBK void ovcExit( VESSEL *vessel )
{
	try
	{
		if (vessel) delete static_cast<OBSS*>(vessel);
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in ovcExit: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in ovcExit" );
		abort();
	}
}


OBSS::OBSS( OBJHANDLE hVessel ):VESSEL4( hVessel )
{
	return;
}

OBSS::~OBSS( void )
{
	return;
}

void OBSS::clbkSetClassCaps( FILEHANDLE cfg )
{
	try
	{
		hMesh = oapiLoadMeshGlobal( MESHNAME );
		mesh_idx = AddMesh( hMesh );
		SetMeshVisibilityMode( mesh_idx, MESHVIS_ALWAYS );
		SetSize( 10.0 );
		SetCrossSections( _V( 6.0, 5.81, 0.25 ) );
		SetPMI( _V( 18.95, 18.95, 0.02 ) );
		SetCameraOffset( _V( 0.0, 0.0, 0.0 ) );
		SetEmptyMass( MASS );

		ahToMPM = CreateAttachment( true, MPM_ATTACH_POS, MPM_ATTACH_DIR, MPM_ATTACH_ROT, "MPM" );
		ahToGF_fwd = CreateAttachment( true, GF_FWD_ATTACH_POS, GF_FWD_ATTACH_DIR, GF_FWD_ATTACH_ROT, "GF" );
		ahToGF_mid = CreateAttachment( true, GF_MID_ATTACH_POS, GF_MID_ATTACH_DIR, GF_MID_ATTACH_ROT, "GF" );
		ahToPWP = CreateAttachment( false, PWP_ATTACH_POS, PWP_ATTACH_DIR, PWP_ATTACH_ROT, "PWP" );

		DefineAnimations();

		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkSetClassCaps: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkSetClassCaps" );
		abort();
	}
}

void OBSS::clbkPostCreation( void )
{
	try
	{
		// TODO
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkPostCreation: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkPostCreation" );
		abort();
	}
}

void OBSS::DefineAnimations( void )
{
	// TODO
	return;
}

void OBSS::clbkVisualCreated( VISHANDLE vis, int refcount )
{
	try
	{
		// TODO
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkVisualCreated: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkVisualCreated" );
		abort();
	}
}

void OBSS::clbkSaveState( FILEHANDLE scn )
{
	try
	{
		VESSEL4::clbkSaveState( scn );

		// TODO
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkSaveState: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkSaveState" );
		abort();
	}
}

void OBSS::clbkLoadStateEx( FILEHANDLE scn, void *status )
{
	try
	{
		char* line;

		while (oapiReadScenario_nextline( scn, line ))
		{
			// TODO
			ParseScenarioLineEx( line, status );
		}
		return;
	}
	catch (std::exception &e)
	{
		oapiWriteLogV( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkLoadStateEx: %s", e.what() );
		abort();
	}
	catch (...)
	{
		oapiWriteLog( "(SSV_OBSS) [FATAL ERROR] Exception in OBSS::clbkLoadStateEx" );
		abort();
	}
}
