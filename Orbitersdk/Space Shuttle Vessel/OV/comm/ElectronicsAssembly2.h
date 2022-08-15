/****************************************************************************
  This file is part of Space Shuttle Vessel

  Electronics Assembly 2 subsystem definition


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
2020/03/29   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/06   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Electronics Assembly 2 definition



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

#ifndef _comm_EA2_H_
#define _comm_EA2_H_


#include "..\AtlantisSubsystem.h"
#include <discsignals.h>
#include <Orbitersdk.h>


using namespace discsignals;


namespace comm
{
	class DeployedAssembly;

	class ElectronicsAssembly2:public AtlantisSubsystem
	{
			double dt_OLD;
			DeployedAssembly* pDeployedAssembly;

			DiscInPort pPower_Off;
			DiscInPort pPower_On;
			DiscInPort KUaz;
			DiscInPort KUel;
			DiscInPort RADSTB;
			DiscInPort RADON;
			DiscInPort RADARPOWERLOW;
			DiscInPort RADARPOWERMEDIUM;

			DiscOutPort Range;
			DiscOutPort RangeRate;
			DiscOutPort Detect;
			DiscOutPort TGTaz;
			DiscOutPort TGTel;

			OBJHANDLE target;
			double rOLD;

			OBJHANDLE FindTarget( double &r, double &az, double &el );
			bool GetTargetInfo( OBJHANDLE hVessel, double &r, double &rr, double &az, double &el, double dt );

			bool IsDetected( OBJHANDLE hVessel, double &r, double &az, double &el );

			double GetPower( void );

		public:
			ElectronicsAssembly2( AtlantisSubsystemDirector* _director, DeployedAssembly* pDeployedAssembly );
			virtual ~ElectronicsAssembly2();

			void Realize( void ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;
	};

};

#endif// _comm_EA2_H_