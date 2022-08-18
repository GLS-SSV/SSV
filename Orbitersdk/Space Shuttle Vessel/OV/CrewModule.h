/****************************************************************************
  This file is part of Space Shuttle Ultra

  Crew Module definition



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
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
#ifndef __CM_H_
#define __CM_H_


#include "AtlantisSubsystem.h"


class CrewModule:public AtlantisSubsystem
{
	private:
		enum CC_CFG {ASCENTENTRY, ORBIT};
		CC_CFG cfg;// current crew module configuration

		unsigned short seats;// number of seats, except CDR and PLT seats
		bool internalAL;
		bool escape;

		VECTOR3 SEATS_POSITION[5];

		MESHHANDLE hSeatMesh;
		UINT mesh_seat[5];// seats 3 thru 7

		MGROUP_ROTATE* pSeat5rot;
		MGROUP_ROTATE* pSeat6rot;
		MGROUP_ROTATE* pSeat7rot;
		UINT anim_seats;


		enum COAS_LOC {STOWED, FW, OH};
		COAS_LOC COAS_loc;// current COAS location

		MESHHANDLE hCOASMesh;
		UINT mesh_coasfw;
		UINT mesh_coasoh;

		MGROUP_ROTATE* pCOASFWrot;
		UINT anim_COASFW;


		MESHHANDLE hPoleMesh;
		UINT mesh_polestowed;
		UINT mesh_poleinstalled;

		MGROUP_ROTATE* pPoleStowedrot;
		MGROUP_ROTATE* pPoleInstalledrot;
		UINT anim_PoleStowed;
		UINT anim_PoleInstalled;


		void AddMesh( void );
		void UpdateVisual( void );
		void UpdateDialog( HWND hWnd );

	public:
		CrewModule( AtlantisSubsystemDirector* _director, unsigned short seats, bool internalAL, bool escape );
		virtual ~CrewModule( void );

		void Realize( void ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine( void ) const override {return true;};
		void OnPreStep( double simt, double simdt, double mjd ) override;

		void HideMeshes( void );
		void ShowMeshes( void );
		void VisualCreated( VISHANDLE vis );
		bool IsOrbitConfig( void ) const {return cfg == ORBIT;};

		BOOL CC_DlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};


#endif// __CM_H_
