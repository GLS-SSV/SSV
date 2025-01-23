/****************************************************************************
  This file is part of Space Shuttle Vessel

  RCS/RCS Crossfeed and Reconfiguration definition


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
#ifndef _dps_RCS_RCS_XFEED_H_
#define _dps_RCS_RCS_XFEED_H_


#include "../SimpleGPCSoftware.h"


namespace dps
{
	class RCS_RCS_XFEED:public SimpleGPCSoftware
	{
		private:
			unsigned short POST_SEQ_CMD_TERM_FLAG;

			// TODO init
			unsigned short OMS_L_POD_XFD_VLVS_A_CMD_1_OP;// V43K4282X
			unsigned short OMS_L_POD_XFD_VLVS_A_CMD_1_CL;// V43K4283X
			unsigned short OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_OP;// V43K4284X
			unsigned short OMS_L_POD_OXDZR_XFD_VLV_A_CMD_2_CL;// V43K4285X
			unsigned short OMS_L_POD_XFD_VLVS_B_CMD_1_OP;// V43K4286X
			unsigned short OMS_L_POD_XFD_VLVS_B_CMD_1_CL;// V43K4287X
			unsigned short OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_OP;// V43K4288X
			unsigned short OMS_L_POD_OXDZR_XFD_VLV_B_CMD_2_CL;// V43K4289X
			unsigned short OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_OP;// V43K4384X
			unsigned short OMS_L_POD_FUEL_XFD_VLV_A_CMD_2_CL;// V43K4385X
			unsigned short OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_OP;// V43K4388X
			unsigned short OMS_L_POD_FUEL_XFD_VLV_B_CMD_2_CL;// V43K4389X
			unsigned short OMS_R_POD_XFD_VLVS_A_CMD_1_OP;// V43K5282X
			unsigned short OMS_R_POD_XFD_VLVS_A_CMD_1_CL;// V43K5283X
			unsigned short OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_OP;// V43K5284X
			unsigned short OMS_R_POD_OXDZR_XFD_VLV_A_CMD_2_CL;// V43K5285X
			unsigned short OMS_R_POD_XFD_VLVS_B_CMD_1_OP;// V43K5286X
			unsigned short OMS_R_POD_XFD_VLVS_B_CMD_1_CL;// V43K5287X
			unsigned short OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_OP;// V43K5288X
			unsigned short OMS_R_POD_OXDZR_XFD_VLV_B_CMD_2_CL;// V43K5289X
			unsigned short OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_OP;// V43K5384X
			unsigned short OMS_R_POD_FUEL_XFD_VLV_A_CMD_2_CL;// V43K5385X
			unsigned short OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_OP;// V43K5388X
			unsigned short OMS_R_POD_FUEL_XFD_VLV_B_CMD_2_CL;// V43K5389X

			unsigned short RCS_L_AFT_XFD_VLV_12_GPC_OP_A;// V42K2402X
			unsigned short RCS_L_AFT_OX_XFD_V_12_GPC_OP_B;// V42K2403X
			unsigned short RCS_L_AFT_FU_XFD_V_12_GPC_OP_B;// V42K2404X
			unsigned short RCS_L_AFT_XFD_VLV_345_GPC_OP_A;// V42K2408X
			unsigned short RCS_L_AFT_OX_XFD_V_345_GPC_OP_B;// V42K2409X
			unsigned short RCS_L_AFT_FU_XFD_V_345_GPC_OP_B;// V42K2410X
			unsigned short RCS_L_AFT_XFD_V_12_GPC_CL_A;// V42K2416X
			unsigned short RCS_L_AFT_OX_XFD_V_12_GPC_CL_B;// V42K2418X
			unsigned short RCS_L_AFT_FU_XFD_V_12_GPC_CL_B;// V42K2422X
			unsigned short RCS_L_AFT_XFD_V_345_GPC_CL_A;// V42K2428X
			unsigned short RCS_L_AFT_OX_XFD_V_345_GPC_CL_B;// V42K2430X
			unsigned short RCS_L_AFT_FU_XFD_V_345_GPC_CL_B;// V42K2434X

			unsigned short RCS_R_AFT_XFD_VLV_12_GPC_OP_A;// V42K3402X
			unsigned short RCS_R_AFT_OX_XFD_V_12_GPC_OP_B;// V42K3403X
			unsigned short RCS_R_AFT_FU_XFD_V_12_GPC_OP_B;// V42K3404X
			unsigned short RCS_R_AFT_XFD_VLV_345_GPC_OP_A;// V42K3408X
			unsigned short RCS_R_AFT_OX_XFD_V_345_GPC_OP_B;// V42K3409X
			unsigned short RCS_R_AFT_FU_XFD_V_345_GPC_OP_B;// V42K3410X
			unsigned short RCS_R_AFT_XFD_V_12_GPC_CL_A;// V42K3416X
			unsigned short RCS_R_AFT_OX_XFD_V_12_GPC_CL_B;// V42K3418X
			unsigned short RCS_R_AFT_FU_XFD_V_12_GPC_CL_B;// V42K3422X
			unsigned short RCS_R_AFT_XFD_V_345_GPC_CL_A;// V42K3428X
			unsigned short RCS_R_AFT_OX_XFD_V_345_GPC_CL_B;// V42K3430X
			unsigned short RCS_R_AFT_FU_XFD_V_345_GPC_CL_B;// V42K3434X

			unsigned short RCS_L_AFT_TK_ISLN_V_12_GPC_OP_A;// V42K2342X
			unsigned short RCS_L_AFT_OX_TK_ISLN_V_12_GPC_OP_B;// V42K2343X
			unsigned short RCS_L_AFT_FU_TK_ISLN_V_12_GPC_OP_B;// V42K2344X
			unsigned short RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_OP;// V42K2346X
			unsigned short RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_OP;// V42K2347X
			unsigned short RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_OP;// V42K2349X
			unsigned short RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_OP;// V42K2350X
			unsigned short RCS_L_AFT_TK_ISLN_V_12_GPC_CL_A;// V42K2353X
			unsigned short RCS_L_AFT_OX_TK_ISLN_V_12_GPC_CL_B;// V42K2354X
			unsigned short RCS_L_AFT_FU_TK_ISLN_V_12_GPC_CL_B;// V42K2355X
			unsigned short RCS_L_AFT_OX_TK_ISLN_V_345A_GPC_CL;// V42K2357X
			unsigned short RCS_L_AFT_FU_TK_ISLN_V_345A_GPC_CL;// V42K2358X
			unsigned short RCS_L_AFT_OX_TK_ISLN_V_345B_GPC_CL;// V42K2360X
			unsigned short RCS_L_AFT_FU_TK_ISLN_V_345B_GPC_CL;// V42K2361X

			unsigned short RCS_R_AFT_TK_ISLN_V_12_GPC_OP_A;// V42K3342X
			unsigned short RCS_R_AFT_OX_TK_ISLN_V_12_GPC_OP_B;// V42K3343X
			unsigned short RCS_R_AFT_FU_TK_ISLN_V_12_GPC_OP_B;// V42K3344X
			unsigned short RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_OP;// V42K3346X
			unsigned short RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_OP;// V42K3347X
			unsigned short RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_OP;// V42K3349X
			unsigned short RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_OP;// V42K3350X
			unsigned short RCS_R_AFT_TK_ISLN_V_12_GPC_CL_A;// V42K3353X
			unsigned short RCS_R_AFT_OX_TK_ISLN_V_12_GPC_CL_B;// V42K3354X
			unsigned short RCS_R_AFT_FU_TK_ISLN_V_12_GPC_CL_B;// V42K3355X
			unsigned short RCS_R_AFT_OX_TK_ISLN_V_345A_GPC_CL;// V42K3357X
			unsigned short RCS_R_AFT_FU_TK_ISLN_V_345A_GPC_CL;// V42K3358X
			unsigned short RCS_R_AFT_OX_TK_ISLN_V_345B_GPC_CL;// V42K3360X
			unsigned short RCS_R_AFT_FU_TK_ISLN_V_345B_GPC_CL;// V42K3361X


			bool firstpass_subseqa;
			bool firstpass_subseqb;
			bool firstpass_subseqc;
			bool firstpass_stepa1;
			bool firstpass_stepa3;
			bool firstpass_stepa4;
			bool firstpass_stepa5;
			bool firstpass_stepa6;
			bool firstpass_stepb1;
			bool firstpass_stepb2;
			bool firstpass_stepb3;
			bool firstpass_stepc1;
			bool firstpass_stepc3;
			bool firstpass_stepc4;
			bool firstpass_stepc5;
			bool firstpass_stepc6;
			double timer_stepa3;
			double timer_stepa4;
			double timer_stepa5;
			double timer_stepa6;
			double timer_stepb1;
			double timer_stepb2;
			double timer_stepb3;
			double timer_stepc3;
			double timer_stepc4;
			double timer_stepc5;
			double timer_stepc6;
			bool timerena_stepa3;
			bool timerena_stepa4;
			bool timerena_stepa5;
			bool timerena_stepa6;
			bool timerena_stepb1;
			bool timerena_stepb2;
			bool timerena_stepb3;
			bool timerena_stepc3;
			bool timerena_stepc4;
			bool timerena_stepc5;
			bool timerena_stepc6;

			void SubsequenceA( void );
			void SubsequenceB( void );
			void SubsequenceC( void );
			void SubsequenceE( void );

		public:
			explicit RCS_RCS_XFEED( SimpleGPCSystem* _gpc );
			~RCS_RCS_XFEED( void );

			void OnPostStep( double simt, double simdt, double mjd ) override;

			bool OnParseLine( const char* keyword, const char* value ) override;
			void OnSaveState( FILEHANDLE scn ) const override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;
	};
}


#endif// _dps_RCS_RCS_XFEED_H_
