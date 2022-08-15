/****************************************************************************
  This file is part of Space Shuttle Vessel

  PRSD subsystem definition


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
2020/06/28   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/10/06   GLS
2020/10/07   GLS
2021/06/06   GLS
2021/06/28   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/05   GLS
2021/12/23   GLS
2021/12/26   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/02/16   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  PRSD definition



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

#ifndef _eps_PRSD_H_
#define _eps_PRSD_H_


#include "..\AtlantisSubsystem.h"
#include <discsignals.h>
#include <PressureSource.h>
#include <ValveManager.h>
#include <Sensor.h>


class SolenoidLatchingValve;


using namespace discsignals;


namespace eps
{
	class PRSD:public AtlantisSubsystem, public PressureSource
	{
		private:
			unsigned short sets;
			vector<double> O2mass;// g
			vector<double> O2press;// Pa
			vector<double> O2temp;// K
			vector<double> H2mass;// g
			vector<double> H2press;// Pa
			vector<double> H2temp;// K

			unsigned short pallet;
			bool EDOhw;

			ValveManager vman;

			SolenoidLatchingValve* O2Manif[2];
			SolenoidLatchingValve* H2Manif[2];

			SolenoidLatchingValve* FCO2Reac[3];
			SolenoidLatchingValve* FCH2Reac[3];

			SolenoidLatchingValve* O2ECLSSSupply[2];

			vector<Sensor> O2TKqty;
			vector<Sensor> O2TKpress;
			vector<Sensor> O2TKtemp;
			vector<Sensor> O2TKhtrcntrpress;
			vector<Sensor> O2TKhtrassytemp1;
			vector<Sensor> O2TKhtrassytemp2;
			vector<Sensor> H2TKqty;
			vector<Sensor> H2TKpress;
			vector<Sensor> H2TKtemp;
			vector<Sensor> H2TKhtrcntrpress;
			vector<Sensor> H2TKhtrassytemp;

			Sensor* O2ManifPress[2];
			Sensor* H2ManifPress[2];

			vector<DiscInPort> O2HeatersA_On;
			vector<DiscInPort> O2HeatersA_Auto;
			vector<DiscInPort> O2HeatersB_On;
			vector<DiscInPort> O2HeatersB_Auto;
			vector<DiscInPort> O2Heaters_Test;
			vector<DiscInPort> O2Heaters_Reset;
			vector<DiscInPort> H2HeatersA_On;
			vector<DiscInPort> H2HeatersA_Auto;
			vector<DiscInPort> H2HeatersB_On;
			vector<DiscInPort> H2HeatersB_Auto;


			MESHHANDLE hEDOPalletMesh;
			UINT mesh_EDOPallet;

			void AddMesh( void );

		public:
			PRSD( unsigned short internalsets, bool EDOhw, unsigned short pallet, AtlantisSubsystemDirector* _director );
			virtual ~PRSD();

			void Realize( void ) override;
			void OnPreStep( double simt, double simdt, double mjd ) override;

			bool SingleParamParseLine() const override {return true;};
			bool OnParseLine( const char* line ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			double GetSubsystemMass() const override;

			double Use( double flow, int source ) override;

			void GetPLBInfo( unsigned short& PLID, bool& Reversed, unsigned short& pallet ) const;
	};

};

#endif// _eps_PRSD_H_
