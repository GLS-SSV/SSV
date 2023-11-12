/****************************************************************************
  This file is part of Space Shuttle Vessel

  MDM IOM Analog Output Differential definition


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
#ifndef _IOM_AOD_H_
#define _IOM_AOD_H_


#include "IOM.h"
#include <discsignals.h>


namespace dps
{
	class IOM_AOD:public IOM
	{
		private:
			discsignals::DiscOutPort portPlus[16];
			discsignals::DiscOutPort portMinus[16];
			unsigned short driver[16];

			void Output( const unsigned short addr );

		public:
			IOM_AOD( const std::string& mdmname, const unsigned short iomidx );
			virtual ~IOM_AOD();

			void Connect( discsignals::DiscreteBundleManager* bman ) override;
			bool LoadState( const char* line ) override;
			void SaveState( FILEHANDLE scn ) const override;
			void PowerLoss( void ) override;

			bool busSCU( const unsigned char addr, const unsigned char task, unsigned short& data ) override;
	};
}

#endif// _IOM_AOD_H_
