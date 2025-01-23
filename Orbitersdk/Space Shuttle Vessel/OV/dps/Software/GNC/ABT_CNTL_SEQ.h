/****************************************************************************
  This file is part of Space Shuttle Vessel

  Abort Control Sequence definition


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
#ifndef _dps_ABT_CNTL_SEQ_H_
#define _dps_ABT_CNTL_SEQ_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class ABT_CNTL_SEQ:public SimpleGPCSoftware
	{
		private:
			unsigned short PRE_MECO_ICNCT_COMPLETE_FLAG;
			double SERC_IC_DEL_TIMER;
			unsigned short BURN_TIME_SEL_COMPLETE_FLAG;
			unsigned short DUMP_CUTOFF_FLAG;
			unsigned short ATO_ABORT_SELECTED;
			double OMS_DELAY_TIMER;
			double OMS_CUTOFF_DELAY;
			double ICNCT_DELAY_TIMER;
			unsigned short MM_602_DUMP_INIT_FLAG;
			double CG_TRIM_DELAY_TIMER;
			unsigned short OMS_NZ_DUMP_INHIBIT_FLAG;
			unsigned short IGN_PRESS_DELAY_INIT_FLAG;
			double IGN_PRESS_DELAY_TIMER;
			unsigned short DUMP_ENA_INIT_FLAG;
			unsigned short TWO_OME_DUMP_FLAG;
			double RCS_4X_ON_TIME;

			unsigned short OMS_L_POD_HE_ISLN_VLV_A_OP;// V43K4180X
			unsigned short OMS_L_POD_HE_ISLN_VLV_B_OP;// V43K4181X
			unsigned short OMS_L_POD_VAPOR_ISLN_VLV_1_OP;// V43K4182X
			unsigned short OMS_L_POD_VAPOR_ISLN_VLV_2_OP;// V43K4183X
			unsigned short OMS_R_POD_HE_ISLN_VLV_A_OP;// V43K5180X
			unsigned short OMS_R_POD_HE_ISLN_VLV_B_OP;// V43K5181X
			unsigned short OMS_R_POD_VAPOR_ISLN_VLV_1_OP;// V43K5182X
			unsigned short OMS_R_POD_VAPOR_ISLN_VLV_2_OP;// V43K5183X

			bool firstpass_step1a_1;
			bool firstpass_step1a_2;
			bool firstpass_step1a_3;
			bool firstpass_step1b_1;
			bool firstpass_step1b_2;
			bool firstpass_step6a;
			bool firstpass_step10;
			bool firstpass_step12_1;
			bool firstpass_step12_2;
			bool firstpass_step12_3;
			bool firstpass_step13;
			bool firstpass_step14_1;
			bool firstpass_step14_2;
			bool firstpass_step16a;
			bool firstpass_step22;
			bool firstpass_step24_1;
			bool firstpass_step24_2;
			bool firstpass_step25_1;
			bool firstpass_step25_2;

			bool ena_SERC_IC_DEL_TIMER;
			bool ena_OMS_DELAY_TIMER;
			bool ena_ICNCT_DELAY_TIMER;
			bool ena_CG_TRIM_DELAY_TIMER;
			bool ena_IGN_PRESS_DELAY_TIMER;
			bool ena_RCS_4X_ON_TIME;

			unsigned short nzcheck_step18_1;
			unsigned short nzcheck_step18_2;
			double mm602check_step23;
			double nzcheck_step26;
			double nzcheck_step28;

			double step;

		public:
			explicit ABT_CNTL_SEQ( SimpleGPCSystem* _gpc );
			~ABT_CNTL_SEQ( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_ABT_CNTL_SEQ_H_
