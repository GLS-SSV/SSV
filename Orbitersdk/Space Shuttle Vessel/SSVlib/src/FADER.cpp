/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "FADER.h"
#include <MathSSV.h>
#include <cassert>


FADER::FADER( void ):FADER( 1.0 )
{
}

FADER::FADER( double t )
{
	assert( (t > 0.0) && "FADER::FADER.t" );

	this->t = t;
	val = 1.0;
	rate = val / t;
}

FADER::~FADER()
{
}

void FADER::SetValue( double val )
{
	this->val = val;
	rate = val / t;
	return;
}

double FADER::Fade( double dt )
{
	if (val == 0.0) return 0.0;

	double sgn = sign( val );
	val = val - (sgn * rate * dt);
	if (sign( val ) != sgn) val = 0.0;
	return val;
}
