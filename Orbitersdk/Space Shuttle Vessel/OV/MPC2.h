/****************************************************************************
  This file is part of Space Shuttle Vessel

  Mid Power Control Assembly 2 subsystem definition


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
#ifndef _MPC2_H_
#define _MPC2_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


class MPC2: public AtlantisSubsystem
{
	private:
		bool K5;

		discsignals::DiscInPort K5_on;
		discsignals::DiscInPort K5_off;

		discsignals::DiscOutPort MNB_A7;

		discsignals::DiscOutPort LogicPwr_B1;
		discsignals::DiscOutPort LogicPwr_B2;

		discsignals::DiscOutPort LightDepressVlv_MNB;

	public:
		explicit MPC2( AtlantisSubsystemDirector* _director );
		virtual ~MPC2();

		void Realize( void ) override;

		void OnPreStep( double simt, double simdt, double mjd ) override;

		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		bool SingleParamParseLine() const override {return true;};
};

#endif// _MPC2_H_
