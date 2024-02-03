/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Power Control Assembly 3 subsystem definition


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
#ifndef _MPC3_H_
#define _MPC3_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


class MPC3: public AtlantisSubsystem
{
	private:
		discsignals::DiscOutPort LogicPwr_C2;
		discsignals::DiscOutPort LogicPwr_C3;

	public:
		explicit MPC3( AtlantisSubsystemDirector* _director );
		virtual ~MPC3();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;
};

#endif// _MPC3_H_
