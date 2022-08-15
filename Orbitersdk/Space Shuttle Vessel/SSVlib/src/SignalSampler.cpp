/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/24   GLS
********************************************/
#include "SignalSampler.h"
#include <cassert>


SignalSampler::SignalSampler( void ):SignalSampler( 1.0 )
{
}

SignalSampler::SignalSampler( double ts )
{
	assert( (ts >= 0.0) && "SignalSampler::SignalSampler.ts" );

	this->ts = ts;
	time = 0.0;
}

SignalSampler::~SignalSampler()
{
}

double SignalSampler::GetValue( double dt, double input )
{
	double val = 0.0;

	time += dt;

	if (time >= ts)
	{
		val = input;
		time = 0.0;
	}
	return val;
}

void SignalSampler::SetSampleTime( double ts )
{
	assert( (ts >= 0.0) && "SignalSampler::SetSampleTime.ts" );

	this->ts = ts;
	return;
}
