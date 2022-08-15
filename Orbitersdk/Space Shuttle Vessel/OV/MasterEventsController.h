/****************************************************************************
  This file is part of Space Shuttle Vessel

  Master Events Controller subsystem definition


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
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Master Events Controller definition



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
#ifndef __MEC_H_
#define __MEC_H_


#include "AtlantisSubsystem.h"
#include <DiscInPort.h>


// MEC critical commands
inline constexpr unsigned short MEC_CR_SRB_IGNITION_ARM = 0x3EAC;
inline constexpr unsigned short MEC_CR_SRB_IGNITION_FIRE_1 = 0x3E6A;
inline constexpr unsigned short MEC_CR_SRB_IGNITION_FIRE_2 = 0x3E42;
inline constexpr unsigned short MEC_CR_SRB_SEP_ARM = 0x3154;
inline constexpr unsigned short MEC_CR_SRB_SEP_FIRE_1 = 0x316A;
inline constexpr unsigned short MEC_CR_SRB_SEP_FIRE_2 = 0x319B;
inline constexpr unsigned short MEC_CR_ETORB_STRUCT_SEP_ARM = 0xE117;
inline constexpr unsigned short MEC_CR_ETORB_STRUCT_SEP_FIRE_1 = 0xE168;
inline constexpr unsigned short MEC_CR_ETORB_STRUCT_SEP_FIRE_2 = 0xE199;
inline constexpr unsigned short MEC_CR_T0_UMB_RELEASE_ARM = 0xCEDC;
inline constexpr unsigned short MEC_CR_T0_UMB_RELEASE_FIRE_1 = 0xCE6A;
inline constexpr unsigned short MEC_CR_T0_UMB_RELEASE_FIRE_2 = 0xCE9A;

// MEC non-critical commands
// ....

// CR buffer index
inline constexpr int SRB_IGNITION_ARM = 0;
inline constexpr int SRB_IGNITION_FIRE_1 = 1;
inline constexpr int SRB_IGNITION_FIRE_2 = 2;
inline constexpr int SRB_SEP_ARM = 3;
inline constexpr int SRB_SEP_FIRE_1 = 4;
inline constexpr int SRB_SEP_FIRE_2 = 5;
inline constexpr int ETORB_STRUCT_SEP_ARM = 6;
inline constexpr int ETORB_STRUCT_SEP_FIRE_1 = 7;
inline constexpr int ETORB_STRUCT_SEP_FIRE_2 = 8;
inline constexpr int T0_UMB_RELEASE_ARM = 9;
inline constexpr int T0_UMB_RELEASE_FIRE_1 = 10;
inline constexpr int T0_UMB_RELEASE_FIRE_2 = 11;
inline constexpr int CRsize = 12;


using namespace discsignals;


class MasterEventsController:public AtlantisSubsystem
{
	private:
		static bool PIC_SRM_IGNITION;// and also HDP, ETVAS and ETVAS lanyard
		static bool PIC_T0_UMB;
		static bool PIC_SRB_SEP;
		static bool PIC_ET_SEP;

		short ID;
		DiscInPort power;

		bool CR[CRsize];

	public:
		MasterEventsController( AtlantisSubsystemDirector* _director, const string& _ident, short nID );
		~MasterEventsController( void );

		bool SingleParamParseLine() const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		void Realize( void ) override;
		void OnPreStep( double simt, double simdt, double mjd ) override;

		void SetCriticalCmd( unsigned short cmd );
		void MasterResetCmd( void );
};


#endif// __MEC_H_