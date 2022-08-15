/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/01/19   GLS
2021/01/20   GLS
2021/08/24   GLS
********************************************/
#include "SimpleShuttleBus.h"
#include "SimpleBTU.h"
#include <cassert>


namespace dps
{
	SimpleShuttleBus::SimpleShuttleBus()
	{
	}

	SimpleShuttleBus::~SimpleShuttleBus()
	{
	}

	void SimpleShuttleBus::ConnectTo( SimpleBTU* pBTU, unsigned short TermID )
	{
		assert( (pBTU != NULL) && "SimpleShuttleBus::ConnectTo.pBTU" );

		vBTU.push_back( pBTU );
		pBTU->ConnectTo( this );
		pBTU->SetTerminalID( TermID );
		return;
	}

	void SimpleShuttleBus::SendCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		for (auto &i : vBTU) i->busRead( cw, cdw );
		return;
	}
};
