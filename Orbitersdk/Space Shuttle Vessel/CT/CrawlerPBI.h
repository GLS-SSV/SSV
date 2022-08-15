/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerPBI definition


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
2021/08/24   GLS
2021/12/25   GLS
********************************************/

#ifndef CRAWLERPBI_H_C614EBD5_5D80_4c0b_8513_0A2A23CF6DCC
#define CRAWLERPBI_H_C614EBD5_5D80_4c0b_8513_0A2A23CF6DCC
#pragma once

#include <BasicVCComponent.h>
#include "CrawlerPanelLight.h"
#include "Crawler_vc_defs.h"


namespace vc
{
	using discsignals::DiscOutPort;

	class CrawlerPBI : public CrawlerPanelLight
	{
		private:
			UINT anim_pb;
			double motionlength;
			MGROUP_TRANSLATE* pPushDown;
		public:
			CrawlerPBI( Crawler* _v, const string& _ident );
			~CrawlerPBI();

			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			virtual void OnPress();
			virtual void OnRelease();
			void ConnectPushButton( DiscreteBundle* pBundle, unsigned short usLine );

			void SetMotionLength( double _motionlength );

			DiscOutPort output;
	};

	class CrawlerPBI2 : public CrawlerPanelLight2
	{
			UINT anim_pb;
			double motionlength;
			MGROUP_TRANSLATE* pPushDown;
		public:
			CrawlerPBI2( Crawler* _v, const string& _ident );
			~CrawlerPBI2();

			void DefineVCAnimations( UINT vc_idx ) override;
			bool OnMouseEvent( int _event, float x, float y ) override;
			virtual void OnPress();
			virtual void OnRelease();
			void ConnectPushButton( DiscreteBundle* pBundle, unsigned short usLine );

			void SetMotionLength( double _motionlength );

			DiscOutPort output;
	};
};

#endif