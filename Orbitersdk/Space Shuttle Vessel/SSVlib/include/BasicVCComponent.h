/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic VC component definitions


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/03/20   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic VC component definitions



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file Doc\Space Shuttle Ultra\GPL.txt for more details.

  **************************************************************************/
#ifndef _BASICVCCOMPONENT_H_
#define _BASICVCCOMPONENT_H_


#include "BasicPanel.h"
#include <OrbiterAPI.h>
#include "ISubsystem.h"
#include <set>
#include <string>
#include <cassert>

namespace vc {

	using namespace std;

typedef struct {
	float x, y;
} VCMOUSEEVENTPOINT;

template <class TVessel>
class BasicPanel;

template <class TVessel>
class BasicVCComponent: public ISubsystem
{
	TVessel* sts;
	BasicPanel<TVessel>* pParent;
	string ident;
	VECTOR3 reference;
	VECTOR3 dir;
	double fInitialAnimState;
	VCMOUSEEVENTPOINT p_a, p_b, p_c, p_d;
	UINT mouseregionID;

	mutable float cache_lastx;
	mutable float cache_lasty;
	mutable float cache_mx;
	mutable float cache_my;

	set<UINT> availableForRendering;
protected:
	bool bHasReference;
	bool bHasDirection;
	bool bHasAnimations;


	double InitialAnimState() const {return fInitialAnimState;};
	bool SetAnimation(UINT anim, double fState);
	TVessel* V() const;
	bool VerifyAnimations();
	bool TriggerRedraw();
	bool WriteScenarioString(FILEHANDLE scn, const string& key, const string& value) const;
	bool WriteScenarioInt(FILEHANDLE scn, const string& key, const int iValue) const;
	bool WriteScenarioVector(FILEHANDLE scn, const string& key, const VECTOR3& vector) const;


public:
	explicit BasicVCComponent(TVessel* _v);
	BasicVCComponent(TVessel* _v, const string& _ident);
	virtual ~BasicVCComponent();

	/**
	 * Add an area ID to the redraw event list
	 */
	void AddAIDToRedrawEventList(UINT aid);


	//bool SetMouseRegion(VCMOUSEEVENTPOINT _a, VCMOUSEEVENTPOINT _b, VCMOUSEEVENTPOINT _c, VCMOUSEEVENTPOINT _d);

	/**
	 * Set the mouse region of the switch inside the area.
	 * Only allows rectangular regions currently.
	 * @param aid  Mouse area ID.
	 * @param xmin The x coordinate of the left side
	 * @param xmax The x coordinate of the right side
	 * @param ymin The y coordinate of the top side
	 * @param ymax The y coordinate of the bottom side.
	 */
	bool SetMouseRegion( UINT aid, float xmin, float ymin, float xmax, float ymax);


	void SetParentPanel(BasicPanel<TVessel>* pPanel);

	virtual void SetInitialAnimState(double fState = 0.0);
	virtual void DefineVCAnimations(UINT vc_idx);
	virtual bool OnMouseEvent(int _event, float x, float y);
	virtual const VECTOR3& GetDirection() const;
	virtual const VECTOR3& GetReference() const;
	virtual double GetState() const;
	virtual bool GetStateString(unsigned long ulBufferSize, char* pszBuffer);

	/**
	 * @return true if the object uses multiple lines for saving it's
	 * state.
	 */
	virtual bool IsMultiLineSaveState() const;


	bool IsOwnRegion(UINT aid) const;
	UINT GetMouseRegionID( void ) const;
	bool IsPointOver(float x, float y) const;
	bool ProjectMouse(float x, float y, float &mx, float &my) const;

	/**
	 * Set reference position
	 */

	void SetReference(const VECTOR3& _ref);
	/**
	 * Set reference position and direction
	 */
	void SetReference(const VECTOR3& _ref, const VECTOR3& dir);
	void SetDirection(const VECTOR3& _ref);




	virtual void Realize();
	virtual bool RegisterComponent(SubsystemComponent* pComponent);
	virtual void RegisterVC();
	virtual bool DelComponent(SubsystemComponent* pComponent);
	virtual unsigned long CountComponents() const;
	virtual void OnPreStep(double simt, double simdt, double mjd);
	virtual void OnPostStep(double simt, double simdt, double mjd);
	virtual void OnPropagate(double simt, double simdt, double mjd);
	virtual void OnPlaybackEvent(double simt, double fEventT, const char* event_t, const char* event);
	virtual bool OnVCRedrawEvent(int id, int _event, SURFHANDLE surf);
	virtual bool OnParseLine(const char* line);
	virtual bool OnParseLine(const char* keyword, const char* line);
	virtual bool OnReadState (FILEHANDLE scn);
	virtual void OnSaveState(FILEHANDLE scn) const;

