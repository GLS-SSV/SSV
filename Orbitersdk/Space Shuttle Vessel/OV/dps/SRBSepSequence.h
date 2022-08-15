/****************************************************************************
  This file is part of Space Shuttle Vessel

  Solid Rocket Booster Separation Sequence definition


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
2020/06/20   GLS
2021/07/03   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/10/23   GLS
2021/12/30   GLS
2022/03/29   GLS
2022/03/31   GLS
2022/04/26   GLS
2022/05/29   GLS
2022/08/05   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Solid Rocket Booster Separation Sequence definition



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
#ifndef _dps_SRBSEP_H_
#define _dps_SRBSEP_H_


#include "SimpleGPCSoftware.h"


namespace dps
{
	class SSME_Operations;
	class AscentDAP;
	class MEC_SOP;

	/**
	 * @brief	Implementation of the SRB Separation Sequencer running in the GPCs.
	 *
	 * Controls and executes the SRB Separation, checking that separation conditions are met.
	 */
	class SRBSepSequence:public SimpleGPCSoftware
	{
		private:
			SSME_Operations* pSSME_Operations;
			AscentDAP* pAscentDAP;
			MEC_SOP* pMEC_SOP;

			bool Active;

			// I-Loads
			double SRB_SEP_BACKUP_CUE_T;// (sec) V97U9751C
			double SRB_SEP_MODING_T_DELAY;// (sec) V97U9752C
			double SRB_SEP_COMMAND_T_DELAY;// (sec) V97U9753C
			double BP_ROLL_RATE_LMT_CONSTANT;// (deg/sec) V97U9757C
			double BQ_PITCH_RATE_LMT_CONSTANT;// (deg/sec) V97U9758C
			double BR_YAW_RATE_LMT_CONSTANT;// (deg/sec) V97U9759C
			double DYNAMIC_PRS_LMT;// (lb/ft2) V97U9760C
			double MAX_SRB_SEP_CUE_DIFRNTL;// (sec) V97U9761C


			bool SRBSeparationCmd;// V90X8331X
			bool LHRHSRBPC50PSI;// V90X8332X
			bool SRBSeparationInitiation;// V90X8333X
			bool SRBAutoSepInhibitCrewAlert;// V90X8340X

			bool firstpass_step2;
			bool firstpass_step4_A;
			bool firstpass_step4_B;

			double SRBSepModingTimeDelayTimer;
			double SRBSepCmdTimeDelayTimer;
			double SepCmdTimer;

			double LHPC50time;
			double RHPC50time;

			double timeSRBSEPinit;
		public:
			explicit SRBSepSequence( SimpleGPCSystem* _gpc );
			~SRBSepSequence( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			void Realize( void ) override;

			void ReadILOADs( const std::map<std::string,std::string>& ILOADs ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			/**
			 * Returns an indication of whether the SRB PC < 50 flag has been set.
			 * @return		true = PC < 50
			 */
			bool GetLHRHSRBPC50PSIFlag( void ) const;

			/**
			 * Returns an indication of whether the SRB Separation inhibit flag has been set.
			 * @return		true = SRB Separation inhibited
			 */
			bool GetSRBAutoSepInhibitCrewAlertFlag( void ) const;
	};
}


#endif// _dps_SRBSEP_H_