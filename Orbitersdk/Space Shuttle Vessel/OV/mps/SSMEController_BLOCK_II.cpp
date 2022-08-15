/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "SSMEController_BLOCK_II.h"
#include "VehicleInterfaceElectronics_BLOCK_II.h"
#include "PowerSupplyElectronics_BLOCK_II.h"
#include "InputElectronics_BLOCK_II.h"
#include "OutputElectronics_BLOCK_II.h"
#include "DigitalComputerUnit_BLOCK_II.h"
#include "ComputerInterfaceElectronics_BLOCK_II.h"
#include "MPSdefs.h"
#ifdef _MPSDEBUG
#include <string>
#endif// _MPSDEBUG



namespace mps
{
	SSMEController_BLOCK_II::SSMEController_BLOCK_II( SSME* eng, const std::string& sw ):SSMEController( eng )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " SSMEController_BLOCK_II::SSMEController_BLOCK_II in || sw:%s", sw.c_str() );
#endif// _MPSDEBUG

		VIE = new VehicleInterfaceElectronics_BLOCK_II( this );
		PSE[chA] = new PowerSupplyElectronics_BLOCK_II( chA, this );
		PSE[chB] = new PowerSupplyElectronics_BLOCK_II( chB, this );
		IE[chA] = new InputElectronics_BLOCK_II( chA, this );
		IE[chB] = new InputElectronics_BLOCK_II( chB, this );
		OE[chA] = new OutputElectronics_BLOCK_II( chA, eng, this );
		OE[chB] = new OutputElectronics_BLOCK_II( chB, eng, this  );
		DCU[chA] = new DigitalComputerUnit_BLOCK_II( chA, sw, this );
		DCU[chB] = new DigitalComputerUnit_BLOCK_II( chB, sw, this );
		CIE[chA] = new ComputerInterfaceElectronics_BLOCK_II( chA, this );
		CIE[chB] = new ComputerInterfaceElectronics_BLOCK_II( chB, this );

#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEController_BLOCK_II::SSMEController_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	SSMEController_BLOCK_II::~SSMEController_BLOCK_II( void )
	{
		delete VIE;
		delete PSE[chA];
		delete PSE[chB];
		delete IE[chA];
		delete IE[chB];
		delete OE[chA];
		delete OE[chB];
		delete DCU[chA];
		delete DCU[chB];
		delete CIE[chA];
		delete CIE[chB];
		return;
	}

	void SSMEController_BLOCK_II::tmestp( double time, double tmestp )
	{
		PSE[chA]->tmestp( time );
		PSE[chB]->tmestp( time );
		IE[chA]->tmestp( time );
		IE[chB]->tmestp( time );
		CIE[chA]->tmestp( time, tmestp );
		CIE[chB]->tmestp( time, tmestp );
		DCU[chA]->tmestp( time, tmestp );
		DCU[chB]->tmestp( time, tmestp );
		VIE->tmestp( time );// after DCU
		OE[chA]->tmestp( time, tmestp );
		OE[chB]->tmestp( time, tmestp );
		return;
	}
}