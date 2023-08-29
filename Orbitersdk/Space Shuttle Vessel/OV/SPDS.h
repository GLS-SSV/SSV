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
		UINT mesh_idx_SPDS[2];

		UINT anim_Zo;
		UINT anim_Yo;
		UINT anim_RDU[2];
		UINT anim_EjectionPiston;

		/**
		 * Handle to SPDS attachment.
		 */
		ATTACHMENTHANDLE hAttach;

		VECTOR3 attachpos;

		double pedestal_xpos[2];

		double motorYo;// 0 = berth, 1 = outboard
		double posZo;// 0 = stow, 1 = extend
		double motorRDU[2];// 0 = reberth, 1 = deploy
		double posEjectionPiston;// 0 = in, 1 = out
		bool RDU_PRI_PED_ENGAGED;
		bool RDU_SEC_PED_ENGAGED;
		bool PAYLOAD_RELEASED;
		bool unlockZo;

		UINT anim_Latch[5];

		double LatchState[5];// 0 = closed; 1 = open

		VECTOR3 CG;


		double tfZo;
		double staticposZo;// static value of posZo (no oscillation)


		discsignals::DiscOutPort LatchLAT_A[5];
		discsignals::DiscOutPort LatchLAT_B[5];
		discsignals::DiscOutPort LatchREL_A[5];
		discsignals::DiscOutPort LatchREL_B[5];
		discsignals::DiscInPort LatchMOTOR_1_PWR[5];
		discsignals::DiscInPort LatchMOTOR_2_PWR[5];
		discsignals::DiscInPort LatchIND_A[5];
		discsignals::DiscInPort LatchIND_B[5];
		discsignals::DiscOutPort LatchLAT_A_TB[5];
		discsignals::DiscOutPort LatchREL_A_TB[5];
		discsignals::DiscOutPort LatchRDY_A_TB[5];
		discsignals::DiscOutPort LatchREL_A_TM[5];
		discsignals::DiscOutPort LatchLAT_A_TM[5];
		discsignals::DiscOutPort LatchRDY_A_TM[5];
		discsignals::DiscOutPort LatchREL_B_TM[5];
		discsignals::DiscOutPort LatchLAT_B_TM[5];
		discsignals::DiscOutPort LatchRDY_B_TM[5];

		mission::MissionSPDS spds;

		discsignals::DiscOutPort PRI_Zo_SYS_A_EXTEND_TB;
		discsignals::DiscOutPort PRI_Zo_SYS_A_EXTEND_TM;// PORT_MID_MECH_DEPLOY_IND_1
		discsignals::DiscOutPort PRI_Zo_SYS_B_EXTEND_TM;// PORT_MID_MECH_DEPLOY_IND_2
		discsignals::DiscOutPort SEC_Zo_SYS_A_EXTEND_TB;
		discsignals::DiscOutPort SEC_Zo_SYS_A_EXTEND_TM;// PORT_MID_MECH_STOW_IND_1
		discsignals::DiscOutPort SEC_Zo_SYS_B_EXTEND_TM;// PORT_MID_MECH_STOW_IND_2

		discsignals::DiscInPort Yo_MOTOR_A1;// PORT_MPM_MOTOR_1_PWR
		discsignals::DiscInPort Yo_MOTOR_A2;// PL_2_SEL_1_MOTOR_1_PWR
		discsignals::DiscInPort Yo_MOTOR_A3;// PL_3_SEL_5_MOTOR_1_PWR
		discsignals::DiscInPort Yo_MOTOR_B1;// PORT_MPM_MOTOR_2_PWR
		discsignals::DiscInPort Yo_MOTOR_B2;// PL_2_SEL_1_MOTOR_2_PWR
		discsignals::DiscInPort Yo_MOTOR_B3;// PL_3_SEL_5_MOTOR_2_PWR

		discsignals::DiscInPort Yo_IND_PWR_2A;// IND_2A_1
		discsignals::DiscInPort Yo_IND_PWR_2B;// IND_2B_1
		discsignals::DiscInPort Yo_IND_PWR_3A;// IND_3A_5
		discsignals::DiscInPort Yo_IND_PWR_3B;// IND_3B_5

		discsignals::DiscOutPort PRI_Yo_OUTBD_IND_A_TB;
		discsignals::DiscOutPort PRI_Yo_OUTBD_IND_A_TM;
		discsignals::DiscOutPort PRI_Yo_OUTBD_IND_B_TM;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A1;// PORT_SHLD_MECH_DEPLOY_IND_1
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A2;// PL_2_SEL_1A_REL
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A3;// PL_3_SEL_5A_REL
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A_TB1;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A_TB2;// PL_2_SEL_1A_REL_TB
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A_TB3;// PL_3_SEL_5A_REL_TB
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A_TM1;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A_TM2;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_A_TM3;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_B1;// PORT_SHLD_MECH_DEPLOY_IND_2
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_B2;// PL_2_SEL_1B_REL
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_B3;// PL_3_SEL_5B_REL
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_B_TM1;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_B_TM2;
		discsignals::DiscOutPort SEC_Yo_OUTBD_IND_B_TM3;

		discsignals::DiscOutPort PRI_Yo_BERTH_IND_A_TB;
		discsignals::DiscOutPort PRI_Yo_BERTH_IND_A_TM;
		discsignals::DiscOutPort PRI_Yo_BERTH_IND_B_TM;
		discsignals::DiscOutPort SEC_Yo_BERTH_IND_A;// PL_2_SEL_1A_LAT
		discsignals::DiscOutPort SEC_Yo_BERTH_IND_A_TB1;
		discsignals::DiscOutPort SEC_Yo_BERTH_IND_A_TB2;// PL_2_SEL_1A_LAT_TB
		discsignals::DiscOutPort SEC_Yo_BERTH_IND_A_TM;
		discsignals::DiscOutPort SEC_Yo_BERTH_IND_B;// PL_2_SEL_1B_LAT
		discsignals::DiscOutPort SEC_Yo_BERTH_IND_B_TM;

		discsignals::DiscOutPort PRI_Yo_INBD_IND_A_TB;
		discsignals::DiscOutPort PRI_Yo_INBD_IND_A_TM;
		discsignals::DiscOutPort PRI_Yo_INBD_IND_B_TM;
		discsignals::DiscOutPort SEC_Yo_INBD_IND_A1;// PORT_SHLD_MECH_STOW_IND_1
		discsignals::DiscOutPort SEC_Yo_INBD_IND_A3;// PL_3_SEL_5A_LAT
		discsignals::DiscOutPort SEC_Yo_INBD_IND_A_TB1;
		discsignals::DiscOutPort SEC_Yo_INBD_IND_A_TB2;// PL_3_SEL_5A_LAT_TB
		discsignals::DiscOutPort SEC_Yo_INBD_IND_A_TM1;
		discsignals::DiscOutPort SEC_Yo_INBD_IND_A_TM3;
		discsignals::DiscOutPort SEC_Yo_INBD_IND_B1;// PORT_SHLD_MECH_STOW_IND_2
		discsignals::DiscOutPort SEC_Yo_INBD_IND_B3;// PL_3_SEL_5B_LAT
		discsignals::DiscOutPort SEC_Yo_INBD_IND_B_TM1;
		discsignals::DiscOutPort SEC_Yo_INBD_IND_B_TM3;


		discsignals::DiscInPort PRI_RDU_MOTOR_A1;// PORT_FWD_MRL_MOTOR_2_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_A2;// PL_2_SEL_2_MOTOR_1_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_A3;// PL_2_SEL_3_MOTOR_1_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_B1;// PORT_FWD_MRL_MOTOR_1_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_B2;// PL_2_SEL_2_MOTOR_2_PWR
		discsignals::DiscInPort PRI_RDU_MOTOR_B3;// PL_2_SEL_3_MOTOR_2_PWR

		discsignals::DiscInPort SEC_RDU_MOTOR_A3;// PL_3_SEL_3_MOTOR_1_PWR
		discsignals::DiscInPort SEC_RDU_MOTOR_A4;// PL_3_SEL_4_MOTOR_1_PWR
		discsignals::DiscInPort SEC_RDU_MOTOR_B3;// PL_3_SEL_3_MOTOR_2_PWR
		discsignals::DiscInPort SEC_RDU_MOTOR_B4;// PL_3_SEL_4_MOTOR_2_PWR

		discsignals::DiscInPort RDU_IND_PWR_2A;// IND_2A_2
		discsignals::DiscInPort RDU_IND_PWR_2B;// IND_2B_2
		discsignals::DiscInPort RDU_IND_PWR_3A;// IND_3A_3
		discsignals::DiscInPort RDU_IND_PWR_3B;// IND_3B_3

		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_A1;// PORT_FWD_MRL_LATCH_IND_2
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_A3;// PL_2_SEL_3A_LAT
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_A_TB1;
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_A_TB3;// PL_2_SEL_3A_LAT_TB
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_A_TM1;
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_A_TM3;
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_B1;// PORT_FWD_MRL_LATCH_IND_1
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_B3;// PL_2_SEL_3B_LAT
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_B_TM1;
		discsignals::DiscOutPort PRI_RDU_REBERTH_IND_B_TM3;
		discsignals::DiscOutPort SEC_RDU_REBERTH_IND_A3;// PL_3_SEL_3A_LAT
		discsignals::DiscOutPort SEC_RDU_REBERTH_IND_A_TB1;
		discsignals::DiscOutPort SEC_RDU_REBERTH_IND_A_TB3;// PL_3_SEL_3A_LAT_TB
		discsignals::DiscOutPort SEC_RDU_REBERTH_IND_A_TM3;
		discsignals::DiscOutPort SEC_RDU_REBERTH_IND_B3;// PL_3_SEL_3B_LAT
		discsignals::DiscOutPort SEC_RDU_REBERTH_IND_B_TM3;

		discsignals::DiscOutPort PRI_RDU_STOW_IND_A2;// PL_2_SEL_2A_LAT
		discsignals::DiscOutPort PRI_RDU_STOW_IND_A_TB1;
		discsignals::DiscOutPort PRI_RDU_STOW_IND_A_TB2;// PL_2_SEL_2A_LAT_TB
		discsignals::DiscOutPort PRI_RDU_STOW_IND_A_TM2;
		discsignals::DiscOutPort PRI_RDU_STOW_IND_B2;// PL_2_SEL_2B_LAT
		discsignals::DiscOutPort PRI_RDU_STOW_IND_B_TM2;
		discsignals::DiscOutPort SEC_RDU_STOW_IND_A4;// PL_3_SEL_4A_LAT
		discsignals::DiscOutPort SEC_RDU_STOW_IND_A_TB1;
		discsignals::DiscOutPort SEC_RDU_STOW_IND_A_TB4;// PL_3_SEL_4A_LAT_TB
		discsignals::DiscOutPort SEC_RDU_STOW_IND_A_TM4;
		discsignals::DiscOutPort SEC_RDU_STOW_IND_B4;// PL_3_SEL_4B_LAT
		discsignals::DiscOutPort SEC_RDU_STOW_IND_B_TM4;

		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A1;// PORT_FWD_MRL_RELEASE_IND_2
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A2;// PL_2_SEL_2A_REL
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A3;// PL_2_SEL_3A_REL
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A_TB1;
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A_TB2;// PL_2_SEL_2A_REL_TB
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A_TB3;// PL_2_SEL_3A_REL_TB
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A_TM1;
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A_TM2;
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_A_TM3;
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_B1;// PORT_FWD_MRL_RELEASE_IND_1
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_B2;// PL_2_SEL_2B_REL
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_B3;// PL_2_SEL_3B_REL
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_B_TM1;
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_B_TM2;
		discsignals::DiscOutPort PRI_RDU_DEPLOY_IND_B_TM3;
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A3;// PL_3_SEL_3A_REL
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A4;// PL_3_SEL_4A_REL
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A_TB1;
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A_TB3;// PL_3_SEL_3A_REL_TB
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A_TB4;// PL_3_SEL_4A_REL_TB
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A_TM3;
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_A_TM4;
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_B3;// PL_3_SEL_3B_REL
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_B4;// PL_3_SEL_4B_REL
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_B_TM3;
		discsignals::DiscOutPort SEC_RDU_DEPLOY_IND_B_TM4;


		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_A_DIS_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_A_DIS_TM;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_A_ENG_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_A_ENG_TM;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_B_DIS_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_B_DIS_TM;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_B_ENG_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_PRI_B_ENG_TM;

		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_A_DIS_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_A_DIS_TM;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_A_ENG_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_A_ENG_TM;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_B_DIS_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_B_DIS_TM;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_B_ENG_TB;
		discsignals::DiscOutPort SPDS_PED_DRV_XFR_SEC_B_ENG_TM;


		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_A_LAT_TB;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_A_LAT_TM;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_A_REL_TB;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_A_REL_TM;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_B_LAT_TB;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_B_LAT_TM;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_B_REL_TB;
		discsignals::DiscOutPort SPDS_PL_REL_PRI_PED_B_REL_TM;

		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_A_LAT_TB;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_A_LAT_TM;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_A_REL_TB;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_A_REL_TM;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_B_LAT_TB;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_B_LAT_TM;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_B_REL_TB;
		discsignals::DiscOutPort SPDS_PL_REL_SEC_PED_B_REL_TM;


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
		void LoadLatches( void );
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

		bool LatchesOpen( void ) const;
		bool PayloadUnlatched( void ) const;

	public:
		SPDS( AtlantisSubsystemDirector* _director, const mission::MissionSPDS& spds, bool portside );
		virtual ~SPDS( void );

		void Realize( void ) override;
		void OnPreStep( double simt, double simdt, double mjd ) override;
		bool SingleParamParseLine( void ) const override {return true;};
		bool OnParseLine( const char* line ) override;
		void OnSaveState( FILEHANDLE scn ) const override;
		void VisualCreated( VISHANDLE vis ) override;
		double GetSubsystemMass( void ) const override;
		bool GetSubsystemCoG( VECTOR3& CoG ) const override;

		void CreateAttachment( void );
		void UpdateAttachment( void );

		void GetPLBInfo( unsigned short& PLID_longeron_port1, unsigned short& PLID_longeron_port2, unsigned short& PLID_longeron_stbd1, unsigned short& PLID_longeron_stbd2, unsigned short& PLID_keel ) const;
};

#endif// __SPDS_H
