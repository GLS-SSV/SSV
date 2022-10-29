/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic Panel definition


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
2020/03/29   GLS
2020/04/01   GLS
2020/04/07   GLS
2020/05/24   GLS
2020/08/24   GLS
2021/06/03   GLS
2021/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/01/15   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic panel definitions



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
#ifndef __BASIC_PANEL_H__
#define __BASIC_PANEL_H__

#include <OrbiterAPI.h>
#include <set>
#include <string>
#include <vector>
#include "BasicVCComponent.h"


namespace vc
{

using namespace std;

enum PanelState {
	PS_UNKNOWN = 0,
	PS_CREATED,
	PS_DEFINED,
	PS_REGISTERED,
	PS_REALIZED
};

template <class TVessel>
class BasicVCComponent;


template <class TVessel>
class BasicPanel
{
	TVessel* pv;
	string name;

	set<UINT> availableForMouse;
	vector< BasicVCComponent<TVessel>* > components;

	bool bCoordinateDisplayMode;

	PanelState pstate;
protected:
	// mesh handles for panels with own mesh
	MESHHANDLE hMesh;
	UINT mesh_idx;
	VECTOR3 panelofs;

	bool bHasOwnVCMesh;

	void AddAIDToMouseEventList(UINT aid);

	void DeleteAllComponents();
	bool DistributeMouseEvent( UINT aid, int _event, const VECTOR3& p);
	bool FindComponent( UINT aid, const VECTOR3& p, BasicVCComponent<TVessel>** foundElement) const;

	virtual void DefineMesh( const char* meshname ){};
	virtual void DefineMesh( const char* meshname, const VECTOR3& panelofs ){};

public:
	BasicPanel(TVessel* v, const string& _name);
	virtual ~BasicPanel();
	TVessel* V() const;
	virtual void DefineVCAnimations (UINT vcidx);
	virtual void RegisterVC();
	virtual void DefineVC() = 0;
	virtual UINT GetVCMeshIndex() const;
	virtual MESHHANDLE GetVCMeshHandle( void ) const;
	virtual void ReplaceComponent(unsigned long ulIndex, BasicVCComponent<TVessel>* pReplacement);

	virtual BasicVCComponent<TVessel>* Add(BasicVCComponent<TVessel>* pNew);

	virtual void AddMeshes( const VECTOR3& ofs ){};
	virtual void SetMeshVisibility( bool visible ){};
	virtual BasicVCComponent<TVessel>* GetSwitch(const string& switchID) const;
	virtual void Realize();
	virtual bool OnVCMouseEvent (int id, int _event, VECTOR3 &p);
	virtual bool OnVCRedrawEvent (int id, int _event, SURFHANDLE surf);
	virtual void OnPreStep (double simt, double simdt, double mjd);
	virtual void OnPostStep (double simt, double simdt, double mjd);
	virtual void OnPropagate(double simt, double simdt, double mjd);
	virtual bool OnParseLine (char *line);
	virtual bool OnReadState (FILEHANDLE scn);
	virtual void OnSaveState (FILEHANDLE scn);

	virtual const string& GetIdentifier() const;
	virtual const string& GetQualifiedIdentifier() const;

	virtual bool HasSwitch(const string& switchID);

	bool HasOwnVCMesh() const {return bHasOwnVCMesh;};


	bool EnableCoordinateDisplayMode() {bCoordinateDisplayMode = true; return true;};
	bool DisableCoordinateDisplayMode() {bCoordinateDisplayMode = false; return true;};
	bool ToggleCoordinateDisplayMode() {bCoordinateDisplayMode = !bCoordinateDisplayMode; return true;};

	virtual void VisualCreated();
	inline void SetPanelState(PanelState s)
	{
		pstate = s;
	}

