/****************************************************************************
  This file is part of Space Shuttle Vessel

  Computer Interface Electronics definition


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
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Computer Interface Electronics definition



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
#ifndef _mps_CIE_H_
#define _mps_CIE_H_


#include <Orbitersdk.h>


namespace mps
{
	// must be the same values as in SW

	inline constexpr unsigned short DIO_DEV_INPUT = 0x0000;// 0xxx xxxx xxxx xxxx
	inline constexpr unsigned short DIO_DEV_OUTPUT = 0x8000;// 1xxx xxxx xxxx xxxx

	inline constexpr unsigned short DIO_DEV_OEchA = 0x0000;// x000 xxxx xxxx xxxx
	inline constexpr unsigned short DIO_DEV_OEchB = 0x1000;// x001 xxxx xxxx xxxx
	inline constexpr unsigned short DIO_DEV_VIE = 0x2000;// x010 xxxx xxxx xxxx

	inline constexpr unsigned short DIO_DEV_OE_STORAGE_REG = 0x0000;// xxxx 0000 xxxx xxxx
	inline constexpr unsigned short DIO_DEV_OE_ONOFF_REG_1 = 0x0100;// xxxx 0001 xxxx xxxx
	inline constexpr unsigned short DIO_DEV_OE_ONOFF_REG_2 = 0x0200;// xxxx 0010 xxxx xxxx

	inline constexpr unsigned short DIO_DEV_VIE_CMD1 = 0x0000;// xxxx 0000 xxxx xxxx
	inline constexpr unsigned short DIO_DEV_VIE_CMD2 = 0x0100;// xxxx 0001 xxxx xxxx
	inline constexpr unsigned short DIO_DEV_VIE_CMD3 = 0x0200;// xxxx 0010 xxxx xxxx


	class PowerSupplyElectronics;
	class DigitalComputerUnit;
	class VehicleInterfaceElectronics;
	class InputElectronics;
	class OutputElectronics;
	class SSMEController;


	class ComputerInterfaceElectronics
	{
		protected:
			int ch;
			PowerSupplyElectronics* PSE;
			DigitalComputerUnit* DCU;
			VehicleInterfaceElectronics* VIE;
			InputElectronics* IE[2];
			OutputElectronics* OE[2];
			ComputerInterfaceElectronics* CIEOpposite;
			SSMEController* Controller;

			double dWDT[2];
			bool bWDT[2];// timed out

			double time;
			double dt;

		public:
			ComputerInterfaceElectronics( int ch, SSMEController* Controller );
			virtual ~ComputerInterfaceElectronics( void );

			virtual void OnSaveState( FILEHANDLE scn ) const;
			virtual bool OnParseLine( const char* line );

			void Realize( void );

			void tmestp( double time, double dt );

			void DMA_ch1( unsigned short readaddress, unsigned short readlength );
			void DMA_ch2( unsigned short readaddress, unsigned short readlength );
			void DMA_ch3( unsigned short selectcontrol, unsigned short writeaddress, unsigned short writelength );

			unsigned short DIO( unsigned short control, unsigned short data );

			void InitializeWDT( int nWDT );
			void ResetWDT( int nWDT );
			bool CheckWDTOwn( int nWDT );
			bool CheckWDTOpposite( int nWDT );

			void Interrupt( int num );

			void PowerBusDown( void );

			void SwitchVRC( void );
			void RestoreVRC( void );
	};

}


#endif// _mps_CIE_H_
