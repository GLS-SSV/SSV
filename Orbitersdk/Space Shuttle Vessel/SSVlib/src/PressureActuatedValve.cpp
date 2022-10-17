/******* SSV File Modification Notice *******
Date         Developer
2020/04/01   GLS
2020/04/15   GLS
2020/05/10   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/09/30   GLS
********************************************/
#include <PressureActuatedValve.h>
#include <cassert>


PressureActuatedValve::PressureActuatedValve( double initpos, double rate, PressureSource* OP, PressureSource* CL, PressureSource* psource, PressureSource* psourceinvent )
{
	assert( (initpos >= 0) && (initpos <= 1) && "PressureActuatedValve::PressureActuatedValve.initpos" );
	assert( (rate > 0) && "PressureActuatedValve::PressureActuatedValve.rate" );
	pos = initpos;
	this->rate = rate / 100;
	this->OP = OP;
	this->CL = CL;
	this->psource = psource;
	this->psourceinvent = psourceinvent;

	// set indications
	if (pos == 0)
	{
		dopCLInd[0].SetLine();
		dopCLInd[1].SetLine();
		dopOPInd[0].ResetLine();
		dopOPInd[1].ResetLine();
	}
	else if (pos == 1)
	{
		dopCLInd[0].ResetLine();
		dopCLInd[1].ResetLine();
		dopOPInd[0].SetLine();
		dopOPInd[1].SetLine();
	}
	else
	{
		dopCLInd[0].ResetLine();
		dopCLInd[1].ResetLine();
		dopOPInd[0].ResetLine();
		dopOPInd[1].ResetLine();
	}
}

PressureActuatedValve::~PressureActuatedValve( void )
{
	return;
}

void PressureActuatedValve::ConnectIndication( bool openind, unsigned short output, DiscreteBundle* pBundle, unsigned short iLine )
{
	assert( (output <= 1) && "PressureActuatedValve::ConnectIndication.output" );
	if (openind == true) dopOPInd[output].Connect( pBundle, iLine );
	else dopCLInd[output].Connect( pBundle, iLine );
	return;
}

void PressureActuatedValve::SetPressureSources( PressureSource* OP, PressureSource* CL, PressureSource* psource, PressureSource* psourceinvent )
{
	if (OP != nullptr) this->OP = OP;
	if (CL != nullptr) this->CL = CL;
	if (psource != nullptr) this->psource = psource;
	if (psourceinvent != nullptr) this->psourceinvent = psourceinvent;
	return;
}

double PressureActuatedValve::GetPos( void ) const
{
	return pos;
}

void PressureActuatedValve::tmestp( double dt )
{
	double mpos = 0;

	if (OP != nullptr)
	{
		if (CL != nullptr)
		{
			// type 1
			if (OP->Use( 0.0, 0 ) > CL->Use( 0.0, 0 )) mpos = 1;
			else if (OP->Use( 0.0, 0 ) < CL->Use( 0.0, 0 )) mpos = 0;
			else mpos = pos;
		}
		else
		{
			// type 2 NC
			if (OP->Use( 0.0, 0 ) >= MIN_PRESS_OPEN_PAV) mpos = 1;// just get press
			else mpos = 0;
		}
	}
	else
	{
		if (CL != nullptr)
		{
			// type 2 NO
			if (CL->Use( 0.0, 0 ) >= MIN_PRESS_OPEN_PAV) mpos = 0;// just get press
			else mpos = 1;
		}
	}

	if (mpos != pos)
	{
		if (mpos > pos)
		{
			if (OP != nullptr) OP->Use( HE_USE_OPEN_PAV, 0 );// use now
			pos += (rate * dt);
			if (pos > 1) pos = 1;
		}
		else
		{
			if (CL != nullptr) CL->Use( HE_USE_OPEN_PAV, 0 );// use now
			pos -= (rate * dt);
			if (pos < 0) pos = 0;
		}
	}

	// set indications
	if (pos == 0)
	{
		dopCLInd[0].SetLine();
		dopCLInd[1].SetLine();
		dopOPInd[0].ResetLine();
		dopOPInd[1].ResetLine();
	}
	else if (pos == 1)
	{
		dopCLInd[0].ResetLine();
		dopCLInd[1].ResetLine();
		dopOPInd[0].SetLine();
		dopOPInd[1].SetLine();
	}
	else
	{
		dopCLInd[0].ResetLine();
		dopCLInd[1].ResetLine();
		dopOPInd[0].ResetLine();
		dopOPInd[1].ResetLine();
	}
	return;
}

void PressureActuatedValve::_backdoor( double ipos )
{
	assert( (ipos >= 0) && (ipos <= 1) && "PressureActuatedValve::_backdoor.ipos" );
	pos = ipos;

	// set indications
	if (pos == 0)
	{
		dopCLInd[0].SetLine();
		dopCLInd[1].SetLine();
		dopOPInd[0].ResetLine();
		dopOPInd[1].ResetLine();
	}
	else if (pos == 1)
	{
		dopCLInd[0].ResetLine();
		dopCLInd[1].ResetLine();
		dopOPInd[0].SetLine();
		dopOPInd[1].SetLine();
	}
	else
	{
		dopCLInd[0].ResetLine();
		dopCLInd[1].ResetLine();
		dopOPInd[0].ResetLine();
		dopOPInd[1].ResetLine();
	}
	return;
}

double PressureActuatedValve::Use( double flow, int source )
{
	if (pos == 0)// TODO improve?
	{
		if (psourceinvent != nullptr) return psourceinvent->Use( flow, 0 );
		else return 0;
	}
	else
	{
		if (psource != nullptr) return  pos * psource->Use( flow, 0 );
		else return 0;
	}
}
