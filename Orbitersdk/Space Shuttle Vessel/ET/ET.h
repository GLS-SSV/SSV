/****************************************************************************
  This file is part of Space Shuttle Vessel

  External Tank vessel definition


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
2020/03/20   GLS
2020/03/29   GLS
2020/04/01   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/25   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/28   GLS
2021/08/08   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/08/05   GLS
********************************************/

#ifndef _ET_H
#define _ET_H
#pragma once

#include <Orbitersdk.h>
#include <discsignals.h>
#include <Sensor.h>
#include <cJSON.h>


using namespace discsignals;


inline constexpr double LOX_MAX_PROPELLANT_MASS = 624252.0;
inline constexpr double LH2_MAX_PROPELLANT_MASS = 104463.23;// seems to already include a 2145.485 lbs fuel bias, for 6.032 MR
inline constexpr double TANK_MAX_PROPELLANT_MASS = LOX_MAX_PROPELLANT_MASS+LH2_MAX_PROPELLANT_MASS;
// Main tank propellant mass [kg]


// ==========================================================
// Interface for derived vessel class: Atlantis_Tank
// ==========================================================

class ET: public VESSEL4 {
public:
	explicit ET (OBJHANDLE hObj);
	~ET();
	// Construct interface from existing object

	// Overloaded callback functions
	void clbkVisualCreated(VISHANDLE vis, int refcount) override;
	void clbkVisualDestroyed(VISHANDLE vis, int refcount) override;
	void clbkSetClassCaps (FILEHANDLE cfg) override;
	void clbkPostStep (double simt, double simdt, double mjd) override;
	void clbkLoadStateEx(FILEHANDLE scn, void* status) override;
	void clbkSaveState (FILEHANDLE scn) override;
	void clbkPostCreation( void ) override;
	int clbkGeneric( int msgid = 0, int prm = 0, void *context = NULL ) override;

	/**
	 * Simulated propellant flow from the External Tank.
	 * @param[in,out]	LOXmass	mass of liquid oxygen (in kg) to subtract from the ET, returns actual mass subtracted
	 * @param[in,out]	LH2mass	mass of liquid hydrogen (in kg) to subtract from the ET, returns actual mass subtracted
	 */
	virtual void PropellantFlow( double& LOXmass, double& LH2mass );

	/**
	 * Simulated pressurant flow into the External Tank.
	 * @param[in]	GOXmass	mass of gaseous oxygen pressurant (in kg) to add to the ET
	 * @param[in]	GH2mass	mass of gaseous hydrogen pressurant (in kg) to add to the ET
	 */
	virtual void PressurantFlow( double GOXmass, double GH2mass );

	/**
	 * Returns the remaining propellant mass level in the ET. No distinction is made between LOX and LH2 masses.
	 * @return		remaining propellant mass (in percent)
	 */
	virtual double GetPropellantLevel( void ) const;

	/**
	 * Returns the ullage pressure inside the LOX tank.
	 * This function should only be used for physics purposes.
	 * @return		LOX tank ullage pressure (in pascal)
	 * @see GetLH2UllagePressure
	 */
	virtual double GetLOXUllagePressure( void ) const;

	/**
	 * Returns the ullage pressure inside the LH2 tank.
	 * This function should only be used for physics purposes.
	 * @return		LH2 tank ullage pressure (in pascal)
	 * @see GetLOXUllagePressure
	 */
	virtual double GetLH2UllagePressure( void ) const;

private:
	typedef enum {SWT, LWT, SLWT} ET_TYPE;

	ET_TYPE type;

	void SetTexture( SURFHANDLE tex );
	void LoadTextures( void );

	void LoadMissionFile( void );
	void LoadMissionV1( cJSON* root );

	void SetConfiguration( void );

	/**
	 * This function updates the output of the pressure and level sensors.
	 */
	void UpdateSensors( void );

	bool useFRL;

	std::string strMission;

	VISHANDLE hVis;

	MESHHANDLE hTankMesh;
	DEVMESHHANDLE hDevTankMesh;
	UINT mesh_idx;
	bool bUseScorchedTexture;
	SURFHANDLE hTexture;
	SURFHANDLE hScorchedTexture;

	std::string strTextureName;

	ATTACHMENTHANDLE ahToOrbiter;

	PROPELLANT_HANDLE phET;
	double LOXmass;// kg
	double LH2mass;// kg
	double LOXullagepress;// Pa
	double LH2ullagepress;// Pa
	double GOXmass;// g
	double GH2mass;// g

	// level sensors (wet = true/5v, dry = false/0v)
	// considering level sensors are 0.15% "tall"
	Sensor LOXPct5LevelSensor;
	Sensor LOXPct98LevelSensor[2];
	Sensor LOXPct100MinusLevelSensor;//99.85%
	Sensor LOXPct100LevelSensor[2];
	Sensor LOXPct100PlusLevelSensor;// 100.15%
	Sensor LOXOverfillLevelSensor;// HACK using 101%

	Sensor LH2LowLevelSensor[4];// HACK using 0.2-0.05%
	Sensor LH2Pct5LevelSensor;
	Sensor LH2Pct98LevelSensor[2];
	Sensor LH2Pct100MinusLevelSensor;//99.85%
	Sensor LH2Pct100LevelSensor[2];
	Sensor LH2Pct100PlusLevelSensor;// 100.15%
	Sensor LH2OverfillLevelSensor;// HACK using 101%

	// pressure sensors
	Sensor LOXUllagePressureSensor[4];

	Sensor LH2UllagePressureSensor[4];

	bool sensorsconnected;
	bool postsep;

	// vent/relief valves
	bool GO2VentReliefValveOpen;
	bool GH2VentReliefValveOpen;

	// vents
	THRUSTER_HANDLE thGOXventNE;
	THRUSTER_HANDLE thGOXventSW;
	THRUSTER_HANDLE thGH2vent;
};

#endif// _ET_H
