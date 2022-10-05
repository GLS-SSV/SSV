/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbital Maneuvering System subsystem definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Orbital Maneuvering System definition



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
#ifndef __OMS_H_
#define __OMS_H_


#include "../AtlantisSubsystem.h"
#include <DiscInPort.h>


using namespace discsignals;


namespace oms
{
	class OMS:public AtlantisSubsystem
	{
		private:
			unsigned int ID;

			DiscInPort OMS_Arm;
			DiscInPort OMS_ArmPress;
			DiscInPort OMS_Vlv_Coil;
			DiscInPort OMS_Eng_Vlv;

		public:
			OMS( AtlantisSubsystemDirector* _director, const string& _ident, unsigned int ID );
			virtual ~OMS( void );

			void Realize( void ) override;
			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;
			bool SingleParamParseLine( void ) const override {return true;};
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}


#endif// __OMS_H_
