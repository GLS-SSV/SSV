/******* SSV File Modification Notice *******
Date         Developer
2020/04/15   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
// DiscretePort.cpp: Implementierung der Klasse DiscretePort.
//
//////////////////////////////////////////////////////////////////////

#include "DiscretePort.h"
#include <cstdio>
#include <cassert>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace discsignals
{

DiscretePort::DiscretePort()
{
	pBundle = NULL;
	usLine = 0;
}
DiscretePort::DiscretePort(DiscreteBundle* pBundle, unsigned short iLine)
{
	Connect(pBundle, iLine);
}

DiscretePort::~DiscretePort()
{

}

bool DiscretePort::Connect(DiscreteBundle *pBundle, unsigned short iLine)
{
	assert( (pBundle != NULL) && "DiscretePort::Connect.pBundle" );
	assert( (iLine <= 15) && "DiscretePort::Connect.iLine" );
	this->pBundle = pBundle;
	this->usLine = iLine;
	return true;
}

bool DiscretePort::Disconnect()
{
	pBundle = NULL;
	usLine = 0;
	return true;
}

	DiscMultiplex::DiscMultiplex() {
	}

	DiscMultiplex::~DiscMultiplex() {
	}

	void DiscMultiplex::Propagate(double simt, double simdt, double mjd) {
	}

}
