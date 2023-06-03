/****************************************************************************
  This file is part of Space Shuttle Vessel

  IO Control definition


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
2022/12/23   GLS
2023/06/03   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  IO Control definition



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
#ifndef _dps_IO_Control_H_
#define _dps_IO_Control_H_


#include "../SimpleGPCSoftware.h"
#include <discsignals.h>


using namespace discsignals;


namespace dps
{
	//inline constexpr int SW_DUMPSEQUENCE = 0;
	//inline constexpr int SW_BACKUPLH2VLV = 1;
	inline constexpr int SW_PNEU_L_HE_XOVR = 2;
	inline constexpr int SW_PNEU_HE_ISOL = 3;
	inline constexpr int SW_HE_ISOL_A_CTR = 4;
	inline constexpr int SW_HE_ISOL_A_LEFT = 5;
	inline constexpr int SW_HE_ISOL_A_RIGHT = 6;
	inline constexpr int SW_HE_ISOL_B_CTR = 7;
	inline constexpr int SW_HE_ISOL_B_LEFT = 8;
	inline constexpr int SW_HE_ISOL_B_RIGHT = 9;
	inline constexpr int SW_HE_IC_CTR = 10;
	inline constexpr int SW_HE_IC_LEFT = 11;
	inline constexpr int SW_HE_IC_RIGHT = 12;
	inline constexpr int SW_LH2ULLAGEPRESS = 13;
	inline constexpr int COUNT_INPUT = 14;

	inline constexpr int LH2_INBD_BU_DV_OP = 0;
	inline constexpr int LH2_OTBD_BU_DV_OP = 1;
	inline constexpr int PNEU_L_HE_XOVR_OP = 2;
	inline constexpr int PNEU_HE_ISOL_1_OP = 3;
	inline constexpr int PNEU_HE_ISOL_2_OP = 4;
	inline constexpr int HE_ISOL_A_CTR_OP = 5;
	inline constexpr int HE_ISOL_A_LEFT_OP = 6;
	inline constexpr int HE_ISOL_A_RIGHT_OP = 7;
	inline constexpr int HE_ISOL_B_CTR_OP = 8;
	inline constexpr int HE_ISOL_B_LEFT_OP = 9;
	inline constexpr int HE_ISOL_B_RIGHT_OP = 10;
	inline constexpr int HE_IC_CTR_IN_OP = 11;
	inline constexpr int HE_IC_LEFT_IN_OP = 12;
	inline constexpr int HE_IC_RIGHT_IN_OP = 13;
	inline constexpr int HE_IC_CTR_OUT_OP = 14;
	inline constexpr int HE_IC_LEFT_OUT_OP = 15;
	inline constexpr int HE_IC_RIGHT_OUT_OP = 16;
	inline constexpr int LOX_OVBD_BV = 17;
	inline constexpr int ME1_LOX_PVLV_CL_A = 18;
	inline constexpr int ME2_LOX_PVLV_CL_A = 19;
	inline constexpr int ME3_LOX_PVLV_CL_A = 20;
	inline constexpr int ME1_LOX_PVLV_CL_B = 21;
	inline constexpr int ME2_LOX_PVLV_CL_B = 22;
	inline constexpr int ME3_LOX_PVLV_CL_B = 23;
	inline constexpr int ME1_LOX_PVLV_OP_A = 24;
	inline constexpr int ME2_LOX_PVLV_OP_A = 25;
	inline constexpr int ME3_LOX_PVLV_OP_A = 26;
	inline constexpr int ME1_LOX_PVLV_OP_B = 27;
	inline constexpr int ME2_LOX_PVLV_OP_B = 28;
	inline constexpr int ME3_LOX_PVLV_OP_B = 29;
	inline constexpr int ME1_LH2_PVLV_CL = 30;
	inline constexpr int ME2_LH2_PVLV_CL = 31;
	inline constexpr int ME3_LH2_PVLV_CL = 32;
	inline constexpr int ME1_LH2_PVLV_OP = 33;
	inline constexpr int ME2_LH2_PVLV_OP = 34;
	inline constexpr int ME3_LH2_PVLV_OP = 35;
	inline constexpr int LOX_POGO_RECIRC_1 = 36;
	inline constexpr int LOX_POGO_RECIRC_2 = 37;
	inline constexpr int LOX_OTBD_FD_VLV_CL = 38;
	inline constexpr int LOX_OTBD_FD_VLV_OP = 39;
	inline constexpr int LOX_INBD_FD_VLV_CL = 40;
	inline constexpr int LOX_INBD_FD_VLV_OP = 41;
	inline constexpr int LH2_OTBD_FD_VLV_CL = 42;
	inline constexpr int LH2_OTBD_FD_VLV_OP = 43;
	inline constexpr int LH2_INBD_FD_VLV_CL = 44;
	inline constexpr int LH2_INBD_FD_VLV_OP = 45;
	inline constexpr int LH2_TOPPING_VLV_OP = 46;
	inline constexpr int LOX_REPRESS_1_OP = 47;
	inline constexpr int LOX_REPRESS_2_OP = 48;
	inline constexpr int LH2_REPRESS_1_OP = 49;
	inline constexpr int LH2_REPRESS_2_OP = 50;
	inline constexpr int LO2_FEEDLINE_RLF_ISOL_CL = 51;
	inline constexpr int LH2_FEEDLINE_RLF_ISOL_CL = 52;
	inline constexpr int GOX_FCV_1 = 53;
	inline constexpr int GOX_FCV_2 = 54;
	inline constexpr int GOX_FCV_3 = 55;
	inline constexpr int GH2_FCV_1 = 56;
	inline constexpr int GH2_FCV_2 = 57;
	inline constexpr int GH2_FCV_3 = 58;
	inline constexpr int COUNT_OUTPUT = 59;

	class IO_Control:public SimpleGPCSoftware
	{
		private:
			DiscInPort dspINPUT_1[COUNT_INPUT];
			DiscInPort dspINPUT_2[COUNT_INPUT];

			DiscOutPort dspOUTPUT[COUNT_OUTPUT];

			bool CMD[COUNT_OUTPUT];

		public:
			explicit IO_Control( SimpleGPCSystem* _gpc );
			~IO_Control( void );

			void OnPreStep( double simt, double simdt, double mjd ) override;
			void OnPostStep( double simt, double simdt, double mjd ) override;

			void Realize( void ) override;

			bool OnMajorModeChange( unsigned int newMajorMode ) override;

			int GetSWPos( int sw ) const;
			void SetCommand( int output, bool cmd );
	};
}


#endif// _dps_IO_Control_H_