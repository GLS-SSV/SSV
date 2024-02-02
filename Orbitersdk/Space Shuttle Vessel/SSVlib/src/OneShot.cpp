#include <OneShot.h>
#include <MathSSV.h>
#include <cassert>


OneShot::OneShot( double t )
{
	assert( (t > 0.0) && "OneShot::OneShot.t" );

	this->t = t;
	tcount = 0;
	return;
}

OneShot::~OneShot()
{
	return;
}

bool OneShot::Run( const double dt, const bool input )
{
	if (input)
	{
		tcount = t;
		return true;
	}
	else
	{
		tcount -= dt;
		if (tcount < 0) tcount = 0;

		return tcount > 0;
	}
}
