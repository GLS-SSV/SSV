/****************************************************************************
  This file is part of Space Shuttle Vessel

  Panel C3 definition



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
2020/03/20   GLS
2020/05/08   GLS
2020/05/10   GLS
2020/06/20   GLS
2021/06/02   GLS
2021/06/07   GLS
2021/06/10   GLS
2021/06/11   GLS
2021/06/28   GLS
2021/08/23   GLS
2021/08/24   GLS
2021/09/20   GLS
2021/12/26   GLS
2021/12/28   GLS
2021/12/29   GLS
2021/12/30   GLS
2022/04/21   GLS
2022/05/29   GLS
2022/09/29   GLS
2023/11/11   GLS
2023/11/12   GLS
********************************************/
/****************************************************************************
  This file is part of Space Shuttle Ultra

  Panel C3 VC Component



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
#ifndef _VC_PANEL_C3_H_
#define _VC_PANEL_C3_H_


#include "AtlantisPanel.h"
#include <discsignals.h>


using namespace discsignals;


namespace vc
{
	class PushButtonIndicatorSingleLight;
	class LockableLever2;
	class LockableLever3;
	class StdSwitch2;
	class StdSwitch3;
	class StandardSwitchCover;
	class PushButton;


	class PanelC3 : public AtlantisPanel
	{
	public:
		explicit PanelC3( Atlantis* _sts, const std::string &orbiter );
		virtual ~PanelC3();

		void DefineVC() override;
		void RegisterVC() override;
		void Realize() override;
		void VisualCreated( void ) override;
		void OnPreStep( double simt, double simdt, double mjd ) override;

	private:
		bool OV102;
		SURFHANDLE hOV102Texture;

		//DAP PBIs
		PushButtonIndicatorSingleLight* pPBIs[24];

		LockableLever3* pOMSArm[2];

		StdSwitch2* pBFCCRTDisplay;
		StdSwitch3* pBFCCRTSelect;

		StdSwitch2* pAirDataProbeStow[2];
		LockableLever3* pAirDataProbe[2];

		StdSwitch3* pSSMELimitShutDn;

		StandardSwitchCover* pSSMESDPBCover[3];
		PushButton* pSSMESDPB[3];

		StdSwitch2* pSRBSEPSW;
		StandardSwitchCover* pSRBSEPCover;
		PushButton* pSRBSEPPB;

		LockableLever2* pETSEPSW;
		StandardSwitchCover* pETSEPCover;
		PushButton* pETSEPPB;

		LockableLever3* pBodyFlap;
		StdSwitch3* pPitchTrim;
		StdSwitch3* pRollTrim;
		StdSwitch3* pYawTrim;

		StdSwitch3* pCautionWarningMemory;
		StdSwitch3* pCautionWarningMode;

		DiscInPort dipAIR_DATA_PROBE_STOW_LEFT_ENABLE;
		DiscInPort dipAIR_DATA_PROBE_LEFT_DEPLOY;
		DiscInPort dipAIR_DATA_PROBE_LEFT_DEPLOYHEAT;
		DiscInPort dipAIR_DATA_PROBE_STOW_RIGHT_ENABLE;
		DiscInPort dipAIR_DATA_PROBE_RIGHT_DEPLOY;
		DiscInPort dipAIR_DATA_PROBE_RIGHT_DEPLOYHEAT;
		DiscOutPort dopAIR_DATA_PROBE_LEFT_DEPLOYHEAT;
		DiscOutPort dopAIR_DATA_PROBE_LEFT_DEPLOY;
		DiscOutPort dopAIR_DATA_PROBE_LEFT_STOW;
		DiscOutPort dopAIR_DATA_PROBE_STOW_LEFT_ENABLE;
		DiscOutPort dopAIR_DATA_PROBE_RIGHT_DEPLOYHEAT;
		DiscOutPort dopAIR_DATA_PROBE_RIGHT_DEPLOY;
		DiscOutPort dopAIR_DATA_PROBE_RIGHT_STOW;
		DiscOutPort dopAIR_DATA_PROBE_STOW_RIGHT_ENABLE;

		DiscInPort dipOMSArmLeftArm;
		DiscInPort dipOMSArmLeftArmPress;
		DiscInPort dipOMSArmRightArm;
		DiscInPort dipOMSArmRightArmPress;
		DiscOutPort dopOMSArmLeftArm_1;
		DiscOutPort dopOMSArmLeftArm_1_TM;
		DiscOutPort dopOMSArmLeftArm_2;
		DiscOutPort dopOMSArmLeftArm_2_TM;
		DiscOutPort dopOMSArmLeftArmPress_1;
		DiscOutPort dopOMSArmLeftArmPress_1_TM;
		DiscOutPort dopOMSArmLeftArmPress_2;
		DiscOutPort dopOMSArmLeftArmPress_2_TM;
		DiscOutPort dopOMSArmRightArm_1;
		DiscOutPort dopOMSArmRightArm_1_TM;
		DiscOutPort dopOMSArmRightArm_2;
		DiscOutPort dopOMSArmRightArm_2_TM;
		DiscOutPort dopOMSArmRightArmPress_1;
		DiscOutPort dopOMSArmRightArmPress_1_TM;
		DiscOutPort dopOMSArmRightArmPress_2;
		DiscOutPort dopOMSArmRightArmPress_2_TM;

		DiscInPort dipTrimPanelOn;
		DiscInPort dipUpPitchTrim;
		DiscInPort dipDownPitchTrim;
		DiscInPort dipRightRollTrim;
		DiscInPort dipLeftRollTrim;
		DiscInPort dipRightYawTrim;
		DiscInPort dipLeftYawTrim;
		DiscOutPort dopUpPitchTrim_A;
		DiscOutPort dopUpPitchTrim_B;
		DiscOutPort dopDownPitchTrim_A;
		DiscOutPort dopDownPitchTrim_B;
		DiscOutPort dopRightRollTrim_A;
		DiscOutPort dopRightRollTrim_B;
		DiscOutPort dopLeftRollTrim_A;
		DiscOutPort dopLeftRollTrim_B;
		DiscOutPort dopRightYawTrim_A;
		DiscOutPort dopRightYawTrim_B;
		DiscOutPort dopLeftYawTrim_A;
		DiscOutPort dopLeftYawTrim_B;

		DiscInPort dipSRBSEPSW_AUTOMAN;
		DiscInPort dipSRBSEPSW_AUTO;
		DiscInPort dipETSEPSW_MAN;
		DiscInPort dipETSEPSW_AUTO;
		DiscInPort dipSRBSEP;
		DiscInPort dipETSEP;
		DiscOutPort dopSRBSEPSW_AUTOMAN_A;
		DiscOutPort dopSRBSEPSW_AUTOMAN_B;
		DiscOutPort dopSRBSEPSW_AUTOMAN_C;
		DiscOutPort dopSRBSEPSW_AUTO_A;
		DiscOutPort dopSRBSEPSW_AUTO_B;
		DiscOutPort dopSRBSEPSW_AUTO_C;
		DiscOutPort dopETSEPSW_MAN_A;
		DiscOutPort dopETSEPSW_MAN_B;
		DiscOutPort dopETSEPSW_MAN_C;
		DiscOutPort dopETSEPSW_AUTO_A;
		DiscOutPort dopETSEPSW_AUTO_B;
		DiscOutPort dopETSEPSW_AUTO_C;
		DiscOutPort dopSRBSEP_A;
		DiscOutPort dopSRBSEP_B;
		DiscOutPort dopSRBSEP_C;
		DiscOutPort dopETSEP_A;
		DiscOutPort dopETSEP_B;
		DiscOutPort dopETSEP_C;
	};
}

#endif// _VC_PANEL_C3_H_
