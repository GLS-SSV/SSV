/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic rotary switch vc component definition


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
2020/03/20   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/08/24   GLS
2021/01/20   GLS
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic rotary switch vc component definition



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
#ifndef __VC_BASICROTARYSWITCH_H
#define __VC_BASICROTARYSWITCH_H
#pragma once

#include "AtlantisVCComponent.h"
#include <vector>
#include <string>

namespace vc
{
	class BasicRotarySwitch: public AtlantisVCComponent
	{
	protected:
		unsigned short usNumPositions;
		vector<string> labels;
		unsigned short usCurrentPosition;

		bool allowWraparound;

		float rotOffset; // angle in radians
		float rotAngle; // angle in radians
		MGROUP_ROTATE* pSwitchRot;
		UINT anim_switch;
		UINT grpIndex;
	public:
		BasicRotarySwitch(Atlantis* _sts, unsigned short _usNumPositions, const std::string &_ident);
		virtual ~BasicRotarySwitch();

		void SetLabel(unsigned short iPosition, const string& _label);
		void DefineGroup(UINT _grpIndex);
		void DefineRotationAngle(float _rotAngle); // angle measured in degrees
		virtual void SetInitialAnimState( double fState ) override;
		/**
		 * Angles (in degreees) between 12-o'clock position and initial (usCurrentPosition=0) position
		 * Used for mouse click handling
		 */
		void SetOffset(float fOffset = 0.0);
		void SetWraparound(bool _allowWraparound);

		void DefineVCAnimations(UINT vc_idx) override;
		bool GetStateString(unsigned long ulBufferSize, char* pszBuffer) override;
		bool OnParseLine(const char* line) override;
		bool OnMouseEvent(int _event, float x, float y) override;
		void Realize() override;

		virtual void OnRotateLeft();
		virtual void OnRotateRight();
		virtual void OnPositionChange(unsigned short usNewPosition);

		/**
		 * Sets initial position of switch
		 * If used, it has to be called as early as possible so it doesn't overwrite scenario entry.
		 */
		void SetInitialPosition(unsigned short usPos);
	};
};

#endif //__VC_BASICROTARY_SWITCH_H