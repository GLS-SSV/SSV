/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Multiplexer/Demultiplexer Flight-Critical Forward 2 definition



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
2020/04/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2020/07/11   GLS
2021/06/28   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/28   GLS
2021/12/30   GLS
2022/05/24   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple Multiplexer/Demultiplexer Flight-Critical Forward 2 definition



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
#ifndef _SIMPLEMDM_FF2_H_
#define _SIMPLEMDM_FF2_H_


#include "SimpleMDM.h"


namespace gnc
{
	class RadarAltimeter;
}


namespace dps
{
	class SimpleMDM_FF2:public SimpleMDM
	{
		private:
			bool powered;

			DiscOutPort dopIOM2[3][16];
			DiscInPort dipIOM4[3][16];
			DiscOutPort dopIOM5[3][16];
			DiscInPort dipIOM6[3][16];
			DiscInPort dipIOM9[3][16];
			DiscOutPort dopIOM10[3][16];
			DiscInPort dipIOM12[3][16];
			DiscOutPort dopIOM13[3][16];
			DiscInPort dipIOM15[3][16];
			gnc::RadarAltimeter* pRA2;

		public:
			explicit SimpleMDM_FF2( AtlantisSubsystemDirector* _director );
			virtual ~SimpleMDM_FF2();

			void Realize( void ) override;

			void busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;
			void busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;

			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _SIMPLEMDM_FF2_H_
