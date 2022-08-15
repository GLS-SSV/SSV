/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "BasicValve.h"
#include <cassert>


BasicValve::BasicValve( const string& name, double initpos, double rate )
{
	assert( (initpos >= 0.0) && (initpos <= 1.0) && "BasicValve::BasicValve.initpos" );
	assert( (rate > 0.0) && "BasicValve::BasicValve.rate" );

	this->name = name;
	pos = initpos;
	this->rate = rate / 100;
}

BasicValve::~BasicValve( void )
{
}

double BasicValve::GetPos( void ) const
{
	return pos;
}

bool BasicValve::OnParseLine( const char* line )
{
	if (!_strnicmp( line, name.c_str(), name.length() ))
	{
		double tmp = 0.0;
		sscanf_s( line + name.length(), "%lf", &tmp );
		assert( (tmp >= 0.0) && (tmp <= 1.0) && "BasicValve::OnParseLine.tmp" );
		pos = tmp;
		return true;
	}
	else return false;
}

void BasicValve::OnSaveState( FILEHANDLE scn ) const
{
	oapiWriteScenario_float( scn, (char*)name.c_str(), pos );
	return;
}

void BasicValve::OnPreStep( double simt, double simdt, double mjd )
{
	return;
}

void BasicValve::OnPostStep( double simt, double simdt, double mjd )
{
	return;
}
