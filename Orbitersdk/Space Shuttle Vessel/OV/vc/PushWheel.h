/****************************************************************************
  This file is part of Space Shuttle Vessel

  Push Wheel VC Component


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
#ifndef __PUSHWHEEL_H
#define __PUSHWHEEL_H


#include "SelectorWheel.h"


namespace vc
{
	class PushWheel:public SelectorWheel
	{
		private:
			unsigned short tgtpistonup;
			unsigned short tgtpistondn;

			bool bHasPushButtonDir;

			UINT grpIndexUp;
			UINT grpIndexDn;
			MGROUP_TRANSLATE* piston_up;
			MGROUP_TRANSLATE* piston_dn;
			UINT anim_up;
			UINT anim_dn;

			VECTOR3 PushButtonDir;

		public:
			PushWheel( Atlantis* _sts, const std::string& _ident );
			virtual ~PushWheel();

			void DefinePushButtonGroups( UINT _grpIndexUp, UINT _grpIndexDn );
			void DefinePushButtonDirection( const VECTOR3& dir );
			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
	};
};

#endif// __PUSHWHEEL_H
