/****************************************************************************
  This file is part of Space Shuttle Vessel

  Xenon Lights vessel definition


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
2020/05/01   GLS
2020/05/10   GLS
2020/06/01   GLS
2020/06/12   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/09/09   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/12/25   GLS
2022/01/09   GLS
********************************************/

#ifndef __XENONLIGHTS_H_
#define __XENONLIGHTS_H_


#include <Orbitersdk.h>
#include <vector>


class XenonLights : public VESSEL4
{
public:
	XenonLights(OBJHANDLE hVessel, int fmodel);
	virtual ~XenonLights();

	void clbkSetClassCaps(FILEHANDLE cfg) override;

	void clbkPreStep(double simT, double simDT, double mjd) override;

	void clbkLoadStateEx( FILEHANDLE scn, void *status ) override;
	void clbkSaveState( FILEHANDLE scn ) override;

private:
	bool FindTarget();
	/**
	 * Gets parent vessel to which hVessel is attached
	 * @param hVessel vessel to find parent attachment
	 * @returns NULL if no parent, otherwise handle of parent vessel
	 */
	OBJHANDLE GetAttachedParent(OBJHANDLE hVessel) const;
	bool IsDay() const;

	void CreateLights();
	void DefineAnimations();

	void SetDirection(VECTOR3 dir);
	void SetLightState(bool on);

	UINT meshIndex;
	UINT anim_pan[2], anim_tilt[2];
	std::vector<MGROUP_TRANSFORM*> vpAnimations;
	VECTOR3 lightPosition[2];
	//double pan, tilt;
	VECTOR3 lightDir;

	BEACONLIGHTSPEC pLightsGlare[2];
	LightEmitter* pLights[2];

	bool bLightsOn;
	bool bFoundTarget;
	OBJHANDLE hTarget; // vessel lights are pointed at
	double heightOffset;

	double updateClock; // if <0, update position of target and light state

	bool locked;
};

#endif// __XENONLIGHTS_H_
