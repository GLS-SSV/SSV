/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "InputElectronics_BLOCK_II.h"
#include "SSME.h"
#include "SSMEController.h"
#include "PowerSupplyElectronics.h"
#include "OutputElectronics.h"
#include "MPSdefs.h"


namespace mps
{
	InputElectronics_BLOCK_II::InputElectronics_BLOCK_II( int ch, SSMEController* Controller ):InputElectronics( ch, Controller )
	{
#ifdef _MPSDEBUG
		oapiWriteLogV( " InputElectronics_BLOCK_II::InputElectronics_BLOCK_II in || ch:%d", ch );
#endif// _MPSDEBUG

#ifdef _MPSDEBUG
		oapiWriteLogV( " InputElectronics_BLOCK_II::InputElectronics_BLOCK_II out" );
#endif// _MPSDEBUG
		return;
	}

	InputElectronics_BLOCK_II::~InputElectronics_BLOCK_II( void )
	{
		return;
	}

	void InputElectronics_BLOCK_II::OnSaveState( FILEHANDLE scn ) const
	{
		InputElectronics::OnSaveState( scn );
		return;
	}

	bool InputElectronics_BLOCK_II::OnParseLine( const char* line )
	{
		return InputElectronics::OnParseLine( line );
	}

	void InputElectronics_BLOCK_II::tmestp( double time )
	{
		// check power supply
		if (PSE->Power() == false) return;

		OE->GetSH( samplehold );
		OE->GetPOS( actpos );
		return;
	}
}