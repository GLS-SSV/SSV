/****************************************************************************
  This file is part of Space Shuttle Vessel

  Remote Manipulator System subsystem definition


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
2020/05/06   GLS
2020/05/10   GLS
2020/05/14   GLS
2020/06/20   GLS
2020/10/10   GLS
2021/06/28   GLS
2021/07/02   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2022/01/02   GLS
2022/01/03   GLS
2022/01/04   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/02/16   GLS
2022/03/24   GLS
2022/03/26   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/10/30   GLS
2022/11/01   GLS
2022/11/09   GLS
2022/11/12   GLS
2023/01/15   GLS
2023/02/12   GLS
2023/02/13   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Remote Manipulator System definition



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
#ifndef __RMS_H
#define __RMS_H


#include "MPM.h"


class ExternalLight;class CCTVCamera;
class CCTVCameraPTU;
class RemoteVideoSwitcher;


class RMS : public MPM
{
public:
	typedef enum {SHOULDER_YAW=0, SHOULDER_PITCH=1, ELBOW_PITCH=2, WRIST_PITCH=3, WRIST_YAW=4, WRIST_ROLL=5} RMS_JOINT;

	RMS( AtlantisSubsystemDirector* _director, const std::string& _ident, bool portside );
	virtual ~RMS();

	void Realize() override;
	void OnPreStep(double simt, double simdt, double mjd) override;
	void OnPostStep(double simt, double simdt, double mjd) override;
	bool OnParseLine(const char* line) override;
	void OnSaveState(FILEHANDLE scn) const override;
	void VisualCreated( VISHANDLE vis ) override;
	bool SingleParamParseLine() const override {return true;};

	// mass value from Shuttle Systems Weight & Performance Monthly Status Report, Dec. 30 1983 (NASA-TM-85494)
	double GetSubsystemMass() const override {return 426.8304;};

	void CreateAttachment() override;
	virtual void ShiftCG( const VECTOR3& shift ) override;

	void UpdateAttachment( void );

	/**
	 * Returns true if arm is free to move.
	 * Returns false if arm is grappled to payload which is attached to something else.
	 */
	bool Movable() const;

protected:
	void OnMRLLatched( void ) override;
	void OnMRLReleased( void ) override;

	void OnAttach() override;
	void OnDetach() override;
private:
	void AddMesh( void );
	void DefineAnimations( void );
	bool ArmStowed() const;

	/**
	 * Calculates new EE position (in IK frame) for given delta pos
	 * @param dPos change in position (in meters) in selected RMS control frame
	 * @param newPos new EE position in IK frame
	 */
	void Translate(const VECTOR3 &dPos, VECTOR3& newPos);
	/**
	 * Calculates new EE rotation parameters (in IK frame) for given Euler angles.
	 * @param dAngles YZX Euler angles (around RMS control frame) in radians
	 * @param newDir new direction vector of EE after rotation in IK frame
	 * @param newRot new rot vector of EE after rotation in IK frame
	 */
	void Rotate(const VECTOR3 &dAngles, VECTOR3& newDir, VECTOR3& newRot); // angles in radians
	bool MoveEE(const VECTOR3 &newPos, const VECTOR3 &newDir, const VECTOR3 &newRot, double simdt);
	void SetJointAngle(RMS_JOINT joint, double angle); //angle in degrees
	/**
	 * Converts vector from Orbitersim frame to RMS frame
	 * Does not rotate vector to correct for RMS rollout angle
	 */
	VECTOR3 ConvertVectorToRMSFrame(const VECTOR3& v) const
	{
		return _V(-v.z, -v.x, -v.y);
	}

	int GetSelectedJoint() const;

	/**
	 * Updates the EE spotlight position/direction. To be called when the RMS moves and also from the Atlantis c.g. change member.
	 */
	void UpdateEELight( void );

	void AutoGrappleSequence();
	void AutoReleaseSequence();

	/**
	 * Checks if any joint is past its software stop.
	 */
	void CheckSoftwareStop( void );

	void CheckRFL( void );

	/**
	 * Calculates EE, CCTV and light positions, directions and orientations from joint angles.
	 */
	void CalcVectors( void );

	MESHHANDLE hMesh_RMS;
	MESHHANDLE hMesh_Pedestal;
	UINT mesh_index_RMS;
	UINT mesh_index_pedestal_forward;
	UINT mesh_index_pedestal_mid;
	UINT mesh_index_pedestal_aft;

	DiscInPort RMSSelect;

	UINT anim_joint[6], anim_rms_ee;

	CCTVCameraPTU* cameraElbow;
	CCTVCamera* cameraWrist;
	RemoteVideoSwitcher* videoswitcher;


	ExternalLight* light;

	//EE and IK parameters
	/** Refence frame for internal calculations:
	 * +X: Towards tail
	 * +Y: towards port side (right from aft windows)
	 * +Z: Down
	 * arm_ik_dir and arm_ik_rot define frame oriented along RMS joints; this is slightly rotated from shuttle frame (and from EE frame)
	 */
	VECTOR3 arm_ik_pos, arm_ik_dir, arm_ik_rot;
	VECTOR3 arm_ee_angles; // angles in radians; used for some IK modes
	double joint_angle[6];// angles in degrees
	int joint_motion[6];
	int ee_translation[3];

	// EE, CCTV and light vectors
	VECTOR3 posEE;
	VECTOR3 dirEE;
	VECTOR3 rotEE;
	VECTOR3 rotEEik;
	VECTOR3 posCCTVEE;
	VECTOR3 posCCTVElbow;
	VECTOR3 dirCCTVElbow;
	VECTOR3 rotCCTVElbow;
	VECTOR3 posLight;

	DiscInPort JointSelect[6], DirectDrivePlus, DirectDriveMinus;
	DiscInPort RHCInput[3], THCInput[3];
	DiscInPort RMSMode[12];
	DiscInPort RMSCoarseRateCMD;

	double shoulder_brace;
	DiscInPort ShoulderBrace;
	DiscOutPort ShoulderBraceReleased;

	DiscOutPort CWLights[12];
	DiscOutPort ModeLights[12];

	DiscOutPort SoftStopTB;// input inverted to display barberpole when "on"
	DiscOutPort RateMinTB;

	AnimState Grapple_State, Rigid_State, Extend_State;
	DiscInPort EEAuto, EEMan, EERigid, EEDerigid, EEGrapple, EERelease;
	DiscOutPort EECapture, EEExtended, EEClosed, EEOpened, EERigidized, EEDerigidized;
	bool bAutoGrapple, bAutoRelease;

	DiscInPort MasterAlarmPBI;

	bool MasterAlarmOn;
	bool ReachLimit;

	bool arm_moved;
	bool update_vectors, update_angles;

	bool bFirstStep;

	/**
	 * Indicates if RMS is stowed and latched (i.e., not movable).
	 */
	bool stowed_and_latched;

	/**
	 * True if any joint is past its software stop.
	 */
	bool bSoftStop;

	bool bEECapture;
	bool bEEExtended;
	bool bEEClosed;
	bool bEEOpened;
	bool bEERigidized;
	bool bEEDerigidized;

	// for LED displays on panel A8
	DiscOutPort JointAngles[6], EEPosition[3], EEAttitude[3];
};

#endif //__RMS_H
