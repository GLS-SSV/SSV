/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/04/15   GLS
2020/05/08   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/09/30   GLS
********************************************/
// DiscreteBundle.cpp: Implementierung der Klasse DiscreteBundle.
//
//////////////////////////////////////////////////////////////////////

#include <DiscreteBundle.h>
#include <cassert>
#include <OrbiterAPI.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace discsignals
{

DiscreteBundle::DiscreteBundle(const string& _ident, unsigned short nLines)
{
	assert( (nLines > 0) && (nLines <= 16) && "DiscreteBundle::DiscreteBundle.nLines" );

	snLines = nLines;
	ident = _ident;
	for(unsigned int i=0;i<nLines;i++) fLines[i] = 0.0; // by default, all lines are not set
}

DiscreteBundle::~DiscreteBundle()
{
	oapiWriteLogV( "(DiscreteBundle::~DiscreteBundle) destructor called for %s:%d", ident.c_str(), snLines );
}

const string& DiscreteBundle::GetIdentity() const
{
	return ident;
}

void DiscreteBundle::SetDiscrete(unsigned short iIndex, float fVoltage)
{
	assert( (iIndex < snLines) && "DiscreteBundle::SetDiscrete.iIndex" );
	fLines[iIndex] = fVoltage;
}

float DiscreteBundle::GetVoltage(unsigned short iIndex) const
{
	assert( (iIndex < snLines) && "DiscreteBundle::GetVoltage.iIndex" );
	return fLines[iIndex];
}

void DiscreteBundle::SetLogMode(short iMode)
{

}

unsigned short DiscreteBundle::CountLines() const throw()
{
	return snLines;
}

}
