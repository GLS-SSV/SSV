/****************************************************************************
  This file is part of Space Shuttle Vessel

  Water Spray Boiler subsystem definition


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
2021/06/06   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Water Spray Boiler simulation definition



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
#ifndef _WSB_H_
#define _WSB_H_


#include "AtlantisSubsystem.h"
#include <discsignals.h>


using namespace discsignals;

/**
 * Simulates Water Spray Boiler used to cool APUs and hyd fluid
 * At the moment, all it does is check WSB ready for APU talkbacks
 * TODO: accurately calculate boiloff rate
 * TODO: propulsive force when venting steam
 */
class WSB : public AtlantisSubsystem
{
	unsigned short usID; // from 1 to 3

	double waterMass[2];

	// indicates controller selected and if controller is powered
	DiscInPort Power, ControllerPwr, ControllerA, ControllerB;
	DiscInPort BoilerN2Supply;
	DiscOutPort Ready;
public:
	WSB(AtlantisSubsystemDirector* _director, const string& _ident, unsigned short _ID);
	virtual ~WSB();

	void Realize() override;

	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPostStep(double simt, double simdt, double mjd) override;
	void OnPropagate(double simt, double simdt, double mjd) override;

	void OnSaveState(FILEHANDLE scn) const override;
	bool OnParseLine(const char* keyword, const char* line) override;
};

#endif// _WSB_H_
