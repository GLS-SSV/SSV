#include "FlipFlopD.h"

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#endif// _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>


FlipFlopD::FlipFlopD( void ):FlipFlopD( false )
{
}

FlipFlopD::FlipFlopD( bool init ):
	clk(true), q(init)
{
}

FlipFlopD::~FlipFlopD( void )
{
}

void FlipFlopD::SaveState( char* line ) const
{
	sprintf( line, "%d", q ? 1 : 0 );
	return;
}

void FlipFlopD::LoadState( const char* line )
{
	int tmp = 0;
	sscanf_s( line, "%d", &tmp );
	q = (tmp != 0);
	return;
}

bool FlipFlopD::run( bool CLK, bool D )
{
	return run( CLK, D, false, false );
}

bool FlipFlopD::run( bool CLK, bool D, bool R )
{
	return run( CLK, D, R, false );
}

bool FlipFlopD::run( bool CLK, bool D, bool R, bool S )
{
	// detect CLK rising edge
	if (!clk)
	{
		if (CLK)
		{
			clk = true;

			// update
			q = D;
		}
	}
	else if (!CLK) clk = false;

	// handle reset and set
	if (R != S)
	{
		if (R) q = false;
		else q = true;
	}

	return q;
}
