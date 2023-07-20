/****************************************************************************
  This file is part of Space Shuttle Vessel

  Helium System definition


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
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Helium System definition



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
#ifndef _mps_HESYS_H_
#define _mps_HESYS_H_


#include <PressureSource.h>
#include "../AtlantisSubsystem.h"
#include <Sensor.h>


class SolenoidValve;


namespace mps
{
	using discsignals::DiscreteBundle;
	class HeSysPneu;


	class HeSysEng:public AtlantisSubsystem, public PressureSource
	{
		// 2 4.7cf
		// 1 17.3cf
		private:
			int ID;
			HeSysEng* sys1;// not system 1, but one of the other 2 systems
			HeSysEng* sys2;// not system 2, but one of the other 2 systems
			HeSysPneu* sysP;// pneumatic system

			SolenoidValve* vlvISOL_A;// LV1 / LV3 / LV5
			SolenoidValve* vlvISOL_B;// LV2 / LV4 / LV6

			SolenoidValve* vlvInIC;// LV59 / LV61 / LV63
			SolenoidValve* vlvOutIC;// LV60 / LV62 / LV64

			double HeMass;// g
			double TankPress;// psia
			double TankTemp;// K
			double RegPress;// TODO one sensor per reg
			double TotalFlow;

			Sensor TankPressure;
			Sensor RegPressure[2];
		public:
			HeSysEng( AtlantisSubsystemDirector* _director, const string& _ident, int ID );
			~HeSysEng( void );

			void Realize( void ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool SingleParamParseLine() const override {return true;};

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;

			double Use( double flow, int source ) override;// flow g/s
			double UseTank( double mass );
			double FillTank( double mass );

			int GetTankPress( void ) const;
			int GetRegPress( void ) const;
			double IsOutICOpen( void ) const;
	};


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////


	class HeSysPneu:public AtlantisSubsystem, public PressureSource
	{
		friend class HeSysEng;
		// 1 4.7cf
		private:
			HeSysEng* sys1;// system 1
			HeSysEng* sys2;// system 2
			HeSysEng* sys3;// system 3

			SolenoidValve* vlvISOL_A;// LV7
			SolenoidValve* vlvISOL_B;// LV8

			SolenoidValve* vlvLEngXOVR;// LV10

			double HeMass;// g
			double TankPress;// psia
			double TankTemp;// K
			double RegPress;
			double TotalFlow;

			Sensor TankPressure;
			Sensor RegPressure;
		public:
			HeSysPneu( AtlantisSubsystemDirector* _director, const string& _ident );
			~HeSysPneu( void );

			void Realize( void ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool SingleParamParseLine() const override {return true;};

			void OnSaveState( FILEHANDLE scn ) const override;
			bool OnParseLine( const char* line ) override;

			double Use( double flow, int source ) override;// flow g/s
			double UseTank( double mass );
			double FillTank( double mass );

			int GetTankPress( void ) const;
			int GetRegPress( void ) const;
	};
}

#endif // _mps_HESYS_H_