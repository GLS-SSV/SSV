/****************************************************************************
  This file is part of Space Shuttle Vessel

  Multiplexer/Demultiplexer definition


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
#ifndef _MDM_H_
#define _MDM_H_


#include "../AtlantisSubsystem.h"
#include <BusTerminal.h>
#include <discsignals.h>
#include <vector>


using namespace discsignals;


namespace dps
{
	class IOM;


	class MDM:public AtlantisSubsystem, public BusTerminal
	{
		protected:
			discsignals::DiscInPort Power1;
			discsignals::DiscInPort Power2;
			bool powered;

			unsigned short addr;

			std::vector<IOM*> iom;

		public:
			MDM( AtlantisSubsystemDirector* _director, const string& _ident, BusManager* pBusManager, const unsigned short BusAddr, const BUS_ID PriBus, const BUS_ID SecBus );
			virtual ~MDM();

			bool SingleParamParseLine() const override {return true;};
			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			void Rx( const BUS_ID id, void* data, const unsigned short datalen ) override;

			virtual void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// _MDM_H_
