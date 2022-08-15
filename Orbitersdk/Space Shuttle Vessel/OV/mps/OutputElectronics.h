/****************************************************************************
  This file is part of Space Shuttle Vessel

  Output Electronics definition


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

  Output Electronics definition



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
#ifndef _mps_OE_H_
#define _mps_OE_H_


#include <Orbitersdk.h>
#include <DiscOutPort.h>


namespace mps
{
	class SSME;
	class SSMEController;
	class PowerSupplyElectronics;
	class ComputerInterfaceElectronics;

	using namespace discsignals;

	class OutputElectronics
	{
		protected:
			int ch;
			SSMEController* Controller;
			SSME* eng;
			PowerSupplyElectronics* PSE;
			ComputerInterfaceElectronics* CIE[2];
			double time;

			unsigned short StorageRegister;
			unsigned short ONOFFCommandRegister[2];// only 12 MSBs used

			double SH[5];
			double POS[9];
			double SVmodel_cur[5];
			double SVmodel_tgt[5];
			double triplevel[2];

			DiscOutPort HSV_pos[5];
			DiscOutPort FO_SS[5];
			DiscOutPort FS_SS[5];

			DiscOutPort FuelSystemPurge_SV;
			DiscOutPort BleedValvesControl_SV;
			DiscOutPort EmergencyShutdown_SV;
			DiscOutPort ShutdownPurge_SV;
			DiscOutPort HPOTPISPurge_SV;
			DiscOutPort AFV_SV;
			DiscOutPort HPV_SV;

		public:
			OutputElectronics( int ch, SSME* eng, SSMEController* Controller );
			virtual ~OutputElectronics( void );

			virtual void OnSaveState( FILEHANDLE scn ) const;
			virtual bool OnParseLine( const char* line );

			virtual void tmestp( double time, double tmestp ) = 0;
			void Realize( discsignals::DiscreteBundle* bundle, discsignals::DiscreteBundle* bundleCCV, discsignals::DiscreteBundle* bundleMFV, discsignals::DiscreteBundle* bundleMOV, discsignals::DiscreteBundle* bundleFPOV, discsignals::DiscreteBundle* bundleOPOV );

			virtual void StorageRegister_write( unsigned short data, int ch ) = 0;
			virtual unsigned short StorageRegister_read( void ) const = 0;
			virtual unsigned short ONOFFCommandRegister_read( int num ) const = 0;
			virtual void CommandDecoder( void ) = 0;

			virtual void GetSH( double* data ) = 0;
			virtual void GetPOS( double* data ) = 0;
	};
}


#endif// _mps_OE_H_
