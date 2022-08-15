/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "PowerSupplyElectronics.h"
#include "SSMEController.h"
#include "DigitalComputerUnit.h"
#include "ComputerInterfaceElectronics.h"
#include "MPSdefs.h"


namespace mps
{
	PowerSupplyElectronics::PowerSupplyElectronics( int ch, SSMEController* Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " PowerSupplyElectronics::PowerSupplyElectronics in" );
#endif// _MPSDEBUG

		this->ch = ch;
		this->Controller = Controller;
		PowerOn = true;

#ifdef _MPSDEBUG
		oapiWriteLog( " PowerSupplyElectronics::PowerSupplyElectronics out" );
#endif// _MPSDEBUG
		return;
	}

	PowerSupplyElectronics::~PowerSupplyElectronics( void )
	{
		return;
	}

	void PowerSupplyElectronics::OnSaveState( FILEHANDLE scn ) const
	{
		return;
	}

	bool PowerSupplyElectronics::OnParseLine( const char* line )
	{
		return false;
	}

	void PowerSupplyElectronics::Realize( void )
	{
		DCU = Controller->DCU[ch];
		if (ch == chA) CIEOpposite = Controller->CIE[chB];
		else CIEOpposite = Controller->CIE[chA];
		return;
	}

	void PowerSupplyElectronics::tmestp( double time )
	{
		if (AC.IsSet() == false)
		{
			if (PowerOn == true)
			{
				// power failure on the way
				DCU->PowerFailureSense();
				CIEOpposite->PowerBusDown();
			}
		}
		PowerOn = AC.IsSet();
		return;
	}

	void PowerSupplyElectronics::ConnectPower( DiscreteBundle* AC )
	{
		this->AC.Connect( AC, ch );
		return;
	}

	bool PowerSupplyElectronics::Power( void ) const
	{
		return PowerOn;
	}
}