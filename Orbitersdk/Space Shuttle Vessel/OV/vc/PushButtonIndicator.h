/****************************************************************************
  This file is part of Space Shuttle Vessel

  Push Button/Indicator VC component definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/10/04   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Pushbutton/indicator VC component definition



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
#ifndef __PUSHBUTTONINDICATOR_H
#define __PUSHBUTTONINDICATOR_H
#pragma once


#include "PushButton.h"
#include "StandardLight.h"
#include <DiscInPort.h>
#include <DiscOutPort.h>
#include <Orbitersdk.h>


namespace vc
{
	using discsignals::DiscOutPort;
	using discsignals::DiscInPort;

	class PushButtonIndicatorSingleLight : public StandardSingleLight
	{
			UINT anim_pb;
			double motionlength;
			MGROUP_TRANSLATE* pPushDown;
			DiscOutPort output;

		public:
			PushButtonIndicatorSingleLight( Atlantis* _sts, const string& _ident );
			~PushButtonIndicatorSingleLight();

			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			virtual void OnPress();
			virtual void OnRelease();
			void ConnectPushButton( DiscreteBundle* pBundle, unsigned short usLine );

			void SetMotionLength( double _motionlength );
	};



	class PushButtonIndicatorDoubleLight : public StandardDoubleLight
	{
			UINT anim_pb;
			double motionlength;
			MGROUP_TRANSLATE* pPushDown;
			DiscOutPort output;

		public:
			PushButtonIndicatorDoubleLight( Atlantis* _sts, const string& _ident );
			~PushButtonIndicatorDoubleLight();

			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			virtual void OnPress();
			virtual void OnRelease();
			void ConnectPushButton( DiscreteBundle* pBundle, unsigned short usLine );

			void SetMotionLength( double _motionlength );
	};
};

#endif //__PUSHBUTTONINDICATOR_H
