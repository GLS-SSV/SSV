/****************************************************************************
  This file is part of Space Shuttle Vessel

  LDB Output Message Coordinator definition


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
#ifndef _DGO_LDB_COORD_H_
#define _DGO_LDB_COORD_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	class DGO_LDB_COORD : public SimpleGPCSoftware
	{
		public:
			DGO_LDB_COORD( SimpleGPCSystem* pGPC );
			virtual ~DGO_LDB_COORD( void );

			void Call( const unsigned short DGO_BUFFER_ID, const unsigned short DGO_WDCOUNT );
	};
}

#endif// _DGO_LDB_COORD_H_
