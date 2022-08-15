/****************************************************************************
  This file is part of Space Shuttle Vessel

  Basic Mechanical Meter VC Component definition


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
2020/06/20   GLS
2021/08/24   GLS
2021/12/26   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Basic Mechanical Meter VC Component definition



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
#ifndef __VC_BASICMECHMETER_H
#define __VC_BASICMECHMETER_H


#include "AtlantisVCComponent.h"
#include <DiscInPort.h>


namespace vc
{
	using ::discsignals::DiscreteBundle;
	using ::discsignals::DiscInPort;

	class BasicMechMeter:public AtlantisVCComponent
	{
		protected:
			UINT anim;

			UINT grpIndex;

			double motionrange;// degrees or meters

		public:
			DiscInPort input;

			BasicMechMeter( Atlantis* _sts, const string& _ident );
			virtual ~BasicMechMeter();

			void DefineNeedleGroup( UINT _grpIndex );
			void SetMotionRange( double range );

			void SetInput( DiscreteBundle* pBundle, unsigned short usLine );
	};
}

#endif// __VC_BASICMECHMETER_H
