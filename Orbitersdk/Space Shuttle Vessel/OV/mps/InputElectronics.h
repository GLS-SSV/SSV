/****************************************************************************
  This file is part of Space Shuttle Vessel

  Input Electronics definition


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

  Input Electronics definition



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
#ifndef _mps_IE_H_
#define _mps_IE_H_


#include <Orbitersdk.h>
#include <DiscInPort.h>


namespace mps
{
	class PowerSupplyElectronics;
	class OutputElectronics;

	using namespace discsignals;


	class InputElectronics
	{
		friend class SSMEController;

		protected:
			int ch;
			SSMEController* Controller;
			PowerSupplyElectronics* PSE;
			OutputElectronics* OE;

			// sensor input
			DiscInPort press[15];
			DiscInPort temp[8];
			DiscInPort speed[3];
			DiscInPort flow[4];
			double actpos[9];
			double samplehold[5];

		public:
			InputElectronics( int ch, SSMEController* Controller );
			virtual ~InputElectronics( void );

			virtual void OnSaveState( FILEHANDLE scn ) const;
			virtual bool OnParseLine( const char* line );

			void Realize( DiscreteBundle* Press, DiscreteBundle* Temp, DiscreteBundle* Flow, DiscreteBundle* Speed );

			virtual void tmestp( double time ) = 0;

			void GetData( unsigned short device, unsigned short* data );
	};
}


#endif// _mps_IE_H_
