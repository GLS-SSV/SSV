/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "VehicleInterfaceElectronics_BLOCK_II.h"
#include "MPSdefs.h"


namespace mps
{
	VehicleInterfaceElectronics_BLOCK_II::VehicleInterfaceElectronics_BLOCK_II( SSMEController* Controller ):VehicleInterfaceElectronics( Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " VehicleInterfaceElectronics_BLOCK_II::VehicleInterfaceElectronics_BLOCK_II in" );
#endif// _MPSDEBUG

#ifdef _MPSDEBUG
		oapiWriteLog( " VehicleInterfaceElectronics_BLOCK_II::VehicleInterfaceElectronics_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	VehicleInterfaceElectronics_BLOCK_II::~VehicleInterfaceElectronics_BLOCK_II( void )
	{
		return;
	}

	void VehicleInterfaceElectronics_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		VehicleInterfaceElectronics::OnSaveState( scn );
		return;
	}

	bool VehicleInterfaceElectronics_BLOCK_II::OnParseLine( const char* line )
	{
		return VehicleInterfaceElectronics::OnParseLine( line );
	}

	void VehicleInterfaceElectronics_BLOCK_II::tmestp( double time )
	{
		int count = 0;

		while (count < 3)// TODO find if/how/when the registers are reset, for now it stays like this
		{
			// reset "register"
			Command[count] = 0;
			count++;
		}

		return;
	}

	void VehicleInterfaceElectronics_BLOCK_II::SwitchVRC( void )
	{
		VehicleDataSwitch = false;
		return;
	}

	void VehicleInterfaceElectronics_BLOCK_II::RestoreVRC( void )
	{
		VehicleDataSwitch = true;
		return;
	}
}