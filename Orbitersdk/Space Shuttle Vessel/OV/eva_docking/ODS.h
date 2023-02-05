/****************************************************************************
  This file is part of Space Shuttle Vessel

  Orbiter Docking System subsystem definition


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
2020/04/07   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/05/23   GLS
2020/05/24   GLS
2020/06/01   GLS
2020/06/20   GLS
2020/06/23   GLS
2021/06/06   GLS
2021/06/30   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2022/01/10   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
2022/09/29   GLS
2023/02/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Orbiter Docking System definition



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
#ifndef _ODS_H_
#define _ODS_H_


#include "ExtAirlock.h"
#include <DiscOutPort.h>
#include <DiscInPort.h>
#include <set>
#include <VesselAPI.h>


class CCTVCamera;


namespace eva_docking
{
	using discsignals::DiscInPort;
	using discsignals::DiscOutPort;

	using namespace std;

	class ODS: public ExtAirlock {
	protected:
		//UINT midxODS;
		double fRingState;
		double fHookState;
		double fLatchState;
		//double fVestPressure[2];
		double fInterfAtmP[2];
		double fInterfAtmT[2];
		double fInterfAtmMass[2];

		bool bDSCUPower;

		bool bFirstStep;

		AnimState RingState;

		//Target data
		bool bTargetInCone;
		bool bTargetCaptured;
		OBJHANDLE ohTarget;
		ATTACHMENTHANDLE ahTarget;
		VECTOR3 target_pos;
		VECTOR3 target_dir;
		VECTOR3 target_rot;
		VECTOR3 target_vel;	//Use also for relative speed in captured case.
		VECTOR3 target_avel;
		VECTOR3 eX, eY, eZ;

		vector<pair<OBJHANDLE,ATTACHMENTHANDLE>> APASdevices;// list of vessel/APAS port pairs

		bool APASdevices_populated;

		typedef enum ___extend_goal {
			EXTEND_TO_INITIAL,
			EXTEND_TO_FINAL,
			RETRACT_TO_FINAL
		} EXTEND_GOAL;

		EXTEND_GOAL extend_goal;

		UINT anim_ring;
		UINT anim_rods;
		UINT anim_screw;
		MGROUP_TRANSLATE*	pRingAnim;
		MGROUP_TRANSLATE*	pRingAnimV;
		MGROUP_SCALE*		pCoilAnim;
		MGROUP_ROTATE*		pRod1LAnim[3];
		MGROUP_ROTATE*		pRod2LAnim[3];
		MGROUP_ROTATE*		pRod3LAnim[3];
		MGROUP_ROTATE*		pRod1RAnim[3];
		MGROUP_ROTATE*		pRod2RAnim[3];
		MGROUP_ROTATE*		pRod3RAnim[3];

		bool bPowerRelay;
		bool bAPDSCircuitProtectionOff;
		bool bFixersOn;
		bool bLatchesOpen;
		bool bLatchesClosed;
		bool bHooks1Open;
		bool bHooks1Closed;
		bool bHooks2Open;
		bool bHooks2Closed;

		VECTOR3 odsAttachVec[3];

		UINT mesh_ods;
		MESHHANDLE hODSMesh;

		ATTACHMENTHANDLE ahDockAux;

		DiscInPort dscu_PowerOn;
		DiscInPort dscu_PowerOff;
		DiscInPort dscu_RingOut;
		DiscInPort dscu_RingIn;
		DiscInPort dscu_APDSCircProtectionOff;
		DiscInPort dscu_CloseHooks;
		DiscInPort dscu_CloseLatches;
		DiscInPort dscu_FixerOff;
		DiscInPort dscu_PyroCircProtOff;
		DiscInPort dscu_PyroCircProtOn;
		DiscInPort dscu_ActHooksFiring;
		DiscInPort dscu_PasHooksFiring;
		DiscInPort dscu_OpenHooks;
		DiscInPort dscu_OpenLatches;
		DiscInPort dscu_Undocking;

		DiscInPort dscu_ControlPanelPowerA;
		DiscInPort dscu_ControlPanelPowerB;
		DiscInPort dscu_ControlPanelPowerC;
		DiscInPort dscu_HeatersDCUPowerH1;
		DiscInPort dscu_HeatersDCUPowerH2DCU;
		DiscInPort dscu_HeatersDCUPowerH3DCU;
		DiscInPort dscu_APDSPowerA;
		DiscInPort dscu_APDSPowerB;
		DiscInPort dscu_APDSPowerC;
		DiscInPort dscu_PyrosAp;
		DiscInPort dscu_PyrosBp;
		DiscInPort dscu_PyrosCp;

		DiscInPort LightsTrussFwd;
		DiscInPort LightsTrussAft;
		DiscInPort LightsVestibulePort;
		DiscInPort LightsVestibuleStbd;

		DiscOutPort dscu_PowerOnLight;
		DiscOutPort dscu_APDSCircProtectLight;
		DiscOutPort dscu_RingAlignedLight;
		DiscOutPort dscu_RingInitialLight;
		DiscOutPort dscu_FixersOffLight;
		DiscOutPort dscu_Hooks1OpenLight;
		DiscOutPort dscu_Hooks2OpenLight;
		DiscOutPort dscu_LatchesClosedLight;
		DiscOutPort dscu_UndockCompleteLight;
		DiscOutPort dscu_InitialContactLight;
		DiscOutPort dscu_CaptureLight;
		DiscOutPort dscu_RingForwardLight;
		DiscOutPort dscu_ReadyToHookLight;
		DiscOutPort dscu_InterfSealedLight;
		DiscOutPort dscu_Hooks1ClosedLight;
		DiscOutPort dscu_Hooks2ClosedLight;
		DiscOutPort dscu_LatchesOpenLight;
		DiscOutPort dscu_RingFinalLight;
		DiscOutPort dscu_PyroProtectCircuitOff;
		DiscOutPort dscu_ADSLight;
		DiscOutPort dscu_BDSLight;
		DiscOutPort dscu_CDSLight;
		DiscOutPort dscu_APLight;
		DiscOutPort dscu_BPLight;
		DiscOutPort dscu_CPLight;

		LightEmitter* FwdTrussLight;
		LightEmitter* AftTrussLight;
		LightEmitter* CLVestPortLight;
		LightEmitter* CLVestStbdLight;
		VECTOR3 FwdTrussLightPosition;
		VECTOR3 AftTrussLightPosition;
		VECTOR3 CLVestPortLightPosition;
		VECTOR3 CLVestStbdLightPosition;
		BEACONLIGHTSPEC FwdTrussLight_bspec;
		BEACONLIGHTSPEC AftTrussLight_bspec;
		BEACONLIGHTSPEC CLVestPortLight_bspec;
		BEACONLIGHTSPEC CLVestStbdLight_bspec;

		CCTVCamera* camera;


		bool HasDSCUPower() const;
		void CalculateRodAnimation();

		void PopulateAPASdevices( void );
		bool FindClosestAPAS( void );
		void AddMesh( void );
		void SetDockParams( void );
		void DefineAnimations( void );

		/**
		 * Defines payload bay light (LightEmitter and associated beacon)
		 * \param pos position of light
		 * \param bspec Beacon spec to be initialized with data
		 * \returns LightEmitter pointer
		 */
		LightEmitter* AddLight( VECTOR3& pos, BEACONLIGHTSPEC& bspec );

		void CreateLights( void );
		void RunLights( void );

	public:
		ODS( AtlantisSubsystemDirector* _director, bool aftlocation );
		virtual ~ODS();
		void Realize() override;
		double GetSubsystemMass( void ) const override;
		bool GetSubsystemCoG( VECTOR3& CoG ) const override;
		void OnSaveState(FILEHANDLE scn) const override;
		void OnPreStep(double simt, double simdt, double mjd) override;
		void OnPostStep(double simt, double simdt, double mjd) override;
		bool OnParseLine(const char* keyword, const char* line) override;
		void UpdateODSAttachment( void );
		void UpdateLights( void );
	};

}

#endif// _ODS_H_
