/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "FILT2.h"
#include "MathSSV.h"


FILT2::FILT2( void ):FILT2( 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 )
{
}

FILT2::FILT2( double G1, double G2, double G3, double G4, double G5 ):FILT2( G1, G2, G3, G4, G5, 0.0, 0.0 )
{
}

FILT2::FILT2( double LIM_L, double LIM_U ):FILT2( 0.0, 0.0, 0.0, 0.0, 0.0, LIM_L, LIM_U )
{
}

FILT2::FILT2( double G1, double G2, double G3, double G4, double G5, double LIM_L, double LIM_U )
{
	this->G1 = G1;
	this->G2 = G2;
	this->G3 = G3;
	this->G4 = G4;
	this->G5 = G5;
	this->LIM_L = LIM_L;
	this->LIM_U = LIM_U;
	Y0[0] = 0.0;
	Y0[1] = 0.0;
	X0[0] = 0.0;
	X0[1] = 0.0;
}

FILT2::~FILT2()
{
}

void FILT2::SaveState( char* line ) const
{
	sprintf( line, "%lf %lf %lf %lf", Y0[0], Y0[1], X0[0], X0[1] );
	return;
}

void FILT2::LoadState( const char* line )
{
	sscanf_s( line, "%lf %lf %lf %lf", &Y0[0], &Y0[1], &X0[0], &X0[1] );
	return;
}

double FILT2::GetValue( double Xn )
{
	double Yn = (G1 * Xn) + (G2 * X0[0]) - (G4 * Y0[0]) + (G3 * X0[1]) - (G5 * Y0[1]);

	if (LIM_L != LIM_U) Yn = range( LIM_L, Yn, LIM_U );

	Y0[1] = Y0[0];
	X0[1] = X0[0];
	Y0[0] = Yn;
	X0[0] = Xn;
	return Yn;
}

void FILT2::SetGains( double G1, double G2, double G3, double G4, double G5 )
{
	this->G1 = G1;
	this->G2 = G2;
	this->G3 = G3;
	this->G4 = G4;
	this->G5 = G5;
	return;
}

void FILT2::SetLimits( double LIM_L, double LIM_U )
{
	this->LIM_L = LIM_L;
	this->LIM_U = LIM_U;
	return;
}

void FILT2::SetInitialValue( double IC )
{
	Y0[0] = IC;
	return;
}
