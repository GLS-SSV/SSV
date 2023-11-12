/****************************************************************************
  This file is part of Space Shuttle Vessel

  Multiplexer/Demultiplexer Payload Forward 2 definition



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
#ifndef _MDM_PF2_H_
#define _MDM_PF2_H_


#include "MDM.h"


namespace dps
{
	class MDM_PF2:public MDM
	{
		public:
			MDM_PF2( AtlantisSubsystemDirector* _director, BusManager* pBusManager );
			virtual ~MDM_PF2();

			void Realize( void ) override;
	};
}

#endif// _MDM_PF2_H_