	virtual void OnDumpToLog() const;
	virtual const string& GetQualifiedIdentifier() const;

	/**
	 * Get identification of this component
	 * @return The identification string, used for locating this component inside a panel
	 */
	virtual const string& GetIdentifier() const;
	virtual bool OnFail(const string& strFailureCode);

	virtual void VisualCreated();
};

template <class TVessel>
BasicVCComponent<TVessel>::BasicVCComponent(TVessel* _sts)
: sts(_sts), pParent(NULL), bHasReference(false), bHasDirection(false),
	bHasAnimations(false), fInitialAnimState(0.0)
{
}

template <class TVessel>
BasicVCComponent<TVessel>::BasicVCComponent(TVessel* _sts, const string& _ident)
: sts(_sts), ident(_ident), pParent(NULL), bHasReference(false),
	bHasDirection(false), bHasAnimations(false), fInitialAnimState(0.0)
{

}

template <class TVessel>
BasicVCComponent<TVessel>::~BasicVCComponent()
{

}

template <class TVessel>
void BasicVCComponent<TVessel>::AddAIDToRedrawEventList(UINT aid)
{
	availableForRendering.insert(aid);
}

template <class TVessel>
bool BasicVCComponent<TVessel>::GetStateString(unsigned long ulBufferSize, char* pszBuffer) {
	return false;
}

template <class TVessel>
void BasicVCComponent<TVessel>::Realize()
{
}

template <class TVessel>
TVessel* BasicVCComponent<TVessel>::V() const
{
	return sts;
}

template <class TVessel>
void BasicVCComponent<TVessel>::SetParentPanel(BasicPanel<TVessel>* pPanel) {
	pParent = pPanel;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::SetMouseRegion( UINT aid, float xmin, float ymin, float xmax, float ymax)
{
	mouseregionID = aid;
	p_a.x = xmin;
	p_a.y = ymin;
	p_d.x = xmax;
	p_d.y = ymax;
	return true;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::IsMultiLineSaveState() const {
	return false;
};

template <class TVessel>
bool BasicVCComponent<TVessel>::IsOwnRegion(UINT aid) const
{
	if(availableForRendering.find(aid) != availableForRendering.end())
		return true;
	else
		return false;
}

template <class TVessel>
UINT BasicVCComponent<TVessel>::GetMouseRegionID( void ) const
{
	return mouseregionID;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::IsPointOver(float x, float y) const
{
	if(p_a.x <= x && p_d.x >= x &&
		p_a.y <= y && p_d.y >= y) {
		return true;
	}
	else
		return false;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::ProjectMouse(float x, float y, float &mx, float &my) const
{
	if(IsPointOver(x, y))
	{
		mx = (x - p_a.x) /(p_d.x - p_a.x);
		my = (y - p_a.y) /(p_d.y - p_a.y);
		return true;
	}
	return false;
}

template <class TVessel>
const VECTOR3& BasicVCComponent<TVessel>::GetReference() const
{
	return reference;
}

template <class TVessel>
const VECTOR3& BasicVCComponent<TVessel>::GetDirection() const
{
	return dir;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::RegisterComponent(SubsystemComponent* pComponent)
{
	return false;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::DelComponent(SubsystemComponent* pComponent)
{
	return false;
}



template <class TVessel>
double BasicVCComponent<TVessel>::GetState() const
{
	return 0.0;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::OnMouseEvent(int event, float x, float y)
{
	return false;
}

template <class TVessel>
void BasicVCComponent<TVessel>::OnPreStep(double simt, double simdt, double mjd)
{

}

template <class TVessel>
void BasicVCComponent<TVessel>::OnPostStep(double simt, double simdt, double mjd)
{

}

template <class TVessel>
void BasicVCComponent<TVessel>::OnPropagate(double simt, double simdt, double mjd)
{
	//Do nothing - switches propagate by user events.
}

template <class TVessel>
void BasicVCComponent<TVessel>::DefineVCAnimations(UINT vc_idx)
{
#if _DEBUG
	oapiWriteLogV("BasicVCComponent[%s]:\tDefine VC Animations", GetQualifiedIdentifier().c_str() );
#endif// _DEBUG
}

template <class TVessel>
const string& BasicVCComponent<TVessel>::GetIdentifier() const
{
	return ident;
}

template <class TVessel>
const string& BasicVCComponent<TVessel>::GetQualifiedIdentifier() const
{
	static string result;
	if(pParent != NULL)
	{
		result = pParent->GetQualifiedIdentifier() + "::" + ident;
		return result;
	}
	else
	{
		return ident;
	}
}

template <class TVessel>
bool BasicVCComponent<TVessel>::OnFail(const string& strFailureCode)
{
	return false;
}

template <class TVessel>
void BasicVCComponent<TVessel>::OnDumpToLog() const
{
}

template <class TVessel>
bool BasicVCComponent<TVessel>::OnParseLine(const char* line)
{
	return true;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::OnParseLine(const char* keyword, const char* line) {
	return true;
}

template <class TVessel>
void BasicVCComponent<TVessel>::OnPlaybackEvent(double simt, double fEventT, const char* event_t, const char* event)
{
}

template <class TVessel>
bool BasicVCComponent<TVessel>::OnReadState(FILEHANDLE scn) {
	char* line;
	char pszKey[256];
	while(oapiReadScenario_nextline(scn, line)) {
		if(!_strnicmp(line, "@ENDOBJECT", 10)) {
			return true;
		} else if (!_strnicmp(line, "@ENDPANEL", 9)) {
			return false;
		} else {
			unsigned long i = 0;
			while(*line != ' ' && *line != '\0') {
				pszKey[i++] = *line;
				line++;
			}
			pszKey[++i] = '\0';
			if(*line != '\0') {
				OnParseLine(pszKey, line);
			} else {
				OnParseLine(pszKey, NULL);
			}
		}
	}
	return false;
}

template <class TVessel>
void BasicVCComponent<TVessel>::OnSaveState(FILEHANDLE scn) const
{

}


template <class TVessel>
bool BasicVCComponent<TVessel>::OnVCRedrawEvent(int id, int _event, SURFHANDLE surf)
{
	return false;
}

template <class TVessel>
unsigned long BasicVCComponent<TVessel>::CountComponents() const
{
	return 0;
}

template <class TVessel>
void BasicVCComponent<TVessel>::RegisterVC()
{
}

template <class TVessel>
bool BasicVCComponent<TVessel>::SetAnimation(UINT anim, double fState)
{
	if(bHasAnimations)
	{
		//sprintf_s(oapiDebugString(), 256, "SET ANIMATION");
		V()->SetAnimation(anim, fState);
		return true;
	}
	return false;
}

template <class TVessel>
void BasicVCComponent<TVessel>::SetInitialAnimState(double fState)
{
	assert( (fState >= 0.0) && (fState <= 1.0) && "BasicVCComponent::SetInitialAnimState.fState" );

	fInitialAnimState = fState;
}

template <class TVessel>
void BasicVCComponent<TVessel>::SetReference(const VECTOR3& ref)
{
	bHasReference = true;
	reference = ref;
}

template <class TVessel>
void BasicVCComponent<TVessel>::SetDirection(const VECTOR3& _dir)
{
	bHasDirection = true;
	dir = _dir;
}

template <class TVessel>
void BasicVCComponent<TVessel>::SetReference(const VECTOR3& ref, const VECTOR3& dir)
{
	bHasReference = true;
	bHasDirection = true;
	reference = ref;
	this->dir = dir;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::TriggerRedraw() {

	set<UINT>::iterator iter = availableForRendering.begin();
	while(iter != availableForRendering.end()) {
		oapiVCTriggerRedrawArea( -1, *iter);
		++iter;
	}
	return true;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::VerifyAnimations()
{
	bHasAnimations = true;
	return true;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::WriteScenarioInt(FILEHANDLE scn, const std::string &key, const int iValue) const
{

	return false;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::WriteScenarioString(FILEHANDLE scn, const std::string &key, const std::string &value) const
{
	return false;
}

template <class TVessel>
bool BasicVCComponent<TVessel>::WriteScenarioVector(FILEHANDLE scn, const std::string &key, const VECTOR3 &vector) const
{
	return false;
}

template <class TVessel>
void BasicVCComponent<TVessel>::VisualCreated()
{
}

}

#endif// _BASICVCCOMPONENT_H_
