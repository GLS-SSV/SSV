/****************************************************************************
  This file is part of Space Shuttle Vessel

  Stabilized Payload Deployment System subsystem definition


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
#ifndef __SPDS_H
#define __SPDS_H


#include "AtlantisSubsystem.h"
#include "MPM_Base.h"
#include <discsignals.h>
#include "mission/Mission.h"


class SPDS : public AtlantisSubsystem, public MPM_Base
{
	private:
		/**
		 * Handle to SPDS attachment.
		 */
		ATTACHMENTHANDLE hAttach;

		MESHHANDLE hMesh_SPDS;
		UINT mesh_index_SPDS;
		
		UINT anim_Zo;
		UINT anim_Yo;
		UINT anim_RDU;

		VECTOR3 attach_pos;
		VECTOR3 attach_dir;

		double motorYo;// 0 = berth, 1 = outboard
		double posZo;// 0 = stow, 1 = extend
		double motorRDU;// 0 = reberth, 1 = deploy
		bool RDU_PRI_PED_ENGAGED;
		bool RDU_SEC_PED_ENGAGED;
		bool PAYLOAD_RELEASED;

		mission::MissionSPDS spds;

		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_DIS;// PORT_FWD_MECH_STOW_IND_1;
		discsignals::DiscOutPort SEC_Zo_SYS_A_EXTEND;// PORT_MID_MECH_STOW_IND_1
		discsignals::DiscOutPort PAYLOAD_RELEASE_SEC_PED_SYS_A_REL;// PORT_AFT_MECH_STOW_IND_1
		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_PRI_PED_SYS_B_ENG;// PORT_FWD_MECH_DEPLOY_IND_1
		discsignals::DiscOutPort PRI_Zo_SYS_A_EXTEND;// PORT_MID_MECH_DEPLOY_IND_1
		discsignals::DiscOutPort PAYLOAD_RELEASE_SEC_PED_SYS_A_LAT;// PORT_AFT_MECH_DEPLOY_IND_1
		discsignals::DiscOutPort PAYLOAD_RELEASE_PRI_PED_SYS_A_REL;// PORT_FWD_MECH_STOW_IND_2
		discsignals::DiscOutPort SEC_Zo_SYS_B_EXTEND;// PORT_MID_MECH_STOW_IND_2
		discsignals::DiscOutPort PAYLOAD_RELEASE_SEC_PED_SYS_B_REL;// PORT_AFT_MECH_STOW_IND_2
		discsignals::DiscOutPort PAYLOAD_RELEASE_PRI_PED_SYS_A_LAT;// PORT_FWD_MECH_DEPLOY_IND_2
		discsignals::DiscOutPort PRI_Zo_SYS_B_EXTEND;// PORT_MID_MECH_DEPLOY_IND_2
		discsignals::DiscOutPort PAYLOAD_RELEASE_SEC_PED_SYS_B_LAT;// PORT_AFT_MECH_DEPLOY_IND_2

		discsignals::DiscInPort Yo_MOTOR_A_MMC4_OUTBD_INBD;// PORT_MPM_MOTOR_1_PWR
		discsignals::DiscInPort Yo_MOTOR_B_MMC2_OUTBD_INBD;// PORT_MPM_MOTOR_2_PWR

		discsignals::DiscOutPort PRI_RDU_SYS_B_REBERTH;// PORT_FWD_MRL_LATCH_IND_1
		discsignals::DiscOutPort PRI_RDU_SYS_B_DEPLOY;// PORT_FWD_MRL_RELEASE_IND_1
		discsignals::DiscOutPort PRI_RDU_SYS_A_REBERTH;// PORT_FWD_MRL_LATCH_IND_2
		discsignals::DiscOutPort PRI_RDU_SYS_A_DEPLOY;// PORT_FWD_MRL_RELEASE_IND_2
		discsignals::DiscOutPort PAYLOAD_RELEASE_PRI_PED_SYS_B_LAT;// PORT_FWD_RETNN_RFL_1
		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_DIS;// PORT_FWD_RETNN_RFL_2

		discsignals::DiscOutPort PRI_Yo_SYS_A_BERTH;// PORT_MID_MRL_LATCH_IND_1
		discsignals::DiscOutPort PRI_Yo_SYS_A_INBD;// PORT_MID_MRL_RELEASE_IND_1
		discsignals::DiscOutPort PRI_Yo_SYS_B_BERTH;// PORT_MID_MRL_LATCH_IND_2
		discsignals::DiscOutPort PRI_Yo_SYS_B_INBD;// PORT_MID_MRL_RELEASE_IND_2
		discsignals::DiscOutPort PRI_Yo_SYS_A_OUTBD;// PORT_MID_RETNN_RFL_1
		discsignals::DiscOutPort PRI_Yo_SYS_B_OUTBD;// PORT_MID_RETNN_RFL_2

		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_ENG;// PORT_AFT_MRL_LATCH_IND_1
		discsignals::DiscOutPort PAYLOAD_RELEASE_PRI_PED_SYS_B_REL;// PORT_AFT_MRL_RELEASE_IND_1
		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_ENG;// PORT_AFT_MRL_LATCH_IND_2
		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_PRI_PED_SYS_A_ENG;// PORT_AFT_MRL_RELEASE_IND_2
		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_SEC_PED_SYS_B_DIS;// PORT_AFT_RETNN_RFL_1
		discsignals::DiscOutPort PEDESTAL_DRIVE_XFER_SEC_PED_SYS_A_DIS;// PORT_AFT_RETNN_RFL_2

		discsignals::DiscInPort PRI_RDU_MOTOR_B_MMC2_DPY_REBERTH;// PORT_FWD_MRL_MOTOR_1_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_A_MMC4_DPY_REBERTH;// PORT_FWD_MRL_MOTOR_2_PWR

		discsignals::DiscOutPort SEC_Yo_SYS_A_BERTH;// PL2_1_LAT_A
		discsignals::DiscInPort Yo_MOTOR_A_MMC1_OUTBD_BERTH;// PL2_1_MOTOR_1_PWR
		discsignals::DiscOutPort SEC_Yo_SYS_B_BERTH;// PL2_1_LAT_B
		discsignals::DiscInPort Yo_MOTOR_B_MMC3_OUTBD_BERTH;// PL2_1_MOTOR_2_PWR

		discsignals::DiscOutPort PRI_RDU_SYS_A_STOW;// PL2_2_LAT_A
		discsignals::DiscInPort PRI_RDU_MOTOR_A_MMC1_DPY_STO;// PL2_2_MOTOR_1_PWR
		discsignals::DiscInPort PL2_2_IND_A;
		discsignals::DiscOutPort PRI_RDU_SYS_B_STOW;// PL2_2_LAT_B
		discsignals::DiscInPort PRI_RDU_MOTOR_B_MMC3_DPY_STO;// PL2_2_MOTOR_2_PWR
		discsignals::DiscInPort PL2_2_IND_B;

		discsignals::DiscInPort PRI_RDU_MOTOR_A_MMC1_DPY_REBERTH;// PL2_3_MOTOR_1_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_B_MMC3_DPY_REBERTH;// PL2_3_MOTOR_2_PWR

		discsignals::DiscOutPort SEC_RDU_SYS_A_REBERTH;// PL3_3_LAT_A
		discsignals::DiscInPort SEC_RDU_MOTOR_A_MMC1_DPY_REBERTH;// PL3_3_MOTOR_1_PWR
		discsignals::DiscInPort PL3_3_IND_A;
		discsignals::DiscOutPort SEC_RDU_SYS_B_REBERTH;// PL3_3_LAT_B
		discsignals::DiscInPort SEC_RDU_MOTOR_B_MMC3_DPY_REBERTH;// PL3_3_MOTOR_2_PWR
		discsignals::DiscInPort PL3_3_IND_B;

		discsignals::DiscOutPort SEC_RDU_SYS_A_STOW;// PL3_4_LAT_A
		discsignals::DiscOutPort SEC_RDU_SYS_A_DEPLOY;// PL3_4_REL_A
		discsignals::DiscInPort SEC_RDU_MOTOR_A_MMC1_DPY_STO;// PL3_4_MOTOR_1_PWR
		discsignals::DiscOutPort SEC_RDU_SYS_B_STOW;// PL3_4_LAT_B
		discsignals::DiscOutPort SEC_RDU_SYS_B_DEPLOY;// PL3_4_REL_B
		discsignals::DiscInPort SEC_RDU_MOTOR_B_MMC3_DPY_STO;// PL3_4_MOTOR_2_PWR

		discsignals::DiscOutPort SEC_Yo_SYS_A_INBD;// PL3_5_LAT_A
		discsignals::DiscOutPort SEC_Yo_SYS_A_OUTBD;// PL3_5_REL_A
		discsignals::DiscInPort Yo_MOTOR_A_MMC1_OUTBD_INBD;// PL3_5_MOTOR_1_PWR
		discsignals::DiscInPort PL3_5_IND_A;
		discsignals::DiscOutPort SEC_Yo_SYS_B_INBD;// PL3_5_LAT_B
		discsignals::DiscOutPort SEC_Yo_SYS_B_OUTBD;// PL3_5_REL_B
		discsignals::DiscInPort Yo_MOTOR_B_MMC3_OUTBD_INBD;// PL3_5_MOTOR_2_PWR
		discsignals::DiscInPort PL3_5_IND_B;

		discsignals::DiscInPort PAYLOAD_RELEASE_SYS_A_ARM;
		discsignals::DiscInPort PAYLOAD_RELEASE_SYS_B_ARM;
		discsignals::DiscInPort PAYLOAD_RELEASE_SYS_A_FIRE;
		discsignals::DiscInPort PAYLOAD_RELEASE_SYS_B_FIRE;
		discsignals::DiscInPort PEDESTAL_DRIVE_XFER_SYS_A_ARM;
		discsignals::DiscInPort PEDESTAL_DRIVE_XFER_SYS_B_ARM;
		discsignals::DiscInPort PEDESTAL_DRIVE_XFER_SYS_A_FIRE;
		discsignals::DiscInPort PEDESTAL_DRIVE_XFER_SYS_B_FIRE;


		void AddMesh( void );
		void DefineAnimations( void );
		void CreateAttachment( void );
		void UpdateAttachment( void );
		void SetIndications( void );
		void SetAnimations( void );

		/**
		 * Determines motor power input value from 3 power sources.
		 * If at least one source has close and at least one other source has open, no motion will result.
		 * @param a		power source a
		 * @param b		power source b
		 * @param c		power source c
		 * @return		resulting power signal
		 */
		int MotorPower3( double a, double b, double c ) const;
		/**
		 * See ::MotorPower3
		 */
		int MotorPower2( double a, double b ) const;

	public:
		SPDS( AtlantisSubsystemDirector* _director, const mission::MissionSPDS& spds, bool portside );
		virtual ~SPDS( void );

		void Realize( void ) override;
		void OnPostStep( double simt, double simdt, double mjd ) override;
		bool SingleParamParseLine( void ) const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
};

#endif// __SPDS_H
