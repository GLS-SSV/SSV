/****************************************************************************
  This file is part of Space Shuttle Vessel

  Power Supply Electronics definition


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
2020/04/01   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Power Supply Electronics definition



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
#ifndef _mps_PSE_H_
#define _mps_PSE_H_


#include <DiscInPort.h>
#include <Orbitersdk.h>


namespace mps
{
	class SSMEController;
	class DigitalComputerUnit;
	class ComputerInterfaceElectronics;

	using namespace discsignals;

	class PowerSupplyElectronics
	{
		protected:
			int ch;
			SSMEController* Controller;
			DigitalComputerUnit* DCU;
			ComputerInterfaceElectronics* CIEOpposite;

			bool PowerOn;
		public:
			DiscInPort AC;

			PowerSupplyElectronics( int ch, SSMEController* Controller );
			virtual ~PowerSupplyElectronics( void );

			void tmestp( double time );

			virtual void OnSaveState( FILEHANDLE scn ) const;
			virtual bool OnParseLine( const char* line );

			void Realize( void );

			void ConnectPower( DiscreteBundle* AC );

			bool Power( void ) const;
	};
}


#endif// _mps_PSE_H_
