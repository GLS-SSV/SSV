#include "BusTerminal.h"
#include "BusManager.h"
#include <cassert>


unsigned int CalcParity( const unsigned int val )
{
	unsigned int ret = val;
	ret = ret ^ (ret >> 1);
	ret = ret ^ (ret >> 2);
	ret = ret ^ (ret >> 4);
	ret = ret ^ (ret >> 8);
	ret = ret ^ (ret >> 16);
	return ret & 1;
}


BusTerminal::BusTerminal( BusManager* busmanager ):busmanager(busmanager)
{
	assert( busmanager && "busmanager != null" );
	return;
}

BusTerminal::~BusTerminal( void )
{
	return;
}

void BusTerminal::BusConnect( const BUS_ID id )
{
	busmanager->Connect( id, this );
	return;
}

void BusTerminal::Tx( const BUS_ID id, void* data, const unsigned short datalen )
{
	busmanager->Tx( id, data, datalen, this );
	return;
}
