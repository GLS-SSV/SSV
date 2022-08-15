/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Bus Terminal Unit definition


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
2021/01/19   GLS
2021/07/03   GLS
2021/08/24   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple Bus Terminal Unit definition



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
#ifndef SIMPLEBTU_H
#define SIMPLEBTU_H


#include "dps_defs.h"


namespace dps
{
	class SimpleShuttleBus;

	class SimpleBTU
	{
		private:
			SimpleShuttleBus* pBus;
			unsigned short usTerminalID;

		protected:
			SimpleShuttleBus* GetBus( void ) const;
			unsigned short GetAddr( void ) const;
			bool ReadEna;

		public:
			SimpleBTU();
			virtual ~SimpleBTU();

			/**
			 * Implements logic to command bus.
			 * If subsystem-to-GPC transfer, cw = 0.
			 * @param	cw	command word
			 * @param	cdw	command data word
			 */
			virtual void busCommand( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) = 0;

			/**
			 * Implements logic to read bus and check id on the received words.
			 * If subsystem-to-GPC transfer, cw = 0.
			 * @param	cw	command word
			 * @param	cdw	command data word
			 */
			virtual void busRead( const SIMPLEBUS_COMMAND_WORD& cw, SIMPLEBUS_COMMANDDATA_WORD* cdw ) = 0;

			void ConnectTo( SimpleShuttleBus* _pBus );

			void SetTerminalID( unsigned short TermID );
	};
};

#endif// SIMPLEBTU_H
