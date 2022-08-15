/****************************************************************************
  This file is part of Space Shuttle Vessel

  Digital Computer Unit subsystem definition


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
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Digital Computer Unit definition



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
#ifndef _mps_DCU_H_
#define _mps_DCU_H_


#include <string>
#include <Orbitersdk.h>


namespace mps
{
	// interrupts (BLOCK I): 17 external (+2?) (12 SV failure)
	inline constexpr int INT_PFI = 1;// power failure
	inline constexpr int INT_PRI = 2;// power recovery
	inline constexpr int INT_PBDI = 3;// power bus down (opposite)
	inline constexpr int INT_CCVSVAFI = 4;// CCV SV chA failure
	inline constexpr int INT_CCVSVBFI = 5;// CCV SV chB failure
	inline constexpr int INT_MFVSVAFI = 6;// MFV SV chA failure
	inline constexpr int INT_MFVSVBFI = 7;// MFV SV chB failure
	inline constexpr int INT_MOVSVAFI = 8;// MOV SV chA failure
	inline constexpr int INT_MOVSVBFI = 9;// MOV SV chB failure
	inline constexpr int INT_FPOVSVAFI = 10;// FPOV SV chA failure
	inline constexpr int INT_FPOVSVBFI = 11;// FPOV SV chB failure
	inline constexpr int INT_OPOVSVAFI = 12;// OPOV SV chA failure
	inline constexpr int INT_OPOVSVBFI = 13;// OPOV SV chB failure
	inline constexpr int INT_CMD_RCVD = 14;// command received


	class SSMEController;
	class PowerSupplyElectronics;

	class DigitalComputerUnit
	{
		friend class ComputerInterfaceElectronics;
		friend class SSMEControllerSW;
		friend class SSMEControllerSW_AD08;

		protected:
			int ch;
			int ramsize;
			PowerSupplyElectronics* PSE;
			ComputerInterfaceElectronics* CIE;
			SSMEController* Controller;
			SSMEControllerSW* sw;
			unsigned short* RAM;

			double time;
			double dt;

			void (SSMEControllerSW::*funct)( void );

			virtual void PROM( void ) = 0;
		public:
			DigitalComputerUnit( int ch, int ramsize, const std::string& sw, SSMEController* Controller );
			virtual ~DigitalComputerUnit( void );

			virtual void OnSaveState( FILEHANDLE scn ) const;
			virtual bool OnParseLine( const char* line );

			void Realize( void );

			virtual void tmestp( double time, double tmestp ) = 0;

			unsigned short DIO_in( unsigned short device );
			void DIO_out( unsigned short device, unsigned short data );

			void DMA_write( unsigned short selectcontrol, unsigned short writeaddress, unsigned short writelength );
			void DMA_read( unsigned short selectcontrol, unsigned short readaddress, unsigned short readlength );

			void PowerFailureSense( void );
			void Interrupt( int num );
	};
}


#endif// _mps_DCU_H_
