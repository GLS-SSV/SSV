/****************************************************************************
  This file is part of Space Shuttle Vessel

  Launch Control Center vessel definition


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
2020/05/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/28   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/

#ifndef __SSVLCC_H
#define __SSVLCC_H


#include <Orbitersdk.h>
#include "../PadLCCInterface.h"


class LCCPadInterface;


class LCC: public VESSEL4, public PadLCCInterface
{
	friend class LCC_MFD;
public:
	LCC(OBJHANDLE hVessel, int flightmodel);
	~LCC();

	void clbkPostCreation() override;
	void clbkPreStep(double simt, double simdt, double mjd) override;
	void clbkSaveState(FILEHANDLE scn) override;
	void clbkLoadStateEx(FILEHANDLE scn, void *status) override;

private:
	double launch_mjd;// GMTLO
	double CountdownTime;
	double lastCT;

	bool clockholding;// use LPSCountdownHold for this?
	bool requestautohold;
	bool resumecmd;
	bool resuming;
	double resumetimer;
	bool cutoff;
	bool safingcomplete;
	bool liftoff;
	double cutofftimer;
	bool OAAemergencyextend;
	bool Firexactivated;
	bool hold0730;
	bool hold0500;
	bool hold0400;
	bool hold0255;
	bool hold0157;
	bool hold0031;

	bool LPSCountdownHold;

	double MPSHeSupplyPressure1;
	double MPSHeSupplyPressure2;
	bool _firstrun;
	bool MPSHeSupply;
	bool MPSTVCProfile;

	char PadName[256];

	LCCPadInterface* pPad;

	int mfdID;

	std::string strMission;

	void Checks( void );
	void Commands( void );

	void IssueCutoff( void );
};

#endif //__SSVLCC_H
