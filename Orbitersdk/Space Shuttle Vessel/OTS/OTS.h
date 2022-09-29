/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbiter Transporter Vehicle vessel definition


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
2020/05/01   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/08/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/08/28   GLS
2021/12/25   GLS
2021/12/30   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Centaur G/G-Prime definition



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
#ifndef __OTS_H
#define __OTS_H


#include <Orbitersdk.h>


class SurfaceRoving;

class OTS: public VESSEL4
{
	public:
		explicit OTS( OBJHANDLE hVessel );
		~OTS( void );

		void clbkSetClassCaps( FILEHANDLE cfg ) override;
		void clbkPostCreation( void ) override;
		void clbkPreStep( double simt, double simdt, double mjd ) override;
		int clbkConsumeBufferedKey( DWORD key, bool down, char* kstate ) override;
		void clbkVisualCreated( VISHANDLE vis, int refcount ) override;
		void clbkSaveState( FILEHANDLE scn ) override;
		void clbkLoadStateEx( FILEHANDLE scn, void *status ) override;

	private:
		MESHHANDLE hMesh;
		UINT mesh_idx;

		double fwdsteer;
		double aftsteer;
		double drive;

		ATTACHMENTHANDLE ahToOV;

		SurfaceRoving* surfaceroving;

		void DefineAnimations( void );
};

#endif// __OTS_H
