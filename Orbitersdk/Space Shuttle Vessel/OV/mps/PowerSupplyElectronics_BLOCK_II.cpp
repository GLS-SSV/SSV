/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "PowerSupplyElectronics_BLOCK_II.h"
#include "MPSdefs.h"


namespace mps
{
	PowerSupplyElectronics_BLOCK_II::PowerSupplyElectronics_BLOCK_II( int ch, SSMEController* Controller ):PowerSupplyElectronics( ch, Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " PowerSupplyElectronics_BLOCK_II::PowerSupplyElectronics_BLOCK_II in" );
#endif// _MPSDEBUG

#ifdef _MPSDEBUG
		oapiWriteLog( " PowerSupplyElectronics_BLOCK_II::PowerSupplyElectronics_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	PowerSupplyElectronics_BLOCK_II::~PowerSupplyElectronics_BLOCK_II( void )
	{
		return;
	}

	void PowerSupplyElectronics_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		PowerSupplyElectronics::OnSaveState( scn );
		return;
	}

	bool PowerSupplyElectronics_BLOCK_II::OnParseLine( const char* line )
	{
		return PowerSupplyElectronics::OnParseLine( line );
	}
}
