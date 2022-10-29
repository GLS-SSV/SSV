/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/03/29   GLS
2020/05/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
// BasicSwitch.cpp: Implementierung der Klasse BasicSwitch.
//
//////////////////////////////////////////////////////////////////////

#include "BasicSwitch.h"
#include "../Atlantis.h"
#include "../../SSVSound.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace vc {

BasicSwitch::BasicSwitch(Atlantis* _sts, unsigned short usNumPositions, const string& _ident, int switchSoundID)
: AtlantisVCComponent(_sts, _ident), bOrientation(false), bSpringLoaded(false), vbSpringLoaded(usNumPositions, false), usCurrentPosition(0),
  switchSound(switchSoundID)
{
	this->usNumPositions = usNumPositions;
	labels.resize(usNumPositions);
	for(int i = 0; i<usNumPositions; i++) {
		labels[i] = "";
	}

	grpIndex = (UINT)(-1);
}

BasicSwitch::~BasicSwitch()
{

}
void BasicSwitch::DefineVCAnimations(UINT vc_idx)
{

}

void BasicSwitch::DefineGroup( UINT _grpIndex )
{
	grpIndex = _grpIndex;
}

bool BasicSwitch::IsFullySpringLoaded( void )
{
	bool one = false;
	for (unsigned short i = 0; i < usNumPositions; i++)
	{
		if (!vbSpringLoaded.at( i ))
		{
			if (one) return false;
			else one = true;
		}
	}
	return true;
}

bool BasicSwitch::GetStateString(unsigned long ulBufferSize, char* pszBuffer) {

	if (IsFullySpringLoaded()) return false;// no need to save state if the switch only has one non-spring loaded position

	if(labels.at(usCurrentPosition).compare("")) {
		sprintf_s(pszBuffer, ulBufferSize, "%s", labels.at(usCurrentPosition).c_str());
	} else {
		sprintf_s(pszBuffer, ulBufferSize, "[%d]", usCurrentPosition);
	}
	return true;
}

bool BasicSwitch::OnMouseEvent(int _event, float x, float y)
{
	/*
	sprintf_s(oapiDebugString(), 256, "BASICSWITCH %s [%d/%d] (%d, %f, %f)",
		GetQualifiedIdentifier().c_str(),
		usCurrentPosition,
		usNumPositions,
		_event, x, y);

	*/

	// only process mouse down events (and mouse up events if this is a spring loaded switch)
	if(!(_event & PANEL_MOUSE_LBDOWN) && (!bSpringLoaded || !(_event & PANEL_MOUSE_LBUP)))
		return false;

	if(bOrientation) {
		if(x > 0.6) {
			if(_event & PANEL_MOUSE_LBDOWN) OnPositionDown();
			else if(vbSpringLoaded.at(usCurrentPosition)) {
				OnPositionUp();
			}
			return true;
		}
		else if(x < 0.4) {
			if(_event & PANEL_MOUSE_LBDOWN) OnPositionUp();
			else if(vbSpringLoaded.at(usCurrentPosition)) {
				OnPositionDown();
			}
			return true;
		}
	}
	else {
		if(y > 0.6) {
			if(_event & PANEL_MOUSE_LBDOWN) OnPositionDown();
			else if(vbSpringLoaded.at(usCurrentPosition)) {
				OnPositionUp();
			}
			return true;
		}
		else if( y < 0.4) {
			if(_event & PANEL_MOUSE_LBDOWN) OnPositionUp();
			else if(vbSpringLoaded.at(usCurrentPosition)) {
				OnPositionDown();
			}
			return true;
		}
	}
	return false;
}

bool BasicSwitch::OnParseLine(const char* line)
{
#if _DEBUG
	oapiWriteLogV( "\t\tSet switch \"%s\" to state \"%s\".",
		GetQualifiedIdentifier().c_str(), line );
#endif// _DEBUG

	if(line[0] == '[') {
		usCurrentPosition = atoi(line+1);
		OnPositionChange(usCurrentPosition);
		return true;
	} else {
		for(unsigned short i = 0; i<usNumPositions; i++) {
			if(labels.at(i) == line)
			{
				usCurrentPosition = i;
				OnPositionChange(usCurrentPosition);
				return true;
			}
		}
	}
	return false;
}

void BasicSwitch::OnPositionChange(unsigned short usNewPosition)
{
	if(switchSound > 0) PlayVesselWave(STS()->GetSoundID(), switchSound);
}

void BasicSwitch::OnPositionUp()
{
	if(usCurrentPosition < usNumPositions - 1)
	{
		usCurrentPosition++;
		OnPositionChange(usCurrentPosition);
	}
}

void BasicSwitch::OnPositionDown()
{
	if(usCurrentPosition > 0)
	{
		usCurrentPosition--;
		OnPositionChange(usCurrentPosition);
	}
}



void BasicSwitch::OnSaveState(FILEHANDLE scn) const
{

}

void BasicSwitch::SetLabel(unsigned short iPosition, const string& _label)
{
	assert( (iPosition < usNumPositions) && "BasicSwitch::SetLabel.iPosition" );

	labels.at(iPosition) = _label;
}

void BasicSwitch::SetInitialPosition(unsigned short usPos)
{
	assert( (usPos < usNumPositions) && "BasicSwitch::SetInitialPosition.usPos" );

	usCurrentPosition=usPos;
}

void BasicSwitch::SetOrientation(bool bHorizontal)
{
	bOrientation = bHorizontal;
}

void BasicSwitch::SetSpringLoaded(bool IsSpringLoaded, unsigned short usPos)
{
	assert( (usPos < usNumPositions) && "BasicSwitch::SetSpringLoaded.usPos" );

	bSpringLoaded = bSpringLoaded || IsSpringLoaded;
	vbSpringLoaded.at(usPos) = IsSpringLoaded;
}

void BasicSwitch::SetSpringLoaded(bool IsSpringLoaded)
{
	unsigned short usMidPosition = (usNumPositions - 1)/2;
	for(unsigned short i=0;i<usNumPositions;i++) {
		SetSpringLoaded(IsSpringLoaded && (i!=usMidPosition), i);
	}
}

}
