/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Flight Computer Operating System Input/Output for GNC definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/28   GLS
2021/12/30   GLS
2022/05/19   GLS
2022/08/05   GLS
2022/12/23   GLS
2023/05/07   GLS
2023/05/12   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Simple Flight Computer Operating System Input/Output definition



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
#ifndef SIMPLEFCOSIO_GNC_H
#define SIMPLEFCOSIO_GNC_H


#include "../../dps_defs.h"
#include "../SimpleFCOS_IO.h"


enum BUS_ID;


namespace dps
{
	class SimpleGPCSystem;


	class SimpleFCOS_IO_GNC : public SimpleFCOS_IO
	{
		private:
			void InputEIU( unsigned short addr, unsigned short dataaddr, unsigned short datalen, BUS_ID busid );

			void OutputEIU( unsigned short addr, unsigned short dataaddr );
			void OutputDDU( unsigned short addr, unsigned short channeladdr, unsigned short dataaddr, unsigned short datalen );

		public:
			explicit SimpleFCOS_IO_GNC( SimpleGPCSystem* _gpc );
			virtual ~SimpleFCOS_IO_GNC();

			/**
			 * Send data requests to subystems.
			 */
			virtual void input( void ) override;

			/**
			 * Send commands to subystems.
			 */
			virtual void output( void ) override;
	};
};

#endif// SIMPLEFCOSIO_GNC_H
