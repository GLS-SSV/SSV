/****************************************************************************
  This file is part of Space Shuttle Vessel

  Space Shuttle Main Engine Controller Software definition


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
2020/06/20   GLS
2021/07/03   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Space Shuttle Main Engine Controller Software definition



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
#ifndef _mps_SSMECONTROLLERSW_H_
#define _mps_SSMECONTROLLERSW_H_


namespace mps
{
	// must be the same values as in CIE
	// out
	inline constexpr unsigned short DEV_CIE_OEchA = 0x0000;// 0000 0000 0000 0000
	inline constexpr unsigned short DEV_CIE_OEchB = 0x1000;// 0001 0000 0000 0000

	// oe out
	inline constexpr unsigned short DEV_OE_ON_OFF_1 = 0x0001;// 0000 0000 0000 0001
	inline constexpr unsigned short DEV_OE_ON_OFF_2 = 0x0002;// 0000 0000 0000 0010
	inline constexpr unsigned short DEV_OE_CCV = 0x0003;// 0000 0000 0000 0011
	inline constexpr unsigned short DEV_OE_MFV = 0x0004;// 0000 0000 0000 0100
	inline constexpr unsigned short DEV_OE_MOV = 0x0005;// 0000 0000 0000 0101
	inline constexpr unsigned short DEV_OE_FPOV = 0x0006;// 0000 0000 0000 0110
	inline constexpr unsigned short DEV_OE_OPOV = 0x0007;// 0000 0000 0000 0111

	// in
	inline constexpr unsigned short DEV_CIE_VIE_CMD1 = 0x2000;// 0010 0000 0000 0000
	inline constexpr unsigned short DEV_CIE_VIE_CMD2 = 0x2100;// 0010 0001 0000 0000
	inline constexpr unsigned short DEV_CIE_VIE_CMD3 = 0x2200;// 0010 0010 0000 0000

	// oe in
	inline constexpr unsigned short DEV_CIE_OE_STORAGE_REG = 0x0000;
	inline constexpr unsigned short DEV_CIE_ONOFF_REG_1 = 0x0100;
	inline constexpr unsigned short DEV_CIE_ONOFF_REG_2 = 0x0200;


	class DigitalComputerUnit;

	class SSMEControllerSW
	{
		protected:
			DigitalComputerUnit* DCU;
		public:
			SSMEControllerSW( DigitalComputerUnit* DCU );
			virtual ~SSMEControllerSW( void );

			virtual int GetConfig( void ) = 0;
			virtual void SetConfig( int config ) = 0;

			virtual void Executive( void ) = 0;

			virtual void Interrupt( int num ) = 0;
	};
}


#endif// _mps_SSMECONTROLLERSW_H_
