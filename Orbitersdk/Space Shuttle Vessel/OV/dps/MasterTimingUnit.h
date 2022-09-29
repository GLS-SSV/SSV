/****************************************************************************
  This file is part of Space Shuttle Vessel

  Master Timing Unit subsystem definition


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
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Master Timing Unit subsystem definition



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
#if !defined(AFX_MASTERTIMINGUNIT_H__FEF22983_033D_412B_B3A9_876EE3A3EC04__INCLUDED_)
#define AFX_MASTERTIMINGUNIT_H__FEF22983_033D_412B_B3A9_876EE3A3EC04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dps_defs.h"
#include "../AtlantisSubsystem.h"

namespace dps {

typedef short MTU_ACCU_INDEX;


class TimePort {
	unsigned short usPulseCount;
	unsigned short usPulsesPerTimeStep;
	IRIGB_FRAME fdat;
public:
	TimePort();
	unsigned short GetDay() const;
	unsigned short GetHours() const;
	unsigned short GetMinutes() const;
	unsigned short GetSeconds() const;
};


class MasterTimingUnit : public AtlantisSubsystem
{
	double fGMT[3][2];
	double fMET[3][2];

	short sGMTMillis[3];
	short sGMTSeconds[3];
	short sGMTMinutes[3];
	short sGMTHours[3];
	short sGMTDays[3];

	short sMETMillis[3];
	short sMETSeconds[3];
	short sMETMinutes[3];
	short sMETHours[3];
	short sMETDays[3];

	bool bMETCounting[2];
public:
	explicit MasterTimingUnit(AtlantisSubsystemDirector* _director);
	virtual ~MasterTimingUnit();

	short GetMETMilli(MTU_ACCU_INDEX accu_index) const;
	short GetMETSec(MTU_ACCU_INDEX accu_index) const;
	short GetMETMin(MTU_ACCU_INDEX accu_index) const;
	short GetMETHour(MTU_ACCU_INDEX accu_index) const;
	short GetMETDay(MTU_ACCU_INDEX accu_index) const;

	void ResetMET();
	void StartMET();

	short GetGMTMilli(MTU_ACCU_INDEX accu_index) const;
	short GetGMTSec(MTU_ACCU_INDEX accu_index) const;
	short GetGMTMin(MTU_ACCU_INDEX accu_index) const;
	short GetGMTHour(MTU_ACCU_INDEX accu_index) const;
	short GetGMTDay(MTU_ACCU_INDEX accu_index) const;

	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPropagate(double simt, double simdt, double mjd) override;
	void Realize( void ) override;
	void OnSaveState(FILEHANDLE scn) const override;
	bool OnParseLine(const char* keyword, const char* line) override;

};


class TimeBus {
public:
	TimeBus(MasterTimingUnit* pMTU, TimePort* pTarget);
};

};

#endif // !defined(AFX_MASTERTIMINGUNIT_H__FEF22983_033D_412B_B3A9_876EE3A3EC04__INCLUDED_)
