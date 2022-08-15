/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerPanel definition


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
2020/06/14   GLS
2020/06/20   GLS
2021/08/24   GLS
2021/12/25   GLS
********************************************/

#ifndef _CRAWLER_VC_DEFS_H_9D94C752_88E7_4ecd_8F96_10FBC0914FDE
#define _CRAWLER_VC_DEFS_H_9D94C752_88E7_4ecd_8F96_10FBC0914FDE
#pragma once

#include "BasicPanel.h"

class Crawler;

const VECTOR3 CRAWLER_REAR_VC_OFFSET = _V(-15.242, 4.544, -18.35);
const VECTOR3 CRAWLER_FWD_VC_OFFSET = _V(15.242, 4.544, 18.35);

namespace vc
{
	typedef enum {
		FWD = 0,// CAB-3
		REAR = 1// CAB-1
	} CRAWLER_CAB;

	class CrawlerPanel : public BasicPanel<Crawler>
	{
	protected:
		CRAWLER_CAB cabID;
	public:
		CrawlerPanel(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab)
			: BasicPanel(_v, _ident), cabID(_cab) {};
		virtual ~CrawlerPanel() {};
	protected:
		/**
		 * Rotates vector for Fwd cab
		 */
		inline VECTOR3 TransformVector(const VECTOR3& v) {
			if(cabID == FWD) return _V(-v.x, v.y, -v.z);
			else return v;
		}
	};
};

#endif