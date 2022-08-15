/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel Group definition


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
2020/08/24   GLS
2020/08/31   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/07/16   GLS
2022/08/05   GLS
2022/08/08   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel Group definition



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
#pragma once

#include "OrbiterAPI.h"
#include <vector>
#include "BasicPanel.h"


namespace vc {
	using namespace std;

	template <class TVessel>
	class PanelGroup {
		vector< BasicPanel<TVessel>* > panels;
	public:
		PanelGroup();
		virtual ~PanelGroup();

		virtual bool AddPanel(BasicPanel<TVessel>* pPanel);
		void RegisterVC();
		void DefineVCAnimations (UINT vcidx);
		void DefineVC();
		bool HasPanel(const string& panelname) const;
		bool ParsePanelBlock(const string& panelname, FILEHANDLE scn);
		void Realize();
		bool OnVCMouseEvent (int id, int _event, VECTOR3 &p);
		bool OnVCRedrawEvent (int id, int _event, SURFHANDLE surf);
		void OnPreStep (double simt, double simdt, double mjd);
		void OnPostStep (double simt, double simdt, double mjd);
		void OnPropagate(double simt, double simdt, double mjd);
		bool OnParseLine (char *line);
		void OnSaveState (FILEHANDLE scn);
		bool EnableCoordinateDisplayMode();
		bool DisableCoordinateDisplayMode();
		bool ToggleCoordinateDisplayMode();
		void HidePanels();
		void ShowPanels();
		void LogPanels(char *grp);
		void VisualCreated();
		void AddMeshes( const VECTOR3& ofs );
	};

	template <class TVessel>
	PanelGroup<TVessel>::PanelGroup()
	{
	}

	template <class TVessel>
	PanelGroup<TVessel>::~PanelGroup()
	{
		while(!panels.empty()) {
			BasicPanel<TVessel>* panel = panels.back();
			if (panel)
			{
				oapiWriteLogV( "Deleting panel \"%s\" ...", panel->GetQualifiedIdentifier().c_str() );
				delete panel;
			}
			panels.pop_back();
		}
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::AddPanel(BasicPanel<TVessel>* pPanel)
	{
		panels.push_back(pPanel);
		return true;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::DefineVCAnimations(UINT vcidx)
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->DefineVCAnimations(vcidx);
	}

	template <class TVessel>
	void PanelGroup<TVessel>::DefineVC()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->DefineVC();
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::HasPanel(const string& panelname) const {
		for(unsigned int i = 0; i<panels.size(); i++) {
			if(panels.at(i)->GetIdentifier() == panelname) {
				return true;
			}
		}
		return false;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::ParsePanelBlock(const string& panelname, FILEHANDLE scn) {

		for(unsigned int i = 0; i<panels.size(); i++) {
			if(panels.at(i)->GetIdentifier() == panelname) {
				return panels.at(i)->OnReadState(scn);
			}
		}
#if _DEBUG
		oapiWriteLog("\tNo Panel found here!");
#endif// _DEBUG
		return false;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::RegisterVC()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->RegisterVC();
	}

	template <class TVessel>
	void PanelGroup<TVessel>::Realize()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->Realize();
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::OnParseLine(char *line)
	{
		for(unsigned int i = 0; i<panels.size(); i++)
		{
			//Test syntax of line
			panels.at(i)->OnParseLine(line);
		}
		return false;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnPostStep(double simt, double simdt, double mjd)
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->OnPostStep(simt, simdt, mjd);
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnPreStep(double simt, double simdt, double mjd)
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->OnPreStep(simt, simdt, mjd);
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnPropagate(double simt, double simdt, double mjd)
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->OnPropagate(simt, simdt, mjd);
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnSaveState(FILEHANDLE scn)
	{
		if(panels.empty()) {
			//oapiWriteLog("\tNo panels to be saved here...");
			return;
		}
		for(unsigned int i = 0; i<panels.size(); i++) {
			oapiWriteLogV( "Save panel \"%s\" ...", panels.at(i)->GetQualifiedIdentifier().c_str() );
			panels.at(i)->OnSaveState(scn);
		}
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::OnVCMouseEvent(int id, int _event, VECTOR3 &p)
	{
		bool r = false;
		for (unsigned int i = 0; i < panels.size(); i++)
		{
			r |= panels.at(i)->OnVCMouseEvent(id, _event, p);
		}
		return r;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::OnVCRedrawEvent(int id, int _event, SURFHANDLE surf)
	{
		bool r = false;
		for(unsigned int i = 0; i<panels.size(); i++)
			r |= panels.at(i)->OnVCRedrawEvent(id, _event, surf);
		return r;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::EnableCoordinateDisplayMode()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->EnableCoordinateDisplayMode();
		return true;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::DisableCoordinateDisplayMode()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->DisableCoordinateDisplayMode();
		return true;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::ToggleCoordinateDisplayMode()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->ToggleCoordinateDisplayMode();
		return true;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::HidePanels()
	{
		for(unsigned int i=0;i<panels.size();i++)
			panels.at(i)->SetMeshVisibility(false);
	}

	template <class TVessel>
	void PanelGroup<TVessel>::ShowPanels()
	{
		for(unsigned int i=0;i<panels.size();i++)
			panels.at(i)->SetMeshVisibility(true);
	}

	template <class TVessel>
	void PanelGroup<TVessel>::LogPanels(char * panelgroup) {
		char *state;

		oapiWriteLogV( "Panel group dump for group \"%s\": ", panelgroup );

		for (unsigned int i = 0; i < panels.size(); i++)
		{
			switch (panels.at(i)->GetPanelState())
			{
			case PS_CREATED:
				state = "CREATED";
				break;
			case PS_DEFINED:
				state = "DEFINED";
				break;
			case PS_REGISTERED:
				state = "REGISTERED";
				break;
			case PS_REALIZED:
				state = "REALIZED";
				break;
			case PS_UNKNOWN:
			default:
				state = "UNKNOWN";
			}
			oapiWriteLogV( "   %s  : %s ", panels.at(i)->GetQualifiedIdentifier().c_str(), state );
		}
	}

	template <class TVessel>
	void PanelGroup<TVessel>::VisualCreated()
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->VisualCreated();
	}

	template <class TVessel>
	void PanelGroup<TVessel>::AddMeshes( const VECTOR3& ofs )
	{
		for(unsigned int i = 0; i<panels.size(); i++)
			panels.at(i)->AddMeshes( ofs );
	}
};