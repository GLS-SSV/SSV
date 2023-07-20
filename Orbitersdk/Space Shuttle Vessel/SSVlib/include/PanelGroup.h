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
2022/09/29   GLS
2023/02/19   GLS
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
#ifndef _PANELGROUP_H
#define _PANELGROUP_H


#include <OrbiterAPI.h>
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
		for (auto& x : panels)
		{
			oapiWriteLogV( "Deleting panel \"%s\" ...", x->GetQualifiedIdentifier().c_str() );
			delete x;
		}
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::AddPanel( BasicPanel<TVessel>* pPanel )
	{
		panels.push_back( pPanel );
		return true;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::DefineVCAnimations( UINT vcidx )
	{
		for (const auto& x : panels) x->DefineVCAnimations( vcidx );
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::DefineVC( void )
	{
		for (const auto& x : panels) x->DefineVC();
		return;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::HasPanel( const string& panelname ) const
	{
		for (const auto& x : panels)
		{
			if (x->GetIdentifier() == panelname)
			{
				return true;
			}
		}
		return false;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::ParsePanelBlock( const string& panelname, FILEHANDLE scn )
	{
		for (const auto& x : panels)
		{
			if (x->GetIdentifier() == panelname)
			{
				return x->OnReadState( scn );
			}
		}
#if _DEBUG
		oapiWriteLog("\tNo Panel found here!");
#endif// _DEBUG
		return false;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::RegisterVC( void )
	{
		for (const auto& x : panels) x->RegisterVC();
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::Realize( void )
	{
		for (const auto& x : panels) x->Realize();
		return;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::OnParseLine( char* line )
	{
		for (const auto& x : panels) x->OnParseLine( line );
		return false;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnPostStep( double simt, double simdt, double mjd )
	{
		for (const auto& x : panels) x->OnPostStep( simt, simdt, mjd );
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnPreStep( double simt, double simdt, double mjd )
	{
		for (const auto& x : panels) x->OnPreStep( simt, simdt, mjd );
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnPropagate( double simt, double simdt, double mjd )
	{
		for (const auto& x : panels) x->OnPropagate( simt, simdt, mjd );
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::OnSaveState( FILEHANDLE scn )
	{
		for (const auto& x : panels)
		{
			oapiWriteLogV( "Save panel \"%s\" ...", x->GetQualifiedIdentifier().c_str() );
			x->OnSaveState( scn );
		}
		return;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::OnVCMouseEvent( int id, int _event, VECTOR3& p )
	{
		bool r = false;
		for (const auto& x : panels) r |= x->OnVCMouseEvent( id, _event, p );
		return r;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::OnVCRedrawEvent( int id, int _event, SURFHANDLE surf )
	{
		bool r = false;
		for (const auto& x : panels) r |= x->OnVCRedrawEvent( id, _event, surf );
		return r;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::EnableCoordinateDisplayMode( void )
	{
		for (const auto& x : panels) x->EnableCoordinateDisplayMode();
		return true;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::DisableCoordinateDisplayMode( void )
	{
		for (const auto& x : panels) x->DisableCoordinateDisplayMode();
		return true;
	}

	template <class TVessel>
	bool PanelGroup<TVessel>::ToggleCoordinateDisplayMode( void )
	{
		for (const auto& x : panels) x->ToggleCoordinateDisplayMode();
		return true;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::HidePanels( void )
	{
		for (const auto& x : panels) x->SetMeshVisibility( false );
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::ShowPanels( void )
	{
		for (const auto& x : panels) x->SetMeshVisibility( true );
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::LogPanels( char* panelgroup )
	{
		char *state;

		oapiWriteLogV( "Panel group dump for group \"%s\": ", panelgroup );

		for (const auto& x : panels)
		{
			switch (x->GetPanelState())
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
			oapiWriteLogV( "   %s  : %s ", x->GetQualifiedIdentifier().c_str(), state );
		}
	}

	template <class TVessel>
	void PanelGroup<TVessel>::VisualCreated( void )
	{
		for (const auto& x : panels) x->VisualCreated();
		return;
	}

	template <class TVessel>
	void PanelGroup<TVessel>::AddMeshes( const VECTOR3& ofs )
	{
		for (const auto& x : panels) x->AddMeshes( ofs );
		return;
	}
}

#endif// _PANELGROUP_H
