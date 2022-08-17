#include "MotorValve.h"
#include "MathSSV.h"
#include "assert.h"


MotorValve::MotorValve( const string& name, double initpos, double rate, PressureSource* psource, PressureSource* psourceinvent ):BasicValve( name, initpos, rate )
{
	this->psource = psource;
	this->psourceinvent = psourceinvent;
}

MotorValve::~MotorValve( void )
{
	return;
}

void MotorValve::ConnectInput( DiscreteBundle* pBundle, int iLine )
{
	dipInput.Connect( pBundle, iLine );
	return;
}

void MotorValve::ConnectPositionSensor( unsigned int output, bool open, DiscreteBundle* pBundle, int iLine )
{
	assert( (output <= 1) && "MotorValve::ConnectPositionSensor.output" );
	if (open) dopPosOP[output].Connect( pBundle, iLine );
	else dopPosCL[output].Connect( pBundle, iLine );
	return;
}

void MotorValve::OnPostStep( double fSimT, double fDeltaT, double fMJD )
{
	double motorpwr = dipInput.GetVoltage();
	if (motorpwr != 0.0) pos = range( 0.0, pos + (motorpwr * rate * fDeltaT), 1.0 );

	if (pos == 1.0)
	{
		dopPosOP[0].SetLine();
		dopPosOP[1].SetLine();
		dopPosCL[0].ResetLine();
		dopPosCL[1].ResetLine();
	}
	else if (pos == 0.0)
	{
		dopPosOP[0].ResetLine();
		dopPosOP[1].ResetLine();
		dopPosCL[0].SetLine();
		dopPosCL[1].SetLine();
	}
	else
	{
		dopPosOP[0].ResetLine();
		dopPosOP[1].ResetLine();
		dopPosCL[0].ResetLine();
		dopPosCL[1].ResetLine();
	}
	return;
}

double MotorValve::Use( double flow, int source )
{
	if (pos == 0.0)
	{
		if (psourceinvent != nullptr) return psourceinvent->Use( flow, 0 );
		else return 0;
	}
	else
	{
		if (psourceinvent != nullptr) return pos * psource->Use( flow, 0 );
		else return 0;
	}
}
