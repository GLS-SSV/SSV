/****************************************************************************
  This file is part of Space Shuttle Vessel

  Event Time 7-Segment Display Controller VC Component


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
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Event Time 7-Segment Display Controller VC Component



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
#ifndef __7SD_ET_H
#define __7SD_ET_H


#include "7SegDisp.h"
#include <DiscInPort.h>


namespace vc
{
	using discsignals::DiscInPort;

	class _7SegDisp_EventTime:public _7SegDisp
	{
		private:
			short time;
			double clk;

			bool start;
			bool up;
			bool forceup;
			bool forceup_set;
			bool old_start;
			bool old_AbortReset;
			bool old_LiftoffStart;

		public:
			DiscInPort Timer_Set;
			DiscInPort Timer_Reset;
			DiscInPort Control_Start;
			DiscInPort Control_Stop;
			DiscInPort Mode_Up;
			DiscInPort Mode_Test;

			DiscInPort Seconds_1;
			DiscInPort Seconds_2;
			DiscInPort Seconds_4;
			DiscInPort Seconds_8;
			DiscInPort Seconds_10;
			DiscInPort Seconds_20;
			DiscInPort Seconds_40;

			DiscInPort Minutes_1;
			DiscInPort Minutes_2;
			DiscInPort Minutes_4;
			DiscInPort Minutes_8;
			DiscInPort Minutes_10;
			DiscInPort Minutes_20;
			DiscInPort Minutes_40;

			DiscInPort LiftoffStart;
			DiscInPort AbortReset;// not implemented in the sw

			_7SegDisp_EventTime( Atlantis* _sts, const std::string& _ident );
			virtual ~_7SegDisp_EventTime();

			bool OnParseLine( const char* line ) override;
			bool GetStateString( unsigned long ulBufferSize, char* pszBuffer ) override;

			void Controller( void ) override;
	};
};

#endif// __7SD_ET_H