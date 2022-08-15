/****************************************************************************
  This file is part of Space Shuttle Vessel

  Digital Computer Unit Block II definition


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

  Digital Computer Unit Block II definition



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
#ifndef _mps_DCU_BLOCK_II_H_
#define _mps_DCU_BLOCK_II_H_


#include "DigitalComputerUnit.h"


namespace mps
{
	inline constexpr int RAMSIZE_DCU_BII = 65536;


	// Self-Test Status
	inline constexpr unsigned short ESW_EngineOK = 1;
	inline constexpr unsigned short ESW_MCF = 2;

	// Phase/Mode
	inline constexpr unsigned short ESW_PROM = 0x0700;
	inline constexpr unsigned short ESW_Standby = 0x0800;

	// Command Status
	inline constexpr unsigned short ESW_NoCommand = 0x0000;
	inline constexpr unsigned short ESW_CommandRejected_A = 0x0002;
	inline constexpr unsigned short ESW_CommandRejected_B = 0x0004;
	inline constexpr unsigned short ESW_Accepted = 0x0006;


	inline constexpr int RAM_PROM_BII_CH = 0;
	inline constexpr int RAM_PROM_BII_TREF = 1;

	inline constexpr int RAM_PROM_BII_ESW = 3;

	inline constexpr int RAM_PROM_BII_VALIDCMD = 5;
	inline constexpr int RAM_PROM_BII_CMD1 = 6;
	inline constexpr int RAM_PROM_BII_CMD2 = 7;
	inline constexpr int RAM_PROM_BII_CMD3 = 8;

	inline constexpr int RAM_PROM_BII_CURCMD = 9;
	inline constexpr int RAM_PROM_BII_PRVCMD = 10;

	inline constexpr int RAM_PROM_BII_DVDT_1 = 21;
	inline constexpr int RAM_PROM_BII_DVDT_2 = 22;
	inline constexpr int RAM_PROM_BII_DVDT_3 = 23;
	inline constexpr int RAM_PROM_BII_DVDT_5 = 25;
	inline constexpr int RAM_PROM_BII_DVDT_90 = 110;
	inline constexpr int RAM_PROM_BII_DVDT_98 = 118;
	inline constexpr int RAM_PROM_BII_DVDT_99 = 119;
	inline constexpr int RAM_PROM_BII_DVDT_100 = 120;
	inline constexpr int RAM_PROM_BII_DVDT_103 = 123;

	// commands
	inline constexpr unsigned short NOP = 0x0000;
	inline constexpr unsigned short SDCA = 0x0400;
	inline constexpr unsigned short SDCB = 0x0800;
	inline constexpr unsigned short EGND = 0x0C00;
	inline constexpr unsigned short EFLT = 0x1000;
	inline constexpr unsigned short EFRT = 0x1400;
	inline constexpr unsigned short ETWO = 0x1800;
	inline constexpr unsigned short RVRC = 0x1C00;
	inline constexpr unsigned short SVRC = 0x2000;
	inline constexpr unsigned short AFRT = 0x2400;
	inline constexpr unsigned short XFRT = 0x2800;
	inline constexpr unsigned short HYDC = 0x2C00;
	inline constexpr unsigned short ERCK = 0x3000;
	inline constexpr unsigned short RSYS = 0x3400;
	inline constexpr unsigned short RESM = 0x3800;
	inline constexpr unsigned short RSCT = 0x3C00;
	inline constexpr unsigned short MLDA = 0x4000;
	inline constexpr unsigned short MLDB = 0x4400;
	inline constexpr unsigned short RSCA = 0x4800;
	inline constexpr unsigned short RSCB = 0x4C00;
	inline constexpr unsigned short HELA = 0x5000;
	inline constexpr unsigned short HELB = 0x5400;
	inline constexpr unsigned short PSCA = 0x5800;
	inline constexpr unsigned short PSCB = 0x5C00;
	inline constexpr unsigned short IOHA = 0x6000;
	inline constexpr unsigned short IOHB = 0x6400;
	inline constexpr unsigned short IOLA = 0x6800;
	inline constexpr unsigned short IOLB = 0x6C00;
	inline constexpr unsigned short IOSA = 0x7000;
	inline constexpr unsigned short IOSB = 0x7400;
	inline constexpr unsigned short ENFA = 0x7800;
	inline constexpr unsigned short ENFB = 0x7C00;
	inline constexpr unsigned short ROFA = 0x8000;
	inline constexpr unsigned short ROFB = 0x8400;
	inline constexpr unsigned short RWRA = 0x8800;
	inline constexpr unsigned short RWRB = 0x8C00;
	inline constexpr unsigned short RSKA = 0x9000;
	inline constexpr unsigned short RSKB = 0x9400;
	inline constexpr unsigned short EXPM = 0x9800;
	inline constexpr unsigned short MRC1 = 0x9C00;
	inline constexpr unsigned short MRC2 = 0xA000;
	inline constexpr unsigned short LOXD = 0xA400;
	inline constexpr unsigned short APOW = 0xA800;
	inline constexpr unsigned short XPOW = 0xAC00;
	inline constexpr unsigned short PSN1 = 0xB000;
	inline constexpr unsigned short PSN2 = 0xB400;
	inline constexpr unsigned short PSN3 = 0xB800;
	inline constexpr unsigned short PSN4 = 0xBC00;
	inline constexpr unsigned short STEN = 0xC000;
	inline constexpr unsigned short IGNT = 0xC400;
	inline constexpr unsigned short SDEN = 0xC800;
	inline constexpr unsigned short STDN = 0xCC00;
	inline constexpr unsigned short TMSQ = 0xD000;
	inline constexpr unsigned short THRT = 0xD400;
	inline constexpr unsigned short COSY = 0xD800;
	inline constexpr unsigned short DAVL = 0xDC00;
	inline constexpr unsigned short ENLS = 0xE000;
	inline constexpr unsigned short INLS = 0xE400;
	inline constexpr unsigned short INFA = 0xE800;
	inline constexpr unsigned short INFB = 0xEC00;


	class DigitalComputerUnit_BLOCK_II:public DigitalComputerUnit
	{
		private:
			void PROM( void ) override;
		public:
			DigitalComputerUnit_BLOCK_II( int ch, const std::string& sw, SSMEController* Controller );
			~DigitalComputerUnit_BLOCK_II( void );

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;

			void tmestp( double time, double tmestp ) override;
	};
}


#endif// _mps_DCU_BLOCK_II_H_
