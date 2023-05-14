#include "BusManager.h"
#include "BusTerminal.h"
#include <cassert>


BusManager::BusManager( void )
{
	return;
}

BusManager::~BusManager( void )
{
	return;
}

void BusManager::Connect( const BUS_ID id, BusTerminal* terminal )
{
	assert( (id < ___LAST___BUS_ID_SIZE) && "id < ___LAST___BUS_ID_SIZE" );

	terminals[id].push_back( terminal );
	return;
}

void BusManager::Tx( const BUS_ID id, void* data, const unsigned short datalen, BusTerminal* src )
{
	assert( (id < ___LAST___BUS_ID_SIZE) && "id < ___LAST___BUS_ID_SIZE" );

	bool connected = false;// for checking that sender is connected to this bus
	for (auto x : terminals[id])
	{
		if (x != src) x->Rx( id, data, datalen );
		else connected = true;
	}

	assert( connected && "BusManager::Tx sender not connected to this bus" );
	return;
}
