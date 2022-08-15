/****************************************************************************
  This file is part of Space Shuttle Vessel

  Centaur G/G-Prime vessel definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/05/14   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2020/08/19   GLS
2021/06/28   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Centaur G/G-Prime definition



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
#ifndef __SC_H
#define __SC_H


#include <Orbitersdk.h>
#include "PIDControl.h"
#include <cJSON.h>


inline constexpr double RL10_START_SEQ = 270.0;// s
inline constexpr double ACS_ENA_DELAY = 300.0;// s
inline constexpr double RL10_ENA_DELAY = 2700.0 - RL10_START_SEQ;// s


class Centaur: public VESSEL4
{
	friend class Centaur_MFD;

	public:
		explicit Centaur( OBJHANDLE hVessel );
		~Centaur( void );

		void clbkSetClassCaps( FILEHANDLE cfg ) override;
		void clbkPostCreation( void ) override;
		void clbkPreStep( double simt, double simdt, double mjd ) override;
		int clbkConsumeBufferedKey( DWORD key, bool down, char* kstate ) override;
		void clbkVisualCreated( VISHANDLE vis, int refcount ) override;
		void clbkSaveState( FILEHANDLE scn ) override;
		void clbkLoadStateEx( FILEHANDLE scn, void *status ) override;

	private:
		bool isGPrime;
		MESHHANDLE hMesh;
		UINT mesh_idx;

		AnimState asANTENNA;
		UINT anim_ANTENNA;

		MGROUP_ROTATE* ANTENNA1;
		MGROUP_ROTATE* ANTENNA2;

		std::string AdapterMeshName;
		double AdapterOffset;// m
		double AdapterMass;// Kg

		ATTACHMENTHANDLE ahToPayload;
		ATTACHMENTHANDLE ahToCISS;
		PROPELLANT_HANDLE phTank;
		PROPELLANT_HANDLE phACS;
		THRUSTER_HANDLE thRL10[2];
		THRUSTER_HANDLE thACS[12];

		PIDControl ctrlRL10_P;
		PIDControl ctrlRL10_Y;
		PIDControl ctrlRL10_R;
		double RL10_P;
		double RL10_Y;
		double RL10_R;
		double manP;
		double manY;
		double manR;

		bool separated;
		double timer_ACS_ENA;
		bool ACS_ENA;
		double timer_RL10_ENA;
		bool RL10_ENA;
		double timer_RL10_startseq;
		bool RL10_startseq;
		double RL10_chill;

		int mfdID;

		LightEmitter* RL10light[2];

		std::string strMission;

		void DefineGAnimations( void );
		void DefineGPrimeAnimations( void );

		void EnableACS( void ) const;
		void EnablePitchYawRollACS( void ) const;
		void InhibitPitchYawRollACS( void ) const;

		void LoadMissionFile( void );
		void LoadMissionV1( cJSON* root );

		void AddPayloadAdapter( void );
};

#endif// __SC_H
