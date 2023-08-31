/****************************************************************************
  This file is part of Space Shuttle Vessel

  MEDS Analog/Digital Converter definition


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

#ifndef _dps_ADC_H_
#define _dps_ADC_H_


#include "../AtlantisSubsystem.h"
#include <DiscInPort.h>
#include <BusTerminal.h>


class APU;


namespace dps
{
	/**
	 * @brief	Implementation of the MEDS Analog/Digital Converter.
	 *
	 * This class receives analog subsystem data and digitalizes it for display.
	 */
	class ADC : public AtlantisSubsystem, public BusTerminal
	{
		private:
			discsignals::DiscInPort input[32];
			unsigned char id;// 1=1A, 2=1B, 3=2A, 4=2B
			APU* pAPU[3];
			
			unsigned short GetData( const unsigned short idx ) const;

		public:
			explicit ADC( AtlantisSubsystemDirector* _director, const string& _ident, BusManager* pBusManager );
			~ADC( void );

			void Realize( void ) override;

			void Rx( const BUS_ID id, void* data, const unsigned short datalen ) override;
	};
}

#endif// _dps_ADC_H_
