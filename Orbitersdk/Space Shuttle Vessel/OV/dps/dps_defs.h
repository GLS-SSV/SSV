/****************************************************************************
  This file is part of Space Shuttle Vessel

  Data Processing System definitions



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
2020/06/12   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Data Processing System definitions



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
#pragma once

inline constexpr char SSV_KEY_FAULTSUMM = 1;
inline constexpr char SSV_KEY_SYSSUMM = 2;
inline constexpr char SSV_KEY_MSGRESET = 3;
inline constexpr char SSV_KEY_ACK = 4;
inline constexpr char SSV_KEY_GPCCRT = 5;
inline constexpr char SSV_KEY_A = 6;
inline constexpr char SSV_KEY_B = 7;
inline constexpr char SSV_KEY_C = 8;
inline constexpr char SSV_KEY_IORESET = 9;
inline constexpr char SSV_KEY_D = 10;
inline constexpr char SSV_KEY_E = 11;
inline constexpr char SSV_KEY_F = 12;
inline constexpr char SSV_KEY_ITEM = 13;
inline constexpr char SSV_KEY_1 = 14;
inline constexpr char SSV_KEY_2 = 15;
inline constexpr char SSV_KEY_3 = 16;
inline constexpr char SSV_KEY_EXEC = 17;
inline constexpr char SSV_KEY_4 = 18;
inline constexpr char SSV_KEY_5 = 19;
inline constexpr char SSV_KEY_6 = 20;
inline constexpr char SSV_KEY_OPS = 21;
inline constexpr char SSV_KEY_7 = 22;
inline constexpr char SSV_KEY_8 = 23;
inline constexpr char SSV_KEY_9 = 24;
inline constexpr char SSV_KEY_SPEC = 25;
inline constexpr char SSV_KEY_MINUS = 26;
inline constexpr char SSV_KEY_0 = 27;
inline constexpr char SSV_KEY_PLUS = 28;
inline constexpr char SSV_KEY_RESUME = 29;
inline constexpr char SSV_KEY_CLEAR = 30;
inline constexpr char SSV_KEY_DOT = 31;
inline constexpr char SSV_KEY_PRO = 32;


namespace dps
{
	typedef enum {
		GNC = 0,
		SM = 1,
		PL = 2
	} MAJORFUNCTION;

	struct DEUCHAR {
		unsigned char cSymbol;
		char cAttr;
	};

	struct DEU_LINE {
		int x0, y0;
		int x1, y1;
		char cAttr;
	};

	struct DEU_ELLIPSE {
		int xLeft, yTop, xRight, yBottom;
		char cAttr;
	};

	struct DEU_PIXEL
	{
		int x, y;
		char cAttr;
	};


	/**
	 * @brief IRIG-B compatible time frame
	 *
	 * Format used for transmitting GMT and MET over serial lines in
	 * the shuttle. One such frame requires 1 second to be transmitted,
	 * so millisecond timing comes from other time sources, such as the
	 * pulses used for transmitting this frame.
	 * It takes half a second to send to actual time in 5 pulse coded bytes
	 * The other 5 bytes of the time are not used but get transmitted anyway.
	 */
	struct IRIGB_FRAME {
		unsigned int uSeconds:7;
		unsigned int uMinutes:7;
		unsigned int uHours:6;
		unsigned int uDays:9;
		unsigned char uP5:8;
		unsigned char uP6:8;
		unsigned char uP7:8;
		unsigned char uP8:8;
		unsigned char uP9:8;
	};


	struct SIMPLEBUS_COMMAND_WORD
	{
		unsigned int sync:3;
		unsigned int MIAaddr:5;
		unsigned int payload:14;
		unsigned int numwords:5;
		unsigned int parity:1;
	};

	struct SIMPLEBUS_COMMANDDATA_WORD
	{
		unsigned int sync:3;
		unsigned int MIAaddr:5;
		unsigned int payload:16;
		unsigned int SEV:3;
		unsigned int parity:1;
	};
};
