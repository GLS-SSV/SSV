/****************************************************************************
  This file is part of Space Shuttle Vessel

  Master Events Controller Subsystem Operating Program definition


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
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Master Events Controller Subsystem Operating Program definition



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
#ifndef _dps_MEC_SOP_H_
#define _dps_MEC_SOP_H_


#include "SimpleGPCSoftware.h"


class MasterEventsController;


namespace dps
{
	// Launch Sequencer
	// CR
	inline constexpr unsigned short MECSOP_LAUNCH_SRM_IGNITION_ARM = 0x0001;
	inline constexpr unsigned short MECSOP_LAUNCH_SRM_IGNITION_FIRE_1 = 0x0002;
	inline constexpr unsigned short MECSOP_LAUNCH_SRM_IGNITION_FIRE_2 = 0x0004;
	inline constexpr unsigned short MECSOP_LAUNCH_T0_UMB_RELEASE_ARM = 0x0008;
	inline constexpr unsigned short MECSOP_LAUNCH_T0_UMB_RELEASE_FIRE_1 = 0x0010;
	inline constexpr unsigned short MECSOP_LAUNCH_T0_UMB_RELEASE_FIRE_2 = 0x0020;
	inline constexpr unsigned short MECSOP_LAUNCH_SRB_RSS_PWR_OFF = 0x0040;
	inline constexpr unsigned short MECSOP_LAUNCH_SRB_RSS_SAFE = 0x0080;
	// NCR

	// SRB Sep Sequencer
	// CR
	inline constexpr unsigned short MECSOP_SRBSEP_SRB_SEP_PICS_ARM = 0x0001;
	inline constexpr unsigned short MECSOP_SRBSEP_SRB_SEP_FIRE_1 = 0x0002;
	inline constexpr unsigned short MECSOP_SRBSEP_SRB_SEP_FIRE_2 = 0x0004;
	inline constexpr unsigned short MECSOP_SRBSEP_SRB_RSS_PWR_OFF = 0x0008;
	inline constexpr unsigned short MECSOP_SRBSEP_SRB_RSS_SAFE = 0x0010;
	// NCR

	// ET Sep Sequencer
	// CR
	inline constexpr unsigned short MECSOP_ETSEP_ETUMB_UNLATCH_PICS_ARM = 0x0001;
	inline constexpr unsigned short MECSOP_ETSEP_ET_TUMBLE_SYS_ARM = 0x0002;
	inline constexpr unsigned short MECSOP_ETSEP_ET_TUMBLE_SYS_FIRE = 0x0004;
	inline constexpr unsigned short MECSOP_ETSEP_ETUMB_UNLATCH_PICS_FIRE_1 = 0x0008;
	inline constexpr unsigned short MECSOP_ETSEP_ETUMB_UNLATCH_PICS_FIRE_2 = 0x0010;
	inline constexpr unsigned short MECSOP_ETSEP_ETORB_STR_SEPN_FIRE_1 = 0x0020;
	inline constexpr unsigned short MECSOP_ETSEP_ETORB_STR_SEPN_FIRE_2 = 0x0040;
	inline constexpr unsigned short MECSOP_ETSEP_ETUMB_RETRACT_FIRE_1 = 0x0080;
	inline constexpr unsigned short MECSOP_ETSEP_ETUMB_RETRACT_FIRE_2 = 0x0100;
	inline constexpr unsigned short MECSOP_ETSEP_ETORB_STR_SEPN_PICS_ARM = 0x0200;
	// NCR

	/**
	 * @brief	Implementation of the MEC SOP software that runs in the GPCs.
	 *
	 * This class receives commands from the RSLS, SRB Sep Sequencer and ET Sep Sequencer, and outputs them to the MECs.
	 */
	class MEC_SOP:public SimpleGPCSoftware
	{
		private:
			unsigned short LaunchSequencerFlag;
			unsigned short SRBSepSequencerFlag;
			unsigned short ETSepSequencerFlag;

			bool MECMasterReset;

			MasterEventsController* pMEC1;
			MasterEventsController* pMEC2;

		public:
			explicit MEC_SOP( SimpleGPCSystem* _gpc );
			~MEC_SOP( void );

			void Realize( void ) override;

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			void SetLaunchSequencerFlag( unsigned short flag );
			//void ResetLaunchSequencerFlag( unsigned short flag );

			void SetSRBSepSequencerFlag( unsigned short flag );
			//void ResetSRBSepSequencerFlag( unsigned short flag );

			void SetETSepSequencerFlag( unsigned short flag );
			//void ResetETSepSequencerFlag( unsigned short flag );

			void SetMECMasterResetFlag( void );
	};
}


#endif// _dps_MEC_SOP_H_