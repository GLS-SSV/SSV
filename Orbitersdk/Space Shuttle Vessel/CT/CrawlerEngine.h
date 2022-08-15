/****************************************************************************
  This file is part of Space Shuttle Vessel

  CrawlerEngine definition


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
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/14   GLS
2020/06/20   GLS
2021/06/01   GLS
2021/06/06   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/08/05   GLS
********************************************/

#ifndef __CRAWLERENGINE_H_F05A8448_9C86_481c_B632_0641CA218CF0
#define __CRAWLERENGINE_H_F05A8448_9C86_481c_B632_0641CA218CF0
#pragma once

#include <Orbitersdk.h>
#include <Subsystem.h>
#include <DiscreteBundle.h>
#include <DiscInPort.h>
#include <DiscOutPort.h>

//const double MAX_POWER = 4000.0e3;
// total power (Watts) of all 4 generators

using namespace discsignals;

class Crawler;

class CrawlerEngine : public Subsystem<Crawler>
{
	typedef enum {NEUT, FWD, REV} ENGINE_DIRECTION;
	typedef enum {OFF, SHUTDOWN, STARTING, ON} ENGINE_STATE;
public:
	explicit CrawlerEngine(SubsystemDirector<Crawler>* _director);
	~CrawlerEngine();

	void Realize() override;

	void OnPreStep(double simt, double SimDT, double mjd) override;

	bool OnParseLine(const char* keyword, const char* line) override;
	void OnSaveState(FILEHANDLE scn) const override;

	/**
	 * Returns acceleration of crawler due to engine (in m/s^2)
	 */
	double GetAcceleration() const;
	//void SetTargetSpeed(double speed);
	//void SetMaxSpeed(double speed);

	//void IncreaseTgtSpeed(bool _inc);
	//void DecreaseTgtSpeed(bool _dec);
private:
	// speed in m/s
	//double maxSpeed;
	//double targetSpeed;
	//double actualSpeed;
	double currentAcceleration;
	bool bReverse;

	//bool accelerate;
	//bool brake;
	//bool increaseTgtSpeed;
	//bool decreaseTgtSpeed;

	//double acceleration;

	double enginePower; // between -1 (reverse) and 1

	ENGINE_DIRECTION engineDirection;
	ENGINE_STATE engineState;

	DiscInPort NeutPBIFwd;
	DiscInPort NeutPBIAft;
	DiscInPort FwdPBIFwd;
	DiscInPort FwdPBIAft;
	DiscInPort RevPBIFwd;
	DiscInPort RevPBIAft;
	DiscOutPort NeutLightFwd;
	DiscOutPort NeutLightAft;
	DiscOutPort FwdLightFwd;
	DiscOutPort FwdLightAft;
	DiscOutPort RevLightFwd;
	DiscOutPort RevLightAft;

	DiscInPort currentSpeedFwd;
	DiscInPort currentSpeedAft;
	DiscInPort tgtSpeedFwd;
	DiscInPort tgtSpeedAft;
	DiscOutPort commandVoltageFwd;
	DiscOutPort commandVoltageAft;
};

#endif //__CRAWLERENGINE_H_F05A8448_9C86_481c_B632_0641CA218CF0