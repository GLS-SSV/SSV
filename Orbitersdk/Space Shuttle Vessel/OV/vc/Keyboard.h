/****************************************************************************
  This file is part of Space Shuttle Vessel

  Keyboard VC Component definition


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
2020/06/20   GLS
2021/01/20   GLS
2021/07/03   GLS
2021/08/24   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Keyboard VC Component



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

  See http://spaceshuttleultra.sourceforge.net/license/ for more details.

  **************************************************************************/
#ifndef __KEYBOARD_H
#define __KEYBOARD_H


#include "AtlantisVCComponent.h"


namespace dps
{
	class IDP;
}

namespace vc
{
	class Keyboard:public AtlantisVCComponent
	{
			int ID;

			dps::IDP* pIDP[2];

			// key order is same as in dps_defs.h
			UINT anim_key[32];
			UINT keyGrp[32];
			MGROUP_TRANSLATE* pKEY[32];

			void OnKeyPress( char key );
			void OnKeyRelease( char key );

		public:
			Keyboard( Atlantis* _sts, const std::string& _ident, int ID );
			virtual ~Keyboard();

			void ConnectIDP( unsigned int num, dps::IDP* p_idp );

			void DefineGroup( UINT* _grpIndex );
			virtual void DefineVCAnimations( UINT vc_idx ) override;
			virtual bool OnMouseEvent( int _event, float x, float y ) override;
	};
};

#endif //__TALKBACK_H