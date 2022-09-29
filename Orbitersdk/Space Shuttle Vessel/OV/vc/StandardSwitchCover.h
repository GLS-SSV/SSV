/****************************************************************************
  This file is part of Space Shuttle Vessel

  Standard Switch cover VC component


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
2020/05/10   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Standard Switch cover VC component



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
#ifndef __STANDARDSWITCHCOVER_H
#define __STANDARDSWITCHCOVER_H


#include "BasicSwitch.h"

namespace vc
{
	/**
	 * Class for switch cover.
	 * Cover component must be added to panel BEFORE switch it covers.
	 */
	class StandardSwitchCover : public BasicSwitch
	{
		MGROUP_ROTATE* pcoverrot;
		UINT anim_cover;

		VCMOUSEEVENTPOINT mouse_a[2], mouse_d[2];
		UINT mouseregion;
	public:
		StandardSwitchCover(Atlantis* _sts, const std::string& _ident);
		virtual ~StandardSwitchCover();

		void DefineVCAnimations(UINT vc_idx) override;
		bool OnMouseEvent(int _event, float x, float y) override;
		void OnPositionChange(unsigned short usNewPosition) override;

		void SetMouseRegion( UINT aid, unsigned short position, float xmin, float ymin, float xmax, float ymax);
	};
}

#endif // __STANDARDSWITCHCOVER_H
