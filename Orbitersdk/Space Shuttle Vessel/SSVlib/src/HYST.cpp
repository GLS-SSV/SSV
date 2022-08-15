/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/24   GLS
********************************************/
#include "HYST.h"
#include <cassert>


HYST::HYST( void ):HYST( 1.0, 2.0 )
{
}

HYST::HYST( double LIM1, double LIM2 )
{
	assert( (LIM1 > 0.0) && "HYST::HYST.LIM1" );
	assert( (LIM2 > 0.0) && "HYST::HYST.LIM2" );
	// TODO check logic to see if LIM2 can be smaller than LIM1

	this->LIM1 = LIM1;
	this->LIM2 = LIM2;
	Y = 0;
}

HYST::~HYST()
{
}

int HYST::GetValue( double X )
{
	if (X >= LIM2) Y = 1;
	else if (X > LIM1);// Y = Y;
	else if (X >= -LIM1) Y = 0;
	else if (X > -LIM2);// Y = Y;
	else Y = -1;

	return Y;
}

void HYST::SetLimits( double LIM1, double LIM2  )
{
	assert( (LIM1 > 0.0) && "HYST::SetLimits.LIM1" );
	assert( (LIM2 > 0.0) && "HYST::SetLimits.LIM2" );

	this->LIM1 = LIM1;
	this->LIM2 = LIM2;
	return;
}