	inline PanelState GetPanelState() const
	{
		return pstate;
	}
};

template <class TVessel>
BasicPanel<TVessel>::BasicPanel(TVessel* _v, const string& _name)
	: pv(_v), name(_name), bCoordinateDisplayMode(false), pstate(PS_CREATED), hMesh(NULL), mesh_idx(-1), bHasOwnVCMesh(false)
{
	panelofs = _V( 0.0, 0.0, 0.0 );
}

template <class TVessel>
BasicPanel<TVessel>::~BasicPanel()
{
	DeleteAllComponents();
}

template <class TVessel>
BasicVCComponent<TVessel>* BasicPanel<TVessel>::Add(BasicVCComponent<TVessel>* pNew)
{
	pNew->SetParentPanel(this);
	components.push_back(pNew);
	return pNew;
}

template <class TVessel>
void BasicPanel<TVessel>::DeleteAllComponents()
{
	unsigned long i = 0;
	for(; i<components.size(); i++)
	{
		delete components.at(i);
	}
}

template <class TVessel>
TVessel* BasicPanel<TVessel>::V() const
{
	return pv;
}

template <class TVessel>
void BasicPanel<TVessel>::DefineVCAnimations(UINT vcidx)
{
	if (pstate != PS_CREATED)
	{
		oapiWriteLogV( "(SSVlib) [DEBUG] Panel state violation in %s, not created at DefineVCAnimations", this->GetQualifiedIdentifier().c_str() );
	}

#if _DEBUG
	oapiWriteLogV( "BasicPanel[%s]:\tDefine VC Animations. %d components",
		GetQualifiedIdentifier().c_str(), components.size() );
#endif// _DEBUG

	UINT idx = vcidx;
	if (HasOwnVCMesh()) idx = mesh_idx;// use own mesh, if it has one

	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->DefineVCAnimations( idx );
		++iter;
	}
	pstate = PS_DEFINED;
}

template <class TVessel>
bool BasicPanel<TVessel>::DistributeMouseEvent( UINT aid, int _event, const VECTOR3& p)
{
	unsigned long i;
	float mx = 0, my = 0;
	for(i = 0; i<components.size(); i++)
	{
		BasicVCComponent<TVessel>* currentElement = components.at(i);
		if (currentElement->GetMouseRegionID() == aid)
		{
			if(currentElement->IsPointOver((float)p.x, (float)p.y))
			{
				currentElement->ProjectMouse((float)p.x, (float)p.y, mx, my);
				if(currentElement->OnMouseEvent(_event, mx, my))
					return true;
			}
		}
	}
	return false;
}

template <class TVessel>
bool BasicPanel<TVessel>::FindComponent( UINT aid, const VECTOR3& p, BasicVCComponent<TVessel>** foundElement) const
{
	unsigned long i;
	for(i = 0; i<components.size(); i++)
	{
		BasicVCComponent<TVessel>* currentElement = components.at(i);
		if (currentElement->GetMouseRegionID() == aid)
		{
			if(currentElement->IsPointOver((float)p.x, (float)p.y))
			{
				*foundElement = currentElement;
				return true;
			}
		}
	}
	return false;
}

template <class TVessel>
BasicVCComponent<TVessel>* BasicPanel<TVessel>::GetSwitch(const string& switchID) const {
	unsigned long i;
	for(i = 0; i<components.size(); i++)
	{
		BasicVCComponent<TVessel>* currentElement = components.at(i);
		if(currentElement->GetIdentifier() == switchID)
		{
			return currentElement;
		}
	}
	return NULL;
}

template <class TVessel>
UINT BasicPanel<TVessel>::GetVCMeshIndex() const
{
	return mesh_idx;
}

template <class TVessel>
MESHHANDLE BasicPanel<TVessel>::GetVCMeshHandle( void ) const
{
	return hMesh;
}

template <class TVessel>
void BasicPanel<TVessel>::RegisterVC()
{
	if ((pstate != PS_REALIZED) && (pstate != PS_REGISTERED))
	{
		oapiWriteLogV( "(SSVlib) [DEBUG] Panel state violation in %s, not realized at RegisterVC()", this->GetQualifiedIdentifier().c_str() );
	}

	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->RegisterVC();
		++iter;
	}

	pstate = PS_REGISTERED;
}

