/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/01/19   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
#include "SimpleBTU.h"
#include "SimpleShuttleBus.h"
#include <cassert>


namespace dps
{
	SimpleBTU::SimpleBTU()
	{
		usTerminalID = 0xFFFF;
		ReadEna = true;
		pBus = NULL;
	}

	SimpleBTU::~SimpleBTU()
	{
	}

	SimpleShuttleBus* SimpleBTU::GetBus( void ) const
	{
		assert( (pBus != NULL) && "SimpleBTU::GetBus.pBus" );
		return pBus;
	}

	unsigned short SimpleBTU::GetAddr( void ) const
	{
		assert( (usTerminalID != 0xFFFF) && "SimpleBTU::GetAddr.usTerminalID" );
		return usTerminalID;
	}

	void SimpleBTU::ConnectTo( SimpleShuttleBus* _pBus )
	{
		pBus = _pBus;
	}

	void SimpleBTU::SetTerminalID( unsigned short TermID )
	{
		usTerminalID = TermID;
	}
}
