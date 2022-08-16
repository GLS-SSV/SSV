/****************************************************************************
  This file is part of Space Shuttle Vessel

  MPM subsystem definition


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
2020/05/06   GLS
2020/05/10   GLS
2020/05/13   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/10/10   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/23   GLS
2021/12/30   GLS
2022/05/15   GLS
2022/05/16   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  MPMSystem definition



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
#ifndef __MPM_H
#define __MPM_H
#pragma once

#include "Latch.h"
#include <discsignals.h>


inline constexpr double MPM_DEPLOY_SPEED = 0.0294117647;// 2 motor: 34s, 1 motor 68s

inline constexpr VECTOR3 MPM_DEPLOY_REF_PORT = { -2.4511, -0.11595, 0.0 };// Yo-96.5, Zo+412.25
inline constexpr VECTOR3 MPM_DEPLOY_AXIS_PORT = { 0.0, 0.0, 1.0 };
const float MPM_DEPLOY_ANGLE_PORT = static_cast<float>(31.36 * RAD);

inline constexpr VECTOR3 MPM_DEPLOY_REF_STBD = { 2.4511, -0.11595, 0.0 };// Yo+96.5, Zo+412.25
inline constexpr VECTOR3 MPM_DEPLOY_AXIS_STBD = { 0.0, 0.0, 1.0 };
const float MPM_DEPLOY_ANGLE_STBD = static_cast<float>(-31.36 * RAD);


inline constexpr double MRL_LATCH_SPEED = 0.125;// // 2 motor: 8s, 1 motor 18s


// MPM upper pedestal data for derived classes
inline constexpr VECTOR3 PEDESTAL_OFFSET_PORT_SHOULDER = { 0.0, 0.0, 6.979695 };
inline constexpr VECTOR3 PEDESTAL_OFFSET_PORT_FORWARD = { 0.0, 0.0, 1.098328 };
inline constexpr VECTOR3 PEDESTAL_OFFSET_PORT_MID = { 0.0, 0.0, -5.961605 };
inline constexpr VECTOR3 PEDESTAL_OFFSET_PORT_AFT = { 0.0, 0.0, -7.676105 };

inline constexpr VECTOR3 PEDESTAL_OFFSET_STBD_SHOULDER = { 0.0, 0.0, 6.979695 };
inline constexpr VECTOR3 PEDESTAL_OFFSET_STBD_FORWARD = { 0.0, 0.0, 1.098328 };
inline constexpr VECTOR3 PEDESTAL_OFFSET_STBD_MID = { 0.0, 0.0, -5.961605 };
inline constexpr VECTOR3 PEDESTAL_OFFSET_STBD_AFT = { 0.0, 0.0, -7.676105 };


using namespace discsignals;

class MPM : public LatchSystem
{
public:
	MPM( AtlantisSubsystemDirector* _director, const string& _ident, const string& _attachID, bool _portside, double latchmaxdistance, double latchmaxangle );
	virtual ~MPM();

	void Realize() override;
	void OnPreStep(double simt, double simdt, double mjd) override;
	bool OnParseLine(const char* line) override;
	void OnSaveState(FILEHANDLE scn) const override;

	void CheckDoubleAttach(VESSEL* vessel, bool attached);

protected:
	virtual void OnMRLLatched();
	virtual void OnMRLReleased();

	void OnAttach() override;
	void OnDetach() override;

	void SetRFL( bool fwd, bool mid, bool aft );

	ANIMATIONCOMPONENT_HANDLE mpmparent;// for derived classes
	UINT anim_mpm;// for derived classes

	UINT mesh_index_MPM;

	//true if MPM was moved this timestep
	bool mpm_moved;
	// true if MPM is attached to object that is attached to something else
	bool doubleAttached;

	double Rollout;// 0 = stowed; 1 = deployed
	double MRL[3];// [0 = FWD; 1 = MID; 2 = AFT] 0 = latched; 1 = released

	bool portside;

private:
	void AddMesh();
	void AddAnimation( void );

	void RunMicroswitches( void );

	MESHHANDLE hMesh_MPM;


	DiscInPort MPM_MOTOR_1_PWR;
	DiscInPort MPM_MOTOR_2_PWR;

	DiscInPort MPM_SHOULDER_1_IND_PWR;
	DiscInPort MPM_SHOULDER_2_IND_PWR;
	DiscInPort MPM_FWD_1_IND_PWR;
	DiscInPort MPM_FWD_2_IND_PWR;
	DiscInPort MPM_MID_1_IND_PWR;
	DiscInPort MPM_MID_2_IND_PWR;
	DiscInPort MPM_AFT_1_IND_PWR;
	DiscInPort MPM_AFT_2_IND_PWR;

	DiscOutPort SHLD_MECH_STOW_IND_1;
	DiscOutPort FWD_MECH_STOW_IND_1;
	DiscOutPort MID_MECH_STOW_IND_1;
	DiscOutPort AFT_MECH_STOW_IND_1;
	DiscOutPort SHLD_MECH_DEPLOY_IND_1;
	DiscOutPort FWD_MECH_DEPLOY_IND_1;
	DiscOutPort MID_MECH_DEPLOY_IND_1;
	DiscOutPort AFT_MECH_DEPLOY_IND_1;
	DiscOutPort SHLD_MECH_STOW_IND_2;
	DiscOutPort FWD_MECH_STOW_IND_2;
	DiscOutPort MID_MECH_STOW_IND_2;
	DiscOutPort AFT_MECH_STOW_IND_2;
	DiscOutPort SHLD_MECH_DEPLOY_IND_2;
	DiscOutPort FWD_MECH_DEPLOY_IND_2;
	DiscOutPort MID_MECH_DEPLOY_IND_2;
	DiscOutPort AFT_MECH_DEPLOY_IND_2;


	DiscInPort FWD_MRL_MOTOR_1_PWR;
	DiscInPort FWD_MRL_MOTOR_2_PWR;
	DiscInPort MID_MRL_MOTOR_1_PWR;
	DiscInPort MID_MRL_MOTOR_2_PWR;
	DiscInPort AFT_MRL_MOTOR_1_PWR;
	DiscInPort AFT_MRL_MOTOR_2_PWR;

	DiscInPort FWD_MRL_IND_1_PWR;
	DiscInPort FWD_MRL_IND_2_PWR;
	DiscInPort FWD_RETNN_RFL_1_PWR;
	DiscInPort FWD_RETNN_RFL_2_PWR;
	DiscInPort MID_MRL_IND_1_PWR;
	DiscInPort MID_MRL_IND_2_PWR;
	DiscInPort MID_RETNN_RFL_1_PWR;
	DiscInPort MID_RETNN_RFL_2_PWR;
	DiscInPort AFT_MRL_IND_1_PWR;
	DiscInPort AFT_MRL_IND_2_PWR;
	DiscInPort AFT_RETNN_RFL_1_PWR;
	DiscInPort AFT_RETNN_RFL_2_PWR;

	DiscOutPort FWD_MRL_LATCH_IND_1;
	DiscOutPort MID_MRL_LATCH_IND_1;
	DiscOutPort AFT_MRL_LATCH_IND_1;
	DiscOutPort FWD_MRL_RELEASE_IND_1;
	DiscOutPort MID_MRL_RELEASE_IND_1;
	DiscOutPort AFT_MRL_RELEASE_IND_1;
	DiscOutPort FWD_MRL_LATCH_IND_2;
	DiscOutPort MID_MRL_LATCH_IND_2;
	DiscOutPort AFT_MRL_LATCH_IND_2;
	DiscOutPort FWD_MRL_RELEASE_IND_2;
	DiscOutPort MID_MRL_RELEASE_IND_2;
	DiscOutPort AFT_MRL_RELEASE_IND_2;
	DiscOutPort FWD_RETNN_RFL_1;
	DiscOutPort MID_RETNN_RFL_1;
	DiscOutPort AFT_RETNN_RFL_1;
	DiscOutPort FWD_RETNN_RFL_2;
	DiscOutPort MID_RETNN_RFL_2;
	DiscOutPort AFT_RETNN_RFL_2;
};

#endif //__MPM_H