template <class TVessel>
void BasicPanel<TVessel>::Realize()
{
	if (pstate != PS_DEFINED)
	{
		oapiWriteLogV( "(SSVlib) [DEBUG] Panel state violation in %s, not defined at Realize()", this->GetQualifiedIdentifier().c_str() );
	}
	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->Realize();
		++iter;
	}

	pstate = PS_REALIZED;
}

template <class TVessel>
bool BasicPanel<TVessel>::OnParseLine(char *line)
{
	return false;
}

template <class TVessel>
bool BasicPanel<TVessel>::OnReadState (FILEHANDLE scn) {
	char* line;

	char pszBuffer[256];
#if _DEBUG
	oapiWriteLogV( "\t\tParse panel block for panel \"%s\"...",
		GetQualifiedIdentifier().c_str() );
#endif// _DEBUG

	while(oapiReadScenario_nextline(scn, line)) {
		if(!_strnicmp(line, "@ENDPANEL", 9)) {
#if _DEBUG
			oapiWriteLog("\t\tDone.");
#endif// _DEBUG
			return true;
		} else if(!_strnicmp(line, "@OBJECT", 7)) {
#if _DEBUG
			oapiWriteLog("\t\tEnter Multiline switch block...");
#endif// _DEBUG
			//Multi line object block
			//Get identifier of object or switch
			line += 8;
			unsigned long i = 0;
			bool bStringFlag = false;
			while((*line != '\0' && *line != ' ') || bStringFlag) {
				if(*line == '\"') {
					bStringFlag = !bStringFlag;
				} else {
					pszBuffer[i] = *line;
					i++;
				}
				line++;
			}

			pszBuffer[i] = '\0';
			//Look up object
#if _DEBUG
			oapiWriteLogV( "\tLook up object \"%s\"...", pszBuffer );
#endif// _DEBUG
			//
			if(HasSwitch(pszBuffer)) {
				BasicVCComponent<TVessel>* pT = this->GetSwitch(pszBuffer);
				pT->OnReadState(scn);
			} else {
				//skip block
				while(oapiReadScenario_nextline(scn, line)) {
					if(!_strnicmp(line, "@ENDOBJECT", 10))
						break;
				}
			}
#if _DEBUG
			oapiWriteLog("\t\tLeave Multiline switch block...");
#endif// _DEBUG
		} else {
			//single line object block
			//oapiWriteLog("\t\tEnter single line switch block...");
			unsigned long i = 0;
			bool bStringFlag = false;
			while((*line != '\0' && *line != ' ') || bStringFlag) {
				if(*line == '\"') {
					bStringFlag = !bStringFlag;
				} else {
					pszBuffer[i] = *line;
					i++;
				}
				line++;
			}

			pszBuffer[i] = '\0';
			line++;

			//Look up object
#if _DEBUG
			oapiWriteLogV( "\tLook up switch \"%s\"...\t\t(%s)", pszBuffer, line );
#endif// _DEBUG

			if(HasSwitch(pszBuffer)) {
#if _DEBUG
				oapiWriteLog("\tFound switch.");
#endif// _DEBUG
				BasicVCComponent<TVessel>* pT = this->GetSwitch(pszBuffer);
				if(pT != NULL) {
					if(!pT->IsMultiLineSaveState()) {
#if _DEBUG
						oapiWriteLog("\tRead switch state.");
#endif// _DEBUG
						pT->OnParseLine(line);
					}
				}
			}
			else oapiWriteLogV( "(SSVlib) [ERROR] Switch \"%s\" not found", pszBuffer );

			//oapiWriteLog("\t\tLeave single line switch block...");
		}
	}
#if _DEBUG
	oapiWriteLog("\t\tParsing error.");
#endif// _DEBUG
	return false;
}

