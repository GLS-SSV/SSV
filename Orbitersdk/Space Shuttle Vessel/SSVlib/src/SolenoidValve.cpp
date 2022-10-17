/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/15   GLS
2020/05/10   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
2022/09/30   GLS
********************************************/
#include <SolenoidValve.h>
#include <MathSSV.h>
#include <cassert>


SolenoidValve::SolenoidValve( double initpos, double rate, bool NormallyClosed, PressureSource* psource, PressureSource* psourceinvent )
{
	assert( (initpos >= 0.0) && (initpos <= 1.0) && "SolenoidValve::SolenoidValve.initpos" );
	assert( (rate > 0.0) && "SolenoidValve::SolenoidValve.rate" );
	pos = initpos;
	this->rate = rate / 100.0;
	this->NormallyClosed = NormallyClosed;
	this->psource = psource;
	this->psourceinvent = psourceinvent;
}

SolenoidValve::~SolenoidValve( void )
{
	return;
}

void SolenoidValve::Connect( unsigned short input, DiscreteBundle* pBundle, unsigned short iLine )
{
	assert( (input <= 1) && "SolenoidValve::Connect.input" );
	dipInput[input].Connect( pBundle, iLine );
	return;
}

double SolenoidValve::GetPos( void ) const
{
	return pos;
}

void SolenoidValve::tmestp( double dt )
{
	double mpos = 0.0;

	if ((dipInput[0].IsSet() == true) || (dipInput[1].IsSet() == true)) mpos = (float)NormallyClosed;
	else mpos = (float)!NormallyClosed;

	if (mpos != pos)
	{
		if (mpos > pos)
		{
			pos += (rate * dt);
			if (pos > 1.0) pos = 1.0;
		}
		else
		{
			pos -= (rate * dt);
			if (pos < 0.0) pos = 0.0;
		}
	}
	return;
}

void SolenoidValve::_backdoor( double ipos )
{
	assert( (ipos >= 0.0) && (ipos <= 1.0) && "SolenoidValve::_backdoor.ipos" );
	pos = ipos;
	return;
}

double SolenoidValve::Use( double flow, int source )
{
	if (pos == 0.0)// TODO improve?
	{
		if (psourceinvent != nullptr) return psourceinvent->Use( flow, 0 );
		else return 0.0;
	}
	else return pos * psource->Use( flow, 0 );
}


SolenoidValve_2::SolenoidValve_2( const string& name, double initpos, double rate, bool NormallyClosed, PressureSource* psource, PressureSource* psourceinvent ):BasicValve( name, initpos, rate )
{
	this->NormallyClosed = NormallyClosed;
	this->psource = psource;
	this->psourceinvent = psourceinvent;
}

SolenoidValve_2::~SolenoidValve_2( void )
{
	return;
}

void SolenoidValve_2::ConnectInput( unsigned short input, DiscreteBundle* pBundle, unsigned short iLine )
{
	assert( (input <= 1) && "SolenoidValve_2::ConnectInput.input" );
	dipInput[input].Connect( pBundle, iLine );
	return;
}

void SolenoidValve_2::ConnectPositionSensor( unsigned short output, DiscreteBundle* pBundle, unsigned short iLine )
{
	assert( (output <= 1) && "SolenoidValve_2::ConnectPositionSensor.output" );
	dopPos[output].Connect( pBundle, iLine );
	return;
}

void SolenoidValve_2::OnPostStep( double simt, double simdt, double mjd )
{
	double mpos = 0.0;

	if ((dipInput[0].IsSet() == true) || (dipInput[1].IsSet() == true)) mpos = (float)NormallyClosed;
	else mpos = (float)!NormallyClosed;

	if (mpos != pos)
	{
		if (mpos > pos)
		{
			pos += (rate * simdt);
			if (pos > 1.0) pos = 1.0;
		}
		else
		{
			pos -= (rate * simdt);
			if (pos < 0.0) pos = 0.0;
		}
	}
	return;
}

double SolenoidValve_2::Use( double flow, int source )
{
	if (pos == 0.0)
	{
		if (psourceinvent != nullptr) return psourceinvent->Use( flow, 0 );
		else return 0.0;
	}
	else
	{
		if (psourceinvent != nullptr) return pos * psource->Use( flow, 0 );
		else return 0.0;
	}
}


SolenoidLatchingValve::SolenoidLatchingValve( const string& name, double initpos, double rate, PressureSource* psource, PressureSource* psourceinvent ):BasicValve( name, initpos, rate )
{
	this->psource = psource;
	this->psourceinvent = psourceinvent;
}

SolenoidLatchingValve::~SolenoidLatchingValve( void )
{
	return;
}

void SolenoidLatchingValve::ConnectInput( unsigned short input, bool open, DiscreteBundle* pBundle, unsigned short iLine )
{
	assert( (input <= 1) && "SolenoidLatchingValve::ConnectInput.input" );
	if (open) dipInputOP[input].Connect( pBundle, iLine );
	else dipInputCL[input].Connect( pBundle, iLine );
	return;
}

void SolenoidLatchingValve::ConnectPositionSensor( unsigned short output, DiscreteBundle* pBundle, unsigned short iLine )
{
	assert( (output <= 1) && "SolenoidLatchingValve::ConnectPositionSensor.output" );
	dopPos[output].Connect( pBundle, iLine );
	return;
}

void SolenoidLatchingValve::OnPostStep( double simt, double simdt, double mjd )
{
	double mpos = range( 0.0, Round( pos ) + (int)(dipInputOP[0].IsSet() | dipInputOP[1].IsSet()) - (int)(dipInputCL[0].IsSet() | dipInputCL[1].IsSet()), 1.0 );

	if (mpos != pos)
	{
		if (mpos > pos)
		{
			pos += (rate * simdt);
			if (pos > 1.0) pos = 1.0;
		}
		else
		{
			pos -= (rate * simdt);
			if (pos < 0.0) pos = 0.0;
		}
	}

	if (pos == 1.0)
	{
		dopPos[0].SetLine();
		dopPos[1].SetLine();
	}
	else if (pos == 0.0)
	{
		dopPos[0].ResetLine();
		dopPos[1].ResetLine();
	}
	return;
}

double SolenoidLatchingValve::Use( double flow, int source )
{
	if (pos == 0.0)
	{
		if (psourceinvent != nullptr) return psourceinvent->Use( flow, 0 );
		else return 0.0;
	}
	else
	{
		if (psourceinvent != nullptr) return pos * psource->Use( flow, 0 );
		else return 0.0;
	}
}
