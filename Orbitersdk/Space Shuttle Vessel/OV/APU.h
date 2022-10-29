/****************************************************************************
  This file is part of Space Shuttle Vessel

  APU subsystem definition


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
2021/06/06   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/07/24   GLS
2022/09/29   GLS
2022/10/09   GLS
2022/10/21   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  APU simulation definition



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
#ifndef __APU_H
#define __APU_H


#include "AtlantisSubsystem.h"
#include <DiscInPort.h>
#include <DiscOutPort.h>
#include <Sensor.h>


inline constexpr double APU_FUEL_TANK_MASS = 350.0;
// Max APU Fuel tank mass [lbm]
inline constexpr double APU_FUEL_TANK_FLOWRATE[2] = {3.25/60.0, 1.5/60.0};
// APU fuel consumption rate(lbm/sec)

using namespace discsignals;


class APU: public AtlantisSubsystem
{
public:
	APU(AtlantisSubsystemDirector* _director, const string& _ident, int _ID);
	~APU();

	//functions for CRT MFD APU/HYD display
	virtual double GetHydraulicPressure() const;
	virtual double GetFuelLevel() const;
	virtual double GetAPUSpeed() const;
	bool SingleParamParseLine() const override {return true;};
	double GetSubsystemMass() const override;
	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPostStep(double simt, double simdt, double mjd) override;
	void OnPropagate(double simt, double simdt, double mjd) override;

	void OnSaveState(FILEHANDLE scn) const override;
	bool OnParseLine(const char* line) override;

	typedef enum {OFF, START, ON, SHUTDOWN} APU_STATE;
private:
	bool ReadyToStart() const;

	int ID;

	double FuelMass[2];
	double HydraulicPressure[2];
	double FuelPress[2];
	double APUSpeed[2];

	APU_STATE State;

	DiscInPort APU_Run, APU_HydPumpPress;
	DiscInPort APU_CntlrPwr, APU_FuelTankValves;
	DiscInPort WSB_Ready;
	DiscOutPort APU_HydraulicPress;
	DiscOutPort APU_ReadyToStart;

	Sensor FuTkPress;
	Sensor HYD_MN_PMP_P[3];// A, B, C
};

#endif //__APU_H
