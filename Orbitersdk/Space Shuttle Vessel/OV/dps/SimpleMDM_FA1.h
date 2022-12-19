/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Multiplexer/Demultiplexer Flight-Critical Aft 1 definition



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
2020/07/11   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/01/28   GLS
2022/05/24   GLS
2022/11/15   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple Multiplexer/Demultiplexer Flight-Critical Aft 1 definition



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
#ifndef _SIMPLEMDM_FA1_H_
#define _SIMPLEMDM_FA1_H_


#include "SimpleMDM.h"


namespace dps
{
	class SimpleMDM_FA1:public SimpleMDM
	{
		private:
			bool powered;

			DiscOutPort dopIOM2[3][16];
			DiscInPort dipIOM3[3][16];
			DiscInPort dipIOM5[3][16];
			DiscInPort dipIOM6[32];
			DiscOutPort dopIOM7[3][16];
			DiscInPort dipIOM8[3][16];
			DiscOutPort dopIOM10[3][16];
			DiscInPort dipIOM11[3][16];
			DiscOutPort dopIOM12[3][16];
			DiscInPort dipIOM13[3][16];
			DiscInPort dipIOM14[32];
			DiscOutPort dopIOM15[3][16];

		public:
			explicit SimpleMDM_FA1( AtlantisSubsystemDirector* _director );
			virtual ~SimpleMDM_FA1();

			void Realize( void ) override;

			void busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;
			void busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _SIMPLEMDM_FA1_H_
