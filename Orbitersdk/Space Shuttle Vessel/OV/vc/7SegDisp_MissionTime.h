/****************************************************************************
  This file is part of Space Shuttle Vessel

   Mission Time 7-Segment Display Controller VC Component


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
2021/08/24   GLS
2021/12/26   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Mission Time 7-Segment Display Controller VC Component



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
#ifndef __7SD_MT_H
#define __7SD_MT_H


#include "7SegDisp.h"
#include <DiscInPort.h>


namespace vc
{
	using namespace discsignals;

	class _7SegDisp_MissionTime:public _7SegDisp
	{
		private:
			bool fwd;

			DiscInPort pMissionTimerTEST;
			DiscInPort pMissionTimerGMT;

		public:
			_7SegDisp_MissionTime( Atlantis* _sts, const std::string& _ident );
			virtual ~_7SegDisp_MissionTime();

			void SetLocation( bool fwd );
			void Realize( void ) override;

			void Controller( void ) override;
	};
};

#endif// __7SD_MT_H