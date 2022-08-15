/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/15   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "Sensor.h"
#include <stdlib.h>
#include <cassert>


Sensor::Sensor( double MinValue, double MaxValue, double FSerror )
{
	assert( (MinValue < MaxValue) && "Sensor::Sensor.(MinValue < MaxValue)" );

	this->MaxValue = MaxValue;
	this->MinValue = MinValue;

	conversor = 5 / (MaxValue - MinValue);

	error = (MaxValue - MinValue) * FSerror * (((double)rand() / (RAND_MAX + 1)) - 0.5);
	return;
}

Sensor::~Sensor( void )
{
	return;
}

void Sensor::Connect( DiscreteBundle* pBundle, unsigned short iLine )
{
	dipOutput.Connect( pBundle, iLine );
	return;
}

void Sensor::Disconnect( void )
{
	dipOutput.ResetLine();// set to 0 before disconnecting
	dipOutput.Disconnect();
	return;
}

void Sensor::SetValue( double value )
{
	value += error;

	if (value > MaxValue) value = MaxValue;
	else if (value < MinValue) value = MinValue;

	dipOutput.SetLine( static_cast<float>((value - MinValue) * conversor) );
	return;
}