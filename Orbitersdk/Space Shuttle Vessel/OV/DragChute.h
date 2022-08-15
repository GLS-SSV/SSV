/****************************************************************************
  This file is part of Space Shuttle Vessel

  Drag Chute subsystem definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/03/24   GLS
2022/03/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Drag Chute definition



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
#ifndef __DC_H
#define __DC_H


#include <discsignals.h>
#include "AtlantisSubsystem.h"
#include <Orbitersdk.h>


using namespace discsignals;


class DragChute:public AtlantisSubsystem
{
	private:
		enum {STOWED, DEPLOYING, REEFED, INFLATED, JETTISONED} DragChuteState;
		UINT mesh_index;
		MESHHANDLE hMesh;

		UINT anim_deploy;
		UINT anim_spin;
		AnimState as_spin;

		double DragChuteDeployTime;
		double DragChuteSize;// 0 (Stowed/Jettisoned) or 0.4 (Reefed) or 1.0 (Deployed)

		DiscOutPort DragChuteARM1LT[2];
		DiscOutPort DragChuteARM2LT[2];
		DiscOutPort DragChuteDPY1LT[2];
		DiscOutPort DragChuteDPY2LT[2];
		DiscOutPort DragChuteJETT1LT[2];
		DiscOutPort DragChuteJETT2LT[2];
		DiscInPort DragChuteARM[2];
		DiscInPort DragChuteDPY[2];
		DiscInPort DragChuteJETT[2];

		void SpinChute( double simdt );
		void AddMesh( void );
		void DefineAnimations( void );

	public:
		explicit DragChute( AtlantisSubsystemDirector* _director );
		virtual ~DragChute();

		void Realize( void ) override;
		void OnPreStep( double simt, double simdt, double mjd ) override;
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine( void ) const override {return true;};
		double GetSubsystemMass() const override;

		void AddAero( void ) const;
};

#endif //__DC_H
