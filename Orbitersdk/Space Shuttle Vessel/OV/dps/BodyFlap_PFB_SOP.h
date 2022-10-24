/****************************************************************************
  This file is part of Space Shuttle Vessel

  Body Flap Position Feedback Subsystem Operating Program definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/06/20   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
2022/10/21   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Body Flap Position Feedback Subsystem Operating Program definition



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
#ifndef _dps_BF_PFB_SOP_H_
#define _dps_BF_PFB_SOP_H_


#include "SimpleGPCSoftware.h"
#include <discsignals.h>


namespace dps
{
	using namespace discsignals;

	/**
	 * @brief	Implementation of the Body Flap Position Feedback Subsystem Operating Program software that runs in the GPCs.
	 *
	 * This class retrieves the Body Flap position, and saves it in the COMPOOL.
	 */
	class BodyFlap_PFB_SOP:public SimpleGPCSoftware
	{
		private:
			DiscInPort dipPositionFeedback;

		public:
			explicit BodyFlap_PFB_SOP( SimpleGPCSystem* _gpc );
			~BodyFlap_PFB_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}

#endif// _dps_BF_PFB_SOP_H_
