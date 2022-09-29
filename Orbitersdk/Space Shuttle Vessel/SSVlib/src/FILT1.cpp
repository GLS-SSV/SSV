/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
#include "FILT1.h"
#include <MathSSV.h>


FILT1::FILT1( void ):FILT1( 0.0, 0.0, 0.0, 0.0, 0.0 )
{
}

FILT1::FILT1( double G1, double G2, double G3 ):FILT1( G1, G2, G3, 0.0, 0.0 )
{
}

FILT1::FILT1( double LIM_L, double LIM_U ):FILT1( 0.0, 0.0, 0.0, LIM_L, LIM_U )
{
}

FILT1::FILT1( double G1, double G2, double G3, double LIM_L, double LIM_U )
{
	this->G1 = G1;
	this->G2 = G2;
	this->G3 = G3;
	this->LIM_L = LIM_L;
	this->LIM_U = LIM_U;
	Y0 = 0.0;
	X0 = 0.0;
}

FILT1::~FILT1()
{
}

void FILT1::SaveState( char* line ) const
{
	sprintf( line, "%lf %lf", Y0, X0 );
	return;
}

void FILT1::LoadState( const char* line )
{
	sscanf_s( line, "%lf %lf", &Y0, &X0 );
	return;
}

double FILT1::GetValue( double Xn )
{
	double Yn = (G1 * Xn) + (G2 * X0) - (G3 * Y0);

	if (LIM_L != LIM_U) Yn = range( LIM_L, Yn, LIM_U );

	Y0 = Yn;
	X0 = Xn;
	return Yn;
}

void FILT1::SetGains( double G1, double G2, double G3 )
{
	this->G1 = G1;
	this->G2 = G2;
	this->G3 = G3;
	return;
}

void FILT1::SetLimits( double LIM_L, double LIM_U )
{
	this->LIM_L = LIM_L;
	this->LIM_U = LIM_U;
	return;
}

void FILT1::SetInitialValue( double IC )
{
	Y0 = IC;
	return;
}
