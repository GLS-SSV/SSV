/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "ComputerInterfaceElectronics_BLOCK_II.h"
#include "VehicleInterfaceElectronics.h"
#include "MPSdefs.h"


namespace mps
{
	ComputerInterfaceElectronics_BLOCK_II::ComputerInterfaceElectronics_BLOCK_II( int ch, SSMEController* Controller ):ComputerInterfaceElectronics( ch, Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " ComputerInterfaceElectronics_BLOCK_II::ComputerInterfaceElectronics_BLOCK_II in" );
#endif// _MPSDEBUG

#ifdef _MPSDEBUG
		oapiWriteLog( " ComputerInterfaceElectronics_BLOCK_II::ComputerInterfaceElectronics_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	ComputerInterfaceElectronics_BLOCK_II::~ComputerInterfaceElectronics_BLOCK_II( void )
	{
		return;
	}

	void ComputerInterfaceElectronics_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		ComputerInterfaceElectronics::OnSaveState( scn );
		return;
	}

	bool ComputerInterfaceElectronics_BLOCK_II::OnParseLine( const char* line )
	{
		return ComputerInterfaceElectronics::OnParseLine( line );
	}
}