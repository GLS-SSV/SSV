/****************************************************************************
  This file is part of Space Shuttle Vessel

  BaseSSVPad definition


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
2020/04/07   GLS
2020/05/07   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/14   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/01/07   GLS
2022/01/09   GLS
2022/08/05   GLS
********************************************/

#ifndef _BASESSVPAD_H_
#define _BASESSVPAD_H_
#pragma once

#include <Orbitersdk.h>
#include <vector>

/**
 * Base class for SSV pads (SLC-6 and LC-39)
 * Controls lights and animations common to both pads (OAA, GVA/Hood, IAA and GH2 ventline)
 */

const int OAA_RATE_NORMAL = 0;
const int OAA_RATE_EMERGENCY = 1;

class BaseSSVPad : public VESSEL4
{
	bool bLightsOn;
	double fNextLightUpdate;

	std::vector<BEACONLIGHTSPEC> lights;
	std::vector<BEACONLIGHTSPEC> stadium_lights;
	std::vector<LightEmitter*> pStadiumLights;

	std::vector<MGROUP_TRANSFORM*> vpAnimations;

protected:
	// 0.0 (CLOSED) corresponds to "retracted away from vehicle" state, 1.0 (OPEN) corresponds to "deployed towards the vehicle" state
	AnimState OAA_State;
	AnimState GVA_State;
	AnimState GOXVentHood_State;
	AnimState ETVAS_State;
	AnimState IAA_State;

	UINT anim_OAA;
	UINT anim_GVA;
	UINT anim_GOXVentHood;
	UINT anim_ETVAS;
	UINT anim_IAA;

	int oaa_mode;
	double orbiter_access_arm_rate[2];

	double fSSMESteamLevel;
	double fSRBSteamLevel;

	double WaterTank;// current quantity (gallons)
	double WaterTankCap;// capacity (gallons)
	double PreLOWaterFlowRate;// pre liftoff flow rate (gallons/sec)
	double PostLOWaterFlowRate;// post liftoff flow rate (gallons/sec)

	bool PreLOWaterOn;
	double PreLOWaterLevel;

	bool PostLOWaterOn;
	double PostLOWaterLevel;

	// HACK as the firex tank is big and the flow small, assume we never run out of water
	bool FirexOn_OrbiterSSMEWaterDelugeSystem;
	bool FirexOn_LH2LO2T0WaterDelugeSystem;
	bool FirexOn_OrbiterSkinSpraySystem;
	double FirexLevel_OrbiterSSMEWaterDelugeSystem;
	double FirexLevel_LH2LO2T0WaterDelugeSystem;
	double FirexLevel_OrbiterSkinSpraySystem;

	double GOXVentLevel;

	BaseSSVPad(OBJHANDLE hVessel, int flightmodel, double WaterTankCap, double PreLOWaterFlowRate, double PostLOWaterFlowRate );
	virtual ~BaseSSVPad();

	/**
	 * Creates lights (beacons only) at specified positions
	 * \param positions array of positions at which to create lights
	 * \param count number of lights (size of positions array)
	 */
	void CreateLights(VECTOR3* positions, unsigned int count);
	/**
	 * Creates stadium lights (beacons and spotlights) at specified positions
	 * \param positions array of positions at which to create lights
	 * \param count number of lights (size of positions array)
	 * \param range,att0,att1,att2,umbra,penumbra,diffuse,specular,ambient Passed directly to VESSEL::AddSpotLight function
	 */
	void CreateStadiumLights(const VECTOR3* positions, const VECTOR3* dir, unsigned int count, double range, double att0, double att1, double att2, double umbra, double penumbra, const COLOUR4& diffuse, const COLOUR4& specular, const COLOUR4& ambient);
	void ToggleLights(bool enable);
	bool IsNight() const;

	void SetOrbiterAccessArmRate(double rate, int mode);

	// animation command
	virtual void ExtendOAA( int mode );
	virtual void RetractOAA();
	virtual void HaltOAA();

	virtual void ExtendGVA();
	virtual void RetractGVA();
	virtual void HaltGVA();

	virtual void AttachETVAS();
	virtual void DetachETVAS();

	virtual void RaiseGOXVentHood();
	virtual void LowerGOXVentHood();
	virtual void HaltGOXVentHood();

	virtual void ExtendGVAandHood();
	virtual void RetractGVAandHood();

	virtual void DeployIAA();
	virtual void HaltIAA();
	virtual void RetractIAA();


	/**
	 * Performs actions common to both SLC-6 and LC-39
	 * Updates, loads and saves animations (OAA, GOX Vent Arm, GH2 vent line, Intertank Access Arm)
	 */
	void clbkPreStep(double simt, double simdt, double mjd) override;
	int clbkConsumeBufferedKey(DWORD key, bool down, char* keystate) override;
	void SaveState( FILEHANDLE scn );
	bool LoadState( const char* line );

	virtual void CalculateSteamProduction( double simt, double simdt ) = 0;

	/**
	 * Creates MGROUP_ROTATE struct, adds it to animation list, and returns pointer to struct
	 */
	MGROUP_ROTATE* DefineRotation(UINT mesh, UINT *grp, UINT ngrp, const VECTOR3 &ref, const VECTOR3 &axis, float angle);
	/**
	 * Creates MGROUP_TRANSLATE struct, adds it to animation list, and returns pointer to struct
	 */
	MGROUP_TRANSLATE* DefineTranslation(UINT mesh, UINT* grp, UINT ngrp, const VECTOR3& shift);
	/**
	 * Creates MGROUP_SCALE struct, adds it to animation list, and returns pointer to struct
	 */
	MGROUP_SCALE* DefineScale(UINT mesh, UINT* grp, UINT ngrp, const VECTOR3& ref, const VECTOR3& scale);
};

#endif// _BASESSVPAD_H_
