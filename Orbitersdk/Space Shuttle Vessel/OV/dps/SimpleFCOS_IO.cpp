/******* SSV File Modification Notice *******
Date         Developer
2020/05/10   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/29   GLS
2022/05/13   GLS
2022/05/19   GLS
2022/05/29   GLS
2022/06/04   GLS
2022/06/06   GLS
2022/06/10   GLS
2022/06/16   GLS
2022/06/23   GLS
2022/07/02   GLS
2022/08/05   GLS
********************************************/
#include "SimpleFCOS_IO.h"
#include "SimpleGPCSystem.h"


namespace dps
{
	SimpleFCOS_IO::SimpleFCOS_IO( SimpleGPCSystem* _gpc )
	{
		pGPC = _gpc;
	}

	SimpleFCOS_IO::~SimpleFCOS_IO()
	{
	}

	void SimpleFCOS_IO::InputMDMDiscretes( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr )
	{
		SIMPLEBUS_COMMAND_WORD cw;

		pGPC->WriteBufferAddress = memoryaddr;
		pGPC->WriteBufferLength = 1;
		pGPC->SubSystemAddress = addr;
		cw.MIAaddr = pGPC->SubSystemAddress;
		cw.payload = (mode << 9) | (moduleaddr << 5) | modulech;
		cw.numwords = 0;
		pGPC->busCommand( cw, NULL );
		return;
	}

	void SimpleFCOS_IO::OutputMDMDiscretes( unsigned short addr, unsigned short mode, unsigned short moduleaddr, unsigned short modulech, unsigned short memoryaddr )
	{
		SIMPLEBUS_COMMAND_WORD cw;
		SIMPLEBUS_COMMANDDATA_WORD cdw[32];

		pGPC->SubSystemAddress = addr;
		pGPC->WriteBufferLength = 0;

		cw.MIAaddr = pGPC->SubSystemAddress;
		cw.payload = (mode << 9) | (moduleaddr << 5) | modulech;
		cw.numwords = 0;
		cdw[0].MIAaddr = pGPC->SubSystemAddress;
		cdw[0].payload = pGPC->SimpleCOMPOOL[memoryaddr];
		cdw[0].SEV = 0b101;
		pGPC->busCommand( cw, cdw );

		// reset memory location
		pGPC->SimpleCOMPOOL[memoryaddr] = 0;
		return;
	}

	void SimpleFCOS_IO::busRead( SIMPLEBUS_COMMANDDATA_WORD* cdw )
	{
		// save data from subsystem

		for (unsigned short i = 0; i < pGPC->WriteBufferLength; i++)
		{
			if (cdw[i].MIAaddr != pGPC->SubSystemAddress) return;// check if addr matches subsystem we're waiting data from
			pGPC->SimpleCOMPOOL[pGPC->WriteBufferAddress + i] = cdw[i].payload;
		}
		return;
	}
};
