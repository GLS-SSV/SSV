/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/20   GLS
2021/08/24   GLS
********************************************/
#include "SSMEControllerSW.h"
#include "DigitalComputerUnit.h"
#include "MPSdefs.h"


namespace mps
{
	SSMEControllerSW::SSMEControllerSW( DigitalComputerUnit* DCU )
	{
#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEControllerSW::SSMEControllerSW in" );
#endif// _MPSDEBUG

		this->DCU = DCU;

#ifdef _MPSDEBUG
		oapiWriteLog( " SSMEControllerSW::SSMEControllerSW out" );
#endif// _MPSDEBUG
		return;
	}

	SSMEControllerSW::~SSMEControllerSW( void )
	{
		return;
	}
}