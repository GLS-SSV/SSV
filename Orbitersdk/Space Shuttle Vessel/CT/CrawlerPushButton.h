/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerPushButton definition


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
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/01/20   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/09/29   GLS
********************************************/

#ifndef CRAWLERPUSHBUTTON_H_
#define CRAWLERPUSHBUTTON_H_


#include <BasicVCComponent.h>
#include "Crawler_vc_defs.h"
#include <DiscOutPort.h>


namespace vc
{
	using discsignals::DiscOutPort;

	class CrawlerPushButton : public BasicVCComponent<Crawler>
	{
		private:
			UINT anim_pb;
			UINT uiGroup;
			double motionlength;
			MGROUP_TRANSLATE* pPushDown;
		public:
			CrawlerPushButton( Crawler* _v, const string& _ident );
			virtual ~CrawlerPushButton();

			void DefineGroup(UINT _grpIndex);
			void DefineVCAnimations(UINT vc_idx) override;
			bool OnMouseEvent(int _event, float x, float y) override;
			virtual void Realize() override;
			virtual void OnPress();
			virtual void OnDepress();

			void SetMotionLength( double _motionlength );

			DiscOutPort output;
	};
}

#endif// CRAWLERPUSHBUTTON_H_
