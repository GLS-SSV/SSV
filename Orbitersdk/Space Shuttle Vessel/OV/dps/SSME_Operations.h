/****************************************************************************
  This file is part of Space Shuttle Vessel

  Space Shuttle Main Engine Operations definition


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
2020/05/08   GLS
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/05/29   GLS
2022/08/05   GLS
2022/08/15   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Space Shuttle Main Engine Operations definition



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
#ifndef _dps_SSME_OPS_H_
#define _dps_SSME_OPS_H_


#include "SimpleGPCSoftware.h"
#include <discsignals.h>


using namespace discsignals;


namespace dps
{
	class SSME_SOP;
	class IO_Control;

	/**
	 * @brief	Implementation of the SSME Operations software running in the GPCs.
	 *
	 * Controls the sequence of operations related to the SSMEs, also containing low-level engine cutoff
	 * logic and also engine shutdown limits logic.
	 */
	class SSME_Operations:public SimpleGPCSoftware
	{
		private:
			SSME_SOP* pSSME_SOP;
			IO_Control* pIO_Control;

			DiscInPort dipLO2LowLevelSensor[4];
			DiscInPort dipLO2UllagePressureSensor[4];
			DiscInPort dipLH2LowLevelSensor[4];
			DiscInPort dipLH2UllagePressureSensor[4];

			bool ManualShutdownFlag[3];
			bool ShutdownCommandIssued[3];
			bool ShutdownFlag_A[3];
			bool PVLV_CL_CMD[3];
			bool PVLV_CL_CMD_removed[3];

			bool LowLevelSensorArm;
			bool LO2LowLevelSensorDryFlag[4];
			bool LH2LowLevelSensorDryFlag[4];
			bool LO2LowLevelSensorDsblFlag[4];
			bool LH2LowLevelSensorDsblFlag[4];
			bool LowLevel1stRun;
			double LowLevelLO2timer;
			double LowLevelLH2timer;

			bool ZeroThrust;

			unsigned short counter_A;
			unsigned short counter_B;
			unsigned short counter_CEG[3];
			unsigned short counter_DFH[3];

			double timerADG[3];
			double timerCFI[3];
			double timerLH2PVLV[3];
			double timerMECOConfirmed;

			int LimitSwitch;// 0-INH, 1-AUTO, 2-ENA

			int otherSSMEs[3][2];// engine index

		public:
			explicit SSME_Operations( SimpleGPCSystem* _gpc );
			~SSME_Operations( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;

			void Realize( void ) override;

			//bool OnParseLine( const char* keyword, const char* value );
			//void OnSaveState( FILEHANDLE scn ) const;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			/**
			 * Activates low-level sensor logic.
			 */
			void SetLowLevelSensorArmFlag( void );

			/**
			 * Sets the LO2 Low Level Sensor Disabled Flag for the specified sensor. For exclusive use by LPS.
			 * @param[in]	num	sensor number
			 */
			void SetLO2LowLevelSensorDsblFlag( int num );

			/**
			 * Sets the LH2 Low Level Sensor Disabled Flag for the specified sensor. For exclusive use by LPS.
			 * @param[in]	num	sensor number
			 */
			void SetLH2LowLevelSensorDsblFlag( int num );

			/**
			 * Returns an indication of whether the MECO Confirmed Flag has been set.
			 * HACK for IDP only
			 * @return		true = flag set
			 */
			bool GetMECOConfirmedFlag( void ) const;

			/**
			 * Returns an indication of whether the Zero Thrust Flag has been set.
			 * @return		true = flag set
			 */
			bool GetZeroThrustFlag( void ) const;
	};
}


#endif// _dps_SSME_OPS_H_