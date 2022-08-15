/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/05/10   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/24   GLS
********************************************/
#include "HydraulicActuatedValve.h"
#include "PressureSource.h"
#include <cassert>


HydraulicActuatedValve::HydraulicActuatedValve( double initpos, double rate_hyd )
{
	assert( (initpos >= 0) && (initpos <= 1) && "HydraulicActuatedValve::HydraulicActuatedValve.initpos" );
	assert( (rate_hyd > 0) && "HydraulicActuatedValve::HydraulicActuatedValve.rate_hyd" );
	pos = initpos;
	this->rate_hyd = rate_hyd / 100;
	this->PneumaticClose = nullptr;
	this->SequenceValveOpenPos = 0;
}

HydraulicActuatedValve::HydraulicActuatedValve( double initpos, double rate_hyd, double rate_pneu, PressureSource* PneumaticClose, double SequenceValveOpenPos )
{
	assert( (initpos >= 0) && (initpos <= 1) && "HydraulicActuatedValve::HydraulicActuatedValve.initpos" );
	assert( (rate_hyd > 0) && "HydraulicActuatedValve::HydraulicActuatedValve.rate_hyd" );
	assert( (rate_pneu > 0) && "HydraulicActuatedValve::HydraulicActuatedValve.rate_pneu" );
	assert( (SequenceValveOpenPos >= 0) && (SequenceValveOpenPos <= 1) && "HydraulicActuatedValve::HydraulicActuatedValve.SequenceValveOpenPos" );
	pos = initpos;
	this->rate_hyd = rate_hyd / 100;
	this->rate_pneu = rate_pneu / 100;
	this->PneumaticClose = PneumaticClose;
	this->SequenceValveOpenPos = SequenceValveOpenPos;
}

HydraulicActuatedValve::~HydraulicActuatedValve( void )
{
	return;
}

void HydraulicActuatedValve::Connect( DiscreteBundle* pBundle, DiscreteBundle* pBundleHYD )// HACK makeshift hyd supply
{
	dipServovalve[0].Connect( pBundle, 0 );
	dipServovalve[1].Connect( pBundle, 1 );
	dipFailOperationalServoswitch[0].Connect( pBundle, 2 );
	dipFailOperationalServoswitch[1].Connect( pBundle, 3 );
	dipFailSafeServoswitch[0].Connect( pBundle, 4 );
	dipFailSafeServoswitch[1].Connect( pBundle, 5 );

	dipHYD.Connect( pBundleHYD, 4 );
	return;
}

double HydraulicActuatedValve::GetPos( void ) const// TODO use DiscreteBundle
{
	return pos;
}

void HydraulicActuatedValve::tmestp( double dt )
{
	if ((dipFailSafeServoswitch[0].IsSet() == true) || (dipFailSafeServoswitch[1].IsSet() == true))
	{
		// hyd
		int SV = 0;// default SV A
		if ((dipFailOperationalServoswitch[0].IsSet() == true) || (dipFailOperationalServoswitch[1].IsSet() == true)) SV = 1;// SV B

		if ((dipHYD.GetVoltage() * 1000) < 1500) return;// no moviment below 1500psia

		double mpos = dipServovalve[SV].GetVoltage() / 5;

		if (mpos != pos)
		{
			if (mpos > pos)
			{
				pos += (rate_hyd * dt);
				if (pos > mpos) pos = mpos;
			}
			else
			{
				pos -= (rate_hyd * dt);
				if (pos < mpos) pos = mpos;
			}
		}
	}
	else
	{
		if (PneumaticClose != nullptr)
		{
			// pneu
			if (PneumaticClose->Use( 0.0, 0 ) >= MIN_PRESS_CLOSE_HAV)// just get press
			{
				// close
				if (pos > 0)
				{
					PneumaticClose->Use( HE_USE_CLOSE_HAV, 0 );// use now
					pos -= (rate_pneu * dt);
					if (pos < 0) pos = 0;
				}
			}
		}
	}
	return;
}

void HydraulicActuatedValve::_backdoor( double ipos )
{
	assert( (ipos >= 0) && (ipos <= 1) && "HydraulicActuatedValve::_backdoor.ipos" );
	pos = ipos;
	return;
}

double HydraulicActuatedValve::Use( double flow, int source )
{
	if (pos < SequenceValveOpenPos)
	{
		// seq vlv open
		if (PneumaticClose != nullptr) return PneumaticClose->Use( flow, 0 );
		else return 0;
	}
	else
	{
		// seq vlv close
		return 0;
	}
}