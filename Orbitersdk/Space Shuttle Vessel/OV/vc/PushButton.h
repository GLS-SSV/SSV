/****************************************************************************
  This file is part of Space Shuttle Vessel

  Push Button VC Component definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/06/13   GLS
2022/10/04   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Pushbutton VC Component definition



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
#pragma once

#include "AtlantisVCComponent.h"
#include <DiscOutPort.h>

namespace vc
{
	inline constexpr double PUSH_LENGTH = 0.0015;


	using discsignals::DiscOutPort;
	using discsignals::DiscreteBundle;

	class PushButton: public AtlantisVCComponent {
		UINT anim_pb;
		UINT uiGroup;
		double motionlength;
		MGROUP_TRANSLATE* pPushDown;
		DiscOutPort output;

	public:
		PushButton( Atlantis* _sts, const std::string& _name );
		virtual ~PushButton();

		void DefineGroup(UINT _grpIndex);
		void DefineVCAnimations(UINT vc_idx) override;
		bool OnMouseEvent(int _event, float x, float y) override;
		virtual void OnPress();
		virtual void OnDepress();

		void SetMotionLength( double _motionlength );
		void Connect( DiscreteBundle* pBundle, unsigned short usLine );
	};
};