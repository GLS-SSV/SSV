/****************************************************************************
  This file is part of Space Shuttle Vessel

  Output Electronics Block II definition


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
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Output Electronics Block II definition



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
#ifndef _mps_OE_BLOCK_II_H_
#define _mps_OE_BLOCK_II_H_


#include "OutputElectronics.h"


namespace mps
{
	// command decoder
	inline constexpr unsigned short CD_ONOFF_1 = 0x0001;
	inline constexpr unsigned short CD_ONOFF_2 = 0x0002;
	inline constexpr unsigned short CD_CCV = 0x0003;
	inline constexpr unsigned short CD_MFV = 0x0004;
	inline constexpr unsigned short CD_MOV = 0x0005;
	inline constexpr unsigned short CD_FPOV = 0x0006;
	inline constexpr unsigned short CD_OPOV = 0x0007;

	// ON/OFF 1
	inline constexpr unsigned short SV_HPOTPISPURGE = 0x0010;
	inline constexpr unsigned short SV_EMERGENCYSHUTDOWN = 0x0020;
	inline constexpr unsigned short SV_SHUTDOWNPURGE = 0x0040;
	inline constexpr unsigned short SV_FUELSYSTEMPURGE = 0x0100;
	inline constexpr unsigned short SV_BLEEDVALVESCONTROL = 0x0200;
	inline constexpr unsigned short AFV = 0x0400;
	inline constexpr unsigned short HPV = 0x0800;
	inline constexpr unsigned short IGNITER_MCC = 0x2000;
	inline constexpr unsigned short IGNITER_OPB = 0x4000;
	inline constexpr unsigned short IGNITER_FPB = 0x8000;

	// ON/OFF 2
	inline constexpr unsigned short SS_CCV_FO = 0x0010;
	inline constexpr unsigned short SS_MFV_FO = 0x0020;
	inline constexpr unsigned short SS_MOV_FO = 0x0040;
	inline constexpr unsigned short SS_FPOV_FO = 0x0080;
	inline constexpr unsigned short SS_OPOV_FO = 0x0100;
	inline constexpr unsigned short SS_CCV_FS = 0x0200;
	inline constexpr unsigned short SS_MFV_FS = 0x0400;
	inline constexpr unsigned short SS_MOV_FS = 0x0800;
	inline constexpr unsigned short SS_FPOV_FS = 0x1000;
	inline constexpr unsigned short SS_OPOV_FS = 0x2000;


	class SSME;
	class SSMEController;


	class OutputElectronics_BLOCK_II:public OutputElectronics
	{
		public:
			OutputElectronics_BLOCK_II( int ch, SSME* eng, SSMEController* Controller );
			~OutputElectronics_BLOCK_II( void );

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;

			void tmestp( double time, double tmestp ) override;

			void StorageRegister_write( unsigned short data, int ch ) override;
			unsigned short StorageRegister_read( void ) const override;
			unsigned short ONOFFCommandRegister_read( int num ) const override;
			void CommandDecoder( void ) override;

			void GetSH( double* data ) override;
			void GetPOS( double* data ) override;
	};
}


#endif// _mps_OE_BLOCK_II_H_
