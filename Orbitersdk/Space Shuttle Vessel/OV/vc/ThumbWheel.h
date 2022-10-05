/****************************************************************************
  This file is part of Space Shuttle Vessel

  Thumb Wheel VC Component


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
#ifndef __THUMBWHEEL_H
#define __THUMBWHEEL_H


#include "SelectorWheel.h"


namespace vc
{
	class ThumbWheel:public SelectorWheel
	{
		public:
			ThumbWheel( Atlantis* _sts, const std::string& _ident );
			virtual ~ThumbWheel();

			bool OnMouseEvent( int _event, float x, float y ) override;

	};
}

#endif// __THUMBWHEEL_H