template <class TVessel>
void BasicPanel<TVessel>::OnSaveState(FILEHANDLE scn)
{
	char pszBuffer[256];
	char pszBuffer2[256];

	if(components.empty()) {
		return;
	}

	sprintf_s( pszBuffer, 255, "@PANEL %s", GetIdentifier().c_str() );
	oapiWriteLine( scn, pszBuffer );
	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end()) {
		if((*iter)->IsMultiLineSaveState()) {
			sprintf_s(pszBuffer, 255, "\"%s\"",
					(*iter)->GetIdentifier().c_str());
			oapiWriteScenario_string(scn, "@OBJECT",
				pszBuffer);
			(*iter)->OnSaveState(scn);
			oapiWriteLine(scn, "  @ENDOBJECT");
		} else {
			if((*iter)->GetStateString(255, pszBuffer)) {
				sprintf_s(pszBuffer2, 255, "\"%s\"",
					(*iter)->GetIdentifier().c_str());
				oapiWriteScenario_string(scn,
					pszBuffer2,
					pszBuffer);
			}
		}
		++iter;
	}

	oapiWriteLine( scn, "@ENDPANEL" );
}

template <class TVessel>
bool BasicPanel<TVessel>::OnVCMouseEvent(int id, int _event, VECTOR3 &p)
{
	if(availableForMouse.find(id) != availableForMouse.end()) {
		if(bCoordinateDisplayMode)
		{
			BasicVCComponent<TVessel>* foundElement;
			if(FindComponent( id, p, &foundElement))
			{
				sprintf_s(oapiDebugString(), 256, "PANEL %s (%d) MOUSEEVENT (%d, %f, %f, %f) FOR %s",
					name.c_str(), id, _event, p.x, p.y, p.z,
					foundElement->GetQualifiedIdentifier().c_str());
			}
			else
			{
				sprintf_s(oapiDebugString(), 256, "PANEL %s (%d) MOUSEEVENT (%d, %f, %f, %f)",
					name.c_str(), id, _event, p.x, p.y, p.z);
			}
			return DistributeMouseEvent( id, _event, p);
		} else {

			return DistributeMouseEvent( id, _event, p);
		}
	}
	else {
		return false;
	}
}

template <class TVessel>
bool BasicPanel<TVessel>::OnVCRedrawEvent(int id, int _event, SURFHANDLE surf)
{
	bool bRedraw=false;

	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		BasicVCComponent<TVessel>* comp = (*iter);
		if(comp->IsOwnRegion(id)) {
			if(comp->OnVCRedrawEvent(id, _event, surf)) bRedraw=true;
		}

		++iter;
	}
	return bRedraw;
}

template <class TVessel>
void BasicPanel<TVessel>::OnPreStep(double simt, double simdt, double mjd)
{
	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->OnPreStep(simt, simdt, mjd);
		++iter;
	}
}

template <class TVessel>
void BasicPanel<TVessel>::OnPostStep(double simt, double simdt, double mjd)
{
	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->OnPostStep(simt, simdt, mjd);
		++iter;
	}
}

template <class TVessel>
void BasicPanel<TVessel>::OnPropagate(double simt, double simdt, double mjd)
{
	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->OnPropagate(simt, simdt, mjd);
		++iter;
	}
}

template <class TVessel>
bool BasicPanel<TVessel>::HasSwitch(const string& id)
{
	unsigned long i;
	for(i = 0; i<components.size(); i++)
	{
		BasicVCComponent<TVessel>* currentElement = components.at(i);
		if(currentElement->GetIdentifier() == id)
		{
			return true;
		}
	}
	return false;
}

template <class TVessel>
const string& BasicPanel<TVessel>::GetIdentifier() const
{
	//static string null = "";
	return name;
}

template <class TVessel>
const string& BasicPanel<TVessel>::GetQualifiedIdentifier() const
{
	//static string null = "";
	return name;
}

template <class TVessel>
void BasicPanel<TVessel>::ReplaceComponent(unsigned long ulIndex, BasicVCComponent<TVessel>* pReplacement)
{
	if(ulIndex < components.size())
	{
		components.at(ulIndex) = pReplacement;
	}
}

template <class TVessel>
void BasicPanel<TVessel>::AddAIDToMouseEventList(UINT aid)
{
	availableForMouse.insert(aid);
	return;
}

template <class TVessel>
void BasicPanel<TVessel>::VisualCreated()
{
	typename vector< BasicVCComponent<TVessel>* >::iterator iter = components.begin();
	while(iter != components.end())
	{
		(*iter)->VisualCreated();
		++iter;
	}
}

}

#endif// __BASIC_PANEL_H__
