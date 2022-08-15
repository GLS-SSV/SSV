/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "SSMEController.h"
#include "SSME.h"
#include "VehicleInterfaceElectronics.h"
#include "PowerSupplyElectronics.h"
#include "InputElectronics.h"
#include "OutputElectronics.h"
#include "DigitalComputerUnit.h"
#include "ComputerInterfaceElectronics.h"
#include "EIU.h"
#include "MPSdefs.h"


namespace mps
{
	SSMEController::SSMEController( SSME* eng )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEController::SSMEController in" );
#endif// _MPSDEBUG

		this->eng = eng;

#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEController::SSMEController out" );
#endif// _MPSDEBUG
		return;
	}

	SSMEController::~SSMEController( void )
	{
		return;
	}

	void SSMEController::__OnSaveState( FILEHANDLE scn ) const
	{
		VIE->OnSaveState( scn );// write VIE

		PSE[chA]->OnSaveState( scn );// write PSE chA
		PSE[chB]->OnSaveState( scn );// write PSE chB

		IE[chA]->OnSaveState( scn );// write IE chA
		IE[chB]->OnSaveState( scn );// write IE chB

		OE[chA]->OnSaveState( scn );// write OE chA
		OE[chB]->OnSaveState( scn );// write OE chB

		DCU[chA]->OnSaveState( scn );// write DCU chA
		DCU[chB]->OnSaveState( scn );// write DCU chB

		CIE[chA]->OnSaveState( scn );// write CIE chA
		CIE[chB]->OnSaveState( scn );// write CIE chB
		return;
	}

	bool SSMEController::__OnParseLine( const char* line )
	{
		if (VIE->OnParseLine( line )) return true;// check if VIE wants line

		if (PSE[chA]->OnParseLine( line )) return true;// check if PSE chA wants line
		if (PSE[chB]->OnParseLine( line )) return true;// check if PSE chB wants line

		if (IE[chA]->OnParseLine( line )) return true;// check if IE chA wants line
		if (IE[chB]->OnParseLine( line )) return true;// check if IE chB wants line

		if (OE[chA]->OnParseLine( line )) return true;// check if OE chA wants line
		if (OE[chB]->OnParseLine( line )) return true;// check if OE chB wants line

		if (DCU[chA]->OnParseLine( line )) return true;// check if DCU chA wants line
		if (DCU[chB]->OnParseLine( line )) return true;// check if DCU chB wants line

		if (CIE[chA]->OnParseLine( line )) return true;// check if CIE chA wants line
		if (CIE[chB]->OnParseLine( line )) return true;// check if CIE chB wants line
		return false;
	}

	void SSMEController::Realize( DiscreteBundle* power, DiscreteBundle* OEout, DiscreteBundle* OEoutCCV, DiscreteBundle* OEoutMFV, DiscreteBundle* OEoutMOV, DiscreteBundle* OEoutFPOV, DiscreteBundle* OEoutOPOV, DiscreteBundle* IEchA_Press, DiscreteBundle* IEchB_Press, DiscreteBundle* IEchA_Temp, DiscreteBundle* IEchB_Temp, DiscreteBundle* IEchA_Flow, DiscreteBundle* IEchB_Flow, DiscreteBundle* IEchA_Speed, DiscreteBundle* IEchB_Speed )
	{
		PSE[chA]->ConnectPower( power );
		PSE[chB]->ConnectPower( power );

		PSE[chA]->Realize();
		PSE[chB]->Realize();

		DCU[chA]->Realize();
		DCU[chB]->Realize();

		CIE[chA]->Realize();
		CIE[chB]->Realize();

		OE[chA]->Realize( OEout, OEoutCCV, OEoutMFV, OEoutMOV, OEoutFPOV, OEoutOPOV );
		OE[chB]->Realize( OEout, OEoutCCV, OEoutMFV, OEoutMOV, OEoutFPOV, OEoutOPOV );

		IE[chA]->Realize( IEchA_Press, IEchA_Temp, IEchA_Flow, IEchA_Speed );
		IE[chB]->Realize( IEchB_Press, IEchB_Temp, IEchB_Flow, IEchB_Speed );

		VIE->Realize();
		return;
	}

	void SSMEController::GetEIURef( EIU* pEIU )
	{
		this->pEIU = pEIU;
		return;
	}

	void SSMEController::VIE_CommandDataConverter_write( int ch, unsigned short cmd )
	{
		VIE->CommandDataConverter_write( ch, cmd );
		return;
	}

	void SSMEController::EIU_CIA( int num, unsigned short* data )
	{
		pEIU->CIA( num, data );
		return;
	}
}