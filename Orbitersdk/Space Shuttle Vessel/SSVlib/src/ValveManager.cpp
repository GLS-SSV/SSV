/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/05/22   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/09/30   GLS
********************************************/
#include <ValveManager.h>
#include <BasicValve.h>
#include <cassert>


ValveManager::ValveManager( void )
{
}

ValveManager::~ValveManager( void )
{
	for (auto &x : valves)
	{
		delete x;
	}
	valves.clear();
}


void ValveManager::AddValve( BasicValve *pValve )
{
	assert( (pValve != NULL) && "ValveManager::AddValve.pValve" );

	valves.push_back( pValve );
	return;
}

bool ValveManager::OnParseLine( const char* line )
{
	for (auto &x : valves)
	{
		if (x->OnParseLine( line )) return true;
	}
	return false;
}

void ValveManager::OnSaveState( FILEHANDLE scn ) const
{
	for (auto &x : valves)
	{
		x->OnSaveState( scn );
	}
	return;
}

void ValveManager::OnPreStep( double simt, double simdt, double mjd )
{
	for (auto &x : valves)
	{
		x->OnPostStep( simt, simdt, mjd );
	}
	return;
}

void ValveManager::OnPostStep( double simt, double simdt, double mjd )
{
	for (auto &x : valves)
	{
		x->OnPostStep( simt, simdt, mjd );
	}
	return;
}
