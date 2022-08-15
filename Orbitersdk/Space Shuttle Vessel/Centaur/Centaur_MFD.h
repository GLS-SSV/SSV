/****************************************************************************
  This file is part of Space Shuttle Vessel

  Centaur G/G-Prime MFD definition


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
2020/04/07   GLS
2020/05/14   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/25   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Centaur G/G-Prime MFD definition



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
#ifndef __SCMFD_H
#define __SCMFD_H


#include "MFDAPI.h"
#include "Centaur.h"


class Centaur_MFD:public MFD2
{
	private:
		Centaur* centaurvessel;

	public:
		Centaur_MFD( DWORD w, DWORD h, VESSEL *v );
		~Centaur_MFD( void );

		bool Update( oapi::Sketchpad *skp ) override;
		static int MsgProc( UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam );
};

#endif// __SCMFD_H
