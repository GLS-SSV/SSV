/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Multiplexer/Demultiplexer definition


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
2020/06/20   GLS
2020/07/11   GLS
2021/07/03   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple Multiplexer/Demultiplexer definition



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
#ifndef _SIMPLEMDM_H_
#define _SIMPLEMDM_H_


#include "../AtlantisSubsystem.h"
#include "SimpleBTU.h"
#include <discsignals.h>


namespace gnc
{
	class RadarAltimeter;
}

using namespace discsignals;


namespace dps
{


	class SimpleMDM:public AtlantisSubsystem, public SimpleBTU
	{
		protected:
			DiscInPort Power1;
			DiscInPort Power2;

		public:
			SimpleMDM( AtlantisSubsystemDirector* _director, const string& _ident );
			virtual ~SimpleMDM();

			void Realize( void ) override;

			void busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;
			void busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) override;

			virtual void IOM_TAC( unsigned short task, unsigned int ch, unsigned short& data, gnc::RadarAltimeter* pRA );
			virtual void IOM_DIL( unsigned short task, unsigned int ch, unsigned short& data, DiscInPort dip[3][16] );
			virtual void IOM_DIH( unsigned short task, unsigned int ch, unsigned short& data, DiscInPort dip[3][16] );
			virtual void IOM_DOL( unsigned short task, unsigned int ch, unsigned short& data, DiscOutPort dop[3][16] );
			virtual void IOM_DOH( unsigned short task, unsigned int ch, unsigned short& data, DiscOutPort dop[3][16] );
	};
}

#endif// _SIMPLEMDM_H_
