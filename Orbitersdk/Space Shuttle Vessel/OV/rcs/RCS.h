/****************************************************************************
  This file is part of Space Shuttle Vessel

  Reaction Control System definition


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
#ifndef __RCS_H_
#define __RCS_H_


#include "..\AtlantisSubsystem.h"
#include <discsignals.h>
#include <ValveManager.h>


using namespace discsignals;

class SolenoidLatchingValve;
class MotorValve;


namespace rcs
{
	class RCS:public AtlantisSubsystem
	{
		friend class Atlantis;

		private:
			ValveManager vman;

			SolenoidLatchingValve* FRCSHePressFuelIsolAVlv;
			SolenoidLatchingValve* FRCSHePressFuelIsolBVlv;
			SolenoidLatchingValve* FRCSHePressOxidIsolAVlv;
			SolenoidLatchingValve* FRCSHePressOxidIsolBVlv;

			MotorValve* FRCSFuelTankIsol12Vlv;
			MotorValve* FRCSOxidTankIsol12Vlv;
			MotorValve* FRCSFuelTankIsol345Vlv;
			MotorValve* FRCSOxidTankIsol345Vlv;

			MotorValve* FRCSFuelManifIsol1Vlv;
			MotorValve* FRCSOxidManifIsol1Vlv;
			MotorValve* FRCSFuelManifIsol2Vlv;
			MotorValve* FRCSOxidManifIsol2Vlv;
			MotorValve* FRCSFuelManifIsol3Vlv;
			MotorValve* FRCSOxidManifIsol3Vlv;
			MotorValve* FRCSFuelManifIsol4Vlv;
			MotorValve* FRCSOxidManifIsol4Vlv;
			SolenoidLatchingValve* FRCSFuelManifIsol5Vlv;
			SolenoidLatchingValve* FRCSOxidManifIsol5Vlv;


			SolenoidLatchingValve* LRCSHePressFuelIsolAVlv;
			SolenoidLatchingValve* LRCSHePressFuelIsolBVlv;
			SolenoidLatchingValve* LRCSHePressOxidIsolAVlv;
			SolenoidLatchingValve* LRCSHePressOxidIsolBVlv;

			MotorValve* LRCSFuelTankIsol12Vlv;
			MotorValve* LRCSOxidTankIsol12Vlv;
			MotorValve* LRCSFuelTankIsol345AVlv;
			MotorValve* LRCSFuelTankIsol345BVlv;
			MotorValve* LRCSOxidTankIsol345AVlv;
			MotorValve* LRCSOxidTankIsol345BVlv;

			MotorValve* LRCSFuelManifIsol1Vlv;
			MotorValve* LRCSOxidManifIsol1Vlv;
			MotorValve* LRCSFuelManifIsol2Vlv;
			MotorValve* LRCSOxidManifIsol2Vlv;
			MotorValve* LRCSFuelManifIsol3Vlv;
			MotorValve* LRCSOxidManifIsol3Vlv;
			MotorValve* LRCSFuelManifIsol4Vlv;
			MotorValve* LRCSOxidManifIsol4Vlv;
			SolenoidLatchingValve* LRCSFuelManifIsol5Vlv;
			SolenoidLatchingValve* LRCSOxidManifIsol5Vlv;

			MotorValve* LRCSFuelCrossfeed12Vlv;
			MotorValve* LRCSOxidCrossfeed12Vlv;
			MotorValve* LRCSFuelCrossfeed345Vlv;
			MotorValve* LRCSOxidCrossfeed345Vlv;


			SolenoidLatchingValve* RRCSHePressFuelIsolAVlv;
			SolenoidLatchingValve* RRCSHePressFuelIsolBVlv;
			SolenoidLatchingValve* RRCSHePressOxidIsolAVlv;
			SolenoidLatchingValve* RRCSHePressOxidIsolBVlv;

			MotorValve* RRCSFuelTankIsol12Vlv;
			MotorValve* RRCSOxidTankIsol12Vlv;
			MotorValve* RRCSFuelTankIsol345AVlv;
			MotorValve* RRCSFuelTankIsol345BVlv;
			MotorValve* RRCSOxidTankIsol345AVlv;
			MotorValve* RRCSOxidTankIsol345BVlv;

			MotorValve* RRCSFuelManifIsol1Vlv;
			MotorValve* RRCSOxidManifIsol1Vlv;
			MotorValve* RRCSFuelManifIsol2Vlv;
			MotorValve* RRCSOxidManifIsol2Vlv;
			MotorValve* RRCSFuelManifIsol3Vlv;
			MotorValve* RRCSOxidManifIsol3Vlv;
			MotorValve* RRCSFuelManifIsol4Vlv;
			MotorValve* RRCSOxidManifIsol4Vlv;
			SolenoidLatchingValve* RRCSFuelManifIsol5Vlv;
			SolenoidLatchingValve* RRCSOxidManifIsol5Vlv;

			MotorValve* RRCSFuelCrossfeed12Vlv;
			MotorValve* RRCSOxidCrossfeed12Vlv;
			MotorValve* RRCSFuelCrossfeed345Vlv;
			MotorValve* RRCSOxidCrossfeed345Vlv;


			DiscInPort F_HE_PR_VLV_A_OP_A;
			DiscInPort F_HE_PR_VLV_A_CL_A;
			DiscInPort FWD_RCS_HE_PRESS_A_SW_OPEN;
			DiscInPort FWD_RCS_HE_PRESS_A_SW_CLOSE;
			DiscInPort F_HE_FU_PRESS_V_A_OP;
			DiscInPort F_HE_FU_PRESS_V_A_CL;
			DiscInPort F_HE_OX_PRESS_V_A_OP;
			DiscInPort F_HE_OX_PRESS_V_A_CL;
			DiscOutPort FWD_RCS_HE_PRESS_A_TB_OPEN;
			DiscOutPort FWD_RCS_HE_PRESS_A_TB_CLOSE;
			DiscOutPort FWD_HE_FU_ISOV_A_POWER_OP;
			DiscOutPort FWD_HE_FU_ISOV_A_POWER_CL;
			DiscOutPort FWD_HE_OX_ISOV_A_POWER_OP;
			DiscOutPort FWD_HE_OX_ISOV_A_POWER_CL;
			DiscOutPort F_HE_FU_PRESS_V_A_OP_TM;
			DiscOutPort F_HE_FU_PRESS_V_A_CL_TM;
			DiscOutPort F_HE_OX_PRESS_V_A_OP_TM;
			DiscOutPort F_HE_OX_PRESS_V_A_CL_TM;

			DiscInPort F_HE_PR_VLV_B_OP_A;
			DiscInPort F_HE_PR_VLV_B_CL_A;
			DiscInPort FWD_RCS_HE_PRESS_B_SW_OPEN;
			DiscInPort FWD_RCS_HE_PRESS_B_SW_CLOSE;
			DiscInPort F_HE_FU_PRESS_V_B_OP;
			DiscInPort F_HE_FU_PRESS_V_B_CL;
			DiscInPort F_HE_OX_PRESS_V_B_OP;
			DiscInPort F_HE_OX_PRESS_V_B_CL;
			DiscOutPort FWD_RCS_HE_PRESS_B_TB_OPEN;
			DiscOutPort FWD_RCS_HE_PRESS_B_TB_CLOSE;
			DiscOutPort FWD_HE_FU_ISOV_B_POWER_OP;
			DiscOutPort FWD_HE_FU_ISOV_B_POWER_CL;
			DiscOutPort FWD_HE_OX_ISOV_B_POWER_OP;
			DiscOutPort FWD_HE_OX_ISOV_B_POWER_CL;
			DiscOutPort F_HE_FU_PRESS_V_B_OP_TM;
			DiscOutPort F_HE_FU_PRESS_V_B_CL_TM;
			DiscOutPort F_HE_OX_PRESS_V_B_OP_TM;
			DiscOutPort F_HE_OX_PRESS_V_B_CL_TM;

			DiscInPort F_FU_TK_ISOV_12_OP;
			DiscInPort F_FU_TK_ISOV_12_CL;
			DiscInPort F_OX_TK_ISOV_12_OP;
			DiscInPort F_OX_TK_ISOV_12_CL;
			DiscInPort F_FU_TK_ISOV_345_OP;
			DiscInPort F_FU_TK_ISOV_345_CL;
			DiscInPort F_OX_TK_ISOV_345_OP;
			DiscInPort F_OX_TK_ISOV_345_CL;
			DiscOutPort F_FU_TK_ISOV_12_OP_TM;
			DiscOutPort F_FU_TK_ISOV_12_CL_TM;
			DiscOutPort F_OX_TK_ISOV_12_OP_TM;
			DiscOutPort F_OX_TK_ISOV_12_CL_TM;
			DiscOutPort F_FU_TK_ISOV_345_OP_TM;
			DiscOutPort F_FU_TK_ISOV_345_CL_TM;
			DiscOutPort F_OX_TK_ISOV_345_OP_TM;
			DiscOutPort F_OX_TK_ISOV_345_CL_TM;

			DiscInPort F_FU_MANF_ISOV_1_OP;
			DiscInPort F_FU_MANF_ISOV_1_CL;
			DiscInPort F_OX_MANF_ISOV_1_OP;
			DiscInPort F_OX_MANF_ISOV_1_CL;
			DiscInPort F_FU_MANF_ISOV_2_OP;
			DiscInPort F_FU_MANF_ISOV_2_CL;
			DiscInPort F_OX_MANF_ISOV_2_OP;
			DiscInPort F_OX_MANF_ISOV_2_CL;
			DiscInPort F_FU_MANF_ISOV_3_OP;
			DiscInPort F_FU_MANF_ISOV_3_CL;
			DiscInPort F_OX_MANF_ISOV_3_OP;
			DiscInPort F_OX_MANF_ISOV_3_CL;
			DiscInPort F_FU_MANF_ISOV_4_OP;
			DiscInPort F_FU_MANF_ISOV_4_CL;
			DiscInPort F_OX_MANF_ISOV_4_OP;
			DiscInPort F_OX_MANF_ISOV_4_CL;
			DiscOutPort F_FU_MANF_ISOV_1_OP_TM;
			DiscOutPort F_FU_MANF_ISOV_1_CL_TM;
			DiscOutPort F_OX_MANF_ISOV_1_OP_TM;
			DiscOutPort F_OX_MANF_ISOV_1_CL_TM;
			DiscOutPort F_FU_MANF_ISOV_2_OP_TM;
			DiscOutPort F_FU_MANF_ISOV_2_CL_TM;
			DiscOutPort F_OX_MANF_ISOV_2_OP_TM;
			DiscOutPort F_OX_MANF_ISOV_2_CL_TM;
			DiscOutPort F_FU_MANF_ISOV_3_OP_TM;
			DiscOutPort F_FU_MANF_ISOV_3_CL_TM;
			DiscOutPort F_OX_MANF_ISOV_3_OP_TM;
			DiscOutPort F_OX_MANF_ISOV_3_CL_TM;
			DiscOutPort F_FU_MANF_ISOV_4_OP_TM;
			DiscOutPort F_FU_MANF_ISOV_4_CL_TM;
			DiscOutPort F_OX_MANF_ISOV_4_OP_TM;
			DiscOutPort F_OX_MANF_ISOV_4_CL_TM;

			DiscInPort F_MANF_ISOL_5_OP_A;
			DiscInPort F_MANF_ISOL_5_CL_A;
			DiscInPort F_MANF_ISOL_5_OP_B;
			DiscInPort F_MANF_ISOL_5_CL_B;
			DiscInPort F_MANF_ISOL_5_OP_C;
			DiscInPort F_MANF_ISOL_5_CL_C;
			DiscInPort FWD_RCS_MANIFOLD_ISOLATION_SW_OPEN;
			DiscInPort FWD_RCS_MANIFOLD_ISOLATION_SW_CLOSE;
			DiscInPort F_FU_MANF_ISOV_5_OP;
			DiscInPort F_FU_MANF_ISOV_5_CL;
			DiscInPort F_OX_MANF_ISOV_5_OP;
			DiscInPort F_OX_MANF_ISOV_5_CL;
			DiscOutPort FWD_RCS_MANIFOLD_ISOLATION_TB_OPEN;
			DiscOutPort FWD_RCS_MANIFOLD_ISOLATION_TB_CLOSE;
			DiscOutPort F_FU_MANF_ISOV_NO_5_POWER_OP;
			DiscOutPort F_FU_MANF_ISOV_NO_5_POWER_CL;
			DiscOutPort F_OX_MANF_ISOV_NO_5_POWER_OP;
			DiscOutPort F_OX_MANF_ISOV_NO_5_POWER_CL;
			DiscOutPort F_FU_MANF_ISOV_5_OP_TM;
			DiscOutPort F_FU_MANF_ISOV_5_CL_TM;
			DiscOutPort F_OX_MANF_ISOV_5_OP_TM;
			DiscOutPort F_OX_MANF_ISOV_5_CL_TM;

			DiscInPort L_HE_PR_VLV_A_OP_A;
			DiscInPort L_HE_PR_VLV_A_CL_A;
			DiscInPort AFT_LEFT_RCS_HE_PRESS_A_SW_OPEN;
			DiscInPort AFT_LEFT_RCS_HE_PRESS_A_SW_CLOSE;
			DiscInPort L_HE_FU_PRESS_V_A_OP;
			DiscInPort L_HE_FU_PRESS_V_A_CL;
			DiscInPort L_HE_OX_PRESS_V_A_OP;
			DiscInPort L_HE_OX_PRESS_V_A_CL;
			DiscOutPort AFT_LEFT_RCS_HE_PRESS_A_TB_OPEN;
			DiscOutPort AFT_LEFT_RCS_HE_PRESS_A_TB_CLOSE;
			DiscOutPort LEFT_HE_FU_ISOV_A_POWER_OP;
			DiscOutPort LEFT_HE_FU_ISOV_A_POWER_CL;
			DiscOutPort LEFT_HE_OX_ISOV_A_POWER_OP;
			DiscOutPort LEFT_HE_OX_ISOV_A_POWER_CL;
			DiscOutPort L_HE_FU_PRESS_V_A_OP_TM;
			DiscOutPort L_HE_FU_PRESS_V_A_CL_TM;
			DiscOutPort L_HE_OX_PRESS_V_A_OP_TM;
			DiscOutPort L_HE_OX_PRESS_V_A_CL_TM;

			DiscInPort L_HE_PR_VLV_B_OP_A;
			DiscInPort L_HE_PR_VLV_B_CL_A;
			DiscInPort AFT_LEFT_RCS_HE_PRESS_B_SW_OPEN;
			DiscInPort AFT_LEFT_RCS_HE_PRESS_B_SW_CLOSE;
			DiscInPort L_HE_FU_PRESS_V_B_OP;
			DiscInPort L_HE_FU_PRESS_V_B_CL;
			DiscInPort L_HE_OX_PRESS_V_B_OP;
			DiscInPort L_HE_OX_PRESS_V_B_CL;
			DiscOutPort AFT_LEFT_RCS_HE_PRESS_B_TB_OPEN;
			DiscOutPort AFT_LEFT_RCS_HE_PRESS_B_TB_CLOSE;
			DiscOutPort LEFT_HE_FU_ISOV_B_POWER_OP;
			DiscOutPort LEFT_HE_FU_ISOV_B_POWER_CL;
			DiscOutPort LEFT_HE_OX_ISOV_B_POWER_OP;
			DiscOutPort LEFT_HE_OX_ISOV_B_POWER_CL;
			DiscOutPort L_HE_FU_PRESS_V_B_OP_TM;
			DiscOutPort L_HE_FU_PRESS_V_B_CL_TM;
			DiscOutPort L_HE_OX_PRESS_V_B_OP_TM;
			DiscOutPort L_HE_OX_PRESS_V_B_CL_TM;

			DiscInPort L_FU_TK_ISO_V_12_OP_1;
			DiscInPort L_FU_TK_ISO_V_12_CL_1;
			DiscInPort L_OX_TK_ISO_V_12_OP_1;
			DiscInPort L_OX_TK_ISO_V_12_CL_1;
			DiscOutPort L_FU_TK_ISO_V_12_OP_TM;
			DiscOutPort L_FU_TK_ISO_V_12_CL_TM;
			DiscOutPort L_OX_TK_ISO_V_12_OP_TM;
			DiscOutPort L_OX_TK_ISO_V_12_CL_TM;

			DiscInPort L_FU_TK_ISO_V_345_A_OP;
			DiscInPort L_FU_TK_ISO_V_345_A_CL;
			DiscInPort L_OX_TK_ISO_V_345_A_OP;
			DiscInPort L_OX_TK_ISO_V_345_A_CL;
			DiscInPort L_FU_TK_ISO_V_345_B_OP;
			DiscInPort L_FU_TK_ISO_V_345_B_CL;
			DiscInPort L_OX_TK_ISO_V_345_B_OP;
			DiscInPort L_OX_TK_ISO_V_345_B_CL;
			DiscOutPort L_FU_TK_ISO_V_345_A_OP_TM;
			DiscOutPort L_FU_TK_ISO_V_345_A_CL_TM;
			DiscOutPort L_OX_TK_ISO_V_345_A_OP_TM;
			DiscOutPort L_OX_TK_ISO_V_345_A_CL_TM;
			DiscOutPort L_FU_TK_ISO_V_345_B_OP_TM;
			DiscOutPort L_FU_TK_ISO_V_345_B_CL_TM;
			DiscOutPort L_OX_TK_ISO_V_345_B_OP_TM;
			DiscOutPort L_OX_TK_ISO_V_345_B_CL_TM;

			DiscInPort L_FU_MANF_ISOV_1_OP;
			DiscInPort L_FU_MANF_ISOV_1_CL;
			DiscInPort L_OX_MANF_ISOV_1_OP;
			DiscInPort L_OX_MANF_ISOV_1_CL;
			DiscInPort L_FU_MANF_ISOV_2_OP;
			DiscInPort L_FU_MANF_ISOV_2_CL;
			DiscInPort L_OX_MANF_ISOV_2_OP;
			DiscInPort L_OX_MANF_ISOV_2_CL;
			DiscInPort L_FU_MANF_ISOV_3_OP;
			DiscInPort L_FU_MANF_ISOV_3_CL;
			DiscInPort L_OX_MANF_ISOV_3_OP;
			DiscInPort L_OX_MANF_ISOV_3_CL;
			DiscInPort L_FU_MANF_ISOV_4_OP;
			DiscInPort L_FU_MANF_ISOV_4_CL;
			DiscInPort L_OX_MANF_ISOV_4_OP;
			DiscInPort L_OX_MANF_ISOV_4_CL;
			DiscOutPort L_FU_MANF_ISOV_1_OP_TM;
			DiscOutPort L_FU_MANF_ISOV_1_CL_TM;
			DiscOutPort L_OX_MANF_ISOV_1_OP_TM;
			DiscOutPort L_OX_MANF_ISOV_1_CL_TM;
			DiscOutPort L_FU_MANF_ISOV_2_OP_TM;
			DiscOutPort L_FU_MANF_ISOV_2_CL_TM;
			DiscOutPort L_OX_MANF_ISOV_2_OP_TM;
			DiscOutPort L_OX_MANF_ISOV_2_CL_TM;
			DiscOutPort L_FU_MANF_ISOV_3_OP_TM;
			DiscOutPort L_FU_MANF_ISOV_3_CL_TM;
			DiscOutPort L_OX_MANF_ISOV_3_OP_TM;
			DiscOutPort L_OX_MANF_ISOV_3_CL_TM;
			DiscOutPort L_FU_MANF_ISOV_4_OP_TM;
			DiscOutPort L_FU_MANF_ISOV_4_CL_TM;
			DiscOutPort L_OX_MANF_ISOV_4_OP_TM;
			DiscOutPort L_OX_MANF_ISOV_4_CL_TM;

			DiscInPort L_MANF_ISO_5_OPEN_A;
			DiscInPort L_MANF_ISO_5_CLOSE_A;
			DiscInPort L_MANF_ISO_5_OPEN_B;
			DiscInPort L_MANF_ISO_5_CLOSE_B;
			DiscInPort L_MANF_ISO_5_OPEN_C;
			DiscInPort L_MANF_ISO_5_CLOSE_C;
			DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_OPEN;
			DiscInPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_SW_CLOSE;
			DiscInPort L_FU_MANF_ISOV_5_OP;
			DiscInPort L_FU_MANF_ISOV_5_CL;
			DiscInPort L_OX_MANF_ISOV_5_OP;
			DiscInPort L_OX_MANF_ISOV_5_CL;
			DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_OPEN;
			DiscOutPort AFT_LEFT_RCS_MANIFOLD_ISOLATION_TB_CLOSE;
			DiscOutPort L_FU_MANF_ISOV_NO_5_POWER_OP;
			DiscOutPort L_FU_MANF_ISOV_NO_5_POWER_CL;
			DiscOutPort L_OX_MANF_ISOV_NO_5_POWER_OP;
			DiscOutPort L_OX_MANF_ISOV_NO_5_POWER_CL;
			DiscOutPort L_FU_MANF_ISOV_5_OP_TM;
			DiscOutPort L_FU_MANF_ISOV_5_CL_TM;
			DiscOutPort L_OX_MANF_ISOV_5_OP_TM;
			DiscOutPort L_OX_MANF_ISOV_5_CL_TM;

			DiscInPort L_RCS_FU_XFD_12_OP_1;
			DiscInPort L_RCS_FU_XFD_12_CL_1;
			DiscInPort L_RCS_OX_XFD_12_OP_1;
			DiscInPort L_RCS_OX_XFD_12_CL_1;
			DiscInPort L_RCS_FU_XFD_345_OP_1;
			DiscInPort L_RCS_FU_XFD_345_CL_1;
			DiscInPort L_RCS_OX_XFD_345_OP_1;
			DiscInPort L_RCS_OX_XFD_345_CL_1;
			DiscOutPort L_RCS_FU_XFD_12_OP_TM;
			DiscOutPort L_RCS_FU_XFD_12_CL_TM;
			DiscOutPort L_RCS_OX_XFD_12_OP_TM;
			DiscOutPort L_RCS_OX_XFD_12_CL_TM;
			DiscOutPort L_RCS_FU_XFD_345_OP_TM;
			DiscOutPort L_RCS_FU_XFD_345_CL_TM;
			DiscOutPort L_RCS_OX_XFD_345_OP_TM;
			DiscOutPort L_RCS_OX_XFD_345_CL_TM;

			DiscInPort R_HE_PR_VLV_A_OP_A;
			DiscInPort R_HE_PR_VLV_A_CL_A;
			DiscInPort AFT_RIGHT_RCS_HE_PRESS_A_SW_OPEN;
			DiscInPort AFT_RIGHT_RCS_HE_PRESS_A_SW_CLOSE;
			DiscInPort R_HE_FU_PRESS_V_A_OP;
			DiscInPort R_HE_FU_PRESS_V_A_CL;
			DiscInPort R_HE_OX_PRESS_V_A_OP;
			DiscInPort R_HE_OX_PRESS_V_A_CL;
			DiscOutPort AFT_RIGHT_RCS_HE_PRESS_A_TB_OPEN;
			DiscOutPort AFT_RIGHT_RCS_HE_PRESS_A_TB_CLOSE;
			DiscOutPort RIGHT_HE_FU_ISOV_A_POWER_OP;
			DiscOutPort RIGHT_HE_FU_ISOV_A_POWER_CL;
			DiscOutPort RIGHT_HE_OX_ISOV_A_POWER_OP;
			DiscOutPort RIGHT_HE_OX_ISOV_A_POWER_CL;
			DiscOutPort R_HE_FU_PRESS_V_A_OP_TM;
			DiscOutPort R_HE_FU_PRESS_V_A_CL_TM;
			DiscOutPort R_HE_OX_PRESS_V_A_OP_TM;
			DiscOutPort R_HE_OX_PRESS_V_A_CL_TM;

			DiscInPort R_HE_PR_VLV_B_OP_A;
			DiscInPort R_HE_PR_VLV_B_CL_A;
			DiscInPort AFT_RIGHT_RCS_HE_PRESS_B_SW_OPEN;
			DiscInPort AFT_RIGHT_RCS_HE_PRESS_B_SW_CLOSE;
			DiscInPort R_HE_FU_PRESS_V_B_OP;
			DiscInPort R_HE_FU_PRESS_V_B_CL;
			DiscInPort R_HE_OX_PRESS_V_B_OP;
			DiscInPort R_HE_OX_PRESS_V_B_CL;
			DiscOutPort AFT_RIGHT_RCS_HE_PRESS_B_TB_OPEN;
			DiscOutPort AFT_RIGHT_RCS_HE_PRESS_B_TB_CLOSE;
			DiscOutPort RIGHT_HE_FU_ISOV_B_POWER_OP;
			DiscOutPort RIGHT_HE_FU_ISOV_B_POWER_CL;
			DiscOutPort RIGHT_HE_OX_ISOV_B_POWER_OP;
			DiscOutPort RIGHT_HE_OX_ISOV_B_POWER_CL;
			DiscOutPort R_HE_FU_PRESS_V_B_OP_TM;
			DiscOutPort R_HE_FU_PRESS_V_B_CL_TM;
			DiscOutPort R_HE_OX_PRESS_V_B_OP_TM;
			DiscOutPort R_HE_OX_PRESS_V_B_CL_TM;

			DiscInPort R_FU_TK_ISO_V_12_OP_1;
			DiscInPort R_FU_TK_ISO_V_12_CL_1;
			DiscInPort R_OX_TK_ISO_V_12_OP_1;
			DiscInPort R_OX_TK_ISO_V_12_CL_1;
			DiscOutPort R_FU_TK_ISO_V_12_OP_TM;
			DiscOutPort R_FU_TK_ISO_V_12_CL_TM;
			DiscOutPort R_OX_TK_ISO_V_12_OP_TM;
			DiscOutPort R_OX_TK_ISO_V_12_CL_TM;

			DiscInPort R_FU_TK_ISO_V_345_A_OP;
			DiscInPort R_FU_TK_ISO_V_345_A_CL;
			DiscInPort R_OX_TK_ISO_V_345_A_OP;
			DiscInPort R_OX_TK_ISO_V_345_A_CL;
			DiscInPort R_FU_TK_ISO_V_345_B_OP;
			DiscInPort R_FU_TK_ISO_V_345_B_CL;
			DiscInPort R_OX_TK_ISO_V_345_B_OP;
			DiscInPort R_OX_TK_ISO_V_345_B_CL;
			DiscOutPort R_FU_TK_ISO_V_345_A_OP_TM;
			DiscOutPort R_FU_TK_ISO_V_345_A_CL_TM;
			DiscOutPort R_OX_TK_ISO_V_345_A_OP_TM;
			DiscOutPort R_OX_TK_ISO_V_345_A_CL_TM;
			DiscOutPort R_FU_TK_ISO_V_345_B_OP_TM;
			DiscOutPort R_FU_TK_ISO_V_345_B_CL_TM;
			DiscOutPort R_OX_TK_ISO_V_345_B_OP_TM;
			DiscOutPort R_OX_TK_ISO_V_345_B_CL_TM;

			DiscInPort R_FU_MANF_ISOV_1_OP;
			DiscInPort R_FU_MANF_ISOV_1_CL;
			DiscInPort R_OX_MANF_ISOV_1_OP;
			DiscInPort R_OX_MANF_ISOV_1_CL;
			DiscInPort R_FU_MANF_ISOV_2_OP;
			DiscInPort R_FU_MANF_ISOV_2_CL;
			DiscInPort R_OX_MANF_ISOV_2_OP;
			DiscInPort R_OX_MANF_ISOV_2_CL;
			DiscInPort R_FU_MANF_ISOV_3_OP;
			DiscInPort R_FU_MANF_ISOV_3_CL;
			DiscInPort R_OX_MANF_ISOV_3_OP;
			DiscInPort R_OX_MANF_ISOV_3_CL;
			DiscInPort R_FU_MANF_ISOV_4_OP;
			DiscInPort R_FU_MANF_ISOV_4_CL;
			DiscInPort R_OX_MANF_ISOV_4_OP;
			DiscInPort R_OX_MANF_ISOV_4_CL;
			DiscOutPort R_FU_MANF_ISOV_1_OP_TM;
			DiscOutPort R_FU_MANF_ISOV_1_CL_TM;
			DiscOutPort R_OX_MANF_ISOV_1_OP_TM;
			DiscOutPort R_OX_MANF_ISOV_1_CL_TM;
			DiscOutPort R_FU_MANF_ISOV_2_OP_TM;
			DiscOutPort R_FU_MANF_ISOV_2_CL_TM;
			DiscOutPort R_OX_MANF_ISOV_2_OP_TM;
			DiscOutPort R_OX_MANF_ISOV_2_CL_TM;
			DiscOutPort R_FU_MANF_ISOV_3_OP_TM;
			DiscOutPort R_FU_MANF_ISOV_3_CL_TM;
			DiscOutPort R_OX_MANF_ISOV_3_OP_TM;
			DiscOutPort R_OX_MANF_ISOV_3_CL_TM;
			DiscOutPort R_FU_MANF_ISOV_4_OP_TM;
			DiscOutPort R_FU_MANF_ISOV_4_CL_TM;
			DiscOutPort R_OX_MANF_ISOV_4_OP_TM;
			DiscOutPort R_OX_MANF_ISOV_4_CL_TM;

			DiscInPort R_MANF_ISO_5_OPEN_A;
			DiscInPort R_MANF_ISO_5_CLOSE_A;
			DiscInPort R_MANF_ISO_5_OPEN_B;
			DiscInPort R_MANF_ISO_5_CLOSE_B;
			DiscInPort R_MANF_ISO_5_OPEN_C;
			DiscInPort R_MANF_ISO_5_CLOSE_C;
			DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_OPEN;
			DiscInPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_SW_CLOSE;
			DiscInPort R_FU_MANF_ISOV_5_OP;
			DiscInPort R_FU_MANF_ISOV_5_CL;
			DiscInPort R_OX_MANF_ISOV_5_OP;
			DiscInPort R_OX_MANF_ISOV_5_CL;
			DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_OPEN;
			DiscOutPort AFT_RIGHT_RCS_MANIFOLD_ISOLATION_TB_CLOSE;
			DiscOutPort R_FU_MANF_ISOV_NO_5_POWER_OP;
			DiscOutPort R_FU_MANF_ISOV_NO_5_POWER_CL;
			DiscOutPort R_OX_MANF_ISOV_NO_5_POWER_OP;
			DiscOutPort R_OX_MANF_ISOV_NO_5_POWER_CL;
			DiscOutPort R_FU_MANF_ISOV_5_OP_TM;
			DiscOutPort R_FU_MANF_ISOV_5_CL_TM;
			DiscOutPort R_OX_MANF_ISOV_5_OP_TM;
			DiscOutPort R_OX_MANF_ISOV_5_CL_TM;

			DiscInPort R_RCS_FU_XFD_12_OP_1;
			DiscInPort R_RCS_FU_XFD_12_CL_1;
			DiscInPort R_RCS_OX_XFD_12_OP_1;
			DiscInPort R_RCS_OX_XFD_12_CL_1;
			DiscInPort R_RCS_FU_XFD_345_OP_1;
			DiscInPort R_RCS_FU_XFD_345_CL_1;
			DiscInPort R_RCS_OX_XFD_345_OP_1;
			DiscInPort R_RCS_OX_XFD_345_CL_1;
			DiscOutPort R_RCS_FU_XFD_12_OP_TM;
			DiscOutPort R_RCS_FU_XFD_12_CL_TM;
			DiscOutPort R_RCS_OX_XFD_12_OP_TM;
			DiscOutPort R_RCS_OX_XFD_12_CL_TM;
			DiscOutPort R_RCS_FU_XFD_345_OP_TM;
			DiscOutPort R_RCS_FU_XFD_345_CL_TM;
			DiscOutPort R_RCS_OX_XFD_345_OP_TM;
			DiscOutPort R_RCS_OX_XFD_345_CL_TM;

			/**
			 * A F L R U D
			 *
			 * F1F, F1L, F1U, F1D
			 * F2F, F2R, F2U, F2D
			 * F3F, F3L, F3U, F3D
			 * F4R, F4D
			 * F5L, F5R
			 *
			 *
			 * L1A, L1L, L1U
			 * L2L, L2U, L2D
			 * L3A, L3L, L3D
			 * L4L, L4U, L4D
			 * L5L, L5D
			 *
			 *
			 * R1A, R1R, R1U
			 * R2R, R2U, R2D
			 * R3A, R3R, R3D
			 * R4R, R4U, R4D
			 * R5R, R5D
			 */
			DiscInPort dipDriver[44];
			DiscOutPort dopPC[44];


			unsigned short FRCS1source;
			unsigned short FRCS2source;
			unsigned short FRCS3source;
			unsigned short FRCS4source;
			unsigned short FRCS5source;

			unsigned short LRCS1source;
			unsigned short LRCS2source;
			unsigned short LRCS3source;
			unsigned short LRCS4source;
			unsigned short LRCS5source;

			unsigned short RRCS1source;
			unsigned short RRCS2source;
			unsigned short RRCS3source;
			unsigned short RRCS4source;
			unsigned short RRCS5source;

			void SetFRCS1PropSource( unsigned short source );
			void SetFRCS2PropSource( unsigned short source );
			void SetFRCS3PropSource( unsigned short source );
			void SetFRCS4PropSource( unsigned short source );
			void SetFRCS5PropSource( unsigned short source );

			void SetLRCS1PropSource( unsigned short source );
			void SetLRCS2PropSource( unsigned short source );
			void SetLRCS3PropSource( unsigned short source );
			void SetLRCS4PropSource( unsigned short source );
			void SetLRCS5PropSource( unsigned short source );

			void SetRRCS1PropSource( unsigned short source );
			void SetRRCS2PropSource( unsigned short source );
			void SetRRCS3PropSource( unsigned short source );
			void SetRRCS4PropSource( unsigned short source );
			void SetRRCS5PropSource( unsigned short source );

		public:
			RCS( AtlantisSubsystemDirector* _director, const string& _ident );
			virtual ~RCS( void );
		
			void Realize( void ) override;
			bool OnParseLine( const char* line ) override;
			bool SingleParamParseLine() const override {return true;};
			void OnSaveState( FILEHANDLE scn ) const override;
			void OnPreStep( double simt, double simdt, double mjd ) override;
	};
}

#endif// __RCS_H_
