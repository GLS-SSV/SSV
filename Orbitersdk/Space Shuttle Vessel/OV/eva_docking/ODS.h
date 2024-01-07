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
2023/01/14   GLS
2023/02/05   GLS
2023/02/12   GLS
2023/12/06   GLS
2023/12/20   GLS
2024/01/07   GLS
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


class ExternalLight;
class CCTVCamera;


namespace eva_docking
{
	using discsignals::DiscInPort;
	using discsignals::DiscOutPort;

	using namespace std;

	class PSU;
	class DSCU;
	class DMCU;
	class PACU;
	class LACU;


	class ODS: public ExtAirlock {
	protected:
		double fRingState;// 0=retracted, 1=extended
		double fHooks1State;// 0=op, 1=cl
		double fHooks2State;// 0=op, 1=cl
		double fLatch1State;// 0º=0=op, 180º=1=cl
		double fLatch2State;// 0º=0=op, 180º=1=cl
		double fLatch3State;// 0º=0=op, 180º=1=cl

		bool bFirstStep;

		UINT anim_ring;
		UINT anim_rods;
		UINT anim_hooks1;
		UINT anim_hooks2;
		UINT anim_latches1;
		UINT anim_latches2;
		UINT anim_latches3;

		DOCKHANDLE hDock;
		VECTOR3 DockPos;// current docking port position

		UINT mesh_ods;
		MESHHANDLE hODSMesh;

		DiscInPort dipPowerOn;
		DiscInPort dipPowerOff;
		DiscInPort dipRingOut;
		DiscInPort dipRingIn;
		DiscInPort dipAPDSCircProtOff;
		DiscInPort dipCloseHooks;
		DiscInPort dipCloseLatches;
		DiscInPort dipFixerOff;
		DiscInPort dipPyroCircProtOff;
		DiscInPort dipPyroCircProtOn;
		DiscInPort dipActHooksFiring;
		DiscInPort dipPasHooksFiring;
		DiscInPort dipOpenHooks;
		DiscInPort dipOpenLatches;
		DiscInPort dipUndocking;

		DiscInPort dipControlPanelPowerA;
		DiscInPort dipControlPanelPowerB;
		DiscInPort dipControlPanelPowerC;
		DiscInPort dipHeatersDCUPowerH1;
		DiscInPort dipHeatersDCUPowerH2DCU;
		DiscInPort dipHeatersDCUPowerH3DCU;
		DiscInPort dipAPDSPowerA;
		DiscInPort dipAPDSPowerB;
		DiscInPort dipAPDSPowerC;
		DiscInPort dipPyrosAp;
		DiscInPort dipPyrosBp;
		DiscInPort dipPyrosCp;

		DiscOutPort dopPowerOnLight_A;
		DiscOutPort dopPowerOnLight_C;
		DiscOutPort dopAPDSCircuitProtectOffLight_A;
		DiscOutPort dopAPDSCircuitProtectOffLight_C;
		DiscOutPort dopRingAlignedLight_A;
		DiscOutPort dopRingAlignedLight_C;
		DiscOutPort dopRingInitialPositionLight_A;
		DiscOutPort dopRingInitialPositionLight_C;
		DiscOutPort dopFixersOffLight_A;
		DiscOutPort dopFixersOffLight_C;
		DiscOutPort dopHooks1OpenLight_A;
		DiscOutPort dopHooks1OpenLight_C;
		DiscOutPort dopHooks2OpenLight_A;
		DiscOutPort dopHooks2OpenLight_C;
		DiscOutPort dopLatchesClosedLight_A;
		DiscOutPort dopLatchesClosedLight_C;
		DiscOutPort dopUndockCompletLight_A;
		DiscOutPort dopUndockCompletLight_C;
		DiscOutPort dopInitialContactLight_A;
		DiscOutPort dopInitialContactLight_C;
		DiscOutPort dopCaptureCaptureLight_A;
		DiscOutPort dopCaptureCaptureLight_C;
		DiscOutPort dopRingForwardPositionLight_A;
		DiscOutPort dopRingForwardPositionLight_C;
		DiscOutPort dopReadyToHookLight_A;
		DiscOutPort dopReadyToHookLight_C;
		DiscOutPort dopInterfSealedLight_A;
		DiscOutPort dopInterfSealedLight_C;
		DiscOutPort dopHooks1ClosedLight_A;
		DiscOutPort dopHooks1ClosedLight_C;
		DiscOutPort dopHooks2ClosedLight_A;
		DiscOutPort dopHooks2ClosedLight_C;
		DiscOutPort dopLatchesOpenLight_A;
		DiscOutPort dopLatchesOpenLight_C;
		DiscOutPort dopRingFinalPositionLight_A;
		DiscOutPort dopRingFinalPositionLight_C;
		DiscOutPort dopPyroCircuitProtectOffLight_A;
		DiscOutPort dopPyroCircuitProtectOffLight_C;

		DiscOutPort dopADSLight;
		DiscOutPort dopBDSLight;
		DiscOutPort dopCDSLight;
		DiscOutPort dopAPLight;
		DiscOutPort dopBPLight;
		DiscOutPort dopCPLight;

		ExternalLight* vestibule_lights[2];

		CCTVCamera* camera;


		// hook position sensors (ground) thru PACU
		bool hooks_1_cl_ind_1;
		bool hooks_1_cl_ind_2;
		bool hooks_1_cl_ind_3;
		bool hooks_1_op_ind_1;
		bool hooks_1_op_ind_2;
		bool hooks_1_op_ind_3;
		bool hooks_2_cl_ind_1;
		bool hooks_2_cl_ind_2;
		bool hooks_2_cl_ind_3;
		bool hooks_2_op_ind_1;
		bool hooks_2_op_ind_2;
		bool hooks_2_op_ind_3;

		bool gnd_hooks_1_cl_1;
		bool gnd_hooks_1_cl_2;
		bool gnd_hooks_1_cl_3;
		bool gnd_hooks_2_cl_1;
		bool gnd_hooks_2_cl_2;
		bool gnd_hooks_2_cl_3;

		bool latches_cl_ind_1;
		bool latches_cl_ind_2;
		bool latches_op_ind_1;
		bool latches_op_ind_2;

		bool latch_motor_cl_gnd_1;
		bool latch_motor_cl_gnd_2;
		bool latch_motor_op_gnd_1;
		bool latch_motor_op_gnd_2;

		bool ring_in_cmd_1;
		bool ring_in_cmd_2;
		bool ring_in_cmd_3;


		void CalculateRodAnimation();

		void AddMesh( void );
		void CreateDockingPort( void );
		void UpdateDockParams( void );
		void DefineAnimations( void );

		void RunLights( double simdt );

		double LatchMotorToAnimation( const double motor ) const;

		PSU* pPSU;
		DSCU* pDSCU;
		DMCU* pDMCU;
		PACU* pPACU[2];
		LACU* pLACU;

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
		void VisualCreated( VISHANDLE vis ) override;
		virtual void ShiftCG( const VECTOR3& shift ) override;
	};
}

#endif// _ODS_H_
