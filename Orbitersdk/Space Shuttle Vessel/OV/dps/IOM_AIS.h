/****************************************************************************
  This file is part of Space Shuttle Vessel

  MDM IOM Analog Input Single-Ended definition


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
#ifndef _IOM_AIS_H_
#define _IOM_AIS_H_


#include "IOM.h"
#include <discsignals.h>


namespace dps
{
	class IOM_AIS:public IOM
	{
		private:
			discsignals::DiscInPort port[32];

		public:
			IOM_AIS( const std::string& mdmname, const unsigned short iomidx );
			virtual ~IOM_AIS();

			void Connect( discsignals::DiscreteBundleManager* bman ) override;

			bool busSCU( const unsigned char addr, const unsigned char task, unsigned short& data ) override;
	};
}

#endif// _IOM_AIS_H_
