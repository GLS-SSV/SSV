/****************************************************************************
  This file is part of Space Shuttle Vessel

  Payload Bay subsystem definition


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
2020/04/14   GLS
2020/05/10   GLS
2020/05/23   GLS
2020/06/20   GLS
2020/06/28   GLS
2020/07/03   GLS
2020/07/30   GLS
2020/08/13   GLS
2020/08/14   GLS
2020/08/16   GLS
2020/08/17   GLS
2020/08/19   GLS
2020/08/22   GLS
2020/08/23   GLS
2020/08/25   GLS
2020/09/12   GLS
2020/09/15   GLS
2020/09/24   GLS
2020/10/07   GLS
2020/10/10   GLS
2021/02/16   GLS
2021/06/13   GLS
2021/07/01   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/12   GLS
2021/09/21   GLS
2021/11/13   GLS
2021/11/27   GLS
2021/12/05   GLS
2022/01/10   GLS
2022/01/12   GLS
2022/01/31   GLS
2022/02/01   GLS
2022/02/02   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/11/02   GLS
2023/02/05   GLS
2023/02/15   GLS
2023/02/16   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  PayloadBay System definition



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
#ifndef __PLB_H_
#define __PLB_H_


#include "AtlantisSubsystem.h"
#include "mission/Mission.h"
#include <discsignals.h>
#include <Orbitersdk.h>


class CCTVCameraPTU;
class CCTVCamera;


using namespace discsignals;


class PayloadBay:public AtlantisSubsystem
{
	private:
		DiscInPort MNA_MMC1;
		DiscInPort MNB_MMC1;
		DiscInPort MNB_MMC2;
		DiscInPort MNC_MMC2;
		DiscInPort MNA_MMC3;
		DiscInPort MNB_MMC3;
		DiscInPort MNB_MMC4;
		DiscInPort MNC_MMC4;

		DiscInPort PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR;
		DiscInPort PORT_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR;
		DiscOutPort PORT_FWD_RDY_LATCH_1;
		DiscOutPort PORT_FWD_RDY_LATCH_2;
		DiscOutPort PORT_FWD_RDY_LATCH_3;
		DiscOutPort PORT_AFT_RDY_LATCH_1;
		DiscOutPort PORT_AFT_RDY_LATCH_2;
		DiscOutPort PORT_AFT_RDY_LATCH_3;
		DiscOutPort PORT_DOOR_CLOSE_1;
		DiscOutPort PORT_DOOR_CLOSE_2;
		DiscOutPort PORT_DOOR_OPEN_1;
		DiscOutPort PORT_DOOR_OPEN_2;
		DiscOutPort PORT_FWD_88;
		DiscOutPort PORT_AFT_88;

		DiscInPort STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_1_PWR;
		DiscInPort STARBOARD_DOOR_POWER_DRIVE_UNIT_MOTOR_2_PWR;
		DiscOutPort STBD_FWD_RDY_LATCH_1;
		DiscOutPort STBD_FWD_RDY_LATCH_2;
		DiscOutPort STBD_FWD_RDY_LATCH_3;
		DiscOutPort STBD_AFT_RDY_LATCH_1;
		DiscOutPort STBD_AFT_RDY_LATCH_2;
		DiscOutPort STBD_AFT_RDY_LATCH_3;
		DiscOutPort STBD_DOOR_CLOSE_1;
		DiscOutPort STBD_DOOR_CLOSE_2;
		DiscOutPort STBD_DOOR_OPEN_1;
		DiscOutPort STBD_DOOR_OPEN_2;
		DiscOutPort STBD_FWD_88;
		DiscOutPort STBD_AFT_88;

		DiscInPort CENTERLINE_ACTUATOR_1_4_MOTOR_1_PWR;
		DiscInPort CENTERLINE_ACTUATOR_1_4_MOTOR_2_PWR;
		DiscOutPort LAT_1_4_LAT_1;
		DiscOutPort LAT_1_4_LAT_2;
		DiscOutPort LAT_1_4_REL_1;
		DiscOutPort LAT_1_4_REL_2;

		DiscInPort CENTERLINE_ACTUATOR_5_8_MOTOR_1_PWR;
		DiscInPort CENTERLINE_ACTUATOR_5_8_MOTOR_2_PWR;
		DiscOutPort LAT_5_8_LAT_1;
		DiscOutPort LAT_5_8_LAT_2;
		DiscOutPort LAT_5_8_REL_1;
		DiscOutPort LAT_5_8_REL_2;

		DiscInPort CENTERLINE_ACTUATOR_9_12_MOTOR_1_PWR;
		DiscInPort CENTERLINE_ACTUATOR_9_12_MOTOR_2_PWR;
		DiscOutPort LAT_9_12_LAT_1;
		DiscOutPort LAT_9_12_LAT_2;
		DiscOutPort LAT_9_12_REL_1;
		DiscOutPort LAT_9_12_REL_2;

		DiscInPort CENTERLINE_ACTUATOR_13_16_MOTOR_1_PWR;
		DiscInPort CENTERLINE_ACTUATOR_13_16_MOTOR_2_PWR;
		DiscOutPort LAT_13_16_LAT_1;
		DiscOutPort LAT_13_16_LAT_2;
		DiscOutPort LAT_13_16_REL_1;
		DiscOutPort LAT_13_16_REL_2;

		DiscInPort BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_1_PWR;
		DiscInPort BULKHEAD_ACTUATOR_PORT_FORWARD_MOTOR_2_PWR;
		DiscOutPort PORT_FWD_BLKHD_LAT_1;
		DiscOutPort PORT_FWD_BLKHD_LAT_2;
		DiscOutPort PORT_FWD_BLKHD_REL_1;
		DiscOutPort PORT_FWD_BLKHD_REL_2;

		DiscInPort BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_1_PWR;
		DiscInPort BULKHEAD_ACTUATOR_PORT_AFT_MOTOR_2_PWR;
		DiscOutPort PORT_AFT_BLKHD_LAT_1;
		DiscOutPort PORT_AFT_BLKHD_LAT_2;
		DiscOutPort PORT_AFT_BLKHD_REL_1;
		DiscOutPort PORT_AFT_BLKHD_REL_2;

		DiscInPort BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_1_PWR;
		DiscInPort BULKHEAD_ACTUATOR_STBD_FORWARD_MOTOR_2_PWR;
		DiscOutPort STBD_FWD_BLKHD_LAT_1;
		DiscOutPort STBD_FWD_BLKHD_LAT_2;
		DiscOutPort STBD_FWD_BLKHD_REL_1;
		DiscOutPort STBD_FWD_BLKHD_REL_2;

		DiscInPort BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_1_PWR;
		DiscInPort BULKHEAD_ACTUATOR_STBD_AFT_MOTOR_2_PWR;
		DiscOutPort STBD_AFT_BLKHD_LAT_1;
		DiscOutPort STBD_AFT_BLKHD_LAT_2;
		DiscOutPort STBD_AFT_BLKHD_REL_1;
		DiscOutPort STBD_AFT_BLKHD_REL_2;


		DiscInPort PORT_RAD_DEPLOYMENT_MOTOR_1_PWR;
		DiscInPort PORT_RAD_DEPLOYMENT_MOTOR_2_PWR;
		DiscOutPort PORT_RAD_DEPLOYMENT_DPY_1;
		DiscOutPort PORT_RAD_DEPLOYMENT_STO_1;
		DiscOutPort PORT_RAD_DEPLOYMENT_DPY_2;
		DiscOutPort PORT_RAD_DEPLOYMENT_STO_2;

		DiscInPort STARBOARD_RAD_DEPLOYMENT_MOTOR_1_PWR;
		DiscInPort STARBOARD_RAD_DEPLOYMENT_MOTOR_2_PWR;
		DiscOutPort STARBOARD_RAD_DEPLOYMENT_DPY_1;
		DiscOutPort STARBOARD_RAD_DEPLOYMENT_STO_1;
		DiscOutPort STARBOARD_RAD_DEPLOYMENT_DPY_2;
		DiscOutPort STARBOARD_RAD_DEPLOYMENT_STO_2;


		DiscInPort PORT_RAD_LATCH_1_6_MOTOR_1_PWR;
		DiscInPort PORT_RAD_LATCH_1_6_MOTOR_2_PWR;
		DiscOutPort PORT_RAD_LATCH_1_6_REL_1;
		DiscOutPort PORT_RAD_LATCH_1_6_LAT_1;
		DiscOutPort PORT_RAD_LATCH_1_6_REL_2;
		DiscOutPort PORT_RAD_LATCH_1_6_LAT_2;

		DiscInPort PORT_RAD_LATCH_7_12_MOTOR_1_PWR;
		DiscInPort PORT_RAD_LATCH_7_12_MOTOR_2_PWR;
		DiscOutPort PORT_RAD_LATCH_7_12_REL_1;
		DiscOutPort PORT_RAD_LATCH_7_12_LAT_1;
		DiscOutPort PORT_RAD_LATCH_7_12_REL_2;
		DiscOutPort PORT_RAD_LATCH_7_12_LAT_2;

		DiscInPort STARBOARD_RAD_LATCH_7_12_MOTOR_1_PWR;
		DiscInPort STARBOARD_RAD_LATCH_7_12_MOTOR_2_PWR;
		DiscOutPort STARBOARD_RAD_LATCH_7_12_REL_1;
		DiscOutPort STARBOARD_RAD_LATCH_7_12_LAT_1;
		DiscOutPort STARBOARD_RAD_LATCH_7_12_REL_2;
		DiscOutPort STARBOARD_RAD_LATCH_7_12_LAT_2;

		DiscInPort STARBOARD_RAD_LATCH_1_6_MOTOR_1_PWR;
		DiscInPort STARBOARD_RAD_LATCH_1_6_MOTOR_2_PWR;
		DiscOutPort STARBOARD_RAD_LATCH_1_6_REL_1;
		DiscOutPort STARBOARD_RAD_LATCH_1_6_LAT_1;
		DiscOutPort STARBOARD_RAD_LATCH_1_6_REL_2;
		DiscOutPort STARBOARD_RAD_LATCH_1_6_LAT_2;

		DiscInPort KU_RNDZ_RADAR_MOTOR_1_PWR;
		DiscInPort KU_RNDZ_RADAR_MOTOR_2_PWR;
		DiscOutPort KU_RNDZ_RADAR_STO_IND_1;
		DiscOutPort KU_RNDZ_RADAR_DPY_IND_1;
		DiscOutPort KU_RNDZ_RADAR_STO_IND_2;
		DiscOutPort KU_RNDZ_RADAR_DPY_IND_2;
		DiscOutPort KU_RNDZ_RADAR_STO_IND;// to simplify TB
		DiscOutPort KU_RNDZ_RADAR_DPY_IND;// to simplify TB

		DiscInPort PLBLightPower[6];
		DiscInPort FwdBulkheadLightPower, DockingLightBright, DockingLightDim;

		// physical status
		double posplbd_port;// 0 = cl, 1 = op
		double posplbd_stbd;// 0 = cl, 1 = op
		double posplbd_latch_cl_1_4;// 0 = lat, 1 = rel
		double posplbd_latch_cl_5_8;// 0 = lat, 1 = rel
		double posplbd_latch_cl_9_12;// 0 = lat, 1 = rel
		double posplbd_latch_cl_13_16;// 0 = lat, 1 = rel
		double posplbd_latch_blkd_port_fwd;// 0 = lat, 1 = rel
		double posplbd_latch_blkd_port_aft;// 0 = lat, 1 = rel
		double posplbd_latch_blkd_stbd_fwd;// 0 = lat, 1 = rel
		double posplbd_latch_blkd_stbd_aft;// 0 = lat, 1 = rel

		double posradiator_port;// 0 = cl, 1 = op
		double posradiator_stbd;// 0 = cl, 1 = op
		double posradiator_latch_port_1_6;// 0 = lat, 1 = rel
		double posradiator_latch_port_7_12;// 0 = lat, 1 = rel
		double posradiator_latch_stbd_1_6;// 0 = lat, 1 = rel
		double posradiator_latch_stbd_7_12;// 0 = lat, 1 = rel

		double poskuband;// 0 = sto, 1 = dpy

		bool hasAntenna;
		bool hasFwdBulkDockLights;
		bool hasLiner;
		bool hasAftHandrails;
		bool hasEDOKit;
		bool hasBay13covers;
		bool hasT4panelcovers;
		bool hasDumpLinecovers;
		bool hasOriginalHandrails;
		bool hasMMUFSSInterfacePanel;
		bool hasDFIWireTray;
		bool hasVentDoors4and7;
		bool hasExtALODSKit;

		unsigned short EDOpallet;

		LightEmitter* PLBLight[6];
		LightEmitter* FwdBulkheadLight;
		LightEmitter* DockingLight;
		VECTOR3 PLBLightPosition[6];
		VECTOR3 FwdBulkheadLightPos, DockingLightPos;
		BEACONLIGHTSPEC PLB_bspec[6];
		BEACONLIGHTSPEC FwdBulkhead_bspec, Docking_bspec;

		mission::MissionPayloads payloads;
		mission::PLB_Cameras plbcameras;

		ATTACHMENTHANDLE ahPassive[5];
		ATTACHMENTHANDLE ahBayBridge[8];

		VECTOR3 Passive_pos[5];
		VECTOR3 BayBridge_pos[8];
		VECTOR3 BayBridge_dir[8];
		VECTOR3 BayBridge_rot[8];

		UINT mesh_PLB_bay13;

		UINT anim_door_port;			// handle for port payload bay door animation
		UINT anim_door_port_pushrod;		// handle for port payload bay door push rod animation
		UINT anim_door_port_clamp;		// handle for port payload bay door clamp animation
		UINT anim_door_port_pullrod;		// handle for port payload bay door pull rod animation
		UINT anim_door_port_slidewirelink;	// handle for port payload bay door slidewire link animation
		UINT anim_door_port_slidewirebracket;	// handle for port payload bay door slidewire bracket animation
		UINT anim_door_stbd;			// handle for starboard payload bay door animation
		UINT anim_door_stbd_pushrod;		// handle for starboard payload bay door push rod animation
		UINT anim_door_stbd_clamp;		// handle for starboard payload bay door clamp animation
		UINT anim_door_stbd_pullrod;		// handle for starboard payload bay door pull rod animation
		UINT anim_door_stbd_slidewirelink;	// handle for starboard payload bay door slidewire link animation
		UINT anim_door_stbd_slidewirebracket;	// handle for starboard payload bay door slidewire bracket animation
		UINT anim_rad_port;
		UINT anim_rad_stbd;
		UINT anim_clatch[4];					   // handle for center line latch gangs
		UINT anim_da;
		UINT anim_aftwinch_edo;

		CCTVCameraPTU* cameras[4];
		CCTVCamera* keelcamera;

		ANIMATIONCOMPONENT_HANDLE DAparent;

		bool hasKeelBridge[11];// bay 1-11

		void DefineAnimations( void );
		void SetIndications( void );
		void SetAnimations( void );


		void SetPayloadBayDoorLatchPosition( unsigned int gang, double pos );
		void SetPayloadBayDoorPosition( int side, double pos );

		/**
		 * Defines payload bay light (LightEmitter and associated beacon)
		 * \param pos position of light
		 * \param dir direction of beam
		 * \param degWidth angular width of umbra (in degrees); penumbra is 1.1 times specified width
		 * \param bspec Beacon spec to be initialized with data
		 * \returns LightEmitter pointer
		 */
		LightEmitter* AddPayloadBayLight( VECTOR3& pos, const VECTOR3& dir, double degWidth, BEACONLIGHTSPEC& bspec );

		void CreateLights( void );
		void RunLights( void );

		void LoadPayload( void );
		void AddPRLA( unsigned short PLID, bool Reversed );
		void AddPKA( unsigned short PLID );

		void LoadLongeronPortBridgeByPLID( unsigned short PLID );
		void LoadLongeronStbdBridgeByPLID( unsigned short PLID );
		void LoadKeelBridgeByPLID( unsigned short PLID );

		void LoadLongeronPortBridge( unsigned short bay );
		void LoadLongeronStbdBridge( unsigned short bay );
		void LoadKeelBridge( unsigned short bay );

		void HandleSubsystemsVisuals( void );
		void LoadPLBBlankets( void );
		void LoadDFIWireTray( void );
		void LoadEDOKit( void );
		void LoadExtALODSKit( void );

		void CreateCCTV( void );
		void CreatePLBCam( const VECTOR3& pos, const unsigned int idx );

	public:
		PayloadBay( AtlantisSubsystemDirector* _director, const mission::MissionPayloads& payloads, const mission::PLB_Cameras& plbcameras, const std::string& orbiter, bool KuBandAntenna, bool FwdBulkDockLights, bool Liner, bool DFIWireTray, bool VentDoors4and7, bool EDOKit, bool ExtALODSKit );
		~PayloadBay( void );

		bool SingleParamParseLine() const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		void Realize( void ) override;
		void OnPostStep( double simt, double simdt, double mjd ) override;

		void UpdateLights( void );
		void CreateAttachments( void );
		void VisualCreated( VISHANDLE vis ) override;

		UINT GetDAindex( void ) const {return anim_da;};
		ANIMATIONCOMPONENT_HANDLE GetDAparent( void ) const {return DAparent;};
};


#endif// __PLB_H_