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
2022/05/29   GLS
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
#ifndef __VC_PANEL_C3_H_8B69A84E_82D7_49e2_BE5D_B389A8E2B914
#define __VC_PANEL_C3_H_8B69A84E_82D7_49e2_BE5D_B389A8E2B914
#pragma once

#include "AtlantisPanel.h"
#include "discsignals.h"


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

		DiscInPort dipTrimPanelOn;
		DiscInPort dipUpPitchTrim;
		DiscInPort dipDownPitchTrim;
		DiscInPort dipRightRollTrim;
		DiscInPort dipLeftRollTrim;
		DiscInPort dipRightYawTrim;
		DiscInPort dipLeftYawTrim;
		DiscOutPort dopUpPitchTrim;
		DiscOutPort dopDownPitchTrim;
		DiscOutPort dopRightRollTrim;
		DiscOutPort dopLeftRollTrim;
		DiscOutPort dopRightYawTrim;
		DiscOutPort dopLeftYawTrim;

		DiscInPort dipSRBSEP;
		DiscInPort dipETSEP;
		DiscInPort dipSRBSEPSW_AUTOMAN;
		DiscInPort dipETSEPSW_MAN;
		DiscOutPort dopSRBSEP;
		DiscOutPort dopETSEP;
	};
};

#endif //__VC_PANEL_C3_H_8B69A84E_82D7_49e2_BE5D_B389A8E2B914
