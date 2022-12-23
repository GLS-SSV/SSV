/****************************************************************************
  This file is part of Space Shuttle Vessel

  Simple Flight Computer Operating System Input/Output for SM definition


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
#ifndef SIMPLEFCOSIO_SM_H
#define SIMPLEFCOSIO_SM_H


#include "dps_defs.h"
#include "SimpleFCOS_IO.h"


namespace dps
{
	class SimpleGPCSystem;

	class SimpleFCOS_IO_SM : public SimpleFCOS_IO
	{
		public:
			explicit SimpleFCOS_IO_SM( SimpleGPCSystem* _gpc );
			virtual ~SimpleFCOS_IO_SM();

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

#endif// SIMPLEFCOSIO_SM_H
