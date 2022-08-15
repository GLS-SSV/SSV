/****************************************************************************
  This file is part of Space Shuttle Vessel

  Drag Chute vessel definition


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
2020/05/01   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/25   GLS
2021/12/26   GLS
********************************************/

#ifndef __DRAGCHUTE_H
#define __DRAGCHUTE_H

#pragma once

#include <Orbitersdk.h>

const double CHUTE_DEFLATE_TIME = 0.4;
// chute will deflate in 2.5 seconds

class DragChute: public VESSEL4
{
public:
	DragChute(OBJHANDLE hVessel, int flightmodel);
	~DragChute();

	void clbkSetClassCaps( FILEHANDLE cfg ) override;
	void clbkPreStep(double simt, double simdt, double mjd) override;
	void clbkSaveState(FILEHANDLE scn) override;
	void clbkLoadStateEx(FILEHANDLE scn, void *status) override;
private:
	MESHHANDLE mesh;
	UINT mesh_idx;
	UINT anim_collapse;
	double anim_collapse_state;

	MGROUP_SCALE* collapse;

	void DefineAnimations();
};

#endif// __DRAGCHUTE_H
