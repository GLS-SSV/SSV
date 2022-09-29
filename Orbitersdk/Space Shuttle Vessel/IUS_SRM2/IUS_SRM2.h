/****************************************************************************
  This file is part of Space Shuttle Vessel

  Inertial Upper Stage SRM-2 vessel definition


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
2020/05/08   GLS
2020/05/14   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2020/06/28   GLS
2021/06/28   GLS
2021/08/10   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/10/23   GLS
2021/12/25   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/03/22   GLS
2022/03/23   GLS
2022/03/24   GLS
2022/05/07   GLS
2022/08/05   GLS
2022/09/29   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Inertial Upper Stage definition



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
#ifndef __IUS_SRM_2_H
#define __IUS_SRM_2_H


#include <Orbitersdk.h>
#include <PIDControl.h>
#include <cJSON.h>


inline constexpr double RCS_ENA_DELAY = 600.0;// s
inline constexpr double SRM_ENA_DELAY = 3600.0;// s


class IUS_SRM2:public VESSEL4
{
	friend class IUS_MFD;

	private:
		UINT mesh_stage;

		ATTACHMENTHANDLE ahPayload;
		ATTACHMENTHANDLE ahSRM1;
		ATTACHMENTHANDLE ahASE;

		PROPELLANT_HANDLE ph_main[2];
		PROPELLANT_HANDLE ph_rcs;

		int RCStanks;
		bool FourAntennas;
		double propload[2];

		THRUSTER_HANDLE th_main[2];
		THRUSTER_HANDLE th_rcs[12];

		PIDControl ctrlSRM_P;
		PIDControl ctrlSRM_Y;
		double SRM_P;
		double SRM_Y;
		double manP;
		double manY;

		AnimState asEXTENDNOZZLE;
		UINT anim_EXTENDNOZZLE;

		MGROUP_TRANSLATE* EEC_1;
		MGROUP_TRANSLATE* EEC_2;
		MGROUP_ROTATE* EEC_DEVICE_1;
		MGROUP_ROTATE* EEC_DEVICE_2;
		MGROUP_ROTATE* EEC_DEVICE_3;
		MGROUP_SCALE* EEC_STRIP_1;
		MGROUP_SCALE* EEC_STRIP_2;
		MGROUP_SCALE* EEC_STRIP_3;

		bool deployed;// deployed from ASE
		double timer_RCS_ENA;
		bool RCS_ENA;
		double timer_SRM_ENA;
		bool SRM_ENA;
		bool rollRCSonly;

		std::string AdapterMeshName;
		double AdapterOffset;// m
		double AdapterMass;// Kg

		int mfdID;

		LightEmitter* SRMlight[2];

		std::string strMission;

		std::string strTextureName;
		SURFHANDLE hTexture;

		void UpdateTexture( DEVMESHHANDLE hDevMesh );

		void SetStage2Config( void );
		void EnableRCS( void ) const;
		void EnablePitchYawRCS( void ) const;
		void InhibitPitchYawRCS( void ) const;

		void LoadMissionFile( void );
		void LoadMissionV1( cJSON* root );

		void AddPayloadAdapter( void );

	public:
		explicit IUS_SRM2( OBJHANDLE hObj );
		~IUS_SRM2( void );

		void clbkSetClassCaps(FILEHANDLE cfg) override;
		void clbkPostCreation( void ) override;
		void clbkPostStep( double simt, double simdt, double mjd ) override;
		void DefineAnimations(void);
		int clbkConsumeBufferedKey(DWORD key, bool down, char *kstate) override;
		void clbkVisualCreated(VISHANDLE vis, int refcount) override;
		void clbkLoadStateEx(FILEHANDLE scn, void *status) override;
		void clbkSaveState(FILEHANDLE scn) override;
};

#endif// __IUS_SRM_2_H
